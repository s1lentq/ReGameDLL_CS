#include "precompiled.h"

/* <4205b1> ../cstrike/dlls/hostage/states/hostage_escape.cpp:12 */
void HostageEscapeToCoverState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
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

/* <41fd51> ../cstrike/dlls/hostage/states/hostage_escape.cpp:52 */
void HostageEscapeToCoverState::__MAKE_VHOOK(OnUpdate)(CHostageImprov *improv)
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

/* <41f65f> ../cstrike/dlls/hostage/states/hostage_escape.cpp:95 */
void HostageEscapeToCoverState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
	;
}

/* <41faaf> ../cstrike/dlls/hostage/states/hostage_escape.cpp:100 */
#ifndef HOOK_GAMEDLL
void HostageEscapeToCoverState::__MAKE_VHOOK(OnMoveToFailure)(const Vector &goal, MoveToFailureType reason)
{
	HostageEscapeState *escape = static_cast<HostageEscapeState *>(GetParent());
	escape->LookAround();
}
#endif // HOOK_GAMEDLL

/* <41fa2f> ../cstrike/dlls/hostage/states/hostage_escape.cpp:110 */
void HostageEscapeLookAroundState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
{
	m_timer.Start(RANDOM_FLOAT(5, 10));

	improv->Stop();
	improv->FaceOutwards();
}

/* <41fc67> ../cstrike/dlls/hostage/states/hostage_escape.cpp:119 */
void HostageEscapeLookAroundState::__MAKE_VHOOK(OnUpdate)(CHostageImprov *improv)
{
	improv->UpdateIdleActivity(ACT_IDLE_SNEAKY, ACT_IDLE_SNEAKY_FIDGET);

	if (m_timer.IsElapsed())
	{
		HostageEscapeState *escape = static_cast<HostageEscapeState *>(GetParent());
		escape->ToCover();
	}
}

/* <41f693> ../cstrike/dlls/hostage/states/hostage_escape.cpp:133 */
void HostageEscapeLookAroundState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
	improv->ClearFaceTo();
}

/* <41fb6b> ../cstrike/dlls/hostage/states/hostage_escape.cpp:145 */
void HostageEscapeState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
{
	CCSBotManager *ctrl = TheCSBots();
	const CCSBotManager::Zone *zone = ctrl->GetRandomZone();

	if (zone != NULL)
	{
		m_toCoverState.SetRescueGoal(zone->m_center);

		m_behavior.Reset(improv);
		m_behavior.SetState(&m_toCoverState);
	}

	m_canEscape = true;
}

/* <41fe8e> ../cstrike/dlls/hostage/states/hostage_escape.cpp:167 */
void HostageEscapeState::__MAKE_VHOOK(OnUpdate)(CHostageImprov *improv)
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

/* <41f6c7> ../cstrike/dlls/hostage/states/hostage_escape.cpp:230 */
void HostageEscapeState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
	improv->Run();
}
