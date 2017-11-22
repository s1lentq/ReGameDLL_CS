#include "precompiled.h"

vec3_t vec3_origin = { 0, 0, 0 };
const int nanmask = 255 << 23;

float anglemod(float a)
{
	a = (360.0 / 65536) * (int(a  *(65536 / 360.0)) & 65535);
	return a;
}

void AngleVectors(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up)
{
	float sr, sp, sy, cr, cp;

	real_t cy;
	real_t angle;

	angle = real_t(angles[YAW] * (M_PI * 2 / 360));
	sy = Q_sin(angle);
	cy = Q_cos(angle);

	angle = real_t(angles[PITCH] * (M_PI * 2 / 360));
	sp = Q_sin(angle);
	cp = Q_cos(angle);

	angle = real_t(angles[ROLL] * (M_PI * 2 / 360));
	sr = Q_sin(angle);
	cr = Q_cos(angle);

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

void AngleVectorsTranspose(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up)
{
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = Q_sin(angle);
	cy = Q_cos(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = Q_sin(angle);
	cp = Q_cos(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = Q_sin(angle);
	cr = Q_cos(angle);

	if (forward)
	{
		forward[0] = cp * cy;
		forward[1] = (sr * sp * cy + cr * -sy);
		forward[2] = (cr * sp * cy + -sr * -sy);
	}
	if (right)
	{
		right[0] = cp * sy;
		right[1] = (sr * sp * sy + cr * cy);
		right[2] = (cr * sp * sy + -sr * cy);
	}
	if (up)
	{
		up[0] = -sp;
		up[1] = sr * cp;
		up[2] = cr * cp;
	}
}

void AngleMatrix(const vec_t *angles, float (*matrix)[4])
{
	real_t angle;
	real_t  sr, sp, sy, cr, cp, cy;

	angle = real_t(angles[ROLL] * (M_PI * 2 / 360));
	sy = Q_sin(angle);
	cy = Q_cos(angle);

	angle = real_t(angles[YAW] * (M_PI * 2 / 360));
	sp = Q_sin(angle);
	cp = Q_cos(angle);

	angle = real_t(angles[PITCH] * (M_PI * 2 / 360));
	sr = Q_sin(angle);
	cr = Q_cos(angle);

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

void AngleIMatrix(const vec_t *angles, float (*matrix)[4])
{
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = Q_sin(angle);
	cy = Q_cos(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = Q_sin(angle);
	cp = Q_cos(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = Q_sin(angle);
	cr = Q_cos(angle);

	// matrix = (YAW * PITCH) * ROLL
	matrix[0][0] = cp * cy;
	matrix[0][1] = cp * sy;
	matrix[0][2] = -sp;
	matrix[1][0] = sr * sp * cy + cr * -sy;
	matrix[1][1] = sr * sp * sy + cr * cy;
	matrix[1][2] = sr * cp;
	matrix[2][0] = (cr * sp * cy + -sr * -sy);
	matrix[2][1] = (cr * sp * sy + -sr * cy);
	matrix[2][2] = cr * cp;
	matrix[0][3] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][3] = 0.0;
}

void NormalizeAngles(float *angles)
{
	// Normalize angles
	for (int i = 0; i < 3; i++)
	{
		if (angles[i] > 180.0)
		{
			angles[i] -= 360.0;
		}
		else if (angles[i] < -180.0)
		{
			angles[i] += 360.0;
		}
	}
}

// Interpolate Euler angles.
// FIXME:  Use Quaternions to avoid discontinuities
// Frac is 0.0 to 1.0 (i.e., should probably be clamped, but doesn't have to be)
void InterpolateAngles(float *start, float *end, float *output, float frac)
{
	int i;
	float ang1, ang2;
	float d;

	NormalizeAngles(start);
	NormalizeAngles(end);

	for (i = 0; i < 3; i++)
	{
		ang1 = start[i];
		ang2 = end[i];

		d = ang2 - ang1;
		if (d > 180)
		{
			d -= 360;
		}
		else if (d < -180)
		{
			d += 360;
		}

		output[i] = ang1 + d * frac;
	}

	NormalizeAngles(output);
}

float AngleBetweenVectors(const vec_t *v1, const vec_t *v2)
{
	float angle;
	float l1 = Length(v1);
	float l2 = Length(v2);

	if (!l1 || !l2)
		return 0.0f;

	angle = Q_acos(DotProduct(v1, v2)) / (l1 * l2);
	angle = (angle * 180.0f) / M_PI;

	return angle;
}

void VectorTransform(const vec_t *in1, float (*in2)[4], vec_t *out)
{
	out[0] = DotProduct(in1, in2[0]) + in2[0][3];
	out[1] = DotProduct(in1, in2[1]) + in2[1][3];
	out[2] = DotProduct(in1, in2[2]) + in2[2][3];
}

int VectorCompare(const vec_t *v1, const vec_t *v2)
{
	for (int i = 0; i < 3; i++)
	{
		if (v1[i] != v2[i])
			return 0;
	}

	return 1;
}

void VectorMA(const vec_t *veca, float scale, const vec_t *vecb, vec_t *vecc)
{
	vecc[0] = veca[0] + scale * vecb[0];
	vecc[1] = veca[1] + scale * vecb[1];
	vecc[2] = veca[2] + scale * vecb[2];
}

real_t _DotProduct(const vec_t *v1, const vec_t *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void _VectorSubtract(vec_t *veca, vec_t *vecb, vec_t *out)
{
	out[0] = veca[0] - vecb[0];
	out[1] = veca[1] - vecb[1];
	out[2] = veca[2] - vecb[2];
}

void _VectorAdd(vec_t *veca, vec_t *vecb, vec_t *out)
{
	out[0] = veca[0] + vecb[0];
	out[1] = veca[1] + vecb[1];
	out[2] = veca[2] + vecb[2];
}

void _VectorCopy(vec_t *in, vec_t *out)
{
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

void CrossProduct(const vec_t *v1, const vec_t *v2, vec_t *cross)
{
	cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
	cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
	cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

real_t Length(const vec_t *v)
{
	real_t length = 0.0f;

	for (int i = 0; i < 3; i++)
		length += v[i] * v[i];

	return Q_sqrt(length);
}

float Distance(const vec_t *v1, const vec_t *v2)
{
	vec_t d[3];
	VectorSubtract(v2, v1, d);
	return Length(d);
}

real_t VectorNormalize(vec_t *v)
{
	real_t length;
	real_t ilength;

	length = Q_sqrt(real_t(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));

	if (length)
	{
		ilength = 1.0 / length;

		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}

	return length;
}

void VectorInverse(vec_t *v)
{
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}

void VectorScale(const vec_t *in, vec_t scale, vec_t *out)
{
	out[0] = scale * in[0];
	out[1] = scale * in[1];
	out[2] = scale * in[2];
}

int Q_log2(int val)
{
	int answer = 0;
	while (val >>= 1)
		answer++;

	return answer;
}

void VectorMatrix(vec_t *forward, vec_t *right, vec_t *up)
{
	vec_t tmp[3];

	if (forward[0] == 0 && forward[1] == 0)
	{
		right[0] = 1;
		right[1] = 0;
		right[2] = 0;

		up[0] = -forward[2];
		up[1] = 0;
		up[2] = 0;
		return;
	}

	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 1.0f;

	CrossProduct(forward, tmp, right);
	VectorNormalize(right);
	CrossProduct(right, forward, up);
	VectorNormalize(up);
}

void VectorAngles(const vec_t *forward, vec_t *angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		yaw = (Q_atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = Q_sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (Q_atan2(forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
