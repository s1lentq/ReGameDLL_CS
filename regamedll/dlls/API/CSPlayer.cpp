/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include "precompiled.h"

EXT_FUNC bool CCSPlayer::JoinTeam(TeamName team)
{
	CBasePlayer *pPlayer = BasePlayer();
	switch (team)
	{
	case SPECTATOR:
	{
		// are we already a spectator?
		if (pPlayer->m_iTeam == SPECTATOR)
			return false;

		// not necessary to trigger death event, just died quietly
		pPlayer->pev->deadflag = DEAD_DEAD;
		pPlayer->pev->health = 0;

		if (pPlayer->m_bHasC4)
			pPlayer->DropPlayerItem("weapon_c4");

		pPlayer->RemoveAllItems(TRUE);

		pPlayer->m_iTeam = SPECTATOR;
		pPlayer->m_iJoiningState = JOINED;

		pPlayer->m_pIntroCamera = nullptr;
		pPlayer->m_bTeamChanged = true;

		pPlayer->TeamChangeUpdate();

		edict_t *pentSpawnSpot = g_pGameRules->GetPlayerSpawnSpot(pPlayer);
		pPlayer->StartObserver(pentSpawnSpot->v.origin, pentSpawnSpot->v.angles);

		// do we have fadetoblack on? (need to fade their screen back in)
		if (fadetoblack.value == FADETOBLACK_STAY)
		{
			UTIL_ScreenFade(pPlayer, Vector(0, 0, 0), 0.001, 0, 0, FFADE_IN);
		}

		CSGameRules()->CheckWinConditions();
		return true;
	}
	case CT:
	case TERRORIST:
	{
		if (pPlayer->m_iTeam == SPECTATOR || pPlayer->m_iTeam == UNASSIGNED)
		{
			// If they're switching into spectator, setup spectator properties..
			pPlayer->m_bNotKilled = true;
			pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
			pPlayer->m_iTeamKills = 0;

			if (pPlayer->m_iAccount < int(startmoney.value)) {
				pPlayer->AddAccount(startmoney.value, RT_PLAYER_JOIN);
			}

			pPlayer->pev->solid = SOLID_NOT;
			pPlayer->pev->movetype = MOVETYPE_NOCLIP;
			pPlayer->pev->effects = (EF_NODRAW | EF_NOINTERP);
			pPlayer->pev->takedamage = DAMAGE_NO;
			pPlayer->pev->deadflag = DEAD_DEAD;
			pPlayer->pev->velocity = g_vecZero;
			pPlayer->pev->punchangle = g_vecZero;

			pPlayer->m_bHasNightVision = false;
			pPlayer->m_iHostagesKilled = 0;
			pPlayer->m_fDeadTime = 0;
			pPlayer->has_disconnected = false;

			if (pPlayer->m_bJustConnected) {
				pPlayer->m_iObserverLastMode = OBS_ROAMING;
				pPlayer->m_iObserverC4State = 0;
				pPlayer->m_bObserverHasDefuser = false;
				pPlayer->SetObserverAutoDirector(false);
			}

			pPlayer->m_iJoiningState = GETINTOGAME;
			pPlayer->SendItemStatus();

			SET_CLIENT_MAXSPEED(ENT(pPlayer->pev), 1);
			SET_MODEL(ENT(pPlayer->pev), "models/player.mdl");
		}
		break;
	}
	}

	if (pPlayer->pev->deadflag == DEAD_NO)
	{
		if (pPlayer->Kill())
		{
			pPlayer->pev->frags++;
		}
	}

	MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
		WRITE_BYTE(ENTINDEX(pPlayer->edict()));
		WRITE_SHORT(int(pPlayer->pev->frags));
		WRITE_SHORT(pPlayer->m_iDeaths);
		WRITE_SHORT(0);
		WRITE_SHORT(0);
	MESSAGE_END();

	// Switch their actual team...
	pPlayer->m_bTeamChanged = true;
	pPlayer->m_iTeam = team;
	pPlayer->TeamChangeUpdate();

	return true;
}

EXT_FUNC bool CCSPlayer::RemovePlayerItemEx(const char* pszItemName, bool bRemoveAmmo)
{
	if (!pszItemName)
		return false;

	CBasePlayer *pPlayer = BasePlayer();

	// if it item_ ?
	if (pszItemName[0] == 'i')
	{
		pszItemName += sizeof("item_") - 1;

		// item_thighpack
		if (FStrEq(pszItemName, "thighpack"))
		{
			// if we don't have it?
			if (!pPlayer->m_bHasDefuser)
				return false;

			pPlayer->RemoveDefuser();
		}
		// item_longjump
		else if (FStrEq(pszItemName, "longjump"))
		{
			// if we don't have it?
			if (!pPlayer->m_fLongJump)
				return false;

			pPlayer->m_fLongJump = FALSE;
			SET_PHYSICS_KEY_VALUE(pPlayer->edict(), "slj", "0");
		}
		// item_assaultsuit
		else if (FStrEq(pszItemName, "assaultsuit"))
		{
			// if we don't have it?
			if (pPlayer->m_iKevlar != ARMOR_VESTHELM)
				return false;

			pPlayer->m_iKevlar = ARMOR_NONE;
			pPlayer->pev->armorvalue = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgArmorType, nullptr, pPlayer->pev);
				WRITE_BYTE(0);
			MESSAGE_END();
		}
		// item_kevlar
		else if (FStrEq(pszItemName, "kevlar"))
		{
			// if we don't have it?
			if (pPlayer->m_iKevlar != ARMOR_KEVLAR)
				return false;

			pPlayer->m_iKevlar = ARMOR_NONE;
			pPlayer->pev->armorvalue = 0;
		}
		else
			return false;

		return true;
	}

	else if (FStrEq(pszItemName, "weapon_shield"))
	{
		return RemoveShield();
	}

	auto pItem = GetItemByName(pszItemName);
	if (pItem)
	{
		if (pItem->IsWeapon())
		{
			// These weapons have a unique type of ammo that is used only by them
			// If a weapon is removed, its ammo is also reduced, unless the ammo can be used by another weapon
			if (!bRemoveAmmo && (IsGrenadeWeapon(pItem->m_iId) || pItem->m_iId == WEAPON_C4))
			{
				if (pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()] > 0)
					pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()]--;

				// Hold the weapon until it runs out of ammo
				if (pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()] > 0)
					return true; // ammo was reduced, this will be considered a successful result
			}

			if (bRemoveAmmo) {
				pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()] = 0;
			}

			if (pItem == pPlayer->m_pActiveItem) {
				((CBasePlayerWeapon *)pItem)->RetireWeapon();

				if (pItem->CanHolster() && pItem != pPlayer->m_pActiveItem && !(pPlayer->pev->weapons &(1 << pItem->m_iId))) {
					return true;
				}
			}
		}

		return pItem->DestroyItem();
	}

	return false;
}

EXT_FUNC bool CCSPlayer::RemovePlayerItem(const char *pszItemName)
{
	return RemovePlayerItemEx(pszItemName, false);
}

EXT_FUNC CBaseEntity *CCSPlayer::GiveNamedItemEx(const char *pszName)
{
	CBasePlayer *pPlayer = BasePlayer();

	if (FStrEq(pszName, "weapon_c4")) {
		pPlayer->m_bHasC4 = true;

		if (pPlayer->m_iTeam == TERRORIST) {
			pPlayer->pev->body = 1;
		}

		pPlayer->SetBombIcon();

	} else if (FStrEq(pszName, "weapon_shield")) {
		pPlayer->DropPrimary();
		pPlayer->DropPlayerItem("weapon_elite");
		pPlayer->GiveShield();
		return nullptr;
	}

	return pPlayer->GiveNamedItemEx(pszName);
}

EXT_FUNC bool CCSPlayer::IsConnected() const
{
	return BaseEntity()->has_disconnected == false;
}

EXT_FUNC void CCSPlayer::SetAnimation(PLAYER_ANIM playerAnim)
{
	BasePlayer()->SetAnimation(playerAnim);
}

EXT_FUNC void CCSPlayer::AddAccount(int amount, RewardType type, bool bTrackChange)
{
	BasePlayer()->AddAccount(amount, type, bTrackChange);
}

EXT_FUNC CBaseEntity *CCSPlayer::GiveNamedItem(const char *pszName)
{
	return BasePlayer()->GiveNamedItem(pszName);
}

EXT_FUNC void CCSPlayer::GiveDefaultItems()
{
	BasePlayer()->GiveDefaultItems();
}

EXT_FUNC void CCSPlayer::GiveShield(bool bDeploy)
{
	BasePlayer()->GiveShield(bDeploy);
}

EXT_FUNC CBaseEntity *CCSPlayer::DropShield(bool bDeploy)
{
	return BasePlayer()->DropShield(bDeploy);
}

EXT_FUNC CBaseEntity *CCSPlayer::DropPlayerItem(const char *pszItemName)
{
	return BasePlayer()->DropPlayerItem(pszItemName);
}

EXT_FUNC bool CCSPlayer::RemoveShield()
{
	CBasePlayer *pPlayer = BasePlayer();

	if (!pPlayer->HasShield())
		return false;

	bool bIsProtectedShield = pPlayer->IsProtectedByShield();
	pPlayer->RemoveShield();

	CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(pPlayer->m_pActiveItem);
	if (pWeapon && pWeapon->IsWeapon())
	{
		if (!pWeapon->CanHolster())
			return false;

		if (pWeapon->m_iId == WEAPON_HEGRENADE || pWeapon->m_iId == WEAPON_FLASHBANG || pWeapon->m_iId == WEAPON_SMOKEGRENADE)
		{
			if (pPlayer->m_rgAmmo[pWeapon->m_iPrimaryAmmoType] <= 0)
				g_pGameRules->GetNextBestWeapon(pPlayer, pWeapon);
		}

		if (pWeapon->m_flStartThrow != 0.0f)
			pWeapon->Holster();

		if (pPlayer->IsReloading())
		{
			pWeapon->m_fInReload = FALSE;
			pPlayer->m_flNextAttack = 0;
		}

		if (bIsProtectedShield)
			pWeapon->SecondaryAttack();

		if (!pWeapon->Deploy())
			return false;
	}

	return true;
}

EXT_FUNC void CCSPlayer::RemoveAllItems(bool bRemoveSuit)
{
	BasePlayer()->RemoveAllItems(bRemoveSuit ? TRUE : FALSE);
}

EXT_FUNC void CCSPlayer::SetPlayerModel(bool bHasC4)
{
	BasePlayer()->SetPlayerModel(bHasC4 ? TRUE : FALSE);
}

EXT_FUNC void CCSPlayer::SetPlayerModelEx(const char *modelName)
{
	Q_strlcpy(m_szModel, modelName);
}

EXT_FUNC void CCSPlayer::SetNewPlayerModel(const char *modelName)
{
	BasePlayer()->SetNewPlayerModel(STRING(ALLOC_STRING(modelName)));
}

EXT_FUNC void CCSPlayer::ClientCommand(const char *cmd, const char *arg1, const char *arg2, const char *arg3)
{
	BasePlayer()->ClientCommand(cmd, arg1, arg2, arg3);
}

EXT_FUNC void CCSPlayer::SetProgressBarTime(int time)
{
	BasePlayer()->SetProgressBarTime(time);
}

EXT_FUNC void CCSPlayer::SetProgressBarTime2(int time, float timeElapsed)
{
	BasePlayer()->SetProgressBarTime2(time, timeElapsed);
}

EXT_FUNC edict_t *CCSPlayer::EntSelectSpawnPoint()
{
	return BasePlayer()->EntSelectSpawnPoint();
}

EXT_FUNC void CCSPlayer::SendItemStatus()
{
	BasePlayer()->SendItemStatus();
}

EXT_FUNC void CCSPlayer::SetBombIcon(bool bFlash)
{
	BasePlayer()->SetBombIcon(bFlash ? TRUE : FALSE);
}

EXT_FUNC void CCSPlayer::SetScoreAttrib(CBasePlayer *dest)
{
	BasePlayer()->SetScoreAttrib(dest);
}

EXT_FUNC void CCSPlayer::ReloadWeapons(CBasePlayerItem *pWeapon, bool bForceReload, bool bForceRefill)
{
	BasePlayer()->ReloadWeapons(pWeapon, bForceReload, bForceRefill);
}

EXT_FUNC void CCSPlayer::Observer_SetMode(int iMode)
{
	BasePlayer()->Observer_SetMode(iMode);
}

EXT_FUNC void CCSPlayer::Observer_FindNextPlayer(bool bReverse, const char *name)
{
	BasePlayer()->Observer_FindNextPlayer(bReverse, name);
}

EXT_FUNC bool CCSPlayer::SelectSpawnSpot(const char *pEntClassName, CBaseEntity *&pSpot)
{
	return BasePlayer()->SelectSpawnSpot(pEntClassName, pSpot);
}

EXT_FUNC bool CCSPlayer::SwitchWeapon(CBasePlayerItem *pWeapon)
{
	return BasePlayer()->SwitchWeapon(pWeapon) != FALSE;
}

EXT_FUNC void CCSPlayer::SwitchTeam()
{
	BasePlayer()->SwitchTeam();
}

EXT_FUNC void CCSPlayer::StartObserver(Vector& vecPosition, Vector& vecViewAngle)
{
	BasePlayer()->StartObserver(vecPosition, vecViewAngle);
}

EXT_FUNC void CCSPlayer::TeamChangeUpdate()
{
	BasePlayer()->TeamChangeUpdate();
}

EXT_FUNC void CCSPlayer::DropSecondary()
{
	BasePlayer()->DropSecondary();
}

EXT_FUNC void CCSPlayer::DropPrimary()
{
	BasePlayer()->DropPrimary();
}

EXT_FUNC bool CCSPlayer::HasPlayerItem(CBasePlayerItem *pCheckItem)
{
	return BasePlayer()->HasPlayerItem(pCheckItem);
}

EXT_FUNC bool CCSPlayer::HasNamedPlayerItem(const char *pszItemName)
{
	return BasePlayer()->HasNamedPlayerItem(pszItemName);
}

EXT_FUNC CBasePlayerItem *CCSPlayer::GetItemById(WeaponIdType weaponID)
{
	return BasePlayer()->GetItemById(weaponID);
}

EXT_FUNC CBasePlayerItem *CCSPlayer::GetItemByName(const char *itemName)
{
	return BasePlayer()->GetItemByName(itemName);
}

EXT_FUNC void CCSPlayer::Disappear()
{
	BasePlayer()->Disappear();
}

EXT_FUNC void CCSPlayer::MakeVIP()
{
	BasePlayer()->MakeVIP();
}

EXT_FUNC bool CCSPlayer::MakeBomber()
{
	return BasePlayer()->MakeBomber();
}

EXT_FUNC void CCSPlayer::ResetSequenceInfo()
{
	BasePlayer()->ResetSequenceInfo();
}

EXT_FUNC void CCSPlayer::StartDeathCam()
{
	BasePlayer()->StartDeathCam();
}

EXT_FUNC void CCSPlayer::SetSpawnProtection(float flProtectionTime)
{
	BasePlayer()->SetSpawnProtection(flProtectionTime);
}

EXT_FUNC void CCSPlayer::RemoveSpawnProtection()
{
	BasePlayer()->RemoveSpawnProtection();
}

EXT_FUNC bool CCSPlayer::HintMessageEx(const char *pMessage, float duration, bool bDisplayIfPlayerDead, bool bOverride)
{
	return BasePlayer()->HintMessageEx(pMessage, duration, bDisplayIfPlayerDead, bOverride);
}

EXT_FUNC void CCSPlayer::Reset()
{
	BasePlayer()->Reset();
}

EXT_FUNC void CCSPlayer::OnSpawnEquip(bool addDefault, bool equipGame)
{
	BasePlayer()->OnSpawnEquip(addDefault, equipGame);
}

EXT_FUNC void CCSPlayer::SetScoreboardAttributes(CBasePlayer *destination)
{
	BasePlayer()->SetScoreboardAttributes(destination);
}

EXT_FUNC bool CCSPlayer::CheckActivityInGame()
{
	const CBasePlayer* pPlayer = BasePlayer();

	const float deltaYaw = (m_vecOldvAngle.y - pPlayer->pev->v_angle.y);
	const float deltaPitch = (m_vecOldvAngle.x - pPlayer->pev->v_angle.x);

	m_vecOldvAngle = pPlayer->pev->v_angle;

	return (fabs(deltaYaw) >= 0.1f && fabs(deltaPitch) >= 0.1f);
}

void CCSPlayer::ResetVars()
{
	m_szModel[0] = '\0';

	m_bForceShowMenu = false;
	m_flRespawnPending =
		m_flSpawnProtectionEndTime = 0.0f;

	m_vecOldvAngle = g_vecZero;
	m_iWeaponInfiniteAmmo = 0;
	m_iWeaponInfiniteIds = 0;
	m_bCanShootOverride = false;
	m_bGameForcingRespawn = false;
	m_bAutoBunnyHopping = false;
	m_bMegaBunnyJumping = false;
	m_bSpawnProtectionEffects = false;
}

// Resets all stats
void CCSPlayer::ResetAllStats()
{
	// Resets the kill history for this player
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		m_iNumKilledByUnanswered[i] = 0;
		m_bPlayerDominated[i]       = false;
	}

	m_DamageList.Clear();
}

void CCSPlayer::OnSpawn()
{
	m_bGameForcingRespawn = false;
	m_flRespawnPending = 0.0f;
	m_DamageList.Clear();
}

void CCSPlayer::OnKilled()
{
#ifdef REGAMEDLL_ADD
	if (forcerespawn.value > 0)
	{
		m_bGameForcingRespawn = true;
		m_flRespawnPending = gpGlobals->time + forcerespawn.value;
	}

	if (GetProtectionState() == ProtectionSt_Active)
	{
		BasePlayer()->RemoveSpawnProtection();
	}
#endif
}

void CCSPlayer::OnConnect()
{
	ResetVars();
	ResetAllStats();
	m_iUserID = GETPLAYERUSERID(BasePlayer()->edict());
}

// Remember this amount of damage that we dealt for stats
void CCSPlayer::RecordDamage(CBasePlayer *pAttacker, float flDamage, float flFlashDurationTime)
{
	if (!pAttacker || !pAttacker->IsPlayer())
		return;

	int attackerIndex = pAttacker->entindex() - 1;
	if (attackerIndex < 0 || attackerIndex >= MAX_CLIENTS)
		return;

	CCSPlayer *pCSAttacker = pAttacker->CSPlayer();

	// Accumulate damage
	CDamageRecord_t &record = m_DamageList[attackerIndex];
	if (record.flDamage > 0 && record.userId != pCSAttacker->m_iUserID)
		record.flDamage = 0; // reset damage if attacker became another client

	record.flDamage += flDamage;
	record.userId    = pCSAttacker->m_iUserID;

	if (flFlashDurationTime > 0)
		record.flFlashDurationTime = gpGlobals->time + flFlashDurationTime;
}
