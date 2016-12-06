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

#include "enginecallback.h"

#define eoNullEntity		0	// Testing the three types of "entity" for nullity
#define iStringNull		0	// Testing strings for nullity

#define cchMapNameMost		32

#define CBSENTENCENAME_MAX	16
#define CVOXFILESENTENCEMAX	1536	// max number of sentences in game. NOTE: this must match CVOXFILESENTENCEMAX in engine\sound.h

#define GROUP_OP_AND		0
#define GROUP_OP_NAND		1

extern globalvars_t *gpGlobals;

// Use this instead of ALLOC_STRING on constant strings
#define STRING(offset)		((const char *)(gpGlobals->pStringBase + (unsigned int)(offset)))
#define MAKE_STRING(str)	((uint64)(str) - (uint64)(STRING(0)))

// Dot products for view cone checking
#define VIEW_FIELD_FULL		-1.0		// +-180 degrees
#define VIEW_FIELD_WIDE		-0.7		// +-135 degrees 0.1 // +-85 degrees, used for full FOV checks
#define VIEW_FIELD_NARROW	0.7		// +-45 degrees, more narrow check used to set up ranged attacks
#define VIEW_FIELD_ULTRA_NARROW	0.9		// +-25 degrees, more narrow check used to set up ranged attacks

#define SND_SPAWNING		(1<<8)		// duplicated in protocol.h we're spawing, used in some cases for ambients
#define SND_STOP		(1<<5)		// duplicated in protocol.h stop sound
#define SND_CHANGE_VOL		(1<<6)		// duplicated in protocol.h change sound vol
#define SND_CHANGE_PITCH	(1<<7)		// duplicated in protocol.h change sound pitch

// All monsters need this data
#define DONT_BLEED		-1
#define BLOOD_COLOR_RED		(byte)247
#define BLOOD_COLOR_YELLOW	(byte)195
#define BLOOD_COLOR_GREEN	BLOOD_COLOR_YELLOW

#define GERMAN_GIB_COUNT	4
#define HUMAN_GIB_COUNT		6
#define ALIEN_GIB_COUNT		4

#define LANGUAGE_ENGLISH	0
#define LANGUAGE_GERMAN		1
#define LANGUAGE_FRENCH		2
#define LANGUAGE_BRITISH	3

#define SVC_TEMPENTITY		23
#define SVC_INTERMISSION	30
#define SVC_CDTRACK		32
#define SVC_WEAPONANIM		35
#define SVC_ROOMTYPE		37
#define SVC_DIRECTOR		51

// func_rotating
#define SF_BRUSH_ROTATE_Y_AXIS		0
#define SF_BRUSH_ROTATE_INSTANT		1
#define SF_BRUSH_ROTATE_BACKWARDS	2
#define SF_BRUSH_ROTATE_Z_AXIS		4
#define SF_BRUSH_ROTATE_X_AXIS		8
#define SF_PENDULUM_AUTO_RETURN		16
#define SF_PENDULUM_PASSABLE		32

#define SF_BRUSH_ROTATE_SMALLRADIUS	128
#define SF_BRUSH_ROTATE_MEDIUMRADIUS	256
#define SF_BRUSH_ROTATE_LARGERADIUS	512

#define SPAWNFLAG_NOMESSAGE		1
#define SPAWNFLAG_NOTOUCH		1
#define SPAWNFLAG_DROIDONLY		4

#define VEC_HULL_MIN_Z		Vector(0, 0, -36)
#define VEC_DUCK_HULL_MIN_Z	Vector(0, 0, -18)

#define VEC_HULL_MIN		Vector(-16, -16, -36)
#define VEC_HULL_MAX		Vector(16, 16, 36)

#define VEC_VIEW		Vector(0, 0, 17)

#define VEC_DUCK_HULL_MIN	Vector(-16, -16, -18)
#define VEC_DUCK_HULL_MAX	Vector(16, 16, 32)
#define VEC_DUCK_VIEW		Vector(0, 0, 12)

#define PRECACHE_SOUND_ARRAY(a) \
	{ for (int i = 0; i < ARRAYSIZE(a); ++i) PRECACHE_SOUND((char *)a[i]); }

// Inlines
inline edict_t *FIND_ENTITY_BY_CLASSNAME(edict_t *entStart, const char *pszName) { return FIND_ENTITY_BY_STRING(entStart, "classname", pszName); }
inline edict_t *FIND_ENTITY_BY_TARGETNAME(edict_t *entStart, const char *pszName) { return FIND_ENTITY_BY_STRING(entStart, "targetname", pszName); }

inline edict_t *ENT(const entvars_t *pev) { return pev->pContainingEntity; }
inline edict_t *ENT(EOFFSET eoffset) { return (*g_engfuncs.pfnPEntityOfEntOffset)(eoffset); }
inline EOFFSET OFFSET(const edict_t *pent) { return (*g_engfuncs.pfnEntOffsetOfPEntity)(pent); }
inline EOFFSET OFFSET(const entvars_t *pev) { return OFFSET(ENT(pev)); }

inline entvars_t *VARS(edict_t *pent)
{
	if (!pent)
		return NULL;

	return &pent->v;
}

inline entvars_t *VARS(EOFFSET eoffset)
{
	return VARS(ENT(eoffset));
}

#ifndef ENTINDEX
inline int ENTINDEX(const edict_t *pEdict) { return (*g_engfuncs.pfnIndexOfEdict)(pEdict); }
inline int ENTINDEX(const entvars_t *pev) { return (*g_engfuncs.pfnIndexOfEdict)(ENT(pev)); }
#endif // ENTINDEX

#ifndef INDEXENT
inline edict_t *INDEXENT(int iEdictNum) { return (*g_engfuncs.pfnPEntityOfEntIndex)(iEdictNum); }
#endif // INDEXENT

inline void MESSAGE_BEGIN(int msg_dest, int msg_type, const float *pOrigin, entvars_t *ent) { MESSAGE_BEGIN(msg_dest, msg_type, pOrigin, ENT(ent)); }
inline BOOL FNullEnt(EOFFSET eoffset) { return (eoffset == 0); }
inline BOOL FNullEnt(entvars_t *pev) { return (pev == NULL || FNullEnt(OFFSET(pev))); }
inline BOOL FNullEnt(const edict_t *pent) { return (pent == NULL || FNullEnt(OFFSET(pent))); }
inline BOOL FStringNull(int iString) { return (iString == iStringNull); }
inline BOOL FStrEq(const char *sz1, const char *sz2) { return (strcmp(sz1, sz2) == 0); }
inline BOOL FClassnameIs(entvars_t *pev, const char *szClassname) { return FStrEq(STRING(pev->classname), szClassname); }
inline BOOL FClassnameIs(edict_t *pent, const char *szClassname) { return FStrEq(STRING(VARS(pent)->classname), szClassname); }

inline void UTIL_MakeVectorsPrivate(Vector vecAngles, float *p_vForward, float *p_vRight, float *p_vUp) { g_engfuncs.pfnAngleVectors(vecAngles, p_vForward, p_vRight, p_vUp); }

// NOTE: use EMIT_SOUND_DYN to set the pitch of a sound. Pitch of 100
// is no pitch shift.  Pitch > 100 up to 255 is a higher pitch, pitch < 100
// down to 1 is a lower pitch.   150 to 70 is the realistic range.
// EMIT_SOUND_DYN with pitch != 100 should be used sparingly, as it's not quite as
// fast as EMIT_SOUND (the pitchshift mixer is not native coded).
inline void EMIT_SOUND(edict_t *entity, int channel, const char *sample, float volume, float attenuation)
{
	EMIT_SOUND_DYN2(entity, channel, sample, volume, attenuation, 0, PITCH_NORM);
}

inline void STOP_SOUND(edict_t *entity, int channel, const char *sample)
{
	EMIT_SOUND_DYN2(entity, channel, sample, 0, 0, SND_STOP, PITCH_NORM);
}

inline void UTIL_SetSize(entvars_t *pev, const Vector &vecMin, const Vector &vecMax)
{
	SET_SIZE(ENT(pev), vecMin, vecMax);
}

inline void UTIL_SetOrigin(entvars_t *pev, const Vector &vecOrigin)
{
	edict_t *ent = ENT(pev);

	if (ent != NULL)
		SET_ORIGIN(ent, vecOrigin);
}

inline void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters), pentIgnore, ptr);
}

extern char *UTIL_VarArgs(char *format, ...);
extern void UTIL_LogPrintf(const char *fmt, ...);
