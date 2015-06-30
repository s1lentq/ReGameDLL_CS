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

#ifndef ANIMATION_H
#define ANIMATION_H
#ifdef _WIN32
#pragma once
#endif

#include "com_model.h"
#include "studio.h"
#include "r_studioint.h"

NOBODY int ExtractBbox(void *pmodel, int sequence, float *mins, float *maxs);
int LookupActivity(void *pmodel, entvars_t *pev, int activity);
NOBODY int LookupActivityHeaviest(void *pmodel, entvars_t *pev, int activity);
NOBODY void GetEyePosition(void *pmodel, float *vecEyePosition);
int LookupSequence(void *pmodel, const char *label);
NOBODY int IsSoundEvent(int eventNumber);
NOBODY void SequencePrecache(void *pmodel, const char *pSequenceName);
void GetSequenceInfo(void *pmodel, entvars_t *pev, float *pflFrameRate, float *pflGroundSpeed);
int GetSequenceFlags(void *pmodel, entvars_t *pev);
NOBODY int GetAnimationEvent(void *pmodel, entvars_t *pev, MonsterEvent_t *pMonsterEvent, float flStart, float flEnd, int index);
NOBODY float SetController(void *pmodel, entvars_t *pev, int iController, float flValue);
NOBODY float SetBlending(void *pmodel, entvars_t *pev, int iBlender, float flValue);
NOBODY int FindTransition(void *pmodel, int iEndingAnim, int iGoalAnim, int *piDir);
NOBODY void SetBodygroup(void *pmodel, entvars_t *pev, int iGroup, int iValue);
NOBODY int GetBodygroup(void *pmodel, entvars_t *pev, int iGroup);
NOBODY int Server_GetBlendingInterface(int version, sv_blending_interface_s ** ppinterface, engine_studio_api_s *pstudio, float *rotationmatrix, float *bonetransform);
void AngleQuaternion(vec_t *angles, vec_t *quaternion);
NOBODY void QuaternionSlerp(vec_t *p, vec_t *q, float t, vec_t *qt);
NOBODY void QuaternionMatrix(vec_t *quaternion, float *matrix);
NOBODY mstudioanim_t *StudioGetAnim(model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc);
NOBODY mstudioanim_t *LookupAnimation(studiohdr_t *pstudiohdr, model_s *model, mstudioseqdesc_t *pseqdesc, int index);
NOBODY void StudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen);
NOBODY void StudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q);
NOBODY void StudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos);
NOBODY void StudioSlerpBones(vec4_t *q1, vec3_t *pos1, vec4_t *q2, vec3_t *pos2, float s);
NOBODY void StudioCalcRotations(mstudiobone_t *pbones, int *chain, int chainlength, float *adj, float *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, float s);
NOBODY void ConcatTransforms(float *in1, float *in2, float *out);
NOBODY void SV_StudioSetupBones(model_s *pModel, float frame, int sequence, const vec_t *angles, const vec_t *origin, const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict);

#endif // ANIMATION_H
