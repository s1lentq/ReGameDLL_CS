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

#include <hookchains.h>
#include <interface.h>
#include <cbase.h>
#include <gamerules.h>
#include <client.h>
#include <API/CSInterfaces.h>

#define REGAMEDLL_API_VERSION_MAJOR 5
#define REGAMEDLL_API_VERSION_MINOR 6

// CBasePlayer::Spawn hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_Spawn;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Spawn;

// CBasePlayer::Precache hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_Precache;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Precache;

// CBasePlayer::ObjectCaps hook
typedef IHookChainClass<int, class CBasePlayer> IReGameHook_CBasePlayer_ObjectCaps;
typedef IHookChainRegistryClass<int, class CBasePlayer> IReGameHookRegistry_CBasePlayer_ObjectCaps;

// CBasePlayer::Classify hook
typedef IHookChainClass<int, class CBasePlayer> IReGameHook_CBasePlayer_Classify;
typedef IHookChainRegistryClass<int, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Classify;

// CBasePlayer::TraceAttack hook
typedef IHookChainClass<void, class CBasePlayer, struct entvars_s *, float, Vector &, struct TraceResult *, int> IReGameHook_CBasePlayer_TraceAttack;
typedef IHookChainRegistryClass<void, class CBasePlayer, struct entvars_s *, float, Vector &, struct TraceResult *, int> IReGameHookRegistry_CBasePlayer_TraceAttack;

// CBasePlayer::TakeDamage hook
typedef IHookChainClass<BOOL, class CBasePlayer, struct entvars_s *, struct entvars_s *, float&, int> IReGameHook_CBasePlayer_TakeDamage;
typedef IHookChainRegistryClass<BOOL, class CBasePlayer, struct entvars_s *, struct entvars_s *, float&, int> IReGameHookRegistry_CBasePlayer_TakeDamage;

// CBasePlayer::TakeHealth hook
typedef IHookChainClass<BOOL, class CBasePlayer, float, int> IReGameHook_CBasePlayer_TakeHealth;
typedef IHookChainRegistryClass<BOOL, class CBasePlayer, float, int> IReGameHookRegistry_CBasePlayer_TakeHealth;

// CBasePlayer::Killed hook
typedef IHookChainClass<void, class CBasePlayer, struct entvars_s *, int> IReGameHook_CBasePlayer_Killed;
typedef IHookChainRegistryClass<void, class CBasePlayer, struct entvars_s *, int> IReGameHookRegistry_CBasePlayer_Killed;

// CBasePlayer::AddPoints hook
typedef IHookChainClass<void, class CBasePlayer, int, BOOL> IReGameHook_CBasePlayer_AddPoints;
typedef IHookChainRegistryClass<void, class CBasePlayer, int, BOOL> IReGameHookRegistry_CBasePlayer_AddPoints;

// CBasePlayer::AddPointsToTeam hook
typedef IHookChainClass<void, class CBasePlayer, int, BOOL> IReGameHook_CBasePlayer_AddPointsToTeam;
typedef IHookChainRegistryClass<void, class CBasePlayer, int, BOOL> IReGameHookRegistry_CBasePlayer_AddPointsToTeam;

// CBasePlayer::AddPlayerItem hook
typedef IHookChainClass<BOOL, class CBasePlayer, class CBasePlayerItem *> IReGameHook_CBasePlayer_AddPlayerItem;
typedef IHookChainRegistryClass<BOOL, class CBasePlayer, class CBasePlayerItem *> IReGameHookRegistry_CBasePlayer_AddPlayerItem;

// CBasePlayer::RemovePlayerItem hook
typedef IHookChainClass<BOOL, class CBasePlayer, class CBasePlayerItem *> IReGameHook_CBasePlayer_RemovePlayerItem;
typedef IHookChainRegistryClass<BOOL, class CBasePlayer, class CBasePlayerItem *> IReGameHookRegistry_CBasePlayer_RemovePlayerItem;

// CBasePlayer::GiveAmmo hook
typedef IHookChainClass<int, class CBasePlayer, int , const char *, int> IReGameHook_CBasePlayer_GiveAmmo;
typedef IHookChainRegistryClass<int, class CBasePlayer, int , const char *, int> IReGameHookRegistry_CBasePlayer_GiveAmmo;

// CBasePlayer::ResetMaxSpeed hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_ResetMaxSpeed;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_ResetMaxSpeed;

// CBasePlayer::Jump hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_Jump;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Jump;

// CBasePlayer::Duck hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_Duck;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Duck;

// CBasePlayer::PreThink hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_PreThink;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_PreThink;

// CBasePlayer::PostThink hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_PostThink;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_PostThink;

// CBasePlayer::UpdateClientData hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_UpdateClientData;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_UpdateClientData;

// CBasePlayer::ImpulseCommands hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_ImpulseCommands;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_ImpulseCommands;

// CBasePlayer::RoundRespawn hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_RoundRespawn;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_RoundRespawn;

// CBasePlayer::Blind hook
typedef IHookChainClass<void, class CBasePlayer, float, float, float, int> IReGameHook_CBasePlayer_Blind;
typedef IHookChainRegistryClass<void, class CBasePlayer, float, float, float, int> IReGameHookRegistry_CBasePlayer_Blind;

// CBasePlayer::Observer_IsValidTarget hook
typedef IHookChainClass<class CBasePlayer *, class CBasePlayer, int, bool> IReGameHook_CBasePlayer_Observer_IsValidTarget;
typedef IHookChainRegistryClass<class CBasePlayer *, class CBasePlayer, int, bool> IReGameHookRegistry_CBasePlayer_Observer_IsValidTarget;

// CBasePlayer::SetAnimation hook
typedef IHookChainClass<void, class CBasePlayer, PLAYER_ANIM> IReGameHook_CBasePlayer_SetAnimation;
typedef IHookChainRegistryClass<void, class CBasePlayer, PLAYER_ANIM> IReGameHookRegistry_CBasePlayer_SetAnimation;

// CBasePlayer::GiveDefaultItems hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_GiveDefaultItems;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_GiveDefaultItems;

// CBasePlayer::GiveNamedItem hook
typedef IHookChainClass<class CBaseEntity *, class CBasePlayer, const char *> IReGameHook_CBasePlayer_GiveNamedItem;
typedef IHookChainRegistryClass<class CBaseEntity *, class CBasePlayer, const char *> IReGameHookRegistry_CBasePlayer_GiveNamedItem;

// CBasePlayer::AddAccount hook
typedef IHookChainClass<void, class CBasePlayer, int, RewardType, bool> IReGameHook_CBasePlayer_AddAccount;
typedef IHookChainRegistryClass<void, class CBasePlayer, int, RewardType, bool> IReGameHookRegistry_CBasePlayer_AddAccount;

// CBasePlayer::GiveShield hook
typedef IHookChainClass<void, class CBasePlayer, bool> IReGameHook_CBasePlayer_GiveShield;
typedef IHookChainRegistryClass<void, class CBasePlayer, bool> IReGameHookRegistry_CBasePlayer_GiveShield;

// CBasePlayer:SetClientUserInfoModel hook
typedef IHookChainClass<void, class CBasePlayer, char *, char *> IReGameHook_CBasePlayer_SetClientUserInfoModel;
typedef IHookChainRegistryClass<void, class CBasePlayer, char *, char *> IReGameHookRegistry_CBasePlayer_SetClientUserInfoModel;

// CBasePlayer:SetClientUserInfoName hook
typedef IHookChainClass<bool, class CBasePlayer, char *, char *> IReGameHook_CBasePlayer_SetClientUserInfoName;
typedef IHookChainRegistryClass<bool, class CBasePlayer, char *, char *> IReGameHookRegistry_CBasePlayer_SetClientUserInfoName;

// CBasePlayer::HasRestrictItem hook
typedef IHookChainClass<bool, class CBasePlayer, ItemID, ItemRestType> IReGameHook_CBasePlayer_HasRestrictItem;
typedef IHookChainRegistryClass<bool, class CBasePlayer, ItemID, ItemRestType> IReGameHookRegistry_CBasePlayer_HasRestrictItem;

// CBasePlayer::DropPlayerItem hook
typedef IHookChainClass<class CBaseEntity *, class CBasePlayer, const char *> IReGameHook_CBasePlayer_DropPlayerItem;
typedef IHookChainRegistryClass<class CBaseEntity *, class CBasePlayer, const char *> IReGameHookRegistry_CBasePlayer_DropPlayerItem;

// CBasePlayer::DropShield hook
typedef IHookChainClass<class CBaseEntity *, class CBasePlayer, bool> IReGameHook_CBasePlayer_DropShield;
typedef IHookChainRegistryClass<class CBaseEntity *, class CBasePlayer, bool> IReGameHookRegistry_CBasePlayer_DropShield;

// CBasePlayer::OnSpawnEquip hook
typedef IHookChainClass<void, class CBasePlayer, bool, bool> IReGameHook_CBasePlayer_OnSpawnEquip;
typedef IHookChainRegistryClass<void, class CBasePlayer, bool, bool> IReGameHookRegistry_CBasePlayer_OnSpawnEquip;

// CBasePlayer::Radio hook
typedef IHookChainClass<void, class CBasePlayer, const char *, const char *, short, bool> IReGameHook_CBasePlayer_Radio;
typedef IHookChainRegistryClass<void, class CBasePlayer, const char *, const char *, short, bool> IReGameHookRegistry_CBasePlayer_Radio;

// CBasePlayer::Disappear hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_Disappear;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Disappear;

// CBasePlayer::MakeVIP hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_MakeVIP;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_MakeVIP;

// CBasePlayer::MakeBomber hook
typedef IHookChainClass<bool, class CBasePlayer> IReGameHook_CBasePlayer_MakeBomber;
typedef IHookChainRegistryClass<bool, class CBasePlayer> IReGameHookRegistry_CBasePlayer_MakeBomber;

// CBasePlayer::StartObserver hook
typedef IHookChainClass<void, class CBasePlayer, Vector &, Vector &> IReGameHook_CBasePlayer_StartObserver;
typedef IHookChainRegistryClass<void, class CBasePlayer, Vector &, Vector &> IReGameHookRegistry_CBasePlayer_StartObserver;

// CBasePlayer::GetIntoGame hook
typedef IHookChainClass<bool, class CBasePlayer> IReGameHook_CBasePlayer_GetIntoGame;
typedef IHookChainRegistryClass<bool, class CBasePlayer> IReGameHookRegistry_CBasePlayer_GetIntoGame;

// CBaseAnimating::ResetSequenceInfo hook
typedef IHookChainClass<void, class CBaseAnimating> IReGameHook_CBaseAnimating_ResetSequenceInfo;
typedef IHookChainRegistryClass<void, class CBaseAnimating> IReGameHookRegistry_CBaseAnimating_ResetSequenceInfo;

// GetForceCamera hook
typedef IHookChain<int, class CBasePlayer *> IReGameHook_GetForceCamera;
typedef IHookChainRegistry<int, class CBasePlayer *> IReGameHookRegistry_GetForceCamera;

// PlayerBlind hook
typedef IHookChain<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *, float, float, int, Vector &> IReGameHook_PlayerBlind;
typedef IHookChainRegistry<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *, float, float, int, Vector &> IReGameHookRegistry_PlayerBlind;

// RadiusFlash_TraceLine hook
typedef IHookChain<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *, Vector &, Vector &, struct TraceResult *> IReGameHook_RadiusFlash_TraceLine;
typedef IHookChainRegistry<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *, Vector &, Vector &, struct TraceResult *> IReGameHookRegistry_RadiusFlash_TraceLine;

// RoundEnd hook
typedef IHookChain<bool, int, ScenarioEventEndRound, float> IReGameHook_RoundEnd;
typedef IHookChainRegistry<bool, int, ScenarioEventEndRound, float> IReGameHookRegistry_RoundEnd;

// InstallGameRules hook
typedef IHookChain<class CGameRules *> IReGameHook_InstallGameRules;
typedef IHookChainRegistry<class CGameRules *> IReGameHookRegistry_InstallGameRules;

// PM_Init hook
typedef IHookChain<void, struct playermove_s *> IReGameHook_PM_Init;
typedef IHookChainRegistry<void, struct playermove_s *> IReGameHookRegistry_PM_Init;

// PM_Move hook
typedef IHookChain<void, struct playermove_s *, int> IReGameHook_PM_Move;
typedef IHookChainRegistry<void, struct playermove_s *, int> IReGameHookRegistry_PM_Move;

// PM_AirMove hook
typedef IHookChain<void, int> IReGameHook_PM_AirMove;
typedef IHookChainRegistry<void, int> IReGameHookRegistry_PM_AirMove;

// HandleMenu_ChooseAppearance hook
typedef IHookChain<void, class CBasePlayer *, int> IReGameHook_HandleMenu_ChooseAppearance;
typedef IHookChainRegistry<void, class CBasePlayer *, int> IReGameHookRegistry_HandleMenu_ChooseAppearance;

// HandleMenu_ChooseTeam hook
typedef IHookChain<BOOL, class CBasePlayer *, int> IReGameHook_HandleMenu_ChooseTeam;
typedef IHookChainRegistry<BOOL, class CBasePlayer *, int> IReGameHookRegistry_HandleMenu_ChooseTeam;

// ShowMenu hook
typedef IHookChain<void, class CBasePlayer *, int, int, BOOL, char *> IReGameHook_ShowMenu;
typedef IHookChainRegistry<void, class CBasePlayer *, int, int, BOOL, char *> IReGameHookRegistry_ShowMenu;

// ShowVGUIMenu hook
typedef IHookChain<void, class CBasePlayer *, int, int, char *> IReGameHook_ShowVGUIMenu;
typedef IHookChainRegistry<void, class CBasePlayer *, int, int, char *> IReGameHookRegistry_ShowVGUIMenu;

// BuyGunAmmo hook
typedef IHookChain<bool, class CBasePlayer *, class CBasePlayerItem *, bool> IReGameHook_BuyGunAmmo;
typedef IHookChainRegistry<bool, class CBasePlayer *, class CBasePlayerItem *, bool> IReGameHookRegistry_BuyGunAmmo;

// BuyWeaponByWeaponID hook
typedef IHookChain<class CBaseEntity *, class CBasePlayer *, WeaponIdType> IReGameHook_BuyWeaponByWeaponID;
typedef IHookChainRegistry<class CBaseEntity *, class CBasePlayer *, WeaponIdType> IReGameHookRegistry_BuyWeaponByWeaponID;

// InternalCommand hook
typedef IHookChain<void, edict_t *, const char *, const char *> IReGameHook_InternalCommand;
typedef IHookChainRegistry<void, edict_t *, const char *, const char *> IReGameHookRegistry_InternalCommand;

// CHalfLifeMultiplay::FShouldSwitchWeapon hook
typedef IHookChain<BOOL, class CBasePlayer *, class CBasePlayerItem *> IReGameHook_CSGameRules_FShouldSwitchWeapon;
typedef IHookChainRegistry<BOOL, class CBasePlayer *, class CBasePlayerItem *> IReGameHookRegistry_CSGameRules_FShouldSwitchWeapon;

// CHalfLifeMultiplay::GetNextBestWeapon hook
typedef IHookChain<BOOL, class CBasePlayer *, class CBasePlayerItem *> IReGameHook_CSGameRules_GetNextBestWeapon;
typedef IHookChainRegistry<BOOL, class CBasePlayer *, class CBasePlayerItem *> IReGameHookRegistry_CSGameRules_GetNextBestWeapon;

// CHalfLifeMultiplay::FlPlayerFallDamage hook
typedef IHookChain<float, class CBasePlayer *> IReGameHook_CSGameRules_FlPlayerFallDamage;
typedef IHookChainRegistry<float, class CBasePlayer *> IReGameHookRegistry_CSGameRules_FlPlayerFallDamage;

// CHalfLifeMultiplay::FPlayerCanTakeDamage hook
typedef IHookChain<BOOL, class CBasePlayer *, CBaseEntity *> IReGameHook_CSGameRules_FPlayerCanTakeDamage;
typedef IHookChainRegistry<BOOL, class CBasePlayer *, CBaseEntity *> IReGameHookRegistry_CSGameRules_FPlayerCanTakeDamage;

// CHalfLifeMultiplay::PlayerSpawn hook
typedef IHookChain<void, class CBasePlayer *> IReGameHook_CSGameRules_PlayerSpawn;
typedef IHookChainRegistry<void, class CBasePlayer *> IReGameHookRegistry_CSGameRules_PlayerSpawn;

// CHalfLifeMultiplay::FPlayerCanRespawn hook
typedef IHookChain<BOOL, class CBasePlayer *> IReGameHook_CSGameRules_FPlayerCanRespawn;
typedef IHookChainRegistry<BOOL, class CBasePlayer *> IReGameHookRegistry_CSGameRules_FPlayerCanRespawn;

// CHalfLifeMultiplay::GetPlayerSpawnSpot hook
typedef IHookChain<struct edict_s *, class CBasePlayer *> IReGameHook_CSGameRules_GetPlayerSpawnSpot;
typedef IHookChainRegistry<struct edict_s *, class CBasePlayer *> IReGameHookRegistry_CSGameRules_GetPlayerSpawnSpot;

// CHalfLifeMultiplay::ClientUserInfoChanged hook
typedef IHookChain<void, class CBasePlayer *, char *> IReGameHook_CSGameRules_ClientUserInfoChanged;
typedef IHookChainRegistry<void, class CBasePlayer *, char *> IReGameHookRegistry_CSGameRules_ClientUserInfoChanged;

// CHalfLifeMultiplay::PlayerKilled hook
typedef IHookChain<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *> IReGameHook_CSGameRules_PlayerKilled;
typedef IHookChainRegistry<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *> IReGameHookRegistry_CSGameRules_PlayerKilled;

// CHalfLifeMultiplay::DeathNotice hook
typedef IHookChain<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *> IReGameHook_CSGameRules_DeathNotice;
typedef IHookChainRegistry<void, class CBasePlayer *, struct entvars_s *, struct entvars_s *> IReGameHookRegistry_CSGameRules_DeathNotice;

// CHalfLifeMultiplay::CanHavePlayerItem hook
typedef IHookChain<BOOL, class CBasePlayer *, class CBasePlayerItem *> IReGameHook_CSGameRules_CanHavePlayerItem;
typedef IHookChainRegistry<BOOL, class CBasePlayer *, class CBasePlayerItem *> IReGameHookRegistry_CSGameRules_CanHavePlayerItem;

// CHalfLifeMultiplay::DeadPlayerWeapons hook
typedef IHookChain<int, class CBasePlayer *> IReGameHook_CSGameRules_DeadPlayerWeapons;
typedef IHookChainRegistry<int, class CBasePlayer *> IReGameHookRegistry_CSGameRules_DeadPlayerWeapons;

// CHalfLifeMultiplay::ServerDeactivate hook
typedef IHookChain<void> IReGameHook_CSGameRules_ServerDeactivate;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_ServerDeactivate;

// CHalfLifeMultiplay::CheckMapConditions hook
typedef IHookChain<void> IReGameHook_CSGameRules_CheckMapConditions;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_CheckMapConditions;

// CHalfLifeMultiplay::CleanUpMap hook
typedef IHookChain<void> IReGameHook_CSGameRules_CleanUpMap;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_CleanUpMap;

// CHalfLifeMultiplay::RestartRound hook
typedef IHookChain<void> IReGameHook_CSGameRules_RestartRound;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_RestartRound;

// CHalfLifeMultiplay::CheckWinConditions hook
typedef IHookChain<void> IReGameHook_CSGameRules_CheckWinConditions;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_CheckWinConditions;

// CHalfLifeMultiplay::RemoveGuns hook
typedef IHookChain<void> IReGameHook_CSGameRules_RemoveGuns;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_RemoveGuns;

// CHalfLifeMultiplay::GiveC4 hook
typedef IHookChain<void> IReGameHook_CSGameRules_GiveC4;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_GiveC4;

// CHalfLifeMultiplay::ChangeLevel hook
typedef IHookChain<void> IReGameHook_CSGameRules_ChangeLevel;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_ChangeLevel;

// CHalfLifeMultiplay::GoToIntermission hook
typedef IHookChain<void> IReGameHook_CSGameRules_GoToIntermission;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_GoToIntermission;

// CHalfLifeMultiplay::BalanceTeams hook
typedef IHookChain<void> IReGameHook_CSGameRules_BalanceTeams;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_BalanceTeams;

// CHalfLifeMultiplay::OnRoundFreezeEnd hook
typedef IHookChain<void> IReGameHook_CSGameRules_OnRoundFreezeEnd;
typedef IHookChainRegistry<void> IReGameHookRegistry_CSGameRules_OnRoundFreezeEnd;

// CSGameRules::CanPlayerHearPlayer hook
typedef IHookChain<bool, class CBasePlayer *, class CBasePlayer *> IReGameHook_CSGameRules_CanPlayerHearPlayer;
typedef IHookChainRegistry<bool, class CBasePlayer *, class CBasePlayer *> IReGameHookRegistry_CSGameRules_CanPlayerHearPlayer;

// PM_UpdateStepSound hook
typedef IHookChain<void> IReGameHook_PM_UpdateStepSound;
typedef IHookChainRegistry<void> IReGameHookRegistry_PM_UpdateStepSound;

// CBasePlayer::StartDeathCam hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_StartDeathCam;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_StartDeathCam;

// CBasePlayer::SwitchTeam hook
typedef IHookChainClass<void, class CBasePlayer> IReGameHook_CBasePlayer_SwitchTeam;
typedef IHookChainRegistryClass<void, class CBasePlayer> IReGameHookRegistry_CBasePlayer_SwitchTeam;

// CBasePlayer::CanSwitchTeam hook
typedef IHookChainClass<bool, class CBasePlayer, TeamName> IReGameHook_CBasePlayer_CanSwitchTeam;
typedef IHookChainRegistryClass<bool, class CBasePlayer, TeamName> IReGameHookRegistry_CBasePlayer_CanSwitchTeam;

// CBasePlayer::ThrowGrenade hook
typedef IHookChainClass<class CGrenade *, class CBasePlayer, class CBasePlayerWeapon *, Vector &, Vector &, float, unsigned short> IReGameHook_CBasePlayer_ThrowGrenade;
typedef IHookChainRegistryClass<class CGrenade *, class CBasePlayer, class CBasePlayerWeapon *, Vector &, Vector &, float, unsigned short> IReGameHookRegistry_CBasePlayer_ThrowGrenade;

// CWeaponBox::SetModel hook
typedef IHookChainClass<void, class CWeaponBox, const char *> IReGameHook_CWeaponBox_SetModel;
typedef IHookChainRegistryClass<void, class CWeaponBox, const char *> IReGameHookRegistry_CWeaponBox_SetModel;

// CGrenade::DefuseBombStart hook
typedef IHookChainClass<void, class CGrenade, class CBasePlayer *> IReGameHook_CGrenade_DefuseBombStart;
typedef IHookChainRegistryClass<void, class CGrenade, class CBasePlayer *> IReGameHookRegistry_CGrenade_DefuseBombStart;

// CGrenade::DefuseBombEnd hook
typedef IHookChainClass<void, class CGrenade, class CBasePlayer *, bool> IReGameHook_CGrenade_DefuseBombEnd;
typedef IHookChainRegistryClass<void, class CGrenade, class CBasePlayer *, bool> IReGameHookRegistry_CGrenade_DefuseBombEnd;

// CGrenade::ExplodeHeGrenade hook
typedef IHookChainClass<void, class CGrenade, struct TraceResult *, int> IReGameHook_CGrenade_ExplodeHeGrenade;
typedef IHookChainRegistryClass<void, class CGrenade, struct TraceResult *, int> IReGameHookRegistry_CGrenade_ExplodeHeGrenade;

// CGrenade::ExplodeFlashbang hook
typedef IHookChainClass<void, class CGrenade, struct TraceResult *, int> IReGameHook_CGrenade_ExplodeFlashbang;
typedef IHookChainRegistryClass<void, class CGrenade, struct TraceResult *, int> IReGameHookRegistry_CGrenade_ExplodeFlashbang;

// CGrenade::ExplodeSmokeGrenade hook
typedef IHookChainClass<void, class CGrenade> IReGameHook_CGrenade_ExplodeSmokeGrenade;
typedef IHookChainRegistryClass<void, class CGrenade> IReGameHookRegistry_CGrenade_ExplodeSmokeGrenade;

// CGrenade::ExplodeBomb hook
typedef IHookChainClass<void, class CGrenade, struct TraceResult *, int> IReGameHook_CGrenade_ExplodeBomb;
typedef IHookChainRegistryClass<void, class CGrenade, struct TraceResult *, int> IReGameHookRegistry_CGrenade_ExplodeBomb;

// ThrowHeGrenade hook
typedef IHookChain<class CGrenade *, entvars_t *, Vector &, Vector &, float, int, unsigned short> IReGameHook_ThrowHeGrenade;
typedef IHookChainRegistry<class CGrenade *, entvars_t *, Vector &, Vector &, float, int, unsigned short> IReGameHookRegistry_ThrowHeGrenade;

// ThrowFlashbang hook
typedef IHookChain<class CGrenade *, entvars_t *, Vector &, Vector &, float> IReGameHook_ThrowFlashbang;
typedef IHookChainRegistry<class CGrenade *, entvars_t *, Vector &, Vector &, float> IReGameHookRegistry_ThrowFlashbang;

// ThrowSmokeGrenade hook
typedef IHookChain<class CGrenade *, entvars_t *, Vector &, Vector &, float, unsigned short> IReGameHook_ThrowSmokeGrenade;
typedef IHookChainRegistry<class CGrenade *, entvars_t *, Vector &, Vector &, float, unsigned short> IReGameHookRegistry_ThrowSmokeGrenade;

// PlantBomb hook
typedef IHookChain<class CGrenade *, entvars_t *, Vector &, Vector &> IReGameHook_PlantBomb;
typedef IHookChainRegistry<class CGrenade *, entvars_t *, Vector &, Vector &> IReGameHookRegistry_PlantBomb;

class IReGameHookchains {
public:
	virtual ~IReGameHookchains() {}

	// CBasePlayer virtual
	virtual IReGameHookRegistry_CBasePlayer_Spawn *CBasePlayer_Spawn() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Precache *CBasePlayer_Precache() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ObjectCaps *CBasePlayer_ObjectCaps() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Classify *CBasePlayer_Classify() = 0;
	virtual IReGameHookRegistry_CBasePlayer_TraceAttack *CBasePlayer_TraceAttack() = 0;
	virtual IReGameHookRegistry_CBasePlayer_TakeDamage *CBasePlayer_TakeDamage() = 0;
	virtual IReGameHookRegistry_CBasePlayer_TakeHealth *CBasePlayer_TakeHealth() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Killed *CBasePlayer_Killed() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddPoints *CBasePlayer_AddPoints() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddPointsToTeam *CBasePlayer_AddPointsToTeam() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddPlayerItem *CBasePlayer_AddPlayerItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_RemovePlayerItem *CBasePlayer_RemovePlayerItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveAmmo *CBasePlayer_GiveAmmo() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ResetMaxSpeed *CBasePlayer_ResetMaxSpeed() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Jump *CBasePlayer_Jump() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Duck *CBasePlayer_Duck() = 0;
	virtual IReGameHookRegistry_CBasePlayer_PreThink *CBasePlayer_PreThink() = 0;
	virtual IReGameHookRegistry_CBasePlayer_PostThink *CBasePlayer_PostThink() = 0;
	virtual IReGameHookRegistry_CBasePlayer_UpdateClientData *CBasePlayer_UpdateClientData() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ImpulseCommands *CBasePlayer_ImpulseCommands() = 0;
	virtual IReGameHookRegistry_CBasePlayer_RoundRespawn *CBasePlayer_RoundRespawn() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Blind *CBasePlayer_Blind() = 0;

	virtual IReGameHookRegistry_CBasePlayer_Observer_IsValidTarget *CBasePlayer_Observer_IsValidTarget() = 0;
	virtual IReGameHookRegistry_CBasePlayer_SetAnimation *CBasePlayer_SetAnimation() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveDefaultItems *CBasePlayer_GiveDefaultItems() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveNamedItem *CBasePlayer_GiveNamedItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddAccount *CBasePlayer_AddAccount() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveShield *CBasePlayer_GiveShield() = 0;
	virtual IReGameHookRegistry_CBasePlayer_SetClientUserInfoModel *CBasePlayer_SetClientUserInfoModel() = 0;
	virtual IReGameHookRegistry_CBasePlayer_SetClientUserInfoName *CBasePlayer_SetClientUserInfoName() = 0;
	virtual IReGameHookRegistry_CBasePlayer_HasRestrictItem *CBasePlayer_HasRestrictItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_DropPlayerItem *CBasePlayer_DropPlayerItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_DropShield *CBasePlayer_DropShield() = 0;
	virtual IReGameHookRegistry_CBasePlayer_OnSpawnEquip *CBasePlayer_OnSpawnEquip() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Radio *CBasePlayer_Radio() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Disappear *CBasePlayer_Disappear() = 0;
	virtual IReGameHookRegistry_CBasePlayer_MakeVIP *CBasePlayer_MakeVIP() = 0;
	virtual IReGameHookRegistry_CBasePlayer_MakeBomber *CBasePlayer_MakeBomber() = 0;
	virtual IReGameHookRegistry_CBasePlayer_StartObserver *CBasePlayer_StartObserver() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GetIntoGame *CBasePlayer_GetIntoGame() = 0;

	virtual IReGameHookRegistry_CBaseAnimating_ResetSequenceInfo *CBaseAnimating_ResetSequenceInfo() = 0;

	virtual IReGameHookRegistry_GetForceCamera *GetForceCamera() = 0;
	virtual IReGameHookRegistry_PlayerBlind *PlayerBlind() = 0;
	virtual IReGameHookRegistry_RadiusFlash_TraceLine *RadiusFlash_TraceLine() = 0;
	virtual IReGameHookRegistry_RoundEnd *RoundEnd() = 0;
	virtual IReGameHookRegistry_InstallGameRules *InstallGameRules() = 0;
	virtual IReGameHookRegistry_PM_Init *PM_Init() = 0;
	virtual IReGameHookRegistry_PM_Move *PM_Move() = 0;
	virtual IReGameHookRegistry_PM_AirMove *PM_AirMove() = 0;
	virtual IReGameHookRegistry_HandleMenu_ChooseAppearance *HandleMenu_ChooseAppearance() = 0;
	virtual IReGameHookRegistry_HandleMenu_ChooseTeam *HandleMenu_ChooseTeam() = 0;
	virtual IReGameHookRegistry_ShowMenu *ShowMenu() = 0;
	virtual IReGameHookRegistry_ShowVGUIMenu *ShowVGUIMenu() = 0;
	virtual IReGameHookRegistry_BuyGunAmmo *BuyGunAmmo() = 0;
	virtual IReGameHookRegistry_BuyWeaponByWeaponID *BuyWeaponByWeaponID() = 0;
	virtual IReGameHookRegistry_InternalCommand *InternalCommand() = 0;

	virtual IReGameHookRegistry_CSGameRules_FShouldSwitchWeapon *CSGameRules_FShouldSwitchWeapon() = 0;
	virtual IReGameHookRegistry_CSGameRules_GetNextBestWeapon *CSGameRules_GetNextBestWeapon() = 0;
	virtual IReGameHookRegistry_CSGameRules_FlPlayerFallDamage *CSGameRules_FlPlayerFallDamage() = 0;
	virtual IReGameHookRegistry_CSGameRules_FPlayerCanTakeDamage *CSGameRules_FPlayerCanTakeDamage() = 0;
	virtual IReGameHookRegistry_CSGameRules_PlayerSpawn *CSGameRules_PlayerSpawn() = 0;
	virtual IReGameHookRegistry_CSGameRules_FPlayerCanRespawn *CSGameRules_FPlayerCanRespawn() = 0;
	virtual IReGameHookRegistry_CSGameRules_GetPlayerSpawnSpot *CSGameRules_GetPlayerSpawnSpot() = 0;
	virtual IReGameHookRegistry_CSGameRules_ClientUserInfoChanged *CSGameRules_ClientUserInfoChanged() = 0;
	virtual IReGameHookRegistry_CSGameRules_PlayerKilled *CSGameRules_PlayerKilled() = 0;
	virtual IReGameHookRegistry_CSGameRules_DeathNotice *CSGameRules_DeathNotice() = 0;
	virtual IReGameHookRegistry_CSGameRules_CanHavePlayerItem *CSGameRules_CanHavePlayerItem() = 0;
	virtual IReGameHookRegistry_CSGameRules_DeadPlayerWeapons *CSGameRules_DeadPlayerWeapons() = 0;
	virtual IReGameHookRegistry_CSGameRules_ServerDeactivate *CSGameRules_ServerDeactivate() = 0;
	virtual IReGameHookRegistry_CSGameRules_CheckMapConditions *CSGameRules_CheckMapConditions() = 0;
	virtual IReGameHookRegistry_CSGameRules_CleanUpMap *CSGameRules_CleanUpMap() = 0;
	virtual IReGameHookRegistry_CSGameRules_RestartRound *CSGameRules_RestartRound() = 0;
	virtual IReGameHookRegistry_CSGameRules_CheckWinConditions *CSGameRules_CheckWinConditions() = 0;
	virtual IReGameHookRegistry_CSGameRules_RemoveGuns *CSGameRules_RemoveGuns() = 0;
	virtual IReGameHookRegistry_CSGameRules_GiveC4 *CSGameRules_GiveC4() = 0;
	virtual IReGameHookRegistry_CSGameRules_ChangeLevel *CSGameRules_ChangeLevel() = 0;
	virtual IReGameHookRegistry_CSGameRules_GoToIntermission *CSGameRules_GoToIntermission() = 0;
	virtual IReGameHookRegistry_CSGameRules_BalanceTeams *CSGameRules_BalanceTeams() = 0;
	virtual IReGameHookRegistry_CSGameRules_OnRoundFreezeEnd *CSGameRules_OnRoundFreezeEnd() = 0;
	virtual IReGameHookRegistry_PM_UpdateStepSound *PM_UpdateStepSound() = 0;
	virtual IReGameHookRegistry_CBasePlayer_StartDeathCam *CBasePlayer_StartDeathCam() = 0;
	virtual IReGameHookRegistry_CBasePlayer_SwitchTeam *CBasePlayer_SwitchTeam() = 0;
	virtual IReGameHookRegistry_CBasePlayer_CanSwitchTeam *CBasePlayer_CanSwitchTeam() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ThrowGrenade *CBasePlayer_ThrowGrenade() = 0;
	virtual IReGameHookRegistry_CSGameRules_CanPlayerHearPlayer *CSGameRules_CanPlayerHearPlayer() = 0;
	virtual IReGameHookRegistry_CWeaponBox_SetModel *CWeaponBox_SetModel() = 0;
	virtual IReGameHookRegistry_CGrenade_DefuseBombStart *CGrenade_DefuseBombStart() = 0;
	virtual IReGameHookRegistry_CGrenade_DefuseBombEnd *CGrenade_DefuseBombEnd() = 0;
	virtual IReGameHookRegistry_CGrenade_ExplodeHeGrenade *CGrenade_ExplodeHeGrenade() = 0;
	virtual IReGameHookRegistry_CGrenade_ExplodeFlashbang *CGrenade_ExplodeFlashbang() = 0;
	virtual IReGameHookRegistry_CGrenade_ExplodeSmokeGrenade *CGrenade_ExplodeSmokeGrenade() = 0;
	virtual IReGameHookRegistry_CGrenade_ExplodeBomb *CGrenade_ExplodeBomb() = 0;
	virtual IReGameHookRegistry_ThrowHeGrenade *ThrowHeGrenade() = 0;
	virtual IReGameHookRegistry_ThrowFlashbang *ThrowFlashbang() = 0;
	virtual IReGameHookRegistry_ThrowSmokeGrenade *ThrowSmokeGrenade() = 0;
	virtual IReGameHookRegistry_PlantBomb *PlantBomb() = 0;
};

struct ReGameFuncs_t {
	struct edict_s *(*CREATE_NAMED_ENTITY2)(string_t iClass);
	void (*ChangeString)(char *&dest, const char *source);
	void (*RadiusDamage)(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType);
	void (*ClearMultiDamage)();
	void (*ApplyMultiDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker);
	void (*AddMultiDamage)(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);
	class CBaseEntity *(*UTIL_FindEntityByString)(class CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue);
	void (*AddEntityHashValue)(entvars_t *pev, const char *value, hash_types_e fieldType);
	void (*RemoveEntityHashValue)(entvars_t *pev, const char *value, hash_types_e fieldType);
	int (*Cmd_Argc)();
	const char *(*Cmd_Argv)(int i);
};

class IReGameApi {
public:
	virtual ~IReGameApi() {}

	virtual int GetMajorVersion() = 0;
	virtual int GetMinorVersion() = 0;
	virtual const ReGameFuncs_t *GetFuncs() = 0;
	virtual IReGameHookchains *GetHookchains() = 0;

	virtual class CGameRules *GetGameRules() = 0;
	virtual struct WeaponInfoStruct *GetWeaponInfo(int weaponID) = 0;
	virtual struct WeaponInfoStruct *GetWeaponInfo(const char *weaponName) = 0;
	virtual struct playermove_s *GetPlayerMove() = 0;
	virtual struct WeaponSlotInfo *GetWeaponSlot(WeaponIdType weaponID) = 0;
	virtual struct WeaponSlotInfo *GetWeaponSlot(const char *weaponName) = 0;
	virtual struct ItemInfo *GetItemInfo(WeaponIdType weaponID) = 0;
	virtual struct AmmoInfo *GetAmmoInfo(AmmoType ammoID) = 0;
	virtual struct AmmoInfoStruct *GetAmmoInfoEx(AmmoType ammoID) = 0;
	virtual struct AmmoInfoStruct *GetAmmoInfoEx(const char *ammoName) = 0;
};

#define VRE_GAMEDLL_API_VERSION "VRE_GAMEDLL_API_VERSION001"
