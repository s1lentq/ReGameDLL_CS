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

// long STL names get truncated in browse info.
#pragma warning(disable : 4786)

#ifndef _WIN32
#include <strings.h>
#include <stdio.h>
#endif // _WIN32

#undef min
#undef max

#include <list>
#include <vector>

#include "bot_constants.h"

enum
{
	FirstCustomSkin = 100,
	NumCustomSkins = 100,
	LastCustomSkin = FirstCustomSkin + NumCustomSkins - 1,
};

enum BotProfileTeamType
{
	BOT_TEAM_T,
	BOT_TEAM_CT,
	BOT_TEAM_ANY
};

class BotProfile {
public:
	const char *GetName() const { return m_name; }
	float GetAggression() const { return m_aggression; }
	float GetSkill() const { return m_skill; }
	float GetTeamwork() const { return m_teamwork; }
	int GetWeaponPreference(int i) const { return m_weaponPreference[i]; }
	int GetWeaponPreferenceCount() const { return m_weaponPreferenceCount; }
	int GetCost() const { return m_cost; }
	int GetSkin() const { return m_skin; }
	int GetVoicePitch() const { return m_voicePitch; }
	float GetReactionTime() const { return m_reactionTime; }
	float GetAttackDelay() const { return m_attackDelay; }
	int GetVoiceBank() const { return m_voiceBank; }
	bool PrefersSilencer() const { return m_prefersSilencer; }
public:
	friend class BotProfileManager;

	char *m_name;
	float m_aggression;
	float m_skill;
	float m_teamwork;

	enum { MAX_WEAPON_PREFS = 16 };

	int m_weaponPreference[MAX_WEAPON_PREFS];
	int m_weaponPreferenceCount;

	int m_cost;
	int m_skin;

	unsigned char m_difficultyFlags;
	int m_voicePitch;
	float m_reactionTime;
	float m_attackDelay;
	enum BotProfileTeamType m_teams;
	bool m_prefersSilencer;
	int m_voiceBank;
};

typedef std::list<BotProfile *> BotProfileList;

class BotProfileManager {
public:
	typedef std::vector<char *> VoiceBankList;
	const BotProfileList *GetProfileList() const { return &m_profileList; }
	const VoiceBankList *GetVoiceBanks() const { return &m_voiceBanks; }

public:
	BotProfileList m_profileList;
	VoiceBankList m_voiceBanks;

	char *m_skins[NumCustomSkins];
	char *m_skinModelnames[NumCustomSkins];
	char *m_skinFilenames[NumCustomSkins];
	int m_nextSkin;
};
