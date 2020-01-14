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

void HostageFollowState::OnEnter(CHostageImprov *improv)
{
	improv->Chatter(HOSTAGE_CHATTER_START_FOLLOW);
	improv->Agree();

	m_isWaiting = false;
	m_isWaitingForFriend = false;

	improv->MoveTo(improv->GetFeet());

	m_lastLeaderPos = Vector(999999, 999999, 999999);

	m_makeWayTimer.Invalidate();
	m_stopRange = RANDOM_FLOAT(125, 175);

	if (improv->IsTerroristNearby())
	{
		improv->DelayedChatter(3, HOSTAGE_CHATTER_WARN_NEARBY);
	}
}

void HostageFollowState::OnUpdate(CHostageImprov *improv)
{
	// if we lost our leader, give up
	if (!m_leader)
	{
		improv->Idle();
		return;
	}

	if (m_leader->pev->deadflag != DEAD_NO)
	{
		improv->Frighten(CHostageImprov::TERRIFIED);
		improv->Idle();
		return;
	}

	real_t range = (m_leader->pev->origin - improv->GetCentroid()).Length();

	const float maxPathLength = 3000.0f;
	const float giveUpRange = 1000.0f;

	if (range > giveUpRange || (improv->GetPath()->GetSegmentCount() > 0 && improv->GetPath()->GetLength() > maxPathLength))
	{
		improv->Idle();
		return;
	}

	const float walkRange = m_stopRange + 50.0f;
	const float continueRange = m_stopRange + 20.0f;
	const float runThreshold = 140.0f;

	bool isLeaderRunning;
	float leaderSpeed = m_leader->pev->velocity.Make2D().Length();

	if (leaderSpeed > runThreshold)
	{
		isLeaderRunning = true;
		m_isWaiting = false;
	}
	else
	{
		// track when began to run
		isLeaderRunning = false;

		if (!m_isWaiting)
		{
			if (range < m_stopRange)
			{
				m_isWaiting = true;
				m_impatientTimer.Start(RANDOM_FLOAT(5.0, 20.0));
			}
		}
		else if (range > continueRange)
			m_isWaiting = false;
	}

	if (!m_isWaiting)
	{
		bool makeWay = improv->IsFriendInTheWay();

		if (makeWay && !m_isWaitingForFriend)
		{
			m_isWaitingForFriend = true;
			m_waitForFriendTimer.Start(15.0);

			improv->Stop();
			return;
		}

		if (makeWay && !m_waitForFriendTimer.IsElapsed())
		{
			improv->Stop();
			return;
		}

		if (improv->GetPath()->GetSegmentCount() <= 0 && m_repathTimer.IsElapsed())
		{
			improv->MoveTo(m_leader->pev->origin);

			m_lastLeaderPos = m_leader->pev->origin;
			m_repathTimer.Start(1.0);
		}

		if (isLeaderRunning || range > walkRange)
			improv->Run();
		else
			improv->Walk();

		const float movedRange = 35.0f;
		if ((m_lastLeaderPos - m_leader->pev->origin).IsLengthGreaterThan(movedRange))
		{
			improv->MoveTo(m_leader->pev->origin);
			m_lastLeaderPos = m_leader->pev->origin;
		}

		return;
	}

	if (m_impatientTimer.IsElapsed() && !TheCSBots()->IsRoundOver())
	{
		m_impatientTimer.Start(RANDOM_FLOAT(20.0, 30.0));

		if (improv->CanSeeRescueZone())
			improv->Chatter(HOSTAGE_CHATTER_SEE_RESCUE_ZONE, false);
		else
			improv->Chatter(HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, false);
	}

	const float closeRange = 200.0f;
	if ((m_leader->pev->origin - improv->GetCentroid()).IsLengthLessThan(closeRange))
	{
		bool makeWay = false;
		const float cosTolerance = 0.99f;

		if (improv->IsPlayerLookingAtMe((CBasePlayer *)m_leader, cosTolerance))
		{
			if (!m_makeWayTimer.HasStarted())
			{
				m_makeWayTimer.Start(RANDOM_FLOAT(0.4, 0.75));
			}
			else if (m_makeWayTimer.IsElapsed())
			{
				m_impatientTimer.Invalidate();

				Vector to = (m_leader->pev->origin - improv->GetCentroid());
				to.NormalizeInPlace();

				Vector cross(-to.y, -to.x, 0);
				if (cross.x * gpGlobals->v_forward.x - cross.y * gpGlobals->v_forward.y < 0)
					cross.y = to.x;
				else
					cross.x = to.y;

				float ground;
				float const sideStepSize = 15.0f;
				Vector sideStepPos = improv->GetFeet() + cross * sideStepSize;

				if (GetGroundHeight(&sideStepPos, &ground))
				{
#ifdef REGAMEDLL_FIXES
					if (Q_abs(ground - improv->GetFeet().z) < 18.0f)
#else
					if (Q_abs(int(ground - improv->GetFeet().z)) < 18.0f)
#endif
					{
						const float push = 20.0f;
						Vector lat = cross * push;

						improv->ApplyForce(lat);
						improv->MoveTo(sideStepPos);
						return;
					}
				}
			}
		}
		else
		{
			m_makeWayTimer.Invalidate();
		}
	}

	improv->Stop();

	CBasePlayer *pTerrorist = improv->GetClosestVisiblePlayer(TERRORIST);
	if (pTerrorist)
	{
		improv->LookAt(pTerrorist->EyePosition());
	}
	else
	{
		improv->LookAt(m_leader->EyePosition());
	}
}

void HostageFollowState::OnExit(CHostageImprov *improv)
{
	improv->Stop();
}

void HostageFollowState::UpdateStationaryAnimation(CHostageImprov *improv)
{
	if (improv->IsScared())
		improv->UpdateIdleActivity(ACT_FOLLOW_IDLE_SCARED, ACT_RESET);
	else
		improv->UpdateIdleActivity(ACT_FOLLOW_IDLE, ACT_FOLLOW_IDLE_FIDGET);
}
