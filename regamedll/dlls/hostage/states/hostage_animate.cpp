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

void HostageAnimateState::Reset()
{
	m_sequenceCount = 0;
	m_performance = None;
}

void HostageAnimateState::StartSequence(CHostageImprov *improv, const SeqInfo *seqInfo)
{
	if (seqInfo->seqID >= 0)
	{
		CHostage *hostage = improv->GetEntity();

		hostage->pev->sequence = seqInfo->seqID;
		hostage->ResetSequenceInfo();
		hostage->m_fSequenceLoops = (seqInfo->holdTime > 0) ? TRUE : FALSE;
		hostage->pev->frame = (seqInfo->rate < 0) ? 255 : 0;
		hostage->pev->framerate = seqInfo->rate * hostage->pev->framerate;
	}

	m_isHolding = false;
}

void HostageAnimateState::AddSequence(CHostageImprov *improv, const char *seqName, float holdTime, float rate)
{
	int seqIndex;
	CHostage *hostage = improv->GetEntity();

	if (m_sequenceCount >= MAX_SEQUENCES)
		return;

	if (seqName)
		seqIndex = hostage->LookupSequence(seqName);
	else
		seqIndex = -1;

	m_sequence[m_sequenceCount].seqID = seqIndex;
	m_sequence[m_sequenceCount].holdTime = holdTime;
	m_sequence[m_sequenceCount].rate = rate;

	m_sequenceCount++;
	m_currentSequence = 0;

	StartSequence(improv, m_sequence);
}

void HostageAnimateState::AddSequence(CHostageImprov *improv, int activity, float holdTime, float rate)
{
	CHostage *hostage = improv->GetEntity();

	void *model = GET_MODEL_PTR(hostage->edict());
	if (model)
	{
		m_sequence[m_sequenceCount].seqID = LookupActivity(model, hostage->pev, activity);
		m_sequence[m_sequenceCount].holdTime = holdTime;
		m_sequence[m_sequenceCount].rate = rate;

		m_sequenceCount++;
		m_currentSequence = 0;
	}

	StartSequence(improv, m_sequence);
}

bool HostageAnimateState::IsDoneHolding()
{
	if (m_sequence[m_currentSequence].holdTime < 0)
		return true;

	if (m_isHolding)
		return m_holdTimer.IsElapsed();

	m_isHolding = true;
	m_holdTimer.Start(m_sequence[m_currentSequence].holdTime);
	return false;
}

void HostageAnimateState::OnEnter(CHostageImprov *improv)
{
	;
}

void HostageAnimateState::OnUpdate(CHostageImprov *improv)
{
	if (m_sequenceCount <= 0)
		return;

	if (!improv->GetEntity()->m_fSequenceFinished && m_sequence[m_currentSequence].seqID >= 0)
		return;

	if (m_sequence[m_currentSequence].holdTime >= 0)
	{
		if (!IsDoneHolding())
		{
			return;
		}
	}

	if (++m_currentSequence == m_sequenceCount)
	{
		m_sequenceCount = 0;
		m_performance = None;
		return;
	}

	StartSequence(improv, &m_sequence[m_currentSequence]);
}

void HostageAnimateState::OnExit(CHostageImprov *improv)
{
	;
}

NOXREF bool HostageAnimateState::IsPlaying(CHostageImprov *improv, const char *seqName) const
{
	int id = 0;
	CHostage *hostage = improv->GetEntity();

	if (m_sequenceCount > 0)
	{
		id = m_sequence[m_currentSequence].seqID;
	}

	return LookupSequence(hostage, seqName) == id;
}
