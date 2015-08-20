#include "precompiled.h"

// Used to update view angles to stay on a ladder

/* <3d8352> ../cstrike/dlls/bot/cs_bot_vision.cpp:16 */
float StayOnLadderLine(CCSBot *me, const CNavLadder *ladder)
{
	// determine our facing
	NavDirType faceDir = AngleToDirection( me->pev->v_angle.y );
	const float stiffness = 1.0f;

	// move toward ladder mount point
	switch (faceDir)
	{
	case NORTH:
		return stiffness * (ladder->m_top.x - me->pev->origin.x);
	case EAST:
		return stiffness * (ladder->m_top.y - me->pev->origin.y);
	case SOUTH:
		return -stiffness * (ladder->m_top.x - me->pev->origin.x);
	case WEST:
		return -stiffness * (ladder->m_top.y - me->pev->origin.y);
	}

	return 0.0f;
}

void (*pCCSBot__UpdateLookAngles)(void);

/* <3d882c> ../cstrike/dlls/bot/cs_bot_vision.cpp:48 */
void __declspec(naked) CCSBot::UpdateLookAngles(void)
{
	__asm
	{
		jmp pCCSBot__UpdateLookAngles
	}

	//float stiffness;
	//float damping;

	//if (IsAttacking())
	//{
	//	damping = 30.0f;
	//	stiffness = 300.0f;
	//}
	//else
	//{
	//	damping = 25.0f;
	//	stiffness = 200.0f;
	//}

	//float useYaw = m_lookYaw;
	//float usePitch = m_lookPitch;

	//const float deltaT = (long double)g_flBotCommandInterval;
	//const float maxAccel = 3000.0f;
	//const float lookAlongLadderRange = 100.0f;
	//const float ladderPitch = 60.0f;

	//if (IsUsingLadder())
	//{
	//	NavDirType faceDir = m_pathLadder->m_dir;
	//	Vector to = m_pathLadder->m_top - pev->origin;
	//	float idealYaw = UTIL_VecToYaw( to );

	//	if (m_pathLadderFaceIn)
	//	{
	//		faceDir = OppositeDirection( faceDir );
	//	}

	//	switch (m_pathLadderState)
	//	{
	//		case APPROACH_ASCENDING_LADDER:
	//		{
	//			Vector to = m_goalPosition - pev->origin;
	//			if (to.IsLengthLessThan( lookAlongLadderRange ))
	//				usePitch = -ladderPitch;
	//			useYaw = idealYaw;
	//			break;
	//		}
	//		case APPROACH_DESCENDING_LADDER:
	//		{
	//			Vector to = m_goalPosition - pev->origin;
	//			if (to.IsLengthLessThan( lookAlongLadderRange ))
	//				usePitch = ladderPitch;
	//			useYaw = idealYaw;
	//			break;
	//		}
	//		case FACE_ASCENDING_LADDER:
	//		{
	//			useYaw = idealYaw;
	//			usePitch = -ladderPitch;
	//			break;
	//		}
	//		case FACE_DESCENDING_LADDER:
	//		{
	//			useYaw = idealYaw;
	//			usePitch = ladderPitch;
	//			break;
	//		}
	//		case MOUNT_ASCENDING_LADDER:
	//		case ASCEND_LADDER:
	//		{
	//			useYaw = DirectionToAngle( faceDir ) + StayOnLadderLine(this, m_pathLadder);
	//			usePitch = -ladderPitch;
	//			break;
	//		}
	//		case MOUNT_DESCENDING_LADDER:
	//		case DESCEND_LADDER:
	//		{
	//			useYaw = DirectionToAngle( faceDir ) + StayOnLadderLine(this, m_pathLadder);
	//			usePitch = ladderPitch;
	//			break;
	//		}
	//		case DISMOUNT_ASCENDING_LADDER:
	//		case DISMOUNT_DESCENDING_LADDER:
	//		{
	//			useYaw = DirectionToAngle( faceDir );
	//			break;
	//		}
	//	}
	//}

	//// if almost at target angle, snap to it
	//const float onTargetTolerance = 1.0f;
	//float angleDiff = NormalizeAngle( useYaw - pev->v_angle.y );

	//if (angleDiff < onTargetTolerance && angleDiff > -onTargetTolerance)
	//{
	//	m_lookYawVel = 0;
	//	pev->v_angle.y = useYaw;
	//}
	//else
	//{
	//	// simple angular spring/damper
	//	long double accel = (long double)(angleDiff * stiffness - m_lookYawVel * damping);
	//	//float_precision accel = (float_precision)(angleDiff * stiffness - m_lookYawVel * damping);

	//	// limit rate
	//	if (accel > maxAccel)
	//		accel = maxAccel;

	//	else if (accel < -maxAccel)
	//		accel = -maxAccel;

	//	m_lookYawVel = m_lookYawVel + (deltaT * accel);
	//	pev->v_angle.y += (deltaT * m_lookYawVel);
	//}

	//angleDiff = NormalizeAngle( usePitch - pev->v_angle.x );

	//// simple angular spring/damper
	//// double the stiffness since pitch is only +/- 90 and yaw is +/- 180
	//float accel = 2.0f * stiffness * angleDiff - damping * m_lookPitchVel;

	//if (accel > maxAccel)
	//	accel = maxAccel;

	//else if (accel < -maxAccel)
	//	accel = -maxAccel;

	//m_lookPitchVel += (deltaT * accel);
	//pev->v_angle.x += (deltaT * m_lookPitchVel);

	//// limit range - avoid gimbal lock
	//if (pev->v_angle.x < -89.0f)
	//	pev->v_angle.x = -89.0f;
	//else if (pev->v_angle.x > 89.0f)
	//	pev->v_angle.x = 89.0f;

	//pev->v_angle.z = 0.0f;
}

/* <3d8c91> ../cstrike/dlls/bot/cs_bot_vision.cpp:238 */
NOBODY bool CCSBot::__MAKE_VHOOK(IsVisible)(const Vector *pos, bool testFOV) const
{
//	{
//		const Vector *eye;                            //   248
//		class CCSBotManager *ctrl;                           //   251
//		TraceResult result;                                   //   256
//		GetEyePosition(const class CCSBot *const this);  //   248
//		GetEyePosition(const class CCSBot *const this);  //   252
//	}
}

/* <3d8d9b> ../cstrike/dlls/bot/cs_bot_vision.cpp:269 */
NOBODY bool CCSBot::__MAKE_VHOOK(IsVisible)(CBasePlayer *player, bool testFOV, unsigned char *visParts) const
{
//	{
//		float const topOfHead;                                 //   271
//		float const standFeet;                                 //   272
//		float const crouchFeet;                                //   273
//		unsigned char testVisParts;                           //   274
//		Vector spot;                                    //   283
//		class Vector2D dir;                                   //   297
//		class Vector2D perp;                                  //   299
//		float const edgeOffset;                                //   300
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   283
//		NormalizeInPlace(Vector2D *const this);  //   298
//	}
}

/* <3d8f9f> ../cstrike/dlls/bot/cs_bot_vision.cpp:302 */
bool CCSBot::__MAKE_VHOOK(IsEnemyPartVisible)(VisiblePartType part) const
{
	if (!IsEnemyVisible())
		return false;

	return (m_visibleEnemyParts & part) != 0;
}

/* <3d8f0d> ../cstrike/dlls/bot/cs_bot_vision.cpp:331 */
void CCSBot::UpdateLookAt(void)
{
	Vector to = m_lookAtSpot - EyePosition();
	Vector idealAngle = UTIL_VecToAngles( to );
	idealAngle.x = 360.0f - idealAngle.x;

	SetLookAngles(idealAngle.y, idealAngle.x);
}

/* <3d900c> ../cstrike/dlls/bot/cs_bot_vision.cpp:345 */
void CCSBot::SetLookAt(const char *desc, const Vector *pos, PriorityType pri, float duration, bool clearIfClose, float angleTolerance)
{
	if (pos == NULL)
		return;

	// if currently looking at a point in space with higher priority, ignore this request
	if (m_lookAtSpotState != NOT_LOOKING_AT_SPOT && m_lookAtSpotPriority > pri)
		return;

	// if already looking at this spot, just extend the time
	const float tolerance = 10.0f;
	if (m_lookAtSpotState != NOT_LOOKING_AT_SPOT && VectorsAreEqual( pos, &m_lookAtSpot, tolerance ))
	{
		m_lookAtSpotDuration = duration;

		if (m_lookAtSpotPriority < pri)
			m_lookAtSpotPriority = pri;
	}
	else
	{
		// look at new spot
		m_lookAtSpot = *pos; 
		m_lookAtSpotState = LOOK_TOWARDS_SPOT;
		m_lookAtSpotDuration = duration;
		m_lookAtSpotPriority = pri;
	}

	m_lookAtSpotAngleTolerance = angleTolerance;
	m_lookAtSpotClearIfClose = clearIfClose;
	m_lookAtDesc = desc;
}

/* <3d90a7> ../cstrike/dlls/bot/cs_bot_vision.cpp:383 */
NOBODY void CCSBot::InhibitLookAround(float duration)
{
}

/* <3d90d3> ../cstrike/dlls/bot/cs_bot_vision.cpp:392 */
NOBODY void CCSBot::UpdatePeripheralVision(void)
{
//	{
//		float const peripheralUpdateInterval;                  //   394
//		{
//			const class SpotOrder *spotOrder;           //   403
//			Vector pos;                             //   404
//			{
//				const_iterator iter;                  //   406
//				end(list<SpotOrder, std::allocator<SpotOrder>> *const this);  //   406
//				operator++(_List_const_iterator<SpotOrder> *const this);  //   406
//				{
//					const Vector *spotPos;//   410
//				}
//			}
//		}
//	}
}

/* <3d91af> ../cstrike/dlls/bot/cs_bot_vision.cpp:429 */
NOBODY void CCSBot::UpdateLookAround(bool updateNow)
{
//	{
//		float const noiseStartleRange;                         //   439
//		float const recentThreatTime;                          //   456
//		{
//			Vector spot;                            //   442
//			Vector(Vector *const this,
//				const Vector &v);  //   442
//			InhibitLookAround(CCSBot *const this,
//						float duration);  //   448
//		}
//		IsLookingAtSpot(const class CCSBot *const this,
//				enum PriorityType pri);  //   457
//		{
//			Vector spot;                            //   461
//			Vector(Vector *const this,
//				const Vector &v);  //   461
//			ClearLookAt(CCSBot *const this);  //   459
//		}
//		IsNotMoving(const class CCSBot *const this);  //   481
//		{
//			int which;                                    //   521
//			Vector spot;                            //   522
//			IsViewMoving(const class CCSBot *const this,
//					float angleVelThreshold);  //   489
//			{
//				float range;                          //   491
//			}
//			GetZoomLevel(const class CCSBot *const this);  //   497
//			ClearLookAt(CCSBot *const this);  //   517
//			Vector(Vector *const this,
//				const Vector &v);  //   522
//		}
//		IsLookingAtSpot(const class CCSBot *const this,
//				enum PriorityType pri);  //   541
//		{
//			float asleep;                                 //   550
//			Vector delta;                           //   558
//			float length;                                 //   559
//			float adx;                                    //   560
//			float ady;                                    //   561
//			float t;                                      //   562
//			float const leadCheckRange;                    //   570
//			class HidingSpot *dangerSpot;                //   580
//			int dangerSpotCount;                          //   581
//			int dangerIndex;                              //   582
//			float const checkTime;                         //   584
//			const class SpotOrder *spotOrder;           //   585
//			operator-(const Vector *const this,
//					const Vector &v);  //   558
//			Length(const Vector *const this);  //   559
//			{
//				iterator iter;                        //   586
//				end(list<SpotOrder, std::allocator<SpotOrder>> *const this);  //   586
//				operator++(_List_iterator<SpotOrder> *const this);  //   586
//			}
//			{
//				int which;                            //   607
//				const Vector *checkSpot;      //   608
//				Vector pos;                     //   610
//				operator+(const Vector *const this,
//						const Vector &v);  //   610
//			}
//		}
//	}
}

/* <3d9618> ../cstrike/dlls/bot/cs_bot_vision.cpp:628 */
NOBODY bool CCSBot::BendLineOfSight(Vector *eye, const Vector *point, Vector *bend)
{
//	{
//		TraceResult result;                                   //   631
//		Vector v;                                       //   641
//		float startAngle;                                     //   642
//		float length;                                         //   643
//		float const angleInc;                                  //   645
//		operator+(const Vector *const this,
//				const Vector &v);  //   632
//		Length2D(const Vector *const this);  //   643
//		operator-(const Vector *const this,
//				const Vector &v);  //   641
//		{
//			float angle;                                  //   646
//			{
//				int side;                             //   649
//				{
//					float actualAngle;            //   651
//					float dx;                     //   653
//					float dy;                     //   654
//					Vector rotPoint;        //   657
//					TraceResult result;           //   660
//					Vector ray;             //   667
//					float rayLength;              //   668
//					float visibleLength;          //   669
//					float const bendStepSize;      //   672
//					operator+(const Vector *const this,
//							const Vector &v);  //   661
//					operator-(const Vector *const this,
//							const Vector &v);  //   667
//					NormalizeInPlace(Vector *const this);  //   668
//					{
//						float bendLength;     //   673
//						{
//							Vector rayPoint;        //   676
//							Vector(Vector *const this,
//								float X,
//								float Y,
//								float Z);  //   676
//							operator+(const Vector *const this,
//									const Vector &v);  //   679
//						}
//					}
//				}
//			}
//		}
//	}
}

/* <3d99e8> ../cstrike/dlls/bot/cs_bot_vision.cpp:707 */
NOBODY CBasePlayer *CCSBot::FindMostDangerousThreat(void)
{
//	{
//		class CloseInfo threat;                               //   715
//		int threatCount;                                      //   716
//		float closeFriendRange;                               //   721
//		float closeHumanFriendRange;                          //   724
//		int i;                                                //   726
//		int prevEnemies;                                      //   835
//		int prevFriends;                                      //   836
//		class PlaceRank placeRank;                            //   869
//		int locCount;                                         //   870
//		class PlaceRank common;                               //   872
//		{
//			class CBaseEntity *entity;                   //   729
//			class CBasePlayer *player;                   //   744
//			int idx;                                      //   792
//			Vector d;                               //   801
//			float distSq;                                 //   802
//			FNullEnt(entvars_t *pev);  //   734
//			{
//				int j;                                //   814
//				{
//					int k;                        //   822
//				}
//			}
//			entindex(CBaseEntity *const this);  //   747
//			entindex(CBaseEntity *const this);  //   747
//			{
//				TraceResult result;                   //   758
//				GetEyePosition(const class CCSBot *const this);  //   759
//				{
//					int idx;                      //   763
//					Vector to;              //   768
//					float rangeSq;                //   769
//					entindex(CBaseEntity *const this);  //   763
//					operator-(const Vector *const this,
//							const Vector &v);  //   768
//					LengthSquared(const Vector *const this);  //   769
//				}
//			}
//			entindex(CBaseEntity *const this);  //   792
//			operator-(const Vector *const this,
//					const Vector &v);  //   801
//			LengthSquared(const Vector *const this);  //   802
//		}
//		{
//			float const recentTime;                        //   844
//		}
//		{
//			class CNavArea *area;                        //   879
//			unsigned int threatLoc;                       //   888
//			int j;                                        //   893
//		}
//		{
//			int t;                                        //   948
//			IsProtectedByShield(CBasePlayer *const this);  //   949
//		}
//	}
}

/* <3d9f7d> ../cstrike/dlls/bot/cs_bot_vision.cpp:960 */
NOBODY void CCSBot::UpdateReactionQueue(void)
{
//	{
//		class CBasePlayer *threat;                           //   967
//		int now;                                              //   969
//		float reactionTime;                                   //   994
//		float maxReactionTime;                                //   995
//		int reactionTimeSteps;                                //  1000
//		int i;                                                //  1002
//		IsReloading(CBasePlayer *const this);  //   975
//		IsProtectedByShield(CBasePlayer *const this);  //   976
//	}
}

/* <3da052> ../cstrike/dlls/bot/cs_bot_vision.cpp:1013 */
CBasePlayer *CCSBot::GetRecognizedEnemy(void)
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return NULL;

	return (CBasePlayer *)((CBaseEntity *)m_enemyQueue[ m_enemyQueueAttendIndex ].player);
}

/* <3da075> ../cstrike/dlls/bot/cs_bot_vision.cpp:1025 */
NOBODY bool CCSBot::IsRecognizedEnemyReloading(void)
{
}

/* <3da09d> ../cstrike/dlls/bot/cs_bot_vision.cpp:1037 */
NOBODY bool CCSBot::IsRecognizedEnemyProtectedByShield(void)
{
}

/* <3da0c5> ../cstrike/dlls/bot/cs_bot_vision.cpp:1049 */
NOBODY float CCSBot::GetRangeToNearestRecognizedEnemy(void)
{
//	{
//		const class CBasePlayer *enemy;                     //  1051
//		GetRecognizedEnemy(CCSBot *const this);  //  1051
//		operator-(const Vector *const this,
//				const Vector &v);  //  1054
//		Length(const Vector *const this);  //  1054
//	}
}

/* <3da170> ../cstrike/dlls/bot/cs_bot_vision.cpp:1063 */
NOBODY void CCSBot::__MAKE_VHOOK(Blind)(float duration, float holdTime, float fadeTime, int alpha)
{
//	Say(BotChatterInterface *const this,
//		const char *phraseName,
//		float lifetime,
//		float delay);  //  1091
}

#ifdef HOOK_GAMEDLL

void CCSBot::Blind(float duration, float holdTime, float fadeTime, int alpha)
{
	Blind_(duration, holdTime, fadeTime, alpha);
}

bool CCSBot::IsVisible(const Vector *pos, bool testFOV) const
{
	return IsVisible_(pos, testFOV);
}
bool CCSBot::IsVisible(CBasePlayer *player, bool testFOV, unsigned char *visParts) const
{
	return IsVisible_(player, testFOV, visParts);
}

bool CCSBot::IsEnemyPartVisible(VisiblePartType part) const
{
	return IsEnemyPartVisible_(part);
}

#endif // HOOK_GAMEDLL
