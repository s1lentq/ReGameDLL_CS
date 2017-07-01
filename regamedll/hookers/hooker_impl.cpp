#include "precompiled.h"

// xrefs
void (*pBotPhrase__Randomize)();
void (*pCCSBotManager__AddBot)();
void (*pCCSBot__UpdateLookAngles)();

// custom
char *CGameRules::m_GameDesc = nullptr;
bool CGameRules::m_bGameOver = false;

bool CHalfLifeMultiplay::m_bSkipShowMenu = false;
bool CHalfLifeMultiplay::m_bNeededPlayers = false;
float CHalfLifeMultiplay::m_flEscapeRatio = 0;
float CHalfLifeMultiplay::m_flTimeLimit = 0;
float CHalfLifeMultiplay::m_flGameStartTime = 0;

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
char mp_com_token[ 1500 ];
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
BOOL g_fGameOver;		// moved from gamerules
float g_flTimeLimit;		// moved from gamerules
float g_flResetTime;		// moved from gamerules
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

// sound
int gcTextures;
BOOL fTextureTypeInit;

/*void HostageEscapeToCoverState::OnMoveToFailure_(const Vector &goal, MoveToFailureType reason)
{
	// TODO: why this - 1? Hacks?
	// need investigation
	HostageEscapeState *escape = (HostageEscapeState *)*((int *)this - 1);
	escape->LookAround();
}*/

// cs_bot_chatter
// you can not hook this function, because it uses the rand() function
// which does not allow us to carry out tests because different results at the output.
void __declspec(naked) BotPhrase::Randomize() { __asm { jmp pBotPhrase__Randomize } }

// cs_bot_vision
void __declspec(naked) CCSBot::UpdateLookAngles() { __asm { jmp pCCSBot__UpdateLookAngles } }
