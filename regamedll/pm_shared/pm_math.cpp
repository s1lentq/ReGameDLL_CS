#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

vec3_t vec3_origin = {0, 0, 0};
int nanmask = 255<<23;

#else

vec3_t vec3_origin;
int nanmask;

#endif // HOOK_GAMEDLL

/* <2ce436> ../cstrike/pm_shared/pm_math.c:35 */
NOBODY float anglemod(float a)
{
	a = (360.0 / 65536) * ((int)(a  *(65536 / 360.0)) & 65535);
	return a;
}

/* <2ce461> ../cstrike/pm_shared/pm_math.c:41 */
void AngleVectors(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up)
{
	float sr, sp, sy, cr, cp;

	float_precision cy;
	float_precision angle;

	angle = (float_precision)(angles[YAW] * (M_PI * 2 / 360));
	sy = sin(angle);
	cy = cos(angle);

	angle = (float_precision)(angles[PITCH] * (M_PI * 2 / 360));
	sp = sin(angle);
	cp = cos(angle);

	angle = (float_precision)(angles[ROLL] * (M_PI * 2 / 360));
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
		right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
		right[2] = -1 * sr * cp;
	}
	if (up)
	{
		up[0] = (cr * sp * cy + -sr * -sy);
		up[1] = (cr * sp * sy + -sr * cy);
		up[2] = cr * cp;
	}
}

/* <2ce521> ../cstrike/pm_shared/pm_math.c:76 */
NOBODY void AngleVectorsTranspose(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up)
{
//	float angle;                                                  //    78
//	float sr;                                                     //    79
//	float sp;                                                     //    79
//	float sy;                                                     //    79
//	float cr;                                                     //    79
//	float cp;                                                     //    79
//	float cy;                                                     //    79
}

/* <2ce5d0> ../cstrike/pm_shared/pm_math.c:112 */
void AngleMatrix(const vec_t *angles, float (*matrix)[4])
{
	float_precision angle;
	float_precision  sr, sp, sy, cr, cp, cy;

	angle = (float_precision)(angles[ROLL] * (M_PI * 2 / 360));
	sy = sin(angle);
	cy = cos(angle);

	angle = (float_precision)(angles[YAW] * (M_PI * 2 / 360));
	sp = sin(angle);
	cp = cos(angle);

	angle = (float_precision)(angles[PITCH] * (M_PI * 2 / 360));
	sr = sin(angle);
	cr = cos(angle);

	matrix[0][0] = cr * cp;
	matrix[1][0] = cr * sp;
	matrix[2][0] = -sr;

	matrix[0][1] = (sy * sr) * cp - cy * sp;
	matrix[1][1] = (sy * sr) * sp + cy * cp;
	matrix[2][1] = sy * cr;

	matrix[0][2] = (cy * sr) * cp + sy * sp;
	matrix[1][2] = (cy * sr) * sp - sy * cp;
	matrix[2][2] = cy * cr;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

/* <2ce67b> ../cstrike/pm_shared/pm_math.c:142 */
NOBODY void AngleIMatrix(const vec_t *angles, float (*matrix)[4])
{
//	float angle;                                                  //   144
//	float sr;                                                     //   145
//	float sp;                                                     //   145
//	float sy;                                                     //   145
//	float cr;                                                     //   145
//	float cp;                                                     //   145
//	float cy;                                                     //   145
}

/* <2ce710> ../cstrike/pm_shared/pm_math.c:172 */
NOBODY void NormalizeAngles(float *angles)
{
//	int i;                                                        //   174
}

/* <2ce75f> ../cstrike/pm_shared/pm_math.c:198 */
NOBODY void InterpolateAngles(float *start, float *end, float *output, float frac)
{
//	int i;                                                        //   200
//	float ang1;                                                   //   201
//	float ang2;                                                   //   201
//	float d;                                                      //   202
//	NormalizeAngles(float *angles);  //   204
//	NormalizeAngles(float *angles);  //   205
//	NormalizeAngles(float *angles);  //   225
}

/* <2ce893> ../cstrike/pm_shared/pm_math.c:235 */
NOBODY float AngleBetweenVectors(const vec_t *v1, const vec_t *v2)
{
//	float angle;                                                  //   237
//	float l1;                                                     //   238
//	float l2;                                                     //   239
//	Length(const vec_t *v);  //   238
//	Length(const vec_t *v);  //   239
}

/* <2ce953> ../cstrike/pm_shared/pm_math.c:251 */
NOBODY void VectorTransform(const vec_t *in1, float *in2, vec_t *out)
{
}

/* <2ce996> ../cstrike/pm_shared/pm_math.c:259 */
int VectorCompare(const vec_t *v1, const vec_t *v2)
{
	int i;
	for (i = 0; i < 3; ++i)
	{
		if (v1[i] != v2[i])
			return 0;
	}
	return 1;
}

/* <2ce9de> ../cstrike/pm_shared/pm_math.c:270 */
void VectorMA(const vec_t *veca, float scale, const vec_t *vecb, vec_t *vecc)
{
	vecc[0] = veca[0] + scale * vecb[0];
	vecc[1] = veca[1] + scale * vecb[1];
	vecc[2] = veca[2] + scale * vecb[2];
}

/* <2cea34> ../cstrike/pm_shared/pm_math.c:278 */
float_precision _DotProduct(vec_t *v1, vec_t *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

/* <2cea6e> ../cstrike/pm_shared/pm_math.c:283 */
void _VectorSubtract(vec_t *veca, vec_t *vecb, vec_t *out)
{
	out[0] = veca[0] - vecb[0];
	out[1] = veca[1] - vecb[1];
	out[2] = veca[2] - vecb[2];
}

/* <2ceab5> ../cstrike/pm_shared/pm_math.c:290 */
void _VectorAdd(vec_t *veca, vec_t *vecb, vec_t *out)
{
	out[0] = veca[0] + vecb[0];
	out[1] = veca[1] + vecb[1];
	out[2] = veca[2] + vecb[2];
}

/* <2ceafc> ../cstrike/pm_shared/pm_math.c:297 */
void _VectorCopy(vec_t *in, vec_t *out)
{
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

/* <2ceb8d> ../cstrike/pm_shared/pm_math.c:307 */
void _CrossProduct(const vec_t *v1, const vec_t *v2, vec_t *cross)
{
	cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
	cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
	cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

/* <2ce85f> ../cstrike/pm_shared/pm_math.c:313 */
float_precision Length(const vec_t *v)
{
	int i;
	float_precision length = 0.0f;

	for (i = 0; i < 3; ++i)
		length += v[i] * v[i];

	return sqrt(length);
}

/* <2cebc2> ../cstrike/pm_shared/pm_math.c:325 */
NOBODY float Distance(const vec_t *v1, const vec_t *v2)
{
//	vec_t *d;                                                     //   327
//	Length(const vec_t *v);  //   329
}

/* <2cec3c> ../cstrike/pm_shared/pm_math.c:332 */
float_precision VectorNormalize(vec_t *v)
{
	float_precision length;
	float_precision ilength;

	length = sqrt((float_precision)(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));

	if (length)
	{
		ilength = 1.0 / length;

		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}

	return length;
}

/* <2ceca2> ../cstrike/pm_shared/pm_math.c:351 */
NOBODY void VectorInverse(vec_t *v)
{
}

/* <2cecc9> ../cstrike/pm_shared/pm_math.c:358 */
void VectorScale(const vec_t *in, vec_t scale, vec_t *out)
{
	out[0] = scale * in[0];
	out[1] = scale * in[1];
	out[2] = scale * in[2];
}

/* <2ced0f> ../cstrike/pm_shared/pm_math.c:366 */
NOBODY int Q_log2(int val)
{
	int answer = 0;
	while (val >>= 1)
		answer++;

	return answer;
}

/* <2ced4d> ../cstrike/pm_shared/pm_math.c:374 */
NOBODY void VectorMatrix(vec_t *forward, vec_t *right, vec_t *up)
{
//	vec3_t *tmp;                                                   //   376
//	CrossProduct(const vec_t *v1,
//			const vec_t *v2,
//			vec_t *cross);  //   390
//	VectorNormalize(vec_t *v);  //   391
//	CrossProduct(const vec_t *v1,
//			const vec_t *v2,
//			vec_t *cross);  //   392
//	VectorNormalize(vec_t *v);  //   393
}

/* <2cee68> ../cstrike/pm_shared/pm_math.c:398 */
NOBODY void VectorAngles(const vec_t *forward, vec_t *angles)
{
//	float tmp;                                                    //   400
//	float yaw;                                                    //   400
//	float pitch;                                                  //   400
}
