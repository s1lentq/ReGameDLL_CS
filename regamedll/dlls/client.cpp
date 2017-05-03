#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

bool g_bClientPrintEnable = true;

char *sPlayerModelFiles[] =
{
	"models/player.mdl",
	"models/player/leet/leet.mdl",
	"models/player/gign/gign.mdl",
	"models/player/vip/vip.mdl",
	"models/player/gsg9/gsg9.mdl",
	"models/player/guerilla/guerilla.mdl",
	"models/player/arctic/arctic.mdl",
	"models/player/sas/sas.mdl",
	"models/player/terror/terror.mdl",
	"models/player/urban/urban.mdl",
	"models/player/spetsnaz/spetsnaz.mdl",	// CZ
	"models/player/militia/militia.mdl"	// CZ
};

bool g_skipCareerInitialSpawn = false;

static entity_field_alias_t entity_field_alias[] =
{
	{ "origin[0]",	0 },
	{ "origin[1]",	0 },
	{ "origin[2]",	0 },
	{ "angles[0]",	0 },
	{ "angles[1]",	0 },
	{ "angles[2]",	0 },
};

static entity_field_alias_t player_field_alias[] =
{
	{ "origin[0]",	0 },
	{ "origin[1]",	0 },
	{ "origin[2]",	0 },
};

static entity_field_alias_t custom_entity_field_alias[] =
{
	{ "origin[0]",	0 },
	{ "origin[1]",	0 },
	{ "origin[2]",	0 },
	{ "angles[0]",	0 },
	{ "angles[1]",	0 },
	{ "angles[2]",	0 },
	{ "skin",	0 },
	{ "sequence",	0 },
	{ "animtime",	0 },
};

#endif // HOOK_GAMEDLL

bool g_bServerActive = false;
PLAYERPVSSTATUS g_PVSStatus[MAX_CLIENTS];
unsigned short m_usResetDecals;
unsigned short g_iShadowSprite;

int CMD_ARGC_()
{
	if (!UseBotArgs)
		return CMD_ARGC();

	int i = 0;

	while (BotArgs[i])
		++i;

	return i;
}

const char *CMD_ARGV_(int i)
{
	if (!UseBotArgs)
		return CMD_ARGV(i);

	if (i < 4)
		return BotArgs[i];

	return NULL;
}

NOXREF void set_suicide_frame(entvars_t *pev)
{
	if (!FStrEq(STRING(pev->model), "models/player.mdl"))
		return;

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_TOSS;
	pev->deadflag = DEAD_DEAD;
	pev->nextthink = -1;
}

void BlinkAccount(CBasePlayer *player, int numBlinks)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgBlinkAcct, NULL, player->pev);
		WRITE_BYTE(numBlinks);
	MESSAGE_END();
}

BOOL EXT_FUNC ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
	return g_pGameRules->ClientConnected(pEntity, pszName, pszAddress, szRejectReason);
}

void EXT_FUNC ClientDisconnect(edict_t *pEntity)
{
	CBasePlayer *pPlayer = CBasePlayer::Instance(pEntity);

	if (!g_pGameRules->IsGameOver())
	{
		UTIL_ClientPrintAll(HUD_PRINTNOTIFY, "#Game_disconnected", STRING(pEntity->v.netname));
#ifndef REGAMEDLL_FIXES
		CSound *pSound = CSoundEnt::SoundPointerForIndex(CSoundEnt::ClientSoundIndex(pEntity));

		if (pSound)
			pSound->Reset();
#endif
		pEntity->v.takedamage = DAMAGE_NO;
		pEntity->v.solid = SOLID_NOT;
		pEntity->v.flags = FL_DORMANT;

		if (pPlayer)
			pPlayer->Disconnect();

		UTIL_SetOrigin(&pEntity->v, pEntity->v.origin);
		g_pGameRules->ClientDisconnected(pEntity);
	}

#ifndef REGAMEDLL_FIXES
	if (TheBots && pPlayer && pPlayer->IsBot())
#else
	// These checks are already inside into this CCSBotManager::ClientDisconnect
	if (TheBots)
#endif
	{
		TheBots->ClientDisconnect(pPlayer);
	}
}

void respawn(entvars_t *pev, BOOL fCopyCorpse)
{
	if (gpGlobals->coop || gpGlobals->deathmatch)
	{
		if (CSGameRules()->m_iTotalRoundsPlayed > 0)
			CSGameRules()->MarkSpawnSkipped();

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);
		if (CSGameRules()->IsCareer() && CSGameRules()->ShouldSkipSpawn() && pPlayer->IsAlive())
			g_skipCareerInitialSpawn = true;

		pPlayer->Spawn();
		g_skipCareerInitialSpawn = false;
	}
	else if (pev->deadflag > DEAD_NO)
	{
		SERVER_COMMAND("reload\n");
	}
}

// Suicide...
void EXT_FUNC ClientKill(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (pPlayer->IsObserver())
		return;

	if (pPlayer->m_iJoiningState != JOINED)
		return;

	// prevent suiciding too often
	if (pPlayer->m_fNextSuicideTime > gpGlobals->time)
		return;

	pPlayer->m_LastHitGroup = HITGROUP_GENERIC;

	// don't let them suicide for 5 seconds after suiciding
	pPlayer->m_fNextSuicideTime = gpGlobals->time + 1.0f;

	// have the player kill themself
	pEntity->v.health = 0;
	pPlayer->Killed(pev, GIB_NEVER);

	if (CSGameRules()->m_pVIP == pPlayer)
	{
		CSGameRules()->m_iConsecutiveVIP = 10;
	}
}

LINK_HOOK_VOID_CHAIN(ShowMenu, (CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText), pPlayer, bitsValidSlots, nDisplayTime, fNeedMore, pszText)

void EXT_FUNC __API_HOOK(ShowMenu)(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, NULL, pPlayer->pev);
		WRITE_SHORT(bitsValidSlots);
		WRITE_CHAR(nDisplayTime);
		WRITE_BYTE(fNeedMore);
		WRITE_STRING(pszText);
	MESSAGE_END();
}

LINK_HOOK_VOID_CHAIN(ShowVGUIMenu, (CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu), pPlayer, MenuType, BitMask, szOldMenu);

void EXT_FUNC __API_HOOK(ShowVGUIMenu)(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu)
{
#ifdef REGAMEDLL_ADD
	if (CSGameRules()->ShouldSkipShowMenu()) {
		CSGameRules()->MarkShowMenuSkipped();
		pPlayer->ResetMenu();
		return;
	}

	if (pPlayer->CSPlayer()->m_bForceShowMenu) {
		ShowMenu(pPlayer, BitMask, -1, 0, szOldMenu);
		return;
	}

#endif

	if (pPlayer->m_bVGUIMenus || MenuType > VGUI_Menu_Buy_Item)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgVGUIMenu, NULL, pPlayer->pev);
			WRITE_BYTE(MenuType);
			WRITE_SHORT(BitMask);
			WRITE_CHAR(-1);
			WRITE_BYTE(0);
			WRITE_STRING(" ");
		MESSAGE_END();
	}
	else
		ShowMenu(pPlayer, BitMask, -1, 0, szOldMenu);
}

NOXREF int CountTeams()
{
	int iNumCT = 0, iNumTerrorist = 0;
	CBaseEntity *pPlayer = NULL;

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")))
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		CBasePlayer *player = GetClassPtr<CCSPlayer>((CBasePlayer *)pPlayer->pev);

		if (player->m_iTeam == UNASSIGNED)
			continue;

		if (player->pev->flags & FL_DORMANT)
			continue;

		if (player->m_iTeam == SPECTATOR)
			continue;

		if (player->m_iTeam == CT)
			iNumCT++;

		else if (player->m_iTeam == TERRORIST)
			iNumTerrorist++;
	}

	return iNumCT - iNumTerrorist;
}

void ListPlayers(CBasePlayer *current)
{
	char message[120] = "", cNumber[12];

	CBaseEntity *pPlayer = NULL;
	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")))
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (pPlayer->pev->flags & FL_DORMANT)
			continue;

		CBasePlayer *player = GetClassPtr<CCSPlayer>((CBasePlayer *)pPlayer->pev);
		int iUserID = GETPLAYERUSERID(ENT(player->pev));

		Q_sprintf(cNumber, "%d", iUserID);
		Q_strcpy(message, "\n");
		Q_strcat(message, cNumber);
		Q_strcat(message, " : ");
		Q_strcat(message, STRING(player->pev->netname));

		ClientPrint(current->pev, HUD_PRINTCONSOLE, message);
	}

	ClientPrint(current->pev, HUD_PRINTCONSOLE, "\n");
}

int CountTeamPlayers(int iTeam)
{
	CBaseEntity *pPlayer = NULL;
	int i = 0;

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")))
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (pPlayer->pev->flags & FL_DORMANT)
			continue;

		if (GetClassPtr<CCSPlayer>((CBasePlayer *)pPlayer->pev)->m_iTeam == iTeam)
			++i;
	}

	return i;
}

void ProcessKickVote(CBasePlayer *pVotingPlayer, CBasePlayer *pKickPlayer)
{
	CBaseEntity *pTempEntity;
	CBasePlayer *pTempPlayer;
	int iValidVotes;
	int iVoteID;
	int iVotesNeeded;
	float fKickPercent;

	if (!pVotingPlayer || !pKickPlayer)
		return;

	int iTeamCount = CountTeamPlayers(pVotingPlayer->m_iTeam);

	if (iTeamCount < 3)
		return;

	iValidVotes = 0;
	pTempEntity = NULL;
	iVoteID = pVotingPlayer->m_iCurrentKickVote;

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

		if (!pTempPlayer || pTempPlayer->m_iTeam == UNASSIGNED)
			continue;

		if (pTempPlayer->m_iTeam == pVotingPlayer->m_iTeam && pTempPlayer->m_iCurrentKickVote == iVoteID)
			iValidVotes++;
	}

	if (kick_percent.value < 0)
		CVAR_SET_STRING("mp_kickpercent", "0.0");

	else if (kick_percent.value > 1)
		CVAR_SET_STRING("mp_kickpercent", "1.0");

	iVotesNeeded = iValidVotes;
	fKickPercent = (iTeamCount * kick_percent.value + 0.5);

	if (iVotesNeeded >= int(fKickPercent))
	{
		UTIL_ClientPrintAll(HUD_PRINTCENTER, "#Game_kicked", STRING(pKickPlayer->pev->netname));
		SERVER_COMMAND(UTIL_VarArgs("kick # %d\n", iVoteID));
		pTempEntity = NULL;

		while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
		{
			if (FNullEnt(pTempEntity->edict()))
				break;

			pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

			if (!pTempPlayer || pTempPlayer->m_iTeam == UNASSIGNED)
				continue;

			if (pTempPlayer->m_iTeam == pVotingPlayer->m_iTeam && pTempPlayer->m_iCurrentKickVote == iVoteID)
				pTempPlayer->m_iCurrentKickVote = 0;
		}
	}
}

void CheckStartMoney()
{
	int money = int(startmoney.value);

#ifndef REGAMEDLL_ADD
	if (money > 16000)
		CVAR_SET_FLOAT("mp_startmoney", 16000);
	else if (money < 800)
		CVAR_SET_FLOAT("mp_startmoney", 800);
#else
	int max_money = int(maxmoney.value);

	if (money > max_money)
		CVAR_SET_FLOAT("mp_startmoney", max_money);
	else if (money < 0)
		CVAR_SET_FLOAT("mp_startmoney", 0);
#endif

}

void EXT_FUNC ClientPutInServer(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);

	pPlayer->SetCustomDecalFrames(-1);
	pPlayer->SetPrefsFromUserinfo(GET_INFO_BUFFER(pEntity));

	if (!g_pGameRules->IsMultiplayer())
	{
		pPlayer->Spawn();
		return;
	}

	pPlayer->m_bNotKilled = true;
	pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
	pPlayer->m_iTeamKills = 0;
	pPlayer->m_bJustConnected = true;
	pPlayer->Spawn();
	pPlayer->m_bTeamChanged = false;
	pPlayer->m_iNumSpawns = 0;

	CheckStartMoney();

#ifdef REGAMEDLL_ADD
	pPlayer->AddAccount(startmoney.value, RT_PLAYER_JOIN);
#else
	pPlayer->m_iAccount = int(startmoney.value);
#endif

	pPlayer->m_fGameHUDInitialized = FALSE;
	pPlayer->m_flDisplayHistory &= ~DHF_ROUND_STARTED;
	pPlayer->pev->flags |= FL_SPECTATOR;
	pPlayer->pev->solid = SOLID_NOT;
	pPlayer->pev->movetype = MOVETYPE_NOCLIP;
	pPlayer->pev->effects = EF_NODRAW;
	pPlayer->pev->effects |= EF_NOINTERP;
	pPlayer->pev->takedamage = DAMAGE_NO;
	pPlayer->pev->deadflag = DEAD_DEAD;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->m_iJoiningState = READINGLTEXT;
	pPlayer->m_iTeam = UNASSIGNED;
	pPlayer->pev->fixangle = 1;
	pPlayer->m_iModelName = MODEL_URBAN;
	pPlayer->m_bContextHelp = true;
	pPlayer->m_bHasNightVision = false;
	pPlayer->m_iHostagesKilled = 0;
	pPlayer->m_iMapVote = 0;
	pPlayer->m_iCurrentKickVote = 0;
	pPlayer->m_fDeadTime = 0;
	pPlayer->has_disconnected = false;
	pPlayer->m_iMenu = Menu_OFF;
	pPlayer->ClearAutoBuyData();
	pPlayer->m_rebuyString = NULL;

	SET_CLIENT_MAXSPEED(ENT(pPlayer->pev), 1);
	SET_MODEL(ENT(pPlayer->pev), "models/player.mdl");

	pPlayer->SetThink(NULL);

	CBaseEntity *pTarget = NULL;
	pPlayer->m_pIntroCamera = UTIL_FindEntityByClassname(NULL, "trigger_camera");

	if (g_pGameRules && g_pGameRules->IsMultiplayer())
	{
		CSGameRules()->m_bMapHasCameras = (pPlayer->m_pIntroCamera != NULL);
	}

	if (pPlayer->m_pIntroCamera)
	{
		// find the target (by default info_target) for the camera view direction.
		pTarget = UTIL_FindEntityByTargetname(NULL, STRING(pPlayer->m_pIntroCamera->pev->target));
	}

	if (pPlayer->m_pIntroCamera && pTarget)
	{
		Vector CamAngles = UTIL_VecToAngles((pTarget->pev->origin - pPlayer->m_pIntroCamera->pev->origin).Normalize());
		CamAngles.x = -CamAngles.x;

		UTIL_SetOrigin(pPlayer->pev, pPlayer->m_pIntroCamera->pev->origin);

		pPlayer->pev->angles = CamAngles;
		pPlayer->pev->v_angle = pPlayer->pev->angles;

		pPlayer->m_fIntroCamTime = gpGlobals->time + 6;
		pPlayer->pev->view_ofs = g_vecZero;
	}
#ifndef REGAMEDLL_FIXES
	else
	{
		pPlayer->m_iTeam = CT;

		if (g_pGameRules)
		{
			g_pGameRules->GetPlayerSpawnSpot(pPlayer);
		}

		pPlayer->m_iTeam = UNASSIGNED;
		pPlayer->pev->v_angle = g_vecZero;
		pPlayer->pev->angles = gpGlobals->v_forward;
	}
#endif

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, (CBaseEntity *)pPlayer);
	}

	pPlayer->m_iJoiningState = SHOWLTEXT;

	static char sName[128];
	Q_strcpy(sName, STRING(pPlayer->pev->netname));

	for (char *pApersand = sName; pApersand && *pApersand != '\0'; pApersand++)
	{
		if (*pApersand == '%')
			*pApersand = ' ';
	}

	UTIL_ClientPrintAll(HUD_PRINTNOTIFY, "#Game_connected", (sName[0] != '\0') ? sName : "<unconnected>");
}

NOXREF int Q_strlen_(const char *str)
{
	int count = 0;
	if (str && *str) {
		while (str[count++ + 1]);
	}

	return count;
}

void Host_Say(edict_t *pEntity, BOOL teamonly)
{
	CBasePlayer *client;
	int j;
	char *p;
	char text[128];
	char szTemp[256];
	const char *cpSay = "say";
	const char *cpSayTeam = "say_team";
	const char *pcmd = CMD_ARGV_(0);
	bool bSenderDead = false;
	bool bReciverDead = false;
	
#ifdef REGAMEDLL_ADD
	int chatFlags = UTIL_ReadFlags(chat_flags.string);
#endif

	entvars_t *pev = &pEntity->v;
	CBasePlayer *player = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);

	if (player->m_flLastTalk != 0.0f && gpGlobals->time - player->m_flLastTalk < 0.66f)
		return;

	player->m_flLastTalk = gpGlobals->time;

	if (player->pev->deadflag != DEAD_NO)
		bSenderDead = true;

	// We can get a raw string now, without the "say " prepended
	if (CMD_ARGC_() == 0)
		return;

	if (!Q_stricmp(pcmd, cpSay) || !Q_stricmp(pcmd, cpSayTeam))
	{
		if (CMD_ARGC_() >= 2)
		{
			p = (char *)CMD_ARGS();
		}
		else
		{
			// say with a blank message, nothing to do
			return;
		}
	}
	else // Raw text, need to prepend argv[0]
	{
		if (CMD_ARGC_() >= 2)
		{
			Q_sprintf(szTemp, "%s %s", (char *)pcmd, (char *)CMD_ARGS());
		}
		else
		{
			// Just a one word command, use the first word...sigh
			Q_sprintf(szTemp, "%s", (char *)pcmd);
		}

		p = szTemp;
	}

	// remove quotes if present
	if (*p == '"')
	{
		p++;
		p[Q_strlen(p) - 1] = '\0';
	}

	// make sure the text has content
	if (/*!p || */!p[0] || !Q_UnicodeValidate(p))
	{
		// no character found, so say nothing
		return;
	}

	Q_StripUnprintableAndSpace(p);

	if (Q_strlen(p) <= 0)
		return;

	const char *placeName = NULL;
	char *pszFormat = NULL;
	char *pszConsoleFormat = NULL;
	bool consoleUsesPlaceName = false;

	// team only
	if (teamonly)
	{
		if (g_bIsCzeroGame && (player->m_iTeam == CT || player->m_iTeam == TERRORIST))
		{
			// search the place name where is located the player
			Place playerPlace = TheNavAreaGrid.GetPlace(&player->pev->origin);
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();

			for (auto it : *placeList)
			{
				if (it->GetID() == playerPlace)
				{
					placeName = it->GetName();
					break;
				}
			}
		}

		if (player->m_iTeam == CT)
		{
			if (bSenderDead)
			{
				pszFormat = "#Cstrike_Chat_CT_Dead";
				pszConsoleFormat = "*DEAD*(Counter-Terrorist) %s : %s";
			}
			else if (placeName)
			{
				pszFormat = "#Cstrike_Chat_CT_Loc";
				pszConsoleFormat = "*(Counter-Terrorist) %s @ %s : %s";
				consoleUsesPlaceName = true;
			}
			else
			{
				pszFormat = "#Cstrike_Chat_CT";
				pszConsoleFormat = "(Counter-Terrorist) %s : %s";
			}
		}
		else if (player->m_iTeam == TERRORIST)
		{
			if (bSenderDead)
			{
				pszFormat = "#Cstrike_Chat_T_Dead";
				pszConsoleFormat = "*DEAD*(Terrorist) %s : %s";
			}
			else if (placeName)
			{
				pszFormat = "#Cstrike_Chat_T_Loc";
				pszConsoleFormat = "(Terrorist) %s @ %s : %s";
				consoleUsesPlaceName = true;
			}
			else
			{
				pszFormat = "#Cstrike_Chat_T";
				pszConsoleFormat = "(Terrorist) %s : %s";
			}
		}
		else
		{
			pszFormat = "#Cstrike_Chat_Spec";
			pszConsoleFormat = "(Spectator) %s : %s";
		}
	}
	// everyone
	else
	{
		if (bSenderDead)
		{
			if (player->m_iTeam == SPECTATOR)
			{
				pszFormat = "#Cstrike_Chat_AllSpec";
				pszConsoleFormat = "*SPEC* %s : %s";
			}
			else
			{
				pszFormat = "#Cstrike_Chat_AllDead";
				pszConsoleFormat = "*DEAD* %s : %s";
			}
		}
		else
		{
			pszFormat = "#Cstrike_Chat_All";
			pszConsoleFormat = "%s : %s";
		}
	}

	text[0] = '\0';

	// -3 for /n and null terminator
	j = sizeof(text) - 3 - Q_strlen(text) - Q_strlen(pszFormat);

	if (placeName)
	{
		j -= Q_strlen(placeName) + 1;
	}

	if ((signed int)Q_strlen(p) > j)
		p[j] = 0;

	for (char *pAmpersand = p; pAmpersand && *pAmpersand != '\0'; pAmpersand++)
	{
		if (pAmpersand[0] == '%')
		{
			if (pAmpersand[1] != 'l' && pAmpersand[1] != ' ' && pAmpersand[1] != '\0')
			{
				pAmpersand[0] = ' ';
			}
		}
	}

	Q_strcat(text, p);
	Q_strcat(text, "\n");

	// loop through all players
	// Start with the first player.
	// This may return the world in single player if the client types something between levels or during spawn
	// so check it, or it will infinite loop

	client = NULL;
	while ((client = (CBasePlayer *)UTIL_FindEntityByClassname(client, "player")))
	{
		if (FNullEnt(client->edict()))
			break;

		if (!client->pev)
			continue;

		if (client->edict() == pEntity)
			continue;

		// Not a client ? (should never be true)
		if (!client->IsNetClient())
			continue;

		// can the receiver hear the sender? or has he muted him?
		if (gpGlobals->deathmatch != 0.0f && CSGameRules()->m_VoiceGameMgr.PlayerHasBlockedPlayer(client, player))
			continue;

		if (teamonly && client->m_iTeam != player->m_iTeam)
			continue;
			
		if (client->pev->deadflag != DEAD_NO)
			bReciverDead = true;

#ifdef REGAMEDLL_ADD			
		if ((bReciverDead && !bSenderDead) || (!bReciverDead && bSenderDead))
#else
		if ((client->pev->deadflag != DEAD_NO && !bSenderDead) || (client->pev->deadflag == DEAD_NO && bSenderDead))
#endif
		{
			if (!(player->pev->flags & FL_PROXY))
				continue;
		}

		if ((client->m_iIgnoreGlobalChat == IGNOREMSG_ENEMY && client->m_iTeam == player->m_iTeam)
			|| client->m_iIgnoreGlobalChat == IGNOREMSG_NONE)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgSayText, NULL, client->pev);
				WRITE_BYTE(ENTINDEX(pEntity));
				WRITE_STRING(pszFormat);
				WRITE_STRING("");
				WRITE_STRING(text);

				if (placeName)
				{
					WRITE_STRING(placeName);
				}

			MESSAGE_END();
		}
	}

	char *fullText = p;

	// print to the sending client
	MESSAGE_BEGIN(MSG_ONE, gmsgSayText, NULL, &pEntity->v);
		WRITE_BYTE(ENTINDEX(pEntity));
		WRITE_STRING(pszFormat);
		WRITE_STRING("");
		WRITE_STRING(text);

		if (placeName)
		{
			WRITE_STRING(placeName);
		}

	MESSAGE_END();

	// echo to server console
	if (pszConsoleFormat)
	{
		if (placeName && consoleUsesPlaceName)
			SERVER_PRINT(UTIL_VarArgs(pszConsoleFormat, STRING(player->pev->netname), placeName, text));
		else
			SERVER_PRINT(UTIL_VarArgs(pszConsoleFormat, STRING(player->pev->netname), text));
	}
	else
		SERVER_PRINT(text);

	if (logmessages.value)
	{
		const char *temp = teamonly ? "say_team" : "say";
		const char *deadText = (player->m_iTeam != SPECTATOR && bSenderDead) ? " (dead)" : "";

		char *szTeam = GetTeam(player->m_iTeam);

		UTIL_LogPrintf("\"%s<%i><%s><%s>\" %s \"%s\"%s\n", STRING(player->pev->netname), GETPLAYERUSERID(player->edict()), GETPLAYERAUTHID(player->edict()),
			szTeam, temp, fullText, deadText);
	}
}

bool CanBuyThis(CBasePlayer *pPlayer, int iWeapon)
{
	if (pPlayer->HasShield() && iWeapon == WEAPON_ELITE)
		return false;

	if (pPlayer->HasShield() && iWeapon == WEAPON_SHIELDGUN)
		return false;

	if (pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ] && pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ]->m_iId == WEAPON_ELITE && iWeapon == WEAPON_SHIELDGUN)
		return false;

	if (pPlayer->m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ] && pPlayer->m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ]->m_iId == iWeapon)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cstrike_Already_Own_Weapon");
		}

		return false;
	}

	if (pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ] && pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ]->m_iId == iWeapon)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cstrike_Already_Own_Weapon");
		}

		return false;
	}

	if (!CanBuyWeaponByMaptype(pPlayer->m_iTeam, (WeaponIdType)iWeapon, CSGameRules()->m_bMapHasVIPSafetyZone == TRUE))
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Buy_This");
		}

		return false;
	}

	return true;
}

void BuyPistol(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 5)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	switch (iSlot)
	{
	case 1:
		buyWeapon = WEAPON_GLOCK18;
		break;
	case 2:
		buyWeapon = WEAPON_USP;
		break;
	case 3:
		buyWeapon = WEAPON_P228;
		break;
	case 4:
		buyWeapon = WEAPON_DEAGLE;
		break;
	case 5:
		buyWeapon = (pPlayer->m_iTeam == CT) ? WEAPON_FIVESEVEN : WEAPON_ELITE;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuyShotgun(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 2)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	switch (iSlot)
	{
	case 1:
		buyWeapon = WEAPON_M3;
		break;
	case 2:
		buyWeapon = WEAPON_XM1014;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuySubMachineGun(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 4)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	switch (iSlot)
	{
	case 1:
		buyWeapon = (pPlayer->m_iTeam == CT) ? WEAPON_TMP : WEAPON_MAC10;
		break;
	case 2:
		buyWeapon = WEAPON_MP5N;
		break;
	case 3:
		buyWeapon = WEAPON_UMP45;
		break;
	case 4:
		buyWeapon = WEAPON_P90;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuyRifle(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 6)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	bool bIsCT = (pPlayer->m_iTeam == CT) ? true : false;

	switch (iSlot)
	{
	case 2:
		buyWeapon = bIsCT ? WEAPON_SCOUT : WEAPON_AK47;
		break;
	case 3:
		buyWeapon = bIsCT ? WEAPON_M4A1 : WEAPON_SCOUT;
		break;
	case 4:
		buyWeapon = bIsCT ? WEAPON_AUG : WEAPON_SG552;
		break;
	case 5:
		buyWeapon = bIsCT ? WEAPON_SG550 : WEAPON_AWP;
		break;
	case 6:
		buyWeapon = bIsCT ? WEAPON_AWP : WEAPON_G3SG1;
		break;
	default:
		buyWeapon = bIsCT ? WEAPON_FAMAS : WEAPON_GALIL;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuyMachineGun(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot != 1)
		return;

	BuyWeaponByWeaponID(pPlayer, WEAPON_M249);
}

void BuyItem(CBasePlayer *pPlayer, int iSlot)
{
	int iItemPrice = 0;
	const char *pszItem = NULL;

	if (!pPlayer->CanPlayerBuy(true))
		return;

	if (pPlayer->m_iTeam == CT)
	{
		if (iSlot < 1 || iSlot > 8)
			return;
	}
	else
	{
		if (iSlot < 1 || iSlot > 6)
			return;
	}

	bool bFullArmor = (pPlayer->pev->armorvalue >= 100);
	bool bHasHelmet = (pPlayer->m_iKevlar == ARMOR_VESTHELM);
	bool bEnoughMoney = false;

	switch (iSlot)
	{
		case MENU_SLOT_ITEM_VEST:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_KEVLAR, ITEM_TYPE_BUYING))
				return;
#endif
			if (bFullArmor)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar");
				}

				return;
			}

			if (pPlayer->m_iAccount >= KEVLAR_PRICE)
			{
				if (bHasHelmet && g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Helmet_Bought_Kevlar");
				}

				bEnoughMoney = true;
				pszItem = "item_kevlar";
				iItemPrice = KEVLAR_PRICE;
			}
			break;
		}
		case MENU_SLOT_ITEM_VESTHELM:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_ASSAULT, ITEM_TYPE_BUYING))
				return;
#endif
			if (bFullArmor)
			{
				if (bHasHelmet)
				{
					if (g_bClientPrintEnable)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar_Helmet");
					}

					return;
				}

				if (pPlayer->m_iAccount >= HELMET_PRICE)
				{
					if (g_bClientPrintEnable)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar_Bought_Helmet");
					}

					bEnoughMoney = true;
					pszItem = "item_assaultsuit";
					iItemPrice = HELMET_PRICE;
				}
				break;
			}
			else
			{
				if (bHasHelmet)
				{
					if (pPlayer->m_iAccount >= KEVLAR_PRICE)
					{
						if (g_bClientPrintEnable)
						{
							ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Helmet_Bought_Kevlar");
						}

						bEnoughMoney = true;
						pszItem = "item_assaultsuit";
						iItemPrice = KEVLAR_PRICE;
					}
				}
				else
				{
					if (pPlayer->m_iAccount >= ASSAULTSUIT_PRICE)
					{
						bEnoughMoney = true;
						pszItem = "item_assaultsuit";
						iItemPrice = ASSAULTSUIT_PRICE;
					}
				}
			}
			break;
		}
		case MENU_SLOT_ITEM_FLASHGREN:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_FLASHBANG, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->AmmoInventory(AMMO_FLASHBANG) >= MaxAmmoCarry(WEAPON_FLASHBANG))
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= FLASHBANG_PRICE)
			{
				bEnoughMoney = true;
				pszItem = "weapon_flashbang";
				iItemPrice = FLASHBANG_PRICE;

			}
			break;
		}
		case MENU_SLOT_ITEM_HEGREN:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_HEGRENADE, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->AmmoInventory(AMMO_HEGRENADE) >= MaxAmmoCarry(WEAPON_HEGRENADE))
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= HEGRENADE_PRICE)
			{
				bEnoughMoney = true;
				pszItem = "weapon_hegrenade";
				iItemPrice = HEGRENADE_PRICE;
			}
			break;
		}
		case MENU_SLOT_ITEM_SMOKEGREN:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_SMOKEGRENADE, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->AmmoInventory(AMMO_SMOKEGRENADE) >= MaxAmmoCarry(WEAPON_SMOKEGRENADE))
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= SMOKEGRENADE_PRICE)
			{
				bEnoughMoney = true;
				pszItem = "weapon_smokegrenade";
				iItemPrice = SMOKEGRENADE_PRICE;
			}
			break;
		}
		case MENU_SLOT_ITEM_NVG:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_NVG, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->m_bHasNightVision)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_One");
				}

				return;
			}

			if (pPlayer->m_iAccount >= NVG_PRICE)
			{
				if (!(pPlayer->m_flDisplayHistory & DHF_NIGHTVISION))
				{
					pPlayer->HintMessage("#Hint_use_nightvision");
					pPlayer->m_flDisplayHistory |= DHF_NIGHTVISION;
				}

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/equip_nvg.wav", VOL_NORM, ATTN_NORM);

				bEnoughMoney = true;
				pPlayer->m_bHasNightVision = true;
				pPlayer->AddAccount(-NVG_PRICE, RT_PLAYER_BOUGHT_SOMETHING);
				pPlayer->SendItemStatus();
			}
			break;
		}
		case MENU_SLOT_ITEM_DEFUSEKIT:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_DEFUSEKIT, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->m_iTeam != CT || !CSGameRules()->m_bMapHasBombTarget)
				return;

			if (pPlayer->m_bHasDefuser)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_One");
				}

				return;
			}

			if (pPlayer->m_iAccount >= DEFUSEKIT_PRICE)
			{
				bEnoughMoney = true;
				pPlayer->m_bHasDefuser = true;

				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pPlayer->pev);
					WRITE_BYTE(STATUSICON_SHOW);
					WRITE_STRING("defuser");
					WRITE_BYTE(0);
					WRITE_BYTE(160);
					WRITE_BYTE(0);
				MESSAGE_END();

				pPlayer->pev->body = 1;
				pPlayer->AddAccount(-DEFUSEKIT_PRICE, RT_PLAYER_BOUGHT_SOMETHING);

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/kevlar.wav", VOL_NORM, ATTN_NORM);
				pPlayer->SendItemStatus();
			}
			break;
		}
		case MENU_SLOT_ITEM_SHIELD:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_SHIELDGUN, ITEM_TYPE_BUYING))
				return;
#endif

			if (!CanBuyThis(pPlayer, WEAPON_SHIELDGUN))
				return;

			if (pPlayer->m_iAccount >= SHIELDGUN_PRICE)
			{
				bEnoughMoney = true;

				pPlayer->DropPrimary();
				pPlayer->GiveShield();
				pPlayer->AddAccount(-SHIELDGUN_PRICE, RT_PLAYER_BOUGHT_SOMETHING);

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);
			}
			break;
		}
	}

	if (!bEnoughMoney)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer);
		}

		return;
	}

	if (pszItem)
	{
		pPlayer->GiveNamedItem(pszItem);
		pPlayer->AddAccount(-iItemPrice, RT_PLAYER_BOUGHT_SOMETHING);
	}

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

LINK_HOOK_CHAIN(CBaseEntity *, BuyWeaponByWeaponID, (CBasePlayer *pPlayer, WeaponIdType weaponID), pPlayer, weaponID)

CBaseEntity *EXT_FUNC __API_HOOK(BuyWeaponByWeaponID)(CBasePlayer *pPlayer, WeaponIdType weaponID)
{
	if (!pPlayer->CanPlayerBuy(true))
		return nullptr;

#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem((ItemID)weaponID, ITEM_TYPE_BUYING))
		return nullptr;
#endif

	if (!CanBuyThis(pPlayer, weaponID))
		return nullptr;

	WeaponInfoStruct *info = GetWeaponInfo(weaponID);
	if (!info || !info->entityName)
		return nullptr;

	if (pPlayer->m_iAccount < info->cost)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer);
		}

		return nullptr;
	}

	if (IsPrimaryWeapon(weaponID))
	{
		pPlayer->DropPrimary();
	}
	else
	{
		pPlayer->DropSecondary();
	}

	auto pEntity = pPlayer->GiveNamedItem(info->entityName);
	pPlayer->AddAccount(-info->cost, RT_PLAYER_BOUGHT_SOMETHING);

#ifdef REGAMEDLL_ADD
	if (refill_bpammo_weapons.value > 1 && info->ammoType >= AMMO_338MAGNUM && info->ammoType <= AMMO_9MM) {
		pPlayer->m_rgAmmo[info->ammoType] = info->maxRounds;
	}
#endif

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return pEntity;
}

LINK_HOOK_VOID_CHAIN(HandleMenu_ChooseAppearance, (CBasePlayer *player, int slot), player, slot)

void EXT_FUNC __API_HOOK(HandleMenu_ChooseAppearance)(CBasePlayer *player, int slot)
{
	int numSkins = g_bIsCzeroGame ? CZ_NUM_SKIN : CS_NUM_SKIN;

	struct
	{
		ModelName model_id;
		char *model_name;
		int model_name_index;

	} appearance;

	Q_memset(&appearance, 0, sizeof(appearance));

	if (player->m_iTeam == TERRORIST)
	{
		if ((slot > numSkins || slot < 1) && (!TheBotProfiles->GetCustomSkin(slot) || !player->IsBot()))
		{
			slot = RANDOM_LONG(1, numSkins);
		}

		switch (slot)
		{
		case 1:
			appearance.model_id = MODEL_TERROR;
			appearance.model_name = "terror";
			break;
		case 2:
			appearance.model_id = MODEL_LEET;
			appearance.model_name = "leet";
			break;
		case 3:
			appearance.model_id = MODEL_ARCTIC;
			appearance.model_name = "arctic";
			break;
		case 4:
			appearance.model_id = MODEL_GUERILLA;
			appearance.model_name = "guerilla";
			break;
		case 5:
			if (g_bIsCzeroGame)
			{
				appearance.model_id = MODEL_MILITIA;
				appearance.model_name = "militia";
				break;
			}
		default:
			if (TheBotProfiles->GetCustomSkinModelname(slot) && player->IsBot())
			{
				appearance.model_name = (char *)TheBotProfiles->GetCustomSkinModelname(slot);
			}
			else
			{
				appearance.model_id = MODEL_TERROR;
				appearance.model_name = "terror";
			}
			break;
		}

		// default T model models/player/terror/terror.mdl
		appearance.model_name_index = 8;

	}
	else if (player->m_iTeam == CT)
	{
		if ((slot > numSkins || slot < 1) && (!TheBotProfiles->GetCustomSkin(slot) || !player->IsBot()))
		{
			slot = RANDOM_LONG(1, numSkins);
		}

		switch (slot)
		{
		case 1:
			appearance.model_id = MODEL_URBAN;
			appearance.model_name = "urban";
			break;
		case 2:
			appearance.model_id = MODEL_GSG9;
			appearance.model_name = "gsg9";
			break;
		case 3:
			appearance.model_id = MODEL_SAS;
			appearance.model_name = "sas";
			break;
		case 4:
			appearance.model_id = MODEL_GIGN;
			appearance.model_name = "gign";
			break;
		case 5:
			if (g_bIsCzeroGame)
			{
				appearance.model_id = MODEL_SPETSNAZ;
				appearance.model_name = "spetsnaz";
				break;
			}
		default:
			if (TheBotProfiles->GetCustomSkinModelname(slot) && player->IsBot())
			{
				appearance.model_name = (char *)TheBotProfiles->GetCustomSkinModelname(slot);
			}
			else
			{
				appearance.model_id = MODEL_URBAN;
				appearance.model_name = "urban";
			}
			break;
		}

		// default CT model models/player/urban/urban.mdl
		appearance.model_name_index = 9;
	}

#ifdef REGAMEDLL_FIXES
	player->ResetMenu();
#else
	player->m_iMenu = Menu_OFF;
#endif

	// Reset the player's state
	switch (player->m_iJoiningState)
	{
	case JOINED:
		CSGameRules()->CheckWinConditions();
		break;

	case PICKINGTEAM:
	{
		player->m_iJoiningState = GETINTOGAME;

		if (CSGameRules()->IsCareer())
		{
			if (!player->IsBot())
			{
				CSGameRules()->CheckWinConditions();
			}
		}
		break;
	}
	}

	player->pev->body = 0;
	player->m_iModelName = appearance.model_id;

	player->SetClientUserInfoModel(GET_INFO_BUFFER(player->edict()), appearance.model_name);
	player->SetNewPlayerModel(sPlayerModelFiles[ appearance.model_name_index ]);

	if (CSGameRules()->m_bMapHasVIPSafetyZone)
	{
		if (!CSGameRules()->m_pVIP && player->m_iTeam == CT)
		{
			player->MakeVIP();
		}
	}
}

LINK_HOOK_CHAIN(BOOL, HandleMenu_ChooseTeam, (CBasePlayer *player, int slot), player, slot)

// returns true if the selection has been handled and the player's menu
// can be closed...false if the menu should be displayed again
BOOL EXT_FUNC __API_HOOK(HandleMenu_ChooseTeam)(CBasePlayer *player, int slot)
{
	// If this player is a VIP, don't allow him to switch teams/appearances unless the following conditions are met :
	// a) There is another TEAM_CT player who is in the queue to be a VIP
	// b) This player is dead

	if (player->m_bIsVIP)
	{
		if (player->pev->deadflag == DEAD_NO)
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Cannot_Switch_From_VIP");
			CLIENT_COMMAND(ENT(player->pev), "slot10\n");

			return TRUE;
		}
		else if (CSGameRules()->IsVIPQueueEmpty())
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Cannot_Switch_From_VIP");
			CLIENT_COMMAND(ENT(player->pev), "slot10\n");

			return TRUE;
		}
	}

	TeamName team = UNASSIGNED;

	switch (slot)
	{
	case MENU_SLOT_TEAM_TERRORIST:
		team = TERRORIST;
		break;
	case MENU_SLOT_TEAM_CT:
		team = CT;
		break;
	case MENU_SLOT_TEAM_VIP:
	{
		if (CSGameRules()->m_bMapHasVIPSafetyZone && player->m_iTeam == CT)
		{
			CSGameRules()->AddToVIPQueue(player);
			CLIENT_COMMAND(ENT(player->pev), "slot10\n");
			return TRUE;
		}
		else
		{
			return FALSE;
		}
		break;
	}
	case MENU_SLOT_TEAM_RANDOM:
	{
		// Attempt to auto-select a team
		team = CSGameRules()->SelectDefaultTeam();
		if (team == UNASSIGNED)
		{
			if (cv_bot_auto_vacate.value > 0.0f && !player->IsBot())
			{
				team = (RANDOM_LONG(0, 1) == 0) ? TERRORIST : CT;

				if (!UTIL_KickBotFromTeam(team))
				{
					// no bots on that team, try the other
					team = (team == CT) ? TERRORIST : CT;

					if (!UTIL_KickBotFromTeam(team))
					{
						// couldn't kick any bots, fail
						team = UNASSIGNED;
					}
				}
			}
		}

		break;
	}
	case MENU_SLOT_TEAM_SPECT:
	{
		// Prevent this is the cvar is set
		// spectator proxy
		if (!allow_spectators.value && !(player->pev->flags & FL_PROXY))
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Cannot_Be_Spectator");
			CLIENT_COMMAND(ENT(player->pev), "slot10\n");

			return FALSE;
		}

		// are we already a spectator?
		if (player->m_iTeam == SPECTATOR)
		{
			return TRUE;
		}

		// Only spectate if we are in the freeze period or dead.
		// This is done here just in case.
		if (g_pGameRules->IsFreezePeriod() || player->pev->deadflag != DEAD_NO)
		{
			if (player->m_iTeam != UNASSIGNED && player->pev->deadflag == DEAD_NO)
			{
				ClientKill(player->edict());

				// add 1 to frags to balance out the 1 subtracted for killing yourself
				player->pev->frags++;
			}

			player->RemoveAllItems(TRUE);
			player->m_bHasC4 = false;

#ifdef REGAMEDLL_FIXES
			if (player->m_iTeam != SPECTATOR)
#endif
			{
				// notify other clients of player joined to team spectator
				UTIL_LogPrintf("\"%s<%i><%s><%s>\" joined team \"SPECTATOR\"\n", STRING(player->pev->netname),
					GETPLAYERUSERID(player->edict()), GETPLAYERAUTHID(player->edict()), GetTeam(player->m_iTeam));
			}

			player->m_iTeam = SPECTATOR;
			player->m_iJoiningState = JOINED;

			// Reset money
#ifdef REGAMEDLL_ADD
			player->AddAccount(0, RT_PLAYER_SPEC_JOIN, false);
#else
			player->m_iAccount = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgMoney, NULL, player->pev);
				WRITE_LONG(player->m_iAccount);
				WRITE_BYTE(0);
			MESSAGE_END();
#endif

#ifndef REGAMEDLL_FIXES
			MESSAGE_BEGIN(MSG_BROADCAST, gmsgScoreInfo);
#else
			MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
#endif
				WRITE_BYTE(ENTINDEX(player->edict()));
				WRITE_SHORT(int(player->pev->frags));
				WRITE_SHORT(player->m_iDeaths);
				WRITE_SHORT(0);
				WRITE_SHORT(0);
			MESSAGE_END();

			player->m_pIntroCamera = NULL;
			player->m_bTeamChanged = true;

			if (TheBots)
			{
				TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, player);
			}

			player->TeamChangeUpdate();

			edict_t *pentSpawnSpot = g_pGameRules->GetPlayerSpawnSpot(player);
			player->StartObserver(pentSpawnSpot->v.origin, pentSpawnSpot->v.angles);

#ifndef REGAMEDLL_FIXES
			// TODO: it was already sent in StartObserver
			MESSAGE_BEGIN(MSG_ALL, gmsgSpectator);
				WRITE_BYTE(ENTINDEX(player->edict()));
				WRITE_BYTE(1);
			MESSAGE_END();
#endif
			// do we have fadetoblack on? (need to fade their screen back in)
			if (fadetoblack.value)
			{
				UTIL_ScreenFade(player, Vector(0, 0, 0), 0.001, 0, 0, FFADE_IN);
			}

			return TRUE;
		}
		else
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Cannot_Be_Spectator");
			CLIENT_COMMAND(ENT(player->pev), "slot10\n");

			return FALSE;
		}

		break;
	}
	default:
		return FALSE;
	}

	// If the code gets this far, the team is not TEAM_UNASSIGNED
	// Player is switching to a new team (It is possible to switch to the
	// same team just to choose a new appearance)
	if (CSGameRules()->TeamFull(team))
	{
		// The specified team is full
		// attempt to kick a bot to make room for this player
		bool madeRoom = false;
		if (cv_bot_auto_vacate.value > 0 && !player->IsBot())
		{
			if (UTIL_KickBotFromTeam(team))
				madeRoom = true;
		}

		if (!madeRoom)
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Terrorists_Full" : "#CTs_Full");
			return FALSE;
		}
	}

	// players are allowed to change to their own team so they can just change their model
	if (CSGameRules()->TeamStacked(team, player->m_iTeam))
	{
		// The specified team is full
		ClientPrint(player->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Too_Many_Terrorists" : "#Too_Many_CTs");
		return FALSE;
	}

	if (team != SPECTATOR && !player->IsBot()
#ifdef REGAMEDLL_ADD
		&& auto_join_team.value != 1.0f
#endif
	)
	{
		int humanTeam = UNASSIGNED;
		if (!Q_stricmp(humans_join_team.string, "CT"))
		{
			humanTeam = CT;
		}
		else if (!Q_stricmp(humans_join_team.string, "T"))
		{
			humanTeam = TERRORIST;
		}

		if (humanTeam != UNASSIGNED && team != humanTeam)
		{
			// TODO: These localization strings are not defined on the client CS 1.6, only for CZero
#ifdef REGAMEDLL_FIXES
			ClientPrint(player->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "Humans can only be CT!" : "Humans can only be terrorists!");
#else
			ClientPrint(player->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Humans_Join_Team_CT" : "#Humans_Join_Team_T");
#endif
			return FALSE;
		}
	}

	// If we already died and changed teams once, deny
	if (player->m_bTeamChanged)
	{
		if (player->pev->deadflag != DEAD_NO)
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Only_1_Team_Change");
			return FALSE;
		}
	}

	if (player->m_iTeam == SPECTATOR && team != SPECTATOR)
	{
		// If they're switching into spectator, setup spectator properties..
		player->m_bNotKilled = true;
		player->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
		player->m_iTeamKills = 0;

		CheckStartMoney();

		// all players start with "mp_startmoney" bucks
#ifdef REGAMEDLL_ADD
		player->AddAccount(startmoney.value, RT_PLAYER_SPEC_JOIN, false);
#else
		player->m_iAccount = int(startmoney.value);
#endif

		player->pev->solid = SOLID_NOT;
		player->pev->movetype = MOVETYPE_NOCLIP;
		player->pev->effects = (EF_NODRAW | EF_NOINTERP);
		player->pev->takedamage = DAMAGE_NO;
		player->pev->deadflag = DEAD_DEAD;
		player->pev->punchangle = g_vecZero;

		player->m_bHasNightVision = false;
		player->m_iHostagesKilled = 0;
		player->m_fDeadTime = 0;
		player->has_disconnected = false;

#ifdef REGAMEDLL_ADD
		player->m_iJoiningState = PICKINGTEAM;
#else
		player->pev->velocity = g_vecZero;
		player->m_iJoiningState = GETINTOGAME;
#endif
		player->SendItemStatus();

#ifndef REGAMEDLL_ADD
		SET_CLIENT_MAXSPEED(ENT(player->pev), 1);
#endif

		SET_MODEL(ENT(player->pev), "models/player.mdl");
	}

#ifdef REGAMEDLL_ADD
	if (!CSGameRules()->ShouldSkipShowMenu())
#endif
	{
		if (!CSGameRules()->IsCareer())
		{
			switch (team)
			{
			case CT:
				if (g_bIsCzeroGame)
					ShowVGUIMenu(player, VGUI_Menu_Class_CT, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6), "#CT_Select");
				else
					ShowVGUIMenu(player, VGUI_Menu_Class_CT, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5), "#CT_Select");
				break;

			case TERRORIST:
				if (g_bIsCzeroGame)
					ShowVGUIMenu(player, VGUI_Menu_Class_T, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6), "#Terrorist_Select");
				else
					ShowVGUIMenu(player, VGUI_Menu_Class_T, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5), "#Terrorist_Select");
				break;
			}
		}

		player->m_iMenu = Menu_ChooseAppearance;

		// Show the appropriate Choose Appearance menu
		// This must come before ClientKill() for CheckWinConditions() to function properly
		if (player->pev->deadflag == DEAD_NO)
		{
			ClientKill(player->edict());
		}
	}

	TeamName oldTeam;
	char *szOldTeam, *szNewTeam;

	// Switch their actual team...
	player->m_bTeamChanged = true;
	oldTeam = player->m_iTeam;
	player->m_iTeam = team;

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, player);
	}

	player->TeamChangeUpdate();

	szOldTeam = GetTeam(oldTeam);
	szNewTeam = GetTeam(team);

	// Notify others that this player has joined a new team
	UTIL_ClientPrintAll(HUD_PRINTNOTIFY, (team == TERRORIST) ? "#Game_join_terrorist" : "#Game_join_ct",
		(STRING(player->pev->netname) && STRING(player->pev->netname)[0] != 0) ? STRING(player->pev->netname) : "<unconnected>");

	UTIL_LogPrintf("\"%s<%i><%s><%s>\" joined team \"%s\"\n", STRING(player->pev->netname), GETPLAYERUSERID(player->edict()), GETPLAYERAUTHID(player->edict()), szOldTeam, szNewTeam);
	return TRUE;
}

void Radio1(CBasePlayer *player, int slot)
{
	if (player->m_flRadioTime >= gpGlobals->time)
		return;

	if (player->m_iRadioMessages <= 0)
		return;

	player->m_iRadioMessages--;
	player->m_flRadioTime = gpGlobals->time + 1.5f;

	switch (slot)
	{
	case 1:
		player->Radio("%!MRAD_COVERME", "#Cover_me");
		break;
	case 2:
		player->Radio("%!MRAD_TAKEPOINT", "#You_take_the_point");
		break;
	case 3:
		player->Radio("%!MRAD_POSITION", "#Hold_this_position");
		break;
	case 4:
		player->Radio("%!MRAD_REGROUP", "#Regroup_team");
		break;
	case 5:
		player->Radio("%!MRAD_FOLLOWME", "#Follow_me");
		break;
	case 6:
		player->Radio("%!MRAD_HITASSIST", "#Taking_fire");
		break;
	}

	if (TheBots)
	{
		TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_1 + slot), player);
	}
}

void Radio2(CBasePlayer *player, int slot)
{
	if (player->m_flRadioTime >= gpGlobals->time)
		return;

	if (player->m_iRadioMessages <= 0)
		return;

	player->m_iRadioMessages--;
	player->m_flRadioTime = gpGlobals->time + 1.5f;

	switch (slot)
	{
	case 1:
		player->Radio("%!MRAD_GO", "#Go_go_go");
		break;
	case 2:
		player->Radio("%!MRAD_FALLBACK", "#Team_fall_back");
		break;
	case 3:
		player->Radio("%!MRAD_STICKTOG", "#Stick_together_team");
		break;
	case 4:
		player->Radio("%!MRAD_GETINPOS", "#Get_in_position_and_wait");
		break;
	case 5:
		player->Radio("%!MRAD_STORMFRONT", "#Storm_the_front");
		break;
	case 6:
		player->Radio("%!MRAD_REPORTIN", "#Report_in_team");
		break;
	}

	if (TheBots)
	{
		TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_2 + slot), player);
	}
}

void Radio3(CBasePlayer *player, int slot)
{
	if (player->m_flRadioTime >= gpGlobals->time)
		return;

	if (player->m_iRadioMessages <= 0)
		return;

	player->m_iRadioMessages--;
	player->m_flRadioTime = gpGlobals->time + 1.5f;

	switch (slot)
	{
	case 1:
		if (RANDOM_LONG(0, 1))
			player->Radio("%!MRAD_AFFIRM", "#Affirmative");
		else
			player->Radio("%!MRAD_ROGER", "#Roger_that");

		break;
	case 2:
		player->Radio("%!MRAD_ENEMYSPOT", "#Enemy_spotted");
		break;
	case 3:
		player->Radio("%!MRAD_BACKUP", "#Need_backup");
		break;
	case 4:
		player->Radio("%!MRAD_CLEAR", "#Sector_clear");
		break;
	case 5:
		player->Radio("%!MRAD_INPOS", "#In_position");
		break;
	case 6:
		player->Radio("%!MRAD_REPRTINGIN", "#Reporting_in");
		break;
	case 7:
		player->Radio("%!MRAD_BLOW", "#Get_out_of_there");
		break;
	case 8:
		player->Radio("%!MRAD_NEGATIVE", "#Negative");
		break;
	case 9:
		player->Radio("%!MRAD_ENEMYDOWN", "#Enemy_down");
		break;
	}

	if (TheBots)
	{
		TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_3 + slot), player);
	}
}

LINK_HOOK_CHAIN(bool, BuyGunAmmo, (CBasePlayer *player, CBasePlayerItem *weapon, bool bBlinkMoney), player, weapon, bBlinkMoney)

bool EXT_FUNC __API_HOOK(BuyGunAmmo)(CBasePlayer *player, CBasePlayerItem *weapon, bool bBlinkMoney)
{
	if (!player->CanPlayerBuy(true))
		return false;

	// Ensure that the weapon uses ammo
	int nAmmo = weapon->PrimaryAmmoIndex();
	if (nAmmo == -1)
		return false;

	// Can only buy if the player does not already have full ammo
	if (player->m_rgAmmo[ nAmmo ] >= weapon->iMaxAmmo1())
		return false;

	WeaponInfoStruct *info = GetWeaponInfo(weapon->m_iId);
	if (!info)
	{
		ALERT(at_console, "Tried to buy ammo for an unrecognized gun\n");
		return false;
	}

	// Purchase the ammo if the player has enough money
	if (player->m_iAccount >= info->clipCost)
	{
		player->GiveNamedItem(info->ammoName);
		player->AddAccount(-info->clipCost, RT_PLAYER_BOUGHT_SOMETHING);
		return true;
	}

	if (bBlinkMoney)
	{
		if (g_bClientPrintEnable)
		{
			// Not enough money.. let the player know
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(player);
		}
	}

	return false;
}

bool BuyAmmo(CBasePlayer *player, int nSlot, bool bBlinkMoney)
{
	if (!player->CanPlayerBuy(true))
		return false;

	if (nSlot < PRIMARY_WEAPON_SLOT || nSlot > PISTOL_SLOT)
		return false;

	// Buy one ammo clip for all weapons in the given slot
	//
	// nSlot == 1 : Primary weapons
	// nSlot == 2 : Secondary weapons

	CBasePlayerItem *pItem = player->m_rgpPlayerItems[ nSlot ];

	if (player->HasShield())
	{
		if (player->m_rgpPlayerItems[ PISTOL_SLOT ])
			pItem = player->m_rgpPlayerItems[ PISTOL_SLOT ];
	}

	if (pItem)
	{
		while (BuyGunAmmo(player, pItem, bBlinkMoney))
		{
			pItem = pItem->m_pNext;

			if (!pItem)
			{
				return true;
			}
		}
	}

	return false;
}

CBaseEntity *EntityFromUserID(int userID)
{
	CBaseEntity *pTempEntity = NULL;

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

		if (pTempPlayer->m_iTeam != UNASSIGNED && userID == GETPLAYERUSERID(pTempEntity->edict()))
		{
			return pTempPlayer;
		}
	}

	return NULL;
}

NOXREF int CountPlayersInServer()
{
	int count = 0;
	CBaseEntity *pTempEntity = NULL;

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

		if (pTempPlayer->m_iTeam != UNASSIGNED)
		{
			count++;
		}
	}

	return count;
}

// Handles the special "buy" alias commands we're creating to accommodate the buy
// scripts players use (now that we've rearranged the buy menus and broken the scripts)
// ** Returns TRUE if we've handled the command **
BOOL HandleBuyAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	// Let them buy it if it's got a weapon data string.
	BOOL bRetVal = FALSE;
	const char *pszFailItem = NULL;

	WeaponIdType weaponID = WEAPON_NONE;
	const char *weaponFailName = BuyAliasToWeaponID(pszCommand, weaponID);

	// Ok, we have weapon info ID.
	if (weaponID != WEAPON_NONE)
	{
		// assasination maps have a specific set of weapons that can be used in them.
		if (CanBuyWeaponByMaptype(pPlayer->m_iTeam, weaponID, CSGameRules()->m_bMapHasVIPSafetyZone == TRUE))
		{
			bRetVal = TRUE;
			BuyWeaponByWeaponID(pPlayer, weaponID);
		}
		else if (weaponFailName)
		{
			bRetVal = TRUE;
			if (g_bClientPrintEnable)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Alias_Not_Avail", weaponFailName);
			}
		}
		else
		{
			bRetVal = TRUE;
			if (g_bClientPrintEnable)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Buy_This");
			}
		}
	}
	else
	{
		// primary ammo
		if (FStrEq(pszCommand, "primammo"))
		{
			bRetVal = TRUE;

			// Buy as much primary ammo as possible
			// Blink money only if player doesn't have enough for the
			// first clip
			if (BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, true))
			{
				while (BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, false))
					;

				if (TheTutor)
				{
					TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
				}
			}
		}
		// secondary ammo
		else if (FStrEq(pszCommand, "secammo"))
		{
			bRetVal = TRUE;

			// Buy as much secondary ammo as possible
			// Blink money only if player doesn't have enough for the
			// first clip
			if (BuyAmmo(pPlayer, PISTOL_SLOT, true))
			{
				while (BuyAmmo(pPlayer, PISTOL_SLOT, false))
					;

				if (TheTutor)
				{
					TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
				}
			}
		}
		// equipment
		else if (FStrEq(pszCommand, "vest"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_VEST);
		}
		else if (FStrEq(pszCommand, "vesthelm"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_VESTHELM);
		}
		else if (FStrEq(pszCommand, "flash"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_FLASHGREN);
		}
		else if (FStrEq(pszCommand, "hegren"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_HEGREN);
		}
		else if (FStrEq(pszCommand, "sgren"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_SMOKEGREN);
		}
		else if (FStrEq(pszCommand, "nvgs"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_NVG);
		}
		else if (FStrEq(pszCommand, "defuser"))
		{
			bRetVal = TRUE;
			if (pPlayer->m_iTeam == CT)
			{
				BuyItem(pPlayer, MENU_SLOT_ITEM_DEFUSEKIT);
			}
			else
			{
				// fail gracefully
				pszFailItem = "#Bomb_Defusal_Kit";
			}
		}
		else if (FStrEq(pszCommand, "shield"))
		{
			bRetVal = TRUE;
			if (pPlayer->m_iTeam == CT)
			{
				BuyItem(pPlayer, MENU_SLOT_ITEM_SHIELD);
			}
			else
			{
				// fail gracefully
				pszFailItem = "#TactShield_Desc";
			}
		}
	}

	if (g_bClientPrintEnable && pszFailItem)
	{
		ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Alias_Not_Avail", pszFailItem);
	}

	pPlayer->BuildRebuyStruct();
	return bRetVal;
}

struct RadioStruct
{
	int slot;
	void (*func)(CBasePlayer *, int);
	const char *alias;

} radioInfo[] = {
	{ 1, Radio1, "coverme" },
	{ 2, Radio1, "takepoint" },
	{ 3, Radio1, "holdpos" },
	{ 4, Radio1, "regroup" },
	{ 5, Radio1, "followme" },
	{ 6, Radio1, "takingfire" },

	{ 1, Radio2, "go" },
	{ 2, Radio2, "fallback" },
	{ 3, Radio2, "sticktog" },
	{ 4, Radio2, "getinpos" },
	{ 5, Radio2, "stormfront" },
	{ 6, Radio2, "report" },

	{ 1, Radio3, "roger" },
	{ 2, Radio3, "enemyspot" },
	{ 3, Radio3, "needbackup" },
	{ 4, Radio3, "sectorclear" },
	{ 5, Radio3, "inposition" },
	{ 6, Radio3, "reportingin" },
	{ 7, Radio3, "getout" },
	{ 8, Radio3, "negative" },
	{ 9, Radio3, "enemydown" },
};

BOOL HandleRadioAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	for (auto& radio : radioInfo)
	{
		if (FStrEq(pszCommand, radio.alias))
		{
			radio.func(pPlayer, radio.slot);
			return TRUE;
		}
	}

	return FALSE;
}

void EXT_FUNC InternalCommand(edict_t *pEntity, const char *pcmd, const char *parg1)
{
	const char *pstr = NULL;
	entvars_t *pev = &pEntity->v;
	CBasePlayer *player = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);

	if (FStrEq(pcmd, "say"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_SAY])
		{
			player->m_flLastCommandTime[CMD_SAY] = gpGlobals->time + 0.3f;
			Host_Say(pEntity, FALSE);
		}
	}
	else if (FStrEq(pcmd, "say_team"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_SAYTEAM])
		{
			player->m_flLastCommandTime[CMD_SAYTEAM] = gpGlobals->time + 0.3f;
			Host_Say(pEntity, TRUE);
		}
	}
	else if (FStrEq(pcmd, "fullupdate"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_FULLUPDATE])
		{
			player->m_flLastCommandTime[CMD_FULLUPDATE] = gpGlobals->time + 0.6f;
			player->ForceClientDllUpdate();
		}
	}
	else if (FStrEq(pcmd, "vote"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_VOTE])
		{
			player->m_flLastCommandTime[CMD_VOTE] = gpGlobals->time + 0.3f;

			if (gpGlobals->time < player->m_flNextVoteTime)
			{
				ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Wait_3_Seconds");
				return;
			}

			player->m_flNextVoteTime = gpGlobals->time + 3;

			if (player->m_iTeam != UNASSIGNED)
			{
				int iVoteID;
				int iVoteFail = 0;
				int iNumArgs = CMD_ARGC_();
				int iVoteLength = Q_strlen(parg1);

				if (iNumArgs != 2 || iVoteLength <= 0 || iVoteLength > 6)
				{
					iVoteFail = 1;
				}

				iVoteID = Q_atoi(parg1);
				if (iVoteID <= 0)
				{
					iVoteFail = 1;
				}

				if (iVoteFail)
				{
					ListPlayers(player);
					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_vote_usage");
					return;
				}

				if (CountTeamPlayers(player->m_iTeam) < 3)
				{
					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Cannot_Vote_With_Less_Than_Three");
					return;
				}

				CBaseEntity *pKickEntity = EntityFromUserID(iVoteID);
				if (pKickEntity)
				{
					CBasePlayer *pKickPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pKickEntity->pev);

					if (pKickPlayer->m_iTeam != player->m_iTeam)
					{
						ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_vote_players_on_your_team");
						return;
					}

					if (pKickPlayer == player)
					{
						ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_vote_not_yourself");
						return;
					}

					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_vote_cast", UTIL_dtos1(iVoteID));
					player->m_iCurrentKickVote = iVoteID;
					ProcessKickVote(player, pKickPlayer);
				}
				else
				{
					ListPlayers(player);
					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_vote_player_not_found", UTIL_dtos1(iVoteID));
				}
			}
		}
	}
	else if (FStrEq(pcmd, "listmaps"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_LISTMAPS])
		{
			player->m_flLastCommandTime[CMD_LISTMAPS] = gpGlobals->time + 0.3f;
			CSGameRules()->DisplayMaps(player, 0);
		}
	}
	else if (FStrEq(pcmd, "votemap"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_VOTEMAP])
		{
			player->m_flLastCommandTime[CMD_VOTEMAP] = gpGlobals->time + 0.3f;

			if (gpGlobals->time < player->m_flNextVoteTime)
			{
				ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Wait_3_Seconds");
				return;
			}

			player->m_flNextVoteTime = gpGlobals->time + 3;

			if (player->m_iTeam != UNASSIGNED)
			{
				if (gpGlobals->time < 180)
				{
					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Cannot_Vote_Map");
					return;
				}

				int iFailed = 0;
				int iNumArgs = CMD_ARGC_();
				int iVoteLength = Q_strlen(parg1);

				if (iNumArgs != 2 || iVoteLength > 5)
				{
					iFailed = 1;
				}

				int iVoteID = Q_atoi(parg1);
				if (iVoteID < 1 || iVoteID > MAX_VOTE_MAPS)
				{
					iFailed = 1;
				}

				if (iVoteID > GetMapCount())
				{
					iFailed = 1;
				}

				if (iFailed)
				{
					CSGameRules()->DisplayMaps(player, 0);
					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_votemap_usage");
					return;
				}

				if (CountTeamPlayers(player->m_iTeam) < 2)
				{
					ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Cannot_Vote_Need_More_People");
					return;
				}

				if (player->m_iMapVote)
				{
					if (--CSGameRules()->m_iMapVotes[player->m_iMapVote] < 0)
					{
						CSGameRules()->m_iMapVotes[player->m_iMapVote] = 0;
					}
				}

				ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_voted_for_map", UTIL_dtos1(iVoteID));
				player->m_iMapVote = iVoteID;
				CSGameRules()->ProcessMapVote(player, iVoteID);
			}
		}
	}
	else if (FStrEq(pcmd, "timeleft"))
	{
		if (gpGlobals->time > player->m_iTimeCheckAllowed)
		{
			player->m_iTimeCheckAllowed = int(gpGlobals->time + 1.0f);

			if (!timelimit.value)
			{
				ClientPrint(player->pev, HUD_PRINTTALK, "#Game_no_timelimit");
				return;
			}

			int timeRemaining = (int)CSGameRules()->GetTimeLeft();
			if (timeRemaining < 0)
				timeRemaining = 0;

			int iMinutes = timeRemaining / 60;
			int iSeconds = timeRemaining % 60;

			char secs[5];
			char *temp = UTIL_dtos2(iSeconds);

			if (iSeconds >= 10)
			{
				secs[0] = temp[0];
				secs[1] = temp[1];
				secs[2] = '\0';
			}
			else
			{
				secs[0] = '0';
				secs[1] = temp[0];
				secs[2] = '\0';
			}

			ClientPrint(player->pev, HUD_PRINTTALK, "#Game_timelimit", UTIL_dtos1(iMinutes), secs);
		}
	}
	else if (FStrEq(pcmd, "listplayers"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[CMD_LISTPLAYERS])
		{
			player->m_flLastCommandTime[CMD_LISTPLAYERS] = gpGlobals->time + 0.3f;
			ListPlayers(player);
		}
	}
	else if (FStrEq(pcmd, "client_buy_open"))
	{
		if (player->m_iMenu == Menu_OFF)
		{
			player->m_iMenu = Menu_ClientBuy;
		}

		if (player->m_signals.GetState() & SIGNAL_BUY)
		{
			if (TheTutor)
			{
				TheTutor->OnEvent(EVENT_TUTOR_BUY_MENU_OPENNED);
			}
		}
		else
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, NULL, player->pev);
			MESSAGE_END();
		}
	}
	else if (FStrEq(pcmd, "client_buy_close"))
	{
		if (player->m_iMenu == Menu_ClientBuy)
		{
			player->m_iMenu = Menu_OFF;
		}
	}
	else if (FStrEq(pcmd, "menuselect"))
	{
		int slot = Q_atoi(parg1);
		if (player->m_iJoiningState == JOINED || (player->m_iMenu != Menu_ChooseAppearance && player->m_iMenu != Menu_ChooseTeam))
		{
			if (slot == 10)
			{
				player->m_iMenu = Menu_OFF;
			}
		}

#ifdef REGAMEDLL_ADD
		auto canOpenOldMenu = [player]()-> bool
		{
			if (!player->m_bVGUIMenus || player->CSPlayer()->m_bForceShowMenu) {
				player->CSPlayer()->m_bForceShowMenu = false;
				return true;
			}

			return false;
		};
#else
		auto canOpenOldMenu = [player]()-> bool {
			return player->m_bVGUIMenus == false;
		};
#endif

		switch (player->m_iMenu)
		{
			case Menu_OFF:
				break;

			case Menu_ChooseTeam:
			{
				if (canOpenOldMenu() && !HandleMenu_ChooseTeam(player, slot))
				{
					player->m_iMenu = Menu_ChooseTeam;
					if (player->m_iJoiningState == JOINED)
						ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
					else
						ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5), "#Team_Select");
				}
				break;
			}
			case Menu_IGChooseTeam:
			{
				if (canOpenOldMenu()) {
					HandleMenu_ChooseTeam(player, slot);
				}
				break;
			}
			case Menu_ChooseAppearance:
			{
				if (canOpenOldMenu()) {
					HandleMenu_ChooseAppearance(player, slot);
				}
				break;
			}
			case Menu_Buy:
			{
				if (canOpenOldMenu())
				{
					switch (slot)
					{
						case VGUI_MenuSlot_Buy_Pistol:
						{
							player->m_iMenu = Menu_BuyPistol;
							if (player->m_iTeam == CT)
								ShowVGUIMenu(player, VGUI_Menu_Buy_Pistol, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#CT_BuyPistol");
							else
								ShowVGUIMenu(player, VGUI_Menu_Buy_Pistol, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#T_BuyPistol");
							break;
						}
						case VGUI_MenuSlot_Buy_ShotGun:
						{
							player->m_iMenu = Menu_BuyShotgun;
							if (CSGameRules()->m_bMapHasVIPSafetyZone && player->m_iTeam == TERRORIST)
								ShowVGUIMenu(player, VGUI_Menu_Buy_ShotGun, MENU_KEY_0, "#AS_BuyShotgun");
							else
								ShowVGUIMenu(player, VGUI_Menu_Buy_ShotGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_0), "#BuyShotgun");
							break;
						}
						case VGUI_MenuSlot_Buy_SubMachineGun:
						{
							player->m_iMenu = Menu_BuySubMachineGun;
							if (CSGameRules()->m_bMapHasVIPSafetyZone)
							{
								if (player->m_iTeam == CT)
									ShowVGUIMenu(player, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_0), "#AS_CT_BuySubMachineGun");
								else
									ShowVGUIMenu(player, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_3 | MENU_KEY_0), "#AS_T_BuySubMachineGun");
							}
							else
							{
								if (player->m_iTeam == CT)
									ShowVGUIMenu(player, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_0), "#CT_BuySubMachineGun");
								else
									ShowVGUIMenu(player, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_0), "#T_BuySubMachineGun");
							}
							break;
						}
						case VGUI_MenuSlot_Buy_Rifle:
						{
							player->m_iMenu = Menu_BuyRifle;
							if (CSGameRules()->m_bMapHasVIPSafetyZone)
							{
								if (player->m_iTeam == CT)
									ShowVGUIMenu(player, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#AS_CT_BuyRifle");
								else
									ShowVGUIMenu(player, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#AS_T_BuyRifle");
							}
							else
							{
								if (player->m_iTeam == CT)
									ShowVGUIMenu(player, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#CT_BuyRifle");
								else
									ShowVGUIMenu(player, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#T_BuyRifle");
							}
							break;
						}
						case VGUI_MenuSlot_Buy_MachineGun:
						{
							player->m_iMenu = Menu_BuyMachineGun;
							if (CSGameRules()->m_bMapHasVIPSafetyZone && player->m_iTeam == TERRORIST)
								ShowVGUIMenu(player, VGUI_Menu_Buy_MachineGun, MENU_KEY_0, "#AS_T_BuyMachineGun");
							else
								ShowVGUIMenu(player, VGUI_Menu_Buy_MachineGun, (MENU_KEY_1 | MENU_KEY_0), "#BuyMachineGun");
							break;
						}
						case VGUI_MenuSlot_Buy_PrimAmmo:
						{
							if (player->m_signals.GetState() & SIGNAL_BUY)
							{
								if (BuyAmmo(player, PRIMARY_WEAPON_SLOT, true))
								{
									while (BuyAmmo(player, PRIMARY_WEAPON_SLOT, false))
										;

									if (TheTutor)
									{
										TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, player);
									}
								}

								player->BuildRebuyStruct();
							}
							break;
						}
						case VGUI_MenuSlot_Buy_SecAmmo:
						{
							if (player->m_signals.GetState() & SIGNAL_BUY)
							{
								if (BuyAmmo(player, PISTOL_SLOT, true))
								{
									while (BuyAmmo(player, PISTOL_SLOT, false))
										;

									if (TheTutor)
									{
										TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, player);
									}
								}

								player->BuildRebuyStruct();
							}
							break;
						}
						case VGUI_MenuSlot_Buy_Item:
						{
							if (player->m_signals.GetState() & SIGNAL_BUY)
							{
								player->m_iMenu = Menu_BuyItem;
								if (CSGameRules()->m_bMapHasBombTarget)
								{
									if (player->m_iTeam == CT)
										ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_0), "#DCT_BuyItem");
									else
										ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#DT_BuyItem");
								}
								else
								{
									if (player->m_iTeam == CT)
										ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_8 | MENU_KEY_0), "#CT_BuyItem");
									else
										ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#T_BuyItem");
								}
							}
							break;
						}
					}
				}
				break;
			}
			case Menu_BuyPistol:
			{
				if (canOpenOldMenu()) {
					BuyPistol(player, slot);
				}
				break;
			}
			case Menu_BuyShotgun:
			{
				if (canOpenOldMenu()) {
					BuyShotgun(player, slot);
				}
				break;
			}
			case Menu_BuySubMachineGun:
			{
				if (canOpenOldMenu()) {
					BuySubMachineGun(player, slot);
				}
				break;
			}
			case Menu_BuyRifle:
			{
				if (canOpenOldMenu()) {
					BuyRifle(player, slot);
				}
				break;
			}
			case Menu_BuyMachineGun:
			{
				if (canOpenOldMenu()) {
					BuyMachineGun(player, slot);
				}
				break;
			}
			case Menu_BuyItem:
			{
				if (canOpenOldMenu()) {
					BuyItem(player, slot);
				}
				break;
			}
			case Menu_Radio1:
			{
				Radio1(player, slot);
				break;
			}
			case Menu_Radio2:
			{
				Radio2(player, slot);
				break;
			}
			case Menu_Radio3:
			{
				Radio3(player, slot);
				break;
			}
			default:
				ALERT(at_console, "ClientCommand(): Invalid menu selected\n");
				break;
		}
	}
	else if (FStrEq(pcmd, "chooseteam"))
	{
		if (player->m_iMenu == Menu_ChooseAppearance)
			return;

		if (player->m_bTeamChanged)
		{
			if (player->pev->deadflag != DEAD_NO)
			{
				ClientPrint(player->pev, HUD_PRINTCENTER, "#Only_1_Team_Change");
				return;
			}
		}

		if (!CSGameRules()->IsCareer())
		{
			player->m_iMenu = Menu_ChooseTeam;
			if (CSGameRules()->m_bMapHasVIPSafetyZone && player->m_iJoiningState == JOINED && player->m_iTeam == CT)
			{
				if (CSGameRules()->IsFreezePeriod() || player->pev->deadflag != DEAD_NO)
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#IG_VIP_Team_Select_Spect");
				else
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_5 | MENU_KEY_0), "#IG_VIP_Team_Select");
			}
			else
			{
				if (CSGameRules()->IsFreezePeriod() || player->pev->deadflag != DEAD_NO)
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#IG_Team_Select_Spect");
				else
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
			}
		}
	}
	else if (FStrEq(pcmd, "showbriefing"))
	{
		if (player->m_iMenu == Menu_OFF)
		{
			if (g_szMapBriefingText[0] != '\0')
			{
				if (player->m_iTeam != UNASSIGNED && !(player->m_afPhysicsFlags & PFLAG_OBSERVER))
				{
					player->MenuPrint(g_szMapBriefingText);
					player->m_bMissionBriefing = true;
				}
			}
		}
	}
	else if (FStrEq(pcmd, "ignoremsg"))
	{
		if (player->m_iIgnoreGlobalChat == IGNOREMSG_NONE)
		{
			player->m_iIgnoreGlobalChat = IGNOREMSG_ENEMY;
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Ignore_Broadcast_Messages");
		}
		else if (player->m_iIgnoreGlobalChat == IGNOREMSG_ENEMY)
		{
			player->m_iIgnoreGlobalChat = IGNOREMSG_TEAM;
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Ignore_Broadcast_Team_Messages");
		}
		else if (player->m_iIgnoreGlobalChat == IGNOREMSG_TEAM)
		{
			player->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Accept_All_Messages");
		}
	}
	else if (FStrEq(pcmd, "ignorerad"))
	{
		player->m_bIgnoreRadio = !player->m_bIgnoreRadio;
		ClientPrint(player->pev, HUD_PRINTCENTER, player->m_bIgnoreRadio ? "#Ignore_Radio" : "#Accept_Radio");
	}
	else if (FStrEq(pcmd, "become_vip"))
	{
		if (player->m_iJoiningState != JOINED || player->m_iTeam != CT)
		{
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Command_Not_Available");
			return;
		}

		CSGameRules()->AddToVIPQueue(player);
	}
	else if (FStrEq(pcmd, "spectate") && (player->pev->flags & FL_PROXY)) // always allow proxies to become a spectator
	{
		// clients wants to become a spectator
		HandleMenu_ChooseTeam(player, MENU_SLOT_TEAM_SPECT);
	}
	else if (FStrEq(pcmd, "specmode"))
	{
		// new spectator mode
		int mode = Q_atoi(parg1);
		if (player->IsObserver() && player->CanSwitchObserverModes())
			player->Observer_SetMode(mode);
		else
			player->m_iObserverLastMode = mode;

		if (mode == OBS_CHASE_FREE)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgADStop, NULL, player->pev);
			MESSAGE_END();
		}
	}
	else if (FStrEq(pcmd, "spec_set_ad"))
	{
		float val = Q_atof(parg1);
		player->SetObserverAutoDirector(val > 0.0f);
	}
	else if (FStrEq(pcmd, "follownext"))
	{
		// follow next player
		int arg = Q_atoi(parg1);
		if (player->IsObserver() && player->CanSwitchObserverModes())
		{
			player->Observer_FindNextPlayer(arg != 0);
		}
	}
	else if (FStrEq(pcmd, "follow"))
	{
		if (player->IsObserver() && player->CanSwitchObserverModes())
		{
			player->Observer_FindNextPlayer(false, parg1);
		}
	}
	else
	{
		if (g_pGameRules->ClientCommand_DeadOrAlive(GetClassPtr<CCSPlayer>((CBasePlayer *)pev), pcmd))
			return;

		if (TheBots)
		{
			if (TheBots->ClientCommand(GetClassPtr<CCSPlayer>((CBasePlayer *)pev), pcmd))
				return;
		}

		if (FStrEq(pcmd, "mp_debug"))
		{
			UTIL_SetDprintfFlags(parg1);
		}
		else if (FStrEq(pcmd, "jointeam"))
		{
			if (player->m_iMenu == Menu_ChooseAppearance)
			{
				ClientPrint(player->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}

			int slot = Q_atoi(parg1);
			if (HandleMenu_ChooseTeam(player, slot))
			{
				if (slot == MENU_SLOT_TEAM_VIP || slot == MENU_SLOT_TEAM_SPECT || player->m_bIsVIP)
				{
#ifdef REGAMEDLL_FIXES
					player->ResetMenu();
#else
					player->m_iMenu = Menu_OFF;
#endif
				}
				else
					player->m_iMenu = Menu_ChooseAppearance;
			}
			else
			{
				player->m_iMenu = Menu_ChooseTeam;
				if (player->m_iJoiningState == JOINED)
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
				else
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5), "#Team_Select");
			}
		}
		else if (FStrEq(pcmd, "joinclass"))
		{
			int slot = Q_atoi(parg1);
			if (player->m_iMenu != Menu_ChooseAppearance)
			{
				ClientPrint(player->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}

			HandleMenu_ChooseAppearance(player, slot);
		}
		else if (player->pev->deadflag == DEAD_NO)
		{
			if (FStrEq(pcmd, "nightvision"))
			{
				if (gpGlobals->time >= player->m_flLastCommandTime[CMD_NIGHTVISION])
				{
					player->m_flLastCommandTime[CMD_NIGHTVISION] = gpGlobals->time + 0.3f;

					if (!player->m_bHasNightVision)
						return;

					if (player->m_bNightVisionOn)
					{
						EMIT_SOUND(ENT(player->pev), CHAN_ITEM, "items/nvg_off.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

						MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, player->pev);
							WRITE_BYTE(0); // disable nightvision
						MESSAGE_END();

						player->m_bNightVisionOn = false;

						for (int i = 1; i <= gpGlobals->maxClients; ++i)
						{
							CBasePlayer *pObserver = UTIL_PlayerByIndex(i);
							if (pObserver && pObserver->IsObservingPlayer(player))
							{
								EMIT_SOUND(ENT(pObserver->pev), CHAN_ITEM, "items/nvg_off.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

								MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, pObserver->pev);
									WRITE_BYTE(0); // disable nightvision
								MESSAGE_END();

								pObserver->m_bNightVisionOn = false;
							}
						}
					}
					else
					{
						EMIT_SOUND(ENT(player->pev), CHAN_ITEM, "items/nvg_on.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

						MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, player->pev);
							WRITE_BYTE(1); // enable nightvision
						MESSAGE_END();

						player->m_bNightVisionOn = true;

						for (int i = 1; i <= gpGlobals->maxClients; ++i)
						{
							CBasePlayer *pObserver = UTIL_PlayerByIndex(i);
							if (pObserver && pObserver->IsObservingPlayer(player))
							{
								EMIT_SOUND(ENT(pObserver->pev), CHAN_ITEM, "items/nvg_on.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

								MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, pObserver->pev);
									WRITE_BYTE(1);  // enable nightvision
								MESSAGE_END();

								pObserver->m_bNightVisionOn = true;
							}
						}
					}
				}
			}
			else if (FStrEq(pcmd, "radio1"))
			{
				ShowMenu(player, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), -1, FALSE, "#RadioA");
				player->m_iMenu = Menu_Radio1;
			}
			else if (FStrEq(pcmd, "radio2"))
			{
				ShowMenu(player, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), -1, FALSE, "#RadioB");
				player->m_iMenu = Menu_Radio2;
				return;
			}
			else if (FStrEq(pcmd, "radio3"))
			{
				ShowMenu(player, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_9 | MENU_KEY_0), -1, FALSE, "#RadioC");
				player->m_iMenu = Menu_Radio3;
			}
			else if (FStrEq(pcmd, "drop"))
			{
				// player is dropping an item.
				if (player->HasShield())
				{
					if (player->m_pActiveItem && player->m_pActiveItem->m_iId == WEAPON_C4)
					{
						player->DropPlayerItem("weapon_c4");
					}
					else
						player->DropShield();
				}
				else
					player->DropPlayerItem(parg1);
			}
			else if (FStrEq(pcmd, "fov"))
			{
#if 0
				if (g_flWeaponCheat && CMD_ARGC() > 1)
					GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->m_iFOV = Q_atoi(CMD_ARGV(1));
				else
					CLIENT_PRINTF(pEntity, print_console, UTIL_VarArgs("\"fov\" is \"%d\"\n", int(GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->m_iFOV)));
#endif
			}
			else if (FStrEq(pcmd, "use"))
			{
				GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->SelectItem(parg1);
			}
			else if (((pstr = Q_strstr(pcmd, "weapon_"))) && (pstr == pcmd))
			{
				GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->SelectItem(pcmd);
			}
			else if (FStrEq(pcmd, "lastinv"))
			{
				GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->SelectLastItem();
			}
			else if (FStrEq(pcmd, "buyammo1"))
			{
				if (player->m_signals.GetState() & SIGNAL_BUY)
				{
					BuyAmmo(player, PRIMARY_WEAPON_SLOT, true);
					player->BuildRebuyStruct();

					if (TheTutor)
					{
						TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, player);
					}
				}
			}
			else if (FStrEq(pcmd, "buyammo2"))
			{
				if (player->m_signals.GetState() & SIGNAL_BUY)
				{
					BuyAmmo(player, PISTOL_SLOT, true);
					player->BuildRebuyStruct();

					if (TheTutor)
					{
						TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, player);
					}
				}
			}
			else if (FStrEq(pcmd, "buyequip"))
			{
				if (player->m_signals.GetState() & SIGNAL_BUY)
				{
					if (CSGameRules()->m_bMapHasBombTarget)
					{
						if (player->m_iTeam == CT)
							ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_0), "#DCT_BuyItem");
						else
							ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#DT_BuyItem");
					}
					else
					{
						if (player->m_iTeam == CT)
							ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_8 | MENU_KEY_0), "#CT_BuyItem");
						else
							ShowVGUIMenu(player, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#T_BuyItem");
					}

					player->m_iMenu = Menu_BuyItem;
				}
			}
			else if (FStrEq(pcmd, "buy"))
			{
				if (player->m_signals.GetState() & SIGNAL_BUY)
				{
					ShowVGUIMenu(player, VGUI_Menu_Buy, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_0), "#Buy");
					player->m_iMenu = Menu_Buy;

					if (TheBots)
					{
						TheBots->OnEvent(EVENT_TUTOR_BUY_MENU_OPENNED);
					}
				}
			}
			else if (FStrEq(pcmd, "cl_setautobuy"))
			{
				player->ClearAutoBuyData();

				for (int i = 1; i < CMD_ARGC_(); ++i)
				{
					player->AddAutoBuyData(CMD_ARGV_(i));
				}

				bool oldval = g_bClientPrintEnable;
				g_bClientPrintEnable = false;
				player->AutoBuy();
				g_bClientPrintEnable = oldval;
			}
			else if (FStrEq(pcmd, "cl_setrebuy"))
			{
				if (CMD_ARGC_() == 2)
				{
					player->InitRebuyData(parg1);

					bool oldval = g_bClientPrintEnable;
					g_bClientPrintEnable = false;
					player->Rebuy();
					g_bClientPrintEnable = oldval;
				}
			}
			else if (FStrEq(pcmd, "cl_autobuy"))
			{
				if (player->m_signals.GetState() & SIGNAL_BUY)
				{
					bool oldval = g_bClientPrintEnable;
					g_bClientPrintEnable = false;
					player->AutoBuy();
					g_bClientPrintEnable = oldval;
				}
			}
			else if (FStrEq(pcmd, "cl_rebuy"))
			{
				if (player->m_signals.GetState() & SIGNAL_BUY)
				{
					bool oldval = g_bClientPrintEnable;
					g_bClientPrintEnable = false;
					player->Rebuy();
					g_bClientPrintEnable = oldval;
				}
			}
			else if (FStrEq(pcmd, "smartradio"))
			{
				player->SmartRadio();
			}
			else
			{
				if (HandleBuyAliasCommands(player, pcmd))
					return;

				if (HandleRadioAliasCommands(player, pcmd))
					return;

				if (!g_pGameRules->ClientCommand(GetClassPtr<CCSPlayer>((CBasePlayer *)pev), pcmd))
				{
					// tell the user they entered an unknown command
					char command[128];

					// check the length of the command (prevents crash)
					// max total length is 192 ...and we're adding a string below ("Unknown command: %s\n")
					Q_strncpy(command, pcmd, sizeof(command) - 1);
					command[sizeof(command) - 1] = '\0';

					// tell the user they entered an unknown command
					ClientPrint(&pEntity->v, HUD_PRINTCONSOLE, "#Game_unknown_command", command);
				}
			}
		}
	}
}

// Use CMD_ARGV, CMD_ARGV, and CMD_ARGC to get pointers the character string command.
void EXT_FUNC ClientCommand_(edict_t *pEntity)
{
	// Is the client spawned yet?
	if (!pEntity->pvPrivateData)
		return;

	static char command[128] = "";
	Q_strncpy(command, CMD_ARGV_(0), sizeof command - 1);
	command[sizeof command - 1] = '\0';

	g_ReGameHookchains.m_InternalCommand.callChain(InternalCommand, pEntity, command, CMD_ARGV_(1));
}

// called after the player changes userinfo - gives dll a chance to modify it before it gets sent into the rest of the engine.
void EXT_FUNC ClientUserInfoChanged(edict_t *pEntity, char *infobuffer)
{
	// Is the client spawned yet?
	if (!pEntity->pvPrivateData)
		return;

	CBasePlayer *pPlayer = CBasePlayer::Instance(pEntity);
	char *szBufferName = GET_KEY_VALUE(infobuffer, "name");

	// msg everyone if someone changes their name, and it isn't the first time (changing no name to current name)
	if (pEntity->v.netname && STRING(pEntity->v.netname)[0] != '\0' && !FStrEq(STRING(pEntity->v.netname), szBufferName))
	{
		char szName[32];
		Q_snprintf(szName, sizeof(szName), "%s", szBufferName);

		// First parse the name and remove any %'s
		for (char *pPct = szName; pPct && *pPct != '\0'; pPct++)
		{
			// Replace it with a space
			if (*pPct == '%' || *pPct == '&')
				*pPct = ' ';
		}

		if (szName[0] == '#')
			szName[0] = '*';

		// Can set it a new name?
		if (!pPlayer->SetClientUserInfoName(infobuffer, szName))
		{
			// so to back old name into buffer
			SET_CLIENT_KEY_VALUE(pPlayer->entindex(), infobuffer, "name", (char *)STRING(pPlayer->pev->netname));
		}
	}

	// was already checking on pvPrivateData
#ifndef REGAMEDLL_FIXES
	g_pGameRules->ClientUserInfoChanged(GetClassPtr<CCSPlayer>((CBasePlayer *)&pEntity->v), infobuffer);
#else
	g_pGameRules->ClientUserInfoChanged(pPlayer, infobuffer);
#endif
}

void EXT_FUNC ServerDeactivate()
{
	// It's possible that the engine will call this function more times than is necessary
	// Therefore, only run it one time for each call to ServerActivate
	if (!g_bServerActive)
		return;

	g_bServerActive = false;

	// Peform any shutdown operations here...
	g_pGameRules->ServerDeactivate();
	CLocalNav::Reset();

	if (TheBots)
	{
		TheBots->ServerDeactivate();
	}

	if (g_pHostages)
	{
		g_pHostages->ServerDeactivate();
	}

	WeaponInfoReset();
}

void EXT_FUNC ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	int i;
	CBaseEntity *pClass;

	// Every call to ServerActivate should be matched by a call to ServerDeactivate
	g_bServerActive = true;
	EmptyEntityHashTable();

	// Clients have not been initialized yet
	for (i = 0; i < edictCount; ++i)
	{
		edict_t *pEdict = &pEdictList[i];

		if (pEdict->free)
			continue;

		// Clients aren't necessarily initialized until ClientPutInServer()
		if (i < clientMax || !pEdict->pvPrivateData)
			continue;

		pClass = CBaseEntity::Instance(pEdict);

		// Activate this entity if it's got a class & isn't dormant
		if (pClass && !(pClass->pev->flags & FL_DORMANT))
		{
			AddEntityHashValue(&pEdict->v, STRING(pEdict->v.classname), CLASSNAME);
			pClass->Activate();
		}
		else
			ALERT(at_console, "Can't instance %s\n", STRING(pEdict->v.classname));
	}

	// Link user messages here to make sure first client can get them...
	LinkUserMessages();
	WriteSigonMessages();

	if (g_pGameRules)
	{
		g_pGameRules->CheckMapConditions();
	}

	if (TheBots)
	{
		TheBots->ServerActivate();
	}

	if (g_pHostages)
	{
		g_pHostages->ServerActivate();
	}

#ifdef REGAMEDLL_ADD
	CSGameRules()->ServerActivate();
#endif

}

void EXT_FUNC PlayerPreThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->PreThink();
	}
}

void EXT_FUNC PlayerPostThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->PostThink();
	}
}

void EXT_FUNC ParmsNewLevel()
{
	;
}

void EXT_FUNC ParmsChangeLevel()
{
	// retrieve the pointer to the save data
	SAVERESTOREDATA *pSaveData = (SAVERESTOREDATA *)gpGlobals->pSaveData;

	if (pSaveData)
	{
		pSaveData->connectionCount = BuildChangeList(pSaveData->levelList, MAX_LEVEL_CONNECTIONS);
	}
}

void EXT_FUNC StartFrame()
{
	if (g_pGameRules)
	{
		g_pGameRules->Think();
		if (g_pGameRules->IsGameOver())
			return;
	}

	CLocalNav::Think();

	static cvar_t *skill = NULL;
	if (!skill)
	{
		skill = CVAR_GET_POINTER("skill");
	}

	gpGlobals->teamplay = 1.0f;

	if (skill)
		g_iSkillLevel = int(skill->value);

	else
		g_iSkillLevel = 0;

	if (TheBots) {
		TheBots->StartFrame();
	}

	if (TheTutor) {
		TheTutor->StartFrame(gpGlobals->time);
	}

#ifndef REGAMEDLL_FIXES
	// it is noxref
	++g_ulFrameCount;
#endif
}

void ClientPrecache()
{
	int i;

	PRECACHE_SOUND("weapons/dryfire_pistol.wav");
	PRECACHE_SOUND("weapons/dryfire_rifle.wav");
	PRECACHE_SOUND("player/pl_shot1.wav");
	PRECACHE_SOUND("player/pl_die1.wav");
	PRECACHE_SOUND("player/headshot1.wav");
	PRECACHE_SOUND("player/headshot2.wav");
	PRECACHE_SOUND("player/headshot3.wav");
	PRECACHE_SOUND("player/bhit_flesh-1.wav");
	PRECACHE_SOUND("player/bhit_flesh-2.wav");
	PRECACHE_SOUND("player/bhit_flesh-3.wav");
	PRECACHE_SOUND("player/bhit_kevlar-1.wav");
	PRECACHE_SOUND("player/bhit_helmet-1.wav");
	PRECACHE_SOUND("player/die1.wav");
	PRECACHE_SOUND("player/die2.wav");
	PRECACHE_SOUND("player/die3.wav");
	PRECACHE_SOUND("player/death6.wav");
	PRECACHE_SOUND("radio/locknload.wav");
	PRECACHE_SOUND("radio/letsgo.wav");
	PRECACHE_SOUND("radio/moveout.wav");
	PRECACHE_SOUND("radio/com_go.wav");
	PRECACHE_SOUND("radio/rescued.wav");
	PRECACHE_SOUND("radio/rounddraw.wav");
	PRECACHE_SOUND("items/kevlar.wav");
	PRECACHE_SOUND("items/ammopickup2.wav");
	PRECACHE_SOUND("items/nvg_on.wav");
	PRECACHE_SOUND("items/nvg_off.wav");
	PRECACHE_SOUND("items/equip_nvg.wav");
	PRECACHE_SOUND("weapons/c4_beep1.wav");
	PRECACHE_SOUND("weapons/c4_beep2.wav");
	PRECACHE_SOUND("weapons/c4_beep3.wav");
	PRECACHE_SOUND("weapons/c4_beep4.wav");
	PRECACHE_SOUND("weapons/c4_beep5.wav");
	PRECACHE_SOUND("weapons/c4_explode1.wav");
	PRECACHE_SOUND("weapons/c4_plant.wav");
	PRECACHE_SOUND("weapons/c4_disarm.wav");
	PRECACHE_SOUND("weapons/c4_disarmed.wav");
	PRECACHE_SOUND("weapons/explode3.wav");
	PRECACHE_SOUND("weapons/explode4.wav");
	PRECACHE_SOUND("weapons/explode5.wav");
	PRECACHE_SOUND("player/sprayer.wav");
	PRECACHE_SOUND("player/pl_fallpain2.wav");
	PRECACHE_SOUND("player/pl_fallpain3.wav");
	PRECACHE_SOUND("player/pl_snow1.wav");
	PRECACHE_SOUND("player/pl_snow2.wav");
	PRECACHE_SOUND("player/pl_snow3.wav");
	PRECACHE_SOUND("player/pl_snow4.wav");
	PRECACHE_SOUND("player/pl_snow5.wav");
	PRECACHE_SOUND("player/pl_snow6.wav");
	PRECACHE_SOUND("player/pl_step1.wav");
	PRECACHE_SOUND("player/pl_step2.wav");
	PRECACHE_SOUND("player/pl_step3.wav");
	PRECACHE_SOUND("player/pl_step4.wav");
	PRECACHE_SOUND("common/npc_step1.wav");
	PRECACHE_SOUND("common/npc_step2.wav");
	PRECACHE_SOUND("common/npc_step3.wav");
	PRECACHE_SOUND("common/npc_step4.wav");
	PRECACHE_SOUND("player/pl_metal1.wav");
	PRECACHE_SOUND("player/pl_metal2.wav");
	PRECACHE_SOUND("player/pl_metal3.wav");
	PRECACHE_SOUND("player/pl_metal4.wav");
	PRECACHE_SOUND("player/pl_dirt1.wav");
	PRECACHE_SOUND("player/pl_dirt2.wav");
	PRECACHE_SOUND("player/pl_dirt3.wav");
	PRECACHE_SOUND("player/pl_dirt4.wav");
	PRECACHE_SOUND("player/pl_duct1.wav");
	PRECACHE_SOUND("player/pl_duct2.wav");
	PRECACHE_SOUND("player/pl_duct3.wav");
	PRECACHE_SOUND("player/pl_duct4.wav");
	PRECACHE_SOUND("player/pl_grate1.wav");
	PRECACHE_SOUND("player/pl_grate2.wav");
	PRECACHE_SOUND("player/pl_grate3.wav");
	PRECACHE_SOUND("player/pl_grate4.wav");
	PRECACHE_SOUND("player/pl_slosh1.wav");
	PRECACHE_SOUND("player/pl_slosh2.wav");
	PRECACHE_SOUND("player/pl_slosh3.wav");
	PRECACHE_SOUND("player/pl_slosh4.wav");
	PRECACHE_SOUND("player/pl_tile1.wav");
	PRECACHE_SOUND("player/pl_tile2.wav");
	PRECACHE_SOUND("player/pl_tile3.wav");
	PRECACHE_SOUND("player/pl_tile4.wav");
	PRECACHE_SOUND("player/pl_tile5.wav");
	PRECACHE_SOUND("player/pl_swim1.wav");
	PRECACHE_SOUND("player/pl_swim2.wav");
	PRECACHE_SOUND("player/pl_swim3.wav");
	PRECACHE_SOUND("player/pl_swim4.wav");
	PRECACHE_SOUND("player/pl_ladder1.wav");
	PRECACHE_SOUND("player/pl_ladder2.wav");
	PRECACHE_SOUND("player/pl_ladder3.wav");
	PRECACHE_SOUND("player/pl_ladder4.wav");
	PRECACHE_SOUND("player/pl_wade1.wav");
	PRECACHE_SOUND("player/pl_wade2.wav");
	PRECACHE_SOUND("player/pl_wade3.wav");
	PRECACHE_SOUND("player/pl_wade4.wav");
	PRECACHE_SOUND("debris/wood1.wav");
	PRECACHE_SOUND("debris/wood2.wav");
	PRECACHE_SOUND("debris/wood3.wav");
	PRECACHE_SOUND("plats/train_use1.wav");
	PRECACHE_SOUND("plats/vehicle_ignition.wav");
	PRECACHE_SOUND("buttons/spark5.wav");
	PRECACHE_SOUND("buttons/spark6.wav");
	PRECACHE_SOUND("debris/glass1.wav");
	PRECACHE_SOUND("debris/glass2.wav");
	PRECACHE_SOUND("debris/glass3.wav");
	PRECACHE_SOUND("items/flashlight1.wav");
	PRECACHE_SOUND("items/flashlight1.wav");
	PRECACHE_SOUND("common/bodysplat.wav");
	PRECACHE_SOUND("player/pl_pain2.wav");
	PRECACHE_SOUND("player/pl_pain4.wav");
	PRECACHE_SOUND("player/pl_pain5.wav");
	PRECACHE_SOUND("player/pl_pain6.wav");
	PRECACHE_SOUND("player/pl_pain7.wav");

	int numPlayerModels;
	if (g_bIsCzeroGame)
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles);
	else
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles) - 2;

	for (i = 0; i < numPlayerModels; ++i)
		PRECACHE_MODEL(sPlayerModelFiles[i]);

	if (g_bIsCzeroGame)
	{
		for (i = FirstCustomSkin; i <= LastCustomSkin; ++i)
		{
			const char *fname = TheBotProfiles->GetCustomSkinFname(i);

			if (!fname)
				break;

			PRECACHE_MODEL((char *)fname);
		}
	}

	PRECACHE_MODEL("models/p_ak47.mdl");
	PRECACHE_MODEL("models/p_aug.mdl");
	PRECACHE_MODEL("models/p_awp.mdl");
	PRECACHE_MODEL("models/p_c4.mdl");
	PRECACHE_MODEL("models/w_c4.mdl");
	PRECACHE_MODEL("models/p_deagle.mdl");
	PRECACHE_MODEL("models/shield/p_shield_deagle.mdl");
	PRECACHE_MODEL("models/p_flashbang.mdl");
	PRECACHE_MODEL("models/shield/p_shield_flashbang.mdl");
	PRECACHE_MODEL("models/p_hegrenade.mdl");
	PRECACHE_MODEL("models/shield/p_shield_hegrenade.mdl");
	PRECACHE_MODEL("models/p_glock18.mdl");
	PRECACHE_MODEL("models/shield/p_shield_glock18.mdl");
	PRECACHE_MODEL("models/p_p228.mdl");
	PRECACHE_MODEL("models/shield/p_shield_p228.mdl");
	PRECACHE_MODEL("models/p_smokegrenade.mdl");
	PRECACHE_MODEL("models/shield/p_shield_smokegrenade.mdl");
	PRECACHE_MODEL("models/p_usp.mdl");
	PRECACHE_MODEL("models/shield/p_shield_usp.mdl");
	PRECACHE_MODEL("models/p_fiveseven.mdl");
	PRECACHE_MODEL("models/shield/p_shield_fiveseven.mdl");
	PRECACHE_MODEL("models/p_knife.mdl");
	PRECACHE_MODEL("models/shield/p_shield_knife.mdl");
	PRECACHE_MODEL("models/w_flashbang.mdl");
	PRECACHE_MODEL("models/w_hegrenade.mdl");
	PRECACHE_MODEL("models/p_sg550.mdl");
	PRECACHE_MODEL("models/p_g3sg1.mdl");
	PRECACHE_MODEL("models/p_m249.mdl");
	PRECACHE_MODEL("models/p_m3.mdl");
	PRECACHE_MODEL("models/p_m4a1.mdl");
	PRECACHE_MODEL("models/p_mac10.mdl");
	PRECACHE_MODEL("models/p_mp5.mdl");
	PRECACHE_MODEL("models/p_ump45.mdl");
	PRECACHE_MODEL("models/p_p90.mdl");
	PRECACHE_MODEL("models/p_scout.mdl");
	PRECACHE_MODEL("models/p_sg552.mdl");
	PRECACHE_MODEL("models/w_smokegrenade.mdl");
	PRECACHE_MODEL("models/p_tmp.mdl");
	PRECACHE_MODEL("models/p_elite.mdl");
	PRECACHE_MODEL("models/p_xm1014.mdl");
	PRECACHE_MODEL("models/p_galil.mdl");
	PRECACHE_MODEL("models/p_famas.mdl");
	PRECACHE_MODEL("models/p_shield.mdl");
	PRECACHE_MODEL("models/w_shield.mdl");

	Vector temp = g_vecZero;
	Vector vMin(-38, -24, -41);
	Vector vMax(38, 24, 41);

	for (i = 0; i < numPlayerModels; ++i)
		ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, sPlayerModelFiles[i]);

	if (g_bIsCzeroGame)
	{
		for (i = FirstCustomSkin; i <= LastCustomSkin; ++i)
		{
			const char *fname = TheBotProfiles->GetCustomSkinFname(i);
			if (!fname)
				break;

			ENGINE_FORCE_UNMODIFIED(force_model_specifybounds_if_avail, (float *)&vMin, (float *)&vMax, fname);
		}
	}

	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke1.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke2.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke3.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke4.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/fast_wallpuff1.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/smokepuff.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/gas_puff_01.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc.tga");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc_nw.tga");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc_ne.tga");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc_sw.tga");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-13, -6, -22);
		vMax = Vector(13, 6, 22);
	}
	else
	{
		vMin = Vector(-12, -6, -22);
		vMax = Vector(12, 6, 22);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_deagle.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_p228.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_elite.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_usp.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_fiveseven.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_glock18.mdl");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-26, -19, -21);
		vMax = Vector(26, 23, 21);
	}
	else
	{
		vMin = Vector(-25, -19, -21);
		vMax = Vector(25, 23, 21);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_xm1014.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_m3.mdl");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-23, -9, -20);
		vMax = Vector(23, 17, 20);
	}
	else
	{
		vMin = Vector(-23, -8, -20);
		vMax = Vector(23, 8, 20);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_mac10.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_mp5.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_ump45.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_tmp.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_p90.mdl");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-38, -33, -22);
		vMax = Vector(38, 15, 35);
	}
	else
	{
		vMin = Vector(-31, -8, -21);
		vMax = Vector(31, 12, 31);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_ak47.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_aug.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_awp.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_g3sg1.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_sg550.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_m4a1.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_scout.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_sg552.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_famas.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_galil.mdl");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-30, -10, -20);
		vMax = Vector(30, 11, 20);
	}
	else
	{
		vMin = Vector(-24, -10, -20);
		vMax = Vector(25, 10, 20);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_m249.mdl");

	vMin = Vector(-7, -7, -15);
	vMax = Vector(7, 7, 15);

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_c4.mdl");

	vMin = Vector(-4, -8, -3);
	vMax = Vector(3, 7, 3);

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-17, -8, -3);
		vMax = Vector(17, 7, 3);
	}
	else
	{
		vMin = Vector(-4, -8, -3);
		vMax = Vector(3, 7, 3);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_c4.mdl");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-7, -3, -18);
		vMax = Vector(7, 2, 18);
	}
	else
	{
		vMin = Vector(-7, -2, -18);
		vMax = Vector(7, 2, 18);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_flashbang.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_hegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_smokegrenade.mdl");

	if (g_bIsCzeroGame)
		vMin = Vector(-5, -5, -7);
	else
		vMin = Vector(-5, -5, -5);

	vMax = Vector(5, 5, 14);

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_flashbang.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_hegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_smokegrenade.mdl");

	vMin = Vector(-7, -11, -18);
	vMax = Vector(7, 6, 18);

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_knife.mdl");

	if (g_bIsCzeroGame)
	{
		vMin = Vector(-21, -25, -54);
		vMax = Vector(21, 23, 24);
	}
	else
	{
		vMin = Vector(-16, -8, -54);
		vMax = Vector(16, 6, 24);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_deagle.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_fiveseven.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_flashbang.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_glock18.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_hegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_knife.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_p228.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_smokegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_usp.mdl");

	PRECACHE_SOUND("common/wpn_hudoff.wav");
	PRECACHE_SOUND("common/wpn_hudon.wav");
	PRECACHE_SOUND("common/wpn_moveselect.wav");
	PRECACHE_SOUND("common/wpn_select.wav");
	PRECACHE_SOUND("common/wpn_denyselect.wav");
	PRECACHE_SOUND("player/geiger6.wav");
	PRECACHE_SOUND("player/geiger5.wav");
	PRECACHE_SOUND("player/geiger4.wav");
	PRECACHE_SOUND("player/geiger3.wav");
	PRECACHE_SOUND("player/geiger2.wav");
	PRECACHE_SOUND("player/geiger1.wav");

	if (giPrecacheGrunt)
		UTIL_PrecacheOther("enemy_terrorist");

	g_iShadowSprite = PRECACHE_MODEL("sprites/shadow_circle.spr");

	PRECACHE_MODEL("sprites/wall_puff1.spr");
	PRECACHE_MODEL("sprites/wall_puff2.spr");
	PRECACHE_MODEL("sprites/wall_puff3.spr");
	PRECACHE_MODEL("sprites/wall_puff4.spr");
	PRECACHE_MODEL("sprites/black_smoke1.spr");
	PRECACHE_MODEL("sprites/black_smoke2.spr");
	PRECACHE_MODEL("sprites/black_smoke3.spr");
	PRECACHE_MODEL("sprites/black_smoke4.spr");
	PRECACHE_MODEL("sprites/fast_wallpuff1.spr");
	PRECACHE_MODEL("sprites/pistol_smoke1.spr");
	PRECACHE_MODEL("sprites/pistol_smoke2.spr");
	PRECACHE_MODEL("sprites/rifle_smoke1.spr");
	PRECACHE_MODEL("sprites/rifle_smoke2.spr");
	PRECACHE_MODEL("sprites/rifle_smoke3.spr");
	PRECACHE_GENERIC("sprites/scope_arc.tga");
	PRECACHE_GENERIC("sprites/scope_arc_nw.tga");
	PRECACHE_GENERIC("sprites/scope_arc_ne.tga");
	PRECACHE_GENERIC("sprites/scope_arc_sw.tga");

	m_usResetDecals = g_engfuncs.pfnPrecacheEvent(1, "events/decal_reset.sc");
}

const char *EXT_FUNC GetGameDescription()
{
#ifdef REGAMEDLL_ADD
	if (CSGameRules()) {
		return CSGameRules()->GetGameDescription();
	}
#else
	if (g_bIsCzeroGame) {
		return "Condition Zero";
	}
#endif
	return "Counter-Strike";
}

void EXT_FUNC SysEngine_Error(const char *error_string)
{
	;
}

void EXT_FUNC PlayerCustomization(edict_t *pEntity, customization_t *pCust)
{
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (!pPlayer)
	{
		ALERT(at_console, "PlayerCustomization:  Couldn't get player!\n");
		return;
	}

	if (!pCust)
	{
		ALERT(at_console, "PlayerCustomization:  NULL customization!\n");
		return;
	}

	switch (pCust->resource.type)
	{
	case t_decal:
		pPlayer->SetCustomDecalFrames(pCust->nUserData2);
		break;
	case t_sound:
	case t_skin:
	case t_model:
		break;
	default:
		ALERT(at_console, "PlayerCustomization:  Unknown customization type!\n");
		break;
	}
}

void EXT_FUNC SpectatorConnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorConnect();
	}
}

void EXT_FUNC SpectatorDisconnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorDisconnect();
	}
}

void EXT_FUNC SpectatorThink(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorThink();
	}
}

void EXT_FUNC SetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas)
{
	edict_t *pView = pClient;

	// Find the client's PVS
	if (pViewEntity)
	{
		pView = pViewEntity;
	}

	if (pClient->v.flags & FL_PROXY)
	{
		*pvs = nullptr;	// the spectator proxy sees
		*pas = nullptr;	// and hears everything
		return;
	}

	CBasePlayer *pPlayer = CBasePlayer::Instance(pClient);
	if (pPlayer && pPlayer->pev->iuser2 && pPlayer->m_hObserverTarget)
	{
		if (pPlayer->m_afPhysicsFlags & PFLAG_OBSERVER)
		{
			pView = pPlayer->m_hObserverTarget->edict();
			UTIL_SetOrigin(pPlayer->pev, pPlayer->m_hObserverTarget->pev->origin);
		}
	}

	Vector org = pView->v.origin + pView->v.view_ofs;

	if (pView->v.flags & FL_DUCKING)
	{
		org = org + (VEC_HULL_MIN - VEC_DUCK_HULL_MIN);
	}

	*pvs = ENGINE_SET_PVS((float *)&org);
	*pas = ENGINE_SET_PAS((float *)&org);
}

void ResetPlayerPVS(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];

	Q_memset(pvs, 0, sizeof(*pvs));
	pvs->headnode = client->headnode;
	pvs->num_leafs = client->num_leafs;
	Q_memcpy(pvs->leafnums, client->leafnums, sizeof(pvs->leafnums));
}

bool CheckPlayerPVSLeafChanged(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];
	if (pvs->headnode != client->headnode || pvs->num_leafs != client->num_leafs)
		return true;

	for (int i = 0; i < pvs->num_leafs; ++i)
	{
		if (client->leafnums[i] != pvs->leafnums[i])
			return true;
	}
	return false;
}

void MarkEntityInPVS(int clientnum, int entitynum, float time, bool inpvs)
{
	PLAYERPVSSTATUS *pvs;
	ENTITYPVSSTATUS *es;

	pvs = &g_PVSStatus[clientnum];
	es = &pvs->m_Status[entitynum];

	if (inpvs)
		es->m_fTimeEnteredPVS = time;
	else
		es->m_fTimeEnteredPVS = 0;
}

bool CheckEntityRecentlyInPVS(int clientnum, int entitynum, float currenttime)
{
	PLAYERPVSSTATUS *pvs;
	ENTITYPVSSTATUS *es;

	pvs = &g_PVSStatus[clientnum];
	es = &pvs->m_Status[entitynum];

	if (es->m_fTimeEnteredPVS && es->m_fTimeEnteredPVS + 1.0f >= currenttime)
	{
		return true;
	}

	return false;
}

int EXT_FUNC AddToFullPack(struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet)
{
	if ((ent->v.effects & EF_NODRAW) == EF_NODRAW && ent != host)
		return 0;

	if (!ent->v.modelindex || !STRING(ent->v.model))
		return 0;

	if ((ent->v.flags & FL_SPECTATOR) == FL_SPECTATOR && ent != host)
		return 0;

	int i;
	int hostnum = ENTINDEX(host) - 1;

	if (CheckPlayerPVSLeafChanged(host, hostnum))
		ResetPlayerPVS(host, hostnum);

	if (ent != host)
	{
		if (!CheckEntityRecentlyInPVS(hostnum, e, gpGlobals->time))
		{
			if (!ENGINE_CHECK_VISIBILITY(ent, pSet))
			{
				MarkEntityInPVS(hostnum, e, 0, false);
				return 0;
			}

			MarkEntityInPVS(hostnum, e, gpGlobals->time, true);
		}
	}

	if ((ent->v.flags & FL_SKIPLOCALHOST) == FL_SKIPLOCALHOST && (hostflags & 1) && ent->v.owner == host)
		return 0;

	if (host->v.groupinfo)
	{
		UTIL_SetGroupTrace(host->v.groupinfo, GROUP_OP_AND);

		if (ent->v.groupinfo)
		{
			if (g_groupop == GROUP_OP_AND)
			{
				if (!(ent->v.groupinfo & host->v.groupinfo))
					return 0;
			}
			else if (g_groupop == GROUP_OP_NAND)
			{
				if (ent->v.groupinfo & host->v.groupinfo)
					return 0;
			}
		}

		UTIL_UnsetGroupTrace();
	}

	Q_memset(state, 0, sizeof(entity_state_t));

	state->number = e;
	state->entityType = ENTITY_NORMAL;

	if (ent->v.flags & FL_CUSTOMENTITY)
		state->entityType = ENTITY_BEAM;

	state->animtime = int(1000.0 * ent->v.animtime) / 1000.0;

	Q_memcpy(state->origin, ent->v.origin, sizeof(float) * 3);
	Q_memcpy(state->angles, ent->v.angles, sizeof(float) * 3);
	Q_memcpy(state->mins, ent->v.mins, sizeof(float) * 3);
	Q_memcpy(state->maxs, ent->v.maxs, sizeof(float) * 3);
	Q_memcpy(state->startpos, ent->v.startpos, sizeof(float) * 3);
	Q_memcpy(state->endpos, ent->v.endpos, sizeof(float) * 3);

	state->impacttime = ent->v.impacttime;
	state->starttime = ent->v.starttime;
	state->modelindex = ent->v.modelindex;
	state->frame = ent->v.frame;
	state->skin = ent->v.skin;
	state->effects = ent->v.effects;

	if (!player && ent->v.animtime && !ent->v.velocity.x && !ent->v.velocity.y && !ent->v.velocity.z)
		state->eflags |= EFLAG_SLERP;

	state->scale = ent->v.scale;
	state->solid = ent->v.solid;
	state->colormap = ent->v.colormap;
	state->movetype = ent->v.movetype;
	state->sequence = ent->v.sequence;
	state->framerate = ent->v.framerate;
	state->body = ent->v.body;

	for (i = 0; i < 4; ++i)
		state->controller[i] = ent->v.controller[i];

	for (i = 0; i < 2; ++i)
		state->blending[i] = ent->v.blending[i];

	state->rendermode = ent->v.rendermode;
	state->renderamt = int(ent->v.renderamt);
	state->renderfx = ent->v.renderfx;
	state->rendercolor.r = byte(ent->v.rendercolor.x);
	state->rendercolor.g = byte(ent->v.rendercolor.y);
	state->rendercolor.b = byte(ent->v.rendercolor.z);

	state->aiment = 0;

	if (ent->v.aiment)
		state->aiment = ENTINDEX(ent->v.aiment);

	state->owner = 0;
	if (ent->v.owner)
	{
		int owner = ENTINDEX(ent->v.owner);
		if (owner >= 1 && owner <= gpGlobals->maxClients)
			state->owner = owner;
	}

	if (player)
	{
		Q_memcpy(state->basevelocity, ent->v.basevelocity, sizeof(float) * 3);

		state->weaponmodel = MODEL_INDEX(STRING(ent->v.weaponmodel));
		state->gaitsequence = ent->v.gaitsequence;

		state->spectator = (ent->v.flags & FL_SPECTATOR) ? TRUE : FALSE;
		state->friction = ent->v.friction;
		state->gravity = ent->v.gravity;
		state->usehull = (ent->v.flags & FL_DUCKING) ? 1 : 0;
		state->health = int(ent->v.health);
	}
	else
		state->playerclass = ent->v.playerclass;

	state->iuser4 = ent->v.iuser4;
	return 1;
}

// Creates baselines used for network encoding, especially for player data since players are not spawned until connect time.
void EXT_FUNC CreateBaseline(int player, int eindex, struct entity_state_s *baseline, struct edict_s *entity, int playermodelindex, Vector player_mins, Vector player_maxs)
{
	baseline->origin = entity->v.origin;
	baseline->angles = entity->v.angles;

	baseline->frame = entity->v.frame;
	baseline->skin = (short)entity->v.skin;

	// render information
	baseline->rendermode = byte(entity->v.rendermode);
	baseline->renderamt = byte(entity->v.renderamt);
	baseline->rendercolor.r	= byte(entity->v.rendercolor.x);
	baseline->rendercolor.g	= byte(entity->v.rendercolor.y);
	baseline->rendercolor.b	= byte(entity->v.rendercolor.z);
	baseline->renderfx = byte(entity->v.renderfx);

	if (player)
	{
		baseline->mins = player_mins;
		baseline->maxs = player_maxs;

		baseline->colormap = eindex;
		baseline->modelindex = playermodelindex;
		baseline->friction = 1.0;
		baseline->movetype = MOVETYPE_WALK;

		baseline->solid = SOLID_SLIDEBOX;
		baseline->scale = entity->v.scale;
		baseline->framerate = 1.0;
		baseline->gravity = 1.0;
	}
	else
	{
		baseline->mins = entity->v.mins;
		baseline->maxs = entity->v.maxs;

		baseline->colormap = 0;
		baseline->modelindex = entity->v.modelindex;
		baseline->movetype = entity->v.movetype;

		baseline->scale = entity->v.scale;
		baseline->solid = entity->v.solid;
		baseline->framerate = entity->v.framerate;
		baseline->gravity = entity->v.gravity;
	}
}

void Entity_FieldInit(struct delta_s *pFields)
{
	entity_field_alias[ FIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ORIGIN0 ].name);
	entity_field_alias[ FIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ORIGIN1 ].name);
	entity_field_alias[ FIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ORIGIN2 ].name);
	entity_field_alias[ FIELD_ANGLES0 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ANGLES0 ].name);
	entity_field_alias[ FIELD_ANGLES1 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ANGLES1 ].name);
	entity_field_alias[ FIELD_ANGLES2 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ANGLES2 ].name);
}

// Callback for sending entity_state_t info over network.
void Entity_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to)
{
	entity_state_t *f, *t;
	int localplayer = 0;
	static int initialized = 0;

	if (!initialized)
	{
		Entity_FieldInit(pFields);
		initialized = 1;
	}

	f = (entity_state_t *)from;
	t = (entity_state_t *)to;

	// Never send origin to local player, it's sent with more resolution in clientdata_t structure
	localplayer = (t->number - 1) == ENGINE_CURRENT_PLAYER();

	if (localplayer)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	if (t->impacttime != 0 && t->starttime != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);

		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ANGLES0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ANGLES1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ANGLES2 ].field);
	}
	if (t->movetype == MOVETYPE_FOLLOW && t->aiment != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	else if (t->aiment != f->aiment)
	{
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
}

void Player_FieldInit(struct delta_s *pFields)
{
	player_field_alias[ FIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN0 ].name);
	player_field_alias[ FIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN1 ].name);
	player_field_alias[ FIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN2 ].name);
}

// Callback for sending entity_state_t for players info over network.
void Player_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to)
{
	entity_state_t *f, *t;
	int localplayer = 0;

	static int initialized = 0;
	if (!initialized)
	{
		Player_FieldInit(pFields);
		initialized = 1;
	}

	f = (entity_state_t *)from;
	t = (entity_state_t *)to;

	// Never send origin to local player, it's sent with more resolution in clientdata_t structure
	localplayer = (t->number - 1) == ENGINE_CURRENT_PLAYER();

	if (localplayer)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	if (t->movetype == MOVETYPE_FOLLOW && t->aiment != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	else if (t->aiment != f->aiment)
	{
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
}

void Custom_Entity_FieldInit(delta_s *pFields)
{
	custom_entity_field_alias[ CUSTOMFIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN0 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN1 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN2 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANGLES0 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES0 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANGLES1 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES1 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANGLES2 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES2 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_SKIN ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_SKIN ].name);
	custom_entity_field_alias[ CUSTOMFIELD_SEQUENCE ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_SEQUENCE ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].name);
}

// Callback for sending entity_state_t info ( for custom entities ) over network.
void Custom_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to)
{
	entity_state_t *f, *t;
	int beamType;
	static int initialized = 0;

	if (!initialized)
	{
		Custom_Entity_FieldInit(pFields);
		initialized = 1;
	}

	f = (entity_state_t *)from;
	t = (entity_state_t *)to;

	beamType = t->rendermode & 0x0F;

	if (beamType != BEAM_POINTS)
	{
		if (beamType != BEAM_ENTPOINT)
		{
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN0 ].field);
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN1 ].field);
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN2 ].field);
		}

		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES0 ].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES1 ].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES2 ].field);
	}

	if (beamType != BEAM_ENTS && beamType != BEAM_ENTPOINT)
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_SKIN ].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_SEQUENCE ].field);
	}

	// animtime is compared by rounding first
	// see if we really shouldn't actually send it
	if (int(f->animtime) == int(t->animtime))
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].field);
	}
}

// Allows game .dll to override network encoding of certain types of entities and tweak values, etc.
void EXT_FUNC RegisterEncoders()
{
	DELTA_ADDENCODER("Entity_Encode", Entity_Encode);
	DELTA_ADDENCODER("Custom_Encode", Custom_Encode);
	DELTA_ADDENCODER("Player_Encode", Player_Encode);
}

int EXT_FUNC GetWeaponData(edict_t *player, struct weapon_data_s *info)
{
#ifdef CLIENT_WEAPONS
	entvars_t *pev = &player->v;
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	Q_memset(info, 0, sizeof(weapon_data_t) * MAX_WEAPONS);

	if (!pPlayer)
		return 1;

	// go through all of the weapons and make a list of the ones to pack
	for (int i = 0; i < MAX_ITEM_TYPES; ++i)
	{
		auto pPlayerItem = pPlayer->m_rgpPlayerItems[i];
		while (pPlayerItem != nullptr)
		{
			// there's a weapon here. Should I pack it?
			auto weapon = (CBasePlayerWeapon *)pPlayerItem->GetWeaponPtr();
			if (weapon && weapon->UseDecrement())
			{
				// Get The ID
				ItemInfo II;
				Q_memset(&II, 0, sizeof(II));
				weapon->GetItemInfo(&II);

				if (II.iId >= 0 && II.iId < MAX_WEAPONS)
				{
					auto item = &info[II.iId];

					item->m_iId = II.iId;
					item->m_iClip = weapon->m_iClip;
					item->m_flTimeWeaponIdle = Q_max(weapon->m_flTimeWeaponIdle, -0.001f);
					item->m_flNextPrimaryAttack = Q_max(weapon->m_flNextPrimaryAttack, -0.001f);
					item->m_flNextSecondaryAttack = Q_max(weapon->m_flNextSecondaryAttack, -0.001f);
					item->m_flNextReload = Q_max(weapon->m_flNextReload, -0.001f);
					item->m_fInReload = weapon->m_fInReload;
					item->m_fInSpecialReload = weapon->m_fInSpecialReload;
					item->m_fInZoom = weapon->m_iShotsFired;
					item->m_fAimedDamage = weapon->m_flLastFire;
					item->m_iWeaponState = weapon->m_iWeaponState;
					item->fuser2 = weapon->m_flStartThrow;
					item->fuser3 = weapon->m_flReleaseThrow;
					item->iuser1 = weapon->m_iSwing;
				}
			}

			pPlayerItem = pPlayerItem->m_pNext;
		}
	}
#else
	Q_memset(info, 0, sizeof(weapon_data_t) * MAX_WEAPONS);
#endif

	return 1;
}

// Data sent to current client only engine sets cd to 0 before calling.
void EXT_FUNC UpdateClientData(const struct edict_s *ent, int sendweapons, struct clientdata_s *cd)
{
	if (!ent || !ent->pvPrivateData)
		return;

	entvars_t *pevOrg = nullptr;
	entvars_t *pev = const_cast<entvars_t *>(&ent->v);
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	// if user is spectating different player in First person, override some vars
	if (pPlayer && pPlayer->pev->iuser1 == OBS_IN_EYE && pPlayer->m_hObserverTarget)
	{
		pevOrg = pev;
		pev = pPlayer->m_hObserverTarget->pev;
		pPlayer = CBasePlayer::Instance(pev);
	}

	cd->flags = pev->flags;
	cd->health = pev->health;
	cd->viewmodel = MODEL_INDEX(STRING(pev->viewmodel));
	cd->waterlevel = pev->waterlevel;
	cd->watertype = pev->watertype;
	cd->weapons = pev->weapons;
	cd->origin = pev->origin;
	cd->velocity = pev->velocity;
	cd->view_ofs = pev->view_ofs;
	cd->punchangle = pev->punchangle;
	cd->bInDuck = pev->bInDuck;
	cd->flTimeStepSound = pev->flTimeStepSound;
	cd->flDuckTime = pev->flDuckTime;
	cd->flSwimTime = pev->flSwimTime;
	cd->waterjumptime = int(pev->teleport_time);

	Q_strcpy(cd->physinfo, ENGINE_GETPHYSINFO(ent));

	cd->maxspeed = pev->maxspeed;
	cd->fov = pev->fov;
	cd->weaponanim = pev->weaponanim;
	cd->pushmsec = pev->pushmsec;

	if (pevOrg)
	{
		cd->iuser1 = pevOrg->iuser1;
		cd->iuser2 = pevOrg->iuser2;
		cd->iuser3 = pevOrg->iuser3;
	}
	else
	{
		cd->iuser1 = pev->iuser1;
		cd->iuser2 = pev->iuser2;
		cd->iuser3 = pev->iuser3;
	}

	cd->fuser1 = pev->fuser1;
	cd->fuser3 = pev->fuser3;
	cd->fuser2 = pev->fuser2;

	if (sendweapons && pPlayer)
	{
		cd->ammo_shells = pPlayer->ammo_buckshot;
		cd->ammo_nails = pPlayer->ammo_9mm;
		cd->ammo_cells = pPlayer->ammo_556nato;
		cd->ammo_rockets = pPlayer->ammo_556natobox;
		cd->vuser2.x = pPlayer->ammo_762nato;
		cd->vuser2.y = pPlayer->ammo_45acp;
		cd->vuser2.z = pPlayer->ammo_50ae;
		cd->vuser3.x = pPlayer->ammo_338mag;
		cd->vuser3.y = pPlayer->ammo_57mm;
		cd->vuser3.z = pPlayer->ammo_357sig;
		cd->m_flNextAttack = pPlayer->m_flNextAttack;

		int iUser3 = 0;
		if (pPlayer->m_bCanShoot && !pPlayer->m_bIsDefusing)
			iUser3 |= PLAYER_CAN_SHOOT;

		if (g_pGameRules->IsFreezePeriod())
			iUser3 |= PLAYER_FREEZE_TIME_OVER;

		if (pPlayer->m_signals.GetState() & SIGNAL_BOMB)
			iUser3 |= PLAYER_IN_BOMB_ZONE;

		if (pPlayer->HasShield())
			iUser3 |= PLAYER_HOLDING_SHIELD;

		if (pPlayer->pev->iuser1 == OBS_NONE && !pevOrg)
		{
#ifdef REGAMEDLL_ADD
			// useful for mods
			iUser3 |= pev->iuser3;
#endif
			cd->iuser3 = iUser3;
		}

		if (pPlayer->m_pActiveItem)
		{
			ItemInfo II;
			Q_memset(&II, 0, sizeof(II));

			CBasePlayerWeapon *weapon = (CBasePlayerWeapon *)pPlayer->m_pActiveItem->GetWeaponPtr();
			if (weapon && weapon->UseDecrement() && weapon->GetItemInfo(&II))
			{
				cd->m_iId = II.iId;

				if ((unsigned int)weapon->m_iPrimaryAmmoType < MAX_AMMO_SLOTS)
				{
					cd->vuser4.x = weapon->m_iPrimaryAmmoType;
					cd->vuser4.y = pPlayer->m_rgAmmo[ weapon->m_iPrimaryAmmoType ];
				}
				else
				{
					cd->vuser4.x = -1.0;
					cd->vuser4.y = 0;
				}
			}
		}
	}
}

void EXT_FUNC CmdStart(const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed)
{
	entvars_t *pev = const_cast<entvars_t *>(&player->v);
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer)
		return;

	if (pPlayer->pev->groupinfo)
		UTIL_SetGroupTrace(pPlayer->pev->groupinfo, GROUP_OP_AND);

	pPlayer->random_seed = random_seed;
}

void EXT_FUNC CmdEnd(const edict_t *player)
{
	entvars_t *pev = const_cast<entvars_t *>(&player->v);
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer)
		return;

	if (pPlayer->pev->groupinfo)
		UTIL_UnsetGroupTrace();

	if (pev->flags & FL_DUCKING)
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
}

int EXT_FUNC ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
{
	// Parse stuff from args
	int max_buffer_size = *response_buffer_size;

	// Zero it out since we aren't going to respond.
	// If we wanted to response, we'd write data into response_buffer
	*response_buffer_size = 0;

	// Since we don't listen for anything here, just respond that it's a bogus message
	// If we didn't reject the message, we'd return 1 for success instead.
	return 0;
}

int EXT_FUNC GetHullBounds(int hullnumber, float *mins, float *maxs)
{
	return hullnumber < 3;
}

// Create pseudo-baselines for items that aren't placed in the map at spawn time, but which are likely
// to be created during play ( e.g., grenades, ammo packs, projectiles, corpses, etc. )
void EXT_FUNC CreateInstancedBaselines()
{
#ifndef REGAMEDLL_FIXES
	int iret = 0;
	entity_state_t state;

	Q_memset(&state, 0, sizeof(state));

	// Create any additional baselines here for things like grendates, etc.
	// iret = ENGINE_INSTANCE_BASELINE(pc->pev->classname, &state);

	// Destroy objects.
	// UTIL_Remove(pc);
#endif
}

int EXT_FUNC InconsistentFile(const edict_t *player, const char *filename, char *disconnect_message)
{
	// Server doesn't care?
	if (!CVAR_GET_FLOAT("mp_consistency"))
		return 0;

	// Default behavior is to kick the player
	Q_sprintf(disconnect_message, "Server is enforcing file consistency for %s\n", filename);

	// Kick now with specified disconnect message.
	return 1;
}

// The game .dll should return 1 if lag compensation should be allowed ( could also just set
// the sv_unlag cvar.
// Most games right now should return 0, until client-side weapon prediction code is written
// and tested for them ( note you can predict weapons, but not do lag compensation, too,
// if you want.
int EXT_FUNC AllowLagCompensation()
{
	return 1;
}
