/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef GLOBALS_H
#define GLOBALS_H
#ifdef _WIN32
#pragma once
#endif

#ifdef HOOK_GAMEDLL

#define g_vecZero (*pg_vecZero)
#define g_Language (*pg_Language)

#define g_ulFrameCount (*pg_ulFrameCount)
#define g_ulModelIndexEyes (*pg_ulModelIndexEyes)

#define g_vecAttackDir (*pg_vecAttackDir)
#define g_iSkillLevel (*pg_iSkillLevel)
#define gDisplayTitle (*pgDisplayTitle)
#define g_fGameOver (*pg_fGameOver)

#endif //HOOK_GAMEDLL

extern const Vector g_vecZero;
extern int g_Language;

extern NOXREF u_long g_ulFrameCount;
extern NOXREF u_long g_ulModelIndexEyes;

extern Vector g_vecAttackDir;
extern int g_iSkillLevel;
extern int gDisplayTitle;
extern BOOL g_fGameOver;

#endif // NODES_H
