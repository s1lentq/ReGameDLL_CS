#include "precompiled.h"

void CBaseMonster::GibMonster()
{
	TraceResult tr;
	bool gibbed = false;

	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "common/bodysplat.wav", VOL_NORM, ATTN_NORM);

	// only humans throw skulls UNDONE - eventually monsters will have their own sets of gibs
	if (HasHumanGibs())
	{
		// Only the player will ever get here
		if (CVAR_GET_FLOAT("violence_hgibs") != 0)
		{
			CGib::SpawnHeadGib(pev);

			// throw some human gibs.
			CGib::SpawnRandomGibs(pev, 4, 1);
		}

		gibbed = true;
	}
	else if (HasAlienGibs())
	{
		// Should never get here, but someone might call it directly
		if (CVAR_GET_FLOAT("violence_agibs") != 0)
		{
			// Throw alien gibs
			CGib::SpawnRandomGibs(pev, 4, 0);
		}

		gibbed = true;
	}

	if (!IsPlayer())
	{
		if (gibbed)
		{
			// don't remove players!
			SetThink(&CBaseMonster::SUB_Remove);
			pev->nextthink = gpGlobals->time;
		}
		else
		{
			FadeMonster();
		}
	}
}

BOOL CBaseMonster::HasHumanGibs()
{
	int myClass = Classify();
	if (myClass == CLASS_HUMAN_MILITARY
		|| myClass == CLASS_PLAYER_ALLY
		|| myClass == CLASS_HUMAN_PASSIVE
		|| myClass == CLASS_PLAYER)
		 return TRUE;

	return FALSE;
}

BOOL CBaseMonster::HasAlienGibs()
{
	int myClass = Classify();
	if (myClass == CLASS_ALIEN_MILITARY
		|| myClass == CLASS_ALIEN_MONSTER
		|| myClass == CLASS_ALIEN_PASSIVE
		|| myClass == CLASS_INSECT
		|| myClass == CLASS_ALIEN_PREDATOR
		|| myClass == CLASS_ALIEN_PREY)
		 return TRUE;

	return FALSE;
}

void CBaseMonster::FadeMonster()
{
	StopAnimation();

	pev->velocity = g_vecZero;
	pev->movetype = MOVETYPE_NONE;
	pev->avelocity = g_vecZero;
	pev->animtime = gpGlobals->time;
	pev->effects |= EF_NOINTERP;

	SUB_StartFadeOut();
}

// Determines the best type of death anim to play.
Activity CBaseMonster::GetDeathActivity()
{
	Activity deathActivity;
	BOOL fTriedDirection;
	float flDot;
	TraceResult tr;
	Vector vecSrc;

	if (pev->deadflag != DEAD_NO)
	{
		// don't run this while dying.
		return m_IdealActivity;
	}

	vecSrc = Center();

	fTriedDirection = FALSE;

	// in case we can't find any special deaths to do.
	deathActivity = ACT_DIESIMPLE;

	UTIL_MakeVectors(pev->angles);
	flDot = DotProduct(gpGlobals->v_forward, g_vecAttackDir * -1);

	switch (m_LastHitGroup)
	{
	case HITGROUP_HEAD:
		// try to pick a region-specific death.
		deathActivity = ACT_DIE_HEADSHOT;
		break;
	case HITGROUP_STOMACH:
		deathActivity = ACT_DIE_GUTSHOT;
		break;
	case HITGROUP_GENERIC:
		// try to pick a death based on attack direction
		fTriedDirection = TRUE;

		if (flDot > 0.3)
		{
			deathActivity = ACT_DIEFORWARD;
		}
		else if (flDot <= -0.3)
		{
			deathActivity = ACT_DIEBACKWARD;
		}
		break;

	default:
		// try to pick a death based on attack direction
		fTriedDirection = TRUE;

		if (flDot > 0.3)
		{
			deathActivity = ACT_DIEFORWARD;
		}
		else if (flDot <= -0.3)
		{
			deathActivity = ACT_DIEBACKWARD;
		}
		break;
	}

	// can we perform the prescribed death?
	if (LookupActivity(deathActivity) == ACT_INVALID)
	{
		// no! did we fail to perform a directional death?
		if (fTriedDirection)
		{
			// if yes, we're out of options. Go simple.
			deathActivity = ACT_DIESIMPLE;
		}
		else
		{
			// cannot perform the ideal region-specific death, so try a direction.
			if (flDot > 0.3)
			{
				deathActivity = ACT_DIEFORWARD;
			}
			else if (flDot <= -0.3)
			{
				deathActivity = ACT_DIEBACKWARD;
			}
		}
	}

	if (LookupActivity(deathActivity) == ACT_INVALID)
	{
		// if we're still invalid, simple is our only option.
		deathActivity = ACT_DIESIMPLE;
	}

	if (deathActivity == ACT_DIEFORWARD)
	{
		// make sure there's room to fall forward
		UTIL_TraceHull(vecSrc, vecSrc + gpGlobals->v_forward * 64, dont_ignore_monsters, head_hull, edict(), &tr);

		if (tr.flFraction != 1.0f)
		{
			deathActivity = ACT_DIESIMPLE;
		}
	}

	if (deathActivity == ACT_DIEBACKWARD)
	{
		// make sure there's room to fall backward
		UTIL_TraceHull(vecSrc, vecSrc - gpGlobals->v_forward * 64, dont_ignore_monsters, head_hull, edict(), &tr);

		if (tr.flFraction != 1.0f)
		{
			deathActivity = ACT_DIESIMPLE;
		}
	}

	return deathActivity;
}

// Determines the best type of flinch anim to play.
NOXREF Activity CBaseMonster::GetSmallFlinchActivity()
{
	Activity flinchActivity;
	BOOL fTriedDirection;
	float flDot;

	fTriedDirection = FALSE;
	UTIL_MakeVectors(pev->angles);
	flDot = DotProduct(gpGlobals->v_forward, g_vecAttackDir * -1);	// TODO: noxref

	switch (m_LastHitGroup)
	{
	case HITGROUP_HEAD:
		// pick a region-specific flinch
		flinchActivity = ACT_FLINCH_HEAD;
		break;
	case HITGROUP_STOMACH:
		flinchActivity = ACT_FLINCH_STOMACH;
		break;
	case HITGROUP_LEFTARM:
		flinchActivity = ACT_FLINCH_LEFTARM;
		break;
	case HITGROUP_RIGHTARM:
		flinchActivity = ACT_FLINCH_RIGHTARM;
		break;
	case HITGROUP_LEFTLEG:
		flinchActivity = ACT_FLINCH_LEFTLEG;
		break;
	case HITGROUP_RIGHTLEG:
		flinchActivity = ACT_FLINCH_RIGHTLEG;
		break;
	case HITGROUP_GENERIC:
	default:
		// just get a generic flinch.
		flinchActivity = ACT_SMALL_FLINCH;
		break;
	}

	// do we have a sequence for the ideal activity?
	if (LookupActivity(flinchActivity) == ACT_INVALID)
	{
		flinchActivity = ACT_SMALL_FLINCH;
	}

	return flinchActivity;
}

void CBaseMonster::BecomeDead()
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

BOOL CBaseMonster::ShouldGibMonster(int iGib)
{
	if ((iGib == GIB_NORMAL && pev->health < GIB_HEALTH_VALUE) || (iGib == GIB_ALWAYS))
	{
		return TRUE;
	}

	return FALSE;
}

void CBaseMonster::CallGibMonster()
{
	BOOL fade = FALSE;

	if (HasHumanGibs())
	{
		if (CVAR_GET_FLOAT("violence_hgibs") == 0)
			fade = TRUE;
	}
	else if (HasAlienGibs())
	{
		if (CVAR_GET_FLOAT("violence_agibs") == 0)
			fade = TRUE;
	}

	// do something with the body. while monster blows up
	pev->solid = SOLID_NOT;
	pev->takedamage = DAMAGE_NO;

	if (fade)
	{
		FadeMonster();
	}
	else
	{
		// make the model invisible.
		pev->effects = EF_NODRAW;
		GibMonster();
	}

	pev->deadflag = DEAD_DEAD;
	FCheckAITrigger();

	// don't let the status bar glitch for players.with <0 health.
	if (pev->health < -99.0f)
	{
		pev->health = 0;
	}

	if (ShouldFadeOnDeath() && !fade)
		UTIL_Remove(this);
}

void CBaseMonster::Killed(entvars_t *pevAttacker, int iGib)
{
	if (HasMemory(bits_MEMORY_KILLED))
	{
		if (ShouldGibMonster(iGib))
		{
			CallGibMonster();
		}

		return;
	}

	Remember(bits_MEMORY_KILLED);

	// clear the deceased's sound channels.(may have been firing or reloading when killed)
	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "common/null.wav", VOL_NORM, ATTN_NORM);
	m_IdealMonsterState = MONSTERSTATE_DEAD;
	// Make sure this condition is fired too (TakeDamage breaks out before this happens on death)
	SetConditions(bits_COND_LIGHT_DAMAGE);

	// tell owner ( if any ) that we're dead.This is mostly for MonsterMaker functionality.
	CBaseEntity *pOwner = CBaseEntity::Instance(pev->owner);
	if (pOwner)
	{
		pOwner->DeathNotice(pev);
	}

	if (ShouldGibMonster(iGib))
	{
		CallGibMonster();
		return;
	}
	else if (pev->flags & FL_MONSTER)
	{
		SetTouch(nullptr);
		BecomeDead();
	}

	// don't let the status bar glitch for players.with <0 health.
	if (pev->health < -99)
	{
		pev->health = 0;
	}

	//pev->enemy = ENT(pevAttacker); // why? (sjb)
	m_IdealMonsterState = MONSTERSTATE_DEAD;
}

void CGib::WaitTillLand()
{
	if (!IsInWorld())
	{
		UTIL_Remove(this);
		return;
	}

	if (pev->velocity == g_vecZero)
	{
		SetThink(&CBaseEntity::SUB_StartFadeOut);
		pev->nextthink = gpGlobals->time + m_lifeTime;

#ifndef REGAMEDLL_FIXES
		if (m_bloodColor != DONT_BLEED)
		{
			CSoundEnt::InsertSound(bits_SOUND_MEAT, pev->origin, 384, 25);
		}
#endif
	}
	else
	{
		pev->nextthink = gpGlobals->time + 0.5f;
	}
}

BOOL CBaseMonster::TakeHealth(float flHealth, int bitsDamageType)
{
	if (pev->takedamage == DAMAGE_NO)
		return FALSE;

	// clear out any damage types we healed.
	// UNDONE: generic health should not heal any
	// UNDONE: time-based damage

	m_bitsDamageType &= ~(bitsDamageType & ~DMG_TIMEBASED);
	return CBaseEntity::TakeHealth(flHealth, bitsDamageType);
}

// The damage is coming from inflictor, but get mad at attacker
// This should be the only function that ever reduces health.
// bitsDamageType indicates the type of damage sustained, ie: DMG_SHOCK
//
// Time-based damage: only occurs while the monster is within the trigger_hurt.
// When a monster is poisoned via an arrow etc it takes all the poison damage at once.
BOOL CBaseMonster::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	if (pev->takedamage == DAMAGE_NO)
		return FALSE;

	if (!IsAlive())
	{
		return DeadTakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType);
	}

	if (pev->deadflag == DEAD_NO)
	{
		// no pain sound during death animation.
		PainSound();
	}

	// LATER: make armor consideration here!
	float flTake = flDamage;

	// set damage type sustained
	m_bitsDamageType |= bitsDamageType;

	// grab the vector of the incoming attack. ( pretend that the inflictor is a little lower than it really is, so the body will tend to fly upward a bit).
	Vector vecDir(0, 0, 0);

	if (!FNullEnt(pevInflictor))
	{
		CBaseEntity *pInflictor = CBaseEntity::Instance(pevInflictor);

		if (pInflictor)
		{
#ifndef PLAY_GAMEDLL
			vecDir = (pInflictor->Center() - Vector(0, 0, 10) - Center()).Normalize();
#else
			// TODO: fix test demo
			vecDir = NormalizeSubtract<real_t, float, real_t, real_t>(Center(), pInflictor->Center() - Vector(0, 0, 10));
#endif
			vecDir = g_vecAttackDir = vecDir.Normalize();
		}
	}

	// add to the damage total for clients, which will be sent as a single
	// message at the end of the frame
	// TODO: remove after combining shotgun blasts?
	if (IsPlayer())
	{
		if (pevInflictor)
		{
			pev->dmg_inflictor = ENT(pevInflictor);
		}

		pev->dmg_take += flTake;
	}

	pev->health -= flTake;

	if (m_MonsterState == MONSTERSTATE_SCRIPT)
	{
		SetConditions(bits_COND_LIGHT_DAMAGE);
		return FALSE;
	}

	if (pev->health <= 0.0f)
	{
		g_pevLastInflictor = pevInflictor;

		if (bitsDamageType & DMG_ALWAYSGIB)
			Killed(pevAttacker, GIB_ALWAYS);

		else if (bitsDamageType & DMG_NEVERGIB)
			Killed(pevAttacker, GIB_NEVER);
		else
			Killed(pevAttacker, GIB_NORMAL);

		g_pevLastInflictor = nullptr;
		return FALSE;
	}
	if ((pev->flags & FL_MONSTER) && !FNullEnt(pevAttacker))
	{
		if (pevAttacker->flags & (FL_MONSTER | FL_CLIENT))
		{
			if (pevInflictor)
			{
				if (!m_hEnemy || pevInflictor == m_hEnemy->pev || !HasConditions(bits_COND_SEE_ENEMY))
					m_vecEnemyLKP = pevInflictor->origin;
			}
			else
			{
				m_vecEnemyLKP = pev->origin + (g_vecAttackDir * 64);
			}

			MakeIdealYaw(m_vecEnemyLKP);

			if (flDamage > 20.0f)
			{
				SetConditions(bits_COND_LIGHT_DAMAGE);
			}

			if (flDamage >= 20.0f)
			{
				SetConditions(bits_COND_HEAVY_DAMAGE);
			}
		}
	}

	return TRUE;
}

// Takedamage function called when a monster's corpse is damaged.
BOOL CBaseMonster::DeadTakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	// grab the vector of the incoming attack. ( pretend that the inflictor is a little lower than it really is, so the body will tend to fly upward a bit).
	Vector vecDir(0, 0, 0);

	if (!FNullEnt(pevInflictor))
	{
		CBaseEntity *pInflictor = CBaseEntity::Instance(pevInflictor);
		if (pInflictor)
		{
			vecDir = (pInflictor->Center() - Vector(0, 0, 10) - Center()).Normalize();
			vecDir = g_vecAttackDir = vecDir.Normalize();
		}
	}

// turn this back on when the bounding box issues are resolved.
#if 0

	pev->flags &= ~FL_ONGROUND;
	pev->origin.z += 1;

	// let the damage scoot the corpse around a bit.
	if (!FNullEnt(pevInflictor) && (pevAttacker->solid != SOLID_TRIGGER))
	{
		pev->velocity = pev->velocity + vecDir * -DamageForce(flDamage);
	}

#endif

	// kill the corpse if enough damage was done to destroy the corpse and the damage is of a type that is allowed to destroy the corpse.
	if (bitsDamageType & DMG_GIB_CORPSE)
	{
		if (pev->health <= flDamage)
		{
			pev->health = -50;
			Killed(pevAttacker, GIB_ALWAYS);
			return FALSE;
		}

		// Accumulate corpse gibbing damage, so you can gib with multiple hits
		pev->health -= flDamage * 0.1;
	}

	return TRUE;
}

float CBaseMonster::DamageForce(float damage)
{
	real_t force = damage * ((32 * 32 * 72.0) / (pev->size.x * pev->size.y * pev->size.z)) * 5;
	if (force > 1000.0)
	{
		force = 1000.0;
	}

	return force;
}


void CBaseMonster::RadiusDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
	if (flDamage > 80)
		::RadiusDamage(pev->origin, pevInflictor, pevAttacker, flDamage, flDamage * 3.5, iClassIgnore, bitsDamageType);
	else
		::RadiusDamage2(pev->origin, pevInflictor, pevAttacker, flDamage, flDamage * (RANDOM_FLOAT(0.5, 1.5) + 3), iClassIgnore, bitsDamageType);
}

NOXREF void CBaseMonster::RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
	if (flDamage > 80)
		::RadiusDamage(vecSrc, pevInflictor, pevAttacker, flDamage, flDamage * 3.5, iClassIgnore, bitsDamageType);
	else
		::RadiusDamage2(vecSrc, pevInflictor, pevAttacker, flDamage, flDamage * (RANDOM_FLOAT(0.5, 1.5) + 3), iClassIgnore, bitsDamageType);
}

// Expects a length to trace, amount of damage to do, and damage type.
// Returns a pointer to the damaged entity in case the monster wishes to do
// other stuff to the victim (punchangle, etc)
//
// Used for many contact-range melee attacks. Bites, claws, etc.
NOXREF CBaseEntity *CBaseMonster::CheckTraceHullAttack(float flDist, int iDamage, int iDmgType)
{
	TraceResult tr;

	if (IsPlayer())
		UTIL_MakeVectors(pev->angles);
	else
		UTIL_MakeAimVectors(pev->angles);

	Vector vecStart = pev->origin;
	vecStart.z += pev->size.z * 0.5;
	Vector vecEnd = vecStart + (gpGlobals->v_forward * flDist);

	UTIL_TraceHull(vecStart, vecEnd, dont_ignore_monsters, head_hull, ENT(pev), &tr);

	if (tr.pHit)
	{
		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		if (iDamage > 0)
		{
			pEntity->TakeDamage(pev, pev, iDamage, iDmgType);
		}

		return pEntity;
	}

	return nullptr;
}

// Returns true is the passed ent is in the caller's forward view cone.
// The dot product is performed in 2d, making the view cone infinitely tall.
BOOL CBaseMonster::FInViewCone(CBaseEntity *pEntity)
{
	Vector2D vec2LOS;
	float flDot;

	UTIL_MakeVectors(pev->angles);

	vec2LOS = (pEntity->pev->origin - pev->origin).Make2D();
	vec2LOS = vec2LOS.Normalize();

	flDot = DotProduct(vec2LOS, gpGlobals->v_forward.Make2D());

	if (flDot > m_flFieldOfView)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// Returns true is the passed vector is in the caller's forward view cone.
// The dot product is performed in 2d, making the view cone infinitely tall.
BOOL CBaseMonster::FInViewCone(const Vector *pOrigin)
{
	Vector2D vec2LOS;
	float flDot;

	UTIL_MakeVectors(pev->angles);

	vec2LOS = (*pOrigin - pev->origin).Make2D();
	vec2LOS = vec2LOS.Normalize();

	flDot = DotProduct(vec2LOS, gpGlobals->v_forward.Make2D());

	if (flDot > m_flFieldOfView)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CBaseMonster::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	Vector vecOrigin = ptr->vecEndPos - vecDir * 4;

	if (pev->takedamage != DAMAGE_NO)
	{
		m_LastHitGroup = ptr->iHitgroup;

		switch (ptr->iHitgroup)
		{
		case HITGROUP_GENERIC:
			break;
		case HITGROUP_HEAD:
			flDamage *= 3;
			break;
		case HITGROUP_CHEST:
		case HITGROUP_STOMACH:
			flDamage *= 1.5;
			break;
		case HITGROUP_LEFTARM:
		case HITGROUP_RIGHTARM:
			flDamage *= 1.0;
			break;
		case HITGROUP_LEFTLEG:
		case HITGROUP_RIGHTLEG:
			flDamage *= 0.75;
			break;
		case HITGROUP_SHIELD:
			flDamage = 0;
			break;
		default:
			break;
		}

		AddMultiDamage(pevAttacker, this, flDamage, bitsDamageType);

		int blood = BloodColor();
		if (blood != DONT_BLEED)
		{
			// a little surface blood.
			SpawnBlood(vecOrigin, blood, flDamage);
		}
	}
}

float CBaseMonster::ChangeYaw(int speed)
{
	return 0.0f;
}

void CBaseMonster::MakeIdealYaw(Vector vecTarget)
{
	;
}

NOXREF void CBaseMonster::CorpseFallThink()
{
	if (pev->flags & FL_ONGROUND)
	{
		SetThink(nullptr);
		SetSequenceBox();

		// link into world.
		UTIL_SetOrigin(pev, pev->origin);
	}
	else
	{
		pev->nextthink = gpGlobals->time + 0.1f;
	}
}

void CBaseMonster::MonsterInitDead()
{
	InitBoneControllers();

	pev->solid = SOLID_BBOX;
	pev->movetype = MOVETYPE_TOSS;

	pev->frame = 0;
	ResetSequenceInfo();
	pev->framerate = 0;

	pev->max_health = pev->health;
	pev->deadflag = DEAD_DEAD;

	UTIL_SetSize(pev, g_vecZero, g_vecZero);
	UTIL_SetOrigin(pev, pev->origin);

	BecomeDead();
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.5f;
}

BOOL CBaseMonster::ShouldFadeOnDeath()
{
#if 0
	// if flagged to fade out or I have an owner (I came from a monster spawner)
	if ((pev->spawnflags & SF_MONSTER_FADECORPSE) || !FNullEnt(pev->owner))
		return TRUE;
#endif

	return FALSE;
}

BOOL CBaseMonster::FCheckAITrigger()
{
	return FALSE;
}

void CBaseMonster::KeyValue(KeyValueData *pkvd)
{
	CBaseToggle::KeyValue(pkvd);
}

int CBaseMonster::IRelationship(CBaseEntity *pTarget)
{
	static int const iEnemy[14][14] =
	{
		// NONE MACH  PLYR  HPASS HMIL  AMIL  APASS AMONST APREY APRED INSECT PLRALY PBWPN ABWPN
		{ R_NO, R_NO, R_NO, R_NO, R_NO, R_NO, R_NO, R_NO,  R_NO, R_NO, R_NO,  R_NO,  R_NO, R_NO }, // NONE
		{ R_NO, R_NO, R_DL, R_DL, R_NO, R_DL, R_DL, R_DL,  R_DL, R_DL, R_NO,  R_DL,  R_DL, R_DL }, // MACHINE
		{ R_NO, R_DL, R_NO, R_NO, R_DL, R_DL, R_DL, R_DL,  R_DL, R_DL, R_NO,  R_NO,  R_DL, R_DL }, // PLAYER
		{ R_NO, R_NO, R_AL, R_AL, R_HT, R_FR, R_NO, R_HT,  R_DL, R_FR, R_NO,  R_AL,  R_NO, R_NO }, // HUMANPASSIVE
		{ R_NO, R_NO, R_HT, R_DL, R_NO, R_HT, R_DL, R_DL,  R_DL, R_DL, R_NO,  R_HT,  R_NO, R_NO }, // HUMANMILITAR
		{ R_NO, R_DL, R_HT, R_DL, R_HT, R_NO, R_NO, R_NO,  R_NO, R_NO, R_NO,  R_DL,  R_NO, R_NO }, // ALIENMILITAR
		{ R_NO, R_NO, R_NO, R_NO, R_NO, R_NO, R_NO, R_NO,  R_NO, R_NO, R_NO,  R_NO,  R_NO, R_NO }, // ALIENPASSIVE
		{ R_NO, R_DL, R_DL, R_DL, R_DL, R_NO, R_NO, R_NO,  R_NO, R_NO, R_NO,  R_DL,  R_NO, R_NO }, // ALIENMONSTER
		{ R_NO, R_NO, R_DL, R_DL, R_DL, R_NO, R_NO, R_NO,  R_NO, R_FR, R_NO,  R_DL,  R_NO, R_NO }, // ALIENPREY
		{ R_NO, R_NO, R_DL, R_DL, R_DL, R_NO, R_NO, R_NO,  R_HT, R_DL, R_NO,  R_DL,  R_NO, R_NO }, // ALIENPREDATO
		{ R_FR, R_FR, R_FR, R_FR, R_FR, R_NO, R_FR, R_FR,  R_FR, R_FR, R_NO,  R_FR,  R_NO, R_NO }, // INSECT
		{ R_NO, R_DL, R_AL, R_AL, R_DL, R_DL, R_DL, R_DL,  R_DL, R_DL, R_NO,  R_NO,  R_NO, R_NO }, // PLAYERALLY
		{ R_NO, R_NO, R_DL, R_DL, R_DL, R_DL, R_DL, R_DL,  R_DL, R_DL, R_NO,  R_DL,  R_NO, R_DL }, // PBIOWEAPON
		{ R_NO, R_NO, R_DL, R_DL, R_DL, R_AL, R_NO, R_DL,  R_DL, R_NO, R_NO,  R_DL,  R_DL, R_NO }, // ABIOWEAPON
	};

	return iEnemy[Classify()][pTarget->Classify()];
}

// Base class monster function to find enemies or food by sight.
// iDistance is distance (in units) that the monster can see.
//
// Sets the sight bits of the m_afConditions mask to indicate
// which types of entities were sighted.
// Function also sets the Looker's m_pLink
// to the head of a link list that contains all visible ents.
// (linked via each ent's m_pLink field)
void CBaseMonster::Look(int iDistance)
{
	int iSighted = 0;

	// DON'T let visibility information from last frame sit around!
	ClearConditions(bits_COND_SEE_HATE | bits_COND_SEE_DISLIKE | bits_COND_SEE_ENEMY | bits_COND_SEE_FEAR | bits_COND_SEE_NEMESIS | bits_COND_SEE_CLIENT);

	m_pLink = nullptr;

	// the current visible entity that we're dealing with
	CBaseEntity *pSightEnt = nullptr;
	CBaseEntity *pList[100];

	Vector delta(iDistance, iDistance, iDistance);

	// Find only monsters/clients in box, NOT limited to PVS
	int count = UTIL_EntitiesInBox(pList, ARRAYSIZE(pList), pev->origin - delta, pev->origin + delta, (FL_CLIENT | FL_MONSTER));
	for (int i = 0; i < count; i++)
	{
		pSightEnt = pList[i];
		if (pSightEnt != this && pSightEnt->pev->health > 0)
		{
			// the looker will want to consider this entity
			// don't check anything else about an entity that can't be seen, or an entity that you don't care about.
			if (IRelationship(pSightEnt) != R_NO && FInViewCone(pSightEnt) && !(pSightEnt->pev->flags & FL_NOTARGET) && FVisible(pSightEnt))
			{
				if (pSightEnt->IsPlayer())
				{
					// if we see a client, remember that (mostly for scripted AI)
					iSighted |= bits_COND_SEE_CLIENT;
				}

				pSightEnt->m_pLink = m_pLink;
				m_pLink = pSightEnt;

				if (pSightEnt == m_hEnemy)
				{
					// we know this ent is visible, so if it also happens to be our enemy, store that now.
					iSighted |= bits_COND_SEE_ENEMY;
				}

				// don't add the Enemy's relationship to the conditions. We only want to worry about conditions when
				// we see monsters other than the Enemy.
				switch (IRelationship(pSightEnt))
				{
				case R_NM:
					iSighted |= bits_COND_SEE_NEMESIS;
					break;
				case R_HT:
					iSighted |= bits_COND_SEE_HATE;
					break;
				case R_DL:
					iSighted |= bits_COND_SEE_DISLIKE;
					break;
				case R_FR:
					iSighted |= bits_COND_SEE_FEAR;
					break;
				case R_AL:
					break;
				default:
					ALERT(at_aiconsole, "%s can't assess %s\n", STRING(pev->classname), STRING(pSightEnt->pev->classname));
					break;
				}
			}
		}
	}

	SetConditions(iSighted);
}

// This functions searches the link list whose head is the caller's m_pLink field,
// and returns a pointer to the enemy entity in that list that is nearest the caller.
//
// UNDONE: currently, this only returns the closest enemy.
// we'll want to consider distance, relationship, attack types, back turned, etc.
CBaseEntity *CBaseMonster::BestVisibleEnemy()
{
	CBaseEntity *pReturn;
	CBaseEntity *pNextEnt;
	int iNearest;
	int iDist;
	int iBestRelationship;

	// so first visible entity will become the closest.
	iNearest = 8192;
	pNextEnt = m_pLink;
	pReturn = nullptr;
	iBestRelationship = R_NO;

	while (pNextEnt)
	{
		if (pNextEnt->IsAlive())
		{
			if (IRelationship(pNextEnt) > iBestRelationship)
			{
				// this entity is disliked MORE than the entity that we
				// currently think is the best visible enemy. No need to do
				// a distance check, just get mad at this one for now.
				iBestRelationship = IRelationship(pNextEnt);
				iNearest = (pNextEnt->pev->origin - pev->origin).Length();
				pReturn = pNextEnt;
			}
			else if (IRelationship(pNextEnt) == iBestRelationship)
			{
				// this entity is disliked just as much as the entity that
				// we currently think is the best visible enemy, so we only
				// get mad at it if it is closer.
				iDist = (pNextEnt->pev->origin - pev->origin).Length();

				if (iDist <= iNearest)
				{
					iNearest = iDist;
					iBestRelationship = IRelationship(pNextEnt);
					pReturn = pNextEnt;
				}
			}
		}

		pNextEnt = pNextEnt->m_pLink;
	}

	return pReturn;
}

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
		{
			pev->max_health--;
		}
	}

	for (i = 0; i < cCount; i++)
	{
		vecTraceDir = vecDir;

		vecTraceDir.x += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.y += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.z += RANDOM_FLOAT(-flNoise, flNoise);

		UTIL_TraceLine(ptr->vecEndPos, ptr->vecEndPos + vecTraceDir * 172, ignore_monsters, ENT(pev), &Bloodtr);

		if (Bloodtr.flFraction != 1.0f)
		{
			UTIL_BloodDecalTrace(&Bloodtr, BloodColor());
		}
	}
}

void CBaseMonster::BloodSplat(const Vector &vecSrc, const Vector &vecDir, int HitLocation, int iVelocity)
{
	if (HitLocation != HITGROUP_HEAD)
		return;

#ifdef REGAMEDLL_FIXES
	UTIL_BloodStream(vecSrc, vecDir, BLOOD_COLOR_DARKRED, iVelocity + RANDOM_LONG(0, 100));
#else
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecSrc);
		WRITE_BYTE(TE_BLOODSTREAM);
		WRITE_COORD(vecSrc.x);
		WRITE_COORD(vecSrc.y);
		WRITE_COORD(vecSrc.z);
		WRITE_COORD(vecDir.x);
		WRITE_COORD(vecDir.y);
		WRITE_COORD(vecDir.z);
		WRITE_BYTE(BLOOD_COLOR_DARKRED);
		WRITE_BYTE(iVelocity + RANDOM_LONG(0, 100));
	MESSAGE_END();
#endif
}
