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
*/

#include "precompiled.h"

TYPEDESCRIPTION CTriggerRandom::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerRandom, m_uiTargetsUse, FIELD_INTEGER),
	DEFINE_ARRAY(CTriggerRandom, m_iszTargets, FIELD_STRING, MAX_TR_TARGETS),
	DEFINE_FIELD(CTriggerRandom, m_bActive, FIELD_CHARACTER),
	DEFINE_FIELD(CTriggerRandom, m_flMinDelay, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerRandom, m_flMaxDelay, FIELD_FLOAT)
};

LINK_ENTITY_TO_CLASS(trigger_random, CTriggerRandom, CCSTriggerRandom)
LINK_ENTITY_TO_CLASS(trigger_random_time, CTriggerRandom, CCSTriggerRandom)		// Obsolete: use trigger_random with Timed flag
LINK_ENTITY_TO_CLASS(trigger_random_unique, CTriggerRandom, CCSTriggerRandom)	// Obsolete: use trigger_ranom with Random flag. Unique Trigger Random. Randomly selects an unused trigger.

IMPLEMENT_SAVERESTORE(CTriggerRandom, CBaseDelay)

void CTriggerRandom::Spawn()
{
	m_bActive = (pev->spawnflags & SF_RANDOM_STARTON) == SF_RANDOM_STARTON;

	if (FClassnameIs(pev, "trigger_random_time"))
	{
		pev->spawnflags |= SF_RANDOM_TIMED;
	}
	else if (FClassnameIs(pev, "trigger_random_unique"))
	{
		pev->spawnflags |= SF_RANDOM_UNIQUE;

		if (pev->spawnflags & SF_RANDOM_STARTON)
		{
			pev->spawnflags &= ~SF_RANDOM_STARTON;
			pev->spawnflags |= SF_RANDOM_REUSABLE;
		}
	}

	if (pev->spawnflags & SF_RANDOM_TIMED)
	{
		pev->nextthink = gpGlobals->time + RandomDelay();
		SetThink(&CTriggerRandom::RandomThink);
	}

	if (pev->spawnflags & SF_RANDOM_UNIQUE)
	{
		InitUnique();
	}
}

void CTriggerRandom::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "target_count"))
	{
		m_uiTargetsUse = Q_atoi(pkvd->szValue);

		if (m_uiTargetsUse >= MAX_TR_TARGETS)
		{
			m_uiTargetsUse = MAX_TR_TARGETS;
		}

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "min_delay"))
	{
		m_flMinDelay = Q_atof(pkvd->szValue);

		if (m_flMaxDelay > 0 && m_flMinDelay > m_flMaxDelay)
		{
			SWAP(m_flMinDelay, m_flMaxDelay);
		}

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "max_delay"))
	{
		m_flMaxDelay = Q_atof(pkvd->szValue);

		if (m_flMinDelay > 0 && m_flMaxDelay < m_flMinDelay)
		{
			SWAP(m_flMinDelay, m_flMaxDelay);
		}

		pkvd->fHandled = TRUE;
	}
	else
	{
		if (FStrnEq(pkvd->szKeyName, "target", sizeof("target") - 1))
		{
			char *pszTargetName = nullptr;
			int iTargetsCount = strtoul(&pkvd->szKeyName[sizeof("target") - 1], &pszTargetName, 10);
			if (iTargetsCount < MAX_TR_TARGETS && pszTargetName && pszTargetName[0] == '\0')
			{
				m_iszTargets[iTargetsCount] = ALLOC_STRING(pkvd->szValue);
				pkvd->fHandled = TRUE;
				return;
			}
		}

		CBaseDelay::KeyValue(pkvd);
	}
}

void CTriggerRandom::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (pev->spawnflags & SF_RANDOM_TIMED)
	{
		m_bActive ^= true;

		pev->nextthink = gpGlobals->time + RandomDelay();
		SetThink(&CTriggerRandom::RandomThink);

		return;
	}

	Fire(pActivator);
}

void CTriggerRandom::RandomThink()
{
	if (m_bActive)
	{
		Fire(this);

		if (pev->spawnflags & SF_RANDOM_ONCE)
		{
			m_bActive = false;
		}
	}

	if (m_flMinDelay <= 0 || m_flMaxDelay <= 0)
	{
		m_bActive = false;
		return;
	}

	pev->nextthink = RandomDelay() + gpGlobals->time;
}

void CTriggerRandom::InitUnique()
{
	m_uiTargetsFired = 0;
	Q_memset(m_bActiveTargets, 0, MAX_TR_TARGETS);
}

void CTriggerRandom::Fire(CBaseEntity *pActivator)
{
	string_t iszSelectTarget = iStringNull;
	if (pev->spawnflags & SF_RANDOM_UNIQUE)
	{
		if (m_uiTargetsFired >= m_uiTargetsUse)
		{
			if (pev->spawnflags & SF_RANDOM_REUSABLE)
			{
				InitUnique();
				ALERT(at_aiconsole, "%s(%s): all targets fired; reusable mode on; resetting state\n", pev->classname.str(), pev->targetname.str());
			}
			else
			{
				// no re-usable
				return;
			}
		}

		unsigned int iRandomTarget = 0;
		const int MAX_SELECT_ATTEMPT = 256;

		for (int iSelect = 0; iSelect < MAX_SELECT_ATTEMPT; iSelect++)
		{
			iRandomTarget = RANDOM_LONG(0, m_uiTargetsUse - 1);

			if (!m_bActiveTargets[iRandomTarget])
				break;
		}

		// if queue is busy, try select first free target
		if (m_bActiveTargets[iRandomTarget])
		{
			ALERT(at_aiconsole, "%s(%s): random selection failed, selecting first free target\n", pev->classname.str(), pev->targetname.str());

			for (iRandomTarget = 0; iRandomTarget < m_uiTargetsUse; iRandomTarget++)
			{
				if (!m_bActiveTargets[iRandomTarget])
					break;
			}
		}

		iszSelectTarget = m_iszTargets[iRandomTarget];
		m_bActiveTargets[iRandomTarget] = true;
		m_uiTargetsFired++;
	}
	else
	{
		const int MAX_SELECT_ATTEMPT = 10;
		for (int iSelect = 0; iSelect < MAX_SELECT_ATTEMPT; iSelect++)
		{
			iszSelectTarget = m_iszTargets[RANDOM_LONG(0, m_uiTargetsUse - 1)];

			// free target
			if (!iszSelectTarget.IsNull())
			{
				break;
			}
		}
	}

	FireTargets(iszSelectTarget, pActivator, this, USE_TOGGLE, 0);
}

float CTriggerRandom::RandomDelay()
{
	return RANDOM_FLOAT(m_flMinDelay, m_flMaxDelay);
}
