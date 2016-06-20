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
#pragma once

#include "archtypes.h"
#include "regamedll_api.h"
#include "regamedll_interfaces_impl.h"

// CBasePlayer::Spawn hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_Spawn;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_Spawn;

// CBasePlayer::Precache hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_Precache;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_Precache;

// CBasePlayer::ObjectCaps hook
typedef IHookChainClassImpl<int, CBasePlayer> CReGameHook_CBasePlayer_ObjectCaps;
typedef IHookChainRegistryClassImpl<int, CBasePlayer> CReGameHookRegistry_CBasePlayer_ObjectCaps;

// CBasePlayer::Classify hook
typedef IHookChainClassImpl<int, CBasePlayer> CReGameHook_CBasePlayer_Classify;
typedef IHookChainRegistryClassImpl<int, CBasePlayer> CReGameHookRegistry_CBasePlayer_Classify;

// CBasePlayer::TraceAttack hook
typedef IVoidHookChainClassImpl<CBasePlayer, entvars_t *, float, Vector &, TraceResult *, int> CReGameHook_CBasePlayer_TraceAttack;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, entvars_t *, float, Vector &, TraceResult *, int> CReGameHookRegistry_CBasePlayer_TraceAttack;

// CBasePlayer::TakeDamage hook
typedef IHookChainClassImpl<BOOL, CBasePlayer, entvars_t *, entvars_t *, float&, int> CReGameHook_CBasePlayer_TakeDamage;
typedef IHookChainRegistryClassImpl<BOOL, CBasePlayer, entvars_t *, entvars_t *, float&, int> CReGameHookRegistry_CBasePlayer_TakeDamage;

// CBasePlayer::TakeHealth hook
typedef IHookChainClassImpl<BOOL, CBasePlayer, float, int> CReGameHook_CBasePlayer_TakeHealth;
typedef IHookChainRegistryClassImpl<BOOL, CBasePlayer, float, int> CReGameHookRegistry_CBasePlayer_TakeHealth;

// CBasePlayer::Killed hook
typedef IVoidHookChainClassImpl<CBasePlayer, entvars_t *, int> CReGameHook_CBasePlayer_Killed;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, entvars_t *, int> CReGameHookRegistry_CBasePlayer_Killed;

// CBasePlayer::AddPoints hook
typedef IVoidHookChainClassImpl<CBasePlayer, int, BOOL> CReGameHook_CBasePlayer_AddPoints;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, int, BOOL> CReGameHookRegistry_CBasePlayer_AddPoints;

// CBasePlayer::AddPointsToTeam hook
typedef IVoidHookChainClassImpl<CBasePlayer, int, BOOL> CReGameHook_CBasePlayer_AddPointsToTeam;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, int, BOOL> CReGameHookRegistry_CBasePlayer_AddPointsToTeam;

// CBasePlayer::AddPlayerItem hook
typedef IHookChainClassImpl<BOOL, CBasePlayer, CBasePlayerItem *> CReGameHook_CBasePlayer_AddPlayerItem;
typedef IHookChainRegistryClassImpl<BOOL, CBasePlayer, CBasePlayerItem *> CReGameHookRegistry_CBasePlayer_AddPlayerItem;

// CBasePlayer::RemovePlayerItem hook
typedef IHookChainClassImpl<BOOL, CBasePlayer, CBasePlayerItem *> CReGameHook_CBasePlayer_RemovePlayerItem;
typedef IHookChainRegistryClassImpl<BOOL, CBasePlayer, CBasePlayerItem *> CReGameHookRegistry_CBasePlayer_RemovePlayerItem;

// CBasePlayer::GiveAmmo hook
typedef IHookChainClassImpl<int, CBasePlayer, int , char *, int> CReGameHook_CBasePlayer_GiveAmmo;
typedef IHookChainRegistryClassImpl<int, CBasePlayer, int , char *, int> CReGameHookRegistry_CBasePlayer_GiveAmmo;

// CBasePlayer::ResetMaxSpeed hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_ResetMaxSpeed;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_ResetMaxSpeed;

// CBasePlayer::Jump hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_Jump;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_Jump;

// CBasePlayer::Duck hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_Duck;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_Duck;

// CBasePlayer::PreThink hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_PreThink;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_PreThink;

// CBasePlayer::PostThink hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_PostThink;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_PostThink;

// CBasePlayer::UpdateClientData hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_UpdateClientData;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_UpdateClientData;

// CBasePlayer::ImpulseCommands hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_ImpulseCommands;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_ImpulseCommands;

// CBasePlayer::RoundRespawn hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_RoundRespawn;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_RoundRespawn;

// CBasePlayer::Blind hook
typedef IVoidHookChainClassImpl<CBasePlayer, float, float, float, int> CReGameHook_CBasePlayer_Blind;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, float, float, float, int> CReGameHookRegistry_CBasePlayer_Blind;

// CBasePlayer::Observer_IsValidTarget hook
typedef IHookChainClassImpl<CBasePlayer *, CBasePlayer, int, bool> CReGameHook_CBasePlayer_Observer_IsValidTarget;
typedef IHookChainRegistryClassImpl<CBasePlayer *, CBasePlayer, int, bool> CReGameHookRegistry_CBasePlayer_Observer_IsValidTarget;

// CBasePlayer::SetAnimation hook
typedef IVoidHookChainClassImpl<CBasePlayer, PLAYER_ANIM> CReGameHook_CBasePlayer_SetAnimation;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, PLAYER_ANIM> CReGameHookRegistry_CBasePlayer_SetAnimation;

// CBasePlayer::GiveDefaultItems hook
typedef IVoidHookChainClassImpl<CBasePlayer> CReGameHook_CBasePlayer_GiveDefaultItems;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer> CReGameHookRegistry_CBasePlayer_GiveDefaultItems;

// CBasePlayer::GiveNamedItem hook
typedef IVoidHookChainClassImpl<CBasePlayer, const char *> CReGameHook_CBasePlayer_GiveNamedItem;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, const char *> CReGameHookRegistry_CBasePlayer_GiveNamedItem;

// CBasePlayer::AddAccount hook
typedef IVoidHookChainClassImpl<CBasePlayer, int, RewardType, bool> CReGameHook_CBasePlayer_AddAccount;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, int, RewardType, bool> CReGameHookRegistry_CBasePlayer_AddAccount;

// CBasePlayer::GiveShield hook
typedef IVoidHookChainClassImpl<CBasePlayer, bool> CReGameHook_CBasePlayer_GiveShield;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, bool> CReGameHookRegistry_CBasePlayer_GiveShield;

// CBasePlayer:SetClientUserInfoModel hook
typedef IVoidHookChainClassImpl<CBasePlayer, char *, char *> CReGameHook_CBasePlayer_SetClientUserInfoModel;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, char *, char *> CReGameHookRegistry_CBasePlayer_SetClientUserInfoModel;

// CBasePlayer:SetClientUserInfoName hook
typedef IVoidHookChainClassImpl<CBasePlayer, char *, char *> CReGameHook_CBasePlayer_SetClientUserInfoName;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, char *, char *> CReGameHookRegistry_CBasePlayer_SetClientUserInfoName;

// CBasePlayer::DropPlayerItem hook
typedef IVoidHookChainClassImpl<CBasePlayer, const char *> CReGameHook_CBasePlayer_DropPlayerItem;
typedef IVoidHookChainRegistryClassImpl<CBasePlayer, const char *> CReGameHookRegistry_CBasePlayer_DropPlayerItem;

// CBaseAnimating::ResetSequenceInfo hook
typedef IVoidHookChainClassImpl<CBaseAnimating> CReGameHook_CBaseAnimating_ResetSequenceInfo;
typedef IVoidHookChainRegistryClassImpl<CBaseAnimating> CReGameHookRegistry_CBaseAnimating_ResetSequenceInfo;

// CWeaponBox::Touch hook
typedef IVoidHookChainClassImpl<CWeaponBox, CBaseEntity*> CReGameHook_CWeaponBox_Touch;
typedef IVoidHookChainRegistryClassImpl<CWeaponBox, CBaseEntity*> CReGameHookRegistry_CWeaponBox_Touch;

// CArmoury::Touch hook
typedef IVoidHookChainClassImpl<CArmoury, CBaseEntity*> CReGameHook_CArmoury_Touch;
typedef IVoidHookChainRegistryClassImpl<CArmoury, CBaseEntity*> CReGameHookRegistry_CArmoury_Touch;

// GetForceCamera hook
typedef IHookChainImpl<int, class CBasePlayer *> CReGameHook_GetForceCamera;
typedef IHookChainRegistryImpl<int, class CBasePlayer *> CReGameHookRegistry_GetForceCamera;

// PlayerBlind hook
typedef IVoidHookChainImpl<CBasePlayer *, entvars_t *, entvars_t *, float, float, int, Vector &> CReGameHook_PlayerBlind;
typedef IVoidHookChainRegistryImpl<CBasePlayer *, entvars_t *, entvars_t *, float, float, int, Vector &> CReGameHookRegistry_PlayerBlind;

// RadiusFlash_TraceLine hook
typedef IVoidHookChainImpl<CBasePlayer *, entvars_t *, entvars_t *, Vector &, Vector &, TraceResult *> CReGameHook_RadiusFlash_TraceLine;
typedef IVoidHookChainRegistryImpl<CBasePlayer *, entvars_t *, entvars_t *, Vector &, Vector &, TraceResult *> CReGameHookRegistry_RadiusFlash_TraceLine;

// RoundEnd hook
typedef IHookChainClassImpl<bool, class CHalfLifeMultiplay, int, ScenarioEventEndRound, float> CReGameHook_RoundEnd;
typedef IHookChainRegistryClassEmptyImpl<bool, class CHalfLifeMultiplay, int, ScenarioEventEndRound, float> CReGameHookRegistry_RoundEnd;

// CanBuyThis hook
typedef IHookChainImpl<bool, class CBasePlayer *, int> CReGameHook_CanBuyThis;
typedef IHookChainRegistryImpl<bool, class CBasePlayer *, int> CReGameHookRegistry_CanBuyThis;

// CanBuyThisItem hook
typedef IHookChainImpl<bool, class CBasePlayer *, BuyItemID> CReGameHook_CanBuyThisItem;
typedef IHookChainRegistryImpl<bool, class CBasePlayer *, BuyItemID> CReGameHookRegistry_CanBuyThisItem;

// InstallGameRules hook
typedef IHookChainImpl<CGameRules *> CReGameHook_InstallGameRules;
typedef IHookChainRegistryImpl<CGameRules *> CReGameHookRegistry_InstallGameRules;

// PM_Init hook
typedef IVoidHookChainImpl<struct playermove_s *> CReGameHook_PM_Init;
typedef IVoidHookChainRegistryImpl<struct playermove_s *> CReGameHookRegistry_PM_Init;

// PM_Move hook
typedef IVoidHookChainImpl<struct playermove_s *, int> CReGameHook_PM_Move;
typedef IVoidHookChainRegistryImpl<struct playermove_s *, int> CReGameHookRegistry_PM_Move;

// PM_AirMove hook
typedef IVoidHookChainImpl<int> CReGameHook_PM_AirMove;
typedef IVoidHookChainRegistryImpl<int> CReGameHookRegistry_PM_AirMove;

// HandleMenu_ChooseAppearance hook
typedef IVoidHookChainImpl<CBasePlayer *, int> CReGameHook_HandleMenu_ChooseAppearance;
typedef IVoidHookChainRegistryImpl<CBasePlayer *, int> CReGameHookRegistry_HandleMenu_ChooseAppearance;

// HandleMenu_ChooseTeam hook
typedef IHookChainImpl<BOOL, CBasePlayer *, int> CReGameHook_HandleMenu_ChooseTeam;
typedef IHookChainRegistryImpl<BOOL, CBasePlayer *, int> CReGameHookRegistry_HandleMenu_ChooseTeam;

// ShowMenu hook
typedef IVoidHookChainImpl<CBasePlayer *, int, int, BOOL, char *> CReGameHook_ShowMenu;
typedef IVoidHookChainRegistryImpl<CBasePlayer *, int, int, BOOL, char *> CReGameHookRegistry_ShowMenu;

// ShowVGUIMenu hook
typedef IVoidHookChainImpl<CBasePlayer *, int, int, char *> CReGameHook_ShowVGUIMenu;
typedef IVoidHookChainRegistryImpl<CBasePlayer *, int, int, char *> CReGameHookRegistry_ShowVGUIMenu;

// CHalfLifeMultiplay::FShouldSwitchWeapon hook
typedef IHookChainClassImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBasePlayerItem *> CReGameHook_CSGameRules_FShouldSwitchWeapon;
typedef IHookChainRegistryClassEmptyImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBasePlayerItem *> CReGameHookRegistry_CSGameRules_FShouldSwitchWeapon;

// CHalfLifeMultiplay::GetNextBestWeapon hook
typedef IHookChainClassImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBasePlayerItem *> CReGameHook_CSGameRules_GetNextBestWeapon;
typedef IHookChainRegistryClassEmptyImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBasePlayerItem *> CReGameHookRegistry_CSGameRules_GetNextBestWeapon;

// CHalfLifeMultiplay::FlPlayerFallDamage hook
typedef IHookChainClassImpl<float, class CHalfLifeMultiplay, CBasePlayer *> CReGameHook_CSGameRules_FlPlayerFallDamage;
typedef IHookChainRegistryClassEmptyImpl<float, class CHalfLifeMultiplay, CBasePlayer *> CReGameHookRegistry_CSGameRules_FlPlayerFallDamage;

// CHalfLifeMultiplay::FPlayerCanTakeDamage hook
typedef IHookChainClassImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBaseEntity *> CReGameHook_CSGameRules_FPlayerCanTakeDamage;
typedef IHookChainRegistryClassEmptyImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBaseEntity *> CReGameHookRegistry_CSGameRules_FPlayerCanTakeDamage;

// CHalfLifeMultiplay::PlayerSpawn hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay, CBasePlayer *> CReGameHook_CSGameRules_PlayerSpawn;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay, CBasePlayer *> CReGameHookRegistry_CSGameRules_PlayerSpawn;

// CHalfLifeMultiplay::FPlayerCanRespawn hook
typedef IHookChainClassImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *> CReGameHook_CSGameRules_FPlayerCanRespawn;
typedef IHookChainRegistryClassEmptyImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *> CReGameHookRegistry_CSGameRules_FPlayerCanRespawn;

// CHalfLifeMultiplay::GetPlayerSpawnSpot hook
typedef IHookChainClassImpl<edict_t *, class CHalfLifeMultiplay, CBasePlayer *> CReGameHook_CSGameRules_GetPlayerSpawnSpot;
typedef IHookChainRegistryClassEmptyImpl<edict_t *, class CHalfLifeMultiplay, CBasePlayer *> CReGameHookRegistry_CSGameRules_GetPlayerSpawnSpot;

// CHalfLifeMultiplay::ClientUserInfoChanged hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay, CBasePlayer *, char *> CReGameHook_CSGameRules_ClientUserInfoChanged;
typedef IVoidHookChainRegistryClassEmptyImpl< class CHalfLifeMultiplay, CBasePlayer *, char *> CReGameHookRegistry_CSGameRules_ClientUserInfoChanged;

// CHalfLifeMultiplay::PlayerKilled hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay, CBasePlayer *, entvars_t *, entvars_t *> CReGameHook_CSGameRules_PlayerKilled;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay, CBasePlayer *, entvars_t *, entvars_t *> CReGameHookRegistry_CSGameRules_PlayerKilled;

// CHalfLifeMultiplay::DeathNotice hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay, CBasePlayer *, entvars_t *, entvars_t *> CReGameHook_CSGameRules_DeathNotice;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay, CBasePlayer *, entvars_t *, entvars_t *> CReGameHookRegistry_CSGameRules_DeathNotice;

// CHalfLifeMultiplay::CanHavePlayerItem hook
typedef IHookChainClassImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBasePlayerItem *> CReGameHook_CSGameRules_CanHavePlayerItem;
typedef IHookChainRegistryClassEmptyImpl<BOOL, class CHalfLifeMultiplay, CBasePlayer *, CBasePlayerItem *> CReGameHookRegistry_CSGameRules_CanHavePlayerItem;

// CHalfLifeMultiplay::DeadPlayerWeapons hook
typedef IHookChainClassImpl<int, class CHalfLifeMultiplay, CBasePlayer *> CReGameHook_CSGameRules_DeadPlayerWeapons;
typedef IHookChainRegistryClassEmptyImpl<int, class CHalfLifeMultiplay, CBasePlayer *> CReGameHookRegistry_CSGameRules_DeadPlayerWeapons;

// CHalfLifeMultiplay::ServerDeactivate hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_ServerDeactivate;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_ServerDeactivate;

// CHalfLifeMultiplay::CheckMapConditions hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_CheckMapConditions;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_CheckMapConditions;

// CHalfLifeMultiplay::CleanUpMap hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_CleanUpMap;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_CleanUpMap;

// CHalfLifeMultiplay::RestartRound hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_RestartRound;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_RestartRound;

// CHalfLifeMultiplay::CheckWinConditions hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_CheckWinConditions;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_CheckWinConditions;

// CHalfLifeMultiplay::RemoveGuns hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_RemoveGuns;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_RemoveGuns;

// CHalfLifeMultiplay::GiveC4 hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_GiveC4;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_GiveC4;

// CHalfLifeMultiplay::ChangeLevel hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_ChangeLevel;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_ChangeLevel;

// CHalfLifeMultiplay::GoToIntermission hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_GoToIntermission;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_GoToIntermission;

// CHalfLifeMultiplay::BalanceTeams hook
typedef IVoidHookChainClassImpl<class CHalfLifeMultiplay> CReGameHook_CSGameRules_BalanceTeams;
typedef IVoidHookChainRegistryClassEmptyImpl<class CHalfLifeMultiplay> CReGameHookRegistry_CSGameRules_BalanceTeams;

class CReGameHookchains: public IReGameHookchains {
public:
	// CBasePlayer virtual
	CReGameHookRegistry_CBasePlayer_Spawn m_CBasePlayer_Spawn;
	CReGameHookRegistry_CBasePlayer_Precache m_CBasePlayer_Precache;
	CReGameHookRegistry_CBasePlayer_ObjectCaps m_CBasePlayer_ObjectCaps;
	CReGameHookRegistry_CBasePlayer_Classify m_CBasePlayer_Classify;
	CReGameHookRegistry_CBasePlayer_TraceAttack m_CBasePlayer_TraceAttack;
	CReGameHookRegistry_CBasePlayer_TakeDamage m_CBasePlayer_TakeDamage;
	CReGameHookRegistry_CBasePlayer_TakeHealth m_CBasePlayer_TakeHealth;
	CReGameHookRegistry_CBasePlayer_Killed m_CBasePlayer_Killed;
	CReGameHookRegistry_CBasePlayer_AddPoints m_CBasePlayer_AddPoints;
	CReGameHookRegistry_CBasePlayer_AddPointsToTeam m_CBasePlayer_AddPointsToTeam;
	CReGameHookRegistry_CBasePlayer_AddPlayerItem m_CBasePlayer_AddPlayerItem;
	CReGameHookRegistry_CBasePlayer_RemovePlayerItem m_CBasePlayer_RemovePlayerItem;
	CReGameHookRegistry_CBasePlayer_GiveAmmo m_CBasePlayer_GiveAmmo;
	CReGameHookRegistry_CBasePlayer_ResetMaxSpeed m_CBasePlayer_ResetMaxSpeed;
	CReGameHookRegistry_CBasePlayer_Jump m_CBasePlayer_Jump;
	CReGameHookRegistry_CBasePlayer_Duck m_CBasePlayer_Duck;
	CReGameHookRegistry_CBasePlayer_PreThink m_CBasePlayer_PreThink;
	CReGameHookRegistry_CBasePlayer_PostThink m_CBasePlayer_PostThink;
	CReGameHookRegistry_CBasePlayer_UpdateClientData m_CBasePlayer_UpdateClientData;
	CReGameHookRegistry_CBasePlayer_ImpulseCommands m_CBasePlayer_ImpulseCommands;
	CReGameHookRegistry_CBasePlayer_RoundRespawn m_CBasePlayer_RoundRespawn;
	CReGameHookRegistry_CBasePlayer_Blind m_CBasePlayer_Blind;

	CReGameHookRegistry_CBasePlayer_Observer_IsValidTarget m_CBasePlayer_Observer_IsValidTarget;
	CReGameHookRegistry_CBasePlayer_SetAnimation m_CBasePlayer_SetAnimation;
	CReGameHookRegistry_CBasePlayer_GiveDefaultItems m_CBasePlayer_GiveDefaultItems;
	CReGameHookRegistry_CBasePlayer_GiveNamedItem m_CBasePlayer_GiveNamedItem;
	CReGameHookRegistry_CBasePlayer_AddAccount m_CBasePlayer_AddAccount;
	CReGameHookRegistry_CBasePlayer_GiveShield m_CBasePlayer_GiveShield;
	CReGameHookRegistry_CBasePlayer_SetClientUserInfoModel m_CBasePlayer_SetClientUserInfoModel;
	CReGameHookRegistry_CBasePlayer_SetClientUserInfoName m_CBasePlayer_SetClientUserInfoName;
	CReGameHookRegistry_CBaseAnimating_ResetSequenceInfo m_CBaseAnimating_ResetSequenceInfo;

	CReGameHookRegistry_GetForceCamera m_GetForceCamera;
	CReGameHookRegistry_PlayerBlind m_PlayerBlind;
	CReGameHookRegistry_RadiusFlash_TraceLine m_RadiusFlash_TraceLine;
	CReGameHookRegistry_RoundEnd m_RoundEnd;
	CReGameHookRegistry_CanBuyThis m_CanBuyThis;
	CReGameHookRegistry_InstallGameRules m_InstallGameRules;
	CReGameHookRegistry_PM_Init m_PM_Init;
	CReGameHookRegistry_PM_Move m_PM_Move;
	CReGameHookRegistry_PM_AirMove m_PM_AirMove;
	CReGameHookRegistry_HandleMenu_ChooseAppearance m_HandleMenu_ChooseAppearance;
	CReGameHookRegistry_HandleMenu_ChooseTeam m_HandleMenu_ChooseTeam;
	CReGameHookRegistry_ShowMenu m_ShowMenu;
	CReGameHookRegistry_ShowVGUIMenu m_ShowVGUIMenu;

	CReGameHookRegistry_CSGameRules_FShouldSwitchWeapon m_CSGameRules_FShouldSwitchWeapon;
	CReGameHookRegistry_CSGameRules_GetNextBestWeapon m_CSGameRules_GetNextBestWeapon;
	CReGameHookRegistry_CSGameRules_FlPlayerFallDamage m_CSGameRules_FlPlayerFallDamage;
	CReGameHookRegistry_CSGameRules_FPlayerCanTakeDamage m_CSGameRules_FPlayerCanTakeDamage;
	CReGameHookRegistry_CSGameRules_PlayerSpawn m_CSGameRules_PlayerSpawn;
	CReGameHookRegistry_CSGameRules_FPlayerCanRespawn m_CSGameRules_FPlayerCanRespawn;
	CReGameHookRegistry_CSGameRules_GetPlayerSpawnSpot m_CSGameRules_GetPlayerSpawnSpot;
	CReGameHookRegistry_CSGameRules_ClientUserInfoChanged m_CSGameRules_ClientUserInfoChanged;
	CReGameHookRegistry_CSGameRules_PlayerKilled m_CSGameRules_PlayerKilled;
	CReGameHookRegistry_CSGameRules_DeathNotice m_CSGameRules_DeathNotice;
	CReGameHookRegistry_CSGameRules_CanHavePlayerItem m_CSGameRules_CanHavePlayerItem;
	CReGameHookRegistry_CSGameRules_DeadPlayerWeapons m_CSGameRules_DeadPlayerWeapons;
	CReGameHookRegistry_CSGameRules_ServerDeactivate m_CSGameRules_ServerDeactivate;
	CReGameHookRegistry_CSGameRules_CheckMapConditions m_CSGameRules_CheckMapConditions;
	CReGameHookRegistry_CSGameRules_CleanUpMap m_CSGameRules_CleanUpMap;
	CReGameHookRegistry_CSGameRules_RestartRound m_CSGameRules_RestartRound;
	CReGameHookRegistry_CSGameRules_CheckWinConditions m_CSGameRules_CheckWinConditions;
	CReGameHookRegistry_CSGameRules_RemoveGuns m_CSGameRules_RemoveGuns;
	CReGameHookRegistry_CSGameRules_GiveC4 m_CSGameRules_GiveC4;
	CReGameHookRegistry_CSGameRules_ChangeLevel m_CSGameRules_ChangeLevel;
	CReGameHookRegistry_CSGameRules_GoToIntermission m_CSGameRules_GoToIntermission;
	CReGameHookRegistry_CSGameRules_BalanceTeams m_CSGameRules_BalanceTeams;

	CReGameHookRegistry_CanBuyThisItem m_CanBuyThisItem;
	CReGameHookRegistry_CBasePlayer_DropPlayerItem m_CBasePlayer_DropPlayerItem;
	CReGameHookRegistry_CWeaponBox_Touch m_CWeaponBox_Touch;
	CReGameHookRegistry_CArmoury_Touch m_CArmoury_ArmouryTouch;

public:
	virtual IReGameHookRegistry_CBasePlayer_Spawn* CBasePlayer_Spawn();
	virtual IReGameHookRegistry_CBasePlayer_Precache* CBasePlayer_Precache();
	virtual IReGameHookRegistry_CBasePlayer_ObjectCaps* CBasePlayer_ObjectCaps();
	virtual IReGameHookRegistry_CBasePlayer_Classify* CBasePlayer_Classify();
	virtual IReGameHookRegistry_CBasePlayer_TraceAttack* CBasePlayer_TraceAttack();
	virtual IReGameHookRegistry_CBasePlayer_TakeDamage* CBasePlayer_TakeDamage();
	virtual IReGameHookRegistry_CBasePlayer_TakeHealth* CBasePlayer_TakeHealth();
	virtual IReGameHookRegistry_CBasePlayer_Killed* CBasePlayer_Killed();
	virtual IReGameHookRegistry_CBasePlayer_AddPoints* CBasePlayer_AddPoints();
	virtual IReGameHookRegistry_CBasePlayer_AddPointsToTeam* CBasePlayer_AddPointsToTeam();
	virtual IReGameHookRegistry_CBasePlayer_AddPlayerItem* CBasePlayer_AddPlayerItem();
	virtual IReGameHookRegistry_CBasePlayer_RemovePlayerItem* CBasePlayer_RemovePlayerItem();
	virtual IReGameHookRegistry_CBasePlayer_GiveAmmo* CBasePlayer_GiveAmmo();
	virtual IReGameHookRegistry_CBasePlayer_ResetMaxSpeed* CBasePlayer_ResetMaxSpeed();
	virtual IReGameHookRegistry_CBasePlayer_Jump* CBasePlayer_Jump();
	virtual IReGameHookRegistry_CBasePlayer_Duck* CBasePlayer_Duck();
	virtual IReGameHookRegistry_CBasePlayer_PreThink* CBasePlayer_PreThink();
	virtual IReGameHookRegistry_CBasePlayer_PostThink* CBasePlayer_PostThink();
	virtual IReGameHookRegistry_CBasePlayer_UpdateClientData* CBasePlayer_UpdateClientData();
	virtual IReGameHookRegistry_CBasePlayer_ImpulseCommands* CBasePlayer_ImpulseCommands();
	virtual IReGameHookRegistry_CBasePlayer_RoundRespawn* CBasePlayer_RoundRespawn();
	virtual IReGameHookRegistry_CBasePlayer_Blind* CBasePlayer_Blind();

	virtual IReGameHookRegistry_CBasePlayer_Observer_IsValidTarget* CBasePlayer_Observer_IsValidTarget();
	virtual IReGameHookRegistry_CBasePlayer_SetAnimation* CBasePlayer_SetAnimation();
	virtual IReGameHookRegistry_CBasePlayer_GiveDefaultItems* CBasePlayer_GiveDefaultItems();
	virtual IReGameHookRegistry_CBasePlayer_GiveNamedItem* CBasePlayer_GiveNamedItem();
	virtual IReGameHookRegistry_CBasePlayer_AddAccount* CBasePlayer_AddAccount();
	virtual IReGameHookRegistry_CBasePlayer_GiveShield* CBasePlayer_GiveShield();
	virtual IReGameHookRegistry_CBasePlayer_SetClientUserInfoModel* CBasePlayer_SetClientUserInfoModel();
	virtual IReGameHookRegistry_CBasePlayer_SetClientUserInfoName* CBasePlayer_SetClientUserInfoName();
	virtual IReGameHookRegistry_CBaseAnimating_ResetSequenceInfo* CBaseAnimating_ResetSequenceInfo();

	virtual IReGameHookRegistry_GetForceCamera* GetForceCamera();
	virtual IReGameHookRegistry_PlayerBlind* PlayerBlind();
	virtual IReGameHookRegistry_RadiusFlash_TraceLine* RadiusFlash_TraceLine();
	virtual IReGameHookRegistry_RoundEnd* RoundEnd();
	virtual IReGameHookRegistry_CanBuyThis* CanBuyThis();
	virtual IReGameHookRegistry_InstallGameRules* InstallGameRules();
	virtual IReGameHookRegistry_PM_Init* PM_Init();
	virtual IReGameHookRegistry_PM_Move* PM_Move();
	virtual IReGameHookRegistry_PM_AirMove* PM_AirMove();
	virtual IReGameHookRegistry_HandleMenu_ChooseAppearance* HandleMenu_ChooseAppearance();
	virtual IReGameHookRegistry_HandleMenu_ChooseTeam* HandleMenu_ChooseTeam();
	virtual IReGameHookRegistry_ShowMenu* ShowMenu();
	virtual IReGameHookRegistry_ShowVGUIMenu* ShowVGUIMenu();

	virtual IReGameHookRegistry_CSGameRules_FShouldSwitchWeapon* CSGameRules_FShouldSwitchWeapon();
	virtual IReGameHookRegistry_CSGameRules_GetNextBestWeapon* CSGameRules_GetNextBestWeapon();
	virtual IReGameHookRegistry_CSGameRules_FlPlayerFallDamage* CSGameRules_FlPlayerFallDamage();
	virtual IReGameHookRegistry_CSGameRules_FPlayerCanTakeDamage* CSGameRules_FPlayerCanTakeDamage();
	virtual IReGameHookRegistry_CSGameRules_PlayerSpawn* CSGameRules_PlayerSpawn();
	virtual IReGameHookRegistry_CSGameRules_FPlayerCanRespawn* CSGameRules_FPlayerCanRespawn();
	virtual IReGameHookRegistry_CSGameRules_GetPlayerSpawnSpot* CSGameRules_GetPlayerSpawnSpot();
	virtual IReGameHookRegistry_CSGameRules_ClientUserInfoChanged* CSGameRules_ClientUserInfoChanged();
	virtual IReGameHookRegistry_CSGameRules_PlayerKilled* CSGameRules_PlayerKilled();
	virtual IReGameHookRegistry_CSGameRules_DeathNotice* CSGameRules_DeathNotice();
	virtual IReGameHookRegistry_CSGameRules_CanHavePlayerItem* CSGameRules_CanHavePlayerItem();
	virtual IReGameHookRegistry_CSGameRules_DeadPlayerWeapons* CSGameRules_DeadPlayerWeapons();
	virtual IReGameHookRegistry_CSGameRules_ServerDeactivate* CSGameRules_ServerDeactivate();
	virtual IReGameHookRegistry_CSGameRules_CheckMapConditions* CSGameRules_CheckMapConditions();
	virtual IReGameHookRegistry_CSGameRules_CleanUpMap* CSGameRules_CleanUpMap();
	virtual IReGameHookRegistry_CSGameRules_RestartRound* CSGameRules_RestartRound();
	virtual IReGameHookRegistry_CSGameRules_CheckWinConditions* CSGameRules_CheckWinConditions();
	virtual IReGameHookRegistry_CSGameRules_RemoveGuns* CSGameRules_RemoveGuns();
	virtual IReGameHookRegistry_CSGameRules_GiveC4* CSGameRules_GiveC4();
	virtual IReGameHookRegistry_CSGameRules_ChangeLevel* CSGameRules_ChangeLevel();
	virtual IReGameHookRegistry_CSGameRules_GoToIntermission* CSGameRules_GoToIntermission();
	virtual IReGameHookRegistry_CSGameRules_BalanceTeams* CSGameRules_BalanceTeams();

	virtual IReGameHookRegistry_CanBuyThisItem* CanBuyThisItem();
	virtual IReGameHookRegistry_CBasePlayer_DropPlayerItem* CBasePlayer_DropPlayerItem();
	virtual IReGameHookRegistry_CWeaponBox_Touch* CWeaponBox_Touch();
	virtual IReGameHookRegistry_CArmoury_Touch* CArmoury_Touch();
};

extern CReGameHookchains g_ReGameHookchains;
extern ReGameFuncs_t g_ReGameApiFuncs;

class CReGameApi: public IReGameApi {
public:
	virtual int GetMajorVersion();
	virtual int GetMinorVersion();

	virtual const ReGameFuncs_t *GetFuncs();
	virtual IReGameHookchains *GetHookchains();

	virtual CGameRules* GetGameRules();
	virtual WeaponInfoStruct* GetWeaponInfo(int weaponID);
	virtual WeaponInfoStruct* GetWeaponInfo(const char* weaponName);
	virtual playermove_t* GetPlayerMove();
	virtual WeaponSlotInfo* GetWeaponSlot(WeaponIdType weaponID);
	virtual WeaponSlotInfo* GetWeaponSlot(const char* weaponName);
};

void Regamedll_ChangeString_api(char *&dest, const char *source);
void RadiusDamage_api(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType);

void ClearMultiDamage_api();
void ApplyMultiDamage_api(entvars_t *pevInflictor, entvars_t *pevAttacker);
void AddMultiDamage_api(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);
