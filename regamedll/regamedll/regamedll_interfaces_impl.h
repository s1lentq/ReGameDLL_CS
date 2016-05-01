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

#include "maintypes.h"
#include "regamedll_interfaces.h"

class CCSEntity;
class CCSPlayer;
class CCSMonster;
class CBaseEntity;
class CCSquadMonster;

extern CCSEntity **g_GameEntities;
extern ICSEntity *CBASE_TO_CSENTITY(CBaseEntity *pEntity);
extern ICSPlayer *CBASE_TO_CSPLAYER(CBaseEntity *pEntity);
extern ICSPlayer *INDEX_TO_CSPLAYER(int iPlayerIndex);
extern ICSEntity *INDEX_TO_CSENTITY(int iEntityIndex);

#define __API_VHOOK(fname)\
	fname##_

#ifndef HOOK_GAMEDLL

#define __API_HOOK __API_VHOOK
#define __MAKE_VHOOK(fname)\
	fname

#define LINK_HOOK_CLASS_VOID_CHAIN(className, functionName, args, ...)\
	void className::functionName args {\
		g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this, __VA_ARGS__);\
	}
#define LINK_HOOK_CLASS_VOID_CHAIN2(className, functionName)\
	void className::functionName() {\
		g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this);\
	}

#define LINK_HOOK_CLASS_CHAIN(ret, className, functionName, args, ...)\
	ret className::functionName args {\
		return g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this, __VA_ARGS__);\
	}
#define LINK_HOOK_CLASS_CHAIN2(ret, className, functionName)\
	ret className::functionName() {\
		return g_ReGameHookchains.m_##className##_##functionName.callChain(&className::functionName##_, this);\
	}

#define LINK_HOOK_VOID_CHAIN(functionName, args, ...)\
	void functionName args {\
		g_ReGameHookchains.m_##functionName.callChain(functionName##_, __VA_ARGS__);\
	}

#define LINK_HOOK_CHAIN(ret, functionName, args, ...)\
	ret functionName args {\
		return g_ReGameHookchains.m_##functionName.callChain(functionName##_, __VA_ARGS__);\
	}

#endif

// Implementation interfaces
class CCSEntity: public ICSEntity {
public:
	CBaseEntity *m_pEntity;
	CCSEntity(CBaseEntity *pEntity) : m_pEntity(pEntity) {}
public:
	virtual ~CCSEntity() {}
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Activate() { m_pEntity->Activate(); }
	virtual void SetObjectCollisionBox() { m_pEntity->SetObjectCollisionBox(); }
	virtual int Classify() { return m_pEntity->Classify(); }
	virtual void DeathNotice(entvars_t *pevChild) { m_pEntity->DeathNotice(pevChild); }
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector &vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int TakeHealth(float flHealth, int bitsDamageType) { return m_pEntity->TakeHealth(flHealth, bitsDamageType); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
	virtual void TraceBleed(float flDamage, Vector &vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceBleed(flDamage, vecDir, ptr, bitsDamageType); }
	virtual bool IsTriggered(CCSEntity *pActivator) { return m_pEntity->IsTriggered(pActivator->m_pEntity) ? true : false; }
	virtual ICSMonster *MyMonsterPointer() { return reinterpret_cast<ICSMonster *>(CBASE_TO_CSENTITY(m_pEntity->MyMonsterPointer())); }
	virtual ICSquadMonster *MySquadMonsterPointer() { return (ICSquadMonster *)m_pEntity->MySquadMonsterPointer(); }
	virtual int GetToggleState() { return m_pEntity->GetToggleState(); }
	virtual void AddPoints(int score, bool bAllowNegativeScore) { m_pEntity->AddPoints(score, bAllowNegativeScore ? TRUE : FALSE); }
	virtual void AddPointsToTeam(int score, bool bAllowNegativeScore) { m_pEntity->AddPointsToTeam(score, bAllowNegativeScore ? TRUE : FALSE); }
	virtual bool AddPlayerItem(CCSPlayerItem *pItem) { return m_pEntity->AddPlayerItem((CBasePlayerItem *)((CCSEntity *)pItem)->m_pEntity) ? true : false; }
	virtual bool RemovePlayerItem(CCSPlayerItem *pItem) { return m_pEntity->RemovePlayerItem((CBasePlayerItem *)((CCSEntity *)pItem)->m_pEntity) ? true : false; }
	virtual int GiveAmmo(int iAmount, char *szName, int iMax) { return m_pEntity->GiveAmmo(iAmount, szName, iMax); }
	virtual float GetDelay() { return m_pEntity->GetDelay(); }
	virtual int IsMoving() { return m_pEntity->IsMoving(); }
	virtual void OverrideReset() { m_pEntity->OverrideReset(); }
	virtual int DamageDecal(int bitsDamageType) { return m_pEntity->DamageDecal(bitsDamageType); }
	virtual void SetToggleState(int state) { m_pEntity->SetToggleState(state); }
	virtual void StartSneaking() { m_pEntity->StartSneaking(); }
	virtual void StopSneaking() { m_pEntity->StopSneaking(); }
	virtual bool OnControls(entvars_t *onpev) { return m_pEntity->OnControls(onpev) ? true : false; }
	virtual bool IsSneaking() { return m_pEntity->IsSneaking() ? true : false; }
	virtual bool IsAlive() { return m_pEntity->IsAlive() ? true : false; }
	virtual bool IsBSPModel() { return m_pEntity->IsBSPModel() ? true : false; }
	virtual bool ReflectGauss() { return m_pEntity->ReflectGauss() ? true : false; }
	virtual bool HasTarget(string_t targetname) { return m_pEntity->HasTarget(targetname) ? true : false; }
	virtual bool IsInWorld() { return m_pEntity->IsInWorld() ? true : false; }
	virtual bool IsPlayer() { return m_pEntity->IsPlayer() ? true : false; }
	virtual bool IsNetClient() { return m_pEntity->IsNetClient() ? true : false; }
	virtual const char *TeamID() { return m_pEntity->TeamID(); }
	virtual ICSEntity *GetNextTarget() { return CBASE_TO_CSENTITY(m_pEntity->GetNextTarget()); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
	virtual ICSEntity *Respawn() { return CBASE_TO_CSENTITY(m_pEntity->Respawn()); }
	virtual void UpdateOwner() { m_pEntity->UpdateOwner(); }
	virtual bool FBecomeProne() { return m_pEntity->FBecomeProne() ? true : false; }
	virtual Vector Center() { return m_pEntity->Center(); }
	virtual Vector EyePosition() { return m_pEntity->EyePosition(); }
	virtual Vector EarPosition() { return m_pEntity->EarPosition(); }
	virtual Vector BodyTarget(const Vector &posSrc) { return m_pEntity->BodyTarget(posSrc); }
	virtual int Illumination() { return m_pEntity->Illumination(); }
	virtual bool FVisible(CCSEntity *pEntity) { return m_pEntity->FVisible(pEntity->m_pEntity) ? true : false; }
	virtual bool FVisible(const Vector &vecOrigin) { return m_pEntity->FVisible(vecOrigin) ? true : false; }
public:
	virtual entvars_t *GetEntVars() const { return m_pEntity->pev; }
	virtual CBaseEntity *GetEntity() const { return m_pEntity; }
	virtual void FireBullets(int iShots, Vector &vecSrc, Vector &vecDirShooting, Vector &vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker) { m_pEntity->FireBullets(iShots, vecSrc, vecDirShooting, vecSpread, flDistance, iBulletType, iTracerFreq, iDamage, pevAttacker); };
	virtual Vector FireBullets3(Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand) { return m_pEntity->FireBullets3(vecSrc, vecDirShooting, vecSpread, flDistance, iPenetration, iBulletType, iDamage, flRangeModifier, pevAttacker, bPistol, shared_rand); };
};

class CCSDelay: public CCSEntity {
public:
	CCSDelay(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
};

class CCSAnimating: public CCSDelay {
public:
	CCSAnimating(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void HandleAnimEvent(MonsterEvent_t *pEvent) { return ((CBaseAnimating *)m_pEntity)->HandleAnimEvent(pEvent); }
};

class CCSPlayerItem: public CCSAnimating {
public:
	CCSPlayerItem(CBaseEntity *pEntity) : CCSAnimating(pEntity) {}
public:
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void SetObjectCollisionBox() { m_pEntity->SetObjectCollisionBox(); }
	virtual ICSEntity *Respawn() { return CBASE_TO_CSENTITY(m_pEntity->Respawn()); }
	virtual int AddToPlayer(CCSPlayer *pPlayer) { return ((CBasePlayerItem *)m_pEntity)->AddToPlayer((CBasePlayer *)((CCSEntity *)pPlayer)->m_pEntity); }
	virtual int AddDuplicate(CCSPlayerItem *pItem) { return ((CBasePlayerItem *)m_pEntity)->AddDuplicate((CBasePlayerItem *)pItem->m_pEntity); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool CanDeploy() { return ((CBasePlayerItem *)m_pEntity)->CanDeploy() ? true : false; }
	virtual bool CanDrop() { return ((CBasePlayerItem *)m_pEntity)->CanDrop() ? true : false; }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual bool IsWeapon() { return ((CBasePlayerItem *)m_pEntity)->IsWeapon() ? true : false; }
	virtual bool CanHolster() { return ((CBasePlayerItem *)m_pEntity)->CanHolster() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerItem *)m_pEntity)->Holster(skiplocal); }
	virtual void UpdateItemInfo() { ((CBasePlayerItem *)m_pEntity)->UpdateItemInfo(); }
	virtual void ItemPreFrame() { ((CBasePlayerItem *)m_pEntity)->ItemPreFrame(); }
	virtual void ItemPostFrame() { ((CBasePlayerItem *)m_pEntity)->ItemPostFrame(); }
	virtual void Drop() { ((CBasePlayerItem *)m_pEntity)->Drop(); }
	virtual void Kill() { ((CBasePlayerItem *)m_pEntity)->Kill(); }
	virtual void AttachToPlayer(CCSPlayer *pPlayer) { ((CBasePlayerItem *)m_pEntity)->AttachToPlayer((CBasePlayer *)((CCSEntity *)pPlayer)->m_pEntity); }
	virtual int PrimaryAmmoIndex() { ((CBasePlayerItem *)m_pEntity)->PrimaryAmmoIndex(); }
	virtual int SecondaryAmmoIndex() { ((CBasePlayerItem *)m_pEntity)->SecondaryAmmoIndex(); }
	virtual int UpdateClientData(CCSPlayer *pPlayer) { ((CBasePlayerItem *)m_pEntity)->UpdateClientData((CBasePlayer *)((CCSEntity *)pPlayer)->m_pEntity); }
	virtual ICSPlayerItem *GetWeaponPtr() { ((CBasePlayerItem *)m_pEntity)->GetWeaponPtr(); }
	virtual float GetMaxSpeed() { ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
};

class CCSToggle: public CCSAnimating {
public:
	CCSToggle(CBaseEntity *pEntity) : CCSAnimating(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int GetToggleState() { return m_pEntity->GetToggleState(); }
	virtual float GetDelay() { return m_pEntity->GetDelay(); }
};

class CCSMonster: public CCSToggle {
public:
	CCSMonster(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector &vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int TakeHealth(float flHealth, int bitsDamageType) { return m_pEntity->TakeHealth(flHealth, bitsDamageType); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
	virtual bool IsAlive() { return m_pEntity->IsAlive() ? true : false; }
	virtual float ChangeYaw(int speed) { return ((CBaseMonster *)m_pEntity)->ChangeYaw(speed); }
	virtual bool HasHumanGibs() { return ((CBaseMonster *)m_pEntity)->HasHumanGibs() ? true : false; }
	virtual bool HasAlienGibs() { return ((CBaseMonster *)m_pEntity)->HasAlienGibs() ? true : false; }
	virtual void FadeMonster() { ((CBaseMonster *)m_pEntity)->FadeMonster(); }
	virtual void GibMonster() { ((CBaseMonster *)m_pEntity)->GibMonster(); }
	virtual Activity GetDeathActivity() { return ((CBaseMonster *)m_pEntity)->GetDeathActivity(); }
	virtual void BecomeDead() { ((CBaseMonster *)m_pEntity)->BecomeDead(); }
	virtual bool ShouldFadeOnDeath() { return ((CBaseMonster *)m_pEntity)->ShouldFadeOnDeath() ? true : false; }
	virtual int IRelationship(CCSEntity *pTarget) { return ((CBaseMonster *)m_pEntity)->IRelationship(pTarget->m_pEntity); }
	virtual void PainSound() { ((CBaseMonster *)m_pEntity)->PainSound(); }
	virtual void ResetMaxSpeed() { ((CBaseMonster *)m_pEntity)->ResetMaxSpeed(); }
	virtual void ReportAIState() { ((CBaseMonster *)m_pEntity)->ReportAIState(); }
	virtual void MonsterInitDead() { ((CBaseMonster *)m_pEntity)->MonsterInitDead(); }
	virtual void Look(int iDistance) { ((CBaseMonster *)m_pEntity)->Look(iDistance); }
	virtual ICSEntity *BestVisibleEnemy() { return CBASE_TO_CSENTITY(((CBaseMonster *)m_pEntity)->BestVisibleEnemy()); }
	virtual bool FInViewCone(CCSEntity *pEntity) { return ((CBaseMonster *)m_pEntity)->FInViewCone(pEntity->m_pEntity) ? true : false; }
	virtual bool FInViewCone(const Vector *pOrigin) { return ((CBaseMonster *)m_pEntity)->FInViewCone(pOrigin) ? true : false; }
};

class CCSWeaponBox: public CCSEntity {
public:
	CCSWeaponBox(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void SetObjectCollisionBox() { m_pEntity->SetObjectCollisionBox(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSArmoury: public CCSEntity {
public:
	CCSArmoury(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSPlayer: public CCSMonster {
public:
	CCSPlayer(CBaseEntity *pEntity) : CCSMonster(pEntity) {}

	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int Classify() { return m_pEntity->Classify(); }
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector &vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int TakeHealth(float flHealth, int bitsDamageType) { return m_pEntity->TakeHealth(flHealth, bitsDamageType); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual void AddPoints(int score, bool bAllowNegativeScore) { m_pEntity->AddPoints(score, bAllowNegativeScore ? TRUE : FALSE); }
	virtual void AddPointsToTeam(int score, bool bAllowNegativeScore) { m_pEntity->AddPointsToTeam(score, bAllowNegativeScore ? TRUE : FALSE); }
	virtual bool AddPlayerItem(CCSPlayerItem *pItem) { return m_pEntity->AddPlayerItem((CBasePlayerItem *)pItem->m_pEntity) ? true : false; }
	virtual bool RemovePlayerItem(CCSPlayerItem *pItem) { return m_pEntity->RemovePlayerItem((CBasePlayerItem *)pItem->m_pEntity) ? true : false; }
	virtual int GiveAmmo(int iAmount, char *szName, int iMax) { return m_pEntity->GiveAmmo(iAmount, szName, iMax); }
	virtual void StartSneaking() { m_pEntity->StartSneaking(); }
	virtual void StopSneaking() { m_pEntity->StopSneaking(); }
	virtual bool IsSneaking() { return m_pEntity->IsSneaking() ? true : false; }
	virtual bool IsAlive() { return m_pEntity->IsAlive() ? true : false; }
	virtual bool IsPlayer() { return m_pEntity->IsPlayer() ? true : false; }
	virtual bool IsNetClient() { return m_pEntity->IsNetClient() ? true : false; }
	virtual const char *TeamID() { return m_pEntity->TeamID(); }
	virtual bool FBecomeProne() { return m_pEntity->FBecomeProne() ? true : false; }
	virtual Vector BodyTarget(const Vector &posSrc) { return m_pEntity->BodyTarget(posSrc); }
	virtual int Illumination() { return m_pEntity->Illumination(); }
	virtual bool ShouldFadeOnDeath() { return ((CBasePlayer *)m_pEntity)->ShouldFadeOnDeath() ? true : false; }
	virtual void ResetMaxSpeed() { ((CBasePlayer *)m_pEntity)->ResetMaxSpeed(); }
	virtual void Jump() { ((CBasePlayer *)m_pEntity)->Jump(); }
	virtual void Duck() { ((CBasePlayer *)m_pEntity)->Duck(); }
	virtual void PreThink() { ((CBasePlayer *)m_pEntity)->PreThink(); }
	virtual void PostThink() { ((CBasePlayer *)m_pEntity)->PostThink(); }
	virtual Vector GetGunPosition() { ((CBasePlayer *)m_pEntity)->GetGunPosition(); }
	virtual bool IsBot() { return ((CBasePlayer *)m_pEntity)->IsBot() ? true : false; }
	virtual void UpdateClientData() { ((CBasePlayer *)m_pEntity)->UpdateClientData(); }
	virtual void ImpulseCommands() { ((CBasePlayer *)m_pEntity)->ImpulseCommands(); }
	virtual void RoundRespawn() { ((CBasePlayer *)m_pEntity)->RoundRespawn(); }
	virtual Vector GetAutoaimVector(float flDelta) { ((CBasePlayer *)m_pEntity)->GetAutoaimVector(flDelta); }
	virtual void Blind(float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha) { ((CBasePlayer *)m_pEntity)->Blind(flUntilTime, flHoldTime, flFadeTime, iAlpha); }
	virtual void OnTouchingWeapon(CCSWeaponBox *pWeapon) { ((CBasePlayer *)m_pEntity)->OnTouchingWeapon((CWeaponBox *)pWeapon->m_pEntity); }
public:
	virtual bool IsConnected() const { return m_pEntity->has_disconnected == false; }

	virtual void SetAnimation(PLAYER_ANIM playerAnim) { ((CBasePlayer *)m_pEntity)->SetAnimation(playerAnim); }
	virtual void AddAccount(int amount, bool bTrackChange = true) { ((CBasePlayer *)m_pEntity)->AddAccount(amount, bTrackChange); }
	virtual void GiveNamedItem(const char *pszName) { ((CBasePlayer *)m_pEntity)->GiveNamedItem(pszName); }
	virtual void GiveDefaultItems() { ((CBasePlayer *)m_pEntity)->GiveDefaultItems(); }
	virtual void GiveShield(bool bDeploy = true) { ((CBasePlayer *)m_pEntity)->GiveShield(bDeploy); }
	virtual void RemoveAllItems(bool bRemoveSuit) { ((CBasePlayer *)m_pEntity)->RemoveAllItems(bRemoveSuit ? TRUE : FALSE); }
};

class CAPI_Bot: public CCSPlayer {
public:
	CAPI_Bot(CBaseEntity *pEntity) : CCSPlayer(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual void Think() { m_pEntity->Think(); }
	virtual bool IsBot() { return ((CBot *)m_pEntity)->IsBot() ? true : false; }
	virtual Vector GetAutoaimVector(float flDelta) { return ((CBot *)m_pEntity)->GetAutoaimVector(flDelta); }
	virtual void OnTouchingWeapon(CCSWeaponBox *box) { ((CBot *)m_pEntity)->OnTouchingWeapon((CWeaponBox *)box->m_pEntity); }
	virtual bool Initialize(const BotProfile *profile) { ((CBot *)m_pEntity)->Initialize(profile); }
	virtual void SpawnBot() = 0;
	virtual void Upkeep() = 0;
	virtual void Update() = 0;
	virtual void Run() { ((CBot *)m_pEntity)->Run(); }
	virtual void Walk() { ((CBot *)m_pEntity)->Walk(); }
	virtual void Crouch() { ((CBot *)m_pEntity)->Crouch(); }
	virtual void StandUp() { ((CBot *)m_pEntity)->StandUp(); }
	virtual void MoveForward() { ((CBot *)m_pEntity)->MoveForward(); }
	virtual void MoveBackward() { ((CBot *)m_pEntity)->MoveBackward(); }
	virtual void StrafeLeft() { ((CBot *)m_pEntity)->StrafeLeft(); }
	virtual void StrafeRight() { ((CBot *)m_pEntity)->StrafeRight(); }
	virtual bool Jump(bool mustJump) { return ((CBot *)m_pEntity)->Jump(mustJump); }
	virtual void ClearMovement() { ((CBot *)m_pEntity)->ClearMovement(); }
	virtual void UseEnvironment() { ((CBot *)m_pEntity)->UseEnvironment(); }
	virtual void PrimaryAttack() { ((CBot *)m_pEntity)->PrimaryAttack(); }
	virtual void ClearPrimaryAttack() { ((CBot *)m_pEntity)->ClearPrimaryAttack(); }
	virtual void TogglePrimaryAttack() { ((CBot *)m_pEntity)->TogglePrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBot *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBot *)m_pEntity)->Reload(); }
	virtual void OnEvent(GameEventType event, CCSEntity *entity, CCSEntity *other) { ((CBot *)m_pEntity)->OnEvent(event, entity->m_pEntity, other->m_pEntity); }
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;
	virtual bool IsVisible(CCSPlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const = 0;
	virtual bool IsEnemyPartVisible(VisiblePartTypeBot part) const = 0;
	virtual bool IsPlayerFacingMe(CCSPlayer *other) const { return ((CBot *)m_pEntity)->IsPlayerFacingMe((CBasePlayer *)other->m_pEntity); }
	virtual bool IsPlayerLookingAtMe(CCSPlayer *other) const { return ((CBot *)m_pEntity)->IsPlayerLookingAtMe((CBasePlayer *)other->m_pEntity); }
	virtual void ExecuteCommand() { ((CBot *)m_pEntity)->ExecuteCommand(); }
	virtual void SetModel(const char *modelName) { ((CBot *)m_pEntity)->SetModel(modelName); }
};

class CAPI_CSBot: public CAPI_Bot {
public:
	CAPI_CSBot(CBaseEntity *pEntity) : CAPI_Bot(pEntity) {}
public:
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual void RoundRespawn() { ((CCSBot *)m_pEntity)->RoundRespawn(); }
	virtual void Blind(float duration, float holdTime, float fadeTime, int alpha) { ((CCSBot *)m_pEntity)->Blind(duration, holdTime, fadeTime, alpha); }
	virtual void OnTouchingWeapon(CCSWeaponBox *box) { ((CCSBot *)m_pEntity)->OnTouchingWeapon((CWeaponBox *)box->m_pEntity); }
	virtual bool Initialize(const BotProfile *profile) { return ((CCSBot *)m_pEntity)->Initialize(profile); }
	virtual void SpawnBot() { ((CCSBot *)m_pEntity)->SpawnBot(); }
	virtual void Upkeep() { ((CCSBot *)m_pEntity)->Upkeep(); }
	virtual void Update() { ((CCSBot *)m_pEntity)->Update(); }
	virtual void Walk() { ((CCSBot *)m_pEntity)->Walk(); }
	virtual bool Jump(bool mustJump) { return ((CCSBot *)m_pEntity)->Jump(); }
	virtual void OnEvent(GameEventType event, CCSEntity *entity, CCSEntity *other) { ((CCSBot *)m_pEntity)->OnEvent(event, entity->m_pEntity, other->m_pEntity); }
	virtual bool IsVisible(const Vector *pos, bool testFOV) const { return ((CCSBot *)m_pEntity)->IsVisible(pos, testFOV); }
	virtual bool IsVisible(CCSPlayer *player, bool testFOV, unsigned char *visParts) const { return ((CCSBot *)m_pEntity)->IsVisible((CBasePlayer *)player->m_pEntity, testFOV, visParts); }
	virtual bool IsEnemyPartVisible(VisiblePartTypeBot part) const { return ((CCSBot *)m_pEntity)->IsEnemyPartVisible((CBot::VisiblePartType)part); }
};

class CCSShield: public CCSEntity {
public:
	CCSShield(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSDeadHEV: public CCSMonster {
public:
	CCSDeadHEV(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Classify() { return m_pEntity->Classify(); }
};

class CCSSprayCan: public CCSEntity {
public:
	CCSSprayCan(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Think() { m_pEntity->Think(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSBloodSplat: public CCSEntity {
public:
	CCSBloodSplat(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
};

class CCSPlayerWeapon: public CCSPlayerItem {
public:
	CCSPlayerWeapon(CBaseEntity *pEntity) : CCSPlayerItem(pEntity) {}
public:
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int AddToPlayer(CCSPlayer *pPlayer) { return ((CBasePlayerWeapon *)m_pEntity)->AddToPlayer((CBasePlayer *)pPlayer->m_pEntity); }
	virtual int AddDuplicate(CCSPlayerItem *pItem) { return ((CBasePlayerWeapon *)m_pEntity)->AddDuplicate((CBasePlayerItem *)pItem->m_pEntity); }
	virtual bool CanDeploy() { return ((CBasePlayerWeapon *)m_pEntity)->CanDeploy() ? true : false; }
	virtual bool IsWeapon() { return ((CBasePlayerWeapon *)m_pEntity)->IsWeapon() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerWeapon *)m_pEntity)->Holster(skiplocal); }
	virtual void UpdateItemInfo() { ((CBasePlayerWeapon *)m_pEntity)->UpdateItemInfo(); }
	virtual void ItemPostFrame() { ((CBasePlayerWeapon *)m_pEntity)->ItemPostFrame(); }
	virtual int PrimaryAmmoIndex() { return ((CBasePlayerWeapon *)m_pEntity)->PrimaryAmmoIndex(); }
	virtual int SecondaryAmmoIndex() { return ((CBasePlayerWeapon *)m_pEntity)->SecondaryAmmoIndex(); }
	virtual int UpdateClientData(CCSPlayer *pPlayer) { return ((CBasePlayerWeapon *)m_pEntity)->UpdateClientData((CBasePlayer *)pPlayer->m_pEntity); }
	virtual ICSPlayerItem *GetWeaponPtr() { return reinterpret_cast<ICSPlayerItem *>(CBASE_TO_CSENTITY(((CBasePlayerWeapon *)m_pEntity)->GetWeaponPtr())); }
	virtual int ExtractAmmo(CCSPlayerWeapon *pWeapon) { return ((CBasePlayerWeapon *)m_pEntity)->ExtractAmmo((CBasePlayerWeapon *)pWeapon->m_pEntity); }
	virtual int ExtractClipAmmo(CCSPlayerWeapon *pWeapon) { return ((CBasePlayerWeapon *)m_pEntity)->ExtractClipAmmo((CBasePlayerWeapon *)pWeapon->m_pEntity); }
	virtual int AddWeapon() { return ((CBasePlayerWeapon *)m_pEntity)->AddWeapon(); }
	virtual bool PlayEmptySound() { return ((CBasePlayerWeapon *)m_pEntity)->PlayEmptySound() ? true : false; }
	virtual void ResetEmptySound() { ((CBasePlayerWeapon *)m_pEntity)->ResetEmptySound(); }
	virtual void SendWeaponAnim(int iAnim, int skiplocal) { ((CBasePlayerWeapon *)m_pEntity)->SendWeaponAnim(iAnim, skiplocal); }
	virtual bool IsUseable() { return ((CBasePlayerWeapon *)m_pEntity)->IsUseable() ? true : false; }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual void RetireWeapon() { ((CBasePlayerWeapon *)m_pEntity)->RetireWeapon(); }
	virtual bool ShouldWeaponIdle() { return ((CBasePlayerWeapon *)m_pEntity)->ShouldWeaponIdle() ? true : false; }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSWorld: public CCSEntity {
public:
	CCSWorld(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSDecal: public CCSEntity {
public:
	CCSDecal(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSCorpse: public CCSEntity {
public:
	CCSCorpse(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSGrenade: public CCSMonster {
public:
	CCSGrenade(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void BounceSound() { ((CGrenade *)m_pEntity)->BounceSound(); }
};

class CCSAirtank: public CCSGrenade {
public:
	CCSAirtank(CBaseEntity *pEntity) : CCSGrenade(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
};

class CCSPlayerAmmo: public CCSEntity {
public:
	CCSPlayerAmmo(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((CBasePlayerAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
	virtual ICSEntity *Respawn() { return CBASE_TO_CSENTITY(m_pEntity->Respawn()); }
};

class CCS9MMAmmo: public CCSPlayerAmmo {
public:
	CCS9MMAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C9MMAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCSBuckShotAmmo: public CCSPlayerAmmo {
public:
	CCSBuckShotAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((CBuckShotAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS556NatoAmmo: public CCSPlayerAmmo {
public:
	CCS556NatoAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C556NatoAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS556NatoBoxAmmo: public CCSPlayerAmmo {
public:
	CCS556NatoBoxAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C556NatoBoxAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS762NatoAmmo: public CCSPlayerAmmo {
public:
	CCS762NatoAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C762NatoAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS45ACPAmmo: public CCSPlayerAmmo {
public:
	CCS45ACPAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C45ACPAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS50AEAmmo: public CCSPlayerAmmo {
public:
	CCS50AEAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C50AEAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS338MagnumAmmo: public CCSPlayerAmmo {
public:
	CCS338MagnumAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C338MagnumAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS57MMAmmo: public CCSPlayerAmmo {
public:
	CCS57MMAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C57MMAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCS357SIGAmmo: public CCSPlayerAmmo {
public:
	CCS357SIGAmmo(CBaseEntity *pEntity) : CCSPlayerAmmo(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool AddAmmo(CCSEntity *pOther) { return ((C357SIGAmmo *)m_pEntity)->AddAmmo(pOther->m_pEntity) ? true : false; }
};

class CCSFuncWall: public CCSEntity {
public:
	CCSFuncWall(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncWallToggle: public CCSFuncWall {
public:
	CCSFuncWallToggle(CBaseEntity *pEntity) : CCSFuncWall(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncConveyor: public CCSFuncWall {
public:
	CCSFuncConveyor(CBaseEntity *pEntity) : CCSFuncWall(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncIllusionary: public CCSToggle {
public:
	CCSFuncIllusionary(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSFuncMonsterClip: public CCSFuncWall {
public:
	CCSFuncMonsterClip(CBaseEntity *pEntity) : CCSFuncWall(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncRotating: public CCSEntity {
public:
	CCSFuncRotating(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
};

class CCSPendulum: public CCSEntity {
public:
	CCSPendulum(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
};

class CCSPointEntity: public CCSEntity {
public:
	CCSPointEntity(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSStripWeapons: public CCSPointEntity {
public:
	CCSStripWeapons(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSInfoIntermission: public CCSPointEntity {
public:
	CCSInfoIntermission(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSRevertSaved: public CCSPointEntity {
public:
	CCSRevertSaved(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSEnvGlobal: public CCSPointEntity {
public:
	CCSEnvGlobal(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSMultiSource: public CCSPointEntity {
public:
	CCSMultiSource(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual bool IsTriggered(CCSEntity *pActivator) { return m_pEntity->IsTriggered(pActivator->m_pEntity) ? true : false; }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSButton: public CCSToggle {
public:
	CCSButton(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSRotButton: public CCSButton {
public:
	CCSRotButton(CBaseEntity *pEntity) : CCSButton(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSMomentaryRotButton: public CCSToggle {
public:
	CCSMomentaryRotButton(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSEnvSpark: public CCSEntity {
public:
	CCSEnvSpark(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
};

class CCSButtonTarget: public CCSEntity {
public:
	CCSButtonTarget(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSDoor: public CCSToggle {
public:
	CCSDoor(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { return m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void SetToggleState(int state) { m_pEntity->SetToggleState(state); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
};

class CCSRotDoor: public CCSDoor {
public:
	CCSRotDoor(CBaseEntity *pEntity) : CCSDoor(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void SetToggleState(int state) { m_pEntity->SetToggleState(state); }
};

class CCSMomentaryDoor: public CCSToggle {
public:
	CCSMomentaryDoor(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { return m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGib: public CCSEntity {
public:
	CCSGib(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSBubbling: public CCSEntity {
public:
	CCSBubbling(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSBeam: public CCSEntity {
public:
	CCSBeam(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual Vector Center() { return m_pEntity->Center(); }
};

class CCSLightning: public CCSBeam {
public:
	CCSLightning(CBaseEntity *pEntity) : CCSBeam(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Activate() { m_pEntity->Activate(); }
};

class CCSLaser: public CCSBeam {
public:
	CCSLaser(CBaseEntity *pEntity) : CCSBeam(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGlow: public CCSPointEntity {
public:
	CCSGlow(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSSprite: public CCSPointEntity {
public:
	CCSSprite(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSBombGlow: public CCSSprite {
public:
	CCSBombGlow(CBaseEntity *pEntity) : CCSSprite(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSGibShooter: public CCSDelay {
public:
	CCSGibShooter(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual ICSGib *CreateGib() { CBASE_TO_CSENTITY(((CGibShooter *)m_pEntity)->CreateGib()); }
};

class CCSEnvShooter: public CCSGibShooter {
public:
	CCSEnvShooter(CBaseEntity *pEntity) : CCSGibShooter(pEntity) {}
public:
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual ICSGib *CreateGib() { CBASE_TO_CSENTITY(((CEnvShooter *)m_pEntity)->CreateGib()); }
};

class CCSTestEffect: public CCSDelay {
public:
	CCSTestEffect(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSBlood: public CCSPointEntity {
public:
	CCSBlood(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSShake: public CCSPointEntity {
public:
	CCSShake(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFade: public CCSPointEntity {
public:
	CCSFade(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSMessage: public CCSPointEntity {
public:
	CCSMessage(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSEnvFunnel: public CCSDelay {
public:
	CCSEnvFunnel(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSEnvBeverage: public CCSDelay {
public:
	CCSEnvBeverage(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSItemSoda: public CCSEntity {
public:
	CCSItemSoda(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
};

class CCSShower: public CCSEntity {
public:
	CCSShower(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSEnvExplosion: public CCSMonster {
public:
	CCSEnvExplosion(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSBreakable: public CCSDelay {
public:
	CCSBreakable(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector &vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int DamageDecal(int bitsDamageType) { return m_pEntity->DamageDecal(bitsDamageType); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSPushable: public CCSBreakable {
public:
	CCSPushable(CBaseEntity *pEntity) : CCSBreakable(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncTank: public CCSEntity {
public:
	CCSFuncTank(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual bool OnControls(entvars_t *pevTest) { return m_pEntity->OnControls(pevTest) ? true : false; }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { ((CFuncTank *)m_pEntity)->Fire(barrelEnd, forward, pevAttacker); }
	virtual Vector UpdateTargetPosition(CCSEntity *pTarget) { return ((CFuncTank *)m_pEntity)->UpdateTargetPosition(pTarget->m_pEntity); }
};

class CCSFuncTankGun: public CCSFuncTank {
public:
	CCSFuncTankGun(CBaseEntity *pEntity) : CCSFuncTank(pEntity) {}
public:
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { ((CFuncTankGun *)m_pEntity)->Fire(barrelEnd, forward, pevAttacker); }
};

class CCSFuncTankLaser: public CCSFuncTank {
public:
	CCSFuncTankLaser(CBaseEntity *pEntity) : CCSFuncTank(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Activate() { m_pEntity->Activate(); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { ((CFuncTankLaser *)m_pEntity)->Fire(barrelEnd, forward, pevAttacker); }
};

class CCSFuncTankRocket: public CCSFuncTank {
public:
	CCSFuncTankRocket(CBaseEntity *pEntity) : CCSFuncTank(pEntity) {}
public:
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { ((CFuncTankRocket *)m_pEntity)->Fire(barrelEnd, forward, pevAttacker); }
};

class CCSFuncTankMortar: public CCSFuncTank {
public:
	CCSFuncTankMortar(CBaseEntity *pEntity) : CCSFuncTank(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { ((CFuncTankMortar *)m_pEntity)->Fire(barrelEnd, forward, pevAttacker); }
};

class CCSFuncTankControls: public CCSEntity {
public:
	CCSFuncTankControls(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSRecharge: public CCSToggle {
public:
	CCSRecharge(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSCycler: public CCSMonster {
public:
	CCSCycler(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual bool IsAlive() { return m_pEntity->IsAlive() ? true : false; }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGenericCycler: public CCSCycler {
public:
	CCSGenericCycler(CBaseEntity *pEntity) : CCSCycler(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSCyclerProbe: public CCSCycler {
public:
	CCSCyclerProbe(CBaseEntity *pEntity) : CCSCycler(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSCyclerSprite: public CCSEntity {
public:
	CCSCyclerSprite(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSWeaponCycler: public CCSPlayerWeapon {
public:
	CCSWeaponCycler(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CWeaponCycler *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CWeaponCycler *)m_pEntity)->Deploy() ? true : false; }
	virtual void Holster(int skiplocal) { ((CWeaponCycler *)m_pEntity)->Holster(skiplocal); }
	virtual int iItemSlot() { return ((CWeaponCycler *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CWeaponCycler *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CWeaponCycler *)m_pEntity)->SecondaryAttack(); }
};

class CCSWreckage: public CCSMonster {
public:
	CCSWreckage(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSWorldItem: public CCSEntity {
public:
	CCSWorldItem(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSItem: public CCSEntity {
public:
	CCSItem(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual ICSEntity *Respawn() { return CBASE_TO_CSENTITY(m_pEntity->Respawn()); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItem *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSHealthKit: public CCSItem {
public:
	CCSHealthKit(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CHealthKit *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSWallHealth: public CCSToggle {
public:
	CCSWallHealth(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};





class CCSItemSuit: public CCSItem {
public:
	CCSItemSuit(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemSuit *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};





class CCSItemBattery: public CCSItem {
public:
	CCSItemBattery(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemBattery *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSItemAntidote: public CCSItem {
public:
	CCSItemAntidote(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemAntidote *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSItemSecurity: public CCSItem {
public:
	CCSItemSecurity(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemSecurity *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSItemLongJump: public CCSItem {
public:
	CCSItemLongJump(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemLongJump *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSItemKevlar: public CCSItem {
public:
	CCSItemKevlar(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemKevlar *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSItemAssaultSuit: public CCSItem {
public:
	CCSItemAssaultSuit(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemAssaultSuit *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSItemThighPack: public CCSItem {
public:
	CCSItemThighPack(CBaseEntity *pEntity) : CCSItem(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual bool MyTouch(CCSPlayer *pPlayer) { return ((CItemThighPack *)m_pEntity)->MyTouch((CBasePlayer *)pPlayer->m_pEntity) ? true : false; }
};

class CCSGrenCatch: public CCSEntity {
public:
	CCSGrenCatch(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSFuncWeaponCheck: public CCSEntity {
public:
	CCSFuncWeaponCheck(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSHostage: public CCSMonster {
public:
	CCSHostage(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int Classify() { return m_pEntity->Classify(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSLight: public CCSPointEntity {
public:
	CCSLight(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSEnvLight: public CCSLight {
public:
	CCSEnvLight(CBaseEntity *pEntity) : CCSLight(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSRuleEntity: public CCSEntity {
public:
	CCSRuleEntity(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
};

class CCSRulePointEntity: public CCSRuleEntity {
public:
	CCSRulePointEntity(CBaseEntity *pEntity) : CCSRuleEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSRuleBrushEntity: public CCSRuleEntity {
public:
	CCSRuleBrushEntity(CBaseEntity *pEntity) : CCSRuleEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSGameScore: public CCSRulePointEntity {
public:
	CCSGameScore(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGameEnd: public CCSRulePointEntity {
public:
	CCSGameEnd(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGameText: public CCSRulePointEntity {
public:
	CCSGameText(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGameTeamMaster: public CCSRulePointEntity {
public:
	CCSGameTeamMaster(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int ObjectCaps() { m_pEntity->ObjectCaps(); }
	virtual bool IsTriggered(CCSEntity *pActivator) { return m_pEntity->IsTriggered(pActivator->m_pEntity) ? true : false; }
	virtual const char *TeamID() { return m_pEntity->TeamID(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGameTeamSet: public CCSRulePointEntity {
public:
	CCSGameTeamSet(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGamePlayerZone: public CCSRuleBrushEntity {
public:
	CCSGamePlayerZone(CBaseEntity *pEntity) : CCSRuleBrushEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGamePlayerHurt: public CCSRulePointEntity {
public:
	CCSGamePlayerHurt(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGameCounter: public CCSRulePointEntity {
public:
	CCSGameCounter(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGameCounterSet: public CCSRulePointEntity {
public:
	CCSGameCounterSet(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGamePlayerEquip: public CCSRulePointEntity {
public:
	CCSGamePlayerEquip(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSGamePlayerTeam: public CCSRulePointEntity {
public:
	CCSGamePlayerTeam(CBaseEntity *pEntity) : CCSRulePointEntity(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncMortarField: public CCSToggle {
public:
	CCSFuncMortarField(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSMortar: public CCSGrenade {
public:
	CCSMortar(CBaseEntity *pEntity) : CCSGrenade(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
};

class CCSMapInfo: public CCSPointEntity {
public:
	CCSMapInfo(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSPathCorner: public CCSPointEntity {
public:
	CCSPathCorner(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual float GetDelay() { return m_pEntity->GetDelay(); }
};

class CCSPathTrack: public CCSPointEntity {
public:
	CCSPathTrack(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Activate() { m_pEntity->Activate(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSFuncTrackTrain: public CCSEntity {
public:
	CCSFuncTrackTrain(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void OverrideReset() { m_pEntity->OverrideReset(); }
	virtual bool OnControls(entvars_t *pev) { return m_pEntity->OnControls(pev) ? true : false; }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
};

class CCSFuncVehicleControls: public CCSEntity {
public:
	CCSFuncVehicleControls(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSFuncVehicle: public CCSEntity {
public:
	CCSFuncVehicle(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int Classify() { return m_pEntity->Classify(); }
	virtual void OverrideReset() { m_pEntity->OverrideReset(); }
	virtual bool OnControls(entvars_t *pev) { return m_pEntity->OnControls(pev) ? true : false; }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
};

class CCSPlatTrain: public CCSToggle {
public:
	CCSPlatTrain(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual bool IsTogglePlat() { return ((CBasePlatTrain *)m_pEntity)->IsTogglePlat() ? true : false; }
};

class CCSFuncPlat: public CCSPlatTrain {
public:
	CCSFuncPlat(CBaseEntity *pEntity) : CCSPlatTrain(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
	virtual void GoUp() { ((CFuncPlat *)m_pEntity)->GoUp(); }
	virtual void GoDown() { ((CFuncPlat *)m_pEntity)->GoDown(); }
	virtual void HitTop() { ((CFuncPlat *)m_pEntity)->HitTop(); }
	virtual void HitBottom() { ((CFuncPlat *)m_pEntity)->HitBottom(); }
};

class CCSPlatTrigger: public CCSEntity {
public:
	CCSPlatTrigger(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSFuncPlatRot: public CCSFuncPlat {
public:
	CCSFuncPlatRot(CBaseEntity *pEntity) : CCSFuncPlat(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void GoUp() { ((CFuncPlatRot *)m_pEntity)->GoUp(); }
	virtual void GoDown() { ((CFuncPlatRot *)m_pEntity)->GoDown(); }
	virtual void HitTop() { ((CFuncPlatRot *)m_pEntity)->HitTop(); }
	virtual void HitBottom() { ((CFuncPlatRot *)m_pEntity)->HitBottom(); }
};

class CCSFuncTrain: public CCSPlatTrain {
public:
	CCSFuncTrain(CBaseEntity *pEntity) : CCSPlatTrain(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Activate() { m_pEntity->Activate(); }
	virtual void OverrideReset() { m_pEntity->OverrideReset(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void Blocked(CCSEntity *pOther) { m_pEntity->Blocked(pOther->m_pEntity); }
};

class CCSFuncTrainControls: public CCSEntity {
public:
	CCSFuncTrainControls(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSFuncTrackChange: public CCSFuncPlatRot {
public:
	CCSFuncTrackChange(CBaseEntity *pEntity) : CCSFuncPlatRot(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void OverrideReset() { m_pEntity->OverrideReset(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual bool IsTogglePlat() { return ((CFuncTrackChange *)m_pEntity)->IsTogglePlat() ? true : false; }
	virtual void GoUp() { ((CFuncTrackChange *)m_pEntity)->GoUp(); }
	virtual void GoDown() { ((CFuncTrackChange *)m_pEntity)->GoDown(); }
	virtual void HitTop() { ((CFuncTrackChange *)m_pEntity)->HitTop(); }
	virtual void HitBottom() { ((CFuncTrackChange *)m_pEntity)->HitBottom(); }
	virtual void UpdateAutoTargets(int toggleState) { ((CFuncTrackChange *)m_pEntity)->UpdateAutoTargets(toggleState); }
};

class CCSFuncTrackAuto: public CCSFuncTrackChange {
public:
	CCSFuncTrackAuto(CBaseEntity *pEntity) : CCSFuncTrackChange(pEntity) {}
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual void UpdateAutoTargets(int toggleState) { ((CFuncTrackAuto *)m_pEntity)->UpdateAutoTargets(toggleState); }
};

class CCSGunTarget: public CCSMonster {
public:
	CCSGunTarget(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Activate() { m_pEntity->Activate(); }
	virtual int Classify() { return m_pEntity->Classify(); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual Vector BodyTarget(const Vector &posSrc) { return m_pEntity->BodyTarget(posSrc); }
};

class CCSAmbientGeneric: public CCSEntity {
public:
	CCSAmbientGeneric(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSEnvSound: public CCSPointEntity {
public:
	CCSEnvSound(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSSpeaker: public CCSEntity {
public:
	CCSSpeaker(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSSoundEnt: public CCSEntity {
public:
	CCSSoundEnt(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSUSP: public CCSPlayerWeapon {
public:
	CCSUSP(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSMP5N: public CCSPlayerWeapon {
public:
	CCSMP5N(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSSG552: public CCSPlayerWeapon {
public:
	CCSSG552(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSAK47: public CCSPlayerWeapon {
public:
	CCSAK47(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSAUG: public CCSPlayerWeapon {
public:
	CCSAUG(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSAWP: public CCSPlayerWeapon {
public:
	CCSAWP(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSC4: public CCSPlayerWeapon {
public:
	CCSC4(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerItem *)m_pEntity)->Holster(skiplocal); }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSDEAGLE: public CCSPlayerWeapon {
public:
	CCSDEAGLE(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
	virtual bool IsPistol() { return ((CDEAGLE *)m_pEntity)->IsPistol() ? true : false; }
};

class CCSFlashbang: public CCSPlayerWeapon {
public:
	CCSFlashbang(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool CanDeploy() { return ((CBasePlayerItem *)m_pEntity)->CanDeploy() ? true : false; }
	virtual bool CanDrop() { return ((CBasePlayerItem *)m_pEntity)->CanDrop() ? true : false; }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerItem *)m_pEntity)->Holster(skiplocal); }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
	virtual bool IsPistol() { return ((CFlashbang *)m_pEntity)->IsPistol() ? true : false; }
};

class CCSG3SG1: public CCSPlayerWeapon {
public:
	CCSG3SG1(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSGLOCK18: public CCSPlayerWeapon {
public:
	CCSGLOCK18(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSHEGrenade: public CCSPlayerWeapon {
public:
	CCSHEGrenade(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool CanDeploy() { return ((CBasePlayerItem *)m_pEntity)->CanDeploy() ? true : false; }
	virtual bool CanDrop() { return ((CBasePlayerItem *)m_pEntity)->CanDrop() ? true : false; }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerItem *)m_pEntity)->Holster(skiplocal); }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSKnife: public CCSPlayerWeapon {
public:
	CCSKnife(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool CanDrop() { return ((CBasePlayerWeapon *)m_pEntity)->CanDrop() ? true : false; }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerItem *)m_pEntity)->Holster(skiplocal); }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSM249: public CCSPlayerWeapon {
public:
	CCSM249(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSM3: public CCSPlayerWeapon {
public:
	CCSM3(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSM4A1: public CCSPlayerWeapon {
public:
	CCSM4A1(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSMAC10: public CCSPlayerWeapon {
public:
	CCSMAC10(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSP228: public CCSPlayerWeapon {
public:
	CCSP228(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
	virtual bool IsPistol() { return ((CP228 *)m_pEntity)->IsPistol() ? true : false; }
};

class CCSP90: public CCSPlayerWeapon {
public:
	CCSP90(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSSCOUT: public CCSPlayerWeapon {
public:
	CCSSCOUT(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSSmokeGrenade: public CCSPlayerWeapon {
public:
	CCSSmokeGrenade(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool CanDeploy() { return ((CBasePlayerItem *)m_pEntity)->CanDeploy() ? true : false; }
	virtual bool CanDrop() { return ((CBasePlayerItem *)m_pEntity)->CanDrop() ? true : false; }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual void Holster(int skiplocal) { ((CBasePlayerItem *)m_pEntity)->Holster(skiplocal); }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSTMP: public CCSPlayerWeapon {
public:
	CCSTMP(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSXM1014: public CCSPlayerWeapon {
public:
	CCSXM1014(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSELITE: public CCSPlayerWeapon {
public:
	CCSELITE(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSFiveSeven: public CCSPlayerWeapon {
public:
	CCSFiveSeven(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSUMP45: public CCSPlayerWeapon {
public:
	CCSUMP45(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSSG550: public CCSPlayerWeapon {
public:
	CCSSG550(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSGalil: public CCSPlayerWeapon {
public:
	CCSGalil(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSFamas: public CCSPlayerWeapon {
public:
	CCSFamas(CBaseEntity *pEntity) : CCSPlayerWeapon(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int GetItemInfo(ItemInfo *p) { return ((CBasePlayerItem *)m_pEntity)->GetItemInfo(p); }
	virtual bool Deploy() { return ((CBasePlayerItem *)m_pEntity)->Deploy() ? true : false; }
	virtual float GetMaxSpeed() { return ((CBasePlayerItem *)m_pEntity)->GetMaxSpeed(); }
	virtual int iItemSlot() { return ((CBasePlayerItem *)m_pEntity)->iItemSlot(); }
	virtual void PrimaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->PrimaryAttack(); }
	virtual void SecondaryAttack() { ((CBasePlayerWeapon *)m_pEntity)->SecondaryAttack(); }
	virtual void Reload() { ((CBasePlayerWeapon *)m_pEntity)->Reload(); }
	virtual void WeaponIdle() { ((CBasePlayerWeapon *)m_pEntity)->WeaponIdle(); }
	virtual bool UseDecrement() { return ((CBasePlayerWeapon *)m_pEntity)->UseDecrement() ? true : false; }
};

class CCSNullEntity: public CCSEntity {
public:
	CCSNullEntity(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSDMStart: public CCSPointEntity {
public:
	CCSDMStart(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual bool IsTriggered(CCSEntity *pEntity) { return m_pEntity->IsTriggered(pEntity->m_pEntity) ? true : false; }
};

class CCSFrictionModifier: public CCSEntity {
public:
	CCSFrictionModifier(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSAutoTrigger: public CCSDelay {
public:
	CCSAutoTrigger(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSTriggerRelay: public CCSDelay {
public:
	CCSTriggerRelay(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSMultiManager: public CCSToggle {
public:
	CCSMultiManager(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Restart() { m_pEntity->Restart(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual bool HasTarget(string_t targetname) { m_pEntity->HasTarget(targetname) ? true : false; }
};

class CCSRenderFxManager: public CCSEntity {
public:
	CCSRenderFxManager(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSTrigger: public CCSToggle {
public:
	CCSTrigger(CBaseEntity *pEntity) : CCSToggle(pEntity) {}
public:
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
};

class CCSTriggerHurt: public CCSTrigger {
public:
	CCSTriggerHurt(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerMonsterJump: public CCSTrigger {
public:
	CCSTriggerMonsterJump(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSTriggerCDAudio: public CCSTrigger {
public:
	CCSTriggerCDAudio(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSTargetCDAudio: public CCSPointEntity {
public:
	CCSTargetCDAudio(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Think() { m_pEntity->Think(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSTriggerMultiple: public CCSTrigger {
public:
	CCSTriggerMultiple(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerOnce: public CCSTriggerMultiple {
public:
	CCSTriggerOnce(CBaseEntity *pEntity) : CCSTriggerMultiple(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerCounter: public CCSTrigger {
public:
	CCSTriggerCounter(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerVolume: public CCSPointEntity {
public:
	CCSTriggerVolume(CBaseEntity *pEntity) : CCSPointEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSFireAndDie: public CCSDelay {
public:
	CCSFireAndDie(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Think() { m_pEntity->Think(); }
};

class CCSChangeLevel: public CCSTrigger {
public:
	CCSChangeLevel(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
};

class CCSLadder: public CCSTrigger {
public:
	CCSLadder(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSTriggerPush: public CCSTrigger {
public:
	CCSTriggerPush(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual void Touch(CCSEntity *pOther) { m_pEntity->Touch(pOther->m_pEntity); }
};

class CCSTriggerTeleport: public CCSTrigger {
public:
	CCSTriggerTeleport(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSBuyZone: public CCSTrigger {
public:
	CCSBuyZone(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSBombTarget: public CCSTrigger {
public:
	CCSBombTarget(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSHostageRescue: public CCSTrigger {
public:
	CCSHostageRescue(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSEscapeZone: public CCSTrigger {
public:
	CCSEscapeZone(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSVIP_SafetyZone: public CCSTrigger {
public:
	CCSVIP_SafetyZone(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerSave: public CCSTrigger {
public:
	CCSTriggerSave(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerEndSection: public CCSTrigger {
public:
	CCSTriggerEndSection(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CCSTriggerGravity: public CCSTrigger {
public:
	CCSTriggerGravity(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSTriggerChangeTarget: public CCSDelay {
public:
	CCSTriggerChangeTarget(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSTriggerCamera: public CCSDelay {
public:
	CCSTriggerCamera(CBaseEntity *pEntity) : CCSDelay(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) { m_pEntity->Use(pActivator->m_pEntity, pCaller->m_pEntity, useType, value); }
};

class CCSWeather: public CCSTrigger {
public:
	CCSWeather(CBaseEntity *pEntity) : CCSTrigger(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
};

class CCSClientFog: public CCSEntity {
public:
	CCSClientFog(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
};

class CReGameData: public IReGameData {
public:
	virtual CGameRules** GetGameRules();
};

template <class T>
inline T *Regamedll_InitializeEntities(CBaseEntity *a)
{
	int index = a->entindex();
	g_GameEntities[index] = new T (a);
	return reinterpret_cast<T *>(g_GameEntities[index]);
}

template <class T>
inline T *CBASE_TO_CSENTITY(CBaseEntity *a)
{
	return reinterpret_cast<T *>(CBASE_TO_CSENTITY(a));
}

inline CCSPlayer *CSPlayer(int iPlayerNum) { return reinterpret_cast<CCSPlayer *>(g_GameEntities[iPlayerNum]); }
inline CCSPlayer *CSPlayer(const edict_t *pEdict) { return CSPlayer(ENTINDEX(pEdict)); }
inline CCSPlayer *CSPlayer(CBaseEntity *pEntity) { return CSPlayer(pEntity->entindex()); }

inline CCSEntity *CSEntity(int iEntityNum) { return reinterpret_cast<CCSEntity *>(g_GameEntities[iEntityNum]); }
inline CCSEntity *CSEntity(const edict_t *pEdict) { return CSEntity(ENTINDEX(pEdict)); }
inline CCSEntity *CSEntity(CBaseEntity *pEntity) { return CSEntity(pEntity->entindex()); }

extern void Regamedll_AllocEntities(int maxEdicts);
extern void Regamedll_FreeEntities(CBaseEntity *pEntity = NULL);
extern void Regamedll_MonitorEntities();
