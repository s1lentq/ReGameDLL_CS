#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

const Vector g_vecZero = Vector(0, 0, 0);
u_long g_ulFrameCount = 0;

#else // HOOK_GAMEDLL

const Vector g_vecZero;
u_long g_ulFrameCount;

#endif // HOOK_GAMEDLL

int g_Language;

u_long g_ulModelIndexEyes;
Vector g_vecAttackDir;
int g_iSkillLevel;
int gDisplayTitle;
BOOL g_fGameOver;
