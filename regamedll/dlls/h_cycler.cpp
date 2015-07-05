#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CCycler::m_SaveData[] =
{
	DEFINE_FIELD(CCycler, m_animate, FIELD_INTEGER),
};

TYPEDESCRIPTION CCyclerSprite::m_SaveData[] =
{
	DEFINE_FIELD(CCyclerSprite, m_animate, FIELD_INTEGER),
	DEFINE_FIELD(CCyclerSprite, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CCyclerSprite, m_maxFrame, FIELD_FLOAT),
};

TYPEDESCRIPTION CWreckage::m_SaveData[] =
{
	DEFINE_FIELD(CWreckage, m_flStartTime, FIELD_TIME),
};

#else

TYPEDESCRIPTION (*CCycler::pm_SaveData)[1];
TYPEDESCRIPTION (*CCyclerSprite::pm_SaveData)[3];
TYPEDESCRIPTION (*CWreckage::pm_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <cce5f> ../cstrike/dlls/h_cycler.cpp:61 */
IMPLEMENT_SAVERESTORE(CCycler, CBaseToggle);

/* <cd01f> ../cstrike/dlls/h_cycler.cpp:70 */
void CGenericCycler::Spawn_(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //    70
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //    70
//	GenericCyclerSpawn(CCycler *const this,
//				char *szModel,
//				Vector vecMin,
//				Vector vecMax);  //    70
}

/* <cd2d2> ../cstrike/dlls/h_cycler.cpp:72 */
LINK_ENTITY_TO_CLASS(cycler, CGenericCycler);

/* <cd39c> ../cstrike/dlls/h_cycler.cpp:85 */
LINK_ENTITY_TO_CLASS(cycler_prdroid, CCyclerProbe);

/* <cd16d> ../cstrike/dlls/h_cycler.cpp:86 */
void CCyclerProbe::Spawn_(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //    89
//	operator+(const Vector *const this,
//			const Vector &v);  //    88
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //    89
}

/* <cd466> ../cstrike/dlls/h_cycler.cpp:96 */
void CCycler::GenericCyclerSpawn(char *szModel, Vector vecMin, Vector vecMax)
{
//	GenericCyclerSpawn(CCycler *const this,
//				char *szModel,
//				Vector vecMin,
//				Vector vecMax);  //    96
//	MAKE_STRING_CLASS(const char *str,
//				entvars_t *pev);  //   105
}

/* <ccc91> ../cstrike/dlls/h_cycler.cpp:115 */
void CCycler::Spawn_(void)
{
}

/* <ccd3e> ../cstrike/dlls/h_cycler.cpp:151 */
void CCycler::Think_(void)
{
//	Think(CCycler *const this);  //   151
}

/* <cc8bf> ../cstrike/dlls/h_cycler.cpp:176 */
void CCycler::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <ccf43> ../cstrike/dlls/h_cycler.cpp:189 */
int CCycler::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	TakeDamage(CCycler *const this,
//			entvars_t *pevInflictor,
//			entvars_t *pevAttacker,
//			float flDamage,
//			int bitsDamageType);  //   189
}

/* <cd4f8> ../cstrike/dlls/h_cycler.cpp:246 */
LINK_ENTITY_TO_CLASS(cycler_sprite, CCyclerSprite);

/* <ccef7> ../cstrike/dlls/h_cycler.cpp:255 */
IMPLEMENT_SAVERESTORE(CCyclerSprite, CBaseEntity);

/* <cc982> ../cstrike/dlls/h_cycler.cpp:284 */
void CCyclerSprite::Restart_(void)
{
//	{
//		int i;                                                //   300
//	}
}

/* <cc943> ../cstrike/dlls/h_cycler.cpp:258 */
void CCyclerSprite::Spawn_(void)
{
//	{
//		int i;                                                //   279
//	}
}

/* <cd0ef> ../cstrike/dlls/h_cycler.cpp:305 */
void CCyclerSprite::Think_(void)
{
//	ShouldAnimate(CCyclerSprite *const this);  //   307
//	Animate(CCyclerSprite *const this,
//		float frames);  //   308
}

/* <cc9c1> ../cstrike/dlls/h_cycler.cpp:315 */
void CCyclerSprite::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <cd228> ../cstrike/dlls/h_cycler.cpp:322 */
int CCyclerSprite::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	Animate(CCyclerSprite *const this,
//		float frames);  //   326
}

/* <cd5c2> ../cstrike/dlls/h_cycler.cpp:331 */
void CCyclerSprite::Animate(float frames)
{
//	Animate(CCyclerSprite *const this,
//		float frames);  //   331
}

/* <cd610> ../cstrike/dlls/h_cycler.cpp:358 */
LINK_ENTITY_TO_CLASS(cycler_weapon, CWeaponCycler);

/* <ccbf6> ../cstrike/dlls/h_cycler.cpp:361 */
void CWeaponCycler::Spawn_(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //   372
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   372
}

/* <cca7c> ../cstrike/dlls/h_cycler.cpp:378 */
BOOL CWeaponCycler::Deploy_(void)
{
}

/* <ccaa3> ../cstrike/dlls/h_cycler.cpp:388 */
void CWeaponCycler::Holster_(int skiplocal)
{
}

/* <ccad8> ../cstrike/dlls/h_cycler.cpp:394 */
void CWeaponCycler::PrimaryAttack_(void)
{
}

/* <ccb97> ../cstrike/dlls/h_cycler.cpp:403 */
void CWeaponCycler::SecondaryAttack_(void)
{
//	{
//		float flFrameRate;                                    //   405
//		float flGroundSpeed;                                  //   405
//		void *pmodel;                                        //   410
//	}
}

/* <cce12> ../cstrike/dlls/h_cycler.cpp:443 */
IMPLEMENT_SAVERESTORE(CWreckage, CBaseToggle);

/* <cd6dd> ../cstrike/dlls/h_cycler.cpp:446 */
LINK_ENTITY_TO_CLASS(cycler_wreckage, CWreckage);

/* <ccaff> ../cstrike/dlls/h_cycler.cpp:448 */
void CWreckage::Spawn_(void)
{
}

/* <ccd07> ../cstrike/dlls/h_cycler.cpp:468 */
void CWreckage::Precache_(void)
{
//	Precache(CWreckage *const this);  //   468
}

/* <ccb26> ../cstrike/dlls/h_cycler.cpp:474 */
void CWreckage::Think_(void)
{
//	{
//		Vector VecSrc;                                  //   492
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   498
//	}
}

#ifdef HOOK_GAMEDLL

void CWreckage::Spawn(void)
{
	Spawn_();
}

void CWreckage::Precache(void)
{
	Precache_();
}

int CWreckage::Save(CSave &save)
{
	return Save_(save);
}

int CWreckage::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CWreckage::Think(void)
{
	Think_();
}

void CWeaponCycler::Spawn(void)
{
	Spawn_();
}

BOOL CWeaponCycler::Deploy(void)
{
	return Deploy_();
}

void CWeaponCycler::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CWeaponCycler::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CWeaponCycler::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CCyclerSprite::Spawn(void)
{
	Spawn_();
}

void CCyclerSprite::Restart(void)
{
	Restart_();
}

int CCyclerSprite::Save(CSave &save)
{
	return Save_(save);
}

int CCyclerSprite::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CCyclerSprite::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType);
}

void CCyclerSprite::Think(void)
{
	Think_();
}

void CCyclerSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator,pCaller,useType,value);
}

void CCycler::Spawn(void)
{
	Spawn_();
}

int CCycler::Save(CSave &save)
{
	return Save_(save);
}

int CCycler::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CCycler::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType);
}

void CCycler::Think(void)
{
	Think_();
}

void CCycler::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator,pCaller,useType,value);
}

void CGenericCycler::Spawn(void)
{
	Spawn_();
}

void CCyclerProbe::Spawn(void)
{
	Spawn_();
}

#endif // HOOK_GAMEDLL
