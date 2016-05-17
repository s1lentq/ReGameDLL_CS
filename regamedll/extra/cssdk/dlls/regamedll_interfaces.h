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
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector &vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
	virtual int TakeDamage(struct entvars_s *pevInflictor, struct entvars_s *pevAttacker, float flDamage, int bitsDamageType) = 0;
	virtual int TakeHealth(float flHealth, int bitsDamageType) = 0;
	virtual void Killed(struct entvars_s *pevAttacker, int iGib) = 0;
	virtual int BloodColor() = 0;
	virtual void TraceBleed(float flDamage, Vector &vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
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
	virtual void FireBullets(int iShots, Vector &vecSrc, Vector &vecDirShooting, Vector &vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker) = 0;
	virtual Vector FireBullets3(Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand) = 0;
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
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector &vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
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

class ICSArmoury: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSPlayer: public ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual int Classify() = 0;
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector &vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
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

	virtual void SetAnimation(PLAYER_ANIM playerAnim) = 0;
	virtual void AddAccount(int amount, bool bTrackChange = true) = 0;
	virtual void GiveNamedItem(const char *pszName) = 0;
	virtual void GiveNamedItemEx(const char *pszName) = 0;
	virtual void GiveDefaultItems() = 0;
	virtual void GiveShield(bool bDeploy = true) = 0;
	virtual void DropShield(bool bDeploy = true) = 0;
	virtual void DropPlayerItem(const char *pszItemName) = 0;
	virtual void RemoveShield() = 0;
	virtual void RemoveAllItems(bool bRemoveSuit) = 0;
};

class IAPI_Bot: public ICSPlayer {
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

class IAPI_CSBot: public IAPI_Bot {
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

class ICSShield: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSDeadHEV: public ICSMonster {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Classify() = 0;
};

class ICSSprayCan: public ICSEntity {
public:
	virtual void Think() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSBloodSplat: public ICSEntity {
public:
};

class ICSWorld: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSDecal: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSCorpse: public ICSEntity {
public:
	virtual int ObjectCaps() = 0;
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

class ICSStripWeapons: public ICSPointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSInfoIntermission: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
};

class ICSRevertSaved: public ICSPointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
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
	virtual void TraceAttack(struct entvars_s *pevAttacker, float flDamage, Vector &vecDir, struct TraceResult *ptr, int bitsDamageType) = 0;
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

class ICSWallHealth: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
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

class ICSGrenCatch: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSFuncWeaponCheck: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSHostage: public ICSMonster {
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

class ICSLight: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSEnvLight: public ICSLight {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSRuleEntity: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSRulePointEntity: public ICSRuleEntity {
public:
	virtual void Spawn() = 0;
};

class ICSRuleBrushEntity: public ICSRuleEntity {
public:
	virtual void Spawn() = 0;
};

class ICSGameScore: public ICSRulePointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameEnd: public ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameText: public ICSRulePointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameTeamMaster: public ICSRulePointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool IsTriggered(CCSEntity *pActivator) = 0;
	virtual const char *TeamID() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameTeamSet: public ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerZone: public ICSRuleBrushEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerHurt: public ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameCounter: public ICSRulePointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGameCounterSet: public ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerEquip: public ICSRulePointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSGamePlayerTeam: public ICSRulePointEntity {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncMortarField: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSMortar: public ICSGrenade {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
};

class ICSMapInfo: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSPathCorner: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual float GetDelay() = 0;
};

class ICSPathTrack: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSFuncTrackTrain: public ICSEntity {
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

class ICSFuncVehicleControls: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSFuncVehicle: public ICSEntity {
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

class ICSPlatTrain: public ICSToggle {
public:
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool IsTogglePlat() = 0;
};

class ICSFuncPlat: public ICSPlatTrain {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Blocked(CCSEntity *pOther) = 0;
	virtual void GoUp() = 0;
	virtual void GoDown() = 0;
	virtual void HitTop() = 0;
	virtual void HitBottom() = 0;
};

class ICSPlatTrigger: public ICSEntity {
public:
	virtual int ObjectCaps() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSFuncPlatRot: public ICSFuncPlat {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void GoUp() = 0;
	virtual void GoDown() = 0;
	virtual void HitTop() = 0;
	virtual void HitBottom() = 0;
};

class ICSFuncTrain: public ICSPlatTrain {
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

class ICSFuncTrainControls: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};

class ICSFuncTrackChange: public ICSFuncPlatRot {
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

class ICSFuncTrackAuto: public ICSFuncTrackChange {
public:
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual void UpdateAutoTargets(int toggleState) = 0;
};

class ICSGunTarget: public ICSMonster {
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

class ICSAmbientGeneric: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSEnvSound: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
};

class ICSSpeaker: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSSoundEnt: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
};

class ICSUSP: public ICSPlayerWeapon {
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

class ICSMP5N: public ICSPlayerWeapon {
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

class ICSSG552: public ICSPlayerWeapon {
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

class ICSAK47: public ICSPlayerWeapon {
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

class ICSAUG: public ICSPlayerWeapon {
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

class ICSAWP: public ICSPlayerWeapon {
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

class ICSC4: public ICSPlayerWeapon {
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

class ICSDEAGLE: public ICSPlayerWeapon {
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

class ICSFlashbang: public ICSPlayerWeapon {
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

class ICSG3SG1: public ICSPlayerWeapon {
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

class ICSGLOCK18: public ICSPlayerWeapon {
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

class ICSHEGrenade: public ICSPlayerWeapon {
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

class ICSKnife: public ICSPlayerWeapon {
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

class ICSM249: public ICSPlayerWeapon {
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

class ICSM3: public ICSPlayerWeapon {
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

class ICSM4A1: public ICSPlayerWeapon {
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

class ICSMAC10: public ICSPlayerWeapon {
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

class ICSP228: public ICSPlayerWeapon {
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

class ICSP90: public ICSPlayerWeapon {
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

class ICSSCOUT: public ICSPlayerWeapon {
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

class ICSSmokeGrenade: public ICSPlayerWeapon {
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

class ICSTMP: public ICSPlayerWeapon {
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

class ICSXM1014: public ICSPlayerWeapon {
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

class ICSELITE: public ICSPlayerWeapon {
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

class ICSFiveSeven: public ICSPlayerWeapon {
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

class ICSUMP45: public ICSPlayerWeapon {
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

class ICSSG550: public ICSPlayerWeapon {
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

class ICSGalil: public ICSPlayerWeapon {
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

class ICSFamas: public ICSPlayerWeapon {
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

class ICSNullEntity: public ICSEntity {
public:
	virtual void Spawn() = 0;
};

class ICSDMStart: public ICSPointEntity {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual bool IsTriggered(CCSEntity *pEntity) = 0;
};

class ICSFrictionModifier: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSAutoTrigger: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
};

class ICSTriggerRelay: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSMultiManager: public ICSToggle {
public:
	virtual void Spawn() = 0;
	virtual void Restart() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual bool HasTarget(string_t targetname) = 0;
};

class ICSRenderFxManager: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTrigger: public ICSToggle {
public:
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int ObjectCaps() = 0;
};

class ICSTriggerHurt: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerMonsterJump: public ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSTriggerCDAudio: public ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTargetCDAudio: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Think() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTriggerMultiple: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerOnce: public ICSTriggerMultiple {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerCounter: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerVolume: public ICSPointEntity {
public:
	virtual void Spawn() = 0;
};

class ICSFireAndDie: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual void Think() = 0;
};

class ICSChangeLevel: public ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
};

class ICSLadder: public ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSTriggerPush: public ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual void Touch(CCSEntity *pOther) = 0;
};

class ICSTriggerTeleport: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSBuyZone: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSBombTarget: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSHostageRescue: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSEscapeZone: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSVIP_SafetyZone: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerSave: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerEndSection: public ICSTrigger {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};

class ICSTriggerGravity: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSTriggerChangeTarget: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSTriggerCamera: public ICSDelay {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CCSEntity *pActivator, CCSEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class ICSWeather: public ICSTrigger {
public:
	virtual void Spawn() = 0;
};

class ICSClientFog: public ICSEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(struct KeyValueData_s *pkvd) = 0;
};
