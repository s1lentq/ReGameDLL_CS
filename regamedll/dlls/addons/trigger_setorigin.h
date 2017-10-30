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

#define SF_SETORIGIN_CONST_UPDATE BIT(0)  // The entity will constantly update position if set
#define SF_SETORIGIN_REMOVEFIRE   BIT(2)  // The entity will be removed after firing.

#define SF_SETORIGIN_LOCK_OFFSETS BIT(3)  // Save the offset between the Target entity and the Copy pointer,
                                          // apply offset when updating the Target entity's position (Requires "Constant" flag)

#define SF_SETORIGIN_COPY_ANGLE_X BIT(4)
#define SF_SETORIGIN_COPY_ANGLE_Y BIT(5)
#define SF_SETORIGIN_COPY_ANGLE_Z BIT(6)

#define SF_SETORIGIN_COPY_AXIS_X  BIT(7)
#define SF_SETORIGIN_COPY_AXIS_Y  BIT(8)
#define SF_SETORIGIN_COPY_AXIS_Z  BIT(9)

#define SF_SETORIGIN_SKIP_INITIAL BIT(10) // If you're using the Constant flag, check this box to NOT move the origin of the entity or set the angles initially.
                                          // If you're not using the Constant flag, make sure this isn't enabled or trigger_setorigin won't do anything.
                                          //
                                          // This allows the "Constant" + "offset difference" combination to work as intended from the entity's original location.
                                          //
                                          // You would leave this off if you needed to move the entity to an initial position before having it follow another entity.
                                          // (If this isn't set, trigger_setorigin will move the entity to it's copypointer's origin before doing the offset difference calculation)

const int MAX_SETORIGIN_ENTITIES = 64;

class CTriggerSetOrigin: public CBaseDelay {
public:
	void KeyValue(KeyValueData *pkvd);
	int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }
	void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

	void OnCreate();
	void OnDestroy();

protected:
	friend class CTriggerSetOriginManager;
	void UpdateTick();
	void SetupEntities();
	void UpdateKnownEntities();

private:
	EntityHandle<CBaseEntity> m_hCopyPointer;
	EntityHandle<CBaseEntity> m_hEntities[MAX_SETORIGIN_ENTITIES];

	Vector m_vecEntities[MAX_SETORIGIN_ENTITIES];
	Vector m_vecOffset;
	Vector m_vecAngleOffset;

	bool m_bAngleInvertX;
	bool m_bAngleInvertY;
	bool m_bAngleInvertZ;

	int m_entityNum;
	int m_triggerType;

	string_t m_copyPointer;

	bool m_bUpdateEntities;
	bool m_bSetupEntities;
};

class CTriggerSetOriginManager
{
public:
	CTriggerSetOriginManager() {}

	void Add(CTriggerSetOrigin *pInstance);
	void Remove(CTriggerSetOrigin *pInstance);
	void Update();

	static CTriggerSetOriginManager *getInstance()
	{
		static CTriggerSetOriginManager *pInstance = new CTriggerSetOriginManager;
		return pInstance;
	}

private:
	CUtlVector<EntityHandle<CTriggerSetOrigin>> m_Entities;
};
