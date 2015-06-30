#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

CBotManager *TheBots = NULL;

cvar_t cv_bot_traceview = { "bot_traceview", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_stop = { "bot_stop", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_show_nav = { "bot_show_nav", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_show_danger = { "bot_show_danger", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_nav_edit = { "bot_nav_edit", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_nav_zdraw = { "bot_nav_zdraw", "4", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_walk = { "bot_walk", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_difficulty = { "bot_difficulty", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_debug = { "bot_debug", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_quicksave = { "bot_quicksave", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_quota = { "bot_quota", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_quota_match = { "bot_quota_match", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_prefix = { "bot_prefix", "", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_rogues = { "bot_allow_rogues", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_pistols = { "bot_allow_pistols", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_shotguns = { "bot_allow_shotguns", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_sub_machine_guns = { "bot_allow_sub_machine_guns", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_rifles = { "bot_allow_rifles", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_machine_guns = { "bot_allow_machine_guns", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_grenades = { "bot_allow_grenades", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_snipers = { "bot_allow_snipers", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_allow_shield = { "bot_allow_shield", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_join_team = { "bot_join_team", "any", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_join_after_player = { &unk_1EF09A, "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_auto_vacate = { "bot_auto_vacate", "1", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_zombie = { "bot_zombie", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_defer_to_human = { "bot_defer_to_human", "0", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_chatter = { "bot_chatter", "normal", FCVAR_SERVER,  0.0f, NULL };
cvar_t cv_bot_profile_db = { "bot_profile_db", "BotProfile.db", FCVAR_SERVER, 0.0f, NULL };

float CCSBotManager::m_flNextCVarCheck;
bool CCSBotManager::m_isMapDataLoaded;
bool CCSBotManager::m_isLearningMap;
bool CCSBotManager::m_isAnalysisRequested;

#else // HOOK_GAMEDLL

CBotManager *TheBots;

cvar_t cv_bot_traceview;
cvar_t cv_bot_stop;
cvar_t cv_bot_show_nav;
cvar_t cv_bot_show_danger;
cvar_t cv_bot_nav_edit;
cvar_t cv_bot_nav_zdraw;
cvar_t cv_bot_walk;
cvar_t cv_bot_difficulty;
cvar_t cv_bot_debug;
cvar_t cv_bot_quicksave;
cvar_t cv_bot_quota;
cvar_t cv_bot_quota_match;
cvar_t cv_bot_prefix;
cvar_t cv_bot_allow_rogues;
cvar_t cv_bot_allow_pistols;
cvar_t cv_bot_allow_shotguns;
cvar_t cv_bot_allow_sub_machine_guns;
cvar_t cv_bot_allow_rifles;
cvar_t cv_bot_allow_machine_guns;
cvar_t cv_bot_allow_grenades;
cvar_t cv_bot_allow_snipers;
cvar_t cv_bot_allow_shield;
cvar_t cv_bot_join_team;
cvar_t cv_bot_join_after_player;
cvar_t cv_bot_auto_vacate;
cvar_t cv_bot_zombie;
cvar_t cv_bot_defer_to_human;
cvar_t cv_bot_chatter;
cvar_t cv_bot_profile_db;

float (*CCSBotManager::pm_flNextCVarCheck);
bool (*CCSBotManager::pm_isMapDataLoaded);
bool (*CCSBotManager::pm_isLearningMap);
bool (*CCSBotManager::pm_isAnalysisRequested);

#endif // HOOK_GAMEDLL

/* <36b3b4> ../cstrike/dlls/bot/cs_bot_manager.cpp:45 */
NOBODY CCSBotManager::CCSBotManager(void)
{
//	{
//		const char *filename;                               //    66
//		int dataLength;                                       //    76
//		char *dataPointer;                                   //    77
//		const VoiceBankList *pVoiceBanks;                   //   100
//		SetLooseBomb(CCSBotManager *const this,
//				class CBaseEntity *bomb);  //    49
//		{
//			const char *dataFile;                       //    84
//			const char *token;                          //    85
//			{
//				char *clone;                         //    90
//				CloneString(const char *str);  //    90
//			}
//		}
//		{
//			int i;                                        //   101
//			size(const class vector<char*, std::allocator<char*>> *const this);  //   101
//		}
//	}
//	CountdownTimer(CountdownTimer *const this);  //    45
}

/* <36b22a> ../cstrike/dlls/bot/cs_bot_manager.cpp:111 */
NOBODY void CCSBotManager::RestartRound_(void)
{
//	{
//		float const defenseRushChance;                         //   129
//		SetLooseBomb(CCSBotManager *const this,
//				class CBaseEntity *bomb);  //   116
//		ResetRadioMessageTimestamps(CCSBotManager *const this);  //   122
//	}
}

/* <36aebc> ../cstrike/dlls/bot/cs_bot_manager.cpp:142 */
NOBODY void UTIL_DrawBox(Extent *extent, int lifetime, int red, int green, int blue)
{
//	{
//		Vector v;                                       //   144
//		int const edge;                                        //   154
//		Vector from;                                    //   165
//		Vector to;                                      //   165
//		bool restart;                                         //   166
//		{
//			int i;                                        //   167
//			{
//				int index;                            //   178
//			}
//		}
//	}
}

/* <36b13d> ../cstrike/dlls/bot/cs_bot_manager.cpp:195 */
NOBODY void CCSBotManager::StartFrame_(void)
{

}

/* <36b62a> ../cstrike/dlls/bot/cs_bot_manager.cpp:276 */
NOBODY bool CCSBotManager::IsWeaponUseable(CBasePlayerItem *item) const
{
//	{
//		int weaponClass;                                      //   284
//		AllowShotguns(const class CCSBotManager *const this);  //   286
//	}
	return false;
}

/* <36b68c> ../cstrike/dlls/bot/cs_bot_manager.cpp:306 */
NOBODY bool CCSBotManager::IsOnDefense(CBasePlayer *player) const
{
}

/* <36b6b8> ../cstrike/dlls/bot/cs_bot_manager.cpp:327 */
NOBODY bool CCSBotManager::IsOnOffense(CBasePlayer *player) const
{
//	IsOnDefense(const class CCSBotManager *const this,
//			const class CBasePlayer *player);  //   329
}

/* <36a3b6> ../cstrike/dlls/bot/cs_bot_manager.cpp:331 */
NOBODY void CCSBotManager::ServerActivate_(void)
{

}

/* <36afa3> ../cstrike/dlls/bot/cs_bot_manager.cpp:368 */
NOBODY void CCSBotManager::ServerDeactivate_(void)
{

}

/* <36afcd> ../cstrike/dlls/bot/cs_bot_manager.cpp:369 */
NOBODY void CCSBotManager::AddServerCommand_(const char *cmd)
{
}

/* <36b0e0> ../cstrike/dlls/bot/cs_bot_manager.cpp:375 */
NOBODY void CCSBotManager::AddServerCommands_(void)
{
//	{
//		bool fFirstTime;                                      //   377
//	}
//	AddServerCommands(CCSBotManager *const this);  //   375
}

/* <36b714> ../cstrike/dlls/bot/cs_bot_manager.cpp:464 */
NOBODY void PrintAllEntities(void)
{
//	{
//		edict_t *edict;                                      //   466
//		{
//			int i;                                        //   468
//		}
//	}
}

/* <36ace2> ../cstrike/dlls/bot/cs_bot_manager.cpp:484 */
NOBODY void CCSBotManager::ServerCommand_(const char *pcmd)
{
//	{
//		const char *msg;                                    //   496
//		char buffer;                                          //   498
//	}
//	{
//		bool killThemAll;                                     //   518
//		{
//			int iIndex;                                   //   523
//			{
//				class CBasePlayer *pPlayer;          //   525
//				const char *name;                   //   533
//			}
//		}
//	}
//	{
//		bool kickThemAll;                                     //   548
//		{
//			int iIndex;                                   //   553
//			{
//				class CBasePlayer *pPlayer;          //   555
//				const char *name;                   //   563
//			}
//		}
//	}
//	{
//		char filename;                                        //   696
//	}
//	{
//		const BotPhraseList *placeList;                     //   716
//		int i;                                                //   717
//		{
//			const_iterator iter;                          //   718
//		}
//	}
//	{
//		const BotPhraseList *placeList;                     //   733
//		const class BotPhrase *found;                       //   734
//		bool isAmbiguous;                                     //   735
//		{
//			const_iterator iter;                          //   736
//		}
//	}
//	{
//		class CNavArea *area;                                //   789
//		{
//			class CBaseEntity *pEntity;                  //   792
//			{
//				class CBasePlayer *playerOrBot;      //   797
//				{
//					class CCSBot *bot;           //   801
//				}
//			}
//		}
//	}
//	{
//		unsigned int encounterMem;                            //   829
//		{
//			iterator iter;                                //   830
//			{
//				class CNavArea *area;                //   832
//				{
//					iterator siter;               //   834
//					{
//						class SpotEncounter se; //   838
//					}
//				}
//			}
//		}
//	}
}

/* <36c3c2> ../cstrike/dlls/bot/cs_bot_manager.cpp:903 */
NOBODY bool CCSBotManager::BotAddCommand(BotProfileTeamType team, bool isFromConsole)
{
//	{
//		const class BotProfile *profile;                    //   913
//		GetDifficultyLevel(void);  //   958
//		{
//			enum TeamName defaultTeam;                    //   947
//		}
//		{
//			class CHalfLifeMultiplay *mp;                //   918
//			bool ignoreHumans;                            //   919
//			GetProfile(const class BotProfileManager *const this,
//					const char *name,
//					enum BotProfileTeamType team);  //   927
//		}
//	}
	return false;
}

/* <36d10f> ../cstrike/dlls/bot/cs_bot_manager.cpp:979 */
NOBODY void CCSBotManager::MaintainBotQuota(void)
{
//	{
//		int totalHumansInGame;                                //   984
//		int humanPlayersInGame;                               //   985
//		class CHalfLifeMultiplay *mp;                        //   991
//		int desiredBotCount;                                  //   993
//		BotAddCommand(BotProfileTeamType team,
//				bool isFromConsole);  //  1017
//		{
//			enum TeamName kickTeam;                       //  1027
//		}
//		{
//			bool humansAreCTs;                            //  1067
//		}
//	}
}

/* <36d1dd> ../cstrike/dlls/bot/cs_bot_manager.cpp:1086 */
NOBODY void CCSBotManager::MonitorBotCVars(void)
{
}

/* <36b780> ../cstrike/dlls/bot/cs_bot_manager.cpp:1109 */
NOBODY void CCSBotManager::ValidateMapData(void)
{
//	{
//		class CBaseEntity *entity;                           //  1135
//		int i;                                                //  1136
//		{
//			bool found;                                   //  1144
//			bool isLegacy;                                //  1145
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  1159
//			Vector(Vector *const this,
//				const Vector &v);  //  1189
//			Instance(edict_t *pent);  //  1139
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  1147
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  1153
//			operator+(const Vector *const this,
//					const Vector &v);  //  1189
//			operator/(const Vector *const this,
//					float fl);  //  1189
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  1165
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  1171
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  1178
//		}
//		{
//			class Zone *zone;                            //  1230
//			float const zFudge;                            //  1249
//			{
//				float const legacyRange;               //  1234
//			}
//			{
//				iterator iter;                        //  1255
//				{
//					class CNavArea *area;        //  1257
//					const class Extent *areaExtent;   //  1258
//				}
//				operator++(_List_iterator<CNavArea*> *const this);  //  1255
//			}
//		}
//		edict(CBaseEntity *const this);  //  1208
//		FNullEnt(const edict_t *pent);  //  1208
//	}
}


NOBODY void CCSBotManager::ClientDisconnect_(CBasePlayer *pPlayer)
{

}

/* <36c2b2> ../cstrike/dlls/bot/cs_bot_manager.cpp:1278 */
NOBODY bool CCSBotManager::AddBot(BotProfile *profile, BotProfileTeamType team)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  1285
//		class CCSBot *pBot;                                  //  1286
//		int nTeamSlot;                                        //  1287
//		{
//			int nJoinedTeam;                              //  1329
//			edict(CBaseEntity *const this);  //  1331
//			edict(CBaseEntity *const this);  //  1337
//			entindex(CBaseEntity *const this);  //  1337
//			{
//				int skin;                             //  1348
//			}
//		}
//	}
}

/* <36bb90> ../cstrike/dlls/bot/cs_bot_manager.cpp:1375 */
NOBODY const CCSBotManager::Zone *CCSBotManager::GetZone(const Vector *pos) const
{
//	{
//		int z;                                                //  1377
//		Contains(const class Extent *const this,
//			const Vector *pos);  //  1379
//	}
}

/* <36bbfd> ../cstrike/dlls/bot/cs_bot_manager.cpp:1392 */
NOBODY const CCSBotManager::Zone *CCSBotManager::GetClosestZone(const Vector *pos) const
{
//	{
//		const class Zone *close;                            //  1394
//		float closeRangeSq;                                   //  1395
//		{
//			int z;                                        //  1397
//			{
//				float rangeSq;                        //  1399
//				operator-(const Vector *const this,
//						const Vector &v);  //  1399
//				LengthSquared(const Vector *const this);  //  1399
//			}
//		}
//	}
}

/* <36bcc9> ../cstrike/dlls/bot/cs_bot_manager.cpp:1415 */
NOBODY const Vector *CCSBotManager::GetRandomPositionInZone(const Zone *zone) const
{
//	{
//		Vector pos;                                     //  1417
//		int a;                                                //  1426
//		class CNavArea *area;                                //  1427
//		{
//			const class Extent *areaExtent;             //  1439
//			class Extent overlap;                         //  1440
//		}
//	}
}

/* <36bd64> ../cstrike/dlls/bot/cs_bot_manager.cpp:1458 */
NOBODY CNavArea *CCSBotManager::GetRandomAreaInZone(const Zone *zone) const
{
//	{
//		int a;                                                //  1466
//	}
}

/* <36b02d> ../cstrike/dlls/bot/cs_bot_manager.cpp:1477 */
void CCSBotManager::OnEvent_(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_BOMB_PLANTED:
		m_isBombPlanted = true;
		m_bombPlantTimestamp = gpGlobals->time;
		break;

	case EVENT_BOMB_DEFUSING:
		m_bombDefuser = (CBasePlayer *)entity;
		break;

	case EVENT_BOMB_DEFUSE_ABORTED:
		m_bombDefuser = NULL;
		break;

	case EVENT_BOMB_DEFUSED:
		m_isBombPlanted = false;
		m_bombDefuser = NULL;
		break;

	case EVENT_TERRORISTS_WIN:
	case EVENT_CTS_WIN:
	case EVENT_ROUND_DRAW:
		m_isRoundOver = true;
		break;

	case EVENT_RADIO_ENEMY_SPOTTED:
		m_lastSeenEnemyTimestamp = gpGlobals->time;
		SetLastSeenEnemyTimestamp();
		break;

	default:
		break;
	}
	CBotManager::OnEvent(event, entity, other);
}

NOBODY BOOL CCSBotManager::ClientCommand_(CBasePlayer *pPlayer, const char *pcmd)
{

}

/* <36bdb3> ../cstrike/dlls/bot/cs_bot_manager.cpp:1541 */
NOBODY float CCSBotManager::GetBombTimeLeft(void) const
{
}

/* <36bddb> ../cstrike/dlls/bot/cs_bot_manager.cpp:1547 */
void CCSBotManager::SetLooseBomb(CBaseEntity *bomb)
{
	m_looseBomb = bomb;

	if (bomb)
		m_looseBombArea = TheNavAreaGrid.GetNearestNavArea( &bomb->pev->origin );
	else
		m_looseBombArea = NULL;
}

/* <36b14d> ../cstrike/dlls/bot/cs_bot_manager.cpp:1565 */
NOBODY bool CCSBotManager::IsImportantPlayer_(CBasePlayer *player)
{
//	IsImportantPlayer(const class CCSBotManager *const this,
//				class CBasePlayer *player);  //  1565
}

/* <36b1a7> ../cstrike/dlls/bot/cs_bot_manager.cpp:1602 */
NOBODY unsigned int CCSBotManager::GetPlayerPriority_(CBasePlayer *player) const
{
//	{
//		unsigned int const lowestPriority;                     //  1604
//		class CCSBot *bot;                                   //  1613
//	}
//	GetPlayerPriority(const class CCSBotManager *const this,
//				class CBasePlayer *player);  //  1602
}

/* <36be2e> ../cstrike/dlls/bot/cs_bot_manager.cpp:1655 */
NOBODY float CCSBotManager::GetRadioMessageTimestamp(GameEventType event, int teamID)
{
}

/* <36be76> ../cstrike/dlls/bot/cs_bot_manager.cpp:1667 */
NOBODY float CCSBotManager::GetRadioMessageInterval(GameEventType event, int teamID)
{
}

/* <36bebe> ../cstrike/dlls/bot/cs_bot_manager.cpp:1680 */
NOBODY void CCSBotManager::SetRadioMessageTimestamp(GameEventType event, int teamID)
{
}

/* <36bf06> ../cstrike/dlls/bot/cs_bot_manager.cpp:1690 */
NOBODY void CCSBotManager::ResetRadioMessageTimestamps(void)
{
//	{
//		int t;                                                //  1692
//		{
//			int m;                                        //  1694
//		}
//	}
}

#ifdef HOOK_GAMEDLL

void CCSBotManager::ClientDisconnect(CBasePlayer *pPlayer)
{
	ClientDisconnect_(pPlayer);
}

BOOL CCSBotManager::ClientCommand(CBasePlayer *pPlayer, const char *pcmd)
{
	return ClientCommand_(pPlayer, pcmd);
}

void CCSBotManager::ServerActivate(void)
{
	ServerActivate_();
}

void CCSBotManager::ServerDeactivate(void)
{
	ServerDeactivate_();
}

void CCSBotManager::ServerCommand(const char *pcmd)
{
	ServerCommand_(pcmd);
}

void CCSBotManager::AddServerCommand(const char *cmd)
{
	AddServerCommand_(cmd);
}

void CCSBotManager::AddServerCommands(void)
{
	AddServerCommands_();
}

void CCSBotManager::RestartRound(void)
{
	RestartRound_();
}

void CCSBotManager::StartFrame(void)
{
	StartFrame_();
}

void CCSBotManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	OnEvent_(event, entity, other);
}

unsigned int CCSBotManager::GetPlayerPriority(CBasePlayer *player) const
{
	return GetPlayerPriority_(player);
}

bool CCSBotManager::IsImportantPlayer(CBasePlayer *player)
{
	return IsImportantPlayer_(player);
}

#endif // HOOK_GAMEDLL
