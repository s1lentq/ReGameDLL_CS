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

#pragma once

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

class CNavPath
{
public:
	CNavPath() { m_segmentCount = 0; }

	struct PathSegment
	{
		CNavArea *area;				// the area along the path
		NavTraverseType how;		// how to enter this area from the previous one
		Vector pos;					// our movement goal position at this point in the path
		const CNavLadder *ladder;	// if "how" refers to a ladder, this is it
	};

	const PathSegment *operator[](int i) { return (i >= 0 && i < m_segmentCount) ? &m_path[i] : nullptr; }
	int GetSegmentCount() const { return m_segmentCount; }
	const Vector &GetEndpoint() const { return m_path[m_segmentCount - 1].pos; }

	bool IsAtEnd(const Vector &pos) const;									// return true if position is at the end of the path
	float GetLength() const;												// return length of path from start to finish
	bool GetPointAlongPath(float distAlong, Vector *pointOnPath) const;		// return point a given distance along the path - if distance is out of path bounds, point is clamped to start/end

	// return the node index closest to the given distance along the path without going over - returns (-1) if error
	int GetSegmentIndexAlongPath(float distAlong) const;

	bool IsValid() const { return (m_segmentCount > 0); }
	void Invalidate() { m_segmentCount = 0; }

	// draw the path for debugging
	void Draw();

	// compute closest point on path to given point
	bool FindClosestPointOnPath(const Vector *worldPos, int startIndex, int endIndex, Vector *close) const;

	void Optimize();

	// Compute shortest path from 'start' to 'goal' via A* algorithm
	template<typename CostFunctor>
	bool Compute(const Vector *start, const Vector *goal, CostFunctor &costFunc)
	{
		Invalidate();

		if (!start || !goal)
			return false;

		CNavArea *startArea = TheNavAreaGrid.GetNearestNavArea(start);
		if (!startArea)
			return false;

		CNavArea *goalArea = TheNavAreaGrid.GetNavArea(goal);

		// if we are already in the goal area, build trivial path
		if (startArea == goalArea)
		{
			BuildTrivialPath(start, goal);
			return true;
		}

		// make sure path end position is on the ground
		Vector pathEndPosition = *goal;

		if (goalArea)
			pathEndPosition.z = goalArea->GetZ(&pathEndPosition);
		else
			GetGroundHeight(&pathEndPosition, &pathEndPosition.z);

		// Compute shortest path to goal
		CNavArea *closestArea;
		bool pathToGoalExists = NavAreaBuildPath(startArea, goalArea, goal, costFunc, &closestArea);

		CNavArea *effectiveGoalArea = (pathToGoalExists) ? goalArea : closestArea;

		// Build path by following parent links
		int count = 0;
		CNavArea *area;
		for (area = effectiveGoalArea; area; area = area->GetParent())
			count++;

		// save room for endpoint
		if (count > MAX_PATH_SEGMENTS - 1)
			count = MAX_PATH_SEGMENTS - 1;

		if (count == 0)
			return false;

		if (count == 1)
		{
			BuildTrivialPath(start, goal);
			return true;
		}

		m_segmentCount = count;
		for (area = effectiveGoalArea; count && area; area = area->GetParent())
		{
			count--;
			m_path[count].area = area;
			m_path[count].how = area->GetParentHow();
		}

		// compute path positions
		if (ComputePathPositions() == false)
		{
			Invalidate();
			return false;
		}

		// append path end position
		m_path[m_segmentCount].area = effectiveGoalArea;
		m_path[m_segmentCount].pos = pathEndPosition;
		m_path[m_segmentCount].ladder = nullptr;
		m_path[m_segmentCount].how = NUM_TRAVERSE_TYPES;
		m_segmentCount++;

		return true;
	}

private:
	enum { MAX_PATH_SEGMENTS = 256 };
	PathSegment m_path[MAX_PATH_SEGMENTS];
	int m_segmentCount;

	bool ComputePathPositions();									// determine actual path positions
	bool BuildTrivialPath(const Vector *start, const Vector *goal);	// utility function for when start and goal are in the same area
	int FindNextOccludedNode(int anchor);							// used by Optimize()
};

// Monitor improv movement and determine if it becomes stuck
class CStuckMonitor
{
public:
	CStuckMonitor();

	void Reset();
	void Update(CImprov *improv);

	bool IsStuck()      const { return m_isStuck; }
	float GetDuration() const { return m_isStuck ? m_stuckTimer.GetElapsedTime() : 0.0f; }

private:
	bool m_isStuck;				// if true, we are stuck
	Vector m_stuckSpot;			// the location where we became stuck
	IntervalTimer m_stuckTimer;	// how long we have been stuck

	enum { MAX_VEL_SAMPLES = 5 };

	float m_avgVel[MAX_VEL_SAMPLES];
	int m_avgVelIndex;
	int m_avgVelCount;
	Vector m_lastCentroid;
	float m_lastTime;
};

// The CNavPathFollower class implements path following behavior
class CNavPathFollower
{
public:
	CNavPathFollower();

	void SetImprov(CImprov *improv) { m_improv = improv; }
	void SetPath(CNavPath *path) { m_path = path; }
	void Reset();

	void Update(float deltaT, bool avoidObstacles = true);						// move improv along path
	void Debug(bool status) { m_isDebug = status; }								// turn debugging on/off

	bool IsStuck() const { return m_stuckMonitor.IsStuck(); }					// return true if improv is stuck
	void ResetStuck() { m_stuckMonitor.Reset(); }
	float GetStuckDuration() const { return m_stuckMonitor.GetDuration(); }		// return how long we've been stuck

	void FeelerReflexAdjustment(Vector *goalPosition, float height = -1.0f);	// adjust goal position if "feelers" are touched

private:
	int FindOurPositionOnPath(Vector *close, bool local) const;			// return the closest point to our current position on current path
	int FindPathPoint(float aheadRange, Vector *point, int *prevIndex);	// compute a point a fixed distance ahead along our path.

	CImprov *m_improv;		// who is doing the path following
	CNavPath *m_path;		// the path being followed
	int m_segmentIndex;		// the point on the path the improv is moving towards
	int m_behindIndex;		// index of the node on the path just behind us
	Vector m_goal;			// last computed follow goal
	bool m_isLadderStarted;
	bool m_isDebug;
	CStuckMonitor m_stuckMonitor;
};
