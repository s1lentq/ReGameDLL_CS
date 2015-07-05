#include "precompiled.h"

/* <5f4cb> ../cstrike/dlls/combat.cpp:52 */
NOBODY void CGib::LimitVelocity(void)
{
//	{
//		float length;                                         //    54
//		Length(const Vector *const this);  //    54
//	} 
//	LimitVelocity(CGib *const this);  //    52
}

/* <60320> ../cstrike/dlls/combat.cpp:63 */
NOBODY void CGib::SpawnStickyGibs(entvars_t *pevVictim, Vector vecOrigin, int cGibs)
{
//	{
//		int i;                                                //    65
//		{
//			class CGib *pGib;                            //    75
//			GetClassPtr<CGib>(CGib *a);  //    75
//			operator*(const Vector *const this,
//					float fl);  //    93
//			operator*(const Vector *const this,
//					float fl);  //   100
//			Instance(entvars_t *pev);  //   106
//			operator*(const Vector *const this,
//					float fl);  //   110
//			operator*(const Vector *const this,
//					float fl);  //   118
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   124
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   124
//			LimitVelocity(CGib *const this);  //   128
//			operator*(const Vector *const this,
//					float fl);  //   114
//		} 
//	} 
}

/* <5ff7f> ../cstrike/dlls/combat.cpp:132 */
NOBODY void CGib::SpawnHeadGib(entvars_t *pevVictim)
{
//	{
//		class CGib *pGib;                                    //   134
//		GetClassPtr<CGib>(CGib *a);  //   134
//		{
//			edict_t *pentPlayer;                         //   151
//			operator+(const Vector *const this,
//					const Vector  &v);  //   149
//			{
//				entvars_t *pevPlayer;                //   156
//				operator+(const Vector *const this,
//						const Vector  &v);  //   159
//				operator-(const Vector *const this,
//						const Vector  &v);  //   159
//				Normalize(const Vector *const this);  //   159
//			} 
//			edict(CBaseEntity *const this);  //   151
//			Instance(entvars_t *pev);  //   172
//			operator*(const Vector *const this,
//					float fl);  //   184
//			operator*(const Vector *const this,
//					float fl);  //   176
//			operator*(const Vector *const this,
//					float fl);  //   180
//		} 
//		LimitVelocity(CGib *const this);  //   187
//	} 
}

/* <606c8> ../cstrike/dlls/combat.cpp:190 */
NOBODY void CGib::SpawnRandomGibs(entvars_t *pevVictim, int human, int cGibs)
{
//	{
//		int cSplat;                                           //   192
//		{
//			class CGib *pGib;                            //   196
//			operator*(const Vector *const this,
//					float fl);  //   227
//			operator*(const Vector *const this,
//					float fl);  //   234
//			Instance(entvars_t *pev);  //   240
//			operator*(const Vector *const this,
//					float fl);  //   244
//			operator*(const Vector *const this,
//					float fl);  //   252
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   256
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   256
//			LimitVelocity(CGib *const this);  //   258
//			GetClassPtr<CGib>(CGib *a);  //   196
//			operator*(const Vector *const this,
//					float fl);  //   248
//		} 
//	} 
}

/* <5f58a> ../cstrike/dlls/combat.cpp:263 */
NOBODY BOOL CBaseMonster::HasHumanGibs_(void)
{
//	{
//		int myClass;                                          //   265
//	} 
}

/* <5f5ca> ../cstrike/dlls/combat.cpp:278 */
NOBODY BOOL CBaseMonster::HasAlienGibs_(void)
{
//	{
//		int myClass;                                          //   280
//	} 
}

/* <5f60a> ../cstrike/dlls/combat.cpp:295 */
NOBODY void CBaseMonster::FadeMonster_(void)
{
//	StopAnimation(CBaseMonster *const this);  //   297
//	SUB_StartFadeOut(CBaseEntity *const this);  //   303
}

/* <60a59> ../cstrike/dlls/combat.cpp:310 */
NOBODY void CBaseMonster::GibMonster_(void)
{
//	{
//		TraceResult tr;                                       //   312
//		BOOL gibbed;                                          //   313
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   315
//	} 
}

/* <5f65e> ../cstrike/dlls/combat.cpp:355 */
NOBODY Activity CBaseMonster::GetDeathActivity_(void)
{
//	{
//		Activity deathActivity;                               //   357
//		BOOL fTriedDirection;                                 //   358
//		float flDot;                                          //   359
//		TraceResult tr;                                       //   360
//		class Vector vecSrc;                                  //   361
//		operator*(const Vector *const this,
//				float fl);  //   375
//		DotProduct(const Vector  &a,
//				const Vector  &b);  //   375
//		edict(CBaseEntity *const this);  //   461
//		operator*(const Vector *const this,
//				float fl);  //   461
//		operator-(const Vector *const this,
//				const Vector  &v);  //   461
//		edict(CBaseEntity *const this);  //   450
//		operator*(const Vector *const this,
//				float fl);  //   450
//		operator+(const Vector *const this,
//				const Vector  &v);  //   450
//	} 
}

/* <5f848> ../cstrike/dlls/combat.cpp:476 */
NOBODY Activity CBaseMonster::GetSmallFlinchActivity(void)
{
//	{ 
//		Activity flinchActivity;                              //   478
//		BOOL fTriedDirection;                                 //   479
//		float flDot;                                          //   480
//	} 
}

/* <5f8a6> ../cstrike/dlls/combat.cpp:525 */
void CBaseMonster::BecomeDead_(void)
{
	// don't let autoaim aim at corpses.
	pev->takedamage = DAMAGE_YES;

	// give the corpse half of the monster's original maximum health. 
	pev->health = pev->max_health / 2;

	// max_health now becomes a counter for how many blood decals the corpse can place.
	pev->max_health = 5;

	// make the corpse fly away from the attack vector
	pev->movetype = MOVETYPE_TOSS;
}

/* <5f8cc> ../cstrike/dlls/combat.cpp:542 */
NOBODY BOOL CBaseMonster::ShouldGibMonster(int iGib)
{
}

/* <5f8f8> ../cstrike/dlls/combat.cpp:551 */
NOBODY void CBaseMonster::CallGibMonster(void)
{
//	{
//		BOOL fade;                                            //   553
//	} 
}

/* <5f938> ../cstrike/dlls/combat.cpp:598 */
NOBODY void CBaseMonster::Killed_(entvars_t *pevAttacker, int iGib)
{
//	{
//		unsigned int cCount;                                  //   600
//		BOOL fDone;                                           //   601
//		class CBaseEntity *pOwner;                           //   619
//		HasMemory(CBaseMonster *const this,
//				int iMemory);  //   603
//		ShouldGibMonster(CBaseMonster *const this,
//				int iGib);  //   605
//		Remember(CBaseMonster *const this,
//			int iMemory);  //   610
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   613
//		SetConditions(CBaseMonster *const this,
//				int iConditions);  //   616
//		Instance(edict_t *pent);  //   619
//		ShouldGibMonster(CBaseMonster *const this,
//				int iGib);  //   625
//	} 
}

/* <5e84e> ../cstrike/dlls/combat.cpp:652 */
NOBODY void CBaseEntity::SUB_StartFadeOut(void)
{
}

/* <5ea72> ../cstrike/dlls/combat.cpp:667 */
NOBODY void CBaseEntity::SUB_FadeOut(void)
{
//	SUB_FadeOut(CBaseEntity *const this);  //   667
}

/* <5eab1> ../cstrike/dlls/combat.cpp:688 */
NOBODY void CGib::WaitTillLand(void)
{
//	operator==(const Vector ::WaitTillLand(//			const Vector  &v);  //   696
//	WaitTillLand(CGib *const this);  //   688
}

/* <5eee0> ../cstrike/dlls/combat.cpp:718 */
NOBODY void CGib::BounceGibTouch(CBaseEntity *pOther)
{
//	{
//		class Vector vecSpot;                                 //   720
//		TraceResult tr;                                       //   721
//		operator*(const Vector *const this,
//				float fl);  //   728
//	} 
//	BounceGibTouch(CGib *const this,
//			class CBaseEntity *pOther);  //   718
}

/* <5ed6d> ../cstrike/dlls/combat.cpp:761 */
NOBODY void CGib::StickyGibTouch(CBaseEntity *pOther)
{
//	{
//		class Vector vecSpot;                                 //   763
//		TraceResult tr;                                       //   764
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   769
//	} 
//	StickyGibTouch(CGib *const this,
//			class CBaseEntity *pOther);  //   761
}

/* <5fb0b> ../cstrike/dlls/combat.cpp:789 */
NOBODY void CGib::Spawn(const char *szGibModel)
{
//	MAKE_STRING_CLASS(const char *str,
//				entvars_t *pev);  //   800
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   803
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   803
}

/* <60aea> ../cstrike/dlls/combat.cpp:815 */
int CBaseMonster::TakeHealth_(float flHealth, int bitsDamageType)
{
	if (pev->takedamage == DAMAGE_NO)
		return 0;

	// clear out any damage types we healed.
	// UNDONE: generic health should not heal any
	// UNDONE: time-based damage

	m_bitsDamageType &= ~(bitsDamageType & ~DMG_TIMEBASED);
	return CBaseEntity::TakeHealth(flHealth, bitsDamageType);
}

/* <60d7a> ../cstrike/dlls/combat.cpp:845 */
NOBODY int CBaseMonster::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		float flTake;                                         //   847
//		class Vector vecDir;                                  //   848
//		FNullEnt(entvars_t *pev);  //   872
//		{
//			class CBaseEntity *pInflictor;               //   874
//			Instance(entvars_t *pev);  //   874
//			operator-(const Vector *const this,
//					const Vector &v);  //   877
//			operator-(const Vector *const this,
//					const Vector &v);  //   877
//			Normalize(const Vector *const this);  //   877
//			Normalize(const Vector *const this);  //   878
//		} 
//		FNullEnt(entvars_t *pev);  //   939
//		Vector(Vector *const this,
//			const Vector &v);  //   957
//		SetConditions(CBaseMonster *const this,
//				int iConditions);  //   964
//		SetConditions(CBaseMonster *const this,
//				int iConditions);  //   969
//		SetConditions(CBaseMonster *const this,
//				int iConditions);  //   912
//		operator*(const Vector *const this,
//				float fl);  //   954
//		operator+(const Vector *const this,
//				const Vector &v);  //   954
//		HasConditions(CBaseMonster *const this,
//				int iConditions);  //   947
//	} 
}

/* <60b32> ../cstrike/dlls/combat.cpp:981 */
NOBODY int CBaseMonster::DeadTakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		class Vector vecDir;                                  //   983
//		FNullEnt(entvars_t *pev);  //   987
//		{
//			class CBaseEntity *pInflictor;               //   989
//			Instance(entvars_t *pev);  //   989
//			operator-(const Vector *const this,
//					const Vector &v);  //   992
//			operator-(const Vector *const this,
//					const Vector &v);  //   992
//			Normalize(const Vector *const this);  //   992
//			Normalize(const Vector *const this);  //   993
//		} 
//	} 
}

/* <61120> ../cstrike/dlls/combat.cpp:1027 */
NOBODY float CBaseMonster::DamageForce(float damage)
{
//	{ 
//		float force;                                          //  1029
//	} 
}

/* <61174> ../cstrike/dlls/combat.cpp:1044 */
NOBODY void RadiusFlash(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
//	{
//		class CBaseEntity *pEntity;                          //  1046
//		TraceResult tr;                                       //  1047
//		float flAdjustedDamage;                               //  1048
//		float falloff;                                        //  1048
//		class Vector vecSpot;                                 //  1049
//		float flRadius;                                       //  1050
//		int bInWater;                                         //  1058
//		edict(CBaseEntity *const this);  //  1085
//		{
//			TraceResult tr2;                              //  1088
//			class Vector vecLOS;                          //  1110
//			float flDot;                                  //  1111
//			float fadeTime;                               //  1120
//			float fadeHold;                               //  1120
//			int alpha;                                    //  1121
//			class CBasePlayer *pPlayer;                  //  1137
//			float currentHoldTime;                        //  1140
//			operator-(const Vector *const this,
//					const Vector &v);  //  1102
//			Length(const Vector *const this);  //  1102
//			operator+(const Vector *const this,
//					const Vector &v);  //  1115
//			operator-(const Vector *const this,
//					const Vector &v);  //  1115
//			DotProduct(const Vector &a,
//					const Vector &b);  //  1117
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //  1157
//			{ 
//				int i;                                //  1160
//				{
//					class CBasePlayer *pObserver;//  1162
//					Vector(Vector *const this,
//						float X,
//						float Y,
//						float Z);  //  1166
//				} 
//			} 
//		} 
//	} 
}

/* <5f042> ../cstrike/dlls/combat.cpp:1185 */
NOBODY void GetAmountOfPlayerVisible(Vector vecSrc, CBaseEntity *entity)
{
//	{
//		float retval;                                         //  1187
//		TraceResult tr;                                       //  1189
//		floatconst topOfHead;                                 //  1204
//		class Vector spot;                                    //  1216
//		class Vector2D dir;                                   //  1232
//		floatconst standFeet;                                 //  1205
//		floatconst crouchFeet;                                //  1206
//		class Vector2D perp;                                  //  1234
//		floatconst edgeOffset;                                //  1235
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  1216
//		NormalizeInPlace(Vector2D *const this);  //  1233
//	} 
}

/* <5dc27> ../cstrike/dlls/combat.cpp:1262 */
NOBODY void RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
//	{
//		class CBaseEntity *pEntity;                          //  1264
//		TraceResult tr;                                       //  1265
//		float flAdjustedDamage;                               //  1266
//		float falloff;                                        //  1266
//		class Vector vecSpot;                                 //  1267
//		int bInWater;                                         //  1275
//		{
//			bool useLOS;                                  //  1300
//			float damageRatio;                            //  1305
//			float length;                                 //  1308
//		}
//	}
}

/* <5dcf9> ../cstrike/dlls/combat.cpp:1349 */
NOBODY void RadiusDamage2(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
//	{
//		class CBaseEntity *pEntity;                          //  1351
//		TraceResult tr;                                       //  1352
//		float flAdjustedDamage;                               //  1353
//		float falloff;                                        //  1353
//		class Vector vecSpot;                                 //  1354
//		int bInWater;                                         //  1362
//	}
}

/* <5e0d2> ../cstrike/dlls/combat.cpp:1442 */
NOBODY void CBaseMonster::RadiusDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
	if (flDamage > 80)
		::RadiusDamage(pev->origin, pevInflictor, pevAttacker, flDamage, flDamage * 3.5, iClassIgnore, bitsDamageType);
	else
		RadiusDamage2(pev->origin, pevInflictor, pevAttacker, flDamage, iClassIgnore, bitsDamageType);
}

/* <5e0d2> ../cstrike/dlls/combat.cpp:1448 */
NOXREF void CBaseMonster::RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
	if (flDamage > 80)
		::RadiusDamage(vecSrc, pevInflictor, pevAttacker, flDamage, flDamage * 3.5, iClassIgnore, bitsDamageType);
	else
		RadiusDamage2(vecSrc, pevInflictor, pevAttacker, flDamage, iClassIgnore, bitsDamageType);
}

/* <61949> ../cstrike/dlls/combat.cpp:1454 */
NOBODY CBaseEntity *CBaseMonster::CheckTraceHullAttack(float flDist, int iDamage, int iDmgType)
{
//	{
//		TraceResult tr;                                       //  1456
//		class Vector vecStart;                                //  1463
//		class Vector vecEnd;                                  //  1465
//		Vector(Vector *const this,
//			const Vector &v);  //  1463
//		operator*(const Vector *const this,
//				float fl);  //  1465
//		operator+(const Vector *const this,
//				const Vector &v);  //  1465
//		{ 
//			class CBaseEntity *pEntity;                  //  1471
//			Instance(edict_t *pent);  //  1471
//		} 
//	}
	return NULL;
}

/* <61ae6> ../cstrike/dlls/combat.cpp:1490 */
NOBODY BOOL CBaseMonster::FInViewCone_(CBaseEntity *pEntity)
{
//	{
//		class Vector2D vec2LOS;                               //  1492
//		float flDot;                                          //  1493
//		operator-(const Vector *const this,
//				const Vector &v);  //  1497
//		Normalize(const class Vector2D *const this);  //  1498
//		DotProduct(const class Vector2D  &a,
//				const class Vector2D  &b);  //  1500
//	}
	return FALSE;
}

/* <61be6> ../cstrike/dlls/combat.cpp:1517 */
NOBODY BOOL CBaseMonster::FInViewCone_(Vector *pOrigin)
{
//	{
//		class Vector2D vec2LOS;                               //  1519
//		float flDot;                                          //  1520
//		operator-(const Vector *const this,
//				const Vector &v);  //  1524
//		Normalize(const class Vector2D *const this);  //  1525
//		DotProduct(const class Vector2D  &a,
//				const class Vector2D  &b);  //  1527
//	}
	return FALSE;
}

/* <5ecb4> ../cstrike/dlls/combat.cpp:1543 */
NOBODY BOOL CBaseEntity::FVisible_(CBaseEntity *pEntity)
{
//	{
//		TraceResult tr;                                       //  1545
//		class Vector vecLookerOrigin;                         //  1546
//		class Vector vecTargetOrigin;                         //  1547
//	} 
//	FVisible(CBaseEntity *const this,
//		class CBaseEntity *pEntity);  //  1543
	return FALSE;
}

/* <5e9bb> ../cstrike/dlls/combat.cpp:1576 */
NOBODY BOOL CBaseEntity::FVisible_(Vector &vecOrigin)
{
//	{
//		TraceResult tr;                                       //  1578
//		class Vector vecLookerOrigin;                         //  1579
//	}
	return FALSE;
}

/* <5e872> ../cstrike/dlls/combat.cpp:1600 */
NOBODY void CBaseEntity::TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
//	{
//		class Vector vecOrigin;                               //  1602
//		operator*(const Vector *const this,
//				float fl);  //  1602
//		{
//			int blood;                                    //  1608
//			Vector(Vector *const this,
//				const Vector &v);  //  1612
//			Vector(Vector *const this,
//				const Vector &v);  //  1613
//		} 
//		operator-(const Vector *const this,
//				const Vector &v);  //  1602
//	} 
}

/* <61ce5> ../cstrike/dlls/combat.cpp:1647 */
NOBODY void CBaseMonster::TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
//	{
//		class Vector vecOrigin;                               //  1684
//		int blood;                                            //  1687
//		operator*(const Vector *const this,
//				float fl);  //  1684
//		operator-(const Vector *const this,
//				const Vector &v);  //  1684
//		Vector(Vector *const this,
//			const Vector &v);  //  1691
//	} 
}

/* <61df9> ../cstrike/dlls/combat.cpp:1704 */
NOBODY void CBaseEntity::FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker)
{
//	{
//		int tracerCount;                                      //  1706
//		int tracer;                                           //  1707
//		TraceResult tr;                                       //  1708
//		class Vector vecRight;                                //  1709
//		class Vector vecUp;                                   //  1710
//		bool m_bCreatedShotgunSpark;                          //  1711
//		Vector(Vector *const this,
//			const Vector &v);  //  1709
//		Vector(Vector *const this,
//			const Vector &v);  //  1710
//		{
//			ULONG iShot;                                  //  1722
//			{
//				int spark;                            //  1724
//				float x;                              //  1727
//				float y;                              //  1727
//				float z;                              //  1727
//				class Vector vecDir;                  //  1734
//				class Vector vecEnd;                  //  1737
//				operator*(float fl,
//						const Vector &v);  //  1736
//				operator*(float fl,
//						const Vector &v);  //  1736
//				operator+(const Vector *const this,
//						const Vector &v);  //  1736
//				operator+(const Vector *const this,
//						const Vector &v);  //  1736
//				operator*(const Vector *const this,
//						float fl);  //  1739
//				operator+(const Vector *const this,
//						const Vector &v);  //  1739
//				{
//					class Vector vecTracerSrc;    //  1745
//					operator*(const Vector *const this,
//							float fl);  //  1749
//					operator*(const Vector *const this,
//							float fl);  //  1749
//					operator+(const Vector *const this,
//							const Vector &v);  //  1749
//					operator+(const Vector *const this,
//							const Vector &v);  //  1749
//					operator+(const Vector *const this,
//							const Vector &v);  //  1749
//					MESSAGE_BEGIN(int msg_dest,
//							int msg_type,
//							const float *pOrigin,
//							edict_t *ed);  //  1765
//				} 
//				{
//					class CBaseEntity *pEntity;  //  1780
//					Instance(edict_t *pent);  //  1780
//					Vector(Vector *const this,
//						const Vector &v);  //  1784
//					Vector(Vector *const this,
//						const Vector &v);  //  1786
//					Vector(Vector *const this,
//						const Vector &v);  //  1786
//					{
//						float flDamage;       //  1802
//						Vector(Vector *const this,
//							const Vector &v);  //  1793
//						Vector(Vector *const this,
//							const Vector &v);  //  1830
//						Vector(Vector *const this,
//							const Vector &v);  //  1822
//						Vector(Vector *const this,
//							const Vector &v);  //  1824
//						Vector(Vector *const this,
//							const Vector &v);  //  1824
//						Vector(Vector *const this,
//							const Vector &v);  //  1814
//						Vector(Vector *const this,
//							const Vector &v);  //  1816
//						Vector(Vector *const this,
//							const Vector &v);  //  1816
//						Vector(Vector *const this,
//							const Vector &v);  //  1806
//						Vector(Vector *const this,
//							const Vector &v);  //  1810
//						Vector(Vector *const this,
//							const Vector &v);  //  1797
//						Vector(Vector *const this,
//							const Vector &v);  //  1839
//						Vector(Vector *const this,
//							const Vector &v);  //  1840
//						Vector(Vector *const this,
//							const Vector &v);  //  1840
//						FNullEnt(const edict_t *pent);  //  1842
//						VARS(edict_t *pent);  //  1842
//						Vector(Vector *const this,
//							const Vector &v);  //  1833
//						Vector(Vector *const this,
//							const Vector &v);  //  1833
//					} 
//				} 
//				Vector(Vector *const this,
//					const Vector &v);  //  1851
//				Vector(Vector *const this,
//					const Vector &v);  //  1851
//			} 
//		} 
//	} 
}

/* <62693> ../cstrike/dlls/combat.cpp:1856 */
NOXREF char *vstr(float *v)
{
	static int idx = 0;
	static char string[ 16 ][ 1024 ];

	idx = (idx + 1) % 0xF;
	Q_sprintf(string[ idx ], "%.4f %.4f %.4f", v[0], v[1], v[2]);

	return string[ idx ];
}

Vector (*pFireBullets3)(Vector, Vector, float, float, int, int, int, float, entvars_t *, bool, int);

/* <62709> ../cstrike/dlls/combat.cpp:1869 */
Vector __declspec(naked) CBaseEntity::FireBullets3(Vector vecSrc, Vector vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand)
{
	UNTESTED
	//TODO: crash a test to czero

	__asm
	{
		jmp pFireBullets3
	}
/*	int iOriginalPenetration = iPenetration;
	int iPenetrationPower;

	//int iSparksAmount;
	int iCurrentDamage = iDamage;

	float flPenetrationDistance;
	float flCurrentDistance;

	TraceResult tr;
	TraceResult tr2;

	CBaseEntity *pEntity;
	Vector vecDir;
	Vector vecEnd;

	bool bHitMetal = false;

	Vector vecRight = gpGlobals->v_right;
	Vector vecUp = gpGlobals->v_up;

	switch (iBulletType)
	{
		case BULLET_PLAYER_9MM:
		{
			iPenetrationPower = 21;
			flPenetrationDistance = 800;
			break;
		}
		case BULLET_PLAYER_45ACP:
		{
			iPenetrationPower = 15;
			flPenetrationDistance = 500;
			break;
		}
		case BULLET_PLAYER_50AE:
		{
			iPenetrationPower = 30;
			flPenetrationDistance = 1000;
			break;
		}
		case BULLET_PLAYER_762MM:
		{
			iPenetrationPower = 39;
			flPenetrationDistance = 5000.0f;
			break;
		}
		case BULLET_PLAYER_556MM:
		{
			iPenetrationPower = 35;
			flPenetrationDistance = 4000;
			break;
		}
		case BULLET_PLAYER_338MAG:
		{
			iPenetrationPower = 45;
			flPenetrationDistance = 8000;
			break;
		}
		case BULLET_PLAYER_57MM:
		{
			iPenetrationPower = 30;
			flPenetrationDistance = 2000;
			break;
		}
		case BULLET_PLAYER_357SIG:
		{
			iPenetrationPower = 25;
			flPenetrationDistance = 800;
			break;
		}
		default:
		{
			iPenetrationPower = 0;
			flPenetrationDistance = 0;
			break;
		}
	}

	if (!pevAttacker)
		pevAttacker = pev; // the default attacker is ourselves

	gMultiDamage.type = (DMG_BULLET | DMG_NEVERGIB);

	float x, y, z;

	if (IsPlayer())
	{
		// Use player's random seed.
		// get circular gaussian spread
		x = UTIL_SharedRandomFloat(shared_rand, -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + 1, -0.5, 0.5);
		y = UTIL_SharedRandomFloat(shared_rand + 2, -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + 3, -0.5, 0.5);
	}
	else
	{
		do
		{
			x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			z = x * x + y * y;
		}
		while (z > 1);
	}

	vecDir = vecDirShooting + x * vecSpread * vecRight + y * vecSpread * vecUp;
	vecEnd = vecSrc + vecDir * flDistance;

	float flDamageModifier = 0.5;

	while (iPenetration != 0)
	{
		ClearMultiDamage();
		UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev), &tr);

		if (tr.flFraction != 1)
			TheBots->OnEvent(EVENT_BULLET_IMPACT, this, NULL);

		switch (UTIL_TextureHit(&tr, vecSrc, vecEnd))
		{
			case CHAR_TEX_METAL:
			{
				bHitMetal = true;
				iPenetrationPower *= 0.15;
				flDamageModifier = 0.2;
				break;
			}
			case CHAR_TEX_CONCRETE:
			{
				iPenetrationPower *= 0.25;
				break;
			}
			case CHAR_TEX_GRATE:
			{
				bHitMetal = true;
				iPenetrationPower *= 0.5;
				flDamageModifier = 0.4;
				break;
			}
			case CHAR_TEX_VENT:
			{
				bHitMetal = true;
				iPenetrationPower *= 0.5;
				flDamageModifier = 0.45;
				break;
			}
			case CHAR_TEX_TILE:
			{
				iPenetrationPower *= 0.65;
				flDamageModifier = 0.3;
				break;
			}
			case CHAR_TEX_COMPUTER:
			{
				bHitMetal = true;
				iPenetrationPower *= 0.4;
				flDamageModifier = 0.45;
				break;
			}
			case CHAR_TEX_WOOD:
			{
				flDamageModifier = 0.6;
				break;
			}
			default:
				break;
		}
		if (tr.flFraction != 1.0)
		{
			pEntity = CBaseEntity::Instance(tr.pHit);
			iPenetration--;

			flCurrentDistance = tr.flFraction * flDistance;
			iCurrentDamage *= pow(flRangeModifier, flCurrentDistance / 500);

			if (flCurrentDistance > flPenetrationDistance)
				iPenetration = 0;

			if (tr.iHitgroup == HITGROUP_SHIELD)
			{
				if (RANDOM_LONG(0, 1))
					EMIT_SOUND(pEntity->edict(), CHAN_VOICE, "weapons/ric_metal-1.wav", VOL_NORM, ATTN_NORM);
				else
					EMIT_SOUND(pEntity->edict(), CHAN_VOICE, "weapons/ric_metal-2.wav", VOL_NORM, ATTN_NORM);

				UTIL_Sparks(tr.vecEndPos);

				pEntity->pev->punchangle.x = iCurrentDamage * RANDOM_FLOAT(-0.15, 0.15);
				pEntity->pev->punchangle.z = iCurrentDamage * RANDOM_FLOAT(-0.15, 0.15);

				if (pEntity->pev->punchangle.x < 4)
					pEntity->pev->punchangle.x = -4;//TODO:?? 4 ?

				if (pEntity->pev->punchangle.z < -5)
					pEntity->pev->punchangle.z = -5;

				else if (pEntity->pev->punchangle.z > 5)
					pEntity->pev->punchangle.z = 5;

				break;
			}

			float flDistanceModifier;
			//if (VARS(tr.pHit)->solid != SOLID_BSP || !iPenetration)
			if (pEntity->pev->solid != SOLID_BSP || !iPenetration)
			{
				iPenetrationPower = 42;
				flDamageModifier = 0.75;
				flDistanceModifier = 0.75;
			}
			else
				flDistanceModifier = 0.5;

			DecalGunshot(&tr, iBulletType, (!bPistol && RANDOM_LONG(0, 3)), pev, bHitMetal);
				
			vecSrc = tr.vecEndPos + (vecDir * iPenetrationPower);
			flDistance = (flDistance - flCurrentDistance) * flDistanceModifier;
			vecEnd = vecSrc + (vecDir * flDistance);

			pEntity->TraceAttack(pevAttacker, iCurrentDamage, vecDir, &tr, DMG_BULLET | DMG_NEVERGIB);
			iCurrentDamage *= flDamageModifier;
		}
		else
			iPenetration = 0;

		ApplyMultiDamage(pev, pevAttacker);
	}

	return Vector(x * vecSpread, y * vecSpread, 0);*/
}

/* <5eb17> ../cstrike/dlls/combat.cpp:2075 */
void CBaseEntity::TraceBleed_(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	if (BloodColor() == DONT_BLEED)
		return;

	if (!flDamage)
		return;

	if (!(bitsDamageType & (DMG_CRUSH | DMG_BULLET | DMG_SLASH | DMG_BLAST | DMG_CLUB | DMG_MORTAR)))
		return;

	// make blood decal on the wall! 
	TraceResult Bloodtr;
	Vector vecTraceDir;
	float flNoise;
	int cCount;
	int i;

	if (flDamage < 10.0f)
	{
		flNoise = 0.1f;
		cCount = 1;
	}
	else if (flDamage < 25.0f)
	{
		flNoise = 0.2f;
		cCount = 2;
	}
	else
	{
		flNoise = 0.3f;
		cCount = 4;
	}

	for (i = 0; i < cCount; i++)
	{
		// trace in the opposite direction the shot came from (the direction the shot is going)
		vecTraceDir = vecDir * -1.0f;

		vecTraceDir.x += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.y += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.z += RANDOM_FLOAT(-flNoise, flNoise);

		UTIL_TraceLine(ptr->vecEndPos, ptr->vecEndPos + vecTraceDir * -172.0f, ignore_monsters, ENT(pev), &Bloodtr);
		if (Bloodtr.flFraction != 1.0f)
		{
			if (!RANDOM_LONG(0, 2))
				UTIL_BloodDecalTrace(&Bloodtr, BloodColor());
		}
	}
}

/* <62e0e> ../cstrike/dlls/combat.cpp:2145 */
NOXREF void CBaseMonster::MakeDamageBloodDecal(int cCount, float flNoise, TraceResult *ptr, Vector &vecDir)
{
	// make blood decal on the wall! 
	TraceResult Bloodtr;
	Vector vecTraceDir; 
	int i;

	if (!IsAlive())
	{
		// dealing with a dead monster.
		if (pev->max_health <= 0)
		{
			// no blood decal for a monster that has already decalled its limit.
			return;
		}
		else
			pev->max_health--;
	}

	for (i = 0 ; i < cCount ; i++)
	{
		vecTraceDir = vecDir;

		vecTraceDir.x += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.y += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.z += RANDOM_FLOAT(-flNoise, flNoise);

		UTIL_TraceLine(ptr->vecEndPos, ptr->vecEndPos + vecTraceDir * 172, ignore_monsters, ENT(pev), &Bloodtr);

		if (Bloodtr.flFraction != 1.0)
		{
			UTIL_BloodDecalTrace(&Bloodtr, BloodColor());
		}
	}
}

/* <62f3e> ../cstrike/dlls/combat.cpp:2197 */
void CBaseMonster::BloodSplat(const Vector &vecSrc, const Vector &vecDir, int HitLocation, int iVelocity)
{
	if (HitLocation != HITGROUP_HEAD)
		return;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecSrc);
		WRITE_BYTE(TE_BLOODSTREAM);
		WRITE_COORD(vecSrc.x);
		WRITE_COORD(vecSrc.y);
		WRITE_COORD(vecSrc.z);
		WRITE_COORD(vecDir.x);
		WRITE_COORD(vecDir.y);
		WRITE_COORD(vecDir.z);
		WRITE_BYTE(223);
		WRITE_BYTE(iVelocity + RANDOM_LONG(0, 100));
	MESSAGE_END();
}

#ifdef HOOK_GAMEDLL

void CBaseMonster::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CBaseMonster::TraceAttack(entvars_t *pevAttacker,float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType)
{
	TraceAttack_(pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}

int CBaseMonster::TakeDamage(entvars_t *pevInflictor,entvars_t *pevAttacker,float flDamage,int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

int CBaseMonster::TakeHealth(float flHealth,int bitsDamageType)
{
	return TakeHealth_(flHealth, bitsDamageType);
}

void CBaseMonster::Killed(entvars_t *pevAttacker,int iGib)
{
	Killed_(pevAttacker, iGib);
}

float CBaseMonster::ChangeYaw(int speed)
{
	return ChangeYaw_(speed);
}

BOOL CBaseMonster::HasHumanGibs(void)
{
	return HasHumanGibs_();
}

BOOL CBaseMonster::HasAlienGibs(void)
{
	return HasHumanGibs_();
}

void CBaseMonster::FadeMonster(void)
{
	FadeMonster_();
}

void CBaseMonster::GibMonster(void)
{
	GibMonster_();
}

Activity CBaseMonster::GetDeathActivity(void)
{
	return GetDeathActivity_();
}

void CBaseMonster::BecomeDead(void)
{
	BecomeDead_();
}

BOOL CBaseMonster::ShouldFadeOnDeath(void)
{
	return ShouldFadeOnDeath_();
}

int CBaseMonster::IRelationship(CBaseEntity *pTarget)
{
	return IRelationship_(pTarget);
}

void CBaseMonster::MonsterInitDead(void)
{
	MonsterInitDead_();
}

void CBaseMonster::Look(int iDistance)
{
	Look_(iDistance);
}

CBaseEntity *CBaseMonster::BestVisibleEnemy(void)
{
	return BestVisibleEnemy_();
}

BOOL CBaseMonster::FInViewCone(CBaseEntity *pEntity)
{
	return FInViewCone_(pEntity);
}

BOOL CBaseMonster::FInViewCone(Vector *pOrigin)
{
	return FInViewCone_(pOrigin);
}

#endif // HOOK_GAMEDLL
