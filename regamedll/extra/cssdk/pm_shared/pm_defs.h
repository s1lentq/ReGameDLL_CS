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

#include "pm_info.h"
#include "pmtrace.h"

#ifndef USERCMD_H
#include "usercmd.h"
#endif

#include "const.h"

#define MAX_PHYSENTS 600 		  		// Must have room for all entities in the world.
#define MAX_MOVEENTS 64
#define MAX_CLIP_PLANES	5

#define PM_NORMAL			0x00000000
#define PM_STUDIO_IGNORE		0x00000001	// Skip studio models
#define PM_STUDIO_BOX			0x00000002	// Use boxes for non-complex studio models (even in traceline)
#define PM_GLASS_IGNORE			0x00000004	// Ignore entities with non-normal rendermode
#define PM_WORLD_ONLY			0x00000008	// Only trace against the world

#define PM_TRACELINE_PHYSENTSONLY	0
#define PM_TRACELINE_ANYVISIBLE		1

typedef struct physent_s
{
	char name[32];					// Name of model, or "player" or "world".
	int player;
	vec3_t origin;					// Model's origin in world coordinates.
	struct model_s *model;				// only for bsp models
	struct model_s *studiomodel;			// SOLID_BBOX, but studio clip intersections.
	vec3_t mins, maxs;				// only for non-bsp models
	int info;					// For client or server to use to identify (index into edicts or cl_entities)
	vec3_t angles;					// rotated entities need this info for hull testing to work.

	int solid;					// Triggers and func_door type WATER brushes are SOLID_NOT
	int skin;					// BSP Contents for such things like fun_door water brushes.
	int rendermode;					// So we can ignore glass

	float frame;
	int sequence;
	byte controller[4];
	byte blending[2];

	int movetype;
	int takedamage;
	int blooddecal;
	int team;
	int classnumber;

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

} physent_t;

typedef struct playermove_s
{
	int player_index;				// So we don't try to run the PM_CheckStuck nudging too quickly.
	qboolean server;				// For debugging, are we running physics code on server side?
	qboolean multiplayer;				// 1 == multiplayer server
	float time;					// realtime on host, for reckoning duck timing
	float frametime;				// Duration of this frame
	vec3_t forward, right, up;			// Vectors for angles
	vec3_t origin;					// Movement origin.
	vec3_t angles;					// Movement view angles.
	vec3_t oldangles;				// Angles before movement view angles were looked at.
	vec3_t velocity;				// Current movement direction.
	vec3_t movedir;					// For waterjumping, a forced forward velocity so we can fly over lip of ledge.
	vec3_t basevelocity;				// Velocity of the conveyor we are standing, e.g.
	vec3_t view_ofs;				// For ducking/dead
							// Our eye position.
	float flDuckTime;				// Time we started duck
	qboolean bInDuck;				// In process of ducking or ducked already?
	int flTimeStepSound;				// For walking/falling
							// Next time we can play a step sound
	int iStepLeft;
	float flFallVelocity;
	vec3_t punchangle;
	float flSwimTime;
	float flNextPrimaryAttack;
	int effects;					// MUZZLE FLASH, e.g.
	int flags;					// FL_ONGROUND, FL_DUCKING, etc.
	int usehull;					// 0 = regular player hull, 1 = ducked player hull, 2 = point hull
	float gravity;					// Our current gravity and friction.
	float friction;
	int oldbuttons;					// Buttons last usercmd
	float waterjumptime;				// Amount of time left in jumping out of water cycle.
	qboolean dead;					// Are we a dead player?
	int deadflag;
	int spectator;					// Should we use spectator physics model?
	int movetype;					// Our movement type, NOCLIP, WALK, FLY
	int onground;					// -1 = in air, else pmove entity number
	int waterlevel;
	int watertype;
	int oldwaterlevel;
	char sztexturename[256];
	char chtexturetype;
	float maxspeed;
	float clientmaxspeed;
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
	int numphysent;					// world state
							// Number of entities to clip against.
	physent_t physents[MAX_PHYSENTS];
	int nummoveent;					// Number of momvement entities (ladders)
	physent_t moveents[MAX_MOVEENTS];		// just a list of ladders
	int numvisent;					// All things being rendered, for tracing against things you don't actually collide with
	physent_t visents[MAX_PHYSENTS];
	usercmd_t cmd;					// input to run through physics.
	int numtouch;					// Trace results for objects we collided with.
	pmtrace_t touchindex[MAX_PHYSENTS];
	char physinfo[MAX_PHYSINFO_STRING];		// Physics info string
	struct movevars_s *movevars;
	vec_t _player_mins[4][3];
	vec_t _player_maxs[4][3];

	const char *(*PM_Info_ValueForKey)(const char *s, const char *key);
	void (*PM_Particle)(float *origin, int color, float life, int zpos, int zvel);
	int (*PM_TestPlayerPosition)(float *pos, pmtrace_t *ptrace);
	void (*Con_NPrintf)(int idx, char *fmt, ...);
	void (*Con_DPrintf)(char *fmt, ...);
	void (*Con_Printf)(char *fmt, ...);
	double (*Sys_FloatTime)();
	void (*PM_StuckTouch)(int hitent, pmtrace_t *ptraceresult);
	int (*PM_PointContents)(float *p, int *truecontents);
	int (*PM_TruePointContents)(float *p);
	int (*PM_HullPointContents)(struct hull_s *hull, int num, float *p);
	pmtrace_t (*PM_PlayerTrace)(float *start, float *end, int traceFlags, int ignore_pe);
	struct pmtrace_s *(*PM_TraceLine)(float *start, float *end, int flags, int usehulll, int ignore_pe);
	int32 (*RandomLong)(int32 lLow, int32 lHigh);
	float (*RandomFloat)(float flLow, float flHigh);
	int (*PM_GetModelType)(struct model_s *mod);
	void (*PM_GetModelBounds)(struct model_s *mod, float *mins, float *maxs);
	void *(*PM_HullForBsp)(physent_t *pe, float *offset);
	float (*PM_TraceModel)(physent_t *pEnt, float *start, float *end, trace_t *trace);
	int (*COM_FileSize)(char *filename);
	byte *(*COM_LoadFile)(char *path, int usehunk, int *pLength);
	void (*COM_FreeFile)(void *buffer);
	char *(*memfgets)(byte *pMemFile, int fileSize, int *pFilePos, char *pBuffer, int bufferSize);
	qboolean runfuncs;
	void (*PM_PlaySound)(int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch);
	const char *(*PM_TraceTexture)(int ground, float *vstart, float *vend);
	void (*PM_PlaybackEventFull)(int flags, int clientindex, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);

} playermove_t;
