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
