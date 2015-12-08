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

#ifndef TUTOR_BASE_TUTOR_H
#define TUTOR_BASE_TUTOR_H
#ifdef _WIN32
#pragma once
#endif

class TutorMessageEvent
{
public:
	TutorMessageEvent(int mid, int duplicateID, float time, float lifetime, int priority);
	virtual ~TutorMessageEvent(void);

	bool IsActive(float time);
	int GetPriority(void);
	float GetTimeActive(float time);
	void SetActivationTime(float time);
	int GetID(void);
	int GetDuplicateID(void);
	void AddParameter(char *str);
	char *GetNextParameter(char *buf, int buflen);
	int GetNumParameters(void);
	void SetNext(TutorMessageEvent *next);
	TutorMessageEvent *GetNext(void);

private:
	int m_messageID;
	int m_duplicateID;
	float m_activationTime;
	float m_lifetime;
	int m_priority;
	int m_numParameters;
	struct TutorMessageEventParam *m_paramList;
	TutorMessageEvent *m_next;

};/* size: 36, cachelines: 1, members: 9 */

class CBaseTutor
{
public:
	CBaseTutor(void);
	virtual ~CBaseTutor(void);

	virtual void TutorThink(float time) = 0;
	virtual void PurgeMessages(void) = 0;
	virtual void CallEventHandler(GameEventType event, CBaseEntity *entity, CBaseEntity *other) = 0;
	virtual void ShowTutorMessage(TutorMessageEvent *event) = 0;

	virtual bool IsEntityInViewOfPlayer(CBaseEntity *entity, CBasePlayer *player);
	virtual bool IsBombsiteInViewOfPlayer(CBaseEntity *entity, CBasePlayer *player);
	virtual bool IsEntityInBombsite(CBaseEntity *bombsite, CBaseEntity *entity);
	virtual bool IsPlayerLookingAtPosition(Vector *origin, CBasePlayer *player);
	virtual bool IsPlayerLookingAtEntity(CBaseEntity *entity, CBasePlayer *player);

	virtual void HandleShotFired(Vector source, Vector target) = 0;
	virtual struct TutorMessage *GetTutorMessageDefinition(int messageID) = 0;

#ifdef HOOK_GAMEDLL

	bool IsEntityInViewOfPlayer_(CBaseEntity *entity, CBasePlayer *player);
	bool IsBombsiteInViewOfPlayer_(CBaseEntity *entity, CBasePlayer *player);
	bool IsEntityInBombsite_(CBaseEntity *bombsite, CBaseEntity *entity);
	bool IsPlayerLookingAtPosition_(Vector *origin, CBasePlayer *player);
	bool IsPlayerLookingAtEntity_(CBaseEntity *entity, CBasePlayer *player);

#endif // HOOK_GAMEDLL

public:
	void StartFrame(float time);
	void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL);

	void ShotFired(Vector source, Vector target);
	void DisplayMessageToPlayer(CBasePlayer *player, int id, const char *szMessage, TutorMessageEvent *event);
	NOXREF void DrawLineToEntity(CBasePlayer *player, int entindex, int id);
	void DisplayNewStateDescriptionToPlayer(void);
	void CloseCurrentWindow(void);
	void CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	void CalculatePathForObjective(CBaseEntity *player);
	bool DoMessagesHaveSameID(int id1, int id2);

protected:
	CBaseTutorStateSystem *m_stateSystem;
	TutorMessageEvent *m_eventList;
	float m_deadAirStartTime;
	float m_roundStartTime;

};/* size: 20, cachelines: 1, members: 5 */

#ifdef HOOK_GAMEDLL

#define TheTutor (*pTheTutor)

#endif // HOOK_GAMEDLL

extern CBaseTutor *TheTutor;

#endif // TUTOR_BASE_TUTOR_H
