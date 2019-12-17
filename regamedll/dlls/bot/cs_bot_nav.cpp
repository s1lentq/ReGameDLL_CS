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

// Reset the stuck-checker.
void CCSBot::ResetStuckMonitor()
{
	if (m_isStuck)
	{
		if (IsLocalPlayerWatchingMe() && cv_bot_debug.value > 0.0f)
		{
			EMIT_SOUND(edict(), CHAN_ITEM, "buttons/bell1.wav", VOL_NORM, ATTN_NORM);
		}
	}

	m_isStuck = false;
	m_stuckTimestamp = 0.0f;
	m_stuckJumpTimestamp = 0.0f;

	m_avgVelIndex = 0;
	m_avgVelCount = 0;

	m_areaEnteredTimestamp = gpGlobals->time;
}

// Test if we have become stuck
void CCSBot::StuckCheck()
{
	if (m_isStuck)
	{
		// we are stuck - see if we have moved far enough to be considered unstuck
		Vector delta = pev->origin - m_stuckSpot;

		const float unstuckRange = 75.0f;
		if (delta.IsLengthGreaterThan(unstuckRange))
		{
			// we are no longer stuck
			ResetStuckMonitor();
			PrintIfWatched("UN-STUCK\n");
		}
	}
	else
	{
		// check if we are stuck
		// compute average velocity over a short period (for stuck check)
		Vector vel = pev->origin - m_lastOrigin;

		// if we are jumping, ignore Z
		if (IsJumping())
			vel.z = 0.0f;

		// cannot be Length2D, or will break ladder movement (they are only Z)
		float moveDist = vel.Length();
		float deltaT = g_flBotFullThinkInterval;

		m_avgVel[m_avgVelIndex++] = moveDist / deltaT;

		if (m_avgVelIndex == MAX_VEL_SAMPLES)
			m_avgVelIndex = 0;

		if (m_avgVelCount < MAX_VEL_SAMPLES)
		{
			m_avgVelCount++;
		}
		else
		{
			// we have enough samples to know if we're stuck
			float avgVel = 0.0f;
			for (int t = 0; t < m_avgVelCount; t++)
				avgVel += m_avgVel[t];

			avgVel /= m_avgVelCount;

			// cannot make this velocity too high, or bots will get "stuck" when going down ladders
			float stuckVel = (IsUsingLadder()) ? 10.0f : 20.0f;

			if (avgVel < stuckVel)
			{
				// we are stuck - note when and where we initially become stuck
				m_stuckTimestamp = gpGlobals->time;
				m_stuckSpot = pev->origin;
				m_stuckJumpTimestamp = gpGlobals->time + RANDOM_FLOAT(0.0f, 0.5f);

				PrintIfWatched("STUCK\n");
				if (IsLocalPlayerWatchingMe() && cv_bot_debug.value > 0.0f)
				{
					EMIT_SOUND(ENT(pev), CHAN_ITEM, "buttons/button11.wav", VOL_NORM, ATTN_NORM);
				}

				m_isStuck = true;
			}
		}
	}

	// always need to track this
	m_lastOrigin = pev->origin;
}

// Check if we need to jump due to height change
bool CCSBot::DiscontinuityJump(float ground, bool onlyJumpDown, bool mustJump)
{
	// don't try to jump again.
	if (m_isJumpCrouching)
		return false;

	real_t dz = ground - GetFeetZ();

	if (dz > StepHeight && !onlyJumpDown)
	{
		// dont restrict jump time when going up
		if (Jump(MUST_JUMP))
		{
			m_isJumpCrouching = true;
			m_isJumpCrouched = false;

			StandUp();

			m_jumpCrouchTimestamp = gpGlobals->time;
			return true;
		}
	}
	else if (!IsUsingLadder() && dz < -JumpHeight)
	{
		if (Jump(mustJump))
		{
			m_isJumpCrouching = true;
			m_isJumpCrouched = false;

			StandUp();

			m_jumpCrouchTimestamp = gpGlobals->time;
			return true;
		}
	}

	return false;
}

// Find "simple" ground height, treating current nav area as part of the floor
bool CCSBot::GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal)
{
	if (GetSimpleGroundHeight(pos, height, normal))
	{
		// our current nav area also serves as a ground polygon
		if (m_lastKnownArea && m_lastKnownArea->IsOverlapping(pos))
		{
			*height = Q_max((*height), m_lastKnownArea->GetZ(pos));
		}

		return true;
	}

	return false;
}

Place CCSBot::GetPlace() const
{
	if (m_lastKnownArea)
	{
		return m_lastKnownArea->GetPlace();
	}

	return UNDEFINED_PLACE;
}

void CCSBot::MoveTowardsPosition(const Vector *pos)
{
	// Jump up on ledges
	// Because we may not be able to get to our goal position and enter the next
	// area because our extent collides with a nearby vertical ledge, make sure
	// we look far enough ahead to avoid this situation.
	// Can't look too far ahead, or bots will try to jump up slopes.

	// NOTE: We need to do this frequently to catch edges at the right time
	// TODO: Look ahead *along path* instead of straight line
	if ((!m_lastKnownArea || !(m_lastKnownArea->GetAttributes() & NAV_NO_JUMP))
		&& !IsOnLadder() && !m_isJumpCrouching)
	{
		float ground;
		Vector aheadRay(pos->x - pev->origin.x, pos->y - pev->origin.y, 0);
		aheadRay.NormalizeInPlace();

		// look far ahead to allow us to smoothly jump over gaps, ledges, etc
		// only jump if ground is flat at lookahead spot to avoid jumping up slopes
		bool jumped = false;

		if (IsRunning())
		{
			const float farLookAheadRange = 80.0f;
			Vector normal;
			Vector stepAhead = pev->origin + farLookAheadRange * aheadRay;
			stepAhead.z += HalfHumanHeight;

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground, &normal))
			{
				if (normal.z > 0.9f)
					jumped = DiscontinuityJump(ground, ONLY_JUMP_DOWN);
			}
		}

		if (!jumped)
		{
			// close up jumping
			// cant be less or will miss jumps over low walls
			const float lookAheadRange = 30.0f;
			Vector stepAhead = pev->origin + lookAheadRange * aheadRay;
			stepAhead.z += HalfHumanHeight;

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground))
			{
				jumped = DiscontinuityJump(ground);
			}
		}

		if (!jumped)
		{
			// about to fall gap-jumping
			const float lookAheadRange = 10.0f;
			Vector stepAhead = pev->origin + lookAheadRange * aheadRay;
			stepAhead.z += HalfHumanHeight;

			if (GetSimpleGroundHeightWithFloor(&stepAhead, &ground))
			{
				jumped = DiscontinuityJump(ground, ONLY_JUMP_DOWN, MUST_JUMP);
			}
		}
	}

	// compute our current forward and lateral vectors
	float angle = pev->v_angle.y;

	Vector2D dir(BotCOS(angle), BotSIN(angle));
	Vector2D lat(-dir.y, dir.x);

	// compute unit vector to goal position
	Vector2D to(pos->x - pev->origin.x, pos->y - pev->origin.y);
	to.NormalizeInPlace();

	// move towards the position independant of our view direction
	float toProj = to.x * dir.x + to.y * dir.y;
	float latProj = to.x * lat.x + to.y * lat.y;

	const float c = 0.25f;
	if (toProj > c)
		MoveForward();
	else if (toProj < -c)
		MoveBackward();

	// if we are avoiding someone via strafing, don't override
	if (m_avoid)
		return;

	if (latProj >= c)
		StrafeLeft();
	else if (latProj <= -c)
		StrafeRight();
}

// Move away from position, independant of view angle
NOXREF void CCSBot::MoveAwayFromPosition(const Vector *pos)
{
	// compute our current forward and lateral vectors
	float angle = pev->v_angle[YAW];

	Vector2D dir(BotCOS(angle), BotSIN(angle));
	Vector2D lat(-dir.y, dir.x);

	// compute unit vector to goal position
	Vector2D to(pos->x - pev->origin.x, pos->y - pev->origin.y);
	to.NormalizeInPlace();

	// move away from the position independant of our view direction
	float toProj = to.x * dir.x + to.y * dir.y;
	float latProj = to.x * lat.x + to.y * lat.y;

	const float c = 0.5f;
	if (toProj > c)
		MoveBackward();
	else if (toProj < -c)
		MoveForward();

	if (latProj >= c)
		StrafeRight();
	else if (latProj <= -c)
		StrafeLeft();
}

// Strafe (sidestep) away from position, independant of view angle
void CCSBot::StrafeAwayFromPosition(const Vector *pos)
{
	// compute our current forward and lateral vectors
	float angle = pev->v_angle[YAW];

	Vector2D dir(BotCOS(angle), BotSIN(angle));
	Vector2D lat(-dir.y, dir.x);

	// compute unit vector to goal position
	Vector2D to(pos->x - pev->origin.x, pos->y - pev->origin.y);
	to.NormalizeInPlace();

	// move away from the position independant of our view direction
	float toProj = to.x * dir.x + to.y * dir.y;
	float latProj = to.x * lat.x + to.y * lat.y;

#ifdef REGAMEDLL_FIXES
	const float c = 0.5f;
	if (toProj > c)
		MoveBackward();
	else if (toProj < -c)
		MoveForward();

	if (latProj >= c)
		StrafeRight();
	else if (latProj <= -c)
		StrafeLeft();
#else
	if (latProj >= 0.0f)
		StrafeRight();
	else
		StrafeLeft();
#endif
}

// For getting un-stuck
void CCSBot::Wiggle()
{
	if (IsCrouching())
	{
		ResetStuckMonitor();
		return;
	}

	// for wiggling
	if (gpGlobals->time >= m_wiggleTimestamp)
	{
		m_wiggleDirection = (NavRelativeDirType)RANDOM_LONG(0, 3);
		m_wiggleTimestamp = RANDOM_FLOAT(0.5, 1.5) + gpGlobals->time;
	}

	// TODO: implement checking of the movement to fall down
	switch (m_wiggleDirection)
	{
	case LEFT:
		StrafeLeft();
		break;
	case RIGHT:
		StrafeRight();
		break;
	case FORWARD:
		MoveForward();
		break;
	case BACKWARD:
		MoveBackward();
		break;
	}

	if (gpGlobals->time >= m_stuckJumpTimestamp)
	{
		if (Jump())
		{
			m_stuckJumpTimestamp = RANDOM_FLOAT(1.0, 2.0) + gpGlobals->time;
		}
	}
}

// Determine approach points from eye position and approach areas of current area
void CCSBot::ComputeApproachPoints()
{
	m_approachPointCount = 0;

	if (!m_lastKnownArea)
	{
		return;
	}

	// assume we're crouching for now
	Vector eye = pev->origin;

	Vector ap;
	float halfWidth;
	for (int i = 0; i < m_lastKnownArea->GetApproachInfoCount() && m_approachPointCount < MAX_APPROACH_POINTS; i++)
	{
		const CNavArea::ApproachInfo *info = m_lastKnownArea->GetApproachInfo(i);
		if (!info->here.area || !info->prev.area)
		{
			continue;
		}

		// compute approach point (approach area is "info->here")
		if (info->prevToHereHow <= GO_WEST)
		{
			info->prev.area->ComputePortal(info->here.area, (NavDirType)info->prevToHereHow, &ap, &halfWidth);
			ap.z = info->here.area->GetZ(&ap);
		}
		else
		{
			// use the area's center as an approach point
			ap = *info->here.area->GetCenter();
		}

		// "bend" our line of sight around corners until we can see the approach point
		Vector bendPoint;
		if (BendLineOfSight(&eye, &ap, &bendPoint))
		{
			m_approachPoint[m_approachPointCount++] = bendPoint;
		}
	}
}

void CCSBot::DrawApproachPoints()
{
	for (int i = 0; i < m_approachPointCount; i++)
	{
		UTIL_DrawBeamPoints(m_approachPoint[i], m_approachPoint[i] + Vector(0, 0, 50), 3, 0, 255, 255);
	}
}

// Find the approach point that is nearest to our current path, ahead of us
NOXREF bool CCSBot::FindApproachPointNearestPath(Vector *pos)
{
	if (!HasPath())
		return false;

	// make sure approach points are accurate
	ComputeApproachPoints();

	if (m_approachPointCount == 0)
		return false;

	Vector target(0, 0, 0), close;
	float targetRangeSq = 0.0f;
	bool found = false;

	int start = m_pathIndex;
	int end = m_pathLength;

	// We dont want the strictly closest point, but the farthest approach point
	// from us that is near our path
	const float nearPathSq = 10000.0f;

	for (int i = 0; i < m_approachPointCount; i++)
	{
		if (FindClosestPointOnPath(&m_approachPoint[i], start, end, &close) == false)
			continue;

		float rangeSq = (m_approachPoint[i] - close).LengthSquared();
		if (rangeSq > nearPathSq)
			continue;

		if (rangeSq > targetRangeSq)
		{
			target = close;
			targetRangeSq = rangeSq;
			found = true;
		}
	}

	if (found)
	{
		*pos = target + Vector(0, 0, HalfHumanHeight);
		return true;
	}

	return false;
}
