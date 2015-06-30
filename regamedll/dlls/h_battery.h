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

#ifndef H_BATTERY_H
#define H_BATTERY_H
#ifdef _WIN32
#pragma once
#endif

class CRecharge: public CBaseToggle
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ((CBaseToggle::ObjectCaps()|FCAP_CONTINUOUS_USE) & ~FCAP_ACROSS_TRANSITION);
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
public:
	void EXPORT Off(void);
	void EXPORT Recharge(void);
public:

#ifndef HOOK_GAMEDLL

	static TYPEDESCRIPTION m_SaveData[5];

#else
	static TYPEDESCRIPTION (*m_SaveData)[5];

#endif // HOOK_GAMEDLL

	float m_flNextCharge;
	int m_iReactivate;
	int m_iJuice;
	int m_iOn;
	float m_flSoundTime;

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);
	NOBODY void Precache_(void);
	NOBODY void KeyValue_(KeyValueData *pkvd);
	NOBODY int Save_(CSave &save);
	NOBODY int Restore_(CRestore &restore);
	NOBODY void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 332, cachelines: 6, members: 7 */



#endif // H_BATTERY_H
