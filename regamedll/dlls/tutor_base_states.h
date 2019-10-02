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

enum TutorStateType
{
	TUTORSTATE_UNDEFINED = 0,
	TUTORSTATE_LOOKING_FOR_HOSTAGE,
	TUTORSTATE_ESCORTING_HOSTAGE,
	//TUTORSTATE_LOOKING_FOR_LOST_HOSTAGE,
	TUTORSTATE_FOLLOWING_HOSTAGE_ESCORT,
	TUTORSTATE_MOVING_TO_BOMBSITE,
	TUTORSTATE_LOOKING_FOR_BOMB_CARRIER,
	TUTORSTATE_GUARDING_LOOSE_BOMB,
	TUTORSTATE_DEFUSING_BOMB,
	TUTORSTATE_GUARDING_HOSTAGE,
	TUTORSTATE_MOVING_TO_INTERCEPT_ENEMY,
	TUTORSTATE_LOOKING_FOR_HOSTAGE_ESCORT,
	TUTORSTATE_ATTACKING_HOSTAGE_ESCORT,
	TUTORSTATE_ESCORTING_BOMB_CARRIER,
	TUTORSTATE_MOVING_TO_BOMB_SITE,
	TUTORSTATE_PLANTING_BOMB,
	TUTORSTATE_GUARDING_BOMB,
	TUTORSTATE_LOOKING_FOR_LOOSE_BOMB,
	TUTORSTATE_RUNNING_AWAY_FROM_TICKING_BOMB,
	TUTORSTATE_BUYTIME,
	TUTORSTATE_WAITING_FOR_START,
};

class CBaseTutorState
{
public:
	CBaseTutorState();

	virtual ~CBaseTutorState();
	virtual TutorStateType CheckForStateTransition(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther) = 0;
	virtual const char *GetStateString() = 0;

public:
	TutorStateType GetType() const;

protected:
	static const char *m_TutorStateStrings[];
	TutorStateType m_type;
};

class CBaseTutorStateSystem
{
public:
	CBaseTutorStateSystem();

	virtual ~CBaseTutorStateSystem();
	virtual bool UpdateState(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther) = 0;
	virtual const char *GetCurrentStateString() = 0;
	virtual CBaseTutorState *ConstructNewState(TutorStateType stateType) = 0;

public:
	TutorStateType GetCurrentStateType() const;

protected:
	CBaseTutorState *m_currentState;
};
