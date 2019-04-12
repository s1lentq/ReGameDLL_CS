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

#pragma once

const int MAX_POINT_CMDS = 16; // maximum number of commands a single point_[server/client]command entity may be assigned

class CPointBaseCommand: public CPointEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;

protected:
	size_t m_uiCommandsCount;
	string_t m_iszCommands[MAX_POINT_CMDS];
};

// It issues commands to the client console
class CPointClientCommand: public CPointBaseCommand {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

private:
	void Execute(edict_t *pEdict, const char *command);
};

// It issues commands to the server console
class CPointServerCommand: public CPointBaseCommand {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

private:
	void Execute(const char *command);
};
