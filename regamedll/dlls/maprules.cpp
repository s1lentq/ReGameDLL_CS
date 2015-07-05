#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CRuleEntity::m_SaveData[] =
{
	DEFINE_FIELD(CRuleEntity, m_iszMaster, FIELD_STRING),
};

TYPEDESCRIPTION CGameText::m_SaveData[] =
{
	DEFINE_ARRAY(CGameText, m_textParms, FIELD_CHARACTER, sizeof(hudtextparms_t)),
};

TYPEDESCRIPTION CGamePlayerZone::m_SaveData[] =
{
	DEFINE_FIELD(CGamePlayerZone, m_iszInTarget, FIELD_STRING),
	DEFINE_FIELD(CGamePlayerZone, m_iszOutTarget, FIELD_STRING),
	DEFINE_FIELD(CGamePlayerZone, m_iszInCount, FIELD_STRING),
	DEFINE_FIELD(CGamePlayerZone, m_iszOutCount, FIELD_STRING),
};

#else

TYPEDESCRIPTION (*CRuleEntity::pm_SaveData)[1];
TYPEDESCRIPTION (*CGameText::pm_SaveData)[1];
TYPEDESCRIPTION (*CGamePlayerZone::pm_SaveData)[4];

#endif // HOOK_GAMEDLL

/* <eef33> ../cstrike/dlls/maprules.cpp:57 */
IMPLEMENT_SAVERESTORE(CRuleEntity, CBaseEntity);

/* <eed18> ../cstrike/dlls/maprules.cpp:60 */
NOBODY void CRuleEntity::Spawn_(void)
{
}

/* <eeff6> ../cstrike/dlls/maprules.cpp:68 */
NOBODY void CRuleEntity::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    70
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //    76
//	KeyValue(CRuleEntity *const this,
//		KeyValueData *pkvd);  //    68
}

/* <f0955> ../cstrike/dlls/maprules.cpp:79 */
NOBODY BOOL CRuleEntity::CanFireForActivator(CBaseEntity *pActivator)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //    79
}

/* <eed39> ../cstrike/dlls/maprules.cpp:101 */
NOBODY void CRulePointEntity::Spawn_(void)
{
//	Spawn(CRuleEntity *const this);  //   103
}

/* <eed72> ../cstrike/dlls/maprules.cpp:120 */
NOBODY void CRuleBrushEntity::Spawn_(void)
{
//	Spawn(CRuleEntity *const this);  //   123
}

/* <f099d> ../cstrike/dlls/maprules.cpp:151 */
LINK_ENTITY_TO_CLASS(game_score, CGameScore);

/* <eedb1> ../cstrike/dlls/maprules.cpp:154 */
NOBODY void CGameScore::Spawn_(void)
{
//	Spawn(CRulePointEntity *const this);  //   156
}

/* <efc68> ../cstrike/dlls/maprules.cpp:160 */
NOBODY void CGameScore::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   162
//	KeyValue(CRuleEntity *const this,
//		KeyValueData *pkvd);  //   168
//	KeyValue(CGameScore *const this,
//		KeyValueData *pkvd);  //   160
}

/* <ef54c> ../cstrike/dlls/maprules.cpp:173 */
NOBODY void CGameScore::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   175
//	Use(CGameScore *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   173
//	AwardToTeam(CGameScore *const this);  //   181
//	AllowNegativeScore(CGameScore *const this);  //   187
//	Points(CGameScore *const this);  //   187
}

/* <f0a68> ../cstrike/dlls/maprules.cpp:202 */
LINK_ENTITY_TO_CLASS(game_end, CGameEnd);

/* <f0b33> ../cstrike/dlls/maprules.cpp:242 */
LINK_ENTITY_TO_CLASS(game_text, CGameText);

/* <ef497> ../cstrike/dlls/maprules.cpp:205 */
NOBODY void CGameEnd::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   207
//	Use(CGameEnd *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   205
}

/* <ef252> ../cstrike/dlls/maprules.cpp:251 */
IMPLEMENT_SAVERESTORE(CGameText, CRulePointEntity);

/* <f00dd> ../cstrike/dlls/maprules.cpp:254 */
NOBODY void CGameText::KeyValue_(KeyValueData *pkvd)
{
//	{
//		int color;                                            //   278
//	}
//	{
//		int color;                                            //   288
//	}
//	FStrEq(const char *sz1,
//		const char *sz2);  //   256
//	FStrEq(const char *sz1,
//		const char *sz2);  //   261
//	atof(const char *__nptr);  //   263
//	atoi(const char *__nptr);  //   258
//	KeyValue(CGameText *const this,
//		KeyValueData *pkvd);  //   254
}

/* <ef655> ../cstrike/dlls/maprules.cpp:321 */
NOBODY void CGameText::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   323
//	MessageGet(CGameText *const this);  //   328
//	Use(CGameText *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   321
}

/* <f0bfe> ../cstrike/dlls/maprules.cpp:371 */
LINK_ENTITY_TO_CLASS(game_team_master, CGameTeamMaster);

/* <eff4f> ../cstrike/dlls/maprules.cpp:373 */
NOBODY void CGameTeamMaster::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   375
//	FStrEq(const char *sz1,
//		const char *sz2);  //   380
//	KeyValue(CRuleEntity *const this,
//		KeyValueData *pkvd);  //   398
//	{
//		int type;                                             //   382
//		atoi(const char *__nptr);  //   382
//	}
//	KeyValue(CGameTeamMaster *const this,
//		KeyValueData *pkvd);  //   373
}

/* <f0474> ../cstrike/dlls/maprules.cpp:402 */
void CGameTeamMaster::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   404
//	TeamMatch(CGameTeamMaster *const this,
//			class CBaseEntity *pActivator);  //   420
//	Use(CGameTeamMaster *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   402
}

/* <ef2e0> ../cstrike/dlls/maprules.cpp:429 */
BOOL CGameTeamMaster::IsTriggered_(CBaseEntity *pActivator)
{
//	TeamMatch(CGameTeamMaster *const this,
//			class CBaseEntity *pActivator);  //   431
}

/* <eeeaf> ../cstrike/dlls/maprules.cpp:435 */
const char *CGameTeamMaster::TeamID_(void)
{
//	TeamID(CGameTeamMaster *const this);  //   435
}

/* <f0ccd> ../cstrike/dlls/maprules.cpp:444 */
BOOL CGameTeamMaster::TeamMatch(CBaseEntity *pActivator)
{
//	TeamMatch(CGameTeamMaster *const this,
//			class CBaseEntity *pActivator);  //   444
//	AnyTeam(CGameTeamMaster *const this);  //   446
}

/* <f0d2e> ../cstrike/dlls/maprules.cpp:474 */
LINK_ENTITY_TO_CLASS(game_team_set, CGameTeamSet);

/* <ef735> ../cstrike/dlls/maprules.cpp:477 */
void CGameTeamSet::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   479
//	Use(CGameTeamSet *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   477
}




/* <f0dfd> ../cstrike/dlls/maprules.cpp:519 */
LINK_ENTITY_TO_CLASS(game_zone_player, CGamePlayerZone);

/* <ef0a2> ../cstrike/dlls/maprules.cpp:528 */
IMPLEMENT_SAVERESTORE(CGamePlayerZone, CRuleBrushEntity);



/* <efdbc> ../cstrike/dlls/maprules.cpp:530 */
void CGamePlayerZone::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   532
//	FStrEq(const char *sz1,
//		const char *sz2);  //   537
//	KeyValue(CGamePlayerZone *const this,
//		KeyValueData *pkvd);  //   530
}

/* <ef36e> ../cstrike/dlls/maprules.cpp:556 */
void CGamePlayerZone::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		int playersInCount;                                   //   558
//		int playersOutCount;                                  //   559
//		class CBaseEntity *pPlayer;                          //   564
//		{
//			int i;                                        //   566
//			{
//				TraceResult trace;                    //   571
//				int hullNumber;                       //   572
//			}
//		}
//		CanFireForActivator(CRuleEntity *const this,
//					class CBaseEntity *pActivator);  //   561
//	}
//	Use(CGamePlayerZone *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   556
}

/* <f0ecc> ../cstrike/dlls/maprules.cpp:628 */
LINK_ENTITY_TO_CLASS(game_player_hurt, CGamePlayerHurt);

/* <ef815> ../cstrike/dlls/maprules.cpp:631 */
void CGamePlayerHurt::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   633
//	Use(CGamePlayerHurt *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   631
}

/* <f0f9b> ../cstrike/dlls/maprules.cpp:684 */
LINK_ENTITY_TO_CLASS(game_counter, CGameCounter);

/* <eee2d> ../cstrike/dlls/maprules.cpp:686 */
void CGameCounter::Spawn_(void)
{
//	CountValue(CGameCounter *const this);  //   689
//	SetInitialValue(CGameCounter *const this,
//			int value);  //   689
//	Spawn(CRulePointEntity *const this);  //   690
}

/* <ef8ef> ../cstrike/dlls/maprules.cpp:694 */
void CGameCounter::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   696
//	Use(CGameCounter *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   694
}

/* <f106a> ../cstrike/dlls/maprules.cpp:747 */
LINK_ENTITY_TO_CLASS(game_counter_set, CGameCounterSet);

/* <efa65> ../cstrike/dlls/maprules.cpp:750 */
void CGameCounterSet::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   752
//	Use(CGameCounterSet *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   750
}

/* <f1139> ../cstrike/dlls/maprules.cpp:788 */
LINK_ENTITY_TO_CLASS(game_player_equip, CGamePlayerEquip);

/* <ed81f> ../cstrike/dlls/maprules.cpp:791 */
void CGamePlayerEquip::KeyValue_(KeyValueData *pkvd)
{
//	{
//		int i;                                                //   797
//		{
//			char tmp;                                     //   801
//		}
//	}
//	KeyValue(CRuleEntity *const this,
//		KeyValueData *pkvd);  //   793
//	KeyValue(CGamePlayerEquip *const this,
//		KeyValueData *pkvd);  //   791
}

/* <f06ad> ../cstrike/dlls/maprules.cpp:816 */
void CGamePlayerEquip::Touch_(CBaseEntity *pOther)
{
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   818
//	Touch(CGamePlayerEquip *const this,
//		class CBaseEntity *pOther);  //   816
}

/* <f1208> ../cstrike/dlls/maprules.cpp:827 */
void CGamePlayerEquip::EquipPlayer(CBaseEntity *pEntity)
{
//	{
//		class CBasePlayer *pPlayer;                          //   829
//		{
//			int i;                                        //   839
//			{
//				int j;                                //   843
//			}
//		}
//	}
}

/* <f05f3> ../cstrike/dlls/maprules.cpp:851 */
void CGamePlayerEquip::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	EquipPlayer(CGamePlayerEquip *const this,
//			class CBaseEntity *pEntity);  //   853
}

/* <f1268> ../cstrike/dlls/maprules.cpp:881 */
LINK_ENTITY_TO_CLASS(game_player_team, CGamePlayerTeam);

/* <f1337> ../cstrike/dlls/maprules.cpp:884 */
const char *CGamePlayerTeam::TargetTeamName(const char *pszTargetName)
{
//	{
//		class CBaseEntity *pTeamEntity;                      //   886
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   890
//	}
}

/* <f07df> ../cstrike/dlls/maprules.cpp:898 */
void CGamePlayerTeam::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		const char *pszTargetTeam;                          //   905
//		{
//			class CBasePlayer *pPlayer;                  //   908
//		}
//	}
//	CanFireForActivator(CRuleEntity *const this,
//				class CBaseEntity *pActivator);  //   900
//	Use(CGamePlayerTeam *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   898
}

#ifdef HOOK_GAMEDLL

void CRuleEntity::Spawn(void)
{
	Spawn_();
}

void CRuleEntity::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CRuleEntity::Save(CSave &save)
{
	return Save_(save);
}

int CRuleEntity::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRulePointEntity::Spawn(void)
{
	Spawn_();
}

void CRuleBrushEntity::Spawn(void)
{
	Spawn_();
}

void CGameScore::Spawn(void)
{
	Spawn_();
}

void CGameScore::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CGameScore::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameEnd::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameText::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CGameText::Save(CSave &save)
{
	return Save_(save);
}

int CGameText::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGameText::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameTeamMaster::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

BOOL CGameTeamMaster::IsTriggered(CBaseEntity *pActivator)
{
	return IsTriggered_(pActivator);
}

const char *CGameTeamMaster::TeamID(void)
{
	return TeamID_();
}

void CGameTeamMaster::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameTeamSet::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerZone::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CGamePlayerZone::Save(CSave &save)
{
	return Save_(save);
}

int CGamePlayerZone::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGamePlayerZone::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerHurt::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameCounter::Spawn(void)
{
	Spawn_();
}

void CGameCounter::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGameCounterSet::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerEquip::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CGamePlayerEquip::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CGamePlayerEquip::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CGamePlayerTeam::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
