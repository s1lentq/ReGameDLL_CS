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

#else // HOOK_GAMEDLL

cvar_t *g_psv_gravity;
cvar_t *g_psv_aim;
cvar_t *g_footsteps;
cvar_t *g_psv_accelerate;
cvar_t *g_psv_friction;
cvar_t *g_psv_stopspeed;

cvar_t displaysoundlist;
cvar_t timelimit;
cvar_t flashlight;
cvar_t decalfrequency;
cvar_t fadetoblack;
cvar_t fragsleft;
cvar_t timeleft;
cvar_t friendlyfire;
cvar_t allowmonsters;
cvar_t roundtime;
cvar_t buytime;
cvar_t freezetime;
cvar_t c4timer;
cvar_t ghostfrequency;
cvar_t autokick;
cvar_t autokick_timeout;
cvar_t restartround;
cvar_t sv_restart;
cvar_t limitteams;
cvar_t autoteambalance;
cvar_t tkpunish;
cvar_t hostagepenalty;
cvar_t mirrordamage;
cvar_t logmessages;
cvar_t forcecamera;
cvar_t forcechasecam;
cvar_t mapvoteratio;
cvar_t logdetail;
cvar_t startmoney;
cvar_t maxrounds;
cvar_t winlimit;
cvar_t windifference;
cvar_t playerid;
cvar_t allow_spectators;
cvar_t mp_chattime;
cvar_t kick_percent;
cvar_t humans_join_team;

// NOXREF
//cvar_t sk_agrunt_health1;
//cvar_t sk_agrunt_health2;
//cvar_t sk_agrunt_health3;
//cvar_t sk_agrunt_dmg_punch1;
//cvar_t sk_agrunt_dmg_punch2;
//cvar_t sk_agrunt_dmg_punch3;
//cvar_t sk_apache_health1;
//cvar_t sk_apache_health2;
//cvar_t sk_apache_health3;
//cvar_t sk_barney_health1;
//cvar_t sk_barney_health2;
//cvar_t sk_barney_health3;
//cvar_t sk_bullsquid_health1;
//cvar_t sk_bullsquid_health2;
//cvar_t sk_bullsquid_health3;
//cvar_t sk_bullsquid_dmg_bite1;
//cvar_t sk_bullsquid_dmg_bite2;
//cvar_t sk_bullsquid_dmg_bite3;
//cvar_t sk_bullsquid_dmg_whip1;
//cvar_t sk_bullsquid_dmg_whip2;
//cvar_t sk_bullsquid_dmg_whip3;
//cvar_t sk_bullsquid_dmg_spit1;
//cvar_t sk_bullsquid_dmg_spit2;
//cvar_t sk_bullsquid_dmg_spit3;
//cvar_t sk_bigmomma_health_factor1;
//cvar_t sk_bigmomma_health_factor2;
//cvar_t sk_bigmomma_health_factor3;
//cvar_t sk_bigmomma_dmg_slash1;
//cvar_t sk_bigmomma_dmg_slash2;
//cvar_t sk_bigmomma_dmg_slash3;
//cvar_t sk_bigmomma_dmg_blast1;
//cvar_t sk_bigmomma_dmg_blast2;
//cvar_t sk_bigmomma_dmg_blast3;
//cvar_t sk_bigmomma_radius_blast1;
//cvar_t sk_bigmomma_radius_blast2;
//cvar_t sk_bigmomma_radius_blast3;
//cvar_t sk_gargantua_health1;
//cvar_t sk_gargantua_health2;
//cvar_t sk_gargantua_health3;
//cvar_t sk_gargantua_dmg_slash1;
//cvar_t sk_gargantua_dmg_slash2;
//cvar_t sk_gargantua_dmg_slash3;
//cvar_t sk_gargantua_dmg_fire1;
//cvar_t sk_gargantua_dmg_fire2;
//cvar_t sk_gargantua_dmg_fire3;
//cvar_t sk_gargantua_dmg_stomp1;
//cvar_t sk_gargantua_dmg_stomp2;
//cvar_t sk_gargantua_dmg_stomp3;
//cvar_t sk_hassassin_health1;
//cvar_t sk_hassassin_health2;
//cvar_t sk_hassassin_health3;
//cvar_t sk_headcrab_health1;
//cvar_t sk_headcrab_health2;
//cvar_t sk_headcrab_health3;
//cvar_t sk_headcrab_dmg_bite1;
//cvar_t sk_headcrab_dmg_bite2;
//cvar_t sk_headcrab_dmg_bite3;
//cvar_t sk_hgrunt_health1;
//cvar_t sk_hgrunt_health2;
//cvar_t sk_hgrunt_health3;
//cvar_t sk_hgrunt_kick1;
//cvar_t sk_hgrunt_kick2;
//cvar_t sk_hgrunt_kick3;
//cvar_t sk_hgrunt_pellets1;
//cvar_t sk_hgrunt_pellets2;
//cvar_t sk_hgrunt_pellets3;
//cvar_t sk_hgrunt_gspeed1;
//cvar_t sk_hgrunt_gspeed2;
//cvar_t sk_hgrunt_gspeed3;
//cvar_t sk_houndeye_health1;
//cvar_t sk_houndeye_health2;
//cvar_t sk_houndeye_health3;
//cvar_t sk_houndeye_dmg_blast1;
//cvar_t sk_houndeye_dmg_blast2;
//cvar_t sk_houndeye_dmg_blast3;
//cvar_t sk_islave_health1;
//cvar_t sk_islave_health2;
//cvar_t sk_islave_health3;
//cvar_t sk_islave_dmg_claw1;
//cvar_t sk_islave_dmg_claw2;
//cvar_t sk_islave_dmg_claw3;
//cvar_t sk_islave_dmg_clawrake1;
//cvar_t sk_islave_dmg_clawrake2;
//cvar_t sk_islave_dmg_clawrake3;
//cvar_t sk_islave_dmg_zap1;
//cvar_t sk_islave_dmg_zap2;
//cvar_t sk_islave_dmg_zap3;
//cvar_t sk_ichthyosaur_health1;
//cvar_t sk_ichthyosaur_health2;
//cvar_t sk_ichthyosaur_health3;
//cvar_t sk_ichthyosaur_shake1;
//cvar_t sk_ichthyosaur_shake2;
//cvar_t sk_ichthyosaur_shake3;
//cvar_t sk_leech_health1;
//cvar_t sk_leech_health2;
//cvar_t sk_leech_health3;
//cvar_t sk_leech_dmg_bite1;
//cvar_t sk_leech_dmg_bite2;
//cvar_t sk_leech_dmg_bite3;
//cvar_t sk_controller_health1;
//cvar_t sk_controller_health2;
//cvar_t sk_controller_health3;
//cvar_t sk_controller_dmgzap1;
//cvar_t sk_controller_dmgzap2;
//cvar_t sk_controller_dmgzap3;
//cvar_t sk_controller_speedball1;
//cvar_t sk_controller_speedball2;
//cvar_t sk_controller_speedball3;
//cvar_t sk_controller_dmgball1;
//cvar_t sk_controller_dmgball2;
//cvar_t sk_controller_dmgball3;
//cvar_t sk_nihilanth_health1;
//cvar_t sk_nihilanth_health2;
//cvar_t sk_nihilanth_health3;
//cvar_t sk_nihilanth_zap1;
//cvar_t sk_nihilanth_zap2;
//cvar_t sk_nihilanth_zap3;
//cvar_t sk_scientist_health1;
//cvar_t sk_scientist_health2;
//cvar_t sk_scientist_health3;
//cvar_t sk_snark_health1;
//cvar_t sk_snark_health2;
//cvar_t sk_snark_health3;
//cvar_t sk_snark_dmg_bite1;
//cvar_t sk_snark_dmg_bite2;
//cvar_t sk_snark_dmg_bite3;
//cvar_t sk_snark_dmg_pop1;
//cvar_t sk_snark_dmg_pop2;
//cvar_t sk_snark_dmg_pop3;
//cvar_t sk_zombie_health1;
//cvar_t sk_zombie_health2;
//cvar_t sk_zombie_health3;
//cvar_t sk_zombie_dmg_one_slash1;
//cvar_t sk_zombie_dmg_one_slash2;
//cvar_t sk_zombie_dmg_one_slash3;
//cvar_t sk_zombie_dmg_both_slash1;
//cvar_t sk_zombie_dmg_both_slash2;
//cvar_t sk_zombie_dmg_both_slash3;
//cvar_t sk_turret_health1;
//cvar_t sk_turret_health2;
//cvar_t sk_turret_health3;
//cvar_t sk_miniturret_health1;
//cvar_t sk_miniturret_health2;
//cvar_t sk_miniturret_health3;
//cvar_t sk_sentry_health1;
//cvar_t sk_sentry_health2;
//cvar_t sk_sentry_health3;
//cvar_t sk_plr_crowbar1;
//cvar_t sk_plr_crowbar2;
//cvar_t sk_plr_crowbar3;

cvar_t sk_plr_9mm_bullet1;
cvar_t sk_plr_9mm_bullet2;
cvar_t sk_plr_9mm_bullet3;
cvar_t sk_plr_357_bullet1;
cvar_t sk_plr_357_bullet2;
cvar_t sk_plr_357_bullet3;
cvar_t sk_plr_9mmAR_bullet1;
cvar_t sk_plr_9mmAR_bullet2;
cvar_t sk_plr_9mmAR_bullet3;
cvar_t sk_plr_9mmAR_grenade1;
cvar_t sk_plr_9mmAR_grenade2;
cvar_t sk_plr_9mmAR_grenade3;
cvar_t sk_plr_buckshot1;
cvar_t sk_plr_buckshot2;
cvar_t sk_plr_buckshot3;

// NOXREF
//cvar_t sk_plr_xbow_bolt_client1;
//cvar_t sk_plr_xbow_bolt_client2;
//cvar_t sk_plr_xbow_bolt_client3;
//cvar_t sk_plr_xbow_bolt_monster1;
//cvar_t sk_plr_xbow_bolt_monster2;
//cvar_t sk_plr_xbow_bolt_monster3;

cvar_t sk_plr_rpg1;
cvar_t sk_plr_rpg2;
cvar_t sk_plr_rpg3;

// NOXREF
//cvar_t sk_plr_gauss1;
//cvar_t sk_plr_gauss2;
//cvar_t sk_plr_gauss3;
//cvar_t sk_plr_egon_narrow1;
//cvar_t sk_plr_egon_narrow2;
//cvar_t sk_plr_egon_narrow3;
//cvar_t sk_plr_egon_wide1;
//cvar_t sk_plr_egon_wide2;
//cvar_t sk_plr_egon_wide3;
//cvar_t sk_plr_hand_grenade1;
//cvar_t sk_plr_hand_grenade2;
//cvar_t sk_plr_hand_grenade3;
//cvar_t sk_plr_satchel1;
//cvar_t sk_plr_satchel2;
//cvar_t sk_plr_satchel3;
//cvar_t sk_plr_tripmine1;
//cvar_t sk_plr_tripmine2;
//cvar_t sk_plr_tripmine3;

cvar_t sk_12mm_bullet1;
cvar_t sk_12mm_bullet2;
cvar_t sk_12mm_bullet3;
cvar_t sk_9mmAR_bullet1;
cvar_t sk_9mmAR_bullet2;
cvar_t sk_9mmAR_bullet3;
cvar_t sk_9mm_bullet1;
cvar_t sk_9mm_bullet2;
cvar_t sk_9mm_bullet3;

// NOXREF
//cvar_t sk_hornet_dmg1;
//cvar_t sk_hornet_dmg2;
//cvar_t sk_hornet_dmg3;

cvar_t sk_suitcharger1;
cvar_t sk_suitcharger2;
cvar_t sk_suitcharger3;
cvar_t sk_battery1;
cvar_t sk_battery2;
cvar_t sk_battery3;
cvar_t sk_healthcharger1;
cvar_t sk_healthcharger2;
cvar_t sk_healthcharger3;
cvar_t sk_healthkit1;
cvar_t sk_healthkit2;
cvar_t sk_healthkit3;
cvar_t sk_scientist_heal1;
cvar_t sk_scientist_heal2;
cvar_t sk_scientist_heal3;

// NOXREF
//cvar_t sk_monster_head1;
//cvar_t sk_monster_head2;
//cvar_t sk_monster_head3;
//cvar_t sk_monster_chest1;
//cvar_t sk_monster_chest2;
//cvar_t sk_monster_chest3;
//cvar_t sk_monster_stomach1;
//cvar_t sk_monster_stomach2;
//cvar_t sk_monster_stomach3;
//cvar_t sk_monster_arm1;
//cvar_t sk_monster_arm2;
//cvar_t sk_monster_arm3;
//cvar_t sk_monster_leg1;
//cvar_t sk_monster_leg2;
//cvar_t sk_monster_leg3;
//cvar_t sk_player_head1;
//cvar_t sk_player_head2;
//cvar_t sk_player_head3;
//cvar_t sk_player_chest1;
//cvar_t sk_player_chest2;
//cvar_t sk_player_chest3;
//cvar_t sk_player_stomach1;
//cvar_t sk_player_stomach2;
//cvar_t sk_player_stomach3;
//cvar_t sk_player_arm1;
//cvar_t sk_player_arm2;
//cvar_t sk_player_arm3;
//cvar_t sk_player_leg1;
//cvar_t sk_player_leg2;
//cvar_t sk_player_leg3;

#endif // HOOK_GAMEDLL

#ifdef REGAMEDLL_ADD

cvar_t game_version = { "game_version", APP_VERSION_STRD, FCVAR_SERVER, 0.0f, NULL };
cvar_t maxmoney = { "mp_maxmoney", "16000", FCVAR_SERVER, 0.0f, NULL };
cvar_t round_infinite = { "mp_round_infinite", "0", FCVAR_SERVER, 0.0f, NULL };

#endif // REGAMEDLL_ADD

void GameDLL_Version_f(void)
{
	if (Q_stricmp(CMD_ARGV(1), "version") != 0)
		return;

	// print version
	CONSOLE_ECHO("ReGameDLL build: " __TIME__ " " __DATE__ " (" APP_VERSION_STRD ")\n");
	CONSOLE_ECHO("ReGameDLL API version %i.%i\n", REGAMEDLL_API_VERSION_MAJOR, REGAMEDLL_API_VERSION_MINOR);
}

/* <9c900> ../cstrike/dlls/game.cpp:500 */
void EXT_FUNC GameDLLInit(void)
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

#ifdef REGAMEDLL_ADD

	ADD_SERVER_COMMAND("game", GameDLL_Version_f);

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
