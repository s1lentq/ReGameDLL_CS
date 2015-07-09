#include "precompiled.h"

#define SF_WORLD_DARK		0x0001		// Fade from black at startup
#define SF_WORLD_TITLE		0x0002		// Display game title at startup
#define SF_WORLD_FORCETEAM	0x0004		// Force teams

edict_t *g_pBodyQueueHead;
CGlobalState gGlobalState;
float g_flWeaponCheat;

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

DLL_DECALLIST gDecals[] =
{
	{ "{shot1", 0 },		// DECAL_GUNSHOT1
	{ "{shot2", 0 },		// DECAL_GUNSHOT2
	{ "{shot3", 0 },		// DECAL_GUNSHOT3
	{ "{shot4", 0 },		// DECAL_GUNSHOT4
	{ "{shot5", 0 },		// DECAL_GUNSHOT5
	{ "{lambda01", 0 },		// DECAL_LAMBDA1
	{ "{lambda02", 0 },		// DECAL_LAMBDA2
	{ "{lambda03", 0 },		// DECAL_LAMBDA3
	{ "{lambda04", 0 },		// DECAL_LAMBDA4
	{ "{lambda05", 0 },		// DECAL_LAMBDA5
	{ "{lambda06", 0 },		// DECAL_LAMBDA6
	{ "{scorch1", 0 },		// DECAL_SCORCH1
	{ "{scorch2", 0 },		// DECAL_SCORCH2
	{ "{blood1", 0 },		// DECAL_BLOOD1
	{ "{blood2", 0 },		// DECAL_BLOOD2
	{ "{blood3", 0 },		// DECAL_BLOOD3
	{ "{blood4", 0 },		// DECAL_BLOOD4
	{ "{blood5", 0 },		// DECAL_BLOOD5
	{ "{blood6", 0 },		// DECAL_BLOOD6
	{ "{yblood1", 0 },		// DECAL_YBLOOD1
	{ "{yblood2", 0 },		// DECAL_YBLOOD2
	{ "{yblood3", 0 },		// DECAL_YBLOOD3
	{ "{yblood4", 0 },		// DECAL_YBLOOD4
	{ "{yblood5", 0 },		// DECAL_YBLOOD5
	{ "{yblood6", 0 },		// DECAL_YBLOOD6
	{ "{break1", 0 },		// DECAL_GLASSBREAK1
	{ "{break2", 0 },		// DECAL_GLASSBREAK2
	{ "{break3", 0 },		// DECAL_GLASSBREAK3
	{ "{bigshot1", 0 },		// DECAL_BIGSHOT1
	{ "{bigshot2", 0 },		// DECAL_BIGSHOT2
	{ "{bigshot3", 0 },		// DECAL_BIGSHOT3
	{ "{bigshot4", 0 },		// DECAL_BIGSHOT4
	{ "{bigshot5", 0 },		// DECAL_BIGSHOT5
	{ "{spit1", 0 },		// DECAL_SPIT1
	{ "{spit2", 0 },		// DECAL_SPIT2
	{ "{bproof1", 0 },		// DECAL_BPROOF1
	{ "{gargstomp", 0 },		// DECAL_GARGSTOMP1,		// Gargantua stomp crack
	{ "{smscorch1", 0 },		// DECAL_SMALLSCORCH1,		// Small scorch mark
	{ "{smscorch2", 0 },		// DECAL_SMALLSCORCH2,		// Small scorch mark
	{ "{smscorch3", 0 },		// DECAL_SMALLSCORCH3,		// Small scorch mark
	{ "{mommablob", 0 },		// DECAL_MOMMABIRTH		// BM Birth spray
	{ "{mommablob", 0 },		// DECAL_MOMMASPLAT		// BM Mortar spray?? need decal*/
};

TYPEDESCRIPTION CGlobalState::m_SaveData[] =
{
	DEFINE_FIELD(CGlobalState, m_listCount, FIELD_INTEGER)
};

TYPEDESCRIPTION gGlobalEntitySaveData[] =
{
	DEFINE_ARRAY(globalentity_t, name, FIELD_CHARACTER, 64),
	DEFINE_ARRAY(globalentity_t, levelName, FIELD_CHARACTER, 32),
	DEFINE_FIELD(globalentity_t, state, FIELD_INTEGER)
};

#else // HOOK_GAMEDLL

DLL_DECALLIST gDecals[42];

TYPEDESCRIPTION (*CGlobalState::pm_SaveData)[1];
TYPEDESCRIPTION gGlobalEntitySaveData[3];

#endif // HOOK_GAMEDLL

/* <1db42b> ../cstrike/dlls/world.cpp:120 */
LINK_ENTITY_TO_CLASS(infodecal, CDecal);

/* <1db00a> ../cstrike/dlls/world.cpp:123 */
NOBODY void CDecal::Spawn(void)
{
//	Spawn(CDecal *const this);  //   123
}

/* <1daee2> ../cstrike/dlls/world.cpp:171 */
NOBODY void CDecal::StaticDecal(void)
{
//	{
//		TraceResult trace;                                    //   173
//		int entityIndex;                                      //   174
//		int modelIndex;                                       //   174
//		operator+(const Vector *const this,
//				const Vector &v);  //   176
//		operator-(const Vector *const this,
//				const Vector &v);  //   176
//		ENTINDEX(edict_t *pEdict);  //   178
//		VARS(edict_t *pent);  //   180
//	}
}

/* <1dad69> ../cstrike/dlls/world.cpp:145 */
NOBODY void CDecal::TriggerDecal(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		TraceResult trace;                                    //   149
//		int entityIndex;                                      //   150
//		operator+(const Vector *const this,
//				const Vector &v);  //   152
//		operator-(const Vector *const this,
//				const Vector &v);  //   152
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   154
//		ENTINDEX(edict_t *pEdict);  //   160
//		VARS(edict_t *pent);  //   163
//	}
}

/* <1db068> ../cstrike/dlls/world.cpp:190 */
NOBODY void CDecal::KeyValue(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   192
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   202
//	KeyValue(CDecal *const this,
//		KeyValueData *pkvd);  //   190
}

/* <1db4f5> ../cstrike/dlls/world.cpp:212 */
LINK_ENTITY_TO_CLASS(bodyque, CCorpse);

/* <1da107> ../cstrike/dlls/world.cpp:214 */
NOXREF void InitBodyQue(void)
{
	g_pBodyQueueHead = NULL;
}

/* <1db5bf> ../cstrike/dlls/world.cpp:242 */
NOBODY void CopyToBodyQue(entvars_t *pev)
{
}

/* <1db5e9> ../cstrike/dlls/world.cpp:275 */
NOBODY void ClearBodyQue(void)
{
}

/* <1db601> ../cstrike/dlls/world.cpp:294 */
CGlobalState::CGlobalState(void)
{
//	Reset(CGlobalState *const this);  //   296
}

/* <1db63b> ../cstrike/dlls/world.cpp:299 */
NOBODY void CGlobalState::Reset(void)
{
}

/* <1db69e> ../cstrike/dlls/world.cpp:305 */
globalentity_t *CGlobalState::Find(string_t globalname)
{
	if (!globalname)
		return NULL;

	globalentity_t *pTest = m_pList;
	const char *pEntityName = STRING(globalname);
	while (pTest)
	{
		if (!Q_strcmp(pEntityName, pTest->name))
			break;
		pTest = pTest->pNext;
	}
	return pTest;
}

// This is available all the time now on impulse 104, remove later

/* <1db703> ../cstrike/dlls/world.cpp:329 */
void CGlobalState::DumpGlobals(void)
{
	static char *estates[] = { "Off", "On", "Dead" };
	globalentity_t *pTest;

	ALERT(at_console, "-- Globals --\n");
	pTest = m_pList;

	while (pTest != NULL)
	{
		ALERT(at_console, "%s: %s (%s)\n", pTest->name, pTest->levelName, estates[ pTest->state ]);
		pTest = pTest->pNext;
	}
}

/* <1db76a> ../cstrike/dlls/world.cpp:345 */
NOBODY void CGlobalState::EntityAdd(string_t globalname, string_t mapName, GLOBALESTATE state)
{
//	{
//		globalentity_t *pNewEntity;                          //   349
//	}
}

/* <1db7b3> ../cstrike/dlls/world.cpp:360 */
void CGlobalState::EntitySetState(string_t globalname, GLOBALESTATE state)
{
	globalentity_t *pEnt = Find(globalname);
	if (pEnt)
		pEnt->state = state;
}

/* <1db873> ../cstrike/dlls/world.cpp:369 */
NOBODY const globalentity_t *CGlobalState::EntityFromTable(string_t globalname)
{
//	{
//		globalentity_t *pEnt;                                //   371
//		Find(CGlobalState *const this,
//			string_t globalname);  //   371
//	}
}

/* <1db91c> ../cstrike/dlls/world.cpp:377 */
NOBODY GLOBALESTATE CGlobalState::EntityGetState(string_t globalname)
{
//	{
//		globalentity_t *pEnt;                                //   379
//		Find(CGlobalState *const this,
//			string_t globalname);  //   379
//	}
}

/* <1db9c5> ../cstrike/dlls/world.cpp:402 */
NOBODY int CGlobalState::Save(CSave &save)
{
//	{
//		int i;                                                //   404
//		globalentity_t *pEntity;                             //   405
//	}
}

/* <1dba07> ../cstrike/dlls/world.cpp:422 */
NOBODY int CGlobalState::Restore(CRestore &restore)
{
//	{
//		int i;                                                //   424
//		int listCount;                                        //   424
//		globalentity_t tmpEntity;                             //   425
//		ClearStates(CGlobalState *const this);  //   428
//		EntityAdd(CGlobalState *const this,
//				string_t globalname,
//				string_t mapName,
//				GLOBALESTATE state);  //   439
//	}
}

/* <1dbaf2> ../cstrike/dlls/world.cpp:444 */
NOBODY void CGlobalState::EntityUpdate(string_t globalname, string_t mapname)
{
//	{
//		globalentity_t *pEnt;                                //   446
//		Find(CGlobalState *const this,
//			string_t globalname);  //   446
//	}
}

/* <1dbbae> ../cstrike/dlls/world.cpp:453 */
NOBODY void CGlobalState::ClearStates(void)
{
//	{
//		globalentity_t *pFree;                               //   455
//		{
//			globalentity_t *pNext;                       //   458
//		}
//		Reset(CGlobalState *const this);  //   462
//	}
}

/* <1dbc13> ../cstrike/dlls/world.cpp:466 */
NOBODY void SaveGlobalState(SAVERESTOREDATA *pSaveData)
{
//	{
//		class CSave saveHelper;                               //   468
//		Save(CGlobalState *const this,
//			class CSave &save);  //   469
//		CSave(CSave *const this,
//			SAVERESTOREDATA *pdata);  //   468
//		~CSave(CSave *const this,
//			int const __in_chrg);  //   468
//	}
}

/* <1dbcde> ../cstrike/dlls/world.cpp:473 */
NOBODY void RestoreGlobalState(SAVERESTOREDATA *pSaveData)
{
//	{
//		class CRestore restoreHelper;                         //   475
//		CRestore(CRestore *const this,
//			SAVERESTOREDATA *pdata);  //   475
//		Restore(CGlobalState *const this,
//			class CRestore &restore);  //   476
//		~CRestore(CRestore *const this,
//				int const __in_chrg);  //   475
//	}
}

/* <1dbe72> ../cstrike/dlls/world.cpp:480 */
NOBODY void ResetGlobalState(void)
{
//	ClearStates(CGlobalState *const this);  //   482
}

/* <1dbeff> ../cstrike/dlls/world.cpp:493 */
LINK_ENTITY_TO_CLASS(worldspawn, CWorld);

/* <1dad1d> ../cstrike/dlls/world.cpp:502 */
void CWorld::Spawn_(void)
{
	//int flength;
	//char *pFile;

	EmptyEntityHashTable();
	g_fGameOver = FALSE;

	//TODO: reverse me
	//Precache();

	g_flWeaponCheat = g_engfuncs.pfnCVarGetFloat("sv_cheats");
	/*g_szMapBriefingText[0] = 0;
	flength = 0;

	pFile = (char *)LOAD_FILE_FOR_ME(UTIL_VarArgs("maps/%s.txt",STRING(gpGlobals->mapname)), &flength);
	if (pFile && flength)
	{
		Q_strncpy(g_szMapBriefingText, pFile, 510);
#ifdef REGAMEDLL_FIXES
		g_szMapBriefingText[510] = 0;
#endif // REGAMEDLL_FIXES

		PRECACHE_GENERIC(UTIL_VarArgs("maps/%s.txt",STRING(gpGlobals->mapname)));
		FREE_FILE(pFile);
	}
	else
	{
		pFile = (char *)LOAD_FILE_FOR_ME(UTIL_VarArgs("maps/default.txt"), &flength);
		if (pFile && flength)
		{
			Q_strncpy(g_szMapBriefingText, pFile, 510);
#ifdef REGAMEDLL_FIXES
			g_szMapBriefingText[510] = 0;
#endif // REGAMEDLL_FIXES
			PRECACHE_GENERIC(UTIL_VarArgs("maps/default.txt"));
			FREE_FILE(pFile);
		}
		if (pFile)
			FREE_FILE(pFile);
	}*/
}

/* <1dac06> ../cstrike/dlls/world.cpp:542 */
NOBODY void CWorld::Precache_(void)
{
//	GetClassPtr<CSoundEnt>(CSoundEnt *a);  //   566
//	InitBodyQue(void);  //   574
//	{
//		int i;                                                //   673
//	}
//	{
//		class CBaseEntity *pEntity;                          //   705
//	}
}

/* <1db153> ../cstrike/dlls/world.cpp:731 */
void CWorld::KeyValue_(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "skyname"))
	{
		CVAR_SET_STRING("sv_skyname", pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sounds"))
	{
		gpGlobals->cdAudioTrack = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "WaveHeight"))
	{
		pev->scale = atof(pkvd->szValue) * 0.125;
		pkvd->fHandled = TRUE;
		CVAR_SET_FLOAT("sv_wateramp", pev->scale);
	}
	else if (FStrEq(pkvd->szKeyName, "MaxRange"))
	{
		pev->speed = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "chaptertitle"))
	{
		pev->netname = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "startdark"))
	{
		int flag = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
		if (flag)
			pev->spawnflags |= SF_WORLD_DARK;
	}
	else if (FStrEq(pkvd->szKeyName, "newunit"))
	{
		if (atoi(pkvd->szValue))
			CVAR_SET_FLOAT("sv_newunit", 1.0);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "gametitle"))
	{
		if (atoi(pkvd->szValue))
			pev->spawnflags |= SF_WORLD_TITLE;
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "mapteams"))
	{
		pev->team = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "defaultteam"))
	{
		if (atoi(pkvd->szValue))
			pev->spawnflags |= SF_WORLD_FORCETEAM;
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

#ifdef HOOK_GAMEDLL

void CWorld::Spawn(void)
{
	Spawn_();
}

void CWorld::Precache(void)
{
	Precache_();
}

void CWorld::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

#endif // HOOK_GAMEDLL
