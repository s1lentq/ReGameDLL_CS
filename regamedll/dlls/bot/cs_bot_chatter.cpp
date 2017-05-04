#include "precompiled.h"
#include <algorithm>

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

BotPhraseManager *TheBotPhrases = NULL;
CBaseEntity *g_pSelectedZombieSpawn = NULL;
CountdownTimer BotChatterInterface::m_encourageTimer;
IntervalTimer BotChatterInterface::m_radioSilenceInterval[ 2 ];

#endif

const Vector *GetRandomSpotAtPlace(Place place)
{
	int count = 0;
	NavAreaList::iterator iter;
	int which;

	for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	{
		CNavArea *area = (*iter);

		if (area->GetPlace() == place)
			++count;
	}

	if (count == 0)
		return NULL;

	which = RANDOM_LONG(0, count - 1);

	for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	{
		CNavArea *area = (*iter);

		if (area->GetPlace() == place && which == 0)
			return area->GetCenter();
	}

	return NULL;
}

// Transmit meme to other bots
void BotMeme::Transmit(CCSBot *sender) const
{
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (!player)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		// skip self
		if (sender == player)
			continue;

		// ignore dead humans
		if (!player->IsBot() && !player->IsAlive())
			continue;

		// ignore enemies, since we can't hear them talk
		if (sender->BotRelationship(player) == CCSBot::BOT_ENEMY)
			continue;

		// if not a bot, fail the test
		if (!player->IsBot())
			continue;

		// allow bot to interpret our meme
		Interpret(sender, (CCSBot *)player);
	}
}

// A teammate called for help - respond
void BotHelpMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	const float maxHelpRange = 3000.0f; // 2000
	receiver->RespondToHelpRequest(sender, m_place, maxHelpRange);
}

// A teammate reported information about a bombsite
void BotBombsiteStatusMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	// remember this bombsite's status
	if (m_status == CLEAR)
		receiver->GetGameState()->ClearBombsite(m_zoneIndex);
	else
		receiver->GetGameState()->MarkBombsiteAsPlanted(m_zoneIndex);

	// if we were heading to the just-cleared bombsite, pick another one to search
	// if our target bombsite wasn't cleared, will will continue going to it,
	// because GetNextBombsiteToSearch() will return the same zone (since its not cleared)
	// if the bomb was planted, we will head to that bombsite
	if (receiver->GetTask() == CCSBot::FIND_TICKING_BOMB)
	{
		receiver->Idle();
		receiver->GetChatter()->Affirmative();
	}
}

// A teammate reported information about the bomb
void BotBombStatusMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	// update our gamestate based on teammate's report
	switch (m_state)
	{
		case CSGameState::MOVING:
		{
			receiver->GetGameState()->UpdateBomber(&m_pos);

			// if we are hunting and see no enemies, respond
			if (!receiver->IsRogue() && receiver->IsHunting() && receiver->GetNearbyEnemyCount() == 0)
				receiver->RespondToHelpRequest(sender, TheNavAreaGrid.GetPlace(&m_pos));

			break;
		}
		case CSGameState::LOOSE:
		{
			receiver->GetGameState()->UpdateLooseBomb(&m_pos);

			if (receiver->GetTask() == CCSBot::GUARD_BOMB_ZONE)
			{
				receiver->Idle();
				receiver->GetChatter()->Affirmative();
			}
			break;
		}
	}
}

// A teammate has asked that we follow him
void BotFollowMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	if (receiver->IsRogue())
		return;

	// if we're busy, ignore
	if (receiver->IsBusy())
		return;

	PathCost pathCost(receiver);
	float travelDistance = NavAreaTravelDistance(receiver->GetLastKnownArea(), TheNavAreaGrid.GetNearestNavArea(&sender->pev->origin), pathCost);
	if (travelDistance < 0.0f)
		return;

	const float tooFar = 1000.0f;
	if (travelDistance > tooFar)
		return;

	// begin following
	receiver->Follow(sender);

	// acknowledge
	receiver->GetChatter()->Say("CoveringFriend");
}

// A teammate has asked us to defend a place
void BotDefendHereMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	if (receiver->IsRogue())
		return;

	// if we're busy, ignore
	if (receiver->IsBusy())
		return;

	Place place = TheNavAreaGrid.GetPlace(&m_pos);
	if (place != UNDEFINED_PLACE)
	{
		// pick a random hiding spot in this place
		const Vector *spot = FindRandomHidingSpot(receiver, place, receiver->IsSniper());
		if (spot != NULL)
		{
			receiver->SetTask(CCSBot::HOLD_POSITION);
			receiver->Hide(spot);
			return;
		}
	}

	// hide nearby
	receiver->SetTask(CCSBot::HOLD_POSITION);
	receiver->Hide(TheNavAreaGrid.GetNearestNavArea(&m_pos));

	// acknowledge
	receiver->GetChatter()->Say("Affirmative");
}

// A teammate has asked where the bomb is planted
void BotWhereBombMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	int zone = receiver->GetGameState()->GetPlantedBombsite();

	if (zone != CSGameState::UNKNOWN)
		receiver->GetChatter()->FoundPlantedBomb(zone);
}

// A teammate has asked us to report in
void BotRequestReportMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	receiver->GetChatter()->ReportingIn();
}

// A teammate told us all the hostages are gone
void BotAllHostagesGoneMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	receiver->GetGameState()->AllHostagesGone();

	// acknowledge
	receiver->GetChatter()->Say("Affirmative");
}

// A teammate told us a CT is talking to a hostage
void BotHostageBeingTakenMeme::__MAKE_VHOOK(Interpret)(CCSBot *sender, CCSBot *receiver) const
{
	receiver->GetGameState()->HostageWasTaken();

	// if we're busy, ignore
	if (receiver->IsBusy())
		return;

	receiver->Idle();

	// acknowledge
	receiver->GetChatter()->Say("Affirmative");
}

BotSpeakable::BotSpeakable()
{
	m_phrase = NULL;
}

BotSpeakable::~BotSpeakable()
{
	if (m_phrase != NULL)
	{
		delete[] m_phrase;
		m_phrase = NULL;
	}
}

BotPhrase::BotPhrase(unsigned int id, bool isPlace)
{
	m_name = NULL;
	m_id = id;
	m_isPlace = isPlace;
	m_radioEvent = EVENT_INVALID;
	m_isImportant = false;

	ClearCriteria();

	m_numVoiceBanks = 0;
	InitVoiceBank(0);
}

BotPhrase::~BotPhrase()
{
	for (size_t bank = 0; bank < m_voiceBank.size(); ++bank)
	{
		for (size_t speakable = 0; speakable < m_voiceBank[bank]->size(); ++speakable)
		{
			delete (*m_voiceBank[bank])[speakable];
		}
		delete m_voiceBank[bank];
	}

	if (m_name != NULL)
	{
		delete[] m_name;
		m_name = NULL;
	}
}

void BotPhrase::InitVoiceBank(int bankIndex)
{
	while (m_numVoiceBanks <= bankIndex)
	{
		m_count.push_back(0);
		m_index.push_back(0);
		m_voiceBank.push_back(new BotSpeakableVector);
		++m_numVoiceBanks;
	}
}

// Return a random speakable - avoid repeating
char *BotPhrase::GetSpeakable(int bankIndex, float *duration) const
{
	if (bankIndex < 0 || bankIndex >= m_numVoiceBanks || m_count[bankIndex] == 0)
	{
		if (duration != NULL)
			*duration = 0.0f;

		return NULL;
	}

	// find phrase that meets the current criteria
	int start = m_index[ bankIndex ];
	while (true)
	{
		BotSpeakableVector *speakables = m_voiceBank[ bankIndex ];
		int &index = m_index[ bankIndex ];

		const BotSpeakable *speak = (*speakables)[index++];

		if (m_index[ bankIndex ] >= m_count[ bankIndex ])
			m_index[ bankIndex ] = 0;

		// check place criteria
		// if this speakable has a place criteria, it must match to be used
		// speakables with Place of ANY will match any place
		// speakables with a specific Place will only be used if Place matches
		// speakables with Place of UNDEFINED only match Place of UNDEFINED
		if (speak->m_place == ANY_PLACE || speak->m_place == m_placeCriteria)
		{
			// check count criteria
			// if this speakable has a count criteria, it must match to be used
			// if this speakable does not have a count criteria, we dont care what the count is set to
			if (speak->m_count == UNDEFINED_COUNT || speak->m_count == Q_min(m_countCriteria, (CountCriteria)COUNT_MANY))
			{
				if (duration)
					*duration = speak->m_duration;

				return speak->m_phrase;
			}
		}

		// check if we exhausted all speakables
		if (m_index[bankIndex] == start)
		{
			if (duration != NULL)
				*duration = 0.0f;

			return NULL;
		}
	}

	return NULL;
}

// Randomly shuffle the speakable order
#ifndef HOOK_GAMEDLL
void BotPhrase::Randomize()
{
	for (size_t i = 0; i < m_voiceBank.size(); ++i)
	{
		std::random_shuffle(m_voiceBank[i]->begin(), m_voiceBank[i]->end());
	}
}
#endif

BotPhraseManager::BotPhraseManager()
{
	for (int i = 0; i < MAX_PLACES_PER_MAP; ++i)
		m_placeStatementHistory[i].timer.Invalidate();

	m_placeCount = 0;
}

// Invoked when map changes
void BotPhraseManager::OnMapChange()
{
	m_placeCount = 0;
}

// Invoked when the round resets
void BotPhraseManager::OnRoundRestart()
{
	// effectively reset all interval timers
	m_placeCount = 0;
	BotPhraseList::const_iterator iter;

	// shuffle all the speakables
	for (iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		(*iter)->Randomize();
	}

	for (iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		(*iter)->Randomize();
	}
}

// Initialize phrase system from database file
bool BotPhraseManager::Initialize(const char *filename, int bankIndex)
{
	bool isDefault = (bankIndex == 0);
	int phraseDataLength;
	char *phraseDataFile = (char *)LOAD_FILE_FOR_ME((char *)filename, &phraseDataLength);

	if (phraseDataFile == NULL)
	{
		if (g_bIsCzeroGame)
		{
			CONSOLE_ECHO("WARNING: Cannot access bot phrase database '%s'\n", filename);
		}

		return false;
	}

	char *phraseData = phraseDataFile;
	unsigned int nextID = 1;

	// wav filenames need to be shorter than this to go over the net anyway.
	const int RadioPathLen = 128;
	char baseDir[RadioPathLen] = "";
	char compositeFilename[RadioPathLen];

#ifdef REGAMEDLL_ADD
	char soundDir[MAX_PATH];
	char filePath[MAX_PATH];

	GET_GAME_DIR(soundDir);
	Q_strcat(soundDir, "\\sound\\");
#endif

	// Parse the BotChatter.db into BotPhrase collections
	while (true)
	{
		phraseData = MP_COM_Parse(phraseData);
		if (!phraseData)
			break;

		char *token = MP_COM_GetToken();

		if (!Q_stricmp(token, "BaseDir"))
		{
			// get name of this output device
			phraseData = MP_COM_Parse(phraseData);
			if (!phraseData)
			{
				CONSOLE_ECHO("Error parsing '%s' - expected identifier\n", filename);
				FREE_FILE(phraseDataFile);
				return false;
			}

			char *token = MP_COM_GetToken();
			Q_strncpy(baseDir, token, RadioPathLen);
			baseDir[RadioPathLen - 1] = '\0';
		}
		else if (!Q_stricmp(token, "Place") || !Q_stricmp(token, "Chatter"))
		{
			bool isPlace = (Q_stricmp(token, "Place") == 0);

			// encountered a new phrase collection
			BotPhrase *phrase = NULL;
			if (isDefault)
			{
				phrase = new BotPhrase(nextID++, isPlace);
			}

			// get name of this phrase
			phraseData = MP_COM_Parse(phraseData);
			if (!phraseData)
			{
				CONSOLE_ECHO("Error parsing '%s' - expected identifier\n", filename);
				FREE_FILE(phraseDataFile);
				return false;
			}

			if (isDefault)
			{
				phrase->m_name = CloneString(MP_COM_GetToken());
			}
			// look up the existing phrase
			else
			{
				if (isPlace)
				{
					phrase = const_cast<BotPhrase *>(GetPlace(MP_COM_GetToken()));
				}
				else
				{
					phrase = const_cast<BotPhrase *>(GetPhrase(MP_COM_GetToken()));
				}

				if (!phrase)
				{
					CONSOLE_ECHO("Error parsing '%s' - phrase '%s' is invalid\n", filename, MP_COM_GetToken());
					FREE_FILE(phraseDataFile);
					return false;
				}
			}

			phrase->InitVoiceBank(bankIndex);

			PlaceCriteria placeCriteria = ANY_PLACE;
			CountCriteria countCriteria = UNDEFINED_COUNT;
			GameEventType radioEvent = EVENT_INVALID;
			bool isImportant = false;

			// read attributes of this phrase
			while (true)
			{
				// get next token
				phraseData = MP_COM_Parse(phraseData);
				if (!phraseData)
				{
					CONSOLE_ECHO("Error parsing %s - expected 'End'\n", filename);
					FREE_FILE(phraseDataFile);
					return false;
				}

				token = MP_COM_GetToken();

				// check for Place criteria
				if (!Q_stricmp(token, "Place"))
				{
					phraseData = MP_COM_Parse(phraseData);
					if (!phraseData)
					{
						CONSOLE_ECHO("Error parsing %s - expected Place name\n", filename);
						FREE_FILE(phraseDataFile);
						return false;
					}

					token = MP_COM_GetToken();

					// update place criteria for subsequent speak lines
					// NOTE: this assumes places must be first in the chatter database

					// check for special identifiers
					if (!Q_stricmp("ANY", token))
						placeCriteria = ANY_PLACE;
					else if (!Q_stricmp("UNDEFINED", token))
						placeCriteria = UNDEFINED_PLACE;
					else
						placeCriteria = TheBotPhrases->NameToID(token);

					continue;
				}

				// check for Count criteria
				if (!Q_stricmp(token, "Count"))
				{
					phraseData = MP_COM_Parse(phraseData);
					if (!phraseData)
					{
						CONSOLE_ECHO("Error parsing %s - expected Count value\n", filename);
						FREE_FILE(phraseDataFile);
						return false;
					}

					token = MP_COM_GetToken();

					// update count criteria for subsequent speak lines
					if (!Q_stricmp(token, "Many"))
						countCriteria = COUNT_MANY;
					else
						countCriteria = Q_atoi(token);

					continue;
				}

				// check for radio equivalent
				if (!Q_stricmp(token, "Radio"))
				{
					phraseData = MP_COM_Parse(phraseData);
					if (!phraseData)
					{
						CONSOLE_ECHO("Error parsing %s - expected radio event\n", filename);
						FREE_FILE(phraseDataFile);
						return false;
					}

					token = MP_COM_GetToken();
					GameEventType event = NameToGameEvent(token);
					if (event <= EVENT_START_RADIO_1 || event >= EVENT_END_RADIO)
					{
						CONSOLE_ECHO("Error parsing %s - invalid radio event '%s'\n", filename, token);
						FREE_FILE(phraseDataFile);
						return false;
					}

					radioEvent = event;
					continue;
				}

				// check for "important" flag
				if (!Q_stricmp(token, "Important"))
				{
					isImportant = true;
					continue;
				}

				// check for End delimiter
				if (!Q_stricmp(token, "End"))
					break;

#ifdef REGAMEDLL_ADD
				Q_snprintf(filePath, sizeof(filePath), "%s%s%s", soundDir, baseDir, token);

				if (Q_access(filePath, 0) != 0)
					continue;
#endif

				// found a phrase - add it to the collection
				BotSpeakable *speak = new BotSpeakable;
				if (baseDir[0])
				{
					Q_snprintf(compositeFilename, RadioPathLen, "%s%s", baseDir, token);
					speak->m_phrase = CloneString(compositeFilename);
				}
				else
				{
					speak->m_phrase = CloneString(token);
				}

				speak->m_place = placeCriteria;
				speak->m_count = countCriteria;

				Q_snprintf(compositeFilename, RadioPathLen, "sound\\%s", speak->m_phrase);
				speak->m_duration = (double)GET_APPROX_WAVE_PLAY_LEN(compositeFilename) / 1000.0f;

				if (speak->m_duration <= 0.0f)
				{
					CONSOLE_ECHO("Warning: Couldn't get duration of phrase '%s'\n", compositeFilename);
					speak->m_duration = 1.0f;
				}

				BotSpeakableVector *speakables = phrase->m_voiceBank[ bankIndex ];
				speakables->push_back(speak);

				++phrase->m_count[ bankIndex ];
			}

			if (isDefault)
			{
				phrase->m_radioEvent = radioEvent;
				phrase->m_isImportant = isImportant;
			}

			// add phrase collection to the appropriate master list
			if (isPlace)
				m_placeList.push_back(phrase);
			else
				m_list.push_back(phrase);
		}
	}

	FREE_FILE(phraseDataFile);
	return true;
}

BotPhraseManager::~BotPhraseManager()
{
	BotPhraseList::iterator iter;
	for (iter = m_list.begin(); iter != m_list.end(); ++iter)
		delete (*iter);

	for (iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
		delete (*iter);

	m_list.clear();
	m_placeList.clear();
}

Place BotPhraseManager::NameToID(const char *name) const
{
	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (!Q_stricmp(phrase->m_name, name))
			return phrase->m_id;
	}

	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (!Q_stricmp(phrase->m_name, name))
			return phrase->m_id;
	}

	return 0;
}

const char *BotPhraseManager::IDToName(Place id) const
{
	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (phrase->m_id == id)
			return phrase->m_name;
	}

	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (phrase->m_id == id)
			return phrase->m_name;
	}

	return NULL;
}

// Given a name, return the associated phrase collection
const BotPhrase *BotPhraseManager::GetPhrase(const char *name) const
{
	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (!Q_stricmp(phrase->m_name, name))
			return phrase;
	}

	//CONSOLE_ECHO("GetPhrase: ERROR - Invalid phrase '%s'\n", name);
	return NULL;
}

/*
// Given an id, return the associated phrase collection
// TODO: Store phrases in a vector to make this fast
const BotPhrase *BotPhraseManager::GetPhrase(unsigned int id) const
{
	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (phrase->m_id == id)
			return phrase;
	}

	CONSOLE_ECHO("GetPhrase: ERROR - Invalid phrase id #%d\n", id);
	return NULL;
}
*/

// Given a name, return the associated Place phrase collection
const BotPhrase *BotPhraseManager::GetPlace(const char *name) const
{
	if (name == NULL)
		return NULL;

	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (!Q_stricmp(phrase->m_name, name))
			return phrase;
	}

	return NULL;
}

// Given a place, return the associated Place phrase collection
const BotPhrase *BotPhraseManager::GetPlace(PlaceCriteria place) const
{
	if (place == UNDEFINED_PLACE)
		return NULL;

	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = (*iter);

		if (phrase->m_id == place)
			return phrase;
	}

	return NULL;
}

BotStatement::BotStatement(BotChatterInterface *chatter, BotStatementType type, float expireDuration)
{
	m_chatter = chatter;

	m_prev = m_next = NULL;
	m_timestamp = gpGlobals->time;
	m_speakTimestamp = 0.0f;

	m_type = type;
	m_subject = UNDEFINED_SUBJECT;
	m_place = UNDEFINED_PLACE;
	m_meme = NULL;

	m_startTime = gpGlobals->time;
	m_expireTime = gpGlobals->time + expireDuration;
	m_isSpeaking = false;

	m_nextTime = 0.0f;
	m_index = -1;
	m_count = 0;

	m_conditionCount = 0;
}

BotStatement::~BotStatement()
{
	if (m_meme != NULL)
	{
		delete m_meme;
		m_meme = NULL;
	}
}

CCSBot *BotStatement::GetOwner() const
{
	return m_chatter->GetOwner();
}

// Attach a meme to this statement, to be transmitted to other friendly bots when spoken
void BotStatement::AttachMeme(BotMeme *meme)
{
	m_meme = meme;
}

// Add a conditions that must be true for the statement to be spoken
void BotStatement::AddCondition(ConditionType condition)
{
	if (m_conditionCount < MAX_BOT_CONDITIONS)
		m_condition[ m_conditionCount++ ] = condition;
}

// Return true if this statement is "important" and not personality chatter
bool BotStatement::IsImportant() const
{
	// if a statement contains any important phrases, it is important
	for (int i = 0; i < m_count; ++i)
	{
		if (m_statement[i].isPhrase && m_statement[i].phrase->IsImportant())
			return true;

		// hack for now - phrases with enemy counts are important
		if (!m_statement[i].isPhrase && m_statement[i].context == BotStatement::CURRENT_ENEMY_COUNT)
			return true;
	}

	return false;
}

// Verify all attached conditions
bool BotStatement::IsValid() const
{
	for (int i = 0; i < m_conditionCount; ++i)
	{
		switch (m_condition[i])
		{
			case IS_IN_COMBAT:
			{
				if (!GetOwner()->IsAttacking())
					return false;
				break;
			}
			/*case RADIO_SILENCE:
			{
				if (GetOwner()->GetChatter()->GetRadioSilenceDuration() < 10.0f)
					return false;
				break;
			}*/
			case ENEMIES_REMAINING:
			{
				if (GetOwner()->GetEnemiesRemaining() == 0)
					return false;
				break;
			}
		}
	}

	return true;
}

// Return true if this statement is essentially the same as the given one
bool BotStatement::IsRedundant(const BotStatement *say) const
{
	// special cases
	if (GetType() == REPORT_MY_PLAN ||
			GetType() == REPORT_REQUEST_HELP ||
			GetType() == REPORT_CRITICAL_EVENT ||
			GetType() == REPORT_ACKNOWLEDGE)
		return false;

	// check if topics are different
	if (say->GetType() != GetType())
		return false;

	if (!say->HasPlace() && !HasPlace() && !say->HasSubject() && !HasSubject())
	{
		// neither has place or subject, so they are the same
		return true;
	}

	// check if subject matter is the same
	if (say->HasPlace() && HasPlace() && say->GetPlace() == GetPlace())
	{
		// talking about the same place
		return true;
	}

	if (say->HasSubject() && HasSubject() && say->GetSubject() == GetSubject())
	{
		// talking about the same player
		return true;
	}

	return false;
}

// Return true if this statement is no longer appropriate to say
bool BotStatement::IsObsolete() const
{
	// if the round is over, the only things we should say are emotes
	if (GetOwner()->GetGameState()->IsRoundOver())
	{
		if (m_type != REPORT_EMOTE)
			return true;
	}

#if 0
	// If we're wanting to say "I lost him" but we've spotted another enemy,
	// we no longer need to report losing someone.
	if (GetOwner()->GetChatter()->SeesAtLeastOneEnemy() && m_type == REPORT_ENEMY_LOST)
	{
		return true;
	}
#endif

	// check if statement lifetime has expired
	return (gpGlobals->time > m_expireTime);
}

// Possibly change what were going to say base on what teammate is saying
void BotStatement::Convert(const BotStatement *say)
{
	if (GetType() == REPORT_MY_PLAN && say->GetType() == REPORT_MY_PLAN)
	{
		static const BotPhrase *meToo = TheBotPhrases->GetPhrase("AgreeWithPlan");

		// don't reconvert
		if (m_statement[0].phrase == meToo)
			return;

		// if our plans are the same, change our statement to "me too"
		if (m_statement[0].phrase == say->m_statement[0].phrase)
		{
			if (m_place == say->m_place)
			{
				// same plan at the same place - convert to "me too"
				m_statement[0].phrase = meToo;
				m_startTime = gpGlobals->time + RANDOM_FLOAT(0.5f, 1.0f);
			}
			else
			{
				// same plan at different place - wait a bit to allow others to respond "me too"
				m_startTime = gpGlobals->time + RANDOM_FLOAT(3.0f, 4.0f);
			}
		}
	}
}

void BotStatement::AppendPhrase(const BotPhrase *phrase)
{
	if (phrase == NULL)
		return;

	if (m_count < MAX_BOT_PHRASES)
	{
		m_statement[ m_count ].isPhrase = true;
		m_statement[ m_count++ ].phrase = phrase;
	}
}

// Special phrases that depend on the context
void BotStatement::AppendPhrase(ContextType contextPhrase)
{
	if (m_count < MAX_BOT_PHRASES)
	{
		m_statement[ m_count ].isPhrase = false;
		m_statement[ m_count++ ].context = contextPhrase;
	}
}

// Say our statement
// m_index refers to the phrase currently being spoken, or -1 if we havent started yet
bool BotStatement::Update()
{
	CCSBot *me = GetOwner();

	// if all of our teammates are dead, the only non-redundant statements are emotes
	if (me->GetFriendsRemaining() == 0 && GetType() != REPORT_EMOTE)
		return false;

	if (!m_isSpeaking)
	{
		m_isSpeaking = true;
		m_speakTimestamp = gpGlobals->time;
	}

	// special case - context dependent delay
	if (m_index >= 0 && m_statement[ m_index ].context == ACCUMULATE_ENEMIES_DELAY)
	{
		// report if we see a lot of enemies, or if enough time has passed
		const float reportTime = 2.0f;
		if (me->GetNearbyEnemyCount() > 3 || gpGlobals->time - m_speakTimestamp > reportTime)
		{
			// enough enemies have accumulated to expire this delay
			m_nextTime = 0.0f;
		}
	}

	if (gpGlobals->time > m_nextTime)
	{
		// check for end of statement
		if (++m_index == m_count)
		{
			// transmit any memes carried in this statement to our teammates
			if (m_meme != NULL)
			{
				m_meme->Transmit(me);
			}

			return false;
		}

		// start next part of statement
		float duration = 0.0f;
		const BotPhrase *phrase = NULL;

		if (m_statement[ m_index ].isPhrase)
		{
			// normal phrase
			phrase = m_statement[ m_index ].phrase;
		}
		else
		{
			// context-dependant phrase
			switch (m_statement[ m_index ].context)
			{
				case CURRENT_ENEMY_COUNT:
				{
					int enemyCount = me->GetNearbyEnemyCount();

					// if we are outnumbered, ask for help
					if (enemyCount - 1 > me->GetNearbyFriendCount())
					{
						phrase = TheBotPhrases->GetPhrase("Help");
						AttachMeme(new BotHelpMeme());
					}
					else if (enemyCount > 1)
					{
						phrase = TheBotPhrases->GetPhrase("EnemySpotted");
						phrase->SetCountCriteria(enemyCount);
					}
					break;
				}
				case REMAINING_ENEMY_COUNT:
				{
					static const char *speak[] =
					{
						"NoEnemiesLeft", "OneEnemyLeft", "TwoEnemiesLeft", "ThreeEnemiesLeft"
					};

					int enemyCount = me->GetEnemiesRemaining();

					// dont report if there are lots of enemies left
					if (enemyCount < 0 || enemyCount > 3)
					{
						phrase = NULL;
					}
					else
					{
						phrase = TheBotPhrases->GetPhrase(speak[ enemyCount ]);
					}
					break;
				}
				case SHORT_DELAY:
				{
					m_nextTime = gpGlobals->time + RANDOM_FLOAT(0.1f, 0.5f);
					return true;
				}
				case LONG_DELAY:
				{
					m_nextTime = gpGlobals->time + RANDOM_FLOAT(1.0f, 2.0f);
					return true;
				}
				case ACCUMULATE_ENEMIES_DELAY:
				{
					// wait until test becomes true
					m_nextTime = 99999999.9f;
					return true;
				}
			}
		}

		if (phrase != NULL)
		{
			// if chatter system is in "standard radio" mode, send the equivalent radio command
			if (me->GetChatter()->GetVerbosity() == BotChatterInterface::RADIO)
			{
				GameEventType radioEvent = phrase->GetRadioEquivalent();
				if (radioEvent == EVENT_INVALID)
				{
					// skip directly to the next phrase
					m_nextTime = 0.0f;
				}
				else
				{
					// use the standard radio
					me->GetChatter()->ResetRadioSilenceDuration();
					me->SendRadioMessage(radioEvent);
					duration = 2.0f;
				}
			}
			else
			{
				// set place criteria
				phrase->SetPlaceCriteria(m_place);

				const char *filename = phrase->GetSpeakable(me->GetProfile()->GetVoiceBank(), &duration);
				// CONSOLE_ECHO("%s: Radio('%s')\n", STRING(me->pev->netname), filename);

				bool sayIt = true;
				if (phrase->IsPlace())
				{
					// don't repeat the place if someone just mentioned it not too long ago
					float timeSince = TheBotPhrases->GetPlaceStatementInterval(phrase->GetID());
					const float minRepeatTime = 20.0f;

					if (timeSince < minRepeatTime)
					{
						sayIt = false;
					}
					else
					{
						TheBotPhrases->ResetPlaceStatementInterval(phrase->GetID());
					}
				}

				if (sayIt)
				{
					if (filename == NULL)
					{
						GameEventType radioEvent = phrase->GetRadioEquivalent();
						if (radioEvent == EVENT_INVALID)
						{
							// skip directly to the next phrase
							m_nextTime = 0.0f;
						}
						else
						{
							me->SendRadioMessage(radioEvent);
							me->GetChatter()->ResetRadioSilenceDuration();
							duration = 2.0f;
						}
					}
					else
					{
						me->Radio(filename, NULL, me->GetProfile()->GetVoicePitch(), false);
						me->GetChatter()->ResetRadioSilenceDuration();
						me->StartVoiceFeedback(duration + 1.0f);
					}
				}
			}

			const float gap = 0.1f;
			m_nextTime = gpGlobals->time + duration + gap;
		}
		else
		{
			// skip directly to the next phrase
			m_nextTime = 0.0f;
		}
	}

	return true;
}

// If this statement refers to a specific place, return that place
// Places can be implicit in the statement, or explicitly defined
Place BotStatement::GetPlace() const
{
	// return any explicitly set place if we have one
	if (m_place != UNDEFINED_PLACE)
		return m_place;

	// look for an implicit place in our statement
	for (int i = 0; i < m_count; ++i)
	{
		if (m_statement[i].isPhrase && m_statement[i].phrase->IsPlace())
			return m_statement[i].phrase->GetID();
	}

	return 0;
}

// Return true if this statement has an associated count
bool BotStatement::HasCount() const
{
	for (int i = 0; i < m_count; ++i)
	{
		if (!m_statement[i].isPhrase && m_statement[i].context == CURRENT_ENEMY_COUNT)
			return true;
	}

	return false;
}

enum PitchHack { P_HI, P_NORMAL, P_LOW };

static int nextPitch = P_HI;

BotChatterInterface::BotChatterInterface(CCSBot *me)
{
	m_me = me;
	m_statementList = NULL;

	switch (nextPitch)
	{
	case P_HI:
		m_pitch = RANDOM_LONG(105, 110);
		break;
	case P_NORMAL:
		m_pitch = RANDOM_LONG(95, 105);
		break;
	case P_LOW:
		m_pitch = RANDOM_LONG(85, 95);
		break;
	}

	nextPitch = (nextPitch + 1) % 3;
	Reset();
}

BotChatterInterface::~BotChatterInterface()
{
	// free pending statements
	BotStatement *next;
	for (BotStatement *msg = m_statementList; msg != NULL; msg = next)
	{
		next = msg->m_next;
		delete msg;
	}
}

// Reset to initial state
void BotChatterInterface::Reset()
{
	BotStatement *msg, *nextMsg;

	// removing pending statements - except for those about the round results
	for (msg = m_statementList; msg; msg = nextMsg)
	{
		nextMsg = msg->m_next;

		if (msg->GetType() != REPORT_ROUND_END)
			RemoveStatement(msg);
	}

	m_seeAtLeastOneEnemy = false;
	m_timeWhenSawFirstEnemy = 0.0f;
	m_reportedEnemies = false;
	m_requestedBombLocation = false;

	ResetRadioSilenceDuration();

	m_needBackupInterval.Invalidate();
	m_spottedBomberInterval.Invalidate();
	m_spottedLooseBombTimer.Invalidate();
	m_heardNoiseTimer.Invalidate();
	m_scaredInterval.Invalidate();
	m_planInterval.Invalidate();
	IMPL(m_encourageTimer).Invalidate();
	m_escortingHostageTimer.Invalidate();
}

// Register a statement for speaking
void BotChatterInterface::AddStatement(BotStatement *statement, bool mustAdd)
{
	// don't add statements if bot chatter is shut off
	if (GetVerbosity() == OFF)
	{
		delete statement;
		return;
	}

	// if we only want mission-critical radio chatter, ignore non-important phrases
	if (GetVerbosity() == MINIMAL && !statement->IsImportant())
	{
		delete statement;
		return;
	}

	// don't add statements if we're dead
	if (!m_me->IsAlive() && !mustAdd)
	{
		delete statement;
		return;
	}

	// don't add empty statements
	if (statement->m_count == 0)
	{
		delete statement;
		return;
	}

	// don't add statements that are redundant with something we're already waiting to say
	BotStatement *s;
	for (s = m_statementList; s != NULL; s = s->m_next)
	{
		if (statement->IsRedundant(s))
		{
			m_me->PrintIfWatched("I tried to say something I'm already saying.\n");
			delete statement;
			return;
		}
	}

	// keep statements in order of start time

	// check list is empty
	if (m_statementList == NULL)
	{
		statement->m_next = NULL;
		statement->m_prev = NULL;
		m_statementList = statement;
		return;
	}

	// list has at least one statement on it

	// insert into list in order
	BotStatement *earlier = NULL;
	for (s = m_statementList; s != NULL; s = s->m_next)
	{
		if (s->GetStartTime() > statement->GetStartTime())
			break;

		earlier = s;
	}

	// insert just after "earlier"
	if (earlier != NULL)
	{
		if (earlier->m_next != NULL)
			earlier->m_next->m_prev = statement;

		statement->m_next = earlier->m_next;

		earlier->m_next = statement;
		statement->m_prev = earlier;
	}
	else
	{
		// insert at head
		statement->m_prev = NULL;
		statement->m_next = m_statementList;
		m_statementList->m_prev = statement;
		m_statementList = statement;
	}
}

// Remove a statement
void BotChatterInterface::RemoveStatement(BotStatement *statement)
{
	if (statement->m_next != NULL)
		statement->m_next->m_prev = statement->m_prev;

	if (statement->m_prev != NULL)
		statement->m_prev->m_next = statement->m_next;
	else
		m_statementList = statement->m_next;

	delete statement;
}

// Track nearby enemy count and report enemy activity
void BotChatterInterface::ReportEnemies()
{
	if (!m_me->IsAlive())
		return;

	if (m_me->GetNearbyEnemyCount() == 0)
	{
		m_seeAtLeastOneEnemy = false;
		m_reportedEnemies = false;
	}
	else if (!m_seeAtLeastOneEnemy)
	{
		m_seeAtLeastOneEnemy = true;
		m_timeWhenSawFirstEnemy = gpGlobals->time;
	}

	// determine whether we should report enemy activity
	if (!m_reportedEnemies && m_seeAtLeastOneEnemy)
	{
		// request backup if we're outnumbered
		if (m_me->IsOutnumbered() && NeedBackup())
		{
			m_reportedEnemies = true;
			return;
		}

		m_me->GetChatter()->EnemySpotted();
		m_reportedEnemies = true;
	}
}

void BotChatterInterface::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	;
}

// Invoked when we die
void BotChatterInterface::OnDeath()
{
	if (IsTalking())
	{
		if (m_me->GetChatter()->GetVerbosity() == BotChatterInterface::MINIMAL
			|| m_me->GetChatter()->GetVerbosity() == BotChatterInterface::NORMAL)
		{
			// we've died mid-sentance - emit a gargle of pain
			static const BotPhrase *pain = TheBotPhrases->GetPhrase("pain");

			if (pain != NULL)
			{
				m_me->Radio(pain->GetSpeakable(m_me->GetProfile()->GetVoiceBank()), NULL, m_me->GetProfile()->GetVoicePitch());
				m_me->GetChatter()->ResetRadioSilenceDuration();
			}
		}
	}

	// remove all of our statements
	Reset();
}

// Process ongoing chatter for this bot
void BotChatterInterface::Update()
{
	// report enemy activity
	ReportEnemies();

	// ask team to report in if we havent heard anything in awhile
	if (ShouldSpeak())
	{
		const float longTime = 30.0f;
		if (m_me->GetEnemiesRemaining() > 0 && GetRadioSilenceDuration() > longTime)
		{
			ReportIn();
		}
	}

	// speak if it is our turn
	BotStatement *say = GetActiveStatement();
	if (say != NULL)
	{
		// if our statement is active, speak it
		if (say->GetOwner() == m_me)
		{
			if (say->Update() == false)
			{
				// this statement is complete - destroy it
				RemoveStatement(say);
			}
		}
	}

	// Process active statements.
	// Removed expired statements, re-order statements according to their relavence and importance
	// Remove redundant statements (ie: our teammates already said them)
	const BotStatement *friendSay = GetActiveStatement();
	if (friendSay != NULL && friendSay->GetOwner() == m_me)
		friendSay = NULL;

	BotStatement *nextSay;
	for (say = m_statementList; say != NULL; say = nextSay)
	{
		nextSay = say->m_next;

		// check statement conditions
		if (!say->IsValid())
		{
			RemoveStatement(say);
			continue;
		}

		// don't interrupt ourselves
		if (say->IsSpeaking())
			continue;

		// check for obsolete statements
		if (say->IsObsolete())
		{
			m_me->PrintIfWatched("Statement obsolete - removing.\n");
			RemoveStatement(say);
			continue;
		}

		// if a teammate is saying what we were going to say, dont repeat it
		if (friendSay != NULL)
		{
			// convert what we're about to say based on what our teammate is currently saying
			say->Convert(friendSay);

			// don't say things our teammates have just said
			if (say->IsRedundant(friendSay))
			{
				// thie statement is redundant - destroy it
				m_me->PrintIfWatched("Teammate said what I was going to say - shutting up.\n");
				RemoveStatement(say);
			}
		}
	}
}

// Returns the statement that is being spoken, or is next to be spoken if no-one is speaking now
BotStatement *BotChatterInterface::GetActiveStatement()
{
	// keep track of statement waiting longest to be spoken - it is next
	BotStatement *earliest = nullptr;
	float earlyTime = 999999999.9f;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (!player)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		// ignore dead humans
		if (!player->IsBot() && !player->IsAlive())
			continue;

		// ignore enemies, since we can't hear them talk
		if (m_me->BotRelationship(player) == CCSBot::BOT_ENEMY)
			continue;

		// if not a bot, fail the test
		// TODO: Check if human is currently talking
		if (!player->IsBot())
			continue;

		CCSBot *bot = reinterpret_cast<CCSBot *>(player);
		auto say = bot->GetChatter()->m_statementList;
		while (say)
		{
			// if this statement is currently being spoken, return it
			if (say->IsSpeaking())
				return say;

			// keep track of statement that has been waiting longest to be spoken of anyone on our team
			if (say->GetStartTime() < earlyTime)
			{
				earlyTime = say->GetTimestamp();
				earliest = say;
			}

			say = say->m_next;
		}
	}

	// make sure it is time to start this statement
	if (earliest && earliest->GetStartTime() > gpGlobals->time)
		return nullptr;

	return earliest;
}

// Return true if we speaking makes sense now
bool BotChatterInterface::ShouldSpeak() const
{
	// don't talk to non-existent friends
	if (m_me->GetFriendsRemaining() == 0)
		return false;

	// if everyone is together, no need to tell them what's going on
	if (m_me->GetNearbyFriendCount() == m_me->GetFriendsRemaining())
		return false;

	return true;
}

float BotChatterInterface::GetRadioSilenceDuration()
{
#ifdef REGAMEDLL_FIXES
	if (m_me->m_iTeam != CT && m_me->m_iTeam != TERRORIST)
		return 0;
#endif

	return IMPL(m_radioSilenceInterval)[m_me->m_iTeam - 1].GetElapsedTime();
}

void BotChatterInterface::ResetRadioSilenceDuration()
{
#ifdef REGAMEDLL_FIXES
	if (m_me->m_iTeam != CT && m_me->m_iTeam != TERRORIST)
		return;
#endif

	IMPL(m_radioSilenceInterval)[m_me->m_iTeam - 1].Reset();
}

inline void SayWhere(BotStatement *say, Place place)
{
	say->AppendPhrase(TheBotPhrases->GetPlace(place));
}

// Report enemy sightings
void BotChatterInterface::EnemySpotted()
{
	// NOTE: This could be a few seconds out of date (enemy is in an adjacent place)
	Place place = m_me->GetEnemyPlace();

	BotStatement *say = new BotStatement(this, REPORT_VISIBLE_ENEMIES, 10.0f);

	// where are the enemies
	say->AppendPhrase(TheBotPhrases->GetPlace(place));

	// how many are there
	say->AppendPhrase(BotStatement::ACCUMULATE_ENEMIES_DELAY);
	say->AppendPhrase(BotStatement::CURRENT_ENEMY_COUNT);
	say->AddCondition(BotStatement::IS_IN_COMBAT);

	AddStatement(say);
}

NOXREF void BotChatterInterface::Clear(Place place)
{
	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);

	SayWhere(say, place);
	say->AppendPhrase(TheBotPhrases->GetPhrase("Clear"));
	AddStatement(say);
}

// Request enemy activity report
void BotChatterInterface::ReportIn()
{
	BotStatement *say = new BotStatement(this, REPORT_REQUEST_INFORMATION, 10.0f);

	say->AppendPhrase(TheBotPhrases->GetPhrase("RequestReport"));
	say->AddCondition(BotStatement::RADIO_SILENCE);
	say->AttachMeme(new BotRequestReportMeme());
	AddStatement(say);
}

// Report our situtation
void BotChatterInterface::ReportingIn()
{
	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);

	// where are we
	Place place = m_me->GetPlace();
	SayWhere(say, place);

	// what are we doing
	switch (m_me->GetTask())
	{
		case CCSBot::PLANT_BOMB:
		{
			m_me->GetChatter()->GoingToPlantTheBomb(UNDEFINED_PLACE);
			break;
		}
		case CCSBot::DEFUSE_BOMB:
		{
			m_me->GetChatter()->Say("DefusingBomb");
			break;
		}
		case CCSBot::GUARD_LOOSE_BOMB:
		{
			if (TheCSBots()->GetLooseBomb())
			{
				say->AppendPhrase(TheBotPhrases->GetPhrase("GuardingLooseBomb"));
				say->AttachMeme(new BotBombStatusMeme(CSGameState::LOOSE, TheCSBots()->GetLooseBomb()->pev->origin));
			}
			break;
		}
		case CCSBot::GUARD_HOSTAGES:
		{
			m_me->GetChatter()->GuardingHostages(UNDEFINED_PLACE, !m_me->IsAtHidingSpot());
			break;
		}
		case CCSBot::GUARD_HOSTAGE_RESCUE_ZONE:
		{
			m_me->GetChatter()->GuardingHostageEscapeZone(!m_me->IsAtHidingSpot());
			break;
		}
		case CCSBot::COLLECT_HOSTAGES:
		{
			break;
		}
		case CCSBot::RESCUE_HOSTAGES:
		{
			m_me->GetChatter()->EscortingHostages();
			break;
		}
		case CCSBot::GUARD_VIP_ESCAPE_ZONE:
		{
			break;
		}
	}

	// what do we see
	if (m_me->IsAttacking())
	{
		if (m_me->IsOutnumbered())
		{
			// in trouble in a firefight
			say->AppendPhrase(TheBotPhrases->GetPhrase("Help"));
			say->AttachMeme(new BotHelpMeme(place));
		}
		else
		{
			// battling enemies
			say->AppendPhrase(TheBotPhrases->GetPhrase("InCombat"));
		}
	}
	else
	{
		// not in combat, start our report a little later
		say->SetStartTime(gpGlobals->time + 2.0f);

		const float recentTime = 10.0f;
		if (m_me->GetEnemyDeathTimestamp() < recentTime && m_me->GetEnemyDeathTimestamp() >= m_me->GetTimeSinceLastSawEnemy() + 0.5f)
		{
			// recently saw an enemy die
			say->AppendPhrase(TheBotPhrases->GetPhrase("EnemyDown"));
		}
		else if (m_me->GetTimeSinceLastSawEnemy() < recentTime)
		{
			// recently saw an enemy
			say->AppendPhrase(TheBotPhrases->GetPhrase("EnemySpotted"));
		}
		else
		{
			// haven't seen enemies
			say->AppendPhrase(TheBotPhrases->GetPhrase("Clear"));
		}
	}

	AddStatement(say);
}

bool BotChatterInterface::NeedBackup()
{
	const float minRequestInterval = 10.0f;
	if (m_needBackupInterval.IsLessThen(minRequestInterval))
		return false;

	m_needBackupInterval.Reset();

	if (m_me->GetFriendsRemaining() == 0)
	{
		// we're all alone...
		Scared();
		return true;
	}
	else
	{
		// ask friends for help
		BotStatement *say = new BotStatement(this, REPORT_REQUEST_HELP, 10.0f);

		// where are we
		Place place = m_me->GetPlace();
		SayWhere(say, place);

		say->AppendPhrase(TheBotPhrases->GetPhrase("Help"));
		say->AttachMeme(new BotHelpMeme(place));
		AddStatement(say);
	}

	return true;
}

void BotChatterInterface::PinnedDown()
{
	// this is a form of "need backup"
	const float minRequestInterval = 10.0f;
	if (m_needBackupInterval.IsLessThen(minRequestInterval))
		return;

	m_needBackupInterval.Reset();

	BotStatement *say = new BotStatement(this, REPORT_REQUEST_HELP, 10.0f);

	// where are we
	Place place = m_me->GetPlace();
	SayWhere(say, place);

	say->AppendPhrase(TheBotPhrases->GetPhrase("PinnedDown"));
	say->AttachMeme(new BotHelpMeme(place));
	say->AddCondition(BotStatement::IS_IN_COMBAT);

	AddStatement(say);
}

void BotChatterInterface::HeardNoise(const Vector *pos)
{
	if (TheCSBots()->IsRoundOver())
		return;

	if (m_heardNoiseTimer.IsElapsed())
	{
		// throttle frequency
		m_heardNoiseTimer.Start(20.0f);

		// make rare, since many teammates may try to say this
		if (RANDOM_FLOAT(0.0f, 100.0f) < 33.0f)
		{
			BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 5.0f);

			say->AppendPhrase(TheBotPhrases->GetPhrase("HeardNoise"));
			say->SetPlace(TheNavAreaGrid.GetPlace(pos));

			AddStatement(say);
		}
	}
}

void BotChatterInterface::KilledMyEnemy(int victimID)
{
	// only report if we killed the last enemy in the area
	if (m_me->GetNearbyEnemyCount() <= 1)
		return;

	BotStatement *say = new BotStatement(this, REPORT_ENEMY_ACTION, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("KilledMyEnemy"));
	say->SetSubject(victimID);
	AddStatement(say);
}

void BotChatterInterface::EnemiesRemaining()
{
	// only report if we killed the last enemy in the area
	if (m_me->GetNearbyEnemyCount() > 1)
		return;

	BotStatement *say = new BotStatement(this, REPORT_ENEMIES_REMAINING, 5.0f);
	say->AppendPhrase(BotStatement::REMAINING_ENEMY_COUNT);
	say->SetStartTime(gpGlobals->time + RANDOM_FLOAT(2.0f, 4.0f));
	AddStatement(say);
}

void BotChatterInterface::Affirmative()
{
	BotStatement *say = new BotStatement(this, REPORT_ACKNOWLEDGE, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("Affirmative"));
	AddStatement(say);
}

void BotChatterInterface::Negative()
{
	BotStatement *say = new BotStatement(this, REPORT_ACKNOWLEDGE, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("Negative"));
	AddStatement(say);
}

void BotChatterInterface::GoingToPlantTheBomb(Place place)
{
	if (TheCSBots()->IsRoundOver())
		return;

	const float minInterval = 10.0f; // 20.0f
	if (m_planInterval.IsLessThen(minInterval))
		return;

	m_planInterval.Reset();

	BotStatement *say = new BotStatement(this, REPORT_CRITICAL_EVENT, 10.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("GoingToPlantBomb"));
	say->SetPlace(place);
	say->AttachMeme(new BotFollowMeme());
	AddStatement(say);
}

void BotChatterInterface::PlantingTheBomb(Place place)
{
	if (TheCSBots()->IsRoundOver())
		return;

	BotStatement *say = new BotStatement(this, REPORT_CRITICAL_EVENT, 10.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("PlantingBomb"));
	say->SetPlace(place);
	say->AttachMeme(new BotDefendHereMeme(m_me->pev->origin));
	AddStatement(say);
}

void BotChatterInterface::TheyPickedUpTheBomb()
{
	if (TheCSBots()->IsRoundOver())
		return;

	// if we already know the bomb is not loose, this is old news
	if (!m_me->GetGameState()->IsBombLoose())
		return;

	// update our gamestate - use our own position for now
	m_me->GetGameState()->UpdateBomber(&m_me->pev->origin);

	// tell our teammates
	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("TheyPickedUpTheBomb"));
	say->AttachMeme(new BotBombStatusMeme(CSGameState::MOVING, m_me->pev->origin));
	AddStatement(say);
}

void BotChatterInterface::SpottedBomber(CBasePlayer *bomber)
{
	if (m_me->GetGameState()->IsBombMoving())
	{
		// if we knew where the bomber was, this is old news
		const Vector *bomberPos = m_me->GetGameState()->GetBombPosition();
		const float closeRangeSq = 1000.0f * 1000.0f;
		if (bomberPos != NULL && (bomber->pev->origin - *bomberPos).LengthSquared() < closeRangeSq)
			return;
	}

	// update our gamestate
	m_me->GetGameState()->UpdateBomber(&bomber->pev->origin);

	// tell our teammates
	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);

	// where is the bomber
	Place place = TheNavAreaGrid.GetPlace(&bomber->pev->origin);
	SayWhere(say, place);

	say->AppendPhrase(TheBotPhrases->GetPhrase("SpottedBomber"));
	say->SetSubject(bomber->entindex());

	//say->AttachMeme(new BotHelpMeme(place));
	say->AttachMeme(new BotBombStatusMeme(CSGameState::MOVING, bomber->pev->origin));
	AddStatement(say);
}

void BotChatterInterface::SpottedLooseBomb(CBaseEntity *bomb)
{
	if (TheCSBots()->IsRoundOver())
		return;

	// if we already know the bomb is loose, this is old news
	if (m_me->GetGameState()->IsBombLoose())
		return;

	// update our gamestate
	m_me->GetGameState()->UpdateLooseBomb(&bomb->pev->origin);

	if (m_spottedLooseBombTimer.IsElapsed())
	{
		// throttle frequency
		m_spottedLooseBombTimer.Start(10.0f);

		// tell our teammates
		BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);

		// where is the bomb
		Place place = TheNavAreaGrid.GetPlace(&bomb->pev->origin);
		SayWhere(say, place);

		say->AppendPhrase(TheBotPhrases->GetPhrase("SpottedLooseBomb"));

		if (TheCSBots()->GetLooseBomb())
			say->AttachMeme(new BotBombStatusMeme(CSGameState::LOOSE, bomb->pev->origin));

		AddStatement(say);
	}
}

NOXREF void BotChatterInterface::GuardingLooseBomb(CBaseEntity *bomb)
{
	if (TheCSBots()->IsRoundOver() || !bomb)
		return;

#ifdef REGAMEDLL_FIXES
	const float minInterval = 20.0f;
	if (m_planInterval.IsLessThen(minInterval))
		return;

	m_planInterval.Reset();
#endif

	// update our gamestate
	m_me->GetGameState()->UpdateLooseBomb(&bomb->pev->origin);

	// tell our teammates
	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);

	// where is the bomb
	Place place = TheNavAreaGrid.GetPlace(&bomb->pev->origin);
	SayWhere(say, place);

	say->AppendPhrase(TheBotPhrases->GetPhrase("GuardingLooseBomb"));

	if (TheCSBots()->GetLooseBomb())
		say->AttachMeme(new BotBombStatusMeme(CSGameState::LOOSE, bomb->pev->origin));

	AddStatement(say);
}

void BotChatterInterface::RequestBombLocation()
{
	// only ask once per round
	if (m_requestedBombLocation)
		return;

	m_requestedBombLocation = true;

	// tell our teammates
	BotStatement *say = new BotStatement(this, REPORT_REQUEST_INFORMATION, 10.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("WhereIsTheBomb"));
	say->AttachMeme(new BotWhereBombMeme());
	AddStatement(say);
}

void BotChatterInterface::BombsiteClear(int zoneIndex)
{
	const CCSBotManager::Zone *zone = TheCSBots()->GetZone(zoneIndex);
	if (zone == NULL)
		return;

	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 10.0f);

	SayWhere(say, TheNavAreaGrid.GetPlace(&zone->m_center));
	say->AppendPhrase(TheBotPhrases->GetPhrase("BombsiteClear"));
	say->AttachMeme(new BotBombsiteStatusMeme(zoneIndex, BotBombsiteStatusMeme::CLEAR));
	AddStatement(say);
}

void BotChatterInterface::FoundPlantedBomb(int zoneIndex)
{
	const CCSBotManager::Zone *zone = TheCSBots()->GetZone(zoneIndex);
	if (zone == NULL)
		return;

	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("PlantedBombPlace"));
	say->SetPlace(TheNavAreaGrid.GetPlace(&zone->m_center));
	say->AttachMeme(new BotBombsiteStatusMeme(zoneIndex, BotBombsiteStatusMeme::PLANTED));
	AddStatement(say);
}

void BotChatterInterface::Scared()
{
	const float minInterval = 10.0f;
	if (m_scaredInterval.IsLessThen(minInterval))
		return;

	m_scaredInterval.Reset();

	BotStatement *say = new BotStatement(this, REPORT_EMOTE, 1.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("ScaredEmote"));
	say->AddCondition(BotStatement::IS_IN_COMBAT);
	AddStatement(say);
}

void BotChatterInterface::CelebrateWin()
{
	BotStatement *say = new BotStatement(this, REPORT_EMOTE, 15.0f);

	// wait a bit before speaking
	say->SetStartTime(gpGlobals->time + RANDOM_FLOAT(2.0f, 5.0f));

	const float quickRound = 45.0f;

	if (m_me->GetFriendsRemaining() == 0)
	{
		// we were the last man standing
		if (TheCSBots()->GetElapsedRoundTime() < quickRound)
			say->AppendPhrase(TheBotPhrases->GetPhrase("WonRoundQuickly"));
		else if (RANDOM_FLOAT(0.0f, 100.0f) < 33.3f)
			say->AppendPhrase(TheBotPhrases->GetPhrase("LastManStanding"));
	}
	else
	{
		if (TheCSBots()->GetElapsedRoundTime() < quickRound)
		{
			if (RANDOM_FLOAT(0.0f, 100.0f) < 33.3f)
				say->AppendPhrase(TheBotPhrases->GetPhrase("WonRoundQuickly"));
		}
		else if (RANDOM_FLOAT(0.0f, 100.0f) < 10.0f)
		{
			say->AppendPhrase(TheBotPhrases->GetPhrase("WonRound"));
		}
	}

	AddStatement(say);
}

void BotChatterInterface::AnnouncePlan(const char *phraseName, Place place)
{
	if (TheCSBots()->IsRoundOver())
		return;

	BotStatement *say = new BotStatement(this, REPORT_MY_PLAN, 10.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase(phraseName));
	say->SetPlace(place);

	// wait at least a short time after round start
	say->SetStartTime(TheCSBots()->GetRoundStartTime() + RANDOM_FLOAT(2.0, 3.0f));
	AddStatement(say);
}

void BotChatterInterface::GuardingHostages(Place place, bool isPlan)
{
	if (TheCSBots()->IsRoundOver())
		return;

	const float minInterval = 20.0f;
	if (m_planInterval.IsLessThen(minInterval))
		return;

#ifdef REGAMEDLL_FIXES
	m_planInterval.Reset();
#endif

	if (isPlan)
		AnnouncePlan("GoingToGuardHostages", place);
	else
		Say("GuardingHostages");
}

void BotChatterInterface::GuardingHostageEscapeZone(bool isPlan)
{
	if (TheCSBots()->IsRoundOver())
		return;

	const float minInterval = 20.0f;
	if (m_planInterval.IsLessThen(minInterval))
		return;

#ifdef REGAMEDLL_FIXES
	m_planInterval.Reset();
#endif

	if (isPlan)
		AnnouncePlan("GoingToGuardHostageEscapeZone", UNDEFINED_PLACE);
	else
		Say("GuardingHostageEscapeZone");
}

void BotChatterInterface::HostagesBeingTaken()
{
	if (TheCSBots()->IsRoundOver())
		return;

	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("HostagesBeingTaken"));
	say->AttachMeme(new BotHostageBeingTakenMeme());
	AddStatement(say);
}

void BotChatterInterface::HostagesTaken()
{
	if (TheCSBots()->IsRoundOver())
		return;

	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("HostagesTaken"));
	AddStatement(say);
}

void BotChatterInterface::TalkingToHostages()
{
	;
}

void BotChatterInterface::EscortingHostages()
{
	if (TheCSBots()->IsRoundOver())
		return;

	if (m_escortingHostageTimer.IsElapsed())
	{
		// throttle frequency
		m_escortingHostageTimer.Start(10.0f);

		BotStatement *say = new BotStatement(this, REPORT_MY_PLAN, 5.0f);
		say->AppendPhrase(TheBotPhrases->GetPhrase("EscortingHostages"));
		AddStatement(say);
	}
}

NOXREF void BotChatterInterface::HostageDown()
{
	if (TheCSBots()->IsRoundOver())
		return;

	BotStatement *say = new BotStatement(this, REPORT_INFORMATION, 3.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("HostageDown"));
	AddStatement(say);
}

void BotChatterInterface::Encourage(const char *phraseName, float repeatInterval, float lifetime)
{
	if (IMPL(m_encourageTimer).IsElapsed())
	{
		Say(phraseName, lifetime);
		IMPL(m_encourageTimer).Start(repeatInterval);
	}
}

void BotChatterInterface::KilledFriend()
{
	BotStatement *say = new BotStatement(this, REPORT_KILLED_FRIEND, 2.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("KilledFriend"));

	// give them time to react
	say->SetStartTime(gpGlobals->time + RANDOM_FLOAT(0.5f, 1.0f));
	AddStatement(say);
}

void BotChatterInterface::FriendlyFire()
{
	BotStatement *say = new BotStatement(this, REPORT_FRIENDLY_FIRE, 1.0f);
	say->AppendPhrase(TheBotPhrases->GetPhrase("FriendlyFire"));

	// give them time to react
	say->SetStartTime(gpGlobals->time + RANDOM_FLOAT(0.3f, 0.5f));
	AddStatement(say);
}
