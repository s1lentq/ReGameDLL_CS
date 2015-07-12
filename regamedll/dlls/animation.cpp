#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

sv_blending_interface_t svBlending =
{
	SV_BLENDING_INTERFACE_VERSION,
	SV_StudioSetupBones
};

#else

sv_blending_interface_t svBlending;

#endif // HOOK_GAMEDLL

server_studio_api_t IEngineStudio;
studiohdr_t *g_pstudiohdr;

float (*g_pRotationMatrix)[3][4];
float (*g_pBoneTransform)[128][3][4];

float omega;
float cosom;
float sinom;
float sclp;
float sclq;

/* <1523e> ../cstrike/dlls/animation.cpp:57 */
NOBODY int ExtractBbox(void *pmodel, int sequence, float *mins, float *maxs)
{
//	{
//		studiohdr_t *pstudiohdr;                             //    59
//		mstudioseqdesc_t *pseqdesc;                          //    65
//	}
}

/* <152c6> ../cstrike/dlls/animation.cpp:81 */
int LookupActivity(void *pmodel, entvars_t *pev, int activity)
{
	int i;
	int weightTotal = 0;
	int activitySequenceCount = 0;
	int weight = 0;
	int select;

	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr)
		return 0;

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);
	for (i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].activity == activity)
		{
			weightTotal += pseqdesc[i].actweight;
			activitySequenceCount++;
		}
	}
	if (activitySequenceCount)
	{
		if (!weightTotal)
		{
			select = RANDOM_LONG(0, activitySequenceCount - 1);
			for (i = 0; i < pstudiohdr->numseq; i++)
			{
				if (pseqdesc[i].activity == activity)
				{
					if (!select)
						return i;
					--select;
				}
			}
			return ACTIVITY_NOT_AVAILABLE;
		}
		select = RANDOM_LONG(0, weightTotal - 1);
		for (i = 0; i < pstudiohdr->numseq; i++)
		{
			if (pseqdesc[i].activity == activity)
			{
				weight += pseqdesc[i].actweight;
				if (weight > select)
					return i;
			}
		}
	}
	return ACTIVITY_NOT_AVAILABLE;
}

/* <1539a> ../cstrike/dlls/animation.cpp:149 */
NOBODY int LookupActivityHeaviest(void *pmodel, entvars_t *pev, int activity)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   151
//		mstudioseqdesc_t *pseqdesc;                          //   157
//		int weight;                                           //   161
//		int seq;                                              //   162
//		{
//			int i;                                        //   163
//		}
//	}
}

/* <15439> ../cstrike/dlls/animation.cpp:178 */
NOBODY void GetEyePosition(void *pmodel, float *vecEyePosition)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   180
//	}
}

/* <15485> ../cstrike/dlls/animation.cpp:193 */
int LookupSequence(void *pmodel, const char *label)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr)
		return 0;

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);
	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (!Q_stricmp(pseqdesc[i].label, label))
			return i;
	}
	return -1;
}

/* <1518c> ../cstrike/dlls/animation.cpp:215 */
NOBODY int IsSoundEvent(int eventNumber)
{
}

/* <15539> ../cstrike/dlls/animation.cpp:223 */
NOBODY void SequencePrecache(void *pmodel, const char *pSequenceName)
{
//	{
//		int index;                                            //   225
//		LookupSequence(void *pmodel,
//				const char *label);  //   225
//		{
//			studiohdr_t *pstudiohdr;                     //   228
//			mstudioseqdesc_t *pseqdesc;                  //   234
//			mstudioevent_t *pevent;                      //   235
//			{
//				int i;                                //   240
//				IsSoundEvent(int eventNumber);  //   248
//			}
//		}
//	}
}

/* <15634> ../cstrike/dlls/animation.cpp:263 */
void GetSequenceInfo(void *pmodel, entvars_t *pev, float *pflFrameRate, float *pflGroundSpeed)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr)
		return;

	if (pev->sequence >= pstudiohdr->numseq)
	{
		*pflFrameRate = 0;
		*pflGroundSpeed = 0;
		return;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;
	if (pseqdesc->numframes <= 1)
	{
		*pflFrameRate = 256.0f;
		*pflGroundSpeed = 0.0f;
		return;
	}

	*pflFrameRate = pseqdesc->fps * 256.0f / (pseqdesc->numframes - 1);
	*pflGroundSpeed = sqrt(pseqdesc->linearmovement[0] * pseqdesc->linearmovement[0] + pseqdesc->linearmovement[1] * pseqdesc->linearmovement[1] + pseqdesc->linearmovement[2] * pseqdesc->linearmovement[2]);
	*pflGroundSpeed = *pflGroundSpeed * pseqdesc->fps / (pseqdesc->numframes - 1);
}

/* <156b3> ../cstrike/dlls/animation.cpp:297 */
int GetSequenceFlags(void *pmodel, entvars_t *pev)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr || pev->sequence >= pstudiohdr->numseq)
		return 0;

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;
	return pseqdesc->flags;
}

/* <15717> ../cstrike/dlls/animation.cpp:312 */
NOBODY int GetAnimationEvent(void *pmodel, entvars_t *pev, MonsterEvent_t *pMonsterEvent, float flStart, float flEnd, int index)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   314
//		int events;                                           //   320
//		mstudioseqdesc_t *pseqdesc;                          //   322
//		mstudioevent_t *pevent;                              //   323
//	}
}

/* <157e1> ../cstrike/dlls/animation.cpp:359 */
float SetController(void *pmodel, entvars_t *pev, int iController, float flValue)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
		return flValue;

	int i;
	mstudiobonecontroller_t *pbonecontroller = (mstudiobonecontroller_t *)((byte *)pstudiohdr + pstudiohdr->bonecontrollerindex);
	for (i = 0; i < pstudiohdr->numbonecontrollers; i++, pbonecontroller++)
	{
		if (pbonecontroller->index == iController)
			break;
	}

	if (i >= pstudiohdr->numbonecontrollers)
		return flValue;

	if (pbonecontroller->type & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		if (pbonecontroller->end < pbonecontroller->start)
			flValue = -flValue;

		if (pbonecontroller->end > pbonecontroller->start + 359.0)
		{
			if (flValue > 360.0)
				flValue = flValue - (int64_t)(flValue / 360.0) * 360.0;

			else if (flValue < 0.0)
				flValue = flValue + (int64_t)((flValue / -360.0) + 1) * 360.0;
		}
		else
		{
			if (flValue > ((pbonecontroller->start + pbonecontroller->end) / 2) + 180)
				flValue -= 360;

			if (flValue < ((pbonecontroller->start + pbonecontroller->end) / 2) - 180)
				flValue += 360;
		}
	}

	int setting = (int64_t)(255.0f * (flValue - pbonecontroller->start) / (pbonecontroller->end - pbonecontroller->start));

	if (setting < 0)
		setting = 0;

	if (setting > 255)
		setting = 255;

	pev->controller[ iController ] = setting;

	return setting * (1.0f / 255.0f) * (pbonecontroller->end - pbonecontroller->start) + pbonecontroller->start;
}

/* <15883> ../cstrike/dlls/animation.cpp:414 */
NOBODY float SetBlending(void *pmodel, entvars_t *pev, int iBlender, float flValue)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   416
//		mstudioseqdesc_t *pseqdesc;                          //   422
//		int setting;                                          //   445
//	}
}

/* <15917> ../cstrike/dlls/animation.cpp:458 */
NOBODY int FindTransition(void *pmodel, int iEndingAnim, int iGoalAnim, int *piDir)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   460
//		mstudioseqdesc_t *pseqdesc;                          //   466
//		int iEndNode;                                         //   475
//		byte *pTransition;                                   //   492
//		int iInternNode;                                      //   494
//		int i;                                                //   499
//	}
}

/* <159d8> ../cstrike/dlls/animation.cpp:523 */
NOBODY void SetBodygroup(void *pmodel, entvars_t *pev, int iGroup, int iValue)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   525
//		mstudiobodyparts_t *pbodypart;                       //   534
//		int iCurrent;                                         //   539
//	}
}

/* <15a6d> ../cstrike/dlls/animation.cpp:545 */
int GetBodygroup(void *pmodel, entvars_t *pev, int iGroup)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
		return 0;

	if (iGroup > pstudiohdr->numbodyparts)
		return 0;

	mstudiobodyparts_t *pbodypart = (mstudiobodyparts_t *)((byte *)pstudiohdr + pstudiohdr->bodypartindex) + iGroup;

	if (pbodypart->nummodels <= 1)
		return 0;

	int iCurrent = (pev->body / pbodypart->base) % pbodypart->nummodels;
	return iCurrent;
}

/* <15aed> ../cstrike/dlls/animation.cpp:605 */
C_DLLEXPORT int Server_GetBlendingInterface(int version, struct sv_blending_interface_s **ppinterface, struct engine_studio_api_s *pstudio, float *rotationmatrix, float *bonetransform)
{
	if (version != SV_BLENDING_INTERFACE_VERSION)
		return 0;

	*ppinterface = &svBlending;

	IEngineStudio.Mem_Calloc = pstudio->Mem_Calloc;
	IEngineStudio.Cache_Check = pstudio->Cache_Check;
	IEngineStudio.LoadCacheFile = pstudio->LoadCacheFile;
	IEngineStudio.Mod_Extradata = ((struct server_studio_api_s *)pstudio)->Mod_Extradata;

	g_pRotationMatrix = (float (*)[3][4])rotationmatrix;
	g_pBoneTransform = (float (*)[128][3][4])bonetransform;

	return 1;
}

/* <15ba5> ../cstrike/dlls/animation.cpp:630 */
#ifdef REGAMEDLL_FIXES // SSE2 version
void AngleQuaternion(vec_t *angles, vec_t *quaternion)
{
	static const ALIGN16_BEG int ps_signmask[4] ALIGN16_END = { 0x80000000, 0, 0x80000000, 0 };

	__m128 a = _mm_loadu_ps(angles);
	a = _mm_mul_ps(a, _mm_load_ps(_ps_0p5)); //a *= 0.5
	__m128 s, c;
	sincos_ps(a, &s, &c);

	__m128 im1 = _mm_shuffle_ps(s, c, _MM_SHUFFLE(1, 0, 1, 0)); //im1 =  {sin[0], sin[1], cos[0], cos[1] }
	__m128 im2 = _mm_shuffle_ps(c, s, _MM_SHUFFLE(2, 2, 2, 2)); //im2 =  {cos[2], cos[2], sin[2], sin[2] }

	__m128 part1 = _mm_mul_ps(
		_mm_shuffle_ps(im1, im1, _MM_SHUFFLE(1, 2, 2, 0)),
		_mm_shuffle_ps(im1, im1, _MM_SHUFFLE(0, 3, 1, 3))
		);
	part1 = _mm_mul_ps(part1, im2);

	__m128 part2 = _mm_mul_ps(
		_mm_shuffle_ps(im1, im1, _MM_SHUFFLE(2, 1, 0, 2)),
		_mm_shuffle_ps(im1, im1, _MM_SHUFFLE(3, 0, 3, 1))
		);

	part2 = _mm_mul_ps(part2, _mm_shuffle_ps(im2, im2, _MM_SHUFFLE(0, 0, 2, 2)));

	__m128 signmask = _mm_load_ps((float*)ps_signmask);
	part2 = _mm_xor_ps(part2, signmask);

	__m128 res = _mm_add_ps(part1, part2);
	_mm_storeu_ps(quaternion, res);
}
#else //REGAMEDLL_FIXES
void AngleQuaternion(vec_t *angles, vec_t *quaternion)
{
	long double sy; // st7@1
	long double cy; // st6@1
	double sp_; // qt1@1
	long double cp; // st4@1
	float sr; // ST08_4@1
	float cr; // ST04_4@1
	float ftmp0; // ST00_4@1
	float ftmp1; // [sp+10h] [bp+4h]@1
	float ftmp2; // [sp+10h] [bp+4h]@1

	long double	angle;

	angle = angles[2] * 0.5;
	sy = sin(angle);
	cy = cos(angle);

	angle = angles[1] * 0.5;
	sp_ = sin(angle);
	cp = cos(angle);

	angle = angles[0] * 0.5;
	sr = sin(angle);
	cr = cos(angle);

	ftmp0 = sr * cp;
	ftmp1 = cr * sp_;
	*quaternion = ftmp0 * cy - ftmp1 * sy;
	quaternion[1] = ftmp1 * cy + ftmp0 * sy;
	ftmp2 = cr * cp;
	quaternion[2] = ftmp2 * sy - sp_ * sr * cy;
	quaternion[3] = sp_ * sr * sy + ftmp2 * cy;
}
#endif //REGAMEDLL_FIXES

/* <15c4d> ../cstrike/dlls/animation.cpp:653 */
void QuaternionSlerp(vec_t *p, vec_t *q, float t, vec_t *qt)
{
	int i;
	float_precision a = 0;
	float_precision b = 0;

	for (i = 0; i < 4; i++)
	{
		a += (p[i] - q[i]) * (p[i] - q[i]);
		b += (p[i] + q[i]) * (p[i] + q[i]);
	}

	if (a > b)
	{
		for (i = 0; i < 4; i++)
			q[i] = -q[i];
	}

	cosom = (p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3]);

	if ((1.0 + cosom) > 0.00000001)
	{
		if ((1.0 - cosom) > 0.00000001)
		{
			float_precision cosomega = acos((float_precision)cosom);

			omega = cosomega;
			sinom = sin(cosomega);

			sclp = sin((1.0 - t) * omega) / sinom;
			sclq = sin(omega * t) / sinom;
		}
		else
		{
			sclq = t;
			sclp = 1.0 - t;
		}

		for (i = 0; i < 4; i++)
			qt[i] = sclp * p[i] + sclq * q[i];
	}
	else
	{
		qt[0] = -q[1];
		qt[1] = q[0];
		qt[2] = -q[3];
		qt[3] = q[2];

		sclp = sin((1.0 - t) * 0.5 * M_PI);
		sclq = sin(t * 0.5 * M_PI);

		for (i = 0; i < 3; i++)
			qt[i] = sclp * p[i] + sclq * qt[i];
	}
}

void (*pQuaternionMatrix)(vec_t *quaternion, float matrix[3][4]);

/* <15cd0> ../cstrike/dlls/animation.cpp:700 */
NOBODY void __declspec(naked) QuaternionMatrix(vec_t *quaternion, float matrix[3][4])
{
	UNTESTED
	__asm
	{
		jmp pQuaternionMatrix
	}

	//matrix[0][0] = 1.0 - 2.0 * quaternion[1] * quaternion[1] - 2.0 * quaternion[2] * quaternion[2];
	//matrix[1][1] = 2.0 * quaternion[2] * quaternion[3] + quaternion[0] * quaternion[1];
	//matrix[2][2] = 2.0 * quaternion[2] * quaternion[0] - 2.0 * quaternion[3] * quaternion[1];
	//matrix[0][1] = 2.0 * quaternion[0] * quaternion[1] - 2.0 * quaternion[2] * quaternion[3];
	//matrix[1][2] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[2] * quaternion[2];
	//matrix[3][0] = 2.0 * quaternion[2] * quaternion[1] + quaternion[0] * quaternion[3];
	//matrix[0][2] = 2.0 * quaternion[2] * quaternion[0] + quaternion[3] * quaternion[1];
	//matrix[2][0] = 2.0 * quaternion[2] * quaternion[1] - 2.0 * quaternion[0] * quaternion[3];
}

/* <15d12> ../cstrike/dlls/animation.cpp:715 */
mstudioanim_t *StudioGetAnim(model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc)
{
	mstudioseqgroup_t *pseqgroup;
	cache_user_t *paSequences;

	pseqgroup = (mstudioseqgroup_t *)((byte *)g_pstudiohdr + g_pstudiohdr->seqgroupindex) + pseqdesc->seqgroup;

	if (pseqdesc->seqgroup == 0)
	{
		return (mstudioanim_t *)((byte *)g_pstudiohdr + pseqdesc->animindex);
	}
		
	paSequences = (cache_user_t *)m_pSubModel->submodels;

	if (paSequences == NULL)
	{
		paSequences = (cache_user_t *)IEngineStudio.Mem_Calloc(16, sizeof(cache_user_t)); // UNDONE: leak!
		m_pSubModel->submodels = (dmodel_t *)paSequences;
	}

	if (!IEngineStudio.Cache_Check((struct cache_user_s *)&(paSequences[ pseqdesc->seqgroup ])))
	{
		IEngineStudio.LoadCacheFile(pseqgroup->name, (struct cache_user_s *)&paSequences[ pseqdesc->seqgroup ]);
	}

	return (mstudioanim_t *)((byte *)paSequences[ pseqdesc->seqgroup ].data + pseqdesc->animindex);
}

/* <15d90> ../cstrike/dlls/animation.cpp:749 */
NOXREF mstudioanim_t *LookupAnimation(studiohdr_t *pstudiohdr, model_s *model, mstudioseqdesc_t *pseqdesc, int index)
{
	mstudioanim_t *panim = StudioGetAnim(model, pseqdesc);
	if (index >= 0 && index <= (pseqdesc->numblends - 1))
		panim += index * pstudiohdr->numbones;

	return panim;
}

/* <151a9> ../cstrike/dlls/animation.cpp:770 */
void StudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen)
{
	int i, j;
	float value;
	mstudiobonecontroller_t *pbonecontroller;

	pbonecontroller = (mstudiobonecontroller_t *)((byte *)g_pstudiohdr + g_pstudiohdr->bonecontrollerindex);

	for (j = 0; j < g_pstudiohdr->numbonecontrollers; j++)
	{
		i = pbonecontroller[j].index;
		if (i <= 3)
		{
			// check for 360% wrapping
			if (pbonecontroller[j].type & STUDIO_RLOOP)
			{
				if (abs(pcontroller1[i] - pcontroller2[i]) > 128)
				{
					int a, b;
					a = (pcontroller1[j] + 128) % 256;
					b = (pcontroller2[j] + 128) % 256;
					value = ((a * dadt) + (b * (1 - dadt)) - 128) * (360.0/256.0) + pbonecontroller[j].start;
				}
				else
				{
					value = ((pcontroller1[i] * dadt + (pcontroller2[i]) * (1.0 - dadt))) * (360.0/256.0) + pbonecontroller[j].start;
				}
			}
			else
			{
				value = (pcontroller1[i] * dadt + pcontroller2[i] * (1.0 - dadt)) / 255.0;

				if (value < 0)
					value = 0;

				if (value > 1.0)
					value = 1.0;

				value = (1.0 - value) * pbonecontroller[j].start + value * pbonecontroller[j].end;
			}
		}
		else
		{
			value = mouthopen / 64.0;

			if (value > 1.0)
				value = 1.0;

			value = (1.0 - value) * pbonecontroller[j].start + value * pbonecontroller[j].end;
		}
		switch(pbonecontroller[j].type & STUDIO_TYPES)
		{
		case STUDIO_XR:
		case STUDIO_YR:
		case STUDIO_ZR:
			adj[j] = value * (M_PI / 180.0);
			break;
		case STUDIO_X:
		case STUDIO_Y:
		case STUDIO_Z:
			adj[j] = value;
			break;
		}
	}
}

/* <15ea6> ../cstrike/dlls/animation.cpp:828 */
void StudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q)
{
	int j, k;
	vec4_t q1, q2;
	vec3_t angle1, angle2;
	mstudioanimvalue_t *panimvalue;

	for (j = 0; j < 3; j++)
	{
		if (panim->offset[j + 3] == 0)
		{
			// default;
			angle2[j] = angle1[j] = pbone->value[j + 3];
		}
		else
		{
			panimvalue = (mstudioanimvalue_t *)((byte *)panim + panim->offset[j + 3]);
			k = frame;

			if (panimvalue->num.total < panimvalue->num.valid)
				k = 0;

			while (panimvalue->num.total <= k)
			{
				k -= panimvalue->num.total;
				panimvalue += panimvalue->num.valid + 1;

				if (panimvalue->num.total < panimvalue->num.valid)
					k = 0;
			}

			// Bah, missing blend!
			if (panimvalue->num.valid > k)
			{
				angle1[j] = panimvalue[k + 1].value;

				if (panimvalue->num.valid > k + 1)
				{
					angle2[j] = panimvalue[k + 2].value;
				}
				else
				{
					if (panimvalue->num.total > k + 1)
						angle2[j] = angle1[j];
					else
						angle2[j] = panimvalue[panimvalue->num.valid + 2].value;
				}
			}
			else
			{
				angle1[j] = panimvalue[panimvalue->num.valid].value;
				if (panimvalue->num.total > k + 1)
				{
					angle2[j] = angle1[j];
				}
				else
				{
					angle2[j] = panimvalue[panimvalue->num.valid + 2].value;
				}
			}
			angle1[j] = pbone->value[j + 3] + angle1[j] * pbone->scale[j + 3];
			angle2[j] = pbone->value[j + 3] + angle2[j] * pbone->scale[j + 3];
		}

		if (pbone->bonecontroller[j + 3] != -1)
		{
			angle1[j] += adj[pbone->bonecontroller[j + 3]];
			angle2[j] += adj[pbone->bonecontroller[j + 3]];
		}
	}

	if (!VectorCompare(angle1, angle2))
	{
		AngleQuaternion(angle1, q1);
		AngleQuaternion(angle2, q2);
		QuaternionSlerp(q1, q2, s, q);
	}
	else
		AngleQuaternion(angle1, q);
}

/* <15f94> ../cstrike/dlls/animation.cpp:908 */
void StudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos)
{
	int j, k;
	mstudioanimvalue_t *panimvalue;

	for (j = 0; j < 3; j++)
	{
		// default;
		pos[j] = pbone->value[j];
		if (panim->offset[j] != 0)
		{
			panimvalue = (mstudioanimvalue_t *)((byte *)panim + panim->offset[j]);

			k = frame;

			if (panimvalue->num.total < panimvalue->num.valid)
				k = 0;

			// find span of values that includes the frame we want
			while (panimvalue->num.total <= k)
			{
				k -= panimvalue->num.total;
				panimvalue += panimvalue->num.valid + 1;

				if (panimvalue->num.total < panimvalue->num.valid)
					k = 0;
			}
			// if we're inside the span
			if (panimvalue->num.valid > k)
			{
				// and there's more data in the span
				if (panimvalue->num.valid > k + 1)
					pos[j] += (panimvalue[k + 1].value * (1.0 - s) + s * panimvalue[k + 2].value) * pbone->scale[j];
				else
					pos[j] += panimvalue[k + 1].value * pbone->scale[j];
			}
			else
			{
				// are we at the end of the repeating values section and there's another section with data?
				if (panimvalue->num.total <= k + 1)
					pos[j] += (panimvalue[panimvalue->num.valid].value * (1.0 - s) + s * panimvalue[panimvalue->num.valid + 2].value) * pbone->scale[j];

				else
					pos[j] += panimvalue[panimvalue->num.valid].value * pbone->scale[j];
			}
		}
		if (pbone->bonecontroller[j] != -1 && adj)
		{
			pos[j] += adj[pbone->bonecontroller[j]];
		}
	}
}

/* <1603c> ../cstrike/dlls/animation.cpp:970 */
void StudioSlerpBones(vec4_t *q1, float pos1[][3], vec4_t *q2, float pos2[][3], float s)
{
	int i;
	vec4_t q3;
	float s1;

	if (s < 0)
		s = 0;

	else if (s > 1.0)
		s = 1.0;

	s1 = 1.0 - s;

	for (i = 0; i < g_pstudiohdr->numbones; i++)
	{
		QuaternionSlerp(q1[i], q2[i], s, q3);

		q1[i][0] = q3[0];
		q1[i][1] = q3[1];
		q1[i][2] = q3[2];
		q1[i][3] = q3[3];

		pos1[i][0] = pos1[i][0] * s1 + pos2[i][0] * s;
		pos1[i][1] = pos1[i][1] * s1 + pos2[i][1] * s;
		pos1[i][2] = pos1[i][2] * s1 + pos2[i][2] * s;
	}
}

/* <160de> ../cstrike/dlls/animation.cpp:994 */
NOXREF void StudioCalcRotations(mstudiobone_t *pbones, int *chain, int chainlength, float *adj, float pos[128][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, float s)
{
	int i;
	int j;

	for (i = chainlength - 1; i >= 0; i--)
	{
		j = chain[i];

		StudioCalcBoneQuaterion((int)f, s, &pbones[ j ], &panim[ j ], adj, &(*q)[j]);
		StudioCalcBonePosition((int)f, s, &pbones[ j ], &panim[ j ], adj, pos[j]);
	}
}

/* <161fd> ../cstrike/dlls/animation.cpp:1006 */
void ConcatTransforms(float in1[3][4], float in2[3][4], float out[3][4])
{
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] + in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] + in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] + in1[0][2] * in2[2][2];
	out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] + in1[0][2] * in2[2][3] + in1[0][3];

	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] + in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] + in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] + in1[1][2] * in2[2][2];
	out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] + in1[1][2] * in2[2][3] + in1[1][3];

	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] + in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] + in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] + in1[2][2] * in2[2][2];
	out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] + in1[2][2] * in2[2][3] + in1[2][3];
}

/* <16247> ../cstrike/dlls/animation.cpp:1115 */
NOBODY void SV_StudioSetupBones(struct model_s *pModel, float frame, int sequence, const vec_t *angles, const vec_t *origin, const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict)
{
//	{
//		int i;                                                //  1117
//		int j;                                                //  1117
//		float f;                                              //  1118
//		float subframe;                                       //  1118
//		float adj;                                            //  1119
//		mstudiobone_t *pbones;                               //  1120
//		mstudioseqdesc_t *pseqdesc;                          //  1121
//		mstudioanim_t *panim;                                //  1122
//		float pos;                                            //  1124
//		float bonematrix;                                     //  1125
//		float q;                                              //  1126
//		float pos3;                                           //  1127
//		float q2;                                             //  1128
//		int chain;                                            //  1130
//		int chainlength;                                      //  1131
//		vec3_t temp_angles;                                   //  1354
//		StudioCalcBoneAdj(float dadt,
//					float *adj,
//					const byte *pcontroller1,
//					const byte *pcontroller2,
//					byte mouthopen);  //  1175
//		{
//			float b;                                      //  1295
//		}
//		{
//			float pos3;                                   //  1186
//			float q3;                                     //  1187
//			float pos4;                                   //  1188
//			float q4;                                     //  1189
//			float s;                                      //  1191
//			float t;                                      //  1192
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1236
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1237
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1238
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1239
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1240
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1241
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1242
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1243
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1257
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1258
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1259
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1260
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1261
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1262
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1263
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1264
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1272
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1273
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1274
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1275
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1276
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1277
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1278
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1279
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1222
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1223
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1224
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1225
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1226
//			LookupAnimation(studiohdr_t *pstudiohdr,
//					model_s *model,
//					mstudioseqdesc_t *pseqdesc,
//					int index);  //  1227
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1228
//		}
//		{
//			int copy;                                     //  1323
//			int gaitsequence;                             //  1324
//			StudioCalcRotations(mstudiobone_t *pbones,
//						int *chain,
//						int chainlength,
//						float *adj,
//						float *pos,
//						vec4_t *q,
//						mstudioseqdesc_t *pseqdesc,
//						mstudioanim_t *panim,
//						float f,
//						float s);  //  1333
//		}
//	}
}
