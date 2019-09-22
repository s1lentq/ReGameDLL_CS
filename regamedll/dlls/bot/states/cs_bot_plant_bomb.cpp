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

// Plant the bomb.
void PlantBombState::OnEnter(CCSBot *me)
{
	me->Crouch();
	me->SetDisposition(CCSBot::SELF_DEFENSE);

	float yaw = me->pev->v_angle.y;
	Vector2D dir(BotCOS(yaw), BotSIN(yaw));

	Vector down(me->pev->origin.x + 10.0f * dir.x, me->pev->origin.y + 10.0f * dir.y, me->GetFeetZ());
	me->SetLookAt("Plant bomb on floor", &down, PRIORITY_HIGH);
}

// Plant the bomb.
void PlantBombState::OnUpdate(CCSBot *me)
{
	CBasePlayerWeapon *pCurrentWeapon = me->GetActiveWeapon();
	bool holdingC4 = false;
	if (pCurrentWeapon)
	{
		if (FClassnameIs(pCurrentWeapon->pev, "weapon_c4"))
			holdingC4 = true;
	}

	// if we aren't holding the C4, grab it, otherwise plant it
	if (holdingC4)
		me->PrimaryAttack();
	else
		me->SelectItem("weapon_c4");

	// if we no longer have the C4, we've successfully planted
	if (!me->IsCarryingBomb())
	{
		// move to a hiding spot and watch the bomb
		me->SetTask(CCSBot::GUARD_TICKING_BOMB);
		me->Hide();
	}

	// if we time out, it's because we slipped into a non-plantable area
	const float timeout = 5.0f;
	if (gpGlobals->time - me->GetStateTimestamp() > timeout)
		me->Idle();
}

void PlantBombState::OnExit(CCSBot *me)
{
	// equip our rifle (in case we were interrupted while holding C4)
	me->EquipBestWeapon();
	me->StandUp();
	me->ResetStuckMonitor();
	me->SetDisposition(CCSBot::ENGAGE_AND_INVESTIGATE);
	me->ClearLookAt();
}
