#include "precompiled.h"

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
NOBODY int GetBodygroup(void *pmodel, entvars_t *pev, int iGroup)
{
//	{
//		studiohdr_t *pstudiohdr;                             //   547
//		mstudiobodyparts_t *pbodypart;                       //   556
//		int iCurrent;                                         //   561
//	}
}

/* <15aed> ../cstrike/dlls/animation.cpp:605 */
NOBODY int Server_GetBlendingInterface(int version, sv_blending_interface_s **ppinterface, engine_studio_api_s *pstudio, float *rotationmatrix, float *bonetransform)
{
	return 0;
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
NOBODY void QuaternionSlerp(vec_t *p, vec_t *q, float t, vec_t *qt)
{
//	{
//		int i;                                                //   655
//		float a;                                              //   658
//		float b;                                              //   659
//	}
}

/* <15cd0> ../cstrike/dlls/animation.cpp:700 */
NOBODY void QuaternionMatrix(vec_t *quaternion, float *matrix)
{
}

/* <15d12> ../cstrike/dlls/animation.cpp:715 */
NOBODY mstudioanim_t *StudioGetAnim(model_t *m_pSubModel, mstudioseqdesc_t *pseqdesc)
{
//	{
//		mstudioseqgroup_t *pseqgroup;                        //   717
//		cache_user_t *paSequences;                           //   718
//	}
}

/* <15d90> ../cstrike/dlls/animation.cpp:749 */
NOBODY mstudioanim_t *LookupAnimation(studiohdr_t *pstudiohdr, model_s *model, mstudioseqdesc_t *pseqdesc, int index)
{
//	{
//		mstudioanim_t *panim;                                //   751
//	}
}

/* <151a9> ../cstrike/dlls/animation.cpp:770 */
NOBODY void StudioCalcBoneAdj(float dadt, float *adj, const byte *pcontroller1, const byte *pcontroller2, byte mouthopen)
{
//	{
//		int i;                                                //   772
//		int j;                                                //   772
//		float value;                                          //   773
//		mstudiobonecontroller_t *pbonecontroller;            //   774
//		{
//			int a;                                        //   788
//			int b;                                        //   788
//		}
//	}
}

/* <15ea6> ../cstrike/dlls/animation.cpp:828 */
NOBODY void StudioCalcBoneQuaterion(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *q)
{
//	{
//		int j;                                                //   830
//		int k;                                                //   830
//		vec4_t q1;                                            //   831
//		vec4_t q2;                                            //   831
//		vec3_t angle1;                                        //   832
//		vec3_t angle2;                                        //   832
//		mstudioanimvalue_t *panimvalue;                      //   833
//	}
}

/* <15f94> ../cstrike/dlls/animation.cpp:908 */
NOBODY void StudioCalcBonePosition(int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *adj, float *pos)
{
//	{
//		int j;                                                //   910
//		int k;                                                //   910
//		mstudioanimvalue_t *panimvalue;                      //   911
//	}
}

/* <1603c> ../cstrike/dlls/animation.cpp:970 */
NOBODY void StudioSlerpBones(vec4_t *q1, vec3_t *pos1, vec4_t *q2, vec3_t *pos2, float s)
{
//	{
//		int i;                                                //   972
//		vec4_t q3;                                            //   973
//		float s1;                                             //   974
//	}
}

/* <160de> ../cstrike/dlls/animation.cpp:994 */
NOBODY void StudioCalcRotations(mstudiobone_t *pbones, int *chain, int chainlength, float *adj, float *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, float s)
{
//	{
//		int i;                                                //   996
//		int j;                                                //   996
//	}
}

/* <161fd> ../cstrike/dlls/animation.cpp:1006 */
NOBODY void ConcatTransforms(float *in1, float *in2, float *out)
{
}

/* <16247> ../cstrike/dlls/animation.cpp:1115 */
NOBODY void SV_StudioSetupBones(model_s *pModel, float frame, int sequence, const vec_t *angles, const vec_t *origin, const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict)
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
//		float pos2;                                           //  1127
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
