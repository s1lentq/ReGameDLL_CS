#include "precompiled.h"

const char *CCSTutor::m_TutorIdentifierList[] =
{
	"YOU_FIRED_A_SHOT",
	"YOU_SHOULD_RELOAD",
	"YOU_ARE_OUT_OF_AMMO",
	"YOU_KILLED_A_TEAMMATE",
	"YOU_KILLED_PLAYER",
	"YOU_KILLED_PLAYER_ONE_LEFT",
	"YOU_KILLED_LAST_ENEMY",
	"YOU_KILLED_PLAYER_HEADSHOT",
	"YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT",
	"YOU_KILLED_LAST_ENEMY_HEADSHOT",
	"YOU_DIED",
	"YOU_DIED_HEADSHOT",
	"YOU_FELL_TO_YOUR_DEATH",
	"YOU_WERE_JUST_HURT",
	"YOU_ARE_BLIND_FROM_FLASHBANG",
	"YOU_ATTACKED_TEAMMATE",
	"BUY_TIME_BEGIN",
	"BOMB_PLANTED_T",
	"BOMB_PLANTED_CT",
	"TEAMMATE_KILLED",
	"TEAMMATE_KILLED_ONE_LEFT",
	"LAST_TEAMMATE_KILLED",
	"ENEMY_KILLED",
	"ENEMY_KILLED_ONE_LEFT",
	"LAST_ENEMY_KILLED",
	"YOU_SPAWNED",
	"YOU_SEE_FRIEND",
	"YOU_SEE_ENEMY",
	"YOU_SEE_FRIEND_CORPSE",
	"YOU_SEE_ENEMY_CORPSE",
	"YOU_SEE_LOOSE_BOMB_T",
	"YOU_SEE_LOOSE_BOMB_CT",
	"YOU_SEE_BOMB_CARRIER_T",
	"YOU_SEE_BOMB_CARRIER_CT",
	"YOU_SEE_PLANTED_BOMB_T",
	"YOU_SEE_PLANTED_BOMB_CT",
	"YOU_ARE_BOMB_CARRIER",
	"YOU_SEE_LOOSE_WEAPON",
	"YOU_SEE_LOOSE_DEFUSER",
	"YOU_SEE_BOMBSITE_T",
	"YOU_SEE_BOMBSITE_CT",
	"YOU_SEE_BOMBSITE_T_BOMB",
	"YOU_SEE_HOSTAGE_T",
	"YOU_SEE_HOSTAGE_CT",
	"YOU_SEE_HOSTAGE_CT_EXAMINE",
	"YOU_USED_HOSTAGE_MORE_LEFT",
	"YOU_USED_HOSTAGE_NO_MORE_LEFT",
	"ALL_HOSTAGES_FOLLOWING_T",
	"ALL_HOSTAGES_FOLLOWING_CT",
	"HOSTAGE_RESCUED_T",
	"HOSTAGE_RESCUED_CT",
	"YOU_RESCUED_HOSTAGE",
	"YOU_ARE_IN_BOMBSITE_T",
	"YOU_ARE_IN_BOMBSITE_CT",
	"YOU_ARE_IN_BOMBSITE_T_BOMB",
	"ALL_HOSTAGES_RESCUED_T",
	"ALL_HOSTAGES_RESCUED_CT",
	"YOU_DAMAGED_HOSTAGE",
	"YOU_KILLED_HOSTAGE",
	"ALL_HOSTAGES_DEAD",
	"YOU_HAVE_BEEN_SHOT_AT",
	"TIME_RUNNING_OUT_DE_T",
	"TIME_RUNNING_OUT_DE_CT",
	"TIME_RUNNING_OUT_CS_T",
	"TIME_RUNNING_OUT_CS_CT",
	"DEFUSING_WITHOUT_KIT",
	"BOMB_DEFUSED_T",
	"BOMB_DEFUSED_CT",
	"YOU_DEFUSED_BOMB",
	"BOMB_EXPLODED_T",
	"BOMB_EXPLODED_CT",
	"ROUND_START_DE_T",
	"ROUND_START_DE_CT",
	"ROUND_START_CS_T",
	"ROUND_START_CS_CT",
	"ROUND_OVER",
	"ROUND_DRAW",
	"CT_WIN",
	"T_WIN",
	"DEATH_CAMERA_START",
	"RADIO_COVER_ME",
	"RADIO_YOU_TAKE_THE_POINT",
	"RADIO_HOLD_THIS_POSITION",
	"RADIO_REGROUP_TEAM",
	"RADIO_FOLLOW_ME",
	"RADIO_TAKING_FIRE",
	"RADIO_GO_GO_GO",
	"RADIO_TEAM_FALL_BACK",
	"RADIO_STICK_TOGETHER_TEAM",
	"RADIO_GET_IN_POSITION_AND_WAIT",
	"RADIO_STORM_THE_FRONT",
	"RADIO_REPORT_IN_TEAM",
	"RADIO_AFFIRMATIVE",
	"RADIO_ENEMY_SPOTTED",
	"RADIO_NEED_BACKUP",
	"RADIO_SECTOR_CLEAR",
	"RADIO_IN_POSITION",
	"RADIO_REPORTING_IN",
	"RADIO_GET_OUT_OF_THERE",
	"RADIO_NEGATIVE",
	"RADIO_ENEMY_DOWN",
	"BUY_NEED_PRIMARY",
	"BUY_NEED_PRIMARY_AMMO",
	"BUY_NEED_SECONDARY_AMMO",
	"BUY_NEED_ARMOR",
	"BUY_NEED_DEFUSE_KIT",
	"BUY_NEED_GRENADE",
	"CAREER_TASK_DONE_MORE_LEFT",
	"CAREER_TASK_DONE_ONE_LEFT",
	"CAREER_TASK_DONE_ALL_DONE",
	"HINT_BEGIN",
	"HINT_1",
	"HINT_2",
	"HINT_3",
	"HINT_4",
	"HINT_5",
	"HINT_10",
	"HINT_11",
	"HINT_12",
	"HINT_13",
	"HINT_14",
	"HINT_15",
	"HINT_20",
	"HINT_21",
	"HINT_22",
	"HINT_23",
	"HINT_24",
	"HINT_25",
	"HINT_26",
	"HINT_30",
	"HINT_31",
	"HINT_32",
	"HINT_33",
	"HINT_34",
	"HINT_40",
	"HINT_50",
	"HINT_51",
	"HINT_52",
	"HINT_53",
	"HINT_60",
	"HINT_61",
	"HINT_70",
	"HINT_71",
	"HINT_72",
	"HINT_73",
	"HINT_END",
	"INGAME_HINT_BEGIN",
	"INGAME_HINT_1",
	"INGAME_HINT_2",
	"INGAME_HINT_3"
};

CCSTutor::CCSTutor()
{
	m_stateSystem = new CCSTutorStateSystem;

	m_nextViewableCheckTime = 0;
	m_currentlyShownMessageID = TUTOR_NUM_MESSAGES;
	m_currentMessageEvent = nullptr;
	m_messageTypeMask = TUTORMESSAGETYPE_ALL;
	m_lastScenarioEvent = nullptr;
	m_haveSpawned = false;
	m_lastHintShown = HINT_BEGIN;
	m_lastInGameHintShown = INGAME_HINT_BEGIN;

	ReadTutorMessageFile();
	ApplyPersistentDecay();
	ResetPlayerDeathInfo();
}

CCSTutor::~CCSTutor()
{
	if (m_stateSystem)
	{
		delete m_stateSystem;
		m_stateSystem = nullptr;
	}

	if (m_currentMessageEvent)
	{
		DeleteEvent(m_currentMessageEvent);
		m_currentMessageEvent = nullptr;
	}

	if (m_lastScenarioEvent)
	{
		DeleteEvent(m_lastScenarioEvent);
		m_lastScenarioEvent = nullptr;
	}

	ClearCurrentEvent();
	ClearEventList();
}

void ParseMessageParameters(char *&messageData, TutorMessage *ret)
{
	char *token;

	while (true)
	{
		messageData = SharedParse((char *)messageData);
		token = SharedGetToken();

		if (!messageData || !Q_stricmp(token, "End"))
		{
			break;
		}

		if (!Q_stricmp(token, "String"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_text = Q_strdup(SharedGetToken());
		}
		else if (!Q_stricmp(token, "Duration"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_duration = Q_atoi(SharedGetToken());
		}
		else if (!Q_stricmp(token, "Priority"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_priority = Q_atoi(SharedGetToken());
		}
		else if (!Q_stricmp(token, "KeepOld"))
		{
			messageData = SharedParse((char *)messageData);
			token = SharedGetToken();

			if (!Q_stricmp(token, "true"))
			{
				ret->m_keepOld = TUTORMESSAGEKEEPOLDTYPE_KEEP_OLD;
			}
			else if (!Q_stricmp(token, "updatecontent"))
			{
				ret->m_keepOld = TUTORMESSAGEKEEPOLDTYPE_UPDATE_CONTENT;
			}
			else
			{
				ret->m_keepOld = TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD;
			}
		}
		else if (!Q_stricmp(token, "Class"))
		{
			messageData = SharedParse((char *)messageData);

			if (!Q_stricmp(SharedGetToken(), "Examine"))
			{
				ret->m_class = TUTORMESSAGECLASS_EXAMINE;
			}
			else
			{
				ret->m_class = TUTORMESSAGECLASS_NORMAL;
			}
		}
		else if (!Q_stricmp(token, "Decay"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_decay = Q_atoi(SharedGetToken());
		}
		else if (!Q_stricmp(token, "Type"))
		{
			messageData = SharedParse((char *)messageData);
			token = SharedGetToken();

			if (!Q_stricmp(token, "FriendDeath"))
			{
				ret->m_type = TUTORMESSAGETYPE_FRIEND_DEATH;
			}
			else if (!Q_stricmp(token, "EnemyDeath"))
			{
				ret->m_type = TUTORMESSAGETYPE_ENEMY_DEATH;
			}
			else if (!Q_stricmp(token, "Scenario"))
			{
				ret->m_type = TUTORMESSAGETYPE_SCENARIO;
			}
			else if (!Q_stricmp(token, "Buy"))
			{
				ret->m_type = TUTORMESSAGETYPE_BUY;
			}
			else if (!Q_stricmp(token, "Career"))
			{
				ret->m_type = TUTORMESSAGETYPE_CAREER;
			}
			else if (!Q_stricmp(token, "Hint"))
			{
				ret->m_type = TUTORMESSAGETYPE_HINT;
			}
			else if (!Q_stricmp(token, "InGameHint"))
			{
				ret->m_type = TUTORMESSAGETYPE_INGAME_HINT;
			}
			else if (!Q_stricmp(token, "EndGame"))
			{
				ret->m_type = TUTORMESSAGETYPE_END_GAME;
			}
			else
			{
				ret->m_type = TUTORMESSAGETYPE_DEFAULT;
			}
		}
		else if (!Q_stricmp(token, "Lifetime"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_lifetime = Q_atoi(SharedGetToken());
		}
		else if (!Q_stricmp(token, "DuplicateID"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_duplicateID = Q_atoi(SharedGetToken());
		}
		else if (!Q_stricmp(token, "Interrupt"))
		{
			messageData = SharedParse((char *)messageData);

			if (!Q_stricmp(SharedGetToken(), "Now"))
			{
				ret->m_interruptFlag = TUTORMESSAGEINTERRUPTFLAG_NOW_DAMMIT;
			}
			else
			{
				ret->m_interruptFlag = TUTORMESSAGEINTERRUPTFLAG_DEFAULT;
			}
		}
		else if (!Q_stricmp(token, "MinDisplayTimeOverride"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_minDisplayTimeOverride = Q_atof(SharedGetToken());
		}
		else if (!Q_stricmp(token, "MinRepeatInterval"))
		{
			messageData = SharedParse((char *)messageData);
			ret->m_minRepeatInterval = Q_atof(SharedGetToken());
		}
	}
}

TutorMessage *ConstructTutorMessage(char *&messageData, TutorMessage *defaults)
{
	TutorMessage *msg = new TutorMessage;

	msg->m_text = nullptr;
	msg->m_duplicateID = defaults->m_duplicateID;
	msg->m_keepOld = defaults->m_keepOld;
	msg->m_duration = defaults->m_duration;
	msg->m_priority = defaults->m_priority;
	msg->m_class = defaults->m_class;
	msg->m_type = defaults->m_type;
	msg->m_decay = defaults->m_decay;
	msg->m_lifetime = defaults->m_lifetime;
	msg->m_interruptFlag = defaults->m_interruptFlag;
	msg->m_minDisplayTimeOverride = defaults->m_minDisplayTimeOverride;
	msg->m_minRepeatInterval = defaults->m_minRepeatInterval;
	msg->m_examineStartTime = -1.0f;
	msg->m_timesShown = 0;
	msg->m_lastCloseTime = 0;

	ParseMessageParameters(messageData, msg);

	return msg;
}

void ReadDefaultValues(char *&messageData, TutorMessage *defaults)
{
	ParseMessageParameters(messageData, defaults);
}

void CCSTutor::ReadTutorMessageFile()
{
	int messageFileLen = 0;

	char *messageFile;
	char *messageData;
	TutorMessage defaultMessage;

	messageFile = messageData = (char *)LOAD_FILE_FOR_ME("tutordata.txt", &messageFileLen);

	if (!messageFile)
	{
		if (AreRunningCZero())
		{
			CONSOLE_ECHO("Warning: Cannot access tutor message file tutordata.txt\n");
		}

		return;
	}

	defaultMessage.m_duplicateID = 0;
	defaultMessage.m_keepOld = TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD;
	defaultMessage.m_duration = 1;
	defaultMessage.m_priority = 0;
	defaultMessage.m_class = TUTORMESSAGECLASS_NORMAL;
	defaultMessage.m_type = TUTORMESSAGETYPE_DEFAULT;
	defaultMessage.m_decay = 10;
	defaultMessage.m_lifetime = 10;
	defaultMessage.m_interruptFlag = TUTORMESSAGEINTERRUPTFLAG_DEFAULT;
	defaultMessage.m_minDisplayTimeOverride = 0;
	defaultMessage.m_minRepeatInterval = 0;

	while (true)
	{
		messageData = SharedParse(messageData);
		if (!messageData)
			break;

		char *token = SharedGetToken();
		if (!Q_stricmp(token, "TutorMessage"))
		{
			messageData = SharedParse(messageData);
			token = SharedGetToken();

			std::string identifier = token;
			TutorMessage *tm = ConstructTutorMessage(messageData, &defaultMessage);

			m_messageMap[identifier] = tm;
		}
		else if (!Q_stricmp(token, "Defaults"))
		{
			ReadDefaultValues(messageData, &defaultMessage);
		}
	}

	FREE_FILE(messageFile);
}

void CCSTutor::ApplyPersistentDecay()
{
	for (TutorMessageID mid = YOU_FIRED_A_SHOT; mid < TUTOR_NUM_MESSAGES; mid++)
	{
		TutorMessage *definition = GetTutorMessageDefinition(mid);
		if (definition)
		{
			int timesShown = GET_TIMES_TUTOR_MESSAGE_SHOWN(mid);
			if (timesShown != -1)
			{
				definition->m_timesShown = timesShown;
			}
		}
	}
}

bool CCSTutor::HasCurrentWindowBeenActiveLongEnough(float time)
{
	return (m_currentlyShownMessageID < 0 || m_currentlyShownMessageID >= TUTOR_NUM_MESSAGES || time > m_currentlyShownMessageMinimumCloseTime);
}

bool CCSTutor::ShouldShowMessageEvent(TutorMessageEvent *event, float time)
{
	if (!event)
		return false;

	TutorMessage *message = GetTutorMessageDefinition(event->GetID());
	if (!message)
		return false;

	if (message->m_class == TUTORMESSAGECLASS_NORMAL)
	{
		if (message->m_decay)
		{
			if (message->m_timesShown >= message->m_decay)
				return false;
		}
	}

	if (!(m_messageTypeMask & message->m_type) || (time - message->m_lastCloseTime < message->m_minRepeatInterval))
		return false;

	if (HasCurrentWindowBeenActiveLongEnough(time))
		return true;

	if (message->m_interruptFlag != TUTORMESSAGEINTERRUPTFLAG_NOW_DAMMIT)
		return false;

	TutorMessage *current = GetTutorMessageDefinition(m_currentlyShownMessageID);
	if (!current || (DoMessagesHaveSameID(event->GetID(), m_currentlyShownMessageID) && current->m_keepOld != TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD))
		return false;

	if (message->m_priority > current->m_priority
		|| message->m_priority == current->m_priority
		|| m_currentMessageEvent->GetTimeActive(time) < event->GetTimeActive(time))
	{
		return true;
	}

	return false;
}

void CCSTutor::CheckForInterruptingMessageEvent(float time)
{
	bool newEvent = false;

	TutorMessageEvent *event = m_eventList;
	TutorMessage *oldMessage = GetTutorMessageDefinition(m_currentlyShownMessageID);
	TutorMessageEvent *oldEvent = m_currentMessageEvent;

	while (event)
	{
		if (ShouldShowMessageEvent(event, time))
		{
			newEvent = true;
			ShowTutorMessage(event);
		}

		event = event->GetNext();
	}

	if (!newEvent)
	{
		return;
	}

	if (oldEvent)
	{
		ProcessShownDeathsForEvent(event);
		DeleteEvent(oldEvent);
	}

	CloseCurrentWindow();
	if (oldMessage)
	{
		oldMessage->m_lastCloseTime = time;
	}

	DeleteEventFromEventList(m_currentMessageEvent);
	ConstructMessageAndDisplay();
}

void CCSTutor::TutorThink(float time)
{
	if (m_nextViewableCheckTime <= time)
	{
		CheckForBombViewable();
		CheckForLooseWeaponViewable();
		CheckForLooseDefuserViewable();
		CheckForTimeRunningOut();
		CheckForBombsiteViewable();
		CheckForHostageViewable();
		CheckExamineMessages(time);
		CheckHintMessages(time);
		CheckInGameHintMessages(time);
		CheckForNeedToReload(true);

		if (m_haveSpawned && CanLocalPlayerBuyStuff())
		{
			m_messageTypeMask = TUTORMESSAGETYPE_BUY;
			CreateAndAddEventToList(BUY_TIME_BEGIN);
			m_haveSpawned = false;
		}

		if (CanLocalPlayerBuyStuff() && m_messageTypeMask == TUTORMESSAGETYPE_BUY)
		{
			CheckBuyZoneMessages();
		}
		else
		{
			if (!CanLocalPlayerBuyStuff() && m_messageTypeMask == TUTORMESSAGETYPE_BUY)
			{
				OnEvent(EVENT_PLAYER_LEFT_BUY_ZONE);
			}
		}

		m_nextViewableCheckTime = cv_tutor_viewable_check_interval.value + time;
	}

	CheckForInactiveEvents(time);
	CheckForWindowClose(time);
	CheckForContentUpdate();
	CheckForInterruptingMessageEvent(time);
}

void CCSTutor::CheckForWindowClose(float time)
{
	if (m_currentlyShownMessageID < 0 || m_currentlyShownMessageID >= TUTOR_NUM_MESSAGES || time <= m_currentlyShownMessageCloseTime)
		return;

	TutorMessageEvent *event = GetTutorMessageUpdateEvent();
	if (!event)
	{
		ClearCurrentEvent();
		return;
	}

	UpdateCurrentMessage(event);
	DeleteEventFromEventList(event);
}

void CCSTutor::CheckForContentUpdate()
{
	if (m_currentlyShownMessageID < 0 || m_currentlyShownMessageID >= TUTOR_NUM_MESSAGES)
		return;

	TutorMessage *definition = GetTutorMessageDefinition(m_currentlyShownMessageID);
	if (!definition || definition->m_keepOld != TUTORMESSAGEKEEPOLDTYPE_UPDATE_CONTENT)
		return;

	TutorMessageEvent *event = GetTutorMessageUpdateEvent();
	if (event)
	{
		UpdateCurrentMessage(event);
		DeleteEventFromEventList(event);
	}
}

void CCSTutor::ClearCurrentEvent(bool closeWindow, bool processDeathsForEvent)
{
	TutorMessage *oldMessage = GetTutorMessageDefinition(m_currentlyShownMessageID);
	if (oldMessage)
	{
		oldMessage->m_lastCloseTime = gpGlobals->time;
	}

	if (processDeathsForEvent)
	{
		ProcessShownDeathsForEvent(m_currentMessageEvent);
	}

	if (closeWindow)
	{
		CloseCurrentWindow();
	}

	m_currentlyShownMessageID = TUTOR_NUM_MESSAGES;
	m_currentlyShownMessageCloseTime = 0;
	m_currentlyShownMessageMinimumCloseTime = 0;

	if (m_currentMessageEvent)
	{
		DeleteEvent(m_currentMessageEvent);
		m_currentMessageEvent = nullptr;
	}
}

void CCSTutor::ProcessShownDeathsForEvent(TutorMessageEvent *event)
{
	if (!event)
		return;

	for (auto& info : m_playerDeathInfo)
	{
		if (info.m_event == event) {
			info.m_hasBeenShown = true;
			info.m_event = nullptr;
		}
	}
}

TutorMessageEvent *CCSTutor::GetTutorMessageUpdateEvent()
{
	TutorMessage *definition = GetTutorMessageDefinition(m_currentlyShownMessageID);
	if (!definition || definition->m_keepOld == TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD)
		return nullptr;

	for (TutorMessageEvent *event = m_eventList; event; event = event->GetNext())
	{
		if (DoMessagesHaveSameID(event->GetID(), m_currentlyShownMessageID))
		{
			return event;
		}
	}

	return nullptr;
}

bool CCSTutor::GetDuplicateMessagesFromEventList(TutorMessageEvent *&event1, TutorMessageEvent *&event2)
{
	for (event1 = m_eventList; event1; event1 = event1->GetNext())
	{
		for (event2 = event1->GetNext(); event2; event2 = event2->GetNext())
		{
			if (DoMessagesHaveSameID(event1->GetID(), event2->GetID()))
			{
				return true;
			}
		}
	}

	return false;
}

void CCSTutor::CheckForInactiveEvents(float time)
{
	TutorMessageEvent *event = m_eventList;
	while (event)
	{
		if (!event->IsActive(time))
		{
			TutorMessageEvent *temp = event->GetNext();

			DeleteEventFromEventList(event);
			DeleteEvent(event);

			event = temp;
		}
		else
			event = event->GetNext();
	}

	TutorMessageEvent *event1 = nullptr;
	TutorMessageEvent *event2 = nullptr;

	if (GetDuplicateMessagesFromEventList(event1, event2))
	{
		if (event1->GetTimeActive(time) < event2->GetTimeActive(time))
		{
			TransferDeathEvents(event2, event1);
			DeleteEventFromEventList(event2);
			DeleteEvent(event2);
		}
		else
		{
			TransferDeathEvents(event1, event2);
			DeleteEventFromEventList(event1);
			DeleteEvent(event1);
		}
	}
}

void CCSTutor::CancelEvent(TutorMessageID mid)
{
	if (m_currentlyShownMessageID == mid)
		ClearCurrentEvent();

	TutorMessageEvent *event = m_eventList;
	while (event)
	{
		TutorMessageEvent *temp = event->GetNext();

		if (event->GetID() == mid)
		{
			DeleteEventFromEventList(event);
			DeleteEvent(event);
		}

		event = temp;
	}

	if (m_lastScenarioEvent && m_lastScenarioEvent->GetID() == mid)
	{
		DeleteEvent(m_lastScenarioEvent);
		m_lastScenarioEvent = nullptr;
	}
}

NOXREF void CCSTutor::LookupHotKey(TutorMessageID mid, int paramNum, wchar_t *buf, int buflen)
{
#ifdef _WIN32
	_snwprintf(buf, buflen - 1, L"KEY%d", paramNum);
#endif
}

TutorMessageEvent *CCSTutor::CreateTutorMessageEvent(TutorMessageID mid, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	char enemyList[2048];
	char teammateList[2048];

	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return nullptr;

	TutorMessage *message = GetTutorMessageDefinition(mid);
	if (!message)
		return nullptr;

	TutorMessageEvent *event = new TutorMessageEvent
	(
		mid,
		message->m_duplicateID,
		gpGlobals->time,
		message->m_lifetime,
		message->m_priority
	);

	switch (mid)
	{
	case YOU_KILLED_PLAYER_ONE_LEFT:
	case YOU_KILLED_LAST_ENEMY:
	case YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT:
	case YOU_KILLED_LAST_ENEMY_HEADSHOT:
	case ENEMY_KILLED_ONE_LEFT:
	case LAST_ENEMY_KILLED:
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
			ConstructRecentDeathsList(TERRORIST, enemyList, sizeof(enemyList), event);
			event->AddParameter(enemyList);
			break;
		case TERRORIST:
			ConstructRecentDeathsList(CT, teammateList, sizeof(teammateList), event);
			event->AddParameter(teammateList);
			break;
		}
		break;
	}
	case YOU_KILLED_PLAYER:
	case YOU_KILLED_PLAYER_HEADSHOT:
	case ENEMY_KILLED:
	{
		int numT, numCT;
		char numTStr[16], numCTStr[16];

		GetNumPlayersAliveOnTeams(numT, numCT);

		Q_snprintf(numTStr, sizeof(numTStr), "%i", numT);
		Q_snprintf(numCTStr, sizeof(numCTStr), "%i", numCT);

		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
			event->AddParameter(numCTStr);
			ConstructRecentDeathsList(TERRORIST, enemyList, sizeof(enemyList), event);
			event->AddParameter(enemyList);
			break;
		case TERRORIST:
			event->AddParameter(numTStr);
			ConstructRecentDeathsList(CT, teammateList, sizeof(teammateList), event);
			event->AddParameter(teammateList);
			break;
		}
		break;
	}
	case CAREER_TASK_DONE_MORE_LEFT:
	{
		char numLeftStr[16];
		int numtasks = 0;

		if (TheCareerTasks)
		{
			numtasks = TheCareerTasks->GetNumRemainingTasks();
		}
		Q_sprintf(numLeftStr, "%d", numtasks);
		event->AddParameter(numLeftStr);
		break;
	}
	case YOU_KILLED_A_TEAMMATE:
	case TEAMMATE_KILLED_ONE_LEFT:
	case LAST_TEAMMATE_KILLED:
		ConstructRecentDeathsList(pLocalPlayer->m_iTeam, enemyList, sizeof(enemyList), event);
		event->AddParameter(enemyList);
		break;
	case TEAMMATE_KILLED:
	{
		int numT;
		int numCT;

		char numTStr[16];
		char numCTStr[16];

		GetNumPlayersAliveOnTeams(numT, numCT);

		if (pLocalPlayer->IsAlive())
		{
			switch (pLocalPlayer->m_iTeam)
			{
			case CT:        numCT--; break;
			case TERRORIST: numT--;  break;
			}
		}

		Q_snprintf(numTStr, sizeof(numTStr), "%i", numT);
		Q_snprintf(numCTStr, sizeof(numCTStr), "%i", numCT);

		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
			event->AddParameter(numCTStr);
			break;
		case TERRORIST:
			event->AddParameter(numTStr);
			break;
		}

		ConstructRecentDeathsList(pLocalPlayer->m_iTeam, teammateList, sizeof(teammateList), event);
		event->AddParameter(teammateList);
		break;
	}
	}

	return event;
}

void CCSTutor::AddToEventList(TutorMessageEvent *event)
{
	if (event)
	{
		event->SetNext(m_eventList);
		m_eventList = event;
	}
}

void CCSTutor::CreateAndAddEventToList(TutorMessageID mid, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	auto event = CreateTutorMessageEvent(mid, pEntity, pOther);
	if (event)
	{
		auto message = GetTutorMessageDefinition(mid);
		if (message && message->m_type == TUTORMESSAGETYPE_SCENARIO)
		{
			if (m_lastScenarioEvent)
			{
				DeleteEvent(m_lastScenarioEvent);
				m_lastScenarioEvent = nullptr;
			}

			m_lastScenarioEvent = CreateTutorMessageEvent(mid, pEntity, pOther);
		}

		AddToEventList(event);
	}
}

void CCSTutor::DeleteEventFromEventList(TutorMessageEvent *event)
{
	if (!event)
		return;

	TutorMessageEvent *temp = m_eventList;

	if (temp != event)
	{
		if (temp)
		{
			while (event != temp->GetNext())
			{
				temp = temp->GetNext();
				if (!temp)
				{
					return;
				}
			}

			if (temp && temp->GetNext() == event)
			{
				temp->SetNext(temp->GetNext()->GetNext());
			}
		}
	}
	else
	{
		m_eventList = m_eventList->GetNext();
	}
}

void CCSTutor::ClearEventList()
{
	while (m_eventList)
	{
		TutorMessageEvent *temp = m_eventList;
		m_eventList = m_eventList->GetNext();

		DeleteEvent(temp);
	}
}

void CCSTutor::DeleteEvent(TutorMessageEvent *event)
{
	for (auto& info : m_playerDeathInfo)
	{
		if (info.m_event == event) {
			info.m_event = nullptr;
		}
	}

	delete event;
}

void CCSTutor::PurgeMessages()
{
	ClearCurrentEvent();
	ClearEventList();

	if (m_lastScenarioEvent)
	{
		DeleteEvent(m_lastScenarioEvent);
		m_lastScenarioEvent = nullptr;
	}
}

void CCSTutor::ComputeDisplayTimesForMessage()
{
	TutorMessage *message = GetTutorMessageDefinition(m_currentlyShownMessageID);
	if (!message)
	{
		m_currentlyShownMessageCloseTime = gpGlobals->time;
		return;
	}

	m_currentlyShownMessageCloseTime = message->m_duration + gpGlobals->time;
	m_currentlyShownMessageMinimumCloseTime = cv_tutor_message_minimum_display_time.value;

	int stringLength = GET_LOCALIZED_STRING_LENGTH(message->m_text);
	float minShowTime = stringLength * cv_tutor_message_character_display_time_coefficient.value;

	if (minShowTime > m_currentlyShownMessageMinimumCloseTime)
	{
		m_currentlyShownMessageMinimumCloseTime = minShowTime;
	}

	if (message->m_minDisplayTimeOverride <= m_currentlyShownMessageMinimumCloseTime)
	{
		message->m_minDisplayTimeOverride = m_currentlyShownMessageMinimumCloseTime;
	}

	m_currentlyShownMessageMinimumCloseTime = message->m_minDisplayTimeOverride + gpGlobals->time;

	if (m_currentlyShownMessageMinimumCloseTime > m_currentlyShownMessageCloseTime)
	{
		m_currentlyShownMessageCloseTime = m_currentlyShownMessageMinimumCloseTime;
	}
}

NOXREF bool CCSTutor::ShouldUpdateCurrentMessage(TutorMessageID messageID)
{
	if (DoMessagesHaveSameID(messageID, m_currentlyShownMessageID))
	{
		TutorMessage *definition = GetTutorMessageDefinition(messageID);
		if (definition && definition->m_keepOld != TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD)
		{
			return true;
		}
	}

	return false;
}

void CCSTutor::UpdateCurrentMessage(TutorMessageEvent *event)
{
	TransferDeathEvents(m_currentMessageEvent, event);

	if (m_currentMessageEvent)
	{
		DeleteEvent(m_currentMessageEvent);
		m_currentMessageEvent = nullptr;
	}

	m_currentlyShownMessageID = (TutorMessageID)event->GetID();
	m_currentMessageEvent = event;

	TutorMessage *definition = GetTutorMessageDefinition(event->GetID());
	if (definition)
	{
		CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
		if (pLocalPlayer)
		{
			m_currentlyShownMessageCloseTime = definition->m_duration + gpGlobals->time;

			if (definition->m_keepOld == TUTORMESSAGEKEEPOLDTYPE_UPDATE_CONTENT)
			{
				CloseCurrentWindow();
				DisplayMessageToPlayer(pLocalPlayer, event->GetID(), definition->m_text, event);
			}
		}
	}
}

void CCSTutor::ShowTutorMessage(TutorMessageEvent *event)
{
	TutorMessageID mid = static_cast<TutorMessageID>(event->GetID());
	if (mid < 0 || mid >= TUTOR_NUM_MESSAGES)
		return;

	TutorMessage *message = GetTutorMessageDefinition(mid);
	if (message)
	{
		m_currentlyShownMessageID = mid;
		m_currentMessageEvent = event;

		m_currentlyShownMessageCloseTime = 0;
		m_currentlyShownMessageMinimumCloseTime = 0;
	}
}

void CCSTutor::ConstructMessageAndDisplay()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer && !pLocalPlayer->IsBot())
	{
		TutorMessageID mid = static_cast<TutorMessageID>(m_currentMessageEvent->GetID());
		if (mid < 0 || mid >= TUTOR_NUM_MESSAGES)
			return;

		TutorMessage *message = GetTutorMessageDefinition(mid);
		if (message)
		{
			message->m_timesShown++;
			ComputeDisplayTimesForMessage();
			DisplayMessageToPlayer(pLocalPlayer, mid, message->m_text, m_currentMessageEvent);
		}
	}
}

void CCSTutor::CallEventHandler(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	switch (event)
	{
	case EVENT_WEAPON_FIRED:
		HandleWeaponFired(pEntity, pOther);
		break;
	case EVENT_WEAPON_FIRED_ON_EMPTY:
		HandleWeaponFiredOnEmpty(pEntity, pOther);
		break;
	case EVENT_WEAPON_RELOADED:
		HandleWeaponReloaded(pEntity, pOther);
		break;
	case EVENT_BEING_SHOT_AT:
		HandleBeingShotAt(pEntity, pOther);
		break;
	case EVENT_PLAYER_BLINDED_BY_FLASHBANG:
		HandlePlayerBlindedByFlashbang(pEntity, pOther);
		break;
	case EVENT_PLAYER_DIED:
		HandlePlayerDied(pEntity, pOther);
		break;
	case EVENT_PLAYER_TOOK_DAMAGE:
		HandlePlayerTookDamage(pEntity, pOther);
		break;
	case EVENT_HOSTAGE_DAMAGED:
		HandleHostageDamaged(pEntity, pOther);
		break;
	case EVENT_HOSTAGE_KILLED:
		HandleHostageKilled(pEntity, pOther);
		break;
	case EVENT_BOMB_PLANTED:
		HandleBombPlanted(pEntity, pOther);
		break;
	case EVENT_BOMB_DEFUSING:
		HandleBombDefusing(pEntity, pOther);
		break;
	case EVENT_BOMB_DEFUSED:
		HandleBombDefused(pEntity, pOther);
		break;
	case EVENT_BOMB_EXPLODED:
		HandleBombExploded(pEntity, pOther);
		break;
	case EVENT_HOSTAGE_USED:
		HandleHostageUsed(pEntity, pOther);
		break;
	case EVENT_HOSTAGE_RESCUED:
		HandleHostageRescued(pEntity, pOther);
		break;
	case EVENT_ALL_HOSTAGES_RESCUED:
		HandleAllHostagesRescued(pEntity, pOther);
		break;
	case EVENT_TERRORISTS_WIN:
		HandleTWin(pEntity, pOther);
		break;
	case EVENT_CTS_WIN:
		HandleCTWin(pEntity, pOther);
		break;
	case EVENT_ROUND_DRAW:
		HandleRoundDraw(pEntity, pOther);
		break;
	case EVENT_ROUND_START:
		HandleRoundStart(pEntity, pOther);
		break;
	case EVENT_PLAYER_SPAWNED:
		HandlePlayerSpawned(pEntity, pOther);
		break;
	case EVENT_PLAYER_LEFT_BUY_ZONE:
		HandlePlayerLeftBuyZone(pEntity, pOther);
		break;
	case EVENT_DEATH_CAMERA_START:
		HandleDeathCameraStart(pEntity, pOther);
		break;
	case EVENT_TUTOR_BUY_MENU_OPENNED:
		HandleBuyMenuOpenned(pEntity, pOther);
		break;
	case EVENT_TUTOR_AUTOBUY:
		HandleAutoBuy(pEntity, pOther);
		break;
	case EVENT_TUTOR_NOT_BUYING_ANYTHING:
		HandleNotBuyingAnything(pEntity, pOther);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_PRIMARY_WEAPON:
		HandleNeedToBuyPrimaryWeapon(pEntity, pOther);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_PRIMARY_AMMO:
		HandleNeedToBuyPrimaryAmmo(pEntity, pOther);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_SECONDARY_AMMO:
		HandleNeedToBuySecondaryAmmo(pEntity, pOther);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_ARMOR:
		HandleNeedToBuyArmor(pEntity, pOther);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_DEFUSE_KIT:
		HandleNeedToBuyDefuseKit(pEntity, pOther);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_GRENADE:
		HandleNeedToBuyGrenade(pEntity, pOther);
		break;
	case EVENT_CAREER_TASK_DONE:
		HandleCareerTaskDone(pEntity, pOther);
		break;
	case EVENT_RADIO_COVER_ME:
		HandleRadioCoverMe(pEntity, pOther);
		break;
	case EVENT_RADIO_YOU_TAKE_THE_POINT:
		HandleRadioYouTakeThePoint(pEntity, pOther);
		break;
	case EVENT_RADIO_HOLD_THIS_POSITION:
		HandleRadioHoldThisPosition(pEntity, pOther);
		break;
	case EVENT_RADIO_REGROUP_TEAM:
		HandleRadioRegroupTeam(pEntity, pOther);
		break;
	case EVENT_RADIO_FOLLOW_ME:
		HandleRadioFollowMe(pEntity, pOther);
		break;
	case EVENT_RADIO_TAKING_FIRE:
		HandleRadioTakingFire(pEntity, pOther);
		break;
	case EVENT_RADIO_GO_GO_GO:
		HandleRadioGoGoGo(pEntity, pOther);
		break;
	case EVENT_RADIO_TEAM_FALL_BACK:
		HandleRadioTeamFallBack(pEntity, pOther);
		break;
	case EVENT_RADIO_STICK_TOGETHER_TEAM:
		HandleRadioStickTogetherTeam(pEntity, pOther);
		break;
	case EVENT_RADIO_GET_IN_POSITION_AND_WAIT:
		HandleRadioGetInPositionAndWait(pEntity, pOther);
		break;
	case EVENT_RADIO_STORM_THE_FRONT:
		HandleRadioStormTheFront(pEntity, pOther);
		break;
	case EVENT_RADIO_REPORT_IN_TEAM:
		HandleRadioReportInTeam(pEntity, pOther);
		break;
	case EVENT_RADIO_AFFIRMATIVE:
		HandleRadioAffirmative(pEntity, pOther);
		break;
	case EVENT_RADIO_ENEMY_SPOTTED:
		HandleRadioEnemySpotted(pEntity, pOther);
		break;
	case EVENT_RADIO_NEED_BACKUP:
		HandleRadioNeedBackup(pEntity, pOther);
		break;
	case EVENT_RADIO_SECTOR_CLEAR:
		HandleRadioSectorClear(pEntity, pOther);
		break;
	case EVENT_RADIO_IN_POSITION:
		HandleRadioInPosition(pEntity, pOther);
		break;
	case EVENT_RADIO_REPORTING_IN:
		HandleRadioReportingIn(pEntity, pOther);
		break;
	case EVENT_RADIO_GET_OUT_OF_THERE:
		HandleRadioGetOutOfThere(pEntity, pOther);
		break;
	case EVENT_RADIO_NEGATIVE:
		HandleRadioNegative(pEntity, pOther);
		break;
	case EVENT_RADIO_ENEMY_DOWN:
		HandleRadioEnemyDown(pEntity, pOther);
		break;
	default:
		break;
	}
}

void CCSTutor::HandleWeaponFired(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer || !pLocalPlayer->IsAlive())
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer == pLocalPlayer)
	{
		CheckForNeedToReload();
	}
}

void CCSTutor::HandleWeaponFiredOnEmpty(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer)
	{
		CBasePlayerWeapon *pCurrentWeapon = static_cast<CBasePlayerWeapon *>(pPlayer->m_pActiveItem);
		if (pCurrentWeapon && pPlayer->m_rgAmmo[pCurrentWeapon->m_iPrimaryAmmoType] <= 0)
		{
			TutorMessage *message = GetTutorMessageDefinition(YOU_ARE_OUT_OF_AMMO);
			if (message)
			{
				message->m_lastCloseTime = 0;
			}

			CreateAndAddEventToList(YOU_ARE_OUT_OF_AMMO);
		}
	}
}

void CCSTutor::HandleWeaponReloaded(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer->IsPlayer() && pPlayer == UTIL_GetLocalPlayer())
	{
		CancelEvent(YOU_SHOULD_RELOAD);
	}
}

void CCSTutor::HandlePlayerDied(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pVictim = static_cast<CBasePlayer *>(pEntity);
	CBasePlayer *pAttacker = static_cast<CBasePlayer *>(pOther);

	if (pVictim && !pVictim->IsPlayer())
	{
		pVictim = nullptr;
	}

	if (pAttacker && !pAttacker->IsPlayer())
	{
		pAttacker = nullptr;
	}

	if (pVictim == pLocalPlayer && !pAttacker)
	{
		if (pLocalPlayer->m_bKilledByBomb)
		{
			CreateAndAddEventToList(YOU_DIED, pEntity, pOther);
		}
		else
		{
			CreateAndAddEventToList(YOU_FELL_TO_YOUR_DEATH);
		}
	}

	if (!pVictim || !pAttacker)
		return;

	if (pVictim == pAttacker && pVictim == pLocalPlayer)
	{
		CreateAndAddEventToList(YOU_DIED, pEntity, pOther);
		return;
	}

	int numT, numCT;
	GetNumPlayersAliveOnTeams(numT, numCT);

	if (pAttacker == pLocalPlayer)
	{
		if (pVictim->m_iTeam == pAttacker->m_iTeam)
		{
			CreateAndAddEventToList(YOU_KILLED_A_TEAMMATE, pEntity, pOther);
			return;
		}

		if (pVictim->m_bHeadshotKilled)
		{
			switch (pAttacker->m_iTeam)
			{
			case CT:
			{
				switch (numT)
				{
				case 0: CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY_HEADSHOT, pEntity, pOther); break;
				case 1: CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT, pEntity, pOther); break;
				default: CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT, pEntity, pOther); break;
				}
				break;
			}
			case TERRORIST:
			{
				switch (numCT)
				{
				case 0: CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY_HEADSHOT, pEntity, pOther); break;
				case 1: CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT, pEntity, pOther); break;
				default: CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT, pEntity, pOther); break;
				}
				break;
			}
			}
		}
		else
		{
			switch (pAttacker->m_iTeam)
			{
			case CT:
			{
				switch (numT)
				{
				case 0: CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY, pEntity, pOther); break;
				case 1: CreateAndAddEventToList(YOU_KILLED_PLAYER_ONE_LEFT, pEntity, pOther); break;
				default: CreateAndAddEventToList(YOU_KILLED_PLAYER, pEntity, pOther); break;
				}
				break;
			}
			case TERRORIST:
			{
				switch (numCT)
				{
				case 0: CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY, pEntity, pOther); break;
				case 1: CreateAndAddEventToList(YOU_KILLED_PLAYER_ONE_LEFT, pEntity, pOther); break;
				default: CreateAndAddEventToList(YOU_KILLED_PLAYER, pEntity, pOther); break;
				}
				break;
			}
			}
		}
	}
	else if (pVictim == pLocalPlayer)
	{
		CreateAndAddEventToList(pVictim->m_bHeadshotKilled ? YOU_DIED_HEADSHOT : YOU_DIED, pEntity, pOther);
	}
	else if (pVictim->m_iTeam == pLocalPlayer->m_iTeam)
	{
		switch (pVictim->m_iTeam)
		{
		case CT:
		{
			if (pLocalPlayer->IsAlive())
			{
				if (numCT == 1)
				{
					CreateAndAddEventToList(LAST_TEAMMATE_KILLED, pEntity, pOther);
				}
				else if (numCT == 2)
				{
					CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, pEntity, pOther);
				}
				else
				{
					CreateAndAddEventToList(TEAMMATE_KILLED, pEntity, pOther);
				}
			}
			else
			{
				if (numCT == 1)
				{
					CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, pEntity, pOther);
				}
				else if (numCT > 1)
				{
					CreateAndAddEventToList(TEAMMATE_KILLED, pEntity, pOther);
				}
			}
			break;
		}
		case TERRORIST:
		{
			if (pLocalPlayer->IsAlive())
			{
				if (numT == 1)
				{
					CreateAndAddEventToList(LAST_TEAMMATE_KILLED, pEntity, pOther);
				}
				else if (numT == 2)
				{
					CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, pEntity, pOther);
				}
				else
				{
					CreateAndAddEventToList(TEAMMATE_KILLED, pEntity, pOther);
				}
			}
			else
			{
				if (numT == 1)
				{
					CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, pEntity, pOther);
				}
				else if (numT > 1)
				{
					CreateAndAddEventToList(TEAMMATE_KILLED, pEntity, pOther);
				}
			}
			break;
		}
		}
	}
	else
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
		{
			switch (numT)
			{
			case 0: CreateAndAddEventToList(LAST_ENEMY_KILLED, pEntity, pOther); break;
			case 1: CreateAndAddEventToList(ENEMY_KILLED_ONE_LEFT, pEntity, pOther); break;
			default: CreateAndAddEventToList(ENEMY_KILLED, pEntity, pOther); break;
			}
			break;
		}
		case TERRORIST:
		{
			switch (numCT)
			{
			case 0: CreateAndAddEventToList(LAST_ENEMY_KILLED, pEntity, pOther); break;
			case 1: CreateAndAddEventToList(ENEMY_KILLED_ONE_LEFT, pEntity, pOther); break;
			default: CreateAndAddEventToList(ENEMY_KILLED, pEntity, pOther); break;
			}
			break;
		}
		}
	}
}

void CCSTutor::HandlePlayerTookDamage(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pVictim = static_cast<CBasePlayer *>(pEntity);
	CBasePlayer *pAttacker = static_cast<CBasePlayer *>(pOther);

	if (pVictim && !pVictim->IsPlayer())
	{
		pVictim = nullptr;
	}

	if (pAttacker && !pAttacker->IsPlayer())
	{
		pAttacker = nullptr;
	}

	if (pVictim && pVictim == pLocalPlayer)
	{
		CreateAndAddEventToList(YOU_WERE_JUST_HURT);
	}
	else if (pAttacker && pVictim && pAttacker == pLocalPlayer && pVictim->m_iTeam == pLocalPlayer->m_iTeam)
	{
		CreateAndAddEventToList(YOU_ATTACKED_TEAMMATE);
	}
}

void CCSTutor::HandlePlayerBlindedByFlashbang(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer)
	{
		CreateAndAddEventToList(YOU_ARE_BLIND_FROM_FLASHBANG);
	}
}

void CCSTutor::HandlePlayerSpawned(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (!pPlayer || !pPlayer->IsPlayer() || pPlayer != UTIL_GetLocalPlayer())
		return;

	m_haveSpawned = true;
	m_lastInGameHintShown = INGAME_HINT_BEGIN;
	CreateAndAddEventToList(YOU_SPAWNED, pEntity, pOther);
}

NOXREF void CCSTutor::HandleClientCorpseSpawned(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (!pPlayer || !pPlayer->IsPlayer())
		return;

	ClientCorpseStruct *corpse = new ClientCorpseStruct;

	corpse->m_position = pPlayer->pev->origin;
	corpse->m_team = pPlayer->m_iTeam;

	m_clientCorpseList.push_back(corpse);
}

void CCSTutor::HandleBuyMenuOpenned(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (m_currentlyShownMessageID == BUY_TIME_BEGIN)
	{
		ClearCurrentEvent();
		CheckBuyZoneMessages();
	}
}

void CCSTutor::HandleAutoBuy(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (m_currentlyShownMessageID == BUY_TIME_BEGIN)
	{
		ClearCurrentEvent();
	}
}

NOXREF void CCSTutor::HandleBuyTimeStart(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	;
}

void CCSTutor::HandlePlayerLeftBuyZone(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	m_messageTypeMask = (TUTORMESSAGETYPE_DEFAULT | TUTORMESSAGETYPE_FRIEND_DEATH | TUTORMESSAGETYPE_ENEMY_DEATH | TUTORMESSAGETYPE_SCENARIO | TUTORMESSAGETYPE_CAREER | TUTORMESSAGETYPE_INGAME_HINT | TUTORMESSAGETYPE_END_GAME);

	ClearEventList();
	ClearCurrentEvent();

	if (m_lastScenarioEvent)
	{
		m_lastScenarioEvent->SetActivationTime(gpGlobals->time);
		AddToEventList(m_lastScenarioEvent);
		m_lastScenarioEvent = nullptr;
	}
}

void CCSTutor::HandleBombPlanted(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	if (pLocalPlayer->IsAlive() && pLocalPlayer->m_iTeam == CT)
	{
		CreateAndAddEventToList(BOMB_PLANTED_CT, pEntity, pOther);
	}
	else
	{
		CreateAndAddEventToList(BOMB_PLANTED_T, pEntity, pOther);
	}
}

void CCSTutor::HandleBombDefused(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pDefuser = static_cast<CBasePlayer *>(pEntity);
	if (pDefuser && pDefuser->IsPlayer() && pDefuser == pLocalPlayer)
	{
		CreateAndAddEventToList(YOU_DEFUSED_BOMB);
		return;
	}

	switch (pLocalPlayer->m_iTeam)
	{
	case CT:        CreateAndAddEventToList(BOMB_DEFUSED_CT); break;
	case TERRORIST: CreateAndAddEventToList(BOMB_DEFUSED_T); break;
	default:        CreateAndAddEventToList(ROUND_OVER); break;
	}
}

void CCSTutor::HandleBombDefusing(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer && !pPlayer->m_bHasDefuser)
	{
		CreateAndAddEventToList(DEFUSING_WITHOUT_KIT);
	}
}

void CCSTutor::HandleBombExploded(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	switch (pLocalPlayer->m_iTeam)
	{
	case CT:        CreateAndAddEventToList(BOMB_EXPLODED_CT); break;
	case TERRORIST: CreateAndAddEventToList(BOMB_EXPLODED_T); break;
	default: break;
	}
}

void CCSTutor::HandleRoundStart(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();

	m_roundStartTime = gpGlobals->time;
	if (!pLocalPlayer)
		return;

	if (IsBombMap())
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
			CreateAndAddEventToList(ROUND_START_DE_CT);
			break;
		case TERRORIST:
		{
			if (pLocalPlayer->m_bHasC4)
				CreateAndAddEventToList(YOU_ARE_BOMB_CARRIER, pEntity, pOther);
			else
				CreateAndAddEventToList(ROUND_START_DE_T);
			break;
		}
		}
	}
	else if (IsHostageMap())
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:        CreateAndAddEventToList(ROUND_START_CS_CT); break;
		case TERRORIST: CreateAndAddEventToList(ROUND_START_CS_T); break;
		}
	}
}

void CCSTutor::HandleBeingShotAt(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer && pLocalPlayer->IsAlive())
	{
		CreateAndAddEventToList(YOU_HAVE_BEEN_SHOT_AT, pEntity, pOther);
	}
}

void CCSTutor::HandleHostageUsed(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pActivator = static_cast<CBasePlayer *>(pEntity);
	if (pActivator && pActivator->IsPlayer())
	{
		bool unusedHostages = !CheckForAllHostagesFollowingSomeone();
		if (pActivator == pLocalPlayer)
		{
			CreateAndAddEventToList(unusedHostages ? YOU_USED_HOSTAGE_MORE_LEFT : YOU_USED_HOSTAGE_NO_MORE_LEFT);
		}
		else if (!unusedHostages)
		{
			switch (pLocalPlayer->m_iTeam)
			{
			case CT:        CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_CT); break;
			case TERRORIST: CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_T); break;
			}
		}
	}
}

void CCSTutor::HandleHostageRescued(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pRescuer = static_cast<CBasePlayer *>(pEntity);
	if (pRescuer && pRescuer->IsPlayer())
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:        CreateAndAddEventToList((pLocalPlayer == pRescuer) ? YOU_RESCUED_HOSTAGE : HOSTAGE_RESCUED_CT); break;
		case TERRORIST: CreateAndAddEventToList(HOSTAGE_RESCUED_T); break;
		}
	}
}

void CCSTutor::HandleAllHostagesRescued(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	switch (pLocalPlayer->m_iTeam)
	{
	case CT:        CreateAndAddEventToList(ALL_HOSTAGES_RESCUED_CT); break;
	case TERRORIST: CreateAndAddEventToList(ALL_HOSTAGES_RESCUED_T); break;
	}
}

void CCSTutor::HandleHostageDamaged(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pAttacker = static_cast<CBasePlayer *>(pOther);
	if (pEntity && pAttacker && pAttacker->IsPlayer() && pLocalPlayer == pAttacker)
	{
		CreateAndAddEventToList(YOU_DAMAGED_HOSTAGE);
	}
}

void CCSTutor::HandleHostageKilled(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CheckForAllHostagesDead();

	CBasePlayer *pAttacker = static_cast<CBasePlayer *>(pOther);
	if (pEntity && pAttacker && pAttacker->IsPlayer())
	{
		bool unusedHostages = CheckForAllHostagesFollowingSomeone();
		if (pLocalPlayer == pAttacker)
		{
			CreateAndAddEventToList(YOU_KILLED_HOSTAGE);
		}

		if (unusedHostages)
		{
			switch (pLocalPlayer->m_iTeam)
			{
			case CT:        CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_CT); break;
			case TERRORIST: CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_T); break;
			}
		}
	}
}

void CCSTutor::HandleRoundDraw(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (CSGameRules()->m_iTotalRoundsPlayed)
	{
		CreateAndAddEventToList(ROUND_DRAW);
	}

	ResetPlayerDeathInfo();
}

void CCSTutor::HandleCTWin(CBaseEntity *entith, CBaseEntity *pOther)
{
	CreateAndAddEventToList(CT_WIN);
	ResetPlayerDeathInfo();
}

void CCSTutor::HandleTWin(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(T_WIN);
	ResetPlayerDeathInfo();
}

void CCSTutor::HandleDeathCameraStart(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
	if (pPlayer && pPlayer->IsPlayer() && pPlayer == pLocalPlayer)
	{
		m_messageTypeMask = (TUTORMESSAGETYPE_FRIEND_DEATH | TUTORMESSAGETYPE_ENEMY_DEATH | TUTORMESSAGETYPE_HINT | TUTORMESSAGETYPE_END_GAME);
		CreateAndAddEventToList(DEATH_CAMERA_START);
	}
}

void CCSTutor::HandleRadioCoverMe(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_COVER_ME, pEntity, pOther);
}

void CCSTutor::HandleRadioYouTakeThePoint(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_YOU_TAKE_THE_POINT, pEntity, pOther);
}

void CCSTutor::HandleRadioHoldThisPosition(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_HOLD_THIS_POSITION, pEntity, pOther);
}

void CCSTutor::HandleRadioRegroupTeam(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_REGROUP_TEAM, pEntity, pOther);
}

void CCSTutor::HandleRadioFollowMe(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_FOLLOW_ME, pEntity, pOther);
}

void CCSTutor::HandleRadioTakingFire(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_TAKING_FIRE, pEntity, pOther);
}

void CCSTutor::HandleRadioGoGoGo(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_GO_GO_GO, pEntity, pOther);
}

void CCSTutor::HandleRadioTeamFallBack(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_TEAM_FALL_BACK, pEntity, pOther);
}

void CCSTutor::HandleRadioStickTogetherTeam(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_STICK_TOGETHER_TEAM, pEntity, pOther);
}

void CCSTutor::HandleRadioGetInPositionAndWait(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_GET_IN_POSITION_AND_WAIT, pEntity, pOther);
}

void CCSTutor::HandleRadioStormTheFront(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_STORM_THE_FRONT, pEntity, pOther);
}

void CCSTutor::HandleRadioReportInTeam(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_REPORT_IN_TEAM, pEntity, pOther);
}

void CCSTutor::HandleRadioAffirmative(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_AFFIRMATIVE, pEntity, pOther);
}

void CCSTutor::HandleRadioEnemySpotted(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_ENEMY_SPOTTED, pEntity, pOther);
}

void CCSTutor::HandleRadioNeedBackup(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_NEED_BACKUP, pEntity, pOther);
}

void CCSTutor::HandleRadioSectorClear(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_SECTOR_CLEAR, pEntity, pOther);
}

void CCSTutor::HandleRadioInPosition(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_IN_POSITION, pEntity, pOther);
}

void CCSTutor::HandleRadioReportingIn(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_REPORTING_IN, pEntity, pOther);
}

void CCSTutor::HandleRadioGetOutOfThere(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_GET_OUT_OF_THERE, pEntity, pOther);
}

void CCSTutor::HandleRadioNegative(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_NEGATIVE, pEntity, pOther);
}

void CCSTutor::HandleRadioEnemyDown(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(RADIO_ENEMY_DOWN, pEntity, pOther);
}

void CCSTutor::HandleNotBuyingAnything(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_TIME_BEGIN, pEntity, pOther);
}

void CCSTutor::HandleNeedToBuyPrimaryWeapon(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_NEED_PRIMARY, pEntity, pOther);
}

void CCSTutor::HandleNeedToBuyPrimaryAmmo(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_NEED_PRIMARY_AMMO, pEntity, pOther);
}

void CCSTutor::HandleNeedToBuySecondaryAmmo(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_NEED_SECONDARY_AMMO, pEntity, pOther);
}

void CCSTutor::HandleNeedToBuyArmor(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_NEED_ARMOR, pEntity, pOther);
}

void CCSTutor::HandleNeedToBuyDefuseKit(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_NEED_DEFUSE_KIT, pEntity, pOther);
}

void CCSTutor::HandleNeedToBuyGrenade(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CreateAndAddEventToList(BUY_NEED_GRENADE, pEntity, pOther);
}

void CCSTutor::HandleCareerTaskDone(CBaseEntity *pEntity, CBaseEntity *pOther)
{
	int numTasksRemaining = 0;

	if (TheCareerTasks && (numTasksRemaining = TheCareerTasks->GetNumRemainingTasks()) > 0)
		CreateAndAddEventToList((numTasksRemaining == 1) ? CAREER_TASK_DONE_ONE_LEFT : CAREER_TASK_DONE_MORE_LEFT);
	else
		CreateAndAddEventToList(CAREER_TASK_DONE_ALL_DONE);
}

void CCSTutor::HandleShotFired(Vector source, Vector target)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	float d1, d, angle, flFiringLineDistanceToPlayer;

	d1 = (source - pLocalPlayer->pev->origin).Length();

	if (d1 > 32.0f)
	{
		d = (target - source).Length();
		angle = d1 / d;

		flFiringLineDistanceToPlayer = Q_sin(Q_acos(angle)) * d1;

		if (flFiringLineDistanceToPlayer <= 3000.0f)
		{
			OnEvent(EVENT_BEING_SHOT_AT, pLocalPlayer);
		}
	}
}

void CCSTutor::GetNumPlayersAliveOnTeams(int &numT, int &numCT)
{
	numT = numCT = 0;

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);
		if (!pPlayer || !pPlayer->IsAlive())
			continue;

		switch (pPlayer->m_iTeam)
		{
		case CT:        numCT++; break;
		case TERRORIST: numT++;  break;
		}
	}
}

void CCSTutor::CheckForLooseWeaponViewable()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_LOOSE_WEAPON);
	if (message && message->m_class == TUTORMESSAGECLASS_EXAMINE)
		return;

	CBaseEntity *weapon = nullptr;
	while ((weapon = UTIL_FindEntityByClassname(weapon, "weaponbox")))
	{
		if (IsEntityInViewOfPlayer(weapon, pLocalPlayer))
		{
			CreateAndAddEventToList(YOU_SEE_LOOSE_WEAPON);
			break;
		}
	}
}

void CCSTutor::CheckForLooseDefuserViewable()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer || pLocalPlayer->m_iTeam != CT)
		return;

	TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_LOOSE_DEFUSER);
	if (message && message->m_class == TUTORMESSAGECLASS_EXAMINE)
		return;

	CBaseEntity *pDefuser = nullptr;
	while ((pDefuser = UTIL_FindEntityByClassname(pDefuser, "item_thighpack")))
	{
		if (IsEntityInViewOfPlayer(pDefuser, pLocalPlayer))
		{
			CreateAndAddEventToList(YOU_SEE_LOOSE_DEFUSER);
			break;
		}
	}
}

void CCSTutor::CheckForBombViewable()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CGrenade *pBomb = (CGrenade *)UTIL_FindEntityByClassname(nullptr, "grenade");
	if (pBomb && pBomb->m_bIsC4 && IsEntityInViewOfPlayer(pBomb, pLocalPlayer))
	{
		TutorMessageID mid = TUTOR_NUM_MESSAGES;
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
		{
			mid = YOU_SEE_PLANTED_BOMB_CT;
			break;
		}
		case TERRORIST:
		{
			mid = YOU_SEE_PLANTED_BOMB_T;
			break;
		}
		}

		if (mid != TUTOR_NUM_MESSAGES)
		{
			TutorMessage *message = GetTutorMessageDefinition(mid);
			if (!message || message->m_class != TUTORMESSAGECLASS_EXAMINE)
			{
				CreateAndAddEventToList(mid);
			}
		}
	}
	else
	{
		CBasePlayer *pBombCarrier = nullptr;
		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);
			if (pPlayer && pPlayer->m_bHasC4)
			{
				pBombCarrier = pPlayer;
				break;
			}
		}

		CBaseEntity *pC4 = UTIL_FindEntityByClassname(nullptr, "weapon_c4");
		if (pC4 && IsEntityInViewOfPlayer(pC4, pLocalPlayer))
		{
			if (pBombCarrier)
			{
				if (pBombCarrier != pLocalPlayer)
				{
					switch (pLocalPlayer->m_iTeam)
					{
					case CT:
					{
						TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_BOMB_CARRIER_CT);
						if (!message || message->m_class != TUTORMESSAGECLASS_EXAMINE)
						{
							CreateAndAddEventToList(YOU_SEE_BOMB_CARRIER_CT);
						}
						break;
					}
					case TERRORIST:
					{
						TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_BOMB_CARRIER_T);
						if (!message || message->m_class != TUTORMESSAGECLASS_EXAMINE)
						{
							CreateAndAddEventToList(YOU_SEE_BOMB_CARRIER_T);
						}
						break;
					}
					}
				}
			}
			else
			{
				TutorMessageID mid = TUTOR_NUM_MESSAGES;
				switch (pLocalPlayer->m_iTeam)
				{
				case CT:
				{
					mid = YOU_SEE_LOOSE_BOMB_CT;
					break;
				}
				case TERRORIST:
				{
					mid = YOU_SEE_LOOSE_BOMB_T;
					break;
				}
				}

				if (mid != TUTOR_NUM_MESSAGES)
				{
					TutorMessage *message = GetTutorMessageDefinition(mid);
					if (!message || message->m_class != TUTORMESSAGECLASS_EXAMINE)
					{
						CreateAndAddEventToList(mid);
					}
				}
			}
		}
	}
}

void CCSTutor::CheckForBombsiteViewable()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	TutorMessageID mid = CheckForInBombZone();
	if (mid != TUTOR_NUM_MESSAGES)
	{
		CreateAndAddEventToList(mid);
		return;
	}

	switch (pLocalPlayer->m_iTeam)
	{
	case CT:
	{
		mid = YOU_SEE_BOMBSITE_CT;
		break;
	}
	case TERRORIST:
	{
		if (pLocalPlayer->m_bHasC4)
		{
			mid = YOU_SEE_BOMBSITE_T_BOMB;
		}
		else if (!TheCSBots() || !TheCSBots()->IsBombPlanted())
		{
			mid = YOU_SEE_BOMBSITE_T;
		}
		break;
	}
	}

	TutorMessage *definition = GetTutorMessageDefinition(mid);
	if (!definition || definition->m_class != TUTORMESSAGECLASS_EXAMINE)
	{
		if (IsBombPlantedInBombZone("func_bomb_target")
			|| IsBombPlantedInBombZone("info_bomb_target"))
		{
			CreateAndAddEventToList(mid);
			return;
		}
	}
}

TutorMessageID CCSTutor::CheckForInBombZone()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer && pLocalPlayer->m_iTeam == CT)
	{
		if (IsBombPlantedInBombZone("func_bomb_target")
			|| IsBombPlantedInBombZone("info_bomb_target"))
		{
			return YOU_SEE_PLANTED_BOMB_CT;
		}
	}

	return TUTOR_NUM_MESSAGES;
}

bool CCSTutor::IsBombPlantedInBombsite(CBaseEntity *bombTarget)
{
	CGrenade *pBomb = nullptr;
	while ((pBomb = UTIL_FindEntityByClassname(pBomb, "grenade")))
	{
		if (pBomb->m_bIsC4 && IsEntityInBombsite(pBomb, bombTarget))
		{
			return true;
		}
	}

	return false;
}

bool CCSTutor::IsBombPlantedInBombZone(const char *pszBombZone)
{
	CBaseEntity *bombSite = nullptr;
	while ((bombSite = UTIL_FindEntityByClassname(bombSite, pszBombZone)))
	{
		if (IsBombPlantedInBombsite(bombSite))
		{
			return true;
		}
	}

	return false;
}

void CCSTutor::CheckForHostageViewable()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	CBaseEntity *pHostageEntity = nullptr;
	while ((pHostageEntity = UTIL_FindEntityByClassname(pHostageEntity, "hostage_entity")))
	{
		bool bValidHostage = false;
		CHostage *pHostage = static_cast<CHostage *>(pHostageEntity);

		if (pHostage->IsAlive())
		{
			if (!pHostage->IsFollowingSomeone())
			{
				bValidHostage = true;
			}
		}

		if (bValidHostage && IsEntityInViewOfPlayer(pHostage, pLocalPlayer))
		{
			TutorMessageID mid = TUTOR_NUM_MESSAGES;
			switch (pLocalPlayer->m_iTeam)
			{
			case CT:
			{
				mid = YOU_SEE_HOSTAGE_CT;
				break;
			}
			case TERRORIST:
			{
				mid = YOU_SEE_HOSTAGE_T;
				break;
			}
			}

			if (mid != TUTOR_NUM_MESSAGES)
			{
				TutorMessage *message = GetTutorMessageDefinition(mid);
				if (!message || message->m_class != TUTORMESSAGECLASS_EXAMINE)
				{
					CreateAndAddEventToList(mid);
				}
			}

			break;
		}
	}
}

void CCSTutor::CheckForTimeRunningOut()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer || CSGameRules()->IsFreezePeriod() || CSGameRules()->GetRoundRemainingTime() > 30.0f)
		return;

	if (IsBombMap())
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
			CreateAndAddEventToList(TIME_RUNNING_OUT_DE_CT);
			break;
		case TERRORIST:
			CreateAndAddEventToList(TIME_RUNNING_OUT_DE_T);
			break;
		}
	}
	else if (IsHostageMap())
	{
		switch (pLocalPlayer->m_iTeam)
		{
		case CT:
			CreateAndAddEventToList(TIME_RUNNING_OUT_CS_CT);
			break;
		case TERRORIST:
			CreateAndAddEventToList(TIME_RUNNING_OUT_CS_T);
			break;
		}
	}
}

void CCSTutor::CheckForAllHostagesDead()
{
	bool foundLiveOne = false;
	CHostage *pHostage = nullptr;

	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		if (pHostage->IsAlive())
		{
			foundLiveOne = true;
			break;
		}
	}

	if (!foundLiveOne)
	{
		CreateAndAddEventToList(ALL_HOSTAGES_DEAD);
	}
}

bool CCSTutor::CheckForAllHostagesFollowingSomeone()
{
	bool foundUnusedOne = false;
	CHostage *pHostage = nullptr;

	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		if (pHostage->IsAlive())
		{
			if (!pHostage->IsFollowingSomeone())
			{
				foundUnusedOne = true;
				break;
			}
		}
	}

	return foundUnusedOne ? false : true;
}

TutorMessage *CCSTutor::GetTutorMessageDefinition(int messageID)
{
	if (messageID < 0 || messageID >= TUTOR_NUM_MESSAGES)
		return nullptr;

	TutorMessageMapIter iter = m_messageMap.find(m_TutorIdentifierList[messageID]);
	if (iter != m_messageMap.end())
	{
		return (*iter).second;
	}

	return nullptr;
}

CBaseEntity *CCSTutor::GetEntityForMessageID(int messageID, CBaseEntity *last)
{
	CBaseEntity *pEntity = nullptr;

	switch (messageID)
	{
		case YOU_SEE_FRIEND:
		case YOU_SEE_ENEMY:
			pEntity = UTIL_FindEntityByClassname(last, "player");
			break;
		case YOU_SEE_FRIEND_CORPSE:
		{
			// TODO: this code is noxref
			// this code fucked my brain, in that pointer Vector * is passed through the CBaseEntity *

#if 1
			CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
			if (pLocalPlayer)
			{
				if (m_clientCorpseList.empty())
					return nullptr;

				ClientCorpseStruct *lastCorpse = nullptr;
				ClientCorpseListIter iter;

				if (last)
				{
					iter = m_clientCorpseList.begin();

					while (iter != m_clientCorpseList.end())
					{
						lastCorpse = (*iter);

						if ((CBaseEntity *)lastCorpse == last)
							break;

						iter++;
					}

					while (iter != m_clientCorpseList.end())
					{
						ClientCorpseStruct *corpse = (*iter);

						if (corpse->m_team == pLocalPlayer->m_iTeam)
							return (CBaseEntity *)&corpse->m_position;

						iter++;
					}

					return nullptr;
				}
				else
					return (CBaseEntity *)&m_clientCorpseList.front()->m_position;
			}
#endif
			break;
		}
		case YOU_SEE_LOOSE_BOMB_T:
		case YOU_SEE_LOOSE_BOMB_CT:
		case YOU_SEE_BOMB_CARRIER_T:
		case YOU_SEE_BOMB_CARRIER_CT:
			pEntity = UTIL_FindEntityByClassname(last, "weapon_c4");
			break;
		case YOU_SEE_PLANTED_BOMB_T:
		case YOU_SEE_PLANTED_BOMB_CT:
			pEntity = UTIL_FindEntityByClassname(last, "grenade");
			break;
		case YOU_SEE_LOOSE_WEAPON:
			pEntity = UTIL_FindEntityByClassname(last, "weaponbox");
			break;
		case YOU_SEE_LOOSE_DEFUSER:
			pEntity = UTIL_FindEntityByClassname(last, "item_thighpack");
			break;
		case YOU_SEE_HOSTAGE_T:
		case YOU_SEE_HOSTAGE_CT:
		case YOU_SEE_HOSTAGE_CT_EXAMINE:
			pEntity = UTIL_FindEntityByClassname(last, "hostage_entity");
			break;
	}

	return pEntity;
}

void CCSTutor::CheckHintMessages(float time)
{
	if (m_deadAirStartTime <= 0.0f || (time - m_deadAirStartTime <= cv_tutor_hint_interval_time.value))
		return;

	m_lastHintShown++;

	while (true)
	{
		bool confusingHint = false;
		if (IsHostageMap())
		{
			if (m_lastHintShown >= HINT_BOMB_START && m_lastHintShown <= HINT_BOMB_END)
			{
				confusingHint = true;
			}
		}
		else if (IsBombMap())
		{
			if (m_lastHintShown >= HINT_HOSTAGE_START && m_lastHintShown <= HINT_HOSTAGE_END)
			{
				confusingHint = true;
			}
		}

		if (!confusingHint)
		{
			break;
		}

		m_lastHintShown++;

		if (m_lastHintShown <= HINT_BEGIN || m_lastHintShown >= HINT_END)
		{
			m_lastHintShown = HINT_1;
		}
	}

	if (m_lastHintShown <= HINT_BEGIN || m_lastHintShown >= HINT_END)
	{
		m_lastHintShown = HINT_1;
	}

	TutorMessage *message = GetTutorMessageDefinition(m_lastHintShown);
	if (message)
	{
		CreateAndAddEventToList(m_lastHintShown);
	}
}

void CCSTutor::CheckInGameHintMessages(float time)
{
	if (m_deadAirStartTime <= 0.0f || (time - m_deadAirStartTime <= cv_tutor_hint_interval_time.value))
		return;

	m_lastInGameHintShown++;

	if (m_lastInGameHintShown <= INGAME_HINT_BEGIN || m_lastInGameHintShown >= INGAME_HINT_END)
		return;

	TutorMessage *message = GetTutorMessageDefinition(m_lastInGameHintShown);
	if (message)
	{
		CreateAndAddEventToList(m_lastInGameHintShown);
	}
}

void CCSTutor::CheckForNeedToReload(bool isPassiveCheck)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer || !pLocalPlayer->IsPlayer())
		return;

	CBasePlayerWeapon *pCurrentWeapon = static_cast<CBasePlayerWeapon *>(pLocalPlayer->m_pActiveItem);
	if (!pCurrentWeapon || !pCurrentWeapon->IsWeapon())
		return;

	ItemInfo itemInfo;
	Q_memset(&itemInfo, 0, sizeof(itemInfo));
	pCurrentWeapon->GetItemInfo(&itemInfo);

	if (itemInfo.iSlot && itemInfo.iSlot != 1)
		return;

	if (pLocalPlayer->m_rgAmmo[pCurrentWeapon->m_iPrimaryAmmoType])
	{
		if (isPassiveCheck)
		{
			if ((2 * pCurrentWeapon->m_iClip) < pCurrentWeapon->iMaxClip() && !pCurrentWeapon->m_fInReload)
			{
				CreateAndAddEventToList(YOU_SHOULD_RELOAD);
			}
		}
		else
		{
			if ((5 * pCurrentWeapon->m_iClip) < pCurrentWeapon->iMaxClip() && !pCurrentWeapon->m_fInReload)
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_SHOULD_RELOAD);
				if (message)
				{
					message->m_lastCloseTime = 0;
				}

				CreateAndAddEventToList(YOU_SHOULD_RELOAD);
			}
			else
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_SHOULD_RELOAD);
				if (message)
				{
					message->m_lastCloseTime = gpGlobals->time;
				}
			}
		}
	}
	else if (!pCurrentWeapon->m_iClip)
	{
		if (!isPassiveCheck)
		{
			TutorMessage *message = GetTutorMessageDefinition(YOU_ARE_OUT_OF_AMMO);
			if (message)
			{
				message->m_lastCloseTime = 0;
			}
		}

		CreateAndAddEventToList(YOU_ARE_OUT_OF_AMMO);
	}
}

void CCSTutor::CheckExamineMessages(float time)
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
		return;

	for (int i = 0; i < TUTOR_NUM_MESSAGES; i++)
	{
		TutorMessage *message = GetTutorMessageDefinition(i);
		if (!message || message->m_class != TUTORMESSAGECLASS_EXAMINE)
			continue;

		CBaseEntity *pEntity = nullptr;
		bool isPlayerLooking = false;

		while ((pEntity = GetEntityForMessageID(i, pEntity)))
		{
			if (i == YOU_SEE_FRIEND_CORPSE || i == YOU_SEE_ENEMY_CORPSE)
			{
				if (IsPlayerLookingAtPosition((Vector *)pEntity, pLocalPlayer))
				{
					isPlayerLooking = true;
					break;
				}
			}
			else if (i == YOU_SEE_HOSTAGE_CT_EXAMINE || i == YOU_SEE_FRIEND || i == YOU_SEE_ENEMY)
			{
				if (IsPlayerLookingAtEntity(pEntity, pLocalPlayer))
				{
					isPlayerLooking = true;
					break;
				}
			}
			else if (IsPlayerLookingAtPosition(&pEntity->pev->origin, pLocalPlayer))
			{
				isPlayerLooking = true;
				break;
			}
		}

		if (isPlayerLooking)
		{
			if (message->m_examineStartTime == -1.0f)
				continue;

			if (time - message->m_examineStartTime <= cv_tutor_examine_time.value)
				continue;

			bool validEntity = false;
			if (i == YOU_SEE_FRIEND)
			{
				CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
				if (pPlayer->IsPlayer() && pPlayer->IsAlive() && pPlayer->m_iTeam == pLocalPlayer->m_iTeam)
				{
					validEntity = true;
				}
			}
			else if (i == YOU_SEE_ENEMY)
			{
				CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);
				if (pPlayer->IsPlayer() && pPlayer->IsAlive() && pPlayer->m_iTeam == pLocalPlayer->m_iTeam)
				{
					if ((pPlayer->m_iTeam != CT || pLocalPlayer->m_iTeam == TERRORIST) && (pPlayer->m_iTeam != TERRORIST || pLocalPlayer->m_iTeam == CT))
					{
						validEntity = true;
					}
				}
			}
			else if (i == YOU_SEE_HOSTAGE_CT_EXAMINE)
			{
				CHostage *pHostage = static_cast<CHostage *>(pEntity);
				if (pEntity->IsAlive())
				{
					if (!pHostage->IsFollowingSomeone())
					{
						validEntity = true;
					}
				}
			}

			if (validEntity)
			{
				CreateAndAddEventToList((TutorMessageID)i, pEntity);
			}
		}
		else
		{
			message->m_examineStartTime = -1.0f;
		}
	}
}

bool CCSTutor::CanLocalPlayerBuyStuff()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		return pLocalPlayer->CanPlayerBuy();
	}

	return false;
}

void CCSTutor::CheckBuyZoneMessages()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer || m_currentlyShownMessageID == BUY_TIME_BEGIN)
		return;

	CBasePlayerWeapon *pPrimaryWeapon = static_cast<CBasePlayerWeapon *>(pLocalPlayer->m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	CBasePlayerWeapon *pSecondaryWeapon = static_cast<CBasePlayerWeapon *>(pLocalPlayer->m_rgpPlayerItems[PISTOL_SLOT]);

	if (pPrimaryWeapon)
	{
		if (pLocalPlayer->NeedsPrimaryAmmo() && pLocalPlayer->CanAffordPrimaryAmmo())
		{
			TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_PRIMARY_AMMO);
			return;
		}
	}
	else
	{
		if (pLocalPlayer->CanAffordPrimary())
		{
			TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_PRIMARY_WEAPON);
			return;
		}
	}

	if (pSecondaryWeapon && pLocalPlayer->NeedsSecondaryAmmo() && pLocalPlayer->CanAffordSecondaryAmmo())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_SECONDARY_AMMO);
	}
	else if (pLocalPlayer->NeedsArmor() && pLocalPlayer->CanAffordArmor())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_ARMOR);
	}
	else if (pLocalPlayer->NeedsDefuseKit() && pLocalPlayer->CanAffordDefuseKit())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_DEFUSE_KIT);
	}
	else if (pLocalPlayer->NeedsGrenade() && pLocalPlayer->CanAffordGrenade())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_GRENADE);
	}
	else
	{
		TheTutor->OnEvent(EVENT_TUTOR_NOT_BUYING_ANYTHING);
	}
}

bool CCSTutor::IsHostageMap()
{
	return UTIL_FindEntityByClassname(nullptr, "hostage_entity") != nullptr;
}

bool CCSTutor::IsBombMap()
{
	return CSGameRules()->m_bMapHasBombTarget;
}

void CCSTutor::ResetPlayerDeathInfo()
{
	for (auto& playerDeathInfo : m_playerDeathInfo) {
		playerDeathInfo.m_hasBeenShown = false;
		playerDeathInfo.m_event = nullptr;
	}
}

void CCSTutor::ConstructRecentDeathsList(TeamName team, char *buf, int buflen, TutorMessageEvent *event)
{
	if (!buf || !buflen)
		return;

	char scratch[32];
	buf[0] = '\0';

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!pPlayer)
			continue;

		// ignore alive players
		if (pPlayer->IsAlive())
			continue;

		if (pPlayer->m_iTeam != team)
			continue;

		Q_strcat(buf, "  %n");
		Q_sprintf(scratch, "%d\n", i);
		Q_strcat(buf, scratch);

		m_playerDeathInfo[i].m_event = event;
	}
}

void CCSTutor::TransferDeathEvents(TutorMessageEvent *oldEvent, TutorMessageEvent *newEvent)
{
	for (auto& playerDeathInfo : m_playerDeathInfo)
	{
		if (playerDeathInfo.m_event == oldEvent) {
			playerDeathInfo.m_event = newEvent;
		}
	}
}
