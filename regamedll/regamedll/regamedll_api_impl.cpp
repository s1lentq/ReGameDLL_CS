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

ReGameFuncs_t g_ReGameApiFuncs = {
	&UTIL_PlayerByIndex,
	&CREATE_NAMED_ENTITY,

	&Regamedll_ChangeString_api,

	&RadiusDamage_api,
	&ClearMultiDamage_api,
	&ApplyMultiDamage_api,
	&AddMultiDamage_api,

	&EndRoundMessage,
	&UTIL_FindEntityByString,

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
IReGameHookRegistry_CBasePlayer_SetClientUserInfoModel* CReGameHookchains::CBasePlayer_SetClientUserInfoModel() { return &m_CBasePlayer_SetClientUserInfoModel; }
IReGameHookRegistry_CBasePlayer_SetClientUserInfoName* CReGameHookchains::CBasePlayer_SetClientUserInfoName() { return &m_CBasePlayer_SetClientUserInfoName; }


IReGameHookRegistry_CBaseAnimating_ResetSequenceInfo* CReGameHookchains::CBaseAnimating_ResetSequenceInfo() { return &m_CBaseAnimating_ResetSequenceInfo; }

IReGameHookRegistry_GetForceCamera* CReGameHookchains::GetForceCamera() { return &m_GetForceCamera; }
IReGameHookRegistry_PlayerBlind* CReGameHookchains::PlayerBlind() { return &m_PlayerBlind; }
IReGameHookRegistry_RadiusFlash_TraceLine* CReGameHookchains::RadiusFlash_TraceLine() { return &m_RadiusFlash_TraceLine; }
IReGameHookRegistry_RoundEnd* CReGameHookchains::RoundEnd() { return &m_RoundEnd; }
IReGameHookRegistry_CanBuyThis* CReGameHookchains::CanBuyThis() { return &m_CanBuyThis; }
IReGameHookRegistry_InstallGameRules* CReGameHookchains::InstallGameRules() { return &m_InstallGameRules; }
IReGameHookRegistry_PM_Init* CReGameHookchains::PM_Init() { return &m_PM_Init; }
IReGameHookRegistry_PM_Move* CReGameHookchains::PM_Move() { return &m_PM_Move; }
IReGameHookRegistry_PM_AirMove* CReGameHookchains::PM_AirMove() { return &m_PM_AirMove; }
IReGameHookRegistry_HandleMenu_ChooseAppearance* CReGameHookchains::HandleMenu_ChooseAppearance() { return &m_HandleMenu_ChooseAppearance; }
IReGameHookRegistry_HandleMenu_ChooseTeam* CReGameHookchains::HandleMenu_ChooseTeam() { return &m_HandleMenu_ChooseTeam; }
IReGameHookRegistry_ShowMenu* CReGameHookchains::ShowMenu() { return &m_ShowMenu; }
IReGameHookRegistry_ShowVGUIMenu* CReGameHookchains::ShowVGUIMenu() { return &m_ShowVGUIMenu; }

IReGameHookRegistry_CSGameRules_FShouldSwitchWeapon* CReGameHookchains::CSGameRules_FShouldSwitchWeapon() { return &m_CSGameRules_FShouldSwitchWeapon; }
IReGameHookRegistry_CSGameRules_GetNextBestWeapon* CReGameHookchains::CSGameRules_GetNextBestWeapon() { return &m_CSGameRules_GetNextBestWeapon; }
IReGameHookRegistry_CSGameRules_FlPlayerFallDamage* CReGameHookchains::CSGameRules_FlPlayerFallDamage() { return &m_CSGameRules_FlPlayerFallDamage; }
IReGameHookRegistry_CSGameRules_FPlayerCanTakeDamage* CReGameHookchains::CSGameRules_FPlayerCanTakeDamage() { return &m_CSGameRules_FPlayerCanTakeDamage; }
IReGameHookRegistry_CSGameRules_PlayerSpawn* CReGameHookchains::CSGameRules_PlayerSpawn() { return &m_CSGameRules_PlayerSpawn; }
IReGameHookRegistry_CSGameRules_FPlayerCanRespawn* CReGameHookchains::CSGameRules_FPlayerCanRespawn() { return &m_CSGameRules_FPlayerCanRespawn; }
IReGameHookRegistry_CSGameRules_GetPlayerSpawnSpot* CReGameHookchains::CSGameRules_GetPlayerSpawnSpot() { return &m_CSGameRules_GetPlayerSpawnSpot; }
IReGameHookRegistry_CSGameRules_ClientUserInfoChanged* CReGameHookchains::CSGameRules_ClientUserInfoChanged() { return &m_CSGameRules_ClientUserInfoChanged; }
IReGameHookRegistry_CSGameRules_PlayerKilled* CReGameHookchains::CSGameRules_PlayerKilled() { return &m_CSGameRules_PlayerKilled; }
IReGameHookRegistry_CSGameRules_DeathNotice* CReGameHookchains::CSGameRules_DeathNotice() { return &m_CSGameRules_DeathNotice; }
IReGameHookRegistry_CSGameRules_CanHavePlayerItem* CReGameHookchains::CSGameRules_CanHavePlayerItem() { return &m_CSGameRules_CanHavePlayerItem; }
IReGameHookRegistry_CSGameRules_DeadPlayerWeapons* CReGameHookchains::CSGameRules_DeadPlayerWeapons() { return &m_CSGameRules_DeadPlayerWeapons; }
IReGameHookRegistry_CSGameRules_ServerDeactivate* CReGameHookchains::CSGameRules_ServerDeactivate() { return &m_CSGameRules_ServerDeactivate; }
IReGameHookRegistry_CSGameRules_CheckMapConditions* CReGameHookchains::CSGameRules_CheckMapConditions() { return &m_CSGameRules_CheckMapConditions; }
IReGameHookRegistry_CSGameRules_CleanUpMap* CReGameHookchains::CSGameRules_CleanUpMap() { return &m_CSGameRules_CleanUpMap; }
IReGameHookRegistry_CSGameRules_RestartRound* CReGameHookchains::CSGameRules_RestartRound() { return &m_CSGameRules_RestartRound; }
IReGameHookRegistry_CSGameRules_CheckWinConditions* CReGameHookchains::CSGameRules_CheckWinConditions() { return &m_CSGameRules_CheckWinConditions; }
IReGameHookRegistry_CSGameRules_RemoveGuns* CReGameHookchains::CSGameRules_RemoveGuns() { return &m_CSGameRules_RemoveGuns; }
IReGameHookRegistry_CSGameRules_GiveC4* CReGameHookchains::CSGameRules_GiveC4() { return &m_CSGameRules_GiveC4; }
IReGameHookRegistry_CSGameRules_ChangeLevel* CReGameHookchains::CSGameRules_ChangeLevel() { return &m_CSGameRules_ChangeLevel; }
IReGameHookRegistry_CSGameRules_GoToIntermission* CReGameHookchains::CSGameRules_GoToIntermission() { return &m_CSGameRules_GoToIntermission; }
IReGameHookRegistry_CSGameRules_BalanceTeams* CReGameHookchains::CSGameRules_BalanceTeams() { return &m_CSGameRules_BalanceTeams; }

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

CGameRules* EXT_FUNC CReGameApi::GetGameRules() {
	return g_pGameRules;
}

WeaponInfoStruct* EXT_FUNC CReGameApi::GetWeaponInfo(int weaponID) {
	return ::GetWeaponInfo(weaponID);
}

WeaponInfoStruct* EXT_FUNC CReGameApi::GetWeaponInfo(const char* weaponName) {
	return ::GetWeaponInfo(weaponName);
}

playermove_t* EXT_FUNC CReGameApi::GetPlayerMove() {
	return pmove;
}

WeaponSlotInfo* EXT_FUNC CReGameApi::GetWeaponSlot(WeaponIdType weaponID) { return ::GetWeaponSlot(weaponID); }
WeaponSlotInfo* EXT_FUNC CReGameApi::GetWeaponSlot(const char* weaponName) { return ::GetWeaponSlot(weaponName); }

void EXT_FUNC Regamedll_ChangeString_api(char *&dest, const char *source)
{
	size_t len = Q_strlen(source);
	if (dest == nullptr || Q_strlen(dest) != len) {
		delete [] dest;
		dest = new char [len + 1];
	}

	Q_strcpy(dest, source);
}

void EXT_FUNC RadiusDamage_api(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
	RadiusDamage(vecSrc, pevInflictor, pevAttacker, flDamage, flRadius, iClassIgnore, bitsDamageType);
}

void EXT_FUNC ClearMultiDamage_api()
{
	ClearMultiDamage();
}

void EXT_FUNC ApplyMultiDamage_api(entvars_t *pevInflictor, entvars_t *pevAttacker)
{
	ApplyMultiDamage(pevInflictor, pevAttacker);
}

void EXT_FUNC AddMultiDamage_api(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType)
{
	AddMultiDamage(pevInflictor, pEntity, flDamage, bitsDamageType);
}

EXPOSE_SINGLE_INTERFACE(CReGameApi, IReGameApi, VRE_GAMEDLL_API_VERSION);
