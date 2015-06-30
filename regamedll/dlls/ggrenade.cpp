#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CGrenade::m_SaveData[] =
{
	DEFINE_FIELD(CGrenade, m_fAttenu, FIELD_FLOAT),
	DEFINE_FIELD(CGrenade, m_flNextFreq, FIELD_TIME),
	DEFINE_FIELD(CGrenade, m_flC4Blow, FIELD_TIME),
	DEFINE_FIELD(CGrenade, m_flNextFreqInterval, FIELD_TIME),
	DEFINE_FIELD(CGrenade, m_flNextBeep, FIELD_TIME),
	DEFINE_FIELD(CGrenade, m_flDefuseCountDown, FIELD_TIME),
	DEFINE_FIELD(CGrenade, m_flNextBlink, FIELD_TIME),
	DEFINE_FIELD(CGrenade, m_pentCurBombTarget, FIELD_EDICT),
	DEFINE_FIELD(CGrenade, m_sBeepName, FIELD_POINTER),
	DEFINE_FIELD(CGrenade, m_bIsC4, FIELD_BOOLEAN),
	DEFINE_FIELD(CGrenade, m_bStartDefuse, FIELD_BOOLEAN),
	DEFINE_FIELD(CGrenade, m_SGSmoke, FIELD_INTEGER),
	DEFINE_FIELD(CGrenade, m_bJustBlew, FIELD_BOOLEAN),
	DEFINE_FIELD(CGrenade, m_bLightSmoke, FIELD_BOOLEAN),
	DEFINE_FIELD(CGrenade, m_usEvent, FIELD_INTEGER),
};

#else // HOOK_GAMEDLL

TYPEDESCRIPTION (*CGrenade::m_SaveData)[15];

#endif // HOOK_GAMEDLL

/* <b8dad> ../cstrike/dlls/ggrenade.cpp:52 */
LINK_ENTITY_TO_CLASS(grenade, CGrenade);

/* <b8e83> ../cstrike/dlls/ggrenade.cpp:60 */
void CGrenade::Explode(Vector vecSrc, Vector vecAim)
{
//	{
//		TraceResult tr;                                       //    62
//		operator+(const Vector *const this,
//				const Vector &v);  //    63
//	}
}

/* <b8f35> ../cstrike/dlls/ggrenade.cpp:69 */
void CGrenade::Explode(TraceResult *pTrace, int bitsDamageType)
{
//	{
//		float flRndSound;                                     //    71
//		int iContents;                                        //    84
//		entvars_t *pevOwner;                                 //   133
//		VARS(edict_t *pent);  //   135
//		Instance(edict_t *pent);  //   140
//		Vector(Vector *const this,
//			const Vector &v);  //   145
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   161
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   163
//		{
//			int sparkCount;                               //   179
//			{
//				int i;                                //   180
//			}
//		}
//		operator*(const Vector *const this,
//				float fl);  //    81
//		operator*(const Vector *const this,
//				float fl);  //    81
//		operator+(const Vector *const this,
//				const Vector &v);  //    81
//	}
}

/* <b9159> ../cstrike/dlls/ggrenade.cpp:186 */
void CGrenade::Explode2(TraceResult *pTrace, int bitsDamageType)
{
//	{
//		float flRndSound;                                     //   188
//		class CHalfLifeMultiplay *mp;                        //   189
//		int iContents;                                        //   218
//		entvars_t *pevOwner;                                 //   273
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   233
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   221
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   245
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   257
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   269
//		VARS(edict_t *pent);  //   275
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   289
//		edict(CBaseEntity *const this);  //   292
//		ENTINDEX(edict_t *pEdict);  //   292
//		{
//			int sparkCount;                               //   322
//			{
//				int i;                                //   323
//			}
//		}
//		operator*(const Vector *const this,
//				float fl);  //   215
//		operator*(const Vector *const this,
//				float fl);  //   215
//		operator+(const Vector *const this,
//				const Vector &v);  //   215
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   310
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   312
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   311
//	}
}

/* <b94f3> ../cstrike/dlls/ggrenade.cpp:330 */
void CGrenade::Explode3(TraceResult *pTrace, int bitsDamageType)
{
//	{
//		float flRndSound;                                     //   332
//		entvars_t *pevOwner;                                 //   371
//		float damage;                                         //   382
//		int sparkCount;                                       //   415
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   345
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   358
//		VARS(edict_t *pent);  //   373
//		Instance(edict_t *pent);  //   378
//		{
//			int i;                                        //   416
//		}
//		operator*(const Vector *const this,
//				float fl);  //   342
//		operator*(const Vector *const this,
//				float fl);  //   342
//		operator+(const Vector *const this,
//				const Vector &v);  //   342
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   405
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   407
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   406
//	}
}

/* <b97af> ../cstrike/dlls/ggrenade.cpp:420 */
void CGrenade::SG_Explode(TraceResult *pTrace, int bitsDamageType)
{
//	{
//		float flRndSound;                                     //   422
//		int iContents;                                        //   435
//		entvars_t *pevOwner;                                 //   438
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   458
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   460
//		{
//			int sparkCount;                               //   467
//			{
//				int i;                                //   468
//			}
//		}
//		operator*(const Vector *const this,
//				float fl);  //   432
//		operator*(const Vector *const this,
//				float fl);  //   432
//		operator+(const Vector *const this,
//				const Vector &v);  //   432
//	}
}

/* <b6c26> ../cstrike/dlls/ggrenade.cpp:475 */
void CGrenade::Smoke3_C(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   484
//	operator+(const Vector *const this,
//			const Vector &v);  //   480
//	operator-(const Vector *const this,
//			const Vector &v);  //   480
}

/* <b995d> ../cstrike/dlls/ggrenade.cpp:497 */
void CGrenade::Smoke3_B(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   506
//	operator+(const Vector *const this,
//			const Vector &v);  //   502
//	operator-(const Vector *const this,
//			const Vector &v);  //   502
}

/* <b6b2a> ../cstrike/dlls/ggrenade.cpp:520 */
void CGrenade::Smoke3_A(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   529
//	operator+(const Vector *const this,
//			const Vector &v);  //   525
//	operator-(const Vector *const this,
//			const Vector &v);  //   525
}

/* <b6a2e> ../cstrike/dlls/ggrenade.cpp:544 */
void CGrenade::Smoke2(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   553
//	operator+(const Vector *const this,
//			const Vector &v);  //   549
//	operator-(const Vector *const this,
//			const Vector &v);  //   549
}

/* <b6932> ../cstrike/dlls/ggrenade.cpp:567 */
void CGrenade::Smoke(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   575
//	operator+(const Vector *const this,
//			const Vector &v);  //   571
//	operator-(const Vector *const this,
//			const Vector &v);  //   571
}

/* <b6d22> ../cstrike/dlls/ggrenade.cpp:591 */
void CGrenade::SG_Smoke(void)
{
//	{
//		int iMaxSmokePuffs;                                   //   632
//		float flSmokeInterval;                                //   633
//		{
//			Vector origin;                          //   599
//			Vector angle;                           //   599
//			float x_old;                                  //   605
//			float y_old;                                  //   605
//			float R_angle;                                //   605
//			operator*(const Vector *const this,
//					float fl);  //   603
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   595
//		operator-(const Vector *const this,
//				const Vector &v);  //   595
//	}
}

/* <b8467> ../cstrike/dlls/ggrenade.cpp:664 */
void CGrenade::Killed_(entvars_t *pevAttacker, int iGib)
{
//	Detonate(CGrenade *const this);  //   666
}

/* <b9a59> ../cstrike/dlls/ggrenade.cpp:671 */
void CGrenade::DetonateUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <b9abf> ../cstrike/dlls/ggrenade.cpp:677 */
void CGrenade::PreDetonate(void)
{
}

/* <b789e> ../cstrike/dlls/ggrenade.cpp:686 */
void CGrenade::Detonate(void)
{
//	{
//		TraceResult tr;                                       //   688
//		Vector vecSpot;                                 //   689
//		operator+(const Vector *const this,
//				const Vector &v);  //   691
//		operator+(const Vector *const this,
//				const Vector &v);  //   692
//	}
}

/* <b7355> ../cstrike/dlls/ggrenade.cpp:698 */
void CGrenade::SG_Detonate(void)
{
//	{
//		TraceResult tr;                                       //   700
//		Vector vecSpot;                                 //   701
//		edict_t *pentFind;                                   //   713
//		operator+(const Vector *const this,
//				const Vector &v);  //   703
//		operator+(const Vector *const this,
//				const Vector &v);  //   704
//		Instance(edict_t *pent);  //   707
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   710
//		FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//					const char *pszName);  //   714
//		FNullEnt(const edict_t *pent);  //   715
//		{
//			class CBaseEntity *pEnt;                     //   717
//			Instance(edict_t *pent);  //   717
//			{
//				float fDistance;                      //   720
//				operator-(const Vector *const this,
//						const Vector &v);  //   722
//				Length(const Vector *const this);  //   722
//			}
//			FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//						const char *pszName);  //   727
//		}
//	}
}

/* <b8009> ../cstrike/dlls/ggrenade.cpp:752 */
void CGrenade::Detonate2(void)
{
//	{
//		TraceResult tr;                                       //   754
//		Vector vecSpot;                                 //   755
//		Explode2(CGrenade *const this,
//			TraceResult *pTrace,
//			int bitsDamageType);  //   760
//		operator+(const Vector *const this,
//				const Vector &v);  //   757
//		operator+(const Vector *const this,
//				const Vector &v);  //   758
//	}
}

/* <b7c81> ../cstrike/dlls/ggrenade.cpp:764 */
void CGrenade::Detonate3(void)
{
//	{
//		TraceResult tr;                                       //   766
//		Vector vecSpot;                                 //   767
//		operator+(const Vector *const this,
//				const Vector &v);  //   769
//		operator+(const Vector *const this,
//				const Vector &v);  //   770
//		Explode3(CGrenade *const this,
//			TraceResult *pTrace,
//			int bitsDamageType);  //   772
//	}
}

/* <b7956> ../cstrike/dlls/ggrenade.cpp:780 */
void CGrenade::ExplodeTouch(CBaseEntity *pOther)
{
//	{
//		TraceResult tr;                                       //   782
//		Vector vecSpot;                                 //   783
//		edict(CBaseEntity *const this);  //   785
//		Normalize(const Vector *const this);  //   787
//		operator*(const Vector *const this,
//				float fl);  //   787
//		operator-(const Vector *const this,
//				const Vector &v);  //   787
//		Normalize(const Vector *const this);  //   788
//		operator*(const Vector *const this,
//				float fl);  //   788
//		operator+(const Vector *const this,
//				const Vector &v);  //   788
//	}
}

/* <b7101> ../cstrike/dlls/ggrenade.cpp:794 */
void CGrenade::DangerSoundThink(void)
{
//	DangerSoundThink(CGrenade *const this);  //   794
}

/* <b7209> ../cstrike/dlls/ggrenade.cpp:812 */
void CGrenade::BounceTouch(CBaseEntity *pOther)
{
//	{
//		Vector vecTestVelocity;                         //   824
//		Length(const Vector *const this);  //   871
//		operator*(const Vector *const this,
//				float fl);  //   820
//		operator*(const Vector *const this,
//				float fl);  //   848
//		Length(const Vector *const this);  //   833
//		ENT(EOFFSET eoffset);  //   865
//	}
}

/* <b9ae7> ../cstrike/dlls/ggrenade.cpp:880 */
void CGrenade::SlideTouch(CBaseEntity *pOther)
{
//	edict(CBaseEntity *const this);  //   883
//	operator*(const Vector *const this,
//			float fl);  //   891
}

/* <b7b20> ../cstrike/dlls/ggrenade.cpp:904 */
void CGrenade::BounceSound_(void)
{
//	BounceSound(CGrenade *const this);  //   904
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   907
}

/* <b6f28> ../cstrike/dlls/ggrenade.cpp:919 */
void CGrenade::TumbleThink(void)
{
//	TumbleThink(CGrenade *const this);  //   919
}

/* <b67e7> ../cstrike/dlls/ggrenade.cpp:949 */
void CGrenade::SG_TumbleThink(void)
{
//	operator*(const Vector ::SG_TumbleThink(//			float fl);  //   978
//	operator*(const Vector *const this,
//			float fl);  //   960
//	operator*(const Vector *const this,
//			float fl);  //   968
//	operator+(const Vector *const this,
//			const Vector &v);  //   968
}

/* <b7010> ../cstrike/dlls/ggrenade.cpp:985 */
void CGrenade::Spawn_(void)
{
//	MAKE_STRING_CLASS(const char *str,
//				entvars_t *pev);  //   989
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   994
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   994
}

/* <b9b56> ../cstrike/dlls/ggrenade.cpp:1000 */
void ShootContact(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity)
{
//	{
//		class CGrenade *pGrenade;                            //  1002
//		GetClassPtr<CGrenade>(CGrenade *a);  //  1002
//	}
}

/* <b9c69> ../cstrike/dlls/ggrenade.cpp:1028 */
void ShootTimed2(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, int iTeam, short unsigned int usEvent)
{
//	{
//		class CGrenade *pGrenade;                            //  1030
//		GetClassPtr<CGrenade>(CGrenade *a);  //  1030
//		operator*(const Vector *const this,
//				float fl);  //  1033
//	}
}

/* <b9dd0> ../cstrike/dlls/ggrenade.cpp:1069 */
void ShootTimed(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time)
{
//	{
//		class CGrenade *pGrenade;                            //  1071
//		GetClassPtr<CGrenade>(CGrenade *a);  //  1071
//	}
}

/* <ba5be> ../cstrike/dlls/ggrenade.cpp:1113 */
void CGrenade::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CBasePlayer *player;                           //  1118
//	}
//	Use(CGrenade *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  1113
}

/* <b9eed> ../cstrike/dlls/ggrenade.cpp:1178 */
void ShootSatchelCharge(entvars_t *pevOwner, Vector vecStart, Vector vecAngles)
{
//	{
//		class CGrenade *pGrenade;                            //  1180
//		class CBasePlayer *owner;                            //  1227
//		GetClassPtr<CGrenade>(CGrenade *a);  //  1180
//		MAKE_STRING_CLASS(const char *str,
//					entvars_t *pev);  //  1182
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  1190
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  1190
//		Instance(edict_t *pent);  //  1227
//	}
}

/* <ba122> ../cstrike/dlls/ggrenade.cpp:1238 */
void ShootSmokeGrenade(entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, float time, short unsigned int usEvent)
{
//	{
//		class CGrenade *pGrenade;                            //  1240
//		GetClassPtr<CGrenade>(CGrenade *a);  //  1240
//	}
}

/* <b5701> ../cstrike/dlls/ggrenade.cpp:1284 */
void AnnounceFlashInterval(float interval, float offset)
{
}

/* <b855a> ../cstrike/dlls/ggrenade.cpp:1300 */
void CGrenade::C4Think(void)
{
//	{
//		class CBasePlayer *pBombOwner;                       //  1394
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1379
//		{
//			class CBaseEntity *pBombTarget;              //  1387
//			Instance(edict_t *pent);  //  1387
//			Instance(edict_t *pent);  //  1390
//		}
//		Instance(edict_t *pent);  //  1394
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1401
//	}
//	GET_PRIVATE(edict_t *pent);  //  1417
//	{
//		int iOnGround;                                        //  1419
//		GET_PRIVATE(edict_t *pent);  //  1428
//		GET_PRIVATE(edict_t *pent);  //  1429
//		GET_PRIVATE(edict_t *pent);  //  1432
//	}
//	GET_PRIVATE(edict_t *pent);  //  1444
//	GET_PRIVATE(edict_t *pent);  //  1447
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  1453
//	edict(CBaseEntity *const this);  //  1456
//	ENTINDEX(edict_t *pEdict);  //  1456
//	edict(CBaseEntity *const this);  //  1465
//	edict(CBaseEntity *const this);  //  1465
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //  1470
//	GET_PRIVATE(edict_t *pent);  //  1476
//	GET_PRIVATE(edict_t *pent);  //  1477
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  1479
//	{
//		class CBasePlayer *pPlayer;                          //  1485
//		GET_PRIVATE(edict_t *pent);  //  1485
//	}
//	GET_PRIVATE(edict_t *pent);  //  1494
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  1497
//	GET_PRIVATE(edict_t *pent);  //  1510
//	GET_PRIVATE(edict_t *pent);  //  1512
//	GET_PRIVATE(edict_t *pent);  //  1513
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //  1348
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  1358
//	AnnounceFlashInterval(float interval,
//				float offset);  //  1334
//	AnnounceFlashInterval(float interval,
//				float offset);  //  1339
//	AnnounceFlashInterval(float interval,
//				float offset);  //  1329
//	AnnounceFlashInterval(float interval,
//				float offset);  //  1324
//	AnnounceFlashInterval(float interval,
//				float offset);  //  1319
}

/* <b67b1> ../cstrike/dlls/ggrenade.cpp:1523 */
void CGrenade::C4Touch(CBaseEntity *pOther)
{
	;
}

/* <ba24f> ../cstrike/dlls/ggrenade.cpp:1528 */
void CGrenade::UseSatchelCharges(entvars_t *pevOwner, SATCHELCODE code)
{
//	{
//		edict_t *pentFind;                                   //  1530
//		edict_t *pentOwner;                                  //  1531
//		class CBaseEntity *pOwner;                           //  1536
//		Instance(entvars_t *pev);  //  1536
//		edict(CBaseEntity *const this);  //  1538
//		FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//					const char *pszName);  //  1540
//		FNullEnt(const edict_t *pent);  //  1541
//		{
//			class CBaseEntity *pEnt;                     //  1543
//			FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//						const char *pszName);  //  1554
//			Instance(edict_t *pent);  //  1543
//		}
//	}
}

/* <b6ed7> ../cstrike/dlls/ggrenade.cpp:1579 */
IMPLEMENT_SAVERESTORE(CGrenade, CBaseMonster);

#ifdef HOOK_GAMEDLL

void CGrenade::Spawn(void)
{
	Spawn_();
}

int CGrenade::Save(CSave &save)
{
	Save_(save);
}

int CGrenade::Restore(CRestore &restore)
{
	Restore_(restore);
}

//int CGrenade::ObjectCaps(void)
//{
//	return ObjectCaps_();
//}

void CGrenade::Killed(entvars_t *pevAttacker, int iGib)
{
	Killed_(pevAttacker, iGib);
}

void CGrenade::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGrenade::BounceSound(void)
{
	BounceSound_();
}

#endif // HOOK_GAMEDLL