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

#define PITCH 0	// up/down
#define YAW   1 // left/right
#define ROLL  2 // fall over

extern vec3_t vec3_origin;
extern const int nanmask;

#define IS_NAN(x)	((*reinterpret_cast<int *>(&(x)) & nanmask) == nanmask)

float anglemod(float a);
void AngleVectors(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up);
void AngleVectorsTranspose(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up);
void AngleMatrix(const vec_t *angles, float (*matrix)[4]);
void AngleIMatrix(const vec_t *angles, float (*matrix)[4]);
void NormalizeAngles(float *angles);
void InterpolateAngles(float *start, float *end, float *output, float frac);
float AngleBetweenVectors(const vec_t *v1, const vec_t *v2);
void VectorTransform(const vec_t *in1, float *in2, vec_t *out);
int VectorCompare(const vec_t *v1, const vec_t *v2);
void VectorMA(const vec_t *veca, float scale, const vec_t *vecb, vec_t *vecc);

real_t _DotProduct(const vec_t *v1, const vec_t *v2);
void _VectorSubtract(vec_t *veca, vec_t *vecb, vec_t *out);
void _VectorAdd(vec_t *veca, vec_t *vecb, vec_t *out);
void _VectorCopy(vec_t *in, vec_t *out);
void CrossProduct(const vec_t *v1, const vec_t *v2, vec_t *cross);

real_t Length(const vec_t *v);
float Distance(const vec_t *v1, const vec_t *v2);
real_t VectorNormalize(vec_t *v);

void VectorInverse(vec_t *v);
void VectorScale(const vec_t *in, vec_t scale, vec_t *out);
int Q_log2(int val);
void VectorMatrix(vec_t *forward, vec_t *right, vec_t *up);
void VectorAngles(const vec_t *forward, vec_t *angles);
