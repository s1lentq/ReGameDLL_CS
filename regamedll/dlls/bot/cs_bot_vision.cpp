#include "precompiled.h"

// Used to update view angles to stay on a ladder

/* <3d8352> ../cstrike/dlls/bot/cs_bot_vision.cpp:16 */
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

/* <3d882c> ../cstrike/dlls/bot/cs_bot_vision.cpp:48 */
#ifndef HOOK_GAMEDLL
void CCSBot::UpdateLookAngles(void)
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
#endif // HOOK_GAMEDLL

// Return true if we can see the point

/* <3d8c91> ../cstrike/dlls/bot/cs_bot_vision.cpp:238 */
bool CCSBot::__MAKE_VHOOK(IsVisible)(const Vector *pos, bool testFOV) const
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

/* <3d8d9b> ../cstrike/dlls/bot/cs_bot_vision.cpp:269 */
bool CCSBot::__MAKE_VHOOK(IsVisible)(CBasePlayer *player, bool testFOV, unsigned char *visParts) const
{
	Vector spot = player->pev->origin;
	VisiblePartType testVisParts = NONE;

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

	if (player->pev->flags & FL_DUCKING)
		spot.z = player->pev->origin.z - crouchFeet;
	else
		spot.z = player->pev->origin.z - standFeet;

	// check feet
	if (IsVisible(&spot, testFOV))
		testVisParts |= FEET;

	// check "edges"
	const float edgeOffset = 13.0f;
	Vector2D dir = (player->pev->origin - pev->origin).Make2D();
	dir.NormalizeInPlace();

	Vector2D perp(-dir.y, dir.x);

	spot = player->pev->origin + Vector(perp.x * edgeOffset, perp.y * edgeOffset, 0);

	if (IsVisible(&spot, testFOV))
		testVisParts |= LEFT_SIDE;

	spot = player->pev->origin - Vector(perp.x * edgeOffset, perp.y * edgeOffset, 0);

	if (IsVisible(&spot, testFOV))
		testVisParts |= RIGHT_SIDE;

	if (visParts != NULL)
		*visParts = testVisParts;

	if (testVisParts != NONE)
		return true;

	return false;
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
	Vector idealAngle = UTIL_VecToAngles(to);
	idealAngle.x = 360.0f - idealAngle.x;

	SetLookAngles(idealAngle.y, idealAngle.x);
}

// Look at the given point in space for the given duration (-1 means forever)

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

/* <3d90a7> ../cstrike/dlls/bot/cs_bot_vision.cpp:383 */
void CCSBot::InhibitLookAround(float duration)
{
	m_inhibitLookAroundTimestamp = gpGlobals->time + duration;
}

// Update enounter spot timestamps, etc

/* <3d90d3> ../cstrike/dlls/bot/cs_bot_vision.cpp:392 */
void CCSBot::UpdatePeripheralVision(void)
{
	// if we update at 10Hz, this ensures we test once every three
	const float peripheralUpdateInterval = 0.29f;
	if (gpGlobals->time - m_peripheralTimestamp < peripheralUpdateInterval)
		return;

	m_peripheralTimestamp = gpGlobals->time;

	if (m_spotEncounter)
	{
		// check LOS to all spots in case we see them with our "peripheral vision"
		const SpotOrder *spotOrder = NULL;
		Vector pos;

		for (SpotOrderList::const_iterator iter = m_spotEncounter->spotList.begin(); iter != m_spotEncounter->spotList.end(); ++iter)
		{
			spotOrder = &(*iter);

			const Vector *spotPos = spotOrder->spot->GetPosition();

			pos.x = spotPos->x;
			pos.y = spotPos->y;
			pos.z = spotPos->z + HalfHumanHeight;

			if (!IsVisible(&pos, CHECK_FOV))
				continue;

			// can see hiding spot, remember when we saw it last
			SetHidingSpotCheckTimestamp(spotOrder->spot);
		}
	}
}

// Update the "looking around" behavior.

/* <3d91af> ../cstrike/dlls/bot/cs_bot_vision.cpp:429 */
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

		if (m_lastKnownArea == NULL)
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
		Vector spot = m_approachPoint[ which ];

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
			float_precision asleep = (1.0f - GetProfile()->GetSkill());
			asleep *= asleep;
			asleep *= asleep;

			m_spotCheckTimestamp = gpGlobals->time + asleep * RANDOM_FLOAT(10.0f, 30.0f);

			// figure out how far along the path segment we are
			Vector delta = m_spotEncounter->path.to - m_spotEncounter->path.from;
			float_precision length = delta.Length();
			float adx = (float)abs(int64(delta.x));
			float ady = (float)abs(int64(delta.y));
			float_precision t;

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
			#define MAX_DANGER_SPOTS 8
			HidingSpot *dangerSpot[MAX_DANGER_SPOTS];
			int dangerSpotCount = 0;
			int dangerIndex = 0;

			const float checkTime = 10.0f;
			const SpotOrder *spotOrder;

			for (SpotOrderList::iterator iter = m_spotEncounter->spotList.begin(); iter != m_spotEncounter->spotList.end(); ++iter)
			{
				spotOrder = &(*iter);

				// if we have seen this spot recently, we don't need to look at it
				if (gpGlobals->time - GetHidingSpotCheckTimestamp(spotOrder->spot) <= checkTime)
					continue;

				if (spotOrder->t > t)
					break;

				dangerSpot[ dangerIndex++ ] = spotOrder->spot;
				if (dangerIndex >= MAX_DANGER_SPOTS)
					dangerIndex = 0;
				if (dangerSpotCount < MAX_DANGER_SPOTS)
					++dangerSpotCount;
			}

			if (dangerSpotCount)
			{
				// pick one of the spots at random
				int which = RANDOM_LONG(0, dangerSpotCount - 1);

				const Vector *checkSpot = dangerSpot[ which ]->GetPosition();

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

/* <3d9618> ../cstrike/dlls/bot/cs_bot_vision.cpp:628 */
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
		for (int side = 0; side < 2; ++side)
		{
			float actualAngle = (side) ? (startAngle + angle) : (startAngle - angle);

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

/* <3d99e8> ../cstrike/dlls/bot/cs_bot_vision.cpp:707 */
CBasePlayer *CCSBot::FindMostDangerousThreat(void)
{
	// maximum number of simulataneously attendable threats
	enum { MAX_THREATS = 16 };
	struct CloseInfo
	{
		CBasePlayer *enemy;
		float range;
	}
	threat[ MAX_THREATS ];
	int threatCount = 0;

	m_bomber = NULL;

	m_closestVisibleFriend = NULL;
	float closeFriendRange = 99999999999.9f;

	m_closestVisibleHumanFriend = NULL;
	float closeHumanFriendRange = 99999999999.9f;

	int i;

	{
		for (i = 1; i <= gpGlobals->maxClients; ++i)
		{
			CBaseEntity *entity = UTIL_PlayerByIndex(i);

			if (entity == NULL)
				continue;

			if (FNullEnt(entity->pev))
				continue;

			// is it a player?
			if (!entity->IsPlayer())
				continue;

			CBasePlayer *player = static_cast<CBasePlayer *>(entity);

			// ignore self
			if (player->entindex() == entindex())
				continue;

			// is it alive?
			if (!player->IsAlive())
				continue;

			// is it an enemy?
			if (player->m_iTeam == m_iTeam)
			{
				TraceResult result;
				UTIL_TraceLine(GetEyePosition(), player->pev->origin, ignore_monsters, ignore_glass, edict(), &result);
				if (result.flFraction == 1.0f)
				{
					// update watch timestamp
					int idx = player->entindex() - 1;
					m_watchInfo[idx].timestamp = gpGlobals->time;
					m_watchInfo[idx].isEnemy = false;

					// keep track of our closest friend
					Vector to = pev->origin - player->pev->origin;
					float rangeSq = to.LengthSquared();
					if (rangeSq < closeFriendRange)
					{
						m_closestVisibleFriend = player;
						closeFriendRange = rangeSq;
					}

					// keep track of our closest human friend
					if (!player->IsBot() && rangeSq < closeHumanFriendRange)
					{
						m_closestVisibleHumanFriend = player;
						closeHumanFriendRange = rangeSq;
					}
				}

				continue;
			}

			// check if this enemy is fully
			if (!IsVisible(player, CHECK_FOV))
				continue;

			// update watch timestamp
			int idx = player->entindex() - 1;
			m_watchInfo[idx].timestamp = gpGlobals->time;
			m_watchInfo[idx].isEnemy = true;

			// note if we see the bomber
			if (player->IsBombGuy())
			{
				m_bomber = player;
			}

			// keep track of all visible threats
			Vector d = pev->origin - player->pev->origin;
			float distSq = d.LengthSquared();

			// maintain set of visible threats, sorted by increasing distance
			if (threatCount == 0)
			{
				threat[0].enemy = player;
				threat[0].range = distSq;
				threatCount = 1;
			}
			else
			{
				// find insertion point
				int j;
				for (j = 0; j < threatCount; ++j)
				{
					if (distSq < threat[j].range)
						break;
				}


				// shift lower half down a notch
				for (int k = threatCount - 1; k >= j; --k)
					threat[k + 1] = threat[k];

				// insert threat into sorted list
				threat[j].enemy = player;
				threat[j].range = distSq;

				if (threatCount < MAX_THREATS)
					++threatCount;
			}
		}
	}
	{
		// track the maximum enemy and friend counts we've seen recently
		int prevEnemies = m_nearbyEnemyCount;
		int prevFriends = m_nearbyFriendCount;
		m_nearbyEnemyCount = 0;
		m_nearbyFriendCount = 0;

		for (i = 0; i < MAX_CLIENTS; ++i)
		{
			if (m_watchInfo[i].timestamp <= 0.0f)
				continue;

			const float recentTime = 3.0f;
			if (gpGlobals->time - m_watchInfo[i].timestamp < recentTime)
			{
				if (m_watchInfo[i].isEnemy)
					++m_nearbyEnemyCount;
				else
					++m_nearbyFriendCount;
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
		static PlaceRank placeRank[ MAX_PLACES_PER_MAP ];
		int locCount = 0;

		PlaceRank common;
		common.place = 0;
		common.count = 0;

		for (i = 0; i < threatCount; ++i)
		{
			// find the area the player/bot is standing on
			CNavArea *area;
			CCSBot *bot = dynamic_cast<CCSBot *>(threat[i].enemy);
			if (bot != NULL && bot->IsBot())
			{
				area = bot->GetLastKnownArea();
			}
			else
			{
				area = TheNavAreaGrid.GetNearestNavArea(&threat[i].enemy->pev->origin);
			}

			if (area == NULL)
				continue;

			unsigned int threatLoc = area->GetPlace();
			if (!threatLoc)
				continue;

			// if place is already in set, increment count
			int j;
			for (j = 0; j < locCount; ++j)
			{
				if (placeRank[j].place == threatLoc)
					break;
			}

			if (j == locCount)
			{
				// new place
				if (locCount < MAX_PLACES_PER_MAP)
				{
					placeRank[ locCount ].place = threatLoc;
					placeRank[ locCount ].count = 1;

					if (common.count == 0)
						common = placeRank[locCount];

					++locCount;
				}
			}
			else
			{
				// others are in that place, increment
				++placeRank[j].count;

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
			return NULL;

		// otherwise, find the closest threat that without using shield
		int t;
		for (t = 0; t < threatCount; ++t)
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

/* <3d9f7d> ../cstrike/dlls/bot/cs_bot_vision.cpp:960 */
void CCSBot::UpdateReactionQueue(void)
{
	// zombies dont see any threats
	if (cv_bot_zombie.value > 0.0f)
		return;

	// find biggest threat at this instant
	CBasePlayer *threat = FindMostDangerousThreat();

	int now = m_enemyQueueIndex;

	// store a snapshot of its state at the end of the reaction time queue
	if (threat != NULL)
	{
		m_enemyQueue[ now ].player = threat;
		m_enemyQueue[ now ].isReloading = threat->IsReloading();
		m_enemyQueue[ now ].isProtectedByShield = threat->IsProtectedByShield();
	}
	else
	{
		m_enemyQueue[ now ].player = NULL;
		m_enemyQueue[ now ].isReloading = false;
		m_enemyQueue[ now ].isProtectedByShield = false;
	}

	// queue is round-robin
	++m_enemyQueueIndex;
	if (m_enemyQueueIndex >= MAX_ENEMY_QUEUE)
		m_enemyQueueIndex = 0;

	if (m_enemyQueueCount < MAX_ENEMY_QUEUE)
		++m_enemyQueueCount;

	// clamp reaction time to enemy queue size
	float reactionTime = GetProfile()->GetReactionTime();
	float maxReactionTime = (MAX_ENEMY_QUEUE * g_flBotFullThinkInterval) - 0.01f;
	if (reactionTime > maxReactionTime)
		reactionTime = maxReactionTime;

	// "rewind" time back to our reaction time
	int reactionTimeSteps = (int)((reactionTime / g_flBotFullThinkInterval) + 0.5f);

	int i = now - reactionTimeSteps;
	if (i < 0)
		i += MAX_ENEMY_QUEUE;

	m_enemyQueueAttendIndex = (byte)i;
}

// Return the most dangerous threat we are "conscious" of

/* <3da052> ../cstrike/dlls/bot/cs_bot_vision.cpp:1013 */
CBasePlayer *CCSBot::GetRecognizedEnemy(void)
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return NULL;

	return (CBasePlayer *)m_enemyQueue[ m_enemyQueueAttendIndex ].player;
}

// Return true if the enemy we are "conscious" of is reloading

/* <3da075> ../cstrike/dlls/bot/cs_bot_vision.cpp:1025 */
bool CCSBot::IsRecognizedEnemyReloading(void)
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return false;

	return m_enemyQueue[ m_enemyQueueAttendIndex ].isReloading;
}

// Return true if the enemy we are "conscious" of is hiding behind a shield

/* <3da09d> ../cstrike/dlls/bot/cs_bot_vision.cpp:1037 */
bool CCSBot::IsRecognizedEnemyProtectedByShield(void)
{
	if (m_enemyQueueAttendIndex >= m_enemyQueueCount)
		return false;

	return m_enemyQueue[ m_enemyQueueAttendIndex ].isProtectedByShield;
}

// Return distance to closest enemy we are "conscious" of

/* <3da0c5> ../cstrike/dlls/bot/cs_bot_vision.cpp:1049 */
float CCSBot::GetRangeToNearestRecognizedEnemy(void)
{
	const CBasePlayer *enemy = GetRecognizedEnemy();

	if (enemy != NULL)
	{
		return (pev->origin - enemy->pev->origin).Length();
	}

	return 99999999.9f;
}

// Blind the bot for the given duration

/* <3da170> ../cstrike/dlls/bot/cs_bot_vision.cpp:1063 */
void CCSBot::__MAKE_VHOOK(Blind)(float duration, float holdTime, float fadeTime, int alpha)
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

#ifdef HOOK_GAMEDLL

void (*pCCSBot__UpdateLookAngles)(void);
void __declspec(naked) CCSBot::UpdateLookAngles(void)
{
	__asm { jmp pCCSBot__UpdateLookAngles }
}

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
