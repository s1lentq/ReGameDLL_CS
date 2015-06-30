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

#ifndef TRAINING_GAMERULES_H
#define TRAINING_GAMERULES_H
#ifdef _WIN32
#pragma once
#endif

/* <18bcdd> ../cstrike/dlls/training_gamerules.cpp:23 */
class CHalfLifeTraining: public CHalfLifeMultiplay
{
public:
	CHalfLifeTraining(void);
public:
	virtual BOOL IsMultiplayer(void)
	{
		return FALSE;
	}
	NOBODY virtual BOOL IsDeathmatch(void);
	virtual void InitHUD(CBasePlayer *pl);
	virtual void PlayerSpawn(CBasePlayer *pPlayer);
	NOBODY virtual void PlayerThink(CBasePlayer *pPlayer);
	NOBODY virtual BOOL FPlayerCanRespawn(CBasePlayer *pPlayer);
	virtual edict_t *GetPlayerSpawnSpot(CBasePlayer *pPlayer);
	NOBODY virtual void PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	NOBODY virtual int ItemShouldRespawn(CItem *pItem);
	NOBODY virtual void CheckMapConditions(void) {}
	NOBODY virtual void CheckWinConditions(void);

#ifdef HOOK_GAMEDLL

	//BOOL IsMultiplayer_(void);
	BOOL IsDeathmatch_(void);
	void InitHUD_(CBasePlayer *pl);
	void PlayerSpawn_(CBasePlayer *pPlayer);
	void PlayerThink_(CBasePlayer *pPlayer);
	BOOL FPlayerCanRespawn_(CBasePlayer *pPlayer);
	edict_t *GetPlayerSpawnSpot_(CBasePlayer *pPlayer);
	void PlayerKilled_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor);
	int ItemShouldRespawn_(CItem *pItem);
	//void CheckMapConditions_(void) {}
	void CheckWinConditions_(void);

#endif // HOOK_GAMEDLL

public:
	static void HostageDied(void);
	NOBODY static bool PlayerCanBuy(CBasePlayer *pPlayer);
private:
	float FillAccountTime;
	float ServerRestartTime;
	BOOL fInBuyArea;
	BOOL fVisitedBuyArea;
	bool fVGUIMenus;
};/* size: 728, cachelines: 12, members: 6 */

/* <18a1d5> ../cstrike/dlls/training_gamerules.cpp:252 */
class CBaseGrenCatch: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Think(void);
	NOBODY virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
	}
	void Think_(void);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[5];
#else
	static TYPEDESCRIPTION (*m_SaveData)[5];
#endif // HOOK_GAMEDLL

public:
	int m_NeedGrenadeType;
	string_t sTriggerOnGrenade;
	string_t sDisableOnGrenade;
	bool m_fSmokeTouching;
	bool m_fFlashTouched;

};/* size: 168, cachelines: 3, members: 7 */

/* <18a222> ../cstrike/dlls/training_gamerules.cpp:385 */
class CFuncWeaponCheck: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[6];
#else
	static TYPEDESCRIPTION (*m_SaveData)[6];
#endif // HOOK_GAMEDLL

private:
	string_t sTriggerWithItems;
	string_t sTriggerNoItems;
	string_t sMaster;
	unsigned int sItemName[32];
	int iItemCount;
	int iAnyWeapon;
};/* size: 300, cachelines: 5, members: 8 */

#endif //T RAINING_GAMERULES_H
