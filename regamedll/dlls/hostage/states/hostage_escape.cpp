#include "precompiled.h"

void HostageEscapeToCoverState::OnEnter(CHostageImprov *improv)
{
	CNavPath path;
	HostagePathCost pathCost;

	improv->GetPath()->Invalidate();
	m_canEscape = false;

	if (!path.Compute(&improv->GetFeet(), &m_rescueGoal, pathCost))
		return;

	const float moveRange = 500.0f;
	int idx = path.GetSegmentIndexAlongPath(moveRange);

	if (idx < 0)
		return;

	if (idx < path.GetSegmentCount() - 1)
		++idx;

	Vector pathPos = path[idx]->pos;
	const float hidingRange = 450.0f;
	const Vector *spot = FindNearbyHidingSpot(improv->GetEntity(), &pathPos, TheNavAreaGrid.GetNearestNavArea(&pathPos), hidingRange);

	if (spot == NULL)
		spot = &pathPos;

	m_spot = *spot;

	improv->Run();
	improv->MoveTo(m_spot);

	m_canEscape = true;
}

void HostageEscapeToCoverState::OnUpdate(CHostageImprov *improv)
{
	if (!m_canEscape)
	{
		improv->Idle();
		return;
	}

	if (IsSpotOccupied(improv->GetEntity(), &m_spot))
	{
		const float emergencyHidingRange = 300.0f;
		const Vector *spot = FindNearbyHidingSpot(improv->GetEntity(), &improv->GetFeet(), improv->GetLastKnownArea(), emergencyHidingRange);

		if (spot == NULL)
		{
			HostageEscapeState *escape = static_cast<HostageEscapeState *>(GetParent());
			escape->LookAround();
			return;
		}

		m_spot = *spot;
		improv->MoveTo(m_spot);
	}

	if (improv->IsAtMoveGoal())
	{
		HostageEscapeState *escape = static_cast<HostageEscapeState *>(GetParent());
		escape->LookAround();
		return;
	}
}

void HostageEscapeToCoverState::OnExit(CHostageImprov *improv)
{
	;
}

void HostageEscapeToCoverState::OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
{
	HostageEscapeState *escape = static_cast<HostageEscapeState *>(GetParent());
	escape->LookAround();
}

void HostageEscapeLookAroundState::OnEnter(CHostageImprov *improv)
{
	m_timer.Start(RANDOM_FLOAT(5, 10));

	improv->Stop();
	improv->FaceOutwards();
}

void HostageEscapeLookAroundState::OnUpdate(CHostageImprov *improv)
{
	improv->UpdateIdleActivity(ACT_IDLE_SNEAKY, ACT_IDLE_SNEAKY_FIDGET);

	if (m_timer.IsElapsed())
	{
		HostageEscapeState *escape = static_cast<HostageEscapeState *>(GetParent());
		escape->ToCover();
	}
}

void HostageEscapeLookAroundState::OnExit(CHostageImprov *improv)
{
	improv->ClearFaceTo();
}

void HostageEscapeState::OnEnter(CHostageImprov *improv)
{
	const CCSBotManager::Zone *zone = TheCSBots()->GetRandomZone();

	if (zone != NULL)
	{
		m_toCoverState.SetRescueGoal(zone->m_center);

		m_behavior.Reset(improv);
		m_behavior.SetState(&m_toCoverState);
	}

	m_canEscape = true;
}

void HostageEscapeState::OnUpdate(CHostageImprov *improv)
{
	if (!m_canEscape || (improv->IsScared() && improv->GetScareIntensity() == CHostageImprov::TERRIFIED))
	{
		improv->Stop();
		improv->Idle();
		return;
	}

	if (m_runTimer.IsElapsed())
		improv->Walk();
	else
		improv->Run();

	CBasePlayer *player = improv->GetClosestVisiblePlayer(UNASSIGNED);

	if (player != NULL)
	{
		if (player->m_iTeam != TERRORIST)
		{
			improv->Stop();
			improv->Idle();
			return;
		}

		const float farRange = 750.0f;
		if ((player->pev->origin - improv->GetCentroid().IsLengthGreaterThan(farRange)))
		{
			improv->Frighten(CHostageImprov::NERVOUS);

			m_runTimer.Start(RANDOM_FLOAT(3, 6));
			m_behavior.SetState(&m_toCoverState);
		}
		else
		{
			improv->Frighten(CHostageImprov::SCARED);
			improv->Stop();
			improv->Idle();
			return;
		}
	}
	else
	{
		m_behavior.Update();
	}
}

void HostageEscapeState::OnExit(CHostageImprov *improv)
{
	improv->Run();
}
