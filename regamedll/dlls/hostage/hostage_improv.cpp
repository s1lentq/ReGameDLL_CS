#include "precompiled.h"

/* <4703fc> ../cstrike/dlls/hostage/hostage_improv.cpp:19 */
NOBODY inline void DrawAxes(Vector &origin, int red, int green, int blue)
{
//	{
//		float size;                                           //    21
//	}
}

/* <47353e> ../cstrike/dlls/hostage/hostage_improv.cpp:41 */
CHostageImprov::CHostageImprov(CBaseEntity *entity)
{
//	HostageEscapeState(HostageEscapeState *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	HostageStateMachine(HostageStateMachine *const this);  //    41
//	HostageIdleState(HostageIdleState *const this);  //    41
//	HostageRetreatState(HostageRetreatState *const this);  //    41
//	HostageFollowState(HostageFollowState *const this);  //    41
//	HostageAnimateState(HostageAnimateState *const this);  //    41
//	CNavPath(CNavPath *const this);  //    41
//	IntervalTimer(IntervalTimer *const this);  //    41
//	IntervalTimer(IntervalTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	IntervalTimer(IntervalTimer *const this);  //    41
//	IntervalTimer(IntervalTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	IntervalTimer(IntervalTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
//	CountdownTimer(CountdownTimer *const this);  //    41
}

/* <470d33> ../cstrike/dlls/hostage/hostage_improv.cpp:52 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsAlive)(void) const
{
}

/* <474809> ../cstrike/dlls/hostage/hostage_improv.cpp:61 */
NOBODY void CHostageImprov::__MAKE_VHOOK(MoveTo)(const Vector &goal)
{
//	Invalidate(CNavPath *const this);  //    64
//	MoveTo(CHostageImprov *const this,
//		const Vector &goal);  //    61
}

/* <4717e4> ../cstrike/dlls/hostage/hostage_improv.cpp:78 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(GetSimpleGroundHeightWithFloor)(const Vector *pos, float *height, Vector *normal)
{
//	GetSimpleGroundHeightWithFloor(CHostageImprov *const this,
//					const Vector *pos,
//					float *height,
//					Vector *normal);  //    78
}

/* <473da4> ../cstrike/dlls/hostage/hostage_improv.cpp:96 */
NOBODY bool CHostageImprov::DiscontinuityJump(float ground, bool onlyJumpDown, bool mustJump)
{
//	{
//		float dz;                                             //   101
//	}
//	DiscontinuityJump(CHostageImprov *const this,
//				float ground,
//				bool onlyJumpDown,
//				bool mustJump);  //    96
}

/* <470d5b> ../cstrike/dlls/hostage/hostage_improv.cpp:116 */
NOBODY void CHostageImprov::__MAKE_VHOOK(LookAt)(const Vector &target)
{
}

/* <470d97> ../cstrike/dlls/hostage/hostage_improv.cpp:126 */
NOBODY void CHostageImprov::__MAKE_VHOOK(ClearLookAt)(void)
{
}

/* <470dbf> ../cstrike/dlls/hostage/hostage_improv.cpp:135 */
NOBODY void CHostageImprov::__MAKE_VHOOK(FaceTo)(const Vector &goal)
{
}

/* <470dfb> ../cstrike/dlls/hostage/hostage_improv.cpp:145 */
NOBODY void CHostageImprov::__MAKE_VHOOK(ClearFaceTo)(void)
{
}

/* <476a30> ../cstrike/dlls/hostage/hostage_improv.cpp:154 */
NOBODY void CHostageImprov::MoveTowards(const Vector &pos, float deltaT)
{
//	{
//		Vector move;                                    //   228
//		float accelRate;                                      //   236
//		float const crouchWalkRate;                            //   237
//		{
//			float ground;                                 //   180
//			Vector aheadRay;                        //   181
//			bool jumped;                                  //   186
//			NormalizeInPlace(Vector *const this);  //   182
//			{
//				float const farLookAheadRange;         //   189
//				Vector normal;                  //   190
//				Vector stepAhead;               //   191
//				operator*(float fl,
//						const Vector &v);  //   191
//				operator+(const Vector *const this,
//						const Vector &v);  //   191
//			}
//			{
//				float const lookAheadRange;            //   204
//				Vector stepAhead;               //   205
//				operator*(float fl,
//						const Vector &v);  //   205
//				operator+(const Vector *const this,
//						const Vector &v);  //   205
//			}
//			{
//				float const lookAheadRange;            //   216
//				Vector stepAhead;               //   217
//				operator*(float fl,
//						const Vector &v);  //   217
//				operator+(const Vector *const this,
//						const Vector &v);  //   217
//			}
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //   228
//		IsZero(Vector *const this,
//			float tolerance);  //   231
//		NormalizeInPlace(Vector *const this);  //   232
//	}
}

/* <473e46> ../cstrike/dlls/hostage/hostage_improv.cpp:262 */
NOBODY bool CHostageImprov::FaceTowards(const Vector &target, float deltaT)
{
//	{
//		class Vector2D to;                                    //   264
//		float moveAngle;                                      //   267
//		class Vector2D dir;                                   //   270
//		class Vector2D lat;                                   //   271
//		float const maxTurnRate;                               //   273
//		float error;                                          //   275
//		float dot;                                            //   278
//		operator-(const Vector *const this,
//				const Vector &v);  //   264
//		NormalizeInPlace(Vector2D *const this);  //   265
//		DotProduct(const class Vector2D &a,
//				const class Vector2D &b);  //   275
//		DotProduct(const class Vector2D &a,
//				const class Vector2D &b);  //   278
//		{
//			float const tolerance;                         //   285
//			fabs(double __x);  //   286
//		}
//		SetMoveAngle(CHostageImprov *const this,
//				float angle);  //   298
//	}
}

/* <47402b> ../cstrike/dlls/hostage/hostage_improv.cpp:308 */
NOBODY void CHostageImprov::FaceOutwards(void)
{
//	{
//		TraceResult result;                                   //   310
//		Vector to;                                      //   312
//		float farthestRange;                                  //   313
//		int farthest;                                         //   314
//		int const cornerCount;                                 //   316
//		Vector corner;                                  //   317
//		{
//			int i;                                        //   325
//			{
//				float range;                          //   328
//				operator+(const Vector *const this,
//						const Vector &v);  //   327
//				operator-(const Vector *const this,
//						const Vector &v);  //   328
//				LengthSquared(const Vector *const this);  //   328
//			}
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   337
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   323
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   323
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   323
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //   323
//	}
}

/* <470e23> ../cstrike/dlls/hostage/hostage_improv.cpp:344 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsAtMoveGoal)(float error) const
{
//	operator-(const Vector *const this,
//			const Vector &v);  //   346
//	IsLengthLessThan(const Vector *const this,
//			float length);  //   346
}

/* <470eab> ../cstrike/dlls/hostage/hostage_improv.cpp:353 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsAtFaceGoal)(void) const
{
}

/* <46fb4b> ../cstrike/dlls/hostage/hostage_improv.cpp:395 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsFriendInTheWay)(const Vector &goalPos) const
{
//	{
//		float const avoidFriendInterval;                       //   403
//		IsElapsed(const class CountdownTimer *const this);  //   398
//		{
//			class CheckWayFunctor check;                  //   411
//		}
//		{
//			int i;                                        //   421
//			{
//				class CBasePlayer *player;           //   423
//			}
//		}
//	}
//	IsFriendInTheWay(const class CHostageImprov *const this,
//			const Vector &goalPos);  //   395
}

/* <472b83> ../cstrike/dlls/hostage/hostage_improv.cpp:453 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsFriendInTheWay)(CBaseEntity *myFriend, const Vector &goalPos) const
{
//	{
//		Vector moveDir;                                 //   460
//		float length;                                         //   463
//		Vector friendFeet;                              //   465
//		Vector toFriend;                                //   476
//		float const personalSpace;                             //   479
//		float friendDistAlong;                                //   484
//		Vector pos;                                     //   491
//		float const friendRadius;                              //   498
//		operator-(const Vector *const this,
//				const Vector &v);  //   460
//		NormalizeInPlace(Vector *const this);  //   463
//		operator-(const Vector *const this,
//				const Vector &v);  //   476
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //   480
//		DotProduct(Vector &a,
//				const Vector &b);  //   484
//		operator-(const Vector *const this,
//				const Vector &v);  //   499
//		IsLengthLessThan(const Vector *const this,
//				float length);  //   499
//		IsZero(Vector *const this,
//			float tolerance);  //   504
//		DotProduct(Vector &a,
//				const Vector &b);  //   507
//		operator*(float fl,
//				const Vector &v);  //   495
//		operator+(const Vector *const this,
//				const Vector &v);  //   495
//	}
}

/* <474309> ../cstrike/dlls/hostage/hostage_improv.cpp:557 */
NOBODY bool CHostageImprov::IsFriendInTheWay(void)
{
//	{
//		class CheckAhead check;                               //   559
//		CheckAhead(CheckAhead *const this,
//				const class CHostageImprov *me);  //   559
//		ForEachHostage<CheckAhead>(const class CHostageManager *const this,
//						class CheckAhead &func);  //   561
//		ForEachPlayer<CheckAhead>(CheckAhead &func);  //   562
//	}
}

/* <474631> ../cstrike/dlls/hostage/hostage_improv.cpp:568 */
NOBODY float CHostageImprov::GetSpeed(void)
{
}

/* <46f249> ../cstrike/dlls/hostage/hostage_improv.cpp:592 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(Jump)(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //   604
//	{
//		float const epsilon;                                   //   609
//		float const minJumpInterval;                           //   618
//		{
//			float const fudge;                             //   613
//		}
//	}
//	Jump(CHostageImprov *const this);  //   592
}

/* <470ed3> ../cstrike/dlls/hostage/hostage_improv.cpp:632 */
NOBODY void CHostageImprov::__MAKE_VHOOK(Run)(void)
{
}

/* <470efb> ../cstrike/dlls/hostage/hostage_improv.cpp:638 */
NOBODY void CHostageImprov::__MAKE_VHOOK(Walk)(void)
{
}

/* <470f23> ../cstrike/dlls/hostage/hostage_improv.cpp:644 */
NOBODY void CHostageImprov::__MAKE_VHOOK(Stop)(void)
{
}

/* <470f4c> ../cstrike/dlls/hostage/hostage_improv.cpp:655 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetFeet)(void) const
{
	return m_hostage->pev->origin;
}

/* <470f74> ../cstrike/dlls/hostage/hostage_improv.cpp:661 */
NOBODY const Vector &CHostageImprov::__MAKE_VHOOK(GetCentroid)(void)
{
	m_centroid = m_hostage->pev->origin + Vector(0, 0, 36);
	return m_centroid;
}

/* <470f9c> ../cstrike/dlls/hostage/hostage_improv.cpp:671 */
NOBODY const Vector &CHostageImprov::__MAKE_VHOOK(GetEyes)(void) const
{
}

/* <470fc4> ../cstrike/dlls/hostage/hostage_improv.cpp:681 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsOnGround)(void) const
{
}

/* <470fec> ../cstrike/dlls/hostage/hostage_improv.cpp:687 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsMoving)(void) const
{
//	{
//		float const epsilon;                                   //   689
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //   690
//	}
}

/* <4715d1> ../cstrike/dlls/hostage/hostage_improv.cpp:697 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsVisible)(const Vector &pos, bool testFOV) const
{
//	{
//		class Vectorconst eye;                                //   707
//		TraceResult result;                                   //   715
//		Vector(Vector *const this,
//			const Vector &v);  //   707
//	}
}

/* <472938> ../cstrike/dlls/hostage/hostage_improv.cpp:728 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(IsPlayerLookingAtMe)(CBasePlayer *other, float cosTolerance) const
{
//	{
//		class Vector2D toOther;                               //   730
//		class Vector2D otherDir;                              //   737
//		NormalizeInPlace(Vector2D *const this);  //   733
//		operator+(const Vector *const this,
//				const Vector &v);  //   736
//		NormalizeInPlace(Vector2D *const this);  //   740
//	}
}

/* <472a9f> ../cstrike/dlls/hostage/hostage_improv.cpp:757 */
NOBODY CBasePlayer *CHostageImprov::__MAKE_VHOOK(IsAnyPlayerLookingAtMe)(int team, float cosTolerance) const
{
//	{
//		int i;                                                //   759
//		{
//			class CBasePlayer *player;                   //   761
//			IsEntityValid(CBaseEntity *entity);  //   763
//		}
//	}
}

/* <472e7b> ../cstrike/dlls/hostage/hostage_improv.cpp:783 */
NOBODY CBasePlayer *CHostageImprov::__MAKE_VHOOK(GetClosestPlayerByTravelDistance)(int team, float *range) const
{
//	{
//		class CBasePlayer *close;                            //   788
//		float closeRange;                                     //   789
//		{
//			int i;                                        //   791
//			{
//				class CBasePlayer *player;           //   793
//				class ShortestPathCost cost;          //   804
//				Vector vecCenter;               //   805
//				float range;                          //   806
//				IsEntityValid(CBaseEntity *entity);  //   795
//				NavAreaTravelDistance<ShortestPathCost>(const Vector *startPos,
//									class CNavArea *startArea,
//									const Vector *goalPos,
//									class ShortestPathCost &costFunc);  //   806
//			}
//		}
//	}
}

/* <47166d> ../cstrike/dlls/hostage/hostage_improv.cpp:822 */
void CHostageImprov::__MAKE_VHOOK(OnReset)(void)
{
	m_moveFlags = 0;
	m_moveType = Stopped;
	m_moveLimit = Running;
	
	m_vel.x = 0;
	m_vel.y = 0;

	m_actualVel = Vector(0, 0, 0);
	m_checkNearbyTerroristTimer.Invalidate();

	m_lastKnownArea = NULL;
	m_hasKnownGoodPos = false;
	m_hasPriorKnownGoodPos = false;
	m_isTerroristNearby = false;
	m_isCrouching = false;

	SetMoveAngle(m_hostage->pev->angles.y);

	m_moveGoal = m_hostage->m_vStart;

	ClearLookAt();
	ClearFaceTo();

	m_blinkTimer.Invalidate();
	m_blinkCounter = 0;

	m_hostage->SetBoneController(2, 0);
	m_hostage->SetBoneController(3, 0);
	m_hostage->SetBoneController(4, 0);

	m_path.Invalidate();
	m_chatterTimer.Invalidate();

	m_visiblePlayerCount = 0;
	m_isDelayedChatterPending = 0;

	m_animateState.Reset();
	m_didFidget = 0;

	m_lastSawCT.Start();
	m_lastSawT.Start();

	m_scaredTimer.Invalidate();
	m_jumpTimer.Invalidate();
	m_hasJumped = false;

	m_isFriendInTheWay = false;
	m_aggression = RANDOM_FLOAT(0, 1);

	StandUp();
	m_behavior.Reset(this);
	Idle();
}

/* <474659> ../cstrike/dlls/hostage/hostage_improv.cpp:886 */
NOBODY void CHostageImprov::UpdateVision(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //   888
//	{
//		int i;                                                //   893
//		{
//			class CBasePlayer *player;                   //   895
//			FNullEnt(entvars_t *pev);  //   900
//			Start(IntervalTimer *const this);  //   914
//			Start(IntervalTimer *const this);  //   916
//		}
//	}
//	Start(CountdownTimer *const this,
//		float duration);  //   924
}

/* <476e49> ../cstrike/dlls/hostage/hostage_improv.cpp:997 */
NOBODY void CHostageImprov::__MAKE_VHOOK(TrackPath)(const Vector &pathGoal, float deltaT)
{
//	TrackPath(CHostageImprov *const this,
//			const Vector &pathGoal,
//			float deltaT);  //   997
}

/* <474781> ../cstrike/dlls/hostage/hostage_improv.cpp:1014 */
NOBODY void CHostageImprov::SetKnownGoodPosition(const Vector &pos)
{
//	SetKnownGoodPosition(CHostageImprov *const this,
//				const Vector &pos);  //  1014
}

/* <47486d> ../cstrike/dlls/hostage/hostage_improv.cpp:1038 */
NOBODY void CHostageImprov::ResetToKnownGoodPosition(void)
{
//	{
//		float const tolerance;                                 //  1044
//		operator-(const Vector *const this,
//				const Vector &v);  //  1045
//		IsLengthLessThan(const Vector *const this,
//				float length);  //  1045
//		Start(CountdownTimer *const this,
//			float duration);  //  1055
//	}
//	Invalidate(CNavPath *const this);  //  1073
}

/* <47105c> ../cstrike/dlls/hostage/hostage_improv.cpp:1082 */
NOBODY void CHostageImprov::__MAKE_VHOOK(StartLadder)(const class CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos)
{
}

/* <4710c4> ../cstrike/dlls/hostage/hostage_improv.cpp:1094 */
NOBODY bool CHostageImprov::__MAKE_VHOOK(TraverseLadder)(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT)
{
//	{
//		Vector goal;                                    //  1098
//		AddDirectionVector(Vector *v,
//					enum NavDirType dir,
//					float amount);  //  1122
//		{
//			float const atGoalRange;                       //  1198
//			{
//				float closeRange;                     //  1158
//				float range;                          //  1158
//				operator-(const Vector *const this,
//						const Vector &v);  //  1162
//				LengthSquared(const Vector *const this);  //  1162
//				operator-(const Vector *const this,
//						const Vector &v);  //  1174
//				LengthSquared(const Vector *const this);  //  1174
//				operator-(const Vector *const this,
//						const Vector &v);  //  1186
//				LengthSquared(const Vector *const this);  //  1186
//			}
//			operator-(const Vector *const this,
//					const Vector &v);  //  1199
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1199
//		}
//		{
//			float const walkRange;                         //  1130
//			float const ladderRange;                       //  1135
//			operator-(const Vector *const this,
//					const Vector &v);  //  1131
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1131
//			operator-(const Vector *const this,
//					const Vector &v);  //  1136
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1136
//		}
//		AddDirectionVector(Vector *v,
//					enum NavDirType dir,
//					float amount);  //  1103
//		{
//			float const ladderRange;                       //  1108
//			operator-(const Vector *const this,
//					const Vector &v);  //  1109
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1109
//		}
//	}
}

/* <477691> ../cstrike/dlls/hostage/hostage_improv.cpp:1214 */
NOBODY void CHostageImprov::UpdatePosition(float deltaT)
{
//	{
//		class CNavArea *area;                                //  1217
//		float const friction;                                  //  1344
//		float speed;                                          //  1349
//		float const maxSpeed;                                  //  1351
//		class KeepPersonalSpace spacer;                       //  1365
//		{
//			float const pushSpeed;                         //  1258
//			Vector dir;                             //  1260
//			operator-(const Vector *const this,
//					const Vector &v);  //  1260
//			NormalizeInPlace(Vector *const this);  //  1262
//			ResetJump(CHostageImprov *const this);  //  1247
//		}
//		{
//			Vector angles;                          //  1282
//			float yaw;                                    //  1284
//			float pitch;                                  //  1288
//			operator-(const Vector *const this,
//					const Vector &v);  //  1282
//		}
//		{
//			class HostagePathCost pathCost;               //  1322
//			Compute<HostagePathCost>(CNavPath *const this,
//						const Vector *start,
//						const Vector *goal,
//						class HostagePathCost &costFunc);  //  1323
//			SetPath(CNavPathFollower *const this,
//				class CNavPath *path);  //  1326
//			SetImprov(CNavPathFollower *const this,
//					class CImprov *improv);  //  1325
//			Debug(CNavPathFollower *const this,
//				bool status);  //  1328
//		}
//		IsElapsed(const class CountdownTimer *const this);  //  1333
//		ResetStuck(CNavPathFollower *const this);  //  1336
//		NormalizeInPlace(Vector2D *const this);  //  1349
//		operator*(float fl,
//				const class Vector2D &v);  //  1355
//		KeepPersonalSpace(KeepPersonalSpace *const this,
//					class CHostageImprov *improv);  //  1365
//		ForEachPlayer<KeepPersonalSpace>(KeepPersonalSpace &func);  //  1366
//		DrawAxes(Vector &origin,
//			int red,
//			int green,
//			int blue);  //  1223
//		ForEachHostage<KeepPersonalSpace>(const class CHostageManager *const this,
//							class KeepPersonalSpace &func);  //  1369
//	}
}

/* <47837a> ../cstrike/dlls/hostage/hostage_improv.cpp:1384 */
NOBODY void CHostageImprov::__MAKE_VHOOK(OnUpkeep)(float deltaT)
{
}

/* <4749f9> ../cstrike/dlls/hostage/hostage_improv.cpp:1396 */
NOBODY bool CHostageImprov::IsTerroristNearby(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //  1399
//	CheckForNearbyTerrorists(CHostageImprov *const this);  //  1403
}

/* <474ae7> ../cstrike/dlls/hostage/hostage_improv.cpp:1412 */
NOBODY void CHostageImprov::CheckForNearbyTerrorists(void)
{
//	{
//		float const checkInterval;                             //  1418
//		float range;                                          //  1423
//		IsElapsed(const class CountdownTimer *const this);  //  1414
//		Start(CountdownTimer *const this,
//			float duration);  //  1419
//		{
//			float const nearbyTerroristRange;              //  1427
//			Start(CountdownTimer *const this,
//				float duration);  //  1431
//		}
//	}
}

/* <4753ba> ../cstrike/dlls/hostage/hostage_improv.cpp:1440 */
NOBODY void CHostageImprov::UpdateGrenadeReactions(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //  1442
//	{
//		class CBaseEntity *entity;                           //  1458
//		float const watchGrenadeRadius;                        //  1459
//		Start(CountdownTimer *const this,
//			float duration);  //  1456
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  1464
//		{
//			class CGrenade *grenade;                     //  1466
//			OnInjury(HostageIdleState *const this,
//				float amount);  //  1480
//			Start(CountdownTimer *const this,
//				float duration);  //  1489
//		}
//	}
//	Start(CountdownTimer *const this,
//		float duration);  //  1447
}

/* <475ce3> ../cstrike/dlls/hostage/hostage_improv.cpp:1502 */
NOBODY void CHostageImprov::__MAKE_VHOOK(OnUpdate)(float deltaT)
{
//	{
//		float const runSpeed;                                  //  1553
//		float const walkSpeed;                                 //  1554
//		float const fallVelocity;                              //  1560
//		float const safeTime;                                  //  1687
//		{
//			float dot;                                    //  1621
//			{
//				float speed;                          //  1632
//			}
//		}
//	}
//	OnUpdate(CHostageImprov *const this,
//		float deltaT);  //  1502
}

/* <47552a> ../cstrike/dlls/hostage/hostage_improv.cpp:1705 */
NOBODY void CHostageImprov::__MAKE_VHOOK(OnGameEvent)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	DelayedChatter(CHostageImprov *const this,
//			float delayTime,
//			enum HostageChatterType sayType,
//			bool mustSpeak);  //  1780
//	{
//		Vector *impactPos;                             //  1713
//		float const nearRange;                                 //  1715
//		operator-(const Vector *const this,
//				const Vector &v);  //  1716
//		IsLengthLessThan(const Vector *const this,
//				float length);  //  1716
//	}
//	DelayedChatter(CHostageImprov *const this,
//			float delayTime,
//			enum HostageChatterType sayType,
//			bool mustSpeak);  //  1736
//	OnInjury(HostageIdleState *const this,
//		float amount);  //  1742
//	Invalidate(CountdownTimer *const this);  //  1764
//	DelayedChatter(CHostageImprov *const this,
//			float delayTime,
//			enum HostageChatterType sayType,
//			bool mustSpeak);  //  1769
//	{
//		float range;                                          //  1788
//		enum PriorityType priority;                           //  1789
//		bool isHostile;                                       //  1790
//		{
//			float const fudge;                             //  1793
//			operator-(const Vector *const this,
//					const Vector &v);  //  1795
//			IsLengthLessThan(const Vector *const this,
//					float length);  //  1795
//			Start(IntervalTimer *const this);  //  1798
//			DelayedChatter(CHostageImprov *const this,
//					float delayTime,
//					enum HostageChatterType sayType,
//					bool mustSpeak);  //  1810
//			DelayedChatter(CHostageImprov *const this,
//					float delayTime,
//					enum HostageChatterType sayType,
//					bool mustSpeak);  //  1822
//		}
//	}
//	{
//		Vector *impactPos;                             //  1835
//		float const flashRange;                                //  1837
//		operator-(const Vector *const this,
//				const Vector &v);  //  1838
//		IsLengthLessThan(const Vector *const this,
//				float length);  //  1838
//		DelayedChatter(CHostageImprov *const this,
//				float delayTime,
//				enum HostageChatterType sayType,
//				bool mustSpeak);  //  1843
//	}
}

/* <471e27> ../cstrike/dlls/hostage/hostage_improv.cpp:1854 */
NOBODY void CHostageImprov::__MAKE_VHOOK(OnTouch)(CBaseEntity *other)
{
//	{
//		const char *classname;                              //  1856
//		class Vector2D to;                                    //  1994
//		float const pushForce;                                 //  1997
//		Start(IntervalTimer *const this);  //  1862
//		FStrEq(const char *sz1,
//			const char *sz2);  //  1864
//		{
//			float const lookAheadRange;                    //  1866
//			float ground;                                 //  1870
//			Vector normal;                          //  1871
//			Vector alongFloor;                      //  1881
//			TraceResult result;                           //  1885
//			bool isStep;                                  //  1886
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //  1871
//			{
//				float offset;                         //  1887
//				{
//					Vector pos;             //  1889
//					Vector(Vector *const this,
//						const Vector &v);  //  1889
//					operator*(float fl,
//							const Vector &v);  //  1892
//					operator+(const Vector *const this,
//							const Vector &v);  //  1892
//				}
//			}
//			CrossProduct(Vector &a,
//					const Vector &b);  //  1881
//			{
//				bool isSeam;                          //  1942
//				float const checkSeamRange;            //  1943
//				Vector posBehind;               //  1946
//				operator*(float fl,
//						const Vector &v);  //  1946
//				operator-(const Vector *const this,
//						const Vector &v);  //  1946
//				operator+(const Vector *const this,
//						const Vector &v);  //  1947
//				DotProduct(Vector &a,
//						const Vector &b);  //  1949
//				{
//					Vector posAhead;        //  1956
//					operator+(const Vector *const this,
//							const Vector &v);  //  1956
//					operator+(const Vector *const this,
//							const Vector &v);  //  1957
//					DotProduct(Vector &a,
//							const Vector &b);  //  1959
//				}
//				{
//					float const nudge;             //  1971
//				}
//			}
//			operator*(float fl,
//					const Vector &v);  //  1878
//			Vector(Vector *const this,
//				const Vector &v);  //  1878
//			operator+(const Vector *const this,
//					const Vector &v);  //  1878
//			{
//				float stepAheadGround;                //  1909
//				Vector stepAheadNormal;         //  1910
//				Start(CountdownTimer *const this,
//					float duration);  //  1907
//				{
//					float range;                  //  1912
//					{
//						Vector stepAhead; //  1914
//						{
//							float dz;     //  1927
//						}
//						operator+(const Vector *const this,
//								const Vector &v);  //  1914
//						operator*(float fl,
//								const Vector &v);  //  1914
//					}
//				}
//			}
//		}
//		FStrEq(const char *sz1,
//			const char *sz2);  //  1983
//		operator-(const Vector *const this,
//				const Vector &v);  //  1994
//		NormalizeInPlace(Vector2D *const this);  //  1995
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  1990
//	}
}

/* <474ba8> ../cstrike/dlls/hostage/hostage_improv.cpp:2006 */
NOBODY void CHostageImprov::ApplyForce(Vector force)
{
}

/* <474bd5> ../cstrike/dlls/hostage/hostage_improv.cpp:2016 */
NOBODY bool CHostageImprov::IsAtHome(void)
{
//	IsAtHome(const class CHostage *const this);  //  2018
}

/* <474c76> ../cstrike/dlls/hostage/hostage_improv.cpp:2025 */
NOBODY bool CHostageImprov::CanSeeRescueZone(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  2027
//		const class Zone *zone;                             //  2031
//	}
}

/* <474cd3> ../cstrike/dlls/hostage/hostage_improv.cpp:2047 */
NOBODY CBasePlayer *CHostageImprov::GetClosestVisiblePlayer(int team)
{
//	{
//		class CBasePlayer *close;                            //  2049
//		float closeRangeSq;                                   //  2050
//		{
//			int i;                                        //  2052
//			{
//				class CBasePlayer *player;           //  2054
//				float rangeSq;                        //  2064
//				operator-(const Vector *const this,
//						const Vector &v);  //  2064
//				LengthSquared(const Vector *const this);  //  2064
//			}
//		}
//	}
}

/* <474db2> ../cstrike/dlls/hostage/hostage_improv.cpp:2080 */
NOBODY float CHostageImprov::GetTimeSinceLastSawPlayer(int team)
{
//	{
//		float timeCT;                                         //  2088
//		float timeT;                                          //  2089
//		GetElapsedTime(const class IntervalTimer *const this);  //  2086
//		GetElapsedTime(const class IntervalTimer *const this);  //  2088
//		GetElapsedTime(const class IntervalTimer *const this);  //  2089
//		GetElapsedTime(const class IntervalTimer *const this);  //  2083
//	}
}

/* <474f2c> ../cstrike/dlls/hostage/hostage_improv.cpp:2098 */
NOBODY float CHostageImprov::GetTimeSinceLastInjury(void)
{
//	GetElapsedTime(const class IntervalTimer *const this);  //  2100
}

/* <474fb3> ../cstrike/dlls/hostage/hostage_improv.cpp:2107 */
NOBODY float CHostageImprov::GetTimeSinceLastNoise(void)
{
//	GetElapsedTime(const class IntervalTimer *const this);  //  2109
}

/* <47503a> ../cstrike/dlls/hostage/hostage_improv.cpp:2117 */
NOBODY bool CHostageImprov::IsScared(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //  2119
}

/* <47506e> ../cstrike/dlls/hostage/hostage_improv.cpp:2129 */
NOBODY void CHostageImprov::Frighten(ScareType scare)
{
//	IsScared(const class CHostageImprov *const this);  //  2132
//	Invalidate(CountdownTimer *const this);  //  2137
//	Start(CountdownTimer *const this,
//		float duration);  //  2145
//	{
//		float const ignoreTime;                                //  2152
//		Start(CountdownTimer *const this,
//			float duration);  //  2149
//		Start(CountdownTimer *const this,
//			float duration);  //  2153
//	}
}

/* <475200> ../cstrike/dlls/hostage/hostage_improv.cpp:2165 */
NOBODY void CHostageImprov::Afraid(void)
{
//	{
//		int which;                                            //  2185
//		char animInto;                                        //  2186
//		char animLoop;                                        //  2186
//		char animExit;                                        //  2186
//		SetPerformance(HostageAnimateState *const this,
//				enum PerformanceType performance);  //  2182
//	}
}

/* <475290> ../cstrike/dlls/hostage/hostage_improv.cpp:2201 */
NOBODY void CHostageImprov::UpdateIdleActivity(Activity activity, Activity fidget)
{
}

/* <4752d9> ../cstrike/dlls/hostage/hostage_improv.cpp:2226 */
NOBODY void CHostageImprov::Chatter(HostageChatterType sayType, bool mustSpeak)
{
//	{
//		float duration;                                       //  2239
//	}
//	IsElapsed(const class CountdownTimer *const this);  //  2235
//	Chatter(CHostageImprov *const this,
//		enum HostageChatterType sayType,
//		bool mustSpeak);  //  2226
}

/* <475b35> ../cstrike/dlls/hostage/hostage_improv.cpp:2249 */
NOBODY void CHostageImprov::DelayedChatter(float delayTime, HostageChatterType sayType, bool mustSpeak)
{
//	DelayedChatter(CHostageImprov *const this,
//			float delayTime,
//			enum HostageChatterType sayType,
//			bool mustSpeak);  //  2249
}

/* <475bd4> ../cstrike/dlls/hostage/hostage_improv.cpp:2268 */
NOBODY void CHostageImprov::UpdateDelayedChatter(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //  2270
//	Chatter(CHostageImprov *const this,
//		enum HostageChatterType sayType,
//		bool mustSpeak);  //  2299
}

/* <4761eb> ../cstrike/dlls/hostage/hostage_improv.cpp:2307 */
NOBODY void CHostageImprov::Flinch(Activity activity)
{
//	Chatter(CHostageImprov *const this,
//		enum HostageChatterType sayType,
//		bool mustSpeak);  //  2310
//	SetPerformance(HostageAnimateState *const this,
//			enum PerformanceType performance);  //  2321
}

/* <4762fe> ../cstrike/dlls/hostage/hostage_improv.cpp:2329 */
NOBODY void CHostageImprov::CrouchDie(void)
{
}

/* <476327> ../cstrike/dlls/hostage/hostage_improv.cpp:2339 */
NOBODY void CHostageImprov::Agree(void)
{
}

/* <476350> ../cstrike/dlls/hostage/hostage_improv.cpp:2349 */
NOBODY void CHostageImprov::Disagree(void)
{
//	SetPerformance(HostageAnimateState::Disagree(//			enum PerformanceType performance);  //  2355
}

/* <476395> ../cstrike/dlls/hostage/hostage_improv.cpp:2363 */
NOBODY void CHostageImprov::Wave(void)
{
//	SetPerformance(HostageAnimateState::Wave(//			enum PerformanceType performance);  //  2366
}

/* <474938> ../cstrike/dlls/hostage/hostage_improv.cpp:2375 */
NOBODY void CHostageImprov::__MAKE_VHOOK(OnMoveToFailure)(const Vector &goal, MoveToFailureType reason)
{
//	OnMoveToFailure(HostageStateMachine *const this,
//			const Vector &goal,
//			enum MoveToFailureType reason);  //  2378
}

/* <4763d7> ../cstrike/dlls/hostage/hostage_improv.cpp:2391 */
NOBODY void CHostageImprov::Wiggle(void)
{
//	{
//		Vector dir;                                     //  2399
//		Vector lat;                                     //  2400
//		float const force;                                     //  2402
//		float const minStuckJumpTime;                          //  2423
//		IsElapsed(const class CountdownTimer *const this);  //  2393
//		GetStuckDuration(const class CNavPathFollower *const this);  //  2424
//		operator*(float fl,
//				const Vector &v);  //  2419
//		ApplyForce(CHostageImprov *const this,
//				Vector force);  //  2419
//		Start(CountdownTimer *const this,
//			float duration);  //  2396
//		Start(CountdownTimer *const this,
//			float duration);  //  2429
//		operator*(float fl,
//				const Vector &v);  //  2407
//		operator*(float fl,
//				const Vector &v);  //  2411
//		ApplyForce(CHostageImprov *const this,
//				Vector force);  //  2411
//		operator*(float fl,
//				const Vector &v);  //  2415
//	}
}

/* <4766cc> ../cstrike/dlls/hostage/hostage_improv.cpp:2438 */
NOBODY void CHostageImprov::ClearPath(void)
{
//	{
//		class Vectorconst eye;                                //  2448
//		Vector start;                                   //  2451
//		Vector end;                                     //  2452
//		TraceResult result;                                   //  2459
//		IsElapsed(const class CountdownTimer *const this);  //  2440
//		Start(CountdownTimer *const this,
//			float duration);  //  2445
//		Vector(Vector *const this,
//			const Vector &v);  //  2448
//		Vector(Vector *const this,
//			const Vector &v);  //  2451
//		operator*(const Vector *const this,
//				float fl);  //  2453
//		operator+(const Vector *const this,
//				const Vector &v);  //  2454
//		{
//			entvars_t *entity;                           //  2463
//			VARS(edict_t *pent);  //  2463
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  2467
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  2467
//			{
//				class CBaseEntity *pObject;          //  2469
//				Instance(edict_t *pent);  //  2469
//			}
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  2479
//			{
//				class CBaseEntity *pObject;          //  2481
//				Instance(edict_t *pent);  //  2481
//			}
//		}
//	}
}

/* <471b3f> ../cstrike/dlls/hostage/hostage_improv.cpp:2497 */
NOBODY void CHostageImprov::__MAKE_VHOOK(Crouch)(void)
{
//	{
//		float const minCrouchTime;                             //  2503
//	}
//	Crouch(CHostageImprov *const this);  //  2497
}

/* <47195c> ../cstrike/dlls/hostage/hostage_improv.cpp:2516 */
void CHostageImprov::__MAKE_VHOOK(StandUp)(void)
{
	if (!IsCrouching() || !m_minCrouchTimer.IsElapsed())
	{
		return;
	}

	int y;
	for (y = -24; y < 36; y += 12)
	{
		for (int x = -24; x < 36; x += 12)
		{
			TraceResult result;
			UTIL_TraceLine(GetFeet() + Vector(0, 0, 3), GetFeet() + Vector(x, y, 72), ignore_monsters, ignore_glass, m_hostage->edict(), &result);

			if (result.flFraction < 1.0f)
				return;
		}
	}

	if (y == 36)
	{
		m_animateState.Reset();
		UTIL_SetSize(m_hostage->pev, Vector(-10, -10, 0), Vector(10, 10, 62));
		m_isCrouching = false;
	}
}

/* <477114> ../cstrike/dlls/hostage/hostage_improv.cpp:2558 */
NOBODY void CHostageImprov::UpdateStationaryAnimation(void)
{
//	UpdateStationaryAnimation(HostageStateMachine::UpdateStationaryAnimation(//					class CHostageImprov *improv);  //  2560
}

#ifdef HOOK_GAMEDLL


void CHostageImprov::OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
{
	OnMoveToFailure_(goal, reason);
}

bool CHostageImprov::IsAlive(void) const
{
	return IsAlive_();
}

void CHostageImprov::MoveTo(const Vector &goal)
{
	MoveTo_(goal);
}

void CHostageImprov::LookAt(const Vector &target)
{
	LookAt_(target);
}

void CHostageImprov::ClearLookAt(void)
{
	ClearLookAt_();
}

void CHostageImprov::FaceTo(const Vector &goal)
{
	FaceTo_(goal);
}

void CHostageImprov::ClearFaceTo(void)
{
	ClearFaceTo_();
}

bool CHostageImprov::IsAtMoveGoal(float error) const
{
	return IsAtMoveGoal_(error);
}

bool CHostageImprov::IsAtFaceGoal(void) const
{
	return IsAtFaceGoal_();
}

bool CHostageImprov::IsFriendInTheWay(const Vector &goalPos) const
{
	return IsFriendInTheWay_(goalPos);
}

bool CHostageImprov::IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const
{
	return IsFriendInTheWay_(myFriend, goalPos);
}

bool CHostageImprov::Jump(void)
{
	return Jump_();
}

void CHostageImprov::Crouch(void)
{
	Crouch_();
}

void CHostageImprov::StandUp(void)
{
	StandUp_();
}

void CHostageImprov::TrackPath(const Vector &pathGoal, float deltaT)
{
	TrackPath_(pathGoal, deltaT);
}

void CHostageImprov::StartLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos)
{
	StartLadder_(ladder, how, approachPos, departPos);
}

bool CHostageImprov::TraverseLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT)
{
	return TraverseLadder_(ladder, how, approachPos, departPos, deltaT);
}

bool CHostageImprov::GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal)
{
	return GetSimpleGroundHeightWithFloor_(pos, height, normal);
}

void CHostageImprov::Run(void)
{
	Run_();
}

void CHostageImprov::Walk(void)
{
	Walk_();
}

void CHostageImprov::Stop(void)
{
	Stop_();
}

const Vector &CHostageImprov::GetFeet(void) const
{
	return GetFeet_();
}

const Vector &CHostageImprov::GetCentroid(void)
{
	return GetCentroid_();
}

const Vector &CHostageImprov::GetEyes(void) const
{
	return GetEyes_();
}

bool CHostageImprov::IsOnGround(void) const
{
	return IsOnGround_();
}

bool CHostageImprov::IsMoving(void) const
{
	return IsMoving_();
}

bool CHostageImprov::IsVisible(const Vector &pos, bool testFOV) const
{
	return IsVisible_(pos, testFOV);
}

bool CHostageImprov::IsPlayerLookingAtMe(CBasePlayer *other, float cosTolerance) const
{
	return IsPlayerLookingAtMe_(other, cosTolerance);
}

CBasePlayer *CHostageImprov::IsAnyPlayerLookingAtMe(int team, float cosTolerance) const
{
	return IsAnyPlayerLookingAtMe_(team, cosTolerance);
}

CBasePlayer *CHostageImprov::GetClosestPlayerByTravelDistance(int team, float *range) const
{
	return GetClosestPlayerByTravelDistance_(team, range);
}

void CHostageImprov::OnUpdate(float deltaT)
{
	OnUpdate_(deltaT);
}

void CHostageImprov::OnUpkeep(float deltaT)
{
	OnUpkeep_(deltaT);
}

void CHostageImprov::OnReset(void)
{
	OnReset_();
}

void CHostageImprov::OnGameEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	OnGameEvent_(event, entity, other);
}

void CHostageImprov::OnTouch(CBaseEntity *other)
{
	OnTouch_(other);
}

#endif // HOOK_GAMEDLL
