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

#ifndef HOSTAGE_STATES_H
#define HOSTAGE_STATES_H
#ifdef _WIN32
#pragma once
#endif

class CHostageImprov;

/* <46f85d> ../cstrike/dlls/hostage/hostage_states.h:16 */
class HostageState: public SimpleState<CHostageImprov *>, public IImprovEvent
{
public:
	virtual ~HostageState(void) { };

	virtual void UpdateStationaryAnimation(CHostageImprov *improv) { };

};/* size: 12, cachelines: 1, members: 2 */

/* <46f922> ../cstrike/dlls/hostage/hostage_states.h:26 */
class HostageStateMachine: public SimpleStateMachine<CHostageImprov *, HostageState>, public IImprovEvent
{
public:
	virtual void OnMoveToSuccess(const Vector &goal)
	{
		//TODO: UNTESTED
		//Update();
	}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
	{
		//TODO: UNTESTED
		Update();
	}
	virtual void OnInjury(float amount)
	{
		//TODO: UNTESTED
		Update();
	}

	void UpdateStationaryAnimation(CHostageImprov *improv) { };

};/* size: 16, cachelines: 1, members: 2 */

/* <46fccf> ../cstrike/dlls/hostage/hostage_states.h:38 */
class HostageIdleState: public HostageState
{
public:
	virtual ~HostageIdleState(void) { };

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Idle";
	}
	virtual void UpdateStationaryAnimation(CHostageImprov *improv);
	virtual void OnMoveToSuccess(const Vector &goal)
	{
		m_moveState = MoveDone;
	}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
	{
		m_moveState = MoveFailed;
	}
	virtual void OnInjury(float amount)
	{
		m_fleeTimer.Invalidate();
		m_mustFlee = true;
	}
private:
	CountdownTimer m_waveTimer;
	CountdownTimer m_fleeTimer;
	CountdownTimer m_disagreeTimer;
	CountdownTimer m_escapeTimer;
	CountdownTimer m_askTimer;
	IntervalTimer m_intimidatedTimer;
	CountdownTimer m_pleadTimer;

	enum
	{
		NotMoving = 0,
		Moving,
		MoveDone,
		MoveFailed,
	} m_moveState;

	bool m_mustFlee;

};/* size: 72, cachelines: 2, members: 10 */

/* <46f8ec> ../cstrike/dlls/hostage/hostage_states.h:71 */
class HostageEscapeToCoverState: public HostageState
{
public:
	virtual ~HostageEscapeToCoverState(void) { };

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Escape:ToCover";
	}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason);
public:
	void SetRescueGoal(const Vector &rescueGoal);
private:
	Vector m_rescueGoal;
	Vector m_spot;
	bool m_canEscape;

};/* size: 40, cachelines: 1, members: 4 */

/* <46f907> ../cstrike/dlls/hostage/hostage_states.h:92 */
class HostageEscapeLookAroundState: public HostageState
{
public:
	virtual ~HostageEscapeLookAroundState(void) { };

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Escape:LookAround";
	}

private:
	CountdownTimer m_timer;

};/* size: 20, cachelines: 1, members: 2 */

/* <46fcea> ../cstrike/dlls/hostage/hostage_states.h:109 */
class HostageEscapeState: public HostageState
{
public:
	virtual ~HostageEscapeState(void) { };

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Escape";
	}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
	{
		//TODO: i'm unsure
		if (m_behavior.IsState(this))
			IImprovEvent::OnMoveToFailure(goal, reason);
	}
public:
	void ToCover(void);
	void LookAround(void);
private:
	HostageEscapeToCoverState m_toCoverState;
	HostageEscapeLookAroundState m_lookAroundState;
	HostageStateMachine m_behavior;
	bool m_canEscape;
	CountdownTimer m_runTimer;

};/* size: 100, cachelines: 2, members: 6 */

/* <46fd03> ../cstrike/dlls/hostage/hostage_states.h:138 */
class HostageRetreatState: public HostageState
{
public:
	virtual ~HostageRetreatState(void) { };

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Retreat";
	}

};/* size: 12, cachelines: 1, members: 1 */

/* <46fd1e> ../cstrike/dlls/hostage/hostage_states.h:149 */
class HostageFollowState: public HostageState
{
public:
	virtual ~HostageFollowState(void) { };

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Follow";
	}
	virtual void UpdateStationaryAnimation(CHostageImprov *improv);
public:
	void SetLeader(CBaseEntity *leader);
	CBaseEntity *GetLeader(void);
private:
	EHANDLE m_leader;
	Vector m_lastLeaderPos;
	bool m_isWaiting;
	float m_stopRange;
	CountdownTimer m_makeWayTimer;
	CountdownTimer m_impatientTimer;
	CountdownTimer m_repathTimer;
	bool m_isWaitingForFriend;
	CountdownTimer m_waitForFriendTimer;

};/* size: 76, cachelines: 2, members: 10 */

/* <46fd39> ../cstrike/dlls/hostage/hostage_states.h:186 */
class HostageAnimateState: public HostageState
{
public:
	virtual ~HostageAnimateState(void) { }

	virtual void OnEnter(CHostageImprov *improv);
	virtual void OnUpdate(CHostageImprov *improv);
	virtual void OnExit(CHostageImprov *improv);
	virtual const char *GetName(void) const
	{
		return "Animate";
	}
public:
	struct SeqInfo
	{
		int seqID;
		float holdTime;
		float rate;

	};/* size: 12, cachelines: 1, members: 3 */

	enum PerformanceType
	{
		None = 0,
		Walk,
		Run,
		Jump,
		Fall,
		Crouch,
		CrouchWalk,
		Calm,
		Anxious,
		Afraid,
		Sitting,
		GettingUp,
		Waving,
		LookingAround,
		Disagreeing,
		Flinching,
	};

	void Reset(void);
	void AddSequence(CHostageImprov *improv, const char *seqName, float holdTime, float rate);
	void AddSequence(CHostageImprov *improv, int activity, float holdTime, float rate);

	bool IsBusy(void)
	{
		// TODO: i'm unsure
		return (GetPerformance() != None);
	}
	bool IsPlaying(CHostageImprov *improv, const char *seqName);
	int GetCurrentSequenceID(void)
	{
		return m_currentSequence;
	}
	PerformanceType GetPerformance(void)
	{
		return m_performance;
	}
	void SetPerformance(PerformanceType performance)
	{
		m_performance = performance;
	}
	void StartSequence(CHostageImprov *improv, const SeqInfo *seqInfo);
	bool IsDoneHolding(void);

private:

	enum { MAX_SEQUENCES = 8 };

	struct SeqInfo m_sequence[ MAX_SEQUENCES ];
	int m_sequenceCount;
	int m_currentSequence;
	enum PerformanceType m_performance;
	bool m_isHolding;
	CountdownTimer m_holdTimer;

};/* size: 132, cachelines: 3, members: 7 */

#ifdef HOOK_GAMEDLL

typedef void (HostageAnimateState::*ADD_SEQUENCE_NAME)(CHostageImprov *, const char *, float, float);
typedef void (HostageAnimateState::*ADD_SEQUENCE_NUMBER)(CHostageImprov *, int, float, float);

#endif // HOOK_GAMEDLL

#endif // HOSTAGE_STATES_H
