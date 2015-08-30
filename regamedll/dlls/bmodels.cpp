#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncRotating::m_SaveData[] =
{
	DEFINE_FIELD(CFuncRotating, m_flFanFriction, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_flAttenuation, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_flVolume, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_pitch, FIELD_FLOAT),
	DEFINE_FIELD(CFuncRotating, m_sounds, FIELD_INTEGER)
};

TYPEDESCRIPTION CPendulum::m_SaveData[] =
{
	DEFINE_FIELD(CPendulum, m_accel, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_distance, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_time, FIELD_TIME),
	DEFINE_FIELD(CPendulum, m_damp, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_maxSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_dampSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CPendulum, m_center, FIELD_VECTOR),
	DEFINE_FIELD(CPendulum, m_start, FIELD_VECTOR),
};

#else

TYPEDESCRIPTION (*CFuncRotating::pm_SaveData)[5];
TYPEDESCRIPTION (*CPendulum::pm_SaveData)[8];

#endif // HOOK_GAMEDLL

/* <1c36f> ../cstrike/dlls/bmodels.cpp:43 */
Vector VecBModelOrigin(entvars_t *pevBModel)
{
	return pevBModel->absmin + (pevBModel->size * 0.5);
}

/* <1e384> ../cstrike/dlls/bmodels.cpp:63 */
LINK_ENTITY_TO_CLASS(func_wall, CFuncWall);

/* <1d193> ../cstrike/dlls/bmodels.cpp:65 */
NOBODY void CFuncWall::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1d873> ../cstrike/dlls/bmodels.cpp:77 */
NOBODY void CFuncWall::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CFuncWall *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //    77
}

/* <1e44e> ../cstrike/dlls/bmodels.cpp:96 */
LINK_ENTITY_TO_CLASS(func_wall_toggle, CFuncWallToggle);

/* <1e28f> ../cstrike/dlls/bmodels.cpp:98 */
NOBODY void CFuncWallToggle::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(CFuncWall *const this);  //   100
//	TurnOff(CFuncWallToggle *const this);  //   102
}

/* <1e518> ../cstrike/dlls/bmodels.cpp:106 */
NOBODY void CFuncWallToggle::TurnOff(void)
{
}

/* <1e53a> ../cstrike/dlls/bmodels.cpp:114 */
NOBODY void CFuncWallToggle::TurnOn(void)
{
}

/* <1e55c> ../cstrike/dlls/bmodels.cpp:122 */
NOBODY BOOL CFuncWallToggle::IsOn(void)
{
}

/* <1e101> ../cstrike/dlls/bmodels.cpp:130 */
NOBODY void CFuncWallToggle::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int status;                                           //   132
//		IsOn(CFuncWallToggle *const this);  //   132
//		TurnOff(CFuncWallToggle *const this);  //   137
//		TurnOn(CFuncWallToggle *const this);  //   139
//	}
}

/* <1e57d> ../cstrike/dlls/bmodels.cpp:155 */
LINK_ENTITY_TO_CLASS(func_conveyor, CFuncConveyor);

/* <1e1c3> ../cstrike/dlls/bmodels.cpp:156 */
NOBODY void CFuncConveyor::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(CFuncWall *const this);  //   159
//	UpdateSpeed(CFuncConveyor *const this,
//			float speed);  //   174
}

/* <1e647> ../cstrike/dlls/bmodels.cpp:179 */
NOBODY void CFuncConveyor::UpdateSpeed(float speed)
{
//	{
//		int speedCode;                                        //   182
//		fabs(double __x);  //   182
//	}
}

/* <1e021> ../cstrike/dlls/bmodels.cpp:194 */
NOBODY void CFuncConveyor::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	UpdateSpeed(CFuncConveyor *const this,
//			float speed);  //   197
}

/* <1e695> ../cstrike/dlls/bmodels.cpp:217 */
LINK_ENTITY_TO_CLASS(func_illusionary, CFuncIllusionary);

/* <1ddc9> ../cstrike/dlls/bmodels.cpp:219 */
NOBODY void CFuncIllusionary::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   221
//	KeyValue(CFuncIllusionary *const this,
//		KeyValueData *pkvd);  //   219
}

/* <1d1db> ../cstrike/dlls/bmodels.cpp:230 */
NOBODY void CFuncIllusionary::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1e75f> ../cstrike/dlls/bmodels.cpp:262 */
LINK_ENTITY_TO_CLASS(func_monsterclip, CFuncMonsterClip);

/* <1e24f> ../cstrike/dlls/bmodels.cpp:264 */
NOBODY void CFuncMonsterClip::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(CFuncWall *const this);  //   266
}

/* <1e82c> ../cstrike/dlls/bmodels.cpp:313 */
LINK_ENTITY_TO_CLASS(func_rotating, CFuncRotating);

/* <1d826> ../cstrike/dlls/bmodels.cpp:310 */
IMPLEMENT_SAVERESTORE(CFuncRotating, CBaseEntity);

/* <1dc21> ../cstrike/dlls/bmodels.cpp:315 */
NOBODY void CFuncRotating::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   317
//	FStrEq(const char *sz1,
//		const char *sz2);  //   322
//	FStrEq(const char *sz1,
//		const char *sz2);  //   332
//	FStrEq(const char *sz1,
//		const char *sz2);  //   339
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   345
//	{
//		Vector tmp;                                     //   334
//		operator!=(const Vector *const this,
//				const Vector &v);  //   336
//	}
//	atoi(const char *__nptr);  //   341
//	atof(const char *__nptr);  //   324
//	atof(const char *__nptr);  //   319
}

/* <1d5c4> ../cstrike/dlls/bmodels.cpp:362 */
NOBODY void CFuncRotating::__MAKE_VHOOK(Spawn)(void)
{
//	operator*(const Vector ::Spawn(//			float fl);  //   404
}

/* <1d28a> ../cstrike/dlls/bmodels.cpp:447 */
NOBODY void CFuncRotating::__MAKE_VHOOK(Precache)(void)
{
//	{
//		char *szSoundFile;                                   //   449
//		operator!=(const Vector *const this,
//				const Vector &v);  //   502
//	}
}

/* <1dea4> ../cstrike/dlls/bmodels.cpp:517 */
NOBODY void CFuncRotating::HurtTouch(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevOther;                                 //   519
//		Length(const Vector *const this);  //   526
//		VecBModelOrigin(entvars_t *pevBModel);  //   530
//		operator-(const Vector *const this,
//				const Vector &v);  //   530
//		Normalize(const Vector *const this);  //   530
//		operator*(const Vector *const this,
//				float fl);  //   530
//	}
}

/* <1e8f9> ../cstrike/dlls/bmodels.cpp:540 */
NOBODY void CFuncRotating::RampPitchVol(int fUp)
{
//	{
//		Vector vecAVel;                                 //   543
//		vec_t vecCur;                                         //   544
//		vec_t vecFinal;                                       //   545
//		float fpct;                                           //   546
//		float fvol;                                           //   547
//		float fpitch;                                         //   548
//		int pitch;                                            //   549
//		Vector(Vector *const this,
//			const Vector &v);  //   543
//	}
}

/* <1ea74> ../cstrike/dlls/bmodels.cpp:585 */
NOBODY void CFuncRotating::SpinUp(void)
{
//	{
//		Vector vecAVel;                                 //   587
//		operator*(const Vector *const this,
//				float fl);  //   590
//		operator+(const Vector *const this,
//				const Vector &v);  //   590
//		Rotate(CFuncRotating *const this);  //   604
//	}
}

/* <1e9c3> ../cstrike/dlls/bmodels.cpp:615 */
NOBODY void CFuncRotating::SpinDown(void)
{
//	{
//		Vector vecAVel;                                 //   617
//		vec_t vecdir;                                         //   618
//		operator*(const Vector *const this,
//				float fl);  //   622
//		operator-(const Vector *const this,
//				const Vector &v);  //   622
//		Rotate(CFuncRotating *const this);  //   645
//	}
}

/* <1d304> ../cstrike/dlls/bmodels.cpp:653 */
NOBODY void CFuncRotating::Rotate(void)
{
}

/* <1d60e> ../cstrike/dlls/bmodels.cpp:661 */
NOBODY void CFuncRotating::RotatingUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	operator!=(const Vector *const this,
//			const Vector &v);  //   667
//	operator!=(const Vector *const this,
//			const Vector &v);  //   683
//	operator*(const Vector *const this,
//			float fl);  //   694
//	Rotate(CFuncRotating *const this);  //   697
}

/* <1d325> ../cstrike/dlls/bmodels.cpp:706 */
NOBODY void CFuncRotating::__MAKE_VHOOK(Blocked)(CBaseEntity *pOther)
{
}

/* <1eb14> ../cstrike/dlls/bmodels.cpp:747 */
LINK_ENTITY_TO_CLASS(func_pendulum, CPendulum);

/* <1d7d9> ../cstrike/dlls/bmodels.cpp:761 */
IMPLEMENT_SAVERESTORE(CPendulum, CBaseEntity);

/* <1db2a> ../cstrike/dlls/bmodels.cpp:765 */
NOBODY void CPendulum::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   767
//	FStrEq(const char *sz1,
//		const char *sz2);  //   772
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   778
//	atof(const char *__nptr);  //   769
//	KeyValue(CPendulum *const this,
//		KeyValueData *pkvd);  //   765
}

/* <1d9c7> ../cstrike/dlls/bmodels.cpp:782 */
NOBODY void CPendulum::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(CPendulum *const this);  //   782
}

/* <1d8ec> ../cstrike/dlls/bmodels.cpp:821 */
NOBODY void CPendulum::PendulumUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		float delta;                                          //   827
//	}
//	PendulumUse(CPendulum *const this,
//			class CBaseEntity *pActivator,
//			class CBaseEntity *pCaller,
//			USE_TYPE useType,
//			float value);  //   821
}

/* <1d381> ../cstrike/dlls/bmodels.cpp:852 */
NOBODY void CPendulum::Stop(void)
{
}

/* <1d3a7> ../cstrike/dlls/bmodels.cpp:861 */
NOBODY void CPendulum::__MAKE_VHOOK(Blocked)(CBaseEntity *pOther)
{
}

/* <1d533> ../cstrike/dlls/bmodels.cpp:867 */
NOBODY void CPendulum::Swing(void)
{
//	{
//		float delta;                                          //   869
//		float dt;                                             //   869
//		operator*(float fl,
//				const Vector &v);  //   885
//	}
}

/* <1d3f5> ../cstrike/dlls/bmodels.cpp:909 */
NOBODY void CPendulum::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevOther;                                 //   911
//		float damage;                                         //   921
//		VecBModelOrigin(entvars_t *pevBModel);  //   928
//		operator-(const Vector *const this,
//				const Vector &v);  //   928
//		Normalize(const Vector *const this);  //   928
//		operator*(const Vector *const this,
//				float fl);  //   928
//	}
}

/* <1da85> ../cstrike/dlls/bmodels.cpp:931 */
NOBODY void CPendulum::RopeTouch(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevOther;                                 //   933
//		edict(CBaseEntity *const this);  //   946
//	}
//	RopeTouch(CPendulum *const this,
//			class CBaseEntity *pOther);  //   931
}

#ifdef HOOK_GAMEDLL

void CFuncWall::Spawn(void)
{
	Spawn_();
}

void CFuncWall::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncWallToggle::Spawn(void)
{
	Spawn_();
}

void CFuncWallToggle::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncConveyor::Spawn(void)
{
	Spawn_();
}

void CFuncConveyor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncIllusionary::Spawn(void)
{
	Spawn_();
}

void CFuncIllusionary::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CFuncMonsterClip::Spawn(void)
{
	Spawn_();
}

void CFuncRotating::Spawn(void)
{
	Spawn_();
}

void CFuncRotating::Precache(void)
{
	Precache_();
}

void CFuncRotating::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncRotating::Save(CSave &save)
{
	return Save_(save);
}

int CFuncRotating::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncRotating::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

void CPendulum::Spawn(void)
{
	Spawn_();
}

void CPendulum::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CPendulum::Save(CSave &save)
{
	return Save_(save);
}

int CPendulum::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CPendulum::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CPendulum::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

#endif // HOOK_GAMEDLL
