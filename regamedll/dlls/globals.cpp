#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

const Vector g_vecZero(0, 0, 0);
NOXREF u_long g_ulFrameCount = 0;

#endif

int g_Language;

NOXREF u_long g_ulModelIndexEyes;
Vector g_vecAttackDir;
int g_iSkillLevel;
int gDisplayTitle;
BOOL g_fGameOver;
bool g_bIsCzeroGame = false;
bool g_bAllowedCSBot = false;
bool g_bHostageImprov = false;
