#include "precompiled.h"

CBaseTutorStateSystem::CBaseTutorStateSystem()
{
	;
}

CBaseTutorStateSystem::~CBaseTutorStateSystem()
{
	;
}

int CBaseTutorStateSystem::GetCurrentStateType() const
{
	if (m_currentState)
	{
		return m_currentState->GetType();
	}

	return 0;
}

CBaseTutorState::CBaseTutorState()
{
	;
}

CBaseTutorState::~CBaseTutorState()
{
	;
}

int CBaseTutorState::GetType() const
{
	return m_type;
}
