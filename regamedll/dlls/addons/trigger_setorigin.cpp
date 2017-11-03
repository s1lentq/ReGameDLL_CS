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

LINK_ENTITY_TO_CLASS(trigger_setorigin, CTriggerSetOrigin, CCSTriggerSetOrigin)

void CTriggerSetOrigin::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "triggerstate"))
	{
		int type = Q_atoi(pkvd->szValue);
		switch (type)
		{
		case 0:
			m_triggerType = USE_OFF;
			break;
		case 2:
			m_triggerType = USE_TOGGLE;
			break;
		default:
			m_triggerType = USE_ON;
			break;
		}

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "copypointer"))
	{
		m_copyPointer = ALLOC_STRING(pkvd->szValue);
	}
	else if (FStrEq(pkvd->szKeyName, "offset"))
	{
		UTIL_StringToVector(m_vecOffset, pkvd->szValue, ' ');
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "angleoffset"))
	{
		UTIL_StringToVector(m_vecAngleOffset, pkvd->szValue, ' ');
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "invert_x"))
	{
		m_bAngleInvertX = Q_atoi(pkvd->szValue) ? true : false;
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "invert_y"))
	{
		m_bAngleInvertY = Q_atoi(pkvd->szValue) ? true : false;
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "invert_z"))
	{
		m_bAngleInvertZ = Q_atoi(pkvd->szValue) ? true : false;
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_fRotate"))
	{
		pev->spawnflags |= SF_SETORIGIN_LOCK_OFFSETS;
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseDelay::KeyValue(pkvd);
	}
}

void CTriggerSetOrigin::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!(pev->spawnflags & SF_SETORIGIN_CONST_UPDATE))
	{
		m_bSetupEntities = true;
		return;
	}

	switch (useType)
	{
	case USE_OFF:
		m_bUpdateEntities = false;
		break;

	case USE_ON:
		m_bUpdateEntities = true;
		break;

	case USE_TOGGLE:
		m_bUpdateEntities = !m_bUpdateEntities;
		break;
	}

	if (m_bUpdateEntities)
	{
		m_bSetupEntities = true;
	}
}

void CTriggerSetOrigin::UpdateTick()
{
	if (m_bSetupEntities)
	{
		SetupEntities();
	}

	if (m_bUpdateEntities)
	{
		UpdateKnownEntities();
	}
}

void CTriggerSetOrigin::SetupEntities()
{
	EntityHandle<CBaseEntity> hPrevEnt(m_hCopyPointer);

	m_bSetupEntities = false;
	m_entityNum = 0;

	m_hCopyPointer = UTIL_FindEntityByTargetname(m_hCopyPointer, m_copyPointer);

	if (!m_hCopyPointer.IsValid() && hPrevEnt.IsValid())
	{
		m_hCopyPointer = hPrevEnt;
	}

	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByTargetname(pEntity, pev->target)))
	{
		if (m_entityNum > MAX_SETORIGIN_ENTITIES)
			break;

		if (FNullEnt(pEntity))
			continue;

		if (m_hCopyPointer.IsValid() && !FNullEnt(m_hCopyPointer.Get()))
		{
			bool bForceCopy = false;
			if (!(pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_X) &&
				!(pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Y) &&
				!(pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Z) &&
				!(pev->spawnflags & SF_SETORIGIN_COPY_AXIS_X)  &&
				!(pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Y)  &&
				!(pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Z))
			{
				bForceCopy = true;
			}

			if (!(pev->spawnflags & SF_SETORIGIN_SKIP_INITIAL))
			{
				Vector vecCopy(pEntity->pev->origin);

				// copy axis X
				if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_X) || bForceCopy)
					vecCopy.x = m_hCopyPointer->pev->origin.x;

				// copy axis Y
				if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Y) || bForceCopy)
					vecCopy.y = m_hCopyPointer->pev->origin.y;

				// copy axis Z
				if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Z) || bForceCopy)
					vecCopy.z = m_hCopyPointer->pev->origin.z;

				// copy angles X
				if (pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_X)
					pEntity->pev->angles.x = m_hCopyPointer->pev->angles.x;

				if (m_bAngleInvertX)
					pEntity->pev->angles.x = UTIL_AngleMod(-pEntity->pev->angles.x);

				// copy angles Y
				if (pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Y)
					pEntity->pev->angles.y = m_hCopyPointer->pev->angles.y;

				if (m_bAngleInvertY)
					pEntity->pev->angles.y = UTIL_AngleMod(-pEntity->pev->angles.y);

				// copy angles Z
				if (pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Z)
					pEntity->pev->angles.z = m_hCopyPointer->pev->angles.z;

				if (m_bAngleInvertZ)
					pEntity->pev->angles.z = UTIL_AngleMod(-pEntity->pev->angles.z);

				pEntity->pev->origin = vecCopy + m_vecOffset;
				pEntity->pev->angles = pEntity->pev->angles + m_vecAngleOffset;

				UTIL_SetOrigin(pEntity->pev, pEntity->pev->origin);
			}

			m_hEntities  [m_entityNum] = pEntity;
			m_vecEntities[m_entityNum] = pEntity->pev->origin - m_hCopyPointer->pev->origin;

			Vector vecForward, vecRight, vecUp;
			UTIL_MakeVectorsPrivate(m_hCopyPointer->pev->angles, vecForward, vecRight, vecUp);
			m_vecEntities[m_entityNum++] *= vecForward + vecRight + vecUp;
		}
		else
		{
			pEntity->pev->origin = pEntity->pev->origin + m_vecOffset;
			pEntity->pev->angles = pEntity->pev->angles + m_vecAngleOffset;

			UTIL_SetOrigin(pev, pEntity->pev->origin);
		}
	}

	if (pev->spawnflags & SF_SETORIGIN_REMOVEFIRE)
	{
		UTIL_Remove(this);
	}
}

void CTriggerSetOrigin::UpdateKnownEntities()
{
	bool bUpdated = false;
	for (int i = 0; i < MAX_SETORIGIN_ENTITIES; i++)
	{
		auto &pEntity = m_hEntities[i];
		if (!pEntity.IsValid())
		{
			pEntity = nullptr;
			continue;
		}

		if (!m_hCopyPointer.IsValid())
		{
			m_bUpdateEntities = false;
			break;
		}

		bool bForceCopy = false;
		if (!(pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_X) &&
			!(pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Y) &&
			!(pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Z) &&
			!(pev->spawnflags & SF_SETORIGIN_COPY_AXIS_X)  &&
			!(pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Y)  &&
			!(pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Z))
		{
			bForceCopy = true;
		}

		if (pev->spawnflags & SF_SETORIGIN_LOCK_OFFSETS)
		{
			Vector vecForward, vecRight, vecUp;
			Vector vecAxisX(g_vecZero), vecAxisY(g_vecZero), vecAxisZ(g_vecZero);

			UTIL_MakeVectorsPrivate(m_hCopyPointer->pev->angles, vecForward, vecRight, vecUp);

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_X) || bForceCopy)
				vecAxisX = m_vecEntities[i].x * vecForward;

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Y) || bForceCopy)
				vecAxisY = m_vecEntities[i].y * vecRight;

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Z) || bForceCopy)
				vecAxisZ = m_vecEntities[i].z * vecUp;

			Vector vecCopy(m_hCopyPointer->pev->origin + vecAxisX + vecAxisY + vecAxisZ);

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_X) || bForceCopy)
				pEntity->pev->origin.x = vecCopy.x;

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Y) || bForceCopy)
				pEntity->pev->origin.y = vecCopy.y;

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Z) || bForceCopy)
				pEntity->pev->origin.z = vecCopy.z;
		}
		else
		{
			Vector vecCopy(pEntity->pev->origin);

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_X) || bForceCopy)
				vecCopy.x = m_hCopyPointer->pev->origin.x;

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Y) || bForceCopy)
				vecCopy.y = m_hCopyPointer->pev->origin.y;

			if ((pev->spawnflags & SF_SETORIGIN_COPY_AXIS_Z) || bForceCopy)
				vecCopy.z = m_hCopyPointer->pev->origin.z;

			pEntity->pev->origin = vecCopy + m_vecOffset;
		}

		// copy angles Y
		if (pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_X)
			pEntity->pev->angles.x = UTIL_AngleMod(m_hCopyPointer->pev->angles.x);

		if (m_bAngleInvertX)
			pEntity->pev->angles.x = UTIL_AngleMod(-pEntity->pev->angles.x);

		// copy angles X
		if (pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Y)
			pEntity->pev->angles.y = UTIL_AngleMod(m_hCopyPointer->pev->angles.y);

		if (m_bAngleInvertY)
			pEntity->pev->angles.y = UTIL_AngleMod(-pEntity->pev->angles.y);

		// copy angles Z
		if (pev->spawnflags & SF_SETORIGIN_COPY_ANGLE_Z)
			pEntity->pev->angles.z = UTIL_AngleMod(m_hCopyPointer->pev->angles.z);

		if (m_bAngleInvertZ)
			pEntity->pev->angles.z = UTIL_AngleMod(-pEntity->pev->angles.z);

		pEntity->pev->angles += m_vecAngleOffset;

		pEntity->pev->groundentity = nullptr;
		pEntity->pev->flags &= ~FL_ONGROUND;

		bUpdated = true;
		UTIL_SetOrigin(pEntity->pev, pEntity->pev->origin);
	}

	if (!bUpdated)
	{
		m_bUpdateEntities = false;
	}
}

void CTriggerSetOrigin::OnCreate()
{
	m_bUpdateEntities = false;
	m_bSetupEntities = false;

	CTriggerSetOriginManager::getInstance()->Add(this);
}

void CTriggerSetOrigin::OnDestroy()
{
	CTriggerSetOriginManager::getInstance()->Remove(this);
}

void CTriggerSetOriginManager::Add(CTriggerSetOrigin *pInstance)
{
	if (!pInstance)
		return;

	m_Entities.AddToTail(pInstance);
}

void CTriggerSetOriginManager::Remove(CTriggerSetOrigin *pInstance)
{
	if (!pInstance)
		return;

	m_Entities.FindAndRemove(pInstance);
}

void CTriggerSetOriginManager::Update()
{
	for (int i = 0; i < m_Entities.Count(); i++)
	{
		if (!m_Entities[i].IsValid())
		{
			m_Entities.Remove(i);

			// Move iterator to back, because Remove method makes shift elements
			i--;
			continue;
		}

		// Update trigger
		m_Entities[i]->UpdateTick();
	}
}
