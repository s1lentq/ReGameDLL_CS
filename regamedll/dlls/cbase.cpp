#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

static DLL_FUNCTIONS gFunctionTable =
{
	GameDLLInit,
	DispatchSpawn,
	DispatchThink,
	DispatchUse,
	DispatchTouch,
	DispatchBlocked,
	DispatchKeyValue,
	DispatchSave,
	DispatchRestore,
	DispatchObjectCollsionBox,
	SaveWriteFields,
	SaveReadFields,
	SaveGlobalState,
	RestoreGlobalState,
	ResetGlobalState,
	ClientConnect,
	ClientDisconnect,
	ClientKill,
	ClientPutInServer,
	ClientCommand,
	ClientUserInfoChanged,
	ServerActivate,
	ServerDeactivate,
	PlayerPreThink,
	PlayerPostThink,
	StartFrame,
	ParmsNewLevel,
	ParmsChangeLevel,
	GetGameDescription,
	PlayerCustomization,
	SpectatorConnect,
	SpectatorDisconnect,
	SpectatorThink,
	Sys_Error,
	PM_Move,
	PM_Init,
	PM_FindTextureType,
	SetupVisibility,
	UpdateClientData,
	AddToFullPack,
	CreateBaseline,
	RegisterEncoders,
	GetWeaponData,
	CmdStart,
	CmdEnd,
	ConnectionlessPacket,
	GetHullBounds,
	CreateInstancedBaselines,
	InconsistentFile,
	AllowLagCompensation
};

static NEW_DLL_FUNCTIONS gNewDLLFunctions
{
	OnFreeEntPrivateData,
	NULL,
	NULL
};

// Global Savedata for Delay
TYPEDESCRIPTION	CBaseEntity::m_SaveData[] =
{
	DEFINE_FIELD(CBaseEntity, m_pGoalEnt, FIELD_CLASSPTR),
	DEFINE_FIELD(CBaseEntity, m_pfnThink, FIELD_FUNCTION),	// UNDONE: Build table of these!!!
	DEFINE_FIELD(CBaseEntity, m_pfnTouch, FIELD_FUNCTION),
	DEFINE_FIELD(CBaseEntity, m_pfnUse, FIELD_FUNCTION),
	DEFINE_FIELD(CBaseEntity, m_pfnBlocked, FIELD_FUNCTION),
};

CMemoryPool hashItemMemPool(sizeof(hash_item_t), 64);
BOOL gTouchDisabled = FALSE;

#else // HOOK_GAMEDLL

DLL_FUNCTIONS gFunctionTable;
NEW_DLL_FUNCTIONS gNewDLLFunctions;
TYPEDESCRIPTION	IMPLEMENT_ARRAY_CLASS(CBaseEntity, m_SaveData)[5];

CMemoryPool hashItemMemPool;
BOOL gTouchDisabled;

#endif // HOOK_GAMEDLL

/* <30850> ../cstrike/dlls/cbase.cpp:117 */
int CaseInsensitiveHash(const char *string, int iBounds)
{
	unsigned int hash = 0;

	if (!*string)
		return 0;

	while (*string)
	{
		if (*string < 'A' || *string > 'Z')
			hash = *string + 2 * hash;
		else
			hash = *string + 2 * hash + ' ';

		string++;
	}

	return (hash % iBounds);
}

/* <30d81> ../cstrike/dlls/cbase.cpp:136 */
void EmptyEntityHashTable(void)
{
	int i;
	hash_item_t *item, *temp, *free;

	for (i = 0; i < stringsHashTable.Count(); i++)
	{
		item = &stringsHashTable[i];
		temp = item->next;

		item->pev = NULL;
		item->pevIndex = 0;
		item->lastHash = 0;
		item->next = NULL;

		while (temp)
		{
			free = temp;
			temp = temp->next;
			hashItemMemPool.Free(free);
		}
	}
}

/* <2f053> ../cstrike/dlls/cbase.cpp:156 */
void AddEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType)
{
	int count;
	hash_item_t *item, *next, *temp, *newp;
	int hash, pevIndex;
	entvars_t *pevtemp;

	if (fieldType != CLASSNAME)
		return;

	if (FStringNull(pev->classname))
		return;

	count = stringsHashTable.Count();
	hash = CaseInsensitiveHash(value, count);
	pevIndex = ENTINDEX(ENT(pev));
	item = &stringsHashTable[hash];

	while (item->pev)
	{
		if (!Q_strcmp(STRING(item->pev->classname), STRING(pev->classname)))
			break;

		hash = (hash + 1) % count;
		item = &stringsHashTable[hash];
	}
	if (item->pev)
	{
		next = item->next;
		while (next)
		{
			if (item->pev == pev || item->pevIndex >= pevIndex)
				break;

			item = next;
			next = next->next;
		}
		if (pevIndex < item->pevIndex)
		{
			pevtemp = item->pev;
			item->pev = pev;
			item->lastHash = NULL;
			item->pevIndex = pevIndex;

			pevIndex = ENTINDEX(ENT(pevtemp));
		}
		else
			pevtemp = pev;

		if (item->pev != pevtemp)
		{
			temp = item->next;
			newp = (hash_item_t *)hashItemMemPool.Alloc(sizeof(hash_item_t));

			item->next = newp;
			newp->pev = pevtemp;
			newp->lastHash = NULL;
			newp->pevIndex = pevIndex;

			if (next)
				newp->next = temp;
			else
				newp->next = NULL;
		}
	}
	else
	{
		item->pev = pev;
		item->lastHash = NULL;
		item->pevIndex = ENTINDEX(ENT(pev));
	}
}

/* <2f0c8> ../cstrike/dlls/cbase.cpp:255 */
void RemoveEntityHashValue(entvars_t *pev, const char *value, hash_types_e fieldType)
{
	int hash;
	hash_item_t *item;
	hash_item_t *last;
	int pevIndex;
	int count;

	count = stringsHashTable.Count();
	hash = CaseInsensitiveHash(value, count);
	pevIndex = ENTINDEX(ENT(pev));

	if (fieldType != CLASSNAME)
		return;

	hash = hash % count;
	item = &stringsHashTable[hash];

	while (item->pev)
	{
		if (!Q_strcmp(STRING(item->pev->classname), STRING(pev->classname)))
			break;

		hash = (hash + 1) % count;
		item = &stringsHashTable[hash];
	}
	if (item->pev)
	{
		last = item;
		while (item->next)
		{
			if (item->pev == pev)
				break;

			last = item;
			item = item->next;
		}
		if (item->pev == pev)
		{
			if (last == item)
			{
				if (item->next)
				{
					item->pev = item->next->pev;
					item->pevIndex = item->next->pevIndex;
					item->lastHash = NULL;
					item->next = item->next->next;
				}
				else
				{
					item->pev = NULL;
					item->lastHash = NULL;
					item->pevIndex = 0;
				}
			}
			else
			{
				if (stringsHashTable[hash].lastHash == item)
					stringsHashTable[hash].lastHash = NULL;

				last->next = item->next;
				hashItemMemPool.Free(item);
			}
		}
	}
}

/* <31125> ../cstrike/dlls/cbase.cpp:337 */
void printEntities(void)
{
	for (int i = 0; i < stringsHashTable.Count(); i++)
	{
		hash_item_t *item = &stringsHashTable[i];

		if (item->pev)
		{
			UTIL_LogPrintf("Print: %s %i %p\n", STRING(stringsHashTable[i].pev->classname), ENTINDEX(ENT(item->pev)), item->pev);
		}

		for (item = stringsHashTable[i].next; item; item = item->next)
		{
			UTIL_LogPrintf("Print: %s %i %p\n", STRING(item->pev->classname), ENTINDEX(ENT(item->pev)), item->pev);
		}
	}
}

/* <311e9> ../cstrike/dlls/cbase.cpp:354 */
edict_t *CREATE_NAMED_ENTITY(string_t iClass)
{
	edict_t *named = g_engfuncs.pfnCreateNamedEntity(iClass);
	if (named != NULL)
	{
		AddEntityHashValue(&named->v, STRING(iClass), CLASSNAME);
	}

	return named;
}

/* <31249> ../cstrike/dlls/cbase.cpp:366 */
void REMOVE_ENTITY(edict_t *e)
{
	if (e != NULL)
	{
		(*g_engfuncs.pfnRemoveEntity)(e);
	}
}

/* <30158> ../cstrike/dlls/cbase.cpp:375 */
void CONSOLE_ECHO_(char *pszMsg, ...)
{
	va_list argptr;
	static char szStr[1024];

	va_start(argptr, pszMsg);
	vsprintf(szStr, pszMsg, argptr);
	va_end(argptr);

	SERVER_PRINT(szStr);
}

/* <31273> ../cstrike/dlls/cbase.cpp:386 */
void loopPerformance(void)
{
	CPerformanceCounter loopCounter;
	loopCounter.InitializePerformanceCounter();

	double start, end;
	int i;

	start = loopCounter.GetCurTime();

	for (i = 0; i < 100; i++)
	{
		CBaseEntity *pSpot;
		for (pSpot = UTIL_FindEntityByString_Old(NULL, "classname", "info_player_start"); pSpot != NULL; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "info_player_start"))
			;

		for (pSpot = UTIL_FindEntityByString_Old(NULL, "classname", "info_player_deathmatch"); pSpot != NULL; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "info_player_deathmatch"))
			;

		for (pSpot = UTIL_FindEntityByString_Old(NULL, "classname", "player"); pSpot != NULL; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "player"))
			;

		for (pSpot = UTIL_FindEntityByString_Old(NULL, "classname", "bodyque"); pSpot != NULL; pSpot = UTIL_FindEntityByString_Old(pSpot, "classname", "bodyque"))
			;
	}

	end = loopCounter.GetCurTime();
	CONSOLE_ECHO(" Time in old search loop %.4f\n", (end - start) * 1000.0);

	// check time new search loop
	start = loopCounter.GetCurTime();

	for (i = 0; i < 100; i++)
	{
		CBaseEntity *pSpot;
		for (pSpot = UTIL_FindEntityByString(NULL, "classname", "info_player_start"); pSpot != NULL; pSpot = UTIL_FindEntityByString(pSpot, "classname", "info_player_start"))
			;

		for (pSpot = UTIL_FindEntityByString(NULL, "classname", "info_player_deathmatch"); pSpot != NULL; pSpot = UTIL_FindEntityByString(pSpot, "classname", "info_player_deathmatch"))
			;

		for (pSpot = UTIL_FindEntityByString(NULL, "classname", "player"); pSpot != NULL; pSpot = UTIL_FindEntityByString(pSpot, "classname", "player"))
			;

		for (pSpot = UTIL_FindEntityByString(NULL, "classname", "bodyque"); pSpot != NULL; pSpot = UTIL_FindEntityByString(pSpot, "classname", "bodyque"))
			;
	}

	end = loopCounter.GetCurTime();
	CONSOLE_ECHO(" Time in new search loop %.4f\n", (end - start) * 1000.0);
}

/* <313df> ../cstrike/dlls/cbase.cpp:451 */
C_DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion)
{
	if (!pFunctionTable || interfaceVersion != INTERFACE_VERSION)
		return 0;

	Q_memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	stringsHashTable.AddMultipleToTail(2048);
	for (int i = 0; i < stringsHashTable.Count(); i++)
	{
		stringsHashTable[i].next = NULL;
	}

	EmptyEntityHashTable();
	return 1;
}

/* <3161a> ../cstrike/dlls/cbase.cpp:471 */
NOXREF int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion)
{
	if (!pFunctionTable || *interfaceVersion != INTERFACE_VERSION)
	{
		*interfaceVersion = INTERFACE_VERSION;
		return 0;
	}

	Q_memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	return 1;
}

/* <3165b> ../cstrike/dlls/cbase.cpp:485 */
C_DLLEXPORT int GetNewDLLFunctions(NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion)
{
	if (!pFunctionTable || *interfaceVersion != NEW_DLL_FUNCTIONS_VERSION)
	{
		*interfaceVersion = NEW_DLL_FUNCTIONS_VERSION;
		return 0;
	}

	Q_memcpy(pFunctionTable, &gNewDLLFunctions, sizeof(NEW_DLL_FUNCTIONS));
	return 1;
}

/* <30ab0> ../cstrike/dlls/cbase.cpp:498 */
int DispatchSpawn(edict_t *pent)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pent);

	if (pEntity != NULL)
	{
		// Initialize these or entities who don't link to the world won't have anything in here
		pEntity->pev->absmin = pEntity->pev->origin - Vector(1, 1, 1);
		pEntity->pev->absmax = pEntity->pev->origin + Vector(1, 1, 1);
		pEntity->Spawn();

		// Try to get the pointer again, in case the spawn function deleted the entity.
		// UNDONE: Spawn() should really return a code to ask that the entity be deleted, but
		// that would touch too much code for me to do that right now.
		pEntity = (CBaseEntity *)GET_PRIVATE(pent);

		if (pEntity != NULL)
		{
			if (g_pGameRules && !g_pGameRules->IsAllowedToSpawn(pEntity))
			{
				// return that this entity should be deleted
				return -1;
			}

			if (pEntity->pev->flags & FL_KILLME)
			{
				return -1;
			}
		}

		// Handle global stuff here
		if (pEntity != NULL && pEntity->pev->globalname)
		{
			const globalentity_t *pGlobal = gGlobalState.EntityFromTable(pEntity->pev->globalname);

			if (pGlobal)
			{
				// Already dead? delete
				if (pGlobal->state == GLOBAL_DEAD)
					return -1;

				else if (!FStrEq(STRING(gpGlobals->mapname), pGlobal->levelName))
				{
					// Hasn't been moved to this level yet, wait but stay alive
					// In this level & not dead, continue on as normal
					pEntity->MakeDormant();
				}
			}
			else
			{
				// Spawned entities default to 'On'
				gGlobalState.EntityAdd(pEntity->pev->globalname, gpGlobals->mapname, GLOBAL_ON);
			}
		}

	}

	return 0;
}

/* <2e8a0> ../cstrike/dlls/cbase.cpp:549 */
void DispatchKeyValue(edict_t *pentKeyvalue, KeyValueData *pkvd)
{
	if (!pkvd || !pentKeyvalue)
		return;

	EntvarsKeyvalue(VARS(pentKeyvalue), pkvd);

	// If the key was an entity variable, or there's no class set yet, don't look for the object, it may
	// not exist yet.
	if (pkvd->fHandled || !pkvd->szClassName)
		return;

	// Get the actualy entity object
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pentKeyvalue);

	if (!pEntity)
		return;

	pEntity->KeyValue(pkvd);
}

// HACKHACK -- this is a hack to keep the node graph entity from "touching" things (like triggers)
// while it builds the graph

/* <2e7db> ../cstrike/dlls/cbase.cpp:574 */
void DispatchTouch(edict_t *pentTouched, edict_t *pentOther)
{
	if (gTouchDisabled)
		return;

	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pentTouched);
	CBaseEntity *pOther = (CBaseEntity *)GET_PRIVATE(pentOther);

	if (pEntity && pOther && !((pEntity->pev->flags | pOther->pev->flags) & FL_KILLME))
		pEntity->Touch(pOther);
}

/* <2fa9b> ../cstrike/dlls/cbase.cpp:587 */
void DispatchUse(edict_t *pentUsed, edict_t *pentOther)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pentUsed);
	CBaseEntity *pOther = (CBaseEntity *)GET_PRIVATE(pentOther);

	if (pEntity && !(pEntity->pev->flags & FL_KILLME))
	{
		pEntity->Use(pOther, pOther, USE_TOGGLE, 0);
	}
}

/* <2fb2f> ../cstrike/dlls/cbase.cpp:596 */
void DispatchThink(edict_t *pent)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pent);

	if (pEntity != NULL)
	{
		if (pEntity->pev->flags & FL_DORMANT)
		{
			ALERT(at_error, "Dormant entity %s is thinking!!\n", STRING(pEntity->pev->classname));
		}

		pEntity->Think();
	}
}

/* <2fb89> ../cstrike/dlls/cbase.cpp:612 */
void DispatchBlocked(edict_t *pentBlocked, edict_t *pentOther)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pentBlocked);
	CBaseEntity *pOther = (CBaseEntity *)GET_PRIVATE(pentOther);

	if (pEntity != NULL)
	{
		pEntity->Blocked(pOther);
	}
}

/* <2ff56> ../cstrike/dlls/cbase.cpp:621 */
void DispatchSave(edict_t *pent, SAVERESTOREDATA *pSaveData)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pent);

	if (pEntity != NULL && pSaveData != NULL)
	{
		ENTITYTABLE *pTable = &pSaveData->pTable[ pSaveData->currentIndex ];

		if (pTable->pent != pent)
		{
			ALERT(at_error, "ENTITY TABLE OR INDEX IS WRONG!!!!\n");
		}

		if (pEntity->ObjectCaps() & FCAP_DONT_SAVE)
			return;

		// These don't use ltime & nextthink as times really, but we'll fudge around it.
		if (pEntity->pev->movetype == MOVETYPE_PUSH)
		{
			float_precision delta = pEntity->pev->nextthink - pEntity->pev->ltime;
			pEntity->pev->ltime = gpGlobals->time;
			pEntity->pev->nextthink = pEntity->pev->ltime + delta;
		}

		// Remember entity position for file I/O
		pTable->location = pSaveData->size;

		// Remember entity class for respawn
		pTable->classname = pEntity->pev->classname;

		CSave saveHelper(pSaveData);
		pEntity->Save(saveHelper);

		// Size of entity block is data size written to block
		pTable->size = pSaveData->size - pTable->location;
	}
}

// Find the matching global entity.  Spit out an error if the designer made entities of
// different classes with the same global name

/* <31697> ../cstrike/dlls/cbase.cpp:656 */
CBaseEntity *FindGlobalEntity(string_t classname, string_t globalname)
{
	edict_t *pent = FIND_ENTITY_BY_STRING(NULL, "globalname", STRING(globalname));
	CBaseEntity *pReturn = CBaseEntity::Instance(pent);

	if (pReturn != NULL)
	{
		if (!FClassnameIs(pReturn->pev, STRING(classname)))
		{
			ALERT(at_console, "Global entity found %s, wrong class %s\n", STRING(globalname), STRING(pReturn->pev->classname));
			pReturn = NULL;
		}
	}

	return pReturn;
}

/* <3179c> ../cstrike/dlls/cbase.cpp:673 */
int DispatchRestore(edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pent);

	if (pEntity && pSaveData)
	{
		entvars_t tmpVars;
		Vector oldOffset;
		CRestore restoreHelper(pSaveData);

		if (globalEntity)
		{
			CRestore tmpRestore(pSaveData);
			tmpRestore.PrecacheMode(0);
			tmpRestore.ReadEntVars("ENTVARS", &tmpVars);

			// HACKHACK - reset the save pointers, we're going to restore for real this time
			pSaveData->size = pSaveData->pTable[pSaveData->currentIndex].location;
			pSaveData->pCurrentData = pSaveData->pBaseData + pSaveData->size;

			const globalentity_t *pGlobal = gGlobalState.EntityFromTable(tmpVars.globalname);

			// Don't overlay any instance of the global that isn't the latest
			// pSaveData->szCurrentMapName is the level this entity is coming from
			// pGlobla->levelName is the last level the global entity was active in.
			// If they aren't the same, then this global update is out of date.
			if (!FStrEq(pSaveData->szCurrentMapName, pGlobal->levelName))
			{
				return 0;
			}

			// Compute the new global offset
			oldOffset = pSaveData->vecLandmarkOffset;
			CBaseEntity *pNewEntity = FindGlobalEntity(tmpVars.classname, tmpVars.globalname);

			if (pNewEntity != NULL)
			{
				// Tell the restore code we're overlaying a global entity from another level
				// Don't overwrite global fields
				restoreHelper.SetGlobalMode(1);

				pSaveData->vecLandmarkOffset = (pSaveData->vecLandmarkOffset - pNewEntity->pev->mins) + tmpVars.mins;

				// we're going to restore this data OVER the old entity
				pEntity = pNewEntity;
				pent = ENT(pEntity->pev);

				// Update the global table to say that the global definition of this entity should come from this level
				gGlobalState.EntityUpdate(pEntity->pev->globalname, gpGlobals->mapname);
			}
			else
			{
				// This entity will be freed automatically by the engine.  If we don't do a restore on a matching entity (below)
				// or call EntityUpdate() to move it to this level, we haven't changed global state at all.

				return 0;
			}
		}

		if (pEntity->ObjectCaps() & FCAP_MUST_SPAWN)
		{
			pEntity->Restore(restoreHelper);
			pEntity->Spawn();
		}
		else
		{
			pEntity->Restore(restoreHelper);
			pEntity->Precache();
		}

		// Again, could be deleted, get the pointer again.
		pEntity = (CBaseEntity *)GET_PRIVATE(pent);

		// Is this an overriding global entity (coming over the transition), or one restoring in a level
		if (globalEntity)
		{
			pSaveData->vecLandmarkOffset = oldOffset;

			if (pEntity != NULL)
			{
				UTIL_SetOrigin(pEntity->pev, pEntity->pev->origin);
				pEntity->OverrideReset();
			}
		}
		else if (pEntity != NULL && pEntity->pev->globalname)
		{
			const globalentity_t *pGlobal = gGlobalState.EntityFromTable(pEntity->pev->globalname);

			if (pGlobal != NULL)
			{
				// Already dead? delete
				if (pGlobal->state == GLOBAL_DEAD)
					return -1;

				else if (!FStrEq(STRING(gpGlobals->mapname), pGlobal->levelName))
				{
					// Hasn't been moved to this level yet, wait but stay alive
					pEntity->MakeDormant();
				}
				// In this level & not dead, continue on as normal
			}
			else
			{
				ALERT(at_error, "Global Entity %s (%s) not in table!!!\n", STRING(pEntity->pev->globalname), STRING(pEntity->pev->classname));

				// Spawned entities default to 'On'
				gGlobalState.EntityAdd(pEntity->pev->globalname, gpGlobals->mapname, GLOBAL_ON);
			}
		}
	}

	return 0;
}

/* <2fdcd> ../cstrike/dlls/cbase.cpp:776 */
void DispatchObjectCollsionBox(edict_t *pent)
{
	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pent);

	if (pEntity != NULL)
	{
		pEntity->SetObjectCollisionBox();
	}
	else
		SetObjectCollisionBox(&pent->v);

}

/* <2fe94> ../cstrike/dlls/cbase.cpp:788 */
void SaveWriteFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	CSave saveHelper(pSaveData);
	saveHelper.WriteFields(pname, pBaseData, pFields, fieldCount);
}

/* <30047> ../cstrike/dlls/cbase.cpp:795 */
void SaveReadFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	CRestore restoreHelper(pSaveData);
	restoreHelper.ReadFields(pname, pBaseData, pFields, fieldCount);
}

/* <31a74> ../cstrike/dlls/cbase.cpp:802 */
edict_t *EHANDLE::Get(void)
{
	if (!m_pent || m_pent->serialnumber != m_serialnumber)
		return NULL;

	return m_pent;
}

/* <31a95> ../cstrike/dlls/cbase.cpp:814 */
edict_t *EHANDLE::Set(edict_t *pent)
{
	m_pent = pent;
	if (pent)
		m_serialnumber = pent->serialnumber;

	return pent;
}

/* <31ace> ../cstrike/dlls/cbase.cpp:823 */
EHANDLE::operator CBaseEntity *(void)
{
	return (CBaseEntity *)GET_PRIVATE(Get());
}

/* <31b30> ../cstrike/dlls/cbase.cpp:829 */
CBaseEntity *EHANDLE::operator=(CBaseEntity *pEntity)
{
	if (pEntity != NULL)
	{
		m_pent = ENT(pEntity->pev);
		if (m_pent)
			m_serialnumber = m_pent->serialnumber;
	}
	else
	{
		m_pent = NULL;
		m_serialnumber = 0;
	}

	return pEntity;
}

/* <31b69> ../cstrike/dlls/cbase.cpp:845 */
EHANDLE::operator int(void)
{
	return Get() != NULL;
}

/* <31bac> ../cstrike/dlls/cbase.cpp:850 */
CBaseEntity *EHANDLE::operator->(void)
{
	return (CBaseEntity *)GET_PRIVATE(Get());
}

/* <301be> ../cstrike/dlls/cbase.cpp:857 */
int CBaseEntity::__MAKE_VHOOK(TakeHealth)(float flHealth, int bitsDamageType)
{
	if (pev->takedamage == DAMAGE_NO)
		return 0;

	if (pev->health >= pev->max_health)
		return 0;

	pev->health += flHealth;

	if (pev->health > pev->max_health)
	{
		pev->health = pev->max_health;
	}

	return 1;
}

/* <305af> ../cstrike/dlls/cbase.cpp:876 */
int CBaseEntity::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	Vector vecTemp;

	if (pev->takedamage == DAMAGE_NO)
		return 0;

	// UNDONE: some entity types may be immune or resistant to some bitsDamageType
	// if Attacker == Inflictor, the attack was a melee or other instant-hit attack.
	// (that is, no actual entity projectile was involved in the attack so use the shooter's origin).
	if (pevAttacker == pevInflictor)
	{
		vecTemp = pevInflictor->origin - (VecBModelOrigin(pev));
	}
	else
	{
		// an actual missile was involved.
		vecTemp = pevInflictor->origin - (VecBModelOrigin(pev));
	}

	// this global is still used for glass and other non-monster killables, along with decals.
	g_vecAttackDir = vecTemp.Normalize();

	// save damage based on the target's armor level
	// figure momentum add (don't let hurt brushes or other triggers move player)
	if ((!FNullEnt(pevInflictor)) && (pev->movetype == MOVETYPE_WALK || pev->movetype == MOVETYPE_STEP) && (pevAttacker->solid != SOLID_TRIGGER))
	{
		Vector vecDir = pev->origin - (pevInflictor->absmin + pevInflictor->absmax) * 0.5;
		vecDir = vecDir.Normalize();

		float_precision flForce = flDamage * ((32 * 32 * 72.0) / (pev->size.x * pev->size.y * pev->size.z)) * 5;

		if (flForce > 1000.0)
			flForce = 1000.0;

		pev->velocity = pev->velocity + vecDir * flForce;
	}

	// do the damage
	pev->health -= flDamage;
	if (pev->health <= 0)
	{
		Killed(pevAttacker, GIB_NORMAL);
		return 0;
	}

	return 1;
}

/* <2fe50> ../cstrike/dlls/cbase.cpp:927 */
void CBaseEntity::__MAKE_VHOOK(Killed)(entvars_t *pevAttacker, int iGib)
{
	pev->takedamage = DAMAGE_NO;
	pev->deadflag = DEAD_DEAD;
	UTIL_Remove(this);
}

/* <2fc1c> ../cstrike/dlls/cbase.cpp:935 */
CBaseEntity *CBaseEntity::__MAKE_VHOOK(GetNextTarget)(void)
{
	if (FStringNull(pev->target))
		return NULL;

	edict_t *pTarget = FIND_ENTITY_BY_TARGETNAME(NULL, STRING(pev->target));

	if (FNullEnt(pTarget))
	{
		return NULL;
	}

	return Instance(pTarget);
}

/* <302a6> ../cstrike/dlls/cbase.cpp:958 */
int CBaseEntity::__MAKE_VHOOK(Save)(CSave &save)
{
	if (save.WriteEntVars("ENTVARS", pev))
	{
		return save.WriteFields("BASE", this, IMPLEMENT_ARRAY(m_SaveData), ARRAYSIZE(IMPLEMENT_ARRAY(m_SaveData)));
	}

	return 0;
}

/* <30440> ../cstrike/dlls/cbase.cpp:966 */
int CBaseEntity::__MAKE_VHOOK(Restore)(CRestore &restore)
{
	int status;

	status = restore.ReadEntVars("ENTVARS", pev);

	if (status)
	{
		status = restore.ReadFields("BASE", this, IMPLEMENT_ARRAY(m_SaveData), ARRAYSIZE(IMPLEMENT_ARRAY(m_SaveData)));
	}

	if (pev->modelindex != 0 && !FStringNull(pev->model))
	{
		Vector mins, maxs;

		// Set model is about to destroy these
		mins = pev->mins;
		maxs = pev->maxs;

		PRECACHE_MODEL((char *)STRING(pev->model));
		SET_MODEL(ENT(pev), STRING(pev->model));

		// Reset them
		UTIL_SetSize(pev, mins, maxs);
	}

	return status;
}

/* <2fcf6> ../cstrike/dlls/cbase.cpp:991 */
void SetObjectCollisionBox(entvars_t *pev)
{
	if ((pev->solid == SOLID_BSP) && (pev->angles.x || pev->angles.y || pev->angles.z))
	{
		// expand for rotation
		float_precision max, v;
		int i;

		max = 0;
		for (i = 0; i < 3; i++)
		{
			v = fabs((float_precision)((float *)pev->mins)[i]);
			if (v > max)
			{
				max = v;
			}

			v = fabs((float_precision)((float *)pev->maxs)[i]);
			if (v > max)
			{
				max = v;
			}
		}
		for (i = 0; i < 3; i++)
		{
			((float *)pev->absmin)[i] = ((float *)pev->origin)[i] - max;
			((float *)pev->absmax)[i] = ((float *)pev->origin)[i] + max;
		}
	}
	else
	{
		pev->absmin = pev->origin + pev->mins;
		pev->absmax = pev->origin + pev->maxs;
	}

	pev->absmin.x -= 1;
	pev->absmin.y -= 1;
	pev->absmin.z -= 1;

	pev->absmax.x += 1;
	pev->absmax.y += 1;
	pev->absmax.z += 1;
}

/* <2fe2a> ../cstrike/dlls/cbase.cpp:1030 */
void CBaseEntity::__MAKE_VHOOK(SetObjectCollisionBox)(void)
{
	::SetObjectCollisionBox(pev);
}

/* <31c0e> ../cstrike/dlls/cbase.cpp:1036 */
int CBaseEntity::Intersects(CBaseEntity *pOther)
{
	if (pOther->pev->absmin.x > pev->absmax.x
		|| pOther->pev->absmin.y > pev->absmax.y
		|| pOther->pev->absmin.z > pev->absmax.z
		|| pOther->pev->absmax.x < pev->absmin.x
		|| pOther->pev->absmax.y < pev->absmin.y
		|| pOther->pev->absmax.z < pev->absmin.z)
		 return 0;
	return 1;
}

/* <31c43> ../cstrike/dlls/cbase.cpp:1048 */
void CBaseEntity::MakeDormant(void)
{
	pev->flags |= FL_DORMANT;

	// Don't touch
	pev->solid = SOLID_NOT;

	// Don't move
	pev->movetype = MOVETYPE_NONE;

	// Don't draw
	pev->effects |= EF_NODRAW;

	// Don't think
	pev->nextthink = 0;

	// Relink
	UTIL_SetOrigin(pev, pev->origin);
}

/* <31c66> ../cstrike/dlls/cbase.cpp:1064 */
int CBaseEntity::IsDormant(void)
{
	return (pev->flags & FL_DORMANT) == FL_DORMANT;
}

/* <30221> ../cstrike/dlls/cbase.cpp:1069 */
BOOL CBaseEntity::__MAKE_VHOOK(IsInWorld)(void)
{
	// position
	if (pev->origin.x >= 4096.0 || pev->origin.y >= 4096.0 || pev->origin.z >= 4096.0)
	{
		return FALSE;
	}
	if (pev->origin.x <= -4096.0 || pev->origin.y <= -4096.0 || pev->origin.z <= -4096.0)
	{
		return FALSE;
	}

	// speed
	if (pev->velocity.x >= 2000.0 || pev->velocity.y >= 2000.0 || pev->velocity.z >= 2000.0)
	{
		return FALSE;
	}
	if (pev->velocity.x <= -2000.0 || pev->velocity.y <= -2000.0 || pev->velocity.z <= -2000.0)
	{
		return FALSE;
	}

	return TRUE;
}

/* <31c8c> ../cstrike/dlls/cbase.cpp:1089 */
int CBaseEntity::ShouldToggle(USE_TYPE useType, BOOL currentState)
{
	if (useType != USE_TOGGLE && useType != USE_SET)
	{
		if ((currentState && useType == USE_ON) || (!currentState && useType == USE_OFF))
			return 0;
	}

	return 1;
}

/* <30258> ../cstrike/dlls/cbase.cpp:1100 */
int CBaseEntity::__MAKE_VHOOK(DamageDecal)(int bitsDamageType)
{
	if (pev->rendermode == kRenderTransAlpha)
		return -1;

	if (pev->rendermode != kRenderNormal)
		return DECAL_BPROOF1;

	return DECAL_GUNSHOT1 + RANDOM_LONG(0, 4);
}

// NOTE: szName must be a pointer to constant memory, e.g. "monster_class" because the entity
// will keep a pointer to it after this call.

/* <31cd1> ../cstrike/dlls/cbase.cpp:1115 */
CBaseEntity *CBaseEntity::Create(char *szName, const Vector &vecOrigin, const Vector &vecAngles, edict_t *pentOwner)
{
	edict_t	*pent;
	CBaseEntity *pEntity;

	pent = CREATE_NAMED_ENTITY(MAKE_STRING(szName));
	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in Create!\n");
		return NULL;
	}

	pEntity = Instance(pent);

	pEntity->pev->owner = pentOwner;
	pEntity->pev->origin = vecOrigin;
	pEntity->pev->angles = vecAngles;

	DispatchSpawn(pEntity->edict());

	return pEntity;
}

/* <30885> ../cstrike/dlls/cbase.cpp:1134 */
void OnFreeEntPrivateData(edict_t *pEnt)
{
	CBaseEntity *pEntity = CBaseEntity::Instance(pEnt);
	if (!pEntity)
		return;

	pEntity->UpdateOnRemove();
	RemoveEntityHashValue(pEntity->pev, STRING(pEntity->pev->classname), CLASSNAME);
}

#ifdef HOOK_GAMEDLL

int CBaseEntity::Save(CSave &save)
{
	return Save_(save);
}

int CBaseEntity::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBaseEntity::SetObjectCollisionBox(void)
{
	SetObjectCollisionBox_();
}

void CBaseEntity::TraceAttack(entvars_t *pevAttacker,float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType)
{
	TraceAttack_(pevAttacker,flDamage,vecDir,ptr,bitsDamageType);
}

int CBaseEntity::TakeDamage(entvars_t *pevInflictor,entvars_t *pevAttacker,float flDamage,int bitsDamageType)
{
	return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType);
}

int CBaseEntity::TakeHealth(float flHealth,int bitsDamageType)
{
	return TakeHealth_(flHealth, bitsDamageType);
}

void CBaseEntity::Killed(entvars_t *pevAttacker,int iGib)
{
	Killed_(pevAttacker,iGib);
}

void CBaseEntity::TraceBleed(float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType)
{
	TraceBleed_(flDamage,vecDir,ptr,bitsDamageType);
}

int CBaseEntity::DamageDecal(int bitsDamageType)
{
	return DamageDecal_(bitsDamageType);
}

BOOL CBaseEntity::IsInWorld(void)
{
	return IsInWorld_();
}

CBaseEntity *CBaseEntity::GetNextTarget(void)
{
	return GetNextTarget_();
}

BOOL CBaseEntity::FVisible(CBaseEntity *pEntity)
{
	return FVisible_(pEntity);
}

BOOL CBaseEntity::FVisible(const Vector &vecOrigin)
{
	return FVisible_(vecOrigin);
}

#endif // HOOK_GAMEDLL
