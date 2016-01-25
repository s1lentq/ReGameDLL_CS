#include "precompiled.h"

/* <5499ae> ../cstrike/dlls/bot/states/cs_bot_escape_from_bomb.cpp:16 */
void EscapeFromBombState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
	me->StandUp();
	me->Run();
	me->DestroyPath();
	me->EquipKnife();
}

// Escape from the bomb

/* <549be9> ../cstrike/dlls/bot/states/cs_bot_escape_from_bomb.cpp:28 */
void EscapeFromBombState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
	const Vector *bombPos = me->GetGameState()->GetBombPosition();

	// if we don't know where the bomb is, we shouldn't be in this state
	if (bombPos == NULL)
	{
		me->Idle();
		return;
	}

	// grab our knife to move quickly
	me->EquipKnife();

	// look around
	me->UpdateLookAround();

	if (me->UpdatePathMovement() != CCSBot::PROGRESSING)
	{
		// we have no path, or reached the end of one - create a new path far away from the bomb
		FarAwayFromPositionFunctor func(bombPos);
		CNavArea *goalArea = FindMinimumCostArea(me->GetLastKnownArea(), func);

		// if this fails, we'll try again next time
		me->ComputePath(goalArea, NULL, FASTEST_ROUTE);
	}
}

/* <549976> ../cstrike/dlls/bot/states/cs_bot_escape_from_bomb.cpp:60 */
void EscapeFromBombState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
	me->EquipBestWeapon();
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
