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

#ifndef ITEMS_H
#define ITEMS_H
#ifdef _WIN32
#pragma once
#endif

// constant items
#define ITEM_HEALTHKIT		1
#define ITEM_ANTIDOTE		2
#define ITEM_SECURITY		3
#define ITEM_BATTERY		4
#define ITEM_SUIT		5

/* <e0742> ../cstrike/dlls/items.h:19 */
class CItem: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual CBaseEntity *Respawn(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer)
	{
		return FALSE;
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	CBaseEntity *Respawn_(void);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ItemTouch(CBaseEntity *pOther);
	void EXPORT Materialize(void);

};/* size: 152, cachelines: 3, members: 1 */

/* <e06f5> ../cstrike/dlls/items.cpp:38 */
class CWorldItem: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL

public:
	int m_iType;

};/* size: 156, cachelines: 3, members: 2 */

/* <e075d> ../cstrike/dlls/items.cpp:188 */
class CItemSuit: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e07aa> ../cstrike/dlls/items.cpp:219 */
class CItemBattery: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e07f7> ../cstrike/dlls/items.cpp:269 */
class CItemAntidote: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e084a> ../cstrike/dlls/items.cpp:293 */
class CItemSecurity: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e089d> ../cstrike/dlls/items.cpp:314 */
class CItemLongJump: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e08eb> ../cstrike/dlls/items.cpp:352 */
class CItemKevlar: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e093e> ../cstrike/dlls/items.cpp:393 */
class CItemAssaultSuit: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <e0991> ../cstrike/dlls/items.cpp:432 */
class CItemThighPack: public CItem
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL MyTouch(CBasePlayer *pPlayer);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	BOOL MyTouch_(CBasePlayer *pPlayer);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

#endif // ITEMS_H
