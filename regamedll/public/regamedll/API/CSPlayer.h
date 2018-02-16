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

#pragma once

#include <API/CSPlayerItem.h>
#include <API/CSPlayerWeapon.h>

class CCSPlayer: public CCSMonster {
public:
	CCSPlayer() : m_bForceShowMenu(false), m_flRespawnPending(0)
	{
		m_szModel[0] = '\0';
	}

	virtual bool IsConnected() const;
	virtual void SetAnimation(PLAYER_ANIM playerAnim);
	virtual void AddAccount(int amount, RewardType type = RT_NONE, bool bTrackChange = true);
	virtual CBaseEntity *GiveNamedItem(const char *pszName);
	virtual CBaseEntity *GiveNamedItemEx(const char *pszName);
	virtual void GiveDefaultItems();
	virtual void GiveShield(bool bDeploy = true);
	virtual void DropShield(bool bDeploy = true);
	virtual void DropPlayerItem(const char *pszItemName);
	virtual void RemoveShield();
	virtual void RemoveAllItems(bool bRemoveSuit);
	virtual bool RemovePlayerItem(const char* pszItemName);
	virtual void SetPlayerModel(bool bHasC4);
	virtual void SetPlayerModelEx(const char *modelName);
	virtual void SetNewPlayerModel(const char *modelName);
	virtual void ClientCommand(const char *cmd, const char *arg1 = nullptr, const char *arg2 = nullptr, const char *arg3 = nullptr);
	virtual void SetProgressBarTime(int time);
	virtual void SetProgressBarTime2(int time, float timeElapsed);
	virtual struct edict_s *EntSelectSpawnPoint();
	virtual void SetBombIcon(bool bFlash = false);
	virtual void SetScoreAttrib(CBasePlayer *dest);
	virtual void SendItemStatus();
	virtual void ReloadWeapons(CBasePlayerItem *pWeapon = nullptr, bool bForceReload = false, bool bForceRefill = false);
	virtual void Observer_SetMode(int iMode);
	virtual bool SelectSpawnSpot(const char *pEntClassName, CBaseEntity* &pSpot);
	virtual bool SwitchWeapon(CBasePlayerItem *pWeapon);
	virtual void SwitchTeam();
	virtual bool JoinTeam(TeamName team);
	virtual void StartObserver(Vector& vecPosition, Vector& vecViewAngle);
	virtual void TeamChangeUpdate();
	virtual void DropSecondary();
	virtual void DropPrimary();
	virtual bool HasPlayerItem(CBasePlayerItem *pCheckItem);
	virtual bool HasNamedPlayerItem(const char *pszItemName);
	virtual CBasePlayerItem *GetItemById(WeaponIdType weaponID);
	virtual CBasePlayerItem *GetItemByName(const char *itemName);
	virtual void Disappear();
	virtual void MakeVIP();
	virtual bool MakeBomber();
	virtual void ResetSequenceInfo();
	virtual void StartDeathCam();
	virtual bool RemovePlayerItemEx(const char* pszItemName, bool bRemoveAmmo);

	CBasePlayer *BasePlayer() const;

public:
	char m_szModel[32];
	bool m_bForceShowMenu;
	float m_flRespawnPending;
};

// Inlines
inline CBasePlayer *CCSPlayer::BasePlayer() const
{
	return reinterpret_cast<CBasePlayer *>(this->m_pContainingEntity);
}
