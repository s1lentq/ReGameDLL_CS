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

#ifndef BOT_PROFILE
#define BOT_PROFILE
#ifdef _WIN32
#pragma once
#endif

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

/* <4a79de> ../game_shared/bot/bot_profile.h:46 */
class BotProfile
{
public:
	BotProfile(void)
	{
		m_name = NULL;
		m_aggression = 0.0f;
		m_skill = 0.0f;
		m_teamwork = 0.0f;
		m_weaponPreferenceCount = 0;
		m_cost = 0;
		m_skin = 0;
		m_difficultyFlags = 0;
		m_voicePitch = 100;
		m_reactionTime = 0.3f;
		m_attackDelay = 0.0f;
		m_teams = BOT_TEAM_ANY;
		m_voiceBank = 0;
		m_prefersSilencer = false;
	}

	const char *GetName(void) const
	{
		return m_name;
	}
	float GetAggression(void) const
	{
		return m_aggression;
	}
	float GetSkill(void) const
	{
		return m_skill;
	}
	float GetTeamwork(void) const
	{
		return m_teamwork;
	}
	int GetWeaponPreference(int i)
	{
		return m_weaponPreference[i];
	}
	NOBODY const char *GetWeaponPreferenceAsString(int i) const;
	int GetWeaponPreferenceCount(void) const
	{
		return m_weaponPreferenceCount;
	}

	NOBODY bool HasPrimaryPreference(void) const;
	NOBODY bool HasPistolPreference(void) const;

	int GetCost(void) const
	{
		return m_cost;
	}
	int GetSkin(void) const
	{
		return m_skin;
	}
	NOBODY bool IsDifficulty(BotDifficultyType diff) const;
	int GetVoicePitch(void) const
	{
		return m_voicePitch;
	}
	float GetReactionTime(void) const
	{
		return m_reactionTime;
	}
	float GetAttackDelay(void) const
	{
		return m_attackDelay;
	}
	int GetVoiceBank(void) const
	{
		return m_voiceBank;
	}
	bool IsValidForTeam(BotProfileTeamType team) const;
	bool PrefersSilencer(void) const
	{
		return m_prefersSilencer;
	}
	// TODO: it func private
	NOBODY void Inherit(const BotProfile *parent, const BotProfile *baseline);

private:

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

}; /* size: 120, cachelines: 2, members: 15 */

/* <4a666f> ../game_shared/bot/bot_profile.h:115 */
inline bool BotProfile::IsDifficulty(BotDifficultyType diff) const
{
	return (m_difficultyFlags & (1 << diff)) ? true : false;
}

/* <4a7a20> ../game_shared/bot/bot_profile.h:123 */
inline void BotProfile::Inherit(const BotProfile *parent, const BotProfile *baseline)
{
	if (parent->m_aggression != baseline->m_aggression)
		m_aggression = parent->m_aggression;

	if (parent->m_skill != baseline->m_skill)
		m_skill = parent->m_skill;

	if (parent->m_teamwork != baseline->m_teamwork)
		m_teamwork = parent->m_teamwork;

	if (parent->m_weaponPreferenceCount != baseline->m_weaponPreferenceCount)
	{
		m_weaponPreferenceCount = parent->m_weaponPreferenceCount;
		for (int i = 0; i<parent->m_weaponPreferenceCount; i++)
			m_weaponPreference[i] = parent->m_weaponPreference[i];
	}

	if (parent->m_cost != baseline->m_cost)
		m_cost = parent->m_cost;

	if (parent->m_skin != baseline->m_skin)
		m_skin = parent->m_skin;

	if (parent->m_difficultyFlags != baseline->m_difficultyFlags)
		m_difficultyFlags = parent->m_difficultyFlags;

	if (parent->m_voicePitch != baseline->m_voicePitch)
		m_voicePitch = parent->m_voicePitch;

	if (parent->m_reactionTime != baseline->m_reactionTime)
		m_reactionTime = parent->m_reactionTime;

	if (parent->m_attackDelay != baseline->m_attackDelay)
		m_attackDelay = parent->m_attackDelay;

	if (parent->m_teams != baseline->m_teams)
		m_teams = parent->m_teams;

	if (parent->m_voiceBank != baseline->m_voiceBank)
		m_voiceBank = parent->m_voiceBank;
}

typedef std::list<BotProfile *> BotProfileList;

/* <36a051> ../game_shared/bot/bot_profile.h:180 */
class BotProfileManager
{
public:
	BotProfileManager(void);
	~BotProfileManager(void);

	void Init(const char *filename, unsigned int *checksum = NULL);
	void Reset(void);

	const BotProfile *GetProfile(const char *name, BotProfileTeamType team) const
	{
		for (BotProfileList::const_iterator iter = m_profileList.begin(); iter != m_profileList.end(); ++iter)
			if (!Q_stricmp(name, (*iter)->GetName()) && (*iter)->IsValidForTeam(team))
				return *iter;

		return NULL;
	}
	const BotProfileList *GetProfileList(void) const
	{
		return &m_profileList;
	}
	const BotProfile *GetRandomProfile(BotDifficultyType difficulty, BotProfileTeamType team) const;

	const char *GetCustomSkin(int index);
	const char *GetCustomSkinModelname(int index);
	const char *GetCustomSkinFname(int index);
	int GetCustomSkinIndex(const char *name, const char *filename = NULL);

	typedef std::vector<char *> VoiceBankList;

	const VoiceBankList *GetVoiceBanks() const
	{
		return &m_voiceBanks;
	}
	int FindVoiceBankIndex(const char *filename);

protected:

#if defined(_WIN32) && defined(HOOK_GAMEDLL)
	int unknown_padding1;
#endif // HOOK_GAMEDLL

	BotProfileList m_profileList;
	VoiceBankList m_voiceBanks;

	char *m_skins[NumCustomSkins];
	char *m_skinModelnames[NumCustomSkins];
	char *m_skinFilenames[NumCustomSkins];
	int m_nextSkin;

};/* size: 1224, cachelines: 20, members: 6 */

#ifdef HOOK_GAMEDLL

#define TheBotProfiles (*pTheBotProfiles)

#endif // HOOK_GAMEDLL

extern BotProfileManager *TheBotProfiles;

#endif // BOT_PROFILE
