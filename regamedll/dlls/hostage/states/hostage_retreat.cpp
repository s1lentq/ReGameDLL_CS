#include "precompiled.h"

/* <449fee> ../cstrike/dlls/hostage/states/hostage_retreat.cpp:12 */
void HostageRetreatState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
{
	improv->Walk();
	improv->MoveTo(improv->GetEntity()->m_vStart);
}

/* <44a220> ../cstrike/dlls/hostage/states/hostage_retreat.cpp:20 */
void HostageRetreatState::__MAKE_VHOOK(OnUpdate)(CHostageImprov *improv)
{
	if (improv->IsAtHome())
	{
		improv->Stop();
		improv->Idle();
		return;
	}

	CBasePlayer *player = improv->GetClosestVisiblePlayer(UNASSIGNED);

	if (player != NULL)
	{
		const float farRange = 400.0f;
		if ((player->pev->origin - improv->GetCentroid()).IsLengthGreaterThan(farRange))
		{
			if (player->m_iTeam == CT && !improv->IsScared())
			{
				improv->Stop();
				improv->Idle();
				return;
			}
		}
	}

	if (improv->IsScared() && improv->GetScareIntensity() == CHostageImprov::TERRIFIED)
		improv->Run();
	else
		improv->Walk();
}

/* <44a023> ../cstrike/dlls/hostage/states/hostage_retreat.cpp:79 */
void HostageRetreatState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
	;
}
