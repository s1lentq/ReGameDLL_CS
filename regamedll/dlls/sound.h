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

#define CSENTENCEG_MAX		200		// max number of sentence groups
#define CSENTENCE_LRU_MAX	32

typedef struct
{
	char szgroupname[16];
	int count;
	unsigned char rgblru[ CSENTENCE_LRU_MAX ];

} sentenceg;
/* size: 52, cachelines: 1, members: 3 */

NOBODY BOOL FEnvSoundInRange(entvars_t *pev, entvars_t *pevTarget, float *pflRange);
void USENTENCEG_InitLRU(unsigned char *plru, int count);
int USENTENCEG_PickSequential(int isentenceg, char *szfound, int ipick, int freset);
int USENTENCEG_Pick(int isentenceg, char *szfound);
NOXREF int SENTENCEG_GetIndex(const char *szgroupname);
NOXREF int SENTENCEG_PlayRndI(edict_t *entity, int isentenceg, float volume, float attenuation, int flags, int pitch);
NOXREF int SENTENCEG_PlayRndSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch);
int SENTENCEG_PlaySequentialSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch, int ipick, int freset);
NOXREF void SENTENCEG_Stop(edict_t *entity, int isentenceg, int ipick);
void SENTENCEG_Init(void);
int SENTENCEG_Lookup(const char *sample, char *sentencenum);
void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch);
void EMIT_SOUND_SUIT(edict_t *entity, const char *sample);
void EMIT_GROUPID_SUIT(edict_t *entity, int isentenceg);
NOXREF void EMIT_GROUPNAME_SUIT(edict_t *entity, const char *groupname);
char *memfgets(byte *pMemFile, int fileSize, int &filePos, char *pBuffer, int bufferSize);
NOBODY void TEXTURETYPE_Init(void);
char TEXTURETYPE_Find(char *name);
NOBODY float TEXTURETYPE_PlaySound(TraceResult *ptr, Vector vecSrc, Vector vecEnd, int iBulletType);

#ifdef HOOK_GAMEDLL

#define gszallsentencenames (*pgszallsentencenames)
#define rgsentenceg (*prgsentenceg)
#define fSentencesInit (*pfSentencesInit)
#define gcallsentences (*pgcallsentences)

#endif // HOOK_GAMEDLL

extern char gszallsentencenames[ CVOXFILESENTENCEMAX ][ CBSENTENCENAME_MAX ];
extern sentenceg rgsentenceg[ CSENTENCEG_MAX ];
extern int fSentencesInit;
extern int gcallsentences;

#endif // SOUND_H
