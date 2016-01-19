#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

cvar_t voice_serverdebug = { "voice_serverdebug", "0", 0, 0.0f, NULL };
cvar_t sv_alltalk = { "sv_alltalk", "0", FCVAR_SERVER, 0.0f, NULL };

#else

cvar_t voice_serverdebug;
cvar_t sv_alltalk;

#endif // HOOK_GAMEDLL

CPlayerBitVec g_PlayerModEnable;
CBitVec< VOICE_MAX_PLAYERS > g_BanMasks[ VOICE_MAX_PLAYERS ];
CBitVec< VOICE_MAX_PLAYERS > g_SentGameRulesMasks[ VOICE_MAX_PLAYERS ];
CBitVec< VOICE_MAX_PLAYERS > g_SentBanMasks[ VOICE_MAX_PLAYERS ];
CPlayerBitVec g_bWantModEnable;

/* <2d3c38> ../game_shared/voice_gamemgr.cpp:68 */
void VoiceServerDebug(const char *pFmt, ...)
{
	char msg[4096];
	va_list marker;

	if (!voice_serverdebug.value)
		return;

	va_start(marker, pFmt);
	Q_vsnprintf(msg, ARRAYSIZE(msg), pFmt, marker);
	va_end(marker);

	ALERT(at_console, "%s", msg);
}

/* <2d3cd1> ../game_shared/voice_gamemgr.cpp:89 */
CVoiceGameMgr::CVoiceGameMgr(void)
{
	m_UpdateInterval = 0;
	m_nMaxPlayers = 0;
}

/* <2d3c98> ../game_shared/voice_gamemgr.cpp:96 */
CVoiceGameMgr::~CVoiceGameMgr(void)
{
	;
}

/* <2d3d0b> ../game_shared/voice_gamemgr.cpp:101 */
bool CVoiceGameMgr::Init(IVoiceGameMgrHelper *pHelper, int maxClients)
{
	m_pHelper = pHelper;
	m_nMaxPlayers = (maxClients > VOICE_MAX_PLAYERS) ? VOICE_MAX_PLAYERS : maxClients;

	PRECACHE_MODEL("sprites/voiceicon.spr");

	m_msgPlayerVoiceMask = REG_USER_MSG("VoiceMask", VOICE_MAX_PLAYERS_DW * 4 * 2);
	m_msgRequestState = REG_USER_MSG("ReqState", 0);

	// register voice_serverdebug if it hasn't been registered already
	if (!CVAR_GET_POINTER("voice_serverdebug"))
		CVAR_REGISTER(&voice_serverdebug);

	if (!CVAR_GET_POINTER("sv_alltalk"))
		CVAR_REGISTER(&sv_alltalk);

	return true;
}

/* <2d3d4e> ../game_shared/voice_gamemgr.cpp:123 */
NOXREF void CVoiceGameMgr::SetHelper(IVoiceGameMgrHelper *pHelper)
{
	m_pHelper = pHelper;
}

/* <2d4486> ../game_shared/voice_gamemgr.cpp:129 */
void CVoiceGameMgr::Update(double frametime)
{
	// Only update periodically.
	m_UpdateInterval += frametime;

	if (m_UpdateInterval >= UPDATE_INTERVAL)
		UpdateMasks();
}

/* <2d3d82> ../game_shared/voice_gamemgr.cpp:140 */
void CVoiceGameMgr::ClientConnected(edict_t *pEdict)
{
	int index = ENTINDEX(pEdict) - 1;

	// Clear out everything we use for deltas on this guy.
	g_bWantModEnable[index] = true;
	g_SentGameRulesMasks[index].Init(0);
	g_SentBanMasks[index].Init(0);
}

// Called to determine if the Receiver has muted (blocked) the Sender
// Returns true if the receiver has blocked the sender

/* <2d3ec5> ../game_shared/voice_gamemgr.cpp:152 */
bool CVoiceGameMgr::PlayerHasBlockedPlayer(CBasePlayer *pReceiver, CBasePlayer *pSender)
{
	int iReceiverIndex, iSenderIndex;

	if (!pReceiver || !pSender)
		return false;

	iReceiverIndex = pReceiver->entindex() - 1;
	iSenderIndex = pSender->entindex() - 1;

	if (iReceiverIndex < 0 || iReceiverIndex >= m_nMaxPlayers || iSenderIndex < 0 || iSenderIndex >= m_nMaxPlayers)
		return false;

	return (g_BanMasks[ iReceiverIndex ][ iSenderIndex ] != 0);
}

/* <2d401a> ../game_shared/voice_gamemgr.cpp:169 */
bool CVoiceGameMgr::ClientCommand(CBasePlayer *pPlayer, const char *cmd)
{
	int playerClientIndex = pPlayer->entindex() - 1;
	if (playerClientIndex < 0 || playerClientIndex >= m_nMaxPlayers)
	{
		VoiceServerDebug("CVoiceGameMgr::ClientCommand: cmd %s from invalid client (%d)\n", cmd, playerClientIndex);
		return true;
	}

	bool bBan = Q_stricmp(cmd, "vban") == 0;
	if (bBan && CMD_ARGC() >= 2)
	{
		for (int i = 1; i < CMD_ARGC(); ++i)
		{
			uint32 mask = 0;
			sscanf(CMD_ARGV(i), "%x", &mask);

			if (i <= VOICE_MAX_PLAYERS_DW)
			{
				VoiceServerDebug("CVoiceGameMgr::ClientCommand: vban (0x%x) from %d\n", mask, playerClientIndex);
				g_BanMasks[ playerClientIndex ].SetDWord(i - 1, mask);
			}
			else
				VoiceServerDebug("CVoiceGameMgr::ClientCommand: invalid index (%d)\n", i);
		}

		// Force it to update the masks now.
		//UpdateMasks();
		return true;
	}
	else if (Q_stricmp(cmd, "VModEnable") == 0 && CMD_ARGC() >= 2)
	{
		VoiceServerDebug("CVoiceGameMgr::ClientCommand: VModEnable (%d)\n", !!Q_atoi(CMD_ARGV(1)));

		g_PlayerModEnable[ playerClientIndex ] = !!Q_atoi(CMD_ARGV(1));
		g_bWantModEnable[ playerClientIndex ] = false;
		//UpdateMasks();
		return true;
	}

	return false;
}

/* <2d416b> ../game_shared/voice_gamemgr.cpp:215 */
void CVoiceGameMgr::UpdateMasks(void)
{
	m_UpdateInterval = 0;

	bool bAllTalk = !!(sv_alltalk.value);

	for (int iClient = 0; iClient < m_nMaxPlayers; ++iClient)
	{
		CBaseEntity *pEnt = UTIL_PlayerByIndex(iClient + 1);

		if (!pEnt
#ifndef REGAMEDLL_FIXES
			|| !pEnt->IsPlayer()
#endif	// REGAMEDLL_FIXES
		)
			continue;

		CBasePlayer *pPlayer = (CBasePlayer *)pEnt;
		CPlayerBitVec gameRulesMask;

		// Request the state of their "VModEnable" cvar.
		if (g_bWantModEnable[ iClient ])
		{
			MESSAGE_BEGIN(MSG_ONE, m_msgRequestState, NULL, pEnt->pev);
			MESSAGE_END();
		}

		if (g_PlayerModEnable[ iClient ])
		{
			// Build a mask of who they can hear based on the game rules.
			for (int iOtherClient = 0; iOtherClient < m_nMaxPlayers; ++iOtherClient)
			{
				CBaseEntity *pEnt = UTIL_PlayerByIndex(iOtherClient + 1);

				if (pEnt && (bAllTalk || m_pHelper->CanPlayerHearPlayer(pPlayer, (CBasePlayer *)pEnt)))
				{
					gameRulesMask[ iOtherClient ] = true;
				}
			}
		}

		// If this is different from what the client has, send an update.
		if (gameRulesMask != g_SentGameRulesMasks[ iClient ] || g_BanMasks[ iClient ] != g_SentBanMasks[ iClient ])
		{
			g_SentGameRulesMasks[ iClient ] = gameRulesMask;
			g_SentBanMasks[ iClient ] = g_BanMasks[ iClient ];

			MESSAGE_BEGIN(MSG_ONE, m_msgPlayerVoiceMask, NULL, pPlayer->pev);
				for (int dw = 0; dw < VOICE_MAX_PLAYERS_DW; ++dw)
				{
					WRITE_LONG(gameRulesMask.GetDWord(dw));
					WRITE_LONG(g_BanMasks[ iClient ].GetDWord(dw));
				}
			MESSAGE_END();
		}

		// Tell the engine.
		for (int iOtherClient = 0; iOtherClient < m_nMaxPlayers; ++iOtherClient)
		{
			bool bCanHear = gameRulesMask[ iOtherClient ] && !g_BanMasks[ iClient ][ iOtherClient ];
			SET_CLIENT_LISTENING(iClient + 1, iOtherClient + 1, bCanHear);
		}
	}
}
