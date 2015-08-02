#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CPathCorner::m_SaveData[] =
{
	DEFINE_FIELD(CPathCorner, m_flWait, FIELD_FLOAT),
};

TYPEDESCRIPTION CPathTrack::m_SaveData[] =
{
	DEFINE_FIELD(CPathTrack, m_length, FIELD_FLOAT),
	DEFINE_FIELD(CPathTrack, m_pnext, FIELD_CLASSPTR),
	DEFINE_FIELD(CPathTrack, m_paltpath, FIELD_CLASSPTR),
	DEFINE_FIELD(CPathTrack, m_pprevious, FIELD_CLASSPTR),
	DEFINE_FIELD(CPathTrack, m_altName, FIELD_STRING),
};

#else // HOOK_GAMEDLL

TYPEDESCRIPTION (*CPathCorner::pm_SaveData)[1];
TYPEDESCRIPTION (*CPathTrack::pm_SaveData)[5];

#endif // HOOK_GAMEDLL

/* <122843> ../cstrike/dlls/pathcorner.cpp:41 */
LINK_ENTITY_TO_CLASS(path_corner, CPathCorner);

/* <1225b6> ../cstrike/dlls/pathcorner.cpp:49 */
IMPLEMENT_SAVERESTORE(CPathCorner, CPointEntity);

/* <122697> ../cstrike/dlls/pathcorner.cpp:54 */
NOBODY void CPathCorner::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    56
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //    62
//	KeyValue(CPathCorner *const this,
//		KeyValueData *pkvd);  //    54
}

/* <122325> ../cstrike/dlls/pathcorner.cpp:66 */
NOBODY void CPathCorner::Spawn_(void)
{
}

/* <12256a> ../cstrike/dlls/pathcorner.cpp:80 */
IMPLEMENT_SAVERESTORE(CPathTrack, CBaseEntity);

/* <12290d> ../cstrike/dlls/pathcorner.cpp:81 */
LINK_ENTITY_TO_CLASS(path_track, CPathTrack);

/* <122602> ../cstrike/dlls/pathcorner.cpp:86 */
NOBODY void CPathTrack::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    88
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //    94
//	KeyValue(CPathTrack *const this,
//		KeyValueData *pkvd);  //    86
}

/* <122433> ../cstrike/dlls/pathcorner.cpp:97 */
NOBODY void CPathTrack::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int on;                                               //    99
//	}
//	Use(CPathTrack *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //    97
}

/* <122a12> ../cstrike/dlls/pathcorner.cpp:128 */
NOBODY void CPathTrack::Link(void)
{
//	{
//		edict_t *pentTarget;                                 //   130
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   151
//		FNullEnt(const edict_t *pent);  //   152
//		Instance(edict_t *pent);  //   154
//		SetPrevious(CPathTrack *const this,
//				class CPathTrack *pprev);  //   158
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   134
//		FNullEnt(const edict_t *pent);  //   135
//		Instance(edict_t *pent);  //   137
//		SetPrevious(CPathTrack *const this,
//				class CPathTrack *pprev);  //   141
//	}
}

/* <12239a> ../cstrike/dlls/pathcorner.cpp:165 */
NOBODY void CPathTrack::Spawn_(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //   168
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   168
}

/* <122c76> ../cstrike/dlls/pathcorner.cpp:180 */
NOBODY void CPathTrack::Activate_(void)
{
}

/* <122c9c> ../cstrike/dlls/pathcorner.cpp:186 */
NOBODY CPathTrack *CPathTrack::ValidPath(CPathTrack *ppath, int testFlag)
{
}

/* <122745> ../cstrike/dlls/pathcorner.cpp:198 */
NOBODY void CPathTrack::Project(CPathTrack *pstart, CPathTrack *pend, Vector *origin, float dist)
{
//	{
//		Vector dir;                                     //   202
//		operator-(const Vector *const this,
//				const Vector &v);  //   202
//		Normalize(const Vector *const this);  //   203
//		operator*(const Vector *const this,
//				float fl);  //   204
//		operator+(const Vector *const this,
//				const Vector &v);  //   204
//	}
}

/* <122d0f> ../cstrike/dlls/pathcorner.cpp:208 */
NOBODY CPathTrack *CPathTrack::GetNext(void)
{
}

/* <122d30> ../cstrike/dlls/pathcorner.cpp:218 */
NOBODY CPathTrack *CPathTrack::GetPrevious(void)
{
}

/* <122d51> ../cstrike/dlls/pathcorner.cpp:228 */
NOBODY void CPathTrack::SetPrevious(CPathTrack *pprev)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   231
}

/* <122d95> ../cstrike/dlls/pathcorner.cpp:237 */
NOBODY CPathTrack *CPathTrack::LookAhead(Vector *origin, float dist, int move)
{
//	{
//		class CPathTrack *pcurrent;                          //   239
//		float originalDist;                                   //   240
//		Vector currentPos;                              //   243
//		Vector(Vector *const this,
//			const Vector &v);  //   243
//		{
//			Vector dir;                             //   291
//			float length;                                 //   292
//			GetNext(CPathTrack *const this);  //   285
//			ValidPath(CPathTrack *const this,
//					class CPathTrack *ppath,
//					int testFlag);  //   285
//			GetNext(CPathTrack *const this);  //   291
//			operator-(const Vector *const this,
//					const Vector &v);  //   291
//			Length(const Vector *const this);  //   292
//			GetNext(CPathTrack *const this);  //   293
//			GetNext(CPathTrack *const this);  //   293
//			ValidPath(CPathTrack *const this,
//					class CPathTrack *ppath,
//					int testFlag);  //   293
//			Project(CPathTrack *const this,
//				class CPathTrack *pstart,
//				class CPathTrack *pend,
//				Vector *origin,
//				float dist);  //   288
//			GetNext(CPathTrack *const this);  //   307
//			GetNext(CPathTrack *const this);  //   308
//			operator*(const Vector *const this,
//					float fl);  //   301
//			operator+(const Vector *const this,
//					const Vector &v);  //   301
//			GetPrevious(CPathTrack *const this);  //   288
//		}
//		{
//			Vector dir;                             //   250
//			float length;                                 //   251
//			operator-(const Vector *const this,
//					const Vector &v);  //   250
//			Length(const Vector *const this);  //   251
//			GetPrevious(CPathTrack *const this);  //   254
//			ValidPath(CPathTrack *const this,
//					class CPathTrack *ppath,
//					int testFlag);  //   254
//			GetPrevious(CPathTrack *const this);  //   260
//			GetPrevious(CPathTrack *const this);  //   275
//			GetPrevious(CPathTrack *const this);  //   272
//			ValidPath(CPathTrack *const this,
//					class CPathTrack *ppath,
//					int testFlag);  //   272
//			operator*(const Vector *const this,
//					float fl);  //   264
//			operator+(const Vector *const this,
//					const Vector &v);  //   264
//			GetNext(CPathTrack *const this);  //   257
//			Project(CPathTrack *const this,
//				class CPathTrack *pstart,
//				class CPathTrack *pend,
//				Vector *origin,
//				float dist);  //   257
//		}
//	}
}

/* <123220> ../cstrike/dlls/pathcorner.cpp:320 */
NOBODY CPathTrack *CPathTrack::Nearest(Vector origin)
{
//	{
//		int deadCount;                                        //   322
//		float minDist;                                        //   323
//		float dist;                                           //   323
//		Vector delta;                                   //   324
//		class CPathTrack *ppath;                             //   325
//		class CPathTrack *pnearest;                          //   325
//		operator-(const Vector *const this,
//				const Vector &v);  //   328
//		Length(const Vector *const this);  //   330
//		GetNext(CPathTrack *const this);  //   332
//		GetNext(CPathTrack *const this);  //   352
//		operator-(const Vector *const this,
//				const Vector &v);  //   344
//		Length(const Vector *const this);  //   346
//	}
}

/* <123375> ../cstrike/dlls/pathcorner.cpp:358 */
NOBODY CPathTrack *CPathTrack::Instance(edict_t *pent)
{
//	FClassnameIs(edict_t *pent,
//			const char *szClassname);  //   360
//	GET_PRIVATE(edict_t *pent);  //   361
}

#ifdef HOOK_GAMEDLL

void CPathCorner::Spawn(void)
{
	Spawn_();
}

void CPathCorner::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CPathCorner::Save(CSave &save)
{
	return Save_(save);
}

int CPathCorner::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CPathTrack::Spawn(void)
{
	Spawn_();
}

void CPathTrack::KeyValue(KeyValueData* pkvd)
{
	KeyValue_(pkvd);
}

int CPathTrack::Save(CSave &save)
{
	return Save_(save);
}

int CPathTrack::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CPathTrack::Activate(void)
{
	Activate_();
}

void CPathTrack::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
