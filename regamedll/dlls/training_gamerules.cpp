#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncWeaponCheck::m_SaveData[] =
{
	DEFINE_FIELD(CFuncWeaponCheck, sTriggerWithItems, FIELD_STRING),
	DEFINE_FIELD(CFuncWeaponCheck, sTriggerNoItems, FIELD_STRING),
	DEFINE_FIELD(CFuncWeaponCheck, iItemCount, FIELD_INTEGER),
	DEFINE_ARRAY(CFuncWeaponCheck, sMaster, FIELD_STRING, MAX_ITEM_COUNTS),
	DEFINE_FIELD(CFuncWeaponCheck, sItemName, FIELD_STRING),
	DEFINE_FIELD(CFuncWeaponCheck, iAnyWeapon, FIELD_INTEGER),
};

TYPEDESCRIPTION CBaseGrenCatch::m_SaveData[] =
{
	DEFINE_FIELD(CBaseGrenCatch, m_NeedGrenadeType, FIELD_INTEGER),
	DEFINE_FIELD(CBaseGrenCatch, m_fSmokeTouching, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseGrenCatch, m_fFlashTouched, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseGrenCatch, sTriggerOnGrenade, FIELD_STRING),
	DEFINE_FIELD(CBaseGrenCatch, sDisableOnGrenade, FIELD_STRING),
};

#else

TYPEDESCRIPTION (*CFuncWeaponCheck::pm_SaveData)[6];
TYPEDESCRIPTION (*CBaseGrenCatch::pm_SaveData)[5];

#endif // HOOK_GAMEDLL

/* <18bcc4> ../cstrike/dlls/training_gamerules.cpp:23 */
NOBODY CHalfLifeTraining::CHalfLifeTraining(void)
{
	PRECACHE_MODEL("models/w_weaponbox.mdl");
}

/* <18ae1b> ../cstrike/dlls/training_gamerules.cpp:27 */
BOOL CHalfLifeTraining::IsDeathmatch_(void)
{
	return FALSE;
}

/* <18ae41> ../cstrike/dlls/training_gamerules.cpp:28 */
void CHalfLifeTraining::InitHUD_(CBasePlayer *pl)
{
	;
}

/* <18bcff> ../cstrike/dlls/training_gamerules.cpp:29 */
void CHalfLifeTraining::HostageDied(void)
{
	CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex(1);

	if (pPlayer)
		pPlayer->pev->radsuit_finished = gpGlobals->time + 3;
}

/* <18b005> ../cstrike/dlls/training_gamerules.cpp:34 */
edict_t *CHalfLifeTraining::GetPlayerSpawnSpot_(CBasePlayer *pPlayer)
{
	CBaseEntity *pSpot = UTIL_FindEntityByClassname(NULL, "info_player_start");

	if (FNullEnt(pSpot))
	{
		ALERT(at_error, "PutClientInServer: no info_player_start on level");
		return INDEXENT(0);
	}

	pPlayer->pev->origin = pSpot->pev->origin + Vector(0, 0, 1);
	pPlayer->pev->v_angle = g_vecZero;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->angles = pSpot->pev->angles;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->pev->fixangle = 1;

	return pSpot->edict();
}

/* <18b4aa> ../cstrike/dlls/training_gamerules.cpp:52 */
NOBODY void CHalfLifeTraining::PlayerThink_(CBasePlayer *pPlayer)
{
//	{
//		class CGrenade *pBomb;                               //    94
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //    81
//		{ 
//			class CBasePlayerWeapon *pWeapon;            //    82
//		} 
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //   124
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //   127
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //   105
//	} 
}

/* <18b79c> ../cstrike/dlls/training_gamerules.cpp:151 */
void CHalfLifeTraining::PlayerSpawn_(CBasePlayer *pPlayer)
{
	if (pPlayer->m_bNotKilled)
		return;

	fInBuyArea = TRUE;
	fVisitedBuyArea = FALSE;
	FillAccountTime = 0;

	pPlayer->m_iJoiningState = JOINED;
	pPlayer->m_iTeam = CT;
	pPlayer->m_bNotKilled = true;
	pPlayer->pev->body = 0;
	pPlayer->m_iModelName = MODEL_URBAN;

	fVGUIMenus = pPlayer->m_bVGUIMenus;
	SET_MODEL(ENT(pPlayer->pev), "models/player.mdl");

	CBaseEntity *pWeaponEntity = NULL;

	while ((pWeaponEntity = UTIL_FindEntityByClassname(pWeaponEntity, "game_player_equip")) != NULL)
		pWeaponEntity->Touch(pPlayer);

	pPlayer->SetPlayerModel(false);
	pPlayer->Spawn();
	pPlayer->m_iHideHUD |= (HIDEHUD_WEAPONS | HIDEHUD_HEALTH | HIDEHUD_TIMER | HIDEHUD_MONEY);
}

/* <18ae74> ../cstrike/dlls/training_gamerules.cpp:182 */
NOBODY int CHalfLifeTraining::ItemShouldRespawn_(CItem *pItem)
{
}

/* <18aea8> ../cstrike/dlls/training_gamerules.cpp:186 */
NOBODY BOOL CHalfLifeTraining::FPlayerCanRespawn_(CBasePlayer *pPlayer)
{
}

/* <18bd40> ../cstrike/dlls/training_gamerules.cpp:190 */
bool CHalfLifeTraining::PlayerCanBuy(CBasePlayer *pPlayer)
{
	return pPlayer->m_signals.GetState() & SIGNAL_BUY;
}

/* <18afa5> ../cstrike/dlls/training_gamerules.cpp:195 */
NOBODY void CHalfLifeTraining::PlayerKilled_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
//	edict(CBaseEntity *const this);  //   198
}

/* <18b0fb> ../cstrike/dlls/training_gamerules.cpp:202 */
NOBODY void CHalfLifeTraining::CheckWinConditions_(void)
{
//	{
//		class CBaseEntity *pHostage;                         //   229
//		{
//			class CGrenade *pBomb;                       //   217
//			Instance(edict_t *pent);  //   225
//			Instance(edict_t *pent);  //   225
//		} 
//		{
//			class CGrenade *pBomb;                       //   205
//			Instance(edict_t *pent);  //   213
//			Instance(edict_t *pent);  //   213
//		} 
//		FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//					const char *pszName);  //   229
//		Instance(edict_t *pent);  //   229
//		{
//			class CBaseEntity *pRescueArea;              //   236
//			class CBaseEntity *pFirstRescueArea;         //   237
//			FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//						const char *pszName);  //   236
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   235
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   235
//			Instance(edict_t *pent);  //   236
//		} 
//	} 
}

/* <18b74f> ../cstrike/dlls/training_gamerules.cpp:280 */
IMPLEMENT_SAVERESTORE(CBaseGrenCatch, CBaseEntity);

/* <18bd74> ../cstrike/dlls/training_gamerules.cpp:282 */
LINK_ENTITY_TO_CLASS(func_grencatch, CBaseGrenCatch);

/* <18af50> ../cstrike/dlls/training_gamerules.cpp:293 */
NOBODY void CBaseGrenCatch::Touch_(CBaseEntity *pOther)
{
//	strstr(const char *__haystack,
//		const char *__needle);  //   297
}

/* <18af02> ../cstrike/dlls/training_gamerules.cpp:284 */
NOBODY void CBaseGrenCatch::Spawn_(void)
{
}

/* <18b835> ../cstrike/dlls/training_gamerules.cpp:300 */
NOBODY void CBaseGrenCatch::Think_(void)
{
//	{
//		class CGrenade *pGrenade;                            //   302
//		BOOL m_fSmokeTouchingLastFrame;                       //   304
//		class CBaseEntity *pTrigger;                         //   320
//		{
//			class Vector vMax;                            //   311
//			class Vector vMin;                            //   311
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   312
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   312
//			Vector(Vector *const this,
//				const class Vector  &const v);  //   311
//			Vector(Vector *const this,
//				const class Vector  &const v);  //   311
//			strstr(const char *__haystack,
//				const char *__needle);  //   314
//			Length(const class Vector *const this);  //   315
//		} 
//	} 
}

/* <18ba09> ../cstrike/dlls/training_gamerules.cpp:358 */
NOBODY void CBaseGrenCatch::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   360
//	FStrEq(const char *sz1,
//		const char *sz2);  //   365
//	FStrEq(const char *sz1,
//		const char *sz2);  //   370
//	FStrEq(const char *sz1,
//		const char *sz2);  //   372
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   376
//	FStrEq(const char *sz1,
//		const char *sz2);  //   373
}

/* <18af29> ../cstrike/dlls/training_gamerules.cpp:400 */
NOBODY void CFuncWeaponCheck::Spawn_(void)
{
}

/* <18b702> ../cstrike/dlls/training_gamerules.cpp:420 */
IMPLEMENT_SAVERESTORE(CFuncWeaponCheck, CBaseEntity);

/* <18be46> ../cstrike/dlls/training_gamerules.cpp:422 */
LINK_ENTITY_TO_CLASS(func_weaponcheck, CFuncWeaponCheck);

/* <18b5f6> ../cstrike/dlls/training_gamerules.cpp:424 */
NOBODY void CFuncWeaponCheck::Touch_(CBaseEntity *pOther)
{
//	{ 
//		class CBasePlayer *pPlayer;                          //   430
//	} 
//	Touch(CFuncWeaponCheck *const this,
//		class CBaseEntity *pOther);  //   424
}

/* <18bb28> ../cstrike/dlls/training_gamerules.cpp:462 */
NOBODY void CFuncWeaponCheck::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   464
//	FStrEq(const char *sz1,
//		const char *sz2);  //   469
//	KeyValue(CFuncWeaponCheck *const this,
//		KeyValueData *pkvd);  //   462
}

#ifdef HOOK_GAMEDLL

void CBaseGrenCatch::Spawn(void)
{
	Spawn_();
}

void CBaseGrenCatch::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBaseGrenCatch::Save(CSave &save)
{
	return Save_(save);
}

int CBaseGrenCatch::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBaseGrenCatch::Think(void)
{
	Think_();
}

void CBaseGrenCatch::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CFuncWeaponCheck::Spawn(void)
{
	Spawn_();
}

void CFuncWeaponCheck::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncWeaponCheck::Save(CSave &save)
{
	return Save_(save);
}

int CFuncWeaponCheck::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CFuncWeaponCheck::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

BOOL CHalfLifeTraining::IsDeathmatch(void)
{
	return IsDeathmatch_();
}

void CHalfLifeTraining::InitHUD(CBasePlayer *pl)
{
	InitHUD_(pl);
}

void CHalfLifeTraining::PlayerSpawn(CBasePlayer *pPlayer)
{
	PlayerSpawn_(pPlayer);
}

void CHalfLifeTraining::PlayerThink(CBasePlayer *pPlayer)
{
	PlayerThink_(pPlayer);
}

BOOL CHalfLifeTraining::FPlayerCanRespawn(CBasePlayer *pPlayer)
{
	return FPlayerCanRespawn_(pPlayer);
}

edict_t *CHalfLifeTraining::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
{
	return GetPlayerSpawnSpot_(pPlayer);
}

void CHalfLifeTraining::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	PlayerKilled_(pVictim, pKiller, pInflictor);
}

int CHalfLifeTraining::ItemShouldRespawn(CItem *pItem)
{
	return ItemShouldRespawn_(pItem);
}

void CHalfLifeTraining::CheckWinConditions(void)
{
	CheckWinConditions_();
}

#endif // HOOK_GAMEDLL