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

class CNavPath {
public:
	CNavPath() { m_segmentCount = 0; }

	struct PathSegment
	{
		CNavArea *area;			// the area along the path
		NavTraverseType how;		// how to enter this area from the previous one
		Vector pos;			// our movement goal position at this point in the path
		const CNavLadder *ladder;	// if "how" refers to a ladder, this is it
	};

	const PathSegment *operator[](int i) { return (i >= 0 && i < m_segmentCount) ? &m_path[i] : NULL; }
	int GetSegmentCount() const { return m_segmentCount; }
	const Vector &GetEndpoint() const { return m_path[ m_segmentCount - 1 ].pos; }

	bool IsValid() const { return (m_segmentCount > 0); }
	void Invalidate() { m_segmentCount = 0; }
public:
	enum { MAX_PATH_SEGMENTS = 256 };
	PathSegment m_path[ MAX_PATH_SEGMENTS ];
	int m_segmentCount;

	bool ComputePathPositions();					// determine actual path positions
	bool BuildTrivialPath(const Vector *start, const Vector *goal);	// utility function for when start and goal are in the same area
	int FindNextOccludedNode(int anchor_);				// used by Optimize()
};

// Monitor improv movement and determine if it becomes stuck
class CStuckMonitor {
public:
	bool IsStuck() const { return m_isStuck; }
	float GetDuration() const { return m_isStuck ? m_stuckTimer.GetElapsedTime() : 0.0f; }
public:
	bool m_isStuck;			// if true, we are stuck
	Vector m_stuckSpot;		// the location where we became stuck
	IntervalTimer m_stuckTimer;	// how long we have been stuck

	enum { MAX_VEL_SAMPLES = 5 };

	float m_avgVel[ MAX_VEL_SAMPLES ];
	int m_avgVelIndex;
	int m_avgVelCount;
	Vector m_lastCentroid;
	float m_lastTime;
};

// The CNavPathFollower class implements path following behavior
class CNavPathFollower {
public:
	void SetImprov(CImprov *improv) { m_improv = improv; }
	void SetPath(CNavPath *path) { m_path = path; }

	void Debug(bool status) { m_isDebug = status; }					// turn debugging on/off
public:
	int FindOurPositionOnPath(Vector *close, bool local) const;		// return the closest point to our current position on current path
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
