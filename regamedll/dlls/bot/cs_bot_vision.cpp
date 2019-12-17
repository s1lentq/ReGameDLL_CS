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

// Used to update view angles to stay on a ladder
float StayOnLadderLine(CCSBot *me, const CNavLadder *ladder)
{
	// determine our facing
	NavDirType faceDir = AngleToDirection(me->pev->v_angle.y);
	const float stiffness = 1.0f;

	// move toward ladder mount point
	switch (faceDir)
	{
	case NORTH:
		return (stiffness * (ladder->m_top.x - me->pev->origin.x));
	case EAST:
		return (stiffness * (ladder->m_top.y - me->pev->origin.y));
	case SOUTH:
		return (-stiffness * (ladder->m_top.x - me->pev->origin.x));
	case WEST:
		return (-stiffness * (ladder->m_top.y - me->pev->origin.y));
	}

	return 0.0f;
}

// Move actual view angles towards desired ones.
// This is the only place v_angle is altered.
// TODO: Make stiffness and turn rate constants timestep invariant.
void CCSBot::UpdateLookAngles()
{
	const float deltaT = g_flBotCommandInterval;
	float maxAccel;
	float stiffness;
	float damping;

	// springs are stiffer when attacking, so we can track and move between targets better
	if (IsAttacking())
	{
		stiffness = 300.0f;
		damping = 30.0f;
		maxAccel = 3000.0f;
	}
	else
	{
		stiffness = 200.0f;
		damping = 25.0f;
		maxAccel = 3000.0f;
	}

	// these may be overridden by ladder logic
	float useYaw = m_lookYaw;
	float usePitch = m_lookPitch;

	// Ladders require precise movement, therefore we need to look at the
	// ladder as we approach and ascend/descend it.
	// If we are on a ladder, we need to look up or down to traverse it - override pitch in this case.
	// If we're trying to break something, though, we actually need to look at it before we can
	// look at the ladder
	if (IsUsingLadder())
	{
		// set yaw to aim at ladder
		Vector to = m_pathLadder->m_top - pev->origin;
		float idealYaw = UTIL_VecToYaw(to);

		NavDirType faceDir = m_pathLadder->m_dir;

		if (m_pathLadderFaceIn)
		{
			faceDir = OppositeDirection(faceDir);
		}

		const float lookAlongLadderRange = 100.0f;
		const float ladderPitch = 60.0f;

		// adjust pitch to look up/down ladder as we ascend/descend
		switch (m_pathLadderState)
		{
		case APPROACH_ASCENDING_LADDER:
		{
			Vector to = m_goalPosition - pev->origin;
			useYaw = idealYaw;

			if (to.IsLengthLessThan(lookAlongLadderRange))
				usePitch = -ladderPitch;
			break;
		}
		case APPROACH_DESCENDING_LADDER:
		{
			Vector to = m_goalPosition - pev->origin;
			useYaw = idealYaw;

			if (to.IsLengthLessThan(lookAlongLadderRange))
				usePitch = ladderPitch;
			break;
		}
		case FACE_ASCENDING_LADDER:
		{
			useYaw = idealYaw;
			usePitch = -ladderPitch;
			break;
		}
		case FACE_DESCENDING_LADDER:
		{
			useYaw = idealYaw;
			usePitch = ladderPitch;
			break;
		}
		case MOUNT_ASCENDING_LADDER:
		case ASCEND_LADDER:
		{
			useYaw = DirectionToAngle(faceDir) + StayOnLadderLine(this, m_pathLadder);
			usePitch = -ladderPitch;
			break;
		}
		case MOUNT_DESCENDING_LADDER:
		case DESCEND_LADDER:
		{
			useYaw = DirectionToAngle(faceDir) + StayOnLadderLine(this, m_pathLadder);
			usePitch = ladderPitch;
			break;
		}
		case DISMOUNT_ASCENDING_LADDER:
		case DISMOUNT_DESCENDING_LADDER:
		{
			useYaw = DirectionToAngle(faceDir);
			break;
		}
		}
	}

	// Yaw
	float angleDiff = NormalizeAngle(useYaw - pev->v_angle.y);

	// if almost at target angle, snap to it
	const float onTargetTolerance = 1.0f;
	if (angleDiff < onTargetTolerance && angleDiff > -onTargetTolerance)
	{
		m_lookYawVel = 0.0f;
		pev->v_angle.y = useYaw;
	}
	else
	{
		// simple angular spring/damper
		float accel = stiffness * angleDiff - damping * m_lookYawVel;

		// limit rate
		if (accel > maxAccel)
			accel = maxAccel;

		else if (accel < -maxAccel)
			accel = -maxAccel;

		m_lookYawVel += deltaT * accel;
		pev->v_angle.y += deltaT * m_lookYawVel;
	}

	// Pitch
	// Actually, this is negative pitch.
	angleDiff = usePitch - pev->v_angle.x;

	angleDiff = NormalizeAngle(angleDiff);

	if (false && angleDiff < onTargetTolerance && angleDiff > -onTargetTolerance)
	{
		m_lookPitchVel = 0.0f;
		pev->v_angle.x = usePitch;
	}
	else
	{
		// simple angular spring/damper
		// double the stiffness since pitch is only +/- 90 and yaw is +/- 180
		float accel = 2.0f * stiffness * angleDiff - damping * m_lookPitchVel;

		// limit rate
		if (accel > maxAccel)
			accel = maxAccel;

		else if (accel < -maxAccel)
			accel = -maxAccel;

		m_lookPitchVel += deltaT * accel;
		pev->v_angle.x += deltaT * m_lookPitchVel;
	}

	// limit range - avoid gimbal lock
	if (pev->v_angle.x < -89.0f)
		pev->v_angle.x = -89.0f;
	else if (pev->v_angle.x > 89.0f)
		pev->v_angle.x = 89.0f;

	pev->v_angle.z = 0.0f;
}

// Return true if we can see the point
bool CCSBot::IsVisible(const Vector *pos, bool testFOV) const
{
	// we can't see anything if we're blind
	if (IsBlind())
		return false;

	// is it in my general viewcone?
	if (testFOV && !(const_cast<CCSBot *>(this)->FInViewCone(pos)))
		return false;

	// check line of sight against smoke
	if (TheCSBots()->IsLineBlockedBySmoke(&GetEyePosition(), pos))
		return false;

	// check line of sight
	// Must include CONTENTS_MONSTER to pick up all non-brush objects like barrels
	TraceResult result;
	UTIL_TraceLine(GetEyePosition(), *pos, ignore_monsters, ignore_glass, ENT(pev), &result);

	if (result.flFraction != 1.0f)
		return false;

	return true;
}

// Return true if we can see any part of the player
// Check parts in order of importance. Return the first part seen in "visParts" if it is non-NULL.
bool CCSBot::IsVisible(CBasePlayer *pPlayer, bool testFOV, unsigned char *visParts) const
{
#ifdef REGAMEDLL_ADD // REGAMEDLL_FIXES ?
	if ((pPlayer->pev->flags & FL_NOTARGET) || (pPlayer->pev->effects & EF_NODRAW))
		return false;
#endif
	
	Vector spot = pPlayer->pev->origin;
	unsigned char testVisParts = NONE;

	// finish chest check
	if (IsVisible(&spot, testFOV))
		testVisParts |= CHEST;

	// check top of head
	spot = spot + Vector(0, 0, 25.0f);

	if (IsVisible(&spot, testFOV))
		testVisParts |= HEAD;

	// check feet
	const float standFeet = 34.0f;
	const float crouchFeet = 14.0f;

	if (pPlayer->pev->flags & FL_DUCKING)
		spot.z = pPlayer->pev->origin.z - crouchFeet;
	else
		spot.z = pPlayer->pev->origin.z - standFeet;

	// check feet
	if (IsVisible(&spot, testFOV))
		testVisParts |= FEET;

	// check "edges"
	const float edgeOffset = 13.0f;
	Vector2D dir = (pPlayer->pev->origin - pev->origin).Make2D();
	dir.NormalizeInPlace();

	Vector2D perp(-dir.y, dir.x);

	spot = pPlayer->pev->origin + Vector(perp.x * edgeOffset, perp.y * edgeOffset, 0);

	if (IsVisible(&spot, testFOV))
		testVisParts |= LEFT_SIDE;

	spot = pPlayer->pev->origin - Vector(perp.x * edgeOffset, perp.y * edgeOffset, 0);

	if (IsVisible(&spot, testFOV))
		testVisParts |= RIGHT_SIDE;

	if (visParts)
		*visParts = testVisParts;

	if (testVisParts != NONE)
		return true;

	return false;
}

bool CCSBot::IsEnemyPartVisible(VisiblePartType part) const
{
	if (!IsEnemyVisible())
		return false;

	return (m_visibleEnemyParts & part) != 0;
}

void CCSBot::UpdateLookAt()
{
	Vector to = m_lookAtSpot - EyePosition();
	Vector idealAngle = UTIL_VecToAngles(to);
	idealAngle.x = 360.0f - idealAngle.x;

	SetLookAngles(idealAngle.y, idealAngle.x);
}

// Look at the given point in space for the given duration (-1 means forever)
void CCSBot::SetLookAt(const char *desc, const Vector *pos, PriorityType pri, float duration, bool clearIfClose, float angleTolerance)
{
	if (!pos)
		return;

	// if currently looking at a point in space with higher priority, ignore this request
	if (m_lookAtSpotState != NOT_LOOKING_AT_SPOT && m_lookAtSpotPriority > pri)
		return;

	// if already looking at this spot, just extend the time
	const float tolerance = 10.0f;
	if (m_lookAtSpotState != NOT_LOOKING_AT_SPOT && VectorsAreEqual(pos, &m_lookAtSpot, tolerance))
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

// Block all "look at" and "look around" behavior for given duration - just look ahead
void CCSBot::InhibitLookAround(float duration)
{
	m_inhibitLookAroundTimestamp = gpGlobals->time + duration;
}

// Update enounter spot timestamps, etc
void CCSBot::UpdatePeripheralVision()
{
	// if we update at 10Hz, this ensures we test once every three
	const float peripheralUpdateInterval = 0.29f;
	if (gpGlobals->time - m_peripheralTimestamp < peripheralUpdateInterval)
		return;

	m_peripheralTimestamp = gpGlobals->time;

	if (m_spotEncounter)
	{
		// check LOS to all spots in case we see them with our "peripheral vision"
		Vector pos;
		for (auto &spotOrder : m_spotEncounter->spotList)
		{
			const Vector *spotPos = spotOrder.spot->GetPosition();

			pos.x = spotPos->x;
			pos.y = spotPos->y;
			pos.z = spotPos->z + HalfHumanHeight;

			if (!IsVisible(&pos, CHECK_FOV))
				continue;

			// can see hiding spot, remember when we saw it last
			SetHidingSpotCheckTimestamp(spotOrder.spot);
		}
	}
}

// Update the "looking around" behavior.
void CCSBot::UpdateLookAround(bool updateNow)
{
	// check if looking around has been inhibited
	// Moved inhibit to allow high priority enemy lookats to still occur
	if (gpGlobals->time < m_inhibitLookAroundTimestamp)
		return;

	const float recentThreatTime = 0.25f; // 1.0f;

	// Unless we can hear them moving, in which case look towards the noise
	if (!IsEnemyVisible())
	{
		const float noiseStartleRange = 1000.0f;
		if (CanHearNearbyEnemyGunfire(noiseStartleRange))
		{
			Vector spot = m_noisePosition;
			spot.z += HalfHumanHeight;

			SetLookAt("Check dangerous noise", &spot, PRIORITY_HIGH, recentThreatTime);
			InhibitLookAround(RANDOM_FLOAT(2.0f, 4.0f));

			return;
		}
	}

	// If we recently saw an enemy, look towards where we last saw them
	if (!IsLookingAtSpot(PRIORITY_MEDIUM) && gpGlobals->time - m_lastSawEnemyTimestamp < recentThreatTime)
	{
		ClearLookAt();

		Vector spot = m_lastEnemyPosition;

		// find enemy position on the ground
		if (GetSimpleGroundHeight(&m_lastEnemyPosition, &spot.z))
		{
			spot.z += HalfHumanHeight;
			SetLookAt("Last Enemy Position", &spot, PRIORITY_MEDIUM, RANDOM_FLOAT(2.0f, 3.0f), true);
			return;
		}
	}

	// Look at nearby enemy noises
	if (UpdateLookAtNoise())
		return;

	if (IsNotMoving())
	{
		// if we're sniping, zoom in to watch our approach points
		if (IsUsingSniperRifle())
		{
			// low skill bots don't pre-zoom
			if (GetProfile()->GetSkill() > 0.4f)
			{
				if (!IsViewMoving())
				{
					float range = ComputeWeaponSightRange();
					AdjustZoom(range);
				}
				else
				{
					// zoom out
					if (GetZoomLevel() != NO_ZOOM)
						SecondaryAttack();
				}
			}
		}

		if (!m_lastKnownArea)
			return;

		if (gpGlobals->time < m_lookAroundStateTimestamp)
			return;

		// if we're sniping, switch look-at spots less often
		if (IsUsingSniperRifle())
			m_lookAroundStateTimestamp = gpGlobals->time + RANDOM_FLOAT(5.0f, 10.0f);
		else
			m_lookAroundStateTimestamp = gpGlobals->time + RANDOM_FLOAT(1.0f, 2.0f);

		if (m_approachPointCount == 0)
		{
			ClearLookAt();
			return;
		}

		int which = RANDOM_LONG(0, m_approachPointCount - 1);
		Vector spot = m_approachPoint[which];

		// don't look at the floor, look roughly at chest level
		// TODO: If this approach point is very near, this will cause us to aim up in the air if were crouching
		spot.z += HalfHumanHeight;
		SetLookAt("Approach Point (Hiding)", &spot, PRIORITY_LOW);
		return;
	}

	// Glance at "encouter spots" as we move past them
	if (m_spotEncounter)
	{
		// Check encounter spots
		if (!IsSafe() && !IsLookingAtSpot(PRIORITY_LOW))
		{
			// allow a short time to look where we're going
			if (gpGlobals->time < m_spotCheckTimestamp)
				return;

			// TODO: Use skill parameter instead of accuracy

			// lower skills have exponentially longer delays
			real_t asleep = (1.0f - GetProfile()->GetSkill());
			asleep *= asleep;
			asleep *= asleep;

			m_spotCheckTimestamp = gpGlobals->time + asleep * RANDOM_FLOAT(10.0f, 30.0f);

			// figure out how far along the path segment we are
			Vector delta = m_spotEncounter->path.to - m_spotEncounter->path.from;
			real_t length = delta.Length();

#ifdef REGAMEDLL_FIXES
			float adx = Q_abs(delta.x);
			float ady = Q_abs(delta.y);
#else
			float adx = float(Q_abs(int64(delta.x)));
			float ady = float(Q_abs(int64(delta.y)));
#endif
			real_t t;

			if (adx > ady)
				t = (pev->origin.x - m_spotEncounter->path.from.x) / delta.x;
			else
				t = (pev->origin.y - m_spotEncounter->path.from.y) / delta.y;

			// advance parameter a bit so we "lead" our checks
			const float leadCheckRange = 50.0f;
			t += leadCheckRange / length;

			if (t < 0.0f)
				t = 0.0f;
			else if (t > 1.0f)
				t = 1.0f;

			// collect the unchecked spots so far
			const int MAX_DANGER_SPOTS = 8;
			HidingSpot *dangerSpot[MAX_DANGER_SPOTS];
			int dangerSpotCount = 0;
			int dangerIndex = 0;

			const float checkTime = 10.0f;

			for (auto &spotOrder : m_spotEncounter->spotList)
			{
				// if we have seen this spot recently, we don't need to look at it
				if (gpGlobals->time - GetHidingSpotCheckTimestamp(spotOrder.spot) <= checkTime)
					continue;

				if (spotOrder.t > t)
					break;

				dangerSpot[dangerIndex++] = spotOrder.spot;
				if (dangerIndex >= MAX_DANGER_SPOTS)
					dangerIndex = 0;

				if (dangerSpotCount < MAX_DANGER_SPOTS)
					dangerSpotCount++;
			}

			if (dangerSpotCount)
			{
				// pick one of the spots at random
				int which = RANDOM_LONG(0, dangerSpotCount - 1);

				const Vector *checkSpot = dangerSpot[which]->GetPosition();

				Vector pos = *checkSpot;
				pos.z += HalfHumanHeight;

				// glance at the spot for minimum time
				SetLookAt("Encounter Spot", &pos, PRIORITY_LOW, 0, true, 10.0f);

				// immediately mark it as "checked", so we don't check it again
				// if we get distracted before we check it - that's the way it goes
				SetHidingSpotCheckTimestamp(dangerSpot[which]);
			}
		}
	}
}

// "Bend" our line of sight around corners until we can "see" the point.
bool CCSBot::BendLineOfSight(const Vector *eye, const Vector *point, Vector *bend) const
{
	// if we can directly see the point, use it
	TraceResult result;
	UTIL_TraceLine(*eye, *point + Vector(0, 0, HalfHumanHeight), ignore_monsters, ENT(pev), &result);

	if (result.flFraction == 1.0f && !result.fStartSolid)
	{
		// can directly see point, no bending needed
		*bend = *point;
		return true;
	}

	// "bend" our line of sight until we can see the approach point
	Vector v = *point - *eye;
	float startAngle = UTIL_VecToYaw(v);
	float length = v.Length2D();
	v.NormalizeInPlace();

	float angleInc = 10.0f;
	for (float angle = angleInc; angle <= 135.0f; angle += angleInc)
	{
		// check both sides at this angle offset
		for (int side = 0; side < 2; side++)
		{
			float actualAngle = side ? (startAngle + angle) : (startAngle - angle);

			float dx = BotCOS(actualAngle);
			float dy = BotSIN(actualAngle);

			// compute rotated point ray endpoint
			Vector rotPoint(eye->x + length * dx, eye->y + length * dy, point->z);

			TraceResult result;
			UTIL_TraceLine(*eye, rotPoint + Vector(0, 0, HalfHumanHeight), ignore_monsters, ENT(pev), &result);

			// if this ray started in an obstacle, skip it
			if (result.fStartSolid)
			{
				continue;
			}

			Vector ray = rotPoint - *eye;
			float rayLength = ray.NormalizeInPlace();
			float visibleLength = rayLength * result.flFraction;

			// step along ray, checking if point is visible from ray point
			const float bendStepSize = 50.0f;
			for (float bendLength = bendStepSize; bendLength <= visibleLength; bendLength += bendStepSize)
			{
				// compute point along ray
				Vector rayPoint = *eye + bendLength * ray;

				// check if we can see approach point from this bend point
				UTIL_TraceLine(rayPoint, *point + Vector(0, 0, HalfHumanHeight), ignore_monsters, ENT(pev), &result);

				if (result.flFraction == 1.0f && !result.fStartSolid)
				{
					// target is visible from this bend point on the ray - use this point on the ray as our point

					// keep "bent" point at correct height along line of sight
					if (!GetGroundHeight(&rayPoint, &rayPoint.z))
					{
						rayPoint.z = point->z;
					}

					*bend = rayPoint;
					return true;
				}
			}
		}
	}

	*bend = *point;

	// bending rays didn't help - still can't see the point
	return false;
}

CBasePlayer *CCSBot::FindMostDangerousThreat()
{
	// maximum number of simulataneously attendable threats
#ifdef REGAMEDLL_FIXES
	const int MAX_THREATS = MAX_CLIENTS;
#else
	const int MAX_THREATS = 16;
#endif

	struct CloseInfo
	{
		CBasePlayer *enemy;
		float range;
	};

	CloseInfo threat[MAX_THREATS];
	int threatCount = 0;

#ifdef REGAMEDLL_ADD
	int prevIndex = m_enemyQueueIndex - 1;
	if (prevIndex < 0)
		prevIndex = MAX_ENEMY_QUEUE - 1;

	CBasePlayer *currentThreat = m_enemyQueue[prevIndex].player;
#endif

	m_bomber = nullptr;
	m_closestVisibleFriend = nullptr;
	m_closestVisibleHumanFriend = nullptr;

	float closeFriendRange = 99999999999.9f;
	float closeHumanFriendRange = 99999999999.9f;

	int i;

	{
		for (i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

			if (!pPlayer)
				continue;

			if (FNullEnt(pPlayer->pev))
				continue;

			// is it a player?
			if (!pPlayer->IsPlayer())
				continue;

			// ignore self
			if (pPlayer->entindex() == entindex())
				continue;

			// is it alive?
			if (!pPlayer->IsAlive())
				continue;

#ifdef REGAMEDLL_ADD // REGAMEDLL_FIXES ?
			if ((pPlayer->pev->flags & FL_NOTARGET) || (pPlayer->pev->effects & EF_NODRAW))
				continue;
#endif
			// is it an enemy?
			if (BotRelationship(pPlayer) == BOT_TEAMMATE)
			{
				TraceResult result;
				UTIL_TraceLine(GetEyePosition(), pPlayer->pev->origin, ignore_monsters, ignore_glass, edict(), &result);
				if (result.flFraction == 1.0f)
				{
					// update watch timestamp
					int idx = pPlayer->entindex() - 1;
					m_watchInfo[idx].timestamp = gpGlobals->time;
					m_watchInfo[idx].isEnemy = false;

					// keep track of our closest friend
					Vector to = pev->origin - pPlayer->pev->origin;
					float rangeSq = to.LengthSquared();
					if (rangeSq < closeFriendRange)
					{
						m_closestVisibleFriend = pPlayer;
						closeFriendRange = rangeSq;
					}

					// keep track of our closest human friend
					if (!pPlayer->IsBot() && rangeSq < closeHumanFriendRange)
					{
						m_closestVisibleHumanFriend = pPlayer;
						closeHumanFriendRange = rangeSq;
					}
				}

				continue;
			}

			// check if this enemy is fully
			unsigned char visParts;
			if (!IsVisible(pPlayer, CHECK_FOV, &visParts))
				continue;

#ifdef REGAMEDLL_ADD
			// do we notice this enemy? (always notice current enemy)
			if (pPlayer != currentThreat)
			{
				if (!IsNoticable(pPlayer, visParts))
				{
					continue;
				}
			}
#endif

			// update watch timestamp
			int idx = pPlayer->entindex() - 1;
			m_watchInfo[idx].timestamp = gpGlobals->time;
			m_watchInfo[idx].isEnemy = true;

			// note if we see the bomber
			if (pPlayer->IsBombGuy())
			{
				m_bomber = pPlayer;
			}

			// keep track of all visible threats
			Vector d = pev->origin - pPlayer->pev->origin;
			float distSq = d.LengthSquared();

			// maintain set of visible threats, sorted by increasing distance
			if (threatCount == 0)
			{
				threat[0].enemy = pPlayer;
				threat[0].range = distSq;
				threatCount = 1;
			}
			else
			{
				// find insertion point
				int j;
				for (j = 0; j < threatCount; j++)
				{
					if (distSq < threat[j].range)
						break;
				}

				// shift lower half down a notch
				for (int k = threatCount - 1; k >= j; k--)
					threat[k + 1] = threat[k];

				// insert threat into sorted list
				threat[j].enemy = pPlayer;
				threat[j].range = distSq;

				if (threatCount < MAX_THREATS)
					threatCount++;
			}
		}
	}
	{
		// track the maximum enemy and friend counts we've seen recently
		int prevEnemies = m_nearbyEnemyCount;
		int prevFriends = m_nearbyFriendCount;
		m_nearbyEnemyCount = 0;
		m_nearbyFriendCount = 0;

		for (i = 0; i < MAX_CLIENTS; i++)
		{
			if (m_watchInfo[i].timestamp <= 0.0f)
				continue;

			const float recentTime = 3.0f;
			if (gpGlobals->time - m_watchInfo[i].timestamp < recentTime)
			{
				if (m_watchInfo[i].isEnemy)
					m_nearbyEnemyCount++;
				else
					m_nearbyFriendCount++;
			}
		}

		// note when we saw this batch of enemies
		if (prevEnemies == 0 && m_nearbyEnemyCount > 0)
		{
			m_firstSawEnemyTimestamp = gpGlobals->time;
		}

		if (prevEnemies != m_nearbyEnemyCount || prevFriends != m_nearbyFriendCount)
		{
			PrintIfWatched("Nearby friends = %d, enemies = %d\n", m_nearbyFriendCount, m_nearbyEnemyCount);
		}
	}
	{
		// Track the place where we saw most of our enemies
		struct PlaceRank
		{
			unsigned int place;
			int count;
		};
		static PlaceRank placeRank[MAX_PLACES_PER_MAP];
		int locCount = 0;

		PlaceRank common;
		common.place = 0;
		common.count = 0;

		for (i = 0; i < threatCount; i++)
		{
			// find the area the player/bot is standing on
			CNavArea *area;
			CCSBot *pBot = static_cast<CCSBot *>(threat[i].enemy);

			if (pBot->IsBot())
			{
				area = pBot->GetLastKnownArea();
			}
			else
			{
				area = TheNavAreaGrid.GetNearestNavArea(&threat[i].enemy->pev->origin);
			}

			if (!area)
				continue;

			unsigned int threatLoc = area->GetPlace();
			if (!threatLoc)
				continue;

			// if place is already in set, increment count
			int j;
			for (j = 0; j < locCount; j++)
			{
				if (placeRank[j].place == threatLoc)
					break;
			}

			if (j == locCount)
			{
				// new place
				if (locCount < MAX_PLACES_PER_MAP)
				{
					placeRank[locCount].place = threatLoc;
					placeRank[locCount].count = 1;

					if (common.count == 0)
						common = placeRank[locCount];

					locCount++;
				}
			}
			else
			{
				// others are in that place, increment
				placeRank[j].count++;

				// keep track of the most common place
				if (placeRank[j].count > common.count)
					common = placeRank[j];
			}
		}

		// remember most common place
		m_enemyPlace = common.place;
	}

	{
		if (threatCount == 0)
			return nullptr;

		int t;

#ifdef REGAMEDLL_ADD
		bool sawCloserThreat = false;
		bool sawCurrentThreat = false;
		for (t = 0; t < threatCount; t++)
		{
			if (threat[t].enemy == currentThreat)
			{
				sawCurrentThreat = true;
			}
			else if (threat[t].enemy != currentThreat && IsSignificantlyCloser(threat[t].enemy, currentThreat))
			{
				sawCloserThreat = true;
			}
		}

		if (sawCurrentThreat && !sawCloserThreat)
		{
			return currentThreat;
		}
#endif

		// otherwise, find the closest threat that without using shield
		for (t = 0; t < threatCount; t++)
		{
			if (!threat[t].enemy->IsProtectedByShield())
			{
				return threat[t].enemy;
			}
		}
	}

	// return closest threat
	return threat[0].enemy;
}

// Update our reaction time queue
void CCSBot::UpdateReactionQueue()
{
	// zombies dont see any threats
	if (cv_bot_zombie.value > 0.0f)
		return;

	// find biggest threat at this instant
	CBasePlayer *threat = FindMostDangerousThreat();

	int now = m_enemyQueueIndex;

#ifdef REGAMEDLL_ADD
	// reset timer
	m_attentionInterval.Start();
#endif

	// store a snapshot of its state at the end of the reaction time queue
	if (threat)
	{
		m_enemyQueue[now].player = threat;
		m_enemyQueue[now].isReloading = threat->IsReloading();
		m_enemyQueue[now].isProtectedByShield = threat->IsProtectedByShield();
	}
	else
	{
		m_enemyQueue[now].player = nullptr;
		m_enemyQueue[now].isReloading = false;
		m_enemyQueue[now].isProtectedByShield = false;
	}

	// queue is round-robin
	if (++m_enemyQueueIndex >= MAX_ENEMY_QUEUE)
		m_enemyQueueIndex = 0;

	if (m_enemyQueueCount < MAX_ENEMY_QUEUE)
		m_enemyQueueCount++;

	// clamp reaction time to enemy queue size
	float reactionTime = GetProfile()->GetReactionTime();
	float maxReactionTime = (MAX_ENEMY_QUEUE * g_flBotFullThinkInterval) - 0.01f;
	if (reactionTime > maxReactionTime)
		reactionTime = maxReactionTime;

	// "rewind" time back to our reaction time
	int reactionTimeSteps = int((reactionTime / g_flBotFullThinkInterval) + 0.5f);

	int i = now - reactionTimeSteps;
	if (i < 0)
		i += MAX_ENEMY_QUEUE;

	m_enemyQueueAttendIndex = byte(i);
}

// Return the most dangerous threat we are "conscious" of
CBasePlayer *CCSBot::GetRecognizedEnemy()
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return nullptr;

	return m_enemyQueue[m_enemyQueueAttendIndex].player;
}

// Return true if the enemy we are "conscious" of is reloading
bool CCSBot::IsRecognizedEnemyReloading()
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return false;

	return m_enemyQueue[m_enemyQueueAttendIndex].isReloading;
}

// Return true if the enemy we are "conscious" of is hiding behind a shield
bool CCSBot::IsRecognizedEnemyProtectedByShield()
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return false;

	return m_enemyQueue[m_enemyQueueAttendIndex].isProtectedByShield;
}

// Return distance to closest enemy we are "conscious" of
float CCSBot::GetRangeToNearestRecognizedEnemy()
{
	const CBasePlayer *pEnemy = GetRecognizedEnemy();

	if (pEnemy)
	{
		return (pev->origin - pEnemy->pev->origin).Length();
	}

	return 99999999.9f;
}

// Blind the bot for the given duration
void CCSBot::Blind(float duration, float holdTime, float fadeTime, int alpha)
{
	// extend
	CBasePlayer::Blind(duration, holdTime, fadeTime, alpha);

	PrintIfWatched("I'm blind!\n");

	if (RANDOM_FLOAT(0.0f, 100.0f) < 33.3f)
	{
		GetChatter()->Say("Blinded", 1.0f);
	}

	// decide which way to move while blind
	m_blindMoveDir = static_cast<NavRelativeDirType>(RANDOM_LONG(1, NUM_RELATIVE_DIRECTIONS - 1));

	// if blinded while in combat - then spray and pray!
	m_blindFire = (RANDOM_FLOAT(0.0f, 100.0f) < 10.0f) != 0;

	// no longer safe
	AdjustSafeTime();
}

#ifdef REGAMEDLL_ADD
bool CCSBot::IsNoticable(const CBasePlayer *pPlayer, unsigned char visibleParts) const
{
	float deltaT = m_attentionInterval.GetElapsedTime();

	// all chances are specified in terms of a standard "quantum" of time
	// in which a normal person would notice something
	const float noticeQuantum = 0.25f;

	// determine percentage of player that is visible
	float coverRatio = 0.0f;

	if (visibleParts & CHEST)
	{
		const float chance = 40.0f;
		coverRatio += chance;
	}

	if (visibleParts & HEAD)
	{
		const float chance = 10.0f;
		coverRatio += chance;
	}

	if (visibleParts & LEFT_SIDE)
	{
		const float chance = 20.0f;
		coverRatio += chance;
	}

	if (visibleParts & RIGHT_SIDE)
	{
		const float chance = 20.0f;
		coverRatio += chance;
	}

	if (visibleParts & FEET)
	{
		const float chance = 10.0f;
		coverRatio += chance;
	}

	// compute range modifier - farther away players are harder to notice, depeding on what they are doing
	float range = (pPlayer->pev->origin - pev->origin).Length();
	const float closeRange = 300.0f;
	const float farRange = 1000.0f;

	float rangeModifier;
	if (range < closeRange)
	{
		rangeModifier = 0.0f;
	}
	else if (range > farRange)
	{
		rangeModifier = 1.0f;
	}
	else
	{
		rangeModifier = (range - closeRange) / (farRange - closeRange);
	}

	// harder to notice when crouched
	bool isCrouching = (pPlayer->pev->flags & FL_DUCKING) == FL_DUCKING;
	// moving players are easier to spot
	float playerSpeedSq = pPlayer->pev->velocity.LengthSquared();
	const float runSpeed = 200.0f;
	const float walkSpeed = 30.0f;
	float farChance, closeChance;
	if (playerSpeedSq > runSpeed * runSpeed)
	{
		// running players are always easy to spot (must be standing to run)
		return true;
	}
	else if (playerSpeedSq > walkSpeed * walkSpeed)
	{
		// walking players are less noticable far away
		if (isCrouching)
		{
			closeChance = 90.0f;
			farChance = 60.0f;
		}
		// standing
		else
		{
			closeChance = 100.0f;
			farChance = 75.0f;
		}
	}
	else
	{
		// motionless players are hard to notice
		if (isCrouching)
		{
			// crouching and motionless - very tough to notice
			closeChance = 80.0f;
			farChance = 5.0f;		// takes about three seconds to notice (50% chance)
		}
		// standing
		else
		{
			closeChance = 100.0f;
			farChance = 10.0f;
		}
	}

	// combine posture, speed, and range chances
	float dispositionChance = closeChance + (farChance - closeChance) * rangeModifier;

	// determine actual chance of noticing player
	float noticeChance = dispositionChance * coverRatio/100.0f;

	// scale by skill level
	noticeChance *= (0.5f + 0.5f * GetProfile()->GetSkill());

	// if we are alert, our chance of noticing is much higher
	//if (IsAlert())
	//{
	//	const float alertBonus = 50.0f;
	//	noticeChance += alertBonus;
	//}

	// scale by time quantum
	noticeChance *= deltaT / noticeQuantum;

	// there must always be a chance of detecting the enemy
	const float minChance = 0.1f;
	if (noticeChance < minChance)
	{
		noticeChance = minChance;
	}

	//PrintIfWatched("Notice chance = %3.2f\n", noticeChance);
	return (RANDOM_FLOAT(0.0f, 100.0f) < noticeChance);
}
#endif
