#include "precompiled.h"

void _print_chat(class CBasePlayer *pPlayer, const char *fmt, ...)
{
	static char Dest[4096];

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(Dest, sizeof(Dest), fmt, ap);
	va_end(ap);

	if (Q_strlen(Dest) < sizeof(Dest) - 2)
		Q_strcat(Dest, "\n");

	else Dest[Q_strlen(Dest) - 1] = '\n';

	UTIL_SayText(Dest, (class CBaseEntity *)pPlayer);
}

void _print_console(struct entvars_s *pev, const char *fmt, ...)
{
	static char Dest[4096];

	va_list ap;
	va_start(ap, fmt);
	vsnprintf(Dest, sizeof(Dest), fmt, ap);
	va_end(ap);

	if (Q_strlen(Dest) < sizeof(Dest) - 2)
		Q_strcat(Dest, "\n");

	else Dest[Q_strlen(Dest) - 1] = '\n';

	ClientPrint(pev, HUD_PRINTCONSOLE, Dest);
}

void _printf2(const char *fmt, ...)
{
	/*
	* check is null, test the demo started before than searches pointer to refs
	*/
	if (&g_engfuncs == NULL || g_engfuncs.pfnServerPrint == NULL)
		return;

	static char Dest[4096];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(Dest, sizeof(Dest), fmt, ap);
	va_end(ap);

	if (Q_strlen(Dest) < sizeof(Dest) - 2)
		Q_strcat(Dest, "\n");

	else Dest[Q_strlen(Dest) - 1] = '\n';

	SERVER_PRINT(Dest);
}
