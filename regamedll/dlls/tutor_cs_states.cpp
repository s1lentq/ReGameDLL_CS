#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

const char *g_TutorStateStrings[] =
{
	"#Cstrike_TutorState_Undefined",						// TUTORSTATE_UNDEFINED
	"#Cstrike_TutorState_Looking_For_Hostage",				// TUTORSTATE_LOOKING_FOR_HOSTAGE
	"#Cstrike_TutorState_Escorting_Hostage",				// TUTORSTATE_ESCORTING_HOSTAGE
	"#Cstrike_TutorState_Following_Hostage_Escort",			// TUTORSTATE_FOLLOWING_HOSTAGE_ESCORT
	"#Cstrike_TutorState_Moving_To_Bombsite",				// TUTORSTATE_MOVING_TO_BOMBSITE,
	"#Cstrike_TutorState_Looking_For_Bomb_Carrier",			// TUTORSTATE_LOOKING_FOR_BOMB_CARRIER
	"#Cstrike_TutorState_Guarding_Loose_Bomb",				// TUTORSTATE_GUARDING_LOOSE_BOMB
	"#Cstrike_TutorState_Defusing_Bomb",					// TUTORSTATE_DEFUSING_BOMB
	"#Cstrike_TutorState_Guarding_Hostage",					// TUTORSTATE_GUARDING_HOSTAGE
	"#Cstrike_TutorState_Moving_To_Intercept_Enemy",		// TUTORSTATE_MOVING_TO_INTERCEPT_ENEMY
	"#Cstrike_TutorState_Looking_For_Hostage_Escort",		// TUTORSTATE_LOOKING_FOR_HOSTAGE_ESCORT
	"#Cstrike_TutorState_Attacking_Hostage_Escort",			// TUTORSTATE_ATTACKING_HOSTAGE_ESCORT
	"#Cstrike_TutorState_Escorting_Bomb_Carrier",			// TUTORSTATE_ESCORTING_BOMB_CARRIER
	"#Cstrike_TutorState_Moving_To_Bomb_Site",				// TUTORSTATE_MOVING_TO_BOMB_SITE
	"#Cstrike_TutorState_Planting_Bomb",					// TUTORSTATE_PLANTING_BOMB
	"#Cstrike_TutorState_Guarding_Bomb",					// TUTORSTATE_GUARDING_BOMB
	"#Cstrike_TutorState_Looking_For_Loose_Bomb",			// TUTORSTATE_LOOKING_FOR_LOOSE_BOMB
	"#Cstrike_TutorState_Running_Away_From_Ticking_Bomb",	// TUTORSTATE_RUNNING_AWAY_FROM_TICKING_BOMB
	"#Cstrike_TutorState_Buy_Time",							// TUTORSTATE_BUYTIME
	"#Cstrike_TutorState_Waiting_For_Start"					// TUTORSTATE_WAITING_FOR_START
};

#endif

CCSTutorStateSystem::CCSTutorStateSystem()
{
	m_currentState = new CCSTutorUndefinedState;
}

CCSTutorStateSystem::~CCSTutorStateSystem()
{
	if (m_currentState)
	{
		delete m_currentState;
		m_currentState = nullptr;
	}
}

bool CCSTutorStateSystem::UpdateState(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (!m_currentState)
	{
		m_currentState = new CCSTutorUndefinedState;
	}

	if (m_currentState)
	{
		TutorStateType nextStateType = m_currentState->CheckForStateTransition(event, entity, other);
		if (nextStateType != TUTORSTATE_UNDEFINED)
		{
			delete m_currentState;
			m_currentState = ConstructNewState(nextStateType);
			return true;
		}
	}

	return false;
}

const char *CCSTutorStateSystem::GetCurrentStateString()
{
	if (m_currentState)
	{
		return m_currentState->GetStateString();
	}

	return nullptr;
}

CBaseTutorState *CCSTutorStateSystem::ConstructNewState(TutorStateType stateType)
{
	switch (stateType)
	{
	case TUTORSTATE_BUYTIME:			return new CCSTutorBuyMenuState;
	case TUTORSTATE_WAITING_FOR_START:	return new CCSTutorWaitingForStartState;
	case TUTORSTATE_UNDEFINED:			return new CCSTutorUndefinedState;
	}

	return nullptr;
}

CCSTutorUndefinedState::CCSTutorUndefinedState()
{
	m_type = TUTORSTATE_UNDEFINED;
}

CCSTutorUndefinedState::~CCSTutorUndefinedState()
{
	;
}

TutorStateType CCSTutorUndefinedState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (event == EVENT_PLAYER_SPAWNED)
	{
		return HandlePlayerSpawned(entity, other);
	}

	return TUTORSTATE_UNDEFINED;
}

TutorStateType CCSTutorUndefinedState::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		CBasePlayer *pPlayer = static_cast<CBasePlayer *>(entity);
		if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer)
		{
			return TUTORSTATE_WAITING_FOR_START;
		}
	}

	return TUTORSTATE_UNDEFINED;
}

const char *CCSTutorUndefinedState::GetStateString()
{
	return nullptr;
}

CCSTutorWaitingForStartState::CCSTutorWaitingForStartState()
{
	m_type = TUTORSTATE_WAITING_FOR_START;
}

CCSTutorWaitingForStartState::~CCSTutorWaitingForStartState()
{
	;
}

TutorStateType CCSTutorWaitingForStartState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_PLAYER_SPAWNED:
		return HandlePlayerSpawned(entity, other);
	case EVENT_BUY_TIME_START:
		return HandleBuyTimeStart(entity, other);
	}

	return TUTORSTATE_UNDEFINED;
}

const char *CCSTutorWaitingForStartState::GetStateString()
{
#ifdef REGAMEDLL_FIXES
	if (m_type < TUTORSTATE_UNDEFINED || m_type > TUTORSTATE_WAITING_FOR_START)
	{
		return nullptr;
	}
#endif

	return g_TutorStateStrings[m_type];
}

TutorStateType CCSTutorWaitingForStartState::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		CBasePlayer *pPlayer = static_cast<CBasePlayer *>(entity);
		if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer)
		{
			return TUTORSTATE_WAITING_FOR_START;
		}
	}

	return TUTORSTATE_UNDEFINED;
}

TutorStateType CCSTutorWaitingForStartState::HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other)
{
	return TUTORSTATE_BUYTIME;
}

CCSTutorBuyMenuState::CCSTutorBuyMenuState()
{
	m_type = TUTORSTATE_BUYTIME;
}

CCSTutorBuyMenuState::~CCSTutorBuyMenuState()
{
	;
}

TutorStateType CCSTutorBuyMenuState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (event == EVENT_ROUND_START)
	{
		return HandleRoundStart(entity, other);
	}

	return TUTORSTATE_UNDEFINED;
}

const char *CCSTutorBuyMenuState::GetStateString()
{
#ifdef REGAMEDLL_FIXES
	if (m_type < TUTORSTATE_UNDEFINED || m_type > TUTORSTATE_WAITING_FOR_START)
	{
		return nullptr;
	}
#endif

	return g_TutorStateStrings[m_type];
}

TutorStateType CCSTutorBuyMenuState::HandleRoundStart(CBaseEntity *entity, CBaseEntity *other)
{
	return TUTORSTATE_WAITING_FOR_START;
}
