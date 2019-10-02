/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#include "precompiled.h"

bool HasDefaultPistol(CCSBot *me)
{
	CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(me->m_rgpPlayerItems[PISTOL_SLOT]);

	if (!pSecondary)
		return false;

	if (me->m_iTeam == TERRORIST && pSecondary->m_iId == WEAPON_GLOCK18)
		return true;

	if (me->m_iTeam == CT && pSecondary->m_iId == WEAPON_USP)
		return true;

	return false;
}

// Buy weapons, armor, etc.
void BuyState::OnEnter(CCSBot *me)
{
	m_retries = 0;
	m_prefRetries = 0;
	m_prefIndex = 0;

	m_doneBuying = false;
	m_isInitialDelay = true;

	// this will force us to stop holding live grenade
	me->EquipBestWeapon();

	m_buyDefuseKit = false;
	m_buyShield = false;

	if (me->m_iTeam == CT)
	{
		if (TheCSBots()->GetScenario() == CCSBotManager::SCENARIO_DEFUSE_BOMB)
		{
			// CT's sometimes buy defuse kits in the bomb scenario (except in career mode, where the player should defuse)
			if (!CSGameRules()->IsCareer())
			{
				const float buyDefuseKitChance = 50.0f;	// 100.0f * (me->GetProfile()->GetSkill() + 0.2f);
				if (RANDOM_FLOAT(0.0f, 100.0f) < buyDefuseKitChance)
				{
					m_buyDefuseKit = true;
				}
			}
		}

		// determine if we want a tactical shield
		if (!me->m_bHasPrimary && TheCSBots()->AllowTacticalShield())
		{
			if (me->m_iAccount > 2500)
			{
				if (me->m_iAccount < 4000)
					m_buyShield = (RANDOM_FLOAT(0, 100.0f) < 33.3f) ? true : false;
				else
					m_buyShield = (RANDOM_FLOAT(0, 100.0f) < 10.0f) ? true : false;
			}
		}
	}

	if (TheCSBots()->AllowGrenades())
	{
		m_buyGrenade = (RANDOM_FLOAT(0.0f, 100.0f) < 33.3f) ? true : false;
	}
	else
	{
		m_buyGrenade = false;
	}

	m_buyPistol = false;

	if (TheCSBots()->AllowPistols())
	{
		CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(me->m_rgpPlayerItems[PISTOL_SLOT]);

		// check if we have a pistol
		if (pSecondary)
		{
			// if we have our default pistol, think about buying a different one
			if (HasDefaultPistol(me))
			{
				// if everything other than pistols is disallowed, buy a pistol
				if (!TheCSBots()->AllowShotguns()
					&& !TheCSBots()->AllowSubMachineGuns()
					&& !TheCSBots()->AllowRifles()
					&& !TheCSBots()->AllowMachineGuns()
					&& !TheCSBots()->AllowTacticalShield()
					&& !TheCSBots()->AllowSnipers())
				{
					m_buyPistol = (RANDOM_FLOAT(0, 100) < 75.0f);
				}
				else if (me->m_iAccount < 1000)
				{
					// if we're low on cash, buy a pistol
					m_buyPistol = (RANDOM_FLOAT(0, 100) < 75.0f);
				}
				else
				{
					m_buyPistol = (RANDOM_FLOAT(0, 100) < 33.3f);
				}
			}
		}
		else
		{
			// we dont have a pistol - buy one
			m_buyPistol = true;
		}
	}
}

enum WeaponType
{
	PISTOL,
	SHOTGUN,
	SUB_MACHINE_GUN,
	RIFLE,
	MACHINE_GUN,
	SNIPER_RIFLE,
	GRENADE,
	NUM_WEAPON_TYPES,
};

struct BuyInfo
{
	WeaponType type;
	bool preferred; // more challenging bots prefer these weapons
	char *buyAlias; // the buy alias for this equipment
};

// These tables MUST be kept in sync with the CT and T buy aliases
BuyInfo primaryWeaponBuyInfoCT[MAX_BUY_WEAPON_PRIMARY] =
{
	{ SHOTGUN,          false, "m3"     }, // WEAPON_M3
	{ SHOTGUN,          false, "xm1014" }, // WEAPON_XM1014
	{ SUB_MACHINE_GUN,  false, "tmp"    }, // WEAPON_TMP
	{ SUB_MACHINE_GUN,  false, "mp5"    }, // WEAPON_MP5N
	{ SUB_MACHINE_GUN,  false, "ump45"  }, // WEAPON_UMP45
	{ SUB_MACHINE_GUN,  false, "p90"    }, // WEAPON_P90
	{ RIFLE,            true,  "famas"  }, // WEAPON_FAMAS
	{ SNIPER_RIFLE,     false, "scout"  }, // WEAPON_SCOUT
	{ RIFLE,            true,  "m4a1"   }, // WEAPON_M4A1
	{ RIFLE,            false, "aug"    }, // WEAPON_AUG
	{ SNIPER_RIFLE,     true,  "sg550"  }, // WEAPON_SG550
	{ SNIPER_RIFLE,     true,  "awp"    }, // WEAPON_AWP
	{ MACHINE_GUN,      false, "m249"   }, // WEAPON_M249
};

BuyInfo secondaryWeaponBuyInfoCT[MAX_BUY_WEAPON_SECONDARY] =
{
//	{ PISTOL, false, "glock"  },
//	{ PISTOL, false, "usp"    },
	{ PISTOL, true,  "p228"   },
	{ PISTOL, true,  "deagle" },
	{ PISTOL, true,  "fn57"   },
};

BuyInfo primaryWeaponBuyInfoT[MAX_BUY_WEAPON_PRIMARY] =
{
	{ SHOTGUN,          false, "m3"     }, // WEAPON_M3
	{ SHOTGUN,          false, "xm1014" }, // WEAPON_XM1014
	{ SUB_MACHINE_GUN,  false, "mac10"  }, // WEAPON_MAC10
	{ SUB_MACHINE_GUN,  false, "mp5"    }, // WEAPON_MP5N
	{ SUB_MACHINE_GUN,  false, "ump45"  }, // WEAPON_UMP45
	{ SUB_MACHINE_GUN,  false, "p90"    }, // WEAPON_P90
	{ RIFLE,            true,  "galil"  }, // WEAPON_GALIL
	{ RIFLE,            true,  "ak47"   }, // WEAPON_AK47
	{ SNIPER_RIFLE,     false, "scout"  }, // WEAPON_SCOUT
	{ RIFLE,            true,  "sg552"  }, // WEAPON_SG552
	{ SNIPER_RIFLE,     true,  "awp"    }, // WEAPON_AWP
	{ SNIPER_RIFLE,     true,  "g3sg1"  }, // WEAPON_G3SG1
	{ MACHINE_GUN,      false, "m249"   }, // WEAPON_M249
};

BuyInfo secondaryWeaponBuyInfoT[MAX_BUY_WEAPON_SECONDARY] =
{
//	{ PISTOL, false, "glock"  },
//	{ PISTOL, false, "usp"    },
	{ PISTOL, true,  "p228"   },
	{ PISTOL, true,  "deagle" },
	{ PISTOL, true,  "elites" },
};

// Given a weapon alias, return the kind of weapon it is
inline WeaponType GetWeaponType(const char *alias)
{
	int i;
	for (i = 0; i < MAX_BUY_WEAPON_PRIMARY; i++)
	{
		if (!Q_stricmp(alias, primaryWeaponBuyInfoCT[i].buyAlias))
			return primaryWeaponBuyInfoCT[i].type;

		if (!Q_stricmp(alias, primaryWeaponBuyInfoT[i].buyAlias))
			return primaryWeaponBuyInfoT[i].type;
	}

	for (i = 0; i < MAX_BUY_WEAPON_SECONDARY; i++)
	{
		if (!Q_stricmp(alias, secondaryWeaponBuyInfoCT[i].buyAlias))
			return secondaryWeaponBuyInfoCT[i].type;

		if (!Q_stricmp(alias, secondaryWeaponBuyInfoT[i].buyAlias))
			return secondaryWeaponBuyInfoT[i].type;
	}

	return NUM_WEAPON_TYPES;
}

void BuyState::OnUpdate(CCSBot *me)
{
	// wait for a Navigation Mesh
	if (!TheNavAreaList.size())
		return;

	// apparently we cant buy things in the first few seconds, so wait a bit
	if (m_isInitialDelay)
	{
		const float waitToBuyTime = 2.0f; // 0.25f;
		if (gpGlobals->time - me->GetStateTimestamp() < waitToBuyTime)
			return;

		m_isInitialDelay = false;
	}

	// if we're done buying and still in the freeze period, wait
	if (m_doneBuying)
	{
		if (CSGameRules()->IsMultiplayer() && CSGameRules()->IsFreezePeriod())
		{
#ifdef REGAMEDLL_FIXES
			// make sure we're locked and loaded
			me->EquipBestWeapon(MUST_EQUIP);
			me->Reload();
			me->ResetStuckMonitor();
#endif
			return;
		}

		me->Idle();

#ifdef REGAMEDLL_FIXES
		return;
#endif
	}

	// is the bot spawned outside of a buy zone?
	if (!(me->m_signals.GetState() & SIGNAL_BUY))
	{
		m_doneBuying = true;
		UTIL_DPrintf("%s bot spawned outside of a buy zone (%d, %d, %d)\n", (me->m_iTeam == CT) ? "CT" : "Terrorist", int(me->pev->origin.x), int(me->pev->origin.y), int(me->pev->origin.z));
		return;
	}

	// try to buy some weapons
	const float buyInterval = 0.2f; // 0.02f
	if (gpGlobals->time - me->GetStateTimestamp() > buyInterval)
	{
		me->m_stateTimestamp = gpGlobals->time;

		bool isPreferredAllDisallowed = true;

		// try to buy our preferred weapons first
		if (m_prefIndex < me->GetProfile()->GetWeaponPreferenceCount())
		{
			// need to retry because sometimes first buy fails??
			const int maxPrefRetries = 2;
			if (m_prefRetries >= maxPrefRetries)
			{
				// try to buy next preferred weapon
				m_prefIndex++;
				m_prefRetries = 0;
				return;
			}

			int weaponPreference = me->GetProfile()->GetWeaponPreference(m_prefIndex);

			// don't buy it again if we still have one from last round
			CBasePlayerWeapon *pCurrentWeapon = me->GetActiveWeapon();
			if (pCurrentWeapon && pCurrentWeapon->m_iId == weaponPreference)
			{
				// done with buying preferred weapon
				m_prefIndex = 9999;
				return;
			}

			if (me->HasShield() && weaponPreference == WEAPON_SHIELDGUN)
			{
				// done with buying preferred weapon
				m_prefIndex = 9999;
				return;
			}

			const char *buyAlias = nullptr;
			if (weaponPreference == WEAPON_SHIELDGUN)
			{
				if (TheCSBots()->AllowTacticalShield())
					buyAlias = "shield";
			}
			else
			{
				buyAlias = WeaponIDToAlias(weaponPreference);
				WeaponType type = GetWeaponType(buyAlias);

				switch (type)
				{
				case PISTOL:
					if (!TheCSBots()->AllowPistols())
						buyAlias = nullptr;
					break;
				case SHOTGUN:
					if (!TheCSBots()->AllowShotguns())
						buyAlias = nullptr;
					break;
				case SUB_MACHINE_GUN:
					if (!TheCSBots()->AllowSubMachineGuns())
						buyAlias = nullptr;
					break;
				case RIFLE:
					if (!TheCSBots()->AllowRifles())
						buyAlias = nullptr;
					break;
				case MACHINE_GUN:
					if (!TheCSBots()->AllowMachineGuns())
						buyAlias = nullptr;
					break;
				case SNIPER_RIFLE:
					if (!TheCSBots()->AllowSnipers())
						buyAlias = nullptr;
					break;
				}
			}

			if (buyAlias)
			{
				me->ClientCommand(buyAlias);
				me->PrintIfWatched("Tried to buy preferred weapon %s.\n", buyAlias);

				isPreferredAllDisallowed = false;
			}

			m_prefRetries++;

			// bail out so we dont waste money on other equipment
			// unless everything we prefer has been disallowed, then buy at random
			if (isPreferredAllDisallowed == false)
				return;
		}

		// if we have no preferred primary weapon (or everything we want is disallowed), buy at random
		if (!me->m_bHasPrimary && (isPreferredAllDisallowed || !me->GetProfile()->HasPrimaryPreference()))
		{
			if (m_buyShield)
			{
				// buy a shield
				me->ClientCommand("shield");
				me->PrintIfWatched("Tried to buy a shield.\n");
			}
			else
			{
				// build list of allowable weapons to buy
				BuyInfo *masterPrimary = (me->m_iTeam == TERRORIST) ? primaryWeaponBuyInfoT : primaryWeaponBuyInfoCT;
				BuyInfo *stockPrimary[MAX_BUY_WEAPON_PRIMARY];
				int stockPrimaryCount = 0;

				// dont choose sniper rifles as often
				const float sniperRifleChance = 50.0f;
				bool wantSniper = (RANDOM_FLOAT(0, 100) < sniperRifleChance) ? true : false;

				for (int i = 0; i < MAX_BUY_WEAPON_PRIMARY; i++)
				{
					if ((masterPrimary[i].type == SHOTGUN && TheCSBots()->AllowShotguns())
						|| (masterPrimary[i].type == SUB_MACHINE_GUN && TheCSBots()->AllowSubMachineGuns())
						|| (masterPrimary[i].type == RIFLE && TheCSBots()->AllowRifles())
						|| (masterPrimary[i].type == SNIPER_RIFLE && TheCSBots()->AllowSnipers() && wantSniper)
						|| (masterPrimary[i].type == MACHINE_GUN && TheCSBots()->AllowMachineGuns()))
					{
						stockPrimary[stockPrimaryCount++] = &masterPrimary[i];
					}
				}

				if (stockPrimaryCount)
				{
					// buy primary weapon if we don't have one
					int which;

					// on hard difficulty levels, bots try to buy preferred weapons on the first pass
					if (m_retries == 0 && TheCSBots()->GetDifficultyLevel() >= BOT_HARD)
					{
						// count up available preferred weapons
						int prefCount = 0;
						for (which = 0; which < stockPrimaryCount; which++)
						{
							if (stockPrimary[which]->preferred)
								prefCount++;
						}

						if (prefCount)
						{
							int whichPref = RANDOM_LONG(0, prefCount - 1);
							for (which = 0; which < stockPrimaryCount; which++)
							{
								if (stockPrimary[which]->preferred && whichPref-- == 0)
									break;
							}
						}
						else
						{
							// no preferred weapons available, just pick randomly
							which = RANDOM_LONG(0, stockPrimaryCount - 1);
						}
					}
					else
					{
						which = RANDOM_LONG(0, stockPrimaryCount - 1);
					}

					me->ClientCommand(stockPrimary[which]->buyAlias);
					me->PrintIfWatched("Tried to buy %s.\n", stockPrimary[which]->buyAlias);
				}
			}
		}

		// If we now have a weapon, or have tried for too long, we're done
		if (me->m_bHasPrimary || m_retries++ > 5)
		{
			// primary ammo
			if (me->m_bHasPrimary)
			{
				me->ClientCommand("primammo");
			}

			// buy armor last, to make sure we bought a weapon first
			me->ClientCommand("vesthelm");
			me->ClientCommand("vest");

			// pistols - if we have no preferred pistol, buy at random
			if (TheCSBots()->AllowPistols() && !me->GetProfile()->HasPistolPreference())
			{
				if (m_buyPistol)
				{
					int which = RANDOM_LONG(0, MAX_BUY_WEAPON_SECONDARY - 1);

					if (me->m_iTeam == TERRORIST)
						me->ClientCommand(secondaryWeaponBuyInfoT[which].buyAlias);
					else
						me->ClientCommand(secondaryWeaponBuyInfoCT[which].buyAlias);

					// only buy one pistol
					m_buyPistol = false;
				}

				me->ClientCommand("secammo");
			}

			// buy a grenade if we wish, and we don't already have one
			if (m_buyGrenade && !me->HasGrenade())
			{
				if (UTIL_IsTeamAllBots(me->m_iTeam))
				{
					// only allow Flashbangs if everyone on the team is a bot (dont want to blind our friendly humans)
					float rnd = RANDOM_FLOAT(0, 100);

					if (rnd < 10.0f)
					{
						// smoke grenade
						me->ClientCommand("sgren");
					}
					else if (rnd < 35.0f)
					{
						// flashbang
						me->ClientCommand("flash");
					}
					else
					{
						// he grenade
						me->ClientCommand("hegren");
					}
				}
				else
				{
					if (RANDOM_FLOAT(0, 100) < 10.0f)
					{
						// smoke grenade
						me->ClientCommand("sgren");
					}
					else
					{
						// he grenade
						me->ClientCommand("hegren");
					}
				}
			}

			if (m_buyDefuseKit)
			{
				me->ClientCommand("defuser");
			}

			m_doneBuying = true;
		}
	}
}

void BuyState::OnExit(CCSBot *me)
{
	me->ResetStuckMonitor();
	me->EquipBestWeapon();
}
