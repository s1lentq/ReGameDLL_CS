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

enum PathTraversAble
{
	PTRAVELS_EMPTY,
	PTRAVELS_SLOPE,
	PTRAVELS_STEP,
	PTRAVELS_STEPJUMPABLE,
};

using node_index_t = int;
constexpr node_index_t NODE_INVALID_EMPTY = {-1};

typedef struct localnode_s
{
	Vector vecLoc;
	int offsetX;
	int offsetY;
	byte bDepth;
	BOOL fSearched;
	node_index_t nindexParent;

} localnode_t;

class CLocalNav
{
public:
	CLocalNav(CHostage *pOwner);
	virtual ~CLocalNav();

	void SetTargetEnt(CBaseEntity *pTarget)
	{
		if (pTarget)
			m_pTargetEnt = pTarget->edict();
		else
			m_pTargetEnt = nullptr;
	}

	node_index_t FindPath(Vector &vecStart, Vector &vecDest, float flTargetRadius, BOOL fNoMonsters);
	int SetupPathNodes(node_index_t nindex, Vector *vecNodes, BOOL fNoMonsters);
	node_index_t GetFurthestTraversableNode(Vector &vecStartingLoc, Vector *vecNodes, int nTotalNodes, BOOL fNoMonsters);
	PathTraversAble PathTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters);
	BOOL PathClear(Vector &vecOrigin, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr);
	BOOL PathClear(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters);
	node_index_t AddNode(node_index_t nindexParent, Vector &vecLoc, int offsetX = 0, int offsetY = 0, byte bDepth = 0);
	localnode_t *GetNode(node_index_t nindex);
	node_index_t NodeExists(int offsetX, int offsetY);
	void AddPathNodes(node_index_t nindexSource, BOOL fNoMonsters);
	void AddPathNode(node_index_t nindexSource, int offsetX, int offsetY, BOOL fNoMonsters);
	node_index_t GetBestNode(Vector &vecOrigin, Vector &vecDest);
	BOOL SlopeTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr);
	BOOL LadderTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr);
	BOOL StepTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr);
	BOOL StepJumpable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr);
	node_index_t FindDirectPath(Vector &vecStart, Vector &vecDest, float flTargetRadius, BOOL fNoMonsters);
	BOOL LadderHit(Vector &vecSource, Vector &vecDest, TraceResult &tr);

	static void Think();
	static void RequestNav(CHostage *pCaller);
	static void Reset();
	static void HostagePrethink();
	static float m_flStepSize;

private:
	static EntityHandle<CHostage> m_hQueue[MAX_HOSTAGES_NAV];
	static EntityHandle<CHostage> m_hHostages[MAX_HOSTAGES_NAV];
	static int m_CurRequest;
	static int m_NumRequest;
	static int m_NumHostages;
	static int m_NodeValue;
	static float m_flNextCvarCheck;
	static float m_flLastThinkTime;

	CHostage *m_pOwner;
	edict_t *m_pTargetEnt;
	BOOL m_fTargetEntHit;
	localnode_t *m_nodeArr;
	node_index_t m_nindexAvailableNode;
	Vector m_vecStartingLoc;
};
