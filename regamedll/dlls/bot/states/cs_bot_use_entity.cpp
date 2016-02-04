#include "precompiled.h"

// Face the entity and "use" it
// NOTE: This state assumes we are standing in range of the entity to be used, with no obstructions.

/* <5e3017> ../cstrike/dlls/bot/states/cs_bot_use_entity.cpp:17 */
void UseEntityState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
	;
}

/* <5e308c> ../cstrike/dlls/bot/states/cs_bot_use_entity.cpp:21 */
void UseEntityState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
	// in the very rare situation where two or more bots "used" a hostage at the same time,
	// one bot will fail and needs to time out of this state
	const float useTimeout = 5.0f;
	if (me->GetStateTimestamp() - gpGlobals->time > useTimeout)
	{
		me->Idle();
		return;
	}

	// look at the entity
	Vector pos = m_entity->pev->origin + Vector(0, 0, HumanHeight * 0.5f);
	me->SetLookAt("Use entity", &pos, PRIORITY_HIGH);

	// if we are looking at the entity, "use" it and exit
	if (me->IsLookingAtPosition(&pos))
	{
		if (TheCSBots()->GetScenario() == CCSBotManager::SCENARIO_RESCUE_HOSTAGES
			&& me->m_iTeam == CT
			&& me->GetTask() == CCSBot::COLLECT_HOSTAGES)
		{
			// we are collecting a hostage, assume we were successful - the update check will correct us if we weren't
			me->IncreaseHostageEscortCount();
		}

		me->UseEnvironment();
		me->Idle();
	}
}

/* <5e304a> ../cstrike/dlls/bot/states/cs_bot_use_entity.cpp:54 */
void UseEntityState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
	me->ClearLookAt();
	me->ResetStuckMonitor();
}
