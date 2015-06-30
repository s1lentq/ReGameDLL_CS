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

#ifndef PATHCORNER_H
#define PATHCORNER_H
#ifdef _WIN32
#pragma once
#endif

/* <121944> ../cstrike/dlls/pathcorner.cpp:25 */
class CPathCorner: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY float GetDelay(void)
	{
		return GetDelay_();
	}
#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	float GetDelay_(void)
	{
		return m_flWait;
	}
#endif // HOOK_GAMEDLL

public:
#ifndef HOOK_GAMEDLL
	static TYPEDESCRIPTION m_SaveData[1];
#else // HOOK_GAMEDLL
	static TYPEDESCRIPTION (*m_SaveData)[1];
#endif // HOOK_GAMEDLL

private:
	float m_flWait;

};/* size: 156, cachelines: 3, members: 3 */



#endif // PATHCORNER_H
