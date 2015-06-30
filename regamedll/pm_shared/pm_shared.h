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

#ifndef PM_SHARED_H
#define PM_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#define OBS_NONE			0
#define OBS_CHASE_LOCKED		1
#define OBS_CHASE_FREE			2
#define OBS_ROAMING			3
#define OBS_IN_EYE			4
#define OBS_MAP_FREE			5
#define OBS_MAP_CHASE			6

#define STEP_CONCRETE			0
#define STEP_METAL			1
#define STEP_DIRT			2
#define STEP_VENT			3
#define STEP_GRATE			4
#define STEP_TILE			5
#define STEP_SLOSH			6
#define STEP_WADE			7
#define STEP_LADDER			8
#define STEP_SNOW			9

#ifdef HOOK_GAMEDLL

#define pmove (*pg_ppmove)
#define pm_shared_initialized (*ppm_shared_initialized)
#define rgv3tStuckTable (*prgv3tStuckTable)

#define pm_gcTextures (*ppm_gcTextures)
#define pm_grgszTextureName (*ppm_grgszTextureName)
#define pm_grgchTextureType (*ppm_grgchTextureType)

#endif // HOOK_GAMEDLL

extern playermove_t *pmove;
extern int pm_shared_initialized;
extern vec3_t rgv3tStuckTable[54];

extern int pm_gcTextures;
extern char pm_grgszTextureName[ CTEXTURESMAX ][ CBTEXTURENAMEMAX ];
extern char pm_grgchTextureType[ CTEXTURESMAX ];

NOXREF void PM_SwapTextures(int i, int j);
NOXREF int PM_IsThereGrassTexture(void);
NOXREF void PM_SortTextures(void);
void PM_InitTextureTypes(void);
char PM_FindTextureType(char *name);
void PM_PlayStepSound(int step, float fvol);
NOXREF int PM_MapTextureTypeStepType(char chTextureType);
void PM_CatagorizeTextureType(void);
void PM_UpdateStepSound(void);
NOBODY qboolean PM_AddToTouched(pmtrace_t tr, vec3_t impactvelocity);
NOBODY void PM_CheckVelocity(void);
NOBODY int PM_ClipVelocity(vec3_t in, vec3_t normal, vec3_t out, float overbounce);
NOBODY void PM_AddCorrectGravity(void);
NOBODY void PM_FixupGravityVelocity(void);
NOBODY int PM_FlyMove(void);
NOBODY void PM_Accelerate(vec3_t wishdir, float wishspeed, float accel);
NOBODY void PM_WalkMove(void);
NOBODY void PM_Friction(void);
NOBODY void PM_AirAccelerate(vec3_t wishdir, float wishspeed, float accel);
NOBODY void PM_WaterMove(void);
NOBODY void PM_AirMove(void);
NOBODY qboolean PM_InWater(void);
NOBODY qboolean PM_CheckWater(void);
NOBODY void PM_CatagorizePosition(void);
NOBODY int PM_GetRandomStuckOffsets(int nIndex, int server, vec3_t offset);
NOBODY void PM_ResetStuckOffsets(int nIndex, int server);
NOBODY int PM_CheckStuck(void);
NOBODY void PM_SpectatorMove(void);
NOBODY float PM_SplineFraction(float value, float scale);
NOBODY float PM_SimpleSpline(float value);
NOBODY void PM_FixPlayerCrouchStuck(int direction);
NOBODY void PM_Duck(void);
NOBODY void PM_LadderMove(physent_t *pLadder);
NOBODY physent_t *PM_Ladder(void);
NOBODY void PM_WaterJump(void);
NOBODY void PM_AddGravity(void);
NOBODY pmtrace_t PM_PushEntity(vec3_t push);
NOBODY void PM_Physics_Toss(void);
NOBODY void PM_NoClip(void);
NOBODY void PM_PreventMegaBunnyJumping(void);
NOBODY void PM_Jump(void);
NOBODY void PM_CheckWaterJump(void);
NOBODY void PM_CheckFalling(void);
NOBODY void PM_PlayWaterSounds(void);
NOXREF float PM_CalcRoll(vec_t *angles, vec_t *velocity, float rollangle, float rollspeed);
NOXREF void PM_DropPunchAngle(vec_t *punchangle);
void PM_CheckParamters(void);
void PM_ReduceTimers(void);
NOXREF qboolean PM_ShouldDoSpectMode(void);
void PM_PlayerMove(qboolean server);
void PM_CreateStuckTable(void);
void PM_Move(struct playermove_s *ppmove, int server);
NOXREF int PM_GetVisEntInfo(int ent);
NOXREF int PM_GetPhysEntInfo(int ent);
void PM_Init(struct playermove_s *ppmove);

#endif // PM_SHARED_H
