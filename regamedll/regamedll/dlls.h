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

#include "mathlib.h"
#include "extdll.h"

#include "h_export.h"
#include "schedule.h"
#include "archtypes.h"
#include "scriptevent.h"
#include "enginecallback.h"
#include "entity_state.h"
#include "nodes.h"
#include "screenfade.h"
#include "utlvector.h"

// SDK
#include "usercmd.h"
#include "weaponinfo.h"
#include "customentity.h"

// Globals vars
#include "globals.h"
#include "saverestore.h"

// GameInit
#include "game.h"

//PM
#include "pm_shared/pm_defs.h"
#include "pm_shared/pm_materials.h"
#include "pm_shared/pm_movevars.h"
#include "pm_shared/pm_debug.h"
#include "pm_shared/pm_shared.h"
#include "pm_shared/pm_math.h"

#include "shake.h"
#include "util.h"
#include "decals.h"
#include "hltv.h"
#include "cbase.h"
#include "world.h"

#include "sound.h"
#include "basemonster.h"
#include "monsters.h"
#include "unisignals.h"
#include "weapons.h"
#include "maprules.h"
#include "ammo.h"
#include "mortar.h"
#include "effects.h"
#include "lights.h"
#include "items.h"
#include "healthkit.h"
#include "vehicle.h"
#include "func_tank.h"
#include "func_break.h"
#include "doors.h"
#include "bmodels.h"

#include "debug.h"

#include "player.h"
#include "observer.h"
#include "client.h"

#include "trains.h"
#include "pathcorner.h"
#include "plats.h"
#include "buttons.h"

// weapon shared
#include "wpn_shared.h"

// CSBOT and Nav
#include "game_shared/bot/bot_util.h"
#include "game_shared/bot/simple_state_machine.h"

#include "game_shared/steam_util.h"

#include "game_shared/bot/bot_manager.h"
#include "game_shared/bot/bot_constants.h"
#include "game_shared/bot/bot.h"

#include "game_shared/shared_util.h"
#include "game_shared/bot/bot_profile.h"

#include "game_shared/bot/improv.h"
#include "game_shared/bot/nav.h"
#include "game_shared/bot/nav_node.h"
#include "game_shared/bot/nav_area.h"
#include "game_shared/bot/nav_file.h"
#include "game_shared/bot/nav_path.h"

#include "airtank.h"
#include "h_ai.h"
#include "h_cycler.h"
#include "h_battery.h"

// Hostage
#include "hostage/hostage.h"
#include "hostage/hostage_localnav.h"

#include "bot/cs_bot.h"

// Tutor
#include "tutor.h"
#include "tutor_base_states.h"
#include "tutor_base_tutor.h"
#include "tutor_cs_states.h"
#include "tutor_cs_tutor.h"

#include "revert_saved.h"
#include "triggers.h"
#include "subs.h"
#include "doors.h"
#include "explode.h"
#include "gamerules.h"
#include "career_tasks.h"
#include "training_gamerules.h"
#include "maprules.h"
#include "monsterevent.h"
#include "plane.h"
#include "skill.h"
#include "soundent.h"
#include "spectator.h"
#include "talkmonster.h"
#include "animation.h"
#include "shake.h"
