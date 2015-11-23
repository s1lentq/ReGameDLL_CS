#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

cvar_t cv_hostage_debug = { "hostage_debug", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_hostage_stop = { "hostage_stop", "0", FCVAR_SERVER, 0.0f, NULL };

#else

cvar_t cv_hostage_debug;
cvar_t cv_hostage_stop;

#endif // HOOK_GAMEDLL

CHostageManager *g_pHostages;
int g_iHostageNumber;

/* <45c3fa> ../cstrike/dlls/hostage/hostage.cpp:47 */
LINK_ENTITY_TO_CLASS(hostage_entity, CHostage);

/* <45c4d3> ../cstrike/dlls/hostage/hostage.cpp:48 */
LINK_ENTITY_TO_CLASS(monster_scientist, CHostage);

/* <45c228> ../cstrike/dlls/hostage/hostage.cpp:54 */
NOBODY void CHostage::__MAKE_VHOOK(Spawn)(void)
{
//	MAKE_STRING_CLASS(const char *str,
//				entvars_t *pev);  //    61
//	SetActivity(CHostage *const this,
//			int act);  //    83
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //    93
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //    93
//	edict(CBaseEntity *const this);  //   102
//	CHostageManager(CHostageManager *const this);  //    57
}

/* <45bf91> ../cstrike/dlls/hostage/hostage.cpp:137 */
NOBODY void CHostage::__MAKE_VHOOK(Precache)(void)
{
//	{
//		int which;                                            //   141
//	}
}

/* <45c5ac> ../cstrike/dlls/hostage/hostage.cpp:179 */
void CHostage::SetActivity(int act)
{
	if (m_Activity != act)
	{
		int sequence = LookupActivity(act);

		if (sequence != -1)
		{
			if (pev->sequence != sequence)
			{
				if ((m_Activity != ACT_WALK && m_Activity != ACT_RUN) || (act != ACT_WALK && act != ACT_RUN))
				{
					pev->frame = 0;
				}

				pev->sequence = sequence;
			}

			m_Activity = act;
			ResetSequenceInfo();
		}
	}
}

void (*pCHostage__IdleThink)(void);

/* <45f194> ../cstrike/dlls/hostage/hostage.cpp:204 */
NOBODY void __declspec(naked) CHostage::IdleThink(void)
{
	__asm
	{
		jmp pCHostage__IdleThink
	}
//	{
//		float const upkeepRate;                                //   220
//		float flInterval;                                     //   224
//		float const updateRate;                                //   236
//		{
//			float const giveUpTime;                        //   249
//		}
//		{
//			class CBasePlayer *player;                   //   263
//			GetFollowLeader(const class CHostageImprov *const this);  //   263
//			{
//				class CBaseEntity *pSpot;            //   271
//				BOOL bContinue;                       //   272
//				BOOL bResHostagePt;                   //   272
//				operator-(const Vector *const this,
//						const Vector &v);  //   284
//				Length(const Vector *const this);  //   284
//				operator-(const Vector *const this,
//						const Vector &v);  //   298
//				Length(const Vector *const this);  //   298
//			}
//			edict(CBaseEntity *const this);  //   332
//			edict(CBaseEntity *const this);  //   332
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //   337
//			edict(CBaseEntity *const this);  //   340
//			ENTINDEX(edict_t *pEdict);  //   340
//			edict(CBaseEntity *const this);  //   341
//			ENTINDEX(edict_t *pEdict);  //   341
//			Remove(CHostage *const this);  //   346
//		}
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   242
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   242
//		{
//			Vector vDistance;                       //   395
//			operator-(const Vector *const this,
//					const Vector &v);  //   395
//			Length(const Vector *const this);  //   397
//		}
//		Length(const Vector *const this);  //   378
//		SetActivity(CHostage *const this,
//				int act);  //   379
//		Length(const Vector *const this);  //   380
//		SetActivity(CHostage *const this,
//				int act);  //   381
//		SetActivity(CHostage *const this,
//				int act);  //   383
//	}
}

/* <45c041> ../cstrike/dlls/hostage/hostage.cpp:413 */
NOBODY void CHostage::Remove(void)
{
//	Vector(Vector::Remove(//		float X,
//		float Y,
//		float Z);  //   419
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   419
}

/* <45c624> ../cstrike/dlls/hostage/hostage.cpp:426 */
void CHostage::RePosition(void)
{
	pev->health = pev->max_health;
	pev->movetype = MOVETYPE_STEP;
	pev->solid = SOLID_SLIDEBOX;
	pev->takedamage = DAMAGE_YES;
	pev->deadflag = DEAD_NO;
	pev->velocity = Vector(0, 0, 0);
	pev->angles = m_vStartAngles;
	pev->effects &= ~EF_NODRAW;

	m_hTargetEnt = NULL;
	m_hStoppedTargetEnt = NULL;

	m_bTouched = FALSE;
	m_bRescueMe = FALSE;

	m_flNextRadarTime = 0;
	m_vOldPos = Vector(9999, 9999, 9999);

	UTIL_SetOrigin(pev, m_vStart);
	UTIL_SetSize(pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_HULL_MAX);

	DROP_TO_FLOOR(edict());
	SetActivity(ACT_IDLE);

	SetThink(&CHostage::IdleThink);
	pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);

	m_fHasPath = FALSE;
	nTargetNode = -1;

	m_flLastPathCheck = -1;
	m_flPathAcquired = -1;
	m_flPathCheckInterval = 0.1f;
	m_flNextFullThink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);
}

/* <45ee7f> ../cstrike/dlls/hostage/hostage.cpp:469 */
NOBODY int CHostage::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		float flActualDamage;                                 //   471
//		class CBasePlayer *pAttacker;                        //   472
//		GetModifiedDamage(CHostage *const this,
//					float flDamage,
//					int nHitGroup);  //   475
//		PlayPainSound(CHostage *const this);  //   485
//		{
//			class CBaseEntity *pAttackingEnt;            //   489
//			GetClassPtr<CBaseEntity>(CBaseEntity *a);  //   492
//		}
//		ApplyHostagePenalty(CHostage *const this,
//					class CBasePlayer *pAttacker);  //   518
//		SetFlinchActivity(CHostage *const this);  //   552
//	}
}

/* <45c783> ../cstrike/dlls/hostage/hostage.cpp:578 */
NOBODY float CHostage::GetModifiedDamage(float flDamage, int nHitGroup)
{
}

/* <45c7d3> ../cstrike/dlls/hostage/hostage.cpp:597 */
NOBODY void CHostage::PlayPainSound(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   603
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   605
}

/* <45c8c4> ../cstrike/dlls/hostage/hostage.cpp:612 */
NOBODY void CHostage::SetFlinchActivity(void)
{
//	{
//		Activity activity;                                    //   616
//		SetActivity(CHostage *const this,
//				int act);  //   637
//	}
}

/* <45c960> ../cstrike/dlls/hostage/hostage.cpp:642 */
NOBODY void CHostage::SetDeathActivity(void)
{
//	SetActivity(CHostage::SetDeathActivity(//			int act);  //   675
//	SetActivity(CHostage *const this,
//			int act);  //   678
//	SetActivity(CHostage *const this,
//			int act);  //   676
//	SetActivity(CHostage *const this,
//			int act);  //   677
//	SetActivity(CHostage *const this,
//			int act);  //   658
//	SetActivity(CHostage *const this,
//			int act);  //   656
}

/* <45cc41> ../cstrike/dlls/hostage/hostage.cpp:684 */
NOBODY void CHostage::AnnounceDeath(CBasePlayer *pAttacker)
{
//	edict(CBaseEntity *const this);  //   704
//	edict(CBaseEntity *const this);  //   704
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   707
//	edict(CBaseEntity *const this);  //   710
//	ENTINDEX(edict_t *pEdict);  //   710
//	edict(CBaseEntity *const this);  //   711
//	ENTINDEX(edict_t *pEdict);  //   711
}

/* <45cd6b> ../cstrike/dlls/hostage/hostage.cpp:717 */
NOBODY void CHostage::ApplyHostagePenalty(CBasePlayer *pAttacker)
{
//	{
//		int iHostagePenalty;                                  //   719
//		edict(CBaseEntity *const this);  //   735
//	}
}

/* <45cfd6> ../cstrike/dlls/hostage/hostage.cpp:740 */
NOBODY void CHostage::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CBasePlayer *pPlayer;                          //   742
//	}
//	Use(CHostage *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   740
}

/* <45cdba> ../cstrike/dlls/hostage/hostage.cpp:833 */
NOBODY void CHostage::PlayFollowRescueSound(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   845
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   843
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   837
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   839
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   841
}

/* <45d1ff> ../cstrike/dlls/hostage/hostage.cpp:851 */
NOBODY void CHostage::GiveCTTouchBonus(CBasePlayer *pPlayer)
{
//	edict(CBaseEntity *const this);  //   865
//	edict(CBaseEntity *const this);  //   865
}

/* <45bf69> ../cstrike/dlls/hostage/hostage.cpp:869 */
NOBODY int CHostage::__MAKE_VHOOK(ObjectCaps)(void)
{
}

/* <45c0e3> ../cstrike/dlls/hostage/hostage.cpp:876 */
NOBODY void CHostage::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
//	{
//		class Vector2D vPush;                                 //   901
//		float const pushForce;                                 //   904
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   895
//		{
//			class CBasePlayer *pPlayer;                  //   888
//		}
//	}
//	Touch(CHostage *const this,
//		class CBaseEntity *pOther);  //   876
}

/* <45dd66> ../cstrike/dlls/hostage/hostage.cpp:910 */
NOBODY void CHostage::DoFollow(void)
{
//	{
//		class CBaseEntity *pFollowing;                       //   912
//		Vector vecDest;                                 //   913
//		float flRadius;                                       //   914
//		float flDistToDest;                                   //   915
//		GetClassPtr<CBaseEntity>(CBaseEntity *a);  //   930
//		SetTargetEnt(CLocalNav *const this,
//				class CBaseEntity *pTarget);  //   931
//		operator-(const Vector *const this,
//				const Vector &v);  //   937
//		Length(const Vector *const this);  //   937
//		Length2D(const Vector *const this);  //  1009
//		operator-(const Vector *const this,
//				const Vector &v);  //   964
//		Length2D(const Vector *const this);  //   964
//		Length2D(const Vector *const this);  //   952
//		IsFollowingSomeone(CHostage *const this);  //   994
//		PointAt(CHostage *const this,
//			const Vector &vecLoc);  //   985
//	}
}

/* <45d278> ../cstrike/dlls/hostage/hostage.cpp:1018 */
NOBODY void CHostage::PointAt(const Vector &vecLoc)
{
//	operator-(const Vector *const this,
//			const Vector &v);  //  1022
}

/* <45d34c> ../cstrike/dlls/hostage/hostage.cpp:1025 */
NOBODY void CHostage::MoveToward(const Vector &vecLoc)
{
//	{
//		int nFwdMove;                                         //  1027
//		Vector vecFwd;                                  //  1028
//		Vector vecbigDest;                              //  1029
//		Vector vecMove;                                 //  1030
//		class CBaseEntity *pFollowing;                       //  1032
//		Vector vecAng;                                  //  1034
//		float flDist;                                         //  1040
//		GetClassPtr<CBaseEntity>(CBaseEntity *a);  //  1032
//		UTIL_MakeVectorsPrivate(Vector &vecAngles,
//					float *p_vForward,
//					float *p_vRight,
//					float *p_vUp);  //  1038
//		operator-(const Vector *const this,
//				const Vector &v);  //  1036
//		operator-(const Vector *const this,
//				const Vector &v);  //  1040
//		Length2D(const Vector *const this);  //  1040
//		operator*(const Vector *const this,
//				float fl);  //  1040
//		Length2D(const Vector *const this);  //  1040
//		operator-(const Vector *const this,
//				const Vector &v);  //  1040
//		Length2D(const Vector *const this);  //  1040
//		operator*(const Vector *const this,
//				float fl);  //  1041
//		operator+(const Vector *const this,
//				const Vector &v);  //  1043
//		{
//			float flSpeed;                                //  1049
//			Vector vecDest;                         //  1051
//			{
//				float flDist;                         //  1061
//				operator-(const Vector *const this,
//						const Vector &v);  //  1063
//				Length(const Vector *const this);  //  1063
//			}
//		}
//		operator*(const Vector *const this,
//				float fl);  //  1040
//		Length2D(const Vector *const this);  //  1040
//	}
}

/* <45d704> ../cstrike/dlls/hostage/hostage.cpp:1102 */
NOBODY BOOL CHostage::IsOnLadder(void)
{
}

/* <45d727> ../cstrike/dlls/hostage/hostage.cpp:1106 */
void CHostage::NavReady(void)
{
	CBaseEntity *pFollowing;
	Vector vecDest;
	float flRadius = 40.0;

	if (!m_hTargetEnt)
	{
		return;
	}

	pFollowing = GetClassPtr((CBaseEntity *)m_hTargetEnt->pev);
	vecDest = pFollowing->pev->origin;

	if (!(pFollowing->pev->flags & FL_ONGROUND))
	{
		TraceResult tr;
		Vector vecDropDest = (pFollowing->pev->origin - Vector(0, 0, 300));
		UTIL_TraceHull(vecDest, vecDropDest, ignore_monsters, human_hull, pFollowing->edict(), &tr);

		if (tr.fStartSolid || tr.flFraction == 1.0f)
		{
			return;
		}

		vecDest = tr.vecEndPos;
	}

	vecDest.z += pFollowing->pev->mins.z;
	m_LocalNav->SetTargetEnt(pFollowing);

	node_index_t nindexPath = m_LocalNav->FindPath(pev->origin, vecDest, flRadius, 1);
	if (nindexPath == -1)
	{
		if (!m_fHasPath)
		{
			m_flPathCheckInterval += 0.1;

			if (m_flPathCheckInterval >= 0.5f)
			{
				m_flPathCheckInterval = 0.5f;
			}
		}
	}
	else
	{
		m_fHasPath = TRUE;
		nTargetNode = -1;
		m_flPathAcquired = gpGlobals->time;
		m_flPathCheckInterval = 0.5;

		m_nPathNodes = m_LocalNav->SetupPathNodes(nindexPath, vecNodes, 1);
	}
}

/* <45edaa> ../cstrike/dlls/hostage/hostage.cpp:1159 */
NOBODY void CHostage::SendHostagePositionMsg(void)
{
//	{
//		class CBaseEntity *pEntity;                          //  1161
//		edict(CBaseEntity *const this);  //  1165
//		FNullEnt(const edict_t *pent);  //  1165
//		{
//			class CBasePlayer *pTempPlayer;              //  1169
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  1173
//		}
//	}
}

/* <45ecd5> ../cstrike/dlls/hostage/hostage.cpp:1189 */
NOBODY void CHostage::SendHostageEventMsg(void)
{
//	{
//		class CBaseEntity *pEntity;                          //  1191
//		edict(CBaseEntity *const this);  //  1195
//		FNullEnt(const edict_t *pent);  //  1195
//		{
//			class CBasePlayer *pTempPlayer;              //  1199
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  1203
//		}
//	}
}

/* <45d8a6> ../cstrike/dlls/hostage/hostage.cpp:1292 */
NOBODY void CHostage::Wiggle(void)
{
//	{
//		TraceResult tr;                                       //  1294
//		Vector vec;                                     //  1295
//		Vector wiggle_directions;                       //  1297
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		{
//			int i;                                        //  1309
//			{
//				Vector dest;                    //  1311
//				operator+(const Vector *const this,
//						const Vector &v);  //  1311
//				operator-(const Vector *const this,
//						const Vector &v);  //  1314
//			}
//		}
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator*(const Vector *const this,
//				float fl);  //  1307
//		operator+(const Vector *const this,
//				const Vector &v);  //  1338
//		Normalize(const Vector *const this);  //  1340
//		operator+(const Vector *const this,
//				const Vector &v);  //  1340
//	}
}

/* <45e00c> ../cstrike/dlls/hostage/hostage.cpp:1346 */
void CHostage::PreThink(void)
{
	Vector vecSrc;
	Vector vecDest;
	TraceResult tr;
	float flOrigDist;
	float flRaisedDist;
	float flInterval;

	if (m_improv != NULL)
	{
		return;
	}

	if (!(pev->flags & FL_ONGROUND))
	{
		return;
	}

	if (pev->velocity.Length2D() < 1)
	{
		return;
	}

	vecSrc = pev->origin;

#ifndef HOOK_GAMEDLL
	flInterval = m_LocalNav->ps_flStepSize;
#else
	flInterval = (*m_LocalNav->ps_flStepSize);
#endif // HOOK_GAMEDLL

	vecDest = vecSrc + pev->velocity * gpGlobals->frametime;
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid || tr.flFraction == 1.0f || tr.vecPlaneNormal.z > 0.7f)
	{
		return;
	}

	flOrigDist = (tr.vecEndPos - pev->origin).Length2D();
	vecSrc.z += flInterval;
	vecDest = vecSrc + (pev->velocity.Normalize() * 0.1);
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid)
	{
		return;
	}

	vecSrc = tr.vecEndPos;
	vecDest = tr.vecEndPos;
	vecDest.z -= flInterval;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.vecPlaneNormal.z < 0.7f)
	{
		return;
	}

	flRaisedDist = (tr.vecEndPos - pev->origin).Length2D();

	if (flRaisedDist > flOrigDist)
	{
		Vector vecNewOrigin = pev->origin;

		vecNewOrigin.z = tr.vecEndPos.z;
		UTIL_SetOrigin(pev, vecNewOrigin);
		pev->velocity.z += pev->gravity * g_psv_gravity->value * gpGlobals->frametime;
	}
}

/* <45e24e> ../cstrike/dlls/hostage/hostage.cpp:1421 */
void Hostage_RegisterCVars(void)
{
	CVAR_REGISTER(&cv_hostage_debug);
	CVAR_REGISTER(&cv_hostage_stop);
}

/* <45e2a6> ../cstrike/dlls/hostage/hostage.cpp:1430 */
NOBODY void InstallHostageManager(void)
{
//	~CHostageManager(CHostageManager *const this,
//			int const __in_chrg);  //  1433
//	CHostageManager(CHostageManager *const this);  //  1435
}

/* <45e375> ../cstrike/dlls/hostage/hostage.cpp:1443 */
NOBODY CHostageManager::CHostageManager(void)
{
	Q_memset(&m_chatter, 0, sizeof(m_chatter));
	m_hostageCount = 0;

//	SimpleChatter(SimpleChatter *const this);  //  1443
}

/* <45e39b> ../cstrike/dlls/hostage/hostage.cpp:1456 */
void CHostageManager::ServerActivate(void)
{
	m_hostageCount = 0;

	CBaseEntity *pEntity = NULL;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "hostage_entity")) != NULL)
	{
		AddHostage((CHostage *)pEntity);
	}

	if (UTIL_IsGame("czero"))
	{
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/getouttahere.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/illfollow.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letsdoit.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letsgo.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letshurry.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letsmove.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/okletsgo.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/youlead.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/comeback.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/dontleaveme.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/illstayhere.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/notleaveme.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/yeahillstay.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/donthurtme1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/donthurtme2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/dontkill.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/endpeace.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/nevernegotiate.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/nottellanything.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/surrender.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/whatdoyou.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/whyareyou.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/donthurtme1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/donthurtme2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/dontkill.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/dontkill.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/illgoback1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/illgoback2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/okokgoing.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/okokgoing2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/sorry1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/sorry2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/sorry3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain4.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain5.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain6.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/awwcrap1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/awwcrap2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/getdown1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/getdown2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/getdown3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookout1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookout2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookshooting1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookshooting2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookshooting3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/ohgod1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/ohgod2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awwcrap1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awwcrap2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/deargod1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/deargod2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/deargod3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohgod1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohgod2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohno1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohno2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awww2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awww4.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/awwcrap1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/awwcrap2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/lookout1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/lookout2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/areyousave.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/getmeoutta1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/getmeoutta2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/imahostage.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/rescueme1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/rescueme2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/theyregonna.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/areyousave.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/getmeoutta1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/getmeoutta2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/rescueme1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/rescueme2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/almostouttahere.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/almostthere.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/keepgoing.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/notfar.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/alldead.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/goodnews.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/outtahere.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over4.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over5.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/relief.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/doomed.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/godno.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/nowwhat.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/ohman.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/ohno.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/finally.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/finallysafe.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/thankyou.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/wemadeit1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/wemadeit2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/wemadeit3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/becareful1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/becareful2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/stillaround1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/stillaround2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/lookout1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/lookout2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/overthere1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/overthere2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/helpme1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/helpme2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/hey1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/hey2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/overhere1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough3.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough4.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough5.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough6.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_BLINDED, "hostage/hflash/cantsee.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_BLINDED, "hostage/hflash/myeyes.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/grenade1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/grenade2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/run.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/watchout.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_DEATH_CRY, "hostage/hdie/hdeath1.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_DEATH_CRY, "hostage/hdie/hdeath2.wav");
		m_chatter.AddSound(HOSTAGE_CHATTER_DEATH_CRY, "hostage/hdie/hdeath3.wav");
	}
}

/* <45e3a2> ../cstrike/dlls/hostage/hostage.cpp:1624 */
void CHostageManager::ServerDeactivate(void)
{
	;
}

/* <45e3f7> ../cstrike/dlls/hostage/hostage.cpp:1631 */
void CHostageManager::RestartRound(void)
{
	for (int i = 0; i < m_hostageCount; i++)
	{
		if (m_hostage[ i ]->m_improv != NULL)
		{
			m_hostage[ i ]->m_improv->OnReset();
		}
	}
}

/* <45e43d> ../cstrike/dlls/hostage/hostage.cpp:1640 */
void CHostageManager::AddHostage(CHostage *hostage)
{
	if (m_hostageCount >= MAX_HOSTAGES)
		return;

	int i;
	for (i = 0; i < m_hostageCount; i++)
	{
		if (m_hostage[i] == hostage)
		{
			break;
		}
	}

	if (i == m_hostageCount)
	{
		m_hostage[m_hostageCount] = hostage;
		m_hostageCount++;
	}
}

/* <45e47f> ../cstrike/dlls/hostage/hostage.cpp:1657 */
NOBODY bool CHostageManager::IsNearbyHostageTalking(CHostageImprov *improv)
{
//	{
//		int i;                                                //  1659
//		{
//			const class CHostageImprov *other;          //  1663
//			float const closeRange;                        //  1671
//			operator-(const Vector *const this,
//					const Vector &v);  //  1672
//			IsLengthGreaterThan(const Vector *const this,
//						float length);  //  1672
//			IsTalking(const class CHostageImprov *const this);  //  1675
//		}
//	}
}

/* <45e57b> ../cstrike/dlls/hostage/hostage.cpp:1689 */
NOBODY bool CHostageManager::IsNearbyHostageJumping(CHostageImprov *improv)
{
//	{
//		int i;                                                //  1691
//		{
//			const class CHostageImprov *other;          //  1695
//			float const closeRange;                        //  1703
//			operator-(const Vector *const this,
//					const Vector &v);  //  1704
//			IsLengthGreaterThan(const Vector *const this,
//						float length);  //  1704
//		}
//	}
}

/* <45e642> ../cstrike/dlls/hostage/hostage.cpp:1716 */
void CHostageManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	for (int i = 0; i < m_hostageCount; i++)
	{
		CHostageImprov *improv = m_hostage[ i ]->m_improv;

		if (improv != NULL)
		{
			improv->OnGameEvent(event, entity, other);
		}
	}
}

/* <45e6b8> ../cstrike/dlls/hostage/hostage.cpp:1726 */
SimpleChatter::SimpleChatter(void)
{
	for (int i = 0; i < ARRAYSIZE(m_chatter); i++)
	{
		m_chatter[i].count = 0;
		m_chatter[i].index = 0;
		m_chatter[i].needsShuffle = false;
	}
}

/* <45e6f0> ../cstrike/dlls/hostage/hostage.cpp:1737 */
SimpleChatter::~SimpleChatter(void)
{
	for (int i = 0; i < ARRAYSIZE(m_chatter); i++)
	{
		for (int f = 0; f < m_chatter[i].count; f++)
		{
			if (m_chatter[i].file[f].filename)
			{
				delete[] m_chatter[i].file[f].filename;
			}
		}
	}
}

/* <45e736> ../cstrike/dlls/hostage/hostage.cpp:1752 */
void SimpleChatter::AddSound(HostageChatterType type, char *filename)
{
	ChatterSet *chatter;
	char actualFilename[128];

	chatter = &m_chatter[ type ];

	Q_snprintf(actualFilename, sizeof(actualFilename), "sound\\%s", filename);

	chatter->file[ chatter->count ].filename = CloneString(filename);
	chatter->file[ chatter->count ].duration = (double)GET_APPROX_WAVE_PLAY_LEN(actualFilename) / 1000.0;

	chatter->needsShuffle = true;
	chatter->count++;

	PRECACHE_SOUND(filename);
}

/* <45e8c7> ../cstrike/dlls/hostage/hostage.cpp:1773 */
NOBODY void SimpleChatter::Shuffle(ChatterSet *chatter)
{
//	{
//		int i;                                                //  1775
//		{
//			int j;                                        //  1777
//			{
//				class SoundFile tmp;                  //  1781
//			}
//		}
//	}
}

/* <45e979> ../cstrike/dlls/hostage/hostage.cpp:1793 */
NOBODY char *SimpleChatter::GetSound(HostageChatterType type, float *duration)
{
//	{
//		class ChatterSet *chatter;                           //  1795
//		char *sound;                                         //  1805
//		Shuffle(SimpleChatter *const this,
//			class ChatterSet *chatter);  //  1800
//	}
}

/* <45ea1b> ../cstrike/dlls/hostage/hostage.cpp:1818 */
NOBODY float SimpleChatter::PlaySound(CBaseEntity *entity, HostageChatterType type)
{
//	{
//		class CHostage *hostage;                             //  1821
//		float duration;                                       //  1823
//		char *sound;                                         //  1824
//		GetSound(SimpleChatter *const this,
//			enum HostageChatterType type,
//			float *duration);  //  1824
//		{
//			int pitch;                                    //  1828
//			int attenuation;                              //  1838
//		}
//	}
}

#ifdef HOOK_GAMEDLL

void CHostage::Spawn(void)
{
	Spawn_();
}

void CHostage::Precache(void)
{
	Precache_();
}

int CHostage::ObjectCaps(void)
{
	return ObjectCaps_();
}

int CHostage::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

void CHostage::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CHostage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
