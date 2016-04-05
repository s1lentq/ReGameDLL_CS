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
class BotProfile;
class CCSWeaponBox;
class CCSPlayerItem;
class CCSPlayerWeapon;
class CCSquadMonster;

class ICSMonster;
class ICSquadMonster;

enum VisiblePartTypeBot:uint8
{
	NONE = 0x00,
	CHEST = 0x01,
	HEAD = 0x02,
	LEFT_SIDE = 0x04,
	RIGHT_SIDE = 0x08,
	FEET = 0x10
};

class ICSEntity {
public:
	virtual ~ICSEntity() = 0;
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
public:
	virtual struct entvars_s *GetEntVars() const = 0;
	virtual class CBaseEntity *GetEntity() const = 0;
};

class ICSDelay: public virtual ICSEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSAnimating: public virtual ICSDelay {
public:
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void HandleAnimEvent(struct MonsterEvent_s *pEvent) = 0;
};

class ICSPlayerItem: public virtual ICSAnimating {
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

class ICSPlayerWeapon: public virtual ICSPlayerItem {
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

class ICSToggle: public virtual ICSAnimating {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int GetToggleState() = 0;
	virtual float GetDelay() = 0;
};

class ICSMonster: public virtual ICSToggle {
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

class ICSWeaponBox: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void SetObjectCollisionBox() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSArmoury: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSPlayer: public virtual ICSMonster {
public:
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
public:
	virtual bool IsConnected() const = 0;
};

class IAPI_Bot: public virtual ICSPlayer {
public:
	virtual void Spawn() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual void Think() = 0;
	virtual bool IsBot() = 0;
	virtual Vector GetAutoaimVector(float flDelta) = 0;
	virtual void OnTouchingWeapon(CCSWeaponBox *box) = 0;
	virtual bool Initialize(const BotProfile *profile) = 0;
	virtual void SpawnBot() = 0;
	virtual void Upkeep() = 0;
	virtual void Update() = 0;
	virtual void Run() = 0;
	virtual void Walk() = 0;
	virtual void Crouch() = 0;
	virtual void StandUp() = 0;
	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void StrafeLeft() = 0;
	virtual void StrafeRight() = 0;
	virtual bool Jump(bool mustJump = false) = 0;
	virtual void ClearMovement() = 0;
	virtual void UseEnvironment() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void ClearPrimaryAttack() = 0;
	virtual void TogglePrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void OnEvent(enum GameEventType event, CCSEntity *entity = NULL, CCSEntity *other = NULL) = 0;
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;
	virtual bool IsVisible(CCSPlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const = 0;
	virtual bool IsEnemyPartVisible(VisiblePartTypeBot part) const = 0;
	virtual bool IsPlayerFacingMe(CCSPlayer *other) const = 0;
	virtual bool IsPlayerLookingAtMe(CCSPlayer *other) const = 0;
	virtual void ExecuteCommand() = 0;
	virtual void SetModel(const char *modelName) = 0;
};

class IAPI_CSBot: public virtual IAPI_Bot {
public:
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual void RoundRespawn() = 0;
	virtual void Blind(float duration, float holdTime, float fadeTime, int alpha = 255) = 0;
	virtual void OnTouchingWeapon(CCSWeaponBox *box) = 0;
	virtual bool Initialize(const BotProfile *profile) = 0;
	virtual void SpawnBot() = 0;
	virtual void Upkeep() = 0;
	virtual void Update() = 0;
	virtual void Walk() = 0;
	virtual bool Jump(bool mustJump = false) = 0;
	virtual void OnEvent(enum GameEventType event, CCSEntity *entity = NULL, CCSEntity *other = NULL) = 0;
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;
	virtual bool IsVisible(CCSPlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const = 0;
	virtual bool IsEnemyPartVisible(VisiblePartTypeBot part) const = 0;
};

class ICSShield: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSDeadHEV: public virtual ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Classify() = 0;
};

class ICSSprayCan: public virtual ICSEntity {
public:
	virtual void Think() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSBloodSplat: public virtual ICSEntity {
public:
};

class ICSWorld: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSDecal: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSCorpse: public virtual ICSEntity {
public:
	virtual int ObjectCaps() = 0;
};

class ICSGrenade: public virtual ICSMonster {
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

class ICSAirtank: public virtual ICSGrenade {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
};

class ICSPlayerAmmo: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
	virtual ICSEntity *Respawn() = 0;
};

class ICS9MMAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICSBuckShotAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS556NatoAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS556NatoBoxAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS762NatoAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS45ACPAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS50AEAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS338MagnumAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS57MMAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICS357SIGAmmo: public virtual ICSPlayerAmmo {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool AddAmmo(CCSEntity *pOther) = 0;
};

class ICSFuncWall: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncWallToggle: public virtual ICSFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncConveyor: public virtual ICSFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncIllusionary: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSFuncMonsterClip: public virtual ICSFuncWall {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncRotating: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSPendulum: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSPointEntity: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSStripWeapons: public virtual ICSPointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSInfoIntermission: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
};

class ICSRevertSaved: public virtual ICSPointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvGlobal: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSMultiSource: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool IsTriggered(CCSEntity *pActivator) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSButton: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSRotButton: public virtual ICSButton {
public:
	virtual void Spawn() = 0;
};

class ICSMomentaryRotButton: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvSpark: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSButtonTarget: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSDoor: public virtual ICSToggle {
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

class ICSRotDoor: public virtual ICSDoor {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void SetToggleState(int state) = 0;
};

class ICSMomentaryDoor: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGib: public virtual ICSEntity {
public:
	virtual int ObjectCaps() = 0;
};

class ICSBubbling: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBeam: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual Vector Center() = 0;
};

class ICSLightning: public virtual ICSBeam {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
};

class ICSLaser: public virtual ICSBeam {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGlow: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
};

class ICSSprite: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBombGlow: public virtual ICSSprite {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
};

class ICSGibShooter: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual ICSGib *CreateGib() = 0;
};

class ICSEnvShooter: public virtual ICSGibShooter {
public:
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual ICSGib *CreateGib() = 0;
};


class ICSTestEffect: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBlood: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSShake: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFade: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};


class ICSMessage: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvFunnel: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvBeverage: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSItemSoda: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
};

class ICSShower: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSEnvExplosion: public virtual ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSBreakable: public virtual ICSDelay {
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

class ICSPushable: public virtual ICSBreakable {
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

class ICSFuncTank: public virtual ICSEntity {
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

class ICSFuncTankGun: public virtual ICSFuncTank {
public:
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankLaser: public virtual ICSFuncTank {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
	virtual void Think() = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankRocket: public virtual ICSFuncTank {
public:
	virtual void Precache() = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankMortar: public virtual ICSFuncTank {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Fire(const Vector &barrelEnd, const Vector &forward, struct entvars_s *pevAttacker) = 0;
};

class ICSFuncTankControls: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSRecharge: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSCycler: public virtual ICSMonster {
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

class ICSGenericCycler: public virtual ICSCycler {
public:
	virtual void Spawn() = 0;
};

class ICSCyclerProbe: public virtual ICSCycler {
public:
	virtual void Spawn() = 0;
};

class ICSCyclerSprite: public virtual ICSEntity {
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

class ICSWeaponCycler: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual int GetItemInfo(struct ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal = 0) = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
};

class ICSWreckage: public virtual ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
};

class ICSWorldItem: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSItem: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual ICSEntity *Respawn() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSHealthKit: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSWallHealth: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSItemSuit: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemBattery: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemAntidote: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemSecurity: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemLongJump: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemKevlar: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemAssaultSuit: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSItemThighPack: public virtual ICSItem {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual bool MyTouch(CCSPlayer *pPlayer) = 0;
};

class ICSGrenCatch: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSFuncWeaponCheck: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSHostage: public virtual ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual int Classify() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int BloodColor() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSLight: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvLight: public virtual ICSLight {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSRuleEntity: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSRulePointEntity: public virtual ICSRuleEntity {
public:
	virtual void Spawn() = 0;
};

class ICSRuleBrushEntity: public virtual ICSRuleEntity {
public:
	virtual void Spawn() = 0;
};

class ICSGameScore: public virtual ICSRulePointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameEnd: public virtual ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameText: public virtual ICSRulePointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameTeamMaster: public virtual ICSRulePointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool IsTriggered(CCSEntity *pActivator) = 0;
	virtual const char *TeamID() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameTeamSet: public virtual ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerZone: public virtual ICSRuleBrushEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerHurt: public virtual ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameCounter: public virtual ICSRulePointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameCounterSet: public virtual ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerEquip: public virtual ICSRulePointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerTeam: public virtual ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncMortarField: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSMortar: public virtual ICSGrenade {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
};

class ICSMapInfo: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSPathCorner: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual float GetDelay() = 0;
};

class ICSPathTrack: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncTrackTrain: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void OverrideReset() = 0;
	virtual bool OnControls(struct entvars_s *pev) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSFuncVehicleControls: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSFuncVehicle: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual int Classify() = 0;
	virtual void OverrideReset() = 0;
	virtual bool OnControls(struct entvars_s *pev) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSPlatTrain: public virtual ICSToggle {
public:
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool IsTogglePlat() = 0;
};

class ICSFuncPlat: public virtual ICSPlatTrain {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
	virtual void GoUp() = 0;
	virtual void GoDown() = 0;
	virtual void HitTop() = 0;
	virtual void HitBottom() = 0;
};

class ICSPlatTrigger: public virtual ICSEntity {
public:
	virtual int ObjectCaps() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSFuncPlatRot: public virtual ICSFuncPlat {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void GoUp() = 0;
	virtual void GoDown() = 0;
	virtual void HitTop() = 0;
	virtual void HitBottom() = 0;
};

class ICSFuncTrain: public virtual ICSPlatTrain {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
	virtual void OverrideReset() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
};

class ICSFuncTrainControls: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSFuncTrackChange: public virtual ICSFuncPlatRot {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void OverrideReset() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual bool IsTogglePlat() = 0;
	virtual void GoUp() = 0;
	virtual void GoDown() = 0;
	virtual void HitTop() = 0;
	virtual void HitBottom() = 0;
	virtual void UpdateAutoTargets(int toggleState) = 0;
};

class ICSFuncTrackAuto: public virtual ICSFuncTrackChange {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void UpdateAutoTargets(int toggleState) = 0;
};

class ICSGunTarget: public virtual ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Activate() = 0;
	virtual int Classify() = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int BloodColor() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual Vector BodyTarget(const Vector &posSrc) = 0;
};

class ICSAmbientGeneric: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSEnvSound: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
};

class ICSSpeaker: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSSoundEnt: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
};

class ICSUSP: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSMP5N: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSSG552: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSAK47: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSAUG: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSAWP: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSC4: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSDEAGLE: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
	virtual bool IsPistol() = 0;
};

class ICSFlashbang: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool CanDeploy() = 0;
	virtual bool CanDrop() = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
	virtual bool IsPistol() = 0;
};

class ICSG3SG1: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSGLOCK18: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSHEGrenade: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool CanDeploy() = 0;
	virtual bool CanDrop() = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSKnife: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool CanDrop() = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSM249: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSM3: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSM4A1: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSMAC10: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSP228: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
	virtual bool IsPistol() = 0;
};

class ICSP90: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSSCOUT: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSSmokeGrenade: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool CanDeploy() = 0;
	virtual bool CanDrop() = 0;
	virtual bool Deploy() = 0;
	virtual void Holster(int skiplocal) = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSTMP: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSXM1014: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSELITE: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSFiveSeven: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSUMP45: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSSG550: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSGalil: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSFamas: public virtual ICSPlayerWeapon {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int GetItemInfo(ItemInfo *p) = 0;
	virtual bool Deploy() = 0;
	virtual float GetMaxSpeed() = 0;
	virtual int iItemSlot() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;
	virtual void WeaponIdle() = 0;
	virtual bool UseDecrement() = 0;
};

class ICSNullEntity: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
};

class ICSDMStart: public virtual ICSPointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual bool IsTriggered(CCSEntity *pEntity) = 0;
};

class ICSFrictionModifier: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSAutoTrigger: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
};

class ICSTriggerRelay: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSMultiManager: public virtual ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool HasTarget(string_t targetname) = 0;
};

class ICSRenderFxManager: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTrigger: public virtual ICSToggle {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSTriggerHurt: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerMonsterJump: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSTriggerCDAudio: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTargetCDAudio: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTriggerMultiple: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerOnce: public virtual ICSTriggerMultiple {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerCounter: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerVolume: public virtual ICSPointEntity {
public:
	virtual void Spawn() = 0;
};

class ICSFireAndDie: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
};

class ICSChangeLevel: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSLadder: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSTriggerPush: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSTriggerTeleport: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSBuyZone: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSBombTarget: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSHostageRescue: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSEscapeZone: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSVIP_SafetyZone: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerSave: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerEndSection: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSTriggerGravity: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerChangeTarget: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTriggerCamera: public virtual ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSWeather: public virtual ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSClientFog: public virtual ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class IReGameData {
public:
	virtual ~IReGameData() {}

	virtual class CGameRules** GetGameRules() = 0;
};
