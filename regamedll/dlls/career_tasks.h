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

#ifndef CAREER_TASK_H
#define CAREER_TASK_H
#ifdef _WIN32
#pragma once
#endif

#include <list>

/* <1ef43f> ../cstrike/dlls/career_tasks.cpp:192 */
class CCareerTask
{
public:
	CCareerTask(void) {};
	CCareerTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);
public:
	virtual void OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	virtual void Reset(void);
	virtual bool IsTaskCompletableThisRound(void) { return true; }

#ifdef HOOK_GAMEDLL

	void OnEvent_(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void Reset_(void);

#endif // HOOK_GAMEDLL

public:
	static CCareerTask *NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);

	void OnWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void OnWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker);

	bool IsComplete(void)		{ return m_isComplete;}
	const char *GetTaskName(void)	{ return m_name; }

	int GetWeaponId(void)		{ return m_weaponId; }
	int GetWeaponClassId(void)	{ return m_weaponClassId; }

	bool IsValidFor(CBasePlayer *pPlayer)	{ return true; }
	void SendPartialNotification(void);

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

};/* size: 44, cachelines: 1, members: 15 */

typedef std::STD_LIST<CCareerTask *> CareerTaskList;
typedef CareerTaskList::iterator CareerTaskListIt;

typedef CCareerTask *(*TaskFactoryFunction)(const char *taskName, GameEventType event, const char *weaponName, int eventCount, bool mustLive, bool crossRounds, int nextId, bool isComplete);

/* <1ef56d> ../cstrike/dlls/career_tasks.cpp:139 */
class CPreventDefuseTask: public CCareerTask
{
public:
	CPreventDefuseTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);
public:
	virtual void OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	virtual void Reset(void);
	virtual bool IsTaskCompletableThisRound(void) { return m_bombPlantedThisRound && !m_defuseStartedThisRound; }

#ifdef HOOK_GAMEDLL

	void OnEvent_(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void Reset_(void);

#endif // HOOK_GAMEDLL

public:
	static CCareerTask *NewTask(const char *taskName, GameEventType event, const char *weaponName, int n, bool mustLive, bool crossRounds, int id, bool isComplete);

protected:
	bool m_bombPlantedThisRound;
	bool m_defuseStartedThisRound;

};/* size: 48, cachelines: 1, members: 3 */

/* <1efed1> ../cstrike/dlls/career_tasks.cpp:636 */
class CCareerTaskManager
{
public:
	CCareerTaskManager(void);

public:
	static void Create(void);

	void Reset(bool deleteTasks = true);
	void AddTask(const char *taskName, const char *weaponName, int eventCount, bool mustLive, bool crossRounds, bool isComplete);

	void HandleEvent(GameEventType event, CBasePlayer *pAttacker = NULL, CBasePlayer *pVictim = NULL);
	void HandleEnemyKill(bool wasBlind, const char *weaponName, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void HandleWeaponKill(int weaponId, int weaponClassId, bool headshot, bool killerHasShield, CBasePlayer *pAttacker, CBasePlayer *pVictim);
	void HandleDeath(int team, CBasePlayer *pAttacker = NULL);
	void HandleWeaponInjury(int weaponId, int weaponClassId, bool attackerHasShield, CBasePlayer *pAttacker);
	void HandleEnemyInjury(const char *weaponName, bool attackerHasShield, CBasePlayer *pAttacker);

	bool AreAllTasksComplete(void);
	int GetNumRemainingTasks(void);
	float GetRoundElapsedTime(void);
	int GetTaskTime(void) { return m_taskTime; }
	void SetFinishedTaskTime(int val);
	int GetFinishedTaskTime(void) { return m_finishedTaskTime; }
	int GetFinishedTaskRound(void) { return m_finishedTaskRound; }
	CareerTaskList *GetTasks(void) { return &m_tasks; }
	void LatchRoundEndMessage(void);
	void UnlatchRoundEndMessage(void);

private:
	CareerTaskList m_tasks;

	int m_nextId;
	float m_roundStartTime;
	int m_taskTime;
	int m_finishedTaskTime;

	int m_finishedTaskRound;
	GameEventType m_roundEndMessage;
	bool m_shouldLatchRoundEndMessage;

};/* size: 36, cachelines: 1, members: 8 */

struct TaskInfo
{
	const char *taskName;
	GameEventType event;
	TaskFactoryFunction factory;

};/* size: 12, cachelines: 1, members: 3 */

#ifdef HOOK_GAMEDLL

#define TheCareerTasks (*pTheCareerTasks)
#define taskInfo (*ptaskInfo)

#endif // HOOK_GAMEDLL

extern CCareerTaskManager *TheCareerTasks;
extern const TaskInfo taskInfo[21];

#endif // CAREER_TASK_H
