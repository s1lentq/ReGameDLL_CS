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

#define _A(a)\
	{ a, #a }

activity_map_t activity_map[] =
{
	_A(ACT_IDLE),
	_A(ACT_GUARD),
	_A(ACT_WALK),
	_A(ACT_RUN),
	_A(ACT_FLY),
	_A(ACT_SWIM),
	_A(ACT_HOP),
	_A(ACT_LEAP),
	_A(ACT_FALL),
	_A(ACT_LAND),
	_A(ACT_STRAFE_LEFT),
	_A(ACT_STRAFE_RIGHT),
	_A(ACT_ROLL_LEFT),
	_A(ACT_ROLL_RIGHT),
	_A(ACT_TURN_LEFT),
	_A(ACT_TURN_RIGHT),
	_A(ACT_CROUCH),
	_A(ACT_CROUCHIDLE),
	_A(ACT_STAND),
	_A(ACT_USE),
	_A(ACT_SIGNAL1),
	_A(ACT_SIGNAL2),
	_A(ACT_SIGNAL3),
	_A(ACT_TWITCH),
	_A(ACT_COWER),
	_A(ACT_SMALL_FLINCH),
	_A(ACT_BIG_FLINCH),
	_A(ACT_RANGE_ATTACK1),
	_A(ACT_RANGE_ATTACK2),
	_A(ACT_MELEE_ATTACK1),
	_A(ACT_MELEE_ATTACK2),
	_A(ACT_RELOAD),
	_A(ACT_ARM),
	_A(ACT_DISARM),
	_A(ACT_EAT),
	_A(ACT_DIESIMPLE),
	_A(ACT_DIEBACKWARD),
	_A(ACT_DIEFORWARD),
	_A(ACT_DIEVIOLENT),
	_A(ACT_BARNACLE_HIT),
	_A(ACT_BARNACLE_PULL),
	_A(ACT_BARNACLE_CHOMP),
	_A(ACT_BARNACLE_CHEW),
	_A(ACT_SLEEP),
	_A(ACT_INSPECT_FLOOR),
	_A(ACT_INSPECT_WALL),
	_A(ACT_IDLE_ANGRY),
	_A(ACT_WALK_HURT),
	_A(ACT_RUN_HURT),
	_A(ACT_HOVER),
	_A(ACT_GLIDE),
	_A(ACT_FLY_LEFT),
	_A(ACT_FLY_RIGHT),
	_A(ACT_DETECT_SCENT),
	_A(ACT_SNIFF),
	_A(ACT_BITE),
	_A(ACT_THREAT_DISPLAY),
	_A(ACT_FEAR_DISPLAY),
	_A(ACT_EXCITED),
	_A(ACT_SPECIAL_ATTACK1),
	_A(ACT_SPECIAL_ATTACK2),
	_A(ACT_COMBAT_IDLE),
	_A(ACT_WALK_SCARED),
	_A(ACT_RUN_SCARED),
	_A(ACT_VICTORY_DANCE),
	_A(ACT_DIE_HEADSHOT),
	_A(ACT_DIE_CHESTSHOT),
	_A(ACT_DIE_GUTSHOT),
	_A(ACT_DIE_BACKSHOT),
	_A(ACT_FLINCH_HEAD),
	_A(ACT_FLINCH_CHEST),
	_A(ACT_FLINCH_STOMACH),
	_A(ACT_FLINCH_LEFTARM),
	_A(ACT_FLINCH_RIGHTARM),
	_A(ACT_FLINCH_LEFTLEG),
	_A(ACT_FLINCH_RIGHTLEG),
	0, NULL
};
