#include "precompiled.h"

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

BOOL C9MMAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_9MM_BUY, "9mm") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL CBuckShotAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_BUCKSHOT_BUY, "buckshot") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C556NatoAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_556NATO_BUY, "556Nato") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C556NatoBoxAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_556NATOBOX_BUY, "556NatoBox") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C762NatoAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_762NATO_BUY, "762Nato") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C45ACPAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_45ACP_BUY, "45acp") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C50AEAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_50AE_BUY, "50AE") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C338MagnumAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_338MAG_BUY, "338Magnum") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C57MMAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_57MM_BUY, "57mm") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
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

BOOL C357SIGAmmo::AddAmmo(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_357SIG_BUY, "357SIG") == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_357sig, C357SIGAmmo, CCS357SIGAmmo)
