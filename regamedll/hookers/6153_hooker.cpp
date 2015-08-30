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

#define CBASE_VIRTUAL_COUNT	58

template<typename MFUNC>
size_t mfunc_ptr_cast(MFUNC f)
{
	auto x = f;
	size_t addr = (size_t &)x;
	return addr;
}

// Offset where engine assumed be loaded to ajust hooks offsets. NULL for the Linux to trigger symbols searching.
#ifdef _WIN32
extern const size_t g_BaseOffset = 0x01D00000;
#else
extern const size_t g_BaseOffset = NULL;
#endif

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
//#define CS_Util_Region
//#define CS_Init_Region
//#define H_Region
//#define Tutor_CS_Region
//#define Nav_Region
//#define Hostage_Region
//#define GameShr_BotProfile_Region
//#define VoiceManager_Region
//#define Vector_Region
//#define Data_References_Region
//#define Function_References_Region

FunctionHook g_FunctionHooks[] =
{

#ifndef Mem_Region

#ifdef _WIN32

	{ 0x01DE015D, "malloc", (size_t)&_malloc_mhook_ },
	{ 0x01DE2331, "calloc", (size_t)&_calloc_mhook_ },
	{ 0x01DE12A5, "realloc", (size_t)&_realloc_mhook_ },
	{ 0x01DE0E7B, "free", (size_t)&_free_mhook_ },
	{ 0x01DF27C9, "strdup", (size_t)&_strdup_mhook_ },

#endif // _WIN32

#endif // Mem_Region

#ifndef Export_Region

	{ 0x01D86730, "GiveFnptrsToDll", (size_t)&GiveFnptrsToDll },

#endif // Export_Region

#ifndef PM_Shared_Region

	{ 0x01DB6640, "PM_Move", (size_t)&PM_Move },
	{ 0x01DB6710, "PM_Init", (size_t)&PM_Init },
	{ 0x01DB1020, "PM_FindTextureType", (size_t)&PM_FindTextureType },
//pm_debug
	//{ 0x0, "PM_ShowClipBox", (size_t)&PM_ShowClipBox },
	//{ 0x0, "PM_ParticleLine", (size_t)&PM_ParticleLine },
	//{ 0x0, "PM_DrawRectangle", (size_t)&PM_DrawRectangle },
	//{ 0x0, "PM_DrawPhysEntBBox", (size_t)&PM_DrawPhysEntBBox },
	//{ 0x0, "PM_DrawBBox", (size_t)&PM_DrawBBox },
	//{ 0x0, "PM_ViewEntity", (size_t)&PM_ViewEntity },
//pm_shared
	//{ 0x01DB0AB0, "PM_SwapTextures", (size_t)&PM_SwapTextures },	// NOXREF
	//{ 0x01DB0B30, "PM_IsThereGrassTexture", (size_t)&PM_IsThereGrassTexture },	// NOXREF
	//{ 0x01DB0B60, "PM_SortTextures", (size_t)&PM_SortTextures },	// NOXREF
	{ 0x01DB0C80, "PM_InitTextureTypes", (size_t)&PM_InitTextureTypes },
	//{ 0x0, "PM_FindTextureType", (size_t)&PM_FindTextureType },
	{ 0x01DB1080, "PM_PlayStepSound", (size_t)&PM_PlayStepSound },
	//{ 0x01DB17E0, "PM_MapTextureTypeStepType", (size_t)&PM_MapTextureTypeStepType },	// NOXREF
	{ 0x01DB1860, "PM_CatagorizeTextureType", (size_t)&PM_CatagorizeTextureType },
	{ 0x01DB19B0, "PM_UpdateStepSound", (size_t)&PM_UpdateStepSound },
	//{ 0x01DB1CB0, "PM_AddToTouched", (size_t)&PM_AddToTouched },	// NOXREF
	{ 0x01DB1D50, "PM_CheckVelocity", (size_t)&PM_CheckVelocity },
	{ 0x01DB1E40, "PM_ClipVelocity", (size_t)&PM_ClipVelocity },
	//{ 0x01DB1EF0, "PM_AddCorrectGravity", (size_t)&PM_AddCorrectGravity },	// NOXREF
	//{ 0x01DB1F70, "PM_FixupGravityVelocity", (size_t)&PM_FixupGravityVelocity },	// NOXREF
	{ 0x01DB1FD0, "PM_FlyMove", (size_t)&PM_FlyMove },
	//{ 0x01DB24E0, "PM_Accelerate", (size_t)&PM_Accelerate },	// NOXREF
	{ 0x01DB2580, "PM_WalkMove", (size_t)&PM_WalkMove },
	{ 0x01DB2B50, "PM_Friction", (size_t)&PM_Friction },
	{ 0x01DB2CF0, "PM_AirAccelerate", (size_t)&PM_AirAccelerate },
	{ 0x01DB2DB0, "PM_WaterMove", (size_t)&PM_WaterMove },
	{ 0x01DB30C0, "PM_AirMove", (size_t)&PM_AirMove },
	//{ 0x01DB3200, "PM_InWater", (size_t)&PM_InWater },	// NOXREF
	{ 0x01DB3220, "PM_CheckWater", (size_t)&PM_CheckWater },
	{ 0x01DB33E0, "PM_CatagorizePosition", (size_t)&PM_CatagorizePosition },
	//{ 0x01DB3590, "PM_GetRandomStuckOffsets", (size_t)&PM_GetRandomStuckOffsets },	// NOXREF
	//{ 0x01DB35E0, "PM_ResetStuckOffsets", (size_t)&PM_ResetStuckOffsets },	// NOXREF
	{ 0x01DB3600, "PM_CheckStuck", (size_t)&PM_CheckStuck },
	{ 0x01DB3970, "PM_SpectatorMove", (size_t)&PM_SpectatorMove },
	//{ 0x01DB3C70, "PM_SplineFraction", (size_t)&PM_SplineFraction },	// NOXREF
	//{ 0x01DB3C90, "PM_SimpleSpline", (size_t)&PM_SimpleSpline },	// NOXREF
	//{ 0x01DB3CB0, "PM_FixPlayerCrouchStuck", (size_t)&PM_FixPlayerCrouchStuck },	// NOXREF
	{ 0x01DB3D50, "PM_Duck", (size_t)&PM_Duck },
	{ 0x01DB4110, "PM_LadderMove", (size_t)&PM_LadderMove },
	{ 0x01DB44D0, "PM_Ladder", (size_t)&PM_Ladder },
	//{ 0x01DB45A0, "PM_WaterJump", (size_t)&PM_WaterJump },	// NOXREF
	//{ 0x01DB4660, "PM_AddGravity", (size_t)&PM_AddGravity },	// NOXREF
	//{ 0x01DB46C0, "PM_PushEntity", (size_t)&PM_PushEntity },	// NOXREF
	{ 0x01DB4820, "PM_Physics_Toss", (size_t)&PM_Physics_Toss },
	{ 0x01DB4DE0, "PM_NoClip", (size_t)&PM_NoClip },
	//{ 0x01DB4E90, "PM_PreventMegaBunnyJumping", (size_t)&PM_PreventMegaBunnyJumping },	// NOXREF
	{ 0x01DB4F00, "PM_Jump", (size_t)&PM_Jump },
	{ 0x01DB52F0, "PM_CheckWaterJump", (size_t)&PM_CheckWaterJump },
	{ 0x01DB5560, "PM_CheckFalling", (size_t)&PM_CheckFalling },
	//{ 0x01DB5810, "PM_PlayWaterSounds", (size_t)&PM_PlayWaterSounds },	// NOXREF
	//{ 0x01DB5810, "PM_CalcRoll", (size_t)&PM_CalcRoll },	// NOXREF
	//{ 0x01DB58A0, "PM_DropPunchAngle", (size_t)&PM_DropPunchAngle },	// NOXREF
	{ 0x01DB58F0, "PM_CheckParamters", (size_t)&PM_CheckParamters },
	{ 0x01DB5BE0, "PM_ReduceTimers", (size_t)&PM_ReduceTimers },
	//{ 0x01DB5D20, "PM_ShouldDoSpectMode", (size_t)&PM_ShouldDoSpectMode },	// NOXREF
	{ 0x01DB5D50, "PM_PlayerMove", (size_t)&PM_PlayerMove },
	{ 0x01DB6430, "PM_CreateStuckTable", (size_t)&PM_CreateStuckTable },
	//{ 0x01DB66B0, "PM_GetVisEntInfo", (size_t)&PM_GetVisEntInfo },	// NOXREF
	//{ 0x01DB66E0, "PM_GetPhysEntInfo", (size_t)&PM_GetPhysEntInfo },	// NOXREF
//pm_math
	//{ 0x0, "anglemod", (size_t)&anglemod },
	{ 0x01DB0000, "AngleVectors", (size_t)&AngleVectors },
	//{ 0x0, "AngleVectorsTranspose", (size_t)&AngleVectorsTranspose },
	{ 0x01DB0200, "AngleMatrix", (size_t)&AngleMatrix },
	//{ 0x0, "AngleIMatrix", (size_t)&AngleIMatrix },
	//{ 0x0, "NormalizeAngles", (size_t)&NormalizeAngles },
	//{ 0x0, "InterpolateAngles", (size_t)&InterpolateAngles },
	//{ 0x0, "AngleBetweenVectors", (size_t)&AngleBetweenVectors },
	//{ 0x0, "VectorTransform", (size_t)&VectorTransform },
	{ 0x01DB0610, "VectorCompare", (size_t)&VectorCompare },
	{ 0x01DB0640, "VectorMA", (size_t)&VectorMA },
	//{ 0x01DB0680, "_DotProduct", (size_t)&_DotProduct },	// NOXREF
	//{ 0x01DB06A0, "_VectorSubtract", (size_t)&_VectorSubtract },	// NOXREF
	//{ 0x01DB06D0, "_VectorAdd", (size_t)&_VectorAdd },	// NOXREF
	//{ 0x01DB0700, "_VectorCopy", (size_t)&_VectorCopy },	// NOXREF
	//{ 0x01DB0720, "CrossProduct", (size_t)&_CrossProduct },	// NOXREF
	{ 0x01DB0760, "Length", (size_t)&Length },
	//{ 0x0, "Distance", (size_t)&Distance },
	{ 0x01DB07D0, "VectorNormalize", (size_t)&VectorNormalize },
	//{ 0x0, "VectorInverse", (size_t)&VectorInverse },
	{ 0x01DB0840, "VectorScale", (size_t)&VectorScale },
	//{ 0x0, "Q_log2", (size_t)&Q_log2 },
	//{ 0x0, "VectorMatrix", (size_t)&VectorMatrix },
	//{ 0x0, "VectorAngles", (size_t)&VectorAngles },

#endif // PM_Shared_Region

#ifndef Monsters_Region
//CGib
	//virtual func
	{ 0x01D70C90, "_ZN4CGib10ObjectCapsEv", mfunc_ptr_cast(&CGib::ObjectCaps_) },
	//non-virtual func
	{ 0x01D6FFE0, "_ZN4CGib5SpawnEPKc", mfunc_ptr_cast(&CGib::Spawn) },
	{ 0x01D6FCA0, "_ZN4CGib14BounceGibTouchEP11CBaseEntity", mfunc_ptr_cast(&CGib::BounceGibTouch) },
	{ 0x01D6FE40, "_ZN4CGib14StickyGibTouchEP11CBaseEntity", mfunc_ptr_cast(&CGib::StickyGibTouch) },
	{ 0x01D6FBF0, "_ZN4CGib12WaitTillLandEv", mfunc_ptr_cast(&CGib::WaitTillLand) },
	{ 0x01D6E550, "_ZN4CGib13LimitVelocityEv", mfunc_ptr_cast(&CGib::LimitVelocity) },
	//{ 0x01D6EAB0, "_ZN4CGib12SpawnHeadGibEP9entvars_s", mfunc_ptr_cast(&CGib::SpawnHeadGib) },
	{ 0x01D6EEB0, "_ZN4CGib15SpawnRandomGibsEP9entvars_sii", mfunc_ptr_cast(&CGib::SpawnRandomGibs) },
	//{ 0x01D6E640, "_ZN4CGib15SpawnStickyGibsEP9entvars_s6Vectori", mfunc_ptr_cast(&CGib::SpawnStickyGibs) },	// NOXREF
#endif // Monsters_Region

#ifndef AirTank_Region

	//virtual func
	{ 0x01D592B0, "_ZN8CAirtank5SpawnEv", mfunc_ptr_cast(&CAirtank::Spawn_) },
	{ 0x01D593A0, "_ZN8CAirtank8PrecacheEv", mfunc_ptr_cast(&CAirtank::Precache_) },
	{ 0x01D59250, "_ZN8CAirtank4SaveER5CSave", mfunc_ptr_cast(&CAirtank::Save_) },
	{ 0x01D59280, "_ZN8CAirtank7RestoreER8CRestore", mfunc_ptr_cast(&CAirtank::Restore_) },
	{ 0x01D593C0, "_ZN8CAirtank6KilledEP9entvars_si", mfunc_ptr_cast(&CAirtank::Killed_) },
	{ 0x01D59240, "_ZN8CAirtank10BloodColorEv", mfunc_ptr_cast(&CAirtank::BloodColor_) },
	//non-virtual func
	{ 0x01D59410, "_ZN8CAirtank9TankThinkEv", mfunc_ptr_cast(&CAirtank::TankThink) },
	{ 0x01D59430, "_ZN8CAirtank9TankTouchEP11CBaseEntity", mfunc_ptr_cast(&CAirtank::TankTouch) },
	{ 0x01D591F0, "item_airtank", (size_t)&item_airtank },

#endif // AirTank_Region

#ifndef Client_Region

	//{ 0x0, "_ZL8CMD_ARGCv", (size_t)&CMD_ARGC_ },
	//{ 0x0, "_ZL8CMD_ARGVi", (size_t)&CMD_ARGV_ },
	//{ 0x01D63CE0, "_Z17set_suicide_frameP9entvars_s", (size_t)&set_suicide_frame },	// NOXREF
	{ 0x01D63D30, "_Z13ClientConnectP7edict_sPKcS2_Pc", (size_t)&ClientConnect },
	{ 0x01D63D50, "_Z16ClientDisconnectP7edict_s", (size_t)&ClientDisconnect },
	{ 0x01D63E50, "_Z7respawnP9entvars_si", (size_t)&respawn },
	{ 0x01D63F60, "_Z10ClientKillP7edict_s", (size_t)&ClientKill },
	{ 0x01D64010, "_Z8ShowMenuP11CBasePlayeriiiPc_constprop_32", (size_t)&ShowMenu },
	{ 0x01D64070, "_Z12ShowVGUIMenuP11CBasePlayeriiPc", (size_t)&ShowVGUIMenu },
	{ 0x01D64130, "CountTeams", (size_t)&CountTeams },				//extern c func
	{ 0x01D64260, "_Z11ListPlayersP11CBasePlayer", (size_t)&ListPlayers },
	{ 0x01D64460, "CountTeamPlayers", (size_t)&CountTeamPlayers },			//extern c func
	{ 0x01D64580, "_Z15ProcessKickVoteP11CBasePlayerS0_", (size_t)&ProcessKickVote },
	{ 0x01D64920, "_Z17SelectDefaultTeamv", (size_t)&SelectDefaultTeam },
	{ 0x01D649A0, "_Z15CheckStartMoneyv", (size_t)&CheckStartMoney },
	{ 0x01D649F0, "_Z17ClientPutInServerP7edict_s", (size_t)&ClientPutInServer },
	{ 0x01D64F00, "Q_strlen", (size_t)&Q_strlen_ },
	{ 0x01D64F20, "_Z8Host_SayP7edict_si", (size_t)&Host_Say },
	//{ 0x0, "", (size_t)&DropSecondary },	// NOXREF
	{ 0x01D656F0, "_Z11DropPrimaryP11CBasePlayer", (size_t)&DropPrimary },
	{ 0x01D65740, "_Z10CanBuyThisP11CBasePlayeri", (size_t)&CanBuyThis },
	{ 0x01D65850, "_Z9BuyPistolP11CBasePlayeri", (size_t)&BuyPistol },
	{ 0x01D65A30, "_Z10BuyShotgunP11CBasePlayeri", (size_t)&BuyShotgun },
	{ 0x01D65B70, "_Z16BuySubMachineGunP11CBasePlayeri", (size_t)&BuySubMachineGun },
	{ 0x01D65D00, "_Z19BuyWeaponByWeaponIDP11CBasePlayer12WeaponIdType", (size_t)&BuyWeaponByWeaponID },
	{ 0x01D65E80, "_Z8BuyRifleP11CBasePlayeri", (size_t)&BuyRifle },
	{ 0x01D66070, "_Z13BuyMachineGunP11CBasePlayeri", (size_t)&BuyMachineGun },
	{ 0x01D66170, "_Z7BuyItemP11CBasePlayeri", (size_t)&BuyItem },
	{ 0x01D669A0, "_Z27HandleMenu_ChooseAppearanceP11CBasePlayeri", (size_t)&HandleMenu_ChooseAppearance },
	{ 0x01D66D10, "_Z21HandleMenu_ChooseTeamP11CBasePlayeri", (size_t)&HandleMenu_ChooseTeam },

	{ 0x01D67930, "_Z6Radio1P11CBasePlayeri", (size_t)&Radio1 },
	{ 0x01D67A20, "_Z6Radio2P11CBasePlayeri", (size_t)&Radio2 },
	{ 0x01D67B10, "_Z6Radio3P11CBasePlayeri", (size_t)&Radio3 },
	{ 0x01D67C70, "_Z10BuyGunAmmoR11CBasePlayerR15CBasePlayerItemb", (size_t)&BuyGunAmmo },

	//{ 0x01D67E50, "_Z7BuyAmmoP11CBasePlayerib", (size_t)&BuyAmmo },	// NOXREF
	//{ 0x01D67EC0, "_Z16EntityFromUserIDi", (size_t)&EntityFromUserID },	// NOXREF
	//{ 0x01D67FC0, "_Z20CountPlayersInServerv", (size_t)&CountPlayersInServer },	// NOXREF
	{ 0x01D680D0, "_Z22HandleBuyAliasCommandsP11CBasePlayerPKc", (size_t)&HandleBuyAliasCommands },
	{ 0x01D68540, "_Z24HandleRadioAliasCommandsP11CBasePlayerPKc", (size_t)&HandleRadioAliasCommands },
	{ 0x01D68840, "_Z13ClientCommandP7edict_s", (size_t)&ClientCommand },
	{ 0x01D6B230, "_Z21ClientUserInfoChangedP7edict_sPc", (size_t)&ClientUserInfoChanged },
	{ 0x01D6B4D0, "_Z16ServerDeactivatev", (size_t)&ServerDeactivate },
	{ 0x01D6B520, "_Z14ServerActivateP7edict_sii", (size_t)&ServerActivate },
	{ 0x01D6B620, "_Z14PlayerPreThinkP7edict_s", (size_t)&PlayerPreThink },
	{ 0x01D6B640, "_Z15PlayerPostThinkP7edict_s", (size_t)&PlayerPostThink },
	//{ 0x01D6B660, "_Z13ParmsNewLevelv", (size_t)&ParmsNewLevel },	// PURE
	{ 0x01D6B670, "_Z16ParmsChangeLevelv", (size_t)&ParmsChangeLevel },
	{ 0x01D6B6A0, "_Z10StartFramev", (size_t)&StartFrame },
	{ 0x01D6B740, "_Z14ClientPrecachev", (size_t)&ClientPrecache },
	{ 0x01D6CCE0, "_Z18GetGameDescriptionv", (size_t)&GetGameDescription },
	{ 0x01D6CD00, "_Z9Sys_ErrorPKc", (size_t)&Sys_Error },
	{ 0x01D6CD10, "_Z19PlayerCustomizationP7edict_sP15customization_s", (size_t)&PlayerCustomization },
	{ 0x01D6CD90, "_Z16SpectatorConnectP7edict_s", (size_t)&SpectatorConnect },
	{ 0x01D6CDB0, "_Z19SpectatorDisconnectP7edict_s", (size_t)&SpectatorDisconnect },
	{ 0x01D6CDD0, "_Z14SpectatorThinkP7edict_s", (size_t)&SpectatorThink },
	{ 0x01D6CDF0, "_Z15SetupVisibilityP7edict_sS0_PPhS2_", (size_t)&SetupVisibility },
	//{ 0x01D6CF60, "_Z14ResetPlayerPVSP7edict_si", (size_t)&ResetPlayerPVS },	// NOXREF
	//{ 0x01D6CFB0, "_Z25CheckPlayerPVSLeafChangedP7edict_si", (size_t)&CheckPlayerPVSLeafChanged },	// NOXREF
	//{ 0x01D6D020, "_Z15MarkEntityInPVSiifb", (size_t)&MarkEntityInPVS },				// NOXREF
	//{ 0x01D6D060, "_Z24CheckEntityRecentlyInPVSiif", (size_t)&CheckEntityRecentlyInPVS },	// NOXREF
	{ 0x01D6D0B0, "_Z13AddToFullPackP14entity_state_siP7edict_sS2_iiPh", (size_t)&AddToFullPack },
	{ 0x01D6D5F0, "_Z14CreateBaselineiiP14entity_state_sP7edict_si6VectorS3_", (size_t)&CreateBaseline },
	//{ 0x01D6D790, "_Z16Entity_FieldInitP7delta_s", (size_t)&Entity_FieldInit },	// NOXREF
	{ 0x01D6D800, "_Z13Entity_EncodeP7delta_sPKhS2_", (size_t)&Entity_Encode },
	//{ 0x01D6D9C0, "_Z16Player_FieldInitP7delta_s", (size_t)&Player_FieldInit },	// NOXREF
	{ 0x01D6DA00, "_Z13Player_EncodeP7delta_sPKhS2_", (size_t)&Player_Encode },
	{ 0x01D6DB10, "_Z23Custom_Entity_FieldInitP7delta_s", (size_t)&Custom_Entity_FieldInit },
	{ 0x01D6DBC0, "_Z13Custom_EncodeP7delta_sPKhS2_", (size_t)&Custom_Encode },
	{ 0x01D6DCB0, "_Z16RegisterEncodersv", (size_t)&RegisterEncoders },
	{ 0x01D6DCF0, "_Z13GetWeaponDataP7edict_sP13weapon_data_s", (size_t)&GetWeaponData },
	{ 0x01D6DF00, "_Z16UpdateClientDataPK7edict_siP12clientdata_s", (size_t)&UpdateClientData },
	{ 0x01D6E2F0, "_Z8CmdStartPK7edict_sPK9usercmd_sj", (size_t)&CmdStart },
	{ 0x01D6E360, "_Z6CmdEndPK7edict_s", (size_t)&CmdEnd },
	{ 0x01D6E410, "_Z20ConnectionlessPacketPK8netadr_sPKcPcPi", (size_t)&ConnectionlessPacket },
	{ 0x01D6E420, "_Z13GetHullBoundsiPfS_", (size_t)&GetHullBounds },
	{ 0x01D6E440, "_Z24CreateInstancedBaselinesv", (size_t)&CreateInstancedBaselines },
	{ 0x01D6E450, "_Z16InconsistentFilePK7edict_sPKcPc", (size_t)&InconsistentFile },
	{ 0x01D6E490, "_Z20AllowLagCompensationv", (size_t)&AllowLagCompensation },

#endif // Client_Region

#ifndef Cbase_Region

	//base func
	{ 0x01D61A30, "_Z19CaseInsensitiveHashPKci", (size_t)&CaseInsensitiveHash },
	{ 0x01D61A70, "_Z20EmptyEntityHashTablev", (size_t)&EmptyEntityHashTable },
	{ 0x01D61AE0, "_Z18AddEntityHashValueP9entvars_sPKc12hash_types_e", (size_t)&AddEntityHashValue },
	{ 0x01D61CA0, "_Z21RemoveEntityHashValueP9entvars_sPKc12hash_types_e", (size_t)&RemoveEntityHashValue },

	{ 0x01D61E20, "_Z13printEntitiesv", (size_t)&printEntities },
	{ 0x01D61ED0, "_Z19CREATE_NAMED_ENTITYj", (size_t)&CREATE_NAMED_ENTITY },
	{ 0x01D61F10, "_Z13REMOVE_ENTITYP7edict_s", (size_t)&REMOVE_ENTITY },

	{ 0x01D62540, "_Z12CONSOLE_ECHOPcz", (size_t)&CONSOLE_ECHO_ },
	{ 0x01D61F30, "_Z15loopPerformancev", (size_t)&loopPerformance },
	{ 0x01D62570, "GetEntityAPI", (size_t)&GetEntityAPI },
	//{ 0x01D62670, "_Z13GetEntityAPI2P13DLL_FUNCTIONSPi", (size_t)&GetEntityAPI2 },	// NOXREF
	{ 0x01D626B0, "GetNewDLLFunctions", (size_t)&GetNewDLLFunctions },

	//{ 0x01D62B20, "_Z16FindGlobalEntityjj", (size_t)&FindGlobalEntity },	// NOXREF
	{ 0x01D63700, "_ZL21SetObjectCollisionBoxP9entvars_s", (size_t)&SetObjectCollisionBox },
	{ 0x01D63BE0, "_Z20OnFreeEntPrivateDataP7edict_s", (size_t)&OnFreeEntPrivateData },
	{ 0x01D80630, "_Z11GameDLLInitv", (size_t)&GameDLLInit },
	//{ 0x01DB6BD0, "_Z12GetSkillCvarPc", (size_t)&GetSkillCvar },		//NOXREF
	{ 0x01D626F0, "_Z13DispatchSpawnP7edict_s", (size_t)&DispatchSpawn },
	{ 0x01D629D0, "_Z13DispatchThinkP7edict_s", (size_t)&DispatchThink },
	{ 0x01D62990, "_Z11DispatchUseP7edict_sS0_", (size_t)&DispatchUse },
	{ 0x01D62930, "_Z13DispatchTouchP7edict_sS0_", (size_t)&DispatchTouch },
	{ 0x01D62A20, "_Z15DispatchBlockedP7edict_sS0_", (size_t)&DispatchBlocked },
	{ 0x01D628F0, "_Z16DispatchKeyValueP7edict_sP14KeyValueData_s", (size_t)&DispatchKeyValue },
	{ 0x01D62A50, "_Z12DispatchSaveP7edict_sP13saverestore_s", (size_t)&DispatchSave },
	{ 0x01D62BD0, "_Z15DispatchRestoreP7edict_sP13saverestore_si", (size_t)&DispatchRestore },
	{ 0x01D62FF0, "_Z25DispatchObjectCollsionBoxP7edict_s", (size_t)&DispatchObjectCollsionBox },
	{ 0x01D63020, "_Z15SaveWriteFieldsP13saverestore_sPKcPvP15TYPEDESCRIPTIONi", (size_t)&SaveWriteFields },
	{ 0x01D63060, "_Z14SaveReadFieldsP13saverestore_sPKcPvP15TYPEDESCRIPTIONi", (size_t)&SaveReadFields },
	//virtual func
//CBaseEntity
	//{ 0x01D18590, "_ZN11CBaseEntity5SpawnEv", mfunc_ptr_cast(&CBaseEntity::Spawn_) },		// pure
	//{ 0x01D185A0, "_ZN11CBaseEntity8PrecacheEv", mfunc_ptr_cast(&CBaseEntity::Precache) },
	//{ 0x01D01B90, "_ZN11CBaseEntity7RestartEv", mfunc_ptr_cast(&CBaseEntity::Restart) },
	////{ 0x01D185B0, "_ZN11CBaseEntity8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseEntity::KeyValue_) },
	{ 0x01D635D0, "_ZN11CBaseEntity4SaveER5CSave", mfunc_ptr_cast(&CBaseEntity::Save_) },
	{ 0x01D63610, "_ZN11CBaseEntity7RestoreER8CRestore", mfunc_ptr_cast(&CBaseEntity::Restore_) },
	//{ 0x01D01BA0, "_ZN11CBaseEntity10ObjectCapsEv", mfunc_ptr_cast(&CBaseEntity::ObjectCaps) },
	//{ 0x01D01BB0, "_ZN11CBaseEntity8ActivateEv", mfunc_ptr_cast(&CBaseEntity::Activate) },
	//{ 0x01D638B0, "_ZN11CBaseEntity21SetObjectCollisionBoxEv", mfunc_ptr_cast(&CBaseEntity::SetObjectCollisionBox) },
	//{ 0x01D01BC0, "_ZN11CBaseEntity8ClassifyEv", mfunc_ptr_cast(&CBaseEntity::Classify) },
	{ 0x01D01BD0, "_ZN11CBaseEntity11DeathNoticeEP9entvars_s", mfunc_ptr_cast(&CBaseEntity::DeathNotice_) },
	{ 0x01D719D0, "_ZN11CBaseEntity11TraceAttackEP9entvars_sf6VectorP11TraceResulti", mfunc_ptr_cast(&CBaseEntity::TraceAttack_) },
	{ 0x01D63210, "_ZN11CBaseEntity10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBaseEntity::TakeDamage_) },
	{ 0x01D63190, "_ZN11CBaseEntity10TakeHealthEfi", mfunc_ptr_cast(&CBaseEntity::TakeHealth_) },
	{ 0x01D63550, "_ZN11CBaseEntity6KilledEP9entvars_si", mfunc_ptr_cast(&CBaseEntity::Killed_) },
	//{ 0x01D01BE0, "_ZN11CBaseEntity10BloodColorEv", mfunc_ptr_cast(&CBaseEntity::BloodColor) },
	{ 0x01D72EE0, "_ZN11CBaseEntity10TraceBleedEf6VectorP11TraceResulti", mfunc_ptr_cast(&CBaseEntity::TraceBleed_) },
	//{ 0x01D01BF0, "_ZN11CBaseEntity11IsTriggeredEPS_", mfunc_ptr_cast(&CBaseEntity::IsTriggered) },
	//{ 0x01D01C00, "_ZN11CBaseEntity16MyMonsterPointerEv", mfunc_ptr_cast(&CBaseEntity::MyMonsterPointer) },
	//{ 0x01D01C10, "_ZN11CBaseEntity21MySquadMonsterPointerEv", mfunc_ptr_cast(&CBaseEntity::MySquadMonsterPointer) },
	{ 0x01D01C20, "_ZN11CBaseEntity14GetToggleStateEv", mfunc_ptr_cast(&CBaseEntity::GetToggleState_) },
	//{ 0x01D01C30, "_ZN11CBaseEntity9AddPointsEii", mfunc_ptr_cast(&CBaseEntity::AddPoints) },
	//{ 0x01D01C40, "_ZN11CBaseEntity15AddPointsToTeamEii", mfunc_ptr_cast(&CBaseEntity::AddPointsToTeam) },
	//{ 0x01D01C50, "_ZN11CBaseEntity13AddPlayerItemEP15CBasePlayerItem", mfunc_ptr_cast(&CBaseEntity::AddPlayerItem) },
	//{ 0x01D01C60, "_ZN11CBaseEntity16RemovePlayerItemEP15CBasePlayerItem", mfunc_ptr_cast(&CBaseEntity::RemovePlayerItem) },
	//{ 0x01D01C70, "_ZN11CBaseEntity8GiveAmmoEiPci", mfunc_ptr_cast(&CBaseEntity::GiveAmmo) },
	{ 0x01D01C80, "_ZN11CBaseEntity8GetDelayEv", mfunc_ptr_cast(&CBaseEntity::GetDelay_) },
	////{ 0x01D01C90, "_ZN11CBaseEntity8IsMovingEv", mfunc_ptr_cast(&CBaseEntity::IsMoving) },
	//{ 0x01D01CE0, "_ZN11CBaseEntity13OverrideResetEv", mfunc_ptr_cast(&CBaseEntity::OverrideReset) },
	{ 0x01D63AF0, "_ZN11CBaseEntity11DamageDecalEi", mfunc_ptr_cast(&CBaseEntity::DamageDecal_) },
	//{ 0x01D01CF0, "_ZN11CBaseEntity14SetToggleStateEi", mfunc_ptr_cast(&CBaseEntity::SetToggleState) },
	//{ 0x01D01D00, "_ZN11CBaseEntity13StartSneakingEv", mfunc_ptr_cast(&CBaseEntity::StartSneaking) },
	//{ 0x01D01D10, "_ZN11CBaseEntity12StopSneakingEv", mfunc_ptr_cast(&CBaseEntity::StopSneaking) },
	//{ 0x01D01D20, "_ZN11CBaseEntity10OnControlsEP9entvars_s", mfunc_ptr_cast(&CBaseEntity::OnControls) },
	////{ 0x01D01D30, "_ZN11CBaseEntity10IsSneakingEv", mfunc_ptr_cast(&CBaseEntity::IsSneaking) },
	//{ 0x01D01D40, "_ZN11CBaseEntity7IsAliveEv", mfunc_ptr_cast(&CBaseEntity::IsAlive) },
	//{ 0x01D01D70, "_ZN11CBaseEntity10IsBSPModelEv", mfunc_ptr_cast(&CBaseEntity::IsBSPModel) },
	//{ 0x01D01D90, "_ZN11CBaseEntity12ReflectGaussEv", mfunc_ptr_cast(&CBaseEntity::ReflectGauss) },
	//{ 0x01D01DC0, "_ZN11CBaseEntity9HasTargetEj", mfunc_ptr_cast(&CBaseEntity::HasTarget) },
	{ 0x01D639C0, "_ZN11CBaseEntity9IsInWorldEv", mfunc_ptr_cast(&CBaseEntity::IsInWorld_) },
	//{ 0x01D01E30, "_ZN11CBaseEntity8IsPlayerEv", mfunc_ptr_cast(&CBaseEntity::IsPlayer) },
	//{ 0x01D01E40, "_ZN11CBaseEntity11IsNetClientEv", mfunc_ptr_cast(&CBaseEntity::IsNetClient_) },
	//{ 0x01D01E50, "_ZN11CBaseEntity6TeamIDEv", mfunc_ptr_cast(&CBaseEntity::TeamID) },
	{ 0x01D63580, "_ZN11CBaseEntity13GetNextTargetEv", mfunc_ptr_cast(&CBaseEntity::GetNextTarget_) },
	//{ 0x01D01E60, "_ZN11CBaseEntity5ThinkEv", mfunc_ptr_cast(&CBaseEntity::Think) },
	//{ 0x01D01E70, "_ZN11CBaseEntity5TouchEPS_", mfunc_ptr_cast(&CBaseEntity::Touch) },
	//{ 0x01D01E80, "_ZN11CBaseEntity3UseEPS_S0_8USE_TYPEf", mfunc_ptr_cast(&CBaseEntity::Use) },
	//{ 0x01D01EA0, "_ZN11CBaseEntity7BlockedEPS_", mfunc_ptr_cast(&CBaseEntity::Blocked) },
	//{ 0x01D18B00, "_ZN11CBaseEntity7RespawnEv", mfunc_ptr_cast(&CBaseEntity::Respawn) },
	//{ 0x01D01EC0, "_ZN11CBaseEntity11UpdateOwnerEv", mfunc_ptr_cast(&CBaseEntity::UpdateOwner) },
	//{ 0x01D01ED0, "_ZN11CBaseEntity12FBecomeProneEv", mfunc_ptr_cast(&CBaseEntity::FBecomeProne) },
	//{ 0x01D01EE0, "_ZN11CBaseEntity6CenterEv", mfunc_ptr_cast(&CBaseEntity::Center) },
	//{ 0x01D01F40, "_ZN11CBaseEntity11EyePositionEv", mfunc_ptr_cast(&CBaseEntity::EyePosition) },
	//{ 0x01D01F70, "_ZN11CBaseEntity11EarPositionEv", mfunc_ptr_cast(&CBaseEntity::EarPosition) },
	{ 0x01D01FA0, "_ZN11CBaseEntity10BodyTargetERK6Vector", mfunc_ptr_cast(&CBaseEntity::BodyTarget_) },
	////{ 0x01D01FC0, "_ZN11CBaseEntity12IlluminationEv", mfunc_ptr_cast(&CBaseEntity::Illumination) },
	//{ 0x01D71950, "_ZN11CBaseEntity8FVisibleERK6Vector", mfunc_ptr_cast<FVISIBLE_VECTOR>(&CBaseEntity::FVisible_) },
	//{ 0x01D71840, "_ZN11CBaseEntity8FVisibleEPS_", mfunc_ptr_cast<FVISIBLE_ENTITY>(&CBaseEntity::FVisible_) },
	//non-virtual func
	//{ 0x01DA7FD0, "", mfunc_ptr_cast<CBASE_ISTANCE_EDICT>(&CBaseEntity::Instance) },
	{ 0x01DBAF90, "_ZN11CBaseEntity14UpdateOnRemoveEv", mfunc_ptr_cast(&CBaseEntity::UpdateOnRemove) },
	{ 0x01DBAFF0, "_ZN11CBaseEntity10SUB_RemoveEv", mfunc_ptr_cast(&CBaseEntity::SUB_Remove) },
	{ 0x01DBB0A0, "_ZN11CBaseEntity13SUB_DoNothingEv", mfunc_ptr_cast(&CBaseEntity::SUB_DoNothing) },
	{ 0x01D6FB10, "_ZN11CBaseEntity16SUB_StartFadeOutEv", mfunc_ptr_cast(&CBaseEntity::SUB_StartFadeOut) },
	{ 0x01D6FB80, "_ZN11CBaseEntity11SUB_FadeOutEv", mfunc_ptr_cast(&CBaseEntity::SUB_FadeOut) },
	{ 0x01D01EB0, "_ZN11CBaseEntity17SUB_CallUseToggleEv", mfunc_ptr_cast(&CBaseEntity::SUB_CallUseToggle) },
	{ 0x01D63AC0, "_ZN11CBaseEntity12ShouldToggleE8USE_TYPEi", mfunc_ptr_cast(&CBaseEntity::ShouldToggle) },
	//{ 0x01D71BC0, "_ZN11CBaseEntity11FireBulletsEj6VectorS0_S0_fiiiP9entvars_s", mfunc_ptr_cast(&CBaseEntity::FireBullets) },
	//C!@{ 0x01D72480, "_ZN11CBaseEntity12FireBullets3E6VectorS0_ffiiifP9entvars_sbi", mfunc_ptr_cast(&CBaseEntity::FireBullets3) },
	{ 0x01DBB190, "_ZN11CBaseEntity14SUB_UseTargetsEPS_8USE_TYPEf", mfunc_ptr_cast(&CBaseEntity::SUB_UseTargets) },		
	{ 0x01DBB260, "_Z11FireTargetsPKcP11CBaseEntityS2_8USE_TYPEf", (size_t)&FireTargets },
	{ 0x01D638C0, "_ZN11CBaseEntity10IntersectsEPS_", mfunc_ptr_cast(&CBaseEntity::Intersects) },
	//{ 0x01D63950, "_ZN11CBaseEntity11MakeDormantEv", mfunc_ptr_cast(&CBaseEntity::MakeDormant) }, // NOXREF
	{ 0x01D639B0, "_ZN11CBaseEntity9IsDormantEv", mfunc_ptr_cast(&CBaseEntity::IsDormant) },
	//{ 0x0, "_ZN11CBaseEntity16IsLockedByMasterEv", mfunc_ptr_cast(&CBaseEntity::IsLockedByMaster) }, // NOXREF
	{ 0x01D63B20, "_ZN11CBaseEntity6CreateEPcRK6VectorS3_P7edict_s", mfunc_ptr_cast(&CBaseEntity::Create) },
//CPointEntity
	//{ 0x01DBACC0, "_ZN12CPointEntity5SpawnEv", mfunc_ptr_cast(&CPointEntity::Spawn) },
	//{ 0x01D60CB0, "_ZN12CPointEntity10ObjectCapsEv", mfunc_ptr_cast(&CPointEntity::ObjectCaps) },
//CBaseDelay
	//virtual func
	{ 0x01DBB110, "_ZN10CBaseDelay8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseDelay::KeyValue_) },
	{ 0x01DBB0B0, "_ZN10CBaseDelay4SaveER5CSave", mfunc_ptr_cast(&CBaseDelay::Save_) },
	{ 0x01DBB0E0, "_ZN10CBaseDelay7RestoreER8CRestore", mfunc_ptr_cast(&CBaseDelay::Restore_) },
	//non-virtual func
	{ 0x01DBB620, "_Z10SetMovedirP9entvars_s", (size_t)&SetMovedir },
	{ 0x01DBB360, "_ZN10CBaseDelay14SUB_UseTargetsEP11CBaseEntity8USE_TYPEf", mfunc_ptr_cast(&CBaseDelay::SUB_UseTargets) },
	{ 0x01DBB730, "_ZN10CBaseDelay10DelayThinkEv", mfunc_ptr_cast(&CBaseDelay::DelayThink) },
//CBaseAnimating
	//virtual func
	{ 0x01D59E70, "_ZN14CBaseAnimating4SaveER5CSave", mfunc_ptr_cast(&CBaseAnimating::Save_) },
	{ 0x01D59EA0, "_ZN14CBaseAnimating7RestoreER8CRestore", mfunc_ptr_cast(&CBaseAnimating::Restore_) },
	//{ 0x01D01FE0, "_ZN14CBaseAnimating15HandleAnimEventEP14MonsterEvent_t", mfunc_ptr_cast(&CBaseAnimating::HandleAnimEvent_) },	// PURE
	//non-virtual func
	{ 0x01D59ED0, "_ZN14CBaseAnimating18StudioFrameAdvanceEf", mfunc_ptr_cast(&CBaseAnimating::StudioFrameAdvance) },
	//{ 0x01D5A130, "_ZN14CBaseAnimating16GetSequenceFlagsEv", mfunc_ptr_cast(&CBaseAnimating::GetSequenceFlags) },	// NOXREF
	{ 0x01D5A010, "_ZN14CBaseAnimating14LookupActivityEi", mfunc_ptr_cast(&CBaseAnimating::LookupActivity) },
	{ 0x01D5A040, "_ZN14CBaseAnimating22LookupActivityHeaviestEi", mfunc_ptr_cast(&CBaseAnimating::LookupActivityHeaviest) },
	{ 0x01D5A070, "_ZN14CBaseAnimating14LookupSequenceEPKc", mfunc_ptr_cast(&CBaseAnimating::LookupSequence) },
	{ 0x01D5A0A0, "_ZN14CBaseAnimating17ResetSequenceInfoEv", mfunc_ptr_cast(&CBaseAnimating::ResetSequenceInfo) },
	{ 0x01D5A160, "_ZN14CBaseAnimating18DispatchAnimEventsEf", mfunc_ptr_cast(&CBaseAnimating::DispatchAnimEvents) },
	{ 0x01D5A280, "_ZN14CBaseAnimating17SetBoneControllerEif", mfunc_ptr_cast(&CBaseAnimating::SetBoneController) },
	{ 0x01D5A2B0, "_ZN14CBaseAnimating19InitBoneControllersEv", mfunc_ptr_cast(&CBaseAnimating::InitBoneControllers) },
	//{ 0x01D5A310, "_ZN14CBaseAnimating11SetBlendingEif", mfunc_ptr_cast(&CBaseAnimating::SetBlending) },			// NOXREF
	//{ 0x01D5A340, "_ZN14CBaseAnimating15GetBonePositionEiR6VectorS1_", mfunc_ptr_cast(&CBaseAnimating::GetBonePosition) },	// NOXREF
	//{ 0x01D5A370, "_ZN14CBaseAnimating13GetAttachmentEiR6VectorS1_", mfunc_ptr_cast(&CBaseAnimating::GetAttachment) },	// NOXREF
	//{ 0x01D5A3A0, "_ZN14CBaseAnimating14FindTransitionEiiPi", mfunc_ptr_cast(&CBaseAnimating::FindTransition) },	// NOXREF
	//{ 0x01D5A400, "_ZN14CBaseAnimating15GetAutomovementER6VectorS1_f", mfunc_ptr_cast(&CBaseAnimating::GetAutomovement) },	// NOXREF
	//{ 0x01D5A410, "_ZN14CBaseAnimating12SetBodygroupEii", mfunc_ptr_cast(&CBaseAnimating::SetBodygroup) },	// NOXREF
	//{ 0x01D5A440, "_ZN14CBaseAnimating12GetBodygroupEi", mfunc_ptr_cast(&CBaseAnimating::GetBodygroup) },	// NOXREF
	//{ 0x01D5A470, "_ZN14CBaseAnimating11ExtractBboxEiPfS0_", mfunc_ptr_cast(&CBaseAnimating::ExtractBbox) },	// NOXREF
	{ 0x01D5A4A0, "_ZN14CBaseAnimating14SetSequenceBoxEv", mfunc_ptr_cast(&CBaseAnimating::SetSequenceBox) },
//CBaseToggle
	//virtual func
	{ 0x01DBB7D0, "_ZN11CBaseToggle8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseToggle::KeyValue_) },
	{ 0x01DBB770, "_ZN11CBaseToggle4SaveER5CSave", mfunc_ptr_cast(&CBaseToggle::Save_) },
	{ 0x01DBB7A0, "_ZN11CBaseToggle7RestoreER8CRestore", mfunc_ptr_cast(&CBaseToggle::Restore_) },
	//{ 0x01D20F20, "_ZN11CBaseToggle14GetToggleStateEv", mfunc_ptr_cast(&CBaseToggle::GetToggleState_) },
	//{ 0x01D20F30, "_ZN11CBaseToggle8GetDelayEv", mfunc_ptr_cast(&CBaseToggle::GetDelay_) },
	//non-virtual func
	//{ 0x0, "_ZN11CBaseToggle10LinearMoveE6Vectorf", mfunc_ptr_cast(&CBaseToggle::LinearMove) },
	//{ 0x0, "_ZN11CBaseToggle14LinearMoveDoneEv", mfunc_ptr_cast(&CBaseToggle::LinearMoveDone) },
	//{ 0x0, "_ZN11CBaseToggle11AngularMoveE6Vectorf", mfunc_ptr_cast(&CBaseToggle::AngularMove) },
	//{ 0x0, "_ZN11CBaseToggle15AngularMoveDoneEv", mfunc_ptr_cast(&CBaseToggle::AngularMoveDone) },
	//{ 0x0, "_ZN11CBaseToggle16IsLockedByMasterEv", mfunc_ptr_cast(&CBaseToggle::IsLockedByMaster) },
	//{ 0x01DBBCA0, "_ZN11CBaseToggle9AxisValueEiRK6Vector", mfunc_ptr_cast(&CBaseToggle::AxisValue) },
	//{ 0x0, "_ZN11CBaseToggle7AxisDirEP9entvars_s", mfunc_ptr_cast(&CBaseToggle::AxisDir) },
	//{ 0x01DBBD60, "_ZN11CBaseToggle9AxisDeltaEiRK6VectorS2_", mfunc_ptr_cast(&CBaseToggle::AxisDelta) },
	//{ 0x01DBBDA0, "_Z13FEntIsVisibleP9entvars_sS0_", (size_t)&FEntIsVisible },		// NOXREF
//CWorld
	//virtual func
	{ 0x01DD1EE0, "_ZN6CWorld5SpawnEv", mfunc_ptr_cast(&CWorld::Spawn_) },
	{ 0x01DD2000, "_ZN6CWorld8PrecacheEv", mfunc_ptr_cast(&CWorld::Precache_) },
	{ 0x01DD2440, "_ZN6CWorld8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CWorld::KeyValue_) },

//CClientFog
	//virtual func
	//{ 0x0, "_ZN10CClientFog5SpawnEv", mfunc_ptr_cast(&CClientFog::Spawn) },
	//{ 0x0, "_ZN10CClientFog8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CClientFog::KeyValue) },

#endif // Cbase_Region

#ifndef Spectator_Region

	//virtual func
	//{ 0x01DBAC90, "_ZN14CBaseSpectator5SpawnEv", mfunc_ptr_cast(&CBaseSpectator::Spawn_) },	// NOXREF
	//non-virtual func
	//{ 0x01DBAB20, "_ZN14CBaseSpectator16SpectatorConnectEv", mfunc_ptr_cast(&CBaseSpectator::SpectatorConnect) },	// NOXREF
	//{ 0x01DBAB50, "_ZN14CBaseSpectator19SpectatorDisconnectEv", mfunc_ptr_cast(&CBaseSpectator::SpectatorDisconnect) },	// NOXREF
	//{ 0x01DBAC40, "_ZN14CBaseSpectator14SpectatorThinkEv", mfunc_ptr_cast(&CBaseSpectator::SpectatorThink) },	// NOXREF
	{ 0x01DBAB60, "_ZN14CBaseSpectator23SpectatorImpulseCommandEv", mfunc_ptr_cast(&CBaseSpectator::SpectatorImpulseCommand) },

#endif // Spectator_Region

#ifndef BaseMonster_Region

	//virtual func
	{ 0x01D8AD30, "_ZN12CBaseMonster8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseMonster::KeyValue_) },
	{ 0x01D71AA0, "_ZN12CBaseMonster11TraceAttackEP9entvars_sf6VectorP11TraceResulti", mfunc_ptr_cast(&CBaseMonster::TraceAttack_) },
	{ 0x01D70180, "_ZN12CBaseMonster10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBaseMonster::TakeDamage_) },
	{ 0x01D70130, "_ZN12CBaseMonster10TakeHealthEfi", mfunc_ptr_cast(&CBaseMonster::TakeHealth_) },
	{ 0x01D6F9D0, "_ZN12CBaseMonster6KilledEP9entvars_si", mfunc_ptr_cast(&CBaseMonster::Killed_) },
	{ 0x01D20F50, "_ZN12CBaseMonster10BloodColorEv", mfunc_ptr_cast(&CBaseMonster::BloodColor_) },
	{ 0x01D24CF0, "_ZN12CBaseMonster7IsAliveEv", mfunc_ptr_cast(&CBaseMonster::IsAlive_) },
	{ 0x01D8ABF0, "_ZN12CBaseMonster9ChangeYawEi", mfunc_ptr_cast(&CBaseMonster::ChangeYaw_) },
	{ 0x01D6F360, "_ZN12CBaseMonster12HasHumanGibsEv", mfunc_ptr_cast(&CBaseMonster::HasHumanGibs_) },
	{ 0x01D6F390, "_ZN12CBaseMonster12HasAlienGibsEv", mfunc_ptr_cast(&CBaseMonster::HasAlienGibs_) },
	{ 0x01D6F3C0, "_ZN12CBaseMonster11FadeMonsterEv", mfunc_ptr_cast(&CBaseMonster::FadeMonster_) },
	{ 0x01D6F4B0, "_ZN12CBaseMonster10GibMonsterEv", mfunc_ptr_cast(&CBaseMonster::GibMonster_) },
	//{ 0x01D6F5A0, "_ZN12CBaseMonster16GetDeathActivityEv", mfunc_ptr_cast(&CBaseMonster::GetDeathActivity) },
	{ 0x01D6F880, "_ZN12CBaseMonster10BecomeDeadEv", mfunc_ptr_cast(&CBaseMonster::BecomeDead_) },
	{ 0x01D8AD10, "_ZN12CBaseMonster17ShouldFadeOnDeathEv", mfunc_ptr_cast(&CBaseMonster::ShouldFadeOnDeath_) },
	//{ 0x01D8AD40, "_ZN12CBaseMonster13IRelationshipEP11CBaseEntity", mfunc_ptr_cast(&CBaseMonster::IRelationship) },
	//{ 0x01D20F40, "_ZN12CBaseMonster9PainSoundEv", mfunc_ptr_cast(&CBaseMonster::PainSound_) },
	//{ 0x01D24AD0, "_ZN12CBaseMonster13ResetMaxSpeedEv", mfunc_ptr_cast(&CBaseMonster::ResetMaxSpeed) },
	//{ 0x01D8ABE0, "_ZN12CBaseMonster13ReportAIStateEv", mfunc_ptr_cast(&CBaseMonster::ReportAIState) },
	{ 0x01D8AC60, "_ZN12CBaseMonster15MonsterInitDeadEv", mfunc_ptr_cast(&CBaseMonster::MonsterInitDead_) },
	//{ 0x01D8AD70, "_ZN12CBaseMonster4LookEi", mfunc_ptr_cast(&CBaseMonster::Look) },
	//{ 0x01D8AF10, "_ZN12CBaseMonster16BestVisibleEnemyEv", mfunc_ptr_cast(&CBaseMonster::BestVisibleEnemy) },
	//{ 0x01D716D0, "_ZN12CBaseMonster11FInViewConeEP11CBaseEntity", mfunc_ptr_cast<FINVIEWCONE_ENTITY>(&CBaseMonster::FInViewCone_) },
	//{ 0x01D71790, "_ZN12CBaseMonster11FInViewConeEP6Vector", mfunc_ptr_cast<FINVIEWCONE_VECTOR>(&CBaseMonster::FInViewCone_) },
	//non-virtual func
	//{ 0x01D8AC00, "_ZN12CBaseMonster12MakeIdealYawE6Vector", mfunc_ptr_cast(&CBaseMonster::MakeIdealYaw) },	// PURE
	//{ 0x01D6F7F0, "_ZN12CBaseMonster22GetSmallFlinchActivityEv", mfunc_ptr_cast(&CBaseMonster::GetSmallFlinchActivity) },	// NOXREF
	//{ 0x01D6F8C0, "_ZN12CBaseMonster16ShouldGibMonsterEi", mfunc_ptr_cast(&CBaseMonster::ShouldGibMonster) },	// NOXREF
	{ 0x01D6F8F0, "_ZN12CBaseMonster14CallGibMonsterEv", mfunc_ptr_cast(&CBaseMonster::CallGibMonster) },
	{ 0x01D8AD20, "_ZN12CBaseMonster15FCheckAITriggerEv", mfunc_ptr_cast(&CBaseMonster::FCheckAITrigger) },
	{ 0x01D705B0, "_ZN12CBaseMonster14DeadTakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBaseMonster::DeadTakeDamage) },
	//{ 0x01D707C0, "_ZN12CBaseMonster11DamageForceEf", mfunc_ptr_cast(&CBaseMonster::DamageForce) },	// NOXREF
	{ 0x01D71470, "_ZN12CBaseMonster12RadiusDamageEP9entvars_sS1_fii", mfunc_ptr_cast<RADIUSDAMAGE_ENTVARS>(&CBaseMonster::RadiusDamage) },
	//{ 0x01D71520, "_ZN12CBaseMonster12RadiusDamageE6VectorP9entvars_sS2_fii", mfunc_ptr_cast<RADIUSDAMAGE_VECTOR>(&CBaseMonster::RadiusDamage) },	// NOXREF
	//{ 0x0, "_ZN12CBaseMonster13RadiusDamage2E6VectorP9entvars_sS2_fii", mfunc_ptr_cast(&CBaseMonster::RadiusDamage2) },	// NOXREF
	//{ 0x01D8AC10, "_ZN12CBaseMonster15CorpseFallThinkEv", mfunc_ptr_cast(&CBaseMonster::CorpseFallThink) },
	//{ 0x01D715D0, "_ZN12CBaseMonster20CheckTraceHullAttackEfii", mfunc_ptr_cast(&CBaseMonster::CheckTraceHullAttack) },	// NOXREF
	//{ 0x01D730E0, "_ZN12CBaseMonster20MakeDamageBloodDecalEifP11TraceResultRK6Vector", mfunc_ptr_cast(&CBaseMonster::MakeDamageBloodDecal) },	// NOXREF
	{ 0x01D73240, "_ZN12CBaseMonster10BloodSplatER6VectorS1_ii", mfunc_ptr_cast(&CBaseMonster::BloodSplat) },
	{ 0x01D70800, "_Z11RadiusFlash6VectorP9entvars_sS1_fii", (size_t)&RadiusFlash },
	//{ 0x0, "_ZL24GetAmountOfPlayerVisible6VectorP11CBaseEntity_constprop_21", (size_t)&GetAmountOfPlayerVisible },	// NOXREF
	{ 0x01D70CA0, "_Z12RadiusDamage6VectorP9entvars_sS1_ffii", (size_t)&RadiusDamage },
	{ 0x01D711B0, "_Z13RadiusDamage26VectorP9entvars_sS1_ffii", (size_t)&RadiusDamage2 },
	//{ 0x01D72430, "_Z4vstrPf", (size_t)&vstr },	// NOXREF

#endif // BaseMonster_Region

#ifndef Player_Region
	
//CBasePlayer
	//virtual func
	{ 0x01DA5200, "_ZN11CBasePlayer5SpawnEv", mfunc_ptr_cast(&CBasePlayer::Spawn_) },
	{ 0x01DA5E40, "_ZN11CBasePlayer8PrecacheEv", mfunc_ptr_cast(&CBasePlayer::Precache_) },
	{ 0x01DA5EE0, "_ZN11CBasePlayer4SaveER5CSave", mfunc_ptr_cast(&CBasePlayer::Save_) },
	{ 0x01DA6080, "_ZN11CBasePlayer7RestoreER8CRestore", mfunc_ptr_cast(&CBasePlayer::Restore_) },
	{ 0x01D210A0, "_ZN11CBasePlayer10ObjectCapsEv", mfunc_ptr_cast(&CBasePlayer::ObjectCaps_) },
	{ 0x01DA3550, "_ZN11CBasePlayer8ClassifyEv", mfunc_ptr_cast(&CBasePlayer::Classify_) },
	{ 0x01D9BE00, "_ZN11CBasePlayer11TraceAttackEP9entvars_sf6VectorP11TraceResulti", mfunc_ptr_cast(&CBasePlayer::TraceAttack_) },
	{ 0x01D9C4C0, "_ZN11CBasePlayer10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBasePlayer::TakeDamage_) },
	{ 0x01D9BD70, "_ZN11CBasePlayer10TakeHealthEfi", mfunc_ptr_cast(&CBasePlayer::TakeHealth_) },
	{ 0x01D9E550, "_ZN11CBasePlayer6KilledEP9entvars_si", mfunc_ptr_cast(&CBasePlayer::Killed_) },
	{ 0x01DA3560, "_ZN11CBasePlayer9AddPointsEii", mfunc_ptr_cast(&CBasePlayer::AddPoints_) },
	{ 0x01DA3640, "_ZN11CBasePlayer15AddPointsToTeamEii", mfunc_ptr_cast(&CBasePlayer::AddPointsToTeam_) },
	{ 0x01DA86C0, "_ZN11CBasePlayer13AddPlayerItemEP15CBasePlayerItem", mfunc_ptr_cast(&CBasePlayer::AddPlayerItem_) },
	{ 0x01DA8960, "_ZN11CBasePlayer16RemovePlayerItemEP15CBasePlayerItem", mfunc_ptr_cast(&CBasePlayer::RemovePlayerItem_) },
	{ 0x01DA8AA0, "_ZN11CBasePlayer8GiveAmmoEiPci", mfunc_ptr_cast(&CBasePlayer::GiveAmmo_) },
	{ 0x01D20FD0, "_ZN11CBasePlayer13StartSneakingEv", mfunc_ptr_cast(&CBasePlayer::StartSneaking_) },
	{ 0x01D20FF0, "_ZN11CBasePlayer12StopSneakingEv", mfunc_ptr_cast(&CBasePlayer::StopSneaking_) },
	{ 0x01D21010, "_ZN11CBasePlayer10IsSneakingEv", mfunc_ptr_cast(&CBasePlayer::IsSneaking_) },
	{ 0x01D21030, "_ZN11CBasePlayer7IsAliveEv", mfunc_ptr_cast(&CBasePlayer::IsAlive_) },
	{ 0x01D21070, "_ZN11CBasePlayer8IsPlayerEv", mfunc_ptr_cast(&CBasePlayer::IsPlayer_) },
	{ 0x01D21090, "_ZN11CBasePlayer11IsNetClientEv", mfunc_ptr_cast(&CBasePlayer::IsNetClient_) },
	{ 0x01DA6950, "_ZN11CBasePlayer6TeamIDEv", mfunc_ptr_cast(&CBasePlayer::TeamID_) },
	{ 0x01DA9BF0, "_ZN11CBasePlayer12FBecomeProneEv", mfunc_ptr_cast(&CBasePlayer::FBecomeProne_) },
	{ 0x01D20F60, "_ZN11CBasePlayer10BodyTargetERK6Vector", mfunc_ptr_cast(&CBasePlayer::BodyTarget_) },
	{ 0x01DA9C50, "_ZN11CBasePlayer12IlluminationEv", mfunc_ptr_cast(&CBasePlayer::Illumination_) },
	{ 0x01D21060, "_ZN11CBasePlayer17ShouldFadeOnDeathEv", mfunc_ptr_cast(&CBasePlayer::ShouldFadeOnDeath_) },
	{ 0x01DA9CB0, "_ZN11CBasePlayer13ResetMaxSpeedEv", mfunc_ptr_cast(&CBasePlayer::ResetMaxSpeed_) },
	{ 0x01DA3310, "_ZN11CBasePlayer4JumpEv", mfunc_ptr_cast(&CBasePlayer::Jump_) },
	{ 0x01DA3530, "_ZN11CBasePlayer4DuckEv", mfunc_ptr_cast(&CBasePlayer::Duck_) },
	{ 0x01DA3850, "_ZN11CBasePlayer8PreThinkEv", mfunc_ptr_cast(&CBasePlayer::PreThink_) },
	{ 0x01DA4610, "_ZN11CBasePlayer9PostThinkEv", mfunc_ptr_cast(&CBasePlayer::PostThink_) },
	{ 0x01D9BD80, "_ZN11CBasePlayer14GetGunPositionEv", mfunc_ptr_cast(&CBasePlayer::GetGunPosition_) },
	{ 0x01D25AD0, "_ZN11CBasePlayer5IsBotEv", mfunc_ptr_cast(&CBasePlayer::IsBot_) },
	{ 0x01DA8F90, "_ZN11CBasePlayer16UpdateClientDataEv", mfunc_ptr_cast(&CBasePlayer::UpdateClientData_) },
	{ 0x01DA7020, "_ZN11CBasePlayer15ImpulseCommandsEv", mfunc_ptr_cast(&CBasePlayer::ImpulseCommands_) },
	{ 0x01DA2490, "_ZN11CBasePlayer12RoundRespawnEv", mfunc_ptr_cast(&CBasePlayer::RoundRespawn_) },
	{ 0x01DA9DC0, "_ZN11CBasePlayer16GetAutoaimVectorEf", mfunc_ptr_cast(&CBasePlayer::GetAutoaimVector_) },
	{ 0x01DAA220, "_ZN11CBasePlayer5BlindEfffi", mfunc_ptr_cast(&CBasePlayer::Blind_) },
	{ 0x01D25AE0, "_ZN11CBasePlayer16OnTouchingWeaponEP10CWeaponBox", mfunc_ptr_cast(&CBasePlayer::OnTouchingWeapon_) },	// pure
	//non-virtual func
	{ 0x01DAC8D0, "_ZN11CBasePlayer21SpawnClientSideCorpseEv", mfunc_ptr_cast(&CBasePlayer::SpawnClientSideCorpse) },
	{ 0x01D93750, "_ZN11CBasePlayer23Observer_FindNextPlayerEbPKc", mfunc_ptr_cast(&CBasePlayer::Observer_FindNextPlayer) },
	{ 0x01D936E0, "_ZN11CBasePlayer22Observer_IsValidTargetEib", mfunc_ptr_cast(&CBasePlayer::Observer_IsValidTarget) },
	{ 0x01D93D10, "_ZN11CBasePlayer22Observer_HandleButtonsEv", mfunc_ptr_cast(&CBasePlayer::Observer_HandleButtons) },
	{ 0x01D94280, "_ZN11CBasePlayer16Observer_SetModeEi", mfunc_ptr_cast(&CBasePlayer::Observer_SetMode) },
	{ 0x01D93DF0, "_ZN11CBasePlayer20Observer_CheckTargetEv", mfunc_ptr_cast(&CBasePlayer::Observer_CheckTarget) },
	{ 0x01D93F30, "_ZN11CBasePlayer24Observer_CheckPropertiesEv", mfunc_ptr_cast(&CBasePlayer::Observer_CheckProperties) },
	//{ 0x0, "_ZN11CBasePlayer10IsObserverEv", mfunc_ptr_cast(&CBasePlayer::IsObserver) },	// NOXREF
	//{ 0x0, "_ZN11CBasePlayer7PlantC4Ev", mfunc_ptr_cast(&CBasePlayer::PlantC4) },	// NOXREF
	{ 0x01D9B670, "_ZN11CBasePlayer5RadioEPKcS1_sb", mfunc_ptr_cast(&CBasePlayer::Radio) },
	//{ 0x01D9B4F0, "_ZN11CBasePlayer21GetNextRadioRecipientEPS_", mfunc_ptr_cast(&CBasePlayer::GetNextRadioRecipient) },	// NOXREF
	//{ 0x01D9B9A0, "_ZN11CBasePlayer10SmartRadioEv", mfunc_ptr_cast(&CBasePlayer::SmartRadio) },	// NOXREF
	{ 0x01DA07D0, "_ZN11CBasePlayer11ThrowWeaponEPc", mfunc_ptr_cast(&CBasePlayer::ThrowWeapon) },	// NOXREF
	//{ 0x01DA0DB0, "_ZN11CBasePlayer12ThrowPrimaryEv", mfunc_ptr_cast(&CBasePlayer::ThrowPrimary) },	// NOXREF
	{ 0x01DA1170, "_ZN11CBasePlayer10AddAccountEib", mfunc_ptr_cast(&CBasePlayer::AddAccount) },
	{ 0x01DA1DA0, "_ZN11CBasePlayer9DisappearEv", mfunc_ptr_cast(&CBasePlayer::Disappear) },
	{ 0x01DA15B0, "_ZN11CBasePlayer7MakeVIPEv", mfunc_ptr_cast(&CBasePlayer::MakeVIP) },
	{ 0x01DA36C0, "_ZN11CBasePlayer12CanPlayerBuyEb", mfunc_ptr_cast(&CBasePlayer::CanPlayerBuy) },
	{ 0x01DAB070, "_ZN11CBasePlayer10SwitchTeamEv", mfunc_ptr_cast(&CBasePlayer::SwitchTeam) },
	{ 0x01DAB820, "_ZN11CBasePlayer12TabulateAmmoEv", mfunc_ptr_cast(&CBasePlayer::TabulateAmmo) },
	{ 0x01D9B9B0, "_ZN11CBasePlayer4PainEib", mfunc_ptr_cast(&CBasePlayer::Pain) },
	{ 0x01D9F410, "_ZN11CBasePlayer9IsBombGuyEv", mfunc_ptr_cast(&CBasePlayer::IsBombGuy) },
	{ 0x01DACC30, "_ZNK11CBasePlayer19IsLookingAtPositionEPK6Vectorf", mfunc_ptr_cast(&CBasePlayer::IsLookingAtPosition) },
	{ 0x01DA6310, "_ZN11CBasePlayer5ResetEv", mfunc_ptr_cast(&CBasePlayer::Reset) },
	{ 0x01DA5F10, "_ZN11CBasePlayer23SetScoreboardAttributesEPS_", mfunc_ptr_cast(&CBasePlayer::SetScoreboardAttributes) },
	//{ 0x01DA6070, "_ZN11CBasePlayer10RenewItemsEv", mfunc_ptr_cast(&CBasePlayer::RenewItems) },	// NOXREF
	{ 0x01D9D630, "_ZN11CBasePlayer19PackDeadPlayerItemsEv", mfunc_ptr_cast(&CBasePlayer::PackDeadPlayerItems) },
	{ 0x01D9DAD0, "_ZN11CBasePlayer16GiveDefaultItemsEv", mfunc_ptr_cast(&CBasePlayer::GiveDefaultItems) },
	{ 0x01D9DD60, "_ZN11CBasePlayer14RemoveAllItemsEi", mfunc_ptr_cast(&CBasePlayer::RemoveAllItems) },
	{ 0x01D9E020, "_ZN11CBasePlayer11SetBombIconEi", mfunc_ptr_cast(&CBasePlayer::SetBombIcon) },
	{ 0x01D9E190, "_ZN11CBasePlayer18SetProgressBarTimeEi", mfunc_ptr_cast(&CBasePlayer::SetProgressBarTime) },
	{ 0x01D9E320, "_ZN11CBasePlayer19SetProgressBarTime2Eif", mfunc_ptr_cast(&CBasePlayer::SetProgressBarTime2) },
	//{ 0x01D93690, "_Z14GetForceCamerav", (size_t)&GetForceCamera },		// NOXREF
	{ 0x01D93A00, "_ZL19UpdateClientEffectsP11CBasePlayeri", (size_t)&UpdateClientEffects },

	//{ 0x0, "", (size_t)&OLD_CheckBuyZone },	// NOXREF
	//{ 0x0, "", (size_t)&OLD_CheckBombTarget },	// NOXREF
	//{ 0x0, "", (size_t)&OLD_CheckRescueZone },	// NOXREF

#ifdef _WIN32

	//{ 0x0, "", (size_t)&BuyZoneIcon_Set },
	//{ 0x0, "", (size_t)&BuyZoneIcon_Clear },	// NOXREF
	//{ 0x0, "", (size_t)&BombTargetFlash_Set },
	//{ 0x0, "", (size_t)&BombTargetFlash_Clear },	// NOXREF
	//{ 0x0, "", (size_t)&RescueZoneIcon_Set },
	//{ 0x0, "", (size_t)&RescueZoneIcon_Clear },	// NOXREF
	{ 0x01DA8410, "", (size_t)&EscapeZoneIcon_Set },
	{ 0x01DA84C0, "", (size_t)&EscapeZoneIcon_Clear },
	{ 0x01DA8550, "", (size_t)&VIP_SafetyZoneIcon_Set },
	{ 0x01DA8630, "", (size_t)&VIP_SafetyZoneIcon_Clear },

#endif // _WIN32

	{ 0x01DA4420, "_ZN11CBasePlayer17SetNewPlayerModelEPKc", mfunc_ptr_cast(&CBasePlayer::SetNewPlayerModel) },
	{ 0x01DAB720, "_ZN11CBasePlayer12SwitchWeaponEP15CBasePlayerItem", mfunc_ptr_cast(&CBasePlayer::SwitchWeapon) },
	//{ 0x01DA43F0, "_ZN11CBasePlayer13CheckPowerupsEP9entvars_s", mfunc_ptr_cast(&CBasePlayer::CheckPowerups) },	// NOXREF
	{ 0x01DACDA0, "_ZN11CBasePlayer16CanAffordPrimaryEv", mfunc_ptr_cast(&CBasePlayer::CanAffordPrimary) },
	{ 0x01DACE10, "_ZN11CBasePlayer20CanAffordPrimaryAmmoEv", mfunc_ptr_cast(&CBasePlayer::CanAffordPrimaryAmmo) },
	{ 0x01DACE60, "_ZN11CBasePlayer22CanAffordSecondaryAmmoEv", mfunc_ptr_cast(&CBasePlayer::CanAffordSecondaryAmmo) },
	{ 0x01DACEB0, "_ZN11CBasePlayer14CanAffordArmorEv", mfunc_ptr_cast(&CBasePlayer::CanAffordArmor) },
	{ 0x01DACEF0, "_ZN11CBasePlayer18CanAffordDefuseKitEv", mfunc_ptr_cast(&CBasePlayer::CanAffordDefuseKit) },
	{ 0x01DACF00, "_ZN11CBasePlayer16CanAffordGrenadeEv", mfunc_ptr_cast(&CBasePlayer::CanAffordGrenade) },
	{ 0x01DACF20, "_ZN11CBasePlayer16NeedsPrimaryAmmoEv", mfunc_ptr_cast(&CBasePlayer::NeedsPrimaryAmmo) },
	{ 0x01DACF60, "_ZN11CBasePlayer18NeedsSecondaryAmmoEv", mfunc_ptr_cast(&CBasePlayer::NeedsSecondaryAmmo) },
	{ 0x01DACFA0, "_ZN11CBasePlayer10NeedsArmorEv", mfunc_ptr_cast(&CBasePlayer::NeedsArmor) },
	{ 0x01DACFD0, "_ZN11CBasePlayer14NeedsDefuseKitEv", mfunc_ptr_cast(&CBasePlayer::NeedsDefuseKit) },
	{ 0x01DAD000, "_ZN11CBasePlayer12NeedsGrenadeEv", mfunc_ptr_cast(&CBasePlayer::NeedsGrenade) },
	{ 0x01DA07B0, "_ZN11CBasePlayer10IsOnLadderEv", mfunc_ptr_cast(&CBasePlayer::IsOnLadder) },
	//{ 0x01DA6E80, "_ZN11CBasePlayer14FlashlightIsOnEv", mfunc_ptr_cast(&CBasePlayer::FlashlightIsOn) },	// NOXREF
	//{ 0x01DA6E90, "_ZN11CBasePlayer16FlashlightTurnOnEv", mfunc_ptr_cast(&CBasePlayer::FlashlightTurnOn) },	// NOXREF
	//{ 0x01DA6F40, "_ZN11CBasePlayer17FlashlightTurnOffEv", mfunc_ptr_cast(&CBasePlayer::FlashlightTurnOff) },	// NOXREF
	{ 0x01DA4450, "_ZN11CBasePlayer17UpdatePlayerSoundEv", mfunc_ptr_cast(&CBasePlayer::UpdatePlayerSound) },
	//{ 0x01D9BCA0, "_ZN11CBasePlayer10DeathSoundEv", mfunc_ptr_cast(&CBasePlayer::DeathSound) },	// NOXREF
	{ 0x01D9F430, "_ZN11CBasePlayer12SetAnimationE11PLAYER_ANIM", mfunc_ptr_cast(&CBasePlayer::SetAnimation) },
	//{ 0x0, "_ZN11CBasePlayer17SetWeaponAnimTypeEPKc", mfunc_ptr_cast(&CBasePlayer::SetWeaponAnimType) },	// NOXREF
	{ 0x01DA73C0, "_ZN11CBasePlayer20CheatImpulseCommandsEi", mfunc_ptr_cast(&CBasePlayer::CheatImpulseCommands) },
	//{ 0x01DA2640, "_ZN11CBasePlayer13StartDeathCamEv", mfunc_ptr_cast(&CBasePlayer::StartDeathCam) },		// NOXREF
	{ 0x01DA26D0, "_ZN11CBasePlayer13StartObserverE6VectorS0_", mfunc_ptr_cast(&CBasePlayer::StartObserver) },
	{ 0x01DA7FF0, "_ZN11CBasePlayer13HandleSignalsEv", mfunc_ptr_cast(&CBasePlayer::HandleSignals) },
	{ 0x01DAA850, "_ZN11CBasePlayer14DropPlayerItemEPKc", mfunc_ptr_cast(&CBasePlayer::DropPlayerItem) },
	{ 0x01DAAF30, "_ZN11CBasePlayer13HasPlayerItemEP15CBasePlayerItem", mfunc_ptr_cast(&CBasePlayer::HasPlayerItem) },
	{ 0x01DAAFC0, "_ZN11CBasePlayer18HasNamedPlayerItemEPKc", mfunc_ptr_cast(&CBasePlayer::HasNamedPlayerItem) },
	//{ 0x01DA6920, "_ZN11CBasePlayer10HasWeaponsEv", mfunc_ptr_cast(&CBasePlayer::HasWeapons) },	// NOXREF
	//{ 0x01DA6940, "_ZN11CBasePlayer14SelectPrevItemEi", mfunc_ptr_cast(&CBasePlayer::SelectPrevItem) }, // NOXREF
	//{ 0x01DA6470, "_ZN11CBasePlayer14SelectNextItemEi", mfunc_ptr_cast(&CBasePlayer::SelectNextItem) }, // NOXREF
	{ 0x01DA65E0, "_ZN11CBasePlayer10SelectItemEPKc", mfunc_ptr_cast(&CBasePlayer::SelectItem) },
	{ 0x01DA67A0, "_ZN11CBasePlayer14SelectLastItemEv", mfunc_ptr_cast(&CBasePlayer::SelectLastItem) },
	//{ 0x01DA8BB0, "_ZN11CBasePlayer12ItemPreFrameEv", mfunc_ptr_cast(&CBasePlayer::ItemPreFrame) },	// NOXREF
	//{ 0x01DA8BE0, "_ZN11CBasePlayer13ItemPostFrameEv", mfunc_ptr_cast(&CBasePlayer::ItemPostFrame) },	// NOXREF
	{ 0x01DA6CC0, "_ZN11CBasePlayer13GiveNamedItemEPKc", mfunc_ptr_cast(&CBasePlayer::GiveNamedItem) },
	{ 0x01DA9C80, "_ZN11CBasePlayer13EnableControlEi", mfunc_ptr_cast(&CBasePlayer::EnableControl) },
	{ 0x01DA9D50, "_ZN11CBasePlayer11HintMessageEPKcii", mfunc_ptr_cast(&CBasePlayer::HintMessage) },
	{ 0x01DA8CC0, "_ZN11CBasePlayer14SendAmmoUpdateEv", mfunc_ptr_cast(&CBasePlayer::SendAmmoUpdate) },
	//{ 0x01D9E4F0, "_ZN11CBasePlayer7SendFOVEi", mfunc_ptr_cast(&CBasePlayer::SendFOV) },	// NOXREF
	{ 0x01DA0390, "_ZN11CBasePlayer9WaterMoveEv", mfunc_ptr_cast(&CBasePlayer::WaterMove) },
	{ 0x01DA2140, "_ZN11CBasePlayer16PlayerDeathThinkEv", mfunc_ptr_cast(&CBasePlayer::PlayerDeathThink) },
	{ 0x01DA29A0, "_ZN11CBasePlayer9PlayerUseEv", mfunc_ptr_cast(&CBasePlayer::PlayerUse) },
	{ 0x01DA3290, "_ZN11CBasePlayer11HostageUsedEv", mfunc_ptr_cast(&CBasePlayer::HostageUsed) },
	{ 0x01DA1680, "_ZN11CBasePlayer12JoiningThinkEv", mfunc_ptr_cast(&CBasePlayer::JoiningThink) },
	//{ 0x01DA1480, "_ZN11CBasePlayer15RemoveLevelTextEv", mfunc_ptr_cast(&CBasePlayer::RemoveLevelText) },	// NOXREF
	{ 0x01DA14D0, "_ZN11CBasePlayer9MenuPrintEPS_PKc", mfunc_ptr_cast(&CBasePlayer::MenuPrint) },
	//{ 0x01DA11F0, "_ZN11CBasePlayer9ResetMenuEv", mfunc_ptr_cast(&CBasePlayer::ResetMenu) },	// NOXREF
	{ 0x01DA1240, "_ZN11CBasePlayer14SyncRoundTimerEv", mfunc_ptr_cast(&CBasePlayer::SyncRoundTimer) },
	{ 0x01DA4220, "_ZN11CBasePlayer15CheckSuitUpdateEv", mfunc_ptr_cast(&CBasePlayer::CheckSuitUpdate) },
	{ 0x01DA43E0, "_ZN11CBasePlayer13SetSuitUpdateEPcii", mfunc_ptr_cast(&CBasePlayer::SetSuitUpdate) },
	//{ 0x01DA4170, "_ZN11CBasePlayer19UpdateGeigerCounterEv", mfunc_ptr_cast(&CBasePlayer::UpdateGeigerCounter) },	// NOXREF
	{ 0x01DA3FE0, "_ZN11CBasePlayer20CheckTimeBasedDamageEv", mfunc_ptr_cast(&CBasePlayer::CheckTimeBasedDamage) },
	//{ 0x01DA9C10, "_ZN11CBasePlayer20BarnacleVictimBittenEP9entvars_s", mfunc_ptr_cast(&CBasePlayer::BarnacleVictimBitten) },	// NOXREF
	//{ 0x01DA9C40, "_ZN11CBasePlayer22BarnacleVictimReleasedEv", mfunc_ptr_cast(&CBasePlayer::BarnacleVictimReleased) },	// NOXREF
	{ 0x01DA8C80, "_ZN11CBasePlayer12GetAmmoIndexEPKc", mfunc_ptr_cast(&CBasePlayer::GetAmmoIndex) },
	{ 0x01DA8C60, "_ZN11CBasePlayer13AmmoInventoryEi", mfunc_ptr_cast(&CBasePlayer::AmmoInventory) },
	//{ 0x01DAA150, "_ZN11CBasePlayer12ResetAutoaimEv", mfunc_ptr_cast(&CBasePlayer::ResetAutoaim) },	// NOXREF
	//{ 0x01DAA120, "_ZN11CBasePlayer17AutoaimDeflectionER6Vectorff", mfunc_ptr_cast(&CBasePlayer::AutoaimDeflection) },	// NOXREF
	{ 0x01DA6FD0, "_ZN11CBasePlayer20ForceClientDllUpdateEv", mfunc_ptr_cast(&CBasePlayer::ForceClientDllUpdate) },
	//{ 0x0, "_ZN11CBasePlayer12DeathMessageEP9entvars_s", mfunc_ptr_cast(&CBasePlayer::DeathMessage) },	// NOXREF
	{ 0x01DAA1E0, "_ZN11CBasePlayer20SetCustomDecalFramesEi", mfunc_ptr_cast(&CBasePlayer::SetCustomDecalFrames) },
	//{ 0x01DAA210, "_ZN11CBasePlayer20GetCustomDecalFramesEv", mfunc_ptr_cast(&CBasePlayer::GetCustomDecalFrames) },	// NOXREF
	//{ 0x01DAA260, "_ZN11CBasePlayer13InitStatusBarEv", mfunc_ptr_cast(&CBasePlayer::InitStatusBar) },	// NOXREF
	{ 0x01DAA270, "_ZN11CBasePlayer15UpdateStatusBarEv", mfunc_ptr_cast(&CBasePlayer::UpdateStatusBar) },
	{ 0x01DAC0F0, "_ZN11CBasePlayer18StudioEstimateGaitEv", mfunc_ptr_cast(&CBasePlayer::StudioEstimateGait) },
	//{ 0x01DAC400, "_ZN11CBasePlayer17StudioPlayerBlendEPiPf", mfunc_ptr_cast(&CBasePlayer::StudioPlayerBlend) },	// NOXREF
	//{ 0x01DAC490, "_ZN11CBasePlayer19CalculatePitchBlendEv", mfunc_ptr_cast(&CBasePlayer::CalculatePitchBlend) },	// NOXREF
	{ 0x01DAC510, "_ZN11CBasePlayer17CalculateYawBlendEv", mfunc_ptr_cast(&CBasePlayer::CalculateYawBlend) },
	{ 0x01DAC640, "_ZN11CBasePlayer17StudioProcessGaitEv", mfunc_ptr_cast(&CBasePlayer::StudioProcessGait) },
	//{ 0x01DA8D40, "_ZN11CBasePlayer14SendHostagePosEv", mfunc_ptr_cast(&CBasePlayer::SendHostagePos) },	// NOXREF
	{ 0x01DA8DE0, "_ZN11CBasePlayer16SendHostageIconsEv", mfunc_ptr_cast(&CBasePlayer::SendHostageIcons) },
	//{ 0x01DAC7C0, "_ZN11CBasePlayer12ResetStaminaEv", mfunc_ptr_cast(&CBasePlayer::ResetStamina) },	// NOXREF
	//{ 0x01DACA10, "_ZN11CBasePlayer9IsArmoredEi", mfunc_ptr_cast(&CBasePlayer::IsArmored) },	// NOXREF
	//{ 0x01DACA60, "_ZN11CBasePlayer19ShouldDoLargeFlinchEii", mfunc_ptr_cast(&CBasePlayer::ShouldDoLargeFlinch) },	// NOXREF
	{ 0x01DACAD0, "_ZN11CBasePlayer20SetPrefsFromUserinfoEPc", mfunc_ptr_cast(&CBasePlayer::SetPrefsFromUserinfo) },
	{ 0x01DA8EE0, "_ZN11CBasePlayer15SendWeatherInfoEv", mfunc_ptr_cast(&CBasePlayer::SendWeatherInfo) },
	{ 0x01DAB6F0, "_ZN11CBasePlayer21UpdateShieldCrosshairEb", mfunc_ptr_cast(&CBasePlayer::UpdateShieldCrosshair) },
	{ 0x01DA0DA0, "_ZN11CBasePlayer9HasShieldEv", mfunc_ptr_cast(&CBasePlayer::HasShield) },
	//{ 0x0, "_ZN11CBasePlayer19IsProtectedByShieldEv", mfunc_ptr_cast(&CBasePlayer::IsProtectedByShield) },
	//{ 0x01DA0B20, "_ZN11CBasePlayer12RemoveShieldEv", mfunc_ptr_cast(&CBasePlayer::RemoveShield) },	// NOXREF
	{ 0x01DA0B60, "_ZN11CBasePlayer10DropShieldEb", mfunc_ptr_cast(&CBasePlayer::DropShield) },
	{ 0x01DA0A90, "_ZN11CBasePlayer10GiveShieldEb", mfunc_ptr_cast(&CBasePlayer::GiveShield) },
	//{ 0x01D9BDB0, "_ZN11CBasePlayer15IsHittingShieldERK6VectorP11TraceResult", mfunc_ptr_cast(&CBasePlayer::IsHittingShield) },	// NOXREF
	//{ 0x0, "_ZN11CBasePlayer11IsReloadingEv", mfunc_ptr_cast(&CBasePlayer::IsReloading) },	// NOXREF
	//{ 0x0, "_ZNK11CBasePlayer7IsBlindEv", mfunc_ptr_cast(&CBasePlayer::IsBlind) },	// NOXREF
	//{ 0x0, "_ZNK11CBasePlayer19IsAutoFollowAllowedEv", mfunc_ptr_cast(&CBasePlayer::IsAutoFollowAllowed) },	// NOXREF
	//{ 0x0, "_ZN11CBasePlayer17InhibitAutoFollowEf", mfunc_ptr_cast(&CBasePlayer::InhibitAutoFollow) },	// NOXREF
	//{ 0x0, "_ZN11CBasePlayer15AllowAutoFollowEv", mfunc_ptr_cast(&CBasePlayer::AllowAutoFollow) },	// NOXREF
	{ 0x01DAD180, "_ZN11CBasePlayer16ClearAutoBuyDataEv", mfunc_ptr_cast(&CBasePlayer::ClearAutoBuyData) },
	{ 0x01DAD190, "_ZN11CBasePlayer14AddAutoBuyDataEPKc", mfunc_ptr_cast(&CBasePlayer::AddAutoBuyData) },
	{ 0x01DAD280, "_ZN11CBasePlayer7AutoBuyEv", mfunc_ptr_cast(&CBasePlayer::AutoBuy) },
	{ 0x01DAD0D0, "_ZN11CBasePlayer13ClientCommandEPKcS1_S1_S1_", mfunc_ptr_cast(&CBasePlayer::ClientCommand) },
	{ 0x01DADD00, "_ZN11CBasePlayer23PrioritizeAutoBuyStringEPcPKc", mfunc_ptr_cast(&CBasePlayer::PrioritizeAutoBuyString) },
	//{ 0x01DAD590, "_ZN11CBasePlayer27PickPrimaryCareerTaskWeaponEv", mfunc_ptr_cast(&CBasePlayer::PickPrimaryCareerTaskWeapon) },
	//{ 0x01DAD930, "_ZN11CBasePlayer29PickSecondaryCareerTaskWeaponEv", mfunc_ptr_cast(&CBasePlayer::PickSecondaryCareerTaskWeapon) },
	//{ 0x01DADC60, "_ZN11CBasePlayer25PickFlashKillWeaponStringEv", mfunc_ptr_cast(&CBasePlayer::PickFlashKillWeaponString) },	// NOXREF
	//{ 0x01DADCC0, "_ZN11CBasePlayer27PickGrenadeKillWeaponStringEv", mfunc_ptr_cast(&CBasePlayer::PickGrenadeKillWeaponString) },	// NOXREF
	//{ 0x01DADF70, "_ZN11CBasePlayer27ShouldExecuteAutoBuyCommandEPK17AutoBuyInfoStructbb", mfunc_ptr_cast(&CBasePlayer::ShouldExecuteAutoBuyCommand) },		// NOXREF
	{ 0x01DADFF0, "_ZN11CBasePlayer28PostAutoBuyCommandProcessingEPK17AutoBuyInfoStructRbS3_", mfunc_ptr_cast(&CBasePlayer::PostAutoBuyCommandProcessing) },
	{ 0x01DADE20, "_ZN11CBasePlayer18ParseAutoBuyStringEPKcRbS2_", mfunc_ptr_cast(&CBasePlayer::ParseAutoBuyString) },
	//{ 0x01DADFB0, "_ZN11CBasePlayer21GetAutoBuyCommandInfoEPKc", mfunc_ptr_cast(&CBasePlayer::GetAutoBuyCommandInfo) },	// NOXREF
	{ 0x01DAD1F0, "_ZN11CBasePlayer13InitRebuyDataEPKc", mfunc_ptr_cast(&CBasePlayer::InitRebuyData) },
	{ 0x01DAE0A0, "_ZN11CBasePlayer16BuildRebuyStructEv", mfunc_ptr_cast(&CBasePlayer::BuildRebuyStruct) },
	{ 0x01DAE260, "_ZN11CBasePlayer5RebuyEv", mfunc_ptr_cast(&CBasePlayer::Rebuy) },
	//{ 0x01DAE580, "_ZN11CBasePlayer18RebuyPrimaryWeaponEv", mfunc_ptr_cast(&CBasePlayer::RebuyPrimaryWeapon) },	// NOXREF
	//{ 0x01DAE5E0, "_ZN11CBasePlayer16RebuyPrimaryAmmoEv", mfunc_ptr_cast(&CBasePlayer::RebuyPrimaryAmmo) },	// NOXREF
	//{ 0x01DAE650, "_ZN11CBasePlayer20RebuySecondaryWeaponEv", mfunc_ptr_cast(&CBasePlayer::RebuySecondaryWeapon) },	// NOXREF
	//{ 0x01DAE6B0, "_ZN11CBasePlayer18RebuySecondaryAmmoEv", mfunc_ptr_cast(&CBasePlayer::RebuySecondaryAmmo) },
	//{ 0x01DAE720, "_ZN11CBasePlayer14RebuyHEGrenadeEv", mfunc_ptr_cast(&CBasePlayer::RebuyHEGrenade) },			// NOXREF
	//{ 0x01DAE7C0, "_ZN11CBasePlayer14RebuyFlashbangEv", mfunc_ptr_cast(&CBasePlayer::RebuyFlashbang) },		// NOXREF
	//{ 0x01DAE860, "_ZN11CBasePlayer17RebuySmokeGrenadeEv", mfunc_ptr_cast(&CBasePlayer::RebuySmokeGrenade) },	// NOXREF
	{ 0x01DAE900, "_ZN11CBasePlayer12RebuyDefuserEv", mfunc_ptr_cast(&CBasePlayer::RebuyDefuser) },
	{ 0x01DAE960, "_ZN11CBasePlayer16RebuyNightVisionEv", mfunc_ptr_cast(&CBasePlayer::RebuyNightVision) },
	{ 0x01DAE9C0, "_ZN11CBasePlayer10RebuyArmorEv", mfunc_ptr_cast(&CBasePlayer::RebuyArmor) },
	{ 0x01DAEAB0, "_ZN11CBasePlayer14UpdateLocationEb", mfunc_ptr_cast(&CBasePlayer::UpdateLocation) },
	//{ 0x0, "_ZN11CBasePlayer23SetObserverAutoDirectorEb", mfunc_ptr_cast(&CBasePlayer::SetObserverAutoDirector) },	// NOXREF
	{ 0x01DAEA40, "_ZN11CBasePlayer17IsObservingPlayerEPS_", mfunc_ptr_cast(&CBasePlayer::IsObservingPlayer) },
	//{ 0x0, "_ZNK11CBasePlayer22CanSwitchObserverModesEv", mfunc_ptr_cast(&CBasePlayer::CanSwitchObserverModes) },	// NOXREF
	//{ 0x0, "_ZN11CBasePlayer7IntenseEv", mfunc_ptr_cast(&CBasePlayer::Intense) },	// NOXREF
	{ 0x01D9AB20, "_Z16LinkUserMessagesv", (size_t)&LinkUserMessages },
	{ 0x01D9B0F0, "_Z18WriteSigonMessagesv", (size_t)&WriteSigonMessages },
	{ 0x01D9B280, "_Z14SendItemStatusP11CBasePlayer", (size_t)&SendItemStatus },
	{ 0x01D9D8A0, "_ZL14GetCSModelNamei", (size_t)&GetCSModelName },
	{ 0x01D9B2D0, "_ZN11CBasePlayer14SetPlayerModelEi", mfunc_ptr_cast(&CBasePlayer::SetPlayerModel) },
	//{ 0x01D9BB40, "_Z20VecVelocityForDamagef", (size_t)&VecVelocityForDamage },	// NOXREF
	//{ 0x01D9BC40, "_Z10TrainSpeedii", (size_t)&TrainSpeed },	// NOXREF
	{ 0x01D9C2B0, "_Z13GetWeaponNameP9entvars_sS0_", (size_t)&GetWeaponName },
	{ 0x01D9C3C0, "_Z9LogAttackP11CBasePlayerS0_iiiiiPKc", (size_t)&LogAttack },
	{ 0x01D9D770, "_ZL14packPlayerItemP11CBasePlayerP15CBasePlayerItemb", (size_t)&packPlayerItem },
	{ 0x01DA3110, "_ZL13CanSeeUseableP11CBasePlayerP11CBaseEntity_isra_13", (size_t)&CanSeeUseable },
	//{ 0x01DA34E0, "_Z20FixPlayerCrouchStuckP7edict_s", (size_t)&FixPlayerCrouchStuck },	// NOXREF
	//{ 0x01DA4A90, "_Z17IsSpawnPointValidP11CBaseEntityS0_", (size_t)&IsSpawnPointValid },	// NOXREF
	//{ 0x01DA4B20, "_Z16InitZombieSpawnsv", (size_t)&InitZombieSpawns },	// NOXREF
	//{ 0x01DA4BC0, "_Z15FindZombieSpawnP11CBaseEntityb", (size_t)&FindZombieSpawn },	// NOXREF
	{ 0x01DA4BD0, "_Z19EntSelectSpawnPointP11CBaseEntity", (size_t)&EntSelectSpawnPoint },

#ifdef _WIN32
	{ 0x01DA5180, "", (size_t)&SetScoreAttrib },
#endif // _WIN32

	//{ 0x01DA6D60, "_Z17FindEntityForwardP11CBaseEntity", (size_t)&FindEntityForward },	// NOXREF
	{ 0x01DAC7E0, "_Z14GetPlayerPitchPK7edict_s", (size_t)&GetPlayerPitch },
	{ 0x01DAC830, "_Z12GetPlayerYawPK7edict_s", (size_t)&GetPlayerYaw },
	{ 0x01DAC880, "_Z21GetPlayerGaitsequencePK7edict_s", (size_t)&GetPlayerGaitsequence },
	//{ 0x01DAD120, "_Z26GetBuyStringForWeaponClassi", (size_t)&GetBuyStringForWeaponClass },	// NOXREF
	//{ 0x01DAD470, "_Z20IsPrimaryWeaponClassi", (size_t)&IsPrimaryWeaponClass },	// NOXREF
	//{ 0x01DAD490, "_Z17IsPrimaryWeaponIdi", (size_t)&IsPrimaryWeaponId },	// NOXREF
	//{ 0x01DAD4C0, "_Z22IsSecondaryWeaponClassi", (size_t)&IsSecondaryWeaponClass },		// NOXREF
	//{ 0x01DAD4D0, "_Z19IsSecondaryWeaponIdi", (size_t)&IsSecondaryWeaponId },	// NOXREF
	//{ 0x01DAD500, "_Z22GetWeaponAliasFromNamePKc", (size_t)&GetWeaponAliasFromName },	// NOXREF
	//{ 0x01DAD520, "_Z22CurrentWeaponSatisfiesP17CBasePlayerWeaponii", (size_t)&CurrentWeaponSatisfies },	// NOXREF
//CWShield
	//virtual func
	{ 0x1DA08D0, "_ZN8CWShield5SpawnEv", mfunc_ptr_cast(&CWShield::Spawn_) },
	{ 0x01DA0920, "_ZN8CWShield5TouchEP11CBaseEntity", mfunc_ptr_cast(&CWShield::Touch_) },
	//non-virtual func
	//{ 0x0, "_ZN8CWShield23SetCantBePickedUpByUserEP11CBaseEntityf", mfunc_ptr_cast(&CWShield::SetCantBePickedUpByUser) } // NOXREF INLINEBODY

//CSprayCan
	//virtual func
	{ 0x01DA6A30, "_ZN9CSprayCan5ThinkEv", mfunc_ptr_cast(&CSprayCan::Think_) },
	{ 0x01DA73B0, "_ZN9CSprayCan10ObjectCapsEv", mfunc_ptr_cast(&CSprayCan::ObjectCaps_) },
	//non-virtual func
	{ 0x01DA6970, "_ZN9CSprayCan5SpawnEP9entvars_s", mfunc_ptr_cast(&CSprayCan::Spawn) },	// NOXREF
//CBloodSplat
	//{ 0x01DA6B70, "_ZN11CBloodSplat5SpawnEP9entvars_s", mfunc_ptr_cast(&CBloodSplat::Spawn) },	// NOXREF
	//{ 0x01DA6C00, "_ZN11CBloodSplat5SprayEv", mfunc_ptr_cast(&CBloodSplat::Spray) },	// NOXREF
//CDeadHEV
	//virtual func
	{ 0x01DABAF0, "_ZN8CDeadHEV5SpawnEv", mfunc_ptr_cast(&CDeadHEV::Spawn_) },
	{ 0x01DABAE0, "_ZN8CDeadHEV8ClassifyEv", mfunc_ptr_cast(&CDeadHEV::Classify_) },
	{ 0x01DABA40, "_ZN8CDeadHEV8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CDeadHEV::KeyValue_) },
//CStripWeapons
	//virtual func
	{ 0x01DABC10, "_ZN13CStripWeapons3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CStripWeapons::Use_) },
//CRevertSaved
	//virtual func
	{ 0x01DABD20, "_ZN12CRevertSaved8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CRevertSaved::KeyValue_) },
	{ 0x01DABCC0, "_ZN12CRevertSaved4SaveER5CSave", mfunc_ptr_cast(&CRevertSaved::Save_) },
	{ 0x01DABCF0, "_ZN12CRevertSaved7RestoreER8CRestore", mfunc_ptr_cast(&CRevertSaved::Restore_) },
	{ 0x01DABE10, "_ZN12CRevertSaved3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CRevertSaved::Use_) },
	//non-virtual func
	{ 0x01DABE70, "_ZN12CRevertSaved12MessageThinkEv", mfunc_ptr_cast(&CRevertSaved::MessageThink) },
	{ 0x01DABEF0, "_ZN12CRevertSaved9LoadThinkEv", mfunc_ptr_cast(&CRevertSaved::LoadThink) },
//CInfoIntermission
	//virtual func
	{ 0x01DABF20, "_ZN17CInfoIntermission5SpawnEv", mfunc_ptr_cast(&CInfoIntermission::Spawn_) },
	{ 0x01DABF90, "_ZN17CInfoIntermission5ThinkEv", mfunc_ptr_cast(&CInfoIntermission::Think_) },
//linked object
	{ 0x01D9B1F0, "player", (size_t)&player },
	{ 0x01DAC0A0, "info_intermission", (size_t)&info_intermission },
	{ 0x01DABC70, "player_loadsaved", (size_t)&player_loadsaved },
	{ 0x01DABBC0, "player_weaponstrip", (size_t)&player_weaponstrip },
	{ 0x01DABA90, "monster_hevsuit_dead", (size_t)&monster_hevsuit_dead },
	{ 0x01DA0880, "weapon_shield", (size_t)&weapon_shield },

#endif // Player_Region

#ifndef Effects_Region

//CSprite
	//virtual func
	{ 0x01D792F0, "_ZN7CSprite5SpawnEv", mfunc_ptr_cast(&CSprite::Spawn_) },
	{ 0x01D79500, "_ZN7CSprite8PrecacheEv", mfunc_ptr_cast(&CSprite::Precache_) },
	{ 0x01D79440, "_ZN7CSprite7RestartEv", mfunc_ptr_cast(&CSprite::Restart_) },
	{ 0x01D79290, "_ZN7CSprite4SaveER5CSave", mfunc_ptr_cast(&CSprite::Save_) },
	{ 0x01D792C0, "_ZN7CSprite7RestoreER8CRestore", mfunc_ptr_cast(&CSprite::Restore_) },
	{ 0x01D78660, "_ZN7CSprite10ObjectCapsEv", mfunc_ptr_cast(&CSprite::ObjectCaps_) },
	{ 0x01D79AE0, "_ZN7CSprite3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CSprite::Use_) },
	//non-virtual func
	{ 0x01D79740, "_ZN7CSprite12AnimateThinkEv", mfunc_ptr_cast(&CSprite::AnimateThink) },
	{ 0x01D79930, "_ZN7CSprite11ExpandThinkEv", mfunc_ptr_cast(&CSprite::ExpandThink) },
	//{ 0x01D799C0, "_ZN7CSprite12AnimateThinkEv", mfunc_ptr_cast(&CSprite::Animate) },		// NOXREF
	//{ 0x01D798E0, "_ZN7CSprite6ExpandEff", mfunc_ptr_cast(&CSprite::Expand) },	// NOXREF
	//{ 0x01D79590, "_ZN7CSprite10SpriteInitEPKcRK6Vector", mfunc_ptr_cast(&CSprite::SpriteInit) },		// NOXREF
	//{ 0x0, "_ZN7CSprite13SetAttachmentEP7edict_si", mfunc_ptr_cast(&CSprite::SetAttachment) },	// NOXREF
	//{ 0x01D79A40, "_ZN7CSprite7TurnOffEv", mfunc_ptr_cast(&CSprite::TurnOff) },		// NOXREF
	{ 0x01D79A60, "_ZN7CSprite6TurnOnEv", mfunc_ptr_cast(&CSprite::TurnOn) },
	//{ 0x0, "_ZN7CSprite6FramesEv", mfunc_ptr_cast(&CSprite::Frames) },				// NOXREF
	//{ 0x0, "_ZN7CSprite15SetTransparencyEiiiiii", mfunc_ptr_cast(&CSprite::SetTransparency) },	// NOXREF
	//{ 0x0, "_ZN7CSprite10SetTextureEi", mfunc_ptr_cast(&CSprite::SetTexture) },			// NOXREF
	//{ 0x0, "_ZN7CSprite8SetScaleEf", mfunc_ptr_cast(&CSprite::SetScale) },			// NOXREF
	//{ 0x0, "_ZN7CSprite8SetColorEiii", mfunc_ptr_cast(&CSprite::SetColor) },			// NOXREF
	//{ 0x0, "_ZN7CSprite13SetBrightnessEi", mfunc_ptr_cast(&CSprite::SetBrightness) },		// NOXREF
	//{ 0x0, "_ZN7CSprite13AnimateAndDieEf", mfunc_ptr_cast(&CSprite::AnimateAndDie) },		// NOXREF
	{ 0x01D79800, "_ZN7CSprite16AnimateUntilDeadEv", mfunc_ptr_cast(&CSprite::AnimateUntilDead) },
	{ 0x01D795D0, "_ZN7CSprite12SpriteCreateEPKcRK6Vectori", mfunc_ptr_cast(&CSprite::SpriteCreate) },
//CBeam
	//virtual func
	{ 0x01D75E00, "_ZN5CBeam5SpawnEv", mfunc_ptr_cast(&CBeam::Spawn_) },
	{ 0x01D75E20, "_ZN5CBeam8PrecacheEv", mfunc_ptr_cast(&CBeam::Precache_) },
	{ 0x01D788B0, "_ZN5CBeam10ObjectCapsEv", mfunc_ptr_cast(&CBeam::ObjectCaps_) },
	{ 0x01D78D20, "_ZN5CBeam6CenterEv", mfunc_ptr_cast(&CBeam::Center_) },
	//non-virtual func
	{ 0x01D76660, "_ZN5CBeam12TriggerTouchEP11CBaseEntity", mfunc_ptr_cast(&CBeam::TriggerTouch) },
	//{ 0x0, "_ZN5CBeam7SetTypeEi", mfunc_ptr_cast(&CBeam::SetType) },						// NOXREF
	//{ 0x0, "_ZN5CBeam8SetFlagsEi", mfunc_ptr_cast(&CBeam::SetFlags) },						// NOXREF
	//{ 0x0, "_ZN5CBeam11SetStartPosERK6Vector", mfunc_ptr_cast(&CBeam::SetStartPos) },				// NOXREF
	//{ 0x0, "_ZN5CBeam9SetEndPosERK6Vector", mfunc_ptr_cast(&CBeam::SetEndPos) },					// NOXREF
	//{ 0x01D75EC0, "_ZN5CBeam14SetStartEntityEi", mfunc_ptr_cast(&CBeam::SetStartEntity) },		// NOXREF
	//{ 0x01D75F10, "_ZN5CBeam12SetEndEntityEi", mfunc_ptr_cast(&CBeam::SetEndEntity) },		// NOXREF
	{ 0x01D7A860, "_ZN5CBeam18SetStartAttachmentEi", mfunc_ptr_cast(&CBeam::SetStartAttachment) },
	{ 0x01D7A890, "_ZN5CBeam16SetEndAttachmentEi", mfunc_ptr_cast(&CBeam::SetEndAttachment) },
	//{ 0x0, "_ZN5CBeam10SetTextureEi", mfunc_ptr_cast(&CBeam::SetTexture) },					// NOXREF
	//{ 0x0, "_ZN5CBeam8SetWidthEi", mfunc_ptr_cast(&CBeam::SetWidth) },						// NOXREF
	//{ 0x0, "_ZN5CBeam8SetNoiseEi", mfunc_ptr_cast(&CBeam::SetNoise) },						// NOXREF
	//{ 0x0, "_ZN5CBeam8SetColorEiii", mfunc_ptr_cast(&CBeam::SetColor) },						// NOXREF
	//{ 0x0, "_ZN5CBeam13SetBrightnessEi", mfunc_ptr_cast(&CBeam::SetBrightness) },					// NOXREF
	//{ 0x0, "_ZN5CBeam8SetFrameEf", mfunc_ptr_cast(&CBeam::SetFrame) },						// NOXREF
	//{ 0x0, "_ZN5CBeam13SetScrollRateEi", mfunc_ptr_cast(&CBeam::SetScrollRate) },					// NOXREF
	//{ 0x0, "_ZN5CBeam7GetTypeEv", mfunc_ptr_cast(&CBeam::GetType) },						// NOXREF
	//{ 0x0, "_ZN5CBeam8GetFlagsEv", mfunc_ptr_cast(&CBeam::GetFlags) },						// NOXREF
	//{ 0x0, "_ZN5CBeam14GetStartEntityEv", mfunc_ptr_cast(&CBeam::GetStartEntity) },				// NOXREF
	//{ 0x0, "_ZN5CBeam12GetEndEntityEv", mfunc_ptr_cast(&CBeam::GetEndEntity) },					// NOXREF
	//{ 0x01D75F60, "_ZN5CBeam11GetStartPosEv", mfunc_ptr_cast(&CBeam::GetStartPos) },	// NOXREF
	//{ 0x01D75FA0, "_ZN5CBeam9GetEndPosEv", mfunc_ptr_cast(&CBeam::GetEndPos) },		// NOXREF
	//{ 0x0, "_ZN5CBeam10GetTextureEv", mfunc_ptr_cast(&CBeam::GetTexture) },					// NOXREF
	//{ 0x0, "_ZN5CBeam8GetWidthEv", mfunc_ptr_cast(&CBeam::GetWidth) },						// NOXREF
	//{ 0x0, "_ZN5CBeam8GetNoiseEv", mfunc_ptr_cast(&CBeam::GetNoise) },						// NOXREF
	//{ 0x0, "_ZN5CBeam13GetBrightnessEv", mfunc_ptr_cast(&CBeam::GetBrightness) },					// NOXREF
	//{ 0x0, "_ZN5CBeam8GetFrameEv", mfunc_ptr_cast(&CBeam::GetFrame) },						// NOXREF
	//{ 0x0, "_ZN5CBeam13GetScrollRateEv", mfunc_ptr_cast(&CBeam::GetScrollRate) },					// NOXREF
	{ 0x01D76480, "_ZN5CBeam10RelinkBeamEv", mfunc_ptr_cast(&CBeam::RelinkBeam) },
	//{ 0x01D76700, "_ZN5CBeam8DoSparksERK6VectorS2_", mfunc_ptr_cast(&CBeam::DoSparks) },			// NOXREF
	//{ 0x01D766B0, "_ZN5CBeam16RandomTargetnameEPKc", mfunc_ptr_cast(&CBeam::RandomTargetname) },		// NOXREF
	{ 0x01D775B0, "_ZN5CBeam10BeamDamageEP11TraceResult", mfunc_ptr_cast(&CBeam::BeamDamage) },
	{ 0x01D76140, "_ZN5CBeam8BeamInitEPKci", mfunc_ptr_cast(&CBeam::BeamInit) },
	//{ 0x01D76200, "_ZN5CBeam10PointsInitERK6VectorS2_", mfunc_ptr_cast(&CBeam::PointsInit) },		// NOXREF
	//{ 0x01D76300, "_ZN5CBeam12PointEntInitERK6Vectori", mfunc_ptr_cast(&CBeam::PointEntInit) },		// NOXREF
	//{ 0x01D763B0, "_ZN5CBeam8EntsInitEii", mfunc_ptr_cast(&CBeam::EntsInit) },				// NOXREF
	//{ 0x01D76280, "_ZN5CBeam8HoseInitERK6VectorS2_", mfunc_ptr_cast(&CBeam::HoseInit) },				// NOXREF
	//{ 0x01D75FF0, "_ZN5CBeam10BeamCreateEPKci", mfunc_ptr_cast(&CBeam::BeamCreate) },				// NOXREF
	//{ 0x0, "_ZN5CBeam11LiveForTimeEf", mfunc_ptr_cast(&CBeam::LiveForTime) },					// NOXREF
	//{ 0x0, "_ZN5CBeam17BeamDamageInstantEP11TraceResultf", mfunc_ptr_cast(&CBeam::BeamDamageInstant) },		// NOXREF
//CLaser
	//virtual func
	{ 0x01D782A0, "_ZN6CLaser5SpawnEv", mfunc_ptr_cast(&CLaser::Spawn_) },
	{ 0x01D78680, "_ZN6CLaser8PrecacheEv", mfunc_ptr_cast(&CLaser::Precache_) },
	{ 0x01D786D0, "_ZN6CLaser8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CLaser::KeyValue_) },
	{ 0x01D78240, "_ZN6CLaser4SaveER5CSave", mfunc_ptr_cast(&CLaser::Save_) },
	{ 0x01D78270, "_ZN6CLaser7RestoreER8CRestore", mfunc_ptr_cast(&CLaser::Restore_) },
	{ 0x01D789E0, "_ZN6CLaser3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CLaser::Use_) },
	//non-virtual func
	{ 0x01D78930, "_ZN6CLaser6TurnOnEv", mfunc_ptr_cast(&CLaser::TurnOn) },
	{ 0x01D788F0, "_ZN6CLaser7TurnOffEv", mfunc_ptr_cast(&CLaser::TurnOff) },
	//{ 0x01D788D0, "_ZN6CLaser4IsOnEv", mfunc_ptr_cast(&CLaser::IsOn) },	// NOXREF
	{ 0x01D78B00, "_ZN6CLaser11FireAtPointER11TraceResult", mfunc_ptr_cast(&CLaser::FireAtPoint) },
	{ 0x01D78BB0, "_ZN6CLaser11StrikeThinkEv", mfunc_ptr_cast(&CLaser::StrikeThink) },
//CBubbling
	//virtual func
	{ 0x01D75A90, "_ZN9CBubbling5SpawnEv", mfunc_ptr_cast(&CBubbling::Spawn_) },
	{ 0x01D75BA0, "_ZN9CBubbling8PrecacheEv", mfunc_ptr_cast(&CBubbling::Precache_) },
	{ 0x01D75C30, "_ZN9CBubbling8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBubbling::KeyValue_) },
	{ 0x01D75A30, "_ZN9CBubbling4SaveER5CSave", mfunc_ptr_cast(&CBubbling::Save_) },
	{ 0x01D75A60, "_ZN9CBubbling7RestoreER8CRestore", mfunc_ptr_cast(&CBubbling::Restore_) },
	{ 0x01D75A20, "_ZN9CBubbling10ObjectCapsEv", mfunc_ptr_cast(&CBubbling::ObjectCaps_) },
	{ 0x01D75BC0, "_ZN9CBubbling3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBubbling::Use_) },
	//non-virtual func
	{ 0x01D75CF0, "_ZN9CBubbling9FizzThinkEv", mfunc_ptr_cast(&CBubbling::FizzThink) },
//CLightning
	//virtual func
	{ 0x01D76840, "_ZN10CLightning5SpawnEv", mfunc_ptr_cast(&CLightning::Spawn_) },
	{ 0x01D76970, "_ZN10CLightning8PrecacheEv", mfunc_ptr_cast(&CLightning::Precache_) },
	{ 0x01D76A60, "_ZN10CLightning8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CLightning::KeyValue_) },
	{ 0x01D767E0, "_ZN10CLightning4SaveER5CSave", mfunc_ptr_cast(&CLightning::Save_) },
	{ 0x01D76810, "_ZN10CLightning7RestoreER8CRestore", mfunc_ptr_cast(&CLightning::Restore_) },
	{ 0x01D76A30, "_ZN10CLightning8ActivateEv", mfunc_ptr_cast(&CLightning::Activate_) },
	//non-virtual func
	{ 0x01D76EE0, "_ZN10CLightning11StrikeThinkEv", mfunc_ptr_cast(&CLightning::StrikeThink) },
	{ 0x01D776A0, "_ZN10CLightning11DamageThinkEv", mfunc_ptr_cast(&CLightning::DamageThink) },
	{ 0x01D778C0, "_ZN10CLightning10RandomAreaEv", mfunc_ptr_cast(&CLightning::RandomArea) },
	{ 0x01D77CC0, "_ZN10CLightning11RandomPointER6Vector", mfunc_ptr_cast(&CLightning::RandomPoint) },
	{ 0x01D77760, "_ZN10CLightning3ZapERK6VectorS2_", mfunc_ptr_cast(&CLightning::Zap) },
	{ 0x01D76E00, "_ZN10CLightning9StrikeUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CLightning::StrikeUse) },
	{ 0x01D76CB0, "_ZN10CLightning9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CLightning::ToggleUse) },
	//{ 0x0, "_ZN10CLightning10ServerSideEv", mfunc_ptr_cast(&CLightning::ServerSide) },	// NOXREF
	{ 0x01D77E60, "_ZN10CLightning14BeamUpdateVarsEv", mfunc_ptr_cast(&CLightning::BeamUpdateVars) },
	//{ 0x1D76E70, "_Z13IsPointEntityP11CBaseEntity", (size_t)&IsPointEntity },	// NOXREF
//CGlow
	//virtual func
	{ 0x01D78E90, "_ZN5CGlow5SpawnEv", mfunc_ptr_cast(&CGlow::Spawn_) },
	{ 0x01D78E30, "_ZN5CGlow4SaveER5CSave", mfunc_ptr_cast(&CGlow::Save_) },
	{ 0x01D78E60, "_ZN5CGlow7RestoreER8CRestore", mfunc_ptr_cast(&CGlow::Restore_) },
	{ 0x01D78FA0, "_ZN5CGlow5ThinkEv", mfunc_ptr_cast(&CGlow::Think_) },
	//non-virtual func
	//{ 0x01D79010, "_ZN5CGlow7AnimateEf", mfunc_ptr_cast(&CGlow::Animate) },	// NOXREF
//CBombGlow
	//virtual func
	{ 0x01D790A0, "_ZN9CBombGlow5SpawnEv", mfunc_ptr_cast(&CBombGlow::Spawn_) },
	{ 0x01D79150, "_ZN9CBombGlow5ThinkEv", mfunc_ptr_cast(&CBombGlow::Think_) },
//CGibShooter
	//virtual func
	{ 0x01D79DA0, "_ZN11CGibShooter5SpawnEv", mfunc_ptr_cast(&CGibShooter::Spawn_) },
	{ 0x01D79C50, "_ZN11CGibShooter8PrecacheEv", mfunc_ptr_cast(&CGibShooter::Precache_) },
	{ 0x01D79C90, "_ZN11CGibShooter8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CGibShooter::KeyValue_) },
	{ 0x01D79BA0, "_ZN11CGibShooter4SaveER5CSave", mfunc_ptr_cast(&CGibShooter::Save_) },
	{ 0x01D79BD0, "_ZN11CGibShooter7RestoreER8CRestore", mfunc_ptr_cast(&CGibShooter::Restore_) },
	{ 0x01D79D80, "_ZN11CGibShooter3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGibShooter::Use_) },
	{ 0x01D79E20, "_ZN11CGibShooter9CreateGibEv", mfunc_ptr_cast(&CGibShooter::CreateGib_) },
	//non-virtual func
	{ 0x01D79EF0, "_ZN11CGibShooter10ShootThinkEv", mfunc_ptr_cast(&CGibShooter::ShootThink) },
//CEnvShooter
	//virtual func
	{ 0x01D7A370, "_ZN11CEnvShooter8PrecacheEv", mfunc_ptr_cast(&CEnvShooter::Precache_) },
	{ 0x01D7A270, "_ZN11CEnvShooter8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CEnvShooter::KeyValue_) },
	{ 0x01D7A3B0, "_ZN11CEnvShooter9CreateGibEv", mfunc_ptr_cast(&CEnvShooter::CreateGib_) },
//CTestEffect
	//virtual func
	{ 0x01D7A530, "_ZN11CTestEffect5SpawnEv", mfunc_ptr_cast(&CTestEffect::Spawn_) },
	{ 0x01D7A540, "_ZN11CTestEffect8PrecacheEv", mfunc_ptr_cast(&CTestEffect::Precache_) },
	{ 0x01D7A8C0, "_ZN11CTestEffect3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTestEffect::Use_) },
	//non-virtual func
	{ 0x01D7A550, "_ZN11CTestEffect9TestThinkEv", mfunc_ptr_cast(&CTestEffect::TestThink) },
//CBlood
	//virtual func
	{ 0x01D7A940, "_ZN6CBlood5SpawnEv", mfunc_ptr_cast(&CBlood::Spawn_) },
	{ 0x01D7A980, "_ZN6CBlood8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBlood::KeyValue_) },
	{ 0x01D7AB70, "_ZN6CBlood3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBlood::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN6CBlood5ColorEv", mfunc_ptr_cast(&CBlood::Color) },				// NOXREF
	//{ 0x0, "_ZN6CBlood11BloodAmountEv", mfunc_ptr_cast(&CBlood::BloodAmount) },			// NOXREF
	//{ 0x0, "_ZN6CBlood8SetColorEi", mfunc_ptr_cast(&CBlood::SetColor) },				// NOXREF
	//{ 0x0, "_ZN6CBlood14SetBloodAmountEf", mfunc_ptr_cast(&CBlood::SetBloodAmount) },		// NOXREF
	//{ 0x01D7AA30, "_ZN6CBlood9DirectionEv", mfunc_ptr_cast(&CBlood::Direction) },		// NOXREF
	{ 0x01D7AA70, "_ZN6CBlood13BloodPositionEP11CBaseEntity", mfunc_ptr_cast(&CBlood::BloodPosition) },
//CShake
	//virtual func
	{ 0x01D7ADB0, "_ZN6CShake5SpawnEv", mfunc_ptr_cast(&CShake::Spawn_) },
	{ 0x01D7ADF0, "_ZN6CShake8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CShake::KeyValue_) },
	{ 0x01D7AEE0, "_ZN6CShake3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CShake::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN6CShake9AmplitudeEv", mfunc_ptr_cast(&CShake::Amplitude) },				// NOXREF
	//{ 0x0, "_ZN6CShake9FrequencyEv", mfunc_ptr_cast(&CShake::Frequency) },				// NOXREF
	//{ 0x0, "_ZN6CShake8DurationEv", mfunc_ptr_cast(&CShake::Duration) },					// NOXREF
	//{ 0x0, "_ZN6CShake6RadiusEv", mfunc_ptr_cast(&CShake::Radius) },					// NOXREF
	//{ 0x0, "_ZN6CShake12SetAmplitudeEf", mfunc_ptr_cast(&CShake::SetAmplitude) },				// NOXREF
	//{ 0x0, "_ZN6CShake12SetFrequencyEf", mfunc_ptr_cast(&CShake::SetFrequency) },				// NOXREF
	//{ 0x0, "_ZN6CShake11SetDurationEf", mfunc_ptr_cast(&CShake::SetDuration) },				// NOXREF
	//{ 0x0, "_ZN6CShake9SetRadiusEf", mfunc_ptr_cast(&CShake::SetRadius) },				// NOXREF
//CFade
	//virtual func
	{ 0x01D7AF70, "_ZN5CFade5SpawnEv", mfunc_ptr_cast(&CFade::Spawn_) },
	{ 0x01D7AFA0, "_ZN5CFade8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFade::KeyValue_) },
	{ 0x01D7B030, "_ZN5CFade3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFade::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN5CFade8DurationEv", mfunc_ptr_cast(&CFade::Duration) },				// NOXREF
	//{ 0x0, "_ZN5CFade8HoldTimeEv", mfunc_ptr_cast(&CFade::HoldTime) },				// NOXREF
	//{ 0x0, "_ZN5CFade11SetDurationEf", mfunc_ptr_cast(&CFade::SetDuration) },			// NOXREF
	//{ 0x0, "_ZN5CFade11SetHoldTimeEf", mfunc_ptr_cast(&CFade::SetHoldTime) },			// NOXREF
//CMessage
	//virtual func
	{ 0x01D7B150, "_ZN8CMessage5SpawnEv", mfunc_ptr_cast(&CMessage::Spawn_) },
	{ 0x01D7B1E0, "_ZN8CMessage8PrecacheEv", mfunc_ptr_cast(&CMessage::Precache_) },
	{ 0x01D7B210, "_ZN8CMessage8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CMessage::KeyValue_) },
	{ 0x01D7B2E0, "_ZN8CMessage3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CMessage::Use_) },
//CEnvFunnel
	//virtual func
	{ 0x01D7B4E0, "_ZN10CEnvFunnel5SpawnEv", mfunc_ptr_cast(&CEnvFunnel::Spawn_) },
	{ 0x01D7B3E0, "_ZN10CEnvFunnel8PrecacheEv", mfunc_ptr_cast(&CEnvFunnel::Precache_) },
	{ 0x01D7B450, "_ZN10CEnvFunnel3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CEnvFunnel::Use_) },
//CEnvBeverage
	//virtual func
	{ 0x01D7B630, "_ZN12CEnvBeverage5SpawnEv", mfunc_ptr_cast(&CEnvBeverage::Spawn_) },
	{ 0x01D7B510, "_ZN12CEnvBeverage8PrecacheEv", mfunc_ptr_cast(&CEnvBeverage::Precache_) },
	{ 0x01D7B580, "_ZN12CEnvBeverage3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CEnvBeverage::Use_) },
//CItemSoda
	//virtual func
	{ 0x01D7B6E0, "_ZN9CItemSoda5SpawnEv", mfunc_ptr_cast(&CItemSoda::Spawn_) },
	//{ 0x01D7B680, "_ZN9CItemSoda8PrecacheEv", mfunc_ptr_cast(&CItemSoda::Precache_) },	// pure
	//non-virtual func
	{ 0x01D7B790, "_ZN9CItemSoda8CanThinkEv", mfunc_ptr_cast(&CItemSoda::CanThink) },
	{ 0x01D7B820, "_ZN9CItemSoda8CanTouchEP11CBaseEntity", mfunc_ptr_cast(&CItemSoda::CanTouch) },
	
//linked objects
	{ 0x01D75980, "info_target", (size_t)&info_target },
	{ 0x01D759D0, "env_bubbles", (size_t)&env_bubbles },
	{ 0x01D75DB0, "beam", (size_t)&beam },
	{ 0x01D76740, "env_lightning", (size_t)&env_lightning },
	{ 0x01D76790, "env_beam", (size_t)&env_beam },
	{ 0x01D781F0, "env_laser", (size_t)&env_laser },
	{ 0x01D78DE0, "env_glow", (size_t)&env_glow },
	{ 0x01D79050, "env_bombglow", (size_t)&env_bombglow },
	{ 0x01D79240, "env_sprite", (size_t)&env_sprite },
	{ 0x01D79C00, "gibshooter", (size_t)&gibshooter },
	{ 0x01D7A220, "env_shooter", (size_t)&env_shooter },
	{ 0x01D7A4E0, "test_effect", (size_t)&test_effect },
	{ 0x01D7A8F0, "env_blood", (size_t)&env_blood },
	{ 0x01D7AD60, "env_shake", (size_t)&env_shake },
	{ 0x01D7AF20, "env_fade", (size_t)&env_fade },
	{ 0x01D7B100, "env_message", (size_t)&env_message },
	{ 0x01D7B400, "env_funnel", (size_t)&env_funnel },
	{ 0x01D7B530, "env_beverage", (size_t)&env_beverage },
	{ 0x01D7B690, "item_sodacan", (size_t)&item_sodacan },

#endif // Effects_Region

#ifndef Plats_Region

//CBasePlatTrain
	//virtual func
	//{ 0x0, "_ZN14CBasePlatTrain8PrecacheEv", mfunc_ptr_cast(&CBasePlatTrain::Precache_) },
	//{ 0x0, "_ZN14CBasePlatTrain8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBasePlatTrain::KeyValue_) },
	//{ 0x0, "_ZN14CBasePlatTrain4SaveER5CSave", mfunc_ptr_cast(&CBasePlatTrain::Save_) },
	//{ 0x0, "_ZN14CBasePlatTrain7RestoreER8CRestore", mfunc_ptr_cast(&CBasePlatTrain::Restore_) },
	//{ 0x0, "_ZN14CBasePlatTrain10ObjectCapsEv", mfunc_ptr_cast(&CBasePlatTrain::ObjectCaps_) },
	//{ 0x0, "_ZN14CBasePlatTrain12IsTogglePlatEv", mfunc_ptr_cast(&CBasePlatTrain::IsTogglePlat_) },
//CFuncPlat
	//virtual func
	//{ 0x0, "_ZN9CFuncPlat5SpawnEv", mfunc_ptr_cast(&CFuncPlat::Spawn_) },
	//{ 0x0, "_ZN9CFuncPlat8PrecacheEv", mfunc_ptr_cast(&CFuncPlat::Precache_) },
	//{ 0x0, "_ZN9CFuncPlat7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CFuncPlat::Blocked_) },
	//{ 0x0, "_ZN9CFuncPlat4GoUpEv", mfunc_ptr_cast(&CFuncPlat::GoUp_) },
	//{ 0x0, "_ZN9CFuncPlat6GoDownEv", mfunc_ptr_cast(&CFuncPlat::GoDown_) },
	//{ 0x0, "_ZN9CFuncPlat6HitTopEv", mfunc_ptr_cast(&CFuncPlat::HitTop_) },
	//{ 0x0, "_ZN9CFuncPlat9HitBottomEv", mfunc_ptr_cast(&CFuncPlat::HitBottom_) },
	//non-virtual func
	//{ 0x0, "_ZN9CFuncPlat5SetupEv", mfunc_ptr_cast(&CFuncPlat::Setup) },
	//{ 0x0, "_ZN9CFuncPlat7PlatUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncPlat::PlatUse) },
	//{ 0x0, "_ZN9CFuncPlat10CallGoDownEv", mfunc_ptr_cast(&CFuncPlat::CallGoDown) },
	//{ 0x0, "_ZN9CFuncPlat10CallHitTopEv", mfunc_ptr_cast(&CFuncPlat::CallHitTop) },
	//{ 0x0, "_ZN9CFuncPlat13CallHitBottomEv", mfunc_ptr_cast(&CFuncPlat::CallHitBottom) },
//CPlatTrigger
	//virtual func
	//{ 0x0, "_ZN12CPlatTrigger10ObjectCapsEv", mfunc_ptr_cast(&CPlatTrigger::ObjectCaps_) },
	//{ 0x0, "_ZN12CPlatTrigger5TouchEP11CBaseEntity", mfunc_ptr_cast(&CPlatTrigger::Touch_) },
	//non-virtual func
	//{ 0x0, "_ZN12CPlatTrigger18SpawnInsideTriggerEP9CFuncPlat", mfunc_ptr_cast(&CPlatTrigger::SpawnInsideTrigger) },
//CFuncPlatRot
	//virtual func
	//{ 0x0, "_ZN12CFuncPlatRot5SpawnEv", mfunc_ptr_cast(&CFuncPlatRot::Spawn_) },
	//{ 0x0, "_ZN12CFuncPlatRot4SaveER5CSave", mfunc_ptr_cast(&CFuncPlatRot::Save_) },
	//{ 0x0, "_ZN12CFuncPlatRot7RestoreER8CRestore", mfunc_ptr_cast(&CFuncPlatRot::Restore_) },
	//{ 0x0, "_ZN12CFuncPlatRot4GoUpEv", mfunc_ptr_cast(&CFuncPlat::GoUp_) },
	//{ 0x0, "_ZN12CFuncPlatRot6GoDownEv", mfunc_ptr_cast(&CFuncPlat::GoDown_) },
	//{ 0x0, "_ZN12CFuncPlatRot6HitTopEv", mfunc_ptr_cast(&CFuncPlat::HitTop_) },
	//{ 0x0, "_ZN12CFuncPlatRot9HitBottomEv", mfunc_ptr_cast(&CFuncPlat::HitBottom_) },
	//non-virtual func
	//{ 0x0, "_ZN12CFuncPlatRot13SetupRotationEv", mfunc_ptr_cast(&CFuncPlatRot::SetupRotation) },
	//{ 0x0, "_ZN12CFuncPlatRot7RotMoveER6Vectorf", mfunc_ptr_cast(&CFuncPlatRot::RotMove) },
//CFuncTrain
	//virtual func
	//{ 0x0, "_ZN10CFuncTrain5SpawnEv", mfunc_ptr_cast(&CFuncTrain::Spawn_) },
	//{ 0x0, "_ZN10CFuncTrain8PrecacheEv", mfunc_ptr_cast(&CFuncTrain::Precache_) },
	//{ 0x0, "_ZN10CFuncTrain7RestartEv", mfunc_ptr_cast(&CFuncTrain::Restart_) },
	//{ 0x0, "_ZN10CFuncTrain8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncTrain::KeyValue_) },
	//{ 0x0, "_ZN10CFuncTrain4SaveER5CSave", mfunc_ptr_cast(&CFuncTrain::Save_) },
	//{ 0x0, "_ZN10CFuncTrain7RestoreER8CRestore", mfunc_ptr_cast(&CFuncTrain::Restore_) },
	//{ 0x0, "_ZN10CFuncTrain8ActivateEv", mfunc_ptr_cast(&CFuncTrain::Activate_) },
	//{ 0x0, "_ZN10CFuncTrain13OverrideResetEv", mfunc_ptr_cast(&CFuncTrain::OverrideReset_) },
	//{ 0x0, "_ZN10CFuncTrain3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncTrain::Use_) },
	//{ 0x0, "_ZN10CFuncTrain7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CFuncTrain::Blocked_) },
	//non-virtual func
	//{ 0x0, "_ZN10CFuncTrain4WaitEv", mfunc_ptr_cast(&CFuncTrain::Wait) },
	//{ 0x0, "_ZN10CFuncTrain4NextEv", mfunc_ptr_cast(&CFuncTrain::Next) },
//CFuncTrackTrain
	//virtual func
	//{ 0x0, "_ZN15CFuncTrackTrain5SpawnEv", mfunc_ptr_cast(&CFuncTrackTrain::Spawn_) },
	//{ 0x0, "_ZN15CFuncTrackTrain8PrecacheEv", mfunc_ptr_cast(&CFuncTrackTrain::Precache_) },
	//{ 0x0, "_ZN15CFuncTrackTrain7RestartEv", mfunc_ptr_cast(&CFuncTrackTrain::Restart_) },
	//{ 0x0, "_ZN15CFuncTrackTrain8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncTrackTrain::KeyValue_) },
	//{ 0x0, "_ZN15CFuncTrackTrain4SaveER5CSave", mfunc_ptr_cast(&CFuncTrackTrain::Save_) },
	//{ 0x0, "_ZN15CFuncTrackTrain7RestoreER8CRestore", mfunc_ptr_cast(&CFuncTrackTrain::Restore_) },
	//{ 0x0, "_ZN15CFuncTrackTrain10ObjectCapsEv", mfunc_ptr_cast(&CFuncTrackTrain::ObjectCaps_) },
	//{ 0x0, "_ZN15CFuncTrackTrain13OverrideResetEv", mfunc_ptr_cast(&CFuncTrackTrain::OverrideReset_) },
	//{ 0x0, "_ZN15CFuncTrackTrain10OnControlsEP9entvars_s", mfunc_ptr_cast(&CFuncTrackTrain::OnControls_) },
	//{ 0x0, "_ZN15CFuncTrackTrain3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncTrackTrain::Use_) },
	//{ 0x0, "_ZN15CFuncTrackTrain7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CFuncTrackTrain::Blocked_) },
	//non-virtual func
	//{ 0x0, "_ZN15CFuncTrackTrain4NextEv", mfunc_ptr_cast(&CFuncTrackTrain::Next) },
	//{ 0x0, "_ZN15CFuncTrackTrain4FindEv", mfunc_ptr_cast(&CFuncTrackTrain::Find) },
	//{ 0x0, "_ZN15CFuncTrackTrain11NearestPathEv", mfunc_ptr_cast(&CFuncTrackTrain::NearestPath) },
	//{ 0x0, "_ZN15CFuncTrackTrain7DeadEndEv", mfunc_ptr_cast(&CFuncTrackTrain::DeadEnd) },
	//{ 0x0, "_ZN15CFuncTrackTrain9NextThinkEfi", mfunc_ptr_cast(&CFuncTrackTrain::NextThink) },
	//{ 0x0, "_ZN15CFuncTrackTrain8SetTrackEP10CPathTrack", mfunc_ptr_cast(&CFuncTrackTrain::SetTrack) },		// NOXREF
	//{ 0x0, "_ZN15CFuncTrackTrain11SetControlsEP9entvars_s", mfunc_ptr_cast(&CFuncTrackTrain::SetControls) },
	//{ 0x0, "_ZN15CFuncTrackTrain9StopSoundEv", mfunc_ptr_cast(&CFuncTrackTrain::StopSound) },
	//{ 0x0, "_ZN15CFuncTrackTrain11UpdateSoundEv", mfunc_ptr_cast(&CFuncTrackTrain::UpdateSound) },
	//{ 0x0, "_ZN15CFuncTrackTrain8InstanceEP7edict_s", mfunc_ptr_cast(&CFuncTrackTrain::Instance) },
//CFuncTrainControls
	//virtual func
	//{ 0x0, "_ZN18CFuncTrainControls5SpawnEv", mfunc_ptr_cast(&CFuncTrainControls::Spawn_) },
	//{ 0x0, "_ZN18CFuncTrainControls10ObjectCapsEv", mfunc_ptr_cast(&CFuncTrainControls::ObjectCaps_) },
	//non-virtual func
	//{ 0x0, "_ZN18CFuncTrainControls4FindEv", mfunc_ptr_cast(&CFuncTrainControls::Find) },
//CFuncTrackChange
	//virtual func
	//{ 0x0, "_ZN16CFuncTrackChange5SpawnEv", mfunc_ptr_cast(&CFuncTrackChange::Spawn_) },
	//{ 0x0, "_ZN16CFuncTrackChange8PrecacheEv", mfunc_ptr_cast(&CFuncTrackChange::Precache_) },
	//{ 0x0, "_ZN16CFuncTrackChange8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncTrackChange::KeyValue_) },
	//{ 0x0, "_ZN16CFuncTrackChange4SaveER5CSave", mfunc_ptr_cast(&CFuncTrackChange::Save_) },
	//{ 0x0, "_ZN16CFuncTrackChange7RestoreER8CRestore", mfunc_ptr_cast(&CFuncTrackChange::Restore_) },
	//{ 0x0, "_ZN16CFuncTrackChange13OverrideResetEv", mfunc_ptr_cast(&CFuncTrackChange::OverrideReset_) },
	//{ 0x0, "_ZN16CFuncTrackChange5TouchEP11CBaseEntity", mfunc_ptr_cast(&CFuncTrackChange::Touch_) },
	//{ 0x0, "_ZN16CFuncTrackChange3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncTrackChange::Use_) },
	//{ 0x0, "_ZN16CFuncTrackChange12IsTogglePlatEv", mfunc_ptr_cast(&CFuncTrackChange::IsTogglePlat_) },
	//{ 0x0, "_ZN16CFuncTrackChange4GoUpEv", mfunc_ptr_cast(&CFuncTrackChange::GoUp_) },
	//{ 0x0, "_ZN16CFuncTrackChange6GoDownEv", mfunc_ptr_cast(&CFuncTrackChange::GoDown_) },
	//{ 0x0, "_ZN16CFuncTrackChange9HitBottomEv", mfunc_ptr_cast(&CFuncTrackChange::HitBottom_) },
	//{ 0x0, "_ZN16CFuncTrackChange6HitTopEv", mfunc_ptr_cast(&CFuncTrackChange::HitTop_) },
	//{ 0x0, "_ZN16CFuncTrackChange17UpdateAutoTargetsEi", mfunc_ptr_cast(&CFuncTrackChange::UpdateAutoTargets_) },
	//non-virtual func
	//{ 0x0, "_ZN16CFuncTrackChange4FindEv", mfunc_ptr_cast(&CFuncTrackChange::Find) },
	//{ 0x0, "_ZN16CFuncTrackChange13EvaluateTrainEP10CPathTrack", mfunc_ptr_cast(&CFuncTrackChange::EvaluateTrain) },
	//{ 0x0, "_ZN16CFuncTrackChange11UpdateTrainER6Vector", mfunc_ptr_cast(&CFuncTrackChange::UpdateTrain) },
	//{ 0x0, "_ZN16CFuncTrackChange10DisableUseEv", mfunc_ptr_cast(&CFuncTrackChange::DisableUse) },				// NOXREF
	//{ 0x0, "_ZN16CFuncTrackChange9EnableUseEv", mfunc_ptr_cast(&CFuncTrackChange::EnableUse) },				// NOXREF
	//{ 0x0, "_ZN16CFuncTrackChange10UseEnabledEv", mfunc_ptr_cast(&CFuncTrackChange::UseEnabled) },					// NOXREF
//CFuncTrackAuto
	//virtual func
	//{ 0x0, "_ZN14CFuncTrackAuto3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncTrackAuto::Use_) },
	//{ 0x0, "_ZN14CFuncTrackAuto17UpdateAutoTargetsEi", mfunc_ptr_cast(&CFuncTrackAuto::UpdateAutoTargets_) },
//CGunTarget
	//virtual func
	//{ 0x0, "_ZN10CGunTarget5SpawnEv", mfunc_ptr_cast(&CGunTarget::Spawn_) },
	//{ 0x0, "_ZN10CGunTarget4SaveER5CSave", mfunc_ptr_cast(&CGunTarget::Save_) },
	//{ 0x0, "_ZN10CGunTarget7RestoreER8CRestore", mfunc_ptr_cast(&CGunTarget::Restore_) },
	//{ 0x0, "_ZN10CGunTarget10ObjectCapsEv", mfunc_ptr_cast(&CGunTarget::ObjectCaps_) },
	//{ 0x0, "_ZN10CGunTarget8ActivateEv", mfunc_ptr_cast(&CGunTarget::Activate_) },
	//{ 0x0, "_ZN10CGunTarget8ClassifyEv", mfunc_ptr_cast(&CGunTarget::Classify_) },
	//{ 0x0, "_ZN10CGunTarget10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CGunTarget::TakeDamage_) },
	//{ 0x0, "_ZN10CGunTarget10BloodColorEv", mfunc_ptr_cast(&CGunTarget::BloodColor_) },
	//{ 0x0, "_ZN10CGunTarget3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGunTarget::Use_) },
	//{ 0x0, "_ZN10CGunTarget10BodyTargetERK6Vector", mfunc_ptr_cast(&CGunTarget::BodyTarget_) },
	//non-virtual func
	//{ 0x0, "_ZN10CGunTarget4NextEv", mfunc_ptr_cast(&CGunTarget::Next) },
	//{ 0x0, "_ZN10CGunTarget5StartEv", mfunc_ptr_cast(&CGunTarget::Start) },
	//{ 0x0, "_ZN10CGunTarget4WaitEv", mfunc_ptr_cast(&CGunTarget::Wait) },
	//{ 0x0, "_ZN10CGunTarget4StopEv", mfunc_ptr_cast(&CGunTarget::Stop) },
//CPlane
	//{ 0x01D952F0, "_ZN6CPlaneC2Ev", mfunc_ptr_cast(&CPlane::CPlane) },	// NOXREF
	//{ 0x01D95300, "_ZN6CPlane15InitializePlaneERK6VectorS2_", mfunc_ptr_cast(&CPlane::InitializePlane) },	// NOXREF
	//{ 0x01D95340, "_ZN6CPlane12PointInFrontERK6Vector", mfunc_ptr_cast(&CPlane::PointInFront) },	// NOXREF

#endif // Plats_Region

#ifndef PathCorner_Region

//CPathTrack
	//virtual func
	//{ 0x0, "_ZN10CPathTrack5SpawnEv", mfunc_ptr_cast(&CPathTrack::Spawn_) },
	//{ 0x0, "_ZN10CPathTrack8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CPathTrack::KeyValue_) },
	//{ 0x0, "_ZN10CPathTrack4SaveER5CSave", mfunc_ptr_cast(&CPathTrack::Save_) },
	//{ 0x0, "_ZN10CPathTrack7RestoreER8CRestore", mfunc_ptr_cast(&CPathTrack::Restore_) },
	//{ 0x0, "_ZN10CPathTrack8ActivateEv", mfunc_ptr_cast(&CPathTrack::Activate_) },
	//{ 0x0, "_ZN10CPathTrack3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CPathTrack::Use_) },
	//non-virtual func
	//{ 0x01D94B90, "_ZN10CPathTrack11SetPreviousEPS_", mfunc_ptr_cast(&CPathTrack::SetPrevious) },	// NOXREF
	//{ 0x0, "_ZN10CPathTrack4LinkEv", mfunc_ptr_cast(&CPathTrack::Link) },
	//{ 0x01D94A10, "_ZN10CPathTrack9ValidPathEPS_i", mfunc_ptr_cast(&CPathTrack::ValidPath) },
	//{ 0x01D94A40, "_ZN10CPathTrack7ProjectEPS_S0_P6Vectorf", mfunc_ptr_cast(&CPathTrack::Project) },	// NOXREF
	//{ 0x0, "_ZN10CPathTrack8InstanceEP7edict_s", mfunc_ptr_cast(&CPathTrack::Instance) },
	//{ 0x0, "_ZN10CPathTrack9LookAheadEP6Vectorfi", mfunc_ptr_cast(&CPathTrack::LookAhead) },
	//{ 0x0, "_ZN10CPathTrack7NearestE6Vector", mfunc_ptr_cast(&CPathTrack::Nearest) },
	//{ 0x0, "_ZN10CPathTrack7GetNextEv", mfunc_ptr_cast(&CPathTrack::GetNext) },
	//{ 0x0, "_ZN10CPathTrack11GetPreviousEv", mfunc_ptr_cast(&CPathTrack::GetPrevious) },
//CPathCorner
	//virtual func
	//{ 0x0, "_ZN11CPathCorner5SpawnEv", mfunc_ptr_cast(&CPathCorner::Spawn_) },
	//{ 0x0, "_ZN11CPathCorner8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CPathCorner::KeyValue_) },
	//{ 0x0, "_ZN11CPathCorner4SaveER5CSave", mfunc_ptr_cast(&CPathCorner::Save_) },
	//{ 0x0, "_ZN11CPathCorner7RestoreER8CRestore", mfunc_ptr_cast(&CPathCorner::Restore_) },
	//{ 0x0, "_ZN11CPathCorner8GetDelayEv", mfunc_ptr_cast(&CPathCorner::GetDelay_) },

#endif // PathCorner_Region

#ifndef Vehicle_Region

//CFuncVehicle
	//virtual func
	//{ 0x0, "_ZN12CFuncVehicle5SpawnEv", mfunc_ptr_cast(&CFuncVehicle::Spawn_) },
	{ 0x01DCC310, "_ZN12CFuncVehicle8PrecacheEv", mfunc_ptr_cast(&CFuncVehicle::Precache_) },
	//{ 0x0, "_ZN12CFuncVehicle7RestartEv", mfunc_ptr_cast(&CFuncVehicle::Restart_) },
	//{ 0x0, "_ZN12CFuncVehicle8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncVehicle::KeyValue_) },
	//{ 0x0, "_ZN12CFuncVehicle4SaveER5CSave", mfunc_ptr_cast(&CFuncVehicle::Save_) },
	//{ 0x0, "_ZN12CFuncVehicle7RestoreER8CRestore", mfunc_ptr_cast(&CFuncVehicle::Restore_) },
	//{ 0x0, "_ZN12CFuncVehicle10ObjectCapsEv", mfunc_ptr_cast(&CFuncVehicle::ObjectCaps_) },
	{ 0x01DCBFB0, "_ZN12CFuncVehicle8ClassifyEv", mfunc_ptr_cast(&CFuncVehicle::Classify_) },
	//{ 0x0, "_ZN12CFuncVehicle13OverrideResetEv", mfunc_ptr_cast(&CFuncVehicle::OverrideReset_) },
	{ 0x01DCBA30, "_ZN12CFuncVehicle10OnControlsEP9entvars_s", mfunc_ptr_cast(&CFuncVehicle::OnControls_) },
	//{ 0x0, "_ZN12CFuncVehicle3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncVehicle::Use_) },
	//{ 0x0, "_ZN12CFuncVehicle7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CFuncVehicle::Blocked_) },
	//non-virtual func
	//{ 0x0, "_ZN12CFuncVehicle4NextEv", mfunc_ptr_cast(&CFuncVehicle::Next) },
	//{ 0x0, "_ZN12CFuncVehicle4FindEv", mfunc_ptr_cast(&CFuncVehicle::Find) },
	//{ 0x0, "_ZN12CFuncVehicle11NearestPathEv", mfunc_ptr_cast(&CFuncVehicle::NearestPath) },
	//{ 0x0, "_ZN12CFuncVehicle7DeadEndEv", mfunc_ptr_cast(&CFuncVehicle::DeadEnd) },
	//{ 0x0, "_ZN12CFuncVehicle9NextThinkEfi", mfunc_ptr_cast(&CFuncVehicle::NextThink) },
	//{ 0x0, "_ZN12CFuncVehicle18CollisionDetectionEv", mfunc_ptr_cast(&CFuncVehicle::CollisionDetection) },
	//{ 0x0, "_ZN12CFuncVehicle16TerrainFollowingEv", mfunc_ptr_cast(&CFuncVehicle::TerrainFollowing) },
	//{ 0x0, "_ZN12CFuncVehicle12CheckTurningEv", mfunc_ptr_cast(&CFuncVehicle::CheckTurning) },
	//{ 0x0, "_ZN12CFuncVehicle8SetTrackEP10CPathTrack", mfunc_ptr_cast(&CFuncVehicle::SetTrack) },		// NOXREF
	//{ 0x01DCB980, "_ZN12CFuncVehicle11SetControlsEP9entvars_s", mfunc_ptr_cast(&CFuncVehicle::SetControls) },	// NOXREF
	//{ 0x0, "_ZN12CFuncVehicle9StopSoundEv", mfunc_ptr_cast(&CFuncVehicle::StopSound) },
	//{ 0x0, "_ZN12CFuncVehicle11UpdateSoundEv", mfunc_ptr_cast(&CFuncVehicle::UpdateSound) },
	//{ 0x01DCBF60, "_ZN12CFuncVehicle8InstanceEP7edict_s", mfunc_ptr_cast(&CFuncVehicle::Instance) },	// NOXREF
	//{ 0x0, "", (size_t)&FixupAngles2 },	// NOXREF
//CFuncVehicleControls
	//virtual func
	//{ 0x0, "_ZN20CFuncVehicleControls5SpawnEv", mfunc_ptr_cast(&CFuncVehicleControls::Spawn) },
	//{ 0x0, "_ZN20CFuncVehicleControls10ObjectCapsEv", mfunc_ptr_cast(&CFuncVehicleControls::ObjectCaps) },
	//non-virtual func
	//{ 0x0, "_ZN20CFuncVehicleControls4FindEv", mfunc_ptr_cast(&CFuncVehicleControls::Find) },

#endif // Vehicle_Region

#ifndef Func_Tank_Region

//CFuncTank
	//virtual func
	//{ 0x0, "_ZN9CFuncTank5SpawnEv", mfunc_ptr_cast(&CFuncTank::Spawn_) },
	//{ 0x0, "_ZN9CFuncTank8PrecacheEv", mfunc_ptr_cast(&CFuncTank::Precache_) },
	//{ 0x0, "_ZN9CFuncTank8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncTank::KeyValue_) },
	//{ 0x0, "_ZN9CFuncTank4SaveER5CSave", mfunc_ptr_cast(&CFuncTank::Save_) },
	//{ 0x0, "_ZN9CFuncTank7RestoreER8CRestore", mfunc_ptr_cast(&CFuncTank::Restore_) },
	//{ 0x0, "_ZN9CFuncTank10ObjectCapsEv", mfunc_ptr_cast(&CFuncTank::ObjectCaps_) },
	//{ 0x0, "_ZN9CFuncTank10OnControlsEP9entvars_s", mfunc_ptr_cast(&CFuncTank::OnControls_) },
	//{ 0x0, "_ZN9CFuncTank5ThinkEv", mfunc_ptr_cast(&CFuncTank::Think_) },
	//{ 0x0, "_ZN9CFuncTank3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncTank::Use_) },
	//{ 0x0, "_ZN9CFuncTank4FireERK6VectorS2_P9entvars_s", mfunc_ptr_cast(&CFuncTank::Fire_) },
	//{ 0x0, "_ZN9CFuncTank20UpdateTargetPositionEP11CBaseEntity", mfunc_ptr_cast(&CFuncTank::UpdateTargetPosition_) },
	//non-virtual func
	//{ 0x0, "_ZN9CFuncTank11TrackTargetEv", mfunc_ptr_cast(&CFuncTank::TrackTarget) },
	//{ 0x0, "_ZN9CFuncTank13StartRotSoundEv", mfunc_ptr_cast(&CFuncTank::StartRotSound) },
	//{ 0x0, "_ZN9CFuncTank12StopRotSoundEv", mfunc_ptr_cast(&CFuncTank::StopRotSound) },
	//{ 0x0, "_ZN9CFuncTank8IsActiveEv", mfunc_ptr_cast(&CFuncTank::IsActive) },		// NOXREF
	//{ 0x0, "_ZN9CFuncTank12TankActivateEv", mfunc_ptr_cast(&CFuncTank::TankActivate) },		// NOXREF
	//{ 0x0, "_ZN9CFuncTank14TankDeactivateEv", mfunc_ptr_cast(&CFuncTank::TankDeactivate) },		// NOXREF
	//{ 0x0, "_ZN9CFuncTank7CanFireEv", mfunc_ptr_cast(&CFuncTank::CanFire) },		// NOXREF
	//{ 0x0, "_ZN9CFuncTank7InRangeEf", mfunc_ptr_cast(&CFuncTank::InRange) },
	//{ 0x0, "_ZN9CFuncTank10FindTargetEP7edict_s", mfunc_ptr_cast(&CFuncTank::FindTarget) },
	//{ 0x0, "_ZN9CFuncTank9TankTraceERK6VectorS2_S2_R11TraceResult", mfunc_ptr_cast(&CFuncTank::TankTrace) },
	//{ 0x0, "_ZN9CFuncTank14BarrelPositionEv", mfunc_ptr_cast(&CFuncTank::BarrelPosition) },
	//{ 0x0, "_ZN9CFuncTank21AdjustAnglesForBarrelER6Vectorf", mfunc_ptr_cast(&CFuncTank::AdjustAnglesForBarrel) },
	//{ 0x0, "_ZN9CFuncTank12StartControlEP11CBasePlayer", mfunc_ptr_cast(&CFuncTank::StartControl) },
	//{ 0x0, "_ZN9CFuncTank11StopControlEv", mfunc_ptr_cast(&CFuncTank::StopControl) },
	//{ 0x0, "_ZN9CFuncTank19ControllerPostFrameEv", mfunc_ptr_cast(&CFuncTank::ControllerPostFrame) },
//CFuncTankGun
	//virtual func
	//{ 0x0, "_ZN12CFuncTankGun4FireERK6VectorS2_P9entvars_s", mfunc_ptr_cast(&CFuncTankGun::Spawn_) },
//CFuncTankLaser
	//virtual func
	//{ 0x0, "_ZN14CFuncTankLaser8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncTankLaser::KeyValue_) },
	//{ 0x0, "_ZN14CFuncTankLaser4SaveER5CSave", mfunc_ptr_cast(&CFuncTankLaser::Save_) },
	//{ 0x0, "_ZN14CFuncTankLaser7RestoreER8CRestore", mfunc_ptr_cast(&CFuncTankLaser::Restore_) },
	//{ 0x0, "_ZN14CFuncTankLaser8ActivateEv", mfunc_ptr_cast(&CFuncTankLaser::Activate_) },
	//{ 0x0, "_ZN14CFuncTankLaser5ThinkEv", mfunc_ptr_cast(&CFuncTankLaser::Think_) },
	//{ 0x0, "_ZN14CFuncTankLaser4FireERK6VectorS2_P9entvars_s", mfunc_ptr_cast(&CFuncTankLaser::Fire_) },
	//non-virtual func
	//{ 0x0, "_ZN14CFuncTankLaser8GetLaserEv", mfunc_ptr_cast(&CFuncTankLaser::GetLaser) },
//CFuncTankRocket
	//virtual func
	//{ 0x0, "_ZN15CFuncTankRocket8PrecacheEv", mfunc_ptr_cast(&CFuncTankRocket::Precache_) },
	//{ 0x0, "_ZN15CFuncTankRocket4FireERK6VectorS2_P9entvars_s", mfunc_ptr_cast(&CFuncTankRocket::Fire_) },
//CFuncTankMortar
	//virtual func
	//{ 0x0, "_ZN15CFuncTankMortar8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncTankRocket::KeyValue_) },
	//{ 0x0, "_ZN15CFuncTankMortar4FireERK6VectorS2_P9entvars_s", mfunc_ptr_cast(&CFuncTankRocket::Fire_) },
//CFuncTankControls
	//virtual func
	//{ 0x0, "_ZN17CFuncTankControls5SpawnEv", mfunc_ptr_cast(&BaseClass::Spawn_) },
	//{ 0x0, "_ZN17CFuncTankControls4SaveER5CSave", mfunc_ptr_cast(&BaseClass::Save_) },
	//{ 0x0, "_ZN17CFuncTankControls7RestoreER8CRestore", mfunc_ptr_cast(&BaseClass::Restore_) },
	//{ 0x0, "_ZN17CFuncTankControls10ObjectCapsEv", mfunc_ptr_cast(&BaseClass::ObjectCaps_) },
	//{ 0x0, "_ZN17CFuncTankControls5ThinkEv", mfunc_ptr_cast(&BaseClass::Think_) },
	//{ 0x0, "_ZN17CFuncTankControls3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&BaseClass::Use_) },

#endif // Func_Tank_Region

#ifndef Func_Break_Region

//CBreakable
	//virtual func
	//{ 0x0, "_ZN10CBreakable5SpawnEv", mfunc_ptr_cast(&CBreakable::Spawn_) },
	//{ 0x0, "_ZN10CBreakable8PrecacheEv", mfunc_ptr_cast(&CBreakable::Precache_) },
	//{ 0x0, "_ZN10CBreakable7RestartEv", mfunc_ptr_cast(&CBreakable::Restart_) },
	//{ 0x0, "_ZN10CBreakable8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBreakable::KeyValue_) },
	//{ 0x0, "_ZN10CBreakable4SaveER5CSave", mfunc_ptr_cast(&CBreakable::Save_) },
	//{ 0x0, "_ZN10CBreakable7RestoreER8CRestore", mfunc_ptr_cast(&CBreakable::Restore_) },
	//{ 0x0, "_ZN10CBreakable10ObjectCapsEv", mfunc_ptr_cast(&CBreakable::ObjectCaps_) },
	//{ 0x0, "_ZN10CBreakable11TraceAttackEP9entvars_sf6VectorP11TraceResulti", mfunc_ptr_cast(&CBreakable::TraceAttack_) },
	//{ 0x0, "_ZN10CBreakable10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBreakable::TakeDamage_) },
	//{ 0x0, "_ZN10CBreakable11DamageDecalEi", mfunc_ptr_cast(&CBreakable::DamageDecal_) },
	//{ 0x0, "_ZN10CBreakable3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBreakable::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN10CBreakable10BreakTouchEP11CBaseEntity", mfunc_ptr_cast(&CBreakable::BreakTouch) },
	//{ 0x0, "_ZN10CBreakable11DamageSoundEv", mfunc_ptr_cast(&CBreakable::DamageSound) },
	//{ 0x0, "_ZN10CBreakable11IsBreakableEv", mfunc_ptr_cast(&CBreakable::IsBreakable) },
	//{ 0x0, "_ZN10CBreakable12SparkWhenHitEv", mfunc_ptr_cast(&CBreakable::SparkWhenHit) },
	//{ 0x0, "_ZN10CBreakable3DieEv", mfunc_ptr_cast(&CBreakable::Die) },
	//{ 0x0, "_ZN10CBreakable10ExplodableEv", mfunc_ptr_cast(&CBreakable::Explodable) },					// NOXREF
	//{ 0x0, "_ZN10CBreakable18ExplosionMagnitudeEv", mfunc_ptr_cast(&CBreakable::ExplosionMagnitude) },		// NOXREF
	//{ 0x0, "_ZN10CBreakable21ExplosionSetMagnitudeEi", mfunc_ptr_cast(&CBreakable::ExplosionSetMagnitude) },		// NOXREF
	{ 0x01D7C670, "_ZN10CBreakable21MaterialSoundPrecacheE9Materials", mfunc_ptr_cast(&CBreakable::MaterialSoundPrecache) },
	{ 0x01D7C710, "_ZN10CBreakable19MaterialSoundRandomEP7edict_s9Materialsf", mfunc_ptr_cast(&CBreakable::MaterialSoundRandom) },
	//{ 0x01D7C5D0, "_ZN10CBreakable17MaterialSoundListE9MaterialsRi", mfunc_ptr_cast(&CBreakable::MaterialSoundList) },	// NOXREF
//CPushable
	//virtual func
	//{ 0x0, "_ZN9CPushable5SpawnEv", mfunc_ptr_cast(&CPushable::Spawn_) },
	//{ 0x0, "_ZN9CPushable8PrecacheEv", mfunc_ptr_cast(&CPushable::Precache_) },
	//{ 0x0, "_ZN9CPushable8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CPushable::KeyValue_) },
	//{ 0x0, "_ZN9CPushable4SaveER5CSave", mfunc_ptr_cast(&CPushable::Save_) },
	//{ 0x0, "_ZN9CPushable7RestoreER8CRestore", mfunc_ptr_cast(&CPushable::Restore_) },
	//{ 0x0, "_ZN9CPushable10ObjectCapsEv", mfunc_ptr_cast(&CPushable::ObjectCaps_) },
	//{ 0x0, "_ZN9CPushable10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CPushable::TakeDamage_) },
	//{ 0x0, "_ZN9CPushable5TouchEP11CBaseEntity", mfunc_ptr_cast(&CPushable::Touch_) },
	//{ 0x0, "_ZN9CPushable3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CPushable::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN9CPushable4MoveEP11CBaseEntityi", mfunc_ptr_cast(&CPushable::Move) },
	//{ 0x0, "_ZN9CPushable9StopSoundEv", mfunc_ptr_cast(&CPushable::StopSound) },
	//{ 0x0, "_ZN9CPushable8MaxSpeedEv", mfunc_ptr_cast(&CPushable::MaxSpeed) },	// NOXREF

#endif // Func_Break_Region

#ifndef Door_Region

//CBaseDoor
	//virtual func
	//{ 0x0, "_ZN9CBaseDoor5SpawnEv", mfunc_ptr_cast(&CBaseDoor::Spawn_) },
	//{ 0x0, "_ZN9CBaseDoor8PrecacheEv", mfunc_ptr_cast(&CBaseDoor::Precache_) },
	//{ 0x0, "_ZN9CBaseDoor7RestartEv", mfunc_ptr_cast(&CBaseDoor::Restart_) },
	//{ 0x0, "_ZN9CBaseDoor8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseDoor::KeyValue_) },
	//{ 0x0, "_ZN9CBaseDoor4SaveER5CSave", mfunc_ptr_cast(&CBaseDoor::Save_) },
	//{ 0x0, "_ZN9CBaseDoor7RestoreER8CRestore", mfunc_ptr_cast(&CBaseDoor::Restore_) },
	//{ 0x0, "_ZN9CBaseDoor10ObjectCapsEv", mfunc_ptr_cast(&CBaseDoor::ObjectCaps_) },
	//{ 0x0, "_ZN9CBaseDoor14SetToggleStateEi", mfunc_ptr_cast(&CBaseDoor::SetToggleState_) },
	//{ 0x0, "_ZN9CBaseDoor3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBaseDoor::Use_) },
	//{ 0x0, "_ZN9CBaseDoor7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CBaseDoor::Blocked_) },
	//non-virtual func
	//{ 0x0, "_ZN9CBaseDoor9DoorTouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseDoor::DoorTouch) },
	//{ 0x0, "_ZN9CBaseDoor12DoorActivateEv", mfunc_ptr_cast(&CBaseDoor::DoorActivate) },
	//{ 0x0, "_ZN9CBaseDoor8DoorGoUpEv", mfunc_ptr_cast(&CBaseDoor::DoorGoUp) },
	//{ 0x0, "_ZN9CBaseDoor10DoorGoDownEv", mfunc_ptr_cast(&CBaseDoor::DoorGoDown) },
	//{ 0x0, "_ZN9CBaseDoor10DoorHitTopEv", mfunc_ptr_cast(&CBaseDoor::DoorHitTop) },
	//{ 0x0, "_ZN9CBaseDoor13DoorHitBottomEv", mfunc_ptr_cast(&CBaseDoor::DoorHitBottom) },
//CRotDoor
	//virtual func
	//{ 0x0, "_ZN8CRotDoor5SpawnEv", mfunc_ptr_cast(&CRotDoor::Spawn_) },
	//{ 0x0, "_ZN8CRotDoor7RestartEv", mfunc_ptr_cast(&CRotDoor::Restart_) },
	//{ 0x0, "_ZN8CRotDoor14SetToggleStateEi", mfunc_ptr_cast(&CRotDoor::SetToggleState_) },
//CMomentaryDoor
	//virtual func
	//{ 0x0, "_ZN14CMomentaryDoor5SpawnEv", mfunc_ptr_cast(&CMomentaryDoor::Spawn_) },
	//{ 0x0, "_ZN14CMomentaryDoor8PrecacheEv", mfunc_ptr_cast(&CMomentaryDoor::Precache_) },
	//{ 0x0, "_ZN14CMomentaryDoor8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CMomentaryDoor::KeyValue_) },
	//{ 0x0, "_ZN14CMomentaryDoor4SaveER5CSave", mfunc_ptr_cast(&CMomentaryDoor::Save_) },
	//{ 0x0, "_ZN14CMomentaryDoor7RestoreER8CRestore", mfunc_ptr_cast(&CMomentaryDoor::Restore_) },
	//{ 0x0, "_ZN14CMomentaryDoor10ObjectCapsEv", mfunc_ptr_cast(&CMomentaryDoor::ObjectCaps_) },
	//{ 0x0, "_ZN14CMomentaryDoor3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CMomentaryDoor::Use_) },

	//{ 0x0, "_Z14PlayLockSoundsP9entvars_sP10locksoundsii", (size_t)&PlayLockSounds },

#endif // Door_Region

#ifndef BModels_Region

//CFuncWall
	//virtual func
	//{ 0x0, "_ZN9CFuncWall5SpawnEv", mfunc_ptr_cast(&CFuncWall::Spawn_) },
	//{ 0x0, "_ZN9CFuncWall10ObjectCapsEv", mfunc_ptr_cast(&CFuncWall::ObjectCaps_) },
	//{ 0x0, "_ZN9CFuncWall3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncWall::Use_) },
//CFuncWallToggle
	//virtual func
	//{ 0x0, "_ZN15CFuncWallToggle5SpawnEv", mfunc_ptr_cast(&CFuncWallToggle::Spawn_) },
	//{ 0x0, "_ZN15CFuncWallToggle3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncWallToggle::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN15CFuncWallToggle7TurnOffEv", mfunc_ptr_cast(&CFuncWallToggle::TurnOff) },
	//{ 0x0, "_ZN15CFuncWallToggle6TurnOnEv", mfunc_ptr_cast(&CFuncWallToggle::TurnOn) },
	//{ 0x0, "_ZN15CFuncWallToggle4IsOnEv", mfunc_ptr_cast(&CFuncWallToggle::IsOn) },
//CFuncConveyor
	//virtual func
	//{ 0x0, "_ZN13CFuncConveyor5SpawnEv", mfunc_ptr_cast(&CFuncConveyor::Spawn_) },
	//{ 0x0, "_ZN13CFuncConveyor3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncConveyor::Use_) },
//CFuncIllusionary
	//virtual func
	//{ 0x0, "_ZN16CFuncIllusionary5SpawnEv", mfunc_ptr_cast(&CFuncIllusionary::Spawn_) },
	//{ 0x0, "_ZN16CFuncIllusionary8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncIllusionary::KeyValue_) },
	//{ 0x0, "_ZN16CFuncIllusionary10ObjectCapsEv", mfunc_ptr_cast(&CFuncIllusionary::ObjectCaps_) },
//CFuncMonsterClip
	//virtual func
	//{ 0x0, "_ZN16CFuncMonsterClip5SpawnEv", mfunc_ptr_cast(&CFuncMonsterClip::Spawn_) },
	//{ 0x0, "_ZN16CFuncMonsterClip3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncMonsterClip::Use_) },	// PURE
//CFuncRotating
	//virtual func
	//{ 0x0, "_ZN13CFuncRotating5SpawnEv", mfunc_ptr_cast(&CFuncRotating::Spawn_) },
	//{ 0x0, "_ZN13CFuncRotating8PrecacheEv", mfunc_ptr_cast(&CFuncRotating::Precache_) },
	//{ 0x0, "_ZN13CFuncRotating8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncRotating::KeyValue_) },
	//{ 0x0, "_ZN13CFuncRotating4SaveER5CSave", mfunc_ptr_cast(&CFuncRotating::Save_) },
	//{ 0x0, "_ZN13CFuncRotating7RestoreER8CRestore", mfunc_ptr_cast(&CFuncRotating::Restore_) },
	//{ 0x0, "_ZN13CFuncRotating10ObjectCapsEv", mfunc_ptr_cast(&CFuncRotating::ObjectCaps_) },
	//{ 0x0, "_ZN13CFuncRotating7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CFuncRotating::Blocked_) },
	//non-virtual func
	//{ 0x0, "_ZN13CFuncRotating6SpinUpEv", mfunc_ptr_cast(&CFuncRotating::SpinUp) },
	//{ 0x0, "_ZN13CFuncRotating8SpinDownEv", mfunc_ptr_cast(&CFuncRotating::SpinDown) },
	//{ 0x0, "_ZN13CFuncRotating9HurtTouchEP11CBaseEntity", mfunc_ptr_cast(&CFuncRotating::HurtTouch) },
	//{ 0x0, "_ZN13CFuncRotating11RotatingUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncRotating::RotatingUse) },
	//{ 0x0, "_ZN13CFuncRotating6RotateEv", mfunc_ptr_cast(&CFuncRotating::Rotate) },
	//{ 0x0, "_ZN13CFuncRotating12RampPitchVolEi", mfunc_ptr_cast(&CFuncRotating::RampPitchVol) },
//CPendulum
	//virtual func
	//{ 0x0, "_ZN9CPendulum5SpawnEv", mfunc_ptr_cast(&CPendulum::Spawn_) },
	//{ 0x0, "_ZN9CPendulum8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CPendulum::KeyValue_) },
	//{ 0x0, "_ZN9CPendulum4SaveER5CSave", mfunc_ptr_cast(&CPendulum::Save_) },
	//{ 0x0, "_ZN9CPendulum7RestoreER8CRestore", mfunc_ptr_cast(&CPendulum::Restore_) },
	//{ 0x0, "_ZN9CPendulum10ObjectCapsEv", mfunc_ptr_cast(&CPendulum::ObjectCaps_) },
	//{ 0x0, "_ZN9CPendulum5TouchEP11CBaseEntity", mfunc_ptr_cast(&CPendulum::Touch_) },
	//{ 0x0, "_ZN9CPendulum7BlockedEP11CBaseEntity", mfunc_ptr_cast(&CPendulum::Blocked_) },
	//non-virtual func
	//{ 0x0, "_ZN9CPendulum5SwingEv", mfunc_ptr_cast(&CPendulum::Swing) },
	//{ 0x0, "_ZN9CPendulum11PendulumUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CPendulum::PendulumUse) },
	//{ 0x0, "_ZN9CPendulum4StopEv", mfunc_ptr_cast(&CPendulum::Stop) },
	//{ 0x0, "_ZN9CPendulum9RopeTouchEP11CBaseEntity", mfunc_ptr_cast(&CPendulum::RopeTouch) },

	{ 0x01D5CF20, "_Z15VecBModelOriginP9entvars_s", (size_t)&VecBModelOrigin },

#endif // BModels_Region

#ifndef Button_Region

//CEnvGlobal
	//virtual func
	//{ 0x0, "_ZN10CEnvGlobal5SpawnEv", mfunc_ptr_cast(&CEnvGlobal::Spawn_) },
	//{ 0x0, "_ZN10CEnvGlobal8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CEnvGlobal::KeyValue_) },
	//{ 0x0, "_ZN10CEnvGlobal4SaveER5CSave", mfunc_ptr_cast(&CEnvGlobal::Save_) },
	//{ 0x0, "_ZN10CEnvGlobal7RestoreER8CRestore", mfunc_ptr_cast(&CEnvGlobal::Restore_) },
	//{ 0x0, "_ZN10CEnvGlobal3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CEnvGlobal::Use_) },
//CMultiSource
	//virtual func
	//{ 0x0, "_ZN12CMultiSource5SpawnEv", mfunc_ptr_cast(&CMultiSource::Spawn_) },
	//{ 0x0, "_ZN12CMultiSource8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CMultiSource::KeyValue_) },
	//{ 0x0, "_ZN12CMultiSource3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CMultiSource::Use_) },
	//{ 0x0, "_ZN12CMultiSource10ObjectCapsEv", mfunc_ptr_cast(&CMultiSource::ObjectCaps_) },
	//{ 0x0, "_ZN12CMultiSource11IsTriggeredEP11CBaseEntity", mfunc_ptr_cast(&CMultiSource::IsTriggered_) },
	//{ 0x0, "_ZN12CMultiSource4SaveER5CSave", mfunc_ptr_cast(&CMultiSource::Save_) },
	//{ 0x0, "_ZN12CMultiSource7RestoreER8CRestore", mfunc_ptr_cast(&CMultiSource::Restore_) },
	//non-virtual func
	//{ 0x0, "_ZN12CMultiSource8RegisterEv", mfunc_ptr_cast(&CMultiSource::Register) },
//CBaseButton
	//virtual func
	//{ 0x0, "_ZN11CBaseButton5SpawnEv", mfunc_ptr_cast(&CBaseButton::Spawn_) },
	//{ 0x0, "_ZN11CBaseButton8PrecacheEv", mfunc_ptr_cast(&CBaseButton::Precache_) },
	//{ 0x01D5F7D0, "_ZN11CBaseButton8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseButton::KeyValue_) },
	//{ 0x0, "_ZN11CBaseButton4SaveER5CSave", mfunc_ptr_cast(&CBaseButton::Save_) },
	//{ 0x0, "_ZN11CBaseButton7RestoreER8CRestore", mfunc_ptr_cast(&CBaseButton::Restore_) },
	//{ 0x0, "_ZN11CBaseButton10ObjectCapsEv", mfunc_ptr_cast(&CBaseButton::ObjectCaps_) },
	//{ 0x0, "_ZN11CBaseButton10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBaseButton::TakeDamage_) },
	//non-virtual func
	//{ 0x0, "_ZN11CBaseButton8RotSpawnEv", mfunc_ptr_cast(&CBaseButton::RotSpawn) },
	//{ 0x0, "_ZN11CBaseButton14ButtonActivateEv", mfunc_ptr_cast(&CBaseButton::ButtonActivate) },
	//{ 0x0, "_ZN11CBaseButton15SparkSoundCacheEv", mfunc_ptr_cast(&CBaseButton::SparkSoundCache) },
	//{ 0x0, "_ZN11CBaseButton10ButtonShotEv", mfunc_ptr_cast(&CBaseButton::ButtonShot) },
	//{ 0x0, "_ZN11CBaseButton11ButtonTouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseButton::ButtonTouch) },
	//{ 0x0, "_ZN11CBaseButton11ButtonSparkEv", mfunc_ptr_cast(&CBaseButton::ButtonSpark) },
	//{ 0x0, "_ZN11CBaseButton14TriggerAndWaitEv", mfunc_ptr_cast(&CBaseButton::TriggerAndWait) },
	//{ 0x0, "_ZN11CBaseButton12ButtonReturnEv", mfunc_ptr_cast(&CBaseButton::ButtonReturn) },
	//{ 0x0, "_ZN11CBaseButton14ButtonBackHomeEv", mfunc_ptr_cast(&CBaseButton::ButtonBackHome) },
	//{ 0x0, "_ZN11CBaseButton9ButtonUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBaseButton::ButtonUse) },
	//{ 0x0, "_ZN11CBaseButton21ButtonResponseToTouchEv", mfunc_ptr_cast(&CBaseButton::ButtonResponseToTouch) },
//CRotButton
	//virtual func
	//{ 0x0, "_ZN10CRotButton5SpawnEv", mfunc_ptr_cast(&CRotButton::Spawn_) },
//CMomentaryRotButton
	//virtual func
	//{ 0x0, "_ZN19CMomentaryRotButton5SpawnEv", mfunc_ptr_cast(&CMomentaryRotButton::Spawn_) },
	//{ 0x0, "_ZN19CMomentaryRotButton8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CMomentaryRotButton::KeyValue_) },
	//{ 0x0, "_ZN19CMomentaryRotButton4SaveER5CSave", mfunc_ptr_cast(&CMomentaryRotButton::Save_) },
	//{ 0x0, "_ZN19CMomentaryRotButton7RestoreER8CRestore", mfunc_ptr_cast(&CMomentaryRotButton::Restore_) },
	//{ 0x0, "_ZN19CMomentaryRotButton10ObjectCapsEv", mfunc_ptr_cast(&CMomentaryRotButton::ObjectCaps_) },
	//{ 0x0, "_ZN19CMomentaryRotButton3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CMomentaryRotButton::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN19CMomentaryRotButton3OffEv", mfunc_ptr_cast(&CMomentaryRotButton::Off) },
	//{ 0x0, "_ZN19CMomentaryRotButton6ReturnEv", mfunc_ptr_cast(&CMomentaryRotButton::Return) },
	//{ 0x0, "_ZN19CMomentaryRotButton10UpdateSelfEf", mfunc_ptr_cast(&CMomentaryRotButton::UpdateSelf) },
	//{ 0x0, "_ZN19CMomentaryRotButton16UpdateSelfReturnEf", mfunc_ptr_cast(&CMomentaryRotButton::UpdateSelfReturn) },
	//{ 0x0, "_ZN19CMomentaryRotButton16UpdateAllButtonsEfi", mfunc_ptr_cast(&CMomentaryRotButton::UpdateAllButtons) },
	//{ 0x0, "_ZN19CMomentaryRotButton9PlaySoundEv", mfunc_ptr_cast(&CMomentaryRotButton::PlaySound) },
	//{ 0x0, "_ZN19CMomentaryRotButton12UpdateTargetEf", mfunc_ptr_cast(&CMomentaryRotButton::UpdateTarget) },
	//{ 0x0, "_ZN19CMomentaryRotButton8InstanceEP7edict_s", mfunc_ptr_cast(&CMomentaryRotButton::Instance) },		// NOXREF
//CEnvSpark
	//virtual func
	//{ 0x0, "_ZN9CEnvSpark5SpawnEv", mfunc_ptr_cast(&CEnvSpark::Spawn_) },
	//{ 0x0, "_ZN9CEnvSpark8PrecacheEv", mfunc_ptr_cast(&CEnvSpark::Precache_) },
	//{ 0x0, "_ZN9CEnvSpark8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CEnvSpark::KeyValue_) },
	//{ 0x0, "_ZN9CEnvSpark4SaveER5CSave", mfunc_ptr_cast(&CEnvSpark::Save_) },
	//{ 0x0, "_ZN9CEnvSpark7RestoreER8CRestore", mfunc_ptr_cast(&CEnvSpark::Restore_) },
	//non-virtual func
	//{ 0x0, "_ZN9CEnvSpark10SparkThinkEv", mfunc_ptr_cast(&CEnvSpark::SparkThink) },
	//{ 0x0, "_ZN9CEnvSpark10SparkStartEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CEnvSpark::SparkStart) },
	//{ 0x0, "_ZN9CEnvSpark9SparkStopEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CEnvSpark::SparkStop) },
//CButtonTarget
	//virtual func
	//{ 0x0, "_ZN13CButtonTarget5SpawnEv", mfunc_ptr_cast(&CButtonTarget::Spawn_) },
	//{ 0x0, "_ZN13CButtonTarget10ObjectCapsEv", mfunc_ptr_cast(&CButtonTarget::ObjectCaps_) },
	//{ 0x0, "_ZN13CButtonTarget10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CButtonTarget::TakeDamage_) },
	//{ 0x0, "_ZN13CButtonTarget3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CButtonTarget::Use_) },

#endif // Button_Region

#ifndef Explode_Region

//CShower
	//virtual func
	{ 0x01D7B960, "_ZN7CShower5SpawnEv", mfunc_ptr_cast(&CShower::Spawn_) },
	{ 0x01D7B950, "_ZN7CShower10ObjectCapsEv", mfunc_ptr_cast(&CShower::ObjectCaps_) },
	{ 0x01D7BAD0, "_ZN7CShower5ThinkEv", mfunc_ptr_cast(&CShower::Think_) },
	{ 0x01D7BB60, "_ZN7CShower5TouchEP11CBaseEntity", mfunc_ptr_cast(&CShower::Touch_) },
	//linked objects
	{ 0x01D7B900, "spark_shower", (size_t)&spark_shower },
//CEnvExplosion
	//virtual func
	{ 0x01D7BD10, "_ZN13CEnvExplosion5SpawnEv", mfunc_ptr_cast(&CEnvExplosion::Spawn_) },
	{ 0x01D7BCC0, "_ZN13CEnvExplosion8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CEnvExplosion::KeyValue_) },
	{ 0x01D7BC10, "_ZN13CEnvExplosion4SaveER5CSave", mfunc_ptr_cast(&CEnvExplosion::Save_) },
	{ 0x01D7BC40, "_ZN13CEnvExplosion7RestoreER8CRestore", mfunc_ptr_cast(&CEnvExplosion::Restore_) },
	{ 0x01D7BD70, "_ZN13CEnvExplosion3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CEnvExplosion::Use_) },
	//non-virtual func
	{ 0x01D7C040, "_ZN13CEnvExplosion5SmokeEv", mfunc_ptr_cast(&CEnvExplosion::Smoke) },
	{ 0x01D7C0E0, "_Z15ExplosionCreateRK6VectorS1_P7edict_sii", (size_t)&ExplosionCreate },
	//linked objects
	{ 0x01D7BC70, "env_explosion", (size_t)&env_explosion },

#endif // Explode_Region

#ifndef Mortar_Region

//CFuncMortarField
	//virtual func
	{ 0x01D8A610, "_ZN16CFuncMortarField5SpawnEv", mfunc_ptr_cast(&CFuncMortarField::Spawn_) },
	{ 0x01D8A680, "_ZN16CFuncMortarField8PrecacheEv", mfunc_ptr_cast(&CFuncMortarField::Precache_) },
	{ 0x01D8A500, "_ZN16CFuncMortarField8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncMortarField::KeyValue_) },
	{ 0x01D8A4A0, "_ZN16CFuncMortarField4SaveER5CSave", mfunc_ptr_cast(&CFuncMortarField::Save_) },
	{ 0x01D8A4D0, "_ZN16CFuncMortarField7RestoreER8CRestore", mfunc_ptr_cast(&CFuncMortarField::Restore_) },
	{ 0x01D8A490, "_ZN16CFuncMortarField10ObjectCapsEv", mfunc_ptr_cast(&CFuncMortarField::ObjectCaps_) },
	//non-virtual func
	{ 0x01D8A6B0, "_ZN16CFuncMortarField8FieldUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CFuncMortarField::FieldUse) },
	//linked objects
	{ 0x01D8A440, "func_mortar_field", (size_t)&func_mortar_field },
//CMortar
	//virtual func
	{ 0x01D8A990, "_ZN7CMortar5SpawnEv", mfunc_ptr_cast(&CMortar::Spawn_) },
	{ 0x01D8A9D0, "_ZN7CMortar8PrecacheEv", mfunc_ptr_cast(&CMortar::Precache_) },
	//non-virtual func
	{ 0x01D8A9F0, "_ZN7CMortar13MortarExplodeEv", mfunc_ptr_cast(&CMortar::MortarExplode) },
	//linked objects
	{ 0x01D8A940, "monster_mortar", (size_t)&monster_mortar },

#endif // Mortar_Region

#ifndef Healkit_Region

//CHealthKit
	//virtual func
	{ 0x01D867A0, "_ZN10CHealthKit5SpawnEv", mfunc_ptr_cast(&CHealthKit::Spawn_) },
	{ 0x01D867D0, "_ZN10CHealthKit8PrecacheEv", mfunc_ptr_cast(&CHealthKit::Precache_) },
	{ 0x01D867F0, "_ZN10CHealthKit7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CHealthKit::MyTouch_) },

//CWallHealth
	//virtual func
	{ 0x01D86A30, "_ZN11CWallHealth5SpawnEv", mfunc_ptr_cast(&CWallHealth::Spawn_) },
	{ 0x01D86AC0, "_ZN11CWallHealth8PrecacheEv", mfunc_ptr_cast(&CWallHealth::Precache_) },
	{ 0x01D86980, "_ZN11CWallHealth8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CWallHealth::KeyValue_) },
	{ 0x01D868C0, "_ZN11CWallHealth4SaveER5CSave", mfunc_ptr_cast(&CWallHealth::Save_) },
	{ 0x01D868F0, "_ZN11CWallHealth7RestoreER8CRestore", mfunc_ptr_cast(&CWallHealth::Restore_) },
	{ 0x01D86970, "_ZN11CWallHealth10ObjectCapsEv", mfunc_ptr_cast(&CWallHealth::ObjectCaps_) },
	{ 0x01D86AF0, "_ZN11CWallHealth3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CWallHealth::Use_) },
	//non-virtual func
	{ 0x01D86D90, "_ZN11CWallHealth3OffEv", mfunc_ptr_cast(&CWallHealth::Off) },
	{ 0x01D86D30, "_ZN11CWallHealth8RechargeEv", mfunc_ptr_cast(&CWallHealth::Recharge) },

#endif // Healkit_Region

#ifndef Lights_Region

//CLight
	//virtual func
	{ 0x01D88790, "_ZN6CLight5SpawnEv", mfunc_ptr_cast(&CLight::Spawn_) },
	{ 0x01D88830, "_ZN6CLight7RestartEv", mfunc_ptr_cast(&CLight::Restart_) },
	{ 0x01D88670, "_ZN6CLight4SaveER5CSave", mfunc_ptr_cast(&CLight::Save_) },
	{ 0x01D886A0, "_ZN6CLight7RestoreER8CRestore", mfunc_ptr_cast(&CLight::Restore_) },
	{ 0x01D886D0, "_ZN6CLight8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CLight::KeyValue_) },
	{ 0x01D888C0, "_ZN6CLight3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CLight::Use_) },
//CEnvLight
	//virtual func
	{ 0x01D88BB0, "_ZN9CEnvLight5SpawnEv", mfunc_ptr_cast(&CEnvLight::Spawn_) },
	{ 0x01D88A20, "_ZN9CEnvLight8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CEnvLight::KeyValue_) },

#endif // Lights_Region

#ifndef MapRules_Region

//CRuleEntity
	//virtual func
	//{ 0x0, "_ZN11CRuleEntity5SpawnEv", mfunc_ptr_cast(&CRuleEntity::Spawn_) },
	//{ 0x0, "_ZN11CRuleEntity8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CRuleEntity::KeyValue_) },
	//{ 0x0, "_ZN11CRuleEntity4SaveER5CSave", mfunc_ptr_cast(&CRuleEntity::Save_) },
	//{ 0x0, "_ZN11CRuleEntity7RestoreER8CRestore", mfunc_ptr_cast(&CRuleEntity::Restore_) },
	//non-virtual func
	//{ 0x0, "_ZN11CRuleEntity9SetMasterEi", mfunc_ptr_cast(&CRuleEntity::SetMaster) },					// NOXREF
	//{ 0x0, "_ZN11CRuleEntity19CanFireForActivatorEP11CBaseEntity", mfunc_ptr_cast(&CRuleEntity::CanFireForActivator) },
//CRulePointEntity
	//virtual func
	//{ 0x0, "_ZN16CRulePointEntity5SpawnEv", mfunc_ptr_cast(&CRulePointEntity::Spawn_) },
//CRuleBrushEntity
	//virtual func
	//{ 0x0, "_ZN16CRuleBrushEntity5SpawnEv", mfunc_ptr_cast(&CRuleBrushEntity::Spawn_) },
//CGameScore
	//virtual func
	//{ 0x0, "_ZN10CGameScore5SpawnEv", mfunc_ptr_cast(&CGameScore::Spawn_) },
	//{ 0x0, "_ZN10CGameScore8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CGameScore::KeyValue_) },
	//{ 0x0, "_ZN10CGameScore3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameScore::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN10CGameScore6PointsEv", mfunc_ptr_cast(&CGameScore::Points) },			// NOXREF
	//{ 0x0, "_ZN10CGameScore18AllowNegativeScoreEv", mfunc_ptr_cast(&CGameScore::AllowNegativeScore) },			// NOXREF
	//{ 0x0, "_ZN10CGameScore11AwardToTeamEv", mfunc_ptr_cast(&CGameScore::AwardToTeam) },			// NOXREF
	//{ 0x0, "_ZN10CGameScore9SetPointsEi", mfunc_ptr_cast(&CGameScore::SetPoints) },			// NOXREF
//CGameEnd
	//{ 0x0, "_ZN8CGameEnd3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameEnd::Use_) },
//CGameText
	//virtual func
	//{ 0x0, "_ZN9CGameText8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CGameText::KeyValue_) },
	//{ 0x0, "_ZN9CGameText4SaveER5CSave", mfunc_ptr_cast(&CGameText::Save_) },
	//{ 0x0, "_ZN9CGameText7RestoreER8CRestore", mfunc_ptr_cast(&CGameText::Restore_) },
	//{ 0x0, "_ZN9CGameText3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameText::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN9CGameText12MessageToAllEv", mfunc_ptr_cast(&CGameText::MessageToAll) },			// NOXREF
	//{ 0x0, "_ZN9CGameText10MessageSetEPKc", mfunc_ptr_cast(&CGameText::MessageSet) },			// NOXREF
	//{ 0x0, "_ZN9CGameText10MessageGetEv", mfunc_ptr_cast(&CGameText::MessageGet) },			// NOXREF
//CGameTeamMaster
	//virtual func
	//{ 0x0, "_ZN15CGameTeamMaster8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CGameTeamMaster::KeyValue_) },
	//{ 0x0, "_ZN15CGameTeamMaster10ObjectCapsEv", mfunc_ptr_cast(&CGameTeamMaster::ObjectCaps_) },
	//{ 0x0, "_ZN15CGameTeamMaster11IsTriggeredEP11CBaseEntity", mfunc_ptr_cast(&CGameTeamMaster::IsTriggered_) },
	//{ 0x0, "_ZN15CGameTeamMaster6TeamIDEv", mfunc_ptr_cast(&CGameTeamMaster::TeamID_) },
	//{ 0x0, "_ZN15CGameTeamMaster3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameTeamMaster::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN15CGameTeamMaster12RemoveOnFireEv", mfunc_ptr_cast(&CGameTeamMaster::RemoveOnFire) },		// NOXREF
	//{ 0x0, "_ZN15CGameTeamMaster7AnyTeamEv", mfunc_ptr_cast(&CGameTeamMaster::AnyTeam) },			// NOXREF
	//{ 0x0, "_ZN15CGameTeamMaster9TeamMatchEP11CBaseEntity", mfunc_ptr_cast(&CGameTeamMaster::TeamMatch) },
//CGameTeamSet
	//virtual func
	//{ 0x0, "_ZN12CGameTeamSet3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameTeamSet::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN12CGameTeamSet12RemoveOnFireEv", mfunc_ptr_cast(&CGameTeamSet::RemoveOnFire) },		// NOXREF
	//{ 0x0, "_ZN12CGameTeamSet15ShouldClearTeamEv", mfunc_ptr_cast(&CGameTeamSet::ShouldClearTeam) },			// NOXREF
//CGamePlayerZone
	//virtual func
	//{ 0x0, "_ZN15CGamePlayerZone8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CGamePlayerZone::KeyValue_) },
	//{ 0x0, "_ZN15CGamePlayerZone4SaveER5CSave", mfunc_ptr_cast(&CGamePlayerZone::Save_) },
	//{ 0x0, "_ZN15CGamePlayerZone7RestoreER8CRestore", mfunc_ptr_cast(&CGamePlayerZone::Restore_) },
	//{ 0x0, "_ZN15CGamePlayerZone3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGamePlayerZone::Use_) },
//CGamePlayerHurt
	//virtual func
	//{ 0x0, "_ZN15CGamePlayerHurt3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGamePlayerHurt::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN15CGamePlayerHurt12RemoveOnFireEv", mfunc_ptr_cast(&CGamePlayerHurt::RemoveOnFire) },		// NOXREF
//CGameCounter
	//virtual func
	//{ 0x0, "_ZN12CGameCounter5SpawnEv", mfunc_ptr_cast(&CGameCounter::Spawn) },
	//{ 0x0, "_ZN12CGameCounter3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameCounter::Use) },
	//non-virtual func
	//{ 0x0, "_ZN12CGameCounter12RemoveOnFireEv", mfunc_ptr_cast(&CGameCounter::RemoveOnFire) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter11ResetOnFireEv", mfunc_ptr_cast(&CGameCounter::ResetOnFire) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter7CountUpEv", mfunc_ptr_cast(&CGameCounter::CountUp) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter9CountDownEv", mfunc_ptr_cast(&CGameCounter::CountDown) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter10ResetCountEv", mfunc_ptr_cast(&CGameCounter::ResetCount) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter10CountValueEv", mfunc_ptr_cast(&CGameCounter::CountValue) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter10LimitValueEv", mfunc_ptr_cast(&CGameCounter::LimitValue) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter8HitLimitEv", mfunc_ptr_cast(&CGameCounter::HitLimit) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter13SetCountValueEi", mfunc_ptr_cast(&CGameCounter::SetCountValue) },		// NOXREF
	//{ 0x0, "_ZN12CGameCounter15SetInitialValueEi", mfunc_ptr_cast(&CGameCounter::SetInitialValue) },		// NOXREF
//CGameCounterSet
	//virtual func
	//{ 0x0, "_ZN15CGameCounterSet3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGameCounterSet::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN15CGameCounterSet12RemoveOnFireEv", mfunc_ptr_cast(&CGameCounterSet::RemoveOnFire) },		// NOXREF
//CGamePlayerEquip
	//virtual func
	//{ 0x0, "_ZN16CGamePlayerEquip8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CGamePlayerEquip::KeyValue_) },
	//{ 0x0, "_ZN16CGamePlayerEquip5TouchEP11CBaseEntity", mfunc_ptr_cast(&CGamePlayerEquip::Touch_) },
	//{ 0x0, "_ZN16CGamePlayerEquip3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGamePlayerEquip::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN16CGamePlayerEquip7UseOnlyEv", mfunc_ptr_cast(&CGamePlayerEquip::UseOnly) },			// NOXREF
	//{ 0x0, "_ZN16CGamePlayerEquip11EquipPlayerEP11CBaseEntity", mfunc_ptr_cast(&CGamePlayerEquip::EquipPlayer) },
//CGamePlayerTeam
	//virtual func
	//{ 0x0, "_ZN15CGamePlayerTeam3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGamePlayerTeam::Use) },
	//non-virtual func
	//{ 0x0, "_ZN15CGamePlayerTeam12RemoveOnFireEv", mfunc_ptr_cast(&CGamePlayerTeam::RemoveOnFire) },
	//{ 0x0, "_ZN15CGamePlayerTeam16ShouldKillPlayerEv", mfunc_ptr_cast(&CGamePlayerTeam::ShouldKillPlayer) },
	//{ 0x0, "_ZN15CGamePlayerTeam15ShouldGibPlayerEv", mfunc_ptr_cast(&CGamePlayerTeam::ShouldGibPlayer) },
	//{ 0x0, "_ZN15CGamePlayerTeam14TargetTeamNameEPKc", mfunc_ptr_cast(&CGamePlayerTeam::TargetTeamName) },

#endif // MapRules_Region

#ifndef HintMessage_Region

//CHintMessage
	//{ 0x0, "_ZNK12CHintMessage11GetDurationEv", mfunc_ptr_cast(&CHintMessage::GetDuration) },	// NOXREF
	//{ 0x0, "_ZN12CHintMessage4SendER11CBaseEntity", mfunc_ptr_cast(&CHintMessage::Send) },	// NOXREF

//CHintMessageQueue
	{ 0x01D86FC0, "_ZN17CHintMessageQueue5ResetEv", mfunc_ptr_cast(&CHintMessageQueue::Reset) },
	{ 0x01D87050, "_ZN17CHintMessageQueue6UpdateER11CBaseEntity", mfunc_ptr_cast(&CHintMessageQueue::Update) },
	{ 0x01D87120, "_ZN17CHintMessageQueue10AddMessageEPKcfbP10CUtlVectorIS1_E", mfunc_ptr_cast(&CHintMessageQueue::AddMessage) },
	//{ 0x0, "_ZN17CHintMessageQueue7IsEmptyEv", mfunc_ptr_cast(&CHintMessageQueue::IsEmpty) },

#endif // HintMessage_Region

#ifndef Items_Region

//CItem
	//virtual func
	{ 0x01D87570, "_ZN5CItem5SpawnEv", mfunc_ptr_cast(&CItem::Spawn_) },
	{ 0x01D876C0, "_ZN5CItem7RespawnEv", mfunc_ptr_cast(&CItem::Respawn_) },
	//{ 0x0, "_ZN5CItem7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItem::MyTouch_) },	// NOXREF
	//non-virtual func
	{ 0x01D87610, "_ZN5CItem9ItemTouchEP11CBaseEntity", mfunc_ptr_cast(&CItem::ItemTouch) },
	{ 0x01D87730, "_ZN5CItem11MaterializeEv", mfunc_ptr_cast(&CItem::Materialize) },
//CWorldItem
	//virtual func
	{ 0x01D874A0, "_ZN10CWorldItem5SpawnEv", mfunc_ptr_cast(&CWorldItem::Spawn_) },
	{ 0x01D87450, "_ZN10CWorldItem8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CWorldItem::KeyValue_) },
//CItemSuit
	//virtual func
	{ 0x01D877F0, "_ZN9CItemSuit5SpawnEv", mfunc_ptr_cast(&CItemSuit::Spawn_) },
	{ 0x01D878B0, "_ZN9CItemSuit8PrecacheEv", mfunc_ptr_cast(&CItemSuit::Precache_) },
	{ 0x01D878D0, "_ZN9CItemSuit7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemSuit::MyTouch_) },
//CItemBattery
	//virtual func
	{ 0x01D87990, "_ZN12CItemBattery5SpawnEv", mfunc_ptr_cast(&CItemBattery::Spawn_) },
	{ 0x01D87A50, "_ZN12CItemBattery8PrecacheEv", mfunc_ptr_cast(&CItemBattery::Precache_) },
	{ 0x01D87A70, "_ZN12CItemBattery7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemBattery::MyTouch_) },
//CItemAntidote
	//virtual func
	{ 0x01D87C10, "_ZN13CItemAntidote5SpawnEv", mfunc_ptr_cast(&CItemAntidote::Spawn_) },
	{ 0x01D87CD0, "_ZN13CItemAntidote8PrecacheEv", mfunc_ptr_cast(&CItemAntidote::Precache_) },
	{ 0x01D87CE0, "_ZN13CItemAntidote7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemAntidote::MyTouch_) },
//CItemSecurity
	//virtual func
	{ 0x01D87D60, "_ZN13CItemSecurity5SpawnEv", mfunc_ptr_cast(&CItemSecurity::Spawn_) },
	{ 0x01D87E20, "_ZN13CItemSecurity8PrecacheEv", mfunc_ptr_cast(&CItemSecurity::Precache_) },
	{ 0x01D87E30, "_ZN13CItemSecurity7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemSecurity::MyTouch_) },
//CItemLongJump
	//virtual func
	{ 0x01D87EA0, "_ZN13CItemLongJump5SpawnEv", mfunc_ptr_cast(&CItemLongJump::Spawn_) },
	{ 0x01D87F60, "_ZN13CItemLongJump8PrecacheEv", mfunc_ptr_cast(&CItemLongJump::Precache_) },
	{ 0x01D87F70, "_ZN13CItemLongJump7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemLongJump::MyTouch_) },
//CItemKevlar
	//virtual func
	{ 0x01D88070, "_ZN11CItemKevlar5SpawnEv", mfunc_ptr_cast(&CItemKevlar::Spawn_) },
	{ 0x01D88130, "_ZN11CItemKevlar8PrecacheEv", mfunc_ptr_cast(&CItemKevlar::Precache_) },
	{ 0x01D88140, "_ZN11CItemKevlar7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemKevlar::MyTouch_) },
//CItemAssaultSuit
	//virtual func
	{ 0x01D88270, "_ZN16CItemAssaultSuit5SpawnEv", mfunc_ptr_cast(&CItemAssaultSuit::Spawn_) },
	{ 0x01D88330, "_ZN16CItemAssaultSuit8PrecacheEv", mfunc_ptr_cast(&CItemAssaultSuit::Precache_) },
	{ 0x01D88340, "_ZN16CItemAssaultSuit7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemAssaultSuit::MyTouch_) },
//CItemThighPack
	//virtual func
	{ 0x01D88460, "_ZN14CItemThighPack5SpawnEv", mfunc_ptr_cast(&CItemThighPack::Spawn_) },
	{ 0x01D88520, "_ZN14CItemThighPack8PrecacheEv", mfunc_ptr_cast(&CItemThighPack::Precache_) },
	{ 0x01D88530, "_ZN14CItemThighPack7MyTouchEP11CBasePlayer", mfunc_ptr_cast(&CItemThighPack::MyTouch_) },

#endif // Items_Region

#ifndef Triggers_Region

//CFrictionModifier
	//virtual func
	//{ 0x0, "_ZN17CFrictionModifier5SpawnEv", mfunc_ptr_cast(&CFrictionModifier::Spawn_) },
	//{ 0x0, "_ZN17CFrictionModifier8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFrictionModifier::KeyValue_) },
	//{ 0x0, "_ZN17CFrictionModifier4SaveER5CSave", mfunc_ptr_cast(&CFrictionModifier::Save_) },
	//{ 0x0, "_ZN17CFrictionModifier7RestoreER8CRestore", mfunc_ptr_cast(&CFrictionModifier::Restore_) },
	//{ 0x0, "_ZN17CFrictionModifier10ObjectCapsEv", mfunc_ptr_cast(&CFrictionModifier::ObjectCaps_) },
	//non-virtual func
	//{ 0x01DBD0E0, "func_friction", (size_t)&func_friction },
	//{ 0x0, "_ZN17CFrictionModifier14ChangeFrictionEP11CBaseEntity", mfunc_ptr_cast(&CFrictionModifier::ChangeFriction) },
//CAutoTrigger
	//virtual func
	//{ 0x0, "_ZN12CAutoTrigger5SpawnEv", mfunc_ptr_cast(&CAutoTrigger::Spawn_) },
	//{ 0x0, "_ZN12CAutoTrigger8PrecacheEv", mfunc_ptr_cast(&CAutoTrigger::Precache_) },
	//{ 0x01DBD340, "_ZN12CAutoTrigger8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CAutoTrigger::KeyValue_) },
	//{ 0x0, "_ZN12CAutoTrigger10ObjectCapsEv", mfunc_ptr_cast(&CAutoTrigger::ObjectCaps_) },
	//{ 0x0, "_ZN12CAutoTrigger4SaveER5CSave", mfunc_ptr_cast(&CAutoTrigger::Save_) },
	//{ 0x0, "_ZN12CAutoTrigger7RestoreER8CRestore", mfunc_ptr_cast(&CAutoTrigger::Restore_) },
	//{ 0x0, "_ZN12CAutoTrigger5ThinkEv", mfunc_ptr_cast(&CAutoTrigger::Think_) },
	//non-virtual func
	//{ 0x01DBD280, "trigger_auto", (size_t)&trigger_auto },
//CTriggerRelay
	//virtual func
	//{ 0x0, "_ZN13CTriggerRelay5SpawnEv", mfunc_ptr_cast(&CTriggerRelay::Spawn_) },
	//{ 0x0, "_ZN13CTriggerRelay8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CTriggerRelay::KeyValue_) },
	//{ 0x0, "_ZN13CTriggerRelay4SaveER5CSave", mfunc_ptr_cast(&CTriggerRelay::Save_) },
	//{ 0x0, "_ZN13CTriggerRelay7RestoreER8CRestore", mfunc_ptr_cast(&CTriggerRelay::Restore_) },
	//{ 0x0, "_ZN13CTriggerRelay10ObjectCapsEv", mfunc_ptr_cast(&CTriggerRelay::ObjectCaps_) },
	//{ 0x0, "_ZN13CTriggerRelay3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTriggerRelay::Use_) },
	//non-virtual func
	//{ 0x01DBD480, "trigger_relay", (size_t)&trigger_relay },
//CMultiManager
	//virtual func
	//{ 0x0, "_ZN13CMultiManager5SpawnEv", mfunc_ptr_cast(&CMultiManager::Spawn_) },
	//{ 0x0, "_ZN13CMultiManager7RestartEv", mfunc_ptr_cast(&CMultiManager::Restart_) },
	//{ 0x0, "_ZN13CMultiManager8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CMultiManager::KeyValue_) },
	//{ 0x0, "_ZN13CMultiManager4SaveER5CSave", mfunc_ptr_cast(&CMultiManager::Save_) },
	//{ 0x0, "_ZN13CMultiManager7RestoreER8CRestore", mfunc_ptr_cast(&CMultiManager::Restore_) },
	//{ 0x0, "_ZN13CMultiManager10ObjectCapsEv", mfunc_ptr_cast(&CMultiManager::ObjectCaps_) },
	//{ 0x0, "_ZN13CMultiManager9HasTargetEj", mfunc_ptr_cast(&CMultiManager::HasTarget_) },
	//non-virtual func
	//{ 0x01DBD600, "multi_manager", (size_t)&multi_manager },
	//{ 0x0, "_ZN13CMultiManager12ManagerThinkEv", mfunc_ptr_cast(&CMultiManager::ManagerThink) },
	//{ 0x0, "_ZN13CMultiManager10ManagerUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CMultiManager::ManagerUse) },
	//{ 0x0, "_ZN13CMultiManager5CloneEv", mfunc_ptr_cast(&CMultiManager::Clone) }, // NOXREF
//CRenderFxManager
	//virtual func
	//{ 0x0, "_ZN16CRenderFxManager5SpawnEv", mfunc_ptr_cast(&CRenderFxManager::Spawn_) },
	//{ 0x0, "_ZN16CRenderFxManager3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CRenderFxManager::Use_) },
	//non-virtual func
	//{ 0x01DBDBF0, "env_render", (size_t)&env_render },
//CBaseTrigger
	//virtual func
	//{ 0x0, "_ZN12CBaseTrigger8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseTrigger::KeyValue_) },
	//{ 0x0, "_ZN12CBaseTrigger10ObjectCapsEv", mfunc_ptr_cast(&CBaseTrigger::ObjectCaps_) },
	//non-virtual func
	//{ 0x01DBDD30, "trigger", (size_t)&trigger },
	//{ 0x0, "_ZN12CBaseTrigger13TeleportTouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseTrigger::TeleportTouch) },
	//{ 0x0, "_ZN12CBaseTrigger10MultiTouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseTrigger::MultiTouch) },
	//{ 0x0, "_ZN12CBaseTrigger9HurtTouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseTrigger::HurtTouch) },
	//{ 0x0, "_ZN12CBaseTrigger12CDAudioTouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseTrigger::CDAudioTouch) }, // NOXREF
	//{ 0x0, "_ZN12CBaseTrigger20ActivateMultiTriggerEP11CBaseEntity", mfunc_ptr_cast(&CBaseTrigger::ActivateMultiTrigger) },
	//{ 0x0, "_ZN12CBaseTrigger13MultiWaitOverEv", mfunc_ptr_cast(&CBaseTrigger::MultiWaitOver) },
	//{ 0x0, "_ZN12CBaseTrigger10CounterUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBaseTrigger::CounterUse) },
	//{ 0x0, "_ZN12CBaseTrigger9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBaseTrigger::ToggleUse) },
	//{ 0x0, "_ZN12CBaseTrigger11InitTriggerEv", mfunc_ptr_cast(&CBaseTrigger::InitTrigger) },
//CTriggerHurt
	//virtual func
	//{ 0x0, "_ZN12CTriggerHurt5SpawnEv", mfunc_ptr_cast(&CTriggerHurt::Spawn_) },
	//non-virtual func
	//{ 0x01DBDF00, "trigger_hurt", (size_t)&trigger_hurt },
	//{ 0x0, "_ZN12CTriggerHurt14RadiationThinkEv", mfunc_ptr_cast(&CTriggerHurt::RadiationThink) },
//CTriggerMonsterJump
	//virtual func
	//{ 0x0, "_ZN19CTriggerMonsterJump5SpawnEv", mfunc_ptr_cast(&CTriggerMonsterJump::Spawn_) },
	//{ 0x0, "_ZN19CTriggerMonsterJump5ThinkEv", mfunc_ptr_cast(&CTriggerMonsterJump::Think_) },
	//{ 0x0, "_ZN19CTriggerMonsterJump5TouchEP11CBaseEntity", mfunc_ptr_cast(&CTriggerMonsterJump::Touch_) },
	//non-virtual func
	//{ 0x01DBDF50, "trigger_monsterjump", (size_t)&trigger_monsterjump },
//CTriggerCDAudio
	//virtual func
	//{ 0x0, "_ZN15CTriggerCDAudio5SpawnEv", mfunc_ptr_cast(&CTriggerCDAudio::Spawn_) },
	//{ 0x0, "_ZN15CTriggerCDAudio5TouchEP11CBaseEntity", mfunc_ptr_cast(&CTriggerCDAudio::Touch_) },
	//{ 0x0, "_ZN15CTriggerCDAudio3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTriggerCDAudio::Use_) },
	//non-virtual func
	//{ 0x01DBE170, "trigger_cdaudio", (size_t)&trigger_cdaudio },
	//{ 0x0, "_ZN15CTriggerCDAudio9PlayTrackEv", mfunc_ptr_cast(&CTriggerCDAudio::PlayTrack) },
//CTargetCDAudio
	//virtual func
	//{ 0x0, "_ZN14CTargetCDAudio5SpawnEv", mfunc_ptr_cast(&CTargetCDAudio::Spawn_) },
	//{ 0x0, "_ZN14CTargetCDAudio8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CTargetCDAudio::KeyValue_) },
	//{ 0x0, "_ZN14CTargetCDAudio5ThinkEv", mfunc_ptr_cast(&CTargetCDAudio::Think_) },
	//{ 0x0, "_ZN14CTargetCDAudio3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTargetCDAudio::Use_) },
	//non-virtual func
	//{ 0x01DBE4C0, "target_cdaudio", (size_t)&target_cdaudio },
	//{ 0x0, "_Z11PlayCDTracki", (size_t)&PlayCDTrack },
	//{ 0x0, "_ZN14CTargetCDAudio4PlayEv", mfunc_ptr_cast(&CTargetCDAudio::Play) },
//CTriggerMultiple
	//virtual func
	//{ 0x0, "_ZN16CTriggerMultiple5SpawnEv", mfunc_ptr_cast(&CTriggerMultiple::Spawn_) },
	//non-virtual func
	//{ 0x01DBEE40, "trigger_multiple", (size_t)&trigger_multiple },
//CTriggerOnce
	//virtual func
	//{ 0x0, "_ZN12CTriggerOnce5SpawnEv", mfunc_ptr_cast(&CTriggerOnce::Spawn_) },
	//non-virtual func
	//{ 0x01DBEF60, "trigger_once", (size_t)&trigger_once },
//CTriggerCounter
	//virtual func
	//{ 0x0, "_ZN15CTriggerCounter5SpawnEv", mfunc_ptr_cast(&CTriggerCounter::Spawn_) },
	//non-virtual func
	//{ 0x01DBF3C0, "trigger_counter", (size_t)&trigger_counter },
//CTriggerVolume
	//virtual func
	//{ 0x0, "_ZN14CTriggerVolume5SpawnEv", mfunc_ptr_cast(&CTriggerVolume::Spawn_) },
	//non-virtual func
	//{ 0x01DBF440, "trigger_transition", (size_t)&trigger_transition },
//CFireAndDie
	//virtual func
	//{ 0x0, "_ZN11CFireAndDie5SpawnEv", mfunc_ptr_cast(&CFireAndDie::Spawn_) },
	//{ 0x0, "_ZN11CFireAndDie8PrecacheEv", mfunc_ptr_cast(&CFireAndDie::Precache_) },
	//{ 0x0, "_ZN11CFireAndDie10ObjectCapsEv", mfunc_ptr_cast(&CFireAndDie::ObjectCaps_) },
	//{ 0x0, "_ZN11CFireAndDie5ThinkEv", mfunc_ptr_cast(&CFireAndDie::Think) },
	//non-virtual func
	//{ 0x01DBF4F0, "fireanddie", (size_t)&fireanddie },
//CChangeLevel
	//virtual func
	//{ 0x0, "_ZN12CChangeLevel5SpawnEv", mfunc_ptr_cast(&CChangeLevel::Spawn_) },
	//{ 0x0, "_ZN12CChangeLevel8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CChangeLevel::KeyValue_) },
	//{ 0x0, "_ZN12CChangeLevel4SaveER5CSave", mfunc_ptr_cast(&CChangeLevel::Save_) },
	//{ 0x0, "_ZN12CChangeLevel7RestoreER8CRestore", mfunc_ptr_cast(&CChangeLevel::Restore_) },
	//non-virtual func
	//{ 0x01DBF5F0, "trigger_changelevel", (size_t)&trigger_changelevel },
	{ 0x01DBFD80, "_Z15BuildChangeListP9LEVELLISTi", (size_t)&BuildChangeList },
	//{ 0x0, "_Z9NextLevelv", (size_t)&NextLevel },
	//{ 0x0, "_ZN12CChangeLevel14UseChangeLevelEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CChangeLevel::UseChangeLevel) },
	//{ 0x0, "_ZN12CChangeLevel18TriggerChangeLevelEv", mfunc_ptr_cast(&CChangeLevel::TriggerChangeLevel) }, // NOXREF
	//{ 0x0, "_ZN12CChangeLevel18ExecuteChangeLevelEv", mfunc_ptr_cast(&CChangeLevel::ExecuteChangeLevel) },
	//{ 0x0, "_ZN12CChangeLevel16TouchChangeLevelEP11CBaseEntity", mfunc_ptr_cast(&CChangeLevel::TouchChangeLevel) },
	//{ 0x0, "_ZN12CChangeLevel14ChangeLevelNowEP11CBaseEntity", mfunc_ptr_cast(&CChangeLevel::ChangeLevelNow) },
	//{ 0x01DBF990, "_ZN12CChangeLevel12FindLandmarkEPKc", mfunc_ptr_cast(&CChangeLevel::FindLandmark) },	// NOXREF
	{ 0x01DBFE50, "_ZN12CChangeLevel10ChangeListEP9LEVELLISTi", mfunc_ptr_cast(&CChangeLevel::ChangeList) },
	{ 0x01DBFCA0, "_ZN12CChangeLevel19AddTransitionToListEP9LEVELLISTiPKcS3_P7edict_s", mfunc_ptr_cast(&CChangeLevel::AddTransitionToList) },
	{ 0x01DBFD90, "_ZN12CChangeLevel18InTransitionVolumeEP11CBaseEntityPc", mfunc_ptr_cast(&CChangeLevel::InTransitionVolume) },
//CLadder
	//virtual func
	//{ 0x0, "_ZN7CLadder5SpawnEv", mfunc_ptr_cast(&CLadder::Spawn_) },
	//{ 0x0, "_ZN7CLadder8PrecacheEv", mfunc_ptr_cast(&CLadder::Precache_) },
	//{ 0x0, "_ZN7CLadder8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CLadder::KeyValue_) },
	//non-virtual func
	//{ 0x01DC02A0, "func_ladder", (size_t)&func_ladder },
//CTriggerPush
	//virtual func
	//{ 0x0, "_ZN12CTriggerPush5SpawnEv", mfunc_ptr_cast(&CTriggerPush::Spawn_) },
	//{ 0x0, "_ZN12CTriggerPush8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CTriggerPush::KeyValue_) },
	//{ 0x0, "_ZN12CTriggerPush5TouchEP11CBaseEntity", mfunc_ptr_cast(&CTriggerPush::Touch_) },
	//non-virtual func
	//{ 0x01DC03C0, "trigger_push", (size_t)&trigger_push },
//CTriggerTeleport
	//virtual func
	//{ 0x0, "_ZN16CTriggerTeleport5SpawnEv", mfunc_ptr_cast(&CTriggerTeleport::Spawn_) },
	//non-virtual func
	//{ 0x01DC0860, "trigger_teleport", (size_t)&trigger_teleport },
	//{ 0x01DC0970, "info_teleport_destination", (size_t)&info_teleport_destination },
//CBuyZone
	//virtual func
	//{ 0x0, "_ZN8CBuyZone5SpawnEv", mfunc_ptr_cast(&CBuyZone::Spawn_) },
	//non-virtual func
	//{ 0x01DC09C0, "func_buyzone", (size_t)&func_buyzone },
	//{ 0x0, "_ZN8CBuyZone8BuyTouchEP11CBaseEntity", mfunc_ptr_cast(&CBuyZone::BuyTouch) },
//CBombTarget
	//virtual func
	//{ 0x0, "_ZN11CBombTarget5SpawnEv", mfunc_ptr_cast(&CBombTarget::Spawn_) },
	//non-virtual func
	//{ 0x01DC0B40, "func_bomb_target", (size_t)&func_bomb_target },
	//{ 0x0, "_ZN11CBombTarget15BombTargetTouchEP11CBaseEntity", mfunc_ptr_cast(&CBombTarget::BombTargetTouch) },
	//{ 0x0, "_ZN11CBombTarget13BombTargetUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CBombTarget::BombTargetUse) },
//CHostageRescue
	//virtual func
	//{ 0x0, "_ZN14CHostageRescue5SpawnEv", mfunc_ptr_cast(&CHostageRescue::Spawn_) },
	//non-virtual func
	//{ 0x01DC0CB0, "func_hostage_rescue", (size_t)&func_hostage_rescue },
	//{ 0x0, "_ZN14CHostageRescue18HostageRescueTouchEP11CBaseEntity", mfunc_ptr_cast(&CHostageRescue::HostageRescueTouch) },
//CEscapeZone
	//virtual func
	//{ 0x0, "_ZN11CEscapeZone5SpawnEv", mfunc_ptr_cast(&CEscapeZone::Spawn_) },
	//non-virtual func
	//{ 0x01DC0E20, "func_escapezone", (size_t)&func_escapezone },
	//{ 0x0, "_ZN11CEscapeZone11EscapeTouchEP11CBaseEntity", mfunc_ptr_cast(&CEscapeZone::EscapeTouch) },
//CVIP_SafetyZone
	//virtual func
	//{ 0x0, "_ZN15CVIP_SafetyZone5SpawnEv", mfunc_ptr_cast(&CVIP_SafetyZone::Spawn_) },
	//non-virtual func
	//{ 0x01DC1050, "func_vip_safetyzone", (size_t)&func_vip_safetyzone },
	//{ 0x0, "_ZN15CVIP_SafetyZone15VIP_SafetyTouchEP11CBaseEntity", mfunc_ptr_cast(&CVIP_SafetyZone::VIP_SafetyTouch) },
//CTriggerSave
	//virtual func
	//{ 0x0, "_ZN12CTriggerSave5SpawnEv", mfunc_ptr_cast(&CTriggerSave::Spawn_) },
	//non-virtual func
	//{ 0x01DC11F0, "trigger_autosave", (size_t)&trigger_autosave },
	//{ 0x0, "_ZN12CTriggerSave9SaveTouchEP11CBaseEntity", mfunc_ptr_cast(&CTriggerSave::SaveTouch) },
//CTriggerEndSection
	//virtual func
	//{ 0x0, "_ZN18CTriggerEndSection5SpawnEv", mfunc_ptr_cast(&CTriggerEndSection::Spawn_) },
	//{ 0x0, "_ZN18CTriggerEndSection8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CTriggerEndSection::KeyValue_) },
	//non-virtual func
	//{ 0x01DC1370, "trigger_endsection", (size_t)&trigger_endsection },
	//{ 0x0, "_ZN18CTriggerEndSection15EndSectionTouchEP11CBaseEntity", mfunc_ptr_cast(&CTriggerEndSection::EndSectionTouch) },
	//{ 0x0, "_ZN18CTriggerEndSection13EndSectionUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTriggerEndSection::EndSectionUse) },
//CTriggerGravity
	//virtual func
	//{ 0x0, "_ZN15CTriggerGravity5SpawnEv", mfunc_ptr_cast(&CTriggerGravity::Spawn_) },
	//non-virtual func
	//{ 0x01DC15A0, "trigger_gravity", (size_t)&trigger_gravity },
	//{ 0x0, "_ZN15CTriggerGravity12GravityTouchEP11CBaseEntity", mfunc_ptr_cast(&CTriggerGravity::GravityTouch) },
//CTriggerChangeTarget
	//virtual func
	//{ 0x0, "_ZN20CTriggerChangeTarget5SpawnEv", mfunc_ptr_cast(&CTriggerChangeTarget::Spawn_) },
	//{ 0x0, "_ZN20CTriggerChangeTarget8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CTriggerChangeTarget::KeyValue_) },
	//{ 0x0, "_ZN20CTriggerChangeTarget4SaveER5CSave", mfunc_ptr_cast(&CTriggerChangeTarget::Save_) },
	//{ 0x0, "_ZN20CTriggerChangeTarget7RestoreER8CRestore", mfunc_ptr_cast(&CTriggerChangeTarget::Restore_) },
	//{ 0x0, "_ZN20CTriggerChangeTarget10ObjectCapsEv", mfunc_ptr_cast(&CTriggerChangeTarget::ObjectCaps_) },
	//{ 0x0, "_ZN20CTriggerChangeTarget3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTriggerChangeTarget::Use_) },
	//non-virtual func
	//{ 0x01DC16E0, "trigger_changetarget", (size_t)&trigger_changetarget },
//CTriggerCamera
	//virtual func
	//{ 0x0, "_ZN14CTriggerCamera5SpawnEv", mfunc_ptr_cast(&CTriggerCamera::Spawn_) },
	//{ 0x0, "_ZN14CTriggerCamera8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CTriggerCamera::KeyValue_) },
	//{ 0x0, "_ZN14CTriggerCamera4SaveER5CSave", mfunc_ptr_cast(&CTriggerCamera::Save_) },
	//{ 0x0, "_ZN14CTriggerCamera7RestoreER8CRestore", mfunc_ptr_cast(&CTriggerCamera::Restore_) },
	//{ 0x0, "_ZN14CTriggerCamera10ObjectCapsEv", mfunc_ptr_cast(&CTriggerCamera::ObjectCap_s) },
	//{ 0x0, "_ZN14CTriggerCamera3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CTriggerCamera::Use_) },
	//non-virtual func
	//{ 0x01DC1860, "trigger_camera", (size_t)&trigger_camera },
	//{ 0x0, "_ZN14CTriggerCamera12FollowTargetEv", mfunc_ptr_cast(&CTriggerCamera::FollowTarget) },
	//{ 0x0, "_ZN14CTriggerCamera4MoveEv", mfunc_ptr_cast(&CTriggerCamera::Move) },
//CWeather
	//virtual func
	//{ 0x0, "_ZN8CWeather5SpawnEv", mfunc_ptr_cast(&CWeather::Spawn_) },
	//non-virtual func
	//{ 0x01DC2350, "env_snow", (size_t)&env_snow },
	//{ 0x01DC23A0, "func_snow", (size_t)&func_snow },
	//{ 0x01DC23F0, "env_rain", (size_t)&env_rain },
	//{ 0x01DC2440, "func_rain", (size_t)&func_rain },
//CClientFog
	//virtual func
	//{ 0x0, "_ZN10CClientFog5SpawnEv", mfunc_ptr_cast(&CClientFog::Spawn_) },
	//{ 0x0, "_ZN10CClientFog8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CClientFog::KeyValue) },
	//non-virtual func
	//{ 0x01DC2610, "env_fog", (size_t)&env_fog },

#endif // Triggers_Region

#ifndef SharedUtil_Region

#ifdef _WIN32
	//{ 0x01D50CA0, "", (size_t)&CloneString },
#endif // _WIN32

	//{ 0x01D58EE0, "_Z14SharedWVarArgsPwz", (size_t)&SharedWVarArgs },	// NOXREF
	{ 0x01D58F30, "_Z13SharedVarArgsPcz", (size_t)&SharedVarArgs },
	{ 0x01D58F80, "_Z9BufPrintfPcRiPKcz", (size_t)&BufPrintf },
	//{ 0x01D58FD0, "_Z10BufWPrintfPwRiPKwz", (size_t)&BufWPrintf },??
	//{ 0x01D59010, "_Z12NumAsWStringi", (size_t)&NumAsWString },	// NOXREF
	{ 0x01D59060, "_Z11NumAsStringi", (size_t)&NumAsString },
	{ 0x01D590B0, "_Z14SharedGetTokenv", (size_t)&SharedGetToken },
	//{ 0x01D590C0, "_Z18SharedSetQuoteCharc", (size_t)&SharedSetQuoteChar },	// NOXREF
	//{ 0x01D590D0, "_Z11SharedParsePKc", (size_t)&SharedParse },
	//{ 0x01D591B0, "_Z18SharedTokenWaitingPKc", (size_t)&SharedTokenWaiting },	// NOXREF

#endif // SharedUtil_Region

#ifndef World_Region
	//virtual func
	{ 0x01DD1750, "_ZN7CCorpse10ObjectCapsEv", mfunc_ptr_cast(&CCorpse::ObjectCaps_) },
	//non-virtual func
	{ 0x01DD1420, "_ZN6CDecal5SpawnEv", mfunc_ptr_cast(&CDecal::Spawn_) },
	{ 0x01DD15C0, "_ZN6CDecal11StaticDecalEv", mfunc_ptr_cast(&CDecal::StaticDecal) },
	{ 0x01DD1490, "_ZN6CDecal12TriggerDecalEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CDecal::TriggerDecal) },
	{ 0x01DD1690, "_ZN6CDecal8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CDecal::KeyValue_) },
	//{ 0x01DD1760, "_Z13CopyToBodyQueP9entvars_s", (size_t)&CopyToBodyQue },	// PURE
	//{ 0x01DD1770, "_Z12ClearBodyQuev", (size_t)&ClearBodyQue },	// NOXREF
	//{ 0x01DD1780, "_ZN12CGlobalStateC2Ev", mfunc_ptr_cast(&CGlobalState__CGlobalState) },
	//{ 0x01DD1790, "_ZN12CGlobalState5ResetEv", mfunc_ptr_cast(&CGlobalState::Reset) },	// NOXREF
	{ 0x01DD17A0, "_ZN12CGlobalState4FindEj", mfunc_ptr_cast(&CGlobalState::Find) },
	{ 0x01DD1810, "_ZN12CGlobalState11DumpGlobalsEv", mfunc_ptr_cast(&CGlobalState::DumpGlobals) },
	{ 0x01DD1860, "_ZN12CGlobalState9EntityAddEjj12GLOBALESTATE", mfunc_ptr_cast(&CGlobalState::EntityAdd) },
	{ 0x01DD18D0, "_ZN12CGlobalState14EntitySetStateEj12GLOBALESTATE", mfunc_ptr_cast(&CGlobalState::EntitySetState) },
	{ 0x01DD1950, "_ZN12CGlobalState15EntityFromTableEj", mfunc_ptr_cast(&CGlobalState::EntityFromTable) },
	{ 0x01DD19C0, "_ZN12CGlobalState14EntityGetStateEj", mfunc_ptr_cast(&CGlobalState::EntityGetState) },
	//{ 0x01DD1A40, "_ZN12CGlobalState4SaveER5CSave", mfunc_ptr_cast(&CGlobalState::Save) },	// NOXREF
	//{ 0x01DD1AB0, "_ZN12CGlobalState7RestoreER8CRestore", mfunc_ptr_cast(&CGlobalState::Restore) },	// NOXREF
	{ 0x01DD1BD0, "_ZN12CGlobalState12EntityUpdateEjj", mfunc_ptr_cast(&CGlobalState::EntityUpdate) },
	//{ 0x01DD1C50, "_ZN12CGlobalState11ClearStatesEv", mfunc_ptr_cast(&CGlobalState::ClearStates) },	// NOXREF

	{ 0x01DD1C80, "_Z15SaveGlobalStateP13saverestore_s", (size_t)&SaveGlobalState },
	{ 0x01DD1D00, "_Z18RestoreGlobalStateP13saverestore_s", (size_t)&RestoreGlobalState },
	{ 0x01DD1E50, "_Z16ResetGlobalStatev", (size_t)&ResetGlobalState },

//linked objects
	{ 0x01DD13D0, "infodecal", (size_t)&infodecal },
	{ 0x01DD1700, "bodyque", (size_t)&bodyque },
	{ 0x01DD1E90, "worldspawn", (size_t)&worldspawn },
#endif // World_Region

#ifndef Graph_Region

	//{ 0x01D8AB70, "_ZN6CGraph9InitGraphEv", mfunc_ptr_cast(&CGraph::InitGraph) },	// pure
	//{ 0x01D8AB90, "_ZN6CGraph10AllocNodesEv", mfunc_ptr_cast(&CGraph::AllocNodes) }, // pure
	//{ 0x01D8ABA0, "_ZN6CGraph12CheckNODFileEPc", mfunc_ptr_cast(&CGraph::CheckNODFile) }, // pure
	//{ 0x01D8AB80, "_ZN6CGraph10FLoadGraphEPc", mfunc_ptr_cast(&CGraph::FLoadGraph) }, // pure
	//{ 0x01D8ABB0, "_ZN6CGraph17FSetGraphPointersEv", mfunc_ptr_cast(&CGraph::FSetGraphPointers) }, // pure
	//{ 0x01D8ABC0, "_ZN6CGraph19ShowNodeConnectionsEi", mfunc_ptr_cast(&CGraph::ShowNodeConnections) }, // pure
	//{ 0x0, "_ZN6CGraph15FindNearestNodeERK6VectorP11CBaseEntity", mfunc_ptr_cast<FIND_NEAREST_NODE_ENTITY>(&CGraph::FindNearestNode) }, // pure
	//{ 0x01D8ABD0, "_ZN6CGraph15FindNearestNodeERK6Vectori", mfunc_ptr_cast<FIND_NEAREST_NODE_INT>(&CGraph::FindNearestNode) }, // pure

#endif // Graph_Region

#ifndef SoundEnt_Region

//CSound
	//non-virtual func
	//{ 0x0, "_ZN6CSound5ClearEv", mfunc_ptr_cast(&CSound::Clear) },
	{ 0x01DBA560, "_ZN6CSound5ResetEv", mfunc_ptr_cast(&CSound::Reset) },
	//{ 0x0, "_ZN6CSound8FIsSoundEv", mfunc_ptr_cast(&CSound::FIsSound) },
	//{ 0x0, "_ZN6CSound8FIsScentEv", mfunc_ptr_cast(&CSound::FIsScent) },
//CSoundEnt
	//virtual func
	//{ 0x0, "_ZN9CSoundEnt5SpawnEv", mfunc_ptr_cast(&CSoundEnt::Spawn_) },
	//{ 0x0, "_ZN9CSoundEnt8PrecacheEv", mfunc_ptr_cast(&CSoundEnt::Precache_) },
	//{ 0x0, "_ZN9CSoundEnt10ObjectCapsEv", mfunc_ptr_cast(&CSoundEnt::ObjectCaps_) },
	//{ 0x0, "_ZN9CSoundEnt5ThinkEv", mfunc_ptr_cast(&CSoundEnt::Think_) },
	//non-virtual func
	//{ 0x0, "_ZN9CSoundEnt10InitializeEv", mfunc_ptr_cast(&CSoundEnt::Initialize) },
	{ 0x01DBA820, "_ZN9CSoundEnt11InsertSoundEiRK6Vectorif", mfunc_ptr_cast(&CSoundEnt::InsertSound) },
	//{ 0x0, "_ZN9CSoundEnt9FreeSoundEii", mfunc_ptr_cast(&CSoundEnt::FreeSound) },
	//{ 0x0, "_ZN9CSoundEnt10ActiveListEv", mfunc_ptr_cast(&CSoundEnt::ActiveList) },
	//{ 0x0, "_ZN9CSoundEnt8FreeListEv", mfunc_ptr_cast(&CSoundEnt::FreeList) },
	{ 0x01DBAAB0, "_ZN9CSoundEnt20SoundPointerForIndexEi", mfunc_ptr_cast(&CSoundEnt::SoundPointerForIndex) },
	{ 0x01DBAB00, "_ZN9CSoundEnt16ClientSoundIndexEP7edict_s", mfunc_ptr_cast(&CSoundEnt::ClientSoundIndex) },
	//{ 0x0, "_ZN9CSoundEnt7IsEmptyEv", mfunc_ptr_cast(&CSoundEnt::IsEmpty) },		// NOXREF
	//{ 0x0, "_ZN9CSoundEnt13ISoundsInListEi", mfunc_ptr_cast(&CSoundEnt::ISoundsInList) },
	//{ 0x01DBA7D0, "_ZN9CSoundEnt11IAllocSoundEv", mfunc_ptr_cast(&CSoundEnt::IAllocSound) },	// NOXREF

#endif // SoundEnt_Region

#ifndef Sound_Region
	
	//{ 0x01DB6C30, "ambient_generic", (size_t)&ambient_generic },
	//{ 0x01DB7E10, "env_sound", (size_t)&env_sound },
	//{ 0x01DB9F10, "speaker", (size_t)&speaker },
	//{ 0x0, "_ZN15CAmbientGeneric4SaveER5CSave", mfunc_ptr_cast(&CAmbientGeneric::Save) },
	//{ 0x0, "_ZN15CAmbientGeneric7RestoreER8CRestore", mfunc_ptr_cast(&CAmbientGeneric::Restore) },
	//{ 0x0, "_ZN15CAmbientGeneric5SpawnEv", mfunc_ptr_cast(&CAmbientGeneric::Spawn) },
	//{ 0x0, "_ZN15CAmbientGeneric10ObjectCapsEv", mfunc_ptr_cast(&CAmbientGeneric::ObjectCaps) },
	//{ 0x0, "_ZN15CAmbientGeneric7RestartEv", mfunc_ptr_cast(&CAmbientGeneric::Restart) },
	//{ 0x0, "_ZN15CAmbientGeneric8PrecacheEv", mfunc_ptr_cast(&CAmbientGeneric::Precache) },
	//{ 0x0, "_ZN15CAmbientGeneric9RampThinkEv", mfunc_ptr_cast(&CAmbientGeneric::RampThink) },
	//{ 0x0, "_ZN15CAmbientGeneric19InitModulationParmsEv", mfunc_ptr_cast(&CAmbientGeneric::InitModulationParms) },
	//{ 0x0, "_ZN15CAmbientGeneric9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CAmbientGeneric::ToggleUse) },
	//{ 0x0, "_ZN15CAmbientGeneric8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CAmbientGeneric::KeyValue) },
	//{ 0x0, "_ZN9CEnvSound4SaveER5CSave", mfunc_ptr_cast(&CEnvSound::Save) },
	//{ 0x0, "_ZN9CEnvSound7RestoreER8CRestore", mfunc_ptr_cast(&CEnvSound::Restore) },
	//{ 0x0, "_ZN9CEnvSound8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CEnvSound::KeyValue) },
	//{ 0x01DB7F30, "_Z16FEnvSoundInRangeP9entvars_sS0_Pf", (size_t)&FEnvSoundInRange },
	//{ 0x01DB8090, "_ZN9CEnvSound5ThinkEv", mfunc_ptr_cast(&CEnvSound::Think) },
	//{ 0x01DB8270, "_ZN9CEnvSound5SpawnEv", mfunc_ptr_cast(&CEnvSound::Spawn_) },
	//{ 0x01DB82A0, "_Z18USENTENCEG_InitLRUPhi", (size_t)&USENTENCEG_InitLRU },		// NOXREF
	{ 0x01DB8310, "_Z25USENTENCEG_PickSequentialiPcii", (size_t)&USENTENCEG_PickSequential },
	{ 0x01DB8420, "_Z15USENTENCEG_PickiPc", (size_t)&USENTENCEG_Pick },
	//{ 0x01DB85C0, "_Z18SENTENCEG_GetIndexPKc", (size_t)&SENTENCEG_GetIndex },		// NOXREF
	//{ 0x01DB8640, "_Z18SENTENCEG_PlayRndIP7edict_siffii", (size_t)&SENTENCEG_PlayRndI },	// NOXREF
	//{ 0x01DB87B0, "_Z19SENTENCEG_PlayRndSzP7edict_sPKcffii", (size_t)&SENTENCEG_PlayRndSz },		// NOXREF
	{ 0x01DB89A0, "_Z26SENTENCEG_PlaySequentialSzP7edict_sPKcffiiii", (size_t)&SENTENCEG_PlaySequentialSz },
	//{ 0x01DB8BA0, "_Z14SENTENCEG_StopP7edict_sii", (size_t)&SENTENCEG_Stop },				// NOXREF
	{ 0x01DB8D30, "_Z14SENTENCEG_Initv", (size_t)&SENTENCEG_Init },
	{ 0x01DB9050, "_Z16SENTENCEG_LookupPKcPc", (size_t)&SENTENCEG_Lookup },
	{ 0x01DB9100, "_Z14EMIT_SOUND_DYNP7edict_siPKcffii", (size_t)&EMIT_SOUND_DYN },
	{ 0x01DB9210, "_Z15EMIT_SOUND_SUITP7edict_sPKc", (size_t)&EMIT_SOUND_SUIT },
	{ 0x01DB9380, "_Z17EMIT_GROUPID_SUITP7edict_si", (size_t)&EMIT_GROUPID_SUIT },
	//{ 0x01DB9510, "_Z19EMIT_GROUPNAME_SUITP7edict_sPKc", (size_t)&EMIT_GROUPNAME_SUIT },		// NOXREF
	{ 0x01DB9720, "_ZL8memfgetsPhiRiPci_constprop_21", (size_t)&memfgets },
	{ 0x01DB97C0, "_Z16TEXTURETYPE_Initv", (size_t)&TEXTURETYPE_Init },
	{ 0x01DB99A0, "_Z16TEXTURETYPE_FindPc", (size_t)&TEXTURETYPE_Find },
	{ 0x01DB99F0, "_Z21TEXTURETYPE_PlaySoundP11TraceResult6VectorS1_i", (size_t)&TEXTURETYPE_PlaySound },
	//{ 0x0, "_ZN8CSpeaker10ObjectCapsEv", mfunc_ptr_cast(&CSpeaker::ObjectCaps) },
	//{ 0x0, "_ZN8CSpeaker4SaveER5CSave", mfunc_ptr_cast(&CSpeaker::Save) },
	//{ 0x0, "_ZN8CSpeaker7RestoreER8CRestore", mfunc_ptr_cast(&CSpeaker::Restore) },
	//{ 0x0, "_ZN8CSpeaker5SpawnEv", mfunc_ptr_cast(&CSpeaker::Spawn) },
	//{ 0x0, "_ZN8CSpeaker8PrecacheEv", mfunc_ptr_cast(&CSpeaker::Precache) },
	//{ 0x0, "_ZN8CSpeaker12SpeakerThinkEv", mfunc_ptr_cast(&CSpeaker::SpeakerThink) },
	//{ 0x0, "_ZN8CSpeaker9ToggleUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CSpeaker::ToggleUse) },
	//{ 0x0, "_ZN8CSpeaker8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CSpeaker::KeyValue) },

#endif // Sound_Region

#ifndef Util_Region

#ifdef _WIN32
	//{ 0x01D67920, "", mfunc_ptr_cast<entvars_t *(*)(edict_t *)>(&VARS) },
#endif // _WIN32

	//{ 0x01DC2670, "_Z8U_Randomv", (size_t)&U_Random },	// NOXREF
	//{ 0x01DC26B0, "_Z7U_Srandj", (size_t)&U_Srand },	// NOXREF
	{ 0x01DC26D0, "_Z21UTIL_SharedRandomLongjii", (size_t)&UTIL_SharedRandomLong },
	{ 0x01DC2740, "_Z22UTIL_SharedRandomFloatjff", (size_t)&UTIL_SharedRandomFloat },
	//{ 0x01DC2820, "_Z21UTIL_ParametricRocketP9entvars_s6VectorS1_P7edict_s", (size_t)&UTIL_ParametricRocket },	// NOXREF
	{ 0x01DC2980, "_Z18UTIL_SetGroupTraceii", (size_t)&UTIL_SetGroupTrace },
	{ 0x01DC29B0, "_Z20UTIL_UnsetGroupTracev", (size_t)&UTIL_UnsetGroupTrace },
	//{ 0x01DC29D0, "_ZN15UTIL_GroupTraceC2Eii", mfunc_ptr_cast(&UTIL_GroupTrace::UTIL_GroupTrace) },	// NOXREF
	//{ 0x01DC2A10, "_ZN15UTIL_GroupTraceD2Ev", mfunc_ptr_cast(&UTIL_GroupTrace::~UTIL_GroupTrace) },	// NOXREF
	//{ 0x01DC2A30, "_Z22UTIL_GetNextBestWeaponP11CBasePlayerP15CBasePlayerItem", (size_t)&UTIL_GetNextBestWeapon },	// NOXREF
	//{ 0x01DC2A50, "_Z13UTIL_AngleModf", (size_t)&UTIL_AngleMod },	// NOXREF
	//{ 0x01DC2AD0, "_Z14UTIL_AngleDiffff", (size_t)&UTIL_AngleDiff },	// NOXREF
	{ 0x01DC2B20, "_Z16UTIL_VecToAnglesRK6Vector", (size_t)&UTIL_VecToAngles },
	//{ 0x01DC2B50, "_Z17UTIL_MoveToOriginP7edict_sRK6Vectorfi", (size_t)&UTIL_MoveToOrigin },	// NOXREF
	{ 0x01DC2B90, "_Z18UTIL_EntitiesInBoxPP11CBaseEntityiRK6VectorS4_i", (size_t)&UTIL_EntitiesInBox },
	//{ 0x01DC2C90, "_Z21UTIL_MonstersInSpherePP11CBaseEntityiRK6Vectorf", (size_t)&UTIL_MonstersInSphere },	// NOXREF
	{ 0x01DC2D90, "_Z23UTIL_FindEntityInSphereP11CBaseEntityRK6Vectorf", (size_t)&UTIL_FindEntityInSphere },
	{ 0x01DC2DE0, "_Z27UTIL_FindEntityByString_OldP11CBaseEntityPKcS2_", (size_t)&UTIL_FindEntityByString_Old },
	{ 0x01DC2E30, "_Z23UTIL_FindEntityByStringP11CBaseEntityPKcS2_", (size_t)&UTIL_FindEntityByString },
	{ 0x01DC2FB0, "_Z26UTIL_FindEntityByClassnameP11CBaseEntityPKc", (size_t)&UTIL_FindEntityByClassname },
	{ 0x01DC2FD0, "_Z27UTIL_FindEntityByTargetnameP11CBaseEntityPKc", (size_t)&UTIL_FindEntityByTargetname },
	//{ 0x01DC2FF0, "_Z22UTIL_FindEntityGenericPKcR6Vectorf", (size_t)&UTIL_FindEntityGeneric },	// NOXREF
	{ 0x01DC30A0, "_Z18UTIL_PlayerByIndexi", (size_t)&UTIL_PlayerByIndex },
	{ 0x01DC30E0, "_Z16UTIL_MakeVectorsRK6Vector", (size_t)&UTIL_MakeVectors },
	{ 0x01DC30F0, "_Z19UTIL_MakeAimVectorsRK6Vector", (size_t)&UTIL_MakeAimVectors },
	{ 0x01DC3120, "_Z19UTIL_MakeInvVectorsRK6VectorP12globalvars_t", (size_t)&UTIL_MakeInvVectors },
	{ 0x01DC31A0, "_Z21UTIL_EmitAmbientSoundP7edict_sRK6VectorPKcffii", (size_t)&UTIL_EmitAmbientSound },
	{ 0x01DC3240, "_Z16UTIL_ScreenShakeRK6Vectorffff", (size_t)&UTIL_ScreenShake },
	//{ 0x01DC33F0, "_Z19UTIL_ScreenShakeAllRK6Vectorfff", (size_t)&UTIL_ScreenShakeAll },	// NOXREF
	//{ 0x01DC3410, "_Z20UTIL_ScreenFadeBuildR10ScreenFadeRK6Vectorffii", (size_t)&UTIL_ScreenFadeBuild },	// NOXREF
	//{ 0x01DC34A0, "_Z20UTIL_ScreenFadeWriteRK10ScreenFadeP11CBaseEntity", (size_t)&UTIL_ScreenFadeWrite },	// NOXREF
	{ 0x01DC3540, "_Z18UTIL_ScreenFadeAllRK6Vectorffii", (size_t)&UTIL_ScreenFadeAll },
	{ 0x01DC36E0, "_Z15UTIL_ScreenFadeP11CBaseEntityRK6Vectorffii", (size_t)&UTIL_ScreenFade },
	{ 0x01DC3810, "_Z15UTIL_HudMessageP11CBaseEntityRK14hudtextparms_sPKc", (size_t)&UTIL_HudMessage },
	{ 0x01DC3A80, "_Z18UTIL_HudMessageAllRK14hudtextparms_sPKc", (size_t)&UTIL_HudMessageAll },
	{ 0x01DC3AF0, "_Z19UTIL_ClientPrintAlliPKcS0_S0_S0_S0_", (size_t)&UTIL_ClientPrintAll },
	{ 0x01DC3B70, "_Z11ClientPrintP9entvars_siPKcS2_S2_S2_S2_", (size_t)&ClientPrint },
	//{ 0x01DC3C00, "_Z12UTIL_SayTextPKcP11CBaseEntity", (size_t)&UTIL_SayText },	// NOXREF						// NOXREF
	{ 0x01DC3C60, "_Z15UTIL_SayTextAllPKcP11CBaseEntity", (size_t)&UTIL_SayTextAll },
	{ 0x01DC3CB0, "_Z10UTIL_dtos1i", (size_t)&UTIL_dtos1 },
	{ 0x01DC3CD0, "_Z10UTIL_dtos2i", (size_t)&UTIL_dtos2 },
	//{ 0x01DC3CF0, "_Z10UTIL_dtos3i", (size_t)&UTIL_dtos3 },		// NOXREF								// NOXREF
	//{ 0x01DC3D10, "_Z10UTIL_dtos4i", (size_t)&UTIL_dtos4 },		// NOXREF
	{ 0x01DC3D30, "_Z20UTIL_ShowMessageArgsPKcP11CBaseEntityP10CUtlVectorIPcEb", (size_t)&UTIL_ShowMessageArgs },
	{ 0x01DC3E20, "_Z16UTIL_ShowMessagePKcP11CBaseEntityb", (size_t)&UTIL_ShowMessage },
	{ 0x01DC3E80, "_Z19UTIL_ShowMessageAllPKcb", (size_t)&UTIL_ShowMessageAll },
	{ 0x01DC3F30, "_Z14UTIL_TraceLineRK6VectorS1_15IGNORE_MONSTERS12IGNORE_GLASSP7edict_sP11TraceResult", mfunc_ptr_cast<UTIL_TRACELINE_IGNORE_GLASS>(&UTIL_TraceLine) },
	{ 0x01DC3F70, "_Z14UTIL_TraceLineRK6VectorS1_15IGNORE_MONSTERSP7edict_sP11TraceResult", mfunc_ptr_cast<UTIL_TRACELINE_IGNORE>(&UTIL_TraceLine) },
	{ 0x01DC3F90, "_Z14UTIL_TraceHullRK6VectorS1_15IGNORE_MONSTERSiP7edict_sP11TraceResult", (size_t)&UTIL_TraceHull },
	{ 0x01DC3FB0, "_Z15UTIL_TraceModelRK6VectorS1_iP7edict_sP11TraceResult", (size_t)&UTIL_TraceModel },
	//{ 0x01DC3FC0, "_Z19UTIL_GetGlobalTracev", (size_t)&UTIL_GetGlobalTrace },	// NOXREF
	{ 0x01DC4090, "_Z12UTIL_SetSizeP9entvars_sRK6VectorS3_", (size_t)&UTIL_SetSize },
	{ 0x01DC40B0, "_Z13UTIL_VecToYawRK6Vector", (size_t)&UTIL_VecToYaw },
	{ 0x01DC40C0, "_Z14UTIL_SetOriginP9entvars_sRK6Vector", (size_t)&UTIL_SetOrigin },
	//{ 0x01DC40E0, "_Z19UTIL_ParticleEffectRK6VectorS1_jj", (size_t)&UTIL_ParticleEffect },	// NOXREF
	{ 0x01DC4130, "_Z13UTIL_Approachfff", (size_t)&UTIL_Approach },
	{ 0x01DC4170, "_Z18UTIL_ApproachAnglefff", (size_t)&UTIL_ApproachAngle },
	{ 0x01DC42F0, "_Z18UTIL_AngleDistanceff", (size_t)&UTIL_AngleDistance },
	{ 0x01DC4330, "_Z19UTIL_SplineFractionff", (size_t)&UTIL_SplineFraction },
	{ 0x01DC4350, "_Z12UTIL_VarArgsPcz", (size_t)&UTIL_VarArgs },
	//{ 0x01DC4370, "_Z17UTIL_GetAimVectorP7edict_sf", (size_t)&UTIL_GetAimVector },	// NOXREF
	{ 0x01DC43B0, "_Z22UTIL_IsMasterTriggeredjP11CBaseEntity", (size_t)&UTIL_IsMasterTriggered },
	//{ 0x01DC4430, "_Z20UTIL_ShouldShowBloodi", (size_t)&UTIL_ShouldShowBlood },	// NOXREF
	{ 0x01DC4490, "_Z18UTIL_PointContentsRK6Vector", (size_t)&UTIL_PointContents },
	{ 0x01DC44A0, "_Z16UTIL_BloodStreamRK6VectorS1_ii", (size_t)&UTIL_BloodStream },
	{ 0x01DC4590, "_Z15UTIL_BloodDripsRK6VectorS1_ii", (size_t)&UTIL_BloodDrips },
	{ 0x01DC46D0, "_Z22UTIL_RandomBloodVectorv", (size_t)&UTIL_RandomBloodVector },
	{ 0x01DC4720, "_Z20UTIL_BloodDecalTraceP11TraceResulti", (size_t)&UTIL_BloodDecalTrace },
	{ 0x01DC47A0, "_Z15UTIL_DecalTraceP11TraceResulti", (size_t)&UTIL_DecalTrace },
	{ 0x01DC48A0, "_Z21UTIL_PlayerDecalTraceP11TraceResultiii", (size_t)&UTIL_PlayerDecalTrace },
	//{ 0x01DC4940, "_Z22UTIL_GunshotDecalTraceP11TraceResultibP9entvars_s", (size_t)&UTIL_GunshotDecalTrace },	// NOXREF
	{ 0x01DC4A40, "_Z11UTIL_SparksRK6Vector", (size_t)&UTIL_Sparks },
	{ 0x01DC4A90, "_Z13UTIL_RicochetRK6Vectorf", (size_t)&UTIL_Ricochet },
	{ 0x01DC4AF0, "_Z15UTIL_TeamsMatchPKcS0_", (size_t)&UTIL_TeamsMatch },
	{ 0x01DC4B30, "_Z19UTIL_StringToVectorPfPKc", (size_t)&UTIL_StringToVector },
	{ 0x01DC4BB0, "_Z21UTIL_StringToIntArrayPiiPKc", (size_t)&UTIL_StringToIntArray },
	//{ 0x01DC4C40, "_Z21UTIL_ClampVectorToBoxRK6VectorS1_", (size_t)&UTIL_ClampVectorToBox },	// NOXREF
	//{ 0x01DC4D80, "_Z15UTIL_WaterLevelRK6Vectorff", (size_t)&UTIL_WaterLevel },	// NOXREF
	{ 0x01DC4E50, "_Z12UTIL_Bubbles6VectorS_i", (size_t)&UTIL_Bubbles },
	{ 0x01DC5010, "_Z16UTIL_BubbleTrail6VectorS_i", (size_t)&UTIL_BubbleTrail },
	{ 0x01DC5290, "_Z11UTIL_RemoveP11CBaseEntity", (size_t)&UTIL_Remove },
	//{ 0x01DC52D0, "_Z18UTIL_IsValidEntityP7edict_s", (size_t)&UTIL_IsValidEntity },	// NOXREF
	{ 0x01DC5300, "_Z18UTIL_PrecacheOtherPKc", (size_t)&UTIL_PrecacheOther },
	{ 0x01DC5380, "_Z14UTIL_LogPrintfPcz", (size_t)&UTIL_LogPrintf },
	//{ 0x01DC53B0, "_Z14UTIL_DotPointsRK6VectorS1_S1_", (size_t)&UTIL_DotPoints },	// NOXREF
	{ 0x01DC5430, "_Z15UTIL_StripTokenPKcPc", (size_t)&UTIL_StripToken },
	//{ 0x01DC5470, "_ZN18CSaveRestoreBufferC2Ev", mfunc_ptr_cast<CSAVERESTOREBUFFER_VOID>(&CSaveRestoreBuffer::CSaveRestoreBuffer) },		// NOXREF
	//{ 0x01DC5480, "_ZN18CSaveRestoreBufferC2EP13saverestore_s", mfunc_ptr_cast<CSAVERESTOREBUFFER_POINTER>(&CSaveRestoreBuffer::CSaveRestoreBuffer) },	// NOXREF
	//{ 0x01DC5490, "_ZN18CSaveRestoreBufferD2Ev", mfunc_ptr_cast(&CSaveRestoreBuffer::~CSaveRestoreBuffer) },					// NOXREF
	{ 0x01DC54A0, "_ZN18CSaveRestoreBuffer11EntityIndexEP11CBaseEntity", mfunc_ptr_cast<ENTITYINDEX_CBASE>(&CSaveRestoreBuffer::EntityIndex) },
	//{ 0x01DC54F0, "_ZN18CSaveRestoreBuffer11EntityIndexEP7edict_s", mfunc_ptr_cast<ENTITYINDEX_ENTVARS>(&CSaveRestoreBuffer::EntityIndex) },	// NOXREF
	//{ 0x01DC5540, "_ZN18CSaveRestoreBuffer11EntityIndexEi", mfunc_ptr_cast<ENTITYINDEX_EOFFSET>(&CSaveRestoreBuffer::EntityIndex) },	// NOXREF
	{ 0x01DC5590, "_ZN18CSaveRestoreBuffer11EntityIndexEP9entvars_s", mfunc_ptr_cast<ENTITYINDEX_EDICT>(&CSaveRestoreBuffer::EntityIndex) },
	//{ 0x01DC55D0, "_ZN18CSaveRestoreBuffer15EntityFromIndexEi", mfunc_ptr_cast(&CSaveRestoreBuffer::EntityFromIndex) },			// NOXREF
	{ 0x01DC5610, "_ZN18CSaveRestoreBuffer14EntityFlagsSetEii", mfunc_ptr_cast(&CSaveRestoreBuffer::EntityFlagsSet) },
	//{ 0x01DC5660, "_ZN18CSaveRestoreBuffer12BufferRewindEi", mfunc_ptr_cast(&CSaveRestoreBuffer::BufferRewind) },	// NOXREF
	//{ 0x01DC5690, "_ZN18CSaveRestoreBuffer10HashStringEPKc", mfunc_ptr_cast(&CSaveRestoreBuffer::HashString) },	// NOXREF
	{ 0x01DC56B0, "_ZN18CSaveRestoreBuffer9TokenHashEPKc", mfunc_ptr_cast(&CSaveRestoreBuffer::TokenHash) },
	//{ 0x01DC57C0, "_ZN5CSave9WriteDataEPKciS1_", mfunc_ptr_cast(&CSave::WriteData) },	// NOXREF
	//{ 0x01DC58F0, "_ZN5CSave10WriteShortEPKcPKsi", mfunc_ptr_cast(&CSave::WriteShort) },	// NOXREF
	//{ 0x01DC5A30, "_ZN5CSave8WriteIntEPKcPKii", mfunc_ptr_cast(&CSave::WriteInt) },	// NOXREF
	//{ 0x01DC5B70, "_ZN5CSave10WriteFloatEPKcPKfi", mfunc_ptr_cast(&CSave::WriteFloat) },	// NOXREF
	//{ 0x01DC5CB0, "_ZN5CSave9WriteTimeEPKcPKfi", mfunc_ptr_cast(&CSave::WriteTime) },	// NOXREF
	//{ 0x01DC5DF0, "_ZN5CSave11WriteStringEPKcS1_", mfunc_ptr_cast<WRITESTRING_>(&CSave::WriteString) },	// NOXREF
	//{ 0x01DC5F30, "_ZN5CSave11WriteStringEPKcPKii", mfunc_ptr_cast<WRITESTRING_COUNT>(&CSave::WriteString) },	// NOXREF
	//{ 0x01DC60C0, "_ZN5CSave11WriteVectorEPKcRK6Vector", mfunc_ptr_cast<WRITEVECTOR_>(&CSave::WriteVector) },	// NOXREF
	//{ 0x01DC61E0, "_ZN5CSave11WriteVectorEPKcPKfi", mfunc_ptr_cast<WRITEVECTOR_COUNT>(&CSave::WriteVector) },	// NOXREF
	//{ 0x01DC6310, "_ZN5CSave19WritePositionVectorEPKcRK6Vector", mfunc_ptr_cast<WRITEPOSITIONVECTOR_>(&CSave::WritePositionVector) },	// NOXREF
	//{ 0x01DC64F0, "_ZN5CSave19WritePositionVectorEPKcPKfi", mfunc_ptr_cast<WRITEPOSITIONVECTOR_COUNT>(&CSave::WritePositionVector) },	// NOXREF
	//{ 0x01DC6670, "_ZN5CSave13WriteFunctionEPKcPPvi", mfunc_ptr_cast(&CSave::WriteFunction) },	// NOXREF
	{ 0x01DC67E0, "_Z15EntvarsKeyvalueP9entvars_sP14KeyValueData_s", (size_t)&EntvarsKeyvalue },
	{ 0x01DC6990, "_ZN5CSave12WriteEntVarsEPKcP9entvars_s", mfunc_ptr_cast(&CSave::WriteEntVars) },
	{ 0x01DC69B0, "_ZN5CSave11WriteFieldsEPKcPvP15TYPEDESCRIPTIONi", mfunc_ptr_cast(&CSave::WriteFields) },
	//{ 0x01DC6E60, "_ZN5CSave12BufferStringEPci", mfunc_ptr_cast(&CSave::BufferString) },	// NOXREF
	//{ 0x01DC6F20, "_ZN5CSave9DataEmptyEPKci", mfunc_ptr_cast(&CSave::DataEmpty) },	// NOXREF
	{ 0x01DC6F50, "_ZN5CSave11BufferFieldEPKciS1_", mfunc_ptr_cast(&CSave::BufferField) },
	{ 0x01DC7080, "_ZN5CSave12BufferHeaderEPKci", mfunc_ptr_cast(&CSave::BufferHeader) },
	{ 0x01DC7150, "_ZN5CSave10BufferDataEPKci", mfunc_ptr_cast(&CSave::BufferData) },
	{ 0x01DC71C0, "_ZN8CRestore9ReadFieldEPvP15TYPEDESCRIPTIONiiiPcS0_", mfunc_ptr_cast(&CRestore::ReadField) },
	{ 0x01DC7610, "_ZN8CRestore11ReadEntVarsEPKcP9entvars_s", mfunc_ptr_cast(&CRestore::ReadEntVars) },
	{ 0x01DC7630, "_ZN8CRestore10ReadFieldsEPKcPvP15TYPEDESCRIPTIONi", mfunc_ptr_cast(&CRestore::ReadFields) },
	{ 0x01DC78D0, "_ZN8CRestore10ReadFieldsEPKcPvP15TYPEDESCRIPTIONi", mfunc_ptr_cast(&CRestore::Empty) },
	//{ 0x01DC78F0, "_ZN8CRestore16BufferReadHeaderEP6HEADER", mfunc_ptr_cast(&CRestore::BufferReadHeader) },	// NOXREF
	//{ 0x01DC7A20, "_ZN8CRestore9ReadShortEv", mfunc_ptr_cast(&CRestore::ReadShort) },				// NOXREF
	//{ 0x01DC7A90, "_ZN8CRestore7ReadIntEv", mfunc_ptr_cast(&CRestore::ReadInt) },					// NOXREF
	//{ 0x01DC7AF0, "_ZN8CRestore12ReadNamedIntEPKc", mfunc_ptr_cast(&CRestore::ReadNamedInt) },			// NOXREF
	//{ 0x01DC7C10, "_ZN8CRestore15ReadNamedStringEPKc", mfunc_ptr_cast(&CRestore::ReadNamedString) },		// NOXREF
	//{ 0x01DC7D30, "_ZN8CRestore13BufferPointerEv", mfunc_ptr_cast(&CRestore::BufferPointer) },			// NOXREF
	{ 0x01DC7D40, "_ZN8CRestore15BufferReadBytesEPci", mfunc_ptr_cast(&CRestore::BufferReadBytes) },
	//{ 0x01DC7DC0, "_ZN8CRestore15BufferSkipBytesEi", mfunc_ptr_cast(&CRestore::BufferSkipBytes) },		// NOXREF
	//{ 0x01DC7E20, "_ZN8CRestore17BufferSkipZStringEv", mfunc_ptr_cast(&CRestore::BufferSkipZString) },		// NOXREF
	//{ 0x01DC7EA0, "_ZN8CRestore18BufferCheckZStringEPKc", mfunc_ptr_cast(&CRestore::BufferCheckZString) },	// NOXREF
	{ 0x01DC7EF0, "_Z15UTIL_TextureHitP11TraceResult6VectorS1_", (size_t)&UTIL_TextureHit },
	//{ 0x01DC8000, "GetPlayerTeam", (size_t)&GetPlayerTeam },	// NOXREF
	{ 0x01DC8040, "_Z11UTIL_IsGamePKc", (size_t)&UTIL_IsGame },
	{ 0x01DC8090, "_Z21UTIL_GetPlayerGaitYawi", (size_t)&UTIL_GetPlayerGaitYaw },
	{ 0x01D630B0, "_ZN7EHANDLE3GetEv", mfunc_ptr_cast(&EHANDLE::Get) },
	//{ 0x01D630D0, "_ZN7EHANDLE3SetEP7edict_s", mfunc_ptr_cast(&EHANDLE::Set) },	// NOXREF
	//{ 0x01D630F0, "_ZN7EHANDLEcvP11CBaseEntityEv", mfunc_ptr_cast(&EHANDLE::operator CBaseEntity*) },	// don't take the address
	//{ 0x01D63110, "_ZN7EHANDLEaSEP11CBaseEntity", mfunc_ptr_cast(&EHANDLE::CBaseEntity *operator=) },	// don't take the address
	//{ 0x01D63140, "_ZN7EHANDLEcviEv", mfunc_ptr_cast(&EHANDLE::operator int) },				// don't take the address
	//{ 0x01D63170, "_ZN7EHANDLEptEv", mfunc_ptr_cast(&EHANDLE::CBaseEntity *operator->) },			// don't take the address

#endif // Util_Region

#ifndef WeaponType_Region

	{ 0x01D01000, "_Z15AliasToWeaponIDPKc", (size_t)&AliasToWeaponID },
	{ 0x01D01050, "_Z18BuyAliasToWeaponIDPKcR12WeaponIdType", (size_t)&BuyAliasToWeaponID },
	{ 0x01D010C0, "_Z15WeaponIDToAliasi", (size_t)&WeaponIDToAlias },
	{ 0x01D010F0, "_Z18AliasToWeaponClassPKc", (size_t)&AliasToWeaponClass },
	{ 0x01D01140, "_Z21WeaponIDToWeaponClassi", (size_t)&WeaponIDToWeaponClass },
	{ 0x01D011C0, "_Z15IsPrimaryWeaponi", (size_t)&IsPrimaryWeapon },
	//{ 0x01D01250, "_Z17IsSecondaryWeaponi", (size_t)&IsSecondaryWeapon },	// NOXREF
	{ 0x01D012A0, "_Z13GetWeaponInfoi", (size_t)&GetWeaponInfo },
	{ 0x01D012E0, "_Z21CanBuyWeaponByMaptypei12WeaponIdTypeb", (size_t)&CanBuyWeaponByMaptype },

#endif // WeaponType_Region

#ifndef GameRules_Region

	//{ 0x01D80C90, "_Z16InstallGameRulesv", (size_t)&InstallGameRules },
	{ 0x01D80C00, "_ZN10CGameRules16RefreshSkillDataEv", mfunc_ptr_cast(&CGameRules::RefreshSkillData_) },
	{ 0x01D8EBB0, "_ZN10CGameRules10IsTeamplayEv", mfunc_ptr_cast(&CGameRules::IsTeamplay_) },
	{ 0x01D8EBC0, "_ZN10CGameRules18GetGameDescriptionEv", mfunc_ptr_cast(&CGameRules::GetGameDescription_) },
	//{ 0x01D8EBD0, "_ZN10CGameRules14UpdateGameModeEP11CBasePlayer", mfunc_ptr_cast(&CGameRules::UpdateGameMode_) },	// PURE
	{ 0x01D8EBE0, "_ZN10CGameRules20FPlayerCanTakeDamageEP11CBasePlayerP11CBaseEntity", mfunc_ptr_cast(&CGameRules::FPlayerCanTakeDamage_) },
	{ 0x01D8EBF0, "_ZN10CGameRules13ShouldAutoAimEP11CBasePlayerP7edict_s", mfunc_ptr_cast(&CGameRules::ShouldAutoAim_) },
	{ 0x01D80A60, "_ZN10CGameRules18GetPlayerSpawnSpotEP11CBasePlayer", mfunc_ptr_cast(&CGameRules::GetPlayerSpawnSpot_) },
	{ 0x01D8EC00, "_ZN10CGameRules24AllowAutoTargetCrosshairEv", mfunc_ptr_cast(&CGameRules::AllowAutoTargetCrosshair_) },
	{ 0x01D8EC10, "_ZN10CGameRules25ClientCommand_DeadOrAliveEP11CBasePlayerPKc", mfunc_ptr_cast(&CGameRules::ClientCommand_DeadOrAlive_) },
	{ 0x01D8EC60, "_ZN10CGameRules13ClientCommandEP11CBasePlayerPKc", mfunc_ptr_cast(&CGameRules::ClientCommand_) },
	//{ 0x01D8EC70, "_ZN10CGameRules21ClientUserInfoChangedEP11CBasePlayerPc", mfunc_ptr_cast(&CGameRules::ClientUserInfoChanged_) },	// PURE
	{ 0x01D80B60, "_ZN10CGameRules17CanHavePlayerItemEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CGameRules::CanHavePlayerItem_) },
	{ 0x01D80A20, "_ZN10CGameRules11CanHaveAmmoEP11CBasePlayerPKci", mfunc_ptr_cast(&CGameRules::CanHaveAmmo_) },
	{ 0x01D8EC80, "_ZN10CGameRules24FlHEVChargerRechargeTimeEv", mfunc_ptr_cast(&CGameRules::FlHEVChargerRechargeTime_) },
	{ 0x01D8EC90, "_ZN10CGameRules12GetTeamIndexEPKc", mfunc_ptr_cast(&CGameRules::GetTeamIndex_) },
	{ 0x01D8ED40, "_ZN10CGameRules18GetIndexedTeamNameEi", mfunc_ptr_cast(&CGameRules::GetIndexedTeamName_) },
	{ 0x01D8ED50, "_ZN10CGameRules11IsValidTeamEPKc", mfunc_ptr_cast(&CGameRules::IsValidTeam_) },
	//{ 0x01D8ED60, "_ZN10CGameRules16ChangePlayerTeamEP11CBasePlayerPKcii", mfunc_ptr_cast(&CGameRules::ChangePlayerTeam_) },	// PURE
	{ 0x01D8ED70, "_ZN10CGameRules20SetDefaultPlayerTeamEP11CBasePlayer", mfunc_ptr_cast(&CGameRules::SetDefaultPlayerTeam_) },
	{ 0x01D8ED80, "_ZN10CGameRules17PlayTextureSoundsEv", mfunc_ptr_cast(&CGameRules::PlayTextureSounds_) },
	//{ 0x01D8ED90, "_ZN10CGameRules18EndMultiplayerGameEv", mfunc_ptr_cast(&CGameRules::EndMultiplayerGame_) },	// PURE
	{ 0x01D8EDA0, "_ZN10CGameRules14IsFreezePeriodEv", mfunc_ptr_cast(&CGameRules::IsFreezePeriod_) },
	//{ 0x01D8EDB0, "_ZN10CGameRules16ServerDeactivateEv", mfunc_ptr_cast(&CGameRules::ServerDeactivate_) },	// PURE
	//{ 0x01D8EDC0, "_ZN10CGameRules18CheckMapConditionsEv", mfunc_ptr_cast(&CGameRules::CheckMapConditions_) },	// PURE
	
#endif // GameRules_Region

#ifndef Singleplay_GameRules_Region

	//{ 0x01DB6730, "", mfunc_ptr_cast(&CHalfLifeRules::CHalfLifeRules) },
	{ 0x01DB6750, "_ZN14CHalfLifeRules5ThinkEv", mfunc_ptr_cast(&CHalfLifeRules::Think_) },	// PURE
	{ 0x01DB6AF0, "_ZN14CHalfLifeRules16IsAllowedToSpawnEP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeRules::IsAllowedToSpawn_) },
	{ 0x01DB6BB0, "_ZN14CHalfLifeRules16FAllowFlashlightEv", mfunc_ptr_cast(&CHalfLifeRules::FAllowFlashlight_) },
	{ 0x01DB6790, "_ZN14CHalfLifeRules19FShouldSwitchWeaponEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::FShouldSwitchWeapon_) },
	{ 0x01DB67C0, "_ZN14CHalfLifeRules17GetNextBestWeaponEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::GetNextBestWeapon_) },
	{ 0x01DB6760, "_ZN14CHalfLifeRules13IsMultiplayerEv", mfunc_ptr_cast(&CHalfLifeRules::IsMultiplayer_) },
	{ 0x01DB6770, "_ZN14CHalfLifeRules12IsDeathmatchEv", mfunc_ptr_cast(&CHalfLifeRules::IsDeathmatch_) },
	{ 0x01DB6780, "_ZN14CHalfLifeRules6IsCoOpEv", mfunc_ptr_cast(&CHalfLifeRules::IsCoOp_) },
	{ 0x01DB67D0, "_ZN14CHalfLifeRules15ClientConnectedEP7edict_sPKcS3_Pc", mfunc_ptr_cast(&CHalfLifeRules::ClientConnected_) },
	{ 0x01DB67E0, "_ZN14CHalfLifeRules7InitHUDEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::InitHUD_) },	// PURE
	{ 0x01DB67F0, "_ZN14CHalfLifeRules18ClientDisconnectedEP7edict_s", mfunc_ptr_cast(&CHalfLifeRules::ClientDisconnected_) },	// PURE
	{ 0x01DB6800, "_ZN14CHalfLifeRules18FlPlayerFallDamageEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::FlPlayerFallDamage_) },
	{ 0x01DB6820, "_ZN14CHalfLifeRules11PlayerSpawnEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::PlayerSpawn_) },
	{ 0x01DB68A0, "_ZN14CHalfLifeRules11PlayerThinkEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::PlayerThink_) },	// PURE
	{ 0x01DB68B0, "_ZN14CHalfLifeRules17FPlayerCanRespawnEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::FPlayerCanRespawn_) },
	{ 0x01DB68C0, "_ZN14CHalfLifeRules17FlPlayerSpawnTimeEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::FlPlayerSpawnTime_) },
	{ 0x01DB6960, "_ZN14CHalfLifeRules18GetPlayerSpawnSpotEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::GetPlayerSpawnSpot_) },
	{ 0x01DB6890, "_ZN14CHalfLifeRules24AllowAutoTargetCrosshairEv", mfunc_ptr_cast(&CHalfLifeRules::AllowAutoTargetCrosshair_) },
	{ 0x01DB68D0, "_ZN14CHalfLifeRules14IPointsForKillEP11CBasePlayerS1_", mfunc_ptr_cast(&CHalfLifeRules::IPointsForKill_) },
	{ 0x01DB68E0, "_ZN14CHalfLifeRules12PlayerKilledEP11CBasePlayerP9entvars_sS3_", mfunc_ptr_cast(&CHalfLifeRules::PlayerKilled_) },	// PURE
	{ 0x01DB68F0, "_ZN14CHalfLifeRules11DeathNoticeEP11CBasePlayerP9entvars_sS3_", mfunc_ptr_cast(&CHalfLifeRules::DeathNotice_) },		// PURE
	{ 0x01DB6900, "_ZN14CHalfLifeRules15PlayerGotWeaponEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::PlayerGotWeapon_) },	// PURE
	{ 0x01DB6A70, "_ZN14CHalfLifeRules19WeaponShouldRespawnEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::WeaponShouldRespawn_) },
	{ 0x01DB6910, "_ZN14CHalfLifeRules19FlWeaponRespawnTimeEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::FlWeaponRespawnTime_) },
	{ 0x01DB6920, "_ZN14CHalfLifeRules18FlWeaponTryRespawnEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::FlWeaponTryRespawn_) },
	{ 0x01DB6930, "_ZN14CHalfLifeRules20VecWeaponRespawnSpotEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeRules::VecWeaponRespawnSpot_) },
	{ 0x01DB6A80, "_ZN14CHalfLifeRules11CanHaveItemEP11CBasePlayerP5CItem", mfunc_ptr_cast(&CHalfLifeRules::CanHaveItem_) },
	{ 0x01DB6A90, "_ZN14CHalfLifeRules13PlayerGotItemEP11CBasePlayerP5CItem", mfunc_ptr_cast(&CHalfLifeRules::PlayerGotItem_) },		// PURE
	{ 0x01DB6AA0, "_ZN14CHalfLifeRules17ItemShouldRespawnEP5CItem", mfunc_ptr_cast(&CHalfLifeRules::ItemShouldRespawn_) },
	{ 0x01DB6AB0, "_ZN14CHalfLifeRules17FlItemRespawnTimeEP5CItem", mfunc_ptr_cast(&CHalfLifeRules::FlItemRespawnTime_) },
	{ 0x01DB6AC0, "_ZN14CHalfLifeRules18VecItemRespawnSpotEP5CItem", mfunc_ptr_cast(&CHalfLifeRules::VecItemRespawnSpot_) },
	{ 0x01DB6B00, "_ZN14CHalfLifeRules13PlayerGotAmmoEP11CBasePlayerPci", mfunc_ptr_cast(&CHalfLifeRules::PlayerGotAmmo_) },		// PURE
	{ 0x01DB6B10, "_ZN14CHalfLifeRules17AmmoShouldRespawnEP15CBasePlayerAmmo", mfunc_ptr_cast(&CHalfLifeRules::AmmoShouldRespawn_) },
	{ 0x01DB6B20, "_ZN14CHalfLifeRules17FlAmmoRespawnTimeEP15CBasePlayerAmmo", mfunc_ptr_cast(&CHalfLifeRules::FlAmmoRespawnTime_) },
	{ 0x01DB6B30, "_ZN14CHalfLifeRules18VecAmmoRespawnSpotEP15CBasePlayerAmmo", mfunc_ptr_cast(&CHalfLifeRules::VecAmmoRespawnSpot_) },
	{ 0x01DB6B60, "_ZN14CHalfLifeRules27FlHealthChargerRechargeTimeEv", mfunc_ptr_cast(&CHalfLifeRules::FlHealthChargerRechargeTime_) },
	{ 0x01DB6B70, "_ZN14CHalfLifeRules17DeadPlayerWeaponsEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::DeadPlayerWeapons_) },
	{ 0x01DB6B80, "_ZN14CHalfLifeRules14DeadPlayerAmmoEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeRules::DeadPlayerAmmo_) },
	{ 0x01DB6BC0, "_ZN14CHalfLifeRules9GetTeamIDEP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeRules::GetTeamID_) },
	{ 0x01DB6B90, "_ZN14CHalfLifeRules18PlayerRelationshipEP11CBasePlayerP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeRules::PlayerRelationship_) },
	{ 0x01DB6BA0, "_ZN14CHalfLifeRules14FAllowMonstersEv", mfunc_ptr_cast(&CHalfLifeRules::FAllowMonsters_) },

#endif // Singleplay_GameRules_Region

#ifndef Multiplay_GameRules_Region

//CHalfLifeMultiplay
	//virtual func
	//{ 0x01D8B8A0, "_ZN18CHalfLifeMultiplayC2Ev", mfunc_ptr_cast(&CHalfLifeMultiplay::CHalfLifeMultiplay) },	// constuctor
	{ 0x01D8BF00, "_ZN18CHalfLifeMultiplay16RefreshSkillDataEv", mfunc_ptr_cast(&CHalfLifeMultiplay::RefreshSkillData_) },
	{ 0x01D8F420, "_ZN18CHalfLifeMultiplay5ThinkEv", mfunc_ptr_cast(&CHalfLifeMultiplay::Think_) },
	{ 0x01D921D0, "_ZN18CHalfLifeMultiplay16IsAllowedToSpawnEP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeMultiplay::IsAllowedToSpawn_) },
	{ 0x01D92410, "_ZN18CHalfLifeMultiplay16FAllowFlashlightEv", mfunc_ptr_cast(&CHalfLifeMultiplay::FAllowFlashlight_) },
	{ 0x01D909E0, "_ZN18CHalfLifeMultiplay19FShouldSwitchWeaponEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::FShouldSwitchWeapon_) },
	{ 0x01D90A70, "_ZN18CHalfLifeMultiplay17GetNextBestWeaponEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::GetNextBestWeapon_) },
	{ 0x01D909B0, "_ZN18CHalfLifeMultiplay13IsMultiplayerEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsMultiplayer_) },
	{ 0x01D909C0, "_ZN18CHalfLifeMultiplay12IsDeathmatchEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsDeathmatch_) },
	{ 0x01D909D0, "_ZN18CHalfLifeMultiplay6IsCoOpEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsCoOp_) },
	{ 0x01D90B60, "_ZN18CHalfLifeMultiplay15ClientConnectedEP7edict_sPKcS3_Pc", mfunc_ptr_cast(&CHalfLifeMultiplay::ClientConnected_) },
	{ 0x01D90BC0, "_ZN18CHalfLifeMultiplay7InitHUDEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::InitHUD_) },
	{ 0x01D910E0, "_ZN18CHalfLifeMultiplay18ClientDisconnectedEP7edict_s", mfunc_ptr_cast(&CHalfLifeMultiplay::ClientDisconnected_) },
	{ 0x01D90B80, "_ZN18CHalfLifeMultiplay14UpdateGameModeEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::UpdateGameMode_) },
	{ 0x01D91360, "_ZN18CHalfLifeMultiplay18FlPlayerFallDamageEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::FlPlayerFallDamage_) },
	{ 0x01D91390, "_ZN18CHalfLifeMultiplay20FPlayerCanTakeDamageEP11CBasePlayerP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeMultiplay::FPlayerCanTakeDamage_) },
	{ 0x01D91560, "_ZN18CHalfLifeMultiplay11PlayerSpawnEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerSpawn_) },
	{ 0x01D913E0, "_ZN18CHalfLifeMultiplay11PlayerThinkEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerThink_) },
	{ 0x01D915F0, "_ZN18CHalfLifeMultiplay17FPlayerCanRespawnEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::FPlayerCanRespawn_) },
	{ 0x01D916C0, "_ZN18CHalfLifeMultiplay17FlPlayerSpawnTimeEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::FlPlayerSpawnTime_) },
	{ 0x01D92280, "_ZN18CHalfLifeMultiplay18GetPlayerSpawnSpotEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::GetPlayerSpawnSpot_) },
	{ 0x01D916D0, "_ZN18CHalfLifeMultiplay24AllowAutoTargetCrosshairEv", mfunc_ptr_cast(&CHalfLifeMultiplay::AllowAutoTargetCrosshair_) },
	{ 0x01D90B30, "_ZN18CHalfLifeMultiplay25ClientCommand_DeadOrAliveEP11CBasePlayerPKc", mfunc_ptr_cast(&CHalfLifeMultiplay::ClientCommand_DeadOrAlive_) },
	{ 0x01D90B50, "_ZN18CHalfLifeMultiplay13ClientCommandEP11CBasePlayerPKc", mfunc_ptr_cast(&CHalfLifeMultiplay::ClientCommand_) },
	{ 0x01D93660, "_ZN18CHalfLifeMultiplay21ClientUserInfoChangedEP11CBasePlayerPc", mfunc_ptr_cast(&CHalfLifeMultiplay::ClientUserInfoChanged_) },
	{ 0x01D916E0, "_ZN18CHalfLifeMultiplay14IPointsForKillEP11CBasePlayerS1_", mfunc_ptr_cast(&CHalfLifeMultiplay::IPointsForKill_) },
	{ 0x01D916F0, "_ZN18CHalfLifeMultiplay12PlayerKilledEP11CBasePlayerP9entvars_sS3_", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerKilled_) },
	{ 0x01D91BE0, "_ZN18CHalfLifeMultiplay11DeathNoticeEP11CBasePlayerP9entvars_sS3_", mfunc_ptr_cast(&CHalfLifeMultiplay::DeathNotice_) },
	{ 0x01D92130, "_ZN18CHalfLifeMultiplay17CanHavePlayerItemEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::CanHavePlayerItem_) },
	//{ 0x01D92060, "_ZN18CHalfLifeMultiplay15PlayerGotWeaponEP11CBasePlayerP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerGotWeapon_) },	// PURE
	{ 0x01D92110, "_ZN18CHalfLifeMultiplay19WeaponShouldRespawnEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::WeaponShouldRespawn_) },
	{ 0x01D92070, "_ZN18CHalfLifeMultiplay19FlWeaponRespawnTimeEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::FlWeaponRespawnTime_) },
	{ 0x01D92080, "_ZN18CHalfLifeMultiplay18FlWeaponTryRespawnEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::FlWeaponTryRespawn_) },
	{ 0x01D920E0, "_ZN18CHalfLifeMultiplay20VecWeaponRespawnSpotEP15CBasePlayerItem", mfunc_ptr_cast(&CHalfLifeMultiplay::VecWeaponRespawnSpot_) },
	{ 0x01D92140, "_ZN18CHalfLifeMultiplay11CanHaveItemEP11CBasePlayerP5CItem", mfunc_ptr_cast(&CHalfLifeMultiplay::CanHaveItem_) },
	{ 0x01D92150, "_ZN18CHalfLifeMultiplay13PlayerGotItemEP11CBasePlayerP5CItem", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerGotItem_) },	// PURE
	{ 0x01D92160, "_ZN18CHalfLifeMultiplay17ItemShouldRespawnEP5CItem", mfunc_ptr_cast(&CHalfLifeMultiplay::ItemShouldRespawn_) },
	{ 0x01D92180, "_ZN18CHalfLifeMultiplay17FlItemRespawnTimeEP5CItem", mfunc_ptr_cast(&CHalfLifeMultiplay::FlItemRespawnTime_) },
	{ 0x01D92190, "_ZN18CHalfLifeMultiplay18VecItemRespawnSpotEP5CItem", mfunc_ptr_cast(&CHalfLifeMultiplay::VecItemRespawnSpot_) },
	{ 0x01D921C0, "_ZN18CHalfLifeMultiplay13PlayerGotAmmoEP11CBasePlayerPci", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerGotAmmo_) },
	{ 0x01D921E0, "_ZN18CHalfLifeMultiplay17AmmoShouldRespawnEP15CBasePlayerAmmo", mfunc_ptr_cast(&CHalfLifeMultiplay::AmmoShouldRespawn_) },
	{ 0x01D92200, "_ZN18CHalfLifeMultiplay17FlAmmoRespawnTimeEP15CBasePlayerAmmo", mfunc_ptr_cast(&CHalfLifeMultiplay::FlAmmoRespawnTime_) },
	{ 0x01D92210, "_ZN18CHalfLifeMultiplay18VecAmmoRespawnSpotEP15CBasePlayerAmmo", mfunc_ptr_cast(&CHalfLifeMultiplay::VecAmmoRespawnSpot_) },
	{ 0x01D92240, "_ZN18CHalfLifeMultiplay27FlHealthChargerRechargeTimeEv", mfunc_ptr_cast(&CHalfLifeMultiplay::FlHealthChargerRechargeTime_) },
	{ 0x01D92250, "_ZN18CHalfLifeMultiplay24FlHEVChargerRechargeTimeEv", mfunc_ptr_cast(&CHalfLifeMultiplay::FlHEVChargerRechargeTime_) },
	{ 0x01D92260, "_ZN18CHalfLifeMultiplay17DeadPlayerWeaponsEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::DeadPlayerWeapons_) },
	{ 0x01D92270, "_ZN18CHalfLifeMultiplay14DeadPlayerAmmoEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::DeadPlayerAmmo_) },
	{ 0x01D8EDD0, "_ZN18CHalfLifeMultiplay9GetTeamIDEP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeMultiplay::GetTeamID_) },
	{ 0x01D922D0, "_ZN18CHalfLifeMultiplay18PlayerRelationshipEP11CBasePlayerP11CBaseEntity", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerRelationship_) },
	{ 0x01D8EDE0, "_ZN18CHalfLifeMultiplay17PlayTextureSoundsEv", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayTextureSounds_) },
	{ 0x01D92450, "_ZN18CHalfLifeMultiplay14FAllowMonstersEv", mfunc_ptr_cast(&CHalfLifeMultiplay::FAllowMonsters_) },
	{ 0x01D8EE20, "_ZN18CHalfLifeMultiplay18EndMultiplayerGameEv", mfunc_ptr_cast(&CHalfLifeMultiplay::EndMultiplayerGame_) },
	{ 0x01D8B4B0, "_ZN18CHalfLifeMultiplay16ServerDeactivateEv", mfunc_ptr_cast(&CHalfLifeMultiplay::ServerDeactivate_) },
	{ 0x01D8DFD0, "_ZN18CHalfLifeMultiplay18CheckMapConditionsEv", mfunc_ptr_cast(&CHalfLifeMultiplay::CheckMapConditions_) },
	{ 0x01D8C050, "_ZN18CHalfLifeMultiplay10CleanUpMapEv", mfunc_ptr_cast(&CHalfLifeMultiplay::CleanUpMap_) },
	{ 0x01D8E0A0, "_ZN18CHalfLifeMultiplay12RestartRoundEv", mfunc_ptr_cast(&CHalfLifeMultiplay::RestartRound_) },
	{ 0x01D8CAF0, "_ZN18CHalfLifeMultiplay18CheckWinConditionsEv", mfunc_ptr_cast(&CHalfLifeMultiplay::CheckWinConditions_) },
	{ 0x01D8BF60, "_ZN18CHalfLifeMultiplay10RemoveGunsEv", mfunc_ptr_cast(&CHalfLifeMultiplay::RemoveGuns_) },
	{ 0x01D8C340, "_ZN18CHalfLifeMultiplay6GiveC4Ev", mfunc_ptr_cast(&CHalfLifeMultiplay::GiveC4_) },
	{ 0x01D93270, "_ZN18CHalfLifeMultiplay11ChangeLevelEv", mfunc_ptr_cast(&CHalfLifeMultiplay::ChangeLevel_) },
	{ 0x01D92480, "_ZN18CHalfLifeMultiplay16GoToIntermissionEv", mfunc_ptr_cast(&CHalfLifeMultiplay::GoToIntermission_) },
	//non-virtual func
	{ 0x01D8B4A0, "_ZN18CHalfLifeMultiplay8IsCareerEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsCareer) },
	{ 0x01D8C800, "_ZN18CHalfLifeMultiplay23QueueCareerRoundEndMenuEfi", mfunc_ptr_cast(&CHalfLifeMultiplay::QueueCareerRoundEndMenu) },
	//{ 0x01D8B470, "_ZN18CHalfLifeMultiplay19SetCareerMatchLimitEii", mfunc_ptr_cast(&CHalfLifeMultiplay::SetCareerMatchLimit) },	// NOXREF
	//{ 0x01D8B310, "_ZN18CHalfLifeMultiplay15IsInCareerRoundEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsInCareerRound) },	// NOXREF
	//{ 0x01D908F0, "_ZN18CHalfLifeMultiplay13CareerRestartEv", mfunc_ptr_cast(&CHalfLifeMultiplay::CareerRestart) },	// NOXREF
	//{ 0x0, "_ZN18CHalfLifeMultiplay16PlayerJoinedTeamEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::PlayerJoinedTeam) },	// NOXREF
	{ 0x01D8EC20, "_ZN18CHalfLifeMultiplay8TeamFullEi", mfunc_ptr_cast(&CHalfLifeMultiplay::TeamFull) },
	{ 0x01D8ECA0, "_ZN18CHalfLifeMultiplay11TeamStackedEii", mfunc_ptr_cast(&CHalfLifeMultiplay::TeamStacked) },
	{ 0x01D8EE30, "_ZN18CHalfLifeMultiplay15IsVIPQueueEmptyEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsVIPQueueEmpty) },
	{ 0x01D8EEA0, "_ZN18CHalfLifeMultiplay13AddToVIPQueueEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeMultiplay::AddToVIPQueue) },
	{ 0x01D8F0D0, "_ZN18CHalfLifeMultiplay11PickNextVIPEv", mfunc_ptr_cast(&CHalfLifeMultiplay::PickNextVIP) },
	//{ 0x01D90790, "_ZN18CHalfLifeMultiplay19HasRoundTimeExpiredEv", mfunc_ptr_cast(&CHalfLifeMultiplay::HasRoundTimeExpired) },	// NOXREF
	//{ 0x01D90820, "_ZN18CHalfLifeMultiplay13IsBombPlantedEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsBombPlanted) },	// NOXREF
	//{ 0x01D90860, "_ZN18CHalfLifeMultiplay51MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRoundEi", mfunc_ptr_cast(&CHalfLifeMultiplay::MarkLivingPlayersOnTeamAsNotReceivingMoneyNextRound) },	// NOXREF
	{ 0x01D8EDF0, "_ZN18CHalfLifeMultiplay13StackVIPQueueEv", mfunc_ptr_cast(&CHalfLifeMultiplay::StackVIPQueue) },
	{ 0x01D8EFA0, "_ZN18CHalfLifeMultiplay15ResetCurrentVIPEv", mfunc_ptr_cast(&CHalfLifeMultiplay::ResetCurrentVIP) },
	{ 0x01D8DDB0, "_ZN18CHalfLifeMultiplay12BalanceTeamsEv", mfunc_ptr_cast(&CHalfLifeMultiplay::BalanceTeams) },
	//{ 0x01D8DC40, "_ZN18CHalfLifeMultiplay14SwapAllPlayersEv", mfunc_ptr_cast(&CHalfLifeMultiplay::SwapAllPlayers) },	// NOXREF
	//{ 0x01D8BFE0, "_ZN18CHalfLifeMultiplay16UpdateTeamScoresEv", mfunc_ptr_cast(&CHalfLifeMultiplay::UpdateTeamScores) },	// NOXREF
	{ 0x01D92DB0, "_ZN18CHalfLifeMultiplay11DisplayMapsEP11CBasePlayeri", mfunc_ptr_cast(&CHalfLifeMultiplay::DisplayMaps) },
	//{ 0x01D92BF0, "_ZN18CHalfLifeMultiplay16ResetAllMapVotesEv", mfunc_ptr_cast(&CHalfLifeMultiplay::ResetAllMapVotes) },	// NOXREF
	{ 0x01D93080, "_ZN18CHalfLifeMultiplay14ProcessMapVoteEP11CBasePlayeri", mfunc_ptr_cast(&CHalfLifeMultiplay::ProcessMapVote) },
	{ 0x01D8EAC0, "_ZN18CHalfLifeMultiplay14IsThereABomberEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsThereABomber) },
	{ 0x01D8EB50, "_ZN18CHalfLifeMultiplay12IsThereABombEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsThereABomb) },
	//{ 0x0, "_ZN18CHalfLifeMultiplay14IsMatchStartedEv", mfunc_ptr_cast(&CHalfLifeMultiplay::IsMatchStarted) },	// NOXREF
	{ 0x01D93530, "_ZN18CHalfLifeMultiplay16SendMOTDToClientEP7edict_s", mfunc_ptr_cast(&CHalfLifeMultiplay::SendMOTDToClient) },
	//non class func
	//{ 0x0, "", (size_t)&IsBotSpeaking },	// NOXREF
	{ 0x01D8B010, "_Z13SV_Continue_fv", (size_t)&SV_Continue_f },
	{ 0x01D8B0C0, "_Z17SV_Tutor_Toggle_fv", (size_t)&SV_Tutor_Toggle_f },
	{ 0x01D8B110, "_Z19SV_Career_Restart_fv", (size_t)&SV_Career_Restart_f },
	{ 0x01D8B1F0, "_Z20SV_Career_EndRound_fv", (size_t)&SV_Career_EndRound_f },
	{ 0x01D8B350, "_Z18SV_CareerAddTask_fv", (size_t)&SV_CareerAddTask_f },
	{ 0x01D8B400, "_Z21SV_CareerMatchLimit_fv", (size_t)&SV_CareerMatchLimit_f },
	{ 0x01D8B6E0, "_Z9BroadcastPKc", (size_t)&Broadcast },
	{ 0x01D8B780, "_Z7GetTeami", (size_t)&GetTeam },
	{ 0x01D8B7B0, "_Z15EndRoundMessagePKci", (size_t)&EndRoundMessage },
	{ 0x01D8BD80, "_ZL18ReadMultiplayCvarsP18CHalfLifeMultiplay", (size_t)&ReadMultiplayCvars },
	//{ 0x01D92670, "_Z15DestroyMapCycleP10mapcycle_s", (size_t)&DestroyMapCycle },	// NOXREF
	{ 0x01D926B0, "_Z15MP_COM_GetTokenv", (size_t)&MP_COM_GetToken },
	{ 0x01D926C0, "_Z12MP_COM_ParsePc", (size_t)&MP_COM_Parse },
	//{ 0x01D927A0, "_Z19MP_COM_TokenWaitingPc", (size_t)&MP_COM_TokenWaiting },	// NOXREF
	{ 0x01D927F0, "_Z18ReloadMapCycleFilePcP10mapcycle_s", (size_t)&ReloadMapCycleFile },
	//{ 0x01D92AB0, "_Z12CountPlayersv", (size_t)&CountPlayers },	// NOXREF
	{ 0x01D92AF0, "_Z20ExtractCommandStringPcS_", (size_t)&ExtractCommandString },
	{ 0x01D92D10, "_Z11GetMapCountv", (size_t)&GetMapCount },
//CCStrikeGameMgrHelper
	//virtual func
	{ 0x01D8B630, "_ZN21CCStrikeGameMgrHelper19CanPlayerHearPlayerEP11CBasePlayerS1_", mfunc_ptr_cast(&CCStrikeGameMgrHelper::CanPlayerHearPlayer_) },
//CMapInfo
	//virtual func
	{ 0x01D8B5E0, "_ZN21CCStrikeGameMgrHelper19CanPlayerHearPlayerEP11CBasePlayerS1_", mfunc_ptr_cast(&CMapInfo::Spawn_) },
	{ 0x01D8B540, "_ZN21CCStrikeGameMgrHelper19CanPlayerHearPlayerEP11CBasePlayerS1_", mfunc_ptr_cast(&CMapInfo::KeyValue_) },
// linked objects
	{ 0x01D8B4F0, "info_map_parameters", (size_t)&info_map_parameters },

#endif // Multiplay_GameRules_Region

#ifndef Training_Gamerules_Region
	
//CHalfLifeTraining
	//virtual func
	//{ 0x01DBBE50, "_ZN17CHalfLifeTrainingC2Ev", mfunc_ptr_cast(&CHalfLifeTraining::CHalfLifeTraining) }
	{ 0x01DBBE70, "_ZN17CHalfLifeTraining13IsMultiplayerEv", mfunc_ptr_cast(&CHalfLifeTraining::IsMultiplayer_) },
	{ 0x01DBBE90, "_ZN17CHalfLifeTraining12IsDeathmatchEv", mfunc_ptr_cast(&CHalfLifeTraining::IsDeathmatch_) },
	{ 0x01DBBEA0, "_ZN17CHalfLifeTraining7InitHUDEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeTraining::InitHUD_) },	// PURE
	{ 0x01DBC3E0, "_ZN17CHalfLifeTraining11PlayerSpawnEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeTraining::PlayerSpawn_) },
	{ 0x01DBC010, "_ZN17CHalfLifeTraining11PlayerThinkEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeTraining::PlayerThink_) },
	{ 0x01DBC4C0, "_ZN17CHalfLifeTraining17FPlayerCanRespawnEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeTraining::FPlayerCanRespawn_) },
	{ 0x01DBBEE0, "_ZN17CHalfLifeTraining18GetPlayerSpawnSpotEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeTraining::GetPlayerSpawnSpot_) },
	{ 0x01DBC4E0, "_ZN17CHalfLifeTraining12PlayerKilledEP11CBasePlayerP9entvars_sS3_", mfunc_ptr_cast(&CHalfLifeTraining::PlayerKilled_) },
	{ 0x01DBC4B0, "_ZN17CHalfLifeTraining17ItemShouldRespawnEP5CItem", mfunc_ptr_cast(&CHalfLifeTraining::ItemShouldRespawn_) },
	//{ 0x01DBBE80, "_ZN17CHalfLifeTraining18CheckMapConditionsEv", mfunc_ptr_cast(&CHalfLifeTraining::CheckMapConditions_) },	// PURE
	{ 0x01DBC510, "_ZN17CHalfLifeTraining18CheckWinConditionsEv", mfunc_ptr_cast(&CHalfLifeTraining::CheckWinConditions_) },
	//non-virtual func
	{ 0x01DBBEB0, "_ZN17CHalfLifeTraining11HostageDiedEv", mfunc_ptr_cast(&CHalfLifeTraining::HostageDied) },
	{ 0x01DBC4D0, "_ZN17CHalfLifeTraining12PlayerCanBuyEP11CBasePlayer", mfunc_ptr_cast(&CHalfLifeTraining::PlayerCanBuy) },
//CBaseGrenCatch
	//virtual func
	{ 0x01DBC8B0, "_ZN14CBaseGrenCatch5SpawnEv", mfunc_ptr_cast(&CBaseGrenCatch::Spawn_) },
	{ 0x01DBCC00, "_ZN14CBaseGrenCatch8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CBaseGrenCatch::KeyValue_) },
	{ 0x01DBC7F0, "_ZN14CBaseGrenCatch4SaveER5CSave", mfunc_ptr_cast(&CBaseGrenCatch::Save_) },
	{ 0x01DBC820, "_ZN14CBaseGrenCatch7RestoreER8CRestore", mfunc_ptr_cast(&CBaseGrenCatch::Restore_) },
	{ 0x01DBC8A0, "_ZN14CBaseGrenCatch10ObjectCapsEv", mfunc_ptr_cast(&CBaseGrenCatch::ObjectCaps_) },
	{ 0x01DBC970, "_ZN14CBaseGrenCatch5ThinkEv", mfunc_ptr_cast(&CBaseGrenCatch::Think_) },
	{ 0x01DBC930, "_ZN14CBaseGrenCatch5TouchEP11CBaseEntity", mfunc_ptr_cast(&CBaseGrenCatch::Touch_) },
//CFuncWeaponCheck
	//virtual func
	{ 0x01DBCCE0, "_ZN16CFuncWeaponCheck5SpawnEv", mfunc_ptr_cast(&CFuncWeaponCheck::Spawn_) },
	{ 0x01DBCF70, "_ZN16CFuncWeaponCheck8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CFuncWeaponCheck::KeyValue_) },
	{ 0x01DBCD50, "_ZN16CFuncWeaponCheck4SaveER5CSave", mfunc_ptr_cast(&CFuncWeaponCheck::Save_) },
	{ 0x01DBCD80, "_ZN16CFuncWeaponCheck7RestoreER8CRestore", mfunc_ptr_cast(&CFuncWeaponCheck::Restore_) },
	{ 0x01DBCE00, "_ZN16CFuncWeaponCheck5TouchEP11CBaseEntity", mfunc_ptr_cast(&CFuncWeaponCheck::Touch_) },
// linked objects
	{ 0x01DBC850, "func_grencatch", (size_t)&func_grencatch },
	{ 0x01DBCDB0, "func_weaponcheck", (size_t)&func_weaponcheck },

#endif // Training_Gamerules_Region

#ifndef CareerTasks_Region

//CCareerTask
	//{ 0x01DDCBD0, "_ZN11CCareerTaskC2EPKc13GameEventTypeS1_ibbib", mfunc_ptr_cast(&CCareerTask::CCareerTask) },
	//virtual func
	{ 0x01DDD150, "_ZN11CCareerTask7OnEventE13GameEventTypeP11CBasePlayerS2_", mfunc_ptr_cast(&CCareerTask::OnEvent_) },
	{ 0x01DDCCD0, "_ZN11CCareerTask5ResetEv", mfunc_ptr_cast(&CCareerTask::Reset_) },
	{ 0x01DDDDE0, "_ZNK11CCareerTask26IsTaskCompletableThisRoundEv", mfunc_ptr_cast(&CCareerTask::IsTaskCompletableThisRound_) },
	//non-virtual func
	//{ 0x01DDCB80, "_ZN11CCareerTask7NewTaskEPKc13GameEventTypeS1_ibbib", mfunc_ptr_cast(&CCareerTask::NewTask) },
	{ 0x01DDCDB0, "_ZN11CCareerTask12OnWeaponKillEiibbP11CBasePlayerS1_", mfunc_ptr_cast(&CCareerTask::OnWeaponKill) },
	{ 0x01DDD000, "_ZN11CCareerTask14OnWeaponInjuryEiibP11CBasePlayer", mfunc_ptr_cast(&CCareerTask::OnWeaponInjury) },
	//{ 0x0, "_ZN11CCareerTask10IsCompleteEv", mfunc_ptr_cast(&CCareerTask::IsComplete) },
	//{ 0x0, "_ZN11CCareerTask11GetTaskNameEv", mfunc_ptr_cast(&CCareerTask::GetTaskName) },
	//{ 0x0, "_ZN11CCareerTask11GetWeaponIdEv", mfunc_ptr_cast(&CCareerTask::GetWeaponId) },
	//{ 0x0, "_ZN11CCareerTask16GetWeaponClassIdEv", mfunc_ptr_cast(&CCareerTask::GetWeaponClassId) },
	//{ 0x0, "_ZNK11CCareerTask10IsValidForEP11CBasePlayer ", mfunc_ptr_cast(&CCareerTask::IsValidFor) },
	//{ 0x01DDCD50, "_ZN11CCareerTask23SendPartialNotificationEv", mfunc_ptr_cast(&CCareerTask::SendPartialNotification) },	// NOXREF
//CCareerTaskManager
	//{ 0x01DDD7C0, "_ZN18CCareerTaskManagerC2Ev", mfunc_ptr_cast(&CCareerTaskManager::CCareerTaskManager) },
	//{ 0x01DDD750, "_ZN18CCareerTaskManager6CreateEv", mfunc_ptr_cast(&CCareerTaskManager::Create) },
	{ 0x01DDD800, "_ZN18CCareerTaskManager5ResetEb", mfunc_ptr_cast(&CCareerTaskManager::Reset) },
	{ 0x01DDD8D0, "_ZN18CCareerTaskManager7AddTaskEPKcS1_ibbb", mfunc_ptr_cast(&CCareerTaskManager::AddTask) },
	{ 0x01DDDA00, "_ZN18CCareerTaskManager11HandleEventE13GameEventTypeP11CBasePlayerS2_", mfunc_ptr_cast(&CCareerTaskManager::HandleEvent) },
	{ 0x01DDDAB0, "_ZN18CCareerTaskManager15HandleEnemyKillEbPKcbbP11CBasePlayerS3_", mfunc_ptr_cast(&CCareerTaskManager::HandleEnemyKill) },
	//{ 0x01DDDA60, "_ZN18CCareerTaskManager16HandleWeaponKillEiibbP11CBasePlayerS1_", mfunc_ptr_cast(&CCareerTaskManager::HandleWeaponKill) },	// NOXREF
	{ 0x01DDDC30, "_ZN18CCareerTaskManager11HandleDeathEiP11CBasePlayer", mfunc_ptr_cast(&CCareerTaskManager::HandleDeath) },
	//{ 0x01DDDB80, "_ZN18CCareerTaskManager18HandleWeaponInjuryEiibP11CBasePlayer", mfunc_ptr_cast(&CCareerTaskManager::HandleWeaponInjury) },	// NOXREF
	{ 0x01DDDBC0, "_ZN18CCareerTaskManager17HandleEnemyInjuryEPKcbP11CBasePlayer", mfunc_ptr_cast(&CCareerTaskManager::HandleEnemyInjury) },
	{ 0x01DDDCD0, "_ZN18CCareerTaskManager19AreAllTasksCompleteEv", mfunc_ptr_cast(&CCareerTaskManager::AreAllTasksComplete) },
	{ 0x01DDDD00, "_ZN18CCareerTaskManager20GetNumRemainingTasksEv", mfunc_ptr_cast(&CCareerTaskManager::GetNumRemainingTasks) },
	{ 0x01DDDD30, "_ZN18CCareerTaskManager19GetRoundElapsedTimeEv", mfunc_ptr_cast(&CCareerTaskManager::GetRoundElapsedTime) },
	//{ 0x0, "_ZN18CCareerTaskManager11GetTaskTimeEv", mfunc_ptr_cast(&CCareerTaskManager::GetTaskTime) },
	//{ 0x01DDD8B0, "_ZN18CCareerTaskManager19SetFinishedTaskTimeEi", mfunc_ptr_cast(&CCareerTaskManager::SetFinishedTaskTime) },	// NOXREF
	//{ 0x0, "_ZN18CCareerTaskManager19GetFinishedTaskTimeEv", mfunc_ptr_cast(&CCareerTaskManager::GetFinishedTaskTime) },
	//{ 0x0, "_ZN18CCareerTaskManager20GetFinishedTaskRoundEv", mfunc_ptr_cast(&CCareerTaskManager::GetFinishedTaskRound) },
	//{ 0x0, "_ZN18CCareerTaskManager8GetTasksEv", mfunc_ptr_cast(&CCareerTaskManager::GetTasks) },
	{ 0x01DDDD40, "_ZN18CCareerTaskManager20LatchRoundEndMessageEv", mfunc_ptr_cast(&CCareerTaskManager::LatchRoundEndMessage) },
	{ 0x01DDDD50, "_ZN18CCareerTaskManager22UnlatchRoundEndMessageEv", mfunc_ptr_cast(&CCareerTaskManager::UnlatchRoundEndMessage) },
//CPreventDefuseTask
	//virtual func
	//{ 0x01DDCA60, "_ZN18CPreventDefuseTaskC2EPKc13GameEventTypeS1_ibbib", mfunc_ptr_cast(&CPreventDefuseTask::CPreventDefuseTask) },
	{ 0x01DDCB30, "_ZN18CPreventDefuseTask7OnEventE13GameEventTypeP11CBasePlayerS2_", mfunc_ptr_cast(&CPreventDefuseTask::OnEvent_) },
	{ 0x01DDCAB0, "_ZN18CPreventDefuseTask5ResetEv", mfunc_ptr_cast(&CPreventDefuseTask::Reset_) },
	{ 0x01DDDDF0, "_ZNK18CPreventDefuseTask26IsTaskCompletableThisRoundEv", mfunc_ptr_cast(&CPreventDefuseTask::IsTaskCompletableThisRound_) },
	//non-virtual func
	//{ 0x01DDCA00, "_ZN18CPreventDefuseTask7NewTaskEPKc13GameEventTypeS1_ibbib", mfunc_ptr_cast(&CPreventDefuseTask::NewTask) },

#endif // CareerTasks_Region

#ifndef Weapons_Region

//Weapons base
	//{ 0x01DCCD60, "_Z12MaxAmmoCarryi", (size_t)&MaxAmmoCarry },	// NOXREF
	{ 0x01DCCE60, "_Z16ClearMultiDamagev", (size_t)&ClearMultiDamage },
	{ 0x01DCCE80, "_Z16ApplyMultiDamageP9entvars_sS0_", (size_t)&ApplyMultiDamage },
	{ 0x01DCCEB0, "_Z14AddMultiDamageP9entvars_sP11CBaseEntityfi", (size_t)&AddMultiDamage },
	{ 0x01DCCF20, "_Z10SpawnBlood6Vectorif", (size_t)&SpawnBlood },
	////{ 0x0, "_Z11DamageDecalP11CBaseEntityi", (size_t)&DamageDecal },	// NOXREF
	////{ 0x0, "_Z12DecalGunshotP11TraceResultibP9entvars_sb", (size_t)&DecalGunshot },	// NOXREF
	//{ 0x01DCCF90, "_Z10EjectBrassRK6VectorS1_S1_fiii", (size_t)&EjectBrass },
	//{ 0x0, "_Z11EjectBrass2RK6VectorS1_fiiP9entvars_s", (size_t)&EjectBrass2 },
	//{ 0x01DCD120, "_Z25AddAmmoNameToAmmoRegistryPKc", (size_t)&AddAmmoNameToAmmoRegistry },	// NOXREF
	{ 0x01DCD180, "_Z24UTIL_PrecacheOtherWeaponPKc", (size_t)&UTIL_PrecacheOtherWeapon },
	//{ 0x01DCD310, "_Z25UTIL_PrecacheOtherWeapon2PKc", (size_t)&UTIL_PrecacheOtherWeapon2 },	// NOXREF
	{ 0x01DCD4A0, "_Z10W_Precachev", (size_t)&W_Precache },
	//{ 0x01DCE600, "_Z9CanAttackffi", (size_t)&CanAttack },	// NOXREF
//CBasePlayerItem
	//virtual func
	//{ 0x01DCD860, "_ZN15CBasePlayerItem4SaveER5CSave", mfunc_ptr_cast(&CBasePlayerItem::Save_) },	// NOXREF
	//{ 0x01DCD890, "_ZN15CBasePlayerItem7RestoreER8CRestore", mfunc_ptr_cast(&CBasePlayerItem::Restore_) },	// NOXREF
	//{ 0x0, "_ZN15CBasePlayerItem21SetObjectCollisionBoxEv", mfunc_ptr_cast(&CBasePlayerItem::SetObjectCollisionBox) },
	//{ 0x01DCDC80, "_ZN15CBasePlayerItem7RespawnEv", mfunc_ptr_cast(&CBasePlayerItem::Respawn) },
	//{ 0x01DCEC60, "_ZN15CBasePlayerItem11AddToPlayerEP11CBasePlayer", mfunc_ptr_cast(&CBasePlayerItem::AddToPlayer_) },	// NOXREF
	//{ 0x0, "_ZN15CBasePlayerItem12AddDuplicateEPS_", mfunc_ptr_cast(&CBasePlayerItem::AddDuplicate) },	// NOXREF
	//{ 0x0, "_ZN15CBasePlayerItem11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CBasePlayerItem::GetItemInfo) },
	//{ 0x0, "_ZN15CBasePlayerItem9CanDeployEv", mfunc_ptr_cast(&CBasePlayerItem::CanDeploy) },

	//{ 0x0, "_ZN15CBasePlayerItem7CanDropEv", mfunc_ptr_cast(&CBasePlayerItem::CanDrop_) },
	//0x01DCF160 - CBasePlayerItem::???
	//0x01D861D0 - CBasePlayerItem::???
	
	//{ 0x0, "_ZN15CBasePlayerItem6DeployEv", mfunc_ptr_cast(&CBasePlayerItem::Deploy) },
	//{ 0x0, "_ZN15CBasePlayerItem8IsWeaponEv", mfunc_ptr_cast(&CBasePlayerItem::IsWeapon) },
	//{ 0x0, "_ZN15CBasePlayerItem10CanHolsterEv", mfunc_ptr_cast(&CBasePlayerItem::CanHolster) },
	//{ 0x01DCED10, "_ZN15CBasePlayerItem7HolsterEi", mfunc_ptr_cast(&CBasePlayerItem::Holster) },	// NOXREF
	//{ 0x0, "_ZN15CBasePlayerItem14UpdateItemInfoEv", mfunc_ptr_cast(&CBasePlayerItem::UpdateItemInfo) },	// NOXREF
	//{ 0x0, "_ZN15CBasePlayerItem12ItemPreFrameEv", mfunc_ptr_cast(&CBasePlayerItem::ItemPreFrame) },
	//{ 0x0, "_ZN15CBasePlayerItem13ItemPostFrameEv", mfunc_ptr_cast(&CBasePlayerItem::ItemPostFrame) },
	{ 0x01DCECB0, "_ZN15CBasePlayerItem4DropEv", mfunc_ptr_cast(&CBasePlayerItem::Drop_) },
	{ 0x01DCECE0, "_ZN15CBasePlayerItem4KillEv", mfunc_ptr_cast(&CBasePlayerItem::Kill_) },
	{ 0x01DCED40, "_ZN15CBasePlayerItem14AttachToPlayerEP11CBasePlayer", mfunc_ptr_cast(&CBasePlayerItem::AttachToPlayer_) },
	//{ 0x0, "_ZN15CBasePlayerItem16PrimaryAmmoIndexEv", mfunc_ptr_cast(&CBasePlayerItem::PrimaryAmmoIndex) },
	//{ 0x0, "_ZN15CBasePlayerItem18SecondaryAmmoIndexEv", mfunc_ptr_cast(&CBasePlayerItem::SecondaryAmmoIndex) },
	//{ 0x0, "_ZN15CBasePlayerItem16UpdateClientDataEP11CBasePlayer", mfunc_ptr_cast(&CBasePlayerItem::UpdateClientData) },
	//{ 0x0, "_ZN15CBasePlayerItem12GetWeaponPtrEv", mfunc_ptr_cast(&CBasePlayerItem::GetWeaponPtr) },
	//{ 0x0, "_ZN15CBasePlayerItem11GetMaxSpeedEv", mfunc_ptr_cast(&CBasePlayerItem::GetMaxSpeed) },
	//{ 0x0, "_ZN15CBasePlayerItem9iItemSlotEv", mfunc_ptr_cast(&CBasePlayerItem::iItemSlot) },
	//non-virtual func
	//{ 0x0, "_ZN15CBasePlayerItem11DestroyItemEv", mfunc_ptr_cast(&CBasePlayerItem::DestroyItem) },
	{ 0x01DCDD50, "_ZN15CBasePlayerItem12DefaultTouchEP11CBaseEntity", mfunc_ptr_cast(&CBasePlayerItem::DefaultTouch) },
	{ 0x01DCDAA0, "_ZN15CBasePlayerItem9FallThinkEv", mfunc_ptr_cast(&CBasePlayerItem::FallThink) },
	{ 0x01DCDB30, "_ZN15CBasePlayerItem11MaterializeEv", mfunc_ptr_cast(&CBasePlayerItem::Materialize) },
	//{ 0x0, "_ZN15CBasePlayerItem20AttemptToMaterializeEv", mfunc_ptr_cast(&CBasePlayerItem::AttemptToMaterialize) },
	{ 0x01DCDA00, "_ZN15CBasePlayerItem8FallInitEv", mfunc_ptr_cast(&CBasePlayerItem::FallInit) },
	{ 0x01DCDC50, "_ZN15CBasePlayerItem12CheckRespawnEv", mfunc_ptr_cast(&CBasePlayerItem::CheckRespawn) },
	//{ 0x0, "_ZN15CBasePlayerItem8pszAmmo1Ev", mfunc_ptr_cast(&CBasePlayerItem::pszAmmo1) },
	//{ 0x0, "_ZN15CBasePlayerItem9iMaxAmmo1Ev", mfunc_ptr_cast(&CBasePlayerItem::iMaxAmmo1) },
	//{ 0x0, "_ZN15CBasePlayerItem8pszAmmo2Ev", mfunc_ptr_cast(&CBasePlayerItem::pszAmmo2) },
	//{ 0x0, "_ZN15CBasePlayerItem9iMaxAmmo2Ev", mfunc_ptr_cast(&CBasePlayerItem::iMaxAmmo2) },
	//{ 0x0, "_ZN15CBasePlayerItem7pszNameEv", mfunc_ptr_cast(&CBasePlayerItem::pszName) },
	//{ 0x0, "_ZN15CBasePlayerItem8iMaxClipEv", mfunc_ptr_cast(&CBasePlayerItem::iMaxClip) },
	//{ 0x0, "_ZN15CBasePlayerItem7iWeightEv", mfunc_ptr_cast(&CBasePlayerItem::iWeight) },
	//{ 0x0, "_ZN15CBasePlayerItem6iFlagsEv", mfunc_ptr_cast(&CBasePlayerItem::iFlags) },
//CBasePlayerWeapon
	//virtual func
	{ 0x01DCD8C0, "_ZN17CBasePlayerWeapon4SaveER5CSave", mfunc_ptr_cast(&CBasePlayerWeapon::Save_) },
	{ 0x01DCD910, "_ZN17CBasePlayerWeapon7RestoreER8CRestore", mfunc_ptr_cast(&CBasePlayerWeapon::Restore_) },
	{ 0x01DCEDE0, "_ZN17CBasePlayerWeapon11AddToPlayerEP11CBasePlayer", mfunc_ptr_cast(&CBasePlayerWeapon::AddToPlayer_) },
	{ 0x01DCEDC0, "_ZN17CBasePlayerWeapon12AddDuplicateEP15CBasePlayerItem", mfunc_ptr_cast(&CBasePlayerWeapon::AddDuplicate_) },
	//{ 0x01D02050, "_ZN17CBasePlayerWeapon9CanDeployEv", mfunc_ptr_cast(&CBasePlayerWeapon::CanDeploy) },
	//{ 0x01D02000, "_ZN17CBasePlayerWeapon8IsWeaponEv", mfunc_ptr_cast(&CBasePlayerWeapon::IsWeapon) },
	{ 0x01DCF570, "_ZN17CBasePlayerWeapon7HolsterEi", mfunc_ptr_cast(&CBasePlayerWeapon::Holster_) },
	//{ 0x0, "_ZN17CBasePlayerWeapon14UpdateItemInfoEv", mfunc_ptr_cast(&CBasePlayerWeapon::UpdateItemInfo) },	// NOXREF
	//{ 0x0, "_ZN17CBasePlayerWeapon13ItemPostFrameEv", mfunc_ptr_cast(&CBasePlayerWeapon::ItemPostFrame) },
	//{ 0x0, "_ZN17CBasePlayerWeapon16PrimaryAmmoIndexEv", mfunc_ptr_cast(&CBasePlayerWeapon::PrimaryAmmoIndex) },
	//{ 0x0, "_ZN17CBasePlayerWeapon18SecondaryAmmoIndexEv", mfunc_ptr_cast(&CBasePlayerWeapon::SecondaryAmmoIndex) },
	{ 0x01DCEEB0, "_ZN17CBasePlayerWeapon16UpdateClientDataEP11CBasePlayer", mfunc_ptr_cast(&CBasePlayerWeapon::UpdateClientData_) },
	//{ 0x0, "_ZN17CBasePlayerWeapon12GetWeaponPtrEv", mfunc_ptr_cast(&CBasePlayerWeapon::GetWeaponPtr) },
	{ 0x01DCF7E0, "_ZN17CBasePlayerWeapon11ExtractAmmoEPS_", mfunc_ptr_cast(&CBasePlayerWeapon::ExtractAmmo_) },
	{ 0x01DCF8A0, "_ZN17CBasePlayerWeapon15ExtractClipAmmoEPS_", mfunc_ptr_cast(&CBasePlayerWeapon::ExtractClipAmmo_) },
	//{ 0x01D02020, "_ZN17CBasePlayerWeapon9AddWeaponEv", mfunc_ptr_cast(&CBasePlayerWeapon::AddWeapon) },
	{ 0x01DCF4C0, "_ZN17CBasePlayerWeapon14PlayEmptySoundEv", mfunc_ptr_cast(&CBasePlayerWeapon::PlayEmptySound_) },
	{ 0x01DCF540, "_ZN17CBasePlayerWeapon15ResetEmptySoundEv", mfunc_ptr_cast(&CBasePlayerWeapon::ResetEmptySound_) },
	{ 0x01DCEFB0, "_ZN17CBasePlayerWeapon14SendWeaponAnimEii", mfunc_ptr_cast(&CBasePlayerWeapon::SendWeaponAnim_) },
	//{ 0x0, "_ZN17CBasePlayerWeapon9IsUseableEv", mfunc_ptr_cast(&CBasePlayerWeapon::IsUseable) },
	//{ 0x0, "_ZN17CBasePlayerWeapon13PrimaryAttackEv", mfunc_ptr_cast(&CBasePlayerWeapon::PrimaryAttack) },
	//{ 0x0, "_ZN17CBasePlayerWeapon15SecondaryAttackEv", mfunc_ptr_cast(&CBasePlayerWeapon::SecondaryAttack) },
	//{ 0x0, "_ZN17CBasePlayerWeapon6ReloadEv", mfunc_ptr_cast(&CBasePlayerWeapon::Reload) },
	//{ 0x0, "_ZN17CBasePlayerWeapon10WeaponIdleEv", mfunc_ptr_cast(&CBasePlayerWeapon::WeaponIdle) },
	//{ 0x01DCF8F0, "_ZN17CBasePlayerWeapon12RetireWeaponEv", mfunc_ptr_cast(&CBasePlayerWeapon::RetireWeapon) },
	//{ 0x0, "_ZN17CBasePlayerWeapon16ShouldWeaponIdleEv", mfunc_ptr_cast(&CBasePlayerWeapon::ShouldWeaponIdle) },
	//{ 0x0, "_ZN17CBasePlayerWeapon12UseDecrementEv", mfunc_ptr_cast(&CBasePlayerWeapon::UseDecrement) },
	//non-virtual func
	{ 0x01DCF030, "_ZN17CBasePlayerWeapon14AddPrimaryAmmoEiPcii", mfunc_ptr_cast(&CBasePlayerWeapon::AddPrimaryAmmo) },
	//{ 0x01DCF0F0, "_ZN17CBasePlayerWeapon16AddSecondaryAmmoEiPci", mfunc_ptr_cast(&CBasePlayerWeapon::AddSecondaryAmmo) },	// NOXREF
	{ 0x01DCF1B0, "_ZN17CBasePlayerWeapon13DefaultDeployEPcS0_iS0_i", mfunc_ptr_cast(&CBasePlayerWeapon::DefaultDeploy) },
	{ 0x01DCF430, "_ZN17CBasePlayerWeapon13DefaultReloadEiif", mfunc_ptr_cast(&CBasePlayerWeapon::DefaultReload) },
	//{ 0x01DCE380, "_ZN17CBasePlayerWeapon13FireRemainingERiRfi", mfunc_ptr_cast(&CBasePlayerWeapon::FireRemaining) },
	//{ 0x0, "_ZN17CBasePlayerWeapon8KickBackEffffffi", mfunc_ptr_cast(&CBasePlayerWeapon::KickBack) },
	//{ 0x0, "_ZN17CBasePlayerWeapon14EjectBrassLateEv", mfunc_ptr_cast(&CBasePlayerWeapon::EjectBrassLate) },
	//{ 0x0, "_ZN17CBasePlayerWeapon8MakeBeamEv", mfunc_ptr_cast(&CBasePlayerWeapon::MakeBeam) },
	//{ 0x0, "_ZN17CBasePlayerWeapon10BeamUpdateEv", mfunc_ptr_cast(&CBasePlayerWeapon::BeamUpdate) },
	{ 0x01DCF2D0, "_ZN17CBasePlayerWeapon11ReloadSoundEv", mfunc_ptr_cast(&CBasePlayerWeapon::ReloadSound) },
	{ 0x01DCF930, "_ZN17CBasePlayerWeapon18GetNextAttackDelayEf", mfunc_ptr_cast(&CBasePlayerWeapon::GetNextAttackDelay) },
	//{ 0x01DCE630, "_ZN17CBasePlayerWeapon18HasSecondaryAttackEv", mfunc_ptr_cast(&CBasePlayerWeapon::HasSecondaryAttack) },	// NOXREF
	//{ 0x0, "_ZN17CBasePlayerWeapon8IsPistolEv", mfunc_ptr_cast(&CBasePlayerWeapon::IsPistol) },
	{ 0x01DCDE10, "_ZN17CBasePlayerWeapon19SetPlayerShieldAnimEv", mfunc_ptr_cast(&CBasePlayerWeapon::SetPlayerShieldAnim) },
	{ 0x01DCDE60, "_ZN17CBasePlayerWeapon21ResetPlayerShieldAnimEv", mfunc_ptr_cast(&CBasePlayerWeapon::ResetPlayerShieldAnim) },
	{ 0x01DCE140, "_ZN17CBasePlayerWeapon19ShieldSecondaryFireEii", mfunc_ptr_cast(&CBasePlayerWeapon::ShieldSecondaryFire) },
//CBasePlayerAmmo
	//virtual func
	{ 0x01DCF5A0, "_ZN15CBasePlayerAmmo5SpawnEv", mfunc_ptr_cast(&CBasePlayerAmmo::Spawn_) },
	//{ 0x0, "_ZN15CBasePlayerAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&CBasePlayerAmmo::AddAmmo_) },
	{ 0x01DCF650, "_ZN15CBasePlayerAmmo7RespawnEv", mfunc_ptr_cast(&CBasePlayerAmmo::Respawn_) },
	//non-virtual func
//CBasePlayerAmmo
	{ 0x01DCF6C0, "_ZN15CBasePlayerAmmo11MaterializeEv", mfunc_ptr_cast(&CBasePlayerAmmo::Materialize) },
	{ 0x01DCF730, "_ZN15CBasePlayerAmmo12DefaultTouchEP11CBaseEntity", mfunc_ptr_cast(&CBasePlayerAmmo::DefaultTouch) },
//C9MMAmmo
	{ 0x01D59550, "_ZN8C9MMAmmo5SpawnEv", mfunc_ptr_cast(&C9MMAmmo::Spawn_) },
	{ 0x01D59580, "_ZN8C9MMAmmo8PrecacheEv", mfunc_ptr_cast(&C9MMAmmo::Precache_) },
	{ 0x01D595A0, "_ZN8C9MMAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C9MMAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D59500, "ammo_9mm", (size_t)&ammo_9mm },
//CBuckShotAmmo
	{ 0x01D59640, "_ZN13CBuckShotAmmo5SpawnEv", mfunc_ptr_cast(&CBuckShotAmmo::Spawn_) },
	{ 0x01D59670, "_ZN13CBuckShotAmmo8PrecacheEv", mfunc_ptr_cast(&CBuckShotAmmo::Precache_) },
	{ 0x01D59690, "_ZN13CBuckShotAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&CBuckShotAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D595F0, "ammo_buckshot", (size_t)&ammo_buckshot },
//C556NatoAmmo
	{ 0x01D59730, "_ZN12C556NatoAmmo5SpawnEv", mfunc_ptr_cast(&C556NatoAmmo::Spawn_) },
	{ 0x01D59760, "_ZN12C556NatoAmmo8PrecacheEv", mfunc_ptr_cast(&C556NatoAmmo::Precache_) },
	{ 0x01D59780, "_ZN12C556NatoAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C556NatoAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D596E0, "ammo_556nato", (size_t)&ammo_556nato },
//C556NatoBoxAmmo
	{ 0x01D59820, "_ZN15C556NatoBoxAmmo5SpawnEv", mfunc_ptr_cast(&C556NatoBoxAmmo::Spawn_) },
	{ 0x01D59850, "_ZN15C556NatoBoxAmmo8PrecacheEv", mfunc_ptr_cast(&C556NatoBoxAmmo::Precache_) },
	{ 0x01D59870, "_ZN15C556NatoBoxAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C556NatoBoxAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D597D0, "ammo_556natobox", (size_t)&ammo_556natobox },
//C762NatoAmmo
	{ 0x01D59920, "_ZN12C762NatoAmmo5SpawnEv", mfunc_ptr_cast(&C762NatoAmmo::Spawn_) },
	{ 0x01D59950, "_ZN12C762NatoAmmo8PrecacheEv", mfunc_ptr_cast(&C762NatoAmmo::Precache_) },
	{ 0x01D59970, "_ZN12C762NatoAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C762NatoAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D598D0, "ammo_762nato", (size_t)&ammo_762nato },
//C45ACPAmmo
	{ 0x01D59A10, "_ZN10C45ACPAmmo5SpawnEv", mfunc_ptr_cast(&C45ACPAmmo::Spawn_) },
	{ 0x01D59A40, "_ZN10C45ACPAmmo8PrecacheEv", mfunc_ptr_cast(&C45ACPAmmo::Precache_) },
	{ 0x01D59A60, "_ZN10C45ACPAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C45ACPAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D599C0, "ammo_45acp", (size_t)&ammo_45acp },
//C50AEAmmo
	{ 0x01D59B00, "_ZN9C50AEAmmo5SpawnEv", mfunc_ptr_cast(&C50AEAmmo::Spawn_) },
	{ 0x01D59B30, "_ZN9C50AEAmmo8PrecacheEv", mfunc_ptr_cast(&C50AEAmmo::Precache_) },
	{ 0x01D59B50, "_ZN9C50AEAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C50AEAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D59AB0, "ammo_50ae", (size_t)&ammo_50ae },
//C338MagnumAmmo
	{ 0x01D59BF0, "_ZN14C338MagnumAmmo5SpawnEv", mfunc_ptr_cast(&C338MagnumAmmo::Spawn_) },
	{ 0x01D59C20, "_ZN14C338MagnumAmmo8PrecacheEv", mfunc_ptr_cast(&C338MagnumAmmo::Precache_) },
	{ 0x01D59C40, "_ZN14C338MagnumAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C338MagnumAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D59BA0, "ammo_338magnum", (size_t)&ammo_338magnum },
//C57MMAmmo
	{ 0x01D59CE0, "_ZN9C57MMAmmo5SpawnEv", mfunc_ptr_cast(&C57MMAmmo::Spawn_) },
	{ 0x01D59D10, "_ZN9C57MMAmmo8PrecacheEv", mfunc_ptr_cast(&C57MMAmmo::Precache_) },
	{ 0x01D59D30, "_ZN9C57MMAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C57MMAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D59C90, "ammo_57mm", (size_t)&ammo_57mm },
//C357SIGAmmo
	{ 0x01D59DD0, "_ZN11C357SIGAmmo5SpawnEv", mfunc_ptr_cast(&C357SIGAmmo::Spawn_) },
	{ 0x01D59E00, "_ZN11C357SIGAmmo8PrecacheEv", mfunc_ptr_cast(&C357SIGAmmo::Precache_) },
	{ 0x01D59E20, "_ZN11C357SIGAmmo7AddAmmoEP11CBaseEntity", mfunc_ptr_cast(&C357SIGAmmo::AddAmmo_) },
	//non-virtual func
	{ 0x01D59D80, "ammo_357sig", (size_t)&ammo_357sig },
//CWeaponBox
	//virtual func
	//{ 0x01DCFD80, "_ZN10CWeaponBox5SpawnEv", mfunc_ptr_cast(&CWeaponBox::Spawn_) },
	//{ 0x01DCFA40, "_ZN10CWeaponBox8PrecacheEv", mfunc_ptr_cast(&CWeaponBox::Precache_) },
	//{ 0x01DCFA50, "_ZN10CWeaponBox8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CWeaponBox::KeyValue_) },
	//{ 0x01DCF9E0, "_ZN10CWeaponBox4SaveER5CSave", mfunc_ptr_cast(&CWeaponBox::Save_) },
	//{ 0x01DCFA10, "_ZN10CWeaponBox7RestoreER8CRestore", mfunc_ptr_cast(&CWeaponBox::Restore_) },
	//{ 0x01DD0970, "_ZN10CWeaponBox21SetObjectCollisionBoxEv", mfunc_ptr_cast(&CWeaponBox::SetObjectCollisionBox_) },
	//{ 0x01DCFE30, "_ZN10CWeaponBox5TouchEP11CBaseEntity", mfunc_ptr_cast(&CWeaponBox::Touch_) },
	//non-virtual func
	//{ 0x01DCF990, "weaponbox", (size_t)&weaponbox },
	//{ 0x01DD0930, "_ZN10CWeaponBox7IsEmptyEv", mfunc_ptr_cast(&CWeaponBox::IsEmpty) },	// NOXREF
	{ 0x01DD07C0, "_ZN10CWeaponBox8GiveAmmoEiPciPi", mfunc_ptr_cast(&CWeaponBox::GiveAmmo) },
	{ 0x01DCFDE0, "_ZN10CWeaponBox4KillEv", mfunc_ptr_cast(&CWeaponBox::Kill) },
	{ 0x01DCFBF0, "_ZN10CWeaponBox9BombThinkEv", mfunc_ptr_cast(&CWeaponBox::BombThink) }, //export func
	//{ 0x01DD08A0, "_ZN10CWeaponBox9HasWeaponEP15CBasePlayerItem", mfunc_ptr_cast(&CWeaponBox::HasWeapon) },	// NOXREF
	{ 0x01DD0500, "_ZN10CWeaponBox10PackWeaponEP15CBasePlayerItem", mfunc_ptr_cast(&CWeaponBox::PackWeapon) },
	{ 0x01DD0670, "_ZN10CWeaponBox8PackAmmoEii", mfunc_ptr_cast(&CWeaponBox::PackAmmo) },
//CUSP
	//virtual func
	//!@{ 0x01D0F8B0, "_ZN4CUSP5SpawnEv", mfunc_ptr_cast(&CUSP::Spawn_) },
	{ 0x01D0F910, "_ZN4CUSP8PrecacheEv", mfunc_ptr_cast(&CUSP::Precache_) },
	//!@{ 0x01D0F9D0, "_ZN4CUSP11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CUSP::GetItemInfo_) },
	//!@{ 0x01D0FA40, "_ZN4CUSP6DeployEv", mfunc_ptr_cast(&CUSP::Deploy_) },
	//{ 0x0, "_ZN4CUSP11GetMaxSpeedEv", mfunc_ptr_cast(&CUSP::GetMaxSpeed) },
	//{ 0x0, "_ZN4CUSP9iItemSlotEv", mfunc_ptr_cast(&CUSP::iItemSlot) },
	//{ 0x0, "_ZN4CUSP13PrimaryAttackEv", mfunc_ptr_cast(&CUSP::PrimaryAttack) },
	//{ 0x0, "_ZN4CUSP15SecondaryAttackEv", mfunc_ptr_cast(&CUSP::SecondaryAttack) },
	//!@{ 0x01D10060, "_ZN4CUSP6ReloadEv", mfunc_ptr_cast(&CUSP::Reload_) },
	//!@{ 0x01D100C0, "_ZN4CUSP10WeaponIdleEv", mfunc_ptr_cast(&CUSP::WeaponIdle_) },
	//{ 0x0, "_ZN4CUSP12UseDecrementEv", mfunc_ptr_cast(&CUSP::UseDecrement) },
	//{ 0x0, "_ZN4CUSP8IsPistolEv", mfunc_ptr_cast(&CUSP::IsPistol) },
	//non-virtual func
	{ 0x01D0F860, "weapon_usp", (size_t)&weapon_usp },
	//@{ 0x01D0FD50, "_ZN4CUSP7USPFireEffi", mfunc_ptr_cast(&CUSP::USPFire) },	// UNTESTED TODO: Reverse ME
	////{ 0x0, "_ZN4CUSP8MakeBeamEv", mfunc_ptr_cast(&CUSP::MakeBeam) },	// NOXREF
	////{ 0x0, "_ZN4CUSP10BeamUpdateEv", mfunc_ptr_cast(&CUSP::BeamUpdate) },	// NOXREF
//CMP5N
	//virtual func
	//{ 0x0, "_ZN5CMP5N5SpawnEv", mfunc_ptr_cast(&CMP5N::Spawn) },
	//{ 0x0, "_ZN5CMP5N8PrecacheEv", mfunc_ptr_cast(&CMP5N::Precache) },
	//{ 0x0, "_ZN5CMP5N11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CMP5N::GetItemInfo) },
	//{ 0x0, "_ZN5CMP5N6DeployEv", mfunc_ptr_cast(&CMP5N::Deploy) },
	//{ 0x0, "_ZN5CMP5N11GetMaxSpeedEv", mfunc_ptr_cast(&CMP5N::GetMaxSpeed) },
	//{ 0x0, "_ZN5CMP5N9iItemSlotEv", mfunc_ptr_cast(&CMP5N::iItemSlot) },
	//{ 0x0, "_ZN5CMP5N13PrimaryAttackEv", mfunc_ptr_cast(&CMP5N::PrimaryAttack) },
	//{ 0x0, "_ZN5CMP5N6ReloadEv", mfunc_ptr_cast(&CMP5N::Reload) },
	//{ 0x0, "_ZN5CMP5N10WeaponIdleEv", mfunc_ptr_cast(&CMP5N::WeaponIdle) },
	//{ 0x0, "_ZN5CMP5N12UseDecrementEv", mfunc_ptr_cast(&CMP5N::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_mp5navy", (size_t)&weapon_mp5navy },
	//{ 0x0, "_ZN5CMP5N8MP5NFireEffi", mfunc_ptr_cast(&CMP5N::USPFire) },
//CSG552
	//virtual func
	//{ 0x0, "_ZN6CSG5525SpawnEv", mfunc_ptr_cast(&CSG552::Spawn) },
	//{ 0x0, "_ZN6CSG5528PrecacheEv", mfunc_ptr_cast(&CSG552::Precache) },
	//{ 0x0, "_ZN6CSG55211GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CSG552::GetItemInfo) },
	//{ 0x0, "_ZN6CSG5526DeployEv", mfunc_ptr_cast(&CSG552::Deploy) },
	//{ 0x0, "_ZN6CSG55211GetMaxSpeedEv", mfunc_ptr_cast(&CSG552::GetMaxSpeed) },
	//{ 0x0, "_ZN6CSG5529iItemSlotEv", mfunc_ptr_cast(&CSG552::iItemSlot) },
	//{ 0x0, "_ZN6CSG55213PrimaryAttackEv", mfunc_ptr_cast(&CSG552::PrimaryAttack) },
	//{ 0x0, "_ZN6CSG55215SecondaryAttackEv", mfunc_ptr_cast(&CSG552::SecondaryAttack) },
	//{ 0x0, "_ZN6CSG5526ReloadEv", mfunc_ptr_cast(&CSG552::Reload) },
	//{ 0x0, "_ZN6CSG55210WeaponIdleEv", mfunc_ptr_cast(&CSG552::WeaponIdle) },
	//{ 0x0, "_ZN6CSG55212UseDecrementEv", mfunc_ptr_cast(&CSG552::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_sg552", (size_t)&weapon_sg552 },
	//{ 0x0, "_ZN6CSG5529SG552FireEffi", mfunc_ptr_cast(&CSG552::SG552Fire) },
//CAK47
	//virtual func
	//{ 0x0, "_ZN5CAK475SpawnEv", mfunc_ptr_cast(&CAK47::Spawn) },
	//{ 0x0, "_ZN5CAK478PrecacheEv", mfunc_ptr_cast(&CAK47::Precache) },
	//{ 0x0, "_ZN5CAK4711GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CAK47::GetItemInfo) },
	//{ 0x0, "_ZN5CAK476DeployEv", mfunc_ptr_cast(&CAK47::Deploy) },
	//{ 0x01D02080, "_ZN5CAK4711GetMaxSpeedEv", mfunc_ptr_cast(&CAK47::GetMaxSpeed) },
	//{ 0x0, "_ZN5CAK479iItemSlotEv", mfunc_ptr_cast(&CAK47::iItemSlot) },
	//{ 0x0, "_ZN5CAK4713PrimaryAttackEv", mfunc_ptr_cast(&CAK47::PrimaryAttack) },
	//{ 0x0, "_ZN5CAK4715SecondaryAttackEv", mfunc_ptr_cast(&CAK47::SecondaryAttack) },
	//{ 0x0, "_ZN5CAK476ReloadEv", mfunc_ptr_cast(&CAK47::Reload) },
	//{ 0x0, "_ZN5CAK4710WeaponIdleEv", mfunc_ptr_cast(&CAK47::WeaponIdle) },
	//{ 0x0, "_ZN5CAK4712UseDecrementEv", mfunc_ptr_cast(&CAK47::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_ak47", (size_t)&weapon_ak47 },
	//{ 0x0, "_ZN5CAK478AK47FireEffi", mfunc_ptr_cast(&CAK47::USPFire) },
//CAUG
	//virtual func
	//{ 0x0, "_ZN4CAUG5SpawnEv", mfunc_ptr_cast(&CAUG::Spawn) },
	//{ 0x0, "_ZN4CAUG8PrecacheEv", mfunc_ptr_cast(&CAUG::Precache) },
	//{ 0x0, "_ZN4CAUG11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CAUG::GetItemInfo) },
	//{ 0x0, "_ZN4CAUG6DeployEv", mfunc_ptr_cast(&CAUG::Deploy) },
	//{ 0x0, "_ZN4CAUG11GetMaxSpeedEv", mfunc_ptr_cast(&CAUG::GetMaxSpeed) },
	//{ 0x0, "_ZN4CAUG9iItemSlotEv", mfunc_ptr_cast(&CAUG::iItemSlot) },
	//{ 0x0, "_ZN4CAUG13PrimaryAttackEv", mfunc_ptr_cast(&CAUG::PrimaryAttack) },
	//{ 0x0, "_ZN4CAUG15SecondaryAttackEv", mfunc_ptr_cast(&CAUG::SecondaryAttack) },
	//{ 0x0, "_ZN4CAUG6ReloadEv", mfunc_ptr_cast(&CAUG::Reload) },
	//{ 0x0, "_ZN4CAUG10WeaponIdleEv", mfunc_ptr_cast(&CAUG::WeaponIdle) },
	//{ 0x0, "_ZN4CAUG12UseDecrementEv", mfunc_ptr_cast(&CAUG::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_aug", (size_t)&weapon_aug },
	//{ 0x0, "_ZN4CAUG7AUGFireEffi", mfunc_ptr_cast(&CAUG::AUGFire) },
//CAWP
	//virtual func
	//{ 0x0, "_ZN4CAWP5SpawnEv", mfunc_ptr_cast(&CAWP::Spawn) },
	//{ 0x0, "_ZN4CAWP8PrecacheEv", mfunc_ptr_cast(&CAWP::Precache) },
	//{ 0x0, "_ZN4CAWP11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CAWP::GetItemInfo) },
	//{ 0x0, "_ZN4CAWP6DeployEv", mfunc_ptr_cast(&CAWP::Deploy) },
	//{ 0x0, "_ZN4CAWP11GetMaxSpeedEv", mfunc_ptr_cast(&CAWP::GetMaxSpeed) },
	//{ 0x0, "_ZN4CAWP9iItemSlotEv", mfunc_ptr_cast(&CAWP::iItemSlot) },
	//{ 0x0, "_ZN4CAWP13PrimaryAttackEv", mfunc_ptr_cast(&CAWP::PrimaryAttack) },
	//{ 0x0, "_ZN4CAWP15SecondaryAttackEv", mfunc_ptr_cast(&CAWP::SecondaryAttack) },
	//{ 0x0, "_ZN4CAWP6ReloadEv", mfunc_ptr_cast(&CAWP::Reload) },
	//{ 0x0, "_ZN4CAWP10WeaponIdleEv", mfunc_ptr_cast(&CAWP::WeaponIdle) },
	//{ 0x0, "_ZN4CAWP12UseDecrementEv", mfunc_ptr_cast(&CAWP::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_awp", (size_t)&weapon_awp },
	//{ 0x0, "_ZN4CAWP7AWPFireEffi", mfunc_ptr_cast(&CAWP::AWPFire) },
//CC4
	//virtual func
	//{ 0x0, "_ZN3CC45SpawnEv", mfunc_ptr_cast(&CC4::Spawn) },
	//{ 0x0, "_ZN3CC48PrecacheEv", mfunc_ptr_cast(&CC4::Precache) },
	//{ 0x0, "_ZN3CC48KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CC4::KeyValue) },
	//{ 0x0, "_ZN3CC43UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CC4::Use) },
	//{ 0x0, "_ZN3CC411GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CC4::GetItemInfo) },
	//{ 0x0, "_ZN3CC46DeployEv", mfunc_ptr_cast(&CC4::Deploy) },
	//{ 0x0, "_ZN3CC47HolsterEi", mfunc_ptr_cast(&CC4::Holster) },
	//{ 0x0, "_ZN3CC411GetMaxSpeedEv", mfunc_ptr_cast(&CC4::GetMaxSpeed) },
	//{ 0x0, "_ZN3CC49iItemSlotEv", mfunc_ptr_cast(&CC4::iItemSlot) },
	//{ 0x0, "_ZN3CC413PrimaryAttackEv", mfunc_ptr_cast(&CC4::PrimaryAttack) },
	//{ 0x0, "_ZN3CC410WeaponIdleEv", mfunc_ptr_cast(&CC4::WeaponIdle) },
	//{ 0x0, "_ZN3CC412UseDecrementEv", mfunc_ptr_cast(&CC4::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_c4", (size_t)&weapon_c4 },
//CDEAGLE
	//virtual func
	//{ 0x0, "_ZN7CDEAGLE5SpawnEv", mfunc_ptr_cast(&CDEAGLE::Spawn) },
	//{ 0x0, "_ZN7CDEAGLE8PrecacheEv", mfunc_ptr_cast(&CDEAGLE::Precache) },
	//{ 0x0, "_ZN7CDEAGLE11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CDEAGLE::GetItemInfo) },
	//{ 0x0, "_ZN7CDEAGLE6DeployEv", mfunc_ptr_cast(&CDEAGLE::Deploy) },
	//{ 0x0, "_ZN7CDEAGLE11GetMaxSpeedEv", mfunc_ptr_cast(&CDEAGLE::GetMaxSpeed) },
	//{ 0x0, "_ZN7CDEAGLE9iItemSlotEv", mfunc_ptr_cast(&CDEAGLE::iItemSlot) },
	//{ 0x0, "_ZN7CDEAGLE13PrimaryAttackEv", mfunc_ptr_cast(&CDEAGLE::PrimaryAttack) },
	//{ 0x0, "_ZN7CDEAGLE15SecondaryAttackEv", mfunc_ptr_cast(&CDEAGLE::SecondaryAttack) },
	//{ 0x0, "_ZN7CDEAGLE6ReloadEv", mfunc_ptr_cast(&CDEAGLE::Reload) },
	//{ 0x0, "_ZN7CDEAGLE10WeaponIdleEv", mfunc_ptr_cast(&CDEAGLE::WeaponIdle) },
	//{ 0x0, "_ZN7CDEAGLE12UseDecrementEv", mfunc_ptr_cast(&CDEAGLE::UseDecrement) },
	//{ 0x0, "_ZN7CDEAGLE8IsPistolEv", mfunc_ptr_cast(&CDEAGLE::IsPistol) },
	//non-virtual func
	//{ 0x0, "weapon_deagle", (size_t)&weapon_deagle },
	//{ 0x0, "_ZN7CDEAGLE10DEAGLEFireEffi", mfunc_ptr_cast(&CDEAGLE::DEAGLEFire) },
//CFlashbang
	//virtual func
	//{ 0x0, "_ZN10CFlashbang5SpawnEv", mfunc_ptr_cast(&CFlashbang::Spawn) },
	//{ 0x0, "_ZN10CFlashbang8PrecacheEv", mfunc_ptr_cast(&CFlashbang::Precache) },
	//{ 0x0, "_ZN10CFlashbang11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CFlashbang::GetItemInfo) },
	//{ 0x0, "_ZN10CFlashbang9CanDeployEv", mfunc_ptr_cast(&CFlashbang::CanDeploy) },
	//{ 0x0, "_ZN10CFlashbang7CanDropEv", mfunc_ptr_cast(&CFlashbang::CanDrop) },
	//{ 0x0, "_ZN10CFlashbang6DeployEv", mfunc_ptr_cast(&CFlashbang::Deploy) },
	//{ 0x0, "_ZN10CFlashbang7HolsterEi", mfunc_ptr_cast(&CFlashbang::Holster) },
	//{ 0x0, "_ZN10CFlashbang11GetMaxSpeedEv", mfunc_ptr_cast(&CFlashbang::GetMaxSpeed) },
	//{ 0x0, "_ZN10CFlashbang9iItemSlotEv", mfunc_ptr_cast(&CFlashbang::iItemSlot) },
	//{ 0x0, "_ZN10CFlashbang13PrimaryAttackEv", mfunc_ptr_cast(&CFlashbang::PrimaryAttack) },
	//{ 0x0, "_ZN10CFlashbang15SecondaryAttackEv", mfunc_ptr_cast(&CFlashbang::SecondaryAttack) },
	//{ 0x0, "_ZN10CFlashbang10WeaponIdleEv", mfunc_ptr_cast(&CFlashbang::WeaponIdle) },
	//{ 0x0, "_ZN10CFlashbang12UseDecrementEv", mfunc_ptr_cast(&CFlashbang::UseDecrement) },
	//{ 0x0, "_ZN10CFlashbang8IsPistolEv", mfunc_ptr_cast(&CFlashbang::IsPistol) },
	//non-virtual func
	//{ 0x0, "weapon_flashbang", (size_t)&weapon_flashbang },
	//{ 0x0, "_ZN10CFlashbang19ShieldSecondaryFireEii", mfunc_ptr_cast(&CFlashbang::ShieldSecondaryFire) },
	//{ 0x0, "_ZN10CFlashbang19SetPlayerShieldAnimEv", mfunc_ptr_cast(&CFlashbang::SetPlayerShieldAnim) },
	//{ 0x0, "_ZN10CFlashbang21ResetPlayerShieldAnimEv", mfunc_ptr_cast(&CFlashbang::ResetPlayerShieldAnim) },
//CG3SG1
	//virtual func
	//{ 0x0, "_ZN6CG3SG15SpawnEv", mfunc_ptr_cast(&CG3SG1::Spawn) },
	//{ 0x0, "_ZN6CG3SG18PrecacheEv", mfunc_ptr_cast(&CG3SG1::Precache) },
	//{ 0x0, "_ZN6CG3SG111GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CG3SG1::GetItemInfo) },
	//{ 0x0, "_ZN6CG3SG16DeployEv", mfunc_ptr_cast(&CG3SG1::Deploy) },
	//{ 0x0, "_ZN6CG3SG111GetMaxSpeedEv", mfunc_ptr_cast(&CG3SG1::GetMaxSpeed) },
	//{ 0x0, "_ZN6CG3SG19iItemSlotEv", mfunc_ptr_cast(&CG3SG1::iItemSlot) },
	//{ 0x0, "_ZN6CG3SG113PrimaryAttackEv", mfunc_ptr_cast(&CG3SG1::PrimaryAttack) },
	//{ 0x0, "_ZN6CG3SG115SecondaryAttackEv", mfunc_ptr_cast(&CG3SG1::SecondaryAttack) },
	//{ 0x0, "_ZN6CG3SG16ReloadEv", mfunc_ptr_cast(&CG3SG1::Reload) },
	//{ 0x0, "_ZN6CG3SG110WeaponIdleEv", mfunc_ptr_cast(&CG3SG1::WeaponIdle) },
	//{ 0x0, "_ZN6CG3SG112UseDecrementEv", mfunc_ptr_cast(&CG3SG1::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_g3sg1", (size_t)&weapon_g3sg1 },
	//{ 0x0, "_ZN6CG3SG19G3SG1FireEffi", mfunc_ptr_cast(&CG3SG1::G3SG1Fire) },
//CGLOCK18
	//virtual func
	//{ 0x0, "_ZN8CGLOCK185SpawnEv", mfunc_ptr_cast(&CGLOCK18::Spawn) },
	//{ 0x0, "_ZN8CGLOCK188PrecacheEv", mfunc_ptr_cast(&CGLOCK18::Precache) },
	//{ 0x0, "_ZN8CGLOCK1811GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CGLOCK18::GetItemInfo) },
	//{ 0x0, "_ZN8CGLOCK186DeployEv", mfunc_ptr_cast(&CGLOCK18::Deploy) },
	//{ 0x0, "_ZN8CGLOCK1811GetMaxSpeedEv", mfunc_ptr_cast(&CGLOCK18::GetMaxSpeed) },
	//{ 0x0, "_ZN8CGLOCK189iItemSlotEv", mfunc_ptr_cast(&CGLOCK18::iItemSlot) },
	//{ 0x0, "_ZN8CGLOCK1813PrimaryAttackEv", mfunc_ptr_cast(&CGLOCK18::PrimaryAttack) },
	//{ 0x0, "_ZN8CGLOCK1815SecondaryAttackEv", mfunc_ptr_cast(&CGLOCK18::SecondaryAttack) },
	//{ 0x0, "_ZN8CGLOCK186ReloadEv", mfunc_ptr_cast(&CGLOCK18::Reload) },
	//{ 0x0, "_ZN8CGLOCK1810WeaponIdleEv", mfunc_ptr_cast(&CGLOCK18::WeaponIdle) },
	//{ 0x0, "_ZN8CGLOCK1812UseDecrementEv", mfunc_ptr_cast(&CGLOCK18::UseDecrement) },
	//{ 0x0, "_ZN8CGLOCK188IsPistolEv", mfunc_ptr_cast(&CGLOCK18::IsPistol) },
	//non-virtual func
	//{ 0x0, "weapon_glock18", (size_t)&weapon_glock18 },
	//{ 0x0, "_ZN6CG3SG19G3SG1FireEffi", mfunc_ptr_cast(&CG3SG1::GLOCK18Fire) },
//CHEGrenade
	//virtual func
	//{ 0x0, "_ZN10CHEGrenade5SpawnEv", mfunc_ptr_cast(&CHEGrenade::Spawn) },
	//{ 0x0, "_ZN10CHEGrenade8PrecacheEv", mfunc_ptr_cast(&CHEGrenade::Precache) },
	//{ 0x0, "_ZN10CHEGrenade11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CHEGrenade::GetItemInfo) },
	//{ 0x0, "_ZN10CHEGrenade9CanDeployEv", mfunc_ptr_cast(&CHEGrenade::CanDeploy) },
	//{ 0x0, "_ZN10CHEGrenade7CanDropEv", mfunc_ptr_cast(&CHEGrenade::CanDrop) },
	//{ 0x0, "_ZN10CHEGrenade6DeployEv", mfunc_ptr_cast(&CHEGrenade::Deploy) },
	//{ 0x0, "_ZN10CHEGrenade7HolsterEi", mfunc_ptr_cast(&CHEGrenade::Holster) },
	//{ 0x0, "_ZN10CHEGrenade11GetMaxSpeedEv", mfunc_ptr_cast(&CHEGrenade::GetMaxSpeed) },
	//{ 0x0, "_ZN10CHEGrenade9iItemSlotEv", mfunc_ptr_cast(&CHEGrenade::iItemSlot) },
	//{ 0x0, "_ZN10CHEGrenade13PrimaryAttackEv", mfunc_ptr_cast(&CHEGrenade::PrimaryAttack) },
	//{ 0x0, "_ZN10CHEGrenade15SecondaryAttackEv", mfunc_ptr_cast(&CHEGrenade::SecondaryAttack) },
	//{ 0x0, "_ZN10CHEGrenade10WeaponIdleEv", mfunc_ptr_cast(&CHEGrenade::WeaponIdle) },
	//{ 0x0, "_ZN10CHEGrenade12UseDecrementEv", mfunc_ptr_cast(&CHEGrenade::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_hegrenade", (size_t)&weapon_hegrenade },
	//{ 0x0, "_ZN10CHEGrenade19ShieldSecondaryFireEii", mfunc_ptr_cast(&CHEGrenade::ShieldSecondaryFire) },
	//{ 0x0, "_ZN10CHEGrenade19SetPlayerShieldAnimEv", mfunc_ptr_cast(&CHEGrenade::SetPlayerShieldAnim) },
	//{ 0x0, "_ZN10CHEGrenade21ResetPlayerShieldAnimEv", mfunc_ptr_cast(&CHEGrenade::ResetPlayerShieldAnim) },
//CKnife
	//virtual func
	//{ 0x0, "_ZN6CKnife5SpawnEv", mfunc_ptr_cast(&CKnife::Spawn) },
	//{ 0x0, "_ZN6CKnife8PrecacheEv", mfunc_ptr_cast(&CKnife::Precache) },
	//{ 0x0, "_ZN6CKnife11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CKnife::GetItemInfo) },
	//{ 0x0, "_ZN6CKnife7CanDropEv", mfunc_ptr_cast(&CKnife::CanDrop) },
	//{ 0x0, "_ZN6CKnife6DeployEv", mfunc_ptr_cast(&CKnife::Deploy) },
	//{ 0x0, "_ZN6CKnife7HolsterEi", mfunc_ptr_cast(&CKnife::Holster) },
	//{ 0x0, "_ZN6CKnife11GetMaxSpeedEv", mfunc_ptr_cast(&CKnife::GetMaxSpeed) },
	//{ 0x0, "_ZN6CKnife9iItemSlotEv", mfunc_ptr_cast(&CKnife::iItemSlot) },
	//{ 0x0, "_ZN6CKnife13PrimaryAttackEv", mfunc_ptr_cast(&CKnife::PrimaryAttack) },
	//{ 0x0, "_ZN6CKnife15SecondaryAttackEv", mfunc_ptr_cast(&CKnife::SecondaryAttack) },
	//{ 0x0, "_ZN6CKnife12UseDecrementEv", mfunc_ptr_cast(&CKnife::UseDecrement) },
	//{ 0x0, "_ZN6CKnife10WeaponIdleEv", mfunc_ptr_cast(&CKnife::WeaponIdle) },
	//non-virtual func
	//{ 0x0, "weapon_knife", (size_t)&weapon_knife },
	//{ 0x0, "FindHullIntersection", (size_t)&FindHullIntersection },
	//{ 0x0, "_ZN6CKnife10SwingAgainEv", mfunc_ptr_cast(&CKnife::SwingAgain) },
	//{ 0x0, "_ZN6CKnife5SmackEv", mfunc_ptr_cast(&CKnife::Smack) },
	//{ 0x0, "_ZN6CKnife15WeaponAnimationEi", mfunc_ptr_cast(&CKnife::WeaponAnimation) },
	//{ 0x0, "_ZN6CKnife4StabEi", mfunc_ptr_cast(&CKnife::Stab) },
	//{ 0x0, "_ZN6CKnife5SwingEi", mfunc_ptr_cast(&CKnife::Swing) },
	//{ 0x0, "_ZN6CKnife19ShieldSecondaryFireEii", mfunc_ptr_cast(&CKnife::ShieldSecondaryFire) },
	//{ 0x0, "_ZN6CKnife19SetPlayerShieldAnimEv", mfunc_ptr_cast(&CKnife::SetPlayerShieldAnim) },
	//{ 0x0, "_ZN6CKnife21ResetPlayerShieldAnimEv", mfunc_ptr_cast(&CKnife::ResetPlayerShieldAnim) },
//CM249
	//virtual func
	//{ 0x0, "_ZN5CM2495SpawnEv", mfunc_ptr_cast(&CM249::Spawn) },
	//{ 0x0, "_ZN5CM2498PrecacheEv", mfunc_ptr_cast(&CM249::Precache) },
	//{ 0x0, "_ZN5CM24911GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CM249::GetItemInfo) },
	//{ 0x0, "_ZN5CM2496DeployEv", mfunc_ptr_cast(&CM249::Deploy) },
	//{ 0x0, "_ZN5CM24911GetMaxSpeedEv", mfunc_ptr_cast(&CM249::GetMaxSpeed) },
	//{ 0x0, "_ZN5CM2499iItemSlotEv", mfunc_ptr_cast(&CM249::iItemSlot) },
	//{ 0x0, "_ZN5CM24913PrimaryAttackEv", mfunc_ptr_cast(&CM249::PrimaryAttack) },
	//{ 0x0, "_ZN5CM2496ReloadEv", mfunc_ptr_cast(&CM249::Reload) },
	//{ 0x0, "_ZN5CM24910WeaponIdleEv", mfunc_ptr_cast(&CM249::WeaponIdle) },
	//{ 0x0, "_ZN5CM24912UseDecrementEv", mfunc_ptr_cast(&CM249::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_m249", (size_t)&weapon_m249 },
	//{ 0x0, "_ZN5CM2498M249FireEffi", mfunc_ptr_cast(&CM249::M249Fire) },
//CM3
	//virtual func
	//{ 0x0, "_ZN3CM35SpawnEv", mfunc_ptr_cast(&CM3::Spawn) },
	//{ 0x0, "_ZN3CM38PrecacheEv", mfunc_ptr_cast(&CM3::Precache) },
	//{ 0x0, "_ZN3CM311GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CM3::GetItemInfo) },
	//{ 0x0, "_ZN3CM36DeployEv", mfunc_ptr_cast(&CM3::Deploy) },
	//{ 0x0, "_ZN3CM311GetMaxSpeedEv", mfunc_ptr_cast(&CM3::GetMaxSpeed) },
	//{ 0x0, "_ZN3CM39iItemSlotEv", mfunc_ptr_cast(&CM3::iItemSlot) },
	//{ 0x01D0A1E0, "_ZN3CM313PrimaryAttackEv", mfunc_ptr_cast(&CM3::PrimaryAttack) },
	//{ 0x0, "_ZN3CM36ReloadEv", mfunc_ptr_cast(&CM3::Reload) },
	//{ 0x0, "_ZN3CM310WeaponIdleEv", mfunc_ptr_cast(&CM3::WeaponIdle) },
	//{ 0x0, "_ZN3CM312UseDecrementEv", mfunc_ptr_cast(&CM3::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_m3", (size_t)&weapon_m3 },
//CM4A1
	//virtual func
	//{ 0x0, "_ZN5CM4A15SpawnEv", mfunc_ptr_cast(&CM4A1::Spawn) },
	//{ 0x0, "_ZN5CM4A18PrecacheEv", mfunc_ptr_cast(&CM4A1::Precache) },
	//{ 0x0, "_ZN5CM4A111GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CM4A1::GetItemInfo) },
	//{ 0x0, "_ZN5CM4A16DeployEv", mfunc_ptr_cast(&CM4A1::Deploy) },
	//{ 0x0, "_ZN5CM4A111GetMaxSpeedEv", mfunc_ptr_cast(&CM4A1::GetMaxSpeed) },
	//{ 0x0, "_ZN5CM4A19iItemSlotEv", mfunc_ptr_cast(&CM4A1::iItemSlot) },
	//{ 0x0, "_ZN5CM4A113PrimaryAttackEv", mfunc_ptr_cast(&CM4A1::PrimaryAttack) },
	//{ 0x0, "_ZN5CM4A115SecondaryAttackEv", mfunc_ptr_cast(&CM4A1::SecondaryAttack) },
	//{ 0x0, "_ZN5CM4A16ReloadEv", mfunc_ptr_cast(&CM4A1::Reload) },
	//{ 0x0, "_ZN5CM4A110WeaponIdleEv", mfunc_ptr_cast(&CM4A1::WeaponIdle) },
	//{ 0x0, "_ZN5CM4A112UseDecrementEv", mfunc_ptr_cast(&CM4A1::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_m4a1", (size_t)&weapon_m4a1 },
	//{ 0x0, "_ZN5CM4A18M4A1FireEffi", mfunc_ptr_cast(&CM4A1::M4A1Fire) },
//CMAC10
	//virtual func
	//{ 0x0, "_ZN6CMAC105SpawnEv", mfunc_ptr_cast(&CMAC10::Spawn) },
	//{ 0x0, "_ZN6CMAC108PrecacheEv", mfunc_ptr_cast(&CMAC10::Precache) },
	//{ 0x0, "_ZN6CMAC1011GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CMAC10::GetItemInfo) },
	//{ 0x0, "_ZN6CMAC106DeployEv", mfunc_ptr_cast(&CMAC10::Deploy) },
	//{ 0x0, "_ZN6CMAC1011GetMaxSpeedEv", mfunc_ptr_cast(&CMAC10::GetMaxSpeed) },
	//{ 0x0, "_ZN6CMAC109iItemSlotEv", mfunc_ptr_cast(&CMAC10::iItemSlot) },
	//{ 0x0, "_ZN6CMAC1013PrimaryAttackEv", mfunc_ptr_cast(&CMAC10::PrimaryAttack) },
	//{ 0x0, "_ZN6CMAC106ReloadEv", mfunc_ptr_cast(&CMAC10::Reload) },
	//{ 0x0, "_ZN6CMAC1010WeaponIdleEv", mfunc_ptr_cast(&CMAC10::WeaponIdle) },
	//{ 0x0, "_ZN6CMAC1012UseDecrementEv", mfunc_ptr_cast(&CMAC10::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_mac10", (size_t)&weapon_mac10 },
	//{ 0x0, "_ZN6CMAC109MAC10FireEffi", mfunc_ptr_cast(&CMAC10::CMAC10Fire) },
//CP228
	//virtual func
	//{ 0x0, "_ZN5CP2285SpawnEv", mfunc_ptr_cast(&CP228::Spawn) },
	//{ 0x0, "_ZN5CP2288PrecacheEv", mfunc_ptr_cast(&CP228::Precache) },
	//{ 0x0, "_ZN5CP22811GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CP228::GetItemInfo) },
	//{ 0x0, "_ZN5CP2286DeployEv", mfunc_ptr_cast(&CP228::Deploy) },
	//{ 0x0, "_ZN5CP22811GetMaxSpeedEv", mfunc_ptr_cast(&CP228::GetMaxSpeed) },
	//{ 0x0, "_ZN5CP2289iItemSlotEv", mfunc_ptr_cast(&CP228::iItemSlot) },
	//{ 0x0, "_ZN5CP22813PrimaryAttackEv", mfunc_ptr_cast(&CP228::PrimaryAttack) },
	//{ 0x0, "_ZN5CP22815SecondaryAttackEv", mfunc_ptr_cast(&CP228::SecondaryAttack) },
	//{ 0x0, "_ZN5CP2286ReloadEv", mfunc_ptr_cast(&CP228::Reload) },
	//{ 0x0, "_ZN5CP22810WeaponIdleEv", mfunc_ptr_cast(&CP228::WeaponIdle) },
	//{ 0x0, "_ZN5CP22812UseDecrementEv", mfunc_ptr_cast(&CP228::UseDecrement) },
	//{ 0x0, "_ZN5CP2288IsPistolEv", mfunc_ptr_cast(&CP228::IsPistol) },
	//non-virtual func
	//{ 0x0, "weapon_p228", (size_t)&weapon_p228 },
	//{ 0x0, "_ZN5CP2288P228FireEffi", mfunc_ptr_cast(&CP228::P228Fire) },
	////{ 0x0, "_ZN5CP2288MakeBeamEv", mfunc_ptr_cast(&CP228::MakeBeam) },			// NOXREF
	////{ 0x0, "_ZN5CP22810BeamUpdateEv", mfunc_ptr_cast(&CP228::BeamUpdate) },		// NOXREF
//CP90
	//virtual func
	//{ 0x0, "_ZN4CP905SpawnEv", mfunc_ptr_cast(&CP90::Spawn) },
	//{ 0x0, "_ZN4CP908PrecacheEv", mfunc_ptr_cast(&CP90::Precache) },
	//{ 0x0, "_ZN4CP9011GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CP90::GetItemInfo) },
	//{ 0x0, "_ZN4CP906DeployEv", mfunc_ptr_cast(&CP90::Deploy) },
	//{ 0x0, "_ZN4CP9011GetMaxSpeedEv", mfunc_ptr_cast(&CP90::GetMaxSpeed) },
	//{ 0x0, "_ZN4CP909iItemSlotEv", mfunc_ptr_cast(&CP90::iItemSlot) },
	//{ 0x0, "_ZN4CP9013PrimaryAttackEv", mfunc_ptr_cast(&CP90::PrimaryAttack) },
	//{ 0x0, "_ZN4CP906ReloadEv", mfunc_ptr_cast(&CP90::Reload) },
	//{ 0x0, "_ZN4CP9010WeaponIdleEv", mfunc_ptr_cast(&CP90::WeaponIdle) },
	//{ 0x0, "_ZN4CP9012UseDecrementEv", mfunc_ptr_cast(&CP90::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_p90", (size_t)&weapon_p90 },
	//{ 0x0, "_ZN4CP907P90FireEffi", mfunc_ptr_cast(&CP90::P90Fire) },
//CSCOUT
	//virtual func
	//{ 0x0, "_ZN6CSCOUT5SpawnEv", mfunc_ptr_cast(&CSCOUT::Spawn) },
	//{ 0x0, "_ZN6CSCOUT8PrecacheEv", mfunc_ptr_cast(&CSCOUT::Precache) },
	//{ 0x0, "_ZN6CSCOUT11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CSCOUT::GetItemInfo) },
	//{ 0x0, "_ZN6CSCOUT6DeployEv", mfunc_ptr_cast(&CSCOUT::Deploy) },
	//{ 0x0, "_ZN6CSCOUT11GetMaxSpeedEv", mfunc_ptr_cast(&CSCOUT::GetMaxSpeed) },
	//{ 0x0, "_ZN6CSCOUT9iItemSlotEv", mfunc_ptr_cast(&CSCOUT::iItemSlot) },
	//{ 0x0, "_ZN6CSCOUT13PrimaryAttackEv", mfunc_ptr_cast(&CSCOUT::PrimaryAttack) },
	//{ 0x0, "_ZN6CSCOUT15SecondaryAttackEv", mfunc_ptr_cast(&CSCOUT::SecondaryAttack) },
	//{ 0x0, "_ZN6CSCOUT6ReloadEv", mfunc_ptr_cast(&CSCOUT::Reload) },
	//{ 0x0, "_ZN6CSCOUT10WeaponIdleEv", mfunc_ptr_cast(&CSCOUT::WeaponIdle) },
	//{ 0x0, "_ZN6CSCOUT12UseDecrementEv", mfunc_ptr_cast(&CSCOUT::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_scout", (size_t)&weapon_scout },
	//{ 0x0, "_ZN6CSCOUT9SCOUTFireEffi", mfunc_ptr_cast(&CSCOUT::SCOUTFire) },
//CSmokeGrenade
	//virtual func
	//{ 0x0, "_ZN13CSmokeGrenade5SpawnEv", mfunc_ptr_cast(&CSmokeGrenade::Spawn) },
	//{ 0x0, "_ZN13CSmokeGrenade8PrecacheEv", mfunc_ptr_cast(&CSmokeGrenade::Precache) },
	//{ 0x0, "_ZN13CSmokeGrenade11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CSmokeGrenade::GetItemInfo) },
	//{ 0x0, "_ZN13CSmokeGrenade9CanDeployEv", mfunc_ptr_cast(&CSmokeGrenade::CanDeploy) },
	//{ 0x0, "_ZN13CSmokeGrenade7CanDropEv", mfunc_ptr_cast(&CSmokeGrenade::CanDrop) },
	//{ 0x0, "_ZN13CSmokeGrenade6DeployEv", mfunc_ptr_cast(&CSmokeGrenade::Deploy) },
	//{ 0x0, "_ZN13CSmokeGrenade7HolsterEi", mfunc_ptr_cast(&CSmokeGrenade::Holster) },
	//{ 0x0, "_ZN13CSmokeGrenade11GetMaxSpeedEv", mfunc_ptr_cast(&CSmokeGrenade::GetMaxSpeed) },
	//{ 0x0, "_ZN13CSmokeGrenade9iItemSlotEv", mfunc_ptr_cast(&CSmokeGrenade::iItemSlot) },
	//{ 0x0, "_ZN13CSmokeGrenade13PrimaryAttackEv", mfunc_ptr_cast(&CSmokeGrenade::PrimaryAttack) },
	//{ 0x0, "_ZN13CSmokeGrenade15SecondaryAttackEv", mfunc_ptr_cast(&CSmokeGrenade::SecondaryAttack) },
	//{ 0x0, "_ZN13CSmokeGrenade10WeaponIdleEv", mfunc_ptr_cast(&CSmokeGrenade::WeaponIdle) },
	//{ 0x0, "_ZN13CSmokeGrenade12UseDecrementEv", mfunc_ptr_cast(&CSmokeGrenade::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_smokegrenade", (size_t)&weapon_smokegrenade },
	//{ 0x0, "_ZN13CSmokeGrenade19ShieldSecondaryFireEii", mfunc_ptr_cast(&CSmokeGrenade::ShieldSecondaryFire) },
	//{ 0x0, "_ZN13CSmokeGrenade19SetPlayerShieldAnimEv", mfunc_ptr_cast(&CSmokeGrenade::SetPlayerShieldAnim) },
	//{ 0x0, "_ZN13CSmokeGrenade21ResetPlayerShieldAnimEv", mfunc_ptr_cast(&CSmokeGrenade::ResetPlayerShieldAnim) },
//CTMP
	//virtual func
	//{ 0x0, "_ZN4CTMP5SpawnEv", mfunc_ptr_cast(&CTMP::Spawn) },
	//{ 0x0, "_ZN4CTMP8PrecacheEv", mfunc_ptr_cast(&CTMP::Precache) },
	//{ 0x0, "_ZN4CTMP11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CTMP::GetItemInfo) },
	//{ 0x0, "_ZN4CTMP6DeployEv", mfunc_ptr_cast(&CTMP::Deploy) },
	//{ 0x0, "_ZN4CTMP11GetMaxSpeedEv", mfunc_ptr_cast(&CTMP::GetMaxSpeed) },
	//{ 0x0, "_ZN4CTMP9iItemSlotEv", mfunc_ptr_cast(&CTMP::iItemSlot) },
	//{ 0x0, "_ZN4CTMP13PrimaryAttackEv", mfunc_ptr_cast(&CTMP::PrimaryAttack) },
	//{ 0x0, "_ZN4CTMP6ReloadEv", mfunc_ptr_cast(&CTMP::Reload) },
	//{ 0x0, "_ZN4CTMP10WeaponIdleEv", mfunc_ptr_cast(&CTMP::WeaponIdle) },
	//{ 0x0, "_ZN4CTMP12UseDecrementEv", mfunc_ptr_cast(&CTMP::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_tmp", (size_t)&weapon_tmp },
	//{ 0x0, "_ZN4CTMP7TMPFireEffi", mfunc_ptr_cast(&CTMP::TMPFire) },
//CXM1014
	//virtual func
	//{ 0x0, "_ZN7CXM10145SpawnEv", mfunc_ptr_cast(&CXM1014::Spawn) },
	//{ 0x0, "_ZN7CXM10148PrecacheEv", mfunc_ptr_cast(&CXM1014::Precache) },
	//{ 0x0, "_ZN7CXM101411GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CXM1014::GetItemInfo) },
	//{ 0x0, "_ZN7CXM10146DeployEv", mfunc_ptr_cast(&CXM1014::Deploy) },
	//{ 0x0, "_ZN7CXM101411GetMaxSpeedEv", mfunc_ptr_cast(&CXM1014::GetMaxSpeed) },
	//{ 0x0, "_ZN7CXM10149iItemSlotEv", mfunc_ptr_cast(&CXM1014::iItemSlot) },
	//{ 0x01D10370, "_ZN7CXM101413PrimaryAttackEv", mfunc_ptr_cast(&CXM1014::PrimaryAttack) },
	//{ 0x0, "_ZN7CXM10146ReloadEv", mfunc_ptr_cast(&CXM1014::Reload) },
	//{ 0x0, "_ZN7CXM101410WeaponIdleEv", mfunc_ptr_cast(&CXM1014::WeaponIdle) },
	//{ 0x0, "_ZN7CXM101412UseDecrementEv", mfunc_ptr_cast(&CXM1014::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_xm1014", (size_t)&weapon_xm1014 },
//CELITE
	//virtual func
	//{ 0x0, "_ZN6CELITE5SpawnEv", mfunc_ptr_cast(&CELITE::Spawn) },
	//{ 0x0, "_ZN6CELITE8PrecacheEv", mfunc_ptr_cast(&CELITE::Precache) },
	//{ 0x0, "_ZN6CELITE11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CELITE::GetItemInfo) },
	//{ 0x0, "_ZN6CELITE6DeployEv", mfunc_ptr_cast(&CELITE::Deploy) },
	//{ 0x0, "_ZN6CELITE11GetMaxSpeedEv", mfunc_ptr_cast(&CELITE::GetMaxSpeed) },
	//{ 0x0, "_ZN6CELITE9iItemSlotEv", mfunc_ptr_cast(&CELITE::iItemSlot) },
	//{ 0x0, "_ZN6CELITE13PrimaryAttackEv", mfunc_ptr_cast(&CELITE::PrimaryAttack) },
	//{ 0x0, "_ZN6CELITE6ReloadEv", mfunc_ptr_cast(&CELITE::Reload) },
	//{ 0x0, "_ZN6CELITE10WeaponIdleEv", mfunc_ptr_cast(&CELITE::WeaponIdle) },
	//{ 0x0, "_ZN6CELITE12UseDecrementEv", mfunc_ptr_cast(&CELITE::UseDecrement) },
	//{ 0x0, "_ZN6CELITE8IsPistolEv", mfunc_ptr_cast(&CELITE::IsPistol) },
	//non-virtual func
	//{ 0x0, "weapon_xm1014", (size_t)&weapon_xm1014 },
	//{ 0x0, "_ZN6CELITE9ELITEFireEffi", mfunc_ptr_cast(&CELITE::ELITEFire) },
//CFiveSeven
	//virtual func
	//{ 0x0, "_ZN10CFiveSeven5SpawnEv", mfunc_ptr_cast(&CFiveSeven::Spawn) },
	//{ 0x0, "_ZN10CFiveSeven8PrecacheEv", mfunc_ptr_cast(&CFiveSeven::Precache) },
	//{ 0x0, "_ZN10CFiveSeven11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CFiveSeven::GetItemInfo) },
	//{ 0x0, "_ZN10CFiveSeven6DeployEv", mfunc_ptr_cast(&CFiveSeven::Deploy) },
	//{ 0x0, "_ZN10CFiveSeven11GetMaxSpeedEv", mfunc_ptr_cast(&CFiveSeven::GetMaxSpeed) },
	//{ 0x0, "_ZN10CFiveSeven9iItemSlotEv", mfunc_ptr_cast(&CFiveSeven::iItemSlot) },
	//{ 0x0, "_ZN10CFiveSeven13PrimaryAttackEv", mfunc_ptr_cast(&CFiveSeven::PrimaryAttack) },
	//{ 0x0, "_ZN10CFiveSeven15SecondaryAttackEv", mfunc_ptr_cast(&CFiveSeven::SecondaryAttack) },
	//{ 0x0, "_ZN10CFiveSeven6ReloadEv", mfunc_ptr_cast(&CFiveSeven::Reload) },
	//{ 0x0, "_ZN10CFiveSeven10WeaponIdleEv", mfunc_ptr_cast(&CFiveSeven::WeaponIdle) },
	//{ 0x0, "_ZN10CFiveSeven12UseDecrementEv", mfunc_ptr_cast(&CFiveSeven::UseDecrement) },
	//{ 0x0, "_ZN10CFiveSeven8IsPistolEv", mfunc_ptr_cast(&CFiveSeven::IsPistol) },
	//non-virtual func
	//{ 0x0, "weapon_fiveseven", (size_t)&weapon_fiveseven },
	//{ 0x0, "_ZN10CFiveSeven13FiveSevenFireEffi", mfunc_ptr_cast(&CFiveSeven::FiveSevenFire) },
	////{ 0x0, "_ZN10CFiveSeven8MakeBeamEv", mfunc_ptr_cast(&CFiveSeven::MakeBeam) },					// NOXREF
	////{ 0x0, "_ZN10CFiveSeven10BeamUpdateEv", mfunc_ptr_cast(&CFiveSeven::BeamUpdate) },					// NOXREF
//CUMP45
	//virtual func
	//{ 0x0, "_ZN6CUMP455SpawnEv", mfunc_ptr_cast(&CUMP45::Spawn) },
	//{ 0x0, "_ZN6CUMP458PrecacheEv", mfunc_ptr_cast(&CUMP45::Precache) },
	//{ 0x0, "_ZN6CUMP4511GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CUMP45::GetItemInfo) },
	//{ 0x0, "_ZN6CUMP456DeployEv", mfunc_ptr_cast(&CUMP45::Deploy) },
	//{ 0x0, "_ZN6CUMP4511GetMaxSpeedEv", mfunc_ptr_cast(&CUMP45::GetMaxSpeed) },
	//{ 0x0, "_ZN6CUMP459iItemSlotEv", mfunc_ptr_cast(&CUMP45::iItemSlot) },
	//{ 0x0, "_ZN6CUMP4513PrimaryAttackEv", mfunc_ptr_cast(&CUMP45::PrimaryAttack) },
	//{ 0x0, "_ZN6CUMP456ReloadEv", mfunc_ptr_cast(&CUMP45::Reload) },
	//{ 0x0, "_ZN6CUMP4510WeaponIdleEv", mfunc_ptr_cast(&CUMP45::WeaponIdle) },
	//{ 0x0, "_ZN6CUMP4512UseDecrementEv", mfunc_ptr_cast(&CUMP45::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_ump45", (size_t)&weapon_ump45 },
	//{ 0x0, "_ZN6CUMP459UMP45FireEffi", mfunc_ptr_cast(&CUMP45::UMP45Fire) },
//CSG550
	//virtual func
	//{ 0x0, "_ZN6CSG5505SpawnEv", mfunc_ptr_cast(&CSG550::Spawn) },
	//{ 0x0, "_ZN6CSG5508PrecacheEv", mfunc_ptr_cast(&CSG550::Precache) },
	//{ 0x0, "_ZN6CSG55011GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CSG550::GetItemInfo) },
	//{ 0x0, "_ZN6CSG5506DeployEv", mfunc_ptr_cast(&CSG550::Deploy) },
	//{ 0x0, "_ZN6CSG55011GetMaxSpeedEv", mfunc_ptr_cast(&CSG550::GetMaxSpeed) },
	//{ 0x0, "_ZN6CSG5509iItemSlotEv", mfunc_ptr_cast(&CSG550::iItemSlot) },
	//{ 0x0, "_ZN6CSG55013PrimaryAttackEv", mfunc_ptr_cast(&CSG550::PrimaryAttack) },
	//{ 0x0, "_ZN6CSG55015SecondaryAttackEv", mfunc_ptr_cast(&CSG550::SecondaryAttack) },
	//{ 0x0, "_ZN6CSG5506ReloadEv", mfunc_ptr_cast(&CSG550::Reload) },
	//{ 0x0, "_ZN6CSG55010WeaponIdleEv", mfunc_ptr_cast(&CSG550::WeaponIdle) },
	//{ 0x0, "_ZN6CSG55012UseDecrementEv", mfunc_ptr_cast(&CSG550::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_sg550", (size_t)&weapon_sg550 },
	//{ 0x0, "_ZN6CSG5509SG550FireEffi", mfunc_ptr_cast(&CSG550::SG550Fire) },
//CGalil
	//virtual func
	//{ 0x0, "_ZN6CGalil5SpawnEv", mfunc_ptr_cast(&CGalil::Spawn) },
	//{ 0x0, "_ZN6CGalil8PrecacheEv", mfunc_ptr_cast(&CGalil::Precache) },
	//{ 0x0, "_ZN6CGalil11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CGalil::GetItemInfo) },
	//{ 0x0, "_ZN6CGalil6DeployEv", mfunc_ptr_cast(&CGalil::Deploy) },
	//{ 0x0, "_ZN6CGalil11GetMaxSpeedEv", mfunc_ptr_cast(&CGalil::GetMaxSpeed) },
	//{ 0x0, "_ZN6CGalil9iItemSlotEv", mfunc_ptr_cast(&CGalil::iItemSlot) },
	//{ 0x0, "_ZN6CGalil13PrimaryAttackEv", mfunc_ptr_cast(&CGalil::PrimaryAttack) },
	//{ 0x0, "_ZN6CGalil15SecondaryAttackEv", mfunc_ptr_cast(&CGalil::SecondaryAttack) },
	//{ 0x0, "_ZN6CGalil6ReloadEv", mfunc_ptr_cast(&CGalil::Reload) },
	//{ 0x0, "_ZN6CGalil10WeaponIdleEv", mfunc_ptr_cast(&CGalil::WeaponIdle) },
	//{ 0x0, "_ZN6CGalil12UseDecrementEv", mfunc_ptr_cast(&CGalil::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_galil", (size_t)&weapon_galil },
	//{ 0x0, "_ZN6CGalil9GalilFireEffi", mfunc_ptr_cast(&CGalil::GalilFire) },
//CFamas
	//virtual func
	//{ 0x0, "_ZN6CFamas5SpawnEv", mfunc_ptr_cast(&CFamas::Spawn) },
	//{ 0x0, "_ZN6CFamas8PrecacheEv", mfunc_ptr_cast(&CFamas::Precache) },
	//{ 0x0, "_ZN6CFamas11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CFamas::GetItemInfo) },
	//{ 0x0, "_ZN6CFamas6DeployEv", mfunc_ptr_cast(&CFamas::Deploy) },
	//{ 0x0, "_ZN6CFamas11GetMaxSpeedEv", mfunc_ptr_cast(&CFamas::GetMaxSpeed) },
	//{ 0x0, "_ZN6CFamas9iItemSlotEv", mfunc_ptr_cast(&CFamas::iItemSlot) },
	//{ 0x0, "_ZN6CFamas13PrimaryAttackEv", mfunc_ptr_cast(&CFamas::PrimaryAttack) },
	//{ 0x0, "_ZN6CFamas15SecondaryAttackEv", mfunc_ptr_cast(&CFamas::SecondaryAttack) },
	//{ 0x0, "_ZN6CFamas6ReloadEv", mfunc_ptr_cast(&CFamas::Reload) },
	//{ 0x0, "_ZN6CFamas10WeaponIdleEv", mfunc_ptr_cast(&CFamas::WeaponIdle) },
	//{ 0x0, "_ZN6CFamas12UseDecrementEv", mfunc_ptr_cast(&CFamas::UseDecrement) },
	//non-virtual func
	//{ 0x0, "weapon_famas", (size_t)&weapon_famas },
	//{ 0x0, "_ZN6CFamas9FamasFireEffii", mfunc_ptr_cast(&CFamas::FamasFire) },
//CArmoury
	//virtual func
	//{ 0x0, "_ZN8CArmoury5SpawnEv", mfunc_ptr_cast(&CArmoury::Spawn) },
	//{ 0x0, "_ZN8CArmoury8PrecacheEv", mfunc_ptr_cast(&CArmoury::Precache) },
	//{ 0x0, "_ZN8CArmoury7RestartEv", mfunc_ptr_cast(&CArmoury::Restart) },
	//{ 0x01DD0D80, "_ZN8CArmoury8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CArmoury::KeyValue) },
	//non-virtual func
	//{ 0x0, "armoury_entity", (size_t)&armoury_entity },
	//{ 0x0, "_ZN8CArmoury12ArmouryTouchEP11CBaseEntity", mfunc_ptr_cast(&CArmoury::ArmouryTouch) },

#endif // Weapons_Region

#ifndef GGrenade_Region

	//virtual func
	{ 0x01D831C0, "_ZN8CGrenade5SpawnEv", mfunc_ptr_cast(&CGrenade::Spawn_) },
	{ 0x01D84820, "_ZN8CGrenade4SaveER5CSave", mfunc_ptr_cast(&CGrenade::Save_) },
	{ 0x01D84850, "_ZN8CGrenade7RestoreER8CRestore", mfunc_ptr_cast(&CGrenade::Restore_) },
	{ 0x01D594F0, "_ZN8CGrenade10ObjectCapsEv", mfunc_ptr_cast(&CGrenade::ObjectCaps_) },
	{ 0x01D82320, "_ZN8CGrenade6KilledEP9entvars_si", mfunc_ptr_cast(&CGrenade::Killed_) },
	{ 0x01D83560, "_ZN8CGrenade10BloodColorEv", mfunc_ptr_cast(&CGrenade::BloodColor_) },
	{ 0x01D83720, "_ZN8CGrenade3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGrenade::Use_) },
	{ 0x01D82E00, "_ZN8CGrenade11BounceSoundEv", mfunc_ptr_cast(&CGrenade::BounceSound_) },
	//non-virtual func
	//{ 0x0, "", (size_t)&AnnounceFlashInterval }, // NOXREF
	{ 0x01D83570, "_ZN8CGrenade10ShootTimedEP9entvars_s6VectorS2_f", mfunc_ptr_cast(&CGrenade::ShootTimed) },
	{ 0x01D833D0, "_ZN8CGrenade11ShootTimed2EP9entvars_s6VectorS2_fit", mfunc_ptr_cast(&CGrenade::ShootTimed2) },
	//{ 0x01D832C0, "_ZN8CGrenade12ShootContactEP9entvars_s6VectorS2_", mfunc_ptr_cast(&CGrenade::ShootContact) },	// NOXREF
	{ 0x01D83C90, "_ZN8CGrenade17ShootSmokeGrenadeEP9entvars_s6VectorS2_ft", mfunc_ptr_cast(&CGrenade::ShootSmokeGrenade) },
	{ 0x01D839C0, "_ZN8CGrenade18ShootSatchelChargeEP9entvars_s6VectorS2_", mfunc_ptr_cast(&CGrenade::ShootSatchelCharge) },
	//{ 0x01D84760, "_ZN8CGrenade17UseSatchelChargesEP9entvars_sNS_11SATCHELCODEE", mfunc_ptr_cast(&CGrenade::UseSatchelCharges) },	// NOXREF
	{ 0x01D80D40, "_ZN8CGrenade7ExplodeE6VectorS0_", mfunc_ptr_cast<EXPLODE_VECTOR>(&CGrenade::Explode) },
	{ 0x01D80DA0, "_ZN8CGrenade7ExplodeEP11TraceResulti", mfunc_ptr_cast<EXPLODE_TRACERESULT>(&CGrenade::Explode) },
	{ 0x01D81010, "_ZN8CGrenade8Explode2EP11TraceResulti", mfunc_ptr_cast(&CGrenade::Explode2) },
	{ 0x01D81620, "_ZN8CGrenade8Explode3EP11TraceResulti", mfunc_ptr_cast(&CGrenade::Explode3) },
	//{ 0x01D819B0, "_ZN8CGrenade10SG_ExplodeEP11TraceResulti", mfunc_ptr_cast(&CGrenade::SG_Explode) },	// NOXREF
	{ 0x01D82050, "_ZN8CGrenade5SmokeEv", mfunc_ptr_cast(&CGrenade::Smoke) },
	{ 0x01D81F50, "_ZN8CGrenade6Smoke2Ev", mfunc_ptr_cast(&CGrenade::Smoke2) },
	{ 0x01D81DF0, "_ZN8CGrenade8Smoke3_AEv", mfunc_ptr_cast(&CGrenade::Smoke3_A) },
	{ 0x01D81C90, "_ZN8CGrenade8Smoke3_BEv", mfunc_ptr_cast(&CGrenade::Smoke3_B) },
	{ 0x01D81B70, "_ZN8CGrenade8Smoke3_CEv", mfunc_ptr_cast(&CGrenade::Smoke3_C) },
	{ 0x01D82150, "_ZN8CGrenade8SG_SmokeEv", mfunc_ptr_cast(&CGrenade::SG_Smoke) },
	{ 0x01D82B10, "_ZN8CGrenade11BounceTouchEP11CBaseEntity", mfunc_ptr_cast(&CGrenade::BounceTouch) },
	{ 0x01D82D80, "_ZN8CGrenade10SlideTouchEP11CBaseEntity", mfunc_ptr_cast(&CGrenade::SlideTouch) },
	{ 0x01D83E60, "_ZN8CGrenade7C4ThinkEv", mfunc_ptr_cast(&CGrenade::C4Think) },
	{ 0x01D84750, "_ZN8CGrenade7C4TouchEP11CBaseEntity", mfunc_ptr_cast(&CGrenade::C4Touch) },
	{ 0x01D82820, "_ZN8CGrenade12ExplodeTouchEP11CBaseEntity", mfunc_ptr_cast(&CGrenade::ExplodeTouch) },
	{ 0x01D82A00, "_ZN8CGrenade16DangerSoundThinkEv", mfunc_ptr_cast(&CGrenade::DangerSoundThink) },
	{ 0x01D823D0, "_ZN8CGrenade11PreDetonateEv", mfunc_ptr_cast(&CGrenade::PreDetonate) },
	{ 0x01D82410, "_ZN8CGrenade8DetonateEv", mfunc_ptr_cast(&CGrenade::Detonate) },
	{ 0x01D824A0, "_ZN8CGrenade11SG_DetonateEv", mfunc_ptr_cast(&CGrenade::SG_Detonate) },
	{ 0x01D82700, "_ZN8CGrenade9Detonate2Ev", mfunc_ptr_cast(&CGrenade::Detonate2) },
	{ 0x01D82790, "_ZN8CGrenade9Detonate3Ev", mfunc_ptr_cast(&CGrenade::Detonate3) },
	{ 0x01D823B0, "_ZN8CGrenade11DetonateUseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CGrenade::DetonateUse) },
	{ 0x01D82EE0, "_ZN8CGrenade11TumbleThinkEv", mfunc_ptr_cast(&CGrenade::TumbleThink) },
	{ 0x01D83030, "_ZN8CGrenade14SG_TumbleThinkEv", mfunc_ptr_cast(&CGrenade::SG_TumbleThink) },

#endif // GGrenade_Region

#ifndef Animation_Region

	{ 0x01D5A650, "_Z11ExtractBboxPviPfS0_", (size_t)&ExtractBbox },
	{ 0x01D5A6B0, "_Z14LookupActivityPvP9entvars_si", (size_t)&LookupActivity },
	{ 0x01D5A780, "_Z22LookupActivityHeaviestPvP9entvars_si", (size_t)&LookupActivityHeaviest },
	//{ 0x01D5A7D0, "_Z14GetEyePositionPvPf", (size_t)&GetEyePosition },	// NOXREF
	{ 0x01D5A810, "_Z14LookupSequencePvPKc", (size_t)&LookupSequence },
	//{ 0x01D5A870, "_Z12IsSoundEventi", (size_t)&IsSoundEvent },	// NOXREF
	//{ 0x01D5A890, "_Z16SequencePrecachePvPKc", (size_t)&SequencePrecache },	// NOXREF
	{ 0x01D5A9A0, "_Z15GetSequenceInfoPvP9entvars_sPfS2_", (size_t)&GetSequenceInfo },
	{ 0x01D5AA60, "_Z16GetSequenceFlagsPvP9entvars_s", (size_t)&GetSequenceFlags },
	{ 0x01D5AAA0, "_Z17GetAnimationEventPvP9entvars_sP14MonsterEvent_tffi", (size_t)&GetAnimationEvent },
	{ 0x01D5ABF0, "_Z13SetControllerPvP9entvars_sif", (size_t)&SetController },
	{ 0x01D5AD60, "_Z11SetBlendingPvP9entvars_sif", (size_t)&SetBlending },
	{ 0x01D5AEB0, "_Z14FindTransitionPviiPi", (size_t)&FindTransition },
	{ 0x01D5AFC0, "_Z12SetBodygroupPvP9entvars_sii", (size_t)&SetBodygroup },
	{ 0x01D5B020, "_Z12GetBodygroupPvP9entvars_si", (size_t)&GetBodygroup },
	{ 0x01D5B080, "Server_GetBlendingInterface", (size_t)&Server_GetBlendingInterface },
	{ 0x01D5B0E0, "_Z15AngleQuaternionPfS_", (size_t)&AngleQuaternion },
	{ 0x01D5B190, "_Z15QuaternionSlerpPfS_fS_", (size_t)&QuaternionSlerp },
	//{ 0x01D5B350, "_Z16QuaternionMatrixPfPA4_f", (size_t)&QuaternionMatrix },
	{ 0x01D5B430, "_Z13StudioGetAnimP7model_sP16mstudioseqdesc_t", (size_t)&StudioGetAnim },
	//{ 0x01D5B4C0, "_Z15LookupAnimationP11studiohdr_tP7model_sP16mstudioseqdesc_ti", (size_t)&LookupAnimation },	// NOXREF
	{ 0x01D5B500, "_Z17StudioCalcBoneAdjfPfPKhS1_h", (size_t)&StudioCalcBoneAdj },
	{ 0x01D5B720, "_Z23StudioCalcBoneQuaterionifP13mstudiobone_tP13mstudioanim_tPfS3_", (size_t)&StudioCalcBoneQuaterion },
	{ 0x01D5B8E0, "_Z22StudioCalcBonePositionifP13mstudiobone_tP13mstudioanim_tPfS3_", (size_t)&StudioCalcBonePosition },
	{ 0x01D5BA20, "_Z16StudioSlerpBonesPA4_fPA3_fS0_S2_f", (size_t)&StudioSlerpBones },
	//{ 0x01D5BB50, "_Z19StudioCalcRotationsP13mstudiobone_tPiiPfPA3_fPA4_fP16mstudioseqdesc_tP13mstudioanim_tff", (size_t)&StudioCalcRotations },	// NOXREF
	{ 0x01D5BBE0, "_Z16ConcatTransformsPA4_fS0_S0_", (size_t)&ConcatTransforms },
	//{ 0x01D5BD20, "_Z19SV_StudioSetupBonesP7model_sfiPKfS2_PKhS4_iPK7edict_s", (size_t)&SV_StudioSetupBones },

#endif // Animation_Region

#ifndef MemoryPool_Region

	//{ 0x01D8A2D0, "_ZN11CMemoryPoolC2Eii", mfunc_ptr_cast(&CMemoryPool::CMemoryPool) }, // NOXREF
	{ 0x01D8A330, "_ZN11CMemoryPool10AddNewBlobEv", mfunc_ptr_cast(&CMemoryPool::AddNewBlob) },
	{ 0x01D8A3D0, "_ZN11CMemoryPool5AllocEj", mfunc_ptr_cast(&CMemoryPool::Alloc) },
	{ 0x01D8A420, "_ZN11CMemoryPool4FreeEPv", mfunc_ptr_cast(&CMemoryPool::Free) },

#endif // MemoryPool_Region

#ifndef Unicode_StrTools_Region

	//{ 0x0, "_Z16Q_IsValidUChar32w", (size_t)&Q_IsValidUChar32 },

#ifdef _WIN32
	{ 0x01DDE010, "", (size_t)&Q_UTF32ToUChar32 },
#endif // _WIN32

	//{ 0x0, "", (size_t)&Q_UChar32ToUTF32Len },
	//{ 0x0, "", (size_t)&Q_UChar32ToUTF32 },
	//{ 0x01DDDEE0, "", (size_t)&Q_UChar32ToUTF8Len },	// NOXREF
	//{ 0x0, "_Z19Q_UChar32ToUTF16Lenw", (size_t)&Q_UChar32ToUTF16Len },	// NOXREF
	//{ 0x0, "_Z16Q_UChar32ToUTF16wPt", (size_t)&Q_UChar32ToUTF16 },	// NOXREF
	//{ 0x01DDDF70, "_Z15Q_UChar32ToUTF8wPc", (size_t)&Q_UChar32ToUTF8 },	// NOXREF
	//{ 0x0, "_Z16Q_UTF16ToUChar32PKtRwRb", (size_t)&Q_UTF16ToUChar32 },	// NOXREF
	//{ 0x0, "_Z13Q_UTF8ToUTF16PKcPti25EStringConvertErrorPolicy", (size_t)&Q_UTF8ToUTF16 },	// NOXREF
	//{ 0x01DDFA30, "_Z13Q_UTF8ToUTF32PKcPwi25EStringConvertErrorPolicy", (size_t)&Q_UTF8ToUTF32 },
	//{ 0x0, "_Z13Q_UTF16ToUTF8PKtPci25EStringConvertErrorPolicy", (size_t)&Q_UTF16ToUTF8 },	// NOXREF
	//{ 0x0, "_Z14Q_UTF16ToUTF32PKtPwi25EStringConvertErrorPolicy", (size_t)&Q_UTF16ToUTF32 },	// NOXREF
	//{ 0x0, "_Z13Q_UTF32ToUTF8PKwPci25EStringConvertErrorPolicy", (size_t)&Q_UTF32ToUTF8 },	// NOXREF
	//{ 0x01DDEB00, "_Z14Q_UTF32ToUTF16PKwPti25EStringConvertErrorPolicy", (size_t)&Q_UTF32ToUTF16 },	// NOXREF
	//{ 0x01DDECA0, "_Z15Q_UTF8ToUChar32PKcRwRb", (size_t)&Q_UTF8ToUChar32 },
	{ 0x01DDEE00, "Q_UnicodeValidate", (size_t)&Q_UnicodeValidate },
	//{ 0x01DDEE50, "Q_UnicodeLength", (size_t)&Q_UnicodeLength },	// NOXREF
	//{ 0x01DDEE80, "Q_UnicodeAdvance", (size_t)&Q_UnicodeAdvance },
	//{ 0x01DDEEC0, "_Z14Q_IsMeanSpaceWw", (size_t)&Q_IsMeanSpaceW },	// NOXREF
	//{ 0x01DDF150, "_Z15Q_IsDeprecatedWw", (size_t)&Q_IsDeprecatedW },	// NOXREF
	//{ 0x0, "", (size_t)&StripWhitespaceWorker },	// NOXREF
	//{ 0x0, "", (size_t)&StripUnprintableWorker },	// NOXREF
	{ 0x01DDF1D0, "Q_StripUnprintableAndSpace", (size_t)&Q_StripUnprintableAndSpace },
	//{ 0x01DDF8A0, "V_UTF8ToUChar32", (size_t)&V_UTF8ToUChar32 },	// NOXREF
	//{ 0x01DDF8D0, "Q_UnicodeRepair", (size_t)&Q_UnicodeRepair },	// NOXREF

#endif // Unicode_StrTools_Region

#ifndef CUtlSymbol_Region

	//{ 0x0, "_ZN10CUtlSymbolC2EPKc", mfunc_ptr_cast(&CUtlSymbol::CUtlSymbol) },
	//{ 0x0, "_ZN10CUtlSymbol10InitializeEv", mfunc_ptr_cast(&CUtlSymbol::Initialize) },
	//{ 0x0, "_ZN10CUtlSymbol9CurrTableEv", mfunc_ptr_cast(&CUtlSymbol::CurrTable) },
	//{ 0x0, "_ZNK10CUtlSymbol6StringEv", mfunc_ptr_cast(&CUtlSymbol::String) },
	//{ 0x01DC8390, "_ZN15CUtlSymbolTable7SymLessERKjS1_", mfunc_ptr_cast(&CUtlSymbolTable::SymLess) },
	//{ 0x01DC8410, "_ZN15CUtlSymbolTable8SymLessiERKjS1_", mfunc_ptr_cast(&CUtlSymbolTable::SymLessi) },
	//{ 0x01DC8460, "_ZN15CUtlSymbolTableC2Eiib", mfunc_ptr_cast(&CUtlSymbolTable::CUtlSymbolTable) },	// NOXREF
	//{ 0x01DC84D0, "_ZN15CUtlSymbolTableD2Ev", mfunc_ptr_cast(&CUtlSymbolTable::~CUtlSymbolTable) },	// NOXREF
	//{ 0x01DC8540, "_ZN15CUtlSymbolTable4FindEPKc", mfunc_ptr_cast(&CUtlSymbolTable::Find) },	// NOXREF
	//{ 0x0, "_ZNK15CUtlSymbolTable6StringE10CUtlSymbol", mfunc_ptr_cast(&CUtlSymbolTable::String) },
	//{ 0x0, "_ZN15CUtlSymbolTable9RemoveAllEv", mfunc_ptr_cast(&CUtlSymbolTable::RemoveAll) },
	//{ 0x0, "_ZN15CUtlSymbolTable9AddStringEPKc", mfunc_ptr_cast(&CUtlSymbolTable::AddString) },

#endif // CUtlSymbol_Region

#ifndef Debug_Region

	//{ 0x0, "", (size_t)&IsDeveloper },	// NOXREF
	//{ 0x01D732D0, "_Z12UTIL_DPrintf15DebugOutputTypePcz", mfunc_ptr_cast<DPrintf_Flag>(&UTIL_DPrintf) },	// NOXREF
	{ 0x01D73320, "_Z12UTIL_DPrintfPcz", mfunc_ptr_cast<DPrintf_MSG>(&UTIL_DPrintf) },
	//{ 0x01D73360, "_Z20UTIL_SetDprintfFlagsPKc", (size_t)&PrintDebugFlags },	// NOXREF
	//{ 0x0, "_ZL12SetDebugFlagPKcb", (size_t)&SetDebugFlag },	// NOXREF
	//{ 0x0, "_Z14PrintDebugFlagPKc", (size_t)&PrintDebugFlag },	// NOXREF
	{ 0x01D73410, "_Z20UTIL_SetDprintfFlagsPKc", (size_t)&UTIL_SetDprintfFlags },
	//{ 0x01D73690, "_Z15UTIL_BotDPrintfPcz", (size_t)&UTIL_BotDPrintf },		// NOXREF
	{ 0x01D736E0, "_Z18UTIL_CareerDPrintfPcz", (size_t)&UTIL_CareerDPrintf },
	//{ 0x01D73730, "_Z17UTIL_TutorDPrintfPcz", (size_t)&UTIL_TutorDPrintf },	// NOXREF
	//{ 0x01D73780, "_Z17UTIL_StatsDPrintfPcz", (size_t)&UTIL_StatsDPrintf },	// NOXREF
	//{ 0x01D737D0, "_Z19UTIL_HostageDPrintfPcz", (size_t)&UTIL_HostageDPrintf },	// NOXREF

#endif // Debug_Region

#ifndef CS_Bot_Region
//Bot Manager
	//virtual func
	{ 0x01D341B0, "_ZN11CBotManager12RestartRoundEv", mfunc_ptr_cast(&CBotManager::RestartRound_) },
	{ 0x01D34210, "_ZN11CBotManager10StartFrameEv", mfunc_ptr_cast(&CBotManager::StartFrame_) },
	{ 0x01D34540, "_ZN11CBotManager7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBotManager::OnEvent_) },
	//non-virtual func
	////{ 0x0, "", mfunc_ptr_cast(&CBotManager::CBotManager) },
	{ 0x01D34510, "_ZNK11CBotManager17GetNavMapFilenameEv", mfunc_ptr_cast(&CBotManager::GetNavMapFilename) },
	{ 0x01D34650, "_ZN11CBotManager10AddGrenadeEiP8CGrenade", mfunc_ptr_cast(&CBotManager::AddGrenade) },
	{ 0x01D346C0, "_ZN11CBotManager13RemoveGrenadeEP8CGrenade", mfunc_ptr_cast(&CBotManager::RemoveGrenade) },
	//{ 0x01D346F0, "_ZN11CBotManager22ValidateActiveGrenadesEv", mfunc_ptr_cast(&CBotManager::ValidateActiveGrenades) },	// NOXREF
	//{ 0x01D34740, "_ZN11CBotManager18DestroyAllGrenadesEv", mfunc_ptr_cast(&CBotManager::DestroyAllGrenades) },	// NOXREF
	{ 0x01D347A0, "_ZN11CBotManager18IsInsideSmokeCloudEPK6Vector", mfunc_ptr_cast(&CBotManager::IsInsideSmokeCloud) },				// FIXME!!
	{ 0x01D34850, "_ZN11CBotManager20IsLineBlockedBySmokeEPK6VectorS2_", mfunc_ptr_cast(&CBotManager::IsLineBlockedBySmoke) },
	//non-class func
	//{ 0x0, "_Z15NameToGameEventPKc", (size_t)&NameToGameEvent },
//CCSBotManager
	//virtual func
	{ 0x01D23770, "_ZN13CCSBotManager16ClientDisconnectEP11CBasePlayer", mfunc_ptr_cast(&CCSBotManager::ClientDisconnect_) },
	{ 0x01D24880, "_ZN13CCSBotManager13ClientCommandEP11CBasePlayerPKc", mfunc_ptr_cast(&CCSBotManager::ClientCommand_) },
	{ 0x01D234D0, "_ZN13CCSBotManager14ServerActivateEv", mfunc_ptr_cast(&CCSBotManager::ServerActivate_) },
	{ 0x01D23760, "_ZN13CCSBotManager16ServerDeactivateEv", mfunc_ptr_cast(&CCSBotManager::ServerDeactivate_) },
	//{ 0x01D23900, "_ZN13CCSBotManager13ServerCommandEPKc", mfunc_ptr_cast(&CCSBotManager::ServerCommand_) },
	{ 0x01D23520, "_ZN13CCSBotManager16AddServerCommandEPKc", mfunc_ptr_cast(&CCSBotManager::AddServerCommand_) },
	{ 0x01D23540, "_ZN13CCSBotManager17AddServerCommandsEv", mfunc_ptr_cast(&CCSBotManager::AddServerCommands_) },
	{ 0x01D22F40, "_ZN13CCSBotManager12RestartRoundEv", mfunc_ptr_cast(&CCSBotManager::RestartRound_) },
	//{ 0x01D23200, "_ZN13CCSBotManager10StartFrameEv", mfunc_ptr_cast(&CCSBotManager::StartFrame) },
	{ 0x01D25780, "_ZN13CCSBotManager7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSBotManager::OnEvent_) },
	//{ 0x01D25970, "_ZNK13CCSBotManager17GetPlayerPriorityEP11CBasePlayer", mfunc_ptr_cast(&CCSBotManager::GetPlayerPriority) },
	//{ 0x0, "_ZNK13CCSBotManager17IsImportantPlayerEP11CBasePlayer", mfunc_ptr_cast(&CCSBotManager::IsImportantPlayer) },
	//non-virtual func
	{ 0x01D24D90, "_ZN13CCSBotManager15ValidateMapDataEv", mfunc_ptr_cast(&CCSBotManager::ValidateMapData) },
	//{ 0x0, "_ZNK13CCSBotManager13IsLearningMapEv", mfunc_ptr_cast(&CCSBotManager::IsLearningMap) },
	//{ 0x0, "_ZN13CCSBotManager18SetLearningMapFlagEv", mfunc_ptr_cast(&CCSBotManager::SetLearningMapFlag) },
	//{ 0x0, "_ZNK13CCSBotManager19IsAnalysisRequestedEv", mfunc_ptr_cast(&CCSBotManager::IsAnalysisRequested) },
	//{ 0x0, "_ZN13CCSBotManager15RequestAnalysisEv", mfunc_ptr_cast(&CCSBotManager::RequestAnalysis) },
	//{ 0x0, "_ZN13CCSBotManager18AckAnalysisRequestEv", mfunc_ptr_cast(&CCSBotManager::AckAnalysisRequest) },
	//{ 0x0, "_ZN13CCSBotManager18GetDifficultyLevelEv", mfunc_ptr_cast(&CCSBotManager::BotDifficultyType GetDifficultyLevel) },
	//{ 0x0, "_ZNK13CCSBotManager11GetScenarioEv", mfunc_ptr_cast(&CCSBotManager::GameScenarioType GetScenario) },
	//{ 0x0, "_ZNK13CCSBotManager7GetZoneEi", mfunc_ptr_cast<GET_ZONE_INT>(&CCSBotManager::GetZone) },	// NOXREF
	//{ 0x01D25530, "_ZNK13CCSBotManager7GetZoneEPK6Vector", mfunc_ptr_cast<GET_ZONE_VECTOR>(&CCSBotManager::GetZone) },
	//{ 0x0, "_ZNK13CCSBotManager14GetClosestZoneEPK6void", mfunc_ptr_cast(&CCSBotManager::GetClosestZone) },
	//{ 0x0, "_ZNK13CCSBotManager14GetClosestZoneEPK11CBaseEntity", mfunc_ptr_cast(&CCSBotManager::GetClosestZone) },
	//{ 0x0, "_ZNK13CCSBotManager12GetZoneCountEv", mfunc_ptr_cast(&CCSBotManager::GetZoneCount) },
	//{ 0x0, "_ZNK13CCSBotManager23GetRandomPositionInZoneEPKNS_4ZoneE", mfunc_ptr_cast(&CCSBotManager::GetRandomPositionInZone) },
	//{ 0x01D25750, "_ZNK13CCSBotManager19GetRandomAreaInZoneEPKNS_4ZoneE", mfunc_ptr_cast(&CCSBotManager::GetRandomAreaInZone) },
	//{ 0x0, "_ZNK13CCSBotManager13GetRandomZoneEv", mfunc_ptr_cast(&CCSBotManager::GetRandomZone) },
	//{ 0x0, "_ZNK13CCSBotManager13IsBombPlantedEv", mfunc_ptr_cast(&CCSBotManager::IsBombPlanted) },
	//{ 0x0, "_ZNK13CCSBotManager21GetBombPlantTimestampEv", mfunc_ptr_cast(&CCSBotManager::GetBombPlantTimestamp) },
	//{ 0x0, "_ZNK13CCSBotManager17IsTimeToPlantBombEv", mfunc_ptr_cast(&CCSBotManager::IsTimeToPlantBomb) },
	//{ 0x0, "_ZNK13CCSBotManager14GetBombDefuserEv", mfunc_ptr_cast(&CCSBotManager::GetBombDefuser) },
	//{ 0x0, "_ZNK13CCSBotManager15GetBombTimeLeftEv", mfunc_ptr_cast(&CCSBotManager::GetBombTimeLeft) },
	//{ 0x0, "_ZN13CCSBotManager12GetLooseBombEv", mfunc_ptr_cast(&CCSBotManager::GetLooseBomb) },
	//{ 0x0, "_ZNK13CCSBotManager16GetLooseBombAreaEv", mfunc_ptr_cast(&CCSBotManager::GetLooseBombArea) },
	{ 0x01D258D0, "_ZN13CCSBotManager12SetLooseBombEP11CBaseEntity", mfunc_ptr_cast(&CCSBotManager::SetLooseBomb) },
	//{ 0x0, "_ZNK13CCSBotManager24GetRadioMessageTimestampE13GameEventTypei", mfunc_ptr_cast(&CCSBotManager::GetRadioMessageTimestamp) },
	//{ 0x0, "_ZNK13CCSBotManager23GetRadioMessageIntervalE13GameEventTypei", mfunc_ptr_cast(&CCSBotManager::GetRadioMessageInterval) },
	//{ 0x0, "_ZN13CCSBotManager24SetRadioMessageTimestampE13GameEventTypei", mfunc_ptr_cast(&CCSBotManager::SetRadioMessageTimestamp) },
	//{ 0x01D25AA0, "_ZN13CCSBotManager27ResetRadioMessageTimestampsEv", mfunc_ptr_cast(&CCSBotManager::ResetRadioMessageTimestamps) },	// NOXREF
	//{ 0x0, "_ZNK13CCSBotManager25GetLastSeenEnemyTimestampEv", mfunc_ptr_cast(&CCSBotManager::GetLastSeenEnemyTimestamp) },
	//{ 0x0, "_ZN13CCSBotManager25SetLastSeenEnemyTimestampEv", mfunc_ptr_cast(&CCSBotManager::SetLastSeenEnemyTimestamp) },
	//{ 0x0, "_ZNK13CCSBotManager17GetRoundStartTimeEv", mfunc_ptr_cast(&CCSBotManager::GetRoundStartTime) },
	//{ 0x0, "_ZNK13CCSBotManager19GetElapsedRoundTimeEv", mfunc_ptr_cast(&CCSBotManager::GetElapsedRoundTime) },
	//{ 0x0, "_ZNK13CCSBotManager11AllowRoguesEv", mfunc_ptr_cast(&CCSBotManager::AllowRogues) },
	//{ 0x0, "_ZNK13CCSBotManager12AllowPistolsEv", mfunc_ptr_cast(&CCSBotManager::AllowPistols) },
	//{ 0x0, "_ZNK13CCSBotManager13AllowShotgunsEv", mfunc_ptr_cast(&CCSBotManager::AllowShotguns) },
	//{ 0x0, "_ZNK13CCSBotManager19AllowSubMachineGunsEv", mfunc_ptr_cast(&CCSBotManager::AllowSubMachineGuns) },
	//{ 0x0, "_ZNK13CCSBotManager11AllowRiflesEv", mfunc_ptr_cast(&CCSBotManager::AllowRifles) },
	//{ 0x0, "_ZNK13CCSBotManager16AllowMachineGunsEv", mfunc_ptr_cast(&CCSBotManager::AllowMachineGuns) },
	//{ 0x0, "_ZNK13CCSBotManager13AllowGrenadesEv", mfunc_ptr_cast(&CCSBotManager::AllowGrenades) },
	//{ 0x0, "_ZNK13CCSBotManager12AllowSnipersEv", mfunc_ptr_cast(&CCSBotManager::AllowSnipers) },
	//{ 0x0, "_ZNK13CCSBotManager19AllowTacticalShieldEv", mfunc_ptr_cast(&CCSBotManager::AllowTacticalShield) },
	//{ 0x0, "_ZNK13CCSBotManager23AllowFriendlyFireDamageEv", mfunc_ptr_cast(&CCSBotManager::AllowFriendlyFireDamage) },
	{ 0x01D232D0, "_ZN13CCSBotManager15IsWeaponUseableEP15CBasePlayerItem", mfunc_ptr_cast(&CCSBotManager::IsWeaponUseable) },
	//{ 0x0, "_ZNK13CCSBotManager16IsDefenseRushingEv", mfunc_ptr_cast(&CCSBotManager::IsDefenseRushing) },
	//{ 0x0, "_ZNK13CCSBotManager11IsOnDefenseEPK11CBasePlayer", mfunc_ptr_cast(&CCSBotManager::IsOnDefense) },
	//{ 0x0, "_ZNK13CCSBotManager11IsOnOffenseEPK11CBasePlayer", mfunc_ptr_cast(&CCSBotManager::IsOnOffense) },
	//{ 0x0, "_ZNK13CCSBotManager11IsRoundOverEv", mfunc_ptr_cast(&CCSBotManager::IsRoundOver) },
	//{ 0x0, "_ZNK13CCSBotManager11GetNavPlaceEv", mfunc_ptr_cast(&CCSBotManager::GetNavPlace) },
	//{ 0x0, "_ZN13CCSBotManager11SetNavPlaceEj", mfunc_ptr_cast(&CCSBotManager::SetNavPlace) },
	//{ 0x01D24D10, "_ZN13CCSBotManager15MonitorBotCVarsEv", mfunc_ptr_cast(&CCSBotManager::MonitorBotCVars) },
	//{ 0x01D24AE0, "_ZN13CCSBotManager16MaintainBotQuotaEv", mfunc_ptr_cast(&CCSBotManager::MaintainBotQuota) },
	//{ 0x0, "_ZN13CCSBotManager16GetRandomBotNameENS_9SkillTypeE", mfunc_ptr_cast(&CCSBotManager::GetRandomBotName) },
	//{ 0x01D25270, "_ZN13CCSBotManager6AddBotEPK10BotProfile18BotProfileTeamType", mfunc_ptr_cast(&CCSBotManager::AddBot) },
	//{ 0x01D248B0, "_ZN13CCSBotManager13BotAddCommandE18BotProfileTeamTypeb", mfunc_ptr_cast(&CCSBotManager::BotAddCommand) },
	//{ 0x01D238A0, "_Z16PrintAllEntitiesv", (size_t)&PrintAllEntities },	// NOXREF
	//{ 0x01D23020, "_Z12UTIL_DrawBoxP6Extentiiii", (size_t)&UTIL_DrawBox },

//CCSBot
	//{ 0x0, "_ZN6CCSBotC2Ev", mfunc_ptr_cast(&CCSBot::CCSBot) },
	//virtual func
	//{ 0x0, "_ZN6CCSBot10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CCSBot::TakeDamage_) },
	//{ 0x01D175A0, "_ZN6CCSBot6KilledEP9entvars_si", mfunc_ptr_cast(&CCSBot::Killed_) },
	//{ 0x0, "_ZN6CCSBot12RoundRespawnEv", mfunc_ptr_cast(&CCSBot::RoundRespawn_) },
	//{ 0x0, "_ZN6CCSBot5BlindEfffi", mfunc_ptr_cast(&CCSBot::Blind_) },
	//{ 0x01D32370, "_ZN6CCSBot16OnTouchingWeaponEP10CWeaponBox", mfunc_ptr_cast(&CCSBot::OnTouchingWeapon_) },
	//{ 0x01D20A60, "_ZN6CCSBot10InitializeEPK10BotProfile", mfunc_ptr_cast(&CCSBot::Initialize_) },
	//{ 0x0, "_ZN6CCSBot8SpawnBotEv", mfunc_ptr_cast(&CCSBot::SpawnBot_) },
	{ 0x01D2D370, "_ZN6CCSBot6UpkeepEv", mfunc_ptr_cast(&CCSBot::Upkeep_) },
	//{ 0x01D2D9B0, "_ZN6CCSBot6UpdateEv", mfunc_ptr_cast(&CCSBot::Update_) },	// using refs
	//{ 0x0, "_ZN6CCSBot4WalkEv", mfunc_ptr_cast(&CCSBot::Walk_) },
	//{ 0x0, "_ZN6CCSBot4JumpEb", mfunc_ptr_cast(&CCSBot::Jump_) },
	//{ 0x01D1F990, "_ZN6CCSBot7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSBot::OnEvent_) },
	//{ 0x01D2F490, "_ZNK6CCSBot9IsVisibleEPK6Vectorb", mfunc_ptr_cast<IS_VISIBLE_VECTOR>(&CCSBot::IsVisible_) },
	//{ 0x01D2F5C0, "_ZNK6CCSBot9IsVisibleEP11CBasePlayerbPh", mfunc_ptr_cast<IS_VISIBLE_CBASEPLAYER>(&CCSBot::IsVisible_) },
	{ 0x01D21390, "_ZNK6CCSBot18IsEnemyPartVisibleEN4CBot15VisiblePartTypeE", mfunc_ptr_cast(&CCSBot::IsEnemyPartVisible_) },
	//non-virtual func
	{ 0x01D20EE0, "_ZN6CCSBot10DisconnectEv", mfunc_ptr_cast(&CCSBot::Disconnect) },
	//{ 0x0, "_ZNK6CCSBot14GetCombatRangeEv", mfunc_ptr_cast(&CCSBot::GetCombatRange) },
	//{ 0x0, "_ZNK6CCSBot7IsRogueEv", mfunc_ptr_cast(&CCSBot::IsRogue) },
	//{ 0x0, "_ZN6CCSBot8SetRogueEb", mfunc_ptr_cast(&CCSBot::SetRogue) },
	//{ 0x0, "_ZNK6CCSBot10IsHurryingEv", mfunc_ptr_cast(&CCSBot::IsHurrying) },
	//{ 0x0, "_ZN6CCSBot5HurryEf", mfunc_ptr_cast(&CCSBot::Hurry) },
	//{ 0x01D18620, "_ZNK6CCSBot6IsSafeEv", mfunc_ptr_cast(&CCSBot::IsSafe) },
	//{ 0x01D18650, "_ZNK6CCSBot14IsWellPastSafeEv", mfunc_ptr_cast(&CCSBot::IsWellPastSafe) },
	//{ 0x0, "_ZNK6CCSBot15IsEndOfSafeTimeEv", mfunc_ptr_cast(&CCSBot::IsEndOfSafeTime) },
	//{ 0x0, "_ZNK6CCSBot20GetSafeTimeRemainingEv", mfunc_ptr_cast(&CCSBot::GetSafeTimeRemaining) },
	//{ 0x0, "_ZNK6CCSBot11GetSafeTimeEv", mfunc_ptr_cast(&CCSBot::GetSafeTime) },
	//{ 0x0, "_ZNK6CCSBot11IsUnhealthyEv", mfunc_ptr_cast(&CCSBot::IsUnhealthy) },
	//{ 0x01D2BE50, "_ZN6CCSBot4IdleEv", mfunc_ptr_cast(&CCSBot::Idle) },
	//{ 0x0, "_ZN6CCSBot4HideEP8CNavAreaffb", mfunc_ptr_cast<HIDE_NAV_AREA>(&CCSBot::Hide) },
	//{ 0x0, "_ZN6CCSBot4HideEPK6Vectorfb", mfunc_ptr_cast<HIDE_VECTOR>(&CCSBot::Hide) },
	//{ 0x0, "_ZN6CCSBot9TryToHideEP8CNavAreaffbb", mfunc_ptr_cast(&CCSBot::TryToHide) },
	//{ 0x0, "_ZN6CCSBot12TryToRetreatEv", mfunc_ptr_cast(&CCSBot::TryToRetreat) },
	{ 0x01D2CEA0, "_ZNK6CCSBot8IsHidingEv", mfunc_ptr_cast(&CCSBot::IsHiding) },
	//{ 0x01D2CEC0, "_ZNK6CCSBot14IsAtHidingSpotEv", mfunc_ptr_cast(&CCSBot::IsAtHidingSpot) },
	//{ 0x0, "_ZN6CCSBot4HuntEv", mfunc_ptr_cast(&CCSBot::Hunt) },
	//{ 0x0, "_ZNK6CCSBot9IsHuntingEv", mfunc_ptr_cast(&CCSBot::IsHunting) },
	//{ 0x01D2CB60, "_ZN6CCSBot6AttackEP11CBasePlayer", mfunc_ptr_cast(&CCSBot::Attack) },
	//{ 0x0, "_ZN6CCSBot17FireWeaponAtEnemyEv", mfunc_ptr_cast(&CCSBot::FireWeaponAtEnemy) },
	//{ 0x01D2CD80, "_ZN6CCSBot13StopAttackingEv", mfunc_ptr_cast(&CCSBot::StopAttacking) },
	{ 0x01D2CE50, "_ZNK6CCSBot11IsAttackingEv", mfunc_ptr_cast(&CCSBot::IsAttacking) },
	//{ 0x01D2CF40, "_ZN6CCSBot6MoveToEPK6Vector9RouteType", mfunc_ptr_cast(&CCSBot::MoveTo) },
	//{ 0x0, "_ZNK6CCSBot10IsMovingToEv", mfunc_ptr_cast(&CCSBot::IsMovingTo) },
	//{ 0x0, "_ZN6CCSBot9PlantBombEv", mfunc_ptr_cast(&CCSBot::PlantBomb) },
	//{ 0x0, "_ZN6CCSBot9FetchBombEv", mfunc_ptr_cast(&CCSBot::FetchBomb) },
	//{ 0x0, "_ZNK6CCSBot15NoticeLooseBombEv", mfunc_ptr_cast(&CCSBot::NoticeLooseBomb) },
	//{ 0x0, "_ZNK6CCSBot15CanSeeLooseBombEv", mfunc_ptr_cast(&CCSBot::CanSeeLooseBomb) },
	//{ 0x0, "_ZNK6CCSBot14IsCarryingBombEv", mfunc_ptr_cast(&CCSBot::IsCarryingBomb) },
	//{ 0x0, "_ZN6CCSBot10DefuseBombEv", mfunc_ptr_cast(&CCSBot::DefuseBomb) },
	//{ 0x0, "_ZNK6CCSBot14IsDefusingBombEv", mfunc_ptr_cast(&CCSBot::IsDefusingBomb) },
	//{ 0x0, "_ZNK6CCSBot17CanSeePlantedBombEv", mfunc_ptr_cast(&CCSBot::CanSeePlantedBomb) },
	//{ 0x0, "_ZN6CCSBot14EscapeFromBombEv", mfunc_ptr_cast(&CCSBot::EscapeFromBomb) },
	//{ 0x0, "_ZNK6CCSBot18IsEscapingFromBombEv", mfunc_ptr_cast(&CCSBot::IsEscapingFromBomb) },
	//{ 0x0, "_ZN6CCSBot14RescueHostagesEv", mfunc_ptr_cast(&CCSBot::RescueHostages) },
	//{ 0x0, "_ZN6CCSBot9UseEntityEP11CBaseEntity", mfunc_ptr_cast(&CCSBot::UseEntity) },
	//{ 0x0, "_ZNK6CCSBot8IsBuyingEv", mfunc_ptr_cast(&CCSBot::IsBuying) },
	//{ 0x0, "_ZN6CCSBot5PanicEP11CBasePlayer", mfunc_ptr_cast(&CCSBot::Panic) },
	//{ 0x0, "_ZN6CCSBot6FollowEP11CBasePlayer", mfunc_ptr_cast(&CCSBot::Follow) },
	//{ 0x0, "_ZN6CCSBot17ContinueFollowingEv", mfunc_ptr_cast(&CCSBot::ContinueFollowing) },
	//{ 0x0, "_ZN6CCSBot13StopFollowingEv", mfunc_ptr_cast(&CCSBot::StopFollowing) },
	//{ 0x0, "_ZNK6CCSBot11IsFollowingEv", mfunc_ptr_cast(&CCSBot::IsFollowing) },
	//{ 0x0, "_ZN6CCSBot15GetFollowLeaderEv", mfunc_ptr_cast(&CCSBot::GetFollowLeader) },
	//{ 0x0, "_ZNK6CCSBot17GetFollowDurationEv", mfunc_ptr_cast(&CCSBot::GetFollowDuration) },
	//{ 0x0, "_ZNK6CCSBot13CanAutoFollowEv", mfunc_ptr_cast(&CCSBot::CanAutoFollow) },
	//{ 0x0, "_ZNK6CCSBot11IsNotMovingEv", mfunc_ptr_cast(&CCSBot::IsNotMoving) },
	//{ 0x0, "_ZN6CCSBot10AimAtEnemyEv", mfunc_ptr_cast(&CCSBot::AimAtEnemy) },
	//{ 0x0, "_ZN6CCSBot10StopAimingEv", mfunc_ptr_cast(&CCSBot::StopAiming) },
	//{ 0x0, "_ZNK6CCSBot15IsAimingAtEnemyEv", mfunc_ptr_cast(&CCSBot::IsAimingAtEnemy) },
	//{ 0x0, "_ZNK6CCSBot11IsSurprisedEv", mfunc_ptr_cast(&CCSBot::IsSurprised) },
	//{ 0x0, "_ZNK6CCSBot16GetSurpriseDelayEv", mfunc_ptr_cast(&CCSBot::GetSurpriseDelay) },
	//{ 0x0, "_ZN6CCSBot18ClearSurpriseDelayEv", mfunc_ptr_cast(&CCSBot::ClearSurpriseDelay) },
	//{ 0x0, "_ZNK6CCSBot17GetStateTimestampEv", mfunc_ptr_cast(&CCSBot::GetStateTimestamp) },
	//{ 0x0, "_ZNK6CCSBot15IsDoingScenarioEv", mfunc_ptr_cast(&CCSBot::IsDoingScenario) },
	//{ 0x0, "_ZNK6CCSBot12GetGameStateEv", mfunc_ptr_cast<GETGAMESTATE_CONST>(&CCSBot::GetGameState) },
	//{ 0x0, "_ZN6CCSBot12GetGameStateEv", mfunc_ptr_cast<GETGAMESTATE_NOTCONST>(&CCSBot::GetGameState) },
	//{ 0x0, "_ZN6CCSBot12IsAtBombsiteEv", mfunc_ptr_cast(&CCSBot::IsAtBombsite) },
	//{ 0x01D18740, "_ZN6CCSBot15GuardRandomZoneEf", mfunc_ptr_cast(&CCSBot::GuardRandomZone) },
	//{ 0x0, "_ZNK6CCSBot6IsBusyEv", mfunc_ptr_cast(&CCSBot::IsBusy) },
	//{ 0x0, "_ZN6CCSBot7SetTaskENS_8TaskTypeEP11CBaseEntity", mfunc_ptr_cast(&CCSBot::SetTask) },
	//{ 0x0, "_ZNK6CCSBot7GetTaskEv", mfunc_ptr_cast(&CCSBot::GetTask) },
	//{ 0x0, "_ZN6CCSBot13GetTaskEntityEv", mfunc_ptr_cast(&CCSBot::GetTaskEntity) },
	//{ 0x0, "_ZN6CCSBot14SetDispositionENS_15DispositionTypeE", mfunc_ptr_cast(&CCSBot::SetDisposition) },
	{ 0x01D18440, "_ZNK6CCSBot14GetDispositionEv", mfunc_ptr_cast(&CCSBot::GetDisposition) },
	//{ 0x0, "_ZN6CCSBot13IgnoreEnemiesEf", mfunc_ptr_cast(&CCSBot::IgnoreEnemies) },
	//{ 0x0, "_ZNK6CCSBot9GetMoraleEv", mfunc_ptr_cast(&CCSBot::GetMorale) },
	//{ 0x0, "_ZN6CCSBot14IncreaseMoraleEv", mfunc_ptr_cast(&CCSBot::IncreaseMorale) },
	{ 0x01D184B0, "_ZN6CCSBot14DecreaseMoraleEv", mfunc_ptr_cast(&CCSBot::DecreaseMorale) },
	//{ 0x0, "_ZNK6CCSBot12IsNoiseHeardEv", mfunc_ptr_cast(&CCSBot::IsNoiseHeard) },
	//{ 0x0, "_ZN6CCSBot22ShouldInvestigateNoiseEPf", mfunc_ptr_cast(&CCSBot::ShouldInvestigateNoise) },
	//{ 0x0, "_ZN6CCSBot16InvestigateNoiseEv", mfunc_ptr_cast(&CCSBot::InvestigateNoise) },
	//{ 0x0, "_ZNK6CCSBot16GetNoisePositionEv", mfunc_ptr_cast(&CCSBot::GetNoisePosition) },
	//{ 0x0, "_ZNK6CCSBot12GetNoiseAreaEv", mfunc_ptr_cast(&CCSBot::GetNoiseArea) },
	//{ 0x0, "_ZN6CCSBot11ForgetNoiseEv", mfunc_ptr_cast(&CCSBot::ForgetNoise) },
	//{ 0x0, "_ZNK6CCSBot19CanSeeNoisePositionEv", mfunc_ptr_cast(&CCSBot::CanSeeNoisePosition) },
	//{ 0x0, "_ZNK6CCSBot13GetNoiseRangeEv", mfunc_ptr_cast(&CCSBot::GetNoiseRange) },
	//{ 0x0, "_ZNK6CCSBot25CanHearNearbyEnemyGunfireEf", mfunc_ptr_cast(&CCSBot::CanHearNearbyEnemyGunfire) },
	//{ 0x0, "_ZNK6CCSBot16GetNoisePriorityEv", mfunc_ptr_cast(&CCSBot::GetNoisePriority) },
	//{ 0x0, "_ZN6CCSBot16SendRadioMessageE13GameEventType", mfunc_ptr_cast(&CCSBot::SendRadioMessage) },
	//{ 0x0, "_ZN6CCSBot10GetChatterEv", mfunc_ptr_cast(&CCSBot::GetChatter) },
	//{ 0x0, "_ZN6CCSBot20RespondToHelpRequestEP11CBasePlayerjf", mfunc_ptr_cast(&CCSBot::RespondToHelpRequest) },
	//{ 0x0, "_ZN6CCSBot18StartVoiceFeedbackEf", mfunc_ptr_cast(&CCSBot::StartVoiceFeedback) },
	//{ 0x0, "_ZNK6CCSBot12IsUsingVoiceEv", mfunc_ptr_cast(&CCSBot::IsUsingVoice) },
	{ 0x01D179D0, "_ZN6CCSBot8SetEnemyEP11CBasePlayer", mfunc_ptr_cast(&CCSBot::SetEnemy) },
	//{ 0x0, "_ZN6CCSBot8GetEnemyEv", mfunc_ptr_cast(&CCSBot::GetEnemy) },
	//{ 0x0, "_ZNK6CCSBot19GetNearbyEnemyCountEv", mfunc_ptr_cast(&CCSBot::GetNearbyEnemyCount) },
	//{ 0x0, "_ZNK6CCSBot13GetEnemyPlaceEv", mfunc_ptr_cast(&CCSBot::GetEnemyPlace) },
	//{ 0x0, "_ZNK6CCSBot12CanSeeBomberEv", mfunc_ptr_cast(&CCSBot::CanSeeBomber) },
	//{ 0x0, "_ZN6CCSBot9GetBomberEv", mfunc_ptr_cast(&CCSBot::GetBomber) },
	//{ 0x0, "_ZNK6CCSBot20GetNearbyFriendCountEv", mfunc_ptr_cast(&CCSBot::GetNearbyFriendCount) },
	//{ 0x0, "_ZNK6CCSBot23GetClosestVisibleFriendEv", mfunc_ptr_cast(&CCSBot::GetClosestVisibleFriend) },
	//{ 0x0, "_ZNK6CCSBot28GetClosestVisibleHumanFriendEv", mfunc_ptr_cast(&CCSBot::GetClosestVisibleHumanFriend) },
	//{ 0x01D181A0, "_ZNK6CCSBot13IsOutnumberedEv", mfunc_ptr_cast(&CCSBot::IsOutnumbered) },
	//{ 0x0, "_ZNK6CCSBot16OutnumberedCountEv", mfunc_ptr_cast(&CCSBot::OutnumberedCount) },
	//{ 0x0, "_ZNK6CCSBot17GetImportantEnemyEb", mfunc_ptr_cast(&CCSBot::GetImportantEnemy) },
	//{ 0x01D30830, "_ZN6CCSBot19UpdateReactionQueueEv", mfunc_ptr_cast(&CCSBot::UpdateReactionQueue) },
	{ 0x01D30980, "_ZN6CCSBot18GetRecognizedEnemyEv", mfunc_ptr_cast(&CCSBot::GetRecognizedEnemy) },
	//{ 0x0, "_ZN6CCSBot26IsRecognizedEnemyReloadingEv", mfunc_ptr_cast(&CCSBot::IsRecognizedEnemyReloading) },
	//{ 0x0, "_ZN6CCSBot34IsRecognizedEnemyProtectedByShieldEv", mfunc_ptr_cast(&CCSBot::IsRecognizedEnemyProtectedByShield) },
	//{ 0x0, "_ZN6CCSBot32GetRangeToNearestRecognizedEnemyEv", mfunc_ptr_cast(&CCSBot::GetRangeToNearestRecognizedEnemy) },
	//{ 0x0, "_ZNK6CCSBot11GetAttackerEv", mfunc_ptr_cast(&CCSBot::GetAttacker) },
	//{ 0x0, "_ZNK6CCSBot20GetTimeSinceAttackedEv", mfunc_ptr_cast(&CCSBot::GetTimeSinceAttacked) },
	//{ 0x0, "_ZNK6CCSBot25GetFirstSawEnemyTimestampEv", mfunc_ptr_cast(&CCSBot::GetFirstSawEnemyTimestamp) },
	//{ 0x0, "_ZNK6CCSBot24GetLastSawEnemyTimestampEv", mfunc_ptr_cast(&CCSBot::GetLastSawEnemyTimestamp) },
	//{ 0x0, "_ZNK6CCSBot24GetTimeSinceLastSawEnemyEv", mfunc_ptr_cast(&CCSBot::GetTimeSinceLastSawEnemy) },
	//{ 0x0, "_ZNK6CCSBot32GetTimeSinceAcquiredCurrentEnemyEv", mfunc_ptr_cast(&CCSBot::GetTimeSinceAcquiredCurrentEnemy) },
	//{ 0x0, "_ZNK6CCSBot26HasNotSeenEnemyForLongTimeEv", mfunc_ptr_cast(&CCSBot::HasNotSeenEnemyForLongTime) },
	//{ 0x0, "_ZNK6CCSBot25GetLastKnownEnemyPositionEv", mfunc_ptr_cast(&CCSBot::GetLastKnownEnemyPosition) },
	//{ 0x0, "_ZNK6CCSBot14IsEnemyVisibleEv", mfunc_ptr_cast(&CCSBot::IsEnemyVisible) },
	//{ 0x0, "_ZNK6CCSBot22GetEnemyDeathTimestampEv", mfunc_ptr_cast(&CCSBot::GetEnemyDeathTimestamp) },
	//{ 0x01D32440, "_ZN6CCSBot20IsFriendInLineOfFireEv", mfunc_ptr_cast(&CCSBot::IsFriendInLineOfFire) },
	//{ 0x0, "_ZNK6CCSBot19IsAwareOfEnemyDeathEv", mfunc_ptr_cast(&CCSBot::IsAwareOfEnemyDeath) },
	//{ 0x0, "_ZNK6CCSBot15GetLastVictimIDEv", mfunc_ptr_cast(&CCSBot::GetLastVictimID) },
	//{ 0x0, "_ZNK6CCSBot7HasPathEv", mfunc_ptr_cast(&CCSBot::HasPath) },
	//{ 0x0, "_ZN6CCSBot11DestroyPathEv", mfunc_ptr_cast(&CCSBot::DestroyPath) },
	//{ 0x0, "_ZNK6CCSBot8GetFeetZEv", mfunc_ptr_cast(&CCSBot::GetFeetZ) },
	//{ 0x0, "_ZN6CCSBot18UpdatePathMovementEb", mfunc_ptr_cast(&CCSBot::UpdatePathMovement) },
	//{ 0x0, "_ZN6CCSBot11AStarSearchEP8CNavAreaS1_", mfunc_ptr_cast(&CCSBot::AStarSearch) }, // NOXREF
	//{ 0x0, "_ZN6CCSBot11ComputePathEP8CNavAreaPK6Vector9RouteType", mfunc_ptr_cast(&CCSBot::ComputePath) },
	//{ 0x0, "_ZN6CCSBot13StayOnNavMeshEv", mfunc_ptr_cast(&CCSBot::StayOnNavMesh) },
	//{ 0x0, "_ZNK6CCSBot16GetLastKnownAreaEv", mfunc_ptr_cast(&CCSBot::GetLastKnownArea) },
	//{ 0x0, "_ZNK6CCSBot15GetPathEndpointEv", mfunc_ptr_cast(&CCSBot::GetPathEndpoint) },
	//{ 0x0, "_ZNK6CCSBot24GetPathDistanceRemainingEv", mfunc_ptr_cast(&CCSBot::GetPathDistanceRemaining) },
	//{ 0x0, "_ZN6CCSBot17ResetStuckMonitorEv", mfunc_ptr_cast(&CCSBot::ResetStuckMonitor) },
	//{ 0x0, "_ZNK6CCSBot13IsAreaVisibleEPK8CNavArea", mfunc_ptr_cast(&CCSBot::IsAreaVisible) }, // NOXREF
	//{ 0x0, "_ZNK6CCSBot15GetPathPositionEi", mfunc_ptr_cast(&CCSBot::GetPathPosition) }, // NOXREF
	//{ 0x0, "_ZN6CCSBot30GetSimpleGroundHeightWithFloorEPK6VectorPfPS0_", mfunc_ptr_cast(&CCSBot::GetSimpleGroundHeightWithFloor) },
	//{ 0x01D26060, "_ZNK6CCSBot8GetPlaceEv", mfunc_ptr_cast(&CCSBot::GetPlace) },
	//{ 0x0, "_ZNK6CCSBot13IsUsingLadderEv", mfunc_ptr_cast(&CCSBot::IsUsingLadder) },
	//{ 0x0, "_ZN6CCSBot12GetOffLadderEv", mfunc_ptr_cast(&CCSBot::GetOffLadder) },
	//{ 0x0, "_ZN6CCSBot13SetGoalEntityEP11CBaseEntity", mfunc_ptr_cast(&CCSBot::SetGoalEntity) },
	//{ 0x0, "_ZN6CCSBot13GetGoalEntityEv", mfunc_ptr_cast(&CCSBot::GetGoalEntity) },
	//{ 0x0, "_ZNK6CCSBot10IsNearJumpEv", mfunc_ptr_cast(&CCSBot::IsNearJump) },
	//{ 0x0, "_ZNK6CCSBot24GetApproximateFallDamageEf", mfunc_ptr_cast(&CCSBot::GetApproximateFallDamage) },
	//{ 0x0, "_ZN6CCSBot8ForceRunEf", mfunc_ptr_cast(&CCSBot::ForceRun) },
	//{ 0x0, "_ZN6CCSBot6WiggleEv", mfunc_ptr_cast(&CCSBot::Wiggle) },
	//{ 0x0, "_ZNK6CCSBot16IsFriendInTheWayEPK6Vector", mfunc_ptr_cast(&CCSBot::IsFriendInTheWay) },
	//{ 0x0, "_ZN6CCSBot22FeelerReflexAdjustmentEP6Vector", mfunc_ptr_cast(&CCSBot::FeelerReflexAdjustment) },
	//{ 0x0, "_ZN6CCSBot13SetLookAnglesEff", mfunc_ptr_cast(&CCSBot::SetLookAngles) },
	//2@@{ 0x01D2EDD0, "_ZN6CCSBot16UpdateLookAnglesEv", mfunc_ptr_cast(&CCSBot::UpdateLookAngles) },	// Using REFS
	//{ 0x0, "_ZN6CCSBot16UpdateLookAroundEb", mfunc_ptr_cast(&CCSBot::UpdateLookAround) },
	//{ 0x0, "_ZN6CCSBot17InhibitLookAroundEf", mfunc_ptr_cast(&CCSBot::InhibitLookAround) },
	//{ 0x0, "_ZN6CCSBot15SetForwardAngleEf", mfunc_ptr_cast(&CCSBot::SetForwardAngle) }, // NOXREF
	//{ 0x0, "_ZN6CCSBot17SetLookAheadAngleEf", mfunc_ptr_cast(&CCSBot::SetLookAheadAngle) }, // NOXREF
	{ 0x01D2F7F0, "_ZN6CCSBot9SetLookAtEPKcPK6Vector12PriorityTypefbf", mfunc_ptr_cast(&CCSBot::SetLookAt) },
	//{ 0x0, "_ZN6CCSBot11ClearLookAtEv", mfunc_ptr_cast(&CCSBot::ClearLookAt) },
	//{ 0x0, "_ZNK6CCSBot15IsLookingAtSpotE12PriorityType", mfunc_ptr_cast(&CCSBot::IsLookingAtSpot) },
	//{ 0x0, "_ZNK6CCSBot12IsViewMovingEf", mfunc_ptr_cast(&CCSBot::IsViewMoving) },
	//{ 0x0, "_ZNK6CCSBot14GetEyePositionEv", mfunc_ptr_cast(&CCSBot::GetEyePosition) },
	//{ 0x0, "_ZN6CCSBot23ComputeWeaponSightRangeEv", mfunc_ptr_cast(&CCSBot::ComputeWeaponSightRange) },
	//{ 0x01D26890, "_ZN6CCSBot21ComputeApproachPointsEv", mfunc_ptr_cast(&CCSBot::ComputeApproachPoints) },
	//{ 0x0, "_ZN6CCSBot20UpdateApproachPointsEv", mfunc_ptr_cast(&CCSBot::UpdateApproachPoints) },
	//{ 0x0, "_ZN6CCSBot19ClearApproachPointsEv", mfunc_ptr_cast(&CCSBot::ClearApproachPoints) },
	//{ 0x01D269D0, "_ZN6CCSBot18DrawApproachPointsEv", mfunc_ptr_cast(&CCSBot::DrawApproachPoints) },
	//{ 0x0, "_ZNK6CCSBot27GetHidingSpotCheckTimestampEP10HidingSpot", mfunc_ptr_cast(&CCSBot::GetHidingSpotCheckTimestamp) },
	//{ 0x0, "_ZN6CCSBot27SetHidingSpotCheckTimestampEP10HidingSpot", mfunc_ptr_cast(&CCSBot::SetHidingSpotCheckTimestamp) },
	//{ 0x0, "_ZN6CCSBot15EquipBestWeaponEb", mfunc_ptr_cast(&CCSBot::EquipBestWeapon) },
	//{ 0x0, "_ZN6CCSBot11EquipPistolEv", mfunc_ptr_cast(&CCSBot::EquipPistol) },
	//{ 0x0, "_ZN6CCSBot10EquipKnifeEv", mfunc_ptr_cast(&CCSBot::EquipKnife) },
	//{ 0x0, "_ZN6CCSBot12EquipGrenadeEb", mfunc_ptr_cast(&CCSBot::EquipGrenade) },
	{ 0x01D31A00, "_ZNK6CCSBot12IsUsingKnifeEv", mfunc_ptr_cast(&CCSBot::IsUsingKnife) },
	{ 0x01D31A20, "_ZNK6CCSBot13IsUsingPistolEv", mfunc_ptr_cast(&CCSBot::IsUsingPistol) },
	{ 0x01D31A60, "_ZNK6CCSBot14IsUsingGrenadeEv", mfunc_ptr_cast(&CCSBot::IsUsingGrenade) },
	{ 0x01D313F0, "_ZNK6CCSBot18IsUsingSniperRifleEv", mfunc_ptr_cast(&CCSBot::IsUsingSniperRifle) },
	{ 0x01D313A0, "_ZNK6CCSBot10IsUsingAWPEv", mfunc_ptr_cast(&CCSBot::IsUsingAWP) },
	//{ 0x0, "_ZNK6CCSBot8IsSniperEv", mfunc_ptr_cast(&CCSBot::IsSniper) },
	//{ 0x0, "_ZNK6CCSBot9IsSnipingEv", mfunc_ptr_cast(&CCSBot::IsSniping) },
	{ 0x01D314D0, "_ZNK6CCSBot14IsUsingShotgunEv", mfunc_ptr_cast(&CCSBot::IsUsingShotgun) },
	{ 0x01D31500, "_ZNK6CCSBot17IsUsingMachinegunEv", mfunc_ptr_cast(&CCSBot::IsUsingMachinegun) },
	{ 0x01D31AB0, "_ZN6CCSBot12ThrowGrenadeEPK6Vector", mfunc_ptr_cast(&CCSBot::ThrowGrenade) },
	//{ 0x0, "_ZNK6CCSBot17IsThrowingGrenadeEv", mfunc_ptr_cast(&CCSBot::IsThrowingGrenade) },
	//{ 0x0, "_ZNK6CCSBot10HasGrenadeEv", mfunc_ptr_cast(&CCSBot::HasGrenade) },
	//{ 0x0, "_ZNK6CCSBot28DoesActiveWeaponHaveSilencerEv", mfunc_ptr_cast(&CCSBot::DoesActiveWeaponHaveSilencer) },
	//{ 0x0, "_ZNK6CCSBot16IsUsingHEGrenadeEv", mfunc_ptr_cast(&CCSBot::IsUsingHEGrenade) },
	//{ 0x0, "_ZN6CCSBot14StartRapidFireEv", mfunc_ptr_cast(&CCSBot::StartRapidFire) },
	//{ 0x0, "_ZN6CCSBot13StopRapidFireEv", mfunc_ptr_cast(&CCSBot::StopRapidFire) },
	//{ 0x0, "_ZNK6CCSBot13IsRapidFiringEv", mfunc_ptr_cast(&CCSBot::IsRapidFiring) },
	//{ 0x0, "_ZNK6CCSBot12GetZoomLevelEv", mfunc_ptr_cast(&CCSBot::GetZoomLevel) },
	//{ 0x0, "_ZN6CCSBot10AdjustZoomEf", mfunc_ptr_cast(&CCSBot::AdjustZoom) },
	//{ 0x0, "_ZNK6CCSBot20IsPrimaryWeaponEmptyEv", mfunc_ptr_cast(&CCSBot::IsPrimaryWeaponEmpty) },
	//{ 0x0, "_ZNK6CCSBot13IsPistolEmptyEv", mfunc_ptr_cast(&CCSBot::IsPistolEmpty) },
	//{ 0x0, "_ZNK6CCSBot21GetHostageEscortCountEv", mfunc_ptr_cast(&CCSBot::GetHostageEscortCount) },
	//{ 0x0, "_ZN6CCSBot26IncreaseHostageEscortCountEv", mfunc_ptr_cast(&CCSBot::IncreaseHostageEscortCount) },
	//{ 0x0, "_ZNK6CCSBot33GetRangeToFarthestEscortedHostageEv", mfunc_ptr_cast(&CCSBot::GetRangeToFarthestEscortedHostage) },
	//{ 0x0, "_ZN6CCSBot27ResetWaitForHostagePatienceEv", mfunc_ptr_cast(&CCSBot::ResetWaitForHostagePatience) },
	//{ 0x01D20AE0, "_ZN6CCSBot11ResetValuesEv", mfunc_ptr_cast(&CCSBot::ResetValues) },
	//{ 0x01D17950, "_ZN6CCSBot13BotDeathThinkEv", mfunc_ptr_cast(&CCSBot::BotDeathThink) },	// PURE
	//{ 0x0, "_ZN6CCSBot16FindNearbyPlayerEv", mfunc_ptr_cast(&CCSBot::FindNearbyPlayer) },
	{ 0x01D186E0, "_ZN6CCSBot14AdjustSafeTimeEv", mfunc_ptr_cast(&CCSBot::AdjustSafeTime) },
	//{ 0x01D2BD80, "_ZN6CCSBot8SetStateEP8BotState", mfunc_ptr_cast(&CCSBot::SetState) },
	//{ 0x0, "_ZN6CCSBot19MoveTowardsPositionEPK6Vector", mfunc_ptr_cast(&CCSBot::MoveTowardsPosition) },
	//{ 0x0, "_ZN6CCSBot20MoveAwayFromPositionEPK6Vector", mfunc_ptr_cast(&CCSBot::MoveAwayFromPosition) },
	//{ 0x0, "_ZN6CCSBot22StrafeAwayFromPositionEPK6Vector", mfunc_ptr_cast(&CCSBot::StrafeAwayFromPosition) },
	//{ 0x01D25C50, "_ZN6CCSBot10StuckCheckEv", mfunc_ptr_cast(&CCSBot::StuckCheck) },
	//{ 0x0, "_ZN6CCSBot16BuildTrivialPathEPK6Vector", mfunc_ptr_cast(&CCSBot::BuildTrivialPath) },
	//{ 0x0, "_ZN6CCSBot20ComputePathPositionsEv", mfunc_ptr_cast(&CCSBot::ComputePathPositions) },
	//{ 0x0, "_ZN6CCSBot19SetupLadderMovementEv", mfunc_ptr_cast(&CCSBot::SetupLadderMovement) },
	//{ 0x0, "_ZN6CCSBot12SetPathIndexEi", mfunc_ptr_cast(&CCSBot::SetPathIndex) },
	//{ 0x0, "_ZN6CCSBot8DrawPathEv", mfunc_ptr_cast(&CCSBot::DrawPath) },
	//{ 0x0, "_ZNK6CCSBot21FindOurPositionOnPathEP6Vectorb", mfunc_ptr_cast(&CCSBot::FindOurPositionOnPath) },
	//{ 0x0, "_ZN6CCSBot13FindPathPointEfP6VectorPi", mfunc_ptr_cast(&CCSBot::FindPathPoint) },
	//{ 0x0, "_ZNK6CCSBot22FindClosestPointOnPathEPK6VectoriiPS0_", mfunc_ptr_cast(&CCSBot::FindClosestPointOnPath) },
	//{ 0x0, "_ZNK6CCSBot26IsStraightLinePathWalkableEPK6Vector", mfunc_ptr_cast(&CCSBot::IsStraightLinePathWalkable) },
	//{ 0x0, "_ZN6CCSBot17DiscontinuityJumpEfbb", mfunc_ptr_cast(&CCSBot::DiscontinuityJump) },
	//{ 0x0, "_ZN6CCSBot20UpdateLadderMovementEv", mfunc_ptr_cast(&CCSBot::UpdateLadderMovement) },
	//{ 0x0, "_ZN6CCSBot21ComputeLadderEndpointEb", mfunc_ptr_cast(&CCSBot::ComputeLadderEndpoint) },
	//{ 0x0, "_ZN6CCSBot24UpdateHostageEscortCountEv", mfunc_ptr_cast(&CCSBot::UpdateHostageEscortCount) },
	//{ 0x0, "_ZN6CCSBot17UpdateLookAtNoiseEv", mfunc_ptr_cast(&CCSBot::UpdateLookAtNoise) },
	{ 0x01D2F760, "_ZN6CCSBot12UpdateLookAtEv", mfunc_ptr_cast(&CCSBot::UpdateLookAt) },
	//{ 0x0, "_ZN6CCSBot22UpdatePeripheralVisionEv", mfunc_ptr_cast(&CCSBot::UpdatePeripheralVision) },
	//{ 0x0, "_ZNK6CCSBot15BendLineOfSightEPK6VectorS2_PS0_", mfunc_ptr_cast(&CCSBot::BendLineOfSight) },
	//{ 0x0, "_ZN6CCSBot28FindApproachPointNearestPathEP6Vector", mfunc_ptr_cast(&CCSBot::FindApproachPointNearestPath) },
	//{ 0x0, "_ZN6CCSBot25FindGrenadeTossPathTargetEP6Vector", mfunc_ptr_cast(&CCSBot::FindGrenadeTossPathTarget) },
	{ 0x01D31030, "_ZN6CCSBot12SetAimOffsetEf", mfunc_ptr_cast(&CCSBot::SetAimOffset) },
	{ 0x01D311E0, "_ZN6CCSBot15UpdateAimOffsetEv", mfunc_ptr_cast(&CCSBot::UpdateAimOffset) },
	//{ 0x0, "_ZN6CCSBot7DoEquipEP17CBasePlayerWeapon", mfunc_ptr_cast(&CCSBot::DoEquip) },
	//{ 0x0, "_ZN6CCSBot11ReloadCheckEv", mfunc_ptr_cast(&CCSBot::ReloadCheck) },
	//{ 0x0, "_ZN6CCSBot13SilencerCheckEv", mfunc_ptr_cast(&CCSBot::SilencerCheck) },
	//{ 0x01D302D0, "_ZN6CCSBot23FindMostDangerousThreatEv", mfunc_ptr_cast(&CCSBot::FindMostDangerousThreat) },
	//{ 0x0, "_ZN6CCSBot22RespondToRadioCommandsEv", mfunc_ptr_cast(&CCSBot::RespondToRadioCommands) },
	//{ 0x0, "_ZNK6CCSBot14IsRadioCommandE13GameEventType", mfunc_ptr_cast(&CCSBot::IsRadioCommand) },
	{ 0x01D2BA00, "_ZN6CCSBot16EndVoiceFeedbackEb", mfunc_ptr_cast(&CCSBot::EndVoiceFeedback) },
	//{ 0x0, "_ZN6CCSBot7AddNodeEPK6VectorS2_10NavDirTypeP8CNavNode", mfunc_ptr_cast(&CCSBot::AddNode) },
	//{ 0x0, "_ZN6CCSBot17StartLearnProcessEv", mfunc_ptr_cast(&CCSBot::StartLearnProcess) },
	//{ 0x01D21EF0, "_ZN6CCSBot18UpdateLearnProcessEv", mfunc_ptr_cast(&CCSBot::UpdateLearnProcess) },
	//{ 0x0, "_ZN6CCSBot9LearnStepEv", mfunc_ptr_cast(&CCSBot::LearnStep) },
	{ 0x01D21FE0, "_ZN6CCSBot24StartAnalyzeAlphaProcessEv", mfunc_ptr_cast(&CCSBot::StartAnalyzeAlphaProcess) },
	//{ 0x01D22080, "_ZN6CCSBot25UpdateAnalyzeAlphaProcessEv", mfunc_ptr_cast(&CCSBot::UpdateAnalyzeAlphaProcess) },
	//{ 0x0, "_ZN6CCSBot16AnalyzeAlphaStepEv", mfunc_ptr_cast(&CCSBot::AnalyzeAlphaStep) },
	//{ 0x0, "_ZN6CCSBot23StartAnalyzeBetaProcessEv", mfunc_ptr_cast(&CCSBot::StartAnalyzeBetaProcess) },
	//{ 0x01D22200, "_ZN6CCSBot24UpdateAnalyzeBetaProcessEv", mfunc_ptr_cast(&CCSBot::UpdateAnalyzeBetaProcess) },
	//{ 0x0, "_ZN6CCSBot15AnalyzeBetaStepEv", mfunc_ptr_cast(&CCSBot::AnalyzeBetaStep) },
	//{ 0x0, "_ZN6CCSBot16StartSaveProcessEv", mfunc_ptr_cast(&CCSBot::StartSaveProcess) },
	//{ 0x01D22340, "_ZN6CCSBot17UpdateSaveProcessEv", mfunc_ptr_cast(&CCSBot::UpdateSaveProcess) },
	{ 0x01D22450, "_ZN6CCSBot18StartNormalProcessEv", mfunc_ptr_cast(&CCSBot::StartNormalProcess) },
	//{ 0x0, "_ZN6CCSBot8BotTouchEP11CBaseEntity", mfunc_ptr_cast(&CCSBot::BotTouch) },
//CSGameState
	//{ 0x0, "", mfunc_ptr_cast(&CSGameState::CSGameState) },
	//{ 0x01D32730, "_ZN11CSGameState5ResetEv", mfunc_ptr_cast(&CSGameState::Reset) },
	//{ 0x0, "_ZN11CSGameState7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CSGameState::OnEvent) },
	//{ 0x0, "_ZNK11CSGameState11IsRoundOverEv", mfunc_ptr_cast(&CSGameState::IsRoundOver) },
	//{ 0x0, "_ZNK11CSGameState12IsBombMovingEv", mfunc_ptr_cast(&CSGameState::IsBombMoving) },
	//{ 0x0, "_ZNK11CSGameState11IsBombLooseEv", mfunc_ptr_cast(&CSGameState::IsBombLoose) },
	//{ 0x0, "_ZNK11CSGameState13IsBombPlantedEv", mfunc_ptr_cast(&CSGameState::IsBombPlanted) },
	//{ 0x0, "_ZNK11CSGameState13IsBombDefusedEv", mfunc_ptr_cast(&CSGameState::IsBombDefused) },	// NOXREF
	//{ 0x0, "_ZNK11CSGameState14IsBombExplodedEv", mfunc_ptr_cast(&CSGameState::IsBombExploded) },	// NOXREF
	//{ 0x0, "_ZN11CSGameState15UpdateLooseBombEPK6Vector", mfunc_ptr_cast(&CSGameState::UpdateLooseBomb) },
	//{ 0x0, "_ZNK11CSGameState25TimeSinceLastSawLooseBombEv", mfunc_ptr_cast(&CSGameState::TimeSinceLastSawLooseBomb) },
	//{ 0x0, "_ZNK11CSGameState24IsLooseBombLocationKnownEv", mfunc_ptr_cast(&CSGameState::IsLooseBombLocationKnown) },
	//{ 0x0, "_ZN11CSGameState12UpdateBomberEPK6Vector", mfunc_ptr_cast(&CSGameState::UpdateBomber) },
	//{ 0x0, "_ZNK11CSGameState22TimeSinceLastSawBomberEv", mfunc_ptr_cast(&CSGameState::TimeSinceLastSawBomber) },
	//{ 0x0, "_ZN11CSGameState17UpdatePlantedBombEPK6Vector", mfunc_ptr_cast(&CSGameState::UpdatePlantedBomb) },
	//{ 0x0, "_ZNK11CSGameState26IsPlantedBombLocationKnownEv", mfunc_ptr_cast(&CSGameState::IsPlantedBombLocationKnown) },
	//{ 0x0, "_ZN11CSGameState21MarkBombsiteAsPlantedEi", mfunc_ptr_cast(&CSGameState::MarkBombsiteAsPlanted) },
	//{ 0x0, "_ZNK11CSGameState18GetPlantedBombsiteEv", mfunc_ptr_cast(&CSGameState::GetPlantedBombsite) },
	//{ 0x0, "_ZNK11CSGameState19IsAtPlantedBombsiteEv", mfunc_ptr_cast(&CSGameState::IsAtPlantedBombsite) },
	//{ 0x0, "_ZN11CSGameState23GetNextBombsiteToSearchEv", mfunc_ptr_cast(&CSGameState::GetNextBombsiteToSearch) },
	//{ 0x0, "_ZNK11CSGameState15IsBombsiteClearEi", mfunc_ptr_cast(&CSGameState::IsBombsiteClear) },
	//{ 0x0, "_ZN11CSGameState13ClearBombsiteEi", mfunc_ptr_cast(&CSGameState::ClearBombsite) },
	//{ 0x0, "_ZNK11CSGameState15GetBombPositionEv", mfunc_ptr_cast(&CSGameState::GetBombPosition) },
	//{ 0x0, "_ZNK11CSGameState21GetNearestFreeHostageEP6Vector", mfunc_ptr_cast(&CSGameState::GetNearestFreeHostage) },
	//{ 0x0, "_ZNK11CSGameState28GetRandomFreeHostagePositionEv", mfunc_ptr_cast(&CSGameState::GetRandomFreeHostagePosition) },
	//{ 0x0, "_ZNK11CSGameState26AreAllHostagesBeingRescuedEv", mfunc_ptr_cast(&CSGameState::AreAllHostagesBeingRescued) },
	//{ 0x0, "_ZNK11CSGameState18AreAllHostagesGoneEv", mfunc_ptr_cast(&CSGameState::AreAllHostagesGone) },
	//{ 0x0, "_ZN11CSGameState15AllHostagesGoneEv", mfunc_ptr_cast(&CSGameState::AllHostagesGone) },
	//{ 0x0, "_ZNK11CSGameState25HaveSomeHostagesBeenTakenEv", mfunc_ptr_cast(&CSGameState::HaveSomeHostagesBeenTaken) },
	//{ 0x0, "_ZN11CSGameState15HostageWasTakenEv", mfunc_ptr_cast(&CSGameState::HostageWasTaken) },
	//{ 0x0, "_ZNK11CSGameState28GetNearestVisibleFreeHostageEv", mfunc_ptr_cast(&CSGameState::GetNearestVisibleFreeHostage) },
	//{ 0x0, "_ZN11CSGameState24ValidateHostagePositionsEv", mfunc_ptr_cast(&CSGameState::ValidateHostagePositions) },
	//{ 0x0, "_ZN11CSGameState12SetBombStateENS_9BombStateE", mfunc_ptr_cast(&CSGameState::SetBombState) },
	//{ 0x0, "_ZNK11CSGameState12GetBombStateEv", mfunc_ptr_cast(&CSGameState::GetBombState) },	// NOXREF
	//{ 0x0, "_ZNK11CSGameState17GetNearestHostageEv", mfunc_ptr_cast(&CSGameState::GetNearestHostage) },	// NOXREF
	//{ 0x0, "_ZN11CSGameState21InitializeHostageInfoEv", mfunc_ptr_cast(&CSGameState::InitializeHostageInfo) },

	//{ 0x0, "_Z17GetBotFollowCountP11CBasePlayer", (size_t)&GetBotFollowCount },
	//{ 0x01D187B0, "_Z21FindNearbyRetreatSpotP6CCSBotf", (size_t)&FindNearbyRetreatSpot },

	//{ 0x0, "", (size_t)&drawProgressMeter },	// NOXREF
	//{ 0x0, "", (size_t)&startProgressMeter },	// NOXREF
	//{ 0x0, "", (size_t)&hideProgressMeter },	// NOXREF

#endif // CS_Bot_Region

#ifndef CS_BotState_Region

//BotState
	//virtual func
	//{ 0x0, "_ZN8BotState7OnEnterEP6CCSBot", mfunc_ptr_cast(&BotState::OnEnter) },			// PURE
	//{ 0x0, "_ZN8BotState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&BotState::OnUpdate) },	// PURE
	//{ 0x0, "_ZN8BotState6OnExitEP6CCSBot", mfunc_ptr_cast(&BotState::OnExit) },			// PURE
	//{ 0x0, "_ZNK8BotState7GetNameEv", mfunc_ptr_cast(&BotState::GetName) },		// NOXREF
//IdleState
	//virtual func
	//{ 0x0, "_ZN9IdleState7OnEnterEP6CCSBot", mfunc_ptr_cast(&IdleState::OnEnter) },
	//{ 0x0, "_ZN9IdleState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&IdleState::OnUpdate) },
	//{ 0x0, "_ZNK9IdleState7GetNameEv", mfunc_ptr_cast(&IdleState::GetName) },
//HuntState
	//virtual func
	//{ 0x0, "_ZN9HuntState7OnEnterEP6CCSBot", mfunc_ptr_cast(&HuntState::OnEnter) },
	//{ 0x0, "_ZN9HuntState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&HuntState::OnUpdate) },
	//{ 0x0, "_ZN9HuntState6OnExitEP6CCSBot", mfunc_ptr_cast(&HuntState::OnExit) },
	//{ 0x0, "_ZNK9HuntState7GetNameEv", mfunc_ptr_cast(&HuntState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN9HuntState13ClearHuntAreaEv", mfunc_ptr_cast(&HuntState::ClearHuntArea) },		// NOXREF
//AttackState
	//virtual func
	//{ 0x01D10960, "_ZN11AttackState7OnEnterEP6CCSBot", mfunc_ptr_cast(&AttackState::OnEnter) },
	//{ 0x0, "_ZN11AttackState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&AttackState::OnUpdate) },
	//{ 0x0, "_ZN11AttackState6OnExitEP6CCSBot", mfunc_ptr_cast(&AttackState::OnExit) },
	//{ 0x0, "_ZNK11AttackState7GetNameEv", mfunc_ptr_cast(&AttackState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN11AttackState16SetCrouchAndHoldEb", mfunc_ptr_cast(&AttackState::SetCrouchAndHold) },		// NOXREF
	//{ 0x0, "_ZN11AttackState13StopAttackingEP6CCSBot", mfunc_ptr_cast(&AttackState::StopAttacking) },
//InvestigateNoiseState
	//virtual func
	//{ 0x0, "_ZN21InvestigateNoiseState7OnEnterEP6CCSBot", mfunc_ptr_cast(&InvestigateNoiseState::OnEnter) },
	//{ 0x0, "_ZN21InvestigateNoiseState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&InvestigateNoiseState::OnUpdate) },
	//{ 0x0, "_ZN21InvestigateNoiseState6OnExitEP6CCSBot", mfunc_ptr_cast(&InvestigateNoiseState::OnExit) },
	//{ 0x0, "_ZNK21InvestigateNoiseState7GetNameEv", mfunc_ptr_cast(&InvestigateNoiseState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN21InvestigateNoiseState18AttendCurrentNoiseEP6CCSBot", mfunc_ptr_cast(&InvestigateNoiseState::AttendCurrentNoise) },
//BuyState
	//virtual func
	//{ 0x0, "_ZN8BuyState7OnEnterEP6CCSBot", mfunc_ptr_cast(&BuyState::OnEnter) },
	//{ 0x0, "_ZN8BuyState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&BuyState::OnUpdate) },
	//{ 0x0, "_ZN8BuyState6OnExitEP6CCSBot", mfunc_ptr_cast(&BuyState::OnExit) },
	//{ 0x0, "_ZNK8BuyState7GetNameEv", mfunc_ptr_cast(&BuyState::GetName) },
//MoveToState
	//virtual func
	//{ 0x0, "_ZN11MoveToState7OnEnterEP6CCSBot", mfunc_ptr_cast(&MoveToState::OnEnter) },
	//{ 0x0, "_ZN11MoveToState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&MoveToState::OnUpdate) },
	//{ 0x0, "_ZN11MoveToState6OnExitEP6CCSBot", mfunc_ptr_cast(&MoveToState::OnExit) },
	//{ 0x0, "_ZNK11MoveToState7GetNameEv", mfunc_ptr_cast(&MoveToState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN11MoveToState15SetGoalPositionEPK6Vector", mfunc_ptr_cast(&MoveToState::SetGoalPosition) },		// NOXREF
	//{ 0x0, "_ZN11MoveToState12SetRouteTypeE9RouteType", mfunc_ptr_cast(&MoveToState::SetRouteType) },		// NOXREF
//FetchBombState
	//virtual func
	//{ 0x0, "_ZN14FetchBombState7OnEnterEP6CCSBot", mfunc_ptr_cast(&FetchBombState::OnEnter) },
	//{ 0x0, "_ZN14FetchBombState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&FetchBombState::OnUpdate) },
	//{ 0x0, "_ZNK14FetchBombState7GetNameEv", mfunc_ptr_cast(&FetchBombState::GetName) },
//PlantBombState
	//virtual func
	//{ 0x0, "_ZN14PlantBombState7OnEnterEP6CCSBot", mfunc_ptr_cast(&PlantBombState::OnEnter) },
	//{ 0x0, "_ZN14PlantBombState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&PlantBombState::OnUpdate) },
	//{ 0x0, "_ZN14PlantBombState6OnExitEP6CCSBot", mfunc_ptr_cast(&PlantBombState::OnExit) },
	//{ 0x0, "_ZNK14PlantBombState7GetNameEv", mfunc_ptr_cast(&PlantBombState::GetName) },
//DefuseBombState
	//virtual func
	//{ 0x0, "_ZN15DefuseBombState7OnEnterEP6CCSBot", mfunc_ptr_cast(&DefuseBombState::OnEnter) },
	//{ 0x0, "_ZN15DefuseBombState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&DefuseBombState::OnUpdate) },
	//{ 0x0, "_ZN15DefuseBombState6OnExitEP6CCSBot", mfunc_ptr_cast(&DefuseBombState::OnExit) },
	//{ 0x0, "_ZNK15DefuseBombState7GetNameEv", mfunc_ptr_cast(&DefuseBombState::GetName) },
//HideState
	//virtual func
	//{ 0x0, "_ZN9HideState7OnEnterEP6CCSBot", mfunc_ptr_cast(&HideState::OnEnter) },
	//{ 0x0, "_ZN9HideState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&HideState::OnUpdate) },
	//{ 0x0, "_ZN9HideState6OnExitEP6CCSBot", mfunc_ptr_cast(&HideState::OnExit) },
	//{ 0x0, "_ZNK9HideState7GetNameEv", mfunc_ptr_cast(&HideState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN9HideState13SetHidingSpotEPK6Vector", mfunc_ptr_cast(&HideState::SetHidingSpot) },		// NOXREF
	//{ 0x0, "_ZNK9HideState13GetHidingSpotEv", mfunc_ptr_cast(&HideState::GetHidingSpot) },		// NOXREF
	//{ 0x0, "_ZN9HideState13SetSearchAreaEP8CNavArea", mfunc_ptr_cast(&HideState::SetSearchArea) },		// NOXREF
	//{ 0x0, "_ZN9HideState14SetSearchRangeEf", mfunc_ptr_cast(&HideState::SetSearchRange) },		// NOXREF
	//{ 0x0, "_ZN9HideState11SetDurationEf", mfunc_ptr_cast(&HideState::SetDuration) },		// NOXREF
	//{ 0x0, "_ZN9HideState15SetHoldPositionEb", mfunc_ptr_cast(&HideState::SetHoldPosition) },		// NOXREF
	//{ 0x0, "_ZNK9HideState8IsAtSpotEv", mfunc_ptr_cast(&HideState::IsAtSpot) },		// NOXREF
//EscapeFromBombState
	//virtual func
	//{ 0x0, "_ZN19EscapeFromBombState7OnEnterEP6CCSBot", mfunc_ptr_cast(&EscapeFromBombState::OnEnter) },
	//{ 0x0, "_ZN19EscapeFromBombState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&EscapeFromBombState::OnUpdate) },
	//{ 0x0, "_ZN19EscapeFromBombState6OnExitEP6CCSBot", mfunc_ptr_cast(&EscapeFromBombState::OnExit) },
	//{ 0x0, "_ZNK19EscapeFromBombState7GetNameEv", mfunc_ptr_cast(&EscapeFromBombState::GetName) },
//FollowState
	//virtual func
	//{ 0x0, "_ZN11FollowState7OnEnterEP6CCSBot", mfunc_ptr_cast(&FollowState::OnEnter) },
	//{ 0x0, "_ZN11FollowState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&FollowState::OnUpdate) },
	//{ 0x0, "_ZN11FollowState6OnExitEP6CCSBot", mfunc_ptr_cast(&FollowState::OnExit) },
	//{ 0x0, "_ZNK11FollowState7GetNameEv", mfunc_ptr_cast(&FollowState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN11FollowState9SetLeaderEP11CBasePlayer", mfunc_ptr_cast(&FollowState::SetLeader) },		// NOXREF
	//{ 0x0, "_ZN11FollowState24ComputeLeaderMotionStateEf", mfunc_ptr_cast(&FollowState::ComputeLeaderMotionState) },
//UseEntityState
	//virtual func
	//{ 0x0, "_ZN14UseEntityState7OnEnterEP6CCSBot", mfunc_ptr_cast(&UseEntityState::OnEnter) },
	//{ 0x0, "_ZN14UseEntityState8OnUpdateEP6CCSBot", mfunc_ptr_cast(&UseEntityState::OnUpdate) },
	//{ 0x0, "_ZN14UseEntityState6OnExitEP6CCSBot", mfunc_ptr_cast(&UseEntityState::OnExit) },
	//{ 0x0, "_ZNK14UseEntityState7GetNameEv", mfunc_ptr_cast(&UseEntityState::GetName) },
	//non-virtual func
	//{ 0x0, "_ZN14UseEntityState9SetEntityEP11CBaseEntity", mfunc_ptr_cast(&UseEntityState::SetEntity) },		// NOXREF

#ifdef _WIN32
	//{ 0x01D12F90, "_ZN8PathCostclEP8CNavAreaS1_PK10CNavLadder", mfunc_ptr_cast(&FollowTargetCollector::operator()) },
#endif // _WIN32

#endif // CS_BotState_Region

#ifndef Bot_Region

//ActiveGrenade
	//virtual func
	//{ 0x0, "_ZN13ActiveGrenadeC2EiP8CGrenade", mfunc_ptr_cast(&ActiveGrenade::ActiveGrenade) },
	{ 0x01D34080, "_ZN13ActiveGrenade12OnEntityGoneEv", mfunc_ptr_cast(&ActiveGrenade::OnEntityGone) },
	{ 0x01D340A0, "_ZNK13ActiveGrenade7IsValidEv", mfunc_ptr_cast(&ActiveGrenade::IsValid) },
	//{ 0x0, "_ZNK13ActiveGrenade8IsEntityEP8CGrenade", mfunc_ptr_cast(&ActiveGrenade::IsEntity) },	// NOXREF
	//{ 0x0, "_ZNK13ActiveGrenade5GetIDEv", mfunc_ptr_cast(&ActiveGrenade::GetID) },	// NOXREF
	//{ 0x0, "_ZNK13ActiveGrenade21GetDetonationPositionEv", mfunc_ptr_cast(&ActiveGrenade::GetDetonationPosition) },	// NOXREF
	//{ 0x01D340C0, "_ZNK13ActiveGrenade11GetPositionEv", mfunc_ptr_cast(&ActiveGrenade::GetPosition) },

//CBot
	//{ 0x0, "", mfunc_ptr_cast(&CBot::CBot) },
	//virtual func
	//{ 0x01D33550, "_ZN4CBot5SpawnEv", mfunc_ptr_cast(&CBot::Spawn_) },
	//{ 0x0, "_ZN4CBot10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CBot::TakeDamage) },
	//{ 0x0, "_ZN4CBot6KilledEP9entvars_si", mfunc_ptr_cast(&CBot::Killed) },
	//{ 0x0, "_ZN4CBot5ThinkEv", mfunc_ptr_cast(&CBot::Think) },
	//{ 0x0, "_ZN4CBot5IsBotEv", mfunc_ptr_cast(&CBot::IsBot) },
	//{ 0x0, "_ZN4CBot16GetAutoaimVectorEf", mfunc_ptr_cast(&CBot::GetAutoaimVector_) },
	//{ 0x0, "_ZN4CBot16OnTouchingWeaponEP10CWeaponBox", mfunc_ptr_cast(&CBot::OnTouchingWeapon) },
	{ 0x01D33540, "_ZN4CBot10InitializeEPK10BotProfile", mfunc_ptr_cast(&CBot::Initialize_) },
	//{ 0x0, "_ZN4CBot8SpawnBotEv", mfunc_ptr_cast(&CBot::SpawnBot) },
	//{ 0x0, "_ZN4CBot6UpkeepEv", mfunc_ptr_cast(&CBot::Upkeep) },
	//{ 0x0, "_ZN4CBot6UpdateEv", mfunc_ptr_cast(&CBot::Update) },
	//{ 0x0, "_ZN4CBot3RunEv", mfunc_ptr_cast(&CBot::Run) },
	//{ 0x0, "_ZN4CBot4WalkEv", mfunc_ptr_cast(&CBot::Walk) },
	//{ 0x0, "_ZN4CBot6CrouchEv", mfunc_ptr_cast(&CBot::Crouch_) },
	//{ 0x0, "_ZN4CBot7StandUpEv", mfunc_ptr_cast(&CBot::StandUp_) },
	//{ 0x0, "_ZN4CBot11MoveForwardEv", mfunc_ptr_cast(&CBot::MoveForward_) },
	//{ 0x0, "_ZN4CBot12MoveBackwardEv", mfunc_ptr_cast(&CBot::MoveBackward_) },
	//{ 0x0, "_ZN4CBot10StrafeLeftEv", mfunc_ptr_cast(&CBot::StrafeLeft_) },
	//{ 0x0, "_ZN4CBot11StrafeRightEv", mfunc_ptr_cast(&CBot::StrafeRight_) },
	//{ 0x0, "_ZN4CBot4JumpEb", mfunc_ptr_cast(&CBot::Jump_) },
	//{ 0x0, "_ZN4CBot13ClearMovementEv", mfunc_ptr_cast(&CBot::ClearMovement_) },
	//{ 0x0, "_ZN4CBot14UseEnvironmentEv", mfunc_ptr_cast(&CBot::UseEnvironment_) },
	//{ 0x0, "_ZN4CBot13PrimaryAttackEv", mfunc_ptr_cast(&CBot::PrimaryAttack_) },
	//{ 0x0, "_ZN4CBot18ClearPrimaryAttackEv", mfunc_ptr_cast(&CBot::ClearPrimaryAttack_) },
	{ 0x01D33990, "_ZN4CBot19TogglePrimaryAttackEv", mfunc_ptr_cast(&CBot::TogglePrimaryAttack_) },
	//{ 0x0, "_ZN4CBot15SecondaryAttackEv", mfunc_ptr_cast(&CBot::SecondaryAttack_) },
	//{ 0x0, "_ZN4CBot6ReloadEv", mfunc_ptr_cast(&CBot::Reload_) },
	//{ 0x0, "_ZN4CBot7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBot::OnEvent) },
	//{ 0x0, "_ZNK4CBot9IsVisibleEPK6Vectorb", mfunc_ptr_cast<IS_VISIBLE_VECTOR>(&CBot::IsVisible) },
	//{ 0x0, "_ZNK4CBot9IsVisibleEP11CBasePlayerbPh", mfunc_ptr_cast<IS_VISIBLE_CBASE_PLAYER>(&CBot::IsVisible) },
	//{ 0x0, "_ZNK4CBot18IsEnemyPartVisibleENS_15VisiblePartTypeE", mfunc_ptr_cast(&CBot::IsEnemyPartVisible) },	// NOXREF PURE
	//{ 0x0, "_ZNK4CBot16IsPlayerFacingMeEP11CBasePlayer", mfunc_ptr_cast(&CBot::IsPlayerFacingMe) },
	//{ 0x0, "_ZNK4CBot19IsPlayerLookingAtMeEP11CBasePlayer", mfunc_ptr_cast(&CBot::IsPlayerLookingAtMe) },
	{ 0x01D33AA0, "_ZN4CBot14ExecuteCommandEv", mfunc_ptr_cast(&CBot::ExecuteCommand_) },
	//{ 0x0, "_ZN4CBot8SetModelEPKc", mfunc_ptr_cast(&CBot::SetModel) },
	//non-virtual func
	//{ 0x0, "_ZNK4CBot5GetIDEv", mfunc_ptr_cast(&CBot::GetID) },
	//{ 0x0, "_ZNK4CBot9IsRunningEv", mfunc_ptr_cast(&CBot::IsRunning) },
	//{ 0x0, "_ZNK4CBot11IsCrouchingEv", mfunc_ptr_cast(&CBot::IsCrouching) },
	//{ 0x0, "_ZN4CBot18PushPostureContextEv", mfunc_ptr_cast(&CBot::PushPostureContext) },
	//{ 0x0, "_ZN4CBot17PopPostureContextEv", mfunc_ptr_cast(&CBot::PopPostureContext) },
	//{ 0x0, "_ZN4CBot9IsJumpingEv", mfunc_ptr_cast(&CBot::IsJumping) },
	//{ 0x0, "_ZNK4CBot16GetJumpTimestampEv", mfunc_ptr_cast(&CBot::GetJumpTimestamp) },
	//{ 0x0, "_ZNK4CBot24GetActiveWeaponAmmoRatioEv", mfunc_ptr_cast(&CBot::GetActiveWeaponAmmoRatio) },
	//{ 0x0, "_ZNK4CBot23IsActiveWeaponClipEmptyEv", mfunc_ptr_cast(&CBot::IsActiveWeaponClipEmpty) },
	//{ 0x0, "_ZNK4CBot23IsActiveWeaponOutOfAmmoEv", mfunc_ptr_cast(&CBot::IsActiveWeaponOutOfAmmo) },
	//{ 0x0, "_ZNK4CBot23IsActiveWeaponReloadingEv", mfunc_ptr_cast(&CBot::IsActiveWeaponReloading) },
	//{ 0x0, "_ZNK4CBot24IsActiveWeaponRecoilHighEv", mfunc_ptr_cast(&CBot::IsActiveWeaponRecoilHigh) },
	//{ 0x0, "_ZNK4CBot15GetActiveWeaponEv", mfunc_ptr_cast(&CBot::GetActiveWeapon) },
	{ 0x01D33A80, "_ZNK4CBot12IsUsingScopeEv", mfunc_ptr_cast(&CBot::IsUsingScope) },
	//{ 0x0, "_ZNK4CBot7IsEnemyEP11CBaseEntity", mfunc_ptr_cast(&CBot::IsEnemy) },
	//{ 0x01D33C40, "_ZNK4CBot19GetEnemiesRemainingEv", mfunc_ptr_cast(&CBot::GetEnemiesRemaining) },
	//{ 0x01D33D20, "_ZNK4CBot19GetFriendsRemainingEv", mfunc_ptr_cast(&CBot::GetFriendsRemaining) },
	{ 0x01D33E30, "_ZNK4CBot23IsLocalPlayerWatchingMeEv", mfunc_ptr_cast(&CBot::IsLocalPlayerWatchingMe) },
	//{ 0x01D33E90, "_ZNK4CBot5PrintEPcz", mfunc_ptr_cast(&CBot::Print) },	// NOXREF
	{ 0x01D33F00, "_ZNK4CBot14PrintIfWatchedEPcz", mfunc_ptr_cast(&CBot::PrintIfWatched) },
	{ 0x01D33660, "_ZN4CBot8BotThinkEv", mfunc_ptr_cast(&CBot::BotThink) },
	//{ 0x0, "_ZNK4CBot11IsNetClientEv", mfunc_ptr_cast(&CBot::IsNetClient) },
	//{ 0x0, "_ZNK4CBot4SaveER5CSave", mfunc_ptr_cast(&CBot::Save) },
	//{ 0x0, "_ZNK4CBot7RestoreER8CRestore", mfunc_ptr_cast(&CBot::Restore) },
	//{ 0x0, "_ZNK4CBot10GetProfileEv", mfunc_ptr_cast(&CBot::GetProfile) },
	{ 0x01D33BA0, "_ZN4CBot13ClientCommandEPKcS1_S1_S1_", mfunc_ptr_cast(&CBot::ClientCommand) },
	//{ 0x01D33B50, "_ZN4CBot12ResetCommandEv", mfunc_ptr_cast(&CBot::ResetCommand) },	// NOXREF
	//{ 0x01D33B70, "_ZNK4CBot13ThrottledMsecEv", mfunc_ptr_cast(&CBot::ThrottledMsec) },	// NOXREF
	//{ 0x0, "_ZN4CBot12GetMoveSpeedEv", mfunc_ptr_cast(&CBot::GetMoveSpeed) },
//BotMeme
	//{ 0x0, "_ZNK7BotMeme8TransmitEP6CCSBot", mfunc_ptr_cast(&BotMeme::Transmit) },
	//{ 0x0, "_ZNK7BotMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotMeme::Interpret) },	// NOXREF
//BotAllHostagesGoneMeme
	//{ 0x0, "_ZNK22BotAllHostagesGoneMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotAllHostagesGoneMeme::Interpret) },
//BotHostageBeingTakenMeme
	//{ 0x0, "_ZNK24BotHostageBeingTakenMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotHostageBeingTakenMeme::Interpret) },
//BotHelpMeme
	//{ 0x0, "_ZNK11BotHelpMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotHelpMeme::Interpret) },
//BotBombsiteStatusMeme
	//{ 0x0, "_ZNK21BotBombsiteStatusMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotBombsiteStatusMeme::Interpret) },
//BotBombStatusMeme
	//{ 0x0, "_ZNK17BotBombStatusMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotBombStatusMeme::Interpret) },
//BotFollowMeme
	//{ 0x0, "_ZNK13BotFollowMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotFollowMeme::Interpret) },
//BotDefendHereMeme
	//{ 0x0, "_ZNK17BotDefendHereMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotDefendHereMeme::Interpret) },
//BotWhereBombMeme
	//{ 0x0, "_ZNK16BotWhereBombMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotWhereBombMeme::Interpret) },
//BotRequestReportMeme
	//{ 0x0, "_ZNK20BotRequestReportMeme9InterpretEP6CCSBotS1_", mfunc_ptr_cast(&BotRequestReportMeme::Interpret) },
//BotSpeakable
	//{ 0x0, "", mfunc_ptr_cast(&BotSpeakable::BotSpeakable) },	// NOXREF
	//{ 0x0, "", mfunc_ptr_cast(&BotSpeakable::~BotSpeakable) },	// NOXREF
//BotPhrase
	//{ 0x01D196B0, "", mfunc_ptr_cast(&BotPhrase::BotPhrase) },	// NOXREF
	//{ 0x01D198E0, "", mfunc_ptr_cast(&BotPhrase::~BotPhrase) },	// NOXREF
	//{ 0x0, "_ZN9BotPhrase13InitVoiceBankEi", mfunc_ptr_cast(&BotPhrase::InitVoiceBank) },
	//3@@{ 0x01D19BB0, "_ZNK9BotPhrase12GetSpeakableEiPf", mfunc_ptr_cast(&BotPhrase::GetSpeakable) },
	//{ 0x0, "_ZNK9BotPhrase13ClearCriteriaEv", mfunc_ptr_cast(&BotPhrase::ClearCriteria) },
	//{ 0x0, "_ZNK9BotPhrase16SetPlaceCriteriaEj", mfunc_ptr_cast(&BotPhrase::SetPlaceCriteria) },
	//{ 0x0, "_ZNK9BotPhrase16SetCountCriteriaEj", mfunc_ptr_cast(&BotPhrase::SetCountCriteria) },
	//{ 0x0, "_ZNK9BotPhrase7GetNameEv", mfunc_ptr_cast(&BotPhrase::GetName) },
	//{ 0x0, "_ZNK9BotPhrase5GetIDEv", mfunc_ptr_cast(&BotPhrase::GetID) },
	//{ 0x0, "_ZNK9BotPhrase18GetRadioEquivalentEv", mfunc_ptr_cast(&BotPhrase::GetRadioEquivalent) },
	//{ 0x0, "_ZNK9BotPhrase11IsImportantEv", mfunc_ptr_cast(&BotPhrase::IsImportant) },
	//{ 0x0, "_ZNK9BotPhrase7IsPlaceEv", mfunc_ptr_cast(&BotPhrase::IsPlace) },
	//{ 0x01D19C70, "_ZN9BotPhrase9RandomizeEv", mfunc_ptr_cast(&BotPhrase::Randomize) },	// NOXREF
//BotPhraseManager
	//{ 0x01D19D20, "", mfunc_ptr_cast(&BotPhraseManager::BotPhraseManager) },
	//{ 0x0, "", mfunc_ptr_cast(&BotPhraseManager::~BotPhraseManager) },
	//{ 0x01D19ED0, "_ZN16BotPhraseManager10InitializeEPKci", mfunc_ptr_cast(&BotPhraseManager::Initialize) },
	{ 0x01D19DA0, "_ZN16BotPhraseManager14OnRoundRestartEv", mfunc_ptr_cast(&BotPhraseManager::OnRoundRestart) },
	//{ 0x0, "_ZN16BotPhraseManager11OnMapChangeEv", mfunc_ptr_cast(&BotPhraseManager::OnMapChange) },
	//{ 0x01D1A830, "_ZNK16BotPhraseManager8NameToIDEPKc", mfunc_ptr_cast(&BotPhraseManager::NameToID) },
	//{ 0x01D1A8A0, "_ZNK16BotPhraseManager8IDToNameEj", mfunc_ptr_cast(&BotPhraseManager::IDToName) },
	//{ 0x01D1A8F0, "_ZNK16BotPhraseManager9GetPhraseEPKc", mfunc_ptr_cast(&BotPhraseManager::GetPhrase) },
	//{ 0x0, "_ZNK16BotPhraseManager8GetPlaceEPKc", mfunc_ptr_cast<GET_PLACE_NAME>(&BotPhraseManager::GetPlace) },
	//{ 0x0, "_ZNK16BotPhraseManager8GetPlaceEj", mfunc_ptr_cast<GET_PLACE_PLACE>(&BotPhraseManager::GetPlace) },
	//{ 0x0, "_ZNK16BotPhraseManager12GetPlaceListEv", mfunc_ptr_cast(&BotPhraseManager::GetPlaceList) },
	//{ 0x0, "_ZNK16BotPhraseManager25GetPlaceStatementIntervalEj", mfunc_ptr_cast(&BotPhraseManager::GetPlaceStatementInterval) },
	//{ 0x0, "_ZN16BotPhraseManager27ResetPlaceStatementIntervalEj", mfunc_ptr_cast(&BotPhraseManager::ResetPlaceStatementInterval) },
#ifdef _WIN32
	//{ 0x01D1F830, "_ZNK16BotPhraseManager14FindPlaceIndexEj", mfunc_ptr_cast(&BotPhraseManager::FindPlaceIndex) },
#endif // _WIN32

//BotStatement
	//{ 0x0, "", mfunc_ptr_cast(&BotStatement::BotStatement) },
	//{ 0x0, "", mfunc_ptr_cast(&BotStatement::~BotStatement) },
	//{ 0x0, "_ZNK12BotStatement10GetChatterEv", mfunc_ptr_cast(&BotStatement::GetChatter) },
	//{ 0x0, "_ZNK12BotStatement8GetOwnerEv", mfunc_ptr_cast(&BotStatement::GetOwner) },
	//{ 0x0, "_ZNK12BotStatement7GetTypeEv", mfunc_ptr_cast(&BotStatement::GetType) },
	//{ 0x0, "_ZNK12BotStatement11IsImportantEv", mfunc_ptr_cast(&BotStatement::IsImportant) },
	//{ 0x0, "_ZNK12BotStatement10HasSubjectEv", mfunc_ptr_cast(&BotStatement::HasSubject) },
	//{ 0x0, "_ZN12BotStatement10SetSubjectEi", mfunc_ptr_cast(&BotStatement::SetSubject) },
	//{ 0x0, "_ZNK12BotStatement10GetSubjectEv", mfunc_ptr_cast(&BotStatement::GetSubject) },
	//{ 0x0, "_ZNK12BotStatement8HasPlaceEv", mfunc_ptr_cast(&BotStatement::HasPlace) },
	//{ 0x0, "_ZNK12BotStatement8GetPlaceEv", mfunc_ptr_cast(&BotStatement::GetPlace) },
	//{ 0x0, "_ZN12BotStatement8SetPlaceEj", mfunc_ptr_cast(&BotStatement::SetPlace) },
	//{ 0x0, "_ZNK12BotStatement8HasCountEv", mfunc_ptr_cast(&BotStatement::HasCount) },
	//{ 0x0, "_ZNK12BotStatement11IsRedundantEPKS_", mfunc_ptr_cast(&BotStatement::IsRedundant) },
	//{ 0x0, "_ZNK12BotStatement10IsObsoleteEv", mfunc_ptr_cast(&BotStatement::IsObsolete) },
	//{ 0x0, "_ZN12BotStatement7ConvertEPKS_", mfunc_ptr_cast(&BotStatement::Convert) },
	//{ 0x0, "_ZN12BotStatement12AppendPhraseEPK9BotPhrase", mfunc_ptr_cast<APPEND_PHRASE_BOTPHRASE>(&BotStatement::AppendPhrase) },
	//{ 0x0, "_ZN12BotStatement12AppendPhraseENS_11ContextTypeE", mfunc_ptr_cast<APPEND_PHRASE_CONTEXT>(&BotStatement::AppendPhrase) },
	//{ 0x0, "_ZN12BotStatement12SetStartTimeEf ", mfunc_ptr_cast(&BotStatement::SetStartTime) },
	//{ 0x0, "_ZNK12BotStatement12GetStartTimeEv", mfunc_ptr_cast(&BotStatement::GetStartTime) },
	//{ 0x0, "_ZN12BotStatement12AddConditionENS_13ConditionTypeE", mfunc_ptr_cast(&BotStatement::AddCondition) },
	//{ 0x0, "_ZNK12BotStatement7IsValidEv", mfunc_ptr_cast(&BotStatement::IsValid) },
	//{ 0x01D1AE20, "_ZN12BotStatement6UpdateEv", mfunc_ptr_cast(&BotStatement::Update) },
	//{ 0x0, "_ZNK12BotStatement10IsSpeakingEv", mfunc_ptr_cast(&BotStatement::IsSpeaking) },
	//{ 0x0, "_ZNK12BotStatement12GetTimestampEv", mfunc_ptr_cast(&BotStatement::GetTimestamp) },
	//{ 0x0, "_ZN12BotStatement10AttachMemeEP7BotMeme", mfunc_ptr_cast(&BotStatement::AttachMeme) },
//BotChatterInterface
	//{ 0x0, "", mfunc_ptr_cast(&BotChatterInterface::BotChatterInterface) },
	//{ 0x0, "", mfunc_ptr_cast(&BotChatterInterface::~BotChatterInterface) },
	//{ 0x0, "_ZN19BotChatterInterface5ResetEv", mfunc_ptr_cast(&BotChatterInterface::Reset) },
	//{ 0x01D1B8E0, "_ZN19BotChatterInterface6UpdateEv", mfunc_ptr_cast(&BotChatterInterface::Update) },
	//{ 0x0, "_ZN19BotChatterInterface7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&BotChatterInterface::OnEvent) },
	//{ 0x01D1B7E0, "_ZN19BotChatterInterface7OnDeathEv", mfunc_ptr_cast(&BotChatterInterface::OnDeath) },
	//{ 0x0, "_ZNK19BotChatterInterface12GetVerbosityEv", mfunc_ptr_cast(&BotChatterInterface::VerbosityType GetVerbosity) },
	//{ 0x0, "_ZNK19BotChatterInterface8GetOwnerEv", mfunc_ptr_cast(&BotChatterInterface::GetOwner) },
	//{ 0x0, "_ZNK19BotChatterInterface9IsTalkingEv", mfunc_ptr_cast(&BotChatterInterface::IsTalking) },
	//{ 0x0, "_ZN19BotChatterInterface23GetRadioSilenceDurationEv", mfunc_ptr_cast(&BotChatterInterface::GetRadioSilenceDuration) },
	//{ 0x0, "_ZN19BotChatterInterface25ResetRadioSilenceDurationEv", mfunc_ptr_cast(&BotChatterInterface::ResetRadioSilenceDuration) },
	//{ 0x01D1B490, "_ZN19BotChatterInterface12AddStatementEP12BotStatementb", mfunc_ptr_cast(&BotChatterInterface::AddStatement) },
	//{ 0x0, "_ZN19BotChatterInterface15RemoveStatementEP12BotStatement", mfunc_ptr_cast(&BotChatterInterface::RemoveStatement) },
	//{ 0x0, "_ZN19BotChatterInterface18GetActiveStatementEv", mfunc_ptr_cast(&BotChatterInterface::GetActiveStatement) },
	//{ 0x0, "_ZNK19BotChatterInterface12GetStatementEv", mfunc_ptr_cast(&BotChatterInterface::GetStatement) },
	//{ 0x0, "_ZNK19BotChatterInterface8GetPitchEv", mfunc_ptr_cast(&BotChatterInterface::GetPitch) },
	//{ 0x0, "_ZN19BotChatterInterface3SayEPKcff", mfunc_ptr_cast(&BotChatterInterface::Say) },
	//{ 0x0, "_ZN19BotChatterInterface12AnnouncePlanEPKcj", mfunc_ptr_cast(&BotChatterInterface::AnnouncePlan) },
	//{ 0x0, "_ZN19BotChatterInterface11AffirmativeEv", mfunc_ptr_cast(&BotChatterInterface::Affirmative) },
	//{ 0x0, "_ZN19BotChatterInterface8NegativeEv", mfunc_ptr_cast(&BotChatterInterface::Negative) },
	//{ 0x0, "_ZN19BotChatterInterface12EnemySpottedEv", mfunc_ptr_cast(&BotChatterInterface::EnemySpotted) },
	//{ 0x0, "_ZN19BotChatterInterface13KilledMyEnemyEi", mfunc_ptr_cast(&BotChatterInterface::KilledMyEnemy) },
	//{ 0x0, "_ZN19BotChatterInterface16EnemiesRemainingEv", mfunc_ptr_cast(&BotChatterInterface::EnemiesRemaining) },
	//{ 0x0, "_ZN19BotChatterInterface5ClearEj", mfunc_ptr_cast(&BotChatterInterface::Clear) },
	//{ 0x0, "_ZN19BotChatterInterface8ReportInEv", mfunc_ptr_cast(&BotChatterInterface::ReportIn) },
	//{ 0x0, "_ZN19BotChatterInterface11ReportingInEv", mfunc_ptr_cast(&BotChatterInterface::ReportingIn) },
	//{ 0x01D1C6D0, "_ZN19BotChatterInterface10NeedBackupEv", mfunc_ptr_cast(&BotChatterInterface::NeedBackup) },
	//{ 0x0, "_ZN19BotChatterInterface10PinnedDownEv", mfunc_ptr_cast(&BotChatterInterface::PinnedDown) },
	//{ 0x0, "_ZN19BotChatterInterface6ScaredEv", mfunc_ptr_cast(&BotChatterInterface::Scared) },
	//{ 0x0, "_ZN19BotChatterInterface10HeardNoiseEPK6Vector", mfunc_ptr_cast(&BotChatterInterface::HeardNoise) },
	//{ 0x0, "_ZN19BotChatterInterface19TheyPickedUpTheBombEv", mfunc_ptr_cast(&BotChatterInterface::TheyPickedUpTheBomb) },
	//{ 0x0, "_ZN19BotChatterInterface19GoingToPlantTheBombEj", mfunc_ptr_cast(&BotChatterInterface::GoingToPlantTheBomb) },
	//{ 0x0, "_ZN19BotChatterInterface13BombsiteClearEi", mfunc_ptr_cast(&BotChatterInterface::BombsiteClear) },
	//{ 0x0, "_ZN19BotChatterInterface16FoundPlantedBombEi", mfunc_ptr_cast(&BotChatterInterface::FoundPlantedBomb) },
	//{ 0x0, "_ZN19BotChatterInterface15PlantingTheBombEj", mfunc_ptr_cast(&BotChatterInterface::PlantingTheBomb) },
	//{ 0x0, "_ZN19BotChatterInterface13SpottedBomberEP11CBasePlayer", mfunc_ptr_cast(&BotChatterInterface::SpottedBomber) },
	//{ 0x0, "_ZN19BotChatterInterface16SpottedLooseBombEP11CBaseEntity", mfunc_ptr_cast(&BotChatterInterface::SpottedLooseBomb) },
	//{ 0x0, "_ZN19BotChatterInterface17GuardingLooseBombEP11CBaseEntity", mfunc_ptr_cast(&BotChatterInterface::GuardingLooseBomb) },
	//{ 0x0, "_ZN19BotChatterInterface19RequestBombLocationEv", mfunc_ptr_cast(&BotChatterInterface::RequestBombLocation) },
	//{ 0x0, "_ZN19BotChatterInterface16GuardingHostagesEjb", mfunc_ptr_cast(&BotChatterInterface::GuardingHostages) },
	//{ 0x0, "_ZN19BotChatterInterface25GuardingHostageEscapeZoneEb", mfunc_ptr_cast(&BotChatterInterface::GuardingHostageEscapeZone) },
	//{ 0x0, "_ZN19BotChatterInterface18HostagesBeingTakenEv", mfunc_ptr_cast(&BotChatterInterface::HostagesBeingTaken) },
	//{ 0x0, "_ZN19BotChatterInterface13HostagesTakenEv", mfunc_ptr_cast(&BotChatterInterface::HostagesTaken) },
	//{ 0x0, "_ZN19BotChatterInterface17TalkingToHostagesEv", mfunc_ptr_cast(&BotChatterInterface::TalkingToHostages) },
	//{ 0x0, "_ZN19BotChatterInterface17EscortingHostagesEv", mfunc_ptr_cast(&BotChatterInterface::EscortingHostages) },
	//{ 0x0, "_ZN19BotChatterInterface11HostageDownEv", mfunc_ptr_cast(&BotChatterInterface::HostageDown) },
	//{ 0x0, "_ZN19BotChatterInterface12CelebrateWinEv", mfunc_ptr_cast(&BotChatterInterface::CelebrateWin) },
	//{ 0x0, "_ZN19BotChatterInterface9EncourageEPKcff", mfunc_ptr_cast(&BotChatterInterface::Encourage) },
	//{ 0x0, "_ZN19BotChatterInterface12KilledFriendEv", mfunc_ptr_cast(&BotChatterInterface::KilledFriend) },
	//{ 0x0, "_ZN19BotChatterInterface12FriendlyFireEv", mfunc_ptr_cast(&BotChatterInterface::FriendlyFire) },
	//{ 0x01D1B630, "_ZN19BotChatterInterface13ReportEnemiesEv", mfunc_ptr_cast(&BotChatterInterface::ReportEnemies) },
	//{ 0x0, "_ZNK19BotChatterInterface11ShouldSpeakEv", mfunc_ptr_cast(&BotChatterInterface::ShouldSpeak) },

	//{ 0x0, "_Z20GetRandomSpotAtPlacej", (size_t)&GetRandomSpotAtPlace },

#endif // Bot_Region

#ifndef CS_Util_Region

	{ 0x01D36490, "_Z16UTIL_IsNameTakenPKcb", (size_t)&UTIL_IsNameTaken },
	{ 0x01D365E0, "_Z18UTIL_ClientsInGamev", (size_t)&UTIL_ClientsInGame },
	{ 0x01D36690, "_Z24UTIL_ActivePlayersInGamev", (size_t)&UTIL_ActivePlayersInGame },
	{ 0x01D36760, "_Z17UTIL_HumansInGameb", (size_t)&UTIL_HumansInGame },
	//{ 0x0, "_Z17UTIL_HumansOnTeamib", (size_t)&UTIL_HumansOnTeam },
	//{ 0x0, "_Z15UTIL_BotsInGamev", (size_t)&UTIL_BotsInGame },
	{ 0x01D36A00, "_Z20UTIL_KickBotFromTeam8TeamName", (size_t)&UTIL_KickBotFromTeam },
	//{ 0x0, "_Z18UTIL_IsTeamAllBotsi", (size_t)&UTIL_IsTeamAllBots },
	//{ 0x0, "_Z21UTIL_GetClosestPlayerPK6VectorPf", mfunc_ptr_cast<UTIL_GETCLOSE_PLAYER>(&UTIL_GetClosestPlayer) },
	//{ 0x0, "_Z21UTIL_GetClosestPlayerPK6VectoriPf", mfunc_ptr_cast<UTIL_GETCLOSE_TEAM>(&UTIL_GetClosestPlayer) },
	//{ 0x01D36F90, "_Z17UTIL_GetBotPrefixv", (size_t)&UTIL_GetBotPrefix },	// NOXREF
	{ 0x01D36FA0, "_Z24UTIL_ConstructBotNetNamePciPK10BotProfile", (size_t)&UTIL_ConstructBotNetName },
	//{ 0x0, "_Z20UTIL_IsVisibleToTeamRK6Vectorif", (size_t)&UTIL_IsVisibleToTeam },
	{ 0x01D37190, "_Z19UTIL_GetLocalPlayerv", (size_t)&UTIL_GetLocalPlayer },
	//{ 0x0, "_Z18UTIL_ComputeOriginP9entvars_s", mfunc_ptr_cast<UTIL_CUMPUTE_ENTVARS>(&UTIL_ComputeOrigin) },
	//{ 0x0, "_Z18UTIL_ComputeOriginP11CBaseEntity", mfunc_ptr_cast<UTIL_CUMPUTE_CBASE>(&UTIL_ComputeOrigin) },
	//{ 0x0, "_Z18UTIL_ComputeOriginP7edict_s", mfunc_ptr_cast<UTIL_CUMPUTE_EDICT>(&UTIL_ComputeOrigin) },
	//{ 0x0, "_Z20UTIL_DrawBeamFromEnti6Vectorihhh", (size_t)&UTIL_DrawBeamFromEnt },
	//{ 0x01D37480, "_Z19UTIL_DrawBeamPoints6VectorS_ihhh", (size_t)&UTIL_DrawBeamPoints },
	{ 0x01D375D0, "_Z11BotPrecachev", (size_t)&BotPrecache },
	{ 0x01D37570, "_Z12CONSOLE_ECHOPcz", (size_t)&CONSOLE_ECHO },
	//{ 0x01D375A0, "_Z19CONSOLE_ECHO_LOGGEDPcz", (size_t)&CONSOLE_ECHO_LOGGED },	// NOXREF
	{ 0x01D37660, "_Z11InitBotTrigv", (size_t)&InitBotTrig },

	{ 0x01D37690, "_Z6BotCOSf", (size_t)&BotCOS },
	{ 0x01D37700, "_Z6BotSINf", (size_t)&BotSIN },

	//{ 0x01D37770, "_Z18IsGameEventAudible13GameEventTypeP11CBaseEntityS1_PfP12PriorityTypePb", (size_t)&IsGameEventAudible },
	{ 0x01D37A00, "_Z23HintMessageToAllPlayersPKc", (size_t)&HintMessageToAllPlayers },

#endif // CS_Util_Region

#ifndef CS_Init_Region

	//{ 0x01D206A0, "_Z17InstallBotControlv", (size_t)&InstallBotControl },
	{ 0x01D20730, "_Z17Bot_ServerCommandv", (size_t)&Bot_ServerCommand },
	{ 0x01D20760, "_Z17Bot_RegisterCvarsv", (size_t)&Bot_RegisterCvars },

#endif // CS_Init_Region

#ifndef H_Region

//AI
	//{ 0x01D848B0, "_Z11FBoxVisibleP9entvars_sS0_R6Vectorf", (size_t)&FBoxVisible },		// NOXREF
	//{ 0x01D84A10, "_Z12VecCheckTossP9entvars_sRK6VectorS1_f", (size_t)&VecCheckToss },	// NOXREF
	//{ 0x01D84EB0, "_Z13VecCheckThrowP9entvars_sRK6VectorS1_ff", (size_t)&VecCheckThrow },	// NOXREF

//CRecharge
	//virtual func
	{ 0x01D851E0, "_ZN9CRecharge5SpawnEv", mfunc_ptr_cast(&CRecharge::Spawn_) },
	{ 0x01D85270, "_ZN9CRecharge8PrecacheEv", mfunc_ptr_cast(&CRecharge::Precache_) },
	{ 0x01D85130, "_ZN9CRecharge8KeyValueEP14KeyValueData_s", mfunc_ptr_cast(&CRecharge::KeyValue_) },
	{ 0x01D85070, "_ZN9CRecharge4SaveER5CSave", mfunc_ptr_cast(&CRecharge::Save_) },
	{ 0x01D850A0, "_ZN9CRecharge7RestoreER8CRestore", mfunc_ptr_cast(&CRecharge::Restore_) },
	{ 0x01D85120, "_ZN9CRecharge10ObjectCapsEv", mfunc_ptr_cast(&CRecharge::ObjectCaps_) },
	{ 0x01D852A0, "_ZN9CRecharge3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CRecharge::Use_) },
	//non-virtual func
	//{ 0x01D850D0, "func_recharge", (size_t)&func_recharge },
	{ 0x01D855A0, "_ZN9CRecharge3OffEv", mfunc_ptr_cast(&CRecharge::Off) },
	{ 0x01D85570, "_ZN9CRecharge8RechargeEv", mfunc_ptr_cast(&CRecharge::Recharge) },
//CCycler
	//virtual func
	//{ 0x0, "_ZN7CCycler5SpawnEv", mfunc_ptr_cast(&CCycler::Spawn_) },
	//{ 0x0, "_ZN7CCycler4SaveER5CSave", mfunc_ptr_cast(&CCycler::Save_) },
	//{ 0x0, "_ZN7CCycler7RestoreER8CRestore", mfunc_ptr_cast(&CCycler::Restore_) },
	////{ 0x0, "_ZN7CCycler10ObjectCapsEv", mfunc_ptr_cast(&CCycler::ObjectCaps_) },
	//{ 0x0, "_ZN7CCycler10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CCycler::TakeDamage_) },
	////{ 0x0, "_ZN7CCycler7IsAliveEv", mfunc_ptr_cast(&CCycler::IsAlive_) },
	//{ 0x0, "_ZN7CCycler5ThinkEv", mfunc_ptr_cast(&CCycler::Think_) },
	//{ 0x0, "_ZN7CCycler3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CCycler::Use_) },
	//non-virtual func
	//{ 0x0, "_ZN7CCycler18GenericCyclerSpawnEPc6VectorS1__part_11_constprop_16", mfunc_ptr_cast(&CCycler::GenericCyclerSpawn) },
//CCyclerProbe
	//virtual func
	//{ 0x0, "_ZN12CCyclerProbe5SpawnEv", mfunc_ptr_cast(&CCyclerProbe::Spawn_) },
	//non-virtual func
	//{ 0x01D85810, "cycler_prdroid", (size_t)&cycler_prdroid },
//CGenericCycler
	//virtual func
	//{ 0x0, "_ZN14CGenericCycler5SpawnEv", mfunc_ptr_cast(&CGenericCycler::Spawn_) },
	//non-virtual func
	//{ 0x01D85690, "cycler", (size_t)&cycler },
//CCyclerSprite
	//virtual func
	//{ 0x0, "_ZN13CCyclerSprite5SpawnEv", mfunc_ptr_cast(&CCyclerSprite::Spawn_) },
	//{ 0x0, "_ZN13CCyclerSprite7RestartEv", mfunc_ptr_cast(&CCyclerSprite::Restart_) },
	//{ 0x0, "_ZN13CCyclerSprite4SaveER5CSave", mfunc_ptr_cast(&CCyclerSprite::Save_) },
	//{ 0x0, "_ZN13CCyclerSprite7RestoreER8CRestore", mfunc_ptr_cast(&CCyclerSprite::Restore_) },
	////{ 0x01D85D70, "_ZN13CCyclerSprite10ObjectCapsEv", mfunc_ptr_cast(&CCyclerSprite::ObjectCaps_) },
	//{ 0x0, "_ZN13CCyclerSprite10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CCyclerSprite::TakeDamage_) },
	//{ 0x0, "_ZN13CCyclerSprite5ThinkEv", mfunc_ptr_cast(&CCyclerSprite::Think_) },
	//{ 0x0, "_ZN13CCyclerSprite3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CCyclerSprite::Use_) },
	//non-virtual func
	//{ 0x01D85D20, "cycler_sprite", (size_t)&cycler_sprite },
	//{ 0x0, "_ZN13CCyclerSprite7AnimateEf", mfunc_ptr_cast(&CCyclerSprite::Animate) },
//CWeaponCycler
	//virtual func
	//{ 0x0, "_ZN13CWeaponCycler5SpawnEv", mfunc_ptr_cast(&CWeaponCycler::Spawn_) },
	////{ 0x0, "_ZN13CWeaponCycler11GetItemInfoEP8ItemInfo", mfunc_ptr_cast(&CWeaponCycler::GetItemInfo_) },
	//{ 0x0, "_ZN13CWeaponCycler6DeployEv", mfunc_ptr_cast(&CWeaponCycler::Deploy_) },
	//{ 0x0, "_ZN13CWeaponCycler7HolsterEi", mfunc_ptr_cast(&CWeaponCycler::Holster_) },
	////{ 0x0, "_ZN13CWeaponCycler9iItemSlotEv", mfunc_ptr_cast(&CWeaponCycler::iItemSlot_) },
	//{ 0x0, "_ZN13CWeaponCycler13PrimaryAttackEv", mfunc_ptr_cast(&CWeaponCycler::PrimaryAttack_) },
	//{ 0x0, "_ZN13CWeaponCycler15SecondaryAttackEv", mfunc_ptr_cast(&CWeaponCycler::SecondaryAttack_) },
	//non-virtual func
	//{ 0x01D86150, "cycler_weapon", (size_t)&cycler_weapon },
//CWreckage
	//virtual func
	//{ 0x0, "_ZN9CWreckage5SpawnEv", mfunc_ptr_cast(&CWreckage::Spawn_) },
	//{ 0x0, "_ZN9CWreckage8PrecacheEv", mfunc_ptr_cast(&CWreckage::Precache_) },
	//{ 0x0, "_ZN9CWreckage4SaveER5CSave", mfunc_ptr_cast(&CWreckage::Save_) },
	//{ 0x0, "_ZN9CWreckage7RestoreER8CRestore", mfunc_ptr_cast(&CWreckage::Restore_) },
	//{ 0x0, "_ZN9CWreckage5ThinkEv", mfunc_ptr_cast(&CWreckage::Think_) },
	//non-virtual func
	//{ 0x01D86480, "cycler_wreckage", (size_t)&cycler_wreckage },

#endif // H_Region

#ifndef Tutor_CS_Region

	{ 0x01DD26D0, "_Z12InstallTutorb", (size_t)&InstallTutor },
	{ 0x01DD2740, "_Z19Tutor_RegisterCVarsv", (size_t)&Tutor_RegisterCVars },
	{ 0x01DD27C0, "_Z18MonitorTutorStatusv", (size_t)&MonitorTutorStatus },
//CBaseTutor
	//{ 0x01DD2BF0, "_ZN10CBaseTutorC2Ev", mfunc_ptr_cast(&CBaseTutor::CBaseTutor) },
	//{ 0x01DD2C10, "_ZN10CBaseTutorD0Ev", mfunc_ptr_cast(&CBaseTutor::~CBaseTutor) },
	//virtual func
	//{ 0x0, "_ZN10CBaseTutor10TutorThinkEf", mfunc_ptr_cast(&CBaseTutor::TutorThink_) },	// PURE virt
	//{ 0x0, "_ZN10CBaseTutor13PurgeMessagesEv", mfunc_ptr_cast(&CBaseTutor::PurgeMessages_) },	// PURE virt
	//{ 0x0, "_ZN10CBaseTutor16CallEventHandlerE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBaseTutor::CallEventHandler_) },	// PURE virt
	//{ 0x0, "_ZN10CBaseTutor16ShowTutorMessageEP17TutorMessageEvent", mfunc_ptr_cast(&CBaseTutor::ShowTutorMessage_) },	// PURE virt
	{ 0x01DD3070, "_ZN10CBaseTutor22IsEntityInViewOfPlayerEP11CBaseEntityP11CBasePlayer", mfunc_ptr_cast(&CBaseTutor::IsEntityInViewOfPlayer_) },
	{ 0x01DD3350, "_ZN10CBaseTutor24IsBombsiteInViewOfPlayerEP11CBaseEntityP11CBasePlayer", mfunc_ptr_cast(&CBaseTutor::IsBombsiteInViewOfPlayer_) },
	{ 0x01DD3480, "_ZN10CBaseTutor18IsEntityInBombsiteEP11CBaseEntityS1_", mfunc_ptr_cast(&CBaseTutor::IsEntityInBombsite_) },
	{ 0x01DD3160, "_ZN10CBaseTutor25IsPlayerLookingAtPositionEP6VectorP11CBasePlayer", mfunc_ptr_cast(&CBaseTutor::IsPlayerLookingAtPosition_) },
	{ 0x01DD3240, "_ZN10CBaseTutor23IsPlayerLookingAtEntityEP11CBaseEntityP11CBasePlayer", mfunc_ptr_cast(&CBaseTutor::IsPlayerLookingAtEntity_) },
	//{ 0x0, "_ZN10CBaseTutor15HandleShotFiredE6VectorS0_", mfunc_ptr_cast(&CBaseTutor::HandleShotFired_) },	// PURE virt
	//{ 0x0, "_ZN10CBaseTutor25GetTutorMessageDefinitionEi", mfunc_ptr_cast(&CBaseTutor::GetTutorMessageDefinition_) },	// PURE virt
	//non-virtual func
	{ 0x01DD2DA0, "_ZN10CBaseTutor10StartFrameEf", mfunc_ptr_cast(&CBaseTutor::StartFrame) },
	{ 0x01DD2C70, "_ZN10CBaseTutor7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBaseTutor::OnEvent) },
	//{ 0x01DD2CF0, "_ZN10CBaseTutor9ShotFiredE6VectorS0_", mfunc_ptr_cast(&CBaseTutor::ShotFired) },	// NOXREF
	{ 0x01DD2DB0, "_ZN10CBaseTutor22DisplayMessageToPlayerEP11CBasePlayeriPKcP17TutorMessageEvent", mfunc_ptr_cast(&CBaseTutor::DisplayMessageToPlayer) },
	//{ 0x01DD2F80, "_ZN10CBaseTutor16DrawLineToEntityEP11CBasePlayerii", mfunc_ptr_cast(&CBaseTutor::DrawLineToEntity) },			// NOXREF
	//{ 0x01DD2FD0, "_ZN10CBaseTutor34DisplayNewStateDescriptionToPlayerEv", mfunc_ptr_cast(&CBaseTutor::DisplayNewStateDescriptionToPlayer) },	// NOXREF
	{ 0x01DD3020, "_ZN10CBaseTutor18CloseCurrentWindowEv", mfunc_ptr_cast(&CBaseTutor::CloseCurrentWindow) },
	//{ 0x01DD2D30, "_ZN10CBaseTutor23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBaseTutor::CheckForStateTransition) },	// NOXREF
	//{ 0x01DD3060, "_ZN10CBaseTutor25CalculatePathForObjectiveEP11CBaseEntity", mfunc_ptr_cast(&CBaseTutor::CalculatePathForObjective) },	// PURE
	{ 0x01DD3510, "_ZN10CBaseTutor20DoMessagesHaveSameIDEii", mfunc_ptr_cast(&CBaseTutor::DoMessagesHaveSameID) },
//CCSTutor
	//{ 0x01DD3A30, "_ZN8CCSTutorC2Ev", mfunc_ptr_cast(&CCSTutor::CCSTutor) },
	//{ 0x01DD3B90, "_ZN8CCSTutorC2Ev", mfunc_ptr_cast(&CCSTutor::~CCSTutor) },
	//virtual func
	{ 0x01DD46C0, "_ZN8CCSTutor10TutorThinkEf", mfunc_ptr_cast(&CCSTutor::TutorThink_) },
	{ 0x01DD56C0, "_ZN8CCSTutor13PurgeMessagesEv", mfunc_ptr_cast(&CCSTutor::PurgeMessages_) },
	{ 0x01DD5960, "_ZN8CCSTutor16ShowTutorMessageEP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::ShowTutorMessage_) },
	{ 0x01DD5A20, "_ZN8CCSTutor16CallEventHandlerE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutor::CallEventHandler_) },
	{ 0x01DD9830, "_ZN8CCSTutor15HandleShotFiredE6VectorS0_", mfunc_ptr_cast(&CCSTutor::HandleShotFired_) },
	{ 0x01DDA8B0, "_ZN8CCSTutor25GetTutorMessageDefinitionEi", mfunc_ptr_cast(&CCSTutor::GetTutorMessageDefinition_) },
	//non-virtual func
	{ 0x01DD5510, "_ZN8CCSTutor14AddToEventListEP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::AddToEventList) },
	{ 0x01DD5530, "_ZN8CCSTutor23CreateAndAddEventToListE14TutorMessageIDP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutor::CreateAndAddEventToList) },
	{ 0x01DD51B0, "_ZN8CCSTutor23CreateTutorMessageEventE14TutorMessageIDP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutor::CreateTutorMessageEvent) },
	{ 0x01DD55C0, "_ZN8CCSTutor24DeleteEventFromEventListEP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::DeleteEventFromEventList) },
	{ 0x01DD5640, "_ZN8CCSTutor14ClearEventListEv", mfunc_ptr_cast(&CCSTutor::ClearEventList) },
	{ 0x01DD4BE0, "_ZN8CCSTutor17ClearCurrentEventEbb", mfunc_ptr_cast(&CCSTutor::ClearCurrentEvent) },
	{ 0x01DD5690, "_ZN8CCSTutor11DeleteEventEP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::DeleteEvent) },
	{ 0x01DD4410, "_ZN8CCSTutor22ShouldShowMessageEventEP17TutorMessageEventf", mfunc_ptr_cast(&CCSTutor::ShouldShowMessageEvent) },
	//{ 0x01DD5870, "_ZN8CCSTutor26ShouldUpdateCurrentMessageE14TutorMessageID", mfunc_ptr_cast(&CCSTutor::ShouldUpdateCurrentMessage) },	// NOXREF
	{ 0x01DD57B0, "_ZN8CCSTutor29ComputeDisplayTimesForMessageEv", mfunc_ptr_cast(&CCSTutor::ComputeDisplayTimesForMessage) },
	{ 0x01DD58A0, "_ZN8CCSTutor20UpdateCurrentMessageEP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::UpdateCurrentMessage) },
	//{ 0x01DD59B0, "_ZN8CCSTutor26ConstructMessageAndDisplayEv", mfunc_ptr_cast(&CCSTutor::ConstructMessageAndDisplay) },	// NOXREF
	//{ 0x01DD5190, "_ZN8CCSTutor12LookupHotKeyE14TutorMessageIDiPwi", mfunc_ptr_cast(&CCSTutor::LookupHotKey) },	// NOXREF
	//{ 0x01DD4970, "_ZN8CCSTutor19CheckForWindowCloseEf", mfunc_ptr_cast(&CCSTutor::CheckForWindowClose) },	// NOXREF
	//{ 0x01DD4AF0, "_ZN8CCSTutor21CheckForContentUpdateEv", mfunc_ptr_cast(&CCSTutor::CheckForContentUpdate) },	// NOXREF
	//{ 0x01DD43E0, "_ZN8CCSTutor36HasCurrentWindowBeenActiveLongEnoughEf", mfunc_ptr_cast(&CCSTutor::HasCurrentWindowBeenActiveLongEnough) },	// NOXREF
	{ 0x01DD4540, "_ZN8CCSTutor32CheckForInterruptingMessageEventEf", mfunc_ptr_cast(&CCSTutor::CheckForInterruptingMessageEvent) },
	{ 0x01DD4D80, "_ZN8CCSTutor22CheckForInactiveEventsEf", mfunc_ptr_cast(&CCSTutor::CheckForInactiveEvents) },
	{ 0x01DD5020, "_ZN8CCSTutor11CancelEventE14TutorMessageID", mfunc_ptr_cast(&CCSTutor::CancelEvent) },
	//{ 0x01DD4C90, "_ZN8CCSTutor26ProcessShownDeathsForEventEP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::ProcessShownDeathsForEvent) },	// NOXREF
	//{ 0x01DDB520, "_ZN8CCSTutor19TransferDeathEventsEP17TutorMessageEventS1_", mfunc_ptr_cast(&CCSTutor::TransferDeathEvents) },	// NOXREF
	{ 0x01DD4CC0, "_ZN8CCSTutor26GetTutorMessageUpdateEventEv", mfunc_ptr_cast(&CCSTutor::GetTutorMessageUpdateEvent) },
	{ 0x01DD4D10, "_ZN8CCSTutor33GetDuplicateMessagesFromEventListERP17TutorMessageEventS2_", mfunc_ptr_cast(&CCSTutor::GetDuplicateMessagesFromEventList) },
	//{ 0x01DDB390, "_ZN8CCSTutor9IsBombMapEv", mfunc_ptr_cast(&CCSTutor::IsBombMap) },	// NOXREF
	//{ 0x01DDB370, "_ZN8CCSTutor12IsHostageMapEv", mfunc_ptr_cast(&CCSTutor::IsHostageMap) },	// NOXREF
	//{ 0x01DD6460, "_ZN8CCSTutor17HandleWeaponFiredEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleWeaponFired) },	// NOXREF
	{ 0x01DD64A0, "_ZN8CCSTutor24HandleWeaponFiredOnEmptyEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleWeaponFiredOnEmpty) },
	//{ 0x01DD65A0, "_ZN8CCSTutor20HandleWeaponReloadedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleWeaponReloaded) },	// NOXREF
	{ 0x01DD65E0, "_ZN8CCSTutor16HandlePlayerDiedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandlePlayerDied) },
	//{ 0x01DD6F90, "_ZN8CCSTutor19HandlePlayerSpawnedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandlePlayerSpawned) },	// NOXREF
	//{ 0x01DD7040, "_ZN8CCSTutor25HandleClientCorpseSpawnedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleClientCorpseSpawned) },	// NOXREF
	{ 0x01DD6D60, "_ZN8CCSTutor22HandlePlayerTookDamageEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandlePlayerTookDamage) },
	//{ 0x01DD6EE0, "_ZN8CCSTutor30HandlePlayerBlindedByFlashbangEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandlePlayerBlindedByFlashbang) },	// NOXREF
	//{ 0x01DD7380, "_ZN8CCSTutor18HandleBuyTimeStartEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBuyTimeStart) },	// NOXREF
	//{ 0x01DD7390, "_ZN8CCSTutor23HandlePlayerLeftBuyZoneEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandlePlayerLeftBuyZone) },	// NOXREF
	//{ 0x01DD7490, "_ZN8CCSTutor17HandleBombPlantedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBombPlanted) },	// NOXREF
	{ 0x01DD75B0, "_ZN8CCSTutor17HandleBombDefusedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBombDefused) },
	//{ 0x01DD7740, "_ZN8CCSTutor18HandleBombDefusingEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBombDefusing) },	// NOXREF
	//{ 0x01DD7800, "_ZN8CCSTutor18HandleBombExplodedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBombExploded) },	// NOXREF
	{ 0x01DD7920, "_ZN8CCSTutor16HandleRoundStartEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRoundStart) },
	//{ 0x01DD7B30, "_ZN8CCSTutor17HandleBeingShotAtEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBeingShotAt) },	// NOXREF
	{ 0x01DD7C00, "_ZN8CCSTutor17HandleHostageUsedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleHostageUsed) },
	//{ 0x01DD7E30, "_ZN8CCSTutor20HandleHostageRescuedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleHostageRescued) },	// NOXREF
	//{ 0x01DD7FD0, "_ZN8CCSTutor24HandleAllHostagesRescuedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleAllHostagesRescued) },	// NOXREF
	//{ 0x01DD80F0, "_ZN8CCSTutor20HandleHostageDamagedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleHostageDamaged) },	// NOXREF
	{ 0x01DD81B0, "_ZN8CCSTutor19HandleHostageKilledEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleHostageKilled) },
	//{ 0x01DD8430, "_ZN8CCSTutor15HandleRoundDrawEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRoundDraw) },	// NOXREF
	//{ 0x01DD84E0, "_ZN8CCSTutor11HandleCTWinEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleCTWin) },	// NOXREF
	//{ 0x01DD8580, "_ZN8CCSTutor10HandleTWinEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleTWin) },	// NOXREF
	//{ 0x01DD8620, "_ZN8CCSTutor22HandleDeathCameraStartEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleDeathCameraStart) },	// NOXREF
	//{ 0x01DD86E0, "_ZN8CCSTutor18HandleRadioCoverMeEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioCoverMe) },	// NOXREF
	//{ 0x01DD8770, "_ZN8CCSTutor26HandleRadioYouTakeThePointEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioYouTakeThePoint) },	// NOXREF
	//{ 0x01DD8800, "_ZN8CCSTutor27HandleRadioHoldThisPositionEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioHoldThisPosition) },	// NOXREF
	//{ 0x01DD8890, "_ZN8CCSTutor22HandleRadioRegroupTeamEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioRegroupTeam) },	// NOXREF
	//{ 0x01DD8920, "_ZN8CCSTutor19HandleRadioFollowMeEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioFollowMe) },	// NOXREF
	//{ 0x01DD89B0, "_ZN8CCSTutor21HandleRadioTakingFireEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioTakingFire) },	// NOXREF
	//{ 0x01DD8A40, "_ZN8CCSTutor17HandleRadioGoGoGoEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioGoGoGo) },	// NOXREF
	//{ 0x01DD8AD0, "_ZN8CCSTutor23HandleRadioTeamFallBackEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioTeamFallBack) },	// NOXREF
	//{ 0x01DD8B60, "_ZN8CCSTutor28HandleRadioStickTogetherTeamEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioStickTogetherTeam) },	// NOXREF
	//{ 0x01DD8BF0, "_ZN8CCSTutor31HandleRadioGetInPositionAndWaitEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioGetInPositionAndWait) },	// NOXREF
	//{ 0x01DD8C80, "_ZN8CCSTutor24HandleRadioStormTheFrontEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioStormTheFront) },	// NOXREF
	//{ 0x01DD8D10, "_ZN8CCSTutor23HandleRadioReportInTeamEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioReportInTeam) },	// NOXREF
	//{ 0x01DD8DA0, "_ZN8CCSTutor22HandleRadioAffirmativeEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioAffirmative) },	// NOXREF
	//{ 0x01DD8E30, "_ZN8CCSTutor23HandleRadioEnemySpottedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioEnemySpotted) },	// NOXREF
	//{ 0x01DD8EC0, "_ZN8CCSTutor21HandleRadioNeedBackupEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioNeedBackup) },	// NOXREF
	//{ 0x01DD8F50, "_ZN8CCSTutor22HandleRadioSectorClearEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioSectorClear) },	// NOXREF
	//{ 0x01DD8FE0, "_ZN8CCSTutor21HandleRadioInPositionEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioInPosition) },	// NOXREF
	//{ 0x01DD9070, "_ZN8CCSTutor22HandleRadioReportingInEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioReportingIn) },	// NOXREF
	//{ 0x01DD9100, "_ZN8CCSTutor24HandleRadioGetOutOfThereEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioGetOutOfThere) },	// NOXREF
	//{ 0x01DD9190, "_ZN8CCSTutor19HandleRadioNegativeEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioNegative) },	// NOXREF
	//{ 0x01DD9220, "_ZN8CCSTutor20HandleRadioEnemyDownEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleRadioEnemyDown) },	// NOXREF
	//{ 0x01DD7240, "_ZN8CCSTutor20HandleBuyMenuOpennedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleBuyMenuOpenned) },	// NOXREF
	//{ 0x01DD72E0, "_ZN8CCSTutor13HandleAutoBuyEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleAutoBuy) },	// NOXREF
	//{ 0x01DD92B0, "_ZN8CCSTutor23HandleNotBuyingAnythingEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNotBuyingAnything) },	// NOXREF
	//{ 0x01DD9340, "_ZN8CCSTutor28HandleNeedToBuyPrimaryWeaponEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNeedToBuyPrimaryWeapon) },	// NOXREF
	//{ 0x01DD93D0, "_ZN8CCSTutor26HandleNeedToBuyPrimaryAmmoEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNeedToBuyPrimaryAmmo) },	// NOXREF
	//{ 0x01DD9460, "_ZN8CCSTutor28HandleNeedToBuySecondaryAmmoEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNeedToBuySecondaryAmmo) },	// NOXREF
	//{ 0x01DD94F0, "_ZN8CCSTutor20HandleNeedToBuyArmorEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNeedToBuyArmor) },	// NOXREF
	//{ 0x01DD9580, "_ZN8CCSTutor24HandleNeedToBuyDefuseKitEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNeedToBuyDefuseKit) },	// NOXREF
	//{ 0x01DD9610, "_ZN8CCSTutor22HandleNeedToBuyGrenadeEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleNeedToBuyGrenade) },	// NOXREF
	//{ 0x01DD96A0, "_ZN8CCSTutor20HandleCareerTaskDoneEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutor::HandleCareerTaskDone) },	// NOXREF
	//{ 0x01DD98F0, "_ZN8CCSTutor25GetNumPlayersAliveOnTeamsERiS0_", mfunc_ptr_cast(&CCSTutor::GetNumPlayersAliveOnTeams) },	// NOXREF
	{ 0x01DD9BA0, "_ZN8CCSTutor20CheckForBombViewableEv", mfunc_ptr_cast(&CCSTutor::CheckForBombViewable) },
	//{ 0x01DD9970, "_ZN8CCSTutor27CheckForLooseWeaponViewableEv", mfunc_ptr_cast(&CCSTutor::CheckForLooseWeaponViewable) },	// NOXREF
	{ 0x01DD9A80, "_ZN8CCSTutor28CheckForLooseDefuserViewableEv", mfunc_ptr_cast(&CCSTutor::CheckForLooseDefuserViewable) },
	{ 0x01DD9F30, "_ZN8CCSTutor24CheckForBombsiteViewableEv", mfunc_ptr_cast(&CCSTutor::CheckForBombsiteViewable) },
	{ 0x01DDA1D0, "_ZN8CCSTutor18CheckForInBombZoneEv", mfunc_ptr_cast(&CCSTutor::CheckForInBombZone) },
	{ 0x01DDA340, "_ZN8CCSTutor23CheckForHostageViewableEv", mfunc_ptr_cast(&CCSTutor::CheckForHostageViewable) },
	{ 0x01DDA550, "_ZN8CCSTutor22CheckForTimeRunningOutEv", mfunc_ptr_cast(&CCSTutor::CheckForTimeRunningOut) },
	//{ 0x01DDA740, "_ZN8CCSTutor23CheckForAllHostagesDeadEv", mfunc_ptr_cast(&CCSTutor::CheckForAllHostagesDead) },	// NOXREF
	//{ 0x01DDA810, "_ZN8CCSTutor35CheckForAllHostagesFollowingSomeoneEv", mfunc_ptr_cast(&CCSTutor::CheckForAllHostagesFollowingSomeone) },	// NOXREF
	{ 0x01DDAB10, "_ZN8CCSTutor17CheckHintMessagesEf", mfunc_ptr_cast(&CCSTutor::CheckHintMessages) },
	//{ 0x01DDAC40, "_ZN8CCSTutor23CheckInGameHintMessagesEf", mfunc_ptr_cast(&CCSTutor::CheckInGameHintMessages) },	// NOXREF
	{ 0x01DDAF80, "_ZN8CCSTutor20CheckExamineMessagesEf", mfunc_ptr_cast(&CCSTutor::CheckExamineMessages) },
	{ 0x01DDAD20, "_ZN8CCSTutor20CheckForNeedToReloadEb", mfunc_ptr_cast(&CCSTutor::CheckForNeedToReload) },
	//{ 0x01DDB210, "_ZN8CCSTutor22CanLocalPlayerBuyStuffEv", mfunc_ptr_cast(&CCSTutor::CanLocalPlayerBuyStuff) },	// NOXREF
	{ 0x01DDB230, "_ZN8CCSTutor20CheckBuyZoneMessagesEv", mfunc_ptr_cast(&CCSTutor::CheckBuyZoneMessages) },
	//{ 0x01DDA2F0, "_ZN8CCSTutor23IsBombPlantedInBombsiteEP11CBaseEntity", mfunc_ptr_cast(&CCSTutor::IsBombPlantedInBombsite) },	// NOXREF
	{ 0x01DD3D30, "_ZN8CCSTutor20ReadTutorMessageFileEv", mfunc_ptr_cast(&CCSTutor::ReadTutorMessageFile) },
	//{ 0x01DD43A0, "_ZN8CCSTutor20ApplyPersistentDecayEv", mfunc_ptr_cast(&CCSTutor::ApplyPersistentDecay) },	// NOXREF
	{ 0x01DDA9A0, "_ZN8CCSTutor21GetEntityForMessageIDEiP11CBaseEntity", mfunc_ptr_cast(&CCSTutor::GetEntityForMessageID) },
	{ 0x01DDB3A0, "_ZN8CCSTutor20ResetPlayerDeathInfoEv", mfunc_ptr_cast(&CCSTutor::ResetPlayerDeathInfo) },
	{ 0x01DDB3C0, "_ZN8CCSTutor25ConstructRecentDeathsListE8TeamNamePciP17TutorMessageEvent", mfunc_ptr_cast(&CCSTutor::ConstructRecentDeathsList) },	
//TutorMessageEvent
	//virtual func
	//{ 0x01DD2A10, "_ZN17TutorMessageEventC2Eiiffi", mfunc_ptr_cast(&TutorMessageEvent::TutorMessageEvent) },
	//{ 0x01DD2A50, "_ZN17TutorMessageEventD0Ev", mfunc_ptr_cast(&TutorMessageEvent::~TutorMessageEvent) },
	//non-virtual func
	{ 0x01DD2A80, "_ZN17TutorMessageEvent8IsActiveEf", mfunc_ptr_cast(&TutorMessageEvent::IsActive) },
	//{ 0x01DD2AA0, "_ZN17TutorMessageEvent11GetPriorityEv", mfunc_ptr_cast(&TutorMessageEvent::GetPriority) },	// NOXREF
	{ 0x01DD2AB0, "_ZN17TutorMessageEvent13GetTimeActiveEf", mfunc_ptr_cast(&TutorMessageEvent::GetTimeActive) },
	{ 0x01DD2AC0, "_ZN17TutorMessageEvent17SetActivationTimeEf", mfunc_ptr_cast(&TutorMessageEvent::SetActivationTime) },
	{ 0x01DD2AD0, "_ZN17TutorMessageEvent5GetIDEv", mfunc_ptr_cast(&TutorMessageEvent::GetID) },
	//{ 0x01DD2AE0, "_ZN17TutorMessageEvent14GetDuplicateIDEv", mfunc_ptr_cast(&TutorMessageEvent::GetDuplicateID) },	// NOXREF
	{ 0x01DD2AF0, "_ZN17TutorMessageEvent7SetNextEPS_", mfunc_ptr_cast(&TutorMessageEvent::SetNext) },
	{ 0x01DD2B00, "_ZN17TutorMessageEvent7GetNextEv", mfunc_ptr_cast(&TutorMessageEvent::GetNext) },
	{ 0x01DD2B10, "_ZN17TutorMessageEvent12AddParameterEPc", mfunc_ptr_cast(&TutorMessageEvent::AddParameter) },
	//{ 0x01DD2BA0, "_ZN17TutorMessageEvent16GetNextParameterEPci", mfunc_ptr_cast(&TutorMessageEvent::GetNextParameter) },	// NOXREF
	//{ 0x01DD2BE0, "_ZN17TutorMessageEvent16GetNumParametersEv", mfunc_ptr_cast(&TutorMessageEvent::GetNumParameters) },	// NOXREF
//CBaseTutorStateSystem
	//virtual func
	//{ 0x01DD2970, "_ZN21CBaseTutorStateSystemC2Ev", mfunc_ptr_cast(&CBaseTutorStateSystem::CBaseTutorStateSystem) },
	//{ 0x01DD2980, "_ZN21CBaseTutorStateSystemD0Ev", mfunc_ptr_cast(&CBaseTutorStateSystem::~CBaseTutorStateSystem) },
	//{ 0x0, "_ZN21CBaseTutorStateSystem11UpdateStateE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBaseTutorStateSystem::UpdateState) },
	//{ 0x0, "_ZN21CBaseTutorStateSystem21GetCurrentStateStringEv", mfunc_ptr_cast(&CBaseTutorStateSystem::GetCurrentStateString) },
	//{ 0x0, "_ZN21CBaseTutorStateSystem17ConstructNewStateEi", mfunc_ptr_cast(&CBaseTutorStateSystem::ConstructNewState) },
	//non-virtual func
	//{ 0x01DD29B0, "_ZN21CBaseTutorStateSystem19GetCurrentStateTypeEv", mfunc_ptr_cast(&CBaseTutorStateSystem::GetCurrentStateType) },	// NOXREF
//CBaseTutorState
	//virtual func
	//{ 0x01DD29C0, "_ZN15CBaseTutorStateC2Ev", mfunc_ptr_cast(&CBaseTutorState::CBaseTutorState) },
	//{ 0x01DD29D0, "_ZN15CBaseTutorStateD0Ev", mfunc_ptr_cast(&CBaseTutorState::~CBaseTutorState) },
	//{ 0x0, "_ZN15CBaseTutorState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CBaseTutorState::CheckForStateTransition_) },	// PURE virt
	//{ 0x0, "_ZN15CBaseTutorState14GetStateStringEv", mfunc_ptr_cast(&CBaseTutorState::GetStateString_) },	// PURE virt
	//non-virtual func
	//{ 0x01DD2A00, "_ZN15CBaseTutorState7GetTypeEv", mfunc_ptr_cast(&CBaseTutorState::GetType) },	// NOXREF
//CCSTutorStateSystem
	//{ 0x01DD3560, "_ZN19CCSTutorStateSystemC2Ev", mfunc_ptr_cast(&CCSTutorStateSystem::CCSTutorStateSystem) },
	//virtual func
	//{ 0x01DD35B0, "_ZN19CCSTutorStateSystemD0Ev", mfunc_ptr_cast(&CCSTutorStateSystem::~CCSTutorStateSystem) },
	{ 0x01DD3620, "_ZN19CCSTutorStateSystem11UpdateStateE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutorStateSystem::UpdateState_) },
	{ 0x01DD36B0, "_ZN19CCSTutorStateSystem21GetCurrentStateStringEv", mfunc_ptr_cast(&CCSTutorStateSystem::GetCurrentStateString_) },
	{ 0x01DD36C0, "_ZN19CCSTutorStateSystem17ConstructNewStateEi", mfunc_ptr_cast(&CCSTutorStateSystem::ConstructNewState_) },
//CCSTutorUndefinedState
	//{ 0x01DD3760, "_ZN22CCSTutorUndefinedStateC2Ev", mfunc_ptr_cast(&CCSTutorUndefinedState::CCSTutorUndefinedState) },
	//{ 0x01DD3780, "_ZN22CCSTutorUndefinedStateD0Ev", mfunc_ptr_cast(&CCSTutorUndefinedState::~CCSTutorUndefinedState) },
	//virtual func
	{ 0x01DD37C0, "_ZN22CCSTutorUndefinedState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutorUndefinedState::CheckForStateTransition_) },
	{ 0x01DD3850, "_ZN22CCSTutorUndefinedState14GetStateStringEv", mfunc_ptr_cast(&CCSTutorUndefinedState::GetStateString_) },
	//non-virtual func
	//{ 0x01DD3810, "_ZN22CCSTutorUndefinedState19HandlePlayerSpawnedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutorUndefinedState::HandlePlayerSpawned) },	// NOXREF
//CCSTutorWaitingForStartState
	//{ 0x01DD3860, "_ZN28CCSTutorWaitingForStartStateC2Ev", mfunc_ptr_cast(&CCSTutorWaitingForStartState::CCSTutorWaitingForStartState) },
	//virtual func
	//{ 0x01DD3880, "_ZN28CCSTutorWaitingForStartStateD0Ev", mfunc_ptr_cast(&CCSTutorWaitingForStartState::~CCSTutorWaitingForStartState) },
	{ 0x01DD38C0, "_ZN28CCSTutorWaitingForStartState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutorWaitingForStartState::CheckForStateTransition_) },
	{ 0x01DD3910, "_ZN28CCSTutorWaitingForStartState14GetStateStringEv", mfunc_ptr_cast(&CCSTutorWaitingForStartState::GetStateString_) },
	//non-virtual func
	//{ 0x01DD3920, "_ZN28CCSTutorWaitingForStartState19HandlePlayerSpawnedEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutorWaitingForStartState::HandlePlayerSpawned) },	// NOXREF
	//{ 0x01DD3960, "_ZN28CCSTutorWaitingForStartState18HandleBuyTimeStartEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutorWaitingForStartState::HandleBuyTimeStart) },	// NOXREF
//CCSTutorBuyMenuState
	//{ 0x01DD3970, "_ZN20CCSTutorBuyMenuStateC2Ev", mfunc_ptr_cast(&CCSTutorBuyMenuState::CCSTutorBuyMenuState) },
	//virtual func
	//{ 0x01DD3990, "_ZN20CCSTutorBuyMenuStateD0Ev", mfunc_ptr_cast(&CCSTutorBuyMenuState::~CCSTutorBuyMenuState) },
	{ 0x01DD39D0, "_ZN20CCSTutorBuyMenuState23CheckForStateTransitionE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CCSTutorBuyMenuState::CheckForStateTransition_) },
	{ 0x01DD39F0, "_ZN20CCSTutorBuyMenuState14GetStateStringEv", mfunc_ptr_cast(&CCSTutorBuyMenuState::GetStateString_) },
	//non-virtual func
	//{ 0x01DD3A00, "_ZN20CCSTutorBuyMenuState16HandleRoundStartEP11CBaseEntityS1_", mfunc_ptr_cast(&CCSTutorBuyMenuState::HandleRoundStart) },	// NOXREF
	{ 0x01DD3FB0, "_ZL22ParseMessageParametersRPcP12TutorMessage", (size_t)&ParseMessageParameters },
	//{ 0x0, "", (size_t)&ConstructTutorMessage },	// NOXREF
	//{ 0x0, "", (size_t)&ReadDefaultValues },	// NOXREF

#endif // Tutor_CS_Region

#ifndef GameShr_BotProfile_Region

//BotProfile
	//{ 0x0, "", mfunc_ptr_cast(&BotProfile::BotProfile) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile7GetNameEv", mfunc_ptr_cast(&BotProfile::GetName) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile13GetAggressionEv", mfunc_ptr_cast(&BotProfile::GetAggression) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile8GetSkillEv", mfunc_ptr_cast(&BotProfile::GetSkill) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile11GetTeamworkEv", mfunc_ptr_cast(&BotProfile::GetTeamwork) },	// NOXREF

	//{ 0x0, "_ZNK10BotProfile19GetWeaponPreferenceEi", mfunc_ptr_cast(&BotProfile::GetWeaponPreference) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile27GetWeaponPreferenceAsStringEi", mfunc_ptr_cast(&BotProfile::GetWeaponPreferenceAsString) },
	//{ 0x0, "_ZNK10BotProfile24GetWeaponPreferenceCountEv", mfunc_ptr_cast(&BotProfile::GetWeaponPreferenceCount) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile20HasPrimaryPreferenceEv", mfunc_ptr_cast(&BotProfile::HasPrimaryPreference) },
	//{ 0x0, "_ZNK10BotProfile19HasPistolPreferenceEv", mfunc_ptr_cast(&BotProfile::HasPistolPreference) },
	//{ 0x0, "_ZNK10BotProfile7GetCostEv", mfunc_ptr_cast(&BotProfile::GetCost) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile7GetSkinEv", mfunc_ptr_cast(&BotProfile::GetSkin) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile12IsDifficultyE17BotDifficultyType", mfunc_ptr_cast(&BotProfile::IsDifficulty) },

	//{ 0x0, "_ZNK10BotProfile13GetVoicePitchEv", mfunc_ptr_cast(&BotProfile::GetVoicePitch) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile15GetReactionTimeEv", mfunc_ptr_cast(&BotProfile::GetReactionTime) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile14GetAttackDelayEv", mfunc_ptr_cast(&BotProfile::GetAttackDelay) },	// NOXREF
	//{ 0x0, "_ZNK10BotProfile12GetVoiceBankEv", mfunc_ptr_cast(&BotProfile::GetVoiceBank) },	// NOXREF

	{ 0x01D34E90, "_ZNK10BotProfile14IsValidForTeamE18BotProfileTeamType", mfunc_ptr_cast(&BotProfile::IsValidForTeam) },
	//{ 0x0, "_ZNK10BotProfile15PrefersSilencerEv", mfunc_ptr_cast(&BotProfile::PrefersSilencer) },	// NOXREF
	//{ 0x0, "_ZN10BotProfile7InheritEPKS_S1_", mfunc_ptr_cast(&BotProfile::Inherit) },
//BotProfileManager
	//{ 0x0, "_ZN17BotProfileManagerC2Ev", mfunc_ptr_cast(&BotProfileManager::BotProfileManager) },	// NOXREF
	//{ 0x0, "_ZN17BotProfileManagerD2Ev", mfunc_ptr_cast(&BotProfileManager::~BotProfileManager) },	// NOXREF
	//{ 0x0, "_ZN17BotProfileManager4InitEPKcPj", mfunc_ptr_cast(&BotProfileManager::Init) },
	//{ 0x0, "_ZN17BotProfileManager5ResetEv", mfunc_ptr_cast(&BotProfileManager::Reset) },
	//{ 0x0, "_ZNK17BotProfileManager10GetProfileEPKc18BotProfileTeamType", mfunc_ptr_cast(&BotProfileManager::GetProfile) },	// NOXREF
	//{ 0x0, "_ZNK17BotProfileManager14GetProfileListEv", mfunc_ptr_cast(&BotProfileManager::GetProfileList) },	// NOXREF
	{ 0x01D36070, "_ZNK17BotProfileManager16GetRandomProfileE17BotDifficultyType18BotProfileTeamType", mfunc_ptr_cast(&BotProfileManager::GetRandomProfile) },
	{ 0x01D35D90, "_ZN17BotProfileManager13GetCustomSkinEi", mfunc_ptr_cast(&BotProfileManager::GetCustomSkin) },
	{ 0x01D35DD0, "_ZN17BotProfileManager22GetCustomSkinModelnameEi", mfunc_ptr_cast(&BotProfileManager::GetCustomSkinModelname) },
	{ 0x01D35DB0, "_ZN17BotProfileManager18GetCustomSkinFnameEi", mfunc_ptr_cast(&BotProfileManager::GetCustomSkinFname) },
	//{ 0x01D35DF0, "_ZN17BotProfileManager18GetCustomSkinIndexEPKcS1_", mfunc_ptr_cast(&BotProfileManager::GetCustomSkinIndex) },	// NOXREF
	//{ 0x0, "_ZNK17BotProfileManager13GetVoiceBanksEv", mfunc_ptr_cast(&BotProfileManager::GetVoiceBanks) },	// NOXREF
	//{ 0x0, "_ZN17BotProfileManager18FindVoiceBankIndexEPKc", mfunc_ptr_cast(&BotProfileManager::FindVoiceBankIndex) },

#endif // GameShr_BotProfile_Region

#ifndef VoiceManager_Region

//CVoiceGameMgr
	//constructor/destructor func
	//{ 0x0, "_ZN13CVoiceGameMgrD0Ev", mfunc_ptr_cast(&CVoiceGameMgr::~CVoiceGameMgr) },
	//non-virtual func
	//{ 0x01DCC6F0, "_ZN13CVoiceGameMgrC2Ev", mfunc_ptr_cast(&CVoiceGameMgr::CVoiceGameMgr) },
	{ 0x01DCC740, "_ZN13CVoiceGameMgr4InitEP19IVoiceGameMgrHelperi", mfunc_ptr_cast(&CVoiceGameMgr::Init) },
	//{ 0x01DCC7D0, "_ZN13CVoiceGameMgr9SetHelperEP19IVoiceGameMgrHelper", mfunc_ptr_cast(&CVoiceGameMgr::SetHelper) },	// NOXREF
	{ 0x01DCC7E0, "_ZN13CVoiceGameMgr6UpdateEd", mfunc_ptr_cast(&CVoiceGameMgr::Update) },
	{ 0x01DCC800, "_ZN13CVoiceGameMgr15ClientConnectedEP7edict_s", mfunc_ptr_cast(&CVoiceGameMgr::ClientConnected) },
	{ 0x01DCC910, "_ZN13CVoiceGameMgr13ClientCommandEP11CBasePlayerPKc", mfunc_ptr_cast(&CVoiceGameMgr::ClientCommand) },
	{ 0x01DCC890, "_ZN13CVoiceGameMgr22PlayerHasBlockedPlayerEP11CBasePlayerS1_", mfunc_ptr_cast(&CVoiceGameMgr::PlayerHasBlockedPlayer) },
	{ 0x01DCCB10, "_ZN13CVoiceGameMgr11UpdateMasksEv", mfunc_ptr_cast(&CVoiceGameMgr::UpdateMasks) },
	{ 0x01DCCAB0, "_ZL16VoiceServerDebugPKcz", (size_t)&VoiceServerDebug },

#endif // VoiceManager_Region

#ifndef Vector_Region

	{ 0x01D71160, "_ZN8Vector2D16NormalizeInPlaceEv", mfunc_ptr_cast(&Vector2D::NormalizeInPlace) },
#ifdef _WIN32

	{ 0x01D12570, "", mfunc_ptr_cast(&Vector::Length) },
	{ 0x01D4EA30, "", mfunc_ptr_cast(&Vector::Normalize) },

#endif // _WIN32

#endif // Vector_Region

#ifndef Nav_Region

//Nav_File
	//{ 0x0, "_Z14GetBspFilenamePKc", (size_t)&GetBspFilename },
	//{ 0x0, "", (size_t)&COM_FixSlashes },	// NOXREF
	//{ 0x01D45CF0, "_Z17SaveNavigationMapPKc", (size_t)&SaveNavigationMap },
	//{ 0x01D45F80, "_Z16LoadLocationFilePKc", (size_t)&LoadLocationFile },
	//{ 0x01D46170, "_Z24SanityCheckNavigationMapPKc", (size_t)&SanityCheckNavigationMap },
	//{ 0x01D46310, "_Z17LoadNavigationMapv", (size_t)&LoadNavigationMap },
//IImprovEvent
	//virtual func
	//{ 0x0, "_ZN12IImprovEvent15OnMoveToSuccessERK6Vector", mfunc_ptr_cast(&IImprovEvent::OnMoveToSuccess) },
	//{ 0x0, "_ZN12IImprovEvent15OnMoveToFailureERK6VectorNS_17MoveToFailureTypeE", mfunc_ptr_cast(&IImprovEvent::OnMoveToFailure) },
	//{ 0x0, "_ZN12IImprovEvent8OnInjuryEf", mfunc_ptr_cast(&IImprovEvent::OnInjury) },
//CImprov
	//virtual func
	//{ 0x0, "_ZNK7CImprov7IsAliveEv", mfunc_ptr_cast(&CImprov::IsAlive) },
	//{ 0x0, "_ZN7CImprov6MoveToERK6Vector", mfunc_ptr_cast(&CImprov::MoveTo) },
	//{ 0x0, "_ZN7CImprov6LookAtERK6Vector", mfunc_ptr_cast(&CImprov::LookAt) },
	//{ 0x0, "_ZN7CImprov11ClearLookAtEv", mfunc_ptr_cast(&CImprov::ClearLookAt) },
	//{ 0x0, "_ZN7CImprov6FaceToERK6Vector", mfunc_ptr_cast(&CImprov::FaceTo) },
	//{ 0x0, "_ZN7CImprov11ClearFaceToEv", mfunc_ptr_cast(&CImprov::ClearFaceTo) },
	//{ 0x0, "_ZNK7CImprov12IsAtMoveGoalEf", mfunc_ptr_cast(&CImprov::IsAtMoveGoal) },
	//{ 0x0, "_ZNK7CImprov9HasLookAtEv", mfunc_ptr_cast(&CImprov::HasLookAt) },
	//{ 0x0, "_ZNK7CImprov9HasFaceToEv", mfunc_ptr_cast(&CImprov::HasFaceTo) },
	//{ 0x0, "_ZNK7CImprov12IsAtFaceGoalEv", mfunc_ptr_cast(&CImprov::IsAtFaceGoal) },
	//{ 0x0, "_ZNK7CImprov16IsFriendInTheWayERK6Vector", mfunc_ptr_cast<IS_FRIEND_INT_THEWAY_VECTOR>(&CImprov::IsFriendInTheWay) },
	//{ 0x0, "_ZNK7CImprov16IsFriendInTheWayEP11CBaseEntityRK6Vector", mfunc_ptr_cast<IS_FRIEND_INT_THEWAY_CBASEENTITY>(&CImprov::IsFriendInTheWay) },
	//{ 0x0, "_ZN7CImprov11MoveForwardEv", mfunc_ptr_cast(&CImprov::MoveForward) },
	//{ 0x0, "_ZN7CImprov12MoveBackwardEv", mfunc_ptr_cast(&CImprov::MoveBackward) },
	//{ 0x0, "_ZN7CImprov10StrafeLeftEv", mfunc_ptr_cast(&CImprov::StrafeLeft) },
	//{ 0x0, "_ZN7CImprov11StrafeRightEv", mfunc_ptr_cast(&CImprov::StrafeRight) },
	//{ 0x0, "_ZN7CImprov4JumpEv", mfunc_ptr_cast(&CImprov::Jump) },
	//{ 0x0, "_ZN7CImprov6CrouchEv", mfunc_ptr_cast(&CImprov::Crouch) },
	//{ 0x0, "_ZN7CImprov7StandUpEv", mfunc_ptr_cast(&CImprov::StandUp) },
	//{ 0x0, "_ZN7CImprov9TrackPathERK6Vectorf", mfunc_ptr_cast(&CImprov::TrackPath) },
	//{ 0x0, "_ZN7CImprov11StartLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_", mfunc_ptr_cast(&CImprov::StartLadder) },
	//{ 0x0, "_ZN7CImprov14TraverseLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_f", mfunc_ptr_cast(&CImprov::TraverseLadder) },
	//{ 0x0, "_ZN7CImprov30GetSimpleGroundHeightWithFloorEPK6VectorPfPS0_", mfunc_ptr_cast(&CImprov::GetSimpleGroundHeightWithFloor) },
	//{ 0x0, "_ZN7CImprov3RunEv", mfunc_ptr_cast(&CImprov::Run) },
	//{ 0x0, "_ZN7CImprov4WalkEv", mfunc_ptr_cast(&CImprov::Walk) },
	//{ 0x0, "_ZN7CImprov4StopEv", mfunc_ptr_cast(&CImprov::Stop) },
	//{ 0x0, "_ZNK7CImprov12GetMoveAngleEv", mfunc_ptr_cast(&CImprov::GetMoveAngle) },
	//{ 0x0, "_ZNK7CImprov12GetFaceAngleEv", mfunc_ptr_cast(&CImprov::GetFaceAngle) },
	//{ 0x0, "_ZNK7CImprov7GetFeetEv", mfunc_ptr_cast(&CImprov::GetFeet) },
	//{ 0x0, "_ZNK7CImprov11GetCentroidEv", mfunc_ptr_cast(&CImprov::GetCentroid) },
	//{ 0x0, "_ZNK7CImprov7GetEyesEv", mfunc_ptr_cast(&CImprov::GetEyes) },
	//{ 0x0, "_ZNK7CImprov9IsRunningEv", mfunc_ptr_cast(&CImprov::IsRunning) },
	//{ 0x0, "_ZNK7CImprov9IsWalkingEv", mfunc_ptr_cast(&CImprov::IsWalking) },
	//{ 0x0, "_ZNK7CImprov9IsStoppedEv", mfunc_ptr_cast(&CImprov::IsStopped) },
	//{ 0x0, "_ZNK7CImprov11IsCrouchingEv", mfunc_ptr_cast(&CImprov::IsCrouching) },
	//{ 0x0, "_ZNK7CImprov9IsJumpingEv", mfunc_ptr_cast(&CImprov::IsJumping) },
	//{ 0x0, "_ZNK7CImprov13IsUsingLadderEv", mfunc_ptr_cast(&CImprov::IsUsingLadder) },
	//{ 0x0, "_ZNK7CImprov10IsOnGroundEv", mfunc_ptr_cast(&CImprov::IsOnGround) },
	//{ 0x0, "_ZNK7CImprov8IsMovingEv", mfunc_ptr_cast(&CImprov::IsMoving) },
	//{ 0x0, "_ZNK7CImprov6CanRunEv", mfunc_ptr_cast(&CImprov::CanRun) },
	//{ 0x0, "_ZNK7CImprov9CanCrouchEv", mfunc_ptr_cast(&CImprov::CanCrouch) },
	//{ 0x0, "_ZNK7CImprov7CanJumpEv", mfunc_ptr_cast(&CImprov::CanJump) },
	//{ 0x0, "_ZNK7CImprov9IsVisibleERK6Vectorb", mfunc_ptr_cast(&CImprov::IsVisible) },
	//{ 0x0, "_ZNK7CImprov19IsPlayerLookingAtMeEP11CBasePlayerf", mfunc_ptr_cast(&CImprov::IsPlayerLookingAtMe) },
	//{ 0x0, "_ZNK7CImprov22IsAnyPlayerLookingAtMeEif", mfunc_ptr_cast(&CImprov::IsAnyPlayerLookingAtMe) },
	//{ 0x0, "_ZNK7CImprov32GetClosestPlayerByTravelDistanceEiPf", mfunc_ptr_cast(&CImprov::GetClosestPlayerByTravelDistance) },
	//{ 0x0, "_ZNK7CImprov16GetLastKnownAreaEv", mfunc_ptr_cast(&CImprov::GetLastKnownArea) },
	//{ 0x0, "_ZN7CImprov8OnUpdateEf", mfunc_ptr_cast(&CImprov::OnUpdate) },
	//{ 0x0, "_ZN7CImprov8OnUpkeepEf", mfunc_ptr_cast(&CImprov::OnUpkeep) },
	//{ 0x0, "_ZN7CImprov7OnResetEv", mfunc_ptr_cast(&CImprov::OnReset) },
	//{ 0x0, "_ZN7CImprov11OnGameEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CImprov::OnGameEvent) },
	//{ 0x0, "_ZN7CImprov7OnTouchEP11CBaseEntity", mfunc_ptr_cast(&CImprov::OnTouch) },
//CNavNode
	//{ 0x0, "", mfunc_ptr_cast(&CNavNode::CNavNode) },
	//{ 0x0, "_ZN8CNavNode7GetNodeEPK6Vector", mfunc_ptr_cast(&CNavNode::GetNode) },
	//{ 0x0, "_ZNK8CNavNode16GetConnectedNodeE10NavDirType", mfunc_ptr_cast(&CNavNode::GetConnectedNode) },
	//{ 0x0, "_ZNK8CNavNode11GetPositionEv", mfunc_ptr_cast(&CNavNode::GetPosition) },
	//{ 0x0, "_ZNK8CNavNode9GetNormalEv", mfunc_ptr_cast(&CNavNode::GetNormal) },
	//{ 0x0, "_ZNK8CNavNode5GetIDEv", mfunc_ptr_cast(&CNavNode::GetID) },
	//{ 0x0, "_ZN8CNavNode8GetFirstEv", mfunc_ptr_cast(&CNavNode::GetFirst) },
	//{ 0x0, "_ZN8CNavNode13GetListLengthEv", mfunc_ptr_cast(&CNavNode::GetListLength) },
	//{ 0x0, "_ZN8CNavNode7GetNextEv", mfunc_ptr_cast(&CNavNode::GetNext) },
	//{ 0x0, "_ZN8CNavNode9ConnectToEPS_10NavDirType", mfunc_ptr_cast(&CNavNode::ConnectTo) },
	//{ 0x0, "_ZNK8CNavNode9GetParentEv", mfunc_ptr_cast(&CNavNode::GetParent) },
	//{ 0x0, "_ZN8CNavNode13MarkAsVisitedE10NavDirType", mfunc_ptr_cast(&CNavNode::MarkAsVisited) },
	//{ 0x0, "_ZN8CNavNode10HasVisitedE10NavDirType", mfunc_ptr_cast(&CNavNode::HasVisited) },
	//{ 0x0, "_ZNK8CNavNode10IsBiLinkedE10NavDirType", mfunc_ptr_cast(&CNavNode::IsBiLinked) },
	//{ 0x0, "_ZNK8CNavNode12IsClosedCellEv", mfunc_ptr_cast(&CNavNode::IsClosedCell) },
	//{ 0x0, "_ZN8CNavNode5CoverEv", mfunc_ptr_cast(&CNavNode::Cover) },
	//{ 0x0, "_ZNK8CNavNode9IsCoveredEv", mfunc_ptr_cast(&CNavNode::IsCovered) },
	//{ 0x0, "_ZN8CNavNode10AssignAreaEP8CNavArea", mfunc_ptr_cast(&CNavNode::AssignArea) },
	//{ 0x0, "_ZNK8CNavNode7GetAreaEv", mfunc_ptr_cast(&CNavNode::GetArea) },
	//{ 0x0, "_ZN8CNavNode13SetAttributesEh", mfunc_ptr_cast(&CNavNode::SetAttributes) },
	//{ 0x0, "_ZNK8CNavNode13GetAttributesEv", mfunc_ptr_cast(&CNavNode::GetAttributes) },
//CNavPath
	//{ 0x0, "", mfunc_ptr_cast(&CNavPath::CNavPath) },
	//{ 0x0, "_ZN8CNavPathixEi", mfunc_ptr_cast(&CNavPath::operator[]) },
	//{ 0x0, "_ZNK8CNavPath15GetSegmentCountEv", mfunc_ptr_cast(&CNavPath::GetSegmentCount) },
	//{ 0x0, "_ZNK8CNavPath11GetEndpointEv", mfunc_ptr_cast(&CNavPath::GetEndpoint) },
	//{ 0x0, "_ZNK8CNavPath7IsAtEndERK6Vector", mfunc_ptr_cast(&CNavPath::IsAtEnd) },
	//{ 0x0, "_ZNK8CNavPath9GetLengthEv", mfunc_ptr_cast(&CNavPath::GetLength) },
	//{ 0x0, "_ZNK8CNavPath17GetPointAlongPathEfP6Vector", mfunc_ptr_cast(&CNavPath::GetPointAlongPath) },
	//{ 0x0, "_ZNK8CNavPath24GetSegmentIndexAlongPathEf", mfunc_ptr_cast(&CNavPath::GetSegmentIndexAlongPath) },
	//{ 0x0, "_ZNK8CNavPath7IsValidEv", mfunc_ptr_cast(&CNavPath::IsValid) },
	//{ 0x0, "_ZN8CNavPath10InvalidateEv", mfunc_ptr_cast(&CNavPath::Invalidate) },
	//{ 0x0, "_ZN8CNavPath4DrawEv", mfunc_ptr_cast(&CNavPath::Draw) },
	//{ 0x0, "_ZNK8CNavPath22FindClosestPointOnPathEPK6VectoriiPS0_", mfunc_ptr_cast(&CNavPath::FindClosestPointOnPath) },
	//{ 0x0, "_ZN8CNavPath8OptimizeEv", mfunc_ptr_cast(&CNavPath::Optimize) },
	//{ 0x0, "_ZN8CNavPath20ComputePathPositionsEv", mfunc_ptr_cast(&CNavPath::ComputePathPositions) },
	//{ 0x0, "_ZN8CNavPath16BuildTrivialPathEPK6VectorS2_", mfunc_ptr_cast(&CNavPath::BuildTrivialPath) },
	//{ 0x0, "_ZN8CNavPath20FindNextOccludedNodeEi", mfunc_ptr_cast(&CNavPath::FindNextOccludedNode) },
//CStuckMonitor
	//{ 0x0, "", mfunc_ptr_cast(&CStuckMonitor::CStuckMonitor) },
	//{ 0x0, "_ZN13CStuckMonitor5ResetEv", mfunc_ptr_cast(&CStuckMonitor::Reset) },
	//{ 0x0, "_ZN13CStuckMonitor6UpdateEP7CImprov", mfunc_ptr_cast(&CStuckMonitor::Update) },
	//{ 0x0, "_ZNK13CStuckMonitor7IsStuckEv", mfunc_ptr_cast(&CStuckMonitor::IsStuck) },
	//{ 0x0, "_ZNK13CStuckMonitor11GetDurationEv", mfunc_ptr_cast(&CStuckMonitor::GetDuration) },
//CNavPathFollower
	//{ 0x0, "", mfunc_ptr_cast(&CNavPathFollower::CNavPathFollower) },
	//{ 0x0, "_ZN16CNavPathFollower9SetImprovEP7CImprov", mfunc_ptr_cast(&CNavPathFollower::SetImprov) },
	//{ 0x0, "_ZN16CNavPathFollower7SetPathEP8CNavPath", mfunc_ptr_cast(&CNavPathFollower::SetPath) },
	//{ 0x0, "_ZN16CNavPathFollower5ResetEv", mfunc_ptr_cast(&CNavPathFollower::Reset) },
	//{ 0x0, "_ZN16CNavPathFollower6UpdateEfb", mfunc_ptr_cast(&CNavPathFollower::Update) },
	//{ 0x0, "_ZN16CNavPathFollower5DebugEb", mfunc_ptr_cast(&CNavPathFollower::Debug) },
	//{ 0x0, "_ZNK16CNavPathFollower7IsStuckEv", mfunc_ptr_cast(&CNavPathFollower::IsStuck) },
	//{ 0x0, "_ZN16CNavPathFollower10ResetStuckEv", mfunc_ptr_cast(&CNavPathFollower::ResetStuck) },
	//{ 0x0, "_ZNK16CNavPathFollower16GetStuckDurationEv", mfunc_ptr_cast(&CNavPathFollower::GetStuckDuration) },
	//{ 0x0, "_ZN16CNavPathFollower22FeelerReflexAdjustmentEP6Vectorf", mfunc_ptr_cast(&CNavPathFollower::FeelerReflexAdjustment) },
	//{ 0x0, "_ZNK16CNavPathFollower21FindOurPositionOnPathEP6Vectorb", mfunc_ptr_cast(&CNavPathFollower::FindOurPositionOnPath) },
	//{ 0x0, "_ZN16CNavPathFollower13FindPathPointEfP6VectorPi", mfunc_ptr_cast(&CNavPathFollower::FindPathPoint) },
//HidingSpot
	//{ 0x0, "", mfunc_ptr_cast<HIDING_SPOT_VOID>(&HidingSpot::HidingSpot) },
	//{ 0x0, "", mfunc_ptr_cast<HIDING_SPOT_VECTOR>(&HidingSpot::HidingSpot) },
	//{ 0x0, "_ZNK10HidingSpot4SaveEij", mfunc_ptr_cast(&HidingSpot::Save) },
	//{ 0x0, "_ZN10HidingSpot4LoadEP9SteamFilej", mfunc_ptr_cast(&HidingSpot::Load) },
//CNavArea
	//{ 0x01D44F80, "_ZN8CNavArea4SaveEij", mfunc_ptr_cast<SAVE_FD>(&CNavArea::Save) },
	//{ 0x0, "_ZNK8CNavArea4SaveEP8_IO_FILE", mfunc_ptr_cast<SAVE_FILE>(&CNavArea::Save) },
	//{ 0x0, "", mfunc_ptr_cast<CNAV_AREA_VOID>(&CNavArea::CNavArea) },
	//{ 0x0, "", mfunc_ptr_cast<CNAV_AREA_TWO_VECTOR>(&CNavArea::CNavArea) },
	//{ 0x0, "", mfunc_ptr_cast<CNAV_AREA_VECTOR>(&CNavArea::CNavArea) },
	//{ 0x0, "", mfunc_ptr_cast<CNAV_AREA_NAVNODE>(&CNavArea::CNavArea) },
	//{ 0x01D386A0, "", mfunc_ptr_cast(&CNavArea::~CNavArea) },
	//{ 0x0, "_ZN8CNavArea10InitializeEv", mfunc_ptr_cast(&CNavArea::Initialize) },
	//{ 0x01D388A0, "_ZN8CNavArea15OnDestroyNotifyEPS_", mfunc_ptr_cast(&CNavArea::OnDestroyNotify) },		// NOXREF
	//{ 0x0, "_ZN8CNavArea9ConnectToEPS_10NavDirType", mfunc_ptr_cast(&CNavArea::ConnectTo) },
	//{ 0x01D389D0, "_ZN8CNavArea10DisconnectEPS_", mfunc_ptr_cast(&CNavArea::Disconnect) },		// NOXREF
	//{ 0x0, "_ZN8CNavArea11FinishMergeEPS_", mfunc_ptr_cast(&CNavArea::FinishMerge) },
	//{ 0x0, "_ZN8CNavArea24MergeAdjacentConnectionsEPS_", mfunc_ptr_cast(&CNavArea::MergeAdjacentConnections) },
	//{ 0x01D38D70, "_ZN8CNavArea11AssignNodesEPS_", mfunc_ptr_cast(&CNavArea::AssignNodes) },
	//{ 0x0, "_ZN8CNavArea9SplitEditEbfPPS_S1_", mfunc_ptr_cast(&CNavArea::SplitEdit) },
	//{ 0x01D390F0, "_ZNK8CNavArea11IsConnectedEPKS_10NavDirType", mfunc_ptr_cast(&CNavArea::IsConnected) },
	//{ 0x0, "_ZN8CNavArea19ComputeHeightChangeEPKS_", mfunc_ptr_cast(&CNavArea::ComputeHeightChange) },
	//{ 0x0, "_ZN8CNavArea15FinishSplitEditEPS_10NavDirType", mfunc_ptr_cast(&CNavArea::FinishSplitEdit) },
	//{ 0x0, "_ZN8CNavArea10SpliceEditEPS_", mfunc_ptr_cast(&CNavArea::SpliceEdit) },
	//{ 0x0, "_ZN8CNavArea9MergeEditEPS_", mfunc_ptr_cast(&CNavArea::MergeEdit) },
	//{ 0x0, "_ZN8CNavArea5StripEv", mfunc_ptr_cast(&CNavArea::Strip) },
	//{ 0x0, "_ZNK8CNavArea13IsOverlappingEPK6Vector", mfunc_ptr_cast<OVERLAP_VECTOR>(&CNavArea::IsOverlapping) },
	//{ 0x0, "_ZNK8CNavArea13IsOverlappingEPKS_", mfunc_ptr_cast<OVERLAP_CNAV>(&CNavArea::IsOverlapping) },
	//{ 0x0, "_ZNK8CNavArea14IsOverlappingXEPKS_", mfunc_ptr_cast(&CNavArea::IsOverlappingX) },
	//{ 0x0, "_ZNK8CNavArea14IsOverlappingYEPKS_", mfunc_ptr_cast(&CNavArea::IsOverlappingY) },
	//{ 0x01D3C7C0, "_ZNK8CNavArea8ContainsEPK6Vector", mfunc_ptr_cast(&CNavArea::Contains) },
	//{ 0x0, "_ZNK8CNavArea10IsCoplanarEPKS_", mfunc_ptr_cast(&CNavArea::IsCoplanar) },
	//!@{ 0x01D3CA60, "_ZNK8CNavArea4GetZEPK6Vector", mfunc_ptr_cast<GETZ_VECTOR>(&CNavArea::GetZ) }, // Used refs
	//{ 0x0, "_ZNK8CNavArea4GetZEff", mfunc_ptr_cast<GETZ_TWO_FLOAT>(&CNavArea::GetZ) },
	{ 0x01D3CB80, "_ZNK8CNavArea21GetClosestPointOnAreaEPK6VectorPS0_", mfunc_ptr_cast(&CNavArea::GetClosestPointOnArea) },
	//{ 0x0, "_ZNK8CNavArea25GetDistanceSquaredToPointEPK6Vector", mfunc_ptr_cast(&CNavArea::GetDistanceSquaredToPoint) },
	//{ 0x0, "_ZNK8CNavArea21GetRandomAdjacentAreaE10NavDirType", mfunc_ptr_cast(&CNavArea::GetRandomAdjacentArea) },
	//{ 0x0, "_ZNK8CNavArea13ComputePortalEPKS_10NavDirTypeP6VectorPf", mfunc_ptr_cast(&CNavArea::ComputePortal) },
	//{ 0x0, "_ZNK8CNavArea27ComputeClosestPointInPortalEPKS_10NavDirTypePK6VectorPS3_", mfunc_ptr_cast(&CNavArea::ComputeClosestPointInPortal) },
	//{ 0x0, "_ZNK8CNavArea6IsEdgeE10NavDirType", mfunc_ptr_cast(&CNavArea::IsEdge) },
	//{ 0x0, "_ZNK8CNavArea16ComputeDirectionEP6Vector", mfunc_ptr_cast(&CNavArea::ComputeDirection) },
	//{ 0x0, "_ZN8CNavArea4DrawEhhhi", mfunc_ptr_cast(&CNavArea::Draw) },
	//{ 0x0, "_ZN8CNavArea16DrawMarkedCornerE13NavCornerTypehhhi", mfunc_ptr_cast(&CNavArea::DrawMarkedCorner) },
	//{ 0x0, "_ZN8CNavArea13AddToOpenListEv", mfunc_ptr_cast(&CNavArea::AddToOpenList) },
	//{ 0x0, "_ZN8CNavArea16UpdateOnOpenListEv", mfunc_ptr_cast(&CNavArea::UpdateOnOpenList) },
	//{ 0x01D3DBC0, "_ZN8CNavArea18RemoveFromOpenListEv", mfunc_ptr_cast(&CNavArea::RemoveFromOpenList) },
	//{ 0x0, "_ZN8CNavArea16ClearSearchListsEv", mfunc_ptr_cast(&CNavArea::ClearSearchLists) },
	//{ 0x0, "_ZNK8CNavArea9GetCornerE13NavCornerType", mfunc_ptr_cast(&CNavArea::GetCorner) },
	//{ 0x0, "_ZNK8CNavArea21IsHidingSpotCollisionEPK6Vector", mfunc_ptr_cast(&CNavArea::IsHidingSpotCollision) },
	//{ 0x0, "_ZN8CNavArea18ComputeHidingSpotsEv", mfunc_ptr_cast(&CNavArea::ComputeHidingSpots) },
	//{ 0x0, "_ZN8CNavArea18ComputeSniperSpotsEv", mfunc_ptr_cast(&CNavArea::ComputeSniperSpots) },
	//{ 0x0, "_ZN8CNavArea16GetSpotEncounterEPKS_S1_", mfunc_ptr_cast(&CNavArea::GetSpotEncounter) },
	//{ 0x0, "_ZN8CNavArea17AddSpotEncountersEPKS_10NavDirTypeS1_S2_", mfunc_ptr_cast(&CNavArea::AddSpotEncounters) },
	//{ 0x0, "_ZN8CNavArea21ComputeSpotEncountersEv", mfunc_ptr_cast(&CNavArea::ComputeSpotEncounters) },
	//{ 0x0, "_ZN8CNavArea11DecayDangerEv", mfunc_ptr_cast(&CNavArea::DecayDanger) },
	//{ 0x0, "_ZN8CNavArea14IncreaseDangerEif", mfunc_ptr_cast(&CNavArea::IncreaseDanger) },
	//{ 0x0, "_ZN8CNavArea9GetDangerEi", mfunc_ptr_cast(&CNavArea::GetDanger) },
	//{ 0x0, "_ZNK8CNavArea14GetPlayerCountEiP11CBasePlayer", mfunc_ptr_cast(&CNavArea::GetPlayerCount) },
	//{ 0x01D40340, "_ZN8CNavArea18DrawConnectedAreasEv", mfunc_ptr_cast(&CNavArea::DrawConnectedAreas) },
	//{ 0x0, "_ZN8CNavArea11RaiseCornerE13NavCornerTypei", mfunc_ptr_cast(&CNavArea::RaiseCorner) },
	//{ 0x0, "_ZN8CNavArea20ComputeApproachAreasEv", mfunc_ptr_cast(&CNavArea::ComputeApproachAreas) },
	//{ 0x0, "", mfunc_ptr_cast(&CollectHidingSpotsFunctor::CollectHidingSpotsFunctor) },
	//{ 0x0, "_ZN25CollectHidingSpotsFunctor10RemoveSpotEi", mfunc_ptr_cast(&CollectHidingSpotsFunctor::RemoveSpot) },
	//{ 0x0, "", mfunc_ptr_cast(&CNavAreaGrid::CNavAreaGrid) },
	//{ 0x0, "", mfunc_ptr_cast(&CNavAreaGrid::~CNavAreaGrid) },
	//{ 0x01D43180, "_ZN12CNavAreaGrid5ResetEv", mfunc_ptr_cast(&CNavAreaGrid::Reset) },	// NOXREF
	//{ 0x0, "_ZN12CNavAreaGrid10InitializeEffff", mfunc_ptr_cast(&CNavAreaGrid::Initialize) },
	//{ 0x0, "_ZN12CNavAreaGrid10AddNavAreaEP8CNavArea", mfunc_ptr_cast(&CNavAreaGrid::AddNavArea) },
	//{ 0x01D43560, "_ZN12CNavAreaGrid13RemoveNavAreaEP8CNavArea", mfunc_ptr_cast(&CNavAreaGrid::RemoveNavArea) },
	//!@{ 0x01D43710, "_ZNK12CNavAreaGrid10GetNavAreaEPK6Vectorf", mfunc_ptr_cast(&CNavAreaGrid::GetNavArea) },	// Used refs
	//!@{ 0x01D43860, "_ZNK12CNavAreaGrid17GetNearestNavAreaEPK6Vectorb", mfunc_ptr_cast(&CNavAreaGrid::GetNearestNavArea) },	// Used refs
	//{ 0x0, "_ZNK12CNavAreaGrid14GetNavAreaByIDEj", mfunc_ptr_cast(&CNavAreaGrid::GetNavAreaByID) },
	{ 0x01D439F0, "_ZNK12CNavAreaGrid8GetPlaceEPK6Vector", mfunc_ptr_cast(&CNavAreaGrid::GetPlace) },
	//{ 0x0, "_Z19IsHidingSpotInCoverPK6Vector", (size_t)&IsHidingSpotInCover },
	//{ 0x0, "_Z18ClassifySniperSpotP10HidingSpot", (size_t)&ClassifySniperSpot },
	//{ 0x0, "", (size_t)&buildGoodSizedList },	// NOXREF
	{ 0x01D37CF0, "_Z18DestroyHidingSpotsv", (size_t)&DestroyHidingSpots },
	//{ 0x01D40920, "_Z12EditNavAreas14NavEditCmdType", (size_t)&EditNavAreas },
	{ 0x01D42540, "_Z15GetGroundHeightPK6VectorPfPS_", (size_t)&GetGroundHeight },
	//{ 0x0, "_Z21GetSimpleGroundHeightPK6VectorPfPS_", (size_t)&GetSimpleGroundHeight },
	//{ 0x0, "", (size_t)&IsAreaVisible },	// NOXREF
	//{ 0x01D40250, "_Z13GetMarkedAreav", (size_t)&GetMarkedArea },
	//{ 0x01D40260, "_Z17EditNavAreasResetv", (size_t)&EditNavAreasReset },	// NOXREF
	//{ 0x0, "_Z15DrawHidingSpotsPK8CNavArea", (size_t)&DrawHidingSpots },
	//{ 0x01D3EE10, "_Z20IncreaseDangerNearbyifP8CNavAreaPK6Vectorf", (size_t)&IncreaseDangerNearby },
	//{ 0x01D3F020, "_Z10DrawDangerv", (size_t)&DrawDanger },
	//{ 0x0, "_Z14IsSpotOccupiedP11CBaseEntityPK6Vector", (size_t)&IsSpotOccupied },
	//{ 0x0, "_Z20FindNearbyHidingSpotP11CBaseEntityPK6VectorP8CNavAreafbb", (size_t)&FindNearbyHidingSpot },
	//{ 0x01D187B0, "_Z21FindNearbyRetreatSpotP11CBaseEntityPK6VectorP8CNavAreafib", mfunc_ptr_cast<FIND_SPOT_CBASE>(&FindNearbyRetreatSpot) },
	//{ 0x0, "_Z20IsCrossingLineOfFireRK6VectorS1_P11CBaseEntityi", (size_t)&IsCrossingLineOfFire },
	//{ 0x0, "_Z20FindRandomHidingSpotP11CBaseEntityjb", (size_t)&FindRandomHidingSpot },
	//{ 0x01D37FB0, "_Z17GetHidingSpotByIDj", (size_t)&GetHidingSpotByID },
	{ 0x01D39F30, "_Z24ApproachAreaAnalysisPrepv", (size_t)&ApproachAreaAnalysisPrep },
	{ 0x01D39FD0, "_Z31CleanupApproachAreaAnalysisPrepv", (size_t)&CleanupApproachAreaAnalysisPrep },
	//{ 0x01D3A010, "_Z14DestroyLaddersv", (size_t)&DestroyLadders },	// NOXREF
	//{ 0x01D3A060, "_Z20DestroyNavigationMapv", (size_t)&DestroyNavigationMap },
	//!@{ 0x01D3A210, "_Z20StripNavigationAreasv", (size_t)&StripNavigationAreas },
	//{ 0x0, "", (size_t)&FindFirstAreaInDirection },	// NOXREF
	//{ 0x0, "", (size_t)&testJumpDown },	// NOXREF
	//{ 0x0, "", (size_t)&findJumpDownArea },	// NOXREF
	//{ 0x0, "_Z21ConnectGeneratedAreasv", (size_t)&ConnectGeneratedAreas },
	//{ 0x0, "_Z19MergeGeneratedAreasv", (size_t)&MergeGeneratedAreas },
	//{ 0x0, "", (size_t)&IsAreaRoughlySquare },	// NOXREF
	//{ 0x0, "_Z6SplitXP8CNavArea", (size_t)&SplitX },
	//{ 0x0, "_Z6SplitYP8CNavArea", (size_t)&SplitY },
	//{ 0x0, "_Z13SquareUpAreasv", (size_t)&SquareUpAreas },
	//{ 0x0, "_Z8TestAreaP8CNavNodeii", (size_t)&TestArea },
	//{ 0x0, "_Z9BuildAreaP8CNavNodeii", (size_t)&BuildArea },
	//{ 0x0, "_Z12BuildLaddersv", (size_t)&BuildLadders },
	//{ 0x0, "_Z13MarkJumpAreasv", (size_t)&MarkJumpAreas },
	//{ 0x0, "_Z26GenerateNavigationAreaMeshv", (size_t)&GenerateNavigationAreaMesh },

#endif // Nav_Region

#ifndef Hostage_Region

//HostageState
	//{ 0x01D50DA0, "", mfunc_ptr_cast(&CHostageImprov::CHostageImprov) },
	//virtual func
	//{ 0x0, "_ZN14CHostageImprov15OnMoveToSuccessERK6Vector", mfunc_ptr_cast(&CHostageImprov::OnMoveToSuccess_) },
	//{ 0x0, "_ZN14CHostageImprov15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", mfunc_ptr_cast(&CHostageImprov::OnMoveToFailure_) },
	//{ 0x0, "_ZN14CHostageImprov8OnInjuryEf", mfunc_ptr_cast(&CHostageImprov::OnInjury_) },
	//{ 0x01D51040, "_ZNK14CHostageImprov7IsAliveEv", mfunc_ptr_cast(&CHostageImprov::IsAlive_) },
	//{ 0x0, "_ZN14CHostageImprov6MoveToERK6Vector", mfunc_ptr_cast(&CHostageImprov::MoveTo_) },
	//{ 0x0, "_ZN14CHostageImprov6LookAtERK6Vector", mfunc_ptr_cast(&CHostageImprov::LookAt_) },
	//{ 0x0, "_ZN14CHostageImprov11ClearLookAtEv", mfunc_ptr_cast(&CHostageImprov::ClearLookAt_) },
	//{ 0x0, "_ZN14CHostageImprov6FaceToERK6Vector", mfunc_ptr_cast(&CHostageImprov::FaceTo_) },
	//{ 0x0, "_ZN14CHostageImprov11ClearFaceToEv", mfunc_ptr_cast(&CHostageImprov::ClearFaceTo_) },
	//{ 0x0, "_ZNK14CHostageImprov12IsAtMoveGoalEf", mfunc_ptr_cast(&CHostageImprov::IsAtMoveGoal_) },
	//{ 0x0, "_ZNK14CHostageImprov9HasLookAtEv", mfunc_ptr_cast(&CHostageImprov::HasLookAt_) },
	//{ 0x0, "_ZNK14CHostageImprov9HasFaceToEv", mfunc_ptr_cast(&CHostageImprov::HasFaceTo_) },
	//{ 0x0, "_ZNK14CHostageImprov12IsAtFaceGoalEv", mfunc_ptr_cast(&CHostageImprov::IsAtFaceGoal_) },
	//{ 0x0, "_ZNK14CHostageImprov16IsFriendInTheWayERK6Vector", mfunc_ptr_cast<IS_FRIEND_IN_THE_WAY_VECTOR>(&CHostageImprov::IsFriendInTheWay_) },
	//{ 0x0, "_ZNK14CHostageImprov16IsFriendInTheWayEP11CBaseEntityRK6Vector", mfunc_ptr_cast<IS_FRIEND_IN_THE_WAY_CBASE>(&CHostageImprov::IsFriendInTheWay_) },
	//{ 0x0, "_ZN14CHostageImprov11MoveForwardEv", mfunc_ptr_cast(&CHostageImprov::MoveForward_) },
	//{ 0x0, "_ZN14CHostageImprov12MoveBackwardEv", mfunc_ptr_cast(&CHostageImprov::MoveBackward_) },
	//{ 0x0, "_ZN14CHostageImprov10StrafeLeftEv", mfunc_ptr_cast(&CHostageImprov::StrafeLeft_) },
	//{ 0x0, "_ZN14CHostageImprov11StrafeRightEv", mfunc_ptr_cast(&CHostageImprov::StrafeRight_) },
	//{ 0x0, "_ZN14CHostageImprov4JumpEv", mfunc_ptr_cast(&CHostageImprov::Jump_) },
	//{ 0x01D56710, "_ZN14CHostageImprov6CrouchEv", mfunc_ptr_cast(&CHostageImprov::Crouch_) },
	{ 0x01D567A0, "_ZN14CHostageImprov7StandUpEv", mfunc_ptr_cast(&CHostageImprov::StandUp_) },
	//{ 0x0, "_ZN14CHostageImprov9TrackPathERK6Vectorf", mfunc_ptr_cast(&CHostageImprov::TrackPath_) },
	//{ 0x0, "_ZN14CHostageImprov11StartLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_", mfunc_ptr_cast(&CHostageImprov::StartLadder_) },
	//{ 0x0, "_ZN14CHostageImprov14TraverseLadderEPK10CNavLadder15NavTraverseTypePK6VectorS6_f", mfunc_ptr_cast(&CHostageImprov::TraverseLadder_) },
	//{ 0x01D51150, "_ZN14CHostageImprov30GetSimpleGroundHeightWithFloorEPK6VectorPfPS0_", mfunc_ptr_cast(&CHostageImprov::GetSimpleGroundHeightWithFloor_) },
	//{ 0x0, "_ZN14CHostageImprov3RunEv", mfunc_ptr_cast(&CHostageImprov::Run_) },
	//{ 0x0, "_ZN14CHostageImprov4WalkEv", mfunc_ptr_cast(&CHostageImprov::Walk_) },
	//{ 0x0, "_ZN14CHostageImprov4StopEv", mfunc_ptr_cast(&CHostageImprov::Stop_) },
	//{ 0x0, "_ZNK14CHostageImprov12GetMoveAngleEv", mfunc_ptr_cast(&CHostageImprov::GetMoveAngle_) },
	//{ 0x0, "_ZNK14CHostageImprov12GetFaceAngleEv", mfunc_ptr_cast(&CHostageImprov::GetFaceAngle_) },
	{ 0x01D523F0, "_ZNK14CHostageImprov7GetFeetEv", mfunc_ptr_cast(&CHostageImprov::GetFeet_) },
	//{ 0x01D52400, "_ZNK14CHostageImprov11GetCentroidEv", mfunc_ptr_cast(&CHostageImprov::GetCentroid_) },
	//{ 0x01D52430, "_ZNK14CHostageImprov7GetEyesEv", mfunc_ptr_cast(&CHostageImprov::GetEyes_) },
	//{ 0x0, "_ZNK14CHostageImprov9IsRunningEv", mfunc_ptr_cast(&CHostageImprov::IsRunning_) },
	//{ 0x0, "_ZNK14CHostageImprov9IsWalkingEv", mfunc_ptr_cast(&CHostageImprov::IsWalking_) },
	//{ 0x01D56CC0, "_ZNK14CHostageImprov9IsStoppedEv", mfunc_ptr_cast(&CHostageImprov::IsStopped_) },
	//{ 0x0, "_ZNK14CHostageImprov11IsCrouchingEv", mfunc_ptr_cast(&CHostageImprov::IsCrouching_) },
	//{ 0x0, "_ZNK14CHostageImprov9IsJumpingEv", mfunc_ptr_cast(&CHostageImprov::IsJumping_) },
	//{ 0x0, "_ZNK14CHostageImprov13IsUsingLadderEv", mfunc_ptr_cast(&CHostageImprov::IsUsingLadder_) },
	//{ 0x0, "_ZNK14CHostageImprov10IsOnGroundEv", mfunc_ptr_cast(&CHostageImprov::IsOnGround_) },
	//{ 0x0, "_ZNK14CHostageImprov8IsMovingEv", mfunc_ptr_cast(&CHostageImprov::IsMoving_) },
	//{ 0x0, "_ZNK14CHostageImprov6CanRunEv", mfunc_ptr_cast(&CHostageImprov::CanRun_) },
	//{ 0x0, "_ZNK14CHostageImprov9CanCrouchEv", mfunc_ptr_cast(&CHostageImprov::CanCrouch_) },
	//{ 0x0, "_ZNK14CHostageImprov7CanJumpEv", mfunc_ptr_cast(&CHostageImprov::CanJump_) },
	//{ 0x0, "_ZNK14CHostageImprov9IsVisibleERK6Vectorb", mfunc_ptr_cast(&CHostageImprov::IsVisible_) },
	//{ 0x0, "_ZNK14CHostageImprov19IsPlayerLookingAtMeEP11CBasePlayerf", mfunc_ptr_cast(&CHostageImprov::IsPlayerLookingAtMe_) },
	//{ 0x0, "_ZNK14CHostageImprov22IsAnyPlayerLookingAtMeEif", mfunc_ptr_cast(&CHostageImprov::IsAnyPlayerLookingAtMe_) },
	//{ 0x0, "_ZNK14CHostageImprov32GetClosestPlayerByTravelDistanceEiPf", mfunc_ptr_cast(&CHostageImprov::GetClosestPlayerByTravelDistance_) },
	//{ 0x01D56D60, "_ZNK14CHostageImprov16GetLastKnownAreaEv", mfunc_ptr_cast(&CHostageImprov::GetLastKnownArea_) },
	//{ 0x0, "_ZN14CHostageImprov8OnUpdateEf", mfunc_ptr_cast(&CHostageImprov::OnUpdate_) },
	//{ 0x0, "_ZN14CHostageImprov8OnUpkeepEf", mfunc_ptr_cast(&CHostageImprov::OnUpkeep_) },
	{ 0x01D52A60, "_ZN14CHostageImprov7OnResetEv", mfunc_ptr_cast(&CHostageImprov::OnReset_) },
	//{ 0x0, "_ZN14CHostageImprov11OnGameEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CHostageImprov::OnGameEvent_) },
	//{ 0x0, "_ZN14CHostageImprov7OnTouchEP11CBaseEntity", mfunc_ptr_cast(&CHostageImprov::OnTouch_) },
	//non-virtual func
	//{ 0x0, "_ZN14CHostageImprov12FaceOutwardsEv", mfunc_ptr_cast(&CHostageImprov::FaceOutwards) },
	//{ 0x0, "_ZNK14CHostageImprov16IsFriendInTheWayEv", mfunc_ptr_cast(&CHostageImprov::IsFriendInTheWay) },
	//{ 0x01D52EE0, "_ZN14CHostageImprov20SetKnownGoodPositionERK6Vector", mfunc_ptr_cast(&CHostageImprov::SetKnownGoodPosition) },	// NOXREF
	//{ 0x0, "_ZNK14CHostageImprov20GetKnownGoodPositionEv", mfunc_ptr_cast(&CHostageImprov::GetKnownGoodPosition) },
	//{ 0x0, "_ZN14CHostageImprov24ResetToKnownGoodPositionEv", mfunc_ptr_cast(&CHostageImprov::ResetToKnownGoodPosition) },
	//{ 0x0, "_ZN14CHostageImprov9ResetJumpEv", mfunc_ptr_cast(&CHostageImprov::ResetJump) },
	//{ 0x0, "_ZN14CHostageImprov10ApplyForceE6Vector", mfunc_ptr_cast(&CHostageImprov::ApplyForce) },
	//{ 0x0, "_ZNK14CHostageImprov17GetActualVelocityEv", mfunc_ptr_cast(&CHostageImprov::GetActualVelocity) },
	//{ 0x0, "_ZN14CHostageImprov12SetMoveLimitENS_8MoveTypeE", mfunc_ptr_cast(&CHostageImprov::SetMoveLimit) },
	//{ 0x0, "_ZNK14CHostageImprov12GetMoveLimitEv", mfunc_ptr_cast(&CHostageImprov::GetMoveLimit) },
	//{ 0x0, "_ZN14CHostageImprov7GetPathEv", mfunc_ptr_cast(&CHostageImprov::GetPath) },
	//{ 0x0, "_ZN14CHostageImprov15GetPathFollowerEv", mfunc_ptr_cast(&CHostageImprov::GetPathFollower) },
	//{ 0x0, "_ZN14CHostageImprov4IdleEv", mfunc_ptr_cast(&CHostageImprov::Idle) },
	//{ 0x0, "_ZNK14CHostageImprov6IsIdleEv", mfunc_ptr_cast(&CHostageImprov::IsIdle) },
	//{ 0x0, "_ZN14CHostageImprov6FollowEP11CBasePlayer", mfunc_ptr_cast(&CHostageImprov::Follow) },
	//{ 0x0, "_ZNK14CHostageImprov11IsFollowingEPK11CBaseEntity", mfunc_ptr_cast(&CHostageImprov::IsFollowing) },
	//{ 0x0, "_ZN14CHostageImprov6EscapeEv", mfunc_ptr_cast(&CHostageImprov::Escape) },
	//{ 0x0, "_ZNK14CHostageImprov10IsEscapingEv", mfunc_ptr_cast(&CHostageImprov::IsEscaping) },
	//{ 0x0, "_ZN14CHostageImprov7RetreatEv", mfunc_ptr_cast(&CHostageImprov::Retreat) },
	//{ 0x0, "_ZNK14CHostageImprov12IsRetreatingEv", mfunc_ptr_cast(&CHostageImprov::IsRetreating) },
	//{ 0x0, "_ZNK14CHostageImprov8IsAtHomeEv", mfunc_ptr_cast(&CHostageImprov::IsAtHome) },
	//{ 0x0, "_ZNK14CHostageImprov16CanSeeRescueZoneEv", mfunc_ptr_cast(&CHostageImprov::CanSeeRescueZone) },
	//{ 0x0, "_ZNK14CHostageImprov15GetFollowLeaderEv", mfunc_ptr_cast(&CHostageImprov::GetFollowLeader) },
	//{ 0x0, "_ZN14CHostageImprov23GetClosestVisiblePlayerEi", mfunc_ptr_cast(&CHostageImprov::GetClosestVisiblePlayer) },
	//{ 0x0, "_ZN14CHostageImprov25GetTimeSinceLastSawPlayerEi", mfunc_ptr_cast(&CHostageImprov::GetTimeSinceLastSawPlayer) },
	//{ 0x01D55B90, "_ZN14CHostageImprov22GetTimeSinceLastInjuryEv", mfunc_ptr_cast(&CHostageImprov::GetTimeSinceLastInjury) },	// NOXREF
	//{ 0x01D55BC0, "_ZN14CHostageImprov21GetTimeSinceLastNoiseEv", mfunc_ptr_cast(&CHostageImprov::GetTimeSinceLastNoise) },	// NOXREF
	//{ 0x01D540C0, "_ZN14CHostageImprov17IsTerroristNearbyEv", mfunc_ptr_cast(&CHostageImprov::IsTerroristNearby) },	// NOXREF
	//{ 0x0, "_ZN14CHostageImprov8FrightenENS_9ScareTypeE", mfunc_ptr_cast(&CHostageImprov::Frighten) },
	//{ 0x0, "_ZNK14CHostageImprov8IsScaredEv", mfunc_ptr_cast(&CHostageImprov::IsScared) },
	//{ 0x0, "_ZNK14CHostageImprov17GetScareIntensityEv", mfunc_ptr_cast(&CHostageImprov::GetScareIntensity) },
	//{ 0x0, "_ZNK14CHostageImprov20IsIgnoringTerroristsEv", mfunc_ptr_cast(&CHostageImprov::IsIgnoringTerrorists) },
	//{ 0x0, "_ZNK14CHostageImprov13GetAggressionEv", mfunc_ptr_cast(&CHostageImprov::GetAggression) },
	//{ 0x0, "_ZN14CHostageImprov7ChatterE18HostageChatterTypeb", mfunc_ptr_cast(&CHostageImprov::Chatter) },
	//{ 0x0, "_ZN14CHostageImprov14DelayedChatterEf18HostageChatterTypeb", mfunc_ptr_cast(&CHostageImprov::DelayedChatter) },
	//{ 0x01D55FE0, "_ZN14CHostageImprov20UpdateDelayedChatterEv", mfunc_ptr_cast(&CHostageImprov::UpdateDelayedChatter) },	// NOXREF
	//{ 0x0, "_ZNK14CHostageImprov9IsTalkingEv", mfunc_ptr_cast(&CHostageImprov::IsTalking) },
	//{ 0x0, "_ZN14CHostageImprov22UpdateGrenadeReactionsEv", mfunc_ptr_cast(&CHostageImprov::UpdateGrenadeReactions) },
	//{ 0x0, "_ZN14CHostageImprov6AfraidEv", mfunc_ptr_cast(&CHostageImprov::Afraid) },
	//{ 0x0, "_ZN14CHostageImprov4WaveEv", mfunc_ptr_cast(&CHostageImprov::Wave) },
	//{ 0x0, "_ZN14CHostageImprov5AgreeEv", mfunc_ptr_cast(&CHostageImprov::Agree) },
	//{ 0x0, "_ZN14CHostageImprov8DisagreeEv", mfunc_ptr_cast(&CHostageImprov::Disagree) },
	//{ 0x0, "_ZN14CHostageImprov9CrouchDieEv", mfunc_ptr_cast(&CHostageImprov::CrouchDie) },
	//{ 0x0, "_ZN14CHostageImprov6FlinchE8Activity", mfunc_ptr_cast(&CHostageImprov::Flinch) },
	//{ 0x01D55E20, "_ZN14CHostageImprov18UpdateIdleActivityE8ActivityS0_", mfunc_ptr_cast(&CHostageImprov::UpdateIdleActivity) },
	//{ 0x01D56910, "_ZN14CHostageImprov25UpdateStationaryAnimationEv", mfunc_ptr_cast(&CHostageImprov::UpdateStationaryAnimation) },	// NOXREF
	//{ 0x0, "_ZNK14CHostageImprov9GetEntityEv", mfunc_ptr_cast(&CHostageImprov::GetEntity) },
	//{ 0x0, "_ZN14CHostageImprov24CheckForNearbyTerroristsEv", mfunc_ptr_cast(&CHostageImprov::CheckForNearbyTerrorists) },
	//{ 0x0, "_ZN14CHostageImprov14UpdatePositionEf", mfunc_ptr_cast(&CHostageImprov::UpdatePosition) },
	//{ 0x0, "_ZN14CHostageImprov11MoveTowardsERK6Vectorf", mfunc_ptr_cast(&CHostageImprov::MoveTowards) },
	//{ 0x0, "_ZN14CHostageImprov11FaceTowardsERK6Vectorf", mfunc_ptr_cast(&CHostageImprov::FaceTowards) },
	//{ 0x0, "_ZN14CHostageImprov8GetSpeedEv", mfunc_ptr_cast(&CHostageImprov::GetSpeed) },
	//{ 0x0, "_ZN14CHostageImprov12SetMoveAngleEf", mfunc_ptr_cast(&CHostageImprov::SetMoveAngle) },
	//{ 0x01D56300, "_ZN14CHostageImprov6WiggleEv", mfunc_ptr_cast(&CHostageImprov::Wiggle) },
	//{ 0x0, "_ZN14CHostageImprov9ClearPathEv", mfunc_ptr_cast(&CHostageImprov::ClearPath) },
	//{ 0x01D511C0, "_ZN14CHostageImprov17DiscontinuityJumpEfbb", mfunc_ptr_cast(&CHostageImprov::DiscontinuityJump) },	// NOXREF
	//{ 0x0, "_ZN14CHostageImprov12UpdateVisionEv", mfunc_ptr_cast(&CHostageImprov::UpdateVision) },
//HostageState
	//virtual func
	//{ 0x0, "_ZN12HostageStateD0Ev", mfunc_ptr_cast(&HostageState::~HostageState) },
	//{ 0x0, "_ZN12HostageStateD2Ev", mfunc_ptr_cast(&HostageState::~HostageState) },
	//{ 0x0, "_ZN12HostageState25UpdateStationaryAnimationEP14CHostageImprov", mfunc_ptr_cast(&HostageState::UpdateStationaryAnimation) },
//HostageIdleState
	//virtual func
	//{ 0x0, "_ZN16HostageIdleState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageIdleState::OnEnter) },
	//{ 0x0, "_ZN16HostageIdleState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageIdleState::OnUpdate) },
	//{ 0x0, "_ZN16HostageIdleState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageIdleState::OnExit) },
	//{ 0x0, "_ZNK16HostageIdleState7GetNameEv", mfunc_ptr_cast(&HostageIdleState::GetName) },
	//{ 0x01D4BBD0, "_ZN16HostageIdleState25UpdateStationaryAnimationEP14CHostageImprov", mfunc_ptr_cast(&HostageIdleState::UpdateStationaryAnimation) },
	//{ 0x0, "_ZN16HostageIdleState15OnMoveToSuccessERK6Vector", mfunc_ptr_cast(&HostageIdleState::OnMoveToSuccess) },
	//{ 0x0, "_ZN16HostageIdleState15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", mfunc_ptr_cast(&HostageIdleState::OnMoveToFailure) },
	//{ 0x0, "_ZN16HostageIdleState8OnInjuryEf", mfunc_ptr_cast(&HostageIdleState::OnInjury) },
//HostageStateMachine
	//virtual func
	//{ 0x0, "_ZN19HostageStateMachine15OnMoveToSuccessERK6Vector", mfunc_ptr_cast(&HostageStateMachine::OnMoveToSuccess) },
	//{ 0x0, "_ZN19HostageStateMachine15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", mfunc_ptr_cast(&HostageStateMachine::OnMoveToFailure) },
	//{ 0x0, "_ZN19HostageStateMachine8OnInjuryEf", mfunc_ptr_cast(&HostageStateMachine::OnInjury) },
	//non-virtual func
	//{ 0x0, "_ZN19HostageStateMachine25UpdateStationaryAnimationEP14CHostageImprov", mfunc_ptr_cast(&HostageStateMachine::UpdateStationaryAnimation) },
//HostageEscapeToCoverState
	//virtual func
	//{ 0x0, "_ZN25HostageEscapeToCoverState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeToCoverState::OnEnter) },
	//{ 0x0, "_ZN25HostageEscapeToCoverState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeToCoverState::OnUpdate) },
	//{ 0x0, "_ZN25HostageEscapeToCoverState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeToCoverState::OnExit) },
	//{ 0x0, "_ZNK25HostageEscapeToCoverState7GetNameEv", mfunc_ptr_cast(&HostageEscapeToCoverState::GetName) },
	//{ 0x0, "_ZN25HostageEscapeToCoverState15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", mfunc_ptr_cast(&HostageEscapeToCoverState::OnMoveToFailure) },
	//non-virtual func
	//{ 0x0, "_ZN25HostageEscapeToCoverState13SetRescueGoalERK6Vector", mfunc_ptr_cast(&HostageEscapeToCoverState::SetRescueGoal) },
//HostageEscapeLookAroundState
	//virtual func
	//{ 0x0, "_ZN28HostageEscapeLookAroundState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeLookAroundState::OnEnter) },
	//{ 0x0, "_ZN28HostageEscapeLookAroundState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeLookAroundState::OnUpdate) },
	//{ 0x0, "_ZN28HostageEscapeLookAroundState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeLookAroundState::OnExit) },
	//{ 0x0, "_ZNK28HostageEscapeLookAroundState7GetNameEv", mfunc_ptr_cast(&HostageEscapeLookAroundState::GetName) },
//HostageEscapeState
	//virtual func
	//{ 0x0, "_ZN18HostageEscapeState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeState::OnEnter) },
	//{ 0x0, "_ZN18HostageEscapeState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeState::OnUpdate) },
	//{ 0x0, "_ZN18HostageEscapeState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageEscapeState::OnExit) },
	//{ 0x0, "_ZNK18HostageEscapeState7GetNameEv", mfunc_ptr_cast(&HostageEscapeState::GetName) },
	//{ 0x0, "_ZN18HostageEscapeState15OnMoveToFailureERK6VectorN12IImprovEvent17MoveToFailureTypeE", mfunc_ptr_cast(&HostageEscapeState::OnMoveToFailure) },
	//non-virtual func
	//{ 0x0, "_ZN18HostageEscapeState7ToCoverEv", mfunc_ptr_cast(&HostageEscapeState::ToCover) },
	//{ 0x0, "_ZN18HostageEscapeState10LookAroundEv", mfunc_ptr_cast(&HostageEscapeState::LookAround) },
//HostageRetreatState
	//virtual func
	//{ 0x0, "_ZN19HostageRetreatState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageRetreatState::OnEnter) },
	//{ 0x0, "_ZN19HostageRetreatState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageRetreatState::OnUpdate) },
	//{ 0x0, "_ZN19HostageRetreatState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageRetreatState::OnExit) },
	//{ 0x0, "_ZNK19HostageRetreatState7GetNameEv", mfunc_ptr_cast(&HostageRetreatState::GetName) },
//HostageFollowState
	//virtual func
	//{ 0x0, "_ZN18HostageFollowState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageFollowState::OnEnter) },
	//{ 0x0, "_ZN18HostageFollowState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageFollowState::OnUpdate) },
	//{ 0x0, "_ZN18HostageFollowState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageFollowState::OnExit) },
	//{ 0x0, "_ZNK18HostageFollowState7GetNameEv", mfunc_ptr_cast(&HostageFollowState::GetName) },
	//{ 0x0, "_ZN18HostageFollowState25UpdateStationaryAnimationEP14CHostageImprov", mfunc_ptr_cast(&HostageFollowState::UpdateStationaryAnimation) },
	//non-virtual func
	//{ 0x0, "_ZN18HostageFollowState9SetLeaderEP11CBaseEntity", mfunc_ptr_cast(&HostageFollowState::SetLeader) },
	//{ 0x0, "_ZNK18HostageFollowState9GetLeaderEv", mfunc_ptr_cast(&HostageFollowState::GetLeader) },
//HostageAnimateState
	//virtual func
	//{ 0x0, "_ZN19HostageAnimateState7OnEnterEP14CHostageImprov", mfunc_ptr_cast(&HostageAnimateState::OnEnter) },
	//{ 0x0, "_ZN19HostageAnimateState8OnUpdateEP14CHostageImprov", mfunc_ptr_cast(&HostageAnimateState::OnUpdate) },
	//{ 0x0, "_ZN19HostageAnimateState6OnExitEP14CHostageImprov", mfunc_ptr_cast(&HostageAnimateState::OnExit) },
	//{ 0x0, "_ZNK19HostageAnimateState7GetNameEv", mfunc_ptr_cast(&HostageAnimateState::GetName) },
	//non-virtual func
	{ 0x01D49D60, "_ZN19HostageAnimateState5ResetEv", mfunc_ptr_cast(&HostageAnimateState::Reset) },
	//{ 0x0, "_ZN19HostageAnimateState11AddSequenceEP14CHostageImprovPKcff", mfunc_ptr_cast<ADD_SEQUENCE_NAME>(&HostageAnimateState::AddSequence) },
	//{ 0x01D49F00, "_ZN19HostageAnimateState11AddSequenceEP14CHostageImproviff", mfunc_ptr_cast<ADD_SEQUENCE_NUMBER>(&HostageAnimateState::AddSequence) },
	//{ 0x0, "_ZNK19HostageAnimateState6IsBusyEv", mfunc_ptr_cast(&HostageAnimateState::IsBusy) },
	//{ 0x0, "_ZNK19HostageAnimateState9IsPlayingEP14CHostageImprovPKc", mfunc_ptr_cast(&HostageAnimateState::IsPlaying) },
	//{ 0x0, "_ZN19HostageAnimateState20GetCurrentSequenceIDEv", mfunc_ptr_cast(&HostageAnimateState::GetCurrentSequenceID) },	// NOXREF
	//{ 0x0, "_ZNK19HostageAnimateState14GetPerformanceEv", mfunc_ptr_cast(&HostageAnimateState::GetPerformance) },
	//{ 0x0, "_ZN19HostageAnimateState14SetPerformanceENS_15PerformanceTypeE", mfunc_ptr_cast(&HostageAnimateState::SetPerformance) },
	//{ 0x0, "_ZN19HostageAnimateState13StartSequenceEP14CHostageImprovPKNS_7SeqInfoE", mfunc_ptr_cast(&HostageAnimateState::StartSequence) },
	//{ 0x0, "_ZN19HostageAnimateState13IsDoneHoldingEv", mfunc_ptr_cast(&HostageAnimateState::IsDoneHolding) },
//CHostage
	//virtual func
	//{ 0x0, "_ZN8CHostage5SpawnEv", mfunc_ptr_cast(&CHostage::Spawn_) },
	//{ 0x0, "_ZN8CHostage8PrecacheEv", mfunc_ptr_cast(&CHostage::Precache_) },
	//{ 0x0, "_ZN8CHostage10ObjectCapsEv", mfunc_ptr_cast(&CHostage::ObjectCaps_) },
	//{ 0x0, "_ZN8CHostage8ClassifyEv", mfunc_ptr_cast(&CHostage::Classify_) },
	//{ 0x0, "_ZN8CHostage10TakeDamageEP9entvars_sS1_fi", mfunc_ptr_cast(&CHostage::TakeDamage_) },
	//{ 0x0, "_ZN8CHostage10BloodColorEv", mfunc_ptr_cast(&CHostage::BloodColor_) },
	//{ 0x0, "_ZN8CHostage5TouchEP11CBaseEntity", mfunc_ptr_cast(&CHostage::Touch_) },
	//{ 0x0, "_ZN8CHostage3UseEP11CBaseEntityS1_8USE_TYPEf", mfunc_ptr_cast(&CHostage::Use_) },
	//non-virtual func
	//{ 0x01D4C450, "_ZN8CHostage9IdleThinkEv", mfunc_ptr_cast(&CHostage::IdleThink) },	// export func
	//{ 0x0, "_ZN8CHostage6RemoveEv", mfunc_ptr_cast(&CHostage::Remove) },
	{ 0x01D4CC20, "_ZN8CHostage10RePositionEv", mfunc_ptr_cast(&CHostage::RePosition) },
	{ 0x01D4C3E0, "_ZN8CHostage11SetActivityEi", mfunc_ptr_cast(&CHostage::SetActivity) },
	//{ 0x0, "_ZN8CHostage11GetActivityEv", mfunc_ptr_cast(&CHostage::GetActivity) },
	//{ 0x0, "_ZN8CHostage17GetModifiedDamageEfi", mfunc_ptr_cast(&CHostage::GetModifiedDamage) },
	//{ 0x01D4D390, "_ZN8CHostage17SetFlinchActivityEv", mfunc_ptr_cast(&CHostage::SetFlinchActivity) },	// NOXREF
	//{ 0x0, "_ZN8CHostage16SetDeathActivityEv", mfunc_ptr_cast(&CHostage::SetDeathActivity) },
	//{ 0x01D4D310, "_ZN8CHostage13PlayPainSoundEv", mfunc_ptr_cast(&CHostage::PlayPainSound) },	// NOXREF
	//{ 0x0, "_ZN8CHostage21PlayFollowRescueSoundEv", mfunc_ptr_cast(&CHostage::PlayFollowRescueSound) },
	//{ 0x0, "_ZN8CHostage13AnnounceDeathEP11CBasePlayer", mfunc_ptr_cast(&CHostage::AnnounceDeath) },
	//{ 0x01D4D6A0, "_ZN8CHostage19ApplyHostagePenaltyEP11CBasePlayer", mfunc_ptr_cast(&CHostage::ApplyHostagePenalty) },	// NOXREF
	//{ 0x01D4DA80, "_ZN8CHostage16GiveCTTouchBonusEP11CBasePlayer", mfunc_ptr_cast(&CHostage::GiveCTTouchBonus) },		// NOXREF
	//{ 0x01D4E580, "_ZN8CHostage22SendHostagePositionMsgEv", mfunc_ptr_cast(&CHostage::SendHostagePositionMsg) },
	//{ 0x0, "_ZN8CHostage19SendHostageEventMsgEv", mfunc_ptr_cast(&CHostage::SendHostageEventMsg) },
	//{ 0x01D4DC10, "_ZN8CHostage8DoFollowEv", mfunc_ptr_cast(&CHostage::DoFollow) },
	//{ 0x01D4E380, "_ZN8CHostage10IsOnLadderEv", mfunc_ptr_cast(&CHostage::IsOnLadder) },		// NOXREF
	//{ 0x0, "_ZN8CHostage7PointAtERK6Vector", mfunc_ptr_cast(&CHostage::PointAt) },
	//{ 0x01D4E080, "_ZN8CHostage10MoveTowardERK6Vector", mfunc_ptr_cast(&CHostage::MoveToward) },
	{ 0x01D4E3A0, "_ZN8CHostage8NavReadyEv", mfunc_ptr_cast(&CHostage::NavReady) },
	//{ 0x01D4E850, "_ZN8CHostage6WiggleEv", mfunc_ptr_cast(&CHostage::Wiggle) },
	{ 0x01D4EAB0, "_ZN8CHostage8PreThinkEv", mfunc_ptr_cast(&CHostage::PreThink) },
	//{ 0x0, "_ZN8CHostage18IsFollowingSomeoneEv", mfunc_ptr_cast(&CHostage::IsFollowingSomeone) },
	//{ 0x0, "_ZN8CHostage9GetLeaderEv", mfunc_ptr_cast(&CHostage::GetLeader) },
	//{ 0x0, "_ZN8CHostage11IsFollowingEPK11CBaseEntity", mfunc_ptr_cast(&CHostage::IsFollowing) },
	//{ 0x0, "_ZN8CHostage7IsValidEv", mfunc_ptr_cast(&CHostage::IsValid) },
	//{ 0x0, "_ZN8CHostage6IsDeadEv", mfunc_ptr_cast(&CHostage::IsDead) },
	//{ 0x0, "_ZNK8CHostage8IsAtHomeEv", mfunc_ptr_cast(&CHostage::IsAtHome) },
	//{ 0x0, "_ZNK8CHostage15GetHomePositionEv", mfunc_ptr_cast(&CHostage::GetHomePosition) },
//CHostageManager
	//{ 0x01D4EE20, "_Z21Hostage_RegisterCVarsv", (size_t)&Hostage_RegisterCVars },	// NOXREF
	//{ 0x01D4EE40, "_Z21InstallHostageManagerv", (size_t)&InstallHostageManager },
	{ 0x01D4EF10, "_ZN15CHostageManager14ServerActivateEv", mfunc_ptr_cast(&CHostageManager::ServerActivate) },
	//{ 0x0, "_ZN15CHostageManager16ServerDeactivateEv", mfunc_ptr_cast(&CHostageManager::ServerDeactivate) },
	{ 0x01D50670, "_ZN15CHostageManager12RestartRoundEv", mfunc_ptr_cast(&CHostageManager::RestartRound) },
	//{ 0x01D506A0, "_ZN15CHostageManager10AddHostageEP8CHostage", mfunc_ptr_cast(&CHostageManager::AddHostage) },	// NOXREF
	//{ 0x0, "_ZN15CHostageManager10GetChatterEv", mfunc_ptr_cast(&CHostageManager::GetChatter) },
	//{ 0x0, "_ZNK15CHostageManager22IsNearbyHostageTalkingEP14CHostageImprov", mfunc_ptr_cast(&CHostageManager::IsNearbyHostageTalking) },
	//{ 0x0, "_ZNK15CHostageManager22IsNearbyHostageJumpingEP14CHostageImprov", mfunc_ptr_cast(&CHostageManager::IsNearbyHostageJumping) },
	{ 0x01D50850, "_ZN15CHostageManager7OnEventE13GameEventTypeP11CBaseEntityS2_", mfunc_ptr_cast(&CHostageManager::OnEvent) },
	//{ 0x0, "_ZN15CHostageManager17GetClosestHostageERK6VectorPf", mfunc_ptr_cast(&CHostageManager::GetClosestHostage) },
//SimpleChatter
	//{ 0x01D508A0, "_ZN13SimpleChatterC2Ev", mfunc_ptr_cast(&SimpleChatter::SimpleChatter) },
	//{ 0x01D508D0, "_ZN13SimpleChatterD2Ev", mfunc_ptr_cast(&SimpleChatter::~SimpleChatter) },
	{ 0x01D50910, "_ZN13SimpleChatter8AddSoundE18HostageChatterTypePc", mfunc_ptr_cast(&SimpleChatter::AddSound) },
	//{ 0x01D50B40, "_ZN13SimpleChatter9PlaySoundEP11CBaseEntity18HostageChatterType", mfunc_ptr_cast(&SimpleChatter::PlaySound) },
	//{ 0x0, "_ZN13SimpleChatter8GetSoundE18HostageChatterTypePf", mfunc_ptr_cast(&SimpleChatter::GetSound) },
	//{ 0x0, "_ZN13SimpleChatter7ShuffleEPNS_10ChatterSetE", mfunc_ptr_cast(&SimpleChatter::Shuffle) },
//CLocalNav
	//{ 0x0, "_ZN9CLocalNav12SetTargetEntEP11CBaseEntity", mfunc_ptr_cast(&CLocalNav::SetTargetEnt) },	// NOXREF
	{ 0x01D57420, "_ZN9CLocalNav8FindPathER6VectorS1_fi", mfunc_ptr_cast(&CLocalNav::FindPath) },
	{ 0x01D57380, "_ZN9CLocalNav14SetupPathNodesEiP6Vectori", mfunc_ptr_cast(&CLocalNav::SetupPathNodes) },
	//{ 0x01D573D0, "_ZN9CLocalNav26GetFurthestTraversableNodeER6VectorPS0_ii", mfunc_ptr_cast(&CLocalNav::GetFurthestTraversableNode) },
	{ 0x01D57AC0, "_ZN9CLocalNav15PathTraversableER6VectorS1_i", mfunc_ptr_cast(&CLocalNav::PathTraversable) },
	//{ 0x01D57A50, "_ZN9CLocalNav9PathClearER6VectorS1_iR11TraceResult", mfunc_ptr_cast<PATH_CLEAR_TRACE_RESULT>(&CLocalNav::PathClear) },	// NOXREF
	//{ 0x0, "_ZN9CLocalNav9PathClearER6VectorS1_i", mfunc_ptr_cast<PATH_CLEAR_DEFAULT>(&CLocalNav::PathClear) },	// NOXREF
	{ 0x01D58AC0, "_ZN9CLocalNav5ThinkEv", mfunc_ptr_cast(&CLocalNav::Think) },
	//{ 0x01D58D50, "_ZN9CLocalNav10RequestNavEP8CHostage", mfunc_ptr_cast(&CLocalNav::RequestNav) },
	{ 0x01D58E20, "_ZN9CLocalNav5ResetEv", mfunc_ptr_cast(&CLocalNav::Reset) },
	//{ 0x01D58E50, "_ZN9CLocalNav15HostagePrethinkEv", mfunc_ptr_cast(&CLocalNav::HostagePrethink) },	// NOXREF
	//{ 0x01D56F20, "_ZN9CLocalNav7AddNodeEiR6Vectoriih", mfunc_ptr_cast(&CLocalNav::AddNode) },	// NOXREF
	//{ 0x0, "_ZN9CLocalNav7GetNodeEi", mfunc_ptr_cast(&CLocalNav::GetNode) },	// NOXREF
	//{ 0x01D56F80, "_ZN9CLocalNav10NodeExistsEii", mfunc_ptr_cast(&CLocalNav::NodeExists) },	// NOXREF
	//{ 0x01D56FC0, "_ZN9CLocalNav12AddPathNodesEii", mfunc_ptr_cast(&CLocalNav::AddPathNodes) },	// NOXREF
	{ 0x01D57040, "_ZN9CLocalNav11AddPathNodeEiiii", mfunc_ptr_cast(&CLocalNav::AddPathNode) },
	{ 0x01D57290, "_ZN9CLocalNav11GetBestNodeER6VectorS1_", mfunc_ptr_cast(&CLocalNav::GetBestNode) },
	{ 0x01D57EB0, "_ZN9CLocalNav16SlopeTraversableER6VectorS1_iR11TraceResult", mfunc_ptr_cast(&CLocalNav::SlopeTraversable) },
	//{ 0x01D580A0, "_ZN9CLocalNav17LadderTraversableER6VectorS1_iR11TraceResult", mfunc_ptr_cast(&CLocalNav::LadderTraversable) },
	{ 0x01D581D0, "_ZN9CLocalNav15StepTraversableER6VectorS1_iR11TraceResult", mfunc_ptr_cast(&CLocalNav::StepTraversable) },
	{ 0x01D583C0, "_ZN9CLocalNav12StepJumpableER6VectorS1_iR11TraceResult", mfunc_ptr_cast(&CLocalNav::StepJumpable) },
	{ 0x01D57810, "_ZN9CLocalNav14FindDirectPathER6VectorS1_fi", mfunc_ptr_cast(&CLocalNav::FindDirectPath) },
	//{ 0x01D585C0, "_ZN9CLocalNav9LadderHitER6VectorS1_R11TraceResult", mfunc_ptr_cast(&CLocalNav::LadderHit) },

#endif // Hostage_Region

	{ NULL, NULL, NULL }
};

// refs for uncompleted virtual function
VirtualTableRef g_TableRefs[] =
{
	// CBaseEntity
	{ 0x01DF8A94, "CGib",			CBASE_VIRTUAL_COUNT },
	{ 0x01DFD824, "CBaseDelay",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF607C, "CBaseEntity",		CBASE_VIRTUAL_COUNT },
	{ 0x01DFA894, "CGrenade",		77 },
	{ 0x01DF67D4, "CBaseToggle",		60 },
	{ 0x01DF652C, "CBasePlayer",		88 },
	{ 0x01DF6694, "CBaseMonster",		76 },
	{ 0x01DFDA84, "CSprayCan",		CBASE_VIRTUAL_COUNT },
	{ 0x01DFDB74, "CBloodSplat",		CBASE_VIRTUAL_COUNT },
	{ 0x01DFDC6C, "CDeadHEV",		76 },
	{ 0x01DFDF84, "CInfoIntermission",	CBASE_VIRTUAL_COUNT },
	{ 0x01DFDE94, "CRevertSaved",		CBASE_VIRTUAL_COUNT },
	{ 0x01DFDDA4, "CStripWeapons",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF69B4, "CBot",			116 },
	{ 0x01DF61DC, "CCSBot",			116 },
	{ 0x01DF64F0, "CCSBotManager",		12 },
	{ 0x01DF6C9C, "CHostage",		76 },
	{ 0x01DFE4E4, "CSoundEnt",		CBASE_VIRTUAL_COUNT },
	{ 0x01E00D9C, "CCorpse",		CBASE_VIRTUAL_COUNT },
	{ 0x01E00CAC, "CDecal",			CBASE_VIRTUAL_COUNT },
	{ 0x01E00E8C, "CWorld",			CBASE_VIRTUAL_COUNT },
	{ 0x01DFE8D4, "CBaseGrenCatch",		CBASE_VIRTUAL_COUNT },
	{ 0x01DFE9C4, "CFuncWeaponCheck",	CBASE_VIRTUAL_COUNT },
	{ 0x01E00ACC, "CWeaponBox",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF9F94, "CShower",		CBASE_VIRTUAL_COUNT },
	{ 0x01DFA084, "CEnvExplosion",		76 },
	{ 0x01DFC79C, "CFuncMortarField",	59 },
	{ 0x01DF7204, "CAirtank",		77 },
	{ 0x01DFC88C, "CMortar",		77 },

	{ 0x01DF7344, "C9MMAmmo",		59 },
	{ 0x01DF7434, "CBuckShotAmmo",		59 },
	{ 0x01DF7524, "C556NatoAmmo",		59 },
	{ 0x01DF7614, "C556NatoBoxAmmo",	59 },
	{ 0x01DF7704, "C762NatoAmmo",		59 },
	{ 0x01DF77F4, "C45ACPAmmo",		59 },
	{ 0x01DF78E4, "C50AEAmmo",		59 },
	{ 0x01DF79D4, "C338MagnumAmmo",		59 },
	{ 0x01DF7AC4, "C57MMAmmo",		59 },
	{ 0x01DF7BB4, "C357SIGAmmo",		59 },

	// rules
	{ 0x01DFCBFC, "CGameRules",		63 },
	{ 0x01DFE10C, "CHalfLifeRules",		63 },
	{ 0x01DFCADC, "CHalfLifeMultiplay",	70 },
	{ 0x01DFE7B4, "CHalfLifeTraining",	70 },
	{ 0x01DFC9D4, "CMapInfo", 0 },

	// effects
	{ 0x01DF8EAC, "CPointEntity",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF8F9C, "CBubbling",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF908C, "CBeam",			CBASE_VIRTUAL_COUNT },
	{ 0x01DF917C, "CLightning",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF926C, "CLaser",			CBASE_VIRTUAL_COUNT },
	{ 0x01DF944C, "CGlow",			CBASE_VIRTUAL_COUNT },
	{ 0x01DF953C, "CBombGlow",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF935C, "CSprite",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF9634, "CGibShooter",		59 },
	{ 0x01DF9724, "CEnvShooter",		59 },
	{ 0x01DF9814, "CTestEffect",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF9904, "CBlood",			CBASE_VIRTUAL_COUNT },
	{ 0x01DF99F4, "CShake",			CBASE_VIRTUAL_COUNT },
	{ 0x01DF9AE4, "CFade",			CBASE_VIRTUAL_COUNT },
	{ 0x01DF9BD4, "CMessage",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF9CC4, "CEnvFunnel",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF9DB4, "CEnvBeverage",		CBASE_VIRTUAL_COUNT },
	{ 0x01DF9EA4, "CItemSoda",		CBASE_VIRTUAL_COUNT },

	// tutor
	{ 0x01E00FA4, "CBaseTutor",			12 },
	{ 0x01E00F9C, "TutorMessageEvent",		1 },
	{ 0x01E01024, "CCSTutor",			12 },
	{ 0x01E00FEC, "CCSTutorStateSystem",		4 },
	{ 0x01E00F78, "CBaseTutorStateSystem",		4 },
	{ 0x01E00F8C, "CBaseTutorState",		3 },
	{ 0x01E00FDC, "CCSTutorUndefinedState",		3 },
	{ 0x01E01000, "CCSTutorBuyMenuState",		3 },
	{ 0x01E01010, "CCSTutorWaitingForStartState",	3 },

	// Weapons vtable
	{ 0x01DF5C6C, "CUSP",			95 },
	{ 0x01DFD984, "CWShield",		CBASE_VIRTUAL_COUNT },

	{ NULL, NULL }	// BaseClass__for_vtbl
};

// refs
AddressRef g_FunctionRefs[] =
{
#ifndef Function_References_Region

	{ 0x01D3CA60, "_ZNK8CNavArea4GetZEPK6Vector", (size_t)&pGetZ__Vector },
	{ 0x01D43860, "_ZNK12CNavAreaGrid17GetNearestNavAreaEPK6Vectorb", (size_t)&pGetNearestNavArea },
	{ 0x01D43710, "_ZNK12CNavAreaGrid10GetNavAreaEPK6Vectorf", (size_t)&pGetNavArea },
	{ 0x01D72480, "_ZN11CBaseEntity12FireBullets3E6VectorS0_ffiiifP9entvars_sbi", (size_t)&pFireBullets3 },
	{ 0x01D2EDD0, "_ZN6CCSBot16UpdateLookAnglesEv", (size_t)&pCCSBot__UpdateLookAngles },
	{ 0x01D2D9B0, "_ZN6CCSBot6UpdateEv", (size_t)&pCCSBot__Update },
	{ 0x01D5B350, "_Z16QuaternionMatrixPfPA4_f", (size_t)&pQuaternionMatrix },

	{ 0x01DAD590, "_ZN11CBasePlayer27PickPrimaryCareerTaskWeaponEv", (size_t)&pCBasePlayer__PickPrimaryCareerTaskWeapon },
	{ 0x01DAD930, "_ZN11CBasePlayer29PickSecondaryCareerTaskWeaponEv", (size_t)&pCBasePlayer__PickSecondaryCareerTaskWeapon },
	{ 0x01D46310, "_Z17LoadNavigationMapv", (size_t)&pLoadNavigationMap },
	{ 0x01D19C70, "_ZN9BotPhrase9RandomizeEv", (size_t)&pBotPhrase__Randomize },

	{ 0x01D25270, "_ZN13CCSBotManager6AddBotEPK10BotProfile18BotProfileTeamType", (size_t)&pCCSBotManager__AddBot },
	{ 0x01D6EAB0, "_ZN4CGib12SpawnHeadGibEP9entvars_s", (size_t)&pCGib__SpawnHeadGib },
	{ 0x01D3A060, "_Z20DestroyNavigationMapv", (size_t)&pDestroyNavigationMap },
	{ 0x01D80C90, "_Z16InstallGameRulesv", (size_t)&pInstallGameRules },
	{ 0x01D4C450, "_ZN8CHostage9IdleThinkEv", (size_t)&pCHostage__IdleThink },

#endif // Function_References_Region

	{ NULL, NULL, NULL }
};

AddressRef g_DataRefs[] =
{
#ifndef Data_References_Region

	{ 0x01E61BD0, "g_engfuncs", (size_t)&pg_engfuncs },
	{ 0x01E61E48, "gpGlobals", (size_t)&pgpGlobals },

	{ 0x01E2A3F8, "_ZL14s_shared_token", (size_t)&ps_shared_token },
	{ 0x01E13218, "_ZL14s_shared_quote", (size_t)&ps_shared_quote },

	{ 0x01E61BA4, "g_vecZero", (size_t)&pg_vecZero },
	{ 0x01E61BB4, "g_Language", (size_t)&pg_Language },
	{ 0x01E61BB8, "g_ulFrameCount", (size_t)&pg_ulFrameCount },	// NOXREF
	//{ 0x0, "g_ulModelIndexEyes", (size_t)&pg_ulModelIndexEyes },	// NOXREF
	{ 0x01E61BC0, "g_vecAttackDir", (size_t)&pg_vecAttackDir },
	{ 0x01E61BBC, "g_iSkillLevel", (size_t)&pg_iSkillLevel },
	{ 0x01E61B9C, "gDisplayTitle", (size_t)&pgDisplayTitle },
	{ 0x01E61BA0, "g_fGameOver", (size_t)&pg_fGameOver },
	{ 0x01E683A0, "gSkillData", (size_t)&pgSkillData },
	{ 0x01E75EC8, "g_sModelIndexLaser", (size_t)&pg_sModelIndexLaser },
	{ 0x01E227A8, "g_pModelNameLaser", (size_t)&pg_pModelNameLaser },
	{ 0x01E75FD8, "g_sModelIndexLaserDot", (size_t)&pg_sModelIndexLaserDot },
	{ 0x01E75EC6, "g_sModelIndexFireball", (size_t)&pg_sModelIndexFireball },
	{ 0x01E75EB4, "g_sModelIndexSmoke", (size_t)&pg_sModelIndexSmoke },
	{ 0x01E75EB2, "g_sModelIndexWExplosion", (size_t)&pg_sModelIndexWExplosion },
	{ 0x01E76562, "g_sModelIndexBubbles", (size_t)&pg_sModelIndexBubbles },
	{ 0x01E75EB6, "g_sModelIndexBloodDrop", (size_t)&pg_sModelIndexBloodDrop },
	{ 0x01E75ECA, "g_sModelIndexBloodSpray", (size_t)&pg_sModelIndexBloodSpray },
	{ 0x01E76566, "g_sModelIndexSmokePuff", (size_t)&pg_sModelIndexSmokePuff },
	{ 0x01E75ED0, "g_sModelIndexFireball2", (size_t)&pg_sModelIndexFireball2 },
	{ 0x01E75ECC, "g_sModelIndexFireball3", (size_t)&pg_sModelIndexFireball3 },
	{ 0x01E75ECE, "g_sModelIndexFireball4", (size_t)&pg_sModelIndexFireball4 },
	{ 0x01E76564, "g_sModelIndexCTGhost", (size_t)&pg_sModelIndexCTGhost },
	{ 0x01E75EB0, "g_sModelIndexTGhost", (size_t)&pg_sModelIndexTGhost },
	{ 0x01E76560, "g_sModelIndexC4Glow", (size_t)&pg_sModelIndexC4Glow },
	{ 0x01E76568, "giAmmoIndex", (size_t)&pgiAmmoIndex },

	{ 0x01E75EC4, "g_sModelIndexRadio", (size_t)&pg_sModelIndexRadio },
	{ 0x01E75EB8, "gMultiDamage", (size_t)&pgMultiDamage },
	{ 0x01E29880, "_ZL13s_iBeamSprite", (size_t)&ps_iBeamSprite },
	{ 0x01E29480, "_ZL8cosTable", (size_t)&pcosTable },
	
	{ 0x01E23AA8, "TutorIdentifierList", (size_t)&pTutorIdentifierList },
	{ 0x01E23678, "_ZL19g_TutorStateStrings", (size_t)&pg_TutorStateStrings },

	{ 0x01E61E4C, "WorldGraph", (size_t)&pWorldGraph },
	{ 0x01E61B98, "g_pGameRules", (size_t)&pg_pGameRules },
	{ 0x01E62560, "g_pMPGameRules", (size_t)&pg_pMPGameRules },
	{ 0x01E61E70, "_ZL12mp_com_token", (size_t)&pmp_com_token },
	
	{ 0x01E636F0, "vec3_origin", (size_t)&pvec3_origin },
	{ 0x01E1F420, "nanmask", (size_t)&pnanmask },

	{ 0x01E0B0B0, "_ZL15weaponAliasInfo", (size_t)&pweaponAliasInfo },
	{ 0x01E0B1E8, "_ZL18weaponBuyAliasInfo", (size_t)&pweaponBuyAliasInfo },
	{ 0x01E0B3F0, "_ZL20weaponClassAliasInfo", (size_t)&pweaponClassAliasInfo },
	{ 0x01E0B560, "g_autoBuyInfo", (size_t)&pg_autoBuyInfo },
	{ 0x01E0B708, "_ZL10weaponInfo", (size_t)&pweaponInfo },

	{ 0x01E6AC80, "gszallsentencenames", (size_t)&pgszallsentencenames },
	{ 0x01E683E0, "rgsentenceg", (size_t)&prgsentenceg },
	{ 0x01E75480, "fSentencesInit", (size_t)&pfSentencesInit },
	{ 0x01E75484, "gcallsentences", (size_t)&pgcallsentences },

	{ 0x01E75488, "fTextureTypeInit", (size_t)&pfTextureTypeInit },

	{ 0x01E7548C, "gcTextures_1", (size_t)&pgcTextures },
	{ 0x01E70C80, "grgszTextureName_1", (size_t)&pgrgszTextureName },
	{ 0x01E75080, "grgchTextureType_1", (size_t)&pgrgchTextureType },
	//implementation at PM_Shared

	{ 0x01E63B88, "grgszTextureName", (size_t)&ppm_grgszTextureName },
	{ 0x01E67F88, "grgchTextureType", (size_t)&ppm_grgchTextureType },
	{ 0x01E68388, "pm_shared_initialized", (size_t)&ppm_shared_initialized },
	{ 0x01E63700, "rgv3tStuckTable", (size_t)&prgv3tStuckTable },
	{ 0x01E63A88, "rgStuckLast", (size_t)&prgStuckLast },
	{ 0x01E68394, "g_onladder", (size_t)&pg_onladder },

	{ 0x01E68390, "gcTextures", (size_t)&ppm_gcTextures },

	{ 0x01E6838C, "pmove", (size_t)&pg_ppmove },
	{ 0x01E76578, "g_flWeaponCheat", (size_t)&pg_flWeaponCheat },
	{ 0x01E62778, "gEvilImpulse101", (size_t)&pgEvilImpulse101 },
	{ 0x01E62790, "g_szMapBriefingText", (size_t)&pg_szMapBriefingText },
	{ 0x01E1DD78, "gInitHUD", (size_t)&pgInitHUD },
	{ 0x01E75CFC, "g_groupmask", (size_t)&pg_groupmask },
	{ 0x01E75D00, "g_groupop", (size_t)&pg_groupop },
	{ 0x01E21EF8, "_ZL6gSizes", (size_t)&pgSizes },

	{ 0x01E75490, "pSoundEnt", (size_t)&ppSoundEnt },
	{ 0x01E75CF8, "_ZL6glSeed", (size_t)&pglSeed },
	{ 0x01E21598, "seed_table", (size_t)&pseed_table },
	{ 0x01E21998, "gEntvarsDescription", (size_t)&pgEntvarsDescription },
	{ 0x01E22DBC, "gGlobalEntitySaveData", (size_t)&pgGlobalEntitySaveData },
	{ 0x01E7656C, "g_pBodyQueueHead", (size_t)&pg_pBodyQueueHead },
	{ 0x01E76570, "gGlobalState", (size_t)&pgGlobalState },
	{ 0x01E22C50, "gDecals", (size_t)&pgDecals },
	{ 0x01E31748, "stringsHashTable", (size_t)&pstringsHashTable },
	{ 0x01E312E8, "hashItemMemPool", (size_t)&phashItemMemPool },
	{ 0x01E3175C, "gTouchDisabled", (size_t)&pgTouchDisabled },
	{ 0x01E6359C, "giPrecacheGrunt", (size_t)&pgiPrecacheGrunt },
	{ 0x01E6360C, "gmsgWeapPickup", (size_t)&pgmsgWeapPickup },
	{ 0x01E635E0, "gmsgHudText", (size_t)&pgmsgHudText },
	{ 0x01E635E4, "gmsgHudTextArgs", (size_t)&pgmsgHudTextArgs },
	{ 0x01E635A0, "gmsgShake", (size_t)&pgmsgShake },
	{ 0x01E635A4, "gmsgFade", (size_t)&pgmsgFade },
	{ 0x01E635A8, "gmsgFlashlight", (size_t)&pgmsgFlashlight },
	{ 0x01E635AC, "gmsgFlashBattery", (size_t)&pgmsgFlashBattery },
	{ 0x01E635B0, "gmsgResetHUD", (size_t)&pgmsgResetHUD },
	{ 0x01E635B4, "gmsgInitHUD", (size_t)&pgmsgInitHUD },
	{ 0x01E635B8, "gmsgViewMode", (size_t)&pgmsgViewMode },
	{ 0x01E635BC, "gmsgShowGameTitle", (size_t)&pgmsgShowGameTitle },
	{ 0x01E635C0, "gmsgCurWeapon", (size_t)&pgmsgCurWeapon },
	{ 0x01E635C4, "gmsgHealth", (size_t)&pgmsgHealth },
	{ 0x01E635C8, "gmsgDamage", (size_t)&pgmsgDamage },
	{ 0x01E635CC, "gmsgBattery", (size_t)&pgmsgBattery },
	{ 0x01E635D0, "gmsgTrain", (size_t)&pgmsgTrain },
	{ 0x01E635D4, "gmsgLogo", (size_t)&pgmsgLogo },
	{ 0x01E635D8, "gmsgWeaponList", (size_t)&pgmsgWeaponList },
	{ 0x01E635DC, "gmsgAmmoX", (size_t)&pgmsgAmmoX },
	{ 0x01E635E8, "gmsgDeathMsg", (size_t)&pgmsgDeathMsg },
	{ 0x01E635EC, "gmsgScoreAttrib", (size_t)&pgmsgScoreAttrib },
	{ 0x01E635F0, "gmsgScoreInfo", (size_t)&pgmsgScoreInfo },
	{ 0x01E635F4, "gmsgTeamInfo", (size_t)&pgmsgTeamInfo },
	{ 0x01E635F8, "gmsgTeamScore", (size_t)&pgmsgTeamScore },
	{ 0x01E635FC, "gmsgGameMode", (size_t)&pgmsgGameMode },
	{ 0x01E63600, "gmsgMOTD", (size_t)&pgmsgMOTD },
	{ 0x01E63604, "gmsgServerName", (size_t)&pgmsgServerName },
	{ 0x01E63608, "gmsgAmmoPickup", (size_t)&pgmsgAmmoPickup },
	{ 0x01E63610, "gmsgItemPickup", (size_t)&pgmsgItemPickup },
	{ 0x01E63614, "gmsgHideWeapon", (size_t)&pgmsgHideWeapon },
	{ 0x01E63618, "gmsgSayText", (size_t)&pgmsgSayText },
	{ 0x01E6361C, "gmsgTextMsg", (size_t)&pgmsgTextMsg },
	{ 0x01E63620, "gmsgSetFOV", (size_t)&pgmsgSetFOV },
	{ 0x01E63624, "gmsgShowMenu", (size_t)&pgmsgShowMenu },
	{ 0x01E63628, "gmsgSendAudio", (size_t)&pgmsgSendAudio },
	{ 0x01E6362C, "gmsgRoundTime", (size_t)&pgmsgRoundTime },
	{ 0x01E63630, "gmsgMoney", (size_t)&pgmsgMoney },
	{ 0x01E63634, "gmsgBlinkAcct", (size_t)&pgmsgBlinkAcct },
	{ 0x01E63638, "gmsgArmorType", (size_t)&pgmsgArmorType },
	{ 0x01E6363C, "gmsgStatusValue", (size_t)&pgmsgStatusValue },
	{ 0x01E63640, "gmsgStatusText", (size_t)&pgmsgStatusText },
	{ 0x01E63644, "gmsgStatusIcon", (size_t)&pgmsgStatusIcon },
	{ 0x01E63648, "gmsgBarTime", (size_t)&pgmsgBarTime },
	{ 0x01E6364C, "gmsgReloadSound", (size_t)&pgmsgReloadSound },
	{ 0x01E63650, "gmsgCrosshair", (size_t)&pgmsgCrosshair },
	{ 0x01E63654, "gmsgNVGToggle", (size_t)&pgmsgNVGToggle },
	{ 0x01E63658, "gmsgRadar", (size_t)&pgmsgRadar },
	{ 0x01E6365C, "gmsgSpectator", (size_t)&pgmsgSpectator },
	{ 0x01E63660, "gmsgVGUIMenu", (size_t)&pgmsgVGUIMenu },
	{ 0x01E63664, "gmsgCZCareer", (size_t)&pgmsgCZCareer },
	{ 0x01E63668, "gmsgCZCareerHUD", (size_t)&pgmsgCZCareerHUD },
	{ 0x01E6366C, "gmsgTaskTime", (size_t)&pgmsgTaskTime },
	{ 0x01E63670, "gmsgTutorText", (size_t)&pgmsgTutorText },
	{ 0x01E63674, "gmsgTutorLine", (size_t)&pgmsgTutorLine },
	{ 0x01E63678, "gmsgShadowIdx", (size_t)&pgmsgShadowIdx },
	{ 0x01E6367C, "gmsgTutorState", (size_t)&pgmsgTutorState },
	{ 0x01E63680, "gmsgTutorClose", (size_t)&pgmsgTutorClose },
	{ 0x01E63684, "gmsgAllowSpec", (size_t)&pgmsgAllowSpec },
	{ 0x01E63688, "gmsgBombDrop", (size_t)&pgmsgBombDrop },
	{ 0x01E6368C, "gmsgBombPickup", (size_t)&pgmsgBombPickup },
	{ 0x01E63690, "gmsgHostagePos", (size_t)&pgmsgHostagePos },
	{ 0x01E63694, "gmsgHostageK", (size_t)&pgmsgHostageK },
	{ 0x01E63698, "gmsgGeigerRange", (size_t)&pgmsgGeigerRange },
	{ 0x01E6369C, "gmsgSendCorpse", (size_t)&pgmsgSendCorpse },
	{ 0x01E636A0, "gmsgHLTV", (size_t)&pgmsgHLTV },
	{ 0x01E636A4, "gmsgSpecHealth", (size_t)&pgmsgSpecHealth },
	{ 0x01E636A8, "gmsgForceCam", (size_t)&pgmsgForceCam },
	{ 0x01E636AC, "gmsgADStop", (size_t)&pgmsgADStop },
	{ 0x01E636B0, "gmsgReceiveW", (size_t)&pgmsgReceiveW },
	{ 0x01E636B4, "gmsgScenarioIcon", (size_t)&pgmsgScenarioIcon },
	{ 0x01E636B8, "gmsgBotVoice", (size_t)&pgmsgBotVoice },
	{ 0x01E636BC, "gmsgBuyClose", (size_t)&pgmsgBuyClose },
	{ 0x01E636C0, "gmsgItemStatus", (size_t)&pgmsgItemStatus },
	{ 0x01E636C4, "gmsgLocation", (size_t)&pgmsgLocation },
	{ 0x01E636C8, "gmsgSpecHealth2", (size_t)&pgmsgSpecHealth2 },
	{ 0x01E636CC, "gmsgBarTime2", (size_t)&pgmsgBarTime2 },
	{ 0x01E636D0, "gmsgBotProgress", (size_t)&pgmsgBotProgress },
	{ 0x01E636D4, "gmsgBrass", (size_t)&pgmsgBrass },
	{ 0x01E636D8, "gmsgFog", (size_t)&pgmsgFog },
	{ 0x01E636DC, "gmsgShowTimer", (size_t)&pgmsgShowTimer },

	{ 0x01E61B80, "g_psv_gravity", (size_t)&pg_psv_gravity },
	{ 0x01E61B84, "g_psv_aim", (size_t)&pg_psv_aim },//TODO: unused, used cvar_t *sv_aim
	{ 0x01E63598, "sv_aim", (size_t)&psv_aim },

	{ 0x01E61E6C, "sv_clienttrace", (size_t)&psv_clienttrace },
	{ 0x01E61E68, "_ZL15g_GameMgrHelper", (size_t)&pg_GameMgrHelper },
	{ 0x01E22624, "voice_serverdebug", (size_t)&pvoice_serverdebug },
	{ 0x01E22638, "sv_alltalk", (size_t)&psv_alltalk },

	{ 0x01E75D20, "g_PlayerModEnable", (size_t)&pg_PlayerModEnable },
	{ 0x01E75D28, "g_BanMasks", (size_t)&pg_BanMasks },
	{ 0x01E75DA8, "g_SentGameRulesMasks", (size_t)&pg_SentGameRulesMasks },
	{ 0x01E75E30, "g_SentBanMasks", (size_t)&pg_SentBanMasks },
	{ 0x01E75E28, "g_bWantModEnable", (size_t)&pg_bWantModEnable },

	{ 0x01E76580, "_ZL23s_tutorDisabledThisGame", (size_t)&ps_tutorDisabledThisGame },
	{ 0x01E76584, "_ZL19s_nextCvarCheckTime", (size_t)&ps_nextCvarCheckTime },

	{ 0x01E61B88, "g_footsteps", (size_t)&pg_footsteps },
	{ 0x01E61B8C, "g_psv_accelerate", (size_t)&pg_psv_accelerate },
	{ 0x01E61B90, "g_psv_friction", (size_t)&pg_psv_friction },
	{ 0x01E61B94, "g_psv_stopspeed", (size_t)&pg_psv_stopspeed },
	{ 0x01E18738, "displaysoundlist", (size_t)&pdisplaysoundlist },
	{ 0x01E18774, "timelimit", (size_t)&ptimelimit },
	{ 0x01E1879C, "flashlight", (size_t)&pflashlight },
	{ 0x01E187B0, "decalfrequency", (size_t)&pdecalfrequency },
	{ 0x01E189A4, "fadetoblack", (size_t)&pfadetoblack },
	{ 0x01E1874C, "fragsleft", (size_t)&pfragsleft },
	{ 0x01E18760, "timeleft", (size_t)&ptimeleft },
	{ 0x01E18788, "friendlyfire", (size_t)&pfriendlyfire },
	{ 0x01E187C4, "allowmonsters", (size_t)&pallowmonsters },
	{ 0x01E187D8, "roundtime", (size_t)&proundtime },
	{ 0x01E187EC, "buytime", (size_t)&pbuytime },
	{ 0x01E18800, "freezetime", (size_t)&pfreezetime },
	{ 0x01E18814, "c4timer", (size_t)&pc4timer },
	{ 0x01E18828, "ghostfrequency", (size_t)&pghostfrequency },
	{ 0x01E1883C, "autokick", (size_t)&pautokick },
	{ 0x01E18850, "autokick_timeout", (size_t)&pautokick_timeout },
	{ 0x01E18864, "restartround", (size_t)&prestartround },
	{ 0x01E18878, "sv_restart", (size_t)&psv_restart },
	{ 0x01E1888C, "limitteams", (size_t)&plimitteams },
	{ 0x01E188A0, "autoteambalance", (size_t)&pautoteambalance },
	{ 0x01E188B4, "tkpunish", (size_t)&ptkpunish },
	{ 0x01E188C8, "hostagepenalty", (size_t)&phostagepenalty },
	{ 0x01E188DC, "mirrordamage", (size_t)&pmirrordamage },
	{ 0x01E188F0, "logmessages", (size_t)&plogmessages },
	{ 0x01E18904, "forcecamera", (size_t)&pforcecamera },
	{ 0x01E18918, "forcechasecam", (size_t)&pforcechasecam },
	{ 0x01E1892C, "mapvoteratio", (size_t)&pmapvoteratio },
	{ 0x01E18940, "logdetail", (size_t)&plogdetail },
	{ 0x01E18954, "startmoney", (size_t)&pstartmoney },
	{ 0x01E18968, "maxrounds", (size_t)&pmaxrounds },
	{ 0x01E1897C, "winlimit", (size_t)&pwinlimit },
	{ 0x01E18990, "windifference", (size_t)&pwindifference },
	{ 0x01E189B8, "playerid", (size_t)&pplayerid },
	{ 0x01E189CC, "allow_spectators", (size_t)&pallow_spectators },
	{ 0x01E189E0, "mp_chattime", (size_t)&pmp_chattime },
	{ 0x01E189F4, "kick_percent", (size_t)&pkick_percent },
	{ 0x01E18A08, "humans_join_team", (size_t)&phumans_join_team },
	{ 0x01E195D4, "sk_plr_9mm_bullet1", (size_t)&psk_plr_9mm_bullet1 },
	{ 0x01E195E8, "sk_plr_9mm_bullet2", (size_t)&psk_plr_9mm_bullet2 },
	{ 0x01E195FC, "sk_plr_9mm_bullet3", (size_t)&psk_plr_9mm_bullet3 },
	{ 0x01E19610, "sk_plr_357_bullet1", (size_t)&psk_plr_357_bullet1 },
	{ 0x01E19624, "sk_plr_357_bullet2", (size_t)&psk_plr_357_bullet2 },
	{ 0x01E19638, "sk_plr_357_bullet3", (size_t)&psk_plr_357_bullet3 },
	{ 0x01E1964C, "sk_plr_9mmAR_bullet1", (size_t)&psk_plr_9mmAR_bullet1 },
	{ 0x01E19660, "sk_plr_9mmAR_bullet2", (size_t)&psk_plr_9mmAR_bullet2 },
	{ 0x01E19674, "sk_plr_9mmAR_bullet3", (size_t)&psk_plr_9mmAR_bullet3 },
	{ 0x01E19688, "sk_plr_9mmAR_grenade1", (size_t)&psk_plr_9mmAR_grenade1 },
	{ 0x01E1969C, "sk_plr_9mmAR_grenade2", (size_t)&psk_plr_9mmAR_grenade2 },
	{ 0x01E196B0, "sk_plr_9mmAR_grenade3", (size_t)&psk_plr_9mmAR_grenade3 },
	{ 0x01E196C4, "sk_plr_buckshot1", (size_t)&psk_plr_buckshot1 },
	{ 0x01E196D8, "sk_plr_buckshot2", (size_t)&psk_plr_buckshot2 },
	{ 0x01E196EC, "sk_plr_buckshot3", (size_t)&psk_plr_buckshot3 },
	{ 0x01E19778, "sk_plr_rpg1", (size_t)&psk_plr_rpg1 },
	{ 0x01E1978C, "sk_plr_rpg2", (size_t)&psk_plr_rpg2 },
	{ 0x01E197A0, "sk_plr_rpg3", (size_t)&psk_plr_rpg3 },
	{ 0x01E1991C, "sk_12mm_bullet1", (size_t)&psk_12mm_bullet1 },
	{ 0x01E19930, "sk_12mm_bullet2", (size_t)&psk_12mm_bullet2 },
	{ 0x01E19944, "sk_12mm_bullet3", (size_t)&psk_12mm_bullet3 },
	{ 0x01E19958, "sk_9mmAR_bullet1", (size_t)&psk_9mmAR_bullet1 },
	{ 0x01E1996C, "sk_9mmAR_bullet2", (size_t)&psk_9mmAR_bullet2 },
	{ 0x01E19980, "sk_9mmAR_bullet3", (size_t)&psk_9mmAR_bullet3 },
	{ 0x01E19994, "sk_9mm_bullet1", (size_t)&psk_9mm_bullet1 },
	{ 0x01E199A8, "sk_9mm_bullet2", (size_t)&psk_9mm_bullet2 },
	{ 0x01E199BC, "sk_9mm_bullet3", (size_t)&psk_9mm_bullet3 },
	{ 0x01E19A0C, "sk_suitcharger1", (size_t)&psk_suitcharger1 },
	{ 0x01E19A20, "sk_suitcharger2", (size_t)&psk_suitcharger2 },
	{ 0x01E19A34, "sk_suitcharger3", (size_t)&psk_suitcharger3 },
	{ 0x01E19A48, "sk_battery1", (size_t)&psk_battery1 },
	{ 0x01E19A5C, "sk_battery2", (size_t)&psk_battery2 },
	{ 0x01E19A70, "sk_battery3", (size_t)&psk_battery3 },
	{ 0x01E19A84, "sk_healthcharger1", (size_t)&psk_healthcharger1 },
	{ 0x01E19A98, "sk_healthcharger2", (size_t)&psk_healthcharger2 },
	{ 0x01E19AAC, "sk_healthcharger3", (size_t)&psk_healthcharger3 },
	{ 0x01E19AC0, "sk_healthkit1", (size_t)&psk_healthkit1 },
	{ 0x01E19AD4, "sk_healthkit2", (size_t)&psk_healthkit2 },
	{ 0x01E19AE8, "sk_healthkit3", (size_t)&psk_healthkit3 },
	{ 0x01E19AFC, "sk_scientist_heal1", (size_t)&psk_scientist_heal1 },
	{ 0x01E19B10, "sk_scientist_heal2", (size_t)&psk_scientist_heal2 },
	{ 0x01E19B24, "sk_scientist_heal3", (size_t)&psk_scientist_heal3 },

	{ 0x01E10738, "g_flBotCommandInterval", (size_t)&pg_flBotCommandInterval },
	{ 0x01E1073C, "g_flBotFullThinkInterval", (size_t)&pg_flBotFullThinkInterval },

	{ 0x01E28A20, "BotArgs", (size_t)&pBotArgs },
	{ 0x01E28A30, "UseBotArgs", (size_t)&pUseBotArgs },

	{ 0x01E1E040, "g_weaponStruct", (size_t)&pg_weaponStruct },

	{ 0x01E0EFF8, "cv_bot_traceview", (size_t)&pcv_bot_traceview },
	{ 0x01E0F00C, "cv_bot_stop", (size_t)&pcv_bot_stop },
	{ 0x01E0F020, "cv_bot_show_nav", (size_t)&pcv_bot_show_nav },
	{ 0x01E0F034, "cv_bot_show_danger", (size_t)&pcv_bot_show_danger },
	{ 0x01E0F048, "cv_bot_nav_edit", (size_t)&pcv_bot_nav_edit },
	{ 0x01E0F05C, "cv_bot_nav_zdraw", (size_t)&pcv_bot_nav_zdraw },
	{ 0x01E0F070, "cv_bot_walk", (size_t)&pcv_bot_walk },
	{ 0x01E0F084, "cv_bot_difficulty", (size_t)&pcv_bot_difficulty },
	{ 0x01E0F098, "cv_bot_debug", (size_t)&pcv_bot_debug },
	{ 0x01E0F0AC, "cv_bot_quicksave", (size_t)&pcv_bot_quicksave },
	{ 0x01E0F0C0, "cv_bot_quota", (size_t)&pcv_bot_quota },
	{ 0x01E0F0D4, "cv_bot_quota_match", (size_t)&pcv_bot_quota_match },
	{ 0x01E0F0E8, "cv_bot_prefix", (size_t)&pcv_bot_prefix },
	{ 0x01E0F0FC, "cv_bot_allow_rogues", (size_t)&pcv_bot_allow_rogues },
	{ 0x01E0F110, "cv_bot_allow_pistols", (size_t)&pcv_bot_allow_pistols },
	{ 0x01E0F124, "cv_bot_allow_shotguns", (size_t)&pcv_bot_allow_shotguns },
	{ 0x01E0F138, "cv_bot_allow_sub_machine_guns", (size_t)&pcv_bot_allow_sub_machine_guns },
	{ 0x01E0F14C, "cv_bot_allow_rifles", (size_t)&pcv_bot_allow_rifles },
	{ 0x01E0F160, "cv_bot_allow_machine_guns", (size_t)&pcv_bot_allow_machine_guns },
	{ 0x01E0F174, "cv_bot_allow_grenades", (size_t)&pcv_bot_allow_grenades },
	{ 0x01E0F188, "cv_bot_allow_snipers", (size_t)&pcv_bot_allow_snipers },
	{ 0x01E0F19C, "cv_bot_allow_shield", (size_t)&pcv_bot_allow_shield },
	{ 0x01E0F1B0, "cv_bot_join_team", (size_t)&pcv_bot_join_team },
	{ 0x01E0F1C4, "cv_bot_join_after_player", (size_t)&pcv_bot_join_after_player },
	{ 0x01E0F1D8, "cv_bot_auto_vacate", (size_t)&pcv_bot_auto_vacate },
	{ 0x01E0F1EC, "cv_bot_zombie", (size_t)&pcv_bot_zombie },
	{ 0x01E0F200, "cv_bot_defer_to_human", (size_t)&pcv_bot_defer_to_human },
	{ 0x01E0F214, "cv_bot_chatter", (size_t)&pcv_bot_chatter },
	{ 0x01E0F228, "cv_bot_profile_db", (size_t)&pcv_bot_profile_db },

	{ 0x01E233BC, "cv_tutor_message_repeats", (size_t)&pcv_tutor_message_repeats },
	{ 0x01E233D0, "cv_tutor_debug_level", (size_t)&pcv_tutor_debug_level },
	{ 0x01E233E4, "cv_tutor_view_distance", (size_t)&pcv_tutor_view_distance },
	{ 0x01E233F8, "cv_tutor_viewable_check_interval", (size_t)&pcv_tutor_viewable_check_interval },
	{ 0x01E2340C, "cv_tutor_look_distance", (size_t)&pcv_tutor_look_distance },
	{ 0x01E23420, "cv_tutor_look_angle", (size_t)&pcv_tutor_look_angle },
	{ 0x01E23434, "cv_tutor_examine_time", (size_t)&pcv_tutor_examine_time },
	{ 0x01E23448, "cv_tutor_message_minimum_display_time", (size_t)&pcv_tutor_message_minimum_display_time },
	{ 0x01E2345C, "cv_tutor_message_character_display_time_coefficient", (size_t)&pcv_tutor_message_character_display_time_coefficient },
	{ 0x01E23470, "cv_tutor_hint_interval_time", (size_t)&pcv_tutor_hint_interval_time },

	{ 0x01E2A3E8, "_ZN9CLocalNav15flNextCvarCheckE", mfunc_ptr_cast(&CLocalNav::pflNextCvarCheck) },
	{ 0x01E2A3D8, "_ZN9CLocalNav12s_flStepSizeE", mfunc_ptr_cast(&CLocalNav::ps_flStepSize) },
	{ 0x01E2A3EC, "_ZN9CLocalNav15flLastThinkTimeE", mfunc_ptr_cast(&CLocalNav::pflLastThinkTime) },
	{ 0x01E2A3E4, "_ZN9CLocalNav7nodevalE", mfunc_ptr_cast(&CLocalNav::pnodeval) },
	{ 0x01E2A3F0, "_ZN9CLocalNav12tot_hostagesE", mfunc_ptr_cast(&CLocalNav::ptot_hostages) },
	{ 0x01E2A298, "_ZN9CLocalNav8hostagesE", mfunc_ptr_cast(&CLocalNav::phostages) },
	{ 0x01E2A3E0, "_ZN9CLocalNav11tot_inqueueE", mfunc_ptr_cast(&CLocalNav::ptot_inqueue) },
	{ 0x01E2A3DC, "_ZN9CLocalNav4qptrE", mfunc_ptr_cast(&CLocalNav::pqptr) },
	{ 0x01E2A338, "_ZN9CLocalNav5queueE", mfunc_ptr_cast(&CLocalNav::pqueue) },

	{ 0x01E287F8, "_ZL12navAreaCount", (size_t)&pnavAreaCount },
	{ 0x01E287FC, "_ZL12currentIndex", (size_t)&pcurrentIndex },

	//{ 0x0, "_ZN10CBreakable13pSpawnObjectsE", mfunc_ptr_cast(&CBreakable::ppSpawnObjects) },
	//{ 0x0, "_ZN10CBreakable11pSoundsWoodE", mfunc_ptr_cast(&CBreakable::ppSoundsWood) },
	//{ 0x0, "_ZN10CBreakable12pSoundsFleshE", mfunc_ptr_cast(&CBreakable::ppSoundsFlesh) },
	//{ 0x0, "_ZN10CBreakable12pSoundsMetalE", mfunCBaseEntity::Savec_ptr_cast(&CBreakable::ppSoundsMetal) },
	//{ 0x0, "_ZN10CBreakable15pSoundsConcreteE", mfunc_ptr_cast(&CBreakable::ppSoundsConcrete) },
	//{ 0x0, "_ZN10CBreakable12pSoundsGlassE", mfunc_ptr_cast(&CBreakable::ppSoundsGlass) },
	//{ 0x0, "_ZN9CPushable12m_soundNamesE", mfunc_ptr_cast(&CPushable::pm_soundNames) },
	{ 0x01E1E00C, "_ZN8CDeadHEV9m_szPosesE", mfunc_ptr_cast(&CDeadHEV::pm_szPoses) },
	{ 0x01E1DD88, "_ZN11CBasePlayer16m_playerSaveDataE", mfunc_ptr_cast(&CBasePlayer::pm_playerSaveData) },
	{ 0x01E14A68, "_ZN11CBaseEntity10m_SaveDataE", mfunc_ptr_cast(&CBaseEntity::pm_SaveData) },
	{ 0x01E22DAC, "_ZN12CGlobalState10m_SaveDataE", mfunc_ptr_cast(&CGlobalState::pm_SaveData) },
	//{ 0x0, "_ZN9CEnvSpark10m_SaveDataE", mfunc_ptr_cast(&CEnvSpark::pm_SaveData) },
	//{ 0x0, "_ZN19CMomentaryRotButton10m_SaveDataE", mfunc_ptr_cast(&CMomentaryRotButton::pm_SaveData) },
	//{ 0x0, "_ZN10CEnvGlobal10m_SaveDataE", mfunc_ptr_cast(&CEnvGlobal::pm_SaveData) },
	{ 0x01E1B4C0, "_ZN8CGrenade10m_SaveDataE", mfunc_ptr_cast(&CGrenade::pm_SaveData) },
	//{ 0x0, "_ZN9CWreckage10m_SaveDataE", mfunc_ptr_cast(&CWreckage::pm_SaveData) },
	//{ 0x0, "_ZN13CCyclerSprite10m_SaveDataE", mfunc_ptr_cast(&CCyclerSprite::pm_SaveData) },
	//{ 0x0, "_ZN7CCycler10m_SaveDataE", mfunc_ptr_cast(&CCycler::pm_SaveData) },
	{ 0x01E1BE38, "_ZN6CLight10m_SaveDataE", mfunc_ptr_cast(&CLight::pm_SaveData) },
	{ 0x01E1BB00, "_ZN11CWallHealth10m_SaveDataE", mfunc_ptr_cast(&CWallHealth::pm_SaveData) },
	{ 0x01E1B850, "_ZN9CRecharge10m_SaveDataE", mfunc_ptr_cast(&CRecharge::pm_SaveData) },
	{ 0x01E1C248, "_ZN16CFuncMortarField10m_SaveDataE", mfunc_ptr_cast(&CFuncMortarField::pm_SaveData) },
	{ 0x01E17A08, "_ZN13CEnvExplosion10m_SaveDataE", mfunc_ptr_cast(&CEnvExplosion::pm_SaveData) },
	//{ 0x0, "_ZN13CFuncRotating10m_SaveDataE", mfunc_ptr_cast(&CFuncRotating::pm_SaveData) },
	//{ 0x0, "_ZN9CPendulum10m_SaveDataE", mfunc_ptr_cast(&CPendulum::pm_SaveData) },
	//{ 0x0, "_ZN9CBaseDoor10m_SaveDataE", mfunc_ptr_cast(&CBaseDoor::pm_SaveData) },
	//{ 0x0, "_ZN14CMomentaryDoor10m_SaveDataE", mfunc_ptr_cast(&CMomentaryDoor::pm_SaveData) },
	//{ 0x0, "_ZN10CBreakable10m_SaveDataE", mfunc_ptr_cast(&CBreakable::pm_SaveData) },
	//{ 0x0, "_ZN9CPushable10m_SaveDataE", mfunc_ptr_cast(&CPushable::pm_SaveData) },
	//{ 0x0, "_ZN9CFuncTank10m_SaveDataE", mfunc_ptr_cast(&CFuncTank::pm_SaveData) },
	//{ 0x0, "_ZN14CFuncTankLaser10m_SaveDataE", mfunc_ptr_cast(&CFuncTankLaser::pm_SaveData) },
	//{ 0x0, "_ZN17CFuncTankControls10m_SaveDataE", mfunc_ptr_cast(&CFuncTankControls::pm_SaveData) },
	//{ 0x0, "_ZN12CFuncVehicle10m_SaveDataE", mfunc_ptr_cast(&CFuncVehicle::pm_SaveData) },
	//{ 0x0, "_ZN11CPathCorner10m_SaveDataE", mfunc_ptr_cast(&CPathCorner::pm_SaveData) },
	//{ 0x0, "_ZN10CPathTrack10m_SaveDataE", mfunc_ptr_cast(&CPathTrack::pm_SaveData) },
	{ 0x01E1E01C, "_ZN12CRevertSaved10m_SaveDataE", mfunc_ptr_cast(&CRevertSaved::pm_SaveData) },
	//{ 0x0, "_ZN11CRuleEntity10m_SaveDataE", mfunc_ptr_cast(&CRuleEntity::pm_SaveData) },
	//{ 0x0, "_ZN9CGameText10m_SaveDataE", mfunc_ptr_cast(&CGameText::pm_SaveData) },
	//{ 0x0, "_ZN15CGamePlayerZone10m_SaveDataE", mfunc_ptr_cast(&CGamePlayerZone::pm_SaveData) },
	//{ 0x0, "_ZN17CFrictionModifier10m_SaveDataE", mfunc_ptr_cast(&CFrictionModifier::pm_SaveData) },
	//{ 0x0, "_ZN12CAutoTrigger10m_SaveDataE", mfunc_ptr_cast(&CAutoTrigger::pm_SaveData) },
	//{ 0x0, "_ZN13CTriggerRelay10m_SaveDataE", mfunc_ptr_cast(&CTriggerRelay::pm_SaveData) },
	//{ 0x0, "_ZN13CMultiManager10m_SaveDataE", mfunc_ptr_cast(&CMultiManager::pm_SaveData) },
	//{ 0x0, "_ZN12CChangeLevel10m_SaveDataE", mfunc_ptr_cast(&CChangeLevel::pm_SaveData) },
	//{ 0x0, "_ZN20CTriggerChangeTarget10m_SaveDataE", mfunc_ptr_cast(&CTriggerChangeTarget::pm_SaveData) },
	//{ 0x0, "_ZN14CTriggerCamera10m_SaveDataE", mfunc_ptr_cast(&CTriggerCamera::pm_SaveData) },
	{ 0x01E208D8, "_ZN16CFuncWeaponCheck10m_SaveDataE", mfunc_ptr_cast(&CFuncWeaponCheck::pm_SaveData) },
	{ 0x01E20888, "_ZN14CBaseGrenCatch10m_SaveDataE", mfunc_ptr_cast(&CBaseGrenCatch::pm_SaveData) },
	{ 0x01E13228, "_ZN8CAirtank10m_SaveDataE", mfunc_ptr_cast(&CAirtank::pm_SaveData) },
	//{ 0x0, "_ZN12CMultiSource10m_SaveDataE", mfunc_ptr_cast(&CMultiSource::pm_SaveData) },
	{ 0x01E20538, "_ZN10CBaseDelay10m_SaveDataE", mfunc_ptr_cast(&CBaseDelay::pm_SaveData) },
	{ 0x01E13438, "_ZN14CBaseAnimating10m_SaveDataE", mfunc_ptr_cast(&CBaseAnimating::pm_SaveData) },
	{ 0x01E20558, "_ZN11CBaseToggle10m_SaveDataE", mfunc_ptr_cast(&CBaseToggle::pm_SaveData) },
	//{ 0x0, "_ZN11CBaseButton10m_SaveDataE", mfunc_ptr_cast(&CBaseButton::pm_SaveData) },
	//{ 0x0, "_ZN15CAmbientGeneric10m_SaveDataE", mfunc_ptr_cast(&CAmbientGeneric::pm_SaveData) },
	//{ 0x0, "_ZN9CEnvSound10m_SaveDataE", mfunc_ptr_cast(&CEnvSound::pm_SaveData) },
	//{ 0x0, "_ZN8CSpeaker10m_SaveDataE", mfunc_ptr_cast(&CSpeaker::pm_SaveData) },
	{ 0x01E17258, "_ZN9CBubbling10m_SaveDataE", mfunc_ptr_cast(&CBubbling::pm_SaveData) },
	{ 0x01E17288, "_ZN10CLightning10m_SaveDataE", mfunc_ptr_cast(&CLightning::pm_SaveData) },
	{ 0x01E17358, "_ZN6CLaser10m_SaveDataE", mfunc_ptr_cast(&CLaser::pm_SaveData) },
	{ 0x01E17388, "_ZN5CGlow10m_SaveDataE", mfunc_ptr_cast(&CGlow::pm_SaveData) },
	{ 0x01E173A8, "_ZN7CSprite10m_SaveDataE", mfunc_ptr_cast(&CSprite::pm_SaveData) },
	{ 0x01E173C8, "_ZN11CGibShooter10m_SaveDataE", mfunc_ptr_cast(&CGibShooter::pm_SaveData) },
	{ 0x01E227AC, "_ZN15CBasePlayerItem10m_SaveDataE", mfunc_ptr_cast(&CBasePlayerItem::pm_SaveData) },
	{ 0x01E227E0, "_ZN17CBasePlayerWeapon10m_SaveDataE", mfunc_ptr_cast(&CBasePlayerWeapon::pm_SaveData) },
	{ 0x01E22850, "_ZN10CWeaponBox10m_SaveDataE", mfunc_ptr_cast(&CWeaponBox::pm_SaveData) },
	//{ 0x0, "_ZN14CBasePlatTrain10m_SaveDataE", mfunc_ptr_cast(&CBasePlatTrain::pm_SaveData) },
	//{ 0x0, "_ZN12CFuncPlatRot10m_SaveDataE", mfunc_ptr_cast(&CFuncPlatRot::pm_SaveData) },
	//{ 0x0, "_ZN10CFuncTrain10m_SaveDataE", mfunc_ptr_cast(&CFuncTrain::pm_SaveData) },
	//{ 0x0, "_ZN15CFuncTrackTrain10m_SaveDataE", mfunc_ptr_cast(&CFuncTrackTrain::pm_SaveData) },
	//{ 0x0, "_ZN16CFuncTrackChange10m_SaveDataE", mfunc_ptr_cast(&CFuncTrackChange::pm_SaveData) },
	//{ 0x0, "_ZN10CGunTarget10m_SaveDataE", mfunc_ptr_cast(&CGunTarget::pm_SaveData) },
	{ 0x01E75FE0, "_ZN15CBasePlayerItem13ItemInfoArrayE", mfunc_ptr_cast(&CBasePlayerItem::pItemInfoArray) },
	{ 0x01E75ED8, "_ZN15CBasePlayerItem13AmmoInfoArrayE", mfunc_ptr_cast(&CBasePlayerItem::pAmmoInfoArray) },
	{ 0x01E28816, "_ZN13CCSBotManager17m_isMapDataLoadedE", mfunc_ptr_cast(&CCSBotManager::pm_isMapDataLoaded) },
	{ 0x01E28818, "_ZN13CCSBotManager9m_editCmdE", mfunc_ptr_cast(&CCSBotManager::pm_editCmd) },
	{ 0x01E2881C, "_ZN13CCSBotManager17m_flNextCVarCheckE", mfunc_ptr_cast(&CCSBotManager::pm_flNextCVarCheck) },
	{ 0x01E28814, "_ZN13CCSBotManager15m_isLearningMapE", mfunc_ptr_cast(&CCSBotManager::pm_isLearningMap) },
	{ 0x01E28815, "_ZN13CCSBotManager21m_isAnalysisRequestedE", mfunc_ptr_cast(&CCSBotManager::pm_isAnalysisRequested) },

	//{ 0x01E233BC, "cv_tutor_message_repeats", (size_t)&pcv_tutor_message_repeats },
	//{ 0x01E233D0, "cv_tutor_debug_level", (size_t)&pcv_tutor_debug_level },
	//{ 0x01E233E4, "cv_tutor_view_distance", (size_t)&pcv_tutor_view_distance },
	//{ 0x01E233F8, "cv_tutor_viewable_check_interval", (size_t)&pcv_tutor_viewable_check_interval },
	//{ 0x01E2340C, "cv_tutor_look_distance", (size_t)&pcv_tutor_look_distance },
	//{ 0x01E23420, "cv_tutor_look_angle", (size_t)&pcv_tutor_look_angle },
	//{ 0x01E23434, "cv_tutor_examine_time", (size_t)&pcv_tutor_examine_time },
	//{ 0x01E23448, "cv_tutor_message_minimum_display_time", (size_t)&pcv_tutor_message_minimum_display_time },
	//{ 0x01E2345C, "cv_tutor_message_character_display_time_coefficient", (size_t)&pcv_tutor_message_character_display_time_coefficient },
	//{ 0x01E23470, "cv_tutor_hint_interval_time", (size_t)&pcv_tutor_hint_interval_time },

	{ 0x01E11EE4, "cv_hostage_debug", (size_t)&pcv_hostage_debug },
	{ 0x01E11EF8, "cv_hostage_stop", (size_t)&pcv_hostage_stop },

	//{ 0x0, "_ZL14placeDirectory", (size_t)&pplaceDirectory },
	{ 0x01E2A0E8, "TheNavLadderList", (size_t)&pTheNavLadderList },
	{ 0x01E2A0F4, "TheHidingSpotList", (size_t)&pTheHidingSpotList },
	{ 0x01E14C5C, "sPlayerModelFiles", (size_t)&psPlayerModelFiles },
	{ 0x01E5D6F0, "g_flTimeLimit", (size_t)&pg_flTimeLimit },
	{ 0x01E5D6F4, "g_flResetTime", (size_t)&pg_flResetTime },
	{ 0x01E14C58, "g_bClientPrintEnable", (size_t)&pg_bClientPrintEnable },
	{ 0x01E5D6F8, "g_skipCareerInitialSpawn", (size_t)&pg_skipCareerInitialSpawn },
	{ 0x01E31768, "m_usResetDecals", (size_t)&pm_usResetDecals },
	{ 0x01E31760, "g_iShadowSprite", (size_t)&pg_iShadowSprite },

	{ 0x01E31770, "_ZL11g_PVSStatus", (size_t)&pg_PVSStatus },
	{ 0x01E14C90, "_ZL18entity_field_alias", (size_t)&pentity_field_alias },
	{ 0x01E14D68, "_ZL18player_field_alias", (size_t)&pplayer_field_alias },
	{ 0x01E14DD8, "custom_entity_field_alias", (size_t)&pcustom_entity_field_alias },
	{ 0x01E5D718, "_ZL14g_serveractive", (size_t)&pg_serveractive },

	{ 0x01E2A0AC, "_ZL17goodSizedAreaList", (size_t)&pgoodSizedAreaList },
	{ 0x01E2A0DC, "TheNavAreaList", (size_t)&pTheNavAreaList },
	{ 0x01E29888, "TheNavAreaGrid", (size_t)&pTheNavAreaGrid },

	{ 0x01E2A250, "_ZN8CNavNode6m_listE", mfunc_ptr_cast(&CNavNode::pm_list) },
	//{ 0x0, "_ZN8CNavArea8m_nextIDE", mfunc_ptr_cast(&CNavArea::m_nextID) },
	{ 0x01E11584, "_ZN8CNavArea14m_masterMarkerE", mfunc_ptr_cast(&CNavArea::pm_masterMarker) },
	{ 0x01E11588, "_ZN10HidingSpot8m_nextIDE", mfunc_ptr_cast(&HidingSpot::pm_nextID) },
	//{ 0x0, "_ZN10HidingSpot14m_masterMarkerE", mfunc_ptr_cast(&HidingSpot::m_masterMarker) },

	{ 0x01E2A100, "_ZN8CNavArea9m_isResetE", mfunc_ptr_cast(&CNavArea::pm_isReset) },
	{ 0x01E2A0FC, "_ZN8CNavArea10m_openListE", mfunc_ptr_cast(&CNavArea::pm_openList) },

	{ 0x01E2A104, "lastDrawTimestamp", (size_t)&plastDrawTimestamp },
	{ 0x01E2A118, "_ZL13editTimestamp", (size_t)&peditTimestamp },
	//{ 0x0, "goodSizedAreaList", (size_t)&pgoodSizedAreaList },
	{ 0x01E2A10C, "_ZL10markedArea", (size_t)&pmarkedArea },
	{ 0x01E2A110, "_ZL16lastSelectedArea", (size_t)&plastSelectedArea },
	{ 0x01E1158C, "_ZL12markedCorner", (size_t)&pmarkedCorner },
	{ 0x01E2A114, "_ZL17isCreatingNavArea", (size_t)&pisCreatingNavArea },
	//{ 0x0, "isAnchored", (size_t)&pisAnchored },
	//{ 0x0, "anchor", (size_t)&panchor },
	//{ 0x0, "isPlaceMode", (size_t)&pisPlaceMode },
	{ 0x01E2A117, "_ZL15isPlacePainting", (size_t)&pisPlacePainting },
	{ 0x01E29CA4, "_ZL9BlockedID", (size_t)&pBlockedID },
	{ 0x01E2A120, "_ZL14BlockedIDCount", (size_t)&pBlockedIDCount },

	{ 0x01E14988, "_ZL14gFunctionTable", (size_t)&pgFunctionTable },
	{ 0x01E14A50, "gNewDLLFunctions", (size_t)&pgNewDLLFunctions },
	{ 0x01E28810, "TheBots", (size_t)&pTheBots },

	{ 0x01E24950, "_ZL8taskInfo", (size_t)&ptaskInfo },
	{ 0x01E76594, "TheCareerTasks", (size_t)&pTheCareerTasks },
	{ 0x01E28C7C, "TheBotProfiles", (size_t)&pTheBotProfiles },

	{ 0x01E287CC, "g_pSelectedZombieSpawn", (size_t)&pg_pSelectedZombieSpawn },
	{ 0x01E287F0, "TheBotPhrases", (size_t)&pTheBotPhrases },

	{ 0x01E7657C, "TheTutor", (size_t)&pTheTutor },
	{ 0x01E2A25C, "g_pHostages", (size_t)&pg_pHostages },
	{ 0x01E2A258, "g_iHostageNumber", (size_t)&pg_iHostageNumber },

	{ 0x01E16EE0, "_ZL11outputLevel", (size_t)&poutputLevel },
	{ 0x01E61B40, "_ZL19theDebugOutputTypes", (size_t)&ptheDebugOutputTypes },
	{ 0x01E61740, "_ZL14theDebugBuffer", (size_t)&ptheDebugBuffer },

	{ 0x01E75D04, "_ZL9g_LessCtx", (size_t)&pg_LessCtx },
	{ 0x01E62670, "g_pevLastInflictor", (size_t)&pg_pevLastInflictor },
	{ 0x01E62788, "g_pLastSpawn", (size_t)&pg_pLastSpawn },

	{ 0x01E63590, "g_pLastCTSpawn", (size_t)&pg_pLastCTSpawn },
	{ 0x01E63594, "g_pLastTerroristSpawn", (size_t)&pg_pLastTerroristSpawn },

	{ 0x01E62990, "_ZL11zombieSpawn", (size_t)&pzombieSpawn },
	{ 0x01E636E8, "_ZL16zombieSpawnCount", (size_t)&pzombieSpawnCount },

	{ 0x01E13838, "svBlending", (size_t)&psvBlending },
	{ 0x01E312D0, "IEngineStudio", (size_t)&pIEngineStudio },
	{ 0x01E2DAA8, "g_pstudiohdr", (size_t)&pg_pstudiohdr },
	{ 0x01E2F8C0, "g_pRotationMatrix", (size_t)&pg_pRotationMatrix },
	{ 0x01E2F8B0, "g_pBoneTransform", (size_t)&pg_pBoneTransform },

	{ 0x01E2F8BC, "omega", (size_t)&pomega },
	{ 0x01E312E0, "cosom", (size_t)&pcosom },
	{ 0x01E306C8, "sinom", (size_t)&psinom },
	{ 0x01E2F8B4, "sclp", (size_t)&psclp },
	{ 0x01E2F8B8, "sclq", (size_t)&psclq },

#endif // Data_References_Region

	{ NULL, NULL, NULL }
};
