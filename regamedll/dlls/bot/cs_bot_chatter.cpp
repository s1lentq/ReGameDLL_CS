#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

BotPhraseManager *TheBotPhrases = NULL;
CBaseEntity *g_pSelectedZombieSpawn = NULL;

#else // HOOK_GAMEDLL

BotPhraseManager *TheBotPhrases;
CBaseEntity *g_pSelectedZombieSpawn;

#endif // HOOK_GAMEDLL

/* <303469> ../cstrike/dlls/bot/cs_bot_chatter.cpp:32 */
NOBODY const Vector *GetRandomSpotAtPlace(Place place)
{
//	{
//		int count;                                            //    34
//		iterator iter;                                        //    35
//		int which;                                            //    46
//		{
//			class CNavArea *area;                        //    38
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //    36
//		operator++(_List_iterator<CNavArea*> *const this);  //    47
//		{
//			class CNavArea *area;                        //    49
//		}
//	}
}

/* <303541> ../cstrike/dlls/bot/cs_bot_chatter.cpp:62 */
NOBODY void BotMeme::Transmit(CCSBot *sender) const
{
//	{
//		int i;                                                //    64
//		{
//			class CBasePlayer *player;                   //    66
//			class CCSBot *bot;                           //    93
//			FNullEnt(entvars_t *pev);  //    71
//		}
//	}
}

/* <301f03> ../cstrike/dlls/bot/cs_bot_chatter.cpp:104 */
NOBODY void BotHelpMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	{
//		float const maxHelpRange;                              //   106
//	}
}

/* <306b4f> ../cstrike/dlls/bot/cs_bot_chatter.cpp:114 */
NOBODY void BotBombsiteStatusMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	Interpret(const class BotBombsiteStatusMeme *const this,
//			class CCSBot *sender,
//			class CCSBot *receiver);  //   114
}


/* <306ab6> ../cstrike/dlls/bot/cs_bot_chatter.cpp:137 */
NOBODY void BotBombStatusMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	Interpret(const class BotBombStatusMeme *const this,
//			class CCSBot *sender,
//			class CCSBot *receiver);  //   137
}

/* <302c87> ../cstrike/dlls/bot/cs_bot_chatter.cpp:167 */
NOBODY void BotFollowMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	{
//		class PathCost pathCost;                              //   178
//		float travelDistance;                                 //   179
//		float const tooFar;                                    //   185
//	}
//	Interpret(const class BotFollowMeme *const this,
//			class CCSBot *sender,
//			class CCSBot *receiver);  //   167
}

/* <302759> ../cstrike/dlls/bot/cs_bot_chatter.cpp:200 */
NOBODY void BotDefendHereMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	{
//		Place place;                                          //   209
//		{
//			const Vector *spot;                   //   213
//		}
//	}
}

/* <3082a5> ../cstrike/dlls/bot/cs_bot_chatter.cpp:234 */
NOBODY void BotWhereBombMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	{
//		int zone;                                             //   236
//	}
}

/* <30a56e> ../cstrike/dlls/bot/cs_bot_chatter.cpp:246 */
NOBODY void BotRequestReportMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
}

/* <3025b5> ../cstrike/dlls/bot/cs_bot_chatter.cpp:256 */
NOBODY void BotAllHostagesGoneMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	Say(//		const char *phraseName,
//		float lifetime,
//		float delay);  //   261
}

/* <3029a9> ../cstrike/dlls/bot/cs_bot_chatter.cpp:269 */
NOBODY void BotHostageBeingTakenMeme::Interpret(CCSBot *sender, CCSBot *receiver) const
{
//	HostageWasTaken(CSGameState *const this);  //   271
//	Interpret(const class BotHostageBeingTakenMeme *const this,
//			class CCSBot *sender,
//			class CCSBot *receiver);  //   269
}

/* <303609> ../cstrike/dlls/bot/cs_bot_chatter.cpp:285 */
NOBODY BotSpeakable::BotSpeakable(void)
{
	m_phrase = NULL;
}

/* <303655> ../cstrike/dlls/bot/cs_bot_chatter.cpp:291 */
NOBODY BotSpeakable::~BotSpeakable(void)
{
	if (m_phrase)
	{
		delete[] m_phrase;
		m_phrase = NULL;
	}
}

/* <30ba3b> ../cstrike/dlls/bot/cs_bot_chatter.cpp:303 */
NOBODY BotPhrase::BotPhrase(unsigned int id, bool isPlace)
{
//	vector(vector<std::vector<BotSpeakable*, std::allocator<BotSpeakable*>>*, std::allocator<std::vector<BotSpeakable*, std::allocaconst this);  //   303
//	vector(vector<int, std::allocator<int>> *const this);  //   303
//	vector(vector<int, std::allocator<int>> *const this);  //   303
//	ClearCriteria(const class BotPhrase *const this);  //   309
}

/* <3036c2> ../cstrike/dlls/bot/cs_bot_chatter.cpp:314 */
NOBODY BotPhrase::~BotPhrase(void)
{
//	{
//		int bank;                                             //   316
//		size(const class vector<std::vector<BotSpeakable*, std::allocator<BotSpeakable*>>*, std::allocator<std::vector<BotSpeakable*, std::const this);  //   316
//		{
//			int speakable;                                //   318
//			operator[](vector<std::vector<BotSpeakable*, std::allocator<BotSpeakable*>>*, std::allocator<std::vector<BotSpeakable*, std::allocaconst this,
//					size_type __n);  //   318
//			size(const class vector<BotSpeakable*, std::allocator<BotSpeakable*>> *const this);  //   318
//			~BotSpeakable(BotSpeakable *const this,
//					int const __in_chrg);  //   320
//		}
//		~vector(vector<BotSpeakable*, std::allocator<BotSpeakable*>> *const this,
//			int const __in_chrg);  //   322
//	}
//	~vector(vector<int, std::allocator<int>> *const this,
//		int const __in_chrg);  //   314
//	~vector(vector<int, std::allocator<int>> *const this,
//		int const __in_chrg);  //   314
//	~vector(vector<std::vector<BotSpeakable*, std::allocator<BotSpeakable*>>*, std::allocator<std::vector<BotSpeakable*, std::allocaconst this,
//		int const __in_chrg);  //   314
}

/* <30b837> ../cstrike/dlls/bot/cs_bot_chatter.cpp:326 */
NOBODY void BotPhrase::InitVoiceBank(int bankIndex)
{
//	push_back(vector<int, std::allocator<int>> *const this,
//			const value_type &__x);  //   330
//	push_back(vector<int, std::allocator<int>> *const this,
//			const value_type &__x);  //   331
//	vector(vector<BotSpeakable*, std::allocator<BotSpeakable*>> *const this);  //   332
//	push_back(vector<std::vector<BotSpeakable*, std::allocator<BotSpeakable*>>*, std::allocator<std::vector<BotSpeakable*, std::allocaconst this,
//			const value_type &__x);  //   332
}

/* <303917> ../cstrike/dlls/bot/cs_bot_chatter.cpp:340 */
char *BotPhrase::GetSpeakable(int bankIndex, float *duration) const
{
	if (bankIndex < 0 || bankIndex >= m_numVoiceBanks || m_count[bankIndex] == 0)
	{
		if (duration)
			*duration = 0.0f;

		return NULL;
	}

	// find phrase that meets the current criteria
	int start = m_index[bankIndex];
	while (true)
	{
		BotSpeakableVector *speakables = m_voiceBank[bankIndex];
		int &index = m_index[bankIndex];

#ifdef HOOK_GAMEDLL
		// TODO: temporary fix of std::vector padding
		*(byte *)&speakables += 4;
#endif // HOOK_GAMEDLL

		const BotSpeakable *speak = (*speakables)[index++];

		if (m_index[bankIndex] >= m_count[bankIndex])
			m_index[bankIndex] = 0;

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
			if (speak->m_count == UNDEFINED_COUNT || speak->m_count == min(m_countCriteria, COUNT_MANY))
			{
				if (duration)
					*duration = speak->m_duration;

				return speak->m_phrase;
			}
		}

		// check if we exhausted all speakables
		if (m_index[bankIndex] == start)
		{
			if (duration)
				*duration = 0.0f;

			return NULL;
		}
	}

	return NULL;
}

void (*pBotPhrase__Randomize)(void);

/* <30395a> ../cstrike/dlls/bot/cs_bot_chatter.cpp:395 */
NOBODY void __declspec(naked) BotPhrase::Randomize(void)
{
	__asm
	{
		jmp pBotPhrase__Randomize
	}

//	UNTESTED
//
//	for (unsigned int i = 0; i < m_voiceBank.size(); i++)
//	{
//		BotSpeakableVector *speakables = m_voiceBank[i];
//
//#ifdef HOOK_GAMEDLL
//		// TODO: temporary fix of std::vector padding
//		*(byte *)&speakables += 4;
//#endif // HOOK_GAMEDLL
//
//		BotSpeakable *firstElem = speakables->front();
//		int nSize = speakables->size();
//	
//		for (unsigned int index = 1; index < nSize; index++)
//		{
//			// TODO: check it, need hook std rand
//			int randIndex = (rand() % nSize);
//
//			BotSpeakable *speakable = (*speakables)[ randIndex ];
//
//			(*speakables)[ randIndex ] = (*speakables)[ index ];
//			(*speakables)[ index ] = speakable;
//		}
//	}
}

/* <303b3f> ../cstrike/dlls/bot/cs_bot_chatter.cpp:409 */
NOBODY BotPhraseManager::BotPhraseManager(void)
{
//	list(list<BotPhrase*, std::allocator<BotPhrase*>> *const this);  //   409
//	list(list<BotPhrase*, std::allocator<BotPhrase*>> *const this);  //   409
//	PlaceTimeInfo(PlaceTimeInfo *const this);  //   409
}

/* <303c45> ../cstrike/dlls/bot/cs_bot_chatter.cpp:417 */
NOBODY void BotPhraseManager::OnMapChange(void)
{
}

/* <303c70> ../cstrike/dlls/bot/cs_bot_chatter.cpp:425 */
void BotPhraseManager::OnRoundRestart(void)
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

/* <30c1fc> ../cstrike/dlls/bot/cs_bot_chatter.cpp:443 */
NOBODY bool BotPhraseManager::Initialize(const char *filename, int bankIndex)
{
//	{
//		bool isDefault;                                       //   445
//		int phraseDataLength;                                 //   446
//		char *phraseDataFile;                                //   447
//		char *phraseData;                                    //   448
//		unsigned int nextID;                                  //   459
//		int const RadioPathLen;                                //   461
//		char baseDir;                                         //   462
//		char compositeFilename;                               //   463
//		{
//			char *token;                                 //   474
//			{
//				bool isPlace;                         //   492
//				class BotPhrase *phrase;             //   495
//				PlaceCriteria placeCriteria;          //   533
//				CountCriteria countCriteria;          //   534
//				enum GameEventType radioEvent;        //   535
//				bool isImportant;                     //   536
//				{
//					class BotSpeakable *speak;   //   635
//					BotSpeakableVector *speakables;  //   657
//					operator[](vector<std::vector<BotSpeakable*, std::allocator<BotSpeakable*>>*, std::allocator<std::vector<BotSpeakable*, std::allocaconst this,
//							size_type __n);  //   657
//					{
//						enum GameEventType event;   //   610
//					}
//					BotSpeakable(BotSpeakable *const this);  //   635
//					CloneString(const char *str);  //   639
//					push_back(vector<BotSpeakable*, std::allocator<BotSpeakable*>> *const this,
//							const value_type &__x);  //   658
//					operator[](vector<int, std::allocator<int>> *const this,
//							size_type __n);  //   660
//					NameToID(const class BotPhraseManager *const this,
//						const char *name);  //   572
//					atoi(const char *__nptr);  //   593
//					CloneString(const char *str);  //   643
//				}
//				GetPlace(const class BotPhraseManager *const this,
//					const char *name);  //   517
//				GetPhrase(const class BotPhraseManager *const this,
//						const char *name);  //   521
//				BotPhrase(BotPhrase *const this,
//						unsigned int id,
//						bool isPlace);  //   498
//				CloneString(const char *str);  //   511
//				push_back(list<BotPhrase*, std::allocator<BotPhrase*>> *const this,
//						const value_type &__x);  //   671
//				push_back(list<BotPhrase*, std::allocator<BotPhrase*>> *const this,
//						const value_type &__x);  //   673
//			}
//			{
//				char *token;                         //   486
//			}
//		}
//	}
}

/* <30409e> ../cstrike/dlls/bot/cs_bot_chatter.cpp:682 */
NOBODY BotPhraseManager::~BotPhraseManager(void)
{
//	~list(list<BotPhrase*, std::allocator<BotPhrase*>>::~BotPhraseManager(//		int const __in_chrg);  //   682
//	{
//		iterator iter;                                        //   684
//		{
//			class BotPhrase *phrase;                     //   689
//		}
//		operator++(_List_iterator<BotPhrase*> *const this);  //   687
//		end(list<BotPhrase*, std::allocator<BotPhrase*>> *const this);  //   694
//		{
//			class BotPhrase *phrase;                     //   696
//		}
//		operator++(_List_iterator<BotPhrase*> *const this);  //   694
//		clear(list<BotPhrase*, std::allocator<BotPhrase*>> *const this);  //   701
//		clear(list<BotPhrase*, std::allocator<BotPhrase*>> *const this);  //   702
//	}
}

/* <3043ec> ../cstrike/dlls/bot/cs_bot_chatter.cpp:708 */
Place BotPhraseManager::NameToID(const char *name) const
{
	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (!Q_stricmp(phrase->m_name, name))
			return phrase->m_id;
	}

	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (!Q_stricmp(phrase->m_name, name))
			return phrase->m_id;
	}

	return 0;
}

/* <3044b4> ../cstrike/dlls/bot/cs_bot_chatter.cpp:732 */
const char *BotPhraseManager::IDToName(Place id) const
{
	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (phrase->m_id == id)
			return phrase->m_name;
	}

	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (phrase->m_id == id)
			return phrase->m_name;
	}

	return NULL;
}

/* <304597> ../cstrike/dlls/bot/cs_bot_chatter.cpp:758 */
NOBODY const BotPhrase *BotPhraseManager::GetPhrase(const char *name) const
{
	for (BotPhraseList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (!Q_stricmp(phrase->m_name, name))
			return phrase;
	}
	return NULL;
}

/* <304654> ../cstrike/dlls/bot/cs_bot_chatter.cpp:793 */
NOBODY const BotPhrase *BotPhraseManager::GetPlace(const char *name) const
{
	if (name == NULL)
		return NULL;

	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (!Q_stricmp(phrase->m_name, name))
			return phrase;
	}

	return NULL;
}

/* <3046eb> ../cstrike/dlls/bot/cs_bot_chatter.cpp:811 */
NOBODY const BotPhrase *BotPhraseManager::GetPlace(PlaceCriteria place) const
{
	if (place == UNDEFINED_PLACE)
		return NULL;

	for (BotPhraseList::const_iterator iter = m_placeList.begin(); iter != m_placeList.end(); ++iter)
	{
		const BotPhrase *phrase = *iter;

		if (phrase->m_id == place)
			return phrase;
	}

	return NULL;
}

/* <30477e> ../cstrike/dlls/bot/cs_bot_chatter.cpp:830 */
NOBODY BotStatement::BotStatement(BotChatterInterface *chatter, BotStatementType type, float expireDuration)
{
}

/* <3047bd> ../cstrike/dlls/bot/cs_bot_chatter.cpp:855 */
NOBODY BotStatement::~BotStatement(void)
{
}

/* <3047e0> ../cstrike/dlls/bot/cs_bot_chatter.cpp:863 */
NOBODY CCSBot *BotStatement::GetOwner(void) const
{

}

/* <304803> ../cstrike/dlls/bot/cs_bot_chatter.cpp:872 */
NOBODY void BotStatement::AttachMeme(BotMeme *meme)
{
}

/* <30482f> ../cstrike/dlls/bot/cs_bot_chatter.cpp:881 */
NOBODY void BotStatement::AddCondition(ConditionType condition)
{
}

/* <30485b> ../cstrike/dlls/bot/cs_bot_chatter.cpp:891 */
NOBODY bool BotStatement::IsImportant(void) const
{
//	{
//		int i;                                                //   894
//	}
}

/* <3048bc> ../cstrike/dlls/bot/cs_bot_chatter.cpp:911 */
NOBODY bool BotStatement::IsValid(void) const
{
//	{
//		int i;                                                //   913
//		GetOwner(const class BotStatement *const this);  //   919
//		GetOwner(const class BotStatement *const this);  //   935
//	}
}

/* <30492d> ../cstrike/dlls/bot/cs_bot_chatter.cpp:950 */
NOBODY bool BotStatement::IsRedundant(const BotStatement *say) const
{
}

/* <304977> ../cstrike/dlls/bot/cs_bot_chatter.cpp:990 */
NOBODY bool BotStatement::IsObsolete(void) const
{
//	GetOwner(const class BotStatement *const this);  //   993
}

/* <3049b6> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1008 */
NOBODY void BotStatement::Convert(const class BotStatement *say)
{
//	{
//		const class BotPhrase *meToo;                       //  1012
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1012
//	}
}

/* <304a7c> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1037 */
NOBODY void BotStatement::AppendPhrase(const class BotPhrase *phrase)
{
//	AppendPhrase(BotStatement *const this,
//			const class BotPhrase *phrase);  //  1037
}

/* <304acf> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1052 */
NOBODY void BotStatement::AppendPhrase(ContextType contextPhrase)
{
//	AppendPhrase(BotStatement *const this,
//			enum ContextType contextPhrase);  //  1052
}

/* <304b22> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1065 */
NOBODY bool BotStatement::Update(void)
{
//	{
//		class CCSBot *me;                                    //  1067
//		GetOwner(const class BotStatement *const this);  //  1067
//		{
//			float const reportTime;                        //  1083
//			GetNearbyEnemyCount(const class CCSBot *const this);  //  1084
//		}
//		{
//			float duration;                               //  1105
//			const class BotPhrase *phrase;              //  1106
//			{
//				const char *const speak;             //  1138
//				int enemyCount;                       //  1143
//				GetPhrase(const class BotPhraseManager *const this,
//						const char *name);  //  1152
//			}
//			{
//				int enemyCount;                       //  1120
//				GetNearbyEnemyCount(const class CCSBot *const this);  //  1120
//				GetNearbyFriendCount(const class CCSBot *const this);  //  1123
//				GetPhrase(const class BotPhraseManager *const this,
//						const char *name);  //  1130
//				SetCountCriteria(const class BotPhrase *const this,
//						CountCriteria count);  //  1131
//				GetPhrase(const class BotPhraseManager *const this,
//						const char *name);  //  1125
//				BotHelpMeme(BotHelpMeme *const this,
//						Place place);  //  1126
//				AttachMeme(BotStatement *const this,
//						class BotMeme *meme);  //  1126
//			}
//			{
//				float const gap;                       //  1249
//				GetVerbosity(const class BotChatterInterface *const this);  //  1181
//				{
//					enum GameEventType radioEvent;//  1183
//					ResetRadioSilenceDuration(BotChatterInterface *const this);  //  1192
//				}
//				{
//					const char *filename;       //  1202
//					bool sayIt;                   //  1205
//					{
//						enum GameEventType radioEvent;        //  1226
//						ResetRadioSilenceDuration(BotChatterInterface *const this);  //  1236
//					}
//					ResetRadioSilenceDuration(BotChatterInterface *const this);  //  1243
//					SetPlaceCriteria(const class BotPhrase *const this,
//							PlaceCriteria place);  //  1200
//					GetSpeakable(const class BotPhrase *const this,
//							int bankIndex,
//							float *duration);  //  1202
//					{
//						float timeSince;      //  1210
//						float const minRepeatTime;   //  1211
//						GetPlaceStatementInterval(const class BotPhraseManager *const this,
//										Place place);  //  1210
//						ResetPlaceStatementInterval(BotPhraseManager *const this,
//										Place place);  //  1218
//					}
//				}
//			}
//		}
//	}
}

/* <2fee36> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1266 */
NOBODY Place BotStatement::GetPlace(void) const
{
//	{
//		int i;                                                //  1273
//	}
}

/* <305289> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1283 */
NOBODY bool BotStatement::HasCount(void) const
{
//	{
//		int i;                                                //  1285
//	}
}

/* <305543> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1308 */
NOBODY BotChatterInterface::BotChatterInterface(CCSBot *me)
{
//	IntervalTimer(IntervalTimer *const this);  //  1308
//	IntervalTimer(IntervalTimer *const this);  //  1308
//	IntervalTimer(IntervalTimer *const this);  //  1308
//	IntervalTimer(IntervalTimer *const this);  //  1308
//	CountdownTimer(CountdownTimer *const this);  //  1308
//	CountdownTimer(CountdownTimer *const this);  //  1308
//	CountdownTimer(CountdownTimer *const this);  //  1308
}

/* <305307> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1334 */
NOBODY BotChatterInterface::~BotChatterInterface(void)
{
//	{
//		class BotStatement *msg;                             //  1337
//		~BotStatement(BotStatement *const this,
//				int const __in_chrg);  //  1339
//	}
}

/* <305386> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1347 */
NOBODY void BotChatterInterface::Reset(void)
{
//	{
//		class BotStatement *msg;                             //  1349
//		class BotStatement *nextMsg;                         //  1349
//		RemoveStatement(BotChatterInterface *const this,
//				class BotStatement *statement);  //  1357
//		ResetRadioSilenceDuration(BotChatterInterface *const this);  //  1365
//		Invalidate(CountdownTimer *const this);  //  1373
//		Invalidate(IntervalTimer *const this);  //  1367
//		Invalidate(IntervalTimer *const this);  //  1368
//		Invalidate(CountdownTimer *const this);  //  1369
//		Invalidate(CountdownTimer *const this);  //  1370
//		Invalidate(IntervalTimer *const this);  //  1371
//		Invalidate(IntervalTimer *const this);  //  1372
//		Invalidate(CountdownTimer *const this);  //  1374
//	}
}

/* <305661> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1381 */
NOBODY void BotChatterInterface::AddStatement(BotStatement *statement, bool mustAdd)
{
//	{
//		class BotStatement *s;                               //  1403
//		class BotStatement *earlier;                         //  1428
//		GetVerbosity(const class BotChatterInterface *const this);  //  1384
//		IsImportant(const class BotStatement *const this);  //  1388
//	}
}

/* <3056fa> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1462 */
NOBODY void BotChatterInterface::RemoveStatement(BotStatement *statement)
{
//	~BotStatement(BotStatement *const this,
//			int const __in_chrg);  //  1472
}

/* <3087ee> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1479 */
NOBODY void BotChatterInterface::ReportEnemies(void)
{
//	GetNearbyEnemyCount(const class CCSBot *const this);  //  1484
}

/* <305743> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1515 */
NOBODY void BotChatterInterface::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{

}

/* <30579e> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1524 */
NOBODY void BotChatterInterface::OnDeath(void)
{
//	{
//		const class BotPhrase *pain;                        //  1532
//		GetSpeakable(const class BotPhrase *const this,
//				int bankIndex,
//				float *duration);  //  1535
//		ResetRadioSilenceDuration(BotChatterInterface *const this);  //  1536
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1532
//	}
//	IsTalking(const class BotChatterInterface *const this);  //  1526
//	GetVerbosity(const class BotChatterInterface *const this);  //  1528
//	GetVerbosity(const class BotChatterInterface *const this);  //  1529
}

/* <308852> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1549 */
NOBODY void BotChatterInterface::Update(void)
{
//	{
//		class BotStatement *say;                             //  1565
//		const class BotStatement *friendSay;                //  1586
//		class BotStatement *nextSay;                         //  1590
//		ShouldSpeak(const class BotChatterInterface *const this);  //  1555
//		GetOwner(const class BotStatement *const this);  //  1570
//		GetOwner(const class BotStatement *const this);  //  1587
//		IsValid(const class BotStatement *const this);  //  1596
//		RemoveStatement(BotChatterInterface *const this,
//				class BotStatement *statement);  //  1598
//		RemoveStatement(BotChatterInterface *const this,
//				class BotStatement *statement);  //  1625
//		IsObsolete(const class BotStatement *const this);  //  1607
//		IsRedundant(const class BotStatement *const this,
//				const class BotStatement *say);  //  1621
//		{
//			float const longTime;                          //  1557
//			GetRadioSilenceDuration(BotChatterInterface *const this);  //  1558
//		}
//		RemoveStatement(BotChatterInterface *const this,
//				class BotStatement *statement);  //  1575
//	}
}

/* <305915> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1635 */
NOBODY BotStatement *BotChatterInterface::GetActiveStatement(void)
{
//	{
//		class BotStatement *earliest;                        //  1638
//		float earlyTime;                                      //  1639
//		{
//			int i;                                        //  1641
//			{
//				class CBasePlayer *player;           //  1643
//				class CCSBot *bot;                   //  1667
//				FNullEnt(entvars_t *pev);  //  1648
//				{
//					class BotStatement *say;     //  1669
//				}
//			}
//		}
//	}
}

/* <305a35> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1694 */
NOBODY bool BotChatterInterface::ShouldSpeak(void) const
{
//	GetNearbyFriendCount(const class CCSBot *const this);  //  1701
}

/* <305a8f> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1708 */
NOBODY float BotChatterInterface::GetRadioSilenceDuration(void)
{
//	GetElapsedTime(const class IntervalTimer *const this);  //  1710
}

/* <305b15> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1714 */
NOBODY void BotChatterInterface::ResetRadioSilenceDuration(void)
{
//	Reset(IntervalTimer *const this);  //  1716
}

/* <305d7b> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1732 */
NOBODY inline void SayWhere(BotStatement *say, Place place)
{
}

/* <305b50> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1740 */
NOBODY void BotChatterInterface::EnemySpotted(void)
{
//	{
//		Place place;                                          //  1743
//		class BotStatement *say;                             //  1745
//		GetPlace(const class BotPhraseManager *const this,
//			PlaceCriteria place);  //  1748
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1745
//		AppendPhrase(BotStatement *const this,
//				enum ContextType contextPhrase);  //  1751
//		AppendPhrase(BotStatement *const this,
//				enum ContextType contextPhrase);  //  1752
//		AddCondition(BotStatement *const this,
//				enum ConditionType condition);  //  1753
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1748
//	}
}

/* <305da4> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1759 */
NOBODY void BotChatterInterface::Clear(Place place)
{
//	{
//		class BotStatement *say;                             //  1761
//		SayWhere(BotStatement *say,
//			Place place);  //  1763
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1761
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1764
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1764
//	}
}

/* <305ffa> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1773 */
NOBODY void BotChatterInterface::ReportIn(void)
{
//	{
//		class BotStatement *say;                             //  1775
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1775
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1777
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1777
//		AddCondition(BotStatement *const this,
//				enum ConditionType condition);  //  1778
//		BotRequestReportMeme(BotRequestReportMeme *const this);  //  1779
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  1779
//	}
}

/* <309851> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1788 */
NOBODY void BotChatterInterface::ReportingIn(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  1790
//		class BotStatement *say;                             //  1792
//		Place place;                                          //  1795
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1792
//		SayWhere(BotStatement *say,
//			Place place);  //  1796
//		GoingToPlantTheBomb(BotChatterInterface *const this,
//					Place place);  //  1803
//		{
//			float const recentTime;                        //  1874
//			SetStartTime(BotStatement *const this,
//					float timestamp);  //  1872
//			GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //  1875
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  1878
//			AppendPhrase(BotStatement *const this,
//					const class BotPhrase *phrase);  //  1888
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  1888
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  1883
//		}
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1860
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1860
//		BotHelpMeme(BotHelpMeme *const this,
//				Place place);  //  1861
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  1861
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1866
//		Say(BotChatterInterface *const this,
//			const char *phraseName,
//			float lifetime,
//			float delay);  //  1809
//		GuardingHostages(BotChatterInterface *const this,
//				Place place,
//				bool isPlan);  //  1825
//		GuardingHostageEscapeZone(BotChatterInterface *const this,
//						bool isPlan);  //  1831
//		GetLooseBomb(CCSBotManager *const this);  //  1815
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1817
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1817
//		GetLooseBomb(CCSBotManager *const this);  //  1818
//		BotBombStatusMeme(BotBombStatusMeme *const this,
//					enum BombState state,
//					const Vector *pos);  //  1818
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  1818
//	}
}

/* <3084cf> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1896 */
NOBODY bool BotChatterInterface::NeedBackup(void)
{
//	{
//		float const minRequestInterval;                        //  1898
//		IsLessThen(const class IntervalTimer *const this,
//				float duration);  //  1899
//		{
//			class BotStatement *say;                     //  1913
//			Place place;                                  //  1916
//			BotStatement(BotStatement *const this,
//					class BotChatterInterface *chatter,
//					enum BotStatementType type,
//					float expireDuration);  //  1913
//			SayWhere(BotStatement *say,
//				Place place);  //  1917
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  1919
//			AppendPhrase(BotStatement *const this,
//					const class BotPhrase *phrase);  //  1919
//			BotHelpMeme(BotHelpMeme *const this,
//					Place place);  //  1920
//			AttachMeme(BotStatement *const this,
//					class BotMeme *meme);  //  1920
//		}
//		Reset(IntervalTimer *const this);  //  1902
//	}
}

/* <3061a8> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1929 */
NOBODY void BotChatterInterface::PinnedDown(void)
{
//	{
//		float const minRequestInterval;                        //  1932
//		class BotStatement *say;                             //  1938
//		Place place;                                          //  1941
//		IsLessThen(const class IntervalTimer *const this,
//				float duration);  //  1933
//		Reset(IntervalTimer *const this);  //  1936
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1938
//		SayWhere(BotStatement *say,
//			Place place);  //  1942
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1944
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1944
//		BotHelpMeme(BotHelpMeme *const this,
//				Place place);  //  1945
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  1945
//		AddCondition(BotStatement *const this,
//				enum ConditionType condition);  //  1946
//	}
}

/* <3064e2> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1952 */
NOBODY void BotChatterInterface::HeardNoise(const Vector *pos)
{
//	{
//		class CCSBotManager *ctrl;                           //  1954
//		IsElapsed(const class CountdownTimer *const this);  //  1958
//		Start(CountdownTimer *const this,
//			float duration);  //  1961
//		{
//			class BotStatement *say;                     //  1966
//			BotStatement(BotStatement *const this,
//					class BotChatterInterface *chatter,
//					enum BotStatementType type,
//					float expireDuration);  //  1966
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  1968
//			AppendPhrase(BotStatement *const this,
//					const class BotPhrase *phrase);  //  1968
//			SetPlace(BotStatement *const this,
//				Place where);  //  1969
//		}
//	}
}

/* <3066a7> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1978 */
NOBODY void BotChatterInterface::KilledMyEnemy(int victimID)
{
//	{
//		class BotStatement *say;                             //  1984
//		GetNearbyEnemyCount(const class CCSBot *const this);  //  1981
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1984
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  1986
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  1986
//		SetSubject(BotStatement *const this,
//				int playerID);  //  1987
//	}
}

/* <306853> ../cstrike/dlls/bot/cs_bot_chatter.cpp:1993 */
NOBODY void BotChatterInterface::EnemiesRemaining(void)
{
//	{
//		class BotStatement *say;                             //  1999
//		GetNearbyEnemyCount(const class CCSBot *const this);  //  1996
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  1999
//		AppendPhrase(BotStatement *const this,
//				enum ContextType contextPhrase);  //  2000
//		SetStartTime(BotStatement *const this,
//				float timestamp);  //  2001
//	}
}

/* <306974> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2008 */
NOBODY void BotChatterInterface::Affirmative(void)
{
//	{
//		class BotStatement *say;                             //  2010
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2010
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2012
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2012
//	}
}

/* <306bb2> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2018 */
NOBODY void BotChatterInterface::Negative(void)
{
//	{
//		class BotStatement *say;                             //  2020
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2020
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2022
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2022
//	}
}

/* <306cf4> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2028 */
NOBODY void BotChatterInterface::GoingToPlantTheBomb(Place place)
{
//	{
//		class CCSBotManager *ctrl;                           //  2030
//		float const minInterval;                               //  2034
//		class BotStatement *say;                             //  2040
//		IsLessThen(const class IntervalTimer *const this,
//				float duration);  //  2035
//		Reset(IntervalTimer *const this);  //  2038
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2040
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2042
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2042
//		SetPlace(BotStatement *const this,
//			Place where);  //  2043
//		BotFollowMeme(BotFollowMeme *const this);  //  2044
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2044
//	}
}

/* <306ef6> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2050 */
NOBODY void BotChatterInterface::PlantingTheBomb(Place place)
{
//	{
//		class CCSBotManager *ctrl;                           //  2052
//		class BotStatement *say;                             //  2056
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2056
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2058
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2058
//		SetPlace(BotStatement *const this,
//			Place where);  //  2059
//		BotDefendHereMeme(BotDefendHereMeme *const this,
//					const Vector *pos);  //  2060
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2060
//	}
}

/* <3070c8> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2066 */
NOBODY void BotChatterInterface::TheyPickedUpTheBomb(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  2068
//		class BotStatement *say;                             //  2080
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2080
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2082
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2082
//		BotBombStatusMeme(BotBombStatusMeme *const this,
//					enum BombState state,
//					const Vector *pos);  //  2084
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2084
//	}
}

/* <307272> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2090 */
NOBODY void BotChatterInterface::SpottedBomber(CBasePlayer *bomber)
{
//	{
//		class BotStatement *say;                             //  2105
//		Place place;                                          //  2108
//		{
//			const Vector *bomberPos;              //  2095
//			float const closeRangeSq;                      //  2096
//			operator-(const Vector *const this,
//					const Vector &v);  //  2097
//			LengthSquared(const Vector *const this);  //  2097
//		}
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2105
//		SayWhere(BotStatement *say,
//			Place place);  //  2109
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2111
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2111
//		entindex(CBaseEntity *const this);  //  2113
//		SetSubject(BotStatement *const this,
//				int playerID);  //  2113
//		BotBombStatusMeme(BotBombStatusMeme *const this,
//					enum BombState state,
//					const Vector *pos);  //  2116
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2116
//	}
}

/* <30761a> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2122 */
NOBODY void BotChatterInterface::SpottedLooseBomb(CBaseEntity *bomb)
{
//	{
//		class CCSBotManager *ctrl;                           //  2124
//		IsElapsed(const class CountdownTimer *const this);  //  2135
//		{
//			class BotStatement *say;                     //  2141
//			Place place;                                  //  2144
//			Start(CountdownTimer *const this,
//				float duration);  //  2138
//			BotStatement(BotStatement *const this,
//					class BotChatterInterface *chatter,
//					enum BotStatementType type,
//					float expireDuration);  //  2141
//			SayWhere(BotStatement *say,
//				Place place);  //  2145
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  2147
//			AppendPhrase(BotStatement *const this,
//					const class BotPhrase *phrase);  //  2147
//			GetLooseBomb(CCSBotManager *const this);  //  2149
//			BotBombStatusMeme(BotBombStatusMeme *const this,
//						enum BombState state,
//						const Vector *pos);  //  2150
//			AttachMeme(BotStatement *const this,
//					class BotMeme *meme);  //  2150
//		}
//	}
}

/* <30795b> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2157 */
NOBODY void BotChatterInterface::GuardingLooseBomb(CBaseEntity *bomb)
{
//	{
//		class CCSBotManager *ctrl;                           //  2163
//		class BotStatement *say;                             //  2171
//		Place place;                                          //  2174
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2171
//		SayWhere(BotStatement *say,
//			Place place);  //  2175
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2177
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2177
//		GetLooseBomb(CCSBotManager *const this);  //  2179
//		BotBombStatusMeme(BotBombStatusMeme *const this,
//					enum BombState state,
//					const Vector *pos);  //  2180
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2180
//	}
}

/* <307c56> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2186 */
NOBODY void BotChatterInterface::RequestBombLocation(void)
{
//	{
//		class BotStatement *say;                             //  2195
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2195
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2197
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2197
//		BotWhereBombMeme(BotWhereBombMeme *const this);  //  2199
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2199
//	}
}

/* <307de2> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2205 */
NOBODY void BotChatterInterface::BombsiteClear(int zoneIndex)
{
//	{
//		class CCSBotManager *ctrl;                           //  2207
//		const class Zone *zone;                             //  2208
//		class BotStatement *say;                             //  2212
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2212
//		SayWhere(BotStatement *say,
//			Place place);  //  2214
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2215
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2215
//		BotBombsiteStatusMeme(BotBombsiteStatusMeme *const this,
//					int zoneIndex,
//					enum StatusType status);  //  2217
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2217
//	}
}

/* <3080b8> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2223 */
NOBODY void BotChatterInterface::FoundPlantedBomb(int zoneIndex)
{
//	{
//		class CCSBotManager *ctrl;                           //  2225
//		const class Zone *zone;                             //  2226
//		class BotStatement *say;                             //  2230
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2230
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2232
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2232
//		SetPlace(BotStatement *const this,
//			Place where);  //  2233
//		BotBombsiteStatusMeme(BotBombsiteStatusMeme *const this,
//					int zoneIndex,
//					enum StatusType status);  //  2235
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2235
//	}
}

/* <308308> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2242 */
NOBODY void BotChatterInterface::Scared(void)
{
//	{
//		float const minInterval;                               //  2244
//		class BotStatement *say;                             //  2250
//		IsLessThen(const class IntervalTimer *const this,
//				float duration);  //  2245
//		Reset(IntervalTimer *const this);  //  2248
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2250
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2252
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2252
//		AddCondition(BotStatement *const this,
//				enum ConditionType condition);  //  2253
//	}
}

/* <308b60> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2259 */
NOBODY void BotChatterInterface::CelebrateWin(void)
{
//	{
//		class BotStatement *say;                             //  2261
//		float const quickRound;                                //  2266
//		class CCSBotManager *ctrl;                           //  2267
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2261
//		SetStartTime(BotStatement *const this,
//				float timestamp);  //  2264
//		GetElapsedRoundTime(const class CCSBotManager *const this);  //  2272
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2282
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2286
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2286
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2273
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2275
//	}
}

/* <308e52> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2294 */
NOBODY void BotChatterInterface::AnnouncePlan(const char *phraseName, Place place)
{
//	{
//		class CCSBotManager *ctrl;                           //  2296
//		class BotStatement *say;                             //  2300
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2300
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2302
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2302
//		SetPlace(BotStatement *const this,
//			Place where);  //  2303
//		SetStartTime(BotStatement *const this,
//				float timestamp);  //  2306
//	}
}

/* <308fdd> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2312 */
NOBODY void BotChatterInterface::GuardingHostages(Place place, bool isPlan)
{
//	{
//		class CCSBotManager *ctrl;                           //  2314
//		float const minInterval;                               //  2318
//		IsLessThen(const class IntervalTimer *const this,
//				float duration);  //  2319
//		Say(BotChatterInterface *const this,
//			const char *phraseName,
//			float lifetime,
//			float delay);  //  2325
//	}
}

/* <3091eb> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2329 */
NOBODY void BotChatterInterface::GuardingHostageEscapeZone(bool isPlan)
{
//	{
//		class CCSBotManager *ctrl;                           //  2331
//		float const minInterval;                               //  2335
//		IsLessThen(const class IntervalTimer *const this,
//				float duration);  //  2336
//		Say(BotChatterInterface *const this,
//			const char *phraseName,
//			float lifetime,
//			float delay);  //  2342
//	}
}

/* <3093a9> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2346 */
NOBODY void BotChatterInterface::HostagesBeingTaken(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  2348
//		class BotStatement *say;                             //  2352
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2352
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2354
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2354
//		BotHostageBeingTakenMeme(BotHostageBeingTakenMeme *const this);  //  2355
//		AttachMeme(BotStatement *const this,
//				class BotMeme *meme);  //  2355
//	}
}

/* <309542> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2361 */
NOBODY void BotChatterInterface::HostagesTaken(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  2363
//		class BotStatement *say;                             //  2367
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2367
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2369
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2369
//	}
}

/* <309691> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2375 */
NOBODY void BotChatterInterface::TalkingToHostages(void)
{
}

/* <3096bc> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2380 */
NOBODY void BotChatterInterface::EscortingHostages(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  2382
//		IsElapsed(const class CountdownTimer *const this);  //  2386
//		{
//			class BotStatement *say;                     //  2391
//			Start(CountdownTimer *const this,
//				float duration);  //  2389
//			BotStatement(BotStatement *const this,
//					class BotChatterInterface *chatter,
//					enum BotStatementType type,
//					float expireDuration);  //  2391
//			GetPhrase(const class BotPhraseManager *const this,
//					const char *name);  //  2393
//			AppendPhrase(BotStatement *const this,
//					const class BotPhrase *phrase);  //  2393
//		}
//	}
}

/* <30a5b9> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2400 */
NOBODY void BotChatterInterface::HostageDown(void)
{
//	{
//		class CCSBotManager *ctrl;                           //  2402
//		class BotStatement *say;                             //  2406
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2406
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2408
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2408
//	}
}

/* <30a708> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2414 */
NOBODY void BotChatterInterface::Encourage(const char *phraseName, float repeatInterval, float lifetime)
{
//	{
//		class CCSBotManager *ctrl;                           //  2416
//		IsElapsed(const class CountdownTimer *const this);  //  2418
//		Say(BotChatterInterface *const this,
//			const char *phraseName,
//			float lifetime,
//			float delay);  //  2420
//		Start(CountdownTimer *const this,
//			float duration);  //  2421
//	}
}

/* <30a905> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2427 */
NOBODY void BotChatterInterface::KilledFriend(void)
{
//	{
//		class BotStatement *say;                             //  2429
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2429
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2431
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2431
//		SetStartTime(BotStatement *const this,
//				float timestamp);  //  2434
//	}
}

/* <30aa67> ../cstrike/dlls/bot/cs_bot_chatter.cpp:2440 */
NOBODY void BotChatterInterface::FriendlyFire(void)
{
//	{
//		class BotStatement *say;                             //  2442
//		BotStatement(BotStatement *const this,
//				class BotChatterInterface *chatter,
//				enum BotStatementType type,
//				float expireDuration);  //  2442
//		GetPhrase(const class BotPhraseManager *const this,
//				const char *name);  //  2444
//		AppendPhrase(BotStatement *const this,
//				const class BotPhrase *phrase);  //  2444
//		SetStartTime(BotStatement *const this,
//				float timestamp);  //  2447
//	}
}
