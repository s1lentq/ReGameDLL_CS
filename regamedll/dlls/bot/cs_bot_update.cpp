#include "precompiled.h"

/* <3c635f> ../cstrike/dlls/bot/cs_bot_update.cpp:26 */
void CCSBot::__MAKE_VHOOK(Upkeep)(void)
{
	CCSBotManager *ctrl = TheCSBots();

	if (ctrl->IsLearningMap() || !IsAlive())
		return;

	if (m_isRapidFiring)
		TogglePrimaryAttack();

	if (IsAimingAtEnemy())
	{
		UpdateAimOffset();

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

				if (IsUsingAWP() || IsUsingShotgun() || IsUsingMachinegun() || GetProfile()->GetSkill() < 0.8f
					|| (IsActiveWeaponRecoilHigh() && !IsUsingPistol() && !IsUsingSniperRifle()))
				{
					if (IsEnemyPartVisible(CHEST))
					{
						// No headshots in this game, go for the chest.
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
		const float sharpshooter = 0.5f;

		// have view "drift" very slowly, so view looks "alive"
		if (IsUsingSniperRifle() && IsUsingScope())
			driftAmplitude = sharpshooter;

		m_lookYaw += driftAmplitude * BotCOS(33.0f * gpGlobals->time);
		m_lookPitch += driftAmplitude * BotSIN(13.0f * gpGlobals->time);
	}

	// view angles can change quickly
	UpdateLookAngles();
}

void (*pCCSBot__Update)(void);

/* <3c6e1e> ../cstrike/dlls/bot/cs_bot_update.cpp:208 */
void __declspec(naked) CCSBot::__MAKE_VHOOK(Update)(void)
{
	__asm
	{
		jmp pCCSBot__Update
	}
//	{
//		class CCSBotManager *ctrl;                           //   210
//		float const rememberNoiseDuration;                     //   401
//		float const recomputeApproachPointTolerance;           //   419
//		class CBasePlayer *threat;                           //   459
//		float const seenRecentTime;                            //   572
//		float const safeRearmTime;                             //   676
//		float const avoidTime;                                 //   691
//		float const earliestAutoFollowTime;                    //   807
//		float const minAutoFollowTeamwork;                     //   808
//		{
//			Vector vecAiming;                       //   342
//			Vector vecSrc;                          //   344
//			operator+(const Vector *const this,
//					const Vector &v);  //   341
//			operator+(const Vector *const this,
//					const Vector &v);  //   349
//			operator*(float fl,
//					const Vector &v);  //   349
//			operator+(const Vector *const this,
//					const Vector &v);  //   351
//			operator*(float fl,
//					const Vector &v);  //   351
//			Vector(Vector *const this,
//				const Vector &v);  //   351
//			Vector(Vector *const this,
//				const Vector &v);  //   349
//		}
//		{
//			Vector dir;                             //   366
//			float length;                                 //   367
//			const class SpotOrder *order;               //   369
//			Vector along;                           //   370
//			Vector(Vector *const this,
//				const Vector &v);  //   364
//			Vector(Vector *const this,
//				const Vector &v);  //   364
//			operator-(const Vector *const this,
//					const Vector &v);  //   366
//			NormalizeInPlace(Vector *const this);  //   367
//			{
//				const_iterator iter;                  //   371
//				end(list<SpotOrder, std::allocator<SpotOrder>> *const this);  //   371
//				operator*(float fl,
//						const Vector &v);  //   375
//				operator+(const Vector *const this,
//						const Vector &v);  //   375
//				Vector(Vector *const this,
//					const Vector &v);  //   377
//				Vector(Vector *const this,
//					const Vector &v);  //   377
//				operator++(_List_const_iterator<SpotOrder> *const this);  //   371
//			}
//		}
//		{
//			Vector from;                            //   385
//			float const size;                              //   387
//			Vector arrow;                           //   389
//			GetEyePosition(const class CCSBot *const this);  //   385
//			operator+(const Vector *const this,
//					const Vector &v);  //   391
//			Vector(Vector *const this,
//				const Vector &v);  //   391
//		}
//		ForgetNoise(CCSBot *const this);  //   403
//		SetClearedTimestamp(CNavArea *const this,
//					int teamID);  //   415
//		operator-(const Vector *const this,
//				const Vector &v);  //   420
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //   420
//		AckAnalysisRequest(CCSBotManager *const this);  //   215
//		{
//			float const selfDefenseRange;                  //   465
//			{
//				float const knifeAttackRange;          //   490
//				operator-(const Vector *const this,
//						const Vector &v);  //   491
//				IsLengthLessThan(const Vector *const this,
//						float length);  //   491
//			}
//			GetEnemy(CCSBot *const this);  //   485
//			operator-(const Vector *const this,
//					const Vector &v);  //   483
//			IsLengthLessThan(const Vector *const this,
//					float length);  //   483
//			{
//				float const recentAttackDuration;      //   512
//				GetTimeSinceAttacked(const class CCSBot *const this);  //   513
//			}
//			SetLastSeenEnemyTimestamp(CCSBotManager *const this);  //   522
//		}
//		IsAwareOfEnemyDeath(const class CCSBot *const this);  //   530
//		GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   573
//		{
//			Vector target;                          //   591
//		}
//		{
//			bool doToss;                                  //   601
//			IsElapsed(const class CountdownTimer *const this);  //   605
//		}
//		IsActiveWeaponReloading(const class CBot *const this);  //   677
//		{
//			float const duration;                          //   704
//			float crouchDelayTime;                        //   705
//			float standUpTime;                            //   706
//			float elapsed;                                //   708
//		}
//		{
//			unsigned char status;                         //   784
//			HostageWasTaken(CSGameState *const this);  //   793
//		}
//		{
//			float gonnaBlowTime;                          //   755
//		}
//		GetElapsedRoundTime(const class CCSBotManager *const this);  //   809
//		{
//			class CBasePlayer *leader;                   //   820
//			GetClosestVisibleHumanFriend(const class CCSBot *const this);  //   820
//			IsAutoFollowAllowed(const class CBasePlayer *const this);  //   821
//			{
//				float const maxFollowCount;            //   824
//				{
//					float const autoFollowRange;   //   827
//					operator-(const Vector *const this,
//							const Vector &v);  //   828
//					IsLengthLessThan(const Vector *const this,
//							float length);  //   828
//					{
//						class CNavArea *leaderArea;      //   830
//						{
//							class PathCost pc;    //   833
//							float travelRange;    //   834
//							PathCost(PathCost *const this,
//								class CCSBot *bot,
//								enum RouteType route);  //   833
//							NavAreaTravelDistance<PathCost>(CNavArea *startArea,
//											class CNavArea *endArea,
//											class PathCost &costFunc);  //   834
//						}
//					}
//				}
//			}
//		}
//		{
//			class CBaseEntity *leader;                   //   865
//			float const highTeamwork;                      //   872
//			{
//				float minFollowDuration;              //   875
//				GetFollowDuration(const class CCSBot *const this);  //   876
//			}
//		}
//		{
//			float const campChance;                        //   890
//		}
//		IsReloading(CBasePlayer *const this);  //   920
//		IsElapsed(const class CountdownTimer *const this);  //   927
//		{
//			float const waitForHostageRange;               //   929
//			Start(CountdownTimer *const this,
//				float duration);  //   936
//			IsElapsed(const class CountdownTimer *const this);  //   941
//			Start(CountdownTimer *const this,
//				float duration);  //   945
//		}
//		GetLooseBomb(CCSBotManager *const this);  //   743
//		GetBomber(CCSBot *const this);  //   740
//		GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   678
//	}
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
