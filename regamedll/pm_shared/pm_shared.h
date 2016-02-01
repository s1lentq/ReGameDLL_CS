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

#define MAX_CLIENTS			32

#define PM_DEAD_VIEWHEIGHT		-8

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

#define WJ_HEIGHT				8
#define	STOP_EPSILON				0.1
#define MAX_CLIMB_SPEED				200
#define PLAYER_DUCKING_MULTIPLIER		0.333
#define PM_CHECKSTUCK_MINTIME			0.05	// Don't check again too quickly.

#define PLAYER_LONGJUMP_SPEED			350.0f	// how fast we longjump

// Ducking time
#define TIME_TO_DUCK				0.4
#define STUCK_MOVEUP				1

#define PM_VEC_DUCK_HULL_MIN			-18
#define PM_VEC_HULL_MIN				-36
#define PM_VEC_DUCK_VIEW			12
#define PM_VEC_VIEW				17

#define PM_PLAYER_MAX_SAFE_FALL_SPEED		580	// approx 20 feet
#define PM_PLAYER_MIN_BOUNCE_SPEED		350
#define PM_PLAYER_FALL_PUNCH_THRESHHOLD		250	// won't punch player's screen/make scrape noise unless player falling at least this fast.

// Only allow bunny jumping up to 1.2x server / player maxspeed setting
#define BUNNYJUMP_MAX_SPEED_FACTOR		1.2f

#ifdef HOOK_GAMEDLL

#define pmove (*pg_ppmove)
#define pm_shared_initialized (*ppm_shared_initialized)
#define rgv3tStuckTable (*prgv3tStuckTable)

#define pm_gcTextures (*ppm_gcTextures)
#define pm_grgszTextureName (*ppm_grgszTextureName)
#define pm_grgchTextureType (*ppm_grgchTextureType)
#define rgStuckLast (*prgStuckLast)
#define g_onladder (*pg_onladder)

#endif // HOOK_GAMEDLL

extern playermove_t *pmove;
extern int pm_shared_initialized;
extern vec3_t rgv3tStuckTable[54];
extern int rgStuckLast[MAX_CLIENTS][2];
extern int g_onladder;

extern int pm_gcTextures;
extern char pm_grgszTextureName[ CTEXTURESMAX ][ CBTEXTURENAMEMAX ];
extern char pm_grgchTextureType[ CTEXTURESMAX ];

void PM_SwapTextures(int i, int j);
NOXREF int PM_IsThereGrassTexture(void);
void PM_SortTextures(void);
void PM_InitTextureTypes(void);
char PM_FindTextureType(char *name);
void PM_PlayStepSound(int step, float fvol);
int PM_MapTextureTypeStepType(char chTextureType);
void PM_CatagorizeTextureType(void);
void PM_UpdateStepSound(void);
qboolean PM_AddToTouched(pmtrace_t tr, vec_t *impactvelocity);
void PM_CheckVelocity(void);
int PM_ClipVelocity(vec_t *in, vec_t *normal, vec_t *out, float overbounce);
void PM_AddCorrectGravity(void);
void PM_FixupGravityVelocity(void);
int PM_FlyMove(void);
void PM_Accelerate(vec_t *wishdir, float_precision wishspeed, float accel);
void PM_WalkMove(void);
void PM_Friction(void);
void PM_AirAccelerate(vec_t *wishdir, float wishspeed, float accel);
void PM_WaterMove(void);
void PM_AirMove(void);
qboolean PM_InWater(void);
qboolean PM_CheckWater(void);
void PM_CatagorizePosition(void);
int PM_GetRandomStuckOffsets(int nIndex, int server, vec_t *offset);
void PM_ResetStuckOffsets(int nIndex, int server);
int PM_CheckStuck(void);
void PM_SpectatorMove(void);
float PM_SplineFraction(float value, float scale);
NOXREF float PM_SimpleSpline(float value);
void PM_FixPlayerCrouchStuck(int direction);
void PM_Duck(void);
void PM_LadderMove(physent_t *pLadder);
physent_t *PM_Ladder(void);
void PM_WaterJump(void);
void PM_AddGravity(void);
pmtrace_t PM_PushEntity(vec_t *push);
void PM_Physics_Toss(void);
void PM_NoClip(void);
void PM_PreventMegaBunnyJumping(void);
void PM_Jump(void);
void PM_CheckWaterJump(void);
void PM_CheckFalling(void);
void PM_PlayWaterSounds(void);
float PM_CalcRoll(vec_t *angles, vec_t *velocity, float rollangle, float rollspeed);
void PM_DropPunchAngle(vec_t *punchangle);
void PM_CheckParamters(void);
void PM_ReduceTimers(void);
qboolean PM_ShouldDoSpectMode(void);
void PM_PlayerMove(qboolean server);
void PM_CreateStuckTable(void);
void PM_Move(struct playermove_s *ppmove, int server);
NOXREF int PM_GetVisEntInfo(int ent);
NOXREF int PM_GetPhysEntInfo(int ent);
void PM_Init(struct playermove_s *ppmove);

#endif // PM_SHARED_H
