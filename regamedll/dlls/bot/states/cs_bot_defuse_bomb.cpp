#include "precompiled.h"

// Begin defusing the bomb
void DefuseBombState::OnEnter(CCSBot *me)
{
	me->Crouch();
	me->SetDisposition(CCSBot::SELF_DEFENSE);
	me->GetChatter()->Say("DefusingBomb");
}

// Defuse the bomb
void DefuseBombState::OnUpdate(CCSBot *me)
{
	const Vector *bombPos = me->GetGameState()->GetBombPosition();

	if (!bombPos)
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
		if (!TheCSBots()->GetBombDefuser())
		{
			me->PrintIfWatched("Failed to start defuse, giving up\n");
			me->Idle();
			return;
		}
		else if (TheCSBots()->GetBombDefuser() != me)
		{
			// if someone else got the defuse, give up
			me->PrintIfWatched("Someone else started defusing, giving up\n");
			me->Idle();
			return;
		}
	}

	// if bomb has been defused, give up
	if (!TheCSBots()->IsBombPlanted())
	{
#ifdef REGAMEDLL_ADD
		if (HasRoundInfinite(SCENARIO_BLOCK_BOMB)) {
			me->GetGameState()->Reset();
			me->Hunt();
			return;
		}
#endif

		me->Idle();
		return;
	}
}

void DefuseBombState::OnExit(CCSBot *me)
{
	me->StandUp();
	me->ResetStuckMonitor();
	me->SetTask(CCSBot::SEEK_AND_DESTROY);
	me->SetDisposition(CCSBot::ENGAGE_AND_INVESTIGATE);
	me->ClearLookAt();
}
