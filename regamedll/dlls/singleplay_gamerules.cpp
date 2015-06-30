#include "precompiled.h"

/* <1676c5> ../cstrike/dlls/singleplay_gamerules.cpp:32 */
CHalfLifeRules::CHalfLifeRules(void)
{
	RefreshSkillData();
}

/* <166d5d> ../cstrike/dlls/singleplay_gamerules.cpp:40 */
void CHalfLifeRules::Think(void)
{
	;
}

/* <166d83> ../cstrike/dlls/singleplay_gamerules.cpp:46 */
BOOL CHalfLifeRules::IsMultiplayer(void)
{
	return FALSE;
}

/* <166da9> ../cstrike/dlls/singleplay_gamerules.cpp:53 */
BOOL CHalfLifeRules::IsDeathmatch(void)
{
	return FALSE;
}

/* <166dcf> ../cstrike/dlls/singleplay_gamerules.cpp:60 */
BOOL CHalfLifeRules::IsCoOp(void)
{
	return FALSE;
}

/* <166df5> ../cstrike/dlls/singleplay_gamerules.cpp:68 */
BOOL CHalfLifeRules::FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
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

/* <166e38> ../cstrike/dlls/singleplay_gamerules.cpp:86 */
BOOL CHalfLifeRules::GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	return FALSE;
}

/* <166e7a> ../cstrike/dlls/singleplay_gamerules.cpp:93 */
BOOL CHalfLifeRules::ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
	return TRUE;
}

/* <166ed8> ../cstrike/dlls/singleplay_gamerules.cpp:98 */
void CHalfLifeRules::InitHUD(CBasePlayer *pl)
{
	;
}

/* <166f0b> ../cstrike/dlls/singleplay_gamerules.cpp:104 */
void CHalfLifeRules::ClientDisconnected(edict_t *pClient)
{
	;
}

/* <166f3f> ../cstrike/dlls/singleplay_gamerules.cpp:110 */
float CHalfLifeRules::FlPlayerFallDamage(CBasePlayer *pPlayer)
{
	pPlayer->m_flFallVelocity -= PLAYER_MAX_SAFE_FALL_SPEED;
	return pPlayer->m_flFallVelocity * DAMAGE_FOR_FALL_SPEED;
}

/* <167677> ../cstrike/dlls/singleplay_gamerules.cpp:120 */
void CHalfLifeRules::PlayerSpawn_(CBasePlayer *pPlayer)
{
	pPlayer->pev->weapons |= (1 << WEAPON_SUIT);

	pPlayer->GiveNamedItem("weapon_knife");
	pPlayer->GiveNamedItem("weapon_usp");
	pPlayer->GiveNamedItem("weapon_mp5navy");
	pPlayer->GiveNamedItem("weapon_hegrenade");

	pPlayer->GiveAmmo(60, "9mm", 120);
	pPlayer->GiveAmmo(24, "45acp", 100);
}

/* <166f73> ../cstrike/dlls/singleplay_gamerules.cpp:135 */
BOOL CHalfLifeRules::AllowAutoTargetCrosshair(void)
{
	return (g_iSkillLevel == SKILL_EASY);
}

/* <166f99> ../cstrike/dlls/singleplay_gamerules.cpp:142 */
void CHalfLifeRules::PlayerThink(CBasePlayer *pPlayer)
{
	;
}

/* <166fcd> ../cstrike/dlls/singleplay_gamerules.cpp:149 */
BOOL CHalfLifeRules::FPlayerCanRespawn(CBasePlayer *pPlayer)
{
	return TRUE;
}

/* <167001> ../cstrike/dlls/singleplay_gamerules.cpp:156 */
float CHalfLifeRules::FlPlayerSpawnTime(CBasePlayer *pPlayer)
{
	return gpGlobals->time;
}

/* <167035> ../cstrike/dlls/singleplay_gamerules.cpp:165 */
int CHalfLifeRules::IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled)
{
	return 1;
}

/* <167077> ../cstrike/dlls/singleplay_gamerules.cpp:173 */
void CHalfLifeRules::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	;
}

/* <1670c7> ../cstrike/dlls/singleplay_gamerules.cpp:180 */
void CHalfLifeRules::DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	;
}

/* <167117> ../cstrike/dlls/singleplay_gamerules.cpp:188 */
void CHalfLifeRules::PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	;
}

/* <167159> ../cstrike/dlls/singleplay_gamerules.cpp:196 */
float CHalfLifeRules::FlWeaponRespawnTime(CBasePlayerItem *pWeapon)
{
	return -1;
}

/* <16718d> ../cstrike/dlls/singleplay_gamerules.cpp:206 */
float CHalfLifeRules::FlWeaponTryRespawn(CBasePlayerItem *pWeapon)
{
	return 0;
}

/* <1671c1> ../cstrike/dlls/singleplay_gamerules.cpp:215 */
Vector CHalfLifeRules::VecWeaponRespawnSpot(CBasePlayerItem *pWeapon)
{
	return pWeapon->pev->origin;
}

/* <1675e6> ../cstrike/dlls/singleplay_gamerules.cpp:220 */
edict_t *CHalfLifeRules::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
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

/* <16721c> ../cstrike/dlls/singleplay_gamerules.cpp:243 */
int CHalfLifeRules::WeaponShouldRespawn(CBasePlayerItem *pWeapon)
{
	return GR_WEAPON_RESPAWN_NO;
}

/* <167250> ../cstrike/dlls/singleplay_gamerules.cpp:250 */
BOOL CHalfLifeRules::CanHaveItem(CBasePlayer *pPlayer, CItem *pItem)
{
	return TRUE;
}

/* <167292> ../cstrike/dlls/singleplay_gamerules.cpp:257 */
void CHalfLifeRules::PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem)
{
	;
}

/* <1672d6> ../cstrike/dlls/singleplay_gamerules.cpp:263 */
int CHalfLifeRules::ItemShouldRespawn(CItem *pItem)
{
	return GR_ITEM_RESPAWN_NO;
}

/* <16730b> ../cstrike/dlls/singleplay_gamerules.cpp:272 */
float CHalfLifeRules::FlItemRespawnTime(CItem *pItem)
{
	return -1;
}

/* <167340> ../cstrike/dlls/singleplay_gamerules.cpp:281 */
Vector CHalfLifeRules::VecItemRespawnSpot(CItem *pItem)
{
	return pItem->pev->origin;
}

/* <16739d> ../cstrike/dlls/singleplay_gamerules.cpp:288 */
BOOL CHalfLifeRules::IsAllowedToSpawn(CBaseEntity *pEntity)
{
	return TRUE;
}

/* <1673d2> ../cstrike/dlls/singleplay_gamerules.cpp:295 */
void CHalfLifeRules::PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount)
{
	;
}

/* <167425> ../cstrike/dlls/singleplay_gamerules.cpp:301 */
int CHalfLifeRules::AmmoShouldRespawn(CBasePlayerAmmo *pAmmo)
{
	return GR_AMMO_RESPAWN_NO;
}

/* <16745a> ../cstrike/dlls/singleplay_gamerules.cpp:308 */
float CHalfLifeRules::FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo)
{
	return -1;
}

/* <16748f> ../cstrike/dlls/singleplay_gamerules.cpp:315 */
Vector CHalfLifeRules::VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo)
{
	return pAmmo->pev->origin;
}

/* <1674ec> ../cstrike/dlls/singleplay_gamerules.cpp:322 */
float CHalfLifeRules::FlHealthChargerRechargeTime(void)
{
	return 0;
}

/* <167512> ../cstrike/dlls/singleplay_gamerules.cpp:329 */
int CHalfLifeRules::DeadPlayerWeapons(CBasePlayer *pPlayer)
{
	return GR_PLR_DROP_GUN_NO;
}

/* <167547> ../cstrike/dlls/singleplay_gamerules.cpp:336 */
int CHalfLifeRules::DeadPlayerAmmo(CBasePlayer *pPlayer)
{
	return GR_PLR_DROP_AMMO_NO;
}

/* <16757c> ../cstrike/dlls/singleplay_gamerules.cpp:343 */
int CHalfLifeRules::PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget)
{
	// why would a single player in half life need this? 
	return GR_NOTTEAMMATE;
}

/* <1675c0> ../cstrike/dlls/singleplay_gamerules.cpp:351 */
BOOL CHalfLifeRules::FAllowMonsters(void)
{
	return TRUE;
}

#ifdef HOOK_GAMEDLL

void CHalfLifeRules::PlayerSpawn(CBasePlayer *pPlayer)
{
	PlayerSpawn_(pPlayer);
}

#endif // HOOK_GAMEDLL