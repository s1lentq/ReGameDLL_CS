#include "precompiled.h"

void Regamedll_Game_Init()
{
	g_bIsCzeroGame = UTIL_IsGame("czero");
	g_bAllowedCSBot = UTIL_AreBotsAllowed();		// determine whether bots can be used or not
	g_bHostageImprov = UTIL_AreHostagesImprov();		// determine whether hostage improv can be used or not

	WeaponInfoReset();
}
