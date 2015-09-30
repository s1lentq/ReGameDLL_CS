#include "precompiled.h"
#include "entity_state.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

float g_flTimeLimit = 0;
float g_flResetTime = 0;
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

bool g_skipCareerInitialSpawn;

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
}

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
}

static int g_serveractive = 0;

#else

float g_flTimeLimit;
float g_flResetTime;
bool g_bClientPrintEnable;

char *sPlayerModelFiles[12];
bool g_skipCareerInitialSpawn;

entity_field_alias_t entity_field_alias[6];
entity_field_alias_t player_field_alias[3];
entity_field_alias_t custom_entity_field_alias[9];
int g_serveractive;

#endif // HOOK_GAMEDLL

PLAYERPVSSTATUS g_PVSStatus[32];
unsigned short m_usResetDecals;
unsigned short g_iShadowSprite;

/* <47b45> ../cstrike/dlls/client.cpp:76 */
int CMD_ARGC_(void)
{
	if (!UseBotArgs)
		return CMD_ARGC();

	int i = 0;

	while (BotArgs[i])
		i++;

	return i;
}

/* <47b84> ../cstrike/dlls/client.cpp:90 */
const char *CMD_ARGV_(int i)
{
	if (!UseBotArgs)
		return CMD_ARGV(i);

	if (i < 4)
		return BotArgs[i];

	return NULL;
}

/* <47eac> ../cstrike/dlls/client.cpp:180 */
NOXREF void set_suicide_frame(entvars_t *pev)
{
	if (!FStrEq(STRING(pev->model), "models/player.mdl"))
		return;

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_TOSS;
	pev->deadflag = DEAD_DEAD;
	pev->nextthink = -1;
}

/* <47a58> ../cstrike/dlls/client.cpp:192 */
void TeamChangeUpdate(CBasePlayer *player, int team_id)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgTeamInfo);
		WRITE_BYTE(player->entindex());
		switch (team_id)
		{
		case CT:
			WRITE_STRING("CT");
			break;
		case TERRORIST:
			WRITE_STRING("TERRORIST");
			break;
		case SPECTATOR:
			WRITE_STRING("SPECTATOR");
			break;
		default:
			WRITE_STRING("UNASSIGNED");
			break;
		}
	MESSAGE_END();

	if (team_id != UNASSIGNED)
	{
		player->SetScoreboardAttributes();
	}
}

/* <4731f> ../cstrike/dlls/client.cpp:222 */
void BlinkAccount(CBasePlayer *player, int numBlinks)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgBlinkAcct, NULL, player->pev);
		WRITE_BYTE(numBlinks);
	MESSAGE_END();
}

/* <47efd> ../cstrike/dlls/client.cpp:236 */
BOOL ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
	return g_pGameRules->ClientConnected(pEntity, pszName, pszAddress, szRejectReason);
}

/* <47f5b> ../cstrike/dlls/client.cpp:255 */
void ClientDisconnect(edict_t *pEntity)
{
	CBasePlayer *pPlayer = (CBasePlayer *)CBaseEntity::Instance(pEntity);

	if (!g_fGameOver)
	{
		UTIL_ClientPrintAll(HUD_PRINTNOTIFY, "#Game_disconnected", STRING(pEntity->v.netname));
		CSound *pSound = CSoundEnt::SoundPointerForIndex(CSoundEnt::ClientSoundIndex(pEntity));

		if (pSound)
			pSound->Reset();

		pEntity->v.takedamage = DAMAGE_NO;
		pEntity->v.solid = SOLID_NOT;
		pEntity->v.flags = FL_DORMANT;

		if (pPlayer)
			pPlayer->SetThink(NULL);

		UTIL_SetOrigin(&pEntity->v, pEntity->v.origin);
		g_pGameRules->ClientDisconnected(pEntity);
	}

	if (pPlayer && pPlayer->IsBot())
	{
		TheBots->ClientDisconnect(pPlayer);
	}
}

/* <4c477> ../cstrike/dlls/client.cpp:306 */
void respawn(entvars_t *pev, BOOL fCopyCorpse)
{
	if (gpGlobals->coop || gpGlobals->deathmatch)
	{
		CHalfLifeMultiplay *mp = g_pGameRules;

		if (mp->m_iTotalRoundsPlayed > 0)
			mp->MarkSpawnSkipped();

		CBasePlayer *pPlayer = GetClassPtr((CBasePlayer *)pev);

		if (mp->IsCareer() && mp->ShouldSkipSpawn() && pPlayer->IsAlive())
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

/* <48013> ../cstrike/dlls/client.cpp:347 */
void ClientKill(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CHalfLifeMultiplay *mp = g_pGameRules;
	CBasePlayer *pl = (CBasePlayer *)CBasePlayer::Instance(pev);

	if (pl->IsObserver())
		return;

	if (pl->m_iJoiningState != JOINED)
		return;

	// prevent suiciding too often
	if (pl->m_fNextSuicideTime > gpGlobals->time)
		return;

	pl->m_LastHitGroup = 0;

	// don't let them suicide for 5 seconds after suiciding
	pl->m_fNextSuicideTime = gpGlobals->time + 1;

	// have the player kill themself
	pEntity->v.health = 0;
	pl->Killed(pev, GIB_NEVER);

	if (mp->m_pVIP == pl)
	{
		mp->m_iConsecutiveVIP = 10;
	}
}

/* <47a8a> ../cstrike/dlls/client.cpp:379 */
void ShowMenu(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, NULL, pPlayer->pev);
		WRITE_SHORT(bitsValidSlots);
		WRITE_CHAR(nDisplayTime);
		WRITE_BYTE(fNeedMore);
		WRITE_STRING(pszText);
	MESSAGE_END();
}

/* <4735f> ../cstrike/dlls/client.cpp:390 */
void ShowVGUIMenu(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu)
{
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

/* <4c3c5> ../cstrike/dlls/client.cpp:414 */
NOXREF int CountTeams(void)
{
	int iNumCT = 0, iNumTerrorist = 0;
	CBaseEntity *pPlayer = NULL;

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		CBasePlayer *player = GetClassPtr((CBasePlayer *)pPlayer->pev);

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

/* <4c2be> ../cstrike/dlls/client.cpp:443 */
void ListPlayers(CBasePlayer *current)
{
	char message[120], cNumber[12];
	Q_strcpy(message, "");

	CBaseEntity *pPlayer = NULL;
	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (pPlayer->pev->flags & FL_DORMANT)
			continue;

		CBasePlayer *player = GetClassPtr((CBasePlayer *)pPlayer->pev);
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

/* <4c200> ../cstrike/dlls/client.cpp:475 */
int CountTeamPlayers(int iTeam)
{
	CBaseEntity *pPlayer = NULL;
	int i = 0;

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (pPlayer->pev->flags & FL_DORMANT)
			continue;

		if (GetClassPtr((CBasePlayer *)pPlayer->pev)->m_iTeam == iTeam)
			i++;
	}

	return i;
}

/* <4c4ef> ../cstrike/dlls/client.cpp:494 */
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

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")) != NULL)
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		pTempPlayer = GetClassPtr((CBasePlayer *)pTempEntity->pev);

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

	if (iVotesNeeded >= (int)fKickPercent)
	{
		UTIL_ClientPrintAll(HUD_PRINTCENTER, "#Game_kicked", STRING(pKickPlayer->pev->netname));
		SERVER_COMMAND(UTIL_VarArgs("kick # %d\n", iVoteID));
		pTempEntity = NULL;

		while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")) != NULL)
		{
			if (FNullEnt(pTempEntity->edict()))
				break;

			pTempPlayer = GetClassPtr((CBasePlayer *)pTempEntity->pev);

			if (!pTempPlayer || pTempPlayer->m_iTeam == UNASSIGNED)
				continue;

			if (pTempPlayer->m_iTeam == pVotingPlayer->m_iTeam && pTempPlayer->m_iCurrentKickVote == iVoteID)
				pTempPlayer->m_iCurrentKickVote = 0;
		}
	}
}

/* <48298> ../cstrike/dlls/client.cpp:580 */
TeamName SelectDefaultTeam(void)
{
	TeamName team = UNASSIGNED;
	CHalfLifeMultiplay *mp = g_pGameRules;

	if (mp->m_iNumTerrorist < mp->m_iNumCT)
	{
		team = TERRORIST;
	}
	else if (mp->m_iNumTerrorist > mp->m_iNumCT)
	{
		team = CT;
	}
	// Choose the team that's losing
	else if (mp->m_iNumTerroristWins < mp->m_iNumCTWins)
	{
		team = TERRORIST;
	}
	else if (mp->m_iNumCTWins < mp->m_iNumTerroristWins)
	{
		team = CT;
	}
	else
	{
		// Teams and scores are equal, pick a random team
		if (RANDOM_LONG(0, 1) == 0)
		{
			team = CT;
		}
		else
		{
			team = TERRORIST;
		}
	}

	if (mp->TeamFull(team))
	{
		// Pick the opposite team
		if (team == TERRORIST)
		{
			team = CT;
		}
		else
		{
			team = TERRORIST;
		}

		// No choices left
		if (mp->TeamFull(team))
		{
			return UNASSIGNED;
		}
	}

	return team;

}

/* <473a3> ../cstrike/dlls/client.cpp:638 */
void CheckStartMoney(void)
{
	int money = (int)startmoney.value;

	if (money > 16000)
		CVAR_SET_FLOAT("mp_startmoney", 16000);
	else if (money < 800)
		CVAR_SET_FLOAT("mp_startmoney", 800);
}

/* <4c084> ../cstrike/dlls/client.cpp:661 */
void ClientPutInServer(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = GetClassPtr((CBasePlayer *)pev);
	CHalfLifeMultiplay *mp = g_pGameRules;

	pPlayer->SetCustomDecalFrames(-1);
	pPlayer->SetPrefsFromUserinfo(GET_INFO_BUFFER(pEntity));

	if (!mp->IsMultiplayer())
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

	pPlayer->m_iAccount = (int)startmoney.value;
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

	CBaseEntity *Target = UTIL_FindEntityByClassname(NULL, "trigger_camera");
	pPlayer->m_pIntroCamera = Target;

	if (mp && mp->m_bMapHasCameras == MAP_HAS_CAMERAS_INIT)
	{
		mp->m_bMapHasCameras = (Target != NULL);
	}

	if (pPlayer->m_pIntroCamera)
		Target = UTIL_FindEntityByTargetname(NULL, STRING(pPlayer->m_pIntroCamera->pev->target));

	if (pPlayer->m_pIntroCamera && Target)
	{
		Vector CamAngles = UTIL_VecToAngles((Target->pev->origin - pPlayer->m_pIntroCamera->pev->origin).Normalize());
		CamAngles.x = -CamAngles.x;

		UTIL_SetOrigin(pPlayer->pev, pPlayer->m_pIntroCamera->pev->origin);

		pPlayer->pev->angles = CamAngles;
		pPlayer->pev->v_angle = pPlayer->pev->angles;

		pPlayer->m_fIntroCamTime = gpGlobals->time + 6;
		pPlayer->pev->view_ofs = g_vecZero;
	}
	else
	{
		pPlayer->m_iTeam = CT;

		if (mp)
		{
			mp->GetPlayerSpawnSpot(pPlayer);
		}

		pPlayer->m_iTeam = UNASSIGNED;
		pPlayer->pev->v_angle = g_vecZero;
		pPlayer->pev->angles = gpGlobals->v_forward;
	}

	TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, (CBaseEntity *)pPlayer);
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

/* <478f7> ../cstrike/dlls/client.cpp:792 */
int Q_strlen_(const char *str)
{
	int count = 0;
	if (str && *str)
	{
		while (str[count++ + 1]);
	}
	return count;
}

/* <4bbff> ../cstrike/dlls/client.cpp:814 */
void Host_Say(edict_t *pEntity, int teamonly)
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

	entvars_t *pev = &pEntity->v;
	CBasePlayer *player = GetClassPtr((CBasePlayer *)pev);

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
	if (!p || !p[0] || !Q_UnicodeValidate(p))
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

	if (teamonly)
	{
		if (player->m_iTeam == CT || player->m_iTeam == TERRORIST)
		{
			// search the place name where is located the player
			Place playerPlace = TheNavAreaGrid.GetPlace(&player->pev->origin);
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();

			for (BotPhraseList::const_iterator iter = placeList->begin(); iter != placeList->end(); ++iter)
			{
				if ((*iter)->GetID() == playerPlace)
				{
					placeName = (*iter)->GetName();
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
			else if (placeName != NULL)
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
			else if (placeName != NULL)
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

	if (placeName != NULL)
	{
		j -= Q_strlen(placeName) + 1;
	}

	if ((signed int)Q_strlen(p) > j)
		p[j] = 0;

	for (char *pAmpersand = p; pAmpersand != NULL && *pAmpersand != '\0'; pAmpersand++)
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
	while ((client = (CBasePlayer *)UTIL_FindEntityByClassname(client, "player")) != NULL)
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
		if (gpGlobals->deathmatch != 0.0f && g_pGameRules->m_VoiceGameMgr.PlayerHasBlockedPlayer(client, player))
			continue;

		if (teamonly && client->m_iTeam != player->m_iTeam)
			continue;

		if ((client->pev->deadflag != DEAD_NO && !bSenderDead) || (client->pev->deadflag == DEAD_NO && bSenderDead))
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

				if (placeName != NULL)
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

		if (placeName != NULL)
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

	if (CVAR_GET_FLOAT("mp_logmessages") != 0)
	{
		const char *temp = teamonly ? "say_team" : "say";
		const char *deadText = (player->m_iTeam != SPECTATOR && bSenderDead) ? " (dead)" : "";

		char *szTeam = GetTeam(player->m_iTeam);

		UTIL_LogPrintf
		(
			"\"%s<%i><%s><%s>\" %s \"%s\"%s\n",
			STRING(player->pev->netname),
			GETPLAYERUSERID(player->edict()),
			GETPLAYERAUTHID(player->edict()),
			szTeam,
			temp,
			fullText,
			deadText
		);
	}
}

/* <4865e> ../cstrike/dlls/client.cpp:1160 */
void DropSecondary(CBasePlayer *pPlayer)
{
	if (pPlayer->HasShield())
	{
		if (pPlayer->HasShield() && pPlayer->m_bShieldDrawn && pPlayer->m_pActiveItem != NULL)
		{
			((CBasePlayerWeapon *)pPlayer->m_pActiveItem)->SecondaryAttack();
		}

		pPlayer->m_bShieldDrawn = false;
	}

	CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ];

	if (pWeapon != NULL)
	{
		pPlayer->DropPlayerItem(STRING(pWeapon->pev->classname));
	}

}

/* <473db> ../cstrike/dlls/client.cpp:1182 */
void DropPrimary(CBasePlayer *pPlayer)
{
	if (pPlayer->HasShield())
	{
		pPlayer->DropShield();
		return;
	}

	if (pPlayer->m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ])
	{
		pPlayer->DropPlayerItem(STRING(pPlayer->m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ]->pev->classname));
	}
}

/* <483a2> ../cstrike/dlls/client.cpp:1197 */
bool CanBuyThis(CBasePlayer *pPlayer, int iWeapon)
{
	CHalfLifeMultiplay *mp = g_pGameRules;

	if (pPlayer->HasShield() && iWeapon == WEAPON_ELITE)
	{
		return false;
	}

	if (pPlayer->HasShield() && iWeapon == WEAPON_SHIELDGUN)
	{
		return false;
	}

	if (pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ] != NULL && pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ]->m_iId == WEAPON_ELITE && iWeapon == WEAPON_SHIELDGUN)
	{
		return false;
	}

	if (pPlayer->m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ] != NULL && pPlayer->m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ]->m_iId == iWeapon)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cstrike_Already_Own_Weapon");
		}

		return false;
	}

	if (pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ] != NULL && pPlayer->m_rgpPlayerItems[ PISTOL_SLOT ]->m_iId == iWeapon)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cstrike_Already_Own_Weapon");
		}

		return false;
	}

	if (!CanBuyWeaponByMaptype(pPlayer->m_iTeam, (WeaponIdType)iWeapon, (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES)))
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Buy_This");
		}

		return false;
	}

	return true;
}

/* <48696> ../cstrike/dlls/client.cpp:1247 */
void BuyPistol(CBasePlayer *pPlayer, int iSlot)
{
	int iWeapon = 0;
	int iWeaponPrice = 0;
	const char *pszWeapon = NULL;

	if (!pPlayer->CanPlayerBuy(true))
	{
		return;
	}

	if (iSlot < 1 || iSlot > 5)
	{
		return;
	}

	switch (iSlot)
	{
		case 1:
		{
			iWeapon = WEAPON_GLOCK18;
			iWeaponPrice = GLOCK18_PRICE;
			pszWeapon = "weapon_glock18";
			break;
		}
		case 2:
		{
			iWeapon = WEAPON_USP;
			iWeaponPrice = USP_PRICE;
			pszWeapon = "weapon_usp";
			break;
		}
		case 3:
		{
			iWeapon = WEAPON_P228;
			iWeaponPrice = P228_PRICE;
			pszWeapon = "weapon_p228";
			break;
		}
		case 4:
		{
			iWeapon = WEAPON_DEAGLE;
			iWeaponPrice = DEAGLE_PRICE;
			pszWeapon = "weapon_deagle";
			break;
		}
		case 5:
		{
			if (pPlayer->m_iTeam == CT)
			{
				iWeapon = WEAPON_FIVESEVEN;
				iWeaponPrice = FIVESEVEN_PRICE;
				pszWeapon = "weapon_fiveseven";
			}
			else
			{
				iWeapon = WEAPON_ELITE;
				iWeaponPrice = ELITE_PRICE;
				pszWeapon = "weapon_elite";
			}

			break;
		}
	}

	if (!CanBuyThis(pPlayer, iWeapon))
	{
		return;
	}

	if (pPlayer->m_iAccount < iWeaponPrice)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	DropSecondary(pPlayer);

	pPlayer->GiveNamedItem(pszWeapon);
	pPlayer->AddAccount(-iWeaponPrice);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <487b0> ../cstrike/dlls/client.cpp:1325 */
void BuyShotgun(CBasePlayer *pPlayer, int iSlot)
{
	int iWeapon = 0;
	int iWeaponPrice = 0;
	const char *pszWeapon = NULL;

	if (!pPlayer->CanPlayerBuy(true))
	{
		return;
	}

	if (iSlot < 1 || iSlot > 2)
	{
		return;
	}

	switch (iSlot)
	{
		case 1:
		{
			iWeapon = WEAPON_M3;
			iWeaponPrice = M3_PRICE;
			pszWeapon = "weapon_m3";
			break;
		}
		case 2:
		{
			iWeapon = WEAPON_XM1014;
			iWeaponPrice = XM1014_PRICE;
			pszWeapon = "weapon_xm1014";
			break;
		}
	}

	if (!CanBuyThis(pPlayer, iWeapon))
	{
		return;
	}

	if (pPlayer->m_iAccount < iWeaponPrice)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	DropPrimary(pPlayer);

	pPlayer->GiveNamedItem(pszWeapon);
	pPlayer->AddAccount(-iWeaponPrice);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <488b5> ../cstrike/dlls/client.cpp:1378 */
void BuySubMachineGun(CBasePlayer *pPlayer, int iSlot)
{
	int iWeapon = 0;
	int iWeaponPrice = 0;
	const char *pszWeapon = NULL;

	if (!pPlayer->CanPlayerBuy(true))
	{
		return;
	}

	if (iSlot < 1 || iSlot > 4)
	{
		return;
	}

	switch (iSlot)
	{
		case 1:
		{
			if (pPlayer->m_iTeam == CT)
			{
				iWeapon = WEAPON_TMP;
				iWeaponPrice = TMP_PRICE;
				pszWeapon = "weapon_tmp";
			}
			else
			{
				iWeapon = WEAPON_MAC10;
				iWeaponPrice = MAC10_PRICE;
				pszWeapon = "weapon_mac10";
			}

			break;
		}
		case 2:
		{
			iWeapon = WEAPON_MP5N;
			iWeaponPrice = MP5NAVY_PRICE;
			pszWeapon = "weapon_mp5navy";
			break;
		}
		case 3:
		{
			iWeapon = WEAPON_UMP45;
			iWeaponPrice = UMP45_PRICE;
			pszWeapon = "weapon_ump45";
			break;
		}
		case 4:
		{
			iWeapon = WEAPON_P90;
			iWeaponPrice = P90_PRICE;
			pszWeapon = "weapon_p90";
			break;
		}
	}

	if (!CanBuyThis(pPlayer, iWeapon))
	{
		return;
	}

	if (pPlayer->m_iAccount < iWeaponPrice)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	DropPrimary(pPlayer);

	pPlayer->GiveNamedItem(pszWeapon);
	pPlayer->AddAccount(-iWeaponPrice);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <489bb> ../cstrike/dlls/client.cpp:1450 */
void BuyWeaponByWeaponID(CBasePlayer *pPlayer, WeaponIdType weaponID)
{
	if (!pPlayer->CanPlayerBuy(true))
	{
		return;
	}

	if (!CanBuyThis(pPlayer, weaponID))
	{
		return;
	}

	WeaponInfoStruct *info = GetWeaponInfo(weaponID);

	if (!info || !info->entityName)
	{
		return;
	}

	if (pPlayer->m_iAccount < info->cost)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	if (IsPrimaryWeapon(weaponID))
	{
		DropPrimary(pPlayer);
	}
	else
	{
		DropSecondary(pPlayer);
	}

	pPlayer->GiveNamedItem(info->entityName);
	pPlayer->AddAccount(-info->cost);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <48adf> ../cstrike/dlls/client.cpp:1498 */
void BuyRifle(CBasePlayer *pPlayer, int iSlot)
{
	int iWeapon = 0;
	int iWeaponPrice = 0;
	bool bIsCT = false;
	const char *pszWeapon = NULL;

	if (!pPlayer->CanPlayerBuy(true))
	{
		return;
	}

	if (iSlot < 1 || iSlot > 6)
	{
		return;
	}

	if (pPlayer->m_iTeam == CT)
		bIsCT = true;

	switch (iSlot)
	{
		case 2:
		{
			if (bIsCT)
			{
				iWeapon = WEAPON_SCOUT;
				iWeaponPrice = SCOUT_PRICE;
				pszWeapon = "weapon_scout";
			}
			else
			{
				iWeapon = WEAPON_AK47;
				iWeaponPrice = AK47_PRICE;
				pszWeapon = "weapon_ak47";
			}

			break;
		}
		case 3:
		{
			if (bIsCT)
			{
				iWeapon = WEAPON_M4A1;
				iWeaponPrice = M4A1_PRICE;
				pszWeapon = "weapon_m4a1";
			}
			else
			{
				iWeapon = WEAPON_SCOUT;
				iWeaponPrice = SCOUT_PRICE;
				pszWeapon = "weapon_scout";
			}

			break;
		}
		case 4:
		{
			if (bIsCT)
			{
				iWeapon = WEAPON_AUG;
				iWeaponPrice = AUG_PRICE;
				pszWeapon = "weapon_aug";
			}
			else
			{
				iWeapon = WEAPON_SG552;
				iWeaponPrice = SG552_PRICE;
				pszWeapon = "weapon_sg552";
			}

			break;
		}
		case 5:
		{
			if (bIsCT)
			{
				iWeapon = WEAPON_SG550;
				iWeaponPrice = SG550_PRICE;
				pszWeapon = "weapon_sg550";
			}
			else
			{
				iWeapon = WEAPON_AWP;
				iWeaponPrice = AWP_PRICE;
				pszWeapon = "weapon_awp";
			}

			break;
		}
		case 6:
		{
			if (bIsCT)
			{
				iWeapon = WEAPON_AWP;
				iWeaponPrice = AWP_PRICE;
				pszWeapon = "weapon_awp";
			}
			else
			{
				iWeapon = WEAPON_G3SG1;
				iWeaponPrice = G3SG1_PRICE;
				pszWeapon = "weapon_g3sg1";
			}

			break;
		}
		default:
		{
			if (bIsCT)
			{
				iWeapon = WEAPON_FAMAS;
				iWeaponPrice = FAMAS_PRICE;
				pszWeapon = "weapon_famas";
			}
			else
			{
				iWeapon = WEAPON_GALIL;
				iWeaponPrice = GALIL_PRICE;
				pszWeapon = "weapon_galil";
			}

			break;
		}
	}

	if (!CanBuyThis(pPlayer, iWeapon))
	{
		return;
	}

	if (pPlayer->m_iAccount < iWeaponPrice)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	DropPrimary(pPlayer);

	pPlayer->GiveNamedItem(pszWeapon);
	pPlayer->AddAccount(-iWeaponPrice);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <48bf5> ../cstrike/dlls/client.cpp:1629 */
void BuyMachineGun(CBasePlayer *pPlayer, int iSlot)
{
	int iWeapon = WEAPON_M249;
	int iWeaponPrice = M249_PRICE;
	const char *pszWeapon = "weapon_m249";

	if (!pPlayer->CanPlayerBuy(true))
	{
		return;
	}

	if (iSlot != 1)
	{
		return;
	}

	if (!CanBuyThis(pPlayer, iWeapon))
	{
		return;
	}

	if (pPlayer->m_iAccount < iWeaponPrice)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	DropPrimary(pPlayer);

	pPlayer->GiveNamedItem(pszWeapon);
	pPlayer->AddAccount(-iWeaponPrice);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <473f8> ../cstrike/dlls/client.cpp:1677 */
void BuyItem(CBasePlayer *pPlayer, int iSlot)
{
	//int iItem = 0;
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

	int fullArmor = (pPlayer->pev->armorvalue >= 100);
	int helmet = (pPlayer->m_iKevlar == ARMOR_TYPE_HELMET);
	//int price;
	int enoughMoney = 1;

	switch (iSlot)
	{
		case MENU_SLOT_ITEM_VEST:
		{
			if (fullArmor)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar");
				}

				return;
			}

			if (pPlayer->m_iAccount >= KEVLAR_PRICE)
			{
				if (helmet)
				{
					if (g_bClientPrintEnable)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Helmet_Bought_Kevlar");
					}
				}

				pszItem = "item_kevlar";
				iItemPrice = KEVLAR_PRICE;
			}
			else
				enoughMoney = 0;

			break;
		}
		case MENU_SLOT_ITEM_VESTHELM:
		{
			if (fullArmor)
			{
				if (helmet)
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

					pszItem = "item_assaultsuit";
					iItemPrice = HELMET_PRICE;
				}
				else
					enoughMoney = 0;

				break;
			}
			else
			{
				if (helmet)
				{
					if (pPlayer->m_iAccount >= KEVLAR_PRICE)
					{
						if (g_bClientPrintEnable)
						{
							ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Helmet_Bought_Kevlar");
						}

						pszItem = "item_assaultsuit";
						iItemPrice = KEVLAR_PRICE;
					}
					else
						enoughMoney = 0;
				}
				else
				{
					if (pPlayer->m_iAccount >= ASSAULTSUIT_PRICE)
					{
						pszItem = "item_assaultsuit";
						iItemPrice = ASSAULTSUIT_PRICE;
					}
					else
						enoughMoney = 0;
				}
			}

			break;
		}
		case MENU_SLOT_ITEM_FLASHGREN:
		{
			if (pPlayer->AmmoInventory(pPlayer->GetAmmoIndex("Flashbang")) >= 2)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= FLASHBANG_PRICE)
			{
				pszItem = "weapon_flashbang";
				iItemPrice = FLASHBANG_PRICE;

			}
			else
				enoughMoney = 0;

			break;
		}
		case MENU_SLOT_ITEM_HEGREN:
		{
			if (pPlayer->AmmoInventory(pPlayer->GetAmmoIndex("HEGrenade")) >= 1)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= HEGRENADE_PRICE)
			{
				pszItem = "weapon_hegrenade";
				iItemPrice = HEGRENADE_PRICE;
			}
			else
				enoughMoney = 0;

			break;
		}
		case MENU_SLOT_ITEM_SMOKEGREN:
		{
			if (pPlayer->AmmoInventory(pPlayer->GetAmmoIndex("SmokeGrenade")) >= 1)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= SMOKEGRENADE_PRICE)
			{
				pszItem = "weapon_smokegrenade";
				iItemPrice = SMOKEGRENADE_PRICE;
			}
			else
				enoughMoney = 0;

			break;
		}
		case MENU_SLOT_ITEM_NVG:
		{
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

				pPlayer->m_bHasNightVision = true;
				pPlayer->AddAccount(-NVG_PRICE);

				SendItemStatus(pPlayer);
			}
			else
				enoughMoney = 0;

			break;
		}
		case MENU_SLOT_ITEM_DEFUSEKIT:
		{
			if (pPlayer->m_iTeam != CT || !g_pGameRules->m_bMapHasBombTarget)
			{
				return;
			}

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
				pPlayer->m_bHasDefuser = true;

				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pPlayer->pev);
					WRITE_BYTE(STATUSICON_SHOW);
					WRITE_STRING("defuser");
					WRITE_BYTE(0);
					WRITE_BYTE(160);
					WRITE_BYTE(0);
				MESSAGE_END();

				pPlayer->pev->body = 1;
				pPlayer->AddAccount(-DEFUSEKIT_PRICE);

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/kevlar.wav", VOL_NORM, ATTN_NORM);
				SendItemStatus(pPlayer);
			}
			else
				enoughMoney = 0;

			break;
		}
		case MENU_SLOT_ITEM_SHIELD:
		{
			if (!CanBuyThis(pPlayer, WEAPON_SHIELDGUN))
			{
				return;
			}

			if (pPlayer->m_iAccount >= SHIELDGUN_PRICE)
			{
				DropPrimary(pPlayer);

				pPlayer->GiveShield(true);
				pPlayer->AddAccount(-SHIELDGUN_PRICE);

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);
			}
			else
				enoughMoney = 0;

			break;
		}
	}

	if (!enoughMoney)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);
		}

		return;
	}

	if (pszItem != NULL)
	{
		pPlayer->GiveNamedItem(pszItem);
		pPlayer->AddAccount(-iItemPrice);
	}

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

/* <48d40> ../cstrike/dlls/client.cpp:1998 */
void HandleMenu_ChooseAppearance(CBasePlayer *player, int slot)
{
	CHalfLifeMultiplay *mp = g_pGameRules;
	int numSkins = UTIL_IsGame("czero") ? CZ_NUM_SKIN : CS_NUM_SKIN;

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
			if (UTIL_IsGame("czero"))
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
			if (UTIL_IsGame("czero"))
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

	player->m_iMenu = Menu_OFF;

	// Reset the player's state
	if (player->m_iJoiningState == JOINED)
	{
		mp->CheckWinConditions();
	}
	else if (player->m_iJoiningState == PICKINGTEAM)
	{
		player->m_iJoiningState = GETINTOGAME;

		if (mp->IsCareer())
		{
			if (!player->IsBot())
			{
				mp->CheckWinConditions();
			}
		}
	}

	player->pev->body = 0;
	player->m_iModelName = appearance.model_id;

	SET_CLIENT_KEY_VALUE(player->entindex(), GET_INFO_BUFFER(player->edict()), "model", appearance.model_name);
	player->SetNewPlayerModel(sPlayerModelFiles[ appearance.model_name_index ]);

	if (mp->m_iMapHasVIPSafetyZone == MAP_VIP_SAFETYZONE_UNINITIALIZED)
	{
		if ((UTIL_FindEntityByClassname(NULL, "func_vip_safetyzone")) != NULL)
			mp->m_iMapHasVIPSafetyZone = MAP_HAVE_VIP_SAFETYZONE_YES;
		else
			mp->m_iMapHasVIPSafetyZone = MAP_HAVE_VIP_SAFETYZONE_NO;
	}

	if (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES)
	{
		if (!mp->m_pVIP && player->m_iTeam == CT)
		{
			player->MakeVIP();
		}
	}
}

// returns true if the selection has been handled and the player's menu
// can be closed...false if the menu should be displayed again

/* <48e4b> ../cstrike/dlls/client.cpp:2214 */
BOOL HandleMenu_ChooseTeam(CBasePlayer *player, int slot)
{
	CHalfLifeMultiplay *mp = g_pGameRules;

	int oldTeam;
	char *szOldTeam;
	char *szNewTeam;

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
		else if (g_pGameRules->IsVIPQueueEmpty())
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
		if (mp->m_iMapHasVIPSafetyZone != MAP_HAVE_VIP_SAFETYZONE_YES || player->m_iTeam != CT)
		{
			return FALSE;
		}

		mp->AddToVIPQueue(player);
		CLIENT_COMMAND(ENT(player->pev), "slot10\n");
		return TRUE;
	}
	case MENU_SLOT_TEAM_RANDOM:
	{
		// Attempt to auto-select a team
		team = SelectDefaultTeam();

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
		if (mp->IsFreezePeriod() || player->pev->deadflag != DEAD_NO)
		{
			if (player->m_iTeam != UNASSIGNED && player->pev->deadflag == DEAD_NO)
			{
				ClientKill(player->edict());

				// add 1 to frags to balance out the 1 subtracted for killing yourself
				player->pev->frags++;
			}

			player->RemoveAllItems(TRUE);
			player->m_bHasC4 = false;

			if (player->m_iTeam != SPECTATOR)
			{
				// notify other clients of player joined to team spectator
				UTIL_LogPrintf
				(
					"\"%s<%i><%s><%s>\" joined team \"SPECTATOR\"\n",
					STRING(player->pev->netname),
					GETPLAYERUSERID(player->edict()),
					GETPLAYERAUTHID(player->edict()),
					GetTeam(player->m_iTeam)
				);
			}

			player->m_iTeam = SPECTATOR;
			player->m_iJoiningState = JOINED;

			// Reset money
			player->m_iAccount = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgMoney, NULL, player->pev);
				WRITE_LONG(player->m_iAccount);
				WRITE_BYTE(0);
			MESSAGE_END();

			MESSAGE_BEGIN(MSG_BROADCAST, gmsgScoreInfo);
				WRITE_BYTE(ENTINDEX(player->edict()));
				WRITE_SHORT((int)player->pev->frags);
				WRITE_SHORT(player->m_iDeaths);
				WRITE_SHORT(0);
				WRITE_SHORT(0);
			MESSAGE_END();

			player->m_pIntroCamera = NULL;
			player->m_bTeamChanged = true;

			TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, player);

			TeamChangeUpdate(player, player->m_iTeam);

			edict_t *pentSpawnSpot = mp->GetPlayerSpawnSpot(player);
			player->StartObserver(VARS(pentSpawnSpot)->origin, VARS(pentSpawnSpot)->angles);

			MESSAGE_BEGIN(MSG_ALL, gmsgSpectator);
				WRITE_BYTE(ENTINDEX(player->edict()));
				WRITE_BYTE(1);
			MESSAGE_END();

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

	if (mp->TeamFull(team))
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
	if (mp->TeamStacked(team, player->m_iTeam))
	{
		// The specified team is full
		ClientPrint(player->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Too_Many_Terrorists" : "#Too_Many_CTs");
		return FALSE;
	}

	if (team != SPECTATOR && !player->IsBot())
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
			ClientPrint(player->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Humans_Join_Team_CT" : "#Humans_Join_Team_T");
			return FALSE;
		}
	}

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
		player->m_iAccount = (int)startmoney.value;

		player->pev->solid = SOLID_NOT;
		player->pev->movetype = MOVETYPE_NOCLIP;
		player->pev->effects = EF_NODRAW;
		player->pev->effects |= EF_NOINTERP;
		player->pev->takedamage = DAMAGE_NO;
		player->pev->deadflag = DEAD_DEAD;
		player->pev->velocity = g_vecZero;
		player->pev->punchangle = g_vecZero;

		player->m_bHasNightVision = false;
		player->m_iHostagesKilled = 0;
		player->m_fDeadTime = 0;
		player->has_disconnected = false;

		player->m_iJoiningState = GETINTOGAME;

		SendItemStatus(player);
		SET_CLIENT_MAXSPEED(ENT(player->pev), 1);
		SET_MODEL(ENT(player->pev), "models/player.mdl");
	}

	if (!g_pGameRules->IsCareer())
	{
		bool isCZero = UTIL_IsGame("czero");

		switch (team)
		{
		case CT:
			if (isCZero)
				ShowVGUIMenu(player, VGUI_Menu_Class_CT, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6), "#CT_Select");
			else
				ShowVGUIMenu(player, VGUI_Menu_Class_CT, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5), "#CT_Select");
			break;

		case TERRORIST:
			if (isCZero)
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

	// Switch their actual team...
	player->m_bTeamChanged = true;
	oldTeam = player->m_iTeam;
	player->m_iTeam = team;

	TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, player);

	TeamChangeUpdate(player, team);

	szOldTeam = GetTeam(oldTeam);
	szNewTeam = GetTeam(team);

	// Notify others that this player has joined a new team
	UTIL_ClientPrintAll
	(
		HUD_PRINTNOTIFY,
		(team == TERRORIST) ? "#Game_join_terrorist" : "#Game_join_ct",
		(STRING(player->pev->netname) && STRING(player->pev->netname)[0] != 0) ? STRING(player->pev->netname) : "<unconnected>"
	);

	UTIL_LogPrintf
	(
		"\"%s<%i><%s><%s>\" joined team \"%s\"\n",
		STRING(player->pev->netname),
		GETPLAYERUSERID(player->edict()),
		GETPLAYERAUTHID(player->edict()),
		szOldTeam,
		szNewTeam
	);

	return TRUE;
}

/* <474a0> ../cstrike/dlls/client.cpp:2553 */
void Radio1(CBasePlayer *player, int slot)
{
	if (player->m_flRadioTime >= gpGlobals->time)
	{
		return;
	}

	if (player->m_iRadioMessages <= 0)
	{
		return;
	}

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

	TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_1 + slot), player);
}

/* <474ca> ../cstrike/dlls/client.cpp:2596 */
void Radio2(CBasePlayer *player, int slot)
{
	if (player->m_flRadioTime >= gpGlobals->time)
	{
		return;
	}

	if (player->m_iRadioMessages <= 0)
	{
		return;
	}

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

	TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_2 + slot), player);
}

/* <474f4> ../cstrike/dlls/client.cpp:2639 */
void Radio3(CBasePlayer *player, int slot)
{
	if (player->m_flRadioTime >= gpGlobals->time)
	{
		return;
	}

	if (player->m_iRadioMessages <= 0)
	{
		return;
	}

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

	TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_3 + slot), player);
}

/* <49402> ../cstrike/dlls/client.cpp:2698 */
bool BuyGunAmmo(CBasePlayer *player, CBasePlayerItem *weapon, bool bBlinkMoney)
{
	int cost;
	const char *classname;

	if (!player->CanPlayerBuy(true))
	{
		return false;
	}

	// Ensure that the weapon uses ammo
	int nAmmo = weapon->PrimaryAmmoIndex();
	if (nAmmo == -1)
	{
		return false;
	}

	// Can only buy if the player does not already have full ammo
	if (player->m_rgAmmo[ nAmmo ] >= weapon->iMaxAmmo1())
	{
		return false;
	}

	switch (weapon->m_iId)
	{
	case WEAPON_AWP:
		cost = AMMO_338MAG_PRICE;
		classname = "ammo_338magnum";
		break;
	case WEAPON_SCOUT:
	case WEAPON_G3SG1:
	case WEAPON_AK47:
		cost = AMMO_762MM_PRICE;
		classname = "ammo_762nato";
		break;
	case WEAPON_XM1014:
	case WEAPON_M3:
		cost = AMMO_BUCKSHOT_PRICE;
		classname = "ammo_buckshot";
		break;
	case WEAPON_MAC10:
	case WEAPON_UMP45:
	case WEAPON_USP:
		cost = AMMO_45ACP_PRICE;
		classname = "ammo_45acp";
		break;
	case WEAPON_M249:
		cost = AMMO_556MM_PRICE;
		classname = "ammo_556natobox";
		break;
	case WEAPON_FIVESEVEN:
	case WEAPON_P90:
		cost = AMMO_57MM_PRICE;
		classname = "ammo_57mm";
		break;
	case WEAPON_ELITE:
	case WEAPON_GLOCK18:
	case WEAPON_MP5N:
	case WEAPON_TMP:
		cost = AMMO_9MM_PRICE;
		classname = "ammo_9mm";
		break;
	case WEAPON_DEAGLE:
		cost = AMMO_50AE_PRICE;
		classname = "ammo_50ae";
		break;
	case WEAPON_P228:
		cost = AMMO_357SIG_PRICE;
		classname = "ammo_357sig";
		break;
	case WEAPON_AUG:
	case WEAPON_SG550:
	case WEAPON_GALIL:
	case WEAPON_FAMAS:
	case WEAPON_M4A1:
	case WEAPON_SG552:
		cost = AMMO_556MM_PRICE;
		classname = "ammo_556nato";
		break;
	default:
		ALERT(at_console, "Tried to buy ammo for an unrecognized gun\n");
		return false;
	}

	// Purchase the ammo if the player has enough money
	if (player->m_iAccount >= cost)
	{
		player->GiveNamedItem(classname);
		player->AddAccount(-cost);
		return true;
	}

	if (bBlinkMoney)
	{
		if (g_bClientPrintEnable)
		{
			// Not enough money.. let the player know
			ClientPrint(player->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(player, 2);
		}
	}

	return false;
}

/* <4751e> ../cstrike/dlls/client.cpp:2884 */
bool BuyAmmo(CBasePlayer *player, int nSlot, bool bBlinkMoney)
{
	if (!player->CanPlayerBuy(true))
	{
		return false;
	}

	if (nSlot < PRIMARY_WEAPON_SLOT || nSlot > PISTOL_SLOT)
	{
		return false;
	}

	// Buy one ammo clip for all weapons in the given slot
	//
	//  nSlot == 1 : Primary weapons
	//  nSlot == 2 : Secondary weapons

	CBasePlayerItem *pItem = player->m_rgpPlayerItems[ nSlot ];

	if (player->HasShield())
	{
		if (player->m_rgpPlayerItems[ PISTOL_SLOT ])
			pItem = player->m_rgpPlayerItems[ PISTOL_SLOT ];
	}

	if (pItem != NULL)
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

/* <4bb4a> ../cstrike/dlls/client.cpp:2933 */
CBaseEntity *EntityFromUserID(int userID)
{
	CBaseEntity *pTempEntity = NULL;

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")) != NULL)
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		CBasePlayer *pTempPlayer = GetClassPtr((CBasePlayer *)pTempEntity->pev);

		if (pTempPlayer->m_iTeam != UNASSIGNED && userID == GETPLAYERUSERID(pTempEntity->edict()))
		{
			return pTempPlayer;
		}
	}

	return NULL;
}

/* <4baa5> ../cstrike/dlls/client.cpp:2958 */
NOXREF int CountPlayersInServer(void)
{
	int count = 0;
	CBaseEntity *pTempEntity = NULL;

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")) != NULL)
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		CBasePlayer *pTempPlayer = GetClassPtr((CBasePlayer *)pTempEntity->pev);

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

/* <4958c> ../cstrike/dlls/client.cpp:2983 */
BOOL HandleBuyAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	// Let them buy it if it's got a weapon data string.
	BOOL bRetVal = FALSE;
	const char *pszFailItem = NULL;

	WeaponIdType weaponID = WEAPON_NONE;
	const char *weaponFailName = BuyAliasToWeaponID(pszCommand, weaponID);

	if (weaponID != WEAPON_NONE)
	{
		// Ok, we have weapon info ID.
		// assasination maps have a specific set of weapons that can be used in them.
		if (CanBuyWeaponByMaptype(pPlayer->m_iTeam, weaponID, (g_pGameRules->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES)))
		{
			bRetVal = TRUE;
			BuyWeaponByWeaponID(pPlayer, weaponID);
		}
		else if (weaponFailName != NULL)
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

				if (TheTutor != NULL)
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

				if (TheTutor != NULL)
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

	if (g_bClientPrintEnable && pszFailItem != NULL)
	{
		ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Alias_Not_Avail", pszFailItem);
	}

	pPlayer->BuildRebuyStruct();
	return bRetVal;
}

/* <49c3e> ../cstrike/dlls/client.cpp:3113 */
BOOL HandleRadioAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	BOOL bRetVal = FALSE;

	if (FStrEq(pszCommand, "coverme"))
	{
		bRetVal = TRUE;
		Radio1(pPlayer, 1);
	}
	else if (FStrEq(pszCommand, "takepoint"))
	{
		bRetVal = TRUE;
		Radio1(pPlayer, 2);
	}
	else if (FStrEq(pszCommand, "holdpos"))
	{
		bRetVal = TRUE;
		Radio1(pPlayer, 3);
	}
	else if (FStrEq(pszCommand, "regroup"))
	{
		bRetVal = TRUE;
		Radio1(pPlayer, 4);
	}
	else if (FStrEq(pszCommand, "followme"))
	{
		bRetVal = TRUE;
		Radio1(pPlayer, 5);
	}
	else if (FStrEq(pszCommand, "takingfire"))
	{
		bRetVal = TRUE;
		Radio1(pPlayer, 6);
	}
	else if (FStrEq(pszCommand, "go"))
	{
		bRetVal = TRUE;
		Radio2(pPlayer, 1);
	}
	else if (FStrEq(pszCommand, "fallback"))
	{
		bRetVal = TRUE;
		Radio2(pPlayer, 2);
	}
	else if (FStrEq(pszCommand, "sticktog"))
	{
		bRetVal = TRUE;
		Radio2(pPlayer, 3);
	}
	else if (FStrEq(pszCommand, "getinpos"))
	{
		bRetVal = TRUE;
		Radio2(pPlayer, 4);
	}
	else if (FStrEq(pszCommand, "stormfront"))
	{
		bRetVal = TRUE;
		Radio2(pPlayer, 5);
	}
	else if (FStrEq(pszCommand, "report"))
	{
		bRetVal = TRUE;
		Radio2(pPlayer, 6);
	}
	else if (FStrEq(pszCommand, "roger"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 1);
	}
	else if (FStrEq(pszCommand, "enemyspot"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 2);
	}
	else if (FStrEq(pszCommand, "needbackup"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 3);
	}
	else if (FStrEq(pszCommand, "sectorclear"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 4);
	}
	else if (FStrEq(pszCommand, "inposition"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 5);
	}
	else if (FStrEq(pszCommand, "reportingin"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 6);
	}
	else if (FStrEq(pszCommand, "getout"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 7);
	}
	else if (FStrEq(pszCommand, "negative"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 8);
	}
	else if (FStrEq(pszCommand, "enemydown"))
	{
		bRetVal = TRUE;
		Radio3(pPlayer, 9);
	}

	return bRetVal;
}

// Use CMD_ARGV,  CMD_ARGV, and CMD_ARGC to get pointers the character string command.

/* <4c6c1> ../cstrike/dlls/client.cpp:3234 */
void ClientCommand(edict_t *pEntity)
{
	const char *pcmd = CMD_ARGV_(0);
	const char *pstr = NULL;
	CHalfLifeMultiplay *mp = g_pGameRules;

	// Is the client spawned yet?
	if (!pEntity->pvPrivateData)
		return;

	entvars_t *pev = &pEntity->v;
	CBasePlayer *player = GetClassPtr((CBasePlayer *)pev);

	if (FStrEq(pcmd, "say"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[0])
		{
			player->m_flLastCommandTime[0] = gpGlobals->time + 0.3f;
			Host_Say(pEntity, 0);
		}
	}
	else if (FStrEq(pcmd, "say_team"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[1])
		{
			player->m_flLastCommandTime[1] = gpGlobals->time + 0.3f;
			Host_Say(pEntity, 1);
		}
	}
	else if (FStrEq(pcmd, "fullupdate"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[2])
		{
			player->m_flLastCommandTime[2] = gpGlobals->time + 0.6f;
			player->ForceClientDllUpdate();
		}
	}
	else if (FStrEq(pcmd, "vote"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[3])
		{
			player->m_flLastCommandTime[3] = gpGlobals->time + 0.3f;

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
				const char *pszArg1 = CMD_ARGV_(1);
				int iVoteLength = Q_strlen(pszArg1);

				if (iNumArgs != 2 || iVoteLength <= 0 || iVoteLength > 6)
				{
					iVoteFail = 1;
				}

				iVoteID = Q_atoi(pszArg1);
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
				if (pKickEntity != NULL)
				{
					CBasePlayer *pKickPlayer = GetClassPtr((CBasePlayer *)pKickEntity->pev);

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
		if (gpGlobals->time >= player->m_flLastCommandTime[5])
		{
			player->m_flLastCommandTime[5] = gpGlobals->time + 0.3f;
			mp->DisplayMaps(player, 0);
		}
	}
	else if (FStrEq(pcmd, "votemap"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[4])
		{
			player->m_flLastCommandTime[4] = gpGlobals->time + 0.3f;

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
				const char *pszArg1 = CMD_ARGV_(1);
				int iVoteLength = Q_strlen(pszArg1);

				if (iNumArgs != 2 || iVoteLength > 5)
				{
					iFailed = 1;
				}

				int iVoteID = Q_atoi(pszArg1);
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
					mp->DisplayMaps(player, 0);
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
					mp->m_iMapVotes[ player->m_iMapVote ]--;

					if (mp->m_iMapVotes[player->m_iMapVote] < 0)
					{
						mp->m_iMapVotes[player->m_iMapVote] = 0;
					}
				}

				ClientPrint(player->pev, HUD_PRINTCONSOLE, "#Game_voted_for_map", UTIL_dtos1(iVoteID));
				player->m_iMapVote = iVoteID;
				mp->ProcessMapVote(player, iVoteID);
			}
		}
	}
	else if (FStrEq(pcmd, "timeleft"))
	{
		if (gpGlobals->time > player->m_iTimeCheckAllowed)
		{
			player->m_iTimeCheckAllowed = (int)(gpGlobals->time + 1);

			if (!timelimit.value)
			{
				ClientPrint(player->pev, HUD_PRINTTALK, "#Game_no_timelimit");
				return;
			}

			int iTimeRemaining = (int)(g_flTimeLimit - gpGlobals->time);

			if (iTimeRemaining < 0)
				iTimeRemaining = 0;

			int iMinutes = (int)(iTimeRemaining % 60);
			int iSeconds = (int)(iTimeRemaining / 60);

			char secs[5];
			char *temp = UTIL_dtos2(iMinutes);

			if (iMinutes >= 10)
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

			ClientPrint(player->pev, HUD_PRINTTALK, "#Game_timelimit", UTIL_dtos1(iSeconds), secs);
		}
	}
	else if (FStrEq(pcmd, "listplayers"))
	{
		if (gpGlobals->time >= player->m_flLastCommandTime[6])
		{
			player->m_flLastCommandTime[6] = gpGlobals->time + 0.3f;
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
		int slot = Q_atoi(CMD_ARGV_(1));

		if (player->m_iJoiningState == JOINED || (player->m_iMenu != SPECTATOR && player->m_iMenu != TERRORIST))
		{
			if (slot == 10)
			{
				player->m_iMenu = Menu_OFF;
			}
		}

		switch (player->m_iMenu)
		{
			case Menu_OFF:
				break;

			case Menu_ChooseTeam:
			{
				if (!player->m_bVGUIMenus && !HandleMenu_ChooseTeam(player, slot))
				{
					if (player->m_iJoiningState == JOINED)
						ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
					else
						ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5), "#Team_Select");

					player->m_iMenu = Menu_ChooseTeam;
				}
				break;
			}
			case Menu_IGChooseTeam:
			{
				if (!player->m_bVGUIMenus)
				{
					HandleMenu_ChooseTeam(player, slot);
				}
				break;
			}
			case Menu_ChooseAppearance:
			{
				if (!player->m_bVGUIMenus)
				{
					HandleMenu_ChooseAppearance(player, slot);
				}
				break;
			}
			case Menu_Buy:
			{
				if (!player->m_bVGUIMenus)
				{
					switch (slot)
					{
						case VGUI_MenuSlot_Buy_Pistol:
						{
							if (player->m_iTeam == CT)
								ShowVGUIMenu(player, VGUI_Menu_Buy_Pistol, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#CT_BuyPistol");
							else
								ShowVGUIMenu(player, VGUI_Menu_Buy_Pistol, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#T_BuyPistol");

							player->m_iMenu = Menu_BuyPistol;
							break;
						}
						case VGUI_MenuSlot_Buy_ShotGun:
						{
							if (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES && player->m_iTeam == TERRORIST)
								ShowVGUIMenu(player, VGUI_Menu_Buy_ShotGun, MENU_KEY_0, "#AS_BuyShotgun");
							else
								ShowVGUIMenu(player, VGUI_Menu_Buy_ShotGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_0), "#BuyShotgun");

							player->m_iMenu = Menu_BuyShotgun;
							break;
						}
						case VGUI_MenuSlot_Buy_SubMachineGun:
						{
							if (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES)
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

							player->m_iMenu = Menu_BuySubMachineGun;
							break;
						}
						case VGUI_MenuSlot_Buy_Rifle:
						{
							if (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES)
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

							player->m_iMenu = Menu_BuyRifle;
							break;
						}
						case VGUI_MenuSlot_Buy_MachineGun:
						{
							if (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES && player->m_iTeam == TERRORIST)
								ShowVGUIMenu(player, VGUI_Menu_Buy_MachineGun, MENU_KEY_0, "#AS_T_BuyMachineGun");
							else
								ShowVGUIMenu(player, VGUI_Menu_Buy_MachineGun, (MENU_KEY_1 | MENU_KEY_0), "#BuyMachineGun");

							player->m_iMenu = Menu_BuyMachineGun;
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
						}
						case VGUI_MenuSlot_Buy_Item:
						{
							if (player->m_signals.GetState() & SIGNAL_BUY)
							{
								if (mp->m_bMapHasBombTarget)
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
							break;
						}
					}
				}
				break;
			}
			case Menu_BuyPistol:
			{
				if (!player->m_bVGUIMenus)
				{
					BuyPistol(player, slot);
				}
				break;
			}
			case Menu_BuyShotgun:
			{
				if (!player->m_bVGUIMenus)
				{
					BuyShotgun(player, slot);
				}
				break;
			}
			case Menu_BuySubMachineGun:
			{
				if (!player->m_bVGUIMenus)
				{
					BuySubMachineGun(player, slot);
				}
				break;
			}
			case Menu_BuyRifle:
			{
				if (!player->m_bVGUIMenus)
				{
					BuyRifle(player, slot);
				}
				break;
			}
			case Menu_BuyMachineGun:
			{
				if (!player->m_bVGUIMenus)
				{
					BuyMachineGun(player, slot);
				}
				break;
			}
			case Menu_BuyItem:
			{
				if (!player->m_bVGUIMenus)
				{
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
		{
			return;
		}

		if (player->m_bTeamChanged)
		{
			if (player->pev->deadflag != DEAD_NO)
			{
				ClientPrint(player->pev, HUD_PRINTCENTER, "#Only_1_Team_Change");
				return;
			}
		}

		if (!mp->IsCareer())
		{
			if (mp->m_iMapHasVIPSafetyZone == MAP_HAVE_VIP_SAFETYZONE_YES && player->m_iJoiningState == JOINED && player->m_iTeam == CT)
			{
				if (mp->IsFreezePeriod() || player->pev->deadflag != DEAD_NO)
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#IG_VIP_Team_Select_Spect");
				else
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_5 | MENU_KEY_0), "#IG_VIP_Team_Select");
			}
			else
			{
				if (mp->IsFreezePeriod() || player->pev->deadflag != DEAD_NO)
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#IG_Team_Select_Spect");
				else
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
			}

			player->m_iMenu = Menu_ChooseTeam;
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

		mp->AddToVIPQueue(player);
	}
	else if (FStrEq(pcmd, "spectate") && (player->pev->flags & FL_PROXY)) // always allow proxies to become a spectator
	{
		// clients wants to become a spectator
		HandleMenu_ChooseTeam(player, MENU_SLOT_TEAM_SPECT);
	}
	else if (FStrEq(pcmd, "specmode"))
	{
		// new spectator mode
		int mode = Q_atoi(CMD_ARGV_(1));

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
		float val = Q_atof(CMD_ARGV_(1));
		player->SetObserverAutoDirector(val > 0.0f);
	}
	else if (FStrEq(pcmd, "follownext"))
	{
		// follow next player
		int arg = Q_atoi(CMD_ARGV_(1));

		if (player->IsObserver() && player->CanSwitchObserverModes())
		{
			player->Observer_FindNextPlayer(arg != 0);
		}
	}
	else if (FStrEq(pcmd, "follow"))
	{
		if (player->IsObserver() && player->CanSwitchObserverModes())
		{
			player->Observer_FindNextPlayer(false, CMD_ARGV_(1));
		}
	}
	else
	{
		if (mp->ClientCommand_DeadOrAlive(GetClassPtr((CBasePlayer *)pev), pcmd))
			return;

		if (TheBots->ClientCommand(GetClassPtr((CBasePlayer *)pev), pcmd))
			return;

		if (FStrEq(pcmd, "mp_debug"))
		{
			UTIL_SetDprintfFlags(CMD_ARGV_(1));
		}
		else if (FStrEq(pcmd, "jointeam"))
		{
			if (player->m_iMenu == Menu_ChooseAppearance)
			{
				ClientPrint(player->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}

			int slot = Q_atoi(CMD_ARGV_(1));
			if (HandleMenu_ChooseTeam(player, slot))
			{
				if (slot == MENU_SLOT_TEAM_VIP || slot == MENU_SLOT_TEAM_SPECT || player->m_bIsVIP)
				{
					player->m_iMenu = Menu_OFF;
				}
				else
					player->m_iMenu = Menu_ChooseAppearance;
			}
			else
			{
				if (player->m_iJoiningState == JOINED)
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
				else
					ShowVGUIMenu(player, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5), "#Team_Select");

				player->m_iMenu = Menu_ChooseTeam;
			}
		}
		else if (FStrEq(pcmd, "joinclass"))
		{
			int slot = Q_atoi(CMD_ARGV_(1));

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
				if (gpGlobals->time >= player->m_flLastCommandTime[7])
				{
					player->m_flLastCommandTime[7] = gpGlobals->time + 0.3f;

					if (!player->m_bHasNightVision)
						return;

					if (player->m_bNightVisionOn)
					{
						EMIT_SOUND(ENT(player->pev), CHAN_ITEM, "items/nvg_off.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

						MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, player->pev);
							WRITE_BYTE(0); // disable nightvision
						MESSAGE_END();

						player->m_bNightVisionOn = false;

						for (int i = 1; i <= gpGlobals->maxClients; i++)
						{
							CBasePlayer *pObserver = (CBasePlayer *)UTIL_PlayerByIndex(i);

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

						for (int i = 1; i <= gpGlobals->maxClients; i++)
						{
							CBasePlayer *pObserver = (CBasePlayer *)UTIL_PlayerByIndex(i);

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
					player->DropPlayerItem(CMD_ARGV_(1));
			}
			else if (FStrEq(pcmd, "fov"))
			{
#if 0
				if (g_flWeaponCheat && CMD_ARGC() > 1)
					GetClassPtr((CBasePlayer *)pev)->m_iFOV = Q_atoi(CMD_ARGV(1));
				else
					CLIENT_PRINTF(pEntity, print_console, UTIL_VarArgs("\"fov\" is \"%d\"\n", (int)GetClassPtr((CBasePlayer *)pev)->m_iFOV));
#endif
			}
			else if (FStrEq(pcmd, "use"))
			{
				GetClassPtr((CBasePlayer *)pev)->SelectItem(CMD_ARGV_(1));
			}
			else if (((pstr = Q_strstr(pcmd, "weapon_")) != NULL) && (pstr == pcmd))
			{
				GetClassPtr((CBasePlayer *)pev)->SelectItem(pcmd);
			}
			else if (FStrEq(pcmd, "lastinv"))
			{
				GetClassPtr((CBasePlayer *)pev)->SelectLastItem();
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
					if (mp->m_bMapHasBombTarget)
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

				for (int i = 1; i < CMD_ARGC_(); i++)
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
					player->InitRebuyData(CMD_ARGV_(1));

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

				if (!g_pGameRules->ClientCommand(GetClassPtr((CBasePlayer *)pev), pcmd))
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

/* <4b959> ../cstrike/dlls/client.cpp:4282 */
void ClientUserInfoChanged(edict_t *pEntity, char *infobuffer)
{
	// Is the client spawned yet?
	if (!pEntity->pvPrivateData)
	{
		return;
	}

	CBasePlayer *pPlayer = (CBasePlayer *)CBaseEntity::Instance(pEntity);

	char *szBufferName = GET_KEY_VALUE(infobuffer, "name");
	int iClientIndex = pPlayer->entindex();

	// msg everyone if someone changes their name,  and it isn't the first time (changing no name to current name)
	if (pEntity->v.netname && STRING(pEntity->v.netname)[0] != '\0' && !FStrEq(STRING(pEntity->v.netname), szBufferName))
	{
		char szName[32];
		Q_snprintf(szName, sizeof(szName), "%s", szBufferName);

		// First parse the name and remove any %'s
		for (char *pPct = szName; pPct != NULL && *pPct != '\0'; pPct++)
		{
			// Replace it with a space
			if (*pPct == '%' || *pPct == '&')
				*pPct = ' ';
		}

		if (szName[0] == '#')
			szName[0] = '*';

		if (pPlayer->pev->deadflag != DEAD_NO)
		{
			pPlayer->m_bHasChangedName = true;
			Q_snprintf(pPlayer->m_szNewName, sizeof(pPlayer->m_szNewName), "%s", szName);
			ClientPrint(pPlayer->pev, HUD_PRINTTALK, "#Name_change_at_respawn");
			SET_CLIENT_KEY_VALUE(iClientIndex, infobuffer, "name", (char *)STRING(pEntity->v.netname));
		}
		else
		{
			// Set the name
			SET_CLIENT_KEY_VALUE(iClientIndex, infobuffer, "name", szName);

			MESSAGE_BEGIN(MSG_BROADCAST, gmsgSayText);
				WRITE_BYTE(iClientIndex);
				WRITE_STRING("#Cstrike_Name_Change");
				WRITE_STRING(STRING(pEntity->v.netname));
				WRITE_STRING(szName);
			MESSAGE_END();

			UTIL_LogPrintf
			(
				"\"%s<%i><%s><%s>\" changed name to \"%s\"\n",
				STRING(pEntity->v.netname),
				GETPLAYERUSERID(pEntity),
				GETPLAYERAUTHID(pEntity),
				GetTeam(pPlayer->m_iTeam),
				szName
			);
		}
	}

	g_pGameRules->ClientUserInfoChanged(GetClassPtr((CBasePlayer *)&pEntity->v), infobuffer);
}

/* <4a378> ../cstrike/dlls/client.cpp:4362 */
void ServerDeactivate(void)
{
	// It's possible that the engine will call this function more times than is necessary
	//  Therefore, only run it one time for each call to ServerActivate
	if (g_serveractive != 1)
	{
		return;
	}

	g_serveractive = 0;

	// Peform any shutdown operations here...
	g_pGameRules->ServerDeactivate();
	CLocalNav::Reset();
	TheBots->ServerDeactivate();

	if (g_pHostages)
	{
		g_pHostages->ServerDeactivate();
	}
}

/* <4a392> ../cstrike/dlls/client.cpp:4400 */
void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	int i;
	CBaseEntity *pClass;

	// Every call to ServerActivate should be matched by a call to ServerDeactivate
	g_serveractive = 1;
	EmptyEntityHashTable();

	// Clients have not been initialized yet
	for (i = 0; i < edictCount; i++)
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

	TheBots->ServerActivate();

	if (g_pHostages)
	{
		g_pHostages->ServerActivate();
	}
}

/* <4a404> ../cstrike/dlls/client.cpp:4459 */
void PlayerPreThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->PreThink();
	}
}

/* <4a47c> ../cstrike/dlls/client.cpp:4475 */
void PlayerPostThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->PostThink();
	}
}

/* <4a4f4> ../cstrike/dlls/client.cpp:4486 */
void ParmsNewLevel(void)
{
	;
}

/* <4a50d> ../cstrike/dlls/client.cpp:4491 */
void ParmsChangeLevel(void)
{
	// retrieve the pointer to the save data
	SAVERESTOREDATA *pSaveData = (SAVERESTOREDATA *)gpGlobals->pSaveData;

	if (pSaveData)
	{
		pSaveData->connectionCount = BuildChangeList(pSaveData->levelList, MAX_LEVEL_CONNECTIONS);
	}
}

/* <4a548> ../cstrike/dlls/client.cpp:4504 */
void StartFrame(void)
{
	if (g_pGameRules != NULL)
	{
		g_pGameRules->Think();
	}

	if (g_fGameOver)
		return;

	CLocalNav::Think();

	static cvar_t *skill = NULL;
	if (!skill)
	{
		skill = CVAR_GET_POINTER("skill");
	}

	gpGlobals->teamplay = 1.0f;

	if (skill != NULL)
		g_iSkillLevel = (int)skill->value;

	else
		g_iSkillLevel = 0;

	TheBots->StartFrame();

	if (TheTutor)
	{
		TheTutor->StartFrame(gpGlobals->time);
	}

	++g_ulFrameCount;
}

/* <4a581> ../cstrike/dlls/client.cpp:4534 */
void ClientPrecache(void)
{
	int i;
	bool isCZero = UTIL_IsGame("czero");

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
	if (isCZero)
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles);
	else
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles) - 2;

	for (i = 0; i < numPlayerModels; i++)
		PRECACHE_MODEL(sPlayerModelFiles[i]);

	for (i = FirstCustomSkin; i <= LastCustomSkin; i++)
	{
		const char *fname = TheBotProfiles->GetCustomSkinFname(i);

		if (!fname)
			break;

		PRECACHE_MODEL((char *)fname);
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
	Vector vMin = Vector(-38, -24, -41);
	Vector vMax = Vector(38, 24, 41);

	for (i = 0; i < numPlayerModels; i++)
		ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, sPlayerModelFiles[i]);

	for (i = FirstCustomSkin; i <= LastCustomSkin; i++)
	{
		const char *fname = TheBotProfiles->GetCustomSkinFname(i);

		if (!fname)
			break;

		ENGINE_FORCE_UNMODIFIED(force_model_specifybounds_if_avail, (float *)&vMin, (float *)&vMax, fname);
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

/* <4a6e5> ../cstrike/dlls/client.cpp:4996 */
const char *GetGameDescription(void)
{
	if (UTIL_IsGame("czero"))
		return "Condition Zero";

	return "Counter-Strike";
}

/* <4a703> ../cstrike/dlls/client.cpp:5022 */
void Sys_Error(const char *error_string)
{
	;
}

/* <4a731> ../cstrike/dlls/client.cpp:5039 */
void PlayerCustomization(edict_t *pEntity, customization_t *pCust)
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

/* <4a7b9> ../cstrike/dlls/client.cpp:5079 */
void SpectatorConnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorConnect();
	}
}

/* <4a83d> ../cstrike/dlls/client.cpp:5095 */
void SpectatorDisconnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorDisconnect();
	}
}

/* <4a8b5> ../cstrike/dlls/client.cpp:5111 */
void SpectatorThink(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorThink();
	}
}

/* <4a92d> ../cstrike/dlls/client.cpp:5160 */
void SetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas)
{
	edict_t *pView = pClient;

	// Find the client's PVS
	if (pViewEntity)
	{
		pView = pViewEntity;
	}

	if (pClient->v.flags & FL_PROXY)
	{
		*pvs = NULL;	// the spectator proxy sees
		*pas = NULL;	// and hears everything
		return;
	}

	CBasePlayer *pPlayer = reinterpret_cast<CBasePlayer *>(CBasePlayer::Instance(pClient));

	if (pPlayer->pev->iuser2 && pPlayer->m_hObserverTarget)
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

/* <4aa75> ../cstrike/dlls/client.cpp:5226 */
void ResetPlayerPVS(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];

	Q_memset(pvs, 0, sizeof(*pvs));
	pvs->headnode = client->headnode;
	pvs->num_leafs = client->num_leafs;
	Q_memcpy(pvs->leafnums, client->leafnums, sizeof(pvs->leafnums));
}

/* <4aae8> ../cstrike/dlls/client.cpp:5240 */
bool CheckPlayerPVSLeafChanged(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];
	if (pvs->headnode != client->headnode || pvs->num_leafs != client->num_leafs)
		return true;

	for (int i = 0; i < pvs->num_leafs; i++)
	{
		if (client->leafnums[i] != pvs->leafnums[i])
			return true;
	}
	return false;
}

/* <475e3> ../cstrike/dlls/client.cpp:5263 */
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

/* <47581> ../cstrike/dlls/client.cpp:5275 */
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

/* <4ac57> ../cstrike/dlls/client.cpp:5312 */
int AddToFullPack(struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet)
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

	Q_memset(state, 0, sizeof(*state));

	state->number = e;
	state->entityType = ENTITY_NORMAL;

	if (ent->v.flags & FL_CUSTOMENTITY)
		state->entityType = ENTITY_BEAM;

	state->animtime = (int)(1000.0 * ent->v.animtime) / 1000.0;

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

	for (i = 0; i < 4; i++)
		state->controller[i] = ent->v.controller[i];

	for (i = 0; i < 2; i++)
		state->blending[i] = ent->v.blending[i];

	state->rendermode = ent->v.rendermode;
	state->renderamt = (int)ent->v.renderamt;
	state->renderfx = ent->v.renderfx;
	state->rendercolor.r = (byte)ent->v.rendercolor.x;
	state->rendercolor.g = (byte)ent->v.rendercolor.y;
	state->rendercolor.b = (byte)ent->v.rendercolor.z;

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
		state->health = (int)ent->v.health;
	}
	else
		state->playerclass = ent->v.playerclass;

	state->iuser4 = ent->v.iuser4;
	return 1;
}

// Creates baselines used for network encoding, especially for player data since players are not spawned until connect time.

/* <4aef3> ../cstrike/dlls/client.cpp:5516 */
void CreateBaseline(int player, int eindex, struct entity_state_s *baseline, struct edict_s *entity, int playermodelindex, Vector player_mins, Vector player_maxs)
{
	baseline->origin = entity->v.origin;
	baseline->angles = entity->v.angles;

	baseline->frame = entity->v.frame;
	baseline->skin = (short)entity->v.skin;

	// render information
	baseline->rendermode = (byte)entity->v.rendermode;
	baseline->renderamt = (byte)entity->v.renderamt;
	baseline->rendercolor.r	= (byte)entity->v.rendercolor.x;
	baseline->rendercolor.g	= (byte)entity->v.rendercolor.y;
	baseline->rendercolor.b	= (byte)entity->v.rendercolor.z;
	baseline->renderfx = (byte)entity->v.renderfx;

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

/* <47d8a> ../cstrike/dlls/client.cpp:5586 */
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

/* <47da7> ../cstrike/dlls/client.cpp:5604 */
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
	localplayer =  (t->number - 1) == ENGINE_CURRENT_PLAYER();

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

/* <47cb4> ../cstrike/dlls/client.cpp:5662 */
void Player_FieldInit(struct delta_s *pFields)
{
	player_field_alias[ FIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN0 ].name);
	player_field_alias[ FIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN1 ].name);
	player_field_alias[ FIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN2 ].name);
}

// Callback for sending entity_state_t for players info over network.

/* <47cd1> ../cstrike/dlls/client.cpp:5676 */
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
	localplayer =  (t->number - 1) == ENGINE_CURRENT_PLAYER();

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

/* <4afc4> ../cstrike/dlls/client.cpp:5738 */
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

/* <4aff3> ../cstrike/dlls/client.cpp:5759 */
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

	if ((int)f->animtime == (int)t->animtime)
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].field);
	}
}

/* <4b08a> ../cstrike/dlls/client.cpp:5811 */
void RegisterEncoders(void)
{
	DELTA_ADDENCODER("Entity_Encode", Entity_Encode);
	DELTA_ADDENCODER("Custom_Encode", Custom_Encode);
	DELTA_ADDENCODER("Player_Encode", Player_Encode);
}

/* <4b0a4> ../cstrike/dlls/client.cpp:5818 */
int GetWeaponData(edict_s *player, struct weapon_data_s *info)
{
	entvars_t *pev = &player->v;
	CBasePlayer *pl = reinterpret_cast<CBasePlayer *>(CBasePlayer::Instance(pev));

	Q_memset(info, 0, sizeof(weapon_data_t) * MAX_WEAPONS);

	if (!pl)
	{
		return 1;
	}

	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		CBasePlayerItem *pPlayerItem = pl->m_rgpPlayerItems[i];

		while (pPlayerItem != NULL)
		{
			CBasePlayerWeapon *gun = reinterpret_cast<CBasePlayerWeapon *>(pPlayerItem->GetWeaponPtr());

			if (gun && gun->UseDecrement())
			{
				ItemInfo II;
				Q_memset(&II, 0, sizeof(II));
				gun->GetItemInfo(&II);

				if (II.iId >= 0 && II.iId < MAX_WEAPONS)
				{
					weapon_data_t *item = &info[II.iId];

					item->m_iId = II.iId;
					item->m_iClip = gun->m_iClip;
					item->m_flTimeWeaponIdle = Q_max(gun->m_flTimeWeaponIdle, -0.001f);
					item->m_flNextPrimaryAttack = Q_max(gun->m_flNextPrimaryAttack, -0.001f);
					item->m_flNextSecondaryAttack = Q_max(gun->m_flNextSecondaryAttack, -0.001f);
					item->m_flNextReload = Q_max(gun->m_flNextReload, -0.001f);
					item->m_fInReload = gun->m_fInReload;
					item->m_fInSpecialReload = gun->m_fInSpecialReload;
					item->m_fInZoom = gun->m_iShotsFired;
					item->m_fAimedDamage = gun->m_flLastFire;
					item->m_iWeaponState = gun->m_iWeaponState;
					item->fuser2 = gun->m_flStartThrow;
					item->fuser3 = gun->m_flReleaseThrow;
					item->iuser1 = gun->m_iSwing;
				}
			}

			pPlayerItem = pPlayerItem->m_pNext;
		}
	}

	return 1;
}

/* <4b1fd> ../cstrike/dlls/client.cpp:5889 */
void UpdateClientData(const struct edict_s *ent, int sendweapons, struct clientdata_s *cd)
{
	if (!ent || !ent->pvPrivateData)
	{
		return;
	}

	entvars_t *pevOrg = NULL;
	entvars_t *pev = (entvars_t *)&ent->v;
	CBasePlayer *pl = reinterpret_cast<CBasePlayer *>(CBasePlayer::Instance(pev));

	if (pl->pev->iuser1 == OBS_IN_EYE && pl->m_hObserverTarget)
	{
		pevOrg = pev;
		pev = pl->m_hObserverTarget->pev;
		pl = reinterpret_cast<CBasePlayer *>(CBasePlayer::Instance(pev));
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
	cd->waterjumptime = (int)pev->teleport_time;

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

	if (sendweapons && pl != NULL)
	{
		cd->ammo_shells = pl->ammo_buckshot;
		cd->ammo_nails = pl->ammo_9mm;
		cd->ammo_cells = pl->ammo_556nato;
		cd->ammo_rockets = pl->ammo_556natobox;
		cd->vuser2.x = pl->ammo_762nato;
		cd->vuser2.y = pl->ammo_45acp;
		cd->vuser2.z = pl->ammo_50ae;
		cd->vuser3.x = pl->ammo_338mag;
		cd->vuser3.y = pl->ammo_57mm;
		cd->vuser3.z = pl->ammo_357sig;
		cd->m_flNextAttack = pl->m_flNextAttack;

		int iUser3 = 0;
		if (pl->m_bCanShoot && !pl->m_bIsDefusing)
			iUser3 |= DATA_IUSER3_CANSHOOT;

		if (g_pGameRules->IsFreezePeriod())
			iUser3 |= DATA_IUSER3_FREEZETIMEOVER;
		else
			iUser3 &= ~DATA_IUSER3_FREEZETIMEOVER;

		if (pl->m_signals.GetState() & SIGNAL_BOMB)
			iUser3 |= DATA_IUSER3_INBOMBZONE;
		else
			iUser3 &= ~DATA_IUSER3_INBOMBZONE;

		if (pl->HasShield())
			iUser3 |= DATA_IUSER3_HOLDINGSHIELD;
		else
			iUser3 &= ~DATA_IUSER3_HOLDINGSHIELD;

		if (!pl->pev->iuser1 && !pevOrg)
			cd->iuser3 = iUser3;

		if (pl->m_pActiveItem != NULL)
		{
			ItemInfo II;
			Q_memset(&II, 0, sizeof(II));

			CBasePlayerWeapon *gun = reinterpret_cast<CBasePlayerWeapon *>(pl->m_pActiveItem->GetWeaponPtr());

			if (gun != NULL && gun->UseDecrement() && gun->GetItemInfo(&II))
			{
				cd->m_iId = II.iId;

				if ((unsigned int)gun->m_iPrimaryAmmoType < MAX_AMMO_TYPES)
				{
					cd->vuser4.x = gun->m_iPrimaryAmmoType;
					cd->vuser4.y = pl->m_rgAmmo[ gun->m_iPrimaryAmmoType ];
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

/* <4b3ee> ../cstrike/dlls/client.cpp:6050 */
void CmdStart(const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed)
{
	entvars_t *pev = (entvars_t *)&player->v;
	CBasePlayer *pl = reinterpret_cast<CBasePlayer *>(CBasePlayer::Instance(pev));

	if (!pl)
	{
		return;
	}

	if (pl->pev->groupinfo)
	{
		UTIL_SetGroupTrace(pl->pev->groupinfo, GROUP_OP_AND);
	}

	pl->random_seed = random_seed;
}

/* <4b4eb> ../cstrike/dlls/client.cpp:6074 */
void CmdEnd(const edict_t *player)
{
	entvars_t *pev = (entvars_t *)&player->v;
	CBasePlayer *pl = reinterpret_cast<CBasePlayer *>(CBasePlayer::Instance(pev));

	if (!pl)
		return;

	if (pl->pev->groupinfo)
		UTIL_UnsetGroupTrace();

	if (pev->flags & FL_DUCKING)
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
}

/* <4b644> ../cstrike/dlls/client.cpp:6101 */
int ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
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

/* <4b6c2> ../cstrike/dlls/client.cpp:6122 */
int GetHullBounds(int hullnumber, float *mins, float *maxs)
{
	return hullnumber < 3;
}

// Create pseudo-baselines for items that aren't placed in the map at spawn time, but which are likely
// to be created during play ( e.g., grenades, ammo packs, projectiles, corpses, etc. )

/* <4b733> ../cstrike/dlls/client.cpp:6156 */
void CreateInstancedBaselines(void)
{
	int iret = 0;
	entity_state_t state;

	Q_memset(&state, 0, sizeof(state));

	// Create any additional baselines here for things like grendates, etc.
	// iret = ENGINE_INSTANCE_BASELINE(pc->pev->classname, &state);

	// Destroy objects.
	// UTIL_Remove(pc);
}

/* <4b77c> ../cstrike/dlls/client.cpp:6179 */
int InconsistentFile(const edict_t *player, const char *filename, char *disconnect_message)
{
	// Server doesn't care?
	if (CVAR_GET_FLOAT("mp_consistency") != 1)
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

/* <4b7cf> ../cstrike/dlls/client.cpp:6204 */
int AllowLagCompensation(void)
{
	return 1;
}
