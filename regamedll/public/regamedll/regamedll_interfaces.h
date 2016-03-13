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

class CSave;
class Vector;
class CRestore;

class CCSEntity;
class CCSPlayer;
class CCSMonster;
class CCSWeaponBox;
class CCSPlayerItem;
class CCSPlayerWeapon;
class CCSquadMonster;

class ICSMonster;
class ICSquadMonster;

class ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Activate() = 0;
	virtual void SetObjectCollisionBox() = 0;
	virtual int Classify() = 0;
	virtual void DeathNotice(struct entvars_s *pevChild) = 0;
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int TakeHealth(float flHealth, int bitsDamageType) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual void TraceBleed(float flDamage, Vector vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
	virtual bool IsTriggered(CCSEntity *pActivator) = 0;
	virtual ICSMonster *MyMonsterPointer() = 0;
	virtual ICSquadMonster *MySquadMonsterPointer() = 0;
	virtual int GetToggleState() = 0;
	virtual void AddPoints(int score, bool bAllowNegativeScore) = 0;
	virtual void AddPointsToTeam(int score, bool bAllowNegativeScore) = 0;
	virtual bool AddPlayerItem(CCSPlayerItem *pItem) = 0;
	virtual bool RemovePlayerItem(CCSPlayerItem *pItem) = 0;
	virtual int GiveAmmo(int iAmount, char *szName, int iMax) = 0;
	virtual float GetDelay() = 0;
	virtual int IsMoving() = 0;
	virtual void OverrideReset() = 0;
	virtual int DamageDecal(int bitsDamageType) = 0;
	virtual void SetToggleState(int state) = 0;
	virtual void StartSneaking() = 0;
	virtual void StopSneaking() = 0;
	virtual bool OnControls(struct entvars_s *onpev) = 0;
	virtual bool IsSneaking() = 0;
	virtual bool IsAlive() = 0;
	virtual bool IsBSPModel() = 0;
	virtual bool ReflectGauss() = 0;
	virtual bool HasTarget(string_t targetname) = 0;
	virtual bool IsInWorld() = 0;
	virtual bool IsPlayer() = 0;
	virtual bool IsNetClient() = 0;
	virtual const char *TeamID()  = 0;
	virtual ICSEntity *GetNextTarget() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType = USE_OFF, float value = 0.0f) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
	virtual ICSEntity *Respawn() = 0;
	virtual void UpdateOwner() = 0;
	virtual bool FBecomeProne() = 0;
	virtual Vector Center() = 0;
	virtual Vector EyePosition() = 0;
	virtual Vector EarPosition() = 0;
	virtual Vector BodyTarget(const Vector &posSrc) = 0;
	virtual int Illumination() = 0;
	virtual bool FVisible(CCSEntity *pEntity) = 0;
	virtual bool FVisible(const Vector &vecOrigin) = 0;
};

class ICSDelay: public ICSEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSAnimating: public ICSDelay {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void HandleAnimEvent(struct MonsterEvent_s *pEvent) = 0;
};

class ICSPlayerItem: public ICSAnimating {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void SetObjectCollisionBox() = 0;
	virtual ICSEntity *Respawn() = 0;
	virtual int AddToPlayer(CCSPlayer *pPlayer) = 0;
	virtual int AddDuplicate(CCSPlayerItem *pItem) = 0;
	virtual int GetItemInfo(struct ItemInfo *p) = 0;
	virtual bool CanDeploy() = 0;
	virtual bool CanDrop() = 0;
	virtual bool Deploy() = 0;
	virtual bool IsWeapon() = 0;
	virtual bool CanHolster() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual void UpdateItemInfo() = 0;
	virtual void ItemPreFrame() = 0;
	virtual void ItemPostFrame() = 0;
	virtual void Drop() = 0;
	virtual void Kill() = 0;
	virtual void AttachToPlayer(CCSPlayer *pPlayer) = 0;
	virtual int PrimaryAmmoIndex() = 0;
	virtual int SecondaryAmmoIndex() = 0;
	virtual int UpdateClientData(CCSPlayer *pPlayer) = 0;
	virtual ICSPlayerItem *GetWeaponPtr() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
};

class ICSPlayerWeapon: public ICSPlayerItem {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int AddToPlayer(CCSPlayer *pPlayer) = 0;
	virtual int AddDuplicate(CCSPlayerItem *pItem) = 0;
	virtual bool CanDeploy() = 0;
	virtual bool IsWeapon() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual void UpdateItemInfo() = 0;
	virtual void ItemPostFrame() = 0;
	virtual int PrimaryAmmoIndex() = 0;
	virtual int SecondaryAmmoIndex() = 0;
	virtual int UpdateClientData(CCSPlayer *pPlayer) = 0;
	virtual ICSPlayerItem *GetWeaponPtr() = 0;
	virtual int ExtractAmmo(CCSPlayerWeapon *pWeapon) = 0;
	virtual int ExtractClipAmmo(CCSPlayerWeapon *pWeapon) = 0;
	virtual int AddWeapon() = 0;
	virtual bool PlayEmptySound() = 0;
	virtual void ResetEmptySound() = 0;
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0) = 0;
	virtual bool IsUseable() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual void RetireWeapon() = 0;
	virtual bool ShouldWeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSToggle: public ICSAnimating {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int GetToggleState() = 0;
	virtual float GetDelay() = 0;
};

class ICSMonster: public ICSToggle {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int TakeHealth(float flHealth, int bitsDamageType) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual bool IsAlive() = 0;
	virtual float ChangeYaw(int speed) = 0;
	virtual bool HasHumanGibs() = 0;
	virtual bool HasAlienGibs() = 0;
	virtual void FadeMonster() = 0;
	virtual void GibMonster() = 0;
	virtual enum Activity_s GetDeathActivity() = 0;
	virtual void BecomeDead() = 0;
	virtual bool ShouldFadeOnDeath() = 0;
	virtual int IRelationship(CCSEntity *pTarget) = 0;
	virtual void PainSound() = 0;
	virtual void ResetMaxSpeed() = 0;
	virtual void ReportAIState() = 0;
	virtual void MonsterInitDead() = 0;
	virtual void Look(int iDistance) = 0;
	virtual ICSEntity *BestVisibleEnemy() = 0;
	virtual bool FInViewCone(CCSEntity *pEntity) = 0;
	virtual bool FInViewCone(const Vector *pOrigin) = 0;
};

class ICSWeaponBox: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void SetObjectCollisionBox() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSPlayer: public ICSMonster {
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual int Classify() = 0;
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int TakeHealth(float flHealth, int bitsDamageType) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual void AddPoints(int score, bool bAllowNegativeScore) = 0;
	virtual void AddPointsToTeam(int score, bool bAllowNegativeScore) = 0;
	virtual bool AddPlayerItem(CCSPlayerItem *pItem) = 0;
	virtual bool RemovePlayerItem(CCSPlayerItem *pItem) = 0;
	virtual int GiveAmmo(int iAmount, char *szName, int iMax) = 0;
	virtual void StartSneaking() = 0;
	virtual void StopSneaking() = 0;
	virtual bool IsSneaking() = 0;
	virtual bool IsAlive() = 0;
	virtual bool IsPlayer() = 0;
	virtual bool IsNetClient() = 0;
	virtual const char *TeamID() = 0;
	virtual bool FBecomeProne() = 0;
	virtual Vector BodyTarget(const Vector &posSrc) = 0;
	virtual int Illumination() = 0;
	virtual bool ShouldFadeOnDeath() = 0;
	virtual void ResetMaxSpeed() = 0;
	virtual void Jump() = 0;
	virtual void Duck() = 0;
	virtual void PreThink() = 0;
	virtual void PostThink() = 0;
	virtual Vector GetGunPosition() = 0;
	virtual bool IsBot() = 0;
	virtual void UpdateClientData() = 0;
	virtual void ImpulseCommands() = 0;
	virtual void RoundRespawn() = 0;
	virtual Vector GetAutoaimVector(float flDelta) = 0;
	virtual void Blind(float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha) = 0;
	virtual void OnTouchingWeapon(CCSWeaponBox *pWeapon) = 0;

	virtual bool IsConnected() const = 0;
};

class ICSWorld: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSGrenade: public ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void BounceSound() = 0;
};

class ICSAirtank: public ICSGrenade {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
};

class ICSPlayerAmmo: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
	virtual ICSEntity *Respawn() = 0;
};

class ICS9MMAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICSBuckShotAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS556NatoAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS556NatoBoxAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS762NatoAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS45ACPAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS50AEAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS338MagnumAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS57MMAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS357SIGAmmo: public ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICSFuncWall: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncWallToggle: public ICSFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncConveyor: public ICSFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncIllusionary: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSFuncMonsterClip: public ICSFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncRotating: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSPendulum: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSPointEntity: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSEnvGlobal: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSMultiSource: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool IsTriggered(CCSEntity *pActivator) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSButton: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSRotButton: public ICSButton {
public:
	virtual void Spawn() = 0;
};

class ICSMomentaryRotButton: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvSpark: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSButtonTarget: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSDoor: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void SetToggleState(int state) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSRotDoor: public ICSDoor {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void SetToggleState(int state) = 0;
};

class ICSMomentaryDoor: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGib: public ICSEntity {
public:
	virtual int ObjectCaps() = 0;
};

class ICSBubbling: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBeam: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual Vector Center() = 0;
};

class ICSLightning: public ICSBeam {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
};

class ICSLaser: public ICSBeam {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGlow: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
};

class ICSSprite: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBombGlow: public ICSSprite {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
};

class ICSGibShooter: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual ICSGib *CreateGib() = 0;
};

class ICSEnvShooter: public ICSGibShooter {
public:
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual ICSGib *CreateGib() = 0;
};


class ICSTestEffect: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBlood: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSShake: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFade: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};


class ICSMessage: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvFunnel: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvBeverage: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSItemSoda: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
};

class ICSShower: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSEnvExplosion: public ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBreakable: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int DamageDecal(int bitsDamageType) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSPushable: public ICSBreakable {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncTank: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool OnControls(struct entvars_s *pevTest) = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
	virtual Vector UpdateTargetPosition(CCSEntity *pTarget) = 0;
};

class ICSFuncTankGun: public ICSFuncTank {
public:
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankLaser: public ICSFuncTank {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
	virtual void Think() = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankRocket: public ICSFuncTank {
public:
	virtual void Precache() = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankMortar: public ICSFuncTank {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankControls: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSRecharge: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSCycler: public ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual bool IsAlive() = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGenericCycler: public ICSCycler {
public:
	virtual void Spawn() = 0;
};

class ICSCyclerProbe: public ICSCycler {
public:
	virtual void Spawn() = 0;
};

class ICSCyclerSprite: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSWeaponCycler: public ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual int GetItemInfo(struct ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
};

class ICSWreckage: public ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
};

class ICSWorldItem: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSItem: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual ICSEntity *Respawn() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSHealthKit: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemSuit: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemBattery: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemAntidote: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemSecurity: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemLongJump: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemKevlar: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemAssaultSuit: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemThighPack: public ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

