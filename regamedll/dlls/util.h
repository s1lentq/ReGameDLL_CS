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

#include "shake.h"
#include "activity.h"
#include "enginecallback.h"
#include "utlvector.h"

#define _LOG_TRACE\
	static int iNumPassed = 0;\
	printf2("%s:: iNumPassed - %d", __FUNCTION__, iNumPassed++);

#define _LOG_TRACE2\
	static int iNumPassedt = 0;\
	printf2("%s:: iNumPassed - %d", __FUNCTION__, iNumPassedt++);\
	_logf("%s:: iNumPassed - %d", __FUNCTION__, iNumPassedt++);

// Makes these more explicit, and easier to find
#ifdef HOOK_GAMEDLL

#define STD_LIST list_vs6		// use STL containers of the old version from Visual Studio 6.0 sp6
#define STD_VECTOR vector_vs6

#define FILE_GLOBAL static
#define DLL_GLOBAL

#else

#define STD_LIST list
#define STD_VECTOR vector

#define FILE_GLOBAL
#define DLL_GLOBAL

#endif

#define eoNullEntity		0	// Testing the three types of "entity" for nullity
#define iStringNull		0	// Testing strings for nullity

#define cchMapNameMost		32

#define CBSENTENCENAME_MAX	16
#define CVOXFILESENTENCEMAX	1536	// max number of sentences in game. NOTE: this must match CVOXFILESENTENCEMAX in engine\sound.h

#define GROUP_OP_AND		0
#define GROUP_OP_NAND		1

extern globalvars_t *gpGlobals;

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

#if !defined(HOOK_GAMEDLL)
#define __MAKE_VHOOK(fname)\
	fname
#endif // !defined(HOOK_GAMEDLL) && defined(REGAMEDLL_API)

#define LINK_ENTITY_TO_CLASS(mapClassName, DLLClassName, DLLClassWrapName)\
	C_DLLEXPORT void EXT_FUNC mapClassName(entvars_t *pev);\
	void mapClassName(entvars_t *pev)\
	{\
		GetClassPtr<DLLClassWrapName>((DLLClassName *)pev);\
	}

class UTIL_GroupTrace
{
public:
	UTIL_GroupTrace(int groupmask, int op);
	~UTIL_GroupTrace();
private:
	int m_oldgroupmask;
	int m_oldgroupop;
};

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
inline BOOL FStrEq(const char *sz1, const char *sz2) { return (Q_strcmp(sz1, sz2) == 0); }
inline BOOL FClassnameIs(entvars_t *pev, const char *szClassname) { return FStrEq(STRING(pev->classname), szClassname); }
inline BOOL FClassnameIs(edict_t *pent, const char *szClassname) { return FStrEq(STRING(VARS(pent)->classname), szClassname); }
inline void UTIL_MakeVectorsPrivate(Vector vecAngles, float *p_vForward, float *p_vRight, float *p_vUp) { g_engfuncs.pfnAngleVectors(vecAngles, p_vForward, p_vRight, p_vUp); }

extern void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch);

// NOTE: use EMIT_SOUND_DYN to set the pitch of a sound. Pitch of 100
// is no pitch shift.  Pitch > 100 up to 255 is a higher pitch, pitch < 100
// down to 1 is a lower pitch.   150 to 70 is the realistic range.
// EMIT_SOUND_DYN with pitch != 100 should be used sparingly, as it's not quite as
// fast as EMIT_SOUND (the pitchshift mixer is not native coded).
inline void EMIT_SOUND(edict_t *entity, int channel, const char *sample, float volume, float attenuation)
{
	EMIT_SOUND_DYN(entity, channel, sample, volume, attenuation, 0, PITCH_NORM);
}

inline void STOP_SOUND(edict_t *entity, int channel, const char *sample)
{
	EMIT_SOUND_DYN(entity, channel, sample, 0, 0, SND_STOP, PITCH_NORM);
}

class CBaseEntity;
class CBasePlayer;
class CBasePlayerItem;

float UTIL_WeaponTimeBase();
unsigned int U_Random();
void U_Srand(unsigned int seed);
int UTIL_SharedRandomLong(unsigned int seed, int low, int high);
float UTIL_SharedRandomFloat(unsigned int seed, float low, float high);
void UTIL_ParametricRocket(entvars_t *pev, Vector vecOrigin, Vector vecAngles, edict_t *owner);
void UTIL_SetGroupTrace(int groupmask, int op);
void UTIL_UnsetGroupTrace();
BOOL UTIL_GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon);
float UTIL_AngleMod(float a);
float UTIL_AngleDiff(float destAngle, float srcAngle);
Vector UTIL_VecToAngles(const Vector &vec);
void UTIL_MoveToOrigin(edict_t *pent, const Vector &vecGoal, float flDist, int iMoveType);
int UTIL_EntitiesInBox(CBaseEntity **pList, int listMax, const Vector &mins, const Vector &maxs, int flagMask);
int UTIL_MonstersInSphere(CBaseEntity **pList, int listMax, const Vector &center, float radius);
CBaseEntity *UTIL_FindEntityInSphere(CBaseEntity *pStartEntity, const Vector &vecCenter, float flRadius);
CBaseEntity *UTIL_FindEntityByString_Old(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue);
CBaseEntity *UTIL_FindEntityByString(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue);
CBaseEntity *UTIL_FindEntityByClassname(CBaseEntity *pStartEntity, const char *szName);
CBaseEntity *UTIL_FindEntityByTargetname(CBaseEntity *pStartEntity, const char *szName);
CBaseEntity *UTIL_FindEntityGeneric(const char *szWhatever, const Vector &vecSrc, float flRadius);
#ifndef REGAMEDLL_FIXES
CBasePlayer *UTIL_PlayerByIndex(int playerIndex);
#endif
void UTIL_MakeVectors(const Vector &vecAngles);
void UTIL_MakeAimVectors(const Vector &vecAngles);
void UTIL_MakeInvVectors(const Vector &vec, globalvars_t *pgv);
void UTIL_EmitAmbientSound(edict_t *entity, const Vector &vecOrigin, const char *samp, float vol, float attenuation, int fFlags, int pitch);
unsigned short FixedUnsigned16(float value, float scale);
short FixedSigned16(float value, float scale);
void UTIL_ScreenShake(const Vector &center, float amplitude, float frequency, float duration, float radius);
void UTIL_ScreenShakeAll(const Vector &center, float amplitude, float frequency, float duration);
void UTIL_ScreenFadeBuild(ScreenFade &fade, const Vector &color, float fadeTime, float fadeHold, int alpha, int flags);
void UTIL_ScreenFadeWrite(const ScreenFade &fade, CBaseEntity *pEntity);
void UTIL_ScreenFadeAll(const Vector &color, float fadeTime, float fadeHold, int alpha, int flags);
void UTIL_ScreenFade(CBaseEntity *pEntity, const Vector &color, float fadeTime, float fadeHold = 0.0f, int alpha = 0, int flags = 0);
void UTIL_HudMessage(CBaseEntity *pEntity, const hudtextparms_t &textparms, const char *pMessage);
void UTIL_HudMessageAll(const hudtextparms_t &textparms, const char *pMessage);
void UTIL_ClientPrintAll(int msg_dest, const char *msg_name, const char *param1 = NULL, const char *param2 = NULL, const char *param3 = NULL, const char *param4 = NULL);
void ClientPrint(entvars_t *client, int msg_dest, const char *msg_name, const char *param1 = NULL, const char *param2 = NULL, const char *param3 = NULL, const char *param4 = NULL);
void UTIL_SayText(const char *pText, CBaseEntity *pEntity);
void UTIL_SayTextAll(const char *pText, CBaseEntity *pEntity);
char *UTIL_dtos1(int d);
char *UTIL_dtos2(int d);
char *UTIL_dtos3(int d);
char *UTIL_dtos4(int d);
void UTIL_ShowMessageArgs(const char *pString, CBaseEntity *pPlayer, CUtlVector<char*> *args, bool isHint = false);
void UTIL_ShowMessage(const char *pString, CBaseEntity *pEntity, bool isHint = false);
void UTIL_ShowMessageAll(const char *pString, bool isHint = false);
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr);
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t *pentIgnore, TraceResult *ptr);
void UTIL_TraceHull(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, int hullNumber, edict_t *pentIgnore, TraceResult *ptr);
void UTIL_TraceModel(const Vector &vecStart, const Vector &vecEnd, int hullNumber, edict_t *pentModel, TraceResult *ptr);
TraceResult UTIL_GetGlobalTrace();
void UTIL_SetSize(entvars_t *pev, const Vector &vecMin, const Vector &vecMax);
float UTIL_VecToYaw(const Vector &vec);
void UTIL_SetOrigin(entvars_t *pev, const Vector &vecOrigin);
void UTIL_ParticleEffect(const Vector &vecOrigin, const Vector &vecDirection, ULONG ulColor, ULONG ulCount);
float UTIL_Approach(float target, float value, float speed);
float_precision UTIL_ApproachAngle(float target, float value, float speed);
float_precision UTIL_AngleDistance(float next, float cur);
float UTIL_SplineFraction(float value, float scale);
char *UTIL_VarArgs(char *format, ...);
Vector UTIL_GetAimVector(edict_t *pent, float flSpeed);
int UTIL_IsMasterTriggered(string_t sMaster, CBaseEntity *pActivator);
BOOL UTIL_ShouldShowBlood(int color);
int UTIL_PointContents(const Vector &vec);
void UTIL_BloodStream(const Vector &origin, const Vector &direction, int color, int amount);
void UTIL_BloodDrips(const Vector &origin, const Vector &direction, int color, int amount);
Vector UTIL_RandomBloodVector();
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
BOOL UTIL_IsValidEntity(edict_t *pent);
void UTIL_PrecacheOther(const char *szClassname);
void UTIL_RestartOther(const char *szClassname);
void UTIL_ResetEntities();
void UTIL_RemoveOther(const char *szClassname);
void UTIL_LogPrintf(const char *fmt, ...);
float UTIL_DotPoints(const Vector &vecSrc, const Vector &vecCheck, const Vector &vecDir);
void UTIL_StripToken(const char *pKey, char *pDest);
void EntvarsKeyvalue(entvars_t *pev, KeyValueData *pkvd);
char UTIL_TextureHit(TraceResult *ptr, Vector vecSrc, Vector vecEnd);
int GetPlayerTeam(int index);
bool UTIL_IsGame(const char *gameName);
float_precision UTIL_GetPlayerGaitYaw(int playerIndex);
int UTIL_ReadFlags(const char *c);
bool UTIL_AreBotsAllowed();
bool UTIL_AreHostagesImprov();
void MAKE_STRING_CLASS(const char *str, entvars_t *pev);
void NORETURN Sys_Error(const char *error, ...);

extern int g_groupmask;
extern int g_groupop;

#endif // UTIL_H
