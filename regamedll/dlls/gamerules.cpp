#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

CHalfLifeMultiplay *g_pGameRules = NULL;

#else //HOOK_GAMEDLL

CHalfLifeMultiplay *g_pGameRules;

#endif //HOOK_GAMEDLL

/* <ad93d> ../cstrike/dlls/gamerules.cpp:36 */
BOOL CGameRules::__MAKE_VHOOK(CanHaveAmmo)(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry)
{
	int iAmmoIndex;

	if (pszAmmoName != NULL)
	{
		iAmmoIndex = pPlayer->GetAmmoIndex(pszAmmoName);

		if (iAmmoIndex > -1)
		{
			if (pPlayer->AmmoInventory(iAmmoIndex) < iMaxCarry)
			{
				// player has room for more of this type of ammo
				return TRUE;
			}
		}
	}

	return FALSE;
}

/* <ad89d> ../cstrike/dlls/gamerules.cpp:59 */
edict_t *CGameRules::__MAKE_VHOOK(GetPlayerSpawnSpot)(CBasePlayer *pPlayer)
{
	// gat valid spawn point
	edict_t *pentSpawnSpot = EntSelectSpawnPoint(pPlayer);

	// Move the player to the place it said.
#ifndef PLAY_GAMEDLL
	pPlayer->pev->origin = VARS(pentSpawnSpot)->origin + Vector(0, 0, 1);
#else
	// TODO: fix test demo
	pPlayer->pev->origin = VARS(pentSpawnSpot)->origin;
	pPlayer->pev->origin.z += 1;
#endif // PLAY_GAMEDLL

	pPlayer->pev->v_angle = g_vecZero;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->angles = VARS(pentSpawnSpot)->angles;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->pev->fixangle = 1;

	return pentSpawnSpot;
}

/* <ad9a3> ../cstrike/dlls/gamerules.cpp:75 */
BOOL CGameRules::__MAKE_VHOOK(CanHavePlayerItem)(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	// only living players can have items
	if (pPlayer->pev->deadflag != DEAD_NO)
	{
		return FALSE;
	}

	CCSBotManager *ctrl = TheCSBots();

	if (pPlayer->IsBot() && ctrl != NULL && !ctrl->IsWeaponUseable(pWeapon))
	{
		return FALSE;
	}

	if (pWeapon->pszAmmo1())
	{
		if (!CanHaveAmmo(pPlayer, pWeapon->pszAmmo1(), pWeapon->iMaxAmmo1()))
		{
			// we can't carry anymore ammo for this gun. We can only
			// have the gun if we aren't already carrying one of this type
			if (pPlayer->HasPlayerItem(pWeapon))
			{
				return FALSE;
			}
		}
	}
	else
	{
		// weapon doesn't use ammo, don't take another if you already have it.
		if (pPlayer->HasPlayerItem(pWeapon))
		{
			return FALSE;
		}
	}

	// note: will fall through to here if GetItemInfo doesn't fill the struct!
	return TRUE;
}

/* <ad85d> ../cstrike/dlls/gamerules.cpp:119 */
void CGameRules::__MAKE_VHOOK(RefreshSkillData)(void)
{
	int iSkill = (int)CVAR_GET_FLOAT("skill");

	if (iSkill < 1)
		iSkill = 1;

	else if (iSkill > 3)
		iSkill = 3;

	gSkillData.iSkillLevel = iSkill;
	ALERT(at_console, "\nGAME SKILL LEVEL:%d\n", iSkill);

	gSkillData.monDmg12MM = 8;
	gSkillData.monDmgMP5 = 3;
	gSkillData.monDmg9MM = 5;
	gSkillData.suitchargerCapacity = 75;
	gSkillData.batteryCapacity = 15;
	gSkillData.healthchargerCapacity = 50;
	gSkillData.healthkitCapacity = 15;
}

void (*pInstallGameRules)(void);

/* <ada23> ../cstrike/dlls/gamerules.cpp:157 */
#ifdef HOOK_GAMEDLL
NOBODY __declspec(naked) CGameRules *InstallGameRules(void)
{
	__asm
	{
		jmp pInstallGameRules
	}
}
#else
CGameRules *InstallGameRules(void)
{
	SERVER_COMMAND("exec game.cfg\n");
	SERVER_EXECUTE();

	if (!gpGlobals->deathmatch)
		return new CHalfLifeTraining;

	return new CHalfLifeMultiplay;
}
#endif // HOOK_GAMEDLL

#ifdef HOOK_GAMEDLL

void CGameRules::RefreshSkillData(void)
{
	RefreshSkillData_();
}

edict_t *CGameRules::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
{
	return GetPlayerSpawnSpot_(pPlayer);
}

BOOL CGameRules::CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	return CanHavePlayerItem_(pPlayer, pWeapon);
}

BOOL CGameRules::CanHaveAmmo(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry)
{
	return CanHaveAmmo_(pPlayer, pszAmmoName, iMaxCarry);
}

#endif // HOOK_GAMEDLL
