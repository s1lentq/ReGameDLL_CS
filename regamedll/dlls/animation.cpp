#include "precompiled.h"

void EXT_FUNC SV_StudioSetupBones(model_t *pModel, float frame, int sequence, const vec_t *angles, const vec_t *origin, const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict);

sv_blending_interface_t svBlending =
{
	SV_BLENDING_INTERFACE_VERSION,
	SV_StudioSetupBones
};

server_studio_api_t IEngineStudio;
studiohdr_t *g_pstudiohdr;

float (*g_pRotationMatrix)[3][4];
float (*g_pBoneTransform)[128][3][4];

int ExtractBbox(void *pmodel, int sequence, float *mins, float *maxs)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		return 0;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	mins[0] = pseqdesc[sequence].bbmin[0];
	mins[1] = pseqdesc[sequence].bbmin[1];
	mins[2] = pseqdesc[sequence].bbmin[2];

	maxs[0] = pseqdesc[sequence].bbmax[0];
	maxs[1] = pseqdesc[sequence].bbmax[1];
	maxs[2] = pseqdesc[sequence].bbmax[2];

	return 1;
}

int LookupActivity(void *pmodel, entvars_t *pev, int activity)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		return 0;
	}

	mstudioseqdesc_t *pseqdesc;

	int i;
	int weightTotal = 0;
	int activitySequenceCount = 0;
	int weight = 0;
	int select;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	for (i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].activity == activity)
		{
			weightTotal += pseqdesc[i].actweight;
			activitySequenceCount++;
		}
	}

	if (activitySequenceCount > 0)
	{
		if (weightTotal)
		{
			int which = RANDOM_LONG(0, weightTotal - 1);

			for (i = 0; i < pstudiohdr->numseq; i++)
			{
				if (pseqdesc[i].activity == activity)
				{
					weight += pseqdesc[i].actweight;

					if (weight > which)
					{
						return i;
					}
				}
			}
		}
		else
		{
			select = RANDOM_LONG(0, activitySequenceCount - 1);

			for (i = 0; i < pstudiohdr->numseq; i++)
			{
				if (pseqdesc[i].activity == activity)
				{
					if (select == 0)
					{
						return i;
					}

					select--;
				}
			}
		}
	}

	return ACT_INVALID;
}

int LookupActivityHeaviest(void *pmodel, entvars_t *pev, int activity)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		return 0;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);
	int weight = 0;
	int seq = ACT_INVALID;

	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].activity == activity)
		{
			if (pseqdesc[i].actweight > weight)
			{
				weight = pseqdesc[i].actweight;
				seq = i;
			}
		}
	}

	return seq;
}

NOXREF void GetEyePosition(void *pmodel, float *vecEyePosition)
{
	studiohdr_t *pstudiohdr;

	pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		ALERT(at_console, "GetEyePosition() Can't get pstudiohdr ptr!\n");
		return;
	}

	vecEyePosition[0] = pstudiohdr->eyeposition[0];
	vecEyePosition[1] = pstudiohdr->eyeposition[1];
	vecEyePosition[2] = pstudiohdr->eyeposition[2];
}

int LookupSequence(void *pmodel, const char *label)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		return 0;
	}

	// Look up by sequence name.
	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);
	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (!Q_stricmp(pseqdesc[i].label, label))
			return i;
	}

	// Not found
	return ACT_INVALID;
}

int IsSoundEvent(int eventNumber)
{
	if (eventNumber == SCRIPT_EVENT_SOUND || eventNumber == SCRIPT_EVENT_SOUND_VOICE)
	{
		return 1;
	}

	return 0;
}

NOXREF void SequencePrecache(void *pmodel, const char *pSequenceName)
{
	int index = LookupSequence(pmodel, pSequenceName);

	if (index >= 0)
	{
		studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
		if (!pstudiohdr || index >= pstudiohdr->numseq)
		{
			return;
		}

		mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + index;
		mstudioevent_t *pevent = (mstudioevent_t *)((byte *)pstudiohdr + pseqdesc->eventindex);

		for (int i = 0; i < pseqdesc->numevents; i++)
		{
			// Don't send client-side events to the server AI
			if (pevent[i].event >= EVENT_CLIENT)
				continue;

			// UNDONE: Add a callback to check to see if a sound is precached yet and don't allocate a copy
			// of it's name if it is.
			if (IsSoundEvent(pevent[i].event))
			{
				if (!Q_strlen(pevent[i].options))
				{
					ALERT(at_error, "Bad sound event %d in sequence %s :: %s (sound is \"%s\")\n", pevent[i].event, pstudiohdr->name, pSequenceName, pevent[i].options);
				}

				PRECACHE_SOUND((char *)(gpGlobals->pStringBase + ALLOC_STRING(pevent[i].options)));
			}
		}
	}
}

void GetSequenceInfo(void *pmodel, entvars_t *pev, float *pflFrameRate, float *pflGroundSpeed)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		return;
	}

	if (pev->sequence >= pstudiohdr->numseq)
	{
		*pflFrameRate = 0;
		*pflGroundSpeed = 0;
		return;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + int(pev->sequence);
	if (pseqdesc->numframes <= 1)
	{
		*pflFrameRate = 256.0f;
		*pflGroundSpeed = 0.0f;
		return;
	}

	*pflFrameRate = pseqdesc->fps * 256.0f / (pseqdesc->numframes - 1);
	*pflGroundSpeed = Q_sqrt(pseqdesc->linearmovement[0] * pseqdesc->linearmovement[0] + pseqdesc->linearmovement[1] * pseqdesc->linearmovement[1] + pseqdesc->linearmovement[2] * pseqdesc->linearmovement[2]);
	*pflGroundSpeed = *pflGroundSpeed * pseqdesc->fps / (pseqdesc->numframes - 1);
}

int GetSequenceFlags(void *pmodel, entvars_t *pev)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr || pev->sequence >= pstudiohdr->numseq)
	{
		return 0;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + int(pev->sequence);
	return pseqdesc->flags;
}

int GetAnimationEvent(void *pmodel, entvars_t *pev, MonsterEvent_t *pMonsterEvent, float flStart, float flEnd, int index)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr || pev->sequence >= pstudiohdr->numseq || !pMonsterEvent)
	{
		return 0;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + int(pev->sequence);
	mstudioevent_t *pevent = (mstudioevent_t *)((byte *)pstudiohdr + pseqdesc->eventindex);

	if (pseqdesc->numevents == 0 || index > pseqdesc->numevents)
	{
		return 0;
	}

	if (pseqdesc->numframes > 1)
	{
		flStart *= (pseqdesc->numframes - 1) / 256.0;
		flEnd *= (pseqdesc->numframes - 1) / 256.0;
	}
	else
	{
		flStart = 0;
		flEnd = 1.0;
	}

	for (; index < pseqdesc->numevents; index++)
	{
		// Don't send client-side events to the server AI
		if (pevent[index].event >= EVENT_CLIENT)
			continue;

		if ((pevent[index].frame >= flStart && pevent[index].frame < flEnd) ||
			((pseqdesc->flags & STUDIO_LOOPING)
				&& flEnd >= pseqdesc->numframes - 1
				&& pevent[index].frame < flEnd - pseqdesc->numframes + 1))
		{
			pMonsterEvent->event = pevent[index].event;
			pMonsterEvent->options = pevent[index].options;

			return index + 1;
		}
	}

	return 0;
}

float SetController(void *pmodel, entvars_t *pev, int iController, float flValue)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr)
	{
		return flValue;
	}

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
				flValue = flValue - int64(flValue / 360.0) * 360.0;

			else if (flValue < 0.0)
				flValue = flValue + int64((flValue / -360.0) + 1) * 360.0;
		}
		else
		{
			if (flValue > ((pbonecontroller->start + pbonecontroller->end) / 2) + 180)
				flValue -= 360;

			if (flValue < ((pbonecontroller->start + pbonecontroller->end) / 2) - 180)
				flValue += 360;
		}
	}

	int setting = int64(255.0f * (flValue - pbonecontroller->start) / (pbonecontroller->end - pbonecontroller->start));
	setting = Q_clamp(setting, 0, 255);

	pev->controller[iController] = setting;

	return setting * (1.0f / 255.0f) * (pbonecontroller->end - pbonecontroller->start) + pbonecontroller->start;
}

float SetBlending(void *pmodel, entvars_t *pev, int iBlender, float flValue)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr)
	{
		return flValue;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + int(pev->sequence);

	if (pseqdesc->blendtype[iBlender] == 0)
	{
		return flValue;
	}

	if (pseqdesc->blendtype[iBlender] & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pseqdesc->blendend[iBlender] < pseqdesc->blendstart[iBlender])
			flValue = -flValue;

		// does the controller not wrap?
		if (pseqdesc->blendstart[iBlender] + 359.0 >= pseqdesc->blendend[iBlender])
		{
			if (flValue > ((pseqdesc->blendstart[iBlender] + pseqdesc->blendend[iBlender]) / 2.0) + 180)
			{
				flValue = flValue - 360;
			}

			if (flValue < ((pseqdesc->blendstart[iBlender] + pseqdesc->blendend[iBlender]) / 2.0) - 180)
			{
				flValue = flValue + 360;
			}
		}
	}

	int setting = int64(255.0f * (flValue - pseqdesc->blendstart[iBlender]) / (pseqdesc->blendend[iBlender] - pseqdesc->blendstart[iBlender]));
	setting = Q_clamp(setting, 0, 255);

	pev->blending[iBlender] = setting;

	return setting * (1.0 / 255.0) * (pseqdesc->blendend[iBlender] - pseqdesc->blendstart[iBlender]) + pseqdesc->blendstart[iBlender];
}

int FindTransition(void *pmodel, int iEndingAnim, int iGoalAnim, int *piDir)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr)
	{
		return iGoalAnim;
	}

	mstudioseqdesc_t *pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex);

	// bail if we're going to or from a node 0
	if (pseqdesc[iEndingAnim].entrynode == 0 || pseqdesc[iGoalAnim].entrynode == 0)
	{
		return iGoalAnim;
	}

	int iEndNode;

	if (*piDir > 0)
	{
		iEndNode = pseqdesc[iEndingAnim].exitnode;
	}
	else
	{
		iEndNode = pseqdesc[iEndingAnim].entrynode;
	}

	if (iEndNode == pseqdesc[iGoalAnim].entrynode)
	{
		*piDir = 1;
		return iGoalAnim;
	}

	byte *pTransition = ((byte *)pstudiohdr + pstudiohdr->transitionindex);

	int iInternNode = pTransition[(iEndNode - 1)*pstudiohdr->numtransitions + (pseqdesc[iGoalAnim].entrynode - 1)];

	if (iInternNode == 0)
	{
		return iGoalAnim;
	}

	// look for someone going
	for (int i = 0; i < pstudiohdr->numseq; i++)
	{
		if (pseqdesc[i].entrynode == iEndNode && pseqdesc[i].exitnode == iInternNode)
		{
			*piDir = 1;
			return i;
		}
		if (pseqdesc[i].nodeflags)
		{
			if (pseqdesc[i].exitnode == iEndNode && pseqdesc[i].entrynode == iInternNode)
			{
				*piDir = -1;
				return i;
			}
		}
	}

	ALERT(at_console, "error in transition graph");
	return iGoalAnim;
}

void SetBodygroup(void *pmodel, entvars_t *pev, int iGroup, int iValue)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;
	if (!pstudiohdr)
	{
		return;
	}

	if (iGroup > pstudiohdr->numbodyparts)
	{
		return;
	}

	mstudiobodyparts_t *pbodypart = (mstudiobodyparts_t *)((byte *)pstudiohdr + pstudiohdr->bodypartindex) + iGroup;

	if (iValue >= pbodypart->nummodels)
	{
		return;
	}

	int iCurrent = (pev->body / pbodypart->base) % pbodypart->nummodels;
	pev->body += (iValue - iCurrent) * pbodypart->base;
}

int GetBodygroup(void *pmodel, entvars_t *pev, int iGroup)
{
	studiohdr_t *pstudiohdr = (studiohdr_t *)pmodel;

	if (!pstudiohdr || iGroup > pstudiohdr->numbodyparts)
	{
		return 0;
	}

	mstudiobodyparts_t *pbodypart = (mstudiobodyparts_t *)((byte *)pstudiohdr + pstudiohdr->bodypartindex) + iGroup;

	if (pbodypart->nummodels <= 1)
		return 0;

	int iCurrent = (pev->body / pbodypart->base) % pbodypart->nummodels;
	return iCurrent;
}

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

#if defined(REGAMEDLL_FIXES) && defined(HAVE_SSE) // SSE2 version
void AngleQuaternion(vec_t *angles, vec_t *quaternion)
{
	static const ALIGN16_BEG size_t ps_signmask[4] ALIGN16_END = { 0x80000000, 0, 0x80000000, 0 };

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
#else // REGAMEDLL_FIXES
void AngleQuaternion(vec_t *angles, vec_t *quaternion)
{
	real_t sy, cy, sp_, cp;
	real_t angle;
	float sr, cr;

	float ftmp0;
	float ftmp1;
	float ftmp2;

	angle = angles[ROLL] * 0.5;
	sy = Q_sin(angle);
	cy = Q_cos(angle);

	angle = angles[YAW] * 0.5;
	sp_ = Q_sin(angle);
	cp = Q_cos(angle);

	angle = angles[PITCH] * 0.5;
	sr = Q_sin(angle);
	cr = Q_cos(angle);

	ftmp0 = sr * cp;
	ftmp1 = cr * sp_;

	*quaternion = ftmp0 * cy - ftmp1 * sy;
	quaternion[1] = ftmp1 * cy + ftmp0 * sy;

	ftmp2 = cr * cp;
	quaternion[2] = ftmp2 * sy - sp_ * sr * cy;
	quaternion[3] = sp_ * sr * sy + ftmp2 * cy;
}
#endif // REGAMEDLL_FIXES

void QuaternionSlerp(vec_t *p, vec_t *q, float t, vec_t *qt)
{
	int i;
	real_t a = 0;
	real_t b = 0;

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

	float sclp, sclq;
	real_t cosom = (p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3]);

	if ((1.0 + cosom) > 0.000001)
	{
		if ((1.0 - cosom) > 0.000001)
		{
			real_t cosomega = Q_acos(real_t(cosom));

			float omega = cosomega;
			float sinom = Q_sin(cosomega);

			sclp = Q_sin((1.0f - t) * omega) / sinom;
			sclq = Q_sin(real_t(omega * t)) / sinom;
		}
		else
		{
			sclq = t;
			sclp = 1.0f - t;
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

		sclp = Q_sin((1.0f - t) * (0.5f * M_PI));
		sclq = Q_sin(t * (0.5f * M_PI));

		for (i = 0; i < 3; i++)
			qt[i] = sclp * p[i] + sclq * qt[i];
	}
}

void QuaternionMatrix(vec_t *quaternion, float (*matrix)[4])
{
	matrix[0][0] = 1.0 - 2.0 * quaternion[1] * quaternion[1] - 2.0 * quaternion[2] * quaternion[2];
	matrix[1][0] = 2.0 * quaternion[0] * quaternion[1] + 2.0 * quaternion[3] * quaternion[2];
	matrix[2][0] = 2.0 * quaternion[0] * quaternion[2] - 2.0 * quaternion[3] * quaternion[1];

	matrix[0][1] = 2.0 * quaternion[0] * quaternion[1] - 2.0 * quaternion[3] * quaternion[2];
	matrix[1][1] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[2] * quaternion[2];
	matrix[2][1] = 2.0 * quaternion[1] * quaternion[2] + 2.0 * quaternion[3] * quaternion[0];

	matrix[0][2] = 2.0 * quaternion[0] * quaternion[2] + 2.0 * quaternion[3] * quaternion[1];
	matrix[1][2] = 2.0 * quaternion[1] * quaternion[2] - 2.0 * quaternion[3] * quaternion[0];
	matrix[2][2] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[1] * quaternion[1];
}

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

	if (!paSequences)
	{
		paSequences = (cache_user_t *)IEngineStudio.Mem_Calloc(16, sizeof(cache_user_t)); // UNDONE: leak!
		m_pSubModel->submodels = (dmodel_t *)paSequences;
	}

	if (!IEngineStudio.Cache_Check((struct cache_user_s *)&(paSequences[pseqdesc->seqgroup])))
	{
		IEngineStudio.LoadCacheFile(pseqgroup->name, (struct cache_user_s *)&paSequences[pseqdesc->seqgroup]);
	}

	return (mstudioanim_t *)((byte *)paSequences[pseqdesc->seqgroup].data + pseqdesc->animindex);
}

mstudioanim_t *LookupAnimation(model_t *model, mstudioseqdesc_t *pseqdesc, int index)
{
	mstudioanim_t *panim = StudioGetAnim(model, pseqdesc);
	if (index >= 0 && index <= (pseqdesc->numblends - 1))
		panim += index * g_pstudiohdr->numbones;

	return panim;
}

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
				if (Q_abs(pcontroller1[i] - pcontroller2[i]) > 128)
				{
					int a, b;
					a = (pcontroller1[j] + 128) % 256;
					b = (pcontroller2[j] + 128) % 256;
					value = ((a * dadt) + (b * (1 - dadt)) - 128) * (360.0 / 256.0) + pbonecontroller[j].start;
				}
				else
				{
					value = (pcontroller1[i] * dadt + (pcontroller2[i]) * (1.0 - dadt)) * (360.0 / 256.0) + pbonecontroller[j].start;
				}
			}
			else
			{
				value = (pcontroller1[i] * dadt + pcontroller2[i] * (1.0 - dadt)) / 255.0;
				value = Q_clamp(value, 0.0f, 1.0f);
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
		switch (pbonecontroller[j].type & STUDIO_TYPES)
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
			// default
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

void StudioSlerpBones(vec4_t *q1, float pos1[][3], vec4_t *q2, float pos2[][3], float s)
{
	int i;
	vec4_t q3;
	float s1;

	s = Q_clamp(s, 0.0f, 1.0f);
	s1 = 1.0f - s;

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

void StudioCalcRotations(mstudiobone_t *pbones, int *chain, int chainlength, float *adj, float pos[128][3], vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, float s)
{
	int i;
	int j;

	for (i = chainlength - 1; i >= 0; i--)
	{
		j = chain[i];

		StudioCalcBoneQuaterion((int)f, s, &pbones[j], &panim[j], adj, q[j]);
		StudioCalcBonePosition((int)f, s, &pbones[j], &panim[j], adj, pos[j]);
	}
}

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

real_t StudioEstimateFrame(float frame, mstudioseqdesc_t *pseqdesc)
{
	if (pseqdesc->numframes <= 1)
		return 0;

	return real_t(pseqdesc->numframes - 1) * frame / 256;
}

void SV_StudioSetupBones(model_t *pModel, float frame, int sequence, const vec_t *angles, const vec_t *origin, const byte *pcontroller, const byte *pblending, int iBone, const edict_t *pEdict)
{
	int i, j, chainlength = 0;
	int chain[MAXSTUDIOBONES];
	double f;

	float subframe;
	float adj[MAXSTUDIOCONTROLLERS];
	mstudiobone_t *pbones;
	mstudioseqdesc_t *pseqdesc;
	mstudioanim_t *panim;
	float bonematrix[3][4];
	vec3_t temp_angles;

	static float pos[MAXSTUDIOBONES][3] = {}, pos2[MAXSTUDIOBONES][3] = {};
	static float q[MAXSTUDIOBONES][4] = {}, q2[MAXSTUDIOBONES][4] = {};

	g_pstudiohdr = (studiohdr_t *)IEngineStudio.Mod_Extradata(pModel);

	// Bound sequence number
	if (sequence < 0 || sequence >= g_pstudiohdr->numseq)
		sequence = 0;

	pbones = (mstudiobone_t *)((byte *)g_pstudiohdr + g_pstudiohdr->boneindex);
	pseqdesc = (mstudioseqdesc_t *)((byte *)g_pstudiohdr + g_pstudiohdr->seqindex) + sequence;
	panim = StudioGetAnim(pModel, pseqdesc);

	if (iBone < -1 || iBone >= g_pstudiohdr->numbones)
		iBone = 0;

	if (iBone == -1)
	{
		chainlength = g_pstudiohdr->numbones;

		for (i = 0; i < chainlength; i++)
			chain[(chainlength - i) - 1] = i;
	}
	else
	{
		// only the parent bones
		for (i = iBone; i != -1; i = pbones[i].parent)
			chain[chainlength++] = i;
	}

	f = StudioEstimateFrame(frame, pseqdesc);
	subframe = int(f);
	f -= subframe;

	StudioCalcBoneAdj(0, adj, pcontroller, pcontroller, 0);
	StudioCalcRotations(pbones, chain, chainlength, adj, pos, q, pseqdesc, panim, subframe, f);

	if (pseqdesc->numblends != NUM_BLENDING)
	{
		if (pseqdesc->numblends > 1)
		{
			float b = real_t(pblending[0]) / 255.0f;

			panim = StudioGetAnim(pModel, pseqdesc);
			panim += g_pstudiohdr->numbones;

			StudioCalcRotations(pbones, chain, chainlength, adj, pos2, q2, pseqdesc, panim, subframe, f);
			StudioSlerpBones(q, pos, q2, pos2, b);
		}
	}
	// This game knows how to do nine way blending
	else
	{
		static float pos3[MAXSTUDIOBONES][3] = {}, pos4[MAXSTUDIOBONES][3] = {};
		static float q3[MAXSTUDIOBONES][4] = {}, q4[MAXSTUDIOBONES][4] = {};

		real_t s, t;
		s = GetPlayerYaw(pEdict);
		t = GetPlayerPitch(pEdict);

		// Blending is 0-127 == Left to Middle, 128 to 255 == Middle to right
		if (s <= 127.0f)
		{
			// Scale 0-127 blending up to 0-255
			s = (s * 2.0f);

			if (t <= 127.0f)
			{
				t = (t * 2.0f);

				StudioCalcRotations(pbones, chain, chainlength, adj, pos, q, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 1);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos2, q2, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 3);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos3, q3, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 4);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos4, q4, pseqdesc, panim, subframe, f);
			}
			else
			{
				t = 2.0f * (t - 127.0f);

				panim = LookupAnimation(pModel, pseqdesc, 3);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos, q, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 4);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos2, q2, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 6);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos3, q3, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 7);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos4, q4, pseqdesc, panim, subframe, f);
			}
		}
		else
		{
			// Scale 127-255 blending up to 0-255
			s = 2.0f * (s - 127.0f);

			if (t <= 127.0f)
			{
				t = (t * 2.0f);

				panim = LookupAnimation(pModel, pseqdesc, 1);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos, q, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 2);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos2, q2, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 4);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos3, q3, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 5);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos4, q4, pseqdesc, panim, subframe, f);
			}
			else
			{
				t = 2.0f * (t - 127.0f);

				panim = LookupAnimation(pModel, pseqdesc, 4);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos, q, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 5);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos2, q2, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 7);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos3, q3, pseqdesc, panim, subframe, f);

				panim = LookupAnimation(pModel, pseqdesc, 8);
				StudioCalcRotations(pbones, chain, chainlength, adj, pos4, q4, pseqdesc, panim, subframe, f);
			}
		}

		// Normalize interpolant
		s /= 255.0f;
		t /= 255.0f;

		// Spherically interpolate the bones
		StudioSlerpBones(q, pos, q2, pos2, s);
		StudioSlerpBones(q3, pos3, q4, pos4, s);
		StudioSlerpBones(q, pos, q3, pos3, t);
	}

	if (pseqdesc->numblends == 9 && sequence < ANIM_FIRST_DEATH_SEQUENCE && sequence != ANIM_SWIM_1 && sequence != ANIM_SWIM_2)
	{
		bool bCopy = true;
		int gaitsequence = GetPlayerGaitsequence(pEdict);	// calc gait animation

		if (gaitsequence < 0 || gaitsequence >= g_pstudiohdr->numseq)
			gaitsequence = 0;

		pseqdesc = (mstudioseqdesc_t *)((byte *)g_pstudiohdr + g_pstudiohdr->seqindex) + gaitsequence;
		panim = StudioGetAnim(pModel, pseqdesc);
		StudioCalcRotations(pbones, chain, chainlength, adj, pos2, q2, pseqdesc, panim, 0, 0);

		for (i = 0; i < g_pstudiohdr->numbones; i++)
		{
			if (!Q_strcmp(pbones[i].name, "Bip01 Spine"))
			{
				bCopy = false;
			}
			else if (!Q_strcmp(pbones[pbones[i].parent].name, "Bip01 Pelvis"))
			{
				bCopy = true;
			}

			if (bCopy)
			{
				Q_memcpy(pos[i], pos2[i], sizeof(pos[i]));
				Q_memcpy(q[i], q2[i], sizeof(q[i]));
			}
		}
	}

	VectorCopy(angles, temp_angles);

#ifndef REGAMEDLL_FIXES
	if (pEdict)
#else
	if (pEdict && CBaseEntity::Instance(const_cast<edict_t *>(pEdict))->IsPlayer())
#endif
	{
		temp_angles[1] = UTIL_GetPlayerGaitYaw(ENTINDEX(pEdict));

		if (temp_angles[1] < 0)
			temp_angles[1] += 360.0f;
	}

	AngleMatrix(temp_angles, (*g_pRotationMatrix));

	(*g_pRotationMatrix)[0][3] = origin[0];
	(*g_pRotationMatrix)[1][3] = origin[1];
	(*g_pRotationMatrix)[2][3] = origin[2];

	for (i = chainlength - 1; i >= 0; i--)
	{
		j = chain[i];
		QuaternionMatrix(q[j], bonematrix);

		bonematrix[0][3] = pos[j][0];
		bonematrix[1][3] = pos[j][1];
		bonematrix[2][3] = pos[j][2];

		if (pbones[j].parent == -1)
			ConcatTransforms((*g_pRotationMatrix), bonematrix, (*g_pBoneTransform)[j]);
		else
			ConcatTransforms((*g_pBoneTransform)[pbones[j].parent], bonematrix, (*g_pBoneTransform)[j]);
	}
}
