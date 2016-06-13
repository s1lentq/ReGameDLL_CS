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
#pragma once

class CHalfLifeTraining: public CHalfLifeMultiplay {
protected:
	virtual ~CHalfLifeTraining() {};
public:
	virtual BOOL IsMultiplayer() = 0;
	virtual BOOL IsDeathmatch() = 0;
	virtual void InitHUD(CBasePlayer *pl) = 0;
	virtual void PlayerSpawn(CBasePlayer *pPlayer) = 0;
	virtual void PlayerThink(CBasePlayer *pPlayer) = 0;
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer) = 0;
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer) = 0;
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) = 0;
	virtual int ItemShouldRespawn(CItem *pItem) = 0;
	virtual void CheckMapConditions() = 0;
	virtual void CheckWinConditions() = 0;
public:
	float FillAccountTime;
	float ServerRestartTime;
	BOOL fInBuyArea;
	BOOL fVisitedBuyArea;
	bool fVGUIMenus;
};

class CBaseGrenCatch: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
public:
	int m_NeedGrenadeType;
	string_t sTriggerOnGrenade;
	string_t sDisableOnGrenade;
	bool m_fSmokeTouching;
	bool m_fFlashTouched;
};

class CFuncWeaponCheck: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
private:
	string_t sTriggerWithItems;
	string_t sTriggerNoItems;
	string_t sMaster;
	unsigned int sItemName[32];
	int iItemCount;
	int iAnyWeapon;
};
