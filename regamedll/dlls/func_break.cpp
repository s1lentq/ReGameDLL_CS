#include "precompiled.h"

// Just add more items to the bottom of this array and they will automagically be supported
// This is done instead of just a classname in the FGD so we can control which entities can
// be spawned, and still remain fairly flexible
const char *CBreakable::m_pszSpawnObjects[] =
{
	nullptr,
	"item_battery",
	"item_healthkit",
	"weapon_9mmhandgun",
	"ammo_9mmclip",
	"weapon_9mmAR",
	"ammo_9mmAR",
	"ammo_ARgrenades",
	"weapon_shotgun",
	"ammo_buckshot",
	"weapon_crossbow",
	"ammo_crossbow",
	"weapon_357",
	"ammo_357",
	"weapon_rpg",
	"ammo_rpgclip",
	"ammo_gaussclip",
	"weapon_handgrenade",
	"weapon_tripmine",
	"weapon_satchel",
	"weapon_snark",
	"weapon_hornetgun",
	"weapon_usp",
	"weapon_glock18",
	"weapon_awp",
	"weapon_mp5n",
	"weapon_m249",
	"weapon_m3",
	"weapon_m4a1",
	"weapon_tmp",
	"weapon_g3sg1",
	"weapon_flashbang"
};

const char *CBreakable::m_pszSoundsWood[] =
{
	"debris/wood1.wav",
	"debris/wood2.wav",
	"debris/wood3.wav"
};

const char *CBreakable::m_pszSoundsFlesh[] =
{
	"debris/flesh1.wav",
	"debris/flesh2.wav",
	"debris/flesh3.wav",
	"debris/flesh5.wav",
	"debris/flesh6.wav",
	"debris/flesh7.wav"
};

const char *CBreakable::m_pszSoundsMetal[] =
{
	"debris/metal1.wav",
	"debris/metal2.wav",
	"debris/metal3.wav"
};

const char *CBreakable::m_pszSoundsConcrete[] =
{
	"debris/concrete1.wav",
	"debris/concrete2.wav",
	"debris/concrete3.wav"
};

const char *CBreakable::m_pszSoundsGlass[] =
{
	"debris/glass1.wav",
	"debris/glass2.wav",
	"debris/glass3.wav"
};

TYPEDESCRIPTION CBreakable::m_SaveData[] =
{
	DEFINE_FIELD(CBreakable, m_Material, FIELD_INTEGER),
	DEFINE_FIELD(CBreakable, m_Explosion, FIELD_INTEGER),
	DEFINE_FIELD(CBreakable, m_angle, FIELD_FLOAT),
	DEFINE_FIELD(CBreakable, m_iszGibModel, FIELD_STRING),
	DEFINE_FIELD(CBreakable, m_iszSpawnObject, FIELD_STRING),
};

LINK_ENTITY_TO_CLASS(func_breakable, CBreakable, CCSBreakable)
IMPLEMENT_SAVERESTORE(CBreakable, CBaseEntity)

LINK_HOOK_CLASS_VOID_CHAIN2(CBreakable, Spawn)

void EXT_FUNC CBreakable::__API_HOOK(Spawn)()
{
	Precache();

	if (pev->spawnflags & SF_BREAK_TRIGGER_ONLY)
		pev->takedamage = DAMAGE_NO;
	else
		pev->takedamage = DAMAGE_YES;

	m_flHealth = pev->health;
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;
	m_angle = pev->angles.y;
	pev->angles.y = 0;

	// HACK: matGlass can receive decals, we need the client to know about this
	// so use class to store the material flag
	if (m_Material == matGlass)
	{
		pev->playerclass = 1;
	}

	// set size and link into world.
	SET_MODEL(ENT(pev), STRING(pev->model));

	SetTouch(&CBreakable::BreakTouch);

	// Only break on trigger
	if (pev->spawnflags & SF_BREAK_TRIGGER_ONLY)
	{
		SetTouch(nullptr);
	}

	// Flag unbreakable glass as "worldbrush" so it will block ALL tracelines
	if (!IsBreakable() && pev->rendermode != kRenderNormal)
	{
		pev->flags |= FL_WORLDBRUSH;
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBreakable, Restart)

void EXT_FUNC CBreakable::__API_HOOK(Restart)()
{
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;
	pev->deadflag = DEAD_NO;

	if (pev->spawnflags & SF_BREAK_TRIGGER_ONLY)
		pev->takedamage = DAMAGE_NO;
	else
		pev->takedamage = DAMAGE_YES;

	pev->health = m_flHealth;
	pev->effects &= ~EF_NODRAW;
	m_angle = pev->angles.y;
	pev->angles.y = 0;

	SET_MODEL(ENT(pev), STRING(pev->model));
	SetTouch(&CBreakable::BreakTouch);

	if (pev->spawnflags & SF_BREAK_TRIGGER_ONLY)
	{
		SetTouch(nullptr);
	}

	if (!IsBreakable() && pev->rendermode != kRenderNormal)
	{
		pev->flags |= FL_WORLDBRUSH;
	}

#ifdef REGAMEDLL_FIXES
	if (m_iszSpawnObject)
	{
		CBaseEntity *pEntity = nullptr;

		while ((pEntity = UTIL_FindEntityByClassname(pEntity, STRING(m_iszSpawnObject))))
		{
			if (!FNullEnt(pEntity->pev->owner) && FClassnameIs(pEntity->pev->owner, "func_breakable"))
			{
				pEntity->SetThink(&CBaseEntity::SUB_Remove);
				pEntity->pev->nextthink = gpGlobals->time + 0.1f;
			}
		}
	}
#endif
}

void CBreakable::KeyValue(KeyValueData *pkvd)
{
	// UNDONE_WC: explicitly ignoring these fields, but they shouldn't be in the map file!
	if (FStrEq(pkvd->szKeyName, "explosion"))
	{
		if (!Q_stricmp(pkvd->szValue, "directed"))
			m_Explosion = expDirected;

		else if (!Q_stricmp(pkvd->szValue, "random"))
			m_Explosion = expRandom;
		else
			m_Explosion = expRandom;

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "material"))
	{
		Materials type = (Materials)Q_atoi(pkvd->szValue);

		// 0:glass, 1:wood, 2:metal, 3:flesh etc
		if (type < 0 || type >= matLastMaterial)
			m_Material = matWood;
		else
			m_Material = type;

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "deadmodel"))
	{
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "shards"))
	{
		//m_iShards = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "gibmodel"))
	{
		m_iszGibModel = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "spawnobject"))
	{
		int object = Q_atoi(pkvd->szValue);
		if (object > 0 && object < ARRAYSIZE(m_pszSpawnObjects))
		{
			m_iszSpawnObject = MAKE_STRING(m_pszSpawnObjects[object]);
		}

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "explodemagnitude"))
	{
		ExplosionSetMagnitude(Q_atoi(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "lip"))
	{
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseDelay::KeyValue(pkvd);
	}
}

const char **CBreakable::MaterialSoundList(Materials precacheMaterial, int &soundCount)
{
	const char **pSoundList;

	switch (precacheMaterial)
	{
	case matWood:
	{
		pSoundList = m_pszSoundsWood;
		soundCount = ARRAYSIZE(m_pszSoundsWood);
		break;
	}
	case matFlesh:
	{
		pSoundList = m_pszSoundsFlesh;
		soundCount = ARRAYSIZE(m_pszSoundsFlesh);
		break;
	}
	case matGlass:
	case matComputer:
	case matUnbreakableGlass:
	{
		pSoundList = m_pszSoundsGlass;
		soundCount = ARRAYSIZE(m_pszSoundsGlass);
		break;
	}
	case matMetal:
	{
		pSoundList = m_pszSoundsMetal;
		soundCount = ARRAYSIZE(m_pszSoundsMetal);
		break;
	}
	case matCinderBlock:
	case matRocks:
	{
		pSoundList = m_pszSoundsConcrete;
		soundCount = ARRAYSIZE(m_pszSoundsConcrete);
		break;
	}
	case matCeilingTile:
	case matNone:
	default:
		pSoundList = nullptr;
		soundCount = 0;
		break;
	}

	return pSoundList;
}

void CBreakable::MaterialSoundPrecache(Materials precacheMaterial)
{
	const char **pSoundList;
	int i, soundCount = 0;

	pSoundList = MaterialSoundList(precacheMaterial, soundCount);

	for (i = 0; i < soundCount; i++)
	{
		PRECACHE_SOUND((char *)pSoundList[i]);
	}
}

void CBreakable::MaterialSoundRandom(edict_t *pEdict, Materials soundMaterial, float volume)
{
	int soundCount = 0;
	const char **pSoundList = MaterialSoundList(soundMaterial, soundCount);

	if (soundCount)
	{
		EMIT_SOUND(pEdict, CHAN_BODY, pSoundList[RANDOM_LONG(0, soundCount - 1)], volume, 1.0);
	}
}

void CBreakable::Precache()
{
	const char *pGibName = nullptr;

	switch (m_Material)
	{
	case matWood:
		pGibName = "models/woodgibs.mdl";

		PRECACHE_SOUND("debris/bustcrate1.wav");
		PRECACHE_SOUND("debris/bustcrate2.wav");
		break;
	case matFlesh:
		pGibName = "models/fleshgibs.mdl";

		PRECACHE_SOUND("debris/bustflesh1.wav");
		PRECACHE_SOUND("debris/bustflesh2.wav");
		break;
	case matComputer:
		PRECACHE_SOUND("buttons/spark5.wav");
		PRECACHE_SOUND("buttons/spark6.wav");
		pGibName = "models/computergibs.mdl";

		PRECACHE_SOUND("debris/bustmetal1.wav");
		PRECACHE_SOUND("debris/bustmetal2.wav");
		break;
	case matGlass:
	case matUnbreakableGlass:
		pGibName = "models/glassgibs.mdl";

		PRECACHE_SOUND("debris/bustglass1.wav");
		PRECACHE_SOUND("debris/bustglass2.wav");
		break;
	case matMetal:
		pGibName = "models/metalplategibs.mdl";

		PRECACHE_SOUND("debris/bustmetal1.wav");
		PRECACHE_SOUND("debris/bustmetal2.wav");
		break;
	case matCinderBlock:
		pGibName = "models/cindergibs.mdl";

		PRECACHE_SOUND("debris/bustconcrete1.wav");
		PRECACHE_SOUND("debris/bustconcrete2.wav");
		break;
	case matRocks:
		pGibName = "models/rockgibs.mdl";

		PRECACHE_SOUND("debris/bustconcrete1.wav");
		PRECACHE_SOUND("debris/bustconcrete2.wav");
		break;
	case matCeilingTile:
		pGibName = "models/ceilinggibs.mdl";

		PRECACHE_SOUND("debris/bustceiling.wav");
		break;
	}

	MaterialSoundPrecache(m_Material);

	if (m_iszGibModel)
	{
		pGibName = STRING(m_iszGibModel);
	}

	if (pGibName)
	{
		m_idShard = PRECACHE_MODEL(pGibName);
	}

	// Precache the spawn item's data
	if (m_iszSpawnObject)
	{
		UTIL_PrecacheOther(STRING(m_iszSpawnObject));
	}
}

void CBreakable::DamageSound()
{
	int pitch;
	float fvol;
	char *rgpsz[6];
	int i = 0;
	int material = m_Material;

	if (RANDOM_LONG(0, 2))
		pitch = PITCH_NORM;
	else
		pitch = 95 + RANDOM_LONG(0, 34);

	fvol = RANDOM_FLOAT(0.75, 1.0);

#ifndef REGAMEDLL_FIXES
	if (material == matComputer && RANDOM_LONG(0, 1))
		material = matMetal;
#endif

	switch (material)
	{
	case matGlass:
	case matComputer:
	case matUnbreakableGlass:
		rgpsz[0] = "debris/glass1.wav";
		rgpsz[1] = "debris/glass2.wav";
		rgpsz[2] = "debris/glass3.wav";
		i = 3;
		break;

	case matWood:
		rgpsz[0] = "debris/wood1.wav";
		rgpsz[1] = "debris/wood2.wav";
		rgpsz[2] = "debris/wood3.wav";
		i = 3;
		break;

	case matMetal:
		rgpsz[0] = "debris/metal1.wav";
		rgpsz[1] = "debris/metal3.wav";
		rgpsz[2] = "debris/metal2.wav";
#ifdef REGAMEDLL_FIXES
		i = 3;
#else
		i = 2;
#endif
		break;

	case matFlesh:
		rgpsz[0] = "debris/flesh1.wav";
		rgpsz[1] = "debris/flesh2.wav";
		rgpsz[2] = "debris/flesh3.wav";
		rgpsz[3] = "debris/flesh5.wav";
		rgpsz[4] = "debris/flesh6.wav";
		rgpsz[5] = "debris/flesh7.wav";
		i = 6;
		break;

	case matRocks:
	case matCinderBlock:
		rgpsz[0] = "debris/concrete1.wav";
		rgpsz[1] = "debris/concrete2.wav";
		rgpsz[2] = "debris/concrete3.wav";
		i = 3;
		break;

	case matCeilingTile:
		// UNDONE: no ceiling tile shard sound yet
		i = 0;
		break;
	}

	if (i)
	{
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, rgpsz[RANDOM_LONG(0, i - 1)], fvol, ATTN_NORM, 0, pitch);
	}
}

LINK_HOOK_CLASS_VOID_CHAIN(CBreakable, BreakTouch, (CBaseEntity *pOther), pOther)

void EXT_FUNC CBreakable::__API_HOOK(BreakTouch)(CBaseEntity *pOther)
{
	float flDamage;
	entvars_t *pevToucher = pOther->pev;

	// only players can break these right now
	if (!pOther->IsPlayer() || !IsBreakable())
	{
		if (pev->rendermode == kRenderNormal || !FClassnameIs(pOther->pev, "grenade"))
			return;

		pev->angles.y = m_angle;
		UTIL_MakeVectors(pev->angles);

		g_vecAttackDir = gpGlobals->v_forward;

#ifndef REGAMEDLL_FIXES
		pev->takedamage = DAMAGE_NO;
		pev->deadflag = DEAD_DEAD;
		pev->effects = EF_NODRAW;
#endif

		Die();
	}

	// can be broken when run into
	if (pev->spawnflags & SF_BREAK_TOUCH)
	{
		flDamage = pevToucher->velocity.Length() * 0.01f;

		if (flDamage >= pev->health)
		{
			SetTouch(nullptr);
			TakeDamage(pevToucher, pevToucher, flDamage, DMG_CRUSH);

			// do a little damage to player if we broke glass or computer
			pOther->TakeDamage(pev, pev, flDamage / 4, DMG_SLASH);
		}
	}

	// can be broken when stood upon
	if ((pev->spawnflags & SF_BREAK_PRESSURE) && pevToucher->absmin.z >= pev->maxs.z - 2)
	{
		// play creaking sound here.
		DamageSound();

		SetThink(&CBreakable::Die);
		SetTouch(nullptr);

		// BUGBUG: why doesn't zero delay work?
		if (m_flDelay == 0.0f)
		{
			m_flDelay = 0.1f;
		}

		pev->nextthink = pev->ltime + m_flDelay;
	}
}

LINK_HOOK_CLASS_VOID_CHAIN(CBreakable, Use, (CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value), pActivator, pCaller, useType, value)
// Smash the our breakable object
// Break when triggered
void EXT_FUNC CBreakable::__API_HOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, FloatRef value)
{
	if (IsBreakable())
	{
		pev->angles.y = m_angle;
		UTIL_MakeVectors(pev->angles);
		g_vecAttackDir = gpGlobals->v_forward;

#ifndef REGAMEDLL_FIXES
		pev->takedamage = DAMAGE_NO;
		pev->deadflag = DEAD_DEAD;
		pev->effects = EF_NODRAW;
#endif

		Die();
	}
}

LINK_HOOK_CLASS_VOID_CHAIN(CBreakable, TraceAttack, (entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType), pevAttacker, flDamage, vecDir, ptr, bitsDamageType)

void EXT_FUNC CBreakable::__API_HOOK(TraceAttack)(entvars_t *pevAttacker, float flDamage, VectorRef vecDir, TraceResult *ptr, int bitsDamageType)
{
	// random spark if this is a 'computer' object
	if (RANDOM_LONG(0, 1))
	{
		switch (m_Material)
		{
		case matComputer:
		{
			UTIL_Sparks(ptr->vecEndPos);

			//random volume range
			float flVolume = RANDOM_FLOAT(0.7 , 1.0);
			switch (RANDOM_LONG(0, 1))
			{
			case 0: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark5.wav", flVolume, ATTN_NORM); break;
			case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "buttons/spark6.wav", flVolume, ATTN_NORM); break;
			}

			break;
		}
		case matUnbreakableGlass:
		{
			UTIL_Ricochet(ptr->vecEndPos, RANDOM_FLOAT(0.5, 1.5));
			break;
		}
		}
	}

	CBaseDelay::TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}

LINK_HOOK_CLASS_CHAIN(BOOL, CBreakable, TakeDamage, (entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType), pevInflictor, pevAttacker, flDamage, bitsDamageType)
// Special takedamage for func_breakable. Allows us to make
// exceptions that are breakable-specific
// bitsDamageType indicates the type of damage sustained ie: DMG_CRUSH
BOOL EXT_FUNC CBreakable::__API_HOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, FloatRef flDamage, int bitsDamageType)
{
	Vector vecTemp;

	// if Attacker == Inflictor, the attack was a melee or other instant-hit attack.
	// (that is, no actual entity projectile was involved in the attack so use the shooter's origin).
	if (pevAttacker == pevInflictor)
	{
		vecTemp = pevInflictor->origin - (pev->absmin + (pev->size * 0.5f));

		// if a client hit the breakable with a crowbar, and breakable is crowbar-sensitive, break it now.
		if ((pevAttacker->flags & FL_CLIENT) && (pev->spawnflags & SF_BREAK_CROWBAR) && (bitsDamageType & DMG_CLUB))
		{
			flDamage = pev->health;
		}
	}
	else
	{
		// an actual missile was involved.
		vecTemp = pevInflictor->origin - (pev->absmin + (pev->size * 0.5f));
	}

	if (!IsBreakable())
		return FALSE;

	// Breakables take double damage from the crowbar
	if (bitsDamageType & DMG_CLUB)
	{
		flDamage *= 2.0f;
	}

	// Boxes / glass / etc. don't take much poison damage, just the impact of the dart - consider that 10%
	if (bitsDamageType & DMG_POISON)
	{
		flDamage *= 0.1f;
	}

	// this global is still used for glass and other non-monster killables, along with decals.
	g_vecAttackDir = vecTemp.Normalize();

	// do the damage
	pev->health -= flDamage;

	if (pev->health <= 0)
	{
#ifndef REGAMEDLL_FIXES
		pev->takedamage = DAMAGE_NO;
		pev->deadflag = DEAD_DEAD;
		pev->effects = EF_NODRAW;
#endif
		Die();

		if (m_flDelay == 0.0f)
		{
			m_flDelay = 0.1f;
		}

		pev->nextthink = pev->ltime + m_flDelay;
		return FALSE;
	}

	// Make a shard noise each time func breakable is hit.
	// Don't play shard noise if cbreakable actually died.
	DamageSound();
	return TRUE;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBreakable, Die)

void EXT_FUNC CBreakable::__API_HOOK(Die)()
{
	Vector vecSpot;	// shard origin
	Vector vecVelocity;	// shard velocity
	CBaseEntity *pEntity = nullptr;
	char cFlag = 0;
	int pitch;
	float fvol;

#ifdef REGAMEDLL_FIXES
	pev->takedamage = DAMAGE_NO;
	pev->deadflag = DEAD_DEAD;
	pev->effects = EF_NODRAW;
#endif

	pitch = 95 + RANDOM_LONG(0, 29);

	if (pitch > 97 && pitch < 103)
		pitch = 100;

	// The more negative pev->health, the louder
	// the sound should be.

#ifdef REGAMEDLL_FIXES
	fvol = RANDOM_FLOAT(0.85f, 1.0f) + (Q_abs(pev->health) / 100.0f);
#else
	fvol = RANDOM_FLOAT(0.85f, 1.0f) + (Q_abs(int(pev->health)) / 100.0f);
#endif

	if (fvol > 1.0f)
		fvol = 1.0f;

	switch (m_Material)
	{
	case matGlass:
		switch (RANDOM_LONG(0, 1))
		{
		case 0:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustglass1.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		case 1:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustglass2.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		}
		cFlag = BREAK_GLASS;

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_BREAK_GLASS, this);
		}
		break;
	case matWood:
		switch (RANDOM_LONG(0, 1))
		{
		case 0:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustcrate1.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		case 1:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustcrate2.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		}
		cFlag = BREAK_WOOD;

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_BREAK_WOOD, this);
		}
		break;

	case matMetal:
	case matComputer:
		switch (RANDOM_LONG(0, 1))
		{
		case 0:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustmetal1.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		case 1:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustmetal2.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		}
		cFlag = BREAK_METAL;

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_BREAK_METAL, this);
		}
		break;

	case matFlesh:
		switch (RANDOM_LONG(0, 1))
		{
		case 0:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustflesh1.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		case 1:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustflesh2.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		}
		cFlag = BREAK_FLESH;

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_BREAK_FLESH, this);
		}
		break;

	case matCinderBlock:
	case matRocks:
		switch (RANDOM_LONG(0, 1))
		{
		case 0:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustconcrete1.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		case 1:	EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustconcrete2.wav", fvol, ATTN_NORM, 0, pitch);
			break;
		}
		cFlag = BREAK_CONCRETE;

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_BREAK_CONCRETE, this);
		}
		break;

	case matCeilingTile:
		EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "debris/bustceiling.wav", fvol, ATTN_NORM, 0, pitch);
		break;
	}

	if (m_Explosion == expDirected)
	{
		vecVelocity = g_vecAttackDir * 200.0f;
	}
	else
	{
		vecVelocity.x = 0;
		vecVelocity.y = 0;
		vecVelocity.z = 0;
	}

	vecSpot = pev->origin + (pev->mins + pev->maxs) * 0.5f;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecSpot);
		WRITE_BYTE(TE_BREAKMODEL);
		WRITE_COORD(vecSpot.x);		// position
		WRITE_COORD(vecSpot.y);
		WRITE_COORD(vecSpot.z);
		WRITE_COORD(pev->size.x);	// size
		WRITE_COORD(pev->size.y);
		WRITE_COORD(pev->size.z);
		WRITE_COORD(vecVelocity.x);	// velocity
		WRITE_COORD(vecVelocity.y);
		WRITE_COORD(vecVelocity.z);
		WRITE_BYTE(10);				// randomization
		WRITE_SHORT(m_idShard);		// model id#
		WRITE_BYTE(0);				// # of shards, let client decide
		WRITE_BYTE(25);				// duration, 2.5 seconds
		WRITE_BYTE(cFlag);			// flags
	MESSAGE_END();

	float size = pev->size.x;

	if (size < pev->size.y)
		size = pev->size.y;

	if (size < pev->size.z)
		size = pev->size.z;

	Vector mins = pev->absmin;
	Vector maxs = pev->absmax;
	mins.z = pev->absmax.z;
	maxs.z += 8;

	CBaseEntity *pList[256];
	int count = UTIL_EntitiesInBox(pList, ARRAYSIZE(pList), mins, maxs, FL_ONGROUND);

	for (int i = 0; i < count; i++)
	{
		pList[i]->pev->flags &= ~FL_ONGROUND;
		pList[i]->pev->groundentity = nullptr;
	}

	pev->solid = SOLID_NOT;
	SUB_UseTargets(nullptr, USE_TOGGLE, 0);
	SetThink(nullptr);

	pev->nextthink = pev->ltime + 0.1f;

	if (m_iszSpawnObject)
	{
		// TODO: Implement a list of entities to remove them on restart round
		auto pItem = CBaseEntity::Create((char *)STRING(m_iszSpawnObject), VecBModelOrigin(pev), pev->angles, edict());

#ifdef REGAMEDLL_FIXES
		if (pItem)
		{
			pItem->pev->spawnflags |= SF_NORESPAWN;
		}
#endif

	}

	if (Explodable())
	{
		ExplosionCreate(Center(), pev->angles, edict(), ExplosionMagnitude(), TRUE);
	}
}

BOOL CBreakable::IsBreakable()
{
	return m_Material != matUnbreakableGlass;
}

int CBreakable::DamageDecal(int bitsDamageType)
{
	if (m_Material == matGlass)
		return DECAL_GLASSBREAK1 + RANDOM_LONG(0, 2);

	if (m_Material == matUnbreakableGlass)
		return DECAL_BPROOF1;

	return CBaseEntity::DamageDecal(bitsDamageType);
}

TYPEDESCRIPTION CPushable::m_SaveData[] =
{
	DEFINE_FIELD(CPushable, m_maxSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CPushable, m_soundTime, FIELD_TIME),
};

const char *CPushable::m_soundNames[] =
{
	"debris/pushbox1.wav",
	"debris/pushbox2.wav",
	"debris/pushbox3.wav"
};

LINK_ENTITY_TO_CLASS(func_pushable, CPushable, CCSPushable)
IMPLEMENT_SAVERESTORE(CPushable, CBreakable)

void CPushable::Spawn()
{
	if (pev->spawnflags & SF_PUSH_BREAKABLE)
		CBreakable::Spawn();
	else
		Precache();

	pev->movetype = MOVETYPE_PUSHSTEP;
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->friction > 399)
	{
		pev->friction = 399;
	}

	m_maxSpeed = 400 - pev->friction;

	pev->flags |= FL_FLOAT;
	pev->friction = 0;

	// Pick up off of the floor
	pev->origin.z += 1;
	UTIL_SetOrigin(pev, pev->origin);

#ifdef REGAMEDLL_FIXES
	pev->oldorigin = pev->origin;
#endif

	// Multiply by area of the box's cross-section (assume 1000 units^3 standard volume)
	pev->skin = int((pev->skin * (pev->maxs.x - pev->mins.x) * (pev->maxs.y - pev->mins.y)) * 0.0005);
	m_soundTime = 0;
}

void CPushable::Precache()
{
	for (int i = 0; i < ARRAYSIZE(m_soundNames); i++)
	{
		PRECACHE_SOUND(m_soundNames[i]);
	}

	if (pev->spawnflags & SF_PUSH_BREAKABLE)
	{
		CBreakable::Precache();
	}
}

#ifdef REGAMEDLL_FIXES
void CPushable::Restart()
{
	if (pev->spawnflags & SF_PUSH_BREAKABLE)
		CBreakable::Restart();

	pev->movetype = MOVETYPE_PUSHSTEP;
	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->friction > 399)
		pev->friction = 399;

	m_soundTime = 0;
	m_maxSpeed = 400 - pev->friction;

	pev->flags |= FL_FLOAT;
	pev->friction = 0;

	UTIL_SetOrigin(pev, pev->oldorigin);
}
#endif

void CPushable::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "size"))
	{
		int bbox = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;

		switch (bbox)
		{
		case 0: // Point
			UTIL_SetSize(pev, Vector(-8, -8, -8), Vector(8, 8, 8));
			break;

		case 2: // TODO: Big Hull? BUGBUG: Figure out what this hull really is
			UTIL_SetSize(pev, VEC_DUCK_HULL_MIN * 2, VEC_DUCK_HULL_MAX * 2);
			break;

		case 3: // Player duck
			UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
			break;

		default:
		case 1: // Player
			UTIL_SetSize(pev, VEC_HULL_MIN, VEC_HULL_MAX);
			break;
		}
	}
	else if (FStrEq(pkvd->szKeyName, "buoyancy"))
	{
		pev->skin = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBreakable::KeyValue(pkvd);
	}
}

// Pull the func_pushable
void CPushable::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!pActivator || !pActivator->IsPlayer())
	{
		if (pev->spawnflags & SF_PUSH_BREAKABLE)
		{
			this->CBreakable::Use(pActivator, pCaller, useType, value);
		}

		return;
	}

	if (pActivator->pev->velocity != g_vecZero)
	{
		Move(pActivator, 0);
	}
}

void CPushable::Touch(CBaseEntity *pOther)
{
	if (FClassnameIs(pOther->pev, "worldspawn"))
		return;

	Move(pOther, 1);
}

void CPushable::Move(CBaseEntity *pOther, int push)
{
	entvars_t *pevToucher = pOther->pev;
	bool bPlayerTouch = false;

	// Is entity standing on this pushable ?
	if ((pevToucher->flags & FL_ONGROUND) && pevToucher->groundentity && VARS(pevToucher->groundentity) == pev)
	{
		// Only push if floating
		if (pev->waterlevel > 0)
		{
			pev->velocity.z += pevToucher->velocity.z * 0.1f;
		}

		return;
	}

	if (pOther->IsPlayer())
	{
		// Don't push unless the player is pushing forward and NOT use (pull)
		if (push && !(pevToucher->button & (IN_FORWARD | IN_USE)))
		{
			return;
		}

		bPlayerTouch = true;
	}

	real_t factor;

	if (bPlayerTouch)
	{
		// Don't push away from jumping/falling players unless in water
		if (!(pevToucher->flags & FL_ONGROUND))
		{
			if (pev->waterlevel < 1)
				return;
			else
				factor = 0.1f;
		}
		else
			factor = 1.0f;
	}
	else
	{
		factor = 0.25f;
	}

	pev->velocity.x += pevToucher->velocity.x * factor;
	pev->velocity.y += pevToucher->velocity.y * factor;

	real_t length = Q_sqrt(pev->velocity.x * pev->velocity.x + pev->velocity.y * pev->velocity.y);

	if (push && (length > MaxSpeed()))
	{
		pev->velocity.x = (pev->velocity.x * MaxSpeed() / length);
		pev->velocity.y = (pev->velocity.y * MaxSpeed() / length);
	}

	if (bPlayerTouch)
	{
// do not push player along with entity
#ifndef REGAMEDLL_FIXES
		pevToucher->velocity.x = pev->velocity.x;
		pevToucher->velocity.y = pev->velocity.y;
#endif // REGAMEDLL_FIXES

		if ((gpGlobals->time - m_soundTime) > 0.7f)
		{
			m_soundTime = gpGlobals->time;

			if (length > 0 && (pev->flags & FL_ONGROUND))
			{
				m_lastSound = RANDOM_LONG(0, 2);
				EMIT_SOUND(ENT(pev), CHAN_WEAPON, m_soundNames[m_lastSound], 0.5, ATTN_NORM);

				//SetThink(StopSound);
				//pev->nextthink = pev->ltime + 0.1f;
			}
			else
				STOP_SOUND(ENT(pev), CHAN_WEAPON, m_soundNames[m_lastSound]);
		}
	}
}

BOOL CPushable::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	if (pev->spawnflags & SF_PUSH_BREAKABLE)
	{
		return CBreakable::TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType);
	}

	return TRUE;
}
