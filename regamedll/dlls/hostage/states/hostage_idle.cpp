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

void HostageIdleState::OnEnter(CHostageImprov *improv)
{
	m_moveState = MoveDone;
	m_fleeTimer.Invalidate();
	m_mustFlee = false;
}

void HostageIdleState::OnUpdate(CHostageImprov *improv)
{
	if (!UTIL_ActivePlayersInGame())
		return;

	if (m_mustFlee || (improv->IsScared() && !improv->IsTerroristNearby() && m_moveState != Moving))
	{
		if (!m_mustFlee && improv->GetScareIntensity() == CHostageImprov::TERRIFIED)
			m_mustFlee = true;

		if ((improv->GetScareIntensity() == CHostageImprov::TERRIFIED || m_mustFlee) || (m_fleeTimer.IsElapsed() && improv->GetScareIntensity() > CHostageImprov::NERVOUS))
		{
			m_fleeTimer.Start(RANDOM_FLOAT(10, 20));

			const float fleeChance = 33.3f;
			const float terroristRecentTime = 5.0f;

			if (!m_mustFlee && improv->GetTimeSinceLastSawPlayer(TERRORIST) > terroristRecentTime && RANDOM_FLOAT(0, 100) < fleeChance)
				m_mustFlee = true;

			if (m_mustFlee)
			{
				m_mustFlee = false;

				const Vector *spot = FindNearbyRetreatSpot(nullptr, &improv->GetFeet(), improv->GetLastKnownArea(), 500.0, TERRORIST, false);
				if (spot)
				{
					improv->MoveTo(*spot);
					improv->Run();

					m_moveState = Moving;

					if (improv->GetScareIntensity() == CHostageImprov::TERRIFIED)
					{
						improv->Frighten(CHostageImprov::SCARED);
					}

					return;
				}
			}
		}
	}

	if (m_moveState && improv->IsAtMoveGoal())
	{
		m_moveState = NotMoving;

		improv->Stop();
		improv->FaceOutwards();

		const float crouchChance = 33.3f;
		if (improv->IsScared() && !improv->IsAtHome() && RANDOM_FLOAT(0, 100) <= crouchChance)
		{
			improv->Crouch();
		}

		return;
	}

	if (m_moveState == Moving)
	{
		improv->Run();
		return;
	}

	if (!improv->IsAtMoveGoal(75.0f))
	{
		improv->Walk();
		m_moveState = Moving;
		return;
	}

	CBasePlayer *pRescuer = improv->GetClosestVisiblePlayer(CT);
	CBasePlayer *pCaptor = improv->GetClosestVisiblePlayer(TERRORIST);

	if (pRescuer)
	{
		improv->LookAt(pRescuer->EyePosition());
		improv->Stop();

		if (pCaptor)
		{
			const float attentionRange = 700.0f;
			float rangeT = (improv->GetCentroid() - pCaptor->pev->origin).Length();

			if (rangeT < attentionRange)
			{
				const float cosTolerance = 0.95f;
				if (improv->IsAnyPlayerLookingAtMe(TERRORIST, cosTolerance))
				{
					improv->LookAt(pCaptor->EyePosition());
				}
				else
				{
					TraceResult result;
					UTIL_TraceLine(pRescuer->pev->origin, pCaptor->pev->origin, ignore_monsters, ignore_glass, pCaptor->edict(), &result);

					if (result.flFraction != 1.0f && m_disagreeTimer.IsElapsed())
					{
						improv->Disagree();
						m_disagreeTimer.Start(RANDOM_FLOAT(2, 4));
					}
				}

				return;
			}
		}
		else if (!TheCSBots()->IsRoundOver() && m_askTimer.IsElapsed())
		{
			const float closeRange = 200.0f;
			if ((pRescuer->pev->origin - improv->GetCentroid()).IsLengthLessThan(closeRange))
			{
				if (improv->IsPlayerLookingAtMe(pRescuer, 0.99))
				{
					HostageChatterType say;
					if (improv->IsTerroristNearby())
						say = HOSTAGE_CHATTER_WARN_NEARBY;
					else
						say = HOSTAGE_CHATTER_PLEASE_RESCUE_ME;

					improv->Chatter(say, false);
					m_askTimer.Start(RANDOM_FLOAT(3, 10));
				}
			}
		}

		if (m_waveTimer.IsElapsed())
		{
			CHostage *hostage = improv->GetEntity();

			const float waveRange = 250.0f;
			if ((pRescuer->pev->origin - hostage->pev->origin).IsLengthGreaterThan(waveRange))
			{
				improv->Stop();
				improv->Wave();

				improv->LookAt(pRescuer->EyePosition());
				improv->Chatter(HOSTAGE_CHATTER_CALL_TO_RESCUER, false);

				m_moveState = NotMoving;
				m_waveTimer.Start(RANDOM_FLOAT(10, 20));
			}
		}
	}
	else if (pCaptor)
	{
		improv->LookAt(pCaptor->EyePosition());
		improv->Stop();

		const float closeRange = 200.0f;
		if ((pCaptor->pev->origin - improv->GetCentroid()).IsLengthLessThan(closeRange) && improv->IsPlayerLookingAtMe(pCaptor, 0.99))
		{
			if (!m_intimidatedTimer.HasStarted())
			{
				m_intimidatedTimer.Start();
			}

			if (!improv->IsScared())
			{
				improv->Frighten(CHostageImprov::NERVOUS);
			}

			const float minThreatenTime = 1.0f;
			if ((!m_intimidatedTimer.HasStarted() || m_intimidatedTimer.IsGreaterThen(minThreatenTime)) && m_pleadTimer.IsElapsed())
			{
				improv->Chatter(HOSTAGE_CHATTER_INTIMIDATED, true);
				m_pleadTimer.Start(RANDOM_FLOAT(10, 20));
			}

			if (!improv->IsAtHome())
			{
				improv->Chatter(HOSTAGE_CHATTER_RETREAT, true);
				improv->Retreat();
			}
		}
		else
		{
			m_intimidatedTimer.Invalidate();
		}
	}
	else
	{
		improv->ClearLookAt();

		const float pushbackRange = 60.0f;
		if (pushbackRange - improv->GetAggression() * 5.0f < TheCSBots()->GetElapsedRoundTime() && m_escapeTimer.IsElapsed())
		{
			const float stayHomeDuration = 5.0f;
			m_escapeTimer.Start(stayHomeDuration);

			float sightTimeT = improv->GetTimeSinceLastSawPlayer(TERRORIST);
			float sightTimeCT = improv->GetTimeSinceLastSawPlayer(CT);

			const float waitTime = 15.0f - improv->GetAggression() * 3.0f;

			if (sightTimeT > waitTime && sightTimeCT > waitTime)
			{
				if (improv->IsTerroristNearby())
				{
					if (cv_hostage_debug.value > 0.0f)
					{
						CONSOLE_ECHO("Hostage: I want to escape, but a T is nearby\n");
					}

					m_escapeTimer.Start(waitTime);
				}
				else
				{
					improv->Escape();

					if (cv_hostage_debug.value > 0.0f)
					{
						CONSOLE_ECHO("Hostage: I'm escaping!\n");
					}
				}
			}
		}
	}
}

void HostageIdleState::OnExit(CHostageImprov *improv)
{
	improv->StandUp();
	improv->ClearFaceTo();
}

void HostageIdleState::UpdateStationaryAnimation(CHostageImprov *improv)
{
	if (improv->IsScared())
	{
		if (improv->GetScareIntensity() == CHostageImprov::TERRIFIED)
			improv->Afraid();
		else
			improv->UpdateIdleActivity(ACT_IDLE_SCARED, ACT_RESET);
	}
	else if (improv->IsAtHome())
	{
		improv->UpdateIdleActivity(ACT_IDLE, ACT_IDLE_FIDGET);
	}
	else
	{
		improv->UpdateIdleActivity(ACT_IDLE_SNEAKY, ACT_IDLE_SNEAKY_FIDGET);
	}
}
