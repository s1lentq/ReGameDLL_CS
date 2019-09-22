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

#include "precompiled.h"

EntityHandle<CHostage> CLocalNav::m_hQueue[MAX_HOSTAGES_NAV];
EntityHandle<CHostage> CLocalNav::m_hHostages[MAX_HOSTAGES_NAV];

int CLocalNav::m_CurRequest  = 0;
int CLocalNav::m_NumRequest  = 0;
int CLocalNav::m_NumHostages = 0;
int CLocalNav::m_NodeValue   = 0;

float CLocalNav::m_flStepSize      = 18.0f; // sv_stepsize by default
float CLocalNav::m_flNextCvarCheck = 0.0f;
float CLocalNav::m_flLastThinkTime = 0.0f;

CLocalNav::CLocalNav(CHostage *pOwner)
{
	m_pOwner = pOwner;
	m_pTargetEnt = nullptr;
	m_nodeArr = new localnode_t[MAX_NODES];

	if (m_NumHostages >= MAX_HOSTAGES_NAV)
		return;

	m_hHostages[m_NumHostages++] = pOwner;
}

CLocalNav::~CLocalNav()
{
	if (m_nodeArr)
	{
		delete[] m_nodeArr;
		m_nodeArr = nullptr;
	}
}

node_index_t CLocalNav::AddNode(node_index_t nindexParent, Vector &vecLoc, int offsetX, int offsetY, byte bDepth)
{
	localnode_t *nodeNew;

	if (m_nindexAvailableNode == MAX_NODES)
		return NODE_INVALID_EMPTY;

	nodeNew = GetNode(m_nindexAvailableNode);

	nodeNew->vecLoc = vecLoc;
	nodeNew->offsetX = offsetX;
	nodeNew->offsetY = offsetY;
	nodeNew->bDepth = bDepth;
	nodeNew->fSearched = FALSE;
	nodeNew->nindexParent = nindexParent;

	return m_nindexAvailableNode++;
}

localnode_t *CLocalNav::GetNode(node_index_t nindex)
{
	return &m_nodeArr[nindex];
}

node_index_t CLocalNav::NodeExists(int offsetX, int offsetY)
{
	node_index_t nindexCurrent = NODE_INVALID_EMPTY;
	localnode_t *nodeCurrent;

	for (nindexCurrent = m_nindexAvailableNode - 1; nindexCurrent != NODE_INVALID_EMPTY; nindexCurrent--)
	{
		nodeCurrent = GetNode(nindexCurrent);

		if (nodeCurrent->offsetX == offsetX && nodeCurrent->offsetY == offsetY)
		{
			break;
		}
	}

	return nindexCurrent;
}

void CLocalNav::AddPathNodes(node_index_t nindexSource, BOOL fNoMonsters)
{
	AddPathNode(nindexSource, 1, 0, fNoMonsters);
	AddPathNode(nindexSource, -1, 0, fNoMonsters);
	AddPathNode(nindexSource, 0, 1, fNoMonsters);
	AddPathNode(nindexSource, 0, -1, fNoMonsters);
	AddPathNode(nindexSource, 1, 1, fNoMonsters);
	AddPathNode(nindexSource, 1, -1, fNoMonsters);
	AddPathNode(nindexSource, -1, 1, fNoMonsters);
	AddPathNode(nindexSource, -1, -1, fNoMonsters);
}

void CLocalNav::AddPathNode(node_index_t nindexSource, int offsetX, int offsetY, BOOL fNoMonsters)
{
	byte bDepth;
	Vector vecSource, vecDest;
	int offsetXAbs, offsetYAbs;

	if (nindexSource == NODE_INVALID_EMPTY)
	{
		bDepth = 1;

		offsetXAbs = offsetX;
		offsetYAbs = offsetY;

		vecSource = m_vecStartingLoc;
		vecDest = vecSource + Vector(real_t(offsetX) * HOSTAGE_STEPSIZE, real_t(offsetY) * HOSTAGE_STEPSIZE, 0);
	}
	else
	{
		localnode_t *nodeSource;
		localnode_t *nodeCurrent;
		node_index_t nindexCurrent;

		nodeCurrent = GetNode(nindexSource);
		offsetXAbs = offsetX + nodeCurrent->offsetX;
		offsetYAbs = offsetY + nodeCurrent->offsetY;
		nodeSource = GetNode(m_nindexAvailableNode);

		// if there exists a node, then to ignore adding a the new node
		if (NodeExists(offsetXAbs, offsetYAbs) != NODE_INVALID_EMPTY)
		{
			return;
		}

		vecSource = nodeCurrent->vecLoc;
		vecDest = vecSource + Vector((real_t(offsetX) * HOSTAGE_STEPSIZE), (real_t(offsetY) * HOSTAGE_STEPSIZE), 0);

		if (m_nindexAvailableNode)
		{
			nindexCurrent = m_nindexAvailableNode;

			do
			{
				nodeSource--;
				nindexCurrent--;

				offsetX = (nodeSource->offsetX - offsetXAbs);

				if (offsetX >= 0)
				{
					if (offsetX > 1)
					{
						continue;
					}
				}
				else
				{
					if (-offsetX > 1)
					{
						continue;
					}
				}

				offsetY = (nodeSource->offsetY - offsetYAbs);

				if (offsetY >= 0)
				{
					if (offsetY > 1)
					{
						continue;
					}
				}
				else
				{
					if (-offsetY > 1)
					{
						continue;
					}
				}

				if (PathTraversable(nodeSource->vecLoc, vecDest, fNoMonsters) != PTRAVELS_EMPTY)
				{
					nodeCurrent = nodeSource;
					nindexSource = nindexCurrent;
				}
			}
			while (nindexCurrent);
		}

		vecSource = nodeCurrent->vecLoc;
		bDepth = (nodeCurrent->bDepth + 1) & 0xff;
	}

	if (PathTraversable(vecSource, vecDest, fNoMonsters) != PTRAVELS_EMPTY)
	{
		AddNode(nindexSource, vecDest, offsetXAbs, offsetYAbs, bDepth);
	}
}

node_index_t CLocalNav::GetBestNode(Vector &vecOrigin, Vector &vecDest)
{
	node_index_t nindexCurrent;
	localnode_t *nodeCurrent;
	node_index_t nindexBest;
	float flBestVal;

	nindexBest = NODE_INVALID_EMPTY;
	nindexCurrent = 0;
	flBestVal = 1000000.0;

	while (nindexCurrent < m_nindexAvailableNode)
	{
		nodeCurrent = GetNode(nindexCurrent);

		if (!nodeCurrent->fSearched)
		{
			real_t flCurrentVal;
			real_t flDistFromStart;

			float flDistToDest;
			real_t flZDiff = -1.0;

			flDistFromStart = LengthSubtract<real_t, real_t, real_t, real_t>(vecDest, nodeCurrent->vecLoc);

			flDistToDest = nodeCurrent->vecLoc.z - vecDest.z;
			if (flDistToDest >= 0.0)
			{
				flZDiff = 1.0;
			}

			if ((flDistToDest * flZDiff) <= m_flStepSize)
				flZDiff = 1.0;
			else
				flZDiff = 1.25;

			flCurrentVal = flZDiff * (real_t(nodeCurrent->bDepth) * HOSTAGE_STEPSIZE + flDistFromStart);
			if (flCurrentVal < flBestVal)
			{
				flBestVal = flCurrentVal;
				nindexBest = nindexCurrent;
			}
		}

		nindexCurrent++;
	}

	return nindexBest;
}

int CLocalNav::SetupPathNodes(node_index_t nindex, Vector *vecNodes, BOOL fNoMonsters)
{
	node_index_t nCurrentIndex = nindex;
	int nNodeCount = 0;

	while (nCurrentIndex != NODE_INVALID_EMPTY)
	{
		localnode_t *nodeCurrent = GetNode(nCurrentIndex);
		Vector vecCurrentLoc = nodeCurrent->vecLoc;
		vecNodes[nNodeCount++] = vecCurrentLoc;

		nCurrentIndex = nodeCurrent->nindexParent;
	}

	return nNodeCount;
}

node_index_t CLocalNav::GetFurthestTraversableNode(Vector &vecStartingLoc, Vector *vecNodes, int nTotalNodes, BOOL fNoMonsters)
{
	int nCount = 0;
	while (nCount < nTotalNodes)
	{
		if (PathTraversable(vecStartingLoc, vecNodes[nCount], fNoMonsters) != PTRAVELS_EMPTY)
			return nCount;

		nCount++;
	}

	return NODE_INVALID_EMPTY;
}

node_index_t CLocalNav::FindPath(Vector &vecStart, Vector &vecDest, float flTargetRadius, BOOL fNoMonsters)
{
	node_index_t nIndexBest = FindDirectPath(vecStart, vecDest, flTargetRadius, fNoMonsters);

	if (nIndexBest != NODE_INVALID_EMPTY)
	{
		return nIndexBest;
	}

	localnode_t *node;
	Vector vecNodeLoc;
	real_t flDistToDest;

	m_vecStartingLoc = vecStart;
	m_nindexAvailableNode = 0;

	AddPathNodes(NODE_INVALID_EMPTY, fNoMonsters);
	nIndexBest = GetBestNode(vecStart, vecDest);

	while (nIndexBest != NODE_INVALID_EMPTY)
	{
		node = GetNode(nIndexBest);
		node->fSearched = TRUE;

		vecNodeLoc = node->vecLoc;
		flDistToDest = (vecDest - node->vecLoc).Length2D();

		if (flDistToDest <= flTargetRadius)
			break;

		if (flDistToDest <= HOSTAGE_STEPSIZE)
			break;

		if (((flDistToDest - flTargetRadius) > ((MAX_NODES - m_nindexAvailableNode) * HOSTAGE_STEPSIZE))
			|| m_nindexAvailableNode == MAX_NODES)
		{
			nIndexBest = NODE_INVALID_EMPTY;
			break;
		}

		AddPathNodes(nIndexBest, fNoMonsters);
		nIndexBest = GetBestNode(vecNodeLoc, vecDest);
	}

	if (m_nindexAvailableNode <= 10)
		m_NodeValue += 2;

	else if (m_nindexAvailableNode <= 20)
		m_NodeValue += 4;

	else if (m_nindexAvailableNode <= 30)
		m_NodeValue += 8;

	else if (m_nindexAvailableNode <= 40)
		m_NodeValue += 13;

	else if (m_nindexAvailableNode <= 50)
		m_NodeValue += 19;

	else if (m_nindexAvailableNode <= 60)
		m_NodeValue += 26;

	else if (m_nindexAvailableNode <= 70)
		m_NodeValue += 34;

	else if (m_nindexAvailableNode <= 80)
		m_NodeValue += 43;

	else if (m_nindexAvailableNode <= 90)
		m_NodeValue += 53;

	else if (m_nindexAvailableNode <= 100)
		m_NodeValue += 64;

	else if (m_nindexAvailableNode <= 110)
		m_NodeValue += 76;

	else if (m_nindexAvailableNode <= 120)
		m_NodeValue += 89;

	else if (m_nindexAvailableNode <= 130)
		m_NodeValue += 103;

	else if (m_nindexAvailableNode <= 140)
		m_NodeValue += 118;

	else if (m_nindexAvailableNode <= 150)
		m_NodeValue += 134;

	else if (m_nindexAvailableNode <= 160)
		m_NodeValue += 151;
	else
		m_NodeValue += 169;

	return nIndexBest;
}

node_index_t CLocalNav::FindDirectPath(Vector &vecStart, Vector &vecDest, float flTargetRadius, BOOL fNoMonsters)
{
	Vector vecActualDest;
	Vector vecPathDir;
	Vector vecNodeLoc;
	node_index_t nIndexLast;

	vecPathDir = NormalizeSubtract<real_t, float, float, real_t>(vecStart, vecDest);
	vecActualDest = vecDest - (vecPathDir * flTargetRadius);

	if (PathTraversable(vecStart, vecActualDest, fNoMonsters) == PTRAVELS_EMPTY)
	{
		return NODE_INVALID_EMPTY;
	}

	nIndexLast = NODE_INVALID_EMPTY;
	vecNodeLoc = vecStart;
	m_nindexAvailableNode = 0;

	while ((vecNodeLoc - vecActualDest).Length2D() >= HOSTAGE_STEPSIZE)
	{
		node_index_t nindexCurrent = nIndexLast;

		vecNodeLoc = vecNodeLoc + (vecPathDir * HOSTAGE_STEPSIZE);
		nIndexLast = AddNode(nindexCurrent, vecNodeLoc);

		if (nIndexLast == NODE_INVALID_EMPTY)
			break;
	}

	return nIndexLast;
}

BOOL CLocalNav::PathClear(Vector &vecOrigin, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr)
{
	TRACE_MONSTER_HULL(m_pOwner->edict(), vecOrigin, vecDest, fNoMonsters, m_pOwner->edict(), &tr);

	if (tr.fStartSolid)
		return FALSE;

	if (tr.flFraction == 1.0f)
		return TRUE;

	if (tr.pHit == m_pTargetEnt)
	{
		m_fTargetEntHit = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL CLocalNav::PathClear(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters)
{
	TraceResult tr;
	return PathClear(vecSource, vecDest, fNoMonsters, tr);
}

PathTraversAble CLocalNav::PathTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters)
{
	TraceResult tr;
	Vector vecSrcTmp;
	Vector vecDestTmp;
	Vector vecDir;
	real_t flTotal;
	auto retval = PTRAVELS_EMPTY;

	vecSrcTmp = vecSource;
	vecDestTmp = vecDest - vecSource;

	vecDir = vecDestTmp.NormalizePrecision();
	vecDir.z = 0;

	flTotal = vecDestTmp.Length2D();

	while (flTotal > 1.0f)
	{
		if (flTotal >= m_flStepSize)
		{
#ifndef PLAY_GAMEDLL
			vecDestTmp = vecSrcTmp + (vecDir * m_flStepSize);
#else
			// TODO: fix test demo
			vecDestTmp[0] = vecSrcTmp[0] + (vecDir[0] * m_flStepSize);
			vecDestTmp[1] = vecSrcTmp[1] + float(vecDir[1] * m_flStepSize);
			vecDestTmp[2] = vecSrcTmp[2] + (vecDir[2] * m_flStepSize);
#endif

		}
		else
			vecDestTmp = vecDest;

		m_fTargetEntHit = FALSE;

		if (PathClear(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
		{
			vecDestTmp = tr.vecEndPos;

			if (retval == PTRAVELS_EMPTY)
			{
				retval = PTRAVELS_SLOPE;
			}
		}
		else
		{
			if (tr.fStartSolid)
			{
				return PTRAVELS_EMPTY;
			}

			if (tr.pHit && !fNoMonsters && tr.pHit->v.classname)
			{
				if (FClassnameIs(tr.pHit, "hostage_entity"))
				{
					return PTRAVELS_EMPTY;
				}
			}

			vecSrcTmp = tr.vecEndPos;

			if (tr.vecPlaneNormal.z <= MaxUnitZSlope)
			{
				if (StepTraversable(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
				{
					if (retval == PTRAVELS_EMPTY)
					{
						retval = PTRAVELS_STEP;
					}
				}
				else
				{
					if (!StepJumpable(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
					{
						return PTRAVELS_EMPTY;
					}

					if (retval == PTRAVELS_EMPTY)
					{
						retval = PTRAVELS_STEPJUMPABLE;
					}
				}
			}
			else
			{
				if (!SlopeTraversable(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
				{
					return PTRAVELS_EMPTY;
				}

				if (retval == PTRAVELS_EMPTY)
				{
					retval = PTRAVELS_SLOPE;
				}
			}
		}

		Vector vecDropDest = vecDestTmp - Vector(0, 0, 300);

		if (PathClear(vecDestTmp, vecDropDest, fNoMonsters, tr))
		{
			return PTRAVELS_EMPTY;
		}

		if (!tr.fStartSolid)
			vecDestTmp = tr.vecEndPos;

		vecSrcTmp = vecDestTmp;

		BOOL fProgressThisTime = m_fTargetEntHit;
		Vector vecSrcThisTime = vecDest - vecDestTmp;

		if (fProgressThisTime)
			break;

		flTotal = vecSrcThisTime.Length2D();
	}

	vecDest = vecDestTmp;

	return retval;
}

BOOL CLocalNav::SlopeTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr)
{
	Vector vecSlopeEnd;
	Vector vecDown;
	Vector vecAngles;

	vecSlopeEnd = vecDest;
	vecDown = vecDest - vecSource;

	vecAngles = UTIL_VecToAngles(tr.vecPlaneNormal);
	vecSlopeEnd.z = vecDown.Length2D() * Q_tan(real_t((90.0 - vecAngles.x) * (M_PI / 180))) + vecSource.z;

	if (!PathClear(vecSource, vecSlopeEnd, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
			return FALSE;

		if ((tr.vecEndPos - vecSource).Length2D() < 1.0f)
			return FALSE;
	}

	vecSlopeEnd = tr.vecEndPos;

	vecDown = vecSlopeEnd;
	vecDown.z -= m_flStepSize;

	if (!PathClear(vecSlopeEnd, vecDown, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
		{
			vecDest = vecSlopeEnd;
			return TRUE;
		}
	}

	vecDest = tr.vecEndPos;
	return TRUE;
}

BOOL CLocalNav::LadderTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr)
{
	Vector vecStepStart;
	Vector vecStepDest;

	vecStepStart = tr.vecEndPos;
	vecStepDest = vecStepStart;
	vecStepDest.z += HOSTAGE_STEPSIZE;

	if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
			return FALSE;

		if ((tr.vecEndPos - vecStepStart).Length() < 1.0f)
			return FALSE;
	}

	vecStepStart = tr.vecEndPos;
	vecDest.z = tr.vecEndPos.z;

	return PathTraversable(vecStepStart, vecDest, fNoMonsters);
}

BOOL CLocalNav::StepTraversable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr)
{
	Vector vecStepStart;
	Vector vecStepDest;
	//BOOL fFwdTrace = FALSE; // unused?
	float flFwdFraction;

	vecStepStart = vecSource;
	vecStepDest = vecDest;

	vecStepStart.z += m_flStepSize;
	vecStepDest.z = vecStepStart.z;

	if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
			return FALSE;

		flFwdFraction = (tr.vecEndPos - vecStepStart).Length();

		if (flFwdFraction < 1.0f)
			return FALSE;
	}

	vecStepStart = tr.vecEndPos;

	vecStepDest = vecStepStart;
	vecStepDest.z -= m_flStepSize;

	if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
		{
			vecDest = vecStepStart;
			return TRUE;
		}
	}

	vecDest = tr.vecEndPos;
	return TRUE;
}

BOOL CLocalNav::StepJumpable(Vector &vecSource, Vector &vecDest, BOOL fNoMonsters, TraceResult &tr)
{
	Vector vecStepStart;
	Vector vecStepDest;
	float flFwdFraction;
	float flJumpHeight = m_flStepSize + 1.0f;

	vecStepStart = vecSource;
	vecStepStart.z += flJumpHeight;

	while (flJumpHeight < 40.0f)
	{
		vecStepDest = vecDest;
		vecStepDest.z = vecStepStart.z;

		if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
		{
			if (tr.fStartSolid)
				break;

			flFwdFraction = (tr.vecEndPos - vecStepStart).Length2D();

			if (flFwdFraction < 1.0f)
			{
				flJumpHeight += 10.0f;
				vecStepStart.z += 10.0f;

				continue;
			}
		}

		vecStepStart = tr.vecEndPos;
		vecStepDest = vecStepStart;
		vecStepDest.z -= m_flStepSize;

		if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
		{
			if (tr.fStartSolid)
			{
				vecDest = vecStepStart;
				return TRUE;
			}
		}

		vecDest = tr.vecEndPos;
		return TRUE;
	}

	return FALSE;
}

BOOL CLocalNav::LadderHit(Vector &vecSource, Vector &vecDest, TraceResult &tr)
{
	Vector vecFwd, vecRight, vecUp;
	Vector vecAngles, vecOrigin;

	vecAngles = UTIL_VecToAngles(-tr.vecPlaneNormal);
	UTIL_MakeVectorsPrivate(vecAngles, vecFwd, vecRight, vecUp);
	vecOrigin = tr.vecEndPos + (vecFwd * 15) + (vecUp * 36);

	if (UTIL_PointContents(vecOrigin) == CONTENTS_LADDER)
		return true;

	vecOrigin = tr.vecEndPos + (vecFwd * 15) - (vecUp * 36);

	if (UTIL_PointContents(vecOrigin) == CONTENTS_LADDER)
		return true;

	vecOrigin = tr.vecEndPos + (vecFwd * 15) + (vecRight * 16) + (vecUp * 36);

	if (UTIL_PointContents(vecOrigin) == CONTENTS_LADDER)
		return true;

	vecOrigin = tr.vecEndPos + (vecFwd * 15) - (vecRight * 16) + (vecUp * 36);

	if (UTIL_PointContents(vecOrigin) == CONTENTS_LADDER)
		return true;

	vecOrigin = tr.vecEndPos + (vecFwd * 15) + (vecRight * 16) - (vecUp * 36);

	if (UTIL_PointContents(vecOrigin) == CONTENTS_LADDER)
		return true;

	vecOrigin = tr.vecEndPos + (vecFwd * 15) - (vecRight * 16) + (vecUp * 36);

	if (UTIL_PointContents(vecOrigin) == CONTENTS_LADDER)
		return true;

	return false;
}

void CLocalNav::Think()
{
	if (gpGlobals->time >= m_flNextCvarCheck)
	{
		if (g_psv_stepsize)
		{
			m_flStepSize = g_psv_stepsize->value;
		}

		m_flNextCvarCheck = gpGlobals->time + 1.0f;
	}

	HostagePrethink();

	float flElapsedTime = gpGlobals->time - m_flLastThinkTime;
	m_NodeValue -= flElapsedTime * 250;
	m_flLastThinkTime = gpGlobals->time;

	if (m_NodeValue < 0)
		m_NodeValue = 0;

	else if (m_NodeValue > 17)
		return;

	if (m_NumRequest)
	{
		auto hHostage = m_hQueue[m_CurRequest];
		while (!hHostage.IsValid() && m_NumRequest > 0)
		{
			if (++m_CurRequest == MAX_HOSTAGES_NAV)
				m_CurRequest = 0;

			m_NumRequest--;
			if (m_NumRequest <= 0)
			{
				hHostage = nullptr;
				break;
			}

			hHostage = m_hQueue[m_CurRequest];
		}

		if (hHostage.IsValid())
		{
			if (++m_CurRequest == MAX_HOSTAGES_NAV)
				m_CurRequest = 0;

			m_NumRequest--;
			hHostage->NavReady();
		}
	}
}

void CLocalNav::RequestNav(CHostage *pCaller)
{
	int curr = m_CurRequest;
	int found = 0;

	if (m_NodeValue <= 17 && !m_NumRequest)
	{
		pCaller->NavReady();
		return;
	}

	if (m_NumRequest >= MAX_HOSTAGES_NAV)
	{
		return;
	}

	for (int i = 0; i < m_NumRequest; i++)
	{
		if (m_hQueue[curr] == pCaller)
			return;

		if (++curr == MAX_HOSTAGES_NAV)
			curr = 0;
	}

	m_hQueue[curr] = pCaller;
	m_NumRequest++;
}

void CLocalNav::Reset()
{
	m_flNextCvarCheck = 0.0f;
	m_flLastThinkTime = 0.0f;

	m_NumRequest = 0;
	m_CurRequest = 0;
	m_NumHostages = 0;
	m_NodeValue = 0;
}

void CLocalNav::HostagePrethink()
{
	for (int i = 0; i < m_NumHostages; i++)
	{
		if (m_hHostages[i].IsValid()) {
			m_hHostages[i]->PreThink();
		}
	}
}
