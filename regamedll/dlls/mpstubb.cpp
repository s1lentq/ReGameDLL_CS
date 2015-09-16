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
NOXREF void CBaseMonster::CorpseFallThink(void)
{
	if (pev->flags & FL_ONGROUND)
	{
		SetThink(NULL);
		SetSequenceBox();

		// link into world.
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
int CBaseMonster::__MAKE_VHOOK(IRelationship)(CBaseEntity *pTarget)
{
	static int const iEnemy[14][14] =
	{
		//   NONE	MACH	 PLYR	 HPASS	 HMIL	 AMIL	 APASS	 AMONST	APREY	 APRED	 INSECT	PLRALY	PBWPN	ABWPN
		{ R_NO,		R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO	},	// NONE
		{ R_NO,		R_NO,	R_DL,	R_DL,	R_NO,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_NO,	R_DL,	R_DL,	R_DL	},	// MACHINE
		{ R_NO,		R_DL,	R_NO,	R_NO,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_NO,	R_NO,	R_DL,	R_DL	},	// PLAYER
		{ R_NO,		R_NO,	R_AL,	R_AL,	R_HT,	R_FR,	R_NO,	R_HT,	R_DL,	R_FR,	R_NO,	R_AL,	R_NO,	R_NO	},	// HUMANPASSIVE
		{ R_NO,		R_NO,	R_HT,	R_DL,	R_NO,	R_HT,	R_DL,	R_DL,	R_DL,	R_DL,	R_NO,	R_HT,	R_NO,	R_NO	},	// HUMANMILITAR
		{ R_NO,		R_DL,	R_HT,	R_DL,	R_HT,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_DL,	R_NO,	R_NO	},	// ALIENMILITAR
		{ R_NO,		R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO	},	// ALIENPASSIVE
		{ R_NO,		R_DL,	R_DL,	R_DL,	R_DL,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_NO,	R_DL,	R_NO,	R_NO	},	// ALIENMONSTER
		{ R_NO,		R_NO,	R_DL,	R_DL,	R_DL,	R_NO,	R_NO,	R_NO,	R_NO,	R_FR,	R_NO,	R_DL,	R_NO,	R_NO	},	// ALIENPREY
		{ R_NO,		R_NO,	R_DL,	R_DL,	R_DL,	R_NO,	R_NO,	R_NO,	R_HT,	R_DL,	R_NO,	R_DL,	R_NO,	R_NO	},	// ALIENPREDATO
		{ R_FR,		R_FR,	R_FR,	R_FR,	R_FR,	R_NO,	R_FR,	R_FR,	R_FR,	R_FR,	R_NO,	R_FR,	R_NO,	R_NO	},	// INSECT
		{ R_NO,		R_DL,	R_AL,	R_AL,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_NO,	R_NO,	R_NO,	R_NO	},	// PLAYERALLY
		{ R_NO,		R_NO,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_DL,	R_NO,	R_DL,	R_NO,	R_DL	},	// PBIOWEAPON
		{ R_NO,		R_NO,	R_DL,	R_DL,	R_DL,	R_AL,	R_NO,	R_DL,	R_DL,	R_NO,	R_NO,	R_DL,	R_DL,	R_NO	}	// ABIOWEAPON
	};

	return iEnemy[ Classify() ][ pTarget->Classify() ];
}

// Look - Base class monster function to find enemies or
// food by sight. iDistance is distance (in units) that the
// monster can see.
//
// Sets the sight bits of the m_afConditions mask to indicate
// which types of entities were sighted.
// Function also sets the Looker's m_pLink
// to the head of a link list that contains all visible ents.
// (linked via each ent's m_pLink field)

/* <fc0e4> ../cstrike/dlls/mpstubb.cpp:140 */
void CBaseMonster::__MAKE_VHOOK(Look)(int iDistance)
{
	int iSighted = 0;

	// DON'T let visibility information from last frame sit around!
	ClearConditions(bits_COND_SEE_HATE | bits_COND_SEE_DISLIKE | bits_COND_SEE_ENEMY | bits_COND_SEE_FEAR | bits_COND_SEE_NEMESIS | bits_COND_SEE_CLIENT);

	m_pLink = NULL;

	// the current visible entity that we're dealing with
	CBaseEntity *pSightEnt = NULL;
	CBaseEntity *pList[100];

	Vector delta = Vector(iDistance, iDistance, iDistance);

	// Find only monsters/clients in box, NOT limited to PVS
	int count = UTIL_EntitiesInBox(pList, ARRAYSIZE(pList), pev->origin - delta, pev->origin + delta, (FL_CLIENT | FL_MONSTER));
	for (int i = 0; i < count; i++)
	{
		pSightEnt = pList[i];
		if (pSightEnt != this && pSightEnt->pev->health > 0)
		{
			// the looker will want to consider this entity
			// don't check anything else about an entity that can't be seen, or an entity that you don't care about.
			if (IRelationship(pSightEnt) != R_NO && FInViewCone(pSightEnt) && !(pSightEnt->pev->flags & FL_NOTARGET) && FVisible(pSightEnt))
			{
				if (pSightEnt->IsPlayer())
				{
					// if we see a client, remember that (mostly for scripted AI)
					iSighted |= bits_COND_SEE_CLIENT;
				}

				pSightEnt->m_pLink = m_pLink;
				m_pLink = pSightEnt;

				if (pSightEnt == m_hEnemy)
				{
					// we know this ent is visible, so if it also happens to be our enemy, store that now.
					iSighted |= bits_COND_SEE_ENEMY;
				}

				// don't add the Enemy's relationship to the conditions. We only want to worry about conditions when
				// we see monsters other than the Enemy.
				switch (IRelationship (pSightEnt))
				{
				case R_NM:
					iSighted |= bits_COND_SEE_NEMESIS;
					break;
				case R_HT:
					iSighted |= bits_COND_SEE_HATE;
					break;
				case R_DL:
					iSighted |= bits_COND_SEE_DISLIKE;
					break;
				case R_FR:
					iSighted |= bits_COND_SEE_FEAR;
					break;
				case R_AL:
					break;
				default:
					ALERT(at_aiconsole, "%s can't assess %s\n", STRING(pev->classname), STRING(pSightEnt->pev->classname));
					break;
				}
			}
		}
	}

	SetConditions(iSighted);
}

// BestVisibleEnemy - this functions searches the link
// list whose head is the caller's m_pLink field, and returns
// a pointer to the enemy entity in that list that is nearest the
// caller.
//
// !!!UNDONE - currently, this only returns the closest enemy.
// we'll want to consider distance, relationship, attack types, back turned, etc.

/* <fc317> ../cstrike/dlls/mpstubb.cpp:220 */
CBaseEntity *CBaseMonster::__MAKE_VHOOK(BestVisibleEnemy)(void)
{
	CBaseEntity *pReturn;
	CBaseEntity *pNextEnt;
	int iNearest;
	int iDist;
	int iBestRelationship;

	// so first visible entity will become the closest.
	iNearest = 8192;
	pNextEnt = m_pLink;
	pReturn = NULL;
	iBestRelationship = R_NO;

	while (pNextEnt != NULL)
	{
		if (pNextEnt->IsAlive())
		{
			if (IRelationship(pNextEnt) > iBestRelationship)
			{
				// this entity is disliked MORE than the entity that we
				// currently think is the best visible enemy. No need to do
				// a distance check, just get mad at this one for now.
				iBestRelationship = IRelationship(pNextEnt);
				iNearest = (pNextEnt->pev->origin - pev->origin).Length();
				pReturn = pNextEnt;
			}
			else if (IRelationship(pNextEnt) == iBestRelationship)
			{
				// this entity is disliked just as much as the entity that
				// we currently think is the best visible enemy, so we only
				// get mad at it if it is closer.
				iDist = (pNextEnt->pev->origin - pev->origin).Length();

				if (iDist <= iNearest)
				{
					iNearest = iDist;
					iBestRelationship = IRelationship(pNextEnt);
					pReturn = pNextEnt;
				}
			}
		}

		pNextEnt = pNextEnt->m_pLink;
	}

	return pReturn;
}
