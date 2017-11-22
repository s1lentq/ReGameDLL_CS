#include "precompiled.h"

void InstallCommands()
{
	static bool installedCommands = false;
	if (installedCommands)
		return;

	if (AreRunningCZero())
	{
		ADD_SERVER_COMMAND("career_continue", SV_Continue_f);
		ADD_SERVER_COMMAND("career_matchlimit", SV_CareerMatchLimit_f);
		ADD_SERVER_COMMAND("career_add_task", SV_CareerAddTask_f);
		ADD_SERVER_COMMAND("career_endround", SV_Career_EndRound_f);
		ADD_SERVER_COMMAND("career_restart", SV_Career_Restart_f);
		ADD_SERVER_COMMAND("tutor_toggle", SV_Tutor_Toggle_f);
	}

	ADD_SERVER_COMMAND("perf_test", SV_LoopPerformance_f);
	ADD_SERVER_COMMAND("print_ent", SV_PrintEntities_f);

	installedCommands = true;
}

void SV_Continue_f()
{
	if (CSGameRules()->IsCareer() && CSGameRules()->m_flRestartRoundTime > 100000.0)
	{
		CSGameRules()->m_flRestartRoundTime = gpGlobals->time;

		// go continue
		MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
			WRITE_STRING("GOGOGO");
		MESSAGE_END();

		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

			if (pPlayer && !pPlayer->IsBot())
			{
				// at the end of the round is showed window with the proposal surrender or continue
				// now of this time HUD is completely hidden
				// we must to restore HUD after entered continued
				pPlayer->m_iHideHUD &= ~HIDEHUD_ALL;
			}
		}
	}
}

void SV_CareerMatchLimit_f()
{
	if (CMD_ARGC() != 3)
	{
		return;
	}

	if (CSGameRules()->IsCareer())
	{
		CSGameRules()->SetCareerMatchLimit(Q_atoi(CMD_ARGV(1)), Q_atoi(CMD_ARGV(2)));
	}
}

void SV_CareerAddTask_f()
{
	if (CMD_ARGC() != 7)
		return;

	const char *taskName = CMD_ARGV(1);
	const char *weaponName = CMD_ARGV(2);

	int reps = Q_atoi(CMD_ARGV(3));
	bool mustLive = Q_atoi(CMD_ARGV(4)) != 0;
	bool crossRounds = Q_atoi(CMD_ARGV(5)) != 0;
	bool isComplete = Q_atoi(CMD_ARGV(6)) != 0;

	if (TheCareerTasks)
	{
		TheCareerTasks->AddTask(taskName, weaponName, reps, mustLive, crossRounds, isComplete);
	}
}

void SV_Career_EndRound_f()
{
	if (!CSGameRules()->IsCareer() || !CSGameRules()->IsInCareerRound())
	{
		return;
	}

	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		SERVER_COMMAND("kill\n");

		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

			if (!pPlayer || FNullEnt(pPlayer->pev))
				continue;

			if (pPlayer->IsBot() && pPlayer->m_iTeam == pLocalPlayer->m_iTeam)
			{
				SERVER_COMMAND(UTIL_VarArgs("bot_kill \"%s\"\n", STRING(pPlayer->pev->netname)));
			}
		}
	}
}

void SV_Career_Restart_f()
{
	if (CSGameRules()->IsCareer())
	{
		CSGameRules()->CareerRestart();
	}
}

void SV_Tutor_Toggle_f()
{
	CVAR_SET_FLOAT("tutor_enable", (CVAR_GET_FLOAT("tutor_enable") <= 0.0));
}

void SV_LoopPerformance_f()
{
	CCounter loopCounter;
	loopCounter.Init();

	double start, end;
	int i;

	start = loopCounter.GetCurTime();

	for (i = 0; i < 100; i++)
	{
		CBaseEntity *pSpot;
		for (pSpot = UTIL_FindEntityByString_Old(nullptr, "classname", "info_player_start"); pSpot; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "info_player_start"))
			;

		for (pSpot = UTIL_FindEntityByString_Old(nullptr, "classname", "info_player_deathmatch"); pSpot; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "info_player_deathmatch"))
			;

		for (pSpot = UTIL_FindEntityByString_Old(nullptr, "classname", "player"); pSpot; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "player"))
			;

		for (pSpot = UTIL_FindEntityByString_Old(nullptr, "classname", "bodyque"); pSpot; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "bodyque"))
			;
	}

	end = loopCounter.GetCurTime();
	CONSOLE_ECHO(" Time in old search loop %.4f\n", (end - start) * 1000.0);

	// check time new search loop
	start = loopCounter.GetCurTime();

	for (i = 0; i < 100; i++)
	{
		CBaseEntity *pSpot;
		for (pSpot = UTIL_FindEntityByClassname(nullptr, "info_player_start"); pSpot; pSpot = UTIL_FindEntityByClassname(pSpot, "info_player_start"))
			;

		for (pSpot = UTIL_FindEntityByClassname(nullptr, "info_player_deathmatch"); pSpot; pSpot = UTIL_FindEntityByClassname(pSpot, "info_player_deathmatch"))
			;

		for (pSpot = UTIL_FindEntityByClassname(nullptr, "player"); pSpot; pSpot = UTIL_FindEntityByClassname(pSpot, "player"))
			;

		for (pSpot = UTIL_FindEntityByClassname(nullptr, "bodyque"); pSpot; pSpot = UTIL_FindEntityByClassname(pSpot, "bodyque"))
			;
	}

	end = loopCounter.GetCurTime();
	CONSOLE_ECHO(" Time in new search loop %.4f\n", (end - start) * 1000.0);
}

void SV_PrintEntities_f()
{
	for (int i = 0; i < stringsHashTable.Count(); i++)
	{
		hash_item_t *item = &stringsHashTable[i];

		if (item->pev)
		{
			UTIL_LogPrintf("Print: %s %i %p\n", STRING(stringsHashTable[i].pev->classname), ENTINDEX(ENT(item->pev)), item->pev);
		}

		for (item = stringsHashTable[i].next; item; item = item->next)
		{
			UTIL_LogPrintf("Print: %s %i %p\n", STRING(item->pev->classname), ENTINDEX(ENT(item->pev)), item->pev);
		}
	}
}
