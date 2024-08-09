#include "precompiled.h"

cvar_t *g_pskill          = nullptr;
cvar_t *g_psv_gravity     = nullptr;
cvar_t *g_psv_aim         = nullptr;
cvar_t *g_footsteps       = nullptr;
cvar_t *g_psv_accelerate  = nullptr;
cvar_t *g_psv_friction    = nullptr;
cvar_t *g_psv_stopspeed   = nullptr;
cvar_t *g_psv_stepsize    = nullptr;
cvar_t *g_psv_clienttrace = nullptr;
cvar_t *g_psv_maxvelocity = nullptr;

cvar_t displaysoundlist      = { "displaysoundlist", "0", 0, 0.0f, nullptr };
cvar_t timelimit             = { "mp_timelimit", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t flashlight            = { "mp_flashlight", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t decalfrequency        = { "decalfrequency", "30", FCVAR_SERVER, 0.0f, nullptr };
cvar_t fadetoblack           = { "mp_fadetoblack", "0", FCVAR_SERVER, 0.0f, nullptr };

cvar_t fragsleft             = { "mp_fragsleft", "0", FCVAR_SERVER | FCVAR_UNLOGGED, 0.0f, nullptr };		// Don't spam console/log files/users with this changing
cvar_t timeleft              = { "mp_timeleft", "0", FCVAR_SERVER | FCVAR_UNLOGGED, 0.0f, nullptr };

cvar_t friendlyfire          = { "mp_friendlyfire", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t infiniteAmmo          = { "mp_infinite_ammo", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t infiniteGrenades      = { "mp_infinite_grenades", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t allowmonsters         = { "mp_allowmonsters", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t roundtime             = { "mp_roundtime", "5", FCVAR_SERVER, 0.0f, nullptr };
cvar_t buytime               = { "mp_buytime", "1.5", FCVAR_SERVER, 0.0f, nullptr };
cvar_t freezetime            = { "mp_freezetime", "6", FCVAR_SERVER, 0.0f, nullptr };
cvar_t c4timer               = { "mp_c4timer", "45", FCVAR_SERVER, 0.0f, nullptr };
cvar_t ghostfrequency        = { "mp_ghostfrequency", "0.1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t autokick              = { "mp_autokick", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t autokick_timeout      = { "mp_autokick_timeout", "-1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t restartround          = { "sv_restartround", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t sv_restart            = { "sv_restart", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t limitteams            = { "mp_limitteams", "2", FCVAR_SERVER, 0.0f, nullptr };
cvar_t autoteambalance       = { "mp_autoteambalance", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t tkpunish              = { "mp_tkpunish", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t hostagepenalty        = { "mp_hostagepenalty", "13", FCVAR_SERVER, 0.0f, nullptr };
cvar_t mirrordamage          = { "mp_mirrordamage", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t logmessages           = { "mp_logmessages", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t forcecamera           = { "mp_forcecamera", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t forcechasecam         = { "mp_forcechasecam", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t mapvoteratio          = { "mp_mapvoteratio", "0.66", FCVAR_SERVER, 0.0f, nullptr };
cvar_t logdetail             = { "mp_logdetail", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t startmoney            = { "mp_startmoney", "800", FCVAR_SERVER, 0.0f, nullptr };
cvar_t maxrounds             = { "mp_maxrounds", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t winlimit              = { "mp_winlimit", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t windifference         = { "mp_windifference", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t playerid              = { "mp_playerid", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t allow_spectators      = { "allow_spectators", "1.0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t mp_chattime           = { "mp_chattime", "10", FCVAR_SERVER, 0.0f, nullptr };
cvar_t kick_percent          = { "mp_kickpercent", "0.66", FCVAR_SERVER, 0.0f, nullptr };
cvar_t humans_join_team      = { "humans_join_team", "any", FCVAR_SERVER, 0.0f, nullptr };
cvar_t sk_plr_9mm_bullet1    = { "sk_plr_9mm_bullet1", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mm_bullet2    = { "sk_plr_9mm_bullet2", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mm_bullet3    = { "sk_plr_9mm_bullet3", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_357_bullet1    = { "sk_plr_357_bullet1", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_357_bullet2    = { "sk_plr_357_bullet2", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_357_bullet3    = { "sk_plr_357_bullet3", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mmAR_bullet1  = { "sk_plr_9mmAR_bullet1", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mmAR_bullet2  = { "sk_plr_9mmAR_bullet2", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mmAR_bullet3  = { "sk_plr_9mmAR_bullet3", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mmAR_grenade1 = { "sk_plr_9mmAR_grenade1", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mmAR_grenade2 = { "sk_plr_9mmAR_grenade2", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_9mmAR_grenade3 = { "sk_plr_9mmAR_grenade3", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_buckshot1      = { "sk_plr_buckshot1", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_buckshot2      = { "sk_plr_buckshot2", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_buckshot3      = { "sk_plr_buckshot3", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_rpg1           = { "sk_plr_rpg1", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_rpg2           = { "sk_plr_rpg2", "0", 0, 0.0f, nullptr };
cvar_t sk_plr_rpg3           = { "sk_plr_rpg3", "0", 0, 0.0f, nullptr };
cvar_t sk_12mm_bullet1       = { "sk_12mm_bullet1", "0", 0, 0.0f, nullptr };
cvar_t sk_12mm_bullet2       = { "sk_12mm_bullet2", "0", 0, 0.0f, nullptr };
cvar_t sk_12mm_bullet3       = { "sk_12mm_bullet3", "0", 0, 0.0f, nullptr };
cvar_t sk_9mmAR_bullet1      = { "sk_9mmAR_bullet1", "0", 0, 0.0f, nullptr };
cvar_t sk_9mmAR_bullet2      = { "sk_9mmAR_bullet2", "0", 0, 0.0f, nullptr };
cvar_t sk_9mmAR_bullet3      = { "sk_9mmAR_bullet3", "0", 0, 0.0f, nullptr };
cvar_t sk_9mm_bullet1        = { "sk_9mm_bullet1", "0", 0, 0.0f, nullptr };
cvar_t sk_9mm_bullet2        = { "sk_9mm_bullet2", "0", 0, 0.0f, nullptr };
cvar_t sk_9mm_bullet3        = { "sk_9mm_bullet3", "0", 0, 0.0f, nullptr };
cvar_t sk_suitcharger1       = { "sk_suitcharger1", "0", 0, 0.0f, nullptr };
cvar_t sk_suitcharger2       = { "sk_suitcharger2", "0", 0, 0.0f, nullptr };
cvar_t sk_suitcharger3       = { "sk_suitcharger3", "0", 0, 0.0f, nullptr };
cvar_t sk_battery1           = { "sk_battery1", "0", 0, 0.0f, nullptr };
cvar_t sk_battery2           = { "sk_battery2", "0", 0, 0.0f, nullptr };
cvar_t sk_battery3           = { "sk_battery3", "0", 0, 0.0f, nullptr };
cvar_t sk_healthcharger1     = { "sk_healthcharger1", "0", 0, 0.0f, nullptr };
cvar_t sk_healthcharger2     = { "sk_healthcharger2", "0", 0, 0.0f, nullptr };
cvar_t sk_healthcharger3     = { "sk_healthcharger3", "0", 0, 0.0f, nullptr };
cvar_t sk_healthkit1         = { "sk_healthkit1", "0", 0, 0.0f, nullptr };
cvar_t sk_healthkit2         = { "sk_healthkit2", "0", 0, 0.0f, nullptr };
cvar_t sk_healthkit3         = { "sk_healthkit3", "0", 0, 0.0f, nullptr };
cvar_t sk_scientist_heal1    = { "sk_scientist_heal1", "0", 0, 0.0f, nullptr };
cvar_t sk_scientist_heal2    = { "sk_scientist_heal2", "0", 0, 0.0f, nullptr };
cvar_t sk_scientist_heal3    = { "sk_scientist_heal3", "0", 0, 0.0f, nullptr };

#ifdef BUILD_LATEST

cvar_t scoreboard_showmoney  = { "mp_scoreboard_showmoney", "3", FCVAR_SERVER, 0.0f, nullptr };
cvar_t scoreboard_showhealth = { "mp_scoreboard_showhealth", "3", FCVAR_SERVER, 0.0f, nullptr };
cvar_t scoreboard_showdefkit = { "mp_scoreboard_showdefkit", "1", FCVAR_SERVER, 0.0f, nullptr };

#endif

#ifdef REGAMEDLL_ADD

cvar_t game_version          = { "game_version", APP_VERSION, FCVAR_SERVER, 0.0f, nullptr };
cvar_t maxmoney              = { "mp_maxmoney", "16000", FCVAR_SERVER, 0.0f, nullptr };
cvar_t round_infinite        = { "mp_round_infinite", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t hegrenade_penetration = { "mp_hegrenade_penetration", "0", 0, 0.0f, nullptr };
cvar_t nadedrops             = { "mp_nadedrops", "0", 0, 0.0f, nullptr };
cvar_t weapondrop            = { "mp_weapondrop", "1", 0, 1.0f, nullptr };
cvar_t ammodrop              = { "mp_ammodrop", "1", 0, 1.0f, nullptr };
cvar_t roundrespawn_time     = { "mp_roundrespawn_time", "20", 0, 20.0f, nullptr };
cvar_t auto_reload_weapons   = { "mp_auto_reload_weapons", "0", 0, 0.0f, nullptr };
cvar_t refill_bpammo_weapons = { "mp_refill_bpammo_weapons", "0", 0, 0.0f, nullptr }; // Useful for mods like DeathMatch, GunGame, ZombieMod etc
cvar_t freeforall            = { "mp_freeforall", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t auto_join_team        = { "mp_auto_join_team", "0", 0, 0.0f, nullptr };
cvar_t max_teamkills         = { "mp_max_teamkills", "3", 0, 3.0f, nullptr };
cvar_t fraglimit             = { "mp_fraglimit", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t round_restart_delay   = { "mp_round_restart_delay", "5", FCVAR_SERVER, 0.0f, nullptr };
cvar_t showtriggers          = { "showtriggers", "0", 0, 0.0f, nullptr }; // debug cvar shows triggers
                                                                          // TODO: Maybe it's better to register in the engine?
cvar_t hostagehurtable              = { "mp_hostage_hurtable", "1", FCVAR_SERVER, 1.0f, nullptr };
cvar_t roundover                    = { "mp_roundover", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t forcerespawn                 = { "mp_forcerespawn", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t show_radioicon               = { "mp_show_radioicon", "1", 0, 1.0f, nullptr };
cvar_t show_scenarioicon            = { "mp_show_scenarioicon", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t old_bomb_defused_sound       = { "mp_old_bomb_defused_sound", "1", 0, 1.0f, nullptr };
cvar_t item_staytime                = { "mp_item_staytime", "300", FCVAR_SERVER, 300.0f, nullptr };
cvar_t legacy_bombtarget_touch      = { "mp_legacy_bombtarget_touch", "1", 0, 1.0f, nullptr };
cvar_t respawn_immunitytime         = { "mp_respawn_immunitytime", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t respawn_immunity_effects     = { "mp_respawn_immunity_effects", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t respawn_immunity_force_unset = { "mp_respawn_immunity_force_unset", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t kill_filled_spawn            = { "mp_kill_filled_spawn", "1", 0, 0.0f, nullptr };
cvar_t afk_bomb_drop_time           = { "mp_afk_bomb_drop_time", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t buy_anywhere                 = { "mp_buy_anywhere", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t give_player_c4               = { "mp_give_player_c4", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t weapons_allow_map_placed     = { "mp_weapons_allow_map_placed", "1", FCVAR_SERVER, 0.0f, nullptr };

cvar_t allow_point_servercommand    = { "mp_allow_point_servercommand", "0", 0, 0.0f, nullptr };
cvar_t hullbounds_sets              = { "mp_hullbounds_sets", "1", 0, 0.0f, nullptr };
cvar_t unduck_method                = { "mp_unduck_method", "0", 0, 0.0f, nullptr };

cvar_t ff_damage_reduction_bullets      = { "ff_damage_reduction_bullets",      "0.35", FCVAR_SERVER, 0.0f, nullptr };
cvar_t ff_damage_reduction_grenade      = { "ff_damage_reduction_grenade",      "0.25", FCVAR_SERVER, 0.0f, nullptr };
cvar_t ff_damage_reduction_grenade_self = { "ff_damage_reduction_grenade_self", "1",    FCVAR_SERVER, 0.0f, nullptr };
cvar_t ff_damage_reduction_other        = { "ff_damage_reduction_other",        "0.25", FCVAR_SERVER, 0.0f, nullptr };

cvar_t radio_timeout           = { "mp_radio_timeout", "1.5", FCVAR_SERVER, 1.5f, nullptr };
cvar_t radio_maxinround        = { "mp_radio_maxinround", "60", FCVAR_SERVER, 60.0f, nullptr };
cvar_t falldamage              = { "mp_falldamage", "1", FCVAR_SERVER, 1.0f, nullptr };

cvar_t ct_default_grenades               = { "mp_ct_default_grenades", "", 0, 0.0f, nullptr };
cvar_t ct_give_player_knife              = { "mp_ct_give_player_knife", "1", 0, 1.0f, nullptr };
cvar_t ct_default_weapons_secondary      = { "mp_ct_default_weapons_secondary", "usp", 0, 0.0f, nullptr };
cvar_t ct_default_weapons_primary        = { "mp_ct_default_weapons_primary", "", 0, 0.0f, nullptr };
cvar_t t_default_grenades                = { "mp_t_default_grenades", "", 0, 0.0f, nullptr };
cvar_t t_give_player_knife               = { "mp_t_give_player_knife", "1", 0, 1.0f, nullptr };
cvar_t t_default_weapons_secondary       = { "mp_t_default_weapons_secondary", "glock18", 0, 0.0f, nullptr };
cvar_t t_default_weapons_primary         = { "mp_t_default_weapons_primary", "", 0, 0.0f, nullptr };
cvar_t free_armor                        = { "mp_free_armor", "0", 0, 0.0f, nullptr };
cvar_t teamflash                         = { "mp_team_flash", "1", 0, 1.0f, nullptr };
cvar_t allchat                           = { "sv_allchat", "0", 0, 0.0f, nullptr };
cvar_t sv_autobunnyhopping               = { "sv_autobunnyhopping", "0", 0, 0.0f, nullptr };
cvar_t sv_enablebunnyhopping             = { "sv_enablebunnyhopping", "0", 0, 0.0f, nullptr };
cvar_t plant_c4_anywhere                 = { "mp_plant_c4_anywhere", "0", 0, 0.0f, nullptr };
cvar_t give_c4_frags                     = { "mp_give_c4_frags", "3", 0, 3.0f, nullptr };
cvar_t deathmsg_flags                    = { "mp_deathmsg_flags", "abc", 0, 0.0f, nullptr };
cvar_t assist_damage_threshold           = { "mp_assist_damage_threshold", "40", 0, 40.0f, nullptr };
cvar_t freezetime_duck                   = { "mp_freezetime_duck", "1", 0, 1.0f, nullptr };
cvar_t freezetime_jump                   = { "mp_freezetime_jump", "1", 0, 1.0f, nullptr };

cvar_t hostages_rescued_ratio = { "mp_hostages_rescued_ratio", "1.0", 0, 1.0f, nullptr };

cvar_t legacy_vehicle_block               = { "mp_legacy_vehicle_block", "1", 0, 0.0f, nullptr };

cvar_t dying_time              = { "mp_dying_time", "3.0", 0, 3.0f, nullptr };
cvar_t defuser_allocation      = { "mp_defuser_allocation", "0", 0, 0.0f, nullptr };
cvar_t location_area_info      = { "mp_location_area_info", "0", 0, 0.0f, nullptr };
cvar_t chat_loc_fallback       = { "mp_chat_loc_fallback", "1", 1, 0.0f, nullptr };

cvar_t item_respawn_time       = { "mp_item_respawn_time", "30", FCVAR_SERVER, 30.0f, nullptr };
cvar_t weapon_respawn_time     = { "mp_weapon_respawn_time", "20", FCVAR_SERVER, 20.0f, nullptr };
cvar_t ammo_respawn_time       = { "mp_ammo_respawn_time", "20", FCVAR_SERVER, 20.0f, nullptr };

cvar_t vote_flags              = { "mp_vote_flags", "km", 0, 0.0f, nullptr };
cvar_t votemap_min_time        = { "mp_votemap_min_time", "180", 0, 180.0f, nullptr };

void GameDLL_Version_f()
{
	if (Q_stricmp(CMD_ARGV(1), "version") != 0)
		return;

	// print version
	CONSOLE_ECHO("ReGameDLL version: " APP_VERSION "\n");
	CONSOLE_ECHO("Build date: " APP_COMMIT_TIME " " APP_COMMIT_DATE "\n");
	CONSOLE_ECHO("Build from: " APP_COMMIT_URL APP_COMMIT_SHA "\n");
}

void GameDLL_EndRound_f()
{
	if (CMD_ARGC() == 2)
	{
		const char *pCmd = CMD_ARGV(1);

		if (pCmd[0] == '1' || !Q_stricmp(pCmd, "T"))
		{
			CSGameRules()->OnRoundEnd_Intercept(WINSTATUS_TERRORISTS, ROUND_TERRORISTS_WIN, CSGameRules()->GetRoundRestartDelay());
			return;
		}
		else if (pCmd[0] == '2' || !Q_stricmp(pCmd, "CT"))
		{
			CSGameRules()->OnRoundEnd_Intercept(WINSTATUS_CTS, ROUND_CTS_WIN, CSGameRules()->GetRoundRestartDelay());
			return;
		}
	}

	CSGameRules()->OnRoundEnd_Intercept(WINSTATUS_DRAW, ROUND_END_DRAW, CSGameRules()->GetRoundRestartDelay());
}

void GameDLL_SwapTeams_f()
{
	CSGameRules()->SwapAllPlayers();

	float value = 1.0f;
	if (CMD_ARGC() >= 2)
	{
		value = Q_atof(CMD_ARGV(1));
	}

	if (value > 0.0f)
	{
		CVAR_SET_FLOAT("sv_restartround", value);
	}
}

#endif // REGAMEDLL_ADD

SpewRetval_t GameDLL_SpewHandler(SpewType_t spewType, int level, const char *pMsg);

void EXT_FUNC GameDLLInit()
{
	// By default, direct dbg reporting...
	SpewOutputFunc(GameDLL_SpewHandler);

	g_pskill          = CVAR_GET_POINTER("skill");
	g_psv_gravity     = CVAR_GET_POINTER("sv_gravity");
	g_psv_aim         = CVAR_GET_POINTER("sv_aim");
	g_footsteps       = CVAR_GET_POINTER("mp_footsteps");
	g_psv_accelerate  = CVAR_GET_POINTER("sv_accelerate");
	g_psv_friction    = CVAR_GET_POINTER("sv_friction");
	g_psv_stopspeed   = CVAR_GET_POINTER("sv_stopspeed");
	g_psv_stepsize    = CVAR_GET_POINTER("sv_stepsize");
	g_psv_clienttrace = CVAR_GET_POINTER("sv_clienttrace");
	g_psv_maxvelocity = CVAR_GET_POINTER("sv_maxvelocity");

	CVAR_REGISTER(&displaysoundlist);
	CVAR_REGISTER(&timelimit);
	CVAR_REGISTER(&friendlyfire);

#ifdef BUILD_LATEST
	CVAR_REGISTER(&infiniteAmmo);
	CVAR_REGISTER(&infiniteGrenades);
#endif

	CVAR_REGISTER(&flashlight);
	CVAR_REGISTER(&decalfrequency);

#ifndef REGAMEDLL_FIXES
	CVAR_REGISTER(&allowmonsters);
#endif

	CVAR_REGISTER(&roundtime);
	CVAR_REGISTER(&buytime);
	CVAR_REGISTER(&freezetime);
	CVAR_REGISTER(&c4timer);

#ifndef REGAMEDLL_FIXES
	CVAR_REGISTER(&ghostfrequency);
#endif

	CVAR_REGISTER(&autokick);
	CVAR_REGISTER(&autokick_timeout);
	CVAR_REGISTER(&restartround);
	CVAR_REGISTER(&sv_restart);
	CVAR_REGISTER(&limitteams);
	CVAR_REGISTER(&autoteambalance);
	CVAR_REGISTER(&tkpunish);
	CVAR_REGISTER(&hostagepenalty);

#ifndef REGAMEDLL_FIXES
	CVAR_REGISTER(&mirrordamage);
#endif

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

#ifdef BUILD_LATEST
	CVAR_REGISTER(&scoreboard_showhealth);
	CVAR_REGISTER(&scoreboard_showmoney);
	CVAR_REGISTER(&scoreboard_showdefkit);
#endif

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
	ADD_SERVER_COMMAND("swapteams", GameDLL_SwapTeams_f);

	CVAR_REGISTER(&game_version);
	CVAR_REGISTER(&maxmoney);
	CVAR_REGISTER(&round_infinite);
	CVAR_REGISTER(&hegrenade_penetration);
	CVAR_REGISTER(&nadedrops);
	CVAR_REGISTER(&weapondrop);
	CVAR_REGISTER(&ammodrop);
	CVAR_REGISTER(&roundrespawn_time);
	CVAR_REGISTER(&auto_reload_weapons);
	CVAR_REGISTER(&refill_bpammo_weapons);
	CVAR_REGISTER(&freeforall);
	CVAR_REGISTER(&auto_join_team);
	CVAR_REGISTER(&max_teamkills);
	CVAR_REGISTER(&fraglimit);
	CVAR_REGISTER(&round_restart_delay);

	CVAR_REGISTER(&showtriggers);
	CVAR_REGISTER(&hostagehurtable);
	CVAR_REGISTER(&roundover);
	CVAR_REGISTER(&forcerespawn);
	CVAR_REGISTER(&show_radioicon);

	if (!AreRunningCZero())
	{
		CVAR_REGISTER(&show_scenarioicon);
	}

	CVAR_REGISTER(&old_bomb_defused_sound);
	CVAR_REGISTER(&item_staytime);
	CVAR_REGISTER(&legacy_bombtarget_touch);
	CVAR_REGISTER(&respawn_immunitytime);
	CVAR_REGISTER(&respawn_immunity_effects);
	CVAR_REGISTER(&respawn_immunity_force_unset);
	CVAR_REGISTER(&kill_filled_spawn);
	CVAR_REGISTER(&afk_bomb_drop_time);
	CVAR_REGISTER(&buy_anywhere);
	CVAR_REGISTER(&give_player_c4);
	CVAR_REGISTER(&allow_point_servercommand);
	CVAR_REGISTER(&hullbounds_sets);
	CVAR_REGISTER(&unduck_method);
	CVAR_REGISTER(&weapons_allow_map_placed);

	CVAR_REGISTER(&ff_damage_reduction_bullets);
	CVAR_REGISTER(&ff_damage_reduction_grenade);
	CVAR_REGISTER(&ff_damage_reduction_grenade_self);
	CVAR_REGISTER(&ff_damage_reduction_other);

	CVAR_REGISTER(&radio_timeout);
	CVAR_REGISTER(&radio_maxinround);
	CVAR_REGISTER(&falldamage);

	CVAR_REGISTER(&ct_default_grenades);
	CVAR_REGISTER(&ct_give_player_knife);
	CVAR_REGISTER(&ct_default_weapons_secondary);
	CVAR_REGISTER(&ct_default_weapons_primary);
	CVAR_REGISTER(&t_default_grenades);
	CVAR_REGISTER(&t_give_player_knife);
	CVAR_REGISTER(&t_default_weapons_secondary);
	CVAR_REGISTER(&t_default_weapons_primary);
	CVAR_REGISTER(&free_armor);
	CVAR_REGISTER(&teamflash);
	CVAR_REGISTER(&allchat);
	CVAR_REGISTER(&sv_autobunnyhopping);
	CVAR_REGISTER(&sv_enablebunnyhopping);
	CVAR_REGISTER(&plant_c4_anywhere);
	CVAR_REGISTER(&give_c4_frags);

	CVAR_REGISTER(&hostages_rescued_ratio);

	CVAR_REGISTER(&legacy_vehicle_block);

	CVAR_REGISTER(&dying_time);
	CVAR_REGISTER(&deathmsg_flags);
	CVAR_REGISTER(&assist_damage_threshold);

	CVAR_REGISTER(&freezetime_duck);
	CVAR_REGISTER(&freezetime_jump);
	CVAR_REGISTER(&defuser_allocation);
	CVAR_REGISTER(&location_area_info);
	CVAR_REGISTER(&chat_loc_fallback);

	CVAR_REGISTER(&item_respawn_time);
	CVAR_REGISTER(&weapon_respawn_time);
	CVAR_REGISTER(&ammo_respawn_time);

	CVAR_REGISTER(&vote_flags);
	CVAR_REGISTER(&votemap_min_time);

	// print version
	CONSOLE_ECHO("ReGameDLL version: " APP_VERSION "\n");

#endif // REGAMEDLL_ADD

	Bot_RegisterCVars();
	Tutor_RegisterCVars();
	Hostage_RegisterCVars();

#ifdef REGAMEDLL_FIXES
	VoiceGameMgr_RegisterCVars();
#endif

#ifdef REGAMEDLL_ADD
	// execute initial pre-configurations
	SERVER_COMMAND("exec game_init.cfg\n");
	SERVER_EXECUTE();
#endif

}

SpewRetval_t GameDLL_SpewHandler(SpewType_t spewType, int level, const char *pMsg)
{
	bool bSpewPrint = (CVAR_GET_FLOAT("developer") >= level);
	switch (spewType)
	{
	case SPEW_LOG:
	case SPEW_MESSAGE:
		if (bSpewPrint) UTIL_ServerPrint("%s", pMsg);
		break;
	case SPEW_WARNING:
		if (bSpewPrint) UTIL_ServerPrint("Warning: %s", pMsg);
		break;
	case SPEW_ERROR:
		Sys_Error("%s", pMsg);
		return SPEW_ABORT; // fatal error, terminate it!
	case SPEW_ASSERT:
		UTIL_ServerPrint("Assert: %s", pMsg);
		return SPEW_DEBUGGER; // assert always tries to debugger break
	default:
		break;
	}

	return SPEW_CONTINUE; // spew handled, continue on
}
