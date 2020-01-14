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

#include "skill.h"

#define R_AL -2 // (ALLY) pals. Good alternative to R_NO when applicable.
#define R_FR -1 // (FEAR) will run
#define R_NO 0  // (NO RELATIONSHIP) disregard
#define R_DL 1  // (DISLIKE) will attack
#define R_HT 2  // (HATE) will attack this character instead of any visible DISLIKEd characters
#define R_NM 3  // (NEMESIS) A monster Will ALWAYS attack its nemsis, no matter what

#define SF_MONSTER_WAIT_TILL_SEEN  BIT(0) // spawnflag that makes monsters wait until player can see them before attacking.
#define SF_MONSTER_GAG             BIT(1) // no idle noises from this monster
#define SF_MONSTER_HITMONSTERCLIP  BIT(2)
#define SF_MONSTER_PRISONER        BIT(4) // monster won't attack anyone, no one will attacks him.

#define SF_MONSTER_WAIT_FOR_SCRIPT BIT(7) //spawnflag that makes monsters wait to check for attacking until the script is done or they've been attacked
#define SF_MONSTER_PREDISASTER     BIT(8) //this is a predisaster scientist or barney. Influences how they speak.
#define SF_MONSTER_FADECORPSE      BIT(9) // Fade out corpse after death
#define SF_MONSTER_FALL_TO_GROUND  BIT(31)

// These bits represent the monster's memory
#define MEMORY_CLEAR               0
#define bits_MEMORY_PROVOKED       BIT(0)  // right now only used for houndeyes.
#define bits_MEMORY_INCOVER        BIT(1)  // monster knows it is in a covered position.
#define bits_MEMORY_SUSPICIOUS     BIT(2)  // Ally is suspicious of the player, and will move to provoked more easily
#define bits_MEMORY_PATH_FINISHED  BIT(3)  // Finished monster path (just used by big momma for now)
#define bits_MEMORY_ON_PATH        BIT(4)  // Moving on a path
#define bits_MEMORY_MOVE_FAILED    BIT(5)  // Movement has already failed
#define bits_MEMORY_FLINCHED       BIT(6)  // Has already flinched
#define bits_MEMORY_KILLED         BIT(7)  // HACKHACK -- remember that I've already called my Killed()
#define bits_MEMORY_CUSTOM4        BIT(28) // Monster-specific memory
#define bits_MEMORY_CUSTOM3        BIT(29) // Monster-specific memory
#define bits_MEMORY_CUSTOM2        BIT(30) // Monster-specific memory
#define bits_MEMORY_CUSTOM1        BIT(31) // Monster-specific memory

// MoveToOrigin stuff
#define MOVE_START_TURN_DIST 64 // when this far away from moveGoal, start turning to face next goal
#define MOVE_STUCK_DIST      32 // if a monster can't step this far, it is stuck.

#define MOVE_NORMAL          0 // normal move in the direction monster is facing
#define MOVE_STRAFE          1 // moves in direction specified, no matter which way monster is facing

enum HitBoxGroup
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_SHIELD,
	NUM_HITGROUPS,
};
