#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

float CLocalNav::s_flStepSize;
int CLocalNav::qptr;
EHANDLE CLocalNav::_queue[ MAX_HOSTAGES_NAV ];
int CLocalNav::tot_inqueue;
float CLocalNav::nodeval;
float CLocalNav::flNextCvarCheck;
float CLocalNav::flLastThinkTime;
EHANDLE CLocalNav::hostages[ MAX_HOSTAGES_NAV ];
int CLocalNav::tot_hostages;

#else

float (*CLocalNav::ps_flStepSize);
int (*CLocalNav::pqptr);
EHANDLE (*CLocalNav::pqueue)[ MAX_HOSTAGES_NAV ];
int (*CLocalNav::ptot_inqueue);
float (*CLocalNav::pnodeval);
float (*CLocalNav::pflNextCvarCheck);
float (*CLocalNav::pflLastThinkTime);
EHANDLE (*CLocalNav::phostages)[ MAX_HOSTAGES_NAV ];
int (*CLocalNav::ptot_hostages);

#endif // HOOK_GAMEDLL

/* <485b67> ../cstrike/dlls/hostage/hostage_localnav.cpp:45 */
NOBODY CLocalNav::CLocalNav(CHostage *pOwner)
{
}

/* <485b09> ../cstrike/dlls/hostage/hostage_localnav.cpp:68 */
NOBODY CLocalNav::~CLocalNav(void)
{
//	~CLocalNav(CLocalNav::~CLocalNav(//			int const __in_chrg);  //    71
}

/* <485b91> ../cstrike/dlls/hostage/hostage_localnav.cpp:74 */
NOXREF node_index_t CLocalNav::AddNode(node_index_t nindexParent, Vector &vecLoc, int offsetX, int offsetY, byte bDepth)
{
	localnode_t *nodeNew;

	if (m_nindexAvailableNode == MAX_NODES)
		return -1;

	nodeNew = GetNode(m_nindexAvailableNode);

	nodeNew->vecLoc = vecLoc;
	nodeNew->offsetX = offsetX;
	nodeNew->offsetY = offsetY;
	nodeNew->bDepth = bDepth;
	nodeNew->fSearched = FALSE;
	nodeNew->nindexParent = nindexParent;

	return m_nindexAvailableNode++;
}

/* <485570> ../cstrike/dlls/hostage/hostage_localnav.cpp:94 */
NOXREF localnode_t *CLocalNav::GetNode(node_index_t nindex)
{
	return &m_nodeArr[ nindex ];
}

/* <485c01> ../cstrike/dlls/hostage/hostage_localnav.cpp:100 */
NOXREF node_index_t CLocalNav::NodeExists(int offsetX, int offsetY)
{
	node_index_t nindexCurrent;
	localnode_t *nodeCurrent;

	for (nindexCurrent = m_nindexAvailableNode - 1; nindexCurrent != 0; nindexCurrent--)
	{
		nodeCurrent = GetNode(nindexCurrent);

		if (nodeCurrent->offsetX == offsetX && nodeCurrent->offsetY == offsetY)
			return nindexCurrent;
	}
	return -1;
}

/* <486d46> ../cstrike/dlls/hostage/hostage_localnav.cpp:123 */
NOBODY void CLocalNav::AddPathNodes(node_index_t nindexSource, int fNoMonsters)
{
}

/* <486adb> ../cstrike/dlls/hostage/hostage_localnav.cpp:138 */
NOBODY void CLocalNav::AddPathNode(node_index_t nindexSource, int offsetX, int offsetY, int fNoMonsters)
{
//	{
//		int bDepth;                                           //   140
//		Vector vecSource;                               //   141
//		Vector vecDest;                                 //   142
//		int offsetXAbs;                                       //   143
//		int offsetYAbs;                                       //   144
//		{
//			localnode_t *nodeSource;                     //   156
//			localnode_t *nodeCurrent;                    //   157
//			node_index_t nindexCurrent;                   //   158
//			GetNode(CLocalNav *const this,
//				node_index_t nindex);  //   160
//			NodeExists(CLocalNav *const this,
//					int offsetX,
//					int offsetY);  //   166
//			operator+(const Vector *const this,
//					const Vector &v);  //   170
//			operator*(const Vector *const this,
//					float fl);  //   170
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   149
//		operator*(const Vector *const this,
//				float fl);  //   149
//		AddNode(CLocalNav *const this,
//			node_index_t nindexParent,
//			Vector &vecLoc,
//			int offsetX,
//			int offsetY,
//			byte bDepth);  //   200
//	}
}

/* <485c63> ../cstrike/dlls/hostage/hostage_localnav.cpp:205 */
NOBODY node_index_t CLocalNav::GetBestNode(Vector &vecOrigin, Vector &vecDest)
{
//	{
//		node_index_t nindexCurrent;                           //   207
//		localnode_t *nodeCurrent;                            //   208
//		node_index_t nindexBest;                              //   209
//		float flBestVal;                                      //   210
//		{
//			float flCurrentVal;                           //   220
//			float flDistFromStart;                        //   221
//			float flDistToDest;                           //   222
//			float flZDiff;                                //   223
//			operator-(const Vector *const this,
//					const Vector &v);  //   235
//			Length(const Vector *const this);  //   235
//		}
//	}
}

/* <485d79> ../cstrike/dlls/hostage/hostage_localnav.cpp:263 */
NOBODY int CLocalNav::SetupPathNodes(node_index_t nindex, Vector *vecNodes, int fNoMonsters)
{
//	{
//		node_index_t nCurrentIndex;                           //   265
//		int nNodeCount;                                       //   266
//		{
//			localnode_t *nodeCurrent;                    //   273
//			Vector vecCurrentLoc;                   //   274
//			GetNode(CLocalNav *const this,
//				node_index_t nindex);  //   276
//		}
//	}
}

/* <486a56> ../cstrike/dlls/hostage/hostage_localnav.cpp:290 */
NOBODY int CLocalNav::GetFurthestTraversableNode(Vector &vecStartingLoc, Vector *vecNodes, int nTotalNodes, int fNoMonsters)
{
//	{
//		int nCount;                                           //   292
//	}
}

/* <486d8d> ../cstrike/dlls/hostage/hostage_localnav.cpp:304 */
NOBODY node_index_t CLocalNav::FindPath(Vector &vecStart, Vector &vecDest, float flTargetRadius, int fNoMonsters)
{
//	{
//		node_index_t nIndexBest;                              //   306
//		{
//			localnode_t *node;                           //   325
//			Vector vecNodeLoc;                      //   326
//			float flDistToDest;                           //   327
//			GetNode(CLocalNav *const this,
//				node_index_t nindex);  //   329
//			operator-(const Vector *const this,
//					const Vector &v);  //   332
//			Length2D(const Vector *const this);  //   332
//		}
//	}

	int nIndexBest;
	localnode_t *node;
	Vector vecNodeLoc;
	float flDistToDest;

	nIndexBest = FindDirectPath(vecStart, vecDest, flTargetRadius, fNoMonsters); // TODO: Reverse me!

	if (nIndexBest != -1)
		return nIndexBest;

	m_vecStartingLoc = vecStart;
	m_nindexAvailableNode = 0;
	AddPathNodes(-1, fNoMonsters);

	vecNodeLoc = vecStart;
	nIndexBest = GetBestNode(vecNodeLoc, vecDest); // TODO: Reverse me!

	while (nIndexBest != -1)
	{
		node = GetNode(nIndexBest);
		vecNodeLoc = node->vecLoc;
		node->fSearched = TRUE;
		flDistToDest = (vecDest - node->vecLoc).Length2D();

		if (flDistToDest <= flTargetRadius)
			break;

		if (flDistToDest <= HOSTAGE_STEPSIZE)
			break;

		if ((flDistToDest - flTargetRadius) > (MAX_NODES - m_nindexAvailableNode) * HOSTAGE_STEPSIZE || m_nindexAvailableNode == MAX_NODES)
		{
			nIndexBest = -1;
			break;
		}

		AddPathNodes(nIndexBest, fNoMonsters); // TODO: Reverse me!
		nIndexBest = GetBestNode(vecNodeLoc, vecDest); // TODO: Reverse me!
	}

	if (m_nindexAvailableNode <= 10)
		nodeval += 2;

	else if (m_nindexAvailableNode <= 20)
		nodeval += 4;

	else if (m_nindexAvailableNode <= 30)
		nodeval += 8;

	else if (m_nindexAvailableNode <= 40)
		nodeval += 13;

	else if (m_nindexAvailableNode <= 50)
		nodeval += 19;

	else if (m_nindexAvailableNode <= 60)
		nodeval += 26;

	else if (m_nindexAvailableNode <= 70)
		nodeval += 34;

	else if (m_nindexAvailableNode <= 80)
		nodeval += 43;

	else if (m_nindexAvailableNode <= 90)
		nodeval += 53;

	else if (m_nindexAvailableNode <= 100)
		nodeval += 64;

	else if (m_nindexAvailableNode <= 110)
		nodeval += 76;

	else if (m_nindexAvailableNode <= 120)
		nodeval += 89;

	else if (m_nindexAvailableNode <= 130)
		nodeval += 103;

	else if (m_nindexAvailableNode <= 140)
		nodeval += 118;

	else if (m_nindexAvailableNode <= 150)
		nodeval += 134;

	else if (m_nindexAvailableNode <= 160)
		nodeval += 151;
	else
		nodeval += 169;

	return nIndexBest;
}

/* <4867dc> ../cstrike/dlls/hostage/hostage_localnav.cpp:413 */
NOBODY node_index_t CLocalNav::FindDirectPath(Vector &vecStart, Vector &vecDest, float flTargetRadius, int fNoMonsters)
{
//	{
//		Vector vecActualDest;                           //   415
//		Vector vecPathDir;                              //   416
//		Vector vecNodeLoc;                              //   417
//		node_index_t nindexLast;                              //   418
//		operator-(const Vector *const this,
//				const Vector &v);  //   420
//		Normalize(const Vector *const this);  //   420
//		operator*(const Vector *const this,
//				float fl);  //   422
//		operator-(const Vector *const this,
//				const Vector &v);  //   422
//		operator-(const Vector *const this,
//				const Vector &v);  //   432
//		Length2D(const Vector *const this);  //   432
//		{
//			node_index_t nindexCurrent;                   //   434
//			AddNode(CLocalNav *const this,
//				node_index_t nindexParent,
//				Vector &vecLoc,
//				int offsetX,
//				int offsetY,
//				byte bDepth);  //   438
//			operator*(const Vector *const this,
//					float fl);  //   436
//			operator+(const Vector *const this,
//					const Vector &v);  //   436
//		}
//	}

	Vector vecActualDest;
	Vector vecPathDir;
	Vector vecNodeLoc;
	node_index_t nindexLast;

	vecPathDir = (vecDest - vecStart).Normalize();
	vecActualDest = vecDest - (vecPathDir * flTargetRadius);

	if (!PathTraversable(vecStart, vecActualDest, fNoMonsters)) // TODO: Reverse me!
		return -1;

	m_nindexAvailableNode = 0;
	nindexLast = -1;
	vecNodeLoc = vecStart;

	while ((vecNodeLoc - vecActualDest).Length2D() >= HOSTAGE_STEPSIZE)
	{
		vecNodeLoc = vecNodeLoc + (vecPathDir * HOSTAGE_STEPSIZE);
		nindexLast = AddNode(nindexLast, vecNodeLoc, 0, 0, 0); // TODO: Reverse me!

		if (nindexLast == -1)
			break;
	}

	return nindexLast;



}

/* <485e40> ../cstrike/dlls/hostage/hostage_localnav.cpp:449 */
BOOL CLocalNav::PathClear(Vector &vecOrigin, Vector &vecDest, int fNoMonsters, TraceResult &tr)
{
	TRACE_MONSTER_HULL(m_pOwner->edict(), vecOrigin, vecDest, fNoMonsters, m_pOwner->edict(), &tr);

	if (tr.fStartSolid)
		return FALSE;

	if (tr.flFraction == 1.0)
		return TRUE;

	if (tr.pHit == m_pTargetEnt)
	{
		m_fTargetEntHit = TRUE;
		return TRUE;
	}
	return FALSE;
}

/* <485ecf> ../cstrike/dlls/hostage/hostage_localnav.cpp:472 */
int CLocalNav::PathTraversable(Vector &vecSource, Vector &vecDest, int fNoMonsters)
{
	TraceResult tr;
	Vector vecSrcTmp;
	Vector vecDestTmp;
	Vector vecDir;
	double flTotal;
	int retval = PATH_TRAVERSABLE_EMPTY;

	vecSrcTmp = vecSource;
	vecDestTmp = vecDest - vecSource;

	vecDir = vecDestTmp.Normalize();
	vecDir.z = 0;

	flTotal = vecDestTmp.Length2D();

	while (flTotal > 1.0)
	{
		if (flTotal >= s_flStepSize)
		{
#ifdef HOOK_GAMEDLL
			vecDestTmp.x = vecSrcTmp.x + (vecDir.x * s_flStepSize);
			vecDestTmp.y = vecSrcTmp.y + (float)(vecDir.y * s_flStepSize);
			vecDestTmp.z = vecSrcTmp.z + (vecDir.z * s_flStepSize);
#else
			vecDestTmp = vecSrcTmp + (vecDir * s_flStepSize);
#endif // HOOK_GAMEDLL
		}
		else
			vecDestTmp = vecDest;

		m_fTargetEntHit = FALSE;

		if (PathClear(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
		{
			vecDestTmp = tr.vecEndPos;

			if (retval == PATH_TRAVERSABLE_EMPTY)
				retval = PATH_TRAVERSABLE_SLOPE;
		}
		else
		{
			if (tr.fStartSolid)
				return PATH_TRAVERSABLE_EMPTY;

			if (tr.pHit && !fNoMonsters && tr.pHit->v.classname)
			{
				if (FClassnameIs(tr.pHit, "hostage_entity"))
					return PATH_TRAVERSABLE_EMPTY;
			}

			vecSrcTmp = tr.vecEndPos;

			if (tr.vecPlaneNormal.z <= 0.7)
			{
				if (StepTraversable(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
				{
					if (retval == PATH_TRAVERSABLE_EMPTY)
						retval = PATH_TRAVERSABLE_STEP;
				}
				else
				{
					if (!StepJumpable(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
						return PATH_TRAVERSABLE_EMPTY;

					if (retval == PATH_TRAVERSABLE_EMPTY)
						retval = PATH_TRAVERSABLE_STEPJUMPABLE;
				}
			}
			else
			{
				if (!SlopeTraversable(vecSrcTmp, vecDestTmp, fNoMonsters, tr))
					return PATH_TRAVERSABLE_EMPTY;

				if (retval == PATH_TRAVERSABLE_EMPTY)
					retval = PATH_TRAVERSABLE_SLOPE;
			}
		}

		Vector vecDropDest = vecDestTmp - Vector(0, 0, 300);

		if (PathClear(vecDestTmp, vecDropDest, fNoMonsters, tr))
			return PATH_TRAVERSABLE_EMPTY;

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

/* <486ea0> ../cstrike/dlls/hostage/hostage_localnav.cpp:593 */
BOOL CLocalNav::SlopeTraversable(Vector &vecSource, Vector &vecDest, int fNoMonsters, TraceResult &tr)
{
	Vector vecSlopeEnd;
	Vector vecDown;
	Vector vecAngles;

	vecSlopeEnd = vecDest;
	vecDown = vecDest - vecSource;

	vecAngles = UTIL_VecToAngles(tr.vecPlaneNormal);
	vecSlopeEnd.z = vecDown.Length2D() * tan((double)((90.0 - vecAngles.x) * (M_PI / 180))) + vecSource.z;

	if (!PathClear(vecSource, vecSlopeEnd, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
			return FALSE;

		if ((tr.vecEndPos - vecSource).Length2D() < 1.0)
			return FALSE;
	}

	vecSlopeEnd = tr.vecEndPos;

	vecDown = vecSlopeEnd;
	vecDown.z -= s_flStepSize;

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

/* <487085> ../cstrike/dlls/hostage/hostage_localnav.cpp:635 */
NOBODY BOOL CLocalNav::LadderTraversable(Vector &vecSource, Vector &vecDest, int fNoMonsters, TraceResult &tr)
{
//	{
//		Vector vecLadderStart;                          //   637
//		Vector vecLadderDest;                           //   638
//		PathClear(CLocalNav *const this,
//				Vector &vecOrigin,
//				Vector &vecDest,
//				int fNoMonsters,
//				TraceResult &tr);  //   646
//		operator-(const Vector *const this,
//				const Vector &v);  //   651
//		Length(const Vector *const this);  //   651
//	}
}

/* <4871ef> ../cstrike/dlls/hostage/hostage_localnav.cpp:662 */
BOOL CLocalNav::StepTraversable(Vector &vecSource, Vector &vecDest, int fNoMonsters, TraceResult &tr)
{
	Vector vecStepStart;
	Vector vecStepDest;
	//BOOL fFwdTrace = FALSE; // unused?
	float flFwdFraction;

	vecStepStart = vecSource;
	vecStepDest = vecDest;

	vecStepStart.z += s_flStepSize;
	vecStepDest.z = vecStepStart.z;

	if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
	{
		if (tr.fStartSolid)
			return FALSE;

		flFwdFraction = (tr.vecEndPos - vecStepStart).Length();

		if (flFwdFraction < 1.0)
			return FALSE;
	}

	vecStepStart = tr.vecEndPos;

	vecStepDest = vecStepStart;
	vecStepDest.z -= s_flStepSize;

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

/* <4873b3> ../cstrike/dlls/hostage/hostage_localnav.cpp:713 */
BOOL CLocalNav::StepJumpable(Vector &vecSource, Vector &vecDest, int fNoMonsters, TraceResult &tr)
{
	Vector vecStepStart;
	Vector vecStepDest;
	//BOOL fFwdTrace = FALSE; // unused?
	float flFwdFraction;
	float flJumpHeight = s_flStepSize + 1.0;
	//BOOL fJumpClear = FALSE; // unused?
	//edict_t *hit = NULL; // unused?

	vecStepStart = vecSource;
	vecStepStart.z += flJumpHeight;

	while (flJumpHeight < 40.0)
	{
		vecStepDest = vecDest;
		vecStepDest.z = vecStepStart.z;

		if (!PathClear(vecStepStart, vecStepDest, fNoMonsters, tr))
		{
			if (tr.fStartSolid)
				break;

			flFwdFraction = (tr.vecEndPos - vecStepStart).Length2D();

			if (flFwdFraction < 1.0)
			{
				flJumpHeight += 10.0;
				vecStepStart.z += 10.0;

				continue;
			}
		}

		vecStepStart = tr.vecEndPos;
		vecStepDest = vecStepStart;
		vecStepDest.z -= s_flStepSize;

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

/* <487588> ../cstrike/dlls/hostage/hostage_localnav.cpp:824 */
NOBODY BOOL CLocalNav::LadderHit(Vector &vecSource, Vector &vecDest, TraceResult &tr)
{
//	{
//		Vector vecFwd;                                  //   826
//		Vector vecRight;                                //   827
//		Vector vecUp;                                   //   828
//		operator-(const Vector *const this);  //   832
//		UTIL_MakeVectorsPrivate(Vector &vecAngles,
//					float *p_vForward,
//					float *p_vRight,
//					float *p_vUp);  //   832
//		operator*(const Vector *const this,
//				float fl);  //   834
//		operator*(const Vector *const this,
//				float fl);  //   834
//		operator+(const Vector *const this,
//				const Vector &v);  //   834
//		operator+(const Vector *const this,
//				const Vector &v);  //   834
//		operator*(const Vector *const this,
//				float fl);  //   836
//		operator+(const Vector *const this,
//				const Vector &v);  //   836
//		operator*(const Vector *const this,
//				float fl);  //   836
//		operator-(const Vector *const this,
//				const Vector &v);  //   836
//		operator*(const Vector *const this,
//				float fl);  //   838
//		operator*(const Vector *const this,
//				float fl);  //   838
//		operator*(const Vector *const this,
//				float fl);  //   838
//		operator+(const Vector *const this,
//				const Vector &v);  //   838
//		operator+(const Vector *const this,
//				const Vector &v);  //   838
//		operator+(const Vector *const this,
//				const Vector &v);  //   838
//		operator*(const Vector *const this,
//				float fl);  //   840
//		operator*(const Vector *const this,
//				float fl);  //   840
//		operator+(const Vector *const this,
//				const Vector &v);  //   840
//		operator*(const Vector *const this,
//				float fl);  //   840
//		operator-(const Vector *const this,
//				const Vector &v);  //   840
//		operator+(const Vector *const this,
//				const Vector &v);  //   840
//		operator*(const Vector *const this,
//				float fl);  //   842
//		operator*(const Vector *const this,
//				float fl);  //   842
//		operator+(const Vector *const this,
//				const Vector &v);  //   842
//		operator+(const Vector *const this,
//				const Vector &v);  //   842
//		operator*(const Vector *const this,
//				float fl);  //   842
//		operator-(const Vector *const this,
//				const Vector &v);  //   842
//		operator*(const Vector *const this,
//				float fl);  //   844
//		operator+(const Vector *const this,
//				const Vector &v);  //   844
//		operator*(const Vector *const this,
//				float fl);  //   844
//		operator-(const Vector *const this,
//				const Vector &v);  //   844
//		operator*(const Vector *const this,
//				float fl);  //   844
//		operator-(const Vector *const this,
//				const Vector &v);  //   844
//	}
}

/* <487eeb> ../cstrike/dlls/hostage/hostage_localnav.cpp:851 */
void CLocalNav::Think(void)
{
//	{
//		float flElapsedTime;                                  //   853
//		class EHANDLE hCallback;                              //   854
//		cvar_t *sv_stepsize;                                 //   855
//		{
//			class CHostage *pHostage;                    //   909
//			GetClassPtr<CHostage>(CHostage *a);  //   911
//		}
//	}

	EHANDLE hostage;
	static cvar_t *sv_stepsize = NULL;

	if (flNextCvarCheck <= gpGlobals->time)
	{
		if (sv_stepsize)
		{
			flNextCvarCheck = gpGlobals->time + 1;
			s_flStepSize = sv_stepsize->value;
		}
		else
		{
			sv_stepsize = CVAR_GET_POINTER("sv_stepsize");
			flNextCvarCheck = gpGlobals->time + 1;
			s_flStepSize = s_flStepSize ? sv_stepsize->value : 18;
		}
	}

	HostagePrethink();
	nodeval -= (gpGlobals->time - flLastThinkTime) * 250;
	flLastThinkTime = gpGlobals->time;

	if (nodeval < 0)
		nodeval = 0;

	else if (nodeval > 17)
		return;

	if (tot_inqueue)
	{
#ifndef REGAMEDLL_FIXES
		hostage = NULL;
#endif // REGAMEDLL_FIXES
		hostage = _queue[ qptr ];

		if (!hostage)
		{
			while (tot_inqueue > 0)
			{
				if (++qptr == MAX_HOSTAGES_NAV)
					qptr = 0;

				tot_inqueue--;
				if (!tot_inqueue)
				{
					hostage = NULL;
					break;
				}

				hostage = _queue[ qptr ];

				if (hostage)
					break;
			}
		}

		if (hostage)
		{
			CHostage *pHostage = GetClassPtr((CHostage *)hostage->pev);

			if (++qptr == MAX_HOSTAGES_NAV)
				qptr = 0;

			tot_inqueue--;
			pHostage->NavReady();
		}
	}
}

/* <487ccd> ../cstrike/dlls/hostage/hostage_localnav.cpp:922 */
void CLocalNav::RequestNav(CHostage *pCaller)
{
//	{
//		int curr;                                             //   932
//		int found;                                            //   933
//		{
//			int i;                                        //   934
//			{
//				class CHostage *pQueueItem;          //   936
//				GetClassPtr<CHostage>(CHostage *a);  //   938
//			}
//		}
//	}
}

/* <487e03> ../cstrike/dlls/hostage/hostage_localnav.cpp:964 */
void CLocalNav::Reset(void)
{
	flNextCvarCheck = 0;
	flLastThinkTime = 0;
	tot_inqueue = 0;
	qptr = 0;
	nodeval = 0;
	tot_hostages = 0;
}

/* <487e14> ../cstrike/dlls/hostage/hostage_localnav.cpp:976 */
void CLocalNav::HostagePrethink(void)
{
	for (int iCount = 0; iCount < tot_hostages; iCount++)
	{
		if (hostages[ iCount ] != NULL)
			GetClassPtr((CHostage *)hostages[ iCount ]->pev)->PreThink();
	}
}
