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

#include <list>

class CNavArea;

void DestroyHidingSpots();
void StripNavigationAreas();
bool SaveNavigationMap(const char *filename);
NavErrorType LoadNavigationMap();
void DestroyNavigationMap();

enum NavEditCmdType
{
	EDIT_NONE,
	EDIT_DELETE,				// delete current area
	EDIT_SPLIT,					// split current area
	EDIT_MERGE,					// merge adjacent areas
	EDIT_JOIN,					// define connection between areas
	EDIT_BREAK,					// break connection between areas
	EDIT_MARK,					// mark an area for further operations
	EDIT_ATTRIB_CROUCH,			// toggle crouch attribute on current area
	EDIT_ATTRIB_JUMP,			// toggle jump attribute on current area
	EDIT_ATTRIB_PRECISE,		// toggle precise attribute on current area
	EDIT_ATTRIB_NO_JUMP,		// toggle inhibiting discontinuity jumping in current area
	EDIT_BEGIN_AREA,			// begin creating a new nav area
	EDIT_END_AREA,				// end creation of the new nav area
	EDIT_CONNECT,				// connect marked area to selected area
	EDIT_DISCONNECT,			// disconnect marked area from selected area
	EDIT_SPLICE,				// create new area in between marked and selected areas
	EDIT_TOGGLE_PLACE_MODE,		// switch between normal and place editing
	EDIT_TOGGLE_PLACE_PAINTING,	// switch between "painting" places onto areas
	EDIT_PLACE_FLOODFILL,		// floodfill areas out from current area
	EDIT_PLACE_PICK,			// "pick up" the place at the current area
	EDIT_MARK_UNNAMED,			// mark an unnamed area for further operations
	EDIT_WARP_TO_MARK,			// warp a spectating local player to the selected mark
	EDIT_SELECT_CORNER,			// select a corner on the current area
	EDIT_RAISE_CORNER,			// raise a corner on the current area
	EDIT_LOWER_CORNER,			// lower a corner on the current area
};

enum RouteType
{
	FASTEST_ROUTE,
	SAFEST_ROUTE,
};

union NavConnect
{
	unsigned int id;
	CNavArea *area;

	bool operator==(const NavConnect &other) const { return (area == other.area) ? true : false; }
};

typedef std::list<NavConnect> NavConnectList;

enum LadderDirectionType
{
	LADDER_UP = 0,
	LADDER_DOWN,
	NUM_LADDER_DIRECTIONS
};

class CNavLadder
{
public:
	CNavLadder()
	{
		m_topForwardArea = nullptr;
		m_topRightArea = nullptr;
		m_topLeftArea = nullptr;
		m_topBehindArea = nullptr;
		m_bottomArea = nullptr;
		m_entity = nullptr;
	}

	Vector m_top;
	Vector m_bottom;
	float m_length;
	NavDirType m_dir;
	Vector2D m_dirVector;
	CBaseEntity *m_entity;

	CNavArea *m_topForwardArea;
	CNavArea *m_topLeftArea;
	CNavArea *m_topRightArea;
	CNavArea *m_topBehindArea;
	CNavArea *m_bottomArea;

	bool m_isDangling;

	void OnDestroyNotify(CNavArea *dead)
	{
		if (dead == m_topForwardArea)
			m_topForwardArea = nullptr;

		if (dead == m_topLeftArea)
			m_topLeftArea = nullptr;

		if (dead == m_topRightArea)
			m_topRightArea = nullptr;

		if (dead == m_topBehindArea)
			m_topBehindArea = nullptr;

		if (dead == m_bottomArea)
			m_bottomArea = nullptr;
	}
};

typedef std::list<CNavLadder *> NavLadderList;
extern NavLadderList TheNavLadderList;

class HidingSpot
{
public:
	HidingSpot();
	HidingSpot(const Vector *pos, unsigned char flags);

	enum
	{
		IN_COVER = 0x01,
		GOOD_SNIPER_SPOT = 0x02,
		IDEAL_SNIPER_SPOT = 0x04
	};

	bool HasGoodCover() const { return (m_flags & IN_COVER) ? true : false; }
	bool IsGoodSniperSpot() const { return (m_flags & GOOD_SNIPER_SPOT) ? true : false; }
	bool IsIdealSniperSpot() const { return (m_flags & IDEAL_SNIPER_SPOT) ? true : false; }

	void SetFlags(unsigned char flags) { m_flags |= flags; }
	unsigned char GetFlags() const { return m_flags; }

	void Save(int fd, unsigned int version) const;
	void Load(SteamFile *file, unsigned int version);

	const Vector *GetPosition() const { return &m_pos; }
	unsigned int GetID() const { return m_id; }

	void Mark() { m_marker = m_masterMarker; }
	bool IsMarked() const { return (m_marker == m_masterMarker) ? true : false; }

	static void ChangeMasterMarker() { m_masterMarker++; }

private:
	friend void DestroyHidingSpots();

	Vector m_pos;
	unsigned int m_id;
	unsigned int m_marker;
	unsigned char m_flags;

	static unsigned int m_nextID;
	static unsigned int m_masterMarker;
};

typedef std::list<HidingSpot *> HidingSpotList;
extern HidingSpotList TheHidingSpotList;

struct SpotOrder
{
	float t;
	union
	{
		HidingSpot *spot;
		unsigned int id;
	};
};

typedef std::list<SpotOrder> SpotOrderList;

struct SpotEncounter
{
	NavConnect from;
	NavDirType fromDir;
	NavConnect to;
	NavDirType toDir;
	Ray path;				// the path segment
	SpotOrderList spotList;	// list of spots to look at, in order of occurrence
};

typedef std::list<SpotEncounter> SpotEncounterList;
typedef std::list<CNavArea *> NavAreaList;

// A CNavArea is a rectangular region defining a walkable area in the map
class CNavArea
{
public:
	CNavArea(CNavNode *nwNode, CNavNode *neNode, CNavNode *seNode, CNavNode *swNode);
	CNavArea();
	CNavArea(const Vector *corner, const Vector *otherCorner);
	CNavArea(const Vector *nwCorner, const Vector *neCorner, const Vector *seCorner, const Vector *swCorner);

	~CNavArea();

	void ConnectTo(CNavArea *area, NavDirType dir);		// connect this area to given area in given direction
	void Disconnect(CNavArea *area);					// disconnect this area from given area

	void Save(FILE *fp) const;
	void Save(int fd, unsigned int version);

	void Load(SteamFile *file, unsigned int version);
	NavErrorType PostLoad();

	unsigned int GetID() const { return m_id; }
	void SetAttributes(unsigned char bits) { m_attributeFlags = bits; }
	unsigned char GetAttributes() const { return m_attributeFlags; }
	void SetPlace(Place place) { m_place = place; }						// set place descriptor
	Place GetPlace() const { return m_place; }							// get place descriptor

	bool IsOverlapping(const Vector *pos) const;						// return true if 'pos' is within 2D extents of area
	bool IsOverlapping(const CNavArea *area) const;						// return true if 'area' overlaps our 2D extents
	bool IsOverlappingX(const CNavArea *area) const;					// return true if 'area' overlaps our X extent
	bool IsOverlappingY(const CNavArea *area) const;					// return true if 'area' overlaps our Y extent
	int GetPlayerCount(int teamID = 0, CBasePlayer *ignore = nullptr) const;			// return number of players with given teamID in this area (teamID == 0 means any/all)
	float GetZ(const Vector *pos) const;								// return Z of area at (x,y) of 'pos'
	float GetZ(float x, float y) const;									// return Z of area at (x,y) of 'pos'
	bool Contains(const Vector *pos) const;								// return true if given point is on or above this area, but no others
	bool IsCoplanar(const CNavArea *area) const;						// return true if this area and given area are approximately co-planar
	void GetClosestPointOnArea(const Vector *pos, Vector *close) const;	// return closest point to 'pos' on this area - returned point in 'close'
	float GetDistanceSquaredToPoint(const Vector *pos) const;			// return shortest distance between point and this area
	bool IsDegenerate() const;											// return true if this area is badly formed
	bool IsEdge(NavDirType dir) const;									// return true if there are no bi-directional links on the given side
	int GetAdjacentCount(NavDirType dir) const { return m_connect[dir].size(); }		// return number of connected areas in given direction
	CNavArea *GetAdjacentArea(NavDirType dir, int i) const;				// return the i'th adjacent area in the given direction
	CNavArea *GetRandomAdjacentArea(NavDirType dir) const;
	const NavConnectList *GetAdjacentList(NavDirType dir) const { return &m_connect[dir]; }
	bool IsConnected(const CNavArea *area, NavDirType dir) const;		// return true if given area is connected in given direction
	float ComputeHeightChange(const CNavArea *area);					// compute change in height from this area to given area

	const NavLadderList *GetLadderList(LadderDirectionType dir) const { return &m_ladder[dir]; }

	void ComputePortal(const CNavArea *to, NavDirType dir, Vector *center, float *halfWidth) const;							// compute portal to adjacent area
	void ComputeClosestPointInPortal(const CNavArea *to, NavDirType dir, const Vector *fromPos, Vector *closePos) const;	// compute closest point within the "portal" between to adjacent areas
	NavDirType ComputeDirection(Vector *point) const;									// return direction from this area to the given point

	// for hunting algorithm
	void SetClearedTimestamp(int teamID) { m_clearedTimestamp[teamID] = gpGlobals->time; }	// set this area's "clear" timestamp to now
	float GetClearedTimestamp(int teamID) { return m_clearedTimestamp[teamID]; }			// get time this area was marked "clear"

	// hiding spots
	const HidingSpotList *GetHidingSpotList() const { return &m_hidingSpotList; }

	void ComputeHidingSpots();							// analyze local area neighborhood to find "hiding spots" in this area - for map learning
	void ComputeSniperSpots();							// analyze local area neighborhood to find "sniper spots" in this area - for map learning

	SpotEncounter *GetSpotEncounter(const CNavArea *from, const CNavArea *to);	// given the areas we are moving between, return the spots we will encounter
	void ComputeSpotEncounters();							// compute spot encounter data - for map learning

	// danger
	void IncreaseDanger(int teamID, float amount);				// increase the danger of this area for the given team
	float GetDanger(int teamID);							// return the danger of this area (decays over time)

	float GetSizeX() const { return m_extent.hi.x - m_extent.lo.x; }
	float GetSizeY() const { return m_extent.hi.y - m_extent.lo.y; }

	const Extent *GetExtent() const { return &m_extent; }
	const Vector *GetCenter() const { return &m_center; }
	const Vector *GetCorner(NavCornerType corner) const;

	// approach areas
	struct ApproachInfo
	{
		NavConnect here;			// the approach area
		NavConnect prev;			// the area just before the approach area on the path
		NavTraverseType prevToHereHow;
		NavConnect next;			// the area just after the approach area on the path
		NavTraverseType hereToNextHow;
	};

	const ApproachInfo *GetApproachInfo(int i) const { return &m_approach[i]; }
	int GetApproachInfoCount() const { return m_approachCount; }
	void ComputeApproachAreas();						// determine the set of "approach areas" - for map learning

	// A* pathfinding algorithm
	static void MakeNewMarker()
	{
		if (++m_masterMarker == 0)
			m_masterMarker = 1;
	}
	void Mark() { m_marker = m_masterMarker; }
	BOOL IsMarked() const { return (m_marker == m_masterMarker) ? true : false; }
	void SetParent(CNavArea *parent, NavTraverseType how = NUM_TRAVERSE_TYPES) { m_parent = parent; m_parentHow = how; }
	CNavArea *GetParent() const { return m_parent; }
	NavTraverseType GetParentHow() const { return m_parentHow; }

	bool IsOpen() const;		// true if on "open list"
	void AddToOpenList();		// add to open list in decreasing value order
	void UpdateOnOpenList();	// a smaller value has been found, update this area on the open list
	void RemoveFromOpenList();
	static bool IsOpenListEmpty();
	static CNavArea *PopOpenList();	// remove and return the first element of the open list

	bool IsClosed() const;			// true if on "closed list"
	void AddToClosedList();			// add to the closed list
	void RemoveFromClosedList();

	static void ClearSearchLists();	// clears the open and closed lists for a new search

	void SetTotalCost(float value) { m_totalCost = value; }
	float GetTotalCost() const { return m_totalCost; }

	void SetCostSoFar(float value) { m_costSoFar = value; }
	float GetCostSoFar() const { return m_costSoFar; }

	// editing
	void Draw(byte red, byte green, byte blue, int duration = 50);							// draw area for debugging & editing
	void DrawConnectedAreas();
	void DrawMarkedCorner(NavCornerType corner, byte red, byte green, byte blue, int duration = 50);
	bool SplitEdit(bool splitAlongX, float splitEdge, CNavArea **outAlpha = nullptr, CNavArea **outBeta = nullptr);	// split this area into two areas at the given edge
	bool MergeEdit(CNavArea *adj);											// merge this area and given adjacent area
	bool SpliceEdit(CNavArea *other);										// create a new area between this area and given area
	void RaiseCorner(NavCornerType corner, int amount);						// raise/lower a corner (or all corners if corner == NUM_CORNERS)

	// ladders
	void AddLadderUp(CNavLadder *ladder) { m_ladder[LADDER_UP].push_back(ladder); }
	void AddLadderDown(CNavLadder *ladder) { m_ladder[LADDER_DOWN].push_back(ladder); }

private:
	friend void ConnectGeneratedAreas();
	friend void MergeGeneratedAreas();
	friend void MarkJumpAreas();
	friend bool SaveNavigationMap(const char *filename);
	friend NavErrorType LoadNavigationMap();
	friend void DestroyNavigationMap();
	friend void DestroyHidingSpots();
	friend void StripNavigationAreas();
	friend class CNavAreaGrid;
	friend class CCSBotManager;

	void Initialize();					// to keep constructors consistent
	static bool m_isReset;				// if true, don't bother cleaning up in destructor since everything is going away
	static unsigned int m_nextID;		// used to allocate unique IDs
	unsigned int m_id;					// unique area ID
	Extent m_extent;					// extents of area in world coords (NOTE: lo.z is not necessarily the minimum Z, but corresponds to Z at point (lo.x, lo.y), etc
	Vector m_center;					// centroid of area
	unsigned char m_attributeFlags;		// set of attribute bit flags (see NavAttributeType)
	Place m_place;						// place descriptor

	// height of the implicit corners
	float m_neZ;
	float m_swZ;

	enum { MAX_AREA_TEAMS = 2 };

	// for hunting
	float m_clearedTimestamp[MAX_AREA_TEAMS];	// time this area was last "cleared" of enemies

	// danger
	float m_danger[MAX_AREA_TEAMS];				// danger of this area, allowing bots to avoid areas where they died in the past - zero is no danger
	float m_dangerTimestamp[MAX_AREA_TEAMS];	// time when danger value was set - used for decaying
	void DecayDanger();

	// hiding spots
	HidingSpotList m_hidingSpotList;
	bool IsHidingSpotCollision(const Vector *pos) const;	// returns true if an existing hiding spot is too close to given position

	// encounter spots
	SpotEncounterList m_spotEncounterList;			// list of possible ways to move thru this area, and the spots to look at as we do
	void AddSpotEncounters(const CNavArea *from, NavDirType fromDir, const CNavArea *to, NavDirType toDir);

	// approach areas
	enum { MAX_APPROACH_AREAS = 16 };
	ApproachInfo m_approach[MAX_APPROACH_AREAS];
	unsigned char m_approachCount;

	void Strip();						// remove "analyzed" data from nav area

	// A* pathfinding algorithm
	static unsigned int m_masterMarker;
	unsigned int m_marker;				// used to flag the area as visited
	CNavArea *m_parent;					// the area just prior to this on in the search path
	NavTraverseType m_parentHow;		// how we get from parent to us
	float m_totalCost;					// the distance so far plus an estimate of the distance left
	float m_costSoFar;					// distance travelled so far

	static CNavArea *m_openList;
	CNavArea *m_nextOpen, *m_prevOpen;		// only valid if m_openMarker == m_masterMarker
	unsigned int m_openMarker;				// if this equals the current marker value, we are on the open list

	// connections to adjacent areas
	NavConnectList m_connect[NUM_DIRECTIONS];			// a list of adjacent areas for each direction
	NavLadderList m_ladder[NUM_LADDER_DIRECTIONS];		// list of ladders leading up and down from this area

	CNavNode *m_node[NUM_CORNERS];						// nav nodes at each corner of the area

	void FinishMerge(CNavArea *adjArea);				// recompute internal data once nodes have been adjusted during merge
	void MergeAdjacentConnections(CNavArea *adjArea);	// for merging with "adjArea" - pick up all of "adjArea"s connections
	void AssignNodes(CNavArea *area);					// assign internal nodes to the given area
	void FinishSplitEdit(CNavArea *newArea, NavDirType ignoreEdge);		// given the portion of the original area, update its internal data

	NavAreaList m_overlapList;							// list of areas that overlap this area
	void OnDestroyNotify(CNavArea *dead);				// invoked when given area is going away

	CNavArea *m_prevHash, *m_nextHash;					// for hash table in CNavAreaGrid
};

extern NavAreaList TheNavAreaList;

inline bool CNavArea::IsDegenerate() const
{
	return (m_extent.lo.x >= m_extent.hi.x || m_extent.lo.y >= m_extent.hi.y);
}

inline CNavArea *CNavArea::GetAdjacentArea(NavDirType dir, int i) const
{
	for (auto &con : m_connect[dir])
	{
		if (i == 0)
			return con.area;
		i--;
	}

	return nullptr;
}

inline bool CNavArea::IsOpen() const
{
	return (m_openMarker == m_masterMarker) ? true : false;
}

inline bool CNavArea::IsOpenListEmpty()
{
	return m_openList ? false : true;
}

inline CNavArea *CNavArea::PopOpenList()
{
	if (m_openList)
	{
		CNavArea *area = m_openList;

		// disconnect from list
		area->RemoveFromOpenList();
		return area;
	}

	return nullptr;
}

inline bool CNavArea::IsClosed() const
{
	if (IsMarked() && !IsOpen())
		return true;

	return false;
}

inline void CNavArea::AddToClosedList()
{
	Mark();
}

inline void CNavArea::RemoveFromClosedList()
{
	// since "closed" is defined as visited (marked) and not on open list, do nothing
}

// The CNavAreaGrid is used to efficiently access navigation areas by world position
// Each cell of the grid contains a list of areas that overlap it
// Given a world position, the corresponding grid cell is ( x/cellsize, y/cellsize )
class CNavAreaGrid
{
public:
	CNavAreaGrid();
	~CNavAreaGrid();

	void Reset();										// clear the grid to empty
	void Initialize(float minX, float maxX, float minY, float maxY);			// clear and reset the grid to the given extents
	void AddNavArea(CNavArea *area);											// add an area to the grid
	void RemoveNavArea(CNavArea *area);											// remove an area from the grid
	unsigned int GetNavAreaCount() const { return m_areaCount; }				// return total number of nav areas
	CNavArea *GetNavArea(const Vector *pos, float beneathLimt = 120.0f) const;	// given a position, return the nav area that IsOverlapping and is *immediately* beneath it
	CNavArea *GetNavAreaByID(unsigned int id) const;
	CNavArea *GetNearestNavArea(const Vector *pos, bool anyZ = false) const;

	Place GetPlace(const Vector *pos) const;						// return radio chatter place for given coordinate

private:
	const float m_cellSize;
	NavAreaList *m_grid;
	int m_gridSizeX;
	int m_gridSizeY;
	float m_minX;
	float m_minY;
	unsigned int m_areaCount;				// total number of nav areas

	enum { HASH_TABLE_SIZE = 256 };
	CNavArea *m_hashTable[HASH_TABLE_SIZE];				// hash table to optimize lookup by ID
	inline int ComputeHashKey(unsigned int id) const	// returns a hash key for the given nav area ID
	{
		return id & 0xFF;
	}

	inline int WorldToGridX(float wx) const
	{
		int x = (wx - m_minX) / m_cellSize;
		if (x < 0)
			x = 0;

		else if (x >= m_gridSizeX)
			x = m_gridSizeX - 1;

		return x;
	}
	inline int WorldToGridY(float wy) const
	{
		int y = (wy - m_minY) / m_cellSize;
		if (y < 0)
			y = 0;
		else if (y >= m_gridSizeY)
			y = m_gridSizeY - 1;

		return y;
	}
};

extern CNavAreaGrid TheNavAreaGrid;

class ShortestPathCost
{
public:
	float operator()(CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		if (!fromArea)
		{
			// first area in path, no cost
			return 0.0f;
		}
		else
		{
			// compute distance travelled along path so far
			float dist;

			if (ladder)
				dist = ladder->m_length;
			else
				dist = (*area->GetCenter() - *fromArea->GetCenter()).Length();

			float cost = dist + fromArea->GetCostSoFar();

			// if this is a "crouch" area, add penalty
			if (area->GetAttributes() & NAV_CROUCH)
			{
				const float crouchPenalty = 20.0f;
				cost += crouchPenalty * dist;
			}

			// if this is a "jump" area, add penalty
			if (area->GetAttributes() & NAV_JUMP)
			{
				const float jumpPenalty = 5.0f;
				cost += jumpPenalty * dist;
			}

			return cost;
		}
	}
};

// Find path from startArea to goalArea via an A* search, using supplied cost heuristic.
// If cost functor returns -1 for an area, that area is considered a dead end.
// This doesn't actually build a path, but the path is defined by following parent
// pointers back from goalArea to startArea.
// If 'closestArea' is non-NULL, the closest area to the goal is returned (useful if the path fails).
// If 'goalArea' is NULL, will compute a path as close as possible to 'goalPos'.
// If 'goalPos' is NULL, will use the center of 'goalArea' as the goal position.
// Returns true if a path exists.
template <typename CostFunctor>
bool NavAreaBuildPath(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, CostFunctor &costFunc, CNavArea **closestArea = nullptr)
{
	if (closestArea)
		*closestArea = nullptr;

	if (!startArea)
		return false;

	// If goalArea is NULL, this function will return the closest area to the goal.
	// However, if there is also no goal, we can't do anything.
	if (!goalArea && !goalPos)
	{
		return false;
	}

	startArea->SetParent(nullptr);

	// if we are already in the goal area, build trivial path
	if (startArea == goalArea)
	{
		goalArea->SetParent(nullptr);

		if (closestArea)
			*closestArea = goalArea;

		return true;
	}

	// determine actual goal position
	Vector actualGoalPos = (goalPos != nullptr) ? (*goalPos) : (*goalArea->GetCenter());

	// start search
	CNavArea::ClearSearchLists();

	// compute estimate of path length
	// TODO: Cost might work as "manhattan distance"
	startArea->SetTotalCost((*startArea->GetCenter() - actualGoalPos).Length());

	real_t initCost = costFunc(startArea, nullptr, nullptr);
	if (initCost < 0.0f)
		return false;

	startArea->SetCostSoFar(initCost);
	startArea->AddToOpenList();

	// keep track of the area we visit that is closest to the goal
	if (closestArea)
		*closestArea = startArea;

	float closestAreaDist = startArea->GetTotalCost();

	// do A* search
	while (!CNavArea::IsOpenListEmpty())
	{
		// get next area to check
		CNavArea *area = CNavArea::PopOpenList();

		// check if we have found the goal area
		if (area == goalArea)
		{
			if (closestArea)
				*closestArea = goalArea;

			return true;
		}

		// search adjacent areas
		bool searchFloor = true;
		int dir = NORTH;
		const NavConnectList *floorList = area->GetAdjacentList(NORTH);
		auto floorIter = floorList->begin();

		bool ladderUp = true;
		const NavLadderList *ladderList = nullptr;
		NavLadderList::const_iterator ladderIter;
		enum
		{
			AHEAD = 0,
			LEFT,
			RIGHT,
			BEHIND,
			NUM_TOP_DIRECTIONS
		};

		int ladderTopDir;
		while (true)
		{
			CNavArea *newArea;
			NavTraverseType how;
			const CNavLadder *ladder = nullptr;

			// Get next adjacent area - either on floor or via ladder
			if (searchFloor)
			{
				// if exhausted adjacent connections in current direction, begin checking next direction
				if (floorIter == floorList->end())
				{
					dir++;

					if (dir == NUM_DIRECTIONS)
					{
						// checked all directions on floor - check ladders next
						searchFloor = false;

						ladderList = area->GetLadderList(LADDER_UP);
						ladderIter = ladderList->begin();
						ladderTopDir = AHEAD;
					}
					else
					{
						// start next direction
						floorList = area->GetAdjacentList((NavDirType)dir);
						floorIter = floorList->begin();
					}
					continue;
				}

				newArea = (*floorIter).area;
				how = (NavTraverseType)dir;
				floorIter++;
			}
			// search ladders
			else
			{
				if (ladderIter == ladderList->end())
				{
					if (!ladderUp)
					{
						// checked both ladder directions - done
						break;
					}
					else
					{
						// check down ladders
						ladderUp = false;
						ladderList = area->GetLadderList(LADDER_DOWN);
						ladderIter = ladderList->begin();
					}
					continue;
				}

				if (ladderUp)
				{
					ladder = (*ladderIter);

					// cannot use this ladder if the ladder bottom is hanging above our head
					if (ladder->m_isDangling)
					{
						ladderIter++;
						continue;
					}

					// do not use BEHIND connection, as its very hard to get to when going up a ladder
					if (ladderTopDir == AHEAD)
						newArea = ladder->m_topForwardArea;
					else if (ladderTopDir == LEFT)
						newArea = ladder->m_topLeftArea;
					else if (ladderTopDir == RIGHT)
						newArea = ladder->m_topRightArea;
					else
					{
						ladderIter++;
						continue;
					}

					how = GO_LADDER_UP;
					ladderTopDir++;
				}
				else
				{
					newArea = (*ladderIter)->m_bottomArea;
					how = GO_LADDER_DOWN;
					ladder = (*ladderIter);
					ladderIter++;
				}

				if (!newArea)
					continue;
			}

			// don't backtrack
			if (newArea == area)
				continue;

			real_t newCostSoFar = costFunc(newArea, area, ladder);

			// check if cost functor says this area is a dead-end
			if (newCostSoFar < 0.0f)
				continue;

			if ((newArea->IsOpen() || newArea->IsClosed()) && newArea->GetCostSoFar() <= newCostSoFar)
			{
				// this is a worse path - skip it
				continue;
			}
			else
			{
				// compute estimate of distance left to go
				real_t newCostRemaining = (*newArea->GetCenter() - actualGoalPos).Length();

				// track closest area to goal in case path fails
				if (closestArea && newCostRemaining < closestAreaDist)
				{
					*closestArea = newArea;
					closestAreaDist = newCostRemaining;
				}

				newArea->SetParent(area, how);
				newArea->SetCostSoFar(newCostSoFar);
				newArea->SetTotalCost(newCostSoFar + newCostRemaining);

				if (newArea->IsClosed())
					newArea->RemoveFromClosedList();

				if (newArea->IsOpen())
				{
					// area already on open list, update the list order to keep costs sorted
					newArea->UpdateOnOpenList();
				}
				else
					newArea->AddToOpenList();
			}
		}

		// we have searched this area
		area->AddToClosedList();
	}

	return false;
}

// Compute distance between two areas. Return -1 if can't reach 'endArea' from 'startArea'.
template <typename CostFunctor>
real_t NavAreaTravelDistance(CNavArea *startArea, CNavArea *endArea, CostFunctor &costFunc)
{
	if (!startArea)
		return -1.0f;

	if (!endArea)
		return -1.0f;

	if (startArea == endArea)
		return 0.0f;

	// compute path between areas using given cost heuristic
	if (NavAreaBuildPath(startArea, endArea, nullptr, costFunc) == false)
		return -1.0f;

	// compute distance along path
	real_t distance = 0.0f;
	for (CNavArea *area = endArea; area->GetParent(); area = area->GetParent())
	{
		distance += (*area->GetCenter() - *area->GetParent()->GetCenter()).Length();
	}

	return distance;
}

// Compute distance from area to position. Return -1 if can't reach position.
template <typename CostFunctor>
float NavAreaTravelDistance(const Vector *startPos, CNavArea *startArea, const Vector *goalPos, CostFunctor &costFunc)
{
	if (!startArea || !startPos || !goalPos)
		return -1.0f;

	// compute path between areas using given cost heuristic
	CNavArea *goalArea = nullptr;
	if (NavAreaBuildPath(startArea, TheNavAreaGrid.GetNearestNavArea(goalPos), goalPos, costFunc, &goalArea) == false)
		return -1.0f;

	if (!goalArea)
		return -1.0f;

	// compute distance along path
	if (!goalArea->GetParent())
	{
		return (*goalPos - *startPos).Length();
	}
	else
	{
		CNavArea *area = goalArea->GetParent();
		float distance = (*goalPos - *area->GetCenter()).Length();

		for (; area->GetParent(); area = area->GetParent())
		{
			distance += (*area->GetCenter() - *area->GetParent()->GetCenter()).Length();
		}

		return distance;
	}
}

// Do a breadth-first search, invoking functor on each area.
// If functor returns 'true', continue searching from this area.
// If functor returns 'false', the area's adjacent areas are not explored (dead end).
// If 'maxRange' is 0 or less, no range check is done (all areas will be examined).
// NOTE: Returns all areas that overlap range, even partially
// TODO: Use ladder connections
//
// helper function
inline void AddAreaToOpenList(CNavArea *area, CNavArea *parent, const Vector *startPos, float maxRange)
{
	if (!area)
		return;

	if (!area->IsMarked())
	{
		area->Mark();
		area->SetTotalCost(0.0f);
		area->SetParent(parent);

		if (maxRange > 0.0f)
		{
			// make sure this area overlaps range
			Vector closePos;
			area->GetClosestPointOnArea(startPos, &closePos);
			if ((closePos - *startPos).Make2D().IsLengthLessThan(maxRange))
			{
				// compute approximate distance along path to limit travel range, too
				float distAlong = parent->GetCostSoFar();
				distAlong += (*area->GetCenter() - *parent->GetCenter()).Length();
				area->SetCostSoFar(distAlong);

				// allow for some fudge due to large size areas
				if (distAlong <= 1.5f * maxRange)
					area->AddToOpenList();
			}
		}
		else
		{
			// infinite range
			area->AddToOpenList();
		}
	}
}

template <typename Functor>
void SearchSurroundingAreas(CNavArea *startArea, const Vector *startPos, Functor &func, float maxRange = -1.0f)
{
	if (!startArea || !startPos)
		return;

	CNavArea::MakeNewMarker();
	CNavArea::ClearSearchLists();

	startArea->AddToOpenList();
	startArea->SetTotalCost(0.0f);
	startArea->SetCostSoFar(0.0f);
	startArea->SetParent(nullptr);
	startArea->Mark();

	while (!CNavArea::IsOpenListEmpty())
	{
		// get next area to check
		CNavArea *area = CNavArea::PopOpenList();

		// invoke functor on area
		if (func(area))
		{
			// explore adjacent floor areas
			for (int dir = 0; dir < NUM_DIRECTIONS; dir++)
			{
				int count = area->GetAdjacentCount((NavDirType)dir);
				for (int i = 0; i < count; i++)
				{
					CNavArea *adjArea = area->GetAdjacentArea((NavDirType)dir, i);
					AddAreaToOpenList(adjArea, area, startPos, maxRange);
				}
			}

			// explore adjacent areas connected by ladders
			NavLadderList::const_iterator ladderIt;

			// check up ladders
			const NavLadderList *ladderList = area->GetLadderList(LADDER_UP);
			if (ladderList)
			{
				for (ladderIt = ladderList->begin(); ladderIt != ladderList->end(); ladderIt++)
				{
					const CNavLadder *ladder = *ladderIt;

					// cannot use this ladder if the ladder bottom is hanging above our head
					if (ladder->m_isDangling)
					{
						continue;
					}

					// do not use BEHIND connection, as its very hard to get to when going up a ladder
					AddAreaToOpenList(ladder->m_topForwardArea, area, startPos, maxRange);
					AddAreaToOpenList(ladder->m_topLeftArea, area, startPos, maxRange);
					AddAreaToOpenList(ladder->m_topRightArea, area, startPos, maxRange);
				}
			}

			// check down ladders
			ladderList = area->GetLadderList(LADDER_DOWN);
			if (ladderList)
			{
				for (ladderIt = ladderList->begin(); ladderIt != ladderList->end(); ladderIt++)
				{
					const CNavLadder *ladder = *ladderIt;
					AddAreaToOpenList(ladder->m_bottomArea, area, startPos, maxRange);
				}
			}
		}
	}
}

// Apply the functor to all navigation areas
// If functor returns false, stop processing and return false.
template <typename Functor>
bool ForAllAreas(Functor &func)
{
	NavAreaList::iterator iter;
	for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); iter++)
	{
		CNavArea *area = (*iter);
		if (func(area) == false)
			return false;
	}

	return true;
}

// Fuctor that returns lowest cost for farthest away areas
// For use with FindMinimumCostArea()
class FarAwayFunctor
{
public:
	float operator()(CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		if (area == fromArea)
			return 9999999.9f;

		return 1.0f / (*fromArea->GetCenter() - *area->GetCenter()).Length();
	}
};

// Fuctor that returns lowest cost for farthest away areas
// For use with FindMinimumCostArea()
class FarAwayFromPositionFunctor
{
public:
	FarAwayFromPositionFunctor(const Vector *pos) { m_pos = pos; }

	float operator() (CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		return 1.0f / (*m_pos - *area->GetCenter()).Length();
	}

private:
	const Vector *m_pos;
};

// Pick a low-cost area of "decent" size
template <typename CostFunctor>
CNavArea *FindMinimumCostArea(CNavArea *startArea, CostFunctor &costFunc)
{
	const float minSize = 150.0f;

	// collect N low-cost areas of a decent size
	enum { NUM_CHEAP_AREAS = 32 };
	struct
	{
		CNavArea *area;
		float cost;
	}
	cheapAreaSet[NUM_CHEAP_AREAS];
	int cheapAreaSetCount = 0;

	NavAreaList::iterator iter;
	for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); iter++)
	{
		CNavArea *area = (*iter);

		// skip the small areas
		const Extent *extent = area->GetExtent();
		if (extent->hi.x - extent->lo.x < minSize || extent->hi.y - extent->lo.y < minSize)
			continue;

		// compute cost of this area
		float cost = costFunc(area, startArea, nullptr);

		if (cheapAreaSetCount < NUM_CHEAP_AREAS)
		{
			cheapAreaSet[cheapAreaSetCount].area = area;
			cheapAreaSet[cheapAreaSetCount++].cost = cost;
		}
		else
		{
			// replace most expensive cost if this is cheaper
			int expensive = 0;
			for (int i = 1; i < NUM_CHEAP_AREAS; i++)
			{
				if (cheapAreaSet[i].cost > cheapAreaSet[expensive].cost)
					expensive = i;
			}

			if (cheapAreaSet[expensive].cost > cost)
			{
				cheapAreaSet[expensive].area = area;
				cheapAreaSet[expensive].cost = cost;
			}
		}
	}
	if (cheapAreaSetCount)
	{
		// pick one of the areas at random
		return cheapAreaSet[RANDOM_LONG(0, cheapAreaSetCount - 1)].area;
	}
	else
	{
		// degenerate case - no decent sized areas - pick a random area
		int numAreas = TheNavAreaList.size();
		int which = RANDOM_LONG(0, numAreas - 1);

		NavAreaList::iterator iter;
		for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); iter++)
		{
			if (which-- == 0)
				break;
		}

		return (*iter);
	}
}

bool IsHidingSpotInCover(const Vector *spot);
void ClassifySniperSpot(HidingSpot *spot);
void DestroyHidingSpots();
void EditNavAreas(NavEditCmdType cmd);
bool GetGroundHeight(const Vector *pos, float *height, Vector *normal = nullptr);
bool GetSimpleGroundHeight(const Vector *pos, float *height, Vector *normal = nullptr);
CNavArea *GetMarkedArea();
void EditNavAreasReset();
void DrawHidingSpots(const CNavArea *area);
void IncreaseDangerNearby(int teamID, float amount, CNavArea *startArea, const Vector *pos, float maxRadius);
void DrawDanger();
bool IsSpotOccupied(CBaseEntity *me, const Vector *pos);	// if a player is at the given spot, return true
const Vector *FindNearbyHidingSpot(CBaseEntity *me, const Vector *pos, CNavArea *startArea, float maxRange = 1000.0f, bool isSniper = false, bool useNearest = false);
const Vector *FindNearbyRetreatSpot(CBaseEntity *me, const Vector *start, CNavArea *startArea, float maxRange = 1000.0f, int avoidTeam = 0, bool useCrouchAreas = true);

// return true if moving from "start" to "finish" will cross a player's line of fire
bool IsCrossingLineOfFire(const Vector &start, const Vector &finish, CBaseEntity *ignore = nullptr, int ignoreTeam = 0);
const Vector *FindRandomHidingSpot(CBaseEntity *me, Place place, bool isSniper = false);
HidingSpot *GetHidingSpotByID(unsigned int id);
void ApproachAreaAnalysisPrep();
void CleanupApproachAreaAnalysisPrep();
void DestroyLadders();
void DestroyNavigationMap();
void StripNavigationAreas();
CNavArea *FindFirstAreaInDirection(const Vector *start, NavDirType dir, float range, float beneathLimit, CBaseEntity *traceIgnore, Vector *closePos);
bool testJumpDown(const Vector *fromPos, const Vector *toPos);
void ConnectGeneratedAreas();
void MergeGeneratedAreas();
bool IsAreaRoughlySquare(const CNavArea *area);
void SplitX(CNavArea *area);
void SplitY(CNavArea *area);
void SquareUpAreas();
bool TestArea(CNavNode *node, int width, int height);
int BuildArea(CNavNode *node, int width, int height);
void BuildLadders();
void MarkJumpAreas();
void GenerateNavigationAreaMesh();
