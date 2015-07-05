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

#ifndef MORTAR_H
#define MORTAR_H
#ifdef _WIN32
#pragma once
#endif

/* <f5dea> ../cstrike/dlls/mortar.cpp:31 */
class CFuncMortarField: public CBaseToggle
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseToggle::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT FieldUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[6];

public:
	int m_iszXController;
	int m_iszYController;
	float m_flSpread;
	float m_flDelay;
	int m_iCount;
	int m_fControl;

};/* size: 336, cachelines: 6, members: 8 */

/* <f5f11> ../cstrike/dlls/mortar.cpp:192 */
class CMortar: public CGrenade
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);

#endif // HOOK_GAMEDLL

	NOBODY void EXPORT MortarExplode(void);

public:
	int m_spriteTexture;

};/* size: 504, cachelines: 8, members: 2 */

#endif // MORTAR_H
