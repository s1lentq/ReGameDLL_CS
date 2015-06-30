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

#ifndef AIRTANK_H
#define AIRTANK_H
#ifdef _WIN32
#pragma once
#endif

/* <468c> ../cstrike/dlls/airtank.cpp:23 */
class CAirtank: public CGrenade
{

public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Killed(entvars_t *pevAttacker, int iGib);
	virtual int BloodColor(void);
public:
	void EXPORT TankThink(void);
	void EXPORT TankTouch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	NOBODY void Spawn_(void);
	NOBODY void Precache_(void);
	NOBODY int Save_(CSave &save);
	NOBODY int Restore_(CRestore &restore);
	NOBODY void Killed_(entvars_t *pevAttacker, int iGib);
	NOBODY int BloodColor_(void);

#endif // HOOK_GAMEDLL

public:

#ifndef HOOK_GAMEDLL

	static TYPEDESCRIPTION m_SaveData[1];
#else
	static TYPEDESCRIPTION (*m_SaveData)[1];

#endif // HOOK_GAMEDLL

private:
	int m_state;

};

//NOBODY void item_airtank(entvars_t *pev);

#endif // AIRTANK_H
