#include "precompiled.h"

// xrefs
void (CBaseEntity::*pCHostage__IdleThink)();
void (*pBotPhrase__Randomize)();
void (*pCCSBotManager__AddBot)();
void (*pCCSBot__UpdateLookAngles)();

// globals
TYPEDESCRIPTION	IMPL_CLASS(CBaseEntity, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CAirtank, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CBaseAnimating, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CFuncRotating, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CPendulum, m_SaveData)[8];
TYPEDESCRIPTION IMPL_CLASS(CEnvGlobal, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CMultiSource, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CBaseButton, m_SaveData)[8];
TYPEDESCRIPTION IMPL_CLASS(CMomentaryRotButton, m_SaveData)[6];
TYPEDESCRIPTION IMPL_CLASS(CEnvSpark, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CAmbientGeneric, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CEnvSound, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CSpeaker, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CGlobalState, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CBaseDoor, m_SaveData)[7];
TYPEDESCRIPTION IMPL_CLASS(CMomentaryDoor, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CBubbling, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CLightning, m_SaveData)[13];
TYPEDESCRIPTION IMPL_CLASS(CLaser, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CGlow, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CSprite, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CGibShooter, m_SaveData)[7];
TYPEDESCRIPTION IMPL_CLASS(CEnvExplosion, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CBreakable, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CPushable, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CFuncTank, m_SaveData)[26];
TYPEDESCRIPTION IMPL_CLASS(CFuncTankLaser, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CFuncTankControls, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CGrenade, m_SaveData)[15];
TYPEDESCRIPTION IMPL_CLASS(CRecharge, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CCycler, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CCyclerSprite, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CWreckage, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CWallHealth, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CLight, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CRuleEntity, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CGameText, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CGamePlayerZone, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CFuncMortarField, m_SaveData)[6];
TYPEDESCRIPTION IMPL_CLASS(CPathCorner, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CPathTrack, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CBasePlatTrain, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CFuncPlatRot, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CFuncTrain, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CFuncTrackTrain, m_SaveData)[12];
TYPEDESCRIPTION IMPL_CLASS(CFuncTrackChange, m_SaveData)[9];
TYPEDESCRIPTION IMPL_CLASS(CGunTarget, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CBaseDelay, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CBaseToggle, m_SaveData)[19];
TYPEDESCRIPTION IMPL_CLASS(CFuncWeaponCheck, m_SaveData)[6];
TYPEDESCRIPTION IMPL_CLASS(CBaseGrenCatch, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CFrictionModifier, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CAutoTrigger, m_SaveData)[2];
TYPEDESCRIPTION IMPL_CLASS(CTriggerRelay, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CMultiManager, m_SaveData)[5];
TYPEDESCRIPTION IMPL_CLASS(CChangeLevel, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CTriggerChangeTarget, m_SaveData)[1];
TYPEDESCRIPTION IMPL_CLASS(CTriggerCamera, m_SaveData)[13];
TYPEDESCRIPTION IMPL_CLASS(CFuncVehicle, m_SaveData)[12];
TYPEDESCRIPTION IMPL_CLASS(CBasePlayerItem, m_SaveData)[3];
TYPEDESCRIPTION IMPL_CLASS(CBasePlayerWeapon, m_SaveData)[7];
TYPEDESCRIPTION IMPL_CLASS(CWeaponBox, m_SaveData)[4];
TYPEDESCRIPTION IMPL_CLASS(CRevertSaved, m_SaveData)[2];

TYPEDESCRIPTION IMPL_CLASS(CBasePlayer, m_playerSaveData)[40];
TYPEDESCRIPTION gGlobalEntitySaveData[3];

// globals gamerules
CGameRules *g_pGameRules;
char mp_com_token[ COM_TOKEN_LEN ];
cvar_t *sv_clienttrace;

// globals player.cpp
int giPrecacheGrunt, gmsgWeapPickup, gmsgHudText, gmsgHudTextArgs, gmsgShake, gmsgFade, gmsgFlashlight, gmsgFlashBattery, gmsgResetHUD,
gmsgInitHUD, gmsgViewMode, gmsgShowGameTitle, gmsgCurWeapon, gmsgHealth, gmsgDamage, gmsgBattery, gmsgTrain, gmsgLogo,
gmsgWeaponList, gmsgAmmoX, gmsgDeathMsg, gmsgScoreAttrib, gmsgScoreInfo, gmsgTeamInfo, gmsgTeamScore, gmsgGameMode, gmsgMOTD,
gmsgServerName, gmsgAmmoPickup, gmsgItemPickup, gmsgHideWeapon, gmsgSayText, gmsgTextMsg, gmsgSetFOV, gmsgShowMenu, gmsgSendAudio,
gmsgRoundTime, gmsgMoney, gmsgBlinkAcct, gmsgArmorType, gmsgStatusValue, gmsgStatusText, gmsgStatusIcon, gmsgBarTime, gmsgReloadSound,
gmsgCrosshair, gmsgNVGToggle, gmsgRadar, gmsgSpectator, gmsgVGUIMenu, gmsgCZCareer, gmsgCZCareerHUD, gmsgTaskTime, gmsgTutorText,
gmsgTutorLine, gmsgShadowIdx, gmsgTutorState, gmsgTutorClose, gmsgAllowSpec, gmsgBombDrop, gmsgBombPickup, gmsgHostagePos, gmsgHostageK,
gmsgGeigerRange, gmsgSendCorpse, gmsgHLTV, gmsgSpecHealth, gmsgForceCam, gmsgADStop, gmsgReceiveW, gmsgScenarioIcon, gmsgBotVoice,
gmsgBuyClose, gmsgItemStatus, gmsgLocation, gmsgSpecHealth2, gmsgBarTime2, gmsgBotProgress, gmsgBrass, gmsgFog, gmsgShowTimer;
BOOL gInitHUD;
cvar_t *sv_aim;
WeaponStruct g_weaponStruct[ MAX_WEAPONS ];
char *(*CDeadHEV::pm_szPoses)[4];

// globals hostages
CHostageManager *g_pHostages;
int g_iHostageNumber;

cvar_t cv_hostage_debug;
cvar_t cv_hostage_stop;

float (*CLocalNav::ps_flStepSize);
int (*CLocalNav::pqptr);
EHANDLE (*CLocalNav::pqueue)[20];
int (*CLocalNav::ptot_inqueue);
float (*CLocalNav::pnodeval);
float (*CLocalNav::pflNextCvarCheck);
float (*CLocalNav::pflLastThinkTime);
EHANDLE (*CLocalNav::phostages)[20];
int (*CLocalNav::ptot_hostages);

// soundent
CSoundEnt *pSoundEnt;

// globals weapons
const char *g_pModelNameLaser;
ItemInfo IMPL_CLASS(CBasePlayerItem, ItemInfoArray)[32];
AmmoInfo IMPL_CLASS(CBasePlayerItem, AmmoInfoArray)[32];

AutoBuyInfoStruct g_autoBuyInfo[35];
WeaponAliasInfo weaponAliasInfo[39];
WeaponBuyAliasInfo weaponBuyAliasInfo[43];
WeaponClassAliasInfo weaponClassAliasInfo[46];
WeaponInfoStruct weaponInfo[27];

// globals utils
TYPEDESCRIPTION gEntvarsDescription[86];
unsigned int seed_table[256];
int g_groupop;
int g_groupmask;
const int gSizes[18];

// globals bots
CBotManager *TheBots;
BotPhraseManager *TheBotPhrases;
CBaseEntity *g_pSelectedZombieSpawn;

CountdownTimer IMPL_CLASS(BotChatterInterface, m_encourageTimer);
IntervalTimer IMPL_CLASS(BotChatterInterface, m_radioSilenceInterval)[ 2 ];

float IMPL_CLASS(CCSBotManager, m_flNextCVarCheck);
bool IMPL_CLASS(CCSBotManager, m_isMapDataLoaded);
bool IMPL_CLASS(CCSBotManager, m_isLearningMap);
bool IMPL_CLASS(CCSBotManager, m_isAnalysisRequested);
NavEditCmdType IMPL_CLASS(CCSBotManager, m_editCmd);

cvar_t cv_bot_traceview;
cvar_t cv_bot_stop;
cvar_t cv_bot_show_nav;
cvar_t cv_bot_show_danger;
cvar_t cv_bot_nav_edit;
cvar_t cv_bot_nav_zdraw;
cvar_t cv_bot_walk;
cvar_t cv_bot_difficulty;
cvar_t cv_bot_debug;
cvar_t cv_bot_quicksave;
cvar_t cv_bot_quota;
cvar_t cv_bot_quota_match;
cvar_t cv_bot_prefix;
cvar_t cv_bot_allow_rogues;
cvar_t cv_bot_allow_pistols;
cvar_t cv_bot_allow_shotguns;
cvar_t cv_bot_allow_sub_machine_guns;
cvar_t cv_bot_allow_rifles;
cvar_t cv_bot_allow_machine_guns;
cvar_t cv_bot_allow_grenades;
cvar_t cv_bot_allow_snipers;
cvar_t cv_bot_allow_shield;
cvar_t cv_bot_join_team;
cvar_t cv_bot_join_after_player;
cvar_t cv_bot_auto_vacate;
cvar_t cv_bot_zombie;
cvar_t cv_bot_defer_to_human;
cvar_t cv_bot_chatter;
cvar_t cv_bot_profile_db;

// globals globals.cpp
const Vector g_vecZero;
u_long g_ulFrameCount;

// globals func_tank.cpp
Vector gTankSpread[5];

// globals func_break.cpp
const char *(*CBreakable::ppSpawnObjects)[32];
const char *(*CBreakable::ppSoundsWood)[3];
const char *(*CBreakable::ppSoundsFlesh)[6];
const char *(*CBreakable::ppSoundsMetal)[3];
const char *(*CBreakable::ppSoundsConcrete)[3];
const char *(*CBreakable::ppSoundsGlass)[3];
char *(*CPushable::pm_soundNames)[3];

// globals sound.cpp
dynpitchvol_t rgdpvpreset[CDPVPRESETMAX];
int fSentencesInit;
int gcallsentences;

// globals cbase.cpp
DLL_FUNCTIONS gFunctionTable;
NEW_DLL_FUNCTIONS gNewDLLFunctions;
CMemoryPool hashItemMemPool;
BOOL gTouchDisabled;

// globals world.cpp
DLL_DECALLIST gDecals[42];

// globals animation.cpp
sv_blending_interface_t svBlending;

// globals career_tasks.cpp
CCareerTaskManager *TheCareerTasks;
const TaskInfo taskInfo[21];

// globals client.cpp
float g_flTimeLimit;
float g_flResetTime;
bool g_bClientPrintEnable;

char *sPlayerModelFiles[12];
bool g_skipCareerInitialSpawn;

entity_field_alias_t entity_field_alias[6];
entity_field_alias_t player_field_alias[3];
entity_field_alias_t custom_entity_field_alias[9];
int g_serveractive;

// globals debug.cpp
DebugOutputLevel outputLevel[ NUM_LEVELS ];
unsigned int theDebugOutputTypes;
char theDebugBuffer[ DebugBufferSize ];

// globals tutors
char *const g_TutorStateStrings[20];
const char *TutorIdentifierList[150];

bool s_tutorDisabledThisGame;
float s_nextCvarCheckTime;

cvar_t cv_tutor_message_repeats;
cvar_t cv_tutor_debug_level;
cvar_t cv_tutor_view_distance;
cvar_t cv_tutor_viewable_check_interval;
cvar_t cv_tutor_look_distance;
cvar_t cv_tutor_look_angle;
cvar_t cv_tutor_examine_time;
cvar_t cv_tutor_message_minimum_display_time;
cvar_t cv_tutor_message_character_display_time_coefficient;
cvar_t cv_tutor_hint_interval_time;

// globals game.cpp
cvar_t *g_psv_gravity;
cvar_t *g_psv_aim;
cvar_t *g_footsteps;
cvar_t *g_psv_accelerate;
cvar_t *g_psv_friction;
cvar_t *g_psv_stopspeed;

cvar_t displaysoundlist;
cvar_t timelimit;
cvar_t flashlight;
cvar_t decalfrequency;
cvar_t fadetoblack;
cvar_t fragsleft;
cvar_t timeleft;
cvar_t friendlyfire;
cvar_t allowmonsters;
cvar_t roundtime;
cvar_t buytime;
cvar_t freezetime;
cvar_t c4timer;
cvar_t ghostfrequency;
cvar_t autokick;
cvar_t autokick_timeout;
cvar_t restartround;
cvar_t sv_restart;
cvar_t limitteams;
cvar_t autoteambalance;
cvar_t tkpunish;
cvar_t hostagepenalty;
cvar_t mirrordamage;
cvar_t logmessages;
cvar_t forcecamera;
cvar_t forcechasecam;
cvar_t mapvoteratio;
cvar_t logdetail;
cvar_t startmoney;
cvar_t maxrounds;
cvar_t winlimit;
cvar_t windifference;
cvar_t playerid;
cvar_t allow_spectators;
cvar_t mp_chattime;
cvar_t kick_percent;
cvar_t humans_join_team;

// NOXREF
//cvar_t sk_agrunt_health1;
//cvar_t sk_agrunt_health2;
//cvar_t sk_agrunt_health3;
//cvar_t sk_agrunt_dmg_punch1;
//cvar_t sk_agrunt_dmg_punch2;
//cvar_t sk_agrunt_dmg_punch3;
//cvar_t sk_apache_health1;
//cvar_t sk_apache_health2;
//cvar_t sk_apache_health3;
//cvar_t sk_barney_health1;
//cvar_t sk_barney_health2;
//cvar_t sk_barney_health3;
//cvar_t sk_bullsquid_health1;
//cvar_t sk_bullsquid_health2;
//cvar_t sk_bullsquid_health3;
//cvar_t sk_bullsquid_dmg_bite1;
//cvar_t sk_bullsquid_dmg_bite2;
//cvar_t sk_bullsquid_dmg_bite3;
//cvar_t sk_bullsquid_dmg_whip1;
//cvar_t sk_bullsquid_dmg_whip2;
//cvar_t sk_bullsquid_dmg_whip3;
//cvar_t sk_bullsquid_dmg_spit1;
//cvar_t sk_bullsquid_dmg_spit2;
//cvar_t sk_bullsquid_dmg_spit3;
//cvar_t sk_bigmomma_health_factor1;
//cvar_t sk_bigmomma_health_factor2;
//cvar_t sk_bigmomma_health_factor3;
//cvar_t sk_bigmomma_dmg_slash1;
//cvar_t sk_bigmomma_dmg_slash2;
//cvar_t sk_bigmomma_dmg_slash3;
//cvar_t sk_bigmomma_dmg_blast1;
//cvar_t sk_bigmomma_dmg_blast2;
//cvar_t sk_bigmomma_dmg_blast3;
//cvar_t sk_bigmomma_radius_blast1;
//cvar_t sk_bigmomma_radius_blast2;
//cvar_t sk_bigmomma_radius_blast3;
//cvar_t sk_gargantua_health1;
//cvar_t sk_gargantua_health2;
//cvar_t sk_gargantua_health3;
//cvar_t sk_gargantua_dmg_slash1;
//cvar_t sk_gargantua_dmg_slash2;
//cvar_t sk_gargantua_dmg_slash3;
//cvar_t sk_gargantua_dmg_fire1;
//cvar_t sk_gargantua_dmg_fire2;
//cvar_t sk_gargantua_dmg_fire3;
//cvar_t sk_gargantua_dmg_stomp1;
//cvar_t sk_gargantua_dmg_stomp2;
//cvar_t sk_gargantua_dmg_stomp3;
//cvar_t sk_hassassin_health1;
//cvar_t sk_hassassin_health2;
//cvar_t sk_hassassin_health3;
//cvar_t sk_headcrab_health1;
//cvar_t sk_headcrab_health2;
//cvar_t sk_headcrab_health3;
//cvar_t sk_headcrab_dmg_bite1;
//cvar_t sk_headcrab_dmg_bite2;
//cvar_t sk_headcrab_dmg_bite3;
//cvar_t sk_hgrunt_health1;
//cvar_t sk_hgrunt_health2;
//cvar_t sk_hgrunt_health3;
//cvar_t sk_hgrunt_kick1;
//cvar_t sk_hgrunt_kick2;
//cvar_t sk_hgrunt_kick3;
//cvar_t sk_hgrunt_pellets1;
//cvar_t sk_hgrunt_pellets2;
//cvar_t sk_hgrunt_pellets3;
//cvar_t sk_hgrunt_gspeed1;
//cvar_t sk_hgrunt_gspeed2;
//cvar_t sk_hgrunt_gspeed3;
//cvar_t sk_houndeye_health1;
//cvar_t sk_houndeye_health2;
//cvar_t sk_houndeye_health3;
//cvar_t sk_houndeye_dmg_blast1;
//cvar_t sk_houndeye_dmg_blast2;
//cvar_t sk_houndeye_dmg_blast3;
//cvar_t sk_islave_health1;
//cvar_t sk_islave_health2;
//cvar_t sk_islave_health3;
//cvar_t sk_islave_dmg_claw1;
//cvar_t sk_islave_dmg_claw2;
//cvar_t sk_islave_dmg_claw3;
//cvar_t sk_islave_dmg_clawrake1;
//cvar_t sk_islave_dmg_clawrake2;
//cvar_t sk_islave_dmg_clawrake3;
//cvar_t sk_islave_dmg_zap1;
//cvar_t sk_islave_dmg_zap2;
//cvar_t sk_islave_dmg_zap3;
//cvar_t sk_ichthyosaur_health1;
//cvar_t sk_ichthyosaur_health2;
//cvar_t sk_ichthyosaur_health3;
//cvar_t sk_ichthyosaur_shake1;
//cvar_t sk_ichthyosaur_shake2;
//cvar_t sk_ichthyosaur_shake3;
//cvar_t sk_leech_health1;
//cvar_t sk_leech_health2;
//cvar_t sk_leech_health3;
//cvar_t sk_leech_dmg_bite1;
//cvar_t sk_leech_dmg_bite2;
//cvar_t sk_leech_dmg_bite3;
//cvar_t sk_controller_health1;
//cvar_t sk_controller_health2;
//cvar_t sk_controller_health3;
//cvar_t sk_controller_dmgzap1;
//cvar_t sk_controller_dmgzap2;
//cvar_t sk_controller_dmgzap3;
//cvar_t sk_controller_speedball1;
//cvar_t sk_controller_speedball2;
//cvar_t sk_controller_speedball3;
//cvar_t sk_controller_dmgball1;
//cvar_t sk_controller_dmgball2;
//cvar_t sk_controller_dmgball3;
//cvar_t sk_nihilanth_health1;
//cvar_t sk_nihilanth_health2;
//cvar_t sk_nihilanth_health3;
//cvar_t sk_nihilanth_zap1;
//cvar_t sk_nihilanth_zap2;
//cvar_t sk_nihilanth_zap3;
//cvar_t sk_scientist_health1;
//cvar_t sk_scientist_health2;
//cvar_t sk_scientist_health3;
//cvar_t sk_snark_health1;
//cvar_t sk_snark_health2;
//cvar_t sk_snark_health3;
//cvar_t sk_snark_dmg_bite1;
//cvar_t sk_snark_dmg_bite2;
//cvar_t sk_snark_dmg_bite3;
//cvar_t sk_snark_dmg_pop1;
//cvar_t sk_snark_dmg_pop2;
//cvar_t sk_snark_dmg_pop3;
//cvar_t sk_zombie_health1;
//cvar_t sk_zombie_health2;
//cvar_t sk_zombie_health3;
//cvar_t sk_zombie_dmg_one_slash1;
//cvar_t sk_zombie_dmg_one_slash2;
//cvar_t sk_zombie_dmg_one_slash3;
//cvar_t sk_zombie_dmg_both_slash1;
//cvar_t sk_zombie_dmg_both_slash2;
//cvar_t sk_zombie_dmg_both_slash3;
//cvar_t sk_turret_health1;
//cvar_t sk_turret_health2;
//cvar_t sk_turret_health3;
//cvar_t sk_miniturret_health1;
//cvar_t sk_miniturret_health2;
//cvar_t sk_miniturret_health3;
//cvar_t sk_sentry_health1;
//cvar_t sk_sentry_health2;
//cvar_t sk_sentry_health3;
//cvar_t sk_plr_crowbar1;
//cvar_t sk_plr_crowbar2;
//cvar_t sk_plr_crowbar3;

cvar_t sk_plr_9mm_bullet1;
cvar_t sk_plr_9mm_bullet2;
cvar_t sk_plr_9mm_bullet3;
cvar_t sk_plr_357_bullet1;
cvar_t sk_plr_357_bullet2;
cvar_t sk_plr_357_bullet3;
cvar_t sk_plr_9mmAR_bullet1;
cvar_t sk_plr_9mmAR_bullet2;
cvar_t sk_plr_9mmAR_bullet3;
cvar_t sk_plr_9mmAR_grenade1;
cvar_t sk_plr_9mmAR_grenade2;
cvar_t sk_plr_9mmAR_grenade3;
cvar_t sk_plr_buckshot1;
cvar_t sk_plr_buckshot2;
cvar_t sk_plr_buckshot3;

// NOXREF
//cvar_t sk_plr_xbow_bolt_client1;
//cvar_t sk_plr_xbow_bolt_client2;
//cvar_t sk_plr_xbow_bolt_client3;
//cvar_t sk_plr_xbow_bolt_monster1;
//cvar_t sk_plr_xbow_bolt_monster2;
//cvar_t sk_plr_xbow_bolt_monster3;

cvar_t sk_plr_rpg1;
cvar_t sk_plr_rpg2;
cvar_t sk_plr_rpg3;

// NOXREF
//cvar_t sk_plr_gauss1;
//cvar_t sk_plr_gauss2;
//cvar_t sk_plr_gauss3;
//cvar_t sk_plr_egon_narrow1;
//cvar_t sk_plr_egon_narrow2;
//cvar_t sk_plr_egon_narrow3;
//cvar_t sk_plr_egon_wide1;
//cvar_t sk_plr_egon_wide2;
//cvar_t sk_plr_egon_wide3;
//cvar_t sk_plr_hand_grenade1;
//cvar_t sk_plr_hand_grenade2;
//cvar_t sk_plr_hand_grenade3;
//cvar_t sk_plr_satchel1;
//cvar_t sk_plr_satchel2;
//cvar_t sk_plr_satchel3;
//cvar_t sk_plr_tripmine1;
//cvar_t sk_plr_tripmine2;
//cvar_t sk_plr_tripmine3;

cvar_t sk_12mm_bullet1;
cvar_t sk_12mm_bullet2;
cvar_t sk_12mm_bullet3;
cvar_t sk_9mmAR_bullet1;
cvar_t sk_9mmAR_bullet2;
cvar_t sk_9mmAR_bullet3;
cvar_t sk_9mm_bullet1;
cvar_t sk_9mm_bullet2;
cvar_t sk_9mm_bullet3;

// NOXREF
//cvar_t sk_hornet_dmg1;
//cvar_t sk_hornet_dmg2;
//cvar_t sk_hornet_dmg3;

cvar_t sk_suitcharger1;
cvar_t sk_suitcharger2;
cvar_t sk_suitcharger3;
cvar_t sk_battery1;
cvar_t sk_battery2;
cvar_t sk_battery3;
cvar_t sk_healthcharger1;
cvar_t sk_healthcharger2;
cvar_t sk_healthcharger3;
cvar_t sk_healthkit1;
cvar_t sk_healthkit2;
cvar_t sk_healthkit3;
cvar_t sk_scientist_heal1;
cvar_t sk_scientist_heal2;
cvar_t sk_scientist_heal3;

// NOXREF
//cvar_t sk_monster_head1;
//cvar_t sk_monster_head2;
//cvar_t sk_monster_head3;
//cvar_t sk_monster_chest1;
//cvar_t sk_monster_chest2;
//cvar_t sk_monster_chest3;
//cvar_t sk_monster_stomach1;
//cvar_t sk_monster_stomach2;
//cvar_t sk_monster_stomach3;
//cvar_t sk_monster_arm1;
//cvar_t sk_monster_arm2;
//cvar_t sk_monster_arm3;
//cvar_t sk_monster_leg1;
//cvar_t sk_monster_leg2;
//cvar_t sk_monster_leg3;
//cvar_t sk_player_head1;
//cvar_t sk_player_head2;
//cvar_t sk_player_head3;
//cvar_t sk_player_chest1;
//cvar_t sk_player_chest2;
//cvar_t sk_player_chest3;
//cvar_t sk_player_stomach1;
//cvar_t sk_player_stomach2;
//cvar_t sk_player_stomach3;
//cvar_t sk_player_arm1;
//cvar_t sk_player_arm2;
//cvar_t sk_player_arm3;
//cvar_t sk_player_leg1;
//cvar_t sk_player_leg2;
//cvar_t sk_player_leg3;

// globals shared_util
char s_shared_token[1500];
char s_shared_quote;

// bot util
const char *GameEventName[ NUM_GAME_EVENTS + 1 ];

// voice_gamemgr
cvar_t voice_serverdebug;
cvar_t sv_alltalk;

// bot
float g_flBotCommandInterval;
float g_flBotFullThinkInterval;
const char *BotArgs[4];
bool UseBotArgs;

// utlsymbol
LessCtx_t g_LessCtx;

// bot_profile
BotProfileManager *TheBotProfiles;
char *BotDifficultyName[5];

// bot_util
short s_iBeamSprite;
float cosTable[256];

// nav_area
unsigned int IMPL_CLASS(CNavArea, m_nextID);
unsigned int IMPL_CLASS(CNavArea, m_masterMarker);
unsigned int IMPL_CLASS(HidingSpot, m_nextID);
unsigned int IMPL_CLASS(HidingSpot, m_masterMarker);
NavLadderList TheNavLadderList;
HidingSpotList TheHidingSpotList;
NavAreaList TheNavAreaList;
CNavAreaGrid TheNavAreaGrid;
CNavArea *IMPL_CLASS(CNavArea, m_openList);
bool IMPL_CLASS(CNavArea, m_isReset);
float lastDrawTimestamp;
NavAreaList goodSizedAreaList;
CNavArea *markedArea;
CNavArea *lastSelectedArea;
NavCornerType markedCorner;
bool isCreatingNavArea;
bool isAnchored;
Vector anchor;
bool isPlaceMode;
bool isPlacePainting;
float editTimestamp;
unsigned int BlockedID[256];
int BlockedIDCount;

// nav_node
NavDirType Opposite[4];
CNavNode *IMPL_CLASS(CNavNode, m_list);
unsigned int IMPL_CLASS(CNavNode, m_listLength);

// pm_shared
int pm_shared_initialized;
vec3_t rgv3tStuckTable[54];
int rgStuckLast[MAX_CLIENTS][2];
int pm_gcTextures;
char pm_grgszTextureName[1024][17];
char pm_grgchTextureType[1024];
playermove_t *pmove;
int g_onladder;

// pm_math
vec3_t vec3_origin;
int nanmask;

// CAirtank
void CAirtank::Spawn() { Spawn_(); }
void CAirtank::Precache() { Precache_(); }
int CAirtank::Save(CSave &save) { return Save_(save); }
int CAirtank::Restore(CRestore &restore) { return Restore_(restore); }
void CAirtank::Killed(entvars_t *pevAttacker, int iGib) { Killed_(pevAttacker, iGib); }

// Ammo
void C9MMAmmo::Spawn() { Spawn_(); }
void C9MMAmmo::Precache() { Precache_(); }
BOOL C9MMAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void CBuckShotAmmo::Spawn() { Spawn_(); }
void CBuckShotAmmo::Precache() { Precache_(); }
BOOL CBuckShotAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C556NatoAmmo::Spawn() { Spawn_(); }
void C556NatoAmmo::Precache() { Precache_(); }
BOOL C556NatoAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C556NatoBoxAmmo::Spawn() { Spawn_(); }
void C556NatoBoxAmmo::Precache() { Precache_(); }
BOOL C556NatoBoxAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C762NatoAmmo::Spawn() { Spawn_(); }
void C762NatoAmmo::Precache() { Precache_(); }
BOOL C762NatoAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C45ACPAmmo::Spawn() { Spawn_(); }
void C45ACPAmmo::Precache() { Precache_(); }
BOOL C45ACPAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C50AEAmmo::Spawn() { Spawn_(); }
void C50AEAmmo::Precache() { Precache_(); }
BOOL C50AEAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C338MagnumAmmo::Spawn() { Spawn_(); }
void C338MagnumAmmo::Precache() { Precache_(); }
BOOL C338MagnumAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C57MMAmmo::Spawn() { Spawn_(); }
void C57MMAmmo::Precache() { Precache_(); }
BOOL C57MMAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

void C357SIGAmmo::Spawn() { Spawn_(); }
void C357SIGAmmo::Precache() { Precache_(); }
BOOL C357SIGAmmo::AddAmmo(CBaseEntity *pOther) { return AddAmmo_(pOther); }

// Animating
int CBaseAnimating::Save(CSave &save) { return Save_(save); }
int CBaseAnimating::Restore(CRestore &restore) { return Restore_(restore); }

// bmodels
void CFuncWall::Spawn() { Spawn_(); }
void CFuncWall::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CFuncWallToggle::Spawn() { Spawn_(); }
void CFuncWallToggle::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CFuncConveyor::Spawn() { Spawn_(); }
void CFuncConveyor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CFuncIllusionary::Spawn() { Spawn_(); }
void CFuncIllusionary::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CFuncMonsterClip::Spawn() { Spawn_(); }

void CFuncRotating::Spawn() { Spawn_(); }
void CFuncRotating::Precache() { Precache_(); }
void CFuncRotating::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncRotating::Save(CSave &save) { return Save_(save); }
int CFuncRotating::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncRotating::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }

void CPendulum::Spawn() { Spawn_(); }
void CPendulum::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CPendulum::Save(CSave &save) { return Save_(save); }
int CPendulum::Restore(CRestore &restore) { return Restore_(restore); }
void CPendulum::Touch(CBaseEntity *pOther) { Touch_(pOther); }
void CPendulum::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }

// buttons
void CBaseButton::Spawn() { Spawn_(); }
void CBaseButton::Precache() { Precache_(); }
void CBaseButton::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBaseButton::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
int CBaseButton::Save(CSave &save) { return Save_(save); }
int CBaseButton::Restore(CRestore &restore) { return Restore_(restore); }

void CEnvGlobal::Spawn() { Spawn_(); }
void CEnvGlobal::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CEnvGlobal::Save(CSave &save) { return Save_(save); }
int CEnvGlobal::Restore(CRestore &restore) { return Restore_(restore); }
void CEnvGlobal::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CMultiSource::Spawn() { Spawn_(); }
void CMultiSource::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CMultiSource::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
BOOL CMultiSource::IsTriggered(CBaseEntity *pActivator) { return IsTriggered_(pActivator); }
int CMultiSource::Save(CSave &save) { return Save_(save); }
int CMultiSource::Restore(CRestore &restore) { return Restore_(restore); }

void CRotButton::Spawn() { Spawn_(); }

void CMomentaryRotButton::Spawn() { Spawn_(); }
void CMomentaryRotButton::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CMomentaryRotButton::Save(CSave &save) { return Save_(save); }
int CMomentaryRotButton::Restore(CRestore &restore) { return Restore_(restore); }
void CMomentaryRotButton::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CEnvSpark::Spawn() { Spawn_(); }
void CEnvSpark::Precache() { Precache_(); }
void CEnvSpark::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CEnvSpark::Save(CSave &save) { return Save_(save); }
int CEnvSpark::Restore(CRestore &restore) { return Restore_(restore); }

void CButtonTarget::Spawn() { Spawn_(); }
int CButtonTarget::ObjectCaps() { return ObjectCaps_(); }
int CButtonTarget::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
void CButtonTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// career
void CCareerTask::OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim) { OnEvent_(event, pAttacker, pVictim); }
void CCareerTask::Reset() { Reset_(); }

void CPreventDefuseTask::OnEvent(GameEventType event, CBasePlayer *pAttacker, CBasePlayer *pVictim) { OnEvent_(event, pAttacker, pVictim); }
void CPreventDefuseTask::Reset() { Reset_(); }

// cbase
int CBaseEntity::Save(CSave &save) { return Save_(save); }
int CBaseEntity::Restore(CRestore &restore) { return Restore_(restore); }
void CBaseEntity::SetObjectCollisionBox() { SetObjectCollisionBox_(); }
void CBaseEntity::TraceAttack(entvars_t *pevAttacker,float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType) { TraceAttack_(pevAttacker,flDamage,vecDir,ptr,bitsDamageType); }
int CBaseEntity::TakeDamage(entvars_t *pevInflictor,entvars_t *pevAttacker,float flDamage,int bitsDamageType) { return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType); }
int CBaseEntity::TakeHealth(float flHealth,int bitsDamageType) { return TakeHealth_(flHealth, bitsDamageType); }
void CBaseEntity::Killed(entvars_t *pevAttacker,int iGib) { Killed_(pevAttacker,iGib); }
void CBaseEntity::TraceBleed(float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType) { TraceBleed_(flDamage,vecDir,ptr,bitsDamageType); }
int CBaseEntity::DamageDecal(int bitsDamageType) { return DamageDecal_(bitsDamageType); }
BOOL CBaseEntity::IsInWorld() { return IsInWorld_(); }
CBaseEntity *CBaseEntity::GetNextTarget() { return GetNextTarget_(); }
BOOL CBaseEntity::FVisible(CBaseEntity *pEntity) { return FVisible_(pEntity); }
BOOL CBaseEntity::FVisible(const Vector &vecOrigin) { return FVisible_(vecOrigin); }

// combat
void CBaseMonster::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CBaseMonster::TraceAttack(entvars_t *pevAttacker,float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType) { TraceAttack_(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
int CBaseMonster::TakeDamage(entvars_t *pevInflictor,entvars_t *pevAttacker,float flDamage,int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
int CBaseMonster::TakeHealth(float flHealth,int bitsDamageType) { return TakeHealth_(flHealth, bitsDamageType); }
void CBaseMonster::Killed(entvars_t *pevAttacker,int iGib) { Killed_(pevAttacker, iGib); }
float CBaseMonster::ChangeYaw(int speed) { return ChangeYaw_(speed); }
BOOL CBaseMonster::HasHumanGibs() { return HasHumanGibs_(); }
BOOL CBaseMonster::HasAlienGibs() { return HasHumanGibs_(); }
void CBaseMonster::FadeMonster() { FadeMonster_(); }
void CBaseMonster::GibMonster() { GibMonster_(); }
Activity CBaseMonster::GetDeathActivity() { return GetDeathActivity_(); }
void CBaseMonster::BecomeDead() { BecomeDead_(); }
BOOL CBaseMonster::ShouldFadeOnDeath() { return ShouldFadeOnDeath_(); }
int CBaseMonster::IRelationship(CBaseEntity *pTarget) { return IRelationship_(pTarget); }
void CBaseMonster::MonsterInitDead() { MonsterInitDead_(); }
void CBaseMonster::Look(int iDistance) { Look_(iDistance); }
CBaseEntity *CBaseMonster::BestVisibleEnemy() { return BestVisibleEnemy_(); }
BOOL CBaseMonster::FInViewCone(CBaseEntity *pEntity) { return FInViewCone_(pEntity); }
BOOL CBaseMonster::FInViewCone(const Vector *pOrigin) { return FInViewCone_(pOrigin); }

// doors
void CBaseDoor::Spawn() { Spawn_(); }
void CBaseDoor::Precache() { Precache_(); }
void CBaseDoor::Restart() { Restart_(); }
void CBaseDoor::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBaseDoor::Save(CSave &save) { return Save_(save); }
int CBaseDoor::Restore(CRestore &restore) { return Restore_(restore); }
void CBaseDoor::SetToggleState(int state) { SetToggleState_(state); }
void CBaseDoor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CBaseDoor::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }
void CRotDoor::Spawn() { Spawn_(); }
void CRotDoor::Restart() { Restart_(); }
void CRotDoor::SetToggleState(int state) { SetToggleState_(state); }
void CMomentaryDoor::Spawn() { Spawn_(); }
void CMomentaryDoor::Precache() { Precache_(); }
void CMomentaryDoor::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CMomentaryDoor::Save(CSave &save) { return Save_(save); }
int CMomentaryDoor::Restore(CRestore &restore) { return Restore_(restore); }
void CMomentaryDoor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// effects
void CBombGlow::Spawn() { Spawn_(); }
void CBombGlow::Think() { Think_(); }

void CSprite::Spawn() { Spawn_(); }
void CSprite::Precache() { Precache_(); }
void CSprite::Restart() { Restart_(); }
int CSprite::Save(CSave &save) { return Save_(save); }
int CSprite::Restore(CRestore &restore) { return Restore_(restore); }
void CSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CBeam::Spawn() { Spawn_(); }
void CBeam::Precache() { Precache_(); }

void CLaser::Spawn() { Spawn_(); }
void CLaser::Precache() { Precache_(); }
void CLaser::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CLaser::Save(CSave &save) { return Save_(save); }
int CLaser::Restore(CRestore &restore) { return Restore_(restore); }
void CLaser::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CBubbling::Spawn() { Spawn_(); }
void CBubbling::Precache() { Precache_(); }
void CBubbling::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBubbling::Save(CSave &save) { return Save_(save); }
int CBubbling::Restore(CRestore &restore) { return Restore_(restore); }
void CBubbling::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CLightning::Spawn() { Spawn_(); }
void CLightning::Precache() { Precache_(); }
void CLightning::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CLightning::Save(CSave &save) { return Save_(save); }
int CLightning::Restore(CRestore &restore) { return Restore_(restore); }
void CLightning::Activate() { Activate_(); }

void CGlow::Spawn() { Spawn_(); }
int CGlow::Save(CSave &save) { return Save_(save); }
int CGlow::Restore(CRestore &restore) { return Restore_(restore); }
void CGlow::Think() { Think_(); }

void CGibShooter::Spawn() { Spawn_(); }
void CGibShooter::Precache() { Precache_(); }
void CGibShooter::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CGibShooter::Save(CSave &save) { return Save_(save); }
int CGibShooter::Restore(CRestore &restore) { return Restore_(restore); }
void CGibShooter::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
CGib *CGibShooter::CreateGib() { return CreateGib_(); }

void CEnvShooter::Precache() { Precache_(); }
void CEnvShooter::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
CGib *CEnvShooter::CreateGib() { return CreateGib_(); }

void CTestEffect::Spawn() { Spawn_(); }
void CTestEffect::Precache() { Precache_(); }
void CTestEffect::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CBlood::Spawn() { Spawn_(); }
void CBlood::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CBlood::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CShake::Spawn() { Spawn_(); }
void CShake::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CShake::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CFade::Spawn() { Spawn_(); }
void CFade::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CFade::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CMessage::Spawn() { Spawn_(); }
void CMessage::Precache() { Precache_(); }
void CMessage::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CMessage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CEnvFunnel::Spawn() { Spawn_(); }
void CEnvFunnel::Precache() { Precache_(); }
void CEnvFunnel::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CEnvBeverage::Spawn() { Spawn_(); }
void CEnvBeverage::Precache() { Precache_(); }
void CEnvBeverage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CItemSoda::Spawn() { Spawn_(); }
void CItemSoda::Precache() { Precache_(); }

// explode
void CShower::Spawn() { Spawn_(); }
void CShower::Think() { Think_(); }
void CShower::Touch(CBaseEntity *pOther) { Touch_(pOther); }

void CEnvExplosion::Spawn() { Spawn_(); }
void CEnvExplosion::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CEnvExplosion::Save(CSave &save) { return Save_(save); }
int CEnvExplosion::Restore(CRestore &restore) { return Restore_(restore); }
void CEnvExplosion::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// func_break
void CBreakable::Spawn() { Spawn_(); }
void CBreakable::Precache() { Precache_(); }
void CBreakable::Restart() { Restart_(); }
void CBreakable::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBreakable::Save(CSave &save) { return Save_(save); }
int CBreakable::Restore(CRestore &restore) { return Restore_(restore); }
void CBreakable::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { TraceAttack_(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
int CBreakable::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
int CBreakable::DamageDecal(int bitsDamageType) { return DamageDecal_(bitsDamageType); }
void CBreakable::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CPushable::Spawn() { Spawn_(); }
void CPushable::Precache() { Precache_(); }
void CPushable::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CPushable::Save(CSave &save) { return Save_(save); }
int CPushable::Restore(CRestore &restore) { return Restore_(restore); }
int CPushable::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
void CPushable::Touch(CBaseEntity *pOther) { Touch_(pOther); }
void CPushable::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// func_tank
void CFuncTank::Spawn() { Spawn_(); }
void CFuncTank::Precache() { Precache_(); }
void CFuncTank::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncTank::Save(CSave &save) { return Save_(save); }
int CFuncTank::Restore(CRestore &restore) { return Restore_(restore); }
BOOL CFuncTank::OnControls(entvars_t *pevTest) { OnControls_(pevTest); }
void CFuncTank::Think() { Think_(); }
void CFuncTank::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CFuncTank::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { Fire_(barrelEnd, forward, pevAttacker); }

void CFuncTankGun::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { Fire_(barrelEnd, forward, pevAttacker); }

void CFuncTankLaser::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncTankLaser::Save(CSave &save) { return Save_(save); }
int CFuncTankLaser::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncTankLaser::Activate() { Activate_(); }
void CFuncTankLaser::Think() { Think_(); }
void CFuncTankLaser::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { Fire_(barrelEnd, forward, pevAttacker); }

void CFuncTankRocket::Precache() { Precache_(); }
void CFuncTankRocket::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { Fire_(barrelEnd, forward, pevAttacker); }

void CFuncTankMortar::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CFuncTankMortar::Fire(const Vector &barrelEnd, const Vector &forward, entvars_t *pevAttacker) { Fire_(barrelEnd, forward, pevAttacker); }

void CFuncTankControls::Spawn() { Spawn_(); }
int CFuncTankControls::Save(CSave &save) { return Save_(save); }
int CFuncTankControls::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncTankControls::Think() { Think_(); }
void CFuncTankControls::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// gamerules
void CGameRules::RefreshSkillData() { RefreshSkillData_(); }
edict_t *CGameRules::GetPlayerSpawnSpot(CBasePlayer *pPlayer) { return GetPlayerSpawnSpot_(pPlayer); }
BOOL CGameRules::CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) { return CanHavePlayerItem_(pPlayer, pWeapon); }
BOOL CGameRules::CanHaveAmmo(CBasePlayer *pPlayer, const char *pszAmmoName, int iMaxCarry) { return CanHaveAmmo_(pPlayer, pszAmmoName, iMaxCarry); }

// grenade
void CGrenade::Spawn() { Spawn_(); }
int CGrenade::Save(CSave &save) { Save_(save); }
int CGrenade::Restore(CRestore &restore) { Restore_(restore); }
void CGrenade::Killed(entvars_t *pevAttacker, int iGib) { Killed_(pevAttacker, iGib); }
void CGrenade::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CGrenade::BounceSound() { BounceSound_(); }

// h_battery
void CRecharge::Spawn() { Spawn_(); }
void CRecharge::Precache() { Precache_(); }
void CRecharge::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CRecharge::Save(CSave &save) { return Save_(save); }
int CRecharge::Restore(CRestore &restore) { return Restore_(restore); }
void CRecharge::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// h_cycler
void CWreckage::Spawn() { Spawn_(); }
void CWreckage::Precache() { Precache_(); }
int CWreckage::Save(CSave &save) { return Save_(save); }
int CWreckage::Restore(CRestore &restore) { return Restore_(restore); }
void CWreckage::Think() { Think_(); }

void CWeaponCycler::Spawn() { Spawn_(); }
BOOL CWeaponCycler::Deploy() { return Deploy_(); }
void CWeaponCycler::Holster(int skiplocal) { Holster_(skiplocal); }
void CWeaponCycler::PrimaryAttack() { PrimaryAttack_(); }
void CWeaponCycler::SecondaryAttack() { SecondaryAttack_(); }

void CCyclerSprite::Spawn() { Spawn_(); }
void CCyclerSprite::Restart() { Restart_(); }
int CCyclerSprite::Save(CSave &save) { return Save_(save); }
int CCyclerSprite::Restore(CRestore &restore) { return Restore_(restore); }
int CCyclerSprite::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType); }
void CCyclerSprite::Think() { Think_(); }
void CCyclerSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator,pCaller,useType,value); }

void CCycler::Spawn() { Spawn_(); }
int CCycler::Save(CSave &save) { return Save_(save); }
int CCycler::Restore(CRestore &restore) { return Restore_(restore); }
int CCycler::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType); }
void CCycler::Think() { Think_(); }
void CCycler::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator,pCaller,useType,value); }

void CGenericCycler::Spawn() { Spawn_(); }

void CCyclerProbe::Spawn() { Spawn_(); }

// healthkit
void CHealthKit::Spawn() { Spawn_(); }
void CHealthKit::Precache() { Precache_(); }
BOOL CHealthKit::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CWallHealth::Spawn() { Spawn_(); }
void CWallHealth::Precache() { Precache_(); }
void CWallHealth::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CWallHealth::Save(CSave &save) { return Save_(save); }
int CWallHealth::Restore(CRestore &restore) { return Restore_(restore); }
void CWallHealth::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// items
void CItem::Spawn() { Spawn_(); }
CBaseEntity *CItem::Respawn() { return Respawn_(); }

void CWorldItem::Spawn() { Spawn_(); }
void CWorldItem::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CItemSuit::Spawn() { Spawn_(); }
void CItemSuit::Precache() { Precache_(); }
BOOL CItemSuit::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemBattery::Spawn() { Spawn_(); }
void CItemBattery::Precache() { Precache_(); }
BOOL CItemBattery::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemAntidote::Spawn() { Spawn_(); }
void CItemAntidote::Precache() { Precache_(); }
BOOL CItemAntidote::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemSecurity::Spawn() { Spawn_(); }
void CItemSecurity::Precache() { Precache_(); }
BOOL CItemSecurity::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemLongJump::Spawn() { Spawn_(); }
void CItemLongJump::Precache() { Precache_(); }
BOOL CItemLongJump::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemKevlar::Spawn() { Spawn_(); }
void CItemKevlar::Precache() { Precache_(); }
BOOL CItemKevlar::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemAssaultSuit::Spawn() { Spawn_(); }
void CItemAssaultSuit::Precache() { Precache_(); }
BOOL CItemAssaultSuit::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

void CItemThighPack::Spawn() { Spawn_(); }
void CItemThighPack::Precache() { Precache_(); }
BOOL CItemThighPack::MyTouch(CBasePlayer *pPlayer) { return MyTouch_(pPlayer); }

// lights
void CLight::Spawn() { Spawn_(); }
void CLight::Restart() { Restart_(); }
int CLight::Save(CSave &save) { return Save_(save); }
int CLight::Restore(CRestore &restore) { return Restore_(restore); }
void CLight::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CLight::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CEnvLight::Spawn() { Spawn_(); }
void CEnvLight::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

// maprules
void CRuleEntity::Spawn() { Spawn_(); }
void CRuleEntity::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CRuleEntity::Save(CSave &save) { return Save_(save); }
int CRuleEntity::Restore(CRestore &restore) { return Restore_(restore); }

void CRulePointEntity::Spawn() { Spawn_(); }

void CRuleBrushEntity::Spawn() { Spawn_(); }

void CGameScore::Spawn() { Spawn_(); }
void CGameScore::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CGameScore::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGameEnd::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGameText::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CGameText::Save(CSave &save) { return Save_(save); }
int CGameText::Restore(CRestore &restore) { return Restore_(restore); }
void CGameText::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGameTeamMaster::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
BOOL CGameTeamMaster::IsTriggered(CBaseEntity *pActivator) { return IsTriggered_(pActivator); }
const char *CGameTeamMaster::TeamID() { return TeamID_(); }
void CGameTeamMaster::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGameTeamSet::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGamePlayerZone::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CGamePlayerZone::Save(CSave &save) { return Save_(save); }
int CGamePlayerZone::Restore(CRestore &restore) { return Restore_(restore); }
void CGamePlayerZone::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGamePlayerHurt::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGameCounter::Spawn() { Spawn_(); }
void CGameCounter::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGameCounterSet::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGamePlayerEquip::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CGamePlayerEquip::Touch(CBaseEntity *pOther) { Touch_(pOther); }
void CGamePlayerEquip::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CGamePlayerTeam::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// mortar
void CFuncMortarField::Spawn() { Spawn_(); }
void CFuncMortarField::Precache() { Precache_(); }
void CFuncMortarField::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncMortarField::Save(CSave &save) { return Save_(save); }
int CFuncMortarField::Restore(CRestore &restore) { return Restore_(restore); }

void CMortar::Spawn() { Spawn_(); }
void CMortar::Precache() { Precache_(); }

// multiplay_gamerules
void CMapInfo::Spawn() { Spawn_(); }
void CMapInfo::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

bool CCStrikeGameMgrHelper::CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pSender) { return CanPlayerHearPlayer_(pListener, pSender); }

void CHalfLifeMultiplay::RefreshSkillData() { RefreshSkillData_(); }
void CHalfLifeMultiplay::Think() { Think_(); }
BOOL CHalfLifeMultiplay::IsAllowedToSpawn(CBaseEntity *pEntity) { return IsAllowedToSpawn_(pEntity); }
BOOL CHalfLifeMultiplay::FAllowFlashlight() { return FAllowFlashlight_(); }
BOOL CHalfLifeMultiplay::FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) { return FShouldSwitchWeapon_(pPlayer, pWeapon); }
BOOL CHalfLifeMultiplay::GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) { return GetNextBestWeapon_(pPlayer, pCurrentWeapon); }
BOOL CHalfLifeMultiplay::IsMultiplayer() { return IsMultiplayer_(); }
BOOL CHalfLifeMultiplay::IsDeathmatch() { return IsDeathmatch_(); }
BOOL CHalfLifeMultiplay::IsCoOp() { return IsCoOp_(); }
BOOL CHalfLifeMultiplay::ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]) { return ClientConnected_(pEntity, pszName, pszAddress, szRejectReason); }
void CHalfLifeMultiplay::InitHUD(CBasePlayer *pl) { InitHUD_(pl); }
void CHalfLifeMultiplay::ClientDisconnected(edict_t *pClient) { ClientDisconnected_(pClient); }
void CHalfLifeMultiplay::UpdateGameMode(CBasePlayer *pPlayer) { UpdateGameMode_(pPlayer); }
float CHalfLifeMultiplay::FlPlayerFallDamage(CBasePlayer *pPlayer) { return FlPlayerFallDamage_(pPlayer); }
BOOL CHalfLifeMultiplay::FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker) { return FPlayerCanTakeDamage_(pPlayer, pAttacker); }
void CHalfLifeMultiplay::PlayerSpawn(CBasePlayer *pPlayer) { PlayerSpawn_(pPlayer); }
void CHalfLifeMultiplay::PlayerThink(CBasePlayer *pPlayer) { PlayerThink_(pPlayer); }
BOOL CHalfLifeMultiplay::FPlayerCanRespawn(CBasePlayer *pPlayer) { return FPlayerCanRespawn_(pPlayer); }
float CHalfLifeMultiplay::FlPlayerSpawnTime(CBasePlayer *pPlayer) { return FlPlayerSpawnTime_(pPlayer); }
edict_t *CHalfLifeMultiplay::GetPlayerSpawnSpot(CBasePlayer *pPlayer) { return GetPlayerSpawnSpot_(pPlayer); }
BOOL CHalfLifeMultiplay::AllowAutoTargetCrosshair() { return AllowAutoTargetCrosshair_(); }
BOOL CHalfLifeMultiplay::ClientCommand_DeadOrAlive(CBasePlayer *pPlayer, const char *pcmd) { return ClientCommand_DeadOrAlive_(pPlayer, pcmd); }
BOOL CHalfLifeMultiplay::ClientCommand(CBasePlayer *pPlayer, const char *pcmd) { return ClientCommand_(pPlayer, pcmd); }
void CHalfLifeMultiplay::ClientUserInfoChanged(CBasePlayer *pPlayer, char *infobuffer) { ClientUserInfoChanged_(pPlayer, infobuffer); }
int CHalfLifeMultiplay::IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) { return IPointsForKill_(pAttacker, pKilled); }
void CHalfLifeMultiplay::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) { PlayerKilled_(pVictim, pKiller, pInflictor); }
void CHalfLifeMultiplay::DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) { DeathNotice_(pVictim, pKiller, pInflictor); }
BOOL CHalfLifeMultiplay::CanHavePlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) { return CanHavePlayerItem_(pPlayer, pWeapon); }
void CHalfLifeMultiplay::PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) { PlayerGotWeapon_(pPlayer, pWeapon); }
int CHalfLifeMultiplay::WeaponShouldRespawn(CBasePlayerItem *pWeapon) { return WeaponShouldRespawn_(pWeapon); }
float CHalfLifeMultiplay::FlWeaponRespawnTime(CBasePlayerItem *pWeapon) { return FlWeaponRespawnTime_(pWeapon); }
float CHalfLifeMultiplay::FlWeaponTryRespawn(CBasePlayerItem *pWeapon) { return FlWeaponTryRespawn_(pWeapon); }
Vector CHalfLifeMultiplay::VecWeaponRespawnSpot(CBasePlayerItem *pWeapon) { return VecWeaponRespawnSpot_(pWeapon); }
BOOL CHalfLifeMultiplay::CanHaveItem(CBasePlayer *pPlayer, CItem *pItem) { return CanHaveItem_(pPlayer, pItem); }
void CHalfLifeMultiplay::PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem) { PlayerGotItem_(pPlayer, pItem); }
int CHalfLifeMultiplay::ItemShouldRespawn(CItem *pItem) { return ItemShouldRespawn_(pItem); }
float CHalfLifeMultiplay::FlItemRespawnTime(CItem *pItem) { return FlItemRespawnTime_(pItem); }
Vector CHalfLifeMultiplay::VecItemRespawnSpot(CItem *pItem) { return VecItemRespawnSpot_(pItem); }
void CHalfLifeMultiplay::PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount) { PlayerGotAmmo_(pPlayer, szName, iCount); }
int CHalfLifeMultiplay::AmmoShouldRespawn(CBasePlayerAmmo *pAmmo) { return AmmoShouldRespawn_(pAmmo); }
float CHalfLifeMultiplay::FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo) { return FlAmmoRespawnTime_(pAmmo); }
Vector CHalfLifeMultiplay::VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo) { return VecAmmoRespawnSpot_(pAmmo); }
float CHalfLifeMultiplay::FlHealthChargerRechargeTime() { return FlHealthChargerRechargeTime_(); }
float CHalfLifeMultiplay::FlHEVChargerRechargeTime() { return FlHEVChargerRechargeTime_(); }
int CHalfLifeMultiplay::DeadPlayerWeapons(CBasePlayer *pPlayer) { return DeadPlayerWeapons_(pPlayer); }
int CHalfLifeMultiplay::DeadPlayerAmmo(CBasePlayer *pPlayer) { return DeadPlayerAmmo_(pPlayer); }
int CHalfLifeMultiplay::PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) { return PlayerRelationship_(pPlayer, pTarget); }
BOOL CHalfLifeMultiplay::FAllowMonsters() { return FAllowMonsters_(); }
void CHalfLifeMultiplay::ServerDeactivate() { ServerDeactivate_(); }
void CHalfLifeMultiplay::CheckMapConditions() { CheckMapConditions_(); }
void CHalfLifeMultiplay::CleanUpMap() { CleanUpMap_(); }
void CHalfLifeMultiplay::RestartRound() { RestartRound_(); }
void CHalfLifeMultiplay::CheckWinConditions() { CheckWinConditions_(); }
void CHalfLifeMultiplay::RemoveGuns() { RemoveGuns_(); }
void CHalfLifeMultiplay::GiveC4() { GiveC4_(); }
void CHalfLifeMultiplay::ChangeLevel() { ChangeLevel_(); }
void CHalfLifeMultiplay::GoToIntermission() { GoToIntermission_(); }

// pathcorner
void CPathCorner::Spawn() { Spawn_(); }
void CPathCorner::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CPathCorner::Save(CSave &save) { return Save_(save); }
int CPathCorner::Restore(CRestore &restore) { return Restore_(restore); }

void CPathTrack::Spawn() { Spawn_(); }
void CPathTrack::KeyValue(KeyValueData* pkvd) { KeyValue_(pkvd); }
int CPathTrack::Save(CSave &save) { return Save_(save); }
int CPathTrack::Restore(CRestore &restore) { return Restore_(restore); }
void CPathTrack::Activate() { Activate_(); }
void CPathTrack::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// plats
void CBasePlatTrain::Precache() { Precache_(); }
void CBasePlatTrain::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBasePlatTrain::Save(CSave &save) { return Save_(save); }
int CBasePlatTrain::Restore(CRestore &restore) { return Restore_(restore); }

void CFuncPlat::Spawn() { Spawn_(); }
void CFuncPlat::Precache() { Precache_(); }
void CFuncPlat::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }
void CFuncPlat::GoUp() { GoUp_(); }
void CFuncPlat::GoDown() { GoDown_(); }
void CFuncPlat::HitTop() { HitTop_(); }
void CFuncPlat::HitBottom() { HitBottom_(); }

void CPlatTrigger::Touch(CBaseEntity *pOther) { Touch_(pOther); }

void CFuncPlatRot::Spawn() { Spawn_(); }
int CFuncPlatRot::Save(CSave &save) { return Save_(save); }
int CFuncPlatRot::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncPlatRot::GoUp() { GoUp_(); }
void CFuncPlatRot::GoDown() { GoDown_(); }
void CFuncPlatRot::HitTop() { HitTop_(); }
void CFuncPlatRot::HitBottom() { HitBottom_(); }

void CFuncTrain::Spawn() { Spawn_(); }
void CFuncTrain::Precache() { Precache_(); }
void CFuncTrain::Restart() { Restart_(); }
void CFuncTrain::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncTrain::Save(CSave &save) { return Save_(save); }
int CFuncTrain::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncTrain::Activate() { Activate_(); }
void CFuncTrain::OverrideReset() { OverrideReset_(); }
void CFuncTrain::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CFuncTrain::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }

void CFuncTrackTrain::Spawn() { Spawn_(); }
void CFuncTrackTrain::Precache() { Precache_(); }
void CFuncTrackTrain::Restart() { Restart_(); }
void CFuncTrackTrain::KeyValue(KeyValueData* pkvd) { KeyValue_(pkvd); }
int CFuncTrackTrain::Save(CSave &save) { return Save_(save); }
int CFuncTrackTrain::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncTrackTrain::OverrideReset() { OverrideReset_(); }
BOOL CFuncTrackTrain::OnControls(entvars_t *pev) { return OnControls_(pev); }
void CFuncTrackTrain::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CFuncTrackTrain::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }

void CFuncTrainControls::Spawn() { Spawn_(); }

void CFuncTrackChange::Spawn() { Spawn_(); }
void CFuncTrackChange::Precache() { Precache_(); }
void CFuncTrackChange::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncTrackChange::Save(CSave &save) { return Save_(save); }
int CFuncTrackChange::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncTrackChange::OverrideReset() { OverrideReset_(); }
void CFuncTrackChange::Touch(CBaseEntity *pOther) { Touch_(pOther); }
void CFuncTrackChange::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
BOOL CFuncTrackChange::IsTogglePlat() { return IsTogglePlat_(); }
void CFuncTrackChange::GoUp() { GoUp_(); }
void CFuncTrackChange::GoDown() { GoDown_(); }
void CFuncTrackChange::HitBottom() { HitBottom_(); }
void CFuncTrackChange::HitTop() { HitTop_(); }
void CFuncTrackChange::UpdateAutoTargets(int toggleState) { UpdateAutoTargets_(toggleState); }

void CFuncTrackAuto::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CFuncTrackAuto::UpdateAutoTargets(int toggleState) { UpdateAutoTargets_(toggleState); }

void CGunTarget::Spawn() { Spawn_(); }
int CGunTarget::Save(CSave &save) { return Save_(save); }
int CGunTarget::Restore(CRestore &restore) { return Restore_(restore); }
void CGunTarget::Activate() { Activate_(); }
int CGunTarget::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
void CGunTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// player
void CBasePlayer::Spawn() { Spawn_(); }
void CBasePlayer::Precache() { Precache_(); }
int CBasePlayer::Save(CSave &save) { return Save_(save); }
int CBasePlayer::Restore(CRestore &restore) { return Restore_(restore); }
int CBasePlayer::Classify() { return Classify_(); }
void CBasePlayer::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType) { TraceAttack_(pevAttacker, flDamage, vecDir, ptr, bitsDamageType); }
int CBasePlayer::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
int CBasePlayer::TakeHealth(float flHealth, int bitsDamageType) { return TakeHealth_(flHealth, bitsDamageType); }
void CBasePlayer::Killed(entvars_t *pevAttacker, int iGib) { Killed_(pevAttacker, iGib); }
void CBasePlayer::AddPoints(int score, BOOL bAllowNegativeScore) { AddPoints_(score, bAllowNegativeScore); }
void CBasePlayer::AddPointsToTeam(int score, BOOL bAllowNegativeScore) { AddPointsToTeam_(score, bAllowNegativeScore); }
BOOL CBasePlayer::AddPlayerItem(CBasePlayerItem *pItem) { return AddPlayerItem_(pItem); }
BOOL CBasePlayer::RemovePlayerItem(CBasePlayerItem *pItem) { return RemovePlayerItem_(pItem); }
int CBasePlayer::GiveAmmo(int iAmount, char *szName, int iMax) { return GiveAmmo_(iAmount, szName, iMax); }
const char *CBasePlayer::TeamID() { return TeamID_(); }
BOOL CBasePlayer::FBecomeProne() { return FBecomeProne_(); }
int CBasePlayer::Illumination() { return Illumination_(); }
void CBasePlayer::ResetMaxSpeed() { ResetMaxSpeed_(); }
void CBasePlayer::Jump() { Jump_(); }
void CBasePlayer::Duck() { Duck_(); }
void CBasePlayer::PreThink() { PreThink_(); }
void CBasePlayer::PostThink() { PostThink_(); }
Vector CBasePlayer::GetGunPosition() { return GetGunPosition_(); }
void CBasePlayer::UpdateClientData() { UpdateClientData_(); }
void CBasePlayer::ImpulseCommands() { ImpulseCommands_(); }
void CBasePlayer::RoundRespawn() { RoundRespawn_(); }
Vector CBasePlayer::GetAutoaimVector(float flDelta) { return GetAutoaimVector_(flDelta); }
void CBasePlayer::Blind(float flUntilTime, float flHoldTime, float flFadeTime, int iAlpha) { Blind_(flUntilTime, flHoldTime, flFadeTime, iAlpha); }

void CStripWeapons::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CRevertSaved::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CRevertSaved::Save(CSave &save) { return Save_(save); }
int CRevertSaved::Restore(CRestore &restore) { return Restore_(restore); }
void CRevertSaved::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CDeadHEV::Spawn() { Spawn_(); }
void CDeadHEV::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CDeadHEV::Classify() { return Classify_(); }

void CSprayCan::Think() { Think_(); }

void CInfoIntermission::Spawn() { Spawn_(); }
void CInfoIntermission::Think() { Think_(); }

void CWShield::Spawn() { Spawn_(); }
void CWShield::Touch(CBaseEntity *pOther) { Touch_(pOther); }

// singleplay_gamerules
void CHalfLifeRules::Think() { Think_(); }
BOOL CHalfLifeRules::IsAllowedToSpawn(CBaseEntity *pEntity) { return IsAllowedToSpawn_(pEntity); }
BOOL CHalfLifeRules::FShouldSwitchWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) { return FShouldSwitchWeapon_(pPlayer, pWeapon); }
BOOL CHalfLifeRules::GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon) { return GetNextBestWeapon_(pPlayer, pCurrentWeapon); }
BOOL CHalfLifeRules::IsMultiplayer() { return IsMultiplayer_(); }
BOOL CHalfLifeRules::IsDeathmatch() { return IsDeathmatch_(); }
BOOL CHalfLifeRules::IsCoOp() { return IsCoOp_(); }
BOOL CHalfLifeRules::ClientConnected(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]) { return ClientConnected_(pEntity, pszName, pszAddress, szRejectReason); }
void CHalfLifeRules::InitHUD(CBasePlayer *pl) { InitHUD_(pl); }
void CHalfLifeRules::ClientDisconnected(edict_t *pClient) { ClientDisconnected_(pClient); }
float CHalfLifeRules::FlPlayerFallDamage(CBasePlayer *pPlayer) { return FlPlayerFallDamage_(pPlayer); }
void CHalfLifeRules::PlayerSpawn(CBasePlayer *pPlayer) { PlayerSpawn_(pPlayer); }
void CHalfLifeRules::PlayerThink(CBasePlayer *pPlayer) { PlayerThink_(pPlayer); }
BOOL CHalfLifeRules::FPlayerCanRespawn(CBasePlayer *pPlayer) { return FPlayerCanRespawn_(pPlayer); }
float CHalfLifeRules::FlPlayerSpawnTime(CBasePlayer *pPlayer) { return FlPlayerSpawnTime_(pPlayer); }
edict_t *CHalfLifeRules::GetPlayerSpawnSpot(CBasePlayer *pPlayer) { return GetPlayerSpawnSpot_(pPlayer); }
BOOL CHalfLifeRules::AllowAutoTargetCrosshair() { return AllowAutoTargetCrosshair_(); }
int CHalfLifeRules::IPointsForKill(CBasePlayer *pAttacker, CBasePlayer *pKilled) { return IPointsForKill_(pAttacker, pKilled); }
void CHalfLifeRules::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) { PlayerKilled_(pVictim, pKiller, pInflictor); }
void CHalfLifeRules::DeathNotice(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) { DeathNotice_(pVictim, pKiller, pInflictor); }
void CHalfLifeRules::PlayerGotWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pWeapon) { PlayerGotWeapon_(pPlayer, pWeapon); }
int CHalfLifeRules::WeaponShouldRespawn(CBasePlayerItem *pWeapon) { return WeaponShouldRespawn_(pWeapon); }
float CHalfLifeRules::FlWeaponRespawnTime(CBasePlayerItem *pWeapon) { return FlWeaponRespawnTime_(pWeapon); }
float CHalfLifeRules::FlWeaponTryRespawn(CBasePlayerItem *pWeapon) { return FlWeaponTryRespawn_(pWeapon); }
Vector CHalfLifeRules::VecWeaponRespawnSpot(CBasePlayerItem *pWeapon) { return VecWeaponRespawnSpot_(pWeapon); }
BOOL CHalfLifeRules::CanHaveItem(CBasePlayer *pPlayer, CItem *pItem) { return CanHaveItem_(pPlayer, pItem); }
void CHalfLifeRules::PlayerGotItem(CBasePlayer *pPlayer, CItem *pItem) { PlayerGotItem_(pPlayer, pItem); }
int CHalfLifeRules::ItemShouldRespawn(CItem *pItem) { return ItemShouldRespawn_(pItem); }
float CHalfLifeRules::FlItemRespawnTime(CItem *pItem) { return FlItemRespawnTime_(pItem); }
Vector CHalfLifeRules::VecItemRespawnSpot(CItem *pItem) { return VecItemRespawnSpot_(pItem); }
void CHalfLifeRules::PlayerGotAmmo(CBasePlayer *pPlayer, char *szName, int iCount) { PlayerGotAmmo_(pPlayer, szName, iCount); }
int CHalfLifeRules::AmmoShouldRespawn(CBasePlayerAmmo *pAmmo) { return AmmoShouldRespawn_(pAmmo); }
float CHalfLifeRules::FlAmmoRespawnTime(CBasePlayerAmmo *pAmmo) { return FlAmmoRespawnTime_(pAmmo); }
Vector CHalfLifeRules::VecAmmoRespawnSpot(CBasePlayerAmmo *pAmmo) { return VecAmmoRespawnSpot_(pAmmo); }
float CHalfLifeRules::FlHealthChargerRechargeTime() { return FlHealthChargerRechargeTime_(); }
int CHalfLifeRules::DeadPlayerWeapons(CBasePlayer *pPlayer) { return DeadPlayerWeapons_(pPlayer); }
int CHalfLifeRules::DeadPlayerAmmo(CBasePlayer *pPlayer) { return DeadPlayerAmmo_(pPlayer); }
int CHalfLifeRules::PlayerRelationship(CBasePlayer *pPlayer, CBaseEntity *pTarget) { return PlayerRelationship_(pPlayer, pTarget); }
BOOL CHalfLifeRules::FAllowMonsters() { return FAllowMonsters_(); }

// sound
void CAmbientGeneric::Spawn() { Spawn_(); }
void CAmbientGeneric::Precache() { Precache_(); }
void CAmbientGeneric::Restart() { Restart_(); }
void CAmbientGeneric::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CAmbientGeneric::Save(CSave &save) { Save_(save); }
int CAmbientGeneric::Restore(CRestore &restore) { Restore_(restore); }

void CEnvSound::Spawn() { Spawn_(); }
void CEnvSound::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CEnvSound::Save(CSave &save) { return Save_(save); }
int CEnvSound::Restore(CRestore &restore) { return Restore_(restore); }
void CEnvSound::Think() { Think_(); }

void CSpeaker::Spawn() { Spawn_(); }
void CSpeaker::Precache() { Precache_(); }
void CSpeaker::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CSpeaker::Save(CSave &save) { return Save_(save); }
int CSpeaker::Restore(CRestore &restore) { return Restore_(restore); }

// soundent
void CSoundEnt::Spawn() { Spawn_(); }
void CSoundEnt::Precache() { Precache_(); }
void CSoundEnt::Think() { Think_(); }

// spectator
void CBaseSpectator::Spawn() { Spawn_(); }

// subs
void CNullEntity::Spawn() { Spawn_(); }

void CPointEntity::Spawn() { Spawn_(); }

void CBaseDelay::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBaseDelay::Save(CSave &save) { return Save_(save); }
int CBaseDelay::Restore(CRestore &restore) { return Restore_(restore); }

void CBaseToggle::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBaseToggle::Save(CSave &save) { return Save_(save); }
int CBaseToggle::Restore(CRestore &restore) { return Restore_(restore); }

void CBaseDMStart::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
BOOL CBaseDMStart::IsTriggered(CBaseEntity *pEntity) { return IsTriggered_(pEntity); }

// training_gamerules
void CBaseGrenCatch::Spawn() { Spawn_(); }
void CBaseGrenCatch::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CBaseGrenCatch::Save(CSave &save) { return Save_(save); }
int CBaseGrenCatch::Restore(CRestore &restore) { return Restore_(restore); }
void CBaseGrenCatch::Think() { Think_(); }
void CBaseGrenCatch::Touch(CBaseEntity *pOther) { Touch_(pOther); }

void CFuncWeaponCheck::Spawn() { Spawn_(); }
void CFuncWeaponCheck::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncWeaponCheck::Save(CSave &save) { return Save_(save); }
int CFuncWeaponCheck::Restore(CRestore &restore) { return Restore_(restore); }
void CFuncWeaponCheck::Touch(CBaseEntity *pOther) { Touch_(pOther); }

BOOL CHalfLifeTraining::IsDeathmatch() { return IsDeathmatch_(); }
void CHalfLifeTraining::InitHUD(CBasePlayer *pl) { InitHUD_(pl); }
void CHalfLifeTraining::PlayerSpawn(CBasePlayer *pPlayer) { PlayerSpawn_(pPlayer); }
void CHalfLifeTraining::PlayerThink(CBasePlayer *pPlayer) { PlayerThink_(pPlayer); }
BOOL CHalfLifeTraining::FPlayerCanRespawn(CBasePlayer *pPlayer) { return FPlayerCanRespawn_(pPlayer); }
edict_t *CHalfLifeTraining::GetPlayerSpawnSpot(CBasePlayer *pPlayer) { return GetPlayerSpawnSpot_(pPlayer); }
void CHalfLifeTraining::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor) { PlayerKilled_(pVictim, pKiller, pInflictor); }
int CHalfLifeTraining::ItemShouldRespawn(CItem *pItem) { return ItemShouldRespawn_(pItem); }
void CHalfLifeTraining::CheckWinConditions() { CheckWinConditions_(); }

// triggers
void CFrictionModifier::Spawn() { Spawn_(); }
void CFrictionModifier::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFrictionModifier::Save(CSave &save) { return Save_(save); }
int CFrictionModifier::Restore(CRestore &restore) { return Restore_(restore); }

void CAutoTrigger::Spawn() { Spawn_(); }
void CAutoTrigger::Precache() { Precache_(); }
void CAutoTrigger::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CAutoTrigger::Save(CSave &save) { return Save_(save); }
int CAutoTrigger::Restore(CRestore &restore) { return Restore_(restore); }
void CAutoTrigger::Think() { Think_(); }

void CTriggerRelay::Spawn() { Spawn_(); }
void CTriggerRelay::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CTriggerRelay::Save(CSave &save) { return Save_(save); }
int CTriggerRelay::Restore(CRestore &restore) { return Restore_(restore); }
void CTriggerRelay::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CMultiManager::Spawn() { Spawn_(); }
void CMultiManager::Restart() { Restart_(); }
void CMultiManager::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CMultiManager::Save(CSave &save) { return Save_(save); }
int CMultiManager::Restore(CRestore &restore) { return Restore_(restore); }
BOOL CMultiManager::HasTarget(string_t targetname) { return HasTarget_(targetname); }

void CRenderFxManager::Spawn() { Spawn_(); }
void CRenderFxManager::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CBaseTrigger::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CTriggerHurt::Spawn() { Spawn_(); }

void CTriggerMonsterJump::Spawn() { Spawn_(); }
void CTriggerMonsterJump::Think() { Think_(); }
void CTriggerMonsterJump::Touch(CBaseEntity *pOther) { Touch_(pOther); }

void CTriggerCDAudio::Spawn() { Spawn_(); }
void CTriggerCDAudio::Touch(CBaseEntity *pOther) { Touch_(pOther); }
void CTriggerCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CTargetCDAudio::Spawn() { Spawn_(); }
void CTargetCDAudio::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CTargetCDAudio::Think() { Think_(); }
void CTargetCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CTriggerMultiple::Spawn() { Spawn_(); }

void CTriggerOnce::Spawn() { Spawn_(); }

void CTriggerCounter::Spawn() { Spawn_(); }

void CTriggerVolume::Spawn() { Spawn_(); }

void CFireAndDie::Spawn() { Spawn_(); }
void CFireAndDie::Precache() { Precache_(); }
void CFireAndDie::Think() { Think_(); }

void CChangeLevel::Spawn() { Spawn_(); }
void CChangeLevel::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CChangeLevel::Save(CSave &save) { return Save_(save); }
int CChangeLevel::Restore(CRestore &restore) { return Restore_(restore); }

void CLadder::Spawn() { Spawn_(); }
void CLadder::Precache() { Precache_(); }
void CLadder::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CTriggerPush::Spawn() { Spawn_(); }
void CTriggerPush::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CTriggerPush::Touch(CBaseEntity *pOther) { Touch_(pOther); }

void CTriggerTeleport::Spawn() { Spawn_(); }

void CBuyZone::Spawn() { Spawn_(); }

void CBombTarget::Spawn() { Spawn_(); }

void CHostageRescue::Spawn() { Spawn_(); }

void CEscapeZone::Spawn() { Spawn_(); }

void CVIP_SafetyZone::Spawn() { Spawn_(); }

void CTriggerSave::Spawn() { Spawn_(); }

void CTriggerEndSection::Spawn() { Spawn_(); }
void CTriggerEndSection::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CTriggerGravity::Spawn() { Spawn_(); }

void CTriggerChangeTarget::Spawn() { Spawn_(); }
void CTriggerChangeTarget::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CTriggerChangeTarget::Save(CSave &save) { return Save_(save); }
int CTriggerChangeTarget::Restore(CRestore &restore) { return Restore_(restore); }
void CTriggerChangeTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CTriggerCamera::Spawn() { Spawn_(); }
void CTriggerCamera::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CTriggerCamera::Save(CSave &save) { return Save_(save); }
int CTriggerCamera::Restore(CRestore &restore) { return Restore_(restore); }
void CTriggerCamera::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

void CClientFog::Spawn() { Spawn_(); }
void CClientFog::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CWeather::Spawn() { Spawn_(); }

// tutor_base_tutor
bool CBaseTutor::IsEntityInViewOfPlayer(CBaseEntity *entity, CBasePlayer *player) { return IsEntityInViewOfPlayer_(entity, player); }
bool CBaseTutor::IsBombsiteInViewOfPlayer(CBaseEntity *entity, CBasePlayer *player) { return IsBombsiteInViewOfPlayer_(entity, player); }
bool CBaseTutor::IsEntityInBombsite(CBaseEntity *bombsite, CBaseEntity *entity) { return IsEntityInBombsite_(bombsite, entity); }
bool CBaseTutor::IsPlayerLookingAtPosition(Vector *origin, CBasePlayer *player) { return IsPlayerLookingAtPosition_(origin, player); }
bool CBaseTutor::IsPlayerLookingAtEntity(CBaseEntity *entity, CBasePlayer *player) { return IsPlayerLookingAtEntity_(entity, player); }

// tutor_cs_states
bool CCSTutorStateSystem::UpdateState(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { return UpdateState_(event, entity, other); }
char *CCSTutorStateSystem::GetCurrentStateString() { return GetCurrentStateString_(); }
CBaseTutorState *CCSTutorStateSystem::ConstructNewState(int stateType) { return ConstructNewState_(stateType); }

int CCSTutorUndefinedState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { return CheckForStateTransition_(event, entity, other); }
char *CCSTutorUndefinedState::GetStateString() { return GetStateString_(); }

int CCSTutorWaitingForStartState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { return CheckForStateTransition_(event, entity, other); }
char *CCSTutorWaitingForStartState::GetStateString() { return GetStateString_(); }

int CCSTutorBuyMenuState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { return CheckForStateTransition_(event, entity, other); }
char *CCSTutorBuyMenuState::GetStateString() { return GetStateString_(); }

// tutor_cs_tutor
void CCSTutor::TutorThink(float time) { TutorThink_(time); }
void CCSTutor::PurgeMessages() { PurgeMessages_(); }
void CCSTutor::CallEventHandler(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { CallEventHandler_(event, entity, other); }
void CCSTutor::ShowTutorMessage(TutorMessageEvent *event) { ShowTutorMessage_(event); }
void CCSTutor::HandleShotFired(Vector source, Vector target) { HandleShotFired_(source, target); }
TutorMessage *CCSTutor::GetTutorMessageDefinition(int messageID) { return GetTutorMessageDefinition_(messageID); }

// vehicle
void CFuncVehicle::Spawn() { Spawn_(); }
void CFuncVehicle::Precache() { Precache_(); }
void CFuncVehicle::Restart() { Restart_(); }
void CFuncVehicle::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CFuncVehicle::Save(CSave &save) { return Save_(save); }
int CFuncVehicle::Restore(CRestore &restore) { return Restore_(restore); }
int CFuncVehicle::Classify() { return Classify_(); }
void CFuncVehicle::OverrideReset() { OverrideReset_(); }
BOOL CFuncVehicle::OnControls(entvars_t *pev) { return OnControls_(pev); }
void CFuncVehicle::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
void CFuncVehicle::Blocked(CBaseEntity *pOther) { Blocked_(pOther); }
void CFuncVehicleControls::Spawn() { Spawn_(); }

// weapons
void CArmoury::Spawn() { Spawn_(); }
void CArmoury::Precache() { Precache_(); }
void CArmoury::Restart() { Restart_(); }
void CArmoury::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CBasePlayerAmmo::Spawn() { Spawn_(); }
CBaseEntity *CBasePlayerAmmo::Respawn() { return Respawn_(); }

int CBasePlayerWeapon::Save(CSave &save) { return Save_(save); }
int CBasePlayerWeapon::Restore(CRestore &restore) { return Restore_(restore); }
int CBasePlayerWeapon::AddToPlayer(CBasePlayer *pPlayer) { return AddToPlayer_(pPlayer); }
int CBasePlayerWeapon::AddDuplicate(CBasePlayerItem *pItem) { return AddDuplicate_(pItem); }
BOOL CBasePlayerWeapon::CanDeploy() { return CanDeploy_(); }
void CBasePlayerWeapon::Holster(int skiplocal) { Holster_(skiplocal); }
void CBasePlayerWeapon::ItemPostFrame() { ItemPostFrame_(); }
int CBasePlayerWeapon::PrimaryAmmoIndex() { return PrimaryAmmoIndex_(); }
int CBasePlayerWeapon::SecondaryAmmoIndex() { return SecondaryAmmoIndex_(); }
int CBasePlayerWeapon::UpdateClientData(CBasePlayer *pPlayer) { return UpdateClientData_(pPlayer); }
int CBasePlayerWeapon::ExtractAmmo(CBasePlayerWeapon *pWeapon) { return ExtractAmmo_(pWeapon); }
int CBasePlayerWeapon::ExtractClipAmmo(CBasePlayerWeapon *pWeapon) { return ExtractClipAmmo_(pWeapon); }
BOOL CBasePlayerWeapon::PlayEmptySound() { return PlayEmptySound_(); }
void CBasePlayerWeapon::ResetEmptySound() { ResetEmptySound_(); }
void CBasePlayerWeapon::SendWeaponAnim(int iAnim,int skiplocal) { SendWeaponAnim_(iAnim,skiplocal); }
BOOL CBasePlayerWeapon::IsUseable() { return IsUseable_(); }
void CBasePlayerWeapon::RetireWeapon() { RetireWeapon_(); }

int CBasePlayerItem::Save(CSave &save) { return Save_(save); }
int CBasePlayerItem::Restore(CRestore &restore) { return Restore_(restore); }
void CBasePlayerItem::SetObjectCollisionBox() { SetObjectCollisionBox_(); }
CBaseEntity *CBasePlayerItem::Respawn() { return Respawn_(); }
int CBasePlayerItem::AddToPlayer(CBasePlayer *pPlayer) { return AddToPlayer_(pPlayer); }
void CBasePlayerItem::Holster(int skiplocal) { Holster_(skiplocal); }
void CBasePlayerItem::Drop() { Drop_(); }
void CBasePlayerItem::Kill() { Kill_(); }
void CBasePlayerItem::AttachToPlayer(CBasePlayer *pPlayer) { AttachToPlayer_(pPlayer); }

void CWeaponBox::Spawn() { Spawn_(); }
void CWeaponBox::Precache() { Precache_(); }
void CWeaponBox::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
int CWeaponBox::Save(CSave &save) { return Save_(save); }
int CWeaponBox::Restore(CRestore &restore) { return Restore_(restore); }
void CWeaponBox::SetObjectCollisionBox() { SetObjectCollisionBox_(); }
void CWeaponBox::Touch(CBaseEntity *pOther) { Touch_(pOther); }

// world
//void CDecal::Spawn() { Spawn_(); }
//void CDecal::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

void CWorld::Spawn() { Spawn_(); }
void CWorld::Precache() { Precache_(); }
void CWorld::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }

// AK47
void CAK47::Spawn() { Spawn_(); }
void CAK47::Precache() { Precache_(); }
int CAK47::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CAK47::Deploy() { return Deploy_(); }
void CAK47::PrimaryAttack() { PrimaryAttack_(); }
void CAK47::SecondaryAttack() { SecondaryAttack_(); }
void CAK47::Reload() { Reload_(); }
void CAK47::WeaponIdle() { WeaponIdle_(); }

// AUG
void CAUG::Spawn() { Spawn_(); }
void CAUG::Precache() { Precache_(); }
int CAUG::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CAUG::Deploy() { return Deploy_(); }
void CAUG::PrimaryAttack() { PrimaryAttack_(); }
void CAUG::SecondaryAttack() { SecondaryAttack_(); }
void CAUG::Reload() { Reload_(); }
void CAUG::WeaponIdle() { WeaponIdle_(); }

// AWP
void CAWP::Spawn() { Spawn_(); }
void CAWP::Precache() { Precache_(); }
int CAWP::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CAWP::Deploy() { return Deploy_(); }
float CAWP::GetMaxSpeed() { return GetMaxSpeed_(); }
void CAWP::PrimaryAttack() { PrimaryAttack_(); }
void CAWP::SecondaryAttack() { SecondaryAttack_(); }
void CAWP::Reload() { Reload_(); }
void CAWP::WeaponIdle() { WeaponIdle_(); }

// C4
void CC4::Spawn() { Spawn_(); }
void CC4::Precache() { Precache_(); }
void CC4::KeyValue(KeyValueData *pkvd) { KeyValue_(pkvd); }
void CC4::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }
int CC4::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CC4::Deploy() { return Deploy_(); }
void CC4::Holster(int skiplocal) { Holster_(skiplocal); }
float CC4::GetMaxSpeed() { return GetMaxSpeed_(); }
void CC4::PrimaryAttack() { PrimaryAttack_(); }
void CC4::WeaponIdle() { WeaponIdle_(); }

// DEAGLE
void CDEAGLE::Spawn() { Spawn_(); }
void CDEAGLE::Precache() { Precache_(); }
int CDEAGLE::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CDEAGLE::Deploy() { return Deploy_(); }
void CDEAGLE::PrimaryAttack() { PrimaryAttack_(); }
void CDEAGLE::SecondaryAttack() { SecondaryAttack_(); }
void CDEAGLE::Reload() { Reload_(); }
void CDEAGLE::WeaponIdle() { WeaponIdle_(); }

// ELITE
void CELITE::Spawn() { Spawn_(); }
void CELITE::Precache() { Precache_(); }
int CELITE::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CELITE::Deploy() { return Deploy_(); }
void CELITE::PrimaryAttack() { PrimaryAttack_(); }
void CELITE::Reload() { Reload_(); }
void CELITE::WeaponIdle() { WeaponIdle_(); }

// FAMAS
void CFamas::Spawn() { Spawn_(); }
void CFamas::Precache() { Precache_(); }
int CFamas::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CFamas::Deploy() { return Deploy_(); }
void CFamas::PrimaryAttack() { PrimaryAttack_(); }
void CFamas::SecondaryAttack() { SecondaryAttack_(); }
void CFamas::Reload() { Reload_(); }
void CFamas::WeaponIdle() { WeaponIdle_(); }

// FIVESEVEN
void CFiveSeven::Spawn() { Spawn_(); }
void CFiveSeven::Precache() { Precache_(); }
int CFiveSeven::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CFiveSeven::Deploy() { return Deploy_(); }
void CFiveSeven::PrimaryAttack() { PrimaryAttack_(); }
void CFiveSeven::SecondaryAttack() { SecondaryAttack_(); }
void CFiveSeven::Reload() { Reload_(); }
void CFiveSeven::WeaponIdle() { WeaponIdle_(); }

// FLASHBANG
void CFlashbang::Spawn() { Spawn_(); }
void CFlashbang::Precache() { Precache_(); }
int CFlashbang::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CFlashbang::CanDeploy() { return CanDeploy_(); }
BOOL CFlashbang::Deploy() { return Deploy_(); }
void CFlashbang::Holster(int skiplocal) { Holster_(skiplocal); }
void CFlashbang::PrimaryAttack() { PrimaryAttack_(); }
void CFlashbang::SecondaryAttack() { SecondaryAttack_(); }
void CFlashbang::WeaponIdle() { WeaponIdle_(); }

// G3SG1
void CG3SG1::Spawn() { Spawn_(); }
void CG3SG1::Precache() { Precache_(); }
int CG3SG1::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CG3SG1::Deploy() { return Deploy_(); }
float CG3SG1::GetMaxSpeed() { return GetMaxSpeed_(); }
void CG3SG1::PrimaryAttack() { PrimaryAttack_(); }
void CG3SG1::SecondaryAttack() { SecondaryAttack_(); }
void CG3SG1::Reload() { Reload_(); }
void CG3SG1::WeaponIdle() { WeaponIdle_(); }

// GALIL
void CGalil::Spawn() { Spawn_(); }
void CGalil::Precache() { Precache_(); }
int CGalil::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CGalil::Deploy() { return Deploy_(); }
void CGalil::PrimaryAttack() { PrimaryAttack_(); }
void CGalil::SecondaryAttack() { SecondaryAttack_(); }
void CGalil::Reload() { Reload_(); }
void CGalil::WeaponIdle() { WeaponIdle_(); }

// GLOCK18
void CGLOCK18::Spawn() { Spawn_(); }
void CGLOCK18::Precache() { Precache_(); }
int CGLOCK18::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CGLOCK18::Deploy() { return Deploy_(); }
void CGLOCK18::PrimaryAttack() { PrimaryAttack_(); }
void CGLOCK18::SecondaryAttack() { SecondaryAttack_(); }
void CGLOCK18::Reload() { Reload_(); }
void CGLOCK18::WeaponIdle() { WeaponIdle_(); }

// HEGRENADE
void CHEGrenade::Spawn() { Spawn_(); }
void CHEGrenade::Precache() { Precache_(); }
int CHEGrenade::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CHEGrenade::CanDeploy() { return CanDeploy_(); }
BOOL CHEGrenade::Deploy() { return Deploy_(); }
void CHEGrenade::Holster(int skiplocal) { Holster_(skiplocal); }
void CHEGrenade::PrimaryAttack() { PrimaryAttack_(); }
void CHEGrenade::SecondaryAttack() { SecondaryAttack_(); }
void CHEGrenade::WeaponIdle() { WeaponIdle_(); }

// KNIFE
void CKnife::Spawn() { Spawn_(); }
void CKnife::Precache() { Precache_(); }
int CKnife::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CKnife::Deploy() { return Deploy_(); }
void CKnife::Holster(int skiplocal) { Holster_(skiplocal); }
void CKnife::PrimaryAttack() { PrimaryAttack_(); }
void CKnife::SecondaryAttack() { SecondaryAttack_(); }
void CKnife::WeaponIdle() { WeaponIdle_(); }

// M3
void CM3::Spawn() { Spawn_(); }
void CM3::Precache() { Precache_(); }
int CM3::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CM3::Deploy() { return Deploy_(); }
void CM3::PrimaryAttack() { PrimaryAttack_(); }
void CM3::Reload() { Reload_(); }
void CM3::WeaponIdle() { WeaponIdle_(); }

// M4A1
void CM4A1::Spawn() { Spawn_(); }
void CM4A1::Precache() { Precache_(); }
int CM4A1::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CM4A1::Deploy() { return Deploy_(); }
float CM4A1::GetMaxSpeed() { return GetMaxSpeed_(); }
void CM4A1::PrimaryAttack() { PrimaryAttack_(); }
void CM4A1::SecondaryAttack() { SecondaryAttack_(); }
void CM4A1::Reload() { Reload_(); }
void CM4A1::WeaponIdle() { WeaponIdle_(); }

// M249
void CM249::Spawn() { Spawn_(); }
void CM249::Precache() { Precache_(); }
int CM249::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CM249::Deploy() { return Deploy_(); }
void CM249::PrimaryAttack() { PrimaryAttack_(); }
void CM249::Reload() { Reload_(); }
void CM249::WeaponIdle() { WeaponIdle_(); }

// MAC10
void CMAC10::Spawn() { Spawn_(); }
void CMAC10::Precache() { Precache_(); }
int CMAC10::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CMAC10::Deploy() { return Deploy_(); }
void CMAC10::PrimaryAttack() { PrimaryAttack_(); }
void CMAC10::Reload() { Reload_(); }
void CMAC10::WeaponIdle() { WeaponIdle_(); }

// MP5NAVY
void CMP5N::Spawn() { Spawn_(); }
void CMP5N::Precache() { Precache_(); }
int CMP5N::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CMP5N::Deploy() { return Deploy_(); }
void CMP5N::PrimaryAttack() { PrimaryAttack_(); }
void CMP5N::Reload() { Reload_(); }
void CMP5N::WeaponIdle() { WeaponIdle_(); }

// P90
void CP90::Spawn() { Spawn_(); }
void CP90::Precache() { Precache_(); }
int CP90::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CP90::Deploy() { return Deploy_(); }
void CP90::PrimaryAttack() { PrimaryAttack_(); }
void CP90::Reload() { Reload_(); }
void CP90::WeaponIdle() { WeaponIdle_(); }
float CP90::GetMaxSpeed() { return GetMaxSpeed_(); }

// P228
void CP228::Spawn() { Spawn_(); }
void CP228::Precache() { Precache_(); }
int CP228::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CP228::Deploy() { return Deploy_(); }
void CP228::PrimaryAttack() { PrimaryAttack_(); }
void CP228::SecondaryAttack() { SecondaryAttack_(); }
void CP228::Reload() { Reload_(); }
void CP228::WeaponIdle() { WeaponIdle_(); }

// SCOUT
void CSCOUT::Spawn() { Spawn_(); }
void CSCOUT::Precache() { Precache_(); }
int CSCOUT::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CSCOUT::Deploy() { return Deploy_(); }
float CSCOUT::GetMaxSpeed() { return GetMaxSpeed_(); }
void CSCOUT::PrimaryAttack() { PrimaryAttack_(); }
void CSCOUT::SecondaryAttack() { SecondaryAttack_(); }
void CSCOUT::Reload() { Reload_(); }
void CSCOUT::WeaponIdle() { WeaponIdle_(); }

// SG550
void CSG550::Spawn() { Spawn_(); }
void CSG550::Precache() { Precache_(); }
int CSG550::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CSG550::Deploy() { return Deploy_(); }
float CSG550::GetMaxSpeed() { return GetMaxSpeed_(); }
void CSG550::PrimaryAttack() { PrimaryAttack_(); }
void CSG550::SecondaryAttack() { SecondaryAttack_(); }
void CSG550::Reload() { Reload_(); }
void CSG550::WeaponIdle() { WeaponIdle_(); }

// SG552
void CSG552::Spawn() { Spawn_(); }
void CSG552::Precache() { Precache_(); }
int CSG552::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CSG552::Deploy() { return Deploy_(); }
float CSG552::GetMaxSpeed() { return GetMaxSpeed_(); }
void CSG552::PrimaryAttack() { PrimaryAttack_(); }
void CSG552::SecondaryAttack() { SecondaryAttack_(); }
void CSG552::Reload() { Reload_(); }
void CSG552::WeaponIdle() { WeaponIdle_(); }

// SMOKEGRENADE
void CSmokeGrenade::Spawn() { Spawn_(); }
void CSmokeGrenade::Precache() { Precache_(); }
int CSmokeGrenade::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CSmokeGrenade::CanDeploy() { return CanDeploy_(); }
BOOL CSmokeGrenade::Deploy() { return Deploy_(); }
void CSmokeGrenade::Holster(int skiplocal) { Holster_(skiplocal); }
void CSmokeGrenade::PrimaryAttack() { PrimaryAttack_(); }
void CSmokeGrenade::SecondaryAttack() { SecondaryAttack_(); }
void CSmokeGrenade::WeaponIdle() { WeaponIdle_(); }

// TMP
void CTMP::Spawn() { Spawn_(); }
void CTMP::Precache() { Precache_(); }
int CTMP::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CTMP::Deploy() { return Deploy_(); }
void CTMP::PrimaryAttack() { PrimaryAttack_(); }
void CTMP::Reload() { Reload_(); }
void CTMP::WeaponIdle() { WeaponIdle_(); }

// UMP45
void CUMP45::Spawn() { Spawn_(); }
void CUMP45::Precache() { Precache_(); }
int CUMP45::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CUMP45::Deploy() { return Deploy_(); }
void CUMP45::PrimaryAttack() { PrimaryAttack_(); }
void CUMP45::Reload() { Reload_(); }
void CUMP45::WeaponIdle() { WeaponIdle_(); }

// USP
void CUSP::Spawn() { Spawn_(); }
void CUSP::Precache() { Precache_(); }
int CUSP::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CUSP::Deploy() { return Deploy_(); }
void CUSP::PrimaryAttack() { PrimaryAttack_(); }
void CUSP::SecondaryAttack() { SecondaryAttack_(); }
void CUSP::Reload() { Reload_(); }
void CUSP::WeaponIdle() { WeaponIdle_(); }

// XM1014
void CXM1014::Spawn() { Spawn_(); }
void CXM1014::Precache() { Precache_(); }
int CXM1014::GetItemInfo(ItemInfo *p) { return GetItemInfo_(p); }
BOOL CXM1014::Deploy() { return Deploy_(); }
void CXM1014::PrimaryAttack() { PrimaryAttack_(); }
void CXM1014::Reload() { Reload_(); }
void CXM1014::WeaponIdle() { WeaponIdle_(); }

// hostage
void CHostage::Spawn() { Spawn_(); }
void CHostage::Precache() { Precache_(); }
int CHostage::ObjectCaps() { return ObjectCaps_(); }
int CHostage::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
void CHostage::Touch(CBaseEntity *pOther) { Touch_(pOther); }
void CHostage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) { Use_(pActivator, pCaller, useType, value); }

// hostage_improv
void CHostageImprov::OnMoveToFailure(const Vector &goal, MoveToFailureType reason) { OnMoveToFailure_(goal, reason); }
bool CHostageImprov::IsAlive() const { return IsAlive_(); }
void CHostageImprov::MoveTo(const Vector &goal) { MoveTo_(goal); }
void CHostageImprov::LookAt(const Vector &target) { LookAt_(target); }
void CHostageImprov::ClearLookAt() { ClearLookAt_(); }
void CHostageImprov::FaceTo(const Vector &goal) { FaceTo_(goal); }
void CHostageImprov::ClearFaceTo() { ClearFaceTo_(); }
bool CHostageImprov::IsAtMoveGoal(float error) const { return IsAtMoveGoal_(error); }
bool CHostageImprov::IsAtFaceGoal() const { return IsAtFaceGoal_(); }
bool CHostageImprov::IsFriendInTheWay(const Vector &goalPos) const { return IsFriendInTheWay_(goalPos); }
bool CHostageImprov::IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const { return IsFriendInTheWay_(myFriend, goalPos); }
bool CHostageImprov::Jump() { return Jump_(); }
void CHostageImprov::Crouch() { Crouch_(); }
void CHostageImprov::StandUp() { StandUp_(); }
void CHostageImprov::TrackPath(const Vector &pathGoal, float deltaT) { TrackPath_(pathGoal, deltaT); }
void CHostageImprov::StartLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos) { StartLadder_(ladder, how, approachPos, departPos); }
bool CHostageImprov::TraverseLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT) { return TraverseLadder_(ladder, how, approachPos, departPos, deltaT); }
bool CHostageImprov::GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal) { return GetSimpleGroundHeightWithFloor_(pos, height, normal); }
void CHostageImprov::Run() { Run_(); }
void CHostageImprov::Walk() { Walk_(); }
void CHostageImprov::Stop() { Stop_(); }
const Vector &CHostageImprov::GetFeet() const { return GetFeet_(); }
const Vector &CHostageImprov::GetCentroid() const { return GetCentroid_(); }
const Vector &CHostageImprov::GetEyes() const { return GetEyes_(); }
bool CHostageImprov::IsOnGround() const { return IsOnGround_(); }
bool CHostageImprov::IsMoving() const { return IsMoving_(); }
bool CHostageImprov::IsVisible(const Vector &pos, bool testFOV) const { return IsVisible_(pos, testFOV); }
bool CHostageImprov::IsPlayerLookingAtMe(CBasePlayer *other, float cosTolerance) const { return IsPlayerLookingAtMe_(other, cosTolerance); }
CBasePlayer *CHostageImprov::IsAnyPlayerLookingAtMe(int team, float cosTolerance) const { return IsAnyPlayerLookingAtMe_(team, cosTolerance); }
CBasePlayer *CHostageImprov::GetClosestPlayerByTravelDistance(int team, float *range) const { return GetClosestPlayerByTravelDistance_(team, range); }
void CHostageImprov::OnUpdate(float deltaT) { OnUpdate_(deltaT); }
void CHostageImprov::OnUpkeep(float deltaT) { OnUpkeep_(deltaT); }
void CHostageImprov::OnReset() { OnReset_(); }
void CHostageImprov::OnGameEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { OnGameEvent_(event, entity, other); }
void CHostageImprov::OnTouch(CBaseEntity *other) { OnTouch_(other); }

// hostage_idle
void HostageIdleState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageIdleState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageIdleState::OnExit(CHostageImprov *improv) { OnExit_(improv); }
void HostageIdleState::UpdateStationaryAnimation(CHostageImprov *improv) { UpdateStationaryAnimation_(improv); }

// hostage_escape
void HostageEscapeToCoverState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageEscapeToCoverState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageEscapeToCoverState::OnExit(CHostageImprov *improv) { OnExit_(improv); }

void HostageEscapeToCoverState::OnMoveToFailure(const Vector &goal, MoveToFailureType reason) { OnMoveToFailure_(goal, reason); }
/*void HostageEscapeToCoverState::OnMoveToFailure_(const Vector &goal, MoveToFailureType reason)
{
	// TODO: why this - 1? Hacks?
	// need investigation
	HostageEscapeState *escape = (HostageEscapeState *)*((int *)this - 1);
	escape->LookAround();
}*/


void HostageEscapeLookAroundState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageEscapeLookAroundState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageEscapeLookAroundState::OnExit(CHostageImprov *improv) { OnExit_(improv); }

void HostageEscapeState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageEscapeState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageEscapeState::OnExit(CHostageImprov *improv) { OnExit_(improv); }

// hostage_follow
void HostageFollowState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageFollowState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageFollowState::OnExit(CHostageImprov *improv) { OnExit_(improv); }
void HostageFollowState::UpdateStationaryAnimation(CHostageImprov *improv) { UpdateStationaryAnimation_(improv); }

// hostage_animate
void HostageAnimateState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageAnimateState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageAnimateState::OnExit(CHostageImprov *improv) { OnExit_(improv); }

// hostage_retreat
void HostageRetreatState::OnEnter(CHostageImprov *improv) { OnEnter_(improv); }
void HostageRetreatState::OnUpdate(CHostageImprov *improv) { OnUpdate_(improv); }
void HostageRetreatState::OnExit(CHostageImprov *improv) { OnExit_(improv); }

// cs_bot
void CCSBot::Walk() { Walk_(); }
bool CCSBot::Jump(bool mustJump) { return Jump_(mustJump); }
int CCSBot::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) { return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType); }
void CCSBot::Killed(entvars_t *pevAttacker, int iGib) { Killed_(pevAttacker, iGib); }

// cs_bot_chatter
// you can not hook this function, because it uses the rand() function
// which does not allow us to carry out tests because different results at the output.
void __declspec(naked) BotPhrase::Randomize() { __asm { jmp pBotPhrase__Randomize } }

void BotAllHostagesGoneMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotHostageBeingTakenMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotHelpMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotBombsiteStatusMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotBombStatusMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotFollowMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotDefendHereMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotWhereBombMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }
void BotRequestReportMeme::Interpret(CCSBot *sender, CCSBot *receiver) const { Interpret_(sender, receiver); }

// cs_bot_event
void CCSBot::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { OnEvent_(event, entity, other); }

// cs_bot_init
bool CCSBot::Initialize(const BotProfile *profile) { return Initialize_(profile); }
void CCSBot::SpawnBot() { SpawnBot_(); }
void CCSBot::RoundRespawn() { RoundRespawn_(); }

void CCSBotManager::ClientDisconnect(CBasePlayer *pPlayer) { ClientDisconnect_(pPlayer); }
BOOL CCSBotManager::ClientCommand(CBasePlayer *pPlayer, const char *pcmd) { return ClientCommand_(pPlayer, pcmd); }
void CCSBotManager::ServerActivate() { ServerActivate_(); }
void CCSBotManager::ServerDeactivate() { ServerDeactivate_(); }
void CCSBotManager::ServerCommand(const char *pcmd) { ServerCommand_(pcmd); }
void CCSBotManager::AddServerCommand(const char *cmd) { AddServerCommand_(cmd); }
void CCSBotManager::AddServerCommands() { AddServerCommands_(); }
void CCSBotManager::RestartRound() { RestartRound_(); }
void CCSBotManager::StartFrame() { StartFrame_(); }
void CCSBotManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { OnEvent_(event, entity, other); }
unsigned int CCSBotManager::GetPlayerPriority(CBasePlayer *player) const { return GetPlayerPriority_(player); }
bool CCSBotManager::IsImportantPlayer(CBasePlayer *player) const { return IsImportantPlayer_(player); }

// cs_bot_update
void CCSBot::Upkeep() { Upkeep_(); }
void CCSBot::Update() { Update_(); }

// cs_bot_vision
void __declspec(naked) CCSBot::UpdateLookAngles() { __asm { jmp pCCSBot__UpdateLookAngles } }
void CCSBot::Blind(float duration, float holdTime, float fadeTime, int alpha) { Blind_(duration, holdTime, fadeTime, alpha); }
bool CCSBot::IsVisible(const Vector *pos, bool testFOV) const { return IsVisible_(pos, testFOV); }
bool CCSBot::IsVisible(CBasePlayer *player, bool testFOV, unsigned char *visParts) const { return IsVisible_(player, testFOV, visParts); }
bool CCSBot::IsEnemyPartVisible(VisiblePartType part) const { return IsEnemyPartVisible_(part); }

// cs_bot_weapon
void CCSBot::OnTouchingWeapon(CWeaponBox *box) { OnTouchingWeapon_(box); }

// cs_bot_idle
void IdleState::OnEnter(CCSBot *me) { OnEnter_(me); }
void IdleState::OnUpdate(CCSBot *me) { OnUpdate_(me); }

// cs_bot_attack
void AttackState::OnEnter(CCSBot *me) { OnEnter_(me); }
void AttackState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void AttackState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_buy
void BuyState::OnEnter(CCSBot *me) { OnEnter_(me); }
void BuyState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void BuyState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_hide
void HideState::OnEnter(CCSBot *me) { OnEnter_(me); }
void HideState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void HideState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_move_to
void MoveToState::OnEnter(CCSBot *me) { OnEnter_(me); }
void MoveToState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void MoveToState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_follow
void FollowState::OnEnter(CCSBot *me) { OnEnter_(me); }
void FollowState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void FollowState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_hunt
void HuntState::OnEnter(CCSBot *me) { OnEnter_(me); }
void HuntState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void HuntState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_investigate_noise
void InvestigateNoiseState::OnEnter(CCSBot *me) { OnEnter_(me); }
void InvestigateNoiseState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void InvestigateNoiseState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_plant_bomb
void PlantBombState::OnEnter(CCSBot *me) { OnEnter_(me); }
void PlantBombState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void PlantBombState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_defuse_bomb
void DefuseBombState::OnEnter(CCSBot *me) { OnEnter_(me); }
void DefuseBombState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void DefuseBombState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_use_entity
void UseEntityState::OnEnter(CCSBot *me) { OnEnter_(me); }
void UseEntityState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void UseEntityState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_escape_from_bomb
void EscapeFromBombState::OnEnter(CCSBot *me) { OnEnter_(me); }
void EscapeFromBombState::OnUpdate(CCSBot *me) { OnUpdate_(me); }
void EscapeFromBombState::OnExit(CCSBot *me) { OnExit_(me); }

// cs_bot_fetch_bomb
void FetchBombState::OnEnter(CCSBot *me) { OnEnter_(me); }
void FetchBombState::OnUpdate(CCSBot *me) { OnUpdate_(me); }

// bot_manager
void CBotManager::RestartRound() { RestartRound_(); }
void CBotManager::StartFrame() { StartFrame_(); }
void CBotManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other) { return OnEvent_(event, entity, other); }

// bot
void CBot::Spawn() { Spawn_(); }
Vector CBot::GetAutoaimVector(float flDelta) { return GetAutoaimVector_(flDelta); }
bool CBot::Initialize(const BotProfile *profile) { return Initialize_(profile); }
void CBot::Crouch() { Crouch_(); }
void CBot::StandUp() { StandUp_(); }
void CBot::MoveForward() { MoveForward_(); }
void CBot::MoveBackward() { MoveBackward_(); }
void CBot::StrafeLeft() { StrafeLeft_(); }
void CBot::StrafeRight() { StrafeRight_(); }
bool CBot::Jump(bool mustJump) { return Jump_(mustJump); }
void CBot::ClearMovement() { ClearMovement_(); }
void CBot::UseEnvironment() { UseEnvironment_(); }
void CBot::PrimaryAttack() { PrimaryAttack_(); }
void CBot::ClearPrimaryAttack() { ClearPrimaryAttack_(); }
void CBot::TogglePrimaryAttack() { TogglePrimaryAttack_(); }
void CBot::SecondaryAttack() { SecondaryAttack_(); }
void CBot::Reload() { Reload_(); }
void CBot::ExecuteCommand() { ExecuteCommand_(); }


// hostage_improv.h
// NavAreaBuildPath<HostagePathCost> hook
bool NavAreaBuildPath__HostagePathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, HostagePathCost &costFunc, CNavArea **closestArea) { return NavAreaBuildPath(startArea, goalArea, goalPos, costFunc, closestArea); }

// NavAreaBuildPath<ShortestPathCost> hook
bool NavAreaBuildPath__ShortestPathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, ShortestPathCost &costFunc, CNavArea **closestArea) { return NavAreaBuildPath(startArea, goalArea, goalPos, costFunc, closestArea); }

// NavAreaBuildPath<PathCost> hook
bool NavAreaBuildPath__PathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, PathCost &costFunc, CNavArea **closestArea) { return NavAreaBuildPath(startArea, goalArea, goalPos, costFunc, closestArea); }

// NavAreaTravelDistance<PathCost> hook
float_precision NavAreaTravelDistance__PathCost__wrapper(CNavArea *startArea, CNavArea *endArea, PathCost &costFunc) { return NavAreaTravelDistance(startArea, endArea, costFunc); }


// functions
bool CBot::IsPlayerFacingMe(CBasePlayer *other) const
{
	return IsPlayerFacingMe_(other);
}

bool CBot::IsPlayerLookingAtMe(CBasePlayer *other) const
{
	return IsPlayerLookingAtMe_(other);
}

void CBot::SetModel(const char *modelName)
{
	SetModel_(modelName);
}
