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

int EXT_FUNC Cmd_Argc_api() {
	return CMD_ARGC_();
}

const char *EXT_FUNC Cmd_Argv_api(int i) {
	return CMD_ARGV_(i);
}

ReGameFuncs_t g_ReGameApiFuncs = {
	&CREATE_NAMED_ENTITY,

	&Regamedll_ChangeString_api,

	&RadiusDamage_api,
	&ClearMultiDamage_api,
	&ApplyMultiDamage_api,
	&AddMultiDamage_api,

	&UTIL_FindEntityByString,

	&AddEntityHashValue,
	&RemoveEntityHashValue,

	Cmd_Argc_api,
	Cmd_Argv_api
};

GAMEHOOK_REGISTRY(CBasePlayer_Spawn);
GAMEHOOK_REGISTRY(CBasePlayer_Precache);
GAMEHOOK_REGISTRY(CBasePlayer_ObjectCaps);
GAMEHOOK_REGISTRY(CBasePlayer_Classify);
GAMEHOOK_REGISTRY(CBasePlayer_TraceAttack);
GAMEHOOK_REGISTRY(CBasePlayer_TakeDamage);
GAMEHOOK_REGISTRY(CBasePlayer_TakeHealth);
GAMEHOOK_REGISTRY(CBasePlayer_Killed);
GAMEHOOK_REGISTRY(CBasePlayer_AddPoints);
GAMEHOOK_REGISTRY(CBasePlayer_AddPointsToTeam);
GAMEHOOK_REGISTRY(CBasePlayer_AddPlayerItem);
GAMEHOOK_REGISTRY(CBasePlayer_RemovePlayerItem);
GAMEHOOK_REGISTRY(CBasePlayer_GiveAmmo);
GAMEHOOK_REGISTRY(CBasePlayer_ResetMaxSpeed);
GAMEHOOK_REGISTRY(CBasePlayer_Jump);
GAMEHOOK_REGISTRY(CBasePlayer_Duck);
GAMEHOOK_REGISTRY(CBasePlayer_PreThink);
GAMEHOOK_REGISTRY(CBasePlayer_PostThink);
GAMEHOOK_REGISTRY(CBasePlayer_UpdateClientData);
GAMEHOOK_REGISTRY(CBasePlayer_ImpulseCommands);
GAMEHOOK_REGISTRY(CBasePlayer_RoundRespawn);
GAMEHOOK_REGISTRY(CBasePlayer_Blind);

GAMEHOOK_REGISTRY(CBasePlayer_Observer_IsValidTarget);
GAMEHOOK_REGISTRY(CBasePlayer_SetAnimation);
GAMEHOOK_REGISTRY(CBasePlayer_GiveDefaultItems);
GAMEHOOK_REGISTRY(CBasePlayer_GiveNamedItem);
GAMEHOOK_REGISTRY(CBasePlayer_AddAccount);
GAMEHOOK_REGISTRY(CBasePlayer_GiveShield);
GAMEHOOK_REGISTRY(CBasePlayer_SetClientUserInfoModel);
GAMEHOOK_REGISTRY(CBasePlayer_SetClientUserInfoName);
GAMEHOOK_REGISTRY(CBasePlayer_HasRestrictItem);
GAMEHOOK_REGISTRY(CBasePlayer_DropPlayerItem);
GAMEHOOK_REGISTRY(CBasePlayer_DropShield);
GAMEHOOK_REGISTRY(CBasePlayer_OnSpawnEquip);
GAMEHOOK_REGISTRY(CBasePlayer_Radio);
GAMEHOOK_REGISTRY(CBasePlayer_Disappear);
GAMEHOOK_REGISTRY(CBasePlayer_MakeVIP);
GAMEHOOK_REGISTRY(CBasePlayer_MakeBomber);
GAMEHOOK_REGISTRY(CBasePlayer_StartObserver);
GAMEHOOK_REGISTRY(CBasePlayer_GetIntoGame);

GAMEHOOK_REGISTRY(CBaseAnimating_ResetSequenceInfo);

GAMEHOOK_REGISTRY(GetForceCamera);
GAMEHOOK_REGISTRY(PlayerBlind);
GAMEHOOK_REGISTRY(RadiusFlash_TraceLine);
GAMEHOOK_REGISTRY(RoundEnd);
GAMEHOOK_REGISTRY(InstallGameRules);
GAMEHOOK_REGISTRY(PM_Init);
GAMEHOOK_REGISTRY(PM_Move);
GAMEHOOK_REGISTRY(PM_AirMove);
GAMEHOOK_REGISTRY(HandleMenu_ChooseAppearance);
GAMEHOOK_REGISTRY(HandleMenu_ChooseTeam);
GAMEHOOK_REGISTRY(ShowMenu);
GAMEHOOK_REGISTRY(ShowVGUIMenu);
GAMEHOOK_REGISTRY(BuyGunAmmo);
GAMEHOOK_REGISTRY(BuyWeaponByWeaponID);
GAMEHOOK_REGISTRY(InternalCommand);

GAMEHOOK_REGISTRY(CSGameRules_FShouldSwitchWeapon);
GAMEHOOK_REGISTRY(CSGameRules_GetNextBestWeapon);
GAMEHOOK_REGISTRY(CSGameRules_FlPlayerFallDamage);
GAMEHOOK_REGISTRY(CSGameRules_FPlayerCanTakeDamage);
GAMEHOOK_REGISTRY(CSGameRules_PlayerSpawn);
GAMEHOOK_REGISTRY(CSGameRules_FPlayerCanRespawn);
GAMEHOOK_REGISTRY(CSGameRules_GetPlayerSpawnSpot);
GAMEHOOK_REGISTRY(CSGameRules_ClientUserInfoChanged);
GAMEHOOK_REGISTRY(CSGameRules_PlayerKilled);
GAMEHOOK_REGISTRY(CSGameRules_DeathNotice);
GAMEHOOK_REGISTRY(CSGameRules_CanHavePlayerItem);
GAMEHOOK_REGISTRY(CSGameRules_DeadPlayerWeapons);
GAMEHOOK_REGISTRY(CSGameRules_ServerDeactivate);
GAMEHOOK_REGISTRY(CSGameRules_CheckMapConditions);
GAMEHOOK_REGISTRY(CSGameRules_CleanUpMap);
GAMEHOOK_REGISTRY(CSGameRules_RestartRound);
GAMEHOOK_REGISTRY(CSGameRules_CheckWinConditions);
GAMEHOOK_REGISTRY(CSGameRules_RemoveGuns);
GAMEHOOK_REGISTRY(CSGameRules_GiveC4);
GAMEHOOK_REGISTRY(CSGameRules_ChangeLevel);
GAMEHOOK_REGISTRY(CSGameRules_GoToIntermission);
GAMEHOOK_REGISTRY(CSGameRules_BalanceTeams);
GAMEHOOK_REGISTRY(CSGameRules_OnRoundFreezeEnd);
GAMEHOOK_REGISTRY(PM_UpdateStepSound);
GAMEHOOK_REGISTRY(CBasePlayer_StartDeathCam);

int EXT_FUNC CReGameApi::GetMajorVersion() {
	return REGAMEDLL_API_VERSION_MAJOR;
}

int EXT_FUNC CReGameApi::GetMinorVersion() {
	return REGAMEDLL_API_VERSION_MINOR;
}

const EXT_FUNC ReGameFuncs_t *CReGameApi::GetFuncs() {
	return &g_ReGameApiFuncs;
}

IReGameHookchains* EXT_FUNC CReGameApi::GetHookchains() {
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

ItemInfo* EXT_FUNC CReGameApi::GetItemInfo(WeaponIdType weaponID) { return &IMPL_CLASS(CBasePlayerItem, ItemInfoArray)[ weaponID ]; }
AmmoInfo* EXT_FUNC CReGameApi::GetAmmoInfo(AmmoType ammoID) { return &IMPL_CLASS(CBasePlayerItem, AmmoInfoArray)[ ammoID ]; }

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
