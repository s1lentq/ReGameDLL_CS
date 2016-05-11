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

// constant items
#define ITEM_HEALTHKIT		1
#define ITEM_ANTIDOTE		2
#define ITEM_SECURITY		3
#define ITEM_BATTERY		4
#define ITEM_SUIT		5

class CItem: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual CBaseEntity *Respawn() = 0;
	virtual BOOL MyTouch(CBasePlayer *pPlayer) = 0;

public:
	void EXPORT ItemTouch(CBaseEntity *pOther) = 0;
	void EXPORT Materialize() = 0;
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
