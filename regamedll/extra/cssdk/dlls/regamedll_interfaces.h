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

class CBaseEntity;
class CBasePlayer;

// Implementation wrapper
class CCSEntity {
public:
	virtual ~CCSEntity() {}
	virtual void FireBullets(int iShots, Vector &vecSrc, Vector &vecDirShooting, Vector &vecSpread, float flDistance, int iBulletType, int iTracerFreq, int iDamage, entvars_t *pevAttacker);
	virtual Vector FireBullets3(Vector &vecSrc, Vector &vecDirShooting, float vecSpread, float flDistance, int iPenetration, int iBulletType, int iDamage, float flRangeModifier, entvars_t *pevAttacker, bool bPistol, int shared_rand);
public:
	CBaseEntity *m_pContainingEntity;
};

class CCSDelay: public CCSEntity {};
class CCSAnimating: public CCSDelay {};
class CCSPlayerItem: public CCSAnimating {};
class CCSToggle: public CCSAnimating {};
class CCSMonster: public CCSToggle {};
class CCSWeaponBox: public CCSEntity {};
class CCSArmoury: public CCSEntity {};

class CCSPlayer: public CCSMonster {
public:
	CCSPlayer() : m_bForceShowMenu(false)
	{
		m_szModel[0] = '\0';
	}

	virtual bool IsConnected() const;
	virtual void SetAnimation(PLAYER_ANIM playerAnim);
	virtual void AddAccount(int amount, RewardType type = RT_NONE, bool bTrackChange = true);
	virtual CBaseEntity *GiveNamedItem(const char *pszName);
	virtual CBaseEntity *GiveNamedItemEx(const char *pszName);
	virtual void GiveDefaultItems();
	virtual void GiveShield(bool bDeploy = true);
	virtual void DropShield(bool bDeploy = true);
	virtual void DropPlayerItem(const char *pszItemName);
	virtual void RemoveShield();
	virtual void RemoveAllItems(bool bRemoveSuit);
	virtual bool RemovePlayerItem(const char* pszItemName);
	virtual void SetPlayerModel(bool bHasC4);
	virtual void SetPlayerModelEx(const char *modelName);
	virtual void SetNewPlayerModel(const char *modelName);
	virtual void ClientCommand(const char *cmd, const char *arg1 = nullptr, const char *arg2 = nullptr, const char *arg3 = nullptr);
	virtual void SetProgressBarTime(int time);
	virtual void SetProgressBarTime2(int time, float timeElapsed);
	virtual struct edict_s *EntSelectSpawnPoint();
	virtual void SetBombIcon(bool bFlash = false);
	virtual void SetScoreAttrib(CBasePlayer *dest);
	virtual void SendItemStatus();
	virtual void ReloadWeapons(CBasePlayerItem *pWeapon = nullptr, bool bForceReload = false, bool bForceRefill = false);
	virtual void Observer_SetMode(int iMode);
	virtual bool SelectSpawnSpot(const char *pEntClassName, CBaseEntity* &pSpot);
	virtual bool SwitchWeapon(CBasePlayerItem *pWeapon);
	virtual void SwitchTeam();
	virtual bool JoinTeam(TeamName team);
	virtual void StartObserver(Vector& vecPosition, Vector& vecViewAngle);
	virtual void TeamChangeUpdate();
	virtual void DropSecondary();
	virtual void DropPrimary();
	virtual bool HasPlayerItem(CBasePlayerItem *pCheckItem);
	virtual bool HasNamedPlayerItem(const char *pszItemName);
	virtual CBasePlayerItem *GetItemById(WeaponIdType weaponID);
	virtual CBasePlayerItem *GetItemByName(const char *itemName);
	virtual void Disappear();
	virtual void MakeVIP();
	virtual bool MakeBomber();

	CBasePlayer *BasePlayer() const;
public:
	char m_szModel[32];
	bool m_bForceShowMenu;
};

class CAPI_Bot: public CCSPlayer {};
class CAPI_CSBot: public CAPI_Bot {};
class CCSShield: public CCSEntity {};
class CCSDeadHEV: public CCSMonster {};
class CCSSprayCan: public CCSEntity {};
class CCSBloodSplat: public CCSEntity {};
class CCSPlayerWeapon: public CCSPlayerItem {};
class CCSWorld: public CCSEntity {};
class CCSDecal: public CCSEntity {};
class CCSCorpse: public CCSEntity {};
class CCSGrenade: public CCSMonster {};
class CCSAirtank: public CCSGrenade {};
class CCSPlayerAmmo: public CCSEntity {};
class CCS9MMAmmo: public CCSPlayerAmmo {};
class CCSBuckShotAmmo: public CCSPlayerAmmo {};
class CCS556NatoAmmo: public CCSPlayerAmmo {};
class CCS556NatoBoxAmmo: public CCSPlayerAmmo {};
class CCS762NatoAmmo: public CCSPlayerAmmo {};
class CCS45ACPAmmo: public CCSPlayerAmmo {};
class CCS50AEAmmo: public CCSPlayerAmmo {};
class CCS338MagnumAmmo: public CCSPlayerAmmo {};
class CCS57MMAmmo: public CCSPlayerAmmo {};
class CCS357SIGAmmo: public CCSPlayerAmmo {};
class CCSFuncWall: public CCSEntity {};
class CCSFuncWallToggle: public CCSFuncWall {};
class CCSFuncConveyor: public CCSFuncWall {};
class CCSFuncIllusionary: public CCSToggle {};
class CCSFuncMonsterClip: public CCSFuncWall {};
class CCSFuncRotating: public CCSEntity {};
class CCSPendulum: public CCSEntity {};
class CCSPointEntity: public CCSEntity {};
class CCSStripWeapons: public CCSPointEntity {};
class CCSInfoIntermission: public CCSPointEntity {};
class CCSRevertSaved: public CCSPointEntity {};
class CCSEnvGlobal: public CCSPointEntity {};
class CCSMultiSource: public CCSPointEntity {};
class CCSButton: public CCSToggle {};
class CCSRotButton: public CCSButton {};
class CCSMomentaryRotButton: public CCSToggle {};
class CCSEnvSpark: public CCSEntity {};
class CCSButtonTarget: public CCSEntity {};
class CCSDoor: public CCSToggle {};
class CCSRotDoor: public CCSDoor {};
class CCSMomentaryDoor: public CCSToggle {};
class CCSGib: public CCSEntity {};
class CCSBubbling: public CCSEntity {};
class CCSBeam: public CCSEntity {};
class CCSLightning: public CCSBeam {};
class CCSLaser: public CCSBeam {};
class CCSGlow: public CCSPointEntity {};
class CCSSprite: public CCSPointEntity {};
class CCSBombGlow: public CCSSprite {};
class CCSGibShooter: public CCSDelay {};
class CCSEnvShooter: public CCSGibShooter {};
class CCSTestEffect: public CCSDelay {};
class CCSBlood: public CCSPointEntity {};
class CCSShake: public CCSPointEntity {};
class CCSFade: public CCSPointEntity {};
class CCSMessage: public CCSPointEntity {};
class CCSEnvFunnel: public CCSDelay {};
class CCSEnvBeverage: public CCSDelay {};
class CCSItemSoda: public CCSEntity {};
class CCSShower: public CCSEntity {};
class CCSEnvExplosion: public CCSMonster {};
class CCSBreakable: public CCSDelay {};
class CCSPushable: public CCSBreakable {};
class CCSFuncTank: public CCSEntity {};
class CCSFuncTankGun: public CCSFuncTank {};
class CCSFuncTankLaser: public CCSFuncTank {};
class CCSFuncTankRocket: public CCSFuncTank {};
class CCSFuncTankMortar: public CCSFuncTank {};
class CCSFuncTankControls: public CCSEntity {};
class CCSRecharge: public CCSToggle {};
class CCSCycler: public CCSMonster {};
class CCSGenericCycler: public CCSCycler {};
class CCSCyclerProbe: public CCSCycler {};
class CCSCyclerSprite: public CCSEntity {};
class CCSWeaponCycler: public CCSPlayerWeapon {};
class CCSWreckage: public CCSMonster {};
class CCSWorldItem: public CCSEntity {};
class CCSItem: public CCSEntity {};
class CCSHealthKit: public CCSItem {};
class CCSWallHealth: public CCSToggle {};
class CCSItemSuit: public CCSItem {};
class CCSItemBattery: public CCSItem {};
class CCSItemAntidote: public CCSItem {};
class CCSItemSecurity: public CCSItem {};
class CCSItemLongJump: public CCSItem {};
class CCSItemKevlar: public CCSItem {};
class CCSItemAssaultSuit: public CCSItem {};
class CCSItemThighPack: public CCSItem {};
class CCSGrenCatch: public CCSEntity {};
class CCSFuncWeaponCheck: public CCSEntity {};
class CCSHostage: public CCSMonster {};
class CCSLight: public CCSPointEntity {};
class CCSEnvLight: public CCSLight {};
class CCSRuleEntity: public CCSEntity {};
class CCSRulePointEntity: public CCSRuleEntity {};
class CCSRuleBrushEntity: public CCSRuleEntity {};
class CCSGameScore: public CCSRulePointEntity {};
class CCSGameEnd: public CCSRulePointEntity {};
class CCSGameText: public CCSRulePointEntity {};
class CCSGameTeamMaster: public CCSRulePointEntity {};
class CCSGameTeamSet: public CCSRulePointEntity {};
class CCSGamePlayerZone: public CCSRuleBrushEntity {};
class CCSGamePlayerHurt: public CCSRulePointEntity {};
class CCSGameCounter: public CCSRulePointEntity {};
class CCSGameCounterSet: public CCSRulePointEntity {};
class CCSGamePlayerEquip: public CCSRulePointEntity {};
class CCSGamePlayerTeam: public CCSRulePointEntity {};
class CCSFuncMortarField: public CCSToggle {};
class CCSMortar: public CCSGrenade {};
class CCSMapInfo: public CCSPointEntity {};
class CCSPathCorner: public CCSPointEntity {};
class CCSPathTrack: public CCSPointEntity {};
class CCSFuncTrackTrain: public CCSEntity {};
class CCSFuncVehicleControls: public CCSEntity {};
class CCSFuncVehicle: public CCSEntity {};
class CCSPlatTrain: public CCSToggle {};
class CCSFuncPlat: public CCSPlatTrain {};
class CCSPlatTrigger: public CCSEntity {};
class CCSFuncPlatRot: public CCSFuncPlat {};
class CCSFuncTrain: public CCSPlatTrain {};
class CCSFuncTrainControls: public CCSEntity {};
class CCSFuncTrackChange: public CCSFuncPlatRot {};
class CCSFuncTrackAuto: public CCSFuncTrackChange {};
class CCSGunTarget: public CCSMonster {};
class CCSAmbientGeneric: public CCSEntity {};
class CCSEnvSound: public CCSPointEntity {};
class CCSSpeaker: public CCSEntity {};
class CCSSoundEnt: public CCSEntity {};
class CCSUSP: public CCSPlayerWeapon {};
class CCSMP5N: public CCSPlayerWeapon {};
class CCSSG552: public CCSPlayerWeapon {};
class CCSAK47: public CCSPlayerWeapon {};
class CCSAUG: public CCSPlayerWeapon {};
class CCSAWP: public CCSPlayerWeapon {};
class CCSC4: public CCSPlayerWeapon {};
class CCSDEAGLE: public CCSPlayerWeapon {};
class CCSFlashbang: public CCSPlayerWeapon {};
class CCSG3SG1: public CCSPlayerWeapon {};
class CCSGLOCK18: public CCSPlayerWeapon {};
class CCSHEGrenade: public CCSPlayerWeapon {};
class CCSKnife: public CCSPlayerWeapon {};
class CCSM249: public CCSPlayerWeapon {};
class CCSM3: public CCSPlayerWeapon {};
class CCSM4A1: public CCSPlayerWeapon {};
class CCSMAC10: public CCSPlayerWeapon {};
class CCSP228: public CCSPlayerWeapon {};
class CCSP90: public CCSPlayerWeapon {};
class CCSSCOUT: public CCSPlayerWeapon {};
class CCSSmokeGrenade: public CCSPlayerWeapon {};
class CCSTMP: public CCSPlayerWeapon {};
class CCSXM1014: public CCSPlayerWeapon {};
class CCSELITE: public CCSPlayerWeapon {};
class CCSFiveSeven: public CCSPlayerWeapon {};
class CCSUMP45: public CCSPlayerWeapon {};
class CCSSG550: public CCSPlayerWeapon {};
class CCSGalil: public CCSPlayerWeapon {};
class CCSFamas: public CCSPlayerWeapon {};
class CCSNullEntity: public CCSEntity {};
class CCSDMStart: public CCSPointEntity {};
class CCSFrictionModifier: public CCSEntity {};
class CCSAutoTrigger: public CCSDelay {};
class CCSTriggerRelay: public CCSDelay {};
class CCSMultiManager: public CCSToggle {};
class CCSRenderFxManager: public CCSEntity {};
class CCSTrigger: public CCSToggle {};
class CCSTriggerHurt: public CCSTrigger {};
class CCSTriggerMonsterJump: public CCSTrigger {};
class CCSTriggerCDAudio: public CCSTrigger {};
class CCSTargetCDAudio: public CCSPointEntity {};
class CCSTriggerMultiple: public CCSTrigger {};
class CCSTriggerOnce: public CCSTriggerMultiple {};
class CCSTriggerCounter: public CCSTrigger {};
class CCSTriggerVolume: public CCSPointEntity {};
class CCSFireAndDie: public CCSDelay {};
class CCSChangeLevel: public CCSTrigger {};
class CCSLadder: public CCSTrigger {};
class CCSTriggerPush: public CCSTrigger {};
class CCSTriggerTeleport: public CCSTrigger {};
class CCSBuyZone: public CCSTrigger {};
class CCSBombTarget: public CCSTrigger {};
class CCSHostageRescue: public CCSTrigger {};
class CCSEscapeZone: public CCSTrigger {};
class CCSVIP_SafetyZone: public CCSTrigger {};
class CCSTriggerSave: public CCSTrigger {};
class CCSTriggerEndSection: public CCSTrigger {};
class CCSTriggerGravity: public CCSTrigger {};
class CCSTriggerChangeTarget: public CCSDelay {};
class CCSTriggerCamera: public CCSDelay {};
class CCSWeather: public CCSTrigger {};
class CCSClientFog: public CCSEntity {};

inline CBasePlayer *CCSPlayer::BasePlayer() const {
	return reinterpret_cast<CBasePlayer *>(this->m_pContainingEntity);
}
