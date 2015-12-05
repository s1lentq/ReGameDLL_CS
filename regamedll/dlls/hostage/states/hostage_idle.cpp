#include "precompiled.h"

/* <43c558> ../cstrike/dlls/hostage/states/hostage_idle.cpp:15 */
void HostageIdleState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
{
	m_moveState = MoveDone;
	m_fleeTimer.Invalidate();
	m_mustFlee = false;
}

/* <43c197> ../cstrike/dlls/hostage/states/hostage_idle.cpp:23 */
void HostageIdleState::__MAKE_VHOOK(OnUpdate)(CHostageImprov *improv)
{

}

/* <43c59b> ../cstrike/dlls/hostage/states/hostage_idle.cpp:297 */
void HostageIdleState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
}

/* <43c783> ../cstrike/dlls/hostage/states/hostage_idle.cpp:307 */
void HostageIdleState::__MAKE_VHOOK(UpdateStationaryAnimation)(CHostageImprov *improv)
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
		improv->UpdateIdleActivity(ACT_IDLE_SNEAKY, ACT_IDLE_SNEAKY_FIDGET);
}

#ifdef HOOK_GAMEDLL

void HostageIdleState::OnEnter(CHostageImprov *improv)
{
	OnEnter_(improv);
}

void HostageIdleState::OnUpdate(CHostageImprov *improv)
{
	OnUpdate_(improv);
}

void HostageIdleState::OnExit(CHostageImprov *improv)
{
	OnExit_(improv);
}

void HostageIdleState::UpdateStationaryAnimation(CHostageImprov *improv)
{
	UpdateStationaryAnimation_(improv);
}

#endif // HOOK_GAMEDLL
