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
BOOL CGameRules::CanHaveAmmo_(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry)
{
	if (pszAmmoName)
	{
		int iAmmoIndex = pPlayer->GetAmmoIndex(pszAmmoName);

		if (iAmmoIndex > -1)
		{
			if (pPlayer->AmmoInventory(iAmmoIndex) < iMaxCarry)
				return TRUE;
		}
	}
	return FALSE;
}

/* <ad89d> ../cstrike/dlls/gamerules.cpp:59 */
NOBODY edict_t *CGameRules::GetPlayerSpawnSpot_(CBasePlayer *pPlayer)
{
//	{
//		edict_t *pentSpawnSpot;                              //    61
//		VARS(edict_t *pent);  //    66
//		VARS(edict_t *pent);  //    63
//		operator+(const Vector *const this,
//				const Vector &v);  //    63
//	}
}

/* <ad9a3> ../cstrike/dlls/gamerules.cpp:75 */
NOBODY BOOL CGameRules::CanHavePlayerItem_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	/*if (pPlayer->pev->deadflag != DEAD_NO)
		return FALSE;

	CCSBotManager *ctrl = TheCSBots();
	if (!pPlayer->AddPlayerItem(pWeapon) ||	ctrl->IsWeaponUseable(pWeapon))
	{
		// TODO: check it
		if (pWeapon->pszAmmo1() && CanHaveAmmo(pPlayer,pWeapon->pszAmmo1(),pWeapon->iMaxAmmo1()) || !pPlayer->HasPlayerItem(pWeapon))
		{
			return TRUE;
		}
	}*/
	return FALSE;
}

/* <ad85d> ../cstrike/dlls/gamerules.cpp:119 */
void CGameRules::RefreshSkillData_(void)
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

/* <ada23> ../cstrike/dlls/gamerules.cpp:157 */
NOBODY CGameRules *InstallGameRules(void)
{
	SERVER_COMMAND("exec game.cfg\n");
	SERVER_EXECUTE();

	if (!gpGlobals->deathmatch)
		return new CHalfLifeTraining;

	return new CHalfLifeMultiplay;
}

#ifdef HOOK_GAMEDLL

BOOL CGameRules::CanHaveAmmo(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry)
{
	return CanHaveAmmo_(pPlayer,pszAmmoName,iMaxCarry);
}

edict_t *CGameRules::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
{
	return GetPlayerSpawnSpot_(pPlayer);
}

BOOL CGameRules::CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	return CanHavePlayerItem_(pPlayer,pWeapon);
}

void CGameRules::RefreshSkillData(void)
{
	RefreshSkillData_();
}

#endif // HOOK_GAMEDLL
