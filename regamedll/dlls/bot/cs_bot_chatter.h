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

#ifndef CS_BOT_CHATTER_H
#define CS_BOT_CHATTER_H
#ifdef _WIN32
#pragma once
#endif

#define UNDEFINED_COUNT		0xFFFF
#define MAX_PLACES_PER_MAP	64
#define UNDEFINED_SUBJECT	(-1)

class CCSBot;
class BotChatterInterface;

typedef unsigned int PlaceCriteria;
typedef unsigned int CountCriteria;


/* <2fe97b> ../cstrike/dlls/bot/cs_bot_chatter.h:42 */
class BotMeme
{
public:
	NOBODY void Transmit(CCSBot *sender) const;
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const = 0;

};/* size: 4, cachelines: 1, members: 1 */

class BotAllHostagesGoneMeme: public BotMeme
{
public:
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;

};/* size: 4, cachelines: 1, members: 1 */

class BotHostageBeingTakenMeme: public BotMeme
{
public:
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;

};/* size: 4, cachelines: 1, members: 1 */

/* <2ff7ef> ../cstrike/dlls/bot/cs_bot_chatter.h:53 */
class BotHelpMeme: public BotMeme
{
public:
	BotHelpMeme(Place place = UNDEFINED_PLACE)
	{
		m_place = place;
	}
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;
private:
	Place m_place;

};/* size: 8, cachelines: 1, members: 2 */

/* <2ff65e> ../cstrike/dlls/bot/cs_bot_chatter.h:70 */
class BotBombsiteStatusMeme: public BotMeme
{
public:
	enum StatusType
	{
		CLEAR = 0,
		PLANTED
	};
	BotBombsiteStatusMeme(int zoneIndex, StatusType status)
	{
		m_zoneIndex = zoneIndex;
		m_status = status;
	}
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;
private:
	int m_zoneIndex;
	StatusType m_status;

};/* size: 12, cachelines: 1, members: 3 */


/* <2ff6de> ../cstrike/dlls/bot/cs_bot_chatter.h:87 */
class BotBombStatusMeme: public BotMeme
{
public:
	BotBombStatusMeme(CSGameState::BombState state, const Vector &pos)
	{
		m_state = state;
		m_pos = pos;
	}
public:
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;
private:
	CSGameState::BombState m_state;
	Vector m_pos;

};/* size: 20, cachelines: 1, members: 3 */

/* <2ff75d> ../cstrike/dlls/bot/cs_bot_chatter.h:101 */
class BotFollowMeme: public BotMeme
{
public:
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;

};/* size: 4, cachelines: 1, members: 1 */

/* <2ff731> ../cstrike/dlls/bot/cs_bot_chatter.h:111 */
class BotDefendHereMeme: public BotMeme
{
public:
	BotDefendHereMeme(const Vector &pos)
	{
		m_pos = pos;
	}
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;
private:
	Vector m_pos;

};/* size: 16, cachelines: 1, members: 2 */

/* <2ff696> ../cstrike/dlls/bot/cs_bot_chatter.h:123 */
class BotWhereBombMeme: public BotMeme
{
public:
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;

};/* size: 4, cachelines: 1, members: 1 */

/* <2ff81b> ../cstrike/dlls/bot/cs_bot_chatter.h:130 */
class BotRequestReportMeme: public BotMeme
{
public:
	NOBODY virtual void Interpret(CCSBot *sender, CCSBot *receiver) const;

};/* size: 4, cachelines: 1, members: 1 */

enum BotStatementType
{
	REPORT_VISIBLE_ENEMIES = 0,
	REPORT_ENEMY_ACTION,
	REPORT_MY_CURRENT_TASK,
	REPORT_MY_INTENTION,
	REPORT_CRITICAL_EVENT,
	REPORT_REQUEST_HELP,
	REPORT_REQUEST_INFORMATION,
	REPORT_ROUND_END,
	REPORT_MY_PLAN,
	REPORT_INFORMATION,
	REPORT_EMOTE,
	REPORT_ACKNOWLEDGE,
	REPORT_ENEMIES_REMAINING,
	REPORT_FRIENDLY_FIRE,
	REPORT_KILLED_FRIEND,
	NUM_BOT_STATEMENT_TYPES,
};

class BotSpeakable
{
public:
	BotSpeakable(void);
	~BotSpeakable(void);

	char *m_phrase;
	float m_duration;
	PlaceCriteria m_place;
	CountCriteria m_count;

};/* size: 16, cachelines: 1, members: 4 */

typedef std::vector<BotSpeakable *> BotSpeakableVector;
typedef std::vector<BotSpeakableVector *> BotVoiceBankVector;

class BotPhrase
{
public:
	NOBODY BotPhrase(unsigned int id, bool isPlace);
	NOBODY ~BotPhrase(void);

	NOBODY void InitVoiceBank(int bankIndex);
	NOBODY char *GetSpeakable(int bankIndex, float *duration = NULL) const;

	void ClearCriteria(void) const;
	void SetPlaceCriteria(PlaceCriteria place) const;
	void SetCountCriteria(CountCriteria count) const;

	const char *GetName(void) const
	{
		return m_name;
	}
	Place GetID(void) const
	{
		return m_id;
	}
	GameEventType GetRadioEquivalent(void) const
	{
		return m_radioEvent;
	}
	bool IsImportant(void) const
	{
		return m_isImportant;
	}
	bool IsPlace(void) const
	{
		return m_isPlace;
	}
	NOBODY void Randomize(void);
private:
	friend class BotPhraseManager;

	char *m_name;
	Place m_id;
	bool m_isPlace;
	GameEventType m_radioEvent;
	bool m_isImportant;

	mutable BotVoiceBankVector m_voiceBank;
	std::vector< int > m_count;
	mutable std::vector< int > m_index;

	int m_numVoiceBanks;
	mutable PlaceCriteria m_placeCriteria;
	mutable CountCriteria m_countCriteria;

};/* size: 68, cachelines: 2, members: 11 */

typedef std::list<BotPhrase *> BotPhraseList;

/* <2fea0e> ../cstrike/dlls/bot/cs_bot_chatter.h:239 */
inline void BotPhrase::ClearCriteria(void) const
{
	m_placeCriteria = ANY_PLACE;
	m_countCriteria = UNDEFINED_COUNT;
}

/* <2fea2a> ../cstrike/dlls/bot/cs_bot_chatter.h:245 */
inline void BotPhrase::SetPlaceCriteria(PlaceCriteria place) const
{
	m_placeCriteria = place;
}

/* <2fea52> ../cstrike/dlls/bot/cs_bot_chatter.h:250 */
inline void BotPhrase::SetCountCriteria( CountCriteria count ) const
{
	m_countCriteria = count;
}

// The BotPhraseManager is a singleton that provides an interface to all BotPhrase collections
class BotPhraseManager
{
public:
	NOBODY BotPhraseManager(void);
	NOBODY ~BotPhraseManager(void);

	// initialize phrase system from database file for a specific voice bank (0 is the default voice bank)
	NOBODY bool Initialize(const char *filename, int bankIndex);

	// invoked when round resets
	NOBODY void OnRoundRestart(void);

	// invoked when map changes
	NOBODY void OnMapChange(void);
	Place NameToID(const char *name) const;
	const char *IDToName(Place id) const;

	// given a name, return the associated phrase collection
	NOBODY const BotPhrase *GetPhrase(const char *name) const;

	// given a name, return the associated Place phrase collection
	NOBODY const BotPhrase *GetPlace(const char *name) const;

	// given an id, return the associated Place phrase collection
	NOBODY const BotPhrase *GetPlace(PlaceCriteria place) const;

	const BotPhraseList *GetPlaceList(void) const
	{
		return &m_placeList;
	}

	// return time last statement of given type was emitted by a teammate for the given place
	float GetPlaceStatementInterval(Place place) const;

	// set time of last statement of given type was emitted by a teammate for the given place
	void ResetPlaceStatementInterval(Place place) const;

#ifndef HOOK_GAMEDLL
private:
#else
public:
#endif // HOOK_GAMEDLL

	int FindPlaceIndex(Place where) const;

#if defined(_WIN32) && defined(HOOK_GAMEDLL)
	// The member m_placeList on Windows must be with offset +4
	// on Linux : +0
	int unknown_padding1;

#endif // HOOK_GAMEDLL

	// master list of all phrase collections
	BotPhraseList m_list;

#if defined(_WIN32) && defined(HOOK_GAMEDLL)
	// The member m_placeList on Windows must be with offset +16
	// on Linux : +8
	int unknown_padding2;

#endif // HOOK_GAMEDLL

	// master list of all Place phrases
	BotPhraseList m_placeList;

	struct PlaceTimeInfo
	{
		Place placeID;
		IntervalTimer timer;
	};
	mutable PlaceTimeInfo m_placeStatementHistory[ MAX_PLACES_PER_MAP ];
	mutable int m_placeCount;

};/* size: 532, cachelines: 9, members: 4 */

/* <2fea95> ../cstrike/dlls/bot/cs_bot_chatter.h:298 */
inline int BotPhraseManager::FindPlaceIndex(Place where) const
{
	for (int i = 0; i < m_placeCount; i++)
	{
		if (m_placeStatementHistory[i].placeID == where)
			return i;
	}
	if (m_placeCount < MAX_PLACES_PER_MAP)
	{
		m_placeStatementHistory[++m_placeCount].placeID = where;
		m_placeStatementHistory[++m_placeCount].timer.Invalidate();
		return m_placeCount-1;
	}
	return -1;
}

/* <2ff83d> ../cstrike/dlls/bot/cs_bot_chatter.h:319 */
inline float BotPhraseManager::GetPlaceStatementInterval(Place place) const
{
	int index = FindPlaceIndex(place);

	if (index < 0)
		return 999999.9f;

	if (index >= m_placeCount)
		return 999999.9f;

	return m_placeStatementHistory[ index ].timer.GetElapsedTime();
}

/* <2ff876> ../cstrike/dlls/bot/cs_bot_chatter.h:335 */
inline void BotPhraseManager::ResetPlaceStatementInterval(Place place) const
{
	int index = FindPlaceIndex(place);
	if (index < 0)
		return;

	if (index >= m_placeCount)
		return;

	m_placeStatementHistory[index].timer.Reset();
}

class BotStatement
{
public:
	NOBODY BotStatement(BotChatterInterface *chatter, BotStatementType type, float expireDuration);
	NOBODY ~BotStatement(void);
public:
	BotChatterInterface *GetChatter(void) const
	{
		return m_chatter;
	}
	NOBODY CCSBot *GetOwner(void) const;
	BotStatementType GetType(void) const
	{
		return m_type;
	}
	NOBODY bool IsImportant(void) const;
	bool HasSubject(void) const
	{
		return (m_subject != UNDEFINED_SUBJECT);
	}
	void SetSubject(int playerID)
	{
		m_subject = playerID;
	}
	int GetSubject(void) const
	{
		return m_subject;
	}
	bool HasPlace(void) const
	{
		return (GetPlace()) ? true : false;
	}
	NOBODY Place GetPlace(void) const;
	void SetPlace(Place where)
	{
		m_place = where;
	}
	NOBODY bool HasCount(void) const;
	NOBODY bool IsRedundant(const BotStatement *say) const;
	NOBODY bool IsObsolete(void) const;
	NOBODY void Convert(const BotStatement *say);
	NOBODY void AppendPhrase(const BotPhrase *phrase);
	void SetStartTime(float timestamp)
	{
		m_startTime = timestamp;
	}
	float GetStartTime(void) const
	{
		return m_startTime;
	}

	enum ConditionType
	{
		IS_IN_COMBAT,
		RADIO_SILENCE,
		ENEMIES_REMAINING,
		NUM_CONDITIONS,
	};

	NOBODY void AddCondition(ConditionType condition);
	NOBODY bool IsValid(void) const;

	enum ContextType
	{
		CURRENT_ENEMY_COUNT,
		REMAINING_ENEMY_COUNT,
		SHORT_DELAY,
		LONG_DELAY,
		ACCUMULATE_ENEMIES_DELAY,
	};
	NOBODY void AppendPhrase(ContextType contextPhrase);

	NOBODY bool Update(void);
	NOBODY bool IsSpeaking(void) const
	{
		return m_isSpeaking;
	}
	NOBODY float GetTimestamp(void) const
	{
		return m_timestamp;
	}
	NOBODY void AttachMeme(BotMeme *meme);
public:
	friend class BotChatterInterface;

	BotChatterInterface *m_chatter;
	BotStatement *m_next;
	BotStatement *m_prev;
	BotStatementType m_type;
	int m_subject;
	Place m_place;
	BotMeme *m_meme;
	float m_timestamp;
	float m_startTime;
	float m_expireTime;
	float m_speakTimestamp;
	bool m_isSpeaking;
	float m_nextTime;

	enum { MAX_BOT_PHRASES = 4 };
	struct
	{
		bool isPhrase;
		union
		{
			const BotPhrase *phrase;
			ContextType context;
		};
	} m_statement[ MAX_BOT_PHRASES ];

	enum { MAX_BOT_CONDITIONS = 4 };

	ConditionType m_condition[ MAX_BOT_CONDITIONS ];
	int m_conditionCount;
	int m_index;
	int m_count;
};/* size: 112, cachelines: 2, members: 18 */

class BotChatterInterface
{
public:
	BotChatterInterface(void) { };

	NOBODY BotChatterInterface(CCSBot *me);
	NOBODY ~BotChatterInterface();

	NOBODY void Reset(void);
	NOBODY void Update(void);

	NOBODY void OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	NOBODY void OnDeath(void);

	enum VerbosityType
	{
		NORMAL,
		MINIMAL,
		RADIO,
		OFF,
	};

	VerbosityType GetVerbosity(void) const;
	NOBODY CCSBot *GetOwner(void) const
	{
		return m_me;
	}
	bool IsTalking(void) const;
	NOBODY float GetRadioSilenceDuration(void);
	NOBODY void ResetRadioSilenceDuration(void);

	enum { MUST_ADD = 1 };

	NOBODY void AddStatement(BotStatement *statement, bool mustAdd = false);
	NOBODY void RemoveStatement(BotStatement *statement);

	NOBODY BotStatement *GetActiveStatement(void);
	BotStatement *GetStatement(void) const;

	int GetPitch(void) const
	{
		return m_pitch;
	}

	void Say(const char *phraseName, float lifetime = 3.0f, float delay = 0.0f);

	NOBODY void AnnouncePlan(const char *phraseName, Place place);
	NOBODY void Affirmative(void);
	NOBODY void Negative(void);

	NOBODY void EnemySpotted(void);
	NOBODY void KilledMyEnemy(int victimID);
	NOBODY void EnemiesRemaining(void);

	NOBODY void Clear(Place place);
	NOBODY void ReportIn(void);
	NOBODY void ReportingIn(void);
	NOBODY bool NeedBackup(void);
	NOBODY void PinnedDown(void);
	NOBODY void Scared(void);
	NOBODY void HeardNoise(const Vector *pos);
	NOBODY void TheyPickedUpTheBomb(void);
	NOBODY void GoingToPlantTheBomb(Place place);
	NOBODY void BombsiteClear(int zoneIndex);
	NOBODY void FoundPlantedBomb(int zoneIndex);
	NOBODY void PlantingTheBomb(Place place);
	NOBODY void SpottedBomber(CBasePlayer *bomber);
	NOBODY void SpottedLooseBomb(CBaseEntity *bomb);
	NOBODY void GuardingLooseBomb(CBaseEntity *bomb);
	NOBODY void RequestBombLocation(void);
	NOBODY void GuardingHostages(Place place, bool isPlan);
	NOBODY void GuardingHostageEscapeZone(bool isPlan);
	NOBODY void HostagesBeingTaken(void);
	NOBODY void HostagesTaken(void);
	NOBODY void TalkingToHostages(void);
	NOBODY void EscortingHostages(void);
	NOBODY void HostageDown(void);
	NOBODY void CelebrateWin(void);

	NOBODY void Encourage(const char *phraseName, float repeatInterval = 10.0f, float lifetime = 3.0f);
	NOBODY void KilledFriend(void);
	NOBODY void FriendlyFire(void);
public:
	static CountdownTimer m_encourageTimer;
	static IntervalTimer m_radioSilenceInterval[2];
private:

	NOBODY void ReportEnemies(void);
	NOBODY bool ShouldSpeak(void) const;

	BotStatement *m_statementList;
	CCSBot *m_me;

	bool m_seeAtLeastOneEnemy;
	float m_timeWhenSawFirstEnemy;
	bool m_reportedEnemies;
	bool m_requestedBombLocation;
	int m_pitch;

	IntervalTimer m_needBackupInterval;
	IntervalTimer m_spottedBomberInterval;
	IntervalTimer m_scaredInterval;
	IntervalTimer m_planInterval;
	CountdownTimer m_spottedLooseBombTimer;
	CountdownTimer m_heardNoiseTimer;
	CountdownTimer m_escortingHostageTimer;
};/* size: 64, cachelines: 1, members: 16 */

/* <2fec2d> ../cstrike/dlls/bot/cs_bot_chatter.h:572 */
inline BotChatterInterface::VerbosityType BotChatterInterface::GetVerbosity(void) const
{
	const char *string = cv_bot_chatter.string;

	if (string == NULL)
		return NORMAL;

	if (string[0] == 'm' || string[0] == 'M')
		return MINIMAL;

	if (string[0] == 'r' || string[0] == 'R')
		return RADIO;

	if (string[0] == 'o' || string[0] == 'O')
		return OFF;

	return NORMAL;
}

/* <2fec4a> ../cstrike/dlls/bot/cs_bot_chatter.h:590 */
inline bool BotChatterInterface::IsTalking(void) const	
{ 
	if (m_statementList)
		return m_statementList->IsSpeaking();
	return false;
}

/* <3f2bad> ../cstrike/dlls/bot/cs_bot_chatter.h:596 */
inline BotStatement *BotChatterInterface::GetStatement(void) const
{
	return m_statementList;
}

#ifdef HOOK_GAMEDLL

#define TheBotPhrases (*pTheBotPhrases)
#define g_pSelectedZombieSpawn (*pg_pSelectedZombieSpawn)

#endif // HOOK_GAMEDLL

extern BotPhraseManager *TheBotPhrases;
extern CBaseEntity *g_pSelectedZombieSpawn;

/* <5c4dcf> ../cstrike/dlls/bot/cs_bot_chatter.h:604 */
inline void BotChatterInterface::Say(const char *phraseName, float lifetime, float delay)
{
	/*BotStatement *say = new BotStatement(this, REPORT_MY_INTENTION, lifetime);

	say->AppendPhrase(TheBotPhrases->GetPhrase(phraseName));

	if (delay > 0.0f)
		say->SetStartTime(gpGlobals->curtime + delay);

	AddStatement(say);*/
}

NOBODY const Vector *GetRandomSpotAtPlace(Place place);

#ifdef HOOK_GAMEDLL

typedef void (BotStatement::*APPEND_PHRASE_CONTEXT)(BotStatement::ContextType);
typedef void (BotStatement::*APPEND_PHRASE_BOTPHRASE)(const BotPhrase *);

typedef const BotPhraseManager *(BotPhraseManager::*GET_PLACE_NAME)(const char *name) const;
typedef const BotPhraseManager *(BotPhraseManager::*GET_PLACE_PLACE)(PlaceCriteria place) const;

#endif // HOOK_GAMEDLL

#endif // CS_BOT_CHATTER_H
