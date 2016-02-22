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

#endif

CCSTutorStateSystem::CCSTutorStateSystem()
{
	m_currentState = new CCSTutorUndefinedState;
}

CCSTutorStateSystem::~CCSTutorStateSystem()
{
	if (m_currentState != NULL)
	{
		delete m_currentState;
		m_currentState = NULL;
	}
}

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
			delete m_currentState;
			m_currentState = ConstructNewState(nextStateType);
			return true;
		}
	}

	return false;
}

char *CCSTutorStateSystem::__MAKE_VHOOK(GetCurrentStateString)()
{
	if (m_currentState != NULL)
	{
		return m_currentState->GetStateString();
	}

	return NULL;
}

CBaseTutorState *CCSTutorStateSystem::__MAKE_VHOOK(ConstructNewState)(int stateType)
{
	switch (stateType)
	{
	case TUTORSTATE_BUYTIME:		return new CCSTutorBuyMenuState;
	case TUTORSTATE_WAITING_FOR_START:	return new CCSTutorWaitingForStartState;
	case TUTORSTATE_UNDEFINED:		return new CCSTutorUndefinedState;
	}

	return NULL;
}

CCSTutorUndefinedState::CCSTutorUndefinedState()
{
	m_type = 0;
}

CCSTutorUndefinedState::~CCSTutorUndefinedState()
{
	;
}

int CCSTutorUndefinedState::__MAKE_VHOOK(CheckForStateTransition)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (event == EVENT_PLAYER_SPAWNED)
	{
		return HandlePlayerSpawned(entity, other);
	}

	return 0;
}

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

char *CCSTutorUndefinedState::__MAKE_VHOOK(GetStateString)()
{
	return NULL;
}

CCSTutorWaitingForStartState::CCSTutorWaitingForStartState()
{
	m_type = (TUTORMESSAGETYPE_ENEMY_DEATH | TUTORMESSAGETYPE_BUY);
}

CCSTutorWaitingForStartState::~CCSTutorWaitingForStartState()
{
	;
}

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

char *CCSTutorWaitingForStartState::__MAKE_VHOOK(GetStateString)()
{
	return g_TutorStateStrings[m_type];
}

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

int CCSTutorWaitingForStartState::HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other)
{
	return TUTOR_STATE_FLAG_2;
}

CCSTutorBuyMenuState::CCSTutorBuyMenuState()
{
	m_type = (TUTORMESSAGETYPE_DEFAULT | TUTORMESSAGETYPE_FRIEND_DEATH | TUTORMESSAGETYPE_BUY);
}

CCSTutorBuyMenuState::~CCSTutorBuyMenuState()
{
	;
}

int CCSTutorBuyMenuState::__MAKE_VHOOK(CheckForStateTransition)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (event == EVENT_ROUND_START)
	{
		return HandleRoundStart(entity, other);
	}

	return 0;
}

char *CCSTutorBuyMenuState::__MAKE_VHOOK(GetStateString)()
{
	return g_TutorStateStrings[m_type];
}

int CCSTutorBuyMenuState::HandleRoundStart(CBaseEntity *entity, CBaseEntity *other)
{
	return TUTOR_STATE_FLAG_1;
}
