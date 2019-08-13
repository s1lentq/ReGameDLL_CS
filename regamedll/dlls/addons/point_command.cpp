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
*/

#include "precompiled.h"

void CPointBaseCommand::KeyValue(KeyValueData *pkvd)
{
	// add this field to the command list
	if (m_vecCommands.Count() < MAX_POINT_CMDS)
	{
		if (pkvd->szValue[0] != '\0' &&
			Q_strcmp(pkvd->szValue, "-") != 0)
		{
			m_vecCommands.AddToTail({ pkvd->szKeyName, pkvd->szValue });
		}
		else
		{
			m_vecCommands.AddToTail(pkvd->szKeyName);
		}

		pkvd->fHandled = TRUE;
		return;
	}

	CPointEntity::KeyValue(pkvd);
}

LINK_ENTITY_TO_CLASS(point_clientcommand, CPointClientCommand, CCSPointClientCommand)

void CPointClientCommand::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	edict_t *pClient = nullptr;
	if (gpGlobals->maxClients == 1)
	{
		pClient = INDEXENT(1);
	}
	else if (pActivator &&
		pActivator->IsPlayer() &&
		pActivator->IsNetClient() &&
		!pActivator->IsDormant())
	{
		// In multiplayer, send it back to the activator
		pClient = pActivator->edict();
	}

	if (pClient)
	{
		for (auto &cmd : m_vecCommands) {
			Execute(pClient, "%s \"%s\"\n", cmd.name, cmd.value);
		}
	}
}

void CPointClientCommand::Execute(edict_t *pEdict, const char *pszFmt, ...)
{
	va_list argptr;
	char command[128];

	va_start(argptr, pszFmt);
	Q_vsnprintf(command, sizeof(command), pszFmt, argptr);
	va_end(argptr);

	CLIENT_COMMAND(pEdict, command);
}

LINK_ENTITY_TO_CLASS(point_servercommand, CPointServerCommand, CCSPointServerCommand)

void CPointServerCommand::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
#ifdef REGAMEDLL_ADD
	if (!allow_point_servercommand.value) {
		ALERT(at_warning, "point_servercommand usage blocked by mp_allow_point_servercommand setting\n");
		return;
	}
#endif

	for (auto &cmd : m_vecCommands)
	{
		cvar_t *pCVar = CVAR_GET_POINTER(cmd.name);
		if (pCVar &&
			pCVar->string &&
			pCVar->string[0] != '\0' &&
			Q_stricmp(cmd.value, pCVar->string) != 0) {
			Q_strlcpy(cmd.valueInitial, pCVar->string);
		}

		if (cmd.value[0] != '\0')
		{
			Execute(nullptr, "%s \"%s\"\n", cmd.name, cmd.value);
		}
		else
		{
			Execute(nullptr, "%s\n", cmd.name);
		}
	}
}

void CPointServerCommand::Execute(edict_t *pEdict, const char *pszFmt, ...)
{
	va_list argptr;
	char command[128];

	va_start(argptr, pszFmt);
	Q_vsnprintf(command, sizeof(command), pszFmt, argptr);
	va_end(argptr);

	if (!IS_DEDICATED_SERVER())
	{
		// potentially dangerous for untrusted maps
		// so try to use it for passing through filtered svc_stufftext
		CLIENT_COMMAND(pEdict ? pEdict : INDEXENT(1), command);
		return;
	}

	SERVER_COMMAND(command);
}

void CPointBaseCommand::OnDestroy()
{
	if (!(pev->spawnflags & SF_POINT_CMD_NORESET))
	{
		bool bAtLeastOneCmdReset = false;
		for (auto &cmd : m_vecCommands)
		{
			if (cmd.valueInitial[0] != '\0')
			{
				Execute(nullptr, "%s \"%s\"\n", cmd.name, cmd.valueInitial);
				bAtLeastOneCmdReset = true;
			}
		}

		if (bAtLeastOneCmdReset)
		{
			SERVER_EXECUTE();
		}
	}

	m_vecCommands.Purge();
}
