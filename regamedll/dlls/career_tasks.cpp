#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

CCareerTaskManager *TheCareerTasks = NULL;

const TaskInfo taskInfo[] =
{
	{ "defuse",			EVENT_BOMB_DEFUSED,		&CCareerTask::NewTask },
	{ "plant",			EVENT_BOMB_PLANTED,		&CCareerTask::NewTask },
	{ "rescue",			EVENT_HOSTAGE_RESCUED,		&CCareerTask::NewTask },
	{ "killall",			EVENT_KILL_ALL,			&CCareerTask::NewTask },
	{ "kill",			EVENT_KILL,			&CCareerTask::NewTask },
	{ "killwith",			EVENT_KILL,			&CCareerTask::NewTask },
	{ "killblind",			EVENT_KILL_FLASHBANGED,		&CCareerTask::NewTask },
	{ "killvip",			EVENT_KILL,			&CCareerTask::NewTask },
	{ "headshot",			EVENT_HEADSHOT,			&CCareerTask::NewTask },
	{ "headshotwith",		EVENT_HEADSHOT,			&CCareerTask::NewTask },
	{ "winfast",			EVENT_ROUND_WIN,		&CCareerTask::NewTask },
	{ "rescue",			EVENT_HOSTAGE_RESCUED,		&CCareerTask::NewTask },
	{ "rescueall",			EVENT_ALL_HOSTAGES_RESCUED,	&CCareerTask::NewTask },
	{ "injure",			EVENT_PLAYER_TOOK_DAMAGE,	&CCareerTask::NewTask },
	{ "injurewith",			EVENT_PLAYER_TOOK_DAMAGE,	&CCareerTask::NewTask },
	{ "killdefuser",		EVENT_KILL,			&CCareerTask::NewTask },
	{ "stoprescue",			EVENT_KILL,			&CCareerTask::NewTask },
	{ "defendhostages",		EVENT_ROUND_WIN,		&CCareerTask::NewTask },
	{ "hostagessurvive",		EVENT_ROUND_WIN,		&CCareerTask::NewTask },
	{ "preventdefuse",		EVENT_ROUND_WIN,		&CPreventDefuseTask::NewTask },
	{ NULL,				EVENT_INVALID,			&CCareerTask::NewTask }
};

#else // HOOK_GAMEDLL

CCareerTaskManager *TheCareerTasks;
const TaskInfo taskInfo[21];

#endif // HOOK_GAMEDLL

/* <1ef647> ../cstrike/dlls/career_tasks.cpp:133 */
CCareerTask *CPreventDefuseTask::NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
	CPreventDefuseTask *pNewTask = new CPreventDefuseTask(taskName, event, weaponName, n, mustLive, crossRounds, id, isComplete);
	
	pNewTask->m_bombPlantedThisRound = false;
	pNewTask->m_defuseStartedThisRound = false;

	return (CCareerTask *)pNewTask;
}

/* <1ef5db> ../cstrike/dlls/career_tasks.cpp:139 */
CPreventDefuseTask::CPreventDefuseTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
	CCareerTask(taskName, event, weaponName, n, mustLive, crossRounds, id, isComplete);
	
	m_bombPlantedThisRound = false;
	m_defuseStartedThisRound = false;
}

/* <1ef296> ../cstrike/dlls/career_tasks.cpp:147 */
void CPreventDefuseTask::__MAKE_VHOOK(Reset)(void)
{
	m_bombPlantedThisRound = false;
	m_defuseStartedThisRound = false;

	CCareerTask::Reset();
}

/* <1efbf8> ../cstrike/dlls/career_tasks.cpp:156 */
void CPreventDefuseTask::__MAKE_VHOOK(OnEvent)(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	if (IsComplete())
		return;

	if (event == EVENT_BOMB_PLANTED)
	{
		m_bombPlantedThisRound = true;
	}
	else if (event == EVENT_BOMB_DEFUSING)
	{
		m_defuseStartedThisRound = true;
	}

	CCareerTask::OnEvent(event, pAttacker, pVictim);

	if (event >= EVENT_ROUND_DRAW && event <= EVENT_ROUND_LOSS)
	{
		m_bombPlantedThisRound = false;
		m_defuseStartedThisRound = false;
	}
}

/* <1ef4e1> ../cstrike/dlls/career_tasks.cpp:186 */
CCareerTask *CCareerTask::NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
	CCareerTask *pTask = new CCareerTask(taskName, event, weaponName, n, mustLive, crossRounds, id, isComplete);
	return pTask;
}

/* <1ef43f> ../cstrike/dlls/career_tasks.cpp:192 */
CCareerTask::CCareerTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete)
{
	m_isComplete = isComplete;
	m_event = event;
	m_eventsNeeded = n;

	m_name = taskName;
	m_eventsSeen = 0;
	m_mustLive = mustLive;
	m_crossRounds = crossRounds;
	m_diedThisRound = false;
	m_id = id;
	m_weaponId = AliasToWeaponID(weaponName);
	m_weaponClassId = AliasToWeaponClass(weaponName);

	m_rescuer = (Q_stricmp(taskName, "stoprescue") == 0);
	m_defuser = (Q_stricmp(taskName, "killdefuser") == 0);
	m_vip = (Q_stricmp(taskName, "killvip") == 0);

	if (event == EVENT_ALL_HOSTAGES_RESCUED)
	{
		m_mustLive = true;
		m_crossRounds = false;
	}

	if (m_isComplete)
	{
		MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
			WRITE_STRING("TASKDONE");
			WRITE_BYTE(m_id);
		MESSAGE_END();
	}
}

/* <1ef211> ../cstrike/dlls/career_tasks.cpp:240 */
void CCareerTask::__MAKE_VHOOK(Reset)(void)
{
	m_eventsSeen = 0;
	m_isComplete = false;

	MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
		WRITE_STRING("TASKUNDONE");
		WRITE_BYTE(m_id);
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
		WRITE_STRING("TASKPART");
		WRITE_BYTE(m_id);
		WRITE_SHORT(m_eventsSeen);
	MESSAGE_END();
}

/* <1ef74c> ../cstrike/dlls/career_tasks.cpp:256 */
void CCareerTask::SendPartialNotification(void)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
		WRITE_STRING("TASKPART");
		WRITE_BYTE(m_id);
		WRITE_SHORT(m_eventsSeen);
	MESSAGE_END();

	UTIL_LogPrintf("Career Task Partial %d %d\n", m_id, m_eventsSeen);
}

/* <1efc6c> ../cstrike/dlls/career_tasks.cpp:268 */
void CCareerTask::OnWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	if (m_isComplete || m_event != EVENT_KILL && (m_event != EVENT_HEADSHOT || !headshot))
	{
		return;
	}

	if (!pVictim || (m_defuser && !pVictim->m_bIsDefusing) || (m_vip && !pVictim->m_bIsVIP))
	{
		return;
	}

	if (m_rescuer)
	{
		int hostages_ = 0;
		CBaseEntity *hostageEntity = NULL;

		while ((hostageEntity = UTIL_FindEntityByClassname(hostageEntity, "hostage_entity")) != NULL)
		{
			CHostage *hostage = (CHostage *)hostageEntity;

			if (!hostage || hostage->pev->takedamage != DAMAGE_YES)
				continue;

			if (hostage->m_improv)
			{
				if (!hostage->IsFollowingSomeone())
					continue;
			}
			else if (!hostage->m_hTargetEnt || hostage->m_State != CHostage::FOLLOW)
				continue;

			if (hostage->IsValid() && hostage->m_target == pAttacker)
				++hostages_;
		}

		if (!hostages_)
			return;	
	}

	if (m_weaponId == WEAPON_SHIELDGUN)
	{
		if (!killerHasShield)
			return;
	}
	else if (m_weaponId)
	{
		if (m_weaponId != weaponId)
			return;
	}
	else if (m_weaponClassId)
	{
		if (m_weaponClassId != weaponClassId)
			return;
	}

	++m_eventsSeen;
	SendPartialNotification();
}

/* <1efe16> ../cstrike/dlls/career_tasks.cpp:348 */
void CCareerTask::OnWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker)
{
	if (m_isComplete || m_event != EVENT_PLAYER_TOOK_DAMAGE)
	{
		return;
	}

	if (m_weaponId == WEAPON_SHIELDGUN)
	{
		if (!attackerHasShield)
			return;
	}
	else if (m_weaponId)
	{
		if (m_weaponId != weaponId)
			return;
	}
	else if (m_weaponClassId)
	{
		if (m_weaponClassId != weaponClassId)
			return;
	}

	++m_eventsSeen;
	SendPartialNotification();
}

/* <1ef79d> ../cstrike/dlls/career_tasks.cpp:385 */
void CCareerTask::__MAKE_VHOOK(OnEvent)(GameEventType event, CBasePlayer *pVictim, CBasePlayer *pAttacker)
{
	if (m_isComplete)
		return;

	if (event == m_event)
	{
		if ((m_defuser && !pAttacker->m_bIsDefusing) || (m_vip && !pAttacker->m_bIsVIP))
			return;

		if (m_rescuer)
		{
			int hostages_ = 0;
			CBaseEntity *hostageEntity = NULL;

			while ((hostageEntity = UTIL_FindEntityByClassname(hostageEntity, "hostage_entity")) != NULL)
			{
				if (hostageEntity->pev->takedamage != DAMAGE_YES)
					continue;

				CHostage *hostage = reinterpret_cast<CHostage *>(hostageEntity);

				if (hostage->m_improv)
				{
					if (!hostage->IsFollowingSomeone())
					{
						continue;
					}
				}
				else if (hostage->m_hTargetEnt == NULL || hostage->m_State != CHostage::FOLLOW)
				{
					continue;
				}

				if (hostage->IsValid() && hostage->m_target == pAttacker)
					++hostages_;
			}

			if (!hostages_)
			{
				return;
			}
		}

		if (m_event != EVENT_KILL || (!m_weaponId && !m_weaponClassId)
			&& m_event != EVENT_HEADSHOT || (!m_weaponId && !m_weaponClassId)
			&& m_event != EVENT_PLAYER_TOOK_DAMAGE || (!m_weaponId && !m_weaponClassId))
		{
			if (m_event == EVENT_ROUND_WIN)
			{
				if (!Q_strcmp(m_name, "defendhostages"))
				{
					int hostages_ = 0;
					CBaseEntity *hostageEntity = NULL;

					while ((hostageEntity = UTIL_FindEntityByClassname(hostageEntity, "hostage_entity")) != NULL)
					{
						if (hostageEntity->pev->takedamage != 1.0f && hostageEntity->pev->deadflag != DEAD_DEAD)
							++hostages_;
					}

					if (!hostages_)
					{
						++m_eventsSeen;
						SendPartialNotification();
					}
				}
				else if (!Q_strcmp(m_name, "hostagessurvive"))
				{
					int hostages_ = 0;
					CBaseEntity *hostageEntity = NULL;

					while ((hostageEntity = UTIL_FindEntityByClassname(hostageEntity, "hostage_entity")) != NULL)
					{
						CHostage *hostage = (CHostage *)hostageEntity;

						if (hostage && hostage->IsDead())
							++hostages_;
					}

					if (!hostages_)
					{
						++m_eventsSeen;
						SendPartialNotification();
					}
				}
				else if (!Q_strcmp(m_name, "winfast"))
				{
					if (m_eventsNeeded >= TheCareerTasks->GetRoundElapsedTime())
					{
						m_eventsSeen = m_eventsNeeded;
						SendPartialNotification();
					}
				}
				else if (IsTaskCompletableThisRound())
				{
					++m_eventsSeen;
					SendPartialNotification();
				}
			}
			else
			{
				++m_eventsSeen;
				SendPartialNotification();
			}
		}
	}

	if (event == m_event && !m_mustLive && m_eventsSeen >= m_eventsNeeded && IsTaskCompletableThisRound())
	{
		CBasePlayer *player = UTIL_GetLocalPlayer();
		EMIT_SOUND(ENT(player->pev), CHAN_VOICE, "events/task_complete.wav", VOL_NORM, ATTN_NORM); 

		m_isComplete = true;
		MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
			WRITE_STRING("TASKDONE");
			WRITE_BYTE(m_id);
		MESSAGE_END();

		if (TheTutor)
		{
			TheTutor->OnEvent(EVENT_CAREER_TASK_DONE);
		}

		UTIL_LogPrintf("Career Task Done %d\n", m_id);

		if (m_event == EVENT_ROUND_WIN && !Q_strcmp(m_name, "winfast"))
		{
			TheCareerTasks->SetFinishedTaskTime((int)TheCareerTasks->GetRoundElapsedTime());
			UTIL_GetLocalPlayer()->SyncRoundTimer();
		}
	}
	else if (event >= EVENT_ROUND_DRAW)
	{
		if (event > EVENT_ROUND_LOSS)
		{
			if (event == EVENT_DIE && (m_mustLive || m_crossRounds))
			{
				m_eventsSeen = 0;
				SendPartialNotification();
				m_diedThisRound = true;
			}		
		}
		else if (m_mustLive)
		{
			if (m_eventsSeen >= m_eventsNeeded && !m_diedThisRound && IsTaskCompletableThisRound())
			{
				CBasePlayer *player = UTIL_GetLocalPlayer();
				EMIT_SOUND(ENT(player->pev), CHAN_VOICE, "events/task_complete.wav", VOL_NORM, ATTN_NORM); 

				m_isComplete = true;
				MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
					WRITE_STRING("TASKDONE");
					WRITE_BYTE(m_id);
				MESSAGE_END();

				UTIL_LogPrintf("Career Task Done %d\n", m_id);

				if (m_event == EVENT_ROUND_WIN && !Q_strcmp(m_name, "winfast"))
				{
					TheCareerTasks->SetFinishedTaskTime((signed __int64)(TheCareerTasks->GetRoundElapsedTime()));
					UTIL_GetLocalPlayer()->SyncRoundTimer();
				}

				if (TheTutor)
				{
					TheTutor->OnEvent(EVENT_CAREER_TASK_DONE);
				}
			}

			m_diedThisRound = false;

			if (m_mustLive)
			{
				m_eventsSeen = 0;
				SendPartialNotification();
			}
		}
	}
}

/* <1efeed> ../cstrike/dlls/career_tasks.cpp:623 */
void CCareerTaskManager::Create(void)
{
	if (TheCareerTasks != NULL)
	{
		TheCareerTasks->Reset();
		return;
	}

	TheCareerTasks = new CCareerTaskManager;
}

/* <1eff77> ../cstrike/dlls/career_tasks.cpp:636 */
CCareerTaskManager::CCareerTaskManager(void)
{
	m_taskTime = 0;
	Reset();
}

/* <1effeb> ../cstrike/dlls/career_tasks.cpp:643 */
void CCareerTaskManager::Reset(bool deleteTasks)
{
	if (deleteTasks)
	{
		for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
		{
			delete (*it);
		}

		m_tasks.clear();
		m_nextId = 0;
	}
	else
	{
		for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
		{
			CCareerTask *pTask = (*it);
			pTask->Reset();
		}
	}

	m_finishedTaskTime  = 0;
	m_finishedTaskRound = 0;
	m_shouldLatchRoundEndMessage = false;

	m_roundStartTime = gpGlobals->time + CVAR_GET_FLOAT("mp_freezetime");
}

/* <1f014e> ../cstrike/dlls/career_tasks.cpp:671 */
void CCareerTaskManager::SetFinishedTaskTime(int val)
{
	CHalfLifeMultiplay *mp = g_pGameRules;

	m_finishedTaskTime = val;
	m_finishedTaskRound = mp->m_iTotalRoundsPlayed;
}

/* <1f018b> ../cstrike/dlls/career_tasks.cpp:679 */
void CCareerTaskManager::AddTask(const char *taskName, const char *weaponName, int eventCount, bool mustLive, bool crossRounds, bool isComplete)
{
	++m_nextId;

	for (int i = 0; i < ARRAYSIZE(taskInfo); i++)
	{
		const TaskInfo *pTaskInfo = &taskInfo[ i ];

		if (pTaskInfo->taskName != NULL)
		{
			if (!Q_stricmp(pTaskInfo->taskName, taskName))
			{
				CCareerTask *newTask = pTaskInfo->factory
				(
					pTaskInfo->taskName,
					pTaskInfo->event,
					weaponName,
					eventCount,
					mustLive,
					crossRounds,
					m_nextId,
					isComplete
				);

				m_tasks.push_back(newTask);

				if (pTaskInfo->event == EVENT_ROUND_WIN && !Q_strcmp(taskName, "winfast"))
				{
					m_taskTime = eventCount;

					if (isComplete)
					{
						m_finishedTaskTime = eventCount;
					}
				}

				return;
			}
		}
	}

	MESSAGE_BEGIN(MSG_ALL, gmsgCZCareer);
		WRITE_STRING("TASKDONE");
		WRITE_BYTE(m_nextId);
	MESSAGE_END();
}

/* <1f0381> ../cstrike/dlls/career_tasks.cpp:721 */
void CCareerTaskManager::HandleEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	if (event == EVENT_ROUND_START)
	{
		m_roundStartTime = gpGlobals->time;
		return;
	}

	if ((event <= EVENT_ROUND_LOSS && event >= EVENT_ROUND_DRAW) && m_shouldLatchRoundEndMessage)
	{
		m_roundEndMessage = event;
		return;
	}

	for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		(*it)->OnEvent(event, pAttacker, pVictim);
	}
}

/* <1f0462> ../cstrike/dlls/career_tasks.cpp:748 */
void CCareerTaskManager::HandleWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		(*it)->OnWeaponKill(weaponId, weaponClassId, headshot, killerHasShield, pAttacker, pVictim);
	}
}

/* <1f04ed> ../cstrike/dlls/career_tasks.cpp:757 */
void CCareerTaskManager::HandleEnemyKill(bool wasBlind, const char *weaponName, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	HandleWeaponKill(AliasToWeaponID(weaponName), AliasToWeaponClass(weaponName), headshot, killerHasShield, pAttacker, pVictim);

	HandleEvent(EVENT_KILL, pAttacker, pVictim);

	if (headshot)
	{
		HandleEvent(EVENT_HEADSHOT, pAttacker, pVictim);
	}
	if (wasBlind)
	{
		HandleEvent(EVENT_KILL_FLASHBANGED, pAttacker, pVictim);
	}
}

/* <1f079c> ../cstrike/dlls/career_tasks.cpp:768 */
void CCareerTaskManager::HandleWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker)
{
	for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		(*it)->OnWeaponInjury(weaponId, weaponClassId, attackerHasShield, pAttacker);
	}
}

/* <1f0815> ../cstrike/dlls/career_tasks.cpp:777 */
void CCareerTaskManager::HandleEnemyInjury(const char *weaponName, bool attackerHasShield, CBasePlayer *pAttacker)
{
	HandleWeaponInjury(AliasToWeaponID(weaponName), AliasToWeaponClass(weaponName), attackerHasShield, pAttacker);
	HandleEvent(EVENT_PLAYER_TOOK_DAMAGE);
}

/* <1f094e> ../cstrike/dlls/career_tasks.cpp:784 */
void CCareerTaskManager::HandleDeath(int team, CBasePlayer *pAttacker)
{
	int enemyTeam = (Q_strcmp(humans_join_team.string, "CT") != 0) ? CT : TERRORIST;
	int numEnemies = 0;

	if (enemyTeam != team)
		return;

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex( i );

		if (pPlayer && pPlayer->m_iTeam == enemyTeam && pPlayer->IsAlive())
			++numEnemies;
	}

	if (!numEnemies)
	{
		HandleEvent(EVENT_KILL_ALL);
	}
}

/* <1f0a5d> ../cstrike/dlls/career_tasks.cpp:805 */
bool CCareerTaskManager::AreAllTasksComplete(void)
{
	for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		if (!(*it)->IsComplete())
			return false;
	}

	return true;
}

/* <1f0abc> ../cstrike/dlls/career_tasks.cpp:818 */
int CCareerTaskManager::GetNumRemainingTasks(void)
{
	int ret = 0;
	for (CareerTaskListIt it = m_tasks.begin(); it != m_tasks.end(); ++it)
	{
		if (!(*it)->IsComplete())
			ret++;
	}

	return ret;
}

/* <1f0b33> ../cstrike/dlls/career_tasks.cpp:832 */
float CCareerTaskManager::GetRoundElapsedTime(void)
{
	return (gpGlobals->time - m_roundStartTime);
}

/* <1f0b56> ../cstrike/dlls/career_tasks.cpp:838 */
void CCareerTaskManager::LatchRoundEndMessage(void)
{
	m_shouldLatchRoundEndMessage = true;
}

/* <1f0b81> ../cstrike/dlls/career_tasks.cpp:844 */
void CCareerTaskManager::UnlatchRoundEndMessage(void)
{
	m_shouldLatchRoundEndMessage = false;
	HandleEvent(m_roundEndMessage);
}

#ifdef HOOK_GAMEDLL

void CCareerTask::OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	OnEvent_(event, pAttacker, pVictim);
}

void CCareerTask::Reset(void)
{
	Reset_();
}

void CPreventDefuseTask::OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim)
{
	OnEvent_(event, pAttacker, pVictim);
}

void CPreventDefuseTask::Reset(void)
{
	Reset_();
}

#endif // HOOK_GAMEDLL
