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

// Begin attacking
void AttackState::OnEnter(CCSBot *me)
{
	CBasePlayer *pEnemy = me->GetEnemy();

	// store our posture when the attack began
	me->PushPostureContext();
	me->DestroyPath();

	// if we are using a knife, try to sneak up on the enemy
	if (pEnemy && me->IsUsingKnife() && !me->IsPlayerFacingMe(pEnemy))
		me->Walk();
	else
		me->Run();

	me->GetOffLadder();
	me->ResetStuckMonitor();

	m_repathTimer.Invalidate();
	m_haveSeenEnemy = me->IsEnemyVisible();
	m_nextDodgeStateTimestamp = 0.0f;
	m_firstDodge = true;
	m_isEnemyHidden = false;
	m_reacquireTimestamp = 0.0f;

	m_pinnedDownTimestamp = gpGlobals->time + RANDOM_FLOAT(7.0f, 10.0f);
	m_shieldToggleTimestamp = gpGlobals->time + RANDOM_FLOAT(2.0f, 10.0f);
	m_shieldForceOpen = false;

	// if we encountered someone while escaping, grab our weapon and fight!
	if (me->IsEscapingFromBomb())
		me->EquipBestWeapon();

	if (me->IsUsingKnife())
	{
		// can't crouch and hold with a knife
		m_crouchAndHold = false;
		me->StandUp();
	}
	else
	{
		// decide whether to crouch where we are, or run and gun (if we havent already - see CCSBot::Attack())
		if (!m_crouchAndHold)
		{
			if (pEnemy)
			{
				const float crouchFarRange = 750.0f;
				float crouchChance;

				// more likely to crouch if using sniper rifle or if enemy is far away
				if (me->IsUsingSniperRifle())
					crouchChance = 50.0f;
				else if ((me->pev->origin - pEnemy->pev->origin).IsLengthGreaterThan(crouchFarRange))
					crouchChance = 50.0f;
				else
					crouchChance = 20.0f * (1.0f - me->GetProfile()->GetAggression());

				if (RANDOM_FLOAT(0.0f, 100.0f) < crouchChance)
				{
					// make sure we can still see if we crouch
					TraceResult result;

					Vector origin = me->pev->origin;
					if (!me->IsCrouching())
					{
						// we are standing, adjust for lower crouch origin
						origin.z -= 20.0f;
					}

					UTIL_TraceLine(origin, pEnemy->EyePosition(), ignore_monsters, ignore_glass, ENT(me->pev), &result);

					if (result.flFraction == 1.0f)
					{
						m_crouchAndHold = true;
					}
				}
			}
		}

		if (m_crouchAndHold)
		{
			me->Crouch();
			me->PrintIfWatched("Crouch and hold attack!\n");
		}
	}

	m_scopeTimestamp = 0;
	m_didAmbushCheck = false;

	float skill = me->GetProfile()->GetSkill();

	// tendency to dodge is proportional to skill
	float dodgeChance = 80.0f * skill;

	if (me->IsUsingKnife())
	{
		dodgeChance *= 2.0f;
	}

	// high skill bots always dodge if outnumbered, or they see a sniper
	if (skill > 0.5f && me->IsOutnumbered())
	{
		dodgeChance = 100.0f;
	}

	m_dodge = (RANDOM_FLOAT(0.0f, 100.0f) < dodgeChance) != 0;

	// decide whether we might bail out of this fight
	m_isCoward = (RANDOM_FLOAT(0.0f, 100.0f) > 100.0f * me->GetProfile()->GetAggression());
}

void AttackState::StopAttacking(CCSBot *me)
{
	if (me->m_task == CCSBot::SNIPING)
	{
		// stay in our hiding spot
		me->Hide(me->GetLastKnownArea(), -1.0f, 50.0f);
	}
	else
	{
		me->StopAttacking();
	}
}

// Perform attack behavior
void AttackState::OnUpdate(CCSBot *me)
{
	// can't be stuck while attacking
	me->ResetStuckMonitor();
	me->StopRapidFire();

	CBasePlayerWeapon *pWeapon = me->GetActiveWeapon();
	if (pWeapon)
	{
		if (pWeapon->m_iId == WEAPON_C4 ||
			pWeapon->m_iId == WEAPON_HEGRENADE ||
			pWeapon->m_iId == WEAPON_FLASHBANG ||
			pWeapon->m_iId == WEAPON_SMOKEGRENADE)
		{
			me->EquipBestWeapon();
		}
	}

	CBasePlayer *pEnemy = me->GetEnemy();
	if (!pEnemy)
	{
		StopAttacking(me);
		return;
	}

	// keep track of whether we have seen our enemy at least once yet
	if (!m_haveSeenEnemy)
		m_haveSeenEnemy = me->IsEnemyVisible();

	// Retreat check
	// Do not retreat if the enemy is too close
	if (m_retreatTimer.IsElapsed())
	{
		// If we've been fighting this battle for awhile, we're "pinned down" and
		// need to do something else.
		// If we are outnumbered, retreat.
		bool isPinnedDown = (gpGlobals->time > m_pinnedDownTimestamp);

		if (isPinnedDown ||
			(me->IsOutnumbered() && m_isCoward) ||
			(me->OutnumberedCount() >= 2 && me->GetProfile()->GetAggression() < 1.0f))
		{
			// tell our teammates our plight
			if (isPinnedDown)
				me->GetChatter()->PinnedDown();
			else
				me->GetChatter()->Scared();

			m_retreatTimer.Start(RANDOM_FLOAT(3.0f, 15.0f));

			// try to retreat
			if (me->TryToRetreat())
			{
				// if we are a sniper, equip our pistol so we can fire while retreating
				if (me->IsUsingSniperRifle())
				{
					me->EquipPistol();
				}
			}
			else
			{
				me->PrintIfWatched("I want to retreat, but no safe spots nearby!\n");
			}
		}
	}

	// Knife fighting
	// We need to pathfind right to the enemy to cut him
	if (me->IsUsingKnife())
	{
		// can't crouch and hold with a knife
		m_crouchAndHold = false;
		me->StandUp();

		// if we are using a knife and our prey is looking towards us, run at him
		if (me->IsPlayerFacingMe(pEnemy))
		{
			me->ForceRun(5.0f);
			me->Hurry(10.0f);
		}
		else
		{
			me->Walk();
		}

		// slash our victim
		me->FireWeaponAtEnemy();

		// if our victim has moved, repath
		bool repath = false;
		if (me->HasPath())
		{
			const float repathRange = 100.0f;
			if ((me->GetPathEndpoint() - pEnemy->pev->origin).IsLengthGreaterThan(repathRange))
			{
				repath = true;
			}
		}
		else
		{
			repath = true;
		}

		if (repath && m_repathTimer.IsElapsed())
		{
			me->ComputePath(TheNavAreaGrid.GetNearestNavArea(&pEnemy->pev->origin), &pEnemy->pev->origin, FASTEST_ROUTE);

			const float repathInterval = 0.5f;
			m_repathTimer.Start(repathInterval);
		}

		// move towards victim
		if (me->UpdatePathMovement(NO_SPEED_CHANGE) != CCSBot::PROGRESSING)
		{
			me->DestroyPath();
		}

		return;
	}

	// Simple shield usage
	if (me->HasShield())
	{
		if (me->IsEnemyVisible() && !m_shieldForceOpen)
		{
			if (!me->IsRecognizedEnemyReloading() && !me->IsReloading() && me->IsPlayerLookingAtMe(pEnemy))
			{
				// close up - enemy is pointing his gun at us
				if (!me->IsProtectedByShield())
					me->SecondaryAttack();
			}
			else
			{
				// enemy looking away or reloading his weapon - open up and shoot him
				if (me->IsProtectedByShield())
					me->SecondaryAttack();
			}
		}
		else
		{
			// can't see enemy, open up
			if (me->IsProtectedByShield())
				me->SecondaryAttack();
		}

		if (gpGlobals->time > m_shieldToggleTimestamp)
		{
			m_shieldToggleTimestamp = gpGlobals->time + RANDOM_FLOAT(0.5, 2.0f);

			// toggle shield force open
			m_shieldForceOpen = !m_shieldForceOpen;
		}
	}

	// check if our weapon range is bad and we should switch to pistol
	if (me->IsUsingSniperRifle())
	{
		// if we have a sniper rifle and our enemy is too close, switch to pistol
		// NOTE: Must be larger than NO_ZOOM range in AdjustZoom()
		const float sniperMinRange = 310.0f;
		if ((pEnemy->pev->origin - me->pev->origin).IsLengthLessThan(sniperMinRange))
			me->EquipPistol();
	}
	else if (me->IsUsingShotgun())
	{
		// if we have a shotgun equipped and enemy is too far away, switch to pistol
		const float shotgunMaxRange = 1000.0f;
		if ((pEnemy->pev->origin - me->pev->origin).IsLengthGreaterThan(shotgunMaxRange))
			me->EquipPistol();
	}

	// if we're sniping, look through the scope - need to do this here in case a reload resets our scope
	if (me->IsUsingSniperRifle())
	{
		// for Scouts and AWPs, we need to wait for zoom to resume
		if (me->m_bResumeZoom)
		{
			m_scopeTimestamp = gpGlobals->time;
			return;
		}

		Vector toAimSpot3D = me->m_aimSpot - me->pev->origin;
		float targetRange = toAimSpot3D.Length();

		// dont adjust zoom level if we're already zoomed in - just fire
		if (me->GetZoomLevel() == CCSBot::NO_ZOOM && me->AdjustZoom(targetRange))
			m_scopeTimestamp = gpGlobals->time;

		const float waitScopeTime = 0.2f + me->GetProfile()->GetReactionTime();
		if (gpGlobals->time - m_scopeTimestamp < waitScopeTime)
		{
			// force us to wait until zoomed in before firing
			return;
		}
	}

	// see if we "notice" that our prey is dead
	if (me->IsAwareOfEnemyDeath())
	{
		// let team know if we killed the last enemy
		if (me->GetLastVictimID() == pEnemy->entindex() && me->GetNearbyEnemyCount() <= 1)
		{
			me->GetChatter()->KilledMyEnemy(pEnemy->entindex());
		}

		StopAttacking(me);
		return;
	}

	float notSeenEnemyTime = gpGlobals->time - me->GetLastSawEnemyTimestamp();

	// if we haven't seen our enemy for a moment, continue on if we dont want to fight, or decide to ambush if we do
	if (!me->IsEnemyVisible())
	{
		// attend to nearby enemy gunfire
		if (notSeenEnemyTime > 0.5f && me->CanHearNearbyEnemyGunfire())
		{
			// give up the attack, since we didn't want it in the first place
			StopAttacking(me);

			me->SetLookAt("Nearby enemy gunfire", me->GetNoisePosition(), PRIORITY_HIGH, 0.0f);
			me->PrintIfWatched("Checking nearby threatening enemy gunfire!\n");
			return;
		}

		// check if we have lost track of our enemy during combat
		if (notSeenEnemyTime > 0.25f)
		{
			m_isEnemyHidden = true;
		}

		if (notSeenEnemyTime > 0.1f)
		{
			if (me->GetDisposition() == CCSBot::ENGAGE_AND_INVESTIGATE)
			{
				// decide whether we should hide and "ambush" our enemy
				if (m_haveSeenEnemy && !m_didAmbushCheck)
				{
					const float hideChance = 33.3f;

					if (RANDOM_FLOAT(0.0, 100.0f) < hideChance)
					{
						float ambushTime = RANDOM_FLOAT(3.0f, 15.0f);

						// hide in ambush nearby
						// TODO: look towards where we know enemy is
						const Vector *spot = FindNearbyRetreatSpot(me, 200.0f);
						if (spot)
						{
							me->IgnoreEnemies(1.0f);
							me->Run();
							me->StandUp();
							me->Hide(spot, ambushTime, true);
							return;
						}
					}

					// don't check again
					m_didAmbushCheck = true;
				}
			}
			else
			{
				// give up the attack, since we didn't want it in the first place
				StopAttacking(me);
				return;
			}
		}
	}
	else
	{
		// we can see the enemy again - reset our ambush check
		m_didAmbushCheck = false;

		// if the enemy is coming out of hiding, we need time to react
		if (m_isEnemyHidden)
		{
			m_reacquireTimestamp = gpGlobals->time + me->GetProfile()->GetReactionTime();
			m_isEnemyHidden = false;
		}
	}

	// if we haven't seen our enemy for a long time, chase after them
	float chaseTime = 2.0f + 2.0f * (1.0f - me->GetProfile()->GetAggression());

	// if we are sniping, be very patient
	if (me->IsUsingSniperRifle())
		chaseTime += 3.0f;
	// if we are crouching, be a little patient
	else if (me->IsCrouching())
		chaseTime += 1.0f;

	// if we can't see the enemy, and have either seen him but currently lost sight of him,
	// or haven't yet seen him, chase after him (unless we are a sniper)
	if (!me->IsEnemyVisible() && (notSeenEnemyTime > chaseTime || !m_haveSeenEnemy))
	{
		// snipers don't chase their prey - they wait for their prey to come to them
		if (me->GetTask() == CCSBot::SNIPING)
		{
			StopAttacking(me);
			return;
		}
		else
		{
			// move to last known position of enemy
			me->SetTask(CCSBot::MOVE_TO_LAST_KNOWN_ENEMY_POSITION, pEnemy);
			me->MoveTo(&me->GetLastKnownEnemyPosition());
			return;
		}
	}

	// if we can't see our enemy at the moment, and were shot by
	// a different visible enemy, engage them instead
	const float hurtRecentlyTime = 3.0f;
	if (!me->IsEnemyVisible() &&
		me->GetTimeSinceAttacked() < hurtRecentlyTime &&
		me->GetAttacker() &&
		me->GetAttacker() != me->GetEnemy())
	{
		// if we can see them, attack, otherwise panic
		if (me->IsVisible(me->GetAttacker(), CHECK_FOV))
		{
			me->Attack(me->GetAttacker());
			me->PrintIfWatched("Switching targets to retaliate against new attacker!\n");
		}
		return;
	}

	if (gpGlobals->time > m_reacquireTimestamp)
		me->FireWeaponAtEnemy();

	// do dodge behavior
	// If sniping or crouching, stand still.
	if (m_dodge && !me->IsUsingSniperRifle() && !m_crouchAndHold)
	{
		Vector toEnemy = pEnemy->pev->origin - me->pev->origin;
		float range = toEnemy.Length2D();

		const float hysterisRange = 125.0f;		// (+/-) m_combatRange

		float minRange = me->GetCombatRange() - hysterisRange;
		float maxRange = me->GetCombatRange() + hysterisRange;

		// move towards (or away from) enemy if we are using a knife, behind a corner, or we aren't very skilled
		if (me->GetProfile()->GetSkill() < 0.66f || !me->IsEnemyVisible())
		{
			if (range > maxRange)
				me->MoveForward();
			else if (range < minRange)
				me->MoveBackward();
		}

		// don't dodge if enemy is facing away
		const float dodgeRange = 2000.0f;
		if (range > dodgeRange || !me->IsPlayerFacingMe(pEnemy))
		{
			m_dodgeState = STEADY_ON;
			m_nextDodgeStateTimestamp = 0.0f;
		}
		else if (gpGlobals->time >= m_nextDodgeStateTimestamp)
		{
			int next;

			// select next dodge state that is different that our current one
			do
			{
				// high-skill bots may jump when first engaging the enemy (if they are moving)
				const float jumpChance = 33.3f;
				if (m_firstDodge && me->GetProfile()->GetSkill() > 0.5f && RANDOM_FLOAT(0, 100) < jumpChance && !me->IsNotMoving())
					next = RANDOM_LONG(0, NUM_ATTACK_STATES - 1);
				else
					next = RANDOM_LONG(0, NUM_ATTACK_STATES - 2);
			}
			while (!m_firstDodge && next == m_dodgeState);

			m_dodgeState = (DodgeStateType)next;
			m_nextDodgeStateTimestamp = gpGlobals->time + RANDOM_FLOAT(0.3f, 1.0f);
			m_firstDodge = false;
		}

		switch (m_dodgeState)
		{
		case STEADY_ON:
		{
			break;
		}
		case SLIDE_LEFT:
		{
			me->StrafeLeft();
			break;
		}
		case SLIDE_RIGHT:
		{
			me->StrafeRight();
			break;
		}
		case JUMP:
		{
			if (me->m_isEnemyVisible)
			{
				me->Jump();
			}
			break;
		}
		}
	}
}

// Finish attack
void AttackState::OnExit(CCSBot *me)
{
	me->PrintIfWatched("AttackState:OnExit()\n");

	m_crouchAndHold = false;

	// clear any noises we heard during battle
	me->ForgetNoise();
	me->ResetStuckMonitor();

	// resume our original posture
	me->PopPostureContext();

	// put shield away
	if (me->IsProtectedByShield())
		me->SecondaryAttack();

	me->StopRapidFire();
	me->ClearSurpriseDelay();
}
