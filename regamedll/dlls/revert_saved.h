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

#ifndef REVERT_SAVED_H
#define REVERT_SAVED_H
#ifdef _WIN32
#pragma once
#endif

/* <14f018> ../cstrike/dlls/player.cpp:9446 */
class CRevertSaved: public CPointEntity
{
public:
	NOBODY void KeyValue(KeyValueData *pkvd);
	NOBODY int Save(CSave &save);
	NOBODY int Restore(CRestore &restore);
	NOBODY void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT MessageThink(void);
	NOBODY void EXPORT LoadThink(void);

public:
	inline float Duration(void)
	{
		return pev->dmg_take;
	}
	inline float HoldTime(void)
	{
		return pev->dmg_save;
	}
	inline float MessageTime(void)
	{
		return m_messageTime;
	}
	inline float LoadTime(void)
	{
		return m_loadTime;
	}
	inline void SetDuration(float duration)
	{
		pev->dmg_take = duration;
	}
	inline void SetHoldTime(float hold)
	{
		pev->dmg_save = hold;
	}
	inline void SetMessageTime(float time)
	{
		m_messageTime = time;
	}
	inline void SetLoadTime(float time)
	{
		m_loadTime = time;
	}

public:

#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[2];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[2];
#endif // HOOK_GAMEDLL

public:
	float m_messageTime;
	float m_loadTime;

};/* size: 160, cachelines: 3, members: 4 */

#endif // REVERT_SAVED_H
