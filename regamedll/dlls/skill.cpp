#include "precompiled.h"

skilldata_t gSkillData;

/* <16a558> ../cstrike/dlls/skill.cpp:30 */
NOXREF float GetSkillCvar(char *pName)
{
	//int iCount; //unused

	float flValue;
	char szBuffer[64];

	Q_sprintf(szBuffer, "%s%d", pName, gSkillData.iSkillLevel);
	flValue = CVAR_GET_FLOAT(szBuffer);

	if (flValue <= 0.0f)
		ALERT(at_console, "\n\n** GetSkillCVar Got a zero for %s **\n\n",szBuffer);

	return flValue;
}
