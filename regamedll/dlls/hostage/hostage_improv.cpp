#include "precompiled.h"

/* <4703fc> ../cstrike/dlls/hostage/hostage_improv.cpp:19 */
inline void DrawAxes(const Vector &origin, int red, int green, int blue)
{
	float size = 10;

	if (cv_hostage_debug.value != 1.0f)
		return;

	UTIL_DrawBeamPoints(origin - Vector(size, 0, 0), origin + Vector(size, 0, 0), 2, red, green, blue);
	UTIL_DrawBeamPoints(origin - Vector(0, size, 0), origin + Vector(0, size, 0), 2, red, green, blue);
	UTIL_DrawBeamPoints(origin + Vector(0, 0, size), origin - Vector(0, 0, size), 2, red, green, blue);
}

/* <47353e> ../cstrike/dlls/hostage/hostage_improv.cpp:41 */
CHostageImprov::CHostageImprov(CBaseEntity *entity)
{
	m_hostage = static_cast<CHostage *>(entity);
	OnReset();
}

/* <470d33> ../cstrike/dlls/hostage/hostage_improv.cpp:52 */
bool CHostageImprov::__MAKE_VHOOK(IsAlive)() const
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
void CHostageImprov::__MAKE_VHOOK(ClearLookAt)()
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
void CHostageImprov::__MAKE_VHOOK(ClearFaceTo)()
{
	m_isFacingTo = false;
}

/* <476a30> ../cstrike/dlls/hostage/hostage_improv.cpp:154 */
void CHostageImprov::MoveTowards(const Vector &pos, float deltaT)
{
	Vector move;
	float_precision accelRate;
	const float crouchWalkRate = 250.0f;

	// Jump up on ledges
	// Because we may not be able to get to our goal position and enter the next
	// area because our extent collides with a nearby vertical ledge, make sure
	// we look far enough ahead to avoid this situation.
	// Can't look too far ahead, or bots will try to jump up slopes.
	//
	// NOTE: We need to do this frequently to catch edges at the right time
	// TODO: Look ahead *along path* instead of straight line

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

/* <473e46> ../cstrike/dlls/hostage/hostage_improv.cpp:262 */
bool CHostageImprov::FaceTowards(const Vector &target, float deltaT)
{
	float error = 0;
	Vector2D to = (target - GetFeet()).Make2D();

#ifndef PLAY_GAMEDLL
	to.NormalizeInPlace();
#else
	// TODO: fix test demo
	float_precision float_x = target.x - GetFeet().x;
	float_precision float_y = target.y - GetFeet().y;
	float_precision flLen = to.Length();

	if (flLen <= 0)
	{
		to.x = 1;
		to.y = 0;
	}
	else
	{
		to.x = float_x / flLen;
		to.y = float_y / flLen;
	}
#endif // PLAY_GAMEDLL

	float moveAngle = GetMoveAngle();

	Vector2D lat(BotCOS(moveAngle), BotSIN(moveAngle));
	Vector2D dir(-lat.y, lat.x);

	float_precision dot = DotProduct(to, dir);

	if (DotProduct(to, lat) < 0.0f)
	{
		if (dot >= 0.0f)
			dot = 1.0f;
		else
			dot = -1.0f;

		error = 1;
	}

	const float maxTurnRate = 0.05f;

	if (error || fabs(dot) >= maxTurnRate)
	{
		const float tolerance = 300.0f;
		float moveRatio = dot * deltaT * tolerance + moveAngle;

		BotCOS(moveRatio);
		BotSIN(moveRatio);

		m_moveAngle = moveRatio;
		m_hostage->pev->angles.y = moveRatio;

		return false;
	}

	return true;
}

/* <47402b> ../cstrike/dlls/hostage/hostage_improv.cpp:308 */
void CHostageImprov::FaceOutwards()
{
	TraceResult result;
	Vector to;
	float farthestRange = 0.0f;
	int farthest = 0;

	static Vector corner[] =
	{
		Vector(-1000, 1000, 0),
		Vector(1000, 1000, 0),
		Vector(-1000, -1000, 0),
		Vector(1000, -1000, 0)
	};

	const int cornerCount = ARRAYSIZE(corner);

	for (int i = 0; i < cornerCount; ++i)
	{
		to = GetCentroid() + corner[i];

		UTIL_TraceLine(GetCentroid(), to, ignore_monsters, ignore_glass, m_hostage->edict(), &result);

		float_precision range = (result.vecEndPos - GetCentroid()).LengthSquared();

		if (range > farthestRange)
		{
			farthestRange = range;
			farthest = i;
		}
	}

	to = GetCentroid() + corner[farthest];
	FaceTo(to);
}

/* <470e23> ../cstrike/dlls/hostage/hostage_improv.cpp:344 */
bool CHostageImprov::__MAKE_VHOOK(IsAtMoveGoal)(float error) const
{
	return (GetFeet() - m_moveGoal).IsLengthLessThan(error);
}

/* <470eab> ../cstrike/dlls/hostage/hostage_improv.cpp:353 */
bool CHostageImprov::__MAKE_VHOOK(IsAtFaceGoal)() const
{
	return false;
}

// Return true if a friend is between us and the given position

/* <46fb4b> ../cstrike/dlls/hostage/hostage_improv.cpp:395 */
bool CHostageImprov::__MAKE_VHOOK(IsFriendInTheWay)(const Vector &goalPos) const
{
	// do this check less often to ease CPU burden
	if (!m_avoidFriendTimer.IsElapsed())
	{
		return m_isFriendInTheWay;
	}

	const float avoidFriendInterval = 0.5f;
	m_avoidFriendTimer.Start(avoidFriendInterval);

	CheckWayFunctor check(this, goalPos);

	if (g_pHostages != NULL)
	{
		g_pHostages->ForEachHostage(check);

		if (check.m_blocker != NULL)
		{
			return m_isFriendInTheWay = true;
		}
	}

	// check if any CT are overlapping this linear path
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (!player->IsAlive() || player->m_iTeam == TERRORIST)
			continue;

		if (IsFriendInTheWay(player, goalPos))
		{
			m_isFriendInTheWay = true;
			break;
		}
	}

	return m_isFriendInTheWay;
}

// Return true if a friend is between us and the given entity

/* <472b83> ../cstrike/dlls/hostage/hostage_improv.cpp:453 */
bool CHostageImprov::__MAKE_VHOOK(IsFriendInTheWay)(CBaseEntity *myFriend, const Vector &goalPos) const
{
	if (m_hostage == myFriend)
		return false;

	// compute ray along intended path
	Vector moveDir = goalPos - GetFeet();
	Vector friendFeet = myFriend->pev->origin;

	// make it a unit vector
	float length = moveDir.NormalizeInPlace();

	if (myFriend->IsPlayer())
		friendFeet.z = myFriend->pev->absmin.z;

	Vector toFriend = friendFeet - GetFeet();

	// check if friend is in our "personal space"
	const float personalSpace = 100.0f;
	if (toFriend.IsLengthGreaterThan(personalSpace))
		return false;

	// find distance of friend along our movement path
	float friendDistAlong = DotProduct(toFriend, moveDir);

	// if friend is behind us, ignore him
	if (friendDistAlong <= 0.0f)
		return false;

	// constrain point to be on path segment
	Vector pos;
	if (friendDistAlong >= length)
		pos = goalPos;
	else
		pos = GetFeet() + moveDir * friendDistAlong;

	// check if friend overlaps our intended line of movement
	const float friendRadius = 30.0f;
	if (!(pos - friendFeet).IsLengthLessThan(friendRadius))
		return false;

	if (!myFriend->pev->velocity.IsZero())
	{
		if (DotProduct(myFriend->pev->velocity, m_hostage->pev->velocity) >= 0.0)
			return false;
	}

	// friend is in our personal space and overlaps our intended line of movement
	return true;
}

/* <474309> ../cstrike/dlls/hostage/hostage_improv.cpp:557 */
bool CHostageImprov::IsFriendInTheWay() const
{
	CheckAhead check(this);
	g_pHostages->ForEachHostage(check);
	ForEachPlayer(check);

	return check.IsBlocked();
}

/* <474631> ../cstrike/dlls/hostage/hostage_improv.cpp:568 */
float CHostageImprov::GetSpeed()
{
	return -1.0f;
}

/* <46f249> ../cstrike/dlls/hostage/hostage_improv.cpp:592 */
bool CHostageImprov::__MAKE_VHOOK(Jump)()
{
	if (IsCrouching() || g_pHostages->IsNearbyHostageJumping(this))
		return false;

	if (!m_jumpTimer.IsElapsed())
		return false;

	const float epsilon = 1.0f;

	m_hasJumped = false;
	m_moveFlags |= IN_JUMP;

	if (m_hostage->pev->velocity.LengthSquared() < epsilon)
	{
		const float fudge = 2.0f;
		m_hostage->pev->origin.z += fudge;
	}

	const float minJumpInterval = 3.0f;
	m_jumpTimer.Start(minJumpInterval);

	m_animateState.Reset();
	m_animateState.SetPerformance(HostageAnimateState::Jump);
	m_animateState.AddSequence(this, ACT_HOP);

	return true;
}

/* <470ed3> ../cstrike/dlls/hostage/hostage_improv.cpp:632 */
void CHostageImprov::__MAKE_VHOOK(Run)()
{
	m_moveType = m_moveLimit;
}

/* <470efb> ../cstrike/dlls/hostage/hostage_improv.cpp:638 */
void CHostageImprov::__MAKE_VHOOK(Walk)()
{
	m_moveType = (m_moveLimit > Walking) ? Walking : m_moveLimit;
}

/* <470f23> ../cstrike/dlls/hostage/hostage_improv.cpp:644 */
void CHostageImprov::__MAKE_VHOOK(Stop)()
{
	MoveTo(GetFeet());
	m_hostage->pev->velocity = Vector(0, 0, 0);

	if (m_moveLimit > Stopped)
		m_moveType = Stopped;
	else
		m_moveType = m_moveLimit;
}

/* <470f4c> ../cstrike/dlls/hostage/hostage_improv.cpp:655 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetFeet)() const
{
	return m_hostage->pev->origin;
}

/* <470f74> ../cstrike/dlls/hostage/hostage_improv.cpp:661 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetCentroid)() const
{
	m_centroid = m_hostage->pev->origin + Vector(0, 0, 36);
	return m_centroid;
}

/* <470f9c> ../cstrike/dlls/hostage/hostage_improv.cpp:671 */
const Vector &CHostageImprov::__MAKE_VHOOK(GetEyes)() const
{
	m_eye = m_hostage->pev->origin + Vector(0, 0, 72) - Vector(0, 0, 7);
	return m_eye;
}

/* <470fc4> ../cstrike/dlls/hostage/hostage_improv.cpp:681 */
bool CHostageImprov::__MAKE_VHOOK(IsOnGround)() const
{
	return (m_hostage->pev->flags & FL_ONGROUND) != 0;
}

/* <470fec> ../cstrike/dlls/hostage/hostage_improv.cpp:687 */
bool CHostageImprov::__MAKE_VHOOK(IsMoving)() const
{
	float const epsilon = 10.0f;
	return m_actualVel.IsLengthGreaterThan(epsilon);
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
bool CHostageImprov::__MAKE_VHOOK(IsPlayerLookingAtMe)(CBasePlayer *other, float cosTolerance) const
{
	Vector2D toOther = (other->pev->origin - GetCentroid()).Make2D();
	toOther.NormalizeInPlace();

	UTIL_MakeVectors(other->pev->punchangle + other->pev->v_angle);

	Vector2D otherDir = gpGlobals->v_forward.Make2D();
	otherDir.NormalizeInPlace();

	if (-cosTolerance > DotProduct(toOther, otherDir))
	{
		if (IsVisible(other->EyePosition()))
		{
			return true;
		}
	}

	return false;
}

/* <472a9f> ../cstrike/dlls/hostage/hostage_improv.cpp:757 */
CBasePlayer *CHostageImprov::__MAKE_VHOOK(IsAnyPlayerLookingAtMe)(int team, float cosTolerance) const
{
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (!IsEntityValid(player))
			continue;

		if (player->IsAlive() && (team == UNASSIGNED || player->m_iTeam == team))
		{
			if (IsPlayerLookingAtMe(player, cosTolerance))
			{
				return player;
			}
		}
	}

	return NULL;
}

/* <472e7b> ../cstrike/dlls/hostage/hostage_improv.cpp:783 */
CBasePlayer *CHostageImprov::__MAKE_VHOOK(GetClosestPlayerByTravelDistance)(int team, float *range) const
{
	CBasePlayer *close = NULL;
	float closeRange = 9.9999998e10f;

	if (GetLastKnownArea() == NULL)
		return NULL;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (!IsEntityValid(player))
			continue;

		if (player->IsAlive() && (team == UNASSIGNED || player->m_iTeam == team))
		{
			ShortestPathCost cost;
			Vector vecCenter = player->Center();

			float_precision range = NavAreaTravelDistance(GetLastKnownArea(), TheNavAreaGrid.GetNearestNavArea(&vecCenter), cost);

			if (range > 0 && range < closeRange)
			{
				closeRange = range;
				close = player;
			}
		}
	}

	if (range)
		*range = closeRange;

	return close;
}

/* <47166d> ../cstrike/dlls/hostage/hostage_improv.cpp:822 */
void CHostageImprov::__MAKE_VHOOK(OnReset)()
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
void CHostageImprov::UpdateVision()
{
	if (!m_visionTimer.IsElapsed())
		return;

	m_visiblePlayerCount = false;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (player->IsAlive() && IsVisible(player->pev->origin, true))
		{
			m_visiblePlayer[m_visiblePlayerCount] = player;

			if (player->m_iTeam == TERRORIST)
				m_lastSawT.Start();
			else
				m_lastSawCT.Start();

			if (++m_visiblePlayerCount == ARRAYSIZE(m_visiblePlayer))
				break;
		}
	}

	m_visionTimer.Start(RANDOM_FLOAT(0.4, 0.6));
}

/* <476e49> ../cstrike/dlls/hostage/hostage_improv.cpp:997 */
void CHostageImprov::__MAKE_VHOOK(TrackPath)(const Vector &pathGoal, float deltaT)
{
	FaceTowards(pathGoal, deltaT);
	MoveTowards(pathGoal, deltaT);

	m_jumpTarget = pathGoal;
	DrawAxes(pathGoal, 255, 0, 255);
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
void CHostageImprov::ResetToKnownGoodPosition()
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
void CHostageImprov::__MAKE_VHOOK(StartLadder)(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos)
{
	m_traversingLadder = true;
}

/* <4710c4> ../cstrike/dlls/hostage/hostage_improv.cpp:1094 */
bool CHostageImprov::__MAKE_VHOOK(TraverseLadder)(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT)
{
	Vector goal;

	if (how == GO_LADDER_DOWN)
	{
		goal = ladder->m_bottom;
		AddDirectionVector(&goal, ladder->m_dir, 16);

		if (ladder->m_top.z - 36.0f > GetFeet().z)
		{
			const float atGoalRange = 50.0f;
			if ((GetFeet() - goal).Make2D().IsLengthLessThan(atGoalRange))
			{
				m_hostage->pev->velocity.z = -100.0f;
			}
		}

		if (ladder->m_bottom.z + 36.0f > GetFeet().z)
			return true;
	}
	else if (m_traversingLadder)
	{
		goal = ladder->m_top;
		AddDirectionVector(&goal, ladder->m_dir, 16);

		const float walkRange = 100.0f;

		if ((GetFeet() - goal).Make2D().IsLengthLessThan(walkRange))
		{
			Walk();
		}

		const float ladderRange = 40.0f;
		if ((GetFeet() - goal).Make2D().IsLengthLessThan(ladderRange))
		{
			m_hostage->pev->velocity.z = 150.0;
		}

		if (GetFeet().z > ladder->m_top.z)
			m_traversingLadder = false;
	}
	else
	{
		if (departPos != NULL)
		{
			float closeRange = 1e6;
			float range;

			if (ladder->m_topForwardArea != NULL)
			{
				range = (*departPos - *ladder->m_topForwardArea->GetCenter()).LengthSquared();

				if (range < closeRange)
				{
					closeRange = range;
					goal = *ladder->m_topForwardArea->GetCenter();

					if (ladder->m_topForwardArea->GetAttributes() & NAV_CROUCH)
					{
						Crouch();
					}
				}
			}
			if (ladder->m_topLeftArea != NULL)
			{
				range = (*departPos - *ladder->m_topLeftArea->GetCenter()).LengthSquared();

				if (closeRange > range)
				{
					goal = *ladder->m_topLeftArea->GetCenter();

					if (ladder->m_topLeftArea->GetAttributes() & NAV_CROUCH)
					{
						Crouch();
					}
				}
			}
			if (ladder->m_topRightArea != NULL)
			{
				range = (*departPos - *ladder->m_topRightArea->GetCenter()).LengthSquared();

				if (closeRange > range)
				{
					goal = *ladder->m_topRightArea->GetCenter();

					if (ladder->m_topRightArea->GetAttributes() & NAV_CROUCH)
					{
						Crouch();
					}
				}
			}
		}

		const float ladderRange = 20.0f;
		if ((GetFeet() - goal).Make2D().IsLengthLessThan(ladderRange))
		{
			return true;
		}
	}

	TrackPath(goal, deltaT);
	return false;
}

/* <477691> ../cstrike/dlls/hostage/hostage_improv.cpp:1214 */
void CHostageImprov::UpdatePosition(float deltaT)
{
	CNavArea *area = TheNavAreaGrid.GetNavArea(&m_hostage->pev->origin);

	if (area != NULL)
	{
		m_lastKnownArea = area;
	}

	DrawAxes(m_moveGoal, 255, 255, 0);

	if (IsJumping())
	{
		Vector dir;
		const float pushSpeed = 100.0f;

		if (!m_hasJumped)
		{
			m_hasJumped = true;
			m_hasJumpedIntoAir = false;
			m_hostage->pev->velocity.z += 300.0f;
		}
		else
			ResetJump();

		dir = m_jumpTarget - GetFeet();
		dir.z = 0;

		dir.NormalizeInPlace();

		m_hostage->pev->velocity.x = dir.x * pushSpeed;
		m_hostage->pev->velocity.y = dir.y * pushSpeed;

		m_hostage->SetBoneController(0);
		m_hostage->SetBoneController(1);

		FaceTowards(m_jumpTarget, deltaT);
		return;
	}

	if (m_isLookingAt)
	{
		Vector angles = UTIL_VecToAngles(m_viewGoal - GetEyes());
		float_precision pitch = angles.x - m_hostage->pev->angles.x;
		float_precision yaw = angles.y - m_hostage->pev->angles.y;

		while (yaw > 180.0f)
			yaw -= 360.0f;

		while (yaw < -180.0f)
			yaw += 360.0f;

		while (pitch > 180.0f)
			pitch -= 360.0f;

		while (pitch < -180.0f)
			pitch += 360.0f;

		m_hostage->SetBoneController(0, yaw);
		m_hostage->SetBoneController(1, -pitch);

		if (IsAtMoveGoal() && !HasFaceTo())
		{
			if (yaw < -45.0f || yaw > 45.0f)
			{
				FaceTowards(m_viewGoal, deltaT);
			}
		}
	}
	else
	{
		m_hostage->SetBoneController(0);
		m_hostage->SetBoneController(1);
	}

	if (HasFaceTo() && FaceTowards(m_faceGoal, deltaT))
		ClearFaceTo();

	if (!IsAtMoveGoal() || m_path.GetSegmentCount() > 0)
	{
		if (m_path.GetSegmentCount() <= 0)
		{
			HostagePathCost pathCost;
			if (m_path.Compute(&GetFeet(), &m_moveGoal, pathCost))
			{
				m_follower.SetPath(&m_path);
				m_follower.SetImprov(this);

				m_follower.Reset();
				m_follower.Debug(cv_hostage_debug.value > 0.0);
			}
		}

		m_follower.Update(deltaT, m_inhibitObstacleAvoidance.IsElapsed());

		if (m_moveType == Stopped)
		{
			m_follower.ResetStuck();
		}

		if (m_follower.IsStuck())
		{
			Wiggle();
		}
	}

	const float friction = 3.0f;

	m_vel.x += m_vel.x * -friction * deltaT;
	m_vel.y += m_vel.y * -friction * deltaT;

	float_precision speed = m_vel.NormalizeInPlace();

	const float maxSpeed = 285.0f;
	if (speed > maxSpeed)
	{
		speed = maxSpeed;
	}

	m_vel.x = m_vel.x * speed;
	m_vel.y = m_vel.y * speed;

	KeepPersonalSpace spacer(this);
	ForEachPlayer(spacer);

	if (g_pHostages != NULL)
	{
		g_pHostages->ForEachHostage(spacer);
	}

	m_hostage->pev->velocity.x = m_vel.x;
	m_hostage->pev->velocity.y = m_vel.y;

	m_moveFlags = 0;
}

/* <47837a> ../cstrike/dlls/hostage/hostage_improv.cpp:1384 */
void CHostageImprov::__MAKE_VHOOK(OnUpkeep)(float deltaT)
{
	if (IsAlive())
	{
		UpdatePosition(deltaT);
	}
}

/* <4749f9> ../cstrike/dlls/hostage/hostage_improv.cpp:1396 */
bool CHostageImprov::IsTerroristNearby()
{
	if (m_nearbyTerroristTimer.IsElapsed())
	{
		CheckForNearbyTerrorists();
		return m_isTerroristNearby;
	}

	return true;
}

/* <474ae7> ../cstrike/dlls/hostage/hostage_improv.cpp:1412 */
void CHostageImprov::CheckForNearbyTerrorists()
{
	if (!m_checkNearbyTerroristTimer.IsElapsed())
		return;

	const float checkInterval = 2.0f;
	m_checkNearbyTerroristTimer.Start(checkInterval);
	m_isTerroristNearby = false;

	float range;
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
void CHostageImprov::UpdateGrenadeReactions()
{
	if (m_coughTimer.IsElapsed())
	{
		if (TheBots->IsInsideSmokeCloud(&GetCentroid()))
		{
			m_coughTimer.Start(RANDOM_FLOAT(1, 3));
			Chatter(HOSTAGE_CHATTER_COUGH);
			Frighten(SCARED);
		}
	}

	if (m_grenadeTimer.IsElapsed())
	{
		CBaseEntity *entity = NULL;
		const float watchGrenadeRadius = 500.0f;

		m_grenadeTimer.Start(RANDOM_FLOAT(0.4, 0.6));

		while ((entity = UTIL_FindEntityInSphere(entity, GetCentroid(), watchGrenadeRadius)) != NULL)
		{
			CGrenade *grenade = static_cast<CGrenade *>(entity);

			if (!FClassnameIs(grenade->pev, "grenade") || grenade->m_SGSmoke > 1)
				continue;

			if (IsVisible(grenade->Center()))
			{
				Chatter(HOSTAGE_CHATTER_SAW_HE_GRENADE);

				if (grenade->pev->dmg > 50.0f)
				{
					m_idleState.OnInjury();
					Frighten(TERRIFIED);
				}
				else
					Frighten(SCARED);

				m_grenadeTimer.Start(10);
				break;
			}
		}
	}
}

/* <475ce3> ../cstrike/dlls/hostage/hostage_improv.cpp:1502 */
void CHostageImprov::__MAKE_VHOOK(OnUpdate)(float deltaT)
{
	if (!IsAlive() || cv_hostage_stop.value > 0.0f)
		return;

	if (m_blinkTimer.IsElapsed())
	{
		if (m_scaredTimer.IsElapsed() && m_animateState.GetPerformance() != HostageAnimateState::Afraid)
		{
			m_blinkTimer.Start(RANDOM_FLOAT(3, 10));
			m_blinkCounter = RANDOM_LONG(2, 4);
		}
		else
		{
			m_blinkTimer.Start(RANDOM_FLOAT(0.5, 2.0));
			m_blinkCounter = RANDOM_LONG(1, 2);

		}
	}

	if (m_blinkCounter)
	{
		m_hostage->pev->body = 1;
		--m_blinkCounter;
	}
	else
	{
		m_hostage->pev->body = 0;
	}

	UpdateGrenadeReactions();
	UpdateDelayedChatter();
	UpdateVision();

	m_behavior.Update();

	m_actualVel.x = m_hostage->pev->origin.x - m_lastPosition.x;
	m_actualVel.y = m_hostage->pev->origin.y - m_lastPosition.y;

	const float runSpeed = 289.0f;
	const float walkSpeed = 9.0f;
	const float fallVelocity = -1000.0f;
	const float safeTime = 0.4f;

	if (IsOnGround())
	{
		if (IsCrouching())
		{
			if (m_actualVel.LengthSquared() > 9.0f)
			{
				if (m_animateState.GetPerformance() != HostageAnimateState::CrouchWalk)
				{
					m_animateState.Reset();
					m_animateState.SetPerformance(HostageAnimateState::CrouchWalk);

					ClearLookAt();
					if (m_scaredTimer.IsElapsed() && m_animateState.GetPerformance() != HostageAnimateState::Afraid)
						m_animateState.AddSequence(this, ACT_CROUCH_WALK, 99.9, 2.0);
					else
						m_animateState.AddSequence(this, ACT_CROUCH_WALK_SCARED, 99.9, 2.0);
				}
			}
			else if (m_animateState.GetPerformance() != HostageAnimateState::Crouch)
			{
				m_animateState.Reset();
				m_animateState.SetPerformance(HostageAnimateState::Crouch);

				if (m_scaredTimer.IsElapsed())
					m_animateState.AddSequence(this, ACT_CROUCH_IDLE, 99.9);
				else
					m_animateState.AddSequence(this, ACT_CROUCH_IDLE_SCARED);
			}
		}
		else
		{
			UTIL_MakeVectors(m_hostage->pev->angles);

			float dot = DotProduct2D(gpGlobals->v_forward, m_actualVel);

			if (dot < -3.0f)
			{
				if (m_animateState.GetPerformance() != HostageAnimateState::Walk)
				{
					m_animateState.Reset();
					m_animateState.SetPerformance(HostageAnimateState::Walk);
					ClearLookAt();

					float speed;
					if (m_actualVel.LengthSquared() > runSpeed)
						speed = 2.0f;
					else
						speed = 1.0f;

					m_animateState.AddSequence(this, ACT_WALK_BACK, 99.9, speed);
				}
			}
			else
			{
				if (m_actualVel.LengthSquared() > runSpeed)
				{
					if (m_animateState.GetPerformance() != HostageAnimateState::Run)
					{
						m_animateState.Reset();
						m_animateState.SetPerformance(HostageAnimateState::Run);
						ClearLookAt();

						if (m_scaredTimer.IsElapsed() && m_animateState.GetPerformance() != HostageAnimateState::Afraid && !m_behavior.IsState(&m_escapeState))
							m_animateState.AddSequence(this, ACT_RUN, 99.9, 2.0);
						else
							m_animateState.AddSequence(this, ACT_RUN_SCARED, 99.9, 2.0);
					}
				}
				else if (m_actualVel.LengthSquared() > walkSpeed)
				{
					if (m_animateState.GetPerformance() != HostageAnimateState::Walk)
					{
						m_animateState.Reset();
						m_animateState.SetPerformance(HostageAnimateState::Walk);
						ClearLookAt();

						if (m_behavior.IsState(&m_escapeState))
						{
							m_animateState.AddSequence(this, ACT_WALK_SNEAKY, 99.9, 1.5);
						}
						else if (m_scaredTimer.IsElapsed() && m_animateState.GetPerformance() != HostageAnimateState::Afraid)
						{
							m_animateState.AddSequence(this, ACT_WALK, 99.9, 1.5);
						}
						else
							m_animateState.AddSequence(this, ACT_WALK_SCARED, 99.9, 1.5);
					}
				}
				else
				{
					if (m_animateState.GetPerformance() == HostageAnimateState::Walk || m_animateState.GetPerformance() == HostageAnimateState::Run)
						m_animateState.Reset();

					UpdateStationaryAnimation();
				}
			}
		}
	}
	else if (m_hostage->pev->velocity.z < fallVelocity && m_animateState.GetPerformance() != HostageAnimateState::Fall)
	{
		m_animateState.Reset();
		m_animateState.SetPerformance(HostageAnimateState::Fall);
		m_animateState.AddSequence(this, ACT_FALL, 99.9);
	}

	if (!m_collisionTimer.HasStarted() || m_collisionTimer.IsGreaterThen(safeTime))
		SetKnownGoodPosition(m_lastPosition);

	m_lastPosition = m_hostage->pev->origin;
	m_animateState.OnUpdate(this);
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
				m_idleState.OnInjury();
			}
		}
		break;
	case EVENT_HOSTAGE_RESCUED:
		if (m_hostage == other)
		{
			if (!entity)
				return;

			Chatter(HOSTAGE_CHATTER_RESCUED, false);
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

		for (double offset = 1.0f; offset <= 18.0f; offset += 3.0f)
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
				stepAhead.z = GetEyes().z;

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
bool CHostageImprov::IsAtHome() const
{
	return m_hostage->IsAtHome();
}

/* <474c76> ../cstrike/dlls/hostage/hostage_improv.cpp:2025 */
bool CHostageImprov::CanSeeRescueZone() const
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

	for (int i = 0; i < m_visiblePlayerCount; ++i)
	{
		CBasePlayer *player = (CBasePlayer *)m_visiblePlayer[i];

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
float CHostageImprov::GetTimeSinceLastInjury()
{
	return m_lastInjuryTimer.GetElapsedTime();
}

/* <474fb3> ../cstrike/dlls/hostage/hostage_improv.cpp:2107 */
float CHostageImprov::GetTimeSinceLastNoise()
{
	return m_lastNoiseTimer.GetElapsedTime();
}

/* <47503a> ../cstrike/dlls/hostage/hostage_improv.cpp:2117 */
bool CHostageImprov::IsScared() const
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
void CHostageImprov::Afraid()
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
void CHostageImprov::UpdateDelayedChatter()
{
	if (!m_isDelayedChatterPending)
		return;

	if (!m_delayedChatterTimer.IsElapsed())
		return;

	m_isDelayedChatterPending = false;

	switch (m_delayedChatterType)
	{
	case HOSTAGE_CHATTER_SCARED_OF_GUNFIRE:
		if (RANDOM_FLOAT(0, 100) <= 25)
		{
			Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		}
		break;
	case HOSTAGE_CHATTER_LOOK_OUT:
	case HOSTAGE_CHATTER_PLEASE_RESCUE_ME:
	case HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE:
		if (RANDOM_FLOAT(0, 100) <= 60)
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
void CHostageImprov::CrouchDie()
{
	m_animateState.Reset();
	m_animateState.AddSequence(this, ACT_CROUCH_DIE);
}

/* <476327> ../cstrike/dlls/hostage/hostage_improv.cpp:2339 */
void CHostageImprov::Agree()
{
	m_animateState.Reset();
	m_animateState.AddSequence(this, ACT_YES);
}

/* <476350> ../cstrike/dlls/hostage/hostage_improv.cpp:2349 */
void CHostageImprov::Disagree()
{
	if (m_animateState.GetPerformance() != HostageAnimateState::Disagreeing)
	{
		m_animateState.Reset();
		m_animateState.AddSequence(this, ACT_NO, -1.0, RANDOM_FLOAT(1.5, 3.0));
	}
}

/* <476395> ../cstrike/dlls/hostage/hostage_improv.cpp:2363 */
void CHostageImprov::Wave()
{
	m_animateState.Reset();
	m_animateState.SetPerformance(HostageAnimateState::Waving);
	m_animateState.AddSequence(this, ACT_WAVE);
}

// Invoked when an improv fails to reach a MoveTo goal

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
void CHostageImprov::Wiggle()
{
	// for wiggling
	if (m_wiggleTimer.IsElapsed())
	{
		m_wiggleDirection = static_cast<NavRelativeDirType>(RANDOM_LONG(FORWARD, LEFT));
		m_wiggleTimer.Start(RANDOM_FLOAT(0.3, 0.5));
	}

	const float force = 15.0f;
	Vector dir(BotCOS(m_moveAngle), BotSIN(m_moveAngle), 0.0f);
	Vector lat(-dir.y, dir.x, 0.0f);

	switch (m_wiggleDirection)
	{
	case FORWARD:
		ApplyForce(dir * force);
		break;
	case BACKWARD:
		ApplyForce(dir * -force);
		break;
	case LEFT:
		ApplyForce(lat * force);
		break;
	case RIGHT:
		ApplyForce(lat * -force);
		break;
	default:
		break;
	}

	const float minStuckJumpTime = 0.5f;
	if (m_follower.GetStuckDuration() > minStuckJumpTime && m_wiggleJumpTimer.IsElapsed())
	{
		if (Jump())
		{
			m_wiggleJumpTimer.Start(RANDOM_FLOAT(0.75f, 1.2f));
		}
	}
}

/* <4766cc> ../cstrike/dlls/hostage/hostage_improv.cpp:2438 */
void CHostageImprov::ClearPath()
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
void CHostageImprov::__MAKE_VHOOK(Crouch)()
{
	const float minCrouchTime = 1.0f;

	if (IsCrouching())
		return;

	m_isCrouching = true;
	m_minCrouchTimer.Start(minCrouchTime);
	UTIL_SetSize(m_hostage->pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_CROUCH);
}

/* <47195c> ../cstrike/dlls/hostage/hostage_improv.cpp:2516 */
void CHostageImprov::__MAKE_VHOOK(StandUp)()
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
void CHostageImprov::UpdateStationaryAnimation()
{
	m_behavior.UpdateStationaryAnimation(this);
}
