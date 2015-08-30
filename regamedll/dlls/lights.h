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

#ifndef LIGHT_H
#define LIGHT_H
#ifdef _WIN32
#pragma once
#endif

#define SF_LIGHT_START_OFF		1

/* <e70f6> ../cstrike/dlls/lights.cpp:29 */
class CLight: public CPointEntity
{
public:
	virtual void Spawn(void);
	virtual void Restart(void);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Restart_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

private:

	int m_iStyle;
	int m_iszPattern;
	BOOL m_iStartedOff;

};/* size: 164, cachelines: 3, members: 5 */

/* <e7111> ../cstrike/dlls/lights.cpp:168 */
class CEnvLight: public CLight
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	
#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);

#endif // HOOK_GAMEDLL
};/* size: 164, cachelines: 3, members: 1 */

#endif // LIGHT_H
