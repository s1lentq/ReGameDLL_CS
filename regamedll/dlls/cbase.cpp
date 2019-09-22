#include "precompiled.h"

DLL_FUNCTIONS gFunctionTable =
{
	&GameDLLInit,
	&DispatchSpawn,
	&DispatchThink,
	&DispatchUse,
	&DispatchTouch,
	&DispatchBlocked,
	&DispatchKeyValue,
	&DispatchSave,
	&DispatchRestore,
	&DispatchObjectCollsionBox,
	&SaveWriteFields,
	&SaveReadFields,
	&SaveGlobalState,
	&RestoreGlobalState,
	&ResetGlobalState,
	&ClientConnect,
	&ClientDisconnect,
	&ClientKill,
	&ClientPutInServer,
	&ClientCommand_,
	&ClientUserInfoChanged,
	&ServerActivate,
	&ServerDeactivate,
	&PlayerPreThink,
	&PlayerPostThink,
	&StartFrame,
	&ParmsNewLevel,
	&ParmsChangeLevel,
	&GetGameDescription,
	&PlayerCustomization,
	&SpectatorConnect,
	&SpectatorDisconnect,
	&SpectatorThink,
	&SysEngine_Error,
	&PM_Move,
	&PM_Init,
	&PM_FindTextureType,
	&SetupVisibility,
	&UpdateClientData,
	&AddToFullPack,
	&CreateBaseline,
	&RegisterEncoders,
	&GetWeaponData,
	&CmdStart,
	&CmdEnd,
	&ConnectionlessPacket,
	&GetHullBounds,
	&CreateInstancedBaselines,
	&InconsistentFile,
	&AllowLagCompensation
};

NEW_DLL_FUNCTIONS gNewDLLFunctions =
{
	&OnFreeEntPrivateData,
	&OnGameShutdown,
	nullptr,
	nullptr,
	nullptr
};

CMemoryPool hashItemMemPool(sizeof(hash_item_t), 64);

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

void EmptyEntityHashTable()
{
	int i;
	hash_item_t *item, *temp, *free;

	for (i = 0; i < stringsHashTable.Count(); i++)
	{
		item = &stringsHashTable[i];
		temp = item->next;

		item->pev = nullptr;
		item->pevIndex = 0;
		item->lastHash = 0;
		item->next = nullptr;

		while (temp)
		{
			free = temp;
			temp = temp->next;
			hashItemMemPool.Free(free);
		}
	}
}

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
			item->lastHash = nullptr;
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
			newp->lastHash = nullptr;
			newp->pevIndex = pevIndex;

			if (next)
				newp->next = temp;
			else
				newp->next = nullptr;
		}
	}
	else
	{
		item->pev = pev;
		item->lastHash = nullptr;
		item->pevIndex = ENTINDEX(ENT(pev));
	}
}

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
					item->lastHash = nullptr;
					item->next = item->next->next;
				}
				else
				{
					item->pev = nullptr;
					item->lastHash = nullptr;
					item->pevIndex = 0;
				}
			}
			else
			{
				if (stringsHashTable[hash].lastHash == item)
					stringsHashTable[hash].lastHash = nullptr;

				last->next = item->next;
				hashItemMemPool.Free(item);
			}
		}
	}
}

NOINLINE edict_t *CREATE_NAMED_ENTITY(string_t iClass)
{
	edict_t *named = g_engfuncs.pfnCreateNamedEntity(iClass);
	if (named)
	{
		AddEntityHashValue(&named->v, STRING(iClass), CLASSNAME);
	}

	return named;
}

void REMOVE_ENTITY(edict_t *pEntity)
{
	if (pEntity)
	{
		g_engfuncs.pfnRemoveEntity(pEntity);
	}
}

C_DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion)
{
	if (!pFunctionTable || interfaceVersion != INTERFACE_VERSION)
		return 0;

	Q_memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	stringsHashTable.AddMultipleToTail(2048);
	for (int i = 0; i < stringsHashTable.Count(); i++)
	{
		stringsHashTable[i].next = nullptr;
	}

	EmptyEntityHashTable();
	return 1;
}

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

int DispatchSpawn(edict_t *pent)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pent);
	if (pEntity)
	{
		// Initialize these or entities who don't link to the world won't have anything in here
		pEntity->pev->absmin = pEntity->pev->origin - Vector(1, 1, 1);
		pEntity->pev->absmax = pEntity->pev->origin + Vector(1, 1, 1);
		pEntity->Spawn();

		// Try to get the pointer again, in case the spawn function deleted the entity.
		// UNDONE: Spawn() should really return a code to ask that the entity be deleted, but
		// that would touch too much code for me to do that right now.
		pEntity = GET_PRIVATE<CBaseEntity>(pent);

		if (pEntity)
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
		if (pEntity && pEntity->pev->globalname)
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
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pentKeyvalue);
	if (!pEntity)
		return;

	pEntity->KeyValue(pkvd);
}

// HACKHACK -- this is a hack to keep the node graph entity from "touching" things (like triggers)
// while it builds the graph
void DispatchTouch(edict_t *pentTouched, edict_t *pentOther)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pentTouched);
	CBaseEntity *pOther = GET_PRIVATE<CBaseEntity>(pentOther);

	if (pEntity && pOther && !((pEntity->pev->flags | pOther->pev->flags) & FL_KILLME))
		pEntity->Touch(pOther);
}

void DispatchUse(edict_t *pentUsed, edict_t *pentOther)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pentUsed);
	CBaseEntity *pOther = GET_PRIVATE<CBaseEntity>(pentOther);

	if (pEntity && !(pEntity->pev->flags & FL_KILLME))
		pEntity->Use(pOther, pOther, USE_TOGGLE, 0);
}

void DispatchThink(edict_t *pent)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pent);

	if (pEntity)
	{
		if (pEntity->IsDormant())
		{
			ALERT(at_error, "Dormant entity %s is thinking!!\n", STRING(pEntity->pev->classname));
		}

		pEntity->Think();
	}
}

void DispatchBlocked(edict_t *pentBlocked, edict_t *pentOther)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pentBlocked);
	CBaseEntity *pOther = GET_PRIVATE<CBaseEntity>(pentOther);

	if (pEntity)
	{
		pEntity->Blocked(pOther);
	}
}

void DispatchSave(edict_t *pent, SAVERESTOREDATA *pSaveData)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pent);

	if (pEntity && pSaveData)
	{
		ENTITYTABLE *pTable = &pSaveData->pTable[pSaveData->currentIndex];

		if (pTable->pent != pent)
		{
			ALERT(at_error, "ENTITY TABLE OR INDEX IS WRONG!!!!\n");
		}

		if (pEntity->ObjectCaps() & FCAP_DONT_SAVE)
			return;

		// These don't use ltime & nextthink as times really, but we'll fudge around it.
		if (pEntity->pev->movetype == MOVETYPE_PUSH)
		{
			real_t delta = pEntity->pev->nextthink - pEntity->pev->ltime;
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
CBaseEntity *FindGlobalEntity(string_t classname, string_t globalname)
{
	edict_t *pent = FIND_ENTITY_BY_STRING(nullptr, "globalname", STRING(globalname));
	CBaseEntity *pReturn = CBaseEntity::Instance(pent);

	if (pReturn)
	{
		if (!FClassnameIs(pReturn->pev, classname))
		{
			ALERT(at_console, "Global entity found %s, wrong class %s\n", STRING(globalname), STRING(pReturn->pev->classname));
			pReturn = nullptr;
		}
	}

	return pReturn;
}

int DispatchRestore(edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pent);

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

			if (pNewEntity)
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
		pEntity = GET_PRIVATE<CBaseEntity>(pent);

		// Is this an overriding global entity (coming over the transition), or one restoring in a level
		if (globalEntity)
		{
			pSaveData->vecLandmarkOffset = oldOffset;

			if (pEntity)
			{
				UTIL_SetOrigin(pEntity->pev, pEntity->pev->origin);
				pEntity->OverrideReset();
			}
		}
		else if (pEntity && pEntity->pev->globalname)
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

void DispatchObjectCollsionBox(edict_t *pent)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pent);
	if (pEntity)
	{
		pEntity->SetObjectCollisionBox();
		return;
	}

	SetObjectCollisionBox(&pent->v);
}

void SaveWriteFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	CSave saveHelper(pSaveData);
	saveHelper.WriteFields(pname, pBaseData, pFields, fieldCount);
}

void SaveReadFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	CRestore restoreHelper(pSaveData);
	restoreHelper.ReadFields(pname, pBaseData, pFields, fieldCount);
}

BOOL CBaseEntity::TakeHealth(float flHealth, int bitsDamageType)
{
	if (pev->takedamage == DAMAGE_NO)
		return FALSE;

	if (pev->health >= pev->max_health)
		return FALSE;

	pev->health += flHealth;

	if (pev->health > pev->max_health)
	{
		pev->health = pev->max_health;
	}

	return TRUE;
}

bool CBaseEntity::CanTakeHealth(float flHealth) const
{
	if ((pev->health + flHealth) > pev->max_health)
		return false;

	return true;
}

BOOL CBaseEntity::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	Vector vecTemp;

	if (pev->takedamage == DAMAGE_NO)
		return FALSE;

	// UNDONE: some entity types may be immune or resistant to some bitsDamageType
	// if Attacker == Inflictor, the attack was a melee or other instant-hit attack.
	// (that is, no actual entity projectile was involved in the attack so use the shooter's origin).
#ifndef REGAMEDLL_FIXES
	if (pevAttacker == pevInflictor)
	{
		vecTemp = pevInflictor->origin - (VecBModelOrigin(pev));
	}
	else
#endif
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

		real_t flForce = flDamage * ((32 * 32 * 72.0) / (pev->size.x * pev->size.y * pev->size.z)) * 5;

		if (flForce > 1000.0)
			flForce = 1000.0;

		pev->velocity = pev->velocity + vecDir * flForce;
	}

	// do the damage
	pev->health -= flDamage;
	if (pev->health <= 0)
	{
		Killed(pevAttacker, GIB_NORMAL);
		return FALSE;
	}

	return TRUE;
}

void CBaseEntity::Killed(entvars_t *pevAttacker, int iGib)
{
	pev->takedamage = DAMAGE_NO;
	pev->deadflag = DEAD_DEAD;
	UTIL_Remove(this);
}

CBaseEntity *CBaseEntity::GetNextTarget()
{
	if (FStringNull(pev->target))
		return nullptr;

	edict_t *pTarget = FIND_ENTITY_BY_TARGETNAME(nullptr, STRING(pev->target));
	if (FNullEnt(pTarget))
	{
		return nullptr;
	}

	return Instance(pTarget);
}

// Global Savedata for Delay
TYPEDESCRIPTION	CBaseEntity::m_SaveData[] =
{
	DEFINE_FIELD(CBaseEntity, m_pGoalEnt, FIELD_CLASSPTR),
	DEFINE_FIELD(CBaseEntity, m_pfnThink, FIELD_FUNCTION),	// UNDONE: Build table of these!
	DEFINE_FIELD(CBaseEntity, m_pfnTouch, FIELD_FUNCTION),
	DEFINE_FIELD(CBaseEntity, m_pfnUse, FIELD_FUNCTION),
	DEFINE_FIELD(CBaseEntity, m_pfnBlocked, FIELD_FUNCTION),
};

int CBaseEntity::Save(CSave &save)
{
	if (save.WriteEntVars("ENTVARS", pev))
	{
		return save.WriteFields("BASE", this, m_SaveData, ARRAYSIZE(m_SaveData));
	}

	return 0;
}

int CBaseEntity::Restore(CRestore &restore)
{
	int status = restore.ReadEntVars("ENTVARS", pev);
	if (status)
	{
		status = restore.ReadFields("BASE", this, m_SaveData, ARRAYSIZE(m_SaveData));
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

// Initialize absmin & absmax to the appropriate box
void SetObjectCollisionBox(entvars_t *pev)
{
	if (pev->solid == SOLID_BSP && (pev->angles.x || pev->angles.y || pev->angles.z))
	{
		// expand for rotation
		real_t max, v;
		int i;

		max = 0;
		for (i = 0; i < 3; i++)
		{
			v = Q_fabs(real_t(((float *)pev->mins)[i]));
			if (v > max)
			{
				max = v;
			}

			v = Q_fabs(real_t(((float *)pev->maxs)[i]));
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

void CBaseEntity::SetObjectCollisionBox()
{
	::SetObjectCollisionBox(pev);
}

bool CBaseEntity::Intersects(CBaseEntity *pOther)
{
	return Intersects(pOther->pev->absmin, pOther->pev->absmax);
}

bool CBaseEntity::Intersects(const Vector &mins, const Vector &maxs)
{
	if (mins.x > pev->absmax.x
		|| mins.y > pev->absmax.y
		|| mins.z > pev->absmax.z
		|| maxs.x < pev->absmin.x
		|| maxs.y < pev->absmin.y
		|| maxs.z < pev->absmin.z)
	{
		return false;
	}

	return true;
}

void CBaseEntity::MakeDormant()
{
	pev->flags |= FL_DORMANT;
	pev->solid = SOLID_NOT;		// Don't touch
	pev->movetype = MOVETYPE_NONE;	// Don't move
	pev->effects |= EF_NODRAW;	// Don't draw
	pev->nextthink = 0;		// Don't think

	// Relink
	UTIL_SetOrigin(pev, pev->origin);
}

BOOL CBaseEntity::IsInWorld()
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

int CBaseEntity::ShouldToggle(USE_TYPE useType, BOOL currentState)
{
	if (useType != USE_TOGGLE && useType != USE_SET)
	{
		if ((currentState && useType == USE_ON) || (!currentState && useType == USE_OFF))
			return 0;
	}

	return 1;
}

int CBaseEntity::DamageDecal(int bitsDamageType)
{
	if (pev->rendermode == kRenderTransAlpha)
		return -1;

	if (pev->rendermode != kRenderNormal)
		return DECAL_BPROOF1;

	return DECAL_GUNSHOT1 + RANDOM_LONG(0, 4);
}

// NOTE: szName must be a pointer to constant memory, e.g. "monster_class" because the entity
// will keep a pointer to it after this call.
CBaseEntity *CBaseEntity::Create(const char *szName, const Vector &vecOrigin, const Vector &vecAngles, edict_t *pentOwner)
{
	edict_t	*pent = CREATE_NAMED_ENTITY(MAKE_STRING(szName));
	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in Create!\n");
		return nullptr;
	}

	CBaseEntity *pEntity = Instance(pent);

	pEntity->pev->owner = pentOwner;
	pEntity->pev->origin = vecOrigin;
	pEntity->pev->angles = vecAngles;

	DispatchSpawn(pEntity->edict());

	return pEntity;
}

// Returns true if a line can be traced from the caller's eyes to the target
BOOL CBaseEntity::FVisible(CBaseEntity *pEntity)
{
	TraceResult tr;
	Vector vecLookerOrigin;
	Vector vecTargetOrigin;

	if (pEntity->pev->flags & FL_NOTARGET)
		return FALSE;

	// don't look through water
	if ((pev->waterlevel != 3 && pEntity->pev->waterlevel == 3) || (pev->waterlevel == 3 && pEntity->pev->waterlevel == 0))
		return FALSE;

	//look through the caller's 'eyes'
	vecLookerOrigin = pev->origin + pev->view_ofs;
	vecTargetOrigin = pEntity->EyePosition();

	UTIL_TraceLine(vecLookerOrigin, vecTargetOrigin, ignore_monsters, ignore_glass, ENT(pev), &tr);

	if (tr.flFraction != 1.0f)
	{
		// Line of sight is not established
		return FALSE;
	}
	else
	{
		// line of sight is valid.
		return TRUE;
	}
}

// Returns true if a line can be traced from the caller's eyes to the target vector
BOOL CBaseEntity::FVisible(const Vector &vecOrigin)
{
	TraceResult tr;
	Vector vecLookerOrigin;

	//look through the caller's 'eyes'
	vecLookerOrigin = EyePosition();

	UTIL_TraceLine(vecLookerOrigin, vecOrigin, ignore_monsters, ignore_glass, ENT(pev), &tr);

	if (tr.flFraction != 1.0f)
	{
		// Line of sight is not established
		return FALSE;
	}
	else
	{
		// line of sight is valid.
		return TRUE;
	}
}

void CBaseEntity::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	Vector vecOrigin = ptr->vecEndPos - vecDir * 4;

	if (pev->takedamage != DAMAGE_NO)
	{
		AddMultiDamage(pevAttacker, this, flDamage, bitsDamageType);

		int blood = BloodColor();
		if (blood != DONT_BLEED)
		{
			// a little surface blood.
			SpawnBlood(vecOrigin, blood, flDamage);
			TraceBleed(flDamage, vecDir, ptr, bitsDamageType);
		}
	}
}

void CBaseEntity::FireBullets(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker)
{
	static int tracerCount;
	int tracer;

	TraceResult tr;
	Vector vecRight, vecUp;
	bool m_bCreatedShotgunSpark = true;

	vecRight = gpGlobals->v_right;
	vecUp = gpGlobals->v_up;

	if (!pevAttacker)
	{
		// the default attacker is ourselves
		pevAttacker = pev;
	}

	ClearMultiDamage();
	gMultiDamage.type = (DMG_BULLET | DMG_NEVERGIB);

	for (ULONG iShot = 1; iShot <= cShots; iShot++)
	{
		int spark = 0;

		// get circular gaussian spread
		float x, y, z;

		do
		{
			x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			z = x * x + y * y;
		}
		while (z > 1);

		Vector vecDir, vecEnd;

		vecDir = vecDirShooting + x * vecSpread.x * vecRight + y * vecSpread.y * vecUp;
		vecEnd = vecSrc + vecDir * flDistance;

		UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev), &tr);
		tracer = 0;

		if (iTracerFreq != 0 && !(tracerCount++ % iTracerFreq))
		{
			Vector vecTracerSrc;

			if (IsPlayer())
			{
				// adjust tracer position for player
				vecTracerSrc = vecSrc + Vector(0, 0, -4) + gpGlobals->v_right * 2 + gpGlobals->v_forward * 16;
			}
			else
			{
				vecTracerSrc = vecSrc;
			}

			// guns that always trace also always decal
			if (iTracerFreq != 1)
				tracer = 1;

			MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, vecTracerSrc);
				WRITE_BYTE(TE_TRACER);
				WRITE_COORD(vecTracerSrc.x);
				WRITE_COORD(vecTracerSrc.y);
				WRITE_COORD(vecTracerSrc.z);
				WRITE_COORD(tr.vecEndPos.x);
				WRITE_COORD(tr.vecEndPos.y);
				WRITE_COORD(tr.vecEndPos.z);
			MESSAGE_END();
		}

		// do damage, paint decals
		if (tr.flFraction != 1.0f)
		{
			CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

			if (iDamage)
			{
				pEntity->TraceAttack(pevAttacker, iDamage, vecDir, &tr, DMG_BULLET | ((iDamage > 16) ? DMG_ALWAYSGIB : DMG_NEVERGIB));
				TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
				DecalGunshot(&tr, iBulletType, false, pev, false);
			}
			else
			{
				float flDamage;

				switch (iBulletType)
				{
				case BULLET_PLAYER_MP5:
					pEntity->TraceAttack(pevAttacker, gSkillData.plrDmgMP5, vecDir, &tr, DMG_BULLET);
					break;
				case BULLET_PLAYER_BUCKSHOT:
					flDamage = ((1 - tr.flFraction) * 20);
					pEntity->TraceAttack(pevAttacker, int(flDamage), vecDir, &tr, DMG_BULLET);
					break;
				case BULLET_PLAYER_357:
					pEntity->TraceAttack(pevAttacker, gSkillData.plrDmg357, vecDir, &tr, DMG_BULLET);
					break;
				case BULLET_MONSTER_9MM:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmg9MM, vecDir, &tr, DMG_BULLET);
					TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
					DecalGunshot(&tr, iBulletType, false, pev, false);
					break;
				case BULLET_MONSTER_MP5:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmgMP5, vecDir, &tr, DMG_BULLET);
					TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
					DecalGunshot(&tr, iBulletType, false, pev, false);
					break;
				case BULLET_MONSTER_12MM:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmg12MM, vecDir, &tr, DMG_BULLET);

					if (!tracer)
					{
						TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);
						DecalGunshot(&tr, iBulletType, false, pev, false);
					}
					break;
				case BULLET_NONE:
					flDamage = 50;
					pEntity->TraceAttack(pevAttacker, flDamage, vecDir, &tr, DMG_CLUB);
					TEXTURETYPE_PlaySound(&tr, vecSrc, vecEnd, iBulletType);

					// only decal glass
					if (!FNullEnt(tr.pHit) && VARS(tr.pHit)->rendermode != kRenderNormal)
					{
						UTIL_DecalTrace(&tr, DECAL_GLASSBREAK1 + RANDOM_LONG(0, 2));
					}
					break;
				default:
					pEntity->TraceAttack(pevAttacker, gSkillData.monDmg9MM, vecDir, &tr, DMG_BULLET);
					break;
				}
			}
		}

		// make bullet trails
		UTIL_BubbleTrail(vecSrc, tr.vecEndPos, int((flDistance * tr.flFraction) / 64));
	}

	ApplyMultiDamage(pev, pevAttacker);
}

void CBaseEntity::FireBuckshots(ULONG cShots, Vector vecSrc, Vector vecDirShooting, Vector vecSpread, float flDistance, int iTracerFreq, int iDamage, entvars_t *pevAttacker)
{
    static int tracerCount;
    int tracer;

    TraceResult tr;
    Vector vecRight, vecUp;

    vecRight = gpGlobals->v_right;
    vecUp = gpGlobals->v_up;

    if (!pevAttacker)
    {
        // the default attacker is ourselves
        pevAttacker = pev;
    }

    ClearMultiDamage();
    gMultiDamage.type = (DMG_BULLET | DMG_NEVERGIB);

    for (ULONG iShot = 1; iShot <= cShots; iShot++)
    {
        // get circular gaussian spread
        float x, y, z;

        do
        {
            x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
            y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
            z = x * x + y * y;
        }
        while (z > 1);

        Vector vecDir, vecEnd;

        vecDir = vecDirShooting + x * vecSpread.x * vecRight + y * vecSpread.y * vecUp;
        vecEnd = vecSrc + vecDir * flDistance;

        UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev), &tr);
        tracer = 0;

        if (iTracerFreq != 0 && !(tracerCount++ % iTracerFreq))
        {
            Vector vecTracerSrc;

            if (IsPlayer())
            {
                // adjust tracer position for player
                vecTracerSrc = vecSrc + Vector(0, 0, -4) + gpGlobals->v_right * 2 + gpGlobals->v_forward * 16;
            }
            else
            {
                vecTracerSrc = vecSrc;
            }

            // guns that always trace also always decal
            if (iTracerFreq != 1)
                tracer = 1;

            MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, vecTracerSrc);
                WRITE_BYTE(TE_TRACER);
                WRITE_COORD(vecTracerSrc.x);
                WRITE_COORD(vecTracerSrc.y);
                WRITE_COORD(vecTracerSrc.z);
                WRITE_COORD(tr.vecEndPos.x);
                WRITE_COORD(tr.vecEndPos.y);
                WRITE_COORD(tr.vecEndPos.z);
            MESSAGE_END();
        }

        // do damage, paint decals
        if (tr.flFraction != 1.0f)
        {
            CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
            float flDamage = ((1 - tr.flFraction) * iDamage);
            pEntity->TraceAttack(pevAttacker, int(flDamage), vecDir, &tr, DMG_BULLET);
        }

        // make bullet trails
        UTIL_BubbleTrail(vecSrc, tr.vecEndPos, int((flDistance * tr.flFraction) / 64));
    }

    ApplyMultiDamage(pev, pevAttacker);
}

bool EXT_FUNC IsPenetrableEntity_default(Vector &vecSrc, Vector &vecEnd, entvars_t *pevAttacker, edict_t *pHit)
{
	return true;
}

// Go to the trouble of combining multiple pellets into a single damage call.
// This version is used by Players, uses the random seed generator to sync client and server side shots.
Vector CBaseEntity::FireBullets3(Vector vecSrc, Vector vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand)
{
	int iOriginalPenetration = iPenetration;
	int iPenetrationPower;
	float flPenetrationDistance;
	int iCurrentDamage = iDamage;
	float flCurrentDistance;

	TraceResult tr, tr2;
	Vector vecRight, vecUp;

	bool bHitMetal = false;
	int iSparksAmount = 1;

	vecRight = gpGlobals->v_right;
	vecUp = gpGlobals->v_up;

	switch (iBulletType)
	{
	case BULLET_PLAYER_9MM:
		iPenetrationPower = 21;
		flPenetrationDistance = 800;
		break;
	case BULLET_PLAYER_45ACP:
		iPenetrationPower = 15;
		flPenetrationDistance = 500;
		break;
	case BULLET_PLAYER_50AE:
		iPenetrationPower = 30;
		flPenetrationDistance = 1000;
		break;
	case BULLET_PLAYER_762MM:
		iPenetrationPower = 39;
		flPenetrationDistance = 5000;
		break;
	case BULLET_PLAYER_556MM:
		iPenetrationPower = 35;
		flPenetrationDistance = 4000;
		break;
	case BULLET_PLAYER_338MAG:
		iPenetrationPower = 45;
		flPenetrationDistance = 8000;
		break;
	case BULLET_PLAYER_57MM:
		iPenetrationPower = 30;
		flPenetrationDistance = 2000;
		break;
	case BULLET_PLAYER_357SIG:
		iPenetrationPower = 25;
		flPenetrationDistance = 800;
		break;
	default:
		iPenetrationPower = 0;
		flPenetrationDistance = 0;
		break;
	}

	if (!pevAttacker)
	{
		// the default attacker is ourselves
		pevAttacker = pev;
	}

	gMultiDamage.type = (DMG_BULLET | DMG_NEVERGIB);

	float x, y, z;

	if (IsPlayer())
	{
		// Use player's random seed.
		// get circular gaussian spread
		x = UTIL_SharedRandomFloat(shared_rand, -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + 1, -0.5, 0.5);
		y = UTIL_SharedRandomFloat(shared_rand + 2, -0.5, 0.5) + UTIL_SharedRandomFloat(shared_rand + 3, -0.5, 0.5);
	}
	else
	{
		do
		{
			x = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			y = RANDOM_FLOAT(-0.5, 0.5) + RANDOM_FLOAT(-0.5, 0.5);
			z = x * x + y * y;
		}
		while (z > 1);
	}

	Vector vecDir, vecEnd;
	Vector vecOldSrc, vecNewSrc;

	vecDir = vecDirShooting + x * vecSpread * vecRight + y * vecSpread * vecUp;
	vecEnd = vecSrc + vecDir * flDistance;

	float flDamageModifier = 0.5;

	while (iPenetration != 0)
	{
		ClearMultiDamage();
		UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(pev), &tr);

		if (TheBots && tr.flFraction != 1.0f)
		{
			TheBots->OnEvent(EVENT_BULLET_IMPACT, this, (CBaseEntity *)&tr.vecEndPos);
		}

		char cTextureType = UTIL_TextureHit(&tr, vecSrc, vecEnd);
		bool bSparks = false;

		switch (cTextureType)
		{
		case CHAR_TEX_METAL:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.15;
			flDamageModifier = 0.2;
			break;
		case CHAR_TEX_CONCRETE:
			iPenetrationPower *= 0.25;
			break;
		case CHAR_TEX_GRATE:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.5;
			flDamageModifier = 0.4;
			break;
		case CHAR_TEX_VENT:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.5;
			flDamageModifier = 0.45;
			break;
		case CHAR_TEX_TILE:
			iPenetrationPower *= 0.65;
			flDamageModifier = 0.3;
			break;
		case CHAR_TEX_COMPUTER:
			bHitMetal = true;
			bSparks = true;

			iPenetrationPower *= 0.4;
			flDamageModifier = 0.45;
			break;
		case CHAR_TEX_WOOD:
			flDamageModifier = 0.6;
			break;
		default:
			break;
		}
		if (tr.flFraction != 1.0f)
		{
			CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
			iPenetration--;

			flCurrentDistance = tr.flFraction * flDistance;
			iCurrentDamage *= Q_pow(flRangeModifier, flCurrentDistance / 500);

			if (flCurrentDistance > flPenetrationDistance)
			{
				iPenetration = 0;
			}

			bool bIsPenatrable = g_ReGameHookchains.m_IsPenetrableEntity.callChain(IsPenetrableEntity_default, vecSrc, tr.vecEndPos, pevAttacker, tr.pHit);

			if (!bIsPenatrable)
				iPenetration = 0;

			if (tr.iHitgroup == HITGROUP_SHIELD)
			{
				EMIT_SOUND(pEntity->edict(), CHAN_VOICE, (RANDOM_LONG(0, 1) == 1) ? "weapons/ric_metal-1.wav" : "weapons/ric_metal-2.wav", VOL_NORM, ATTN_NORM);
				UTIL_Sparks(tr.vecEndPos);

				pEntity->pev->punchangle.x = iCurrentDamage * RANDOM_FLOAT(-0.15, 0.15);
				pEntity->pev->punchangle.z = iCurrentDamage * RANDOM_FLOAT(-0.15, 0.15);

				if (pEntity->pev->punchangle.x < 4)
				{
					pEntity->pev->punchangle.x = -4;
				}

				if (pEntity->pev->punchangle.z < -5)
				{
					pEntity->pev->punchangle.z = -5;
				}
				else if (pEntity->pev->punchangle.z > 5)
				{
					pEntity->pev->punchangle.z = 5;
				}

				break;
			}

			float flDistanceModifier;
			if (VARS(tr.pHit)->solid != SOLID_BSP || !iPenetration)
			{
				iPenetrationPower = 42;
				flDamageModifier = 0.75;
				flDistanceModifier = 0.75;
			}
			else
				flDistanceModifier = 0.5;

			DecalGunshot(&tr, iBulletType, (!bPistol && RANDOM_LONG(0, 3)), pev, bHitMetal);

			vecSrc = tr.vecEndPos + (vecDir * iPenetrationPower);
			flDistance = (flDistance - flCurrentDistance) * flDistanceModifier;
			vecEnd = vecSrc + (vecDir * flDistance);

			pEntity->TraceAttack(pevAttacker, iCurrentDamage, vecDir, &tr, (DMG_BULLET | DMG_NEVERGIB));
			iCurrentDamage *= flDamageModifier;
		}
		else
			iPenetration = 0;

		ApplyMultiDamage(pev, pevAttacker);
	}

	return Vector(x * vecSpread, y * vecSpread, 0);
}

void CBaseEntity::TraceBleed(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	if (BloodColor() == DONT_BLEED)
		return;

	if (!flDamage)
		return;

	if (!(bitsDamageType & (DMG_CRUSH | DMG_BULLET | DMG_SLASH | DMG_BLAST | DMG_CLUB | DMG_MORTAR)))
		return;

	// make blood decal on the wall!
	TraceResult Bloodtr;
	Vector vecTraceDir;
	float flNoise;
	int cCount;
	int i;

	if (flDamage < 10.0f)
	{
		flNoise = 0.1f;
		cCount = 1;
	}
	else if (flDamage < 25.0f)
	{
		flNoise = 0.2f;
		cCount = 2;
	}
	else
	{
		flNoise = 0.3f;
		cCount = 4;
	}

	for (i = 0; i < cCount; i++)
	{
		// trace in the opposite direction the shot came from (the direction the shot is going)
		vecTraceDir = vecDir * -1.0f;

		vecTraceDir.x += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.y += RANDOM_FLOAT(-flNoise, flNoise);
		vecTraceDir.z += RANDOM_FLOAT(-flNoise, flNoise);

		UTIL_TraceLine(ptr->vecEndPos, ptr->vecEndPos + vecTraceDir * -172.0f, ignore_monsters, ENT(pev), &Bloodtr);
		if (Bloodtr.flFraction != 1.0f)
		{
			if (!RANDOM_LONG(0, 2))
			{
				UTIL_BloodDecalTrace(&Bloodtr, BloodColor());
			}
		}
	}
}

void CBaseEntity::SUB_StartFadeOut()
{
	if (pev->rendermode == kRenderNormal)
	{
		pev->renderamt = 255.0f;
		pev->rendermode = kRenderTransTexture;
	}

	pev->solid = SOLID_NOT;
	pev->avelocity = g_vecZero;
	pev->nextthink = gpGlobals->time + 0.1f;

	SetThink(&CBaseEntity::SUB_FadeOut);
}

void CBaseEntity::SUB_FadeOut()
{
	if (pev->renderamt > 7)
	{
		pev->renderamt -= 7.0f;
		pev->nextthink = gpGlobals->time + 0.1f;
	}
	else
	{
		pev->renderamt = 0.0f;
		pev->nextthink = gpGlobals->time + 0.2f;
		SetThink(&CBaseEntity::SUB_Remove);
	}
}

void OnGameShutdown()
{
	FileSystem_Shutdown();
}

void OnFreeEntPrivateData(edict_t *pEnt)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pEnt);
	if (!pEntity)
		return;

#ifdef REGAMEDLL_API
	pEntity->OnDestroy();
#endif

	pEntity->UpdateOnRemove();
	RemoveEntityHashValue(pEntity->pev, STRING(pEntity->pev->classname), CLASSNAME);

#ifdef REGAMEDLL_API
	if (pEntity->m_pEntity) {
		delete pEntity->m_pEntity;
		pEntity->m_pEntity = nullptr;
	}
#endif

#ifdef REGAMEDLL_FIXES
	if (TheCSBots()) {
		TheCSBots()->OnFreeEntPrivateData(pEntity);
	}
#endif
}

#ifdef REGAMEDLL_API
void CBaseEntity::OnCreate()
{
	;
}

void CBaseEntity::OnDestroy()
{
	;
}
#endif
