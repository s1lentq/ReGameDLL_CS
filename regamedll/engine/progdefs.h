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

#ifndef PROGDEFS_H
#define PROGDEFS_H
#ifdef _WIN32
#pragma once
#endif

typedef struct
{
	float time;
	float frametime;
	float force_retouch;
	string_t mapname;
	string_t startspot;
	float deathmatch;
	float coop;
	float teamplay;
	float serverflags;
	float found_secrets;
	Vector v_forward;
	Vector v_up;
	Vector v_right;
	float trace_allsolid;
	float trace_startsolid;
	float trace_fraction;
	Vector trace_endpos;
	Vector trace_plane_normal;
	float trace_plane_dist;
	edict_t *trace_ent;
	float trace_inopen;
	float trace_inwater;
	int trace_hitgroup;
	int trace_flags;
	int msg_entity;
	int cdAudioTrack;
	int maxClients;
	int maxEntities;
	const char *pStringBase;
	void *pSaveData;
	Vector vecLandmarkOffset;
} globalvars_t;

typedef struct entvars_s
{
	string_t classname;
	string_t globalname;

	Vector origin;
	Vector oldorigin;
	Vector velocity;
	Vector basevelocity;
	Vector clbasevelocity;		// Base velocity that was passed in to server physics so
					// client can predict conveyors correctly.  Server zeroes it, so we need to store here, too.
	Vector movedir;
	Vector angles;			// Model angles
	Vector avelocity;		// angle velocity (degrees per second)
	Vector punchangle;		// auto-decaying view angle adjustment
	Vector v_angle;			// Viewing angle (player only)

	Vector endpos;
	Vector startpos;
	float impacttime;
	float starttime;
	int fixangle;			// 0:nothing, 1:force view angles, 2:add avelocity
	float idealpitch;
	float pitch_speed;
	float ideal_yaw;
	float yaw_speed;

	int modelindex;
	string_t model;
	string_t viewmodel;		// player's viewmodel
	string_t weaponmodel;	// what other players see

	Vector absmin;			// BB max translated to world coord
	Vector absmax;			// BB max translated to world coord
	Vector mins;			// local BB min
	Vector maxs;			// local BB max
	Vector size;			// maxs - mins

	float ltime;
	float nextthink;
	int movetype;
	int solid;
	int skin;
	int body;			// sub-model selection for studiomodels
	int effects;
	float gravity;			// % of "normal" gravity
	float friction;			// inverse elasticity of MOVETYPE_BOUNCE
	int light_level;
	int sequence;			// animation sequence
	int gaitsequence;		// movement animation sequence for player (0 for none)
	float frame;			// % playback position in animation sequences (0..255)
	float animtime;			// world time when frame was set
	float framerate;		// animation playback rate (-8x to 8x)
	byte controller[4];		// bone controller setting (0..255)
	byte blending[2];		// blending amount between sub-sequences (0..255)

	float scale;			// sprite rendering scale (0..255)
	int rendermode;
	float renderamt;
	Vector rendercolor;
	int renderfx;
	float health;
	float frags;
	int weapons;			// bit mask for available weapons
	float takedamage;

	int deadflag;
	Vector view_ofs;		// eye position
	int button;
	int impulse;

	edict_t *chain;			// Entity pointer when linked into a linked list
	edict_t *dmg_inflictor;
	edict_t *enemy;
	edict_t *aiment;		// entity pointer when MOVETYPE_FOLLOW
	edict_t *owner;
	edict_t *groundentity;

	int spawnflags;
	int flags;
	int colormap;			// lowbyte topcolor, highbyte bottomcolor
	int team;
	float max_health;
	float teleport_time;
	float armortype;
	float armorvalue;
	int waterlevel;
	int watertype;

	string_t target;
	string_t targetname;
	string_t netname;
	string_t message;

	float dmg_take;
	float dmg_save;
	float dmg;
	float dmgtime;

	string_t noise;
	string_t noise1;
	string_t noise2;
	string_t noise3;

	float speed;
	float air_finished;
	float pain_finished;
	float radsuit_finished;

	edict_t *pContainingEntity;

	int playerclass;
	float maxspeed;
	float fov;
	int weaponanim;
	int pushmsec;
	int bInDuck;
	int flTimeStepSound;
	int flSwimTime;
	int flDuckTime;
	int iStepLeft;
	float flFallVelocity;

	int gamestate;
	int oldbuttons;
	int groupinfo;

	// For mods
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
	edict_t *euser1;
	edict_t *euser2;
	edict_t *euser3;
	edict_t *euser4;
} entvars_t;

#endif // PROGDEFS_H
