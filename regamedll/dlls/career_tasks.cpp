#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

CCareerTaskManager *TheCareerTasks = NULL;

#else

CCareerTaskManager *TheCareerTasks;

#endif // HOOK_GAMEDLL

/* <1ef647> ../cstrike/dlls/career_tasks.cpp:133 */
NOBODY CCareerTask *CPreventDefuseTask::NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
//	CPreventDefuseTask(//				const char *taskName,
//				enum GameEventType event,
//				const char *weaponName,
//				int n,
//				bool mustLive,
//				bool crossRounds,
//				int id,
//				bool isComplete);  //   135
}

/* <1ef5db> ../cstrike/dlls/career_tasks.cpp:139 */
NOBODY CPreventDefuseTask::CPreventDefuseTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
	//CCareerTask(taskName, event, weaponName, n, mustLive, crossRounds, id, isComplete);
}

/* <1ef296> ../cstrike/dlls/career_tasks.cpp:147 */
NOBODY void CPreventDefuseTask::Reset(void)
{
}

/* <1efbf8> ../cstrike/dlls/career_tasks.cpp:156 */
NOBODY void CPreventDefuseTask::OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
//	OnEvent(CPreventDefuseTask *const this,
//		enum GameEventType event,
//		class CBasePlayer *pAttacker,
//		class CBasePlayer *pVictim);  //   156
}

/* <1ef4e1> ../cstrike/dlls/career_tasks.cpp:186 */
NOBODY CCareerTask *CCareerTask::NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
}

/* <1ef43f> ../cstrike/dlls/career_tasks.cpp:192 */
NOBODY CCareerTask::CCareerTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   217
}

/* <1ef211> ../cstrike/dlls/career_tasks.cpp:240 */
NOBODY void CCareerTask::Reset(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   244
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   248
}

/* <1ef74c> ../cstrike/dlls/career_tasks.cpp:256 */
NOBODY void CCareerTask::SendPartialNotification(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   258
}

/* <1efc6c> ../cstrike/dlls/career_tasks.cpp:268 */
NOBODY void CCareerTask::OnWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
//	{
//		int hostages;                                         //   298
//		class CBaseEntity *hostageEntity;                    //   299
//		{
//			class CHostage *hostage;                     //   303
//			IsFollowingSomeone(CHostage *const this);  //   304
//			IsValid(CHostage *const this);  //   306
//		}
//	}
//	SendPartialNotification(CCareerTask *const this);  //   341
}

/* <1efe16> ../cstrike/dlls/career_tasks.cpp:348 */
NOBODY void CCareerTask::OnWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker)
{
//	SendPartialNotification(CCareerTask *const this);  //   379
}

/* <1ef79d> ../cstrike/dlls/career_tasks.cpp:385 */
NOBODY void CCareerTask::OnEvent(GameEventType event, CBasePlayer *pVictim, CBasePlayer *pAttacker)
{
//	{
//		int hostages;                                         //   411
//		class CBaseEntity *hostageEntity;                    //   412
//		{
//			class CHostage *hostage;                     //   416
//			IsFollowingSomeone(CHostage *const this);  //   417
//			IsValid(CHostage *const this);  //   419
//		}
//	}
//	GetRoundElapsedTime(CCareerTaskManager *const this);  //   515
//	{
//		int hostages;                                         //   494
//		class CBaseEntity *hostageEntity;                    //   495
//		{
//			class CHostage *hostage;                     //   499
//			IsDead(CHostage *const this);  //   500
//		}
//	}
//	{
//		int hostages;                                         //   460
//		class CBaseEntity *hostageEntity;                    //   461
//		{
//			class CHostage *hostage;                     //   465
//			IsValid(CHostage *const this);  //   466
//		}
//		SendPartialNotification(CCareerTask *const this);  //   476
//	}
//	SendPartialNotification(CCareerTask *const this);  //   535
//	SendPartialNotification(CCareerTask *const this);  //   611
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   545
//	GetRoundElapsedTime(CCareerTaskManager *const this);  //   559
//	SetFinishedTaskTime(CCareerTaskManager *const this,
//				int val);  //   559
//	SendPartialNotification(CCareerTask *const this);  //   571
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   587
//	GetRoundElapsedTime(CCareerTaskManager *const this);  //   596
//	SetFinishedTaskTime(CCareerTaskManager *const this,
//				int val);  //   596
}

/* <1efeed> ../cstrike/dlls/career_tasks.cpp:623 */
NOBODY void CCareerTaskManager::Create(void)
{
//	CCareerTaskManager(CCareerTaskManager *const this);  //   631
}

/* <1eff77> ../cstrike/dlls/career_tasks.cpp:636 */
NOBODY CCareerTaskManager::CCareerTaskManager(void)
{
//	list(list<CCareerTask*, std::allocator<CCareerTask*>> *const this);  //   636
}

/* <1effeb> ../cstrike/dlls/career_tasks.cpp:643 */
NOBODY void CCareerTaskManager::Reset(bool deleteTasks)
{
//	{
//		CareerTaskListIt it;                                  //   647
//		operator++(_List_iterator<CCareerTask*> *const this);  //   647
//	}
//	clear(list<CCareerTask*, std::allocator<CCareerTask*>> *const this);  //   651
//	{
//		CareerTaskListIt it;                                  //   656
//		{
//			class CCareerTask *pTask;                    //   658
//		}
//		operator++(_List_iterator<CCareerTask*> *const this);  //   656
//	}
}

/* <1f014e> ../cstrike/dlls/career_tasks.cpp:671 */
NOBODY void CCareerTaskManager::SetFinishedTaskTime(int val)
{
	CHalfLifeMultiplay *mp = g_pGameRules;

	m_finishedTaskTime = val;
	m_finishedTaskRound = mp->m_iTotalRoundsPlayed;
}

/* <1f018b> ../cstrike/dlls/career_tasks.cpp:679 */
NOBODY void CCareerTaskManager::AddTask(const char *taskName, const char *weaponName, int eventCount, bool mustLive, bool crossRounds, bool isComplete)
{
//	{
//		int i;                                                //   683
//		push_back(list<CCareerTask*, std::allocator<CCareerTask*>> *const this,
//				const value_type &__x);  //   696
//	}
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   714
}

/* <1f0381> ../cstrike/dlls/career_tasks.cpp:721 */
NOBODY void CCareerTaskManager::HandleEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
//	{
//		CareerTaskListIt it;                                  //   741
//		operator++(_List_iterator<CCareerTask*> *const this);  //   741
//	}
}

/* <1f0462> ../cstrike/dlls/career_tasks.cpp:748 */
NOBODY void CCareerTaskManager::HandleWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
//	{
//		CareerTaskListIt it;                                  //   750
//		operator++(_List_iterator<CCareerTask*> *const this);  //   750
//	}
}

/* <1f04ed> ../cstrike/dlls/career_tasks.cpp:757 */
NOBODY void CCareerTaskManager::HandleEnemyKill(bool wasBlind, const char *weaponName, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
//	HandleWeaponKill(CCareerTaskManager *const this,
//			int weaponId,
//			int weaponClassId,
//			bool headshot,
//			bool killerHasShield,
//			class CBasePlayer *pAttacker,
//			class CBasePlayer *pVictim);  //   759
//	HandleEvent(CCareerTaskManager *const this,
//			enum GameEventType event,
//			class CBasePlayer *pAttacker,
//			class CBasePlayer *pVictim);  //   760
//	HandleEvent(CCareerTaskManager *const this,
//			enum GameEventType event,
//			class CBasePlayer *pAttacker,
//			class CBasePlayer *pVictim);  //   764
//	HandleEvent(CCareerTaskManager *const this,
//			enum GameEventType event,
//			class CBasePlayer *pAttacker,
//			class CBasePlayer *pVictim);  //   762
}

/* <1f079c> ../cstrike/dlls/career_tasks.cpp:768 */
NOBODY void CCareerTaskManager::HandleWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker)
{
//	{
//		CareerTaskListIt it;                                  //   770
//		operator++(_List_iterator<CCareerTask*> *const this);  //   770
//	}
}

/* <1f0815> ../cstrike/dlls/career_tasks.cpp:777 */
NOBODY void CCareerTaskManager::HandleEnemyInjury(const char *weaponName, bool attackerHasShield, CBasePlayer *pAttacker)
{
//	HandleWeaponInjury(CCareerTaskManager *const this,
//				int weaponId,
//				int weaponClassId,
//				bool attackerHasShield,
//				class CBasePlayer *pAttacker);  //   779
//	HandleEvent(CCareerTaskManager *const this,
//			enum GameEventType event,
//			class CBasePlayer *pAttacker,
//			class CBasePlayer *pVictim);  //   780
}

/* <1f094e> ../cstrike/dlls/career_tasks.cpp:784 */
NOBODY void CCareerTaskManager::HandleDeath(int team, CBasePlayer *pAttacker)
{
//	{
//		int enemyTeam;                                        //   786
//		int numEnemies;                                       //   790
//		{
//			int i;                                        //   791
//			{
//				class CBasePlayer *pPlayer;          //   793
//			}
//		}
//		HandleEvent(CCareerTaskManager *const this,
//				enum GameEventType event,
//				class CBasePlayer *pAttacker,
//				class CBasePlayer *pVictim);  //   801
//	}
}

/* <1f0a5d> ../cstrike/dlls/career_tasks.cpp:805 */
NOBODY bool CCareerTaskManager::AreAllTasksComplete(void)
{
//	{
//		CareerTaskListIt it;                                  //   807
//		operator++(_List_iterator<CCareerTask*> *const this);  //   807
//	}
}

/* <1f0abc> ../cstrike/dlls/career_tasks.cpp:818 */
NOBODY int CCareerTaskManager::GetNumRemainingTasks(void)
{
//	{
//		int ret;                                              //   820
//		{
//			CareerTaskListIt it;                          //   821
//			operator++(_List_iterator<CCareerTask*> *const this);  //   821
//		}
//	}
}

/* <1f0b33> ../cstrike/dlls/career_tasks.cpp:832 */
float CCareerTaskManager::GetRoundElapsedTime(void)
{
	return gpGlobals->time - m_roundStartTime;
}

/* <1f0b56> ../cstrike/dlls/career_tasks.cpp:838 */
NOBODY void CCareerTaskManager::LatchRoundEndMessage(void)
{
}

/* <1f0b81> ../cstrike/dlls/career_tasks.cpp:844 */
NOBODY void CCareerTaskManager::UnlatchRoundEndMessage(void)
{
//	HandleEvent(CCareerTaskManager::UnlatchRoundEndMessage(//			enum GameEventType event,
//			class CBasePlayer *pAttacker,
//			class CBasePlayer *pVictim);  //   847
}
