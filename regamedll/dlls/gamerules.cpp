#include "precompiled.h"

CGameRules *g_pGameRules = nullptr;

CGameRules::CGameRules()
{
	m_bFreezePeriod = FALSE;
	m_bBombDropped = FALSE;
	m_bGameOver = false;

	m_GameDesc = new char[sizeof("Counter-Strike")];
	Q_strcpy(m_GameDesc, AreRunningCZero() ? "Condition Zero" : "Counter-Strike");
}

CGameRules::~CGameRules()
{
	delete[] m_GameDesc;
	m_GameDesc = nullptr;
}

// this is the game name that gets seen in the server browser
const char *CGameRules::GetGameDescription()
{
#ifdef REGAMEDLL_ADD
	return m_GameDesc;
#else
	return "Counter-Strike";
#endif
}

BOOL CGameRules::CanHaveAmmo(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry)
{
	if (pszAmmoName)
	{
		auto iAmmoIndex = pPlayer->GetAmmoIndex(pszAmmoName);
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

edict_t *CGameRules::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
{
	// gat valid spawn point
	edict_t *pentSpawnSpot = pPlayer->EntSelectSpawnPoint();

	// Move the player to the place it said.
#ifndef PLAY_GAMEDLL
	pPlayer->pev->origin = pentSpawnSpot->v.origin + Vector(0, 0, 1);
#else
	// TODO: fix test demo
	pPlayer->pev->origin = pentSpawnSpot->v.origin;
	pPlayer->pev->origin.z += 1;
#endif

	pPlayer->pev->v_angle = g_vecZero;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->angles = pentSpawnSpot->v.angles;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->pev->fixangle = 1;

	return pentSpawnSpot;
}

BOOL CGameRules::CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	// only living players can have items
	if (pPlayer->pev->deadflag != DEAD_NO)
	{
		return FALSE;
	}

	if (pPlayer->IsBot() && TheCSBots() && !TheCSBots()->IsWeaponUseable(pWeapon))
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

void CGameRules::RefreshSkillData()
{
	int iSkill = int(CVAR_GET_FLOAT("skill"));

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

LINK_HOOK_CHAIN2(CGameRules *, InstallGameRules)

CGameRules *EXT_FUNC __API_HOOK(InstallGameRules)()
{
	SERVER_COMMAND("exec game.cfg\n");
	SERVER_EXECUTE();

	if (!gpGlobals->deathmatch)
		return new CHalfLifeTraining;

	return new CHalfLifeMultiplay;
}
