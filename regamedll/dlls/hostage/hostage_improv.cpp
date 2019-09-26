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

inline void DrawAxes(const Vector &origin, int red, int green, int blue)
{
	float size = 10;

	if (cv_hostage_debug.value != 1.0f)
		return;

	UTIL_DrawBeamPoints(origin - Vector(size, 0, 0), origin + Vector(size, 0, 0), 2, red, green, blue);
	UTIL_DrawBeamPoints(origin - Vector(0, size, 0), origin + Vector(0, size, 0), 2, red, green, blue);
	UTIL_DrawBeamPoints(origin + Vector(0, 0, size), origin - Vector(0, 0, size), 2, red, green, blue);
}

CHostageImprov::CHostageImprov(CBaseEntity *pEntity)
{
	m_animateState.Reset();
	m_hostage = static_cast<CHostage *>(pEntity);
	OnReset();
}

bool CHostageImprov::IsAlive() const
{
	return m_hostage->pev->deadflag != DEAD_DEAD;
}

void CHostageImprov::MoveTo(const Vector &goal)
{
	m_moveGoal = goal;
	m_path.Invalidate();

	if (m_hasKnownGoodPos)
		return;

	m_hasKnownGoodPos = true;
	SetKnownGoodPosition(GetFeet());
}

// Find "simple" ground height, treating current nav area as part of the floor
bool CHostageImprov::GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal)
{
	if (GetSimpleGroundHeight(pos, height, normal))
	{
		// our current nav area also serves as a ground polygon
		if (m_lastKnownArea && m_lastKnownArea->IsOverlapping(pos))
			*height = Q_max((*height), m_lastKnownArea->GetZ(pos));

		return true;
	}

	return false;
}

// Check if we need to jump due to height change
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

void CHostageImprov::LookAt(const Vector &target)
{
	m_isLookingAt = true;
	m_viewGoal = target;
}

void CHostageImprov::ClearLookAt()
{
	m_isLookingAt = false;
}

void CHostageImprov::FaceTo(const Vector &goal)
{
	m_isFacingTo = true;
	m_faceGoal = goal;
}

void CHostageImprov::ClearFaceTo()
{
	m_isFacingTo = false;
}

void CHostageImprov::MoveTowards(const Vector &pos, float deltaT)
{
	Vector move;
	real_t accelRate;
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

	if ((!m_lastKnownArea || !(m_lastKnownArea->GetAttributes() & NAV_NO_JUMP))
		&& !IsUsingLadder() && !IsJumping() && IsOnGround() && !IsCrouching())
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

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground, &normal))
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

bool CHostageImprov::FaceTowards(const Vector &target, float deltaT)
{
	bool bError = false;
	Vector2D to = (target - GetFeet()).Make2D();

#ifndef PLAY_GAMEDLL
	to.NormalizeInPlace();
#else
	// TODO: fix test demo
	real_t float_x = target.x - GetFeet().x;
	real_t float_y = target.y - GetFeet().y;
	real_t flLen = to.Length();

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
#endif

	float moveAngle = GetMoveAngle();

	Vector2D lat(BotCOS(moveAngle), BotSIN(moveAngle));
	Vector2D dir(-lat.y, lat.x);

	real_t dot = DotProduct(to, dir);

	if (DotProduct(to, lat) < 0.0f)
	{
		if (dot >= 0.0f)
			dot = 1.0f;
		else
			dot = -1.0f;

		bError = true;
	}

	const float maxTurnRate = 0.05f;

	if (bError || Q_fabs(dot) >= maxTurnRate)
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

void CHostageImprov::FaceOutwards()
{
	TraceResult result;
	Vector to;
	float farthestRange = 0.0f;
	int farthest = 0;

	static Vector corner[] =
	{
		Vector(-1000,  1000, 0),
		Vector( 1000,  1000, 0),
		Vector(-1000, -1000, 0),
		Vector( 1000, -1000, 0)
	};

	const int cornerCount = ARRAYSIZE(corner);

	for (int i = 0; i < cornerCount; i++)
	{
		to = GetCentroid() + corner[i];

		UTIL_TraceLine(GetCentroid(), to, ignore_monsters, ignore_glass, m_hostage->edict(), &result);

		real_t range = (result.vecEndPos - GetCentroid()).LengthSquared();

		if (range > farthestRange)
		{
			farthestRange = range;
			farthest = i;
		}
	}

	to = GetCentroid() + corner[farthest];
	FaceTo(to);
}

bool CHostageImprov::IsAtMoveGoal(float error) const
{
	return (GetFeet() - m_moveGoal).IsLengthLessThan(error);
}

bool CHostageImprov::IsAtFaceGoal() const
{
	return false;
}

// Return true if a friend is between us and the given position
bool CHostageImprov::IsFriendInTheWay(const Vector &goalPos) const
{
	// do this check less often to ease CPU burden
	if (!m_avoidFriendTimer.IsElapsed())
	{
		return m_isFriendInTheWay;
	}

	const float avoidFriendInterval = 0.5f;
	m_avoidFriendTimer.Start(avoidFriendInterval);

	CheckWayFunctor check(this, goalPos);

	if (g_pHostages)
	{
		g_pHostages->ForEachHostage(check);

		if (check.m_blocker)
		{
			return m_isFriendInTheWay = true;
		}
	}

	// check if any CT are overlapping this linear path
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!pPlayer)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (!pPlayer->IsAlive() || pPlayer->m_iTeam == TERRORIST)
			continue;

		if (IsFriendInTheWay(pPlayer, goalPos))
		{
			m_isFriendInTheWay = true;
			break;
		}
	}

	return m_isFriendInTheWay;
}

// Return true if a friend is between us and the given entity
bool CHostageImprov::IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const
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
		if (DotProduct(myFriend->pev->velocity, m_hostage->pev->velocity) >= 0.0f)
			return false;
	}

	// friend is in our personal space and overlaps our intended line of movement
	return true;
}

bool CHostageImprov::IsFriendInTheWay() const
{
	CheckAhead check(this);
	g_pHostages->ForEachHostage(check);
	ForEachPlayer(check);

	return check.IsBlocked();
}

float CHostageImprov::GetSpeed()
{
	return -1.0f;
}

bool CHostageImprov::Jump()
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

void CHostageImprov::Run()
{
	m_moveType = m_moveLimit;
}

void CHostageImprov::Walk()
{
	m_moveType = (m_moveLimit > Walking) ? Walking : m_moveLimit;
}

void CHostageImprov::Stop()
{
	MoveTo(GetFeet());
	m_hostage->pev->velocity = Vector(0, 0, 0);

	if (m_moveLimit > Stopped)
		m_moveType = Stopped;
	else
		m_moveType = m_moveLimit;
}

const Vector &CHostageImprov::GetFeet() const
{
	return m_hostage->pev->origin;
}

const Vector &CHostageImprov::GetCentroid() const
{
	m_centroid = m_hostage->pev->origin + Vector(0, 0, HalfHumanHeight);
	return m_centroid;
}

const Vector &CHostageImprov::GetEyes() const
{
	m_eye = m_hostage->pev->origin + Vector(0, 0, HumanHeight) - Vector(0, 0, 7);
	return m_eye;
}

bool CHostageImprov::IsOnGround() const
{
	return (m_hostage->pev->flags & FL_ONGROUND) != 0;
}

bool CHostageImprov::IsMoving() const
{
	float const epsilon = 10.0f;
	return m_actualVel.IsLengthGreaterThan(epsilon);
}

bool CHostageImprov::IsVisible(const Vector &pos, bool testFOV) const
{
	const Vector eye = GetEyes();
	TraceResult result;

	UTIL_TraceLine(eye, pos, ignore_monsters, ignore_glass, m_hostage->edict(), &result);
	return result.flFraction == 1.0f;
}

bool CHostageImprov::IsPlayerLookingAtMe(CBasePlayer *pOther, float cosTolerance) const
{
	Vector2D toOther = (pOther->pev->origin - GetCentroid()).Make2D();
	toOther.NormalizeInPlace();

	UTIL_MakeVectors(pOther->pev->punchangle + pOther->pev->v_angle);

	Vector2D otherDir = gpGlobals->v_forward.Make2D();
	otherDir.NormalizeInPlace();

	if (-cosTolerance > DotProduct(toOther, otherDir))
	{
		if (IsVisible(pOther->EyePosition()))
		{
			return true;
		}
	}

	return false;
}

CBasePlayer *CHostageImprov::IsAnyPlayerLookingAtMe(int team, float cosTolerance) const
{
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!IsEntityValid(pPlayer))
			continue;

		if (pPlayer->IsAlive() && (team == UNASSIGNED || pPlayer->m_iTeam == team))
		{
			if (IsPlayerLookingAtMe(pPlayer, cosTolerance))
			{
				return pPlayer;
			}
		}
	}

	return nullptr;
}

CBasePlayer *CHostageImprov::GetClosestPlayerByTravelDistance(int team, float *range) const
{
	CBasePlayer *close = nullptr;
	float closeRange = 9.9999998e10f;

	if (!GetLastKnownArea())
		return nullptr;

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!IsEntityValid(pPlayer))
			continue;

		if (pPlayer->IsAlive() && (team == UNASSIGNED || pPlayer->m_iTeam == team))
		{
			ShortestPathCost cost;
			Vector vecCenter = pPlayer->Center();

			real_t range = NavAreaTravelDistance(GetLastKnownArea(), TheNavAreaGrid.GetNearestNavArea(&vecCenter), cost);

			if (range > 0 && range < closeRange)
			{
				closeRange = range;
				close = pPlayer;
			}
		}
	}

	if (range)
		*range = closeRange;

	return close;
}

void CHostageImprov::OnReset()
{
	m_moveFlags = 0;
	m_moveType = Stopped;
	m_moveLimit = Running;

	m_vel.x = 0;
	m_vel.y = 0;

	m_actualVel = Vector(0, 0, 0);
	m_checkNearbyTerroristTimer.Invalidate();

	m_lastKnownArea = nullptr;
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

void CHostageImprov::UpdateVision()
{
	if (!m_visionTimer.IsElapsed())
		return;

	m_visiblePlayerCount = 0;

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!pPlayer)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (FStrEq(STRING(pPlayer->pev->netname), ""))
			continue;

		if (pPlayer->IsAlive() && IsVisible(pPlayer->pev->origin, true))
		{
			m_visiblePlayer[m_visiblePlayerCount] = pPlayer;

			if (pPlayer->m_iTeam == TERRORIST)
				m_lastSawT.Start();
			else
				m_lastSawCT.Start();

			if (++m_visiblePlayerCount == ARRAYSIZE(m_visiblePlayer))
				break;
		}
	}

	m_visionTimer.Start(RANDOM_FLOAT(0.4f, 0.6f));
}

void CHostageImprov::TrackPath(const Vector &pathGoal, float deltaT)
{
	FaceTowards(pathGoal, deltaT);
	MoveTowards(pathGoal, deltaT);

	m_jumpTarget = pathGoal;
	DrawAxes(pathGoal, 255, 0, 255);
}

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

void CHostageImprov::StartLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos)
{
	m_traversingLadder = true;
}

bool CHostageImprov::TraverseLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT)
{
	Vector goal;

	if (how == GO_LADDER_DOWN)
	{
		goal = ladder->m_bottom;
		AddDirectionVector(&goal, ladder->m_dir, 16);

		if (ladder->m_top.z - HalfHumanHeight > GetFeet().z)
		{
			const float atGoalRange = 50.0f;
			if ((GetFeet() - goal).Make2D().IsLengthLessThan(atGoalRange))
			{
				m_hostage->pev->velocity.z = -100.0f;
			}
		}

		if (ladder->m_bottom.z + HalfHumanHeight > GetFeet().z)
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
		if (departPos)
		{
			float closeRange = 1e6;
			float range;

			if (ladder->m_topForwardArea)
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
			if (ladder->m_topLeftArea)
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
			if (ladder->m_topRightArea)
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

void CHostageImprov::UpdatePosition(float deltaT)
{
	CNavArea *area = TheNavAreaGrid.GetNavArea(&m_hostage->pev->origin);

	if (area)
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

#ifndef PLAY_GAMEDLL
		// TODO: fix test demo
		dir.NormalizeInPlace();

		m_hostage->pev->velocity.x = dir.x * pushSpeed;
		m_hostage->pev->velocity.y = dir.y * pushSpeed;
#else
		Vector vecRet = NormalizeMulScalar<real_t, real_t, real_t, float>(dir, pushSpeed);
		m_hostage->pev->velocity.x = vecRet.x;
		m_hostage->pev->velocity.y = vecRet.y;
#endif

		m_hostage->SetBoneController(0);
		m_hostage->SetBoneController(1);

		FaceTowards(m_jumpTarget, deltaT);
		return;
	}

	if (m_isLookingAt)
	{
		Vector angles = UTIL_VecToAngles(m_viewGoal - GetEyes());
		real_t pitch = angles.x - m_hostage->pev->angles.x;
		real_t yaw = angles.y - m_hostage->pev->angles.y;

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

	real_t speed = m_vel.NormalizeInPlace();

	const float maxSpeed = 285.0f;
	if (speed > maxSpeed)
	{
		speed = maxSpeed;
	}

	m_vel.x = m_vel.x * speed;
	m_vel.y = m_vel.y * speed;

	KeepPersonalSpace spacer(this);
	ForEachPlayer(spacer);

	if (g_pHostages)
	{
		g_pHostages->ForEachHostage(spacer);
	}

	m_hostage->pev->velocity.x = m_vel.x;
	m_hostage->pev->velocity.y = m_vel.y;

	m_moveFlags = 0;
}

void CHostageImprov::OnUpkeep(float deltaT)
{
	if (IsAlive())
	{
		UpdatePosition(deltaT);
	}
}

bool CHostageImprov::IsTerroristNearby()
{
	if (m_nearbyTerroristTimer.IsElapsed())
	{
		CheckForNearbyTerrorists();
		return m_isTerroristNearby;
	}

	return true;
}

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
		CGrenade *pGrenade = nullptr;
		const float watchGrenadeRadius = 500.0f;

		m_grenadeTimer.Start(RANDOM_FLOAT(0.4f, 0.6f));

		while ((pGrenade = UTIL_FindEntityInSphere(pGrenade, GetCentroid(), watchGrenadeRadius)))
		{
			if (!FClassnameIs(pGrenade->pev, "grenade") || pGrenade->m_SGSmoke > 1)
				continue;

			if (IsVisible(pGrenade->Center()))
			{
				Chatter(HOSTAGE_CHATTER_SAW_HE_GRENADE);

				if (pGrenade->pev->dmg > 50.0f)
				{
					m_idleState.OnInjury();
					Frighten(TERRIFIED);
				}
				else
				{
					Frighten(SCARED);
				}

				m_grenadeTimer.Start(10);
				break;
			}
		}
	}
}

void CHostageImprov::OnUpdate(float deltaT)
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
			m_blinkTimer.Start(RANDOM_FLOAT(0.5f, 2.0f));
			m_blinkCounter = RANDOM_LONG(1, 2);

		}
	}

	if (m_blinkCounter)
	{
		m_hostage->pev->body = 1;
		m_blinkCounter--;
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

void CHostageImprov::OnGameEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	switch (event)
	{
	case EVENT_BULLET_IMPACT:
	{
		Vector *impactPos = (Vector *)pOther;
		const float nearRange = 100.0f;

		if ((GetCentroid() - *impactPos).IsLengthLessThan(nearRange))
		{
			Frighten(TERRIFIED);
		}
		break;
	}
	case EVENT_PLAYER_DIED:
	case EVENT_HOSTAGE_KILLED:
		if (IsVisible(pEntity->pev->origin, true))
		{
			Frighten(TERRIFIED);

			if (!pEntity->IsPlayer() || (pEntity->IsPlayer() && ((CBasePlayer *)pEntity)->m_iTeam != TERRORIST))
			{
				DelayedChatter(RANDOM_FLOAT(0.5f, 0.7f), HOSTAGE_CHATTER_SCARED_OF_MURDER, true);
			}
			if (!pEntity->IsPlayer())
			{
				m_idleState.OnInjury();
			}
		}
		break;
	case EVENT_HOSTAGE_RESCUED:
		if (m_hostage == pOther)
		{
			if (!pEntity)
				return;

			Chatter(HOSTAGE_CHATTER_RESCUED, false);
		}
		break;
	case EVENT_TERRORISTS_WIN:
		Frighten(SCARED);
		m_isDelayedChatterPending = false;
		DelayedChatter(RANDOM_FLOAT(1.0f, 4.0f), HOSTAGE_CHATTER_TERRORISTS_WIN);
		return;
	case EVENT_CTS_WIN:
		m_scaredTimer.Invalidate();
		m_isDelayedChatterPending = false;
		DelayedChatter(RANDOM_FLOAT(1.0f, 4.0f), HOSTAGE_CHATTER_CTS_WIN);
		return;
	}

	float range;
	PriorityType priority;
	bool isHostile;

	if (pEntity && IsGameEventAudible(event, pEntity, pOther, &range, &priority, &isHostile))
	{
		const float fudge = 0.4f;

		if ((m_hostage->pev->origin - pEntity->pev->origin).IsLengthLessThan(range * fudge))
		{
			m_lastNoiseTimer.Start();

			if (isHostile)
			{
				Frighten(SCARED);

				switch (event)
				{
				case EVENT_WEAPON_FIRED:
				{
					DelayedChatter(RANDOM_FLOAT(0.3f, 1.0f), HOSTAGE_CHATTER_SCARED_OF_GUNFIRE);
					break;
				}
				case EVENT_HE_GRENADE_EXPLODED:
				case EVENT_SMOKE_GRENADE_EXPLODED:
				case EVENT_BREAK_GLASS:
				case EVENT_BREAK_WOOD:
				case EVENT_BREAK_METAL:
				case EVENT_BREAK_FLESH:
				case EVENT_BREAK_CONCRETE:
					DelayedChatter(RANDOM_FLOAT(0.3f, 1.0f), HOSTAGE_CHATTER_LOOK_OUT);
					break;

				default:
					break;
				}
			}
		}
	}

	if (event == EVENT_FLASHBANG_GRENADE_EXPLODED)
	{
		Vector *impactPos = (Vector *)pOther;
		const float flashRange = 1000.0f;

		if ((GetEyes() - *impactPos).IsLengthLessThan(flashRange) && IsVisible(*impactPos))
		{
			DelayedChatter(RANDOM_FLOAT(0.0f, 1.0f), HOSTAGE_CHATTER_BLINDED, true);
			Frighten(TERRIFIED);
		}
	}
}

void CHostageImprov::OnTouch(CBaseEntity *pOther)
{
	Vector2D to;
	const float pushForce = 20.0f;

	if (cv_hostage_debug.value != 0.0)
	{
		CONSOLE_ECHO("%5.1f: Hostage hit '%s'\n", gpGlobals->time, pOther->GetClassname());
	}

	m_collisionTimer.Start();

	if (FStrEq(pOther->pev->classname, "worldspawn"))
	{
		const float lookAheadRange = 30.0f;
		float ground;
		Vector normal(0, 0, 1);
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

		for (real_t offset = 1.0f; offset <= 18.0f; offset += 3.0f)
		{
			Vector vecStart = GetFeet();
			vecStart.z += offset;

			UTIL_TraceLine(vecStart, vecStart + pos, ignore_monsters, dont_ignore_glass, m_hostage->pev->pContainingEntity, &result);

			if (result.flFraction < 1.0f && result.vecPlaneNormal.z < MaxUnitZSlope)
			{
				isStep = true;
				break;
			}
		}

		if (isStep)
		{
			float stepAheadGround = pos.z;
			Vector stepAheadNormal(0, 0, stepAheadGround);

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
	else if (FStrEq(pOther->pev->classname, "func_breakable"))
	{
		pOther->TakeDamage(m_hostage->pev, m_hostage->pev, 9999.9, DMG_BULLET);
	}
	else if (pOther->IsPlayer() || FClassnameIs(pOther->pev, "hostage_entity"))
	{
		to = (m_hostage->pev->origin - pOther->pev->origin).Make2D();
		to.NormalizeInPlace();

		m_vel.x += to.x * pushForce;
		m_vel.y += to.y * pushForce;
	}
}

void CHostageImprov::ApplyForce(Vector force)
{
	m_vel.x += force.x;
	m_vel.y += force.y;
}

bool CHostageImprov::IsAtHome() const
{
	return m_hostage->IsAtHome();
}

bool CHostageImprov::CanSeeRescueZone() const
{
	if (!TheCSBots())
		return false;

	const CCSBotManager::Zone *zone = TheCSBots()->GetClosestZone(&GetCentroid());

	if (zone)
		return IsVisible(zone->m_center);

	return false;
}

CBasePlayer *CHostageImprov::GetClosestVisiblePlayer(int team)
{
	CBasePlayer *close = nullptr;
	float closeRangeSq = 1e8f;

	for (int i = 0; i < m_visiblePlayerCount; i++)
	{
		CBasePlayer *pPlayer = m_visiblePlayer[i];

		if (!pPlayer || (team > 0 && pPlayer->m_iTeam != team))
			continue;

		real_t rangeSq = (GetCentroid() - pPlayer->pev->origin).LengthSquared();

		if (rangeSq < closeRangeSq)
		{
			closeRangeSq = rangeSq;
			close = pPlayer;
		}
	}

	return close;
}

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

float CHostageImprov::GetTimeSinceLastInjury()
{
	return m_lastInjuryTimer.GetElapsedTime();
}

float CHostageImprov::GetTimeSinceLastNoise()
{
	return m_lastNoiseTimer.GetElapsedTime();
}

bool CHostageImprov::IsScared() const
{
	if (m_scaredTimer.IsElapsed())
	{
		return m_animateState.GetPerformance() == HostageAnimateState::Afraid;
	}

	return true;
}

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

void CHostageImprov::UpdateIdleActivity(Activity activity, Activity fidget)
{
	if (m_animateState.IsBusy())
		return;

	m_animateState.Reset();

	if (m_didFidget || fidget == ACT_RESET)
	{
		m_animateState.AddSequence(this, activity, RANDOM_FLOAT(1, 10), RANDOM_FLOAT(0.9f, 1.1f));
		m_didFidget = false;

	}
	else
	{
		m_animateState.AddSequence(this, fidget, -1, RANDOM_FLOAT(0.9f, 1.5f));
		m_didFidget = true;

	}
}

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
		if (RANDOM_FLOAT(0, 100) <= 25.0f)
		{
			Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		}
		break;
	case HOSTAGE_CHATTER_LOOK_OUT:
	case HOSTAGE_CHATTER_PLEASE_RESCUE_ME:
	case HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE:
		if (RANDOM_FLOAT(0, 100) <= 60.0f)
		{
			Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		}
		break;
	default:
		Chatter(m_delayedChatterType, m_delayedChatterMustSpeak);
		break;
	}
}

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

void CHostageImprov::CrouchDie()
{
	m_animateState.Reset();
	m_animateState.AddSequence(this, ACT_CROUCH_DIE);
}

void CHostageImprov::Agree()
{
	m_animateState.Reset();
	m_animateState.AddSequence(this, ACT_YES);
}

void CHostageImprov::Disagree()
{
	if (m_animateState.GetPerformance() != HostageAnimateState::Disagreeing)
	{
		m_animateState.Reset();
		m_animateState.AddSequence(this, ACT_NO, -1.0, RANDOM_FLOAT(1.5f, 3.0f));
	}
}

void CHostageImprov::Wave()
{
	m_animateState.Reset();
	m_animateState.SetPerformance(HostageAnimateState::Waving);
	m_animateState.AddSequence(this, ACT_WAVE);
}

// Invoked when an improv fails to reach a MoveTo goal
void CHostageImprov::OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
{
	m_behavior.OnMoveToFailure(goal, reason);

	if (reason == FAIL_STUCK)
	{
		ResetToKnownGoodPosition();
	}
}

void CHostageImprov::Wiggle()
{
	// for wiggling
	if (m_wiggleTimer.IsElapsed())
	{
		m_wiggleDirection = static_cast<NavRelativeDirType>(RANDOM_LONG(FORWARD, LEFT));
		m_wiggleTimer.Start(RANDOM_FLOAT(0.3f, 0.5f));
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

void CHostageImprov::ClearPath()
{
	Vector start;
	Vector end;
	TraceResult result;

	if (!m_clearPathTimer.IsElapsed())
		return;

	m_clearPathTimer.Start(RANDOM_FLOAT(0.3f, 0.5f));

	const Vector eye = GetEyes();
	start = eye;

	UTIL_MakeVectors(m_hostage->pev->angles);
	end = gpGlobals->v_forward * 64 + start;

	UTIL_TraceLine(start, end, ignore_monsters, dont_ignore_glass, m_hostage->edict(), &result);

	if (result.flFraction == 1.0f)
		return;

	if (result.pHit)
	{
		edict_t *pEntity = result.pHit;
		if (FClassnameIs(pEntity, "func_door") || FClassnameIs(pEntity, "func_door_rotating"))
		{
			CBaseEntity *pObject = CBaseEntity::Instance(pEntity);
			if (pObject)
			{
				pObject->Touch(m_hostage);
			}
		}
		else if (FClassnameIs(pEntity, "func_breakable") && pEntity->v.takedamage == DAMAGE_YES)
		{
			CBaseEntity *pObject = CBaseEntity::Instance(pEntity);
			if (pObject)
			{
				pObject->TakeDamage(m_hostage->pev, m_hostage->pev, 9999.9, DMG_BULLET);
			}
		}
	}
}

void CHostageImprov::Crouch()
{
	const float minCrouchTime = 1.0f;

	if (IsCrouching())
		return;

	m_isCrouching = true;
	m_minCrouchTimer.Start(minCrouchTime);
	UTIL_SetSize(m_hostage->pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_CROUCH);
}

void CHostageImprov::StandUp()
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

	// HalfHumanHeight
	if (y == 36)
	{
		m_animateState.Reset();
		UTIL_SetSize(m_hostage->pev, Vector(-10, -10, 0), Vector(10, 10, 62));
		m_isCrouching = false;
	}
}

void CHostageImprov::UpdateStationaryAnimation()
{
	m_behavior.UpdateStationaryAnimation(this);
}
