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

#ifndef AMMO_H
#define AMMO_H
#ifdef _WIN32
#pragma once
#endif

/* <9792> ../cstrike/dlls/ammo.cpp:14 */
class C9MMAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <97df> ../cstrike/dlls/ammo.cpp:40 */
class CBuckShotAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <982c> ../cstrike/dlls/ammo.cpp:67 */
class C556NatoAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <9879> ../cstrike/dlls/ammo.cpp:93 */
class C556NatoBoxAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <98c6> ../cstrike/dlls/ammo.cpp:119 */
class C762NatoAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <9913> ../cstrike/dlls/ammo.cpp:145 */
class C45ACPAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <9960> ../cstrike/dlls/ammo.cpp:171 */
class C50AEAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <99ad> ../cstrike/dlls/ammo.cpp:197 */
class C338MagnumAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <99fa> ../cstrike/dlls/ammo.cpp:224 */
class C57MMAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <9a47> ../cstrike/dlls/ammo.cpp:249 */
class C357SIGAmmo: public CBasePlayerAmmo
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual BOOL AddAmmo(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	BOOL AddAmmo_(CBaseEntity *pOther);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

#endif // AMMO_H
