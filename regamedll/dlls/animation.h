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

#define NUM_BLENDING                9

#define ANIM_SWIM_1                 8
#define ANIM_SWIM_2                 9
#define ANIM_FIRST_DEATH_SEQUENCE   101

#include "monsterevent.h"

int IsSoundEvent(int eventNumber);

int LookupActivity(void *pmodel, entvars_t *pev, int activity);
int LookupActivityHeaviest(void *pmodel, entvars_t *pev, int activity);
int LookupSequence(void *pmodel, const char *label);
void GetSequenceInfo(void *pmodel, entvars_t *pev, float *pflFrameRate, float *pflGroundSpeed);
int GetSequenceFlags(void *pmodel, entvars_t *pev);
float SetController(void *pmodel, entvars_t *pev, int iController, float flValue);
float SetBlending(void *pmodel, entvars_t *pev, int iBlender, float flValue);
void GetEyePosition(void *pmodel, float *vecEyePosition);
void SequencePrecache(void *pmodel, const char *pSequenceName);
int FindTransition(void *pmodel, int iEndingAnim, int iGoalAnim, int *piDir);
void SetBodygroup(void *pmodel, entvars_t *pev, int iGroup, int iValue);
int GetBodygroup(void *pmodel, entvars_t *pev, int iGroup);

int GetAnimationEvent(void *pmodel, entvars_t *pev, MonsterEvent_t *pMonsterEvent, float flStart, float flEnd, int index);
int ExtractBbox(void *pmodel, int sequence, float *mins, float *maxs);
