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

#include "precompiled.h"

// Follow our leader
void FollowState::OnEnter(CCSBot *me)
{
	me->StandUp();
	me->Run();
	me->DestroyPath();

	m_isStopped = false;
	m_stoppedTimestamp = 0.0f;

	// to force immediate repath
	m_lastLeaderPos.x = -99999999.9f;
	m_lastLeaderPos.y = -99999999.9f;
	m_lastLeaderPos.z = -99999999.9f;

	m_lastSawLeaderTime = 0;

	// set re-pathing frequency
	m_repathInterval.Invalidate();

	m_isSneaking = false;

	m_walkTime.Invalidate();
	m_isAtWalkSpeed = false;

	m_leaderMotionState = INVALID;
	m_idleTimer.Start(RANDOM_FLOAT(2.0f, 5.0f));
}

// Determine the leader's motion state by tracking his speed
void FollowState::ComputeLeaderMotionState(float leaderSpeed)
{
	// walk = 130, run = 250
	const float runWalkThreshold = 140.0f;
	const float walkStopThreshold = 10.0f;
	LeaderMotionStateType prevState = m_leaderMotionState;
	if (leaderSpeed > runWalkThreshold)
	{
		m_leaderMotionState = RUNNING;
		m_isAtWalkSpeed = false;
	}
	else if (leaderSpeed > walkStopThreshold)
	{
		// track when began to walk
		if (!m_isAtWalkSpeed)
		{
			m_walkTime.Start();
			m_isAtWalkSpeed = true;
		}

		const float minWalkTime = 0.25f;
		if (m_walkTime.GetElapsedTime() > minWalkTime)
		{
			m_leaderMotionState = WALKING;
		}
	}
	else
	{
		m_leaderMotionState = STOPPED;
		m_isAtWalkSpeed = false;
	}

	// track time spent in this motion state
	if (prevState != m_leaderMotionState)
	{
		m_leaderMotionStateTime.Start();
		m_waitTime = RANDOM_FLOAT(1.0f, 3.0f);
	}
}

// Follow our leader
// TODO: Clean up this nasty mess
void FollowState::OnUpdate(CCSBot *me)
{
	// if we lost our leader, give up
	if (!m_leader || !m_leader->IsAlive())
	{
		me->Idle();
		return;
	}

	// if we are carrying the bomb and at a bombsite, plant
	if (me->IsCarryingBomb() && me->IsAtBombsite())
	{
		// plant it
		me->SetTask(CCSBot::PLANT_BOMB);
		me->PlantBomb();

		// radio to the team
		me->GetChatter()->PlantingTheBomb(me->GetPlace());
		return;
	}

	// look around
	me->UpdateLookAround();

	// if we are moving, we are not idle
	if (me->IsNotMoving() == false)
		m_idleTimer.Start(RANDOM_FLOAT(2.0f, 5.0f));

	// compute the leader's speed
	float leaderSpeed = Vector2D(m_leader->pev->velocity.x, m_leader->pev->velocity.y).Length();

	// determine our leader's movement state
	ComputeLeaderMotionState(leaderSpeed);

	// track whether we can see the leader
	bool isLeaderVisible;
	if (me->IsVisible(&m_leader->pev->origin))
	{
		m_lastSawLeaderTime = gpGlobals->time;
		isLeaderVisible = true;
	}
	else
	{
		isLeaderVisible = false;
	}

	// determine whether we should sneak or not
	const float farAwayRange = 750.0f;
	if ((m_leader->pev->origin - me->pev->origin).IsLengthGreaterThan(farAwayRange))
	{
		// far away from leader - run to catch up
		m_isSneaking = false;
	}
	else if (isLeaderVisible)
	{
		// if we see leader walking and we are nearby, walk
		if (m_leaderMotionState == WALKING)
			m_isSneaking = true;

		// if we are sneaking and our leader starts running, stop sneaking
		if (m_isSneaking && m_leaderMotionState == RUNNING)
			m_isSneaking = false;
	}

	// if we haven't seen the leader for a long time, run
	const float longTime = 20.0f;
	if (gpGlobals->time - m_lastSawLeaderTime > longTime)
		m_isSneaking = false;

	if (m_isSneaking)
		me->Walk();
	else
		me->Run();

	bool repath = false;

	// if the leader has stopped, hide nearby
	const float nearLeaderRange = 250.0f;
	if (!me->HasPath() && m_leaderMotionState == STOPPED && m_leaderMotionStateTime.GetElapsedTime() > m_waitTime)
	{
		// throttle how often this check occurs
		m_waitTime += RANDOM_FLOAT(1.0f, 3.0f);

		// the leader has stopped - if we are close to him, take up a hiding spot
		if ((m_leader->pev->origin - me->pev->origin).IsLengthLessThan(nearLeaderRange))
		{
			const float hideRange = 250.0f;
			if (me->TryToHide(nullptr, -1.0f, hideRange, false, USE_NEAREST))
			{
				me->ResetStuckMonitor();
				return;
			}
		}
	}

	// if we have been idle for awhile, move
	if (m_idleTimer.IsElapsed())
	{
		repath = true;

		// always walk when we move such a short distance
		m_isSneaking = true;
	}

	// if our leader has moved, repath (don't repath if leading is stopping)
	if (leaderSpeed > 100.0f && m_leaderMotionState != STOPPED)
	{
		repath = true;
	}

	// move along our path
	if (me->UpdatePathMovement(NO_SPEED_CHANGE) != CCSBot::PROGRESSING)
	{
		me->DestroyPath();
	}

	// recompute our path if necessary
	if (repath && m_repathInterval.IsElapsed())
	{
		// recompute our path to keep us near our leader
		m_lastLeaderPos = m_leader->pev->origin;

		me->ResetStuckMonitor();

		const float runSpeed = 200.0f;
		const float collectRange = (leaderSpeed > runSpeed) ? 600.0f : 400.0f;
		FollowTargetCollector collector(m_leader);
		SearchSurroundingAreas(TheNavAreaGrid.GetNearestNavArea(&m_lastLeaderPos), &m_lastLeaderPos, collector, collectRange);

		if (cv_bot_debug.value > 0.0f)
		{
			for (int i = 0; i < collector.m_targetAreaCount; i++)
				collector.m_targetArea[i]->Draw(255, 0, 0, 2);
		}

		// move to one of the collected areas
		if (collector.m_targetAreaCount)
		{
			CNavArea *target = nullptr;
			Vector targetPos;

			// if we are idle, pick a random area
			if (m_idleTimer.IsElapsed())
			{
				target = collector.m_targetArea[RANDOM_LONG(0, collector.m_targetAreaCount - 1)];
				targetPos = *target->GetCenter();
				me->PrintIfWatched("%4.1f: Bored. Repathing to a new nearby area\n", gpGlobals->time);
			}
			else
			{
				me->PrintIfWatched("%4.1f: Repathing to stay with leader.\n", gpGlobals->time);

				// find closest area to where we are
				CNavArea *area;
				float closeRangeSq = 9999999999.9f;
				Vector close;

				for (int a = 0; a < collector.m_targetAreaCount; a++)
				{
					area = collector.m_targetArea[a];
					area->GetClosestPointOnArea(&me->pev->origin, &close);

					real_t rangeSq = (me->pev->origin - close).LengthSquared();
					if (rangeSq < closeRangeSq)
					{
						target = area;
						targetPos = close;
						closeRangeSq = rangeSq;
					}
				}
			}

			if (!me->ComputePath(target, nullptr, FASTEST_ROUTE))
			{
				me->PrintIfWatched("Pathfind to leader failed.\n");
			}

			// throttle how often we repath
			m_repathInterval.Start(0.5f);
			m_idleTimer.Reset();
		}
	}
}

void FollowState::OnExit(CCSBot *me)
{
	;
}
