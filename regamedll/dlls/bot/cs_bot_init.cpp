#include "precompiled.h"

/* <333bca> ../cstrike/dlls/bot/cs_bot_init.cpp:57 */
NOBODY void InstallBotControl(void)
{
//	~CBotManager(CBotManager *const this,
//			int const __in_chrg);  //    60
}

/* <333cb3> ../cstrike/dlls/bot/cs_bot_init.cpp:68 */
void Bot_ServerCommand(void)
{
	if (TheBots != NULL)
	{
		const char *pcmd = CMD_ARGV(0);
		TheBots->ServerCommand(pcmd);
	}
}

/* <333cec> ../cstrike/dlls/bot/cs_bot_init.cpp:81 */
void Bot_RegisterCvars(void)
{
	if (UTIL_IsGame("czero"))
	{
		CVAR_REGISTER(&cv_bot_traceview);
		CVAR_REGISTER(&cv_bot_stop);
		CVAR_REGISTER(&cv_bot_show_nav);
		CVAR_REGISTER(&cv_bot_show_danger);
		CVAR_REGISTER(&cv_bot_nav_edit);
		CVAR_REGISTER(&cv_bot_nav_zdraw);
		CVAR_REGISTER(&cv_bot_walk);
		CVAR_REGISTER(&cv_bot_difficulty);
		CVAR_REGISTER(&cv_bot_debug);
		CVAR_REGISTER(&cv_bot_quicksave);
		CVAR_REGISTER(&cv_bot_quota);
		CVAR_REGISTER(&cv_bot_quota_match);
		CVAR_REGISTER(&cv_bot_prefix);
		CVAR_REGISTER(&cv_bot_allow_rogues);
		CVAR_REGISTER(&cv_bot_allow_pistols);
		CVAR_REGISTER(&cv_bot_allow_shotguns);
		CVAR_REGISTER(&cv_bot_allow_sub_machine_guns);
		CVAR_REGISTER(&cv_bot_allow_rifles);
		CVAR_REGISTER(&cv_bot_allow_machine_guns);
		CVAR_REGISTER(&cv_bot_allow_grenades);
		CVAR_REGISTER(&cv_bot_allow_snipers);
		CVAR_REGISTER(&cv_bot_allow_shield);
		CVAR_REGISTER(&cv_bot_join_team);
		CVAR_REGISTER(&cv_bot_join_after_player);
		CVAR_REGISTER(&cv_bot_auto_vacate);
		CVAR_REGISTER(&cv_bot_zombie);
		CVAR_REGISTER(&cv_bot_defer_to_human);
		CVAR_REGISTER(&cv_bot_chatter);
		CVAR_REGISTER(&cv_bot_profile_db);
	}
}

/* <333d1e> ../cstrike/dlls/bot/cs_bot_init.cpp:129 */
//CCSBot::CCSBot(void)
//{
//	CountdownTimer(CountdownTimer *const this);  //   129
//	IdleState(IdleState *const this);  //   129
//	MoveToState(MoveToState *const this);  //   129
//	HuntState(HuntState *const this);  //   129
//	FetchBombState(FetchBombState *const this);  //   129
//	AttackState(AttackState *const this);  //   129
//	InvestigateNoiseState(InvestigateNoiseState *const this);  //   129
//	BuyState(BuyState *const this);  //   129
//	PlantBombState(PlantBombState *const this);  //   129
//	DefuseBombState(DefuseBombState *const this);  //   129
//	HideState(HideState *const this);  //   129
//	EscapeFromBombState(EscapeFromBombState *const this);  //   129
//	FollowState(FollowState *const this);  //   129
//	UseEntityState(UseEntityState *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	IntervalTimer(IntervalTimer *const this);  //   129
//	_List_iterator(_List_iterator<CNavArea*> *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//	CountdownTimer(CountdownTimer *const this);  //   129
//}

/* <3342ac> ../cstrike/dlls/bot/cs_bot_init.cpp:137 */
NOBODY bool CCSBot::Initialize_(const BotProfile *profile)
{
	CBot::Initialize(profile);

	m_diedLastRound = false;
	m_morale = POSITIVE;
	m_navNodeList = NULL;
	m_currentNode = NULL;

	m_combatRange = RANDOM_FLOAT(325, 425);
	m_name[0] = '\0';
	m_safeTime = m_profile->GetAggression() * 5 + 15;

	ResetValues();
	StartNormalProcess();

	return true;
}

/* <3341dc> ../cstrike/dlls/bot/cs_bot_init.cpp:167 */
NOBODY void CCSBot::ResetValues(void)
{
	m_chatter.Reset();//TODO: Reverse me
	m_gameState.Reset();//TODO: Reverse me

	m_avoid = NULL;
	m_avoidTimestamp = 0.0f;

	m_hurryTimer.Invalidate();

	m_isStuck = false;
	m_stuckTimestamp = 0.0f;
	m_wiggleTimestamp = 0.0f;
	m_stuckJumpTimestamp = 0.0f;

	m_pathLength = 0;
	m_pathIndex = 0;

	m_areaEnteredTimestamp = 0.0f;
	m_currentArea = NULL;
	m_lastKnownArea = NULL;
	
	m_avoidFriendTimer.Invalidate();

	m_isFriendInTheWay = false;
	m_isWaitingBehindFriend = false;
	m_disposition = ENGAGE_AND_INVESTIGATE;

	m_enemy = NULL;
	m_isWaitingToTossGrenade = false;
	m_wasSafe = true;
	m_nearbyEnemyCount = 0;
	m_enemyPlace = 0;
	m_nearbyFriendCount = 0;

	m_closestVisibleFriend = NULL;
	m_closestVisibleHumanFriend = NULL;

	for (int w = 0; w < ARRAYSIZE(m_watchInfo); w++)
	{
		m_watchInfo[w].timestamp = 0.0f;
		m_watchInfo[w].isEnemy = false;
	}

	m_isEnemyVisible = false;
	m_visibleEnemyParts = NONE;

	m_lastSawEnemyTimestamp = 0.0f;
	m_firstSawEnemyTimestamp = 0.0f;
	m_currentEnemyAcquireTimestamp = 0.0f;

	m_isLastEnemyDead = true;

	m_attacker = NULL;
	m_attackedTimestamp = 0.0f;
	m_enemyDeathTimestamp = 0.0f;
	m_lastVictimID = 0;
	m_isAimingAtEnemy = false;

	m_fireWeaponTimestamp = 0.0f;
	m_equipTimer.Invalidate();
	m_isFollowing = false;
	m_leader = NULL;

	m_followTimestamp = 0.0f;
	m_allowAutoFollowTime = 0.0f;

	m_enemyQueueIndex = 0;
	m_enemyQueueCount = 0;
	m_enemyQueueAttendIndex = 0;
	m_bomber = NULL;

	m_lookAroundStateTimestamp = 0.0f;
	m_inhibitLookAroundTimestamp = 0.0f;
	m_lookPitch = 0.0f;
	m_lookPitchVel = 0.0f;
	m_lookYaw = 0.0f;
	m_lookYawVel = 0.0f;
	m_aimOffsetTimestamp = 0.0f;
	m_aimSpreadTimestamp = 0.0f;

	m_lookAtSpotState = NOT_LOOKING_AT_SPOT;
	m_spotEncounter = NULL;

	m_spotCheckTimestamp = 0.0f;
	m_peripheralTimestamp = 0.0f;

	m_avgVelIndex = 0;
	m_avgVelCount = 0;

	if (pev)
	{
		m_lastOrigin = pev->origin;
	}
	else
		m_lastOrigin = Vector(0, 0, 0);

	m_lastRadioCommand = EVENT_INVALID;

	m_lastRadioRecievedTimestamp = 0.0f;
	m_lastRadioSentTimestamp = 0.0f;
	m_radioSubject = NULL;

	m_noisePosition = Vector(0, 0, 0);
	m_noiseTimestamp = 0.0f;
	m_noiseCheckTimestamp = 0.0f;

	m_voiceFeedbackEndTimestamp = 0.0f;

	m_hostageEscortCount = 0;
	m_hostageEscortCountTimestamp = 0.0f;

	m_isNoiseTravelRangeChecked = false;
	m_stateTimestamp = 0.0f;

	m_task = SEEK_AND_DESTROY;
	m_taskEntity = NULL;

	m_approachPointCount = 0;
	m_approachPointViewPosition = Vector(0, 0, 0);

	m_checkedHidingSpotCount = 0;
	m_isJumpCrouching = false;

	StandUp();
	Run();

	m_pathLadder = NULL;
	m_mustRunTimer.Invalidate();
	m_repathTimer.Invalidate();

	m_huntState.ClearHuntArea();

	// adjust morale - if we died, our morale decreased, 
	// but if we live, no adjustement (round win/loss also adjusts morale
	if (m_diedLastRound)
	{
		DecreaseMorale();
	}

	m_diedLastRound = false;
	m_isRogue = false;

	m_surpriseDelay = 0.0f;
	m_surpriseTimestamp = 0.0f;

	m_goalEntity = NULL;
	m_avoid = NULL;
	m_enemy = NULL;

	// start in idle state
	StopAttacking();//TODO: Reverse me
	Idle();//TODO: Reverse me
}

/* <3342e4> ../cstrike/dlls/bot/cs_bot_init.cpp:336 */
NOBODY void CCSBot::SpawnBot_(void)
{
//	{
//		class CCSBotManager *ctrl;                           //   338
//		SetLearningMapFlag(CCSBotManager *const this);  //   357
//	}
}

/* <3338f7> ../cstrike/dlls/bot/cs_bot_init.cpp:366 */
NOBODY void CCSBot::RoundRespawn_(void)
{
}

/* <334332> ../cstrike/dlls/bot/cs_bot_init.cpp:378 */
void CCSBot::Disconnect(void)
{
	EndVoiceFeedback();

	if (m_processMode)
	{
		MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
			WRITE_BYTE(FLAG_PROGRESS_HIDE);
		MESSAGE_END();
	}
}

#ifdef HOOK_GAMEDLL

bool CCSBot::Initialize(const BotProfile *profile)
{
	return Initialize_(profile);
}

void CCSBot::SpawnBot(void)
{
	SpawnBot_();
}

void CCSBot::RoundRespawn(void)
{
	RoundRespawn_();
}

#endif // HOOK_GAMEDLL
