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

#ifndef TUTOR_CS_STATES_H
#define TUTOR_CS_STATES_H
#ifdef _WIN32
#pragma once
#endif

/* <22bf75> ../cstrike/dlls/tutor_cs_states.cpp:53 */
class CCSTutorStateSystem: public CBaseTutorStateSystem
{
public:
	CCSTutorStateSystem(void);

	virtual ~CCSTutorStateSystem(void);
	virtual bool UpdateState(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	virtual char *GetCurrentStateString(void);
protected:
	virtual CBaseTutorState *ConstructNewState(int stateType);
};/* size: 8, cachelines: 1, members: 1 */

/* <22bfcb> ../cstrike/dlls/tutor_cs_states.cpp:141 */
class CCSTutorUndefinedState: public CBaseTutorState
{
public:
	CCSTutorUndefinedState(void);

	virtual ~CCSTutorUndefinedState(void);
	virtual int CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	virtual char *GetStateString(void);

protected:
	int HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other);
};/* size: 8, cachelines: 1, members: 1 */

/* <22c03e> ../cstrike/dlls/tutor_cs_states.cpp:198 */
class CCSTutorWaitingForStartState: public CBaseTutorState
{
public:
	CCSTutorWaitingForStartState(void);

	virtual ~CCSTutorWaitingForStartState(void);
	virtual int CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	virtual char *GetStateString(void);

protected:

	int HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other);
	int HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other);

};/* size: 8, cachelines: 1, members: 1 */

/* <22c0e2> ../cstrike/dlls/tutor_cs_states.cpp:266 */
class CCSTutorBuyMenuState: public CBaseTutorState
{
public:
	CCSTutorBuyMenuState(void);

	virtual ~CCSTutorBuyMenuState(void);
	virtual int CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	virtual char *GetStateString(void);

protected:
	int HandleRoundStart(CBaseEntity *entity, CBaseEntity *other);

};/* size: 8, cachelines: 1, members: 1 */

#endif // TUTOR_CS_STATES_H
