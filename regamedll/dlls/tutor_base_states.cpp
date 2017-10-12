#include "precompiled.h"

CBaseTutorStateSystem::CBaseTutorStateSystem()
{
	m_currentState = nullptr;
}

CBaseTutorStateSystem::~CBaseTutorStateSystem()
{
	;
}

TutorStateType CBaseTutorStateSystem::GetCurrentStateType() const
{
	if (m_currentState)
	{
		return m_currentState->GetType();
	}

	return TUTORSTATE_UNDEFINED;
}

CBaseTutorState::CBaseTutorState()
{
	m_type = TUTORSTATE_UNDEFINED;
}

CBaseTutorState::~CBaseTutorState()
{
	;
}

TutorStateType CBaseTutorState::GetType() const
{
	return m_type;
}
