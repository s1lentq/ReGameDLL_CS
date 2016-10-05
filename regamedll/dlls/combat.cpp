#include "precompiled.h"

void CGib::LimitVelocity()
{
	float length = pev->velocity.Length();

	// ceiling at 1500.  The gib velocity equation is not bounded properly.  Rather than tune it
	// in 3 separate places again, I'll just limit it here.
	if (length > 1500.0)
	{
		// This should really be sv_maxvelocity * 0.75 or something
		pev->velocity = pev->velocity.Normalize() * 1500;
	}
}

NOXREF void CGib::SpawnStickyGibs(entvars_t *pevVictim, Vector vecOrigin, int cGibs)
{
	if (g_Language == LANGUAGE_GERMAN)
	{
		// no sticky gibs in germany right now!
		return;
	}

	for (int i = 0; i < cGibs; ++i)
	{
		CGib *pGib = GetClassPtr<CCSGib>((CGib *)NULL);

		pGib->Spawn("models/stickygib.mdl");
		pGib->pev->body = RANDOM_LONG(0, 2);

		if (pevVictim)
		{
			pGib->pev->origin.x = vecOrigin.x + RANDOM_FLOAT(-3, 3);
			pGib->pev->origin.y = vecOrigin.y + RANDOM_FLOAT(-3, 3);
			pGib->pev->origin.z = vecOrigin.z + RANDOM_FLOAT(-3, 3);

			// make the gib fly away from the attack vector
			pGib->pev->velocity = g_vecAttackDir * -1;

			// mix in some noise
			pGib->pev->velocity.x += RANDOM_FLOAT(-0.15, 0.15);
			pGib->pev->velocity.y += RANDOM_FLOAT(-0.15, 0.15);
			pGib->pev->velocity.z += RANDOM_FLOAT(-0.15, 0.15);

			pGib->pev->velocity = pGib->pev->velocity * 900;

			pGib->pev->avelocity.x = RANDOM_FLOAT(250, 400);
			pGib->pev->avelocity.y = RANDOM_FLOAT(250, 400);

			// copy owner's blood color
			pGib->m_bloodColor = (CBaseEntity::Instance(pevVictim))->BloodColor();

			if (pevVictim->health > -50)
			{
				pGib->pev->velocity = pGib->pev->velocity * 0.7;
			}
			else if (pevVictim->health > -200)
			{
				pGib->pev->velocity = pGib->pev->velocity * 2;
			}
			else
			{
				pGib->pev->velocity = pGib->pev->velocity * 4;
			}

			pGib->pev->movetype = MOVETYPE_TOSS;
			pGib->pev->solid = SOLID_BBOX;
			UTIL_SetSize(pGib->pev, Vector(0, 0,0), Vector(0, 0, 0));
			pGib->SetTouch(&CGib::StickyGibTouch);
			pGib->SetThink(NULL);
		}

		pGib->LimitVelocity();
	}
}

void CGib::SpawnHeadGib(entvars_t *pevVictim)
{
	CGib *pGib = GetClassPtr<CCSGib>((CGib *)NULL);

	if (g_Language == LANGUAGE_GERMAN)
	{
		// throw one head
		pGib->Spawn("models/germangibs.mdl");
		pGib->pev->body = 0;
	}
	else
	{
		// throw one head
		pGib->Spawn("models/hgibs.mdl");
		pGib->pev->body = 0;
	}

	if (pevVictim)
	{
		pGib->pev->origin = pevVictim->origin + pevVictim->view_ofs;

		edict_t *pentPlayer = FIND_CLIENT_IN_PVS(pGib->edict());

		if (RANDOM_LONG(0, 100) <= 5 && pentPlayer != NULL)
		{
			// 5% chance head will be thrown at player's face.
			entvars_t *pevPlayer = VARS(pentPlayer);

			pGib->pev->velocity = ((pevPlayer->origin + pevPlayer->view_ofs) - pGib->pev->origin).Normalize() * 300;
			pGib->pev->velocity.z += 100;
		}
		else
		{
			// TODO: fix test demo
			pGib->pev->velocity.z = RANDOM_FLOAT(200, 300);
			pGib->pev->velocity.y = RANDOM_FLOAT(-100, 100);
			pGib->pev->velocity.x = RANDOM_FLOAT(-100, 100);
		}

		pGib->pev->avelocity.x = RANDOM_FLOAT(100, 200);
		pGib->pev->avelocity.y = RANDOM_FLOAT(100, 300);

		// copy owner's blood color
		pGib->m_bloodColor = (CBaseEntity::Instance(pevVictim))->BloodColor();

		if (pevVictim->health > -50)
		{
			pGib->pev->velocity = pGib->pev->velocity * 0.7;
		}
		else if (pevVictim->health > -200)
		{
			pGib->pev->velocity = pGib->pev->velocity * 2;
		}
		else
			pGib->pev->velocity = pGib->pev->velocity * 4;
	}

	pGib->LimitVelocity();
}

void CGib::SpawnRandomGibs(entvars_t *pevVictim, int cGibs, int human)
{
	int cSplat;
	for (cSplat = 0; cSplat < cGibs; ++cSplat)
	{
		CGib *pGib = GetClassPtr<CCSGib>((CGib *)NULL);

		if (g_Language == LANGUAGE_GERMAN)
		{
			pGib->Spawn("models/germangibs.mdl");
			pGib->pev->body = RANDOM_LONG(0, GERMAN_GIB_COUNT - 1);
		}
		else
		{
			if (human)
			{
				// human pieces
				pGib->Spawn("models/hgibs.mdl");
				// start at one to avoid throwing random amounts of skulls (0th gib)
				pGib->pev->body = RANDOM_LONG(1, HUMAN_GIB_COUNT - 1);
			}
			else
			{
				// aliens
				pGib->Spawn("models/agibs.mdl");
				pGib->pev->body = RANDOM_LONG(0, ALIEN_GIB_COUNT - 1);
			}
		}

		if (pevVictim)
		{
			// spawn the gib somewhere in the monster's bounding volume
			pGib->pev->origin.x = pevVictim->absmin.x + pevVictim->size.x * (RANDOM_FLOAT(0, 1));
			pGib->pev->origin.y = pevVictim->absmin.y + pevVictim->size.y * (RANDOM_FLOAT(0, 1));
			// absmin.z is in the floor because the engine subtracts 1 to enlarge the box
			pGib->pev->origin.z = pevVictim->absmin.z + pevVictim->size.z * (RANDOM_FLOAT(0, 1)) + 1;

			// make the gib fly away from the attack vector
			pGib->pev->velocity = g_vecAttackDir * -1;

			// mix in some noise
			pGib->pev->velocity.x += RANDOM_FLOAT(-0.25, 0.25);
			pGib->pev->velocity.y += RANDOM_FLOAT(-0.25, 0.25);
			pGib->pev->velocity.z += RANDOM_FLOAT(-0.25, 0.25);

			pGib->pev->velocity = pGib->pev->velocity * RANDOM_FLOAT(300, 400);

			pGib->pev->avelocity.x = RANDOM_FLOAT(100, 200);
			pGib->pev->avelocity.y = RANDOM_FLOAT(100, 300);

			// copy owner's blood color
			pGib->m_bloodColor = (CBaseEntity::Instance(pevVictim))->BloodColor();

			if (pevVictim->health > -50)
				pGib->pev->velocity = pGib->pev->velocity * 0.7;

			else if (pevVictim->health > -200)
				pGib->pev->velocity = pGib->pev->velocity * 2;
			else
				pGib->pev->velocity = pGib->pev->velocity * 4;

			pGib->pev->solid = SOLID_BBOX;
			UTIL_SetSize(pGib->pev, Vector(0, 0, 0), Vector(0, 0, 0));
		}
		pGib->LimitVelocity();
	}
}

BOOL CBaseMonster::__MAKE_VHOOK(HasHumanGibs)()
{
	int myClass = Classify();

	if (myClass == CLASS_HUMAN_MILITARY
		|| myClass == CLASS_PLAYER_ALLY
		|| myClass == CLASS_HUMAN_PASSIVE
		|| myClass == CLASS_PLAYER)
		 return TRUE;

	return FALSE;
}

BOOL CBaseMonster::__MAKE_VHOOK(HasAlienGibs)()
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

void CBaseMonster::__MAKE_VHOOK(FadeMonster)()
{
	StopAnimation();

	pev->velocity = g_vecZero;
	pev->movetype = MOVETYPE_NONE;
	pev->avelocity = g_vecZero;
	pev->animtime = gpGlobals->time;
	pev->effects |= EF_NOINTERP;

	SUB_StartFadeOut();
}

void CBaseMonster::__MAKE_VHOOK(GibMonster)()
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
			FadeMonster();
	}
}

// GetDeathActivity - determines the best type of death
// anim to play.
Activity CBaseMonster::__MAKE_VHOOK(GetDeathActivity)()
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

// GetSmallFlinchActivity - determines the best type of flinch
// anim to play.
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

void CBaseMonster::__MAKE_VHOOK(BecomeDead)()
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

void CBaseMonster::__MAKE_VHOOK(Killed)(entvars_t *pevAttacker, int iGib)
{
	// unsigned int cCount = 0;
	// BOOL fDone = FALSE;

	if (HasMemory(bits_MEMORY_KILLED))
	{
		if (ShouldGibMonster(iGib))
			CallGibMonster();
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
		SetTouch(NULL);
		BecomeDead();
	}

	// don't let the status bar glitch for players.with <0 health.
	if (pev->health < -99)
	{
		pev->health = 0;
	}

	//pev->enemy = ENT(pevAttacker);//why? (sjb)
	m_IdealMonsterState = MONSTERSTATE_DEAD;
}

void CBaseEntity::SUB_StartFadeOut()
{
	if (pev->rendermode == kRenderNormal)
	{
		pev->renderamt = 255.0f;
		pev->rendermode = kRenderTransTexture;
	}

	pev->solid = SOLID_NOT;
	pev->avelocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.1f;

	SetThink(&CBaseEntity::SUB_FadeOut);
}

void CBaseEntity::SUB_FadeOut()
{
	if (pev->renderamt > 7)
	{
		pev->renderamt -= 7.0f;
		pev->nextthink = gpGlobals->time + 0.1f;
	}
	else
	{
		pev->renderamt = 0.0f;
		pev->nextthink = gpGlobals->time + 0.2f;
		SetThink(&CBaseEntity::SUB_Remove);
	}
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
			CSoundEnt::InsertSound(bits_SOUND_MEAT, pev->origin, 384, 25);
#endif
	}
	else
		pev->nextthink = gpGlobals->time + 0.5f;
}

void CGib::BounceGibTouch(CBaseEntity *pOther)
{
	if (pev->flags & FL_ONGROUND)
	{
		pev->velocity = pev->velocity * 0.9;
		pev->angles.x = 0;
		pev->angles.z = 0;
		pev->avelocity.x = 0;
		pev->avelocity.z = 0;
	}
	else
	{
		if (g_Language != LANGUAGE_GERMAN && m_cBloodDecals > 0 && m_bloodColor != DONT_BLEED)
		{
			TraceResult tr;
			Vector vecSpot = pev->origin + Vector(0, 0, 8);
			UTIL_TraceLine(vecSpot, vecSpot + Vector(0, 0, -24), ignore_monsters, ENT(pev), &tr);
			UTIL_BloodDecalTrace(&tr, m_bloodColor);
			m_cBloodDecals--;
		}

		if (m_material != matNone && !RANDOM_LONG(0, 2))
		{
			float zvel = Q_fabs(pev->velocity.z);
			float volume = 0.8 * Q_min(1.0f, zvel / 450);

			CBreakable::MaterialSoundRandom(edict(), (Materials)m_material, volume);
		}
	}
}

// Sticky gib puts blood on the wall and stays put.
void CGib::StickyGibTouch(CBaseEntity *pOther)
{
	Vector vecSpot;
	TraceResult tr;

	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 10;

	if (!FClassnameIs(pOther->pev, "worldspawn"))
	{
		pev->nextthink = gpGlobals->time;
		return;
	}

	vecSpot = pev->origin + pev->velocity * 32;

	UTIL_TraceLine(pev->origin, vecSpot, ignore_monsters, ENT(pev), &tr);
	UTIL_BloodDecalTrace(&tr, m_bloodColor);

	pev->velocity = tr.vecPlaneNormal * -1;
	pev->angles = UTIL_VecToAngles(pev->velocity);
	pev->velocity = g_vecZero;
	pev->avelocity = g_vecZero;
	pev->movetype = MOVETYPE_NONE;
}

void CGib::Spawn(const char *szGibModel)
{
	pev->movetype = MOVETYPE_BOUNCE;

	// deading the bounce a bit
	pev->friction = 0.55;

	// sometimes an entity inherits the edict from a former piece of glass,
	// and will spawn using the same render FX or rendermode! bad!
	pev->renderamt = 255.0;
	pev->rendermode = kRenderNormal;
	pev->renderfx = kRenderFxNone;

	/// hopefully this will fix the VELOCITY TOO LOW crap
	pev->solid = SOLID_SLIDEBOX;

	MAKE_STRING_CLASS("gib", pev);

	SET_MODEL(ENT(pev), szGibModel);
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pev->nextthink = gpGlobals->time + 4.0f;
	m_lifeTime = 25.0f;

	SetThink(&CGib::WaitTillLand);
	SetTouch(&CGib::BounceGibTouch);

	m_material = matNone;

	// how many blood decals this gib can place (1 per bounce until none remain).
	m_cBloodDecals = 5;
}

BOOL CBaseMonster::__MAKE_VHOOK(TakeHealth)(float flHealth, int bitsDamageType)
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
BOOL CBaseMonster::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
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
			vecDir = NormalizeSubtract<
				float_precision, float, float_precision, float_precision
				>(Center(), pInflictor->Center() - Vector(0, 0, 10));
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

		g_pevLastInflictor = NULL;
		return FALSE;
	}
	if ((pev->flags & FL_MONSTER) && !FNullEnt(pevAttacker))
	{
		if (pevAttacker->flags & (FL_MONSTER | FL_CLIENT))
		{
			if (pevInflictor)
			{
				if (m_hEnemy == NULL || pevInflictor == m_hEnemy->pev || !HasConditions(bits_COND_SEE_ENEMY))
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

// DeadTakeDamage - takedamage function called when a monster's corpse is damaged.
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
	float_precision force = damage * ((32 * 32 * 72.0) / (pev->size.x * pev->size.y * pev->size.z)) * 5;

	if (force > 1000.0)
	{
		force = 1000.0;
	}
	return force;
}

void EXT_FUNC PlayerBlind(CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, float fadeTime, float fadeHold, int alpha, Vector &color)
{
	UTIL_ScreenFade(pPlayer, color, fadeTime, fadeHold, alpha, 0);

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *pObserver = UTIL_PlayerByIndex(i);

		if (!pObserver || !pObserver->IsObservingPlayer(pPlayer))
			continue;

		if (!fadetoblack.value)
		{
			UTIL_ScreenFade(pObserver, color, fadeTime, fadeHold, alpha, 0);
		}
	}

	pPlayer->Blind(fadeTime * 0.33, fadeHold, fadeTime, alpha);

	if (TheBots != NULL)
	{
		TheBots->OnEvent(EVENT_PLAYER_BLINDED_BY_FLASHBANG, pPlayer);
	}
}

void RadiusFlash(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
	CBaseEntity *pEntity = NULL;
	TraceResult tr;
	float flAdjustedDamage, falloff;
	Vector vecSpot;
	float flRadius = 1500;

	if (flRadius)
		falloff = flDamage / flRadius;
	else
		falloff = 1;

	int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

	vecSrc.z += 1;

	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, 1500.0)) != NULL)
	{
		TraceResult tr2;
		Vector vecLOS;
		float flDot;
		float fadeTime;
		float fadeHold;
		int alpha;
		CBasePlayer *pPlayer;
		float currentHoldTime;

		if (!pEntity->IsPlayer())
			continue;

		pPlayer = (CBasePlayer *)pEntity;

		if (pPlayer->pev->takedamage == DAMAGE_NO || pPlayer->pev->deadflag != DEAD_NO)
			continue;

		if (bInWater && pPlayer->pev->waterlevel == 0)
			continue;

		if (!bInWater && pPlayer->pev->waterlevel == 3)
			continue;

		vecSpot = pPlayer->BodyTarget(vecSrc);
		UTIL_TraceLine(vecSrc, vecSpot, dont_ignore_monsters, ENT(pevInflictor), &tr);

		g_ReGameHookchains.m_RadiusFlash_TraceLine.callChain(NULL, pPlayer, pevInflictor, pevAttacker, vecSrc, vecSpot, &tr);

		if (tr.flFraction != 1.0f && tr.pHit != pPlayer->pev->pContainingEntity)
			continue;

#ifndef REGAMEDLL_FIXES
		UTIL_TraceLine(vecSpot, vecSrc, dont_ignore_monsters, tr.pHit, &tr2);

		if (tr2.flFraction >= 1.0)
#endif
		{
			if (tr.fStartSolid)
			{
				tr.vecEndPos = vecSrc;
				tr.flFraction = 0;
			}

			flAdjustedDamage = flDamage - (vecSrc - tr.vecEndPos).Length() * falloff;

			if (flAdjustedDamage < 0)
				flAdjustedDamage = 0;

			UTIL_MakeVectors(pPlayer->pev->v_angle);
			vecLOS = vecSrc - pPlayer->EarPosition();
			flDot = DotProduct(vecLOS, gpGlobals->v_forward);

			if (flDot < 0)
			{
				alpha = 200;
				fadeTime = flAdjustedDamage * 1.75;
				fadeHold = flAdjustedDamage / 3.5;
			}
			else
			{
				alpha = 255;
				fadeTime = flAdjustedDamage * 3;
				fadeHold = flAdjustedDamage / 1.5;
			}

			currentHoldTime = pPlayer->m_blindStartTime + pPlayer->m_blindHoldTime - gpGlobals->time;

			if (currentHoldTime > 0.0 && alpha == 255)
				fadeHold += currentHoldTime;

			if (pPlayer->m_blindStartTime != 0.0f && pPlayer->m_blindFadeTime != 0.0f)
			{
				if ((pPlayer->m_blindStartTime + pPlayer->m_blindFadeTime + pPlayer->m_blindHoldTime) > gpGlobals->time)
				{
					if (pPlayer->m_blindFadeTime > fadeTime)
						fadeTime = pPlayer->m_blindFadeTime;

					if (pPlayer->m_blindAlpha >= alpha)
						alpha = pPlayer->m_blindAlpha;
				}
			}

			Vector color(255, 255, 255);
			g_ReGameHookchains.m_PlayerBlind.callChain(PlayerBlind, pPlayer, pevInflictor, pevAttacker, fadeTime, fadeHold, alpha, color);
		}
	}
}

float GetAmountOfPlayerVisible(Vector vecSrc, CBaseEntity *entity)
{
	float retval = 0.0f;
	TraceResult tr;

	const float topOfHead = 25.0f;
	const float standFeet = 34.0f;
	const float crouchFeet = 14.0f;
	const float edgeOffset = 13.0f;

	const float damagePercentageChest = 0.40f;
	const float damagePercentageHead = 0.20f;
	const float damagePercentageFeet = 0.20f;
	const float damagePercentageRightSide = 0.10f;
	const float damagePercentageLeftSide = 0.10f;

	if (!entity->IsPlayer())
	{
		// the entity is not a player, so the damage is all or nothing.
		UTIL_TraceLine(vecSrc, entity->pev->origin, ignore_monsters, NULL, &tr);

		if (tr.flFraction == 1.0f)
			retval = 1.0f;

		return retval;
	}

	// check chest
	Vector vecChest = entity->pev->origin;
	UTIL_TraceLine(vecSrc, vecChest, ignore_monsters, NULL, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageChest;

	// check top of head
	Vector vecHead = entity->pev->origin + Vector(0, 0, topOfHead);
	UTIL_TraceLine(vecSrc, vecHead, ignore_monsters, NULL, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageHead;

	// check feet
	Vector vecFeet = entity->pev->origin;
	vecFeet.z -= (entity->pev->flags & FL_DUCKING) ? crouchFeet : standFeet;

	UTIL_TraceLine(vecSrc, vecFeet, ignore_monsters, NULL, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageFeet;

	Vector2D dir = (entity->pev->origin - vecSrc).Make2D();
	dir.NormalizeInPlace();

	Vector2D perp(-dir.y * edgeOffset, dir.x * edgeOffset);
	Vector vecRightSide = entity->pev->origin + Vector(perp.x, perp.y, 0);
	Vector vecLeftSide = entity->pev->origin - Vector(perp.x, perp.y, 0);

	// check right "edge"
	UTIL_TraceLine(vecSrc, vecRightSide, ignore_monsters, NULL, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageRightSide;

	// check left "edge"
	UTIL_TraceLine(vecSrc, vecLeftSide, ignore_monsters, NULL, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageLeftSide;

	return retval;
}

void RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
	CBaseEntity *pEntity = NULL;
	TraceResult tr;
	float flAdjustedDamage, falloff;
	Vector vecSpot;

	if (flRadius)
		falloff = flDamage / flRadius;
	else
		falloff = 1.0;

	int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

	// in case grenade is lying on the ground
	vecSrc.z += 1;

	if (!pevAttacker)
		pevAttacker = pevInflictor;

	// iterate on all entities in the vicinity.
	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flRadius)) != NULL)
	{
		if (pEntity->pev->takedamage != DAMAGE_NO)
		{
			// UNDONE: this should check a damage mask, not an ignore
			if (iClassIgnore != CLASS_NONE && pEntity->Classify() == iClassIgnore)
				continue;

			// blast's don't tavel into or out of water
			if (bInWater && pEntity->pev->waterlevel == 0)
				continue;

			if (!bInWater && pEntity->pev->waterlevel == 3)
				continue;

			bool useLOS = false;
			float damageRatio = 1.0f;

			if ((bitsDamageType & DMG_EXPLOSION) && g_bIsCzeroGame)
			{
				useLOS = true;
				damageRatio = GetAmountOfPlayerVisible(vecSrc, pEntity);
			}

			damageRatio = GetAmountOfPlayerVisible(vecSrc, pEntity);

			float length;
#ifdef REGAMEDLL_ADD
			// allow to damage breakable objects
			if (FClassnameIs(pEntity->pev, "func_breakable"))
				length = (vecSrc - pEntity->Center()).Length();
			else
#endif
				length = (vecSrc - pEntity->pev->origin).Length();

			if (useLOS)
			{
				if (!flRadius)
					flRadius = flDamage;

				if (!flDamage)
					flRadius = 0;

				flAdjustedDamage = (flRadius - length) * (flRadius - length) * 1.25 / (flRadius * flRadius) * (damageRatio * flDamage) * 1.5;
			}
			else
			{
				flAdjustedDamage = flDamage - length * falloff;
#ifdef REGAMEDLL_ADD
				// disable grenade damage through walls?
				if (hegrenade_penetration.string[0] == '1' && (bitsDamageType & DMG_EXPLOSION))
				{
					UTIL_TraceLine(vecSrc, pEntity->pev->origin, ignore_monsters, NULL, &tr);

					if (tr.flFraction != 1.0f)
						flAdjustedDamage = 0.0f;
				}
#endif
			}

#ifdef REGAMEDLL_FIXES
			// not allow inflict to the player damage is less than 1.0f and to entities not less than 0.0f
			if ((pEntity->Classify() == CLASS_PLAYER && flAdjustedDamage < 1.0f) || flAdjustedDamage <= 0.0f)
				continue;
#else
			if (flAdjustedDamage < 0)
				flAdjustedDamage = 0;
#endif
				pEntity->TakeDamage(pevInflictor, pevAttacker, flAdjustedDamage, bitsDamageType);
		}
	}
}

void RadiusDamage2(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
	CBaseEntity *pEntity = NULL;
	TraceResult tr;
	float flAdjustedDamage, falloff;
	Vector vecSpot;

	if (flRadius)
		falloff = flDamage / flRadius;
	else
		falloff = 1.0;

	int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

	// in case grenade is lying on the ground
	vecSrc.z += 1;

	if (!pevAttacker)
		pevAttacker = pevInflictor;

	// iterate on all entities in the vicinity.
	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flRadius)) != NULL)
	{
		if (pEntity->pev->takedamage != DAMAGE_NO)
		{
			// UNDONE: this should check a damage mask, not an ignore
			if (iClassIgnore != CLASS_NONE && pEntity->Classify() == iClassIgnore)
				continue;

			// blast's don't tavel into or out of water
			if (bInWater && pEntity->pev->waterlevel == 0)
				continue;

			if (!bInWater && pEntity->pev->waterlevel == 3)
				continue;

			vecSpot = pEntity->BodyTarget(vecSrc);
			UTIL_TraceLine(vecSrc, vecSpot, dont_ignore_monsters, ENT(pevInflictor), &tr);

			if (tr.flFraction == 1.0f || tr.pHit == pEntity->edict())
			{
				if (tr.fStartSolid)
				{
					tr.vecEndPos = vecSrc;
					tr.flFraction = 0;
				}

				flAdjustedDamage = flDamage - (vecSrc - pEntity->pev->origin).Length() * falloff;

				if (flAdjustedDamage < 0)
					flAdjustedDamage = 0;

				else if (flAdjustedDamage > 75)
					flAdjustedDamage = 75;

				if (tr.flFraction == 1.0f)
					pEntity->TakeDamage(pevInflictor, pevAttacker, flAdjustedDamage, bitsDamageType);

				else
				{
					ClearMultiDamage();
					pEntity->TraceAttack(pevInflictor, flAdjustedDamage, (tr.vecEndPos - vecSrc).Normalize(), &tr, bitsDamageType);
					ApplyMultiDamage(pevInflictor, pevAttacker);
				}
			}
		}
	}
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

// CheckTraceHullAttack - expects a length to trace, amount
// of damage to do, and damage type. Returns a pointer to
// the damaged entity in case the monster wishes to do
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

	return NULL;
}

// FInViewCone - returns true is the passed ent is in
// the caller's forward view cone. The dot product is performed
// in 2d, making the view cone infinitely tall.
BOOL CBaseMonster::__MAKE_VHOOK(FInViewCone)(CBaseEntity *pEntity)
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

// FInViewCone - returns true is the passed vector is in
// the caller's forward view cone. The dot product is performed
// in 2d, making the view cone infinitely tall.
BOOL CBaseMonster::__MAKE_VHOOK(FInViewCone)(const Vector *pOrigin)
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

// FVisible - returns true if a line can be traced from
// the caller's eyes to the target
BOOL CBaseEntity::__MAKE_VHOOK(FVisible)(CBaseEntity *pEntity)
{
	TraceResult tr;
	Vector vecLookerOrigin;
	Vector vecTargetOrigin;

	if (pEntity->pev->flags & FL_NOTARGET)
		return FALSE;

	// don't look through water
	if ((pev->waterlevel != 3 && pEntity->pev->waterlevel == 3) || (pev->waterlevel == 3 && pEntity->pev->waterlevel == 0))
		return FALSE;

	//look through the caller's 'eyes'
	vecLookerOrigin = pev->origin + pev->view_ofs;
	vecTargetOrigin = pEntity->EyePosition();

	UTIL_TraceLine(vecLookerOrigin, vecTargetOrigin, ignore_monsters, ignore_glass, ENT(pev), &tr);

	if (tr.flFraction != 1.0f)
	{
		// Line of sight is not established
		return FALSE;
	}
	else
	{
		// line of sight is valid.
		return TRUE;
	}
}

// FVisible - returns true if a line can be traced from
// the caller's eyes to the target vector
BOOL CBaseEntity::__MAKE_VHOOK(FVisible)(const Vector &vecOrigin)
{
	TraceResult tr;
	Vector vecLookerOrigin;

	//look through the caller's 'eyes'
	vecLookerOrigin = EyePosition();

	UTIL_TraceLine(vecLookerOrigin, vecOrigin, ignore_monsters, ignore_glass, ENT(pev), &tr);

	if (tr.flFraction != 1.0f)
	{
		// Line of sight is not established
		return FALSE;
	}
	else
	{
		// line of sight is valid.
		return TRUE;
	}
}

void CBaseEntity::__MAKE_VHOOK(TraceAttack)(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	Vector vecOrigin = ptr->vecEndPos - vecDir * 4;

	if (pev->takedamage != DAMAGE_NO)
	{
		AddMultiDamage(pevAttacker, this, flDamage, bitsDamageType);

		int blood = BloodColor();
		if (blood != DONT_BLEED)
		{
			// a little surface blood.
			SpawnBlood(vecOrigin, blood, flDamage);
			TraceBleed(flDamage, vecDir, ptr, bitsDamageType);
		}
	}
}

void CBaseMonster::__MAKE_VHOOK(TraceAttack)(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
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

void CBaseEntity::FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker)
{
	static int tracerCount;
	int tracer;

	TraceResult tr;
	Vector vecRight, vecUp;
	bool m_bCreatedShotgunSpark = true;

	vecRight = gpGlobals->v_right;
	vecUp = gpGlobals->v_up;

	if (!pevAttacker)
	{
		// the default attacker is ourselves
		pevAttacker = pev;
	}

	ClearMultiDamage();
	gMultiDamage.type = (DMG_BULLET | DMG_NEVERGIB);

	for (ULONG iShot = 1; iShot <= cShots; ++iShot)
	{
		int spark = 0;

		// get circular gaussian spread
		float x, y, z;

		do
		{
			x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			z = x * x + y * y;
		}
		while (z > 1);

		Vector vecDir, vecEnd;

		vecDir = vecDirShooting + x * vecSpread.x * vecRight + y * vecSpread.y * vecUp;
		vecEnd = vecSrc + vecDir * flDistance;

		UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev), &tr);
		tracer = 0;

		if (iTracerFreq != 0 && !(tracerCount++ % iTracerFreq))
		{
			Vector vecTracerSrc;

			if (IsPlayer())
			{
				// adjust tracer position for player
				vecTracerSrc = vecSrc + Vector(0, 0, -4) + gpGlobals->v_right * 2 + gpGlobals->v_forward * 16;
			}
			else
			{
				vecTracerSrc = vecSrc;
			}

			// guns that always trace also always decal
			if (iTracerFreq != 1)
				tracer = 1;

			MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, vecTracerSrc);
				WRITE_BYTE(TE_TRACER);
				WRITE_COORD(vecTracerSrc.x);
				WRITE_COORD(vecTracerSrc.y);
				WRITE_COORD(vecTracerSrc.z);
				WRITE_COORD(tr.vecEndPos.x);
				WRITE_COORD(tr.vecEndPos.y);
				WRITE_COORD(tr.vecEndPos.z);
			MESSAGE_END();
		}

		// do damage, paint decals
		if (tr.flFraction != 1.0f)
		{
			CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

			if (iDamage)
			{
				pEntity->TraceAttack(pevAttacker, iDamage, vecDir, &tr, DMG_BULLET | ((iDamage > 16) ? DMG_ALWAYSGIB : DMG_NEVERGIB));
				TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
				DecalGunshot(&tr, iBulletType, false, pev, false);
			}
			else
			{
				float flDamage;

				switch (iBulletType)
				{
				case BULLET_PLAYER_MP5:
					pEntity->TraceAttack(pevAttacker, gSkillData.plrDmgMP5, vecDir, &tr, DMG_BULLET);
					break;
				case BULLET_PLAYER_BUCKSHOT:
					flDamage = ((1 - tr.flFraction) * 20);
					pEntity->TraceAttack(pevAttacker, int(flDamage), vecDir, &tr, DMG_BULLET);
					break;
				case BULLET_PLAYER_357:
					pEntity->TraceAttack(pevAttacker, gSkillData.plrDmg357, vecDir, &tr, DMG_BULLET);
					break;
				case BULLET_MONSTER_9MM:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmg9MM, vecDir, &tr, DMG_BULLET);
					TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
					DecalGunshot(&tr, iBulletType, false, pev, false);
					break;
				case BULLET_MONSTER_MP5:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmgMP5, vecDir, &tr, DMG_BULLET);
					TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
					DecalGunshot(&tr, iBulletType, false, pev, false);
					break;
				case BULLET_MONSTER_12MM:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmg12MM, vecDir, &tr, DMG_BULLET);

					if (!tracer)
					{
						TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
						DecalGunshot(&tr, iBulletType, false, pev, false);
					}
					break;
				case BULLET_NONE:
					flDamage = 50;
					pEntity->TraceAttack(pevAttacker, flDamage, vecDir, &tr, DMG_CLUB);
					TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);

					// only decal glass
					if (!FNullEnt(tr.pHit) && VARS(tr.pHit)->rendermode != kRenderNormal)
					{
						UTIL_DecalTrace(&tr, DECAL_GLASSBREAK1 + RANDOM_LONG(0, 2));
					}
					break;
				default:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmg9MM, vecDir, &tr, DMG_BULLET);
					break;
				}
			}
		}

		// make bullet trails
		UTIL_BubbleTrail(vecSrc, tr.vecEndPos, int((flDistance * tr.flFraction) / 64));
	}

	ApplyMultiDamage(pev, pevAttacker);
}

NOXREF char *vstr(float *v)
{
	static int idx = 0;
	static char string[ 16 ][ 1024 ];

	idx = (idx + 1) % 0xF;
	Q_sprintf(string[ idx ], "%.4f %.4f %.4f", v[0], v[1], v[2]);

	return string[ idx ];
}

// Go to the trouble of combining multiple pellets into a single damage call.
// This version is used by Players, uses the random seed generator to sync client and server side shots.
Vector CBaseEntity::FireBullets3(Vector vecSrc, Vector vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand)
{
	int iOriginalPenetration = iPenetration;
	int iPenetrationPower;
	float flPenetrationDistance;
	int iCurrentDamage = iDamage;
	float flCurrentDistance;

	TraceResult tr, tr2;
	Vector vecRight, vecUp;

	bool bHitMetal = false;
	int iSparksAmount = 1;

	vecRight = gpGlobals->v_right;
	vecUp = gpGlobals->v_up;

	switch (iBulletType)
	{
	case BULLET_PLAYER_9MM:
		iPenetrationPower = 21;
		flPenetrationDistance = 800;
		break;
	case BULLET_PLAYER_45ACP:
		iPenetrationPower = 15;
		flPenetrationDistance = 500;
		break;
	case BULLET_PLAYER_50AE:
		iPenetrationPower = 30;
		flPenetrationDistance = 1000;
		break;
	case BULLET_PLAYER_762MM:
		iPenetrationPower = 39;
		flPenetrationDistance = 5000;
		break;
	case BULLET_PLAYER_556MM:
		iPenetrationPower = 35;
		flPenetrationDistance = 4000;
		break;
	case BULLET_PLAYER_338MAG:
		iPenetrationPower = 45;
		flPenetrationDistance = 8000;
		break;
	case BULLET_PLAYER_57MM:
		iPenetrationPower = 30;
		flPenetrationDistance = 2000;
		break;
	case BULLET_PLAYER_357SIG:
		iPenetrationPower = 25;
		flPenetrationDistance = 800;
		break;
	default:
		iPenetrationPower = 0;
		flPenetrationDistance = 0;
		break;
	}

	if (!pevAttacker)
	{
		// the default attacker is ourselves
		pevAttacker = pev;
	}

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

	Vector vecDir, vecEnd;
	Vector vecOldSrc, vecNewSrc;

	vecDir = vecDirShooting + x * vecSpread * vecRight + y * vecSpread * vecUp;
	vecEnd = vecSrc + vecDir * flDistance;

	float flDamageModifier = 0.5;

	while (iPenetration != 0)
	{
		ClearMultiDamage();
		UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev), &tr);

		if (TheBots != NULL && tr.flFraction != 1.0f)
		{
			TheBots->OnEvent(EVENT_BULLET_IMPACT, this, (CBaseEntity *)&tr.vecEndPos);
		}

		char cTextureType = UTIL_TextureHit(&tr, vecSrc, vecEnd);
		bool bSparks = false;

		switch (cTextureType)
		{
		case CHAR_TEX_METAL:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.15;
			flDamageModifier = 0.2;
			break;
		case CHAR_TEX_CONCRETE:
			iPenetrationPower *= 0.25;
			break;
		case CHAR_TEX_GRATE:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.5;
			flDamageModifier = 0.4;
			break;
		case CHAR_TEX_VENT:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.5;
			flDamageModifier = 0.45;
			break;
		case CHAR_TEX_TILE:
			iPenetrationPower *= 0.65;
			flDamageModifier = 0.3;
			break;
		case CHAR_TEX_COMPUTER:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.4;
			flDamageModifier = 0.45;
			break;
		case CHAR_TEX_WOOD:
			flDamageModifier = 0.6;
			break;
		default:
			break;
		}
		if (tr.flFraction != 1.0f)
		{
			CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
			iPenetration--;

			flCurrentDistance = tr.flFraction * flDistance;
			iCurrentDamage *= Q_pow(flRangeModifier, flCurrentDistance / 500);

			if (flCurrentDistance > flPenetrationDistance)
			{
				iPenetration = 0;
			}

			if (tr.iHitgroup == HITGROUP_SHIELD)
			{
				EMIT_SOUND(pEntity->edict(), CHAN_VOICE, (RANDOM_LONG(0, 1) == 1) ? "weapons/ric_metal-1.wav" : "weapons/ric_metal-2.wav", VOL_NORM, ATTN_NORM);
				UTIL_Sparks(tr.vecEndPos);

				pEntity->pev->punchangle.x = iCurrentDamage * RANDOM_FLOAT(-0.15, 0.15);
				pEntity->pev->punchangle.z = iCurrentDamage * RANDOM_FLOAT(-0.15, 0.15);

				if (pEntity->pev->punchangle.x < 4)
				{
					pEntity->pev->punchangle.x = -4;
				}

				if (pEntity->pev->punchangle.z < -5)
				{
					pEntity->pev->punchangle.z = -5;
				}
				else if (pEntity->pev->punchangle.z > 5)
				{
					pEntity->pev->punchangle.z = 5;
				}

				break;
			}

			float flDistanceModifier;
			if (VARS(tr.pHit)->solid != SOLID_BSP || !iPenetration)
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

			pEntity->TraceAttack(pevAttacker, iCurrentDamage, vecDir, &tr, (DMG_BULLET | DMG_NEVERGIB));
			iCurrentDamage *= flDamageModifier;
		}
		else
			iPenetration = 0;

		ApplyMultiDamage(pev, pevAttacker);
	}

	return Vector(x * vecSpread, y * vecSpread, 0);
}

void CBaseEntity::__MAKE_VHOOK(TraceBleed)(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
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

	for (i = 0; i < cCount; ++i)
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
			{
				UTIL_BloodDecalTrace(&Bloodtr, BloodColor());
			}
		}
	}
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
			pev->max_health--;
	}

	for (i = 0; i < cCount; ++i)
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
