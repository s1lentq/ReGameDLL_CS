#include "precompiled.h"

void CBasePlayerAmmo::Spawn()
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;

	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));
	UTIL_SetOrigin(pev, pev->origin);

	SetTouch(&CBasePlayerAmmo::DefaultTouch);

	if (g_pGameRules->IsMultiplayer())
	{
		SetThink(&CBaseEntity::SUB_Remove);
		pev->nextthink = gpGlobals->time + 2.0f;
	}
}

BOOL CBasePlayerAmmo::AddAmmo(CBaseEntity *pOther)
{
	auto ammoInfo = GetAmmoInfo(pev->classname);
	if (pOther->GiveAmmo(ammoInfo->buyClipSize, ammoInfo->ammoName2) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

CBaseEntity *CBasePlayerAmmo::Respawn()
{
	pev->effects |= EF_NODRAW;
	SetTouch(nullptr);

	// move to wherever I'm supposed to repawn.
	UTIL_SetOrigin(pev, g_pGameRules->VecAmmoRespawnSpot(this));

	SetThink(&CBasePlayerAmmo::Materialize);
	pev->nextthink = g_pGameRules->FlAmmoRespawnTime(this);

	return this;
}

void CBasePlayerAmmo::Materialize()
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

	SetTouch(&CBasePlayerAmmo::DefaultTouch);
}

void CBasePlayerAmmo::DefaultTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	if (AddAmmo(pOther))
	{
		if (g_pGameRules->AmmoShouldRespawn(this) == GR_AMMO_RESPAWN_YES)
		{
			Respawn();
		}
		else
		{
			SetTouch(nullptr);
			SetThink(&CBaseEntity::SUB_Remove);
			pev->nextthink = gpGlobals->time + 0.1f;
#ifdef REGAMEDLL_FIXES
			pev->owner = ENT(pOther->pev);
#endif
		}
	}
}

void C9MMAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C9MMAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_9mm, C9MMAmmo, CCS9MMAmmo)

void CBuckShotAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_shotbox.mdl");
	CBasePlayerAmmo::Spawn();
}

void CBuckShotAmmo::Precache()
{
	PRECACHE_MODEL("models/w_shotbox.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_buckshot, CBuckShotAmmo, CCSBuckShotAmmo)

void C556NatoAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C556NatoAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_556nato, C556NatoAmmo, CCS556NatoAmmo)

void C556NatoBoxAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C556NatoBoxAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_556natobox, C556NatoBoxAmmo, CCS556NatoBoxAmmo)

void C762NatoAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C762NatoAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_762nato, C762NatoAmmo, CCS762NatoAmmo)

void C45ACPAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C45ACPAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_45acp, C45ACPAmmo, CCS45ACPAmmo)

void C50AEAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C50AEAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_50ae, C50AEAmmo, CCS50AEAmmo)

void C338MagnumAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C338MagnumAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_338magnum, C338MagnumAmmo, CCS338MagnumAmmo)

void C57MMAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C57MMAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_57mm, C57MMAmmo, CCS57MMAmmo)

void C357SIGAmmo::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C357SIGAmmo::Precache()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

LINK_ENTITY_TO_CLASS(ammo_357sig, C357SIGAmmo, CCS357SIGAmmo)
