/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include "precompiled.h"

CCSEntity **g_GameEntities = NULL;
bool g_bInitialized = false;

ICSEntity::~ICSEntity() {}

void Regamedll_AllocEntities(int maxEdicts)
{
	if (g_bInitialized)
		return;

	g_bInitialized = true;
	g_GameEntities = (CCSEntity **)Q_malloc(sizeof(CCSEntity *) * maxEdicts);
	Q_memset(g_GameEntities, 0, sizeof(CCSEntity *) * maxEdicts);

#ifdef _DEBUG
	//CONSOLE_ECHO(__FUNCTION__":: alloc entities!\n");

	ADD_SERVER_COMMAND("check_ent", [](){		
		Regamedll_MonitorEntities();
	});
#endif
}

void Regamedll_FreeEntities(CBaseEntity *pEntity)
{
	if (pEntity == NULL)
	{
		for (int i = 0; i < gpGlobals->maxEntities; ++i)
		{
			delete g_GameEntities[i];
			g_GameEntities[i] = NULL;
		}

		Q_free(g_GameEntities);
		g_GameEntities = NULL;
		g_bInitialized = false;
		return;
	}

	int index = pEntity->entindex();
	if (index < 0 || index > gpGlobals->maxEntities)
		return;

	delete g_GameEntities[index];
	g_GameEntities[index] = NULL;

#ifdef _DEBUG
	//CONSOLE_ECHO(__FUNCTION__ ":: Free on (#%d. %s)\n", index, STRING(pEntity->edict()->v.classname));
#endif
}

void Regamedll_MonitorEntities()
{
	int nCount = 0;
	for (int i = 0; i < gpGlobals->maxEntities; ++i)
	{
		if (g_GameEntities[i] == NULL)
			continue;

		++nCount;
	}

	CONSOLE_ECHO(__FUNCTION__":: nCount: (%d) (%d)\n", nCount, gpGlobals->maxEntities);
}

ICSPlayer *EXT_FUNC CBASE_TO_CSPLAYER(CBaseEntity *pEntity)
{
	if (pEntity == NULL)
		return NULL;
	
	int index = pEntity->entindex();
	if (index < 1 || index > gpGlobals->maxClients)
	{
		return NULL;
		//regamedll_syserror(__FUNCTION__": Invalid player index %d", index);
	}

	return reinterpret_cast<ICSPlayer *>(g_GameEntities[index]);
}

ICSPlayer *EXT_FUNC INDEX_TO_CSPLAYER(int iPlayerIndex)
{
	CBaseEntity *pEntity = UTIL_PlayerByIndex(iPlayerIndex);
	return CBASE_TO_CSPLAYER(pEntity);
}

ICSEntity *EXT_FUNC CBASE_TO_CSENTITY(CBaseEntity *pEntity)
{
	if (pEntity == NULL)
		return NULL;
	
	int index = pEntity->entindex();
	if (index < 0 || index > gpGlobals->maxEntities)
	{
		return NULL;
		//regamedll_syserror(__FUNCTION__": Invalid entity index %d", index);
	}

	return g_GameEntities[index];
}

ICSEntity *EXT_FUNC INDEX_TO_CSENTITY(int iEntityIndex)
{
	CBaseEntity *pEntity = CBaseEntity::Instance(INDEXENT(iEntityIndex));
	return CBASE_TO_CSENTITY(pEntity);
}

CGameRules* EXT_FUNC CReGameData::GetGameRules() {
	return g_pGameRules;
}

WeaponInfoStruct* EXT_FUNC CReGameData::GetWeaponInfo(int weaponID) {
	return ::GetWeaponInfo(weaponID);
}
