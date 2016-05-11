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

#define PM_DEAD_VIEWHEIGHT		-8

#define OBS_NONE			0
#define OBS_CHASE_LOCKED		1
#define OBS_CHASE_FREE			2
#define OBS_ROAMING			3
#define OBS_IN_EYE			4
#define OBS_MAP_FREE			5
#define OBS_MAP_CHASE			6

#define STEP_CONCRETE			0
#define STEP_METAL			1
#define STEP_DIRT			2
#define STEP_VENT			3
#define STEP_GRATE			4
#define STEP_TILE			5
#define STEP_SLOSH			6
#define STEP_WADE			7
#define STEP_LADDER			8
#define STEP_SNOW			9

#define WJ_HEIGHT				8
#define STOP_EPSILON				0.1
#define MAX_CLIMB_SPEED				200
#define PLAYER_DUCKING_MULTIPLIER		0.333
#define PM_CHECKSTUCK_MINTIME			0.05	// Don't check again too quickly.

#define PLAYER_LONGJUMP_SPEED			350.0f	// how fast we longjump

// Ducking time
#define TIME_TO_DUCK				0.4
#define STUCK_MOVEUP				1

#define PM_VEC_DUCK_HULL_MIN			-18
#define PM_VEC_HULL_MIN				-36
#define PM_VEC_DUCK_VIEW			12
#define PM_VEC_VIEW				17

#define PM_PLAYER_MAX_SAFE_FALL_SPEED		580	// approx 20 feet
#define PM_PLAYER_MIN_BOUNCE_SPEED		350
#define PM_PLAYER_FALL_PUNCH_THRESHHOLD		250	// won't punch player's screen/make scrape noise unless player falling at least this fast.

// Only allow bunny jumping up to 1.2x server / player maxspeed setting
#define BUNNYJUMP_MAX_SPEED_FACTOR		1.2f

extern struct playermove_s *pmove;
