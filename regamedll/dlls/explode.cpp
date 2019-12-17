#include "precompiled.h"

LINK_ENTITY_TO_CLASS(spark_shower, CShower, CCSShower)

void CShower::Spawn()
{
	pev->velocity = RANDOM_FLOAT(200, 300) * pev->angles;
	pev->velocity.x += RANDOM_FLOAT(-100, 100);
	pev->velocity.y += RANDOM_FLOAT(-100, 100);

	if (pev->velocity.z >= 0)
		pev->velocity.z += 200;
	else
		pev->velocity.z -= 200;

	pev->movetype = MOVETYPE_BOUNCE;
	pev->gravity = 0.5f;
	pev->nextthink = gpGlobals->time + 0.1f;
	pev->solid = SOLID_NOT;

	// Need a model, just use the grenade, we don't draw it anyway
	SET_MODEL(edict(), "models/grenade.mdl");
	UTIL_SetSize(pev, g_vecZero, g_vecZero);

	pev->effects |= EF_NODRAW;
	pev->speed = RANDOM_FLOAT(0.5, 1.5);
	pev->angles = g_vecZero;
}

void CShower::Think()
{
	UTIL_Sparks(pev->origin);

	pev->speed -= 0.1f;

	if (pev->speed > 0)
		pev->nextthink = gpGlobals->time + 0.1f;
	else
		UTIL_Remove(this);

	pev->flags &= ~FL_ONGROUND;
}

void CShower::Touch(CBaseEntity *pOther)
{
	if (pev->flags & FL_ONGROUND)
		pev->velocity = pev->velocity * 0.1f;
	else
		pev->velocity = pev->velocity * 0.6f;

	if ((pev->velocity.x * pev->velocity.x + pev->velocity.y * pev->velocity.y) < 10.0f)
	{
		pev->speed = 0;
	}
}

TYPEDESCRIPTION CEnvExplosion::m_SaveData[] =
{
	DEFINE_FIELD(CEnvExplosion, m_iMagnitude, FIELD_INTEGER),
	DEFINE_FIELD(CEnvExplosion, m_spriteScale, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CEnvExplosion, CBaseMonster)
LINK_ENTITY_TO_CLASS(env_explosion, CEnvExplosion, CCSEnvExplosion)

void CEnvExplosion::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "iMagnitude"))
	{
		m_iMagnitude = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CEnvExplosion::Spawn()
{
	pev->solid = SOLID_NOT;
	pev->effects = EF_NODRAW;
	pev->movetype = MOVETYPE_NONE;

	float flSpriteScale = (m_iMagnitude - 50) * 0.6f;

	if (flSpriteScale < 10.0f)
	{
		flSpriteScale = 10.0f;
	}

	m_spriteScale = int(flSpriteScale);
}

void CEnvExplosion::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	TraceResult tr;

	pev->model = iStringNull;// invisible
	pev->solid = SOLID_NOT;// intangible

	Vector vecSpot;// trace starts here!

	vecSpot = pev->origin + Vector(0, 0, 8);

	UTIL_TraceLine(vecSpot, vecSpot + Vector(0, 0, -40), ignore_monsters, ENT(pev), &tr);

	// Pull out of the wall a bit
	if (tr.flFraction != 1.0f)
	{
		pev->origin = tr.vecEndPos + (tr.vecPlaneNormal * (m_iMagnitude - 24) * 0.6f);
	}

	// draw decal
	if (!(pev->spawnflags & SF_ENVEXPLOSION_NODECAL))
	{
		if (RANDOM_FLOAT(0, 1) < 0.5f)
		{
			UTIL_DecalTrace(&tr, DECAL_SCORCH1);
		}
		else
		{
			UTIL_DecalTrace(&tr, DECAL_SCORCH2);
		}
	}

	// draw fireball
	if (!(pev->spawnflags & SF_ENVEXPLOSION_NOFIREBALL))
	{
		MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_EXPLOSION);
			WRITE_COORD(pev->origin.x);
			WRITE_COORD(pev->origin.y);
			WRITE_COORD(pev->origin.z);
			WRITE_SHORT(g_sModelIndexFireball);
			WRITE_BYTE(byte(m_spriteScale)); // scale * 10
			WRITE_BYTE(15); // framerate
			WRITE_BYTE(TE_EXPLFLAG_NONE);
		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_EXPLOSION);
			WRITE_COORD(pev->origin.x);
			WRITE_COORD(pev->origin.y);
			WRITE_COORD(pev->origin.z);
			WRITE_SHORT(g_sModelIndexFireball);
			WRITE_BYTE(0); // no sprite
			WRITE_BYTE(15); // framerate
			WRITE_BYTE(TE_EXPLFLAG_NONE);
		MESSAGE_END();
	}

	// do damage
	if (!(pev->spawnflags & SF_ENVEXPLOSION_NODAMAGE))
	{
		RadiusDamage(pev, pev, m_iMagnitude, CLASS_NONE, DMG_BLAST);
	}

	SetThink(&CEnvExplosion::Smoke);
	pev->nextthink = gpGlobals->time + 0.3f;

	// draw sparks
	if (!(pev->spawnflags & SF_ENVEXPLOSION_NOSPARKS))
	{
		int sparkCount = RANDOM_LONG(0, 3);
		for (int i = 0; i < sparkCount; i++)
		{
			Create("spark_shower", pev->origin, tr.vecPlaneNormal, nullptr);
		}
	}
}

void CEnvExplosion::Smoke()
{
	if (!(pev->spawnflags & SF_ENVEXPLOSION_NOSMOKE))
	{
		MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
			WRITE_BYTE(TE_SMOKE);
			WRITE_COORD(pev->origin.x);
			WRITE_COORD(pev->origin.y);
			WRITE_COORD(pev->origin.z);
			WRITE_SHORT(g_sModelIndexSmoke);
			WRITE_BYTE(byte(m_spriteScale)); // scale * 10
			WRITE_BYTE(12); // framerate
		MESSAGE_END();
	}

	if (!(pev->spawnflags & SF_ENVEXPLOSION_REPEATABLE))
	{
		UTIL_Remove(this);
	}
}

// HACKHACK: create one of these and fake a keyvalue to get the right explosion setup
void ExplosionCreate(const Vector &center, Vector &angles, edict_t *pOwner, int magnitude, BOOL doDamage)
{
	KeyValueData kvd;
	char buf[128];

	CBaseEntity *pExplosion = CBaseEntity::Create("env_explosion", center, angles, pOwner);

	Q_sprintf(buf, "%3d", magnitude);

	kvd.szKeyName = "iMagnitude";
	kvd.szValue = buf;

	pExplosion->KeyValue(&kvd);

	if (!doDamage)
	{
		pExplosion->pev->spawnflags |= SF_ENVEXPLOSION_NODAMAGE;
	}

	pExplosion->Spawn();
	pExplosion->Use(nullptr, nullptr, USE_TOGGLE, 0);
}
