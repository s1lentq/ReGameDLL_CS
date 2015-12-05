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

#ifndef TUTOR_H
#define TUTOR_H
#ifdef _WIN32
#pragma once
#endif

#ifdef HOOK_GAMEDLL

#define s_tutorDisabledThisGame (*ps_tutorDisabledThisGame)
#define s_nextCvarCheckTime (*ps_nextCvarCheckTime)

#define cv_tutor_message_repeats (*pcv_tutor_message_repeats)
#define cv_tutor_debug_level (*pcv_tutor_debug_level)
#define cv_tutor_view_distance (*pcv_tutor_view_distance)
#define cv_tutor_viewable_check_interval (*pcv_tutor_viewable_check_interval)
#define cv_tutor_look_distance (*pcv_tutor_look_distance)
#define cv_tutor_look_angle (*pcv_tutor_look_angle)
#define cv_tutor_examine_time (*pcv_tutor_examine_time)
#define cv_tutor_message_minimum_display_time (*pcv_tutor_message_minimum_display_time)
#define cv_tutor_message_character_display_time_coefficient (*pcv_tutor_message_character_display_time_coefficient)
#define cv_tutor_hint_interval_time (*pcv_tutor_hint_interval_time)

#endif // HOOK_GAMEDLL

extern bool s_tutorDisabledThisGame;
extern float s_nextCvarCheckTime;

extern cvar_t cv_tutor_message_repeats;
extern cvar_t cv_tutor_debug_level;
extern cvar_t cv_tutor_view_distance;
extern cvar_t cv_tutor_viewable_check_interval;
extern cvar_t cv_tutor_look_distance;
extern cvar_t cv_tutor_look_angle;
extern cvar_t cv_tutor_examine_time;
extern cvar_t cv_tutor_message_minimum_display_time;
extern cvar_t cv_tutor_message_character_display_time_coefficient;
extern cvar_t cv_tutor_hint_interval_time;

void InstallTutor(bool start);
void Tutor_RegisterCVars(void);
void MonitorTutorStatus(void);

#endif // TUTOR_H
