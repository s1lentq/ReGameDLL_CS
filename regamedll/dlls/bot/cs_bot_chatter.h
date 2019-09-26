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

#define UNDEFINED_COUNT     0xFFFF
#define MAX_PLACES_PER_MAP  64
#define UNDEFINED_SUBJECT   (-1)
#define COUNT_MANY          4		// equal to or greater than this is "many"

class CCSBot;
class BotChatterInterface;

typedef unsigned int PlaceCriteria;
typedef unsigned int CountCriteria;

// A meme is a unit information that bots use to
// transmit information to each other via the radio
class BotMeme
{
public:
	void Transmit(CCSBot *pSender) const; // transmit meme to other bots

	virtual ~BotMeme(){}
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const = 0;		// cause the given bot to act on this meme
};

class BotAllHostagesGoneMeme: public BotMeme
{
public:
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme
};

class BotHostageBeingTakenMeme: public BotMeme
{
public:
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme
};

class BotHelpMeme: public BotMeme
{
public:
	BotHelpMeme(Place place = UNDEFINED_PLACE)
	{
		m_place = place;
	}
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme

private:
	Place m_place;
};

class BotBombsiteStatusMeme: public BotMeme
{
public:
	enum StatusType { CLEAR, PLANTED };

	BotBombsiteStatusMeme(int zoneIndex = 0, StatusType status = CLEAR)
	{
		m_zoneIndex = zoneIndex;
		m_status = status;
	}
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme

private:
	int m_zoneIndex;		// the bombsite
	StatusType m_status;	// whether it is cleared or the bomb is there (planted)
};

class BotBombStatusMeme: public BotMeme
{
public:
	BotBombStatusMeme(CSGameState::BombState state = CSGameState::MOVING, const Vector &pos = nullptr)
	{
		m_state = state;
		m_pos = pos;
	}

public:
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme

private:
	CSGameState::BombState m_state;
	Vector m_pos;
};

class BotFollowMeme: public BotMeme
{
public:
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme
};

class BotDefendHereMeme: public BotMeme
{
public:
	BotDefendHereMeme(const Vector &pos = nullptr)
	{
		m_pos = pos;
	}
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme

private:
	Vector m_pos;
};

class BotWhereBombMeme: public BotMeme
{
public:
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme
};

class BotRequestReportMeme: public BotMeme
{
public:
	virtual void Interpret(CCSBot *pSender, CCSBot *pReceiver) const;			// cause the given bot to act on this meme
};

enum BotStatementType
{
	REPORT_VISIBLE_ENEMIES,
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
	REPORT_ACKNOWLEDGE,			// affirmative or negative
	REPORT_ENEMIES_REMAINING,
	REPORT_FRIENDLY_FIRE,
	REPORT_KILLED_FRIEND,
	//REPORT_ENEMY_LOST

	NUM_BOT_STATEMENT_TYPES,
};

// BotSpeakables are the smallest unit of bot chatter.
// They represent a specific wav file of a phrase, and the criteria for which it is useful
class BotSpeakable
{
public:
	BotSpeakable();
	~BotSpeakable();

	char *m_phrase;
	float m_duration;
	PlaceCriteria m_place;
	CountCriteria m_count;
};

typedef std::vector<BotSpeakable *> BotSpeakableVector;
typedef std::vector<BotSpeakableVector *> BotVoiceBankVector;

// The BotPhrase class is a collection of Speakables associated with a name, ID, and criteria
class BotPhrase
{
public:
	char *GetSpeakable(int bankIndex, float *duration = nullptr) const;		// return a random speakable and its duration in seconds that meets the current criteria

	// NOTE: Criteria must be set just before the GetSpeakable() call, since they are shared among all bots
	void ClearCriteria() const;
	void SetPlaceCriteria(PlaceCriteria place) const;						// all returned phrases must have this place criteria
	void SetCountCriteria(CountCriteria count) const;						// all returned phrases must have this count criteria

	const char *GetName() const { return m_name; }
	Place GetID() const { return m_id; }
	GameEventType GetRadioEquivalent() const { return m_radioEvent; }
	bool IsImportant() const { return m_isImportant; }				// return true if this phrase is part of an important statement

	bool IsPlace() const { return m_isPlace; }
	void Randomize();												// randomly shuffle the speakable order

private:
	friend class BotPhraseManager;
	BotPhrase(unsigned int id, bool isPlace);
	~BotPhrase();

	char *m_name;
	Place m_id;
	bool m_isPlace;								// true if this is a Place phrase
	GameEventType m_radioEvent;
	bool m_isImportant;							// mission-critical statement

	mutable BotVoiceBankVector m_voiceBank;		// array of voice banks (arrays of speakables)
	std::vector<int> m_count;					// number of speakables
	mutable std::vector< int > m_index;			// index of next speakable to return
	int m_numVoiceBanks;						// number of voice banks that have been initialized
	void InitVoiceBank(int bankIndex);			// sets up the vector of voice banks for the first bankIndex voice banks

	mutable PlaceCriteria m_placeCriteria;
	mutable CountCriteria m_countCriteria;
};

typedef std::list<BotPhrase *> BotPhraseList;

inline void BotPhrase::ClearCriteria() const
{
	m_placeCriteria = ANY_PLACE;
	m_countCriteria = UNDEFINED_COUNT;
}

inline void BotPhrase::SetPlaceCriteria(PlaceCriteria place) const
{
	m_placeCriteria = place;
}

inline void BotPhrase::SetCountCriteria(CountCriteria count) const
{
	m_countCriteria = count;
}

// The BotPhraseManager is a singleton that provides an interface to all BotPhrase collections
class BotPhraseManager
{
public:
	BotPhraseManager();
	~BotPhraseManager();

	// initialize phrase system from database file for a specific voice bank (0 is the default voice bank)
	bool Initialize(const char *filename, int bankIndex = 0);

	// invoked when round resets
	void OnRoundRestart();

	// invoked when map changes
	void OnMapChange();
	Place NameToID(const char *name) const;
	const char *IDToName(Place id) const;

	// given a name, return the associated phrase collection
	const BotPhrase *GetPhrase(const char *name) const;

	// given an id, return the associated phrase collection
	const BotPhrase *GetPhrase(unsigned int id) const;

	// given a name, return the associated Place phrase collection
	const BotPhrase *GetPlace(const char *name) const;

	// given an id, return the associated Place phrase collection
	const BotPhrase *GetPlace(PlaceCriteria place) const;

	const BotPhraseList *GetPlaceList() const { return &m_placeList; }

	// return time last statement of given type was emitted by a teammate for the given place
	float GetPlaceStatementInterval(Place place) const;

	// set time of last statement of given type was emitted by a teammate for the given place
	void ResetPlaceStatementInterval(Place place) const;

private:
	int FindPlaceIndex(Place where) const;

	// master list of all phrase collections
	BotPhraseList m_list;

	// master list of all Place phrases
	BotPhraseList m_placeList;

	struct PlaceTimeInfo
	{
		Place placeID;
		IntervalTimer timer;
	};

	mutable PlaceTimeInfo m_placeStatementHistory[MAX_PLACES_PER_MAP];
	mutable int m_placeCount;
};

inline int BotPhraseManager::FindPlaceIndex(Place where) const
{
	for (int i = 0; i < m_placeCount; i++)
	{
		if (m_placeStatementHistory[i].placeID == where)
			return i;
	}

	if (m_placeCount < MAX_PLACES_PER_MAP)
	{
#ifdef REGAMEDLL_FIXES
		m_placeStatementHistory[m_placeCount].placeID = where;
		m_placeStatementHistory[m_placeCount].timer.Invalidate();
		m_placeCount++;
#else
		m_placeStatementHistory[++m_placeCount].placeID = where;
		m_placeStatementHistory[++m_placeCount].timer.Invalidate();
#endif // #ifdef REGAMEDLL_FIXES

		return m_placeCount - 1;
	}

	return -1;
}

inline float BotPhraseManager::GetPlaceStatementInterval(Place place) const
{
	int index = FindPlaceIndex(place);

	if (index < 0)
		return 999999.9f;

	if (index >= m_placeCount)
		return 999999.9f;

	return m_placeStatementHistory[index].timer.GetElapsedTime();
}

inline void BotPhraseManager::ResetPlaceStatementInterval(Place place) const
{
	int index = FindPlaceIndex(place);

	if (index < 0)
		return;

	if (index >= m_placeCount)
		return;

	m_placeStatementHistory[index].timer.Reset();
}

// Statements are meaningful collections of phrases
class BotStatement
{
public:
	BotStatement(BotChatterInterface *chatter, BotStatementType type, float expireDuration);
	~BotStatement();

public:
	BotChatterInterface *GetChatter() const { return m_chatter; }
	CCSBot *GetOwner() const;

	BotStatementType GetType() const { return m_type; }							// return the type of statement this is
	bool IsImportant() const;													// return true if this statement is "important" and not personality chatter

	bool HasSubject() const { return (m_subject != UNDEFINED_SUBJECT); }
	void SetSubject(int playerID) { m_subject = playerID; }						// who this statement is about
	int GetSubject() const { return m_subject; }								// who this statement is about

	bool HasPlace() const { return (GetPlace()) ? true : false; }
	Place GetPlace() const;														// if this statement refers to a specific place, return that place
	void SetPlace(Place where) { m_place = where; }								// explicitly set place

	bool HasCount() const;														// return true if this statement has an associated count

	bool IsRedundant(const BotStatement *say) const;							// return true if this statement is the same as the given one
	bool IsObsolete() const;													// return true if this statement is no longer appropriate to say
	void Convert(const BotStatement *say);										// possibly change what were going to say base on what teammate is saying

	void AppendPhrase(const BotPhrase *phrase);

	void SetStartTime(float timestamp) { m_startTime = timestamp; }			// define the earliest time this statement can be spoken
	float GetStartTime() const { return m_startTime; }

	enum ConditionType
	{
		IS_IN_COMBAT,
		RADIO_SILENCE,
		ENEMIES_REMAINING,
		NUM_CONDITIONS,
	};

	void AddCondition(ConditionType condition);			// conditions must be true for the statement to be spoken
	bool IsValid() const;								// verify all attached conditions

	enum ContextType
	{
		CURRENT_ENEMY_COUNT,
		REMAINING_ENEMY_COUNT,
		SHORT_DELAY,
		LONG_DELAY,
		ACCUMULATE_ENEMIES_DELAY,
	};
	void AppendPhrase(ContextType contextPhrase);				// special phrases that depend on the context

	bool Update();												// emit statement over time, return false if statement is done
	bool IsSpeaking() const { return m_isSpeaking; }			// return true if this statement is currently being spoken
	float GetTimestamp() const { return m_timestamp; }			// get time statement was created (but not necessarily started talking)

	void AttachMeme(BotMeme *meme);								// attach a meme to this statement, to be transmitted to other friendly bots when spoken

public:
	friend class BotChatterInterface;

	BotChatterInterface *m_chatter;		// the chatter system this statement is part of
	BotStatement *m_next, *m_prev;		// linked list hooks
	BotStatementType m_type;			// what kind of statement this is
	int m_subject;						// who this subject is about
	Place m_place;						// explicit place - note some phrases have implicit places as well
	BotMeme *m_meme;					// a statement can only have a single meme for now

	float m_timestamp;					// time when message was created
	float m_startTime;					// the earliest time this statement can be spoken
	float m_expireTime;					// time when this statement is no longer valid
	float m_speakTimestamp;				// time when message began being spoken
	bool m_isSpeaking;					// true if this statement is current being spoken

	float m_nextTime;					// time for next phrase to begin

	enum { MAX_BOT_PHRASES = 4 };
	struct
	{
		bool isPhrase;
		union
		{
			const BotPhrase *phrase;
			ContextType context;
		};

	}
	m_statement[MAX_BOT_PHRASES];

	enum { MAX_BOT_CONDITIONS = 4 };
	ConditionType m_condition[MAX_BOT_CONDITIONS];		// conditions that must be true for the statement to be said
	int m_conditionCount;

	int m_index;						// m_index refers to the phrase currently being spoken, or -1 if we havent started yet
	int m_count;
};

// This class defines the interface to the bot radio chatter system
class BotChatterInterface
{
public:
	BotChatterInterface() {};

	BotChatterInterface(CCSBot *me);
	~BotChatterInterface();

	void Reset();										// reset to initial state
	void Update();										// process ongoing chatter

	void OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther);		// invoked when event occurs in the game (some events have NULL entities)
	void OnDeath();										// invoked when we die

	enum VerbosityType
	{
		NORMAL,		// full chatter
		MINIMAL,	// only scenario-critical events
		RADIO,		// use the standard radio instead
		OFF			// no chatter at all
	};
	VerbosityType GetVerbosity() const;						// return our current level of verbosity

	CCSBot *GetOwner() const { return m_me; }
	bool IsTalking() const;									// return true if we are currently talking
	float GetRadioSilenceDuration();						// return time since any teammate said anything
	void ResetRadioSilenceDuration();

	enum { MUST_ADD = 1 };
	void AddStatement(BotStatement *statement, bool mustAdd = false);		// register a statement for speaking
	void RemoveStatement(BotStatement *statement);							// remove a statement

	BotStatement *GetActiveStatement();						// returns the statement that is being spoken, or is next to be spoken if no-one is speaking now
	BotStatement *GetStatement() const;						// returns our current statement, or NULL if we aren't speaking

	int GetPitch() const { return m_pitch; }

	// things the bots can say
	void Say(const char *phraseName, float lifetime = 3.0f, float delay = 0.0f);

	void AnnouncePlan(const char *phraseName, Place place);
	void Affirmative();
	void Negative();

	void EnemySpotted();												// report enemy sightings
	void KilledMyEnemy(int victimID);
	void EnemiesRemaining();

	void Clear(Place place);

	void ReportIn();												// ask for current situation
	void ReportingIn();												// report current situation

	bool NeedBackup();
	void PinnedDown();
	void Scared();
	void HeardNoise(const Vector *pos);

	void TheyPickedUpTheBomb();
	void GoingToPlantTheBomb(Place place);
	void BombsiteClear(int zoneIndex);
	void FoundPlantedBomb(int zoneIndex);
	void PlantingTheBomb(Place place);
	void SpottedBomber(CBasePlayer *bomber);
	void SpottedLooseBomb(CBaseEntity *bomb);
	void GuardingLooseBomb(CBaseEntity *bomb);
	void RequestBombLocation();

	#define IS_PLAN true
	void GuardingHostages(Place place, bool isPlan = false);
	void GuardingHostageEscapeZone(bool isPlan = false);
	void HostagesBeingTaken();
	void HostagesTaken();
	void TalkingToHostages();
	void EscortingHostages();
	void HostageDown();

	void CelebrateWin();

	void Encourage(const char *phraseName, float repeatInterval = 10.0f, float lifetime = 3.0f);		// "encourage" the player to do the scenario

	void KilledFriend();
	void FriendlyFire();

	bool SeesAtLeastOneEnemy() const { return m_seeAtLeastOneEnemy; }

private:
	BotStatement *m_statementList;		// list of all active/pending messages for this bot
	void ReportEnemies();				// track nearby enemy count and generate enemy activity statements
	bool ShouldSpeak() const;			// return true if we speaking makes sense now

	CCSBot *m_me;						// the bot this chatter is for

	bool m_seeAtLeastOneEnemy;
	float m_timeWhenSawFirstEnemy;
	bool m_reportedEnemies;
	bool m_requestedBombLocation;		// true if we already asked where the bomb has been planted

	int m_pitch;

	static IntervalTimer m_radioSilenceInterval[];	// one timer for each team
	static CountdownTimer m_encourageTimer;			// timer to know when we can "encourage" the human player again - shared by all bots

	IntervalTimer m_needBackupInterval;
	IntervalTimer m_spottedBomberInterval;
	IntervalTimer m_scaredInterval;
	IntervalTimer m_planInterval;
	CountdownTimer m_spottedLooseBombTimer;
	CountdownTimer m_heardNoiseTimer;
	CountdownTimer m_escortingHostageTimer;
};

inline BotChatterInterface::VerbosityType BotChatterInterface::GetVerbosity() const
{
	const char *string = cv_bot_chatter.string;

	if (string == nullptr)
		return NORMAL;

	if (string[0] == 'm' || string[0] == 'M')
		return MINIMAL;

	if (string[0] == 'r' || string[0] == 'R')
		return RADIO;

	if (string[0] == 'o' || string[0] == 'O')
		return OFF;

	return NORMAL;
}

inline bool BotChatterInterface::IsTalking() const
{
	if (m_statementList) {
		return m_statementList->IsSpeaking();
	}

	return false;
}

inline BotStatement *BotChatterInterface::GetStatement() const
{
	return m_statementList;
}

extern BotPhraseManager *TheBotPhrases;

inline void BotChatterInterface::Say(const char *phraseName, float lifetime, float delay)
{
	BotStatement *say = new BotStatement(this, REPORT_MY_INTENTION, lifetime);

	say->AppendPhrase(TheBotPhrases->GetPhrase(phraseName));

	if (delay > 0.0f)
		say->SetStartTime(gpGlobals->time + delay);

	AddStatement(say);
}

const Vector *GetRandomSpotAtPlace(Place place);
