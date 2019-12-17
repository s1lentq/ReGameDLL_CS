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

const char *CBaseTutorState::m_TutorStateStrings[] =
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
