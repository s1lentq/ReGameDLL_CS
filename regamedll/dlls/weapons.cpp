#include "precompiled.h"

short g_sModelIndexLaser;		// holds the index for the laser beam
short g_sModelIndexLaserDot;	// holds the index for the laser beam dot
short g_sModelIndexFireball;	// holds the index for the fireball
short g_sModelIndexSmoke;		// holds the index for the smoke cloud
short g_sModelIndexWExplosion;	// holds the index for the underwater explosion
short g_sModelIndexBubbles;		// holds the index for the bubbles model
short g_sModelIndexBloodDrop;	// holds the sprite index for the initial blood
short g_sModelIndexBloodSpray;	// holds the sprite index for splattered blood
short g_sModelIndexSmokePuff;
short g_sModelIndexFireball2;
short g_sModelIndexFireball3;
short g_sModelIndexFireball4;
short g_sModelIndexRadio;

short int g_sModelIndexCTGhost;
short int g_sModelIndexTGhost;
short int g_sModelIndexC4Glow;

int giAmmoIndex;

MULTIDAMAGE gMultiDamage;

// Pass in a name and this function will tell
// you the maximum amount of that type of ammunition that a player can carry.
int MaxAmmoCarry(const char *szName)
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		ItemInfo *info = &CBasePlayerItem::m_ItemInfoArray[i];
		if (info->pszAmmo1 && !Q_stricmp(szName, info->pszAmmo1))
		{
			return info->iMaxAmmo1;
		}

		if (info->pszAmmo2 && !Q_stricmp(szName, info->pszAmmo2))
		{
			return info->iMaxAmmo2;
		}
	}

	ALERT(at_console, "MaxAmmoCarry() doesn't recognize '%s'!\n", szName);
	return -1;
}

int MaxAmmoCarry(WeaponIdType weaponId)
{
	return CBasePlayerItem::m_ItemInfoArray[weaponId].iMaxAmmo1;
}

// All automatic weapons are represented here
float GetBaseAccuracy(WeaponIdType id)
{
	switch (id)
	{
	case WEAPON_M4A1:
	case WEAPON_AK47:
	case WEAPON_AUG:
	case WEAPON_SG552:
	case WEAPON_FAMAS:
	case WEAPON_GALIL:
	case WEAPON_M249:
	case WEAPON_P90:
	case WEAPON_TMP:
		return 0.2f;
	case WEAPON_MAC10:
		return 0.15f;
	case WEAPON_UMP45:
	case WEAPON_MP5N:
		return 0.0f;
	}

	return 0.0f;
}

LINK_HOOK_VOID_CHAIN2(ClearMultiDamage)

// Resets the global multi damage accumulator
void EXT_FUNC __API_HOOK(ClearMultiDamage)()
{
	gMultiDamage.hEntity = nullptr;
	gMultiDamage.amount = 0;
	gMultiDamage.type = 0;
}

LINK_HOOK_VOID_CHAIN(ApplyMultiDamage, (entvars_t *pevInflictor, entvars_t *pevAttacker), pevInflictor, pevAttacker)

// Inflicts contents of global multi damage register on gMultiDamage.pEntity
void EXT_FUNC __API_HOOK(ApplyMultiDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker)
{
	EntityHandle<CBaseEntity> hEnt = gMultiDamage.hEntity;
	if (!hEnt)
		return;

	hEnt->TakeDamage(pevInflictor, pevAttacker, gMultiDamage.amount, gMultiDamage.type);

	// check again, the entity may be removed after taking damage
	if (hEnt)
		hEnt->ResetDmgPenetrationLevel();
}

LINK_HOOK_VOID_CHAIN(AddMultiDamage, (entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType), pevInflictor, pEntity, flDamage, bitsDamageType)

void EXT_FUNC __API_HOOK(AddMultiDamage)(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType)
{
	if (!pEntity)
		return;

	gMultiDamage.type |= bitsDamageType;

	if (pEntity != gMultiDamage.hEntity)
	{
#ifdef REGAMEDLL_FIXES
		if (gMultiDamage.hEntity) // avoid api calls with null default pEntity
#endif
		{
			// UNDONE: wrong attacker!
			ApplyMultiDamage(pevInflictor, pevInflictor);
		}

		gMultiDamage.hEntity = pEntity;
		gMultiDamage.amount = 0;
	}

	gMultiDamage.amount += flDamage;
}

void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage)
{
	UTIL_BloodDrips(vecSpot, bloodColor, int(flDamage));
}

NOXREF int DamageDecal(CBaseEntity *pEntity, int bitsDamageType)
{
	if (pEntity)
	{
		return pEntity->DamageDecal(bitsDamageType);
	}

	return RANDOM_LONG(DECAL_GUNSHOT4, DECAL_GUNSHOT5);
}

void DecalGunshot(TraceResult *pTrace, int iBulletType, bool ClientOnly, entvars_t *pShooter, bool bHitMetal)
{
	;
}

// EjectBrass - tosses a brass shell from passed origin at passed velocity
void EjectBrass(const Vector &vecOrigin, const Vector &vecLeft, const Vector &vecVelocity, float rotation, int model, int soundtype, int entityIndex)
{
	bool useNewBehavior = AreRunningCZero();

	MESSAGE_BEGIN(MSG_PVS, gmsgBrass, vecOrigin);
		if (!useNewBehavior)
		{
			// noxref
			WRITE_BYTE(TE_MODEL);
		}
		WRITE_COORD(vecOrigin.x);	// origin
		WRITE_COORD(vecOrigin.y);
		WRITE_COORD(vecOrigin.z);
		if (!useNewBehavior)
		{
			// noxref
			// it parses the client side, but does not use it
			WRITE_COORD(vecLeft.x);
			WRITE_COORD(vecLeft.y);
			WRITE_COORD(vecLeft.z);
		}
		WRITE_COORD(vecVelocity.x);	// velocity
		WRITE_COORD(vecVelocity.y);
		WRITE_COORD(vecVelocity.z);
		WRITE_ANGLE(rotation);
		WRITE_SHORT(model);
		WRITE_BYTE(soundtype);
		if (!useNewBehavior)
		{
			// noxref
			WRITE_BYTE(25);// 2.5 seconds
		}
		WRITE_BYTE(entityIndex);
	MESSAGE_END();
}

NOXREF void EjectBrass2(const Vector &vecOrigin, const Vector &vecVelocity, float rotation, int model, int soundtype, entvars_t *pev)
{
	MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, nullptr, pev);
		WRITE_BYTE(TE_MODEL);
		WRITE_COORD(vecOrigin.x);
		WRITE_COORD(vecOrigin.y);
		WRITE_COORD(vecOrigin.z);
		WRITE_COORD(vecVelocity.x);
		WRITE_COORD(vecVelocity.y);
		WRITE_COORD(vecVelocity.z);
		WRITE_ANGLE(rotation);
		WRITE_SHORT(model);
		WRITE_BYTE(0);
		WRITE_BYTE(5);// 0.5 seconds
	MESSAGE_END();
}

#ifdef REGAMEDLL_ADD
struct {
	AmmoType type;
	const char *name;
} ammoIndex[] =
{
	{ AMMO_338MAGNUM,    "338Magnum" },
	{ AMMO_762NATO,      "762Nato" },
	{ AMMO_556NATOBOX,   "556NatoBox" },
	{ AMMO_556NATO,      "556Nato" },
	{ AMMO_BUCKSHOT,     "buckshot" },
	{ AMMO_45ACP,        "45acp" },
	{ AMMO_57MM,         "57mm" },
	{ AMMO_50AE,         "50AE" },
	{ AMMO_357SIG,       "357SIG" },
	{ AMMO_9MM,          "9mm" },
	{ AMMO_FLASHBANG,    "Flashbang" },
	{ AMMO_HEGRENADE,    "HEGrenade" },
	{ AMMO_SMOKEGRENADE, "SmokeGrenade" },
	{ AMMO_C4,           "C4" },
};
#endif

// Precaches the ammo and queues the ammo info for sending to clients
int AddAmmoNameToAmmoRegistry(const char *szAmmoname)
{
	// string validation
	if (!szAmmoname || !szAmmoname[0])
	{
		return -1;
	}

	// make sure it's not already in the registry
	for (int i = 1; i < MAX_AMMO_SLOTS; i++)
	{
		if (!CBasePlayerItem::m_AmmoInfoArray[i].pszName)
			continue;

		if (!Q_stricmp(CBasePlayerItem::m_AmmoInfoArray[i].pszName, szAmmoname))
		{
			// ammo already in registry, just quite
			return i;
		}
	}

	giAmmoIndex++;
	DbgAssert(giAmmoIndex < MAX_AMMO_SLOTS);

	if (giAmmoIndex >= MAX_AMMO_SLOTS)
		giAmmoIndex = 1;

#ifdef REGAMEDLL_ADD
	for (auto& ammo : ammoIndex)
	{
		if (Q_stricmp(ammo.name, szAmmoname))
			continue;

		if (ammo.type != giAmmoIndex) {
			CONSOLE_ECHO("Warning: ammo '%s' index mismatch; expected %i, real %i\n", szAmmoname, ammo.type, giAmmoIndex);
		}
		break;
	}
#endif

	CBasePlayerItem::m_AmmoInfoArray[giAmmoIndex].pszName = szAmmoname;

	// Yes, this info is redundant
	CBasePlayerItem::m_AmmoInfoArray[giAmmoIndex].iId = giAmmoIndex;

	return giAmmoIndex;
}

// Precaches the weapon and queues the weapon info for sending to clients
void UTIL_PrecacheOtherWeapon(const char *szClassname)
{
	edict_t *pEdict = CREATE_NAMED_ENTITY(MAKE_STRING(szClassname));
	if (FNullEnt(pEdict))
	{
		ALERT(at_console, "NULL Ent in UTIL_PrecacheOtherWeapon classname `%s`\n", szClassname);
		return;
	}

	CBasePlayerItem *pItem = GET_PRIVATE<CBasePlayerItem>(pEdict);
	if (pItem)
	{
		ItemInfo info;
		Q_memset(&info, 0, sizeof(info));

		pItem->Precache();
		if (pItem->GetItemInfo(&info))
		{
			CBasePlayerItem::m_ItemInfoArray[info.iId] = info;

			AddAmmoNameToAmmoRegistry(info.pszAmmo1);
			AddAmmoNameToAmmoRegistry(info.pszAmmo2);
		}
	}

	REMOVE_ENTITY(pEdict);
}

// Called by worldspawn
void WeaponsPrecache()
{
	Q_memset(CBasePlayerItem::m_ItemInfoArray, 0, sizeof(CBasePlayerItem::m_ItemInfoArray));
	Q_memset(CBasePlayerItem::m_AmmoInfoArray, 0, sizeof(CBasePlayerItem::m_AmmoInfoArray));

	giAmmoIndex = 0;

	// custom items...

	// common world objects
	UTIL_PrecacheOther("item_suit");
	UTIL_PrecacheOther("item_battery");
	UTIL_PrecacheOther("item_antidote");
	UTIL_PrecacheOther("item_security");
	UTIL_PrecacheOther("item_longjump");
	UTIL_PrecacheOther("item_kevlar");
	UTIL_PrecacheOther("item_assaultsuit");
	UTIL_PrecacheOther("item_thighpack");

	// awp magnum
	UTIL_PrecacheOtherWeapon("weapon_awp");
	UTIL_PrecacheOther("ammo_338magnum");

	UTIL_PrecacheOtherWeapon("weapon_g3sg1");
	UTIL_PrecacheOtherWeapon("weapon_ak47");
	UTIL_PrecacheOtherWeapon("weapon_scout");
	UTIL_PrecacheOther("ammo_762nato");

	// m249
	UTIL_PrecacheOtherWeapon("weapon_m249");
	UTIL_PrecacheOther("ammo_556natobox");

	UTIL_PrecacheOtherWeapon("weapon_m4a1");
	UTIL_PrecacheOtherWeapon("weapon_sg552");
	UTIL_PrecacheOtherWeapon("weapon_aug");
	UTIL_PrecacheOtherWeapon("weapon_sg550");
	UTIL_PrecacheOther("ammo_556nato");

	// shotgun
	UTIL_PrecacheOtherWeapon("weapon_m3");
	UTIL_PrecacheOtherWeapon("weapon_xm1014");
	UTIL_PrecacheOther("ammo_buckshot");

	UTIL_PrecacheOtherWeapon("weapon_usp");
	UTIL_PrecacheOtherWeapon("weapon_mac10");
	UTIL_PrecacheOtherWeapon("weapon_ump45");
	UTIL_PrecacheOther("ammo_45acp");

	UTIL_PrecacheOtherWeapon("weapon_fiveseven");
	UTIL_PrecacheOtherWeapon("weapon_p90");
	UTIL_PrecacheOther("ammo_57mm");

	// deagle
	UTIL_PrecacheOtherWeapon("weapon_deagle");
	UTIL_PrecacheOther("ammo_50ae");

	// p228
	UTIL_PrecacheOtherWeapon("weapon_p228");
	UTIL_PrecacheOther("ammo_357sig");

	// knife
	UTIL_PrecacheOtherWeapon("weapon_knife");

	UTIL_PrecacheOtherWeapon("weapon_glock18");
	UTIL_PrecacheOtherWeapon("weapon_mp5navy");
	UTIL_PrecacheOtherWeapon("weapon_tmp");
	UTIL_PrecacheOtherWeapon("weapon_elite");
	UTIL_PrecacheOther("ammo_9mm");

	UTIL_PrecacheOtherWeapon("weapon_flashbang");
	UTIL_PrecacheOtherWeapon("weapon_hegrenade");
	UTIL_PrecacheOtherWeapon("weapon_smokegrenade");
	UTIL_PrecacheOtherWeapon("weapon_c4");
	UTIL_PrecacheOtherWeapon("weapon_galil");
	UTIL_PrecacheOtherWeapon("weapon_famas");

	if (g_pGameRules->IsDeathmatch())
	{
		// container for dropped deathmatch weapons
		UTIL_PrecacheOther("weaponbox");
	}

	g_sModelIndexFireball   = PRECACHE_MODEL("sprites/zerogxplode.spr");	// fireball
	g_sModelIndexWExplosion = PRECACHE_MODEL("sprites/WXplo1.spr");			// underwater fireball
	g_sModelIndexSmoke      = PRECACHE_MODEL("sprites/steam1.spr");			// smoke
	g_sModelIndexBubbles    = PRECACHE_MODEL("sprites/bubble.spr");			// bubbles
	g_sModelIndexBloodSpray = PRECACHE_MODEL("sprites/bloodspray.spr");		// initial blood
	g_sModelIndexBloodDrop  = PRECACHE_MODEL("sprites/blood.spr");			// splattered blood

	g_sModelIndexSmokePuff  = PRECACHE_MODEL("sprites/smokepuff.spr");
	g_sModelIndexFireball2  = PRECACHE_MODEL("sprites/eexplo.spr");
	g_sModelIndexFireball3  = PRECACHE_MODEL("sprites/fexplo.spr");
	g_sModelIndexFireball4  = PRECACHE_MODEL("sprites/fexplo1.spr");
	g_sModelIndexRadio      = PRECACHE_MODEL("sprites/radio.spr");

	g_sModelIndexCTGhost    = PRECACHE_MODEL("sprites/b-tele1.spr");
	g_sModelIndexTGhost     = PRECACHE_MODEL("sprites/c-tele1.spr");
	g_sModelIndexC4Glow     = PRECACHE_MODEL("sprites/ledglow.spr");

	g_sModelIndexLaser      = PRECACHE_MODEL("sprites/laserbeam.spr");
	g_sModelIndexLaserDot   = PRECACHE_MODEL("sprites/laserdot.spr");

	// used by explosions
	PRECACHE_MODEL("models/grenade.mdl");
	PRECACHE_MODEL("sprites/explode1.spr");

	PRECACHE_SOUND("weapons/debris1.wav"); // explosion aftermaths
	PRECACHE_SOUND("weapons/debris2.wav"); // explosion aftermaths
	PRECACHE_SOUND("weapons/debris3.wav"); // explosion aftermaths

	PRECACHE_SOUND("weapons/grenade_hit1.wav");	// grenade
	PRECACHE_SOUND("weapons/grenade_hit2.wav");	// grenade
	PRECACHE_SOUND("weapons/grenade_hit3.wav");	// grenade

	PRECACHE_SOUND("weapons/bullet_hit1.wav");	// hit by bullet
	PRECACHE_SOUND("weapons/bullet_hit2.wav");	// hit by bullet

	PRECACHE_SOUND("items/weapondrop1.wav");	// weapon falls to the ground
	PRECACHE_SOUND("weapons/generic_reload.wav");
}

ItemInfo CBasePlayerItem::m_ItemInfoArray[MAX_WEAPONS];
AmmoInfo CBasePlayerItem::m_AmmoInfoArray[MAX_AMMO_SLOTS];

TYPEDESCRIPTION CBasePlayerItem::m_SaveData[] =
{
	DEFINE_FIELD(CBasePlayerItem, m_pPlayer, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayerItem, m_pNext, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayerItem, m_iId, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CBasePlayerItem, CBaseAnimating)

TYPEDESCRIPTION CBasePlayerWeapon::m_SaveData[] =
{
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextPrimaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextSecondaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flTimeWeaponIdle, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_iPrimaryAmmoType, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerWeapon, m_iSecondaryAmmoType, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerWeapon, m_iClip, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerWeapon, m_iDefaultAmmo, FIELD_INTEGER),
};

IMPLEMENT_SAVERESTORE(CBasePlayerWeapon, CBasePlayerItem)

void CBasePlayerItem::SetObjectCollisionBox()
{
	pev->absmin = pev->origin + Vector(-24, -24, 0);
	pev->absmax = pev->origin + Vector(24, 24, 16);
}

// Sets up movetype, size, solidtype for a new weapon.
void CBasePlayerItem::FallInit()
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_BBOX;

	UTIL_SetOrigin(pev, pev->origin);

	// pointsize until it lands on the ground.
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	SetTouch(&CBasePlayerItem::DefaultTouch);
	SetThink(&CBasePlayerItem::FallThink);

	pev->nextthink = gpGlobals->time + 0.1f;
}

// FallThink - Items that have just spawned run this think
// to catch them when they hit the ground. Once we're sure
// that the object is grounded, we change its solid type
// to trigger and set it in a large box that helps the
// player get it.
void CBasePlayerItem::FallThink()
{
	pev->nextthink = gpGlobals->time + 0.1f;

	if (pev->flags & FL_ONGROUND)
	{
		// clatter if we have an owner (i.e., dropped by someone)
		// don't clatter if the gun is waiting to respawn (if it's waiting, it is invisible!)
		if (!FNullEnt(pev->owner))
		{
			EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "items/weapondrop1.wav", VOL_NORM, ATTN_NORM, 0, RANDOM_LONG(0, 29) + 95);
		}

		// lie flat
		pev->angles.x = 0.0f;
		pev->angles.z = 0.0f;

		Materialize();
	}
}

// Materialize - make a CBasePlayerItem visible and tangible
void CBasePlayerItem::Materialize()
{
	if (pev->effects & EF_NODRAW)
	{
		// changing from invisible state to visible.
		if (g_pGameRules->IsMultiplayer())
		{
			EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, "items/suitchargeok1.wav", VOL_NORM, ATTN_NORM, 0, 150);
		}

		pev->effects &= ~EF_NODRAW;
		pev->effects |= EF_MUZZLEFLASH;
	}

	pev->solid = SOLID_TRIGGER;

	// link into world.
	UTIL_SetOrigin(pev, pev->origin);
	SetTouch(&CBasePlayerItem::DefaultTouch);

	if (g_pGameRules->IsMultiplayer()
#ifdef REGAMEDLL_FIXES
		&& g_pGameRules->WeaponShouldRespawn(this) == GR_WEAPON_RESPAWN_NO
#endif
	)
	{
		if (!CanDrop())
		{
			SetTouch(nullptr);
		}

		SetThink(&CBaseEntity::SUB_Remove);
		pev->nextthink = gpGlobals->time + 1.0f;
	}
	else
	{
		SetThink(nullptr);
	}
}

// AttemptToMaterialize - the item is trying to rematerialize,
// should it do so now or wait longer?
void CBasePlayerItem::AttemptToMaterialize()
{
	float time = g_pGameRules->FlWeaponTryRespawn(this);

	if (time == 0)
	{
		Materialize();
		return;
	}

	pev->nextthink = gpGlobals->time + time;
}

// CheckRespawn - a player is taking this weapon, should
// it respawn?
void CBasePlayerItem::CheckRespawn()
{
	switch (g_pGameRules->WeaponShouldRespawn(this))
	{
		case GR_WEAPON_RESPAWN_YES: {
#ifdef REGAMEDLL_FIXES
			Respawn();
#endif
			return;
		}
		case GR_WEAPON_RESPAWN_NO:
			return;
	}
}

// Respawn - this item is already in the world, but it is
// invisible and intangible. Make it visible and tangible.
CBaseEntity *CBasePlayerItem::Respawn()
{
	// make a copy of this weapon that is invisible and inaccessible to players (no touch function). The weapon spawn/respawn code
	// will decide when to make the weapon visible and touchable.
	CBaseEntity *pNewWeapon = CBaseEntity::Create(pev->classname, g_pGameRules->VecWeaponRespawnSpot(this), pev->angles, pev->owner);

	if (pNewWeapon)
	{
		// invisible for now
		pNewWeapon->pev->effects |= EF_NODRAW;

#ifdef REGAMEDLL_ADD
		pNewWeapon->pev->spawnflags &= ~SF_NORESPAWN;
#endif

		// no touch
		pNewWeapon->SetTouch(nullptr);
		pNewWeapon->SetThink(&CBasePlayerItem::AttemptToMaterialize);

		DROP_TO_FLOOR(ENT(pev));

		// not a typo! We want to know when the weapon the player just picked up should respawn! This new entity we created is the replacement,
		// but when it should respawn is based on conditions belonging to the weapon that was taken.
		pNewWeapon->pev->nextthink = g_pGameRules->FlWeaponRespawnTime(this);
	}
	else
	{
		ALERT(at_console, "Respawn failed to create %s!\n", STRING(pev->classname));
	}

	return pNewWeapon;
}

// whats going on here is that if the player drops this weapon, they shouldn't take it back themselves
// for a little while. But if they throw it at someone else, the other player should get it immediately.
void CBasePlayerItem::DefaultTouch(CBaseEntity *pOther)
{
	// if it's not a player, ignore
	if (!pOther->IsPlayer())
	{
		return;
	}

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pOther);

	if (pPlayer->m_bIsVIP
		&& m_iId != WEAPON_USP
		&& m_iId != WEAPON_GLOCK18
		&& m_iId != WEAPON_P228
		&& m_iId != WEAPON_DEAGLE
		&& m_iId != WEAPON_KNIFE)
	{
		return;
	}

	// can I have this?
	if (!g_pGameRules->CanHavePlayerItem(pPlayer, this))
	{
		return;
	}

	if (pOther->AddPlayerItem(this))
	{
		AttachToPlayer(pPlayer);
#ifndef REGAMEDLL_FIXES
		SetThink(nullptr);
#endif
		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);
	}

	SUB_UseTargets(pOther, USE_TOGGLE, 0);
}

void CBasePlayerWeapon::SetPlayerShieldAnim()
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shield");
	}
	else
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgun");
	}
}

void CBasePlayerWeapon::ResetPlayerShieldAnim()
{
	if (m_pPlayer->HasShield())
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		{
			Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgun");
		}
	}
}

void CBasePlayerWeapon::EjectBrassLate()
{
	int soundType;
	Vector vecUp, vecRight, vecShellVelocity;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	vecUp = RANDOM_FLOAT(100, 150) * gpGlobals->v_up;
	vecRight = RANDOM_FLOAT(50, 70) * gpGlobals->v_right;

	vecShellVelocity = (m_pPlayer->pev->velocity + vecRight + vecUp) + gpGlobals->v_forward * 25;
	soundType = (m_iId == WEAPON_XM1014 || m_iId == WEAPON_M3) ? 2 : 1;

	EjectBrass(pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_up * -9 + gpGlobals->v_forward * 16, gpGlobals->v_right * -9,
		vecShellVelocity, pev->angles.y, m_iShellId, soundType, m_pPlayer->entindex());
}

bool CBasePlayerWeapon::ShieldSecondaryFire(int iUpAnim, int iDownAnim)
{
	if (!m_pPlayer->HasShield())
		return false;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iDownAnim, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgun");
		m_fMaxSpeed = 250.0f;
		m_pPlayer->m_bShieldDrawn = false;
	}
	else
	{
		m_iWeaponState |= WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iUpAnim, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shielded");
		m_fMaxSpeed = 180.0f;
		m_pPlayer->m_bShieldDrawn = true;
	}

	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) != WPNSTATE_SHIELD_DRAWN);
	m_pPlayer->ResetMaxSpeed();

	m_flNextSecondaryAttack = 0.4f;
	m_flNextPrimaryAttack = 0.4f;
	m_flTimeWeaponIdle = 0.6f;

	return true;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayerWeapon, KickBack, (float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change), up_base, lateral_base, up_modifier, lateral_modifier, up_max, lateral_max, direction_change)

void EXT_FUNC CBasePlayerWeapon::__API_HOOK(KickBack)(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change)
{
#ifdef REGAMEDLL_ADD
	real_t flKickUp = up_base;
	float flKickLateral = lateral_base;

	if (m_iShotsFired > 1) // consider == 0 case 
	{
		flKickUp += m_iShotsFired * up_modifier;
		flKickLateral += m_iShotsFired * lateral_modifier;
	}

	if (up_max == 0.0f) // boundaryless vertical kick
	{
		m_pPlayer->pev->punchangle.x -= flKickUp;
	}
	else if (m_pPlayer->pev->punchangle.x > -up_max) // do not kick when already out of boundaries
	{
		m_pPlayer->pev->punchangle.x = Q_max<real_t>(m_pPlayer->pev->punchangle.x - flKickUp, -up_max);
	}

	if (lateral_max == 0.0f) // boundaryless horizontal kick
	{
		m_pPlayer->pev->punchangle.y += flKickLateral * (m_iDirection * 2 - 1);
	}
	else if (Q_fabs(m_pPlayer->pev->punchangle.y) < lateral_max) // do not kick when already out of boundaries
	{
		m_pPlayer->pev->punchangle.y = (m_iDirection == 1) ?
			Q_min(m_pPlayer->pev->punchangle.y + flKickLateral, lateral_max) :
			Q_max(m_pPlayer->pev->punchangle.y - flKickLateral, -lateral_max);
	}

	if (direction_change > 0 && !RANDOM_LONG(0, direction_change)) // be sure to not waste RNG consumption
	{
		m_iDirection = !m_iDirection;
	}
#else
	real_t flKickUp;
	float flKickLateral;

	if (m_iShotsFired == 1)
	{
		flKickUp = up_base;
		flKickLateral = lateral_base;
	}
	else
	{
		flKickUp = m_iShotsFired * up_modifier + up_base;
		flKickLateral = m_iShotsFired * lateral_modifier + lateral_base;
	}

	m_pPlayer->pev->punchangle.x -= flKickUp;

	if (m_pPlayer->pev->punchangle.x < -up_max)
	{
		m_pPlayer->pev->punchangle.x = -up_max;
	}

	if (m_iDirection == 1)
	{
		m_pPlayer->pev->punchangle.y += flKickLateral;

		if (m_pPlayer->pev->punchangle.y > lateral_max)
			m_pPlayer->pev->punchangle.y = lateral_max;
	}
	else
	{
		m_pPlayer->pev->punchangle.y -= flKickLateral;

		if (m_pPlayer->pev->punchangle.y < -lateral_max)
			m_pPlayer->pev->punchangle.y = -lateral_max;
	}

	if (!RANDOM_LONG(0, direction_change))
	{
		m_iDirection = !m_iDirection;
	}
#endif
}

void CBasePlayerWeapon::FireRemaining(int &shotsFired, float &shootTime, BOOL bIsGlock)
{
	float nexttime = 0.1f;
	if (--m_iClip < 0)
	{
		m_iClip = 0;
		shotsFired = 3;
		shootTime = 0;
		return;
	}

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir;

	int flag;
#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = bIsGlock ? GLOCK18_DAMAGE : FAMAS_DAMAGE;
#endif

	if (bIsGlock)
	{
		vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, 0.05, 8192, 1, BULLET_PLAYER_9MM, flBaseDamage, 0.9, m_pPlayer->pev, true, m_pPlayer->random_seed);
#ifndef REGAMEDLL_FIXES
		--m_pPlayer->ammo_9mm;
#endif
		PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireGlock18, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
			int(m_pPlayer->pev->punchangle.x * 10000), int(m_pPlayer->pev->punchangle.y * 10000), m_iClip == 0, FALSE);
	}
	else
	{
		vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, m_fBurstSpread, 8192, 2, BULLET_PLAYER_556MM, flBaseDamage, 0.96, m_pPlayer->pev, false, m_pPlayer->random_seed);
#ifndef REGAMEDLL_FIXES
		--m_pPlayer->ammo_556nato;
#endif

#ifdef REGAMEDLL_ADD
		// HACKHACK: client-side weapon prediction fix
		if (!(iFlags() & ITEM_FLAG_NOFIREUNDERWATER) && m_pPlayer->pev->waterlevel == 3)
			flag = 0;
#endif

		PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireFamas, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
			int(m_pPlayer->pev->punchangle.x * 10000000), int(m_pPlayer->pev->punchangle.y * 10000000), FALSE, FALSE);
	}

	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	if (++shotsFired != 3)
	{
		shootTime = gpGlobals->time + nexttime;
	}
	else
		shootTime = 0;
}

BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted)
{
#ifdef CLIENT_WEAPONS
	if (!isPredicted)
#else
	if (1)
#endif
	{
		return (attack_time <= curtime) ? TRUE : FALSE;
	}
	else
	{
		return (attack_time <= 0.0f) ? TRUE : FALSE;
	}
}

bool CBasePlayerWeapon::HasSecondaryAttack()
{
#ifdef REGAMEDLL_API
	if (CSPlayerWeapon()->m_iStateSecondaryAttack != WEAPON_SECONDARY_ATTACK_NONE)
	{
		switch (CSPlayerWeapon()->m_iStateSecondaryAttack)
		{
			case WEAPON_SECONDARY_ATTACK_SET:
				return true;
			case WEAPON_SECONDARY_ATTACK_BLOCK:
				return false;
			default:
				break;
		}
	}
#endif

	if (m_pPlayer && m_pPlayer->HasShield())
	{
		return true;
	}

	switch (m_iId)
	{
	case WEAPON_AK47:
	case WEAPON_XM1014:
	case WEAPON_MAC10:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_MP5N:
#ifdef BUILD_LATEST_FIXES
	case WEAPON_UMP45:
#endif
	case WEAPON_M249:
	case WEAPON_M3:
	case WEAPON_TMP:
	case WEAPON_DEAGLE:
	case WEAPON_P228:
	case WEAPON_P90:
	case WEAPON_C4:
	case WEAPON_GALIL:
		return false;
	default:
		break;
	}

	return true;
}

void CBasePlayerWeapon::HandleInfiniteAmmo()
{
	int nInfiniteAmmo = 0;

#ifdef REGAMEDLL_API
	nInfiniteAmmo = m_pPlayer->CSPlayer()->m_iWeaponInfiniteAmmo;
#endif

	if (!nInfiniteAmmo)
		nInfiniteAmmo = static_cast<int>(infiniteAmmo.value);

	if (nInfiniteAmmo == WPNMODE_INFINITE_CLIP && !IsGrenadeWeapon(m_iId))
	{
		m_iClip = iMaxClip();
	}
	else if ((nInfiniteAmmo == WPNMODE_INFINITE_BPAMMO
#ifdef REGAMEDLL_API
		&&
		((m_pPlayer->CSPlayer()->m_iWeaponInfiniteIds & (1 << m_iId)) || (m_pPlayer->CSPlayer()->m_iWeaponInfiniteIds <= 0 && !IsGrenadeWeapon(m_iId)))
#endif
		)
		|| (IsGrenadeWeapon(m_iId) && infiniteGrenades.value == 1.0f))
	{
		if (pszAmmo1())
		{
			m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()] = iMaxAmmo1();
		}

		if (pszAmmo2())
		{
			m_pPlayer->m_rgAmmo[SecondaryAmmoIndex()] = iMaxAmmo2();
		}
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayerWeapon, ItemPostFrame)

void EXT_FUNC CBasePlayerWeapon::__API_HOOK(ItemPostFrame)()
{
	int usableButtons = m_pPlayer->pev->button;

	if (!HasSecondaryAttack())
	{
		usableButtons &= ~IN_ATTACK2;
	}

	if (m_flGlock18Shoot != 0)
	{
		FireRemaining(m_iGlock18ShotsFired, m_flGlock18Shoot, TRUE);
	}
	else if (gpGlobals->time > m_flFamasShoot && m_flFamasShoot != 0)
	{
		FireRemaining(m_iFamasShotsFired, m_flFamasShoot, FALSE);
	}

	// Return zoom level back to previous zoom level before we fired a shot.
	// This is used only for the AWP and Scout
	if (m_flNextPrimaryAttack <= UTIL_WeaponTimeBase())
	{
		if (m_pPlayer->m_bResumeZoom)
		{
			m_pPlayer->m_iFOV = m_pPlayer->m_iLastZoom;
			m_pPlayer->pev->fov = m_pPlayer->m_iFOV;

			if (m_pPlayer->m_iFOV == m_pPlayer->m_iLastZoom)
			{
				// return the fade level in zoom.
				m_pPlayer->m_bResumeZoom = false;
			}
		}
	}

	if (m_pPlayer->m_flEjectBrass != 0 && m_pPlayer->m_flEjectBrass <= gpGlobals->time)
	{
		m_pPlayer->m_flEjectBrass = 0;
		EjectBrassLate();
	}

	if (!(m_pPlayer->pev->button & IN_ATTACK))
	{
		m_flLastFireTime = 0;
	}

	if (m_pPlayer->HasShield())
	{
		if (m_fInReload && (m_pPlayer->pev->button & IN_ATTACK2))
		{
			SecondaryAttack();
			m_pPlayer->pev->button &= ~IN_ATTACK2;
			m_fInReload = FALSE;
			m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase();
		}
	}

	if (m_fInReload && m_pPlayer->m_flNextAttack <= UTIL_WeaponTimeBase())
	{
		// complete the reload.
		int j = Q_min(iMaxClip() - m_iClip, m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]);

		// Add them to the clip
		m_iClip += j;

#ifdef REGAMEDLL_ADD
		// Do not remove bpammo of the player,
		// if cvar allows to refill bpammo on during reloading the weapons
		if (refill_bpammo_weapons.value < 3.0f)
#endif
		{
			m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] -= j;
		}

		m_pPlayer->TabulateAmmo();
		m_fInReload = FALSE;
	}

	if ((usableButtons & IN_ATTACK2) && CanAttack(m_flNextSecondaryAttack, UTIL_WeaponTimeBase(), UseDecrement())
#ifdef REGAMEDLL_FIXES
		&& !m_pPlayer->m_bIsDefusing // In-line: I think it's fine to block secondary attack, when defusing. It's better then blocking speed resets in weapons.
#endif
    )
	{
		if (pszAmmo2() && !m_pPlayer->m_rgAmmo[SecondaryAmmoIndex()])
		{
			m_fFireOnEmpty = TRUE;
		}

		SecondaryAttack();
		m_pPlayer->pev->button &= ~IN_ATTACK2;
	}
	else if ((m_pPlayer->pev->button & IN_ATTACK) && CanAttack(m_flNextPrimaryAttack, UTIL_WeaponTimeBase(), UseDecrement()))
	{
		if ((m_iClip == 0 && pszAmmo1()) || (iMaxClip() == WEAPON_NOCLIP && !m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()]))
		{
			m_fFireOnEmpty = TRUE;
		}

		m_pPlayer->TabulateAmmo();

		// Can't shoot during the freeze period
		// Always allow firing in single player
		if (
#ifdef REGAMEDLL_API
			m_pPlayer->CSPlayer()->m_bCanShootOverride ||
#endif
			(m_pPlayer->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !m_pPlayer->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
		{
			// don't fire underwater
			if (m_pPlayer->pev->waterlevel == 3 && (iFlags() & ITEM_FLAG_NOFIREUNDERWATER))
			{
				PlayEmptySound();
				m_flNextPrimaryAttack = GetNextAttackDelay(0.15);
			}
			else
			{
				PrimaryAttack();
			}
		}
	}
	else if ((m_pPlayer->pev->button & IN_RELOAD) && iMaxClip() != WEAPON_NOCLIP && !m_fInReload && m_flNextPrimaryAttack < UTIL_WeaponTimeBase())
	{
		// reload when reload is pressed, or if no buttons are down and weapon is empty.
		if (m_flFamasShoot == 0 && m_flGlock18Shoot == 0)
		{
			if (!(m_iWeaponState & WPNSTATE_SHIELD_DRAWN))
			{
				// reload when reload is pressed, or if no buttons are down and weapon is empty.
				Reload();
			}
		}
	}
	else if (!(usableButtons & (IN_ATTACK | IN_ATTACK2)))
	{
		// no fire buttons down

		// The following code prevents the player from tapping the firebutton repeatedly
		// to simulate full auto and retaining the single shot accuracy of single fire
		if (m_bDelayFire)
		{
			m_bDelayFire = false;

			if (m_iShotsFired > 15)
			{
				m_iShotsFired = 15;
			}

			m_flDecreaseShotsFired = gpGlobals->time + 0.4f;
		}

		m_fFireOnEmpty = FALSE;

		// if it's a pistol then set the shots fired to 0 after the player releases a button
		if (IsSecondaryWeapon(m_iId))
		{
			m_iShotsFired = 0;
		}
		else
		{
			if (m_iShotsFired > 0 && m_flDecreaseShotsFired < gpGlobals->time)
			{
				m_flDecreaseShotsFired = gpGlobals->time + 0.0225f;
				m_iShotsFired--;

#ifdef REGAMEDLL_FIXES
				// Reset accuracy
				if (m_iShotsFired == 0)
				{
					m_flAccuracy = GetBaseAccuracy((WeaponIdType)m_iId);
				}
#endif
			}
		}

		if (!IsUseable() && m_flNextPrimaryAttack < UTIL_WeaponTimeBase())
		{
#if 0
			// weapon isn't useable, switch.
			if (!(iFlags() & ITEM_FLAG_NOAUTOSWITCHEMPTY) && g_pGameRules->GetNextBestWeapon(m_pPlayer, this))
			{
				m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.3f;
				return;
			}
#endif
		}
		else
		{
			if (!(m_iWeaponState & WPNSTATE_SHIELD_DRAWN))
			{
				// weapon is useable. Reload if empty and weapon has waited as long as it has to after firing
				if (!m_iClip && !(iFlags() & ITEM_FLAG_NOAUTORELOAD) && m_flNextPrimaryAttack < UTIL_WeaponTimeBase())
				{
					if (m_flFamasShoot == 0 && m_flGlock18Shoot == 0)
					{
						Reload();
						return;
					}
				}
			}
		}

#ifdef BUILD_LATEST
		HandleInfiniteAmmo();
#endif

		WeaponIdle();
		return;
	}

#ifdef BUILD_LATEST
	HandleInfiniteAmmo();
#endif

	// catch all
	if (ShouldWeaponIdle())
	{
		WeaponIdle();
	}
}

bool CBasePlayerItem::DestroyItem()
{
	bool success = false;

	if (m_pPlayer)
	{
		// if attached to a player, remove.
		if (m_pPlayer->RemovePlayerItem(this))
		{

#ifdef REGAMEDLL_FIXES
			if (m_iId == WEAPON_C4) {
				m_pPlayer->m_bHasC4 = false;
				m_pPlayer->pev->body = 0;
				m_pPlayer->SetBombIcon(FALSE);
				m_pPlayer->SetProgressBarTime(0);
			}

			m_pPlayer->pev->weapons &= ~(1 << m_iId);

			// No more weapon
			if ((m_pPlayer->pev->weapons & ~(1 << WEAPON_SUIT)) == 0) {
				m_pPlayer->m_iHideHUD |= HIDEHUD_WEAPONS;
			}

			if (!m_pPlayer->m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]) {
				m_pPlayer->m_bHasPrimary = false;
			}
#endif
			success = true;
		}
	}

	Kill();

	return success;
}

int CBasePlayerItem::AddToPlayer(CBasePlayer *pPlayer)
{
	m_pPlayer = pPlayer;

	MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, nullptr, pPlayer->pev);
		WRITE_BYTE(m_iId);
	MESSAGE_END();

	return TRUE;
}

void CBasePlayerItem::Drop()
{
	SetTouch(nullptr);
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CBasePlayerItem::Kill()
{
	SetTouch(nullptr);
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CBasePlayerItem::Holster(int skiplocal)
{
	m_pPlayer->pev->viewmodel = 0;
	m_pPlayer->pev->weaponmodel = 0;
}

void CBasePlayerItem::AttachToPlayer(CBasePlayer *pPlayer)
{
	pev->movetype = MOVETYPE_FOLLOW;
	pev->solid = SOLID_NOT;
	pev->aiment = pPlayer->edict();
	pev->effects = EF_NODRAW;

	// server won't send down to clients if modelindex == 0
	pev->modelindex = 0;
	pev->model = 0;
	pev->owner = pPlayer->edict();

#ifndef REGAMEDLL_FIXES
	pev->nextthink = gpGlobals->time + 0.1f;
#else
	// Remove think - prevents futher attempts to materialize
	pev->nextthink = 0;
	SetThink(nullptr);
#endif

	SetTouch(nullptr);
}

void CBasePlayerWeapon::Spawn()
{
#ifdef REGAMEDLL_API
	ItemInfo info;
	Q_memset(&info, 0, sizeof(info));

	if (GetItemInfo(&info)) {
		CSPlayerItem()->SetItemInfo(&info);
	}
#endif
}

// CALLED THROUGH the newly-touched weapon's instance. The existing player weapon is pOriginal
int CBasePlayerWeapon::AddDuplicate(CBasePlayerItem *pOriginal)
{
	if (m_iDefaultAmmo)
	{
		return ExtractAmmo((CBasePlayerWeapon *)pOriginal);
	}
	else
	{
		// a dead player dropped this.
		return ExtractClipAmmo((CBasePlayerWeapon *)pOriginal);
	}
}

int CBasePlayerWeapon::AddToPlayer(CBasePlayer *pPlayer)
{
	m_pPlayer = pPlayer;
	pPlayer->pev->weapons |= (1 << m_iId);

	if (!m_iPrimaryAmmoType)
	{
		m_iPrimaryAmmoType = pPlayer->GetAmmoIndex(pszAmmo1());
#ifndef REGAMEDLL_FIXES
		m_iSecondaryAmmoType = pPlayer->GetAmmoIndex(pszAmmo2());
#endif
	}

#ifdef REGAMEDLL_FIXES
	// (3rd party support) if someone updates (or screws) the secondary ammo type later
	if (!m_iSecondaryAmmoType)
	{
		m_iSecondaryAmmoType = pPlayer->GetAmmoIndex(pszAmmo2());
	}
#endif

	if (AddWeapon())
	{
		return CBasePlayerItem::AddToPlayer(pPlayer);
	}

	return FALSE;
}

int CBasePlayerWeapon::UpdateClientData(CBasePlayer *pPlayer)
{
	bool bSend = false;
	int state = 0;

	if (pPlayer->m_pActiveItem == this)
	{
		if (pPlayer->m_fOnTarget)
			state = WEAPON_IS_ONTARGET;
		else
			state = 1;
	}

	if (!pPlayer->m_fWeapon)
		bSend = true;

	if (this == pPlayer->m_pActiveItem || this == pPlayer->m_pClientActiveItem)
	{
		if (pPlayer->m_pActiveItem != pPlayer->m_pClientActiveItem)
			bSend = true;
	}

	if (m_iClip != m_iClientClip || state != m_iClientWeaponState || pPlayer->m_iFOV != pPlayer->m_iClientFOV)
		bSend = true;

	if (bSend)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, nullptr, pPlayer->pev);
			WRITE_BYTE(state);
			WRITE_BYTE(m_iId);
			WRITE_BYTE(m_iClip);
		MESSAGE_END();

		m_iClientClip = m_iClip;
		m_iClientWeaponState = state;
		pPlayer->m_fWeapon = TRUE;
	}

	if (m_pNext)
	{
		m_pNext->UpdateClientData(pPlayer);
	}

	return 1;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayerWeapon, SendWeaponAnim, (int iAnim, int skiplocal), iAnim, skiplocal)

void EXT_FUNC CBasePlayerWeapon::__API_HOOK(SendWeaponAnim)(int iAnim, int skiplocal)
{
	m_pPlayer->pev->weaponanim = iAnim;

#ifdef CLIENT_WEAPONS
	if (skiplocal && ENGINE_CANSKIP(m_pPlayer->edict()))
		return;
#endif

	MESSAGE_BEGIN(MSG_ONE, SVC_WEAPONANIM, nullptr, m_pPlayer->pev);
		WRITE_BYTE(iAnim);		// sequence number
		WRITE_BYTE(pev->body);	// weaponmodel bodygroup.
	MESSAGE_END();
}

BOOL CBasePlayerWeapon::AddPrimaryAmmo(int iCount, char *szName, int iMaxClip, int iMaxCarry)
{
	int iIdAmmo;

	if (iMaxClip < 1)
	{
		m_iClip = WEAPON_NOCLIP;
		iIdAmmo = m_pPlayer->GiveAmmo(iCount, szName, iMaxCarry);
	}
	else if (m_iClip == 0)
	{
		int i;
		i = Q_min(m_iClip + iCount, iMaxClip);
		m_iClip += i;

		iIdAmmo = m_pPlayer->GiveAmmo(iCount - i, szName, iMaxCarry);
	}
	else
	{
		iIdAmmo = m_pPlayer->GiveAmmo(iCount, szName, iMaxCarry);
	}

	if (iIdAmmo > 0)
	{
		m_iPrimaryAmmoType = iIdAmmo;
		if (m_pPlayer->HasPlayerItem(this))
		{
			// play the "got ammo" sound only if we gave some ammo to a player that already had this gun.
			// if the player is just getting this gun for the first time, DefaultTouch will play the "picked up gun" sound for us.
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
		}
	}

	return iIdAmmo > 0 ? TRUE : FALSE;
}

BOOL CBasePlayerWeapon::AddSecondaryAmmo(int iCount, char *szName, int iMax)
{
	int iIdAmmo = m_pPlayer->GiveAmmo(iCount, szName, iMax);

	if (iIdAmmo > 0)
	{
		m_iSecondaryAmmoType = iIdAmmo;
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	}

	return iIdAmmo > 0 ? TRUE : FALSE;
}

// IsUseable - this function determines whether or not a
// weapon is useable by the player in its current state.
// (does it have ammo loaded? do I have any ammo for the
// weapon?, etc)
BOOL CBasePlayerWeapon::IsUseable()
{
	if (m_iClip <= 0)
	{
		if (m_pPlayer->m_rgAmmo[PrimaryAmmoIndex()] <= 0 && iMaxAmmo1() != -1)
		{
			// clip is empty (or nonexistant) and the player has no more ammo of this type.
			return FALSE;
		}
	}

	return TRUE;
}

LINK_HOOK_CLASS_CHAIN2(BOOL, CBasePlayerWeapon, CanDeploy)

BOOL EXT_FUNC CBasePlayerWeapon::__API_HOOK(CanDeploy)()
{
	return TRUE;
}

LINK_HOOK_CLASS_CHAIN(BOOL, CBasePlayerWeapon, DefaultDeploy, (char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal), szViewModel, szWeaponModel, iAnim, szAnimExt, skiplocal)

BOOL EXT_FUNC CBasePlayerWeapon::__API_HOOK(DefaultDeploy)(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal)
{
	if (!CanDeploy())
		return FALSE;

	m_pPlayer->TabulateAmmo();
#ifdef REGAMEDLL_API
	m_pPlayer->pev->viewmodel = ALLOC_STRING(szViewModel);
	m_pPlayer->pev->weaponmodel = ALLOC_STRING(szWeaponModel);
#else
	m_pPlayer->pev->viewmodel = MAKE_STRING(szViewModel);
	m_pPlayer->pev->weaponmodel = MAKE_STRING(szWeaponModel);
#endif
	model_name = m_pPlayer->pev->viewmodel;
	Q_strcpy(m_pPlayer->m_szAnimExtention, szAnimExt);
	SendWeaponAnim(iAnim, skiplocal);

	m_pPlayer->m_flNextAttack = 0.75f;
	m_flTimeWeaponIdle = 1.5f;
	m_flLastFireTime = 0.0f;
	m_flDecreaseShotsFired = gpGlobals->time;

	m_pPlayer->m_iFOV = DEFAULT_FOV;
	m_pPlayer->pev->fov = DEFAULT_FOV;
	m_pPlayer->m_iLastZoom = DEFAULT_FOV;
	m_pPlayer->m_bResumeZoom = false;

	return TRUE;
}

void CBasePlayerWeapon::ReloadSound()
{
	CBasePlayer *pPlayer = nullptr;
	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")))
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (pPlayer->IsDormant())
			continue;

		if (pPlayer == m_pPlayer)
			continue;

		float distance = (m_pPlayer->pev->origin - pPlayer->pev->origin).Length();
		if (distance <= MAX_DIST_RELOAD_SOUND)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgReloadSound, nullptr, pPlayer->pev);
				WRITE_BYTE(int((1.0f - (distance / MAX_DIST_RELOAD_SOUND)) * 255.0f));
			if (!Q_strcmp(STRING(pev->classname), "weapon_m3") || !Q_strcmp(STRING(pev->classname), "weapon_xm1014"))
				WRITE_BYTE(0);
			else
				WRITE_BYTE(1);
			MESSAGE_END();
		}
	}
}

LINK_HOOK_CLASS_CHAIN(int, CBasePlayerWeapon, DefaultReload, (int iClipSize, int iAnim, float fDelay), iClipSize, iAnim, fDelay)

int EXT_FUNC CBasePlayerWeapon::__API_HOOK(DefaultReload)(int iClipSize, int iAnim, float fDelay)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return FALSE;

	int j = Q_min(iClipSize - m_iClip, m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]);
	if (!j)
	{
		return FALSE;
	}

	m_pPlayer->m_flNextAttack = fDelay;

	ReloadSound();
	SendWeaponAnim(iAnim, UseDecrement() ? 1 : 0);

	m_fInReload = TRUE;
	m_flTimeWeaponIdle = fDelay + 0.5f;

	return TRUE;
}

LINK_HOOK_CLASS_CHAIN(bool, CBasePlayerWeapon, DefaultShotgunReload, (int iAnim, int iStartAnim, float fDelay, float fStartDelay, const char *pszReloadSound1, const char *pszReloadSound2), iAnim, iStartAnim, fDelay, fStartDelay, pszReloadSound1, pszReloadSound2)

bool EXT_FUNC CBasePlayerWeapon::__API_HOOK(DefaultShotgunReload)(int iAnim, int iStartAnim, float fDelay, float fStartDelay, const char *pszReloadSound1, const char *pszReloadSound2)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 || m_iClip == iMaxClip())
		return false;

	// don't reload until recoil is done
	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
		return false;

	// check to see if we're ready to reload
	if (m_fInSpecialReload == 0)
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		SendWeaponAnim(iStartAnim, UseDecrement() != FALSE);

		m_fInSpecialReload = 1;
		m_flNextSecondaryAttack = m_flTimeWeaponIdle = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + fStartDelay;
		m_flNextPrimaryAttack = GetNextAttackDelay(fStartDelay);
	}
	else if (m_fInSpecialReload == 1)
	{
		if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
			return false;

		// was waiting for gun to move to side
		m_fInSpecialReload = 2;

		const char *pszReloadSound = nullptr;
		if (pszReloadSound1 && pszReloadSound2) pszReloadSound = RANDOM_LONG(0, 1) ? pszReloadSound1 : pszReloadSound2;
		else if (pszReloadSound1)               pszReloadSound = pszReloadSound1;
		else if (pszReloadSound2)               pszReloadSound = pszReloadSound2;

		if (pszReloadSound && pszReloadSound[0] != '\0')
		{
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, pszReloadSound, VOL_NORM, ATTN_NORM, 0, 85 + RANDOM_LONG(0, 31));
		}

		SendWeaponAnim(iAnim, UseDecrement());

		m_flTimeWeaponIdle = m_flNextReload = UTIL_WeaponTimeBase() + fDelay;
	}
	else
#ifdef BUILD_LATEST_FIXES
		if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
#endif
	{
		m_iClip++;

#ifdef REGAMEDLL_ADD
		if (refill_bpammo_weapons.value < 3.0f)
#endif
		{
			m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;
			m_pPlayer->ammo_buckshot--;
		}

		m_fInSpecialReload = 1;
	}

	return true;
}

BOOL CBasePlayerWeapon::PlayEmptySound()
{
	if (m_iPlayEmptySound)
	{
		switch (m_iId)
		{
		case WEAPON_USP:
		case WEAPON_GLOCK18:
		case WEAPON_P228:
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/dryfire_pistol.wav", 0.8, ATTN_NORM);
			break;
		default:
			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/dryfire_rifle.wav", 0.8, ATTN_NORM);
			break;
		}
	}

	return FALSE;
}

void CBasePlayerWeapon::ResetEmptySound()
{
	m_iPlayEmptySound = 1;
}

int CBasePlayerWeapon::PrimaryAmmoIndex()
{
	return m_iPrimaryAmmoType;
}

int CBasePlayerWeapon::SecondaryAmmoIndex()
{
#ifdef REGAMEDLL_ADD
	return m_iSecondaryAmmoType;
#else
	return -1;
#endif
}

void CBasePlayerWeapon::Holster(int skiplocal)
{
	// cancel any reload in progress.
	m_fInReload = FALSE;
	m_pPlayer->pev->viewmodel = 0;
	m_pPlayer->pev->weaponmodel = 0;
	
#ifdef REGAMEDLL_FIXES
	m_fInSpecialReload = 0;
#endif
}

// called by the new item with the existing item as parameter
//
// if we call ExtractAmmo(), it's because the player is picking up this type of weapon for
// the first time. If it is spawned by the world, m_iDefaultAmmo will have a default ammo amount in it.
// if  this is a weapon dropped by a dying player, has 0 m_iDefaultAmmo, which means only the ammo in
// the weapon clip comes along.
int CBasePlayerWeapon::ExtractAmmo(CBasePlayerWeapon *pWeapon)
{
	int res = 0;
	if (pszAmmo1())
	{
		// blindly call with m_iDefaultAmmo. It's either going to be a value or zero. If it is zero,
		// we only get the ammo in the weapon's clip, which is what we want.
		res = pWeapon->AddPrimaryAmmo(m_iDefaultAmmo, (char *)pszAmmo1(), iMaxClip(), iMaxAmmo1());
		m_iDefaultAmmo = 0;
	}

	if (pszAmmo2())
	{
		res = pWeapon->AddSecondaryAmmo(0, (char *)pszAmmo2(), iMaxAmmo2());
	}

	return res;
}

// called by the new item's class with the existing item as parameter
int CBasePlayerWeapon::ExtractClipAmmo(CBasePlayerWeapon *pWeapon)
{
	int iAmmo;
	if (m_iClip == WEAPON_NOCLIP)
	{
		// guns with no clips always come empty if they are second-hand
		iAmmo = 0;
	}
	else
	{
		iAmmo = m_iClip;
	}

	int iIdAmmo = pWeapon->m_pPlayer->GiveAmmo(iAmmo, pszAmmo1(), iMaxAmmo1());

#ifdef REGAMEDLL_FIXES
	if (iIdAmmo > 0 && IsGrenadeWeapon(m_iId))
	{
		// grenades have WEAPON_NOCLIP force play the "got ammo" sound.
		EMIT_SOUND(pWeapon->m_pPlayer->edict(), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	}
#endif

	return iIdAmmo;
}

// RetireWeapon - no more ammo for this gun, put it away.
void CBasePlayerWeapon::RetireWeapon()
{
	// first, no viewmodel at all.
	m_pPlayer->pev->viewmodel = iStringNull;
	m_pPlayer->pev->weaponmodel = iStringNull;

	g_pGameRules->GetNextBestWeapon(m_pPlayer, this);
}

// GetNextAttackDelay - An accurate way of calcualting the next attack time.
float CBasePlayerWeapon::GetNextAttackDelay(float delay)
{
#ifndef REGAMEDLL_FIXES
	if (m_flLastFireTime == 0.0f || m_flNextPrimaryAttack == -1.0f)
	{
		// At this point, we are assuming that the client has stopped firing
		// and we are going to reset our book keeping variables.
		m_flPrevPrimaryAttack = delay;
		m_flLastFireTime = gpGlobals->time;
	}
#endif

#ifdef REGAMEDLL_BUILD_6153

	// TODO: Build 6xxx
	// at build 6153 beta this removed
	// maybe it was initiated due to the delay of the shot

	// calculate the time between this shot and the previous
	float flTimeBetweenFires = gpGlobals->time - m_flLastFireTime;
	float flCreep = 0.0f;

	if (flTimeBetweenFires > 0)
	{
		flCreep = flTimeBetweenFires - m_flPrevPrimaryAttack;
	}

	float flNextAttack = UTIL_WeaponTimeBase() + delay - flCreep;
#else
	float flNextAttack = UTIL_WeaponTimeBase() + delay;
#endif

	// save the last fire time
	m_flLastFireTime = gpGlobals->time;

	// we need to remember what the m_flNextPrimaryAttack time is set to for each shot,
	// store it as m_flPrevPrimaryAttack.
	m_flPrevPrimaryAttack = flNextAttack - UTIL_WeaponTimeBase();

	return flNextAttack;
}

// true - keep the amount of bpammo
// false - let take away bpammo
void CBasePlayerWeapon::InstantReload(bool bCanRefillBPAmmo)
{
	// if you already reload
	//if (m_fInReload)
	//	return;

	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return;

	m_fInReload = FALSE;
	m_pPlayer->m_flNextAttack = 0;

	// complete the reload.
	int j = Q_min(iMaxClip() - m_iClip, m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]);
	if (j == 0)
		return;

	// Add them to the clip
	m_iClip += j;

	if (!bCanRefillBPAmmo) {
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] -= j;
	}

	m_pPlayer->TabulateAmmo();
}

TYPEDESCRIPTION CWeaponBox::m_SaveData[] =
{
	DEFINE_ARRAY(CWeaponBox, m_rgAmmo, FIELD_INTEGER, MAX_AMMO_SLOTS),
	DEFINE_ARRAY(CWeaponBox, m_rgiszAmmo, FIELD_STRING, MAX_AMMO_SLOTS),
	DEFINE_ARRAY(CWeaponBox, m_rgpPlayerItems, FIELD_CLASSPTR, MAX_ITEM_TYPES),
	DEFINE_FIELD(CWeaponBox, m_cAmmoTypes, FIELD_INTEGER),
};

LINK_ENTITY_TO_CLASS(weaponbox, CWeaponBox, CCSWeaponBox)
IMPLEMENT_SAVERESTORE(CWeaponBox, CBaseEntity)

void CWeaponBox::Precache()
{
	PRECACHE_MODEL("models/w_weaponbox.mdl");
}

void CWeaponBox::KeyValue(KeyValueData *pkvd)
{
	if (m_cAmmoTypes >= MAX_AMMO_SLOTS)
	{
		ALERT(at_console, "WeaponBox too full! only %d ammotypes allowed\n", MAX_AMMO_SLOTS);
		return;
	}

	PackAmmo(ALLOC_STRING(pkvd->szKeyName), Q_atoi(pkvd->szValue));

	// count this new ammo type.
	m_cAmmoTypes++;
	pkvd->fHandled = TRUE;
}

void CWeaponBox::BombThink()
{
	if (!m_bIsBomb)
		return;

	CBasePlayer *pPlayer = nullptr;
	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")))
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (!pPlayer->IsPlayer() || pPlayer->IsDormant())
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pPlayer->pev);

		if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == TERRORIST)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBombDrop, nullptr, pTempPlayer->edict());
				WRITE_COORD(pev->origin.x);
				WRITE_COORD(pev->origin.y);
				WRITE_COORD(pev->origin.z);
				WRITE_BYTE(BOMB_FLAG_DROPPED);
			MESSAGE_END();
		}
	}

	pev->nextthink = gpGlobals->time + 1.0f;
}

LINK_HOOK_CLASS_VOID_CHAIN(CWeaponBox, SetModel, (const char *pszModelName), pszModelName)

void CWeaponBox::__API_HOOK(SetModel)(const char *pszModelName)
{
	SET_MODEL(ENT(pev), pszModelName);
}

void CWeaponBox::Spawn()
{
	Precache();

	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;

	m_bIsBomb = false;

	UTIL_SetSize(pev, g_vecZero, g_vecZero);
	SET_MODEL(ENT(pev), "models/w_weaponbox.mdl");
}

// The think function that removes the box from the world.
void CWeaponBox::Kill()
{
	// destroy the weapons
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		CBasePlayerItem *pWeapon = m_rgpPlayerItems[i];
		while (pWeapon)
		{
			pWeapon->SetThink(&CBaseEntity::SUB_Remove);
			pWeapon->pev->nextthink = gpGlobals->time + 0.1f;
			pWeapon = pWeapon->m_pNext;
		}
	}

	// remove the box
	UTIL_Remove(this);
}

bool CWeaponBox::GiveAmmoToPlayer(CBasePlayer *pPlayer, CBasePlayerWeapon *pWeapon, int iCurrentAmmo, const char *pszAmmo, int iMaxAmmo, CBasePlayerItem **pGivenItem)
{
	if (iCurrentAmmo >= iMaxAmmo)
		return false; // can't pickup more, these ammo are full in backpack

	// If already have a weapon in backpack, just refill ammo for it
	int iAmmoIndex = GetAmmoIndex(pszAmmo);
	if (iAmmoIndex > 0)
	{
		// How many weapon ammo can pick up?
		int iAmmoPickup = min(m_rgAmmo[iAmmoIndex], iMaxAmmo - iCurrentAmmo);
		if (iAmmoPickup > 0)
		{
			if (iCurrentAmmo == 0 && !(pPlayer->pev->weapons & (1<<pWeapon->m_iId)) && (pWeapon->iFlags() & ITEM_FLAG_EXHAUSTIBLE))
			{
				if (m_rgAmmo[iAmmoIndex] > iMaxAmmo)
				{
					// If ammo capacity of the dropped weapon exceeds the player's backpack capacity,
					// make a copy of dropped weapon and give it to the player
					CBasePlayerItem *copyItem = (CBasePlayerItem *)pPlayer->GiveCopyItem(pWeapon);
					if (copyItem)
					{
						// The cloned weapon must inherit properties from a dropped weapon, such as Item Info
#ifdef REGAMEDLL_API
						ItemInfo info;
						if (pWeapon->CSPlayerItem()->GetItemInfo(&info))
							copyItem->CSPlayerItem()->SetItemInfo(&info);
#endif
						m_rgAmmo[iAmmoIndex]--;
						iAmmoPickup--;
					}
				}
				else
				{
					// If no weapon in backpack, then issue weapon
					if (pPlayer->AddPlayerItem(pWeapon))
					{
						pWeapon->AttachToPlayer(pPlayer);
						if (pGivenItem) *pGivenItem = pWeapon;
					}

					// unlink this weapon from the box
					return true;
				}
			}

			Assert(iAmmoPickup != 0);
			Assert(m_rgAmmo[iAmmoIndex] != 0);

			if (!FStringNull(m_rgiszAmmo[iAmmoIndex]) &&
				pPlayer->GiveAmmo(iAmmoPickup, STRING(m_rgiszAmmo[iAmmoIndex]), iMaxAmmo) != -1)
			{
				m_rgAmmo[iAmmoIndex] -= iAmmoPickup;

				if (m_rgAmmo[iAmmoIndex] < 0)
					m_rgAmmo[iAmmoIndex] = 0;

				EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
			}
		}

		// ammo exhausted, remove this weapon
		if (m_rgAmmo[iAmmoIndex] <= 0)
		{
			pWeapon->Kill();

			// unlink this weapon from the box
			return true;
		}

		// ammo has not been exhausted yet, keep this weapon in weaponbox
		return false;
	}

	// If no weapon in backpack, then issue weapon
	if (pPlayer->AddPlayerItem(pWeapon))
	{
		pWeapon->AttachToPlayer(pPlayer);
		if (pGivenItem) *pGivenItem = pWeapon;
	}

	// unlink this weapon from the box
	return true;
}

// Try to add my contents to the toucher if the toucher is a player.
void CWeaponBox::Touch(CBaseEntity *pOther)
{
	if (!(pev->flags & FL_ONGROUND))
	{
		return;
	}

	if (!pOther->IsPlayer())
	{
		// only players may touch a weaponbox.
		return;
	}

	if (!pOther->IsAlive())
	{
		// no dead guys.
		return;
	}

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pOther);

	if (pPlayer->m_bIsVIP || pPlayer->m_bShieldDrawn)
		return;

	pPlayer->OnTouchingWeapon(this);

	bool bRemove = true;

#ifdef REGAMEDLL_FIXES
	CBasePlayerItem *givenItem = nullptr;
#else
	bool givenItem = false;
#endif

	// go through my weapons and try to give the usable ones to the player.
	// it's important the the player be given ammo first, so the weapons code doesn't refuse
	// to deploy a better weapon that the player may pick up because he has no ammo for it.
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		if (!m_rgpPlayerItems[i])
			continue;

		CBasePlayerItem *pPrev = NULL;
		CBasePlayerItem *pItem = m_rgpPlayerItems[i];

		// have at least one weapon in this slot
		while (pItem)
		{
			if ((pPlayer->HasShield() && pItem->m_iId == WEAPON_ELITE)
				|| (pPlayer->IsBot() && TheCSBots() && !TheCSBots()->IsWeaponUseable(pItem)))
			{
				return;
			}

#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem((pItem->m_iId == WEAPON_SHIELDGUN) ? ITEM_SHIELDGUN : (ItemID)pItem->m_iId, ITEM_TYPE_TOUCHED))
				return;
#endif

			if (FClassnameIs(pItem->pev, "weapon_c4"))
			{
#ifdef REGAMEDLL_FIXES
				if (pPlayer->m_iTeam != TERRORIST)
					return;
#else
				if (pPlayer->m_iTeam != TERRORIST || pPlayer->pev->deadflag != DEAD_NO)
					return;
#endif

				if (pPlayer->m_bShowHints && !(pPlayer->m_flDisplayHistory & DHF_BOMB_RETRIEVED))
				{
					pPlayer->m_flDisplayHistory |= DHF_BOMB_RETRIEVED;
					pPlayer->HintMessage("#Hint_you_have_the_bomb");
				}
				else
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Got_bomb");

				UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Got_The_Bomb\"\n",
					STRING(pPlayer->pev->netname),
					GETPLAYERUSERID(pPlayer->edict()),
					GETPLAYERAUTHID(pPlayer->edict()));

				g_pGameRules->m_bBombDropped = FALSE;

				MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
					WRITE_BYTE(9);
					WRITE_BYTE(DRC_CMD_EVENT);
					WRITE_SHORT(ENTINDEX(pPlayer->edict()));
					WRITE_SHORT(ENTINDEX(edict()));
					WRITE_LONG(6);
				MESSAGE_END();

				pPlayer->m_bHasC4 = true;
				pPlayer->pev->body = 1;
				pPlayer->SetBombIcon(FALSE);

				CBaseEntity *pEntity = nullptr;
				while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
				{
					if (FNullEnt(pEntity->edict()))
						break;

					if (!pEntity->IsPlayer())
						continue;

					if (pEntity->IsDormant())
						continue;

					CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

					if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == TERRORIST)
					{
						if (pTempPlayer != pPlayer)
						{
							ClientPrint(pTempPlayer->pev, HUD_PRINTCENTER, "#Game_bomb_pickup", STRING(pPlayer->pev->netname));
						}

						MESSAGE_BEGIN(MSG_ONE, gmsgBombPickup, nullptr, pTempPlayer->pev);
						MESSAGE_END();
					}
				}

				if (TheCSBots())
				{
					TheCSBots()->SetLooseBomb(nullptr);
				}

				if (TheBots)
				{
					TheBots->OnEvent(EVENT_BOMB_PICKED_UP, pPlayer);
				}
			}

			if (i >= PRIMARY_WEAPON_SLOT && i <= PISTOL_SLOT && pPlayer->m_rgpPlayerItems[i])
			{
				// ...
			}
			else if (i == GRENADE_SLOT)
			{
				CBasePlayerWeapon *pGrenade = static_cast<CBasePlayerWeapon *>(pItem);
				if (pGrenade && pGrenade->IsWeapon())
				{
					int playerGrenades = pPlayer->m_rgAmmo[pGrenade->m_iPrimaryAmmoType];

#ifdef REGAMEDLL_FIXES
					CBasePlayerItem *pNext = pItem->m_pNext;

					// Determine the max ammo capacity for the picked-up grenade
					int iMaxPickupAmmo = pGrenade->iMaxAmmo1();

					// If the player already has the same weapon in inventory,
					// prioritize the max ammo capacity value over the one from the dropped weapon
					// When the pickup occurs, ammo will be granted up to
					// the max ammo capacity of the weapon currently held by the player
					CBasePlayerItem *pInventoryItem = (CBasePlayerItem *)pPlayer->GetItemById((WeaponIdType)pGrenade->m_iId);
					if (pInventoryItem && !Q_stricmp(pInventoryItem->pszAmmo1(), pGrenade->pszAmmo1()))
						iMaxPickupAmmo = pInventoryItem->iMaxAmmo1();

					// Pickup grenade item or refill ammo
					if (GiveAmmoToPlayer(pPlayer, pGrenade,
						playerGrenades, pGrenade->pszAmmo1(), iMaxPickupAmmo, &givenItem))
					{
						// unlink this weapon from the box
						if (pPrev)
							pPrev->m_pNext = pItem = pNext;
						else
							m_rgpPlayerItems[i] = pItem = pNext;

						continue;
					}
#else
					int maxGrenades = 0;
					const char *grenadeName = nullptr;

					switch (pGrenade->m_iId)
					{
					case WEAPON_HEGRENADE:
						grenadeName = "weapon_hegrenade";
						maxGrenades = 1;
						break;
					case WEAPON_SMOKEGRENADE:
						grenadeName = "weapon_smokegrenade";
						maxGrenades = 1;
						break;
					case WEAPON_FLASHBANG:
						grenadeName = "weapon_flashbang";
						maxGrenades = 2;
						break;
					}

					if (playerGrenades < maxGrenades && grenadeName)
					{
						// CRITICAL BUG: since gives a new entity using GiveNamedItem,
						// but the entity is packaged in a weaponbox still exists and will never used or removed. It's leak!
						// How reproduced: Drop your grenade on the ground, check output of command `entity_dump`,
						// there we will see only get one grenade. Next step - pick it up, do check again `entity_dump`,
						// but this time we'll see them x2.

						givenItem = true;
						pPlayer->GiveNamedItem(grenadeName);

						// unlink this weapon from the box
						pItem = m_rgpPlayerItems[i]->m_pNext;
						m_rgpPlayerItems[i] = pItem;
						continue;
					}
#endif

				}
			}
			else if (pPlayer->HasShield() && i == PRIMARY_WEAPON_SLOT)
			{
				// ...
			}
			else
			{
				CBasePlayerItem *pNext = pItem->m_pNext;

				if (pPlayer->AddPlayerItem(pItem))
				{
					pItem->AttachToPlayer(pPlayer);
#ifdef REGAMEDLL_FIXES
					givenItem = pItem;
#else
					givenItem = true;
#endif
				}

				// unlink this weapon from the box
				if (pPrev)
					pPrev->m_pNext = pNext;
				else
					m_rgpPlayerItems[i] = pItem = pNext;

				continue;
			}

			bRemove = false;
			pPrev = pItem;
			pItem = pItem->m_pNext;
		}
	}

	if (bRemove)
	{
		// dole out ammo
		for (int n = 0; n < MAX_AMMO_SLOTS; n++)
		{
			if (!FStringNull(m_rgiszAmmo[n]))
			{
				// there's some ammo of this type
				if (m_rgAmmo[n] > 0)
				{
#ifdef REGAMEDLL_ADD
					int iMaxAmmo = m_rgAmmo[n];
#else
					int iMaxAmmo = MaxAmmoCarry(m_rgiszAmmo[n]);
#endif

					pPlayer->GiveAmmo(m_rgAmmo[n], STRING(m_rgiszAmmo[n]), iMaxAmmo);
				}

				// now empty the ammo from the weaponbox since we just gave it to the player
				m_rgiszAmmo[n] = iStringNull;
				m_rgAmmo[n] = 0;
			}
		}
	}

	if (givenItem)
	{
		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);

#ifdef REGAMEDLL_FIXES
		// BUGBUG: weaponbox links gun to player, then ammo is given
		// so FShouldSwitchWeapon's CanHolster (which checks ammo) check inside AddPlayerItem
		// return FALSE, causing an unarmed player to not deploy any weaponbox grenade
		if (pPlayer->m_pActiveItem != givenItem && CSGameRules()->FShouldSwitchWeapon(pPlayer, givenItem))
		{
			// This re-check is done after ammo is given
			// so it ensures player properly deploys grenade from floor
			pPlayer->SwitchWeapon(givenItem);
		}
#endif
	}

	if (bRemove)
	{
		SetTouch(nullptr);
		UTIL_Remove(this);
	}
}

// Add this weapon to the box
BOOL CWeaponBox::PackWeapon(CBasePlayerItem *pWeapon)
{
	// is one of these weapons already packed in this box?
	if (HasWeapon(pWeapon))
	{
		// box can only hold one of each weapon type
		return FALSE;
	}

	if (pWeapon->m_pPlayer)
	{
		if (pWeapon->m_pPlayer->m_pActiveItem == pWeapon)
		{
			pWeapon->Holster();
		}

		if (!pWeapon->m_pPlayer->RemovePlayerItem(pWeapon))
		{
			// failed to unhook the weapon from the player!
			return FALSE;
		}
	}

	int iWeaponSlot = pWeapon->iItemSlot();
	if (m_rgpPlayerItems[iWeaponSlot])
	{
		// there's already one weapon in this slot, so link this into the slot's column
		pWeapon->m_pNext = m_rgpPlayerItems[iWeaponSlot];
		m_rgpPlayerItems[iWeaponSlot] = pWeapon;
	}
	else
	{
		// first weapon we have for this slot
		m_rgpPlayerItems[iWeaponSlot] = pWeapon;
		pWeapon->m_pNext = nullptr;
	}

	// never respawn
	pWeapon->pev->spawnflags |= SF_NORESPAWN;
	pWeapon->pev->movetype = MOVETYPE_NONE;
	pWeapon->pev->solid = SOLID_NOT;
	pWeapon->pev->effects = EF_NODRAW;
	pWeapon->pev->modelindex = 0;
	pWeapon->pev->model = 0;
	pWeapon->pev->owner = ENT(pev);
	pWeapon->SetThink(nullptr);
	pWeapon->SetTouch(nullptr);
	pWeapon->m_pPlayer = nullptr;

	return TRUE;
}

BOOL CWeaponBox::PackAmmo(string_t iszName, int iCount)
{
	if (!iszName)
	{
		// error here
		ALERT(at_console, "NULL String in PackAmmo!\n");
		return FALSE;
	}

	int iMaxCarry = MaxAmmoCarry(iszName);
	if (iMaxCarry != -1 && iCount > 0)
	{
		GiveAmmo(iCount, (char *)STRING(iszName), iMaxCarry);
		return TRUE;
	}

	return FALSE;
}

int CWeaponBox::GiveAmmo(int iCount, char *szName, int iMax, int *pIndex)
{
	int i;
	for (i = 1; i < MAX_AMMO_SLOTS && !FStringNull(m_rgiszAmmo[i]); i++)
	{
		if (!Q_stricmp(szName, STRING(m_rgiszAmmo[i])))
		{
			if (pIndex)
				*pIndex = i;

			int iAdd = Q_min(iCount, iMax - m_rgAmmo[i]);
			if (iCount == 0 || iAdd > 0)
			{
				m_rgAmmo[i] += iAdd;
				return i;
			}

			return -1;
		}
	}

	if (i < MAX_AMMO_SLOTS)
	{
		if (pIndex)
			*pIndex = i;

		m_rgiszAmmo[i] = MAKE_STRING(szName);
		m_rgAmmo[i] = iCount;

		return i;
	}

	ALERT(at_console, "out of named ammo slots\n");
	return i;
}

int CWeaponBox::GetAmmoIndex(const char *psz) const
{
	if (!psz)
		return -1;

	int i;
	for (i = 1; i < MAX_AMMO_SLOTS; i++)
	{
		if (FStringNull(m_rgiszAmmo[i]))
			continue;

		if (!Q_stricmp(STRING(m_rgiszAmmo[i]), psz))
			return i;
	}

	return -1;
}

// Is a weapon of this type already packed in this box?
BOOL CWeaponBox::HasWeapon(CBasePlayerItem *pCheckItem)
{
	CBasePlayerItem *pItem = m_rgpPlayerItems[pCheckItem->iItemSlot()];
	while (pItem)
	{
		if (FClassnameIs(pItem->pev, pCheckItem->pev->classname)) {
			return TRUE;
		}

		pItem = pItem->m_pNext;
	}

	return FALSE;
}

// Is there anything in this box?
BOOL CWeaponBox::IsEmpty()
{
	int i;
	for (i = 0; i < MAX_ITEM_TYPES; i++)
	{
		if (m_rgpPlayerItems[i])
		{
			return FALSE;
		}
	}

	for (i = 0; i < MAX_AMMO_SLOTS; i++)
	{
		if (m_rgiszAmmo[i])
		{
			// still have a bit of this type of ammo
			return FALSE;
		}
	}

	return TRUE;
}

void CWeaponBox::SetObjectCollisionBox()
{
	pev->absmin = pev->origin + Vector(-16, -16, 0);
	pev->absmax = pev->origin + Vector(16, 16, 16);
}

char *CArmoury::m_ItemModels[] = {
	"models/w_mp5.mdl",
	"models/w_tmp.mdl",
	"models/w_p90.mdl",
	"models/w_mac10.mdl",
	"models/w_ak47.mdl",
	"models/w_sg552.mdl",
	"models/w_m4a1.mdl",
	"models/w_aug.mdl",
	"models/w_scout.mdl",
	"models/w_g3sg1.mdl",
	"models/w_awp.mdl",
	"models/w_m3.mdl",
	"models/w_xm1014.mdl",
	"models/w_m249.mdl",
	"models/w_flashbang.mdl",
	"models/w_hegrenade.mdl",
	"models/w_kevlar.mdl",
	"models/w_assault.mdl",
	"models/w_smokegrenade.mdl",

#ifdef REGAMEDLL_ADD
	"models/w_shield.mdl",
	"models/w_famas.mdl",
	"models/w_sg550.mdl",
	"models/w_galil.mdl",
	"models/w_ump45.mdl",
	"models/w_glock18.mdl",
	"models/w_usp.mdl",
	"models/w_elite.mdl",
	"models/w_fiveseven.mdl",
	"models/w_p228.mdl",
	"models/w_deagle.mdl"
#endif

};

void CArmoury::Spawn()
{
	Precache();

	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;

	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));
	UTIL_SetOrigin(pev, pev->origin);

	SetTouch(&CArmoury::ArmouryTouch);

	if (m_iItem < ARRAYSIZE(m_ItemModels))
	{
		SET_MODEL(ENT(pev), m_ItemModels[m_iItem]);
	}

	if (m_iCount <= 0)
	{
		m_iCount = 1;
	}

#ifdef REGAMEDLL_FIXES
	// Cache the placed origin of source point
	pev->oldorigin = pev->origin;
#endif

	m_bAlreadyCounted = false;
	m_iInitialCount = m_iCount;
}

void CArmoury::Restart()
{
#ifdef REGAMEDLL_ADD
	if (!weapons_allow_map_placed.value)
	{
		Hide();
		return;
	}
#endif

#ifdef REGAMEDLL_FIXES
	// This code refers to the mode of Escape. (Because there is relationship to the team Terrorists)
	if (CSGameRules()->m_bMapHasEscapeZone)
#endif
	{
		if (m_iItem == ARMOURY_FLASHBANG || m_iItem == ARMOURY_HEGRENADE)
		{
			if (!m_bAlreadyCounted)
			{
				m_bAlreadyCounted = true;
				CSGameRules()->m_iTotalGrenadeCount += m_iInitialCount;
				m_iCount = m_iInitialCount;
				Draw();
				return;
			}

			float flRatio = real_t(m_iInitialCount / CSGameRules()->m_iTotalGrenadeCount) * real_t(CSGameRules()->m_iNumTerrorist) * 1.75;
			m_iCount = int(flRatio);
		}
		else if (m_iItem == ARMOURY_KEVLAR || m_iItem == ARMOURY_ASSAULT)
		{
			if (!m_bAlreadyCounted)
			{
				m_bAlreadyCounted = true;
				CSGameRules()->m_iTotalArmourCount += m_iInitialCount;
				m_iCount = m_iInitialCount;
				Draw();
				return;
			}

			float flRatio = real_t(m_iInitialCount / CSGameRules()->m_iTotalArmourCount) * real_t(CSGameRules()->m_iNumTerrorist);
			m_iCount = int(flRatio);
		}
		else
		{
			if (!m_bAlreadyCounted)
			{
				m_bAlreadyCounted = true;
				CSGameRules()->m_iTotalGunCount += m_iInitialCount;
				m_iCount = m_iInitialCount;
				Draw();
				return;
			}

			float flRatio = real_t(m_iInitialCount / CSGameRules()->m_iTotalGunCount) * real_t(CSGameRules()->m_iNumTerrorist) * 0.85;
			m_iCount = int(flRatio);
		}
	}

#ifdef REGAMEDLL_FIXES
	else
	{
		m_iCount = m_iInitialCount;
	}
#endif

	if (m_iCount < 1)
		m_iCount = 1;

	Draw();

#ifdef REGAMEDLL_FIXES
	// Restored origin from the cache
	UTIL_SetOrigin(pev, pev->oldorigin);
	DROP_TO_FLOOR(edict());
#endif
}

void CArmoury::Precache()
{
	if (m_iItem < ARRAYSIZE(m_ItemModels))
	{
		PRECACHE_MODEL(m_ItemModels[m_iItem]);
	}
}

void CArmoury::Draw()
{
	pev->effects &= ~EF_NODRAW;

#ifdef REGAMEDLL_FIXES
	pev->solid = SOLID_TRIGGER;
#endif
}

void CArmoury::Hide()
{
	pev->effects |= EF_NODRAW;

#ifdef REGAMEDLL_FIXES
	// more not to touch with the world.
	pev->solid = SOLID_NOT;
#endif
}

struct ArmouryItemStruct
{
	const char *entityName;
	char *ammoName;
	int giveAmount;
	int maxRounds;
} armouryItemInfo[] = {
	{ "weapon_mp5navy",   "9mm",        60, MAX_AMMO_9MM        }, // ARMOURY_MP5NAVY
	{ "weapon_tmp",       "9mm",        60, MAX_AMMO_9MM        }, // ARMOURY_TMP
	{ "weapon_p90",       "57mm",       50, MAX_AMMO_57MM       }, // ARMOURY_P90
	{ "weapon_mac10",     "45acp",      60, MAX_AMMO_45ACP      }, // ARMOURY_MAC10
	{ "weapon_ak47",      "762Nato",    60, MAX_AMMO_762NATO    }, // ARMOURY_AK47
	{ "weapon_sg552",     "556Nato",    60, MAX_AMMO_556NATO    }, // ARMOURY_SG552
	{ "weapon_m4a1",      "556Nato",    60, MAX_AMMO_556NATO    }, // ARMOURY_M4A1
	{ "weapon_aug",       "556Nato",    60, MAX_AMMO_556NATO    }, // ARMOURY_AUG
	{ "weapon_scout",     "762Nato",    30, MAX_AMMO_762NATO    }, // ARMOURY_SCOUT
	{ "weapon_g3sg1",     "762Nato",    30, MAX_AMMO_762NATO    }, // ARMOURY_G3SG1
	{ "weapon_awp",       "338Magnum",  20, MAX_AMMO_338MAGNUM  }, // ARMOURY_AWP
	{ "weapon_m3",        "buckshot",   24, MAX_AMMO_BUCKSHOT   }, // ARMOURY_M3
	{ "weapon_xm1014",    "buckshot",   24, MAX_AMMO_BUCKSHOT   }, // ARMOURY_XM1014
	{ "weapon_m249",      "556NatoBox", 60, MAX_AMMO_556NATOBOX }, // ARMOURY_M249
	{ nullptr,            nullptr,      0,  0                   }, // ARMOURY_FLASHBANG
	{ nullptr,            nullptr,      0,  0                   }, // ARMOURY_HEGRENADE
	{ nullptr,            nullptr,      0,  0                   }, // ARMOURY_KEVLAR
	{ nullptr,            nullptr,      0,  0                   }, // ARMOURY_ASSAULT
	{ nullptr,            nullptr,      0,  0                   }, // ARMOURY_SMOKEGRENADE
	{ nullptr,            nullptr,      0,  0                   }, // ARMOURY_SHIELD
	{ "weapon_famas",     "556Nato",    90,  MAX_AMMO_556NATO   }, // ARMOURY_FAMAS
	{ "weapon_sg550",     "556Nato",    90,  MAX_AMMO_556NATO   }, // ARMOURY_SG550
	{ "weapon_galil",     "556Nato",    90,  MAX_AMMO_556NATO   }, // ARMOURY_GALIL
	{ "weapon_ump45",     "45acp",      100, MAX_AMMO_45ACP     }, // ARMOURY_UMP45
	{ "weapon_glock18",   "9mm",        120, MAX_AMMO_9MM       }, // ARMOURY_GLOCK18
	{ "weapon_usp",       "45acp",      100, MAX_AMMO_45ACP     }, // ARMOURY_USP
	{ "weapon_elite",     "9mm",        120, MAX_AMMO_9MM       }, // ARMOURY_ELITE
	{ "weapon_fiveseven", "57mm",       100, MAX_AMMO_57MM      }, // ARMOURY_FIVESEVEN
	{ "weapon_p228",      "357SIG",     52,  MAX_AMMO_357SIG    }, // ARMOURY_P228
	{ "weapon_deagle",    "50AE",       35,  MAX_AMMO_50AE      }, // ARMOURY_DEAGLE
};

void CArmoury::ArmouryTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pToucher = static_cast<CBasePlayer *>(pOther);

	if (pToucher->m_bIsVIP)
		return;

#ifdef REGAMEDLL_ADD
	if (pToucher->HasRestrictItem(GetItemIdByArmoury(m_iItem), ITEM_TYPE_TOUCHED))
		return;
#endif

#ifdef REGAMEDLL_FIXES
	if (pToucher->IsBot() && TheCSBots() && !TheCSBots()->IsWeaponUseable(m_iItem))
		return;
#endif

	// primary weapons
	if (m_iCount > 0 && (m_iItem <= ARMOURY_M249
#ifdef REGAMEDLL_ADD
		|| (m_iItem >= ARMOURY_FAMAS && m_iItem <= ARMOURY_UMP45)
#endif
))
	{
		if (pToucher->m_bHasPrimary)
			return;

		m_iCount--;
		auto item = &armouryItemInfo[m_iItem];

#ifdef REGAMEDLL_FIXES
		pToucher->GiveNamedItemEx(item->entityName);
#else
		pToucher->GiveNamedItem(item->entityName);
#endif

		pToucher->GiveAmmo(item->giveAmount, item->ammoName, item->maxRounds);
	}
#ifdef REGAMEDLL_ADD
	// secondary weapons (pistols)
	else if (m_iCount > 0 && m_iItem >= ARMOURY_GLOCK18)
	{
		if (pToucher->m_rgpPlayerItems[PISTOL_SLOT])
			return;

		if (pToucher->HasShield() && m_iItem == ARMOURY_ELITE)
			return;

		m_iCount--;
		auto item = &armouryItemInfo[m_iItem];

		pToucher->GiveNamedItemEx(item->entityName);
		pToucher->GiveAmmo(item->giveAmount, item->ammoName, item->maxRounds);
	}
#endif
	// items & grenades
	else if (m_iCount > 0 && m_iItem >= ARMOURY_FLASHBANG)
	{
		switch (m_iItem)
		{
		case ARMOURY_FLASHBANG:
		{
			if (pToucher->AmmoInventory(AMMO_FLASHBANG) >= MaxAmmoCarry(WEAPON_FLASHBANG))
				return;

			pToucher->GiveNamedItem("weapon_flashbang");
			m_iCount--;
			break;
		}
		case ARMOURY_HEGRENADE:
		{
			if (pToucher->AmmoInventory(AMMO_HEGRENADE) >= MaxAmmoCarry(WEAPON_HEGRENADE))
				return;

			pToucher->GiveNamedItem("weapon_hegrenade");
			m_iCount--;
			break;
		}
		case ARMOURY_KEVLAR:
		{

#ifdef REGAMEDLL_FIXES
			if (pToucher->m_iKevlar != ARMOR_NONE && pToucher->pev->armorvalue >= MAX_NORMAL_BATTERY)
#else
			if (pToucher->m_iKevlar == ARMOR_KEVLAR)
#endif
			{
				return;
			}

			pToucher->GiveNamedItem("item_kevlar");
			m_iCount--;
			break;
		}
		case ARMOURY_ASSAULT:
		{
			if (pToucher->m_iKevlar == ARMOR_VESTHELM
#ifdef REGAMEDLL_FIXES
				&& pToucher->pev->armorvalue >= MAX_NORMAL_BATTERY
#endif
				)
			{
				return;
			}

			pToucher->GiveNamedItem("item_assaultsuit");
			m_iCount--;
			break;
		}
		case ARMOURY_SMOKEGRENADE:
		{
			if (pToucher->AmmoInventory(AMMO_SMOKEGRENADE) >= MaxAmmoCarry(WEAPON_SMOKEGRENADE))
				return;

			pToucher->GiveNamedItem("weapon_smokegrenade");
			m_iCount--;
			break;
		}
#ifdef REGAMEDLL_ADD
		case ARMOURY_SHIELD:
		{
			if (pToucher->m_bHasPrimary || (pToucher->m_rgpPlayerItems[PISTOL_SLOT] && pToucher->GetItemById(WEAPON_ELITE)))
				return;

			pToucher->GiveNamedItemEx("weapon_shield");
			m_iCount--;
			break;
		}
#endif
		}
	}

	if (!m_iCount)
		Hide();
}

void CArmoury::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "item"))
	{
		m_iItem = (ArmouryItemPack)Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "count"))
	{
		m_iCount = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

#ifdef REGAMEDLL_FIXES
void CArmoury::SetObjectCollisionBox()
{
	pev->absmin = pev->origin + Vector(-16, -16, 0);
	pev->absmax = pev->origin + Vector(16, 16, 16);
}
#endif

LINK_ENTITY_TO_CLASS(armoury_entity, CArmoury, CCSArmoury)

#ifdef REGAMEDLL_API
#define m_ItemInfoEx CSPlayerItem()->m_ItemInfo
#else
#define m_ItemInfoEx m_ItemInfoArray[m_iId]
#endif

const char *CBasePlayerItem::pszAmmo1() const
{
	return m_ItemInfoEx.pszAmmo1;
}

int CBasePlayerItem::iMaxAmmo1() const
{
	return m_ItemInfoEx.iMaxAmmo1;
}

const char *CBasePlayerItem::pszAmmo2() const
{
	return m_ItemInfoEx.pszAmmo2;
}

int CBasePlayerItem::iMaxAmmo2() const
{
	return m_ItemInfoEx.iMaxAmmo2;
}

const char *CBasePlayerItem::pszName() const
{
	return m_ItemInfoEx.pszName;
}

int CBasePlayerItem::iMaxClip() const
{
	return m_ItemInfoEx.iMaxClip;
}

int CBasePlayerItem::iWeight() const
{
	return m_ItemInfoEx.iWeight;
}

int CBasePlayerItem::iFlags() const
{
	return m_ItemInfoEx.iFlags;
}

