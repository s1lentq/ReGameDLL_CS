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

	for (int i = 0; i < cGibs; i++)
	{
		CGib *pGib = GetClassPtr<CCSGib>((CGib *)nullptr);

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
			pGib->SetThink(nullptr);
		}

		pGib->LimitVelocity();
	}
}

void CGib::SpawnHeadGib(entvars_t *pevVictim)
{
	CGib *pGib = GetClassPtr<CCSGib>((CGib *)nullptr);

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

		if (RANDOM_LONG(0, 100) <= 5 && pentPlayer)
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
	for (int cSplat = 0; cSplat < cGibs; cSplat++)
	{
		CGib *pGib = GetClassPtr<CCSGib>((CGib *)nullptr);

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
