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

void EscapeFromBombState::OnEnter(CCSBot *me)
{
	me->StandUp();
	me->Run();
	me->DestroyPath();
	me->EquipKnife();
}

// Escape from the bomb
void EscapeFromBombState::OnUpdate(CCSBot *me)
{
	const Vector *bombPos = me->GetGameState()->GetBombPosition();

	// if we don't know where the bomb is, we shouldn't be in this state
	if (!bombPos)
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
		me->ComputePath(goalArea, nullptr, FASTEST_ROUTE);
	}
}

void EscapeFromBombState::OnExit(CCSBot *me)
{
	me->EquipBestWeapon();
}
