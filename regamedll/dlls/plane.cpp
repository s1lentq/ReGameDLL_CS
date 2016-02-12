#include "precompiled.h"

/* <1262b3> ../cstrike/dlls/plane.cpp:24 */
CPlane::CPlane()
{
	m_fInitialized = FALSE;
}

/* <1262d4> ../cstrike/dlls/plane.cpp:33 */
NOXREF void CPlane::InitializePlane(const Vector &vecNormal, const Vector &vecPoint)
{
	m_vecNormal = vecNormal;
	m_fInitialized = TRUE;
	m_flDist = DotProduct(m_vecNormal, vecPoint);
}

/* <126343> ../cstrike/dlls/plane.cpp:45 */
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
