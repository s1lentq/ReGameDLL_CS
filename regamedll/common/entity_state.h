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

#ifndef ENTITY_STATE_H
#define ENTITY_STATE_H
#ifdef _WIN32
#pragma once
#endif

#include "const.h"
#include "pm_info.h"

#define ENTITY_NORMAL	(1<<0)
#define ENTITY_BEAM	(1<<1)

// Entity state is used for the baseline and for delta
// compression of a packet of entities that is sent to a client.
typedef struct entity_state_s entity_state_t;

/* <47642> ../common/entity_state.h:15 */
struct entity_state_s
{
	int entityType;
	int number;			// Index into cl_entities array for this entity.
	float msg_time;
	int messagenum;			// Message number last time the player/entity state was updated.
	vec3_t origin;			// Fields which can be transitted and reconstructed over the network stream
	vec3_t angles;
	int modelindex;
	int sequence;
	float frame;
	int colormap;
	short skin;
	short solid;
	int effects;
	float scale;
	byte eflags;
	int rendermode;			// Render information
	int renderamt;
	color24 rendercolor;
	int renderfx;
	int movetype;
	float animtime;
	float framerate;
	int body;
	byte controller[4];
	byte blending[4];
	vec3_t velocity;
	vec3_t mins;			// Send bbox down to client for use during prediction.
	vec3_t maxs;
	int aiment;
	int owner; 			// If owned by a player, the index of that player ( for projectiles ).
	float friction;			// Friction, for prediction.
	float gravity;			// Gravity multiplier
	int team;
	int playerclass;
	int health;
	qboolean spectator;
	int weaponmodel;
	int gaitsequence;
	vec3_t basevelocity;		// If standing on conveyor, e.g.
	int usehull;			// Use the crouched hull, or the regular player hull.
	int oldbuttons;			// Latched buttons last time state updated.
	int onground;			// -1 = in air, else pmove entity number
	int iStepLeft;
	float flFallVelocity;		// How fast we are falling
	float fov;
	int weaponanim;
	vec3_t startpos;		// Parametric movement overrides
	vec3_t endpos;
	float impacttime;
	float starttime;
	int iuser1;
	int iuser2;
	int iuser3;
	int iuser4;
	float fuser1;
	float fuser2;
	float fuser3;
	float fuser4;
	vec3_t vuser1;
	vec3_t vuser2;
	vec3_t vuser3;
	vec3_t vuser4;
};

typedef struct clientdata_s
{
	Vector origin;
	Vector velocity;
	int viewmodel;
	Vector punchangle;
	int flags;
	int waterlevel;
	int watertype;
	Vector view_ofs;
	float health;
	int bInDuck;
	int weapons;
	int flTimeStepSound;
	int flDuckTime;
	int flSwimTime;
	int waterjumptime;
	float maxspeed;
	float fov;
	int weaponanim;
	int m_iId;
	int ammo_shells;
	int ammo_nails;
	int ammo_cells;
	int ammo_rockets;
	float m_flNextAttack;
	int tfstate;
	int pushmsec;
	int deadflag;
	char physinfo[ MAX_PHYSINFO_STRING ];
	int iuser1;
	int iuser2;
	int iuser3;
	int iuser4;
	float fuser1;
	float fuser2;
	float fuser3;
	float fuser4;
	Vector vuser1;
	Vector vuser2;
	Vector vuser3;
	Vector vuser4;

} clientdata_t;

#endif // ENTITY_STATE_H
