#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

cvar_t cv_hostage_debug = { "hostage_debug", "0", FCVAR_SERVER, 0.0f, NULL };
cvar_t cv_hostage_stop = { "hostage_stop", "0", FCVAR_SERVER, 0.0f, NULL };

CHostageManager *g_pHostages = NULL;
int g_iHostageNumber = 0;

#endif

LINK_ENTITY_TO_CLASS(hostage_entity, CHostage);
LINK_ENTITY_TO_CLASS(monster_scientist, CHostage);

void CHostage::__MAKE_VHOOK(Spawn)()
{
	if (!g_pHostages)
	{
		g_pHostages = new CHostageManager;
	}

	Precache();

	MAKE_STRING_CLASS("hostage_entity", pev);

	pev->movetype = MOVETYPE_STEP;
	pev->solid = SOLID_SLIDEBOX;
	pev->takedamage = DAMAGE_YES;
	pev->flags |= FL_MONSTER;
	pev->deadflag = DEAD_NO;
	pev->max_health = 100;
	pev->health = pev->max_health;
	pev->gravity = 1;
	pev->view_ofs = VEC_HOSTAGE_VIEW;
	pev->velocity = Vector(0, 0, 0);

	if (pev->spawnflags & SF_MONSTER_HITMONSTERCLIP)
		pev->flags |= FL_MONSTERCLIP;

	if (pev->skin < 0)
		pev->skin = 0;

	SET_MODEL(edict(), STRING(pev->model));
	SetActivity(ACT_IDLE);

	m_flNextChange = 0;
	m_State = STAND;
	m_hTargetEnt = NULL;
	m_hStoppedTargetEnt = NULL;
	m_vPathToFollow[0] = Vector(0, 0, 0);
	m_flFlinchTime = 0;
	m_bRescueMe = FALSE;

	UTIL_SetSize(pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_HULL_MAX);
	UTIL_MakeVectors(pev->v_angle);

	SetBoneController(0, UTIL_VecToYaw(gpGlobals->v_forward));
	SetBoneController(1, 0);
	SetBoneController(2, 0);
	SetBoneController(3, 0);
	SetBoneController(4, 0);

	DROP_TO_FLOOR(edict());

#ifndef HOOK_GAMEDLL
	SetThink(&CHostage::IdleThink);
#else
	// TODO: fix test demo
	SetThink(pCHostage__IdleThink);
#endif

	pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);

	m_flNextFullThink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);
	m_vStart = pev->origin;
	m_vStartAngles = pev->angles;
	m_vOldPos = Vector(9999, 9999, 9999);
	m_iHostageIndex = ++g_iHostageNumber;

	nTargetNode = -1;
	m_fHasPath = FALSE;

	m_flLastPathCheck = -1;
	m_flPathAcquired = -1;
	m_flPathCheckInterval = 0.1f;
	m_flNextRadarTime = gpGlobals->time + RANDOM_FLOAT(0, 1);

	m_LocalNav = new CLocalNav(this);
	m_bStuck = FALSE;
	m_flStuckTime = 0;
	m_improv = NULL;
}

void CHostage::__MAKE_VHOOK(Precache)()
{
	static int which = 0;

	if (g_bIsCzeroGame)
	{
		switch (which)
		{
		case REGULAR_GUY:
			pev->model = MAKE_STRING("models/hostageA.mdl");
			break;
		case OLD_GUY:
			pev->model = MAKE_STRING("models/hostageB.mdl");
			break;
		case BLACK_GUY:
			pev->model = MAKE_STRING("models/hostageC.mdl");
			break;
		case GOOFY_GUY:
			pev->model = MAKE_STRING("models/hostageD.mdl");
			break;
		default:
			break;
		}

		m_whichModel = static_cast<ModelType>(which);

		if (++which > 3)
			which = 0;
	}
	else
	{
		m_whichModel = REGULAR_GUY;
		if (FStringNull(pev->model))
		{
			pev->model = MAKE_STRING("models/scientist.mdl");
		}
	}

	PRECACHE_MODEL((char *)STRING(pev->model));
	PRECACHE_SOUND("hostage/hos1.wav");
	PRECACHE_SOUND("hostage/hos2.wav");
	PRECACHE_SOUND("hostage/hos3.wav");
	PRECACHE_SOUND("hostage/hos4.wav");
	PRECACHE_SOUND("hostage/hos5.wav");
	PRECACHE_MODEL("sprites/smoke.spr");
}

void CHostage::SetActivity(int act)
{
	if (m_Activity != act)
	{
		int sequence = LookupActivity(act);

		if (sequence != ACT_INVALID)
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

void CHostage::IdleThink()
{
	float flInterval;
	const float upkeepRate = 0.03f;
	const float giveUpTime = (1 / 30.0f);
	float const updateRate = 0.1f;

	if (AreImprovAllowed() && !TheNavAreaList.empty())
	{
		if (!m_improv)
		{
			m_improv = new CHostageImprov(this);
		}
	}
	else
	{
		if (m_improv != NULL)
		{
			delete m_improv;
			m_improv = NULL;
		}
	}

	pev->nextthink = gpGlobals->time + giveUpTime;

	flInterval = StudioFrameAdvance();
	DispatchAnimEvents(flInterval);

	if (m_improv != NULL)
	{
		m_improv->OnUpkeep(upkeepRate);
	}

	if (m_flNextFullThink > gpGlobals->time)
	{
		return;
	}

	m_flNextFullThink = gpGlobals->time + 0.1f;

	if (pev->deadflag == DEAD_DEAD)
	{
		UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
		return;
	}

	if (m_hTargetEnt != NULL && (m_bStuck && gpGlobals->time - m_flStuckTime > 5.0f || m_hTargetEnt->pev->deadflag != DEAD_NO))
	{
		m_State = STAND;
		m_hTargetEnt = NULL;
		m_bStuck = FALSE;
	}

	if (m_hTargetEnt != NULL || m_improv != NULL)
	{
		CBasePlayer *player = NULL;

		if (m_improv != NULL)
		{
			if (m_improv->IsFollowing())
				player = (CBasePlayer *)m_improv->GetFollowLeader();
		}
		else
			player = GetClassPtr((CBasePlayer *)m_hTargetEnt->pev);

		if (player == NULL || player->m_iTeam == CT)
		{
			if (!CSGameRules()->m_bMapHasRescueZone)
			{
				bool bResHostagePt = false;

				if (UTIL_FindEntityByClassname(NULL, "info_hostage_rescue"))
					bResHostagePt = true;

				CBaseEntity *pSpot = NULL;
				while ((pSpot = UTIL_FindEntityByClassname(pSpot, "info_hostage_rescue")) != NULL)
				{
					if ((pSpot->pev->origin - pev->origin).Length() < RESCUE_HOSTAGES_RADIUS)
					{
						m_bRescueMe = TRUE;
						break;
					}
				}

				if (!bResHostagePt)
				{
					pSpot = NULL;

					while ((pSpot = UTIL_FindEntityByClassname(pSpot, "info_player_start")) != NULL)
					{
						if ((pSpot->pev->origin - pev->origin).Length() < RESCUE_HOSTAGES_RADIUS)
						{
							m_bRescueMe = TRUE;
							break;
						}
					}
				}
			}

			if (m_bRescueMe)
			{
				if (TheBots != NULL)
				{
					TheBots->OnEvent(EVENT_HOSTAGE_RESCUED, player, this);
				}

				if (TheCareerTasks != NULL && CSGameRules()->IsCareer() && player != NULL && !player->IsBot())
				{
					TheCareerTasks->HandleEvent(EVENT_HOSTAGE_RESCUED, player);
				}

				pev->deadflag = DEAD_RESPAWNABLE;

				if (player != NULL)
				{
					player->AddAccount(REWARD_TAKEN_HOSTAGE);
					UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Rescued_A_Hostage\"\n", STRING(player->pev->netname),
						GETPLAYERUSERID(player->edict()), GETPLAYERAUTHID(player->edict()));
				}

				SendHostageEventMsg();

				MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
					WRITE_BYTE(9);
					WRITE_BYTE(DRC_CMD_EVENT);
					WRITE_SHORT(player != NULL ? player->entindex() : 0);
					WRITE_SHORT(entindex());
					WRITE_LONG(15);
				MESSAGE_END();

				pev->effects |= EF_NODRAW;
				Remove();

				CSGameRules()->m_iHostagesRescued++;
				CSGameRules()->CheckWinConditions();

				Broadcast((player != NULL) ? "rescued" : "escaped");
			}
		}
	}

	if (m_improv != NULL)
	{
		m_improv->OnUpdate(updateRate);
	}
	else
	{
		DoFollow();

		if (gpGlobals->time >= m_flFlinchTime)
		{
			if (pev->velocity.Length() > 160.0f)
			{
				SetActivity(ACT_RUN);
			}
			else if (pev->velocity.Length() > 15.0f)
			{
				SetActivity(ACT_WALK);
			}
			else
			{
				SetActivity(ACT_IDLE);
			}
		}
	}

	if (pev->deadflag != DEAD_DEAD && !(pev->effects & EF_NODRAW))
	{
		if (m_flNextRadarTime <= gpGlobals->time)
		{
			Vector vDistance = m_vOldPos - pev->origin;

			if (vDistance.Length() > 1.0f)
			{
				m_vOldPos = pev->origin;

				if (!CSGameRules()->m_fTeamCount)
				{
					SendHostagePositionMsg();
				}
			}

			m_flNextRadarTime = gpGlobals->time + 1.0f;
		}
	}
}

void CHostage::Remove()
{
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_NOT;
	pev->takedamage = DAMAGE_NO;

	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
	pev->nextthink = -1;
	m_flNextFullThink = -1;
}

void CHostage::RePosition()
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

#ifndef HOOK_GAMEDLL
	SetThink(&CHostage::IdleThink);
#else
	// TODO: fix test demo
	SetThink(pCHostage__IdleThink);
#endif
	pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);

	m_fHasPath = FALSE;
	nTargetNode = -1;

	m_flLastPathCheck = -1;
	m_flPathAcquired = -1;
	m_flPathCheckInterval = 0.1f;
	m_flNextFullThink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);
}

int CHostage::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	float flActualDamage;
	CBasePlayer *pAttacker = NULL;

	flActualDamage = GetModifiedDamage(flDamage, m_LastHitGroup);

	if (flActualDamage > pev->health)
		flActualDamage = pev->health;

	pev->health -= flActualDamage;

	if (m_improv != NULL)
	{
		m_improv->OnInjury(flActualDamage);
	}

	PlayPainSound();

	if (pevAttacker != NULL)
	{
		CBaseEntity *pAttackingEnt = GetClassPtr((CBaseEntity *)pevAttacker);

		if (pAttackingEnt->Classify() == CLASS_VEHICLE)
		{
			CBaseEntity *pDriver = ((CFuncVehicle *)pAttackingEnt)->m_pDriver;

			if (pDriver != NULL)
			{
				pevAttacker = pDriver->pev;
			}
		}

		if (pAttackingEnt->IsPlayer())
		{
			pAttacker = GetClassPtr((CBasePlayer *)pevAttacker);
		}
	}

	if (pev->health > 0.0f)
	{
		m_flFlinchTime = gpGlobals->time + 0.75f;
		SetFlinchActivity();

		if (pAttacker != NULL)
		{
			pAttacker->AddAccount(-20 * int(flActualDamage));

			if (TheBots != NULL)
			{
				TheBots->OnEvent(EVENT_HOSTAGE_DAMAGED, this, pAttacker);
			}

			ClientPrint(pAttacker->pev, HUD_PRINTCENTER, "#Injured_Hostage");
			if (!(pAttacker->m_flDisplayHistory & DHF_HOSTAGE_INJURED))
			{
				pAttacker->HintMessage("#Hint_careful_around_hostages");
				pAttacker->m_flDisplayHistory |= DHF_HOSTAGE_INJURED;
			}

			return 1;
		}
	}
	else
	{
		pev->health = 0;
		pev->movetype = MOVETYPE_TOSS;
		pev->flags &= ~FL_ONGROUND;
		SetDeathActivity();

		if (pAttacker != NULL)
		{
			pAttacker->AddAccount(20 * (-25 - int(flActualDamage)));
			AnnounceDeath(pAttacker);
			ApplyHostagePenalty(pAttacker);
		}

		pev->takedamage = DAMAGE_NO;
		pev->deadflag = DEAD_DEAD;
		pev->solid = SOLID_NOT;

		if (TheBots != NULL)
		{
			TheBots->OnEvent(EVENT_HOSTAGE_KILLED, this, pAttacker);
		}

		if (m_improv != NULL)
		{
			m_improv->Chatter(HOSTAGE_CHATTER_DEATH_CRY);
		}

		CSGameRules()->CheckWinConditions();

		if (!CSGameRules()->m_fTeamCount)
			SendHostageEventMsg();

		pev->nextthink = gpGlobals->time + 3.0f;
		SetThink(&CHostage::Remove);
	}

	return 0;
}

float CHostage::GetModifiedDamage(float flDamage, int nHitGroup)
{
	switch (nHitGroup)
	{
	case HITGROUP_GENERIC: flDamage *= 1.75; break;
	case HITGROUP_HEAD: flDamage *= 2.5; break;
	case HITGROUP_CHEST: flDamage *= 1.5; break;
	case HITGROUP_STOMACH: flDamage *= 1.75; break;
	case HITGROUP_LEFTARM:
	case HITGROUP_RIGHTARM: flDamage *= 0.75; break;
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG: flDamage *= 0.6; break;
	default: flDamage *= 1.5; break;
	}

	return flDamage;
}

void CHostage::PlayPainSound()
{
	if (m_LastHitGroup != HITGROUP_HEAD)
		return;

	switch (RANDOM_LONG(0, 1))
	{
	case 0: EMIT_SOUND(edict(), CHAN_VOICE, "player/headshot1.wav", VOL_NORM, ATTN_NORM); break;
	case 1: EMIT_SOUND(edict(), CHAN_VOICE, "player/headshot2.wav", VOL_NORM, ATTN_NORM); break;
	}
}

void CHostage::SetFlinchActivity()
{
	Activity activity = ACT_SMALL_FLINCH;

	if (m_improv != NULL)
	{
		m_improv->Flinch(activity);
		return;
	}

	SetActivity(activity);
}

void CHostage::SetDeathActivity()
{
	if (m_improv != NULL && m_improv->IsCrouching())
	{
		m_improv->CrouchDie();
		return;
	}

	if (g_bIsCzeroGame)
	{
		switch (m_LastHitGroup)
		{
		case HITGROUP_GENERIC:
		case HITGROUP_LEFTARM:
		case HITGROUP_RIGHTARM:
		case HITGROUP_LEFTLEG:
		case HITGROUP_RIGHTLEG:
			SetActivity(ACT_DIESIMPLE);
			break;
		case HITGROUP_HEAD:
			SetActivity(ACT_DIE_HEADSHOT);
			break;
		case HITGROUP_CHEST:
			SetActivity(ACT_DIE_CHESTSHOT);
			break;
		case HITGROUP_STOMACH:
			SetActivity(ACT_DIE_GUTSHOT);
			break;
		}

		return;
	}

	// for CS 1.6
	switch (m_LastHitGroup)
	{
	case HITGROUP_GENERIC:
	case HITGROUP_HEAD:
		SetActivity(ACT_DIE_HEADSHOT);
		break;
	case HITGROUP_CHEST:
	case HITGROUP_RIGHTARM:
		SetActivity(ACT_DIESIMPLE);
		break;
	case HITGROUP_STOMACH:
	case HITGROUP_RIGHTLEG:
		SetActivity(ACT_DIEFORWARD);
		break;
	case HITGROUP_LEFTARM:
	case HITGROUP_LEFTLEG:
		SetActivity(ACT_DIEBACKWARD);
		break;
	}
}

void CHostage::AnnounceDeath(CBasePlayer *pAttacker)
{
	ClientPrint(pAttacker->pev, HUD_PRINTCENTER, "#Killed_Hostage");

	if (!(pAttacker->m_flDisplayHistory & DHF_HOSTAGE_KILLED))
	{
		pAttacker->HintMessage("#Hint_lost_money");
		pAttacker->m_flDisplayHistory |= DHF_HOSTAGE_KILLED;
	}

	if (!g_pGameRules->IsMultiplayer())
	{
		CHalfLifeTraining::HostageDied();
	}

	UTIL_LogPrintf("\"%s<%i><%s><%s>\" triggered \"Killed_A_Hostage\"\n", STRING(pAttacker->pev->netname), GETPLAYERUSERID(pAttacker->edict()),
		GETPLAYERAUTHID(pAttacker->edict()), GetTeam(pAttacker->m_iTeam));

	MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
		WRITE_BYTE(9);
		WRITE_BYTE(DRC_CMD_EVENT);
		WRITE_SHORT(ENTINDEX(pAttacker->edict()));
		WRITE_SHORT(ENTINDEX(edict()));
		WRITE_LONG(15);
	MESSAGE_END();
}

void CHostage::ApplyHostagePenalty(CBasePlayer *pAttacker)
{
	if (pAttacker->m_iTeam != TERRORIST)
		return;

	int iHostagePenalty = int(CVAR_GET_FLOAT("mp_hostagepenalty"));

	if (iHostagePenalty)
	{
		if (pAttacker->m_iHostagesKilled++ == iHostagePenalty)
		{
			pAttacker->HintMessage("#Hint_removed_for_next_hostage_killed", TRUE);
		}
		else if (pAttacker->m_iHostagesKilled >= iHostagePenalty)
		{
		#ifdef REGAMEDLL_FIXES
			SERVER_COMMAND(UTIL_VarArgs("kick #%d\n", GETPLAYERUSERID(pAttacker->edict())));
		#else
			CLIENT_COMMAND(pAttacker->edict(), "disconnect\n");
		#endif
		}
	}
}

void CHostage::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!pActivator->IsPlayer())
		return;

	if (pev->takedamage == DAMAGE_NO)
		return;

	CBasePlayer *pPlayer = (CBasePlayer *)pActivator;

	if (pPlayer->m_iTeam != CT)
	{
		if (!(pPlayer->m_flDisplayHistory & DHF_HOSTAGE_CTMOVE))
		{
			pPlayer->m_flDisplayHistory |= DHF_HOSTAGE_CTMOVE;
			pPlayer->HintMessage("#Only_CT_Can_Move_Hostages", FALSE, TRUE);
		}

		return;
	}

	if (gpGlobals->time >= m_flNextChange)
	{
		m_flNextChange = gpGlobals->time + 1.0f;

		if (m_improv != NULL)
		{
			if (m_improv->IsFollowing() && pActivator == m_improv->GetFollowLeader())
			{
				m_improv->Agree();
				m_improv->Idle();
				m_improv->Chatter(HOSTAGE_CHATTER_STOP_FOLLOW);
			}
			else
			{
				m_improv->Follow(pPlayer);

				if (TheBots != NULL)
				{
					TheBots->OnEvent(EVENT_HOSTAGE_USED, pActivator);
				}
			}
		}
		else
		{
			m_flPathAcquired = gpGlobals->time;

			if (pActivator != m_hTargetEnt)
			{
				m_State = FOLLOW;
				m_hTargetEnt = pActivator;
				m_hStoppedTargetEnt = NULL;
			}
			else if (m_State == FOLLOW)
			{
				m_State = STAND;
				m_hTargetEnt = NULL;
				m_hStoppedTargetEnt = pActivator;
			}
			else
				m_State = FOLLOW;

			if (m_State == FOLLOW)
			{
				PlayFollowRescueSound();
				if (TheBots != NULL)
				{
					TheBots->OnEvent(EVENT_HOSTAGE_USED, pActivator);
				}
			}
		}

		GiveCTTouchBonus(pPlayer);
		pPlayer->HostageUsed();
	}
}

void CHostage::PlayFollowRescueSound()
{
	switch (RANDOM_LONG(0, 4))
	{
	case 0: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos1.wav", VOL_NORM, ATTN_NORM); break;
	case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos2.wav", VOL_NORM, ATTN_NORM); break;
	case 2: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos3.wav", VOL_NORM, ATTN_NORM); break;
	case 3: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos4.wav", VOL_NORM, ATTN_NORM); break;
	case 4: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos5.wav", VOL_NORM, ATTN_NORM); break;
	}
}

void CHostage::GiveCTTouchBonus(CBasePlayer *pPlayer)
{
	if (m_bTouched)
		return;

	m_bTouched = TRUE;
	CSGameRules()->m_iAccountCT += 100;

	pPlayer->AddAccount(150);
	UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Touched_A_Hostage\"\n", STRING(pPlayer->pev->netname), GETPLAYERUSERID(pPlayer->edict()), GETPLAYERAUTHID(pPlayer->edict()));
}

int CHostage::__MAKE_VHOOK(ObjectCaps)()
{
	return (CBaseMonster::ObjectCaps() | FCAP_MUST_SPAWN | FCAP_ONOFF_USE);
}

void CHostage::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
	Vector2D vPush;
	const float pushForce = 50.0f;

	if (m_improv != NULL)
	{
		m_improv->OnTouch(pOther);
		return;
	}

	CBasePlayer *pPlayer = (CBasePlayer *)pOther;

	if (pPlayer->IsPlayer())
	{
		if (pPlayer->m_iTeam != CT)
			return;
	}
	else
	{
		if (!FClassnameIs(pPlayer->pev, "hostage_entity"))
			return;
	}

	vPush = (pev->origin - pOther->pev->origin).Make2D();

#ifndef PLAY_GAMEDLL
	vPush = vPush.Normalize() * pushForce;

	pev->velocity.x += vPush.x;
	pev->velocity.y += vPush.y;
#else
	// TODO: fix test demo
	pev->velocity = pev->velocity + NormalizeMulScalar<float_precision, float_precision, float>(vPush, pushForce);
#endif
}

void CHostage::DoFollow()
{
	CBaseEntity *pFollowing;
	Vector vecDest;
	float flRadius = 0;
	float flDistToDest;

	if (m_hTargetEnt == NULL)
		return;

	if (cv_hostage_stop.value > 0.0f)
	{
		m_State = STAND;
		m_hTargetEnt = NULL;
		m_hStoppedTargetEnt = NULL;
		return;
	}

	pFollowing = GetClassPtr((CBaseEntity *)m_hTargetEnt->pev);
	m_LocalNav->SetTargetEnt(pFollowing);

	vecDest = pFollowing->pev->origin;
	vecDest.z += pFollowing->pev->mins.z;
	flDistToDest = (vecDest - pev->origin).Length();

	if (flDistToDest < 80.0f && (m_fHasPath || m_LocalNav->PathTraversable(pev->origin, vecDest, TRUE)))
		return;

	if (pev->flags & FL_ONGROUND)
	{
		if (m_flPathCheckInterval + m_flLastPathCheck < gpGlobals->time)
		{
			if (!m_fHasPath || pFollowing->pev->velocity.Length2D() > 1.0f)
			{
				m_flLastPathCheck = gpGlobals->time;
				m_LocalNav->RequestNav(this);
			}
		}
	}

	if (m_fHasPath)
	{
		nTargetNode = m_LocalNav->GetFurthestTraversableNode(pev->origin, vecNodes, m_nPathNodes, TRUE);

		if (!nTargetNode)
		{
			if ((vecNodes[nTargetNode] - pev->origin).Length2D() < HOSTAGE_STEPSIZE)
				nTargetNode = -1;
		}
		if (nTargetNode == -1)
		{
			m_fHasPath = FALSE;
			m_flPathCheckInterval = 0.1f;
		}
	}

	if (gpGlobals->time < m_flFlinchTime)
		return;

	if (nTargetNode != -1)
	{
		if (pev->flags & FL_ONGROUND)
			PointAt(vecNodes[nTargetNode]);

		if (pev->movetype == MOVETYPE_FLY)
			pev->v_angle.x = -60;

		MoveToward(vecNodes[nTargetNode]);
		m_bStuck = FALSE;
	}
	else if (pev->takedamage == DAMAGE_YES)
	{
		if (IsFollowingSomeone())
		{
			if (!m_bStuck && flDistToDest > 200.0f)
			{
				m_bStuck = TRUE;
				m_flStuckTime = gpGlobals->time;
			}
		}
	}

	if (pev->flags & FL_ONGROUND)
	{
		if (m_flPathAcquired != -1 && m_flPathAcquired + 2 > gpGlobals->time)
		{
			if (pev->velocity.Length2D() < 1 || nTargetNode == -1)
			{
				Wiggle();
			}
		}
	}
}

void CHostage::PointAt(const Vector &vecLoc)
{
	pev->angles.x = 0;
	pev->angles.y = UTIL_VecToAngles(vecLoc - pev->origin).y;
	pev->angles.z = 0;
}

void CHostage::MoveToward(const Vector &vecLoc)
{
	int nFwdMove;
	Vector vecFwd;
	Vector vecbigDest;
	Vector vecMove;
	CBaseEntity *pFollowing;
	Vector vecAng;
	float_precision flDist;

	pFollowing = GetClassPtr((CBaseEntity *)m_hTargetEnt->pev);
	vecMove = vecLoc - pev->origin;
	vecAng = UTIL_VecToAngles(vecMove);
	vecAng = Vector(0, vecAng.y, 0);
	UTIL_MakeVectorsPrivate(vecAng, vecFwd, NULL, NULL);

	if ((vecFwd * s_flStepSize_LocalNav).Length2D() <= (vecLoc - pev->origin).Length2D())
		flDist = (vecFwd * s_flStepSize_LocalNav).Length2D();
	else
		flDist = (vecLoc - pev->origin).Length2D();

	vecbigDest = pev->origin + (vecFwd * flDist);
	nFwdMove = m_LocalNav->PathTraversable(pev->origin, vecbigDest, FALSE);

	if (nFwdMove != PATH_TRAVERSABLE_EMPTY)
	{
		float_precision flSpeed = 250;

		vecbigDest = pFollowing->pev->origin;
		vecbigDest.z += pFollowing->pev->mins.z;

		if (pev->flags & FL_ONGROUND)
		{
			flSpeed = (vecbigDest - pev->origin).Length();

			if (flSpeed >= 110)
			{
				if (flSpeed >= 250)
					flSpeed = 400;
				else
					flSpeed = 300;
			}
		}

		pev->velocity.x = vecFwd.x * flSpeed;
		pev->velocity.y = vecFwd.y * flSpeed;

		if (nFwdMove == PATH_TRAVERSABLE_STEPJUMPABLE)
		{
			if (pev->flags & FL_ONGROUND)
			{
				pev->velocity.z = 270;
			}
		}
	}
}

BOOL CHostage::IsOnLadder()
{
	return pev->movetype == MOVETYPE_FLY;
}

void CHostage::NavReady()
{
	CBaseEntity *pFollowing;
	Vector vecDest;
	float flRadius = 40.0f;

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
			m_flPathCheckInterval += 0.1f;

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
		m_flPathCheckInterval = 0.5f;

		m_nPathNodes = m_LocalNav->SetupPathNodes(nindexPath, vecNodes, 1);
	}
}

void CHostage::SendHostagePositionMsg()
{
	CBaseEntity *pEntity = NULL;

	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (!pEntity->IsPlayer())
			continue;

		if (pEntity->pev->flags == FL_DORMANT)
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr((CBasePlayer *)pEntity->pev);

		if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == CT)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgHostagePos, NULL, pTempPlayer->pev);
				WRITE_BYTE(0);
				WRITE_BYTE(m_iHostageIndex);
				WRITE_COORD(pev->origin.x);
				WRITE_COORD(pev->origin.y);
				WRITE_COORD(pev->origin.z);
			MESSAGE_END();
		}
	}
}

void CHostage::SendHostageEventMsg()
{
	CBaseEntity *pEntity = NULL;

	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (!pEntity->IsPlayer())
			continue;

		if (pEntity->pev->flags == FL_DORMANT)
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr((CBasePlayer *)pEntity->pev);

		if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == CT)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgHostageK, NULL, pTempPlayer->pev);
				WRITE_BYTE(m_iHostageIndex);
			MESSAGE_END();
		}

		if (pTempPlayer->pev->deadflag == DEAD_NO)
			pTempPlayer->SendHostageIcons();
	}
}

void CHostage::Wiggle()
{
	TraceResult tr;
	Vector vec = Vector(0, 0, 0);
	Vector wiggle_directions[] =
	{
		Vector(50, 0, 0),
		Vector(-50, 0, 0),
		Vector(0, 50, 0),
		Vector(0, -50, 0),
		Vector(50, 50, 0),
		Vector(50, -50, 0),
		Vector(-50, 50, 0),
		Vector(-50, -50, 0)
	};

	for (int i = 0; i < ARRAYSIZE(wiggle_directions); ++i)
	{
		Vector dest = pev->origin + wiggle_directions[i];

		if (m_LocalNav->PathTraversable(pev->origin, dest, TRUE) == PATH_TRAVERSABLE_EMPTY)
		{
			vec = vec - wiggle_directions[i];
		}
	}

#ifndef PLAY_GAMEDLL
	vec = vec + Vector(RANDOM_FLOAT(-3, 3), RANDOM_FLOAT(-3, 3), 0);
#else
	// TODO: fix test demo
	vec.y = vec.y + RANDOM_FLOAT(-3.0, 3.0);
	vec.x = vec.x + RANDOM_FLOAT(-3.0, 3.0);

#endif

	pev->velocity = pev->velocity + (vec.Normalize() * 100);
}

void CHostage::PreThink()
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

	flInterval = s_flStepSize_LocalNav;
	vecDest = vecSrc + pev->velocity * gpGlobals->frametime;
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid || tr.flFraction == 1.0f || tr.vecPlaneNormal.z > MaxUnitZSlope)
	{
		return;
	}

	flOrigDist = (tr.vecEndPos - pev->origin).Length2D();
	vecSrc.z += flInterval;
	vecDest = vecSrc + (pev->velocity.Normalize() * 0.1f);
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

	if (tr.vecPlaneNormal.z < MaxUnitZSlope)
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

void Hostage_RegisterCVars()
{
// These cvars are only used in czero
#ifdef REGAMEDLL_FIXES
	if (!g_bIsCzeroGame)
		return;
#endif

	CVAR_REGISTER(&cv_hostage_debug);
	CVAR_REGISTER(&cv_hostage_stop);
}

void InstallHostageManager()
{
	if (g_pHostages != NULL)
	{
		delete g_pHostages;
		g_pHostages = NULL;
	}

	g_pHostages = new CHostageManager;
}

CHostageManager::CHostageManager()
{
	Q_memset(&m_chatter, 0, sizeof(m_chatter));
	m_hostageCount = 0;
}

void CHostageManager::ServerActivate()
{
	m_hostageCount = 0;

	CBaseEntity *pEntity = NULL;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "hostage_entity")) != NULL)
	{
		AddHostage((CHostage *)pEntity);
	}

	if (g_bIsCzeroGame)
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

void CHostageManager::ServerDeactivate()
{
	;
}

void CHostageManager::RestartRound()
{
	for (int i = 0; i < m_hostageCount; ++i)
	{
		if (m_hostage[i]->m_improv != NULL)
		{
			m_hostage[i]->m_improv->OnReset();
		}
	}
}

void CHostageManager::AddHostage(CHostage *hostage)
{
	if (m_hostageCount >= MAX_HOSTAGES)
		return;

	int i;
	for (i = 0; i < m_hostageCount; ++i)
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

bool CHostageManager::IsNearbyHostageTalking(CHostageImprov *improv)
{
	for (int i = 0; i < m_hostageCount; ++i)
	{
		const float closeRange = 500.0f;
		const CHostageImprov *other = m_hostage[i]->m_improv;

		if (other == NULL)
			continue;

		if (!other->IsAlive() || other == improv)
			continue;

		if (!(improv->GetCentroid() - other->GetCentroid()).IsLengthGreaterThan(closeRange) && !other->IsTalking())
		{
			return true;
		}
	}

	return false;
}

bool CHostageManager::IsNearbyHostageJumping(CHostageImprov *improv)
{
	for (int i = 0; i < m_hostageCount; ++i)
	{
		const CHostageImprov *other = m_hostage[i]->m_improv;

		if (other == NULL)
			continue;

		if (!other->IsAlive() || other == improv)
			continue;

		const float closeRange = 500.0f;
		if (!(improv->GetCentroid() - other->GetCentroid()).IsLengthGreaterThan(closeRange) && other->IsJumping())
		{
			return true;
		}
	}

	return false;
}

void CHostageManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	for (int i = 0; i < m_hostageCount; ++i)
	{
		CHostageImprov *improv = m_hostage[ i ]->m_improv;

		if (improv != NULL)
		{
			improv->OnGameEvent(event, entity, other);
		}
	}
}

SimpleChatter::SimpleChatter()
{
	for (int i = 0; i < ARRAYSIZE(m_chatter); ++i)
	{
		m_chatter[i].count = 0;
		m_chatter[i].index = 0;
		m_chatter[i].needsShuffle = false;
	}
}

SimpleChatter::~SimpleChatter()
{
	for (int i = 0; i < ARRAYSIZE(m_chatter); ++i)
	{
		for (int f = 0; f < m_chatter[i].count; f++)
		{
			delete[] m_chatter[i].file[f].filename;
			m_chatter[i].file[f].filename = NULL;
		}
	}
}

void SimpleChatter::AddSound(HostageChatterType type, char *filename)
{
	ChatterSet *chatter;
	char actualFilename[128];

	chatter = &m_chatter[type];

	Q_snprintf(actualFilename, sizeof(actualFilename), "sound\\%s", filename);

	chatter->file[chatter->count].filename = CloneString(filename);
	chatter->file[chatter->count].duration = (double)GET_APPROX_WAVE_PLAY_LEN(actualFilename) / 1000.0;

	chatter->needsShuffle = true;
	chatter->count++;

	PRECACHE_SOUND(filename);
}

void SimpleChatter::Shuffle(ChatterSet *chatter)
{
	if (!chatter->needsShuffle)
		return;

	for (int i = 1; i < chatter->count; ++i)
	{
		for (int j = i; j < chatter->count; j++)
		{
			if (RANDOM_LONG(0, 100) < 50)
			{
				SoundFile tmp;
				tmp.filename = chatter->file[i - 1].filename;
				tmp.duration = chatter->file[i - 1].duration;

				chatter->file[i - 1] = chatter->file[j];
				chatter->file[j].filename = tmp.filename;
				chatter->file[j].duration = tmp.duration;
			}
		}
	}

	chatter->needsShuffle = false;
}

char *SimpleChatter::GetSound(HostageChatterType type, float *duration)
{
	ChatterSet *chatter = &m_chatter[type];
	char *sound;

	Shuffle(chatter);
	sound = chatter->file[chatter->index].filename;
	*duration = chatter->file[chatter->index].duration;

	if (++chatter->index >= chatter->count)
	{
		chatter->index = 0;
	}

	return sound;
}

float SimpleChatter::PlaySound(CBaseEntity *entity, HostageChatterType type)
{
	CHostage *hostage;
	float duration;
	char *sound;
	int pitch;
	int attenuation = 1;

	sound = GetSound(type, &duration);
	hostage = static_cast<CHostage *>(entity);

	if (sound == NULL)
	{
		return 0;
	}

	switch (hostage->m_whichModel)
	{
	case CHostage::REGULAR_GUY:
		pitch = 92;
		break;
	case CHostage::BLACK_GUY:
		pitch = 86;
		break;
	case CHostage::GOOFY_GUY:
		pitch = 100;
		break;
	case CHostage::OLD_GUY:
	default:
		pitch = 88;
		break;
	}

	EMIT_SOUND_DYN(ENT(hostage->pev), CHAN_VOICE, sound, VOL_NORM, attenuation, 0, pitch);

	if (type == HOSTAGE_CHATTER_CALL_TO_RESCUER)
	{
		if (TheBots != NULL)
		{
			TheBots->OnEvent(EVENT_HOSTAGE_CALLED_FOR_HELP, hostage);
		}
	}

	return duration;
}
