#include "precompiled.h"

void HostageRetreatState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
{
	improv->Walk();
	improv->MoveTo(improv->GetEntity()->m_vStart);
}

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

void HostageRetreatState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
	;
}
