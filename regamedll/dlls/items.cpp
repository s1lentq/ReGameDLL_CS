#include "precompiled.h"

ItemInfo itemInfo[] = {
	DEFINE_ITEMINFO(ITEM_SHIELDGUN,     "weapon_shield"),
	DEFINE_ITEMINFO(ITEM_P228,          "weapon_p228"),
	DEFINE_ITEMINFO(ITEM_GLOCK,         "weapon_glock"),
	DEFINE_ITEMINFO(ITEM_SCOUT,         "weapon_scout"),
	DEFINE_ITEMINFO(ITEM_HEGRENADE,     "weapon_hegrenade"),
	DEFINE_ITEMINFO(ITEM_XM1014,        "weapon_xm1014"),
	DEFINE_ITEMINFO(ITEM_C4,            "weapon_c4"),
	DEFINE_ITEMINFO(ITEM_MAC10,         "weapon_mac10"),
	DEFINE_ITEMINFO(ITEM_AUG,           "weapon_aug"),
	DEFINE_ITEMINFO(ITEM_SMOKEGRENADE,  "weapon_smokegrenade"),
	DEFINE_ITEMINFO(ITEM_ELITE,         "weapon_elite"),
	DEFINE_ITEMINFO(ITEM_FIVESEVEN,     "weapon_fiveseven"),
	DEFINE_ITEMINFO(ITEM_UMP45,         "weapon_ump45"),
	DEFINE_ITEMINFO(ITEM_SG550,         "weapon_sg550"),
	DEFINE_ITEMINFO(ITEM_GALIL,         "weapon_galil"),
	DEFINE_ITEMINFO(ITEM_FAMAS,         "weapon_famas"),
	DEFINE_ITEMINFO(ITEM_USP,           "weapon_usp"),
	DEFINE_ITEMINFO(ITEM_GLOCK18,       "weapon_glock18"),
	DEFINE_ITEMINFO(ITEM_AWP,           "weapon_awp"),
	DEFINE_ITEMINFO(ITEM_MP5N,          "weapon_mp5navy"),
	DEFINE_ITEMINFO(ITEM_M249,          "weapon_m249"),
	DEFINE_ITEMINFO(ITEM_M3,            "weapon_m3"),
	DEFINE_ITEMINFO(ITEM_M4A1,          "weapon_m4a1"),
	DEFINE_ITEMINFO(ITEM_TMP,           "weapon_tmp"),
	DEFINE_ITEMINFO(ITEM_G3SG1,         "weapon_g3sg1"),
	DEFINE_ITEMINFO(ITEM_FLASHBANG,     "weapon_flashbang"),
	DEFINE_ITEMINFO(ITEM_DEAGLE,        "weapon_deagle"),
	DEFINE_ITEMINFO(ITEM_SG552,         "weapon_sg552"),
	DEFINE_ITEMINFO(ITEM_AK47,          "weapon_ak47"),
	DEFINE_ITEMINFO(ITEM_KNIFE,         "weapon_knife"),
	DEFINE_ITEMINFO(ITEM_P90,           "weapon_p90"),
	DEFINE_ITEMINFO(ITEM_NVG,           ""),
	DEFINE_ITEMINFO(ITEM_DEFUSEKIT,     "item_thighpack"),
	DEFINE_ITEMINFO(ITEM_KEVLAR,        "item_kevlar"),
	DEFINE_ITEMINFO(ITEM_ASSAULT,       "item_assaultsuit"),
	DEFINE_ITEMINFO(ITEM_LONGJUMP,      "item_longjump"),
	DEFINE_ITEMINFO(ITEM_HEALTHKIT,     "item_healthkit"),
	DEFINE_ITEMINFO(ITEM_ANTIDOTE,      "item_antidote"),
	DEFINE_ITEMINFO(ITEM_BATTERY,       "item_battery"),
};

LINK_ENTITY_TO_CLASS(world_items, CWorldItem, CCSWorldItem)

void CWorldItem::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "type"))
	{
		m_iType = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CWorldItem::Spawn()
{
	CBaseEntity *pEntity = nullptr;

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

	if (pEntity)
	{
		pEntity->pev->target = pev->target;
		pEntity->pev->targetname = pev->targetname;
		pEntity->pev->spawnflags = pev->spawnflags;
	}

	REMOVE_ENTITY(edict());
}

void CItem::Spawn()
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

void CItem::ItemTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer() || pOther->pev->deadflag != DEAD_NO)
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pOther);

	if (!g_pGameRules->CanHaveItem(pPlayer, this))
		return;

	if (MyTouch(pPlayer))
	{
		SUB_UseTargets(pOther, USE_TOGGLE, 0);
		SetTouch(nullptr);
		g_pGameRules->PlayerGotItem(pPlayer, this);

		if (g_pGameRules->ItemShouldRespawn(this) == GR_ITEM_RESPAWN_YES)
			Respawn();
		else
			UTIL_Remove(this);
	}
}

CBaseEntity *CItem::Respawn()
{
	SetTouch(nullptr);

	pev->effects |= EF_NODRAW;

	// blip to whereever you should respawn.
	UTIL_SetOrigin(pev, g_pGameRules->VecItemRespawnSpot(this));

	SetThink(&CItem::Materialize);
	pev->nextthink = g_pGameRules->FlItemRespawnTime(this);

	return this;
}

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

void CItemSuit::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_kevlar.mdl");
	CItem::Spawn();
}

void CItemSuit::Precache()
{
	PRECACHE_MODEL("models/w_kevlar.mdl");
	PRECACHE_SOUND("items/tr_kevlar.wav");
}

BOOL CItemSuit::MyTouch(CBasePlayer *pPlayer)
{
	if (pPlayer->pev->weapons & (1 << WEAPON_SUIT))
		return FALSE;

	EMIT_SOUND(pPlayer->edict(), CHAN_VOICE, "items/tr_kevlar.wav", VOL_NORM, ATTN_NORM);

	pPlayer->pev->weapons |= (1 << WEAPON_SUIT);
	pPlayer->m_iHideHUD &= ~(HIDEHUD_HEALTH | HIDEHUD_MONEY);

	return TRUE;
}

LINK_ENTITY_TO_CLASS(item_suit, CItemSuit, CCSItemSuit)

void CItemBattery::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_battery.mdl");
	CItem::Spawn();
}

void CItemBattery::Precache()
{
	PRECACHE_MODEL("models/w_battery.mdl");
	PRECACHE_SOUND("items/gunpickup2.wav");
}

BOOL CItemBattery::MyTouch(CBasePlayer *pPlayer)
{
#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_BATTERY, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

	if (pPlayer->pev->armorvalue < MAX_NORMAL_BATTERY && (pPlayer->pev->weapons & (1 << WEAPON_SUIT)))
	{
		auto armorValue = gSkillData.batteryCapacity;

#ifdef REGAMEDLL_FIXES
		if (pev->armorvalue != 0.0f) {
			armorValue = pev->armorvalue;
		}

		if (pPlayer->m_iKevlar == ARMOR_NONE)
			pPlayer->m_iKevlar = ARMOR_KEVLAR;
#endif

		pPlayer->pev->armorvalue += armorValue;
		pPlayer->pev->armorvalue = Q_min(pPlayer->pev->armorvalue, MAX_NORMAL_BATTERY);

		EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);

		MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, nullptr, pPlayer->pev);
			WRITE_STRING(STRING(pev->classname));
		MESSAGE_END();

		// Suit reports new power level
		// For some reason this wasn't working in release build -- round it.
		int pct = int(float(pPlayer->pev->armorvalue * 100.0f) * (1.0f / MAX_NORMAL_BATTERY) + 0.5f);
		pct = (pct / 5);

		if (pct > 0)
			pct--;

		char szcharge[64];
		Q_sprintf(szcharge, "!HEV_%1dP", pct);
		pPlayer->SetSuitUpdate(szcharge, SUIT_SENTENCE, SUIT_NEXT_IN_30SEC);

		return TRUE;
	}

	return FALSE;
}

LINK_ENTITY_TO_CLASS(item_battery, CItemBattery, CCSItemBattery)

void CItemAntidote::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_antidote.mdl");
	CItem::Spawn();
}

void CItemAntidote::Precache()
{
	PRECACHE_MODEL("models/w_antidote.mdl");
}

BOOL CItemAntidote::MyTouch(CBasePlayer *pPlayer)
{
#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_ANTIDOTE, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

	pPlayer->SetSuitUpdate("!HEV_DET4", SUIT_SENTENCE, SUIT_NEXT_IN_1MIN);
	pPlayer->m_rgItems[ITEM_ID_ANTIDOTE] += 1;

	return TRUE;
}

LINK_ENTITY_TO_CLASS(item_antidote, CItemAntidote, CCSItemAntidote)

void CItemSecurity::Spawn()
{
	Precache();

	if (pev->model.IsNullOrEmpty())
	{
		// default model
		SET_MODEL(ENT(pev), "models/w_security.mdl");
	}
	else
	{
		// custom model
		SET_MODEL(ENT(pev), pev->model);
	}

	CItem::Spawn();
}

void CItemSecurity::Precache()
{
	if (pev->model.IsNullOrEmpty())
	{
		// default model
		PRECACHE_MODEL("models/w_security.mdl");
		return;
	}

	// custom model
	PRECACHE_MODEL(pev->model);
}

BOOL CItemSecurity::MyTouch(CBasePlayer *pPlayer)
{
	pPlayer->m_rgItems[ITEM_ID_SECURITY] += 1;
	return TRUE;
}

LINK_ENTITY_TO_CLASS(item_security, CItemSecurity, CCSItemSecurity)

void CItemLongJump::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_longjump.mdl");
	CItem::Spawn();
}

void CItemLongJump::Precache()
{
	PRECACHE_MODEL("models/w_longjump.mdl");
}

BOOL CItemLongJump::MyTouch(CBasePlayer *pPlayer)
{
#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_LONGJUMP, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

	if (pPlayer->m_fLongJump)
		return FALSE;

	if (pPlayer->pev->weapons & (1 << WEAPON_SUIT))
	{
		// player now has longjump module
		pPlayer->m_fLongJump = TRUE;
		SET_PHYSICS_KEY_VALUE(pPlayer->edict(), "slj", "1");

		MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, nullptr, pPlayer->pev);
			WRITE_STRING(STRING(pev->classname));
		MESSAGE_END();

		// Play the longjump sound UNDONE: Kelly? correct sound?
		EMIT_SOUND_SUIT(pPlayer->edict(), "!HEV_A1");
		return TRUE;
	}

	return FALSE;
}

LINK_ENTITY_TO_CLASS(item_longjump, CItemLongJump, CCSItemLongJump)

void CItemKevlar::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_kevlar.mdl");
	CItem::Spawn();
}

void CItemKevlar::Precache()
{
	PRECACHE_MODEL("models/w_kevlar.mdl");
}

BOOL CItemKevlar::MyTouch(CBasePlayer *pPlayer)
{
#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_KEVLAR, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

#ifdef REGAMEDLL_FIXES
	if (pPlayer->m_iKevlar != ARMOR_NONE && pPlayer->pev->armorvalue >= MAX_NORMAL_BATTERY)
		return FALSE;
#endif

	if (pPlayer->m_iKevlar == ARMOR_NONE)
		pPlayer->m_iKevlar = ARMOR_KEVLAR;

	pPlayer->pev->armorvalue = MAX_NORMAL_BATTERY;
	EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/ammopickup2.wav", VOL_NORM, ATTN_NORM);

	MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, nullptr, pPlayer->pev);
		WRITE_STRING(STRING(pev->classname));
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgArmorType, nullptr, pPlayer->pev);
#ifdef REGAMEDLL_FIXES
		WRITE_BYTE(pPlayer->m_iKevlar == ARMOR_KEVLAR ? 0 : 1); // 0 = ARMOR_KEVLAR, 1 = ARMOR_VESTHELM
#else
		WRITE_BYTE(0);
#endif
	MESSAGE_END();

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return TRUE;
}

LINK_ENTITY_TO_CLASS(item_kevlar, CItemKevlar, CCSItemKevlar)

void CItemAssaultSuit::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_assault.mdl");
	CItem::Spawn();
}

void CItemAssaultSuit::Precache()
{
	PRECACHE_MODEL("models/w_assault.mdl");
}

BOOL CItemAssaultSuit::MyTouch(CBasePlayer *pPlayer)
{
#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_ASSAULT, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

#ifdef REGAMEDLL_FIXES
	if (pPlayer->m_iKevlar == ARMOR_VESTHELM && pPlayer->pev->armorvalue >= MAX_NORMAL_BATTERY)
		return FALSE;
#endif

	pPlayer->m_iKevlar = ARMOR_VESTHELM;
	pPlayer->pev->armorvalue = MAX_NORMAL_BATTERY;

	EMIT_SOUND(pPlayer->edict(), CHAN_ITEM, "items/ammopickup2.wav", VOL_NORM, ATTN_NORM);

	MESSAGE_BEGIN(MSG_ONE, gmsgItemPickup, nullptr, pPlayer->pev);
		WRITE_STRING(STRING(pev->classname));
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgArmorType, nullptr, pPlayer->pev);
		WRITE_BYTE(1); // 0 = ARMOR_KEVLAR, 1 = ARMOR_VESTHELM
	MESSAGE_END();

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return TRUE;
}

LINK_ENTITY_TO_CLASS(item_assaultsuit, CItemAssaultSuit, CCSItemAssaultSuit)

void CItemThighPack::Spawn()
{
	Precache();
	SET_MODEL(ENT(pev), "models/w_thighpack.mdl");
	CItem::Spawn();
}

void CItemThighPack::Precache()
{
	PRECACHE_MODEL("models/w_thighpack.mdl");
}

BOOL CItemThighPack::MyTouch(CBasePlayer *pPlayer)
{
	if (pPlayer->m_iTeam != CT || pPlayer->m_bHasDefuser)
		return FALSE;

#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem(ITEM_DEFUSEKIT, ITEM_TYPE_TOUCHED))
		return FALSE;
#endif

	pPlayer->m_bHasDefuser = true;
	pPlayer->pev->body = 1;

	ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Got_defuser");

	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("defuser");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	pPlayer->SendItemStatus();
	EMIT_SOUND(pPlayer->edict(), CHAN_VOICE, "items/kevlar.wav", VOL_NORM, ATTN_NORM);

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return TRUE;
}

LINK_ENTITY_TO_CLASS(item_thighpack, CItemThighPack, CCSItemThighPack)

ItemID GetItemIdByName(const char *pszName)
{
	for (auto& item : itemInfo) {
		if (item.pszName[0] != '\0' && FStrEq(item.pszName, pszName))
			return (ItemID)item.iId;
	}

	return ITEM_NONE;
}

ItemID GetItemIdByArmoury(ArmouryItemPack armoury)
{
	switch (armoury)
	{
	case ARMOURY_MP5NAVY: return ITEM_MP5N;
	case ARMOURY_TMP: return ITEM_TMP;
	case ARMOURY_P90: return ITEM_P90;
	case ARMOURY_MAC10: return ITEM_MAC10;
	case ARMOURY_AK47: return ITEM_AK47;
	case ARMOURY_SG552: return ITEM_SG552;
	case ARMOURY_M4A1: return ITEM_M4A1;
	case ARMOURY_AUG: return ITEM_AUG;
	case ARMOURY_SCOUT: return ITEM_SCOUT;
	case ARMOURY_G3SG1: return ITEM_G3SG1;
	case ARMOURY_AWP: return ITEM_AWP;
	case ARMOURY_M3: return ITEM_M3;
	case ARMOURY_XM1014: return ITEM_XM1014;
	case ARMOURY_M249: return ITEM_M249;
	case ARMOURY_FLASHBANG: return ITEM_FLASHBANG;
	case ARMOURY_HEGRENADE: return ITEM_HEGRENADE;
	case ARMOURY_KEVLAR: return ITEM_KEVLAR;
	case ARMOURY_ASSAULT: return ITEM_ASSAULT;
	case ARMOURY_SMOKEGRENADE: return ITEM_SMOKEGRENADE;
	case ARMOURY_SHIELD: return ITEM_SHIELDGUN;
	case ARMOURY_GLOCK18: return ITEM_GLOCK18;
	case ARMOURY_USP: return ITEM_USP;
	case ARMOURY_ELITE: return ITEM_ELITE;
	case ARMOURY_FIVESEVEN: return ITEM_FIVESEVEN;
	case ARMOURY_P228: return ITEM_P228;
	case ARMOURY_DEAGLE: return ITEM_DEAGLE;
	case ARMOURY_FAMAS: return ITEM_FAMAS;
	case ARMOURY_SG550: return ITEM_SG550;
	case ARMOURY_GALIL: return ITEM_GALIL;
	case ARMOURY_UMP45: return ITEM_UMP45;
	default: return ITEM_NONE;
	}
}
