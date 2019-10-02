/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#include "precompiled.h"

CBotManager *TheBots = nullptr;

float CCSBotManager::m_flNextCVarCheck = 0.0f;
bool CCSBotManager::m_isMapDataLoaded = false;
bool CCSBotManager::m_isLearningMap = false;
bool CCSBotManager::m_isAnalysisRequested = false;
NavEditCmdType CCSBotManager::m_editCmd = EDIT_NONE;

CCSBotManager::CCSBotManager()
{
	m_flNextCVarCheck = 0.0f;

	m_zoneCount = 0;
	SetLooseBomb(nullptr);

	m_isBombPlanted = false;
	m_bombDefuser = nullptr;

	m_isLearningMap = false;
	m_isAnalysisRequested = false;
	m_editCmd = EDIT_NONE;

	m_navPlace = 0;
	m_roundStartTimestamp = 0.0f;

	m_bServerActive = false;

	TheBotPhrases = new BotPhraseManager;
	// load the database of bot radio chatter
	TheBotPhrases->Initialize("BotChatter.db", 0);

	TheBotProfiles = new BotProfileManager;
	// make sure default voice bank is first
	TheBotProfiles->FindVoiceBankIndex("BotChatter.db");

	const char *filename;
	if (IS_CAREER_MATCH())
	{
		filename = "MissionPacks/BotPackList.db";
	}
	else
	{
		filename = "BotPackList.db";
	}

	// read in the list of bot profile DBs
	int dataLength;
	char *dataPointer = (char *)LOAD_FILE_FOR_ME((char *)filename, &dataLength);
	if (!dataPointer)
	{
		TheBotProfiles->Init("BotProfile.db");
	}
	else
	{
		char *dataFile = SharedParse(dataPointer);
		char *token;

		while (dataFile)
		{
			token = SharedGetToken();
			char *clone = CloneString(token);
			TheBotProfiles->Init(clone);
			delete[] clone;
			dataFile = SharedParse(dataFile);
		}

		FREE_FILE(dataPointer);
	}

	// Now that we've parsed all the profiles, we have a list of the voice banks they're using.
	// Go back and parse the custom voice speakables.
	const BotProfileManager::VoiceBankList *pVoiceBanks = TheBotProfiles->GetVoiceBanks();
	for (uint32 i = 1; i < pVoiceBanks->size(); i++)
	{
		TheBotPhrases->Initialize((*pVoiceBanks)[i], i);
	}

#ifdef REGAMEDLL_FIXES
	AddServerCommands();
#endif
}

// Invoked when a new round begins
void CCSBotManager::RestartRound()
{
	// extend
	CBotManager::RestartRound();

	SetLooseBomb(nullptr);
	m_isBombPlanted = false;
	m_earliestBombPlantTimestamp = gpGlobals->time + RANDOM_FLOAT(10.0f, 30.0f);
	m_bombDefuser = nullptr;

	m_editCmd = EDIT_NONE;

	ResetRadioMessageTimestamps();

	m_lastSeenEnemyTimestamp = -9999.9f;
	m_roundStartTimestamp = gpGlobals->time + freezetime.value;

	// randomly decide if defensive team wants to "rush" as a whole
	const float defenseRushChance = 33.3f;	// 25.0f;
	m_isDefenseRushing = (RANDOM_FLOAT(0.0f, 100.0f) <= defenseRushChance) ? true : false;

	TheBotPhrases->OnRoundRestart();

	m_isRoundOver = false;
	m_isRespawnStarted = false;
	m_canRespawn = true;
}

// Called each frame
void CCSBotManager::StartFrame()
{
	// EXTEND
	CBotManager::StartFrame();
	MonitorBotCVars();

	// debug zone extent visualization
	if (cv_bot_debug.value == 5.0f)
	{
		for (int z = 0; z < m_zoneCount; z++)
		{
			Zone *zone = &m_zone[z];
			UTIL_DrawBox(&zone->m_extent, 1, 255, 100, 0);
		}
	}
}

// Return true if the bot can use this weapon
bool CCSBotManager::IsWeaponUseable(CBasePlayerItem *item) const
{
	if (!item)
	{
		return false;
	}

	if (item->m_iId == WEAPON_C4)
		return true;

	WeaponClassType weaponClass = WeaponIDToWeaponClass(item->m_iId);

	if ((!AllowShotguns()          && weaponClass == WEAPONCLASS_SHOTGUN)
		|| (!AllowMachineGuns()    && weaponClass == WEAPONCLASS_MACHINEGUN)
		|| (!AllowRifles()         && weaponClass == WEAPONCLASS_RIFLE)
		|| (!AllowSnipers()        && weaponClass == WEAPONCLASS_SNIPERRIFLE)
		|| (!AllowSubMachineGuns() && weaponClass == WEAPONCLASS_SUBMACHINEGUN)
		|| (!AllowTacticalShield() && item->m_iId == WEAPON_SHIELDGUN)
		|| (!AllowPistols()        && weaponClass == WEAPONCLASS_PISTOL)
		|| (!AllowGrenades()       && weaponClass == WEAPONCLASS_GRENADE))
	{
		return false;
	}

	return true;
}

bool CCSBotManager::IsWeaponUseable(ArmouryItemPack item) const
{
	WeaponClassType weaponClass = WeaponIDToWeaponClass(item);

	if ((!AllowShotguns()          && weaponClass == WEAPONCLASS_SHOTGUN)
		|| (!AllowMachineGuns()    && weaponClass == WEAPONCLASS_MACHINEGUN)
		|| (!AllowRifles()         && weaponClass == WEAPONCLASS_RIFLE)
		|| (!AllowSnipers()        && weaponClass == WEAPONCLASS_SNIPERRIFLE)
		|| (!AllowSubMachineGuns() && weaponClass == WEAPONCLASS_SUBMACHINEGUN)
		|| (!AllowTacticalShield() && item == ARMOURY_SHIELD)
		|| (!AllowPistols()        && weaponClass == WEAPONCLASS_PISTOL)
		|| (!AllowGrenades()       && weaponClass == WEAPONCLASS_GRENADE))
	{
		return false;
	}

	return true;
}

// Return true if this player is on "defense"
bool CCSBotManager::IsOnDefense(CBasePlayer *pPlayer) const
{
	switch (GetScenario())
	{
	case SCENARIO_DEFUSE_BOMB:
		return (pPlayer->m_iTeam == CT);

	case SCENARIO_RESCUE_HOSTAGES:
		return (pPlayer->m_iTeam == TERRORIST);

	case SCENARIO_ESCORT_VIP:
		return (pPlayer->m_iTeam == TERRORIST);
	}

	return false;
}

// Return true if this player is on "offense"
bool CCSBotManager::IsOnOffense(CBasePlayer *pPlayer) const
{
	return !IsOnDefense(pPlayer);
}

// Invoked when a map has just been loaded
void CCSBotManager::ServerActivate()
{
	DestroyNavigationMap();
	m_isMapDataLoaded = false;

	m_zoneCount = 0;
	m_gameScenario = SCENARIO_DEATHMATCH;

	ValidateMapData();
	RestartRound();

	m_isLearningMap = false;
	m_isAnalysisRequested = false;

	m_bServerActive = true;

#ifndef REGAMEDLL_FIXES
	AddServerCommands();
#endif

	TheBotPhrases->OnMapChange();
}

void CCSBotManager::AddServerCommand(const char *cmd)
{
	ADD_SERVER_COMMAND((char *)cmd, Bot_ServerCommand);
}

void CCSBotManager::AddServerCommands()
{
	static bool fFirstTime = true;

	if (!fFirstTime)
		return;

	fFirstTime = false;

	if (!AreBotsAllowed())
		return;

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

void CCSBotManager::ServerDeactivate()
{
	m_bServerActive = false;
}

void CCSBotManager::ClientDisconnect(CBasePlayer *pPlayer)
{
	if (!pPlayer || !pPlayer->IsBot())
		return;

	auto pevTemp = VARS(pPlayer->edict());

	CCSBot *pBot = static_cast<CCSBot *>(pPlayer);
	pBot->Disconnect();

	if (!FStringNull(pPlayer->pev->classname))
	{
		RemoveEntityHashValue(pPlayer->pev, STRING(pPlayer->pev->classname), CLASSNAME);
	}

	FREE_PRIVATE(pPlayer->edict());

	pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pevTemp);
	AddEntityHashValue(pPlayer->pev, STRING(pPlayer->pev->classname), CLASSNAME);
	pPlayer->pev->flags = FL_DORMANT;
}

void PrintAllEntities()
{
	for (int i = 1; i < gpGlobals->maxEntities; i++)
	{
		edict_t *edict = INDEXENT(i);

		if (!edict || FStringNull(edict->v.classname))
			continue;

		CONSOLE_ECHO("  %s\n", STRING(edict->v.classname));
	}
}

void CCSBotManager::ServerCommand(const char *pcmd)
{
	if (!m_bServerActive || !AreBotsAllowed())
		return;

	char buffer[400];
	const char *msg = CMD_ARGV(1);

	if (FStrEq(pcmd, "bot_about"))
	{
		Q_snprintf(buffer, sizeof(buffer),
			"\n--------------------------------------------------------------------------\n"
			"The Official Counter-Strike Bot V%d.%02d\n"
			"Created by Michael S. Booth\n"
			"Web: www.turtlerockstudios.com\\csbot\n"
			"E-mail: csbot@turtlerockstudios.com\n"
			"--------------------------------------------------------------------------\n\n", BOT_VERSION_MAJOR, BOT_VERSION_MINOR);

		CONSOLE_ECHO(buffer);
		HintMessageToAllPlayers(buffer);
	}
	else if (FStrEq(pcmd, "bot_add"))
	{
		BotAddCommand(BOT_TEAM_ANY, FROM_CONSOLE);
	}
	else if (FStrEq(pcmd, "bot_add_t"))
	{
		BotAddCommand(BOT_TEAM_T, FROM_CONSOLE);
	}
	else if (FStrEq(pcmd, "bot_add_ct"))
	{
		BotAddCommand(BOT_TEAM_CT, FROM_CONSOLE);
	}
	else if (FStrEq(pcmd, "bot_kill"))
	{
		bool killThemAll;
		if (CMD_ARGC() == 1 || FStrEq(msg, "all"))
			killThemAll = true;
		else
			killThemAll = false;

		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);
			if (!pPlayer)
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
#ifdef REGAMEDLL_FIXES
					ClientKill(pPlayer->edict());
#else
					pPlayer->TakeDamage(pPlayer->pev, pPlayer->pev, 9999.9f, DMG_CRUSH);
#endif
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

		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);
			if (!pPlayer)
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
					// adjust bot quota so kicked bot is not immediately added back in
					int newQuota = cv_bot_quota.value - 1;
					SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", name));
					CVAR_SET_FLOAT("bot_quota", clamp(newQuota, 0, int(cv_bot_quota.value)));
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
		m_editCmd = EDIT_DELETE;
	}
	else if (FStrEq(pcmd, "bot_nav_split"))
	{
		m_editCmd = EDIT_SPLIT;
	}
	else if (FStrEq(pcmd, "bot_nav_merge"))
	{
		m_editCmd = EDIT_MERGE;
	}
	else if (FStrEq(pcmd, "bot_nav_mark"))
	{
		m_editCmd = EDIT_MARK;
	}
	else if (FStrEq(pcmd, "bot_nav_begin_area"))
	{
		m_editCmd = EDIT_BEGIN_AREA;
	}
	else if (FStrEq(pcmd, "bot_nav_end_area"))
	{
		m_editCmd = EDIT_END_AREA;
	}
	else if (FStrEq(pcmd, "bot_nav_connect"))
	{
		m_editCmd = EDIT_CONNECT;
	}
	else if (FStrEq(pcmd, "bot_nav_disconnect"))
	{
		m_editCmd = EDIT_DISCONNECT;
	}
	else if (FStrEq(pcmd, "bot_nav_splice"))
	{
		m_editCmd = EDIT_SPLICE;
	}
	else if (FStrEq(pcmd, "bot_nav_crouch"))
	{
		m_editCmd = EDIT_ATTRIB_CROUCH;
	}
	else if (FStrEq(pcmd, "bot_nav_jump"))
	{
		m_editCmd = EDIT_ATTRIB_JUMP;
	}
	else if (FStrEq(pcmd, "bot_nav_precise"))
	{
		m_editCmd = EDIT_ATTRIB_PRECISE;
	}
	else if (FStrEq(pcmd, "bot_nav_no_jump"))
	{
		m_editCmd = EDIT_ATTRIB_NO_JUMP;
	}
	else if (FStrEq(pcmd, "bot_nav_analyze"))
	{
		m_isAnalysisRequested = true;
	}
	else if (FStrEq(pcmd, "bot_nav_strip"))
	{
		StripNavigationAreas();
	}
	else if (FStrEq(pcmd, "bot_nav_save"))
	{
		GET_GAME_DIR(buffer);
		Q_strcat(buffer, "\\");
		Q_strcat(buffer, CBotManager::GetNavMapFilename());

		if (SaveNavigationMap(buffer))
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
			// no arguments = list all available places
			int i = 0;
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();
			for (auto phrase : *placeList)
			{
				if (phrase->GetID() == GetNavPlace())
					CONSOLE_ECHO("--> %-26s", phrase->GetName());
				else
					CONSOLE_ECHO("%-30s", phrase->GetName());

				if (!(i % 3))
					CONSOLE_ECHO("\n");
				i++;
			}
			CONSOLE_ECHO("\n");
		}
		else
		{
			// single argument = set current place
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();
			const BotPhrase *found = nullptr;
			bool isAmbiguous = false;
			for (auto phrase : *placeList)
			{
				if (!Q_strnicmp(phrase->GetName(), msg, Q_strlen(msg)))
				{
					// check for exact match in case of subsets of other strings
					if (!Q_strcmp(phrase->GetName(), msg))
					{
						found = phrase;
						isAmbiguous = false;
						break;
					}

					if (found)
					{
						isAmbiguous = true;
					}
					else
					{
						found = phrase;
					}
				}
			}

			if (isAmbiguous)
			{
				CONSOLE_ECHO("Ambiguous\n");
			}
			else
			{
				CONSOLE_ECHO("Current place set to '%s'\n", found->GetName());
				SetNavPlace(found->GetID());
			}
		}
	}
	else if (FStrEq(pcmd, "bot_nav_toggle_place_mode"))
	{
		m_editCmd = EDIT_TOGGLE_PLACE_MODE;
	}
	else if (FStrEq(pcmd, "bot_nav_place_floodfill"))
	{
		m_editCmd = EDIT_PLACE_FLOODFILL;
	}
	else if (FStrEq(pcmd, "bot_nav_place_pick"))
	{
		m_editCmd = EDIT_PLACE_PICK;
	}
	else if (FStrEq(pcmd, "bot_nav_toggle_place_painting"))
	{
		m_editCmd = EDIT_TOGGLE_PLACE_PAINTING;
	}
	else if (FStrEq(pcmd, "bot_goto_mark"))
	{
		// tell the first bot we find to go to our marked area
		CNavArea *area = GetMarkedArea();
		if (area)
		{
			CBaseEntity *pEntity = nullptr;
			while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
			{
				if (!pEntity->IsPlayer())
					continue;

				if (pEntity->IsDormant())
					continue;

				CBasePlayer *playerOrBot = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

				if (playerOrBot->IsBot())
				{
					CCSBot *pBot = static_cast<CCSBot *>(playerOrBot);
					if (pBot)
					{
						pBot->MoveTo(&area->m_center, FASTEST_ROUTE);
					}

					break;
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
		for (auto area : TheNavAreaList)
		{
			for (auto se : area->m_spotEncounterList)
			{
				encounterMem += sizeof(SpotEncounter);
				encounterMem += sizeof(SpotOrder) * se.spotList.size();
			}
		}

		CONSOLE_ECHO("  Encounter Spot data = %d bytes\n", encounterMem);
	}
	else if (FStrEq(pcmd, "bot_nav_mark_unnamed"))
	{
		m_editCmd = EDIT_MARK_UNNAMED;
	}
	else if (FStrEq(pcmd, "bot_nav_warp"))
	{
		m_editCmd = EDIT_WARP_TO_MARK;
	}
	else if (FStrEq(pcmd, "bot_nav_corner_select"))
	{
		m_editCmd = EDIT_SELECT_CORNER;
	}
	else if (FStrEq(pcmd, "bot_nav_corner_raise"))
	{
		m_editCmd = EDIT_RAISE_CORNER;
	}
	else if (FStrEq(pcmd, "bot_nav_corner_lower"))
	{
		m_editCmd = EDIT_LOWER_CORNER;
	}
	else if (FStrEq(pcmd, "bot_nav_check_consistency"))
	{
		if (CMD_ARGC() != 2)
		{
			CONSOLE_ECHO("usage: bot_nav_check_consistency <filename>\n");
			return;
		}

		SanityCheckNavigationMap(msg);
	}
}

BOOL CCSBotManager::ClientCommand(CBasePlayer *pPlayer, const char *pcmd)
{
	return FALSE;
}

// Process the "bot_add" console command
bool CCSBotManager::BotAddCommand(BotProfileTeamType team, bool isFromConsole)
{
	// dont allow bots to join if the Navigation Area is being generated
	if (m_isLearningMap)
		return false;

	const BotProfile *profile = nullptr;
	if (!isFromConsole || CMD_ARGC() < 2)
	{
		// if team not specified, check cv_bot_join_team cvar for preference
		if (team == BOT_TEAM_ANY)
		{
			if (!Q_stricmp(cv_bot_join_team.string, "T"))
				team = BOT_TEAM_T;

			else if (!Q_stricmp(cv_bot_join_team.string, "CT"))
				team = BOT_TEAM_CT;
			else
			{
				TeamName defaultTeam = CSGameRules()->SelectDefaultTeam();
				if (defaultTeam == TERRORIST)
					team = BOT_TEAM_T;

				else if (defaultTeam == CT)
					team = BOT_TEAM_CT;
			}
		}

		// try to add a bot by name
		profile = TheBotProfiles->GetRandomProfile(GetDifficultyLevel(), team);
		if (!profile)
		{
			CONSOLE_ECHO("All bot profiles at this difficulty level are in use.\n");
			return true;
		}
	}
	else
	{
		// in career, ignore humans
		bool ignoreHumans = false;
		if (CSGameRules() && CSGameRules()->IsCareer())
			ignoreHumans = true;

		if (UTIL_IsNameTaken(CMD_ARGV(1), ignoreHumans))
		{
			CONSOLE_ECHO("Error - %s is already in the game.\n", CMD_ARGV(1));
			return true;
		}

		profile = TheBotProfiles->GetProfile(CMD_ARGV(1), team);
		if (!profile)
		{
			CONSOLE_ECHO("Error - no profile for '%s' exists.\n", CMD_ARGV(1));
			return true;
		}
	}

	// create the bot
	if (AddBot(profile, team))
	{
		if (isFromConsole)
		{
			// increase the bot quota to account for manually added bot
			CVAR_SET_FLOAT("bot_quota", cv_bot_quota.value + 1);
		}
	}
#ifdef REGAMEDLL_FIXES
	else
	{
		// decrease the bot quota
		CVAR_SET_FLOAT("bot_quota", cv_bot_quota.value - 1);
	}
#endif

	return true;
}

// Keep a minimum quota of bots in the game
void CCSBotManager::MaintainBotQuota()
{
#ifdef REGAMEDLL_FIXES
	if (!AreBotsAllowed())
		return;
#endif

	if (m_isLearningMap)
		return;

	int totalHumansInGame = UTIL_HumansInGame();
	int humanPlayersInGame = UTIL_HumansInGame(IGNORE_SPECTATORS);

	// don't add bots until local player has been registered, to make sure he's player ID #1
	if (!IS_DEDICATED_SERVER() && totalHumansInGame == 0)
		return;

	int desiredBotCount = int(cv_bot_quota.value);
	int occupiedBotSlots = UTIL_BotsInGame();

	// isRoundInProgress is true if the round has progressed far enough that new players will join as dead.
	bool isRoundInProgress = CSGameRules()->IsGameStarted() &&
							 !TheCSBots()->IsRoundOver() &&
							 (CSGameRules()->GetRoundElapsedTime() >= CSGameRules()->GetRoundRespawnTime());

#ifdef REGAMEDLL_ADD
	if (FStrEq(cv_bot_quota_mode.string, "fill"))
	{
		// If bot_quota_mode is 'fill', we want the number of bots and humans together to equal bot_quota
		// unless the round is already in progress, in which case we play with what we've been dealt
		if (!isRoundInProgress)
		{
			desiredBotCount = Q_max(0, desiredBotCount - humanPlayersInGame);
		}
		else
		{
			desiredBotCount = occupiedBotSlots;
		}
	}
	else if (FStrEq(cv_bot_quota_mode.string, "match"))
	{
		// If bot_quota_mode is 'match', we want the number of bots to be bot_quota * total humans
		// unless the round is already in progress, in which case we play with what we've been dealt
		if (!isRoundInProgress)
		{
			desiredBotCount = Q_max<int>(0, cv_bot_quota.value * humanPlayersInGame);
		}
		else
		{
			desiredBotCount = occupiedBotSlots;
		}
	}
#else // #ifdef REGAMEDLL_ADD
	if (cv_bot_quota_match.value > 0.0)
	{
		desiredBotCount = int(humanPlayersInGame * cv_bot_quota_match.value);
	}
#endif // #ifdef REGAMEDLL_ADD

	// wait for a player to join, if necessary
	if (cv_bot_join_after_player.value > 0.0)
	{
		if (humanPlayersInGame == 0)
			desiredBotCount = 0;
	}

#ifdef REGAMEDLL_ADD
	// wait until the map has been loaded for a bit, to allow players to transition across
	// the transition without missing the pistol round
	if (static_cast<int>(cv_bot_join_delay.value) > CSGameRules()->GetMapElapsedTime())
	{
		desiredBotCount = 0;
	}
#endif

	// if bots will auto-vacate, we need to keep one slot open to allow players to join
	if (cv_bot_auto_vacate.value > 0.0)
		desiredBotCount = Q_min(desiredBotCount, gpGlobals->maxClients - (totalHumansInGame + 1));
	else
		desiredBotCount = Q_min(desiredBotCount, gpGlobals->maxClients - totalHumansInGame);

#ifdef REGAMEDLL_FIXES
	// Try to balance teams, if we are in the first specified seconds of a round and bots can join either team.
	if (occupiedBotSlots > 0 && desiredBotCount == occupiedBotSlots && CSGameRules()->IsGameStarted())
	{
		if (CSGameRules()->GetRoundElapsedTime() < CSGameRules()->GetRoundRespawnTime()) // new bots can still spawn during this time
		{
			if (autoteambalance.value > 0.0f)
			{
				int numAliveTerrorist;
				int numAliveCT;
				int numDeadTerrorist;
				int numDeadCT;

				CSGameRules()->InitializePlayerCounts(numAliveTerrorist, numAliveCT, numDeadTerrorist, numDeadCT);

				if (!FStrEq(cv_bot_join_team.string, "T") &&
					!FStrEq(cv_bot_join_team.string, "CT"))
				{
					if (numAliveTerrorist > CSGameRules()->m_iNumCT + 1)
					{
						if (UTIL_KickBotFromTeam(TERRORIST))
							return;
					}
					else if (numAliveCT > CSGameRules()->m_iNumTerrorist + 1)
					{
						if (UTIL_KickBotFromTeam(CT))
							return;
					}
				}
			}
		}
	}
#endif // #ifdef REGAMEDLL_FIXES

	// add bots if necessary
	if (desiredBotCount > occupiedBotSlots)
	{
		// don't try to add a bot if all teams are full
		if (!CSGameRules()->TeamFull(TERRORIST) || !CSGameRules()->TeamFull(CT))
		{
#ifndef REGAMEDLL_FIXES
			if (AreBotsAllowed())
#endif
			{
				BotAddCommand(BOT_TEAM_ANY);
			}
		}
	}
	else if (desiredBotCount < occupiedBotSlots)
	{
		// kick a bot to maintain quota

		// first remove any unassigned bots
		if (UTIL_KickBotFromTeam(UNASSIGNED))
			return;

		TeamName kickTeam;

		// remove from the team that has more players
		if (CSGameRules()->m_iNumTerrorist > CSGameRules()->m_iNumCT)
		{
			kickTeam = TERRORIST;
		}
		else if (CSGameRules()->m_iNumTerrorist < CSGameRules()->m_iNumCT)
		{
			kickTeam = CT;
		}
		// remove from the team that's winning
		else if (CSGameRules()->m_iNumTerroristWins > CSGameRules()->m_iNumCTWins)
		{
			kickTeam = TERRORIST;
		}
		else if (CSGameRules()->m_iNumCTWins > CSGameRules()->m_iNumTerroristWins)
		{
			kickTeam = CT;
		}
		else
		{
			// teams and scores are equal, pick a team at random
			kickTeam = (RANDOM_LONG(0, 1) == 0) ? CT : TERRORIST;
		}

		// attempt to kick a bot from the given team
		bool atLeastOneKicked = UTIL_KickBotFromTeam(kickTeam);

		if (!atLeastOneKicked)
		{
			// if there were no bots on the team, kick a bot from the other team
			if (kickTeam == TERRORIST)
				atLeastOneKicked = UTIL_KickBotFromTeam(CT);
			else
				atLeastOneKicked = UTIL_KickBotFromTeam(TERRORIST);
		}

		if (atLeastOneKicked)
		{
			CONSOLE_ECHO("These bots kicked to maintain quota.\n");
		}
	}
	else
	{
		if (CSGameRules() && !CSGameRules()->IsCareer())
			return;

		bool humansAreCTs = (Q_strcmp(humans_join_team.string, "CT") == 0);

		if (humansAreCTs)
		{
			if (CSGameRules()->m_iNumCT <= 6)
				return;

			UTIL_KickBotFromTeam(CT);
		}
		else
		{
			if (CSGameRules()->m_iNumTerrorist <= 6)
				return;

			UTIL_KickBotFromTeam(TERRORIST);
		}

		CVAR_SET_FLOAT("bot_quota", cv_bot_quota.value - 1.0f);
	}
}

void CCSBotManager::MonitorBotCVars()
{
	if (cv_bot_nav_edit.value != 0.0f)
	{
		EditNavAreas(m_editCmd);
		m_editCmd = EDIT_NONE;
	}

	if (gpGlobals->time >= m_flNextCVarCheck)
	{
		if (cv_bot_show_danger.value != 0.0f)
			DrawDanger();

		MaintainBotQuota();
		m_flNextCVarCheck = gpGlobals->time + 0.3f;
	}
}

// Collect all nav areas that overlap the given zone
class CollectOverlappingAreas
{
public:
	CollectOverlappingAreas(CCSBotManager::Zone *zone)
	{
		m_zone = zone;
		zone->m_areaCount = 0;
	}
	bool operator()(CNavArea *area)
	{
		const Extent *areaExtent = area->GetExtent();

		if (areaExtent->hi.x >= m_zone->m_extent.lo.x && areaExtent->lo.x <= m_zone->m_extent.hi.x
			&& areaExtent->hi.y >= m_zone->m_extent.lo.y && areaExtent->lo.y <= m_zone->m_extent.hi.y
			&& areaExtent->hi.z >= m_zone->m_extent.lo.z && areaExtent->lo.z <= m_zone->m_extent.hi.z)
		{
			// area overlaps m_zone
			m_zone->m_area[m_zone->m_areaCount++] = area;
			if (m_zone->m_areaCount == CCSBotManager::MAX_ZONE_NAV_AREAS)
			{
				return false;
			}
		}

		return true;
	}

private:
	CCSBotManager::Zone *m_zone;
};

// Search the map entities to determine the game scenario and define important zones.
void CCSBotManager::ValidateMapData()
{
	if (m_isMapDataLoaded || !AreBotsAllowed())
		return;

	m_isMapDataLoaded = true;

	if (LoadNavigationMap())
	{
		CONSOLE_ECHO("Failed to load navigation map.\n");
		return;
	}

	CONSOLE_ECHO("Navigation map loaded.\n");

	m_zoneCount = 0;
	m_gameScenario = SCENARIO_DEATHMATCH;

	// Search all entities in the map and set the game type and store all zones (bomb target, etc).
	CBaseEntity *pEntity = nullptr;
	for (int i = 1; i < gpGlobals->maxEntities; i++)
	{
		pEntity = CBaseEntity::Instance(INDEXENT(i));
		if (!pEntity)
			continue;

		bool found = false;
		bool isLegacy = false;

		if (FClassnameIs(pEntity->pev, "func_bomb_target"))
		{
			m_gameScenario = SCENARIO_DEFUSE_BOMB;
			found = true;
			isLegacy = false;
		}
		else if (FClassnameIs(pEntity->pev, "info_bomb_target"))
		{
			m_gameScenario = SCENARIO_DEFUSE_BOMB;
			found = true;
			isLegacy = true;
		}
		else if (FClassnameIs(pEntity->pev, "func_hostage_rescue"))
		{
			m_gameScenario = SCENARIO_RESCUE_HOSTAGES;
			found = true;
			isLegacy = false;
		}
		else if (FClassnameIs(pEntity->pev, "info_hostage_rescue"))
		{
			m_gameScenario = SCENARIO_RESCUE_HOSTAGES;
			found = true;
			isLegacy = true;
		}
		else if (FClassnameIs(pEntity->pev, "hostage_entity"))
		{
			// some very old maps (ie: cs_assault) use info_player_start
			// as rescue zones, so set the scenario if there are hostages
			// in the map
			m_gameScenario = SCENARIO_RESCUE_HOSTAGES;
		}
		else if (FClassnameIs(pEntity->pev, "func_vip_safetyzone"))
		{
			m_gameScenario = SCENARIO_ESCORT_VIP;
			found = true;
			isLegacy = false;
		}

		if (found)
		{
			if (m_zoneCount < MAX_ZONES)
			{
				m_zone[m_zoneCount].m_center = isLegacy ? pEntity->pev->origin : (pEntity->pev->absmax + pEntity->pev->absmin) / 2.0f;
				m_zone[m_zoneCount].m_isLegacy = isLegacy;
				m_zone[m_zoneCount].m_index = m_zoneCount;
				m_zone[m_zoneCount].m_entity = pEntity;
				m_zoneCount++;
			}
			else
			{
				CONSOLE_ECHO("Warning: Too many zones, some will be ignored.\n");
			}
		}
	}

	// If there are no zones and the scenario is hostage rescue,
	// use the info_player_start entities as rescue zones.
	if (m_zoneCount == 0 && m_gameScenario == SCENARIO_RESCUE_HOSTAGES)
	{
		pEntity = nullptr;

		while ((pEntity = UTIL_FindEntityByClassname(pEntity, "info_player_start")))
		{
#ifdef REGAMEDLL_FIXES
			if (m_zoneCount >= MAX_ZONES)
				break;
#endif

			if (FNullEnt(pEntity->edict()))
				break;

			if (m_zoneCount < MAX_ZONES)
			{
				m_zone[m_zoneCount].m_center = pEntity->pev->origin;
				m_zone[m_zoneCount].m_isLegacy = true;
				m_zone[m_zoneCount].m_index = m_zoneCount;
				m_zone[m_zoneCount].m_entity = pEntity;
				m_zoneCount++;
			}
			else
			{
				CONSOLE_ECHO("Warning: Too many zones, some will be ignored.\n");
			}
		}
	}

	// Collect nav areas that overlap each zone
	for (int i = 0; i < m_zoneCount; i++)
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
		zone->m_extent.lo.z -= zFudge;
		zone->m_extent.hi.z += zFudge;

		// build a list of nav areas that overlap this zone
		CollectOverlappingAreas collector(zone);
		ForAllAreas(collector);
	}
}

bool CCSBotManager::AddBot(const BotProfile *profile, BotProfileTeamType team)
{
	if (!AreBotsAllowed())
		return false;

	int nTeamSlot = UNASSIGNED;
	if (team == BOT_TEAM_ANY)
	{
		// if team not specified, check cv_bot_join_team cvar for preference
		if (!Q_stricmp(cv_bot_join_team.string, "T"))
			nTeamSlot = TERRORIST;

		else if (!Q_stricmp(cv_bot_join_team.string, "CT"))
			nTeamSlot = CT;
	}
	else if (team == BOT_TEAM_CT)
		nTeamSlot = CT;

	else if (team == BOT_TEAM_T)
		nTeamSlot = TERRORIST;

	if (nTeamSlot == UNASSIGNED)
	{
		nTeamSlot = CSGameRules()->SelectDefaultTeam();
	}

	if (nTeamSlot == UNASSIGNED || CSGameRules()->TeamFull(nTeamSlot))
	{
		CONSOLE_ECHO("Could not add bot to the game: Team is full\n");
		return false;
	}

	if (CSGameRules()->TeamStacked(nTeamSlot, UNASSIGNED))
	{
		CONSOLE_ECHO("Could not add bot to the game: Team is stacked (to disable this check, set mp_limitteams and mp_autoteambalance to zero and restart the round).\n");
		return false;
	}

	CCSBot *pBot = CreateBot<CCSBot, CAPI_CSBot>(profile);
	if (!pBot)
	{
		return false;
	}

	//int nJoinedTeam;
	ClientPutInServer(pBot->edict());
	SET_CLIENT_KEY_VALUE(pBot->entindex(), GET_INFO_BUFFER(pBot->edict()), "*bot", "1");

	pBot->m_iMenu = Menu_ChooseTeam;
	pBot->m_iJoiningState = PICKINGTEAM;

	if (HandleMenu_ChooseTeam(pBot, nTeamSlot))
	{
		int skin = profile->GetSkin();
		if (!skin)
			skin = 6;

		HandleMenu_ChooseAppearance(pBot, skin);

		if (IS_DEDICATED_SERVER())
		{
			UTIL_DPrintf("Added bot %s to server\n", STRING(pBot->pev->netname));
		}

		return true;
	}

	SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", STRING(pBot->pev->netname)));
	CONSOLE_ECHO("Could not add bot to the game.\n");
	return false;
}

// Return the zone that contains the given position
const CCSBotManager::Zone *CCSBotManager::GetZone(const Vector *pos) const
{
	for (int z = 0; z < m_zoneCount; z++)
	{
		if (m_zone[z].m_extent.Contains(pos))
		{
			return &m_zone[z];
		}
	}

	return nullptr;
}

// Return the closest zone to the given position
const CCSBotManager::Zone *CCSBotManager::GetClosestZone(const Vector *pos) const
{
	const Zone *close = nullptr;
	float closeRangeSq = 1e9f;

	for (int z = 0; z < m_zoneCount; z++)
	{
		float rangeSq = (m_zone[z].m_center - (*pos)).LengthSquared();

		if (rangeSq < closeRangeSq)
		{
			closeRangeSq = rangeSq;
			close = &m_zone[z];
		}
	}

	return close;
}

// Return a random position inside the given zone
const Vector *CCSBotManager::GetRandomPositionInZone(const Zone *zone) const
{
	static Vector pos;

	if (!zone)
		return nullptr;

	if (zone->m_areaCount == 0)
		return nullptr;

	// pick a random overlapping area
	CNavArea *area = GetRandomAreaInZone(zone);

	// pick a location inside both the nav area and the zone
	// TODO: Randomize this
	if (zone->m_isLegacy)
	{
		// TODO: It is possible that the radius might not overlap this area at all...
		area->GetClosestPointOnArea(&zone->m_center, &pos);
	}
	else
	{
		const Extent &areaExtent = *area->GetExtent();
		Extent overlap;
		overlap.lo.x = Q_max(areaExtent.lo.x, zone->m_extent.lo.x);
		overlap.lo.y = Q_max(areaExtent.lo.y, zone->m_extent.lo.y);
		overlap.hi.x = Q_min(areaExtent.hi.x, zone->m_extent.hi.x);
		overlap.hi.y = Q_min(areaExtent.hi.y, zone->m_extent.hi.y);

		pos.x = (overlap.lo.x + overlap.hi.x) / 2.0f;
		pos.y = (overlap.lo.y + overlap.hi.y) / 2.0f;
		pos.z = area->GetZ(&pos);
	}

	return &pos;
}

// Return a random area inside the given zone
CNavArea *CCSBotManager::GetRandomAreaInZone(const Zone *zone) const
{
	// TODO: improvement is needed
	if (!zone->m_areaCount)
		return nullptr;

	return zone->m_area[RANDOM_LONG(0, zone->m_areaCount - 1)];
}

void CCSBotManager::OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	switch (event)
	{
	case EVENT_BOMB_PLANTED:
		m_isBombPlanted = true;
		m_bombPlantTimestamp = gpGlobals->time;
		break;

	case EVENT_BOMB_DEFUSING:
		m_bombDefuser = static_cast<CBasePlayer *>(pEntity);
		break;

	case EVENT_BOMB_DEFUSE_ABORTED:
		m_bombDefuser = nullptr;
		break;

	case EVENT_BOMB_DEFUSED:
		m_isBombPlanted = false;
		m_bombDefuser = nullptr;
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

	CBotManager::OnEvent(event, pEntity, pOther);
}

// Get the time remaining before the planted bomb explodes
float CCSBotManager::GetBombTimeLeft() const
{
	return (CSGameRules()->m_iC4Timer - (gpGlobals->time - m_bombPlantTimestamp));
}

void CCSBotManager::SetLooseBomb(CBaseEntity *bomb)
{
	m_looseBomb = bomb;

	if (bomb)
	{
		m_looseBombArea = TheNavAreaGrid.GetNearestNavArea(&bomb->pev->origin);
	}
	else
	{
		m_looseBombArea = nullptr;
	}
}

// Return true if player is important to scenario (VIP, bomb carrier, etc)
bool CCSBotManager::IsImportantPlayer(CBasePlayer *pPlayer) const
{
	switch (GetScenario())
	{
		case SCENARIO_DEFUSE_BOMB:
		{
			if (pPlayer->m_iTeam == TERRORIST && pPlayer->IsBombGuy())
				return true;

			// TODO: TEAM_CT's defusing the bomb are important
			return false;
		}
		case SCENARIO_ESCORT_VIP:
		{
			if (pPlayer->m_iTeam == CT && pPlayer->m_bIsVIP)
				return true;

			return false;
		}
		case SCENARIO_RESCUE_HOSTAGES:
		{
			// TODO: TEAM_CT's escorting hostages are important
			return false;
		}
	}

	// everyone is equally important in a deathmatch
	return false;
}

// Return priority of player (0 = max pri)
unsigned int CCSBotManager::GetPlayerPriority(CBasePlayer *pPlayer) const
{
	const unsigned int lowestPriority = 0xFFFFFFFF;

	if (!pPlayer->IsPlayer())
		return lowestPriority;

	// human players have highest priority
	if (!pPlayer->IsBot())
		return 0;

	CCSBot *pBot = static_cast<CCSBot *>(pPlayer);

	// bots doing something important for the current scenario have high priority
	switch (GetScenario())
	{
	case SCENARIO_DEFUSE_BOMB:
	{
		// the bomb carrier has high priority
		if (pBot->m_iTeam == TERRORIST && pBot->m_bHasC4)
			return 1;

		break;
	}
	case SCENARIO_ESCORT_VIP:
	{
		// the VIP has high priority
		if (pBot->m_iTeam == CT && pBot->m_bIsVIP)
			return 1;

		break;
	}
	case SCENARIO_RESCUE_HOSTAGES:
	{
		// TEAM_CT's rescuing hostages have high priority
		if (pBot->m_iTeam == CT && pBot->GetHostageEscortCount())
			return 1;

		break;
	}
	}

	// everyone else is ranked by their unique ID (which cannot be zero)
	return 1 + pBot->GetID();
}

// Return the last time the given radio message was sent for given team
// 'teamID' can be TEAM_CT or TEAM_TERRORIST
float CCSBotManager::GetRadioMessageTimestamp(GameEventType event, int teamID) const
{
	if (event <= EVENT_START_RADIO_1 || event >= EVENT_END_RADIO)
		return 0.0f;

	int i = (teamID == TERRORIST) ? 0 : 1;
	return m_radioMsgTimestamp[event - EVENT_START_RADIO_1][i];
}

// Return the interval since the last time this message was sent
float CCSBotManager::GetRadioMessageInterval(GameEventType event, int teamID) const
{
	if (event <= EVENT_START_RADIO_1 || event >= EVENT_END_RADIO)
		return 99999999.9f;

	int i = (teamID == TERRORIST) ? 0 : 1;
	return gpGlobals->time - m_radioMsgTimestamp[event - EVENT_START_RADIO_1][i];
}

// Set the given radio message timestamp.
// 'teamID' can be TEAM_CT or TEAM_TERRORIST
void CCSBotManager::SetRadioMessageTimestamp(GameEventType event, int teamID)
{
	if (event <= EVENT_START_RADIO_1 || event >= EVENT_END_RADIO)
		return;

	int i = (teamID == TERRORIST) ? 0 : 1;
	m_radioMsgTimestamp[event - EVENT_START_RADIO_1][i] = gpGlobals->time;
}

// Reset all radio message timestamps
void CCSBotManager::ResetRadioMessageTimestamps()
{
	Q_memset(m_radioMsgTimestamp, 0, sizeof(m_radioMsgTimestamp));
}

void CCSBotManager::OnFreeEntPrivateData(CBaseEntity *pEntity)
{
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);
		if (!pPlayer || pPlayer->IsDormant())
			continue;

		if (pPlayer->IsBot())
		{
			CCSBot *pBot = static_cast<CCSBot *>(pPlayer);
			if (pBot->m_attacker == pEntity)
				pBot->m_attacker = nullptr;

			if (pBot->m_bomber == pEntity)
				pBot->m_bomber = nullptr;
		}
	}
}
