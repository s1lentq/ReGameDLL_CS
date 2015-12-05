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

#ifndef SOUND_H
#define SOUND_H
#ifdef _WIN32
#pragma once
#endif

#define CSENTENCEG_MAX		200			// max number of sentence groups
#define CSENTENCE_LRU_MAX	32			// max number of elements per sentence group
#define CDPVPRESETMAX		27

// spawnflags
#define AMBIENT_SOUND_STATIC			0	// medium radius attenuation
#define AMBIENT_SOUND_EVERYWHERE		1
#define AMBIENT_SOUND_SMALLRADIUS		2
#define AMBIENT_SOUND_MEDIUMRADIUS		4
#define AMBIENT_SOUND_LARGERADIUS		8
#define AMBIENT_SOUND_START_SILENT		16
#define AMBIENT_SOUND_NOT_LOOPING		32

#define ANNOUNCE_MINUTES_MIN			0.25
#define ANNOUNCE_MINUTES_MAX			2.25

#define SPEAKER_START_SILENT			1	// wait for trigger 'on' to start announcements

#define	LFO_SQUARE				1	// square
#define LFO_TRIANGLE				2	// triangle
#define LFO_RANDOM				3	// random

// group of related sentences
typedef struct
{
	char szgroupname[16];
	int count;
	unsigned char rgblru[ CSENTENCE_LRU_MAX ];

} sentenceg;
/* size: 52, cachelines: 1, members: 3 */

// runtime pitch shift and volume fadein/out structure

// NOTE: IF YOU CHANGE THIS STRUCT YOU MUST CHANGE THE SAVE/RESTORE VERSION NUMBER
// SEE BELOW (in the typedescription for the class)
typedef struct dynpitchvol
{
	// NOTE: do not change the order of these parameters
	// NOTE: unless you also change order of rgdpvpreset array elements!
	int preset;

	int pitchrun;		// pitch shift % when sound is running 0 - 255
	int pitchstart;		// pitch shift % when sound stops or starts 0 - 255
	int spinup;		// spinup time 0 - 100
	int spindown;		// spindown time 0 - 100

	int volrun;		// volume change % when sound is running 0 - 10
	int volstart;		// volume change % when sound stops or starts 0 - 10
	int fadein;		// volume fade in time 0 - 100
	int fadeout;		// volume fade out time 0 - 100

	// Low Frequency Oscillator
	int lfotype;		// 0) off 1) square 2) triangle 3) random
	int lforate;		// 0 - 1000, how fast lfo osciallates

	int lfomodpitch;	// 0-100 mod of current pitch. 0 is off.
	int lfomodvol;		// 0-100 mod of current volume. 0 is off.

	int cspinup;		// each trigger hit increments counter and spinup pitch

	int cspincount;
	int pitch;
	int spinupsav;
	int spindownsav;
	int pitchfrac;
	int vol;
	int fadeinsav;
	int fadeoutsav;
	int volfrac;
	int lfofrac;
	int lfomult;

} dynpitchvol_t;
/* size: 100, cachelines: 2, members: 25 */

/* <170b59> ../cstrike/dlls/sound.cpp:117 */
class CAmbientGeneric: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void Restart(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Restart_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT RampThink(void);
	void InitModulationParms(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[4];

	float m_flAttenuation;	// attenuation value
	dynpitchvol_t m_dpv;
	BOOL m_fActive;		// only TRUE when the entity is playing a looping sound
	BOOL m_fLooping;	// TRUE when the sound played will loop

};/* size: 264, cachelines: 5, members: 6 */

/* <170bc2> ../cstrike/dlls/sound.cpp:875 */
class CEnvSound: public CPointEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Think(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Think_(void);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

	float m_flRadius;
	float m_flRoomtype;

};/* size: 160, cachelines: 3, members: 4 */

/* <170ced> ../cstrike/dlls/sound.cpp:1867 */
class CSpeaker: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT SpeakerThink(void);
public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	int m_preset;		// preset number

};/* size: 156, cachelines: 3, members: 3 */

BOOL FEnvSoundInRange(entvars_t *pev, entvars_t *pevTarget, float *pflRange);
void USENTENCEG_InitLRU(unsigned char *plru, int count);
int USENTENCEG_PickSequential(int isentenceg, char *szfound, int ipick, int freset);
int USENTENCEG_Pick(int isentenceg, char *szfound);
int SENTENCEG_GetIndex(const char *szgroupname);
int SENTENCEG_PlayRndI(edict_t *entity, int isentenceg, float volume, float attenuation, int flags, int pitch);
int SENTENCEG_PlayRndSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch);
int SENTENCEG_PlaySequentialSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch, int ipick, int freset);
NOXREF void SENTENCEG_Stop(edict_t *entity, int isentenceg, int ipick);
void SENTENCEG_Init(void);
int SENTENCEG_Lookup(const char *sample, char *sentencenum);
void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch);
void EMIT_SOUND_SUIT(edict_t *entity, const char *sample);
void EMIT_GROUPID_SUIT(edict_t *entity, int isentenceg);
NOXREF void EMIT_GROUPNAME_SUIT(edict_t *entity, const char *groupname);
char *memfgets(byte *pMemFile, int fileSize, int &filePos, char *pBuffer, int bufferSize);
void TEXTURETYPE_Init(void);
char TEXTURETYPE_Find(char *name);
float TEXTURETYPE_PlaySound(TraceResult *ptr, Vector vecSrc, Vector vecEnd, int iBulletType);

#ifdef HOOK_GAMEDLL

#define gszallsentencenames (*pgszallsentencenames)
#define rgsentenceg (*prgsentenceg)
#define fSentencesInit (*pfSentencesInit)
#define gcallsentences (*pgcallsentences)
#define rgdpvpreset (*prgdpvpreset)

#endif // HOOK_GAMEDLL

extern char gszallsentencenames[ CVOXFILESENTENCEMAX ][ CBSENTENCENAME_MAX ];
extern sentenceg rgsentenceg[ CSENTENCEG_MAX ];
extern int fSentencesInit;
extern int gcallsentences;
extern dynpitchvol_t rgdpvpreset[CDPVPRESETMAX];

#ifdef HOOK_GAMEDLL

// linked objects
C_DLLEXPORT void ambient_generic(entvars_t *pev);
C_DLLEXPORT void env_sound(entvars_t *pev);
C_DLLEXPORT void speaker(entvars_t *pev);

#endif // HOOK_GAMEDLL

#endif // SOUND_H
