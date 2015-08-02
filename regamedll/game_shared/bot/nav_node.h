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

#ifndef NAV_NODE_H
#define NAV_NODE_H
#ifdef _WIN32
#pragma once
#endif

class CNavNode
{
public:
	CNavNode(const Vector *pos, const Vector *normal, CNavNode *parent = NULL);

	// return navigation node at the position, or NULL if none exists
	static const CNavNode *GetNode(const Vector *pos);

	// get navigation node connected in given direction, or NULL if cant go that way
	CNavNode *GetConnectedNode(NavDirType dir) const;
	const Vector *GetPosition(void) const;
	const Vector *GetNormal(void) const
	{
		return &m_normal;
	}
	unsigned int GetID(void) const
	{
		return m_id;
	}

	static CNavNode *GetFirst(void)
	{
		return IMPLEMENT_ARRAY(m_list);
	}
	static unsigned int GetListLength(void)
	{
		return m_listLength;
	}
	CNavNode *GetNext(void)
	{
		return m_next;
	}
	
	// create a connection FROM this node TO the given node, in the given direction
	void ConnectTo(CNavNode *node, NavDirType dir);
	CNavNode *GetParent(void) const;

	void MarkAsVisited(NavDirType dir);		// mark the given direction as having been visited
	BOOL HasVisited(NavDirType dir);		// return TRUE if the given direction has already been searched
	BOOL IsBiLinked(NavDirType dir) const;		// node is bidirectionally linked to another node in the given direction
	BOOL IsClosedCell(void) const;			// node is the NW corner of a bi-linked quad of nodes

	// @todo Should pass in area that is covering
	void Cover(void)
	{
		m_isCovered = true;
	}
	// return true if this node has been covered by an area
	BOOL IsCovered(void) const
	{
		return m_isCovered;
	}

	// assign the given area to this node
	void AssignArea(CNavArea *area);

	// return associated area						
	CNavArea *GetArea(void) const;							

	void SetAttributes(unsigned char bits)
	{
		m_attributeFlags = bits;
	}
	unsigned char GetAttributes(void) const
	{
		return m_attributeFlags;
	}

private:
	friend void DestroyNavigationMap(void);

	Vector m_pos;				// position of this node in the world
	Vector m_normal;			// surface normal at this location
	CNavNode *m_to[ NUM_DIRECTIONS ];	// links to north, south, east, and west. NULL if no link
	unsigned int m_id;			// unique ID of this node
	unsigned char m_attributeFlags;		// set of attribute bit flags (see NavAttributeType)

#ifdef HOOK_GAMEDLL
public:
#endif // HOOK_GAMEDLL
	static CNavNode *IMPLEMENT_ARRAY(m_list);		// the master list of all nodes for this map
	static unsigned int m_listLength;
#ifdef HOOK_GAMEDLL
private:
#endif // HOOK_GAMEDLL
	CNavNode *m_next;			// next link in master list

	// below are only needed when generating
	// flags for automatic node generation. If direction bit is clear, that direction hasn't been explored yet.
	unsigned char m_visited;
	CNavNode *m_parent;			// the node prior to this in the search, which we pop back to when this node's search is done (a stack)
	BOOL m_isCovered;			// true when this node is "covered" by a CNavArea
	CNavArea *m_area;			// the area this node is contained within

};/* size: 68, cachelines: 2, members: 12 */

/* <4c0577> ../game_shared/bot/nav_node.h:74 */
inline CNavNode *CNavNode::GetConnectedNode(NavDirType dir) const
{
	return m_to[ dir ];
}

/* <4c05ba> ../game_shared/bot/nav_node.h:79 */
inline const Vector *CNavNode::GetPosition(void) const
{
	return &m_pos;
}

/* <3434df> ../game_shared/bot/nav_node.h:84 */
inline CNavNode *CNavNode::GetParent(void) const
{
	return m_parent;
}

/* <3434fe> ../game_shared/bot/nav_node.h:89 */
inline void CNavNode::MarkAsVisited(NavDirType dir)
{
	m_visited |= (1 << dir);
}

/* <343523> ../game_shared/bot/nav_node.h:94 */
inline BOOL CNavNode::HasVisited(NavDirType dir)
{
	if (m_visited & (1 << dir))
		return true;

	return false;
}

/* <4bfdb6> ../game_shared/bot/nav_node.h:102 */
inline void CNavNode::AssignArea(CNavArea *area)
{
	m_area = area;
}

/* <4bfdde> ../game_shared/bot/nav_node.h:107 */
inline CNavArea *CNavNode::GetArea(void) const
{
	return m_area;
}

#ifdef HOOK_GAMEDLL

//#define Opposite (*pOpposite)
//#define m_list (*pm_list)
//#define m_listLength (*pm_listLength)
//#define NodeMapExtent (*pNodeMapExtent)

#endif // HOOK_GAMEDLL

//extern NavDirType Opposite[ NUM_DIRECTIONS ];
//extern CNavNode *CNavNode::m_list;
//extern unsigned int CNavNode::m_listLength;
//extern Extent NodeMapExtent;

#endif // NAV_NODE_H
