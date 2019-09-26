#include "precompiled.h"

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

bool CCSTutorStateSystem::UpdateState(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (!m_currentState)
	{
		m_currentState = new CCSTutorUndefinedState;
	}

	if (m_currentState)
	{
		TutorStateType nextStateType = m_currentState->CheckForStateTransition(event, pEntity, pOther);
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

TutorStateType CCSTutorUndefinedState::CheckForStateTransition(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (event == EVENT_PLAYER_SPAWNED)
	{
		return HandlePlayerSpawned(pEntity, pOther);
	}

	return TUTORSTATE_UNDEFINED;
}

TutorStateType CCSTutorUndefinedState::HandlePlayerSpawned(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
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

TutorStateType CCSTutorWaitingForStartState::CheckForStateTransition(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	switch (event)
	{
	case EVENT_PLAYER_SPAWNED:
		return HandlePlayerSpawned(pEntity, pOther);
	case EVENT_BUY_TIME_START:
		return HandleBuyTimeStart(pEntity, pOther);
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

	return m_TutorStateStrings[m_type];
}

TutorStateType CCSTutorWaitingForStartState::HandlePlayerSpawned(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
		if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer)
		{
			return TUTORSTATE_WAITING_FOR_START;
		}
	}

	return TUTORSTATE_UNDEFINED;
}

TutorStateType CCSTutorWaitingForStartState::HandleBuyTimeStart(CBaseEntity *pEntity, CBaseEntity *pOther)
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

TutorStateType CCSTutorBuyMenuState::CheckForStateTransition(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (event == EVENT_ROUND_START)
	{
		return HandleRoundStart(pEntity, pOther);
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

	return m_TutorStateStrings[m_type];
}

TutorStateType CCSTutorBuyMenuState::HandleRoundStart(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	return TUTORSTATE_WAITING_FOR_START;
}
