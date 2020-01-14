/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#pragma once

#include <list>

class CCareerTask
{
public:
	CCareerTask() {};
	CCareerTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);

	virtual ~CCareerTask() {}

public:
	virtual void OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	virtual void Reset();
	virtual bool IsTaskCompletableThisRound() { return true; }

public:
	static CCareerTask *NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);

	void OnWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void OnWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker);

	bool IsComplete() { return m_isComplete; }
	const char *GetTaskName() { return m_name; }

	int GetWeaponId() { return m_weaponId; }
	int GetWeaponClassId() { return m_weaponClassId; }

	bool IsValidFor(CBasePlayer *pPlayer) { return true; }
	void SendPartialNotification();

private:
	bool m_isComplete;
	const char *m_name;
	int m_id;
	GameEventType m_event;
	int m_eventsNeeded;
	int m_eventsSeen;
	bool m_mustLive;
	bool m_crossRounds;
	bool m_diedThisRound;
	int m_weaponId;
	int m_weaponClassId;
	bool m_rescuer;
	bool m_defuser;
	bool m_vip;
};

typedef std::list<CCareerTask *> CareerTaskList;
typedef CareerTaskList::iterator CareerTaskListIt;

using TaskFactoryFunction = CCareerTask *(*)(const char *taskName, GameEventType event, const char *weaponName, int eventCount, bool mustLive, bool crossRounds, int nextId, bool isComplete);

struct TaskInfo
{
	const char *taskName;
	GameEventType event;
	TaskFactoryFunction factory;
};

class CPreventDefuseTask: public CCareerTask
{
public:
	CPreventDefuseTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);

public:
	virtual void OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	virtual void Reset();
	virtual bool IsTaskCompletableThisRound() { return m_bombPlantedThisRound && !m_defuseStartedThisRound; }

public:
	static CCareerTask *NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);

protected:
	bool m_bombPlantedThisRound;
	bool m_defuseStartedThisRound;
};

class CCareerTaskManager
{
public:
	CCareerTaskManager();

public:
	static void Create();

	void Reset(bool deleteTasks = true);
	void AddTask(const char *taskName, const char *weaponName, int eventCount, bool mustLive, bool crossRounds, bool isComplete);

	void HandleEvent(GameEventType event, CBasePlayer *pAttacker = nullptr, CBasePlayer *pVictim = nullptr);
	void HandleEnemyKill(bool wasBlind, const char *weaponName, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void HandleWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void HandleDeath(int team, CBasePlayer *pAttacker = nullptr);
	void HandleWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker);
	void HandleEnemyInjury(const char *weaponName, bool attackerHasShield, CBasePlayer *pAttacker);

	bool AreAllTasksComplete();
	int GetNumRemainingTasks();
	float GetRoundElapsedTime();
	int GetTaskTime() { return m_taskTime; }
	void SetFinishedTaskTime(int val);
	int GetFinishedTaskTime() { return m_finishedTaskTime; }
	int GetFinishedTaskRound() { return m_finishedTaskRound; }
	CareerTaskList *GetTasks() { return &m_tasks; }
	void LatchRoundEndMessage();
	void UnlatchRoundEndMessage();

private:
	static const TaskInfo m_taskInfo[];

	CareerTaskList m_tasks;

	int m_nextId;
	float m_roundStartTime;
	int m_taskTime;
	int m_finishedTaskTime;

	int m_finishedTaskRound;
	GameEventType m_roundEndMessage;
	bool m_shouldLatchRoundEndMessage;
};

extern CCareerTaskManager *TheCareerTasks;
