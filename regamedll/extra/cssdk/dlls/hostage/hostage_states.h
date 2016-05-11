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

class CHostageImprov;

class HostageState: public SimpleState<CHostageImprov *>, public IImprovEvent {
public:
	virtual ~HostageState() {}
	virtual void UpdateStationaryAnimation(CHostageImprov *improv) {}
};

class HostageStateMachine: public SimpleStateMachine<CHostageImprov *, HostageState>, public IImprovEvent {
public:
	virtual void OnMoveToSuccess(const Vector &goal) {}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) {}
	virtual void OnInjury(float amount) {}
};

class HostageIdleState: public HostageState {
public:
	virtual ~HostageIdleState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Idle"; }
	virtual void UpdateStationaryAnimation(CHostageImprov *improv) {}
	virtual void OnMoveToSuccess(const Vector &goal) {}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) {}
	virtual void OnInjury(float amount = -1.0f) {}
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
};

class HostageEscapeToCoverState: public HostageState {
public:
	virtual ~HostageEscapeToCoverState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Escape:ToCover"; }
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) {}
public:
	void SetRescueGoal(const Vector &rescueGoal) { m_rescueGoal = rescueGoal; }

private:
	Vector m_rescueGoal;
	Vector m_spot;
	bool m_canEscape;
};

class HostageEscapeLookAroundState: public HostageState {
public:
	virtual ~HostageEscapeLookAroundState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Escape:LookAround"; }

private:
	CountdownTimer m_timer;
};

class HostageEscapeState: public HostageState {
public:
	virtual ~HostageEscapeState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Escape"; }
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) {}
public:
	void ToCover() { m_behavior.SetState(&m_toCoverState); }
	void LookAround() { m_behavior.SetState(&m_lookAroundState); }
private:
	HostageEscapeToCoverState m_toCoverState;
	HostageEscapeLookAroundState m_lookAroundState;
	HostageStateMachine m_behavior;
	bool m_canEscape;
	CountdownTimer m_runTimer;
};

class HostageRetreatState: public HostageState {
public:
	virtual ~HostageRetreatState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Retreat"; }
};

class HostageFollowState: public HostageState {
public:
	virtual ~HostageFollowState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Follow"; }
	virtual void UpdateStationaryAnimation(CHostageImprov *improv) {}
public:
	void SetLeader(CBaseEntity *leader) { m_leader = leader; }
	CBaseEntity *GetLeader() const { return m_leader; }
private:
	mutable EHANDLE m_leader;
	Vector m_lastLeaderPos;
	bool m_isWaiting;
	float m_stopRange;
	CountdownTimer m_makeWayTimer;
	CountdownTimer m_impatientTimer;
	CountdownTimer m_repathTimer;
	bool m_isWaitingForFriend;
	CountdownTimer m_waitForFriendTimer;
};

class HostageAnimateState: public HostageState {
public:
	virtual ~HostageAnimateState() {}
	virtual void OnEnter(CHostageImprov *improv) {}
	virtual void OnUpdate(CHostageImprov *improv) {}
	virtual void OnExit(CHostageImprov *improv) {}
	virtual const char *GetName() const { return "Animate"; }
public:
	struct SeqInfo
	{
		int seqID;
		float holdTime;
		float rate;
	};

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

	bool IsBusy() const { return (m_sequenceCount > 0); }
	int GetCurrentSequenceID() { return m_currentSequence; }
	PerformanceType GetPerformance() const { return m_performance; }
	void SetPerformance(PerformanceType performance) { m_performance = performance; }
private:
	enum { MAX_SEQUENCES = 8 };
	struct SeqInfo m_sequence[MAX_SEQUENCES];
	int m_sequenceCount;
	int m_currentSequence;
	enum PerformanceType m_performance;
	bool m_isHolding;
	CountdownTimer m_holdTimer;
};
