#include "precompiled.h"

/* <333bca> ../cstrike/dlls/bot/cs_bot_init.cpp:57 */
NOBODY void InstallBotControl(void)
{
//	~CBotManager(CBotManager *const this,
//			int const __in_chrg);  //    60
}

/* <333cb3> ../cstrike/dlls/bot/cs_bot_init.cpp:68 */
NOBODY void Bot_ServerCommand(void)
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
}

/* <3341dc> ../cstrike/dlls/bot/cs_bot_init.cpp:167 */
NOBODY void CCSBot::ResetValues(void)
{
//	{
//		class CCSBotManager *ctrl;                           //   304
//		Invalidate(CountdownTimer *const this);  //   175
//		Invalidate(CountdownTimer *const this);  //   188
//		{
//			int w;                                        //   206
//		}
//		Invalidate(IntervalTimer *const this);  //   224
//		ClearHuntArea(HuntState *const this);  //   294
//		Invalidate(CountdownTimer *const this);  //   289
//		Invalidate(CountdownTimer *const this);  //   292
//	}
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
NOBODY void CCSBot::Disconnect(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   386
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
