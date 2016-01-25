#include "precompiled.h"

// Begin defusing the bomb

/* <539f0e> ../cstrike/dlls/bot/states/cs_bot_defuse_bomb.cpp:16 */
void DefuseBombState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
	me->Crouch();
	me->SetDisposition(CCSBot::SELF_DEFENSE);
	me->GetChatter()->Say("DefusingBomb");
}

// Defuse the bomb

/* <539eac> ../cstrike/dlls/bot/states/cs_bot_defuse_bomb.cpp:27 */
void DefuseBombState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
	const Vector *bombPos = me->GetGameState()->GetBombPosition();
	CCSBotManager *ctrl = TheCSBots();

	if (bombPos == NULL)
	{
		me->PrintIfWatched("In Defuse state, but don't know where the bomb is!\n");
		me->Idle();
		return;
	}

	// look at the bomb
	me->SetLookAt("Defuse bomb", bombPos, PRIORITY_HIGH);

	// defuse...
	me->UseEnvironment();

	if (gpGlobals->time - me->GetStateTimestamp() > 1.0f)
	{
		// if we missed starting the defuse, give up
		if (ctrl->GetBombDefuser() == NULL)
		{
			me->PrintIfWatched("Failed to start defuse, giving up\n");
			me->Idle();
			return;
		}
		else if (ctrl->GetBombDefuser() != me)
		{
			// if someone else got the defuse, give up
			me->PrintIfWatched("Someone else started defusing, giving up\n");
			me->Idle();
			return;
		}
	}

	// if bomb has been defused, give up
	if (!ctrl->IsBombPlanted())
	{
		me->Idle();
		return;
	}
}

/* <539e36> ../cstrike/dlls/bot/states/cs_bot_defuse_bomb.cpp:73 */
void DefuseBombState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
	me->StandUp();
	me->ResetStuckMonitor();
	me->SetTask(CCSBot::SEEK_AND_DESTROY);
	me->SetDisposition(CCSBot::ENGAGE_AND_INVESTIGATE);
	me->ClearLookAt();
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
