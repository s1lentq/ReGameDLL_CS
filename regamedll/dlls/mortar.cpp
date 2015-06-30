#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncMortarField::m_SaveData[] =
{
	DEFINE_FIELD(CFuncMortarField, m_iszXController, FIELD_STRING),
	DEFINE_FIELD(CFuncMortarField, m_iszYController, FIELD_STRING),
	DEFINE_FIELD(CFuncMortarField, m_flSpread, FIELD_FLOAT),
	DEFINE_FIELD(CFuncMortarField, m_flDelay, FIELD_FLOAT),
	DEFINE_FIELD(CFuncMortarField, m_iCount, FIELD_INTEGER),
	DEFINE_FIELD(CFuncMortarField, m_fControl, FIELD_INTEGER),
};

#else

TYPEDESCRIPTION (*CFuncMortarField::m_SaveData)[6];

#endif // HOOK_GAMEDLL

/* <f6ee7> ../cstrike/dlls/mortar.cpp:56 */
LINK_ENTITY_TO_CLASS(func_mortar_field, CFuncMortarField);

/* <f6d3b> ../cstrike/dlls/mortar.cpp:68 */
IMPLEMENT_SAVERESTORE(CFuncMortarField, CBaseToggle);

/* <f6d87> ../cstrike/dlls/mortar.cpp:71 */
NOBODY void CFuncMortarField::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    73
//	FStrEq(const char *sz1,
//		const char *sz2);  //    78
//	KeyValue(CFuncMortarField *const this,
//		KeyValueData *pkvd);  //    71
}

/* <f694a> ../cstrike/dlls/mortar.cpp:102 */
NOBODY void CFuncMortarField::Spawn_(void)
{
}

/* <f6971> ../cstrike/dlls/mortar.cpp:113 */
NOBODY void CFuncMortarField::Precache_(void)
{
}

/* <f6ae4> ../cstrike/dlls/mortar.cpp:122 */
NOBODY void CFuncMortarField::FieldUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		Vector vecStart;                                //   124
//		int pitch;                                            //   165
//		float t;                                              //   169
//		{
//			class CBaseEntity *pController;              //   143
//		}
//		{
//			int i;                                        //   170
//			{
//				Vector vecSpot;                 //   172
//				TraceResult tr;                       //   176
//				edict_t *pentOwner;                  //   179
//				class CBaseEntity *pMortar;          //   182
//				Vector(Vector *const this,
//					const Vector &v);  //   172
//				operator+(const Vector *const this,
//						const Vector &v);  //   177
//				edict(CBaseEntity *const this);  //   180
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //   182
//			}
//		}
//	}
}

/* <f6fb1> ../cstrike/dlls/mortar.cpp:203 */
LINK_ENTITY_TO_CLASS(monster_mortar, CMortar);

/* <f6998> ../cstrike/dlls/mortar.cpp:205 */
NOBODY void CMortar::Spawn_(void)
{
}

/* <f69be> ../cstrike/dlls/mortar.cpp:221 */
NOBODY void CMortar::Precache_(void)
{
}

/* <f69e5> ../cstrike/dlls/mortar.cpp:226 */
NOBODY void CMortar::MortarExplode(void)
{
//	{
//		TraceResult tr;                                       //   250
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   229
//		operator-(const Vector *const this,
//				const Vector &v);  //   251
//		operator+(const Vector *const this,
//				const Vector &v);  //   251
//	}
}

#ifdef HOOK_GAMEDLL

void CFuncMortarField::Spawn(void)
{
	Spawn_();
}

void CFuncMortarField::Precache(void)
{
	Precache_();
}

void CFuncMortarField::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncMortarField::Save(CSave &save)
{
	return Save_(save);
}

int CFuncMortarField::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CMortar::Spawn(void)
{
	Spawn_();
}

void CMortar::Precache(void)
{
	Precache_();
}

#endif // HOOK_GAMEDLL
