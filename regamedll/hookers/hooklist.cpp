/*
*
*  This program is free software; you can redistribute it and/or modify it
*  under the terms of the GNU General Public License as published by the
*  Free Software Foundation; either version 2 of the License,or (at
*  your option) any later version.
*
*  This program is distributed in the hope that it will be useful,but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not,write to the Free Software Foundation,
*  Inc.,59 Temple Place,Suite 330,Boston,MA  02111-1307  USA
*
*  In addition,as a special exception,the author gives permission to
*  link the code of this program with the Half-Life Game Engine ("HL
*  Engine") and Modified Game Libraries ("MODs") developed by Valve,
*  L.L.C ("Valve").  You must obey the GNU General Public License in all
*  respects for all of the code used other than the HL Engine and MODs
*  from Valve.  If you modify this file,you may extend this exception
*  to your version of the file,but you are not obligated to do so.  If
*  you do not wish to do so,delete this exception statement from your
*  version.
*
*/

#include "precompiled.h"

#define CBASE_VIRTUAL_COUNT		58
#define CWEAPON_VIRTUAL_COUNT	94

//#define Mem_Region
//#define Export_Region
//#define Monsters_Region
//#define AirTank_Region
//#define PM_Shared_Region
//#define Triggers_Region
//#define Cbase_Region
//#define Client_Region
//#define Spectator_Region
//#define BaseMonster_Region
//#define Player_Region
//#define Effects_Region
//#define Plats_Region
//#define PathCorner_Region
//#define Vehicle_Region
//#define Func_Tank_Region
//#define Func_Break_Region
//#define Door_Region
//#define BModels_Region
//#define Button_Region
//#define Explode_Region
//#define Mortar_Region
//#define Healkit_Region
//#define Lights_Region
//#define MapRules_Region
//#define HintMessage_Region
//#define Items_Region
//#define SharedUtil_Region
//#define World_Region
//#define Graph_Region
//#define SoundEnt_Region
//#define Sound_Region
//#define Util_Region
//#define WeaponType_Region
//#define Weapons_Region
//#define GGrenade_Region
//#define Animation_Region
//#define GameRules_Region
//#define Multiplay_GameRules_Region
//#define Singleplay_GameRules_Region
//#define Training_Gamerules_Region
//#define CareerTasks_Region
//#define MemoryPool_Region
//#define Unicode_StrTools_Region
//#define CUtlSymbol_Region
//#define Debug_Region
//#define CS_Bot_Region
//#define CS_BotState_Region
//#define Bot_Region
//#define Bot_Profile
//#define CS_Util_Region
//#define CS_Init_Region
//#define H_Region
//#define Tutor_CS_Region
//#define Nav_Region
//#define Hostage_Region
//#define VoiceManager_Region
//#define Vector_Region

//#define Data_References_Region
//#define Function_References_Region

FunctionHook g_FunctionHooks[] =
{

#ifndef Mem_Region

#ifdef _WIN32

	//HOOK_SYMBOLDEF(0x01DE015D, "__heap_alloc_base", malloc_wrapper),
	HOOK_SYMBOLDEF(0x01DE0131, "_nh_malloc", _nh_malloc_wrapper),
	HOOK_SYMBOLDEF(0x01DE011F, "malloc", malloc_wrapper),

	HOOK_SYMBOLDEF(0x01DE12A5, "realloc", realloc_wrapper),
	HOOK_SYMBOLDEF(0x01DE0E7B, "free", free_wrapper),
	HOOK_SYMBOLDEF(0x01DE2331, "calloc", calloc_wrapper),
	HOOK_SYMBOLDEF(0x01DF27C9, "strdup", strdup_wrapper),
	//HOOK_SYMBOLDEF(0x01DDFD40, "rand", rand_wrapper),

#endif // _WIN32

#endif // Mem_Region

#ifndef Export_Region

	HOOK_DEF(0x01D86730, GiveFnptrsToDll),

#endif // Export_Region

#ifndef PM_Shared_Region

	HOOK_DEF(0x01DB6640, PM_Move),
	HOOK_DEF(0x01DB6710, PM_Init),
	HOOK_DEF(0x01DB1020, PM_FindTextureType),
//pm_debug
	//HOOK_DEF(0x01DAEEE0, PM_ShowClipBox),				// NOXREF
	//HOOK_DEF(0x01DAEEF0, PM_ParticleLine),			// NOXREF
	//HOOK_DEF(0x01DAEFC0, PM_DrawRectangle),			// NOXREF
	//HOOK_DEF(0x01DAF290, PM_DrawPhysEntBBox),			// NOXREF
	//HOOK_DEF(0x01DAFB50, PM_DrawBBox),				// NOXREF
	//HOOK_DEF(0x01DAFF20, PM_ViewEntity),				// NOXREF
//pm_shared
	//HOOK_DEF(0x01DB0AB0, PM_SwapTextures),			// NOXREF
	//HOOK_DEF(0x01DB0B30, PM_IsThereGrassTexture),		// NOXREF
	//HOOK_DEF(0x01DB0B60, PM_SortTextures),			// NOXREF
	HOOK_DEF(0x01DB0C80, PM_InitTextureTypes),
	//HOOK_DEF(0x0, PM_FindTextureType),
	HOOK_DEF(0x01DB1080, PM_PlayStepSound),
	//HOOK_DEF(0x01DB17E0, PM_MapTextureTypeStepType),	// NOXREF
	HOOK_DEF(0x01DB1860, PM_CatagorizeTextureType),
	HOOK_DEF(0x01DB19B0, PM_UpdateStepSound),
	//HOOK_DEF(0x01DB1CB0, PM_AddToTouched),			// NOXREF
	HOOK_DEF(0x01DB1D50, PM_CheckVelocity),
	HOOK_DEF(0x01DB1E40, PM_ClipVelocity),
	//HOOK_DEF(0x01DB1EF0, PM_AddCorrectGravity),		// NOXREF
	//HOOK_DEF(0x01DB1F70, PM_FixupGravityVelocity),	// NOXREF
	HOOK_DEF(0x01DB1FD0, PM_FlyMove),
	//HOOK_DEF(0x01DB24E0, PM_Accelerate),				// NOXREF
	HOOK_DEF(0x01DB2580, PM_WalkMove),
	HOOK_DEF(0x01DB2B50, PM_Friction),
	HOOK_DEF(0x01DB2CF0, PM_AirAccelerate),
	HOOK_DEF(0x01DB2DB0, PM_WaterMove),
	HOOK_DEF(0x01DB30C0, PM_AirMove_internal),
	//HOOK_DEF(0x01DB3200, PM_InWater),					// NOXREF
	HOOK_DEF(0x01DB3220, PM_CheckWater),
	HOOK_DEF(0x01DB33E0, PM_CategorizePosition),
	//HOOK_DEF(0x01DB3590, PM_GetRandomStuckOffsets),	// NOXREF
	//HOOK_DEF(0x01DB35E0, PM_ResetStuckOffsets),		// NOXREF
	HOOK_DEF(0x01DB3600, PM_CheckStuck),
	HOOK_DEF(0x01DB3970, PM_SpectatorMove),
	//HOOK_DEF(0x01DB3C70, PM_SplineFraction),			// NOXREF
	//HOOK_DEF(0x01DB3C90, PM_SimpleSpline),			// NOXREF
	//HOOK_DEF(0x01DB3CB0, PM_FixPlayerCrouchStuck),	// NOXREF
	HOOK_DEF(0x01DB3D50, PM_Duck),
	HOOK_DEF(0x01DB4110, PM_LadderMove),
	HOOK_DEF(0x01DB44D0, PM_Ladder),
	//HOOK_DEF(0x01DB45A0, PM_WaterJump),				// NOXREF
	//HOOK_DEF(0x01DB4660, PM_AddGravity),				// NOXREF
	//HOOK_DEF(0x01DB46C0, PM_PushEntity),				// NOXREF
	HOOK_DEF(0x01DB4820, PM_Physics_Toss),
	HOOK_DEF(0x01DB4DE0, PM_NoClip),
	//HOOK_DEF(0x01DB4E90, PM_PreventMegaBunnyJumping),	// NOXREF
	HOOK_DEF(0x01DB4F00, PM_Jump),
	HOOK_DEF(0x01DB52F0, PM_CheckWaterJump),
	HOOK_DEF(0x01DB5560, PM_CheckFalling),
	//HOOK_DEF(0x01DB5810, PM_PlayWaterSounds),			// NOXREF
	//HOOK_DEF(0x01DB5810, PM_CalcRoll),				// NOXREF
	//HOOK_DEF(0x01DB58A0, PM_DropPunchAngle),			// NOXREF
	HOOK_DEF(0x01DB58F0, PM_CheckParameters),
	HOOK_DEF(0x01DB5BE0, PM_ReduceTimers),
	//HOOK_DEF(0x01DB5D20, PM_ShouldDoSpectMode),		// NOXREF
	HOOK_DEF(0x01DB5D50, PM_PlayerMove),
	HOOK_DEF(0x01DB6430, PM_CreateStuckTable),
	//HOOK_DEF(0x01DB66B0, PM_GetVisEntInfo),			// NOXREF
	//HOOK_DEF(0x01DB66E0, PM_GetPhysEntInfo),			// NOXREF
//pm_math
	//HOOK_DEF(0x0, anglemod),
	HOOK_DEF(0x01DB0000, AngleVectors),
	//HOOK_DEF(0x01DB0100, AngleVectorsTranspose),		// NOXREF
	HOOK_DEF(0x01DB0200, AngleMatrix),
	//HOOK_DEF(0x01DB02D0, AngleIMatrix),				// NOXREF
	//HOOK_DEF(0x01DB03A0, NormalizeAngles),			// NOXREF
	//HOOK_DEF(0x01DB03F0, InterpolateAngles),			// NOXREF
	//HOOK_DEF(0x01DB0510, AngleBetweenVectors),		// NOXREF
	//HOOK_DEF(0x01DB05B0, VectorTransform),			// NOXREF
	HOOK_DEF(0x01DB0610, VectorCompare),
	HOOK_DEF(0x01DB0640, VectorMA),
	//HOOK_DEF(0x01DB0680, _DotProduct),				// NOXREF
	//HOOK_DEF(0x01DB06A0, _VectorSubtract),			// NOXREF
	//HOOK_DEF(0x01DB06D0, _VectorAdd),					// NOXREF
	//HOOK_DEF(0x01DB0700, _VectorCopy),				// NOXREF
	//HOOK_DEF(0x01DB0720, CrossProduct),				// NOXREF
	HOOK_DEF(0x01DB0760, Length),
	//HOOK_DEF(0x01DB0780, Distance),					// NOXREF
	HOOK_DEF(0x01DB07D0, VectorNormalize),
	//HOOK_DEF(0x01DB0820, VectorInverse),
	HOOK_DEF(0x01DB0840, VectorScale),
	//HOOK_DEF(0x01DB0870, Q_log2),
	//HOOK_DEF(0x01DB0880, VectorMatrix),
	//HOOK_DEF(0x01DB09D0, VectorAngles),

#endif // PM_Shared_Region

#ifndef Monsters_Region
//CGib
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D70C90, "_ZN4CGib10ObjectCapsEv", CGib::ObjectCaps),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D6FFE0, "_ZN4CGib5SpawnEPKc", CGib::Spawn),
	HOOK_SYMBOLDEF(0x01D6FCA0, "_ZN4CGib14BounceGibTouchEP11CBaseEntity", CGib::BounceGibTouch),
	HOOK_SYMBOLDEF(0x01D6FE40, "_ZN4CGib14StickyGibTouchEP11CBaseEntity", CGib::StickyGibTouch),
	HOOK_SYMBOLDEF(0x01D6FBF0, "_ZN4CGib12WaitTillLandEv", CGib::WaitTillLand),
	HOOK_SYMBOLDEF(0x01D6E550, "_ZN4CGib13LimitVelocityEv", CGib::LimitVelocity),
	HOOK_SYMBOLDEF(0x01D6EAB0, "_ZN4CGib12SpawnHeadGibEP9entvars_s", CGib::SpawnHeadGib),
	HOOK_SYMBOLDEF(0x01D6EEB0, "_ZN4CGib15SpawnRandomGibsEP9entvars_sii", CGib::SpawnRandomGibs),
	//HOOK_SYMBOLDEF(0x01D6E640, "_ZN4CGib15SpawnStickyGibsEP9entvars_s6Vectori", CGib::SpawnStickyGibs),	// NOXREF
#endif // Monsters_Region

#ifndef AirTank_Region

	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D592B0, "_ZN8CAirtank5SpawnEv", CAirtank::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D593A0, "_ZN8CAirtank8PrecacheEv", CAirtank::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59250, "_ZN8CAirtank4SaveER5CSave", CAirtank::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59280, "_ZN8CAirtank7RestoreER8CRestore", CAirtank::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D593C0, "_ZN8CAirtank6KilledEP9entvars_si", CAirtank::Killed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59240, "_ZN8CAirtank10BloodColorEv", CAirtank::BloodColor),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D59410, "_ZN8CAirtank9TankThinkEv", CAirtank::TankThink),
	HOOK_SYMBOLDEF(0x01D59430, "_ZN8CAirtank9TankTouchEP11CBaseEntity", CAirtank::TankTouch),
	HOOK_DEF(0x01D591F0, item_airtank),

#endif // AirTank_Region

#ifndef Client_Region

	//HOOK_SYMBOLDEF(0x0, "_ZL8CMD_ARGCv", CMD_ARGC_),
	//HOOK_SYMBOLDEF(0x0, "_ZL8CMD_ARGVi", CMD_ARGV_),
	//HOOK_SYMBOLDEF(0x01D63CE0, "_Z17set_suicide_frameP9entvars_s", set_suicide_frame),	// NOXREF
	HOOK_SYMBOLDEF(0x01D63D30, "_Z13ClientConnectP7edict_sPKcS2_Pc", ClientConnect),
	HOOK_SYMBOLDEF(0x01D63D50, "_Z16ClientDisconnectP7edict_s", ClientDisconnect),
	HOOK_SYMBOLDEF(0x01D63E50, "_Z7respawnP9entvars_si", respawn),
	HOOK_SYMBOLDEF(0x01D63F60, "_Z10ClientKillP7edict_s", ClientKill),
	HOOK_SYMBOLDEF(0x01D64010, "_Z8ShowMenuP11CBasePlayeriiiPc_constprop_32", ShowMenu),
	//HOOK_SYMBOLDEF(0x01D64070, "_Z12ShowVGUIMenuP11CBasePlayeriiPc", ShowVGUIMenu),
	HOOK_DEF(0x01D64130, CountTeams),				//extern c func
	HOOK_SYMBOLDEF(0x01D64260, "_Z11ListPlayersP11CBasePlayer", ListPlayers),
	HOOK_DEF(0x01D64460, CountTeamPlayers),			//extern c func
	HOOK_SYMBOLDEF(0x01D64580, "_Z15ProcessKickVoteP11CBasePlayerS0_", ProcessKickVote),
	//HOOK_SYMBOLDEF(0x01D64920, "_Z17SelectDefaultTeamv", SelectDefaultTeam),
	HOOK_SYMBOLDEF(0x01D649A0, "_Z15CheckStartMoneyv", CheckStartMoney),
	HOOK_SYMBOLDEF(0x01D649F0, "_Z17ClientPutInServerP7edict_s", ClientPutInServer),
	//HOOK_DEF(0x01D64F00, Q_strlen_),	// NOXREF
	HOOK_SYMBOLDEF(0x01D64F20, "_Z8Host_SayP7edict_si", Host_Say),
	//HOOK_DEF(0x0, DropSecondary), // NOXREF
	//HOOK_SYMBOLDEF(0x01D656F0, "_Z11DropPrimaryP11CBasePlayer", DropPrimary),
	HOOK_SYMBOLDEF(0x01D65740, "_Z10CanBuyThisP11CBasePlayeri", CanBuyThis),
	HOOK_SYMBOLDEF(0x01D65850, "_Z9BuyPistolP11CBasePlayeri", BuyPistol),
	HOOK_SYMBOLDEF(0x01D65A30, "_Z10BuyShotgunP11CBasePlayeri", BuyShotgun),
	HOOK_SYMBOLDEF(0x01D65B70, "_Z16BuySubMachineGunP11CBasePlayeri", BuySubMachineGun),
	//HOOK_SYMBOLDEF(0x01D65D00, "_Z19BuyWeaponByWeaponIDP11CBasePlayer12WeaponIdType", BuyWeaponByWeaponID),
	HOOK_SYMBOLDEF(0x01D65E80, "_Z8BuyRifleP11CBasePlayeri", BuyRifle),
	HOOK_SYMBOLDEF(0x01D66070, "_Z13BuyMachineGunP11CBasePlayeri", BuyMachineGun),
	HOOK_SYMBOLDEF(0x01D66170, "_Z7BuyItemP11CBasePlayeri", BuyItem),
	HOOK_SYMBOLDEF(0x01D669A0, "_Z27HandleMenu_ChooseAppearanceP11CBasePlayeri", HandleMenu_ChooseAppearance),
	HOOK_SYMBOLDEF(0x01D66D10, "_Z21HandleMenu_ChooseTeamP11CBasePlayeri", HandleMenu_ChooseTeam),
	HOOK_SYMBOLDEF(0x01D67930, "_Z6Radio1P11CBasePlayeri", Radio1),
	HOOK_SYMBOLDEF(0x01D67A20, "_Z6Radio2P11CBasePlayeri", Radio2),
	HOOK_SYMBOLDEF(0x01D67B10, "_Z6Radio3P11CBasePlayeri", Radio3),
	HOOK_SYMBOLDEF(0x01D67C70, "_Z10BuyGunAmmoR11CBasePlayerR15CBasePlayerItemb", BuyGunAmmo),
	//HOOK_SYMBOLDEF(0x01D67E50, "_Z7BuyAmmoP11CBasePlayerib", BuyAmmo),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D67EC0, "_Z16EntityFromUserIDi", EntityFromUserID),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D67FC0, "_Z20CountPlayersInServerv", CountPlayersInServer),	// NOXREF
	HOOK_SYMBOLDEF(0x01D680D0, "_Z22HandleBuyAliasCommandsP11CBasePlayerPKc", HandleBuyAliasCommands),
	HOOK_SYMBOLDEF(0x01D68540, "_Z24HandleRadioAliasCommandsP11CBasePlayerPKc", HandleRadioAliasCommands),
	HOOK_SYMBOLDEF(0x01D68840, "_Z13ClientCommandP7edict_s", ClientCommand_),
	HOOK_SYMBOLDEF(0x01D6B230, "_Z21ClientUserInfoChangedP7edict_sPc", ClientUserInfoChanged),
	HOOK_SYMBOLDEF(0x01D6B4D0, "_Z16ServerDeactivatev", ServerDeactivate),
	HOOK_SYMBOLDEF(0x01D6B520, "_Z14ServerActivateP7edict_sii", ServerActivate),
	HOOK_SYMBOLDEF(0x01D6B620, "_Z14PlayerPreThinkP7edict_s", PlayerPreThink),
	HOOK_SYMBOLDEF(0x01D6B640, "_Z15PlayerPostThinkP7edict_s", PlayerPostThink),
	//HOOK_SYMBOLDEF(0x01D6B660, "_Z13ParmsNewLevelv", ParmsNewLevel),	// PURE
	HOOK_SYMBOLDEF(0x01D6B670, "_Z16ParmsChangeLevelv", ParmsChangeLevel),
	HOOK_SYMBOLDEF(0x01D6B6A0, "_Z10StartFramev", StartFrame),
	HOOK_SYMBOLDEF(0x01D6B740, "_Z14ClientPrecachev", ClientPrecache),
	HOOK_SYMBOLDEF(0x01D6CCE0, "_Z18GetGameDescriptionv", GetGameDescription),
	HOOK_SYMBOLDEF(0x01D6CD00, "_Z9Sys_ErrorPKc", SysEngine_Error),
	HOOK_SYMBOLDEF(0x01D6CD10, "_Z19PlayerCustomizationP7edict_sP15customization_s", PlayerCustomization),
	HOOK_SYMBOLDEF(0x01D6CD90, "_Z16SpectatorConnectP7edict_s", SpectatorConnect),
	HOOK_SYMBOLDEF(0x01D6CDB0, "_Z19SpectatorDisconnectP7edict_s", SpectatorDisconnect),
	HOOK_SYMBOLDEF(0x01D6CDD0, "_Z14SpectatorThinkP7edict_s", SpectatorThink),
	HOOK_SYMBOLDEF(0x01D6CDF0, "_Z15SetupVisibilityP7edict_sS0_PPhS2_", SetupVisibility),
	//HOOK_SYMBOLDEF(0x01D6CF60, "_Z14ResetPlayerPVSP7edict_si", ResetPlayerPVS),						// NOXREF
	//HOOK_SYMBOLDEF(0x01D6CFB0, "_Z25CheckPlayerPVSLeafChangedP7edict_si", CheckPlayerPVSLeafChanged),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D6D020, "_Z15MarkEntityInPVSiifb", MarkEntityInPVS),							// NOXREF
	//HOOK_SYMBOLDEF(0x01D6D060, "_Z24CheckEntityRecentlyInPVSiif", CheckEntityRecentlyInPVS),			// NOXREF
	HOOK_SYMBOLDEF(0x01D6D0B0, "_Z13AddToFullPackP14entity_state_siP7edict_sS2_iiPh", AddToFullPack),
	HOOK_SYMBOLDEF(0x01D6D5F0, "_Z14CreateBaselineiiP14entity_state_sP7edict_si6VectorS3_", CreateBaseline),
	//HOOK_SYMBOLDEF(0x01D6D790, "_Z16Entity_FieldInitP7delta_s", Entity_FieldInit),	// NOXREF
	HOOK_SYMBOLDEF(0x01D6D800, "_Z13Entity_EncodeP7delta_sPKhS2_", Entity_Encode),
	//HOOK_SYMBOLDEF(0x01D6D9C0, "_Z16Player_FieldInitP7delta_s", Player_FieldInit),	// NOXREF
	HOOK_SYMBOLDEF(0x01D6DA00, "_Z13Player_EncodeP7delta_sPKhS2_", Player_Encode),
	HOOK_SYMBOLDEF(0x01D6DB10, "_Z23Custom_Entity_FieldInitP7delta_s", Custom_Entity_FieldInit),
	HOOK_SYMBOLDEF(0x01D6DBC0, "_Z13Custom_EncodeP7delta_sPKhS2_", Custom_Encode),
	HOOK_SYMBOLDEF(0x01D6DCB0, "_Z16RegisterEncodersv", RegisterEncoders),
	HOOK_SYMBOLDEF(0x01D6DCF0, "_Z13GetWeaponDataP7edict_sP13weapon_data_s", GetWeaponData),
	HOOK_SYMBOLDEF(0x01D6DF00, "_Z16UpdateClientDataPK7edict_siP12clientdata_s", UpdateClientData),
	HOOK_SYMBOLDEF(0x01D6E2F0, "_Z8CmdStartPK7edict_sPK9usercmd_sj", CmdStart),
	HOOK_SYMBOLDEF(0x01D6E360, "_Z6CmdEndPK7edict_s", CmdEnd),
	HOOK_SYMBOLDEF(0x01D6E410, "_Z20ConnectionlessPacketPK8netadr_sPKcPcPi", ConnectionlessPacket),
	HOOK_SYMBOLDEF(0x01D6E420, "_Z13GetHullBoundsiPfS_", GetHullBounds),
	HOOK_SYMBOLDEF(0x01D6E440, "_Z24CreateInstancedBaselinesv", CreateInstancedBaselines),
	HOOK_SYMBOLDEF(0x01D6E450, "_Z16InconsistentFilePK7edict_sPKcPc", InconsistentFile),
	HOOK_SYMBOLDEF(0x01D6E490, "_Z20AllowLagCompensationv", AllowLagCompensation),

#endif // Client_Region

#ifndef Cbase_Region

	// base func
	HOOK_SYMBOLDEF(0x01D61A30, "_Z19CaseInsensitiveHashPKci", CaseInsensitiveHash),
	HOOK_SYMBOLDEF(0x01D61A70, "_Z20EmptyEntityHashTablev", EmptyEntityHashTable),
	HOOK_SYMBOLDEF(0x01D61AE0, "_Z18AddEntityHashValueP9entvars_sPKc12hash_types_e", AddEntityHashValue),
	HOOK_SYMBOLDEF(0x01D61CA0, "_Z21RemoveEntityHashValueP9entvars_sPKc12hash_types_e", RemoveEntityHashValue),
	HOOK_SYMBOLDEF(0x01D61E20, "_Z13printEntitiesv", SV_PrintEntities_f),
	HOOK_SYMBOLDEF(0x01D61ED0, "_Z19CREATE_NAMED_ENTITYj", CREATE_NAMED_ENTITY),
	HOOK_SYMBOLDEF(0x01D61F10, "_Z13REMOVE_ENTITYP7edict_s", REMOVE_ENTITY),
	HOOK_SYMBOLDEF(0x01D62540, "_Z12CONSOLE_ECHOPcz", CONSOLE_ECHO),
	HOOK_SYMBOLDEF(0x01D61F30, "_Z15loopPerformancev", SV_LoopPerformance_f),
	HOOK_DEF(0x01D62570, GetEntityAPI),
	//HOOK_SYMBOLDEF(0x01D62670, "_Z13GetEntityAPI2P13DLL_FUNCTIONSPi", GetEntityAPI2),	// NOXREF
	HOOK_DEF(0x01D626B0, GetNewDLLFunctions),
	//HOOK_SYMBOLDEF(0x01D62B20, "_Z16FindGlobalEntityjj", FindGlobalEntity),	// NOXREF
	HOOK_SYMBOLDEF(0x01D63700, "_ZL21SetObjectCollisionBoxP9entvars_s", SetObjectCollisionBox),
	HOOK_SYMBOLDEF(0x01D63BE0, "_Z20OnFreeEntPrivateDataP7edict_s", OnFreeEntPrivateData),
	HOOK_SYMBOLDEF(0x01D80630, "_Z11GameDLLInitv", GameDLLInit),
	//HOOK_SYMBOLDEF(0x01DB6BD0, "_Z12GetSkillCvarPc", GetSkillCvar),		//NOXREF
	HOOK_SYMBOLDEF(0x01D626F0, "_Z13DispatchSpawnP7edict_s", DispatchSpawn),
	HOOK_SYMBOLDEF(0x01D629D0, "_Z13DispatchThinkP7edict_s", DispatchThink),
	HOOK_SYMBOLDEF(0x01D62990, "_Z11DispatchUseP7edict_sS0_", DispatchUse),
	HOOK_SYMBOLDEF(0x01D62930, "_Z13DispatchTouchP7edict_sS0_", DispatchTouch),
	HOOK_SYMBOLDEF(0x01D62A20, "_Z15DispatchBlockedP7edict_sS0_", DispatchBlocked),
	HOOK_SYMBOLDEF(0x01D628F0, "_Z16DispatchKeyValueP7edict_sP14KeyValueData_s", DispatchKeyValue),
	HOOK_SYMBOLDEF(0x01D62A50, "_Z12DispatchSaveP7edict_sP13saverestore_s", DispatchSave),
	HOOK_SYMBOLDEF(0x01D62BD0, "_Z15DispatchRestoreP7edict_sP13saverestore_si", DispatchRestore),
	HOOK_SYMBOLDEF(0x01D62FF0, "_Z25DispatchObjectCollsionBoxP7edict_s", DispatchObjectCollsionBox),
	HOOK_SYMBOLDEF(0x01D63020, "_Z15SaveWriteFieldsP13saverestore_sPKcPvP15TYPEDESCRIPTIONi", SaveWriteFields),
	HOOK_SYMBOLDEF(0x01D63060, "_Z14SaveReadFieldsP13saverestore_sPKcPvP15TYPEDESCRIPTIONi", SaveReadFields),

	// virtual func
//CBaseEntity
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D18590, "_ZN11CBaseEntity5SpawnEv", CBaseEntity::Spawn),		// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D185A0, "_ZN11CBaseEntity8PrecacheEv", CBaseEntity::Precache),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01B90, "_ZN11CBaseEntity7RestartEv", CBaseEntity::Restart),		// PURE
	////HOOK_SYMBOL_VIRTUAL_DEF(0x01D185B0, "_ZN11CBaseEntity8KeyValueEP14KeyValueData_s", CBaseEntity::KeyValue),	// default
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D635D0, "_ZN11CBaseEntity4SaveER5CSave", CBaseEntity::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D63610, "_ZN11CBaseEntity7RestoreER8CRestore", CBaseEntity::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01BA0, "_ZN11CBaseEntity10ObjectCapsEv", CBaseEntity::ObjectCaps),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01BB0, "_ZN11CBaseEntity8ActivateEv", CBaseEntity::Activate),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D638B0, "_ZN11CBaseEntity21SetObjectCollisionBoxEv", CBaseEntity::SetObjectCollisionBox),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01BC0, "_ZN11CBaseEntity8ClassifyEv", CBaseEntity::Classify),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01BD0, "_ZN11CBaseEntity11DeathNoticeEP9entvars_s", CBaseEntity::DeathNotice),	// default
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D719D0, "_ZN11CBaseEntity11TraceAttackEP9entvars_sf6VectorP11TraceResulti", CBaseEntity::TraceAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D63210, "_ZN11CBaseEntity10TakeDamageEP9entvars_sS1_fi", CBaseEntity::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D63190, "_ZN11CBaseEntity10TakeHealthEfi", CBaseEntity::TakeHealth),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D63550, "_ZN11CBaseEntity6KilledEP9entvars_si", CBaseEntity::Killed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01BE0, "_ZN11CBaseEntity10BloodColorEv", CBaseEntity::BloodColor),	// default
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D72EE0, "_ZN11CBaseEntity10TraceBleedEf6VectorP11TraceResulti", CBaseEntity::TraceBleed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01BF0, "_ZN11CBaseEntity11IsTriggeredEPS_", CBaseEntity::IsTriggered),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C00, "_ZN11CBaseEntity16MyMonsterPointerEv", CBaseEntity::MyMonsterPointer),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C10, "_ZN11CBaseEntity21MySquadMonsterPointerEv", CBaseEntity::MySquadMonsterPointer),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C20, "_ZN11CBaseEntity14GetToggleStateEv", CBaseEntity::GetToggleState),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C30, "_ZN11CBaseEntity9AddPointsEii", CBaseEntity::AddPoints),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C40, "_ZN11CBaseEntity15AddPointsToTeamEii", CBaseEntity::AddPointsToTeam),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C50, "_ZN11CBaseEntity13AddPlayerItemEP15CBasePlayerItem", CBaseEntity::AddPlayerItem),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C60, "_ZN11CBaseEntity16RemovePlayerItemEP15CBasePlayerItem", CBaseEntity::RemovePlayerItem),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C70, "_ZN11CBaseEntity8GiveAmmoEiPci", CBaseEntity::GiveAmmo),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C80, "_ZN11CBaseEntity8GetDelayEv", CBaseEntity::GetDelay),			// DEFAULT
	////HOOK_SYMBOL_VIRTUAL_DEF(0x01D01C90, "_ZN11CBaseEntity8IsMovingEv", CBaseEntity::IsMoving),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01CE0, "_ZN11CBaseEntity13OverrideResetEv", CBaseEntity::OverrideReset),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D63AF0, "_ZN11CBaseEntity11DamageDecalEi", CBaseEntity::DamageDecal),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01CF0, "_ZN11CBaseEntity14SetToggleStateEi", CBaseEntity::SetToggleState),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D00, "_ZN11CBaseEntity13StartSneakingEv", CBaseEntity::StartSneaking),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D10, "_ZN11CBaseEntity12StopSneakingEv", CBaseEntity::StopSneaking),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D20, "_ZN11CBaseEntity10OnControlsEP9entvars_s", CBaseEntity::OnControls),	// default
	////HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D30, "_ZN11CBaseEntity10IsSneakingEv", CBaseEntity::IsSneaking),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D40, "_ZN11CBaseEntity7IsAliveEv", CBaseEntity::IsAlive),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D70, "_ZN11CBaseEntity10IsBSPModelEv", CBaseEntity::IsBSPModel),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01D90, "_ZN11CBaseEntity12ReflectGaussEv", CBaseEntity::ReflectGauss),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01DC0, "_ZN11CBaseEntity9HasTargetEj", CBaseEntity::HasTarget),	// default
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D639C0, "_ZN11CBaseEntity9IsInWorldEv", CBaseEntity::IsInWorld),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01E30, "_ZN11CBaseEntity8IsPlayerEv", CBaseEntity::IsPlayer),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01E40, "_ZN11CBaseEntity11IsNetClientEv", CBaseEntity::IsNetClient),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01E50, "_ZN11CBaseEntity6TeamIDEv", CBaseEntity::TeamID),	// default
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D63580, "_ZN11CBaseEntity13GetNextTargetEv", CBaseEntity::GetNextTarget),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01E60, "_ZN11CBaseEntity5ThinkEv", CBaseEntity::Think),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01E70, "_ZN11CBaseEntity5TouchEPS_", CBaseEntity::Touch),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01E80, "_ZN11CBaseEntity3UseEPS_S0_8USE_TYPEf", CBaseEntity::Use),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01EA0, "_ZN11CBaseEntity7BlockedEPS_", CBaseEntity::Blocked),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D18B00, "_ZN11CBaseEntity7RespawnEv", CBaseEntity::Respawn),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01EC0, "_ZN11CBaseEntity11UpdateOwnerEv", CBaseEntity::UpdateOwner),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01ED0, "_ZN11CBaseEntity12FBecomeProneEv", CBaseEntity::FBecomeProne),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01EE0, "_ZN11CBaseEntity6CenterEv", CBaseEntity::Center),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01F40, "_ZN11CBaseEntity11EyePositionEv", CBaseEntity::EyePosition),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01F70, "_ZN11CBaseEntity11EarPositionEv", CBaseEntity::EarPosition),	// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01FA0, "_ZN11CBaseEntity10BodyTargetERK6Vector", CBaseEntity::BodyTarget),// default
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01FC0, "_ZN11CBaseEntity12IlluminationEv", CBaseEntity::Illumination),	// default
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D71840, "_ZN11CBaseEntity8FVisibleEPS_", CBaseEntity::FVisible, BOOL (CBaseEntity *)),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D71950, "_ZN11CBaseEntity8FVisibleERK6Vector", CBaseEntity::FVisible, BOOL (const Vector &)),

	// non-virtual func
	//HOOK_DEF(0x01DA7FD0, CBaseEntity::Instance, CBaseEntity *(edict_t *)),
	HOOK_SYMBOLDEF(0x01DBAF90, "_ZN11CBaseEntity14UpdateOnRemoveEv", CBaseEntity::UpdateOnRemove),
	HOOK_SYMBOLDEF(0x01DBAFF0, "_ZN11CBaseEntity10SUB_RemoveEv", CBaseEntity::SUB_Remove),
	HOOK_SYMBOLDEF(0x01DBB0A0, "_ZN11CBaseEntity13SUB_DoNothingEv", CBaseEntity::SUB_DoNothing),
	HOOK_SYMBOLDEF(0x01D6FB10, "_ZN11CBaseEntity16SUB_StartFadeOutEv", CBaseEntity::SUB_StartFadeOut),
	HOOK_SYMBOLDEF(0x01D6FB80, "_ZN11CBaseEntity11SUB_FadeOutEv", CBaseEntity::SUB_FadeOut),
	HOOK_SYMBOLDEF(0x01D01EB0, "_ZN11CBaseEntity17SUB_CallUseToggleEv", CBaseEntity::SUB_CallUseToggle),
	HOOK_SYMBOLDEF(0x01D63AC0, "_ZN11CBaseEntity12ShouldToggleE8USE_TYPEi", CBaseEntity::ShouldToggle),
	HOOK_SYMBOLDEF(0x01D71BC0, "_ZN11CBaseEntity11FireBulletsEj6VectorS0_S0_fiiiP9entvars_s", CBaseEntity::FireBullets),
	HOOK_SYMBOLDEF(0x01D72480, "_ZN11CBaseEntity12FireBullets3E6VectorS0_ffiiifP9entvars_sbi", CBaseEntity::FireBullets3),
	HOOK_SYMBOLDEF(0x01DBB190, "_ZN11CBaseEntity14SUB_UseTargetsEPS_8USE_TYPEf", CBaseEntity::SUB_UseTargets),
	HOOK_SYMBOLDEF(0x01DBB260, "_Z11FireTargetsPKcP11CBaseEntityS2_8USE_TYPEf", FireTargets),
	//HOOK_SYMBOLDEF(0x01D638C0, "_ZN11CBaseEntity10IntersectsEPS_", CBaseEntity::Intersects),
	//HOOK_SYMBOLDEF(0x01D63950, "_ZN11CBaseEntity11MakeDormantEv", CBaseEntity::MakeDormant), // NOXREF
	HOOK_SYMBOLDEF(0x01D639B0, "_ZN11CBaseEntity9IsDormantEv", CBaseEntity::IsDormant),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBaseEntity16IsLockedByMasterEv", CBaseEntity::IsLockedByMaster), // NOXREF
	HOOK_SYMBOLDEF(0x01D63B20, "_ZN11CBaseEntity6CreateEPcRK6VectorS3_P7edict_s", CBaseEntity::Create),
//CPointEntity
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBACC0, "_ZN12CPointEntity5SpawnEv", CPointEntity::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D60CB0, "_ZN12CPointEntity10ObjectCapsEv", CPointEntity::ObjectCaps),	// default
//CNullEntity
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBACD0, "_ZN11CNullEntity5SpawnEv", CNullEntity::Spawn),
//CBaseDMStart
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBAF20, "_ZN12CBaseDMStart8KeyValueEP14KeyValueData_s", CBaseDMStart::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBAF70, "_ZN12CBaseDMStart11IsTriggeredEP11CBaseEntity", CBaseDMStart::IsTriggered),
//CBaseDelay
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBB110, "_ZN10CBaseDelay8KeyValueEP14KeyValueData_s", CBaseDelay::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBB0B0, "_ZN10CBaseDelay4SaveER5CSave", CBaseDelay::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBB0E0, "_ZN10CBaseDelay7RestoreER8CRestore", CBaseDelay::Restore),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBB620, "_Z10SetMovedirP9entvars_s", SetMovedir),
	HOOK_SYMBOLDEF(0x01DBB360, "_ZN10CBaseDelay14SUB_UseTargetsEP11CBaseEntity8USE_TYPEf", CBaseDelay::SUB_UseTargets),
	HOOK_SYMBOLDEF(0x01DBB730, "_ZN10CBaseDelay10DelayThinkEv", CBaseDelay::DelayThink),
//CBaseAnimating
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59E70, "_ZN14CBaseAnimating4SaveER5CSave", CBaseAnimating::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59EA0, "_ZN14CBaseAnimating7RestoreER8CRestore", CBaseAnimating::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01FE0, "_ZN14CBaseAnimating15HandleAnimEventEP14MonsterEvent_t", CBaseAnimating::HandleAnimEvent),	// PURE
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D59ED0, "_ZN14CBaseAnimating18StudioFrameAdvanceEf", CBaseAnimating::StudioFrameAdvance),
	//HOOK_SYMBOLDEF(0x01D5A130, "_ZN14CBaseAnimating16GetSequenceFlagsEv", CBaseAnimating::GetSequenceFlags),	// NOXREF
	HOOK_SYMBOLDEF(0x01D5A010, "_ZN14CBaseAnimating14LookupActivityEi", CBaseAnimating::LookupActivity),
	HOOK_SYMBOLDEF(0x01D5A040, "_ZN14CBaseAnimating22LookupActivityHeaviestEi", CBaseAnimating::LookupActivityHeaviest),
	HOOK_SYMBOLDEF(0x01D5A070, "_ZN14CBaseAnimating14LookupSequenceEPKc", CBaseAnimating::LookupSequence),
	HOOK_SYMBOLDEF(0x01D5A0A0, "_ZN14CBaseAnimating17ResetSequenceInfoEv", CBaseAnimating::ResetSequenceInfo),
	HOOK_SYMBOLDEF(0x01D5A160, "_ZN14CBaseAnimating18DispatchAnimEventsEf", CBaseAnimating::DispatchAnimEvents),
	HOOK_SYMBOLDEF(0x01D5A280, "_ZN14CBaseAnimating17SetBoneControllerEif", CBaseAnimating::SetBoneController),
	HOOK_SYMBOLDEF(0x01D5A2B0, "_ZN14CBaseAnimating19InitBoneControllersEv", CBaseAnimating::InitBoneControllers),
	//HOOK_SYMBOLDEF(0x01D5A310, "_ZN14CBaseAnimating11SetBlendingEif", CBaseAnimating::SetBlending),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A340, "_ZN14CBaseAnimating15GetBonePositionEiR6VectorS1_", CBaseAnimating::GetBonePosition),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A370, "_ZN14CBaseAnimating13GetAttachmentEiR6VectorS1_", CBaseAnimating::GetAttachment),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A3A0, "_ZN14CBaseAnimating14FindTransitionEiiPi", CBaseAnimating::FindTransition),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A400, "_ZN14CBaseAnimating15GetAutomovementER6VectorS1_f", CBaseAnimating::GetAutomovement),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A410, "_ZN14CBaseAnimating12SetBodygroupEii", CBaseAnimating::SetBodygroup),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A440, "_ZN14CBaseAnimating12GetBodygroupEi", CBaseAnimating::GetBodygroup),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A470, "_ZN14CBaseAnimating11ExtractBboxEiPfS0_", CBaseAnimating::ExtractBbox),	// NOXREF
	HOOK_SYMBOLDEF(0x01D5A4A0, "_ZN14CBaseAnimating14SetSequenceBoxEv", CBaseAnimating::SetSequenceBox),
//CBaseToggle
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBB7D0, "_ZN11CBaseToggle8KeyValueEP14KeyValueData_s", CBaseToggle::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBB770, "_ZN11CBaseToggle4SaveER5CSave", CBaseToggle::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBB7A0, "_ZN11CBaseToggle7RestoreER8CRestore", CBaseToggle::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20F20, "_ZN11CBaseToggle14GetToggleStateEv", CBaseToggle::GetToggleState),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20F30, "_ZN11CBaseToggle8GetDelayEv", CBaseToggle::GetDelay),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBB920, "_ZN11CBaseToggle10LinearMoveE6Vectorf", CBaseToggle::LinearMove),
	HOOK_SYMBOLDEF(0x01DBBA60, "_ZN11CBaseToggle14LinearMoveDoneEv", CBaseToggle::LinearMoveDone),
	HOOK_SYMBOLDEF(0x01DBBAC0, "_ZN11CBaseToggle16IsLockedByMasterEv", CBaseToggle::IsLockedByMaster),	// NOXREF
	HOOK_SYMBOLDEF(0x01DBBB00, "_ZN11CBaseToggle11AngularMoveE6Vectorf", CBaseToggle::AngularMove),
	HOOK_SYMBOLDEF(0x01DBBC40, "_ZN11CBaseToggle15AngularMoveDoneEv", CBaseToggle::AngularMoveDone),
	HOOK_SYMBOLDEF(0x01DBBCA0, "_ZN11CBaseToggle9AxisValueEiRK6Vector", CBaseToggle::AxisValue),
	HOOK_SYMBOLDEF(0x01DBBCD0, "_ZN11CBaseToggle7AxisDirEP9entvars_s", CBaseToggle::AxisDir),
	HOOK_SYMBOLDEF(0x01DBBD60, "_ZN11CBaseToggle9AxisDeltaEiRK6VectorS2_", CBaseToggle::AxisDelta),
	//HOOK_SYMBOLDEF(0x01DBBDA0, "_Z13FEntIsVisibleP9entvars_sS0_", FEntIsVisible),		// NOXREF

//CWorld
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD1EE0, "_ZN6CWorld5SpawnEv", CWorld::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD2000, "_ZN6CWorld8PrecacheEv", CWorld::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD2440, "_ZN6CWorld8KeyValueEP14KeyValueData_s", CWorld::KeyValue),

//linked objects
	HOOK_DEF(0x01DBACF0, info_null),
	HOOK_DEF(0x01DBAD40, info_player_deathmatch),
	HOOK_DEF(0x01DBAD90, info_player_start),
	HOOK_DEF(0x01DBADE0, info_vip_start),
	HOOK_DEF(0x01DBAE30, info_landmark),
	HOOK_DEF(0x01DBAE80, info_hostage_rescue),
	HOOK_DEF(0x01DBAED0, info_bomb_target),
	HOOK_DEF(0x01DBB310, DelayedUse),

#endif // Cbase_Region

#ifndef Spectator_Region

	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBAC90, "_ZN14CBaseSpectator5SpawnEv", CBaseSpectator::Spawn),	// NOXREF
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DBAB20, "_ZN14CBaseSpectator16SpectatorConnectEv", CBaseSpectator::SpectatorConnect),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBAB50, "_ZN14CBaseSpectator19SpectatorDisconnectEv", CBaseSpectator::SpectatorDisconnect),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBAC40, "_ZN14CBaseSpectator14SpectatorThinkEv", CBaseSpectator::SpectatorThink),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBAB60, "_ZN14CBaseSpectator23SpectatorImpulseCommandEv", CBaseSpectator::SpectatorImpulseCommand),

#endif // Spectator_Region

#ifndef BaseMonster_Region

	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8AD30, "_ZN12CBaseMonster8KeyValueEP14KeyValueData_s", CBaseMonster::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D71AA0, "_ZN12CBaseMonster11TraceAttackEP9entvars_sf6VectorP11TraceResulti", CBaseMonster::TraceAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D70180, "_ZN12CBaseMonster10TakeDamageEP9entvars_sS1_fi", CBaseMonster::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D70130, "_ZN12CBaseMonster10TakeHealthEfi", CBaseMonster::TakeHealth),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F9D0, "_ZN12CBaseMonster6KilledEP9entvars_si", CBaseMonster::Killed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20F50, "_ZN12CBaseMonster10BloodColorEv", CBaseMonster::BloodColor),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D24CF0, "_ZN12CBaseMonster7IsAliveEv", CBaseMonster::IsAlive),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8ABF0, "_ZN12CBaseMonster9ChangeYawEi", CBaseMonster::ChangeYaw),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F360, "_ZN12CBaseMonster12HasHumanGibsEv", CBaseMonster::HasHumanGibs),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F390, "_ZN12CBaseMonster12HasAlienGibsEv", CBaseMonster::HasAlienGibs),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F3C0, "_ZN12CBaseMonster11FadeMonsterEv", CBaseMonster::FadeMonster),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F4B0, "_ZN12CBaseMonster10GibMonsterEv", CBaseMonster::GibMonster),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F5A0, "_ZN12CBaseMonster16GetDeathActivityEv", CBaseMonster::GetDeathActivity),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D6F880, "_ZN12CBaseMonster10BecomeDeadEv", CBaseMonster::BecomeDead),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8AD10, "_ZN12CBaseMonster17ShouldFadeOnDeathEv", CBaseMonster::ShouldFadeOnDeath),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8AD40, "_ZN12CBaseMonster13IRelationshipEP11CBaseEntity", CBaseMonster::IRelationship),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20F40, "_ZN12CBaseMonster9PainSoundEv", CBaseMonster::PainSound),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D24AD0, "_ZN12CBaseMonster13ResetMaxSpeedEv", CBaseMonster::ResetMaxSpeed),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D8ABE0, "_ZN12CBaseMonster13ReportAIStateEv", CBaseMonster::ReportAIState),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8AC60, "_ZN12CBaseMonster15MonsterInitDeadEv", CBaseMonster::MonsterInitDead),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8AD70, "_ZN12CBaseMonster4LookEi", CBaseMonster::Look),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8AF10, "_ZN12CBaseMonster16BestVisibleEnemyEv", CBaseMonster::BestVisibleEnemy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D716D0, "_ZN12CBaseMonster11FInViewConeEP11CBaseEntity", CBaseMonster::FInViewCone, BOOL (CBaseEntity *)),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D71790, "_ZN12CBaseMonster11FInViewConeEP6Vector", CBaseMonster::FInViewCone, BOOL (const Vector *)),

	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D8AC00, "_ZN12CBaseMonster12MakeIdealYawE6Vector", CBaseMonster::MakeIdealYaw),	// PURE
	//HOOK_SYMBOLDEF(0x01D6F7F0, "_ZN12CBaseMonster22GetSmallFlinchActivityEv", CBaseMonster::GetSmallFlinchActivity),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D6F8C0, "_ZN12CBaseMonster16ShouldGibMonsterEi", CBaseMonster::ShouldGibMonster),	// NOXREF
	HOOK_SYMBOLDEF(0x01D6F8F0, "_ZN12CBaseMonster14CallGibMonsterEv", CBaseMonster::CallGibMonster),
	HOOK_SYMBOLDEF(0x01D8AD20, "_ZN12CBaseMonster15FCheckAITriggerEv", CBaseMonster::FCheckAITrigger),
	HOOK_SYMBOLDEF(0x01D705B0, "_ZN12CBaseMonster14DeadTakeDamageEP9entvars_sS1_fi", CBaseMonster::DeadTakeDamage),
	//HOOK_SYMBOLDEF(0x01D707C0, "_ZN12CBaseMonster11DamageForceEf", CBaseMonster::DamageForce),	// NOXREF
	HOOK_SYMBOLDEF(0x01D71470, "_ZN12CBaseMonster12RadiusDamageEP9entvars_sS1_fii", CBaseMonster::RadiusDamage, void (entvars_t *, entvars_t *, float, int, int)),
	//HOOK_SYMBOLDEF(0x01D71520, "_ZN12CBaseMonster12RadiusDamageE6VectorP9entvars_sS2_fii", CBaseMonster::RadiusDamage, void(Vector, entvars_t *, entvars_t *, float, int, int)),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CBaseMonster13RadiusDamage2E6VectorP9entvars_sS2_fii", CBaseMonster::RadiusDamage2),	// NOXREF
	HOOK_SYMBOLDEF(0x01D8AC10, "_ZN12CBaseMonster15CorpseFallThinkEv", CBaseMonster::CorpseFallThink),
	//HOOK_SYMBOLDEF(0x01D715D0, "_ZN12CBaseMonster20CheckTraceHullAttackEfii", CBaseMonster::CheckTraceHullAttack),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D730E0, "_ZN12CBaseMonster20MakeDamageBloodDecalEifP11TraceResultRK6Vector", CBaseMonster::MakeDamageBloodDecal),	// NOXREF
	HOOK_SYMBOLDEF(0x01D73240, "_ZN12CBaseMonster10BloodSplatER6VectorS1_ii", CBaseMonster::BloodSplat),
	HOOK_SYMBOLDEF(0x01D70800, "_Z11RadiusFlash6VectorP9entvars_sS1_fii", RadiusFlash),
	//HOOK_SYMBOLDEF(0x0, "_ZL24GetAmountOfPlayerVisible6VectorP11CBaseEntity_constprop_21", GetAmountOfPlayerVisible),	// NOXREF
	HOOK_SYMBOLDEF(0x01D70CA0, "_Z12RadiusDamage6VectorP9entvars_sS1_ffii", RadiusDamage),
	HOOK_SYMBOLDEF(0x01D711B0, "_Z13RadiusDamage26VectorP9entvars_sS1_ffii", RadiusDamage2),
	//HOOK_SYMBOLDEF(0x01D72430, "_Z4vstrPf", vstr),	// NOXREF

#endif // BaseMonster_Region

#ifndef Player_Region

//CBasePlayer
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA5200, "_ZN11CBasePlayer5SpawnEv", CBasePlayer::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA5E40, "_ZN11CBasePlayer8PrecacheEv", CBasePlayer::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA5EE0, "_ZN11CBasePlayer4SaveER5CSave", CBasePlayer::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA6080, "_ZN11CBasePlayer7RestoreER8CRestore", CBasePlayer::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D210A0, "_ZN11CBasePlayer10ObjectCapsEv", CBasePlayer::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA3550, "_ZN11CBasePlayer8ClassifyEv", CBasePlayer::Classify),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9BE00, "_ZN11CBasePlayer11TraceAttackEP9entvars_sf6VectorP11TraceResulti", CBasePlayer::TraceAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9C4C0, "_ZN11CBasePlayer10TakeDamageEP9entvars_sS1_fi", CBasePlayer::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9BD70, "_ZN11CBasePlayer10TakeHealthEfi", CBasePlayer::TakeHealth),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9E550, "_ZN11CBasePlayer6KilledEP9entvars_si", CBasePlayer::Killed),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA3560, "_ZN11CBasePlayer9AddPointsEii", CBasePlayer::AddPoints),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA3640, "_ZN11CBasePlayer15AddPointsToTeamEii", CBasePlayer::AddPointsToTeam),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA86C0, "_ZN11CBasePlayer13AddPlayerItemEP15CBasePlayerItem", CBasePlayer::AddPlayerItem),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA8960, "_ZN11CBasePlayer16RemovePlayerItemEP15CBasePlayerItem", CBasePlayer::RemovePlayerItem),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA8AA0, "_ZN11CBasePlayer8GiveAmmoEiPci", CBasePlayer::GiveAmmo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20FD0, "_ZN11CBasePlayer13StartSneakingEv", CBasePlayer::StartSneaking),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20FF0, "_ZN11CBasePlayer12StopSneakingEv", CBasePlayer::StopSneaking),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21010, "_ZN11CBasePlayer10IsSneakingEv", CBasePlayer::IsSneaking),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21030, "_ZN11CBasePlayer7IsAliveEv", CBasePlayer::IsAlive),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21070, "_ZN11CBasePlayer8IsPlayerEv", CBasePlayer::IsPlayer),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21090, "_ZN11CBasePlayer11IsNetClientEv", CBasePlayer::IsNetClient),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA6950, "_ZN11CBasePlayer6TeamIDEv", CBasePlayer::TeamID),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA9BF0, "_ZN11CBasePlayer12FBecomeProneEv", CBasePlayer::FBecomeProne),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D20F60, "_ZN11CBasePlayer10BodyTargetERK6Vector", CBasePlayer::BodyTarget),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA9C50, "_ZN11CBasePlayer12IlluminationEv", CBasePlayer::Illumination),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21060, "_ZN11CBasePlayer17ShouldFadeOnDeathEv", CBasePlayer::ShouldFadeOnDeath),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA9CB0, "_ZN11CBasePlayer13ResetMaxSpeedEv", CBasePlayer::ResetMaxSpeed),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA3310, "_ZN11CBasePlayer4JumpEv", CBasePlayer::Jump),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA3530, "_ZN11CBasePlayer4DuckEv", CBasePlayer::Duck),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA3850, "_ZN11CBasePlayer8PreThinkEv", CBasePlayer::PreThink),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA4610, "_ZN11CBasePlayer9PostThinkEv", CBasePlayer::PostThink),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9BD80, "_ZN11CBasePlayer14GetGunPositionEv", CBasePlayer::GetGunPosition),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D25AD0, "_ZN11CBasePlayer5IsBotEv", CBasePlayer::IsBot),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA8F90, "_ZN11CBasePlayer16UpdateClientDataEv", CBasePlayer::UpdateClientData),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA7020, "_ZN11CBasePlayer15ImpulseCommandsEv", CBasePlayer::ImpulseCommands),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA2490, "_ZN11CBasePlayer12RoundRespawnEv", CBasePlayer::RoundRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA9DC0, "_ZN11CBasePlayer16GetAutoaimVectorEf", CBasePlayer::GetAutoaimVector),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DAA220, "_ZN11CBasePlayer5BlindEfffi", CBasePlayer::Blind),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D25AE0, "_ZN11CBasePlayer16OnTouchingWeaponEP10CWeaponBox", CBasePlayer::OnTouchingWeapon),				// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DAC8D0, "_ZN11CBasePlayer21SpawnClientSideCorpseEv", CBasePlayer::SpawnClientSideCorpse),
	HOOK_SYMBOLDEF(0x01D93750, "_ZN11CBasePlayer23Observer_FindNextPlayerEbPKc", CBasePlayer::Observer_FindNextPlayer),
	HOOK_SYMBOLDEF(0x01D936E0, "_ZN11CBasePlayer22Observer_IsValidTargetEib", CBasePlayer::Observer_IsValidTarget),
	HOOK_SYMBOLDEF(0x01D93D10, "_ZN11CBasePlayer22Observer_HandleButtonsEv", CBasePlayer::Observer_HandleButtons),
	HOOK_SYMBOLDEF(0x01D94280, "_ZN11CBasePlayer16Observer_SetModeEi", CBasePlayer::Observer_SetMode),
	HOOK_SYMBOLDEF(0x01D93DF0, "_ZN11CBasePlayer20Observer_CheckTargetEv", CBasePlayer::Observer_CheckTarget),
	HOOK_SYMBOLDEF(0x01D93F30, "_ZN11CBasePlayer24Observer_CheckPropertiesEv", CBasePlayer::Observer_CheckProperties),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer10IsObserverEv", CBasePlayer::IsObserver),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer7PlantC4Ev", CBasePlayer::PlantC4),	// NOXREF
	HOOK_SYMBOLDEF(0x01D9B670, "_ZN11CBasePlayer5RadioEPKcS1_sb", CBasePlayer::Radio),
	//HOOK_SYMBOLDEF(0x01D9B4F0, "_ZN11CBasePlayer21GetNextRadioRecipientEPS_", CBasePlayer::GetNextRadioRecipient),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D9B9A0, "_ZN11CBasePlayer10SmartRadioEv", CBasePlayer::SmartRadio),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA07D0, "_ZN11CBasePlayer11ThrowWeaponEPc", CBasePlayer::ThrowWeapon),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA0DB0, "_ZN11CBasePlayer12ThrowPrimaryEv", CBasePlayer::ThrowPrimary),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA1170, "_ZN11CBasePlayer10AddAccountEib", CBasePlayer::AddAccount),
	HOOK_SYMBOLDEF(0x01DA1DA0, "_ZN11CBasePlayer9DisappearEv", CBasePlayer::Disappear),
	HOOK_SYMBOLDEF(0x01DA15B0, "_ZN11CBasePlayer7MakeVIPEv", CBasePlayer::MakeVIP),
	HOOK_SYMBOLDEF(0x01DA36C0, "_ZN11CBasePlayer12CanPlayerBuyEb", CBasePlayer::CanPlayerBuy),
	HOOK_SYMBOLDEF(0x01DAB070, "_ZN11CBasePlayer10SwitchTeamEv", CBasePlayer::SwitchTeam),
	HOOK_SYMBOLDEF(0x01DAB820, "_ZN11CBasePlayer12TabulateAmmoEv", CBasePlayer::TabulateAmmo),
	HOOK_SYMBOLDEF(0x01D9B9B0, "_ZN11CBasePlayer4PainEib", CBasePlayer::Pain),
	HOOK_SYMBOLDEF(0x01D9F410, "_ZN11CBasePlayer9IsBombGuyEv", CBasePlayer::IsBombGuy),
	HOOK_SYMBOLDEF(0x01DACC30, "_ZNK11CBasePlayer19IsLookingAtPositionEPK6Vectorf", CBasePlayer::IsLookingAtPosition),
	HOOK_SYMBOLDEF(0x01DA6310, "_ZN11CBasePlayer5ResetEv", CBasePlayer::Reset),
	HOOK_SYMBOLDEF(0x01DA5F10, "_ZN11CBasePlayer23SetScoreboardAttributesEPS_", CBasePlayer::SetScoreboardAttributes),
	//HOOK_SYMBOLDEF(0x01DA6070, "_ZN11CBasePlayer10RenewItemsEv", CBasePlayer::RenewItems),	// NOXREF
	HOOK_SYMBOLDEF(0x01D9D630, "_ZN11CBasePlayer19PackDeadPlayerItemsEv", CBasePlayer::PackDeadPlayerItems),
	HOOK_SYMBOLDEF(0x01D9DAD0, "_ZN11CBasePlayer16GiveDefaultItemsEv", CBasePlayer::GiveDefaultItems),
	HOOK_SYMBOLDEF(0x01D9DD60, "_ZN11CBasePlayer14RemoveAllItemsEi", CBasePlayer::RemoveAllItems),
	HOOK_SYMBOLDEF(0x01D9E020, "_ZN11CBasePlayer11SetBombIconEi", CBasePlayer::SetBombIcon),
	HOOK_SYMBOLDEF(0x01D9E190, "_ZN11CBasePlayer18SetProgressBarTimeEi", CBasePlayer::SetProgressBarTime),
	HOOK_SYMBOLDEF(0x01D9E320, "_ZN11CBasePlayer19SetProgressBarTime2Eif", CBasePlayer::SetProgressBarTime2),
	//HOOK_SYMBOLDEF(0x01D93690, "_Z14GetForceCamerav", GetForceCamera),		// NOXREF
	HOOK_SYMBOLDEF(0x01D93A00, "_ZL19UpdateClientEffectsP11CBasePlayeri", UpdateClientEffects),
	//HOOK_DEF(0x0, OLD_CheckBuyZone),		// NOXREF
	//HOOK_DEF(0x0, OLD_CheckBombTarget),	// NOXREF
	//HOOK_DEF(0x0, OLD_CheckRescueZone),	// NOXREF

#ifdef _WIN32

	//HOOK_DEF(0x0, BuyZoneIcon_Set),
	//HOOK_DEF(0x0, BuyZoneIcon_Clear),		// NOXREF
	//HOOK_DEF(0x0, BombTargetFlash_Set),
	//HOOK_DEF(0x0, BombTargetFlash_Clear),	// NOXREF
	//HOOK_DEF(0x0, RescueZoneIcon_Set),
	//HOOK_DEF(0x0, RescueZoneIcon_Clear),	// NOXREF
	HOOK_DEF(0x01DA8410, EscapeZoneIcon_Set),
	HOOK_DEF(0x01DA84C0, EscapeZoneIcon_Clear),
	HOOK_DEF(0x01DA8550, VIP_SafetyZoneIcon_Set),
	HOOK_DEF(0x01DA8630, VIP_SafetyZoneIcon_Clear),

#endif // _WIN32

	HOOK_SYMBOLDEF(0x01DA4420, "_ZN11CBasePlayer17SetNewPlayerModelEPKc", CBasePlayer::SetNewPlayerModel),
	HOOK_SYMBOLDEF(0x01DAB720, "_ZN11CBasePlayer12SwitchWeaponEP15CBasePlayerItem", CBasePlayer::SwitchWeapon),
	//HOOK_SYMBOLDEF(0x01DA43F0, "_ZN11CBasePlayer13CheckPowerupsEP9entvars_s", CBasePlayer::CheckPowerups),	// NOXREF
	HOOK_SYMBOLDEF(0x01DACDA0, "_ZN11CBasePlayer16CanAffordPrimaryEv", CBasePlayer::CanAffordPrimary),
	HOOK_SYMBOLDEF(0x01DACE10, "_ZN11CBasePlayer20CanAffordPrimaryAmmoEv", CBasePlayer::CanAffordPrimaryAmmo),
	HOOK_SYMBOLDEF(0x01DACE60, "_ZN11CBasePlayer22CanAffordSecondaryAmmoEv", CBasePlayer::CanAffordSecondaryAmmo),
	HOOK_SYMBOLDEF(0x01DACEB0, "_ZN11CBasePlayer14CanAffordArmorEv", CBasePlayer::CanAffordArmor),
	HOOK_SYMBOLDEF(0x01DACEF0, "_ZN11CBasePlayer18CanAffordDefuseKitEv", CBasePlayer::CanAffordDefuseKit),
	HOOK_SYMBOLDEF(0x01DACF00, "_ZN11CBasePlayer16CanAffordGrenadeEv", CBasePlayer::CanAffordGrenade),
	HOOK_SYMBOLDEF(0x01DACF20, "_ZN11CBasePlayer16NeedsPrimaryAmmoEv", CBasePlayer::NeedsPrimaryAmmo),
	HOOK_SYMBOLDEF(0x01DACF60, "_ZN11CBasePlayer18NeedsSecondaryAmmoEv", CBasePlayer::NeedsSecondaryAmmo),
	HOOK_SYMBOLDEF(0x01DACFA0, "_ZN11CBasePlayer10NeedsArmorEv", CBasePlayer::NeedsArmor),
	HOOK_SYMBOLDEF(0x01DACFD0, "_ZN11CBasePlayer14NeedsDefuseKitEv", CBasePlayer::NeedsDefuseKit),
	HOOK_SYMBOLDEF(0x01DAD000, "_ZN11CBasePlayer12NeedsGrenadeEv", CBasePlayer::NeedsGrenade),
	HOOK_SYMBOLDEF(0x01DA07B0, "_ZN11CBasePlayer10IsOnLadderEv", CBasePlayer::IsOnLadder),
	//HOOK_SYMBOLDEF(0x01DA6E80, "_ZN11CBasePlayer14FlashlightIsOnEv", CBasePlayer::FlashlightIsOn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA6E90, "_ZN11CBasePlayer16FlashlightTurnOnEv", CBasePlayer::FlashlightTurnOn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA6F40, "_ZN11CBasePlayer17FlashlightTurnOffEv", CBasePlayer::FlashlightTurnOff),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA4450, "_ZN11CBasePlayer17UpdatePlayerSoundEv", CBasePlayer::UpdatePlayerSound),
	//HOOK_SYMBOLDEF(0x01D9BCA0, "_ZN11CBasePlayer10DeathSoundEv", CBasePlayer::DeathSound),	// NOXREF
	HOOK_SYMBOLDEF(0x01D9F430, "_ZN11CBasePlayer12SetAnimationE11PLAYER_ANIM", CBasePlayer::SetAnimation),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer17SetWeaponAnimTypeEPKc", CBasePlayer::SetWeaponAnimType),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA73C0, "_ZN11CBasePlayer20CheatImpulseCommandsEi", CBasePlayer::CheatImpulseCommands),
	//HOOK_SYMBOLDEF(0x01DA2640, "_ZN11CBasePlayer13StartDeathCamEv", CBasePlayer::StartDeathCam),		// NOXREF
	HOOK_SYMBOLDEF(0x01DA26D0, "_ZN11CBasePlayer13StartObserverE6VectorS0_", CBasePlayer::StartObserver),
	HOOK_SYMBOLDEF(0x01DA7FF0, "_ZN11CBasePlayer13HandleSignalsEv", CBasePlayer::HandleSignals),
	HOOK_SYMBOLDEF(0x01DAA850, "_ZN11CBasePlayer14DropPlayerItemEPKc", CBasePlayer::DropPlayerItem),
	//HOOK_SYMBOLDEF(0x01DAAF30, "_ZN11CBasePlayer13HasPlayerItemEP15CBasePlayerItem", CBasePlayer::HasPlayerItem),
	//HOOK_SYMBOLDEF(0x01DAAFC0, "_ZN11CBasePlayer18HasNamedPlayerItemEPKc", CBasePlayer::HasNamedPlayerItem),
	//HOOK_SYMBOLDEF(0x01DA6920, "_ZN11CBasePlayer10HasWeaponsEv", CBasePlayer::HasWeapons),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA6940, "_ZN11CBasePlayer14SelectPrevItemEi", CBasePlayer::SelectPrevItem), // NOXREF
	//HOOK_SYMBOLDEF(0x01DA6470, "_ZN11CBasePlayer14SelectNextItemEi", CBasePlayer::SelectNextItem), // NOXREF
	HOOK_SYMBOLDEF(0x01DA65E0, "_ZN11CBasePlayer10SelectItemEPKc", CBasePlayer::SelectItem),
	HOOK_SYMBOLDEF(0x01DA67A0, "_ZN11CBasePlayer14SelectLastItemEv", CBasePlayer::SelectLastItem),
	//HOOK_SYMBOLDEF(0x01DA8BB0, "_ZN11CBasePlayer12ItemPreFrameEv", CBasePlayer::ItemPreFrame),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA8BE0, "_ZN11CBasePlayer13ItemPostFrameEv", CBasePlayer::ItemPostFrame),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA6CC0, "_ZN11CBasePlayer13GiveNamedItemEPKc", CBasePlayer::GiveNamedItem),
	HOOK_SYMBOLDEF(0x01DA9C80, "_ZN11CBasePlayer13EnableControlEi", CBasePlayer::EnableControl),
	HOOK_SYMBOLDEF(0x01DA9D50, "_ZN11CBasePlayer11HintMessageEPKcii", CBasePlayer::HintMessage),
	HOOK_SYMBOLDEF(0x01DA8CC0, "_ZN11CBasePlayer14SendAmmoUpdateEv", CBasePlayer::SendAmmoUpdate),
	//HOOK_SYMBOLDEF(0x01D9E4F0, "_ZN11CBasePlayer7SendFOVEi", CBasePlayer::SendFOV),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA0390, "_ZN11CBasePlayer9WaterMoveEv", CBasePlayer::WaterMove),
	HOOK_SYMBOLDEF(0x01DA2140, "_ZN11CBasePlayer16PlayerDeathThinkEv", CBasePlayer::PlayerDeathThink),
	HOOK_SYMBOLDEF(0x01DA29A0, "_ZN11CBasePlayer9PlayerUseEv", CBasePlayer::PlayerUse),
	HOOK_SYMBOLDEF(0x01DA3290, "_ZN11CBasePlayer11HostageUsedEv", CBasePlayer::HostageUsed),
	HOOK_SYMBOLDEF(0x01DA1680, "_ZN11CBasePlayer12JoiningThinkEv", CBasePlayer::JoiningThink),
	//HOOK_SYMBOLDEF(0x01DA1480, "_ZN11CBasePlayer15RemoveLevelTextEv", CBasePlayer::RemoveLevelText),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA14D0, "_ZN11CBasePlayer9MenuPrintEPS_PKc", CBasePlayer::MenuPrint),	// hook with attribute __stdcall
	//HOOK_SYMBOLDEF(0x01DA11F0, "_ZN11CBasePlayer9ResetMenuEv", CBasePlayer::ResetMenu),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA1240, "_ZN11CBasePlayer14SyncRoundTimerEv", CBasePlayer::SyncRoundTimer),
	HOOK_SYMBOLDEF(0x01DA4220, "_ZN11CBasePlayer15CheckSuitUpdateEv", CBasePlayer::CheckSuitUpdate),
	HOOK_SYMBOLDEF(0x01DA43E0, "_ZN11CBasePlayer13SetSuitUpdateEPcii", CBasePlayer::SetSuitUpdate),
	//HOOK_SYMBOLDEF(0x01DA4170, "_ZN11CBasePlayer19UpdateGeigerCounterEv", CBasePlayer::UpdateGeigerCounter),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA3FE0, "_ZN11CBasePlayer20CheckTimeBasedDamageEv", CBasePlayer::CheckTimeBasedDamage),
	//HOOK_SYMBOLDEF(0x01DA9C10, "_ZN11CBasePlayer20BarnacleVictimBittenEP9entvars_s", CBasePlayer::BarnacleVictimBitten),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA9C40, "_ZN11CBasePlayer22BarnacleVictimReleasedEv", CBasePlayer::BarnacleVictimReleased),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA8C80, "_ZN11CBasePlayer12GetAmmoIndexEPKc", CBasePlayer::GetAmmoIndex),
	HOOK_SYMBOLDEF(0x01DA8C60, "_ZN11CBasePlayer13AmmoInventoryEi", CBasePlayer::AmmoInventory),
	//HOOK_SYMBOLDEF(0x01DAA150, "_ZN11CBasePlayer12ResetAutoaimEv", CBasePlayer::ResetAutoaim),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAA120, "_ZN11CBasePlayer17AutoaimDeflectionER6Vectorff", CBasePlayer::AutoaimDeflection),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA6FD0, "_ZN11CBasePlayer20ForceClientDllUpdateEv", CBasePlayer::ForceClientDllUpdate),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer12DeathMessageEP9entvars_s", CBasePlayer::DeathMessage),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAA1E0, "_ZN11CBasePlayer20SetCustomDecalFramesEi", CBasePlayer::SetCustomDecalFrames),
	//HOOK_SYMBOLDEF(0x01DAA210, "_ZN11CBasePlayer20GetCustomDecalFramesEv", CBasePlayer::GetCustomDecalFrames),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAA260, "_ZN11CBasePlayer13InitStatusBarEv", CBasePlayer::InitStatusBar),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAA270, "_ZN11CBasePlayer15UpdateStatusBarEv", CBasePlayer::UpdateStatusBar),
	HOOK_SYMBOLDEF(0x01DAC0F0, "_ZN11CBasePlayer18StudioEstimateGaitEv", CBasePlayer::StudioEstimateGait),
	//HOOK_SYMBOLDEF(0x01DAC400, "_ZN11CBasePlayer17StudioPlayerBlendEPiPf", CBasePlayer::StudioPlayerBlend),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAC490, "_ZN11CBasePlayer19CalculatePitchBlendEv", CBasePlayer::CalculatePitchBlend),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAC510, "_ZN11CBasePlayer17CalculateYawBlendEv", CBasePlayer::CalculateYawBlend),
	HOOK_SYMBOLDEF(0x01DAC640, "_ZN11CBasePlayer17StudioProcessGaitEv", CBasePlayer::StudioProcessGait),
	//HOOK_SYMBOLDEF(0x01DA8D40, "_ZN11CBasePlayer14SendHostagePosEv", CBasePlayer::SendHostagePos),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA8DE0, "_ZN11CBasePlayer16SendHostageIconsEv", CBasePlayer::SendHostageIcons),
	//HOOK_SYMBOLDEF(0x01DAC7C0, "_ZN11CBasePlayer12ResetStaminaEv", CBasePlayer::ResetStamina),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DACA10, "_ZN11CBasePlayer9IsArmoredEi", CBasePlayer::IsArmored),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DACA60, "_ZN11CBasePlayer19ShouldDoLargeFlinchEii", CBasePlayer::ShouldDoLargeFlinch),	// NOXREF
	HOOK_SYMBOLDEF(0x01DACAD0, "_ZN11CBasePlayer20SetPrefsFromUserinfoEPc", CBasePlayer::SetPrefsFromUserinfo),
	HOOK_SYMBOLDEF(0x01DA8EE0, "_ZN11CBasePlayer15SendWeatherInfoEv", CBasePlayer::SendWeatherInfo),
	HOOK_SYMBOLDEF(0x01DAB6F0, "_ZN11CBasePlayer21UpdateShieldCrosshairEb", CBasePlayer::UpdateShieldCrosshair),
	HOOK_SYMBOLDEF(0x01DA0DA0, "_ZN11CBasePlayer9HasShieldEv", CBasePlayer::HasShield),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer19IsProtectedByShieldEv", CBasePlayer::IsProtectedByShield),
	//HOOK_SYMBOLDEF(0x01DA0B20, "_ZN11CBasePlayer12RemoveShieldEv", CBasePlayer::RemoveShield),	// NOXREF
	HOOK_SYMBOLDEF(0x01DA0B60, "_ZN11CBasePlayer10DropShieldEb", CBasePlayer::DropShield),
	HOOK_SYMBOLDEF(0x01DA0A90, "_ZN11CBasePlayer10GiveShieldEb", CBasePlayer::GiveShield),
	//HOOK_SYMBOLDEF(0x01D9BDB0, "_ZN11CBasePlayer15IsHittingShieldERK6VectorP11TraceResult", CBasePlayer::IsHittingShield),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer11IsReloadingEv", CBasePlayer::IsReloading),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CBasePlayer7IsBlindEv", CBasePlayer::IsBlind),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CBasePlayer19IsAutoFollowAllowedEv", CBasePlayer::IsAutoFollowAllowed),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer17InhibitAutoFollowEf", CBasePlayer::InhibitAutoFollow),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer15AllowAutoFollowEv", CBasePlayer::AllowAutoFollow),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAD180, "_ZN11CBasePlayer16ClearAutoBuyDataEv", CBasePlayer::ClearAutoBuyData),
	HOOK_SYMBOLDEF(0x01DAD190, "_ZN11CBasePlayer14AddAutoBuyDataEPKc", CBasePlayer::AddAutoBuyData),
	HOOK_SYMBOLDEF(0x01DAD280, "_ZN11CBasePlayer7AutoBuyEv", CBasePlayer::AutoBuy),
	HOOK_SYMBOLDEF(0x01DAD0D0, "_ZN11CBasePlayer13ClientCommandEPKcS1_S1_S1_", CBasePlayer::ClientCommand),
	HOOK_SYMBOLDEF(0x01DADD00, "_ZN11CBasePlayer23PrioritizeAutoBuyStringEPcPKc", CBasePlayer::PrioritizeAutoBuyString),
	HOOK_SYMBOLDEF(0x01DAD590, "_ZN11CBasePlayer27PickPrimaryCareerTaskWeaponEv", CBasePlayer::PickPrimaryCareerTaskWeapon),
	HOOK_SYMBOLDEF(0x01DAD930, "_ZN11CBasePlayer29PickSecondaryCareerTaskWeaponEv", CBasePlayer::PickSecondaryCareerTaskWeapon),
	//HOOK_SYMBOLDEF(0x01DADC60, "_ZN11CBasePlayer25PickFlashKillWeaponStringEv", CBasePlayer::PickFlashKillWeaponString),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DADCC0, "_ZN11CBasePlayer27PickGrenadeKillWeaponStringEv", CBasePlayer::PickGrenadeKillWeaponString),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DADF70, "_ZN11CBasePlayer27ShouldExecuteAutoBuyCommandEPK17AutoBuyInfoStructbb", CBasePlayer::ShouldExecuteAutoBuyCommand),		// NOXREF
	HOOK_SYMBOLDEF(0x01DADFF0, "_ZN11CBasePlayer28PostAutoBuyCommandProcessingEPK17AutoBuyInfoStructRbS3_", CBasePlayer::PostAutoBuyCommandProcessing),
	HOOK_SYMBOLDEF(0x01DADE20, "_ZN11CBasePlayer18ParseAutoBuyStringEPKcRbS2_", CBasePlayer::ParseAutoBuyString),
	//HOOK_SYMBOLDEF(0x01DADFB0, "_ZN11CBasePlayer21GetAutoBuyCommandInfoEPKc", CBasePlayer::GetAutoBuyCommandInfo),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAD1F0, "_ZN11CBasePlayer13InitRebuyDataEPKc", CBasePlayer::InitRebuyData),
	HOOK_SYMBOLDEF(0x01DAE0A0, "_ZN11CBasePlayer16BuildRebuyStructEv", CBasePlayer::BuildRebuyStruct),
	HOOK_SYMBOLDEF(0x01DAE260, "_ZN11CBasePlayer5RebuyEv", CBasePlayer::Rebuy),
	//HOOK_SYMBOLDEF(0x01DAE580, "_ZN11CBasePlayer18RebuyPrimaryWeaponEv", CBasePlayer::RebuyPrimaryWeapon),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAE5E0, "_ZN11CBasePlayer16RebuyPrimaryAmmoEv", CBasePlayer::RebuyPrimaryAmmo),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAE650, "_ZN11CBasePlayer20RebuySecondaryWeaponEv", CBasePlayer::RebuySecondaryWeapon),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAE6B0, "_ZN11CBasePlayer18RebuySecondaryAmmoEv", CBasePlayer::RebuySecondaryAmmo),
	//HOOK_SYMBOLDEF(0x01DAE720, "_ZN11CBasePlayer14RebuyHEGrenadeEv", CBasePlayer::RebuyHEGrenade),			// NOXREF
	//HOOK_SYMBOLDEF(0x01DAE7C0, "_ZN11CBasePlayer14RebuyFlashbangEv", CBasePlayer::RebuyFlashbang),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DAE860, "_ZN11CBasePlayer17RebuySmokeGrenadeEv", CBasePlayer::RebuySmokeGrenade),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAE900, "_ZN11CBasePlayer12RebuyDefuserEv", CBasePlayer::RebuyDefuser),
	HOOK_SYMBOLDEF(0x01DAE960, "_ZN11CBasePlayer16RebuyNightVisionEv", CBasePlayer::RebuyNightVision),
	HOOK_SYMBOLDEF(0x01DAE9C0, "_ZN11CBasePlayer10RebuyArmorEv", CBasePlayer::RebuyArmor),
	HOOK_SYMBOLDEF(0x01DAEAB0, "_ZN11CBasePlayer14UpdateLocationEb", CBasePlayer::UpdateLocation),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer23SetObserverAutoDirectorEb", CBasePlayer::SetObserverAutoDirector),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAEA40, "_ZN11CBasePlayer17IsObservingPlayerEPS_", CBasePlayer::IsObservingPlayer),
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CBasePlayer22CanSwitchObserverModesEv", CBasePlayer::CanSwitchObserverModes),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBasePlayer7IntenseEv", CBasePlayer::Intense),	// NOXREF
	HOOK_SYMBOLDEF(0x01D9AB20, "_Z16LinkUserMessagesv", LinkUserMessages),
	HOOK_SYMBOLDEF(0x01D9B0F0, "_Z18WriteSigonMessagesv", WriteSigonMessages),
	//HOOK_SYMBOLDEF(0x01D9B280, "_Z14SendItemStatusP11CBasePlayer", SendItemStatus),
	HOOK_SYMBOLDEF(0x01D9D8A0, "_ZL14GetCSModelNamei", GetCSModelName),
	HOOK_SYMBOLDEF(0x01D9B2D0, "_ZN11CBasePlayer14SetPlayerModelEi", CBasePlayer::SetPlayerModel),
	//HOOK_SYMBOLDEF(0x01D9BB40, "_Z20VecVelocityForDamagef", VecVelocityForDamage),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D9BC40, "_Z10TrainSpeedii", TrainSpeed),	// NOXREF
	HOOK_SYMBOLDEF(0x01D9C2B0, "_Z13GetWeaponNameP9entvars_sS0_", GetWeaponName),
	HOOK_SYMBOLDEF(0x01D9C3C0, "_Z9LogAttackP11CBasePlayerS0_iiiiiPKc", LogAttack),
	HOOK_SYMBOLDEF(0x01D9D770, "_ZL14packPlayerItemP11CBasePlayerP15CBasePlayerItemb", packPlayerItem),
	HOOK_SYMBOLDEF(0x01DA3110, "_ZL13CanSeeUseableP11CBasePlayerP11CBaseEntity_isra_13", CanSeeUseable),
	//HOOK_SYMBOLDEF(0x01DA34E0, "_Z20FixPlayerCrouchStuckP7edict_s", FixPlayerCrouchStuck),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA4A90, "_Z17IsSpawnPointValidP11CBaseEntityS0_", IsSpawnPointValid),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA4B20, "_Z16InitZombieSpawnsv", InitZombieSpawns),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA4BC0, "_Z15FindZombieSpawnP11CBaseEntityb", FindZombieSpawn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA4BD0, "_Z19EntSelectSpawnPointP11CBaseEntity", EntSelectSpawnPoint),

#ifdef _WIN32
	//HOOK_DEF(0x01DA5180, SetScoreAttrib),
#endif // _WIN32

	//HOOK_SYMBOLDEF(0x01DA6D60, "_Z17FindEntityForwardP11CBaseEntity", FindEntityForward),	// NOXREF
	HOOK_SYMBOLDEF(0x01DAC7E0, "_Z14GetPlayerPitchPK7edict_s", GetPlayerPitch),
	HOOK_SYMBOLDEF(0x01DAC830, "_Z12GetPlayerYawPK7edict_s", GetPlayerYaw),
	HOOK_SYMBOLDEF(0x01DAC880, "_Z21GetPlayerGaitsequencePK7edict_s", GetPlayerGaitsequence),
	//HOOK_SYMBOLDEF(0x01DAD120, "_Z26GetBuyStringForWeaponClassi", GetBuyStringForWeaponClass),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAD470, "_Z20IsPrimaryWeaponClassi", IsPrimaryWeaponClass),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAD490, "_Z17IsPrimaryWeaponIdi", IsPrimaryWeaponId),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAD4C0, "_Z22IsSecondaryWeaponClassi", IsSecondaryWeaponClass),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DAD4D0, "_Z19IsSecondaryWeaponIdi", IsSecondaryWeaponId),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAD500, "_Z22GetWeaponAliasFromNamePKc", GetWeaponAliasFromName),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DAD520, "_Z22CurrentWeaponSatisfiesP17CBasePlayerWeaponii", CurrentWeaponSatisfies),	// NOXREF
//CWShield
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA08D0, "_ZN8CWShield5SpawnEv", CWShield::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA0920, "_ZN8CWShield5TouchEP11CBaseEntity", CWShield::Touch),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN8CWShield23SetCantBePickedUpByUserEP11CBaseEntityf", CWShield::SetCantBePickedUpByUser) // NOXREF

//CSprayCan
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DA6A30, "_ZN9CSprayCan5ThinkEv", CSprayCan::Think),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DA73B0, "_ZN9CSprayCan10ObjectCapsEv", CSprayCan::ObjectCaps),			// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DA6970, "_ZN9CSprayCan5SpawnEP9entvars_s", CSprayCan::Spawn),	// NOXREF
//CBloodSplat
	//HOOK_SYMBOLDEF(0x01DA6B70, "_ZN11CBloodSplat5SpawnEP9entvars_s", CBloodSplat::Spawn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DA6C00, "_ZN11CBloodSplat5SprayEv", CBloodSplat::Spray),	// NOXREF
//CDeadHEV
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABAF0, "_ZN8CDeadHEV5SpawnEv", CDeadHEV::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABAE0, "_ZN8CDeadHEV8ClassifyEv", CDeadHEV::Classify),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABA40, "_ZN8CDeadHEV8KeyValueEP14KeyValueData_s", CDeadHEV::KeyValue),
//CStripWeapons
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABC10, "_ZN13CStripWeapons3UseEP11CBaseEntityS1_8USE_TYPEf", CStripWeapons::Use),
//CRevertSaved
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABD20, "_ZN12CRevertSaved8KeyValueEP14KeyValueData_s", CRevertSaved::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABCC0, "_ZN12CRevertSaved4SaveER5CSave", CRevertSaved::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABCF0, "_ZN12CRevertSaved7RestoreER8CRestore", CRevertSaved::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABE10, "_ZN12CRevertSaved3UseEP11CBaseEntityS1_8USE_TYPEf", CRevertSaved::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DABE70, "_ZN12CRevertSaved12MessageThinkEv", CRevertSaved::MessageThink),
	HOOK_SYMBOLDEF(0x01DABEF0, "_ZN12CRevertSaved9LoadThinkEv", CRevertSaved::LoadThink),
//CInfoIntermission
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABF20, "_ZN17CInfoIntermission5SpawnEv", CInfoIntermission::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DABF90, "_ZN17CInfoIntermission5ThinkEv", CInfoIntermission::Think),
	//linked objects
	HOOK_DEF(0x01D9B1F0, player),
	HOOK_DEF(0x01DAC0A0, info_intermission),
	HOOK_DEF(0x01DABC70, player_loadsaved),
	HOOK_DEF(0x01DABBC0, player_weaponstrip),
	HOOK_DEF(0x01DABA90, monster_hevsuit_dead),
	HOOK_DEF(0x01DA0880, weapon_shield),

#endif // Player_Region

#ifndef Effects_Region

//CSprite
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D792F0, "_ZN7CSprite5SpawnEv", CSprite::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79500, "_ZN7CSprite8PrecacheEv", CSprite::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79440, "_ZN7CSprite7RestartEv", CSprite::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79290, "_ZN7CSprite4SaveER5CSave", CSprite::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D792C0, "_ZN7CSprite7RestoreER8CRestore", CSprite::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D78660, "_ZN7CSprite10ObjectCapsEv", CSprite::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79AE0, "_ZN7CSprite3UseEP11CBaseEntityS1_8USE_TYPEf", CSprite::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D79740, "_ZN7CSprite12AnimateThinkEv", CSprite::AnimateThink),
	HOOK_SYMBOLDEF(0x01D79930, "_ZN7CSprite11ExpandThinkEv", CSprite::ExpandThink),
	//HOOK_SYMBOLDEF(0x01D799C0, "_ZN7CSprite12AnimateThinkEv", CSprite::Animate),		// NOXREF
	//HOOK_SYMBOLDEF(0x01D798E0, "_ZN7CSprite6ExpandEff", CSprite::Expand),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D79590, "_ZN7CSprite10SpriteInitEPKcRK6Vector", CSprite::SpriteInit),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite13SetAttachmentEP7edict_si", CSprite::SetAttachment),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D79A40, "_ZN7CSprite7TurnOffEv", CSprite::TurnOff),		// NOXREF
	HOOK_SYMBOLDEF(0x01D79A60, "_ZN7CSprite6TurnOnEv", CSprite::TurnOn),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite6FramesEv", CSprite::Frames),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite15SetTransparencyEiiiiii", CSprite::SetTransparency),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite10SetTextureEi", CSprite::SetTexture),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite8SetScaleEf", CSprite::SetScale),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite8SetColorEiii", CSprite::SetColor),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite13SetBrightnessEi", CSprite::SetBrightness),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN7CSprite13AnimateAndDieEf", CSprite::AnimateAndDie),		// NOXREF
	HOOK_SYMBOLDEF(0x01D79800, "_ZN7CSprite16AnimateUntilDeadEv", CSprite::AnimateUntilDead),
	HOOK_SYMBOLDEF(0x01D795D0, "_ZN7CSprite12SpriteCreateEPKcRK6Vectori", CSprite::SpriteCreate),
//CBeam
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75E00, "_ZN5CBeam5SpawnEv", CBeam::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75E20, "_ZN5CBeam8PrecacheEv", CBeam::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D788B0, "_ZN5CBeam10ObjectCapsEv", CBeam::ObjectCaps),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D78D20, "_ZN5CBeam6CenterEv", CBeam::Center),			// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D76660, "_ZN5CBeam12TriggerTouchEP11CBaseEntity", CBeam::TriggerTouch),
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam7SetTypeEi", CBeam::SetType),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8SetFlagsEi", CBeam::SetFlags),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam11SetStartPosERK6Vector", CBeam::SetStartPos),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam9SetEndPosERK6Vector", CBeam::SetEndPos),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D75EC0, "_ZN5CBeam14SetStartEntityEi", CBeam::SetStartEntity),		// NOXREF
	//HOOK_SYMBOLDEF(0x01D75F10, "_ZN5CBeam12SetEndEntityEi", CBeam::SetEndEntity),			// NOXREF
	HOOK_SYMBOLDEF(0x01D7A860, "_ZN5CBeam18SetStartAttachmentEi", CBeam::SetStartAttachment),
	HOOK_SYMBOLDEF(0x01D7A890, "_ZN5CBeam16SetEndAttachmentEi", CBeam::SetEndAttachment),
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam10SetTextureEi", CBeam::SetTexture),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8SetWidthEi", CBeam::SetWidth),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8SetNoiseEi", CBeam::SetNoise),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8SetColorEiii", CBeam::SetColor),						// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam13SetBrightnessEi", CBeam::SetBrightness),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8SetFrameEf", CBeam::SetFrame),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam13SetScrollRateEi", CBeam::SetScrollRate),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam7GetTypeEv", CBeam::GetType),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8GetFlagsEv", CBeam::GetFlags),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam14GetStartEntityEv", CBeam::GetStartEntity),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam12GetEndEntityEv", CBeam::GetEndEntity),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D75F60, "_ZN5CBeam11GetStartPosEv", CBeam::GetStartPos),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D75FA0, "_ZN5CBeam9GetEndPosEv", CBeam::GetEndPos),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam10GetTextureEv", CBeam::GetTexture),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8GetWidthEv", CBeam::GetWidth),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8GetNoiseEv", CBeam::GetNoise),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam13GetBrightnessEv", CBeam::GetBrightness),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam8GetFrameEv", CBeam::GetFrame),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam13GetScrollRateEv", CBeam::GetScrollRate),				// NOXREF
	HOOK_SYMBOLDEF(0x01D76480, "_ZN5CBeam10RelinkBeamEv", CBeam::RelinkBeam),
	//HOOK_SYMBOLDEF(0x01D76700, "_ZN5CBeam8DoSparksERK6VectorS2_", CBeam::DoSparks),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D766B0, "_ZN5CBeam16RandomTargetnameEPKc", CBeam::RandomTargetname),	// NOXREF
	HOOK_SYMBOLDEF(0x01D775B0, "_ZN5CBeam10BeamDamageEP11TraceResult", CBeam::BeamDamage),
	HOOK_SYMBOLDEF(0x01D76140, "_ZN5CBeam8BeamInitEPKci", CBeam::BeamInit),
	//HOOK_SYMBOLDEF(0x01D76200, "_ZN5CBeam10PointsInitERK6VectorS2_", CBeam::PointsInit),		// NOXREF
	//HOOK_SYMBOLDEF(0x01D76300, "_ZN5CBeam12PointEntInitERK6Vectori", CBeam::PointEntInit),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D763B0, "_ZN5CBeam8EntsInitEii", CBeam::EntsInit),						// NOXREF
	//HOOK_SYMBOLDEF(0x01D76280, "_ZN5CBeam8HoseInitERK6VectorS2_", CBeam::HoseInit),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D75FF0, "_ZN5CBeam10BeamCreateEPKci", CBeam::BeamCreate),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam11LiveForTimeEf", CBeam::LiveForTime),						// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CBeam17BeamDamageInstantEP11TraceResultf", CBeam::BeamDamageInstant),		// NOXREF
//CLaser
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D782A0, "_ZN6CLaser5SpawnEv", CLaser::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78680, "_ZN6CLaser8PrecacheEv", CLaser::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D786D0, "_ZN6CLaser8KeyValueEP14KeyValueData_s", CLaser::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78240, "_ZN6CLaser4SaveER5CSave", CLaser::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78270, "_ZN6CLaser7RestoreER8CRestore", CLaser::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D789E0, "_ZN6CLaser3UseEP11CBaseEntityS1_8USE_TYPEf", CLaser::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D78930, "_ZN6CLaser6TurnOnEv", CLaser::TurnOn),
	HOOK_SYMBOLDEF(0x01D788F0, "_ZN6CLaser7TurnOffEv", CLaser::TurnOff),
	//HOOK_SYMBOLDEF(0x01D788D0, "_ZN6CLaser4IsOnEv", CLaser::IsOn),	// NOXREF
	HOOK_SYMBOLDEF(0x01D78B00, "_ZN6CLaser11FireAtPointER11TraceResult", CLaser::FireAtPoint),
	HOOK_SYMBOLDEF(0x01D78BB0, "_ZN6CLaser11StrikeThinkEv", CLaser::StrikeThink),
//CBubbling
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75A90, "_ZN9CBubbling5SpawnEv", CBubbling::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75BA0, "_ZN9CBubbling8PrecacheEv", CBubbling::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75C30, "_ZN9CBubbling8KeyValueEP14KeyValueData_s", CBubbling::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75A30, "_ZN9CBubbling4SaveER5CSave", CBubbling::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75A60, "_ZN9CBubbling7RestoreER8CRestore", CBubbling::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D75A20, "_ZN9CBubbling10ObjectCapsEv", CBubbling::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75BC0, "_ZN9CBubbling3UseEP11CBaseEntityS1_8USE_TYPEf", CBubbling::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D75CF0, "_ZN9CBubbling9FizzThinkEv", CBubbling::FizzThink),
//CLightning
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D76840, "_ZN10CLightning5SpawnEv", CLightning::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D76970, "_ZN10CLightning8PrecacheEv", CLightning::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D76A60, "_ZN10CLightning8KeyValueEP14KeyValueData_s", CLightning::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D767E0, "_ZN10CLightning4SaveER5CSave", CLightning::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D76810, "_ZN10CLightning7RestoreER8CRestore", CLightning::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D76A30, "_ZN10CLightning8ActivateEv", CLightning::Activate),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D76EE0, "_ZN10CLightning11StrikeThinkEv", CLightning::StrikeThink),
	HOOK_SYMBOLDEF(0x01D776A0, "_ZN10CLightning11DamageThinkEv", CLightning::DamageThink),
	HOOK_SYMBOLDEF(0x01D778C0, "_ZN10CLightning10RandomAreaEv", CLightning::RandomArea),
	HOOK_SYMBOLDEF(0x01D77CC0, "_ZN10CLightning11RandomPointER6Vector", CLightning::RandomPoint),
	HOOK_SYMBOLDEF(0x01D77760, "_ZN10CLightning3ZapERK6VectorS2_", CLightning::Zap),
	HOOK_SYMBOLDEF(0x01D76E00, "_ZN10CLightning9StrikeUseEP11CBaseEntityS1_8USE_TYPEf", CLightning::StrikeUse),
	HOOK_SYMBOLDEF(0x01D76CB0, "_ZN10CLightning9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", CLightning::ToggleUse),
	//HOOK_SYMBOLDEF(0x0, "_ZN10CLightning10ServerSideEv", CLightning::ServerSide),	// NOXREF
	HOOK_SYMBOLDEF(0x01D77E60, "_ZN10CLightning14BeamUpdateVarsEv", CLightning::BeamUpdateVars),
	//HOOK_SYMBOLDEF(0x01D76E70, "_Z13IsPointEntityP11CBaseEntity", IsPointEntity),	// NOXREF
//CGlow
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78E90, "_ZN5CGlow5SpawnEv", CGlow::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78E30, "_ZN5CGlow4SaveER5CSave", CGlow::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78E60, "_ZN5CGlow7RestoreER8CRestore", CGlow::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D78FA0, "_ZN5CGlow5ThinkEv", CGlow::Think),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D79010, "_ZN5CGlow7AnimateEf", CGlow::Animate),	// NOXREF
//CBombGlow
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D790A0, "_ZN9CBombGlow5SpawnEv", CBombGlow::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79150, "_ZN9CBombGlow5ThinkEv", CBombGlow::Think),
//CGibShooter
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79DA0, "_ZN11CGibShooter5SpawnEv", CGibShooter::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79C50, "_ZN11CGibShooter8PrecacheEv", CGibShooter::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79C90, "_ZN11CGibShooter8KeyValueEP14KeyValueData_s", CGibShooter::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79BA0, "_ZN11CGibShooter4SaveER5CSave", CGibShooter::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79BD0, "_ZN11CGibShooter7RestoreER8CRestore", CGibShooter::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79D80, "_ZN11CGibShooter3UseEP11CBaseEntityS1_8USE_TYPEf", CGibShooter::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D79E20, "_ZN11CGibShooter9CreateGibEv", CGibShooter::CreateGib),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D79EF0, "_ZN11CGibShooter10ShootThinkEv", CGibShooter::ShootThink),
//CEnvShooter
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A370, "_ZN11CEnvShooter8PrecacheEv", CEnvShooter::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A270, "_ZN11CEnvShooter8KeyValueEP14KeyValueData_s", CEnvShooter::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A3B0, "_ZN11CEnvShooter9CreateGibEv", CEnvShooter::CreateGib),
//CTestEffect
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A530, "_ZN11CTestEffect5SpawnEv", CTestEffect::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A540, "_ZN11CTestEffect8PrecacheEv", CTestEffect::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A8C0, "_ZN11CTestEffect3UseEP11CBaseEntityS1_8USE_TYPEf", CTestEffect::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D7A550, "_ZN11CTestEffect9TestThinkEv", CTestEffect::TestThink),
//CBlood
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A940, "_ZN6CBlood5SpawnEv", CBlood::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7A980, "_ZN6CBlood8KeyValueEP14KeyValueData_s", CBlood::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7AB70, "_ZN6CBlood3UseEP11CBaseEntityS1_8USE_TYPEf", CBlood::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN6CBlood5ColorEv", CBlood::Color),						// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CBlood11BloodAmountEv", CBlood::BloodAmount),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CBlood8SetColorEi", CBlood::SetColor),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CBlood14SetBloodAmountEf", CBlood::SetBloodAmount),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D7AA30, "_ZN6CBlood9DirectionEv", CBlood::Direction),		// NOXREF
	HOOK_SYMBOLDEF(0x01D7AA70, "_ZN6CBlood13BloodPositionEP11CBaseEntity", CBlood::BloodPosition),
//CShake
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7ADB0, "_ZN6CShake5SpawnEv", CShake::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7ADF0, "_ZN6CShake8KeyValueEP14KeyValueData_s", CShake::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7AEE0, "_ZN6CShake3UseEP11CBaseEntityS1_8USE_TYPEf", CShake::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake9AmplitudeEv", CShake::Amplitude),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake9FrequencyEv", CShake::Frequency),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake8DurationEv", CShake::Duration),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake6RadiusEv", CShake::Radius),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake12SetAmplitudeEf", CShake::SetAmplitude),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake12SetFrequencyEf", CShake::SetFrequency),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake11SetDurationEf", CShake::SetDuration),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CShake9SetRadiusEf", CShake::SetRadius),				// NOXREF
//CFade
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7AF70, "_ZN5CFade5SpawnEv", CFade::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7AFA0, "_ZN5CFade8KeyValueEP14KeyValueData_s", CFade::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B030, "_ZN5CFade3UseEP11CBaseEntityS1_8USE_TYPEf", CFade::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN5CFade8DurationEv", CFade::Duration),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CFade8HoldTimeEv", CFade::HoldTime),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CFade11SetDurationEf", CFade::SetDuration),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CFade11SetHoldTimeEf", CFade::SetHoldTime),		// NOXREF
//CMessage
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B150, "_ZN8CMessage5SpawnEv", CMessage::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B1E0, "_ZN8CMessage8PrecacheEv", CMessage::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B210, "_ZN8CMessage8KeyValueEP14KeyValueData_s", CMessage::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B2E0, "_ZN8CMessage3UseEP11CBaseEntityS1_8USE_TYPEf", CMessage::Use),
//CEnvFunnel
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B4E0, "_ZN10CEnvFunnel5SpawnEv", CEnvFunnel::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B3E0, "_ZN10CEnvFunnel8PrecacheEv", CEnvFunnel::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B450, "_ZN10CEnvFunnel3UseEP11CBaseEntityS1_8USE_TYPEf", CEnvFunnel::Use),
//CEnvBeverage
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B630, "_ZN12CEnvBeverage5SpawnEv", CEnvBeverage::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B510, "_ZN12CEnvBeverage8PrecacheEv", CEnvBeverage::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B580, "_ZN12CEnvBeverage3UseEP11CBaseEntityS1_8USE_TYPEf", CEnvBeverage::Use),
//CItemSoda
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B6E0, "_ZN9CItemSoda5SpawnEv", CItemSoda::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B680, "_ZN9CItemSoda8PrecacheEv", CItemSoda::Precache),	// pure
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D7B790, "_ZN9CItemSoda8CanThinkEv", CItemSoda::CanThink),
	HOOK_SYMBOLDEF(0x01D7B820, "_ZN9CItemSoda8CanTouchEP11CBaseEntity", CItemSoda::CanTouch),
	//linked objects
	HOOK_DEF(0x01D75980, info_target),
	HOOK_DEF(0x01D759D0, env_bubbles),
	HOOK_DEF(0x01D75DB0, beam),
	HOOK_DEF(0x01D76740, env_lightning),
	HOOK_DEF(0x01D76790, env_beam),
	HOOK_DEF(0x01D781F0, env_laser),
	HOOK_DEF(0x01D78DE0, env_glow),
	HOOK_DEF(0x01D79050, env_bombglow),
	HOOK_DEF(0x01D79240, env_sprite),
	HOOK_DEF(0x01D79C00, gibshooter),
	HOOK_DEF(0x01D7A220, env_shooter),
	HOOK_DEF(0x01D7A4E0, test_effect),
	HOOK_DEF(0x01D7A8F0, env_blood),
	HOOK_DEF(0x01D7AD60, env_shake),
	HOOK_DEF(0x01D7AF20, env_fade),
	HOOK_DEF(0x01D7B100, env_message),
	HOOK_DEF(0x01D7B400, env_funnel),
	HOOK_DEF(0x01D7B530, env_beverage),
	HOOK_DEF(0x01D7B690, item_sodacan),

#endif // Effects_Region

#ifndef Plats_Region

//CBasePlatTrain
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95570, "_ZN14CBasePlatTrain8PrecacheEv", CBasePlatTrain::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D953E0, "_ZN14CBasePlatTrain8KeyValueEP14KeyValueData_s", CBasePlatTrain::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95380, "_ZN14CBasePlatTrain4SaveER5CSave", CBasePlatTrain::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D953B0, "_ZN14CBasePlatTrain7RestoreER8CRestore", CBasePlatTrain::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D95890, "_ZN14CBasePlatTrain10ObjectCapsEv", CBasePlatTrain::ObjectCaps),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D958A0, "_ZN14CBasePlatTrain12IsTogglePlatEv", CBasePlatTrain::IsTogglePlat),		// DEFAULT
//CFuncPlat
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95AF0, "_ZN9CFuncPlat5SpawnEv", CFuncPlat::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95A20, "_ZN9CFuncPlat8PrecacheEv", CFuncPlat::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95FC0, "_ZN9CFuncPlat7BlockedEP11CBaseEntity", CFuncPlat::Blocked),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95E90, "_ZN9CFuncPlat4GoUpEv", CFuncPlat::GoUp),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95D80, "_ZN9CFuncPlat6GoDownEv", CFuncPlat::GoDown),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95F10, "_ZN9CFuncPlat6HitTopEv", CFuncPlat::HitTop),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95E00, "_ZN9CFuncPlat9HitBottomEv", CFuncPlat::HitBottom),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D958B0, "_ZN9CFuncPlat5SetupEv", CFuncPlat::Setup),
	HOOK_SYMBOLDEF(0x01D95D10, "_ZN9CFuncPlat7PlatUseEP11CBaseEntityS1_8USE_TYPEf", CFuncPlat::PlatUse),
	HOOK_SYMBOLDEF(0x01D95810, "_ZN9CFuncPlat10CallGoDownEv", CFuncPlat::CallGoDown),
	HOOK_SYMBOLDEF(0x01D95820, "_ZN9CFuncPlat10CallHitTopEv", CFuncPlat::CallHitTop),
	HOOK_SYMBOLDEF(0x01D95830, "_ZN9CFuncPlat13CallHitBottomEv", CFuncPlat::CallHitBottom),
//CPlatTrigger
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D95AE0, "_ZN12CPlatTrigger10ObjectCapsEv", CPlatTrigger::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D95C90, "_ZN12CPlatTrigger5TouchEP11CBaseEntity", CPlatTrigger::Touch),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D95B50, "_ZN12CPlatTrigger18SpawnInsideTriggerEP9CFuncPlat", CPlatTrigger::SpawnInsideTrigger),
//CFuncPlatRot
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96270, "_ZN12CFuncPlatRot5SpawnEv", CFuncPlatRot::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D960C0, "_ZN12CFuncPlatRot4SaveER5CSave", CFuncPlatRot::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96110, "_ZN12CFuncPlatRot7RestoreER8CRestore", CFuncPlatRot::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D965C0, "_ZN12CFuncPlatRot4GoUpEv", CFuncPlatRot::GoUp),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D963D0, "_ZN12CFuncPlatRot6GoDownEv", CFuncPlatRot::GoDown),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D966F0, "_ZN12CFuncPlatRot6HitTopEv", CFuncPlatRot::HitTop),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96500, "_ZN12CFuncPlatRot9HitBottomEv", CFuncPlatRot::HitBottom),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D96160, "_ZN12CFuncPlatRot13SetupRotationEv", CFuncPlatRot::SetupRotation),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D96740, "_ZN12CFuncPlatRot7RotMoveER6Vectorf", CFuncPlatRot::RotMove),			// NOXREF
//CFuncTrain
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96FD0, "_ZN10CFuncTrain5SpawnEv", CFuncTrain::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D971A0, "_ZN10CFuncTrain8PrecacheEv", CFuncTrain::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D97100, "_ZN10CFuncTrain7RestartEv", CFuncTrain::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D968E0, "_ZN10CFuncTrain8KeyValueEP14KeyValueData_s", CFuncTrain::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96840, "_ZN10CFuncTrain4SaveER5CSave", CFuncTrain::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96890, "_ZN10CFuncTrain7RestoreER8CRestore", CFuncTrain::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96EB0, "_ZN10CFuncTrain8ActivateEv", CFuncTrain::Activate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D971B0, "_ZN10CFuncTrain13OverrideResetEv", CFuncTrain::OverrideReset),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96970, "_ZN10CFuncTrain3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncTrain::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D96930, "_ZN10CFuncTrain7BlockedEP11CBaseEntity", CFuncTrain::Blocked),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D96A20, "_ZN10CFuncTrain4WaitEv", CFuncTrain::Wait),
	HOOK_SYMBOLDEF(0x01D96BE0, "_ZN10CFuncTrain4NextEv", CFuncTrain::Next),
//CFuncTrackTrain
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D98A10, "_ZN15CFuncTrackTrain5SpawnEv", CFuncTrackTrain::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D98CF0, "_ZN15CFuncTrackTrain8PrecacheEv", CFuncTrackTrain::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D98C00, "_ZN15CFuncTrackTrain7RestartEv", CFuncTrackTrain::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D97310, "_ZN15CFuncTrackTrain8KeyValueEP14KeyValueData_s", CFuncTrackTrain::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D97260, "_ZN15CFuncTrackTrain4SaveER5CSave", CFuncTrackTrain::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D97290, "_ZN15CFuncTrackTrain7RestoreER8CRestore", CFuncTrackTrain::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D97630, "_ZN15CFuncTrackTrain10ObjectCapsEv", CFuncTrackTrain::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D98980, "_ZN15CFuncTrackTrain13OverrideResetEv", CFuncTrackTrain::OverrideReset),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D98490, "_ZN15CFuncTrackTrain10OnControlsEP9entvars_s", CFuncTrackTrain::OnControls),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D97640, "_ZN15CFuncTrackTrain3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncTrackTrain::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D974B0, "_ZN15CFuncTrackTrain7BlockedEP11CBaseEntity", CFuncTrackTrain::Blocked),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D97A40, "_ZN15CFuncTrackTrain4NextEv", CFuncTrackTrain::Next),	// TODO: FIX me, pev->angles.y is have difference of values 0.00001
	HOOK_SYMBOLDEF(0x01D985C0, "_ZN15CFuncTrackTrain4FindEv", CFuncTrackTrain::Find),
	HOOK_SYMBOLDEF(0x01D98770, "_ZN15CFuncTrackTrain11NearestPathEv", CFuncTrackTrain::NearestPath),
	HOOK_SYMBOLDEF(0x01D982B0, "_ZN15CFuncTrackTrain7DeadEndEv", CFuncTrackTrain::DeadEnd),
	//HOOK_SYMBOLDEF(0x01D97470, "_ZN15CFuncTrackTrain9NextThinkEfi", CFuncTrackTrain::NextThink),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN15CFuncTrackTrain8SetTrackEP10CPathTrack", CFuncTrackTrain::SetTrack),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D983E0, "_ZN15CFuncTrackTrain11SetControlsEP9entvars_s", CFuncTrackTrain::SetControls),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D97860, "_ZN15CFuncTrackTrain9StopSoundEv", CFuncTrackTrain::StopSound),					// NOXREF
	HOOK_SYMBOLDEF(0x01D978F0, "_ZN15CFuncTrackTrain11UpdateSoundEv", CFuncTrackTrain::UpdateSound),
	//HOOK_SYMBOLDEF(0x01D989C0, "_ZN15CFuncTrackTrain8InstanceEP7edict_s", CFuncTrackTrain::Instance),				// NOXREF
//CFuncTrainControls
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D98FF0, "_ZN18CFuncTrainControls5SpawnEv", CFuncTrainControls::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D98E60, "_ZN18CFuncTrainControls10ObjectCapsEv", CFuncTrainControls::ObjectCaps),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D98E70, "_ZN18CFuncTrainControls4FindEv", CFuncTrainControls::Find),
//CFuncTrackChange
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D991C0, "_ZN16CFuncTrackChange5SpawnEv", CFuncTrackChange::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99390, "_ZN16CFuncTrackChange8PrecacheEv", CFuncTrackChange::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99480, "_ZN16CFuncTrackChange8KeyValueEP14KeyValueData_s", CFuncTrackChange::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D990E0, "_ZN16CFuncTrackChange4SaveER5CSave", CFuncTrackChange::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99150, "_ZN16CFuncTrackChange7RestoreER8CRestore", CFuncTrackChange::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99540, "_ZN16CFuncTrackChange13OverrideResetEv", CFuncTrackChange::OverrideReset),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99470, "_ZN16CFuncTrackChange5TouchEP11CBaseEntity", CFuncTrackChange::Touch),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99EB0, "_ZN16CFuncTrackChange3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncTrackChange::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D990D0, "_ZN16CFuncTrackChange12IsTogglePlatEv", CFuncTrackChange::IsTogglePlat),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99C90, "_ZN16CFuncTrackChange4GoUpEv", CFuncTrackChange::GoUp),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99AE0, "_ZN16CFuncTrackChange6GoDownEv", CFuncTrackChange::GoDown),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99F60, "_ZN16CFuncTrackChange9HitBottomEv", CFuncTrackChange::HitBottom),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A090, "_ZN16CFuncTrackChange6HitTopEv", CFuncTrackChange::HitTop),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D99E40, "_ZN16CFuncTrackChange17UpdateAutoTargetsEi", CFuncTrackChange::UpdateAutoTargets),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D99560, "_ZN16CFuncTrackChange4FindEv", CFuncTrackChange::Find),
	HOOK_SYMBOLDEF(0x01D99840, "_ZN16CFuncTrackChange13EvaluateTrainEP10CPathTrack", CFuncTrackChange::EvaluateTrain),
	HOOK_SYMBOLDEF(0x01D99910, "_ZN16CFuncTrackChange11UpdateTrainER6Vector", CFuncTrackChange::UpdateTrain),
	//HOOK_SYMBOLDEF(0x0, "_ZN16CFuncTrackChange10DisableUseEv", CFuncTrackChange::DisableUse),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN16CFuncTrackChange9EnableUseEv", CFuncTrackChange::EnableUse),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN16CFuncTrackChange10UseEnabledEv", CFuncTrackChange::UseEnabled),		// NOXREF
//CFuncTrackAuto
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A270, "_ZN14CFuncTrackAuto3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncTrackAuto::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A1B0, "_ZN14CFuncTrackAuto17UpdateAutoTargetsEi", CFuncTrackAuto::UpdateAutoTargets),
//CGunTarget
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A480, "_ZN10CGunTarget5SpawnEv", CGunTarget::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A420, "_ZN10CGunTarget4SaveER5CSave", CGunTarget::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A450, "_ZN10CGunTarget7RestoreER8CRestore", CGunTarget::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A410, "_ZN10CGunTarget10ObjectCapsEv", CGunTarget::ObjectCaps),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A550, "_ZN10CGunTarget8ActivateEv", CGunTarget::Activate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A3E0, "_ZN10CGunTarget8ClassifyEv", CGunTarget::Classify),					// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A8D0, "_ZN10CGunTarget10TakeDamageEP9entvars_sS1_fi", CGunTarget::TakeDamage),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A3D0, "_ZN10CGunTarget10BloodColorEv", CGunTarget::BloodColor),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A990, "_ZN10CGunTarget3UseEP11CBaseEntityS1_8USE_TYPEf", CGunTarget::Use),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D9A3F0, "_ZN10CGunTarget10BodyTargetERK6Vector", CGunTarget::BodyTarget),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D9A610, "_ZN10CGunTarget4NextEv", CGunTarget::Next),
	HOOK_SYMBOLDEF(0x01D9A600, "_ZN10CGunTarget5StartEv", CGunTarget::Start),
	HOOK_SYMBOLDEF(0x01D9A6E0, "_ZN10CGunTarget4WaitEv", CGunTarget::Wait),
	//HOOK_SYMBOLDEF(0x01D9A890, "_ZN10CGunTarget4StopEv", CGunTarget::Stop),	// NOXREF
//CPlane
	//HOOK_SYMBOLDEF(0x01D952F0, "_ZN6CPlaneC2Ev", CPlane::CPlane),										// NOXREF
	//HOOK_SYMBOLDEF(0x01D95300, "_ZN6CPlane15InitializePlaneERK6VectorS2_", CPlane::InitializePlane),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D95340, "_ZN6CPlane12PointInFrontERK6Vector", CPlane::PointInFront),			// NOXREF
//linked objects
	HOOK_DEF(0x01D95840, func_plat),
	HOOK_DEF(0x01D96070, func_platrot),
	HOOK_DEF(0x01D967F0, func_train),
	HOOK_DEF(0x01D972C0, func_tracktrain),
	HOOK_DEF(0x01D98E10, func_traincontrols),
	HOOK_DEF(0x01D99070, func_trackchange),
	HOOK_DEF(0x01D9A150, func_trackautochange),
	HOOK_DEF(0x01D9A380, func_guntarget),

#endif // Plats_Region

#ifndef PathCorner_Region

//CPathTrack
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D94980, "_ZN10CPathTrack5SpawnEv", CPathTrack::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D946A0, "_ZN10CPathTrack8KeyValueEP14KeyValueData_s", CPathTrack::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D945F0, "_ZN10CPathTrack4SaveER5CSave", CPathTrack::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D94620, "_ZN10CPathTrack7RestoreER8CRestore", CPathTrack::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D949F0, "_ZN10CPathTrack8ActivateEv", CPathTrack::Activate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D946F0, "_ZN10CPathTrack3UseEP11CBaseEntityS1_8USE_TYPEf", CPathTrack::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D94B90, "_ZN10CPathTrack11SetPreviousEPS_", CPathTrack::SetPrevious),	// NOXREF
	HOOK_SYMBOLDEF(0x01D94790, "_ZN10CPathTrack4LinkEv", CPathTrack::Link),
	HOOK_SYMBOLDEF(0x01D94A10, "_ZN10CPathTrack9ValidPathEPS_i", CPathTrack::ValidPath),
	//HOOK_SYMBOLDEF(0x01D94A40, "_ZN10CPathTrack7ProjectEPS_S0_P6Vectorf", CPathTrack::Project),	// NOXREF
	HOOK_SYMBOLDEF(0x01D952A0, "_ZN10CPathTrack8InstanceEP7edict_s", CPathTrack::Instance),
	HOOK_SYMBOLDEF(0x01D94C00, "_ZN10CPathTrack9LookAheadEP6Vectorfi", CPathTrack::LookAhead),
	HOOK_SYMBOLDEF(0x01D951A0, "_ZN10CPathTrack7NearestE6Vector", CPathTrack::Nearest),
	HOOK_SYMBOLDEF(0x01D94B30, "_ZN10CPathTrack7GetNextEv", CPathTrack::GetNext),
	HOOK_SYMBOLDEF(0x01D94B60, "_ZN10CPathTrack11GetPreviousEv", CPathTrack::GetPrevious),
	//linked objects
	HOOK_DEF(0x01D94650, path_track),
//CPathCorner
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D945E0, "_ZN11CPathCorner5SpawnEv", CPathCorner::Spawn),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D94590, "_ZN11CPathCorner8KeyValueEP14KeyValueData_s", CPathCorner::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D94530, "_ZN11CPathCorner4SaveER5CSave", CPathCorner::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D94560, "_ZN11CPathCorner7RestoreER8CRestore", CPathCorner::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D94520, "_ZN11CPathCorner8GetDelayEv", CPathCorner::GetDelay),			// DEFAULT
	//linked objects
	HOOK_DEF(0x01D944D0, path_corner),

#endif // PathCorner_Region

#ifndef Vehicle_Region

//CFuncVehicle
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCBFC0, "_ZN12CFuncVehicle5SpawnEv", CFuncVehicle::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCC310, "_ZN12CFuncVehicle8PrecacheEv", CFuncVehicle::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCC1D0, "_ZN12CFuncVehicle7RestartEv", CFuncVehicle::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC9370, "_ZN12CFuncVehicle8KeyValueEP14KeyValueData_s", CFuncVehicle::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC92C0, "_ZN12CFuncVehicle4SaveER5CSave", CFuncVehicle::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC92F0, "_ZN12CFuncVehicle7RestoreER8CRestore", CFuncVehicle::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DCB970, "_ZN12CFuncVehicle10ObjectCapsEv", CFuncVehicle::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCBFB0, "_ZN12CFuncVehicle8ClassifyEv", CFuncVehicle::Classify),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCBF20, "_ZN12CFuncVehicle13OverrideResetEv", CFuncVehicle::OverrideReset),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCBA30, "_ZN12CFuncVehicle10OnControlsEP9entvars_s", CFuncVehicle::OnControls),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC9A10, "_ZN12CFuncVehicle3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncVehicle::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC9590, "_ZN12CFuncVehicle7BlockedEP11CBaseEntity", CFuncVehicle::Blocked),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DCAD10, "_ZN12CFuncVehicle4NextEv", CFuncVehicle::Next),
	HOOK_SYMBOLDEF(0x01DCBB60, "_ZN12CFuncVehicle4FindEv", CFuncVehicle::Find),
	HOOK_SYMBOLDEF(0x01DCBD10, "_ZN12CFuncVehicle11NearestPathEv", CFuncVehicle::NearestPath),
	HOOK_SYMBOLDEF(0x01DCB840, "_ZN12CFuncVehicle7DeadEndEv", CFuncVehicle::DeadEnd),
	HOOK_SYMBOLDEF(0x01DC9550, "_ZN12CFuncVehicle9NextThinkEfi", CFuncVehicle::NextThink),
	HOOK_SYMBOLDEF(0x01DCA6D0, "_ZN12CFuncVehicle18CollisionDetectionEv", CFuncVehicle::CollisionDetection),
	//HOOK_SYMBOLDEF(0x01DCAC50, "_ZN12CFuncVehicle16TerrainFollowingEv", CFuncVehicle::TerrainFollowing),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCA2F0, "_ZN12CFuncVehicle12CheckTurningEv", CFuncVehicle::CheckTurning),
	//HOOK_SYMBOLDEF(0x0, "_ZN12CFuncVehicle8SetTrackEP10CPathTrack", CFuncVehicle::SetTrack),				// NOXREF
	//HOOK_SYMBOLDEF(0x01DCB980, "_ZN12CFuncVehicle11SetControlsEP9entvars_s", CFuncVehicle::SetControls),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DCA110, "_ZN12CFuncVehicle9StopSoundEv", CFuncVehicle::StopSound),					// NOXREF
	HOOK_SYMBOLDEF(0x01DCA180, "_ZN12CFuncVehicle11UpdateSoundEv", CFuncVehicle::UpdateSound),
	//HOOK_SYMBOLDEF(0x01DCBF60, "_ZN12CFuncVehicle8InstanceEP7edict_s", CFuncVehicle::Instance),			// NOXREF
	//HOOK_DEF(0x0, FixupAngles2),	// NOXREF

#ifdef _WIN32
	//HOOK_DEF(0x01DCB7B0, Fix2),
#endif // _WIN32

	//linked objects
	HOOK_DEF(0x01DC9320, func_vehicle),
//CFuncVehicleControls
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCC5F0, "_ZN20CFuncVehicleControls5SpawnEv", CFuncVehicleControls::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DCC460, "_ZN20CFuncVehicleControls10ObjectCapsEv", CFuncVehicleControls::ObjectCaps),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DCC470, "_ZN20CFuncVehicleControls4FindEv", CFuncVehicleControls::Find),
	//linked objects
	HOOK_DEF(0x01DCC410, func_vehiclecontrols),

#endif // Vehicle_Region

#ifndef Func_Tank_Region

//CFuncTank
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DFB0, "_ZN9CFuncTank5SpawnEv", CFuncTank::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7E170, "_ZN9CFuncTank8PrecacheEv", CFuncTank::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7E1E0, "_ZN9CFuncTank8KeyValueEP14KeyValueData_s", CFuncTank::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DEB0, "_ZN9CFuncTank4SaveER5CSave", CFuncTank::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DEE0, "_ZN9CFuncTank7RestoreER8CRestore", CFuncTank::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FA70, "_ZN9CFuncTank10ObjectCapsEv", CFuncTank::ObjectCaps),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7E620, "_ZN9CFuncTank10OnControlsEP9entvars_s", CFuncTank::OnControls),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7EBD0, "_ZN9CFuncTank5ThinkEv", CFuncTank::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7E9A0, "_ZN9CFuncTank3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncTank::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7F560, "_ZN9CFuncTank4FireERK6VectorS2_P9entvars_s", CFuncTank::Fire),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FA40, "_ZN9CFuncTank20UpdateTargetPositionEP11CBaseEntity", CFuncTank::UpdateTargetPosition),	// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D7ECD0, "_ZN9CFuncTank11TrackTargetEv", CFuncTank::TrackTarget),
	HOOK_SYMBOLDEF(0x01D7F930, "_ZN9CFuncTank13StartRotSoundEv", CFuncTank::StartRotSound),
	//HOOK_SYMBOLDEF(0x01D7F990, "_ZN9CFuncTank12StopRotSoundEv", CFuncTank::StopRotSound),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CFuncTank8IsActiveEv", CFuncTank::IsActive),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CFuncTank12TankActivateEv", CFuncTank::TankActivate),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CFuncTank14TankDeactivateEv", CFuncTank::TankDeactivate),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CFuncTank7CanFireEv", CFuncTank::CanFire),		// NOXREF
	//HOOK_SYMBOLDEF(0x01D7EB80, "_ZN9CFuncTank7InRangeEf", CFuncTank::InRange),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D7EB70, "_ZN9CFuncTank10FindTargetEP7edict_s", CFuncTank::FindTarget),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D7F7B0, "_ZN9CFuncTank9TankTraceERK6VectorS2_S2_R11TraceResult", CFuncTank::TankTrace),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CFuncTank14BarrelPositionEv", CFuncTank::BarrelPosition),					// NOXREF
	HOOK_SYMBOLDEF(0x01D7F4B0, "_ZN9CFuncTank21AdjustAnglesForBarrelER6Vectorf", CFuncTank::AdjustAnglesForBarrel),
	HOOK_SYMBOLDEF(0x01D7E680, "_ZN9CFuncTank12StartControlEP11CBasePlayer", CFuncTank::StartControl),
	//HOOK_SYMBOLDEF(0x01D7E750, "_ZN9CFuncTank11StopControlEv", CFuncTank::StopControl),			// NOXREF
	HOOK_SYMBOLDEF(0x01D7E7F0, "_ZN9CFuncTank19ControllerPostFrameEv", CFuncTank::ControllerPostFrame),
//CFuncTankGun
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FA80, "_ZN12CFuncTankGun4FireERK6VectorS2_P9entvars_s", CFuncTankGun::Fire),
//CFuncTankLaser
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FD50, "_ZN14CFuncTankLaser8KeyValueEP14KeyValueData_s", CFuncTankLaser::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FBF0, "_ZN14CFuncTankLaser4SaveER5CSave", CFuncTankLaser::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FC40, "_ZN14CFuncTankLaser7RestoreER8CRestore", CFuncTankLaser::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FC90, "_ZN14CFuncTankLaser8ActivateEv", CFuncTankLaser::Activate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FE40, "_ZN14CFuncTankLaser5ThinkEv", CFuncTankLaser::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7FF60, "_ZN14CFuncTankLaser4FireERK6VectorS2_P9entvars_s", CFuncTankLaser::Fire),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D7FDA0, "_ZN14CFuncTankLaser8GetLaserEv", CFuncTankLaser::GetLaser),	// NOXREF
//CFuncTankRocket
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D80180, "_ZN15CFuncTankRocket8PrecacheEv", CFuncTankRocket::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D80200, "_ZN15CFuncTankRocket4FireERK6VectorS2_P9entvars_s", CFuncTankRocket::Fire),
//CFuncTankMortar
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D802E0, "_ZN15CFuncTankMortar8KeyValueEP14KeyValueData_s", CFuncTankMortar::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D80330, "_ZN15CFuncTankMortar4FireERK6VectorS2_P9entvars_s", CFuncTankMortar::Fire),
//CFuncTankControls
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D80590, "_ZN17CFuncTankControls5SpawnEv", CFuncTankControls::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D80450, "_ZN17CFuncTankControls4SaveER5CSave", CFuncTankControls::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D80480, "_ZN17CFuncTankControls7RestoreER8CRestore", CFuncTankControls::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D804B0, "_ZN17CFuncTankControls10ObjectCapsEv", CFuncTankControls::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D804E0, "_ZN17CFuncTankControls5ThinkEv", CFuncTankControls::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D804C0, "_ZN17CFuncTankControls3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncTankControls::Use),
//linked objects
	HOOK_DEF(0x01D7F9F0, func_tank),
	HOOK_DEF(0x01D7FBA0, func_tanklaser),
	HOOK_DEF(0x01D80130, func_tankrocket),
	HOOK_DEF(0x01D80290, func_tankmortar),
	HOOK_DEF(0x01D80400, func_tankcontrols),

#endif // Func_Tank_Region

#ifndef Func_Break_Region

//CBreakable
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7C410, "_ZN10CBreakable5SpawnEv", CBreakable::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7C7A0, "_ZN10CBreakable8PrecacheEv", CBreakable::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7C4F0, "_ZN10CBreakable7RestartEv", CBreakable::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7C180, "_ZN10CBreakable8KeyValueEP14KeyValueData_s", CBreakable::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7C3B0, "_ZN10CBreakable4SaveER5CSave", CBreakable::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7C3E0, "_ZN10CBreakable7RestoreER8CRestore", CBreakable::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DEA0, "_ZN10CBreakable10ObjectCapsEv", CBreakable::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7CDC0, "_ZN10CBreakable11TraceAttackEP9entvars_sf6VectorP11TraceResulti", CBreakable::TraceAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7CEB0, "_ZN10CBreakable10TakeDamageEP9entvars_sS1_fi", CBreakable::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D6D0, "_ZN10CBreakable11DamageDecalEi", CBreakable::DamageDecal),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7CD40, "_ZN10CBreakable3UseEP11CBaseEntityS1_8USE_TYPEf", CBreakable::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D7CB80, "_ZN10CBreakable10BreakTouchEP11CBaseEntity", CBreakable::BreakTouch),
	HOOK_SYMBOLDEF(0x01D7C9E0, "_ZN10CBreakable11DamageSoundEv", CBreakable::DamageSound),
	//HOOK_SYMBOLDEF(0x01D7D6C0, "_ZN10CBreakable11IsBreakableEv", CBreakable::IsBreakable),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CBreakable12SparkWhenHitEv", CBreakable::SparkWhenHit),	// NOXREF
	HOOK_SYMBOLDEF(0x01D7D0E0, "_ZN10CBreakable3DieEv", CBreakable::Die),
	//HOOK_SYMBOLDEF(0x0, "_ZN10CBreakable10ExplodableEv", CBreakable::Explodable),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CBreakable18ExplosionMagnitudeEv", CBreakable::ExplosionMagnitude),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CBreakable21ExplosionSetMagnitudeEi", CBreakable::ExplosionSetMagnitude),		// NOXREF
	HOOK_SYMBOLDEF(0x01D7C670, "_ZN10CBreakable21MaterialSoundPrecacheE9Materials", CBreakable::MaterialSoundPrecache),
	HOOK_SYMBOLDEF(0x01D7C710, "_ZN10CBreakable19MaterialSoundRandomEP7edict_s9Materialsf", CBreakable::MaterialSoundRandom),
	//HOOK_SYMBOLDEF(0x01D7C5D0, "_ZN10CBreakable17MaterialSoundListE9MaterialsRi", CBreakable::MaterialSoundList),	// NOXREF
//CPushable
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D800, "_ZN9CPushable5SpawnEv", CPushable::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D920, "_ZN9CPushable8PrecacheEv", CPushable::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D960, "_ZN9CPushable8KeyValueEP14KeyValueData_s", CPushable::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D700, "_ZN9CPushable4SaveER5CSave", CPushable::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D750, "_ZN9CPushable7RestoreER8CRestore", CPushable::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7D7F0, "_ZN9CPushable10ObjectCapsEv", CPushable::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DE70, "_ZN9CPushable10TakeDamageEP9entvars_sS1_fi", CPushable::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DC30, "_ZN9CPushable5TouchEP11CBaseEntity", CPushable::Touch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7DB40, "_ZN9CPushable3UseEP11CBaseEntityS1_8USE_TYPEf", CPushable::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D7DC70, "_ZN9CPushable4MoveEP11CBaseEntityi", CPushable::Move),
	//HOOK_SYMBOLDEF(0x0, "_ZN9CPushable9StopSoundEv", CPushable::StopSound),
	//HOOK_SYMBOLDEF(0x0, "_ZN9CPushable8MaxSpeedEv", CPushable::MaxSpeed),	// NOXREF
//linked objects
	HOOK_DEF(0x01D7C360, func_breakable),
	HOOK_DEF(0x01D7D7A0, func_pushable),

#endif // Func_Break_Region

#ifndef Door_Region

//CBaseDoor
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73D70, "_ZN9CBaseDoor5SpawnEv", CBaseDoor::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73FD0, "_ZN9CBaseDoor8PrecacheEv", CBaseDoor::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73F50, "_ZN9CBaseDoor7RestartEv", CBaseDoor::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73AA0, "_ZN9CBaseDoor8KeyValueEP14KeyValueData_s", CBaseDoor::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73820, "_ZN9CBaseDoor4SaveER5CSave", CBaseDoor::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73850, "_ZN9CBaseDoor7RestoreER8CRestore", CBaseDoor::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D73D10, "_ZN9CBaseDoor10ObjectCapsEv", CBaseDoor::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D73F90, "_ZN9CBaseDoor14SetToggleStateEi", CBaseDoor::SetToggleState),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D74540, "_ZN9CBaseDoor3UseEP11CBaseEntityS1_8USE_TYPEf", CBaseDoor::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D74CB0, "_ZN9CBaseDoor7BlockedEP11CBaseEntity", CBaseDoor::Blocked),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D744B0, "_ZN9CBaseDoor9DoorTouchEP11CBaseEntity", CBaseDoor::DoorTouch),
	HOOK_SYMBOLDEF(0x01D74580, "_ZN9CBaseDoor12DoorActivateEv", CBaseDoor::DoorActivate),
	HOOK_SYMBOLDEF(0x01D74640, "_ZN9CBaseDoor8DoorGoUpEv", CBaseDoor::DoorGoUp),
	HOOK_SYMBOLDEF(0x01D74AC0, "_ZN9CBaseDoor10DoorGoDownEv", CBaseDoor::DoorGoDown),
	HOOK_SYMBOLDEF(0x01D74990, "_ZN9CBaseDoor10DoorHitTopEv", CBaseDoor::DoorHitTop),
	HOOK_SYMBOLDEF(0x01D74BB0, "_ZN9CBaseDoor13DoorHitBottomEv", CBaseDoor::DoorHitBottom),
//CRotDoor
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75150, "_ZN8CRotDoor5SpawnEv", CRotDoor::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75000, "_ZN8CRotDoor7RestartEv", CRotDoor::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75380, "_ZN8CRotDoor14SetToggleStateEi", CRotDoor::SetToggleState),
//CMomentaryDoor
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D754B0, "_ZN14CMomentaryDoor5SpawnEv", CMomentaryDoor::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75650, "_ZN14CMomentaryDoor8PrecacheEv", CMomentaryDoor::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75780, "_ZN14CMomentaryDoor8KeyValueEP14KeyValueData_s", CMomentaryDoor::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75450, "_ZN14CMomentaryDoor4SaveER5CSave", CMomentaryDoor::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75480, "_ZN14CMomentaryDoor7RestoreER8CRestore", CMomentaryDoor::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D75440, "_ZN14CMomentaryDoor10ObjectCapsEv", CMomentaryDoor::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D75820, "_ZN14CMomentaryDoor3UseEP11CBaseEntityS1_8USE_TYPEf", CMomentaryDoor::Use),
	// non-class func
	HOOK_SYMBOLDEF(0x01D73880, "_Z14PlayLockSoundsP9entvars_sP10locksoundsii", PlayLockSounds),
//linked objects
	HOOK_DEF(0x01D73CC0, func_door),
	HOOK_DEF(0x01D73D20, func_water),
	HOOK_DEF(0x01D74FB0, func_door_rotating),
	HOOK_DEF(0x01D753F0, momentary_door),

#endif // Door_Region

#ifndef BModels_Region

//CFuncWall
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5CFE0, "_ZN9CFuncWall5SpawnEv", CFuncWall::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D5CFD0, "_ZN9CFuncWall10ObjectCapsEv", CFuncWall::ObjectCaps),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D060, "_ZN9CFuncWall3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncWall::Use),
//CFuncWallToggle
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D0F0, "_ZN15CFuncWallToggle5SpawnEv", CFuncWallToggle::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D230, "_ZN15CFuncWallToggle3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncWallToggle::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D5D1B0, "_ZN15CFuncWallToggle7TurnOffEv", CFuncWallToggle::TurnOff),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5D1E0, "_ZN15CFuncWallToggle6TurnOnEv", CFuncWallToggle::TurnOn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5D210, "_ZN15CFuncWallToggle4IsOnEv", CFuncWallToggle::IsOn),	// NOXREF
//CFuncConveyor
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D320, "_ZN13CFuncConveyor5SpawnEv", CFuncConveyor::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D4F0, "_ZN13CFuncConveyor3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncConveyor::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D5D470, "_ZN13CFuncConveyor11UpdateSpeedEf", CFuncConveyor::UpdateSpeed),	// NOXREF
//CFuncIllusionary
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D640, "_ZN16CFuncIllusionary5SpawnEv", CFuncIllusionary::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D5E0, "_ZN16CFuncIllusionary8KeyValueEP14KeyValueData_s", CFuncIllusionary::KeyValue),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D5D0, "_ZN16CFuncIllusionary10ObjectCapsEv", CFuncIllusionary::ObjectCaps),		// DEFAULT
//CFuncMonsterClip
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D700, "_ZN16CFuncMonsterClip5SpawnEv", CFuncMonsterClip::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D6F0, "_ZN16CFuncMonsterClip3UseEP11CBaseEntityS1_8USE_TYPEf", CFuncMonsterClip::Use), // PURE
//CFuncRotating
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D9F0, "_ZN13CFuncRotating5SpawnEv", CFuncRotating::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5DC20, "_ZN13CFuncRotating8PrecacheEv", CFuncRotating::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D870, "_ZN13CFuncRotating8KeyValueEP14KeyValueData_s", CFuncRotating::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D7B0, "_ZN13CFuncRotating4SaveER5CSave", CFuncRotating::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D7E0, "_ZN13CFuncRotating7RestoreER8CRestore", CFuncRotating::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D5D860, "_ZN13CFuncRotating10ObjectCapsEv", CFuncRotating::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5E590, "_ZN13CFuncRotating7BlockedEP11CBaseEntity", CFuncRotating::Blocked),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D5E050, "_ZN13CFuncRotating6SpinUpEv", CFuncRotating::SpinUp),
	HOOK_SYMBOLDEF(0x01D5E210, "_ZN13CFuncRotating8SpinDownEv", CFuncRotating::SpinDown),
	HOOK_SYMBOLDEF(0x01D5DDB0, "_ZN13CFuncRotating9HurtTouchEP11CBaseEntity", CFuncRotating::HurtTouch),
	HOOK_SYMBOLDEF(0x01D5E410, "_ZN13CFuncRotating11RotatingUseEP11CBaseEntityS1_8USE_TYPEf", CFuncRotating::RotatingUse),
	HOOK_SYMBOLDEF(0x01D5E3F0, "_ZN13CFuncRotating6RotateEv", CFuncRotating::Rotate),
	HOOK_SYMBOLDEF(0x01D5DF40, "_ZN13CFuncRotating12RampPitchVolEi", CFuncRotating::RampPitchVol),
//CPendulum
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5E700, "_ZN9CPendulum5SpawnEv", CPendulum::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5E670, "_ZN9CPendulum8KeyValueEP14KeyValueData_s", CPendulum::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5E610, "_ZN9CPendulum4SaveER5CSave", CPendulum::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5E640, "_ZN9CPendulum7RestoreER8CRestore", CPendulum::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D5E600, "_ZN9CPendulum10ObjectCapsEv", CPendulum::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EC10, "_ZN9CPendulum5TouchEP11CBaseEntity", CPendulum::Touch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EA10, "_ZN9CPendulum7BlockedEP11CBaseEntity", CPendulum::Blocked),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D5EA20, "_ZN9CPendulum5SwingEv", CPendulum::Swing),
	HOOK_SYMBOLDEF(0x01D5E8B0, "_ZN9CPendulum11PendulumUseEP11CBaseEntityS1_8USE_TYPEf", CPendulum::PendulumUse),
	HOOK_SYMBOLDEF(0x01D5E9C0, "_ZN9CPendulum4StopEv", CPendulum::Stop),
	HOOK_SYMBOLDEF(0x01D5EDA0, "_ZN9CPendulum9RopeTouchEP11CBaseEntity", CPendulum::RopeTouch),
// non-class func
	HOOK_SYMBOLDEF(0x01D5CF20, "_Z15VecBModelOriginP9entvars_s", VecBModelOrigin),
//linked objects
	HOOK_DEF(0x01D5CF80, func_wall),
	HOOK_DEF(0x01D5D0A0, func_wall_toggle),
	HOOK_DEF(0x01D5D2D0, func_conveyor),
	HOOK_DEF(0x01D5D580, func_illusionary),
	HOOK_DEF(0x01D5D6A0, func_monsterclip),
	HOOK_DEF(0x01D5D810, func_rotating),
	HOOK_DEF(0x01D5E5B0, func_pendulum),

#endif // BModels_Region

#ifndef Button_Region

//CEnvGlobal
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EF80, "_ZN10CEnvGlobal5SpawnEv", CEnvGlobal::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EED0, "_ZN10CEnvGlobal8KeyValueEP14KeyValueData_s", CEnvGlobal::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EE20, "_ZN10CEnvGlobal4SaveER5CSave", CEnvGlobal::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EE50, "_ZN10CEnvGlobal7RestoreER8CRestore", CEnvGlobal::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5EFE0, "_ZN10CEnvGlobal3UseEP11CBaseEntityS1_8USE_TYPEf", CEnvGlobal::Use),
//CMultiSource
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F1E0, "_ZN12CMultiSource5SpawnEv", CMultiSource::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F120, "_ZN12CMultiSource8KeyValueEP14KeyValueData_s", CMultiSource::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F230, "_ZN12CMultiSource3UseEP11CBaseEntityS1_8USE_TYPEf", CMultiSource::Use),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D60DF0, "_ZN12CMultiSource10ObjectCapsEv", CMultiSource::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F310, "_ZN12CMultiSource11IsTriggeredEP11CBaseEntity", CMultiSource::IsTriggered),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F070, "_ZN12CMultiSource4SaveER5CSave", CMultiSource::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F0A0, "_ZN12CMultiSource7RestoreER8CRestore", CMultiSource::Restore),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D5F370, "_ZN12CMultiSource8RegisterEv", CMultiSource::Register),
//CBaseButton
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5FB30, "_ZN11CBaseButton5SpawnEv", CBaseButton::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F510, "_ZN11CBaseButton8PrecacheEv", CBaseButton::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F7D0, "_ZN11CBaseButton8KeyValueEP14KeyValueData_s", CBaseButton::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F4B0, "_ZN11CBaseButton4SaveER5CSave", CBaseButton::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F4E0, "_ZN11CBaseButton7RestoreER8CRestore", CBaseButton::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D610F0, "_ZN11CBaseButton10ObjectCapsEv", CBaseButton::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D5F930, "_ZN11CBaseButton10TakeDamageEP9entvars_sS1_fi", CBaseButton::TakeDamage),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBaseButton8RotSpawnEv", CBaseButton::RotSpawn),	// NOXREF
	HOOK_SYMBOLDEF(0x01D603A0, "_ZN11CBaseButton14ButtonActivateEv", CBaseButton::ButtonActivate),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBaseButton15SparkSoundCacheEv", CBaseButton::SparkSoundCache),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CBaseButton10ButtonShotEv", CBaseButton::ButtonShot),	// NOXREF
	HOOK_SYMBOLDEF(0x01D601F0, "_ZN11CBaseButton11ButtonTouchEP11CBaseEntity", CBaseButton::ButtonTouch),
	HOOK_SYMBOLDEF(0x01D60030, "_ZN11CBaseButton11ButtonSparkEv", CBaseButton::ButtonSpark),
	HOOK_SYMBOLDEF(0x01D60490, "_ZN11CBaseButton14TriggerAndWaitEv", CBaseButton::TriggerAndWait),
	HOOK_SYMBOLDEF(0x01D60530, "_ZN11CBaseButton12ButtonReturnEv", CBaseButton::ButtonReturn),
	HOOK_SYMBOLDEF(0x01D605C0, "_ZN11CBaseButton14ButtonBackHomeEv", CBaseButton::ButtonBackHome),
	HOOK_SYMBOLDEF(0x01D60080, "_ZN11CBaseButton9ButtonUseEP11CBaseEntityS1_8USE_TYPEf", CBaseButton::ButtonUse),
	//HOOK_SYMBOLDEF(0x01D60190, "_ZN11CBaseButton21ButtonResponseToTouchEv", CBaseButton::ButtonResponseToTouch),	// NOXREF
	// non-class func
	HOOK_SYMBOLDEF(0x01D5FDA0, "_Z11ButtonSoundi", ButtonSound),
	HOOK_SYMBOLDEF(0x01D5FE90, "_Z7DoSparkP9entvars_sRK6Vector", DoSpark),
//CRotButton
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D60730, "_ZN10CRotButton5SpawnEv", CRotButton::Spawn),
//CMomentaryRotButton
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D60A10, "_ZN19CMomentaryRotButton5SpawnEv", CMomentaryRotButton::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D60BF0, "_ZN19CMomentaryRotButton8KeyValueEP14KeyValueData_s", CMomentaryRotButton::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D60940, "_ZN19CMomentaryRotButton4SaveER5CSave", CMomentaryRotButton::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D60970, "_ZN19CMomentaryRotButton7RestoreER8CRestore", CMomentaryRotButton::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D609F0, "_ZN19CMomentaryRotButton10ObjectCapsEv", CMomentaryRotButton::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D60CC0, "_ZN19CMomentaryRotButton3UseEP11CBaseEntityS1_8USE_TYPEf", CMomentaryRotButton::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D61180, "_ZN19CMomentaryRotButton3OffEv", CMomentaryRotButton::Off),
	HOOK_SYMBOLDEF(0x01D61200, "_ZN19CMomentaryRotButton6ReturnEv", CMomentaryRotButton::Return),
	HOOK_SYMBOLDEF(0x01D60F60, "_ZN19CMomentaryRotButton10UpdateSelfEf", CMomentaryRotButton::UpdateSelf),
	//HOOK_SYMBOLDEF(0x01D613E0, "_ZN19CMomentaryRotButton16UpdateSelfReturnEf", CMomentaryRotButton::UpdateSelfReturn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D60E00, "_ZN19CMomentaryRotButton16UpdateAllButtonsEfi", CMomentaryRotButton::UpdateAllButtons),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D60C70, "_ZN19CMomentaryRotButton9PlaySoundEv", CMomentaryRotButton::PlaySound),					// NOXREF
	//HOOK_SYMBOLDEF(0x01D61110, "_ZN19CMomentaryRotButton12UpdateTargetEf", CMomentaryRotButton::UpdateTarget),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN19CMomentaryRotButton8InstanceEP7edict_s", CMomentaryRotButton::Instance),					// NOXREF
//CEnvSpark
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D615A0, "_ZN9CEnvSpark5SpawnEv", CEnvSpark::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D61620, "_ZN9CEnvSpark8PrecacheEv", CEnvSpark::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D61670, "_ZN9CEnvSpark8KeyValueEP14KeyValueData_s", CEnvSpark::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D614A0, "_ZN9CEnvSpark4SaveER5CSave", CEnvSpark::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D614D0, "_ZN9CEnvSpark7RestoreER8CRestore", CEnvSpark::Restore),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D61730, "_ZN9CEnvSpark10SparkThinkEv", CEnvSpark::SparkThink),
	HOOK_SYMBOLDEF(0x01D61770, "_ZN9CEnvSpark10SparkStartEP11CBaseEntityS1_8USE_TYPEf", CEnvSpark::SparkStart),
	HOOK_SYMBOLDEF(0x01D617B0, "_ZN9CEnvSpark9SparkStopEP11CBaseEntityS1_8USE_TYPEf", CEnvSpark::SparkStop),
//CButtonTarget
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D61820, "_ZN13CButtonTarget5SpawnEv", CButtonTarget::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D61910, "_ZN13CButtonTarget10ObjectCapsEv", CButtonTarget::ObjectCaps),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D61930, "_ZN13CButtonTarget10TakeDamageEP9entvars_sS1_fi", CButtonTarget::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D61890, "_ZN13CButtonTarget3UseEP11CBaseEntityS1_8USE_TYPEf", CButtonTarget::Use),
// linked objects
	HOOK_DEF(0x01D5EE80, env_global),
	HOOK_DEF(0x01D5F0D0, multisource),
	HOOK_DEF(0x01D5FAE0, func_button),
	HOOK_DEF(0x01D606E0, func_rot_button),
	HOOK_DEF(0x01D609A0, momentary_rot_button),
	HOOK_DEF(0x01D61500, env_spark),
	HOOK_DEF(0x01D61550, env_debris),
	HOOK_DEF(0x01D617D0, button_target),

#endif // Button_Region

#ifndef Explode_Region

//CShower
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B960, "_ZN7CShower5SpawnEv", CShower::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D7B950, "_ZN7CShower10ObjectCapsEv", CShower::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BAD0, "_ZN7CShower5ThinkEv", CShower::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BB60, "_ZN7CShower5TouchEP11CBaseEntity", CShower::Touch),
	//linked objects
	HOOK_DEF(0x01D7B900, spark_shower),
//CEnvExplosion
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BD10, "_ZN13CEnvExplosion5SpawnEv", CEnvExplosion::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BCC0, "_ZN13CEnvExplosion8KeyValueEP14KeyValueData_s", CEnvExplosion::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BC10, "_ZN13CEnvExplosion4SaveER5CSave", CEnvExplosion::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BC40, "_ZN13CEnvExplosion7RestoreER8CRestore", CEnvExplosion::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D7BD70, "_ZN13CEnvExplosion3UseEP11CBaseEntityS1_8USE_TYPEf", CEnvExplosion::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D7C040, "_ZN13CEnvExplosion5SmokeEv", CEnvExplosion::Smoke),
	HOOK_SYMBOLDEF(0x01D7C0E0, "_Z15ExplosionCreateRK6VectorS1_P7edict_sii", ExplosionCreate),
	//linked objects
	HOOK_DEF(0x01D7BC70, env_explosion),

#endif // Explode_Region

#ifndef Mortar_Region

//CFuncMortarField
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A610, "_ZN16CFuncMortarField5SpawnEv", CFuncMortarField::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A680, "_ZN16CFuncMortarField8PrecacheEv", CFuncMortarField::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A500, "_ZN16CFuncMortarField8KeyValueEP14KeyValueData_s", CFuncMortarField::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A4A0, "_ZN16CFuncMortarField4SaveER5CSave", CFuncMortarField::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A4D0, "_ZN16CFuncMortarField7RestoreER8CRestore", CFuncMortarField::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A490, "_ZN16CFuncMortarField10ObjectCapsEv", CFuncMortarField::ObjectCaps),			// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D8A6B0, "_ZN16CFuncMortarField8FieldUseEP11CBaseEntityS1_8USE_TYPEf", CFuncMortarField::FieldUse),
	//linked objects
	HOOK_DEF(0x01D8A440, func_mortar_field),
//CMortar
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A990, "_ZN7CMortar5SpawnEv", CMortar::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A9D0, "_ZN7CMortar8PrecacheEv", CMortar::Precache),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D8A9F0, "_ZN7CMortar13MortarExplodeEv", CMortar::MortarExplode),
	//linked objects
	HOOK_DEF(0x01D8A940, monster_mortar),

#endif // Mortar_Region

#ifndef Healkit_Region

//CHealthKit
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D867A0, "_ZN10CHealthKit5SpawnEv", CHealthKit::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D867D0, "_ZN10CHealthKit8PrecacheEv", CHealthKit::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D867F0, "_ZN10CHealthKit7MyTouchEP11CBasePlayer", CHealthKit::MyTouch),
	//linked objects
	HOOK_DEF(0x01D86750, item_healthkit),
//CWallHealth
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86A30, "_ZN11CWallHealth5SpawnEv", CWallHealth::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86AC0, "_ZN11CWallHealth8PrecacheEv", CWallHealth::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86980, "_ZN11CWallHealth8KeyValueEP14KeyValueData_s", CWallHealth::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D868C0, "_ZN11CWallHealth4SaveER5CSave", CWallHealth::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D868F0, "_ZN11CWallHealth7RestoreER8CRestore", CWallHealth::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D86970, "_ZN11CWallHealth10ObjectCapsEv", CWallHealth::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86AF0, "_ZN11CWallHealth3UseEP11CBaseEntityS1_8USE_TYPEf", CWallHealth::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D86D90, "_ZN11CWallHealth3OffEv", CWallHealth::Off),
	HOOK_SYMBOLDEF(0x01D86D30, "_ZN11CWallHealth8RechargeEv", CWallHealth::Recharge),
	//linked objects
	HOOK_DEF(0x01D86920, func_healthcharger),

#endif // Healkit_Region

#ifndef Lights_Region

//CLight
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88790, "_ZN6CLight5SpawnEv", CLight::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88830, "_ZN6CLight7RestartEv", CLight::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88670, "_ZN6CLight4SaveER5CSave", CLight::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D886A0, "_ZN6CLight7RestoreER8CRestore", CLight::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D886D0, "_ZN6CLight8KeyValueEP14KeyValueData_s", CLight::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D888C0, "_ZN6CLight3UseEP11CBaseEntityS1_8USE_TYPEf", CLight::Use),
//CEnvLight
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88BB0, "_ZN9CEnvLight5SpawnEv", CEnvLight::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88A20, "_ZN9CEnvLight8KeyValueEP14KeyValueData_s", CEnvLight::KeyValue),
	//linked objects
	HOOK_DEF(0x01D88620, light),
	HOOK_DEF(0x01D88980, light_spot),
	HOOK_DEF(0x01D889D0, light_environment),

#endif // Lights_Region

#ifndef MapRules_Region

//CRuleEntity
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D88CC0, "_ZN11CRuleEntity5SpawnEv", CRuleEntity::Spawn),	// NOXREF
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88CF0, "_ZN11CRuleEntity8KeyValueEP14KeyValueData_s", CRuleEntity::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88C60, "_ZN11CRuleEntity4SaveER5CSave", CRuleEntity::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88C90, "_ZN11CRuleEntity7RestoreER8CRestore", CRuleEntity::Restore),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN11CRuleEntity9SetMasterEi", CRuleEntity::SetMaster),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D88D40, "_ZN11CRuleEntity19CanFireForActivatorEP11CBaseEntity", CRuleEntity::CanFireForActivator),	// NOXREF
//CRulePointEntity
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88D70, "_ZN16CRulePointEntity5SpawnEv", CRulePointEntity::Spawn),
//CRuleBrushEntity
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88DB0, "_ZN16CRuleBrushEntity5SpawnEv", CRuleBrushEntity::Spawn),
//CGameScore
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88E50, "_ZN10CGameScore5SpawnEv", CGameScore::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88E90, "_ZN10CGameScore8KeyValueEP14KeyValueData_s", CGameScore::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88F20, "_ZN10CGameScore3UseEP11CBaseEntityS1_8USE_TYPEf", CGameScore::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN10CGameScore6PointsEv", CGameScore::Points),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CGameScore18AllowNegativeScoreEv", CGameScore::AllowNegativeScore),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CGameScore11AwardToTeamEv", CGameScore::AwardToTeam),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CGameScore9SetPointsEi", CGameScore::SetPoints),			// NOXREF
//CGameEnd
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88FE0, "_ZN8CGameEnd3UseEP11CBaseEntityS1_8USE_TYPEf", CGameEnd::Use),
//CGameText
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89100, "_ZN9CGameText8KeyValueEP14KeyValueData_s", CGameText::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89060, "_ZN9CGameText4SaveER5CSave", CGameText::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D890B0, "_ZN9CGameText7RestoreER8CRestore", CGameText::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D893C0, "_ZN9CGameText3UseEP11CBaseEntityS1_8USE_TYPEf", CGameText::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN9CGameText12MessageToAllEv", CGameText::MessageToAll),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CGameText10MessageSetEPKc", CGameText::MessageSet),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CGameText10MessageGetEv", CGameText::MessageGet),			// NOXREF
//CGameTeamMaster
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D894B0, "_ZN15CGameTeamMaster8KeyValueEP14KeyValueData_s", CGameTeamMaster::KeyValue),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D894A0, "_ZN15CGameTeamMaster10ObjectCapsEv", CGameTeamMaster::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89690, "_ZN15CGameTeamMaster11IsTriggeredEP11CBaseEntity", CGameTeamMaster::IsTriggered),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D896E0, "_ZN15CGameTeamMaster6TeamIDEv", CGameTeamMaster::TeamID),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D895A0, "_ZN15CGameTeamMaster3UseEP11CBaseEntityS1_8USE_TYPEf", CGameTeamMaster::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGameTeamMaster12RemoveOnFireEv", CGameTeamMaster::RemoveOnFire),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGameTeamMaster7AnyTeamEv", CGameTeamMaster::AnyTeam),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D89700, "_ZN15CGameTeamMaster9TeamMatchEP11CBaseEntity", CGameTeamMaster::TeamMatch),	// NOXREF
//CGameTeamSet
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D897A0, "_ZN12CGameTeamSet3UseEP11CBaseEntityS1_8USE_TYPEf", CGameTeamSet::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameTeamSet12RemoveOnFireEv", CGameTeamSet::RemoveOnFire),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameTeamSet15ShouldClearTeamEv", CGameTeamSet::ShouldClearTeam),	// NOXREF
//CGamePlayerZone
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D898F0, "_ZN15CGamePlayerZone8KeyValueEP14KeyValueData_s", CGamePlayerZone::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89850, "_ZN15CGamePlayerZone4SaveER5CSave", CGamePlayerZone::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D898A0, "_ZN15CGamePlayerZone7RestoreER8CRestore", CGamePlayerZone::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89A10, "_ZN15CGamePlayerZone3UseEP11CBaseEntityS1_8USE_TYPEf", CGamePlayerZone::Use),
//CGamePlayerHurt
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89BE0, "_ZN15CGamePlayerHurt3UseEP11CBaseEntityS1_8USE_TYPEf", CGamePlayerHurt::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGamePlayerHurt12RemoveOnFireEv", CGamePlayerHurt::RemoveOnFire),		// NOXREF
//CGameCounter
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89CD0, "_ZN12CGameCounter5SpawnEv", CGameCounter::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89D30, "_ZN12CGameCounter3UseEP11CBaseEntityS1_8USE_TYPEf", CGameCounter::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter12RemoveOnFireEv", CGameCounter::RemoveOnFire),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter11ResetOnFireEv", CGameCounter::ResetOnFire),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter7CountUpEv", CGameCounter::CountUp),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter9CountDownEv", CGameCounter::CountDown),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter10ResetCountEv", CGameCounter::ResetCount),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter10CountValueEv", CGameCounter::CountValue),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter10LimitValueEv", CGameCounter::LimitValue),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter8HitLimitEv", CGameCounter::HitLimit),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter13SetCountValueEi", CGameCounter::SetCountValue),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CGameCounter15SetInitialValueEi", CGameCounter::SetInitialValue),	// NOXREF
//CGameCounterSet
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89E70, "_ZN15CGameCounterSet3UseEP11CBaseEntityS1_8USE_TYPEf", CGameCounterSet::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGameCounterSet12RemoveOnFireEv", CGameCounterSet::RemoveOnFire),		// NOXREF
//CGamePlayerEquip
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89F10, "_ZN16CGamePlayerEquip8KeyValueEP14KeyValueData_s", CGamePlayerEquip::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D89FE0, "_ZN16CGamePlayerEquip5TouchEP11CBaseEntity", CGamePlayerEquip::Touch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A0D0, "_ZN16CGamePlayerEquip3UseEP11CBaseEntityS1_8USE_TYPEf", CGamePlayerEquip::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN16CGamePlayerEquip7UseOnlyEv", CGamePlayerEquip::UseOnly),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D8A070, "_ZN16CGamePlayerEquip11EquipPlayerEP11CBaseEntity", CGamePlayerEquip::EquipPlayer),	// NOXREF
//CGamePlayerTeam
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8A1E0, "_ZN15CGamePlayerTeam3UseEP11CBaseEntityS1_8USE_TYPEf", CGamePlayerTeam::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGamePlayerTeam12RemoveOnFireEv", CGamePlayerTeam::RemoveOnFire),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGamePlayerTeam16ShouldKillPlayerEv", CGamePlayerTeam::ShouldKillPlayer),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN15CGamePlayerTeam15ShouldGibPlayerEv", CGamePlayerTeam::ShouldGibPlayer),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D8A180, "_ZN15CGamePlayerTeam14TargetTeamNameEPKc", CGamePlayerTeam::TargetTeamName),	// NOXREF

#endif // MapRules_Region

#ifndef HintMessage_Region

//CHintMessage
	//HOOK_SYMBOLDEF(0x0, "_ZNK12CHintMessage11GetDurationEv", CHintMessage::GetDuration),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12CHintMessage4SendER11CBaseEntity", CHintMessage::Send),	// NOXREF

//CHintMessageQueue
	HOOK_SYMBOLDEF(0x01D86FC0, "_ZN17CHintMessageQueue5ResetEv", CHintMessageQueue::Reset),
	HOOK_SYMBOLDEF(0x01D87050, "_ZN17CHintMessageQueue6UpdateER11CBaseEntity", CHintMessageQueue::Update),
	HOOK_SYMBOLDEF(0x01D87120, "_ZN17CHintMessageQueue10AddMessageEPKcfbP10CUtlVectorIS1_E", CHintMessageQueue::AddMessage),
	//HOOK_SYMBOLDEF(0x0, "_ZN17CHintMessageQueue7IsEmptyEv", CHintMessageQueue::IsEmpty),	// NOXREF

#endif // HintMessage_Region

#ifndef Items_Region

//CItem
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87570, "_ZN5CItem5SpawnEv", CItem::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D876C0, "_ZN5CItem7RespawnEv", CItem::Respawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN5CItem7MyTouchEP11CBasePlayer", CItem::MyTouch),	// NOXREF
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D87610, "_ZN5CItem9ItemTouchEP11CBaseEntity", CItem::ItemTouch),
	HOOK_SYMBOLDEF(0x01D87730, "_ZN5CItem11MaterializeEv", CItem::Materialize),
//CWorldItem
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D874A0, "_ZN10CWorldItem5SpawnEv", CWorldItem::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D87450, "_ZN10CWorldItem8KeyValueEP14KeyValueData_s", CWorldItem::KeyValue),
	//linked objects
	//HOOK_DEF(0x01D87400, world_items),
//CItemSuit
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D877F0, "_ZN9CItemSuit5SpawnEv", CItemSuit::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D878B0, "_ZN9CItemSuit8PrecacheEv", CItemSuit::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D878D0, "_ZN9CItemSuit7MyTouchEP11CBasePlayer", CItemSuit::MyTouch),
	//linked objects
	//HOOK_DEF(0x01D877A0, item_suit),
//CItemBattery
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87990, "_ZN12CItemBattery5SpawnEv", CItemBattery::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87A50, "_ZN12CItemBattery8PrecacheEv", CItemBattery::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87A70, "_ZN12CItemBattery7MyTouchEP11CBasePlayer", CItemBattery::MyTouch),
	//linked objects
	HOOK_DEF(0x01D87940, item_battery),
//CItemAntidote
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87C10, "_ZN13CItemAntidote5SpawnEv", CItemAntidote::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87CD0, "_ZN13CItemAntidote8PrecacheEv", CItemAntidote::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87CE0, "_ZN13CItemAntidote7MyTouchEP11CBasePlayer", CItemAntidote::MyTouch),
	//linked objects
	HOOK_DEF(0x01D87BC0, item_antidote),
//CItemSecurity
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D87D60, "_ZN13CItemSecurity5SpawnEv", CItemSecurity::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D87E20, "_ZN13CItemSecurity8PrecacheEv", CItemSecurity::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D87E30, "_ZN13CItemSecurity7MyTouchEP11CBasePlayer", CItemSecurity::MyTouch),
	//linked objects
	//HOOK_DEF(0x01D87D10, item_security),
//CItemLongJump
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87EA0, "_ZN13CItemLongJump5SpawnEv", CItemLongJump::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87F60, "_ZN13CItemLongJump8PrecacheEv", CItemLongJump::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D87F70, "_ZN13CItemLongJump7MyTouchEP11CBasePlayer", CItemLongJump::MyTouch),
	//linked objects
	HOOK_DEF(0x01D87E50, item_longjump),
//CItemKevlar
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88070, "_ZN11CItemKevlar5SpawnEv", CItemKevlar::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88130, "_ZN11CItemKevlar8PrecacheEv", CItemKevlar::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88140, "_ZN11CItemKevlar7MyTouchEP11CBasePlayer", CItemKevlar::MyTouch),
	//linked objects
	HOOK_DEF(0x01D88020, item_kevlar),
//CItemAssaultSuit
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88270, "_ZN16CItemAssaultSuit5SpawnEv", CItemAssaultSuit::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88330, "_ZN16CItemAssaultSuit8PrecacheEv", CItemAssaultSuit::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88340, "_ZN16CItemAssaultSuit7MyTouchEP11CBasePlayer", CItemAssaultSuit::MyTouch),
	//linked objects
	HOOK_DEF(0x01D88220, item_assaultsuit),
//CItemThighPack
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88460, "_ZN14CItemThighPack5SpawnEv", CItemThighPack::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88520, "_ZN14CItemThighPack8PrecacheEv", CItemThighPack::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D88530, "_ZN14CItemThighPack7MyTouchEP11CBasePlayer", CItemThighPack::MyTouch),
	//linked objects
	HOOK_DEF(0x01D88410, item_thighpack),

#endif // Items_Region

#ifndef Triggers_Region

//CFrictionModifier
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD1A0, "_ZN17CFrictionModifier5SpawnEv", CFrictionModifier::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD220, "_ZN17CFrictionModifier8KeyValueEP14KeyValueData_s", CFrictionModifier::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD140, "_ZN17CFrictionModifier4SaveER5CSave", CFrictionModifier::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD170, "_ZN17CFrictionModifier7RestoreER8CRestore", CFrictionModifier::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD130, "_ZN17CFrictionModifier10ObjectCapsEv", CFrictionModifier::ObjectCaps),			// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBD1F0, "_ZN17CFrictionModifier14ChangeFrictionEP11CBaseEntity", CFrictionModifier::ChangeFriction),
//CAutoTrigger
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD400, "_ZN12CAutoTrigger5SpawnEv", CAutoTrigger::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD410, "_ZN12CAutoTrigger8PrecacheEv", CAutoTrigger::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD340, "_ZN12CAutoTrigger8KeyValueEP14KeyValueData_s", CAutoTrigger::KeyValue),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD2D0, "_ZN12CAutoTrigger10ObjectCapsEv", CAutoTrigger::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD2E0, "_ZN12CAutoTrigger4SaveER5CSave", CAutoTrigger::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD310, "_ZN12CAutoTrigger7RestoreER8CRestore", CAutoTrigger::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD430, "_ZN12CAutoTrigger5ThinkEv", CAutoTrigger::Think),
//CTriggerRelay
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD5C0, "_ZN13CTriggerRelay5SpawnEv", CTriggerRelay::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD540, "_ZN13CTriggerRelay8KeyValueEP14KeyValueData_s", CTriggerRelay::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD4E0, "_ZN13CTriggerRelay4SaveER5CSave", CTriggerRelay::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD510, "_ZN13CTriggerRelay7RestoreER8CRestore", CTriggerRelay::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD4D0, "_ZN13CTriggerRelay10ObjectCapsEv", CTriggerRelay::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD5D0, "_ZN13CTriggerRelay3UseEP11CBaseEntityS1_8USE_TYPEf", CTriggerRelay::Use),
//CMultiManager
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD780, "_ZN13CMultiManager5SpawnEv", CMultiManager::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD7F0, "_ZN13CMultiManager7RestartEv", CMultiManager::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD6C0, "_ZN13CMultiManager8KeyValueEP14KeyValueData_s", CMultiManager::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD660, "_ZN13CMultiManager4SaveER5CSave", CMultiManager::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD690, "_ZN13CMultiManager7RestoreER8CRestore", CMultiManager::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD650, "_ZN13CMultiManager10ObjectCapsEv", CMultiManager::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBD8A0, "_ZN13CMultiManager9HasTargetEj", CMultiManager::HasTarget),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBD930, "_ZN13CMultiManager12ManagerThinkEv", CMultiManager::ManagerThink),
	HOOK_SYMBOLDEF(0x01DBDAD0, "_ZN13CMultiManager10ManagerUseEP11CBaseEntityS1_8USE_TYPEf", CMultiManager::ManagerUse),
	//HOOK_SYMBOLDEF(0x01DBDA10, "_ZN13CMultiManager5CloneEv", CMultiManager::Clone), // NOXREF
//CRenderFxManager
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBDC40, "_ZN16CRenderFxManager5SpawnEv", CRenderFxManager::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBDC50, "_ZN16CRenderFxManager3UseEP11CBaseEntityS1_8USE_TYPEf", CRenderFxManager::Use),
//CBaseTrigger
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBDE40, "_ZN12CBaseTrigger8KeyValueEP14KeyValueData_s", CBaseTrigger::KeyValue),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBDD80, "_ZN12CBaseTrigger10ObjectCapsEv", CBaseTrigger::ObjectCaps),				// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DBDD90, "_ZN12CBaseTrigger11InitTriggerEv", CBaseTrigger::InitTrigger),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC06D0, "_ZN12CBaseTrigger13TeleportTouchEP11CBaseEntity", CBaseTrigger::TeleportTouch),
	HOOK_SYMBOLDEF(0x01DBF070, "_ZN12CBaseTrigger10MultiTouchEP11CBaseEntity", CBaseTrigger::MultiTouch),
	HOOK_SYMBOLDEF(0x01DBEC40, "_ZN12CBaseTrigger9HurtTouchEP11CBaseEntity", CBaseTrigger::HurtTouch),
	//HOOK_SYMBOLDEF(0x0, "_ZN12CBaseTrigger12CDAudioTouchEP11CBaseEntity", CBaseTrigger::CDAudioTouch),	// NOXREF
	HOOK_SYMBOLDEF(0x01DBF0E0, "_ZN12CBaseTrigger20ActivateMultiTriggerEP11CBaseEntity", CBaseTrigger::ActivateMultiTrigger),
	HOOK_SYMBOLDEF(0x01DBF290, "_ZN12CBaseTrigger13MultiWaitOverEv", CBaseTrigger::MultiWaitOver),
	HOOK_SYMBOLDEF(0x01DBF2A0, "_ZN12CBaseTrigger10CounterUseEP11CBaseEntityS1_8USE_TYPEf", CBaseTrigger::CounterUse),
	HOOK_SYMBOLDEF(0x01DBEBE0, "_ZN12CBaseTrigger9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", CBaseTrigger::ToggleUse),
//CTriggerHurt
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE810, "_ZN12CTriggerHurt5SpawnEv", CTriggerHurt::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBE940, "_ZN12CTriggerHurt14RadiationThinkEv", CTriggerHurt::RadiationThink),
//CTriggerMonsterJump
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBDFA0, "_ZN19CTriggerMonsterJump5SpawnEv", CTriggerMonsterJump::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE0B0, "_ZN19CTriggerMonsterJump5ThinkEv", CTriggerMonsterJump::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE0E0, "_ZN19CTriggerMonsterJump5TouchEP11CBaseEntity", CTriggerMonsterJump::Touch),
//CTriggerCDAudio
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE270, "_ZN15CTriggerCDAudio5SpawnEv", CTriggerCDAudio::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE1C0, "_ZN15CTriggerCDAudio5TouchEP11CBaseEntity", CTriggerCDAudio::Touch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE320, "_ZN15CTriggerCDAudio3UseEP11CBaseEntityS1_8USE_TYPEf", CTriggerCDAudio::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DBE430, "_ZN15CTriggerCDAudio9PlayTrackEv", CTriggerCDAudio::PlayTrack),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBE3B0, "_Z11PlayCDTracki", PlayCDTrack),							// NOXREF
//CTargetCDAudio
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE560, "_ZN14CTargetCDAudio5SpawnEv", CTargetCDAudio::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE510, "_ZN14CTargetCDAudio8KeyValueEP14KeyValueData_s", CTargetCDAudio::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE640, "_ZN14CTargetCDAudio5ThinkEv", CTargetCDAudio::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBE5A0, "_ZN14CTargetCDAudio3UseEP11CBaseEntityS1_8USE_TYPEf", CTargetCDAudio::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DBE760, "_ZN14CTargetCDAudio4PlayEv", CTargetCDAudio::Play),	// NOXREF
//CTriggerMultiple
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBEE90, "_ZN16CTriggerMultiple5SpawnEv", CTriggerMultiple::Spawn),
//CTriggerOnce
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBEFB0, "_ZN12CTriggerOnce5SpawnEv", CTriggerOnce::Spawn),
//CTriggerCounter
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF410, "_ZN15CTriggerCounter5SpawnEv", CTriggerCounter::Spawn),
//CTriggerVolume
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF490, "_ZN14CTriggerVolume5SpawnEv", CTriggerVolume::Spawn),
//CFireAndDie
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF550, "_ZN11CFireAndDie5SpawnEv", CFireAndDie::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF5B0, "_ZN11CFireAndDie8PrecacheEv", CFireAndDie::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF540, "_ZN11CFireAndDie10ObjectCapsEv", CFireAndDie::ObjectCaps),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF5D0, "_ZN11CFireAndDie5ThinkEv", CFireAndDie::Think),
//CChangeLevel
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF7E0, "_ZN12CChangeLevel5SpawnEv", CChangeLevel::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF6A0, "_ZN12CChangeLevel8KeyValueEP14KeyValueData_s", CChangeLevel::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF640, "_ZN12CChangeLevel4SaveER5CSave", CChangeLevel::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBF670, "_ZN12CChangeLevel7RestoreER8CRestore", CChangeLevel::Restore),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBFD80, "_Z15BuildChangeListP9LEVELLISTi", BuildChangeList),
	//HOOK_SYMBOLDEF(0x01DC0150, "_Z9NextLevelv", NextLevel),		// NOXREF
	HOOK_SYMBOLDEF(0x01DBFA10, "_ZN12CChangeLevel14UseChangeLevelEP11CBaseEntityS1_8USE_TYPEf", CChangeLevel::UseChangeLevel),
	//HOOK_SYMBOLDEF(0x0, "_ZN12CChangeLevel18TriggerChangeLevelEv", CChangeLevel::TriggerChangeLevel),	 // NOXREF
	HOOK_SYMBOLDEF(0x01DBF950, "_ZN12CChangeLevel18ExecuteChangeLevelEv", CChangeLevel::ExecuteChangeLevel),
	HOOK_SYMBOLDEF(0x01DBFC60, "_ZN12CChangeLevel16TouchChangeLevelEP11CBaseEntity", CChangeLevel::TouchChangeLevel),
	HOOK_SYMBOLDEF(0x01DBFA20, "_ZN12CChangeLevel14ChangeLevelNowEP11CBaseEntity", CChangeLevel::ChangeLevelNow),
	//HOOK_SYMBOLDEF(0x01DBF990, "_ZN12CChangeLevel12FindLandmarkEPKc", CChangeLevel::FindLandmark),		// NOXREF
	HOOK_SYMBOLDEF(0x01DBFE50, "_ZN12CChangeLevel10ChangeListEP9LEVELLISTi", CChangeLevel::ChangeList),
	HOOK_SYMBOLDEF(0x01DBFCA0, "_ZN12CChangeLevel19AddTransitionToListEP9LEVELLISTiPKcS3_P7edict_s", CChangeLevel::AddTransitionToList),
	HOOK_SYMBOLDEF(0x01DBFD90, "_ZN12CChangeLevel18InTransitionVolumeEP11CBaseEntityPc", CChangeLevel::InTransitionVolume),
//CLadder
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0370, "_ZN7CLadder5SpawnEv", CLadder::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0300, "_ZN7CLadder8PrecacheEv", CLadder::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC02F0, "_ZN7CLadder8KeyValueEP14KeyValueData_s", CLadder::KeyValue),
//CTriggerPush
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0420, "_ZN12CTriggerPush5SpawnEv", CTriggerPush::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0410, "_ZN12CTriggerPush8KeyValueEP14KeyValueData_s", CTriggerPush::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0560, "_ZN12CTriggerPush5TouchEP11CBaseEntity", CTriggerPush::Touch),
//CTriggerTeleport
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC08B0, "_ZN16CTriggerTeleport5SpawnEv", CTriggerTeleport::Spawn),
//CBuyZone
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0A10, "_ZN8CBuyZone5SpawnEv", CBuyZone::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC0B00, "_ZN8CBuyZone8BuyTouchEP11CBaseEntity", CBuyZone::BuyTouch),
//CBombTarget
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0B90, "_ZN11CBombTarget5SpawnEv", CBombTarget::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC0C50, "_ZN11CBombTarget15BombTargetTouchEP11CBaseEntity", CBombTarget::BombTargetTouch),
	HOOK_SYMBOLDEF(0x01DC0CA0, "_ZN11CBombTarget13BombTargetUseEP11CBaseEntityS1_8USE_TYPEf", CBombTarget::BombTargetUse),
//CHostageRescue
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0D00, "_ZN14CHostageRescue5SpawnEv", CHostageRescue::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC0DC0, "_ZN14CHostageRescue18HostageRescueTouchEP11CBaseEntity", CHostageRescue::HostageRescueTouch),
//CEscapeZone
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC0E70, "_ZN11CEscapeZone5SpawnEv", CEscapeZone::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC0F30, "_ZN11CEscapeZone11EscapeTouchEP11CBaseEntity", CEscapeZone::EscapeTouch),
//CVIP_SafetyZone
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC10A0, "_ZN15CVIP_SafetyZone5SpawnEv", CVIP_SafetyZone::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC1160, "_ZN15CVIP_SafetyZone15VIP_SafetyTouchEP11CBaseEntity", CVIP_SafetyZone::VIP_SafetyTouch),
//CTriggerSave
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1240, "_ZN12CTriggerSave5SpawnEv", CTriggerSave::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC1320, "_ZN12CTriggerSave9SaveTouchEP11CBaseEntity", CTriggerSave::SaveTouch),
//CTriggerEndSection
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1410, "_ZN18CTriggerEndSection5SpawnEv", CTriggerEndSection::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1550, "_ZN18CTriggerEndSection8KeyValueEP14KeyValueData_s", CTriggerEndSection::KeyValue),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC13C0, "_ZN18CTriggerEndSection15EndSectionTouchEP11CBaseEntity", CTriggerEndSection::EndSectionTouch),
	HOOK_SYMBOLDEF(0x01DC1500, "_ZN18CTriggerEndSection13EndSectionUseEP11CBaseEntityS1_8USE_TYPEf", CTriggerEndSection::EndSectionUse),
//CTriggerGravity
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC15F0, "_ZN15CTriggerGravity5SpawnEv", CTriggerGravity::Spawn),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC16B0, "_ZN15CTriggerGravity12GravityTouchEP11CBaseEntity", CTriggerGravity::GravityTouch),
//CTriggerChangeTarget
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC17F0, "_ZN20CTriggerChangeTarget5SpawnEv", CTriggerChangeTarget::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC17A0, "_ZN20CTriggerChangeTarget8KeyValueEP14KeyValueData_s", CTriggerChangeTarget::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1740, "_ZN20CTriggerChangeTarget4SaveER5CSave", CTriggerChangeTarget::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1770, "_ZN20CTriggerChangeTarget7RestoreER8CRestore", CTriggerChangeTarget::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1730, "_ZN20CTriggerChangeTarget10ObjectCapsEv", CTriggerChangeTarget::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1800, "_ZN20CTriggerChangeTarget3UseEP11CBaseEntityS1_8USE_TYPEf", CTriggerChangeTarget::Use),
//CTriggerCamera
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1920, "_ZN14CTriggerCamera5SpawnEv", CTriggerCamera::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC19A0, "_ZN14CTriggerCamera8KeyValueEP14KeyValueData_s", CTriggerCamera::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC18C0, "_ZN14CTriggerCamera4SaveER5CSave", CTriggerCamera::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC18F0, "_ZN14CTriggerCamera7RestoreER8CRestore", CTriggerCamera::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DC18B0, "_ZN14CTriggerCamera10ObjectCapsEv", CTriggerCamera::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC1A90, "_ZN14CTriggerCamera3UseEP11CBaseEntityS1_8USE_TYPEf", CTriggerCamera::Use),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DC1DC0, "_ZN14CTriggerCamera12FollowTargetEv", CTriggerCamera::FollowTarget),
	HOOK_SYMBOLDEF(0x01DC20A0, "_ZN14CTriggerCamera4MoveEv", CTriggerCamera::Move),
//CWeather
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC2490, "_ZN8CWeather5SpawnEv", CWeather::Spawn),
//CClientFog
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC25E0, "_ZN10CClientFog5SpawnEv", CClientFog::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DC2560, "_ZN10CClientFog8KeyValueEP14KeyValueData_s", CClientFog::KeyValue),

//linked objects
	HOOK_DEF(0x01DBD0E0, func_friction),
	HOOK_DEF(0x01DBD280, trigger_auto),
	HOOK_DEF(0x01DBD480, trigger_relay),
	HOOK_DEF(0x01DBD600, multi_manager),
	HOOK_DEF(0x01DBDBF0, env_render),
	HOOK_DEF(0x01DBDD30, trigger),
	HOOK_DEF(0x01DBDF00, trigger_hurt),
	HOOK_DEF(0x01DBDF50, trigger_monsterjump),
	HOOK_DEF(0x01DBE170, trigger_cdaudio),
	HOOK_DEF(0x01DBE4C0, target_cdaudio),
	HOOK_DEF(0x01DBEE40, trigger_multiple),
	HOOK_DEF(0x01DBEF60, trigger_once),
	HOOK_DEF(0x01DBF3C0, trigger_counter),
	HOOK_DEF(0x01DBF440, trigger_transition),
	HOOK_DEF(0x01DBF4F0, fireanddie),
	HOOK_DEF(0x01DBF5F0, trigger_changelevel),
	HOOK_DEF(0x01DC02A0, func_ladder),
	HOOK_DEF(0x01DC03C0, trigger_push),
	HOOK_DEF(0x01DC0860, trigger_teleport),
	HOOK_DEF(0x01DC0970, info_teleport_destination),
	HOOK_DEF(0x01DC09C0, func_buyzone),
	HOOK_DEF(0x01DC0B40, func_bomb_target),
	HOOK_DEF(0x01DC0CB0, func_hostage_rescue),
	HOOK_DEF(0x01DC0E20, func_escapezone),
	HOOK_DEF(0x01DC1050, func_vip_safetyzone),
	HOOK_DEF(0x01DC11F0, trigger_autosave),
	HOOK_DEF(0x01DC1370, trigger_endsection),
	HOOK_DEF(0x01DC15A0, trigger_gravity),
	HOOK_DEF(0x01DC16E0, trigger_changetarget),
	HOOK_DEF(0x01DC1860, trigger_camera),
	HOOK_DEF(0x01DC2350, env_snow),
	HOOK_DEF(0x01DC23A0, func_snow),
	HOOK_DEF(0x01DC23F0, env_rain),
	HOOK_DEF(0x01DC2440, func_rain),
	HOOK_DEF(0x01DC2610, env_fog),

#endif // Triggers_Region

#ifndef SharedUtil_Region

#ifdef _WIN32
	HOOK_DEF(0x01D50CA0, CloneString),
#endif // _WIN32

	//HOOK_SYMBOLDEF(0x01D58EE0, "_Z14SharedWVarArgsPwz", SharedWVarArgs),			// NOXREF
	HOOK_SYMBOLDEF(0x01D58F30, "_Z13SharedVarArgsPcz", SharedVarArgs),
	HOOK_SYMBOLDEF(0x01D58F80, "_Z9BufPrintfPcRiPKcz", BufPrintf),
	//HOOK_SYMBOLDEF(0x01D58FD0, "_Z10BufWPrintfPwRiPKwz", BufWPrintf),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D59010, "_Z12NumAsWStringi", NumAsWString),				// NOXREF
	HOOK_SYMBOLDEF(0x01D59060, "_Z11NumAsStringi", NumAsString),
	HOOK_SYMBOLDEF(0x01D590B0, "_Z14SharedGetTokenv", SharedGetToken),
	//HOOK_SYMBOLDEF(0x01D590C0, "_Z18SharedSetQuoteCharc", SharedSetQuoteChar),		// NOXREF
	HOOK_SYMBOLDEF(0x01D590D0, "_Z11SharedParsePKc", SharedParse),
	//HOOK_SYMBOLDEF(0x01D591B0, "_Z18SharedTokenWaitingPKc", SharedTokenWaiting),		// NOXREF

#endif // SharedUtil_Region

#ifndef World_Region

	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD1750, "_ZN7CCorpse10ObjectCapsEv", CCorpse::ObjectCaps),		// DEFAULT
	// non-virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD1420, "_ZN6CDecal5SpawnEv", CDecal::Spawn),						// DEFAULT
	//HOOK_SYMBOLDEF(0x01DD15C0, "_ZN6CDecal11StaticDecalEv", CDecal::StaticDecal),					// DEFAULT
	//HOOK_SYMBOLDEF(0x01DD1490, "_ZN6CDecal12TriggerDecalEP11CBaseEntityS1_8USE_TYPEf", CDecal::TriggerDecal),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD1690, "_ZN6CDecal8KeyValueEP14KeyValueData_s", CDecal::KeyValue),				// DEFAULT
	//HOOK_SYMBOLDEF(0x01DD1760, "_Z13CopyToBodyQueP9entvars_s", CopyToBodyQue),	// PURE
	//HOOK_SYMBOLDEF(0x01DD1770, "_Z12ClearBodyQuev", ClearBodyQue),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD1780, "_ZN12CGlobalStateC2Ev", CGlobalState__CGlobalState),
	//HOOK_SYMBOLDEF(0x01DD1790, "_ZN12CGlobalState5ResetEv", CGlobalState::Reset),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD17A0, "_ZN12CGlobalState4FindEj", CGlobalState::Find),
	HOOK_SYMBOLDEF(0x01DD1810, "_ZN12CGlobalState11DumpGlobalsEv", CGlobalState::DumpGlobals),
	HOOK_SYMBOLDEF(0x01DD1860, "_ZN12CGlobalState9EntityAddEjj12GLOBALESTATE", CGlobalState::EntityAdd),
	HOOK_SYMBOLDEF(0x01DD18D0, "_ZN12CGlobalState14EntitySetStateEj12GLOBALESTATE", CGlobalState::EntitySetState),
	HOOK_SYMBOLDEF(0x01DD1950, "_ZN12CGlobalState15EntityFromTableEj", CGlobalState::EntityFromTable),
	HOOK_SYMBOLDEF(0x01DD19C0, "_ZN12CGlobalState14EntityGetStateEj", CGlobalState::EntityGetState),
	//HOOK_SYMBOLDEF(0x01DD1A40, "_ZN12CGlobalState4SaveER5CSave", CGlobalState::Save),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD1AB0, "_ZN12CGlobalState7RestoreER8CRestore", CGlobalState::Restore),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD1BD0, "_ZN12CGlobalState12EntityUpdateEjj", CGlobalState::EntityUpdate),
	//HOOK_SYMBOLDEF(0x01DD1C50, "_ZN12CGlobalState11ClearStatesEv", CGlobalState::ClearStates),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD1C80, "_Z15SaveGlobalStateP13saverestore_s", SaveGlobalState),
	HOOK_SYMBOLDEF(0x01DD1D00, "_Z18RestoreGlobalStateP13saverestore_s", RestoreGlobalState),
	HOOK_SYMBOLDEF(0x01DD1E50, "_Z16ResetGlobalStatev", ResetGlobalState),
//linked objects
	HOOK_DEF(0x01DD13D0, infodecal),
	HOOK_DEF(0x01DD1700, bodyque),
	HOOK_DEF(0x01DD1E90, worldspawn),

#endif // World_Region

#ifndef Graph_Region

	//HOOK_SYMBOLDEF(0x01D8AB70, "_ZN6CGraph9InitGraphEv", CGraph::InitGraph),	// pure
	//HOOK_SYMBOLDEF(0x01D8AB90, "_ZN6CGraph10AllocNodesEv", CGraph::AllocNodes), // pure
	//HOOK_SYMBOLDEF(0x01D8ABA0, "_ZN6CGraph12CheckNODFileEPc", CGraph::CheckNODFile), // pure
	//HOOK_SYMBOLDEF(0x01D8AB80, "_ZN6CGraph10FLoadGraphEPc", CGraph::FLoadGraph), // pure
	//HOOK_SYMBOLDEF(0x01D8ABB0, "_ZN6CGraph17FSetGraphPointersEv", CGraph::FSetGraphPointers), // pure
	//HOOK_SYMBOLDEF(0x01D8ABC0, "_ZN6CGraph19ShowNodeConnectionsEi", CGraph::ShowNodeConnections), // pure
	//HOOK_SYMBOLDEF(0x0, "_ZN6CGraph15FindNearestNodeERK6VectorP11CBaseEntity", CGraph::FindNearestNode, int(const Vector &, CBaseEntity *)),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D8ABD0, "_ZN6CGraph15FindNearestNodeERK6Vectori", CGraph::FindNearestNode, int(const Vector &, int)),

#endif // Graph_Region

#ifndef SoundEnt_Region

//CSound
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DBA520, "_ZN6CSound5ClearEv", CSound::Clear),	// NOXREF
	HOOK_SYMBOLDEF(0x01DBA560, "_ZN6CSound5ResetEv", CSound::Reset),
	//HOOK_SYMBOLDEF(0x01DBA590, "_ZN6CSound8FIsSoundEv", CSound::FIsSound),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBA5A0, "_ZN6CSound8FIsScentEv", CSound::FIsScent),	// NOXREF
	//linked objects
	HOOK_DEF(0x01DBA4D0, soundent),
//CSoundEnt
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBA5B0, "_ZN9CSoundEnt5SpawnEv", CSoundEnt::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBA760, "_ZN9CSoundEnt8PrecacheEv", CSoundEnt::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBAB10, "_ZN9CSoundEnt10ObjectCapsEv", CSoundEnt::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBA5E0, "_ZN9CSoundEnt5ThinkEv", CSoundEnt::Think),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBA8F0, "_ZN9CSoundEnt10InitializeEv", CSoundEnt::Initialize),
	HOOK_SYMBOLDEF(0x01DBA820, "_ZN9CSoundEnt11InsertSoundEiRK6Vectorif", CSoundEnt::InsertSound),
	//HOOK_SYMBOLDEF(0x01DBA770, "_ZN9CSoundEnt9FreeSoundEii", CSoundEnt::FreeSound),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBAA70, "_ZN9CSoundEnt10ActiveListEv", CSoundEnt::ActiveList),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBAA90, "_ZN9CSoundEnt8FreeListEv", CSoundEnt::FreeList),	// NOXREF
	HOOK_SYMBOLDEF(0x01DBAAB0, "_ZN9CSoundEnt20SoundPointerForIndexEi", CSoundEnt::SoundPointerForIndex),
	HOOK_SYMBOLDEF(0x01DBAB00, "_ZN9CSoundEnt16ClientSoundIndexEP7edict_s", CSoundEnt::ClientSoundIndex),
	//HOOK_SYMBOLDEF(0x0, "_ZN9CSoundEnt7IsEmptyEv", CSoundEnt::IsEmpty),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBAA20, "_ZN9CSoundEnt13ISoundsInListEi", CSoundEnt::ISoundsInList),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DBA7D0, "_ZN9CSoundEnt11IAllocSoundEv", CSoundEnt::IAllocSound),	// NOXREF

#endif // SoundEnt_Region

#ifndef Sound_Region

//CAmbientGeneric
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6CF0, "_ZN15CAmbientGeneric5SpawnEv", CAmbientGeneric::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6F90, "_ZN15CAmbientGeneric8PrecacheEv", CAmbientGeneric::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6E00, "_ZN15CAmbientGeneric7RestartEv", CAmbientGeneric::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB7900, "_ZN15CAmbientGeneric8KeyValueEP14KeyValueData_s", CAmbientGeneric::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6C90, "_ZN15CAmbientGeneric4SaveER5CSave", CAmbientGeneric::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6CC0, "_ZN15CAmbientGeneric7RestoreER8CRestore", CAmbientGeneric::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6C80, "_ZN15CAmbientGeneric10ObjectCapsEv", CAmbientGeneric::ObjectCaps),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DB7060, "_ZN15CAmbientGeneric9RampThinkEv", CAmbientGeneric::RampThink),
	HOOK_SYMBOLDEF(0x01DB7440, "_ZN15CAmbientGeneric19InitModulationParmsEv", CAmbientGeneric::InitModulationParms),
	HOOK_SYMBOLDEF(0x01DB76A0, "_ZN15CAmbientGeneric9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", CAmbientGeneric::ToggleUse),
//CEnvSound
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB8270, "_ZN9CEnvSound5SpawnEv", CEnvSound::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB7EC0, "_ZN9CEnvSound8KeyValueEP14KeyValueData_s", CEnvSound::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB7E60, "_ZN9CEnvSound4SaveER5CSave", CEnvSound::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB7E90, "_ZN9CEnvSound7RestoreER8CRestore", CEnvSound::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB8090, "_ZN9CEnvSound5ThinkEv", CEnvSound::Think),
//CSpeaker
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB9FD0, "_ZN8CSpeaker5SpawnEv", CSpeaker::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBA090, "_ZN8CSpeaker8PrecacheEv", CSpeaker::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBA480, "_ZN8CSpeaker8KeyValueEP14KeyValueData_s", CSpeaker::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB9F70, "_ZN8CSpeaker4SaveER5CSave", CSpeaker::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB9FA0, "_ZN8CSpeaker7RestoreER8CRestore", CSpeaker::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DB9F60, "_ZN8CSpeaker10ObjectCapsEv", CSpeaker::ObjectCaps),			// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBA3F0, "_ZN8CSpeaker9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", CSpeaker::ToggleUse),
	HOOK_SYMBOLDEF(0x01DBA0D0, "_ZN8CSpeaker12SpeakerThinkEv", CSpeaker::SpeakerThink),
	// non-class func
	HOOK_SYMBOLDEF(0x01DB7F30, "_Z16FEnvSoundInRangeP9entvars_sS0_Pf", FEnvSoundInRange),
	//HOOK_SYMBOLDEF(0x01DB82A0, "_Z18USENTENCEG_InitLRUPhi", USENTENCEG_InitLRU),		// NOXREF
	HOOK_SYMBOLDEF(0x01DB8310, "_Z25USENTENCEG_PickSequentialiPcii", USENTENCEG_PickSequential),
	HOOK_SYMBOLDEF(0x01DB8420, "_Z15USENTENCEG_PickiPc", USENTENCEG_Pick),
	//HOOK_SYMBOLDEF(0x01DB85C0, "_Z18SENTENCEG_GetIndexPKc", SENTENCEG_GetIndex),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DB8640, "_Z18SENTENCEG_PlayRndIP7edict_siffii", SENTENCEG_PlayRndI),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DB87B0, "_Z19SENTENCEG_PlayRndSzP7edict_sPKcffii", SENTENCEG_PlayRndSz),		// NOXREF
	HOOK_SYMBOLDEF(0x01DB89A0, "_Z26SENTENCEG_PlaySequentialSzP7edict_sPKcffiiii", SENTENCEG_PlaySequentialSz),
	//HOOK_SYMBOLDEF(0x01DB8BA0, "_Z14SENTENCEG_StopP7edict_sii", SENTENCEG_Stop),				// NOXREF
	HOOK_SYMBOLDEF(0x01DB8D30, "_Z14SENTENCEG_Initv", SENTENCEG_Init),
	HOOK_SYMBOLDEF(0x01DB9050, "_Z16SENTENCEG_LookupPKcPc", SENTENCEG_Lookup),
	HOOK_SYMBOLDEF(0x01DB9100, "_Z14EMIT_SOUND_DYNP7edict_siPKcffii", EMIT_SOUND_DYN),
	HOOK_SYMBOLDEF(0x01DB9210, "_Z15EMIT_SOUND_SUITP7edict_sPKc", EMIT_SOUND_SUIT),
	HOOK_SYMBOLDEF(0x01DB9380, "_Z17EMIT_GROUPID_SUITP7edict_si", EMIT_GROUPID_SUIT),
	//HOOK_SYMBOLDEF(0x01DB9510, "_Z19EMIT_GROUPNAME_SUITP7edict_sPKc", EMIT_GROUPNAME_SUIT),		// NOXREF
	HOOK_SYMBOLDEF(0x01DB9720, "_ZL8memfgetsPhiRiPci_constprop_21", memfgets),
	HOOK_SYMBOLDEF(0x01DB97C0, "_Z16TEXTURETYPE_Initv", TEXTURETYPE_Init),
	HOOK_SYMBOLDEF(0x01DB99A0, "_Z16TEXTURETYPE_FindPc", TEXTURETYPE_Find),
	HOOK_SYMBOLDEF(0x01DB99F0, "_Z21TEXTURETYPE_PlaySoundP11TraceResult6VectorS1_i", TEXTURETYPE_PlaySound),

	//linked objects
	HOOK_DEF(0x01DB6C30, ambient_generic),
	HOOK_DEF(0x01DB7E10, env_sound),
	HOOK_DEF(0x01DB9F10, speaker),

#endif // Sound_Region

#ifndef Util_Region

#ifdef _WIN32
	HOOK_DEF(0x01D67920, VARS, entvars_t *(edict_t *)),
	HOOK_DEF(0x01D78600, MAKE_STRING_CLASS),
#endif // _WIN32

	//HOOK_SYMBOLDEF(0x01DC2670, "_Z8U_Randomv", U_Random),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC26B0, "_Z7U_Srandj", U_Srand),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC26D0, "_Z21UTIL_SharedRandomLongjii", UTIL_SharedRandomLong),
	HOOK_SYMBOLDEF(0x01DC2740, "_Z22UTIL_SharedRandomFloatjff", UTIL_SharedRandomFloat),
	//HOOK_SYMBOLDEF(0x01DC2820, "_Z21UTIL_ParametricRocketP9entvars_s6VectorS1_P7edict_s", UTIL_ParametricRocket),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC2980, "_Z18UTIL_SetGroupTraceii", UTIL_SetGroupTrace),
	HOOK_SYMBOLDEF(0x01DC29B0, "_Z20UTIL_UnsetGroupTracev", UTIL_UnsetGroupTrace),
	//HOOK_SYMBOLDEF(0x01DC29D0, "_ZN15UTIL_GroupTraceC2Eii", UTIL_GroupTrace::UTIL_GroupTrace),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC2A10, "_ZN15UTIL_GroupTraceD2Ev", UTIL_GroupTrace::~UTIL_GroupTrace),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC2A30, "_Z22UTIL_GetNextBestWeaponP11CBasePlayerP15CBasePlayerItem", UTIL_GetNextBestWeapon),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC2A50, "_Z13UTIL_AngleModf", UTIL_AngleMod),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC2AD0, "_Z14UTIL_AngleDiffff", UTIL_AngleDiff),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC2B20, "_Z16UTIL_VecToAnglesRK6Vector", UTIL_VecToAngles),
	//HOOK_SYMBOLDEF(0x01DC2B50, "_Z17UTIL_MoveToOriginP7edict_sRK6Vectorfi", UTIL_MoveToOrigin),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC2B90, "_Z18UTIL_EntitiesInBoxPP11CBaseEntityiRK6VectorS4_i", UTIL_EntitiesInBox),
	//HOOK_SYMBOLDEF(0x01DC2C90, "_Z21UTIL_MonstersInSpherePP11CBaseEntityiRK6Vectorf", UTIL_MonstersInSphere),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC2D90, "_Z23UTIL_FindEntityInSphereP11CBaseEntityRK6Vectorf", UTIL_FindEntityInSphere),
	HOOK_SYMBOLDEF(0x01DC2DE0, "_Z27UTIL_FindEntityByString_OldP11CBaseEntityPKcS2_", UTIL_FindEntityByString_Old),
	HOOK_SYMBOLDEF(0x01DC2E30, "_Z23UTIL_FindEntityByStringP11CBaseEntityPKcS2_", UTIL_FindEntityByString),
	//HOOK_SYMBOLDEF(0x01DC2FB0, "_Z26UTIL_FindEntityByClassnameP11CBaseEntityPKc", UTIL_FindEntityByClassname),
	//HOOK_SYMBOLDEF(0x01DC2FD0, "_Z27UTIL_FindEntityByTargetnameP11CBaseEntityPKc", UTIL_FindEntityByTargetname),
	//HOOK_SYMBOLDEF(0x01DC2FF0, "_Z22UTIL_FindEntityGenericPKcR6Vectorf", UTIL_FindEntityGeneric),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC30A0, "_Z18UTIL_PlayerByIndexi", UTIL_PlayerByIndex),
	HOOK_SYMBOLDEF(0x01DC30E0, "_Z16UTIL_MakeVectorsRK6Vector", UTIL_MakeVectors),
	HOOK_SYMBOLDEF(0x01DC30F0, "_Z19UTIL_MakeAimVectorsRK6Vector", UTIL_MakeAimVectors),
	HOOK_SYMBOLDEF(0x01DC3120, "_Z19UTIL_MakeInvVectorsRK6VectorP12globalvars_t", UTIL_MakeInvVectors),
	HOOK_SYMBOLDEF(0x01DC31A0, "_Z21UTIL_EmitAmbientSoundP7edict_sRK6VectorPKcffii", UTIL_EmitAmbientSound),
	HOOK_SYMBOLDEF(0x01DC3240, "_Z16UTIL_ScreenShakeRK6Vectorffff", UTIL_ScreenShake),
	//HOOK_SYMBOLDEF(0x01DC33F0, "_Z19UTIL_ScreenShakeAllRK6Vectorfff", UTIL_ScreenShakeAll),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC3410, "_Z20UTIL_ScreenFadeBuildR10ScreenFadeRK6Vectorffii", UTIL_ScreenFadeBuild),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC34A0, "_Z20UTIL_ScreenFadeWriteRK10ScreenFadeP11CBaseEntity", UTIL_ScreenFadeWrite),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC3540, "_Z18UTIL_ScreenFadeAllRK6Vectorffii", UTIL_ScreenFadeAll),
	HOOK_SYMBOLDEF(0x01DC36E0, "_Z15UTIL_ScreenFadeP11CBaseEntityRK6Vectorffii", UTIL_ScreenFade),
	HOOK_SYMBOLDEF(0x01DC3810, "_Z15UTIL_HudMessageP11CBaseEntityRK14hudtextparms_sPKc", UTIL_HudMessage),
	HOOK_SYMBOLDEF(0x01DC3A80, "_Z18UTIL_HudMessageAllRK14hudtextparms_sPKc", UTIL_HudMessageAll),
	HOOK_SYMBOLDEF(0x01DC3AF0, "_Z19UTIL_ClientPrintAlliPKcS0_S0_S0_S0_", UTIL_ClientPrintAll),
	HOOK_SYMBOLDEF(0x01DC3B70, "_Z11ClientPrintP9entvars_siPKcS2_S2_S2_S2_", ClientPrint),
	//HOOK_SYMBOLDEF(0x01DC3C00, "_Z12UTIL_SayTextPKcP11CBaseEntity", UTIL_SayText),	// NOXREF						// NOXREF
	HOOK_SYMBOLDEF(0x01DC3C60, "_Z15UTIL_SayTextAllPKcP11CBaseEntity", UTIL_SayTextAll),
	HOOK_SYMBOLDEF(0x01DC3CB0, "_Z10UTIL_dtos1i", UTIL_dtos1),
	HOOK_SYMBOLDEF(0x01DC3CD0, "_Z10UTIL_dtos2i", UTIL_dtos2),
	//HOOK_SYMBOLDEF(0x01DC3CF0, "_Z10UTIL_dtos3i", UTIL_dtos3),		// NOXREF								// NOXREF
	//HOOK_SYMBOLDEF(0x01DC3D10, "_Z10UTIL_dtos4i", UTIL_dtos4),		// NOXREF
	HOOK_SYMBOLDEF(0x01DC3D30, "_Z20UTIL_ShowMessageArgsPKcP11CBaseEntityP10CUtlVectorIPcEb", UTIL_ShowMessageArgs),
	HOOK_SYMBOLDEF(0x01DC3E20, "_Z16UTIL_ShowMessagePKcP11CBaseEntityb", UTIL_ShowMessage),
	HOOK_SYMBOLDEF(0x01DC3E80, "_Z19UTIL_ShowMessageAllPKcb", UTIL_ShowMessageAll),
	HOOK_SYMBOLDEF(0x01DC3F30, "_Z14UTIL_TraceLineRK6VectorS1_15IGNORE_MONSTERS12IGNORE_GLASSP7edict_sP11TraceResult", UTIL_TraceLine, void (const Vector &, const Vector &, IGNORE_MONSTERS, IGNORE_GLASS, edict_t *, TraceResult *)),
	HOOK_SYMBOLDEF(0x01DC3F70, "_Z14UTIL_TraceLineRK6VectorS1_15IGNORE_MONSTERSP7edict_sP11TraceResult", UTIL_TraceLine, void (const Vector &, const Vector &, IGNORE_MONSTERS, edict_t *, TraceResult *)),
	HOOK_SYMBOLDEF(0x01DC3F90, "_Z14UTIL_TraceHullRK6VectorS1_15IGNORE_MONSTERSiP7edict_sP11TraceResult", UTIL_TraceHull),
	HOOK_SYMBOLDEF(0x01DC3FB0, "_Z15UTIL_TraceModelRK6VectorS1_iP7edict_sP11TraceResult", UTIL_TraceModel),
	//HOOK_SYMBOLDEF(0x01DC3FC0, "_Z19UTIL_GetGlobalTracev", UTIL_GetGlobalTrace),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC4090, "_Z12UTIL_SetSizeP9entvars_sRK6VectorS3_", UTIL_SetSize),
	HOOK_SYMBOLDEF(0x01DC40B0, "_Z13UTIL_VecToYawRK6Vector", UTIL_VecToYaw),
	HOOK_SYMBOLDEF(0x01DC40C0, "_Z14UTIL_SetOriginP9entvars_sRK6Vector", UTIL_SetOrigin),
	//HOOK_SYMBOLDEF(0x01DC40E0, "_Z19UTIL_ParticleEffectRK6VectorS1_jj", UTIL_ParticleEffect),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC4130, "_Z13UTIL_Approachfff", UTIL_Approach),
	HOOK_SYMBOLDEF(0x01DC4170, "_Z18UTIL_ApproachAnglefff", UTIL_ApproachAngle),
	HOOK_SYMBOLDEF(0x01DC42F0, "_Z18UTIL_AngleDistanceff", UTIL_AngleDistance),
	HOOK_SYMBOLDEF(0x01DC4330, "_Z19UTIL_SplineFractionff", UTIL_SplineFraction),
	HOOK_SYMBOLDEF(0x01DC4350, "_Z12UTIL_VarArgsPcz", UTIL_VarArgs),
	//HOOK_SYMBOLDEF(0x01DC4370, "_Z17UTIL_GetAimVectorP7edict_sf", UTIL_GetAimVector),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC43B0, "_Z22UTIL_IsMasterTriggeredjP11CBaseEntity", UTIL_IsMasterTriggered),
	//HOOK_SYMBOLDEF(0x01DC4430, "_Z20UTIL_ShouldShowBloodi", UTIL_ShouldShowBlood),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC4490, "_Z18UTIL_PointContentsRK6Vector", UTIL_PointContents),
	HOOK_SYMBOLDEF(0x01DC44A0, "_Z16UTIL_BloodStreamRK6VectorS1_ii", UTIL_BloodStream),
	HOOK_SYMBOLDEF(0x01DC4590, "_Z15UTIL_BloodDripsRK6VectorS1_ii", UTIL_BloodDrips),
	HOOK_SYMBOLDEF(0x01DC46D0, "_Z22UTIL_RandomBloodVectorv", UTIL_RandomBloodVector),
	HOOK_SYMBOLDEF(0x01DC4720, "_Z20UTIL_BloodDecalTraceP11TraceResulti", UTIL_BloodDecalTrace),
	HOOK_SYMBOLDEF(0x01DC47A0, "_Z15UTIL_DecalTraceP11TraceResulti", UTIL_DecalTrace),
	HOOK_SYMBOLDEF(0x01DC48A0, "_Z21UTIL_PlayerDecalTraceP11TraceResultiii", UTIL_PlayerDecalTrace),
	//HOOK_SYMBOLDEF(0x01DC4940, "_Z22UTIL_GunshotDecalTraceP11TraceResultibP9entvars_s", UTIL_GunshotDecalTrace),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC4A40, "_Z11UTIL_SparksRK6Vector", UTIL_Sparks),
	HOOK_SYMBOLDEF(0x01DC4A90, "_Z13UTIL_RicochetRK6Vectorf", UTIL_Ricochet),
	//HOOK_SYMBOLDEF(0x01DC4AF0, "_Z15UTIL_TeamsMatchPKcS0_", UTIL_TeamsMatch),
	//HOOK_SYMBOLDEF(0x01DC4B30, "_Z19UTIL_StringToVectorPfPKc", UTIL_StringToVector),
	HOOK_SYMBOLDEF(0x01DC4BB0, "_Z21UTIL_StringToIntArrayPiiPKc", UTIL_StringToIntArray),
	//HOOK_SYMBOLDEF(0x01DC4C40, "_Z21UTIL_ClampVectorToBoxRK6VectorS1_", UTIL_ClampVectorToBox),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC4D80, "_Z15UTIL_WaterLevelRK6Vectorff", UTIL_WaterLevel),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC4E50, "_Z12UTIL_Bubbles6VectorS_i", UTIL_Bubbles),
	HOOK_SYMBOLDEF(0x01DC5010, "_Z16UTIL_BubbleTrail6VectorS_i", UTIL_BubbleTrail),
	HOOK_SYMBOLDEF(0x01DC5290, "_Z11UTIL_RemoveP11CBaseEntity", UTIL_Remove),
	//HOOK_SYMBOLDEF(0x01DC52D0, "_Z18UTIL_IsValidEntityP7edict_s", UTIL_IsValidEntity),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC5300, "_Z18UTIL_PrecacheOtherPKc", UTIL_PrecacheOther),
	HOOK_SYMBOLDEF(0x01DC5380, "_Z14UTIL_LogPrintfPcz", UTIL_LogPrintf),
	//HOOK_SYMBOLDEF(0x01DC53B0, "_Z14UTIL_DotPointsRK6VectorS1_S1_", UTIL_DotPoints),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5430, "_Z15UTIL_StripTokenPKcPc", UTIL_StripToken),
	//HOOK_SYMBOLDEF(0x01DC5470, "_ZN18CSaveRestoreBufferC2Ev", (MethodThunk<CSaveRestoreBuffer>::Constructor), void()),														// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5480, "_ZN18CSaveRestoreBufferC2EP13saverestore_s", (MethodThunk<CSaveRestoreBuffer, SAVERESTOREDATA *>::Constructor), void(SAVERESTOREDATA *)),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5490, "_ZN18CSaveRestoreBufferD2Ev", CSaveRestoreBuffer::~CSaveRestoreBuffer),					// NOXREF
	HOOK_SYMBOLDEF(0x01DC54A0, "_ZN18CSaveRestoreBuffer11EntityIndexEP11CBaseEntity", CSaveRestoreBuffer::EntityIndex, int (CBaseEntity *)),
	//HOOK_SYMBOLDEF(0x01DC54F0, "_ZN18CSaveRestoreBuffer11EntityIndexEP7edict_s", CSaveRestoreBuffer::EntityIndex, int (entvars_t *)),			// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5540, "_ZN18CSaveRestoreBuffer11EntityIndexEi", CSaveRestoreBuffer::EntityIndex, int (EOFFSET)),						// NOXREF
	HOOK_SYMBOLDEF(0x01DC5590, "_ZN18CSaveRestoreBuffer11EntityIndexEP9entvars_s", CSaveRestoreBuffer::EntityIndex, int (edict_t *)),
	//HOOK_SYMBOLDEF(0x01DC55D0, "_ZN18CSaveRestoreBuffer15EntityFromIndexEi", CSaveRestoreBuffer::EntityFromIndex),			// NOXREF
	HOOK_SYMBOLDEF(0x01DC5610, "_ZN18CSaveRestoreBuffer14EntityFlagsSetEii", CSaveRestoreBuffer::EntityFlagsSet),
	//HOOK_SYMBOLDEF(0x01DC5660, "_ZN18CSaveRestoreBuffer12BufferRewindEi", CSaveRestoreBuffer::BufferRewind),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5690, "_ZN18CSaveRestoreBuffer10HashStringEPKc", CSaveRestoreBuffer::HashString),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC56B0, "_ZN18CSaveRestoreBuffer9TokenHashEPKc", CSaveRestoreBuffer::TokenHash),
	//HOOK_SYMBOLDEF(0x01DC57C0, "_ZN5CSave9WriteDataEPKciS1_", CSave::WriteData),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC58F0, "_ZN5CSave10WriteShortEPKcPKsi", CSave::WriteShort),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5A30, "_ZN5CSave8WriteIntEPKcPKii", CSave::WriteInt),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5B70, "_ZN5CSave10WriteFloatEPKcPKfi", CSave::WriteFloat),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5CB0, "_ZN5CSave9WriteTimeEPKcPKfi", CSave::WriteTime),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5DF0, "_ZN5CSave11WriteStringEPKcS1_", CSave::WriteString, void(const char *, const char *)),							// NOXREF
	//HOOK_SYMBOLDEF(0x01DC5F30, "_ZN5CSave11WriteStringEPKcPKii", CSave::WriteString, void(const char *, const int *, int)),						// NOXREF
	//HOOK_SYMBOLDEF(0x01DC60C0, "_ZN5CSave11WriteVectorEPKcRK6Vector", CSave::WriteVector, void(const char *, const Vector &)),					// NOXREF
	//HOOK_SYMBOLDEF(0x01DC61E0, "_ZN5CSave11WriteVectorEPKcPKfi", CSave::WriteVector, void(const char *, const float *, int)),						// NOXREF
	//HOOK_SYMBOLDEF(0x01DC6310, "_ZN5CSave19WritePositionVectorEPKcRK6Vector", CSave::WritePositionVector, void(const char *, const Vector &)),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC64F0, "_ZN5CSave19WritePositionVectorEPKcPKfi", CSave::WritePositionVector, void(const char *, const float *, int)),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DC6670, "_ZN5CSave13WriteFunctionEPKcPPvi", CSave::WriteFunction),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC67E0, "_Z15EntvarsKeyvalueP9entvars_sP14KeyValueData_s", EntvarsKeyvalue),
	HOOK_SYMBOLDEF(0x01DC6990, "_ZN5CSave12WriteEntVarsEPKcP9entvars_s", CSave::WriteEntVars),
	HOOK_SYMBOLDEF(0x01DC69B0, "_ZN5CSave11WriteFieldsEPKcPvP15TYPEDESCRIPTIONi", CSave::WriteFields),
	//HOOK_SYMBOLDEF(0x01DC6E60, "_ZN5CSave12BufferStringEPci", CSave::BufferString),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC6F20, "_ZN5CSave9DataEmptyEPKci", CSave::DataEmpty),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC6F50, "_ZN5CSave11BufferFieldEPKciS1_", CSave::BufferField),
	HOOK_SYMBOLDEF(0x01DC7080, "_ZN5CSave12BufferHeaderEPKci", CSave::BufferHeader),
	HOOK_SYMBOLDEF(0x01DC7150, "_ZN5CSave10BufferDataEPKci", CSave::BufferData),
	HOOK_SYMBOLDEF(0x01DC71C0, "_ZN8CRestore9ReadFieldEPvP15TYPEDESCRIPTIONiiiPcS0_", CRestore::ReadField),
	HOOK_SYMBOLDEF(0x01DC7610, "_ZN8CRestore11ReadEntVarsEPKcP9entvars_s", CRestore::ReadEntVars),
	HOOK_SYMBOLDEF(0x01DC7630, "_ZN8CRestore10ReadFieldsEPKcPvP15TYPEDESCRIPTIONi", CRestore::ReadFields),
	HOOK_SYMBOLDEF(0x01DC78D0, "_ZN8CRestore10ReadFieldsEPKcPvP15TYPEDESCRIPTIONi", CRestore::Empty),
	//HOOK_SYMBOLDEF(0x01DC78F0, "_ZN8CRestore16BufferReadHeaderEP6HEADER", CRestore::BufferReadHeader),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7A20, "_ZN8CRestore9ReadShortEv", CRestore::ReadShort),				// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7A90, "_ZN8CRestore7ReadIntEv", CRestore::ReadInt),					// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7AF0, "_ZN8CRestore12ReadNamedIntEPKc", CRestore::ReadNamedInt),			// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7C10, "_ZN8CRestore15ReadNamedStringEPKc", CRestore::ReadNamedString),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7D30, "_ZN8CRestore13BufferPointerEv", CRestore::BufferPointer),			// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7D40, "_ZN8CRestore15BufferReadBytesEPci", CRestore::BufferReadBytes),
	//HOOK_SYMBOLDEF(0x01DC7DC0, "_ZN8CRestore15BufferSkipBytesEi", CRestore::BufferSkipBytes),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7E20, "_ZN8CRestore17BufferSkipZStringEv", CRestore::BufferSkipZString),		// NOXREF
	//HOOK_SYMBOLDEF(0x01DC7EA0, "_ZN8CRestore18BufferCheckZStringEPKc", CRestore::BufferCheckZString),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC7EF0, "_Z15UTIL_TextureHitP11TraceResult6VectorS1_", UTIL_TextureHit),
	//HOOK_DEF(0x01DC8000, GetPlayerTeam),	// NOXREF
	HOOK_SYMBOLDEF(0x01DC8040, "_Z11UTIL_IsGamePKc", UTIL_IsGame),
	HOOK_SYMBOLDEF(0x01DC8090, "_Z21UTIL_GetPlayerGaitYawi", UTIL_GetPlayerGaitYaw),
	HOOK_SYMBOLDEF(0x01D630B0, "_ZN7EHANDLE3GetEv", EHANDLE::Get),
	//HOOK_SYMBOLDEF(0x01D630D0, "_ZN7EHANDLE3SetEP7edict_s", EHANDLE::Set),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D630F0, "_ZN7EHANDLEcvP11CBaseEntityEv", EHANDLE::operator CBaseEntity*),	// don't take the address
	//HOOK_SYMBOLDEF(0x01D63110, "_ZN7EHANDLEaSEP11CBaseEntity", EHANDLE::CBaseEntity *operator=),	// don't take the address
	//HOOK_SYMBOLDEF(0x01D63140, "_ZN7EHANDLEcviEv", EHANDLE::operator int),				// don't take the address
	//HOOK_SYMBOLDEF(0x01D63170, "_ZN7EHANDLEptEv", EHANDLE::CBaseEntity *operator->),			// don't take the address

#endif // Util_Region

#ifndef WeaponType_Region

	HOOK_SYMBOLDEF(0x01D01000, "_Z15AliasToWeaponIDPKc", AliasToWeaponID),
	HOOK_SYMBOLDEF(0x01D01050, "_Z18BuyAliasToWeaponIDPKcR12WeaponIdType", BuyAliasToWeaponID),
	HOOK_SYMBOLDEF(0x01D010C0, "_Z15WeaponIDToAliasi", WeaponIDToAlias),
	HOOK_SYMBOLDEF(0x01D010F0, "_Z18AliasToWeaponClassPKc", AliasToWeaponClass),
	HOOK_SYMBOLDEF(0x01D01140, "_Z21WeaponIDToWeaponClassi", WeaponIDToWeaponClass),
	HOOK_SYMBOLDEF(0x01D011C0, "_Z15IsPrimaryWeaponi", IsPrimaryWeapon),
	//HOOK_SYMBOLDEF(0x01D01250, "_Z17IsSecondaryWeaponi", IsSecondaryWeapon),	// NOXREF
	HOOK_SYMBOLDEF(0x01D012A0, "_Z13GetWeaponInfoi", GetWeaponInfo, WeaponInfoStruct *(int)),
	HOOK_SYMBOLDEF(0x01D012E0, "_Z21CanBuyWeaponByMaptypei12WeaponIdTypeb", CanBuyWeaponByMaptype),

#endif // WeaponType_Region

#ifndef GameRules_Region

	HOOK_SYMBOLDEF(0x01D80C90, "_Z16InstallGameRulesv", InstallGameRules),							// HOOK: FIX ME
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D80C00, CHalfLifeMultiplay, "_ZN10CGameRules16RefreshSkillDataEv", CGameRules::RefreshSkillData),
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EBB0, CHalfLifeMultiplay, "_ZN10CGameRules10IsTeamplayEv", CGameRules::IsTeamplay),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EBC0, CHalfLifeMultiplay, "_ZN10CGameRules18GetGameDescriptionEv", CGameRules::GetGameDescription),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EBD0, CHalfLifeMultiplay, "_ZN10CGameRules14UpdateGameModeEP11CBasePlayer", CGameRules::UpdateGameMode),	// PURE
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EBE0, CHalfLifeMultiplay, "_ZN10CGameRules20FPlayerCanTakeDamageEP11CBasePlayerP11CBaseEntity", CGameRules::FPlayerCanTakeDamage),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EBF0, CHalfLifeMultiplay, "_ZN10CGameRules13ShouldAutoAimEP11CBasePlayerP7edict_s", CGameRules::ShouldAutoAim),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D80A60, CHalfLifeMultiplay, "_ZN10CGameRules18GetPlayerSpawnSpotEP11CBasePlayer", CGameRules::GetPlayerSpawnSpot),
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EC00, CHalfLifeMultiplay, "_ZN10CGameRules24AllowAutoTargetCrosshairEv", CGameRules::AllowAutoTargetCrosshair),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EC10, CHalfLifeMultiplay, "_ZN10CGameRules25ClientCommand_DeadOrAliveEP11CBasePlayerPKc", CGameRules::ClientCommand_DeadOrAlive),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EC60, CHalfLifeMultiplay, "_ZN10CGameRules13ClientCommandEP11CBasePlayerPKc", CGameRules::ClientCommand),					// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EC70, CHalfLifeMultiplay, "_ZN10CGameRules21ClientUserInfoChangedEP11CBasePlayerPc", CGameRules::ClientUserInfoChanged),	// PURE
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D80B60, CHalfLifeMultiplay, "_ZN10CGameRules17CanHavePlayerItemEP11CBasePlayerP15CBasePlayerItem", CGameRules::CanHavePlayerItem),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D80A20, CHalfLifeMultiplay, "_ZN10CGameRules11CanHaveAmmoEP11CBasePlayerPKci", CGameRules::CanHaveAmmo),
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EC80, CHalfLifeMultiplay, "_ZN10CGameRules24FlHEVChargerRechargeTimeEv", CGameRules::FlHEVChargerRechargeTime),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EC90, CHalfLifeMultiplay, "_ZN10CGameRules12GetTeamIndexEPKc", CGameRules::GetTeamIndex),					// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8ED40, CHalfLifeMultiplay, "_ZN10CGameRules18GetIndexedTeamNameEi", CGameRules::GetIndexedTeamName),				// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8ED50, CHalfLifeMultiplay, "_ZN10CGameRules11IsValidTeamEPKc", CGameRules::IsValidTeam),					// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8ED60, CHalfLifeMultiplay, "_ZN10CGameRules16ChangePlayerTeamEP11CBasePlayerPKcii", CGameRules::ChangePlayerTeam),	// PURE
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8ED70, CHalfLifeMultiplay, "_ZN10CGameRules20SetDefaultPlayerTeamEP11CBasePlayer", CGameRules::SetDefaultPlayerTeam),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8ED80, CHalfLifeMultiplay, "_ZN10CGameRules17PlayTextureSoundsEv", CGameRules::PlayTextureSounds),				// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8ED90, CHalfLifeMultiplay, "_ZN10CGameRules18EndMultiplayerGameEv", CGameRules::EndMultiplayerGame),	// PURE
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EDA0, CHalfLifeMultiplay, "_ZN10CGameRules14IsFreezePeriodEv", CGameRules::IsFreezePeriod),				// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EDB0, CHalfLifeMultiplay, "_ZN10CGameRules16ServerDeactivateEv", CGameRules::ServerDeactivate),	// PURE
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D8EDC0, CHalfLifeMultiplay, "_ZN10CGameRules18CheckMapConditionsEv", CGameRules::CheckMapConditions),	// PURE

#endif // GameRules_Region

#ifndef Singleplay_GameRules_Region

	//HOOK_DEF(0x01DB6730, MethodThunk<CHalfLifeRules>::Constructor),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6750, "_ZN14CHalfLifeRules5ThinkEv", CHalfLifeRules::Think),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6AF0, "_ZN14CHalfLifeRules16IsAllowedToSpawnEP11CBaseEntity", CHalfLifeRules::IsAllowedToSpawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6BB0, "_ZN14CHalfLifeRules16FAllowFlashlightEv", CHalfLifeRules::FAllowFlashlight),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6790, "_ZN14CHalfLifeRules19FShouldSwitchWeaponEP11CBasePlayerP15CBasePlayerItem", CHalfLifeRules::FShouldSwitchWeapon),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB67C0, "_ZN14CHalfLifeRules17GetNextBestWeaponEP11CBasePlayerP15CBasePlayerItem", CHalfLifeRules::GetNextBestWeapon),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6760, "_ZN14CHalfLifeRules13IsMultiplayerEv", CHalfLifeRules::IsMultiplayer),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6770, "_ZN14CHalfLifeRules12IsDeathmatchEv", CHalfLifeRules::IsDeathmatch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6780, "_ZN14CHalfLifeRules6IsCoOpEv", CHalfLifeRules::IsCoOp),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB67D0, "_ZN14CHalfLifeRules15ClientConnectedEP7edict_sPKcS3_Pc", CHalfLifeRules::ClientConnected),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB67E0, "_ZN14CHalfLifeRules7InitHUDEP11CBasePlayer", CHalfLifeRules::InitHUD),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB67F0, "_ZN14CHalfLifeRules18ClientDisconnectedEP7edict_s", CHalfLifeRules::ClientDisconnected),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6800, "_ZN14CHalfLifeRules18FlPlayerFallDamageEP11CBasePlayer", CHalfLifeRules::FlPlayerFallDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6820, "_ZN14CHalfLifeRules11PlayerSpawnEP11CBasePlayer", CHalfLifeRules::PlayerSpawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB68A0, "_ZN14CHalfLifeRules11PlayerThinkEP11CBasePlayer", CHalfLifeRules::PlayerThink),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB68B0, "_ZN14CHalfLifeRules17FPlayerCanRespawnEP11CBasePlayer", CHalfLifeRules::FPlayerCanRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB68C0, "_ZN14CHalfLifeRules17FlPlayerSpawnTimeEP11CBasePlayer", CHalfLifeRules::FlPlayerSpawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6960, "_ZN14CHalfLifeRules18GetPlayerSpawnSpotEP11CBasePlayer", CHalfLifeRules::GetPlayerSpawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6890, "_ZN14CHalfLifeRules24AllowAutoTargetCrosshairEv", CHalfLifeRules::AllowAutoTargetCrosshair),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB68D0, "_ZN14CHalfLifeRules14IPointsForKillEP11CBasePlayerS1_", CHalfLifeRules::IPointsForKill),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB68E0, "_ZN14CHalfLifeRules12PlayerKilledEP11CBasePlayerP9entvars_sS3_", CHalfLifeRules::PlayerKilled),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB68F0, "_ZN14CHalfLifeRules11DeathNoticeEP11CBasePlayerP9entvars_sS3_", CHalfLifeRules::DeathNotice),		// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6900, "_ZN14CHalfLifeRules15PlayerGotWeaponEP11CBasePlayerP15CBasePlayerItem", CHalfLifeRules::PlayerGotWeapon),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6A70, "_ZN14CHalfLifeRules19WeaponShouldRespawnEP15CBasePlayerItem", CHalfLifeRules::WeaponShouldRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6910, "_ZN14CHalfLifeRules19FlWeaponRespawnTimeEP15CBasePlayerItem", CHalfLifeRules::FlWeaponRespawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6920, "_ZN14CHalfLifeRules18FlWeaponTryRespawnEP15CBasePlayerItem", CHalfLifeRules::FlWeaponTryRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6930, "_ZN14CHalfLifeRules20VecWeaponRespawnSpotEP15CBasePlayerItem", CHalfLifeRules::VecWeaponRespawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6A80, "_ZN14CHalfLifeRules11CanHaveItemEP11CBasePlayerP5CItem", CHalfLifeRules::CanHaveItem),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6A90, "_ZN14CHalfLifeRules13PlayerGotItemEP11CBasePlayerP5CItem", CHalfLifeRules::PlayerGotItem),		// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6AA0, "_ZN14CHalfLifeRules17ItemShouldRespawnEP5CItem", CHalfLifeRules::ItemShouldRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6AB0, "_ZN14CHalfLifeRules17FlItemRespawnTimeEP5CItem", CHalfLifeRules::FlItemRespawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6AC0, "_ZN14CHalfLifeRules18VecItemRespawnSpotEP5CItem", CHalfLifeRules::VecItemRespawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B00, "_ZN14CHalfLifeRules13PlayerGotAmmoEP11CBasePlayerPci", CHalfLifeRules::PlayerGotAmmo),		// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B10, "_ZN14CHalfLifeRules17AmmoShouldRespawnEP15CBasePlayerAmmo", CHalfLifeRules::AmmoShouldRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B20, "_ZN14CHalfLifeRules17FlAmmoRespawnTimeEP15CBasePlayerAmmo", CHalfLifeRules::FlAmmoRespawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B30, "_ZN14CHalfLifeRules18VecAmmoRespawnSpotEP15CBasePlayerAmmo", CHalfLifeRules::VecAmmoRespawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B60, "_ZN14CHalfLifeRules27FlHealthChargerRechargeTimeEv", CHalfLifeRules::FlHealthChargerRechargeTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B70, "_ZN14CHalfLifeRules17DeadPlayerWeaponsEP11CBasePlayer", CHalfLifeRules::DeadPlayerWeapons),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B80, "_ZN14CHalfLifeRules14DeadPlayerAmmoEP11CBasePlayer", CHalfLifeRules::DeadPlayerAmmo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6BC0, "_ZN14CHalfLifeRules9GetTeamIDEP11CBaseEntity", CHalfLifeRules::GetTeamID),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6B90, "_ZN14CHalfLifeRules18PlayerRelationshipEP11CBasePlayerP11CBaseEntity", CHalfLifeRules::PlayerRelationship),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DB6BA0, "_ZN14CHalfLifeRules14FAllowMonstersEv", CHalfLifeRules::FAllowMonsters),

#endif // Singleplay_GameRules_Region

#ifndef Multiplay_GameRules_Region

//CHalfLifeMultiplay
	// virtual func
	//HOOK_SYMBOLDEF(0x01D8B8A0, "_ZN18CHalfLifeMultiplayC2Ev", CHalfLifeMultiplay::CHalfLifeMultiplay),	// constuctor
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8BF00, "_ZN18CHalfLifeMultiplay16RefreshSkillDataEv", CHalfLifeMultiplay::RefreshSkillData),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8F420, "_ZN18CHalfLifeMultiplay5ThinkEv", CHalfLifeMultiplay::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D921D0, "_ZN18CHalfLifeMultiplay16IsAllowedToSpawnEP11CBaseEntity", CHalfLifeMultiplay::IsAllowedToSpawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92410, "_ZN18CHalfLifeMultiplay16FAllowFlashlightEv", CHalfLifeMultiplay::FAllowFlashlight),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D909E0, "_ZN18CHalfLifeMultiplay19FShouldSwitchWeaponEP11CBasePlayerP15CBasePlayerItem", CHalfLifeMultiplay::FShouldSwitchWeapon),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D90A70, "_ZN18CHalfLifeMultiplay17GetNextBestWeaponEP11CBasePlayerP15CBasePlayerItem", CHalfLifeMultiplay::GetNextBestWeapon),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D909B0, "_ZN18CHalfLifeMultiplay13IsMultiplayerEv", CHalfLifeMultiplay::IsMultiplayer),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D909C0, "_ZN18CHalfLifeMultiplay12IsDeathmatchEv", CHalfLifeMultiplay::IsDeathmatch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D909D0, "_ZN18CHalfLifeMultiplay6IsCoOpEv", CHalfLifeMultiplay::IsCoOp),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D90B60, "_ZN18CHalfLifeMultiplay15ClientConnectedEP7edict_sPKcS3_Pc", CHalfLifeMultiplay::ClientConnected),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D90BC0, "_ZN18CHalfLifeMultiplay7InitHUDEP11CBasePlayer", CHalfLifeMultiplay::InitHUD),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D910E0, "_ZN18CHalfLifeMultiplay18ClientDisconnectedEP7edict_s", CHalfLifeMultiplay::ClientDisconnected),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D90B80, "_ZN18CHalfLifeMultiplay14UpdateGameModeEP11CBasePlayer", CHalfLifeMultiplay::UpdateGameMode),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D91360, "_ZN18CHalfLifeMultiplay18FlPlayerFallDamageEP11CBasePlayer", CHalfLifeMultiplay::FlPlayerFallDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D91390, "_ZN18CHalfLifeMultiplay20FPlayerCanTakeDamageEP11CBasePlayerP11CBaseEntity", CHalfLifeMultiplay::FPlayerCanTakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D91560, "_ZN18CHalfLifeMultiplay11PlayerSpawnEP11CBasePlayer", CHalfLifeMultiplay::PlayerSpawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D913E0, "_ZN18CHalfLifeMultiplay11PlayerThinkEP11CBasePlayer", CHalfLifeMultiplay::PlayerThink),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D915F0, "_ZN18CHalfLifeMultiplay17FPlayerCanRespawnEP11CBasePlayer", CHalfLifeMultiplay::FPlayerCanRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D916C0, "_ZN18CHalfLifeMultiplay17FlPlayerSpawnTimeEP11CBasePlayer", CHalfLifeMultiplay::FlPlayerSpawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92280, "_ZN18CHalfLifeMultiplay18GetPlayerSpawnSpotEP11CBasePlayer", CHalfLifeMultiplay::GetPlayerSpawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D916D0, "_ZN18CHalfLifeMultiplay24AllowAutoTargetCrosshairEv", CHalfLifeMultiplay::AllowAutoTargetCrosshair),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D90B30, "_ZN18CHalfLifeMultiplay25ClientCommand_DeadOrAliveEP11CBasePlayerPKc", CHalfLifeMultiplay::ClientCommand_DeadOrAlive),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D90B50, "_ZN18CHalfLifeMultiplay13ClientCommandEP11CBasePlayerPKc", CHalfLifeMultiplay::ClientCommand),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D93660, "_ZN18CHalfLifeMultiplay21ClientUserInfoChangedEP11CBasePlayerPc", CHalfLifeMultiplay::ClientUserInfoChanged),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D916E0, "_ZN18CHalfLifeMultiplay14IPointsForKillEP11CBasePlayerS1_", CHalfLifeMultiplay::IPointsForKill),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D916F0, "_ZN18CHalfLifeMultiplay12PlayerKilledEP11CBasePlayerP9entvars_sS3_", CHalfLifeMultiplay::PlayerKilled),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D91BE0, "_ZN18CHalfLifeMultiplay11DeathNoticeEP11CBasePlayerP9entvars_sS3_", CHalfLifeMultiplay::DeathNotice),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92130, "_ZN18CHalfLifeMultiplay17CanHavePlayerItemEP11CBasePlayerP15CBasePlayerItem", CHalfLifeMultiplay::CanHavePlayerItem),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D92060, "_ZN18CHalfLifeMultiplay15PlayerGotWeaponEP11CBasePlayerP15CBasePlayerItem", CHalfLifeMultiplay::PlayerGotWeapon),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92110, "_ZN18CHalfLifeMultiplay19WeaponShouldRespawnEP15CBasePlayerItem", CHalfLifeMultiplay::WeaponShouldRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92070, "_ZN18CHalfLifeMultiplay19FlWeaponRespawnTimeEP15CBasePlayerItem", CHalfLifeMultiplay::FlWeaponRespawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92080, "_ZN18CHalfLifeMultiplay18FlWeaponTryRespawnEP15CBasePlayerItem", CHalfLifeMultiplay::FlWeaponTryRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D920E0, "_ZN18CHalfLifeMultiplay20VecWeaponRespawnSpotEP15CBasePlayerItem", CHalfLifeMultiplay::VecWeaponRespawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92140, "_ZN18CHalfLifeMultiplay11CanHaveItemEP11CBasePlayerP5CItem", CHalfLifeMultiplay::CanHaveItem),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92150, "_ZN18CHalfLifeMultiplay13PlayerGotItemEP11CBasePlayerP5CItem", CHalfLifeMultiplay::PlayerGotItem),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92160, "_ZN18CHalfLifeMultiplay17ItemShouldRespawnEP5CItem", CHalfLifeMultiplay::ItemShouldRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92180, "_ZN18CHalfLifeMultiplay17FlItemRespawnTimeEP5CItem", CHalfLifeMultiplay::FlItemRespawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92190, "_ZN18CHalfLifeMultiplay18VecItemRespawnSpotEP5CItem", CHalfLifeMultiplay::VecItemRespawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D921C0, "_ZN18CHalfLifeMultiplay13PlayerGotAmmoEP11CBasePlayerPci", CHalfLifeMultiplay::PlayerGotAmmo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D921E0, "_ZN18CHalfLifeMultiplay17AmmoShouldRespawnEP15CBasePlayerAmmo", CHalfLifeMultiplay::AmmoShouldRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92200, "_ZN18CHalfLifeMultiplay17FlAmmoRespawnTimeEP15CBasePlayerAmmo", CHalfLifeMultiplay::FlAmmoRespawnTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92210, "_ZN18CHalfLifeMultiplay18VecAmmoRespawnSpotEP15CBasePlayerAmmo", CHalfLifeMultiplay::VecAmmoRespawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92240, "_ZN18CHalfLifeMultiplay27FlHealthChargerRechargeTimeEv", CHalfLifeMultiplay::FlHealthChargerRechargeTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92250, "_ZN18CHalfLifeMultiplay24FlHEVChargerRechargeTimeEv", CHalfLifeMultiplay::FlHEVChargerRechargeTime),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92260, "_ZN18CHalfLifeMultiplay17DeadPlayerWeaponsEP11CBasePlayer", CHalfLifeMultiplay::DeadPlayerWeapons),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92270, "_ZN18CHalfLifeMultiplay14DeadPlayerAmmoEP11CBasePlayer", CHalfLifeMultiplay::DeadPlayerAmmo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D8EDD0, "_ZN18CHalfLifeMultiplay9GetTeamIDEP11CBaseEntity", CHalfLifeMultiplay::GetTeamID),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D922D0, "_ZN18CHalfLifeMultiplay18PlayerRelationshipEP11CBasePlayerP11CBaseEntity", CHalfLifeMultiplay::PlayerRelationship),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D8EDE0, "_ZN18CHalfLifeMultiplay17PlayTextureSoundsEv", CHalfLifeMultiplay::PlayTextureSounds),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92450, "_ZN18CHalfLifeMultiplay14FAllowMonstersEv", CHalfLifeMultiplay::FAllowMonsters),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D8EE20, "_ZN18CHalfLifeMultiplay18EndMultiplayerGameEv", CHalfLifeMultiplay::EndMultiplayerGame),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8B4B0, "_ZN18CHalfLifeMultiplay16ServerDeactivateEv", CHalfLifeMultiplay::ServerDeactivate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8DFD0, "_ZN18CHalfLifeMultiplay18CheckMapConditionsEv", CHalfLifeMultiplay::CheckMapConditions),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8C050, "_ZN18CHalfLifeMultiplay10CleanUpMapEv", CHalfLifeMultiplay::CleanUpMap),
	// HOOK_SYMBOL_VIRTUAL_DEF(0x01D8E0A0, "_ZN18CHalfLifeMultiplay12RestartRoundEv", CHalfLifeMultiplay::RestartRound),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8CAF0, "_ZN18CHalfLifeMultiplay18CheckWinConditionsEv", CHalfLifeMultiplay::CheckWinConditions),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8BF60, "_ZN18CHalfLifeMultiplay10RemoveGunsEv", CHalfLifeMultiplay::RemoveGuns),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8C340, "_ZN18CHalfLifeMultiplay6GiveC4Ev", CHalfLifeMultiplay::GiveC4),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D93270, "_ZN18CHalfLifeMultiplay11ChangeLevelEv", CHalfLifeMultiplay::ChangeLevel),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D92480, "_ZN18CHalfLifeMultiplay16GoToIntermissionEv", CHalfLifeMultiplay::GoToIntermission),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D8B4A0, "_ZN18CHalfLifeMultiplay8IsCareerEv", CHalfLifeMultiplay::IsCareer),
	HOOK_SYMBOLDEF(0x01D8C800, "_ZN18CHalfLifeMultiplay23QueueCareerRoundEndMenuEfi", CHalfLifeMultiplay::QueueCareerRoundEndMenu),
	//HOOK_SYMBOLDEF(0x01D8B470, "_ZN18CHalfLifeMultiplay19SetCareerMatchLimitEii", CHalfLifeMultiplay::SetCareerMatchLimit),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D8B310, "_ZN18CHalfLifeMultiplay15IsInCareerRoundEv", CHalfLifeMultiplay::IsInCareerRound),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D908F0, "_ZN18CHalfLifeMultiplay13CareerRestartEv", CHalfLifeMultiplay::CareerRestart),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN18CHalfLifeMultiplay16PlayerJoinedTeamEP11CBasePlayer", CHalfLifeMultiplay::PlayerJoinedTeam),	// NOXREF
	HOOK_SYMBOLDEF(0x01D8EC20, "_ZN18CHalfLifeMultiplay8TeamFullEi", CHalfLifeMultiplay::TeamFull),
	HOOK_SYMBOLDEF(0x01D8ECA0, "_ZN18CHalfLifeMultiplay11TeamStackedEii", CHalfLifeMultiplay::TeamStacked),
	HOOK_SYMBOLDEF(0x01D8EE30, "_ZN18CHalfLifeMultiplay15IsVIPQueueEmptyEv", CHalfLifeMultiplay::IsVIPQueueEmpty),
	HOOK_SYMBOLDEF(0x01D8EEA0, "_ZN18CHalfLifeMultiplay13AddToVIPQueueEP11CBasePlayer", CHalfLifeMultiplay::AddToVIPQueue),
	HOOK_SYMBOLDEF(0x01D8F0D0, "_ZN18CHalfLifeMultiplay11PickNextVIPEv", CHalfLifeMultiplay::PickNextVIP),
	//HOOK_SYMBOLDEF(0x01D90790, "_ZN18CHalfLifeMultiplay19HasRoundTimeExpiredEv", CHalfLifeMultiplay::HasRoundTimeExpired),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D90820, "_ZN18CHalfLifeMultiplay13IsBombPlantedEv", CHalfLifeMultiplay::IsBombPlanted),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D90860, "_ZN18CHalfLifeMultiplay51MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRoundEi", CHalfLifeMultiplay::MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound),	// NOXREF
	HOOK_SYMBOLDEF(0x01D8EDF0, "_ZN18CHalfLifeMultiplay13StackVIPQueueEv", CHalfLifeMultiplay::StackVIPQueue),
	HOOK_SYMBOLDEF(0x01D8EFA0, "_ZN18CHalfLifeMultiplay15ResetCurrentVIPEv", CHalfLifeMultiplay::ResetCurrentVIP),
	HOOK_SYMBOLDEF(0x01D8DDB0, "_ZN18CHalfLifeMultiplay12BalanceTeamsEv", CHalfLifeMultiplay::BalanceTeams),
	//HOOK_SYMBOLDEF(0x01D8DC40, "_ZN18CHalfLifeMultiplay14SwapAllPlayersEv", CHalfLifeMultiplay::SwapAllPlayers),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D8BFE0, "_ZN18CHalfLifeMultiplay16UpdateTeamScoresEv", CHalfLifeMultiplay::UpdateTeamScores),	// NOXREF
	HOOK_SYMBOLDEF(0x01D92DB0, "_ZN18CHalfLifeMultiplay11DisplayMapsEP11CBasePlayeri", CHalfLifeMultiplay::DisplayMaps),
	//HOOK_SYMBOLDEF(0x01D92BF0, "_ZN18CHalfLifeMultiplay16ResetAllMapVotesEv", CHalfLifeMultiplay::ResetAllMapVotes),	// NOXREF
	HOOK_SYMBOLDEF(0x01D93080, "_ZN18CHalfLifeMultiplay14ProcessMapVoteEP11CBasePlayeri", CHalfLifeMultiplay::ProcessMapVote),
	HOOK_SYMBOLDEF(0x01D8EAC0, "_ZN18CHalfLifeMultiplay14IsThereABomberEv", CHalfLifeMultiplay::IsThereABomber),
	HOOK_SYMBOLDEF(0x01D8EB50, "_ZN18CHalfLifeMultiplay12IsThereABombEv", CHalfLifeMultiplay::IsThereABomb),
	//HOOK_SYMBOLDEF(0x0, "_ZN18CHalfLifeMultiplay14IsMatchStartedEv", CHalfLifeMultiplay::IsMatchStarted),	// NOXREF
	HOOK_SYMBOLDEF(0x01D93530, "_ZN18CHalfLifeMultiplay16SendMOTDToClientEP7edict_s", CHalfLifeMultiplay::SendMOTDToClient),
	// non-class func
	//HOOK_DEF(0x0, IsBotSpeaking),	// NOXREF
	HOOK_SYMBOLDEF(0x01D8B010, "_Z13SV_Continue_fv", SV_Continue_f),
	HOOK_SYMBOLDEF(0x01D8B0C0, "_Z17SV_Tutor_Toggle_fv", SV_Tutor_Toggle_f),
	HOOK_SYMBOLDEF(0x01D8B110, "_Z19SV_Career_Restart_fv", SV_Career_Restart_f),
	HOOK_SYMBOLDEF(0x01D8B1F0, "_Z20SV_Career_EndRound_fv", SV_Career_EndRound_f),
	HOOK_SYMBOLDEF(0x01D8B350, "_Z18SV_CareerAddTask_fv", SV_CareerAddTask_f),
	HOOK_SYMBOLDEF(0x01D8B400, "_Z21SV_CareerMatchLimit_fv", SV_CareerMatchLimit_f),
	HOOK_SYMBOLDEF(0x01D8B6E0, "_Z9BroadcastPKc", Broadcast),
	HOOK_SYMBOLDEF(0x01D8B780, "_Z7GetTeami", GetTeam),
	//HOOK_SYMBOLDEF(0x01D8B7B0, "_Z15EndRoundMessagePKci", EndRoundMessage),
	//HOOK_SYMBOLDEF(0x01D8BD80, "_ZL18ReadMultiplayCvarsP18CHalfLifeMultiplay", ReadMultiplayCvars),
	//HOOK_SYMBOLDEF(0x01D92670, "_Z15DestroyMapCycleP10mapcycle_s", DestroyMapCycle),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D926B0, "_Z15MP_COM_GetTokenv", MP_COM_GetToken),
	//HOOK_SYMBOLDEF(0x01D926C0, "_Z12MP_COM_ParsePc", MP_COM_Parse),
	//HOOK_SYMBOLDEF(0x01D927A0, "_Z19MP_COM_TokenWaitingPc", MP_COM_TokenWaiting),	// NOXREF
	HOOK_SYMBOLDEF(0x01D927F0, "_Z18ReloadMapCycleFilePcP10mapcycle_s", ReloadMapCycleFile),
	//HOOK_SYMBOLDEF(0x01D92AB0, "_Z12CountPlayersv", CountPlayers),	// NOXREF
	HOOK_SYMBOLDEF(0x01D92AF0, "_Z20ExtractCommandStringPcS_", ExtractCommandString),
	HOOK_SYMBOLDEF(0x01D92D10, "_Z11GetMapCountv", GetMapCount),
//CCStrikeGameMgrHelper
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8B630, "_ZN21CCStrikeGameMgrHelper19CanPlayerHearPlayerEP11CBasePlayerS1_", CCStrikeGameMgrHelper::CanPlayerHearPlayer),
//CMapInfo
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8B5E0, "_ZN21CCStrikeGameMgrHelper19CanPlayerHearPlayerEP11CBasePlayerS1_", CMapInfo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D8B540, "_ZN21CCStrikeGameMgrHelper19CanPlayerHearPlayerEP11CBasePlayerS1_", CMapInfo::KeyValue),
// linked objects
	HOOK_DEF(0x01D8B4F0, info_map_parameters),

#endif // Multiplay_GameRules_Region

#ifndef Training_Gamerules_Region

//CHalfLifeTraining
	// virtual func
	//HOOK_SYMBOLDEF(0x01DBBE50, "_ZN17CHalfLifeTrainingC2Ev", CHalfLifeTraining::CHalfLifeTraining)
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBBE70, "_ZN17CHalfLifeTraining13IsMultiplayerEv", CHalfLifeTraining::IsMultiplayer),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBBE90, "_ZN17CHalfLifeTraining12IsDeathmatchEv", CHalfLifeTraining::IsDeathmatch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBBEA0, "_ZN17CHalfLifeTraining7InitHUDEP11CBasePlayer", CHalfLifeTraining::InitHUD),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC3E0, "_ZN17CHalfLifeTraining11PlayerSpawnEP11CBasePlayer", CHalfLifeTraining::PlayerSpawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC010, "_ZN17CHalfLifeTraining11PlayerThinkEP11CBasePlayer", CHalfLifeTraining::PlayerThink),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC4C0, "_ZN17CHalfLifeTraining17FPlayerCanRespawnEP11CBasePlayer", CHalfLifeTraining::FPlayerCanRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBBEE0, "_ZN17CHalfLifeTraining18GetPlayerSpawnSpotEP11CBasePlayer", CHalfLifeTraining::GetPlayerSpawnSpot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC4E0, "_ZN17CHalfLifeTraining12PlayerKilledEP11CBasePlayerP9entvars_sS3_", CHalfLifeTraining::PlayerKilled),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC4B0, "_ZN17CHalfLifeTraining17ItemShouldRespawnEP5CItem", CHalfLifeTraining::ItemShouldRespawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBBE80, "_ZN17CHalfLifeTraining18CheckMapConditionsEv", CHalfLifeTraining::CheckMapConditions),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC510, "_ZN17CHalfLifeTraining18CheckWinConditionsEv", CHalfLifeTraining::CheckWinConditions),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DBBEB0, "_ZN17CHalfLifeTraining11HostageDiedEv", CHalfLifeTraining::HostageDied),
	HOOK_SYMBOLDEF(0x01DBC4D0, "_ZN17CHalfLifeTraining12PlayerCanBuyEP11CBasePlayer", CHalfLifeTraining::PlayerCanBuy),
//CBaseGrenCatch
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC8B0, "_ZN14CBaseGrenCatch5SpawnEv", CBaseGrenCatch::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBCC00, "_ZN14CBaseGrenCatch8KeyValueEP14KeyValueData_s", CBaseGrenCatch::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC7F0, "_ZN14CBaseGrenCatch4SaveER5CSave", CBaseGrenCatch::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC820, "_ZN14CBaseGrenCatch7RestoreER8CRestore", CBaseGrenCatch::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC8A0, "_ZN14CBaseGrenCatch10ObjectCapsEv", CBaseGrenCatch::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC970, "_ZN14CBaseGrenCatch5ThinkEv", CBaseGrenCatch::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBC930, "_ZN14CBaseGrenCatch5TouchEP11CBaseEntity", CBaseGrenCatch::Touch),
//CFuncWeaponCheck
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBCCE0, "_ZN16CFuncWeaponCheck5SpawnEv", CFuncWeaponCheck::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBCF70, "_ZN16CFuncWeaponCheck8KeyValueEP14KeyValueData_s", CFuncWeaponCheck::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBCD50, "_ZN16CFuncWeaponCheck4SaveER5CSave", CFuncWeaponCheck::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBCD80, "_ZN16CFuncWeaponCheck7RestoreER8CRestore", CFuncWeaponCheck::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DBCE00, "_ZN16CFuncWeaponCheck5TouchEP11CBaseEntity", CFuncWeaponCheck::Touch),
// linked objects
	HOOK_DEF(0x01DBC850, func_grencatch),
	HOOK_DEF(0x01DBCDB0, func_weaponcheck),

#endif // Training_Gamerules_Region

#ifndef CareerTasks_Region

//CCareerTask
	//HOOK_SYMBOLDEF(0x01DDCBD0, "_ZN11CCareerTaskC2EPKc13GameEventTypeS1_ibbib", CCareerTask::CCareerTask),
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DDD150, "_ZN11CCareerTask7OnEventE13GameEventTypeP11CBasePlayerS2_", CCareerTask::OnEvent),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DDCCD0, "_ZN11CCareerTask5ResetEv", CCareerTask::Reset),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DDDDE0, "_ZNK11CCareerTask26IsTaskCompletableThisRoundEv", CCareerTask::IsTaskCompletableThisRound),		// DEFAULT
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DDCB80, "_ZN11CCareerTask7NewTaskEPKc13GameEventTypeS1_ibbib", CCareerTask::NewTask),
	HOOK_SYMBOLDEF(0x01DDCDB0, "_ZN11CCareerTask12OnWeaponKillEiibbP11CBasePlayerS1_", CCareerTask::OnWeaponKill),
	HOOK_SYMBOLDEF(0x01DDD000, "_ZN11CCareerTask14OnWeaponInjuryEiibP11CBasePlayer", CCareerTask::OnWeaponInjury),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CCareerTask10IsCompleteEv", CCareerTask::IsComplete),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CCareerTask11GetTaskNameEv", CCareerTask::GetTaskName),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CCareerTask11GetWeaponIdEv", CCareerTask::GetWeaponId),
	//HOOK_SYMBOLDEF(0x0, "_ZN11CCareerTask16GetWeaponClassIdEv", CCareerTask::GetWeaponClassId),
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CCareerTask10IsValidForEP11CBasePlayer ", CCareerTask::IsValidFor),
	//HOOK_SYMBOLDEF(0x01DDCD50, "_ZN11CCareerTask23SendPartialNotificationEv", CCareerTask::SendPartialNotification),	// NOXREF
//CCareerTaskManager
	//HOOK_SYMBOLDEF(0x01DDD7C0, "_ZN18CCareerTaskManagerC2Ev", CCareerTaskManager::CCareerTaskManager),
	//HOOK_SYMBOLDEF(0x01DDD750, "_ZN18CCareerTaskManager6CreateEv", CCareerTaskManager::Create),
	HOOK_SYMBOLDEF(0x01DDD800, "_ZN18CCareerTaskManager5ResetEb", CCareerTaskManager::Reset),
	HOOK_SYMBOLDEF(0x01DDD8D0, "_ZN18CCareerTaskManager7AddTaskEPKcS1_ibbb", CCareerTaskManager::AddTask),
	HOOK_SYMBOLDEF(0x01DDDA00, "_ZN18CCareerTaskManager11HandleEventE13GameEventTypeP11CBasePlayerS2_", CCareerTaskManager::HandleEvent),
	HOOK_SYMBOLDEF(0x01DDDAB0, "_ZN18CCareerTaskManager15HandleEnemyKillEbPKcbbP11CBasePlayerS3_", CCareerTaskManager::HandleEnemyKill),
	//HOOK_SYMBOLDEF(0x01DDDA60, "_ZN18CCareerTaskManager16HandleWeaponKillEiibbP11CBasePlayerS1_", CCareerTaskManager::HandleWeaponKill),	// NOXREF
	HOOK_SYMBOLDEF(0x01DDDC30, "_ZN18CCareerTaskManager11HandleDeathEiP11CBasePlayer", CCareerTaskManager::HandleDeath),
	//HOOK_SYMBOLDEF(0x01DDDB80, "_ZN18CCareerTaskManager18HandleWeaponInjuryEiibP11CBasePlayer", CCareerTaskManager::HandleWeaponInjury),	// NOXREF
	HOOK_SYMBOLDEF(0x01DDDBC0, "_ZN18CCareerTaskManager17HandleEnemyInjuryEPKcbP11CBasePlayer", CCareerTaskManager::HandleEnemyInjury),
	HOOK_SYMBOLDEF(0x01DDDCD0, "_ZN18CCareerTaskManager19AreAllTasksCompleteEv", CCareerTaskManager::AreAllTasksComplete),
	HOOK_SYMBOLDEF(0x01DDDD00, "_ZN18CCareerTaskManager20GetNumRemainingTasksEv", CCareerTaskManager::GetNumRemainingTasks),
	HOOK_SYMBOLDEF(0x01DDDD30, "_ZN18CCareerTaskManager19GetRoundElapsedTimeEv", CCareerTaskManager::GetRoundElapsedTime),
	//HOOK_SYMBOLDEF(0x0, "_ZN18CCareerTaskManager11GetTaskTimeEv", CCareerTaskManager::GetTaskTime),
	//HOOK_SYMBOLDEF(0x01DDD8B0, "_ZN18CCareerTaskManager19SetFinishedTaskTimeEi", CCareerTaskManager::SetFinishedTaskTime),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN18CCareerTaskManager19GetFinishedTaskTimeEv", CCareerTaskManager::GetFinishedTaskTime),
	//HOOK_SYMBOLDEF(0x0, "_ZN18CCareerTaskManager20GetFinishedTaskRoundEv", CCareerTaskManager::GetFinishedTaskRound),
	//HOOK_SYMBOLDEF(0x0, "_ZN18CCareerTaskManager8GetTasksEv", CCareerTaskManager::GetTasks),
	HOOK_SYMBOLDEF(0x01DDDD40, "_ZN18CCareerTaskManager20LatchRoundEndMessageEv", CCareerTaskManager::LatchRoundEndMessage),
	HOOK_SYMBOLDEF(0x01DDDD50, "_ZN18CCareerTaskManager22UnlatchRoundEndMessageEv", CCareerTaskManager::UnlatchRoundEndMessage),
//CPreventDefuseTask
	// virtual func
	//HOOK_SYMBOLDEF(0x01DDCA60, "_ZN18CPreventDefuseTaskC2EPKc13GameEventTypeS1_ibbib", CPreventDefuseTask::CPreventDefuseTask),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DDCB30, "_ZN18CPreventDefuseTask7OnEventE13GameEventTypeP11CBasePlayerS2_", CPreventDefuseTask::OnEvent),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DDCAB0, "_ZN18CPreventDefuseTask5ResetEv", CPreventDefuseTask::Reset),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DDDDF0, "_ZNK18CPreventDefuseTask26IsTaskCompletableThisRoundEv", CPreventDefuseTask::IsTaskCompletableThisRound),		// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DDCA00, "_ZN18CPreventDefuseTask7NewTaskEPKc13GameEventTypeS1_ibbib", CPreventDefuseTask::NewTask),

#endif // CareerTasks_Region

#ifndef Weapons_Region

//Weapons base
	//HOOK_SYMBOLDEF(0x01DCCD60, "_Z12MaxAmmoCarryi", MaxAmmoCarry),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCCE60, "_Z16ClearMultiDamagev", ClearMultiDamage),
	HOOK_SYMBOLDEF(0x01DCCE80, "_Z16ApplyMultiDamageP9entvars_sS0_", ApplyMultiDamage),
	HOOK_SYMBOLDEF(0x01DCCEB0, "_Z14AddMultiDamageP9entvars_sP11CBaseEntityfi", AddMultiDamage),
	HOOK_SYMBOLDEF(0x01DCCF20, "_Z10SpawnBlood6Vectorif", SpawnBlood),
	//HOOK_SYMBOLDEF(0x01DCCF50, "_Z11DamageDecalP11CBaseEntityi", DamageDecal),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DCCF80, "_Z12DecalGunshotP11TraceResultibP9entvars_sb", DecalGunshot),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCCF90, "_Z10EjectBrassRK6VectorS1_S1_fiii", EjectBrass),
	//HOOK_SYMBOLDEF(0x01DCD080, "_Z11EjectBrass2RK6VectorS1_fiiP9entvars_s", EjectBrass2),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DCD120, "_Z25AddAmmoNameToAmmoRegistryPKc", AddAmmoNameToAmmoRegistry),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCD180, "_Z24UTIL_PrecacheOtherWeaponPKc", UTIL_PrecacheOtherWeapon),
	//HOOK_SYMBOLDEF(0x01DCD310, "_Z25UTIL_PrecacheOtherWeapon2PKc", UTIL_PrecacheOtherWeapon2),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCD4A0, "_Z10W_Precachev", W_Precache),
	//HOOK_SYMBOLDEF(0x01DCE600, "_Z9CanAttackffi", CanAttack),	// NOXREF
//CBasePlayerItem
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DCD860, "_ZN15CBasePlayerItem4SaveER5CSave", CBasePlayerItem::Save),	// NOXREF
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DCD890, "_ZN15CBasePlayerItem7RestoreER8CRestore", CBasePlayerItem::Restore),	// NOXREF
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCD960, "_ZN15CBasePlayerItem21SetObjectCollisionBoxEv", CBasePlayerItem::SetObjectCollisionBox),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCDC80, "_ZN15CBasePlayerItem7RespawnEv", CBasePlayerItem::Respawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DCEC60, "_ZN15CBasePlayerItem11AddToPlayerEP11CBasePlayer", CBasePlayerItem::AddToPlayer),	// NOXREF
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN15CBasePlayerItem12AddDuplicateEPS_", CBasePlayerItem::AddDuplicate),	// NOXREF
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN15CBasePlayerItem11GetItemInfoEP8ItemInfo", CBasePlayerItem::GetItemInfo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN15CBasePlayerItem9CanDeployEv", CBasePlayerItem::CanDeploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D01FF0, "_ZN15CBasePlayerItem7CanDropEv", CBasePlayerItem::CanDrop),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem6DeployEv", CBasePlayerItem::Deploy),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem8IsWeaponEv", CBasePlayerItem::IsWeapon),
	//HOOK_SYMBOLDEF(0x01D02000, "_ZN15CBasePlayerItem10CanHolsterEv", CBasePlayerItem::CanHolster),
	//HOOK_SYMBOLDEF(0x01DCED10, "_ZN15CBasePlayerItem7HolsterEi", CBasePlayerItem::Holster),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem14UpdateItemInfoEv", CBasePlayerItem::UpdateItemInfo),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D02010, "_ZN15CBasePlayerItem12ItemPreFrameEv", CBasePlayerItem::ItemPreFrame),	// NOXREF PURE
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem13ItemPostFrameEv", CBasePlayerItem::ItemPostFrame),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCECB0, "_ZN15CBasePlayerItem4DropEv", CBasePlayerItem::Drop),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCECE0, "_ZN15CBasePlayerItem4KillEv", CBasePlayerItem::Kill),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCED40, "_ZN15CBasePlayerItem14AttachToPlayerEP11CBasePlayer", CBasePlayerItem::AttachToPlayer),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem16PrimaryAmmoIndexEv", CBasePlayerItem::PrimaryAmmoIndex),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem18SecondaryAmmoIndexEv", CBasePlayerItem::SecondaryAmmoIndex),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem16UpdateClientDataEP11CBasePlayer", CBasePlayerItem::UpdateClientData),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem12GetWeaponPtrEv", CBasePlayerItem::GetWeaponPtr),
	//HOOK_SYMBOLDEF(0x01D861A0, "_ZN15CBasePlayerItem11GetMaxSpeedEv", CBasePlayerItem::GetMaxSpeed),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem9iItemSlotEv", CBasePlayerItem::iItemSlot),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DCEC40, "_ZN15CBasePlayerItem11DestroyItemEv", CBasePlayerItem::DestroyItem),
	HOOK_SYMBOLDEF(0x01DCDD50, "_ZN15CBasePlayerItem12DefaultTouchEP11CBaseEntity", CBasePlayerItem::DefaultTouch),
	HOOK_SYMBOLDEF(0x01DCDAA0, "_ZN15CBasePlayerItem9FallThinkEv", CBasePlayerItem::FallThink),
	HOOK_SYMBOLDEF(0x01DCDB30, "_ZN15CBasePlayerItem11MaterializeEv", CBasePlayerItem::Materialize),
	HOOK_SYMBOLDEF(0x01DCDC10, "_ZN15CBasePlayerItem20AttemptToMaterializeEv", CBasePlayerItem::AttemptToMaterialize),
	HOOK_SYMBOLDEF(0x01DCDA00, "_ZN15CBasePlayerItem8FallInitEv", CBasePlayerItem::FallInit),
	HOOK_SYMBOLDEF(0x01DCDC50, "_ZN15CBasePlayerItem12CheckRespawnEv", CBasePlayerItem::CheckRespawn),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem8pszAmmo1Ev", CBasePlayerItem::pszAmmo1),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem9iMaxAmmo1Ev", CBasePlayerItem::iMaxAmmo1),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem8pszAmmo2Ev", CBasePlayerItem::pszAmmo2),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem9iMaxAmmo2Ev", CBasePlayerItem::iMaxAmmo2),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem7pszNameEv", CBasePlayerItem::pszName),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem8iMaxClipEv", CBasePlayerItem::iMaxClip),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem7iWeightEv", CBasePlayerItem::iWeight),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CBasePlayerItem6iFlagsEv", CBasePlayerItem::iFlags),
//CBasePlayerWeapon
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCD8C0, "_ZN17CBasePlayerWeapon4SaveER5CSave", CBasePlayerWeapon::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCD910, "_ZN17CBasePlayerWeapon7RestoreER8CRestore", CBasePlayerWeapon::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCEDE0, "_ZN17CBasePlayerWeapon11AddToPlayerEP11CBasePlayer", CBasePlayerWeapon::AddToPlayer),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCEDC0, "_ZN17CBasePlayerWeapon12AddDuplicateEP15CBasePlayerItem", CBasePlayerWeapon::AddDuplicate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF1A0, "_ZN17CBasePlayerWeapon9CanDeployEv", CBasePlayerWeapon::CanDeploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02050, "_ZN17CBasePlayerWeapon8IsWeaponEv", CBasePlayerWeapon::IsWeapon),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF570, "_ZN17CBasePlayerWeapon7HolsterEi", CBasePlayerWeapon::Holster),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02030, "_ZN17CBasePlayerWeapon14UpdateItemInfoEv", CBasePlayerWeapon::UpdateItemInfo),	// NOXREF PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCE6A0, "_ZN17CBasePlayerWeapon13ItemPostFrameEv", CBasePlayerWeapon::ItemPostFrame),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF550, "_ZN17CBasePlayerWeapon16PrimaryAmmoIndexEv", CBasePlayerWeapon::PrimaryAmmoIndex),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF560, "_ZN17CBasePlayerWeapon18SecondaryAmmoIndexEv", CBasePlayerWeapon::SecondaryAmmoIndex),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCEEB0, "_ZN17CBasePlayerWeapon16UpdateClientDataEP11CBasePlayer", CBasePlayerWeapon::UpdateClientData),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02060, "_ZN17CBasePlayerWeapon12GetWeaponPtrEv", CBasePlayerWeapon::GetWeaponPtr),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF7E0, "_ZN17CBasePlayerWeapon11ExtractAmmoEPS_", CBasePlayerWeapon::ExtractAmmo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF8A0, "_ZN17CBasePlayerWeapon15ExtractClipAmmoEPS_", CBasePlayerWeapon::ExtractClipAmmo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02020, "_ZN17CBasePlayerWeapon9AddWeaponEv", CBasePlayerWeapon::AddWeapon),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF4C0, "_ZN17CBasePlayerWeapon14PlayEmptySoundEv", CBasePlayerWeapon::PlayEmptySound),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF540, "_ZN17CBasePlayerWeapon15ResetEmptySoundEv", CBasePlayerWeapon::ResetEmptySound),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCEFB0, "_ZN17CBasePlayerWeapon14SendWeaponAnimEii", CBasePlayerWeapon::SendWeaponAnim),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF150, "_ZN17CBasePlayerWeapon9IsUseableEv", CBasePlayerWeapon::IsUseable),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN17CBasePlayerWeapon13PrimaryAttackEv", CBasePlayerWeapon::PrimaryAttack),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D03A50, "_ZN17CBasePlayerWeapon15SecondaryAttackEv", CBasePlayerWeapon::SecondaryAttack),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D03A60, "_ZN17CBasePlayerWeapon6ReloadEv", CBasePlayerWeapon::Reload),	// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D861B0, "_ZN17CBasePlayerWeapon10WeaponIdleEv", CBasePlayerWeapon::WeaponIdle),	// PURE
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF8F0, "_ZN17CBasePlayerWeapon12RetireWeaponEv", CBasePlayerWeapon::RetireWeapon),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02040, "_ZN17CBasePlayerWeapon16ShouldWeaponIdleEv", CBasePlayerWeapon::ShouldWeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D861C0, "_ZN17CBasePlayerWeapon12UseDecrementEv", CBasePlayerWeapon::UseDecrement),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DCF030, "_ZN17CBasePlayerWeapon14AddPrimaryAmmoEiPcii", CBasePlayerWeapon::AddPrimaryAmmo),
	//HOOK_SYMBOLDEF(0x01DCF0F0, "_ZN17CBasePlayerWeapon16AddSecondaryAmmoEiPci", CBasePlayerWeapon::AddSecondaryAmmo),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCF1B0, "_ZN17CBasePlayerWeapon13DefaultDeployEPcS0_iS0_i", CBasePlayerWeapon::DefaultDeploy),
	HOOK_SYMBOLDEF(0x01DCF430, "_ZN17CBasePlayerWeapon13DefaultReloadEiif", CBasePlayerWeapon::DefaultReload),
	HOOK_SYMBOLDEF(0x01DCE380, "_ZN17CBasePlayerWeapon13FireRemainingERiRfi", CBasePlayerWeapon::FireRemaining),
	//HOOK_SYMBOLDEF(0x01DCE260, "_ZN17CBasePlayerWeapon8KickBackEffffffi", CBasePlayerWeapon::KickBack),
	HOOK_SYMBOLDEF(0x01DCDEA0, "_ZN17CBasePlayerWeapon14EjectBrassLateEv", CBasePlayerWeapon::EjectBrassLate),
	//HOOK_SYMBOLDEF(0x0, "_ZN17CBasePlayerWeapon8MakeBeamEv", CBasePlayerWeapon::MakeBeam),
	//HOOK_SYMBOLDEF(0x0, "_ZN17CBasePlayerWeapon10BeamUpdateEv", CBasePlayerWeapon::BeamUpdate),
	HOOK_SYMBOLDEF(0x01DCF2D0, "_ZN17CBasePlayerWeapon11ReloadSoundEv", CBasePlayerWeapon::ReloadSound),
	HOOK_SYMBOLDEF(0x01DCF930, "_ZN17CBasePlayerWeapon18GetNextAttackDelayEf", CBasePlayerWeapon::GetNextAttackDelay),
	//HOOK_SYMBOLDEF(0x01DCE630, "_ZN17CBasePlayerWeapon18HasSecondaryAttackEv", CBasePlayerWeapon::HasSecondaryAttack),	// NOXREF
	HOOK_SYMBOLDEF(0x01D32670, "_ZN17CBasePlayerWeapon8IsPistolEv", CBasePlayerWeapon::IsPistol),
	HOOK_SYMBOLDEF(0x01DCDE10, "_ZN17CBasePlayerWeapon19SetPlayerShieldAnimEv", CBasePlayerWeapon::SetPlayerShieldAnim),
	HOOK_SYMBOLDEF(0x01DCDE60, "_ZN17CBasePlayerWeapon21ResetPlayerShieldAnimEv", CBasePlayerWeapon::ResetPlayerShieldAnim),
	HOOK_SYMBOLDEF(0x01DCE140, "_ZN17CBasePlayerWeapon19ShieldSecondaryFireEii", CBasePlayerWeapon::ShieldSecondaryFire),
//CBasePlayerAmmo
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF5A0, "_ZN15CBasePlayerAmmo5SpawnEv", CBasePlayerAmmo::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN15CBasePlayerAmmo7AddAmmoEP11CBaseEntity", CBasePlayerAmmo::AddAmmo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF650, "_ZN15CBasePlayerAmmo7RespawnEv", CBasePlayerAmmo::Respawn),
	// non-virtual func
//CBasePlayerAmmo
	HOOK_SYMBOLDEF(0x01DCF6C0, "_ZN15CBasePlayerAmmo11MaterializeEv", CBasePlayerAmmo::Materialize),
	HOOK_SYMBOLDEF(0x01DCF730, "_ZN15CBasePlayerAmmo12DefaultTouchEP11CBaseEntity", CBasePlayerAmmo::DefaultTouch),
//C9MMAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59550, "_ZN8C9MMAmmo5SpawnEv", C9MMAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59580, "_ZN8C9MMAmmo8PrecacheEv", C9MMAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D595A0, "_ZN8C9MMAmmo7AddAmmoEP11CBaseEntity", C9MMAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D59500, ammo_9mm),
//CBuckShotAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59640, "_ZN13CBuckShotAmmo5SpawnEv", CBuckShotAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59670, "_ZN13CBuckShotAmmo8PrecacheEv", CBuckShotAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59690, "_ZN13CBuckShotAmmo7AddAmmoEP11CBaseEntity", CBuckShotAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D595F0, ammo_buckshot),
//C556NatoAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59730, "_ZN12C556NatoAmmo5SpawnEv", C556NatoAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59760, "_ZN12C556NatoAmmo8PrecacheEv", C556NatoAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59780, "_ZN12C556NatoAmmo7AddAmmoEP11CBaseEntity", C556NatoAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D596E0, ammo_556nato),
//C556NatoBoxAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59820, "_ZN15C556NatoBoxAmmo5SpawnEv", C556NatoBoxAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59850, "_ZN15C556NatoBoxAmmo8PrecacheEv", C556NatoBoxAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59870, "_ZN15C556NatoBoxAmmo7AddAmmoEP11CBaseEntity", C556NatoBoxAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D597D0, ammo_556natobox),
//C762NatoAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59920, "_ZN12C762NatoAmmo5SpawnEv", C762NatoAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59950, "_ZN12C762NatoAmmo8PrecacheEv", C762NatoAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59970, "_ZN12C762NatoAmmo7AddAmmoEP11CBaseEntity", C762NatoAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D598D0, ammo_762nato),
//C45ACPAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59A10, "_ZN10C45ACPAmmo5SpawnEv", C45ACPAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59A40, "_ZN10C45ACPAmmo8PrecacheEv", C45ACPAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59A60, "_ZN10C45ACPAmmo7AddAmmoEP11CBaseEntity", C45ACPAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D599C0, ammo_45acp),
//C50AEAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59B00, "_ZN9C50AEAmmo5SpawnEv", C50AEAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59B30, "_ZN9C50AEAmmo8PrecacheEv", C50AEAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59B50, "_ZN9C50AEAmmo7AddAmmoEP11CBaseEntity", C50AEAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D59AB0, ammo_50ae),
//C338MagnumAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59BF0, "_ZN14C338MagnumAmmo5SpawnEv", C338MagnumAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59C20, "_ZN14C338MagnumAmmo8PrecacheEv", C338MagnumAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59C40, "_ZN14C338MagnumAmmo7AddAmmoEP11CBaseEntity", C338MagnumAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D59BA0, ammo_338magnum),
//C57MMAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59CE0, "_ZN9C57MMAmmo5SpawnEv", C57MMAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59D10, "_ZN9C57MMAmmo8PrecacheEv", C57MMAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59D30, "_ZN9C57MMAmmo7AddAmmoEP11CBaseEntity", C57MMAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D59C90, ammo_57mm),
//C357SIGAmmo
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59DD0, "_ZN11C357SIGAmmo5SpawnEv", C357SIGAmmo::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D59E00, "_ZN11C357SIGAmmo8PrecacheEv", C357SIGAmmo::Precache),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D59E20, "_ZN11C357SIGAmmo7AddAmmoEP11CBaseEntity", C357SIGAmmo::AddAmmo),
	// non-virtual func
	HOOK_DEF(0x01D59D80, ammo_357sig),
//CWeaponBox
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCFD80, "_ZN10CWeaponBox5SpawnEv", CWeaponBox::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCFA40, "_ZN10CWeaponBox8PrecacheEv", CWeaponBox::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCFA50, "_ZN10CWeaponBox8KeyValueEP14KeyValueData_s", CWeaponBox::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCF9E0, "_ZN10CWeaponBox4SaveER5CSave", CWeaponBox::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCFA10, "_ZN10CWeaponBox7RestoreER8CRestore", CWeaponBox::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD0970, "_ZN10CWeaponBox21SetObjectCollisionBoxEv", CWeaponBox::SetObjectCollisionBox),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DCFE30, "_ZN10CWeaponBox5TouchEP11CBaseEntity", CWeaponBox::Touch),
	// non-virtual func
	HOOK_DEF(0x01DCF990, weaponbox),
	//HOOK_SYMBOLDEF(0x01DD0930, "_ZN10CWeaponBox7IsEmptyEv", CWeaponBox::IsEmpty),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD07C0, "_ZN10CWeaponBox8GiveAmmoEiPciPi", CWeaponBox::GiveAmmo),
	HOOK_SYMBOLDEF(0x01DCFDE0, "_ZN10CWeaponBox4KillEv", CWeaponBox::Kill),
	HOOK_SYMBOLDEF(0x01DCFBF0, "_ZN10CWeaponBox9BombThinkEv", CWeaponBox::BombThink), //export func
	//HOOK_SYMBOLDEF(0x01DD08A0, "_ZN10CWeaponBox9HasWeaponEP15CBasePlayerItem", CWeaponBox::HasWeapon),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD0500, "_ZN10CWeaponBox10PackWeaponEP15CBasePlayerItem", CWeaponBox::PackWeapon),
	HOOK_SYMBOLDEF(0x01DD0670, "_ZN10CWeaponBox8PackAmmoEii", CWeaponBox::PackAmmo),
//CUSP
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F8B0, "_ZN4CUSP5SpawnEv", CUSP::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F910, "_ZN4CUSP8PrecacheEv", CUSP::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F9D0, "_ZN4CUSP11GetItemInfoEP8ItemInfo", CUSP::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0FA40, "_ZN4CUSP6DeployEv", CUSP::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D101A0, "_ZN4CUSP11GetMaxSpeedEv", CUSP::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D10190, "_ZN4CUSP9iItemSlotEv", CUSP::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0FB20, "_ZN4CUSP15SecondaryAttackEv", CUSP::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0FBE0, "_ZN4CUSP13PrimaryAttackEv", CUSP::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10060, "_ZN4CUSP6ReloadEv", CUSP::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D100C0, "_ZN4CUSP10WeaponIdleEv", CUSP::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D101B0, "_ZN4CUSP12UseDecrementEv", CUSP::UseDecrement),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D101C0, "_ZN4CUSP8IsPistolEv", CUSP::IsPistol),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0F860, weapon_usp),
	HOOK_SYMBOLDEF(0x01D0FD50, "_ZN4CUSP7USPFireEffi", CUSP::USPFire),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CUSP8MakeBeamEv", CUSP::MakeBeam),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN4CUSP10BeamUpdateEv", CUSP::BeamUpdate),	// NOXREF
//CMP5N
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B750, "_ZN5CMP5N5SpawnEv", CMP5N::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B7A0, "_ZN5CMP5N8PrecacheEv", CMP5N::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B820, "_ZN5CMP5N11GetItemInfoEP8ItemInfo", CMP5N::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B890, "_ZN5CMP5N6DeployEv", CMP5N::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BD50, "_ZN5CMP5N11GetMaxSpeedEv", CMP5N::GetMaxSpeed),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BD40, "_ZN5CMP5N9iItemSlotEv", CMP5N::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B8E0, "_ZN5CMP5N13PrimaryAttackEv", CMP5N::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BC80, "_ZN5CMP5N6ReloadEv", CMP5N::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BCD0, "_ZN5CMP5N10WeaponIdleEv", CMP5N::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BD60, "_ZN5CMP5N12UseDecrementEv", CMP5N::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0B700, weapon_mp5navy),
	HOOK_SYMBOLDEF(0x01D0B920, "_ZN5CMP5N8MP5NFireEffi", CMP5N::MP5NFire),
//CSG552
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DAA0, "_ZN6CSG5525SpawnEv", CSG552::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DAF0, "_ZN6CSG5528PrecacheEv", CSG552::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DB70, "_ZN6CSG55211GetItemInfoEP8ItemInfo", CSG552::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DBE0, "_ZN6CSG5526DeployEv", CSG552::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E1C0, "_ZN6CSG55211GetMaxSpeedEv", CSG552::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E1E0, "_ZN6CSG5529iItemSlotEv", CSG552::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DC30, "_ZN6CSG55215SecondaryAttackEv", CSG552::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DCA0, "_ZN6CSG55213PrimaryAttackEv", CSG552::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E0D0, "_ZN6CSG5526ReloadEv", CSG552::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E150, "_ZN6CSG55210WeaponIdleEv", CSG552::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E1F0, "_ZN6CSG55212UseDecrementEv", CSG552::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0DA50, weapon_sg552),
	HOOK_SYMBOLDEF(0x01D0DD50, "_ZN6CSG5529SG552FireEffi", CSG552::SG552Fire),
//CAK47
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D014F0, "_ZN5CAK475SpawnEv", CAK47::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D01540, "_ZN5CAK478PrecacheEv", CAK47::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D015C0, "_ZN5CAK4711GetItemInfoEP8ItemInfo", CAK47::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D01630, "_ZN5CAK476DeployEv", CAK47::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02080, "_ZN5CAK4711GetMaxSpeedEv", CAK47::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02070, "_ZN5CAK479iItemSlotEv", CAK47::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D01680, "_ZN5CAK4715SecondaryAttackEv", CAK47::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D01690, "_ZN5CAK4713PrimaryAttackEv", CAK47::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D01AB0, "_ZN5CAK476ReloadEv", CAK47::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D01B00, "_ZN5CAK4710WeaponIdleEv", CAK47::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02090, "_ZN5CAK4712UseDecrementEv", CAK47::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D014A0, weapon_ak47),
	HOOK_SYMBOLDEF(0x01D01730, "_ZN5CAK478AK47FireEffi", CAK47::AK47Fire),
//CAUG
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D020F0, "_ZN4CAUG5SpawnEv", CAUG::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02140, "_ZN4CAUG8PrecacheEv", CAUG::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D021D0, "_ZN4CAUG11GetItemInfoEP8ItemInfo", CAUG::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02240, "_ZN4CAUG6DeployEv", CAUG::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02820, "_ZN4CAUG11GetMaxSpeedEv", CAUG::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02810, "_ZN4CAUG9iItemSlotEv", CAUG::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02290, "_ZN4CAUG15SecondaryAttackEv", CAUG::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02300, "_ZN4CAUG13PrimaryAttackEv", CAUG::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02730, "_ZN4CAUG6ReloadEv", CAUG::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D027A0, "_ZN4CAUG10WeaponIdleEv", CAUG::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02830, "_ZN4CAUG12UseDecrementEv", CAUG::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D020A0, weapon_aug),
	HOOK_SYMBOLDEF(0x01D023B0, "_ZN4CAUG7AUGFireEffi", CAUG::AUGFire),
//CAWP
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02890, "_ZN4CAWP5SpawnEv", CAWP::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D028D0, "_ZN4CAWP8PrecacheEv", CAWP::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02980, "_ZN4CAWP11GetItemInfoEP8ItemInfo", CAWP::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D029F0, "_ZN4CAWP6DeployEv", CAWP::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02FA0, "_ZN4CAWP11GetMaxSpeedEv", CAWP::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02FC0, "_ZN4CAWP9iItemSlotEv", CAWP::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02A60, "_ZN4CAWP15SecondaryAttackEv", CAWP::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02B40, "_ZN4CAWP13PrimaryAttackEv", CAWP::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02EA0, "_ZN4CAWP6ReloadEv", CAWP::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D02F20, "_ZN4CAWP10WeaponIdleEv", CAWP::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D02FD0, "_ZN4CAWP12UseDecrementEv", CAWP::UseDecrement),	// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D02840, weapon_awp),
	HOOK_SYMBOLDEF(0x01D02BF0, "_ZN4CAWP7AWPFireEffi", CAWP::AWPFire),
//CC4
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03030, "_ZN3CC45SpawnEv", CC4::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D030F0, "_ZN3CC48PrecacheEv", CC4::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03840, "_ZN3CC48KeyValueEP14KeyValueData_s", CC4::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03900, "_ZN3CC43UseEP11CBaseEntityS1_8USE_TYPEf", CC4::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03120, "_ZN3CC411GetItemInfoEP8ItemInfo", CC4::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03190, "_ZN3CC46DeployEv", CC4::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03200, "_ZN3CC47HolsterEi", CC4::Holster),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03A80, "_ZN3CC411GetMaxSpeedEv", CC4::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D03A70, "_ZN3CC49iItemSlotEv", CC4::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03280, "_ZN3CC413PrimaryAttackEv", CC4::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03750, "_ZN3CC410WeaponIdleEv", CC4::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D03A90, "_ZN3CC412UseDecrementEv", CC4::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D02FE0, weapon_c4),
//CDEAGLE
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03AF0, "_ZN7CDEAGLE5SpawnEv", CDEAGLE::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03B50, "_ZN7CDEAGLE8PrecacheEv", CDEAGLE::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03BE0, "_ZN7CDEAGLE11GetItemInfoEP8ItemInfo", CDEAGLE::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03C50, "_ZN7CDEAGLE6DeployEv", CDEAGLE::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D04180, "_ZN7CDEAGLE11GetMaxSpeedEv", CDEAGLE::GetMaxSpeed),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D04170, "_ZN7CDEAGLE9iItemSlotEv", CDEAGLE::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03DB0, "_ZN7CDEAGLE15SecondaryAttackEv", CDEAGLE::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D03CF0, "_ZN7CDEAGLE13PrimaryAttackEv", CDEAGLE::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D040B0, "_ZN7CDEAGLE6ReloadEv", CDEAGLE::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D040F0, "_ZN7CDEAGLE10WeaponIdleEv", CDEAGLE::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D04190, "_ZN7CDEAGLE12UseDecrementEv", CDEAGLE::UseDecrement),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D041A0, "_ZN7CDEAGLE8IsPistolEv", CDEAGLE::IsPistol),				// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D03AA0, weapon_deagle),
	HOOK_SYMBOLDEF(0x01D03DC0, "_ZN7CDEAGLE10DEAGLEFireEffi", CDEAGLE::DEAGLEFire),
//CFlashbang
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D059D0, "_ZN10CFlashbang5SpawnEv", CFlashbang::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05A40, "_ZN10CFlashbang8PrecacheEv", CFlashbang::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05A80, "_ZN10CFlashbang11GetItemInfoEP8ItemInfo", CFlashbang::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06260, "_ZN10CFlashbang9CanDeployEv", CFlashbang::CanDeploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D062A0, "_ZN10CFlashbang7CanDropEv", CFlashbang::CanDrop),		// DEFUALT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05AF0, "_ZN10CFlashbang6DeployEv", CFlashbang::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05B90, "_ZN10CFlashbang7HolsterEi", CFlashbang::Holster),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D06290, "_ZN10CFlashbang11GetMaxSpeedEv", CFlashbang::GetMaxSpeed),		// DEFUALT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D06280, "_ZN10CFlashbang9iItemSlotEv", CFlashbang::iItemSlot),		// DEFUALT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05DA0, "_ZN10CFlashbang15SecondaryAttackEv", CFlashbang::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05BF0, "_ZN10CFlashbang13PrimaryAttackEv", CFlashbang::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05E40, "_ZN10CFlashbang10WeaponIdleEv", CFlashbang::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D062B0, "_ZN10CFlashbang12UseDecrementEv", CFlashbang::UseDecrement),		// DEFUALT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D062C0, "_ZN10CFlashbang8IsPistolEv", CFlashbang::IsPistol),			// DEFUALT
	// non-virtual func
	HOOK_DEF(0x01D05980, weapon_flashbang),
	HOOK_SYMBOLDEF(0x01D05C60, "_ZN10CFlashbang19ShieldSecondaryFireEii", CFlashbang::ShieldSecondaryFire),
	//HOOK_SYMBOLDEF(0x01D05DB0, "_ZN10CFlashbang19SetPlayerShieldAnimEv", CFlashbang::SetPlayerShieldAnim),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D05E00, "_ZN10CFlashbang21ResetPlayerShieldAnimEv", CFlashbang::ResetPlayerShieldAnim),	// NOXREF
//CG3SG1
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06320, "_ZN6CG3SG15SpawnEv", CG3SG1::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06370, "_ZN6CG3SG18PrecacheEv", CG3SG1::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D063F0, "_ZN6CG3SG111GetItemInfoEP8ItemInfo", CG3SG1::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06460, "_ZN6CG3SG16DeployEv", CG3SG1::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06A30, "_ZN6CG3SG111GetMaxSpeedEv", CG3SG1::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D06A50, "_ZN6CG3SG19iItemSlotEv", CG3SG1::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D064A0, "_ZN6CG3SG115SecondaryAttackEv", CG3SG1::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06580, "_ZN6CG3SG113PrimaryAttackEv", CG3SG1::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06930, "_ZN6CG3SG16ReloadEv", CG3SG1::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D069B0, "_ZN6CG3SG110WeaponIdleEv", CG3SG1::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D06A60, "_ZN6CG3SG112UseDecrementEv", CG3SG1::UseDecrement),				// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D062D0, weapon_g3sg1),
	HOOK_SYMBOLDEF(0x01D06600, "_ZN6CG3SG19G3SG1FireEffi", CG3SG1::G3SG1Fire),
//CGLOCK18
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D071E0, "_ZN8CGLOCK185SpawnEv", CGLOCK18::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07250, "_ZN8CGLOCK188PrecacheEv", CGLOCK18::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07310, "_ZN8CGLOCK1811GetItemInfoEP8ItemInfo", CGLOCK18::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07380, "_ZN8CGLOCK186DeployEv", CGLOCK18::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07B10, "_ZN8CGLOCK1811GetMaxSpeedEv", CGLOCK18::GetMaxSpeed),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07B00, "_ZN8CGLOCK189iItemSlotEv", CGLOCK18::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07480, "_ZN8CGLOCK1815SecondaryAttackEv", CGLOCK18::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07510, "_ZN8CGLOCK1813PrimaryAttackEv", CGLOCK18::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07980, "_ZN8CGLOCK186ReloadEv", CGLOCK18::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D079F0, "_ZN8CGLOCK1810WeaponIdleEv", CGLOCK18::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07B20, "_ZN8CGLOCK1812UseDecrementEv", CGLOCK18::UseDecrement),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07B30, "_ZN8CGLOCK188IsPistolEv", CGLOCK18::IsPistol),	// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D07190, weapon_glock18),
	HOOK_SYMBOLDEF(0x01D07670, "_ZN8CGLOCK1811GLOCK18FireEffi", CGLOCK18::GLOCK18Fire),
//CHEGrenade
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07B90, "_ZN10CHEGrenade5SpawnEv", CHEGrenade::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07C00, "_ZN10CHEGrenade8PrecacheEv", CHEGrenade::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07C60, "_ZN10CHEGrenade11GetItemInfoEP8ItemInfo", CHEGrenade::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08450, "_ZN10CHEGrenade9CanDeployEv", CHEGrenade::CanDeploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D08490, "_ZN10CHEGrenade7CanDropEv", CHEGrenade::CanDrop),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07CD0, "_ZN10CHEGrenade6DeployEv", CHEGrenade::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07D70, "_ZN10CHEGrenade7HolsterEi", CHEGrenade::Holster),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D08480, "_ZN10CHEGrenade11GetMaxSpeedEv", CHEGrenade::GetMaxSpeed),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D08470, "_ZN10CHEGrenade9iItemSlotEv", CHEGrenade::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07F80, "_ZN10CHEGrenade15SecondaryAttackEv", CHEGrenade::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D07DD0, "_ZN10CHEGrenade13PrimaryAttackEv", CHEGrenade::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08020, "_ZN10CHEGrenade10WeaponIdleEv", CHEGrenade::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D084A0, "_ZN10CHEGrenade12UseDecrementEv", CHEGrenade::UseDecrement),	// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D07B40, weapon_hegrenade),
	HOOK_SYMBOLDEF(0x01D07E40, "_ZN10CHEGrenade19ShieldSecondaryFireEii", CHEGrenade::ShieldSecondaryFire),
	//HOOK_SYMBOLDEF(0x01D07F90, "_ZN10CHEGrenade19SetPlayerShieldAnimEv", CHEGrenade::SetPlayerShieldAnim),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D07FE0, "_ZN10CHEGrenade21ResetPlayerShieldAnimEv", CHEGrenade::ResetPlayerShieldAnim),	// NOXREF
//CKnife
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08500, "_ZN6CKnife5SpawnEv", CKnife::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08550, "_ZN6CKnife8PrecacheEv", CKnife::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D085F0, "_ZN6CKnife11GetItemInfoEP8ItemInfo", CKnife::GetItemInfo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D09910, "_ZN6CKnife7CanDropEv", CKnife::CanDrop),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08640, "_ZN6CKnife6DeployEv", CKnife::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08710, "_ZN6CKnife7HolsterEi", CKnife::Holster),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D09900, "_ZN6CKnife11GetMaxSpeedEv", CKnife::GetMaxSpeed),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D098F0, "_ZN6CKnife9iItemSlotEv", CKnife::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08B50, "_ZN6CKnife15SecondaryAttackEv", CKnife::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08980, "_ZN6CKnife13PrimaryAttackEv", CKnife::PrimaryAttack),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D09920, "_ZN6CKnife12UseDecrementEv", CKnife::UseDecrement),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D08BB0, "_ZN6CKnife10WeaponIdleEv", CKnife::WeaponIdle),
	// non-virtual func
	HOOK_DEF(0x01D084B0, weapon_knife),
	HOOK_DEF(0x01D08780, FindHullIntersection),
	HOOK_SYMBOLDEF(0x01D08BA0, "_ZN6CKnife10SwingAgainEv", CKnife::SwingAgain),
	HOOK_SYMBOLDEF(0x01D08B80, "_ZN6CKnife5SmackEv", CKnife::Smack),
	//HOOK_SYMBOLDEF(0x01D08730, "_ZN6CKnife15WeaponAnimationEi", CKnife::WeaponAnimation),	// NOXREF
	HOOK_SYMBOLDEF(0x01D09390, "_ZN6CKnife4StabEi", CKnife::Stab),
	HOOK_SYMBOLDEF(0x01D08C30, "_ZN6CKnife5SwingEi", CKnife::Swing),
	HOOK_SYMBOLDEF(0x01D08A20, "_ZN6CKnife19ShieldSecondaryFireEii", CKnife::ShieldSecondaryFire),
	//HOOK_SYMBOLDEF(0x01D08990, "_ZN6CKnife19SetPlayerShieldAnimEv", CKnife::SetPlayerShieldAnim),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D089E0, "_ZN6CKnife21ResetPlayerShieldAnimEv", CKnife::ResetPlayerShieldAnim),	// NOXREF
//CM249
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D09980, "_ZN5CM2495SpawnEv", CM249::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D099D0, "_ZN5CM2498PrecacheEv", CM249::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D09A60, "_ZN5CM24911GetItemInfoEP8ItemInfo", CM249::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D09AD0, "_ZN5CM2496DeployEv", CM249::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A010, "_ZN5CM24911GetMaxSpeedEv", CM249::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A000, "_ZN5CM2499iItemSlotEv", CM249::iItemSlot),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D09B20, "_ZN5CM24913PrimaryAttackEv", CM249::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D09F40, "_ZN5CM2496ReloadEv", CM249::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D09F90, "_ZN5CM24910WeaponIdleEv", CM249::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A020, "_ZN5CM24912UseDecrementEv", CM249::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D09930, weapon_m249),
	HOOK_SYMBOLDEF(0x01D09BC0, "_ZN5CM2498M249FireEffi", CM249::M249Fire),
//CM3
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A080, "_ZN3CM35SpawnEv", CM3::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A0C0, "_ZN3CM38PrecacheEv", CM3::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A140, "_ZN3CM311GetItemInfoEP8ItemInfo", CM3::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A1B0, "_ZN3CM36DeployEv", CM3::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A740, "_ZN3CM311GetMaxSpeedEv", CM3::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A730, "_ZN3CM39iItemSlotEv", CM3::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A1E0, "_ZN3CM313PrimaryAttackEv", CM3::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A4A0, "_ZN3CM36ReloadEv", CM3::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A5D0, "_ZN3CM310WeaponIdleEv", CM3::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A750, "_ZN3CM312UseDecrementEv", CM3::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0A030, weapon_m3),
//CM4A1
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A7B0, "_ZN5CM4A15SpawnEv", CM4A1::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A810, "_ZN5CM4A18PrecacheEv", CM4A1::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A8C0, "_ZN5CM4A111GetItemInfoEP8ItemInfo", CM4A1::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A930, "_ZN5CM4A16DeployEv", CM4A1::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B050, "_ZN5CM4A111GetMaxSpeedEv", CM4A1::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B060, "_ZN5CM4A19iItemSlotEv", CM4A1::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0A9C0, "_ZN5CM4A115SecondaryAttackEv", CM4A1::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0AA70, "_ZN5CM4A113PrimaryAttackEv", CM4A1::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0AF60, "_ZN5CM4A16ReloadEv", CM4A1::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0AFC0, "_ZN5CM4A110WeaponIdleEv", CM4A1::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B070, "_ZN5CM4A112UseDecrementEv", CM4A1::UseDecrement),	// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0A760, weapon_m4a1),
	HOOK_SYMBOLDEF(0x01D0AB80, "_ZN5CM4A18M4A1FireEffi", CM4A1::M4A1Fire),
//CMAC10
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B0D0, "_ZN6CMAC105SpawnEv", CMAC10::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B120, "_ZN6CMAC108PrecacheEv", CMAC10::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B190, "_ZN6CMAC1011GetItemInfoEP8ItemInfo", CMAC10::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B200, "_ZN6CMAC106DeployEv", CMAC10::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B6E0, "_ZN6CMAC1011GetMaxSpeedEv", CMAC10::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B6D0, "_ZN6CMAC109iItemSlotEv", CMAC10::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B250, "_ZN6CMAC1013PrimaryAttackEv", CMAC10::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B610, "_ZN6CMAC106ReloadEv", CMAC10::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B660, "_ZN6CMAC1010WeaponIdleEv", CMAC10::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0B6F0, "_ZN6CMAC1012UseDecrementEv", CMAC10::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0B080, weapon_mac10),
	HOOK_SYMBOLDEF(0x01D0B290, "_ZN6CMAC109MAC10FireEffi", CMAC10::MAC10Fire),
//CP228
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BDC0, "_ZN5CP2285SpawnEv", CP228::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BE20, "_ZN5CP2288PrecacheEv", CP228::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BEB0, "_ZN5CP22811GetItemInfoEP8ItemInfo", CP228::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BF20, "_ZN5CP2286DeployEv", CP228::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C4A0, "_ZN5CP22811GetMaxSpeedEv", CP228::GetMaxSpeed),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C490, "_ZN5CP2289iItemSlotEv", CP228::iItemSlot),					// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C080, "_ZN5CP22815SecondaryAttackEv", CP228::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0BFC0, "_ZN5CP22813PrimaryAttackEv", CP228::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C380, "_ZN5CP2286ReloadEv", CP228::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C3D0, "_ZN5CP22810WeaponIdleEv", CP228::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C4B0, "_ZN5CP22812UseDecrementEv", CP228::UseDecrement),				// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C4C0, "_ZN5CP2288IsPistolEv", CP228::IsPistol),				// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0BD70, weapon_p228),
	HOOK_SYMBOLDEF(0x01D0C090, "_ZN5CP2288P228FireEffi", CP228::P228Fire),
	//HOOK_SYMBOLDEF(0x0, "_ZN5CP2288MakeBeamEv", CP228::MakeBeam),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN5CP22810BeamUpdateEv", CP228::BeamUpdate),			// NOXREF
//CP90
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C520, "_ZN4CP905SpawnEv", CP90::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C580, "_ZN4CP908PrecacheEv", CP90::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C600, "_ZN4CP9011GetItemInfoEP8ItemInfo", CP90::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C670, "_ZN4CP906DeployEv", CP90::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CB90, "_ZN4CP9011GetMaxSpeedEv", CP90::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CB80, "_ZN4CP909iItemSlotEv", CP90::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0C6C0, "_ZN4CP9013PrimaryAttackEv", CP90::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CAC0, "_ZN4CP906ReloadEv", CP90::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CB10, "_ZN4CP9010WeaponIdleEv", CP90::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CBA0, "_ZN4CP9012UseDecrementEv", CP90::UseDecrement),	// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0C4D0, weapon_p90),
	HOOK_SYMBOLDEF(0x01D0C750, "_ZN4CP907P90FireEffi", CP90::P90Fire),
//CSCOUT
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CC00, "_ZN6CSCOUT5SpawnEv", CSCOUT::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CC40, "_ZN6CSCOUT8PrecacheEv", CSCOUT::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CCC0, "_ZN6CSCOUT11GetItemInfoEP8ItemInfo", CSCOUT::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CD30, "_ZN6CSCOUT6DeployEv", CSCOUT::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D280, "_ZN6CSCOUT11GetMaxSpeedEv", CSCOUT::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D2A0, "_ZN6CSCOUT9iItemSlotEv", CSCOUT::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CDA0, "_ZN6CSCOUT15SecondaryAttackEv", CSCOUT::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0CE80, "_ZN6CSCOUT13PrimaryAttackEv", CSCOUT::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D1A0, "_ZN6CSCOUT6ReloadEv", CSCOUT::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D200, "_ZN6CSCOUT10WeaponIdleEv", CSCOUT::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D2B0, "_ZN6CSCOUT12UseDecrementEv", CSCOUT::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0CBB0, weapon_scout),
	HOOK_SYMBOLDEF(0x01D0CEF0, "_ZN6CSCOUT9SCOUTFireEffi", CSCOUT::SCOUTFire),
//CSmokeGrenade
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E250, "_ZN13CSmokeGrenade5SpawnEv", CSmokeGrenade::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E2C0, "_ZN13CSmokeGrenade8PrecacheEv", CSmokeGrenade::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E310, "_ZN13CSmokeGrenade11GetItemInfoEP8ItemInfo", CSmokeGrenade::GetItemInfo),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EB80, "_ZN13CSmokeGrenade7CanDropEv", CSmokeGrenade::CanDrop),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E380, "_ZN13CSmokeGrenade6DeployEv", CSmokeGrenade::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E420, "_ZN13CSmokeGrenade7HolsterEi", CSmokeGrenade::Holster),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EB70, "_ZN13CSmokeGrenade11GetMaxSpeedEv", CSmokeGrenade::GetMaxSpeed),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EB60, "_ZN13CSmokeGrenade9iItemSlotEv", CSmokeGrenade::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E630, "_ZN13CSmokeGrenade15SecondaryAttackEv", CSmokeGrenade::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E480, "_ZN13CSmokeGrenade13PrimaryAttackEv", CSmokeGrenade::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0E6D0, "_ZN13CSmokeGrenade10WeaponIdleEv", CSmokeGrenade::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EB90, "_ZN13CSmokeGrenade12UseDecrementEv", CSmokeGrenade::UseDecrement),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EB40, "_ZN13CSmokeGrenade9CanDeployEv", CSmokeGrenade::CanDeploy),
	// non-virtual func
	HOOK_DEF(0x01D0E200, weapon_smokegrenade),
	HOOK_SYMBOLDEF(0x01D0E4F0, "_ZN13CSmokeGrenade19ShieldSecondaryFireEii", CSmokeGrenade::ShieldSecondaryFire),
	//HOOK_SYMBOLDEF(0x01D0E640, "_ZN13CSmokeGrenade19SetPlayerShieldAnimEv", CSmokeGrenade::SetPlayerShieldAnim),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D0E690, "_ZN13CSmokeGrenade21ResetPlayerShieldAnimEv", CSmokeGrenade::ResetPlayerShieldAnim),	// NOXREF
//CTMP
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EBF0, "_ZN4CTMP5SpawnEv", CTMP::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0EC50, "_ZN4CTMP8PrecacheEv", CTMP::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0ECB0, "_ZN4CTMP11GetItemInfoEP8ItemInfo", CTMP::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0ED20, "_ZN4CTMP6DeployEv", CTMP::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F1D0, "_ZN4CTMP11GetMaxSpeedEv", CTMP::GetMaxSpeed),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F1C0, "_ZN4CTMP9iItemSlotEv", CTMP::iItemSlot),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0ED70, "_ZN4CTMP13PrimaryAttackEv", CTMP::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F100, "_ZN4CTMP6ReloadEv", CTMP::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F150, "_ZN4CTMP10WeaponIdleEv", CTMP::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F1E0, "_ZN4CTMP12UseDecrementEv", CTMP::UseDecrement),				// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0EBA0, weapon_tmp),
	HOOK_SYMBOLDEF(0x01D0EDB0, "_ZN4CTMP7TMPFireEffi", CTMP::TMPFire),
//CXM1014
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10220, "_ZN7CXM10145SpawnEv", CXM1014::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10260, "_ZN7CXM10148PrecacheEv", CXM1014::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D102D0, "_ZN7CXM101411GetItemInfoEP8ItemInfo", CXM1014::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10340, "_ZN7CXM10146DeployEv", CXM1014::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D10940, "_ZN7CXM101411GetMaxSpeedEv", CXM1014::GetMaxSpeed),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D10930, "_ZN7CXM10149iItemSlotEv", CXM1014::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10370, "_ZN7CXM101413PrimaryAttackEv", CXM1014::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10640, "_ZN7CXM10146ReloadEv", CXM1014::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D107F0, "_ZN7CXM101410WeaponIdleEv", CXM1014::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D10950, "_ZN7CXM101412UseDecrementEv", CXM1014::UseDecrement),			// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D101D0, weapon_xm1014),
//CELITE
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04200, "_ZN6CELITE5SpawnEv", CELITE::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04250, "_ZN6CELITE8PrecacheEv", CELITE::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04300, "_ZN6CELITE11GetItemInfoEP8ItemInfo", CELITE::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04370, "_ZN6CELITE6DeployEv", CELITE::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D049D0, "_ZN6CELITE11GetMaxSpeedEv", CELITE::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D049C0, "_ZN6CELITE9iItemSlotEv", CELITE::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D043D0, "_ZN6CELITE13PrimaryAttackEv", CELITE::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04900, "_ZN6CELITE6ReloadEv", CELITE::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04940, "_ZN6CELITE10WeaponIdleEv", CELITE::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D049E0, "_ZN6CELITE12UseDecrementEv", CELITE::UseDecrement),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D049F0, "_ZN6CELITE8IsPistolEv", CELITE::IsPistol),				// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D041B0, weapon_elite),
	HOOK_SYMBOLDEF(0x01D04490, "_ZN6CELITE9ELITEFireEffi", CELITE::ELITEFire),
//CFiveSeven
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05280, "_ZN10CFiveSeven5SpawnEv", CFiveSeven::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D052E0, "_ZN10CFiveSeven8PrecacheEv", CFiveSeven::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05370, "_ZN10CFiveSeven11GetItemInfoEP8ItemInfo", CFiveSeven::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D053E0, "_ZN10CFiveSeven6DeployEv", CFiveSeven::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05950, "_ZN10CFiveSeven11GetMaxSpeedEv", CFiveSeven::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05940, "_ZN10CFiveSeven9iItemSlotEv", CFiveSeven::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05540, "_ZN10CFiveSeven15SecondaryAttackEv", CFiveSeven::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05480, "_ZN10CFiveSeven13PrimaryAttackEv", CFiveSeven::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05840, "_ZN10CFiveSeven6ReloadEv", CFiveSeven::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05880, "_ZN10CFiveSeven10WeaponIdleEv", CFiveSeven::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05960, "_ZN10CFiveSeven12UseDecrementEv", CFiveSeven::UseDecrement),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05970, "_ZN10CFiveSeven8IsPistolEv", CFiveSeven::IsPistol),				// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D05230, weapon_fiveseven),
	HOOK_SYMBOLDEF(0x01D05550, "_ZN10CFiveSeven13FiveSevenFireEffi", CFiveSeven::FiveSevenFire),
	//HOOK_SYMBOLDEF(0x0, "_ZN10CFiveSeven8MakeBeamEv", CFiveSeven::MakeBeam),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10CFiveSeven10BeamUpdateEv", CFiveSeven::BeamUpdate),			// NOXREF
//CUMP45
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F240, "_ZN6CUMP455SpawnEv", CUMP45::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F290, "_ZN6CUMP458PrecacheEv", CUMP45::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F300, "_ZN6CUMP4511GetItemInfoEP8ItemInfo", CUMP45::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F370, "_ZN6CUMP456DeployEv", CUMP45::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F840, "_ZN6CUMP4511GetMaxSpeedEv", CUMP45::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F830, "_ZN6CUMP459iItemSlotEv", CUMP45::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F3C0, "_ZN6CUMP4513PrimaryAttackEv", CUMP45::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F770, "_ZN6CUMP456ReloadEv", CUMP45::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F7C0, "_ZN6CUMP4510WeaponIdleEv", CUMP45::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0F850, "_ZN6CUMP4512UseDecrementEv", CUMP45::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0F1F0, weapon_ump45),
	HOOK_SYMBOLDEF(0x01D0F400, "_ZN6CUMP459UMP45FireEffi", CUMP45::UMP45Fire),
//CSG550
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D310, "_ZN6CSG5505SpawnEv", CSG550::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D360, "_ZN6CSG5508PrecacheEv", CSG550::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D3E0, "_ZN6CSG55011GetItemInfoEP8ItemInfo", CSG550::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D450, "_ZN6CSG5506DeployEv", CSG550::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DA10, "_ZN6CSG55011GetMaxSpeedEv", CSG550::GetMaxSpeed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DA30, "_ZN6CSG5509iItemSlotEv", CSG550::iItemSlot),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D480, "_ZN6CSG55015SecondaryAttackEv", CSG550::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D560, "_ZN6CSG55013PrimaryAttackEv", CSG550::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D920, "_ZN6CSG5506ReloadEv", CSG550::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D0D990, "_ZN6CSG55010WeaponIdleEv", CSG550::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D0DA40, "_ZN6CSG55012UseDecrementEv", CSG550::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D0D2C0, weapon_sg550),
	HOOK_SYMBOLDEF(0x01D0D610, "_ZN6CSG5509SG550FireEffi", CSG550::SG550Fire),
//CGalil
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06AC0, "_ZN6CGalil5SpawnEv", CGalil::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06B00, "_ZN6CGalil8PrecacheEv", CGalil::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06B80, "_ZN6CGalil11GetItemInfoEP8ItemInfo", CGalil::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06BF0, "_ZN6CGalil6DeployEv", CGalil::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07170, "_ZN6CGalil11GetMaxSpeedEv", CGalil::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07160, "_ZN6CGalil9iItemSlotEv", CGalil::iItemSlot),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06C40, "_ZN6CGalil15SecondaryAttackEv", CGalil::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D06C50, "_ZN6CGalil13PrimaryAttackEv", CGalil::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D070A0, "_ZN6CGalil6ReloadEv", CGalil::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D070F0, "_ZN6CGalil10WeaponIdleEv", CGalil::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D07180, "_ZN6CGalil12UseDecrementEv", CGalil::UseDecrement),	// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D06A70, weapon_galil),
	HOOK_SYMBOLDEF(0x01D06D20, "_ZN6CGalil9GalilFireEffi", CGalil::GalilFire),
//CFamas
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04A50, "_ZN6CFamas5SpawnEv", CFamas::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04AA0, "_ZN6CFamas8PrecacheEv", CFamas::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04B40, "_ZN6CFamas11GetItemInfoEP8ItemInfo", CFamas::GetItemInfo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04BB0, "_ZN6CFamas6DeployEv", CFamas::Deploy),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05210, "_ZN6CFamas11GetMaxSpeedEv", CFamas::GetMaxSpeed),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05200, "_ZN6CFamas9iItemSlotEv", CFamas::iItemSlot),				// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04C10, "_ZN6CFamas15SecondaryAttackEv", CFamas::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D04C90, "_ZN6CFamas13PrimaryAttackEv", CFamas::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05120, "_ZN6CFamas6ReloadEv", CFamas::Reload),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D05190, "_ZN6CFamas10WeaponIdleEv", CFamas::WeaponIdle),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D05220, "_ZN6CFamas12UseDecrementEv", CFamas::UseDecrement),		// DEFAULT
	// non-virtual func
	HOOK_DEF(0x01D04A00, weapon_famas),
	HOOK_SYMBOLDEF(0x01D04D70, "_ZN6CFamas9FamasFireEffii", CFamas::FamasFire),
//CArmoury
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD0E50, "_ZN8CArmoury5SpawnEv", CArmoury::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD1230, "_ZN8CArmoury8PrecacheEv", CArmoury::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD10A0, "_ZN8CArmoury7RestartEv", CArmoury::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD0D80, "_ZN8CArmoury8KeyValueEP14KeyValueData_s", CArmoury::KeyValue),
	// non-virtual func
	HOOK_DEF(0x01DD0E00, armoury_entity),
	HOOK_SYMBOLDEF(0x01DD0A10, "_ZN8CArmoury12ArmouryTouchEP11CBaseEntity", CArmoury::ArmouryTouch),

#endif // Weapons_Region

#ifndef GGrenade_Region

	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D831C0, "_ZN8CGrenade5SpawnEv", CGrenade::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D84820, "_ZN8CGrenade4SaveER5CSave", CGrenade::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D84850, "_ZN8CGrenade7RestoreER8CRestore", CGrenade::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D594F0, "_ZN8CGrenade10ObjectCapsEv", CGrenade::ObjectCaps),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D82320, "_ZN8CGrenade6KilledEP9entvars_si", CGrenade::Killed),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D83560, "_ZN8CGrenade10BloodColorEv", CGrenade::BloodColor),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D83720, "_ZN8CGrenade3UseEP11CBaseEntityS1_8USE_TYPEf", CGrenade::Use),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D82E00, "_ZN8CGrenade11BounceSoundEv", CGrenade::BounceSound),
	// non-virtual func
	//HOOK_DEF(0x0, AnnounceFlashInterval),	// NOXREF
	HOOK_SYMBOLDEF(0x01D83570, "_ZN8CGrenade10ShootTimedEP9entvars_s6VectorS2_f", CGrenade::ShootTimed),
	HOOK_SYMBOLDEF(0x01D833D0, "_ZN8CGrenade11ShootTimed2EP9entvars_s6VectorS2_fit", CGrenade::ShootTimed2),
	//HOOK_SYMBOLDEF(0x01D832C0, "_ZN8CGrenade12ShootContactEP9entvars_s6VectorS2_", CGrenade::ShootContact),	// NOXREF
	HOOK_SYMBOLDEF(0x01D83C90, "_ZN8CGrenade17ShootSmokeGrenadeEP9entvars_s6VectorS2_ft", CGrenade::ShootSmokeGrenade),
	HOOK_SYMBOLDEF(0x01D839C0, "_ZN8CGrenade18ShootSatchelChargeEP9entvars_s6VectorS2_", CGrenade::ShootSatchelCharge),
	//HOOK_SYMBOLDEF(0x01D84760, "_ZN8CGrenade17UseSatchelChargesEP9entvars_sNS_11SATCHELCODEE", CGrenade::UseSatchelCharges),	// NOXREF
	HOOK_SYMBOLDEF(0x01D80D40, "_ZN8CGrenade7ExplodeE6VectorS0_", CGrenade::Explode, void (Vector, Vector)),
	HOOK_SYMBOLDEF(0x01D80DA0, "_ZN8CGrenade7ExplodeEP11TraceResulti", CGrenade::Explode, void (TraceResult *, int)),
	HOOK_SYMBOLDEF(0x01D81010, "_ZN8CGrenade8Explode2EP11TraceResulti", CGrenade::Explode2),
	HOOK_SYMBOLDEF(0x01D81620, "_ZN8CGrenade8Explode3EP11TraceResulti", CGrenade::Explode3),
	//HOOK_SYMBOLDEF(0x01D819B0, "_ZN8CGrenade10SG_ExplodeEP11TraceResulti", CGrenade::SG_Explode),	// NOXREF
	HOOK_SYMBOLDEF(0x01D82050, "_ZN8CGrenade5SmokeEv", CGrenade::Smoke),
	HOOK_SYMBOLDEF(0x01D81F50, "_ZN8CGrenade6Smoke2Ev", CGrenade::Smoke2),
	HOOK_SYMBOLDEF(0x01D81DF0, "_ZN8CGrenade8Smoke3_AEv", CGrenade::Smoke3_A),
	HOOK_SYMBOLDEF(0x01D81C90, "_ZN8CGrenade8Smoke3_BEv", CGrenade::Smoke3_B),
	HOOK_SYMBOLDEF(0x01D81B70, "_ZN8CGrenade8Smoke3_CEv", CGrenade::Smoke3_C),
	HOOK_SYMBOLDEF(0x01D82150, "_ZN8CGrenade8SG_SmokeEv", CGrenade::SG_Smoke),
	HOOK_SYMBOLDEF(0x01D82B10, "_ZN8CGrenade11BounceTouchEP11CBaseEntity", CGrenade::BounceTouch),
	HOOK_SYMBOLDEF(0x01D82D80, "_ZN8CGrenade10SlideTouchEP11CBaseEntity", CGrenade::SlideTouch),
	HOOK_SYMBOLDEF(0x01D83E60, "_ZN8CGrenade7C4ThinkEv", CGrenade::C4Think),
	HOOK_SYMBOLDEF(0x01D84750, "_ZN8CGrenade7C4TouchEP11CBaseEntity", CGrenade::C4Touch),
	HOOK_SYMBOLDEF(0x01D82820, "_ZN8CGrenade12ExplodeTouchEP11CBaseEntity", CGrenade::ExplodeTouch),
	HOOK_SYMBOLDEF(0x01D82A00, "_ZN8CGrenade16DangerSoundThinkEv", CGrenade::DangerSoundThink),
	HOOK_SYMBOLDEF(0x01D823D0, "_ZN8CGrenade11PreDetonateEv", CGrenade::PreDetonate),
	HOOK_SYMBOLDEF(0x01D82410, "_ZN8CGrenade8DetonateEv", CGrenade::Detonate),
	HOOK_SYMBOLDEF(0x01D824A0, "_ZN8CGrenade11SG_DetonateEv", CGrenade::SG_Detonate),
	HOOK_SYMBOLDEF(0x01D82700, "_ZN8CGrenade9Detonate2Ev", CGrenade::Detonate2),
	HOOK_SYMBOLDEF(0x01D82790, "_ZN8CGrenade9Detonate3Ev", CGrenade::Detonate3),
	HOOK_SYMBOLDEF(0x01D823B0, "_ZN8CGrenade11DetonateUseEP11CBaseEntityS1_8USE_TYPEf", CGrenade::DetonateUse),
	HOOK_SYMBOLDEF(0x01D82EE0, "_ZN8CGrenade11TumbleThinkEv", CGrenade::TumbleThink),
	HOOK_SYMBOLDEF(0x01D83030, "_ZN8CGrenade14SG_TumbleThinkEv", CGrenade::SG_TumbleThink),
	//linked objects
	HOOK_DEF(0x01D80CF0, grenade),

#endif // GGrenade_Region

#ifndef Animation_Region

	HOOK_SYMBOLDEF(0x01D5A650, "_Z11ExtractBboxPviPfS0_", ExtractBbox),
	HOOK_SYMBOLDEF(0x01D5A6B0, "_Z14LookupActivityPvP9entvars_si", LookupActivity),
	HOOK_SYMBOLDEF(0x01D5A780, "_Z22LookupActivityHeaviestPvP9entvars_si", LookupActivityHeaviest),
	//HOOK_SYMBOLDEF(0x01D5A7D0, "_Z14GetEyePositionPvPf", GetEyePosition),	// NOXREF
	HOOK_SYMBOLDEF(0x01D5A810, "_Z14LookupSequencePvPKc", LookupSequence),
	//HOOK_SYMBOLDEF(0x01D5A870, "_Z12IsSoundEventi", IsSoundEvent),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D5A890, "_Z16SequencePrecachePvPKc", SequencePrecache),	// NOXREF
	HOOK_SYMBOLDEF(0x01D5A9A0, "_Z15GetSequenceInfoPvP9entvars_sPfS2_", GetSequenceInfo),
	HOOK_SYMBOLDEF(0x01D5AA60, "_Z16GetSequenceFlagsPvP9entvars_s", GetSequenceFlags),
	HOOK_SYMBOLDEF(0x01D5AAA0, "_Z17GetAnimationEventPvP9entvars_sP14MonsterEvent_tffi", GetAnimationEvent),
	HOOK_SYMBOLDEF(0x01D5ABF0, "_Z13SetControllerPvP9entvars_sif", SetController),
	HOOK_SYMBOLDEF(0x01D5AD60, "_Z11SetBlendingPvP9entvars_sif", SetBlending),
	HOOK_SYMBOLDEF(0x01D5AEB0, "_Z14FindTransitionPviiPi", FindTransition),
	HOOK_SYMBOLDEF(0x01D5AFC0, "_Z12SetBodygroupPvP9entvars_sii", SetBodygroup),
	HOOK_SYMBOLDEF(0x01D5B020, "_Z12GetBodygroupPvP9entvars_si", GetBodygroup),
	HOOK_DEF(0x01D5B080, Server_GetBlendingInterface),
	HOOK_SYMBOLDEF(0x01D5B0E0, "_Z15AngleQuaternionPfS_", AngleQuaternion),
	HOOK_SYMBOLDEF(0x01D5B190, "_Z15QuaternionSlerpPfS_fS_", QuaternionSlerp),
	HOOK_SYMBOLDEF(0x01D5B430, "_Z13StudioGetAnimP7model_sP16mstudioseqdesc_t", StudioGetAnim),
	//HOOK_SYMBOLDEF(0x01D5B4C0, "_Z15LookupAnimationP11studiohdr_tP7model_sP16mstudioseqdesc_ti", LookupAnimation),	// NOXREF
	HOOK_SYMBOLDEF(0x01D5B500, "_Z17StudioCalcBoneAdjfPfPKhS1_h", StudioCalcBoneAdj),
	HOOK_SYMBOLDEF(0x01D5B720, "_Z23StudioCalcBoneQuaterionifP13mstudiobone_tP13mstudioanim_tPfS3_", StudioCalcBoneQuaterion),
	HOOK_SYMBOLDEF(0x01D5B8E0, "_Z22StudioCalcBonePositionifP13mstudiobone_tP13mstudioanim_tPfS3_", StudioCalcBonePosition),
	HOOK_SYMBOLDEF(0x01D5BA20, "_Z16StudioSlerpBonesPA4_fPA3_fS0_S2_f", StudioSlerpBones),
	//HOOK_SYMBOLDEF(0x01D5BB50, "_Z19StudioCalcRotationsP13mstudiobone_tPiiPfPA3_fPA4_fP16mstudioseqdesc_tP13mstudioanim_tff", StudioCalcRotations),	// NOXREF
	HOOK_SYMBOLDEF(0x01D5BBE0, "_Z16ConcatTransformsPA4_fS0_S0_", ConcatTransforms),

#if 1
	// NOTE: both functions must be involved in the hooks or also both disable their.
	HOOK_SYMBOLDEF(0x01D5B350, "_Z16QuaternionMatrixPfPA4_f", QuaternionMatrix),
	HOOK_SYMBOLDEF(0x01D5BD20, "_Z19SV_StudioSetupBonesP7model_sfiPKfS2_PKhS4_iPK7edict_s", SV_StudioSetupBones),
#endif

#endif // Animation_Region

#ifndef MemoryPool_Region

	//HOOK_SYMBOLDEF(0x01D8A2D0, "_ZN11CMemoryPoolC2Eii", CMemoryPool::CMemoryPool), // NOXREF
	HOOK_SYMBOLDEF(0x01D8A330, "_ZN11CMemoryPool10AddNewBlobEv", CMemoryPool::AddNewBlob),
	HOOK_SYMBOLDEF(0x01D8A3D0, "_ZN11CMemoryPool5AllocEj", CMemoryPool::Alloc),
	HOOK_SYMBOLDEF(0x01D8A420, "_ZN11CMemoryPool4FreeEPv", CMemoryPool::Free),

#endif // MemoryPool_Region

#ifndef Unicode_StrTools_Region

	//HOOK_SYMBOLDEF(0x0, "_Z16Q_IsValidUChar32w", Q_IsValidUChar32),

#ifdef _WIN32
	HOOK_DEF(0x01DDE010, Q_UTF32ToUChar32),
#endif // _WIN32

	//HOOK_DEF(0x0, Q_UChar32ToUTF32Len),
	//HOOK_DEF(0x0, Q_UChar32ToUTF32),
	//HOOK_DEF(0x01DDDEE0, Q_UChar32ToUTF8Len),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z19Q_UChar32ToUTF16Lenw", Q_UChar32ToUTF16Len),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z16Q_UChar32ToUTF16wPt", Q_UChar32ToUTF16),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDDF70, "_Z15Q_UChar32ToUTF8wPc", Q_UChar32ToUTF8),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z16Q_UTF16ToUChar32PKtRwRb", Q_UTF16ToUChar32),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z13Q_UTF8ToUTF16PKcPti25EStringConvertErrorPolicy", Q_UTF8ToUTF16),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDFA30, "_Z13Q_UTF8ToUTF32PKcPwi25EStringConvertErrorPolicy", Q_UTF8ToUTF32),
	//HOOK_SYMBOLDEF(0x0, "_Z13Q_UTF16ToUTF8PKtPci25EStringConvertErrorPolicy", Q_UTF16ToUTF8),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z14Q_UTF16ToUTF32PKtPwi25EStringConvertErrorPolicy", Q_UTF16ToUTF32),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z13Q_UTF32ToUTF8PKwPci25EStringConvertErrorPolicy", Q_UTF32ToUTF8),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDEB00, "_Z14Q_UTF32ToUTF16PKwPti25EStringConvertErrorPolicy", Q_UTF32ToUTF16),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDECA0, "_Z15Q_UTF8ToUChar32PKcRwRb", Q_UTF8ToUChar32),
	HOOK_DEF(0x01DDEE00, Q_UnicodeValidate),
	//HOOK_DEF(0x01DDEE50, Q_UnicodeLength),	// NOXREF
	//HOOK_DEF(0x01DDEE80, Q_UnicodeAdvance),
	//HOOK_SYMBOLDEF(0x01DDEEC0, "_Z14Q_IsMeanSpaceWw", Q_IsMeanSpaceW),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDF150, "_Z15Q_IsDeprecatedWw", Q_IsDeprecatedW),	// NOXREF
	//HOOK_DEF(0x0, StripWhitespaceWorker),		// NOXREF
	//HOOK_DEF(0x0, StripUnprintableWorker),	// NOXREF
	HOOK_DEF(0x01DDF1D0, Q_StripUnprintableAndSpace),
	//HOOK_DEF(0x01DDF8A0, V_UTF8ToUChar32),	// NOXREF
	//HOOK_DEF(0x01DDF8D0, Q_UnicodeRepair),	// NOXREF

#endif // Unicode_StrTools_Region

#ifndef CUtlSymbol_Region

	//HOOK_SYMBOLDEF(0x01DC81F0, "_ZN10CUtlSymbolC2EPKc", CUtlSymbol::CUtlSymbol),
	//HOOK_SYMBOLDEF(0x01DC80D0, "_ZN10CUtlSymbol10InitializeEv", CUtlSymbol::Initialize),
	//HOOK_SYMBOLDEF(0x01DC8160, "_ZN10CUtlSymbol9CurrTableEv", CUtlSymbol::CurrTable),
	//HOOK_SYMBOLDEF(0x01DC82A0, "_ZNK10CUtlSymbol6StringEv", CUtlSymbol::String),
	//HOOK_SYMBOLDEF(0x01DC82E0, "_ZNK10CUtlSymboleqEPKc", CUtlSymbol::operator==),
	//HOOK_SYMBOLDEF(0x01DC8390, "_ZN15CUtlSymbolTable7SymLessERKjS1_", CUtlSymbolTable::SymLess),
	//HOOK_SYMBOLDEF(0x01DC8410, "_ZN15CUtlSymbolTable8SymLessiERKjS1_", CUtlSymbolTable::SymLessi),
	//HOOK_SYMBOLDEF(0x01DC8460, "_ZN15CUtlSymbolTableC2Eiib", CUtlSymbolTable::CUtlSymbolTable),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC84D0, "_ZN15CUtlSymbolTableD2Ev", CUtlSymbolTable::~CUtlSymbolTable),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC8540, "_ZN15CUtlSymbolTable4FindEPKc", CUtlSymbolTable::Find),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DC87D0, "_ZNK15CUtlSymbolTable6StringE10CUtlSymbol", CUtlSymbolTable::String),
	//HOOK_SYMBOLDEF(0x01DC8800, "_ZN15CUtlSymbolTable9RemoveAllEv", CUtlSymbolTable::RemoveAll),
	//HOOK_SYMBOLDEF(0x01DC8680, "_ZN15CUtlSymbolTable9AddStringEPKc", CUtlSymbolTable::AddString),

#endif // CUtlSymbol_Region

#ifndef Debug_Region

	//HOOK_DEF(0x0, IsDeveloper),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D732D0, "_Z12UTIL_DPrintf15DebugOutputTypePcz", UTIL_DPrintf, void(DebugOutputType outputType, char *pszMsg, ...)),	// NOXREF
	HOOK_SYMBOLDEF(0x01D73320, "_Z12UTIL_DPrintfPcz", UTIL_DPrintf, void(char *pszMsg, ...)),

	//HOOK_SYMBOLDEF(0x01D73360, "_Z20UTIL_SetDprintfFlagsPKc", PrintDebugFlags),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZL12SetDebugFlagPKcb", SetDebugFlag),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z14PrintDebugFlagPKc", PrintDebugFlag),	// NOXREF
	HOOK_SYMBOLDEF(0x01D73410, "_Z20UTIL_SetDprintfFlagsPKc", UTIL_SetDprintfFlags),
	//HOOK_SYMBOLDEF(0x01D73690, "_Z15UTIL_BotDPrintfPcz", UTIL_BotDPrintf),		// NOXREF
	HOOK_SYMBOLDEF(0x01D736E0, "_Z18UTIL_CareerDPrintfPcz", UTIL_CareerDPrintf),
	//HOOK_SYMBOLDEF(0x01D73730, "_Z17UTIL_TutorDPrintfPcz", UTIL_TutorDPrintf),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D73780, "_Z17UTIL_StatsDPrintfPcz", UTIL_StatsDPrintf),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D737D0, "_Z19UTIL_HostageDPrintfPcz", UTIL_HostageDPrintf),	// NOXREF

#endif // Debug_Region

#ifndef CS_Bot_Region
//Bot Manager
	// virtual func
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D341B0, CCSBotManager, "_ZN11CBotManager12RestartRoundEv", CBotManager::RestartRound),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D34210, CCSBotManager, "_ZN11CBotManager10StartFrameEv", CBotManager::StartFrame),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D34540, CCSBotManager, "_ZN11CBotManager7OnEventE13GameEventTypeP11CBaseEntityS2_", CBotManager::OnEvent),
	// non-virtual func
	//HOOK_DEF(0x01D34170, MethodThunk<CBotManager>::Constructor),
	HOOK_SYMBOLDEF(0x01D34510, "_ZNK11CBotManager17GetNavMapFilenameEv", CBotManager::GetNavMapFilename),
	HOOK_SYMBOLDEF(0x01D34650, "_ZN11CBotManager10AddGrenadeEiP8CGrenade", CBotManager::AddGrenade),
	HOOK_SYMBOLDEF(0x01D346C0, "_ZN11CBotManager13RemoveGrenadeEP8CGrenade", CBotManager::RemoveGrenade),
	//HOOK_SYMBOLDEF(0x01D346F0, "_ZN11CBotManager22ValidateActiveGrenadesEv", CBotManager::ValidateActiveGrenades),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D34740, "_ZN11CBotManager18DestroyAllGrenadesEv", CBotManager::DestroyAllGrenades),	// NOXREF
	HOOK_SYMBOLDEF(0x01D347A0, "_ZN11CBotManager18IsInsideSmokeCloudEPK6Vector", CBotManager::IsInsideSmokeCloud),
	HOOK_SYMBOLDEF(0x01D34850, "_ZN11CBotManager20IsLineBlockedBySmokeEPK6VectorS2_", CBotManager::IsLineBlockedBySmoke),
	// non-class func
	HOOK_SYMBOLDEF(0x01D34120, "_Z15NameToGameEventPKc", NameToGameEvent),
//CCSBotManager
	// virtual func
	//HOOK_DEF(0x01D22D60, MethodThunk<CCSBotManager>::Constructor),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D23770, "_ZN13CCSBotManager16ClientDisconnectEP11CBasePlayer", CCSBotManager::ClientDisconnect),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D24880, "_ZN13CCSBotManager13ClientCommandEP11CBasePlayerPKc", CCSBotManager::ClientCommand),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D234D0, "_ZN13CCSBotManager14ServerActivateEv", CCSBotManager::ServerActivate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D23760, "_ZN13CCSBotManager16ServerDeactivateEv", CCSBotManager::ServerDeactivate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D23900, "_ZN13CCSBotManager13ServerCommandEPKc", CCSBotManager::ServerCommand),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D23520, "_ZN13CCSBotManager16AddServerCommandEPKc", CCSBotManager::AddServerCommand),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D23540, "_ZN13CCSBotManager17AddServerCommandsEv", CCSBotManager::AddServerCommands),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D22F40, "_ZN13CCSBotManager12RestartRoundEv", CCSBotManager::RestartRound),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D23200, "_ZN13CCSBotManager10StartFrameEv", CCSBotManager::StartFrame),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D25780, "_ZN13CCSBotManager7OnEventE13GameEventTypeP11CBaseEntityS2_", CCSBotManager::OnEvent),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D25970, "_ZNK13CCSBotManager17GetPlayerPriorityEP11CBasePlayer", CCSBotManager::GetPlayerPriority),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D25920, "_ZNK13CCSBotManager17IsImportantPlayerEP11CBasePlayer", CCSBotManager::IsImportantPlayer),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D24D90, "_ZN13CCSBotManager15ValidateMapDataEv", CCSBotManager::ValidateMapData),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager13IsLearningMapEv", CCSBotManager::IsLearningMap),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager18SetLearningMapFlagEv", CCSBotManager::SetLearningMapFlag),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager19IsAnalysisRequestedEv", CCSBotManager::IsAnalysisRequested),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager15RequestAnalysisEv", CCSBotManager::RequestAnalysis),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager18AckAnalysisRequestEv", CCSBotManager::AckAnalysisRequest),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager18GetDifficultyLevelEv", CCSBotManager::BotDifficultyType GetDifficultyLevel),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager11GetScenarioEv", CCSBotManager::GameScenarioType GetScenario),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager7GetZoneEi", CCSBotManager::GetZone, const CCSBotManager::Zone *(int) const),	// NOXREF
	HOOK_SYMBOLDEF(0x01D25530, "_ZNK13CCSBotManager7GetZoneEPK6Vector", CCSBotManager::GetZone, const CCSBotManager::Zone *(const Vector *) const),
	//HOOK_SYMBOLDEF(0x01D255C0, "_ZNK13CCSBotManager14GetClosestZoneEPK6Vector", CCSBotManager::GetClosestZone, const CCSBotManager::Zone *(const Vector *) const),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager14GetClosestZoneEPK11CBaseEntity", CCSBotManager::GetClosestZone, const CCSBotManager::Zone *(const CBaseEntity *) const),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager12GetZoneCountEv", CCSBotManager::GetZoneCount),
	HOOK_SYMBOLDEF(0x01D25630, "_ZNK13CCSBotManager23GetRandomPositionInZoneEPKNS_4ZoneE", CCSBotManager::GetRandomPositionInZone),
	HOOK_SYMBOLDEF(0x01D25750, "_ZNK13CCSBotManager19GetRandomAreaInZoneEPKNS_4ZoneE", CCSBotManager::GetRandomAreaInZone),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager13GetRandomZoneEv", CCSBotManager::GetRandomZone),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager13IsBombPlantedEv", CCSBotManager::IsBombPlanted),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager21GetBombPlantTimestampEv", CCSBotManager::GetBombPlantTimestamp),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager17IsTimeToPlantBombEv", CCSBotManager::IsTimeToPlantBomb),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager14GetBombDefuserEv", CCSBotManager::GetBombDefuser),
	HOOK_SYMBOLDEF(0x01D258B0, "_ZNK13CCSBotManager15GetBombTimeLeftEv", CCSBotManager::GetBombTimeLeft),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager12GetLooseBombEv", CCSBotManager::GetLooseBomb),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager16GetLooseBombAreaEv", CCSBotManager::GetLooseBombArea),
	HOOK_SYMBOLDEF(0x01D258D0, "_ZN13CCSBotManager12SetLooseBombEP11CBaseEntity", CCSBotManager::SetLooseBomb),
	HOOK_SYMBOLDEF(0x01D25A10, "_ZNK13CCSBotManager24GetRadioMessageTimestampE13GameEventTypei", CCSBotManager::GetRadioMessageTimestamp),
	HOOK_SYMBOLDEF(0x01D25A40, "_ZNK13CCSBotManager23GetRadioMessageIntervalE13GameEventTypei", CCSBotManager::GetRadioMessageInterval),
	HOOK_SYMBOLDEF(0x01D25A70, "_ZN13CCSBotManager24SetRadioMessageTimestampE13GameEventTypei", CCSBotManager::SetRadioMessageTimestamp),
	//HOOK_SYMBOLDEF(0x01D25AA0, "_ZN13CCSBotManager27ResetRadioMessageTimestampsEv", CCSBotManager::ResetRadioMessageTimestamps),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager25GetLastSeenEnemyTimestampEv", CCSBotManager::GetLastSeenEnemyTimestamp),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager25SetLastSeenEnemyTimestampEv", CCSBotManager::SetLastSeenEnemyTimestamp),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager17GetRoundStartTimeEv", CCSBotManager::GetRoundStartTime),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager19GetElapsedRoundTimeEv", CCSBotManager::GetElapsedRoundTime),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager11AllowRoguesEv", CCSBotManager::AllowRogues),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager12AllowPistolsEv", CCSBotManager::AllowPistols),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager13AllowShotgunsEv", CCSBotManager::AllowShotguns),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager19AllowSubMachineGunsEv", CCSBotManager::AllowSubMachineGuns),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager11AllowRiflesEv", CCSBotManager::AllowRifles),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager16AllowMachineGunsEv", CCSBotManager::AllowMachineGuns),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager13AllowGrenadesEv", CCSBotManager::AllowGrenades),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager12AllowSnipersEv", CCSBotManager::AllowSnipers),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager19AllowTacticalShieldEv", CCSBotManager::AllowTacticalShield),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager23AllowFriendlyFireDamageEv", CCSBotManager::AllowFriendlyFireDamage),
	HOOK_SYMBOLDEF(0x01D232D0, "_ZN13CCSBotManager15IsWeaponUseableEP15CBasePlayerItem", CCSBotManager::IsWeaponUseable),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager16IsDefenseRushingEv", CCSBotManager::IsDefenseRushing),
	//HOOK_SYMBOLDEF(0x01D23410, "_ZNK13CCSBotManager11IsOnDefenseEPK11CBasePlayer", CCSBotManager::IsOnDefense),			// NOXREF
	HOOK_SYMBOLDEF(0x01D23460, "_ZNK13CCSBotManager11IsOnOffenseEPK11CBasePlayer", CCSBotManager::IsOnOffense),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager11IsRoundOverEv", CCSBotManager::IsRoundOver),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CCSBotManager11GetNavPlaceEv", CCSBotManager::GetNavPlace),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager11SetNavPlaceEj", CCSBotManager::SetNavPlace),
	//HOOK_SYMBOLDEF(0x01D24D10, "_ZN13CCSBotManager15MonitorBotCVarsEv", CCSBotManager::MonitorBotCVars),			// NOXREF
	HOOK_SYMBOLDEF(0x01D24AE0, "_ZN13CCSBotManager16MaintainBotQuotaEv", CCSBotManager::MaintainBotQuota),
	//HOOK_SYMBOLDEF(0x0, "_ZN13CCSBotManager16GetRandomBotNameENS_9SkillTypeE", CCSBotManager::GetRandomBotName),
	HOOK_SYMBOLDEF(0x01D25270, "_ZN13CCSBotManager6AddBotEPK10BotProfile18BotProfileTeamType", CCSBotManager::AddBot),
	HOOK_SYMBOLDEF(0x01D248B0, "_ZN13CCSBotManager13BotAddCommandE18BotProfileTeamTypeb", CCSBotManager::BotAddCommand),
	//HOOK_SYMBOLDEF(0x01D238A0, "_Z16PrintAllEntitiesv", PrintAllEntities),	// NOXREF
	HOOK_SYMBOLDEF(0x01D23020, "_Z12UTIL_DrawBoxP6Extentiiii", UTIL_DrawBox),
//CCSBot
	//HOOK_SYMBOLDEF(0x01D208C0, "_ZN6CCSBotC2Ev", CCSBot::CCSBot),
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D173D0, "_ZN6CCSBot10TakeDamageEP9entvars_sS1_fi", CCSBot::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D175A0, "_ZN6CCSBot6KilledEP9entvars_si", CCSBot::Killed),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D20EC0, "_ZN6CCSBot12RoundRespawnEv", CCSBot::RoundRespawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D30A80, "_ZN6CCSBot5BlindEfffi", CCSBot::Blind),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D32370, "_ZN6CCSBot16OnTouchingWeaponEP10CWeaponBox", CCSBot::OnTouchingWeapon),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D20A60, "_ZN6CCSBot10InitializeEPK10BotProfile", CCSBot::Initialize),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D20E40, "_ZN6CCSBot8SpawnBotEv", CCSBot::SpawnBot),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D2D370, "_ZN6CCSBot6UpkeepEv", CCSBot::Upkeep),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D2D9B0, "_ZN6CCSBot6UpdateEv", CCSBot::Update),	// using refs		HOOK: FIX ME
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D17370, "_ZN6CCSBot4WalkEv", CCSBot::Walk),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D173A0, "_ZN6CCSBot4JumpEb", CCSBot::Jump),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D1F990, "_ZN6CCSBot7OnEventE13GameEventTypeP11CBaseEntityS2_", CCSBot::OnEvent),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D2F490, "_ZNK6CCSBot9IsVisibleEPK6Vectorb", CCSBot::IsVisible, bool (const Vector *, bool) const),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D2F5C0, "_ZNK6CCSBot9IsVisibleEP11CBasePlayerbPh", CCSBot::IsVisible, bool (CBasePlayer *, bool, unsigned char *) const),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D21390, "_ZNK6CCSBot18IsEnemyPartVisibleEN4CBot15VisiblePartTypeE", CCSBot::IsEnemyPartVisible),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D20EE0, "_ZN6CCSBot10DisconnectEv", CCSBot::Disconnect),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot14GetCombatRangeEv", CCSBot::GetCombatRange),
	HOOK_SYMBOLDEF(0x01D184D0, "_ZNK6CCSBot7IsRogueEv", CCSBot::IsRogue),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot8SetRogueEb", CCSBot::SetRogue),
	HOOK_SYMBOLDEF(0x01D185C0, "_ZNK6CCSBot10IsHurryingEv", CCSBot::IsHurrying),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot5HurryEf", CCSBot::Hurry),
	HOOK_SYMBOLDEF(0x01D18620, "_ZNK6CCSBot6IsSafeEv", CCSBot::IsSafe),
	HOOK_SYMBOLDEF(0x01D18650, "_ZNK6CCSBot14IsWellPastSafeEv", CCSBot::IsWellPastSafe),
	HOOK_SYMBOLDEF(0x01D18680, "_ZNK6CCSBot15IsEndOfSafeTimeEv", CCSBot::IsEndOfSafeTime),
	HOOK_SYMBOLDEF(0x01D186C0, "_ZNK6CCSBot20GetSafeTimeRemainingEv", CCSBot::GetSafeTimeRemaining),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot11GetSafeTimeEv", CCSBot::GetSafeTime),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot11IsUnhealthyEv", CCSBot::IsUnhealthy),					// NOXREF
	HOOK_SYMBOLDEF(0x01D2BE50, "_ZN6CCSBot4IdleEv", CCSBot::Idle),
	HOOK_SYMBOLDEF(0x01D2C360, "_ZN6CCSBot4HideEP8CNavAreaffb", CCSBot::Hide, void (CNavArea *, float, float, bool)),
	HOOK_SYMBOLDEF(0x01D2C620, "_ZN6CCSBot4HideEPK6Vectorfb", CCSBot::Hide, void (const Vector *, float, bool)),
	HOOK_SYMBOLDEF(0x01D2C830, "_ZN6CCSBot9TryToHideEP8CNavAreaffbb", CCSBot::TryToHide),
	HOOK_SYMBOLDEF(0x01D2CA10, "_ZN6CCSBot12TryToRetreatEv", CCSBot::TryToRetreat),
	HOOK_SYMBOLDEF(0x01D2CEA0, "_ZNK6CCSBot8IsHidingEv", CCSBot::IsHiding),
	HOOK_SYMBOLDEF(0x01D2CEC0, "_ZNK6CCSBot14IsAtHidingSpotEv", CCSBot::IsAtHidingSpot),
	HOOK_SYMBOLDEF(0x01D2CA90, "_ZN6CCSBot4HuntEv", CCSBot::Hunt),
	HOOK_SYMBOLDEF(0x01D2CEE0, "_ZNK6CCSBot9IsHuntingEv", CCSBot::IsHunting),
	HOOK_SYMBOLDEF(0x01D2CB60, "_ZN6CCSBot6AttackEP11CBasePlayer", CCSBot::Attack),
	HOOK_SYMBOLDEF(0x01D30B70, "_ZN6CCSBot17FireWeaponAtEnemyEv", CCSBot::FireWeaponAtEnemy),
	HOOK_SYMBOLDEF(0x01D2CD80, "_ZN6CCSBot13StopAttackingEv", CCSBot::StopAttacking),
	HOOK_SYMBOLDEF(0x01D2CE50, "_ZNK6CCSBot11IsAttackingEv", CCSBot::IsAttacking),
	HOOK_SYMBOLDEF(0x01D2CF40, "_ZN6CCSBot6MoveToEPK6Vector9RouteType", CCSBot::MoveTo),
	//HOOK_SYMBOLDEF(0x01D2CF00, "_ZNK6CCSBot10IsMovingToEv", CCSBot::IsMovingTo),					// NOXREF
	HOOK_SYMBOLDEF(0x01D2D030, "_ZN6CCSBot9PlantBombEv", CCSBot::PlantBomb),
	HOOK_SYMBOLDEF(0x01D2D100, "_ZN6CCSBot9FetchBombEv", CCSBot::FetchBomb),
	HOOK_SYMBOLDEF(0x01D17EA0, "_ZNK6CCSBot15NoticeLooseBombEv", CCSBot::NoticeLooseBomb),
	HOOK_SYMBOLDEF(0x01D17EC0, "_ZNK6CCSBot15CanSeeLooseBombEv", CCSBot::CanSeeLooseBomb),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot14IsCarryingBombEv", CCSBot::IsCarryingBomb),
	HOOK_SYMBOLDEF(0x01D2D1D0, "_ZN6CCSBot10DefuseBombEv", CCSBot::DefuseBomb),
	HOOK_SYMBOLDEF(0x01D2CE80, "_ZNK6CCSBot14IsDefusingBombEv", CCSBot::IsDefusingBomb),
	HOOK_SYMBOLDEF(0x01D17F00, "_ZNK6CCSBot17CanSeePlantedBombEv", CCSBot::CanSeePlantedBomb),
	HOOK_SYMBOLDEF(0x01D2BF10, "_ZN6CCSBot14EscapeFromBombEv", CCSBot::EscapeFromBomb),
	HOOK_SYMBOLDEF(0x01D2CE60, "_ZNK6CCSBot18IsEscapingFromBombEv", CCSBot::IsEscapingFromBomb),
	//HOOK_SYMBOLDEF(0x01D2C260, "_ZN6CCSBot14RescueHostagesEv", CCSBot::RescueHostages),				// NOXREF
	HOOK_SYMBOLDEF(0x01D2C280, "_ZN6CCSBot9UseEntityEP11CBaseEntity", CCSBot::UseEntity),
	HOOK_SYMBOLDEF(0x01D2CF20, "_ZNK6CCSBot8IsBuyingEv", CCSBot::IsBuying),
	HOOK_SYMBOLDEF(0x01D17B80, "_ZN6CCSBot5PanicEP11CBasePlayer", CCSBot::Panic),
	HOOK_SYMBOLDEF(0x01D2BFF0, "_ZN6CCSBot6FollowEP11CBasePlayer", CCSBot::Follow),
	HOOK_SYMBOLDEF(0x01D2C130, "_ZN6CCSBot17ContinueFollowingEv", CCSBot::ContinueFollowing),
	HOOK_SYMBOLDEF(0x01D2C230, "_ZN6CCSBot13StopFollowingEv", CCSBot::StopFollowing),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot11IsFollowingEv", CCSBot::IsFollowing),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot15GetFollowLeaderEv", CCSBot::GetFollowLeader),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot17GetFollowDurationEv", CCSBot::GetFollowDuration),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot13CanAutoFollowEv", CCSBot::CanAutoFollow),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot11IsNotMovingEv", CCSBot::IsNotMoving),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot10AimAtEnemyEv", CCSBot::AimAtEnemy),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot10StopAimingEv", CCSBot::StopAiming),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot15IsAimingAtEnemyEv", CCSBot::IsAimingAtEnemy),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot11IsSurprisedEv", CCSBot::IsSurprised),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot16GetSurpriseDelayEv", CCSBot::GetSurpriseDelay),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot18ClearSurpriseDelayEv", CCSBot::ClearSurpriseDelay),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot17GetStateTimestampEv", CCSBot::GetStateTimestamp),
	HOOK_SYMBOLDEF(0x01D17E70, "_ZNK6CCSBot15IsDoingScenarioEv", CCSBot::IsDoingScenario),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12GetGameStateEv", CCSBot::GetGameState, const CSGameState *() const),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot12GetGameStateEv", CCSBot::GetGameState, CSGameState *()),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot12IsAtBombsiteEv", CCSBot::IsAtBombsite),
	HOOK_SYMBOLDEF(0x01D18740, "_ZN6CCSBot15GuardRandomZoneEf", CCSBot::GuardRandomZone),
	HOOK_SYMBOLDEF(0x01D17900, "_ZNK6CCSBot6IsBusyEv", CCSBot::IsBusy),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot7SetTaskENS_8TaskTypeEP11CBaseEntity", CCSBot::SetTask),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot7GetTaskEv", CCSBot::GetTask),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot13GetTaskEntityEv", CCSBot::GetTaskEntity),
	HOOK_SYMBOLDEF(0x01D18420, "_ZN6CCSBot14SetDispositionENS_15DispositionTypeE", CCSBot::SetDisposition),
	HOOK_SYMBOLDEF(0x01D18440, "_ZNK6CCSBot14GetDispositionEv", CCSBot::GetDisposition),
	HOOK_SYMBOLDEF(0x01D18470, "_ZN6CCSBot13IgnoreEnemiesEf", CCSBot::IgnoreEnemies),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot9GetMoraleEv", CCSBot::GetMorale),
	HOOK_SYMBOLDEF(0x01D18490, "_ZN6CCSBot14IncreaseMoraleEv", CCSBot::IncreaseMorale),
	HOOK_SYMBOLDEF(0x01D184B0, "_ZN6CCSBot14DecreaseMoraleEv", CCSBot::DecreaseMorale),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12IsNoiseHeardEv", CCSBot::IsNoiseHeard),
	HOOK_SYMBOLDEF(0x01D22510, "_ZN6CCSBot22ShouldInvestigateNoiseEPf", CCSBot::ShouldInvestigateNoise),
	HOOK_SYMBOLDEF(0x01D2D2A0, "_ZN6CCSBot16InvestigateNoiseEv", CCSBot::InvestigateNoise),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot16GetNoisePositionEv", CCSBot::GetNoisePosition),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12GetNoiseAreaEv", CCSBot::GetNoiseArea),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot11ForgetNoiseEv", CCSBot::ForgetNoise),
	//HOOK_SYMBOLDEF(0x01D229C0, "_ZNK6CCSBot19CanSeeNoisePositionEv", CCSBot::CanSeeNoisePosition),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot13GetNoiseRangeEv", CCSBot::GetNoiseRange),					// NOXREF
	HOOK_SYMBOLDEF(0x01D227C0, "_ZNK6CCSBot25CanHearNearbyEnemyGunfireEf", CCSBot::CanHearNearbyEnemyGunfire),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot16GetNoisePriorityEv", CCSBot::GetNoisePriority),
	HOOK_SYMBOLDEF(0x01D2BC80, "_ZN6CCSBot16SendRadioMessageE13GameEventType", CCSBot::SendRadioMessage),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot10GetChatterEv", CCSBot::GetChatter),
	HOOK_SYMBOLDEF(0x01D2BA70, "_ZN6CCSBot20RespondToHelpRequestEP11CBasePlayerjf", CCSBot::RespondToHelpRequest),
	HOOK_SYMBOLDEF(0x01D2B970, "_ZN6CCSBot18StartVoiceFeedbackEf", CCSBot::StartVoiceFeedback),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12IsUsingVoiceEv", CCSBot::IsUsingVoice),
	HOOK_SYMBOLDEF(0x01D179D0, "_ZN6CCSBot8SetEnemyEP11CBasePlayer", CCSBot::SetEnemy),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot8GetEnemyEv", CCSBot::GetEnemy),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot19GetNearbyEnemyCountEv", CCSBot::GetNearbyEnemyCount),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot13GetEnemyPlaceEv", CCSBot::GetEnemyPlace),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12CanSeeBomberEv", CCSBot::CanSeeBomber),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot9GetBomberEv", CCSBot::GetBomber),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot20GetNearbyFriendCountEv", CCSBot::GetNearbyFriendCount),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot23GetClosestVisibleFriendEv", CCSBot::GetClosestVisibleFriend),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot28GetClosestVisibleHumanFriendEv", CCSBot::GetClosestVisibleHumanFriend),
	HOOK_SYMBOLDEF(0x01D181A0, "_ZNK6CCSBot13IsOutnumberedEv", CCSBot::IsOutnumbered),
	HOOK_SYMBOLDEF(0x01D181F0, "_ZNK6CCSBot16OutnumberedCountEv", CCSBot::OutnumberedCount),
	HOOK_SYMBOLDEF(0x01D18290, "_ZNK6CCSBot17GetImportantEnemyEb", CCSBot::GetImportantEnemy),
	HOOK_SYMBOLDEF(0x01D30830, "_ZN6CCSBot19UpdateReactionQueueEv", CCSBot::UpdateReactionQueue),
	HOOK_SYMBOLDEF(0x01D30980, "_ZN6CCSBot18GetRecognizedEnemyEv", CCSBot::GetRecognizedEnemy),
	HOOK_SYMBOLDEF(0x01D309B0, "_ZN6CCSBot26IsRecognizedEnemyReloadingEv", CCSBot::IsRecognizedEnemyReloading),
	HOOK_SYMBOLDEF(0x01D309E0, "_ZN6CCSBot34IsRecognizedEnemyProtectedByShieldEv", CCSBot::IsRecognizedEnemyProtectedByShield),
	//HOOK_SYMBOLDEF(0x01D30A10, "_ZN6CCSBot32GetRangeToNearestRecognizedEnemyEv", CCSBot::GetRangeToNearestRecognizedEnemy),		// NOXREF
	HOOK_SYMBOLDEF(0x01D17F40, "_ZNK6CCSBot11GetAttackerEv", CCSBot::GetAttacker),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot20GetTimeSinceAttackedEv", CCSBot::GetTimeSinceAttacked),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot25GetFirstSawEnemyTimestampEv", CCSBot::GetFirstSawEnemyTimestamp),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot24GetLastSawEnemyTimestampEv", CCSBot::GetLastSawEnemyTimestamp),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot24GetTimeSinceLastSawEnemyEv", CCSBot::GetTimeSinceLastSawEnemy),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot32GetTimeSinceAcquiredCurrentEnemyEv", CCSBot::GetTimeSinceAcquiredCurrentEnemy),
	HOOK_SYMBOLDEF(0x01D18710, "_ZNK6CCSBot26HasNotSeenEnemyForLongTimeEv", CCSBot::HasNotSeenEnemyForLongTime),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot25GetLastKnownEnemyPositionEv", CCSBot::GetLastKnownEnemyPosition),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot14IsEnemyVisibleEv", CCSBot::IsEnemyVisible),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot22GetEnemyDeathTimestampEv", CCSBot::GetEnemyDeathTimestamp),
	HOOK_SYMBOLDEF(0x01D32440, "_ZN6CCSBot20IsFriendInLineOfFireEv", CCSBot::IsFriendInLineOfFire),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot19IsAwareOfEnemyDeathEv", CCSBot::IsAwareOfEnemyDeath),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot15GetLastVictimIDEv", CCSBot::GetLastVictimID),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot7HasPathEv", CCSBot::HasPath),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot11DestroyPathEv", CCSBot::DestroyPath),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot8GetFeetZEv", CCSBot::GetFeetZ),
	HOOK_SYMBOLDEF(0x01D29C80, "_ZN6CCSBot18UpdatePathMovementEb", CCSBot::UpdatePathMovement),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot11AStarSearchEP8CNavAreaS1_", CCSBot::AStarSearch), // NOXREF
	HOOK_SYMBOLDEF(0x01D2A7D0, "_ZN6CCSBot11ComputePathEP8CNavAreaPK6Vector9RouteType", CCSBot::ComputePath),
	HOOK_SYMBOLDEF(0x01D17A10, "_ZN6CCSBot13StayOnNavMeshEv", CCSBot::StayOnNavMesh),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot16GetLastKnownAreaEv", CCSBot::GetLastKnownArea),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot15GetPathEndpointEv", CCSBot::GetPathEndpoint),
	HOOK_SYMBOLDEF(0x01D2ADE0, "_ZNK6CCSBot24GetPathDistanceRemainingEv", CCSBot::GetPathDistanceRemaining),
	HOOK_SYMBOLDEF(0x01D25BC0, "_ZN6CCSBot17ResetStuckMonitorEv", CCSBot::ResetStuckMonitor),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot13IsAreaVisibleEPK8CNavArea", CCSBot::IsAreaVisible), // NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot15GetPathPositionEi", CCSBot::GetPathPosition), // NOXREF
	HOOK_SYMBOLDEF(0x01D25FE0, "_ZN6CCSBot30GetSimpleGroundHeightWithFloorEPK6VectorPfPS0_", CCSBot::GetSimpleGroundHeightWithFloor),
	HOOK_SYMBOLDEF(0x01D26060, "_ZNK6CCSBot8GetPlaceEv", CCSBot::GetPlace),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot13IsUsingLadderEv", CCSBot::IsUsingLadder),
	HOOK_SYMBOLDEF(0x01D17F70, "_ZN6CCSBot12GetOffLadderEv", CCSBot::GetOffLadder),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot13SetGoalEntityEP11CBaseEntity", CCSBot::SetGoalEntity),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot13GetGoalEntityEv", CCSBot::GetGoalEntity),
	HOOK_SYMBOLDEF(0x01D291D0, "_ZNK6CCSBot10IsNearJumpEv", CCSBot::IsNearJump),
	HOOK_SYMBOLDEF(0x01D29230, "_ZNK6CCSBot24GetApproximateFallDamageEf", CCSBot::GetApproximateFallDamage),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot8ForceRunEf", CCSBot::ForceRun),
	HOOK_SYMBOLDEF(0x01D26720, "_ZN6CCSBot6WiggleEv", CCSBot::Wiggle),
	HOOK_SYMBOLDEF(0x01D29260, "_ZNK6CCSBot16IsFriendInTheWayEPK6Vector", CCSBot::IsFriendInTheWay),
	HOOK_SYMBOLDEF(0x01D29500, "_ZN6CCSBot22FeelerReflexAdjustmentEP6Vector", CCSBot::FeelerReflexAdjustment),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot13SetLookAnglesEff", CCSBot::SetLookAngles),
	//HOOK_SYMBOLDEF(0x01D2EDD0, "_ZN6CCSBot16UpdateLookAnglesEv", CCSBot::UpdateLookAngles),	// Using REFS FIXME
	HOOK_SYMBOLDEF(0x01D2F9C0, "_ZN6CCSBot16UpdateLookAroundEb", CCSBot::UpdateLookAround),
	HOOK_SYMBOLDEF(0x01D2F910, "_ZN6CCSBot17InhibitLookAroundEf", CCSBot::InhibitLookAround),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot15SetForwardAngleEf", CCSBot::SetForwardAngle), // NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot17SetLookAheadAngleEf", CCSBot::SetLookAheadAngle), // NOXREF
	HOOK_SYMBOLDEF(0x01D2F7F0, "_ZN6CCSBot9SetLookAtEPKcPK6Vector12PriorityTypefbf", CCSBot::SetLookAt),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot11ClearLookAtEv", CCSBot::ClearLookAt),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot15IsLookingAtSpotE12PriorityType", CCSBot::IsLookingAtSpot),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12IsViewMovingEf", CCSBot::IsViewMoving),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot14GetEyePositionEv", CCSBot::GetEyePosition),
	HOOK_SYMBOLDEF(0x01D32560, "_ZN6CCSBot23ComputeWeaponSightRangeEv", CCSBot::ComputeWeaponSightRange),
	HOOK_SYMBOLDEF(0x01D26890, "_ZN6CCSBot21ComputeApproachPointsEv", CCSBot::ComputeApproachPoints),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot20UpdateApproachPointsEv", CCSBot::UpdateApproachPoints),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot19ClearApproachPointsEv", CCSBot::ClearApproachPoints),
	HOOK_SYMBOLDEF(0x01D269D0, "_ZN6CCSBot18DrawApproachPointsEv", CCSBot::DrawApproachPoints),
	HOOK_SYMBOLDEF(0x01D17FA0, "_ZNK6CCSBot27GetHidingSpotCheckTimestampEP10HidingSpot", CCSBot::GetHidingSpotCheckTimestamp),
	HOOK_SYMBOLDEF(0x01D17FF0, "_ZN6CCSBot27SetHidingSpotCheckTimestampEP10HidingSpot", CCSBot::SetHidingSpotCheckTimestamp),
	HOOK_SYMBOLDEF(0x01D315F0, "_ZN6CCSBot15EquipBestWeaponEb", CCSBot::EquipBestWeapon),
	HOOK_SYMBOLDEF(0x01D31810, "_ZN6CCSBot11EquipPistolEv", CCSBot::EquipPistol),
	HOOK_SYMBOLDEF(0x01D318E0, "_ZN6CCSBot10EquipKnifeEv", CCSBot::EquipKnife),
	HOOK_SYMBOLDEF(0x01D31930, "_ZN6CCSBot12EquipGrenadeEb", CCSBot::EquipGrenade),
	HOOK_SYMBOLDEF(0x01D31A00, "_ZNK6CCSBot12IsUsingKnifeEv", CCSBot::IsUsingKnife),
	HOOK_SYMBOLDEF(0x01D31A20, "_ZNK6CCSBot13IsUsingPistolEv", CCSBot::IsUsingPistol),
	HOOK_SYMBOLDEF(0x01D31A60, "_ZNK6CCSBot14IsUsingGrenadeEv", CCSBot::IsUsingGrenade),
	HOOK_SYMBOLDEF(0x01D313F0, "_ZNK6CCSBot18IsUsingSniperRifleEv", CCSBot::IsUsingSniperRifle),
	HOOK_SYMBOLDEF(0x01D313A0, "_ZNK6CCSBot10IsUsingAWPEv", CCSBot::IsUsingAWP),
	HOOK_SYMBOLDEF(0x01D31440, "_ZNK6CCSBot8IsSniperEv", CCSBot::IsSniper),
	HOOK_SYMBOLDEF(0x01D314B0, "_ZNK6CCSBot9IsSnipingEv", CCSBot::IsSniping),
	HOOK_SYMBOLDEF(0x01D314D0, "_ZNK6CCSBot14IsUsingShotgunEv", CCSBot::IsUsingShotgun),
	HOOK_SYMBOLDEF(0x01D31500, "_ZNK6CCSBot17IsUsingMachinegunEv", CCSBot::IsUsingMachinegun),
	HOOK_SYMBOLDEF(0x01D31AB0, "_ZN6CCSBot12ThrowGrenadeEPK6Vector", CCSBot::ThrowGrenade),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot17IsThrowingGrenadeEv", CCSBot::IsThrowingGrenade),
	HOOK_SYMBOLDEF(0x01D31920, "_ZNK6CCSBot10HasGrenadeEv", CCSBot::HasGrenade),
	//HOOK_SYMBOLDEF(0x01D313C0, "_ZNK6CCSBot28DoesActiveWeaponHaveSilencerEv", CCSBot::DoesActiveWeaponHaveSilencer),		// NOXREF
	HOOK_SYMBOLDEF(0x01D31A90, "_ZNK6CCSBot16IsUsingHEGrenadeEv", CCSBot::IsUsingHEGrenade),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot14StartRapidFireEv", CCSBot::StartRapidFire),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot13StopRapidFireEv", CCSBot::StopRapidFire),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot13IsRapidFiringEv", CCSBot::IsRapidFiring),
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot12GetZoomLevelEv", CCSBot::GetZoomLevel),
	HOOK_SYMBOLDEF(0x01D31280, "_ZN6CCSBot10AdjustZoomEf", CCSBot::AdjustZoom),
	HOOK_SYMBOLDEF(0x01D31520, "_ZNK6CCSBot20IsPrimaryWeaponEmptyEv", CCSBot::IsPrimaryWeaponEmpty),
	//HOOK_SYMBOLDEF(0x01D31550, "_ZNK6CCSBot13IsPistolEmptyEv", CCSBot::IsPistolEmpty),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK6CCSBot21GetHostageEscortCountEv", CCSBot::GetHostageEscortCount),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot26IncreaseHostageEscortCountEv", CCSBot::IncreaseHostageEscortCount),			// NOXREF
	HOOK_SYMBOLDEF(0x01D18B10, "_ZNK6CCSBot33GetRangeToFarthestEscortedHostageEv", CCSBot::GetRangeToFarthestEscortedHostage),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot27ResetWaitForHostagePatienceEv", CCSBot::ResetWaitForHostagePatience),
	HOOK_SYMBOLDEF(0x01D20AE0, "_ZN6CCSBot11ResetValuesEv", CCSBot::ResetValues),
	//HOOK_SYMBOLDEF(0x01D17950, "_ZN6CCSBot13BotDeathThinkEv", CCSBot::BotDeathThink),					// PURE
	//HOOK_SYMBOLDEF(0x01D17960, "_ZN6CCSBot16FindNearbyPlayerEv", CCSBot::FindNearbyPlayer),					// NOXREF
	HOOK_SYMBOLDEF(0x01D186E0, "_ZN6CCSBot14AdjustSafeTimeEv", CCSBot::AdjustSafeTime),
	HOOK_SYMBOLDEF(0x01D2BD80, "_ZN6CCSBot8SetStateEP8BotState", CCSBot::SetState),
	HOOK_SYMBOLDEF(0x01D26080, "_ZN6CCSBot19MoveTowardsPositionEPK6Vector", CCSBot::MoveTowardsPosition),
	//HOOK_SYMBOLDEF(0x01D26510, "_ZN6CCSBot20MoveAwayFromPositionEPK6Vector", CCSBot::MoveAwayFromPosition),			// NOXREF
	HOOK_SYMBOLDEF(0x01D26650, "_ZN6CCSBot22StrafeAwayFromPositionEPK6Vector", CCSBot::StrafeAwayFromPosition),
	HOOK_SYMBOLDEF(0x01D25C50, "_ZN6CCSBot10StuckCheckEv", CCSBot::StuckCheck),
	HOOK_SYMBOLDEF(0x01D2A6F0, "_ZN6CCSBot16BuildTrivialPathEPK6Vector", CCSBot::BuildTrivialPath),
	HOOK_SYMBOLDEF(0x01D26BA0, "_ZN6CCSBot20ComputePathPositionsEv", CCSBot::ComputePathPositions),
	HOOK_SYMBOLDEF(0x01D27040, "_ZN6CCSBot19SetupLadderMovementEv", CCSBot::SetupLadderMovement),
	HOOK_SYMBOLDEF(0x01D29130, "_ZN6CCSBot12SetPathIndexEi", CCSBot::SetPathIndex),
	HOOK_SYMBOLDEF(0x01D2AE70, "_ZN6CCSBot8DrawPathEv", CCSBot::DrawPath),
	HOOK_SYMBOLDEF(0x01D282C0, "_ZNK6CCSBot21FindOurPositionOnPathEP6Vectorb", CCSBot::FindOurPositionOnPath),
	HOOK_SYMBOLDEF(0x01D28620, "_ZN6CCSBot13FindPathPointEfP6VectorPi", CCSBot::FindPathPoint),
	//HOOK_SYMBOLDEF(0x01D280B0, "_ZNK6CCSBot22FindClosestPointOnPathEPK6VectoriiPS0_", CCSBot::FindClosestPointOnPath),		// NOXREF
	HOOK_SYMBOLDEF(0x01D28610, "_ZNK6CCSBot26IsStraightLinePathWalkableEPK6Vector", CCSBot::IsStraightLinePathWalkable),
	HOOK_SYMBOLDEF(0x01D25EE0, "_ZN6CCSBot17DiscontinuityJumpEfbb", CCSBot::DiscontinuityJump),
	HOOK_SYMBOLDEF(0x01D27560, "_ZN6CCSBot20UpdateLadderMovementEv", CCSBot::UpdateLadderMovement),
	HOOK_SYMBOLDEF(0x01D27450, "_ZN6CCSBot21ComputeLadderEndpointEb", CCSBot::ComputeLadderEndpoint),
	HOOK_SYMBOLDEF(0x01D180B0, "_ZN6CCSBot24UpdateHostageEscortCountEv", CCSBot::UpdateHostageEscortCount),
	HOOK_SYMBOLDEF(0x01D22A70, "_ZN6CCSBot17UpdateLookAtNoiseEv", CCSBot::UpdateLookAtNoise),
	HOOK_SYMBOLDEF(0x01D2F760, "_ZN6CCSBot12UpdateLookAtEv", CCSBot::UpdateLookAt),
	HOOK_SYMBOLDEF(0x01D2F930, "_ZN6CCSBot22UpdatePeripheralVisionEv", CCSBot::UpdatePeripheralVision),
	HOOK_SYMBOLDEF(0x01D2FF40, "_ZNK6CCSBot15BendLineOfSightEPK6VectorS2_PS0_", CCSBot::BendLineOfSight),
	//HOOK_SYMBOLDEF(0x01D26A50, "_ZN6CCSBot28FindApproachPointNearestPathEP6Vector", CCSBot::FindApproachPointNearestPath),		// NOXREF
	HOOK_SYMBOLDEF(0x01D31B30, "_ZN6CCSBot25FindGrenadeTossPathTargetEP6Vector", CCSBot::FindGrenadeTossPathTarget),
	HOOK_SYMBOLDEF(0x01D31030, "_ZN6CCSBot12SetAimOffsetEf", CCSBot::SetAimOffset),
	HOOK_SYMBOLDEF(0x01D311E0, "_ZN6CCSBot15UpdateAimOffsetEv", CCSBot::UpdateAimOffset),
	HOOK_SYMBOLDEF(0x01D31580, "_ZN6CCSBot7DoEquipEP17CBasePlayerWeapon", CCSBot::DoEquip),
	HOOK_SYMBOLDEF(0x01D31FC0, "_ZN6CCSBot11ReloadCheckEv", CCSBot::ReloadCheck),
	HOOK_SYMBOLDEF(0x01D32290, "_ZN6CCSBot13SilencerCheckEv", CCSBot::SilencerCheck),
	HOOK_SYMBOLDEF(0x01D302D0, "_ZN6CCSBot23FindMostDangerousThreatEv", CCSBot::FindMostDangerousThreat),
	HOOK_SYMBOLDEF(0x01D2B5B0, "_ZN6CCSBot22RespondToRadioCommandsEv", CCSBot::RespondToRadioCommands),
	//HOOK_SYMBOLDEF(0x01D2B570, "_ZNK6CCSBot14IsRadioCommandE13GameEventType", CCSBot::IsRadioCommand),		// NOXREF
	HOOK_SYMBOLDEF(0x01D2BA00, "_ZN6CCSBot16EndVoiceFeedbackEb", CCSBot::EndVoiceFeedback),
	HOOK_SYMBOLDEF(0x01D213C0, "_ZN6CCSBot7AddNodeEPK6VectorS2_10NavDirTypeP8CNavNode", CCSBot::AddNode),
	HOOK_SYMBOLDEF(0x01D21610, "_ZN6CCSBot17StartLearnProcessEv", CCSBot::StartLearnProcess),
	HOOK_SYMBOLDEF(0x01D21EF0, "_ZN6CCSBot18UpdateLearnProcessEv", CCSBot::UpdateLearnProcess),
	HOOK_SYMBOLDEF(0x01D21770, "_ZN6CCSBot9LearnStepEv", CCSBot::LearnStep),
	HOOK_SYMBOLDEF(0x01D21FE0, "_ZN6CCSBot24StartAnalyzeAlphaProcessEv", CCSBot::StartAnalyzeAlphaProcess),
	HOOK_SYMBOLDEF(0x01D22080, "_ZN6CCSBot25UpdateAnalyzeAlphaProcessEv", CCSBot::UpdateAnalyzeAlphaProcess),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot16AnalyzeAlphaStepEv", CCSBot::AnalyzeAlphaStep),
	//HOOK_SYMBOLDEF(0x01D221D0, "_ZN6CCSBot23StartAnalyzeBetaProcessEv", CCSBot::StartAnalyzeBetaProcess),		// NOXREF
	HOOK_SYMBOLDEF(0x01D22200, "_ZN6CCSBot24UpdateAnalyzeBetaProcessEv", CCSBot::UpdateAnalyzeBetaProcess),
	//HOOK_SYMBOLDEF(0x0, "_ZN6CCSBot15AnalyzeBetaStepEv", CCSBot::AnalyzeBetaStep),
	//HOOK_SYMBOLDEF(0x01D22330, "_ZN6CCSBot16StartSaveProcessEv", CCSBot::StartSaveProcess),				// NOXREF
	HOOK_SYMBOLDEF(0x01D22340, "_ZN6CCSBot17UpdateSaveProcessEv", CCSBot::UpdateSaveProcess),
	HOOK_SYMBOLDEF(0x01D22450, "_ZN6CCSBot18StartNormalProcessEv", CCSBot::StartNormalProcess),
	HOOK_SYMBOLDEF(0x01D17620, "_ZN6CCSBot8BotTouchEP11CBaseEntity", CCSBot::BotTouch),
//CSGameState
	//HOOK_SYMBOLDEF(0x01D326A0, "_ZN11CSGameStateC2EP6CCSBot", CSGameState::CSGameState),
	HOOK_SYMBOLDEF(0x01D32730, "_ZN11CSGameState5ResetEv", CSGameState::Reset),
	HOOK_SYMBOLDEF(0x01D327C0, "_ZN11CSGameState7OnEventE13GameEventTypeP11CBaseEntityS2_", CSGameState::OnEvent),
	HOOK_SYMBOLDEF(0x01D328D0, "_ZNK11CSGameState11IsRoundOverEv", CSGameState::IsRoundOver),
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState12IsBombMovingEv", CSGameState::IsBombMoving),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState11IsBombLooseEv", CSGameState::IsBombLoose),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState13IsBombPlantedEv", CSGameState::IsBombPlanted),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState13IsBombDefusedEv", CSGameState::IsBombDefused),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState14IsBombExplodedEv", CSGameState::IsBombExploded),					// NOXREF
	HOOK_SYMBOLDEF(0x01D32900, "_ZN11CSGameState15UpdateLooseBombEPK6Vector", CSGameState::UpdateLooseBomb),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D32940, "_ZNK11CSGameState25TimeSinceLastSawLooseBombEv", CSGameState::TimeSinceLastSawLooseBomb),	// NOXREF
	HOOK_SYMBOLDEF(0x01D32970, "_ZNK11CSGameState24IsLooseBombLocationKnownEv", CSGameState::IsLooseBombLocationKnown),
	HOOK_SYMBOLDEF(0x01D329A0, "_ZN11CSGameState12UpdateBomberEPK6Vector", CSGameState::UpdateBomber),
	//HOOK_SYMBOLDEF(0x01D329E0, "_ZNK11CSGameState22TimeSinceLastSawBomberEv", CSGameState::TimeSinceLastSawBomber),		// NOXREF
	HOOK_SYMBOLDEF(0x01D32B20, "_ZN11CSGameState17UpdatePlantedBombEPK6Vector", CSGameState::UpdatePlantedBomb),
	HOOK_SYMBOLDEF(0x01D32A10, "_ZNK11CSGameState26IsPlantedBombLocationKnownEv", CSGameState::IsPlantedBombLocationKnown),
	HOOK_SYMBOLDEF(0x01D32B80, "_ZN11CSGameState21MarkBombsiteAsPlantedEi", CSGameState::MarkBombsiteAsPlanted),
	HOOK_SYMBOLDEF(0x01D32A20, "_ZNK11CSGameState18GetPlantedBombsiteEv", CSGameState::GetPlantedBombsite),
	HOOK_SYMBOLDEF(0x01D32A30, "_ZNK11CSGameState19IsAtPlantedBombsiteEv", CSGameState::IsAtPlantedBombsite),
	HOOK_SYMBOLDEF(0x01D32A70, "_ZN11CSGameState23GetNextBombsiteToSearchEv", CSGameState::GetNextBombsiteToSearch),
	HOOK_SYMBOLDEF(0x01D32BC0, "_ZNK11CSGameState15IsBombsiteClearEi", CSGameState::IsBombsiteClear),
	HOOK_SYMBOLDEF(0x01D32BA0, "_ZN11CSGameState13ClearBombsiteEi", CSGameState::ClearBombsite),
	HOOK_SYMBOLDEF(0x01D32AC0, "_ZNK11CSGameState15GetBombPositionEv", CSGameState::GetBombPosition),
	HOOK_SYMBOLDEF(0x01D32CC0, "_ZNK11CSGameState21GetNearestFreeHostageEP6Vector", CSGameState::GetNearestFreeHostage),
	HOOK_SYMBOLDEF(0x01D32EB0, "_ZNK11CSGameState28GetRandomFreeHostagePositionEv", CSGameState::GetRandomFreeHostagePosition),
	HOOK_SYMBOLDEF(0x01D33370, "_ZNK11CSGameState26AreAllHostagesBeingRescuedEv", CSGameState::AreAllHostagesBeingRescued),
	HOOK_SYMBOLDEF(0x01D33440, "_ZNK11CSGameState18AreAllHostagesGoneEv", CSGameState::AreAllHostagesGone),
	//HOOK_SYMBOLDEF(0x01D334A0, "_ZN11CSGameState15AllHostagesGoneEv", CSGameState::AllHostagesGone),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState25HaveSomeHostagesBeenTakenEv", CSGameState::HaveSomeHostagesBeenTaken),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11CSGameState15HostageWasTakenEv", CSGameState::HostageWasTaken),					// NOXREF
	HOOK_SYMBOLDEF(0x01D33210, "_ZNK11CSGameState28GetNearestVisibleFreeHostageEv", CSGameState::GetNearestVisibleFreeHostage),
	HOOK_SYMBOLDEF(0x01D32FA0, "_ZN11CSGameState24ValidateHostagePositionsEv", CSGameState::ValidateHostagePositions),
	//HOOK_SYMBOLDEF(0x01D328E0, "_ZN11CSGameState12SetBombStateENS_9BombStateE", CSGameState::SetBombState),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState12GetBombStateEv", CSGameState::GetBombState),						// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK11CSGameState17GetNearestHostageEv", CSGameState::GetNearestHostage),					// NOXREF
	HOOK_SYMBOLDEF(0x01D32BE0, "_ZN11CSGameState21InitializeHostageInfoEv", CSGameState::InitializeHostageInfo),
	//@HOOK_SYMBOLDEF(0x01D15EA0, "_Z16NavAreaBuildPathI8PathCostEbP8CNavAreaS2_PK6VectorRT_PS2_", NavAreaBuildPath__PathCost__wrapper),
	HOOK_SYMBOLDEF(0x01D15EA0, "_Z16NavAreaBuildPathI8PathCostEbP8CNavAreaS2_PK6VectorRT_PS2_", NavAreaBuildPath<PathCost>),

#ifdef _WIN32
	//@HOOK_DEF(0x01D15A30, NavAreaTravelDistance__PathCost__wrapper),
	HOOK_DEF(0x01D15A30, NavAreaTravelDistance<PathCost>, float_precision (CNavArea *startArea, CNavArea *endArea, PathCost &costFunc)),
#endif // _WIN32

	HOOK_SYMBOLDEF(0x01D2B2E0, "_ZN8PathCostclEP8CNavAreaS1_PK10CNavLadder", PathCost::operator()),
	HOOK_SYMBOLDEF(0x01D172A0, "_Z17GetBotFollowCountP11CBasePlayer", GetBotFollowCount),
	HOOK_SYMBOLDEF(0x01D187B0, "_Z21FindNearbyRetreatSpotP6CCSBotf", FindNearbyRetreatSpot, const Vector *(CCSBot *, float)),
	//HOOK_DEF(0x0, drawProgressMeter),		// NOXREF
	//HOOK_DEF(0x0, startProgressMeter),	// NOXREF
	//HOOK_DEF(0x0, hideProgressMeter),		// NOXREF

#endif // CS_Bot_Region

#ifndef CS_BotState_Region

//BotState
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN8BotState7OnEnterEP6CCSBot", BotState::OnEnter),			// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN8BotState8OnUpdateEP6CCSBot", BotState::OnUpdate),			// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D212B0, "_ZN8BotState6OnExitEP6CCSBot", BotState::OnExit),			// PURE
	//HOOK_SYMBOLDEF(0x0, "_ZNK8BotState7GetNameEv", BotState::GetName),				// NOXREF
//IdleState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D142A0, "_ZN9IdleState7OnEnterEP6CCSBot", IdleState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D14320, "_ZN9IdleState8OnUpdateEP6CCSBot", IdleState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D212C0, "_ZNK9IdleState7GetNameEv", IdleState::GetName),			// DEFAULT
//HuntState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D13E20, "_ZN9HuntState7OnEnterEP6CCSBot", HuntState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D13EA0, "_ZN9HuntState8OnUpdateEP6CCSBot", HuntState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D14290, "_ZN9HuntState6OnExitEP6CCSBot", HuntState::OnExit),		// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D212D0, "_ZNK9HuntState7GetNameEv", HuntState::GetName),		// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN9HuntState13ClearHuntAreaEv", HuntState::ClearHuntArea),		// NOXREF
//AttackState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10960, "_ZN11AttackState7OnEnterEP6CCSBot", AttackState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D10CF0, "_ZN11AttackState8OnUpdateEP6CCSBot", AttackState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D11860, "_ZN11AttackState6OnExitEP6CCSBot", AttackState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D212E0, "_ZNK11AttackState7GetNameEv", AttackState::GetName),	// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN11AttackState16SetCrouchAndHoldEb", AttackState::SetCrouchAndHold),		// NOXREF
	//HOOK_SYMBOLDEF(0x01D10CC0, "_ZN11AttackState13StopAttackingEP6CCSBot", AttackState::StopAttacking),	// NOXREF
//InvestigateNoiseState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D165C0, "_ZN21InvestigateNoiseState7OnEnterEP6CCSBot", InvestigateNoiseState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D166B0, "_ZN21InvestigateNoiseState8OnUpdateEP6CCSBot", InvestigateNoiseState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D16920, "_ZN21InvestigateNoiseState6OnExitEP6CCSBot", InvestigateNoiseState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D212F0, "_ZNK21InvestigateNoiseState7GetNameEv", InvestigateNoiseState::GetName),	// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D164D0, "_ZN21InvestigateNoiseState18AttendCurrentNoiseEP6CCSBot", InvestigateNoiseState::AttendCurrentNoise),	// NOXREF
//BuyState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D11910, "_ZN8BuyState7OnEnterEP6CCSBot", BuyState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D11B60, "_ZN8BuyState8OnUpdateEP6CCSBot", BuyState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D121E0, "_ZN8BuyState6OnExitEP6CCSBot", BuyState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21300, "_ZNK8BuyState7GetNameEv", BuyState::GetName),				// DEFAULT
//MoveToState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D16930, "_ZN11MoveToState7OnEnterEP6CCSBot", MoveToState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D169C0, "_ZN11MoveToState8OnUpdateEP6CCSBot", MoveToState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D16FE0, "_ZN11MoveToState6OnExitEP6CCSBot", MoveToState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21310, "_ZNK11MoveToState7GetNameEv", MoveToState::GetName),			// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN11MoveToState15SetGoalPositionEPK6Vector", MoveToState::SetGoalPosition),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN11MoveToState12SetRouteTypeE9RouteType", MoveToState::SetRouteType),		// NOXREF
//FetchBombState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D125A0, "_ZN14FetchBombState7OnEnterEP6CCSBot", FetchBombState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D125C0, "_ZN14FetchBombState8OnUpdateEP6CCSBot", FetchBombState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21320, "_ZNK14FetchBombState7GetNameEv", FetchBombState::GetName),			// DEFAULT
//PlantBombState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D17000, "_ZN14PlantBombState7OnEnterEP6CCSBot", PlantBombState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D170B0, "_ZN14PlantBombState8OnUpdateEP6CCSBot", PlantBombState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D17160, "_ZN14PlantBombState6OnExitEP6CCSBot", PlantBombState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21330, "_ZNK14PlantBombState7GetNameEv", PlantBombState::GetName),			// DEFAULT
//DefuseBombState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D12200, "_ZN15DefuseBombState7OnEnterEP6CCSBot", DefuseBombState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D12270, "_ZN15DefuseBombState8OnUpdateEP6CCSBot", DefuseBombState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D12340, "_ZN15DefuseBombState6OnExitEP6CCSBot", DefuseBombState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21340, "_ZNK15DefuseBombState7GetNameEv", DefuseBombState::GetName),		// DEFAULT
//HideState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D13250, "_ZN9HideState7OnEnterEP6CCSBot", HideState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D13300, "_ZN9HideState8OnUpdateEP6CCSBot", HideState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D13D90, "_ZN9HideState6OnExitEP6CCSBot", HideState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21350, "_ZNK9HideState7GetNameEv", HideState::GetName),				// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN9HideState13SetHidingSpotEPK6Vector", HideState::SetHidingSpot),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK9HideState13GetHidingSpotEv", HideState::GetHidingSpot),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9HideState13SetSearchAreaEP8CNavArea", HideState::SetSearchArea),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9HideState14SetSearchRangeEf", HideState::SetSearchRange),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9HideState11SetDurationEf", HideState::SetDuration),			// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9HideState15SetHoldPositionEb", HideState::SetHoldPosition),		// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK9HideState8IsAtSpotEv", HideState::IsAtSpot),				// NOXREF
//EscapeFromBombState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D12390, "_ZN19EscapeFromBombState7OnEnterEP6CCSBot", EscapeFromBombState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D123D0, "_ZN19EscapeFromBombState8OnUpdateEP6CCSBot", EscapeFromBombState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D12560, "_ZN19EscapeFromBombState6OnExitEP6CCSBot", EscapeFromBombState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21360, "_ZNK19EscapeFromBombState7GetNameEv", EscapeFromBombState::GetName),		// DEFAULT
//FollowState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D12660, "_ZN11FollowState7OnEnterEP6CCSBot", FollowState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D127A0, "_ZN11FollowState8OnUpdateEP6CCSBot", FollowState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D130C0, "_ZN11FollowState6OnExitEP6CCSBot", FollowState::OnExit),				// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21370, "_ZNK11FollowState7GetNameEv", FollowState::GetName),				// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN11FollowState9SetLeaderEP11CBasePlayer", FollowState::SetLeader),		// NOXREF
	HOOK_SYMBOLDEF(0x01D126E0, "_ZN11FollowState24ComputeLeaderMotionStateEf", FollowState::ComputeLeaderMotionState),
//UseEntityState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D171A0, "_ZN14UseEntityState7OnEnterEP6CCSBot", UseEntityState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D171B0, "_ZN14UseEntityState8OnUpdateEP6CCSBot", UseEntityState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D17280, "_ZN14UseEntityState6OnExitEP6CCSBot", UseEntityState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D21380, "_ZNK14UseEntityState7GetNameEv", UseEntityState::GetName),			// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN14UseEntityState9SetEntityEP11CBaseEntity", UseEntityState::SetEntity),		// NOXREF

#ifdef _WIN32
	HOOK_SYMBOLDEF(0x01D12F90, "_ZN21FollowTargetCollectorclEP8CNavArea", FollowTargetCollector::operator()),
#endif // _WIN32

#endif // CS_BotState_Region

#ifndef Bot_Region

//ActiveGrenade
	// virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN13ActiveGrenadeC2EiP8CGrenade", ActiveGrenade::ActiveGrenade),
	HOOK_SYMBOLDEF(0x01D34080, "_ZN13ActiveGrenade12OnEntityGoneEv", ActiveGrenade::OnEntityGone),
	HOOK_SYMBOLDEF(0x01D340A0, "_ZNK13ActiveGrenade7IsValidEv", ActiveGrenade::IsValid),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13ActiveGrenade8IsEntityEP8CGrenade", ActiveGrenade::IsEntity),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK13ActiveGrenade5GetIDEv", ActiveGrenade::GetID),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK13ActiveGrenade21GetDetonationPositionEv", ActiveGrenade::GetDetonationPosition),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D340C0, "_ZNK13ActiveGrenade11GetPositionEv", ActiveGrenade::GetPosition),			// NOXREF
//CBot
	//HOOK_DEF(0x01D334D0, MethodThunk<CBot>::Constructor),
	// virtual func
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33550, CCSBot, "_ZN4CBot5SpawnEv", CBot::Spawn),
	//HOOK_SYMBOLDEF(0x01D340D0, "_ZN4CBot10TakeDamageEP9entvars_sS1_fi", CBot::TakeDamage),		// DEFAULT
	//HOOK_SYMBOLDEF(0x01D340E0, "_ZN4CBot6KilledEP9entvars_si", CBot::Killed),			// DEFAULT
	//HOOK_SYMBOLDEF(0x01D210C0, "_ZN4CBot5ThinkEv", CBot::Think),					// PURE
	//HOOK_SYMBOLDEF(0x01D210B0, "_ZN4CBot5IsBotEv", CBot::IsBot),					// DEFAULT
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33600, CCSBot, "_ZN4CBot16GetAutoaimVectorEf", CBot::GetAutoaimVector),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot16OnTouchingWeaponEP10CWeaponBox", CBot::OnTouchingWeapon),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33540, CCSBot, "_ZN4CBot10InitializeEPK10BotProfile", CBot::Initialize),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot8SpawnBotEv", CBot::SpawnBot),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot6UpkeepEv", CBot::Upkeep),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot6UpdateEv", CBot::Update),
	//HOOK_SYMBOLDEF(0x01D21110, "_ZN4CBot3RunEv", CBot::Run),				// DEFAULT
	//HOOK_SYMBOLDEF(0x01D34110, "_ZN4CBot4WalkEv", CBot::Walk),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33940, CCSBot, "_ZN4CBot6CrouchEv", CBot::Crouch),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33950, CCSBot, "_ZN4CBot7StandUpEv", CBot::StandUp),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D336F0, CCSBot, "_ZN4CBot11MoveForwardEv", CBot::MoveForward),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33740, CCSBot, "_ZN4CBot12MoveBackwardEv", CBot::MoveBackward),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33790, CCSBot, "_ZN4CBot10StrafeLeftEv", CBot::StrafeLeft),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D337E0, CCSBot, "_ZN4CBot11StrafeRightEv", CBot::StrafeRight),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33830, CCSBot, "_ZN4CBot4JumpEb", CBot::Jump),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D338D0, CCSBot, "_ZN4CBot13ClearMovementEv", CBot::ClearMovement),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33960, CCSBot, "_ZN4CBot14UseEnvironmentEv", CBot::UseEnvironment),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33970, CCSBot, "_ZN4CBot13PrimaryAttackEv", CBot::PrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33980, CCSBot, "_ZN4CBot18ClearPrimaryAttackEv", CBot::ClearPrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33990, CCSBot, "_ZN4CBot19TogglePrimaryAttackEv", CBot::TogglePrimaryAttack),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D339C0, CCSBot, "_ZN4CBot15SecondaryAttackEv", CBot::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D339D0, CCSBot, "_ZN4CBot6ReloadEv", CBot::Reload),
	//HOOK_SYMBOLDEF(0x01D34100, "_ZN4CBot7OnEventE13GameEventTypeP11CBaseEntityS2_", CBot::OnEvent),		// PURE
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x0, CCSBot,  "_ZNK4CBot9IsVisibleEPK6Vectorb", CBot::IsVisible, bool(const Vector *, bool) const),
	//HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x0, CCSBot,  "_ZNK4CBot9IsVisibleEP11CBasePlayerbPh", CBot::IsVisible, bool(CBasePlayer *, bool, unsigned char *) const),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot18IsEnemyPartVisibleENS_15VisiblePartTypeE", CBot::IsEnemyPartVisible),	// NOXREF PURE
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D21120, CCSBot, "_ZNK4CBot16IsPlayerFacingMeEP11CBasePlayer", CBot::IsPlayerFacingMe),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D211B0, CCSBot, "_ZNK4CBot19IsPlayerLookingAtMeEP11CBasePlayer", CBot::IsPlayerLookingAtMe),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D33AA0, CCSBot, "_ZN4CBot14ExecuteCommandEv", CBot::ExecuteCommand),
	HOOK_SYMBOL_VIRTUAL_HIERARC_DEF(0x01D210D0, CCSBot, "_ZN4CBot8SetModelEPKc", CBot::SetModel),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot5GetIDEv", CBot::GetID),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot9IsRunningEv", CBot::IsRunning),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot11IsCrouchingEv", CBot::IsCrouching),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot18PushPostureContextEv", CBot::PushPostureContext),
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot17PopPostureContextEv", CBot::PopPostureContext),
	HOOK_SYMBOLDEF(0x01D338F0, "_ZN4CBot9IsJumpingEv", CBot::IsJumping),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot16GetJumpTimestampEv", CBot::GetJumpTimestamp),
	HOOK_SYMBOLDEF(0x01D339E0, "_ZNK4CBot24GetActiveWeaponAmmoRatioEv", CBot::GetActiveWeaponAmmoRatio),
	HOOK_SYMBOLDEF(0x01D33A30, "_ZNK4CBot23IsActiveWeaponClipEmptyEv", CBot::IsActiveWeaponClipEmpty),
	HOOK_SYMBOLDEF(0x01D33A50, "_ZNK4CBot23IsActiveWeaponOutOfAmmoEv", CBot::IsActiveWeaponOutOfAmmo),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot23IsActiveWeaponReloadingEv", CBot::IsActiveWeaponReloading),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot24IsActiveWeaponRecoilHighEv", CBot::IsActiveWeaponRecoilHigh),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot15GetActiveWeaponEv", CBot::GetActiveWeapon),
	HOOK_SYMBOLDEF(0x01D33A80, "_ZNK4CBot12IsUsingScopeEv", CBot::IsUsingScope),
	HOOK_SYMBOLDEF(0x01D33BF0, "_ZNK4CBot7IsEnemyEP11CBaseEntity", CBot::IsEnemy),
	HOOK_SYMBOLDEF(0x01D33C40, "_ZNK4CBot19GetEnemiesRemainingEv", CBot::GetEnemiesRemaining),
	HOOK_SYMBOLDEF(0x01D33D20, "_ZNK4CBot19GetFriendsRemainingEv", CBot::GetFriendsRemaining),
	HOOK_SYMBOLDEF(0x01D33E30, "_ZNK4CBot23IsLocalPlayerWatchingMeEv", CBot::IsLocalPlayerWatchingMe),
	//HOOK_SYMBOLDEF(0x01D33E90, "_ZNK4CBot5PrintEPcz", CBot::Print),			// NOXREF
	HOOK_SYMBOLDEF(0x01D33F00, "_ZNK4CBot14PrintIfWatchedEPcz", CBot::PrintIfWatched),
	HOOK_SYMBOLDEF(0x01D33660, "_ZN4CBot8BotThinkEv", CBot::BotThink),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot11IsNetClientEv", CBot::IsNetClient),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot4SaveER5CSave", CBot::Save),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot7RestoreER8CRestore", CBot::Restore),
	//HOOK_SYMBOLDEF(0x0, "_ZNK4CBot10GetProfileEv", CBot::GetProfile),
	HOOK_SYMBOLDEF(0x01D33BA0, "_ZN4CBot13ClientCommandEPKcS1_S1_S1_", CBot::ClientCommand),
	//HOOK_SYMBOLDEF(0x01D33B50, "_ZN4CBot12ResetCommandEv", CBot::ResetCommand),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D33B70, "_ZNK4CBot13ThrottledMsecEv", CBot::ThrottledMsec),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN4CBot12GetMoveSpeedEv", CBot::GetMoveSpeed),
//BotMeme
	HOOK_SYMBOLDEF(0x01D18C90, "_ZNK7BotMeme8TransmitEP6CCSBot", BotMeme::Transmit),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7BotMeme9InterpretEP6CCSBotS1_", BotMeme::Interpret),	// NOXREF
//BotAllHostagesGoneMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D19470, "_ZNK22BotAllHostagesGoneMeme9InterpretEP6CCSBotS1_", BotAllHostagesGoneMeme::Interpret),			// NOXREF
//BotHostageBeingTakenMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D19570, "_ZNK24BotHostageBeingTakenMeme9InterpretEP6CCSBotS1_", BotHostageBeingTakenMeme::Interpret),
//BotHelpMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D18D90, "_ZNK11BotHelpMeme9InterpretEP6CCSBotS1_", BotHelpMeme::Interpret),
//BotBombsiteStatusMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D18DB0, "_ZNK21BotBombsiteStatusMeme9InterpretEP6CCSBotS1_", BotBombsiteStatusMeme::Interpret),
//BotBombStatusMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D18EE0, "_ZNK17BotBombStatusMeme9InterpretEP6CCSBotS1_", BotBombStatusMeme::Interpret),
//BotFollowMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D19080, "_ZNK13BotFollowMeme9InterpretEP6CCSBotS1_", BotFollowMeme::Interpret),
//BotDefendHereMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D19280, "_ZNK17BotDefendHereMeme9InterpretEP6CCSBotS1_", BotDefendHereMeme::Interpret),
//BotWhereBombMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D19420, "_ZNK16BotWhereBombMeme9InterpretEP6CCSBotS1_", BotWhereBombMeme::Interpret),
//BotRequestReportMeme
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D19450, "_ZNK20BotRequestReportMeme9InterpretEP6CCSBotS1_", BotRequestReportMeme::Interpret),
//BotSpeakable
	//HOOK_DEF(0x01D19680, MethodThunk<BotSpeakable>::Constructor),	// NOXREF
	//HOOK_DEF(0x01D19690, MethodThunk<BotSpeakable>::Destructor),	// NOXREF
//BotPhrase
	//HOOK_DEF(0x01D196B0, MethodThunk<BotPhrase>::Constructor),	// NOXREF
	//HOOK_DEF(0x01D198E0, MethodThunk<BotPhrase>::Destructor),		// NOXREF
	HOOK_SYMBOLDEF(0x01D199C0, "_ZN9BotPhrase13InitVoiceBankEi", BotPhrase::InitVoiceBank),
	HOOK_SYMBOLDEF(0x01D19BB0, "_ZNK9BotPhrase12GetSpeakableEiPf", BotPhrase::GetSpeakable),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase13ClearCriteriaEv", BotPhrase::ClearCriteria),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase16SetPlaceCriteriaEj", BotPhrase::SetPlaceCriteria),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase16SetCountCriteriaEj", BotPhrase::SetCountCriteria),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase7GetNameEv", BotPhrase::GetName),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase5GetIDEv", BotPhrase::GetID),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase18GetRadioEquivalentEv", BotPhrase::GetRadioEquivalent),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase11IsImportantEv", BotPhrase::IsImportant),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9BotPhrase7IsPlaceEv", BotPhrase::IsPlace),
	//HOOK_SYMBOLDEF(0x01D19C70, "_ZN9BotPhrase9RandomizeEv", BotPhrase::Randomize),	// NOXREF
//BotPhraseManager
	//HOOK_DEF(0x01D19D20, MethodThunk<BotPhraseManager>::Constructor),
	//HOOK_DEF(0x01D1A720, MethodThunk<BotPhraseManager>::Destructor),
	HOOK_SYMBOLDEF(0x01D19ED0, "_ZN16BotPhraseManager10InitializeEPKci", BotPhraseManager::Initialize),
	HOOK_SYMBOLDEF(0x01D19DA0, "_ZN16BotPhraseManager14OnRoundRestartEv", BotPhraseManager::OnRoundRestart),
	//HOOK_SYMBOLDEF(0x01D19D90, "_ZN16BotPhraseManager11OnMapChangeEv", BotPhraseManager::OnMapChange),		// NOXREF
	HOOK_SYMBOLDEF(0x01D1A830, "_ZNK16BotPhraseManager8NameToIDEPKc", BotPhraseManager::NameToID),
	HOOK_SYMBOLDEF(0x01D1A8A0, "_ZNK16BotPhraseManager8IDToNameEj", BotPhraseManager::IDToName),
	HOOK_SYMBOLDEF(0x01D1A8F0, "_ZNK16BotPhraseManager9GetPhraseEPKc", BotPhraseManager::GetPhrase),
	//HOOK_SYMBOLDEF(0x01D1A940, "_ZNK16BotPhraseManager8GetPlaceEPKc", BotPhraseManager::GetPlace, const BotPhrase *(const char *name) const),	// NOXREF
	HOOK_SYMBOLDEF(0x01D1A990, "_ZNK16BotPhraseManager8GetPlaceEj", BotPhraseManager::GetPlace, const BotPhrase *(PlaceCriteria place) const),
	//HOOK_SYMBOLDEF(0x0, "_ZNK16BotPhraseManager12GetPlaceListEv", BotPhraseManager::GetPlaceList),
	//HOOK_SYMBOLDEF(0x0, "_ZNK16BotPhraseManager25GetPlaceStatementIntervalEj", BotPhraseManager::GetPlaceStatementInterval),
	//HOOK_SYMBOLDEF(0x0, "_ZN16BotPhraseManager27ResetPlaceStatementIntervalEj", BotPhraseManager::ResetPlaceStatementInterval),
#ifdef _WIN32
	HOOK_SYMBOLDEF(0x01D1F830, "_ZNK16BotPhraseManager14FindPlaceIndexEj", BotPhraseManager::FindPlaceIndex),
#endif // _WIN32

//BotStatement
	//HOOK_DEF(0x01D1A9C0, MethodThunk<BotStatement>::Constructor),	// NOXREF
	//HOOK_DEF(0x01D1AA20, MethodThunk<BotStatement>::Destructor),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement10GetChatterEv", BotStatement::GetChatter),						// NOXREF
	//HOOK_SYMBOLDEF(0x01D1AA30, "_ZNK12BotStatement8GetOwnerEv", BotStatement::GetOwner),						// NOXREF
	//HOOK_SYMBOLDEF(0x01D1AA40, "_ZN12BotStatement10AttachMemeEP7BotMeme", BotStatement::AttachMeme),			// NOXREF
	HOOK_SYMBOLDEF(0x01D1AA50, "_ZN12BotStatement12AddConditionENS_13ConditionTypeE", BotStatement::AddCondition),
	//HOOK_SYMBOLDEF(0x01D1AA70, "_ZNK12BotStatement11IsImportantEv", BotStatement::IsImportant),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D1AAB0, "_ZNK12BotStatement7IsValidEv", BotStatement::IsValid),						// NOXREF
	HOOK_SYMBOLDEF(0x01D1AB00, "_ZNK12BotStatement11IsRedundantEPKS_", BotStatement::IsRedundant),
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement7GetTypeEv", BotStatement::GetType),								// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement10HasSubjectEv", BotStatement::HasSubject),						// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12BotStatement10SetSubjectEi", BotStatement::SetSubject),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement10GetSubjectEv", BotStatement::GetSubject),						// NOXREF
	//HOOK_SYMBOLDEF(0x01D1AC90, "_ZNK12BotStatement10IsObsoleteEv", BotStatement::IsObsolete),					// NOXREF
	HOOK_SYMBOLDEF(0x01D1ACD0, "_ZN12BotStatement7ConvertEPKS_", BotStatement::Convert),
	HOOK_SYMBOLDEF(0x01D1ADC0, "_ZN12BotStatement12AppendPhraseEPK9BotPhrase", BotStatement::AppendPhrase, void (const BotPhrase *)),
	//HOOK_SYMBOLDEF(0x01D1ADF0, "_ZN12BotStatement12AppendPhraseENS_11ContextTypeE", BotStatement::AppendPhrase, void (BotStatement::ContextType)),		// NOXREF
	HOOK_SYMBOLDEF(0x01D1AE20, "_ZN12BotStatement6UpdateEv", BotStatement::Update),
	HOOK_SYMBOLDEF(0x01D1B2A0, "_ZNK12BotStatement8GetPlaceEv", BotStatement::GetPlace),					// NOXREF
	//HOOK_SYMBOLDEF(0x01D1B2E0, "_ZNK12BotStatement8HasCountEv", BotStatement::HasCount),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement8HasPlaceEv", BotStatement::HasPlace),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12BotStatement8SetPlaceEj", BotStatement::SetPlace),							// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN12BotStatement12SetStartTimeEf ", BotStatement::SetStartTime),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement12GetStartTimeEv", BotStatement::GetStartTime),				// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement10IsSpeakingEv", BotStatement::IsSpeaking),					// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK12BotStatement12GetTimestampEv", BotStatement::GetTimestamp),				// NOXREF
//BotChatterInterface
	HOOK_SYMBOLDEF(0x01D1B340, "_ZN19BotChatterInterfaceC2EP6CCSBot", MethodThunk<BotChatterInterface>::Constructor),
	//HOOK_DEF(0x01D1B3C0, MethodThunk<BotChatterInterface>::Destructor),

	HOOK_SYMBOLDEF(0x01D1B3F0, "_ZN19BotChatterInterface5ResetEv", BotChatterInterface::Reset),
	HOOK_SYMBOLDEF(0x01D1B8E0, "_ZN19BotChatterInterface6UpdateEv", BotChatterInterface::Update),
	//HOOK_SYMBOLDEF(0x01D1B7D0, "_ZN19BotChatterInterface7OnEventE13GameEventTypeP11CBaseEntityS2_", BotChatterInterface::OnEvent),			// PURE
	HOOK_SYMBOLDEF(0x01D1B7E0, "_ZN19BotChatterInterface7OnDeathEv", BotChatterInterface::OnDeath),
	//HOOK_SYMBOLDEF(0x0, "_ZNK19BotChatterInterface12GetVerbosityEv", BotChatterInterface::VerbosityType GetVerbosity),
	//HOOK_SYMBOLDEF(0x0, "_ZNK19BotChatterInterface8GetOwnerEv", BotChatterInterface::GetOwner),
	//HOOK_SYMBOLDEF(0x0, "_ZNK19BotChatterInterface9IsTalkingEv", BotChatterInterface::IsTalking),
	//HOOK_SYMBOLDEF(0x01D1BDC0, "_ZN19BotChatterInterface23GetRadioSilenceDurationEv", BotChatterInterface::GetRadioSilenceDuration),		// NOXREF
	HOOK_SYMBOLDEF(0x01D1BE00, "_ZN19BotChatterInterface25ResetRadioSilenceDurationEv", BotChatterInterface::ResetRadioSilenceDuration),
	HOOK_SYMBOLDEF(0x01D1B490, "_ZN19BotChatterInterface12AddStatementEP12BotStatementb", BotChatterInterface::AddStatement),
	HOOK_SYMBOLDEF(0x01D1B5E0, "_ZN19BotChatterInterface15RemoveStatementEP12BotStatement", BotChatterInterface::RemoveStatement),
	HOOK_SYMBOLDEF(0x01D1BC00, "_ZN19BotChatterInterface18GetActiveStatementEv", BotChatterInterface::GetActiveStatement),
	//HOOK_SYMBOLDEF(0x0, "_ZNK19BotChatterInterface12GetStatementEv", BotChatterInterface::GetStatement),
	//HOOK_SYMBOLDEF(0x0, "_ZNK19BotChatterInterface8GetPitchEv", BotChatterInterface::GetPitch),
	HOOK_SYMBOLDEF(0x01D1F890, "_ZN19BotChatterInterface3SayEPKcff", BotChatterInterface::Say),
	HOOK_SYMBOLDEF(0x01D1E100, "_ZN19BotChatterInterface12AnnouncePlanEPKcj", BotChatterInterface::AnnouncePlan),
	HOOK_SYMBOLDEF(0x01D1CDE0, "_ZN19BotChatterInterface11AffirmativeEv", BotChatterInterface::Affirmative),
	HOOK_SYMBOLDEF(0x01D1CED0, "_ZN19BotChatterInterface8NegativeEv", BotChatterInterface::Negative),
	//HOOK_SYMBOLDEF(0x01D1BE20, "_ZN19BotChatterInterface12EnemySpottedEv", BotChatterInterface::EnemySpotted),		// NOXREF
	HOOK_SYMBOLDEF(0x01D1CBE0, "_ZN19BotChatterInterface13KilledMyEnemyEi", BotChatterInterface::KilledMyEnemy),
	HOOK_SYMBOLDEF(0x01D1CCF0, "_ZN19BotChatterInterface16EnemiesRemainingEv", BotChatterInterface::EnemiesRemaining),
	//HOOK_SYMBOLDEF(0x01D1BF30, "_ZN19BotChatterInterface5ClearEj", BotChatterInterface::Clear),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D1C050, "_ZN19BotChatterInterface8ReportInEv", BotChatterInterface::ReportIn),			// NOXREF
	HOOK_SYMBOLDEF(0x01D1C170, "_ZN19BotChatterInterface11ReportingInEv", BotChatterInterface::ReportingIn),
	HOOK_SYMBOLDEF(0x01D1C6D0, "_ZN19BotChatterInterface10NeedBackupEv", BotChatterInterface::NeedBackup),
	HOOK_SYMBOLDEF(0x01D1C910, "_ZN19BotChatterInterface10PinnedDownEv", BotChatterInterface::PinnedDown),
	HOOK_SYMBOLDEF(0x01D1DD00, "_ZN19BotChatterInterface6ScaredEv", BotChatterInterface::Scared),
	HOOK_SYMBOLDEF(0x01D1CA90, "_ZN19BotChatterInterface10HeardNoiseEPK6Vector", BotChatterInterface::HeardNoise),
	HOOK_SYMBOLDEF(0x01D1D240, "_ZN19BotChatterInterface19TheyPickedUpTheBombEv", BotChatterInterface::TheyPickedUpTheBomb),
	HOOK_SYMBOLDEF(0x01D1CFC0, "_ZN19BotChatterInterface19GoingToPlantTheBombEj", BotChatterInterface::GoingToPlantTheBomb),
	HOOK_SYMBOLDEF(0x01D1DA40, "_ZN19BotChatterInterface13BombsiteClearEi", BotChatterInterface::BombsiteClear),
	HOOK_SYMBOLDEF(0x01D1DBB0, "_ZN19BotChatterInterface16FoundPlantedBombEi", BotChatterInterface::FoundPlantedBomb),
	HOOK_SYMBOLDEF(0x01D1D100, "_ZN19BotChatterInterface15PlantingTheBombEj", BotChatterInterface::PlantingTheBomb),
	HOOK_SYMBOLDEF(0x01D1D3A0, "_ZN19BotChatterInterface13SpottedBomberEP11CBasePlayer", BotChatterInterface::SpottedBomber),
	HOOK_SYMBOLDEF(0x01D1D580, "_ZN19BotChatterInterface16SpottedLooseBombEP11CBaseEntity", BotChatterInterface::SpottedLooseBomb),
	//HOOK_SYMBOLDEF(0x01D1D770, "_ZN19BotChatterInterface17GuardingLooseBombEP11CBaseEntity", BotChatterInterface::GuardingLooseBomb),		// NOXREF
	HOOK_SYMBOLDEF(0x01D1D920, "_ZN19BotChatterInterface19RequestBombLocationEv", BotChatterInterface::RequestBombLocation),
	HOOK_SYMBOLDEF(0x01D1E230, "_ZN19BotChatterInterface16GuardingHostagesEjb", BotChatterInterface::GuardingHostages),
	HOOK_SYMBOLDEF(0x01D1E470, "_ZN19BotChatterInterface25GuardingHostageEscapeZoneEb", BotChatterInterface::GuardingHostageEscapeZone),
	HOOK_SYMBOLDEF(0x01D1E6B0, "_ZN19BotChatterInterface18HostagesBeingTakenEv", BotChatterInterface::HostagesBeingTaken),
	HOOK_SYMBOLDEF(0x01D1E7C0, "_ZN19BotChatterInterface13HostagesTakenEv", BotChatterInterface::HostagesTaken),
	//HOOK_SYMBOLDEF(0x01D1E8C0, "_ZN19BotChatterInterface17TalkingToHostagesEv", BotChatterInterface::TalkingToHostages),		// NOXREF
	HOOK_SYMBOLDEF(0x01D1E8D0, "_ZN19BotChatterInterface17EscortingHostagesEv", BotChatterInterface::EscortingHostages),
	//HOOK_SYMBOLDEF(0x01D1E9F0, "_ZN19BotChatterInterface11HostageDownEv", BotChatterInterface::HostageDown),			// NOXREF
	HOOK_SYMBOLDEF(0x01D1DE20, "_ZN19BotChatterInterface12CelebrateWinEv", BotChatterInterface::CelebrateWin),
	HOOK_SYMBOLDEF(0x01D1EAF0, "_ZN19BotChatterInterface9EncourageEPKcff", BotChatterInterface::Encourage),
	HOOK_SYMBOLDEF(0x01D1EC00, "_ZN19BotChatterInterface12KilledFriendEv", BotChatterInterface::KilledFriend),
	HOOK_SYMBOLDEF(0x01D1ED00, "_ZN19BotChatterInterface12FriendlyFireEv", BotChatterInterface::FriendlyFire),
	HOOK_SYMBOLDEF(0x01D1B630, "_ZN19BotChatterInterface13ReportEnemiesEv", BotChatterInterface::ReportEnemies),
	//HOOK_SYMBOLDEF(0x01D1BD70, "_ZNK19BotChatterInterface11ShouldSpeakEv", BotChatterInterface::ShouldSpeak),		// NOXREF
	HOOK_SYMBOLDEF(0x01D18C30, "_Z20GetRandomSpotAtPlacej", GetRandomSpotAtPlace),

#endif // Bot_Region

#ifndef CS_Util_Region

	HOOK_SYMBOLDEF(0x01D36490, "_Z16UTIL_IsNameTakenPKcb", UTIL_IsNameTaken),
	HOOK_SYMBOLDEF(0x01D365E0, "_Z18UTIL_ClientsInGamev", UTIL_ClientsInGame),
	HOOK_SYMBOLDEF(0x01D36690, "_Z24UTIL_ActivePlayersInGamev", UTIL_ActivePlayersInGame),
	HOOK_SYMBOLDEF(0x01D36760, "_Z17UTIL_HumansInGameb", UTIL_HumansInGame),
	HOOK_SYMBOLDEF(0x01D36850, "_Z17UTIL_HumansOnTeamib", UTIL_HumansOnTeam),
	HOOK_SYMBOLDEF(0x01D36940, "_Z15UTIL_BotsInGamev", UTIL_BotsInGame),
	HOOK_SYMBOLDEF(0x01D36A00, "_Z20UTIL_KickBotFromTeam8TeamName", UTIL_KickBotFromTeam),
	HOOK_SYMBOLDEF(0x01D36C10, "_Z18UTIL_IsTeamAllBotsi", UTIL_IsTeamAllBots),
	HOOK_SYMBOLDEF(0x01D36CE0, "_Z21UTIL_GetClosestPlayerPK6VectorPf", UTIL_GetClosestPlayer, CBasePlayer *(const Vector *pos, float *distance)),
	HOOK_SYMBOLDEF(0x01D36E30, "_Z21UTIL_GetClosestPlayerPK6VectoriPf", UTIL_GetClosestPlayer, CBasePlayer *(const Vector *pos, int team, float *distance)),
	//HOOK_SYMBOLDEF(0x01D36F90, "_Z17UTIL_GetBotPrefixv", UTIL_GetBotPrefix),								// NOXREF
	HOOK_SYMBOLDEF(0x01D36FA0, "_Z24UTIL_ConstructBotNetNamePciPK10BotProfile", UTIL_ConstructBotNetName),
	HOOK_SYMBOLDEF(0x01D37000, "_Z20UTIL_IsVisibleToTeamRK6Vectorif", UTIL_IsVisibleToTeam),
	HOOK_SYMBOLDEF(0x01D37190, "_Z19UTIL_GetLocalPlayerv", UTIL_GetLocalPlayer),
	//HOOK_SYMBOLDEF(0x01D371B0, "_Z18UTIL_ComputeOriginP9entvars_s", UTIL_ComputeOrigin, Vector(entvars_t *)),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D37250, "_Z18UTIL_ComputeOriginP11CBaseEntity", UTIL_ComputeOrigin, Vector(CBaseEntity *)),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D37300, "_Z18UTIL_ComputeOriginP7edict_s", UTIL_ComputeOrigin, Vector(edict_t *)),				// NOXREF
	//HOOK_SYMBOLDEF(0x01D373B0, "_Z20UTIL_DrawBeamFromEnti6Vectorihhh", UTIL_DrawBeamFromEnt),					// NOXREF
	HOOK_SYMBOLDEF(0x01D37480, "_Z19UTIL_DrawBeamPoints6VectorS_ihhh", UTIL_DrawBeamPoints),
	HOOK_SYMBOLDEF(0x01D375D0, "_Z11BotPrecachev", BotPrecache),
	HOOK_SYMBOLDEF(0x01D37570, "_Z12CONSOLE_ECHOPcz", CONSOLE_ECHO),
	//HOOK_SYMBOLDEF(0x01D375A0, "_Z19CONSOLE_ECHO_LOGGEDPcz", CONSOLE_ECHO_LOGGED),	// NOXREF
	HOOK_SYMBOLDEF(0x01D37660, "_Z11InitBotTrigv", InitBotTrig),

	HOOK_SYMBOLDEF(0x01D37690, "_Z6BotCOSf", BotCOS),
	HOOK_SYMBOLDEF(0x01D37700, "_Z6BotSINf", BotSIN),

	HOOK_SYMBOLDEF(0x01D37770, "_Z18IsGameEventAudible13GameEventTypeP11CBaseEntityS1_PfP12PriorityTypePb", IsGameEventAudible),
	HOOK_SYMBOLDEF(0x01D37A00, "_Z23HintMessageToAllPlayersPKc", HintMessageToAllPlayers),

#endif // CS_Util_Region

#ifndef CS_Init_Region

	HOOK_SYMBOLDEF(0x01D206A0, "_Z17InstallBotControlv", InstallBotControl),
	HOOK_SYMBOLDEF(0x01D20730, "_Z17Bot_ServerCommandv", Bot_ServerCommand),
	HOOK_SYMBOLDEF(0x01D20760, "_Z17Bot_RegisterCvarsv", Bot_RegisterCVars),

#endif // CS_Init_Region

#ifndef H_Region

//AI
	//HOOK_SYMBOLDEF(0x01D848B0, "_Z11FBoxVisibleP9entvars_sS0_R6Vectorf", FBoxVisible),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D84A10, "_Z12VecCheckTossP9entvars_sRK6VectorS1_f", VecCheckToss),			// NOXREF
	//HOOK_SYMBOLDEF(0x01D84EB0, "_Z13VecCheckThrowP9entvars_sRK6VectorS1_ff", VecCheckThrow),		// NOXREF
//CRecharge
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D851E0, "_ZN9CRecharge5SpawnEv", CRecharge::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85270, "_ZN9CRecharge8PrecacheEv", CRecharge::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85130, "_ZN9CRecharge8KeyValueEP14KeyValueData_s", CRecharge::KeyValue),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85070, "_ZN9CRecharge4SaveER5CSave", CRecharge::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D850A0, "_ZN9CRecharge7RestoreER8CRestore", CRecharge::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D85120, "_ZN9CRecharge10ObjectCapsEv", CRecharge::ObjectCaps),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D852A0, "_ZN9CRecharge3UseEP11CBaseEntityS1_8USE_TYPEf", CRecharge::Use),
	// non-virtual func
	HOOK_DEF(0x01D850D0, func_recharge),
	HOOK_SYMBOLDEF(0x01D855A0, "_ZN9CRecharge3OffEv", CRecharge::Off),
	HOOK_SYMBOLDEF(0x01D85570, "_ZN9CRecharge8RechargeEv", CRecharge::Recharge),
//CCycler
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85AA0, "_ZN7CCycler5SpawnEv", CCycler::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85630, "_ZN7CCycler4SaveER5CSave", CCycler::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85660, "_ZN7CCycler7RestoreER8CRestore", CCycler::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D856E0, "_ZN7CCycler10ObjectCapsEv", CCycler::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85C60, "_ZN7CCycler10TakeDamageEP9entvars_sS1_fi", CCycler::TakeDamage),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D856F0, "_ZN7CCycler7IsAliveEv", CCycler::IsAlive),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85B80, "_ZN7CCycler5ThinkEv", CCycler::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85C20, "_ZN7CCycler3UseEP11CBaseEntityS1_8USE_TYPEf", CCycler::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D859B0, "_ZN7CCycler18GenericCyclerSpawnEPc6VectorS1__part_11_constprop_16", CCycler::GenericCyclerSpawn),	// NOXREF
//CCyclerProbe
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85860, "_ZN12CCyclerProbe5SpawnEv", CCyclerProbe::Spawn),
//CGenericCycler
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85700, "_ZN14CGenericCycler5SpawnEv", CGenericCycler::Spawn),
//CCyclerSprite
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85DE0, "_ZN13CCyclerSprite5SpawnEv", CCyclerSprite::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85F00, "_ZN13CCyclerSprite7RestartEv", CCyclerSprite::Restart),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85D80, "_ZN13CCyclerSprite4SaveER5CSave", CCyclerSprite::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85DB0, "_ZN13CCyclerSprite7RestoreER8CRestore", CCyclerSprite::Restore),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D85D70, "_ZN13CCyclerSprite10ObjectCapsEv", CCyclerSprite::ObjectCaps),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86090, "_ZN13CCyclerSprite10TakeDamageEP9entvars_sS1_fi", CCyclerSprite::TakeDamage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D85FB0, "_ZN13CCyclerSprite5ThinkEv", CCyclerSprite::Think),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86050, "_ZN13CCyclerSprite3UseEP11CBaseEntityS1_8USE_TYPEf", CCyclerSprite::Use),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01D86100, "_ZN13CCyclerSprite7AnimateEf", CCyclerSprite::Animate),	// NOXREF
//CWeaponCycler
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D861F0, "_ZN13CWeaponCycler5SpawnEv", CWeaponCycler::Spawn),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D861E0, "_ZN13CWeaponCycler11GetItemInfoEP8ItemInfo", CWeaponCycler::GetItemInfo),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D862D0, "_ZN13CWeaponCycler6DeployEv", CWeaponCycler::Deploy),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86320, "_ZN13CWeaponCycler7HolsterEi", CWeaponCycler::Holster),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D861D0, "_ZN13CWeaponCycler9iItemSlotEv", CWeaponCycler::iItemSlot),	// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86370, "_ZN13CWeaponCycler15SecondaryAttackEv", CWeaponCycler::SecondaryAttack),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86340, "_ZN13CWeaponCycler13PrimaryAttackEv", CWeaponCycler::PrimaryAttack),
//CWreckage
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D864D0, "_ZN9CWreckage5SpawnEv", CWreckage::Spawn),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86580, "_ZN9CWreckage8PrecacheEv", CWreckage::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86420, "_ZN9CWreckage4SaveER5CSave", CWreckage::Save),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D86450, "_ZN9CWreckage7RestoreER8CRestore", CWreckage::Restore),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D865B0, "_ZN9CWreckage5ThinkEv", CWreckage::Think),
//linked objects
	HOOK_DEF(0x01D85690, cycler),
	HOOK_DEF(0x01D85810, cycler_prdroid),
	HOOK_DEF(0x01D85D20, cycler_sprite),
	HOOK_DEF(0x01D86150, cycler_weapon),
	HOOK_DEF(0x01D86480, cycler_wreckage),

#endif // H_Region

#ifndef Tutor_CS_Region

	HOOK_SYMBOLDEF(0x01DD26D0, "_Z12InstallTutorb", InstallTutor),
	HOOK_SYMBOLDEF(0x01DD2740, "_Z19Tutor_RegisterCVarsv", Tutor_RegisterCVars),
	HOOK_SYMBOLDEF(0x01DD27C0, "_Z18MonitorTutorStatusv", MonitorTutorStatus),
//CBaseTutor
	//HOOK_SYMBOLDEF(0x01DD2BF0, "_ZN10CBaseTutorC2Ev", CBaseTutor::CBaseTutor),
	//HOOK_SYMBOLDEF(0x01DD2C10, "_ZN10CBaseTutorD0Ev", CBaseTutor::~CBaseTutor),
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN10CBaseTutor10TutorThinkEf", CBaseTutor::TutorThink),	// PURE virt
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN10CBaseTutor13PurgeMessagesEv", CBaseTutor::PurgeMessages),	// PURE virt
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN10CBaseTutor16CallEventHandlerE13GameEventTypeP11CBaseEntityS2_", CBaseTutor::CallEventHandler),	// PURE virt
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN10CBaseTutor16ShowTutorMessageEP17TutorMessageEvent", CBaseTutor::ShowTutorMessage),	// PURE virt
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3070, "_ZN10CBaseTutor22IsEntityInViewOfPlayerEP11CBaseEntityP11CBasePlayer", CBaseTutor::IsEntityInViewOfPlayer),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3350, "_ZN10CBaseTutor24IsBombsiteInViewOfPlayerEP11CBaseEntityP11CBasePlayer", CBaseTutor::IsBombsiteInViewOfPlayer),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3480, "_ZN10CBaseTutor18IsEntityInBombsiteEP11CBaseEntityS1_", CBaseTutor::IsEntityInBombsite),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3160, "_ZN10CBaseTutor25IsPlayerLookingAtPositionEP6VectorP11CBasePlayer", CBaseTutor::IsPlayerLookingAtPosition),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3240, "_ZN10CBaseTutor23IsPlayerLookingAtEntityEP11CBaseEntityP11CBasePlayer", CBaseTutor::IsPlayerLookingAtEntity),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN10CBaseTutor15HandleShotFiredE6VectorS0_", CBaseTutor::HandleShotFired),	// PURE virt
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN10CBaseTutor25GetTutorMessageDefinitionEi", CBaseTutor::GetTutorMessageDefinition),	// PURE virt
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DD2DA0, "_ZN10CBaseTutor10StartFrameEf", CBaseTutor::StartFrame),
	HOOK_SYMBOLDEF(0x01DD2C70, "_ZN10CBaseTutor7OnEventE13GameEventTypeP11CBaseEntityS2_", CBaseTutor::OnEvent),
	//HOOK_SYMBOLDEF(0x01DD2CF0, "_ZN10CBaseTutor9ShotFiredE6VectorS0_", CBaseTutor::ShotFired),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD2DB0, "_ZN10CBaseTutor22DisplayMessageToPlayerEP11CBasePlayeriPKcP17TutorMessageEvent", CBaseTutor::DisplayMessageToPlayer),
	//HOOK_SYMBOLDEF(0x01DD2F80, "_ZN10CBaseTutor16DrawLineToEntityEP11CBasePlayerii", CBaseTutor::DrawLineToEntity),			// NOXREF
	//HOOK_SYMBOLDEF(0x01DD2FD0, "_ZN10CBaseTutor34DisplayNewStateDescriptionToPlayerEv", CBaseTutor::DisplayNewStateDescriptionToPlayer),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD3020, "_ZN10CBaseTutor18CloseCurrentWindowEv", CBaseTutor::CloseCurrentWindow),
	//HOOK_SYMBOLDEF(0x01DD2D30, "_ZN10CBaseTutor23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", CBaseTutor::CheckForStateTransition),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD3060, "_ZN10CBaseTutor25CalculatePathForObjectiveEP11CBaseEntity", CBaseTutor::CalculatePathForObjective),	// PURE
	HOOK_SYMBOLDEF(0x01DD3510, "_ZN10CBaseTutor20DoMessagesHaveSameIDEii", CBaseTutor::DoMessagesHaveSameID),
//CCSTutor
	//HOOK_SYMBOLDEF(0x01DD3A30, "_ZN8CCSTutorC2Ev", CCSTutor::CCSTutor),
	//HOOK_SYMBOLDEF(0x01DD3B90, "_ZN8CCSTutorC2Ev", CCSTutor::~CCSTutor),
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD46C0, "_ZN8CCSTutor10TutorThinkEf", CCSTutor::TutorThink),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD56C0, "_ZN8CCSTutor13PurgeMessagesEv", CCSTutor::PurgeMessages),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD5960, "_ZN8CCSTutor16ShowTutorMessageEP17TutorMessageEvent", CCSTutor::ShowTutorMessage),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD5A20, "_ZN8CCSTutor16CallEventHandlerE13GameEventTypeP11CBaseEntityS2_", CCSTutor::CallEventHandler),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD9830, "_ZN8CCSTutor15HandleShotFiredE6VectorS0_", CCSTutor::HandleShotFired),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DDA8B0, "_ZN8CCSTutor25GetTutorMessageDefinitionEi", CCSTutor::GetTutorMessageDefinition),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DD5510, "_ZN8CCSTutor14AddToEventListEP17TutorMessageEvent", CCSTutor::AddToEventList),
	HOOK_SYMBOLDEF(0x01DD5530, "_ZN8CCSTutor23CreateAndAddEventToListE14TutorMessageIDP11CBaseEntityS2_", CCSTutor::CreateAndAddEventToList),
	HOOK_SYMBOLDEF(0x01DD51B0, "_ZN8CCSTutor23CreateTutorMessageEventE14TutorMessageIDP11CBaseEntityS2_", CCSTutor::CreateTutorMessageEvent),
	HOOK_SYMBOLDEF(0x01DD55C0, "_ZN8CCSTutor24DeleteEventFromEventListEP17TutorMessageEvent", CCSTutor::DeleteEventFromEventList),
	HOOK_SYMBOLDEF(0x01DD5640, "_ZN8CCSTutor14ClearEventListEv", CCSTutor::ClearEventList),
	HOOK_SYMBOLDEF(0x01DD4BE0, "_ZN8CCSTutor17ClearCurrentEventEbb", CCSTutor::ClearCurrentEvent),
	HOOK_SYMBOLDEF(0x01DD5690, "_ZN8CCSTutor11DeleteEventEP17TutorMessageEvent", CCSTutor::DeleteEvent),
	HOOK_SYMBOLDEF(0x01DD4410, "_ZN8CCSTutor22ShouldShowMessageEventEP17TutorMessageEventf", CCSTutor::ShouldShowMessageEvent),
	//HOOK_SYMBOLDEF(0x01DD5870, "_ZN8CCSTutor26ShouldUpdateCurrentMessageE14TutorMessageID", CCSTutor::ShouldUpdateCurrentMessage),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD57B0, "_ZN8CCSTutor29ComputeDisplayTimesForMessageEv", CCSTutor::ComputeDisplayTimesForMessage),
	HOOK_SYMBOLDEF(0x01DD58A0, "_ZN8CCSTutor20UpdateCurrentMessageEP17TutorMessageEvent", CCSTutor::UpdateCurrentMessage),
	//HOOK_SYMBOLDEF(0x01DD59B0, "_ZN8CCSTutor26ConstructMessageAndDisplayEv", CCSTutor::ConstructMessageAndDisplay),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD5190, "_ZN8CCSTutor12LookupHotKeyE14TutorMessageIDiPwi", CCSTutor::LookupHotKey),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD4970, "_ZN8CCSTutor19CheckForWindowCloseEf", CCSTutor::CheckForWindowClose),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD4AF0, "_ZN8CCSTutor21CheckForContentUpdateEv", CCSTutor::CheckForContentUpdate),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD43E0, "_ZN8CCSTutor36HasCurrentWindowBeenActiveLongEnoughEf", CCSTutor::HasCurrentWindowBeenActiveLongEnough),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD4540, "_ZN8CCSTutor32CheckForInterruptingMessageEventEf", CCSTutor::CheckForInterruptingMessageEvent),
	HOOK_SYMBOLDEF(0x01DD4D80, "_ZN8CCSTutor22CheckForInactiveEventsEf", CCSTutor::CheckForInactiveEvents),
	HOOK_SYMBOLDEF(0x01DD5020, "_ZN8CCSTutor11CancelEventE14TutorMessageID", CCSTutor::CancelEvent),
	//HOOK_SYMBOLDEF(0x01DD4C90, "_ZN8CCSTutor26ProcessShownDeathsForEventEP17TutorMessageEvent", CCSTutor::ProcessShownDeathsForEvent),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDB520, "_ZN8CCSTutor19TransferDeathEventsEP17TutorMessageEventS1_", CCSTutor::TransferDeathEvents),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD4CC0, "_ZN8CCSTutor26GetTutorMessageUpdateEventEv", CCSTutor::GetTutorMessageUpdateEvent),
	HOOK_SYMBOLDEF(0x01DD4D10, "_ZN8CCSTutor33GetDuplicateMessagesFromEventListERP17TutorMessageEventS2_", CCSTutor::GetDuplicateMessagesFromEventList),
	//HOOK_SYMBOLDEF(0x01DDB390, "_ZN8CCSTutor9IsBombMapEv", CCSTutor::IsBombMap),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDB370, "_ZN8CCSTutor12IsHostageMapEv", CCSTutor::IsHostageMap),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD6460, "_ZN8CCSTutor17HandleWeaponFiredEP11CBaseEntityS1_", CCSTutor::HandleWeaponFired),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD64A0, "_ZN8CCSTutor24HandleWeaponFiredOnEmptyEP11CBaseEntityS1_", CCSTutor::HandleWeaponFiredOnEmpty),
	//HOOK_SYMBOLDEF(0x01DD65A0, "_ZN8CCSTutor20HandleWeaponReloadedEP11CBaseEntityS1_", CCSTutor::HandleWeaponReloaded),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD65E0, "_ZN8CCSTutor16HandlePlayerDiedEP11CBaseEntityS1_", CCSTutor::HandlePlayerDied),
	//HOOK_SYMBOLDEF(0x01DD6F90, "_ZN8CCSTutor19HandlePlayerSpawnedEP11CBaseEntityS1_", CCSTutor::HandlePlayerSpawned),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7040, "_ZN8CCSTutor25HandleClientCorpseSpawnedEP11CBaseEntityS1_", CCSTutor::HandleClientCorpseSpawned),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD6D60, "_ZN8CCSTutor22HandlePlayerTookDamageEP11CBaseEntityS1_", CCSTutor::HandlePlayerTookDamage),
	//HOOK_SYMBOLDEF(0x01DD6EE0, "_ZN8CCSTutor30HandlePlayerBlindedByFlashbangEP11CBaseEntityS1_", CCSTutor::HandlePlayerBlindedByFlashbang),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7380, "_ZN8CCSTutor18HandleBuyTimeStartEP11CBaseEntityS1_", CCSTutor::HandleBuyTimeStart),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7390, "_ZN8CCSTutor23HandlePlayerLeftBuyZoneEP11CBaseEntityS1_", CCSTutor::HandlePlayerLeftBuyZone),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7490, "_ZN8CCSTutor17HandleBombPlantedEP11CBaseEntityS1_", CCSTutor::HandleBombPlanted),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD75B0, "_ZN8CCSTutor17HandleBombDefusedEP11CBaseEntityS1_", CCSTutor::HandleBombDefused),
	//HOOK_SYMBOLDEF(0x01DD7740, "_ZN8CCSTutor18HandleBombDefusingEP11CBaseEntityS1_", CCSTutor::HandleBombDefusing),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7800, "_ZN8CCSTutor18HandleBombExplodedEP11CBaseEntityS1_", CCSTutor::HandleBombExploded),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD7920, "_ZN8CCSTutor16HandleRoundStartEP11CBaseEntityS1_", CCSTutor::HandleRoundStart),
	//HOOK_SYMBOLDEF(0x01DD7B30, "_ZN8CCSTutor17HandleBeingShotAtEP11CBaseEntityS1_", CCSTutor::HandleBeingShotAt),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD7C00, "_ZN8CCSTutor17HandleHostageUsedEP11CBaseEntityS1_", CCSTutor::HandleHostageUsed),
	//HOOK_SYMBOLDEF(0x01DD7E30, "_ZN8CCSTutor20HandleHostageRescuedEP11CBaseEntityS1_", CCSTutor::HandleHostageRescued),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7FD0, "_ZN8CCSTutor24HandleAllHostagesRescuedEP11CBaseEntityS1_", CCSTutor::HandleAllHostagesRescued),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD80F0, "_ZN8CCSTutor20HandleHostageDamagedEP11CBaseEntityS1_", CCSTutor::HandleHostageDamaged),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD81B0, "_ZN8CCSTutor19HandleHostageKilledEP11CBaseEntityS1_", CCSTutor::HandleHostageKilled),
	//HOOK_SYMBOLDEF(0x01DD8430, "_ZN8CCSTutor15HandleRoundDrawEP11CBaseEntityS1_", CCSTutor::HandleRoundDraw),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD84E0, "_ZN8CCSTutor11HandleCTWinEP11CBaseEntityS1_", CCSTutor::HandleCTWin),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8580, "_ZN8CCSTutor10HandleTWinEP11CBaseEntityS1_", CCSTutor::HandleTWin),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8620, "_ZN8CCSTutor22HandleDeathCameraStartEP11CBaseEntityS1_", CCSTutor::HandleDeathCameraStart),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD86E0, "_ZN8CCSTutor18HandleRadioCoverMeEP11CBaseEntityS1_", CCSTutor::HandleRadioCoverMe),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8770, "_ZN8CCSTutor26HandleRadioYouTakeThePointEP11CBaseEntityS1_", CCSTutor::HandleRadioYouTakeThePoint),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8800, "_ZN8CCSTutor27HandleRadioHoldThisPositionEP11CBaseEntityS1_", CCSTutor::HandleRadioHoldThisPosition),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8890, "_ZN8CCSTutor22HandleRadioRegroupTeamEP11CBaseEntityS1_", CCSTutor::HandleRadioRegroupTeam),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8920, "_ZN8CCSTutor19HandleRadioFollowMeEP11CBaseEntityS1_", CCSTutor::HandleRadioFollowMe),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD89B0, "_ZN8CCSTutor21HandleRadioTakingFireEP11CBaseEntityS1_", CCSTutor::HandleRadioTakingFire),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8A40, "_ZN8CCSTutor17HandleRadioGoGoGoEP11CBaseEntityS1_", CCSTutor::HandleRadioGoGoGo),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8AD0, "_ZN8CCSTutor23HandleRadioTeamFallBackEP11CBaseEntityS1_", CCSTutor::HandleRadioTeamFallBack),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8B60, "_ZN8CCSTutor28HandleRadioStickTogetherTeamEP11CBaseEntityS1_", CCSTutor::HandleRadioStickTogetherTeam),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8BF0, "_ZN8CCSTutor31HandleRadioGetInPositionAndWaitEP11CBaseEntityS1_", CCSTutor::HandleRadioGetInPositionAndWait),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8C80, "_ZN8CCSTutor24HandleRadioStormTheFrontEP11CBaseEntityS1_", CCSTutor::HandleRadioStormTheFront),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8D10, "_ZN8CCSTutor23HandleRadioReportInTeamEP11CBaseEntityS1_", CCSTutor::HandleRadioReportInTeam),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8DA0, "_ZN8CCSTutor22HandleRadioAffirmativeEP11CBaseEntityS1_", CCSTutor::HandleRadioAffirmative),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8E30, "_ZN8CCSTutor23HandleRadioEnemySpottedEP11CBaseEntityS1_", CCSTutor::HandleRadioEnemySpotted),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8EC0, "_ZN8CCSTutor21HandleRadioNeedBackupEP11CBaseEntityS1_", CCSTutor::HandleRadioNeedBackup),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8F50, "_ZN8CCSTutor22HandleRadioSectorClearEP11CBaseEntityS1_", CCSTutor::HandleRadioSectorClear),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD8FE0, "_ZN8CCSTutor21HandleRadioInPositionEP11CBaseEntityS1_", CCSTutor::HandleRadioInPosition),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9070, "_ZN8CCSTutor22HandleRadioReportingInEP11CBaseEntityS1_", CCSTutor::HandleRadioReportingIn),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9100, "_ZN8CCSTutor24HandleRadioGetOutOfThereEP11CBaseEntityS1_", CCSTutor::HandleRadioGetOutOfThere),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9190, "_ZN8CCSTutor19HandleRadioNegativeEP11CBaseEntityS1_", CCSTutor::HandleRadioNegative),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9220, "_ZN8CCSTutor20HandleRadioEnemyDownEP11CBaseEntityS1_", CCSTutor::HandleRadioEnemyDown),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD7240, "_ZN8CCSTutor20HandleBuyMenuOpennedEP11CBaseEntityS1_", CCSTutor::HandleBuyMenuOpenned),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD72E0, "_ZN8CCSTutor13HandleAutoBuyEP11CBaseEntityS1_", CCSTutor::HandleAutoBuy),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD92B0, "_ZN8CCSTutor23HandleNotBuyingAnythingEP11CBaseEntityS1_", CCSTutor::HandleNotBuyingAnything),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9340, "_ZN8CCSTutor28HandleNeedToBuyPrimaryWeaponEP11CBaseEntityS1_", CCSTutor::HandleNeedToBuyPrimaryWeapon),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD93D0, "_ZN8CCSTutor26HandleNeedToBuyPrimaryAmmoEP11CBaseEntityS1_", CCSTutor::HandleNeedToBuyPrimaryAmmo),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9460, "_ZN8CCSTutor28HandleNeedToBuySecondaryAmmoEP11CBaseEntityS1_", CCSTutor::HandleNeedToBuySecondaryAmmo),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD94F0, "_ZN8CCSTutor20HandleNeedToBuyArmorEP11CBaseEntityS1_", CCSTutor::HandleNeedToBuyArmor),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9580, "_ZN8CCSTutor24HandleNeedToBuyDefuseKitEP11CBaseEntityS1_", CCSTutor::HandleNeedToBuyDefuseKit),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD9610, "_ZN8CCSTutor22HandleNeedToBuyGrenadeEP11CBaseEntityS1_", CCSTutor::HandleNeedToBuyGrenade),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD96A0, "_ZN8CCSTutor20HandleCareerTaskDoneEP11CBaseEntityS1_", CCSTutor::HandleCareerTaskDone),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD98F0, "_ZN8CCSTutor25GetNumPlayersAliveOnTeamsERiS0_", CCSTutor::GetNumPlayersAliveOnTeams),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD9BA0, "_ZN8CCSTutor20CheckForBombViewableEv", CCSTutor::CheckForBombViewable),
	//HOOK_SYMBOLDEF(0x01DD9970, "_ZN8CCSTutor27CheckForLooseWeaponViewableEv", CCSTutor::CheckForLooseWeaponViewable),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD9A80, "_ZN8CCSTutor28CheckForLooseDefuserViewableEv", CCSTutor::CheckForLooseDefuserViewable),
	HOOK_SYMBOLDEF(0x01DD9F30, "_ZN8CCSTutor24CheckForBombsiteViewableEv", CCSTutor::CheckForBombsiteViewable),
	HOOK_SYMBOLDEF(0x01DDA1D0, "_ZN8CCSTutor18CheckForInBombZoneEv", CCSTutor::CheckForInBombZone),
	HOOK_SYMBOLDEF(0x01DDA340, "_ZN8CCSTutor23CheckForHostageViewableEv", CCSTutor::CheckForHostageViewable),
	HOOK_SYMBOLDEF(0x01DDA550, "_ZN8CCSTutor22CheckForTimeRunningOutEv", CCSTutor::CheckForTimeRunningOut),
	//HOOK_SYMBOLDEF(0x01DDA740, "_ZN8CCSTutor23CheckForAllHostagesDeadEv", CCSTutor::CheckForAllHostagesDead),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DDA810, "_ZN8CCSTutor35CheckForAllHostagesFollowingSomeoneEv", CCSTutor::CheckForAllHostagesFollowingSomeone),	// NOXREF
	HOOK_SYMBOLDEF(0x01DDAB10, "_ZN8CCSTutor17CheckHintMessagesEf", CCSTutor::CheckHintMessages),
	//HOOK_SYMBOLDEF(0x01DDAC40, "_ZN8CCSTutor23CheckInGameHintMessagesEf", CCSTutor::CheckInGameHintMessages),	// NOXREF
	HOOK_SYMBOLDEF(0x01DDAF80, "_ZN8CCSTutor20CheckExamineMessagesEf", CCSTutor::CheckExamineMessages),
	HOOK_SYMBOLDEF(0x01DDAD20, "_ZN8CCSTutor20CheckForNeedToReloadEb", CCSTutor::CheckForNeedToReload),
	//HOOK_SYMBOLDEF(0x01DDB210, "_ZN8CCSTutor22CanLocalPlayerBuyStuffEv", CCSTutor::CanLocalPlayerBuyStuff),	// NOXREF
	HOOK_SYMBOLDEF(0x01DDB230, "_ZN8CCSTutor20CheckBuyZoneMessagesEv", CCSTutor::CheckBuyZoneMessages),
	//HOOK_SYMBOLDEF(0x01DDA2F0, "_ZN8CCSTutor23IsBombPlantedInBombsiteEP11CBaseEntity", CCSTutor::IsBombPlantedInBombsite),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD3D30, "_ZN8CCSTutor20ReadTutorMessageFileEv", CCSTutor::ReadTutorMessageFile),
	//HOOK_SYMBOLDEF(0x01DD43A0, "_ZN8CCSTutor20ApplyPersistentDecayEv", CCSTutor::ApplyPersistentDecay),	// NOXREF
	HOOK_SYMBOLDEF(0x01DDA9A0, "_ZN8CCSTutor21GetEntityForMessageIDEiP11CBaseEntity", CCSTutor::GetEntityForMessageID),
	HOOK_SYMBOLDEF(0x01DDB3A0, "_ZN8CCSTutor20ResetPlayerDeathInfoEv", CCSTutor::ResetPlayerDeathInfo),
	HOOK_SYMBOLDEF(0x01DDB3C0, "_ZN8CCSTutor25ConstructRecentDeathsListE8TeamNamePciP17TutorMessageEvent", CCSTutor::ConstructRecentDeathsList),
//TutorMessageEvent
	// virtual func
	//HOOK_SYMBOLDEF(0x01DD2A10, "_ZN17TutorMessageEventC2Eiiffi", TutorMessageEvent::TutorMessageEvent),
	//HOOK_SYMBOLDEF(0x01DD2A50, "_ZN17TutorMessageEventD0Ev", TutorMessageEvent::~TutorMessageEvent),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01DD2A80, "_ZN17TutorMessageEvent8IsActiveEf", TutorMessageEvent::IsActive),
	//HOOK_SYMBOLDEF(0x01DD2AA0, "_ZN17TutorMessageEvent11GetPriorityEv", TutorMessageEvent::GetPriority),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD2AB0, "_ZN17TutorMessageEvent13GetTimeActiveEf", TutorMessageEvent::GetTimeActive),
	HOOK_SYMBOLDEF(0x01DD2AC0, "_ZN17TutorMessageEvent17SetActivationTimeEf", TutorMessageEvent::SetActivationTime),
	HOOK_SYMBOLDEF(0x01DD2AD0, "_ZN17TutorMessageEvent5GetIDEv", TutorMessageEvent::GetID),
	//HOOK_SYMBOLDEF(0x01DD2AE0, "_ZN17TutorMessageEvent14GetDuplicateIDEv", TutorMessageEvent::GetDuplicateID),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD2AF0, "_ZN17TutorMessageEvent7SetNextEPS_", TutorMessageEvent::SetNext),
	HOOK_SYMBOLDEF(0x01DD2B00, "_ZN17TutorMessageEvent7GetNextEv", TutorMessageEvent::GetNext),
	HOOK_SYMBOLDEF(0x01DD2B10, "_ZN17TutorMessageEvent12AddParameterEPc", TutorMessageEvent::AddParameter),
	//HOOK_SYMBOLDEF(0x01DD2BA0, "_ZN17TutorMessageEvent16GetNextParameterEPci", TutorMessageEvent::GetNextParameter),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD2BE0, "_ZN17TutorMessageEvent16GetNumParametersEv", TutorMessageEvent::GetNumParameters),	// NOXREF
//CBaseTutorStateSystem
	// virtual func
	//HOOK_SYMBOLDEF(0x01DD2970, "_ZN21CBaseTutorStateSystemC2Ev", CBaseTutorStateSystem::CBaseTutorStateSystem),
	//HOOK_SYMBOLDEF(0x01DD2980, "_ZN21CBaseTutorStateSystemD0Ev", CBaseTutorStateSystem::~CBaseTutorStateSystem),
	//HOOK_SYMBOLDEF(0x0, "_ZN21CBaseTutorStateSystem11UpdateStateE13GameEventTypeP11CBaseEntityS2_", CBaseTutorStateSystem::UpdateState),	// NOXREF PURE
	//HOOK_SYMBOLDEF(0x0, "_ZN21CBaseTutorStateSystem21GetCurrentStateStringEv", CBaseTutorStateSystem::GetCurrentStateString),	// NOXREF PURE
	//HOOK_SYMBOLDEF(0x0, "_ZN21CBaseTutorStateSystem17ConstructNewStateEi", CBaseTutorStateSystem::ConstructNewState),	// NOXREF PURE
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DD29B0, "_ZN21CBaseTutorStateSystem19GetCurrentStateTypeEv", CBaseTutorStateSystem::GetCurrentStateType),	// NOXREF
//CBaseTutorState
	// virtual func
	//HOOK_SYMBOLDEF(0x01DD29C0, "_ZN15CBaseTutorStateC2Ev", CBaseTutorState::CBaseTutorState),
	//HOOK_SYMBOLDEF(0x01DD29D0, "_ZN15CBaseTutorStateD0Ev", CBaseTutorState::~CBaseTutorState),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN15CBaseTutorState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", CBaseTutorState::CheckForStateTransition),	// PURE virt
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZN15CBaseTutorState14GetStateStringEv", CBaseTutorState::GetStateString),	// PURE virt
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DD2A00, "_ZN15CBaseTutorState7GetTypeEv", CBaseTutorState::GetType),	// NOXREF
//CCSTutorStateSystem
	//HOOK_SYMBOLDEF(0x01DD3560, "_ZN19CCSTutorStateSystemC2Ev", CCSTutorStateSystem::CCSTutorStateSystem),
	// virtual func
	//HOOK_SYMBOLDEF(0x01DD35B0, "_ZN19CCSTutorStateSystemD0Ev", CCSTutorStateSystem::~CCSTutorStateSystem),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3620, "_ZN19CCSTutorStateSystem11UpdateStateE13GameEventTypeP11CBaseEntityS2_", CCSTutorStateSystem::UpdateState),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD36B0, "_ZN19CCSTutorStateSystem21GetCurrentStateStringEv", CCSTutorStateSystem::GetCurrentStateString),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01DD36C0, "_ZN19CCSTutorStateSystem17ConstructNewStateEi", CCSTutorStateSystem::ConstructNewState),			// PROTECTED
//CCSTutorUndefinedState
	//HOOK_SYMBOLDEF(0x01DD3760, "_ZN22CCSTutorUndefinedStateC2Ev", CCSTutorUndefinedState::CCSTutorUndefinedState),
	//HOOK_SYMBOLDEF(0x01DD3780, "_ZN22CCSTutorUndefinedStateD0Ev", CCSTutorUndefinedState::~CCSTutorUndefinedState),
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD37C0, "_ZN22CCSTutorUndefinedState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", CCSTutorUndefinedState::CheckForStateTransition),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3850, "_ZN22CCSTutorUndefinedState14GetStateStringEv", CCSTutorUndefinedState::GetStateString),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DD3810, "_ZN22CCSTutorUndefinedState19HandlePlayerSpawnedEP11CBaseEntityS1_", CCSTutorUndefinedState::HandlePlayerSpawned),	// NOXREF
//CCSTutorWaitingForStartState
	//HOOK_SYMBOLDEF(0x01DD3860, "_ZN28CCSTutorWaitingForStartStateC2Ev", CCSTutorWaitingForStartState::CCSTutorWaitingForStartState),
	// virtual func
	//HOOK_SYMBOLDEF(0x01DD3880, "_ZN28CCSTutorWaitingForStartStateD0Ev", CCSTutorWaitingForStartState::~CCSTutorWaitingForStartState),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD38C0, "_ZN28CCSTutorWaitingForStartState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", CCSTutorWaitingForStartState::CheckForStateTransition),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD3910, "_ZN28CCSTutorWaitingForStartState14GetStateStringEv", CCSTutorWaitingForStartState::GetStateString),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DD3920, "_ZN28CCSTutorWaitingForStartState19HandlePlayerSpawnedEP11CBaseEntityS1_", CCSTutorWaitingForStartState::HandlePlayerSpawned),	// NOXREF
	//HOOK_SYMBOLDEF(0x01DD3960, "_ZN28CCSTutorWaitingForStartState18HandleBuyTimeStartEP11CBaseEntityS1_", CCSTutorWaitingForStartState::HandleBuyTimeStart),	// NOXREF
//CCSTutorBuyMenuState
	//HOOK_SYMBOLDEF(0x01DD3970, "_ZN20CCSTutorBuyMenuStateC2Ev", CCSTutorBuyMenuState::CCSTutorBuyMenuState),
	// virtual func
	//HOOK_SYMBOLDEF(0x01DD3990, "_ZN20CCSTutorBuyMenuStateD0Ev", CCSTutorBuyMenuState::~CCSTutorBuyMenuState),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD39D0, "_ZN20CCSTutorBuyMenuState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", CCSTutorBuyMenuState::CheckForStateTransition),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01DD39F0, "_ZN20CCSTutorBuyMenuState14GetStateStringEv", CCSTutorBuyMenuState::GetStateString),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DD3A00, "_ZN20CCSTutorBuyMenuState16HandleRoundStartEP11CBaseEntityS1_", CCSTutorBuyMenuState::HandleRoundStart),	// NOXREF
	HOOK_SYMBOLDEF(0x01DD3FB0, "_ZL22ParseMessageParametersRPcP12TutorMessage", ParseMessageParameters),
	//HOOK_DEF(0x0, ConstructTutorMessage),		// NOXREF
	//HOOK_DEF(0x0, ReadDefaultValues),			// NOXREF

#endif // Tutor_CS_Region

#ifndef Bot_Profile

//BotProfile
	//HOOK_DEF(0x0, MethodThunk<BotProfile>::Constructor),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile7GetNameEv", BotProfile::GetName),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile13GetAggressionEv", BotProfile::GetAggression),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile8GetSkillEv", BotProfile::GetSkill),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile11GetTeamworkEv", BotProfile::GetTeamwork),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile19GetWeaponPreferenceEi", BotProfile::GetWeaponPreference),	// NOXREF
	HOOK_SYMBOLDEF(0x01D34DC0, "_ZNK10BotProfile27GetWeaponPreferenceAsStringEi", BotProfile::GetWeaponPreferenceAsString),
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile24GetWeaponPreferenceCountEv", BotProfile::GetWeaponPreferenceCount),	// NOXREF
	HOOK_SYMBOLDEF(0x01D34DF0, "_ZNK10BotProfile20HasPrimaryPreferenceEv", BotProfile::HasPrimaryPreference),
	HOOK_SYMBOLDEF(0x01D34E50, "_ZNK10BotProfile19HasPistolPreferenceEv", BotProfile::HasPistolPreference),
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile7GetCostEv", BotProfile::GetCost),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile7GetSkinEv", BotProfile::GetSkin),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile12IsDifficultyE17BotDifficultyType", BotProfile::IsDifficulty),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile13GetVoicePitchEv", BotProfile::GetVoicePitch),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile15GetReactionTimeEv", BotProfile::GetReactionTime),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile14GetAttackDelayEv", BotProfile::GetAttackDelay),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile12GetVoiceBankEv", BotProfile::GetVoiceBank),	// NOXREF
	HOOK_SYMBOLDEF(0x01D34E90, "_ZNK10BotProfile14IsValidForTeamE18BotProfileTeamType", BotProfile::IsValidForTeam),
	//HOOK_SYMBOLDEF(0x0, "_ZNK10BotProfile15PrefersSilencerEv", BotProfile::PrefersSilencer),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN10BotProfile7InheritEPKS_S1_", BotProfile::Inherit),
//BotProfileManager
	//HOOK_SYMBOLDEF(0x01D34EC0, "_ZN17BotProfileManagerC2Ev", BotProfileManager::BotProfileManager),
	//HOOK_SYMBOLDEF(0x01D35C30, "_ZN17BotProfileManagerD2Ev", BotProfileManager::~BotProfileManager),
	HOOK_SYMBOLDEF(0x01D34F20, "_ZN17BotProfileManager4InitEPKcPj", BotProfileManager::Init),
	HOOK_SYMBOLDEF(0x01D35CE0, "_ZN17BotProfileManager5ResetEv", BotProfileManager::Reset),
	//HOOK_SYMBOLDEF(0x0, "_ZNK17BotProfileManager10GetProfileEPKc18BotProfileTeamType", BotProfileManager::GetProfile),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK17BotProfileManager14GetProfileListEv", BotProfileManager::GetProfileList),	// NOXREF
	HOOK_SYMBOLDEF(0x01D36070, "_ZNK17BotProfileManager16GetRandomProfileE17BotDifficultyType18BotProfileTeamType", BotProfileManager::GetRandomProfile),
	HOOK_SYMBOLDEF(0x01D35D90, "_ZN17BotProfileManager13GetCustomSkinEi", BotProfileManager::GetCustomSkin),
	HOOK_SYMBOLDEF(0x01D35DD0, "_ZN17BotProfileManager22GetCustomSkinModelnameEi", BotProfileManager::GetCustomSkinModelname),
	HOOK_SYMBOLDEF(0x01D35DB0, "_ZN17BotProfileManager18GetCustomSkinFnameEi", BotProfileManager::GetCustomSkinFname),
	//HOOK_SYMBOLDEF(0x01D35DF0, "_ZN17BotProfileManager18GetCustomSkinIndexEPKcS1_", BotProfileManager::GetCustomSkinIndex),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK17BotProfileManager13GetVoiceBanksEv", BotProfileManager::GetVoiceBanks),	// NOXREF
	HOOK_SYMBOLDEF(0x01D35E60, "_ZN17BotProfileManager18FindVoiceBankIndexEPKc", BotProfileManager::FindVoiceBankIndex),

#endif // Bot_Profile

#ifndef VoiceManager_Region

//CVoiceGameMgr
	//constructor/destructor func
	//HOOK_SYMBOLDEF(0x0, "_ZN13CVoiceGameMgrD0Ev", CVoiceGameMgr::~CVoiceGameMgr),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x01DCC6F0, "_ZN13CVoiceGameMgrC2Ev", CVoiceGameMgr::CVoiceGameMgr),
	HOOK_SYMBOLDEF(0x01DCC740, "_ZN13CVoiceGameMgr4InitEP19IVoiceGameMgrHelperi", CVoiceGameMgr::Init),
	//HOOK_SYMBOLDEF(0x01DCC7D0, "_ZN13CVoiceGameMgr9SetHelperEP19IVoiceGameMgrHelper", CVoiceGameMgr::SetHelper),	// NOXREF
	HOOK_SYMBOLDEF(0x01DCC7E0, "_ZN13CVoiceGameMgr6UpdateEd", CVoiceGameMgr::Update),
	HOOK_SYMBOLDEF(0x01DCC800, "_ZN13CVoiceGameMgr15ClientConnectedEP7edict_s", CVoiceGameMgr::ClientConnected),
	HOOK_SYMBOLDEF(0x01DCC910, "_ZN13CVoiceGameMgr13ClientCommandEP11CBasePlayerPKc", CVoiceGameMgr::ClientCommand),
	HOOK_SYMBOLDEF(0x01DCC890, "_ZN13CVoiceGameMgr22PlayerHasBlockedPlayerEP11CBasePlayerS1_", CVoiceGameMgr::PlayerHasBlockedPlayer),
	HOOK_SYMBOLDEF(0x01DCCB10, "_ZN13CVoiceGameMgr11UpdateMasksEv", CVoiceGameMgr::UpdateMasks),
	HOOK_SYMBOLDEF(0x01DCCAB0, "_ZL16VoiceServerDebugPKcz", VoiceServerDebug),

#endif // VoiceManager_Region

#ifndef Vector_Region

	HOOK_SYMBOLDEF(0x01D71160, "_ZN8Vector2D16NormalizeInPlaceEv", Vector2D::NormalizeInPlace),

#ifdef PLAY_GAMEDLL
	HOOK_SYMBOLDEF(0x01D290C0, "_ZN6Vector16NormalizeInPlaceEv", Vector::NormalizeInPlace<>),
#else
	HOOK_SYMBOLDEF(0x01D290C0, "_ZN6Vector16NormalizeInPlaceEv", Vector::NormalizeInPlace),
#endif

#ifdef _WIN32

	HOOK_DEF(0x01D12570, Vector::Length),
	HOOK_DEF(0x01D9C290, Vector::Length2D),
	HOOK_DEF(0x01D4EA30, Vector::Normalize),
	HOOK_DEF(0x01DCB800, Vector::operator==),
	HOOK_DEF(0x01D130D0, Vector::IsLengthLessThan),
	HOOK_DEF(0x01D18AC0, Vector::IsLengthGreaterThan),
	HOOK_DEF(0x01D34D90, DotProduct, float_precision (const Vector &, const Vector &)),

#endif // _WIN32

#endif // Vector_Region

#ifndef Nav_Region

//Nav_File
	//HOOK_DEF(0x0, COM_FixSlashes),											// NOXREF
	//HOOK_SYMBOLDEF(0x01D44E00, "_Z14GetBspFilenamePKc", GetBspFilename),		// NOXREF
	HOOK_SYMBOLDEF(0x01D45CF0, "_Z17SaveNavigationMapPKc", SaveNavigationMap),
	HOOK_SYMBOLDEF(0x01D45F80, "_Z16LoadLocationFilePKc", LoadLocationFile),
	HOOK_SYMBOLDEF(0x01D46170, "_Z24SanityCheckNavigationMapPKc", SanityCheckNavigationMap),
	HOOK_SYMBOLDEF(0x01D46310, "_Z17LoadNavigationMapv", LoadNavigationMap),
//IImprovEvent
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56970, "_ZN12IImprovEvent15OnMoveToSuccessERK6Vector", IImprovEvent::OnMoveToSuccess),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56980, "_ZN12IImprovEvent15OnMoveToFailureERK6VectorNS_17MoveToFailureTypeE", IImprovEvent::OnMoveToFailure),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56990, "_ZN12IImprovEvent8OnInjuryEf", IImprovEvent::OnInjury),
//CImprov
	// virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov7IsAliveEv", CImprov::IsAlive),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov6MoveToERK6Vector", CImprov::MoveTo),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov6LookAtERK6Vector", CImprov::LookAt),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov11ClearLookAtEv", CImprov::ClearLookAt),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov6FaceToERK6Vector", CImprov::FaceTo),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov11ClearFaceToEv", CImprov::ClearFaceTo),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov12IsAtMoveGoalEf", CImprov::IsAtMoveGoal),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9HasLookAtEv", CImprov::HasLookAt),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9HasFaceToEv", CImprov::HasFaceTo),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov12IsAtFaceGoalEv", CImprov::IsAtFaceGoal),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZNK7CImprov16IsFriendInTheWayERK6Vector", CImprov::IsFriendInTheWay, bool(const Vector &) const),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZNK7CImprov16IsFriendInTheWayEP11CBaseEntityRK6Vector", CImprov::IsFriendInTheWay, bool(CBaseEntity *, const Vector &) const),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov11MoveForwardEv", CImprov::MoveForward),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov12MoveBackwardEv", CImprov::MoveBackward),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov10StrafeLeftEv", CImprov::StrafeLeft),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov11StrafeRightEv", CImprov::StrafeRight),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov4JumpEv", CImprov::Jump),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov6CrouchEv", CImprov::Crouch),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov7StandUpEv", CImprov::StandUp),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov9TrackPathERK6Vectorf", CImprov::TrackPath),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov11StartLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_", CImprov::StartLadder),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov14TraverseLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_f", CImprov::TraverseLadder),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov30GetSimpleGroundHeightWithFloorEPK6VectorPfPS0_", CImprov::GetSimpleGroundHeightWithFloor),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov3RunEv", CImprov::Run),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov4WalkEv", CImprov::Walk),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov4StopEv", CImprov::Stop),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov12GetMoveAngleEv", CImprov::GetMoveAngle),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov12GetFaceAngleEv", CImprov::GetFaceAngle),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov7GetFeetEv", CImprov::GetFeet),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov11GetCentroidEv", CImprov::GetCentroid),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov7GetEyesEv", CImprov::GetEyes),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9IsRunningEv", CImprov::IsRunning),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9IsWalkingEv", CImprov::IsWalking),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9IsStoppedEv", CImprov::IsStopped),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov11IsCrouchingEv", CImprov::IsCrouching),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9IsJumpingEv", CImprov::IsJumping),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov13IsUsingLadderEv", CImprov::IsUsingLadder),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov10IsOnGroundEv", CImprov::IsOnGround),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov8IsMovingEv", CImprov::IsMoving),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov6CanRunEv", CImprov::CanRun),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9CanCrouchEv", CImprov::CanCrouch),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov7CanJumpEv", CImprov::CanJump),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov9IsVisibleERK6Vectorb", CImprov::IsVisible),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov19IsPlayerLookingAtMeEP11CBasePlayerf", CImprov::IsPlayerLookingAtMe),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov22IsAnyPlayerLookingAtMeEif", CImprov::IsAnyPlayerLookingAtMe),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov32GetClosestPlayerByTravelDistanceEiPf", CImprov::GetClosestPlayerByTravelDistance),
	//HOOK_SYMBOLDEF(0x0, "_ZNK7CImprov16GetLastKnownAreaEv", CImprov::GetLastKnownArea),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov8OnUpdateEf", CImprov::OnUpdate),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov8OnUpkeepEf", CImprov::OnUpkeep),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov7OnResetEv", CImprov::OnReset),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov11OnGameEventE13GameEventTypeP11CBaseEntityS2_", CImprov::OnGameEvent),
	//HOOK_SYMBOLDEF(0x0, "_ZN7CImprov7OnTouchEP11CBaseEntity", CImprov::OnTouch),
//CNavNode
	//HOOK_SYMBOLDEF(0x01D46F60, "_ZN8CNavNodeC2EPK6VectorS2_PS_", CNavNode::CNavNode),
	HOOK_SYMBOLDEF(0x01D47000, "_ZN8CNavNode7GetNodeEPK6Vector", CNavNode::GetNode),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode16GetConnectedNodeE10NavDirType", CNavNode::GetConnectedNode),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode11GetPositionEv", CNavNode::GetPosition),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode9GetNormalEv", CNavNode::GetNormal),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode5GetIDEv", CNavNode::GetID),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode8GetFirstEv", CNavNode::GetFirst),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode13GetListLengthEv", CNavNode::GetListLength),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode7GetNextEv", CNavNode::GetNext),
	HOOK_SYMBOLDEF(0x01D46FF0, "_ZN8CNavNode9ConnectToEPS_10NavDirType", CNavNode::ConnectTo),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode9GetParentEv", CNavNode::GetParent),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode13MarkAsVisitedE10NavDirType", CNavNode::MarkAsVisited),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode10HasVisitedE10NavDirType", CNavNode::HasVisited),
	//HOOK_SYMBOLDEF(0x01D470E0, "_ZNK8CNavNode10IsBiLinkedE10NavDirType", CNavNode::IsBiLinked),	// NOXREF
	HOOK_SYMBOLDEF(0x01D47110, "_ZNK8CNavNode12IsClosedCellEv", CNavNode::IsClosedCell),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode5CoverEv", CNavNode::Cover),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode9IsCoveredEv", CNavNode::IsCovered),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode10AssignAreaEP8CNavArea", CNavNode::AssignArea),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode7GetAreaEv", CNavNode::GetArea),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavNode13SetAttributesEh", CNavNode::SetAttributes),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavNode13GetAttributesEv", CNavNode::GetAttributes),
//CNavPath
	//HOOK_DEF(0x0, MethodThunk<CNavPath>::Constructor),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavPathixEi", CNavPath::operator[]),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavPath15GetSegmentCountEv", CNavPath::GetSegmentCount),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavPath11GetEndpointEv", CNavPath::GetEndpoint),
	HOOK_SYMBOLDEF(0x01D47570, "_ZNK8CNavPath7IsAtEndERK6Vector", CNavPath::IsAtEnd),
	HOOK_SYMBOLDEF(0x01D475D0, "_ZNK8CNavPath9GetLengthEv", CNavPath::GetLength),
	//HOOK_SYMBOLDEF(0x01D47620, "_ZNK8CNavPath17GetPointAlongPathEfP6Vector", CNavPath::GetPointAlongPath),				// NOXREF
	HOOK_SYMBOLDEF(0x01D47760, "_ZNK8CNavPath24GetSegmentIndexAlongPathEf", CNavPath::GetSegmentIndexAlongPath),
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CNavPath7IsValidEv", CNavPath::IsValid),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CNavPath10InvalidateEv", CNavPath::Invalidate),
	//HOOK_SYMBOLDEF(0x01D47AB0, "_ZN8CNavPath4DrawEv", CNavPath::Draw),								// NOXREF
	//HOOK_SYMBOLDEF(0x01D477F0, "_ZNK8CNavPath22FindClosestPointOnPathEPK6VectoriiPS0_", CNavPath::FindClosestPointOnPath),		// NOXREF
	HOOK_SYMBOLDEF(0x01D47E20, "_ZN8CNavPath8OptimizeEv", CNavPath::Optimize),								// PURE
	HOOK_SYMBOLDEF(0x01D47170, "_ZN8CNavPath20ComputePathPositionsEv", CNavPath::ComputePathPositions),
	HOOK_SYMBOLDEF(0x01D47A00, "_ZN8CNavPath16BuildTrivialPathEPK6VectorS2_", CNavPath::BuildTrivialPath),
	//HOOK_SYMBOLDEF(0x01D47B40, "_ZN8CNavPath20FindNextOccludedNodeEi", CNavPath::FindNextOccludedNode),				// NOXREF
//CStuckMonitor
	//HOOK_DEF(0x01D49B70, MethodThunk<CStuckMonitor>::Constructor),
	HOOK_SYMBOLDEF(0x01D49B90, "_ZN13CStuckMonitor5ResetEv", CStuckMonitor::Reset),
	HOOK_SYMBOLDEF(0x01D49BA0, "_ZN13CStuckMonitor6UpdateEP7CImprov", CStuckMonitor::Update),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CStuckMonitor7IsStuckEv", CStuckMonitor::IsStuck),
	//HOOK_SYMBOLDEF(0x0, "_ZNK13CStuckMonitor11GetDurationEv", CStuckMonitor::GetDuration),
//CNavPathFollower
	HOOK_DEF(0x01D47E30, MethodThunk<CNavPathFollower>::Constructor),
	//HOOK_SYMBOLDEF(0x0, "_ZN16CNavPathFollower9SetImprovEP7CImprov", CNavPathFollower::SetImprov),
	//HOOK_SYMBOLDEF(0x0, "_ZN16CNavPathFollower7SetPathEP8CNavPath", CNavPathFollower::SetPath),
	HOOK_SYMBOLDEF(0x01D47E60, "_ZN16CNavPathFollower5ResetEv", CNavPathFollower::Reset),
	HOOK_SYMBOLDEF(0x01D47E80, "_ZN16CNavPathFollower6UpdateEfb", CNavPathFollower::Update),
	//HOOK_SYMBOLDEF(0x0, "_ZN16CNavPathFollower5DebugEb", CNavPathFollower::Debug),
	//HOOK_SYMBOLDEF(0x0, "_ZNK16CNavPathFollower7IsStuckEv", CNavPathFollower::IsStuck),
	//HOOK_SYMBOLDEF(0x0, "_ZN16CNavPathFollower10ResetStuckEv", CNavPathFollower::ResetStuck),
	//HOOK_SYMBOLDEF(0x0, "_ZNK16CNavPathFollower16GetStuckDurationEv", CNavPathFollower::GetStuckDuration),
	HOOK_SYMBOLDEF(0x01D49460, "_ZN16CNavPathFollower22FeelerReflexAdjustmentEP6Vectorf", CNavPathFollower::FeelerReflexAdjustment),
	HOOK_SYMBOLDEF(0x01D48450, "_ZNK16CNavPathFollower21FindOurPositionOnPathEP6Vectorb", CNavPathFollower::FindOurPositionOnPath),
	HOOK_SYMBOLDEF(0x01D487B0, "_ZN16CNavPathFollower13FindPathPointEfP6VectorPi", CNavPathFollower::FindPathPoint),
//HidingSpot
	//HOOK_DEF(0x01D37DB0, (MethodThunk<HidingSpot>::Constructor), void()),
	//HOOK_DEF(0x01D37E40, (MethodThunk<HidingSpot, const Vector *, unsigned char>::Constructor), void(const Vector *, unsigned char)),

	HOOK_SYMBOLDEF(0x01D37EC0, "_ZNK10HidingSpot4SaveEij", HidingSpot::Save),
	HOOK_SYMBOLDEF(0x01D37F00, "_ZN10HidingSpot4LoadEP9SteamFilej", HidingSpot::Load),
//SteamFile
	//HOOK_DEF(0x0, MethodThunk<SteamFile>::Constructor),
	//HOOK_DEF(0x0, MethodThunk<SteamFile>::Destructor),
	//HOOK_SYMBOLDEF(0x0, "_ZNK9SteamFile7IsValidEv", SteamFile::IsValid),
	HOOK_SYMBOLDEF(0x01D46F00, "_ZN9SteamFile4ReadEPvi", SteamFile::Read),
//CNavArea
	//HOOK_SYMBOLDEF(0x01D45A50, "_ZNK14PlaceDirectory12EntryToPlaceEt", PlaceDirectory::EntryToPlace),	// NOTE: need hook LoadNavigationMap
	HOOK_SYMBOLDEF(0x01D44F80, "_ZN8CNavArea4SaveEij", CNavArea::Save, void (int, unsigned int)),
	HOOK_SYMBOLDEF(0x01D44E60, "_ZNK8CNavArea4SaveEP8_IO_FILE", CNavArea::Save, void (FILE *) const),
	HOOK_SYMBOLDEF(0x01D45330, "_ZN8CNavArea4LoadEP9SteamFilej", CNavArea::Load),
	HOOK_SYMBOLDEF(0x01D45AA0, "_ZN8CNavArea8PostLoadEv", CNavArea::PostLoad),
	HOOK_DEF(0x01D38040, (MethodThunk<CNavArea>::Constructor), void()),
	//HOOK_DEF(0x0, (MethodThunk<CNavArea, const Vector *, const Vector *>::Constructor), void (const Vector *, const Vector *)),
	//HOOK_DEF(0x0, (MethodThunk<CNavArea, const Vector *, const Vector *, const Vector *, const Vector *>::Constructor), void (const Vector *, const Vector *, const Vector *, const Vector *)),
	//HOOK_DEF(0x0, (MethodThunk<CNavArea, CNavNode *, CNavNode *, CNavNode *, CNavNode *>::Constructor), void (CNavNode *, CNavNode *, CNavNode *, CNavNode *)),
	//HOOK_DEF(0x01D386A0, MethodThunk<CNavArea>::Destructor),
	HOOK_SYMBOLDEF(0x01D37FE0, "_ZN8CNavArea10InitializeEv", CNavArea::Initialize),
	//HOOK_SYMBOLDEF(0x01D388A0, "_ZN8CNavArea15OnDestroyNotifyEPS_", CNavArea::OnDestroyNotify),	// NOXREF
	HOOK_SYMBOLDEF(0x01D38960, "_ZN8CNavArea9ConnectToEPS_10NavDirType", CNavArea::ConnectTo),
	//HOOK_SYMBOLDEF(0x01D389D0, "_ZN8CNavArea10DisconnectEPS_", CNavArea::Disconnect),		// NOXREF
	HOOK_SYMBOLDEF(0x01D38A40, "_ZN8CNavArea11FinishMergeEPS_", CNavArea::FinishMerge),
	HOOK_SYMBOLDEF(0x01D38B60, "_ZN8CNavArea24MergeAdjacentConnectionsEPS_", CNavArea::MergeAdjacentConnections),
	//HOOK_SYMBOLDEF(0x01D38D70, "_ZN8CNavArea11AssignNodesEPS_", CNavArea::AssignNodes),		// NOXREF
	HOOK_SYMBOLDEF(0x01D38DC0, "_ZN8CNavArea9SplitEditEbfPPS_S1_", CNavArea::SplitEdit),
	HOOK_SYMBOLDEF(0x01D390F0, "_ZNK8CNavArea11IsConnectedEPKS_10NavDirType", CNavArea::IsConnected),
	HOOK_SYMBOLDEF(0x01D391B0, "_ZN8CNavArea19ComputeHeightChangeEPKS_", CNavArea::ComputeHeightChange),
	HOOK_SYMBOLDEF(0x01D391E0, "_ZN8CNavArea15FinishSplitEditEPS_10NavDirType", CNavArea::FinishSplitEdit),
	HOOK_SYMBOLDEF(0x01D39500, "_ZN8CNavArea10SpliceEditEPS_", CNavArea::SpliceEdit),
	HOOK_SYMBOLDEF(0x01D39CA0, "_ZN8CNavArea9MergeEditEPS_", CNavArea::MergeEdit),
	//HOOK_SYMBOLDEF(0x01D3A290, "_ZN8CNavArea5StripEv", CNavArea::Strip),	// NOXREF
	HOOK_SYMBOLDEF(0x01D3C6C0, "_ZNK8CNavArea13IsOverlappingEPK6Vector", CNavArea::IsOverlapping, bool (const Vector *) const),
	HOOK_SYMBOLDEF(0x01D3C710, "_ZNK8CNavArea13IsOverlappingEPKS_", CNavArea::IsOverlapping, bool (const CNavArea *) const),
	//HOOK_SYMBOLDEF(0x01D3C760, "_ZNK8CNavArea14IsOverlappingXEPKS_", CNavArea::IsOverlappingX),		// NOXREF
	//HOOK_SYMBOLDEF(0x01D3C790, "_ZNK8CNavArea14IsOverlappingYEPKS_", CNavArea::IsOverlappingY),				// NOXREF
	HOOK_SYMBOLDEF(0x01D3C7C0, "_ZNK8CNavArea8ContainsEPK6Vector", CNavArea::Contains),
	HOOK_SYMBOLDEF(0x01D3C8B0, "_ZNK8CNavArea10IsCoplanarEPKS_", CNavArea::IsCoplanar),
	HOOK_SYMBOLDEF(0x01D3CA60, "_ZNK8CNavArea4GetZEPK6Vector", CNavArea::GetZ, float (const Vector *) const),	// NOTE: definitely need to hook CNavAreaGrid::GetNavArea!!
	//HOOK_SYMBOLDEF(0x01D3CB50, "_ZNK8CNavArea4GetZEff", CNavArea::GetZ, float (float x, float y) const),	// NOXREF
	HOOK_SYMBOLDEF(0x01D3CB80, "_ZNK8CNavArea21GetClosestPointOnAreaEPK6VectorPS0_", CNavArea::GetClosestPointOnArea),
	//HOOK_SYMBOLDEF(0x01D3CCD0, "_ZNK8CNavArea25GetDistanceSquaredToPointEPK6Vector", CNavArea::GetDistanceSquaredToPoint),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D3CDF0, "_ZNK8CNavArea21GetRandomAdjacentAreaE10NavDirType", CNavArea::GetRandomAdjacentArea),		// NOXREF
	HOOK_SYMBOLDEF(0x01D3CE40, "_ZNK8CNavArea13ComputePortalEPKS_10NavDirTypeP6VectorPf", CNavArea::ComputePortal),
	HOOK_SYMBOLDEF(0x01D3CFD0, "_ZNK8CNavArea27ComputeClosestPointInPortalEPKS_10NavDirTypePK6VectorPS3_", CNavArea::ComputeClosestPointInPortal),
	//HOOK_SYMBOLDEF(0x01D3D280, "_ZNK8CNavArea6IsEdgeE10NavDirType", CNavArea::IsEdge),	// NOXREF
	HOOK_SYMBOLDEF(0x01D3D310, "_ZNK8CNavArea16ComputeDirectionEP6Vector", CNavArea::ComputeDirection),
	HOOK_SYMBOLDEF(0x01D3D420, "_ZN8CNavArea4DrawEhhhi", CNavArea::Draw),
	HOOK_SYMBOLDEF(0x01D3D860, "_ZN8CNavArea16DrawMarkedCornerE13NavCornerTypehhhi", CNavArea::DrawMarkedCorner),
	HOOK_SYMBOLDEF(0x01D3DAB0, "_ZN8CNavArea13AddToOpenListEv", CNavArea::AddToOpenList),
	HOOK_SYMBOLDEF(0x01D3DB50, "_ZN8CNavArea16UpdateOnOpenListEv", CNavArea::UpdateOnOpenList),
	HOOK_SYMBOLDEF(0x01D3DBC0, "_ZN8CNavArea18RemoveFromOpenListEv", CNavArea::RemoveFromOpenList),
	HOOK_SYMBOLDEF(0x01D3DC10, "_ZN8CNavArea16ClearSearchListsEv", CNavArea::ClearSearchLists),
	HOOK_SYMBOLDEF(0x01D3DC40, "_ZNK8CNavArea9GetCornerE13NavCornerType", CNavArea::GetCorner),
	HOOK_SYMBOLDEF(0x01D3DCF0, "_ZNK8CNavArea21IsHidingSpotCollisionEPK6Vector", CNavArea::IsHidingSpotCollision),
	HOOK_SYMBOLDEF(0x01D3DD50, "_Z19IsHidingSpotInCoverPK6Vector", IsHidingSpotInCover),
	HOOK_SYMBOLDEF(0x01D3DEA0, "_ZN8CNavArea18ComputeHidingSpotsEv", CNavArea::ComputeHidingSpots),
	HOOK_SYMBOLDEF(0x01D3E790, "_ZN8CNavArea18ComputeSniperSpotsEv", CNavArea::ComputeSniperSpots),
	HOOK_SYMBOLDEF(0x01D3E7D0, "_ZN8CNavArea16GetSpotEncounterEPKS_S1_", CNavArea::GetSpotEncounter),
	HOOK_SYMBOLDEF(0x01D3E810, "_ZN8CNavArea17AddSpotEncountersEPKS_10NavDirTypeS1_S2_", CNavArea::AddSpotEncounters),
	HOOK_SYMBOLDEF(0x01D3EC50, "_ZN8CNavArea21ComputeSpotEncountersEv", CNavArea::ComputeSpotEncounters),
	HOOK_SYMBOLDEF(0x01D3ED20, "_ZN8CNavArea11DecayDangerEv", CNavArea::DecayDanger),
	HOOK_SYMBOLDEF(0x01D3ED60, "_ZN8CNavArea14IncreaseDangerEif", CNavArea::IncreaseDanger),
	HOOK_SYMBOLDEF(0x01D3EDC0, "_ZN8CNavArea9GetDangerEi", CNavArea::GetDanger),
	HOOK_SYMBOLDEF(0x01D40110, "_ZNK8CNavArea14GetPlayerCountEiP11CBasePlayer", CNavArea::GetPlayerCount),
	HOOK_SYMBOLDEF(0x01D40340, "_ZN8CNavArea18DrawConnectedAreasEv", CNavArea::DrawConnectedAreas),
	HOOK_SYMBOLDEF(0x01D40870, "_ZN8CNavArea11RaiseCornerE13NavCornerTypei", CNavArea::RaiseCorner),
	HOOK_SYMBOLDEF(0x01D427C0, "_ZN8CNavArea20ComputeApproachAreasEv", CNavArea::ComputeApproachAreas),
	//HOOK_DEF(0x0, MethodThunk<CollectHidingSpotsFunctor>::Constructor),
	//HOOK_SYMBOLDEF(0x0, "_ZN25CollectHidingSpotsFunctor10RemoveSpotEi", CollectHidingSpotsFunctor::RemoveSpot),
	//HOOK_DEF(0x01D43000, MethodThunk<CNavAreaGrid>::Constructor),	// NOXREF
	//HOOK_DEF(0x01D43090, MethodThunk<CNavAreaGrid>::Destructor),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D43180, "_ZN12CNavAreaGrid5ResetEv", CNavAreaGrid::Reset),	// NOXREF
	HOOK_SYMBOLDEF(0x01D43230, "_ZN12CNavAreaGrid10InitializeEffff", CNavAreaGrid::Initialize),
	HOOK_SYMBOLDEF(0x01D43390, "_ZN12CNavAreaGrid10AddNavAreaEP8CNavArea", CNavAreaGrid::AddNavArea),
	HOOK_SYMBOLDEF(0x01D43560, "_ZN12CNavAreaGrid13RemoveNavAreaEP8CNavArea", CNavAreaGrid::RemoveNavArea),
	HOOK_SYMBOLDEF(0x01D43710, "_ZNK12CNavAreaGrid10GetNavAreaEPK6Vectorf", CNavAreaGrid::GetNavArea),
	HOOK_SYMBOLDEF(0x01D43860, "_ZNK12CNavAreaGrid17GetNearestNavAreaEPK6Vectorb", CNavAreaGrid::GetNearestNavArea),
	HOOK_SYMBOLDEF(0x01D439C0, "_ZNK12CNavAreaGrid14GetNavAreaByIDEj", CNavAreaGrid::GetNavAreaByID),
	HOOK_SYMBOLDEF(0x01D439F0, "_ZNK12CNavAreaGrid8GetPlaceEPK6Vector", CNavAreaGrid::GetPlace),
	HOOK_SYMBOLDEF(0x01D3E4F0, "_Z18ClassifySniperSpotP10HidingSpot", ClassifySniperSpot),
	//HOOK_DEF(0x0, buildGoodSizedList),	// NOXREF
	HOOK_SYMBOLDEF(0x01D37CF0, "_Z18DestroyHidingSpotsv", DestroyHidingSpots),
	HOOK_SYMBOLDEF(0x01D40920, "_Z12EditNavAreas14NavEditCmdType", EditNavAreas),
	HOOK_SYMBOLDEF(0x01D42540, "_Z15GetGroundHeightPK6VectorPfPS_", GetGroundHeight),
	HOOK_SYMBOLDEF(0x01D42740, "_Z21GetSimpleGroundHeightPK6VectorPfPS_", GetSimpleGroundHeight),
	//HOOK_DEF(0x0, IsAreaVisible),			// NOXREF
	HOOK_SYMBOLDEF(0x01D40250, "_Z13GetMarkedAreav", GetMarkedArea),
	//HOOK_SYMBOLDEF(0x01D40260, "_Z17EditNavAreasResetv", EditNavAreasReset),	// NOXREF
	HOOK_SYMBOLDEF(0x01D40290, "_Z15DrawHidingSpotsPK8CNavArea", DrawHidingSpots),
	HOOK_SYMBOLDEF(0x01D3EE10, "_Z20IncreaseDangerNearbyifP8CNavAreaPK6Vectorf", IncreaseDangerNearby),
	HOOK_SYMBOLDEF(0x01D3F020, "_Z10DrawDangerv", DrawDanger),
	HOOK_SYMBOLDEF(0x01D3F1C0, "_Z14IsSpotOccupiedP11CBaseEntityPK6Vector", IsSpotOccupied),
	HOOK_SYMBOLDEF(0x01D3F2A0, "_Z20FindNearbyHidingSpotP11CBaseEntityPK6VectorP8CNavAreafbb", FindNearbyHidingSpot),
	//HOOK_SYMBOLDEF(0x01D3F650, "_ZN25CollectHidingSpotsFunctorclEP8CNavArea", CollectHidingSpotsFunctor::operator(), bool (CNavArea *area)),
	HOOK_SYMBOLDEF(0x01D3FDE0, "_Z21FindNearbyRetreatSpotP11CBaseEntityPK6VectorP8CNavAreafib", FindNearbyRetreatSpot, const Vector *(CBaseEntity *, const Vector *, CNavArea *, float, int, bool)),
	HOOK_SYMBOLDEF(0x01D3FAD0, "_Z20IsCrossingLineOfFireRK6VectorS1_P11CBaseEntityi", IsCrossingLineOfFire),
	HOOK_SYMBOLDEF(0x01D3F850, "_Z20FindRandomHidingSpotP11CBaseEntityjb", FindRandomHidingSpot),
	HOOK_SYMBOLDEF(0x01D37FB0, "_Z17GetHidingSpotByIDj", GetHidingSpotByID),
	HOOK_SYMBOLDEF(0x01D39F30, "_Z24ApproachAreaAnalysisPrepv", ApproachAreaAnalysisPrep),
	HOOK_SYMBOLDEF(0x01D39FD0, "_Z31CleanupApproachAreaAnalysisPrepv", CleanupApproachAreaAnalysisPrep),
	//HOOK_SYMBOLDEF(0x01D3A010, "_Z14DestroyLaddersv", DestroyLadders),	// NOXREF
	HOOK_SYMBOLDEF(0x01D3A060, "_Z20DestroyNavigationMapv", DestroyNavigationMap),
	HOOK_SYMBOLDEF(0x01D3A210, "_Z20StripNavigationAreasv", StripNavigationAreas),

#ifdef _WIN32

	HOOK_SYMBOLDEF(0x01D13120, "_ZNK8CNavArea15GetAdjacentAreaE10NavDirTypei", CNavArea::GetAdjacentArea),
	HOOK_SYMBOLDEF(0x01D2B2A0, "_ZN8CNavArea11PopOpenListEv", CNavArea::PopOpenList),
	HOOK_SYMBOLDEF(0x01D2B2C0, "_ZNK8CNavArea8IsClosedEv", CNavArea::IsClosed),

	HOOK_DEF(0x01D224C0, SnapToGrid, void (Vector *)),
	HOOK_DEF(0x01D22460, AddDirectionVector),
	HOOK_DEF(0x01D13150, AddAreaToOpenList),
	HOOK_DEF(0x01D3A870, FindFirstAreaInDirection),
	HOOK_DEF(0x01D3AD20, IsAreaRoughlySquare),
	HOOK_DEF(0x01D2B030, IsEntityWalkable),
	HOOK_DEF(0x01D2B0B0, IsWalkableTraceLineClear),
	HOOK_DEF(0x01D3A9E0, testJumpDown),

#endif // _WIN32

	//HOOK_DEF(0x0, findJumpDownArea),								// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_Z6SplitYP8CNavArea", SplitY),			// NOXREF

	HOOK_SYMBOLDEF(0x01D3A330, "_Z21ConnectGeneratedAreasv", ConnectGeneratedAreas),
	HOOK_SYMBOLDEF(0x01D3AAF0, "_Z19MergeGeneratedAreasv", MergeGeneratedAreas),
	HOOK_SYMBOLDEF(0x01D3AE00, "_Z6SplitXP8CNavArea", SplitX),
	HOOK_SYMBOLDEF(0x01D3AEE0, "_Z13SquareUpAreasv", SquareUpAreas),
	HOOK_SYMBOLDEF(0x01D3B100, "_Z8TestAreaP8CNavNodeii", TestArea),
	HOOK_SYMBOLDEF(0x01D3B2E0, "_Z9BuildAreaP8CNavNodeii", BuildArea),
	HOOK_SYMBOLDEF(0x01D3B3F0, "_Z12BuildLaddersv", BuildLadders),
	HOOK_SYMBOLDEF(0x01D3C1B0, "_Z13MarkJumpAreasv", MarkJumpAreas),
	HOOK_SYMBOLDEF(0x01D3C280, "_Z26GenerateNavigationAreaMeshv", GenerateNavigationAreaMesh),

#endif // Nav_Region

#ifndef Hostage_Region

//HostageState
	//HOOK_DEF(0x01D50DA0, MethodThunk<CHostageImprov>::Constructor),
	//HOOK_DEF(0x01D56E30, MethodThunk<CHostageImprov>::Destructor),
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56D70, "_ZN14CHostageImprov15OnMoveToSuccessERK6Vector", CHostageImprov::OnMoveToSuccess),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D562D0, "_ZN14CHostageImprov15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", CHostageImprov::OnMoveToFailure),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56D80, "_ZN14CHostageImprov8OnInjuryEf", CHostageImprov::OnInjury),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51040, "_ZNK14CHostageImprov7IsAliveEv", CHostageImprov::IsAlive),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51060, "_ZN14CHostageImprov6MoveToERK6Vector", CHostageImprov::MoveTo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51240, "_ZN14CHostageImprov6LookAtERK6Vector", CHostageImprov::LookAt),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51270, "_ZN14CHostageImprov11ClearLookAtEv", CHostageImprov::ClearLookAt),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51280, "_ZN14CHostageImprov6FaceToERK6Vector", CHostageImprov::FaceTo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D512B0, "_ZN14CHostageImprov11ClearFaceToEv", CHostageImprov::ClearFaceTo),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51AC0, "_ZNK14CHostageImprov12IsAtMoveGoalEf", CHostageImprov::IsAtMoveGoal),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C20, "_ZNK14CHostageImprov9HasLookAtEv", CHostageImprov::HasLookAt),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C30, "_ZNK14CHostageImprov9HasFaceToEv", CHostageImprov::HasFaceTo),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51B20, "_ZNK14CHostageImprov12IsAtFaceGoalEv", CHostageImprov::IsAtFaceGoal),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51B30, "_ZNK14CHostageImprov16IsFriendInTheWayERK6Vector", CHostageImprov::IsFriendInTheWay, bool (const Vector &) const),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51CB0, "_ZNK14CHostageImprov16IsFriendInTheWayEP11CBaseEntityRK6Vector", CHostageImprov::IsFriendInTheWay, bool (CBaseEntity *, const Vector &) const),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C40, "_ZN14CHostageImprov11MoveForwardEv", CHostageImprov::MoveForward),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C50, "_ZN14CHostageImprov12MoveBackwardEv", CHostageImprov::MoveBackward),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C60, "_ZN14CHostageImprov10StrafeLeftEv", CHostageImprov::StrafeLeft),		// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C70, "_ZN14CHostageImprov11StrafeRightEv", CHostageImprov::StrafeRight),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52260, "_ZN14CHostageImprov4JumpEv", CHostageImprov::Jump),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D56710, "_ZN14CHostageImprov6CrouchEv", CHostageImprov::Crouch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D567A0, "_ZN14CHostageImprov7StandUpEv", CHostageImprov::StandUp),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52D80, "_ZN14CHostageImprov9TrackPathERK6Vectorf", CHostageImprov::TrackPath),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D530D0, "_ZN14CHostageImprov11StartLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_", CHostageImprov::StartLadder),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D530E0, "_ZN14CHostageImprov14TraverseLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_f", CHostageImprov::TraverseLadder),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D51150, "_ZN14CHostageImprov30GetSimpleGroundHeightWithFloorEPK6VectorPfPS0_", CHostageImprov::GetSimpleGroundHeightWithFloor),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52350, "_ZN14CHostageImprov3RunEv", CHostageImprov::Run),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52360, "_ZN14CHostageImprov4WalkEv", CHostageImprov::Walk),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52380, "_ZN14CHostageImprov4StopEv", CHostageImprov::Stop),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C80, "_ZNK14CHostageImprov12GetMoveAngleEv", CHostageImprov::GetMoveAngle),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56C90, "_ZNK14CHostageImprov12GetFaceAngleEv", CHostageImprov::GetFaceAngle),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D523F0, "_ZNK14CHostageImprov7GetFeetEv", CHostageImprov::GetFeet),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52400, "_ZNK14CHostageImprov11GetCentroidEv", CHostageImprov::GetCentroid),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52430, "_ZNK14CHostageImprov7GetEyesEv", CHostageImprov::GetEyes),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56CA0, "_ZNK14CHostageImprov9IsRunningEv", CHostageImprov::IsRunning),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56CB0, "_ZNK14CHostageImprov9IsWalkingEv", CHostageImprov::IsWalking),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56CC0, "_ZNK14CHostageImprov9IsStoppedEv", CHostageImprov::IsStopped),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56CD0, "_ZNK14CHostageImprov11IsCrouchingEv", CHostageImprov::IsCrouching),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56CE0, "_ZNK14CHostageImprov9IsJumpingEv", CHostageImprov::IsJumping),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56D20, "_ZNK14CHostageImprov13IsUsingLadderEv", CHostageImprov::IsUsingLadder),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52460, "_ZNK14CHostageImprov10IsOnGroundEv", CHostageImprov::IsOnGround),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52480, "_ZNK14CHostageImprov8IsMovingEv", CHostageImprov::IsMoving),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZNK14CHostageImprov6CanRunEv", CHostageImprov::CanRun),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZNK14CHostageImprov9CanCrouchEv", CHostageImprov::CanCrouch),			// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x0, "_ZNK14CHostageImprov7CanJumpEv", CHostageImprov::CanJump),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D524C0, "_ZNK14CHostageImprov9IsVisibleERK6Vectorb", CHostageImprov::IsVisible),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52530, "_ZNK14CHostageImprov19IsPlayerLookingAtMeEP11CBasePlayerf", CHostageImprov::IsPlayerLookingAtMe),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D526A0, "_ZNK14CHostageImprov22IsAnyPlayerLookingAtMeEif", CHostageImprov::IsAnyPlayerLookingAtMe),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D527B0, "_ZNK14CHostageImprov32GetClosestPlayerByTravelDistanceEiPf", CHostageImprov::GetClosestPlayerByTravelDistance),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56D60, "_ZNK14CHostageImprov16GetLastKnownAreaEv", CHostageImprov::GetLastKnownArea),		// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D54500, "_ZN14CHostageImprov8OnUpdateEf", CHostageImprov::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D53FF0, "_ZN14CHostageImprov8OnUpkeepEf", CHostageImprov::OnUpkeep),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D52A60, "_ZN14CHostageImprov7OnResetEv", CHostageImprov::OnReset),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D54C10, "_ZN14CHostageImprov11OnGameEventE13GameEventTypeP11CBaseEntityS2_", CHostageImprov::OnGameEvent),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D55280, "_ZN14CHostageImprov7OnTouchEP11CBaseEntity", CHostageImprov::OnTouch),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D51900, "_ZN14CHostageImprov12FaceOutwardsEv", CHostageImprov::FaceOutwards),
	HOOK_SYMBOLDEF(0x01D51F80, "_ZNK14CHostageImprov16IsFriendInTheWayEv", CHostageImprov::IsFriendInTheWay, bool () const),
	//HOOK_SYMBOLDEF(0x01D52150, "_ZN10CheckAheadclEP11CBaseEntity", CheckAhead::operator()),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CheckWayFunctorclEP8CHostage", CheckWayFunctor::operator()),
	HOOK_SYMBOLDEF(0x01D53E70, "_ZNK17KeepPersonalSpaceclEP11CBaseEntity", KeepPersonalSpace::operator()),
	//HOOK_SYMBOLDEF(0x01D52EE0, "_ZN14CHostageImprov20SetKnownGoodPositionERK6Vector", CHostageImprov::SetKnownGoodPosition),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov20GetKnownGoodPositionEv", CHostageImprov::GetKnownGoodPosition),
	HOOK_SYMBOLDEF(0x01D52F90, "_ZN14CHostageImprov24ResetToKnownGoodPositionEv", CHostageImprov::ResetToKnownGoodPosition),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov9ResetJumpEv", CHostageImprov::ResetJump),
	HOOK_SYMBOLDEF(0x01D55950, "_ZN14CHostageImprov10ApplyForceE6Vector", CHostageImprov::ApplyForce),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov17GetActualVelocityEv", CHostageImprov::GetActualVelocity),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov12SetMoveLimitENS_8MoveTypeE", CHostageImprov::SetMoveLimit),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov12GetMoveLimitEv", CHostageImprov::GetMoveLimit),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov7GetPathEv", CHostageImprov::GetPath),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov15GetPathFollowerEv", CHostageImprov::GetPathFollower),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov4IdleEv", CHostageImprov::Idle),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov6IsIdleEv", CHostageImprov::IsIdle),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov6FollowEP11CBasePlayer", CHostageImprov::Follow),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov11IsFollowingEPK11CBaseEntity", CHostageImprov::IsFollowing),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov6EscapeEv", CHostageImprov::Escape),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov10IsEscapingEv", CHostageImprov::IsEscaping),
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov7RetreatEv", CHostageImprov::Retreat),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov12IsRetreatingEv", CHostageImprov::IsRetreating),
	HOOK_SYMBOLDEF(0x01D55980, "_ZNK14CHostageImprov8IsAtHomeEv", CHostageImprov::IsAtHome),
	HOOK_SYMBOLDEF(0x01D559D0, "_ZNK14CHostageImprov16CanSeeRescueZoneEv", CHostageImprov::CanSeeRescueZone),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov15GetFollowLeaderEv", CHostageImprov::GetFollowLeader),
	HOOK_SYMBOLDEF(0x01D55A10, "_ZN14CHostageImprov23GetClosestVisiblePlayerEi", CHostageImprov::GetClosestVisiblePlayer),
	HOOK_SYMBOLDEF(0x01D55AD0, "_ZN14CHostageImprov25GetTimeSinceLastSawPlayerEi", CHostageImprov::GetTimeSinceLastSawPlayer),
	//HOOK_SYMBOLDEF(0x01D55B90, "_ZN14CHostageImprov22GetTimeSinceLastInjuryEv", CHostageImprov::GetTimeSinceLastInjury),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D55BC0, "_ZN14CHostageImprov21GetTimeSinceLastNoiseEv", CHostageImprov::GetTimeSinceLastNoise),	// NOXREF
	HOOK_SYMBOLDEF(0x01D54010, "_ZN14CHostageImprov17IsTerroristNearbyEv", CHostageImprov::IsTerroristNearby),
	HOOK_SYMBOLDEF(0x01D55C20, "_ZN14CHostageImprov8FrightenENS_9ScareTypeE", CHostageImprov::Frighten),
	HOOK_SYMBOLDEF(0x01D55BF0, "_ZNK14CHostageImprov8IsScaredEv", CHostageImprov::IsScared),
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov17GetScareIntensityEv", CHostageImprov::GetScareIntensity),				// DEFAULT
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov20IsIgnoringTerroristsEv", CHostageImprov::IsIgnoringTerrorists),				// DEFAULT
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov13GetAggressionEv", CHostageImprov::GetAggression),				// DEFAULT
	HOOK_SYMBOLDEF(0x01D55ED0, "_ZN14CHostageImprov7ChatterE18HostageChatterTypeb", CHostageImprov::Chatter),
	HOOK_SYMBOLDEF(0x01D55F80, "_ZN14CHostageImprov14DelayedChatterEf18HostageChatterTypeb", CHostageImprov::DelayedChatter),
	//HOOK_SYMBOLDEF(0x01D55FE0, "_ZN14CHostageImprov20UpdateDelayedChatterEv", CHostageImprov::UpdateDelayedChatter),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov9IsTalkingEv", CHostageImprov::IsTalking),					// DEFAULT
	HOOK_SYMBOLDEF(0x01D54150, "_ZN14CHostageImprov22UpdateGrenadeReactionsEv", CHostageImprov::UpdateGrenadeReactions),
	HOOK_SYMBOLDEF(0x01D55D20, "_ZN14CHostageImprov6AfraidEv", CHostageImprov::Afraid),
	HOOK_SYMBOLDEF(0x01D56290, "_ZN14CHostageImprov4WaveEv", CHostageImprov::Wave),
	HOOK_SYMBOLDEF(0x01D56210, "_ZN14CHostageImprov5AgreeEv", CHostageImprov::Agree),
	HOOK_SYMBOLDEF(0x01D56240, "_ZN14CHostageImprov8DisagreeEv", CHostageImprov::Disagree),
	//HOOK_SYMBOLDEF(0x01D561E0, "_ZN14CHostageImprov9CrouchDieEv", CHostageImprov::CrouchDie),	// NOXREF
	HOOK_SYMBOLDEF(0x01D56120, "_ZN14CHostageImprov6FlinchE8Activity", CHostageImprov::Flinch),
	HOOK_SYMBOLDEF(0x01D55E20, "_ZN14CHostageImprov18UpdateIdleActivityE8ActivityS0_", CHostageImprov::UpdateIdleActivity),
	//HOOK_SYMBOLDEF(0x01D56910, "_ZN14CHostageImprov25UpdateStationaryAnimationEv", CHostageImprov::UpdateStationaryAnimation),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK14CHostageImprov9GetEntityEv", CHostageImprov::GetEntity),
	//HOOK_SYMBOLDEF(0x01D540C0, "_ZN14CHostageImprov24CheckForNearbyTerroristsEv", CHostageImprov::CheckForNearbyTerrorists),	// NOXREF
	HOOK_SYMBOLDEF(0x01D534F0, "_ZN14CHostageImprov14UpdatePositionEf", CHostageImprov::UpdatePosition),
	HOOK_SYMBOLDEF(0x01D512C0, "_ZN14CHostageImprov11MoveTowardsERK6Vectorf", CHostageImprov::MoveTowards),
	HOOK_SYMBOLDEF(0x01D517A0, "_ZN14CHostageImprov11FaceTowardsERK6Vectorf", CHostageImprov::FaceTowards),
	//HOOK_SYMBOLDEF(0x01D52250, "_ZN14CHostageImprov8GetSpeedEv", CHostageImprov::GetSpeed),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN14CHostageImprov12SetMoveAngleEf", CHostageImprov::SetMoveAngle),
	HOOK_SYMBOLDEF(0x01D56300, "_ZN14CHostageImprov6WiggleEv", CHostageImprov::Wiggle),
	HOOK_SYMBOLDEF(0x01D564E0, "_ZN14CHostageImprov9ClearPathEv", CHostageImprov::ClearPath),
	//@HOOK_SYMBOLDEF(0x01D4A890, "_Z16NavAreaBuildPathI15HostagePathCostEbP8CNavAreaS2_PK6VectorRT_PS2_", NavAreaBuildPath__HostagePathCost__wrapper),
	//@HOOK_SYMBOLDEF(0x01D15AD0, "_Z16NavAreaBuildPathI16ShortestPathCostEbP8CNavAreaS2_PK6VectorRT_PS2_", NavAreaBuildPath__ShortestPathCost__wrapper),
	HOOK_SYMBOLDEF(0x01D4A890, "_Z16NavAreaBuildPathI15HostagePathCostEbP8CNavAreaS2_PK6VectorRT_PS2_", NavAreaBuildPath<HostagePathCost>),
	HOOK_SYMBOLDEF(0x01D15AD0, "_Z16NavAreaBuildPathI16ShortestPathCostEbP8CNavAreaS2_PK6VectorRT_PS2_", NavAreaBuildPath<ShortestPathCost>),
	//HOOK_SYMBOLDEF(0x01D511C0, "_ZN14CHostageImprov17DiscontinuityJumpEfbb", CHostageImprov::DiscontinuityJump),	// NOXREF
	HOOK_SYMBOLDEF(0x01D52C00, "_ZN14CHostageImprov12UpdateVisionEv", CHostageImprov::UpdateVision),
//HostageState
	// virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN12HostageStateD0Ev", HostageState::~HostageState),
	//HOOK_SYMBOLDEF(0x0, "_ZN12HostageStateD2Ev", HostageState::~HostageState),
	//HOOK_SYMBOLDEF(0x01D569C0, "_ZN12HostageState25UpdateStationaryAnimationEP14CHostageImprov", HostageState::UpdateStationaryAnimation),
//HostageIdleState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4B3A0, "_ZN16HostageIdleState7OnEnterEP14CHostageImprov", HostageIdleState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4B3C0, "_ZN16HostageIdleState8OnUpdateEP14CHostageImprov", HostageIdleState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4BBB0, "_ZN16HostageIdleState6OnExitEP14CHostageImprov", HostageIdleState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56A30, "_ZNK16HostageIdleState7GetNameEv", HostageIdleState::GetName),			// DEFAULT
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4BBD0, "_ZN16HostageIdleState25UpdateStationaryAnimationEP14CHostageImprov", HostageIdleState::UpdateStationaryAnimation),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56A40, "_ZN16HostageIdleState15OnMoveToSuccessERK6Vector", HostageIdleState::OnMoveToSuccess),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56A50, "_ZN16HostageIdleState15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", HostageIdleState::OnMoveToFailure),	// DEFAULT
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56A60, "_ZN16HostageIdleState8OnInjuryEf", HostageIdleState::OnInjury),	// DEFAULT
//HostageStateMachine
	// virtual func
	//HOOK_SYMBOLDEF(0x01D569D0, "_ZN19HostageStateMachine15OnMoveToSuccessERK6Vector", HostageStateMachine::OnMoveToSuccess),
	//HOOK_SYMBOLDEF(0x01D569F0, "_ZN19HostageStateMachine15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", HostageStateMachine::OnMoveToFailure),
	//HOOK_SYMBOLDEF(0x01D56A10, "_ZN19HostageStateMachine8OnInjuryEf", HostageStateMachine::OnInjury),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN19HostageStateMachine25UpdateStationaryAnimationEP14CHostageImprov", HostageStateMachine::UpdateStationaryAnimation),
//HostageEscapeToCoverState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A200, "_ZN25HostageEscapeToCoverState7OnEnterEP14CHostageImprov", HostageEscapeToCoverState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A4A0, "_ZN25HostageEscapeToCoverState8OnUpdateEP14CHostageImprov", HostageEscapeToCoverState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A590, "_ZN25HostageEscapeToCoverState6OnExitEP14CHostageImprov", HostageEscapeToCoverState::OnExit),		// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56B00, "_ZNK25HostageEscapeToCoverState7GetNameEv", HostageEscapeToCoverState::GetName),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A5A0, "_ZN25HostageEscapeToCoverState15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", HostageEscapeToCoverState::OnMoveToFailure),		// DEFAULT
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN25HostageEscapeToCoverState13SetRescueGoalERK6Vector", HostageEscapeToCoverState::SetRescueGoal),
//HostageEscapeLookAroundState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A5E0, "_ZN28HostageEscapeLookAroundState7OnEnterEP14CHostageImprov", HostageEscapeLookAroundState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A620, "_ZN28HostageEscapeLookAroundState8OnUpdateEP14CHostageImprov", HostageEscapeLookAroundState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A680, "_ZN28HostageEscapeLookAroundState6OnExitEP14CHostageImprov", HostageEscapeLookAroundState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56B40, "_ZNK28HostageEscapeLookAroundState7GetNameEv", HostageEscapeLookAroundState::GetName),
//HostageEscapeState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A690, "_ZN18HostageEscapeState7OnEnterEP14CHostageImprov", HostageEscapeState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A720, "_ZN18HostageEscapeState8OnUpdateEP14CHostageImprov", HostageEscapeState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A880, "_ZN18HostageEscapeState6OnExitEP14CHostageImprov", HostageEscapeState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56A80, "_ZNK18HostageEscapeState7GetNameEv", HostageEscapeState::GetName),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56A70, "_ZN18HostageEscapeState15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", HostageEscapeState::OnMoveToFailure),	// NOXREF
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN18HostageEscapeState7ToCoverEv", HostageEscapeState::ToCover),
	//HOOK_SYMBOLDEF(0x0, "_ZN18HostageEscapeState10LookAroundEv", HostageEscapeState::LookAround),
//HostageRetreatState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4BC30, "_ZN19HostageRetreatState7OnEnterEP14CHostageImprov", HostageRetreatState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4BC50, "_ZN19HostageRetreatState8OnUpdateEP14CHostageImprov", HostageRetreatState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D4BDB0, "_ZN19HostageRetreatState6OnExitEP14CHostageImprov", HostageRetreatState::OnExit),		// PURE
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56BD0, "_ZNK19HostageRetreatState7GetNameEv", HostageRetreatState::GetName),			// DEFAULT
//HostageFollowState
	// virtual func
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4AC70, "_ZN18HostageFollowState7OnEnterEP14CHostageImprov", HostageFollowState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4ACF0, "_ZN18HostageFollowState8OnUpdateEP14CHostageImprov", HostageFollowState::OnUpdate),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4B320, "_ZN18HostageFollowState6OnExitEP14CHostageImprov", HostageFollowState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56BE0, "_ZNK18HostageFollowState7GetNameEv", HostageFollowState::GetName),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4B330, "_ZN18HostageFollowState25UpdateStationaryAnimationEP14CHostageImprov", HostageFollowState::UpdateStationaryAnimation),
	// non-virtual func
	//HOOK_SYMBOLDEF(0x0, "_ZN18HostageFollowState9SetLeaderEP11CBaseEntity", HostageFollowState::SetLeader),
	//HOOK_SYMBOLDEF(0x0, "_ZNK18HostageFollowState9GetLeaderEv", HostageFollowState::GetLeader),
//HostageAnimateState
	// virtual func
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A060, "_ZN19HostageAnimateState7OnEnterEP14CHostageImprov", HostageAnimateState::OnEnter),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A070, "_ZN19HostageAnimateState8OnUpdateEP14CHostageImprov", HostageAnimateState::OnUpdate),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D4A1B0, "_ZN19HostageAnimateState6OnExitEP14CHostageImprov", HostageAnimateState::OnExit),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D56BF0, "_ZNK19HostageAnimateState7GetNameEv", HostageAnimateState::GetName),
	// non-virtual func
	HOOK_SYMBOLDEF(0x01D49D60, "_ZN19HostageAnimateState5ResetEv", HostageAnimateState::Reset),
	HOOK_SYMBOLDEF(0x01D49E10, "_ZN19HostageAnimateState11AddSequenceEP14CHostageImprovPKcff", HostageAnimateState::AddSequence, void (CHostageImprov *, const char *, float, float)),
	HOOK_SYMBOLDEF(0x01D49F00, "_ZN19HostageAnimateState11AddSequenceEP14CHostageImproviff", HostageAnimateState::AddSequence, void (CHostageImprov *, int, float, float)),
	//HOOK_SYMBOLDEF(0x0, "_ZNK19HostageAnimateState6IsBusyEv", HostageAnimateState::IsBusy),
	//HOOK_SYMBOLDEF(0x01D4A1C0, "_ZNK19HostageAnimateState9IsPlayingEP14CHostageImprovPKc", HostageAnimateState::IsPlaying),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN19HostageAnimateState20GetCurrentSequenceIDEv", HostageAnimateState::GetCurrentSequenceID),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK19HostageAnimateState14GetPerformanceEv", HostageAnimateState::GetPerformance),
	//HOOK_SYMBOLDEF(0x0, "_ZN19HostageAnimateState14SetPerformanceENS_15PerformanceTypeE", HostageAnimateState::SetPerformance),
	//HOOK_SYMBOLDEF(0x01D49D70, "_ZN19HostageAnimateState13StartSequenceEP14CHostageImprovPKNS_7SeqInfoE", HostageAnimateState::StartSequence),	// NOXREF
	HOOK_SYMBOLDEF(0x01D4A000, "_ZN19HostageAnimateState13IsDoneHoldingEv", HostageAnimateState::IsDoneHolding),
//CHostage
	// virtual func
	// HOOK_SYMBOL_VIRTUAL_DEF(0x01D4BE60, "_ZN8CHostage5SpawnEv", CHostage::Spawn),			// do not use the hook together CHostage::IdleThink
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4C2C0, "_ZN8CHostage8PrecacheEv", CHostage::Precache),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4DB00, "_ZN8CHostage10ObjectCapsEv", CHostage::ObjectCaps),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D50D80, "_ZN8CHostage8ClassifyEv", CHostage::Classify),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4CE30, "_ZN8CHostage10TakeDamageEP9entvars_sS1_fi", CHostage::TakeDamage),
	//HOOK_SYMBOL_VIRTUAL_DEF(0x01D50D90, "_ZN8CHostage10BloodColorEv", CHostage::BloodColor),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4DB10, "_ZN8CHostage5TouchEP11CBaseEntity", CHostage::Touch),
	HOOK_SYMBOL_VIRTUAL_DEF(0x01D4D710, "_ZN8CHostage3UseEP11CBaseEntityS1_8USE_TYPEf", CHostage::Use),
	// non-virtual func
	// HOOK_SYMBOLDEF(0x01D4C450, "_ZN8CHostage9IdleThinkEv", CHostage::IdleThink),	// export func
	HOOK_SYMBOLDEF(0x01D4CBB0, "_ZN8CHostage6RemoveEv", CHostage::Remove),
	// HOOK_SYMBOLDEF(0x01D4CC20, "_ZN8CHostage10RePositionEv", CHostage::RePosition),		// do not use the hook together CHostage::IdleThink
	HOOK_SYMBOLDEF(0x01D4C3E0, "_ZN8CHostage11SetActivityEi", CHostage::SetActivity),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CHostage11GetActivityEv", CHostage::GetActivity),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D4D290, "_ZN8CHostage17GetModifiedDamageEfi", CHostage::GetModifiedDamage),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D4D390, "_ZN8CHostage17SetFlinchActivityEv", CHostage::SetFlinchActivity),	// NOXREF
	HOOK_SYMBOLDEF(0x01D4D400, "_ZN8CHostage16SetDeathActivityEv", CHostage::SetDeathActivity),
	//HOOK_SYMBOLDEF(0x01D4D310, "_ZN8CHostage13PlayPainSoundEv", CHostage::PlayPainSound),	// NOXREF
	HOOK_SYMBOLDEF(0x01D4D990, "_ZN8CHostage21PlayFollowRescueSoundEv", CHostage::PlayFollowRescueSound),
	HOOK_SYMBOLDEF(0x01D4D580, "_ZN8CHostage13AnnounceDeathEP11CBasePlayer", CHostage::AnnounceDeath),
	//HOOK_SYMBOLDEF(0x01D4D6A0, "_ZN8CHostage19ApplyHostagePenaltyEP11CBasePlayer", CHostage::ApplyHostagePenalty),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D4DA80, "_ZN8CHostage16GiveCTTouchBonusEP11CBasePlayer", CHostage::GiveCTTouchBonus),		// NOXREF
	HOOK_SYMBOLDEF(0x01D4E580, "_ZN8CHostage22SendHostagePositionMsgEv", CHostage::SendHostagePositionMsg),
	HOOK_SYMBOLDEF(0x01D4E6F0, "_ZN8CHostage19SendHostageEventMsgEv", CHostage::SendHostageEventMsg),
	// HOOK_SYMBOLDEF(0x01D4DC10, "_ZN8CHostage8DoFollowEv", CHostage::DoFollow),
	//HOOK_SYMBOLDEF(0x01D4E380, "_ZN8CHostage10IsOnLadderEv", CHostage::IsOnLadder),		// NOXREF
	HOOK_SYMBOLDEF(0x01D4E010, "_ZN8CHostage7PointAtERK6Vector", CHostage::PointAt),	// NOXREF
	// HOOK_SYMBOLDEF(0x01D4E080, "_ZN8CHostage10MoveTowardERK6Vector", CHostage::MoveToward),
	HOOK_SYMBOLDEF(0x01D4E3A0, "_ZN8CHostage8NavReadyEv", CHostage::NavReady),
	HOOK_SYMBOLDEF(0x01D4E850, "_ZN8CHostage6WiggleEv", CHostage::Wiggle),
	HOOK_SYMBOLDEF(0x01D4EAB0, "_ZN8CHostage8PreThinkEv", CHostage::PreThink),
	//HOOK_SYMBOLDEF(0x0, "_ZN8CHostage18IsFollowingSomeoneEv", CHostage::IsFollowingSomeone),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN8CHostage9GetLeaderEv", CHostage::GetLeader),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN8CHostage11IsFollowingEPK11CBaseEntity", CHostage::IsFollowing),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN8CHostage7IsValidEv", CHostage::IsValid),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN8CHostage6IsDeadEv", CHostage::IsDead),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CHostage8IsAtHomeEv", CHostage::IsAtHome),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZNK8CHostage15GetHomePositionEv", CHostage::GetHomePosition),	// NOXREF
	HOOK_DEF(0x01D4BDC0, hostage_entity),
	HOOK_DEF(0x01D4BE10, monster_scientist),
//CHostageManager
	//HOOK_SYMBOLDEF(0x01D4EEE0, "_ZN15CHostageManagerC2Ev", CHostageManager::CHostageManager),
	HOOK_SYMBOLDEF(0x01D4EF10, "_ZN15CHostageManager14ServerActivateEv", CHostageManager::ServerActivate),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CHostageManager16ServerDeactivateEv", CHostageManager::ServerDeactivate),
	HOOK_SYMBOLDEF(0x01D50670, "_ZN15CHostageManager12RestartRoundEv", CHostageManager::RestartRound),
	//HOOK_SYMBOLDEF(0x01D506A0, "_ZN15CHostageManager10AddHostageEP8CHostage", CHostageManager::AddHostage),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN15CHostageManager10GetChatterEv", CHostageManager::GetChatter),
	HOOK_SYMBOLDEF(0x01D506D0, "_ZNK15CHostageManager22IsNearbyHostageTalkingEP14CHostageImprov", CHostageManager::IsNearbyHostageTalking),
	//HOOK_SYMBOLDEF(0x01D50790, "_ZNK15CHostageManager22IsNearbyHostageJumpingEP14CHostageImprov", CHostageManager::IsNearbyHostageJumping),
	HOOK_SYMBOLDEF(0x01D50850, "_ZN15CHostageManager7OnEventE13GameEventTypeP11CBaseEntityS2_", CHostageManager::OnEvent),
	//HOOK_SYMBOLDEF(0x0, "_ZN15CHostageManager17GetClosestHostageERK6VectorPf", CHostageManager::GetClosestHostage),
	//HOOK_SYMBOLDEF(0x01D4EE20, "_Z21Hostage_RegisterCVarsv", Hostage_RegisterCVars),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D4EE40, "_Z21InstallHostageManagerv", InstallHostageManager),
//SimpleChatter
	//HOOK_SYMBOLDEF(0x01D508A0, "_ZN13SimpleChatterC2Ev", SimpleChatter::SimpleChatter),
	//HOOK_SYMBOLDEF(0x01D508D0, "_ZN13SimpleChatterD2Ev", SimpleChatter::~SimpleChatter),
	HOOK_SYMBOLDEF(0x01D50910, "_ZN13SimpleChatter8AddSoundE18HostageChatterTypePc", SimpleChatter::AddSound),
	HOOK_SYMBOLDEF(0x01D50B40, "_ZN13SimpleChatter9PlaySoundEP11CBaseEntity18HostageChatterType", SimpleChatter::PlaySound),
	//HOOK_SYMBOLDEF(0x01D50A60, "_ZN13SimpleChatter8GetSoundE18HostageChatterTypePf", SimpleChatter::GetSound),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D509E0, "_ZN13SimpleChatter7ShuffleEPNS_10ChatterSetE", SimpleChatter::Shuffle),	// NOXREF
//CLocalNav
	//HOOK_SYMBOLDEF(0x01D56E80, "_ZN9CLocalNavC2EP8CHostage", CLocalNav::CLocalNav),
	//HOOK_SYMBOLDEF(0x01D56ED0, "_ZN9CLocalNavD2Ev", CLocalNav::~CLocalNav),
	//HOOK_SYMBOLDEF(0x0, "_ZN9CLocalNav12SetTargetEntEP11CBaseEntity", CLocalNav::SetTargetEnt),	// NOXREF
	HOOK_SYMBOLDEF(0x01D57420, "_ZN9CLocalNav8FindPathER6VectorS1_fi", CLocalNav::FindPath),
	HOOK_SYMBOLDEF(0x01D57380, "_ZN9CLocalNav14SetupPathNodesEiP6Vectori", CLocalNav::SetupPathNodes),
	HOOK_SYMBOLDEF(0x01D573D0, "_ZN9CLocalNav26GetFurthestTraversableNodeER6VectorPS0_ii", CLocalNav::GetFurthestTraversableNode),
	HOOK_SYMBOLDEF(0x01D57AC0, "_ZN9CLocalNav15PathTraversableER6VectorS1_i", CLocalNav::PathTraversable),
	//HOOK_SYMBOLDEF(0x01D57A50, "_ZN9CLocalNav9PathClearER6VectorS1_iR11TraceResult", CLocalNav::PathClear, BOOL (Vector &, Vector &, int, TraceResult &)),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CLocalNav9PathClearER6VectorS1_i", CLocalNav::PathClear, BOOL (Vector &, Vector &, int)),	// NOXREF
	HOOK_SYMBOLDEF(0x01D58AC0, "_ZN9CLocalNav5ThinkEv", CLocalNav::Think),
	HOOK_SYMBOLDEF(0x01D58D50, "_ZN9CLocalNav10RequestNavEP8CHostage", CLocalNav::RequestNav),
	HOOK_SYMBOLDEF(0x01D58E20, "_ZN9CLocalNav5ResetEv", CLocalNav::Reset),
	//HOOK_SYMBOLDEF(0x01D58E50, "_ZN9CLocalNav15HostagePrethinkEv", CLocalNav::HostagePrethink),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D56F20, "_ZN9CLocalNav7AddNodeEiR6Vectoriih", CLocalNav::AddNode),	// NOXREF
	//HOOK_SYMBOLDEF(0x0, "_ZN9CLocalNav7GetNodeEi", CLocalNav::GetNode),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D56F80, "_ZN9CLocalNav10NodeExistsEii", CLocalNav::NodeExists),	// NOXREF
	//HOOK_SYMBOLDEF(0x01D56FC0, "_ZN9CLocalNav12AddPathNodesEii", CLocalNav::AddPathNodes),	// NOXREF
	HOOK_SYMBOLDEF(0x01D57040, "_ZN9CLocalNav11AddPathNodeEiiii", CLocalNav::AddPathNode),
	HOOK_SYMBOLDEF(0x01D57290, "_ZN9CLocalNav11GetBestNodeER6VectorS1_", CLocalNav::GetBestNode),
	HOOK_SYMBOLDEF(0x01D57EB0, "_ZN9CLocalNav16SlopeTraversableER6VectorS1_iR11TraceResult", CLocalNav::SlopeTraversable),
	HOOK_SYMBOLDEF(0x01D580A0, "_ZN9CLocalNav17LadderTraversableER6VectorS1_iR11TraceResult", CLocalNav::LadderTraversable),
	HOOK_SYMBOLDEF(0x01D581D0, "_ZN9CLocalNav15StepTraversableER6VectorS1_iR11TraceResult", CLocalNav::StepTraversable),
	HOOK_SYMBOLDEF(0x01D583C0, "_ZN9CLocalNav12StepJumpableER6VectorS1_iR11TraceResult", CLocalNav::StepJumpable),
	HOOK_SYMBOLDEF(0x01D57810, "_ZN9CLocalNav14FindDirectPathER6VectorS1_fi", CLocalNav::FindDirectPath),
	HOOK_SYMBOLDEF(0x01D585C0, "_ZN9CLocalNav9LadderHitER6VectorS1_R11TraceResult", CLocalNav::LadderHit),

#endif // Hostage_Region

	{ 0, nullptr, 0, 0, false }
};

// refs for uncompleted virtual function
VirtualTableRef g_TableRefs[] =
{
	// Weapon shared
	VTABLE_LINK(0x01DF46BC, "CKnife",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF4394, "CGLOCK18",			95),
	VTABLE_LINK(0x01DF368C, "CC4",				CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF5C6C, "CUSP",				95),
	VTABLE_LINK(0x01DF57DC, "CSmokeGrenade",	CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF4B8C, "CM4A1",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF453C, "CHEGrenade",		CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF3ED4, "CFlashbang",		95),
	VTABLE_LINK(0x01DF3B94, "CFamas",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF39D4, "CELITE",			95),
	VTABLE_LINK(0x01DF3D34, "CFiveSeven",		95),
	VTABLE_LINK(0x01DF502C, "CP228",			95),
	VTABLE_LINK(0x01DF5DF4, "CXM1014",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF407C, "CG3SG1",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF54CC, "CSG550",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF3824, "CDEAGLE",			95),
	VTABLE_LINK(0x01DF34E4, "CAWP",				CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF5334, "CSCOUT",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF5654, "CSG552",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF49FC, "CM3",				CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF333C, "CAUG",				CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF420C, "CGalil",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF3174, "CAK47",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF4864, "CM249",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF51AC, "CP90",				CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF4D0C, "CMAC10",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF5AE4, "CUMP45",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF4E9C, "CMP5N",			CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF595C, "CTMP",				CWEAPON_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFD984, "CWShield",			CBASE_VIRTUAL_COUNT),

	// CBaseEntity
	VTABLE_LINK(0x01DF8A94, "CGib",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFD824, "CBaseDelay",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF607C, "CBaseEntity",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFA894, "CGrenade",			77),
	VTABLE_LINK(0x01DF67D4, "CBaseToggle",		59),
	VTABLE_LINK(0x01DF652C, "CBasePlayer",		88),
	VTABLE_LINK(0x01DF6694, "CBaseMonster",		76),
	VTABLE_LINK(0x01DFDA84, "CSprayCan",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFDB74, "CBloodSplat",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFDC6C, "CDeadHEV",			76),
	VTABLE_LINK(0x01DFDF84, "CInfoIntermission",CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFDE94, "CRevertSaved",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFDDA4, "CStripWeapons",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF69B4, "CBot",				116),
	VTABLE_LINK(0x01DF61DC, "CCSBot",			116),
	VTABLE_LINK(0x01DF64F0, "CCSBotManager",	12),
	VTABLE_LINK(0x01DF6C9C, "CHostage",			76),
	VTABLE_LINK(0x01DF6FF4, "CImprov",			56),
	VTABLE_LINK(0x01DF6E24, "CHostageImprov",	56),

	// hostage states
	VTABLE_LINK(0x01DF6FE4, "HostageStateMachine",		4),
	VTABLE_LINK(0x01DF6FC8, "HostageIdleState",			4),
	VTABLE_LINK(0x01DF6F9C, "HostageEscapeState",		6),
	VTABLE_LINK(0x01DF6F70, "HostageRetreatState",		6),
	VTABLE_LINK(0x01DF6F44, "HostageFollowState",		4),
	VTABLE_LINK(0x01DF7180, "HostageEscapeToCoverState",4),
	VTABLE_LINK(0x01DF6F18, "HostageAnimateState",		4),

	VTABLE_LINK(0x01E00BBC, "CArmoury",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE4E4, "CSoundEnt",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE20C, "CAmbientGeneric",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE2FC, "CEnvSound",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE3F4, "CSpeaker",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E00D9C, "CCorpse",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E00CAC, "CDecal",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E00E8C, "CWorld",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE8D4, "CBaseGrenCatch",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE9C4, "CFuncWeaponCheck",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E00ACC, "CWeaponBox",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9F94, "CShower",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFA1BC, "CBreakable",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFA2AC, "CPushable",		CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DF7D1C, "CFuncWall",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF7E0C, "CFuncWallToggle",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF7EFC, "CFuncConveyor",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF7FF4, "CFuncIllusionary",	59),
	VTABLE_LINK(0x01DF80E4, "CFuncMonsterClip",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF81D4, "CFuncRotating",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF82C4, "CPendulum",		CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DFAAF4, "CGenericCycler",	76),
	VTABLE_LINK(0x01DFAC2C, "CCyclerProbe",		76),
	VTABLE_LINK(0x01DFAD64, "CCyclerSprite",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFAFD4, "CWreckage",		76),

	//VTABLE_LINK(0x0, "CFuncTank",				60),
	VTABLE_LINK(0x01DFA3BC, "CFuncTankGun",		60),
	VTABLE_LINK(0x01DFA4B4, "CFuncTankLaser",	60),
	VTABLE_LINK(0x01DFA5AC, "CFuncTankRocket",	60),
	VTABLE_LINK(0x01DFA6A4, "CFuncTankMortar",	60),
	VTABLE_LINK(0x01DFA79C, "CFuncTankControls",CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DF83BC, "CEnvGlobal",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF84AC, "CMultiSource",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF859C, "CBaseButton",			59),
	VTABLE_LINK(0x01DF868C, "CRotButton",			59),
	VTABLE_LINK(0x01DF877C, "CMomentaryRotButton",	59),
	VTABLE_LINK(0x01DF886C, "CEnvSpark",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF895C, "CButtonTarget",		CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DFE5D4, "CNullEntity",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFE6C4, "CBaseDMStart",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF8EAC, "CPointEntity",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFEAB4, "CFrictionModifier",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFEBA4, "CAutoTrigger",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFEC94, "CTriggerRelay",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFF6E4, "CTriggerVolume",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFF7D4, "CFireAndDie",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E00404, "CTriggerChangeTarget",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E004F4, "CTriggerCamera",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E006D4, "CClientFog",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFEE74, "CRenderFxManager",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFF324, "CTargetCDAudio",		CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DFCD1C, "CPathCorner",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFCE0C, "CPathTrack",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E007D4, "CFuncVehicle",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01E009C4, "CFuncVehicleControls",	CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DFBD4C, "CGameScore",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFBE3C, "CGameEnd",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFBF2C, "CGameText",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC01C, "CGameTeamMaster",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC10C, "CGameTeamSet",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC1FC, "CGamePlayerZone",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC2EC, "CGamePlayerHurt",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC3DC, "CGameCounter",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC4CC, "CGameCounterSet",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC5BC, "CGamePlayerEquip",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFC6AC, "CGamePlayerTeam",	CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DFCEFC, "CFuncPlat",			64),
	VTABLE_LINK(0x01DFD0F4, "CFuncPlatRot",			64),
	VTABLE_LINK(0x01DFD1FC, "CFuncTrain",			60),
	VTABLE_LINK(0x01DFD2F4, "CFuncTrackTrain",		CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFD3EC, "CFuncTrainControls",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFD4DC, "CFuncTrackChange",		65),
	VTABLE_LINK(0x01DFD5E4, "CFuncTrackAuto",		65),
	VTABLE_LINK(0x01DFD6EC, "CGunTarget",			76),
	VTABLE_LINK(0x01DFD004, "CPlatTrigger",			CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01DFED84, "CMultiManager",		59),
	VTABLE_LINK(0x01DFEF64, "CBaseTrigger",			59),
	VTABLE_LINK(0x01DFF054, "CTriggerHurt",			59),
	VTABLE_LINK(0x01DFF144, "CTriggerMonsterJump",	59),

	VTABLE_LINK(0x01DFF234, "CTriggerCDAudio",	59),
	VTABLE_LINK(0x01DFF414, "CTriggerMultiple",	59),
	VTABLE_LINK(0x01DFF504, "CTriggerOnce",		59),
	VTABLE_LINK(0x01DFF5F4, "CTriggerCounter",	59),
	VTABLE_LINK(0x01DFF8C4, "CChangeLevel",		59),
	VTABLE_LINK(0x01DFF9B4, "CLadder",			59),
	VTABLE_LINK(0x01DFFAA4, "CTriggerPush",		59),
	VTABLE_LINK(0x01DFFB94, "CTriggerTeleport",	59),
	VTABLE_LINK(0x01DFFC84, "CBuyZone",			59),
	VTABLE_LINK(0x01DFFD74, "CBombTarget",		59),
	VTABLE_LINK(0x01DFFE64, "CHostageRescue",	59),
	VTABLE_LINK(0x01DFFF54, "CEscapeZone",		59),
	VTABLE_LINK(0x01E00044, "CVIP_SafetyZone",	59),
	VTABLE_LINK(0x01E00134, "CTriggerSave",		59),

	VTABLE_LINK(0x01E00224, "CTriggerEndSection",	59),
	VTABLE_LINK(0x01E00314, "CTriggerGravity",		59),
	VTABLE_LINK(0x01E005E4, "CWeather",				59),

	VTABLE_LINK(0x01DFA084, "CEnvExplosion",	76),
	VTABLE_LINK(0x01DFC79C, "CFuncMortarField",	59),
	VTABLE_LINK(0x01DF7204, "CAirtank",			77),
	VTABLE_LINK(0x01DFC88C, "CMortar",			77),
	VTABLE_LINK(0x01DF7344, "C9MMAmmo",			59),
	VTABLE_LINK(0x01DF7434, "CBuckShotAmmo",	59),
	VTABLE_LINK(0x01DF7524, "C556NatoAmmo",		59),
	VTABLE_LINK(0x01DF7614, "C556NatoBoxAmmo",	59),
	VTABLE_LINK(0x01DF7704, "C762NatoAmmo",		59),
	VTABLE_LINK(0x01DF77F4, "C45ACPAmmo",		59),
	VTABLE_LINK(0x01DF78E4, "C50AEAmmo",		59),
	VTABLE_LINK(0x01DF79D4, "C338MagnumAmmo",	59),
	VTABLE_LINK(0x01DF7AC4, "C57MMAmmo",		59),
	VTABLE_LINK(0x01DF7BB4, "C357SIGAmmo",		59),

	// doors
	VTABLE_LINK(0x01DF8BDC, "CBaseDoor",		59),
	VTABLE_LINK(0x01DF8CCC, "CRotDoor",			59),
	VTABLE_LINK(0x01DF8DBC, "CMomentaryDoor",	59),

	// rules
	VTABLE_LINK(0x01DFCBFC, "CGameRules",			63),
	VTABLE_LINK(0x01DFE10C, "CHalfLifeRules",		63),
	VTABLE_LINK(0x01DFCADC, "CHalfLifeMultiplay",	70),
	VTABLE_LINK(0x01DFE7B4, "CHalfLifeTraining",	70),
	VTABLE_LINK(0x01DFC9D4, "CMapInfo",				CBASE_VIRTUAL_COUNT),

	VTABLE_LINK(0x01E01074, "CPreventDefuseTask",	0),
	VTABLE_LINK(0x01E01084, "CCareerTask",			0),

	// effects
	VTABLE_LINK(0x01DF8F9C, "CBubbling",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF908C, "CBeam",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF917C, "CLightning",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF926C, "CLaser",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF944C, "CGlow",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF953C, "CBombGlow",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF935C, "CSprite",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFB2EC, "CWorldItem",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFBB5C, "CLight",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFBC4C, "CEnvLight",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFEAB4, "CFrictionModifier",	CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFEBA4, "CAutoTrigger",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DFBA6C, "CItemThighPack",		59),
	VTABLE_LINK(0x01DFB97C, "CItemAssaultSuit",		59),
	VTABLE_LINK(0x01DFB88C, "CItemKevlar",			59),
	VTABLE_LINK(0x01DFB79C, "CItemLongJump",		59),
	VTABLE_LINK(0x01DFB6AC, "CItemSecurity",		59),
	VTABLE_LINK(0x01DFB5BC, "CItemAntidote",		59),
	VTABLE_LINK(0x01DFB4CC, "CItemBattery",			59),
	VTABLE_LINK(0x01DFB3DC, "CItemSuit",			59),
	VTABLE_LINK(0x01DFB10C, "CHealthKit",			59),
	VTABLE_LINK(0x01DFB1FC, "CWallHealth",			59),
	VTABLE_LINK(0x01DFA9FC, "CRecharge",			59),
	VTABLE_LINK(0x01DF9634, "CGibShooter",			59),
	VTABLE_LINK(0x01DF9724, "CEnvShooter",			59),
	VTABLE_LINK(0x01DF9814, "CTestEffect",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9904, "CBlood",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF99F4, "CShake",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9AE4, "CFade",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9BD4, "CMessage",				CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9CC4, "CEnvFunnel",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9DB4, "CEnvBeverage",			CBASE_VIRTUAL_COUNT),
	VTABLE_LINK(0x01DF9EA4, "CItemSoda",			CBASE_VIRTUAL_COUNT),

	// tutor
	VTABLE_LINK(0x01E00FA4, "CBaseTutor",					12),
	VTABLE_LINK(0x01E00F9C, "TutorMessageEvent",			1),
	VTABLE_LINK(0x01E01024, "CCSTutor",						12),
	VTABLE_LINK(0x01E00FEC, "CCSTutorStateSystem",			4),
	VTABLE_LINK(0x01E00F78, "CBaseTutorStateSystem",		4),
	VTABLE_LINK(0x01E00F8C, "CBaseTutorState",				3),
	VTABLE_LINK(0x01E00FDC, "CCSTutorUndefinedState",		3),
	VTABLE_LINK(0x01E01000, "CCSTutorBuyMenuState",			3),
	VTABLE_LINK(0x01E01010, "CCSTutorWaitingForStartState",	3),

	VTABLE_LINK(0x01DF6198, "BotFollowMeme",				1),
	VTABLE_LINK(0x01DF617C, "BotHelpMeme",					1),
	VTABLE_LINK(0x01DF61A0, "BotDefendHereMeme",			1),
	VTABLE_LINK(0x01DF61B0, "BotBombsiteStatusMeme",		1),
	VTABLE_LINK(0x01DF618C, "BotBombStatusMeme",			1),
	VTABLE_LINK(0x01DF61B8, "BotHostageBeingTakenMeme",		1),
	VTABLE_LINK(0x01DF61A8, "BotWhereBombMeme",				1),
	VTABLE_LINK(0x01DF6184, "BotRequestReportMeme",			1),

	// bot states
	VTABLE_LINK(0x01DF64A0, "IdleState",				4),
	VTABLE_LINK(0x01DF648C, "HuntState",				4),
	VTABLE_LINK(0x01DF6478, "AttackState",				4),
	VTABLE_LINK(0x01DF6464, "InvestigateNoiseState",	4),
	VTABLE_LINK(0x01DF6450, "BuyState",					4),
	VTABLE_LINK(0x01DF643C, "MoveToState",				4),
	VTABLE_LINK(0x01DF6428, "FetchBombState",			4),
	VTABLE_LINK(0x01DF6414, "PlantBombState",			4),
	VTABLE_LINK(0x01DF6400, "DefuseBombState",			4),
	VTABLE_LINK(0x01DF63EC, "HideState",				4),
	VTABLE_LINK(0x01DF63D8, "EscapeFromBombState",		4),
	VTABLE_LINK(0x01DF63C4, "FollowState",				4),
	VTABLE_LINK(0x01DF63B0, "UseEntityState",			4),

	{ 0, nullptr, 0 }	// BaseClass__for_vtbl
};

// references
AddressRef g_FunctionRefs[] =
{
#ifndef Function_References_Region

	GLOBALVAR_LINK(0x01D2EDD0, "_ZN6CCSBot16UpdateLookAnglesEv", pCCSBot__UpdateLookAngles),
	GLOBALVAR_LINK(0x01D19C70, "_ZN9BotPhrase9RandomizeEv", pBotPhrase__Randomize),

#endif // Function_References_Region

	{ 0, nullptr, 0, 0, false }
};

AddressRef g_DataRefs[] =
{
#ifndef Data_References_Region

	GLOBALVAR_LINK(0x01E61BD0, "g_engfuncs", pg_engfuncs),
	GLOBALVAR_LINK(0x01E61E48, "gpGlobals", pgpGlobals),
	GLOBALVAR_LINK(0x01E10768, "GameEventName", pGameEventName),
	GLOBALVAR_LINK(0x01E2A3F8, "_ZL14s_shared_token", ps_shared_token),
	GLOBALVAR_LINK(0x01E13218, "_ZL14s_shared_quote", ps_shared_quote),
	GLOBALVAR_LINK(0x01E61BA4, "g_vecZero", pg_vecZero),
	GLOBALVAR_LINK(0x01E61BB4, "g_Language", pg_Language),
	//GLOBALVAR_LINK(0x01E61BB8, "g_ulFrameCount", pg_ulFrameCount),	// NOXREF
	//GLOBALVAR_LINK(0x0, "g_ulModelIndexEyes", pg_ulModelIndexEyes),	// NOXREF
	GLOBALVAR_LINK(0x01E61BC0, "g_vecAttackDir", pg_vecAttackDir),
	GLOBALVAR_LINK(0x01E61BBC, "g_iSkillLevel", pg_iSkillLevel),
	GLOBALVAR_LINK(0x01E61B9C, "gDisplayTitle", pgDisplayTitle),
	GLOBALVAR_LINK(0x01E61BA0, "g_fGameOver", pg_fGameOver),
	GLOBALVAR_LINK(0x01E754B8, "st_szNextMap", pst_szNextMap),
	GLOBALVAR_LINK(0x01E75498, "st_szNextSpot", pst_szNextSpot),
	GLOBALVAR_LINK(0x01E683A0, "gSkillData", pgSkillData),
	GLOBALVAR_LINK(0x01E75EC8, "g_sModelIndexLaser", pg_sModelIndexLaser),
	GLOBALVAR_LINK(0x01E227A8, "g_pModelNameLaser", pg_pModelNameLaser),
	GLOBALVAR_LINK(0x01E75FD8, "g_sModelIndexLaserDot", pg_sModelIndexLaserDot),
	GLOBALVAR_LINK(0x01E75EC6, "g_sModelIndexFireball", pg_sModelIndexFireball),
	GLOBALVAR_LINK(0x01E75EB4, "g_sModelIndexSmoke", pg_sModelIndexSmoke),
	GLOBALVAR_LINK(0x01E75EB2, "g_sModelIndexWExplosion", pg_sModelIndexWExplosion),
	GLOBALVAR_LINK(0x01E76562, "g_sModelIndexBubbles", pg_sModelIndexBubbles),
	GLOBALVAR_LINK(0x01E75EB6, "g_sModelIndexBloodDrop", pg_sModelIndexBloodDrop),
	GLOBALVAR_LINK(0x01E75ECA, "g_sModelIndexBloodSpray", pg_sModelIndexBloodSpray),
	GLOBALVAR_LINK(0x01E76566, "g_sModelIndexSmokePuff", pg_sModelIndexSmokePuff),
	GLOBALVAR_LINK(0x01E75ED0, "g_sModelIndexFireball2", pg_sModelIndexFireball2),
	GLOBALVAR_LINK(0x01E75ECC, "g_sModelIndexFireball3", pg_sModelIndexFireball3),
	GLOBALVAR_LINK(0x01E75ECE, "g_sModelIndexFireball4", pg_sModelIndexFireball4),
	GLOBALVAR_LINK(0x01E76564, "g_sModelIndexCTGhost", pg_sModelIndexCTGhost),
	GLOBALVAR_LINK(0x01E75EB0, "g_sModelIndexTGhost", pg_sModelIndexTGhost),
	GLOBALVAR_LINK(0x01E76560, "g_sModelIndexC4Glow", pg_sModelIndexC4Glow),
	GLOBALVAR_LINK(0x01E76568, "giAmmoIndex", pgiAmmoIndex),
	GLOBALVAR_LINK(0x01E75EC4, "g_sModelIndexRadio", pg_sModelIndexRadio),
	GLOBALVAR_LINK(0x01E75EB8, "gMultiDamage", pgMultiDamage),
	GLOBALVAR_LINK(0x01E29880, "_ZL13s_iBeamSprite", ps_iBeamSprite),
	GLOBALVAR_LINK(0x01E29480, "_ZL8cosTable", pcosTable),
	GLOBALVAR_LINK(0x01E23AA8, "TutorIdentifierList", pTutorIdentifierList),
	GLOBALVAR_LINK(0x01E23678, "_ZL19g_TutorStateStrings", pg_TutorStateStrings),
	//GLOBALVAR_LINK(0x01E61E4C, "WorldGraph", pWorldGraph),
	//GLOBALVAR_LINK(0x01E61E5C, "_ZN12CTalkMonster14g_talkWaitTimeE", CTalkMonster::pg_talkWaitTime),
	GLOBALVAR_LINK(0x01E61B98, "g_pGameRules", pg_pGameRules),
	GLOBALVAR_LINK(0x01E62560, "g_pMPGameRules", pg_pMPGameRules),
	//GLOBALVAR_LINK(0x01E61E70, "_ZL12mp_com_token", pmp_com_token),
	GLOBALVAR_LINK(0x01E636F0, "vec3_origin", pvec3_origin),
	GLOBALVAR_LINK(0x01E1F420, "nanmask", pnanmask),
	GLOBALVAR_LINK(0x01E0B0B0, "_ZL15weaponAliasInfo", pweaponAliasInfo),
	GLOBALVAR_LINK(0x01E0B1E8, "_ZL18weaponBuyAliasInfo", pweaponBuyAliasInfo),
	GLOBALVAR_LINK(0x01E0B3F0, "_ZL20weaponClassAliasInfo", pweaponClassAliasInfo),
	GLOBALVAR_LINK(0x01E0B560, "g_autoBuyInfo", pg_autoBuyInfo),
	GLOBALVAR_LINK(0x01E0B708, "_ZL10weaponInfo", pweaponInfo),
	GLOBALVAR_LINK(0x01E6AC80, "gszallsentencenames", pgszallsentencenames),
	GLOBALVAR_LINK(0x01E683E0, "rgsentenceg", prgsentenceg),
	GLOBALVAR_LINK(0x01E75480, "fSentencesInit", pfSentencesInit),
	GLOBALVAR_LINK(0x01E75484, "gcallsentences", pgcallsentences),
	GLOBALVAR_LINK(0x01E1F5B0, "rgdpvpreset", prgdpvpreset),
	GLOBALVAR_LINK(0x01E75488, "fTextureTypeInit", pfTextureTypeInit),
	GLOBALVAR_LINK(0x01E7548C, "gcTextures", pgcTextures, 2),
	GLOBALVAR_LINK(0x01E70C80, "grgszTextureName", pgrgszTextureName, 2),
	GLOBALVAR_LINK(0x01E75080, "grgchTextureType", pgrgchTextureType, 2),
	// implementation at PM_Shared
	GLOBALVAR_LINK(0x01E68390, "gcTextures", ppm_gcTextures, 1),
	GLOBALVAR_LINK(0x01E63B88, "grgszTextureName", ppm_grgszTextureName, 1),
	GLOBALVAR_LINK(0x01E67F88, "grgchTextureType", ppm_grgchTextureType, 1),
	GLOBALVAR_LINK(0x01E68388, "pm_shared_initialized", ppm_shared_initialized),
	GLOBALVAR_LINK(0x01E63700, "rgv3tStuckTable", prgv3tStuckTable),
	GLOBALVAR_LINK(0x01E63A88, "rgStuckLast", prgStuckLast),
	GLOBALVAR_LINK(0x01E68394, "g_onladder", pg_onladder),
	GLOBALVAR_LINK(0x01E6838C, "pmove", pg_ppmove),
	GLOBALVAR_LINK(0x01E76578, "g_flWeaponCheat", pg_flWeaponCheat),
	GLOBALVAR_LINK(0x01E62778, "gEvilImpulse101", pgEvilImpulse101),
	GLOBALVAR_LINK(0x01E62790, "g_szMapBriefingText", pg_szMapBriefingText),
	GLOBALVAR_LINK(0x01E1DD78, "gInitHUD", pgInitHUD),
	GLOBALVAR_LINK(0x01E75CFC, "g_groupmask", pg_groupmask),
	GLOBALVAR_LINK(0x01E75D00, "g_groupop", pg_groupop),
	GLOBALVAR_LINK(0x01E21EF8, "_ZL6gSizes", pgSizes),
	GLOBALVAR_LINK(0x01E75490, "pSoundEnt", ppSoundEnt),
	GLOBALVAR_LINK(0x01E75CF8, "_ZL6glSeed", pglSeed),
	GLOBALVAR_LINK(0x01E21598, "seed_table", pseed_table),
	GLOBALVAR_LINK(0x01E21998, "gEntvarsDescription", pgEntvarsDescription),
	GLOBALVAR_LINK(0x01E22DBC, "gGlobalEntitySaveData", pgGlobalEntitySaveData),
	GLOBALVAR_LINK(0x01E7656C, "g_pBodyQueueHead", pg_pBodyQueueHead),
	GLOBALVAR_LINK(0x01E76570, "gGlobalState", pgGlobalState),
	GLOBALVAR_LINK(0x01E22C50, "gDecals", pgDecals),
	GLOBALVAR_LINK(0x01E31748, "stringsHashTable", pstringsHashTable),
	GLOBALVAR_LINK(0x01E312E8, "hashItemMemPool", phashItemMemPool),
	//GLOBALVAR_LINK(0x01E3175C, "gTouchDisabled", pgTouchDisabled),
	GLOBALVAR_LINK(0x01E6359C, "giPrecacheGrunt", pgiPrecacheGrunt),
	GLOBALVAR_LINK(0x01E6360C, "gmsgWeapPickup", pgmsgWeapPickup),
	GLOBALVAR_LINK(0x01E635E0, "gmsgHudText", pgmsgHudText),
	GLOBALVAR_LINK(0x01E635E4, "gmsgHudTextArgs", pgmsgHudTextArgs),
	GLOBALVAR_LINK(0x01E635A0, "gmsgShake", pgmsgShake),
	GLOBALVAR_LINK(0x01E635A4, "gmsgFade", pgmsgFade),
	GLOBALVAR_LINK(0x01E635A8, "gmsgFlashlight", pgmsgFlashlight),
	GLOBALVAR_LINK(0x01E635AC, "gmsgFlashBattery", pgmsgFlashBattery),
	GLOBALVAR_LINK(0x01E635B0, "gmsgResetHUD", pgmsgResetHUD),
	GLOBALVAR_LINK(0x01E635B4, "gmsgInitHUD", pgmsgInitHUD),
	GLOBALVAR_LINK(0x01E635B8, "gmsgViewMode", pgmsgViewMode),
	GLOBALVAR_LINK(0x01E635BC, "gmsgShowGameTitle", pgmsgShowGameTitle),
	GLOBALVAR_LINK(0x01E635C0, "gmsgCurWeapon", pgmsgCurWeapon),
	GLOBALVAR_LINK(0x01E635C4, "gmsgHealth", pgmsgHealth),
	GLOBALVAR_LINK(0x01E635C8, "gmsgDamage", pgmsgDamage),
	GLOBALVAR_LINK(0x01E635CC, "gmsgBattery", pgmsgBattery),
	GLOBALVAR_LINK(0x01E635D0, "gmsgTrain", pgmsgTrain),
	GLOBALVAR_LINK(0x01E635D4, "gmsgLogo", pgmsgLogo),
	GLOBALVAR_LINK(0x01E635D8, "gmsgWeaponList", pgmsgWeaponList),
	GLOBALVAR_LINK(0x01E635DC, "gmsgAmmoX", pgmsgAmmoX),
	GLOBALVAR_LINK(0x01E635E8, "gmsgDeathMsg", pgmsgDeathMsg),
	GLOBALVAR_LINK(0x01E635EC, "gmsgScoreAttrib", pgmsgScoreAttrib),
	GLOBALVAR_LINK(0x01E635F0, "gmsgScoreInfo", pgmsgScoreInfo),
	GLOBALVAR_LINK(0x01E635F4, "gmsgTeamInfo", pgmsgTeamInfo),
	GLOBALVAR_LINK(0x01E635F8, "gmsgTeamScore", pgmsgTeamScore),
	GLOBALVAR_LINK(0x01E635FC, "gmsgGameMode", pgmsgGameMode),
	GLOBALVAR_LINK(0x01E63600, "gmsgMOTD", pgmsgMOTD),
	GLOBALVAR_LINK(0x01E63604, "gmsgServerName", pgmsgServerName),
	GLOBALVAR_LINK(0x01E63608, "gmsgAmmoPickup", pgmsgAmmoPickup),
	GLOBALVAR_LINK(0x01E63610, "gmsgItemPickup", pgmsgItemPickup),
	GLOBALVAR_LINK(0x01E63614, "gmsgHideWeapon", pgmsgHideWeapon),
	GLOBALVAR_LINK(0x01E63618, "gmsgSayText", pgmsgSayText),
	GLOBALVAR_LINK(0x01E6361C, "gmsgTextMsg", pgmsgTextMsg),
	GLOBALVAR_LINK(0x01E63620, "gmsgSetFOV", pgmsgSetFOV),
	GLOBALVAR_LINK(0x01E63624, "gmsgShowMenu", pgmsgShowMenu),
	GLOBALVAR_LINK(0x01E63628, "gmsgSendAudio", pgmsgSendAudio),
	GLOBALVAR_LINK(0x01E6362C, "gmsgRoundTime", pgmsgRoundTime),
	GLOBALVAR_LINK(0x01E63630, "gmsgMoney", pgmsgMoney),
	GLOBALVAR_LINK(0x01E63634, "gmsgBlinkAcct", pgmsgBlinkAcct),
	GLOBALVAR_LINK(0x01E63638, "gmsgArmorType", pgmsgArmorType),
	GLOBALVAR_LINK(0x01E6363C, "gmsgStatusValue", pgmsgStatusValue),
	GLOBALVAR_LINK(0x01E63640, "gmsgStatusText", pgmsgStatusText),
	GLOBALVAR_LINK(0x01E63644, "gmsgStatusIcon", pgmsgStatusIcon),
	GLOBALVAR_LINK(0x01E63648, "gmsgBarTime", pgmsgBarTime),
	GLOBALVAR_LINK(0x01E6364C, "gmsgReloadSound", pgmsgReloadSound),
	GLOBALVAR_LINK(0x01E63650, "gmsgCrosshair", pgmsgCrosshair),
	GLOBALVAR_LINK(0x01E63654, "gmsgNVGToggle", pgmsgNVGToggle),
	GLOBALVAR_LINK(0x01E63658, "gmsgRadar", pgmsgRadar),
	GLOBALVAR_LINK(0x01E6365C, "gmsgSpectator", pgmsgSpectator),
	GLOBALVAR_LINK(0x01E63660, "gmsgVGUIMenu", pgmsgVGUIMenu),
	GLOBALVAR_LINK(0x01E63664, "gmsgCZCareer", pgmsgCZCareer),
	GLOBALVAR_LINK(0x01E63668, "gmsgCZCareerHUD", pgmsgCZCareerHUD),
	GLOBALVAR_LINK(0x01E6366C, "gmsgTaskTime", pgmsgTaskTime),
	GLOBALVAR_LINK(0x01E63670, "gmsgTutorText", pgmsgTutorText),
	GLOBALVAR_LINK(0x01E63674, "gmsgTutorLine", pgmsgTutorLine),
	GLOBALVAR_LINK(0x01E63678, "gmsgShadowIdx", pgmsgShadowIdx),
	GLOBALVAR_LINK(0x01E6367C, "gmsgTutorState", pgmsgTutorState),
	GLOBALVAR_LINK(0x01E63680, "gmsgTutorClose", pgmsgTutorClose),
	GLOBALVAR_LINK(0x01E63684, "gmsgAllowSpec", pgmsgAllowSpec),
	GLOBALVAR_LINK(0x01E63688, "gmsgBombDrop", pgmsgBombDrop),
	GLOBALVAR_LINK(0x01E6368C, "gmsgBombPickup", pgmsgBombPickup),
	GLOBALVAR_LINK(0x01E63690, "gmsgHostagePos", pgmsgHostagePos),
	GLOBALVAR_LINK(0x01E63694, "gmsgHostageK", pgmsgHostageK),
	GLOBALVAR_LINK(0x01E63698, "gmsgGeigerRange", pgmsgGeigerRange),
	GLOBALVAR_LINK(0x01E6369C, "gmsgSendCorpse", pgmsgSendCorpse),
	GLOBALVAR_LINK(0x01E636A0, "gmsgHLTV", pgmsgHLTV),
	GLOBALVAR_LINK(0x01E636A4, "gmsgSpecHealth", pgmsgSpecHealth),
	GLOBALVAR_LINK(0x01E636A8, "gmsgForceCam", pgmsgForceCam),
	GLOBALVAR_LINK(0x01E636AC, "gmsgADStop", pgmsgADStop),
	GLOBALVAR_LINK(0x01E636B0, "gmsgReceiveW", pgmsgReceiveW),
	GLOBALVAR_LINK(0x01E636B4, "gmsgScenarioIcon", pgmsgScenarioIcon),
	GLOBALVAR_LINK(0x01E636B8, "gmsgBotVoice", pgmsgBotVoice),
	GLOBALVAR_LINK(0x01E636BC, "gmsgBuyClose", pgmsgBuyClose),
	GLOBALVAR_LINK(0x01E636C0, "gmsgItemStatus", pgmsgItemStatus),
	GLOBALVAR_LINK(0x01E636C4, "gmsgLocation", pgmsgLocation),
	GLOBALVAR_LINK(0x01E636C8, "gmsgSpecHealth2", pgmsgSpecHealth2),
	GLOBALVAR_LINK(0x01E636CC, "gmsgBarTime2", pgmsgBarTime2),
	GLOBALVAR_LINK(0x01E636D0, "gmsgBotProgress", pgmsgBotProgress),
	GLOBALVAR_LINK(0x01E636D4, "gmsgBrass", pgmsgBrass),
	GLOBALVAR_LINK(0x01E636D8, "gmsgFog", pgmsgFog),
	GLOBALVAR_LINK(0x01E636DC, "gmsgShowTimer", pgmsgShowTimer),
	GLOBALVAR_LINK(0x01E61B80, "g_psv_gravity", pg_psv_gravity),
	GLOBALVAR_LINK(0x01E61B84, "g_psv_aim", pg_psv_aim),//TODO: unused, used cvar_t *sv_aim
	GLOBALVAR_LINK(0x01E63598, "sv_aim", psv_aim),
	GLOBALVAR_LINK(0x01E61E6C, "sv_clienttrace", psv_clienttrace),
	GLOBALVAR_LINK(0x01E61E68, "_ZL15g_GameMgrHelper", pg_GameMgrHelper),
	GLOBALVAR_LINK(0x01E22624, "voice_serverdebug", pvoice_serverdebug),
	GLOBALVAR_LINK(0x01E22638, "sv_alltalk", psv_alltalk),
	GLOBALVAR_LINK(0x01E75D20, "g_PlayerModEnable", pg_PlayerModEnable),
	GLOBALVAR_LINK(0x01E75D28, "g_BanMasks", pg_BanMasks),
	GLOBALVAR_LINK(0x01E75DA8, "g_SentGameRulesMasks", pg_SentGameRulesMasks),
	GLOBALVAR_LINK(0x01E75E30, "g_SentBanMasks", pg_SentBanMasks),
	GLOBALVAR_LINK(0x01E75E28, "g_bWantModEnable", pg_bWantModEnable),
	GLOBALVAR_LINK(0x01E76580, "_ZL23s_tutorDisabledThisGame", ps_tutorDisabledThisGame),
	GLOBALVAR_LINK(0x01E76584, "_ZL19s_nextCvarCheckTime", ps_nextCvarCheckTime),
	GLOBALVAR_LINK(0x01E11214, "BotDifficultyName", pBotDifficultyName),
	GLOBALVAR_LINK(0x01E61B88, "g_footsteps", pg_footsteps),
	GLOBALVAR_LINK(0x01E61B8C, "g_psv_accelerate", pg_psv_accelerate),
	GLOBALVAR_LINK(0x01E61B90, "g_psv_friction", pg_psv_friction),
	GLOBALVAR_LINK(0x01E61B94, "g_psv_stopspeed", pg_psv_stopspeed),
	GLOBALVAR_LINK(0x01E18738, "displaysoundlist", pdisplaysoundlist),
	GLOBALVAR_LINK(0x01E18774, "timelimit", ptimelimit),
	GLOBALVAR_LINK(0x01E1879C, "flashlight", pflashlight),
	GLOBALVAR_LINK(0x01E187B0, "decalfrequency", pdecalfrequency),
	GLOBALVAR_LINK(0x01E189A4, "fadetoblack", pfadetoblack),
	GLOBALVAR_LINK(0x01E1874C, "fragsleft", pfragsleft),
	GLOBALVAR_LINK(0x01E18760, "timeleft", ptimeleft),
	GLOBALVAR_LINK(0x01E18788, "friendlyfire", pfriendlyfire),
	GLOBALVAR_LINK(0x01E187C4, "allowmonsters", pallowmonsters),
	GLOBALVAR_LINK(0x01E187D8, "roundtime", proundtime),
	GLOBALVAR_LINK(0x01E187EC, "buytime", pbuytime),
	GLOBALVAR_LINK(0x01E18800, "freezetime", pfreezetime),
	GLOBALVAR_LINK(0x01E18814, "c4timer", pc4timer),
	GLOBALVAR_LINK(0x01E18828, "ghostfrequency", pghostfrequency),
	GLOBALVAR_LINK(0x01E1883C, "autokick", pautokick),
	GLOBALVAR_LINK(0x01E18850, "autokick_timeout", pautokick_timeout),
	GLOBALVAR_LINK(0x01E18864, "restartround", prestartround),
	GLOBALVAR_LINK(0x01E18878, "sv_restart", psv_restart),
	GLOBALVAR_LINK(0x01E1888C, "limitteams", plimitteams),
	GLOBALVAR_LINK(0x01E188A0, "autoteambalance", pautoteambalance),
	GLOBALVAR_LINK(0x01E188B4, "tkpunish", ptkpunish),
	GLOBALVAR_LINK(0x01E188C8, "hostagepenalty", phostagepenalty),
	GLOBALVAR_LINK(0x01E188DC, "mirrordamage", pmirrordamage),
	GLOBALVAR_LINK(0x01E188F0, "logmessages", plogmessages),
	GLOBALVAR_LINK(0x01E18904, "forcecamera", pforcecamera),
	GLOBALVAR_LINK(0x01E18918, "forcechasecam", pforcechasecam),
	GLOBALVAR_LINK(0x01E1892C, "mapvoteratio", pmapvoteratio),
	GLOBALVAR_LINK(0x01E18940, "logdetail", plogdetail),
	GLOBALVAR_LINK(0x01E18954, "startmoney", pstartmoney),
	GLOBALVAR_LINK(0x01E18968, "maxrounds", pmaxrounds),
	GLOBALVAR_LINK(0x01E1897C, "winlimit", pwinlimit),
	GLOBALVAR_LINK(0x01E18990, "windifference", pwindifference),
	GLOBALVAR_LINK(0x01E189B8, "playerid", pplayerid),
	GLOBALVAR_LINK(0x01E189CC, "allow_spectators", pallow_spectators),
	GLOBALVAR_LINK(0x01E189E0, "mp_chattime", pmp_chattime),
	GLOBALVAR_LINK(0x01E189F4, "kick_percent", pkick_percent),
	GLOBALVAR_LINK(0x01E18A08, "humans_join_team", phumans_join_team),
	GLOBALVAR_LINK(0x01E195D4, "sk_plr_9mm_bullet1", psk_plr_9mm_bullet1),
	GLOBALVAR_LINK(0x01E195E8, "sk_plr_9mm_bullet2", psk_plr_9mm_bullet2),
	GLOBALVAR_LINK(0x01E195FC, "sk_plr_9mm_bullet3", psk_plr_9mm_bullet3),
	GLOBALVAR_LINK(0x01E19610, "sk_plr_357_bullet1", psk_plr_357_bullet1),
	GLOBALVAR_LINK(0x01E19624, "sk_plr_357_bullet2", psk_plr_357_bullet2),
	GLOBALVAR_LINK(0x01E19638, "sk_plr_357_bullet3", psk_plr_357_bullet3),
	GLOBALVAR_LINK(0x01E1964C, "sk_plr_9mmAR_bullet1", psk_plr_9mmAR_bullet1),
	GLOBALVAR_LINK(0x01E19660, "sk_plr_9mmAR_bullet2", psk_plr_9mmAR_bullet2),
	GLOBALVAR_LINK(0x01E19674, "sk_plr_9mmAR_bullet3", psk_plr_9mmAR_bullet3),
	GLOBALVAR_LINK(0x01E19688, "sk_plr_9mmAR_grenade1", psk_plr_9mmAR_grenade1),
	GLOBALVAR_LINK(0x01E1969C, "sk_plr_9mmAR_grenade2", psk_plr_9mmAR_grenade2),
	GLOBALVAR_LINK(0x01E196B0, "sk_plr_9mmAR_grenade3", psk_plr_9mmAR_grenade3),
	GLOBALVAR_LINK(0x01E196C4, "sk_plr_buckshot1", psk_plr_buckshot1),
	GLOBALVAR_LINK(0x01E196D8, "sk_plr_buckshot2", psk_plr_buckshot2),
	GLOBALVAR_LINK(0x01E196EC, "sk_plr_buckshot3", psk_plr_buckshot3),
	GLOBALVAR_LINK(0x01E19778, "sk_plr_rpg1", psk_plr_rpg1),
	GLOBALVAR_LINK(0x01E1978C, "sk_plr_rpg2", psk_plr_rpg2),
	GLOBALVAR_LINK(0x01E197A0, "sk_plr_rpg3", psk_plr_rpg3),
	GLOBALVAR_LINK(0x01E1991C, "sk_12mm_bullet1", psk_12mm_bullet1),
	GLOBALVAR_LINK(0x01E19930, "sk_12mm_bullet2", psk_12mm_bullet2),
	GLOBALVAR_LINK(0x01E19944, "sk_12mm_bullet3", psk_12mm_bullet3),
	GLOBALVAR_LINK(0x01E19958, "sk_9mmAR_bullet1", psk_9mmAR_bullet1),
	GLOBALVAR_LINK(0x01E1996C, "sk_9mmAR_bullet2", psk_9mmAR_bullet2),
	GLOBALVAR_LINK(0x01E19980, "sk_9mmAR_bullet3", psk_9mmAR_bullet3),
	GLOBALVAR_LINK(0x01E19994, "sk_9mm_bullet1", psk_9mm_bullet1),
	GLOBALVAR_LINK(0x01E199A8, "sk_9mm_bullet2", psk_9mm_bullet2),
	GLOBALVAR_LINK(0x01E199BC, "sk_9mm_bullet3", psk_9mm_bullet3),
	GLOBALVAR_LINK(0x01E19A0C, "sk_suitcharger1", psk_suitcharger1),
	GLOBALVAR_LINK(0x01E19A20, "sk_suitcharger2", psk_suitcharger2),
	GLOBALVAR_LINK(0x01E19A34, "sk_suitcharger3", psk_suitcharger3),
	GLOBALVAR_LINK(0x01E19A48, "sk_battery1", psk_battery1),
	GLOBALVAR_LINK(0x01E19A5C, "sk_battery2", psk_battery2),
	GLOBALVAR_LINK(0x01E19A70, "sk_battery3", psk_battery3),
	GLOBALVAR_LINK(0x01E19A84, "sk_healthcharger1", psk_healthcharger1),
	GLOBALVAR_LINK(0x01E19A98, "sk_healthcharger2", psk_healthcharger2),
	GLOBALVAR_LINK(0x01E19AAC, "sk_healthcharger3", psk_healthcharger3),
	GLOBALVAR_LINK(0x01E19AC0, "sk_healthkit1", psk_healthkit1),
	GLOBALVAR_LINK(0x01E19AD4, "sk_healthkit2", psk_healthkit2),
	GLOBALVAR_LINK(0x01E19AE8, "sk_healthkit3", psk_healthkit3),
	GLOBALVAR_LINK(0x01E19AFC, "sk_scientist_heal1", psk_scientist_heal1),
	GLOBALVAR_LINK(0x01E19B10, "sk_scientist_heal2", psk_scientist_heal2),
	GLOBALVAR_LINK(0x01E19B24, "sk_scientist_heal3", psk_scientist_heal3),
	GLOBALVAR_LINK(0x01E10738, "g_flBotCommandInterval", pg_flBotCommandInterval),
	GLOBALVAR_LINK(0x01E1073C, "g_flBotFullThinkInterval", pg_flBotFullThinkInterval),
	GLOBALVAR_LINK(0x01E61B44, "_ZL11gTankSpread", pgTankSpread),
	GLOBALVAR_LINK(0x01E28A20, "BotArgs", pBotArgs),
	GLOBALVAR_LINK(0x01E28A30, "UseBotArgs", pUseBotArgs),
	GLOBALVAR_LINK(0x01E1E040, "g_weaponStruct", pg_weaponStruct),
	GLOBALVAR_LINK(0x01E0EFF8, "cv_bot_traceview", pcv_bot_traceview),
	GLOBALVAR_LINK(0x01E0F00C, "cv_bot_stop", pcv_bot_stop),
	GLOBALVAR_LINK(0x01E0F020, "cv_bot_show_nav", pcv_bot_show_nav),
	GLOBALVAR_LINK(0x01E0F034, "cv_bot_show_danger", pcv_bot_show_danger),
	GLOBALVAR_LINK(0x01E0F048, "cv_bot_nav_edit", pcv_bot_nav_edit),
	GLOBALVAR_LINK(0x01E0F05C, "cv_bot_nav_zdraw", pcv_bot_nav_zdraw),
	GLOBALVAR_LINK(0x01E0F070, "cv_bot_walk", pcv_bot_walk),
	GLOBALVAR_LINK(0x01E0F084, "cv_bot_difficulty", pcv_bot_difficulty),
	GLOBALVAR_LINK(0x01E0F098, "cv_bot_debug", pcv_bot_debug),
	GLOBALVAR_LINK(0x01E0F0AC, "cv_bot_quicksave", pcv_bot_quicksave),
	GLOBALVAR_LINK(0x01E0F0C0, "cv_bot_quota", pcv_bot_quota),
	GLOBALVAR_LINK(0x01E0F0D4, "cv_bot_quota_match", pcv_bot_quota_match),
	GLOBALVAR_LINK(0x01E0F0E8, "cv_bot_prefix", pcv_bot_prefix),
	GLOBALVAR_LINK(0x01E0F0FC, "cv_bot_allow_rogues", pcv_bot_allow_rogues),
	GLOBALVAR_LINK(0x01E0F110, "cv_bot_allow_pistols", pcv_bot_allow_pistols),
	GLOBALVAR_LINK(0x01E0F124, "cv_bot_allow_shotguns", pcv_bot_allow_shotguns),
	GLOBALVAR_LINK(0x01E0F138, "cv_bot_allow_sub_machine_guns", pcv_bot_allow_sub_machine_guns),
	GLOBALVAR_LINK(0x01E0F14C, "cv_bot_allow_rifles", pcv_bot_allow_rifles),
	GLOBALVAR_LINK(0x01E0F160, "cv_bot_allow_machine_guns", pcv_bot_allow_machine_guns),
	GLOBALVAR_LINK(0x01E0F174, "cv_bot_allow_grenades", pcv_bot_allow_grenades),
	GLOBALVAR_LINK(0x01E0F188, "cv_bot_allow_snipers", pcv_bot_allow_snipers),
	GLOBALVAR_LINK(0x01E0F19C, "cv_bot_allow_shield", pcv_bot_allow_shield),
	GLOBALVAR_LINK(0x01E0F1B0, "cv_bot_join_team", pcv_bot_join_team),
	GLOBALVAR_LINK(0x01E0F1C4, "cv_bot_join_after_player", pcv_bot_join_after_player),
	GLOBALVAR_LINK(0x01E0F1D8, "cv_bot_auto_vacate", pcv_bot_auto_vacate),
	GLOBALVAR_LINK(0x01E0F1EC, "cv_bot_zombie", pcv_bot_zombie),
	GLOBALVAR_LINK(0x01E0F200, "cv_bot_defer_to_human", pcv_bot_defer_to_human),
	GLOBALVAR_LINK(0x01E0F214, "cv_bot_chatter", pcv_bot_chatter),
	GLOBALVAR_LINK(0x01E0F228, "cv_bot_profile_db", pcv_bot_profile_db),
	GLOBALVAR_LINK(0x01E233BC, "cv_tutor_message_repeats", pcv_tutor_message_repeats),
	GLOBALVAR_LINK(0x01E233D0, "cv_tutor_debug_level", pcv_tutor_debug_level),
	GLOBALVAR_LINK(0x01E233E4, "cv_tutor_view_distance", pcv_tutor_view_distance),
	GLOBALVAR_LINK(0x01E233F8, "cv_tutor_viewable_check_interval", pcv_tutor_viewable_check_interval),
	GLOBALVAR_LINK(0x01E2340C, "cv_tutor_look_distance", pcv_tutor_look_distance),
	GLOBALVAR_LINK(0x01E23420, "cv_tutor_look_angle", pcv_tutor_look_angle),
	GLOBALVAR_LINK(0x01E23434, "cv_tutor_examine_time", pcv_tutor_examine_time),
	GLOBALVAR_LINK(0x01E23448, "cv_tutor_message_minimum_display_time", pcv_tutor_message_minimum_display_time),
	GLOBALVAR_LINK(0x01E2345C, "cv_tutor_message_character_display_time_coefficient", pcv_tutor_message_character_display_time_coefficient),
	GLOBALVAR_LINK(0x01E23470, "cv_tutor_hint_interval_time", pcv_tutor_hint_interval_time),
	GLOBALVAR_LINK(0x01E287F8, "_ZL12navAreaCount", pnavAreaCount),
	GLOBALVAR_LINK(0x01E287FC, "_ZL12currentIndex", pcurrentIndex),
	GLOBALVAR_LINK(0x01E2A3E8, "_ZN9CLocalNav15flNextCvarCheckE", CLocalNav::pflNextCvarCheck),
	GLOBALVAR_LINK(0x01E2A3D8, "_ZN9CLocalNav12s_flStepSizeE", CLocalNav::ps_flStepSize),
	GLOBALVAR_LINK(0x01E2A3EC, "_ZN9CLocalNav15flLastThinkTimeE", CLocalNav::pflLastThinkTime),
	GLOBALVAR_LINK(0x01E2A3E4, "_ZN9CLocalNav7nodevalE", CLocalNav::pnodeval),
	GLOBALVAR_LINK(0x01E2A3F0, "_ZN9CLocalNav12tot_hostagesE", CLocalNav::ptot_hostages),
	GLOBALVAR_LINK(0x01E2A298, "_ZN9CLocalNav8hostagesE", CLocalNav::phostages),
	GLOBALVAR_LINK(0x01E2A3E0, "_ZN9CLocalNav11tot_inqueueE", CLocalNav::ptot_inqueue),
	GLOBALVAR_LINK(0x01E2A3DC, "_ZN9CLocalNav4qptrE", CLocalNav::pqptr),
	GLOBALVAR_LINK(0x01E2A338, "_ZN9CLocalNav5queueE", CLocalNav::pqueue),
	GLOBALVAR_LINK(0x01E17AD0, "_ZN10CBreakable13pSpawnObjectsE", CBreakable::ppSpawnObjects),
	GLOBALVAR_LINK(0x01E17BA0, "_ZN10CBreakable11pSoundsWoodE", CBreakable::ppSoundsWood),
	GLOBALVAR_LINK(0x01E17BAC, "_ZN10CBreakable12pSoundsFleshE", CBreakable::ppSoundsFlesh),
	GLOBALVAR_LINK(0x01E17BC4, "_ZN10CBreakable12pSoundsMetalE", CBreakable::ppSoundsMetal),
	GLOBALVAR_LINK(0x01E17BD0, "_ZN10CBreakable15pSoundsConcreteE", CBreakable::ppSoundsConcrete),
	GLOBALVAR_LINK(0x01E17BDC, "_ZN10CBreakable12pSoundsGlassE", CBreakable::ppSoundsGlass),
	GLOBALVAR_LINK(0x01E17C08, "_ZN9CPushable12m_soundNamesE", CPushable::pm_soundNames),
	GLOBALVAR_LINK(0x01E1E00C, "_ZN8CDeadHEV9m_szPosesE", CDeadHEV::pm_szPoses),
	GLOBALVAR_LINK(0x01E1DD88, "_ZN11CBasePlayer16m_playerSaveDataE", CBasePlayer::pm_playerSaveData),
	GLOBALVAR_LINK(0x01E14A68, "_ZN11CBaseEntity10m_SaveDataE", CBaseEntity::pm_SaveData),
	GLOBALVAR_LINK(0x01E22DAC, "_ZN12CGlobalState10m_SaveDataE", CGlobalState::pm_SaveData),
	GLOBALVAR_LINK(0x01E14390, "_ZN9CEnvSpark10m_SaveDataE", CEnvSpark::pm_SaveData),
	GLOBALVAR_LINK(0x01E14330, "_ZN19CMomentaryRotButton10m_SaveDataE", CMomentaryRotButton::pm_SaveData),
	GLOBALVAR_LINK(0x01E14240, "_ZN10CEnvGlobal10m_SaveDataE", CEnvGlobal::pm_SaveData),
	GLOBALVAR_LINK(0x01E1B4C0, "_ZN8CGrenade10m_SaveDataE", CGrenade::pm_SaveData),
	GLOBALVAR_LINK(0x01E1B998, "_ZN9CWreckage10m_SaveDataE", CWreckage::pm_SaveData),
	GLOBALVAR_LINK(0x01E1B968, "_ZN13CCyclerSprite10m_SaveDataE", CCyclerSprite::pm_SaveData),
	GLOBALVAR_LINK(0x01E1B958, "_ZN7CCycler10m_SaveDataE", CCycler::pm_SaveData),
	GLOBALVAR_LINK(0x01E1BE38, "_ZN6CLight10m_SaveDataE", CLight::pm_SaveData),
	GLOBALVAR_LINK(0x01E1BB00, "_ZN11CWallHealth10m_SaveDataE", CWallHealth::pm_SaveData),
	GLOBALVAR_LINK(0x01E1B850, "_ZN9CRecharge10m_SaveDataE", CRecharge::pm_SaveData),
	GLOBALVAR_LINK(0x01E1C248, "_ZN16CFuncMortarField10m_SaveDataE", CFuncMortarField::pm_SaveData),
	GLOBALVAR_LINK(0x01E17A08, "_ZN13CEnvExplosion10m_SaveDataE", CEnvExplosion::pm_SaveData),
	GLOBALVAR_LINK(0x01E13F38, "_ZN13CFuncRotating10m_SaveDataE", CFuncRotating::pm_SaveData),
	GLOBALVAR_LINK(0x01E13F88, "_ZN9CPendulum10m_SaveDataE", CPendulum::pm_SaveData),
	GLOBALVAR_LINK(0x01E16FB0, "_ZN9CBaseDoor10m_SaveDataE", CBaseDoor::pm_SaveData),
	GLOBALVAR_LINK(0x01E17020, "_ZN14CMomentaryDoor10m_SaveDataE", CMomentaryDoor::pm_SaveData),
	GLOBALVAR_LINK(0x01E17B50, "_ZN10CBreakable10m_SaveDataE", CBreakable::pm_SaveData),
	GLOBALVAR_LINK(0x01E17BE8, "_ZN9CPushable10m_SaveDataE", CPushable::pm_SaveData),
	GLOBALVAR_LINK(0x01E18180, "_ZN9CFuncTank10m_SaveDataE", CFuncTank::pm_SaveData),
	GLOBALVAR_LINK(0x01E18320, "_ZN14CFuncTankLaser10m_SaveDataE", CFuncTankLaser::pm_SaveData),
	GLOBALVAR_LINK(0x01E18340, "_ZN17CFuncTankControls10m_SaveDataE", CFuncTankControls::pm_SaveData),
	GLOBALVAR_LINK(0x01E22408, "_ZN12CFuncVehicle10m_SaveDataE", CFuncVehicle::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D2D8, "_ZN11CPathCorner10m_SaveDataE", CPathCorner::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D2E8, "_ZN10CPathTrack10m_SaveDataE", CPathTrack::pm_SaveData),
	GLOBALVAR_LINK(0x01E1E01C, "_ZN12CRevertSaved10m_SaveDataE", CRevertSaved::pm_SaveData),
	GLOBALVAR_LINK(0x01E1BF38, "_ZN11CRuleEntity10m_SaveDataE", CRuleEntity::pm_SaveData),
	GLOBALVAR_LINK(0x01E1BF48, "_ZN9CGameText10m_SaveDataE", CGameText::pm_SaveData),
	GLOBALVAR_LINK(0x01E1BF58, "_ZN15CGamePlayerZone10m_SaveDataE", CGamePlayerZone::pm_SaveData),
	GLOBALVAR_LINK(0x01E20B10, "_ZN17CFrictionModifier10m_SaveDataE", CFrictionModifier::pm_SaveData),
	GLOBALVAR_LINK(0x01E20B20, "_ZN12CAutoTrigger10m_SaveDataE", CAutoTrigger::pm_SaveData),
	GLOBALVAR_LINK(0x01E20B40, "_ZN13CTriggerRelay10m_SaveDataE", CTriggerRelay::pm_SaveData),
	GLOBALVAR_LINK(0x01E20B50, "_ZN13CMultiManager10m_SaveDataE", CMultiManager::pm_SaveData),
	GLOBALVAR_LINK(0x01E20BA0, "_ZN12CChangeLevel10m_SaveDataE", CChangeLevel::pm_SaveData),
	GLOBALVAR_LINK(0x01E20BE0, "_ZN20CTriggerChangeTarget10m_SaveDataE", CTriggerChangeTarget::pm_SaveData),
	GLOBALVAR_LINK(0x01E20BF0, "_ZN14CTriggerCamera10m_SaveDataE", CTriggerCamera::pm_SaveData),
	GLOBALVAR_LINK(0x01E208D8, "_ZN16CFuncWeaponCheck10m_SaveDataE", CFuncWeaponCheck::pm_SaveData),
	GLOBALVAR_LINK(0x01E20888, "_ZN14CBaseGrenCatch10m_SaveDataE", CBaseGrenCatch::pm_SaveData),
	GLOBALVAR_LINK(0x01E13228, "_ZN8CAirtank10m_SaveDataE", CAirtank::pm_SaveData),
	GLOBALVAR_LINK(0x01E14270, "_ZN12CMultiSource10m_SaveDataE", CMultiSource::pm_SaveData),
	GLOBALVAR_LINK(0x01E20538, "_ZN10CBaseDelay10m_SaveDataE", CBaseDelay::pm_SaveData),
	GLOBALVAR_LINK(0x01E13438, "_ZN14CBaseAnimating10m_SaveDataE", CBaseAnimating::pm_SaveData),
	GLOBALVAR_LINK(0x01E20558, "_ZN11CBaseToggle10m_SaveDataE", CBaseToggle::pm_SaveData),
	GLOBALVAR_LINK(0x01E142B0, "_ZN11CBaseButton10m_SaveDataE", CBaseButton::pm_SaveData),
	GLOBALVAR_LINK(0x01E20040, "_ZN15CAmbientGeneric10m_SaveDataE", CAmbientGeneric::pm_SaveData),
	GLOBALVAR_LINK(0x01E20080, "_ZN9CEnvSound10m_SaveDataE", CEnvSound::pm_SaveData),
	GLOBALVAR_LINK(0x01E200A0, "_ZN8CSpeaker10m_SaveDataE", CSpeaker::pm_SaveData),
	GLOBALVAR_LINK(0x01E17258, "_ZN9CBubbling10m_SaveDataE", CBubbling::pm_SaveData),
	GLOBALVAR_LINK(0x01E17288, "_ZN10CLightning10m_SaveDataE", CLightning::pm_SaveData),
	GLOBALVAR_LINK(0x01E17358, "_ZN6CLaser10m_SaveDataE", CLaser::pm_SaveData),
	GLOBALVAR_LINK(0x01E17388, "_ZN5CGlow10m_SaveDataE", CGlow::pm_SaveData),
	GLOBALVAR_LINK(0x01E173A8, "_ZN7CSprite10m_SaveDataE", CSprite::pm_SaveData),
	GLOBALVAR_LINK(0x01E173C8, "_ZN11CGibShooter10m_SaveDataE", CGibShooter::pm_SaveData),
	GLOBALVAR_LINK(0x01E227AC, "_ZN15CBasePlayerItem10m_SaveDataE", CBasePlayerItem::pm_SaveData),
	GLOBALVAR_LINK(0x01E227E0, "_ZN17CBasePlayerWeapon10m_SaveDataE", CBasePlayerWeapon::pm_SaveData),
	GLOBALVAR_LINK(0x01E22850, "_ZN10CWeaponBox10m_SaveDataE", CWeaponBox::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D420, "_ZN14CBasePlatTrain10m_SaveDataE", CBasePlatTrain::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D450, "_ZN12CFuncPlatRot10m_SaveDataE", CFuncPlatRot::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D470, "_ZN10CFuncTrain10m_SaveDataE", CFuncTrain::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D4A0, "_ZN15CFuncTrackTrain10m_SaveDataE", CFuncTrackTrain::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D560, "_ZN16CFuncTrackChange10m_SaveDataE", CFuncTrackChange::pm_SaveData),
	GLOBALVAR_LINK(0x01E1D5F0, "_ZN10CGunTarget10m_SaveDataE", CGunTarget::pm_SaveData),
	GLOBALVAR_LINK(0x01E75FE0, "_ZN15CBasePlayerItem13ItemInfoArrayE", CBasePlayerItem::pItemInfoArray),
	GLOBALVAR_LINK(0x01E75ED8, "_ZN15CBasePlayerItem13AmmoInfoArrayE", CBasePlayerItem::pAmmoInfoArray),
	GLOBALVAR_LINK(0x01E28816, "_ZN13CCSBotManager17m_isMapDataLoadedE", CCSBotManager::pm_isMapDataLoaded),
	GLOBALVAR_LINK(0x01E28818, "_ZN13CCSBotManager9m_editCmdE", CCSBotManager::pm_editCmd),
	GLOBALVAR_LINK(0x01E2881C, "_ZN13CCSBotManager17m_flNextCVarCheckE", CCSBotManager::pm_flNextCVarCheck),
	GLOBALVAR_LINK(0x01E28814, "_ZN13CCSBotManager15m_isLearningMapE", CCSBotManager::pm_isLearningMap),
	GLOBALVAR_LINK(0x01E28815, "_ZN13CCSBotManager21m_isAnalysisRequestedE", CCSBotManager::pm_isAnalysisRequested),
	GLOBALVAR_LINK(0x01E233BC, "cv_tutor_message_repeats", pcv_tutor_message_repeats),
	GLOBALVAR_LINK(0x01E233D0, "cv_tutor_debug_level", pcv_tutor_debug_level),
	GLOBALVAR_LINK(0x01E233E4, "cv_tutor_view_distance", pcv_tutor_view_distance),
	GLOBALVAR_LINK(0x01E233F8, "cv_tutor_viewable_check_interval", pcv_tutor_viewable_check_interval),
	GLOBALVAR_LINK(0x01E2340C, "cv_tutor_look_distance", pcv_tutor_look_distance),
	GLOBALVAR_LINK(0x01E23420, "cv_tutor_look_angle", pcv_tutor_look_angle),
	GLOBALVAR_LINK(0x01E23434, "cv_tutor_examine_time", pcv_tutor_examine_time),
	GLOBALVAR_LINK(0x01E23448, "cv_tutor_message_minimum_display_time", pcv_tutor_message_minimum_display_time),
	GLOBALVAR_LINK(0x01E2345C, "cv_tutor_message_character_display_time_coefficient", pcv_tutor_message_character_display_time_coefficient),
	GLOBALVAR_LINK(0x01E23470, "cv_tutor_hint_interval_time", pcv_tutor_hint_interval_time),
	GLOBALVAR_LINK(0x01E11EE4, "cv_hostage_debug", pcv_hostage_debug),
	GLOBALVAR_LINK(0x01E11EF8, "cv_hostage_stop", pcv_hostage_stop),
	//GLOBALVAR_LINK(0x01E2A228, "_ZL14placeDirectory", pplaceDirectory),	// DONT USE - NOXREF
	GLOBALVAR_LINK(0x01E2A0E4, "TheNavLadderList", pTheNavLadderList),
	GLOBALVAR_LINK(0x01E2A0F0, "TheHidingSpotList", pTheHidingSpotList),
	GLOBALVAR_LINK(0x01E14C5C, "sPlayerModelFiles", psPlayerModelFiles),
	GLOBALVAR_LINK(0x01E5D6F0, "g_flTimeLimit", pg_flTimeLimit),
	GLOBALVAR_LINK(0x01E5D6F4, "g_flResetTime", pg_flResetTime),
	GLOBALVAR_LINK(0x01E14C58, "g_bClientPrintEnable", pg_bClientPrintEnable),
	GLOBALVAR_LINK(0x01E5D6F8, "g_skipCareerInitialSpawn", pg_skipCareerInitialSpawn),
	GLOBALVAR_LINK(0x01E31768, "m_usResetDecals", pm_usResetDecals),
	GLOBALVAR_LINK(0x01E31760, "g_iShadowSprite", pg_iShadowSprite),
	GLOBALVAR_LINK(0x01E31770, "_ZL11g_PVSStatus", pg_PVSStatus),
	GLOBALVAR_LINK(0x01E14C90, "_ZL18entity_field_alias", pentity_field_alias),
	GLOBALVAR_LINK(0x01E14D68, "_ZL18player_field_alias", pplayer_field_alias),
	GLOBALVAR_LINK(0x01E14DD8, "custom_entity_field_alias", pcustom_entity_field_alias),
	//GLOBALVAR_LINK(0x01E5D718, "_ZL14g_serveractive", pg_serveractive),
	GLOBALVAR_LINK(0x01E2A0A8, "_ZL17goodSizedAreaList", pgoodSizedAreaList),
	GLOBALVAR_LINK(0x01E2A0D8, "TheNavAreaList", pTheNavAreaList),
	GLOBALVAR_LINK(0x01E29888, "TheNavAreaGrid", pTheNavAreaGrid),
	GLOBALVAR_LINK(0x01E11E88, "Opposite", pOpposite),
	GLOBALVAR_LINK(0x01E2A250, "_ZN8CNavNode6m_listE", CNavNode::pm_list),
	GLOBALVAR_LINK(0x01E2A254, "_ZN8CNavNode12m_listLengthE", CNavNode::pm_listLength),
	GLOBALVAR_LINK(0x01E11584, "_ZN8CNavArea14m_masterMarkerE", CNavArea::pm_masterMarker),
	GLOBALVAR_LINK(0x01E11588, "_ZN10HidingSpot8m_nextIDE", HidingSpot::pm_nextID),
	GLOBALVAR_LINK(0x01E2A108, "_ZN10HidingSpot14m_masterMarkerE", HidingSpot::pm_masterMarker),
	GLOBALVAR_LINK(0x01E11580, "_ZN8CNavArea8m_nextIDE", CNavArea::pm_nextID),
	GLOBALVAR_LINK(0x01E2A100, "_ZN8CNavArea9m_isResetE", CNavArea::pm_isReset),
	GLOBALVAR_LINK(0x01E2A0FC, "_ZN8CNavArea10m_openListE", CNavArea::pm_openList),
	GLOBALVAR_LINK(0x01E2A104, "lastDrawTimestamp", plastDrawTimestamp),
	GLOBALVAR_LINK(0x01E2A118, "_ZL13editTimestamp", peditTimestamp),
	GLOBALVAR_LINK(0x01E2A10C, "_ZL10markedArea", pmarkedArea),
	GLOBALVAR_LINK(0x01E2A110, "_ZL16lastSelectedArea", plastSelectedArea),
	GLOBALVAR_LINK(0x01E1158C, "_ZL12markedCorner", pmarkedCorner),
	GLOBALVAR_LINK(0x01E2A114, "_ZL17isCreatingNavArea", pisCreatingNavArea),
	GLOBALVAR_LINK(0x01E2A115, "_ZL10isAnchored", pisAnchored),
	GLOBALVAR_LINK(0x01E2A0C8, "_ZL6anchor", panchor),
	GLOBALVAR_LINK(0x01E2A116, "_ZL11isPlaceMode", pisPlaceMode),
	GLOBALVAR_LINK(0x01E2A117, "_ZL15isPlacePainting", pisPlacePainting),
	GLOBALVAR_LINK(0x01E29CA4, "_ZL9BlockedID", pBlockedID),
	GLOBALVAR_LINK(0x01E2A120, "_ZL14BlockedIDCount", pBlockedIDCount),
	GLOBALVAR_LINK(0x01E14988, "_ZL14gFunctionTable", pgFunctionTable),
	GLOBALVAR_LINK(0x01E14A50, "gNewDLLFunctions", pgNewDLLFunctions),
	GLOBALVAR_LINK(0x01E28810, "TheBots", pTheBots),
	GLOBALVAR_LINK(0x01E24950, "_ZL8taskInfo", ptaskInfo),
	GLOBALVAR_LINK(0x01E76594, "TheCareerTasks", pTheCareerTasks),
	GLOBALVAR_LINK(0x01E28C7C, "TheBotProfiles", pTheBotProfiles),
	//GLOBALVAR_LINK(0x01E287CC, "g_pSelectedZombieSpawn", pg_pSelectedZombieSpawn),
	GLOBALVAR_LINK(0x01E287F0, "TheBotPhrases", pTheBotPhrases),
	GLOBALVAR_LINK(0x01E7657C, "TheTutor", pTheTutor),
	GLOBALVAR_LINK(0x01E2A25C, "g_pHostages", pg_pHostages),
	GLOBALVAR_LINK(0x01E2A258, "g_iHostageNumber", pg_iHostageNumber),
	GLOBALVAR_LINK(0x01E16EE0, "_ZL11outputLevel", poutputLevel),
	GLOBALVAR_LINK(0x01E61B40, "_ZL19theDebugOutputTypes", ptheDebugOutputTypes),
	GLOBALVAR_LINK(0x01E61740, "_ZL14theDebugBuffer", ptheDebugBuffer),
	//GLOBALVAR_LINK(0x01E75D04, "_ZL9g_LessCtx", pg_LessCtx),
	GLOBALVAR_LINK(0x01E62670, "g_pevLastInflictor", pg_pevLastInflictor),
	GLOBALVAR_LINK(0x01E62788, "g_pLastSpawn", pg_pLastSpawn),
	GLOBALVAR_LINK(0x01E63590, "g_pLastCTSpawn", pg_pLastCTSpawn),
	GLOBALVAR_LINK(0x01E63594, "g_pLastTerroristSpawn", pg_pLastTerroristSpawn),
	//GLOBALVAR_LINK(0x01E62990, "_ZL11zombieSpawn", pzombieSpawn),
	//GLOBALVAR_LINK(0x01E636E8, "_ZL16zombieSpawnCount", pzombieSpawnCount),
	GLOBALVAR_LINK(0x01E13838, "svBlending", psvBlending),
	GLOBALVAR_LINK(0x01E312D0, "IEngineStudio", pIEngineStudio),
	GLOBALVAR_LINK(0x01E2DAA8, "g_pstudiohdr", pg_pstudiohdr),
	GLOBALVAR_LINK(0x01E2F8C0, "g_pRotationMatrix", pg_pRotationMatrix),
	GLOBALVAR_LINK(0x01E2F8B0, "g_pBoneTransform", pg_pBoneTransform),
	GLOBALVAR_LINK(0x01E0DF70, "primaryWeaponBuyInfoCT", pprimaryWeaponBuyInfoCT),
	GLOBALVAR_LINK(0x01E0E00C, "secondaryWeaponBuyInfoCT", psecondaryWeaponBuyInfoCT),
	GLOBALVAR_LINK(0x01E0E030, "primaryWeaponBuyInfoT", pprimaryWeaponBuyInfoT),
	GLOBALVAR_LINK(0x01E0E0CC, "secondaryWeaponBuyInfoT", psecondaryWeaponBuyInfoT),
	GLOBALVAR_LINK(0x01E287E8, "_ZN19BotChatterInterface16m_encourageTimerE", BotChatterInterface::pm_encourageTimer),
	GLOBALVAR_LINK(0x01E287E0, "_ZN19BotChatterInterface22m_radioSilenceIntervalE", BotChatterInterface::pm_radioSilenceInterval),
	//GLOBALVAR_LINK(0x01E2F8BC, "omega", pomega),	// LOCAL
	//GLOBALVAR_LINK(0x01E312E0, "cosom", pcosom),	// LOCAL
	//GLOBALVAR_LINK(0x01E306C8, "sinom", psinom),	// LOCAL
	//GLOBALVAR_LINK(0x01E2F8B4, "sclp", psclp),	// LOCAL
	//GLOBALVAR_LINK(0x01E2F8B8, "sclq", psclq),	// LOCAL

#endif // Data_References_Region

	{ 0, nullptr, 0, 0, false }
};
