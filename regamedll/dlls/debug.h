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

#pragma once

enum DebugOutputType
{
	DEBUG_NONE    = 0,
	DEBUG_BOT     = BIT(0),
	DEBUG_CAREER  = BIT(1),
	DEBUG_TUTOR   = BIT(2),
	DEBUG_STATS   = BIT(3),
	DEBUG_HOSTAGE = BIT(4),
	DEBUG_ALL     = 0xFFFFFFFF,
};

struct DebugOutputLevel
{
	const char *name;
	DebugOutputType value;
};

const int MAX_DEBUG_BUFF_SIZE = 1024;

bool IsDeveloper();
void UTIL_DPrintf(DebugOutputType outputType, char *pszMsg, ...);
void UTIL_DPrintf(char *pszMsg, ...);
void PrintDebugFlags();

void SetDebugFlag(const char *flagStr, bool state);
void PrintDebugFlag(const char *flagStr);
void UTIL_SetDprintfFlags(const char *flagStr);

void UTIL_BotDPrintf(char *pszMsg, ...);
void UTIL_CareerDPrintf(char *pszMsg, ...);
void UTIL_TutorDPrintf(char *pszMsg, ...);
void UTIL_StatsDPrintf(char *pszMsg, ...);
void UTIL_HostageDPrintf(char *pszMsg, ...);
