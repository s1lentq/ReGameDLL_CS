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

#ifndef NAV_AREA_H
#define NAV_AREA_H
#ifdef _WIN32
#pragma once
#endif

#include <list>
//#include "nav.h"

class CNavArea;

enum
{
	MAX_BLOCKED_AREAS = 256
};

void DestroyHidingSpots(void);
NOBODY void StripNavigationAreas(void);
//bool SaveNavigationMap(const char *filename);
//NavErrorType LoadNavigationMap(void);
NOBODY void DestroyNavigationMap(void);

enum NavEditCmdType
{
	EDIT_NONE,
	EDIT_DELETE,
	EDIT_SPLIT,
	EDIT_MERGE,
	EDIT_JOIN,
	EDIT_BREAK,
	EDIT_MARK,
	EDIT_ATTRIB_CROUCH,
	EDIT_ATTRIB_JUMP,
	EDIT_ATTRIB_PRECISE,
	EDIT_ATTRIB_NO_JUMP,
	EDIT_BEGIN_AREA,
	EDIT_END_AREA,
	EDIT_CONNECT,
	EDIT_DISCONNECT,
	EDIT_SPLICE,
	EDIT_TOGGLE_PLACE_MODE,
	EDIT_TOGGLE_PLACE_PAINTING,
	EDIT_PLACE_FLOODFILL,
	EDIT_PLACE_PICK,
	EDIT_MARK_UNNAMED,
	EDIT_WARP_TO_MARK,
	EDIT_SELECT_CORNER,
	EDIT_RAISE_CORNER,
	EDIT_LOWER_CORNER,
};

//#define NO_CROUCH_SPOTS false
//class CBasePlayer;
//class CBaseEntity;

enum RouteType
{
	FASTEST_ROUTE,
	SAFEST_ROUTE,
};

/* <4c1845> ../game_shared/bot/nav_area.h:35 */
union NavConnect
{
	unsigned int id;
	CNavArea *area;

	/* <4c26c6> ../game_shared/bot/nav_area.h:40 */
	bool operator==(const NavConnect &other) const
	{
		return (area == other.area) ? true : false;
	}
};

typedef std::list<NavConnect> NavConnectList;

enum LadderDirectionType
{
	LADDER_UP = 0,
	LADDER_DOWN,
	NUM_LADDER_DIRECTIONS
};


/* <4c2fda> ../game_shared/bot/nav_area.h:63 */
class CNavLadder
{
public:
	CNavLadder(void)
	{
		m_topForwardArea = NULL;
		m_topRightArea = NULL;
		m_topLeftArea = NULL;
		m_topBehindArea = NULL;
		m_bottomArea = NULL;
		m_entity = NULL;
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

	/* <4c2dc0> ../game_shared/bot/nav_area.h:88 */
	void OnDestroyNotify(CNavArea *dead)
	{
		if (dead == m_topForwardArea)
			m_topForwardArea = NULL;

		if (dead == m_topLeftArea)
			m_topLeftArea = NULL;

		if (dead == m_topRightArea)
			m_topRightArea = NULL;

		if (dead == m_topBehindArea)
			m_topBehindArea = NULL;

		if (dead == m_bottomArea)
			m_bottomArea = NULL;
	}
};/* size: 68, cachelines: 2, members: 12 */

typedef std::list<CNavLadder *> NavLadderList;

class HidingSpot
{
public:
	HidingSpot(void);
	HidingSpot(const Vector *pos, unsigned char flags);

	enum
	{
		IN_COVER = 0x01,
		GOOD_SNIPER_SPOT = 0x02,
		IDEAL_SNIPER_SPOT = 0x04
	};

	bool HasGoodCover(void) const
	{
		return (m_flags & IN_COVER) ? true : false;
	}
	bool IsGoodSniperSpot(void) const
	{
		return (m_flags & GOOD_SNIPER_SPOT) ? true : false;
	}
	bool IsIdealSniperSpot(void) const
	{
		return (m_flags & IDEAL_SNIPER_SPOT) ? true : false;
	}
	void SetFlags(unsigned char flags)
	{
		m_flags |= flags;
	}
	unsigned char GetFlags(void) const
	{
		return m_flags;
	}
	void Save(int fd, unsigned int version) const;
	void Load(SteamFile *file, unsigned int version);

	const Vector *GetPosition(void) const
	{
		return &m_pos;
	}
	unsigned int GetID(void) const
	{
		return m_id;
	}
	void Mark(void)
	{
#ifndef HOOK_GAMEDLL
		m_marker = m_masterMarker;
#else
		m_marker = (*m_masterMarker);
#endif // HOOK_GAMEDLL
	}
	bool IsMarked(void) const
	{
#ifndef HOOK_GAMEDLL
		return (m_marker == m_masterMarker) ? true : false;
#else
		return (m_marker == (*m_masterMarker)) ? true : false;
#endif // HOOK_GAMEDLL
	}
	static void ChangeMasterMarker(void)
	{
#ifndef HOOK_GAMEDLL
		++m_masterMarker;
#else
		++(*m_masterMarker);
#endif // HOOK_GAMEDLL
	}

private:
	friend void DestroyHidingSpots(void);

	Vector m_pos;
	unsigned int m_id;
	unsigned int m_marker;
	unsigned char m_flags;

#ifndef HOOK_GAMEDLL
	static unsigned int m_nextID;
	static unsigned int m_masterMarker;
#else
public:
	static unsigned int (*m_nextID);
	static unsigned int (*m_masterMarker);
#endif // HOOK_GAMEDLL

};/* size: 24, cachelines: 1, members: 6 */

typedef std::list<HidingSpot *> HidingSpotList;

/* <4ec0bd> ../game_shared/bot/nav_area.h:164 */
struct SpotOrder
{
	float t;
	union
	{
		HidingSpot *spot;
		unsigned int id;
	};
};/* size: 8, cachelines: 1, members: 2 */

typedef std::list<SpotOrder> SpotOrderList;

/* <4c3a51> ../game_shared/bot/nav_area.h:179 */
struct SpotEncounter
{
	NavConnect from;
	NavDirType fromDir;
	NavConnect to;
	NavDirType toDir;
	Ray path;
	SpotOrderList spotList;
};/* size: 48, cachelines: 1, members: 6 */

typedef std::list<SpotEncounter> SpotEncounterList;
typedef std::list<CNavArea *> NavAreaList;

class CNavArea
{
public:
	CNavArea(CNavNode *nwNode, CNavNode *neNode, CNavNode *seNode, CNavNode *swNode);
	CNavArea(void);
	CNavArea(const Vector *corner, const Vector *otherCorner);
	CNavArea(const Vector *nwCorner, const Vector *neCorner, const Vector *seCorner, const Vector *swCorner);

	~CNavArea();

	void ConnectTo(CNavArea *area, NavDirType dir);
	void Disconnect(CNavArea *area);

	void Save(FILE *fp) const;
	void Save(int fd, unsigned int version);

	void Load(SteamFile *file, unsigned int version);
	NavErrorType PostLoad(void);

	unsigned int GetID(void) const
	{
		return m_id;
	}
	void SetAttributes(unsigned char bits)
	{
		m_attributeFlags = bits;
	}
	unsigned char GetAttributes(void) const
	{
		return m_attributeFlags;
	}
	void SetPlace(Place place)
	{
		m_place = place;
	}
	Place GetPlace(void) const
	{
		return m_place;
	}

	bool IsOverlapping(const Vector *pos) const;
	bool IsOverlapping(const CNavArea *area) const;
	bool IsOverlappingX(const CNavArea *area) const;
	bool IsOverlappingY(const CNavArea *area) const;
	int GetPlayerCount(int teamID = 0, CBasePlayer *ignore = NULL) const;
	float GetZ(const Vector *pos) const;
	float GetZ(float x, float y) const;
	bool Contains(const Vector *pos) const;
	bool IsCoplanar(const CNavArea *area) const;
	void GetClosestPointOnArea(const Vector *pos, Vector *close) const;
	float GetDistanceSquaredToPoint(const Vector *pos) const;
	bool IsDegenerate(void) const;

	bool IsEdge(NavDirType dir) const;

	int GetAdjacentCount(NavDirType dir) const
	{
		return m_connect[dir].size();
	}
	CNavArea *GetAdjacentArea(NavDirType dir, int i) const;
	CNavArea *GetRandomAdjacentArea(NavDirType dir) const;

	const NavConnectList *GetAdjacentList(NavDirType dir) const
	{
		return &m_connect[dir];
	}
	bool IsConnected(const CNavArea *area, NavDirType dir) const;
	float ComputeHeightChange(const CNavArea *area);

	const NavLadderList *GetLadderList(LadderDirectionType dir) const
	{
		return &m_ladder[dir];
	}

	void ComputePortal(const CNavArea *to, NavDirType dir, Vector *center, float *halfWidth) const;
	void ComputeClosestPointInPortal(const CNavArea *to, NavDirType dir, const Vector *fromPos, Vector *closePos) const;
	NavDirType ComputeDirection(Vector *point) const;

	void SetClearedTimestamp(int teamID)
	{
		m_clearedTimestamp[teamID] = gpGlobals->time;
	}
	float GetClearedTimestamp(int teamID)
	{
		return m_clearedTimestamp[teamID];
	}
	const HidingSpotList *GetHidingSpotList(void) const
	{
		return &m_hidingSpotList;
	}
	void ComputeHidingSpots(void);
	void ComputeSniperSpots(void);

	SpotEncounter *GetSpotEncounter(const CNavArea *from, const CNavArea *to);
	void ComputeSpotEncounters(void);
	void IncreaseDanger(int teamID, float amount);

	float GetDanger(int teamID);
	float GetSizeX(void) const
	{
		return m_extent.hi.x - m_extent.lo.x;
	}
	float GetSizeY(void) const
	{
		return m_extent.hi.y - m_extent.lo.y;
	}
	const Extent *GetExtent(void) const
	{
		return &m_extent;
	}
	const Vector *GetCenter(void) const
	{
		return &m_center;
	}
	const Vector *GetCorner(NavCornerType corner) const;

	struct ApproachInfo
	{
		NavConnect here;
		NavConnect prev;
		NavTraverseType prevToHereHow;
		NavConnect next;
		NavTraverseType hereToNextHow;
	};

	const ApproachInfo *GetApproachInfo(int i) const
	{
		return &m_approach[i];
	}
	int GetApproachInfoCount(void) const
	{
		return m_approachCount;
	}
	void ComputeApproachAreas(void);
	static void MakeNewMarker(void)
	{
#ifndef HOOK_GAMEDLL
		++m_masterMarker;
		if (m_masterMarker == 0)
			m_masterMarker = 1;
#else
		++(*m_masterMarker);
		if ((*m_masterMarker) == 0)
			(*m_masterMarker) = 1;
#endif // HOOK_GAMEDLL
	}
	void Mark(void)
	{
#ifndef HOOK_GAMEDLL
		m_marker = m_masterMarker;
#else
		m_marker = (*m_masterMarker);
#endif // HOOK_GAMEDLL
	}
	BOOL IsMarked(void) const
	{
#ifndef HOOK_GAMEDLL
		return (m_marker == m_masterMarker) ? true : false;
#else
		return (m_marker == (*m_masterMarker)) ? true : false;
#endif // HOOK_GAMEDLL
	}
	void SetParent(CNavArea *parent, NavTraverseType how = NUM_TRAVERSE_TYPES)
	{
		m_parent = parent;
		m_parentHow = how;
	}
	CNavArea *GetParent(void) const
	{
		return m_parent;
	}
	NavTraverseType GetParentHow(void) const
	{
		return m_parentHow;
	}

	bool IsOpen(void) const;
	void AddToOpenList(void);
	void UpdateOnOpenList(void);
	void RemoveFromOpenList(void);
	static bool IsOpenListEmpty(void);
	static CNavArea *PopOpenList(void);

	bool IsClosed(void) const;
	void AddToClosedList(void);
	void RemoveFromClosedList(void);

	static void ClearSearchLists(void);

	void SetTotalCost(float value)
	{
		m_totalCost = value;
	}
	float GetTotalCost(void) const
	{
		return m_totalCost;
	}
	void SetCostSoFar(float value)
	{
		m_costSoFar = value;
	}
	float GetCostSoFar(void) const
	{
		return m_costSoFar;
	}

	void Draw(byte red, byte green, byte blue, int duration = 50);
	void DrawConnectedAreas(void);
	void DrawMarkedCorner(NavCornerType corner, byte red, byte green, byte blue, int duration = 50);
	bool SplitEdit(bool splitAlongX, float splitEdge, CNavArea **outAlpha = NULL, CNavArea **outBeta = NULL);
	bool MergeEdit(CNavArea *adj);
	bool SpliceEdit(CNavArea *other);
	void RaiseCorner(NavCornerType corner, int amount);
	void AddLadderUp(CNavLadder *ladder)
	{
		m_ladder[LADDER_UP].push_back(ladder);
	}
	void AddLadderDown(CNavLadder *ladder)
	{
		m_ladder[LADDER_DOWN].push_back(ladder);
	}

private:
	bool IsHidingSpotCollision(const Vector *pos) const;
	void AddSpotEncounters(const CNavArea *from, NavDirType fromDir, const CNavArea *to, NavDirType toDir);
	void Strip(void);
	void FinishMerge(CNavArea *adjArea);
	void MergeAdjacentConnections(CNavArea *adjArea);
	void AssignNodes(CNavArea *area);
	void FinishSplitEdit(CNavArea *newArea, NavDirType ignoreEdge);
	void OnDestroyNotify(CNavArea *dead);
	void DecayDanger(void);
private:
	friend void ConnectGeneratedAreas(void);
	friend void MergeGeneratedAreas(void);
	friend void MarkJumpAreas(void);
	friend bool SaveNavigationMap(const char *filename);
	friend NavErrorType LoadNavigationMap(void);
	friend void DestroyNavigationMap(void);
	friend void DestroyHidingSpots(void);
	friend void StripNavigationAreas(void);

	friend class CNavAreaGrid;
	friend class CCSBotManager;

	void Initialize(void);

#ifndef HOOK_GAMEDLL
	static bool m_isReset;
	static unsigned int m_nextID;
#else
public:
	static bool (*m_isReset);
	static unsigned int (*m_nextID);
private:
#endif // HOOK_GAMEDLL

	unsigned int m_id;
	Extent m_extent;
	Vector m_center;
	unsigned char m_attributeFlags;
	Place m_place;

	float m_neZ;
	float m_swZ;

	enum { MAX_AREA_TEAMS = 2 };

	float m_clearedTimestamp[MAX_AREA_TEAMS];
	float m_danger[MAX_AREA_TEAMS];
	float m_dangerTimestamp[MAX_AREA_TEAMS];

#if defined(_WIN32) && defined(HOOK_GAMEDLL)
	int unknown_padding1;
#endif // HOOK_GAMEDLL

	HidingSpotList m_hidingSpotList;

#if defined(_WIN32) && defined(HOOK_GAMEDLL)
	int unknown_padding2;
#endif // HOOK_GAMEDLL

	SpotEncounterList m_spotEncounterList;

	enum { MAX_APPROACH_AREAS = 16 };

	ApproachInfo m_approach[MAX_APPROACH_AREAS];
	unsigned char m_approachCount;

#ifndef HOOK_GAMEDLL
	static unsigned int m_masterMarker;
#else
public:
	static unsigned int (*m_masterMarker);
private:
#endif // HOOK_GAMEDLL

	unsigned int m_marker;
	CNavArea *m_parent;
	NavTraverseType m_parentHow;
	float m_totalCost;
	float m_costSoFar;

#ifndef HOOK_GAMEDLL
	static CNavArea *m_openList;
#else
public:
	static CNavArea *(*m_openList);
private:
#endif // HOOK_GAMEDLL

	CNavArea *m_nextOpen;
	CNavArea *m_prevOpen;
	unsigned int m_openMarker;

#ifdef _WIN32
	int unknown_padding3;
#endif // _WIN32

	NavConnectList m_connect[ NUM_DIRECTIONS ];

#ifdef _WIN32
	int unknown_padding4;
	int unknown_padding5;

	int unknown_padding6;
	int unknown_padding7;
#endif // _WIN32

	NavLadderList m_ladder[ NUM_LADDER_DIRECTIONS ];

#ifdef _WIN32
	int unknown_padding8;
#endif // _WIN32

	CNavNode *m_node[ NUM_CORNERS ];

#ifdef _WIN32
	int unknown_padding9;
#endif // _WIN32

	NavAreaList m_overlapList;

	CNavArea *m_prevHash;
	CNavArea *m_nextHash;

};/* size: 532, cachelines: 9, members: 32 */

extern NavAreaList TheNavAreaList;

/* <4c1534> ../game_shared/bot/nav_area.h:417 */
inline bool CNavArea::IsDegenerate(void) const
{
	return (m_extent.lo.x >= m_extent.hi.x || m_extent.lo.y >= m_extent.hi.y);
}

/* <568e1d> ../game_shared/bot/nav_area.h:422 */
inline CNavArea *CNavArea::GetAdjacentArea(NavDirType dir, int i) const
{
	NavConnectList::const_iterator iter;
	for(iter = m_connect[dir].begin(); iter != m_connect[dir].end(); ++iter)
	{
		if (i == 0)
			return (*iter).area;
		--i;
	}
	return NULL;
}

/* <5a01dc> ../game_shared/bot/nav_area.h:435 */
inline bool CNavArea::IsOpen(void) const
{
#ifndef HOOK_GAMEDLL
	return (m_openMarker == m_masterMarker) ? true : false;
#else
	return (m_openMarker == (*m_masterMarker)) ? true : false;
#endif // HOOK_GAMEDLL
}

/* <5a0a62> ../game_shared/bot/nav_area.h:440 */
inline bool CNavArea::IsOpenListEmpty(void)
{
#ifndef HOOK_GAMEDLL
	return (m_openList != NULL) ? false : true;
#else
	return ((*m_openList) != NULL) ? false : true;
#endif // HOOK_GAMEDLL
}

/* <5a1483> ../game_shared/bot/nav_area.h:445 */
inline CNavArea *CNavArea::PopOpenList(void)
{
#ifndef HOOK_GAMEDLL
	if (m_openList)
	{
		CNavArea *area = m_openList;
		area->RemoveFromOpenList();
		return area;
	}
#else
	if ((*m_openList))
	{
		CNavArea *area = (*m_openList);
		area->RemoveFromOpenList();
		return area;
	}
#endif // HOOK_GAMEDLL
	return NULL;
}

/* <5a0a2a> ../game_shared/bot/nav_area.h:460 */
inline bool CNavArea::IsClosed(void) const
{
	if (IsMarked() && !IsOpen())
		return true;

	return false;
}

/* <5a0a46> ../game_shared/bot/nav_area.h:468 */
inline void CNavArea::AddToClosedList(void)
{
	Mark();
}

/* <5a01f8> ../game_shared/bot/nav_area.h:473 */
inline void CNavArea::RemoveFromClosedList(void)
{

}

/* <4cf943> ../game_shared/bot/nav_area.cpp:4947 */
class CNavAreaGrid
{
public:
	CNavAreaGrid(void);
	~CNavAreaGrid();

	void Reset(void);
	void Initialize(float minX, float maxX, float minY, float maxY);
	void AddNavArea(CNavArea *area);
	void RemoveNavArea(CNavArea *area);
	unsigned int GetNavAreaCount(void) const
	{
		return m_areaCount;
	}
	CNavArea *GetNavArea(const Vector *pos, float beneathLimt = 120.0f) const;
	CNavArea *GetNavAreaByID(unsigned int id) const;
	CNavArea *GetNearestNavArea(const Vector *pos, bool anyZ = false) const;

	Place GetPlace(const Vector *pos) const;

private:

	inline int ComputeHashKey(unsigned int id) const
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

private:
	const float m_cellSize;
	NavAreaList *m_grid;
	int m_gridSizeX;
	int m_gridSizeY;
	float m_minX;
	float m_minY;
	unsigned int m_areaCount;

	enum { HASH_TABLE_SIZE = 256 };
	CNavArea *m_hashTable[HASH_TABLE_SIZE];

};/* size: 1052, cachelines: 17, members: 8 */

class ShortestPathCost
{
public:
	float operator() (CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		if (fromArea == NULL)
		{
			return 0.0f;
		}
		else
		{
			float dist;

			if (ladder)
				dist = ladder->m_length;
			else
				dist = (*area->GetCenter() - *fromArea->GetCenter()).Length();

			float cost = dist + fromArea->GetCostSoFar();
			if (area->GetAttributes() & NAV_CROUCH)
			{
				const float crouchPenalty = 20.0f;
				cost += crouchPenalty * dist;
			}
			if (area->GetAttributes() & NAV_JUMP)
			{
				const float jumpPenalty = 5.0f;
				cost += jumpPenalty * dist;
			}
			return cost;
		}
	}
};/* size: 0, cachelines: 0, members: 0 */

/* <4c3e99> ../game_shared/bot/nav_area.h:679 */
template <typename CostFunctor>
bool NavAreaBuildPath(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, CostFunctor &costFunc, CNavArea **closestArea = NULL)
{
	if (closestArea)
		*closestArea = NULL;

	if (startArea == NULL)
		return false;

	if (goalArea == NULL && goalPos == NULL)
	{
		return false;
	}

	startArea->SetParent(NULL);
	if (startArea == goalArea)
	{
		goalArea->SetParent(NULL);

		if (closestArea)
			*closestArea = goalArea;

		return true;
	}
	Vector actualGoalPos = (goalPos) ? *goalPos : *goalArea->GetCenter();
	CNavArea::ClearSearchLists();
	startArea->SetTotalCost((*startArea->GetCenter() - actualGoalPos).Length());

	float initCost = costFunc(startArea, NULL, NULL);
	if (initCost < 0.0f)
		return false;
	startArea->SetCostSoFar(initCost);

	startArea->AddToOpenList();

	if (closestArea)
		*closestArea = startArea;
	float closestAreaDist = startArea->GetTotalCost();

	while(!CNavArea::IsOpenListEmpty())
	{
		CNavArea *area = CNavArea::PopOpenList();
		if (area == goalArea)
		{
			if (closestArea)
				*closestArea = goalArea;

			return true;
		}

		bool searchFloor = true;
		int dir = NORTH;
		const NavConnectList *floorList = area->GetAdjacentList(NORTH);
		NavConnectList::const_iterator floorIter = floorList->begin();

		bool ladderUp = true;
		const NavLadderList *ladderList = NULL;
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

		while(true)
		{
			CNavArea *newArea;
			NavTraverseType how;
			const CNavLadder *ladder = NULL;

			if (searchFloor)
			{
				if (floorIter == floorList->end())
				{
					++dir;

					if (dir == NUM_DIRECTIONS)
					{
						searchFloor = false;

						ladderList = area->GetLadderList(LADDER_UP);
						ladderIter = ladderList->begin();
						ladderTopDir = AHEAD;
					}
					else
					{

						floorList = area->GetAdjacentList((NavDirType)dir);
						floorIter = floorList->begin();
					}
					continue;
				}

				newArea = (*floorIter).area;
				how = (NavTraverseType)dir;
				++floorIter;
			}
			else
			{
				if (ladderIter == ladderList->end())
				{
					if (!ladderUp)
						break;

					else
					{
						ladderUp = false;
						ladderList = area->GetLadderList(LADDER_DOWN);
						ladderIter = ladderList->begin();
					}
					continue;
				}

				if (ladderUp)
				{
					ladder = *ladderIter;
					if (ladder->m_isDangling)
					{
						++ladderIter;
						continue;
					}

					if (ladderTopDir == AHEAD)
						newArea = ladder->m_topForwardArea;
					else if (ladderTopDir == LEFT)
						newArea = ladder->m_topLeftArea;
					else if (ladderTopDir == RIGHT)
						newArea = ladder->m_topRightArea;
					else
					{
						++ladderIter;
						continue;
					}

					how = GO_LADDER_UP;
					++ladderTopDir;
				}
				else
				{
					newArea = (*ladderIter)->m_bottomArea;
					how = GO_LADDER_DOWN;
					ladder = (*ladderIter);
					++ladderIter;
				}

				if (newArea == NULL)
					continue;
			}

			if (newArea == area)
				continue;

			float newCostSoFar = costFunc(newArea, area, ladder);
			if (newCostSoFar < 0.0f)
				continue;

			if ((newArea->IsOpen() || newArea->IsClosed()) && newArea->GetCostSoFar() <= newCostSoFar)
				continue;

			else
			{
				float newCostRemaining = (*newArea->GetCenter() - actualGoalPos).Length();
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
					newArea->UpdateOnOpenList();
				else
					newArea->AddToOpenList();
			}
		}
		area->AddToClosedList();
	}
	return false;
}

/* <3fcb64> ../game_shared/bot/nav_area.h:914 */
template <typename CostFunctor>
float NavAreaTravelDistance(CNavArea *startArea, CNavArea *endArea, CostFunctor &costFunc)
{
	if (startArea == NULL)
		return -1.0f;

	if (endArea == NULL)
		return -1.0f;

	if (startArea == endArea)
		return 0.0f;

	if (NavAreaBuildPath(startArea, endArea, NULL, costFunc) == false)
		return -1.0f;

	float distance = 0.0f;
	for(CNavArea *area = endArea; area->GetParent(); area = area->GetParent())
	{
		distance += (*area->GetCenter() - *area->GetParent()->GetCenter()).Length();
	}
	return distance;
}

// OVERLOAD
template <typename CostFunctor>
float NavAreaTravelDistance(const Vector *startPos, CNavArea *startArea, const Vector *goalPos, CostFunctor &costFunc)
{
	if (startArea == NULL || startPos == NULL || goalPos == NULL)
		return -1.0f;

	CNavArea *goalArea = NULL;
	if (NavAreaBuildPath(startArea, TheNavAreaGrid.GetNearestNavArea(goalPos), goalPos, costFunc, &goalArea) == false)
		return -1.0f;

	if (goalArea == NULL)
		return -1.0f;

	if (goalArea->GetParent() == NULL)
		return (*goalPos - *startPos).Length();

	else
	{
		CNavArea *area = goalArea->GetParent();
		float distance = (*goalPos - *area->GetCenter()).Length();

		for(; area->GetParent(); area = area->GetParent())
		{
			distance += (*area->GetCenter() - *area->GetParent()->GetCenter()).Length();
		}
		return distance;
	}
}

/* <2e7572> ../game_shared/bot/nav_area.h:990 */
inline void AddAreaToOpenList(CNavArea *area, CNavArea *parent, const Vector *startPos, float maxRange)
{
	if (area == NULL)
		return;

	if (!area->IsMarked())
	{
		area->Mark();
		area->SetTotalCost(0.0f);
		area->SetParent(parent);

		if (maxRange > 0.0f)
		{
			Vector closePos;
			area->GetClosestPointOnArea(startPos, &closePos);
			if ((closePos - *startPos).Make2D().IsLengthLessThan(maxRange))
			{
				float distAlong = parent->GetCostSoFar();
				distAlong += (*area->GetCenter() - *parent->GetCenter()).Length();
				area->SetCostSoFar(distAlong);

				if (distAlong <= 1.5f * maxRange)
					area->AddToOpenList();
			}
		}
		else
			area->AddToOpenList();
	}
}

/* <56903e> ../game_shared/bot/nav_area.h:1028 */
template <typename Functor>
void SearchSurroundingAreas(CNavArea *startArea, const Vector *startPos, Functor &func, float maxRange = -1.0f)
{
	if (startArea == NULL || startPos == NULL)
		return;

	CNavArea::MakeNewMarker();
	CNavArea::ClearSearchLists();

	startArea->AddToOpenList();
	startArea->SetTotalCost(0.0f);
	startArea->SetCostSoFar(0.0f);
	startArea->SetParent(NULL);
	startArea->Mark();

	while(!CNavArea::IsOpenListEmpty())
	{

		CNavArea *area = CNavArea::PopOpenList();
		if (func(area))
		{
			for(int dir = 0; dir < NUM_DIRECTIONS; ++dir)
			{
				int count = area->GetAdjacentCount((NavDirType)dir);
				for(int i = 0; i < count; ++i)
				{
					CNavArea *adjArea = area->GetAdjacentArea((NavDirType)dir, i);
					AddAreaToOpenList(adjArea, area, startPos, maxRange);
				}
			}

			NavLadderList::const_iterator ladderIt;
			const NavLadderList *ladderList = area->GetLadderList(LADDER_UP);
			if (ladderList)
			{
				for(ladderIt = ladderList->begin(); ladderIt != ladderList->end(); ++ladderIt)
				{
					const CNavLadder *ladder = *ladderIt;
					if (ladder->m_isDangling)
					{
						continue;
					}

					AddAreaToOpenList(ladder->m_topForwardArea, area, startPos, maxRange);
					AddAreaToOpenList(ladder->m_topLeftArea, area, startPos, maxRange);
					AddAreaToOpenList(ladder->m_topRightArea, area, startPos, maxRange);
				}
			}
			ladderList = area->GetLadderList(LADDER_DOWN);
			if (ladderList)
			{
				for(ladderIt = ladderList->begin(); ladderIt != ladderList->end(); ++ladderIt)
				{
					const CNavLadder *ladder = *ladderIt;
					AddAreaToOpenList(ladder->m_bottomArea, area, startPos, maxRange);
				}
			}
		}
	}
}

/* <4c4137> ../game_shared/bot/nav_area.h:1109 */
template <typename Functor>
void ForAllAreas(Functor &func)
{
	NavAreaList::iterator iter;
	for(iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	{
		CNavArea *area = *iter;
		func(area);
	}
}

/* <5497fa> ../game_shared/bot/nav_area.h:1143 */
class FarAwayFromPositionFunctor
{
public:
	FarAwayFromPositionFunctor(const Vector *pos)
	{
		m_pos = pos;
	}

	float operator() (CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		return 1.0f / (*m_pos - *area->GetCenter()).Length();
	}

private:
	const Vector *m_pos;
};/* size: 4, cachelines: 1, members: 1 */

/* <549838> ../game_shared/bot/nav_area.h:1162 */
template <typename CostFunctor>
CNavArea *FindMinimumCostArea(CNavArea *startArea, CostFunctor &costFunc)
{
	const float minSize = 150.0f;

	enum { NUM_CHEAP_AREAS = 32 };
	struct
	{
		CNavArea *area;
		float cost;
	}
	cheapAreaSet[NUM_CHEAP_AREAS];
	int cheapAreaSetCount = 0;

	NavAreaList::iterator iter;
	for(iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	{
		CNavArea *area = *iter;
		const Extent *extent = area->GetExtent();
		if (extent->hi.x - extent->lo.x < minSize || extent->hi.y - extent->lo.y < minSize)
			continue;

		float cost = costFunc(area, startArea, NULL);
		if (cheapAreaSetCount < NUM_CHEAP_AREAS)
		{
			cheapAreaSet[cheapAreaSetCount].area = area;
			cheapAreaSet[cheapAreaSetCount++].cost = cost;
		}
		else
		{
			int expensive = 0;
			for(int i = 1; i < NUM_CHEAP_AREAS; i++)
				if (cheapAreaSet[i].cost > cheapAreaSet[expensive].cost)
					expensive = i;

			if (cheapAreaSet[expensive].cost > cost)
			{
				cheapAreaSet[expensive].area = area;
				cheapAreaSet[expensive].cost = cost;
			}
		}
	}
	if (cheapAreaSetCount)
	{
		return cheapAreaSet[RANDOM_LONG(0, cheapAreaSetCount-1)].area;
	}
	else
	{
		int numAreas = TheNavAreaList.size();
		int which = RANDOM_LONG(0, numAreas-1);

		NavAreaList::iterator iter;
		for(iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
			if (which-- == 0)
				break;

		return *iter;
	}
}

#ifdef HOOK_GAMEDLL

typedef const Vector *(FIND_SPOT_CBASE)(CBaseEntity *, const Vector *, CNavArea *, float, int, bool);

typedef void (CNavArea::*SAVE_FD)(int fd, unsigned int version);
typedef void (CNavArea::*SAVE_FILE)(FILE *fp);

typedef void (CNavArea::*OVERLAP_VECTOR)(Vector *pos);
typedef void (CNavArea::*OVERLAP_CNAV)(CNavArea *area);

typedef float (CNavArea::*GETZ_VECTOR)(const Vector *pos) const;
typedef float (CNavArea::*GETZ_TWO_FLOAT)(float x, float y) const;

typedef void (HidingSpot::*HIDING_SPOT_VOID)(void);
typedef void (HidingSpot::*HIDING_SPOT_VECTOR)(const Vector *pos, unsigned char flags);

typedef void (HidingSpot::*CNAV_AREA_VOID)(void);
typedef void (HidingSpot::*CNAV_AREA_TWO_VECTOR)(const Vector *corner, const Vector *otherCorner);
typedef void (HidingSpot::*CNAV_AREA_VECTOR)(const Vector *nwCorner, const Vector *neCorner, const Vector *seCorner, const Vector *swCorner);
typedef void (HidingSpot::*CNAV_AREA_NAVNODE)(CNavNode *nwNode, class CNavNode *neNode, class CNavNode *seNode, class CNavNode *swNode);

#endif // HOOK_GAMEDLL

#ifdef HOOK_GAMEDLL

//#define TheNavLadderList (*pTheNavLadderList)
#define TheHidingSpotList (*pTheHidingSpotList)
#define TheNavAreaList (*pTheNavAreaList)
#define TheNavAreaGrid (*pTheNavAreaGrid)

//#define lastDrawTimestamp (*plastDrawTimestamp)
#define goodSizedAreaList (*pgoodSizedAreaList)
//#define markedArea (*pmarkedArea)
//#define lastSelectedArea (*plastSelectedArea)
#define markedCorner (*pmarkedCorner)
//#define isCreatingNavArea (*pisCreatingNavArea)
//#define isAnchored (*pisAnchored)
//#define anchor (*panchor)
//#define isPlaceMode (*pisPlaceMode)
//#define isPlacePainting (*pisPlacePainting)
#define BlockedID (*pBlockedID)
#define BlockedIDCount (*pBlockedIDCount)

#endif // HOOK_GAMEDLL

//extern NavLadderList TheNavLadderList;
extern HidingSpotList TheHidingSpotList;
extern NavAreaList TheNavAreaList;
extern CNavAreaGrid TheNavAreaGrid;
//extern float lastDrawTimestamp;
extern NavAreaList goodSizedAreaList;
//extern CNavArea *markedArea;
//extern CNavArea *lastSelectedArea;
extern NavCornerType markedCorner;
//extern bool isCreatingNavArea;
//extern bool isAnchored;
//extern Vector anchor;
//extern bool isPlaceMode;
//extern bool isPlacePainting;
extern unsigned int BlockedID[ MAX_BLOCKED_AREAS ];
extern int BlockedIDCount;

#ifdef HOOK_GAMEDLL

NOXREF void buildGoodSizedList(void);

#endif // HOOK_GAMEDLL

NOBODY bool IsHidingSpotInCover(const Vector *spot);
NOBODY void ClassifySniperSpot(HidingSpot *spot);
NOBODY void DestroyHidingSpots(void);
NOBODY void EditNavAreas(NavEditCmdType cmd);
bool GetGroundHeight(const Vector *pos, float *height, Vector *normal = NULL);
NOBODY bool GetSimpleGroundHeight(const Vector *pos, float *height, Vector *normal = NULL);
NOBODY inline bool IsAreaVisible(const Vector *pos, const CNavArea *area);
NOBODY CNavArea *GetMarkedArea(void);
NOBODY void EditNavAreasReset(void);
NOBODY void DrawHidingSpots(const CNavArea *area);
NOBODY void IncreaseDangerNearby(int teamID, float amount, CNavArea *startArea, const Vector *pos, float maxRadius);
NOBODY void DrawDanger(void);
NOBODY bool IsSpotOccupied(CBaseEntity *me, const Vector *pos);
NOBODY const Vector *FindNearbyHidingSpot(CBaseEntity *me, const Vector *pos, CNavArea *startArea, float maxRange = 1000.0f, bool isSniper = false, bool useNearest = false);
NOBODY const Vector *FindNearbyRetreatSpot(CBaseEntity *me, const Vector *start, CNavArea *startArea, float maxRange = 1000.0f, int avoidTeam = 0, bool useCrouchAreas = true);
NOBODY bool IsCrossingLineOfFire(const Vector &start, const Vector &finish, CBaseEntity *ignore = NULL, int ignoreTeam = 0);
NOBODY const Vector *FindRandomHidingSpot(CBaseEntity *me, Place place, bool isSniper = false);
NOBODY HidingSpot *GetHidingSpotByID(unsigned int id);
void ApproachAreaAnalysisPrep(void);
void CleanupApproachAreaAnalysisPrep(void);
NOBODY void DestroyLadders(void);
NOBODY void DestroyNavigationMap(void);
NOBODY void StripNavigationAreas(void);
NOBODY inline CNavArea *FindFirstAreaInDirection(const Vector *start, NavDirType dir, float range, float beneathLimit, CBaseEntity *traceIgnore, Vector *closePos);
NOBODY inline bool testJumpDown(const Vector *fromPos, const Vector *toPos);
NOBODY inline CNavArea *findJumpDownArea(const Vector *fromPos, NavDirType dir);
NOBODY void ConnectGeneratedAreas(void);
NOBODY void MergeGeneratedAreas(void);
NOBODY inline bool IsAreaRoughlySquare(const CNavArea *area);
NOBODY void SplitX(CNavArea *area);
NOBODY void SplitY(CNavArea *area);
NOBODY void SquareUpAreas(void);
NOBODY bool TestArea(CNavNode *node, int width, int height);
NOBODY int BuildArea(CNavNode *node, int width, int height);
NOBODY void BuildLadders(void);
NOBODY void MarkJumpAreas(void);
NOBODY void GenerateNavigationAreaMesh(void);

//refs
extern float (*pGetZ__Vector)(const Vector *pos);
extern CNavArea *(*pGetNearestNavArea)(const Vector *pos, bool anyZ);
extern CNavArea *(*pGetNavArea)(const Vector *pos, float beneathLimit);

#endif // NAV_AREA_H
