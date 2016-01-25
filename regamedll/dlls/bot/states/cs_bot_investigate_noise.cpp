#include "precompiled.h"

// Move towards currently heard noise

/* <5b3114> ../cstrike/dlls/bot/states/cs_bot_investigate_noise.cpp:17 */
void InvestigateNoiseState::AttendCurrentNoise(CCSBot *me)
{
	if (!me->IsNoiseHeard() && me->GetNoisePosition())
		return;

	// remember where the noise we heard was
	m_checkNoisePosition = *me->GetNoisePosition();

	// tell our teammates (unless the noise is obvious, like gunfire)
	if (me->IsWellPastSafe() && me->HasNotSeenEnemyForLongTime() && me->GetNoisePriority() != PRIORITY_HIGH)
		me->GetChatter()->HeardNoise(me->GetNoisePosition());

	// figure out how to get to the noise		
	me->PrintIfWatched("Attending to noise...\n");
	me->ComputePath(me->GetNoiseArea(), &m_checkNoisePosition, SAFEST_ROUTE);

	// consume the noise
	me->ForgetNoise();
}

/* <5b2f37> ../cstrike/dlls/bot/states/cs_bot_investigate_noise.cpp:38 */
void InvestigateNoiseState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
	AttendCurrentNoise(me);
}

// Use TravelDistance instead of distance...

/* <5b2fa2> ../cstrike/dlls/bot/states/cs_bot_investigate_noise.cpp:47 */
void InvestigateNoiseState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
	float newNoiseDist;
	if (me->ShouldInvestigateNoise(&newNoiseDist))
	{
		Vector toOldNoise = m_checkNoisePosition - me->pev->origin;
		const float muchCloserDist = 100.0f;
		if (toOldNoise.IsLengthGreaterThan(newNoiseDist + muchCloserDist))
		{
			// new sound is closer
			AttendCurrentNoise(me);
		}
	}

	// if the pathfind fails, give up
	if (!me->HasPath())
	{
		me->Idle();
		return;
	}

	// look around
	me->UpdateLookAround();

	// get distance remaining on our path until we reach the source of the noise
	float noiseDist = (m_checkNoisePosition - me->pev->origin).Length();

	if (me->IsUsingKnife())
	{
		if (me->IsHurrying())
			me->Run();
		else
			me->Walk();
	}
	else
	{
		const float closeToNoiseRange = 1500.0f;
		if (noiseDist < closeToNoiseRange)
		{
			// if we dont have many friends left, or we are alone, and we are near noise source, sneak quietly
			if (me->GetFriendsRemaining() <= 2 && !me->IsHurrying())
			{
				me->Walk();
			}
			else
			{
				me->Run();
			}
		}
		else
		{
			me->Run();
		}
	}

	// if we can see the noise position and we're close enough to it and looking at it,
	// we don't need to actually move there (it's checked enough)
	const float closeRange = 200.0f;
	if (noiseDist < closeRange)
	{
		if (me->IsLookingAtPosition(&m_checkNoisePosition) && me->IsVisible(&m_checkNoisePosition))
		{
			// can see noise position
			me->PrintIfWatched("Noise location is clear.\n");
			//me->ForgetNoise();
			me->Idle();
			return;
		}
	}

	// move towards noise
	if (me->UpdatePathMovement() != CCSBot::PROGRESSING)
	{
		me->Idle();
	}
}

/* <5b2e95> ../cstrike/dlls/bot/states/cs_bot_investigate_noise.cpp:129 */
void InvestigateNoiseState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
	// reset to run mode in case we were sneaking about
	me->Run();
}

#ifdef HOOK_GAMEDLL

void InvestigateNoiseState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void InvestigateNoiseState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

void InvestigateNoiseState::OnExit(CCSBot *me)
{
	OnExit_(me);
}

#endif // HOOK_GAMEDLL
