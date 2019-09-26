/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#include "precompiled.h"

// Move towards currently heard noise
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

void InvestigateNoiseState::OnEnter(CCSBot *me)
{
	AttendCurrentNoise(me);
}

// Use TravelDistance instead of distance...
void InvestigateNoiseState::OnUpdate(CCSBot *me)
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

void InvestigateNoiseState::OnExit(CCSBot *me)
{
	// reset to run mode in case we were sneaking about
	me->Run();
}
