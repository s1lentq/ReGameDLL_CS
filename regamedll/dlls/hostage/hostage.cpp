#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//cvar_t cv_hostage_stop = { "hostage_stop", "0", FCVAR_SERVER };
//cvar_t cv_hostage_debug = { "hostage_debug", "0", FCVAR_SERVER };

#else

//cvar_t cv_hostage_debug;
//cvar_t cv_hostage_stop;

#endif // HOOK_GAMEDLL

CHostageManager *g_pHostages;
int g_iHostageNumber;

/* <45c3fa> ../cstrike/dlls/hostage/hostage.cpp:47 */
LINK_ENTITY_TO_CLASS(hostage_entity, CHostage);

/* <45c4d3> ../cstrike/dlls/hostage/hostage.cpp:48 */
LINK_ENTITY_TO_CLASS(monster_scientist, CHostage);

/* <45c228> ../cstrike/dlls/hostage/hostage.cpp:54 */
NOBODY void CHostage::Spawn_(void)
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
NOBODY void CHostage::Precache_(void)
{
//	{
//		int which;                                            //   141
//	}
}

/* <45c5ac> ../cstrike/dlls/hostage/hostage.cpp:179 */
NOBODY void CHostage::SetActivity(int act)
{
//	{
//		int sequence;                                         //   181
//	}
//	SetActivity(CHostage *const this,
//			int act);  //   179
}

/* <45f194> ../cstrike/dlls/hostage/hostage.cpp:204 */
NOBODY void CHostage::IdleThink(void)
{
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
NOBODY void CHostage::RePosition(void)
{
//	Vector(Vector::RePosition(//		float X,
//		float Y,
//		float Z);  //   449
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //   449
//	edict(CBaseEntity *const this);  //   451
//	SetActivity(CHostage *const this,
//			int act);  //   453
}

/* <45ee7f> ../cstrike/dlls/hostage/hostage.cpp:469 */
NOBODY int CHostage::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
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
NOBODY void CHostage::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
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
NOBODY int CHostage::ObjectCaps_(void)
{
}

/* <45c0e3> ../cstrike/dlls/hostage/hostage.cpp:876 */
NOBODY void CHostage::Touch_(CBaseEntity *pOther)
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
NOBODY void CHostage::NavReady(void)
{
//	{
//		class CBaseEntity *pFollowing;                       //  1108
//		Vector vecDest;                                 //  1109
//		float flRadius;                                       //  1110
//		node_index_t nindexPath;                              //  1111
//		GetClassPtr<CBaseEntity>(CBaseEntity *a);  //  1118
//		{
//			TraceResult tr;                               //  1123
//			Vector vecDropDest;                     //  1124
//			edict(CBaseEntity *const this);  //  1129
//		}
//		SetTargetEnt(CLocalNav *const this,
//				class CBaseEntity *pTarget);  //  1142
//	}

	CBaseEntity *pFollowing;
	Vector vecDest;
	float flRadius = 40.0;

	node_index_t nindexPath;

	if (!m_hTargetEnt)
		return;

	pFollowing = GetClassPtr((CBaseEntity *)m_hTargetEnt->pev);
	vecDest = pFollowing->pev->origin;

	if (!(pFollowing->pev->flags & FL_ONGROUND))
	{
		TraceResult tr;
		Vector vecDropDest = pFollowing->pev->origin - Vector(0, 0, 300);

		UTIL_TraceHull(vecDest, vecDropDest, ignore_monsters, human_hull, pFollowing->edict(), &tr);

		if (tr.fStartSolid || tr.flFraction == 1.0)
			return;

		vecDest = tr.vecEndPos;
	}

	vecDest.z += pFollowing->pev->mins.z;
	m_LocalNav->SetTargetEnt(pFollowing);
	nindexPath = m_LocalNav->FindPath(pev->origin, vecDest, flRadius, 1);// TODO: Reverse me

	if (nindexPath != -1)
	{
		m_fHasPath = TRUE;
		nTargetNode = -1;
		m_flPathCheckInterval = 0.5;

		m_flPathAcquired = gpGlobals->time;
		m_nPathNodes = m_LocalNav->SetupPathNodes(nindexPath, vecNodes, 1);// TODO: Reverse me
	}
	else if (!m_fHasPath)
	{
		m_flPathCheckInterval += 0.1;

		if (m_flPathCheckInterval >= 0.5f)
			m_flPathCheckInterval = 0.5;
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

	if (m_improv)
		return;

	if (!(pev->flags & FL_ONGROUND))
		return;

	if (pev->velocity.Length2D() < 1)
		return;

	vecSrc = pev->origin;

#ifndef HOOK_GAMEDLL
	flInterval = m_LocalNav->ps_flStepSize;
#else
	flInterval = (*m_LocalNav->ps_flStepSize);
#endif // HOOK_GAMEDLL

	vecDest = vecSrc + pev->velocity * gpGlobals->frametime;
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid || tr.flFraction == 1.0 || tr.vecPlaneNormal.z > 0.7)
		return;

	flOrigDist = (tr.vecEndPos - pev->origin).Length2D();
	vecSrc.z += flInterval;
	vecDest = vecSrc + (pev->velocity.Normalize() * 0.1);
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid)
		return;

	vecSrc = tr.vecEndPos;
	vecDest = tr.vecEndPos;
	vecDest.z -= flInterval;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.vecPlaneNormal.z < 0.7)
		return;

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
NOBODY void Hostage_RegisterCVars(void)
{
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
	memset(&m_chatter, 0, sizeof(m_chatter));
	m_hostageCount = 0;

//	SimpleChatter(SimpleChatter *const this);  //  1443
}

/* <45e39b> ../cstrike/dlls/hostage/hostage.cpp:1456 */
NOBODY void CHostageManager::ServerActivate(void)
{

}

/* <45e3f7> ../cstrike/dlls/hostage/hostage.cpp:1631 */
NOBODY void CHostageManager::RestartRound(void)
{
//	{
//		int i;                                                //  1634
//	}
}

/* <45e43d> ../cstrike/dlls/hostage/hostage.cpp:1640 */
NOBODY void CHostageManager::AddHostage(CHostage *hostage)
{
//	{
//		int i;                                                //  1646
//	}
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

		if (improv)
			improv->OnGameEvent(event, entity, other);
	}
}

/* <45e6b8> ../cstrike/dlls/hostage/hostage.cpp:1726 */
NOBODY SimpleChatter::SimpleChatter(void)
{
//	{
//		int i;                                                //  1728
//	}
}

/* <45e6f0> ../cstrike/dlls/hostage/hostage.cpp:1737 */
NOBODY SimpleChatter::~SimpleChatter(void)
{
//	{
//		int i;                                                //  1739
//		{
//			int f;                                        //  1741
//		}
//	}
}

/* <45e736> ../cstrike/dlls/hostage/hostage.cpp:1752 */
NOBODY void SimpleChatter::AddSound(HostageChatterType type, char *filename)
{
//	{
//		class ChatterSet *chatter;                           //  1754
//		char actualFilename;                                  //  1758
//		CloneString(const char *str);  //  1756
//	}
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
