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
	if (m_uiCommandsCount < MAX_POINT_CMDS)
	{
		char command[128];
		if (pkvd->szValue[0] != '\0' &&	Q_strcmp(pkvd->szValue, "-") != 0)
		{
			Q_snprintf(command, sizeof(command), "%s \"%s\"", pkvd->szKeyName, pkvd->szValue);
		}
		else
		{
			Q_strlcpy(command, pkvd->szKeyName);
		}

		m_iszCommands[m_uiCommandsCount++] = ALLOC_STRING(command);
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
		for (size_t cmd = 0; cmd < m_uiCommandsCount; cmd++) {
			CLIENT_COMMAND(pClient, UTIL_VarArgs("%s\n", m_iszCommands[cmd].str()));
		}
	}
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

	for (size_t cmd = 0; cmd < m_uiCommandsCount; cmd++) {
		Execute(m_iszCommands[cmd]);
	}
}

void CPointServerCommand::Execute(const char *command)
{
	if (!IS_DEDICATED_SERVER())
	{
		// potentially dangerous for untrusted maps
		// so try to use it for passing through filtered svc_stufftext
		CLIENT_COMMAND(INDEXENT(1), UTIL_VarArgs("%s\n", command));
		return;
	}

	SERVER_COMMAND(UTIL_VarArgs("%s\n", command));
}
