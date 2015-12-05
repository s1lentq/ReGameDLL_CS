#include "precompiled.h"

/* <4703fc> ../cstrike/dlls/hostage/hostage_improv.cpp:19 */
inline void DrawAxes(Vector &origin, int red, int green, int blue)
{
//	{
//		float size;                                           //    21
//	}
}

/* <47353e> ../cstrike/dlls/hostage/hostage_improv.cpp:41 */
CHostageImprov::CHostageImprov(CBaseEntity *entity)
{
	m_hostage = reinterpret_cast<CHostage *>(entity);
	OnReset();
}

/* <470d33> ../cstrike/dlls/hostage/hostage_improv.cpp:52 */
bool CHostageImprov::__MAKE_VHOOK(IsAlive)(void) const
{
	return m_hostage->pev->deadflag != DEAD_DEAD;
}

/* <474809> ../cstrike/dlls/hostage/hostage_improv.cpp:61 */
void CHostageImprov::__MAKE_VHOOK(MoveTo)(const Vector &goal)
{
	m_moveGoal = goal;
	m_path.Invalidate();

	if (m_hasKnownGoodPos)
		return;

	m_hasKnownGoodPos = true;
	SetKnownGoodPosition(GetFeet());
}

// Find "simple" ground height, treating current nav area as part of the floor

/* <4717e4> ../cstrike/dlls/hostage/hostage_improv.cpp:78 */
bool CHostageImprov::__MAKE_VHOOK(GetSimpleGroundHeightWithFloor)(const Vector *pos, float *height, Vector *normal)
{
	if (GetSimpleGroundHeight(pos, height, normal))
	{
		// our current nav area also serves as a ground polygon
		if (m_lastKnownArea != NULL && m_lastKnownArea->IsOverlapping(pos))
			*height = Q_max((*height), m_lastKnownArea->GetZ(pos));

		return true;
	}

	return false;
}

// Check if we need to jump due to height change

/* <473da4> ../cstrike/dlls/hostage/hostage_improv.cpp:96 */
bool CHostageImprov::DiscontinuityJump(float ground, bool onlyJumpDown, bool mustJump)
{
	// Don't try to jump if in the air or crouching.
	if (IsJumping() || IsCrouching() || IsUsingLadder())
		return false;

	float dz = ground - GetFeet().z;

	if (dz > StepHeight && !onlyJumpDown)
	{
		Jump();
		return true;
	}
	else if (dz < -JumpHeight)
	{
		Jump();
		return true;
	}

	return false;
}

/* <470d5b> ../cstrike/dlls/hostage/hostage_improv.cpp:116 */
void CHostageImprov::__MAKE_VHOOK(LookAt)(const Vector &target)
{
	m_isLookingAt = true;
	m_viewGoal = target;
}

/* <470d97> ../cstrike/dlls/hostage/hostage_improv.cpp:126 */
void CHostageImprov::__MAKE_VHOOK(ClearLookAt)(void)
{
	m_isLookingAt = false;
}

/* <470dbf> ../cstrike/dlls/hostage/hostage_improv.cpp:135 */
void CHostageImprov::__MAKE_VHOOK(FaceTo)(const Vector &goal)
{
	m_isFacingTo = true;
	m_faceGoal = goal;
}

/* <470dfb> ../cstrike/dlls/hostage/hostage_improv.cpp:145 */
void CHostageImprov::__MAKE_VHOOK(ClearFaceTo)(void)
{
	m_isFacingTo = false;
}

/* <476a30> ../cstrike/dlls/hostage/hostage_improv.cpp:154 */
void CHostageImprov::MoveTowards(const Vector &pos, float deltaT)
{
	Vector move;
	float_precision accelRate;
	const float crouchWalkRate = 250.0f;

	//
	// Jump up on ledges
	// Because we may not be able to get to our goal position and enter the next
	// area because our extent collides with a nearby vertical ledge, make sure
	// we look far enough ahead to avoid this situation.
	// Can't look too far ahead, or bots will try to jump up slopes.
	//
	// NOTE: We need to do this frequently to catch edges at the right time
	// @todo Look ahead *along path* instead of straight line 
	//

	ClearPath();

	if ((m_lastKnownArea == NULL || !(m_lastKnownArea->GetAttributes() & 8)) && !IsUsingLadder() && !IsJumping() && IsOnGround() && !IsCrouching())
	{
		float ground;
		Vector aheadRay(pos.x - GetFeet().x, pos.y - GetFeet().y, 0);
		aheadRay.NormalizeInPlace();

		bool jumped = false;
		if (IsRunning())
		{
			const float farLookAheadRange = 80.0f;
			Vector normal;
			Vector stepAhead = GetFeet() + farLookAheadRange * aheadRay;
			stepAhead.z += HumanHeight;

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground, &normal ))
			{
				if (normal.z > 0.9f)
					jumped = DiscontinuityJump(ground, HOSTAGE_ONLY_JUMP_DOWN);
			}
		}

		if (!jumped)
		{
			// close up jumping
			// cant be less or will miss jumps over low walls
			const float lookAheadRange = 30.0f;
			Vector stepAhead = GetFeet() + lookAheadRange * aheadRay;
			stepAhead.z += HumanHeight;

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground))
			{
				jumped = DiscontinuityJump(ground);
			}
		}

		if (!jumped)
		{
			// about to fall gap-jumping
			const float lookAheadRange = 10.0f;
			Vector stepAhead = GetFeet() + lookAheadRange * aheadRay;
			stepAhead.z += HumanHeight;

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground))
			{
				jumped = DiscontinuityJump(ground, HOSTAGE_ONLY_JUMP_DOWN, HOSTAGE_MUST_JUMP);
			}
		}
	}

	move = (pos - GetFeet());
	move.z = 0;

	if (!move.IsZero())
	{
		move.NormalizeInPlace();
	}

	switch (m_moveType)
	{
	case Stopped:
		accelRate = 0;
		break;
	case Walking:
		if (IsCrouching())
			accelRate = crouchWalkRate;
		else
			accelRate = 400;
		break;
	case Running:
		if (IsCrouching())
			accelRate = crouchWalkRate;
		else
			accelRate = 1000;
		break;
	}
	
	m_vel.x = move.x * accelRate * deltaT + m_vel.x;
	m_vel.y = move.y * accelRate * deltaT + m_vel.y;
}

void (*pCHostageImprov__FaceTowards)();

/* <473e46> ../cstrike/dlls/hostage/hostage_improv.cpp:262 */
NOBODY bool __declspec(naked) CHostageImprov::FaceTowards(const Vector &target, float deltaT)
{
	__asm
	{
		jmp pCHostageImprov__FaceTowards
	}

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
void CHostageImprov::__MAKE_VHOOK(Stop)(void)
{
	MoveTo(GetFeet());
	m_hostage->pev->velocity = Vector(0, 0, 0);
	
	if (m_moveLimit > Stopped)
		m_moveType = Stopped;
	else
		m_moveType = m_moveLimit;
}

/* <470f4c> ../cstrike/dlls/hostage/hostage_improv.cpp:655 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetFeet)(void) const
{
	return m_hostage->pev->origin;
}

/* <470f74> ../cstrike/dlls/hostage/hostage_improv.cpp:661 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetCentroid)(void) const
{
	m_centroid = m_hostage->pev->origin + Vector(0, 0, 36);
	return m_centroid;
}

/* <470f9c> ../cstrike/dlls/hostage/hostage_improv.cpp:671 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetEyes)(void) const
{
	m_eye = m_hostage->pev->origin + Vector(0, 0, 72) - Vector(0, 0, 7);
	return m_eye;
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
bool CHostageImprov::__MAKE_VHOOK(IsVisible)(const Vector &pos, bool testFOV) const
{
	const Vector eye = GetEyes();
	TraceResult result;

	UTIL_TraceLine(eye, pos, ignore_monsters, ignore_glass, m_hostage->edict(), &result);
	return result.flFraction == 1.0f;
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
void CHostageImprov::SetKnownGoodPosition(const Vector &pos)
{
	if (IsJumping() || IsCrouching())
		return;

	if (m_hasKnownGoodPos)
	{
		if (m_priorKnownGoodPosTimer.IsElapsed())
		{
			m_hasPriorKnownGoodPos = true;
			m_priorKnownGoodPos = m_knownGoodPos;
			m_priorKnownGoodPosTimer.Start(1);
		}
	}

	m_hasKnownGoodPos = true;
	m_knownGoodPos = pos;
}

/* <47486d> ../cstrike/dlls/hostage/hostage_improv.cpp:1038 */
void CHostageImprov::ResetToKnownGoodPosition(void)
{
	const float tolerance = 10.0f;

	if (m_hasKnownGoodPos)
	{
		if ((m_hostage->pev->origin - m_knownGoodPos).IsLengthLessThan(tolerance))
		{
			if (m_hasPriorKnownGoodPos)
			{
				m_hasPriorKnownGoodPos = false;
				m_knownGoodPos = m_priorKnownGoodPos;
				m_priorKnownGoodPosTimer.Start(5);
			}
			else
			{
				m_hasKnownGoodPos = false;
				m_knownGoodPos = m_hostage->m_vStart;
			}
		}
	}
	else
		m_knownGoodPos = m_hostage->m_vStart;

	m_hostage->pev->origin = m_knownGoodPos;
	m_hostage->pev->velocity = Vector(0, 0, 0);
	m_path.Invalidate();

	Stop();
}

/* <47105c> ../cstrike/dlls/hostage/hostage_improv.cpp:1082 */
void CHostageImprov::__MAKE_VHOOK(StartLadder)(const class CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos)
{
	m_traversingLadder = true;
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
bool CHostageImprov::IsTerroristNearby(void)
{
	if (m_nearbyTerroristTimer.IsElapsed())
	{
		CheckForNearbyTerrorists();
		return m_isTerroristNearby;
	}

	return true;
}

/* <474ae7> ../cstrike/dlls/hostage/hostage_improv.cpp:1412 */
void CHostageImprov::CheckForNearbyTerrorists(void)
{
	const float checkInterval = 2.0f;
	float range;

	if (!m_checkNearbyTerroristTimer.IsElapsed())
		return;

	m_checkNearbyTerroristTimer.Start(checkInterval);
	m_isTerroristNearby = false;

	if (GetClosestPlayerByTravelDistance(TERRORIST, &range))
	{
		const float nearbyTerroristRange = 2000.0f;
		if (range < nearbyTerroristRange)
		{
			m_isTerroristNearby = true;
			m_nearbyTerroristTimer.Start(10);
		}
	}
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
void CHostageImprov::__MAKE_VHOOK(OnGameEvent)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_BULLET_IMPACT:
	{
		Vector *impactPos = (Vector *)other;
		const float nearRange = 100.0f;

		if ((GetCentroid() - *impactPos).IsLengthLessThan(nearRange))
		{
			Frighten(TERRIFIED);
		}
		break;
	}
	case EVENT_PLAYER_DIED:
	case EVENT_HOSTAGE_KILLED:
		if (IsVisible(entity->pev->origin, true))
		{
			Frighten(TERRIFIED);

			if (!entity->IsPlayer() || entity->IsPlayer() && ((CBasePlayer *)entity)->m_iTeam != TERRORIST)
			{
				DelayedChatter(RANDOM_FLOAT(0.5, 0.7), HOSTAGE_CHATTER_SCARED_OF_MURDER, true);
			}
			if (!entity->IsPlayer())
			{
				m_idleState.OnInjury(0);
			}
		}
		break;
	case EVENT_HOSTAGE_RESCUED:
		if (m_hostage == other)
		{
			if (!entity)
				return;

			Chatter(HOSTAGE_CHATTER_RESCUED);
		}
		break;
	case EVENT_TERRORISTS_WIN:
		Frighten(SCARED);
		m_isDelayedChatterPending = false;
		DelayedChatter(RANDOM_FLOAT(1.0, 4.0), HOSTAGE_CHATTER_TERRORISTS_WIN);
		return;
	case EVENT_CTS_WIN:
		m_scaredTimer.Invalidate();
		m_isDelayedChatterPending = false;
		DelayedChatter(RANDOM_FLOAT(1.0, 4.0), HOSTAGE_CHATTER_CTS_WIN);
		return;
	default:
		break;
	}

	float range;
	PriorityType priority;
	bool isHostile;
	
	if (entity != NULL && IsGameEventAudible(event, entity, other, &range, &priority, &isHostile))
	{
		const float fudge = 0.4f;

		if ((m_hostage->pev->origin - entity->pev->origin).IsLengthLessThan(range * fudge))
		{
			m_lastNoiseTimer.Start();

			if (isHostile)
			{
				Frighten(SCARED);

				switch (event)
				{
				case EVENT_WEAPON_FIRED:
				{
					DelayedChatter(RANDOM_FLOAT(0.3, 1.0), HOSTAGE_CHATTER_SCARED_OF_GUNFIRE);
					break;
				}
				case EVENT_HE_GRENADE_EXPLODED:
				case EVENT_SMOKE_GRENADE_EXPLODED:
				case EVENT_BREAK_GLASS:
				case EVENT_BREAK_WOOD:
				case EVENT_BREAK_METAL:
				case EVENT_BREAK_FLESH:
				case EVENT_BREAK_CONCRETE:
					DelayedChatter(RANDOM_FLOAT(0.3, 1.0), HOSTAGE_CHATTER_LOOK_OUT);
					break;

				default:
					break;
				}
			}
		}
	}

	if (event == EVENT_FLASHBANG_GRENADE_EXPLODED)
	{
		Vector *impactPos = (Vector *)other;
		const float flashRange = 1000.0f;

		if ((GetEyes() - *impactPos).IsLengthLessThan(flashRange) && IsVisible(*impactPos))
		{
			DelayedChatter(RANDOM_FLOAT(0.0, 1.0), HOSTAGE_CHATTER_BLINDED, true);
			Frighten(TERRIFIED);
		}
	}
}

/* <471e27> ../cstrike/dlls/hostage/hostage_improv.cpp:1854 */
void CHostageImprov::__MAKE_VHOOK(OnTouch)(CBaseEntity *other)
{
	const char *classname;
	Vector2D to;
	const float pushForce = 20.0f;

	classname = STRING(other->pev->classname);

	if (cv_hostage_debug.value != 0.0)
	{
		CONSOLE_ECHO("%5.1f: Hostage hit '%s'\n", gpGlobals->time, classname);
	}

	m_collisionTimer.Start();

	if (FStrEq(classname, "worldspawn"))
	{
		const float lookAheadRange = 30.0f;
		float ground;
		Vector normal = Vector(0, 0, 1);
		Vector alongFloor;
		TraceResult result;
		bool isStep = false;

		UTIL_MakeVectors(m_hostage->pev->angles);

		if (!GetSimpleGroundHeightWithFloor(&GetEyes(), &ground, &normal))
			return;

		if (cv_hostage_debug.value < 0.0)
		{
			UTIL_DrawBeamPoints(GetFeet() + normal * 50, GetFeet(), 2, 255, 255, 0);
		}

		alongFloor = CrossProduct(normal, gpGlobals->v_right);

		Vector pos = alongFloor * lookAheadRange;

		for (float offset = 1.0f; offset <= 18.0f; offset += 3.0f)
		{
			Vector vecStart = GetFeet();
			vecStart.z += offset;

			UTIL_TraceLine(vecStart, vecStart + pos, ignore_monsters, dont_ignore_glass, m_hostage->pev->pContainingEntity, &result);

			if (result.flFraction < 1.0f && result.vecPlaneNormal[2] < 0.7f)
			{
				isStep = true;
				break;
			}
		}

		if (isStep)
		{
			float stepAheadGround = pos.z;
			Vector stepAheadNormal = Vector(0, 0, stepAheadGround);

			m_inhibitObstacleAvoidance.Start(0.5);

			for (float range = 1.0f; range <= 30.5f; range += 5.0f)
			{
				Vector stepAhead = GetFeet() + alongFloor * range;

				if (GetSimpleGroundHeightWithFloor(&stepAhead, &stepAheadGround, &stepAheadNormal))
				{
					float dz = stepAheadGround - GetFeet().z;

					if (dz > 0.0f && dz < 18.0f)
					{
						m_hostage->pev->origin.z = stepAheadGround + 3.0f;
						break;
					}
				}
			}
		}
		else if (!IsMoving() && !IsUsingLadder())
		{
			bool isSeam = false;
			const float checkSeamRange = 50.0f;
			Vector posBehind;

			posBehind = GetEyes() - alongFloor * checkSeamRange;
			UTIL_TraceLine(posBehind, posBehind - Vector(0, 0, 9999), ignore_monsters, dont_ignore_glass, m_hostage->pev->pContainingEntity, &result);

			if (result.flFraction < 1.0f && DotProduct(result.vecPlaneNormal, normal) < 1.0f)
			{
				isSeam = true;
			}
			else
			{
				Vector posAhead = GetEyes() + alongFloor * checkSeamRange;
				UTIL_TraceLine(posAhead, posAhead - Vector(0, 0, 9999), ignore_monsters, dont_ignore_glass, m_hostage->pev->pContainingEntity, &result);

				if (result.flFraction < 1.0f && DotProduct(result.vecPlaneNormal, normal) < 1.0f)
					isSeam = true;
			}

			if (isSeam)
			{
				if (cv_hostage_debug.value != 0.0)
				{
					CONSOLE_ECHO("Hostage stuck on seam.\n");
				}

				const float nudge = 3.0f;
				m_hostage->pev->origin.z += nudge;
			}
		}
	}
	else if (FStrEq(classname, "func_breakable"))
	{
		other->TakeDamage(m_hostage->pev, m_hostage->pev, 9999.9, DMG_BULLET);
	}
	else if (other->IsPlayer() || FClassnameIs(other->pev, "hostage_entity"))
	{
		to = (m_hostage->pev->origin - other->pev->origin).Make2D();
		to.NormalizeInPlace();

		m_vel.x += to.x * pushForce;
		m_vel.y += to.y * pushForce;
	}
}

/* <474ba8> ../cstrike/dlls/hostage/hostage_improv.cpp:2006 */
void CHostageImprov::ApplyForce(Vector force)
{
	m_vel.x += force.x;
	m_vel.y += force.y;
}

/* <474bd5> ../cstrike/dlls/hostage/hostage_improv.cpp:2016 */
bool CHostageImprov::IsAtHome(void)
{
	return m_hostage->IsAtHome();
}

/* <474c76> ../cstrike/dlls/hostage/hostage_improv.cpp:2025 */
bool CHostageImprov::CanSeeRescueZone(void)
{
	CCSBotManager *ctrl = TheCSBots();

	if (ctrl == NULL)
		return false;

	const CCSBotManager::Zone *zone = ctrl->GetClosestZone(&GetCentroid());

	if (zone != NULL)
		return IsVisible(zone->m_center);

	return false;
}

/* <474cd3> ../cstrike/dlls/hostage/hostage_improv.cpp:2047 */
CBasePlayer *CHostageImprov::GetClosestVisiblePlayer(int team)
{
	CBasePlayer *close = NULL;
	float closeRangeSq = 1e8f;

	for (int i = 0; i < m_visiblePlayerCount; i++)
	{
		CBasePlayer *player = (CBasePlayer *)((CBaseEntity *)m_visiblePlayer[i]);

		if (player == NULL || (team > 0 && player->m_iTeam != team))
			continue;

		float_precision rangeSq = (GetCentroid() - player->pev->origin).LengthSquared();

		if (rangeSq < closeRangeSq)
		{
			closeRangeSq = rangeSq;
			close = player;
		}
	}

	return close;
}

/* <474db2> ../cstrike/dlls/hostage/hostage_improv.cpp:2080 */
float CHostageImprov::GetTimeSinceLastSawPlayer(int team)
{
	float timeCT = m_lastSawCT.GetElapsedTime();
	float timeT = m_lastSawT.GetElapsedTime();

	switch (team)
	{
	case TERRORIST:
		return timeT;
	case CT:
		return timeCT;
	default:
		return (timeCT < timeT) ? timeCT : timeT;
	}
}

/* <474f2c> ../cstrike/dlls/hostage/hostage_improv.cpp:2098 */
float CHostageImprov::GetTimeSinceLastInjury(void)
{
	return m_lastInjuryTimer.GetElapsedTime();
}

/* <474fb3> ../cstrike/dlls/hostage/hostage_improv.cpp:2107 */
float CHostageImprov::GetTimeSinceLastNoise(void)
{
	return m_lastNoiseTimer.GetElapsedTime();
}

/* <47503a> ../cstrike/dlls/hostage/hostage_improv.cpp:2117 */
bool CHostageImprov::IsScared(void)
{
	if (m_scaredTimer.IsElapsed())
	{
		return m_animateState.GetPerformance() == HostageAnimateState::Afraid;
	}

	return true;
}

/* <47506e> ../cstrike/dlls/hostage/hostage_improv.cpp:2129 */
void CHostageImprov::Frighten(ScareType scare)
{
	const float ignoreTime = 10.0f;

	if (!IsScared())
	{
		m_animateState.Reset();
		m_blinkTimer.Invalidate();
	}

	m_scareIntensity = scare;

	switch (scare)
	{
	case NERVOUS:
		m_scaredTimer.Start(RANDOM_FLOAT(2, 4));
		break;
	case SCARED:
		m_scaredTimer.Start(RANDOM_FLOAT(3, 8));
		break;
	case TERRIFIED:
		m_scaredTimer.Start(RANDOM_FLOAT(5, 10));
		m_ignoreTerroristTimer.Start(ignoreTime);
		break;
	}
}

/* <475200> ../cstrike/dlls/hostage/hostage_improv.cpp:2165 */
void CHostageImprov::Afraid(void)
{
	char animInto[32];
	char animLoop[32];
	char animExit[32];

	if (IsCrouching())
		return;

	if (m_animateState.GetPerformance() == HostageAnimateState::Flinching ||
		m_animateState.GetPerformance() == HostageAnimateState::Afraid)
		return;

	if (!IsMoving())
	{
		m_animateState.Reset();
		m_animateState.SetPerformance(HostageAnimateState::Afraid);

		int which = RANDOM_LONG(0, 100) % 3 + 1;

		Q_sprintf(animInto, "cower_into_%d", which);
		Q_sprintf(animLoop, "cower_loop_%d", which);
		Q_sprintf(animExit, "cower_exit_%d", which);
	
		m_animateState.AddSequence(this, animInto);
		m_animateState.AddSequence(this, animLoop, RANDOM_FLOAT(3, 10));
		m_animateState.AddSequence(this, animExit);
	}
}

/* <475290> ../cstrike/dlls/hostage/hostage_improv.cpp:2201 */
void CHostageImprov::UpdateIdleActivity(Activity activity, Activity fidget)
{
	if (m_animateState.IsBusy())
		return;

	m_animateState.Reset();

	if (m_didFidget || fidget == ACT_RESET)
	{
		m_animateState.AddSequence(this, activity, RANDOM_FLOAT(1, 10), RANDOM_FLOAT(0.9, 1.1));
		m_didFidget = false;

	}
	else
	{
		m_animateState.AddSequence(this, fidget, -1, RANDOM_FLOAT(0.9, 1.5));
		m_didFidget = true;

	}
}

/* <4752d9> ../cstrike/dlls/hostage/hostage_improv.cpp:2226 */
void CHostageImprov::Chatter(HostageChatterType sayType, bool mustSpeak)
{
	if (!IsAlive() && sayType != HOSTAGE_CHATTER_DEATH_CRY)
		return;

	if (g_pHostages->IsNearbyHostageTalking(this) && !mustSpeak)
		return;

	if (m_chatterTimer.IsElapsed() || mustSpeak)
	{
		m_chatterTimer.Start(RANDOM_FLOAT(5, 15));
		float duration = g_pHostages->GetChatter()->PlaySound(m_hostage, sayType);
		m_talkingTimer.Start(duration);
	}
}

/* <475b35> ../cstrike/dlls/hostage/hostage_improv.cpp:2249 */
void CHostageImprov::DelayedChatter(float delayTime, HostageChatterType sayType, bool mustSpeak)
{
	if (!IsAlive())
		return;

	if (!m_isDelayedChatterPending || mustSpeak)
	{
		m_isDelayedChatterPending = true;
		m_delayedChatterTimer.Start(delayTime);
		m_delayedChatterType = sayType;
		m_delayedChatterMustSpeak = mustSpeak;
	}
}

/* <475bd4> ../cstrike/dlls/hostage/hostage_improv.cpp:2268 */
NOXREF void CHostageImprov::UpdateDelayedChatter(void)
{
	if (!m_isDelayedChatterPending)
		return;

	if (!m_delayedChatterTimer.IsElapsed())
		return;

	m_isDelayedChatterPending = false;

	switch (m_delayedChatterType)
	{
	case HOSTAGE_CHATTER_SCARED_OF_GUNFIRE:
		if (RANDOM_FLOAT(0, 100) < 25)
		{
			Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		}
		break;
	case HOSTAGE_CHATTER_LOOK_OUT:
	case HOSTAGE_CHATTER_PLEASE_RESCUE_ME:
	case HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE:
		if (RANDOM_FLOAT(0, 100) < 60)
		{
			Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		}
		break;
	default:
		Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		break;
	}
}

/* <4761eb> ../cstrike/dlls/hostage/hostage_improv.cpp:2307 */
void CHostageImprov::Flinch(Activity activity)
{
	Chatter(HOSTAGE_CHATTER_PAIN, true);

	if (!IsCrouching() && !IsMoving())
	{
		m_animateState.Reset();
		m_animateState.SetPerformance(HostageAnimateState::Flinching);
		m_animateState.AddSequence(this, activity);
	}
}

/* <4762fe> ../cstrike/dlls/hostage/hostage_improv.cpp:2329 */
void CHostageImprov::CrouchDie(void)
{
	m_animateState.Reset();
	m_animateState.AddSequence(this, ACT_CROUCH_DIE);
}

/* <476327> ../cstrike/dlls/hostage/hostage_improv.cpp:2339 */
void CHostageImprov::Agree(void)
{
	m_animateState.Reset();
	m_animateState.AddSequence(this, ACT_YES);
}

/* <476350> ../cstrike/dlls/hostage/hostage_improv.cpp:2349 */
void CHostageImprov::Disagree(void)
{
	if (m_animateState.GetPerformance() != HostageAnimateState::Disagreeing)
	{
		m_animateState.Reset();
		m_animateState.AddSequence(this, ACT_NO, -1.0, RANDOM_FLOAT(1.5, 3.0));
	}
}

/* <476395> ../cstrike/dlls/hostage/hostage_improv.cpp:2363 */
void CHostageImprov::Wave(void)
{
	m_animateState.Reset();
	m_animateState.SetPerformance(HostageAnimateState::Waving);
	m_animateState.AddSequence(this, ACT_WAVE);
}

/* <474938> ../cstrike/dlls/hostage/hostage_improv.cpp:2375 */
void CHostageImprov::__MAKE_VHOOK(OnMoveToFailure)(const Vector &goal, MoveToFailureType reason)
{
	m_behavior.OnMoveToFailure(goal, reason);

	if (reason == FAIL_STUCK)
	{
		ResetToKnownGoodPosition();
	}
}

/* <4763d7> ../cstrike/dlls/hostage/hostage_improv.cpp:2391 */
void CHostageImprov::Wiggle(void)
{
	Vector dir;
	Vector lat;

	const float force = 15.0f;
	const float minStuckJumpTime = 0.5f;

	// for wiggling
	if (m_wiggleTimer.IsElapsed())
	{
		m_wiggleDirection = static_cast<NavRelativeDirType>(RANDOM_LONG(FORWARD, LEFT));
		m_wiggleTimer.Start(RANDOM_FLOAT(0.3, 0.5));
	}

	lat.x = BotCOS(m_moveAngle);
	lat.y = BotSIN(m_moveAngle);
	lat.z = 0;

	switch (m_wiggleDirection)
	{
	case FORWARD:
		dir.x = lat.x;
		dir.y = lat.y;

		ApplyForce(dir * force);
		break;
	case RIGHT:
		dir.x = -lat.y;
		dir.y = lat.x;

		ApplyForce(dir * -force);
		break;
	case BACKWARD:
		dir.x = lat.x;
		dir.y = lat.y;

		ApplyForce(dir * -force);
		break;
	case LEFT:
		dir.x = -lat.y;
		dir.y = lat.x;

		ApplyForce(dir * force);
		break;
	default:
		break;
	}
	
	if (m_follower.GetStuckDuration() > minStuckJumpTime && m_wiggleJumpTimer.IsElapsed())
	{
		if (Jump())
		{
			m_wiggleJumpTimer.Start(RANDOM_FLOAT(0.75, 1.2));
		}
	}
}

/* <4766cc> ../cstrike/dlls/hostage/hostage_improv.cpp:2438 */
void CHostageImprov::ClearPath(void)
{
	Vector start;
	Vector end;
	TraceResult result;

	if (!m_clearPathTimer.IsElapsed())
		return;

	m_clearPathTimer.Start(RANDOM_FLOAT(0.3, 0.5));

	const Vector eye = GetEyes();
	start = eye;

	UTIL_MakeVectors(m_hostage->pev->angles);
	end = gpGlobals->v_forward * 64 + start;

	UTIL_TraceLine(start, end, ignore_monsters, dont_ignore_glass, m_hostage->edict(), &result);

	if (result.flFraction == 1.0f)
		return;

	if (result.pHit != NULL)
	{
		entvars_t *entity = VARS(result.pHit);

		if (FClassnameIs(entity, "func_door") || FClassnameIs(entity, "func_door_rotating"))
		{
			CBaseEntity *pObject = CBaseEntity::Instance(entity);

			if (pObject != NULL)
			{
				pObject->Touch(m_hostage);
			}
		}
		else if (FClassnameIs(entity, "func_breakable") && entity->takedamage == DAMAGE_YES)
		{
			CBaseEntity *pObject = CBaseEntity::Instance(entity);

			if (pObject != NULL)
			{
				pObject->TakeDamage(m_hostage->pev, m_hostage->pev, 9999.9, DMG_BULLET);
			}
		}
	}
}

/* <471b3f> ../cstrike/dlls/hostage/hostage_improv.cpp:2497 */
void CHostageImprov::__MAKE_VHOOK(Crouch)(void)
{
	const float minCrouchTime = 1.0f;

	if (IsCrouching())
		return;

	m_isCrouching = true;
	m_minCrouchTimer.Start(minCrouchTime);
	UTIL_SetSize(m_hostage->pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_CROUCH);
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
void CHostageImprov::UpdateStationaryAnimation(void)
{
	m_behavior.UpdateStationaryAnimation(this);
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

const Vector &CHostageImprov::GetCentroid(void) const
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
