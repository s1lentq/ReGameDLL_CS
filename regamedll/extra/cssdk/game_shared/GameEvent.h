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

enum GameEventType
{
	EVENT_INVALID = 0,
	EVENT_WEAPON_FIRED,			// tell bots the player is attack (argumens: 1 = attacker, 2 = NULL)
	EVENT_WEAPON_FIRED_ON_EMPTY,		// tell bots the player is attack without clip ammo (argumens: 1 = attacker, 2 = NULL)
	EVENT_WEAPON_RELOADED,			// tell bots the player is reloading his weapon (argumens: 1 = reloader, 2 = NULL)

	EVENT_HE_GRENADE_EXPLODED,		// tell bots the HE grenade is exploded (argumens: 1 = grenade thrower, 2 = NULL)
	EVENT_FLASHBANG_GRENADE_EXPLODED,	// tell bots the flashbang grenade is exploded (argumens: 1 = grenade thrower, 2 = explosion origin)
	EVENT_SMOKE_GRENADE_EXPLODED,		// tell bots the smoke grenade is exploded (argumens: 1 = grenade thrower, 2 = NULL)
	EVENT_GRENADE_BOUNCED,

	EVENT_BEING_SHOT_AT,
	EVENT_PLAYER_BLINDED_BY_FLASHBANG,	// tell bots the player is flashed (argumens: 1 = flashed player, 2 = NULL)
	EVENT_PLAYER_FOOTSTEP,			// tell bots the player is running (argumens: 1 = runner, 2 = NULL)
	EVENT_PLAYER_JUMPED,			// tell bots the player is jumped (argumens: 1 = jumper, 2 = NULL)
	EVENT_PLAYER_DIED,			// tell bots the player is killed (argumens: 1 = victim, 2 = killer)
	EVENT_PLAYER_LANDED_FROM_HEIGHT,	// tell bots the player is fell with some damage (argumens: 1 = felled player, 2 = NULL)
	EVENT_PLAYER_TOOK_DAMAGE,		// tell bots the player is take damage (argumens: 1 = victim, 2 = attacker)
	EVENT_HOSTAGE_DAMAGED,			// tell bots the player has injured a hostage (argumens: 1 = hostage, 2 = injurer)
	EVENT_HOSTAGE_KILLED,			// tell bots the player has killed a hostage (argumens: 1 = hostage, 2 = killer)

	EVENT_DOOR,				// tell bots the door is moving (argumens: 1 = door, 2 = NULL)
	EVENT_BREAK_GLASS,			// tell bots the glass has break (argumens: 1 = glass, 2 = NULL)
	EVENT_BREAK_WOOD,			// tell bots the wood has break (argumens: 1 = wood, 2 = NULL)
	EVENT_BREAK_METAL,			// tell bots the metal/computer has break (argumens: 1 = metal/computer, 2 = NULL)
	EVENT_BREAK_FLESH,			// tell bots the flesh has break (argumens: 1 = flesh, 2 = NULL)
	EVENT_BREAK_CONCRETE,			// tell bots the concrete has break (argumens: 1 = concrete, 2 = NULL)

	EVENT_BOMB_PLANTED,			// tell bots the bomb has been planted (argumens: 1 = planter, 2 = NULL)
	EVENT_BOMB_DROPPED,			// tell bots the bomb has been dropped (argumens: 1 = NULL, 2 = NULL)
	EVENT_BOMB_PICKED_UP,			// let the bots hear the bomb pickup (argumens: 1 = player that pickup c4, 2 = NULL)
	EVENT_BOMB_BEEP,			// let the bots hear the bomb beeping (argumens: 1 = c4, 2 = NULL)
	EVENT_BOMB_DEFUSING,			// tell the bots someone has started defusing (argumens: 1 = defuser, 2 = NULL)
	EVENT_BOMB_DEFUSE_ABORTED,		// tell the bots someone has aborted defusing (argumens: 1 = NULL, 2 = NULL)
	EVENT_BOMB_DEFUSED,			// tell the bots the bomb is defused (argumens: 1 = defuser, 2 = NULL)
	EVENT_BOMB_EXPLODED,			// let the bots hear the bomb exploding (argumens: 1 = NULL, 2 = NULL)

	EVENT_HOSTAGE_USED,			// tell bots the hostage is used (argumens: 1 = user, 2 = NULL)
	EVENT_HOSTAGE_RESCUED,			// tell bots the hostage is rescued (argumens: 1 = rescuer (CBasePlayer *), 2 = hostage (CHostage *))
	EVENT_ALL_HOSTAGES_RESCUED,		// tell bots the all hostages are rescued (argumens: 1 = NULL, 2 = NULL)

	EVENT_VIP_ESCAPED,			// tell bots the VIP is escaped (argumens: 1 = NULL, 2 = NULL)
	EVENT_VIP_ASSASSINATED,			// tell bots the VIP is assassinated (argumens: 1 = NULL, 2 = NULL)
	EVENT_TERRORISTS_WIN,			// tell bots the terrorists won the round (argumens: 1 = NULL, 2 = NULL)
	EVENT_CTS_WIN,				// tell bots the CTs won the round (argumens: 1 = NULL, 2 = NULL)
	EVENT_ROUND_DRAW,			// tell bots the round was a draw (argumens: 1 = NULL, 2 = NULL)
	EVENT_ROUND_WIN,			// tell carreer the round was a win (argumens: 1 = NULL, 2 = NULL)
	EVENT_ROUND_LOSS,			// tell carreer the round was a loss (argumens: 1 = NULL, 2 = NULL)
	EVENT_ROUND_START,			// tell bots the round was started (when freeze period is expired) (argumens: 1 = NULL, 2 = NULL)
	EVENT_PLAYER_SPAWNED,			// tell bots the player is spawned (argumens: 1 = spawned player, 2 = NULL)
	EVENT_CLIENT_CORPSE_SPAWNED,
	EVENT_BUY_TIME_START,
	EVENT_PLAYER_LEFT_BUY_ZONE,
	EVENT_DEATH_CAMERA_START,
	EVENT_KILL_ALL,
	EVENT_ROUND_TIME,
	EVENT_DIE,
	EVENT_KILL,
	EVENT_HEADSHOT,
	EVENT_KILL_FLASHBANGED,
	EVENT_TUTOR_BUY_MENU_OPENNED,
	EVENT_TUTOR_AUTOBUY,
	EVENT_PLAYER_BOUGHT_SOMETHING,
	EVENT_TUTOR_NOT_BUYING_ANYTHING,
	EVENT_TUTOR_NEED_TO_BUY_PRIMARY_WEAPON,
	EVENT_TUTOR_NEED_TO_BUY_PRIMARY_AMMO,
	EVENT_TUTOR_NEED_TO_BUY_SECONDARY_AMMO,
	EVENT_TUTOR_NEED_TO_BUY_ARMOR,
	EVENT_TUTOR_NEED_TO_BUY_DEFUSE_KIT,
	EVENT_TUTOR_NEED_TO_BUY_GRENADE,
	EVENT_CAREER_TASK_DONE,

	EVENT_START_RADIO_1,
	EVENT_RADIO_COVER_ME,
	EVENT_RADIO_YOU_TAKE_THE_POINT,
	EVENT_RADIO_HOLD_THIS_POSITION,
	EVENT_RADIO_REGROUP_TEAM,
	EVENT_RADIO_FOLLOW_ME,
	EVENT_RADIO_TAKING_FIRE,
	EVENT_START_RADIO_2,
	EVENT_RADIO_GO_GO_GO,
	EVENT_RADIO_TEAM_FALL_BACK,
	EVENT_RADIO_STICK_TOGETHER_TEAM,
	EVENT_RADIO_GET_IN_POSITION_AND_WAIT,
	EVENT_RADIO_STORM_THE_FRONT,
	EVENT_RADIO_REPORT_IN_TEAM,
	EVENT_START_RADIO_3,
	EVENT_RADIO_AFFIRMATIVE,
	EVENT_RADIO_ENEMY_SPOTTED,
	EVENT_RADIO_NEED_BACKUP,
	EVENT_RADIO_SECTOR_CLEAR,
	EVENT_RADIO_IN_POSITION,
	EVENT_RADIO_REPORTING_IN,
	EVENT_RADIO_GET_OUT_OF_THERE,
	EVENT_RADIO_NEGATIVE,
	EVENT_RADIO_ENEMY_DOWN,
	EVENT_END_RADIO,

	EVENT_NEW_MATCH,			// tell bots the game is new (argumens: 1 = NULL, 2 = NULL)
	EVENT_PLAYER_CHANGED_TEAM,		// tell bots the player is switch his team (also called from ClientPutInServer()) (argumens: 1 = switcher, 2 = NULL)
	EVENT_BULLET_IMPACT,			// tell bots the player is shoot at wall (argumens: 1 = shooter, 2 = shoot trace end position)
	EVENT_GAME_COMMENCE,			// tell bots the game is commencing (argumens: 1 = NULL, 2 = NULL)
	EVENT_WEAPON_ZOOMED,			// tell bots the player is switch weapon zoom (argumens: 1 = zoom switcher, 2 = NULL)
	EVENT_HOSTAGE_CALLED_FOR_HELP,		// tell bots the hostage is talking (argumens: 1 = listener, 2 = NULL)
	NUM_GAME_EVENTS,
};

extern const char *GameEventName[ NUM_GAME_EVENTS + 1 ];
