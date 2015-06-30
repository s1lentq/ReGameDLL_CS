#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CEnvGlobal::m_SaveData[] =
{
	DEFINE_FIELD(CEnvGlobal, m_globalstate, FIELD_STRING),
	DEFINE_FIELD(CEnvGlobal, m_triggermode, FIELD_INTEGER),
	DEFINE_FIELD(CEnvGlobal, m_initialstate, FIELD_INTEGER),
};

TYPEDESCRIPTION CMultiSource::m_SaveData[] =
{
	DEFINE_ARRAY(CMultiSource, m_rgEntities, FIELD_EHANDLE, MS_MAX_TARGETS),
	DEFINE_ARRAY(CMultiSource, m_rgTriggered, FIELD_INTEGER, MS_MAX_TARGETS),
	DEFINE_FIELD(CMultiSource, m_iTotal, FIELD_INTEGER),
	DEFINE_FIELD(CMultiSource, m_globalstate, FIELD_STRING),
};

TYPEDESCRIPTION CBaseButton::m_SaveData[] =
{
	DEFINE_FIELD(CBaseButton, m_fStayPushed, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseButton, m_fRotating, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseButton, m_sounds, FIELD_INTEGER),
	DEFINE_FIELD(CBaseButton, m_bLockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_bLockedSentence, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_bUnlockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_bUnlockedSentence, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseButton, m_strChangeTarget, FIELD_STRING),
};

TYPEDESCRIPTION CMomentaryRotButton::m_SaveData[] =
{
	DEFINE_FIELD(CMomentaryRotButton, m_lastUsed, FIELD_INTEGER),
	DEFINE_FIELD(CMomentaryRotButton, m_direction, FIELD_INTEGER),
	DEFINE_FIELD(CMomentaryRotButton, m_returnSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CMomentaryRotButton, m_start, FIELD_VECTOR),
	DEFINE_FIELD(CMomentaryRotButton, m_end, FIELD_VECTOR),
	DEFINE_FIELD(CMomentaryRotButton, m_sounds, FIELD_INTEGER),
};

TYPEDESCRIPTION CEnvSpark::m_SaveData[] =
{
	DEFINE_FIELD(CEnvSpark, m_flDelay, FIELD_FLOAT),
};

#else

TYPEDESCRIPTION (*CEnvGlobal::m_SaveData)[3];
TYPEDESCRIPTION (*CMultiSource::m_SaveData)[4];
TYPEDESCRIPTION (*CBaseButton::m_SaveData)[8];
TYPEDESCRIPTION (*CMomentaryRotButton::m_SaveData)[6];
TYPEDESCRIPTION (*CEnvSpark::m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <260d6> ../cstrike/dlls/buttons.cpp:62 */
IMPLEMENT_SAVERESTORE(CEnvGlobal, CBaseEntity);

/* <272af> ../cstrike/dlls/buttons.cpp:64 */
LINK_ENTITY_TO_CLASS(env_global, CEnvGlobal);

/* <26863> ../cstrike/dlls/buttons.cpp:66 */
NOBODY void CEnvGlobal::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    70
//	FStrEq(const char *sz1,
//		const char *sz2);  //    72
//	KeyValue(CEnvGlobal *const this,
//		KeyValueData *pkvd);  //    66
//	atoi(const char *__nptr);  //    73
}

/* <26486> ../cstrike/dlls/buttons.cpp:80 */
NOBODY void CEnvGlobal::Spawn_(void)
{
//	EntityInTable(CGlobalState::Spawn(//			string_t globalname);  //    89
//	Spawn(CEnvGlobal *const this);  //    80
}

/* <25ee7> ../cstrike/dlls/buttons.cpp:95 */
NOBODY void CEnvGlobal::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		GLOBALESTATE oldState;                                //    97
//		GLOBALESTATE newState;                                //    98
//		EntityInTable(CGlobalState *const this,
//				string_t globalname);  //   124
//	}
}

/* <2616f> ../cstrike/dlls/buttons.cpp:141 */
IMPLEMENT_SAVERESTORE(CMultiSource, CBaseEntity);

/* <27379> ../cstrike/dlls/buttons.cpp:143 */
LINK_ENTITY_TO_CLASS(multisource, CMultiSource);

/* <26d1e> ../cstrike/dlls/buttons.cpp:148 */
NOBODY void CMultiSource::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   150
//	FStrEq(const char *sz1,
//		const char *sz2);  //   151
//	FStrEq(const char *sz1,
//		const char *sz2);  //   152
//	FStrEq(const char *sz1,
//		const char *sz2);  //   153
//	FStrEq(const char *sz1,
//		const char *sz2);  //   154
//	FStrEq(const char *sz1,
//		const char *sz2);  //   155
//	FStrEq(const char *sz1,
//		const char *sz2);  //   157
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   163
}

/* <256e2> ../cstrike/dlls/buttons.cpp:168 */
NOBODY void CMultiSource::Spawn_(void)
{
}

/* <2633b> ../cstrike/dlls/buttons.cpp:179 */
NOBODY void CMultiSource::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int i;                                                //   181
//		{
//			USE_TYPE useType;                             //   203
//		}
//	}
//	Use(CMultiSource *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   179
}

/* <26419> ../cstrike/dlls/buttons.cpp:211 */
NOBODY BOOL CMultiSource::IsTriggered_(CBaseEntity *)
{
//	{
//		int i;                                                //   214
//	}
//	IsTriggered(CMultiSource *const this,
//			class CBaseEntity *);  //   211
}

/* <25d5a> ../cstrike/dlls/buttons.cpp:236 */
NOBODY void CMultiSource::Register(void)
{
//	{
//		edict_t *pentTarget;                                 //   238
//		FNullEnt(const edict_t *pent);  //   249
//		FNullEnt(const edict_t *pent);  //   259
//		{
//			class CBaseEntity *pTarget;                  //   261
//			Instance(edict_t *pent);  //   261
//		}
//		{
//			class CBaseEntity *pTarget;                  //   251
//			Instance(edict_t *pent);  //   251
//		}
//	}
}

/* <262ee> ../cstrike/dlls/buttons.cpp:287 */
IMPLEMENT_SAVERESTORE(CBaseButton, CBaseToggle);

/* <25709> ../cstrike/dlls/buttons.cpp:289 */
NOBODY void CBaseButton::Precache_(void)
{
//	{
//		char *pszSound;                                      //   291
//		ButtonSound(int sound);  //   307
//		ButtonSound(int sound);  //   314
//	}
}

/* <269cb> ../cstrike/dlls/buttons.cpp:355 */
NOBODY void CBaseButton::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   357
//	FStrEq(const char *sz1,
//		const char *sz2);  //   362
//	KeyValue(CBaseButton *const this,
//		KeyValueData *pkvd);  //   355
//	atof(const char *__nptr);  //   364
}

/* <26e90> ../cstrike/dlls/buttons.cpp:394 */
NOBODY int CBaseButton::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		enum BUTTON_CODE code;                                //   396
//
//		ButtonResponseToTouch(CBaseButton *const this);  //   396
//		Instance(entvars_t *pev);  //   403
//		ButtonActivate(CBaseButton *const this);  //   417
//	}
//	TakeDamage(CBaseButton *const this,
//			entvars_t *pevInflictor,
//			entvars_t *pevAttacker,
//			float flDamage,
//			int bitsDamageType);  //   394
}

/* <27443> ../cstrike/dlls/buttons.cpp:439 */
LINK_ENTITY_TO_CLASS(func_button, CBaseButton);

/* <25c2c> ../cstrike/dlls/buttons.cpp:442 */
NOBODY void CBaseButton::Spawn_(void)
{
//	{
//		char *pszSound;                                      //   444
//		ButtonSound(int sound);  //   450
//		fabs(double __x);  //   484
//		fabs(double __x);  //   484
//		fabs(double __x);  //   484
//		operator+(const Vector *const this,
//				const Vector &v);  //   484
//		operator*(const Vector *const this,
//				float fl);  //   484
//		operator-(const Vector *const this,
//				const Vector &v);  //   488
//		Length(const Vector *const this);  //   488
//	}
}

/* <24738> ../cstrike/dlls/buttons.cpp:511 */
NOBODY char *ButtonSound(int sound)
{
//	{
//		char *pszSound;                                      //   513
//	}
}

/* <2752e> ../cstrike/dlls/buttons.cpp:551 */
NOBODY void DoSpark(entvars_t *pev, const Vector &location)
{
//	{
//		Vector tmp;                                     //   553
//		float flVolume;                                       //   556
//		operator*(const Vector *const this,
//				float fl);  //   553
//		operator+(const Vector *const this,
//				const Vector &v);  //   553
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   564
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   563
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   559
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   560
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   561
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   562
//	}
}

/* <277fa> ../cstrike/dlls/buttons.cpp:568 */
NOBODY void CBaseButton::ButtonSpark(void)
{
}

/* <2719b> ../cstrike/dlls/buttons.cpp:580 */
NOBODY void CBaseButton::ButtonUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	ButtonActivate(CBaseButton *const this);  //   599
//	ButtonUse(CBaseButton *const this,
//			class CBaseEntity *pActivator,
//			class CBaseEntity *pCaller,
//			USE_TYPE useType,
//			float value);  //   580
}

/* <27821> ../cstrike/dlls/buttons.cpp:603 */
NOBODY CBaseButton::BUTTON_CODE CBaseButton::ButtonResponseToTouch(void)
{
}

/* <27047> ../cstrike/dlls/buttons.cpp:628 */
NOBODY void CBaseButton::ButtonTouch(CBaseEntity *pOther)
{
//	{
//		enum BUTTON_CODE code;                                //   636
//
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   631
//	}
//	ButtonTouch(CBaseButton *const this,
//			class CBaseEntity *pOther);  //   628
}

/* <27843> ../cstrike/dlls/buttons.cpp:664 */
NOBODY void CBaseButton::ButtonActivate(void)
{
//	Vector(Vector *const this, const Vector &const v);
//	Vector(Vector *const this, const Vector &const v);
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   666
}

/* <263dd> ../cstrike/dlls/buttons.cpp:693 */
NOBODY void CBaseButton::TriggerAndWait(void)
{
//	TriggerAndWait(CBaseButton *const this);  //   693
}

/* <25bb7> ../cstrike/dlls/buttons.cpp:730 */
NOBODY void CBaseButton::ButtonReturn(void)
{
//	Vector(Vector *const this,
//		const Vector &v);  //   739
//	Vector(Vector *const this,
//		const Vector &v);  //   737
}

/* <26658> ../cstrike/dlls/buttons.cpp:748 */
NOBODY void CBaseButton::ButtonBackHome(void)
{
//	{
//		edict_t *pentTarget;                                 //   761
//		{
//			class CBaseEntity *pTarget;                  //   771
//			FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//							const char *pszName);  //   764
//			FNullEnt(const edict_t *pent);  //   766
//			FClassnameIs(edict_t *pent,
//					const char *szClassname);  //   769
//			Instance(edict_t *pent);  //   771
//		}
//	}
}

/* <278a4> ../cstrike/dlls/buttons.cpp:806 */
LINK_ENTITY_TO_CLASS(func_rot_button, CRotButton);

/* <25a06> ../cstrike/dlls/buttons.cpp:808 */
NOBODY void CRotButton::Spawn_(void)
{
//	{
//		char *pszSound;                                      //   810
//		ButtonSound(int sound);  //   815
//		operator*(const Vector *const this,
//				float fl);  //   824
//		operator*(const Vector *const this,
//				float fl);  //   848
//		operator+(const Vector *const this,
//				const Vector &v);  //   848
//	}
}

/* <2577a> ../cstrike/dlls/buttons.cpp:878 */
NOBODY int CMomentaryRotButton::ObjectCaps_(void)
{
//	{
//		int flags;                                            //   880
//	}
}

/* <262a1> ../cstrike/dlls/buttons.cpp:918 */
IMPLEMENT_SAVERESTORE(CMomentaryRotButton, CBaseToggle);

/* <27971> ../cstrike/dlls/buttons.cpp:920 */
LINK_ENTITY_TO_CLASS(momentary_rot_button, CMomentaryRotButton);

/* <25acc> ../cstrike/dlls/buttons.cpp:922 */
NOBODY void CMomentaryRotButton::Spawn_(void)
{
//	{
//		char *pszSound;                                      //   952
//		operator*(const Vector *const this,
//				float fl);  //   931
//		operator+(const Vector *const this,
//				const Vector &v);  //   931
//		ButtonSound(int sound);  //   952
//		operator*(const Vector *const this,
//				float fl);  //   939
//		operator+(const Vector *const this,
//				const Vector &v);  //   939
//	}
}

/* <2678f> ../cstrike/dlls/buttons.cpp:958 */
NOBODY void CMomentaryRotButton::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   960
//	FStrEq(const char *sz1,
//		const char *sz2);  //   965
//	atoi(const char *__nptr);  //   967
//	KeyValue(CMomentaryRotButton *const this,
//		KeyValueData *pkvd);  //   958
}

/* <27a57> ../cstrike/dlls/buttons.cpp:974 */
NOBODY void CMomentaryRotButton::PlaySound(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   976
}

/* <27dc0> ../cstrike/dlls/buttons.cpp:982 */
NOBODY void CMomentaryRotButton::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	UpdateTarget(CMomentaryRotButton *const this,
//			float value);  //   987
}

/* <27c49> ../cstrike/dlls/buttons.cpp:990 */
NOBODY void CMomentaryRotButton::UpdateAllButtons(float value, int start)
{
//	{
//		edict_t *pentTarget;                                 //   993
//		FNullEnt(const edict_t *pent);  //   998
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  1001
//		{
//			class CMomentaryRotButton *pEntity;          //  1003
//			Instance(edict_t *pent);  //  1003
//		}
//	}
}

/* <27ab8> ../cstrike/dlls/buttons.cpp:1015 */
NOBODY void CMomentaryRotButton::UpdateSelf(float value)
{
//	{
//		BOOL fplaysound;                                      //  1017
//		operator*(float fl,
//				const Vector &v);  //  1049
//		PlaySound(CMomentaryRotButton *const this);  //  1041
//	}
}

/* <26550> ../cstrike/dlls/buttons.cpp:1053 */
NOBODY void CMomentaryRotButton::UpdateTarget(float value)
{
//	{
//		edict_t *pentTarget;                                 //  1057
//		{
//			class CBaseEntity *pEntity;                  //  1063
//			FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//							const char *pszName);  //  1060
//			FNullEnt(const edict_t *pent);  //  1061
//			Instance(edict_t *pent);  //  1063
//		}
//	}
}

/* <25f88> ../cstrike/dlls/buttons.cpp:1072 */
NOBODY void CMomentaryRotButton::Off(void)
{
//	Off(CMomentaryRotButton *const this);  //  1072
}

/* <27d60> ../cstrike/dlls/buttons.cpp:1086 */
NOBODY void CMomentaryRotButton::Return(void)
{
//	{
//		float value;                                          //  1088
//		UpdateTarget(CMomentaryRotButton *const this,
//				float value);  //  1092
//	}
}

/* <27bce> ../cstrike/dlls/buttons.cpp:1096 */
NOBODY void CMomentaryRotButton::UpdateSelfReturn(float value)
{
//	operator*(float fl,
//			const Vector &v);  //  1107
}

/* <26122> ../cstrike/dlls/buttons.cpp:1141 */
IMPLEMENT_SAVERESTORE(CEnvSpark, CBaseEntity);

/* <27e77> ../cstrike/dlls/buttons.cpp:1143 */
LINK_ENTITY_TO_CLASS(env_spark, CEnvSpark);

/* <27f44> ../cstrike/dlls/buttons.cpp:1144 */
LINK_ENTITY_TO_CLASS(env_debris, CEnvSpark);

/* <257b7> ../cstrike/dlls/buttons.cpp:1146 */
NOBODY void CEnvSpark::Spawn_(void)
{
}

/* <257de> ../cstrike/dlls/buttons.cpp:1173 */
NOBODY void CEnvSpark::Precache_(void)
{
}

/* <26b97> ../cstrike/dlls/buttons.cpp:1183 */
NOBODY void CEnvSpark::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1185
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1190
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1191
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1192
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1193
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1194
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1195
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //  1198
//	atof(const char *__nptr);  //  1187
}

/* <277d3> ../cstrike/dlls/buttons.cpp:1201 */
NOBODY void CEnvSpark::SparkThink(void)
{
}

/* <25805> ../cstrike/dlls/buttons.cpp:1207 */
NOBODY void CEnvSpark::SparkStart(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <25868> ../cstrike/dlls/buttons.cpp:1214 */
NOBODY void CEnvSpark::SparkStop(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <28011> ../cstrike/dlls/buttons.cpp:1233 */
LINK_ENTITY_TO_CLASS(button_target, CButtonTarget);

/* <258ca> ../cstrike/dlls/buttons.cpp:1235 */
NOBODY void CButtonTarget::Spawn_(void)
{
}

/* <25fc3> ../cstrike/dlls/buttons.cpp:1246 */
NOBODY void CButtonTarget::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CButtonTarget *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  1246
}

/* <258f1> ../cstrike/dlls/buttons.cpp:1258 */
NOBODY int CButtonTarget::ObjectCaps_(void)
{
//	{
//		int caps;                                             //  1260
//	}
}

/* <2592e> ../cstrike/dlls/buttons.cpp:1269 */
NOBODY int CButtonTarget::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	Instance(entvars_t *pev);  //  1271
}

#ifdef HOOK_GAMEDLL

void CBaseButton::Spawn(void)
{
	Spawn_();
}

void CBaseButton::Precache(void)
{
	Precache_();
}

void CBaseButton::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBaseButton::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

int CBaseButton::Save(CSave &save)
{
	return Save_(save);
}

int CBaseButton::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CEnvGlobal::Spawn(void)
{
	Spawn_();
}

void CEnvGlobal::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CEnvGlobal::Save(CSave &save)
{
	return Save_(save);
}

int CEnvGlobal::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CEnvGlobal::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CMultiSource::Spawn(void)
{
	Spawn_();
}

void CMultiSource::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CMultiSource::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

BOOL CMultiSource::IsTriggered(CBaseEntity *pActivator)
{
	return IsTriggered_(pActivator);
}

int CMultiSource::Save(CSave &save)
{
	return Save_(save);
}

int CMultiSource::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRotButton::Spawn(void)
{
	Spawn_();
}

void CMomentaryRotButton::Spawn(void)
{
	Spawn_();
}

void CMomentaryRotButton::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CMomentaryRotButton::Save(CSave &save)
{
	return Save_(save);
}

int CMomentaryRotButton::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CMomentaryRotButton::ObjectCaps(void)
{
	return ObjectCaps_();
}

void CMomentaryRotButton::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CEnvSpark::Spawn(void)
{
	Spawn_();
}

void CEnvSpark::Precache(void)
{
	Precache_();
}

void CEnvSpark::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CEnvSpark::Save(CSave &save)
{
	return Save_(save);
}

int CEnvSpark::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CButtonTarget::Spawn(void)
{
	Spawn_();
}

int CButtonTarget::ObjectCaps(void)
{
	return ObjectCaps_();
}

int CButtonTarget::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

void CButtonTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
