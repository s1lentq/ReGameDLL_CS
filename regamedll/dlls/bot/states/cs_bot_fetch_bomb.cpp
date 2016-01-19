#include "precompiled.h"

/* <5587b3> ../cstrike/dlls/bot/states/cs_bot_fetch_bomb.cpp:17 */
NOBODY void FetchBombState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
//	DestroyPath(CCSBot *const this);  //    19
}

/* <5587fa> ../cstrike/dlls/bot/states/cs_bot_fetch_bomb.cpp:26 */
NOBODY void FetchBombState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
//	{
//		class CCSBotManager *ctrl;                           //    28
//		class CBaseEntity *bomb;                             //    30
//		GetLooseBomb(CCSBotManager *const this);  //    30
//	}
}

#ifdef HOOK_GAMEDLL

void FetchBombState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void FetchBombState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

#endif // HOOK_GAMEDLL
