#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncTank::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTank, m_yawCenter, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_yawRate, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_yawRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_yawTolerance, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchCenter, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchRate, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_pitchTolerance, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_fireLast, FIELD_TIME),
	DEFINE_FIELD(CFuncTank, m_fireRate, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_lastSightTime, FIELD_TIME),
	DEFINE_FIELD(CFuncTank, m_persist, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_minRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_maxRange, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_barrelPos, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTank, m_spriteScale, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTank, m_iszSpriteSmoke, FIELD_STRING),
	DEFINE_FIELD(CFuncTank, m_iszSpriteFlash, FIELD_STRING),
	DEFINE_FIELD(CFuncTank, m_bulletType, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTank, m_sightOrigin, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTank, m_spread, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTank, m_pController, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncTank, m_vecControllerUsePos, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTank, m_flNextAttack, FIELD_TIME),
	DEFINE_FIELD(CFuncTank, m_iBulletDamage, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTank, m_iszMaster, FIELD_STRING),
};

TYPEDESCRIPTION CFuncTankLaser::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTankLaser, m_pLaser, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncTankLaser, m_laserTime, FIELD_TIME),
};

TYPEDESCRIPTION CFuncTankControls::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTankControls, m_pTank, FIELD_CLASSPTR),
};

#else

TYPEDESCRIPTION (*CFuncTank::m_SaveData)[26];
TYPEDESCRIPTION (*CFuncTankLaser::m_SaveData)[2];
TYPEDESCRIPTION (*CFuncTankControls::m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <8ea25> ../cstrike/dlls/func_tank.cpp:177 */
NOBODY void CFuncTank::Spawn_(void)
{
//	IsActive(CFuncTank *const this);  //   188
//	BarrelPosition(CFuncTank *const this);  //   191
}

/* <8d76a> ../cstrike/dlls/func_tank.cpp:164 */
IMPLEMENT_SAVERESTORE(CFuncTank, CBaseEntity);

/* <8d64d> ../cstrike/dlls/func_tank.cpp:202 */
NOBODY void CFuncTank::Precache_(void)
{
//	Precache(CFuncTank *const this);  //   202
}

/* <8e19e> ../cstrike/dlls/func_tank.cpp:214 */
NOBODY void CFuncTank::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   226
//	FStrEq(const char *sz1,
//		const char *sz2);  //   231
//	FStrEq(const char *sz1,
//		const char *sz2);  //   236
//	FStrEq(const char *sz1,
//		const char *sz2);  //   241
//	FStrEq(const char *sz1,
//		const char *sz2);  //   246
//	FStrEq(const char *sz1,
//		const char *sz2);  //   251
//	FStrEq(const char *sz1,
//		const char *sz2);  //   256
//	FStrEq(const char *sz1,
//		const char *sz2);  //   261
//	FStrEq(const char *sz1,
//		const char *sz2);  //   266
//	FStrEq(const char *sz1,
//		const char *sz2);  //   271
//	FStrEq(const char *sz1,
//		const char *sz2);  //   276
//	FStrEq(const char *sz1,
//		const char *sz2);  //   281
//	FStrEq(const char *sz1,
//		const char *sz2);  //   286
//	FStrEq(const char *sz1,
//		const char *sz2);  //   291
//	FStrEq(const char *sz1,
//		const char *sz2);  //   296
//	FStrEq(const char *sz1,
//		const char *sz2);  //   301
//	FStrEq(const char *sz1,
//		const char *sz2);  //   306
//	FStrEq(const char *sz1,
//		const char *sz2);  //   311
//	FStrEq(const char *sz1,
//		const char *sz2);  //   316
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   322
//	atof(const char *__nptr);  //   228
//	atof(const char *__nptr);  //   238
//	atof(const char *__nptr);  //   258
//	atof(const char *__nptr);  //   233
//	atof(const char *__nptr);  //   243
//	atof(const char *__nptr);  //   248
//	atof(const char *__nptr);  //   253
//	atof(const char *__nptr);  //   288
//	atof(const char *__nptr);  //   263
//	atof(const char *__nptr);  //   268
//	atoi(const char *__nptr);  //   293
//	atoi(const char *__nptr);  //   298
//	atoi(const char *__nptr);  //   303
//	atof(const char *__nptr);  //   308
//	atof(const char *__nptr);  //   313
}

/* <8dca8> ../cstrike/dlls/func_tank.cpp:329 */
NOBODY BOOL CFuncTank::OnControls_(entvars_t *pevTest)
{
//	{
//		Vector offset;                                  //   334
//	}
//	OnControls(CFuncTank *const this,
//			entvars_t *pevTest);  //   329
}

/* <8eba8> ../cstrike/dlls/func_tank.cpp:342 */
NOBODY BOOL CFuncTank::StartControl(CBasePlayer *pController)
{
}

/* <8ebde> ../cstrike/dlls/func_tank.cpp:372 */
NOBODY void CFuncTank::StopControl(void)
{
//	IsActive(CFuncTank *const this);  //   393
}

/* <8ec15> ../cstrike/dlls/func_tank.cpp:398 */
NOBODY void CFuncTank::ControllerPostFrame(void)
{
//	{
//		Vector vecForward;                              //   407
//		UTIL_MakeVectorsPrivate(Vector &vecAngles,
//					float *p_vForward,
//					float *p_vRight,
//					float *p_vUp);  //   408
//		BarrelPosition(CFuncTank *const this);  //   412
//	}
}

/* <8ee12> ../cstrike/dlls/func_tank.cpp:424 */
NOBODY void CFuncTank::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	IsActive(CFuncTank *const this);  //   448
//	IsActive(CFuncTank *const this);  //   451
//	TankDeactivate(CFuncTank *const this);  //   452
//	TankActivate(CFuncTank *const this);  //   454
}

/* <8ef04> ../cstrike/dlls/func_tank.cpp:459 */
NOBODY edict_t *CFuncTank::FindTarget(edict_t *pPlayer)
{
}

/* <8ef2d> ../cstrike/dlls/func_tank.cpp:466 */
NOBODY BOOL CFuncTank::InRange(float range)
{
//	InRange(CFuncTank *const this,
//		float range);  //   466
}

/* <8f717> ../cstrike/dlls/func_tank.cpp:477 */
NOBODY void CFuncTank::Think_(void)
{
//	fabs(double __x);  //   482
//	fabs(double __x);  //   482
//	StartRotSound(CFuncTank *const this);  //   483
//	StopRotSound(CFuncTank *const this);  //   485
}

/* <8efe4> ../cstrike/dlls/func_tank.cpp:488 */
NOBODY void CFuncTank::TrackTarget(void)
{
//	{
//		TraceResult tr;                                       //   490
//		edict_t *pPlayer;                                    //   491
//		BOOL updateTime;                                      //   492
//		BOOL lineOfSight;                                     //   492
//		Vector angles;                                  //   493
//		Vector direction;                               //   493
//		Vector targetPosition;                          //   493
//		Vector barrelEnd;                               //   493
//		edict_t *pTarget;                                    //   494
//		float distY;                                          //   578
//		float distX;                                          //   592
//		edict(CBaseEntity *const this);  //   491
//		{
//			float range;                                  //   524
//			IsActive(CFuncTank *const this);  //   506
//			FNullEnt(const edict_t *pent);  //   511
//			BarrelPosition(CFuncTank *const this);  //   522
//			operator+(const Vector *const this,
//					const Vector &v);  //   523
//			operator-(const Vector *const this,
//					const Vector &v);  //   524
//			Length(const Vector *const this);  //   524
//			InRange(CFuncTank *const this,
//				float range);  //   526
//			edict(CBaseEntity *const this);  //   529
//			{
//				class CBaseEntity *pInstance;        //   537
//				InRange(CFuncTank *const this,
//					float range);  //   538
//				Instance(edict_t *pent);  //   537
//			}
//			operator-(const Vector *const this,
//					const Vector &v);  //   548
//			Length(const Vector *const this);  //   553
//			IsActive(CFuncTank *const this);  //   513
//		}
//		CanFire(CFuncTank *const this);  //   603
//		fabs(double __x);  //   603
//		fabs(double __x);  //   603
//		{
//			BOOL fire;                                    //   605
//			Vector forward;                         //   606
//			UTIL_MakeVectorsPrivate(Vector &vecAngles,
//						float *p_vForward,
//						float *p_vRight,
//						float *p_vUp);  //   607
//			{
//				float length;                         //   611
//				Length(const Vector *const this);  //   611
//				operator*(const Vector *const this,
//						float fl);  //   612
//				edict(CBaseEntity *const this);  //   612
//				operator+(const Vector *const this,
//						const Vector &v);  //   612
//			}
//			BarrelPosition(CFuncTank *const this);  //   621
//		}
//	}
}

/* <8ef79> ../cstrike/dlls/func_tank.cpp:632 */
NOBODY void CFuncTank::AdjustAnglesForBarrel(Vector &angles, float distance)
{
//	{
//		float r2;                                             //   634
//		float d2;                                             //   634
//	}
}

/* <8d4ad> ../cstrike/dlls/func_tank.cpp:656 */
NOBODY void CFuncTank::Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
//	{
//		class CSprite *pSprite;                              //   662
//		AnimateAndDie(CSprite *const this,
//				float framerate);  //   663
//		SetTransparency(CSprite *const this,
//				int rendermode,
//				int r,
//				int g,
//				int b,
//				int a,
//				int fx);  //   664
//		SetScale(CSprite *const this,
//			float scale);  //   666
//	}
//	{
//		class CSprite *pSprite;                              //   670
//		SetTransparency(CSprite *const this,
//				int rendermode,
//				int r,
//				int g,
//				int b,
//				int a,
//				int fx);  //   672
//		AnimateAndDie(CSprite *const this,
//				float framerate);  //   671
//		SetScale(CSprite *const this,
//			float scale);  //   673
//	}
}

/* <8f830> ../cstrike/dlls/func_tank.cpp:684 */
NOBODY void CFuncTank::TankTrace(const Vector &vecStart, const Vector &vecForward, const Vector &vecSpread, TraceResult &tr)
{
//	{
//		float x;                                              //   687
//		float y;                                              //   687
//		float z;                                              //   687
//		Vector vecDir;                                  //   693
//		Vector vecEnd;                                  //   696
//		operator*(float fl,
//				const Vector &v);  //   695
//		operator*(float fl,
//				const Vector &v);  //   695
//		operator+(const Vector *const this,
//				const Vector &v);  //   695
//		operator+(const Vector *const this,
//				const Vector &v);  //   695
//		operator*(const Vector *const this,
//				float fl);  //   698
//		operator+(const Vector *const this,
//				const Vector &v);  //   698
//		edict(CBaseEntity *const this);  //   699
//	}
}

/* <8f9c0> ../cstrike/dlls/func_tank.cpp:703 */
NOBODY void CFuncTank::StartRotSound(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   708
}

/* <8fa1b> ../cstrike/dlls/func_tank.cpp:712 */
NOBODY void CFuncTank::StopRotSound(void)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   715
}

/* <8fa65> ../cstrike/dlls/func_tank.cpp:724 */
LINK_ENTITY_TO_CLASS(func_tank, CFuncTankGun);

/* <8c3d5> ../cstrike/dlls/func_tank.cpp:726 */
NOBODY void CFuncTankGun::Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
//	{
//		int i;                                                //   728
//		{
//			int bulletCount;                              //   735
//		}
//	}
//	Fire(CFuncTankGun *const this,
//		const Vector &barrelEnd,
//		const Vector &forward,
//		entvars_t *pevAttacker);  //   726
}

/* <8fb34> ../cstrike/dlls/func_tank.cpp:785 */
LINK_ENTITY_TO_CLASS(func_tanklaser, CFuncTankLaser);

/* <8e07c> ../cstrike/dlls/func_tank.cpp:793 */
IMPLEMENT_SAVERESTORE(CFuncTankLaser, CFuncTank);

/* <8deed> ../cstrike/dlls/func_tank.cpp:795 */
NOBODY void CFuncTankLaser::Activate_(void)
{
//	GetLaser(CFuncTankLaser *const this);  //   797
//	Activate(CFuncTankLaser *const this);  //   795
}

/* <8e8ca> ../cstrike/dlls/func_tank.cpp:809 */
NOBODY void CFuncTankLaser::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   811
//	KeyValue(CFuncTank *const this,
//		KeyValueData *pkvd);  //   817
//	KeyValue(CFuncTankLaser *const this,
//		KeyValueData *pkvd);  //   809
}

/* <8dd79> ../cstrike/dlls/func_tank.cpp:821 */
NOBODY CLaser *CFuncTankLaser::GetLaser(void)
{
//	{
//		edict_t *pentLaser;                                  //   826
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   828
//		FNullEnt(const edict_t *pent);  //   829
//		FClassnameIs(edict_t *pent,
//				const char *szClassname);  //   832
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   838
//		Instance(edict_t *pent);  //   834
//	}
}

/* <8f809> ../cstrike/dlls/func_tank.cpp:845 */
NOBODY void CFuncTankLaser::Think_(void)
{
}

/* <8df51> ../cstrike/dlls/func_tank.cpp:854 */
NOBODY void CFuncTankLaser::Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
//	{
//		int i;                                                //   856
//		TraceResult tr;                                       //   857
//		GetLaser(CFuncTankLaser *const this);  //   859
//		{
//			int bulletCount;                              //   864
//		}
//	}
//	Fire(CFuncTankLaser *const this,
//		const Vector &barrelEnd,
//		const Vector &forward,
//		entvars_t *pevAttacker);  //   854
}

/* <8fc2f> ../cstrike/dlls/func_tank.cpp:893 */
LINK_ENTITY_TO_CLASS(func_tankrocket, CFuncTankRocket);

/* <8e736> ../cstrike/dlls/func_tank.cpp:895 */
NOBODY void CFuncTankRocket::Precache_(void)
{
//	Precache(CFuncTank *const this);  //   898
}

/* <8d7b6> ../cstrike/dlls/func_tank.cpp:903 */
NOBODY void CFuncTankRocket::Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
//	{
//		int i;                                                //   905
//		{
//			int bulletCount;                              //   909
//			{
//				class CBaseEntity *pRocket;          //   914
//			}
//		}
//	}
//	Fire(CFuncTankRocket *const this,
//		const Vector &barrelEnd,
//		const Vector &forward,
//		entvars_t *pevAttacker);  //   903
}

/* <8fcfe> ../cstrike/dlls/func_tank.cpp:930 */
LINK_ENTITY_TO_CLASS(func_tankmortar, CFuncTankMortar);

/* <8e790> ../cstrike/dlls/func_tank.cpp:933 */
NOBODY void CFuncTankMortar::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   935
//	KeyValue(CFuncTank *const this,
//		KeyValueData *pkvd);  //   941
//	KeyValue(CFuncTankMortar *const this,
//		KeyValueData *pkvd);  //   933
}

/* <8dbfa> ../cstrike/dlls/func_tank.cpp:945 */
NOBODY void CFuncTankMortar::Fire_(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
//	{
//		int bulletCount;                                      //   949
//		{
//			TraceResult tr;                               //   953
//		}
//	}
//	Fire(CFuncTankMortar *const this,
//		const Vector &barrelEnd,
//		const Vector &forward,
//		entvars_t *pevAttacker);  //   945
}

/* <8fdcd> ../cstrike/dlls/func_tank.cpp:988 */
LINK_ENTITY_TO_CLASS(func_tankcontrols, CFuncTankControls);

/* <8d71d> ../cstrike/dlls/func_tank.cpp:995 */
IMPLEMENT_SAVERESTORE(CFuncTankControls, CBaseEntity);

/* <8d310> ../cstrike/dlls/func_tank.cpp:1003 */
NOBODY void CFuncTankControls::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <8d39a> ../cstrike/dlls/func_tank.cpp:1012 */
NOBODY void CFuncTankControls::Think_(void)
{
//	{
//		edict_t *pTarget;                                    //  1014
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1018
//		FNullEnt(const edict_t *pent);  //  1019
//		FNullEnt(const edict_t *pent);  //  1021
//		Instance(edict_t *pent);  //  1027
//	}
}

/* <8d373> ../cstrike/dlls/func_tank.cpp:1030 */
NOBODY void CFuncTankControls::Spawn_(void)
{
}

#ifdef HOOK_GAMEDLL

void CFuncTank::Spawn(void)
{
	Spawn_();
}

void CFuncTank::Precache(void)
{
	Precache_();
}

void CFuncTank::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTank::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTank::Restore(CRestore &restore)
{
	return Restore_(restore);
}

BOOL CFuncTank::OnControls(entvars_t *pevTest)
{
	OnControls_(pevTest);
}

void CFuncTank::Think(void)
{
	Think_();
}

void CFuncTank::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncTank::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

//void CFuncTank::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
//{
//	Fire_(barrelEnd, forward, pevAttacker);
//}

void CFuncTankLaser::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTankLaser::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTankLaser::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncTankLaser::Activate(void)
{
	Activate_();
}

void CFuncTankLaser::Think(void)
{
	Think_();
}

void CFuncTankLaser::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankRocket::Precache(void)
{
	Precache_();
}

void CFuncTankRocket::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankMortar::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CFuncTankMortar::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker)
{
	Fire_(barrelEnd, forward, pevAttacker);
}

void CFuncTankControls::Spawn(void)
{
	Spawn_();
}

int CFuncTankControls::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTankControls::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncTankControls::Think(void)
{
	Think_();
}

void CFuncTankControls::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
