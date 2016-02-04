#include "precompiled.h"

// Listen for enemy noises, and determine if we should react to them.
// Returns true if heard a noise and should move to investigate.

/* <354545> ../cstrike/dlls/bot/cs_bot_listen.cpp:17 */
bool CCSBot::ShouldInvestigateNoise(float *retNoiseDist)
{
	if (m_isNoiseTravelRangeChecked)
		return false;

	// don't investigate noises during safe time
	if (!IsWellPastSafe())
		return false;

	// if our disposition is not to investigate, dont investigate
	if (GetDisposition() != ENGAGE_AND_INVESTIGATE)
		return false;

	// listen for enemy noises
	if (IsNoiseHeard() && gpGlobals->time - m_noiseCheckTimestamp >= 0.25f)
	{
		m_noiseCheckTimestamp = gpGlobals->time;
		Vector toNoise = m_noisePosition - pev->origin;
		float noiseDist = toNoise.Length();

		float const oneStoreyHeight = 120.0f;
		if (abs(int64(toNoise.z)) > oneStoreyHeight)
		{
			PathCost pc(this);
			float travelDistToNoise = NavAreaTravelDistance(m_lastKnownArea, m_noiseArea, pc);
			m_isNoiseTravelRangeChecked = true;

			const float tooFar = 1500.0f;
			if (travelDistToNoise < 0.0f || travelDistToNoise > tooFar)
				return false;

			if (noiseDist <= travelDistToNoise)
				noiseDist = travelDistToNoise;
		}

		// if we are hiding, only react to noises very nearby, depending on how aggressive we are
		if (IsAtHidingSpot() && noiseDist > 100.0f + 400.0f * GetProfile()->GetAggression())
			return false;

		// chance of investigating is inversely proportional to distance
		const float maxNoiseDist = 2000.0f;
		float chance = (1.0f - (noiseDist / maxNoiseDist));

		// modify chance by number of friends remaining
		// if we have lots of friends, presumably one of them is closer and will check it out
		if (GetFriendsRemaining() >= 3)
		{
			float friendFactor = 0.05f * GetFriendsRemaining();
			if (friendFactor > 0.5f)
				friendFactor = 0.5f;

			chance -= friendFactor;
		}

		if (RANDOM_FLOAT(0.0f, 1.0f) <= chance)
		{
			if (retNoiseDist)
				*retNoiseDist = noiseDist;

			return true;
		}
	}

	return false;
}

// Return true if we hear nearby threatening enemy gunfire within given range
// -1 == infinite range

/* <354c8d> ../cstrike/dlls/bot/cs_bot_listen.cpp:104 */
bool CCSBot::CanHearNearbyEnemyGunfire(float range) const
{
	// only attend to noise if it just happened
	if (gpGlobals->time - m_noiseTimestamp > 0.5f)
		return false;

	// gunfire is high priority
	if (m_noisePriority < PRIORITY_HIGH)
		return false;

	// check noise range
	if (range > 0.0f && (pev->origin - m_noisePosition).IsLengthGreaterThan(range))
		return false;

	// if we dont have line of sight, it's not threatening (cant get shot)
	if (!CanSeeNoisePosition())
		return false;

	if (IsAttacking() && m_enemy != NULL)
	{
		// gunfire is only threatening if it is closer than our current enemy
		float gunfireDistSq = (m_noisePosition - pev->origin).LengthSquared();
		float enemyDistSq = (m_enemy->pev->origin - pev->origin).LengthSquared();
		const float muchCloserSq = 100.0f * 100.0f;
		if (gunfireDistSq > enemyDistSq - muchCloserSq)
			return false;
	}

	return true;
}

// Return true if we directly see where we think the noise came from
// NOTE: Dont check FOV, since this is used to determine if we should turn our head to look at the noise
// NOTE: Dont use IsVisible(), because smoke shouldnt cause us to not look toward noises

/* <354e7b> ../cstrike/dlls/bot/cs_bot_listen.cpp:141 */
bool CCSBot::CanSeeNoisePosition() const
{
	TraceResult result;
	UTIL_TraceLine(GetEyePosition(), m_noisePosition + Vector(0, 0, HalfHumanHeight), ignore_monsters, ignore_glass, ENT(pev), &result);

	if (result.flFraction == 1.0f)
	{
		// we can see the source of the noise
		return true;
	}

	return false;
}

// Return true if we decided to look towards the most recent noise source
// Assumes m_noisePosition is valid.

/* <354f48> ../cstrike/dlls/bot/cs_bot_listen.cpp:160 */
bool CCSBot::UpdateLookAtNoise()
{
	// make sure a noise exists
	if (!IsNoiseHeard() || gpGlobals->time - m_noiseTimestamp > 0.5f)
		return false;

	bool nearbyThreat = false;
	float const recentThreatTime = 5.0f;
	if (GetTimeSinceLastSawEnemy() < recentThreatTime)
	{
		const float closeThreatRange = 750.0f;
		if ((pev->origin - m_lastEnemyPosition).IsLengthLessThan(closeThreatRange))
		{
			nearbyThreat = true;
		}
	}

	Vector spot;

	// if we have clear line of sight to noise position, look directly at it
	if ((!IsAtHidingSpot() && nearbyThreat) || CanSeeNoisePosition())
	{
		// TODO: adjust noise Z to keep consistent with current height while fighting
		spot = m_noisePosition + Vector(0, 0, HalfHumanHeight);
	}
	else
	{
		// line of sight is blocked, bend it

		if (m_approachPointCount == 0)
			return false;

		int nearIdx = -1;
		float nearRangeSq = 9.9999998e10f;

		for (int i = 0; i < m_approachPointCount; ++i)
		{
			float distanceSq = (m_approachPoint[i] - m_noisePosition).LengthSquared();

			if (distanceSq < nearRangeSq)
			{
				nearRangeSq = distanceSq;
				nearIdx = i;
			}
		}

		if (nearIdx != -1)
		{
			// line of sight is blocked, bend it
			if (BendLineOfSight(&pev->origin, &m_approachPoint[nearIdx], &spot) == false)
				return false;

			spot.z += HalfHumanHeight;
		}
		else
		{
			// prior bend failed
			return false;
		}
	}

	// it's always important to look at enemy noises, because they come from ... enemies!
	PriorityType pri = (GetNoisePriority() == PRIORITY_HIGH) ? PRIORITY_HIGH : PRIORITY_MEDIUM;

	// look longer if we're hiding
	if (IsAtHidingSpot())
	{
		// if there is only one enemy left, look for a long time
		if (GetEnemiesRemaining() == 1)
		{
			SetLookAt("Noise", &spot, pri, RANDOM_FLOAT(5.0f, 15.0f), true);
		}
		else
		{
			SetLookAt("Noise", &spot, pri, RANDOM_FLOAT(2.0f, 5.0f), true);
		}
	}
	else
	{
		SetLookAt("Noise", &spot, pri, RANDOM_FLOAT(1.0f, 2.0f), true);
	}

	return true;
}
