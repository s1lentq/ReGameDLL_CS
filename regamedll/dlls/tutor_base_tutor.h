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

class TutorMessageEvent
{
public:
	TutorMessageEvent(int mid, int duplicateID, float time, float lifetime, int priority);
	virtual ~TutorMessageEvent();

	bool IsActive(float time);
	int GetPriority();
	float GetTimeActive(float time);
	void SetActivationTime(float time);
	int GetID();
	int GetDuplicateID();
	void AddParameter(char *str);
	char *GetNextParameter(char *buf, int buflen);
	int GetNumParameters();
	void SetNext(TutorMessageEvent *next);
	TutorMessageEvent *GetNext();

private:
	int m_messageID;
	int m_duplicateID;
	float m_activationTime;
	float m_lifetime;
	int m_priority;
	int m_numParameters;
	struct TutorMessageEventParam *m_paramList;
	TutorMessageEvent *m_next;
};

class CBaseTutor
{
public:
	CBaseTutor();

	virtual ~CBaseTutor();
	virtual void TutorThink(float time) = 0;
	virtual void PurgeMessages() = 0;
	virtual void CallEventHandler(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther) = 0;
	virtual void ShowTutorMessage(TutorMessageEvent *event) = 0;

	virtual bool IsEntityInViewOfPlayer(CBaseEntity *pEntity, CBasePlayer *pPlayer);
	virtual bool IsBombsiteInViewOfPlayer(CBaseEntity *pEntity, CBasePlayer *pPlayer);
	virtual bool IsEntityInBombsite(CBaseEntity *bombsite, CBaseEntity *pEntity);
	virtual bool IsPlayerLookingAtPosition(Vector *origin, CBasePlayer *pPlayer);
	virtual bool IsPlayerLookingAtEntity(CBaseEntity *pEntity, CBasePlayer *pPlayer);

	virtual void HandleShotFired(Vector source, Vector target) = 0;
	virtual struct TutorMessage *GetTutorMessageDefinition(int messageID) = 0;

public:
	void StartFrame(float time);
	void OnEvent(GameEventType event, CBaseEntity *pEntity = nullptr, CBaseEntity *pOther = nullptr);

	void ShotFired(Vector source, Vector target);
	void DisplayMessageToPlayer(CBasePlayer *pPlayer, int id, const char *szMessage, TutorMessageEvent *event);
	void DrawLineToEntity(CBasePlayer *pPlayer, int entindex, int id);
	void DisplayNewStateDescriptionToPlayer();
	void CloseCurrentWindow();
	void CheckForStateTransition(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther);
	void CalculatePathForObjective(CBaseEntity *pPlayer);
	bool DoMessagesHaveSameID(int id1, int id2);

protected:
	CBaseTutorStateSystem *m_stateSystem;
	TutorMessageEvent *m_eventList;
	float m_deadAirStartTime;
	float m_roundStartTime;
};

extern CBaseTutor *TheTutor;
