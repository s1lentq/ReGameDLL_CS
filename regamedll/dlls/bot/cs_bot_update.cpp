#include "precompiled.h"

// Lightweight maintenance, invoked frequently

/* <3c635f> ../cstrike/dlls/bot/cs_bot_update.cpp:26 */
void CCSBot::__MAKE_VHOOK(Upkeep)(void)
{
	CCSBotManager *ctrl = TheCSBots();

	if (ctrl->IsLearningMap() || !IsAlive())
		return;

	if (m_isRapidFiring)
		TogglePrimaryAttack();

	// aiming must be smooth - update often
	if (IsAimingAtEnemy())
	{
		UpdateAimOffset();

		// aim at enemy, if he's still alive
		if (m_enemy != NULL)
		{
			float feetOffset = pev->origin.z - GetFeetZ();

			if (IsEnemyVisible())
			{
				if (GetProfile()->GetSkill() > 0.5f)
				{
					const float k = 3.0f;
					m_aimSpot = (m_enemy->pev->velocity - pev->velocity) * g_flBotCommandInterval * k + m_enemy->pev->origin;
				}
				else
					m_aimSpot = m_enemy->pev->origin;

				bool aimBlocked = false;
				const float sharpshooter = 0.8f;

				if (IsUsingAWP() || IsUsingShotgun() || IsUsingMachinegun() || GetProfile()->GetSkill() < sharpshooter
					|| (IsActiveWeaponRecoilHigh() && !IsUsingPistol() && !IsUsingSniperRifle()))
				{
					if (IsEnemyPartVisible(CHEST))
					{
						// No headshots, go for the chest.
						aimBlocked = true;
					}
				}

				if (aimBlocked)
					m_aimSpot.z -= feetOffset * 0.25f;

				else if (!IsEnemyPartVisible(HEAD))
				{
					if (IsEnemyPartVisible(CHEST))
					{
						m_aimSpot.z -= feetOffset * 0.5f;
					}
					else if (IsEnemyPartVisible(LEFT_SIDE))
					{
						Vector2D to = (m_enemy->pev->origin - pev->origin).Make2D();
						to.NormalizeInPlace();

						m_aimSpot.x -= to.y * 16.0f;
						m_aimSpot.y += to.x * 16.0f;
						m_aimSpot.z -= feetOffset * 0.5f;
					}
					else if (IsEnemyPartVisible(RIGHT_SIDE))
					{
						Vector2D to = (m_enemy->pev->origin - pev->origin).Make2D();
						to.NormalizeInPlace();

						m_aimSpot.x += to.y * 16.0f;
						m_aimSpot.y -= to.x * 16.0f;
						m_aimSpot.z -= feetOffset * 0.5f;
					}
					else // FEET
						m_aimSpot.z -= (feetOffset + feetOffset);
				}
			}
			else
				m_aimSpot = m_lastEnemyPosition;

			// add in aim error
			m_aimSpot.x += m_aimOffset.x;
			m_aimSpot.y += m_aimOffset.y;
			m_aimSpot.z += m_aimOffset.z;

			Vector toEnemy = m_aimSpot - pev->origin;
			Vector idealAngle = UTIL_VecToAngles(toEnemy);

			idealAngle.x = 360.0 - idealAngle.x;
			SetLookAngles(idealAngle.y, idealAngle.x);
		}
	}
	else
	{
		if (m_lookAtSpotClearIfClose)
		{
			// dont look at spots just in front of our face - it causes erratic view rotation
			const float tooCloseRange = 100.0f;
			if ((m_lookAtSpot - pev->origin).IsLengthLessThan(tooCloseRange))
				m_lookAtSpotState = NOT_LOOKING_AT_SPOT;
		}

		switch (m_lookAtSpotState)
		{
			case NOT_LOOKING_AT_SPOT:
			{
				// look ahead
				SetLookAngles(m_lookAheadAngle, 0);
				break;
			}
			case LOOK_TOWARDS_SPOT:
			{
				UpdateLookAt();

				if (IsLookingAtPosition(&m_lookAtSpot, m_lookAtSpotAngleTolerance))
				{
					m_lookAtSpotState = LOOK_AT_SPOT;
					m_lookAtSpotTimestamp = gpGlobals->time;
				}
				break;
			}
			case LOOK_AT_SPOT:
			{
				UpdateLookAt();

				if (m_lookAtSpotDuration >= 0.0f && gpGlobals->time - m_lookAtSpotTimestamp > m_lookAtSpotDuration)
				{
					m_lookAtSpotState = NOT_LOOKING_AT_SPOT;
					m_lookAtSpotDuration = 0.0f;
				}
				break;
			}
		}

		float driftAmplitude = 2.0f;

		// have view "drift" very slowly, so view looks "alive"
		if (IsUsingSniperRifle() && IsUsingScope())
		{
			driftAmplitude = 0.5f;
		}

		m_lookYaw += driftAmplitude * BotCOS(33.0f * gpGlobals->time);
		m_lookPitch += driftAmplitude * BotSIN(13.0f * gpGlobals->time);
	}

	// view angles can change quickly
	UpdateLookAngles();
}

// Heavyweight processing, invoked less often

/* <3c6e1e> ../cstrike/dlls/bot/cs_bot_update.cpp:208 */
void CCSBot::__MAKE_VHOOK(Update)(void)
{
	CCSBotManager *ctrl = TheCSBots();

	if (ctrl->IsAnalysisRequested() && m_processMode == PROCESS_NORMAL)
	{
		ctrl->AckAnalysisRequest();
		StartAnalyzeAlphaProcess();
	}

	switch (m_processMode)
	{
	case PROCESS_LEARN:		UpdateLearnProcess(); return;
	case PROCESS_ANALYZE_ALPHA:	UpdateAnalyzeAlphaProcess(); return;
	case PROCESS_ANALYZE_BETA:	UpdateAnalyzeBetaProcess(); return;
	case PROCESS_SAVE:		UpdateSaveProcess(); return;
	}

	// update our radio chatter
	// need to allow bots to finish their chatter even if they are dead
	GetChatter()->Update();

	if (m_voiceFeedbackEndTimestamp != 0.0f 
		&& (m_voiceFeedbackEndTimestamp <= gpGlobals->time || gpGlobals->time < m_voiceFeedbackStartTimestamp))
	{
		EndVoiceFeedback(NO_FORCE);
	}

	// check if we are dead
	if (!IsAlive())
	{
		// remember that we died
		m_diedLastRound = true;
		BotDeathThink();
		return;
	}

	// show line of fire
	if ((cv_bot_traceview.value == 100.0f && IsLocalPlayerWatchingMe()) || cv_bot_traceview.value == 101.0f)
	{
		UTIL_MakeVectors(pev->punchangle + pev->v_angle);

		if (!IsFriendInLineOfFire())
		{
			Vector vecAiming = gpGlobals->v_forward;
			Vector vecSrc = GetGunPosition();

			if (m_iTeam == TERRORIST)
				UTIL_DrawBeamPoints(vecSrc, vecSrc + 2000.0f * vecAiming, 1, 255, 0, 0);
			else
				UTIL_DrawBeamPoints(vecSrc, vecSrc + 2000.0f * vecAiming, 1, 0, 50, 255);
		}
	}

	// Debug beam rendering
	if (cv_bot_traceview.value == 2.0f && IsLocalPlayerWatchingMe() || cv_bot_traceview.value == 3.0f)
		DrawApproachPoints();

	if (cv_bot_traceview.value == 4.0f && IsLocalPlayerWatchingMe() || cv_bot_traceview.value == 5.0f)
	{
		// ...
	}

	if (cv_bot_traceview.value == 1.0f && IsLocalPlayerWatchingMe())
	{
		// ...
	}

	if (cv_bot_stop.value != 0.0f)
		return;

	// check if we are stuck
	StuckCheck();

	// if our current 'noise' was heard a long time ago, forget it
	const float rememberNoiseDuration = 20.0f;
	if (m_noiseTimestamp > 0.0f && gpGlobals->time - m_noiseTimestamp > rememberNoiseDuration)
	{
		ForgetNoise();
	}

	// where are we
	if (!m_currentArea || !m_currentArea->Contains(&pev->origin))
	{
		m_currentArea = TheNavAreaGrid.GetNavArea(&pev->origin);
	}

	// track the last known area we were in
	if (m_currentArea != NULL && m_currentArea != m_lastKnownArea)
	{
		m_lastKnownArea = m_currentArea;
		// assume that we "clear" an area of enemies when we enter it
		m_currentArea->SetClearedTimestamp(m_iTeam - 1);
	}

	// update approach points
	const float recomputeApproachPointTolerance = 50.0f;
	if ((m_approachPointViewPosition - pev->origin).IsLengthGreaterThan(recomputeApproachPointTolerance))
	{
		ComputeApproachPoints();
		m_approachPointViewPosition = pev->origin;
	}

	if (cv_bot_show_nav.value > 0.0f && m_lastKnownArea != NULL)
	{
		m_lastKnownArea->DrawConnectedAreas();
	}

	// if we're blind, retreat!
	if (IsBlind())
	{
		if (!IsAtHidingSpot())
		{
			switch (m_blindMoveDir)
			{
				case FORWARD:	MoveForward(); break;
				case RIGHT:	StrafeRight(); break;
				case BACKWARD:	MoveBackward(); break;
				case LEFT:	StrafeLeft(); break;
				default:	Crouch(); break;
			}
		}
		if (m_blindFire)
		{
			PrimaryAttack();
		}

		return;
	}

	// Enemy acquisition and attack initiation
	// take a snapshot and update our reaction time queue
	UpdateReactionQueue();

	// "threat" may be the same as our current enemy
	CBasePlayer *threat = GetRecognizedEnemy();
	if (threat != NULL)
	{
		// adjust our personal "safe" time
		AdjustSafeTime();

		// Decide if we should attack
		bool doAttack = false;
		if (!IsUsingGrenade())
		{
			switch (GetDisposition())
			{
				case IGNORE_ENEMIES:
				{
					// never attack
					doAttack = false;
					break;
				}
				case SELF_DEFENSE:
				{
					// attack if fired on
					doAttack = IsPlayerLookingAtMe(threat);

					// attack if enemy very close
					if (!doAttack)
					{
						const float selfDefenseRange = 750.0f;
						doAttack = (pev->origin - threat->pev->origin).IsLengthLessThan(selfDefenseRange);
					}
					break;
				}
				case ENGAGE_AND_INVESTIGATE:
				case OPPORTUNITY_FIRE:
				{
					// normal combat range
					doAttack = true;
					break;
				}
			}
		}
		else
			ThrowGrenade(&pev->origin);

		// if we aren't attacking but we are being attacked, retaliate
		if (!doAttack && !IsAttacking() && GetDisposition() != IGNORE_ENEMIES)
		{
			const float recentAttackDuration = 1.0f;
			if (GetTimeSinceAttacked() < recentAttackDuration)
			{
				// we may not be attacking our attacker, but at least we're not just taking it
				// (since m_attacker isn't reaction-time delayed, we can't directly use it)
				doAttack = true;
				PrintIfWatched("Ouch! Retaliating!\n");
			}
		}

		if (doAttack)
		{
			if (GetEnemy() == NULL || !IsAttacking() || threat != GetEnemy())
			{
				if (IsUsingKnife() && IsHiding())
				{
					// if hiding with a knife, wait until threat is close
					const float knifeAttackRange = 250.0f;
					if ((pev->origin - threat->pev->origin).IsLengthLessThan(knifeAttackRange))
					{
						Attack(threat);
					}
				}
				else
				{
					Attack(threat);
				}
			}
		}
		else
		{
			// dont attack, but keep track of nearby enemies
			SetEnemy(threat);
			m_isEnemyVisible = true;
		}

		ctrl->SetLastSeenEnemyTimestamp();
	}

	// Validate existing enemy, if any
	if (m_enemy != NULL)
	{
		if (IsAwareOfEnemyDeath())
		{
			// we have noticed that our enemy has died
			m_enemy = NULL;
			m_isEnemyVisible = false;
		}
		else
		{
			// check LOS to current enemy (chest & head), in case he's dead (GetNearestEnemy() only returns live players)
			// note we're not checking FOV - once we've acquired an enemy (which does check FOV), assume we know roughly where he is
			if (IsVisible(m_enemy, false, &m_visibleEnemyParts))
			{
				m_isEnemyVisible = true;
				m_lastSawEnemyTimestamp = gpGlobals->time;
				m_lastEnemyPosition = m_enemy->pev->origin;
			}
			else
			{
				m_isEnemyVisible = false;
			}

			// check if enemy died
			if (m_enemy->IsAlive())
			{
				m_enemyDeathTimestamp = 0.0f;
				m_isLastEnemyDead = false;
			}
			else if (m_enemyDeathTimestamp == 0.0f)
			{
				// note time of death (to allow bots to overshoot for a time)
				m_enemyDeathTimestamp = gpGlobals->time;
				m_isLastEnemyDead = true;
			}
		}
	}
	else
	{
		m_isEnemyVisible = false;
	}

	// if we have seen an enemy recently, keep an eye on him if we can
	const float seenRecentTime = 3.0f;
	if (m_enemy != NULL && GetTimeSinceLastSawEnemy() < seenRecentTime)
	{
		AimAtEnemy();
	}
	else
	{
		StopAiming();
	}

	// Hack to fire while retreating
	// TODO: Encapsulate aiming and firing on enemies separately from current task
	if (GetDisposition() == IGNORE_ENEMIES)
	{
		FireWeaponAtEnemy();
	}

	if (IsEndOfSafeTime() && IsUsingGrenade() && (IsWellPastSafe() || !IsUsingHEGrenade()) && !m_isWaitingToTossGrenade)
	{
		Vector target;
		if (FindGrenadeTossPathTarget(&target))
		{
			ThrowGrenade(&target);
		}
	}

	if (IsUsingGrenade())
	{
		bool doToss = (m_isWaitingToTossGrenade && (m_tossGrenadeTimer.IsElapsed() || m_lookAtSpotState == LOOK_AT_SPOT));

		if (doToss)
		{
			ClearPrimaryAttack();
			m_isWaitingToTossGrenade = false;
		}
		else
		{
			PrimaryAttack();
		}
	}
	else
	{
		m_isWaitingToTossGrenade = false;
	}


	if (IsHunting() && IsWellPastSafe() && IsUsingGrenade())
	{
		EquipBestWeapon(MUST_EQUIP);
	}

	// check if our weapon is totally out of ammo
	// or if we no longer feel "safe", equip our weapon
	if (!IsSafe() && !IsUsingGrenade() && IsActiveWeaponOutOfAmmo())
	{
		EquipBestWeapon();
	}

	// TODO: This doesn't work if we are restricted to just knives and sniper rifles because we cant use the rifle at close range
	if (!IsSafe() && !IsUsingGrenade() && IsUsingKnife() && !IsEscapingFromBomb())
	{
		EquipBestWeapon();
	}

	// if we haven't seen an enemy in awhile, and we switched to our pistol during combat,
	// switch back to our primary weapon (if it still has ammo left)
	const float safeRearmTime = 5.0f;
	if (!IsActiveWeaponReloading() && IsUsingPistol() && !IsPrimaryWeaponEmpty() && GetTimeSinceLastSawEnemy() > safeRearmTime)
	{
		EquipBestWeapon();
	}

	// reload our weapon if we must
	ReloadCheck();

	// equip silencer
	SilencerCheck();

	// listen to the radio
	RespondToRadioCommands();

	// make way
	const float avoidTime = 0.33f;
	if (gpGlobals->time - m_avoidTimestamp < avoidTime && m_avoid != NULL)
	{
		StrafeAwayFromPosition(&m_avoid->pev->origin);
	}
	else
	{
		m_avoid = NULL;
	}

	if (m_isJumpCrouching)
	{
		const float duration = 0.75f;
		const float crouchDelayTime = 0.05f;
		const float standUpTime = 0.6f;
		float elapsed = gpGlobals->time - m_jumpCrouchTimestamp;

		if (elapsed > crouchDelayTime && elapsed < standUpTime)
			Crouch();

		if (elapsed >= standUpTime)
			StandUp();

		if (elapsed > duration)
			m_isJumpCrouching = false;
	}

	// if we're using a sniper rifle and are no longer attacking, stop looking thru scope
	if (!IsAtHidingSpot() && !IsAttacking() && IsUsingSniperRifle() && IsUsingScope())
	{
		SecondaryAttack();
	}

	// check encounter spots
	UpdatePeripheralVision();

	// Update gamestate
	if (m_bomber != NULL)
		GetChatter()->SpottedBomber(GetBomber());

	if (CanSeeLooseBomb())
		GetChatter()->SpottedLooseBomb(ctrl->GetLooseBomb());

	// Scenario interrupts
	switch (ctrl->GetScenario())
	{
		case CCSBotManager::SCENARIO_DEFUSE_BOMB:
		{
			// flee if the bomb is ready to blow and we aren't defusing it or attacking and we know where the bomb is
			// (aggressive players wait until its almost too late)
			float gonnaBlowTime = 8.0f - (2.0f * GetProfile()->GetAggression());

			// if we have a defuse kit, can wait longer
			if (m_bHasDefuser)
				gonnaBlowTime *= 0.66f;

			if (!IsEscapingFromBomb()					// we aren't already escaping the bomb
				&& ctrl->IsBombPlanted()				// is the bomb planted
				&& GetGameState()->IsPlantedBombLocationKnown()		// we know where the bomb is
				&& ctrl->GetBombTimeLeft() < gonnaBlowTime	// is the bomb about to explode
				&& !IsDefusingBomb()					// we aren't defusing the bomb
				&& !IsAttacking())					// we aren't in the midst of a firefight
			{
				EscapeFromBomb();
				break;
			}
			break;
		}
		case CCSBotManager::SCENARIO_RESCUE_HOSTAGES:
		{
			if (m_iTeam == CT)
			{
				UpdateHostageEscortCount();
			}
			else
			{
				// Terrorists have imperfect information on status of hostages
				CSGameState::ValidateStatusType status = GetGameState()->ValidateHostagePositions();

				if (status & CSGameState::HOSTAGES_ALL_GONE)
				{
					GetChatter()->HostagesTaken();
					Idle();
				}
				else if (status & CSGameState::HOSTAGE_GONE)
				{
					GetGameState()->HostageWasTaken();
					Idle();
				}
			}
			break;
		}
	}

	// Follow nearby humans if our co-op is high and we have nothing else to do
	// If we were just following someone, don't auto-follow again for a short while to
	// give us a chance to do something else.
	const float earliestAutoFollowTime = 5.0f;
	const float minAutoFollowTeamwork = 0.4f;
	if (ctrl->GetElapsedRoundTime() > earliestAutoFollowTime
		&& GetProfile()->GetTeamwork() > minAutoFollowTeamwork
		&& CanAutoFollow()
		&& !IsBusy()
		&& !IsFollowing()
		&& !GetGameState()->IsAtPlantedBombsite())
	{
		// chance of following is proportional to teamwork attribute
		if (GetProfile()->GetTeamwork() > RANDOM_FLOAT(0.0f, 1.0f))
		{
			CBasePlayer *leader = GetClosestVisibleHumanFriend();
			if (leader != NULL && leader->IsAutoFollowAllowed())
			{
				// count how many bots are already following this player
				const float maxFollowCount = 2;
				if (GetBotFollowCount(leader) < maxFollowCount)
				{
					const float autoFollowRange = 300.0f;
					if ((leader->pev->origin - pev->origin).IsLengthLessThan(autoFollowRange))
					{
						CNavArea *leaderArea = TheNavAreaGrid.GetNavArea(&leader->pev->origin);
						if (leaderArea != NULL)
						{
							PathCost cost(this, FASTEST_ROUTE);
							float travelRange = NavAreaTravelDistance(GetLastKnownArea(), leaderArea, cost);
							if (/*travelRange >= 0.0f &&*/ travelRange < autoFollowRange)
							{
								// follow this human
								Follow(leader);
								PrintIfWatched("Auto-Following %s\n", STRING(leader->pev->netname));

								if (g_pGameRules->IsCareer())
								{
									GetChatter()->Say("FollowingCommander", 10.0f);
								}
								else
								{
									GetChatter()->Say("FollowingSir", 10.0f);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			// we decided not to follow, don't re-check for a duration
			m_allowAutoFollowTime = gpGlobals->time + 15.0f + (1.0f - GetProfile()->GetTeamwork()) * 30.0f;
		}
	}

	if (IsFollowing())
	{
		// if we are following someone, make sure they are still alive
		CBaseEntity *leader = m_leader;
		if (leader == NULL || !leader->IsAlive())
		{
			StopFollowing();
		}

		// decide whether to continue following them
		const float highTeamwork = 0.85f;
		if (GetProfile()->GetTeamwork() < highTeamwork)
		{
			float minFollowDuration = 15.0f;
			if (GetFollowDuration() > minFollowDuration + 40.0f * GetProfile()->GetTeamwork())
			{
				// we are bored of following our leader
				StopFollowing();
				PrintIfWatched("Stopping following - bored\n");
			}
		}
	}
	else
	{
		if (GetMorale() < NEUTRAL && IsSafe() && GetSafeTimeRemaining() < 2.0f && IsHunting())
		{
			if (GetMorale() * -40.0 > RANDOM_FLOAT(0.0f, 100.0f))
			{
				if (ctrl->IsOnOffense(this) || !ctrl->IsDefenseRushing())
				{
					SetDisposition(OPPORTUNITY_FIRE);
					Hide(m_lastKnownArea, RANDOM_FLOAT(3.0f, 15.0f));
					GetChatter()->Say("WaitingHere");
				}
			}
		}
	}

	// Execute state machine
	if (m_isAttacking)
	{
		m_attackState.OnUpdate(this);
	}
	else
	{
		m_state->OnUpdate(this);
	}

	if (m_isWaitingToTossGrenade)
	{
		ResetStuckMonitor();
		ClearMovement();
	}

	// don't move while reloading unless we see an enemy
	if (IsReloading() && !m_isEnemyVisible)
	{
		ResetStuckMonitor();
		ClearMovement();
	}

	// if we get too far ahead of the hostages we are escorting, wait for them
	if (!IsAttacking() && m_inhibitWaitingForHostageTimer.IsElapsed())
	{
		const float waitForHostageRange = 500.0f;
		if (GetTask() == RESCUE_HOSTAGES && GetRangeToFarthestEscortedHostage() > waitForHostageRange)
		{
			if (!m_isWaitingForHostage)
			{
				// just started waiting
				m_isWaitingForHostage = true;
				m_waitForHostageTimer.Start(10.0f);
			}
			else
			{
				// we've been waiting
				if (m_waitForHostageTimer.IsElapsed())
				{
					// give up waiting for awhile
					m_isWaitingForHostage = false;
					m_inhibitWaitingForHostageTimer.Start(3.0f);
				}
				else
				{
					// keep waiting
					ResetStuckMonitor();
					ClearMovement();
				}
			}
		}
	}

	// remember our prior safe time status
	m_wasSafe = IsSafe();
}

#ifdef HOOK_GAMEDLL

void CCSBot::Upkeep(void)
{
	Upkeep_();
}

void CCSBot::Update(void)
{
	Update_();
}

#endif // HOOK_GAMEDLL
