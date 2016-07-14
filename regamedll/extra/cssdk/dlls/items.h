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

enum ItemRestType
{
	ITEM_TYPE_BUYING,	// when a player buying items
	ITEM_TYPE_TOUCHED,	// when the player touches with a weaponbox or armoury_entity
	ITEM_TYPE_EQUIPPED	// when a entity game_player_equip gives item to player or default item's on player spawn
};

// constant items
#define ITEM_ID_ANTIDOTE	2
#define ITEM_ID_SECURITY	3

enum ItemID
{
	ITEM_NONE = -1,
	ITEM_SHIELDGUN,
	ITEM_P228,
	ITEM_GLOCK,
	ITEM_SCOUT,
	ITEM_HEGRENADE,
	ITEM_XM1014,
	ITEM_C4,
	ITEM_MAC10,
	ITEM_AUG,
	ITEM_SMOKEGRENADE,
	ITEM_ELITE,
	ITEM_FIVESEVEN,
	ITEM_UMP45,
	ITEM_SG550,
	ITEM_GALIL,
	ITEM_FAMAS,
	ITEM_USP,
	ITEM_GLOCK18,
	ITEM_AWP,
	ITEM_MP5N,
	ITEM_M249,
	ITEM_M3,
	ITEM_M4A1,
	ITEM_TMP,
	ITEM_G3SG1,
	ITEM_FLASHBANG,
	ITEM_DEAGLE,
	ITEM_SG552,
	ITEM_AK47,
	ITEM_KNIFE,
	ITEM_P90,
	ITEM_NVG,
	ITEM_DEFUSEKIT,
	ITEM_KEVLAR,
	ITEM_ASSAULT,
	ITEM_LONGJUMP,
	ITEM_SODACAN,
	ITEM_HEALTHKIT,
	ITEM_ANTIDOTE,
	ITEM_BATTERY
};

class CItem: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual CBaseEntity *Respawn() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CWorldItem: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
public:
	int m_iType;
};

class CItemSuit: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemBattery: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemAntidote: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemSecurity: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemLongJump: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemKevlar: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemAssaultSuit: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};

class CItemThighPack: public CItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;
};
