#include "precompiled.h"

/* <21bf94> ../cstrike/dlls/tutor_base_states.cpp:6 */
CBaseTutorStateSystem::CBaseTutorStateSystem()
{
	;
}

/* <21bec7> ../cstrike/dlls/tutor_base_states.cpp:10 */
CBaseTutorStateSystem::~CBaseTutorStateSystem()
{
	;
}

/* <21bfb5> ../cstrike/dlls/tutor_base_states.cpp:14 */
int CBaseTutorStateSystem::GetCurrentStateType() const
{
	if (m_currentState != NULL)
	{
		return m_currentState->GetType();
	}

	return 0;
}

/* <21c00d> ../cstrike/dlls/tutor_base_states.cpp:28 */
CBaseTutorState::CBaseTutorState()
{
	;
}

/* <21bcc6> ../cstrike/dlls/tutor_base_states.cpp:32 */
CBaseTutorState::~CBaseTutorState()
{
	;
}

/* <21c02e> ../cstrike/dlls/tutor_base_states.cpp:36 */
int CBaseTutorState::GetType() const
{
	return m_type;
}
