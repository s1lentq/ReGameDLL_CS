#include "precompiled.h"

// Move to the bomb on the floor and pick it up

/* <5587b3> ../cstrike/dlls/bot/states/cs_bot_fetch_bomb.cpp:17 */
void FetchBombState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
	me->DestroyPath();
}

// Move to the bomb on the floor and pick it up

/* <5587fa> ../cstrike/dlls/bot/states/cs_bot_fetch_bomb.cpp:26 */
void FetchBombState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
	if (me->IsCarryingBomb())
	{
		me->PrintIfWatched( "I picked up the bomb\n" );
		me->Idle();
		return;
	}

	CBaseEntity *bomb = TheCSBots()->GetLooseBomb();
	if (bomb != NULL)
	{
		if (!me->HasPath())
		{
			// build a path to the bomb
			if (me->ComputePath(TheNavAreaGrid.GetNavArea(&bomb->pev->origin), &bomb->pev->origin, SAFEST_ROUTE) == false)
			{
				me->PrintIfWatched("Fetch bomb pathfind failed\n");

				// go Hunt instead of Idle to prevent continuous re-pathing to inaccessible bomb
				me->Hunt();
				//return;
			}
		}
	}
	else
	{
		// someone picked up the bomb
		me->PrintIfWatched("Bomb not loose\n");
		me->Idle();
		return;
	}

	// look around
	me->UpdateLookAround();

	if (me->UpdatePathMovement() != CCSBot::PROGRESSING)
		me->Idle();
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
