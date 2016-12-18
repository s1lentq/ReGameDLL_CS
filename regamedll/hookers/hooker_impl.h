/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef HOOKER_IMPL_H
#define HOOKER_IMPL_H
#ifdef _WIN32
#pragma once
#endif

#include "studio.h"
#include "game_shared/voice_common.h"

class CBaseEntity;
class CBaseMonster;
class CBasePlayer;
class CGrenade;

class CBot;
class CCSBot;
class CCSBotManager;
class BotStatement;
class BotPhrase;
class CSGameState;

class CImprov;
class CNavArea;
class HidingSpot;
class CNavNode;
class PathCost;
class ShortestPathCost;
class HostagePathCost;
class CHostageImprov;
class CLocalNav;
class HostageAnimateState;

class CSave;
class CGraph;
class CRestore;
class CSaveRestoreBuffer;

typedef Vector VectorRef;
typedef float FloatRef;

#define __API_HOOK(fname)\
	fname

#define __API_VHOOK(fname)\
	fname##_

#define __MAKE_VHOOK(fname)\
	fname##_

#define IMPL(var)\
	(*p##var)

#define IMPL_CLASS(baseClass,var)\
	(*baseClass::p##var)

#define LINK_HOOK_CLASS_VOID_CHAIN(...)
#define LINK_HOOK_CLASS_VOID_CHAIN2(...)
#define LINK_HOOK_CLASS_CHAIN(...)
#define LINK_HOOK_CLASS_CHAIN2(...)
#define LINK_HOOK_CLASS_VOID_CUSTOM_CHAIN(...)
#define LINK_HOOK_CLASS_VOID_CUSTOM_CHAIN2(...)
#define LINK_HOOK_CLASS_CUSTOM_CHAIN(...)
#define LINK_HOOK_CLASS_CUSTOM_CHAIN2(...)
#define LINK_HOOK_VOID_CHAIN(...)
#define LINK_HOOK_CHAIN(...)
#define LINK_HOOK_CHAIN2(...)

// refs
extern void (CBaseEntity::*pCHostage__IdleThink)();
extern void (*pBotPhrase__Randomize)();
extern void (*pCCSBotManager__AddBot)();
extern void (*pCCSBot__UpdateLookAngles)();

// globals export
#define g_engfuncs (*pg_engfuncs)
#define gpGlobals (*pgpGlobals)

// globals cbase
#define stringsHashTable (*pstringsHashTable)
#define hashItemMemPool (*phashItemMemPool)
#define gTouchDisabled (*pgTouchDisabled)
#define gFunctionTable (*pgFunctionTable)
#define gNewDLLFunctions (*pgNewDLLFunctions)
#define grgszTextureName (*pgrgszTextureName)
#define grgchTextureType (*pgrgchTextureType)
#define fTextureTypeInit (*pfTextureTypeInit)
#define gcTextures (*pgcTextures)

// globals player
#define m_szPoses (*pm_szPoses)
#define g_weaponStruct (*pg_weaponStruct)
#define gEvilImpulse101 (*pgEvilImpulse101)
#define g_szMapBriefingText (*pg_szMapBriefingText)
#define g_pevLastInflictor (*pg_pevLastInflictor)
#define g_pLastSpawn (*pg_pLastSpawn)
#define g_pLastCTSpawn (*pg_pLastCTSpawn)
#define g_pLastTerroristSpawn (*pg_pLastTerroristSpawn)
#define gInitHUD (*pgInitHUD)
#define sv_aim (*psv_aim)
#define zombieSpawnCount (*pzombieSpawnCount)
#define zombieSpawn (*pzombieSpawn)
#define g_pSelectedZombieSpawn (*pg_pSelectedZombieSpawn)
#define giPrecacheGrunt (*pgiPrecacheGrunt)
#define gmsgWeapPickup (*pgmsgWeapPickup)
#define gmsgHudText (*pgmsgHudText)
#define gmsgHudTextArgs (*pgmsgHudTextArgs)
#define gmsgShake (*pgmsgShake)
#define gmsgFade (*pgmsgFade)
#define gmsgFlashlight (*pgmsgFlashlight)
#define gmsgFlashBattery (*pgmsgFlashBattery)
#define gmsgResetHUD (*pgmsgResetHUD)
#define gmsgInitHUD (*pgmsgInitHUD)
#define gmsgViewMode (*pgmsgViewMode)
#define gmsgShowGameTitle (*pgmsgShowGameTitle)
#define gmsgCurWeapon (*pgmsgCurWeapon)
#define gmsgHealth (*pgmsgHealth)
#define gmsgDamage (*pgmsgDamage)
#define gmsgBattery (*pgmsgBattery)
#define gmsgTrain (*pgmsgTrain)
#define gmsgLogo (*pgmsgLogo)
#define gmsgWeaponList (*pgmsgWeaponList)
#define gmsgAmmoX (*pgmsgAmmoX)
#define gmsgDeathMsg (*pgmsgDeathMsg)
#define gmsgScoreAttrib (*pgmsgScoreAttrib)
#define gmsgScoreInfo (*pgmsgScoreInfo)
#define gmsgTeamInfo (*pgmsgTeamInfo)
#define gmsgTeamScore (*pgmsgTeamScore)
#define gmsgGameMode (*pgmsgGameMode)
#define gmsgMOTD (*pgmsgMOTD)
#define gmsgServerName (*pgmsgServerName)
#define gmsgAmmoPickup (*pgmsgAmmoPickup)
#define gmsgItemPickup (*pgmsgItemPickup)
#define gmsgHideWeapon (*pgmsgHideWeapon)
#define gmsgSayText (*pgmsgSayText)
#define gmsgTextMsg (*pgmsgTextMsg)
#define gmsgSetFOV (*pgmsgSetFOV)
#define gmsgShowMenu (*pgmsgShowMenu)
#define gmsgSendAudio (*pgmsgSendAudio)
#define gmsgRoundTime (*pgmsgRoundTime)
#define gmsgMoney (*pgmsgMoney)
#define gmsgBlinkAcct (*pgmsgBlinkAcct)
#define gmsgArmorType (*pgmsgArmorType)
#define gmsgStatusValue (*pgmsgStatusValue)
#define gmsgStatusText (*pgmsgStatusText)
#define gmsgStatusIcon (*pgmsgStatusIcon)
#define gmsgBarTime (*pgmsgBarTime)
#define gmsgReloadSound (*pgmsgReloadSound)
#define gmsgCrosshair (*pgmsgCrosshair)
#define gmsgNVGToggle (*pgmsgNVGToggle)
#define gmsgRadar (*pgmsgRadar)
#define gmsgSpectator (*pgmsgSpectator)
#define gmsgVGUIMenu (*pgmsgVGUIMenu)
#define gmsgCZCareer (*pgmsgCZCareer)
#define gmsgCZCareerHUD (*pgmsgCZCareerHUD)
#define gmsgTaskTime (*pgmsgTaskTime)
#define gmsgTutorText (*pgmsgTutorText)
#define gmsgTutorLine (*pgmsgTutorLine)
#define gmsgShadowIdx (*pgmsgShadowIdx)
#define gmsgTutorState (*pgmsgTutorState)
#define gmsgTutorClose (*pgmsgTutorClose)
#define gmsgAllowSpec (*pgmsgAllowSpec)
#define gmsgBombDrop (*pgmsgBombDrop)
#define gmsgBombPickup (*pgmsgBombPickup)
#define gmsgHostagePos (*pgmsgHostagePos)
#define gmsgHostageK (*pgmsgHostageK)
#define gmsgGeigerRange (*pgmsgGeigerRange)
#define gmsgSendCorpse (*pgmsgSendCorpse)
#define gmsgHLTV (*pgmsgHLTV)
#define gmsgSpecHealth (*pgmsgSpecHealth)
#define gmsgForceCam (*pgmsgForceCam)
#define gmsgADStop (*pgmsgADStop)
#define gmsgReceiveW (*pgmsgReceiveW)
#define gmsgScenarioIcon (*pgmsgScenarioIcon)
#define gmsgBotVoice (*pgmsgBotVoice)
#define gmsgBuyClose (*pgmsgBuyClose)
#define gmsgItemStatus (*pgmsgItemStatus)
#define gmsgLocation (*pgmsgLocation)
#define gmsgSpecHealth2 (*pgmsgSpecHealth2)
#define gmsgBarTime2 (*pgmsgBarTime2)
#define gmsgBotProgress (*pgmsgBotProgress)
#define gmsgBrass (*pgmsgBrass)
#define gmsgFog (*pgmsgFog)
#define gmsgShowTimer (*pgmsgShowTimer)

// globals skill
#define gSkillData (*pgSkillData)

// globals career
#define TheCareerTasks (*pTheCareerTasks)
#define taskInfo (*ptaskInfo)

// globals triggers
#define st_szNextMap (*pst_szNextMap)
#define st_szNextSpot (*pst_szNextSpot)

// globals animation
#define svBlending (*psvBlending)
#define IEngineStudio (*pIEngineStudio)
#define g_pstudiohdr (*pg_pstudiohdr)
#define g_pRotationMatrix (*pg_pRotationMatrix)
#define g_pBoneTransform (*pg_pBoneTransform)

// globals sound
#define gszallsentencenames (*pgszallsentencenames)
#define rgsentenceg (*prgsentenceg)
#define fSentencesInit (*pfSentencesInit)
#define gcallsentences (*pgcallsentences)
#define rgdpvpreset (*prgdpvpreset)

// globals world
#define gDecals (*pgDecals)

// globals client
#define g_flTimeLimit (*pg_flTimeLimit)
#define g_flResetTime (*pg_flResetTime)
#define g_bClientPrintEnable (*pg_bClientPrintEnable)
#define g_PVSStatus (*pg_PVSStatus)
#define m_usResetDecals (*pm_usResetDecals)
#define g_iShadowSprite (*pg_iShadowSprite)
#define sPlayerModelFiles (*psPlayerModelFiles)
#define g_skipCareerInitialSpawn (*pg_skipCareerInitialSpawn)
#define entity_field_alias (*pentity_field_alias)
#define player_field_alias (*pplayer_field_alias)
#define custom_entity_field_alias (*pcustom_entity_field_alias)
#define g_serveractive (*pg_serveractive)

// globals debug
#define outputLevel (*poutputLevel)
#define theDebugOutputTypes (*ptheDebugOutputTypes)
#define theDebugBuffer (*ptheDebugBuffer)

// globals func_break
#define pSoundsWood (*ppSoundsWood)
#define pSoundsFlesh (*ppSoundsFlesh)
#define pSoundsGlass (*ppSoundsGlass)
#define pSoundsMetal (*ppSoundsMetal)
#define pSoundsConcrete (*ppSoundsConcrete)
#define pSpawnObjects (*ppSpawnObjects)
#define m_soundNames (*pm_soundNames)

// globals func_tank
#define gTankSpread (*pgTankSpread)

// globals game
#define g_psv_gravity (*pg_psv_gravity)
#define g_psv_aim (*pg_psv_aim)
#define g_footsteps (*pg_footsteps)
#define g_psv_accelerate (*pg_psv_accelerate)
#define g_psv_friction (*pg_psv_friction)
#define g_psv_stopspeed (*pg_psv_stopspeed)
#define displaysoundlist (*pdisplaysoundlist)
#define timelimit (*ptimelimit)
#define flashlight (*pflashlight)
#define decalfrequency (*pdecalfrequency)
#define fadetoblack (*pfadetoblack)
#define fragsleft (*pfragsleft)
#define timeleft (*ptimeleft)
#define friendlyfire (*pfriendlyfire)
#define allowmonsters (*pallowmonsters)
#define roundtime (*proundtime)
#define buytime (*pbuytime)
#define freezetime (*pfreezetime)
#define c4timer (*pc4timer)
#define ghostfrequency (*pghostfrequency)
#define autokick (*pautokick)
#define autokick_timeout (*pautokick_timeout)
#define restartround (*prestartround)
#define sv_restart (*psv_restart)
#define limitteams (*plimitteams)
#define autoteambalance (*pautoteambalance)
#define tkpunish (*ptkpunish)
#define hostagepenalty (*phostagepenalty)
#define mirrordamage (*pmirrordamage)
#define logmessages (*plogmessages)
#define forcecamera (*pforcecamera)
#define forcechasecam (*pforcechasecam)
#define mapvoteratio (*pmapvoteratio)
#define logdetail (*plogdetail)
#define startmoney (*pstartmoney)
#define maxrounds (*pmaxrounds)
#define winlimit (*pwinlimit)
#define windifference (*pwindifference)
#define playerid (*pplayerid)
#define allow_spectators (*pallow_spectators)
#define mp_chattime (*pmp_chattime)
#define kick_percent (*pkick_percent)
#define humans_join_team (*phumans_join_team)
#define sk_plr_9mm_bullet1 (*psk_plr_9mm_bullet1)
#define sk_plr_9mm_bullet2 (*psk_plr_9mm_bullet2)
#define sk_plr_9mm_bullet3 (*psk_plr_9mm_bullet3)
#define sk_plr_357_bullet1 (*psk_plr_357_bullet1)
#define sk_plr_357_bullet2 (*psk_plr_357_bullet2)
#define sk_plr_357_bullet3 (*psk_plr_357_bullet3)
#define sk_plr_9mmAR_bullet1 (*psk_plr_9mmAR_bullet1)
#define sk_plr_9mmAR_bullet2 (*psk_plr_9mmAR_bullet2)
#define sk_plr_9mmAR_bullet3 (*psk_plr_9mmAR_bullet3)
#define sk_plr_9mmAR_grenade1 (*psk_plr_9mmAR_grenade1)
#define sk_plr_9mmAR_grenade2 (*psk_plr_9mmAR_grenade2)
#define sk_plr_9mmAR_grenade3 (*psk_plr_9mmAR_grenade3)
#define sk_plr_buckshot1 (*psk_plr_buckshot1)
#define sk_plr_buckshot2 (*psk_plr_buckshot2)
#define sk_plr_buckshot3 (*psk_plr_buckshot3)
#define sk_plr_rpg1 (*psk_plr_rpg1)
#define sk_plr_rpg2 (*psk_plr_rpg2)
#define sk_plr_rpg3 (*psk_plr_rpg3)
#define sk_12mm_bullet1 (*psk_12mm_bullet1)
#define sk_12mm_bullet2 (*psk_12mm_bullet2)
#define sk_12mm_bullet3 (*psk_12mm_bullet3)
#define sk_9mmAR_bullet1 (*psk_9mmAR_bullet1)
#define sk_9mmAR_bullet2 (*psk_9mmAR_bullet2)
#define sk_9mmAR_bullet3 (*psk_9mmAR_bullet3)
#define sk_9mm_bullet1 (*psk_9mm_bullet1)
#define sk_9mm_bullet2 (*psk_9mm_bullet2)
#define sk_9mm_bullet3 (*psk_9mm_bullet3)
#define sk_suitcharger1 (*psk_suitcharger1)
#define sk_suitcharger2 (*psk_suitcharger2)
#define sk_suitcharger3 (*psk_suitcharger3)
#define sk_battery1 (*psk_battery1)
#define sk_battery2 (*psk_battery2)
#define sk_battery3 (*psk_battery3)
#define sk_healthcharger1 (*psk_healthcharger1)
#define sk_healthcharger2 (*psk_healthcharger2)
#define sk_healthcharger3 (*psk_healthcharger3)
#define sk_healthkit1 (*psk_healthkit1)
#define sk_healthkit2 (*psk_healthkit2)
#define sk_healthkit3 (*psk_healthkit3)
#define sk_scientist_heal1 (*psk_scientist_heal1)
#define sk_scientist_heal2 (*psk_scientist_heal2)
#define sk_scientist_heal3 (*psk_scientist_heal3)

// globals gamerules
#define g_pGameRules (*pg_pGameRules)
#define g_GameMgrHelper (*pg_GameMgrHelper)
#define sv_clienttrace (*psv_clienttrace)
#define g_pMPGameRules (*pg_pMPGameRules)
#define mp_com_token (*pmp_com_token)

// globals soundent
#define pSoundEnt (*ppSoundEnt)

// globals weapons
#define g_sModelIndexLaser (*pg_sModelIndexLaser)
#define g_pModelNameLaser (*pg_pModelNameLaser)
#define g_sModelIndexLaserDot (*pg_sModelIndexLaserDot)
#define g_sModelIndexFireball (*pg_sModelIndexFireball)
#define g_sModelIndexSmoke (*pg_sModelIndexSmoke)
#define g_sModelIndexWExplosion (*pg_sModelIndexWExplosion)
#define g_sModelIndexBubbles (*pg_sModelIndexBubbles)
#define g_sModelIndexBloodDrop (*pg_sModelIndexBloodDrop)
#define g_sModelIndexBloodSpray (*pg_sModelIndexBloodSpray)
#define g_sModelIndexSmokePuff (*pg_sModelIndexSmokePuff)
#define g_sModelIndexFireball2 (*pg_sModelIndexFireball2)
#define g_sModelIndexFireball3 (*pg_sModelIndexFireball3)
#define g_sModelIndexFireball4 (*pg_sModelIndexFireball4)
#define g_sModelIndexCTGhost (*pg_sModelIndexCTGhost)
#define g_sModelIndexTGhost (*pg_sModelIndexTGhost)
#define g_sModelIndexC4Glow (*pg_sModelIndexC4Glow)
#define giAmmoIndex (*pgiAmmoIndex)
#define g_sModelIndexRadio (*pg_sModelIndexRadio)
#define gMultiDamage (*pgMultiDamage)

// globals weapontype
#define g_autoBuyInfo (*pg_autoBuyInfo)
#define weaponAliasInfo (*pweaponAliasInfo)
#define weaponBuyAliasInfo (*pweaponBuyAliasInfo)
#define weaponClassAliasInfo (*pweaponClassAliasInfo)
#define weaponInfo (*pweaponInfo)

// globals wolrd
#define g_pBodyQueueHead (*pg_pBodyQueueHead)
#define gGlobalState (*pgGlobalState)
#define g_flWeaponCheat (*pg_flWeaponCheat)
#define gGlobalEntitySaveData (*pgGlobalEntitySaveData)

// globals globals
#define g_vecZero (*pg_vecZero)
#define g_Language (*pg_Language)

#define g_ulFrameCount (*pg_ulFrameCount)
#define g_ulModelIndexEyes (*pg_ulModelIndexEyes)

#define g_vecAttackDir (*pg_vecAttackDir)
#define g_iSkillLevel (*pg_iSkillLevel)
#define gDisplayTitle (*pgDisplayTitle)
#define g_fGameOver (*pg_fGameOver)

#define WorldGraph (*pWorldGraph)

// hostages
#define g_pHostages (*pg_pHostages)
#define g_iHostageNumber (*pg_iHostageNumber)

#define cv_hostage_debug (*pcv_hostage_debug)
#define cv_hostage_stop (*pcv_hostage_stop)
#define s_flStepSize_LocalNav (*m_LocalNav->ps_flStepSize)

#define flNextCvarCheck (*pflNextCvarCheck)
#define s_flStepSize (*ps_flStepSize)
#define flLastThinkTime (*pflLastThinkTime)
#define nodeval (*pnodeval)
#define tot_hostages (*ptot_hostages)
#define tot_inqueue (*ptot_inqueue)
#define qptr (*pqptr)
#define _queue (*pqueue)
#define hostages (*phostages)

// utils
#define gEntvarsDescription (*pgEntvarsDescription)
#define seed_table (*pseed_table)
#define glSeed (*pglSeed)
#define g_groupmask (*pg_groupmask)
#define g_groupop (*pg_groupop)
#define gSizes (*pgSizes)

// tutor
#define TheTutor (*pTheTutor)
#define g_TutorStateStrings (*pg_TutorStateStrings)
#define TutorIdentifierList (*pTutorIdentifierList)

#define s_tutorDisabledThisGame (*ps_tutorDisabledThisGame)
#define s_nextCvarCheckTime (*ps_nextCvarCheckTime)

#define cv_tutor_message_repeats (*pcv_tutor_message_repeats)
#define cv_tutor_debug_level (*pcv_tutor_debug_level)
#define cv_tutor_view_distance (*pcv_tutor_view_distance)
#define cv_tutor_viewable_check_interval (*pcv_tutor_viewable_check_interval)
#define cv_tutor_look_distance (*pcv_tutor_look_distance)
#define cv_tutor_look_angle (*pcv_tutor_look_angle)
#define cv_tutor_examine_time (*pcv_tutor_examine_time)
#define cv_tutor_message_minimum_display_time (*pcv_tutor_message_minimum_display_time)
#define cv_tutor_message_character_display_time_coefficient (*pcv_tutor_message_character_display_time_coefficient)
#define cv_tutor_hint_interval_time (*pcv_tutor_hint_interval_time)

// bots
#define _navAreaCount (*pnavAreaCount)
#define _currentIndex (*pcurrentIndex)
#define primaryWeaponBuyInfoCT (*pprimaryWeaponBuyInfoCT)
#define secondaryWeaponBuyInfoCT (*psecondaryWeaponBuyInfoCT)
#define primaryWeaponBuyInfoT (*pprimaryWeaponBuyInfoT)
#define secondaryWeaponBuyInfoT (*psecondaryWeaponBuyInfoT)
#define TheBotPhrases (*pTheBotPhrases)
#define g_pSelectedZombieSpawn (*pg_pSelectedZombieSpawn)
#define TheBots (*pTheBots)

// bot_util
#define s_iBeamSprite (*ps_iBeamSprite)
#define cosTable (*pcosTable)

#define cv_bot_traceview (*pcv_bot_traceview)
#define cv_bot_stop (*pcv_bot_stop)
#define cv_bot_show_nav (*pcv_bot_show_nav)
#define cv_bot_show_danger (*pcv_bot_show_danger)
#define cv_bot_nav_edit (*pcv_bot_nav_edit)
#define cv_bot_nav_zdraw (*pcv_bot_nav_zdraw)
#define cv_bot_walk (*pcv_bot_walk)
#define cv_bot_difficulty (*pcv_bot_difficulty)
#define cv_bot_debug (*pcv_bot_debug)
#define cv_bot_quicksave (*pcv_bot_quicksave)
#define cv_bot_quota (*pcv_bot_quota)
#define cv_bot_quota_match (*pcv_bot_quota_match)
#define cv_bot_prefix (*pcv_bot_prefix)
#define cv_bot_allow_rogues (*pcv_bot_allow_rogues)
#define cv_bot_allow_pistols (*pcv_bot_allow_pistols)
#define cv_bot_allow_shotguns (*pcv_bot_allow_shotguns)
#define cv_bot_allow_sub_machine_guns (*pcv_bot_allow_sub_machine_guns)
#define cv_bot_allow_rifles (*pcv_bot_allow_rifles)
#define cv_bot_allow_machine_guns (*pcv_bot_allow_machine_guns)
#define cv_bot_allow_grenades (*pcv_bot_allow_grenades)
#define cv_bot_allow_snipers (*pcv_bot_allow_snipers)
#define cv_bot_allow_shield (*pcv_bot_allow_shield)
#define cv_bot_join_team (*pcv_bot_join_team)
#define cv_bot_join_after_player (*pcv_bot_join_after_player)
#define cv_bot_auto_vacate (*pcv_bot_auto_vacate)
#define cv_bot_zombie (*pcv_bot_zombie)
#define cv_bot_defer_to_human (*pcv_bot_defer_to_human)
#define cv_bot_chatter (*pcv_bot_chatter)
#define cv_bot_profile_db (*pcv_bot_profile_db)

// shared_util
#define s_shared_token (*ps_shared_token)
#define s_shared_quote (*ps_shared_quote)

// bot util
#define GameEventName (*pGameEventName)

// voice_gamemgr
#define voice_serverdebug (*pvoice_serverdebug)
#define sv_alltalk (*psv_alltalk)

#define g_PlayerModEnable (*pg_PlayerModEnable)
#define g_BanMasks (*pg_BanMasks)
#define g_SentGameRulesMasks (*pg_SentGameRulesMasks)
#define g_SentBanMasks (*pg_SentBanMasks)
#define g_bWantModEnable (*pg_bWantModEnable)

// bot
#define g_flBotCommandInterval (*pg_flBotCommandInterval)
#define g_flBotFullThinkInterval (*pg_flBotFullThinkInterval)
#define BotArgs (*pBotArgs)
#define UseBotArgs (*pUseBotArgs)
#define BotDifficultyName (*pBotDifficultyName)

// utlsymbol
#define g_LessCtx (*pg_LessCtx)

// bot_profile
#define TheBotProfiles (*pTheBotProfiles)

// nav_area
#define TheNavLadderList (*pTheNavLadderList)
#define TheHidingSpotList (*pTheHidingSpotList)
#define TheNavAreaList (*pTheNavAreaList)
#define TheNavAreaGrid (*pTheNavAreaGrid)
#define lastDrawTimestamp (*plastDrawTimestamp)
#define goodSizedAreaList (*pgoodSizedAreaList)
#define markedArea (*pmarkedArea)
#define lastSelectedArea (*plastSelectedArea)
#define markedCorner (*pmarkedCorner)
#define isCreatingNavArea (*pisCreatingNavArea)
#define isAnchored (*pisAnchored)
#define anchor (*panchor)
#define isPlaceMode (*pisPlaceMode)
#define isPlacePainting (*pisPlacePainting)
#define editTimestamp (*peditTimestamp)
#define BlockedID (*pBlockedID)
#define BlockedIDCount (*pBlockedIDCount)

// nav_node
#define Opposite (*pOpposite)

// pm_shared
#define pmove (*pg_ppmove)
#define pm_shared_initialized (*ppm_shared_initialized)
#define rgv3tStuckTable (*prgv3tStuckTable)
#define pm_gcTextures (*ppm_gcTextures)
#define pm_grgszTextureName (*ppm_grgszTextureName)
#define pm_grgchTextureType (*ppm_grgchTextureType)
#define rgStuckLast (*prgStuckLast)
#define g_onladder (*pg_onladder)

// pm_math
#define vec3_origin (*pvec3_origin)
#define nanmask (*pnanmask)

// linked objects 196
C_DLLEXPORT void ammo_9mm(entvars_t *pev);
C_DLLEXPORT void ammo_buckshot(entvars_t *pev);
C_DLLEXPORT void ammo_556nato(entvars_t *pev);
C_DLLEXPORT void ammo_556natobox(entvars_t *pev);
C_DLLEXPORT void ammo_762nato(entvars_t *pev);
C_DLLEXPORT void ammo_45acp(entvars_t *pev);
C_DLLEXPORT void ammo_50ae(entvars_t *pev);
C_DLLEXPORT void ammo_338magnum(entvars_t *pev);
C_DLLEXPORT void ammo_57mm(entvars_t *pev);
C_DLLEXPORT void ammo_357sig(entvars_t *pev);
C_DLLEXPORT void func_wall(entvars_t *pev);
C_DLLEXPORT void func_wall_toggle(entvars_t *pev);
C_DLLEXPORT void func_conveyor(entvars_t *pev);
C_DLLEXPORT void func_illusionary(entvars_t *pev);
C_DLLEXPORT void func_monsterclip(entvars_t *pev);
C_DLLEXPORT void func_rotating(entvars_t *pev);
C_DLLEXPORT void func_pendulum(entvars_t *pev);
C_DLLEXPORT void func_button(entvars_t *pev);
C_DLLEXPORT void func_rot_button(entvars_t *pev);
C_DLLEXPORT void func_door(entvars_t *pev);
C_DLLEXPORT void func_water(entvars_t *pev);
C_DLLEXPORT void func_door_rotating(entvars_t *pev);
C_DLLEXPORT void func_breakable(entvars_t *pev);
C_DLLEXPORT void func_pushable(entvars_t *pev);
C_DLLEXPORT void func_tank(entvars_t *pev);
C_DLLEXPORT void func_tanklaser(entvars_t *pev);
C_DLLEXPORT void func_tankrocket(entvars_t *pev);
C_DLLEXPORT void func_tankmortar(entvars_t *pev);
C_DLLEXPORT void func_tankcontrols(entvars_t *pev);
C_DLLEXPORT void func_recharge(entvars_t *pev);
C_DLLEXPORT void func_healthcharger(entvars_t *pev);
C_DLLEXPORT void func_mortar_field(entvars_t *pev);
C_DLLEXPORT void func_plat(entvars_t *pev);
C_DLLEXPORT void func_platrot(entvars_t *pev);
C_DLLEXPORT void func_train(entvars_t *pev);
C_DLLEXPORT void func_tracktrain(entvars_t *pev);
C_DLLEXPORT void func_traincontrols(entvars_t *pev);
C_DLLEXPORT void func_trackchange(entvars_t *pev);
C_DLLEXPORT void func_trackautochange(entvars_t *pev);
C_DLLEXPORT void func_guntarget(entvars_t *pev);
C_DLLEXPORT void func_grencatch(entvars_t *pev);
C_DLLEXPORT void func_weaponcheck(entvars_t *pev);
C_DLLEXPORT void func_friction(entvars_t *pev);
C_DLLEXPORT void func_ladder(entvars_t *pev);
C_DLLEXPORT void func_buyzone(entvars_t *pev);
C_DLLEXPORT void func_bomb_target(entvars_t *pev);
C_DLLEXPORT void func_hostage_rescue(entvars_t *pev);
C_DLLEXPORT void func_escapezone(entvars_t *pev);
C_DLLEXPORT void func_vip_safetyzone(entvars_t *pev);
C_DLLEXPORT void func_snow(entvars_t *pev);
C_DLLEXPORT void func_rain(entvars_t *pev);
C_DLLEXPORT void func_vehicle(entvars_t *pev);
C_DLLEXPORT void func_vehiclecontrols(entvars_t *pev);
C_DLLEXPORT void env_sound(entvars_t *pev);
C_DLLEXPORT void env_global(entvars_t *pev);
C_DLLEXPORT void env_spark(entvars_t *pev);
C_DLLEXPORT void env_debris(entvars_t *pev);
C_DLLEXPORT void env_bubbles(entvars_t *pev);
C_DLLEXPORT void env_lightning(entvars_t *pev);
C_DLLEXPORT void env_beam(entvars_t *pev);
C_DLLEXPORT void env_laser(entvars_t *pev);
C_DLLEXPORT void env_glow(entvars_t *pev);
C_DLLEXPORT void env_bombglow(entvars_t *pev);
C_DLLEXPORT void env_sprite(entvars_t *pev);
C_DLLEXPORT void env_shooter(entvars_t *pev);
C_DLLEXPORT void env_blood(entvars_t *pev);
C_DLLEXPORT void env_shake(entvars_t *pev);
C_DLLEXPORT void env_fade(entvars_t *pev);
C_DLLEXPORT void env_message(entvars_t *pev);
C_DLLEXPORT void env_funnel(entvars_t *pev);
C_DLLEXPORT void env_beverage(entvars_t *pev);
C_DLLEXPORT void env_explosion(entvars_t *pev);
C_DLLEXPORT void env_render(entvars_t *pev);
C_DLLEXPORT void env_snow(entvars_t *pev);
C_DLLEXPORT void env_rain(entvars_t *pev);
C_DLLEXPORT void env_fog(entvars_t *pev);
C_DLLEXPORT void weapon_knife(entvars_t *pev);
C_DLLEXPORT void weapon_glock18(entvars_t *pev);
C_DLLEXPORT void weapon_c4(entvars_t *pev);
C_DLLEXPORT void weapon_usp(entvars_t *pev);
C_DLLEXPORT void weapon_smokegrenade(entvars_t *pev);
C_DLLEXPORT void weapon_m4a1(entvars_t *pev);
C_DLLEXPORT void weapon_hegrenade(entvars_t *pev);
C_DLLEXPORT void weapon_flashbang(entvars_t *pev);
C_DLLEXPORT void weapon_famas(entvars_t *pev);
C_DLLEXPORT void weapon_elite(entvars_t *pev);
C_DLLEXPORT void weapon_fiveseven(entvars_t *pev);
C_DLLEXPORT void weapon_p228(entvars_t *pev);
C_DLLEXPORT void weapon_xm1014(entvars_t *pev);
C_DLLEXPORT void weapon_g3sg1(entvars_t *pev);
C_DLLEXPORT void weapon_sg550(entvars_t *pev);
C_DLLEXPORT void weapon_deagle(entvars_t *pev);
C_DLLEXPORT void weapon_awp(entvars_t *pev);
C_DLLEXPORT void weapon_scout(entvars_t *pev);
C_DLLEXPORT void weapon_sg552(entvars_t *pev);
C_DLLEXPORT void weapon_m3(entvars_t *pev);
C_DLLEXPORT void weapon_aug(entvars_t *pev);
C_DLLEXPORT void weapon_galil(entvars_t *pev);
C_DLLEXPORT void weapon_ak47(entvars_t *pev);
C_DLLEXPORT void weapon_m249(entvars_t *pev);
C_DLLEXPORT void weapon_p90(entvars_t *pev);
C_DLLEXPORT void weapon_mac10(entvars_t *pev);
C_DLLEXPORT void weapon_ump45(entvars_t *pev);
C_DLLEXPORT void weapon_mp5navy(entvars_t *pev);
C_DLLEXPORT void weapon_tmp(entvars_t *pev);
C_DLLEXPORT void weapon_shield(entvars_t *pev);
C_DLLEXPORT void trigger(entvars_t *pev);
C_DLLEXPORT void trigger_auto(entvars_t *pev);
C_DLLEXPORT void trigger_relay(entvars_t *pev);
C_DLLEXPORT void trigger_hurt(entvars_t *pev);
C_DLLEXPORT void trigger_monsterjump(entvars_t *pev);
C_DLLEXPORT void trigger_cdaudio(entvars_t *pev);
C_DLLEXPORT void trigger_multiple(entvars_t *pev);
C_DLLEXPORT void trigger_once(entvars_t *pev);
C_DLLEXPORT void trigger_counter(entvars_t *pev);
C_DLLEXPORT void trigger_transition(entvars_t *pev);
C_DLLEXPORT void trigger_changelevel(entvars_t *pev);
C_DLLEXPORT void trigger_push(entvars_t *pev);
C_DLLEXPORT void trigger_teleport(entvars_t *pev);
C_DLLEXPORT void trigger_autosave(entvars_t *pev);
C_DLLEXPORT void trigger_endsection(entvars_t *pev);
C_DLLEXPORT void trigger_gravity(entvars_t *pev);
C_DLLEXPORT void trigger_changetarget(entvars_t *pev);
C_DLLEXPORT void trigger_camera(entvars_t *pev);
C_DLLEXPORT void game_score(entvars_t *pev);
C_DLLEXPORT void game_end(entvars_t *pev);
C_DLLEXPORT void game_text(entvars_t *pev);
C_DLLEXPORT void game_team_master(entvars_t *pev);
C_DLLEXPORT void game_team_set(entvars_t *pev);
C_DLLEXPORT void game_zone_player(entvars_t *pev);
C_DLLEXPORT void game_player_hurt(entvars_t *pev);
C_DLLEXPORT void game_counter(entvars_t *pev);
C_DLLEXPORT void game_counter_set(entvars_t *pev);
C_DLLEXPORT void game_player_equip(entvars_t *pev);
C_DLLEXPORT void game_player_team(entvars_t *pev);
C_DLLEXPORT void info_null(entvars_t *pev);
C_DLLEXPORT void info_target(entvars_t *pev);
C_DLLEXPORT void info_intermission(entvars_t *pev);
C_DLLEXPORT void info_map_parameters(entvars_t *pev);
C_DLLEXPORT void info_player_deathmatch(entvars_t *pev);
C_DLLEXPORT void info_player_start(entvars_t *pev);
C_DLLEXPORT void info_teleport_destination(entvars_t *pev);
C_DLLEXPORT void info_vip_start(entvars_t *pev);
C_DLLEXPORT void info_landmark(entvars_t *pev);
C_DLLEXPORT void info_hostage_rescue(entvars_t *pev);
C_DLLEXPORT void info_bomb_target(entvars_t *pev);
C_DLLEXPORT void item_airtank(entvars_t *pev);
C_DLLEXPORT void item_sodacan(entvars_t *pev);
C_DLLEXPORT void item_healthkit(entvars_t *pev);
C_DLLEXPORT void item_suit(entvars_t *pev);
C_DLLEXPORT void item_battery(entvars_t *pev);
C_DLLEXPORT void item_antidote(entvars_t *pev);
C_DLLEXPORT void item_security(entvars_t *pev);
C_DLLEXPORT void item_longjump(entvars_t *pev);
C_DLLEXPORT void item_kevlar(entvars_t *pev);
C_DLLEXPORT void item_assaultsuit(entvars_t *pev);
C_DLLEXPORT void item_thighpack(entvars_t *pev);
C_DLLEXPORT void light(entvars_t *pev);
C_DLLEXPORT void light_environment(entvars_t *pev);
C_DLLEXPORT void light_spot(entvars_t *pev);
C_DLLEXPORT void cycler(entvars_t *pev);
C_DLLEXPORT void cycler_prdroid(entvars_t *pev);
C_DLLEXPORT void cycler_sprite(entvars_t *pev);
C_DLLEXPORT void cycler_weapon(entvars_t *pev);
C_DLLEXPORT void cycler_wreckage(entvars_t *pev);
C_DLLEXPORT void monster_mortar(entvars_t *pev);
C_DLLEXPORT void monster_scientist(entvars_t *pev);
C_DLLEXPORT void monster_hevsuit_dead(entvars_t *pev);
C_DLLEXPORT void player(entvars_t *pev);
C_DLLEXPORT void player_loadsaved(entvars_t *pev);
C_DLLEXPORT void player_weaponstrip(entvars_t *pev);
C_DLLEXPORT void path_corner(entvars_t *pev);
C_DLLEXPORT void path_track(entvars_t *pev);
C_DLLEXPORT void worldspawn(entvars_t *pev);
C_DLLEXPORT void infodecal(entvars_t *pev);
C_DLLEXPORT void bodyque(entvars_t *pev);
C_DLLEXPORT void spark_shower(entvars_t *pev);
C_DLLEXPORT void beam(entvars_t *pev);
C_DLLEXPORT void gibshooter(entvars_t *pev);
C_DLLEXPORT void test_effect(entvars_t *pev);
C_DLLEXPORT void soundent(entvars_t *pev);
C_DLLEXPORT void ambient_generic(entvars_t *pev);
C_DLLEXPORT void target_cdaudio(entvars_t *pev);
C_DLLEXPORT void speaker(entvars_t *pev);
C_DLLEXPORT void DelayedUse(entvars_t *pev);
C_DLLEXPORT void multi_manager(entvars_t *pev);
C_DLLEXPORT void fireanddie(entvars_t *pev);
C_DLLEXPORT void multisource(entvars_t *pev);
C_DLLEXPORT void button_target(entvars_t *pev);
C_DLLEXPORT void momentary_rot_button(entvars_t *pev);
C_DLLEXPORT void momentary_door(entvars_t *pev);
C_DLLEXPORT void hostage_entity(entvars_t *pev);
C_DLLEXPORT void armoury_entity(entvars_t *pev);
C_DLLEXPORT void weaponbox(entvars_t *pev);
C_DLLEXPORT void grenade(entvars_t *pev);
C_DLLEXPORT void world_items(entvars_t *pev);

typedef int (CGraph::*FIND_NEAREST_NODE_ENTITY)(const Vector &, CBaseEntity *);
typedef int (CGraph::*FIND_NEAREST_NODE_INT)(const Vector &, int);
typedef void (CBaseMonster::*RADIUSDAMAGE_ENTVARS)(entvars_t *, entvars_t *, float, int, int);
typedef void (CBaseMonster::*RADIUSDAMAGE_VECTOR)(Vector, entvars_t *, entvars_t *, float, int, int);
typedef BOOL (CBaseMonster::*FINVIEWCONE_ENTITY)(CBaseEntity *);
typedef BOOL (CBaseMonster::*FINVIEWCONE_VECTOR)(const Vector *);
typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY_VECTOR)(const Vector &) const;
typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY_CBASE)(CBaseEntity *, const Vector &) const;
typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY)() const;
typedef BOOL (CLocalNav::*PATH_CLEAR_TRACE_RESULT)(Vector &, Vector &, int, TraceResult &);
typedef BOOL (CLocalNav::*PATH_CLEAR_DEFAULT)(Vector &, Vector &, int);
typedef void (HostageAnimateState::*ADD_SEQUENCE_NAME)(CHostageImprov *, const char *, float, float);
typedef void (HostageAnimateState::*ADD_SEQUENCE_NUMBER)(CHostageImprov *, int, float, float);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_CBASE)(CBaseEntity *);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_ENTVARS)(entvars_t *);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_EOFFSET)(EOFFSET);
typedef int (CSaveRestoreBuffer::*ENTITYINDEX_EDICT)(edict_t *);
typedef void (CSave::*WRITESTRING_)(const char *,const char *);
typedef void (CSave::*WRITESTRING_COUNT)(const char *,const int *,int);
typedef void (CSave::*WRITEVECTOR_)(const char *,const Vector &);
typedef void (CSave::*WRITEVECTOR_COUNT)(const char *,const float *,int);
typedef void (CSave::*WRITEPOSITIONVECTOR_)(const char *,const Vector &);
typedef void (CSave::*WRITEPOSITIONVECTOR_COUNT)(const char *,const float *,int);
typedef int (CSaveRestoreBuffer::*CSAVERESTOREBUFFER_VOID)(const char *,const Vector &);
typedef int (CSaveRestoreBuffer::*CSAVERESTOREBUFFER_POINTER)(const char *,const float *,int);
typedef bool (CCSBot::*CS_IS_VISIBLE_VECTOR)(const Vector *, bool) const;
typedef bool (CCSBot::*CS_IS_VISIBLE_CBASEPLAYER)(CBasePlayer *, bool, unsigned char *) const;
typedef const Vector *(FIND_SPOT_CSSBOT)(CCSBot *, float);
typedef void (CCSBot::*HIDE_NAV_AREA)(CNavArea *, float, float, bool);
typedef void (CCSBot::*HIDE_VECTOR)(const Vector *, float, bool);
typedef const CSGameState *(CCSBot::*GETGAMESTATE_CONST)() const;
typedef CSGameState *(CCSBot::*GETGAMESTATE_NOTCONST)();
typedef BOOL (CBaseEntity::*FVISIBLE_ENTITY)(CBaseEntity *);
typedef BOOL (CBaseEntity::*FVISIBLE_VECTOR)(const Vector &);
typedef void (CGrenade::*EXPLODE_VECTOR)(Vector, Vector);
typedef void (CGrenade::*EXPLODE_TRACERESULT)(TraceResult *, int);
typedef CBaseEntity *(CBaseEntity::*CBASE_ISTANCE_EDICT)(edict_t *);
typedef CBaseEntity *(CBaseEntity::*CBASE_ISTANCE_ENTVARS)(entvars_t *);
typedef CBaseEntity *(CBaseEntity::*CBASE_ISTANCE_INT)(int);
typedef CBasePlayer *(*UTIL_GETCLOSE_PLAYER)(const Vector *pos, float *distance);
typedef CBasePlayer *(*UTIL_GETCLOSE_TEAM)(const Vector *pos, int team, float *distance);
typedef Vector (*UTIL_CUMPUTE_ENTVARS)(entvars_t *pevVars);
typedef Vector (*UTIL_CUMPUTE_CBASE)(CBaseEntity *pEntity);
typedef Vector (*UTIL_CUMPUTE_EDICT)(edict_t *pentEdict);
typedef bool (CBot::*IS_VISIBLE_VECTOR)(const Vector *, bool) const;
typedef bool (CBot::*IS_VISIBLE_CBASE_PLAYER)(CBasePlayer *, bool, unsigned char *) const;
typedef bool (CImprov::*IS_FRIEND_INT_THEWAY_VECTOR)(const Vector &goalPos) const;
typedef bool (CImprov::*IS_FRIEND_INT_THEWAY_CBASEENTITY)(CBaseEntity *myFriend, const Vector &goalPos) const;
typedef const Vector *(FIND_SPOT_CBASE)(CBaseEntity *, const Vector *, CNavArea *, float, int, bool);
typedef void (CNavArea::*SAVE_FD)(int fd, unsigned int version);
typedef void (CNavArea::*SAVE_FILE)(FILE *fp) const;
typedef bool (CNavArea::*OVERLAP_VECTOR)(const Vector *pos) const;
typedef bool (CNavArea::*OVERLAP_CNAV)(const CNavArea *area) const;
typedef float (CNavArea::*GETZ_VECTOR)(const Vector *pos) const;
typedef float (CNavArea::*GETZ_TWO_FLOAT)(float x, float y) const;
typedef void (HidingSpot::*HIDING_SPOT_VOID)();
typedef void (HidingSpot::*HIDING_SPOT_VECTOR)(const Vector *pos, unsigned char flags);
typedef void (HidingSpot::*CNAV_AREA_VOID)();
typedef void (HidingSpot::*CNAV_AREA_TWO_VECTOR)(const Vector *corner, const Vector *otherCorner);
typedef void (HidingSpot::*CNAV_AREA_VECTOR)(const Vector *nwCorner, const Vector *neCorner, const Vector *seCorner, const Vector *swCorner);
typedef void (HidingSpot::*CNAV_AREA_NAVNODE)(CNavNode *nwNode, class CNavNode *neNode, class CNavNode *seNode, class CNavNode *swNode);

// externs
extern struct WeaponAliasInfo weaponAliasInfo[39];
extern struct WeaponBuyAliasInfo weaponBuyAliasInfo[43];
extern struct WeaponClassAliasInfo weaponClassAliasInfo[46];
extern struct WeaponInfoStruct weaponInfo[27];
extern edict_t *g_pBodyQueueHead;
extern TYPEDESCRIPTION gGlobalEntitySaveData[3];
extern TYPEDESCRIPTION gEntvarsDescription[86];
extern unsigned int seed_table[256];
extern unsigned int glSeed;
extern const int gSizes[18];
extern bool s_tutorDisabledThisGame;
extern float s_nextCvarCheckTime;
extern char *const g_TutorStateStrings[20];
extern const char *TutorIdentifierList[150];
extern struct sv_blending_interface_s svBlending;
extern struct server_studio_api_s IEngineStudio;
extern studiohdr_t *g_pstudiohdr;
extern float (*g_pRotationMatrix)[3][4];
extern float (*g_pBoneTransform)[128][3][4];
extern float omega;
extern float cosom;
extern float sinom;
extern float sclp;
extern float sclq;
extern const struct TaskInfo taskInfo[21];
extern CMemoryPool hashItemMemPool;
extern BOOL gTouchDisabled;
extern DLL_FUNCTIONS gFunctionTable;
extern NEW_DLL_FUNCTIONS gNewDLLFunctions;
extern char grgszTextureName[1024][17];
extern char grgchTextureType[1024];
extern BOOL fTextureTypeInit;
extern struct sentenceg rgsentenceg[200];
extern int fSentencesInit;
extern int gcallsentences;
extern struct dynpitchvol rgdpvpreset[27];
extern struct PLAYERPVSSTATUS g_PVSStatus[32];
extern bool g_bClientPrintEnable;
extern char *sPlayerModelFiles[12];
extern struct entity_field_alias_t entity_field_alias[6];
extern struct entity_field_alias_t player_field_alias[3];
extern struct entity_field_alias_t custom_entity_field_alias[9];
extern int g_serveractive;
extern struct DebugOutputLevel outputLevel[6];
extern unsigned int theDebugOutputTypes;
extern char theDebugBuffer[1024];
extern Vector gTankSpread[5];
extern class CCStrikeGameMgrHelper g_GameMgrHelper;
extern cvar_t *sv_clienttrace;
extern class CHalfLifeMultiplay *g_pMPGameRules;
extern char mp_com_token[1500];
extern int giAmmoIndex;
extern char *m_szPoses[4];
extern struct WeaponStruct g_weaponStruct[32];
extern int zombieSpawnCount;
extern struct ZombieSpawn zombieSpawn[256];
extern CBaseEntity *g_pSelectedZombieSpawn;
extern char st_szNextMap[32];
extern char st_szNextSpot[32];
extern char s_shared_token[1500];
extern char s_shared_quote;
extern cvar_t voice_serverdebug;
extern cvar_t sv_alltalk;
extern CPlayerBitVec g_PlayerModEnable;
extern CBitVec< VOICE_MAX_PLAYERS > g_BanMasks[ VOICE_MAX_PLAYERS ];
extern CBitVec< VOICE_MAX_PLAYERS > g_SentGameRulesMasks[ VOICE_MAX_PLAYERS ];
extern CBitVec< VOICE_MAX_PLAYERS > g_SentBanMasks[ VOICE_MAX_PLAYERS ];
extern CPlayerBitVec g_bWantModEnable;
extern struct LessCtx_t g_LessCtx;
extern short s_iBeamSprite;
extern float cosTable[256];
extern float lastDrawTimestamp;
extern std::list_vs6<CNavArea *> goodSizedAreaList;
extern CNavArea *markedArea;
extern CNavArea *lastSelectedArea;
extern enum NavCornerType markedCorner;
extern bool isCreatingNavArea;
extern bool isAnchored;
extern Vector anchor;
extern bool isPlaceMode;
extern bool isPlacePainting;
extern float editTimestamp;
extern unsigned int BlockedID[256];
extern int BlockedIDCount;
extern enum NavDirType Opposite[4];
extern int pm_shared_initialized;
extern vec3_t rgv3tStuckTable[54];
extern int rgStuckLast[32][2];
extern int g_onladder;
extern int pm_gcTextures;
extern char pm_grgszTextureName[1024][17];
extern char pm_grgchTextureType[1024];
extern char *BotDifficultyName[5];

extern BOOL g_fGameOver;
extern float g_flResetTime;
C_DLLEXPORT float g_flTimeLimit;

// declared functions
C_DLLEXPORT void WINAPI GiveFnptrsToDll(enginefuncs_t *pEnginefuncsTable, globalvars_t *pGlobals);
bool NavAreaBuildPath__HostagePathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, HostagePathCost &costFunc, CNavArea **closestArea);
bool NavAreaBuildPath__ShortestPathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, ShortestPathCost &costFunc, CNavArea **closestArea);
bool NavAreaBuildPath__PathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, PathCost &costFunc, CNavArea **closestArea);
float_precision NavAreaTravelDistance__PathCost__wrapper(CNavArea *startArea, CNavArea *endArea, PathCost &costFunc);

// PM
void PM_SwapTextures(int i, int j);
int PM_IsThereGrassTexture();
void PM_SortTextures();
void PM_InitTextureTypes();
void PM_PlayStepSound(int step, float fvol);
int PM_MapTextureTypeStepType(char chTextureType);
void PM_CatagorizeTextureType();
void PM_UpdateStepSound();
qboolean PM_AddToTouched(struct pmtrace_s tr, vec_t *impactvelocity);
void PM_CheckVelocity();
int PM_ClipVelocity(vec_t *in, vec_t *normal, vec_t *out, float overbounce);
void PM_AddCorrectGravity();
void PM_FixupGravityVelocity();
int PM_FlyMove();
void PM_Accelerate(vec_t *wishdir, float_precision wishspeed, float accel);
void PM_WalkMove();
void PM_Friction();
void PM_AirAccelerate(vec_t *wishdir, float wishspeed, float accel);
void PM_WaterMove();
void PM_AirMove(int playerIndex = 0);
qboolean PM_InWater();
qboolean PM_CheckWater();
void PM_CatagorizePosition();
int PM_GetRandomStuckOffsets(int nIndex, int server, vec_t *offset);
void PM_ResetStuckOffsets(int nIndex, int server);
qboolean PM_CheckStuck();
void PM_SpectatorMove();
float PM_SplineFraction(float value, float scale);
float PM_SimpleSpline(float value);
void PM_FixPlayerCrouchStuck(int direction);
void PM_Duck();
void PM_LadderMove(struct physent_s *pLadder);
struct physent_s *PM_Ladder();
void PM_WaterJump();
void PM_AddGravity();
struct pmtrace_s PM_PushEntity(vec_t *push);
void PM_Physics_Toss();
void PM_NoClip();
void PM_PreventMegaBunnyJumping();
void PM_Jump();
void PM_CheckWaterJump();
void PM_CheckFalling();
void PM_PlayWaterSounds();
float PM_CalcRoll(vec_t *angles, vec_t *velocity, float rollangle, float rollspeed);
void PM_DropPunchAngle(vec_t *punchangle);
void PM_CheckParamters();
void PM_ReduceTimers();
qboolean PM_ShouldDoSpectMode();
void PM_PlayerMove(qboolean server);
void PM_CreateStuckTable();
int PM_GetVisEntInfo(int ent);
int PM_GetPhysEntInfo(int ent);

// Animation
C_DLLEXPORT int Server_GetBlendingInterface(int version, struct sv_blending_interface_s **ppinterface, struct engine_studio_api_s *pstudio, float *rotationmatrix, float *bonetransform);
void AngleQuaternion(vec_t *angles, vec_t *quaternion);
void QuaternionSlerp(vec_t *p, vec_t *q, float t, vec_t *qt);
void QuaternionMatrix(vec_t *quaternion, float (*matrix)[4]);
mstudioanim_t *StudioGetAnim(struct model_s *m_pSubModel, mstudioseqdesc_t *pseqdesc);
mstudioanim_t *LookupAnimation(struct model_s *model, mstudioseqdesc_t *pseqdesc, int index);
void StudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen);
void StudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q);
void StudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos);
void StudioSlerpBones(vec4_t *q1, float pos1[][3], vec4_t *q2, float pos2[][3], float s);
void StudioCalcRotations(mstudiobone_t *pbones, int *chain, int chainlength, float *adj, float pos[128][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, float s);
void ConcatTransforms(float in1[3][4], float in2[3][4], float out[3][4]);
void SV_StudioSetupBones(struct model_s *pModel, float frame, int sequence, const vec_t *angles, const vec_t *origin, const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict);

// basemonster
float GetAmountOfPlayerVisible(Vector vecSrc, CBaseEntity *entity);
char *vstr(float *v);

//cbase
/*C_DLLEXPORT*/ int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

#endif // HOOKER_IMPL_H
