#include "precompiled.h"

CGraph WorldGraph;

/* <fc409> ../cstrike/dlls/mpstubb.cpp:32 */
void CGraph::InitGraph(void)
{
	;
}

/* <fc436> ../cstrike/dlls/mpstubb.cpp:33 */
int CGraph::FLoadGraph(char *szMapName)
{
	return 0;
}

/* <fc46c> ../cstrike/dlls/mpstubb.cpp:34 */
int CGraph::AllocNodes(void)
{
	return 0;
}

/* <fc494> ../cstrike/dlls/mpstubb.cpp:35 */
int CGraph::CheckNODFile(char *szMapName)
{
	return 0;
}

/* <fc4ca> ../cstrike/dlls/mpstubb.cpp:36 */
int CGraph::FSetGraphPointers(void)
{
	return 0;
}

/* <fc4f2> ../cstrike/dlls/mpstubb.cpp:37 */
void CGraph::ShowNodeConnections(int iNode)
{
	;
}

/* <fc528> ../cstrike/dlls/mpstubb.cpp:38 */
int CGraph::FindNearestNode(const Vector &vecOrigin, int afNodeTypes)
{
	return 0;
}

/* <fc528> ../cstrike/dlls/mpstubb.cpp:38 */
int CGraph::FindNearestNode(const Vector &vecOrigin, CBaseEntity *pEntity)
{
	return 0;
}

/* <fc023> ../cstrike/dlls/mpstubb.cpp:45 */
float CBaseMonster::__MAKE_VHOOK(ChangeYaw)(int speed)
{
	return 0.0f;
}

/* <fc571> ../cstrike/dlls/mpstubb.cpp:46 */
void CBaseMonster::MakeIdealYaw(Vector vecTarget)
{
	;
}

/* <fc5a6> ../cstrike/dlls/mpstubb.cpp:49 */
NOBODY void CBaseMonster::CorpseFallThink(void)
{
	if (pev->flags & FL_ONGROUND)
	{
		SetThink(NULL);
		SetSequenceBox();
		UTIL_SetOrigin(pev, pev->origin);
	}
	else
		pev->nextthink = gpGlobals->time + 0.1;
}

/* <fc2a1> ../cstrike/dlls/mpstubb.cpp:62 */
void CBaseMonster::__MAKE_VHOOK(MonsterInitDead)(void)
{
	InitBoneControllers();

	pev->solid = SOLID_BBOX;
	pev->movetype = MOVETYPE_TOSS;

	pev->frame = 0;
	ResetSequenceInfo();
	pev->framerate = 0;

	pev->max_health = pev->health;
	pev->deadflag = DEAD_DEAD;

	UTIL_SetSize(pev, g_vecZero, g_vecZero);
	UTIL_SetOrigin(pev, pev->origin);

	BecomeDead();
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.5;
}

/* <fc057> ../cstrike/dlls/mpstubb.cpp:89 */
BOOL CBaseMonster::__MAKE_VHOOK(ShouldFadeOnDeath)(void)
{
	return FALSE;
}

/* <fc5cd> ../cstrike/dlls/mpstubb.cpp:94 */
BOOL CBaseMonster::FCheckAITrigger(void)
{
	return FALSE;
}

/* <fc26d> ../cstrike/dlls/mpstubb.cpp:99 */
void CBaseMonster::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	CBaseToggle::KeyValue(pkvd);
}

/* <fc07d> ../cstrike/dlls/mpstubb.cpp:104 */
NOBODY int CBaseMonster::__MAKE_VHOOK(IRelationship)(CBaseEntity *pTarget)
{
//	{
//		int const iEnemy;                                      //   106
//	}
}

/* <fc0e4> ../cstrike/dlls/mpstubb.cpp:140 */
NOBODY void CBaseMonster::__MAKE_VHOOK(Look)(int iDistance)
{
//	{
//		int iSighted;                                         //   142
//		class CBaseEntity *pSightEnt;                        //   149
//		class CBaseEntity *pList;                            //   151
//		Vector delta;                                   //   153
//		int count;                                            //   156
//		ClearConditions(CBaseMonster *const this,
//				int iConditions);  //   145
//		operator+(const Vector *const this,
//				const Vector &v);  //   156
//		operator-(const Vector *const this,
//				const Vector &v);  //   156
//		{
//			int i;                                        //   157
//		}
//		SetConditions(CBaseMonster *const this,
//				int iConditions);  //   207
//	}
}

/* <fc317> ../cstrike/dlls/mpstubb.cpp:220 */
NOBODY CBaseEntity *CBaseMonster::__MAKE_VHOOK(BestVisibleEnemy)(void)
{
//	{
//		class CBaseEntity *pReturn;                          //   222
//		class CBaseEntity *pNextEnt;                         //   223
//		int iNearest;                                         //   224
//		int iDist;                                            //   225
//		int iBestRelationship;                                //   226
//		operator-(const Vector *const this,
//				const Vector &v);  //   243
//		Length(const Vector *const this);  //   243
//		operator-(const Vector *const this,
//				const Vector &v);  //   251
//		Length(const Vector *const this);  //   251
//	}
}
