#include "precompiled.h"

skilldata_t gSkillData;

// take the name of a cvar, tack a digit for the skill level
// on, and return the value.of that Cvar
NOXREF float GetSkillCvar(char *pName)
{
	int iCount;
	float flValue;
	char szBuffer[64];

	iCount = Q_sprintf(szBuffer, "%s%d", pName, gSkillData.iSkillLevel);
	flValue = CVAR_GET_FLOAT(szBuffer);

	if (flValue <= 0.0f)
	{
		ALERT(at_console, "\n\n** GetSkillCVar Got a zero for %s **\n\n", szBuffer);
	}

	return flValue;
}
