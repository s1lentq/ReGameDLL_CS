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

#include "utlvector.h"

#define DHF_ROUND_STARTED     BIT(1)
#define DHF_HOSTAGE_SEEN_FAR  BIT(2)
#define DHF_HOSTAGE_SEEN_NEAR BIT(3)
#define DHF_HOSTAGE_USED      BIT(4)
#define DHF_HOSTAGE_INJURED   BIT(5)
#define DHF_HOSTAGE_KILLED    BIT(6)
#define DHF_FRIEND_SEEN       BIT(7)
#define DHF_ENEMY_SEEN        BIT(8)
#define DHF_FRIEND_INJURED    BIT(9)
#define DHF_FRIEND_KILLED     BIT(10)
#define DHF_ENEMY_KILLED      BIT(11)
#define DHF_BOMB_RETRIEVED    BIT(12)
#define DHF_AMMO_EXHAUSTED    BIT(15)
#define DHF_IN_TARGET_ZONE    BIT(16)
#define DHF_IN_RESCUE_ZONE    BIT(17)
#define DHF_IN_ESCAPE_ZONE    BIT(18)
#define DHF_IN_VIPSAFETY_ZONE BIT(19)
#define DHF_NIGHTVISION       BIT(20)
#define DHF_HOSTAGE_CTMOVE    BIT(21)
#define DHF_SPEC_DUCK         BIT(22)

#define DHM_ROUND_CLEAR       (DHF_ROUND_STARTED | DHF_HOSTAGE_KILLED | DHF_FRIEND_KILLED | DHF_BOMB_RETRIEVED)
#define DHM_CONNECT_CLEAR     (DHF_HOSTAGE_SEEN_FAR | DHF_HOSTAGE_SEEN_NEAR | DHF_HOSTAGE_USED | DHF_HOSTAGE_INJURED | DHF_FRIEND_SEEN | DHF_ENEMY_SEEN | DHF_FRIEND_INJURED | DHF_ENEMY_KILLED | DHF_AMMO_EXHAUSTED | DHF_IN_TARGET_ZONE | DHF_IN_RESCUE_ZONE | DHF_IN_ESCAPE_ZONE | DHF_IN_VIPSAFETY_ZONE | DHF_HOSTAGE_CTMOVE | DHF_SPEC_DUCK)

class CHintMessage
{
public:
	CHintMessage(const char *hintString, bool isHint, CUtlVector<const char *> *args, float duration);
	~CHintMessage();

public:
	float GetDuration() const { return m_duration; }
	void Send(CBaseEntity *client);

private:
	const char *m_hintString;
	bool m_isHint;
	CUtlVector<char *> m_args;
	float m_duration;
};

class CHintMessageQueue
{
public:
	void Reset();
	void Update(CBaseEntity *client);
	bool AddMessage(const char *message, float duration, bool isHint, CUtlVector<const char *> *args);
	bool IsEmpty() const { return m_messages.Count() == 0; }

private:
	float m_tmMessageEnd;
	CUtlVector<CHintMessage *> m_messages;
};
