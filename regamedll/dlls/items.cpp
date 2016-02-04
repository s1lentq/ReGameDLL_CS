#include "precompiled.h"

/* <e2209> ../cstrike/dlls/items.cpp:46 */
LINK_ENTITY_TO_CLASS(world_items, CWorldItem);

/* <e173b> ../cstrike/dlls/items.cpp:48 */
void CWorldItem::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "type"))
	{
		m_iType = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <e163a> ../cstrike/dlls/items.cpp:59 */
void CWorldItem::__MAKE_VHOOK(Spawn)()
{
	CBaseEntity *pEntity = NULL;

	switch (m_iType)
	{
	case 41: // ITEM_HEALTHKIT
		break;
	case 42: // ITEM_ANTIDOTE
		pEntity = CBaseEntity::Create("item_antidote", pev->origin, pev->angles);
		break;
	case 43: // ITEM_SECURITY
		pEntity = CBaseEntity::Create("item_security", pev->origin, pev->angles);
		break;
	case 44: // ITEM_BATTERY
		pEntity = CBaseEntity::Create("item_battery", pev->origin, pev->angles);
		break;
	case 45: // ITEM_SUIT
		pEntity = CBaseEntity::Create("item_suit", pev->origin, pev->angles);
		break;
	}

	if (pEntity != NULL)
	{
		pEntity->pev->target = pev->target;
		pEntity->pev->targetname = pev->targetname;
		pEntity->pev->spawnflags = pev->spawnflags;
	}

	REMOVE_ENTITY(edict());
}

/* <e15a6> ../cstrike/dlls/items.cpp:94 */
void CItem::__MAKE_VHOOK(Spawn)()
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));

	SetTouch(&CItem::ItemTouch);

	if (!DROP_TO_FLOOR(ENT(pev)))
	{
		UTIL_Remove(this);
		return;
	}
}

/* <e16d4> ../cstrike/dlls/items.cpp:112 */
void CItem::ItemTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer() || pOther->pev->deadflag != DEAD_NO)
		return;

	CBasePlayer *pPlayer = (CBasePlayer *)pOther;

	if (!g_pGameRules->CanHaveItem(pPlayer, this))
		return;

	if (MyTouch(pPlayer))
	{
		SUB_UseTargets(pOther, USE_TOGGLE, 0);
		SetTouch(NULL);
		g_pGameRules->PlayerGotItem(pPlayer, this);

		if (g_pGameRules->ItemShouldRespawn(this) == GR_ITEM_RESPAWN_YES)
			Respawn();
		else
			UTIL_Remove(this);
	}
	else if (gEvilImpulse101)
		UTIL_Remove(this);
}

/* <e1566> ../cstrike/dlls/items.cpp:154 */
CBaseEntity *CItem::__MAKE_VHOOK(Respawn)()
{
	SetTouch(NULL);

	pev->effects |= EF_NODRAW;

	// blip to whereever you should respawn.
	UTIL_SetOrigin(pev, g_pGameRules->VecItemRespawnSpot(this));

	SetThink(&CItem::Materialize);
	pev->nextthink = g_pGameRules->FlItemRespawnTime(this);

	return this;
}

/* <e1509> ../cstrike/dlls/items.cpp:166 */
void CItem::Materialize()
{
	if (pev->effects & EF_NODRAW)
	{
		// changing from invisible state to visible.
		EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, "items/suitchargeok1.wav", VOL_NORM, ATTN_NORM, 0, 150);

		pev->effects &= ~EF_NODRAW;
		pev->effects |= EF_MUZZLEFLASH;
	}

	SetTouch(&CItem::ItemTouch);
}

/* <e2158> ../cstrike/dlls/items.cpp:190 */
void CItemSuit::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_kevlar.mdl");
	CItem::Spawn();
}

/* <e13a2> ../cstrike/dlls/items.cpp:196 */
void CItemSuit::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_kevlar.mdl");
	PRECACHE_SOUND("items/tr_kevlar.wav");
}

/* <e1b04> ../cstrike/dlls/items.cpp:201 */
BOOL CItemSuit::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	if (pPlayer->pev->weapons & (1 << WEAPON_SUIT))
		return FALSE;

	EMIT_SOUND(pPlayer->edict(), CHAN_VOICE, "items/tr_kevlar.wav", VOL_NORM, ATTN_NORM);

	pPlayer->pev->weapons |= (1 << WEAPON_SUIT);
	pPlayer->m_iHideHUD &= ~(HIDEHUD_HEALTH | HIDEHUD_MONEY);

	return TRUE;
}

/* <e22d3> ../cstrike/dlls/items.cpp:216 */
LINK_ENTITY_TO_CLASS(item_suit, CItemSuit);

/* <e20a7> ../cstrike/dlls/items.cpp:221 */
void CItemBattery::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_battery.mdl");
	CItem::Spawn();
}

/* <e13c9> ../cstrike/dlls/items.cpp:227 */
void CItemBattery::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_battery.mdl");
	PRECACHE_SOUND("items/gunpickup2.wav");
}

/* <e1a20> ../cstrike/dlls/items.cpp:232 */
BOOL CItemBattery::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	if (pPlayer->pev->armorvalue < MAX_NORMAL_BATTERY && (pPlayer->pev->weapons & (1 << WEAPON_SUIT)))
	{
		int pct;
		char szcharge[64];

		pPlayer->pev->armorvalue += gSkillData.batteryCapacity;
		pPlayer->pev->armorvalue = Q_min(pPlayer->pev->armorvalue, MAX_NORMAL_BATTERY);

		EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);

		MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, NULL, pPlayer->pev);
			WRITE_STRING(STRING(pev->classname));
		MESSAGE_END();

		// Suit reports new power level
		// For some reason this wasn't working in release build -- round it.
		pct = (int)((float)(pPlayer->pev->armorvalue * 100.0f) * (1.0f / MAX_NORMAL_BATTERY) + 0.5f);
		pct = (pct / 5);

		if (pct > 0)
			pct--;

		Q_sprintf(szcharge,"!HEV_%1dP", pct);
		pPlayer->SetSuitUpdate(szcharge, FALSE, SUIT_NEXT_IN_30SEC);

		return TRUE;
	}
	return FALSE;
}

/* <e239d> ../cstrike/dlls/items.cpp:266 */
LINK_ENTITY_TO_CLASS(item_battery, CItemBattery);

/* <e1ff5> ../cstrike/dlls/items.cpp:271 */
void CItemAntidote::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_antidote.mdl");
	CItem::Spawn();
}

/* <e13f0> ../cstrike/dlls/items.cpp:277 */
void CItemAntidote::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_antidote.mdl");
}

/* <e1530> ../cstrike/dlls/items.cpp:281 */
BOOL CItemAntidote::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	pPlayer->SetSuitUpdate("!HEV_DET4", FALSE, SUIT_NEXT_IN_1MIN);
	pPlayer->m_rgItems[ ITEM_ANTIDOTE ] += 1;

	return TRUE;
}

/* <e246a> ../cstrike/dlls/items.cpp:290 */
LINK_ENTITY_TO_CLASS(item_antidote, CItemAntidote);

/* <e1f43> ../cstrike/dlls/items.cpp:295 */
void CItemSecurity::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_security.mdl");
	CItem::Spawn();
}

/* <e1416> ../cstrike/dlls/items.cpp:301 */
void CItemSecurity::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_security.mdl");
}

/* <e143c> ../cstrike/dlls/items.cpp:305 */
BOOL CItemSecurity::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	pPlayer->m_rgItems[ ITEM_SECURITY ] += 1;
	return TRUE;
}

/* <e2537> ../cstrike/dlls/items.cpp:312 */
LINK_ENTITY_TO_CLASS(item_security, CItemSecurity);

/* <e1e91> ../cstrike/dlls/items.cpp:316 */
void CItemLongJump::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_longjump.mdl");
	CItem::Spawn();
}

/* <e1471> ../cstrike/dlls/items.cpp:322 */
void CItemLongJump::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_longjump.mdl");
}

/* <e17e9> ../cstrike/dlls/items.cpp:326 */
BOOL CItemLongJump::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	if (pPlayer->m_fLongJump)
		return FALSE;

	if (pPlayer->pev->weapons & (1 << WEAPON_SUIT))
	{
		// player now has longjump module
		pPlayer->m_fLongJump = TRUE;
		SET_PHYSICS_KEY_VALUE(pPlayer->edict(), "slj", "1");

		MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, NULL, pPlayer->pev);
			WRITE_STRING(STRING(pev->classname));
		MESSAGE_END();

		// Play the longjump sound UNDONE: Kelly? correct sound?
		EMIT_SOUND_SUIT(pPlayer->edict(), "!HEV_A1");
		return TRUE;
	}

	return FALSE;
}

/* <e2604> ../cstrike/dlls/items.cpp:350 */
LINK_ENTITY_TO_CLASS(item_longjump, CItemLongJump);

/* <e1ddf> ../cstrike/dlls/items.cpp:354 */
void CItemKevlar::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_kevlar.mdl");
	CItem::Spawn();
}

/* <e1497> ../cstrike/dlls/items.cpp:360 */
void CItemKevlar::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_kevlar.mdl");
}

/* <e1b9d> ../cstrike/dlls/items.cpp:364 */
BOOL CItemKevlar::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	if (pPlayer->m_iKevlar == ARMOR_TYPE_EMPTY)
		pPlayer->m_iKevlar = ARMOR_TYPE_KEVLAR;

	pPlayer->pev->armorvalue = 100;
	EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/ammopickup2.wav", VOL_NORM, ATTN_NORM);

	MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, NULL, pPlayer->pev);
		WRITE_STRING(STRING(pev->classname));
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgArmorType, NULL, pPlayer->pev);
		WRITE_BYTE(0);
	MESSAGE_END();

	if (TheTutor != NULL)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return TRUE;
}

/* <e26d1> ../cstrike/dlls/items.cpp:390 */
LINK_ENTITY_TO_CLASS(item_kevlar, CItemKevlar);

/* <e1d2d> ../cstrike/dlls/items.cpp:395 */
void CItemAssaultSuit::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_assault.mdl");
	CItem::Spawn();
}

/* <e14bd> ../cstrike/dlls/items.cpp:401 */
void CItemAssaultSuit::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_assault.mdl");
}

/* <e1942> ../cstrike/dlls/items.cpp:405 */
BOOL CItemAssaultSuit::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	pPlayer->m_iKevlar = ARMOR_TYPE_HELMET;
	pPlayer->pev->armorvalue = 100;

	EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/ammopickup2.wav", VOL_NORM, ATTN_NORM);

	MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, NULL, pPlayer->pev);
		WRITE_STRING(STRING(pev->classname));
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgArmorType, NULL, pPlayer->pev);
		WRITE_BYTE(1);
	MESSAGE_END();

	if (TheTutor != NULL)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return TRUE;
}

/* <e279e> ../cstrike/dlls/items.cpp:429 */
LINK_ENTITY_TO_CLASS(item_assaultsuit, CItemAssaultSuit);

/* <e1c7b> ../cstrike/dlls/items.cpp:434 */
void CItemThighPack::__MAKE_VHOOK(Spawn)()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_thighpack.mdl");
	CItem::Spawn();
}

/* <e14e3> ../cstrike/dlls/items.cpp:440 */
void CItemThighPack::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/w_thighpack.mdl");
}

/* <e1873> ../cstrike/dlls/items.cpp:444 */
BOOL CItemThighPack::__MAKE_VHOOK(MyTouch)(CBasePlayer *pPlayer)
{
	if (pPlayer->m_iTeam != CT || pPlayer->m_bHasDefuser)
		return FALSE;

	pPlayer->m_bHasDefuser = true;
	pPlayer->pev->body = 1;

	ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Got_defuser");

	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pPlayer->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("defuser");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	SendItemStatus(pPlayer);
	EMIT_SOUND(pPlayer->edict(), CHAN_VOICE, "items/kevlar.wav", VOL_NORM, ATTN_NORM);

	if (TheTutor != NULL)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return TRUE;
}

/* <e286b> ../cstrike/dlls/items.cpp:474 */
LINK_ENTITY_TO_CLASS(item_thighpack, CItemThighPack);
