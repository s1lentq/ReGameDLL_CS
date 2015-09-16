#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBaseAnimating::m_SaveData[] =
{
	DEFINE_FIELD(CBaseMonster, m_flFrameRate, FIELD_FLOAT),
	DEFINE_FIELD(CBaseMonster, m_flGroundSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CBaseMonster, m_flLastEventCheck, FIELD_TIME),
	DEFINE_FIELD(CBaseMonster, m_fSequenceFinished, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseMonster, m_fSequenceLoops, FIELD_BOOLEAN),
};

#else

TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CBaseAnimating, m_SaveData)[5];

#endif // HOOK_GAMEDLL

/* <10583> ../cstrike/dlls/animating.cpp:38 */
IMPLEMENT_SAVERESTORE(CBaseAnimating, CBaseDelay);

/* <105cf> ../cstrike/dlls/animating.cpp:45 */
float CBaseAnimating::StudioFrameAdvance(float flInterval)
{
	if (flInterval == 0.0f)
	{
		flInterval = gpGlobals->time - pev->animtime;

		if (flInterval <= 0.001)
		{
			pev->animtime = gpGlobals->time;
			return 0;
		}
	}

	if (pev->animtime == 0.0f)
		flInterval = 0;

	pev->frame += flInterval * m_flFrameRate * pev->framerate;
	pev->animtime = gpGlobals->time;

	if (pev->frame < 0.0 || pev->frame >= 256.0)
	{
		if (m_fSequenceLoops)
			pev->frame -= (int)(pev->frame / 256.0) * 256.0;
		else
			pev->frame = (pev->frame < 0) ? 0 : 255;

		m_fSequenceFinished = TRUE;
	}

	return flInterval;
}

/* <10605> ../cstrike/dlls/animating.cpp:77 */
int CBaseAnimating::LookupActivity(int activity)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::LookupActivity(pmodel, pev, activity);
}

/* <10653> ../cstrike/dlls/animating.cpp:91 */
int CBaseAnimating::LookupActivityHeaviest(int activity)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::LookupActivityHeaviest(pmodel, pev, activity);
}

/* <107b1> ../cstrike/dlls/animating.cpp:136 */
void CBaseAnimating::DispatchAnimEvents(float flInterval)
{
	MonsterEvent_t event;
	void *pmodel = GET_MODEL_PTR(ENT(pev));

	if (!pmodel)
	{
		ALERT(at_aiconsole, "Gibbed monster is thinking!\n");
		return;
	}

	// FIXME: I have to do this or some events get missed, and this is probably causing the problem below
	flInterval = 0.1f;

	// FIX: this still sometimes hits events twice
	float flStart = pev->frame + (m_flLastEventCheck - pev->animtime) * m_flFrameRate * pev->framerate;
	float flEnd = pev->frame + flInterval * m_flFrameRate * pev->framerate;

	m_fSequenceFinished = FALSE;
	m_flLastEventCheck = pev->animtime + flInterval;

	if (flEnd >= 256.0f || flEnd <= 0.0f)
	{
		m_fSequenceFinished = TRUE;
	}

	int index = 0;
	while ((index = GetAnimationEvent(pmodel, pev, &event, flStart, flEnd, index)) != 0)
	{
		HandleAnimEvent(&event);
	}
}

/* <106a1> ../cstrike/dlls/animating.cpp:100 */
int CBaseAnimating::LookupSequence(const char *label)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::LookupSequence(pmodel, label);
}

/* <10711> ../cstrike/dlls/animating.cpp:110 */
void CBaseAnimating::ResetSequenceInfo(void)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));

	GetSequenceInfo(pmodel, pev, &m_flFrameRate, &m_flGroundSpeed);
	m_fSequenceLoops = ((GetSequenceFlags() & STUDIO_LOOPING) != 0);
	pev->animtime = gpGlobals->time;
	pev->framerate = 1.0f;

	m_fSequenceFinished = FALSE;
	m_flLastEventCheck = gpGlobals->time;
}

/* <1077c> ../cstrike/dlls/animating.cpp:126 */
BOOL CBaseAnimating::GetSequenceFlags(void)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::GetSequenceFlags(pmodel, pev);
}

/* <10837> ../cstrike/dlls/animating.cpp:171 */
float CBaseAnimating::SetBoneController(int iController, float flValue)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));

	return SetController(pmodel, pev, iController, flValue);
}

/* <10893> ../cstrike/dlls/animating.cpp:180 */
void CBaseAnimating::InitBoneControllers(void)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));

	SetController(pmodel, pev, 0, 0);
	SetController(pmodel, pev, 1, 0);
	SetController(pmodel, pev, 2, 0);
	SetController(pmodel, pev, 3, 0);
}

/* <108d3> ../cstrike/dlls/animating.cpp:192 */
NOXREF float CBaseAnimating::SetBlending(int iBlender, float flValue)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::SetBlending(pmodel, pev, iBlender, flValue);
}

/* <1092f> ../cstrike/dlls/animating.cpp:201 */
NOXREF void CBaseAnimating::GetBonePosition(int iBone, Vector &origin, Vector &angles)
{
	GET_BONE_POSITION(ENT(pev), iBone, origin, angles);
}

/* <10984> ../cstrike/dlls/animating.cpp:208 */
NOXREF void CBaseAnimating::GetAttachment(int iAttachment, Vector &origin, Vector &angles)
{
	GET_ATTACHMENT(ENT(pev), iAttachment, origin, angles);
}

/* <109d4> ../cstrike/dlls/animating.cpp:215 */
NOXREF int CBaseAnimating::FindTransition(int iEndingSequence, int iGoalSequence, int *piDir)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));

	if (piDir == NULL)
	{
		int iDir;
		int sequence = ::FindTransition(pmodel, iEndingSequence, iGoalSequence, &iDir);

		if (iDir != 1)
			sequence = -1;

		return sequence;
	}

	return ::FindTransition(pmodel, iEndingSequence, iGoalSequence, piDir);
}

/* <10a5d> ../cstrike/dlls/animating.cpp:234 */
NOXREF void CBaseAnimating::GetAutomovement(Vector &origin, Vector &angles, float flInterval)
{
	;
}

/* <10aad> ../cstrike/dlls/animating.cpp:239 */
NOXREF void CBaseAnimating::SetBodygroup(int iGroup, int iValue)
{
	::SetBodygroup(GET_MODEL_PTR(ENT(pev)), pev, iGroup, iValue);
}

/* <10af0> ../cstrike/dlls/animating.cpp:244 */
NOXREF int CBaseAnimating::GetBodygroup(int iGroup)
{
	return ::GetBodygroup(GET_MODEL_PTR(ENT(pev)), pev, iGroup);
}

/* <10b5f> ../cstrike/dlls/animating.cpp:250 */
int CBaseAnimating::ExtractBbox(int sequence, float *mins, float *maxs)
{
	return ::ExtractBbox(GET_MODEL_PTR(ENT(pev)), sequence, mins, maxs);
}

/* <10b99> ../cstrike/dlls/animating.cpp:258 */
void CBaseAnimating::SetSequenceBox(void)
{
	Vector mins, maxs;

	// Get sequence bbox
	if (ExtractBbox(pev->sequence, mins, maxs))
	{
		// expand box for rotation
		// find min / max for rotations
		float yaw = pev->angles.y * (M_PI / 180.0);

		Vector xvector, yvector;
		xvector.x = cos(yaw);
		xvector.y = sin(yaw);
		yvector.x = -sin(yaw);
		yvector.y = cos(yaw);

		Vector bounds[2];
		bounds[0] = mins;
		bounds[1] = maxs;

		Vector rmin(9999, 9999, 9999);
		Vector rmax(-9999, -9999, -9999);

		Vector base, transformed;
		for (int i = 0; i <= 1; i++)
		{
			base.x = bounds[i].x;
			for (int j = 0; j <= 1; j++)
			{
				base.y = bounds[j].y;
				for (int k = 0; k <= 1; k++)
				{
					base.z = bounds[k].z;

					// transform the point
					transformed.x = xvector.x * base.x + yvector.x * base.y;
					transformed.y = xvector.y * base.x + yvector.y * base.y;
					transformed.z = base.z;

					if (transformed.x < rmin.x)
						rmin.x = transformed.x;

					if (transformed.x > rmax.x)
						rmax.x = transformed.x;

					if (transformed.y < rmin.y)
						rmin.y = transformed.y;

					if (transformed.y > rmax.y)
						rmax.y = transformed.y;

					if (transformed.z < rmin.z)
						rmin.z = transformed.z;

					if (transformed.z > rmax.z)
						rmax.z = transformed.z;
				}
			}
		}

		rmin.z = 0;
		rmax.z = rmin.z + 1;
		UTIL_SetSize(pev, rmin, rmax);
	}
}

#ifdef HOOK_GAMEDLL

int CBaseAnimating::Save(CSave &save)
{
	return Save_(save);
}

int CBaseAnimating::Restore(CRestore &restore)
{
	return Restore_(restore);
}

#endif // HOOK_GAMEDLL
