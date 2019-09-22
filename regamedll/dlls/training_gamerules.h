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

class CHalfLifeTraining: public CHalfLifeMultiplay
{
public:
	CHalfLifeTraining();
	virtual ~CHalfLifeTraining() {};

	virtual BOOL IsMultiplayer() { return FALSE; }
	virtual BOOL IsDeathmatch();
	virtual void InitHUD(CBasePlayer *pl);
	virtual void PlayerSpawn(CBasePlayer *pPlayer);
	virtual void PlayerThink(CBasePlayer *pPlayer);
	virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer);
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	virtual int ItemShouldRespawn(CItem *pItem);
	virtual void CheckMapConditions() {};
	virtual void CheckWinConditions();

public:
	static void HostageDied();
	static bool PlayerCanBuy(CBasePlayer *pPlayer);

	float FillAccountTime;
	float ServerRestartTime;
	BOOL fInBuyArea;
	BOOL fVisitedBuyArea;
	bool fVGUIMenus;
};

enum GrenCatchType : int
{
	GRENADETYPE_NONE  = 0,
	GRENADETYPE_SMOKE,
	GRENADETYPE_FLASH,
};

class CBaseGrenCatch: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	virtual void Think();
	virtual void Touch(CBaseEntity *pOther);

public:
	static TYPEDESCRIPTION m_SaveData[];

	GrenCatchType m_NeedGrenadeType;
	string_t sTriggerOnGrenade;
	string_t sDisableOnGrenade;
	bool m_fSmokeTouching;
	bool m_fFlashTouched;
};

const int MAX_ITEM_COUNTS = 32;

class CFuncWeaponCheck: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Touch(CBaseEntity *pOther);

public:
	static TYPEDESCRIPTION m_SaveData[];

private:
	string_t sTriggerWithItems;
	string_t sTriggerNoItems;
	string_t sMaster;
	string_t sItemName[MAX_ITEM_COUNTS];
	int iItemCount;
	int iAnyWeapon;
};
