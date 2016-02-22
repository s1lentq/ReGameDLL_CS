#include "precompiled.h"

CPlane::CPlane()
{
	m_fInitialized = FALSE;
}

NOXREF void CPlane::InitializePlane(const Vector &vecNormal, const Vector &vecPoint)
{
	m_vecNormal = vecNormal;
	m_fInitialized = TRUE;
	m_flDist = DotProduct(m_vecNormal, vecPoint);
}

NOXREF BOOL CPlane::PointInFront(const Vector &vecPoint)
{
	if (!m_fInitialized)
	{
		return FALSE;
	}

	float flFace = DotProduct(m_vecNormal, vecPoint) - m_flDist;

	if (flFace >= 0.0f)
	{
		return TRUE;
	}

	return FALSE;
}
