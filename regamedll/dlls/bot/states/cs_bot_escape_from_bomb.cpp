#include "precompiled.h"

/* <5499ae> ../cstrike/dlls/bot/states/cs_bot_escape_from_bomb.cpp:16 */
NOBODY void EscapeFromBombState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
//	DestroyPath(CCSBot *const this);  //    20
}

/* <549be9> ../cstrike/dlls/bot/states/cs_bot_escape_from_bomb.cpp:28 */
NOBODY void EscapeFromBombState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
//	{
//		const Vector *bombPos;                        //    30
//		{
//			class FarAwayFromPositionFunctor func;        //    48
//			class CNavArea *goalArea;                    //    49
//			FarAwayFromPositionFunctor(FarAwayFromPositionFunctor *const this,
//							const Vector *pos);  //    48
//		}
//	}
}

/* <549976> ../cstrike/dlls/bot/states/cs_bot_escape_from_bomb.cpp:60 */
NOBODY void EscapeFromBombState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
}

#ifdef HOOK_GAMEDLL

void EscapeFromBombState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void EscapeFromBombState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

void EscapeFromBombState::OnExit(CCSBot *me)
{
	OnExit_(me);
}

#endif // HOOK_GAMEDLL
