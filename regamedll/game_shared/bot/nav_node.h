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

class CNavNode
{
public:
	CNavNode(const Vector *pos, const Vector *normal, CNavNode *parent = nullptr);

	// return navigation node at the position, or NULL if none exists
	static const CNavNode *GetNode(const Vector *pos);

	// get navigation node connected in given direction, or NULL if cant go that way
	CNavNode *GetConnectedNode(NavDirType dir) const;
	const Vector *GetPosition() const;
	const Vector *GetNormal() const { return &m_normal; }
	unsigned int GetID() const { return m_id; }

	static CNavNode *GetFirst() { return m_list; }
	static unsigned int GetListLength() { return m_listLength; }

	CNavNode *GetNext() { return m_next; }

	// create a connection FROM this node TO the given node, in the given direction
	void ConnectTo(CNavNode *node, NavDirType dir);
	CNavNode *GetParent() const;

	void MarkAsVisited(NavDirType dir);				// mark the given direction as having been visited
	BOOL HasVisited(NavDirType dir);				// return TRUE if the given direction has already been searched
	BOOL IsBiLinked(NavDirType dir) const;			// node is bidirectionally linked to another node in the given direction
	BOOL IsClosedCell() const;						// node is the NW corner of a bi-linked quad of nodes

	void Cover() { m_isCovered = true; }			// TODO: Should pass in area that is covering
	BOOL IsCovered() const { return m_isCovered; }	// return true if this node has been covered by an area

	void AssignArea(CNavArea *area);		// assign the given area to this node
	CNavArea *GetArea() const;				// return associated area

	void SetAttributes(unsigned char bits) { m_attributeFlags = bits; }
	unsigned char GetAttributes() const { return m_attributeFlags; }

private:
	friend void DestroyNavigationMap();

	Vector m_pos;						// position of this node in the world
	Vector m_normal;					// surface normal at this location
	CNavNode *m_to[NUM_DIRECTIONS];		// links to north, south, east, and west. NULL if no link
	unsigned int m_id;					// unique ID of this node
	unsigned char m_attributeFlags;		// set of attribute bit flags (see NavAttributeType)

	static CNavNode *m_list;			// the master list of all nodes for this map
	static unsigned int m_listLength;

	CNavNode *m_next;					// next link in master list

	// below are only needed when generating
	// flags for automatic node generation. If direction bit is clear, that direction hasn't been explored yet.
	unsigned char m_visited;
	CNavNode *m_parent;			// the node prior to this in the search, which we pop back to when this node's search is done (a stack)
	BOOL m_isCovered;			// true when this node is "covered" by a CNavArea
	CNavArea *m_area;			// the area this node is contained within
};

inline CNavNode *CNavNode::GetConnectedNode(NavDirType dir) const
{
	return m_to[dir];
}

inline const Vector *CNavNode::GetPosition() const
{
	return &m_pos;
}

inline CNavNode *CNavNode::GetParent() const
{
	return m_parent;
}

inline void CNavNode::MarkAsVisited(NavDirType dir)
{
	m_visited |= (1 << dir);
}

inline BOOL CNavNode::HasVisited(NavDirType dir)
{
	if (m_visited & (1 << dir))
		return true;

	return false;
}

inline void CNavNode::AssignArea(CNavArea *area)
{
	m_area = area;
}

inline CNavArea *CNavNode::GetArea() const
{
	return m_area;
}
