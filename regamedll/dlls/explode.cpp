#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CEnvExplosion::m_SaveData[] =
{
	DEFINE_FIELD(CEnvExplosion, m_iMagnitude, FIELD_INTEGER),
	DEFINE_FIELD(CEnvExplosion, m_spriteScale, FIELD_INTEGER),
};

#else // HOOK_GAMEDLL

TYPEDESCRIPTION (*CEnvExplosion::m_SaveData)[2];

#endif // HOOK_GAMEDLL

/* <7f660> ../cstrike/dlls/explode.cpp:37 */
LINK_ENTITY_TO_CLASS(spark_shower, CShower);

/* <7f49c> ../cstrike/dlls/explode.cpp:39 */
NOBODY void CShower::Spawn_(void)
{
//	operator*(float fl,
//			const Vector &v);  //    41
//	edict(CBaseEntity *const this);  //    52
}

/* <7f475> ../cstrike/dlls/explode.cpp:61 */
NOBODY void CShower::Think_(void)
{
}

/* <7f122> ../cstrike/dlls/explode.cpp:73 */
NOBODY void CShower::Touch_(CBaseEntity *pOther)
{
//	operator*(const Vector *const this,
//			float fl);  //    76
//	operator*(const Vector *const this,
//			float fl);  //    78
}

/* <7f566> ../cstrike/dlls/explode.cpp:106 */
IMPLEMENT_SAVERESTORE(CEnvExplosion, CBaseMonster);

/* <7f72a> ../cstrike/dlls/explode.cpp:107 */
LINK_ENTITY_TO_CLASS(env_explosion, CEnvExplosion);

/* <7f5b2> ../cstrike/dlls/explode.cpp:109 */
NOBODY void CEnvExplosion::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   111
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   117
//	KeyValue(CEnvExplosion *const this,
//		KeyValueData *pkvd);  //   109
}


/* <7f1a5> ../cstrike/dlls/explode.cpp:120 */
NOBODY void CEnvExplosion::Spawn_(void)
{
//	{
//		float flSpriteScale;                                  //   133
//	}
}

/* <7f233> ../cstrike/dlls/explode.cpp:150 */
NOBODY void CEnvExplosion::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		TraceResult tr;                                       //   152
//		Vector vecSpot;                                 //   157
//		operator+(const Vector *const this,
//				const Vector &v);  //   159
//		operator+(const Vector *const this,
//				const Vector &v);  //   161
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   189
//		{
//			int sparkCount;                               //   226
//			{
//				int i;                                //   228
//			}
//		}
//		operator*(const Vector *const this,
//				float fl);  //   166
//		operator*(const Vector *const this,
//				float fl);  //   166
//		operator+(const Vector *const this,
//				const Vector &v);  //   166
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   202
//	}
}

/* <7f1e1> ../cstrike/dlls/explode.cpp:235 */
NOBODY void CEnvExplosion::Smoke(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   239
}

/* <7f7f4> ../cstrike/dlls/explode.cpp:258 */
NOBODY void ExplosionCreate(Vector &center, Vector &angles, edict_t *pOwner, int magnitude, BOOL doDamage)
{
//	{
//		KeyValueData kvd;                                     //   260
//		char buf;                                             //   261
//		class CBaseEntity *pExplosion;                       //   263
//	}
}

#ifdef HOOK_GAMEDLL

void CShower::Spawn(void)
{
	Spawn_();
}

void CShower::Think(void)
{
	Think_();
}

void CShower::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CEnvExplosion::Spawn(void)
{
	Spawn_();
}

void CEnvExplosion::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CEnvExplosion::Save(CSave &save)
{
	return Save_(save);
}

int CEnvExplosion::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CEnvExplosion::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
