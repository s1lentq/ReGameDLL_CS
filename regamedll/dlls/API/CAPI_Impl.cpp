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
GAMEHOOK_REGISTRY(CBasePlayer_SwitchTeam);
GAMEHOOK_REGISTRY(CBasePlayer_CanSwitchTeam);
GAMEHOOK_REGISTRY(CBasePlayer_ThrowGrenade);
GAMEHOOK_REGISTRY(CSGameRules_CanPlayerHearPlayer);
GAMEHOOK_REGISTRY(CWeaponBox_SetModel);
GAMEHOOK_REGISTRY(CGrenade_DefuseBombStart);
GAMEHOOK_REGISTRY(CGrenade_DefuseBombEnd);
GAMEHOOK_REGISTRY(CGrenade_ExplodeHeGrenade);
GAMEHOOK_REGISTRY(CGrenade_ExplodeFlashbang);
GAMEHOOK_REGISTRY(CGrenade_ExplodeSmokeGrenade);
GAMEHOOK_REGISTRY(CGrenade_ExplodeBomb);
GAMEHOOK_REGISTRY(ThrowHeGrenade);
GAMEHOOK_REGISTRY(ThrowFlashbang);
GAMEHOOK_REGISTRY(ThrowSmokeGrenade);
GAMEHOOK_REGISTRY(PlantBomb);
GAMEHOOK_REGISTRY(CBasePlayer_SetSpawnProtection);
GAMEHOOK_REGISTRY(CBasePlayer_RemoveSpawnProtection);
GAMEHOOK_REGISTRY(IsPenetrableEntity);
GAMEHOOK_REGISTRY(CBasePlayer_HintMessageEx);
GAMEHOOK_REGISTRY(CBasePlayer_UseEmpty);
GAMEHOOK_REGISTRY(CBasePlayerWeapon_CanDeploy);
GAMEHOOK_REGISTRY(CBasePlayerWeapon_DefaultDeploy);
GAMEHOOK_REGISTRY(CBasePlayerWeapon_DefaultReload);
GAMEHOOK_REGISTRY(CBasePlayerWeapon_DefaultShotgunReload);
GAMEHOOK_REGISTRY(CBasePlayer_DropIdlePlayer);

int CReGameApi::GetMajorVersion() {
	return REGAMEDLL_API_VERSION_MAJOR;
}

int CReGameApi::GetMinorVersion() {
	return REGAMEDLL_API_VERSION_MINOR;
}

const ReGameFuncs_t *CReGameApi::GetFuncs() {
	return &g_ReGameApiFuncs;
}

IReGameHookchains *CReGameApi::GetHookchains() {
	return &g_ReGameHookchains;
}

CGameRules *CReGameApi::GetGameRules() {
	return g_pGameRules;
}

WeaponInfoStruct *CReGameApi::GetWeaponInfo(int weaponID) {
	return ::GetWeaponInfo(weaponID);
}

WeaponInfoStruct *CReGameApi::GetWeaponInfo(const char *weaponName) {
	return ::GetWeaponInfo(weaponName);
}

playermove_t *CReGameApi::GetPlayerMove() {
	return pmove;
}

WeaponSlotInfo *CReGameApi::GetWeaponSlot(WeaponIdType weaponID) { return ::GetWeaponSlot(weaponID); }
WeaponSlotInfo *CReGameApi::GetWeaponSlot(const char *weaponName) { return ::GetWeaponSlot(weaponName); }

ItemInfo *CReGameApi::GetItemInfo(WeaponIdType weaponID) { return &CBasePlayerItem::m_ItemInfoArray[weaponID]; }
AmmoInfo *CReGameApi::GetAmmoInfo(AmmoType ammoID) { return &CBasePlayerItem::m_AmmoInfoArray[ammoID]; }

AmmoInfoStruct *CReGameApi::GetAmmoInfoEx(AmmoType ammoID) { return ::GetAmmoInfo(ammoID); }
AmmoInfoStruct *CReGameApi::GetAmmoInfoEx(const char *ammoName) { return ::GetAmmoInfo(ammoName); }

bool CReGameApi::BGetICSEntity(const char *pchVersion) const
{
	if (!Q_stricmp(pchVersion, CSENTITY_API_INTERFACE_VERSION))
	{
		return true;
	}

	return false;
}

bool CReGameApi::BGetIGameRules(const char *pchVersion) const
{
	if (!Q_stricmp(pchVersion, GAMERULES_API_INTERFACE_VERSION))
	{
		return true;
	}

	return false;
}

EXT_FUNC void Regamedll_ChangeString_api(char *&dest, const char *source)
{
	size_t len = Q_strlen(source);
	if (dest == nullptr || Q_strlen(dest) != len) {
		delete [] dest;
		dest = new char [len + 1];
	}

	Q_strcpy(dest, source);
}

EXT_FUNC void RadiusDamage_api(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
	RadiusDamage(vecSrc, pevInflictor, pevAttacker, flDamage, flRadius, iClassIgnore, bitsDamageType);
}

EXT_FUNC void ClearMultiDamage_api()
{
	ClearMultiDamage();
}

EXT_FUNC void ApplyMultiDamage_api(entvars_t *pevInflictor, entvars_t *pevAttacker)
{
	ApplyMultiDamage(pevInflictor, pevAttacker);
}

EXT_FUNC void AddMultiDamage_api(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType)
{
	AddMultiDamage(pevInflictor, pEntity, flDamage, bitsDamageType);
}

EXPOSE_SINGLE_INTERFACE(CReGameApi, IReGameApi, VRE_GAMEDLL_API_VERSION);
