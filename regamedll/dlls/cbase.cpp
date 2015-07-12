#include "precompiled.h"
#include "game_shared/perf_counter.h"

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

CMemoryPool hashItemMemPool(sizeof(hash_item_t), 64);
BOOL gTouchDisabled = FALSE;

#else // HOOK_GAMEDLL

DLL_FUNCTIONS gFunctionTable;
NEW_DLL_FUNCTIONS gNewDLLFunctions;

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
	hash_item_t *item;
	hash_item_t *temp;
	hash_item_t *free;

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
	hash_item_t *item;
	hash_item_t *next;
	hash_item_t *temp;
	hash_item_t *newp;
	int hash;
	int pevIndex;
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
		if (!strcmp(STRING(item->pev->classname), STRING(pev->classname)))
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
		if (!strcmp(STRING(item->pev->classname), STRING(pev->classname)))
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
NOBODY void printEntities(void)
{
//	{ 
//		int i;                                                //   339
//		{
//			class hash_item_t *item;                     //   345
//			operator[](CUtlVector<hash_item_t> *const this,
//					int i);  //   341
//			ENTINDEX(edict_t *pEdict);  //   343
//			ENTINDEX(edict_t *pEdict);  //   348
//		} 
//	} 
}

/* <311e9> ../cstrike/dlls/cbase.cpp:354 */
edict_t *CREATE_NAMED_ENTITY(string_t iClass)
{
	edict_t *named = g_engfuncs.pfnCreateNamedEntity(iClass);
	if (named)
		AddEntityHashValue(&named->v, STRING(iClass), CLASSNAME);
	return named;
}

/* <31249> ../cstrike/dlls/cbase.cpp:366 */
void REMOVE_ENTITY(edict_t *e)
{
	if (e)
		(*g_engfuncs.pfnRemoveEntity)(e);
}

/* <30158> ../cstrike/dlls/cbase.cpp:375 */
//NOBODY void CONSOLE_ECHO(char *pszMsg, ...)
//{
//	{ 
//		va_list argptr;                                       //   377
//		char szStr;                                           //   378
//	} 
//}

/* <31273> ../cstrike/dlls/cbase.cpp:386 */
NOBODY void loopPerformance(void)
{
//	{
//		class CPerformanceCounter loopCounter;                //   390
//		double start;                                         //   393
//		int i;                                                //   395
//		double end;                                           //   419
//		GetCurTime(CPerformanceCounter *const this);  //   393
//		{ 
//			class CBaseEntity *pSpot;                    //   398
//		} 
//		GetCurTime(CPerformanceCounter *const this);  //   419
//		GetCurTime(CPerformanceCounter *const this);  //   422
//		{ 
//			class CBaseEntity *pSpot;                    //   426
//		} 
//		GetCurTime(CPerformanceCounter *const this);  //   447
//	} 
}

/* <313df> ../cstrike/dlls/cbase.cpp:451 */
C_DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion)
{
	if (!pFunctionTable || interfaceVersion != INTERFACE_VERSION)
		return 0;

	Q_memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	stringsHashTable.AddMultipleToTail(2048);
	for (int i = 0; i < stringsHashTable.Count(); i++)
		stringsHashTable[i].next = NULL;

	EmptyEntityHashTable();
	return 1;
}

/* <3161a> ../cstrike/dlls/cbase.cpp:471 */
NOXREF extern "C" C_EXPORT int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion)
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
extern "C" C_EXPORT int GetNewDLLFunctions(NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion)
{
	if (!pFunctionTable || *interfaceVersion != NEW_DLL_FUNCTIONS_VERSION)
	{
		*interfaceVersion = NEW_DLL_FUNCTIONS_VERSION;
		return 0;
	}
	Q_memcpy(pFunctionTable, &gNewDLLFunctions, sizeof(NEW_DLL_FUNCTIONS));
	return 1;
}

int (*pDispatchSpawn)(edict_t *);

/* <30ab0> ../cstrike/dlls/cbase.cpp:498 */
NOBODY int __declspec(naked) DispatchSpawn(edict_t *pent)
{
	//Reverse me
	__asm
	{
		jmp pDispatchSpawn;
	}

//	{
//		class CBaseEntity *pEntity;                          //   500
//		GET_PRIVATE(edict_t *pent);  //   500
//		operator-(const class Vector *const this,
//				const class Vector &v);  //   505
//		operator+(const class Vector *const this,
//				const class Vector &v);  //   506
//		GET_PRIVATE(edict_t *pent);  //   513
//		{
//			const globalentity_t *pGlobal;              //   527
//			FStrEq(const char *sz1,
//				const char *sz2);  //   533
//			MakeDormant(CBaseEntity *const this);  //   534
//		} 
//	} 
}

/* <2e8a0> ../cstrike/dlls/cbase.cpp:549 */
void DispatchKeyValue(edict_t *pentKeyvalue, KeyValueData *pkvd)
{
	if (!pkvd || !pentKeyvalue)
		return;

	EntvarsKeyvalue(VARS(pentKeyvalue), pkvd);

	if (pkvd->fHandled || !pkvd->szClassName)
		return;

	CBaseEntity *pEntity = (CBaseEntity *)GET_PRIVATE(pentKeyvalue);

	if (pEntity)
		pEntity->KeyValue(pkvd);
}

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
NOBODY void DispatchUse(edict_t *pentUsed, edict_t *pentOther)
{
//	{
//		class CBaseEntity *pEntity;                          //   589
//		class CBaseEntity *pOther;                           //   590
//		GET_PRIVATE(edict_t *pent);  //   589
//		GET_PRIVATE(edict_t *pent);  //   590
//	} 
}

/* <2fb2f> ../cstrike/dlls/cbase.cpp:596 */
NOBODY void DispatchThink(edict_t *pent)
{
//	{
//		class CBaseEntity *pEntity;                          //   598
//		GET_PRIVATE(edict_t *pent);  //   598
//	} 
}

/* <2fb89> ../cstrike/dlls/cbase.cpp:612 */
NOBODY void DispatchBlocked(edict_t *pentBlocked, edict_t *pentOther)
{
//	{
//		class CBaseEntity *pEntity;                          //   614
//		class CBaseEntity *pOther;                           //   615
//		GET_PRIVATE(edict_t *pent);  //   614
//		GET_PRIVATE(edict_t *pent);  //   615
//	} 
}

/* <2ff56> ../cstrike/dlls/cbase.cpp:621 */
NOBODY void DispatchSave(edict_t *pent, SAVERESTOREDATA *pSaveData)
{
//	{
//		class CBaseEntity *pEntity;                          //   623
//		GET_PRIVATE(edict_t *pent);  //   623
//		{
//			ENTITYTABLE *pTable;                         //   627
//			class CSave saveHelper;                       //   646
//			{ 
//				float delta;                          //   638
//			} 
//			CSave(CSave *const this,
//				SAVERESTOREDATA *pdata);  //   646
//			~CSave(CSave *const this,
//				intconst __in_chrg);  //   646
//		} 
//	} 
}

/* <31697> ../cstrike/dlls/cbase.cpp:656 */
CBaseEntity *FindGlobalEntity(string_t classname, string_t globalname)
{
	edict_t *pent = FIND_ENTITY_BY_STRING(NULL, "globalname", STRING(globalname));
	CBaseEntity *pReturn = CBaseEntity::Instance(pent);
	if (pReturn)
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
NOBODY int DispatchRestore(edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity)
{
//	{
//		class CBaseEntity *pEntity;                          //   675
//		GET_PRIVATE(edict_t *pent);  //   675
//		{ 
//			entvars_t tmpVars;                            //   679
//			class Vector oldOffset;                       //   680
//			class CRestore restoreHelper;                 //   682
//			CRestore(CRestore *const this,
//				SAVERESTOREDATA *pdata);  //   682
//			{
//				class CRestore tmpRestore;            //   685
//				const globalentity_t *pGlobal;      //   695
//				class CBaseEntity *pNewEntity;       //   706
//				CRestore(CRestore *const this,
//					SAVERESTOREDATA *pdata);  //   685
//				PrecacheMode(CRestore *const this,
//						BOOL mode);  //   686
//				FStrEq(const char *sz1,
//					const char *sz2);  //   701
//				SetGlobalMode(CRestore *const this,
//						int global);  //   710
//				operator-(const class Vector *const this,
//						const class Vector &v);  //   711
//				operator+(const class Vector *const this,
//						const class Vector &v);  //   711
//				~CRestore(CRestore *const this,
//						intconst __in_chrg);  //   685
//				~CRestore(CRestore *const this,
//						intconst __in_chrg);  //   685
//			} 
//			GET_PRIVATE(edict_t *pent);  //   738
//			{
//				const globalentity_t *pGlobal;      //   752
//				FStrEq(const char *sz1,
//					const char *sz2);  //   758
//				MakeDormant(CBaseEntity *const this);  //   760
//			} 
//			~CRestore(CRestore *const this,
//					intconst __in_chrg);  //   682
//			~CRestore(CRestore *const this,
//					intconst __in_chrg);  //   682
//		} 
//	} 
}

/* <2fdcd> ../cstrike/dlls/cbase.cpp:776 */
NOBODY void DispatchObjectCollsionBox(edict_t *pent)
{
//	{ 
//		class CBaseEntity *pEntity;                          //   778
//		GET_PRIVATE(edict_t *pent);  //   778
//	} 
}

/* <2fe94> ../cstrike/dlls/cbase.cpp:788 */
NOBODY void SaveWriteFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
//	{ 
//		class CSave saveHelper;                               //   790
//		CSave(CSave *const this,
//			SAVERESTOREDATA *pdata);  //   790
//		~CSave(CSave *const this,
//			intconst __in_chrg);  //   790
//	} 
}

/* <30047> ../cstrike/dlls/cbase.cpp:795 */
NOBODY void SaveReadFields(SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
//	{ 
//		class CRestore restoreHelper;                         //   797
//		CRestore(CRestore *const this,
//			SAVERESTOREDATA *pdata);  //   797
//		~CRestore(CRestore *const this,
//				intconst __in_chrg);  //   797
//	} 
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
	if (pEntity)
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
int CBaseEntity::TakeHealth_(float flHealth, int bitsDamageType)
{
	if (pev->takedamage == DAMAGE_NO)
		return 0;

	if (pev->health >= pev->max_health)
		return 0;

	pev->health += flHealth;

	if (pev->health > pev->max_health)
		pev->health = pev->max_health;

	return 1;
}

/* <305af> ../cstrike/dlls/cbase.cpp:876 */
NOBODY int CBaseEntity::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{ 
//		class Vector vecTemp;                                 //   878
//	} 
//	TakeDamage(CBaseEntity *const this,
//			entvars_t *pevInflictor,
//			entvars_t *pevAttacker,
//			float flDamage,
//			int bitsDamageType);  //   876
	return 0;
}

/* <2fe50> ../cstrike/dlls/cbase.cpp:927 */
NOBODY void CBaseEntity::Killed_(entvars_t *pevAttacker, int iGib)
{
}

/* <2fc1c> ../cstrike/dlls/cbase.cpp:935 */
NOBODY CBaseEntity *CBaseEntity::GetNextTarget_(void)
{
//	{
//		edict_t *pTarget;                                    //   939
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   939
//		FNullEnt(const edict_t *pent);  //   940
//		Instance(edict_t *pent);  //   943
//	}
	return NULL;
}

/* <302a6> ../cstrike/dlls/cbase.cpp:958 */
NOBODY int CBaseEntity::Save(CSave &save)
{
//	Save(CBaseEntity *const this,
//		class CSave &save);  //   958
	return 0;
}

/* <30440> ../cstrike/dlls/cbase.cpp:966 */
NOBODY int CBaseEntity::Restore(CRestore &restore)
{
//	{
//		int status;                                           //   968
//	} 
//	Restore(CBaseEntity *const this,
//		class CRestore &restore);  //   966
	return 0;
}

/* <2fcf6> ../cstrike/dlls/cbase.cpp:991 */
NOBODY void SetObjectCollisionBox(entvars_t *pev)
{
//	operator+(const class Vector *const this,
//			const class Vector &v);  //  1017
//	operator+(const class Vector *const this,
//			const class Vector &v);  //  1018
//	{ 
//		float max;                                            //   996
//		float v;                                              //   996
//		int i;                                                //   997
//		fabs(double __x);  //  1002
//		fabs(double __x);  //  1005
//	} 
}

/* <2fe2a> ../cstrike/dlls/cbase.cpp:1030 */
NOBODY void CBaseEntity::SetObjectCollisionBox(void)
{
	::SetObjectCollisionBox(pev);
}

/* <31c0e> ../cstrike/dlls/cbase.cpp:1036 */
NOBODY int CBaseEntity::Intersects(CBaseEntity *pOther)
{
}

/* <31c43> ../cstrike/dlls/cbase.cpp:1048 */
void CBaseEntity::MakeDormant(void)
{
	pev->flags |= FL_DORMANT;
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects |= EF_NODRAW;
	pev->nextthink = 0;
	UTIL_SetOrigin(pev, pev->origin);
}

/* <31c66> ../cstrike/dlls/cbase.cpp:1064 */
NOBODY int CBaseEntity::IsDormant(void)
{
	return (pev->flags & FL_DORMANT) == FL_DORMANT;
}

/* <30221> ../cstrike/dlls/cbase.cpp:1069 */
NOBODY BOOL CBaseEntity::IsInWorld_(void)
{
//	IsInWorld(CBaseEntity *const this);  //  1069
	return FALSE;
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
NOBODY int CBaseEntity::DamageDecal_(int bitsDamageType)
{
//	DamageDecal(CBaseEntity *const this,
//			int bitsDamageType);  //  1100
	return 0;
}

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
NOBODY void OnFreeEntPrivateData(edict_t *pEnt)
{
	CBaseEntity *pEntity = CBaseEntity::Instance(pEnt);
	if (!pEntity)
		return;

	pEntity->UpdateOnRemove();
	RemoveEntityHashValue(pEntity->pev, STRING(pEntity->pev->classname), CLASSNAME);
}

#ifdef HOOK_GAMEDLL

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
	return GetNextTarget();
}

BOOL CBaseEntity::FVisible(CBaseEntity *pEntity)
{
	return FVisible_(pEntity);
}

BOOL CBaseEntity::FVisible(Vector &vecOrigin)
{
	return FVisible_(vecOrigin);
}

#endif // HOOK_GAMEDLL