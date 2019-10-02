/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

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
