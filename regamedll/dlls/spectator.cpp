#include "precompiled.h"

void CBaseSpectator::SpectatorConnect()
{
	pev->flags = FL_SPECTATOR;
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NOCLIP;

	m_pGoalEnt = nullptr;
}

void CBaseSpectator::SpectatorDisconnect()
{
	;
}

void CBaseSpectator::SpectatorImpulseCommand()
{
	static edict_t *pGoal = nullptr;

	edict_t *pPreviousGoal;
	edict_t *pCurrentGoal;
	BOOL bFound;

	switch (pev->impulse)
	{
		case 1:
		{
			// teleport the spectator to the next spawn point
			// note that if the spectator is tracking, this doesn't do
			// much
			pPreviousGoal = pGoal;
			pCurrentGoal  = pGoal;
			// Start at the current goal, skip the world, and stop if we looped
			// back around

			bFound = FALSE;
			while (true)
			{
				pCurrentGoal = FIND_ENTITY_BY_CLASSNAME(pCurrentGoal, "info_player_deathmatch");

				// Looped around, failure
				if (pCurrentGoal == pPreviousGoal)
				{
					ALERT(at_console, "Could not find a spawn spot.\n");
					break;
				}

				// Found a non-world entity, set success, otherwise, look for the next one.
				if (!FNullEnt(pCurrentGoal))
				{
					bFound = TRUE;
					break;
				}
			}

			// Didn't find a good spot.
			if (!bFound)
				break;

			pGoal = pCurrentGoal;
			UTIL_SetOrigin(pev, pGoal->v.origin);

			pev->angles = pGoal->v.angles;
			pev->fixangle = 0;
			break;
		}
		default:
			ALERT(at_console, "Unknown spectator impulse\n");
			break;
	}

	pev->impulse = 0;
}

void CBaseSpectator::SpectatorThink()
{
	if (!(pev->flags & FL_SPECTATOR))
	{
		pev->flags = FL_SPECTATOR;
	}

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NOCLIP;

	if (pev->impulse)
	{
		SpectatorImpulseCommand();
	}
}

void CBaseSpectator::Spawn()
{
	pev->flags = FL_SPECTATOR;
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NOCLIP;

	m_pGoalEnt = nullptr;
}
