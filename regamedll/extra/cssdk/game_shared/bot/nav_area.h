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
enum NavEditCmdType
{
	EDIT_NONE,
	EDIT_DELETE,			// delete current area
	EDIT_SPLIT,			// split current area
	EDIT_MERGE,			// merge adjacent areas
	EDIT_JOIN,			// define connection between areas
	EDIT_BREAK,			// break connection between areas
	EDIT_MARK,			// mark an area for further operations
	EDIT_ATTRIB_CROUCH,		// toggle crouch attribute on current area
	EDIT_ATTRIB_JUMP,		// toggle jump attribute on current area
	EDIT_ATTRIB_PRECISE,		// toggle precise attribute on current area
	EDIT_ATTRIB_NO_JUMP,		// toggle inhibiting discontinuity jumping in current area
	EDIT_BEGIN_AREA,		// begin creating a new nav area
	EDIT_END_AREA,			// end creation of the new nav area
	EDIT_CONNECT,			// connect marked area to selected area
	EDIT_DISCONNECT,		// disconnect marked area from selected area
	EDIT_SPLICE,			// create new area in between marked and selected areas
	EDIT_TOGGLE_PLACE_MODE,		// switch between normal and place editing
	EDIT_TOGGLE_PLACE_PAINTING,	// switch between "painting" places onto areas
	EDIT_PLACE_FLOODFILL,		// floodfill areas out from current area
	EDIT_PLACE_PICK,		// "pick up" the place at the current area
	EDIT_MARK_UNNAMED,		// mark an unnamed area for further operations
	EDIT_WARP_TO_MARK,		// warp a spectating local player to the selected mark
	EDIT_SELECT_CORNER,		// select a corner on the current area
	EDIT_RAISE_CORNER,		// raise a corner on the current area
	EDIT_LOWER_CORNER,		// lower a corner on the current area
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

class CNavLadder {
public:
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
};

typedef std::list<CNavLadder *> NavLadderList;

class HidingSpot {
public:
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

	const Vector *GetPosition() const { return &m_pos; }
	unsigned int GetID() const { return m_id; }

private:
	Vector m_pos;
	unsigned int m_id;
	unsigned int m_marker;
	unsigned char m_flags;
};

typedef std::list<HidingSpot *> HidingSpotList;

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
	SpotOrderList spotList;			// list of spots to look at, in order of occurrence
};

typedef std::list<SpotEncounter> SpotEncounterList;
typedef std::list<CNavArea *> NavAreaList;

// A CNavArea is a rectangular region defining a walkable area in the map
class CNavArea {
public:
	unsigned int GetID() const { return m_id; }
	void SetAttributes(unsigned char bits) { m_attributeFlags = bits; }
	unsigned char GetAttributes() const { return m_attributeFlags; }
	void SetPlace(Place place) { m_place = place; }						// set place descriptor
	Place GetPlace() const { return m_place; }						// get place descriptor

	int GetAdjacentCount(NavDirType dir) const { return m_connect[dir].size(); }		// return number of connected areas in given direction
	const NavConnectList *GetAdjacentList(NavDirType dir) const { return &m_connect[dir]; }

	const NavLadderList *GetLadderList(LadderDirectionType dir) const { return &m_ladder[dir]; }

	// for hunting algorithm
	void SetClearedTimestamp(int teamID) { m_clearedTimestamp[teamID] = gpGlobals->time; }	// set this area's "clear" timestamp to now
	float GetClearedTimestamp(int teamID) { return m_clearedTimestamp[teamID]; }		// get time this area was marked "clear"

	// hiding spots
	const HidingSpotList *GetHidingSpotList() const { return &m_hidingSpotList; }

	float GetSizeX() const { return m_extent.hi.x - m_extent.lo.x; }
	float GetSizeY() const { return m_extent.hi.y - m_extent.lo.y; }

	const Extent *GetExtent() const { return &m_extent; }
	const Vector *GetCenter() const { return &m_center; }

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

	void SetParent(CNavArea *parent, NavTraverseType how = NUM_TRAVERSE_TYPES) { m_parent = parent; m_parentHow = how; }
	CNavArea *GetParent() const { return m_parent; }
	NavTraverseType GetParentHow() const { return m_parentHow; }

	void SetTotalCost(float value) { m_totalCost = value; }
	float GetTotalCost() const { return m_totalCost; }

	void SetCostSoFar(float value) { m_costSoFar = value; }
	float GetCostSoFar() const { return m_costSoFar; }

public:
	friend class CNavAreaGrid;
	friend class CCSBotManager;

	unsigned int m_id;				// unique area ID
	Extent m_extent;				// extents of area in world coords (NOTE: lo.z is not necessarily the minimum Z, but corresponds to Z at point (lo.x, lo.y), etc
	Vector m_center;				// centroid of area
	unsigned char m_attributeFlags;			// set of attribute bit flags (see NavAttributeType)
	Place m_place;					// place descriptor

	// height of the implicit corners
	float m_neZ;
	float m_swZ;

	enum { MAX_AREA_TEAMS = 2 };

	// for hunting
	float m_clearedTimestamp[MAX_AREA_TEAMS];	// time this area was last "cleared" of enemies

	// danger
	float m_danger[MAX_AREA_TEAMS];			// danger of this area, allowing bots to avoid areas where they died in the past - zero is no danger
	float m_dangerTimestamp[MAX_AREA_TEAMS];	// time when danger value was set - used for decaying

	// hiding spots
	HidingSpotList m_hidingSpotList;

	// encounter spots
	SpotEncounterList m_spotEncounterList;			// list of possible ways to move thru this area, and the spots to look at as we do

	// approach areas
	enum { MAX_APPROACH_AREAS = 16 };
	ApproachInfo m_approach[MAX_APPROACH_AREAS];
	unsigned char m_approachCount;

	// A* pathfinding algorithm
	unsigned int m_marker;					// used to flag the area as visited
	CNavArea *m_parent;					// the area just prior to this on in the search path
	NavTraverseType m_parentHow;				// how we get from parent to us
	float m_totalCost;					// the distance so far plus an estimate of the distance left
	float m_costSoFar;					// distance travelled so far

	CNavArea *m_nextOpen, *m_prevOpen;			// only valid if m_openMarker == m_masterMarker
	unsigned int m_openMarker;				// if this equals the current marker value, we are on the open list

	// connections to adjacent areas
	NavConnectList m_connect[ NUM_DIRECTIONS ];		// a list of adjacent areas for each direction
	NavLadderList m_ladder[ NUM_LADDER_DIRECTIONS ];	// list of ladders leading up and down from this area

	CNavNode *m_node[ NUM_CORNERS ];			// nav nodes at each corner of the area
	NavAreaList m_overlapList;						// list of areas that overlap this area

	CNavArea *m_prevHash, *m_nextHash;					// for hash table in CNavAreaGrid
};

// The CNavAreaGrid is used to efficiently access navigation areas by world position
// Each cell of the grid contains a list of areas that overlap it
// Given a world position, the corresponding grid cell is ( x/cellsize, y/cellsize )
class CNavAreaGrid {
public:
	const float m_cellSize;
	NavAreaList *m_grid;
	int m_gridSizeX;
	int m_gridSizeY;
	float m_minX;
	float m_minY;
	unsigned int m_areaCount;				// total number of nav areas

	enum { HASH_TABLE_SIZE = 256 };
	CNavArea *m_hashTable[HASH_TABLE_SIZE];			// hash table to optimize lookup by ID
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
