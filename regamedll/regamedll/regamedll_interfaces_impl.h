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

class CCSEntity: public ICSEntity {
public:
	CBaseEntity *m_pEntity;
	CCSEntity(CBaseEntity *pEntity) : m_pEntity(pEntity) {}
public:
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
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return m_pEntity->TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
	virtual int TakeHealth(float flHealth, int bitsDamageType) { return m_pEntity->TakeHealth(flHealth, bitsDamageType); }
	virtual void Killed(entvars_t *pevAttacker, int iGib) { m_pEntity->Killed(pevAttacker, iGib); }
	virtual int BloodColor() { return m_pEntity->BloodColor(); }
	virtual void TraceBleed(float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceBleed(flDamage, vecDir, ptr, bitsDamageType); }
	virtual bool IsTriggered(CCSEntity *pActivator) { return m_pEntity->IsTriggered(pActivator->m_pEntity) ? TRUE : FALSE; }
	virtual ICSMonster *MyMonsterPointer() { return (ICSMonster *)CBASE_TO_CSENTITY(m_pEntity->MyMonsterPointer()); }
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
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
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

class CCSPlayer: public CCSMonster {
private:
	bool m_bConnected;
public:
	CCSPlayer(CBaseEntity *pEntity) : CCSMonster(pEntity) {}
	void OnClientConnected() { m_bConnected = true; }
	void OnClientDisconnected() { m_bConnected = false; }

	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual int Save(CSave &save) { return m_pEntity->Save(save); }
	virtual int Restore(CRestore &restore) { return m_pEntity->Restore(restore); }
	virtual int ObjectCaps() { return m_pEntity->ObjectCaps(); }
	virtual int Classify() { return m_pEntity->Classify(); }
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
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
	virtual bool IsConnected() const { return m_bConnected; }
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
	virtual ICSPlayerItem *GetWeaponPtr() { return (ICSPlayerItem *)CBASE_TO_CSENTITY(((CBasePlayerWeapon *)m_pEntity)->GetWeaponPtr()); }
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

class CCSWorld: public CCSEntity
{
public:
	CCSWorld(CBaseEntity *pEntity) : CCSEntity(pEntity) {}
public:
	virtual void Spawn() { m_pEntity->Spawn(); }
	virtual void Precache() { m_pEntity->Precache(); }
	virtual void KeyValue(KeyValueData *pkvd) { m_pEntity->KeyValue(pkvd); }
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
	virtual void TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { m_pEntity->TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
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




inline CCSPlayer *CSPlayer(int iPlayerNum) { return reinterpret_cast<CCSPlayer *>(g_GameEntities[iPlayerNum]); }
inline CCSPlayer *CSPlayer(const edict_t *pEdict) { return CSPlayer(ENTINDEX(pEdict)); }
inline CCSPlayer *CSPlayer(CBaseEntity *pEntity) { return CSPlayer(pEntity->entindex()); }

inline CCSEntity *CSEntity(int iEntityNum) { return reinterpret_cast<CCSEntity *>(g_GameEntities[iEntityNum]); }
inline CCSEntity *CSEntity(const edict_t *pEdict) { return CSEntity(ENTINDEX(pEdict)); }
inline CCSEntity *CSEntity(CBaseEntity *pEntity) { return CSEntity(pEntity->entindex()); }

extern void Regamedll_AllocEntities(int maxEdicts);
extern void Regamedll_FreeEntities(CBaseEntity *pEntity = NULL);
extern void Regamedll_MonitorEntities();
