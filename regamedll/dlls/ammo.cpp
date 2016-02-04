#include "precompiled.h"

/* <a6c7> ../cstrike/dlls/ammo.cpp:16 */
void C9MMAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a3e2> ../cstrike/dlls/ammo.cpp:22 */
void C9MMAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <a861> ../cstrike/dlls/ammo.cpp:27 */
BOOL C9MMAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_9MM_BUY, "9mm", MAX_AMMO_9MM) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <ace9> ../cstrike/dlls/ammo.cpp:37 */
LINK_ENTITY_TO_CLASS(ammo_9mm, C9MMAmmo);

/* <a6a0> ../cstrike/dlls/ammo.cpp:42 */
void CBuckShotAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_shotbox.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a409> ../cstrike/dlls/ammo.cpp:48 */
void CBuckShotAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_shotbox.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <a7d0> ../cstrike/dlls/ammo.cpp:53 */
BOOL CBuckShotAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_BUCKSHOT_BUY, "buckshot", MAX_AMMO_BUCKSHOT) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <adb3> ../cstrike/dlls/ammo.cpp:63 */
LINK_ENTITY_TO_CLASS(ammo_buckshot, CBuckShotAmmo);

/* <a679> ../cstrike/dlls/ammo.cpp:69 */
void C556NatoAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a430> ../cstrike/dlls/ammo.cpp:75 */
void C556NatoAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <a8f2> ../cstrike/dlls/ammo.cpp:80 */
BOOL C556NatoAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_556NATO_BUY, "556Nato", MAX_AMMO_556NATO) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <ae7d> ../cstrike/dlls/ammo.cpp:90 */
LINK_ENTITY_TO_CLASS(ammo_556nato, C556NatoAmmo);

/* <a652> ../cstrike/dlls/ammo.cpp:95 */
void C556NatoBoxAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a457> ../cstrike/dlls/ammo.cpp:101 */
void C556NatoBoxAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <a983> ../cstrike/dlls/ammo.cpp:106 */
BOOL C556NatoBoxAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_556NATOBOX_BUY, "556NatoBox", MAX_AMMO_556NATOBOX) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <af47> ../cstrike/dlls/ammo.cpp:116 */
LINK_ENTITY_TO_CLASS(ammo_556natobox, C556NatoBoxAmmo);

/* <a62b> ../cstrike/dlls/ammo.cpp:121 */
void C762NatoAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a47e> ../cstrike/dlls/ammo.cpp:127 */
void C762NatoAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <aa14> ../cstrike/dlls/ammo.cpp:132 */
BOOL C762NatoAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_762NATO_BUY, "762Nato", MAX_AMMO_762NATO) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <b011> ../cstrike/dlls/ammo.cpp:142 */
LINK_ENTITY_TO_CLASS(ammo_762nato, C762NatoAmmo);

/* <a604> ../cstrike/dlls/ammo.cpp:147 */
void C45ACPAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a4a5> ../cstrike/dlls/ammo.cpp:153 */
void C45ACPAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <aaa5> ../cstrike/dlls/ammo.cpp:158 */
BOOL C45ACPAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_45ACP_BUY, "45acp", MAX_AMMO_45ACP) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <b0db> ../cstrike/dlls/ammo.cpp:168 */
LINK_ENTITY_TO_CLASS(ammo_45acp, C45ACPAmmo);

/* <a5dd> ../cstrike/dlls/ammo.cpp:173 */
void C50AEAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a4cc> ../cstrike/dlls/ammo.cpp:179 */
void C50AEAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <ab36> ../cstrike/dlls/ammo.cpp:184 */
BOOL C50AEAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_50AE_BUY, "50AE", MAX_AMMO_50AE) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <b1a5> ../cstrike/dlls/ammo.cpp:194 */
LINK_ENTITY_TO_CLASS(ammo_50ae, C50AEAmmo);

/* <a5b6> ../cstrike/dlls/ammo.cpp:199 */
void C338MagnumAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a4f3> ../cstrike/dlls/ammo.cpp:205 */
void C338MagnumAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <abc7> ../cstrike/dlls/ammo.cpp:210 */
BOOL C338MagnumAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_338MAG_BUY, "338Magnum", MAX_AMMO_338MAGNUM) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <b26f> ../cstrike/dlls/ammo.cpp:220 */
LINK_ENTITY_TO_CLASS(ammo_338magnum, C338MagnumAmmo);

/* <a58f> ../cstrike/dlls/ammo.cpp:226 */
void C57MMAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a51a> ../cstrike/dlls/ammo.cpp:232 */
void C57MMAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <ac58> ../cstrike/dlls/ammo.cpp:237 */
BOOL C57MMAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_57MM_BUY, "57mm", MAX_AMMO_57MM) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <b339> ../cstrike/dlls/ammo.cpp:247 */
LINK_ENTITY_TO_CLASS(ammo_57mm, C57MMAmmo);

/* <a568> ../cstrike/dlls/ammo.cpp:251 */
void C357SIGAmmo::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_9mmclip.mdl");
	CBasePlayerAmmo::Spawn();
}

/* <a541> ../cstrike/dlls/ammo.cpp:257 */
void C357SIGAmmo::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_9mmclip.mdl");
	PRECACHE_SOUND("items/9mmclip1.wav");
}

/* <a73d> ../cstrike/dlls/ammo.cpp:262 */
BOOL C357SIGAmmo::__MAKE_VHOOK(AddAmmo)(CBaseEntity *pOther)
{
	if (pOther->GiveAmmo(AMMO_357SIG_BUY, "357SIG", MAX_AMMO_357SIG) == -1)
	{
		return FALSE;
	}

	EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	return TRUE;
}

/* <b403> ../cstrike/dlls/ammo.cpp:272 */
LINK_ENTITY_TO_CLASS(ammo_357sig, C357SIGAmmo);
