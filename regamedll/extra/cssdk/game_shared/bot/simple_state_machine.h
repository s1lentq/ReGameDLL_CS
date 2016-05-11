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

// Encapsulation of a finite-state-machine state
template<typename T>
class SimpleState {
public:
	SimpleState() { m_parent = NULL; }

	virtual ~SimpleState() {};
	virtual void OnEnter(T userData) {};		// when state is entered
	virtual void OnUpdate(T userData) {};		// state behavior
	virtual void OnExit(T userData) {};		// when state exited
	virtual const char *GetName() const = 0;	// return state name

	void SetParent(SimpleState<T> *parent)
	{
		m_parent = parent;
	}
	SimpleState<T> *GetParent() const
	{
		return m_parent;
	}

private:
	// the parent state that contains this state
	SimpleState<T> *m_parent;
};

// Encapsulation of a finite state machine
template<typename T, typename S>
class SimpleStateMachine {
public:
	SimpleStateMachine()
	{
		m_state = NULL;
	}
	void Reset(T userData)
	{
		m_userData = userData;
		m_state = NULL;
	}
	// change behavior state - WARNING: not re-entrant. Do not SetState() from within OnEnter() or OnExit()
	void SetState(S *newState)
	{
		if (m_state)
			m_state->OnExit(m_userData);

		newState->OnEnter(m_userData);

		m_state = newState;
		m_stateTimer.Start();
	}
	// how long have we been in the current state
	float GetStateDuration() const
	{
		return m_stateTimer.GetElapsedTime();
	}
	// return true if given state is current state of machine
	bool IsState(const S *state) const
	{
		return (state == m_state);
	}
	// execute current state of machine
	void Update()
	{
		if (m_state)
			m_state->OnUpdate(m_userData);
	}

protected:
	S *m_state;			// current behavior state
	IntervalTimer m_stateTimer;	// how long have we been in the current state
	T m_userData;
};
