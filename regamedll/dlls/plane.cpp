#include "precompiled.h"

/* <1262b3> ../cstrike/dlls/plane.cpp:24 */
NOBODY CPlane::CPlane(void)
{
	m_fInitialized = FALSE;
}

/* <1262d4> ../cstrike/dlls/plane.cpp:33 */
NOBODY void CPlane::InitializePlane(const Vector &vecNormal, const Vector &vecPoint)
{
	m_vecNormal = vecNormal;
	m_flDist = DotProduct(m_vecNormal, vecPoint);
	m_fInitialized = TRUE;
}

/* <126343> ../cstrike/dlls/plane.cpp:45 */
NOBODY BOOL CPlane::PointInFront(const Vector &vecPoint)
{
	if (!m_fInitialized)
		return FALSE;

	float flFace = DotProduct(m_vecNormal, vecPoint) - m_flDist;

	if (flFace >= 0.0f)
		return TRUE;

	return FALSE;
}
