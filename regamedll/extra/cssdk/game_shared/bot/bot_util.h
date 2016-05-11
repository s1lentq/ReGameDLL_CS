/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/
#pragma once

#define COS_TABLE_SIZE		256

#define RAD_TO_DEG(deg)		((deg) * 180.0 / M_PI)
#define DEG_TO_RAD(rad)		((rad) * M_PI / 180.0)

#define SIGN(num)		(((num) < 0) ? -1 : 1)
#define ABS(num)		(SIGN(num) * (num))

class CBasePlayer;
class BotProfile;

enum PriorityType
{
	PRIORITY_LOW, PRIORITY_MEDIUM, PRIORITY_HIGH, PRIORITY_UNINTERRUPTABLE
};

// Simple class for tracking intervals of game time
class IntervalTimer {
public:
	IntervalTimer() { m_timestamp = -1.0f; }
	void Reset() { m_timestamp = gpGlobals->time; }
	void Start() { m_timestamp = gpGlobals->time; }
	void Invalidate() { m_timestamp = -1.0f; }

	bool HasStarted() const { return (m_timestamp > 0.0f); }

	// if not started, elapsed time is very large
	float GetElapsedTime() const { return (HasStarted()) ? (gpGlobals->time - m_timestamp) : 99999.9f; }
	bool IsLessThen(float duration) const { return (gpGlobals->time - m_timestamp < duration) ? true : false; }
	bool IsGreaterThen(float duration) const { return (gpGlobals->time - m_timestamp > duration) ? true : false; }

private:
	float m_timestamp;
};

// Simple class for counting down a short interval of time
class CountdownTimer {
public:
	CountdownTimer() { m_timestamp = -1.0f; m_duration = 0.0f; }
	void Reset() { m_timestamp = gpGlobals->time + m_duration; }

	void Start(float duration) { m_timestamp = gpGlobals->time + duration; m_duration = duration; }
	bool HasStarted() const { return (m_timestamp > 0.0f); }

	void Invalidate() { m_timestamp = -1.0f; }
	bool IsElapsed() const { return (gpGlobals->time > m_timestamp); }

private:
	float m_duration;
	float m_timestamp;
};

// Return true if the given entity is valid
inline bool IsEntityValid(CBaseEntity *entity)
{
	if (entity == NULL)
		return false;

	if (FNullEnt(entity->pev))
		return false;

	if (FStrEq(STRING(entity->pev->netname), ""))
		return false;

	if (entity->pev->flags & FL_DORMANT)
		return false;

	return true;
}

// Given two line segments: startA to endA, and startB to endB, return true if they intesect
// and put the intersection point in "result".
// Note that this computes the intersection of the 2D (x,y) projection of the line segments.
inline bool IsIntersecting2D(const Vector &startA, const Vector &endA, const Vector &startB, const Vector &endB, Vector *result = NULL)
{
	float denom = (endA.x - startA.x) * (endB.y - startB.y) - (endA.y - startA.y) * (endB.x - startB.x);
	if (denom == 0.0f)
	{
		// parallel
		return false;
	}

	float numS = (startA.y - startB.y) * (endB.x - startB.x) - (startA.x - startB.x) * (endB.y - startB.y);
	if (numS == 0.0f)
	{
		// coincident
		return true;
	}

	float numT = (startA.y - startB.y) * (endA.x - startA.x) - (startA.x - startB.x) * (endA.y - startA.y);
	float s = numS / denom;
	if (s < 0.0f || s > 1.0f)
	{
		// intersection is not within line segment of startA to endA
		return false;
	}

	float t = numT / denom;
	if (t < 0.0f || t > 1.0f)
	{
		// intersection is not within line segment of startB to endB
		return false;
	}

	// compute intesection point
	if (result != NULL)
	{
		*result = startA + s * (endA - startA);
	}

	return true;
}
