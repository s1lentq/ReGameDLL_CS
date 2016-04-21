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
#include "regamedll_interfaces.h"
#include "hookchains.h"
#include "interface.h"

#define REGAMEDLL_API_VERSION_MAJOR 1
#define REGAMEDLL_API_VERSION_MINOR 0

// CBasePlayer::Spawn hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_Spawn;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_Spawn;

// CBasePlayer::Precache hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_Precache;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_Precache;

// CBasePlayer::ObjectCaps hook
typedef IHookChain<int> IReGameHook_CBasePlayer_ObjectCaps;
typedef IHookChainRegistryClass<int, class CBasePlayer> IReGameHookRegistry_CBasePlayer_ObjectCaps;

// CBasePlayer::Classify hook
typedef IHookChain<int> IReGameHook_CBasePlayer_Classify;
typedef IHookChainRegistryClass<int, class CBasePlayer> IReGameHookRegistry_CBasePlayer_Classify;

// CBasePlayer::TraceAttack hook
typedef IVoidHookChain<struct entvars_s *, float, Vector &, struct TraceResult *, int> IReGameHook_CBasePlayer_TraceAttack;
typedef IVoidHookChainRegistryClass<class CBasePlayer, struct entvars_s *, float, Vector &, struct TraceResult *, int> IReGameHookRegistry_CBasePlayer_TraceAttack;

// CBasePlayer::TakeDamage hook
typedef IHookChain<int, struct entvars_s *, struct entvars_s *, float, int> IReGameHook_CBasePlayer_TakeDamage;
typedef IHookChainRegistryClass<int, class CBasePlayer, struct entvars_s *, struct entvars_s *, float, int> IReGameHookRegistry_CBasePlayer_TakeDamage;

// CBasePlayer::TakeHealth hook
typedef IHookChain<int, float, int> IReGameHook_CBasePlayer_TakeHealth;
typedef IHookChainRegistryClass<int, class CBasePlayer, float, int> IReGameHookRegistry_CBasePlayer_TakeHealth;

// CBasePlayer::Killed hook
typedef IVoidHookChain<struct entvars_s *, int> IReGameHook_CBasePlayer_Killed;
typedef IVoidHookChainRegistryClass<class CBasePlayer, struct entvars_s *, int> IReGameHookRegistry_CBasePlayer_Killed;

// CBasePlayer::AddPoints hook
typedef IVoidHookChain<int, BOOL> IReGameHook_CBasePlayer_AddPoints;
typedef IVoidHookChainRegistryClass<class CBasePlayer, int, BOOL> IReGameHookRegistry_CBasePlayer_AddPoints;

// CBasePlayer::AddPointsToTeam hook
typedef IVoidHookChain<int, BOOL> IReGameHook_CBasePlayer_AddPointsToTeam;
typedef IVoidHookChainRegistryClass<class CBasePlayer, int, BOOL> IReGameHookRegistry_CBasePlayer_AddPointsToTeam;

// CBasePlayer::AddPlayerItem hook
typedef IHookChain<BOOL, class CBasePlayerItem *> IReGameHook_CBasePlayer_AddPlayerItem;
typedef IHookChainRegistryClass<BOOL, class CBasePlayer, class CBasePlayerItem *> IReGameHookRegistry_CBasePlayer_AddPlayerItem;

// CBasePlayer::RemovePlayerItem hook
typedef IHookChain<BOOL, class CBasePlayerItem *> IReGameHook_CBasePlayer_RemovePlayerItem;
typedef IHookChainRegistryClass<BOOL, class CBasePlayer, class CBasePlayerItem *> IReGameHookRegistry_CBasePlayer_RemovePlayerItem;

// CBasePlayer::GiveAmmo hook
typedef IHookChain<int, int , char *, int> IReGameHook_CBasePlayer_GiveAmmo;
typedef IHookChainRegistryClass<int, class CBasePlayer, int , char *, int> IReGameHookRegistry_CBasePlayer_GiveAmmo;

// CBasePlayer::ResetMaxSpeed hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_ResetMaxSpeed;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_ResetMaxSpeed;

// CBasePlayer::Jump hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_Jump;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_Jump;

// CBasePlayer::Duck hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_Duck;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_Duck;

// CBasePlayer::PreThink hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_PreThink;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_PreThink;

// CBasePlayer::PostThink hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_PostThink;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_PostThink;

// CBasePlayer::UpdateClientData hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_UpdateClientData;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_UpdateClientData;

// CBasePlayer::ImpulseCommands hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_ImpulseCommands;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_ImpulseCommands;

// CBasePlayer::RoundRespawn hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_RoundRespawn;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_RoundRespawn;

// CBasePlayer::Blind hook
typedef IVoidHookChain<float, float, float, int> IReGameHook_CBasePlayer_Blind;
typedef IVoidHookChainRegistryClass<class CBasePlayer, float, float, float, int> IReGameHookRegistry_CBasePlayer_Blind;


// CBasePlayer::Observer_IsValidTarget hook
typedef IHookChain<class CBaseEntity *, int, bool> IReGameHook_CBasePlayer_Observer_IsValidTarget;
typedef IHookChainRegistryClass<class CBaseEntity *, class CBasePlayer, int, bool> IReGameHookRegistry_CBasePlayer_Observer_IsValidTarget;

// CBasePlayer::SetAnimation hook
typedef IVoidHookChain<PLAYER_ANIM> IReGameHook_CBasePlayer_SetAnimation;
typedef IVoidHookChainRegistryClass<class CBasePlayer, PLAYER_ANIM> IReGameHookRegistry_CBasePlayer_SetAnimation;

// CBasePlayer::GiveDefaultItems hook
typedef IVoidHookChain<> IReGameHook_CBasePlayer_GiveDefaultItems;
typedef IVoidHookChainRegistryClass<class CBasePlayer> IReGameHookRegistry_CBasePlayer_GiveDefaultItems;

// CBasePlayer::GiveNamedItem hook
typedef IVoidHookChain<const char *> IReGameHook_CBasePlayer_GiveNamedItem;
typedef IVoidHookChainRegistryClass<class CBasePlayer, const char *> IReGameHookRegistry_CBasePlayer_GiveNamedItem;

// CBasePlayer::AddAccount hook
typedef IVoidHookChain<int, bool> IReGameHook_CBasePlayer_AddAccount;
typedef IVoidHookChainRegistryClass<class CBasePlayer, int, bool> IReGameHookRegistry_CBasePlayer_AddAccount;

// CBasePlayer::GiveShield hook
typedef IVoidHookChain<bool> IReGameHook_CBasePlayer_GiveShield;
typedef IVoidHookChainRegistryClass<class CBasePlayer, bool> IReGameHookRegistry_CBasePlayer_GiveShield;




// CBaseAnimating::ResetSequenceInfo hook
typedef IVoidHookChain<> IReGameHook_CBaseAnimating_ResetSequenceInfo;
typedef IVoidHookChainRegistryClass<class CBaseAnimating> IReGameHookRegistry_CBaseAnimating_ResetSequenceInfo;





// GetForceCamera hook
typedef IHookChain<int, class CBasePlayer *> IReGameHook_GetForceCamera;
typedef IHookChainRegistry<int, class CBasePlayer *> IReGameHookRegistry_GetForceCamera;

// PlayerBlind hook
typedef IVoidHookChain<class CBasePlayer *, struct entvars_s *, struct entvars_s *, float, float, int, Vector &> IReGameHook_PlayerBlind;
typedef IVoidHookChainRegistry<class CBasePlayer *, struct entvars_s *, struct entvars_s *, float, float, int, Vector &> IReGameHookRegistry_PlayerBlind;

// RadiusFlash_TraceLine hook
typedef IVoidHookChain<class CBasePlayer *, struct entvars_s *, struct entvars_s *, Vector &, Vector &, struct TraceResult *> IReGameHook_RadiusFlash_TraceLine;
typedef IVoidHookChainRegistry<class CBasePlayer *, struct entvars_s *, struct entvars_s *, Vector &, Vector &, struct TraceResult *> IReGameHookRegistry_RadiusFlash_TraceLine;

class IReGameHookchains {
public:
	virtual ~IReGameHookchains() {}
	// CBasePlayer virtual
	virtual IReGameHookRegistry_CBasePlayer_Spawn* CBasePlayer_Spawn() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Precache* CBasePlayer_Precache() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ObjectCaps* CBasePlayer_ObjectCaps() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Classify* CBasePlayer_Classify() = 0;
	virtual IReGameHookRegistry_CBasePlayer_TraceAttack* CBasePlayer_TraceAttack() = 0;
	virtual IReGameHookRegistry_CBasePlayer_TakeDamage* CBasePlayer_TakeDamage() = 0;
	virtual IReGameHookRegistry_CBasePlayer_TakeHealth* CBasePlayer_TakeHealth() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Killed* CBasePlayer_Killed() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddPoints* CBasePlayer_AddPoints() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddPointsToTeam* CBasePlayer_AddPointsToTeam() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddPlayerItem* CBasePlayer_AddPlayerItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_RemovePlayerItem* CBasePlayer_RemovePlayerItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveAmmo* CBasePlayer_GiveAmmo() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ResetMaxSpeed* CBasePlayer_ResetMaxSpeed() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Jump* CBasePlayer_Jump() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Duck* CBasePlayer_Duck() = 0;
	virtual IReGameHookRegistry_CBasePlayer_PreThink* CBasePlayer_PreThink() = 0;
	virtual IReGameHookRegistry_CBasePlayer_PostThink* CBasePlayer_PostThink() = 0;
	virtual IReGameHookRegistry_CBasePlayer_UpdateClientData* CBasePlayer_UpdateClientData() = 0;
	virtual IReGameHookRegistry_CBasePlayer_ImpulseCommands* CBasePlayer_ImpulseCommands() = 0;
	virtual IReGameHookRegistry_CBasePlayer_RoundRespawn* CBasePlayer_RoundRespawn() = 0;
	virtual IReGameHookRegistry_CBasePlayer_Blind* CBasePlayer_Blind() = 0;

	virtual IReGameHookRegistry_CBasePlayer_Observer_IsValidTarget* CBasePlayer_Observer_IsValidTarget() = 0;
	virtual IReGameHookRegistry_CBasePlayer_SetAnimation* CBasePlayer_SetAnimation() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveDefaultItems* CBasePlayer_GiveDefaultItems() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveNamedItem* CBasePlayer_GiveNamedItem() = 0;
	virtual IReGameHookRegistry_CBasePlayer_AddAccount* CBasePlayer_AddAccount() = 0;
	virtual IReGameHookRegistry_CBasePlayer_GiveShield* CBasePlayer_GiveShield() = 0;
	
	
	virtual IReGameHookRegistry_CBaseAnimating_ResetSequenceInfo* CBaseAnimating_ResetSequenceInfo() = 0;


	virtual IReGameHookRegistry_GetForceCamera* GetForceCamera() = 0;
	virtual IReGameHookRegistry_PlayerBlind* PlayerBlind() = 0;
	virtual IReGameHookRegistry_RadiusFlash_TraceLine* RadiusFlash_TraceLine() = 0;

};

struct ReGameFuncs_t {
	class CBaseEntity *(*UTIL_PlayerByIndex)(int playerIndex);
	class ICSPlayer *(*CBASE_TO_CSPLAYER)(class CBaseEntity *pEntity);
	class ICSEntity *(*CBASE_TO_CSENTITY)(class CBaseEntity *pEntity);
	class ICSPlayer *(*INDEX_TO_CSPLAYER)(int iPlayerIndex);
	class ICSEntity *(*INDEX_TO_CSENTITY)(int iEntityIndex);
	struct edict_s *(*CREATE_NAMED_ENTITY2)(string_t iClass);

	void (*ChangeString)(char *&dest, const char *source);

	void (*RadiusDamage)(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType);
	void (*ClearMultiDamage)();
	void (*ApplyMultiDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker);
	void (*AddMultiDamage)(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);

};

class IReGameApi {
public:
	virtual ~IReGameApi() {	}

	virtual int GetMajorVersion() = 0;
	virtual int GetMinorVersion() = 0;
	virtual const ReGameFuncs_t* GetFuncs() = 0;
	virtual IReGameHookchains* GetHookchains() = 0;
	virtual IReGameData* GetGameData() = 0;

};

#define VRE_GAMEDLL_API_VERSION "VRE_GAMEDLL_API_VERSION001"
