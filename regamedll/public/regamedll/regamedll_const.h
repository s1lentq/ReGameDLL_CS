/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#pragma once

// These are caps bits to indicate what an object's capabilities (currently used for save/restore and level transitions)
#define FCAP_CUSTOMSAVE         0x00000001
#define FCAP_ACROSS_TRANSITION  0x00000002 // Should transfer between transitions
#define FCAP_MUST_SPAWN         0x00000004 // Spawn after restore
#define FCAP_DONT_SAVE          0x80000000 // Don't save this
#define FCAP_IMPULSE_USE        0x00000008 // Can be used by the player
#define FCAP_CONTINUOUS_USE     0x00000010 // Can be used by the player
#define FCAP_ONOFF_USE          0x00000020 // Can be used by the player
#define FCAP_DIRECTIONAL_USE    0x00000040 // Player sends +/- 1 when using (currently only tracktrains)
#define FCAP_MASTER             0x00000080 // Can be used to "master" other entities (like multisource)
#define FCAP_MUST_RESET         0x00000100 // Should reset on the new round
#define FCAP_MUST_RELEASE       0x00000200 // Should release on the new round

// UNDONE: This will ignore transition volumes (trigger_transition), but not the PVS!!!
#define FCAP_FORCE_TRANSITION   0x00000080 // ALWAYS goes across transitions

// for Classify
#define CLASS_NONE              0
#define CLASS_MACHINE           1
#define CLASS_PLAYER            2
#define CLASS_HUMAN_PASSIVE     3
#define CLASS_HUMAN_MILITARY    4
#define CLASS_ALIEN_MILITARY    5
#define CLASS_ALIEN_PASSIVE     6
#define CLASS_ALIEN_MONSTER     7
#define CLASS_ALIEN_PREY        8
#define CLASS_ALIEN_PREDATOR    9
#define CLASS_INSECT            10
#define CLASS_PLAYER_ALLY       11
#define CLASS_PLAYER_BIOWEAPON  12 // hornets and snarks.launched by players
#define CLASS_ALIEN_BIOWEAPON   13 // hornets and snarks.launched by the alien menace
#define CLASS_VEHICLE           14
#define CLASS_BARNACLE          99 // special because no one pays attention to it, and it eats a wide cross-section of creatures.

#define SF_NORESPAWN            (1<<30) // set this bit on guns and stuff that should never respawn.

#define DMG_GENERIC             0       // generic damage was done
#define DMG_CRUSH               (1<<0)  // crushed by falling or moving object
#define DMG_BULLET              (1<<1)  // shot
#define DMG_SLASH               (1<<2)  // cut, clawed, stabbed
#define DMG_BURN                (1<<3)  // heat burned
#define DMG_FREEZE              (1<<4)  // frozen
#define DMG_FALL                (1<<5)  // fell too far
#define DMG_BLAST               (1<<6)  // explosive blast damage
#define DMG_CLUB                (1<<7)  // crowbar, punch, headbutt
#define DMG_SHOCK               (1<<8)  // electric shock
#define DMG_SONIC               (1<<9)  // sound pulse shockwave
#define DMG_ENERGYBEAM          (1<<10) // laser or other high energy beam
#define DMG_NEVERGIB            (1<<12) // with this bit OR'd in, no damage type will be able to gib victims upon death
#define DMG_ALWAYSGIB           (1<<13) // with this bit OR'd in, any damage type can be made to gib victims upon death
#define DMG_DROWN               (1<<14) // Drowning

// time-based damage
#define DMG_TIMEBASED           (~(0x3FFF)) // mask for time-based damage

#define DMG_PARALYZE            (1<<15) // slows affected creature down
#define DMG_NERVEGAS            (1<<16) // nerve toxins, very bad
#define DMG_POISON              (1<<17) // blood poisioning
#define DMG_RADIATION           (1<<18) // radiation exposure
#define DMG_DROWNRECOVER        (1<<19) // drowning recovery
#define DMG_ACID                (1<<20) // toxic chemicals or acid burns
#define DMG_SLOWBURN            (1<<21) // in an oven
#define DMG_SLOWFREEZE          (1<<22) // in a subzero freezer
#define DMG_MORTAR              (1<<23) // Hit by air raid (done to distinguish grenade from mortar)
#define DMG_EXPLOSION           (1<<24)

// These are the damage types that are allowed to gib corpses
#define DMG_GIB_CORPSE         (DMG_CRUSH | DMG_FALL | DMG_BLAST | DMG_SONIC | DMG_CLUB)

// These are the damage types that have client hud art
#define DMG_SHOWNHUD           (DMG_POISON | DMG_ACID | DMG_FREEZE | DMG_SLOWFREEZE | DMG_DROWN | DMG_BURN | DMG_SLOWBURN | DMG_NERVEGAS | DMG_RADIATION | DMG_SHOCK)

// When calling KILLED(), a value that governs gib behavior is expected to be
// one of these three values
#define GIB_NORMAL             0 // Gib if entity was overkilled
#define GIB_NEVER              1 // Never gib, no matter how much death damage is done ( freezing, etc )
#define GIB_ALWAYS             2 // Always gib ( Houndeye Shock, Barnacle Bite )
#define GIB_HEALTH_VALUE      -30
