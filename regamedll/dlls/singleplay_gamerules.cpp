#include "precompiled.h"

CHalfLifeRules::CHalfLifeRules()
{
	m_bFreezePeriod = FALSE;
	RefreshSkillData();
}

void CHalfLifeRules::__MAKE_VHOOK(Think)()
{
	;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(IsMultiplayer)()
{
	return FALSE;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(IsDeathmatch)()
{
	return FALSE;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(IsCoOp)()
{
	return FALSE;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(FShouldSwitchWeapon)(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	if (!pPlayer->m_pActiveItem)
	{
		// player doesn't have an active item!
		return TRUE;
	}

	if (!pPlayer->m_pActiveItem->CanHolster())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(GetNextBestWeapon)(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	return FALSE;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(ClientConnected)(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
	return TRUE;
}

void CHalfLifeRules::__MAKE_VHOOK(InitHUD)(CBasePlayer *pl)
{
	;
}

void CHalfLifeRules::__MAKE_VHOOK(ClientDisconnected)(edict_t *pClient)
{
	;
}

float CHalfLifeRules::__MAKE_VHOOK(FlPlayerFallDamage)(CBasePlayer *pPlayer)
{
	// subtract off the speed at which a player is allowed to fall without being hurt,
	// so damage will be based on speed beyond that, not the entire fall
	pPlayer->m_flFallVelocity -= PLAYER_MAX_SAFE_FALL_SPEED;
	return pPlayer->m_flFallVelocity * DAMAGE_FOR_FALL_SPEED;
}

void CHalfLifeRules::__MAKE_VHOOK(PlayerSpawn)(CBasePlayer *pPlayer)
{
	pPlayer->pev->weapons |= (1 << WEAPON_SUIT);

	pPlayer->GiveNamedItem("weapon_knife");
	pPlayer->GiveNamedItem("weapon_usp");
	pPlayer->GiveNamedItem("weapon_mp5navy");
	pPlayer->GiveNamedItem("weapon_hegrenade");

	pPlayer->GiveAmmo(60, "9mm", 120);
	pPlayer->GiveAmmo(24, "45acp", 100);
}

BOOL CHalfLifeRules::__MAKE_VHOOK(AllowAutoTargetCrosshair)()
{
	return (g_iSkillLevel == SKILL_EASY);
}

void CHalfLifeRules::__MAKE_VHOOK(PlayerThink)(CBasePlayer *pPlayer)
{
	;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(FPlayerCanRespawn)(CBasePlayer *pPlayer)
{
	return TRUE;
}

float CHalfLifeRules::__MAKE_VHOOK(FlPlayerSpawnTime)(CBasePlayer *pPlayer)
{
	return gpGlobals->time;
}

int CHalfLifeRules::__MAKE_VHOOK(IPointsForKill)(CBasePlayer *pAttacker, CBasePlayer *pKilled)
{
	return 1;
}

void CHalfLifeRules::__MAKE_VHOOK(PlayerKilled)(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	;
}

void CHalfLifeRules::__MAKE_VHOOK(DeathNotice)(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	;
}

void CHalfLifeRules::__MAKE_VHOOK(PlayerGotWeapon)(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	;
}

float CHalfLifeRules::__MAKE_VHOOK(FlWeaponRespawnTime)(CBasePlayerItem *pWeapon)
{
	return -1;
}

float CHalfLifeRules::__MAKE_VHOOK(FlWeaponTryRespawn)(CBasePlayerItem *pWeapon)
{
	return 0;
}

Vector CHalfLifeRules::__MAKE_VHOOK(VecWeaponRespawnSpot)(CBasePlayerItem *pWeapon)
{
	return pWeapon->pev->origin;
}

edict_t *CHalfLifeRules::__MAKE_VHOOK(GetPlayerSpawnSpot)(CBasePlayer *pPlayer)
{
	CBaseEntity *pSpot = UTIL_FindEntityByClassname(NULL, "info_player_start");

	if (!pSpot)
	{
		ALERT(at_error, "PutClientInServer: no info_player_start on level");
		return INDEXENT(0);
	}

	pPlayer->pev->origin = pSpot->pev->origin + Vector(0, 0, 1);
	pPlayer->pev->v_angle  = g_vecZero;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->angles = pSpot->pev->angles;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->pev->fixangle = 1;

	return pSpot->edict();
}

int CHalfLifeRules::__MAKE_VHOOK(WeaponShouldRespawn)(CBasePlayerItem *pWeapon)
{
	return GR_WEAPON_RESPAWN_NO;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(CanHaveItem)(CBasePlayer *pPlayer, CItem *pItem)
{
	return TRUE;
}

void CHalfLifeRules::__MAKE_VHOOK(PlayerGotItem)(CBasePlayer *pPlayer, CItem *pItem)
{
	;
}

int CHalfLifeRules::__MAKE_VHOOK(ItemShouldRespawn)(CItem *pItem)
{
	return GR_ITEM_RESPAWN_NO;
}

float CHalfLifeRules::__MAKE_VHOOK(FlItemRespawnTime)(CItem *pItem)
{
	return -1;
}

Vector CHalfLifeRules::__MAKE_VHOOK(VecItemRespawnSpot)(CItem *pItem)
{
	return pItem->pev->origin;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(IsAllowedToSpawn)(CBaseEntity *pEntity)
{
	return TRUE;
}

void CHalfLifeRules::__MAKE_VHOOK(PlayerGotAmmo)(CBasePlayer *pPlayer, char *szName, int iCount)
{
	;
}

int CHalfLifeRules::__MAKE_VHOOK(AmmoShouldRespawn)(CBasePlayerAmmo *pAmmo)
{
	return GR_AMMO_RESPAWN_NO;
}

float CHalfLifeRules::__MAKE_VHOOK(FlAmmoRespawnTime)(CBasePlayerAmmo *pAmmo)
{
	return -1;
}

Vector CHalfLifeRules::__MAKE_VHOOK(VecAmmoRespawnSpot)(CBasePlayerAmmo *pAmmo)
{
	return pAmmo->pev->origin;
}

float CHalfLifeRules::__MAKE_VHOOK(FlHealthChargerRechargeTime)()
{
	return 0;
}

int CHalfLifeRules::__MAKE_VHOOK(DeadPlayerWeapons)(CBasePlayer *pPlayer)
{
	return GR_PLR_DROP_GUN_NO;
}

int CHalfLifeRules::__MAKE_VHOOK(DeadPlayerAmmo)(CBasePlayer *pPlayer)
{
	return GR_PLR_DROP_AMMO_NO;
}

int CHalfLifeRules::__MAKE_VHOOK(PlayerRelationship)(CBasePlayer *pPlayer, CBaseEntity *pTarget)
{
	// why would a single player in half life need this?
	return GR_NOTTEAMMATE;
}

BOOL CHalfLifeRules::__MAKE_VHOOK(FAllowMonsters)()
{
	return TRUE;
}
