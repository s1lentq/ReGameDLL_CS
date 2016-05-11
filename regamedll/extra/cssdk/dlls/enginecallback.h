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
#pragma once

#include "event_flags.h"

// Must be provided by user of this code
extern enginefuncs_t g_engfuncs;

// The actual engine callbacks
#define GETPLAYERUSERID			(*g_engfuncs.pfnGetPlayerUserId)
#define PRECACHE_MODEL			(*g_engfuncs.pfnPrecacheModel)
#define PRECACHE_SOUND			(*g_engfuncs.pfnPrecacheSound)
#define PRECACHE_GENERIC		(*g_engfuncs.pfnPrecacheGeneric)
#define SET_MODEL			(*g_engfuncs.pfnSetModel)
#define MODEL_INDEX			(*g_engfuncs.pfnModelIndex)
#define MODEL_FRAMES			(*g_engfuncs.pfnModelFrames)
#define SET_SIZE			(*g_engfuncs.pfnSetSize)
#define CHANGE_LEVEL			(*g_engfuncs.pfnChangeLevel)
#define GET_SPAWN_PARMS			(*g_engfuncs.pfnGetSpawnParms)
#define SAVE_SPAWN_PARMS		(*g_engfuncs.pfnSaveSpawnParms)
#define VEC_TO_YAW			(*g_engfuncs.pfnVecToYaw)
#define VEC_TO_ANGLES			(*g_engfuncs.pfnVecToAngles)
#define MOVE_TO_ORIGIN			(*g_engfuncs.pfnMoveToOrigin)
#define oldCHANGE_YAW			(*g_engfuncs.pfnChangeYaw)
#define CHANGE_PITCH			(*g_engfuncs.pfnChangePitch)
#define MAKE_VECTORS			(*g_engfuncs.pfnMakeVectors)
#define CREATE_ENTITY			(*g_engfuncs.pfnCreateEntity)
#define REMOVE_ENTITY			(*g_engfuncs.pfnRemoveEntity)
#define CREATE_NAMED_ENTITY		(*g_engfuncs.pfnCreateNamedEntity)
#define MAKE_STATIC			(*g_engfuncs.pfnMakeStatic)
#define ENT_IS_ON_FLOOR			(*g_engfuncs.pfnEntIsOnFloor)
#define DROP_TO_FLOOR			(*g_engfuncs.pfnDropToFloor)
#define WALK_MOVE			(*g_engfuncs.pfnWalkMove)
#define SET_ORIGIN			(*g_engfuncs.pfnSetOrigin)
#define EMIT_SOUND_DYN2			(*g_engfuncs.pfnEmitSound)
#define BUILD_SOUND_MSG			(*g_engfuncs.pfnBuildSoundMsg)
#define TRACE_LINE			(*g_engfuncs.pfnTraceLine)
#define TRACE_TOSS			(*g_engfuncs.pfnTraceToss)
#define TRACE_MONSTER_HULL		(*g_engfuncs.pfnTraceMonsterHull)
#define TRACE_HULL			(*g_engfuncs.pfnTraceHull)
#define TRACE_MODEL			(*g_engfuncs.pfnTraceModel)
#define GET_AIM_VECTOR			(*g_engfuncs.pfnGetAimVector)
#define SERVER_COMMAND			(*g_engfuncs.pfnServerCommand)
#define SERVER_EXECUTE			(*g_engfuncs.pfnServerExecute)
#define CLIENT_COMMAND			(*g_engfuncs.pfnClientCommand)
#define PARTICLE_EFFECT			(*g_engfuncs.pfnParticleEffect)
#define LIGHT_STYLE			(*g_engfuncs.pfnLightStyle)
#define DECAL_INDEX			(*g_engfuncs.pfnDecalIndex)
#define POINT_CONTENTS			(*g_engfuncs.pfnPointContents)
#define CRC32_INIT			(*g_engfuncs.pfnCRC32_Init)
#define CRC32_PROCESS_BUFFER		(*g_engfuncs.pfnCRC32_ProcessBuffer)
#define CRC32_PROCESS_BYTE		(*g_engfuncs.pfnCRC32_ProcessByte)
#define CRC32_FINAL			(*g_engfuncs.pfnCRC32_Final)
#define RANDOM_LONG			(*g_engfuncs.pfnRandomLong)
#define RANDOM_FLOAT			(*g_engfuncs.pfnRandomFloat)
#define ADD_SERVER_COMMAND		(*g_engfuncs.pfnAddServerCommand)
#define SET_CLIENT_LISTENING		(*g_engfuncs.pfnVoice_SetClientListening)
#define GETPLAYERAUTHID			(*g_engfuncs.pfnGetPlayerAuthId)
#define GET_FILE_SIZE			(*g_engfuncs.pfnGetFileSize)
#define GET_APPROX_WAVE_PLAY_LEN	(*g_engfuncs.pfnGetApproxWavePlayLen)
#define IS_CAREER_MATCH			(*g_engfuncs.pfnIsCareerMatch)
#define GET_LOCALIZED_STRING_LENGTH	(*g_engfuncs.pfnGetLocalizedStringLength)
#define REGISTER_TUTOR_MESSAGE_SHOWN	(*g_engfuncs.pfnRegisterTutorMessageShown)
#define GET_TIMES_TUTOR_MESSAGE_SHOWN	(*g_engfuncs.pfnGetTimesTutorMessageShown)
#define ENG_CHECK_PARM			(*g_engfuncs.pfnEngCheckParm)

inline void MESSAGE_BEGIN(int msg_dest, int msg_type, const float *pOrigin = NULL, edict_t *ed = NULL) { (*g_engfuncs.pfnMessageBegin)(msg_dest, msg_type, pOrigin, ed); }

inline void *GET_PRIVATE(edict_t *pent)
{
	if (pent)
		return pent->pvPrivateData;
	return NULL;
}

#define MESSAGE_END			(*g_engfuncs.pfnMessageEnd)
#define WRITE_BYTE			(*g_engfuncs.pfnWriteByte)
#define WRITE_CHAR			(*g_engfuncs.pfnWriteChar)
#define WRITE_SHORT			(*g_engfuncs.pfnWriteShort)
#define WRITE_LONG			(*g_engfuncs.pfnWriteLong)
#define WRITE_ANGLE			(*g_engfuncs.pfnWriteAngle)
#define WRITE_COORD			(*g_engfuncs.pfnWriteCoord)
#define WRITE_STRING			(*g_engfuncs.pfnWriteString)
#define WRITE_ENTITY			(*g_engfuncs.pfnWriteEntity)
#define CVAR_REGISTER			(*g_engfuncs.pfnCVarRegister)
#define CVAR_GET_FLOAT			(*g_engfuncs.pfnCVarGetFloat)
#define CVAR_GET_STRING			(*g_engfuncs.pfnCVarGetString)
#define CVAR_SET_FLOAT			(*g_engfuncs.pfnCVarSetFloat)
#define CVAR_SET_STRING			(*g_engfuncs.pfnCVarSetString)
#define CVAR_GET_POINTER		(*g_engfuncs.pfnCVarGetPointer)
#define ALERT				(*g_engfuncs.pfnAlertMessage)
#define ENGINE_FPRINTF			(*g_engfuncs.pfnEngineFprintf)
#define ALLOC_PRIVATE			(*g_engfuncs.pfnPvAllocEntPrivateData)
#define FREE_PRIVATE			(*g_engfuncs.pfnFreeEntPrivateData)
//#define STRING			(*g_engfuncs.pfnSzFromIndex)
#define ALLOC_STRING			(*g_engfuncs.pfnAllocString)
#define FIND_ENTITY_BY_STRING		(*g_engfuncs.pfnFindEntityByString)
#define GETENTITYILLUM			(*g_engfuncs.pfnGetEntityIllum)
#define FIND_ENTITY_IN_SPHERE		(*g_engfuncs.pfnFindEntityInSphere)
#define FIND_CLIENT_IN_PVS		(*g_engfuncs.pfnFindClientInPVS)
#define FIND_ENTITY_IN_PVS		(*g_engfuncs.pfnEntitiesInPVS)
#define EMIT_AMBIENT_SOUND		(*g_engfuncs.pfnEmitAmbientSound)
#define GET_MODEL_PTR			(*g_engfuncs.pfnGetModelPtr)
#define REG_USER_MSG			(*g_engfuncs.pfnRegUserMsg)
#define GET_BONE_POSITION		(*g_engfuncs.pfnGetBonePosition)
#define FUNCTION_FROM_NAME		(*g_engfuncs.pfnFunctionFromName)
#define NAME_FOR_FUNCTION		(*g_engfuncs.pfnNameForFunction)
#define TRACE_TEXTURE			(*g_engfuncs.pfnTraceTexture)
#define CLIENT_PRINTF			(*g_engfuncs.pfnClientPrintf)
#define SERVER_PRINT			(*g_engfuncs.pfnServerPrint)
#define CMD_ARGS			(*g_engfuncs.pfnCmd_Args)
#define CMD_ARGC			(*g_engfuncs.pfnCmd_Argc)
#define CMD_ARGV			(*g_engfuncs.pfnCmd_Argv)
#define GET_ATTACHMENT			(*g_engfuncs.pfnGetAttachment)
#define SET_VIEW			(*g_engfuncs.pfnSetView)
#define SET_CROSSHAIRANGLE		(*g_engfuncs.pfnCrosshairAngle)
#define LOAD_FILE_FOR_ME		(*g_engfuncs.pfnLoadFileForMe)
#define FREE_FILE			(*g_engfuncs.pfnFreeFile)
#define END_SECTION			(*g_engfuncs.pfnEndSection)
#define COMPARE_FILE_TIME		(*g_engfuncs.pfnCompareFileTime)
#define GET_GAME_DIR			(*g_engfuncs.pfnGetGameDir)
#define SET_CLIENT_MAXSPEED		(*g_engfuncs.pfnSetClientMaxspeed)
#define CREATE_FAKE_CLIENT		(*g_engfuncs.pfnCreateFakeClient)
#define PLAYER_RUN_MOVE			(*g_engfuncs.pfnRunPlayerMove)
#define NUMBER_OF_ENTITIES		(*g_engfuncs.pfnNumberOfEntities)
#define GET_INFO_BUFFER			(*g_engfuncs.pfnGetInfoKeyBuffer)
#define GET_KEY_VALUE			(*g_engfuncs.pfnInfoKeyValue)
#define SET_KEY_VALUE			(*g_engfuncs.pfnSetKeyValue)
#define SET_CLIENT_KEY_VALUE		(*g_engfuncs.pfnSetClientKeyValue)
#define IS_MAP_VALID			(*g_engfuncs.pfnIsMapValid)
#define STATIC_DECAL			(*g_engfuncs.pfnStaticDecal)
#define IS_DEDICATED_SERVER		(*g_engfuncs.pfnIsDedicatedServer)
#define PRECACHE_EVENT			(*g_engfuncs.pfnPrecacheEvent)
#define PLAYBACK_EVENT_FULL		(*g_engfuncs.pfnPlaybackEvent)
#define ENGINE_SET_PVS			(*g_engfuncs.pfnSetFatPVS)
#define ENGINE_SET_PAS			(*g_engfuncs.pfnSetFatPAS)
#define ENGINE_CHECK_VISIBILITY		(*g_engfuncs.pfnCheckVisibility)
#define DELTA_SET			(*g_engfuncs.pfnDeltaSetField)
#define DELTA_UNSET			(*g_engfuncs.pfnDeltaUnsetField)
#define DELTA_ADDENCODER		(*g_engfuncs.pfnDeltaAddEncoder)
#define ENGINE_CURRENT_PLAYER		(*g_engfuncs.pfnGetCurrentPlayer)
#define ENGINE_CANSKIP			(*g_engfuncs.pfnCanSkipPlayer)
#define DELTA_FINDFIELD			(*g_engfuncs.pfnDeltaFindField)
#define DELTA_SETBYINDEX		(*g_engfuncs.pfnDeltaSetFieldByIndex)
#define DELTA_UNSETBYINDEX		(*g_engfuncs.pfnDeltaUnsetFieldByIndex)
#define REMOVE_KEY_VALUE		(*g_engfuncs.pfnInfo_RemoveKey)
#define SET_PHYSICS_KEY_VALUE		(*g_engfuncs.pfnSetPhysicsKeyValue)
#define ENGINE_GETPHYSINFO		(*g_engfuncs.pfnGetPhysicsInfoString)
#define ENGINE_SETGROUPMASK		(*g_engfuncs.pfnSetGroupMask)
#define ENGINE_INSTANCE_BASELINE	(*g_engfuncs.pfnCreateInstancedBaseline)
#define ENGINE_FORCE_UNMODIFIED		(*g_engfuncs.pfnForceUnmodified)
#define PLAYER_CNX_STATS		(*g_engfuncs.pfnGetPlayerStats)
