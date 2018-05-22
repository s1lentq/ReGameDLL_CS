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

#pragma once

// Makes trigger_random (with 'Timed only' flag) enabled at map start, so it will start it's timer and trigger random target on game start.
// If 'Trigger Once' flag isn't selected, it will continue until deactivated by trigger.
#define SF_RANDOM_STARTON  BIT(0)

// When using random delays (with 'Timed only' flag), this tells to trigger a random target once, instead
// of continuously triggering random targets until deactivation (in that case, disable timer by triggering this entity again).
#define SF_RANDOM_ONCE     BIT(1)

// If set, the trigger_random with 'Unique only' flag can be used again after having fired its targets, handling
// all of them as if not triggered before again.
#define SF_RANDOM_REUSABLE BIT(2)

// Enables 'Minimum/Maximum delay' keyvalues so you can specify to wait a random amount of time before triggering random targets.
// When 'Trigger Once' and 'Start On' flags are NOT selected, triggering this trigger_random starts the timer,
// and it will fire it's targets with random delays repeatedly until triggered again, what pauses it.
#define SF_RANDOM_TIMED    BIT(3)

// Trigger will pick target (each time it's triggered), that haven't been triggered yet, randomly. So if four targets are specified,
// the combination in which they can be picked may be: 3th, 1th, 2th, 4th. It never repeats the same target unless 'Re-usable'
// flag is selected- the list will be "shuffled", and targets can be picked all over again.
#define SF_RANDOM_UNIQUE   BIT(4)

const int MAX_TR_TARGETS = 16; // maximum number of targets a single trigger_random entity may be assigned.

class CTriggerRandom: public CBaseDelay {
public:
	void Spawn();
	void KeyValue(KeyValueData *pkvd);
	int Save(CSave &save);
	int Restore(CRestore &restore);
	int ObjectCaps() { return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
	void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

protected:
	void InitUnique();
	float RandomDelay();
	void Fire(CBaseEntity *pActivator);
	void EXPORT RandomThink();

	static TYPEDESCRIPTION m_SaveData[];

private:
	unsigned int m_uiTargetsUse;
	string_t m_iszTargets[MAX_TR_TARGETS];

	bool m_bActive;

	float m_flMinDelay;
	float m_flMaxDelay;

	unsigned int m_uiTargetsFired;
	bool m_bActiveTargets[MAX_TR_TARGETS];
};
