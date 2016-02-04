#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

char *const g_TutorStateStrings[20] =
{
	"#Cstrike_TutorState_Undefined",
	"#Cstrike_TutorState_Looking_For_Hostage",
	"#Cstrike_TutorState_Escorting_Hostage",
	"#Cstrike_TutorState_Following_Hostage_Escort",
	"#Cstrike_TutorState_Moving_To_Bombsite",
	"#Cstrike_TutorState_Looking_For_Bomb_Carrier",
	"#Cstrike_TutorState_Guarding_Loose_Bomb",
	"#Cstrike_TutorState_Defusing_Bomb",
	"#Cstrike_TutorState_Guarding_Hostage",
	"#Cstrike_TutorState_Moving_To_Intercept_Enemy",
	"#Cstrike_TutorState_Looking_For_Hostage_Escort",
	"#Cstrike_TutorState_Attacking_Hostage_Escort",
	"#Cstrike_TutorState_Escorting_Bomb_Carrier",
	"#Cstrike_TutorState_Moving_To_Bomb_Site",
	"#Cstrike_TutorState_Planting_Bomb",
	"#Cstrike_TutorState_Guarding_Bomb",
	"#Cstrike_TutorState_Looking_For_Loose_Bomb",
	"#Cstrike_TutorState_Running_Away_From_Ticking_Bomb",
	"#Cstrike_TutorState_Buy_Time",
	"#Cstrike_TutorState_Waiting_For_Start"
};

#endif // HOOK_GAMEDLL

/* <22bf8e> ../cstrike/dlls/tutor_cs_states.cpp:53 */
CCSTutorStateSystem::CCSTutorStateSystem()
{
	m_currentState = new CCSTutorUndefinedState;
}

/* <22bd56> ../cstrike/dlls/tutor_cs_states.cpp:58 */
CCSTutorStateSystem::~CCSTutorStateSystem()
{
	if (m_currentState != NULL)
	{
		delete m_currentState;
		m_currentState = NULL;
	}
}

/* <22bccf> ../cstrike/dlls/tutor_cs_states.cpp:68 */
bool CCSTutorStateSystem::__MAKE_VHOOK(UpdateState)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (m_currentState == NULL)
	{
		m_currentState = new CCSTutorUndefinedState;
	}

	if (m_currentState != NULL)
	{
		TutorStateType nextStateType = static_cast<TutorStateType>(m_currentState->CheckForStateTransition(event, entity, other));

		if (nextStateType != TUTORSTATE_UNDEFINED)
		{
			if (m_currentState != NULL)
			{
				delete m_currentState;
			}

			m_currentState = NULL;
			m_currentState = ConstructNewState(nextStateType);

			return true;
		}
	}

	return false;
}

/* <22b96f> ../cstrike/dlls/tutor_cs_states.cpp:108 */
char *CCSTutorStateSystem::__MAKE_VHOOK(GetCurrentStateString)()
{
	if (m_currentState != NULL)
	{
		return m_currentState->GetStateString();
	}

	return NULL;
}

/* <22bbfe> ../cstrike/dlls/tutor_cs_states.cpp:118 */
CBaseTutorState *CCSTutorStateSystem::__MAKE_VHOOK(ConstructNewState)(int stateType)
{
	CBaseTutorState *ret = NULL;

	if (stateType != TUTORSTATE_UNDEFINED)
	{
		if (stateType == TUTORSTATE_BUYTIME)
		{
			ret = new CCSTutorBuyMenuState;
		}
		else if (stateType == TUTORSTATE_WAITING_FOR_START)
		{
			ret = new CCSTutorWaitingForStartState;
		}
	}
	else
	{
		ret = new CCSTutorUndefinedState;
	}

	return ret;
}

/* <22bfcb> ../cstrike/dlls/tutor_cs_states.cpp:141 */
CCSTutorUndefinedState::CCSTutorUndefinedState()
{
	m_type = 0;
}

/* <22bb33> ../cstrike/dlls/tutor_cs_states.cpp:146 */
CCSTutorUndefinedState::~CCSTutorUndefinedState()
{
	;
}

/* <22bdd8> ../cstrike/dlls/tutor_cs_states.cpp:150 */
int CCSTutorUndefinedState::__MAKE_VHOOK(CheckForStateTransition)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (event == EVENT_PLAYER_SPAWNED)
	{
		return HandlePlayerSpawned(entity, other);
	}

	return 0;
}

/* <22bfed> ../cstrike/dlls/tutor_cs_states.cpp:163 */
int CCSTutorUndefinedState::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer)
		{
			// flags
			return TUTOR_STATE_FLAG_1;
		}
	}

	return 0;
}

/* <22b995> ../cstrike/dlls/tutor_cs_states.cpp:190 */
char *CCSTutorUndefinedState::__MAKE_VHOOK(GetStateString)()
{
	return NULL;
}

/* <22c03e> ../cstrike/dlls/tutor_cs_states.cpp:198 */
CCSTutorWaitingForStartState::CCSTutorWaitingForStartState()
{
	m_type = (TUTORMESSAGETYPE_ENEMY_DEATH | TUTORMESSAGETYPE_BUY);
}

/* <22bab6> ../cstrike/dlls/tutor_cs_states.cpp:203 */
CCSTutorWaitingForStartState::~CCSTutorWaitingForStartState()
{
	;
}

/* <22beca> ../cstrike/dlls/tutor_cs_states.cpp:207 */
int CCSTutorWaitingForStartState::__MAKE_VHOOK(CheckForStateTransition)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_PLAYER_SPAWNED:
		return HandlePlayerSpawned(entity, other);
	case EVENT_BUY_TIME_START:
		return HandleBuyTimeStart(entity, other);
	}

	return 0;
}

/* <22b9bb> ../cstrike/dlls/tutor_cs_states.cpp:224 */
char *CCSTutorWaitingForStartState::__MAKE_VHOOK(GetStateString)()
{
	return g_TutorStateStrings[m_type];
}

/* <22c060> ../cstrike/dlls/tutor_cs_states.cpp:230 */
int CCSTutorWaitingForStartState::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer)
		{
			// flags
			return TUTOR_STATE_FLAG_1;
		}
	}

	return 0;
}

/* <22c0b1> ../cstrike/dlls/tutor_cs_states.cpp:257 */
int CCSTutorWaitingForStartState::HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other)
{
	return TUTOR_STATE_FLAG_2;
}

/* <22c0e2> ../cstrike/dlls/tutor_cs_states.cpp:266 */
CCSTutorBuyMenuState::CCSTutorBuyMenuState()
{
	m_type = (TUTORMESSAGETYPE_DEFAULT | TUTORMESSAGETYPE_FRIEND_DEATH | TUTORMESSAGETYPE_BUY);
}

/* <22ba5a> ../cstrike/dlls/tutor_cs_states.cpp:271 */
CCSTutorBuyMenuState::~CCSTutorBuyMenuState()
{
	;
}

/* <22b9e1> ../cstrike/dlls/tutor_cs_states.cpp:275 */
int CCSTutorBuyMenuState::__MAKE_VHOOK(CheckForStateTransition)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (event == EVENT_ROUND_START)
	{
		return HandleRoundStart(entity, other);
	}

	return 0;
}

/* <22ba34> ../cstrike/dlls/tutor_cs_states.cpp:288 */
char *CCSTutorBuyMenuState::__MAKE_VHOOK(GetStateString)()
{
	return g_TutorStateStrings[m_type];
}

/* <22c104> ../cstrike/dlls/tutor_cs_states.cpp:293 */
int CCSTutorBuyMenuState::HandleRoundStart(CBaseEntity *entity, CBaseEntity *other)
{
	return TUTOR_STATE_FLAG_1;
}
