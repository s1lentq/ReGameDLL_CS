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

#ifndef UTIL_H
#define UTIL_H
#ifdef _WIN32
#pragma once
#endif

#include "activity.h"

#define _LOG_TRACE\
	static int iNumPassed = 0;\
	printf2(__FUNCTION__":: iNumPassed - %d", iNumPassed++);

#define _LOG_TRACE2\
	static int iNumPassedt = 0;\
	printf2(__FUNCTION__":: iNumPassed - %d", iNumPassedt++);\
	_logf(__FUNCTION__":: iNumPassed - %d", iNumPassedt++);

// Makes these more explicit, and easier to find
#ifdef HOOK_GAMEDLL

#define FILE_GLOBAL static
#define DLL_GLOBAL

#else

#define FILE_GLOBAL
#define DLL_GLOBAL

#endif // HOOK_GAMEDLL

#define eoNullEntity		0	// Testing the three types of "entity" for nullity
#define iStringNull		0	// Testing strings for nullity

#define cchMapNameMost		32

#define CBSENTENCENAME_MAX	16
#define CVOXFILESENTENCEMAX	1536	// max number of sentences in game. NOTE: this must match CVOXFILESENTENCEMAX in engine\sound.h!!!

#define GROUP_OP_AND		0
#define GROUP_OP_NAND		1

extern globalvars_t *gpGlobals;

#define STRING(offset)		((const char *)(gpGlobals->pStringBase + (unsigned int)(offset)))
#define MAKE_STRING(str)	((uint64_t)(str) - (uint64_t)(STRING(0)))

// Dot products for view cone checking

#define VIEW_FIELD_FULL		-1.0		// +-180 degrees
#define VIEW_FIELD_WIDE		-0.7		// +-135 degrees 0.1 // +-85 degrees, used for full FOV checks
#define VIEW_FIELD_NARROW	0.7		// +-45 degrees, more narrow check used to set up ranged attacks
#define VIEW_FIELD_ULTRA_NARROW	0.9		// +-25 degrees, more narrow check used to set up ranged attacks

#define SND_SPAWNING		(1<<8)		// duplicated in protocol.h we're spawing, used in some cases for ambients
#define SND_STOP		(1<<5)		// duplicated in protocol.h stop sound
#define SND_CHANGE_VOL		(1<<6)		// duplicated in protocol.h change sound vol
#define SND_CHANGE_PITCH	(1<<7)		// duplicated in protocol.h change sound pitch

#define DONT_BLEED		-1
#define BLOOD_COLOR_RED		(byte)247
#define BLOOD_COLOR_YELLOW	(byte)195
#define BLOOD_COLOR_GREEN	BLOOD_COLOR_YELLOW

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

#define SF_TRIG_PUSH_ONCE		1

// func_rotating
#define SF_BRUSH_ROTATE_Y_AXIS		0
#define SF_BRUSH_ROTATE_INSTANT		1
#define SF_BRUSH_ROTATE_BACKWARDS	2
#define SF_BRUSH_ROTATE_Z_AXIS		4
#define SF_BRUSH_ROTATE_X_AXIS		8
#define SF_PENDULUM_AUTO_RETURN		16
#define	SF_PENDULUM_PASSABLE		32

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

#define PLAYBACK_EVENT(flags, who, index)\
		PLAYBACK_EVENT_FULL(flags, who, index, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0)

#define PLAYBACK_EVENT_DELAY(flags, who, index, delay)\
		PLAYBACK_EVENT_FULL(flags, who, index, delay, (float *)&g_vecZero, (float *)&g_vecZero, 0.0, 0.0, 0, 0, 0, 0)

#ifdef HOOK_GAMEDLL

// prefix _
#define __MAKE_VHOOK(fname)\
	fname##_
#else

#define __MAKE_VHOOK(fname)\
	fname

#endif // HOOK_GAMEDLL

#define LINK_ENTITY_TO_CLASS(mapClassName, DLLClassName)\
	C_DLLEXPORT void mapClassName(entvars_t *pev);\
	void mapClassName(entvars_t *pev)\
	{\
		GetClassPtr((DLLClassName *)pev);\
	}

typedef enum
{
	ignore_monsters = 1,
	dont_ignore_monsters = 0,
	missile = 2

} IGNORE_MONSTERS;

typedef enum
{
	ignore_glass = 1,
	dont_ignore_glass = 0

} IGNORE_GLASS;

enum
{
	point_hull = 0,
	human_hull = 1,
	large_hull = 2,
	head_hull = 3
};

typedef enum
{
	MONSTERSTATE_NONE = 0,
	MONSTERSTATE_IDLE,
	MONSTERSTATE_COMBAT,
	MONSTERSTATE_ALERT,
	MONSTERSTATE_HUNT,
	MONSTERSTATE_PRONE,
	MONSTERSTATE_SCRIPT,
	MONSTERSTATE_PLAYDEAD,
	MONSTERSTATE_DEAD

} MONSTERSTATE;

typedef struct hudtextparms_s
{
	float x;
	float y;
	int effect;
	byte r1,g1,b1,a1;
	byte r2,g2,b2,a2;
	float fadeinTime;
	float fadeoutTime;
	float holdTime;
	float fxTime;
	int channel;

} hudtextparms_t;
/* size: 40, cachelines: 1, members: 16 */

class UTIL_GroupTrace
{
public:
	UTIL_GroupTrace(int groupmask, int op);
	~UTIL_GroupTrace(void);
private:
	int m_oldgroupmask;
	int m_oldgroupop;

};/* size: 8, cachelines: 1, members: 2 */

/* <5da42> ../cstrike/dlls/util.h:67 */
inline void MAKE_STRING_CLASS(const char *str, entvars_t *pev)
{
	pev->classname = (string_t)MAKE_STRING(str);
}

/* <b5829> ../cstrike/dlls/util.h:80 */
inline edict_t *FIND_ENTITY_BY_CLASSNAME(edict_t *entStart, const char *pszName)
{
	return FIND_ENTITY_BY_STRING(entStart, "classname", pszName);
}

/* <2468f> ../cstrike/dlls/util.h:85 */
inline edict_t *FIND_ENTITY_BY_TARGETNAME(edict_t *entStart, const char *pszName)
{
	return FIND_ENTITY_BY_STRING(entStart, "targetname", pszName);
}

/* <4299> ../cstrike/dlls/util.h:157 */
inline edict_t *ENT(const entvars_t *pev)
{
	return pev->pContainingEntity;
}

/* <431e6> ../cstrike/dlls/util.h:159 */
inline edict_t *ENT(EOFFSET eoffset)
{
	return (*g_engfuncs.pfnPEntityOfEntOffset)(eoffset);
}

/* <244a7> ../cstrike/dlls/util.h:162 */
inline EOFFSET OFFSET(const edict_t *pent)
{
	return (*g_engfuncs.pfnEntOffsetOfPEntity)(pent);
}

/* <543b7> ../cstrike/dlls/util.h:165 */
inline EOFFSET OFFSET(const entvars_t *pev)
{
	return OFFSET(ENT(pev));
}

/* <4631> ../cstrike/dlls/util.h:180 */
inline entvars_t *VARS(edict_t *pent)
{
	if (!pent)
		return NULL;

	return &pent->v;
}

/* <483c6> ../cstrike/dlls/util.h:184 */
inline entvars_t *VARS(EOFFSET eoffset)
{
	return VARS(ENT(eoffset));
}

/* <2ee03> ../cstrike/dlls/util.h:189 */
inline int ENTINDEX(edict_t *pEdict)
{
	return (*g_engfuncs.pfnIndexOfEdict)(pEdict);
}

/* <14e46e> ../cstrike/dlls/util.h:190 */
inline edict_t *INDEXENT(int iEdictNum)
{
	return (*g_engfuncs.pfnPEntityOfEntIndex)(iEdictNum);
}

/* <15a45d> ../cstrike/dlls/util.h:193 */
inline void MESSAGE_BEGIN(int msg_dest, int msg_type, const float *pOrigin, entvars_t *ent)
{
	MESSAGE_BEGIN(msg_dest, msg_type, pOrigin, ENT(ent));
}

/* <244c4> ../cstrike/dlls/util.h:197 */
inline BOOL FNullEnt(EOFFSET eoffset)
{
	return (eoffset == 0);
}

/* <213e7> ../cstrike/dlls/util.h:198 */
inline BOOL FNullEnt(entvars_t *pev)
{
	return (pev == NULL || FNullEnt(OFFSET(pev)));
}

/* <432b5> ../cstrike/dlls/util.h:199 */
inline BOOL FNullEnt(const edict_t *pent)
{
	return (pent == NULL || FNullEnt(OFFSET(pent)));
}

/* <1c1cb> ../cstrike/dlls/util.h:203 */
inline BOOL FStringNull(int iString)
{
	return (iString == iStringNull);
}

/* <42e8> ../cstrike/dlls/util.h:246 */
inline BOOL FStrEq(const char *sz1, const char *sz2)
{
	return (Q_strcmp(sz1, sz2) == 0);
}

/* <245ce> ../cstrike/dlls/util.h:250 */
inline BOOL FClassnameIs(entvars_t *pev, const char *szClassname)
{
	return FStrEq(STRING(pev->classname), szClassname);
}

/* <249a6> ../cstrike/dlls/util.h:265 */
inline BOOL FClassnameIs(edict_t *pent, const char *szClassname)
{
	//TODO: check is null?
	return FStrEq(STRING(VARS(pent)->classname), szClassname);
}

/* <8c49f> ../cstrike/dlls/util.h:282 */
inline void UTIL_MakeVectorsPrivate(Vector vecAngles, float *p_vForward, float *p_vRight, float *p_vUp)
{
	g_engfuncs.pfnAngleVectors(vecAngles, p_vForward, p_vRight, p_vUp);
}

extern void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch);

/* <4310> ../cstrike/dlls/util.h:570 */
inline void EMIT_SOUND(edict_t *entity, int channel, const char *sample, float volume, float attenuation)
{
	EMIT_SOUND_DYN(entity, channel, sample, volume, attenuation, 0, PITCH_NORM);
}

/* <6862b> ../cstrike/dlls/util.h:575 */
inline void STOP_SOUND(edict_t *entity, int channel, const char *sample)
{
	EMIT_SOUND_DYN(entity, channel, sample, 0, 0, SND_STOP, PITCH_NORM);
}

#ifdef HOOK_GAMEDLL

#define gEntvarsDescription (*pgEntvarsDescription)
#define seed_table (*pseed_table)
#define glSeed (*pglSeed)
#define g_groupmask (*pg_groupmask)
#define g_groupop (*pg_groupop)
#define gSizes (*pgSizes)

#endif // HOOK_GAMEDLL

extern TYPEDESCRIPTION gEntvarsDescription[86];
extern unsigned int seed_table[256];
extern unsigned int glSeed;

extern int g_groupmask;
extern int g_groupop;
extern const int gSizes[18];

float UTIL_WeaponTimeBase(void);
unsigned int U_Random(void);
void U_Srand(unsigned int seed);
int UTIL_SharedRandomLong(unsigned int seed, int low, int high);
float UTIL_SharedRandomFloat(unsigned int seed, float low, float high);
NOXREF void UTIL_ParametricRocket(entvars_t *pev, Vector vecOrigin, Vector vecAngles, edict_t *owner);
void UTIL_SetGroupTrace(int groupmask, int op);
void UTIL_UnsetGroupTrace(void);
NOXREF BOOL UTIL_GetNextBestWeapon(class CBasePlayer *pPlayer, class CBasePlayerItem *pCurrentWeapon);
NOXREF float UTIL_AngleMod(float a);
NOXREF float UTIL_AngleDiff(float destAngle, float srcAngle);
Vector UTIL_VecToAngles(const Vector &vec);
NOXREF void UTIL_MoveToOrigin(edict_t *pent, const Vector &vecGoal, float flDist, int iMoveType);
int UTIL_EntitiesInBox(CBaseEntity **pList, int listMax, const Vector &mins, const Vector &maxs, int flagMask);
NOXREF int UTIL_MonstersInSphere(CBaseEntity **pList, int listMax, const Vector &center, float radius);
CBaseEntity *UTIL_FindEntityInSphere(CBaseEntity *pStartEntity, const Vector &vecCenter, float flRadius);
CBaseEntity *UTIL_FindEntityByString_Old(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue);
CBaseEntity *UTIL_FindEntityByString(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue);
CBaseEntity *UTIL_FindEntityByClassname(CBaseEntity *pStartEntity, const char *szName);
CBaseEntity *UTIL_FindEntityByTargetname(CBaseEntity *pStartEntity, const char *szName);
NOXREF CBaseEntity *UTIL_FindEntityGeneric(const char *szWhatever, const Vector &vecSrc, float flRadius);
CBaseEntity *UTIL_PlayerByIndex(int playerIndex);
void UTIL_MakeVectors(const Vector &vecAngles);
void UTIL_MakeAimVectors(const Vector &vecAngles);
void UTIL_MakeInvVectors(const Vector &vec, globalvars_t *pgv);
void UTIL_EmitAmbientSound(edict_t *entity, const Vector &vecOrigin, const char *samp, float vol, float attenuation, int fFlags, int pitch);
unsigned short FixedUnsigned16(float value, float scale);
short FixedSigned16(float value, float scale);
void UTIL_ScreenShake(const Vector &center, float amplitude, float frequency, float duration, float radius);
NOXREF void UTIL_ScreenShakeAll(const Vector &center, float amplitude, float frequency, float duration);
void UTIL_ScreenFadeBuild(ScreenFade &fade, const Vector &color, float fadeTime, float fadeHold, int alpha, int flags);
void UTIL_ScreenFadeWrite(const ScreenFade &fade, CBaseEntity *pEntity);
void UTIL_ScreenFadeAll(const Vector &color, float fadeTime, float fadeHold, int alpha, int flags);
void UTIL_ScreenFade(CBaseEntity *pEntity, const Vector &color, float fadeTime, float fadeHold = 0.0f, int alpha = 0, int flags = 0);
void UTIL_HudMessage(CBaseEntity *pEntity, const hudtextparms_t &textparms, const char *pMessage);
void UTIL_HudMessageAll(const hudtextparms_t &textparms, const char *pMessage);
void UTIL_ClientPrintAll(int msg_dest, const char *msg_name, const char *param1 = NULL, const char *param2 = NULL, const char *param3 = NULL, const char *param4 = NULL);
void ClientPrint(entvars_t *client, int msg_dest, const char *msg_name, const char *param1 = NULL, const char *param2 = NULL, const char *param3 = NULL, const char *param4 = NULL);
NOXREF void UTIL_SayText(const char *pText, CBaseEntity *pEntity);
void UTIL_SayTextAll(const char *pText, CBaseEntity *pEntity);
char *UTIL_dtos1(int d);
char *UTIL_dtos2(int d);
NOXREF char *UTIL_dtos3(int d);
NOXREF char *UTIL_dtos4(int d);
void UTIL_ShowMessageArgs(const char *pString, CBaseEntity *pPlayer, CUtlVector<char*> *args, bool isHint = false);
void UTIL_ShowMessage(const char *pString, CBaseEntity *pEntity, bool isHint = false);
void UTIL_ShowMessageAll(const char *pString, bool isHint = false);
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr);
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t *pentIgnore, TraceResult *ptr);
void UTIL_TraceHull(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, int hullNumber, edict_t *pentIgnore, TraceResult *ptr);
void UTIL_TraceModel(const Vector &vecStart, const Vector &vecEnd, int hullNumber, edict_t *pentModel, TraceResult *ptr);
NOXREF TraceResult UTIL_GetGlobalTrace(void);
void UTIL_SetSize(entvars_t *pev, const Vector &vecMin, const Vector &vecMax);
float UTIL_VecToYaw(const Vector &vec);
void UTIL_SetOrigin(entvars_t *pev, const Vector &vecOrigin);
NOXREF void UTIL_ParticleEffect(const Vector &vecOrigin, const Vector &vecDirection, ULONG ulColor, ULONG ulCount);
float UTIL_Approach(float target, float value, float speed);
float_precision UTIL_ApproachAngle(float target, float value, float speed);
float_precision UTIL_AngleDistance(float next, float cur);
float UTIL_SplineFraction(float value, float scale);
char *UTIL_VarArgs(char *format, ...);
NOXREF Vector UTIL_GetAimVector(edict_t *pent, float flSpeed);
int UTIL_IsMasterTriggered(string_t sMaster, CBaseEntity *pActivator);
BOOL UTIL_ShouldShowBlood(int color);
int UTIL_PointContents(const Vector &vec);
void UTIL_BloodStream(const Vector &origin, const Vector &direction, int color, int amount);
void UTIL_BloodDrips(const Vector &origin, const Vector &direction, int color, int amount);
Vector UTIL_RandomBloodVector(void);
void UTIL_BloodDecalTrace(TraceResult *pTrace, int bloodColor);
void UTIL_DecalTrace(TraceResult *pTrace, int decalNumber);
void UTIL_PlayerDecalTrace(TraceResult *pTrace, int playernum, int decalNumber, BOOL bIsCustom);
void UTIL_GunshotDecalTrace(TraceResult *pTrace, int decalNumber, bool ClientOnly, entvars_t *pShooter);
void UTIL_Sparks(const Vector &position);
void UTIL_Ricochet(const Vector &position, float scale);
BOOL UTIL_TeamsMatch(const char *pTeamName1, const char *pTeamName2);
void UTIL_StringToVector(float *pVector, const char *pString);
void UTIL_StringToIntArray(int *pVector, int count, const char *pString);
Vector UTIL_ClampVectorToBox(const Vector &input, const Vector &clampSize);
float UTIL_WaterLevel(const Vector &position, float minz, float maxz);
void UTIL_Bubbles(Vector mins, Vector maxs, int count);
void UTIL_BubbleTrail(Vector from, Vector to, int count);
void UTIL_Remove(CBaseEntity *pEntity);
NOXREF BOOL UTIL_IsValidEntity(edict_t *pent);
void UTIL_PrecacheOther(const char *szClassname);
void UTIL_LogPrintf(char *fmt, ...);
NOXREF float UTIL_DotPoints(const Vector &vecSrc, const Vector &vecCheck, const Vector &vecDir);
void UTIL_StripToken(const char *pKey, char *pDest);
void EntvarsKeyvalue(entvars_t *pev, KeyValueData *pkvd);
char UTIL_TextureHit(TraceResult *ptr, Vector vecSrc, Vector vecEnd);
NOXREF int GetPlayerTeam(int index);
bool UTIL_IsGame(const char *gameName);
float_precision UTIL_GetPlayerGaitYaw(int playerIndex);

/*
* Declared for function overload
*/
#ifdef HOOK_GAMEDLL

typedef void (*UTIL_TRACELINE_IGNORE)(const Vector &, const Vector &, IGNORE_MONSTERS, edict_t *, TraceResult *);
typedef void (*UTIL_TRACELINE_IGNORE_GLASS)(const Vector &, const Vector &, IGNORE_MONSTERS, IGNORE_GLASS, edict_t *, TraceResult *);

typedef int (CSaveRestoreBuffer::*ENTITYINDEX_CBASE)(CBaseEntity *);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_ENTVARS)(entvars_t *);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_EOFFSET)(EOFFSET);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_EDICT)(edict_t *);

typedef void (CSave::*WRITESTRING_)(const char *,const char *);
typedef void (CSave::*WRITESTRING_COUNT)(const char *,const int *,int);
typedef void (CSave::*WRITEVECTOR_)(const char *,const Vector &);
typedef void (CSave::*WRITEVECTOR_COUNT)(const char *,const float *,int);
typedef void (CSave::*WRITEPOSITIONVECTOR_)(const char *,const Vector &);
typedef void (CSave::*WRITEPOSITIONVECTOR_COUNT)(const char *,const float *,int);

typedef int (CSaveRestoreBuffer::*CSAVERESTOREBUFFER_VOID)(const char *,const Vector &);
typedef int (CSaveRestoreBuffer::*CSAVERESTOREBUFFER_POINTER)(const char *,const float *,int);

#endif // HOOK_GAMEDLL

#if 1

extern void *addr_orig;
extern char patchByte[5];
extern char patchByteOriginal[5];

#endif

#endif // UTIL_H
