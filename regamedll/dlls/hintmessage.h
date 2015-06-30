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

#ifndef HINTMESSAGE_H
#define HINTMESSAGE_H
#ifdef _WIN32
#pragma once
#endif

class CHintMessage
{
public:
	CHintMessage(const char *hintString, bool isHint, CUtlVector<const char *> *args, float duration);
	~CHintMessage(void);

public:
	float GetDuration(void) const
	{
		return m_duration;
	}
	void Send(CBaseEntity *client);
private:

	const char *m_hintString;
	bool m_isHint;
	CUtlVector<char *> m_args;
	float m_duration;

};/* size: 32, cachelines: 1, members: 4 */

class CHintMessageQueue
{
public:
	void Reset(void);
	void Update(CBaseEntity *client);
	bool AddMessage(const char *message, float duration, bool isHint, CUtlVector<const char *> *args);
	bool IsEmpty(void)
	{
		return m_messages.Count() == 0;
	}
private:
	float m_tmMessageEnd;
	CUtlVector<CHintMessage *> m_messages;

};/* size: 24, cachelines: 1, members: 2 */

#endif // HINTMESSAGE_H
