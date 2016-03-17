#include "precompiled.h"

void C9MMAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C9MMAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C9MMAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_9MM_BUY, "9mm", MAX_AMMO_9MM) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_9mm, C9MMAmmo, CCS9MMAmmo);

void CBuckShotAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_shotbox.mdl");
	CBasePlayerAmmo::Spawn();
}

void CBuckShotAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_shotbox.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL CBuckShotAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_BUCKSHOT_BUY, "buckshot", MAX_AMMO_BUCKSHOT) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_buckshot, CBuckShotAmmo, CCSBuckShotAmmo);

void C556NatoAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C556NatoAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C556NatoAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_556NATO_BUY, "556Nato", MAX_AMMO_556NATO) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_556nato, C556NatoAmmo, CCS556NatoAmmo);

void C556NatoBoxAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C556NatoBoxAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C556NatoBoxAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_556NATOBOX_BUY, "556NatoBox", MAX_AMMO_556NATOBOX) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_556natobox, C556NatoBoxAmmo, CCS556NatoBoxAmmo);

void C762NatoAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C762NatoAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C762NatoAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_762NATO_BUY, "762Nato", MAX_AMMO_762NATO) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_762nato, C762NatoAmmo, CCS762NatoAmmo);

void C45ACPAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C45ACPAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C45ACPAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_45ACP_BUY, "45acp", MAX_AMMO_45ACP) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_45acp, C45ACPAmmo, CCS45ACPAmmo);

void C50AEAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C50AEAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C50AEAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_50AE_BUY, "50AE", MAX_AMMO_50AE) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_50ae, C50AEAmmo, CCS50AEAmmo);

void C338MagnumAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C338MagnumAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C338MagnumAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_338MAG_BUY, "338Magnum", MAX_AMMO_338MAGNUM) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_338magnum, C338MagnumAmmo, CCS338MagnumAmmo);

void C57MMAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C57MMAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C57MMAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_57MM_BUY, "57mm", MAX_AMMO_57MM) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_57mm, C57MMAmmo, CCS57MMAmmo);

void C357SIGAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

void C357SIGAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

BOOL C357SIGAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_357SIG_BUY, "357SIG", MAX_AMMO_357SIG) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

LINK_ENTITY_TO_CLASS(ammo_357sig, C357SIGAmmo, CCS357SIGAmmo);
