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

const int MAX_SENTENCE_NAME      = 16;
const int MAX_SENTENCE_VOXFILE   = 1536;	// Max number of sentences in game. NOTE: this must match CVOXFILESENTENCEMAX in engine\sound.h

const int MAX_SENTENCE_GROUPS    = 200;		// Max number of sentence groups
const int MAX_SENTENCE_LRU       = 32;		// Max number of elements per sentence group
const int MAX_SENTENCE_DPV_RESET = 27;		// Max number of dynamic pitch volumes

const float MAX_ANNOUNCE_MINS    = 2.25f;
const float MIN_ANNOUNCE_MINS    = 0.25f;

enum LowFreqOsc : int
{
	LFO_OFF = 0,
	LFO_SQUARE,		// Square
	LFO_TRIANGLE,	// Triangle
	LFO_RANDOM,		// Random
};

// group of related sentences
struct sentenceg
{
	char szgroupname[16];
	int count;
	unsigned char rgblru[MAX_SENTENCE_LRU];
};

// runtime pitch shift and volume fadein/out structure

// NOTE: IF YOU CHANGE THIS STRUCT YOU MUST CHANGE THE SAVE/RESTORE VERSION NUMBER
// SEE BELOW (in the typedescription for the class)
typedef struct dynpitchvol
{
	// NOTE: do not change the order of these parameters
	// NOTE: unless you also change order of rgdpvpreset array elements!
	int preset;

	int pitchrun;		// Pitch shift % when sound is running 0 - 255
	int pitchstart;		// Pitch shift % when sound stops or starts 0 - 255
	int spinup;			// Spinup time 0 - 100
	int spindown;		// Spindown time 0 - 100

	int volrun;			// Volume change % when sound is running 0 - 10
	int volstart;		// Volume change % when sound stops or starts 0 - 10
	int fadein;			// Volume fade in time 0 - 100
	int fadeout;		// Volume fade out time 0 - 100

	// Low Frequency Oscillator
	LowFreqOsc lfotype;	// 0) off 1) square 2) triangle 3) random
	int lforate;		// 0 - 1000, how fast lfo osciallates

	int lfomodpitch;	// 0-100 mod of current pitch. 0 is off.
	int lfomodvol;		// 0-100 mod of current volume. 0 is off.

	int cspinup;		// Each trigger hit increments counter and spinup pitch

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

#define SF_AMBIENT_SOUND_STATIC         0 // Medium radius attenuation
#define SF_AMBIENT_SOUND_EVERYWHERE     BIT(0)
#define SF_AMBIENT_SOUND_SMALLRADIUS    BIT(1)
#define SF_AMBIENT_SOUND_MEDIUMRADIUS   BIT(2)
#define SF_AMBIENT_SOUND_LARGERADIUS    BIT(3)
#define SF_AMBIENT_SOUND_START_SILENT   BIT(4)
#define SF_AMBIENT_SOUND_NOT_LOOPING    BIT(5)

class CAmbientGeneric: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void Restart();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

public:
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT RampThink();
	void InitModulationParms();

public:
	static TYPEDESCRIPTION m_SaveData[];

	float m_flAttenuation;	// Attenuation value
	dynpitchvol_t m_dpv;
	BOOL m_fActive;			// Only TRUE when the entity is playing a looping sound
	BOOL m_fLooping;		// TRUE when the sound played will loop
};

class CEnvSound: public CPointEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Think();

public:
	static TYPEDESCRIPTION m_SaveData[];

	float m_flRadius;
	float m_flRoomtype;
};

#define SF_SPEAKER_START_SILENT	BIT(0) // Wait for trigger 'on' to start announcements

class CSpeaker: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }

public:
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT SpeakerThink();

public:
	static TYPEDESCRIPTION m_SaveData[];

	int m_preset; // Preset number
};

BOOL FEnvSoundInRange(entvars_t *pev, entvars_t *pevTarget, float *pflRange);
void USENTENCEG_InitLRU(unsigned char *plru, int count);
int USENTENCEG_PickSequential(int isentenceg, char *szfound, int ipick, int freset);
int USENTENCEG_Pick(int isentenceg, char *szfound);
int SENTENCEG_GetIndex(const char *szgroupname);
int SENTENCEG_PlayRndI(edict_t *entity, int isentenceg, float volume, float attenuation, int flags, int pitch);
int SENTENCEG_PlayRndSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch);
int SENTENCEG_PlaySequentialSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch, int ipick, int freset);
void SENTENCEG_Stop(edict_t *entity, int isentenceg, int ipick);
void SENTENCEG_Init();
int SENTENCEG_Lookup(const char *sample, char *sentencenum);
void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch);
void EMIT_SOUND_SUIT(edict_t *entity, const char *sample);
void EMIT_GROUPID_SUIT(edict_t *entity, int isentenceg);
void EMIT_GROUPNAME_SUIT(edict_t *entity, const char *groupname);
char *memfgets(byte *pMemFile, int fileSize, int &filePos, char *pBuffer, int bufferSize);
void TEXTURETYPE_Init();
char TEXTURETYPE_Find(char *name);
float TEXTURETYPE_PlaySound(TraceResult *ptr, Vector vecSrc, Vector vecEnd, int iBulletType);

extern char gszallsentencenames[MAX_SENTENCE_VOXFILE][MAX_SENTENCE_NAME];
extern int gcTextures;
