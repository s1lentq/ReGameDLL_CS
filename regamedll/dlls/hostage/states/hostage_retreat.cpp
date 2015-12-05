#include "precompiled.h"

/* <449fee> ../cstrike/dlls/hostage/states/hostage_retreat.cpp:12 */
void HostageRetreatState::__MAKE_VHOOK(OnEnter)(CHostageImprov *improv)
{
	improv->Walk();
	improv->MoveTo(improv->m_hostage->m_vStart);
}

/* <44a220> ../cstrike/dlls/hostage/states/hostage_retreat.cpp:20 */
void HostageRetreatState::__MAKE_VHOOK(OnUpdate)(CHostageImprov *improv)
{
//	{
//		class CBasePlayer *player;                           //    40
//		{
//			float const farRange;                          //    45
//		}
//	}
//	OnUpdate(HostageRetreatState *const this,
//		class CHostageImprov *improv);  //    20
}

/* <44a023> ../cstrike/dlls/hostage/states/hostage_retreat.cpp:79 */
void HostageRetreatState::__MAKE_VHOOK(OnExit)(CHostageImprov *improv)
{
	;
}

#ifdef HOOK_GAMEDLL

void HostageRetreatState::OnEnter(CHostageImprov *improv)
{
	OnEnter_(improv);
}

void HostageRetreatState::OnUpdate(CHostageImprov *improv)
{
	OnUpdate_(improv);
}

void HostageRetreatState::OnExit(CHostageImprov *improv)
{
	OnExit_(improv);
}

#endif // HOOK_GAMEDLL