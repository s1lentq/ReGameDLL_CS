#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

cvar_t *g_psv_gravity = NULL;
cvar_t *g_psv_aim = NULL;
cvar_t *g_footsteps = NULL;
cvar_t *g_psv_accelerate = NULL;
cvar_t *g_psv_friction = NULL;
cvar_t *g_psv_stopspeed = NULL;
cvar_t displaysoundlist = { "displaysoundlist", "0", 0, 0.0f, NULL };
cvar_t timelimit = { "mp_timelimit", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t flashlight = { "mp_flashlight", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t decalfrequency = { "decalfrequency", "30", FCVAR_SERVER, 0.0f, NULL };
cvar_t fadetoblack = { "mp_fadetoblack", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t fragsleft = { "mp_fragsleft", "0", FCVAR_SERVER | FCVAR_UNLOGGED, 0.0f, NULL };
cvar_t timeleft = { "mp_timeleft", "0", FCVAR_SERVER | FCVAR_UNLOGGED, 0.0f, NULL };
cvar_t friendlyfire = { "mp_friendlyfire", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t allowmonsters = { "mp_allowmonsters", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t roundtime = { "mp_roundtime", "5", FCVAR_SERVER, 0.0f, NULL };
cvar_t buytime = { "mp_buytime", "1.5", FCVAR_SERVER, 0.0f, NULL };
cvar_t freezetime = { "mp_freezetime", "6", FCVAR_SERVER, 0.0f, NULL };
cvar_t c4timer = { "mp_c4timer", "45", FCVAR_SERVER, 0.0f, NULL };
cvar_t ghostfrequency = { "mp_ghostfrequency", "0.1", FCVAR_SERVER, 0.0f, NULL };
cvar_t autokick = { "mp_autokick", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t autokick_timeout = { "mp_autokick_timeout", "-1", FCVAR_SERVER, 0.0f, NULL };
cvar_t restartround = { "sv_restartround", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t sv_restart = { "sv_restart", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t limitteams = { "mp_limitteams", "2", FCVAR_SERVER, 0.0f, NULL };
cvar_t autoteambalance = { "mp_autoteambalance", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t tkpunish = { "mp_tkpunish", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t hostagepenalty = { "mp_hostagepenalty", "13", FCVAR_SERVER, 0.0f, NULL };
cvar_t mirrordamage = { "mp_mirrordamage", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t logmessages = { "mp_logmessages", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t forcecamera = { "mp_forcecamera", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t forcechasecam = { "mp_forcechasecam", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t mapvoteratio = { "mp_mapvoteratio", "0.66", FCVAR_SERVER, 0.0f, NULL };
cvar_t logdetail = { "mp_logdetail", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t startmoney = { "mp_startmoney", "800", FCVAR_SERVER, 0.0f, NULL };
cvar_t maxrounds = { "mp_maxrounds", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t winlimit = { "mp_winlimit", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t windifference = { "mp_windifference", "1", FCVAR_SERVER, 0.0f, NULL };
cvar_t playerid = { "mp_playerid", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t allow_spectators = { "allow_spectators", "1.0", FCVAR_SERVER, 0.0f, NULL };
cvar_t mp_chattime = { "mp_chattime", "10", FCVAR_SERVER, 0.0f, NULL };
cvar_t kick_percent = { "mp_kickpercent", "0.66", FCVAR_SERVER, 0.0f, NULL };
cvar_t humans_join_team = { "humans_join_team", "any", FCVAR_SERVER, 0.0f, NULL };
cvar_t sk_plr_9mm_bullet1 = { "sk_plr_9mm_bullet1", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mm_bullet2 = { "sk_plr_9mm_bullet2", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mm_bullet3 = { "sk_plr_9mm_bullet3", "0", 0, 0.0f, NULL };
cvar_t sk_plr_357_bullet1 = { "sk_plr_357_bullet1", "0", 0, 0.0f, NULL };
cvar_t sk_plr_357_bullet2 = { "sk_plr_357_bullet2", "0", 0, 0.0f, NULL };
cvar_t sk_plr_357_bullet3 = { "sk_plr_357_bullet3", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mmAR_bullet1 = { "sk_plr_9mmAR_bullet1", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mmAR_bullet2 = { "sk_plr_9mmAR_bullet2", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mmAR_bullet3 = { "sk_plr_9mmAR_bullet3", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mmAR_grenade1 = { "sk_plr_9mmAR_grenade1", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mmAR_grenade2 = { "sk_plr_9mmAR_grenade2", "0", 0, 0.0f, NULL };
cvar_t sk_plr_9mmAR_grenade3 = { "sk_plr_9mmAR_grenade3", "0", 0, 0.0f, NULL };
cvar_t sk_plr_buckshot1 = { "sk_plr_buckshot1", "0", 0, 0.0f, NULL };
cvar_t sk_plr_buckshot2 = { "sk_plr_buckshot2", "0", 0, 0.0f, NULL };
cvar_t sk_plr_buckshot3 = { "sk_plr_buckshot3", "0", 0, 0.0f, NULL };
cvar_t sk_plr_rpg1 = { "sk_plr_rpg1", "0", 0, 0.0f, NULL };
cvar_t sk_plr_rpg2 = { "sk_plr_rpg2", "0", 0, 0.0f, NULL };
cvar_t sk_plr_rpg3 = { "sk_plr_rpg3", "0", 0, 0.0f, NULL };
cvar_t sk_12mm_bullet1 = { "sk_12mm_bullet1", "0", 0, 0.0f, NULL };
cvar_t sk_12mm_bullet2 = { "sk_12mm_bullet2", "0", 0, 0.0f, NULL };
cvar_t sk_12mm_bullet3 = { "sk_12mm_bullet3", "0", 0, 0.0f, NULL };
cvar_t sk_9mmAR_bullet1 = { "sk_9mmAR_bullet1", "0", 0, 0.0f, NULL };
cvar_t sk_9mmAR_bullet2 = { "sk_9mmAR_bullet2", "0", 0, 0.0f, NULL };
cvar_t sk_9mmAR_bullet3 = { "sk_9mmAR_bullet3", "0", 0, 0.0f, NULL };
cvar_t sk_9mm_bullet1 = { "sk_9mm_bullet1", "0", 0, 0.0f, NULL };
cvar_t sk_9mm_bullet2 = { "sk_9mm_bullet2", "0", 0, 0.0f, NULL };
cvar_t sk_9mm_bullet3 = { "sk_9mm_bullet3", "0", 0, 0.0f, NULL };
cvar_t sk_suitcharger1 = { "sk_suitcharger1", "0", 0, 0.0f, NULL };
cvar_t sk_suitcharger2 = { "sk_suitcharger2", "0", 0, 0.0f, NULL };
cvar_t sk_suitcharger3 = { "sk_suitcharger3", "0", 0, 0.0f, NULL };
cvar_t sk_battery1 = { "sk_battery1", "0", 0, 0.0f, NULL };
cvar_t sk_battery2 = { "sk_battery2", "0", 0, 0.0f, NULL };
cvar_t sk_battery3 = { "sk_battery3", "0", 0, 0.0f, NULL };
cvar_t sk_healthcharger1 = { "sk_healthcharger1", "0", 0, 0.0f, NULL };
cvar_t sk_healthcharger2 = { "sk_healthcharger2", "0", 0, 0.0f, NULL };
cvar_t sk_healthcharger3 = { "sk_healthcharger3", "0", 0, 0.0f, NULL };
cvar_t sk_healthkit1 = { "sk_healthkit1", "0", 0, 0.0f, NULL };
cvar_t sk_healthkit2 = { "sk_healthkit2", "0", 0, 0.0f, NULL };
cvar_t sk_healthkit3 = { "sk_healthkit3", "0", 0, 0.0f, NULL };
cvar_t sk_scientist_heal1 = { "sk_scientist_heal1", "0", 0, 0.0f, NULL };
cvar_t sk_scientist_heal2 = { "sk_scientist_heal2", "0", 0, 0.0f, NULL };
cvar_t sk_scientist_heal3 = { "sk_scientist_heal3", "0", 0, 0.0f, NULL };

#endif // HOOK_GAMEDLL

#ifdef REGAMEDLL_ADD

cvar_t game_version = { "game_version", APP_VERSION_STRD, FCVAR_SERVER, 0.0f, NULL };
cvar_t maxmoney = { "mp_maxmoney", "16000", FCVAR_SERVER, 0.0f, NULL };
cvar_t round_infinite = { "mp_round_infinite", "0", FCVAR_SERVER, 0.0f, NULL };

void GameDLL_Version_f()
{
	if (Q_stricmp(CMD_ARGV(1), "version") != 0)
		return;

	// print version
	CONSOLE_ECHO("ReGameDLL build: " __TIME__ " " __DATE__ " (" APP_VERSION_STRD ")\n");
	CONSOLE_ECHO("ReGameDLL API version %i.%i\n", REGAMEDLL_API_VERSION_MAJOR, REGAMEDLL_API_VERSION_MINOR);
	CONSOLE_ECHO("Build from: " APP_COMMITS_URL APP_COMMIT_ID " " APP_COMMIT_AUTHOR "\n");
}

void GameDLL_EndRound_f()
{
	EndRoundMessage("#Round_Draw", ROUND_END_DRAW);
	Broadcast("rounddraw");
	CSGameRules()->TerminateRound(5, WINSTATUS_DRAW);
}

#endif // REGAMEDLL_ADD

void EXT_FUNC GameDLLInit()
{
	g_psv_gravity = CVAR_GET_POINTER("sv_gravity");
	g_psv_aim = CVAR_GET_POINTER("sv_aim");
	g_footsteps = CVAR_GET_POINTER("mp_footsteps");
	g_psv_accelerate = CVAR_GET_POINTER("sv_accelerate");
	g_psv_friction = CVAR_GET_POINTER("sv_friction");
	g_psv_stopspeed = CVAR_GET_POINTER("sv_stopspeed");

	CVAR_REGISTER(&displaysoundlist);
	CVAR_REGISTER(&timelimit);
	CVAR_REGISTER(&friendlyfire);
	CVAR_REGISTER(&flashlight);
	CVAR_REGISTER(&decalfrequency);
	CVAR_REGISTER(&allowmonsters);
	CVAR_REGISTER(&roundtime);
	CVAR_REGISTER(&buytime);
	CVAR_REGISTER(&freezetime);
	CVAR_REGISTER(&c4timer);
	CVAR_REGISTER(&ghostfrequency);
	CVAR_REGISTER(&autokick);
	CVAR_REGISTER(&autokick_timeout);
	CVAR_REGISTER(&restartround);
	CVAR_REGISTER(&sv_restart);
	CVAR_REGISTER(&limitteams);
	CVAR_REGISTER(&autoteambalance);
	CVAR_REGISTER(&tkpunish);
	CVAR_REGISTER(&hostagepenalty);
	CVAR_REGISTER(&mirrordamage);
	CVAR_REGISTER(&logmessages);
	CVAR_REGISTER(&forcecamera);
	CVAR_REGISTER(&forcechasecam);
	CVAR_REGISTER(&mapvoteratio);
	CVAR_REGISTER(&maxrounds);
	CVAR_REGISTER(&winlimit);
	CVAR_REGISTER(&windifference);
	CVAR_REGISTER(&fadetoblack);
	CVAR_REGISTER(&logdetail);
	CVAR_REGISTER(&startmoney);
	CVAR_REGISTER(&playerid);
	CVAR_REGISTER(&allow_spectators);
	CVAR_REGISTER(&mp_chattime);
	CVAR_REGISTER(&kick_percent);
	CVAR_REGISTER(&fragsleft);
	CVAR_REGISTER(&timeleft);
	CVAR_REGISTER(&humans_join_team);

// Remove unused cvars
#ifndef REGAMEDLL_FIXES

	CVAR_REGISTER(&sk_plr_9mm_bullet1);
	CVAR_REGISTER(&sk_plr_9mm_bullet2);
	CVAR_REGISTER(&sk_plr_9mm_bullet3);
	CVAR_REGISTER(&sk_plr_357_bullet1);
	CVAR_REGISTER(&sk_plr_357_bullet2);
	CVAR_REGISTER(&sk_plr_357_bullet3);
	CVAR_REGISTER(&sk_plr_9mmAR_bullet1);
	CVAR_REGISTER(&sk_plr_9mmAR_bullet2);
	CVAR_REGISTER(&sk_plr_9mmAR_bullet3);
	CVAR_REGISTER(&sk_plr_9mmAR_grenade1);
	CVAR_REGISTER(&sk_plr_9mmAR_grenade2);
	CVAR_REGISTER(&sk_plr_9mmAR_grenade3);
	CVAR_REGISTER(&sk_plr_buckshot1);
	CVAR_REGISTER(&sk_plr_buckshot2);
	CVAR_REGISTER(&sk_plr_buckshot3);
	CVAR_REGISTER(&sk_plr_rpg1);
	CVAR_REGISTER(&sk_plr_rpg2);
	CVAR_REGISTER(&sk_plr_rpg3);
	CVAR_REGISTER(&sk_12mm_bullet1);
	CVAR_REGISTER(&sk_12mm_bullet2);
	CVAR_REGISTER(&sk_12mm_bullet3);
	CVAR_REGISTER(&sk_9mmAR_bullet1);
	CVAR_REGISTER(&sk_9mmAR_bullet2);
	CVAR_REGISTER(&sk_9mmAR_bullet3);
	CVAR_REGISTER(&sk_9mm_bullet1);
	CVAR_REGISTER(&sk_9mm_bullet2);
	CVAR_REGISTER(&sk_9mm_bullet3);
	CVAR_REGISTER(&sk_suitcharger1);
	CVAR_REGISTER(&sk_suitcharger2);
	CVAR_REGISTER(&sk_suitcharger3);
	CVAR_REGISTER(&sk_battery1);
	CVAR_REGISTER(&sk_battery2);
	CVAR_REGISTER(&sk_battery3);
	CVAR_REGISTER(&sk_healthcharger1);
	CVAR_REGISTER(&sk_healthcharger2);
	CVAR_REGISTER(&sk_healthcharger3);
	CVAR_REGISTER(&sk_healthkit1);
	CVAR_REGISTER(&sk_healthkit2);
	CVAR_REGISTER(&sk_healthkit3);
	CVAR_REGISTER(&sk_scientist_heal1);
	CVAR_REGISTER(&sk_scientist_heal2);
	CVAR_REGISTER(&sk_scientist_heal3);

#endif // REGAMEDLL_FIXES

#ifdef REGAMEDLL_ADD

	ADD_SERVER_COMMAND("game", GameDLL_Version_f);
	ADD_SERVER_COMMAND("endround", GameDLL_EndRound_f);

	CVAR_REGISTER(&game_version);
	CVAR_REGISTER(&maxmoney);
	CVAR_REGISTER(&round_infinite);

	// print version
	CONSOLE_ECHO("ReGameDLL build: " __TIME__ " " __DATE__ " (" APP_VERSION_STRD ")\n");
	CONSOLE_ECHO("ReGameDLL API version %i.%i\n", REGAMEDLL_API_VERSION_MAJOR, REGAMEDLL_API_VERSION_MINOR);

#endif // REGAMEDLL_ADD

	Bot_RegisterCvars();
	Tutor_RegisterCVars();
	Hostage_RegisterCVars();
}

void EXT_FUNC GameDLLShutdown()
{
	Regamedll_FreeEntities();
}
