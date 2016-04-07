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

CReGameHookchains g_ReGameHookchains;
CReGameData g_ReGameData;

ReGameFuncs_t g_ReGameApiFuncs = {
	&UTIL_PlayerByIndex,
	&CBASE_TO_CSPLAYER,
	&CBASE_TO_CSENTITY,
	&INDEX_TO_CSPLAYER,
	&INDEX_TO_CSENTITY,
	&CREATE_NAMED_ENTITY,

	&Regamedll_CopyString_api,
};

IReGameHookRegistry_CBasePlayer_Spawn* CReGameHookchains::CBasePlayer_Spawn() { return &m_CBasePlayer_Spawn; }
IReGameHookRegistry_CBasePlayer_Precache* CReGameHookchains::CBasePlayer_Precache() { return &m_CBasePlayer_Precache; }
IReGameHookRegistry_CBasePlayer_ObjectCaps* CReGameHookchains::CBasePlayer_ObjectCaps() { return &m_CBasePlayer_ObjectCaps; }
IReGameHookRegistry_CBasePlayer_Classify* CReGameHookchains::CBasePlayer_Classify() { return &m_CBasePlayer_Classify; }
IReGameHookRegistry_CBasePlayer_TraceAttack* CReGameHookchains::CBasePlayer_TraceAttack() { return &m_CBasePlayer_TraceAttack; }
IReGameHookRegistry_CBasePlayer_TakeDamage* CReGameHookchains::CBasePlayer_TakeDamage() { return &m_CBasePlayer_TakeDamage; }
IReGameHookRegistry_CBasePlayer_TakeHealth* CReGameHookchains::CBasePlayer_TakeHealth() { return &m_CBasePlayer_TakeHealth; }
IReGameHookRegistry_CBasePlayer_Killed* CReGameHookchains::CBasePlayer_Killed() { return &m_CBasePlayer_Killed; }
IReGameHookRegistry_CBasePlayer_AddPoints* CReGameHookchains::CBasePlayer_AddPoints() { return &m_CBasePlayer_AddPoints; }
IReGameHookRegistry_CBasePlayer_AddPointsToTeam* CReGameHookchains::CBasePlayer_AddPointsToTeam() { return &m_CBasePlayer_AddPointsToTeam; }
IReGameHookRegistry_CBasePlayer_AddPlayerItem* CReGameHookchains::CBasePlayer_AddPlayerItem() { return &m_CBasePlayer_AddPlayerItem; }
IReGameHookRegistry_CBasePlayer_RemovePlayerItem* CReGameHookchains::CBasePlayer_RemovePlayerItem() { return &m_CBasePlayer_RemovePlayerItem; }
IReGameHookRegistry_CBasePlayer_GiveAmmo* CReGameHookchains::CBasePlayer_GiveAmmo() { return &m_CBasePlayer_GiveAmmo; }
IReGameHookRegistry_CBasePlayer_ResetMaxSpeed* CReGameHookchains::CBasePlayer_ResetMaxSpeed() { return &m_CBasePlayer_ResetMaxSpeed; }
IReGameHookRegistry_CBasePlayer_Jump* CReGameHookchains::CBasePlayer_Jump() { return &m_CBasePlayer_Jump; }
IReGameHookRegistry_CBasePlayer_Duck* CReGameHookchains::CBasePlayer_Duck() { return &m_CBasePlayer_Duck; }
IReGameHookRegistry_CBasePlayer_PreThink* CReGameHookchains::CBasePlayer_PreThink() { return &m_CBasePlayer_PreThink; }
IReGameHookRegistry_CBasePlayer_PostThink* CReGameHookchains::CBasePlayer_PostThink() { return &m_CBasePlayer_PostThink; }
IReGameHookRegistry_CBasePlayer_UpdateClientData* CReGameHookchains::CBasePlayer_UpdateClientData() { return &m_CBasePlayer_UpdateClientData; }
IReGameHookRegistry_CBasePlayer_ImpulseCommands* CReGameHookchains::CBasePlayer_ImpulseCommands() { return &m_CBasePlayer_ImpulseCommands; }
IReGameHookRegistry_CBasePlayer_RoundRespawn* CReGameHookchains::CBasePlayer_RoundRespawn() { return &m_CBasePlayer_RoundRespawn; }
IReGameHookRegistry_CBasePlayer_Blind* CReGameHookchains::CBasePlayer_Blind() { return &m_CBasePlayer_Blind; }

IReGameHookRegistry_CBasePlayer_Observer_IsValidTarget* CReGameHookchains::CBasePlayer_Observer_IsValidTarget() { return &m_CBasePlayer_Observer_IsValidTarget; }
IReGameHookRegistry_CBasePlayer_SetAnimation* CReGameHookchains::CBasePlayer_SetAnimation() { return &m_CBasePlayer_SetAnimation; }
IReGameHookRegistry_CBasePlayer_GiveDefaultItems* CReGameHookchains::CBasePlayer_GiveDefaultItems() { return &m_CBasePlayer_GiveDefaultItems; }
IReGameHookRegistry_CBasePlayer_GiveNamedItem* CReGameHookchains::CBasePlayer_GiveNamedItem() { return &m_CBasePlayer_GiveNamedItem; }
IReGameHookRegistry_CBasePlayer_AddAccount* CReGameHookchains::CBasePlayer_AddAccount() { return &m_CBasePlayer_AddAccount; }
IReGameHookRegistry_CBasePlayer_GiveShield* CReGameHookchains::CBasePlayer_GiveShield() { return &m_CBasePlayer_GiveShield; }


IReGameHookRegistry_GetForceCamera* CReGameHookchains::GetForceCamera() { return &m_GetForceCamera; }
IReGameHookRegistry_PlayerBlind* CReGameHookchains::PlayerBlind() { return &m_PlayerBlind; }
IReGameHookRegistry_RadiusFlash_TraceLine* CReGameHookchains::RadiusFlash_TraceLine() { return &m_RadiusFlash_TraceLine; }

int CReGameApi::GetMajorVersion()
{
	return REGAMEDLL_API_VERSION_MAJOR;
}

int CReGameApi::GetMinorVersion()
{
	return REGAMEDLL_API_VERSION_MINOR;
}

const ReGameFuncs_t *CReGameApi::GetFuncs()
{
	return &g_ReGameApiFuncs;
}

IReGameHookchains *CReGameApi::GetHookchains()
{
	return &g_ReGameHookchains;
}

IReGameData *CReGameApi::GetGameData()
{
	return &g_ReGameData;
}

void EXT_FUNC Regamedll_CopyString_api(char *dest, const char *source)
{
	size_t len = Q_strlen(source);
	if (dest == nullptr || Q_strlen(dest) != len) {
		delete [] dest;
		dest = new char [len + 1];
	}

	Q_strcpy(dest, source);
}

EXPOSE_SINGLE_INTERFACE(CReGameApi, IReGameApi, VRE_GAMEDLL_API_VERSION);
