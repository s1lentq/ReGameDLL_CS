/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include "precompiled.h"

bool Plat_IsInDebugSession()
{
#if defined(OSX)
	int mib[4];
	struct kinfo_proc info;
	size_t size;
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_PID;
	mib[3] = getpid();
	size = sizeof(info);
	info.kp_proc.p_flag = 0;
	sysctl(mib, 4, &info, &size, NULL, 0);
	bool result = ((info.kp_proc.p_flag & P_TRACED) == P_TRACED);
	return result;
#elif defined(_LINUX)
	char s[256];
	snprintf(s, 256, "/proc/%d/cmdline", getppid());
	FILE *fp = fopen(s, "r");
	if (fp)
	{
		fread(s, 256, 1, fp);
		fclose(fp);
		return (0 == strncmp(s, "gdb", 3));
	}
	return false;
#endif
}

void Plat_OutputDebugStringRaw(const char *psz)
{
	fprintf(stderr, "%s", psz);
}

void Plat_OutputDebugString(const char *psz)
{
	fprintf(stderr, "%s", psz);
}

void Plat_DebugString(const char *psz)
{
	fprintf(stderr, "%s", psz);
}

static char g_CmdLine[2048]{};

const char *Plat_GetCommandLine()
{
#if defined(_LINUX)
	static bool commandline_initialized = false;
	if (!commandline_initialized)
	{
		commandline_initialized = true;

		FILE *fp = fopen("/proc/self/cmdline", "rb");
		if (fp)
		{
			size_t nCharRead = 0;

			// -1 to leave room for the '\0'
			nCharRead = fread(g_CmdLine, sizeof(g_CmdLine[0]), ARRAYSIZE(g_CmdLine) - 1, fp);
			if (feof(fp) && !ferror(fp)) // Should have read the whole command line without error
			{
				Assert(nCharRead < ARRAYSIZE(g_CmdLine));

				for (int i = 0; i < nCharRead; i++)
				{
					if (!g_CmdLine[i])
						g_CmdLine[i] = ' ';
				}

				g_CmdLine[nCharRead] = '\0';
			}

			fclose(fp);
		}

		Assert(g_CmdLine[0]);
	}
#endif // LINUX

	return g_CmdLine;
}
