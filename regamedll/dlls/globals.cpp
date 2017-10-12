#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

const Vector g_vecZero(0, 0, 0);

#endif

int g_Language;
int g_iSkillLevel;

Vector g_vecAttackDir;
BOOL gDisplayTitle;

bool g_bIsCzeroGame = false;
bool g_bAllowedCSBot = false;
bool g_bHostageImprov = false;
