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

LINK_ENTITY_TO_CLASS(trigger_bomb_reset, CTriggerBombReset, CCSTriggerBombReset)

void CTriggerBombReset::Spawn()
{
	InitTrigger();
	SetTouch(&CTriggerBombReset::Touch);
	SetUse(&CTriggerBombReset::ToggleUse);
}

void CTriggerBombReset::Touch(CBaseEntity *pOther)
{
	CWeaponBox *pWeaponBox = dynamic_cast<CWeaponBox *>(pOther);

	if (pWeaponBox && pWeaponBox->m_bIsBomb)
	{
		// If the bomb touches this trigger, tell it to reset to its last known valid position.
		pWeaponBox->ResetToLastValidPlayerHeldC4Position();
	}
}
