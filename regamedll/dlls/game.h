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

#ifndef GAME_H
#define GAME_H
#ifdef _WIN32
#pragma once
#endif

#define LOG_ENEMYATTACK		1
#define LOG_TEAMMATEATTACK	2

#ifdef HOOK_GAMEDLL

#define g_psv_gravity (*pg_psv_gravity)
#define g_psv_aim (*pg_psv_aim)
#define g_footsteps (*pg_footsteps)
#define g_psv_accelerate (*pg_psv_accelerate)
#define g_psv_friction (*pg_psv_friction)
#define g_psv_stopspeed (*pg_psv_stopspeed)
#define displaysoundlist (*pdisplaysoundlist)
#define timelimit (*ptimelimit)
#define flashlight (*pflashlight)
#define decalfrequency (*pdecalfrequency)
#define fadetoblack (*pfadetoblack)
#define fragsleft (*pfragsleft)
#define timeleft (*ptimeleft)
#define friendlyfire (*pfriendlyfire)
#define allowmonsters (*pallowmonsters)
#define roundtime (*proundtime)
#define buytime (*pbuytime)
#define freezetime (*pfreezetime)
#define c4timer (*pc4timer)
#define ghostfrequency (*pghostfrequency)
#define autokick (*pautokick)
#define autokick_timeout (*pautokick_timeout)
#define restartround (*prestartround)
#define sv_restart (*psv_restart)
#define limitteams (*plimitteams)
#define autoteambalance (*pautoteambalance)
#define tkpunish (*ptkpunish)
#define hostagepenalty (*phostagepenalty)
#define mirrordamage (*pmirrordamage)
#define logmessages (*plogmessages)
#define forcecamera (*pforcecamera)
#define forcechasecam (*pforcechasecam)
#define mapvoteratio (*pmapvoteratio)
#define logdetail (*plogdetail)
#define startmoney (*pstartmoney)
#define maxrounds (*pmaxrounds)
#define winlimit (*pwinlimit)
#define windifference (*pwindifference)
#define playerid (*pplayerid)
#define allow_spectators (*pallow_spectators)
#define mp_chattime (*pmp_chattime)
#define kick_percent (*pkick_percent)
#define humans_join_team (*phumans_join_team)
#define sk_plr_9mm_bullet1 (*psk_plr_9mm_bullet1)
#define sk_plr_9mm_bullet2 (*psk_plr_9mm_bullet2)
#define sk_plr_9mm_bullet3 (*psk_plr_9mm_bullet3)
#define sk_plr_357_bullet1 (*psk_plr_357_bullet1)
#define sk_plr_357_bullet2 (*psk_plr_357_bullet2)
#define sk_plr_357_bullet3 (*psk_plr_357_bullet3)
#define sk_plr_9mmAR_bullet1 (*psk_plr_9mmAR_bullet1)
#define sk_plr_9mmAR_bullet2 (*psk_plr_9mmAR_bullet2)
#define sk_plr_9mmAR_bullet3 (*psk_plr_9mmAR_bullet3)
#define sk_plr_9mmAR_grenade1 (*psk_plr_9mmAR_grenade1)
#define sk_plr_9mmAR_grenade2 (*psk_plr_9mmAR_grenade2)
#define sk_plr_9mmAR_grenade3 (*psk_plr_9mmAR_grenade3)
#define sk_plr_buckshot1 (*psk_plr_buckshot1)
#define sk_plr_buckshot2 (*psk_plr_buckshot2)
#define sk_plr_buckshot3 (*psk_plr_buckshot3)
#define sk_plr_rpg1 (*psk_plr_rpg1)
#define sk_plr_rpg2 (*psk_plr_rpg2)
#define sk_plr_rpg3 (*psk_plr_rpg3)
#define sk_12mm_bullet1 (*psk_12mm_bullet1)
#define sk_12mm_bullet2 (*psk_12mm_bullet2)
#define sk_12mm_bullet3 (*psk_12mm_bullet3)
#define sk_9mmAR_bullet1 (*psk_9mmAR_bullet1)
#define sk_9mmAR_bullet2 (*psk_9mmAR_bullet2)
#define sk_9mmAR_bullet3 (*psk_9mmAR_bullet3)
#define sk_9mm_bullet1 (*psk_9mm_bullet1)
#define sk_9mm_bullet2 (*psk_9mm_bullet2)
#define sk_9mm_bullet3 (*psk_9mm_bullet3)
#define sk_suitcharger1 (*psk_suitcharger1)
#define sk_suitcharger2 (*psk_suitcharger2)
#define sk_suitcharger3 (*psk_suitcharger3)
#define sk_battery1 (*psk_battery1)
#define sk_battery2 (*psk_battery2)
#define sk_battery3 (*psk_battery3)
#define sk_healthcharger1 (*psk_healthcharger1)
#define sk_healthcharger2 (*psk_healthcharger2)
#define sk_healthcharger3 (*psk_healthcharger3)
#define sk_healthkit1 (*psk_healthkit1)
#define sk_healthkit2 (*psk_healthkit2)
#define sk_healthkit3 (*psk_healthkit3)
#define sk_scientist_heal1 (*psk_scientist_heal1)
#define sk_scientist_heal2 (*psk_scientist_heal2)
#define sk_scientist_heal3 (*psk_scientist_heal3)

#endif // HOOK_GAMEDLL

extern cvar_t *g_psv_gravity;
extern cvar_t *g_psv_aim;
extern cvar_t *g_footsteps;
extern cvar_t *g_psv_accelerate;
extern cvar_t *g_psv_friction;
extern cvar_t *g_psv_stopspeed;

extern cvar_t displaysoundlist;
extern cvar_t timelimit;
extern cvar_t flashlight;
extern cvar_t decalfrequency;
extern cvar_t fadetoblack;
extern cvar_t fragsleft;
extern cvar_t timeleft;
extern cvar_t friendlyfire;
extern cvar_t allowmonsters;
extern cvar_t roundtime;
extern cvar_t buytime;
extern cvar_t freezetime;
extern cvar_t c4timer;
extern cvar_t ghostfrequency;
extern cvar_t autokick;
extern cvar_t autokick_timeout;
extern cvar_t restartround;
extern cvar_t sv_restart;
extern cvar_t limitteams;
extern cvar_t autoteambalance;
extern cvar_t tkpunish;
extern cvar_t hostagepenalty;
extern cvar_t mirrordamage;
extern cvar_t logmessages;
extern cvar_t forcecamera;
extern cvar_t forcechasecam;
extern cvar_t mapvoteratio;
extern cvar_t logdetail;
extern cvar_t startmoney;
extern cvar_t maxrounds;
extern cvar_t winlimit;
extern cvar_t windifference;
extern cvar_t playerid;
extern cvar_t allow_spectators;
extern cvar_t mp_chattime;
extern cvar_t kick_percent;
extern cvar_t humans_join_team;
extern cvar_t sk_plr_9mm_bullet1;
extern cvar_t sk_plr_9mm_bullet2;
extern cvar_t sk_plr_9mm_bullet3;
extern cvar_t sk_plr_357_bullet1;
extern cvar_t sk_plr_357_bullet2;
extern cvar_t sk_plr_357_bullet3;
extern cvar_t sk_plr_9mmAR_bullet1;
extern cvar_t sk_plr_9mmAR_bullet2;
extern cvar_t sk_plr_9mmAR_bullet3;
extern cvar_t sk_plr_9mmAR_grenade1;
extern cvar_t sk_plr_9mmAR_grenade2;
extern cvar_t sk_plr_9mmAR_grenade3;
extern cvar_t sk_plr_buckshot1;
extern cvar_t sk_plr_buckshot2;
extern cvar_t sk_plr_buckshot3;
extern cvar_t sk_plr_rpg1;
extern cvar_t sk_plr_rpg2;
extern cvar_t sk_plr_rpg3;
extern cvar_t sk_12mm_bullet1;
extern cvar_t sk_12mm_bullet2;
extern cvar_t sk_12mm_bullet3;
extern cvar_t sk_9mmAR_bullet1;
extern cvar_t sk_9mmAR_bullet2;
extern cvar_t sk_9mmAR_bullet3;
extern cvar_t sk_9mm_bullet1;
extern cvar_t sk_9mm_bullet2;
extern cvar_t sk_9mm_bullet3;
extern cvar_t sk_suitcharger1;
extern cvar_t sk_suitcharger2;
extern cvar_t sk_suitcharger3;
extern cvar_t sk_battery1;
extern cvar_t sk_battery2;
extern cvar_t sk_battery3;
extern cvar_t sk_healthcharger1;
extern cvar_t sk_healthcharger2;
extern cvar_t sk_healthcharger3;
extern cvar_t sk_healthkit1;
extern cvar_t sk_healthkit2;
extern cvar_t sk_healthkit3;
extern cvar_t sk_scientist_heal1;
extern cvar_t sk_scientist_heal2;
extern cvar_t sk_scientist_heal3;

NOBODY void GameDLLInit(void);

#endif // GAME_H
