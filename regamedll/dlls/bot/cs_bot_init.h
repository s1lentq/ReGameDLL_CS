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

#pragma once

extern cvar_t cv_bot_traceview;
extern cvar_t cv_bot_stop;
extern cvar_t cv_bot_show_nav;
extern cvar_t cv_bot_show_danger;
extern cvar_t cv_bot_nav_edit;
extern cvar_t cv_bot_nav_zdraw;
extern cvar_t cv_bot_walk;
extern cvar_t cv_bot_difficulty;
extern cvar_t cv_bot_debug;
extern cvar_t cv_bot_quicksave;
extern cvar_t cv_bot_quota;
extern cvar_t cv_bot_prefix;
extern cvar_t cv_bot_allow_rogues;
extern cvar_t cv_bot_allow_pistols;
extern cvar_t cv_bot_allow_shotguns;
extern cvar_t cv_bot_allow_sub_machine_guns;
extern cvar_t cv_bot_allow_rifles;
extern cvar_t cv_bot_allow_machine_guns;
extern cvar_t cv_bot_allow_grenades;
extern cvar_t cv_bot_allow_snipers;
extern cvar_t cv_bot_allow_shield;
extern cvar_t cv_bot_join_team;
extern cvar_t cv_bot_join_after_player;
extern cvar_t cv_bot_auto_vacate;
extern cvar_t cv_bot_zombie;
extern cvar_t cv_bot_defer_to_human;
extern cvar_t cv_bot_chatter;
extern cvar_t cv_bot_profile_db;

#ifdef REGAMEDLL_ADD
extern cvar_t cv_bot_deathmatch;
extern cvar_t cv_bot_quota_mode;
extern cvar_t cv_bot_join_delay;
#else
extern cvar_t cv_bot_quota_match;
#endif
