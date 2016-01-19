#include "precompiled.h"

/* <539f0e> ../cstrike/dlls/bot/states/cs_bot_defuse_bomb.cpp:16 */
NOBODY void DefuseBombState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
//	Say(BotChatterInterface *const this,
//		const char *phraseName,
//		float lifetime,
//		float delay);  //    20
}

/* <539eac> ../cstrike/dlls/bot/states/cs_bot_defuse_bomb.cpp:27 */
NOBODY void DefuseBombState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
//	{
//		const Vector *bombPos;                        //    29
//		class CCSBotManager *ctrl;                           //    44
//	}
}

/* <539e36> ../cstrike/dlls/bot/states/cs_bot_defuse_bomb.cpp:73 */
NOBODY void DefuseBombState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
//	SetTask(CCSBot *const this,
//		enum TaskType task,
//		class CBaseEntity *entity);  //    77
//	ClearLookAt(CCSBot *const this);  //    79
}

#ifdef HOOK_GAMEDLL

void DefuseBombState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void DefuseBombState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

void DefuseBombState::OnExit(CCSBot *me)
{
	OnExit_(me);
}

#endif // HOOK_GAMEDLL
