#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//static char mp_com_token[1500];
cvar_t *sv_clienttrace;

#else

//char mp_com_token[1500];
cvar_t *sv_clienttrace;

#endif // HOOK_GAMEDLL

CCStrikeGameMgrHelper g_GameMgrHelper;
CHalfLifeMultiplay *g_pMPGameRules;

//void info_map_parameters(entvars_t *pev)

/* <1153e2> ../cstrike/dlls/multiplay_gamerules.cpp:92 */
bool IsBotSpeaking(void)
{
//	{
//		int i;                                                //    94
//		{
//			class CBasePlayer *pPlayer;                  //    96
//			{
//				class CCSBot *pBot;                  //    99
//			}
//		}
//	}
}

/* <1116dd> ../cstrike/dlls/multiplay_gamerules.cpp:111 */
NOBODY void SV_Continue_f(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //   113
//		{
//			int i;                                        //   121
//			{
//				class CBasePlayer *pPlayer;          //   123
//			}
//		}
//	}
}

/* <112860> ../cstrike/dlls/multiplay_gamerules.cpp:133 */
NOBODY void SV_Tutor_Toggle_f(void)
{
}

/* <11538f> ../cstrike/dlls/multiplay_gamerules.cpp:139 */
NOBODY void SV_Career_Restart_f(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //   141
//		IsCareer(CHalfLifeMultiplay *const this);  //   142
//	}
}

/* <111695> ../cstrike/dlls/multiplay_gamerules.cpp:149 */
NOBODY void SV_Career_EndRound_f(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //   151
//		{
//			class CBasePlayer *localPlayer;              //   154
//			{
//				int i;                                //   160
//				{
//					class CBasePlayer *player;   //   162
//				}
//			}
//		}
//	}
}

/* <1145dd> ../cstrike/dlls/multiplay_gamerules.cpp:173 */
NOBODY bool CHalfLifeMultiplay::IsInCareerRound(void)
{
	if (m_fTeamCount)
		return false;

	if (m_fCareerRoundMenuTime)
		return false;

	if (m_fCareerMatchMenuTime)
		return false;

	return true;
}

/* <110ba1> ../cstrike/dlls/multiplay_gamerules.cpp:180 */
NOBODY void SV_CareerAddTask_f(void)
{
//	{
//		const char *taskName;                               //   187
//		const char *weaponName;                             //   188
//		int reps;                                             //   189
//		bool mustLive;                                        //   190
//		bool crossRounds;                                     //   191
//		bool isComplete;                                      //   192
//	}
}

/* <111640> ../cstrike/dlls/multiplay_gamerules.cpp:213 */
NOBODY void SV_CareerMatchLimit_f(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //   219
//	}
}

/* <114600> ../cstrike/dlls/multiplay_gamerules.cpp:227 */
NOBODY void CHalfLifeMultiplay::SetCareerMatchLimit(int minWins, int winDifference)
{
//	IsCareer(CHalfLifeMultiplay *const this);  //   229
}

/* <114650> ../cstrike/dlls/multiplay_gamerules.cpp:238 */
BOOL CHalfLifeMultiplay::IsCareer(void)
{
	return IS_CAREER_MATCH();
}

/* <113e08> ../cstrike/dlls/multiplay_gamerules.cpp:263 */
NOBODY void CMapInfo::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   265
//	FStrEq(const char *sz1,
//		const char *sz2);  //   270
//	atoi(const char *__nptr);  //   272
//	KeyValue(CMapInfo *const this,
//		KeyValueData *pkvd);  //   263
}

/* <112879> ../cstrike/dlls/multiplay_gamerules.cpp:280 */
NOBODY void CMapInfo::Spawn_(void)
{
}

/* <114673> ../cstrike/dlls/multiplay_gamerules.cpp:288 */
//void info_map_parameters(entvars_t *pev)
//{
//	GetClassPtr<CMapInfo>(CMapInfo *a);  //   288
//}

/* <11474f> ../cstrike/dlls/multiplay_gamerules.cpp:331 */
NOBODY void Broadcast(const char *sentence)
{
//	{
//		char text;                                            //   333
//	}
}

/* <111767> ../cstrike/dlls/multiplay_gamerules.cpp:348 */
char *GetTeam(int teamNo)
{
	switch (teamNo)
	{
		case TERRORIST:
			return "TERRORIST";
		case CT:
			return "CT";
		case SPECTATOR:
			return "SPECTATOR";
		default:
			break;
	}
	return "";
}

/* <114805> ../cstrike/dlls/multiplay_gamerules.cpp:364 */
NOBODY void EndRoundMessage(const char *sentence, int event)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //   366
//		char *team;                                          //   368
//		const char *message;                                //   369
//		int teamTriggered;                                    //   370
//	}
}

/* <1128a1> ../cstrike/dlls/multiplay_gamerules.cpp:419 */
NOBODY void ReadMultiplayCvars(CHalfLifeMultiplay *mp)
{
}

/* <11492c> ../cstrike/dlls/multiplay_gamerules.cpp:479 */
NOBODY CHalfLifeMultiplay::CHalfLifeMultiplay(void)
{
	m_VoiceGameMgr.Init(&g_GameMgrHelper, gpGlobals->maxClients);
	RefreshSkillData();

	m_flIntermissionEndTime = 0;
	m_flIntermissionStartTime = 0;
	m_fTeamCount = 0;
	m_iAccountCT = 0;
	m_iAccountTerrorist = 0;
	m_iHostagesRescued = 0;
	m_iRoundWinStatus = 0;
	m_iNumCTWins = 0;
	m_iNumTerroristWins = 0;
	m_pVIP = NULL;
	m_iNumCT = 0;
	m_iNumTerrorist = 0;
	m_iNumSpawnableCT = 0;
	m_iNumSpawnableTerrorist = 0;
	m_bMapHasCameras = 2;
	g_fGameOver = FALSE;

	m_iLoserBonus = 1400;
	m_iNumConsecutiveCTLoses = 0;
	m_iNumConsecutiveTerroristLoses = 0;
	m_iC4Guy = 0;
	m_bBombDefused = false;
	m_bTargetBombed = false;
	m_bFreezePeriod = TRUE;
	m_bLevelInitialized = false;
	m_tmNextPeriodicThink = 0;
	m_bFirstConnected = 0;
	m_bCompleteReset = false;
	m_flRequiredEscapeRatio = 0.5;
	m_iNumEscapers = 0;
	m_bCTCantBuy = false;
	m_bTCantBuy = false;
	m_flBombRadius = 500.0;
	m_iTotalGunCount = 0;
	m_iTotalGrenadeCount = 0;
	m_iTotalArmourCount = 0;
	m_iConsecutiveVIP = 0;
	m_iUnBalancedRounds = 0;
	m_iNumEscapeRounds = 0;
	m_bRoundTerminating = false;

	g_iHostageNumber = 0;

	m_bBombDropped = FALSE;
	m_iMaxRounds = (int)CVAR_GET_FLOAT("mp_maxrounds");

	if (m_iMaxRounds < 0)
	{
		m_iMaxRounds = 0;
		CVAR_SET_FLOAT("mp_maxrounds", 0);
	}

	m_iTotalRoundsPlayed = 0;
	m_iMaxRoundsWon = (int)CVAR_GET_FLOAT("mp_winlimit");

	if (m_iMaxRoundsWon < 0)
	{
		m_iMaxRoundsWon = 0;
		CVAR_SET_FLOAT("mp_winlimit", 0);
	}

	memset(m_iMapVotes, 0, sizeof(m_iMapVotes));

	m_iLastPick = 1;
	m_bMapHasEscapeZone = false;
	m_iMapHasVIPSafetyZone = 0;
	m_bMapHasBombZone = false;
	m_bMapHasRescueZone = false;
	m_iStoredSpectValue = (int)allow_spectators.value;

	for (int j = 0; j < MAX_VIP_QUEUES; j++)
		VIPQueue[ j ] = NULL;

	CVAR_SET_FLOAT("cl_himodels", 0);
	ReadMultiplayCvars(this);

	m_iIntroRoundTime += 2;
	m_fMaxIdlePeriod = m_iRoundTime * 2;

	float flAutoKickIdle = CVAR_GET_FLOAT("mp_autokick_timeout");
	if (flAutoKickIdle > 0.0)
		m_fMaxIdlePeriod = flAutoKickIdle;

	m_bInCareerGame = false;
	m_iRoundTimeSecs = m_iIntroRoundTime;

	if (IS_DEDICATED_SERVER())
	{
		CVAR_SET_FLOAT("pausable", 0);
	}
	else
	{
		if (IsCareer())
		{
			CVAR_SET_FLOAT("pausable", 1);
			CVAR_SET_FLOAT("sv_aim", 0);
			CVAR_SET_FLOAT("sv_maxspeed", 322);
			CVAR_SET_FLOAT("sv_cheats", 0);
			CVAR_SET_FLOAT("mp_windifference", 2);

			m_bInCareerGame = true;
			UTIL_LogPrintf("Career Start\n");
		}
		else
		{
			CVAR_SET_FLOAT("pausable", 0);

			const char *lservercfgfile = CVAR_GET_STRING("lservercfgfile");

			if (lservercfgfile && *lservercfgfile)
			{
				char szCommand[256];
				ALERT(at_console, "Executing listen server config file\n");
				Q_sprintf(szCommand, "exec %s\n", lservercfgfile);
				SERVER_COMMAND(szCommand);
			}
		}
	}

	m_fRoundCount = 0;
	m_fIntroRoundCount = 0;

	InstallBotControl();
	InstallHostageManager();

	m_bSkipSpawn = m_bInCareerGame;

	static bool installedCommands = false;

	if (!installedCommands)
	{
		if (UTIL_IsGame("czero"))
		{
#if defined(HOOK_GAMEDLL) && !defined(REGAMEDLL_UNIT_TESTS)
			ADD_SERVER_COMMAND("career_continue", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z13SV_Continue_fv", (void *)SV_Continue_f));
			ADD_SERVER_COMMAND("career_matchlimit", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z21SV_CareerMatchLimit_fv", (void *)SV_CareerMatchLimit_f));
			ADD_SERVER_COMMAND("career_add_task", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z18SV_CareerAddTask_fv", (void *)SV_CareerAddTask_f));
			ADD_SERVER_COMMAND("career_endround", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z20SV_Career_EndRound_fv", (void *)SV_Career_EndRound_f));
			ADD_SERVER_COMMAND("career_restart", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z19SV_Career_Restart_fv", (void *)SV_Career_Restart_f));
			ADD_SERVER_COMMAND("tutor_toggle", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z17SV_Tutor_Toggle_fv", (void *)SV_Tutor_Toggle_f));
#else
			ADD_SERVER_COMMAND("career_continue", SV_Continue_f);
			ADD_SERVER_COMMAND("career_matchlimit", SV_CareerMatchLimit_f);
			ADD_SERVER_COMMAND("career_add_task", SV_CareerAddTask_f);
			ADD_SERVER_COMMAND("career_endround", SV_Career_EndRound_f);
			ADD_SERVER_COMMAND("career_restart", SV_Career_Restart_f);
			ADD_SERVER_COMMAND("tutor_toggle", SV_Tutor_Toggle_f);
#endif // HOOK_GAMEDLL
		}

#if defined(HOOK_GAMEDLL) && !defined(REGAMEDLL_UNIT_TESTS)
		ADD_SERVER_COMMAND("perf_test", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z15loopPerformancev", (void *)loopPerformance));
		ADD_SERVER_COMMAND("print_ent", (xcommand_t)GetOriginalFuncAddrOrDefault("_Z13printEntitiesv", (void *)printEntities));
#else
		ADD_SERVER_COMMAND("perf_test", loopPerformance);
		ADD_SERVER_COMMAND("print_ent", printEntities);
#endif // HOOK_GAMEDLL

		installedCommands = true;
	}

	m_fCareerRoundMenuTime = 0;
	m_fCareerMatchMenuTime = 0;
	m_iCareerMatchWins = 0;

	m_iRoundWinDifference = (int)CVAR_GET_FLOAT("mp_windifference");
	CCareerTaskManager::Create();

	if (m_iRoundWinDifference < 1)
	{
		m_iRoundWinDifference = 1;
		CVAR_SET_FLOAT("mp_windifference", 1);
	}

	sv_clienttrace = CVAR_GET_POINTER("sv_clienttrace");
	InstallTutor(CVAR_GET_POINTER("tutor_enable") != NULL);

	g_pMPGameRules = this;
}

/* <113b92> ../cstrike/dlls/multiplay_gamerules.cpp:678 */
void CHalfLifeMultiplay::RefreshSkillData_(void)
{
	CGameRules::RefreshSkillData();

	gSkillData.plrDmg9MM = 12;
	gSkillData.plrDmgMP5 = 12;
	gSkillData.suitchargerCapacity = 30;
	gSkillData.plrDmg357 = 40;
	gSkillData.plrDmgM203Grenade = 100;
	gSkillData.plrDmgBuckshot = 20;
	gSkillData.plrDmgCrossbowClient = 20;
	gSkillData.plrDmgRPG = 120;
}

/* <113b51> ../cstrike/dlls/multiplay_gamerules.cpp:713 */
void CHalfLifeMultiplay::RemoveGuns_(void)
{
	CBaseEntity *toremove = NULL;

	while ((toremove = UTIL_FindEntityByClassname(toremove, "weaponbox")) != NULL)
		((CWeaponBox *)toremove)->Kill();

	toremove = NULL;

	while ((toremove = UTIL_FindEntityByClassname(toremove, "weapon_shield")) != NULL)
	{
		toremove->SetThink(&CBaseEntity::SUB_Remove);
		//toremove->SetTouch(NULL); // TODO: this not exists in IDA
		toremove->pev->nextthink = gpGlobals->time + 0.1;
	}
}

/* <1149e8> ../cstrike/dlls/multiplay_gamerules.cpp:733 */
NOBODY void CHalfLifeMultiplay::UpdateTeamScores(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   735
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   740
}

/* <113aee> ../cstrike/dlls/multiplay_gamerules.cpp:747 */
NOBODY void CHalfLifeMultiplay::CleanUpMap_(void)
{
//	{
//		class CBaseEntity *torestart;                        //   749
//		class CBaseEntity *toremove;                         //   750
//		int icount;                                           //   837
//	}
}

/* <118585> ../cstrike/dlls/multiplay_gamerules.cpp:862 */
NOBODY void CHalfLifeMultiplay::GiveC4_(void)
{
//	{
//		int iTeamCount;                                       //   864
//		int iTemp;                                            //   865
//		class CBaseEntity *pPlayer;                          //   866
//		class CBasePlayer *player;                           //   867
//		int humansPresent;                                    //   873
//		bool giveToHumans;                                    //   874
//		{
//			int i;                                        //   878
//			edict(CBaseEntity *const this);  //   882
//			FNullEnt(const edict_t *pent);  //   882
//		}
//		edict(CBaseEntity *const this);  //   906
//		FNullEnt(const edict_t *pent);  //   906
//		IsThereABomber(CHalfLifeMultiplay *const this);  //   941
//		edict(CBaseEntity *const this);  //   949
//		FNullEnt(const edict_t *pent);  //   949
//		edict(CBaseEntity *const this);  //   930
//		edict(CBaseEntity *const this);  //   930
//		edict(CBaseEntity *const this);  //   968
//		edict(CBaseEntity *const this);  //   968
//	}
}

/* <11541f> ../cstrike/dlls/multiplay_gamerules.cpp:981 */
inline void TerminateRound(float tmDelay, int iWinStatus)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //   983
//	}
}

/* <114a6a> ../cstrike/dlls/multiplay_gamerules.cpp:995 */
NOBODY void CHalfLifeMultiplay::QueueCareerRoundEndMenu(float tmDelay, int iWinStatus)
{
//	{
//		bool humansAreCTs;                                    //  1000
//		{
//			class CBaseEntity *hostage;                  //  1005
//			int numHostagesInMap;                         //  1006
//			int numHostagesFollowingHumans;               //  1007
//			int numHostagesAlive;                         //  1008
//			{
//				class CHostage *pHostage;            //  1014
//				{
//					class CBasePlayer *pLeader;  //  1017
//					GetLeader(CHostage *const this);  //  1017
//					IsFollowingSomeone(CHostage *const this);  //  1018
//				}
//			}
//		}
//		{
//			bool canCTsWin;                               //  1060
//			bool canTsWin;                                //  1062
//		}
//	}
}

/* <117750> ../cstrike/dlls/multiplay_gamerules.cpp:1084 */
NOBODY void CHalfLifeMultiplay::CheckWinConditions_(void)
{
//	{
//		class CBaseEntity *pPlayer;                          //  1086
//		class CBasePlayer *player;                           //  1087
//		int NumDeadCT;                                        //  1088
//		int NumDeadTerrorist;                                 //  1088
//		int NumAliveTerrorist;                                //  1088
//		int NumAliveCT;                                       //  1088
//		int NumSpawnableHumans;                               //  1089
//		int NumHumans;                                        //  1090
//		BOOL bNeededPlayers;                                  //  1091
//		class CBaseEntity *hostage;                          //  1454
//		int iHostages;                                        //  1455
//		bool bHostageAlive;                                   //  1456
//		edict(CBaseEntity *const this);  //  1106
//		FNullEnt(const edict_t *pent);  //  1106
//		IsCareer(CHalfLifeMultiplay *const this);  //  1175
//		{
//			class CBasePlayer *player;                   //  1177
//		}
//		IsCareer(CHalfLifeMultiplay *const this);  //  1192
//		TerminateRound(float tmDelay,
//				int iWinStatus);  //  1194
//		TerminateRound(float tmDelay,
//				int iWinStatus);  //  1199
//		{
//			float flEscapeRatio;                          //  1266
//			Broadcast(const char *sentence);  //  1303
//			UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1310
//			Broadcast(const char *sentence);  //  1272
//			UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1279
//			Broadcast(const char *sentence);  //  1287
//			UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1294
//		}
//		Broadcast(const char *sentence);  //  1343
//		{
//			class CGrenade *C4;                          //  1368
//			class CBaseEntity *temp;                     //  1369
//			BOOL nowin;                                   //  1370
//			TerminateRound(float tmDelay,
//					int iWinStatus);  //  1410
//			Broadcast(const char *sentence);  //  1395
//		}
//		Broadcast(const char *sentence);  //  1425
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1436
//		TerminateRound(float tmDelay,
//				int iWinStatus);  //  1440
//		Broadcast(const char *sentence);  //  1447
//		TerminateRound(float tmDelay,
//				int iWinStatus);  //  1448
//		Broadcast(const char *sentence);  //  1473
//		IsCareer(CHalfLifeMultiplay *const this);  //  1488
//		TerminateRound(float tmDelay,
//				int iWinStatus);  //  1493
//		Broadcast(const char *sentence);  //  1325
//		TerminateRound(float tmDelay,
//				int iWinStatus);  //  1337
//		Broadcast(const char *sentence);  //  1242
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1249
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1333
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1354
//		Broadcast(const char *sentence);  //  1214
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1221
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1224
//		edict(CBaseEntity *const this);  //  1227
//		ENTINDEX(edict_t *pEdict);  //  1227
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1481
//	}
}

/* <117336> ../cstrike/dlls/multiplay_gamerules.cpp:1499 */
NOBODY void CHalfLifeMultiplay::SwapAllPlayers(void)
{
//	{
//		class CBasePlayer *player;                           //  1501
//		class CBaseEntity *pPlayer;                          //  1502
//		int iTemp;                                            //  1516
//		edict(CBaseEntity *const this);  //  1505
//		FNullEnt(const edict_t *pent);  //  1505
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1522
//	}
}

/* <1171eb> ../cstrike/dlls/multiplay_gamerules.cpp:1525 */
NOBODY void CHalfLifeMultiplay::BalanceTeams(void)
{
//	{
//		int iTeamToSwap;                                      //  1527
//		int iNumToSwap;                                       //  1528
//		class CBasePlayer *player;                           //  1573
//		class CBasePlayer *toSwap;                           //  1574
//		class CBaseEntity *pPlayer;                          //  1575
//		int iHighestUserID;                                   //  1578
//		{
//			int iDesiredNumCT;                            //  1532
//			int iDesiredNumTerrorist;                     //  1532
//		}
//		{
//			int i;                                        //  1580
//			edict(CBaseEntity *const this);  //  1586
//			FNullEnt(const edict_t *pent);  //  1586
//			edict(CBaseEntity *const this);  //  1591
//			edict(CBaseEntity *const this);  //  1593
//		}
//	}
}

/* <113158> ../cstrike/dlls/multiplay_gamerules.cpp:1608 */
NOBODY void CHalfLifeMultiplay::CheckMapConditions_(void)
{
}

/* <11745e> ../cstrike/dlls/multiplay_gamerules.cpp:1676 */
NOBODY void CHalfLifeMultiplay::RestartRound_(void)
{
//	{
//		float flAutoKickIdle;                                 //  1804
//		class CMapInfo *mi;                                  //  1815
//		class CBaseEntity *hostage;                          //  1896
//		class CHostage *temp;                                //  1897
//		int acct_tmp;                                         //  1903
//		class CBaseEntity *pPlayer;                          //  1965
//		class CBasePlayer *player;                           //  1966
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1711
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1717
//		UpdateTeamScores(CHalfLifeMultiplay *const this);  //  1782
//		{
//			int i;                                        //  1786
//			{
//				class CBasePlayer *plr;              //  1788
//				FNullEnt(entvars_t *pev);  //  1790
//			}
//		}
//		edict(CBaseEntity *const this);  //  1985
//		FNullEnt(const edict_t *pent);  //  1985
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1701
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1704
//	}
}

/* <114d20> ../cstrike/dlls/multiplay_gamerules.cpp:2097 */
NOBODY BOOL CHalfLifeMultiplay::IsThereABomb(void)
{
//	{
//		class CGrenade *pC4;                                 //  2099
//		class CBaseEntity *pWeaponC4;                        //  2100
//		BOOL bFoundBomb;                                      //  2101
//	}
}

/* <114ca3> ../cstrike/dlls/multiplay_gamerules.cpp:2073 */
NOBODY BOOL CHalfLifeMultiplay::IsThereABomber(void)
{
//	{
//		class CBasePlayer *pPlayer;                          //  2075
//		edict(CBaseEntity *const this);  //  2079
//		FNullEnt(const edict_t *pent);  //  2079
//	}
}

/* <114d83> ../cstrike/dlls/multiplay_gamerules.cpp:2129 */
NOBODY BOOL CHalfLifeMultiplay::TeamFull(int team_id)
{
}

/* <114dbb> ../cstrike/dlls/multiplay_gamerules.cpp:2144 */
NOBODY BOOL CHalfLifeMultiplay::TeamStacked(int newTeam_id, int curTeam_id)
{
}

/* <114e2b> ../cstrike/dlls/multiplay_gamerules.cpp:2214 */
NOBODY void CHalfLifeMultiplay::StackVIPQueue(void)
{
//	{
//		int i;                                                //  2216
//	}
}

/* <114e63> ../cstrike/dlls/multiplay_gamerules.cpp:2232 */
NOBODY bool CHalfLifeMultiplay::IsVIPQueueEmpty(void)
{
//	{
//		class CBasePlayer *toCheck;                          //  2234
//		{
//			int i;                                        //  2238
//		}
//		StackVIPQueue(CHalfLifeMultiplay *const this);  //  2249
//	}
}

/* <114eea> ../cstrike/dlls/multiplay_gamerules.cpp:2257 */
NOBODY bool CHalfLifeMultiplay::AddToVIPQueue(CBasePlayer *toAdd)
{
//	{
//		int i;                                                //  2265
//	}
//	{
//		int j;                                                //  2274
//		StackVIPQueue(CHalfLifeMultiplay *const this);  //  2279
//	}
}

/* <114f80> ../cstrike/dlls/multiplay_gamerules.cpp:2290 */
NOBODY void CHalfLifeMultiplay::ResetCurrentVIP(void)
{
//	{
//		char *infobuffer;                                    //  2292
//		int numSkins;                                         //  2294
//		edict(CBaseEntity *const this);  //  2292
//		entindex(CBaseEntity *const this);  //  2327
//		entindex(CBaseEntity *const this);  //  2316
//		entindex(CBaseEntity *const this);  //  2308
//		entindex(CBaseEntity *const this);  //  2312
//		entindex(CBaseEntity *const this);  //  2322
//	}
}

/* <11706f> ../cstrike/dlls/multiplay_gamerules.cpp:2335 */
NOBODY void CHalfLifeMultiplay::PickNextVIP(void)
{
//	{
//		int i;                                                //  2343
//		StackVIPQueue(CHalfLifeMultiplay *const this);  //  2351
//	}
//	{
//		int iCount;                                           //  2365
//		class CBaseEntity *pPlayer;                          //  2367
//		class CBasePlayer *player;                           //  2368
//		class CBasePlayer *pLastPlayer;                      //  2369
//		edict(CBaseEntity *const this);  //  2372
//		FNullEnt(const edict_t *pent);  //  2372
//	}
//	{
//		class CBaseEntity *pPlayer;                          //  2404
//		class CBasePlayer *player;                           //  2405
//		edict(CBaseEntity *const this);  //  2408
//		FNullEnt(const edict_t *pent);  //  2408
//	}
}

/* <115458> ../cstrike/dlls/multiplay_gamerules.cpp:2435 */
NOBODY void CHalfLifeMultiplay::Think_(void)
{
//	{
//		int time_remaining;                                   //  2437
//		float fTimeLimit;                                     //  2495
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  2456
//		{
//			int time;                                     //  2472
//			IsCareer(CHalfLifeMultiplay *const this);  //  2481
//		}
//		IsCareer(CHalfLifeMultiplay *const this);  //  2504
//		IsBotSpeaking(void);  //  2511
//		TimeRemaining(CHalfLifeMultiplay *const this);  //  2594
//		{
//			char CT_sentence;                             //  2602
//			char T_sentence;                              //  2603
//			bool bCTPlayed;                               //  2649
//			bool bTPlayed;                                //  2650
//			{
//				int i;                                //  2652
//				{
//					class CBasePlayer *plr;      //  2654
//				}
//			}
//		}
//		{
//			class CGrenade *C4;                          //  2691
//			float flEndRoundTime;                         //  2692
//			Broadcast(const char *sentence);  //  2710
//			TerminateRound(float tmDelay,
//					int iWinStatus);  //  2715
//			UpdateTeamScores(CHalfLifeMultiplay *const this);  //  2716
//			Broadcast(const char *sentence);  //  2721
//			TerminateRound(float tmDelay,
//					int iWinStatus);  //  2726
//			UpdateTeamScores(CHalfLifeMultiplay *const this);  //  2727
//			TerminateRound(float tmDelay,
//					int iWinStatus);  //  2747
//			Broadcast(const char *sentence);  //  2732
//			TerminateRound(float tmDelay,
//					int iWinStatus);  //  2736
//			UpdateTeamScores(CHalfLifeMultiplay *const this);  //  2737
//		}
//		IsCareer(CHalfLifeMultiplay *const this);  //  2758
//		{
//			bool isBotSpeaking;                           //  2760
//			{
//				bool canCTsWin;                       //  2771
//				bool canTsWin;                        //  2773
//			}
//			{
//				int i;                                //  2801
//				{
//					class CBasePlayer *pPlayer;  //  2803
//					MESSAGE_BEGIN(int msg_dest,
//							int msg_type,
//							const float *pOrigin,
//							entvars_t *ent);  //  2807
//				}
//			}
//			IsBotSpeaking(void);  //  2763
//		}
//		{
//			class CBaseEntity *ent;                      //  2840
//		}
//		{
//			int iRestartDelay;                            //  2860
//			{
//				class CHalfLifeMultiplay *mp;        //  2872
//			}
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  2587
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  2520
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  2527
//	}
}

/* <115189> ../cstrike/dlls/multiplay_gamerules.cpp:2922 */
NOBODY bool CHalfLifeMultiplay::HasRoundTimeExpired(void)
{
//	TimeRemaining(CHalfLifeMultiplay *const this);  //  2925
//	IsBombPlanted(CHalfLifeMultiplay *const this);  //  2929
}

/* <1151f4> ../cstrike/dlls/multiplay_gamerules.cpp:2945 */
NOBODY bool CHalfLifeMultiplay::IsBombPlanted(void)
{
//	{
//		class CGrenade *bomb;                                //  2950
//	}
}

/* <115229> ../cstrike/dlls/multiplay_gamerules.cpp:2971 */
NOBODY void CHalfLifeMultiplay::MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound(int iTeam)
{
//	{
//		int i;                                                //  2973
//		{
//			class CBasePlayer *player;                   //  2975
//			FNullEnt(entvars_t *pev);  //  2977
//		}
//	}
}

/* <1152e2> ../cstrike/dlls/multiplay_gamerules.cpp:2987 */
NOBODY void CHalfLifeMultiplay::CareerRestart(void)
{
//	{
//		int i;                                                //  3004
//		{
//			class CBasePlayer *player;                   //  3006
//			FNullEnt(entvars_t *pev);  //  3008
//		}
//	}
}

/* <1128cb> ../cstrike/dlls/multiplay_gamerules.cpp:3017 */
BOOL CHalfLifeMultiplay::IsMultiplayer_(void)
{
	return TRUE;
}

/* <1128f3> ../cstrike/dlls/multiplay_gamerules.cpp:3024 */
NOBODY BOOL CHalfLifeMultiplay::IsDeathmatch_(void)
{
}

/* <11291b> ../cstrike/dlls/multiplay_gamerules.cpp:3031 */
NOBODY BOOL CHalfLifeMultiplay::IsCoOp_(void)
{
	return TRUE;
}

/* <113fcf> ../cstrike/dlls/multiplay_gamerules.cpp:3038 */
BOOL CHalfLifeMultiplay::FShouldSwitchWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	if (!pWeapon->CanDeploy())
		return FALSE;

	if (!pPlayer->m_pActiveItem)
		return TRUE;

	if (!pPlayer->m_iAutoWepSwitch)
		return FALSE;

	if (!pPlayer->m_pActiveItem->CanHolster())
		return FALSE;

	if (pWeapon->iWeight() > pPlayer->m_pActiveItem->iWeight())
		return TRUE;

	return FALSE;
}

/* <113eec> ../cstrike/dlls/multiplay_gamerules.cpp:3071 */
BOOL CHalfLifeMultiplay::GetNextBestWeapon_(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	if (!pCurrentWeapon->CanHolster())
		return FALSE;

	int iBestWeight = -1;
	CBasePlayerItem *pBest = NULL;

	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		CBasePlayerItem *pCheck = pPlayer->m_rgpPlayerItems[i];
		while (pCheck)
		{
			if (pCheck->iWeight() > iBestWeight && pCheck != pCurrentWeapon && pCheck->CanDeploy())
			{
				iBestWeight = pCheck->iWeight();
				pBest = pCheck;
			}
			pCheck = pCheck->m_pNext;
		}
	}
	if (pBest)
	{
		pPlayer->SwitchWeapon(pBest);
		return TRUE;
	}
	return FALSE;
}

NOBODY BOOL CHalfLifeMultiplay::ClientCommand_(CBasePlayer *pPlayer, const char *pcmd)
{
	return FALSE;
}

/* <113aa5> ../cstrike/dlls/multiplay_gamerules.cpp:3132 */
NOBODY BOOL CHalfLifeMultiplay::ClientCommand_DeadOrAlive_(CBasePlayer *pPlayer, const char *pcmd)
{
}

/* <113a3c> ../cstrike/dlls/multiplay_gamerules.cpp:3145 */
NOBODY BOOL CHalfLifeMultiplay::ClientConnected_(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
}

/* <11298b> ../cstrike/dlls/multiplay_gamerules.cpp:3156 */
NOBODY void CHalfLifeMultiplay::UpdateGameMode_(CBasePlayer *pPlayer)
{
//	edict(CBaseEntity *const this);  //  3158
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  3158
}

/* <11642b> ../cstrike/dlls/multiplay_gamerules.cpp:3163 */
NOBODY void CHalfLifeMultiplay::InitHUD_(CBasePlayer *pl)
{
//	{
//		int i;                                                //  3207
//		edict(CBaseEntity *const this);  //  3168
//		edict(CBaseEntity *const this);  //  3168
//		edict(CBaseEntity *const this);  //  3181
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3181
//		edict(CBaseEntity *const this);  //  3182
//		ENTINDEX(edict_t *pEdict);  //  3182
//		edict(CBaseEntity *const this);  //  3189
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3189
//		IsCareer(CHalfLifeMultiplay *const this);  //  3193
//		edict(CBaseEntity *const this);  //  3196
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3196
//		{
//			class CBasePlayer *plr;                      //  3211
//			edict(CBaseEntity *const this);  //  3215
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3215
//		}
//		edict(CBaseEntity *const this);  //  3226
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3226
//		edict(CBaseEntity *const this);  //  3231
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3231
//		edict(CBaseEntity *const this);  //  3236
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3236
//		edict(CBaseEntity *const this);  //  3240
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3240
//		{
//			class CBasePlayer *plr;                      //  3255
//			entindex(CBaseEntity *const this);  //  3283
//			edict(CBaseEntity *const this);  //  3259
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3259
//			entindex(CBaseEntity *const this);  //  3260
//			edict(CBaseEntity *const this);  //  3287
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3287
//			entindex(CBaseEntity *const this);  //  3288
//		}
//		{
//			class CBaseEntity *pWeaponC4;                //  3301
//			edict(CBaseEntity *const this);  //  3306
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3306
//		}
//		edict(CBaseEntity *const this);  //  3175
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3175
//		edict(CBaseEntity *const this);  //  3248
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3248
//	}
}

/* <1137c1> ../cstrike/dlls/multiplay_gamerules.cpp:3318 */
NOBODY void CHalfLifeMultiplay::ClientDisconnected_(edict_t *pClient)
{
//	{
//		class CBasePlayer *pPlayer;                          //  3322
//		Instance(edict_t *pent);  //  3322
//		{
//			char *team;                                  //  3389
//			class CBasePlayer *client;                   //  3403
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3365
//			ENTINDEX(edict_t *pEdict);  //  3366
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3373
//			ENTINDEX(edict_t *pEdict);  //  3374
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3378
//			ENTINDEX(edict_t *pEdict);  //  3379
//			GetTeam(int teamNo);  //  3389
//			edict(CBaseEntity *const this);  //  3395
//			edict(CBaseEntity *const this);  //  3395
//			edict(CBaseEntity *const this);  //  3404
//			FNullEnt(const edict_t *pent);  //  3404
//			{
//				int iMode;                            //  3415
//			}
//		}
//	}
}

/* <112a05> ../cstrike/dlls/multiplay_gamerules.cpp:3428 */
NOBODY float CHalfLifeMultiplay::FlPlayerFallDamage_(CBasePlayer *pPlayer)
{
}

/* <112a3d> ../cstrike/dlls/multiplay_gamerules.cpp:3436 */
NOBODY BOOL CHalfLifeMultiplay::FPlayerCanTakeDamage_(CBasePlayer *pPlayer, CBaseEntity *pAttacker)
{
}

/* <11370c> ../cstrike/dlls/multiplay_gamerules.cpp:3454 */
NOBODY void CHalfLifeMultiplay::PlayerThink_(CBasePlayer *pPlayer)
{
//	{
//		class CBasePlayerWeapon *pWeapon;                    //  3476
//	}
//	{
//		int team;                                             //  3484
//		IsCareer(CHalfLifeMultiplay *const this);  //  3513
//	}
//	IsCareer(CHalfLifeMultiplay *const this);  //  3459
}

/* <113bcf> ../cstrike/dlls/multiplay_gamerules.cpp:3523 */
NOBODY void CHalfLifeMultiplay::PlayerSpawn_(CBasePlayer *pPlayer)
{
//	{
//		BOOL addDefault;                                      //  3525
//		class CBaseEntity *pWeaponEntity;                    //  3526
//	}
}

/* <113d74> ../cstrike/dlls/multiplay_gamerules.cpp:3553 */
NOBODY BOOL CHalfLifeMultiplay::FPlayerCanRespawn_(CBasePlayer *pPlayer)
{
//	FPlayerCanRespawn(CHalfLifeMultiplay *const this,
//				class CBasePlayer *pPlayer);  //  3553
}

/* <112a86> ../cstrike/dlls/multiplay_gamerules.cpp:3591 */
NOBODY float CHalfLifeMultiplay::FlPlayerSpawnTime_(CBasePlayer *pPlayer)
{
	return -1.0f;
}

/* <112abe> ../cstrike/dlls/multiplay_gamerules.cpp:3596 */
NOBODY BOOL CHalfLifeMultiplay::AllowAutoTargetCrosshair_(void)
{
	return FALSE;
}

/* <112ae6> ../cstrike/dlls/multiplay_gamerules.cpp:3619 */
NOBODY int CHalfLifeMultiplay::IPointsForKill_(CBasePlayer *pAttacker, CBasePlayer *pKilled)
{
}

/* <116cbd> ../cstrike/dlls/multiplay_gamerules.cpp:3627 */
NOBODY void CHalfLifeMultiplay::PlayerKilled_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
//	{
//		class CBasePlayer *peKiller;                         //  3644
//		class CBaseEntity *ktmp;                             //  3645
//		class CBaseEntity *ep;                               //  3751
//		edict(CBaseEntity *const this);  //  3642
//		Instance(entvars_t *pev);  //  3645
//		{
//			class CBasePlayer *pDriver;                  //  3650
//		}
//		{
//			class CBasePlayer *killer;                   //  3667
//			{
//				int iUserID;                          //  3685
//				edict(CBaseEntity *const this);  //  3685
//			}
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3708
//			edict(CBaseEntity *const this);  //  3711
//			ENTINDEX(edict_t *pEdict);  //  3711
//			ENTINDEX(edict_t *pEdict);  //  3712
//			edict(CBaseEntity *const this);  //  3720
//			edict(CBaseEntity *const this);  //  3720
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3742
//		edict(CBaseEntity *const this);  //  3743
//		ENTINDEX(edict_t *pEdict);  //  3743
//		Instance(entvars_t *pev);  //  3751
//		{
//			class CBasePlayer *PK;                       //  3754
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  3756
//			edict(CBaseEntity *const this);  //  3757
//			ENTINDEX(edict_t *pEdict);  //  3757
//		}
//	}
}

/* <113273> ../cstrike/dlls/multiplay_gamerules.cpp:3772 */
NOBODY void CHalfLifeMultiplay::DeathNotice_(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pevInflictor)
{
//	{
//		class CBaseEntity *Killer;                           //  3775
//		const char *killer_weapon_name;                     //  3777
//		int killer_index;                                     //  3778
//		char *tau;                                           //  3781
//		char *gluon;                                         //  3782
//		int iGotHeadshot;                                     //  3819
//		Instance(entvars_t *pev);  //  3775
//		ENTINDEX(edict_t *pEdict);  //  3786
//		{
//			class CBasePlayer *pPlayer;                  //  3793
//			Instance(entvars_t *pev);  //  3793
//			pszName(CBasePlayerItem *const this);  //  3797
//		}
//		{
//			class CBasePlayer *pPlayer;                  //  3856
//			char *VictimTeam;                            //  3858
//			char *KillerTeam;                            //  3859
//			Instance(entvars_t *pev);  //  3856
//			GetTeam(int teamNo);  //  3858
//			edict(CBaseEntity *const this);  //  3872
//		}
//		{
//			char *team;                                  //  3877
//			GetTeam(int teamNo);  //  3877
//			edict(CBaseEntity *const this);  //  3884
//		}
//		{
//			char *team;                                  //  3845
//			GetTeam(int teamNo);  //  3845
//			edict(CBaseEntity *const this);  //  3852
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3890
//		edict(CBaseEntity *const this);  //  3893
//		ENTINDEX(edict_t *pEdict);  //  3893
//		ENTINDEX(edict_t *pEdict);  //  3895
//		ENTINDEX(edict_t *pEdict);  //  3897
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  3829
//		edict(CBaseEntity *const this);  //  3831
//		ENTINDEX(edict_t *pEdict);  //  3831
//	}
}

/* <112b2e> ../cstrike/dlls/multiplay_gamerules.cpp:3916 */
void CHalfLifeMultiplay::PlayerGotWeapon_(CBasePlayer *pPlayer, class CBasePlayerItem *pWeapon)
{
	;
}

/* <112b76> ../cstrike/dlls/multiplay_gamerules.cpp:3924 */
NOBODY float CHalfLifeMultiplay::FlWeaponRespawnTime_(CBasePlayerItem *pWeapon)
{
}

/* <114058> ../cstrike/dlls/multiplay_gamerules.cpp:3938 */
NOBODY float CHalfLifeMultiplay::FlWeaponTryRespawn_(CBasePlayerItem *pWeapon)
{
//	iFlags(CBasePlayerItem *const this);  //  3940
//	FlWeaponTryRespawn(CHalfLifeMultiplay *const this,
//				class CBasePlayerItem *pWeapon);  //  3938
}

/* <112bae> ../cstrike/dlls/multiplay_gamerules.cpp:3956 */
NOBODY Vector CHalfLifeMultiplay::VecWeaponRespawnSpot_(CBasePlayerItem *pWeapon)
{
//	Vector(Vector *const this,
//		const Vector &v);  //  3958
}

/* <112c11> ../cstrike/dlls/multiplay_gamerules.cpp:3965 */
int CHalfLifeMultiplay::WeaponShouldRespawn_(CBasePlayerItem *pWeapon)
{
	if (pWeapon->pev->spawnflags & SF_NORESPAWN)
		return GR_WEAPON_RESPAWN_NO;

	return GR_WEAPON_RESPAWN_YES;
}

/* <11322b> ../cstrike/dlls/multiplay_gamerules.cpp:3979 */
NOBODY BOOL CHalfLifeMultiplay::CanHavePlayerItem_(CBasePlayer *pPlayer, CBasePlayerItem *pItem)
{
	return CGameRules::CanHavePlayerItem(pPlayer, pItem);
}

/* <112c49> ../cstrike/dlls/multiplay_gamerules.cpp:3986 */
BOOL CHalfLifeMultiplay::CanHaveItem_(CBasePlayer *pPlayer, CItem *pItem)
{
	return TRUE;
}

/* <112c91> ../cstrike/dlls/multiplay_gamerules.cpp:3993 */
void CHalfLifeMultiplay::PlayerGotItem_(CBasePlayer *pPlayer, CItem *pItem)
{
	;
}

/* <112cd9> ../cstrike/dlls/multiplay_gamerules.cpp:3999 */
int CHalfLifeMultiplay::ItemShouldRespawn_(CItem *pItem)
{
	if (pItem->pev->spawnflags & SF_NORESPAWN)
		return GR_ITEM_RESPAWN_NO;

	return GR_ITEM_RESPAWN_YES;
}

/* <112d11> ../cstrike/dlls/multiplay_gamerules.cpp:4013 */
float CHalfLifeMultiplay::FlItemRespawnTime_(CItem *pItem)
{
	return gpGlobals->time + ITEM_RESPAWN_TIME;
}

/* <112d49> ../cstrike/dlls/multiplay_gamerules.cpp:4022 */
Vector CHalfLifeMultiplay::VecItemRespawnSpot_(CItem *pItem)
{
	return pItem->pev->origin;
}

/* <112dac> ../cstrike/dlls/multiplay_gamerules.cpp:4029 */
NOBODY void CHalfLifeMultiplay::PlayerGotAmmo_(CBasePlayer *pPlayer, char *szName, int iCount)
{
}

/* <112e04> ../cstrike/dlls/multiplay_gamerules.cpp:4035 */
NOBODY BOOL CHalfLifeMultiplay::IsAllowedToSpawn_(CBaseEntity *pEntity)
{
}

/* <112e3c> ../cstrike/dlls/multiplay_gamerules.cpp:4045 */
int CHalfLifeMultiplay::AmmoShouldRespawn_(CBasePlayerAmmo *pAmmo)
{
	if (pAmmo->pev->spawnflags & SF_NORESPAWN)
		return GR_AMMO_RESPAWN_NO;

	return GR_AMMO_RESPAWN_YES;
}

/* <112e74> ../cstrike/dlls/multiplay_gamerules.cpp:4057 */
float CHalfLifeMultiplay::FlAmmoRespawnTime_(CBasePlayerAmmo *pAmmo)
{
	return gpGlobals->time + 20.0f;
}

/* <112eac> ../cstrike/dlls/multiplay_gamerules.cpp:4064 */
Vector CHalfLifeMultiplay::VecAmmoRespawnSpot_(CBasePlayerAmmo *pAmmo)
{
	return pAmmo->pev->origin;
}

/* <112f0f> ../cstrike/dlls/multiplay_gamerules.cpp:4071 */
NOBODY float CHalfLifeMultiplay::FlHealthChargerRechargeTime_(void)
{
}

/* <112f37> ../cstrike/dlls/multiplay_gamerules.cpp:4077 */
NOBODY float CHalfLifeMultiplay::FlHEVChargerRechargeTime_(void)
{
}

/* <112f5f> ../cstrike/dlls/multiplay_gamerules.cpp:4084 */
int CHalfLifeMultiplay::DeadPlayerWeapons_(CBasePlayer *pPlayer)
{
	return GR_PLR_DROP_GUN_ACTIVE;
}

/* <112f97> ../cstrike/dlls/multiplay_gamerules.cpp:4091 */
int CHalfLifeMultiplay::DeadPlayerAmmo_(CBasePlayer *pPlayer)
{
	return GR_PLR_DROP_AMMO_ACTIVE;
}

/* <1131d6> ../cstrike/dlls/multiplay_gamerules.cpp:4096 */
NOBODY edict_t *CHalfLifeMultiplay::GetPlayerSpawnSpot_(CBasePlayer *pPlayer)
{
//	{
//		edict_t *pentSpawnSpot;                              //  4098
//	}
}

/* <116c24> ../cstrike/dlls/multiplay_gamerules.cpp:4110 */
NOBODY int CHalfLifeMultiplay::PlayerRelationship_(CBasePlayer *pPlayer, CBaseEntity *pTarget)
{
//	{
//		class CBasePlayer *player;                           //  4118
//		class CBasePlayer *target;                           //  4119
//	}
}

/* <112fcf> ../cstrike/dlls/multiplay_gamerules.cpp:4128 */
BOOL CHalfLifeMultiplay::FAllowFlashlight_(void)
{
	static cvar_t *mp_flashlight = NULL;

	if (!mp_flashlight)
		mp_flashlight = CVAR_GET_POINTER("mp_flashlight");

	if (mp_flashlight)
		return mp_flashlight->value != 0;

	return FALSE;
}

/* <113012> ../cstrike/dlls/multiplay_gamerules.cpp:4145 */
NOBODY BOOL CHalfLifeMultiplay::FAllowMonsters_(void)
{
}

/* <114155> ../cstrike/dlls/multiplay_gamerules.cpp:4156 */
NOBODY void CHalfLifeMultiplay::GoToIntermission_(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  4161
//		int time;                                             //  4200
//	}
//	GoToIntermission(CHalfLifeMultiplay *const this);  //  4156
}

NOBODY void CHalfLifeMultiplay::ServerDeactivate_(void)
{
	if (IsCareer())
	{
		CVAR_SET_FLOAT("pausable", 0);
		CVAR_SET_FLOAT("mp_windifference", 1.0);
		UTIL_LogPrintf("Career End\n");
	}
}

/* <115c98> ../cstrike/dlls/multiplay_gamerules.cpp:4241 */
NOBODY void DestroyMapCycle(mapcycle_t *cycle)
{
//	{
//		mapcycle_item_t *p;                                  //  4243
//		mapcycle_item_t *n;                                  //  4243
//		mapcycle_item_t *start;                              //  4243
//	}
}

/* <115d30> ../cstrike/dlls/multiplay_gamerules.cpp:4271 */
NOBODY char *MP_COM_GetToken(void)
{
}

/* <115d4d> ../cstrike/dlls/multiplay_gamerules.cpp:4283 */
NOBODY char *MP_COM_Parse(char *data)
{
//	
//skipwhite:                                                            //  4295
//	{
//		int c;                                                //  4285
//		int len;                                              //  4286
//	}
}

/* <115db1> ../cstrike/dlls/multiplay_gamerules.cpp:4360 */
NOBODY int MP_COM_TokenWaiting(char *buffer)
{
//	{
//		char *p;                                             //  4362
//	}
}

/* <115e11> ../cstrike/dlls/multiplay_gamerules.cpp:4384 */
NOBODY int ReloadMapCycleFile(char *filename, mapcycle_t *cycle)
{
//	{
//		char szBuffer;                                        //  4386
//		char szMap;                                           //  4387
//		int length;                                           //  4388
//		char *pFileList;                                     //  4389
//		char *aFileList;                                     //  4390
//		int hasbuffer;                                        //  4391
//		class mapcycle_item_s *item;                         //  4392
//		class mapcycle_item_s *newlist;                      //  4392
//		class mapcycle_item_s *next;                         //  4392
//		MP_COM_TokenWaiting(char *buffer);  //  4410
//		{
//			char *s;                                     //  4424
//			atoi(const char *__nptr);  //  4440
//			atoi(const char *__nptr);  //  4447
//		}
//	}
}

/* <115f76> ../cstrike/dlls/multiplay_gamerules.cpp:4510 */
NOBODY int CountPlayers(void)
{
//	{
//		int num;                                              //  4512
//		{
//			int i;                                        //  4514
//			{
//				class CBaseEntity *pEnt;             //  4516
//			}
//		}
//	}
}

/* <116002> ../cstrike/dlls/multiplay_gamerules.cpp:4535 */
NOBODY void ExtractCommandString(char *s, char *szCommand)
{
//	{
//		char pkey;                                            //  4538
//		char value;                                           //  4539
//		char *o;                                             //  4541
//	}
}

/* <116b52> ../cstrike/dlls/multiplay_gamerules.cpp:4582 */
NOBODY void CHalfLifeMultiplay::ResetAllMapVotes(void)
{
//	{
//		int j;                                                //  4584
//		class CBaseEntity *pTempEntity;                      //  4585
//		class CBasePlayer *pTempPlayer;                      //  4586
//	}
}

/* <11624e> ../cstrike/dlls/multiplay_gamerules.cpp:4608 */
NOBODY int GetMapCount(void)
{
//	{
//		mapcycle_t mapcycle2;                                 //  4610
//		char *mapcfile;                                      //  4611
//		class mapcycle_item_s *item;                         //  4612
//		int iCount;                                           //  4613
//		int iDone;                                            //  4613
//		DestroyMapCycle(mapcycle_t *cycle);  //  4615
//	}
}

/* <1187d2> ../cstrike/dlls/multiplay_gamerules.cpp:4629 */
NOBODY void CHalfLifeMultiplay::DisplayMaps(CBasePlayer *player, int iVote)
{
//	{
//		mapcycle_t mapcycle2;                                 //  4631
//		char *mapcfile;                                      //  4632
//		class mapcycle_item_s *item;                         //  4633
//		int iCount;                                           //  4634
//		char *pszNewMap;                                     //  4635
//		int done;                                             //  4640
//		DestroyMapCycle(mapcycle_t *cycle);  //  4637
//		ResetAllMapVotes(CHalfLifeMultiplay *const this);  //  4691
//	}
}

/* <11895b> ../cstrike/dlls/multiplay_gamerules.cpp:4702 */
NOBODY void CHalfLifeMultiplay::ProcessMapVote(CBasePlayer *player, int iVote)
{
//	{
//		class CBaseEntity *pTempEntity;                      //  4704
//		class CBasePlayer *pTempPlayer;                      //  4705
//		int iValidVotes;                                      //  4706
//		int iRequiredVotes;                                   //  4707
//		int iNumPlayers;                                      //  4708
//		float ratio;                                          //  4730
//		edict(CBaseEntity *const this);  //  4712
//		FNullEnt(const edict_t *pent);  //  4712
//	}
}

/* <116089> ../cstrike/dlls/multiplay_gamerules.cpp:4773 */
NOBODY void CHalfLifeMultiplay::ChangeLevel_(void)
{
//	{
//		char szPreviousMapCycleFile;                          //  4775
//		mapcycle_t mapcycle;                                  //  4776
//		char szNextMap;                                       //  4778
//		char szFirstMapInList;                                //  4779
//		char szCommands;                                      //  4780
//		char szRules;                                         //  4781
//		int minplayers;                                       //  4782
//		int maxplayers;                                       //  4782
//		int curplayers;                                       //  4785
//		BOOL do_cycle;                                        //  4786
//		char *mapcfile;                                      //  4789
//		CountPlayers(void);  //  4795
//		{
//			BOOL keeplooking;                             //  4813
//			BOOL found;                                   //  4814
//			class mapcycle_item_s *item;                 //  4815
//		}
//		DestroyMapCycle(mapcycle_t *cycle);  //  4802
//	}
}

/* <116317> ../cstrike/dlls/multiplay_gamerules.cpp:4903 */
NOBODY void CHalfLifeMultiplay::SendMOTDToClient(edict_t *client)
{
//	{
//		int length;                                           //  4906
//		int char_count;                                       //  4906
//		char *pFileList;                                     //  4907
//		char *aFileList;                                     //  4908
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  4911
//		{
//			char chunk;                                   //  4920
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  4938
//		}
//	}
}

NOBODY void CHalfLifeMultiplay::ClientUserInfoChanged_(CBasePlayer *pPlayer, char *infobuffer)
{

}

#ifdef HOOK_GAMEDLL

void CMapInfo::Spawn(void)
{
	Spawn_();
}

void CMapInfo::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CHalfLifeMultiplay::RefreshSkillData(void)
{
	RefreshSkillData_();
}

void CHalfLifeMultiplay::Think(void)
{
	Think_();
}

BOOL CHalfLifeMultiplay::IsAllowedToSpawn(CBaseEntity *pEntity)
{
	return IsAllowedToSpawn_(pEntity);
}

BOOL CHalfLifeMultiplay::FAllowFlashlight(void)
{
	return FAllowFlashlight_();
}

BOOL CHalfLifeMultiplay::FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	return FShouldSwitchWeapon_(pPlayer, pWeapon);
}

BOOL CHalfLifeMultiplay::GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	return GetNextBestWeapon_(pPlayer, pCurrentWeapon);
}

BOOL CHalfLifeMultiplay::IsMultiplayer(void)
{
	return IsMultiplayer_();
}

BOOL CHalfLifeMultiplay::IsDeathmatch(void)
{
	return IsDeathmatch_();
}

BOOL CHalfLifeMultiplay::IsCoOp(void)
{
	return IsCoOp_();
}

BOOL CHalfLifeMultiplay::ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128])
{
	return ClientConnected_(pEntity, pszName, pszAddress, szRejectReason);
}

void CHalfLifeMultiplay::InitHUD(CBasePlayer *pl)
{
	InitHUD_(pl);
}

void CHalfLifeMultiplay::ClientDisconnected(edict_t *pClient)
{
	ClientDisconnected_(pClient);
}

void CHalfLifeMultiplay::UpdateGameMode(CBasePlayer *pPlayer)
{
	UpdateGameMode_(pPlayer);
}

float CHalfLifeMultiplay::FlPlayerFallDamage(CBasePlayer *pPlayer)
{
	return FlPlayerFallDamage_(pPlayer);
}

BOOL CHalfLifeMultiplay::FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker)
{
	return FPlayerCanTakeDamage_(pPlayer, pAttacker);
}

void CHalfLifeMultiplay::PlayerSpawn(CBasePlayer *pPlayer)
{
	PlayerSpawn_(pPlayer);
}

void CHalfLifeMultiplay::PlayerThink(CBasePlayer *pPlayer)
{
	PlayerThink_(pPlayer);
}

BOOL CHalfLifeMultiplay::FPlayerCanRespawn(CBasePlayer *pPlayer)
{
	return FPlayerCanRespawn_(pPlayer);
}

float CHalfLifeMultiplay::FlPlayerSpawnTime(CBasePlayer *pPlayer)
{
	return FlPlayerSpawnTime_(pPlayer);
}

edict_t *CHalfLifeMultiplay::GetPlayerSpawnSpot(CBasePlayer *pPlayer)
{
	return GetPlayerSpawnSpot_(pPlayer);
}

BOOL CHalfLifeMultiplay::AllowAutoTargetCrosshair(void)
{
	return AllowAutoTargetCrosshair_();
}

BOOL CHalfLifeMultiplay::ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd)
{
	return ClientCommand_DeadOrAlive_(pPlayer, pcmd);
}

BOOL CHalfLifeMultiplay::ClientCommand(CBasePlayer *pPlayer, const char *pcmd)
{
	return ClientCommand_(pPlayer, pcmd);
}

void CHalfLifeMultiplay::ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer)
{
	ClientUserInfoChanged_(pPlayer, infobuffer);
}

int CHalfLifeMultiplay::IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled)
{
	return IPointsForKill_(pAttacker, pKilled);
}

void CHalfLifeMultiplay::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	PlayerKilled_(pVictim, pKiller, pInflictor);
}

void CHalfLifeMultiplay::DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	DeathNotice_(pVictim, pKiller, pInflictor);
}

BOOL CHalfLifeMultiplay::CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	return CanHavePlayerItem_(pPlayer, pWeapon);
}

void CHalfLifeMultiplay::PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon)
{
	PlayerGotWeapon_(pPlayer, pWeapon);
}

int CHalfLifeMultiplay::WeaponShouldRespawn(CBasePlayerItem *pWeapon)
{
	return WeaponShouldRespawn_(pWeapon);
}

float CHalfLifeMultiplay::FlWeaponRespawnTime(CBasePlayerItem *pWeapon)
{
	return FlWeaponRespawnTime_(pWeapon);
}

float CHalfLifeMultiplay::FlWeaponTryRespawn(CBasePlayerItem *pWeapon)
{
	return FlWeaponTryRespawn_(pWeapon);
}

Vector CHalfLifeMultiplay::VecWeaponRespawnSpot(CBasePlayerItem *pWeapon)
{
	return VecWeaponRespawnSpot_(pWeapon);
}

BOOL CHalfLifeMultiplay::CanHaveItem(CBasePlayer *pPlayer, CItem *pItem)
{
	return CanHaveItem_(pPlayer, pItem);
}

void CHalfLifeMultiplay::PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem)
{
	PlayerGotItem_(pPlayer, pItem);
}

int CHalfLifeMultiplay::ItemShouldRespawn(CItem *pItem)
{
	return ItemShouldRespawn_(pItem);
}

float CHalfLifeMultiplay::FlItemRespawnTime(CItem *pItem)
{
	return FlItemRespawnTime_(pItem);
}

Vector CHalfLifeMultiplay::VecItemRespawnSpot(CItem *pItem)
{
	return VecItemRespawnSpot_(pItem);
}

void CHalfLifeMultiplay::PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount)
{
	PlayerGotAmmo_(pPlayer, szName, iCount);
}

int CHalfLifeMultiplay::AmmoShouldRespawn(CBasePlayerAmmo *pAmmo)
{
	return AmmoShouldRespawn_(pAmmo);
}

float CHalfLifeMultiplay::FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo)
{
	return FlAmmoRespawnTime_(pAmmo);
}

Vector CHalfLifeMultiplay::VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo)
{
	return VecAmmoRespawnSpot_(pAmmo);
}

float CHalfLifeMultiplay::FlHealthChargerRechargeTime(void)
{
	return FlHealthChargerRechargeTime_();
}

float CHalfLifeMultiplay::FlHEVChargerRechargeTime(void)
{
	return FlHEVChargerRechargeTime_();
}

int CHalfLifeMultiplay::DeadPlayerWeapons(CBasePlayer *pPlayer)
{
	return DeadPlayerWeapons_(pPlayer);
}

int CHalfLifeMultiplay::DeadPlayerAmmo(CBasePlayer *pPlayer)
{
	return DeadPlayerAmmo_(pPlayer);
}

int CHalfLifeMultiplay::PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget)
{
	return PlayerRelationship_(pPlayer, pTarget);
}

BOOL CHalfLifeMultiplay::FAllowMonsters(void)
{
	return FAllowMonsters_();
}

void CHalfLifeMultiplay::ServerDeactivate(void)
{
	ServerDeactivate_();
}

void CHalfLifeMultiplay::CheckMapConditions(void)
{
	CheckMapConditions_();
}

void CHalfLifeMultiplay::CleanUpMap(void)
{
	CleanUpMap_();
}

void CHalfLifeMultiplay::RestartRound(void)
{
	RestartRound_();
}

void CHalfLifeMultiplay::CheckWinConditions(void)
{
	CheckWinConditions_();
}

void CHalfLifeMultiplay::RemoveGuns(void)
{
	RemoveGuns_();
}

void CHalfLifeMultiplay::GiveC4(void)
{
	GiveC4_();
}

void CHalfLifeMultiplay::ChangeLevel(void)
{
	ChangeLevel_();
}

void CHalfLifeMultiplay::GoToIntermission(void)
{
	GoToIntermission_();
}

#endif // HOOK_GAMEDLL
