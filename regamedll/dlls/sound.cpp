#include "precompiled.h"
#include "talkmonster.h"

#ifndef HOOK_GAMEDLL

UNTESTED dynpitchvol_t rgdpvpreset[27] =
{
	{ 1, 255, 75, 95, 95, 10, 1, 50, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 255, 85, 70, 88, 10, 1, 20, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 3, 255, 100, 50, 75, 10, 1, 10, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 100, 100, 0, 0, 10, 1, 90, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 100, 100, 0, 0, 10, 1, 80, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 6, 100, 100, 0, 0, 10, 1, 50, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 7, 100, 100, 0, 0, 5, 1, 40, 50, 1, 50, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 8, 100, 100, 0, 0, 5, 1, 40, 50, 1, 150, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 9, 100, 100, 0, 0, 5, 1, 40, 50, 1, 750, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 10, 128, 100, 50, 75, 10, 1, 30, 40, 2, 8, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 11, 128, 100, 50, 75, 10, 1, 30, 40, 2, 25, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 12, 128, 100, 50, 75, 10, 1, 30, 40, 2, 70, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 13, 50, 50, 0, 0, 10, 1, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 14, 70, 70, 0, 0, 10, 1, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 15, 90, 90, 0, 0, 10, 1, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 16, 120, 120, 0, 0, 10, 1, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 17, 180, 180, 0, 0, 10, 1, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 18, 255, 255, 0, 0, 10, 1, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 19, 200, 75, 90, 90, 10, 1, 50, 90, 2, 100, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 20, 255, 75, 97, 90, 10, 1, 50, 90, 1, 40, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 21, 100, 100, 0, 0, 10, 1, 30, 50, 3, 15, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 22, 160, 160, 0, 0, 10, 1, 50, 50, 3, 500, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 23, 255, 75, 88, 0, 10, 1, 40, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 24, 200, 20, 95, 70, 10, 1, 70, 70, 3, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 25, 180, 100, 50, 60, 10, 1, 40, 60, 2, 90, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 26, 60, 60, 0, 0, 10, 1, 40, 70, 3, 80, 20, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 27, 128, 90, 10, 10, 10, 1, 20, 40, 1, 5, 10, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int gcallsentences = 0;
int fSentencesInit = FALSE;

TYPEDESCRIPTION CAmbientGeneric::m_SaveData[] =
{
	DEFINE_FIELD(CAmbientGeneric, m_flAttenuation, FIELD_FLOAT),
	DEFINE_FIELD(CAmbientGeneric, m_fActive, FIELD_BOOLEAN),
	DEFINE_FIELD(CAmbientGeneric, m_fLooping, FIELD_BOOLEAN),
	DEFINE_ARRAY(CAmbientGeneric, m_dpv, FIELD_CHARACTER, sizeof(dynpitchvol_t)),
};

TYPEDESCRIPTION CEnvSound::m_SaveData[] =
{
	DEFINE_FIELD(CEnvSound, m_flRadius, FIELD_FLOAT),
	DEFINE_FIELD(CEnvSound, m_flRoomtype, FIELD_FLOAT),
};

TYPEDESCRIPTION CSpeaker::m_SaveData[] =
{
	DEFINE_FIELD(CSpeaker, m_preset, FIELD_INTEGER),
};

#else

//dynpitchvol_t rgdpvpreset[27]
int fSentencesInit;
int gcallsentences;

TYPEDESCRIPTION (*CAmbientGeneric::pm_SaveData)[4];
TYPEDESCRIPTION (*CEnvSound::pm_SaveData)[2];
TYPEDESCRIPTION (*CSpeaker::pm_SaveData)[1];

#endif // HOOK_GAMEDLL

char gszallsentencenames[ CVOXFILESENTENCEMAX ][ CBSENTENCENAME_MAX ];
sentenceg rgsentenceg[ CSENTENCEG_MAX ];

char grgszTextureName[ CTEXTURESMAX ][ CBTEXTURENAMEMAX ];
char grgchTextureType[ CTEXTURESMAX ];
int fTextureTypeInit;
int gcTextures;

/* <172311> ../cstrike/dlls/sound.cpp:140 */
LINK_ENTITY_TO_CLASS(ambient_generic, CAmbientGeneric);

/* <171c1f> ../cstrike/dlls/sound.cpp:155 */
IMPLEMENT_SAVERESTORE(CAmbientGeneric, CBaseEntity);

/* <1718ea> ../cstrike/dlls/sound.cpp:160 */
NOBODY void CAmbientGeneric::Spawn(void)
{
//	{
//		char *szSoundFile;                                   //   191
//	}
}

/* <1724f8> ../cstrike/dlls/sound.cpp:223 */
NOBODY void CAmbientGeneric::Restart(void)
{
//	{
//		char *szSoundFile;                                   //   247
//	}
}

/* <1724bb> ../cstrike/dlls/sound.cpp:296 */
NOBODY void CAmbientGeneric::Precache(void)
{
//	{
//		char *szSoundFile;                                   //   298
//	}
}

/* <171973> ../cstrike/dlls/sound.cpp:328 */
NOBODY void CAmbientGeneric::RampThink(void)
{
//	{
//		char *szSoundFile;                                   //   330
//		int pitch;                                            //   331
//		int vol;                                              //   332
//		int flags;                                            //   333
//		int fChanged;                                         //   334
//		int prev;                                             //   335
//		{
//			int pos;                                      //   429
//		}
//	}
}

/* <1723db> ../cstrike/dlls/sound.cpp:521 */
NOBODY void CAmbientGeneric::InitModulationParms(void)
{
//	{
//		int pitchinc;                                         //   523
//	}
}

/* <172418> ../cstrike/dlls/sound.cpp:605 */
NOBODY void CAmbientGeneric::ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		char *szSoundFile;                                   //   607
//		float fraction;                                       //   608
//		{
//			int pitchinc;                                 //   649
//		}
//	}
}

/* <171f38> ../cstrike/dlls/sound.cpp:717 */
NOBODY void CAmbientGeneric::KeyValue(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   723
//	FStrEq(const char *sz1,
//		const char *sz2);  //   730
//	FStrEq(const char *sz1,
//		const char *sz2);  //   740
//	FStrEq(const char *sz1,
//		const char *sz2);  //   750
//	FStrEq(const char *sz1,
//		const char *sz2);  //   764
//	FStrEq(const char *sz1,
//		const char *sz2);  //   778
//	FStrEq(const char *sz1,
//		const char *sz2);  //   791
//	FStrEq(const char *sz1,
//		const char *sz2);  //   805
//	FStrEq(const char *sz1,
//		const char *sz2);  //   819
//	FStrEq(const char *sz1,
//		const char *sz2);  //   827
//	FStrEq(const char *sz1,
//		const char *sz2);  //   839
//	FStrEq(const char *sz1,
//		const char *sz2);  //   850
//	FStrEq(const char *sz1,
//		const char *sz2);  //   860
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   869
//	atoi(const char *__nptr);  //   732
//	atoi(const char *__nptr);  //   725
//	atoi(const char *__nptr);  //   742
//	atoi(const char *__nptr);  //   780
//	atoi(const char *__nptr);  //   752
//	atoi(const char *__nptr);  //   766
//	atoi(const char *__nptr);  //   829
//	atoi(const char *__nptr);  //   793
//	atoi(const char *__nptr);  //   807
//	atoi(const char *__nptr);  //   821
//	atoi(const char *__nptr);  //   841
//	atoi(const char *__nptr);  //   852
//	atoi(const char *__nptr);  //   862
}

/* <172566> ../cstrike/dlls/sound.cpp:891 */
LINK_ENTITY_TO_CLASS(env_sound, CEnvSound);

/* <171bd2> ../cstrike/dlls/sound.cpp:898 */
IMPLEMENT_SAVERESTORE(CEnvSound, CBaseEntity);

/* <171d61> ../cstrike/dlls/sound.cpp:901 */
NOBODY void CEnvSound::KeyValue(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   904
//	FStrEq(const char *sz1,
//		const char *sz2);  //   909
//	KeyValue(CEnvSound *const this,
//		KeyValueData *pkvd);  //   901
//	atof(const char *__nptr);  //   906
}

/* <172633> ../cstrike/dlls/sound.cpp:919 */
NOBODY BOOL FEnvSoundInRange(entvars_t *pev, entvars_t *pevTarget, float *pflRange)
{
//	{
//		class CEnvSound *pSound;                             //   921
//		Vector vecSpot1;                                //   922
//		Vector vecSpot2;                                //   923
//		Vector vecRange;                                //   924
//		float flRange;                                        //   925
//		TraceResult tr;                                       //   926
//		GetClassPtr<CEnvSound>(CEnvSound *a);  //   921
//		operator+(const Vector *const this,
//				const Vector &v);  //   922
//		operator+(const Vector *const this,
//				const Vector &v);  //   923
//		operator-(const Vector *const this,
//				const Vector &v);  //   937
//		Length(const Vector *const this);  //   938
//	}
}

/* <17428e> ../cstrike/dlls/sound.cpp:960 */
NOBODY void CEnvSound::Think(void)
{
//	
//env_sound_Think_fast:                                                 //  1039
//	
//env_sound_Think_slow:                                                 //  1043
//	{
//		edict_t *pentPlayer;                                 //   965
//		class CBasePlayer *pPlayer;                          //   966
//		float flRange;                                        //   972
//		edict(CBaseEntity *const this);  //   965
//		FNullEnt(const edict_t *pent);  //   968
//		VARS(edict_t *pent);  //   971
//		FNullEnt(const edict_t *pent);  //   977
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1024
//	}
}

/* <171926> ../cstrike/dlls/sound.cpp:1053 */
NOBODY void CEnvSound::Spawn(void)
{
}

// randomize list of sentence name indices

/* <17093f> ../cstrike/dlls/sound.cpp:1084 */
NOXREF void USENTENCEG_InitLRU(unsigned char *plru, int count)
{
	int i, j, k;
	unsigned char temp;
	
	if (!fSentencesInit)
		return;

	if (count > CSENTENCE_LRU_MAX)
		count = CSENTENCE_LRU_MAX;

	for (i = 0; i < count; i++)
		plru[i] = (unsigned char)i;

	// randomize array
	for (i = 0; i < (count * 4); i++)
	{
		j = RANDOM_LONG(0, count - 1);
		k = RANDOM_LONG(0, count - 1);

		temp = plru[j];
		plru[j] = plru[k];
		plru[k] = temp;
	}
}

// ignore lru. pick next sentence from sentence group. Go in order until we hit the last sentence, 
// then repeat list if freset is true.  If freset is false, then repeat last sentence.
// ipick is passed in as the requested sentence ordinal.
// ipick 'next' is returned.  
// return of -1 indicates an error.

/* <17290a> ../cstrike/dlls/sound.cpp:1115 */
int USENTENCEG_PickSequential(int isentenceg, char *szfound, int ipick, int freset)
{
	char *szgroupname;
	unsigned char count;
	char sznum[8];
	
	if (!fSentencesInit)
		return -1;

	if (isentenceg < 0)
		return -1;

	szgroupname = rgsentenceg[isentenceg].szgroupname;
	count = rgsentenceg[isentenceg].count;
	
	if (count == 0)
		return -1;

	if (ipick >= count)
		ipick = count - 1;

	Q_strcpy(szfound, "!");
	Q_strcat(szfound, szgroupname);
	Q_sprintf(sznum, "%d", ipick);
	Q_strcat(szfound, sznum);
	
	if (ipick >= count)
	{
		if (freset)
			return 0; // reset at end of list
		else
			return count;
	}

	return ipick + 1;
}

// pick a random sentence from rootname0 to rootnameX.
// picks from the rgsentenceg[isentenceg] least
// recently used, modifies lru array. returns the sentencename.
// note, lru must be seeded with 0-n randomized sentence numbers, with the
// rest of the lru filled with -1. The first integer in the lru is
// actually the size of the list.  Returns ipick, the ordinal
// of the picked sentence within the group.

/* <1729cb> ../cstrike/dlls/sound.cpp:1163 */
int USENTENCEG_Pick(int isentenceg, char *szfound)
{
	char *szgroupname;
	unsigned char *plru;
	unsigned char i;
	unsigned char count;
	char sznum[8];
	unsigned char ipick;
	BOOL ffound = FALSE;
	
	if (!fSentencesInit)
		return -1;

	if (isentenceg < 0)
		return -1;

	szgroupname = rgsentenceg[isentenceg].szgroupname;
	count = rgsentenceg[isentenceg].count;
	plru = rgsentenceg[isentenceg].rgblru;

	while (!ffound)
	{
		for (i = 0; i < count; i++)
			if (plru[i] != 0xFF)
			{
				ipick = plru[i];
				plru[i] = 0xFF;
				ffound = TRUE;
				break;
			}

		if (!ffound)
			USENTENCEG_InitLRU(plru, count);
		else
		{
			Q_strcpy(szfound, "!");
			Q_strcat(szfound, szgroupname);
			Q_sprintf(sznum, "%d", ipick);
			Q_strcat(szfound, sznum);
			return ipick;
		}
	}
	return -1;
}

// Given sentence group rootname (name without number suffix),
// get sentence group index (isentenceg). Returns -1 if no such name.

/* <172b0c> ../cstrike/dlls/sound.cpp:1213 */
NOXREF int SENTENCEG_GetIndex(const char *szgroupname)
{
	int i;

	if (!fSentencesInit || !szgroupname)
		return -1;

	// search rgsentenceg for match on szgroupname

	i = 0;
	while (rgsentenceg[i].count != 0)
	{
		if (!Q_strcmp(szgroupname, rgsentenceg[i].szgroupname))
			return i;

		i++;
	}

	return -1;
}

// given sentence group index, play random sentence for given entity.
// returns ipick - which sentence was picked to 
// play from the group. Ipick is only needed if you plan on stopping
// the sound before playback is done (see SENTENCEG_Stop).

/* <170eb5> ../cstrike/dlls/sound.cpp:1238 */
NOXREF int SENTENCEG_PlayRndI(edict_t *entity, int isentenceg, float volume, float attenuation, int flags, int pitch)
{
	char name[64];
	int ipick;

	if (!fSentencesInit)
		return -1;

	name[0] = 0;

	ipick = USENTENCEG_Pick(isentenceg, name);
	if (ipick > 0 && name)
		EMIT_SOUND_DYN(entity, CHAN_VOICE, name, volume, attenuation, flags, pitch);

	return ipick;
}

/* <170a36> ../cstrike/dlls/sound.cpp:1257 */
NOXREF int SENTENCEG_PlayRndSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch)
{
	char name[64];
	int ipick;
	int isentenceg;

	if (!fSentencesInit)
		return -1;

	name[0] = 0;

	isentenceg = SENTENCEG_GetIndex(szgroupname);
	if (isentenceg < 0)
	{
		ALERT( at_console, "No such sentence group %s\n", szgroupname );
		return -1;
	}

	ipick = USENTENCEG_Pick(isentenceg, name);

	if (ipick >= 0 && name[0])
		EMIT_SOUND_DYN(entity, CHAN_VOICE, name, volume, attenuation, flags, pitch);

	return ipick;
}

// play sentences in sequential order from sentence group.  Reset after last sentence.

/* <173125> ../cstrike/dlls/sound.cpp:1285 */
int SENTENCEG_PlaySequentialSz(edict_t *entity, const char *szgroupname, float volume, float attenuation, int flags, int pitch, int ipick, int freset)
{
	char name[64];
	int ipicknext;
	int isentenceg;

	if (!fSentencesInit)
		return -1;

	name[0] = 0;

	isentenceg = SENTENCEG_GetIndex(szgroupname);
	if (isentenceg < 0)
		return -1;

	ipicknext = USENTENCEG_PickSequential(isentenceg, name, ipick, freset);
	if (ipicknext >= 0 && name[0])
		EMIT_SOUND_DYN(entity, CHAN_VOICE, name, volume, attenuation, flags, pitch);

	return ipicknext;
}

// for this entity, for the given sentence within the sentence group, stop
// the sentence.

/* <173360> ../cstrike/dlls/sound.cpp:1311 */
NOXREF void SENTENCEG_Stop(edict_t *entity, int isentenceg, int ipick)
{
	char buffer[64];
	char sznum[8];

	if (!fSentencesInit)
		return;

	if (isentenceg < 0 || ipick < 0)
		return;

	Q_strcpy(buffer, "!");
	Q_strcat(buffer, rgsentenceg[isentenceg].szgroupname);
	Q_sprintf(sznum, "%d", ipick);
	Q_strcat(buffer, sznum);

	STOP_SOUND(entity, CHAN_VOICE, buffer);
}

// open sentences.txt, scan for groups, build rgsentenceg
// Should be called from world spawn, only works on the
// first call and is ignored subsequently.

/* <1734e4> ../cstrike/dlls/sound.cpp:1334 */
void SENTENCEG_Init(void)
{
	char buffer[512];
	char szgroup[64];
	int i, j;
	int isentencegs;

	if (fSentencesInit)
		return;

	Q_memset(gszallsentencenames, 0, sizeof(gszallsentencenames));
	gcallsentences = 0;

	Q_memset(rgsentenceg, 0, CSENTENCEG_MAX * sizeof(sentenceg));
	Q_memset(buffer, 0, sizeof(buffer));
	Q_memset(szgroup, 0, sizeof(szgroup));

	isentencegs = -1;
	
	int filePos = 0, fileSize;
	byte *pMemFile = LOAD_FILE_FOR_ME("sound/sentences.txt", &fileSize);
	if (!pMemFile)
		return;

	// for each line in the file...
	while (memfgets(pMemFile, fileSize, filePos, buffer, sizeof(buffer) - 1) != NULL)
	{
		// skip whitespace
		i = 0;
		while(buffer[i] && buffer[i] == ' ')
			i++;

		if (!buffer[i])
			continue;

		if (buffer[i] == '/' || !isalpha(buffer[i]))
			continue;

		// get sentence name
		j = i;
		while (buffer[j] && buffer[j] != ' ')
			j++;

		if (!buffer[j])
			continue;

		if (gcallsentences > CVOXFILESENTENCEMAX)
		{
			ALERT (at_error, "Too many sentences in sentences.txt!\n");
			break;
		}

		// null-terminate name and save in sentences array
		buffer[j] = 0;
		const char *pString = buffer + i;

		if (Q_strlen( pString ) >= CBSENTENCENAME_MAX)
			ALERT( at_warning, "Sentence %s longer than %d letters\n", pString, CBSENTENCENAME_MAX - 1);

		Q_strcpy(gszallsentencenames[gcallsentences++], pString);

		j--;
		if (j <= i)
			continue;

		if (!isdigit(buffer[j]))
			continue;

		// cut out suffix numbers
		while (j > i && isdigit(buffer[j]))
			j--;

		if (j <= i)
			continue;

		buffer[j + 1] = 0;

		// if new name doesn't match previous group name,
		// make a new group.

		if (Q_strcmp(szgroup, &(buffer[i])))
		{
			// name doesn't match with prev name,
			// copy name into group, init count to 1
			isentencegs++;
			if (isentencegs >= CSENTENCEG_MAX)
			{
				ALERT(at_error, "Too many sentence groups in sentences.txt!\n");
				break;
			}

			Q_strcpy(rgsentenceg[isentencegs].szgroupname, &(buffer[i]));
			rgsentenceg[isentencegs].count = 1;

			Q_strcpy(szgroup, &(buffer[i]));

			continue;
		}
		else
		{
			//name matches with previous, increment group count
			if (isentencegs >= 0)
				rgsentenceg[isentencegs].count++;
		}
	}

	FREE_FILE(pMemFile);

	fSentencesInit = TRUE;

	// init lru lists

	i = 0;

	while (rgsentenceg[i].count && i < CSENTENCEG_MAX)
	{
		USENTENCEG_InitLRU(&(rgsentenceg[i].rgblru[0]), rgsentenceg[i].count);
		i++;
	}
}

// convert sentence (sample) name to !sentencenum, return !sentencenum

/* <172b37> ../cstrike/dlls/sound.cpp:1457 */
int SENTENCEG_Lookup(const char *sample, char *sentencenum)
{
	char sznum[8];
	int i;

	// this is a sentence name; lookup sentence number
	// and give to engine as string.
	for (i = 0; i < gcallsentences; i++)
	{
		if (!Q_stricmp(gszallsentencenames[i], sample + 1))
		{
			if (sentencenum)
			{
				Q_strcpy(sentencenum, "!");
				Q_sprintf(sznum, "%d", i);
				Q_strcat(sentencenum, sznum);
			}
			return i;
		}
	}

	// sentence name not found!
	return -1;
}

/* <170992> ../cstrike/dlls/sound.cpp:1483 */
void EMIT_SOUND_DYN(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int flags, int pitch)
{
	if (sample && *sample == '!')
	{
		char name[32];
		if (SENTENCEG_Lookup(sample, name) >= 0)
			EMIT_SOUND_DYN2(entity, channel, name, volume, attenuation, flags, pitch);
		else
			ALERT(at_aiconsole, "Unable to find %s in sentences.txt\n", sample);
	}
	else
		EMIT_SOUND_DYN2(entity, channel, sample, volume, attenuation, flags, pitch);
}

// play a specific sentence over the HEV suit speaker - just pass player entity, and !sentencename

/* <173770> ../cstrike/dlls/sound.cpp:1500 */
void EMIT_SOUND_SUIT(edict_t *entity, const char *sample)
{
	float fvol;
	int pitch = PITCH_NORM;

	fvol = CVAR_GET_FLOAT("suitvolume");
	if (RANDOM_LONG(0, 1))
		pitch = RANDOM_LONG(0, 6) + 98;

	if (fvol > 0.05)
		EMIT_SOUND_DYN(entity, CHAN_STATIC, sample, fvol, ATTN_NORM, 0, pitch);
}

// play a sentence, randomly selected from the passed in group id, over the HEV suit speaker

/* <1738c3> ../cstrike/dlls/sound.cpp:1515 */
void EMIT_GROUPID_SUIT(edict_t *entity, int isentenceg)
{
	float fvol;
	int pitch = PITCH_NORM;

	fvol = CVAR_GET_FLOAT("suitvolume");
	if (RANDOM_LONG(0, 1))
		pitch = RANDOM_LONG(0, 6) + 98;

	if (fvol > 0.05)
		SENTENCEG_PlayRndI(entity, isentenceg, fvol, ATTN_NORM, 0, pitch);
}

// play a sentence, randomly selected from the passed in groupname

/* <173a7b> ../cstrike/dlls/sound.cpp:1530 */
NOXREF void EMIT_GROUPNAME_SUIT(edict_t *entity, const char *groupname)
{
	float fvol;
	int pitch = PITCH_NORM;

	fvol = CVAR_GET_FLOAT("suitvolume");
	if (RANDOM_LONG(0, 1))
		pitch = RANDOM_LONG(0, 6) + 98;

	if (fvol > 0.05)
		SENTENCEG_PlayRndSz(entity, groupname, fvol, ATTN_NORM, 0, pitch);
}

/* <171cc9> ../cstrike/dlls/sound.cpp:1561 */
char *memfgets(byte *pMemFile, int fileSize, int &filePos, char *pBuffer, int bufferSize)
{
	// Bullet-proofing
	if (!pMemFile || !pBuffer)
		return NULL;

	if (filePos >= fileSize)
		return NULL;

	int i = filePos;
	int last = fileSize;

	// fgets always NULL terminates, so only read bufferSize-1 characters
	if (last - filePos > (bufferSize - 1))
		last = filePos + (bufferSize - 1);

	int stop = 0;

	// Stop at the next newline (inclusive) or end of buffer
	while (i < last && !stop)
	{
		if (pMemFile[i] == '\n')
			stop = 1;
		i++;
	}

	// If we actually advanced the pointer, copy it over
	if (i != filePos)
	{
		// We read in size bytes
		int size = i - filePos;
		// copy it out
		Q_memcpy(pBuffer, pMemFile + filePos, sizeof(byte) * size);

		// If the buffer isn't full, terminate (this is always true)
		if (size < bufferSize)
			pBuffer[size] = 0;

		// Update file pointer
		filePos = i;
		return pBuffer;
	}

	// No data read, bail
	return NULL;
}

/* <173cc2> ../cstrike/dlls/sound.cpp:1610 */
void TEXTURETYPE_Init(void)
{
	char buffer[512];
	int i, j;
	byte *pMemFile;
	int fileSize, filePos = 0;

	if (fTextureTypeInit)
		return;

	Q_memset(&(grgszTextureName[0][0]), 0, sizeof(grgszTextureName));
	Q_memset(grgchTextureType, 0, sizeof(grgchTextureType));

	gcTextures = 0;
	Q_memset(buffer, 0, sizeof(buffer));

	pMemFile = LOAD_FILE_FOR_ME("sound/materials.txt", &fileSize);

	if (!pMemFile)
		return;

	// for each line in the file...
	while (memfgets(pMemFile, fileSize, filePos, buffer, sizeof(buffer) - 1) != NULL && (gcTextures < CTEXTURESMAX))
	{
		// skip whitespace
		i = 0;
		while(buffer[i] && isspace(buffer[i]))
			i++;

		if (!buffer[i])
			continue;

		// skip comment lines
		if (buffer[i] == '/' || !isalpha(buffer[i]))
			continue;

		// get texture type
		grgchTextureType[gcTextures] = toupper(buffer[i++]);

		// skip whitespace
		while(buffer[i] && isspace(buffer[i]))
			i++;

		if (!buffer[i])
			continue;

		// get sentence name
		j = i;
		while (buffer[j] && !isspace(buffer[j]))
			j++;

		if (!buffer[j])
			continue;

		// null-terminate name and save in sentences array
		j = min(j, CBTEXTURENAMEMAX - 1 + i);
		buffer[j] = 0;
		Q_strcpy(&(grgszTextureName[gcTextures++][0]), &(buffer[i]));
	}
	
	FREE_FILE(pMemFile);

	fTextureTypeInit = TRUE;
}

// given texture name, find texture type
// if not found, return type 'concrete'

// NOTE: this routine should ONLY be called if the
// current texture under the player changes!

/* <173d41> ../cstrike/dlls/sound.cpp:1680 */
char TEXTURETYPE_Find(char *name)
{
	// CONSIDER: pre-sort texture names and perform faster binary search here

	for (int i = 0; i < gcTextures; i++)
	{
		if (!Q_strnicmp(name, &(grgszTextureName[ i ][0]), CBTEXTURENAMEMAX - 1))
			return (grgchTextureType[ i ]);
	}
	return CHAR_TEX_CONCRETE;
}

// play a strike sound based on the texture that was hit by the attack traceline.  VecSrc/VecEnd are the
// original traceline endpoints used by the attacker, iBulletType is the type of bullet that hit the texture.
// returns volume of strike instrument (crowbar) to play

/* <173d99> ../cstrike/dlls/sound.cpp:1697 */
float TEXTURETYPE_PlaySound(TraceResult *ptr, Vector vecSrc, Vector vecEnd, int iBulletType)
{
	// hit the world, try to play sound based on texture material type

	char chTextureType;
	float fvol;
	float fvolbar;
	char szbuffer[64];
	const char *pTextureName;
	float rgfl1[3];
	float rgfl2[3];
	char *rgsz[4];
	int cnt;
	float fattn = ATTN_NORM;

	if (!g_pGameRules->PlayTextureSounds())
		return 0.0;

	CBaseEntity *pEntity = CBaseEntity::Instance(ptr->pHit);

	chTextureType = 0;

	if (pEntity && pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
		chTextureType = CHAR_TEX_FLESH;	// hit body
	else
	{
		// hit world
		// find texture under strike, get material type
		// copy trace vector into array for trace_texture

		vecSrc.CopyToArray(rgfl1);
		vecEnd.CopyToArray(rgfl2);

		// get texture from entity or world (world is ent(0))

		if (pEntity)
			pTextureName = TRACE_TEXTURE(ENT(pEntity->pev), rgfl1, rgfl2);
		else
			pTextureName = TRACE_TEXTURE(ENT(0), rgfl1, rgfl2);

		if (pTextureName)
		{
			// strip leading '-0' or '+0~' or '{' or '!'
			if (*pTextureName == '-' || *pTextureName == '+')
				pTextureName += 2;

			if (*pTextureName == '{' || *pTextureName == '!' || *pTextureName == '~' || *pTextureName == ' ')
				pTextureName++;

			// '}}'
			Q_strcpy(szbuffer, pTextureName);
			szbuffer[CBTEXTURENAMEMAX - 1] = 0;

			// get texture type
			chTextureType = TEXTURETYPE_Find(szbuffer);
		}
	}

	switch (chTextureType)
	{
	default:
	case CHAR_TEX_CONCRETE:
		fvol = 0.9f;
		fvolbar = 0.6f;

		rgsz[0] = "player/pl_step1.wav";
		rgsz[1] = "player/pl_step2.wav";
		cnt = 2;
		break;
	case CHAR_TEX_METAL:
		fvol = 0.9f;
		fvolbar = 0.3f;

		rgsz[0] = "player/pl_metal1.wav";
		rgsz[1] = "player/pl_metal2.wav";
		cnt = 2;
		break;
	case CHAR_TEX_DIRT:
		fvol = 0.9f;
		fvolbar = 0.1f;

		rgsz[0] = "player/pl_dirt1.wav";
		rgsz[1] = "player/pl_dirt2.wav";
		rgsz[2] = "player/pl_dirt3.wav";
		cnt = 3;
		break;
	case CHAR_TEX_VENT:
		fvol = 0.5f;
		fvolbar = 0.3f;

		rgsz[0] = "player/pl_duct1.wav";
		rgsz[1] = "player/pl_duct1.wav";
		cnt = 2;
		break;
	case CHAR_TEX_GRATE:
		fvol = 0.9f;
		fvolbar = 0.5f;

		rgsz[0] = "player/pl_grate1.wav";
		rgsz[1] = "player/pl_grate4.wav";
		cnt = 2;
		break;
	case CHAR_TEX_TILE:
		fvol = 0.8f;
		fvolbar = 0.2f;

		rgsz[0] = "player/pl_tile1.wav";
		rgsz[1] = "player/pl_tile3.wav";
		rgsz[2] = "player/pl_tile2.wav";
		rgsz[3] = "player/pl_tile4.wav";
		cnt = 4;
		break;
	case CHAR_TEX_SLOSH:
		fvol = 0.9f;
		fvolbar = 0.0f;

		rgsz[0] = "player/pl_slosh1.wav";
		rgsz[1] = "player/pl_slosh3.wav";
		rgsz[2] = "player/pl_slosh2.wav";
		rgsz[3] = "player/pl_slosh4.wav";
		cnt = 4;
		break;
	case CHAR_TEX_SNOW:
		fvol = 0.7f;
		fvolbar = 0.4f;

		rgsz[0] = "player/pl_snow1.wav";
		rgsz[1] = "player/pl_snow2.wav";
		rgsz[2] = "player/pl_snow3.wav";
		rgsz[3] = "player/pl_snow4.wav";
		cnt = 4;
		break;
	case CHAR_TEX_WOOD:
		fvol = 0.9f;
		fvolbar = 0.2f;

		rgsz[0] = "debris/wood1.wav";
		rgsz[1] = "debris/wood2.wav";
		rgsz[2] = "debris/wood3.wav";
		cnt = 3;
		break;
	case CHAR_TEX_GLASS:
	case CHAR_TEX_COMPUTER:
		fvol = 0.8f;
		fvolbar = 0.2f;

		rgsz[0] = "debris/glass1.wav";
		rgsz[1] = "debris/glass2.wav";
		rgsz[2] = "debris/glass3.wav";
		cnt = 3;
		break;
	case CHAR_TEX_FLESH:
		if (iBulletType == BULLET_PLAYER_CROWBAR)
			return 0.0f; // crowbar already makes this sound

		fvol = 1.0f;
		fvolbar = 0.2f;

		rgsz[0] = "weapons/bullet_hit1.wav";
		rgsz[1] = "weapons/bullet_hit2.wav";
		fattn = 1.0f;
		cnt = 2;
		break;
	}

	// did we hit a breakable?
	if (pEntity && FClassnameIs(pEntity->pev, "func_breakable"))
	{
		// drop volumes, the object will already play a damaged sound
		fvol /= 1.5f;
		fvolbar /= 2.0f;
	}
	else if (chTextureType == CHAR_TEX_COMPUTER)
	{
		// play random spark if computer

		if (ptr->flFraction != 1.0 && RANDOM_LONG(0, 1))
		{
			UTIL_Sparks(ptr->vecEndPos);

			//random volume range
			float flVolume = RANDOM_FLOAT(0.7 , 1.0);

			switch (RANDOM_LONG(0, 1))
			{
				case 0:
					UTIL_EmitAmbientSound(ENT(0), ptr->vecEndPos, "buttons/spark5.wav", flVolume, ATTN_NORM, 0, 100);
					break;
				case 1:
					UTIL_EmitAmbientSound(ENT(0), ptr->vecEndPos, "buttons/spark6.wav", flVolume, ATTN_NORM, 0, 100);
					break;
			}
		}
	}

	// play material hit sound
	UTIL_EmitAmbientSound(ENT(0), ptr->vecEndPos, rgsz[RANDOM_LONG(0, cnt - 1)], fvol, fattn, 0, 96 + RANDOM_LONG(0, 0xf));

	return fvolbar;
}

/* <17406b> ../cstrike/dlls/sound.cpp:1885 */
LINK_ENTITY_TO_CLASS(speaker, CSpeaker);

/* <171b85> ../cstrike/dlls/sound.cpp:1891 */
IMPLEMENT_SAVERESTORE(CSpeaker, CBaseEntity);

/* <171c6b> ../cstrike/dlls/sound.cpp:1896 */
NOBODY void CSpeaker::Spawn(void)
{
//	{
//		char *szSoundFile;                                   //  1898
//	}
//	Spawn(CSpeaker *const this);  //  1896
}

/* <171a16> ../cstrike/dlls/sound.cpp:1924 */
NOBODY void CSpeaker::Precache(void)
{
//	Precache(CSpeaker *const this);  //  1924
}

/* <172b7a> ../cstrike/dlls/sound.cpp:1930 */
NOBODY void CSpeaker::SpeakerThink(void)
{
//	{
//		char *szSoundFile;                                   //  1932
//		float flvolume;                                       //  1933
//		float flattenuation;                                  //  1934
//		int flags;                                            //  1935
//		int pitch;                                            //  1936
//		SENTENCEG_PlayRndSz(edict_t *entity,
//					const char *szgroupname,
//					float volume,
//					float attenuation,
//					int flags,
//					int pitch);  //  1980
//	}
}

/* <171a4e> ../cstrike/dlls/sound.cpp:1997 */
NOBODY void CSpeaker::ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int fActive;                                          //  1999
//	}
}

/* <171e86> ../cstrike/dlls/sound.cpp:2044 */
NOBODY void CSpeaker::KeyValue(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2048
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //  2054
//	KeyValue(CSpeaker *const this,
//		KeyValueData *pkvd);  //  2044
}

#ifdef HOOK_GAMEDLL

int CAmbientGeneric::Save(CSave &save)
{
	return Save_(save);
}

int CAmbientGeneric::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CEnvSound::Save(CSave &save)
{
	return Save_(save);
}

int CEnvSound::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CSpeaker::Save(CSave &save)
{
	return Save_(save);
}

int CSpeaker::Restore(CRestore &restore)
{
	return Restore_(restore);
}

#endif // HOOK_GAMEDLL
