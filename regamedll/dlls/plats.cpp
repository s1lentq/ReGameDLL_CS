#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBasePlatTrain::m_SaveData[] =
{
	DEFINE_FIELD(CBasePlatTrain, m_bMoveSnd, FIELD_CHARACTER),
	DEFINE_FIELD(CBasePlatTrain, m_bStopSnd, FIELD_CHARACTER),
	DEFINE_FIELD(CBasePlatTrain, m_volume, FIELD_FLOAT),
};

TYPEDESCRIPTION CFuncPlatRot::m_SaveData[] =
{
	DEFINE_FIELD(CFuncPlatRot, m_end, FIELD_VECTOR),
	DEFINE_FIELD(CFuncPlatRot, m_start, FIELD_VECTOR),
};

TYPEDESCRIPTION CFuncTrain::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTrain, m_sounds, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTrain, m_pevCurrentTarget, FIELD_EVARS),
	DEFINE_FIELD(CFuncTrain, m_activated, FIELD_BOOLEAN),
};

TYPEDESCRIPTION CFuncTrackTrain::m_SaveData[] =
{
	DEFINE_FIELD(CFuncTrackTrain, m_ppath, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncTrackTrain, m_length, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_height, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_speed, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_dir, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_startSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_controlMins, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTrackTrain, m_controlMaxs, FIELD_VECTOR),
	DEFINE_FIELD(CFuncTrackTrain, m_sounds, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTrackTrain, m_flVolume, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_flBank, FIELD_FLOAT),
	DEFINE_FIELD(CFuncTrackTrain, m_oldSpeed, FIELD_FLOAT),
};

TYPEDESCRIPTION CFuncTrackChange::m_SaveData[] =
{
	DEFINE_GLOBAL_FIELD(CFuncTrackChange, m_trackTop, FIELD_CLASSPTR),
	DEFINE_GLOBAL_FIELD(CFuncTrackChange, m_trackBottom, FIELD_CLASSPTR),
	DEFINE_GLOBAL_FIELD(CFuncTrackChange, m_train, FIELD_CLASSPTR),
	DEFINE_GLOBAL_FIELD(CFuncTrackChange, m_trackTopName, FIELD_STRING),
	DEFINE_GLOBAL_FIELD(CFuncTrackChange, m_trackBottomName, FIELD_STRING),
	DEFINE_GLOBAL_FIELD(CFuncTrackChange, m_trainName, FIELD_STRING),
	DEFINE_FIELD(CFuncTrackChange, m_code, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTrackChange, m_targetState, FIELD_INTEGER),
	DEFINE_FIELD(CFuncTrackChange, m_use, FIELD_INTEGER),
};

TYPEDESCRIPTION CGunTarget::m_SaveData[] =
{
	DEFINE_FIELD(CGunTarget, m_on, FIELD_BOOLEAN),
};

#else

TYPEDESCRIPTION (*CBasePlatTrain::m_SaveData)[3];
TYPEDESCRIPTION (*CFuncPlatRot::m_SaveData)[2];
TYPEDESCRIPTION (*CFuncTrain::m_SaveData)[3];
TYPEDESCRIPTION (*CFuncTrackTrain::m_SaveData)[12];
TYPEDESCRIPTION (*CFuncTrackChange::m_SaveData)[9];
TYPEDESCRIPTION (*CGunTarget::m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <12d629> ../cstrike/dlls/plats.cpp:36 */
NOBODY int CBasePlatTrain::ObjectCaps_(void)
{
	return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
}

/* <12d64f> ../cstrike/dlls/plats.cpp:41 */
NOBODY BOOL CBasePlatTrain::IsTogglePlat_(void)
{
	return (pev->spawnflags & SF_PLAT_TOGGLE) != 0;
}

/* <12e11a> ../cstrike/dlls/plats.cpp:59 */
IMPLEMENT_SAVERESTORE(CBasePlatTrain, CBaseToggle);

/* <12ea9b> ../cstrike/dlls/plats.cpp:61 */
NOBODY void CBasePlatTrain::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    73
//	FStrEq(const char *sz1,
//		const char *sz2);  //    78
//	FStrEq(const char *sz1,
//		const char *sz2);  //    83
//	FStrEq(const char *sz1,
//		const char *sz2);  //    88
//	FStrEq(const char *sz1,
//		const char *sz2);  //    93
//	atof(const char *__nptr);  //    75
//	atof(const char *__nptr);  //    85
//	atof(const char *__nptr);  //    80
//	atof(const char *__nptr);  //    95
//	atof(const char *__nptr);  //    90
}


/* <12d675> ../cstrike/dlls/plats.cpp:105 */
NOBODY void CBasePlatTrain::Precache_(void)
{
}

/* <12d69c> ../cstrike/dlls/plats.cpp:235 */
NOBODY void CFuncPlat::CallGoDown(void)
{
	GoDown();
}

/* <12d6c2> ../cstrike/dlls/plats.cpp:236 */
NOBODY void CFuncPlat::CallHitTop(void)
{
	HitTop();
}

/* <12d6e8> ../cstrike/dlls/plats.cpp:237 */
NOBODY void CFuncPlat::CallHitBottom(void)
{
	HitBottom();
}

/* <130666> ../cstrike/dlls/plats.cpp:244 */
LINK_ENTITY_TO_CLASS(func_plat, CFuncPlat);

/* <130730> ../cstrike/dlls/plats.cpp:275 */
NOBODY void CFuncPlat::Setup(void)
{
}

/* <13088e> ../cstrike/dlls/plats.cpp:309 */
NOBODY void CFuncPlat::Precache_(void)
{
//	PlatSpawnInsideTrigger(entvars_t *pevPlatform);  //   315
}

/* <130757> ../cstrike/dlls/plats.cpp:319 */
NOBODY void CFuncPlat::Spawn_(void)
{
//	Spawn(CFuncPlat *const this);  //   319
}

/* <12c8bb> ../cstrike/dlls/plats.cpp:342 */
NOBODY void PlatSpawnInsideTrigger(entvars_t *pevPlatform)
{
}

/* <130792> ../cstrike/dlls/plats.cpp:351 */
NOBODY void CPlatTrigger::SpawnInsideTrigger(CFuncPlat *pPlatform)
{
//	{
//		Vector vecTMin;                                 //   360
//		Vector vecTMax;                                 //   361
//		operator+(const Vector *const this,
//				const Vector &v);  //   360
//		operator+(const Vector *const this,
//				const Vector &v);  //   361
//	}
}

/* <12e7e7> ../cstrike/dlls/plats.cpp:380 */
NOBODY void CPlatTrigger::Touch_(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevToucher;                               //   383
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   384
//	}
//	Touch(CPlatTrigger *const this,
//		class CBaseEntity *pOther);  //   380
}

/* <12df02> ../cstrike/dlls/plats.cpp:403 */
NOBODY void CFuncPlat::PlatUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		BOOL on;                                              //   408
//	}
//	PlatUse(CFuncPlat *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   403
}

/* <12e49b> ../cstrike/dlls/plats.cpp:431 */
NOBODY void CFuncPlat::GoDown_(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   434
//	Vector(Vector *const this,
//		const Vector &v);  //   439
}

/* <12f381> ../cstrike/dlls/plats.cpp:446 */
NOBODY void CFuncPlat::HitBottom_(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   452
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   449
}

/* <12e52d> ../cstrike/dlls/plats.cpp:462 */
NOBODY void CFuncPlat::GoUp_(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   465
//	Vector(Vector *const this,
//		const Vector &v);  //   470
}

/* <12f452> ../cstrike/dlls/plats.cpp:477 */
NOBODY void CFuncPlat::HitTop_(void)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   480
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   483
}

/* <12f524> ../cstrike/dlls/plats.cpp:497 */
NOBODY void CFuncPlat::Blocked_(CBaseEntity *pOther)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   504
}

/* <130a7b> ../cstrike/dlls/plats.cpp:533 */
LINK_ENTITY_TO_CLASS(func_platrot, CFuncPlatRot);

/* <12f1ce> ../cstrike/dlls/plats.cpp:540 */
IMPLEMENT_SAVERESTORE(CFuncPlatRot, CFuncPlat);

/* <130b48> ../cstrike/dlls/plats.cpp:543 */
NOBODY void CFuncPlatRot::SetupRotation(void)
{
//	operator*(const Vector ::SetupRotation(//			float fl);  //   549
//	operator+(const Vector *const this,
//			const Vector &v);  //   549
}

/* <130bc4> ../cstrike/dlls/plats.cpp:563 */
NOBODY void CFuncPlatRot::Spawn_(void)
{
//	Spawn(CFuncPlat *const this);  //   565
}

/* <12fe63> ../cstrike/dlls/plats.cpp:569 */
NOBODY void CFuncPlatRot::GoDown_(void)
{
//	RotMove(CFuncPlatRot::GoDown(//		Vector &destAngle,
//		float time);  //   572
}

/* <12f430> ../cstrike/dlls/plats.cpp:579 */
NOBODY void CFuncPlatRot::HitBottom_(void)
{
}

/* <12fdad> ../cstrike/dlls/plats.cpp:590 */
NOBODY void CFuncPlatRot::GoUp_(void)
{
//	RotMove(CFuncPlatRot::GoUp(//		Vector &destAngle,
//		float time);  //   593
}

/* <12f502> ../cstrike/dlls/plats.cpp:600 */
NOBODY void CFuncPlatRot::HitTop_(void)
{
}

/* <130c54> ../cstrike/dlls/plats.cpp:608 */
NOBODY void CFuncPlatRot::RotMove(Vector &destAngle, float time)
{
//	{
//		Vector vecDestDelta;                            //   611
//		operator-(const Vector *const this,
//				const Vector &v);  //   611
//		operator/(const Vector *const this,
//				float fl);  //   615
//	}
}

/* <130ce8> ../cstrike/dlls/plats.cpp:657 */
LINK_ENTITY_TO_CLASS(func_train, CFuncTrain);

/* <12f13d> ../cstrike/dlls/plats.cpp:665 */
IMPLEMENT_SAVERESTORE(CFuncTrain, CBasePlatTrain);

/* <130390> ../cstrike/dlls/plats.cpp:668 */
NOBODY void CFuncTrain::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   670
//	KeyValue(CBasePlatTrain *const this,
//		KeyValueData *pkvd);  //   676
//	KeyValue(CFuncTrain *const this,
//		KeyValueData *pkvd);  //   668
}

/* <12de63> ../cstrike/dlls/plats.cpp:679 */
NOBODY void CFuncTrain::Blocked_(CBaseEntity *pOther)
{
//	Blocked(CFuncTrain *const this,
//		class CBaseEntity *pOther);  //   679
}


/* <12fa23> ../cstrike/dlls/plats.cpp:691 */
NOBODY void CFuncTrain::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   708
}

/* <12f914> ../cstrike/dlls/plats.cpp:713 */
NOBODY void CFuncTrain::Wait(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   734
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   732
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   747
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   745
}

/* <12f6a8> ../cstrike/dlls/plats.cpp:760 */
NOBODY void CFuncTrain::Next(void)
{
//	{
//		class CBaseEntity *pTarg;                            //   762
//		edict(CBaseEntity *const this);  //   791
//		operator+(const Vector *const this,
//				const Vector &v);  //   813
//		operator*(const Vector *const this,
//				float fl);  //   813
//		operator-(const Vector *const this,
//				const Vector &v);  //   813
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   774
//		STOP_SOUND(edict_t *entity,
//				int channel,
//				const char *sample);  //   808
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   810
//		operator+(const Vector *const this,
//				const Vector &v);  //   797
//		operator*(const Vector *const this,
//				float fl);  //   797
//		operator-(const Vector *const this,
//				const Vector &v);  //   797
//		STOP_SOUND(edict_t *entity,
//				int channel,
//				const char *sample);  //   771
//	}
}

/* <12e1fd> ../cstrike/dlls/plats.cpp:818 */
NOBODY void CFuncTrain::Activate_(void)
{
//	{
//		entvars_t *pevTarg;                                  //   824
//	}
//	Activate(CFuncTrain *const this);  //   818
}

/* <12dcad> ../cstrike/dlls/plats.cpp:852 */
NOBODY void CFuncTrain::Spawn_(void)
{
}

/* <12dab7> ../cstrike/dlls/plats.cpp:886 */
NOBODY void CFuncTrain::Restart_(void)
{
}

/* <12d734> ../cstrike/dlls/plats.cpp:907 */
NOBODY void CFuncTrain::Precache_(void)
{
}

/* <12e166> ../cstrike/dlls/plats.cpp:913 */
NOBODY void CFuncTrain::OverrideReset_(void)
{
//	{
//		class CBaseEntity *pTarg;                            //   915
//		operator!=(const Vector *const this,
//				const Vector &v);  //   918
//	}
//	OverrideReset(CFuncTrain *const this);  //   913
}

/* <12e0cd> ../cstrike/dlls/plats.cpp:961 */
IMPLEMENT_SAVERESTORE(CFuncTrackTrain, CBaseEntity);

/* <130db5> ../cstrike/dlls/plats.cpp:962 */
LINK_ENTITY_TO_CLASS(func_tracktrain, CFuncTrackTrain);

/* <12e88e> ../cstrike/dlls/plats.cpp:964 */
NOBODY void CFuncTrackTrain::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   966
//	FStrEq(const char *sz1,
//		const char *sz2);  //   971
//	KeyValue(CFuncTrackTrain *const this,
//		KeyValueData *pkvd);  //   964
//	atof(const char *__nptr);  //   968
//	atof(const char *__nptr);  //   973
}

/* <130e82> ../cstrike/dlls/plats.cpp:1002 */
NOBODY void CFuncTrackTrain::NextThink(float thinkTime, BOOL alwaysThink)
{
}

/* <12ee6d> ../cstrike/dlls/plats.cpp:1013 */
NOBODY void CFuncTrackTrain::Blocked_(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevOther;                                 //  1015
//		VARS(edict_t *pent);  //  1018
//		operator-(const Vector *const this,
//				const Vector &v);  //  1028
//		Normalize(const Vector *const this);  //  1028
//		operator*(const Vector *const this,
//				float fl);  //  1028
//		{
//			float deltaSpeed;                             //  1020
//			fabs(double __x);  //  1020
//		}
//	}
}

/* <1312c7> ../cstrike/dlls/plats.cpp:1038 */
NOBODY void CFuncTrackTrain::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		float delta;                                          //  1062
//	}
}

/* <12bc89> ../cstrike/dlls/plats.cpp:1082 */
NOBODY float Fix(float angle)
{
	while (angle < 0)
		angle += 360;
	while (angle > 360)
		angle -= 360;

	return angle;
}

/* <130f04> ../cstrike/dlls/plats.cpp:1093 */
NOBODY void FixupAngles(Vector &v)
{
	v.x = Fix(v.x);
	v.y = Fix(v.y);
	v.z = Fix(v.z);
}

/* <130eb3> ../cstrike/dlls/plats.cpp:1104 */
NOBODY void CFuncTrackTrain::StopSound(void)
{
//	{
//		short unsigned int us_encode;                         //  1109
//		short unsigned int us_sound;                          //  1110
//	}
}

/* <12e31d> ../cstrike/dlls/plats.cpp:1130 */
NOBODY void CFuncTrackTrain::UpdateSound(void)
{
//	{
//		float flpitch;                                        //  1132
//		{
//			short unsigned int us_encode;                 //  1157
//			short unsigned int us_sound;                  //  1158
//			short unsigned int us_pitch;                  //  1159
//			short unsigned int us_volume;                 //  1160
//		}
//	}
}

/* <130f1c> ../cstrike/dlls/plats.cpp:1171 */
NOBODY void CFuncTrackTrain::Next(void)
{
//	{
//		float time;                                           //  1173
//		Vector nextPos;                                 //  1195
//		class CPathTrack *pnext;                             //  1198
//		Vector nextFront;                               //  1202
//		Vector delta;                                   //  1211
//		Vector angles;                                  //  1212
//		float vy;                                             //  1223
//		float vx;                                             //  1223
//		UpdateSound(CFuncTrackTrain *const this);  //  1193
//		Vector(Vector *const this,
//			const Vector &v);  //  1195
//		operator-(const Vector *const this,
//				const Vector &v);  //  1201
//		operator*(const Vector *const this,
//				float fl);  //  1201
//		Vector(Vector *const this,
//			const Vector &v);  //  1202
//		operator-(const Vector *const this,
//				const Vector &v);  //  1211
//		FixupAngles(Vector &v);  //  1217
//		FixupAngles(Vector &v);  //  1218
//		{
//			class CPathTrack *pFire;                     //  1247
//		}
//		NextThink(CFuncTrackTrain *const this,
//				float thinkTime,
//				BOOL alwaysThink);  //  1276
//		{
//			float distance;                               //  1283
//			operator-(const Vector *const this,
//					const Vector &v);  //  1281
//			Length(const Vector *const this);  //  1283
//			operator*(const Vector *const this,
//					float fl);  //  1296
//			NextThink(CFuncTrackTrain *const this,
//					float thinkTime,
//					BOOL alwaysThink);  //  1298
//		}
//	}
}

/* <12de16> ../cstrike/dlls/plats.cpp:1308 */
NOBODY void CFuncTrackTrain::DeadEnd(void)
{
//	{
//		class CPathTrack *pTrack;                            //  1311
//		class CPathTrack *pNext;                             //  1311
//	}
}

/* <131370> ../cstrike/dlls/plats.cpp:1354 */
NOBODY void CFuncTrackTrain::SetControls(entvars_t *pevControls)
{
//	{
//		Vector offset;                                  //  1356
//		operator-(const Vector *const this,
//				const Vector &v);  //  1356
//		operator+(const Vector *const this,
//				const Vector &v);  //  1358
//		operator+(const Vector *const this,
//				const Vector &v);  //  1359
//	}
}

/* <12dd23> ../cstrike/dlls/plats.cpp:1363 */
NOBODY BOOL CFuncTrackTrain::OnControls_(entvars_t *pevTest)
{
//	{
//		Vector offset;                                  //  1365
//		Vector local;                                   //  1372
//		operator-(const Vector *const this,
//				const Vector &v);  //  1365
//		DotProduct(Vector &a,
//				const Vector &b);  //  1373
//		DotProduct(Vector &a,
//				const Vector &b);  //  1374
//		DotProduct(Vector &a,
//				const Vector &b);  //  1375
//	}
}

/* <12e636> ../cstrike/dlls/plats.cpp:1385 */
NOBODY void CFuncTrackTrain::Find(void)
{
//	{
//		entvars_t *pevTarget;                                //  1391
//		Vector nextPos;                                 //  1399
//		Vector look;                                    //  1402
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1387
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  1392
//		Vector(Vector *const this,
//			const Vector &v);  //  1399
//		Vector(Vector *const this,
//			const Vector &v);  //  1402
//		operator-(const Vector *const this,
//				const Vector &v);  //  1407
//		NextThink(CFuncTrackTrain *const this,
//				float thinkTime,
//				BOOL alwaysThink);  //  1414
//		UpdateSound(CFuncTrackTrain *const this);  //  1418
//	}
}

/* <12ecdd> ../cstrike/dlls/plats.cpp:1422 */
NOBODY void CFuncTrackTrain::NearestPath(void)
{
//	{
//		class CBaseEntity *pTrack;                           //  1424
//		class CBaseEntity *pNearest;                         //  1425
//		float dist;                                           //  1426
//		float closest;                                        //  1426
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  1433
//		operator-(const Vector *const this,
//				const Vector &v);  //  1435
//		Length(const Vector *const this);  //  1435
//		operator-(const Vector *const this,
//				const Vector &v);  //  1456
//		Length(const Vector *const this);  //  1456
//		operator-(const Vector *const this,
//				const Vector &v);  //  1456
//		Length(const Vector *const this);  //  1456
//		NextThink(CFuncTrackTrain *const this,
//				float thinkTime,
//				BOOL alwaysThink);  //  1464
//	}
}

/* <12d75a> ../cstrike/dlls/plats.cpp:1470 */
NOBODY void CFuncTrackTrain::OverrideReset_(void)
{
//	NextThink(CFuncTrackTrain::OverrideReset(//			float thinkTime,
//			BOOL alwaysThink);  //  1472
}

/* <131434> ../cstrike/dlls/plats.cpp:1477 */
NOBODY CFuncTrackTrain *CFuncTrackTrain::Instance(edict_t *pent)
{
//	FClassnameIs(edict_t *pent,
//			const char *szClassname);  //  1479
//	GET_PRIVATE(edict_t *pent);  //  1480
}

/* <12dcd4> ../cstrike/dlls/plats.cpp:1495 */
NOBODY void CFuncTrackTrain::Spawn_(void)
{
//	NextThink(CFuncTrackTrain::Spawn(//			float thinkTime,
//			BOOL alwaysThink);  //  1533
}

/* <12dbdf> ../cstrike/dlls/plats.cpp:1539 */
NOBODY void CFuncTrackTrain::Restart_(void)
{
//	NextThink(CFuncTrackTrain::Restart(//			float thinkTime,
//			BOOL alwaysThink);  //  1557
}

/* <12d7a5> ../cstrike/dlls/plats.cpp:1562 */
NOBODY void CFuncTrackTrain::Precache_(void)
{
}

/* <1314d9> ../cstrike/dlls/plats.cpp:1595 */
LINK_ENTITY_TO_CLASS(func_traincontrols, CFuncTrainControls);

/* <12d7cc> ../cstrike/dlls/plats.cpp:1591 */
NOBODY int CFuncTrainControls::ObjectCaps_(void)
{
	return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
}

/* <12fb10> ../cstrike/dlls/plats.cpp:1598 */
NOBODY void CFuncTrainControls::Find(void)
{
//	{
//		edict_t *pTarget;                                    //  1600
//		class CFuncTrackTrain *ptrain;                       //  1613
//		Instance(edict_t *pent);  //  1613
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1604
//		FNullEnt(const edict_t *pent);  //  1605
//		FNullEnt(const edict_t *pent);  //  1607
//		SetControls(CFuncTrackTrain *const this,
//				entvars_t *pevControls);  //  1614
//		FClassnameIs(edict_t *pent,
//				const char *szClassname);  //  1605
//	}
}

/* <12dc86> ../cstrike/dlls/plats.cpp:1619 */
NOBODY void CFuncTrainControls::Spawn_(void)
{
}

/* <12d7f2> ../cstrike/dlls/plats.cpp:1673 */
NOBODY BOOL CFuncTrackChange::IsTogglePlat_(void)
{
	return TRUE;
}

/* <1315a6> ../cstrike/dlls/plats.cpp:1698 */
LINK_ENTITY_TO_CLASS(func_trackchange, CFuncTrackChange);

/* <12ef8f> ../cstrike/dlls/plats.cpp:1713 */
IMPLEMENT_SAVERESTORE(CFuncTrackChange, CFuncPlatRot);

/* <130c1d> ../cstrike/dlls/plats.cpp:1715 */
NOBODY void CFuncTrackChange::Spawn_(void)
{
//	EnableUse(CFuncTrackChange *const this);  //  1738
}

/* <130a3b> ../cstrike/dlls/plats.cpp:1744 */
NOBODY void CFuncTrackChange::Precache_(void)
{
//	Precache(CFuncPlat *const this);  //  1749
}

/* <12d818> ../cstrike/dlls/plats.cpp:1753 */
NOBODY void CFuncTrackChange::Touch_(CBaseEntity *pOther)
{
}

/* <1304ca> ../cstrike/dlls/plats.cpp:1758 */
NOBODY void CFuncTrackChange::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1760
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1765
//	KeyValue(CFuncTrackChange *const this,
//		KeyValueData *pkvd);  //  1758
}

/* <12d84d> ../cstrike/dlls/plats.cpp:1782 */
NOBODY void CFuncTrackChange::OverrideReset_(void)
{
}

/* <12ff19> ../cstrike/dlls/plats.cpp:1788 */
NOBODY void CFuncTrackChange::Find(void)
{
//	{
//		edict_t *target;                                     //  1791
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1793
//		FNullEnt(const edict_t *pent);  //  1794
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1797
//		FNullEnt(const edict_t *pent);  //  1798
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1801
//		FNullEnt(const edict_t *pent);  //  1802
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1820
//		{
//			Vector center;                          //  1810
//			FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//							const char *pszName);  //  1804
//			Instance(edict_t *pent);  //  1804
//			operator+(const Vector *const this,
//					const Vector &v);  //  1810
//			operator*(const Vector *const this,
//					float fl);  //  1810
//			Vector(Vector *const this,
//				const Vector &v);  //  1811
//			Vector(Vector *const this,
//				const Vector &v);  //  1812
//		}
//	}
}

/* <131673> ../cstrike/dlls/plats.cpp:1832 */
NOBODY TRAIN_CODE CFuncTrackChange::EvaluateTrain(CPathTrack *pcurrent)
{
//	{
//		Vector dist;                                    //  1844
//		float length;                                         //  1845
//	}
//	EvaluateTrain(CFuncTrackChange *const this,
//			class CPathTrack *pcurrent);  //  1832
}

/* <1317f9> ../cstrike/dlls/plats.cpp:1858 */
NOBODY void CFuncTrackChange::UpdateTrain(Vector &dest)
{
//	{
//		float time;                                           //  1860
//		Vector offset;                                  //  1870
//		Vector delta;                                   //  1871
//		Vector local;                                   //  1874
//		NextThink(CFuncTrackTrain *const this,
//				float thinkTime,
//				BOOL alwaysThink);  //  1864
//		operator-(const Vector *const this,
//				const Vector &v);  //  1870
//		operator-(const Vector *const this,
//				const Vector &v);  //  1871
//		DotProduct(Vector &a,
//				const Vector &b);  //  1877
//		operator-(const Vector *const this,
//				const Vector &v);  //  1879
//		operator*(const Vector *const this,
//				float fl);  //  1880
//		operator+(const Vector *const this,
//				const Vector &v);  //  1880
//		DotProduct(Vector &a,
//				const Vector &b);  //  1876
//		DotProduct(Vector &a,
//				const Vector &b);  //  1875
//	}
}

/* <131ade> ../cstrike/dlls/plats.cpp:1883 */
NOBODY void CFuncTrackChange::GoDown_(void)
{
//	GoDown(CFuncTrackChange *const this);  //  1883
}

/* <1319f9> ../cstrike/dlls/plats.cpp:1919 */
NOBODY void CFuncTrackChange::GoUp_(void)
{
//	GoUp(CFuncTrackChange *const this);  //  1919
}

/* <12deb0> ../cstrike/dlls/plats.cpp:1954 */
NOBODY void CFuncTrackChange::UpdateAutoTargets_(int toggleState)
{
//	UpdateAutoTargets(CFuncTrackChange *const this,
//				int toggleState);  //  1954
}

/* <131725> ../cstrike/dlls/plats.cpp:1971 */
NOBODY void CFuncTrackChange::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CFuncTrackChange *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  1971
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //  1986
}

/* <12f618> ../cstrike/dlls/plats.cpp:2005 */
NOBODY void CFuncTrackChange::HitBottom_(void)
{
//	HitBottom(CFuncPlatRot *const this);  //  2007
//	EnableUse(CFuncTrackChange *const this);  //  2018
//	SetTrack(CFuncTrackTrain *const this,
//		class CPathTrack *track);  //  2011
}

/* <12f588> ../cstrike/dlls/plats.cpp:2025 */
NOBODY void CFuncTrackChange::HitTop_(void)
{
//	HitTop(CFuncPlatRot *const this);  //  2027
//	EnableUse(CFuncTrackChange *const this);  //  2038
//	SetTrack(CFuncTrackTrain *const this,
//		class CPathTrack *track);  //  2031
}

/* <131bc3> ../cstrike/dlls/plats.cpp:2050 */
LINK_ENTITY_TO_CLASS(func_trackautochange, CFuncTrackAuto);

/* <12dc2a> ../cstrike/dlls/plats.cpp:2053 */
NOBODY void CFuncTrackAuto::UpdateAutoTargets_(int toggleState)
{
//	{
//		class CPathTrack *pTarget;                           //  2055
//		class CPathTrack *pNextTarget;                       //  2055
//	}
}

/* <1301f9> ../cstrike/dlls/plats.cpp:2083 */
NOBODY void CFuncTrackAuto::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CPathTrack *pTarget;                           //  2085
//	}
//	Use(CFuncTrackAuto *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  2083
}

/* <12d873> ../cstrike/dlls/plats.cpp:2146 */
NOBODY int CGunTarget::BloodColor_(void)
{
	return DONT_BLEED;
}

/* <12d899> ../cstrike/dlls/plats.cpp:2147 */
NOBODY int CGunTarget::Classify_(void)
{
	return CLASS_MACHINE;
}

/* <12d8bf> ../cstrike/dlls/plats.cpp:2150 */
NOBODY Vector CGunTarget::BodyTarget_(const Vector &posSrc)
{
	return pev->origin;
//	Vector(Vector *const this,
//		const Vector &v);  //  2150
}

/* <12d921> ../cstrike/dlls/plats.cpp:2152 */
NOBODY int CGunTarget::ObjectCaps_(void)
{
	return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
}

/* <131c90> ../cstrike/dlls/plats.cpp:2163 */
LINK_ENTITY_TO_CLASS(func_guntarget, CGunTarget);

/* <12e080> ../cstrike/dlls/plats.cpp:2170 */
IMPLEMENT_SAVERESTORE(CGunTarget, CBaseMonster);

/* <12dbb8> ../cstrike/dlls/plats.cpp:2173 */
NOBODY void CGunTarget::Spawn_(void)
{
}

/* <12dade> ../cstrike/dlls/plats.cpp:2199 */
NOBODY void CGunTarget::Activate_(void)
{
//	{
//		class CBaseEntity *pTarg;                            //  2201
//		operator+(const Vector *const this,
//				const Vector &v);  //  2208
//		operator*(const Vector *const this,
//				float fl);  //  2208
//		operator-(const Vector *const this,
//				const Vector &v);  //  2208
//	}
}

/* <12d947> ../cstrike/dlls/plats.cpp:2213 */
NOBODY void CGunTarget::Start(void)
{
}

/* <12d96e> ../cstrike/dlls/plats.cpp:2219 */
NOBODY void CGunTarget::Next(void)
{
//	{
//		class CBaseEntity *pTarget;                          //  2224
//		operator+(const Vector *const this,
//				const Vector &v);  //  2232
//		operator*(const Vector *const this,
//				float fl);  //  2232
//		operator-(const Vector *const this,
//				const Vector &v);  //  2232
//		Stop(CGunTarget *const this);  //  2228
//	}
}

/* <12da61> ../cstrike/dlls/plats.cpp:2236 */
NOBODY void CGunTarget::Wait(void)
{
//	{
//		class CBaseEntity *pTarget;                          //  2238
//		Stop(CGunTarget *const this);  //  2242
//	}
}

/* <131d5d> ../cstrike/dlls/plats.cpp:2269 */
NOBODY void CGunTarget::Stop(void)
{
}

/* <12e371> ../cstrike/dlls/plats.cpp:2277 */
NOBODY int CGunTarget::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	Stop(CGunTarget *const this);  //  2285
//	TakeDamage(CGunTarget *const this,
//			entvars_t *pevInflictor,
//			entvars_t *pevAttacker,
//			float flDamage,
//			int bitsDamageType);  //  2277
}

/* <12e408> ../cstrike/dlls/plats.cpp:2294 */
NOBODY void CGunTarget::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Stop(CGunTarget *const this);  //  2301
//	Use(CGunTarget *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  2294
}

#ifdef HOOK_GAMEDLL

void CBasePlatTrain::Precache(void)
{
	Precache_();
}

void CBasePlatTrain::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBasePlatTrain::Save(CSave &save)
{
	return Save_(save);
}

int CBasePlatTrain::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CBasePlatTrain::ObjectCaps(void)
{
	return ObjectCaps_();
}

BOOL CBasePlatTrain::IsTogglePlat(void)
{
	return IsTogglePlat_();
}

void CFuncPlat::Spawn(void)
{
	Spawn_();
}

void CFuncPlat::Precache(void)
{
	Precache_();
}

void CFuncPlat::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

void CFuncPlat::GoUp(void)
{
	GoUp_();
}

void CFuncPlat::GoDown(void)
{
	GoDown_();
}

void CFuncPlat::HitTop(void)
{
	HitTop_();
}

void CFuncPlat::HitBottom(void)
{
	HitBottom_();
}

int CPlatTrigger::ObjectCaps(void)
{
	return ObjectCaps_();
}

void CPlatTrigger::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CFuncPlatRot::Spawn(void)
{
	Spawn_();
}

int CFuncPlatRot::Save(CSave &save)
{
	return Save_(save);
}

int CFuncPlatRot::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncPlatRot::GoUp(void)
{
	GoUp_();
}

void CFuncPlatRot::GoDown(void)
{
	GoDown_();
}

void CFuncPlatRot::HitTop(void)
{
	HitTop_();
}

void CFuncPlatRot::HitBottom(void)
{
	HitBottom_();
}






void CFuncTrain::Spawn(void)
{
	Spawn_();
}

void CFuncTrain::Precache(void)
{
	Precache_();
}

void CFuncTrain::Restart(void)
{
	Restart_();
}

void CFuncTrain::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTrain::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTrain::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncTrain::Activate(void)
{
	Activate_();
}

void CFuncTrain::OverrideReset(void)
{
	OverrideReset_();
}

void CFuncTrain::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncTrain::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

void CFuncTrackTrain::Spawn(void)
{
	Spawn_();
}

void CFuncTrackTrain::Precache(void)
{
	Precache_();
}

void CFuncTrackTrain::Restart(void)
{
	Restart_();
}

void CFuncTrackTrain::KeyValue(KeyValueData* pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTrackTrain::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTrackTrain::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CFuncTrackTrain::ObjectCaps(void)
{
	return ObjectCaps_();
}

void CFuncTrackTrain::OverrideReset(void)
{
	OverrideReset_();
}

BOOL CFuncTrackTrain::OnControls(entvars_t *pev)
{
	return OnControls_(pev);
}

void CFuncTrackTrain::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncTrackTrain::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

void CFuncTrainControls::Spawn(void)
{
	Spawn_();
}

int CFuncTrainControls::ObjectCaps(void)
{
	return ObjectCaps_();
}







void CFuncTrackChange::Spawn(void)
{
	Spawn_();
}

void CFuncTrackChange::Precache(void)
{
	Precache_();
}

void CFuncTrackChange::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncTrackChange::Save(CSave &save)
{
	return Save_(save);
}

int CFuncTrackChange::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncTrackChange::OverrideReset(void)
{
	OverrideReset_();
}

void CFuncTrackChange::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CFuncTrackChange::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

BOOL CFuncTrackChange::IsTogglePlat(void)
{
	return IsTogglePlat_();
}

void CFuncTrackChange::GoUp(void)
{
	GoUp_();
}

void CFuncTrackChange::GoDown(void)
{
	GoDown_();
}

void CFuncTrackChange::HitBottom(void)
{
	HitBottom_();
}

void CFuncTrackChange::HitTop(void)
{
	HitTop_();
}

void CFuncTrackChange::UpdateAutoTargets(int toggleState)
{
	UpdateAutoTargets_(toggleState);
}

void CFuncTrackAuto::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncTrackAuto::UpdateAutoTargets(int toggleState)
{
	UpdateAutoTargets_(toggleState);
}









void CGunTarget::Spawn(void)
{
	Spawn_();
}

int CGunTarget::Save(CSave &save)
{
	return Save_(save);
}

int CGunTarget::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CGunTarget::ObjectCaps(void)
{
	return ObjectCaps_();
}

void CGunTarget::Activate(void)
{
	Activate_();
}

int CGunTarget::Classify(void)
{
	return Classify_();
}

int CGunTarget::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

int CGunTarget::BloodColor(void)
{
	return BloodColor_();
}

void CGunTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

Vector CGunTarget::BodyTarget(const Vector &posSrc)
{
	return BodyTarget_(posSrc);
}

#endif // HOOK_GAMEDLL
