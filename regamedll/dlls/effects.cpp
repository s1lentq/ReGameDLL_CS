#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBubbling::m_SaveData[] =
{
	DEFINE_FIELD(CBubbling, m_density, FIELD_INTEGER),
	DEFINE_FIELD(CBubbling, m_frequency, FIELD_INTEGER),
	DEFINE_FIELD(CBubbling, m_state, FIELD_INTEGER),
};

TYPEDESCRIPTION CLightning::m_SaveData[] =
{
	DEFINE_FIELD(CLightning, m_active, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_iszStartEntity, FIELD_STRING),
	DEFINE_FIELD(CLightning, m_iszEndEntity, FIELD_STRING),
	DEFINE_FIELD(CLightning, m_life, FIELD_FLOAT),
	DEFINE_FIELD(CLightning, m_boltWidth, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_noiseAmplitude, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_brightness, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_speed, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_restrike, FIELD_FLOAT),
	DEFINE_FIELD(CLightning, m_spriteTexture, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_iszSpriteName, FIELD_STRING),
	DEFINE_FIELD(CLightning, m_frameStart, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_radius, FIELD_FLOAT),
};

TYPEDESCRIPTION CLaser::m_SaveData[] =
{
	DEFINE_FIELD(CLaser, m_pSprite, FIELD_CLASSPTR),
	DEFINE_FIELD(CLaser, m_iszSpriteName, FIELD_STRING),
	DEFINE_FIELD(CLaser, m_firePosition, FIELD_POSITION_VECTOR),
};

TYPEDESCRIPTION CGlow::m_SaveData[] =
{
	DEFINE_FIELD(CGlow, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CGlow, m_maxFrame, FIELD_FLOAT),
};

TYPEDESCRIPTION CSprite::m_SaveData[] =
{
	DEFINE_FIELD(CSprite, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CSprite, m_maxFrame, FIELD_FLOAT),
};

TYPEDESCRIPTION CGibShooter::m_SaveData[] =
{
	DEFINE_FIELD(CGibShooter, m_iGibs, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_iGibCapacity, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_iGibMaterial, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_iGibModelIndex, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_flGibVelocity, FIELD_FLOAT),
	DEFINE_FIELD(CGibShooter, m_flVariance, FIELD_FLOAT),
	DEFINE_FIELD(CGibShooter, m_flGibLife, FIELD_FLOAT),
};

#else

TYPEDESCRIPTION (*CBubbling::m_SaveData)[3];
TYPEDESCRIPTION (*CLightning::m_SaveData)[13];
TYPEDESCRIPTION (*CLaser::m_SaveData)[3];
TYPEDESCRIPTION (*CGlow::m_SaveData)[2];
TYPEDESCRIPTION (*CSprite::m_SaveData)[2];
TYPEDESCRIPTION (*CGibShooter::m_SaveData)[7];

#endif // HOOK_GAMEDLL

/* <76042> ../cstrike/dlls/effects.cpp:33 */
LINK_ENTITY_TO_CLASS(info_target, CPointEntity);

/* <7610e> ../cstrike/dlls/effects.cpp:57 */
LINK_ENTITY_TO_CLASS(env_bubbles, CBubbling);

/* <741e0> ../cstrike/dlls/effects.cpp:68 */
IMPLEMENT_SAVERESTORE(CBubbling, CBaseEntity);

/* <73427> ../cstrike/dlls/effects.cpp:48 */
NOBODY int CBubbling::ObjectCaps_(void)
{
	return 0;
}

/* <7344d> ../cstrike/dlls/effects.cpp:73 */
NOBODY void CBubbling::Spawn_(void)
{
//	{
//		int speed;                                            //    81
//	}
}

/* <73489> ../cstrike/dlls/effects.cpp:99 */
NOBODY void CBubbling::Precache_(void)
{
}

/* <742a4> ../cstrike/dlls/effects.cpp:105 */
NOBODY void CBubbling::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CBubbling *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   105
}

/* <74aae> ../cstrike/dlls/effects.cpp:123 */
NOBODY void CBubbling::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   125
//	FStrEq(const char *sz1,
//		const char *sz2);  //   130
//	KeyValue(CBubbling *const this,
//		KeyValueData *pkvd);  //   123
//	atoi(const char *__nptr);  //   127
//	atoi(const char *__nptr);  //   132
}

/* <73d03> ../cstrike/dlls/effects.cpp:145 */
NOBODY void CBubbling::FizzThink(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   147
//	edict(CBaseEntity *const this);  //   149
//	ENTINDEX(edict_t *pEdict);  //   149
}

/* <7620c> ../cstrike/dlls/effects.cpp:166 */
LINK_ENTITY_TO_CLASS(beam, CBeam);

/* <734b0> ../cstrike/dlls/effects.cpp:168 */
NOBODY void CBeam::Spawn_(void)
{
}

/* <734d6> ../cstrike/dlls/effects.cpp:174 */
NOBODY void CBeam::Precache_(void)
{
//	ENTINDEX(edict_t *pEdict);  //   177
//	SetStartEntity(CBeam *const this,
//			int entityIndex);  //   177
//	ENTINDEX(edict_t *pEdict);  //   179
//	SetEndEntity(CBeam *const this,
//			int entityIndex);  //   179
}

/* <762d8> ../cstrike/dlls/effects.cpp:182 */
NOBODY void CBeam::SetStartEntity(int entityIndex)
{
}

/* <76303> ../cstrike/dlls/effects.cpp:188 */
NOBODY void CBeam::SetEndEntity(int entityIndex)
{
}

/* <7632e> ../cstrike/dlls/effects.cpp:196 */
NOBODY const Vector &CBeam::GetStartPos(void)
{
	if (GetType() == BEAM_ENTS)
	{
		edict_t *pent = INDEXENT( GetStartEntity() );
		return pent->v.origin;
	}

	return pev->origin;
//	{
//		edict_t *pent;                                       //   200
//	}
//	GetType(CBeam *const this);  //   198
//	GetStartPos(CBeam *const this);  //   196
}

/* <7639a> ../cstrike/dlls/effects.cpp:207 */
NOBODY const Vector &CBeam::GetEndPos(void)
{
//	{
//		int type;                                             //   209
//		edict_t *pent;                                       //   215
//		GetType(CBeam *const this);  //   209
//	}
//	GetEndPos(CBeam *const this);  //   207
}

/* <76540> ../cstrike/dlls/effects.cpp:222 */
NOBODY CBeam *CBeam::BeamCreate(const char *pSpriteName, int width)
{
//	{
//		class CBeam *pBeam;                                  //   225
//		GetClassPtr<CBeam>(CBeam *a);  //   225
//		MAKE_STRING_CLASS(const char *str,
//					entvars_t *pev);  //   226
//	}
}

/* <76422> ../cstrike/dlls/effects.cpp:234 */
NOBODY void CBeam::BeamInit(const char *pSpriteName, int width)
{
//	SetNoise(CBeam *const this,
//		int amplitude);  //   239
//	SetColor(CBeam *const this,
//		int r,
//		int g,
//		int b);  //   237
//	SetBrightness(CBeam *const this,
//			int brightness);  //   238
//	SetFrame(CBeam *const this,
//		float frame);  //   240
//	SetScrollRate(CBeam *const this,
//			int speed);  //   241
//	SetWidth(CBeam *const this,
//		int width);  //   244
//	SetTexture(CBeam *const this,
//			int spriteIndex);  //   243
}

/* <76a56> ../cstrike/dlls/effects.cpp:251 */
NOBODY void CBeam::PointsInit(const Vector &start, const Vector &end)
{
//	SetType(CBeam *const this,
//		int type);  //   253
//	SetStartPos(CBeam *const this,
//			const Vector &pos);  //   254
//	SetEndPos(CBeam *const this,
//			const Vector &pos);  //   255
//	SetStartAttachment(CBeam *const this,
//				int attachment);  //   256
//	SetEndAttachment(CBeam *const this,
//			int attachment);  //   257
}

/* <7695b> ../cstrike/dlls/effects.cpp:262 */
NOBODY void CBeam::HoseInit(const Vector &start, const Vector &direction)
{
//	SetType(CBeam *const this,
//		int type);  //   264
//	SetStartPos(CBeam *const this,
//			const Vector &pos);  //   265
//	SetEndPos(CBeam *const this,
//			const Vector &pos);  //   266
//	SetStartAttachment(CBeam *const this,
//				int attachment);  //   267
//	SetEndAttachment(CBeam *const this,
//			int attachment);  //   268
}

/* <76887> ../cstrike/dlls/effects.cpp:273 */
NOBODY void CBeam::PointEntInit(const Vector &start, int endIndex)
{
//	SetType(CBeam *const this,
//		int type);  //   275
//	SetStartPos(CBeam *const this,
//			const Vector &pos);  //   276
//	SetEndEntity(CBeam *const this,
//			int entityIndex);  //   277
//	SetStartAttachment(CBeam *const this,
//				int attachment);  //   278
//	SetEndAttachment(CBeam *const this,
//			int attachment);  //   279
}

/* <767ab> ../cstrike/dlls/effects.cpp:283 */
NOBODY void CBeam::EntsInit(int startIndex, int endIndex)
{
//	SetType(CBeam *const this,
//		int type);  //   285
//	SetStartEntity(CBeam *const this,
//			int entityIndex);  //   286
//	SetEndEntity(CBeam *const this,
//			int entityIndex);  //   287
//	SetStartAttachment(CBeam *const this,
//				int attachment);  //   288
//	SetEndAttachment(CBeam *const this,
//			int attachment);  //   289
}

/* <7663a> ../cstrike/dlls/effects.cpp:294 */
NOBODY void CBeam::RelinkBeam(void)
{
//	{
//		const Vector &startPos;                  //   296
//		const Vector &endPos;                    //   296
//		GetStartPos(CBeam *const this);  //   296
//		GetEndPos(CBeam *const this);  //   296
//		operator-(const Vector *const this,
//				const Vector &v);  //   304
//		operator-(const Vector *const this,
//				const Vector &v);  //   305
//	}
}

/* <77305> ../cstrike/dlls/effects.cpp:311 */
NOBODY void CBeam::TriggerTouch(CBaseEntity *pOther)
{
//	{
//		class CBaseEntity *pOwner;                           //   317
//		Instance(edict_t *pent);  //   317
//	}
}

/* <773e2> ../cstrike/dlls/effects.cpp:325 */
NOBODY CBaseEntity *CBeam::RandomTargetname(const char *szName)
{
//	{
//		int total;                                            //   327
//		class CBaseEntity *pEntity;                          //   329
//		class CBaseEntity *pNewEntity;                       //   330
//	}
}

/* <77431> ../cstrike/dlls/effects.cpp:341 */
NOBODY void CBeam::DoSparks(const Vector &start, const Vector &end)
{
//	DoSparks(CBeam *const this,
//		const Vector &start,
//		const Vector &end);  //   341
}

/* <774c2> ../cstrike/dlls/effects.cpp:402 */
LINK_ENTITY_TO_CLASS(env_lightning, CLightning);

/* <77592> ../cstrike/dlls/effects.cpp:403 */
LINK_ENTITY_TO_CLASS(env_beam, CLightning);

/* <74192> ../cstrike/dlls/effects.cpp:441 */
IMPLEMENT_SAVERESTORE(CLightning, CBeam);

/* <744b2> ../cstrike/dlls/effects.cpp:444 */
NOBODY void CLightning::Spawn_(void)
{
//	Spawn(CLightning *const this);  //   444
}

/* <7357f> ../cstrike/dlls/effects.cpp:493 */
NOBODY void CLightning::Precache_(void)
{
}

/* <786a1> ../cstrike/dlls/effects.cpp:500 */
NOBODY void CLightning::Activate_(void)
{
//	ServerSide(CLightning *const this);  //   502
}

/* <7536c> ../cstrike/dlls/effects.cpp:507 */
NOBODY void CLightning::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   509
//	FStrEq(const char *sz1,
//		const char *sz2);  //   514
//	KeyValue(CLightning *const this,
//		KeyValueData *pkvd);  //   507
}

/* <75ad3> ../cstrike/dlls/effects.cpp:569 */
NOBODY void CLightning::ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	ToggleUse(CLightning *const this,
//			class CBaseEntity *pActivator,
//			class CBaseEntity *pCaller,
//			USE_TYPE useType,
//			float value);  //   569
}

/* <7422d> ../cstrike/dlls/effects.cpp:593 */
NOBODY void CLightning::StrikeUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	StrikeUse(CLightning *const this,
//			class CBaseEntity *pActivator,
//			class CBaseEntity *pCaller,
//			USE_TYPE useType,
//			float value);  //   593
}

/* <71e66> ../cstrike/dlls/effects.cpp:614 */
NOBODY int IsPointEntity(CBaseEntity *pEnt)
{
}

/* <77f64> ../cstrike/dlls/effects.cpp:625 */
NOBODY void CLightning::StrikeThink(void)
{
//	{
//		class CBaseEntity *pStart;                           //   653
//		class CBaseEntity *pEnd;                             //   654
//		{
//			class CBaseEntity *pStart;                   //   644
//			RandomTargetname(CBeam *const this,
//					const char *szName);  //   644
//		}
//		RandomTargetname(CBeam *const this,
//				const char *szName);  //   653
//		RandomTargetname(CBeam *const this,
//				const char *szName);  //   654
//		IsPointEntity(CBaseEntity *pEnt);  //   658
//		IsPointEntity(CBaseEntity *pEnt);  //   658
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   667
//		IsPointEntity(CBaseEntity *pEnt);  //   668
//		IsPointEntity(CBaseEntity *pEnt);  //   668
//		entindex(CBaseEntity *const this);  //   704
//		entindex(CBaseEntity *const this);  //   705
//		IsPointEntity(CBaseEntity *pEnt);  //   670
//		IsPointEntity(CBaseEntity *pEnt);  //   677
//		entindex(CBaseEntity *const this);  //   680
//		DoSparks(CBeam *const this,
//			const Vector &start,
//			const Vector &end);  //   720
//		{
//			TraceResult tr;                               //   723
//			BeamDamageInstant(CBeam *const this,
//						TraceResult *ptr,
//						float damage);  //   725
//		}
//	}
}

/* <77680> ../cstrike/dlls/effects.cpp:731 */
NOBODY void CBeam::BeamDamage(TraceResult *ptr)
{
//	{
//		class CBaseEntity *pHit;                             //   736
//		Instance(edict_t *pent);  //   736
//		operator-(const Vector *const this,
//				const Vector &v);  //   740
//		Normalize(const Vector *const this);  //   740
//	}
}

/* <777dd> ../cstrike/dlls/effects.cpp:753 */
NOBODY void CLightning::DamageThink(void)
{
//	{
//		TraceResult tr;                                       //   756
//		GetEndPos(CBeam *const this);  //   757
//		GetStartPos(CBeam *const this);  //   757
//	}
}

/* <77a90> ../cstrike/dlls/effects.cpp:763 */
NOBODY void CLightning::Zap(const Vector &vecSrc, const Vector &vecDest)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   765
//	DoSparks(CBeam *const this,
//		const Vector &start,
//		const Vector &end);  //   786
}

/* <77b45> ../cstrike/dlls/effects.cpp:789 */
NOBODY void CLightning::RandomArea(void)
{
//	{
//		int iLoops;                                           //   791
//		{
//			Vector vecSrc;                          //   795
//			Vector vecDir1;                         //   797
//			TraceResult tr1;                              //   799
//			Vector vecDir2;                         //   805
//			TraceResult tr2;                              //   810
//			Vector(Vector *const this,
//				const Vector &v);  //   795
//			Normalize(const Vector *const this);  //   798
//			operator*(const Vector *const this,
//					float fl);  //   800
//			operator+(const Vector *const this,
//					const Vector &v);  //   800
//			DotProduct(Vector &a,
//					const Vector &b);  //   808
//			Normalize(const Vector *const this);  //   809
//			operator*(const Vector *const this,
//					float fl);  //   811
//			operator+(const Vector *const this,
//					const Vector &v);  //   811
//			operator-(const Vector *const this,
//					const Vector &v);  //   816
//			Length(const Vector *const this);  //   816
//		}
//	}
}

/* <77de8> ../cstrike/dlls/effects.cpp:831 */
NOBODY void CLightning::RandomPoint(Vector &vecSrc)
{
//	{
//		int iLoops;                                           //   833
//		{
//			Vector vecDir1;                         //   837
//			TraceResult tr1;                              //   839
//			Normalize(const Vector *const this);  //   838
//			operator*(const Vector *const this,
//					float fl);  //   840
//			operator+(const Vector *const this,
//					const Vector &v);  //   840
//			operator-(const Vector *const this,
//					const Vector &v);  //   842
//			Length(const Vector *const this);  //   842
//		}
//	}
}

/* <78313> ../cstrike/dlls/effects.cpp:855 */
NOBODY void CLightning::BeamUpdateVars(void)
{
//	{
//		int beamType;                                         //   857
//		int pointStart;                                       //   858
//		int pointEnd;                                         //   858
//		edict_t *pStart;                                     //   860
//		edict_t *pEnd;                                       //   861
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   860
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   861
//		Instance(edict_t *pent);  //   862
//		IsPointEntity(CBaseEntity *pEnt);  //   862
//		Instance(edict_t *pent);  //   863
//		IsPointEntity(CBaseEntity *pEnt);  //   863
//		SetTexture(CBeam *const this,
//				int spriteIndex);  //   870
//		SetType(CBeam *const this,
//			int type);  //   892
//		SetStartPos(CBeam *const this,
//				const Vector &pos);  //   895
//		ENTINDEX(edict_t *pEdict);  //   903
//		SetStartEntity(CBeam *const this,
//				int entityIndex);  //   903
//		ENTINDEX(edict_t *pEdict);  //   904
//		SetEndEntity(CBeam *const this,
//				int entityIndex);  //   904
//		SetWidth(CBeam *const this,
//			int width);  //   909
//		SetNoise(CBeam *const this,
//			int amplitude);  //   910
//		SetScrollRate(CBeam *const this,
//				int speed);  //   912
//		SetFrame(CBeam *const this,
//			float frame);  //   911
//		SetFlags(CBeam *const this,
//			int flags);  //   916
//		SetEndEntity(CBeam *const this,
//				int entityIndex);  //   899
//		SetEndPos(CBeam *const this,
//				const Vector &pos);  //   897
//		SetFlags(CBeam *const this,
//			int flags);  //   914
//	}
}

/* <786d8> ../cstrike/dlls/effects.cpp:920 */
LINK_ENTITY_TO_CLASS(env_laser, CLaser);

/* <74144> ../cstrike/dlls/effects.cpp:929 */
IMPLEMENT_SAVERESTORE(CLaser, CBeam);

/* <76b3f> ../cstrike/dlls/effects.cpp:931 */
NOBODY void CLaser::Spawn_(void)
{
//	Spawn(CLaser *const this);  //   931
}

/* <73d82> ../cstrike/dlls/effects.cpp:960 */
NOBODY void CLaser::Precache_(void)
{
//	Precache(CLaser *const this);  //   960
}

/* <74ff2> ../cstrike/dlls/effects.cpp:968 */
NOBODY void CLaser::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   970
//	FStrEq(const char *sz1,
//		const char *sz2);  //   975
//	KeyValue(CLaser *const this,
//		KeyValueData *pkvd);  //   968
//	atof(const char *__nptr);  //   977
//	SetWidth(CBeam *const this,
//		int width);  //   977
}

/* <787a8> ../cstrike/dlls/effects.cpp:1015 */
NOBODY int CLaser::IsOn(void)
{
}

/* <787c9> ../cstrike/dlls/effects.cpp:1023 */
NOBODY void CLaser::TurnOff(void)
{
//	TurnOff(CSprite *const this);  //  1028
}

/* <78804> ../cstrike/dlls/effects.cpp:1032 */
NOBODY void CLaser::TurnOn(void)
{
//	TurnOn(CSprite *const this);  //  1036
}

/* <75f0a> ../cstrike/dlls/effects.cpp:1042 */
NOBODY void CLaser::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int active;                                           //  1044
//		IsOn(CLaser *const this);  //  1044
//		TurnOff(CLaser *const this);  //  1050
//		TurnOn(CLaser *const this);  //  1054
//	}
//	Use(CLaser *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  1042
}

/* <78841> ../cstrike/dlls/effects.cpp:1059 */
NOBODY void CLaser::FireAtPoint(TraceResult &tr)
{
//	SetEndPos(CBeam *const this,
//			const Vector &pos);  //  1061
//	GetStartPos(CBeam *const this);  //  1066
//	DoSparks(CBeam *const this,
//		const Vector &start,
//		const Vector &end);  //  1066
}

/* <778f6> ../cstrike/dlls/effects.cpp:1069 */
NOBODY void CLaser::StrikeThink(void)
{
//	{
//		class CBaseEntity *pEnd;                             //  1071
//		TraceResult tr;                                       //  1076
//		RandomTargetname(CBeam *const this,
//				const char *szName);  //  1071
//		FireAtPoint(CLaser *const this,
//				TraceResult &tr);  //  1079
//	}
}

/* <7894f> ../cstrike/dlls/effects.cpp:1099 */
LINK_ENTITY_TO_CLASS(env_glow, CGlow);

/* <740f6> ../cstrike/dlls/effects.cpp:1107 */
IMPLEMENT_SAVERESTORE(CGlow, CPointEntity);

/* <735a6> ../cstrike/dlls/effects.cpp:1109 */
NOBODY void CGlow::Spawn_(void)
{
}

/* <74606> ../cstrike/dlls/effects.cpp:1127 */
NOBODY void CGlow::Think_(void)
{
//	Animate(CGlow::Think(//		float frames);  //  1129
}

/* <78a1f> ../cstrike/dlls/effects.cpp:1136 */
NOBODY void CGlow::Animate(float frames)
{
}

/* <78a4a> ../cstrike/dlls/effects.cpp:1157 */
LINK_ENTITY_TO_CLASS(env_bombglow, CBombGlow);

/* <735cd> ../cstrike/dlls/effects.cpp:1161 */
NOBODY void CBombGlow::Spawn(void)
{
}

/* <73a40> ../cstrike/dlls/effects.cpp:1184 */
NOBODY void CBombGlow::Think(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //  1215
}

/* <78b1a> ../cstrike/dlls/effects.cpp:1226 */
LINK_ENTITY_TO_CLASS(env_sprite, CSprite);

/* <740a8> ../cstrike/dlls/effects.cpp:1234 */
IMPLEMENT_SAVERESTORE(CSprite, CPointEntity);

/* <75dc8> ../cstrike/dlls/effects.cpp:1236 */
NOBODY void CSprite::Spawn_(void)
{
//	TurnOff(CSprite *const this);  //  1248
//	TurnOn(CSprite *const this);  //  1250
}

/* <75d55> ../cstrike/dlls/effects.cpp:1260 */
NOBODY void CSprite::Restart_(void)
{
//	TurnOn(CSprite *const this);  //  1270
//	Restart(CSprite *const this);  //  1260
}

/* <74436> ../cstrike/dlls/effects.cpp:1273 */
NOBODY void CSprite::Precache_(void)
{
//	SetAttachment(CSprite::Precache(//			edict_t *pEntity,
//			int attachment);  //  1279
//	Precache(CSprite *const this);  //  1273
}

/* <78bea> ../cstrike/dlls/effects.cpp:1289 */
NOBODY void CSprite::SpriteInit(const char *pSpriteName, const Vector &origin)
{
}

/* <78c1d> ../cstrike/dlls/effects.cpp:1296 */
NOBODY CSprite *CSprite::SpriteCreate(const char *pSpriteName, const Vector &origin, BOOL animate)
{
//	{
//		class CSprite *pSprite;                              //  1298
//		GetClassPtr<CSprite>(CSprite *a);  //  1298
//		SpriteInit(CSprite *const this,
//				const char *pSpriteName,
//				const Vector &origin);  //  1299
//		MAKE_STRING_CLASS(const char *str,
//					entvars_t *pev);  //  1300
//		TurnOn(CSprite *const this);  //  1304
//	}
}

/* <75679> ../cstrike/dlls/effects.cpp:1310 */
NOBODY void CSprite::AnimateThink(void)
{
}

/* <78d6b> ../cstrike/dlls/effects.cpp:1318 */
NOBODY void CSprite::AnimateUntilDead(void)
{
//	AnimateThink(CSprite *const this);  //  1324
}

/* <78de9> ../cstrike/dlls/effects.cpp:1329 */
NOBODY void CSprite::Expand(float scaleSpeed, float fadeSpeed)
{
}

/* <73e2e> ../cstrike/dlls/effects.cpp:1340 */
NOBODY void CSprite::ExpandThink(void)
{
//	{
//		float frametime;                                      //  1342
//	}
//	ExpandThink(CSprite *const this);  //  1340
}

/* <78e2e> ../cstrike/dlls/effects.cpp:1358 */
NOBODY void CSprite::Animate(float frames)
{
//	TurnOff(CSprite *const this);  //  1365
}

/* <78e73> ../cstrike/dlls/effects.cpp:1376 */
NOBODY void CSprite::TurnOff(void)
{
}

/* <78e94> ../cstrike/dlls/effects.cpp:1383 */
NOBODY void CSprite::TurnOn(void)
{
}

/* <75e27> ../cstrike/dlls/effects.cpp:1396 */
NOBODY void CSprite::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int on;                                               //  1398
//		TurnOn(CSprite *const this);  //  1407
//	}
//	Use(CSprite *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  1396
}

/* <7405a> ../cstrike/dlls/effects.cpp:1448 */
IMPLEMENT_SAVERESTORE(CGibShooter, CBaseDelay);

/* <78eb7> ../cstrike/dlls/effects.cpp:1449 */
LINK_ENTITY_TO_CLASS(gibshooter, CGibShooter);

/* <73dbb> ../cstrike/dlls/effects.cpp:1452 */
NOBODY void CGibShooter::Precache_(void)
{
//	Precache(CGibShooter *const this);  //  1452
}

/* <74886> ../cstrike/dlls/effects.cpp:1465 */
NOBODY void CGibShooter::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1467
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1472
//	KeyValue(CGibShooter *const this,
//		KeyValueData *pkvd);  //  1465
//	atoi(const char *__nptr);  //  1469
//	atof(const char *__nptr);  //  1474
}

/* <735f4> ../cstrike/dlls/effects.cpp:1493 */
NOBODY void CGibShooter::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <73cb5> ../cstrike/dlls/effects.cpp:1499 */
NOBODY void CGibShooter::Spawn_(void)
{
}

/* <744ff> ../cstrike/dlls/effects.cpp:1521 */
NOBODY CGib *CGibShooter::CreateGib_(void)
{
//	{
//		class CGib *pGib;                                    //  1526
//		GetClassPtr<CGib>(CGib *a);  //  1526
//	}
}

/* <75751> ../cstrike/dlls/effects.cpp:1541 */
NOBODY void CGibShooter::ShootThink(void)
{
//	{
//		Vector vecShootDir;                             //  1545
//		class CGib *pGib;                                    //  1554
//		operator*(const Vector *const this,
//				float fl);  //  1549
//		operator*(const Vector *const this,
//				float fl);  //  1549
//		operator+(const Vector *const this,
//				const Vector &v);  //  1549
//		operator*(const Vector *const this,
//				float fl);  //  1550
//		operator*(const Vector *const this,
//				float fl);  //  1550
//		operator+(const Vector *const this,
//				const Vector &v);  //  1550
//		operator*(const Vector *const this,
//				float fl);  //  1551
//		operator*(const Vector *const this,
//				float fl);  //  1551
//		operator+(const Vector *const this,
//				const Vector &v);  //  1551
//		Normalize(const Vector *const this);  //  1553
//		{
//			float thinkTime;                              //  1564
//			operator*(const Vector *const this,
//					float fl);  //  1559
//		}
//	}
}

/* <78f87> ../cstrike/dlls/effects.cpp:1600 */
LINK_ENTITY_TO_CLASS(env_shooter, CEnvShooter);

/* <749e7> ../cstrike/dlls/effects.cpp:1602 */
NOBODY void CEnvShooter::KeyValue_(KeyValueData *pkvd)
{
//	{
//		int iNoise;                                           //  1611
//	}
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1604
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1609
//	KeyValue(CEnvShooter *const this,
//		KeyValueData *pkvd);  //  1602
}

/* <73cdc> ../cstrike/dlls/effects.cpp:1644 */
NOBODY void CEnvShooter::Precache_(void)
{
}

/* <7464b> ../cstrike/dlls/effects.cpp:1651 */
NOBODY CGib *CEnvShooter::CreateGib_(void)
{
//	{
//		class CGib *pGib;                                    //  1653
//		int bodyPart;                                         //  1657
//		GetClassPtr<CGib>(CGib *a);  //  1653
//	}
}

/* <79057> ../cstrike/dlls/effects.cpp:1696 */
LINK_ENTITY_TO_CLASS(test_effect, CTestEffect);

/* <73656> ../cstrike/dlls/effects.cpp:1698 */
NOBODY void CTestEffect::Spawn_(void)
{
}

/* <7367c> ../cstrike/dlls/effects.cpp:1703 */
NOBODY void CTestEffect::Precache_(void)
{
}

/* <76e39> ../cstrike/dlls/effects.cpp:1708 */
NOBODY void CTestEffect::TestThink(void)
{
//	{
//		int i;                                                //  1710
//		float t;                                              //  1711
//		{
//			class CBeam *pbeam;                          //  1715
//			TraceResult tr;                               //  1717
//			Vector vecSrc;                          //  1719
//			Vector vecDir;                          //  1720
//			Normalize(const Vector *const this);  //  1721
//			BeamCreate(const char *pSpriteName,
//					int width);  //  1715
//			Vector(Vector *const this,
//				const Vector &v);  //  1719
//			operator*(const Vector *const this,
//					float fl);  //  1722
//			operator+(const Vector *const this,
//					const Vector &v);  //  1722
//			PointsInit(CBeam *const this,
//					const Vector &start,
//					const Vector &end);  //  1724
//			SetColor(CBeam *const this,
//				int r,
//				int g,
//				int b);  //  1726
//			SetWidth(CBeam *const this,
//				int width);  //  1727
//			SetScrollRate(CBeam *const this,
//					int speed);  //  1728
//		}
//		SetBrightness(CBeam *const this,
//				int brightness);  //  1740
//	}
}

/* <736a2> ../cstrike/dlls/effects.cpp:1759 */
NOBODY void CTestEffect::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <79127> ../cstrike/dlls/effects.cpp:1788 */
LINK_ENTITY_TO_CLASS(env_blood, CBlood);

/* <73c8f> ../cstrike/dlls/effects.cpp:1797 */
NOBODY void CBlood::Spawn_(void)
{
}

/* <74c34> ../cstrike/dlls/effects.cpp:1807 */
NOBODY void CBlood::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1809
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1824
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //  1830
//	{
//		int color;                                            //  1811
//		atoi(const char *__nptr);  //  1811
//		SetColor(CBlood *const this,
//			int color);  //  1818
//		SetColor(CBlood *const this,
//			int color);  //  1815
//	}
//	KeyValue(CBlood *const this,
//		KeyValueData *pkvd);  //  1807
}

/* <791f7> ../cstrike/dlls/effects.cpp:1834 */
NOBODY Vector CBlood::Direction(void)
{
}

/* <79256> ../cstrike/dlls/effects.cpp:1843 */
NOBODY Vector CBlood::BloodPosition(CBaseEntity *pActivator)
{
//	{
//		edict_t *pPlayer;                                    //  1847
//		operator+(const Vector *const this,
//				const Vector &v);  //  1856
//		operator+(const Vector *const this,
//				const Vector &v);  //  1856
//		edict(CBaseEntity *const this);  //  1851
//	}
//	Vector(Vector *const this,
//		const Vector &v);  //  1859
}

/* <79351> ../cstrike/dlls/effects.cpp:1863 */
NOBODY void CBlood::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Color(CBlood *const this);  //  1866
//	Direction(CBlood *const this);  //  1866
//	{
//		Vector forward;                                 //  1872
//		Vector start;                                   //  1873
//		TraceResult tr;                                       //  1874
//		Direction(CBlood *const this);  //  1872
//		BloodAmount(CBlood *const this);  //  1876
//		operator*(const Vector *const this,
//				float fl);  //  1876
//		operator*(const Vector *const this,
//				float fl);  //  1876
//		operator+(const Vector *const this,
//				const Vector &v);  //  1876
//		Color(CBlood *const this);  //  1878
//	}
//	Direction(CBlood *const this);  //  1868
//	Color(CBlood *const this);  //  1868
}

/* <79594> ../cstrike/dlls/effects.cpp:1905 */
LINK_ENTITY_TO_CLASS(env_shake, CShake);

/* <73705> ../cstrike/dlls/effects.cpp:1919 */
NOBODY void CShake::Spawn_(void)
{
}

/* <74d76> ../cstrike/dlls/effects.cpp:1931 */
NOBODY void CShake::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1933
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1938
//	KeyValue(CShake *const this,
//		KeyValueData *pkvd);  //  1931
//	atof(const char *__nptr);  //  1935
//	atof(const char *__nptr);  //  1940
}

/* <73c2d> ../cstrike/dlls/effects.cpp:1958 */
NOBODY void CShake::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <79664> ../cstrike/dlls/effects.cpp:1979 */
LINK_ENTITY_TO_CLASS(env_fade, CFade);

/* <7372b> ../cstrike/dlls/effects.cpp:1987 */
NOBODY void CFade::Spawn_(void)
{
}

/* <74efa> ../cstrike/dlls/effects.cpp:1996 */
NOBODY void CFade::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1998
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2003
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //  2009
//	atof(const char *__nptr);  //  2000
//	KeyValue(CFade *const this,
//		KeyValueData *pkvd);  //  1996
}

/* <73bb4> ../cstrike/dlls/effects.cpp:2013 */
NOBODY void CFade::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int fadeFlags;                                        //  2015
//	}
}

/* <79734> ../cstrike/dlls/effects.cpp:2048 */
LINK_ENTITY_TO_CLASS(env_message, CMessage);

/* <73751> ../cstrike/dlls/effects.cpp:2051 */
NOBODY void CMessage::Spawn_(void)
{
}

/* <73df7> ../cstrike/dlls/effects.cpp:2085 */
NOBODY void CMessage::Precache_(void)
{
//	Precache(CMessage *const this);  //  2085
}

/* <74765> ../cstrike/dlls/effects.cpp:2091 */
NOBODY void CMessage::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2093
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2098
//	KeyValue(CMessage *const this,
//		KeyValueData *pkvd);  //  2091
//	atof(const char *__nptr);  //  2100
}

/* <73aa5> ../cstrike/dlls/effects.cpp:2113 */
NOBODY void CMessage::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CBaseEntity *pPlayer;                          //  2115
//		Instance(edict_t *pent);  //  2125
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  2132
//	}
}

/* <79804> ../cstrike/dlls/effects.cpp:2160 */
LINK_ENTITY_TO_CLASS(env_funnel, CEnvFunnel);

/* <73778> ../cstrike/dlls/effects.cpp:2155 */
NOBODY void CEnvFunnel::Precache_(void)
{
}

/* <7379f> ../cstrike/dlls/effects.cpp:2162 */
NOBODY void CEnvFunnel::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  2164
}

/* <7382b> ../cstrike/dlls/effects.cpp:2187 */
NOBODY void CEnvFunnel::Spawn_(void)
{
}

/* <73852> ../cstrike/dlls/effects.cpp:2207 */
NOBODY void CEnvBeverage::Precache_(void)
{
	PRECACHE_MODEL("models/can.mdl");
	PRECACHE_SOUND("weapons/g_bounce3.wav");
}

/* <798d4> ../cstrike/dlls/effects.cpp:2213 */
LINK_ENTITY_TO_CLASS(env_beverage, CEnvBeverage);

/* <7439c> ../cstrike/dlls/effects.cpp:2215 */
NOBODY void CEnvBeverage::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CBaseEntity *pCan;                             //  2223
//	}
//	Use(CEnvBeverage *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  2215
}

/* <73879> ../cstrike/dlls/effects.cpp:2242 */
NOBODY void CEnvBeverage::Spawn_(void)
{
}

/* <738a0> ../cstrike/dlls/effects.cpp:2267 */
NOBODY void CItemSoda::Precache_(void)
{
}

/* <799a4> ../cstrike/dlls/effects.cpp:2271 */
LINK_ENTITY_TO_CLASS(item_sodacan, CItemSoda);

/* <738c6> ../cstrike/dlls/effects.cpp:2273 */
NOBODY void CItemSoda::Spawn_(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //  2280
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //  2280
}

/* <73961> ../cstrike/dlls/effects.cpp:2286 */
NOBODY void CItemSoda::CanThink(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //  2288
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //  2291
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //  2291
}

/* <7431d> ../cstrike/dlls/effects.cpp:2296 */
NOBODY void CItemSoda::CanTouch(CBaseEntity *pOther)
{
//	CanTouch(CItemSoda *const this,
//		class CBaseEntity *pOther);  //  2296
}

#ifdef HOOK_GAMEDLL

void CSprite::Spawn(void)
{
	Spawn_();
}

void CSprite::Precache(void)
{
	Precache_();
}

void CSprite::Restart(void)
{
	Restart_();
}

int CSprite::Save(CSave &save)
{
	return Save_(save);
}

int CSprite::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CSprite::ObjectCaps(void)
{
	return ObjectCaps_();
}

void CSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBeam::Spawn(void)
{
	Spawn_();
}

void CBeam::Precache(void)
{
	Precache_();
}

int CBeam::ObjectCaps(void)
{
	return ObjectCaps_();
}

Vector CBeam::Center(void)
{
	return Center_();
}

void CLaser::Spawn(void)
{
	Spawn_();
}

void CLaser::Precache(void)
{
	Precache_();
}

void CLaser::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CLaser::Save(CSave &save)
{
	return Save_(save);
}

int CLaser::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CLaser::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBubbling::Spawn(void)
{
	Spawn_();
}

void CBubbling::Precache(void)
{
	Precache_();
}

void CBubbling::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBubbling::Save(CSave &save)
{
	return Save_(save);
}

int CBubbling::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CBubbling::ObjectCaps(void)
{
	return ObjectCaps_();
}

void CBubbling::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CLightning::Spawn(void)
{
	Spawn_();
}

void CLightning::Precache(void)
{
	Precache_();
}

void CLightning::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CLightning::Save(CSave &save)
{
	return Save_(save);
}

int CLightning::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CLightning::Activate(void)
{
	Activate_();
}

void CGlow::Spawn(void)
{
	Spawn_();
}

int CGlow::Save(CSave &save)
{
	return Save_(save);
}

int CGlow::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGlow::Think(void)
{
	Think_();
}

void CGibShooter::Spawn(void)
{
	Spawn_();
}

void CGibShooter::Precache(void)
{
	Precache_();
}

void CGibShooter::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CGibShooter::Save(CSave &save)
{
	return Save_(save);
}

int CGibShooter::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGibShooter::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

CGib *CGibShooter::CreateGib(void)
{
	return CreateGib_();
}

void CEnvShooter::Precache(void)
{
	Precache_();
}

void CEnvShooter::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

CGib *CEnvShooter::CreateGib(void)
{
	return CreateGib_();
}

void CTestEffect::Spawn(void)
{
	Spawn_();
}

void CTestEffect::Precache(void)
{
	Precache_();
}

void CTestEffect::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBlood::Spawn(void)
{
	Spawn_();
}

void CBlood::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CBlood::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CShake::Spawn(void)
{
	Spawn_();
}

void CShake::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CShake::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFade::Spawn(void)
{
	Spawn_();
}

void CFade::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CFade::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CMessage::Spawn(void)
{
	Spawn_();
}

void CMessage::Precache(void)
{
	Precache_();
}

void CMessage::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CMessage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CEnvFunnel::Spawn(void)
{
	Spawn_();
}

void CEnvFunnel::Precache(void)
{
	Precache_();
}

void CEnvFunnel::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CEnvBeverage::Spawn(void)
{
	Spawn_();
}

void CEnvBeverage::Precache(void)
{
	Precache_();
}

void CEnvBeverage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CItemSoda::Spawn(void)
{
	Spawn_();
}

void CItemSoda::Precache(void)
{
	Precache_();
}

#endif // HOOK_GAMEDLL
