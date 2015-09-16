#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

CBotManager *TheBots = NULL;

cvar_t cv_bot_traceview = { "bot_traceview", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_stop = { "bot_stop", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_show_nav = { "bot_show_nav", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_show_danger = { "bot_show_danger", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_nav_edit = { "bot_nav_edit", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_nav_zdraw = { "bot_nav_zdraw", "4", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_walk = { "bot_walk", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_difficulty = { "bot_difficulty", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_debug = { "bot_debug", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_quicksave = { "bot_quicksave", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_quota = { "bot_quota", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_quota_match = { "bot_quota_match", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_prefix = { "bot_prefix", "", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_rogues = { "bot_allow_rogues", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_pistols = { "bot_allow_pistols", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_shotguns = { "bot_allow_shotguns", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_sub_machine_guns = { "bot_allow_sub_machine_guns", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_rifles = { "bot_allow_rifles", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_machine_guns = { "bot_allow_machine_guns", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_grenades = { "bot_allow_grenades", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_snipers = { "bot_allow_snipers", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_allow_shield = { "bot_allow_shield", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_join_team = { "bot_join_team", "any", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_join_after_player = { &unk_1EF09A, "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_auto_vacate = { "bot_auto_vacate", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_zombie = { "bot_zombie", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_defer_to_human = { "bot_defer_to_human", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_chatter = { "bot_chatter", "normal", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_bot_profile_db = { "bot_profile_db", "BotProfile.db", FCVAR_SERVER, 0.0f, NULL };

float CCSBotManager::m_flNextCVarCheck;
bool CCSBotManager::m_isMapDataLoaded;
bool CCSBotManager::m_isLearningMap;
bool CCSBotManager::m_isAnalysisRequested;
NavEditCmdType CCSBotManager::m_editCmd;

#else // HOOK_GAMEDLL

CBotManager *TheBots;

cvar_t cv_bot_traceview;
cvar_t cv_bot_stop;
cvar_t cv_bot_show_nav;
cvar_t cv_bot_show_danger;
cvar_t cv_bot_nav_edit;
cvar_t cv_bot_nav_zdraw;
cvar_t cv_bot_walk;
cvar_t cv_bot_difficulty;
cvar_t cv_bot_debug;
cvar_t cv_bot_quicksave;
cvar_t cv_bot_quota;
cvar_t cv_bot_quota_match;
cvar_t cv_bot_prefix;
cvar_t cv_bot_allow_rogues;
cvar_t cv_bot_allow_pistols;
cvar_t cv_bot_allow_shotguns;
cvar_t cv_bot_allow_sub_machine_guns;
cvar_t cv_bot_allow_rifles;
cvar_t cv_bot_allow_machine_guns;
cvar_t cv_bot_allow_grenades;
cvar_t cv_bot_allow_snipers;
cvar_t cv_bot_allow_shield;
cvar_t cv_bot_join_team;
cvar_t cv_bot_join_after_player;
cvar_t cv_bot_auto_vacate;
cvar_t cv_bot_zombie;
cvar_t cv_bot_defer_to_human;
cvar_t cv_bot_chatter;
cvar_t cv_bot_profile_db;

float (*CCSBotManager::pm_flNextCVarCheck);
bool (*CCSBotManager::pm_isMapDataLoaded);
bool (*CCSBotManager::pm_isLearningMap);
bool (*CCSBotManager::pm_isAnalysisRequested);
NavEditCmdType (*CCSBotManager::pm_editCmd);

#endif // HOOK_GAMEDLL

/* <36b3b4> ../cstrike/dlls/bot/cs_bot_manager.cpp:45 */
NOBODY CCSBotManager::CCSBotManager(void)
{
//	{
//		const char *filename;                               //    66
//		int dataLength;                                       //    76
//		char *dataPointer;                                   //    77
//		const VoiceBankList *pVoiceBanks;                   //   100
//		SetLooseBomb(CCSBotManager *const this,
//				class CBaseEntity *bomb);  //    49
//		{
//			const char *dataFile;                       //    84
//			const char *token;                          //    85
//			{
//				char *clone;                         //    90
//				CloneString(const char *str);  //    90
//			}
//		}
//		{
//			int i;                                        //   101
//			size(const class vector<char*, std::allocator<char*>> *const this);  //   101
//		}
//	}
//	CountdownTimer(CountdownTimer *const this);  //    45
}

/* <36b22a> ../cstrike/dlls/bot/cs_bot_manager.cpp:111 */
void CCSBotManager::__MAKE_VHOOK(RestartRound)(void)
{
	// extend
	CBotManager::RestartRound();

	SetLooseBomb(NULL);
	m_isBombPlanted = false;

	m_bombDefuser = NULL;
	m_earliestBombPlantTimestamp = gpGlobals->time + RANDOM_FLOAT(10, 30);

	IMPLEMENT_ARRAY(m_editCmd) = EDIT_NONE;

	ResetRadioMessageTimestamps();
	m_lastSeenEnemyTimestamp = -9999.9f;
	m_roundStartTimestamp = gpGlobals->time + CVAR_GET_FLOAT("mp_freezetime");

	// randomly decide if defensive team wants to "rush" as a whole
	const float defenseRushChance = 33.3f;	// 25.0f;
	m_isDefenseRushing = (RANDOM_FLOAT(0, 100) <= defenseRushChance) ? true : false;

	TheBotPhrases->OnRoundRestart();

	m_isRoundOver = false;
	m_isRespawnStarted = false;
	m_canRespawn = true;
}

/* <36aebc> ../cstrike/dlls/bot/cs_bot_manager.cpp:142 */
NOBODY void UTIL_DrawBox(Extent *extent, int lifetime, int red, int green, int blue)
{
//	{
//		Vector v;                                       //   144
//		int const edge;                                        //   154
//		Vector from;                                    //   165
//		Vector to;                                      //   165
//		bool restart;                                         //   166
//		{
//			int i;                                        //   167
//			{
//				int index;                            //   178
//			}
//		}
//	}
}

/* <36b13d> ../cstrike/dlls/bot/cs_bot_manager.cpp:195 */
NOBODY void CCSBotManager::__MAKE_VHOOK(StartFrame)(void)
{

}

/* <36b62a> ../cstrike/dlls/bot/cs_bot_manager.cpp:276 */
bool CCSBotManager::IsWeaponUseable(CBasePlayerItem *item) const
{
	if (item == NULL)
	{
		return false;
	}

	if (item->m_iId != WEAPON_C4)
	{
		int weaponClass = WeaponIDToWeaponClass(item->m_iId);

		if ((!AllowShotguns() && weaponClass == WEAPONCLASS_SHOTGUN)
			|| (!AllowMachineGuns() && weaponClass == WEAPONCLASS_MACHINEGUN)
			|| (!AllowRifles() && weaponClass == WEAPONCLASS_RIFLE)
			//|| (!AllowShotguns() && weaponClass == WEAPONCLASS_SHOTGUN) // TODO: already is checked shotguns!
			|| (!AllowSnipers() && weaponClass == WEAPONCLASS_SNIPERRIFLE)
			|| (!AllowSubMachineGuns() && weaponClass == WEAPONCLASS_SUBMACHINEGUN)
			|| (!AllowTacticalShield() && item->m_iId == WEAPON_SHIELDGUN)
			|| (!AllowPistols() && weaponClass == WEAPONCLASS_PISTOL)
			|| (!AllowGrenades() && weaponClass == WEAPONCLASS_GRENADE))
		{
			return false;
		}
	}

	return true;
}

/* <36b68c> ../cstrike/dlls/bot/cs_bot_manager.cpp:306 */
NOBODY bool CCSBotManager::IsOnDefense(CBasePlayer *player) const
{
}

/* <36b6b8> ../cstrike/dlls/bot/cs_bot_manager.cpp:327 */
NOBODY bool CCSBotManager::IsOnOffense(CBasePlayer *player) const
{
//	IsOnDefense(const class CCSBotManager *const this,
//			const class CBasePlayer *player);  //   329
}

/* <36a3b6> ../cstrike/dlls/bot/cs_bot_manager.cpp:331 */
void CCSBotManager::__MAKE_VHOOK(ServerActivate)(void)
{
	DestroyNavigationMap();
	IMPLEMENT_ARRAY(m_isMapDataLoaded) = false;

	m_zoneCount = 0;
	m_gameScenario = SCENARIO_DEATHMATCH;

	ValidateMapData();
	RestartRound();

	IMPLEMENT_ARRAY(m_isLearningMap) = false;
	IMPLEMENT_ARRAY(m_isAnalysisRequested) = false;

	m_bServerActive = true;
	AddServerCommands();

	TheBotPhrases->m_placeCount = 0;
}

/* <36afcd> ../cstrike/dlls/bot/cs_bot_manager.cpp:369 */
void CCSBotManager::__MAKE_VHOOK(AddServerCommand)(const char *cmd)
{
#if defined(HOOK_GAMEDLL) && !defined(REGAMEDLL_UNIT_TESTS)
	ADD_SERVER_COMMAND((char *)cmd, (xcommand_t)GetOriginalFuncAddrOrDefault("_Z17Bot_ServerCommandv", (void *)Bot_ServerCommand));
#else
	ADD_SERVER_COMMAND((char *)cmd, Bot_ServerCommand);
#endif // HOOK_GAMEDLL
}

/* <36b0e0> ../cstrike/dlls/bot/cs_bot_manager.cpp:375 */
void CCSBotManager::__MAKE_VHOOK(AddServerCommands)(void)
{
	static bool fFirstTime = true;

	if (!fFirstTime)
		return;

	fFirstTime = false;

	if (UTIL_IsGame("czero"))
	{
		AddServerCommand("bot_about");
		AddServerCommand("bot_add");
		AddServerCommand("bot_add_t");
		AddServerCommand("bot_add_ct");
		AddServerCommand("bot_kill");
		AddServerCommand("bot_kick");
		AddServerCommand("bot_knives_only");
		AddServerCommand("bot_pistols_only");
		AddServerCommand("bot_snipers_only");
		AddServerCommand("bot_all_weapons");
		AddServerCommand("entity_dump");
		AddServerCommand("bot_nav_delete");
		AddServerCommand("bot_nav_split");
		AddServerCommand("bot_nav_merge");
		AddServerCommand("bot_nav_mark");
		AddServerCommand("bot_nav_begin_area");
		AddServerCommand("bot_nav_end_area");
		AddServerCommand("bot_nav_connect");
		AddServerCommand("bot_nav_disconnect");
		AddServerCommand("bot_nav_splice");
		AddServerCommand("bot_nav_crouch");
		AddServerCommand("bot_nav_jump");
		AddServerCommand("bot_nav_precise");
		AddServerCommand("bot_nav_no_jump");
		AddServerCommand("bot_nav_analyze");
		AddServerCommand("bot_nav_strip");
		AddServerCommand("bot_nav_save");
		AddServerCommand("bot_nav_load");
		AddServerCommand("bot_nav_use_place");
		AddServerCommand("bot_nav_place_floodfill");
		AddServerCommand("bot_nav_place_pick");
		AddServerCommand("bot_nav_toggle_place_mode");
		AddServerCommand("bot_nav_toggle_place_painting");
		AddServerCommand("bot_goto_mark");
		AddServerCommand("bot_memory_usage");
		AddServerCommand("bot_nav_mark_unnamed");
		AddServerCommand("bot_nav_warp");
		AddServerCommand("bot_nav_corner_select");
		AddServerCommand("bot_nav_corner_raise");
		AddServerCommand("bot_nav_corner_lower");
		AddServerCommand("bot_nav_check_consistency");
	}
}

/* <36b2ac> ../cstrike/dlls/bot/cs_bot_manager.cpp:413 */
void CCSBotManager::__MAKE_VHOOK(ServerDeactivate)(void)
{
	m_bServerActive = false;
}

/* <36b5fa> ../cstrike/dlls/bot/cs_bot_manager.cpp:415 */
void CCSBotManager::__MAKE_VHOOK(ClientDisconnect)(CBasePlayer *pPlayer)
{
	if (!pPlayer || !pPlayer->IsBot())
		return;

	CCSBot *pBot = static_cast<CCSBot *>(pPlayer);
	entvars_t *temp = VARS(pPlayer->edict());

	pBot->Disconnect();

	if (pPlayer->pev->classname)
		RemoveEntityHashValue(pPlayer->pev, STRING(pPlayer->pev->classname), CLASSNAME);

	FREE_PRIVATE(pPlayer->edict());

	CBasePlayer *player = GetClassPtr((CBasePlayer *)temp);
	AddEntityHashValue(player->pev, STRING(player->pev->classname), CLASSNAME);
	player->pev->flags = FL_DORMANT;
}

/* <36b714> ../cstrike/dlls/bot/cs_bot_manager.cpp:464 */
void PrintAllEntities(void)
{
	for (int i = 1; i < gpGlobals->maxEntities; i++)
	{
		edict_t *edict = INDEXENT(i);

		if (!edict || FStringNull(edict->v.classname))
			continue;

		CONSOLE_ECHO("  %s\n", STRING(edict->v.classname));
	}
}

/* <36ace2> ../cstrike/dlls/bot/cs_bot_manager.cpp:484 */
void CCSBotManager::__MAKE_VHOOK(ServerCommand)(const char *pcmd)
{
	if (!m_bServerActive || !UTIL_IsGame("czero"))
		return;

	char buffer[400];
	const char *msg = CMD_ARGV(1);

	if (FStrEq(pcmd, "bot_about"))
	{
		Q_sprintf(buffer, "\n--------------------------------------------------------------------------\nThe Official Counter-Strike Bot V%d.%02d\nCreated by Michael S. Booth\nWeb: www.turtlerockstudios.com\\csbot\nE-mail: csbot@turtlerockstudios.com\n--------------------------------------------------------------------------\n\n", CSBOT_VERSION_MAJOR, CSBOT_VERSION_MINOR);
		CONSOLE_ECHO(buffer);
		HintMessageToAllPlayers(buffer);
	}
	else if (FStrEq(pcmd, "bot_add"))
	{
		BotAddCommand(BOT_TEAM_ANY);
	}
	else if (FStrEq(pcmd, "bot_add_t"))
	{
		BotAddCommand(BOT_TEAM_T);
	}
	else if (FStrEq(pcmd, "bot_add_ct"))
	{
		BotAddCommand(BOT_TEAM_CT);
	}
	else if (FStrEq(pcmd, "bot_kill"))
	{
		bool killThemAll;
		if (CMD_ARGC() == 1 || FStrEq(msg, "all"))
			killThemAll = true;
		else
			killThemAll = false;

		for (int iIndex = 1; iIndex <= gpGlobals->maxClients; iIndex++)
		{
			CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex(iIndex);

			if (pPlayer == NULL)
				continue;

			if (FNullEnt(pPlayer->pev))
				continue;

			const char *name = STRING(pPlayer->pev->netname);

			if (FStrEq(name, ""))
				continue;

			if (pPlayer->IsBot())
			{
				if (killThemAll || FStrEq(name, msg))
				{
					pPlayer->TakeDamage(pPlayer->pev, pPlayer->pev, 9999.9f, DMG_CRUSH);
				}
			}
		}
	}
	else if (FStrEq(pcmd, "bot_kick"))
	{
		bool kickThemAll;
		if (CMD_ARGC() == 1 || FStrEq(msg, "all"))
			kickThemAll = true;
		else
			kickThemAll = false;

		for (int iIndex = 1; iIndex <= gpGlobals->maxClients; iIndex++)
		{
			CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex(iIndex);

			if (pPlayer == NULL)
				continue;

			if (FNullEnt(pPlayer->pev))
				continue;

			const char *name = STRING(pPlayer->pev->netname);

			if (FStrEq(name, ""))
				continue;

			if (pPlayer->IsBot())
			{
				if (kickThemAll || FStrEq(name, msg))
				{
					SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", name));
					CVAR_SET_FLOAT("bot_quota", cv_bot_quota.value - 1);
				}
			}
		}

		if (kickThemAll || cv_bot_quota.value < 0.0f)
		{
			CVAR_SET_FLOAT("bot_quota", 0);
		}
	}
	else if (FStrEq(pcmd, "bot_knives_only"))
	{
		CVAR_SET_FLOAT("bot_allow_pistols", 0);
		CVAR_SET_FLOAT("bot_allow_shotguns", 0);
		CVAR_SET_FLOAT("bot_allow_sub_machine_guns", 0);
		CVAR_SET_FLOAT("bot_allow_rifles", 0);
		CVAR_SET_FLOAT("bot_allow_machine_guns", 0);
		CVAR_SET_FLOAT("bot_allow_grenades", 0);
		CVAR_SET_FLOAT("bot_allow_snipers", 0);
		CVAR_SET_FLOAT("bot_allow_shield", 0);
	}
	else if (FStrEq(pcmd, "bot_pistols_only"))
	{
		CVAR_SET_FLOAT("bot_allow_pistols", 1);
		CVAR_SET_FLOAT("bot_allow_shotguns", 0);
		CVAR_SET_FLOAT("bot_allow_sub_machine_guns", 0);
		CVAR_SET_FLOAT("bot_allow_rifles", 0);
		CVAR_SET_FLOAT("bot_allow_machine_guns", 0);
		CVAR_SET_FLOAT("bot_allow_grenades", 0);
		CVAR_SET_FLOAT("bot_allow_snipers", 0);
		CVAR_SET_FLOAT("bot_allow_shield", 0);
	}
	else if (FStrEq(pcmd, "bot_snipers_only"))
	{
		CVAR_SET_FLOAT("bot_allow_pistols", 1);
		CVAR_SET_FLOAT("bot_allow_shotguns", 0);
		CVAR_SET_FLOAT("bot_allow_sub_machine_guns", 0);
		CVAR_SET_FLOAT("bot_allow_rifles", 0);
		CVAR_SET_FLOAT("bot_allow_machine_guns", 0);
		CVAR_SET_FLOAT("bot_allow_grenades", 0);
		CVAR_SET_FLOAT("bot_allow_snipers", 1);
		CVAR_SET_FLOAT("bot_allow_shield", 0);
	}
	else if (FStrEq(pcmd, "bot_all_weapons"))
	{
		CVAR_SET_FLOAT("bot_allow_pistols", 1);
		CVAR_SET_FLOAT("bot_allow_shotguns", 1);
		CVAR_SET_FLOAT("bot_allow_sub_machine_guns", 1);
		CVAR_SET_FLOAT("bot_allow_rifles", 1);
		CVAR_SET_FLOAT("bot_allow_machine_guns", 1);
		CVAR_SET_FLOAT("bot_allow_grenades", 1);
		CVAR_SET_FLOAT("bot_allow_snipers", 1);
		CVAR_SET_FLOAT("bot_allow_shield", 1);
	}
	else if (FStrEq(pcmd, "entity_dump"))
	{
		PrintAllEntities();
	}
	else if (FStrEq(pcmd, "bot_nav_delete"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_DELETE;
	}
	else if (FStrEq(pcmd, "bot_nav_split"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_SPLIT;
	}
	else if (FStrEq(pcmd, "bot_nav_merge"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_MERGE;
	}
	else if (FStrEq(pcmd, "bot_nav_mark"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_MARK;
	}
	else if (FStrEq(pcmd, "bot_nav_begin_area"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_BEGIN_AREA;
	}
	else if (FStrEq(pcmd, "bot_nav_end_area"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_END_AREA;
	}
	else if (FStrEq(pcmd, "bot_nav_connect"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_CONNECT;
	}
	else if (FStrEq(pcmd, "bot_nav_disconnect"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_DISCONNECT;
	}
	else if (FStrEq(pcmd, "bot_nav_splice"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_SPLICE;
	}
	else if (FStrEq(pcmd, "bot_nav_crouch"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_ATTRIB_CROUCH;
	}
	else if (FStrEq(pcmd, "bot_nav_jump"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_ATTRIB_JUMP;
	}
	else if (FStrEq(pcmd, "bot_nav_precise"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_ATTRIB_PRECISE;
	}
	else if (FStrEq(pcmd, "bot_nav_no_jump"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_ATTRIB_NO_JUMP;
	}
	else if (FStrEq(pcmd, "bot_nav_analyze"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_isAnalysisRequested) = true;
	}
	else if (FStrEq(pcmd, "bot_nav_strip"))
	{
		StripNavigationAreas();// TODO: reverse me
	}
	else if (FStrEq(pcmd, "bot_nav_save"))
	{
		GET_GAME_DIR(buffer);
		buffer[ Q_strlen(buffer) ] = '\\';

		Q_strcat(buffer, CBotManager::GetNavMapFilename());

		if (SaveNavigationMap(buffer))// TODO: reverse me
			CONSOLE_ECHO("Navigation map '%s' saved.\n", buffer);
		else
			CONSOLE_ECHO("ERROR: Cannot save navigation map '%s'.\n", buffer);
	}
	else if (FStrEq(pcmd, "bot_nav_load"))
	{
		ValidateMapData();
	}
	else if (FStrEq(pcmd, "bot_nav_use_place"))
	{
		if (CMD_ARGC() == 1)
		{
			int i = 0;
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();

			for (BotPhraseList::const_iterator iter = placeList->begin(); iter != placeList->end(); ++iter, i++)
			{
				if ((*iter)->GetID() == GetNavPlace())
					CONSOLE_ECHO("--> %-26s", (*iter)->GetName());
				else
					CONSOLE_ECHO("%-30s", (*iter)->GetName());

				if (!(i % 3))
					CONSOLE_ECHO("\n");
			}
			CONSOLE_ECHO("\n");
		}
		else
		{
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();
			const BotPhrase *found = NULL;
			bool isAmbiguous = false;

			for (BotPhraseList::const_iterator iter = placeList->begin(); iter != placeList->end(); ++iter)
			{
				if (!Q_strnicmp((*iter)->GetName(), msg, Q_strlen(msg)))
				{
					if (!Q_strcmp((*iter)->GetName(), msg))
					{
						found = (*iter);
						break;
					}

					if (found != NULL)
						isAmbiguous = true;
					else
						found = (*iter);
				}
			}

			if (isAmbiguous)
			{
				CONSOLE_ECHO("Ambiguous\n");
				return;
			}

			if (found != NULL)
			{
				CONSOLE_ECHO("Current place set to '%s'\n", found->GetName());
				m_navPlace = found->GetID();
			}
		}
	}
	else if (FStrEq(pcmd, "bot_nav_toggle_place_mode"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_TOGGLE_PLACE_MODE;
	}
	else if (FStrEq(pcmd, "bot_nav_place_floodfill"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_PLACE_FLOODFILL;
	}
	else if (FStrEq(pcmd, "bot_nav_place_pick"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_PLACE_PICK;
	}
	else if (FStrEq(pcmd, "bot_nav_toggle_place_painting"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_TOGGLE_PLACE_PAINTING;
	}
	else if (FStrEq(pcmd, "bot_goto_mark"))
	{
		// tell the first bot we find to go to our marked area
		CNavArea *area = GetMarkedArea();// TODO: reverse me
		if (area != NULL)
		{
			CBaseEntity *pEntity = NULL;
			while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
			{
				if (!pEntity->IsPlayer())
					continue;

				if ((pEntity->pev->flags & FL_DORMANT) == FL_DORMANT)
					continue;

				CBasePlayer *playerOrBot = GetClassPtr((CBasePlayer *)pEntity->pev);

				if (playerOrBot->IsBot())
				{
					CCSBot *bot = reinterpret_cast<CCSBot *>(playerOrBot);
					bot->MoveTo(&area->m_center, FASTEST_ROUTE);// TODO: reverse me
					return;
				}
			}
		}
	}
	else if (FStrEq(pcmd, "bot_memory_usage"))
	{
		CONSOLE_ECHO("Memory usage:\n");
		CONSOLE_ECHO("  %d bytes per bot\b", sizeof(CCSBot));
		CONSOLE_ECHO("  %d Navigation Areas @ %d bytes each = %d bytes\n",
			TheNavAreaGrid.GetNavAreaCount(),
			sizeof(CNavArea),
			TheNavAreaGrid.GetNavAreaCount() * sizeof(CNavArea));
		CONSOLE_ECHO("  %d Hiding Spots @ %d bytes each = %d bytes\n",
			TheHidingSpotList.size(),
			sizeof(HidingSpot),
			sizeof(HidingSpot) * TheHidingSpotList.size());

		unsigned int encounterMem = 0;
		for (NavAreaList::iterator iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
		{
			CNavArea *area = (*iter);

			for (SpotEncounterList::iterator siter = area->m_spotEncounterList.begin(); siter != area->m_spotEncounterList.end(); ++siter)
			{
				// TODO: Fix me, this is crashed in HOOK_GAMEDLL
				SpotEncounter se = (*siter);

				encounterMem += sizeof(SpotEncounter);
				encounterMem += sizeof(SpotOrder) * se.spotList.size();
			}
		}

		CONSOLE_ECHO("  Encounter Spot data = %d bytes\n", encounterMem);
	}
	else if (FStrEq(pcmd, "bot_nav_mark_unnamed"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_MARK_UNNAMED;
	}
	else if (FStrEq(pcmd, "bot_nav_warp"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_WARP_TO_MARK;
	}
	else if (FStrEq(pcmd, "bot_nav_corner_select"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_SELECT_CORNER;
	}
	else if (FStrEq(pcmd, "bot_nav_corner_raise"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_RAISE_CORNER;
	}
	else if (FStrEq(pcmd, "bot_nav_corner_lower"))
	{
		IMPLEMENT_ARRAY_CLASS(CCSBotManager, m_editCmd) = EDIT_LOWER_CORNER;
	}
	else if (FStrEq(pcmd, "bot_nav_check_consistency"))
	{
		if (CMD_ARGC() != 2)
		{
			CONSOLE_ECHO("usage: bot_nav_check_consistency <filename>\n");
			return;
		}

		SanityCheckNavigationMap(msg);// TODO: reverse me
	}
}

/* <36c3c2> ../cstrike/dlls/bot/cs_bot_manager.cpp:903 */
NOBODY bool CCSBotManager::BotAddCommand(BotProfileTeamType team, bool isFromConsole)
{
	if (IMPLEMENT_ARRAY(m_isLearningMap) || ENG_CHECK_PARM("-nobots", NULL))
		return false;

	const BotProfile *profile = NULL;

	if (!isFromConsole || CMD_ARGC() < 2)
	{
		if (team == BOT_TEAM_ANY)
		{
			// if team not specified, check cv_bot_join_team cvar for preference
			if (!Q_stricmp(cv_bot_join_team.string, "T"))
				team = BOT_TEAM_T;

			else if (!Q_stricmp(cv_bot_join_team.string, "CT"))
				team = BOT_TEAM_CT;
			else
			{
				TeamName defaultTeam = SelectDefaultTeam();

				if (defaultTeam == TERRORIST)
					team = BOT_TEAM_T;

				else if (defaultTeam == CT)
					team = BOT_TEAM_CT;
			}
		}

		// try to add a bot by name
		profile = TheBotProfiles->GetRandomProfile(GetDifficultyLevel(), team);

		if (profile == NULL)
		{
			CONSOLE_ECHO("All bot profiles at this difficulty level are in use.\n");
			return true;
		}
	}
	else
	{
		// in career, ignore humans
		bool ignoreHumans = false;
		CHalfLifeMultiplay *mp = g_pGameRules;

		if (mp && mp->IsCareer())
			ignoreHumans = true;

		if (UTIL_IsNameTaken(CMD_ARGV(1), ignoreHumans))
		{
			CONSOLE_ECHO("Error - %s is already in the game.\n", CMD_ARGV(1));
			return true;
		}

		profile = TheBotProfiles->GetProfile(CMD_ARGV(1), team);
		if (profile == NULL)
		{
			CONSOLE_ECHO("Error - no profile for '%s' exists.\n", CMD_ARGV(1));
			return true;
		}
	}

	// create the bot
	if (CCSBotManager::AddBot(profile, team))	// TODO: Reverse me
	{
		if (isFromConsole)
		{
			// increase the bot quota to account for manually added bot
			CVAR_SET_FLOAT("bot_quota", cv_bot_quota.value + 1);
		}
	}

	return true;
}

/* <36d10f> ../cstrike/dlls/bot/cs_bot_manager.cpp:979 */
NOBODY void CCSBotManager::MaintainBotQuota(void)
{
//	{
//		int totalHumansInGame;                                //   984
//		int humanPlayersInGame;                               //   985
//		class CHalfLifeMultiplay *mp;                        //   991
//		int desiredBotCount;                                  //   993
//		BotAddCommand(BotProfileTeamType team,
//				bool isFromConsole);  //  1017
//		{
//			enum TeamName kickTeam;                       //  1027
//		}
//		{
//			bool humansAreCTs;                            //  1067
//		}
//	}
}

/* <36d1dd> ../cstrike/dlls/bot/cs_bot_manager.cpp:1086 */
NOBODY void CCSBotManager::MonitorBotCVars(void)
{
}

/* <36b780> ../cstrike/dlls/bot/cs_bot_manager.cpp:1109 */
void CCSBotManager::ValidateMapData(void)
{
	if (IMPLEMENT_ARRAY(m_isMapDataLoaded) || !UTIL_IsGame("czero"))
	{
		return;
	}

	IMPLEMENT_ARRAY(m_isMapDataLoaded) = true;

	// TODO: Reverse me
	if (LoadNavigationMap())
	{
		CONSOLE_ECHO("Failed to load navigation map.\n");
		return;
	}

	CONSOLE_ECHO("Navigation map loaded.\n");

	m_zoneCount = 0;
	m_gameScenario = SCENARIO_DEATHMATCH;

	// Search all entities in the map and set the game type and
	// store all zones (bomb target, etc).

	CBaseEntity *entity = NULL;
	int i;

	for (i = 1; i < gpGlobals->maxEntities; i++)
	{
		entity = CBaseEntity::Instance(INDEXENT(i));

		if (entity == NULL)
			continue;

		bool found = false;
		bool isLegacy = false;

		if (FClassnameIs(entity->pev, "func_bomb_target"))
		{
			found = true;
			isLegacy = false;

			m_gameScenario = SCENARIO_DEFUSE_BOMB;
		}
		else if (FClassnameIs(entity->pev, "info_bomb_target"))
		{
			found = true;
			isLegacy = true;

			m_gameScenario = SCENARIO_DEFUSE_BOMB;
		}
		else if (FClassnameIs(entity->pev, "func_hostage_rescue"))
		{
			found = true;
			isLegacy = false;

			m_gameScenario = SCENARIO_RESCUE_HOSTAGES;
		}
		else if (FClassnameIs(entity->pev, "info_hostage_rescue"))
		{
			found = true;
			isLegacy = true;

			m_gameScenario = SCENARIO_RESCUE_HOSTAGES;
		}
		else if (FClassnameIs(entity->pev, "hostage_entity"))
		{
			// some very old maps (ie: cs_assault) use info_player_start
			// as rescue zones, so set the scenario if there are hostages
			// in the map
			m_gameScenario = SCENARIO_RESCUE_HOSTAGES;
		}
		else if (FClassnameIs(entity->pev, "func_vip_safetyzone"))
		{
			found = true;
			isLegacy = false;

			m_gameScenario = SCENARIO_ESCORT_VIP;
		}

		if (found)
		{
			if (m_zoneCount < MAX_ZONES)
			{
				if (isLegacy)
					m_zone[ m_zoneCount ].m_center = entity->pev->origin;
				else
					m_zone[ m_zoneCount ].m_center = (entity->pev->absmax + entity->pev->absmin) / 2.0f;

				m_zone[ m_zoneCount ].m_isLegacy = isLegacy;
				m_zone[ m_zoneCount ].m_index = m_zoneCount;
				m_zone[ m_zoneCount ].m_entity = entity;

				++m_zoneCount;
			}
			else
				CONSOLE_ECHO("Warning: Too many zones, some will be ignored.\n");
		}
	}

	// If there are no zones and the scenario is hostage rescue,
	// use the info_player_start entities as rescue zones.
	if (m_zoneCount == 0 && m_gameScenario == SCENARIO_RESCUE_HOSTAGES)
	{
		entity = NULL;

		while ((entity = UTIL_FindEntityByClassname(entity, "info_player_start")) != NULL)
		{
			if (FNullEnt(entity->edict()))
				break;

			if (m_zoneCount < MAX_ZONES)
			{
				m_zone[ m_zoneCount ].m_center = entity->pev->origin;
				m_zone[ m_zoneCount ].m_isLegacy = true;
				m_zone[ m_zoneCount ].m_index = m_zoneCount;
				m_zone[ m_zoneCount ].m_entity = entity;

				++m_zoneCount;
			}
			else
				CONSOLE_ECHO("Warning: Too many zones, some will be ignored.\n");
		}
	}

	// Collect nav areas that overlap each zone
	for (i = 0; i < m_zoneCount; i++)
	{
		Zone *zone = &m_zone[i];

		if (zone->m_isLegacy)
		{
			const float legacyRange = 256.0f;

			zone->m_extent.lo.x = zone->m_center.x - legacyRange;
			zone->m_extent.lo.y = zone->m_center.y - legacyRange;
			zone->m_extent.lo.z = zone->m_center.z - legacyRange;

			zone->m_extent.hi.x = zone->m_center.x + legacyRange;
			zone->m_extent.hi.y = zone->m_center.y + legacyRange;
			zone->m_extent.hi.z = zone->m_center.z + legacyRange;
		}
		else
		{
			zone->m_extent.lo = zone->m_entity->pev->absmin;
			zone->m_extent.hi = zone->m_entity->pev->absmax;
		}

		// ensure Z overlap
		const float zFudge = 50.0f;

		zone->m_areaCount = 0;
		zone->m_extent.lo.z -= zFudge;
		zone->m_extent.hi.z += zFudge;

		// build a list of nav areas that overlap this zone
		for (NavAreaList::iterator iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
		{
			CNavArea *area = (*iter);
			const Extent *areaExtent = area->GetExtent();

			if (areaExtent->hi.x >= zone->m_extent.lo.x && areaExtent->lo.x <= zone->m_extent.hi.x
				&& areaExtent->hi.y >= zone->m_extent.lo.y && areaExtent->lo.y <= zone->m_extent.hi.y
				&& areaExtent->hi.z >= zone->m_extent.lo.z && areaExtent->lo.z <= zone->m_extent.hi.z)
			{
				// area overlaps zone
				zone->m_area[ zone->m_areaCount++ ] = area;

				if (zone->m_areaCount == MAX_ZONE_NAV_AREAS)
				{
					break;
				}
			}
		}
	}
}

void (*pCCSBotManager__AddBot)(void);

/* <36c2b2> ../cstrike/dlls/bot/cs_bot_manager.cpp:1278 */
NOBODY bool __declspec(naked) CCSBotManager::AddBot(const BotProfile *profile, BotProfileTeamType team)
{
	__asm
	{
		jmp pCCSBotManager__AddBot
	}

	//if (!UTIL_IsGame("czero"))
	//	return false;

	//CHalfLifeMultiplay *mp = g_pGameRules;

	//int nTeamSlot = UNASSIGNED;
	//
	//if (team == BOT_TEAM_ANY)
	//{
	//	// if team not specified, check cv_bot_join_team cvar for preference
	//	if (!Q_stricmp(cv_bot_join_team.string, "T"))
	//		nTeamSlot = TERRORIST;

	//	else if (!Q_stricmp(cv_bot_join_team.string, "CT"))
	//		nTeamSlot = CT;
	//}
	//else if (team == BOT_TEAM_CT)
	//	nTeamSlot = CT;

	//else if (team == BOT_TEAM_T)
	//	nTeamSlot = TERRORIST;

	//if (nTeamSlot == UNASSIGNED)
	//{
	//	nTeamSlot = SelectDefaultTeam();
	//}

	//if (nTeamSlot == UNASSIGNED || mp->TeamFull(nTeamSlot))
	//{
	//	CONSOLE_ECHO("Could not add bot to the game: Team is full\n");
	//	return false;
	//}

	//if (mp->TeamStacked(nTeamSlot, UNASSIGNED))
	//{
	//	CONSOLE_ECHO("Could not add bot to the game: Team is stacked (to disable this check, set mp_limitteams and mp_autoteambalance to zero and restart the round).\n");
	//	return false;
	//}

	//CCSBot *pBot = CreateBot<CCSBot>(profile);
	//if (pBot == NULL)
	//{
	//	return false;
	//}

	////int nJoinedTeam;
	//ClientPutInServer(pBot->edict());
	//SET_CLIENT_KEY_VALUE(pBot->entindex(), GET_INFO_BUFFER(pBot->edict()), "*bot", "1");

	//pBot->m_iMenu = Menu_ChooseTeam;
	//pBot->m_iJoiningState = PICKINGTEAM;

	//if (HandleMenu_ChooseTeam(pBot, nTeamSlot))//TODO: Reverse me
	//{
	//	int skin = profile->GetSkin();

	//	if (!skin)
	//		skin = 6;// MODEL_GIGN?

	//	HandleMenu_ChooseAppearance(pBot, skin);//TODO: Reverse me

	//	if (IS_DEDICATED_SERVER())
	//	{
	//		UTIL_DPrintf("Added bot %s to server\n", STRING(pBot->pev->netname));
	//	}

	//	return true;
	//}

	//SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", STRING(pBot->pev->netname)));
	//CONSOLE_ECHO("Could not add bot to the game.\n");

	//return false;
}

/* <36bb90> ../cstrike/dlls/bot/cs_bot_manager.cpp:1375 */
NOBODY const CCSBotManager::Zone *CCSBotManager::GetZone(const Vector *pos) const
{
//	{
//		int z;                                                //  1377
//		Contains(const class Extent *const this,
//			const Vector *pos);  //  1379
//	}
}

/* <36bbfd> ../cstrike/dlls/bot/cs_bot_manager.cpp:1392 */
NOBODY const CCSBotManager::Zone *CCSBotManager::GetClosestZone(const Vector *pos) const
{
//	{
//		const class Zone *close;                            //  1394
//		float closeRangeSq;                                   //  1395
//		{
//			int z;                                        //  1397
//			{
//				float rangeSq;                        //  1399
//				operator-(const Vector *const this,
//						const Vector &v);  //  1399
//				LengthSquared(const Vector *const this);  //  1399
//			}
//		}
//	}
}

/* <36bcc9> ../cstrike/dlls/bot/cs_bot_manager.cpp:1415 */
NOBODY const Vector *CCSBotManager::GetRandomPositionInZone(const Zone *zone) const
{
//	{
//		Vector pos;                                     //  1417
//		int a;                                                //  1426
//		class CNavArea *area;                                //  1427
//		{
//			const class Extent *areaExtent;             //  1439
//			class Extent overlap;                         //  1440
//		}
//	}
}

/* <36bd64> ../cstrike/dlls/bot/cs_bot_manager.cpp:1458 */
NOBODY CNavArea *CCSBotManager::GetRandomAreaInZone(const Zone *zone) const
{
//	{
//		int a;                                                //  1466
//	}
}

/* <36b02d> ../cstrike/dlls/bot/cs_bot_manager.cpp:1477 */
void CCSBotManager::__MAKE_VHOOK(OnEvent)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_BOMB_PLANTED:
		m_isBombPlanted = true;
		m_bombPlantTimestamp = gpGlobals->time;
		break;

	case EVENT_BOMB_DEFUSING:
		m_bombDefuser = (CBasePlayer *)entity;
		break;

	case EVENT_BOMB_DEFUSE_ABORTED:
		m_bombDefuser = NULL;
		break;

	case EVENT_BOMB_DEFUSED:
		m_isBombPlanted = false;
		m_bombDefuser = NULL;
		break;

	case EVENT_TERRORISTS_WIN:
	case EVENT_CTS_WIN:
	case EVENT_ROUND_DRAW:
		m_isRoundOver = true;
		break;

	case EVENT_RADIO_ENEMY_SPOTTED:
		m_lastSeenEnemyTimestamp = gpGlobals->time;
		SetLastSeenEnemyTimestamp();
		break;

	default:
		break;
	}

	CBotManager::OnEvent(event, entity, other);
}

BOOL CCSBotManager::__MAKE_VHOOK(ClientCommand)(CBasePlayer *pPlayer, const char *pcmd)
{
	// TODO: rly?
#ifndef REGAMEDLL_FIXES
	if (pPlayer && UTIL_GetLocalPlayer())
	{
		UTIL_GetLocalPlayer();
	}
#endif // REGAMEDLL_FIXES

	return FALSE;
}

/* <36bdb3> ../cstrike/dlls/bot/cs_bot_manager.cpp:1541 */
NOBODY float CCSBotManager::GetBombTimeLeft(void) const
{
}

/* <36bddb> ../cstrike/dlls/bot/cs_bot_manager.cpp:1547 */
void CCSBotManager::SetLooseBomb(CBaseEntity *bomb)
{
	m_looseBomb = bomb;

	if (bomb)
		m_looseBombArea = TheNavAreaGrid.GetNearestNavArea(&bomb->pev->origin);
	else
		m_looseBombArea = NULL;
}

/* <36b14d> ../cstrike/dlls/bot/cs_bot_manager.cpp:1565 */
NOBODY bool CCSBotManager::__MAKE_VHOOK(IsImportantPlayer)(CBasePlayer *player)
{
//	IsImportantPlayer(const class CCSBotManager *const this,
//				class CBasePlayer *player);  //  1565
}

/* <36b1a7> ../cstrike/dlls/bot/cs_bot_manager.cpp:1602 */
NOBODY unsigned int CCSBotManager::__MAKE_VHOOK(GetPlayerPriority)(CBasePlayer *player) const
{
//	{
//		unsigned int const lowestPriority;                     //  1604
//		class CCSBot *bot;                                   //  1613
//	}
//	GetPlayerPriority(const class CCSBotManager *const this,
//				class CBasePlayer *player);  //  1602
}

/* <36be2e> ../cstrike/dlls/bot/cs_bot_manager.cpp:1655 */
NOBODY float CCSBotManager::GetRadioMessageTimestamp(GameEventType event, int teamID)
{
}

/* <36be76> ../cstrike/dlls/bot/cs_bot_manager.cpp:1667 */
NOBODY float CCSBotManager::GetRadioMessageInterval(GameEventType event, int teamID)
{
}

/* <36bebe> ../cstrike/dlls/bot/cs_bot_manager.cpp:1680 */
NOBODY void CCSBotManager::SetRadioMessageTimestamp(GameEventType event, int teamID)
{
}

/* <36bf06> ../cstrike/dlls/bot/cs_bot_manager.cpp:1690 */
void CCSBotManager::ResetRadioMessageTimestamps(void)
{
	for (int t = 0; t < ARRAYSIZE(m_radioMsgTimestamp[0]); t++)
	{
		for (int m = 0; m < ARRAYSIZE(m_radioMsgTimestamp); m++)
		{
			m_radioMsgTimestamp[m][t] = 0.0f;
		}
	}
}

#ifdef HOOK_GAMEDLL

void CCSBotManager::ClientDisconnect(CBasePlayer *pPlayer)
{
	ClientDisconnect_(pPlayer);
}

BOOL CCSBotManager::ClientCommand(CBasePlayer *pPlayer, const char *pcmd)
{
	return ClientCommand_(pPlayer, pcmd);
}

void CCSBotManager::ServerActivate(void)
{
	ServerActivate_();
}

void CCSBotManager::ServerDeactivate(void)
{
	ServerDeactivate_();
}

void CCSBotManager::ServerCommand(const char *pcmd)
{
	ServerCommand_(pcmd);
}

void CCSBotManager::AddServerCommand(const char *cmd)
{
	AddServerCommand_(cmd);
}

void CCSBotManager::AddServerCommands(void)
{
	AddServerCommands_();
}

void CCSBotManager::RestartRound(void)
{
	RestartRound_();
}

void CCSBotManager::StartFrame(void)
{
	StartFrame_();
}

void CCSBotManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	OnEvent_(event, entity, other);
}

unsigned int CCSBotManager::GetPlayerPriority(CBasePlayer *player) const
{
	return GetPlayerPriority_(player);
}

bool CCSBotManager::IsImportantPlayer(CBasePlayer *player)
{
	return IsImportantPlayer_(player);
}

#endif // HOOK_GAMEDLL
