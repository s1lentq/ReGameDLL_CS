#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

const char *TutorIdentifierList[] =
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

#endif // HOOK_GAMEDLL

/* <212575> ../cstrike/dlls/tutor_cs_tutor.cpp:197 */
CCSTutor::CCSTutor()
{
	m_stateSystem = new CCSTutorStateSystem;

	m_nextViewableCheckTime = 0;
	m_currentlyShownMessageID = TUTOR_NUM_MESSAGES;
	m_currentMessageEvent = NULL;
	m_messageTypeMask = TUTORMESSAGETYPE_ALL;
	m_lastScenarioEvent = NULL;
	m_haveSpawned = false;
	m_lastHintShown = HINT_BEGIN;
	m_lastInGameHintShown = INGAME_HINT_BEGIN;

	ReadTutorMessageFile();
	ApplyPersistentDecay();
	ResetPlayerDeathInfo();
}

/* <217e69> ../cstrike/dlls/tutor_cs_tutor.cpp:221 */
CCSTutor::~CCSTutor()
{
	if (m_stateSystem != NULL)
	{
		delete m_stateSystem;
	}

	if (m_currentMessageEvent != NULL)
	{
		DeleteEvent(m_currentMessageEvent);
		m_currentMessageEvent = NULL;
	}

	if (m_lastScenarioEvent != NULL)
	{
		DeleteEvent(m_lastScenarioEvent);
		m_lastScenarioEvent = NULL;
	}

	ClearCurrentEvent();
	ClearEventList();
}

/* <21066a> ../cstrike/dlls/tutor_cs_tutor.cpp:246 */
void ParseMessageParameters(char *&messageData, TutorMessage *ret)
{
	char *token;

	while (true)
	{
		messageData = MP_COM_Parse((char *)messageData);
		token = MP_COM_GetToken();

		if (!messageData || !Q_stricmp(token, "End"))
		{
			break;
		}

		if (!Q_stricmp(token, "String"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_text = Q_strdup(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "Duration"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_duration = Q_atoi(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "Priority"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_priority = Q_atoi(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "KeepOld"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			token = MP_COM_GetToken();

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
			messageData = MP_COM_Parse((char *)messageData);

			if (!Q_stricmp(MP_COM_GetToken(), "Examine"))
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
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_decay = Q_atoi(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "Type"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			token = MP_COM_GetToken();

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
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_lifetime = Q_atoi(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "DuplicateID"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_duplicateID = Q_atoi(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "Interrupt"))
		{
			messageData = MP_COM_Parse((char *)messageData);

			if (!Q_stricmp(MP_COM_GetToken(), "Now"))
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
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_minDisplayTimeOverride = Q_atof(MP_COM_GetToken());
		}
		else if (!Q_stricmp(token, "MinRepeatInterval"))
		{
			messageData = MP_COM_Parse((char *)messageData);
			ret->m_minRepeatInterval = Q_atof(MP_COM_GetToken());
		}
	}
}

/* <20ffde> ../cstrike/dlls/tutor_cs_tutor.cpp:405 */
TutorMessage *ConstructTutorMessage(char *&messageData, TutorMessage *defaults)
{
	TutorMessage *ret = new TutorMessage;

        ret->m_text = NULL;
        ret->m_duplicateID = defaults->m_duplicateID;
        ret->m_keepOld = defaults->m_keepOld;
        ret->m_duration = defaults->m_duration;
        ret->m_priority = defaults->m_priority;
        ret->m_class = defaults->m_class;
        ret->m_type = defaults->m_type;
        ret->m_decay = defaults->m_decay;
        ret->m_lifetime = defaults->m_lifetime;
        ret->m_interruptFlag = defaults->m_interruptFlag;
        ret->m_minDisplayTimeOverride = defaults->m_minDisplayTimeOverride;
	ret->m_minRepeatInterval = defaults->m_minRepeatInterval;
	ret->m_examineStartTime = -1.0f;
        ret->m_timesShown = 0;
	ret->m_lastCloseTime = 0;

	ParseMessageParameters(messageData, ret);

	return ret;
}

/* <21005d> ../cstrike/dlls/tutor_cs_tutor.cpp:431 */
void ReadDefaultValues(char *&messageData, TutorMessage *defaults)
{
	ParseMessageParameters(messageData, defaults);
}

/* <21164e> ../cstrike/dlls/tutor_cs_tutor.cpp:436 */
void CCSTutor::ReadTutorMessageFile()
{
	int messageFileLen = 0;

	char *messageFile;
	char *messageData;
	TutorMessage defaultMessage;

	messageFile = messageData = (char *)LOAD_FILE_FOR_ME("tutordata.txt", &messageFileLen);

	if (!messageFile)
	{
		if (g_bIsCzeroGame)
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
		messageData = MP_COM_Parse(messageData);

		if (!messageData)
		{
			break;
		}

		char *token = MP_COM_GetToken();

		if (!Q_stricmp(token, "TutorMessage"))
		{
			messageData = MP_COM_Parse(messageData);
			token = MP_COM_GetToken();

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

/* <2126f8> ../cstrike/dlls/tutor_cs_tutor.cpp:491 */
void CCSTutor::ApplyPersistentDecay()
{
	for (TutorMessageID mid = YOU_FIRED_A_SHOT; mid < TUTOR_NUM_MESSAGES; mid++)
	{
		TutorMessage *definition = GetTutorMessageDefinition(mid);

		if (definition != NULL)
		{
			int timesShown = GET_TIMES_TUTOR_MESSAGE_SHOWN(mid);

			if (timesShown != -1)
			{
				definition->m_timesShown = timesShown;
			}
		}
	}
}

/* <21275b> ../cstrike/dlls/tutor_cs_tutor.cpp:511 */
bool CCSTutor::HasCurrentWindowBeenActiveLongEnough(float time)
{
	return (m_currentlyShownMessageID < 0 || m_currentlyShownMessageID >= TUTOR_NUM_MESSAGES || time > m_currentlyShownMessageMinimumCloseTime);
}

/* <212787> ../cstrike/dlls/tutor_cs_tutor.cpp:528 */
bool CCSTutor::ShouldShowMessageEvent(TutorMessageEvent *event, float time)
{
	if (event == NULL)
	{
		return false;
	}

	TutorMessage *message = GetTutorMessageDefinition(event->GetID());

	if (message == NULL)
	{
		return false;
	}

	if (message->m_class == TUTORMESSAGECLASS_NORMAL)
	{
		if (message->m_decay)
		{
			if (message->m_timesShown >= message->m_decay)
				return false;
		}
	}

	if (!(m_messageTypeMask & message->m_type) || (time - message->m_lastCloseTime < message->m_minRepeatInterval))
	{
		return false;
	}

	if (HasCurrentWindowBeenActiveLongEnough(time))
	{
		return true;
	}

	if (message->m_interruptFlag != TUTORMESSAGEINTERRUPTFLAG_NOW_DAMMIT)
	{
		return false;
	}

	TutorMessage *current = GetTutorMessageDefinition(m_currentlyShownMessageID);

	if (current == NULL || (DoMessagesHaveSameID(event->GetID(), m_currentlyShownMessageID) && current->m_keepOld != TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD))
	{
		return false;
	}

	if (message->m_priority > current->m_priority
		|| message->m_priority == current->m_priority
		|| m_currentMessageEvent->GetTimeActive(time) < event->GetTimeActive(time))
	{
		return true;
	}

	return false;
}

/* <21362f> ../cstrike/dlls/tutor_cs_tutor.cpp:597 */
void CCSTutor::CheckForInterruptingMessageEvent(float time)
{
	bool newEvent = false;

	TutorMessageEvent *event = m_eventList;
	TutorMessage *oldMessage = GetTutorMessageDefinition(m_currentlyShownMessageID);
	TutorMessageEvent *oldEvent = m_currentMessageEvent;

	if (event == NULL)
	{
		return;
	}

	while (event != NULL)
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

	if (oldEvent != NULL)
	{
		ProcessShownDeathsForEvent(event);
		DeleteEvent(oldEvent);
	}

	CloseCurrentWindow();
	if (oldMessage != NULL)
	{
		oldMessage->m_lastCloseTime = time;
	}

	DeleteEventFromEventList(m_currentMessageEvent);
	ConstructMessageAndDisplay();
}

/* <215ff3> ../cstrike/dlls/tutor_cs_tutor.cpp:642 */
void CCSTutor::__MAKE_VHOOK(TutorThink)(float time)
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

/* <213556> ../cstrike/dlls/tutor_cs_tutor.cpp:691 */
void CCSTutor::CheckForWindowClose(float time)
{
	if (m_currentlyShownMessageID < 0 || m_currentlyShownMessageID >= 150 || time <= m_currentlyShownMessageCloseTime)
	{
		return;
	}

	TutorMessageEvent *event = GetTutorMessageUpdateEvent();

	if (event == NULL)
	{
		ClearCurrentEvent();
		return;
	}

	UpdateCurrentMessage(event);
	DeleteEventFromEventList(event);
}

/* <2134a7> ../cstrike/dlls/tutor_cs_tutor.cpp:715 */
void CCSTutor::CheckForContentUpdate()
{
	if (m_currentlyShownMessageID < 0 || m_currentlyShownMessageID >= 150)
	{
		return;
	}

	TutorMessage *definition = GetTutorMessageDefinition(m_currentlyShownMessageID);

	if (definition == NULL || definition->m_keepOld != TUTORMESSAGEKEEPOLDTYPE_UPDATE_CONTENT)
	{
		return;
	}

	TutorMessageEvent *event = GetTutorMessageUpdateEvent();

	if (event != NULL)
	{
		UpdateCurrentMessage(event);
		DeleteEventFromEventList(event);
	}
}

/* <21281f> ../cstrike/dlls/tutor_cs_tutor.cpp:744 */
void CCSTutor::ClearCurrentEvent(bool closeWindow, bool processDeathsForEvent)
{
	TutorMessage *oldMessage = GetTutorMessageDefinition(m_currentlyShownMessageID);

	if (oldMessage != NULL)
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

	if (m_currentMessageEvent != NULL)
	{
		DeleteEvent(m_currentMessageEvent);
		m_currentMessageEvent = NULL;
	}
}

/* <2128d0> ../cstrike/dlls/tutor_cs_tutor.cpp:775 */
void CCSTutor::ProcessShownDeathsForEvent(TutorMessageEvent *event)
{
	if (event == NULL)
	{
		return;
	}

	for (int i = 0; i < ARRAYSIZE(m_playerDeathInfo); ++i)
	{
		if (m_playerDeathInfo[i].m_event == event)
		{
			m_playerDeathInfo[i].m_hasBeenShown = true;
			m_playerDeathInfo[i].m_event = NULL;
		}
	}
}

/* <212949> ../cstrike/dlls/tutor_cs_tutor.cpp:794 */
TutorMessageEvent *CCSTutor::GetTutorMessageUpdateEvent()
{
	TutorMessage *definition = GetTutorMessageDefinition(m_currentlyShownMessageID);

	if (definition == NULL || definition->m_keepOld == TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD)
	{
		return NULL;
	}

	for (TutorMessageEvent *event = m_eventList; event != NULL; event = event->GetNext())
	{
		if (DoMessagesHaveSameID(event->GetID(), m_currentlyShownMessageID))
		{
			return event;
		}
	}

	return NULL;
}

/* <212988> ../cstrike/dlls/tutor_cs_tutor.cpp:816 */
bool CCSTutor::GetDuplicateMessagesFromEventList(TutorMessageEvent *&event1, TutorMessageEvent *&event2)
{
	for (event1 = m_eventList; event1 != NULL; event1 = event1->GetNext())
	{
		for (event2 = event1->GetNext(); event2 != NULL; event2 = event2->GetNext())
		{
			if (DoMessagesHaveSameID(event1->GetID(), event2->GetID()))
			{
				return true;
			}
		}
	}

	return false;
}

/* <212f62> ../cstrike/dlls/tutor_cs_tutor.cpp:836 */
void CCSTutor::CheckForInactiveEvents(float time)
{
	TutorMessageEvent *event = m_eventList;

	while (event != NULL)
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

	TutorMessageEvent *event1 = NULL;
	TutorMessageEvent *event2 = NULL;

	bool foundDup = GetDuplicateMessagesFromEventList(event1, event2);

	if (foundDup)
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

/* <21314d> ../cstrike/dlls/tutor_cs_tutor.cpp:886 */
void CCSTutor::CancelEvent(TutorMessageID mid)
{
	if (m_currentlyShownMessageID == mid)
	{
		ClearCurrentEvent();
	}

	TutorMessageEvent *event = m_eventList;

	while (event != NULL)
	{
		TutorMessageEvent *temp = event->GetNext();

		if (event->GetID() == mid)
		{
			DeleteEventFromEventList(event);
			DeleteEvent(event);
		}

		event = temp;
	}

	if (m_lastScenarioEvent != NULL && m_lastScenarioEvent->GetID() == mid)
	{
		DeleteEvent(m_lastScenarioEvent);
		m_lastScenarioEvent = NULL;
	}
}

/* <2129db> ../cstrike/dlls/tutor_cs_tutor.cpp:920 */
NOXREF void CCSTutor::LookupHotKey(TutorMessageID mid, int paramNum, wchar_t *buf, int buflen)
{
#ifdef _WIN32
	_snwprintf(buf, buflen - 1, L"KEY%d", paramNum);
#endif // _WIN32
}

/* <212aa0> ../cstrike/dlls/tutor_cs_tutor.cpp:930 */
TutorMessageEvent *CCSTutor::CreateTutorMessageEvent(TutorMessageID mid, CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer;
	TutorMessage *message;
	TutorMessageEvent *event;

	char enemyList[2048];
	char teammateList[2048];

	localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
	{
		return NULL;
	}

	message = GetTutorMessageDefinition(mid);

	if (message == NULL)
	{
		return NULL;
	}

	event = new TutorMessageEvent
	(
		mid,
		message->m_duplicateID,
		gpGlobals->time,
		message->m_lifetime,
		message->m_priority
	);

	if (event != NULL)
	{
		switch (mid)
		{
		case YOU_KILLED_PLAYER_ONE_LEFT:
		case YOU_KILLED_LAST_ENEMY:
		case YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT:
		case YOU_KILLED_LAST_ENEMY_HEADSHOT:
		case ENEMY_KILLED_ONE_LEFT:
		case LAST_ENEMY_KILLED:
		{
			switch (localPlayer->m_iTeam)
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
			int numT;
			int numCT;

			char numTStr[16];
			char numCTStr[16];

			GetNumPlayersAliveOnTeams(numT, numCT);

			Q_snprintf(numTStr, sizeof(numTStr), "%i", numT);
			Q_snprintf(numCTStr, sizeof(numCTStr), "%i", numCT);

			switch (localPlayer->m_iTeam)
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

			if (TheCareerTasks != NULL)
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
			ConstructRecentDeathsList(localPlayer->m_iTeam, enemyList, sizeof(enemyList), event);
			event->AddParameter(enemyList);
			break;
		case TEAMMATE_KILLED:
		{
			int numT;
			int numCT;

			char numTStr[16];
			char numCTStr[16];

			GetNumPlayersAliveOnTeams(numT, numCT);

			if (localPlayer->IsAlive())
			{
				switch (localPlayer->m_iTeam)
				{
				case CT:
					numCT--;
					break;
				case TERRORIST:
					numT--;
					break;
				}
			}

			Q_snprintf(numTStr, sizeof(numTStr), "%i", numT);
			Q_snprintf(numCTStr, sizeof(numCTStr), "%i", numCT);

			switch (localPlayer->m_iTeam)
			{
			case CT:
				event->AddParameter(numCTStr);
				break;
			case TERRORIST:
				event->AddParameter(numTStr);
				break;
			}

			ConstructRecentDeathsList(localPlayer->m_iTeam, teammateList, sizeof(teammateList), event);
			event->AddParameter(teammateList);

			break;
		}
		default:
			break;
		}

	}

	return event;
}

/* <212d0e> ../cstrike/dlls/tutor_cs_tutor.cpp:1096 */
void CCSTutor::AddToEventList(TutorMessageEvent *event)
{
	if (event != NULL)
	{
		event->SetNext(m_eventList);
		m_eventList = event;
	}
}

/* <212d3b> ../cstrike/dlls/tutor_cs_tutor.cpp:1108 */
void CCSTutor::CreateAndAddEventToList(TutorMessageID mid, CBaseEntity *entity, CBaseEntity *other)
{
	TutorMessageEvent *event;
	TutorMessage *message;

	event = CreateTutorMessageEvent(mid, entity, other);

	if (event != NULL)
	{
		message = GetTutorMessageDefinition(mid);

		if (message != NULL && message->m_type == TUTORMESSAGETYPE_SCENARIO)
		{
			if (m_lastScenarioEvent != NULL)
			{
				DeleteEvent(m_lastScenarioEvent);
				m_lastScenarioEvent = NULL;
			}

			m_lastScenarioEvent = CreateTutorMessageEvent(mid, entity, other);
		}

		AddToEventList(event);
	}
}

/* <212e1a> ../cstrike/dlls/tutor_cs_tutor.cpp:1136 */
void CCSTutor::DeleteEventFromEventList(TutorMessageEvent *event)
{
	if (event == NULL)
	{
		return;
	}

	TutorMessageEvent *temp = m_eventList;

	if (temp != event)
	{
		if (temp != NULL)
		{
			while (event != temp->GetNext())
			{
				temp = temp->GetNext();

				if (temp == NULL)
				{
					return;
				}
			}

			if (temp != NULL && temp->GetNext() == event)
			{
				temp->SetNext(temp->GetNext()->GetNext());
			}
		}
	}
	else
		m_eventList = m_eventList->GetNext();
}

/* <213215> ../cstrike/dlls/tutor_cs_tutor.cpp:1163 */
void CCSTutor::ClearEventList()
{
	while (m_eventList != NULL)
	{
		TutorMessageEvent *temp = m_eventList;
		m_eventList = m_eventList->GetNext();

		DeleteEvent(temp);
	}
}

/* <213289> ../cstrike/dlls/tutor_cs_tutor.cpp:1175 */
void CCSTutor::DeleteEvent(TutorMessageEvent *event)
{
	for (int i = 0; i < ARRAYSIZE(m_playerDeathInfo); ++i)
	{
		if (m_playerDeathInfo[i].m_event == event)
		{
			m_playerDeathInfo[i].m_event = NULL;
		}
	}

	if (event != NULL)
	{
		delete event;
	}
}

/* <210a17> ../cstrike/dlls/tutor_cs_tutor.cpp:1189 */
void CCSTutor::__MAKE_VHOOK(PurgeMessages)()
{
	ClearCurrentEvent();
	ClearEventList();

	if (m_lastScenarioEvent != NULL)
	{
		DeleteEvent(m_lastScenarioEvent);
		m_lastScenarioEvent = NULL;
	}
}

/* <2132ca> ../cstrike/dlls/tutor_cs_tutor.cpp:1203 */
void CCSTutor::ComputeDisplayTimesForMessage()
{
	TutorMessage *message = GetTutorMessageDefinition(m_currentlyShownMessageID);
	float now = gpGlobals->time;

	if (message == NULL)
	{
		m_currentlyShownMessageCloseTime = now;
		return;
	}

	m_currentlyShownMessageCloseTime = message->m_duration + now;
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

	m_currentlyShownMessageMinimumCloseTime = message->m_minDisplayTimeOverride + now;

	if (m_currentlyShownMessageMinimumCloseTime > m_currentlyShownMessageCloseTime)
	{
		m_currentlyShownMessageCloseTime = m_currentlyShownMessageMinimumCloseTime;
	}
}

/* <21333e> ../cstrike/dlls/tutor_cs_tutor.cpp:1241 */
NOXREF bool CCSTutor::ShouldUpdateCurrentMessage(TutorMessageID messageID)
{
	if (DoMessagesHaveSameID(messageID, m_currentlyShownMessageID))
	{
		TutorMessage *definition = GetTutorMessageDefinition(messageID);

		if (definition != NULL && definition->m_keepOld != TUTORMESSAGEKEEPOLDTYPE_DONT_KEEP_OLD)
		{
			return true;
		}
	}

	return false;
}

/* <213393> ../cstrike/dlls/tutor_cs_tutor.cpp:1259 */
void CCSTutor::UpdateCurrentMessage(TutorMessageEvent *event)
{
	TransferDeathEvents(m_currentMessageEvent, event);

	if (m_currentMessageEvent != NULL)
	{
		DeleteEvent(m_currentMessageEvent);
		m_currentMessageEvent = NULL;
	}

	m_currentlyShownMessageID = (TutorMessageID)event->GetID();
	m_currentMessageEvent = event;

	TutorMessage *definition = GetTutorMessageDefinition(event->GetID());

	if (definition != NULL)
	{
		CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

		if (localPlayer != NULL)
		{
			m_currentlyShownMessageCloseTime = definition->m_duration + gpGlobals->time;

			if (definition->m_keepOld == TUTORMESSAGEKEEPOLDTYPE_UPDATE_CONTENT)
			{
				CloseCurrentWindow();
				DisplayMessageToPlayer(localPlayer, event->GetID(), definition->m_text, event);
			}
		}
	}
}

/* <21060a> ../cstrike/dlls/tutor_cs_tutor.cpp:1299 */
void CCSTutor::__MAKE_VHOOK(ShowTutorMessage)(TutorMessageEvent *event)
{
	TutorMessageID mid = static_cast<TutorMessageID>(event->GetID());

	if (mid < 0 || mid >= TUTOR_NUM_MESSAGES)
	{
		return;
	}

	TutorMessage *message = GetTutorMessageDefinition(mid);

	if (message != NULL)
	{
		m_currentlyShownMessageID = mid;
		m_currentMessageEvent = event;

		m_currentlyShownMessageCloseTime = 0;
		m_currentlyShownMessageMinimumCloseTime = 0;
	}
}

/* <2135cc> ../cstrike/dlls/tutor_cs_tutor.cpp:1324 */
void CCSTutor::ConstructMessageAndDisplay()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL && !localPlayer->IsBot())
	{
		TutorMessageID mid = static_cast<TutorMessageID>(m_currentMessageEvent->GetID());

		if (mid < 0 || mid >= TUTOR_NUM_MESSAGES)
		{
			return;
		}

		TutorMessage *message = GetTutorMessageDefinition(mid);

		if (message != NULL)
		{
			message->m_timesShown++;
			ComputeDisplayTimesForMessage();
			DisplayMessageToPlayer(localPlayer, mid, message->m_text, m_currentMessageEvent);
		}
	}
}

/* <2161ea> ../cstrike/dlls/tutor_cs_tutor.cpp:1356 */
void CCSTutor::__MAKE_VHOOK(CallEventHandler)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	switch (event)
	{
	case EVENT_WEAPON_FIRED:
		HandleWeaponFired(entity, other);
		break;
	case EVENT_WEAPON_FIRED_ON_EMPTY:
		HandleWeaponFiredOnEmpty(entity, other);
		break;
	case EVENT_WEAPON_RELOADED:
		HandleWeaponReloaded(entity, other);
		break;
	case EVENT_BEING_SHOT_AT:
		HandleBeingShotAt(entity, other);
		break;
	case EVENT_PLAYER_BLINDED_BY_FLASHBANG:
		HandlePlayerBlindedByFlashbang(entity, other);
		break;
	case EVENT_PLAYER_DIED:
		HandlePlayerDied(entity, other);
		break;
	case EVENT_PLAYER_TOOK_DAMAGE:
		HandlePlayerTookDamage(entity, other);
		break;
	case EVENT_HOSTAGE_DAMAGED:
		HandleHostageDamaged(entity, other);
		break;
	case EVENT_HOSTAGE_KILLED:
		HandleHostageKilled(entity, other);
		break;
	case EVENT_BOMB_PLANTED:
		HandleBombPlanted(entity, other);
		break;
	case EVENT_BOMB_DEFUSING:
		HandleBombDefusing(entity, other);
		break;
	case EVENT_BOMB_DEFUSED:
		HandleBombDefused(entity, other);
		break;
	case EVENT_BOMB_EXPLODED:
		HandleBombExploded(entity, other);
		break;
	case EVENT_HOSTAGE_USED:
		HandleHostageUsed(entity, other);
		break;
	case EVENT_HOSTAGE_RESCUED:
		HandleHostageRescued(entity, other);
		break;
	case EVENT_ALL_HOSTAGES_RESCUED:
		HandleAllHostagesRescued(entity, other);
		break;
	case EVENT_TERRORISTS_WIN:
		HandleTWin(entity, other);
		break;
	case EVENT_CTS_WIN:
		HandleCTWin(entity, other);
		break;
	case EVENT_ROUND_DRAW:
		HandleRoundDraw(entity, other);
		break;
	case EVENT_ROUND_START:
		HandleRoundStart(entity, other);
		break;
	case EVENT_PLAYER_SPAWNED:
		HandlePlayerSpawned(entity, other);
		break;
	case EVENT_PLAYER_LEFT_BUY_ZONE:
		HandlePlayerLeftBuyZone(entity, other);
		break;
	case EVENT_DEATH_CAMERA_START:
		HandleDeathCameraStart(entity, other);
		break;
	case EVENT_TUTOR_BUY_MENU_OPENNED:
		HandleBuyMenuOpenned(entity, other);
		break;
	case EVENT_TUTOR_AUTOBUY:
		HandleAutoBuy(entity, other);
		break;
	case EVENT_TUTOR_NOT_BUYING_ANYTHING:
		HandleNotBuyingAnything(entity, other);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_PRIMARY_WEAPON:
		HandleNeedToBuyPrimaryWeapon(entity, other);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_PRIMARY_AMMO:
		HandleNeedToBuyPrimaryAmmo(entity, other);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_SECONDARY_AMMO:
		HandleNeedToBuySecondaryAmmo(entity, other);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_ARMOR:
		HandleNeedToBuyArmor(entity, other);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_DEFUSE_KIT:
		HandleNeedToBuyDefuseKit(entity, other);
		break;
	case EVENT_TUTOR_NEED_TO_BUY_GRENADE:
		HandleNeedToBuyGrenade(entity, other);
		break;
	case EVENT_CAREER_TASK_DONE:
		HandleCareerTaskDone(entity, other);
		break;
	case EVENT_RADIO_COVER_ME:
		HandleRadioCoverMe(entity, other);
		break;
	case EVENT_RADIO_YOU_TAKE_THE_POINT:
		HandleRadioYouTakeThePoint(entity, other);
		break;
	case EVENT_RADIO_HOLD_THIS_POSITION:
		HandleRadioHoldThisPosition(entity, other);
		break;
	case EVENT_RADIO_REGROUP_TEAM:
		HandleRadioRegroupTeam(entity, other);
		break;
	case EVENT_RADIO_FOLLOW_ME:
		HandleRadioFollowMe(entity, other);
		break;
	case EVENT_RADIO_TAKING_FIRE:
		HandleRadioTakingFire(entity, other);
		break;
	case EVENT_RADIO_GO_GO_GO:
		HandleRadioGoGoGo(entity, other);
		break;
	case EVENT_RADIO_TEAM_FALL_BACK:
		HandleRadioTeamFallBack(entity, other);
		break;
	case EVENT_RADIO_STICK_TOGETHER_TEAM:
		HandleRadioStickTogetherTeam(entity, other);
		break;
	case EVENT_RADIO_GET_IN_POSITION_AND_WAIT:
		HandleRadioGetInPositionAndWait(entity, other);
		break;
	case EVENT_RADIO_STORM_THE_FRONT:
		HandleRadioStormTheFront(entity, other);
		break;
	case EVENT_RADIO_REPORT_IN_TEAM:
		HandleRadioReportInTeam(entity, other);
		break;
	case EVENT_RADIO_AFFIRMATIVE:
		HandleRadioAffirmative(entity, other);
		break;
	case EVENT_RADIO_ENEMY_SPOTTED:
		HandleRadioEnemySpotted(entity, other);
		break;
	case EVENT_RADIO_NEED_BACKUP:
		HandleRadioNeedBackup(entity, other);
		break;
	case EVENT_RADIO_SECTOR_CLEAR:
		HandleRadioSectorClear(entity, other);
		break;
	case EVENT_RADIO_IN_POSITION:
		HandleRadioInPosition(entity, other);
		break;
	case EVENT_RADIO_REPORTING_IN:
		HandleRadioReportingIn(entity, other);
		break;
	case EVENT_RADIO_GET_OUT_OF_THERE:
		HandleRadioGetOutOfThere(entity, other);
		break;
	case EVENT_RADIO_NEGATIVE:
		HandleRadioNegative(entity, other);
		break;
	case EVENT_RADIO_ENEMY_DOWN:
		HandleRadioEnemyDown(entity, other);
		break;
	default:
		break;
	}
}

/* <215cc0> ../cstrike/dlls/tutor_cs_tutor.cpp:1594 */
void CCSTutor::HandleWeaponFired(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL && localPlayer->IsAlive())
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player == localPlayer)
		{
			CheckForNeedToReload();
		}
	}
}

/* <21371d> ../cstrike/dlls/tutor_cs_tutor.cpp:1616 */
void CCSTutor::HandleWeaponFiredOnEmpty(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer)
		{
			CBasePlayerWeapon *currentWeapon = static_cast<CBasePlayerWeapon *>(player->m_pActiveItem);

			if (currentWeapon != NULL && player->m_rgAmmo[currentWeapon->m_iPrimaryAmmoType] <= 0)
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_ARE_OUT_OF_AMMO);

				if (message != NULL)
				{
					message->m_lastCloseTime = 0;
				}

				CreateAndAddEventToList(YOU_ARE_OUT_OF_AMMO);
			}
		}
	}
}

/* <213817> ../cstrike/dlls/tutor_cs_tutor.cpp:1654 */
void CCSTutor::HandleWeaponReloaded(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *player = static_cast<CBasePlayer *>(entity);

	if (player != NULL && player->IsPlayer() && player == UTIL_GetLocalPlayer())
	{
		CancelEvent(YOU_SHOULD_RELOAD);
	}
}

/* <21385d> ../cstrike/dlls/tutor_cs_tutor.cpp:1673 */
void CCSTutor::HandlePlayerDied(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
	{
		return;
	}

	CBasePlayer *victim = static_cast<CBasePlayer *>(entity);
	CBasePlayer *attacker = static_cast<CBasePlayer *>(other);

	if (victim != NULL && !victim->IsPlayer())
	{
		victim = NULL;
	}

	if (attacker != NULL && !attacker->IsPlayer())
	{
		attacker = NULL;
	}

	if (victim == localPlayer && !attacker)
	{
		if (localPlayer->m_bKilledByBomb)
		{
			CreateAndAddEventToList(YOU_DIED, entity, other);
		}
		else
		{
			CreateAndAddEventToList(YOU_FELL_TO_YOUR_DEATH);
		}
	}

	if (!victim || !attacker)
		return;

	if (victim == attacker && victim == localPlayer)
	{
		CreateAndAddEventToList(YOU_DIED, entity, other);
		return;
	}

	int numT, numCT;
	GetNumPlayersAliveOnTeams(numT, numCT);

	if (attacker == localPlayer)
	{
		if (victim->m_iTeam == attacker->m_iTeam)
		{
			CreateAndAddEventToList(YOU_KILLED_A_TEAMMATE, entity, other);
			return;
		}

		if (victim->m_bHeadshotKilled)
		{
			switch (attacker->m_iTeam)
			{
				case CT:
				{
					switch (numT)
					{
					case 0:
						CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY_HEADSHOT, entity, other);
						break;
					case 1:
						CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT, entity, other);
						break;
					default:
						CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT, entity, other);
						break;
					}

					break;
				}
				case TERRORIST:
				{
					switch (numCT)
					{
					case 0:
						CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY_HEADSHOT, entity, other);
						break;
					case 1:
						CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT_ONE_LEFT, entity, other);
						break;
					default:
						CreateAndAddEventToList(YOU_KILLED_PLAYER_HEADSHOT, entity, other);
						break;
					}
					break;
				}
			}
		}
		else
		{
			switch (attacker->m_iTeam)
			{
				case CT:
				{
					switch (numT)
					{
					case 0:
						CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY, entity, other);
						break;
					case 1:
						CreateAndAddEventToList(YOU_KILLED_PLAYER_ONE_LEFT, entity, other);
						break;
					default:
						CreateAndAddEventToList(YOU_KILLED_PLAYER, entity, other);
						break;
					}

					break;
				}
				case TERRORIST:
				{
					switch (numCT)
					{
					case 0:
						CreateAndAddEventToList(YOU_KILLED_LAST_ENEMY, entity, other);
						break;
					case 1:
						CreateAndAddEventToList(YOU_KILLED_PLAYER_ONE_LEFT, entity, other);
						break;
					default:
						CreateAndAddEventToList(YOU_KILLED_PLAYER, entity, other);
						break;
					}
					break;
				}
			}
		}
	}
	else if (victim == localPlayer)
	{
		CreateAndAddEventToList(victim->m_bHeadshotKilled ? YOU_DIED_HEADSHOT : YOU_DIED, entity, other);
	}
	else if (victim->m_iTeam == localPlayer->m_iTeam)
	{
		switch (victim->m_iTeam)
		{
			case CT:
			{
				if (localPlayer->IsAlive())
				{
					if (numCT == 1)
					{
						CreateAndAddEventToList(LAST_TEAMMATE_KILLED, entity, other);
					}
					else if (numCT == 2)
					{
						CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, entity, other);
					}
					else
					{
						CreateAndAddEventToList(TEAMMATE_KILLED, entity, other);
					}
				}
				else
				{
					if (numCT == 1)
					{
						CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, entity, other);
					}
					else if (numCT > 1)
					{
						CreateAndAddEventToList(TEAMMATE_KILLED, entity, other);
					}
				}

				break;
			}
			case TERRORIST:
			{
				if (localPlayer->IsAlive())
				{
					if (numT == 1)
					{
						CreateAndAddEventToList(LAST_TEAMMATE_KILLED, entity, other);
					}
					else if (numT == 2)
					{
						CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, entity, other);
					}
					else
					{
						CreateAndAddEventToList(TEAMMATE_KILLED, entity, other);
					}
				}
				else
				{
					if (numT == 1)
					{
						CreateAndAddEventToList(TEAMMATE_KILLED_ONE_LEFT, entity, other);
					}
					else if (numT > 1)
					{
						CreateAndAddEventToList(TEAMMATE_KILLED, entity, other);
					}
				}

				break;
			}
		}
	}
	else
	{
		switch (localPlayer->m_iTeam)
		{
			case CT:
			{
				switch (numT)
				{
				case 0:
					CreateAndAddEventToList(LAST_ENEMY_KILLED, entity, other);
					break;
				case 1:
					CreateAndAddEventToList(ENEMY_KILLED_ONE_LEFT, entity, other);
					break;
				default:
					CreateAndAddEventToList(ENEMY_KILLED, entity, other);
					break;
				}

				break;
			}
			case TERRORIST:
			{
				switch (numCT)
				{
				case 0:
					CreateAndAddEventToList(LAST_ENEMY_KILLED, entity, other);
					break;
				case 1:
					CreateAndAddEventToList(ENEMY_KILLED_ONE_LEFT, entity, other);
					break;
				default:
					CreateAndAddEventToList(ENEMY_KILLED, entity, other);
					break;
				}
				break;
			}
		}
	}
}

/* <21394c> ../cstrike/dlls/tutor_cs_tutor.cpp:1945 */
void CCSTutor::HandlePlayerTookDamage(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *victim = static_cast<CBasePlayer *>(entity);
		CBasePlayer *attacker = static_cast<CBasePlayer *>(other);

		if (victim != NULL && !victim->IsPlayer())
		{
			victim = NULL;
		}

		if (attacker != NULL && !attacker->IsPlayer())
		{
			attacker = NULL;
		}

		if (victim != NULL && victim == localPlayer)
		{
			CreateAndAddEventToList(YOU_WERE_JUST_HURT);
		}
		else if (attacker != NULL && victim != NULL && attacker == localPlayer && victim->m_iTeam == localPlayer->m_iTeam)
		{
			CreateAndAddEventToList(YOU_ATTACKED_TEAMMATE);
		}
	}
}

/* <213a21> ../cstrike/dlls/tutor_cs_tutor.cpp:1985 */
void CCSTutor::HandlePlayerBlindedByFlashbang(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer)
		{
			CreateAndAddEventToList(YOU_ARE_BLIND_FROM_FLASHBANG);
		}
	}
}

/* <213ab7> ../cstrike/dlls/tutor_cs_tutor.cpp:2008 */
void CCSTutor::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *player = static_cast<CBasePlayer *>(entity);

	if (player->IsPlayer() && player == UTIL_GetLocalPlayer())
	{
		m_haveSpawned = true;
		m_lastInGameHintShown = INGAME_HINT_BEGIN;
		CreateAndAddEventToList(YOU_SPAWNED, entity, other);
	}
}

/* <21868e> ../cstrike/dlls/tutor_cs_tutor.cpp:2033 */
NOXREF void CCSTutor::HandleClientCorpseSpawned(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *player = static_cast<CBasePlayer *>(entity);

	if (player == NULL || !player->IsPlayer())
	{
		return;
	}

	ClientCorpseStruct *corpse = new ClientCorpseStruct;

	corpse->m_position = player->pev->origin;
	corpse->m_team = player->m_iTeam;

	m_clientCorpseList.push_back(corpse);
}

/* <215fbd> ../cstrike/dlls/tutor_cs_tutor.cpp:2050 */
void CCSTutor::HandleBuyMenuOpenned(CBaseEntity *entity, CBaseEntity *other)
{
	if (m_currentlyShownMessageID == BUY_TIME_BEGIN)
	{
		ClearCurrentEvent();
		CheckBuyZoneMessages();
	}
}

/* <213b32> ../cstrike/dlls/tutor_cs_tutor.cpp:2060 */
void CCSTutor::HandleAutoBuy(CBaseEntity *entity, CBaseEntity *other)
{
	if (m_currentlyShownMessageID == BUY_TIME_BEGIN)
	{
		ClearCurrentEvent();
	}
}

/* <213b67> ../cstrike/dlls/tutor_cs_tutor.cpp:2069 */
NOXREF void CCSTutor::HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other)
{
	;
}

/* <213b9c> ../cstrike/dlls/tutor_cs_tutor.cpp:2074 */
void CCSTutor::HandlePlayerLeftBuyZone(CBaseEntity *entity, CBaseEntity *other)
{
	m_messageTypeMask = (TUTORMESSAGETYPE_DEFAULT | TUTORMESSAGETYPE_FRIEND_DEATH | TUTORMESSAGETYPE_ENEMY_DEATH | TUTORMESSAGETYPE_SCENARIO | TUTORMESSAGETYPE_CAREER | TUTORMESSAGETYPE_INGAME_HINT | TUTORMESSAGETYPE_END_GAME);

	ClearEventList();
	ClearCurrentEvent();

	if (m_lastScenarioEvent != NULL)
	{
		m_lastScenarioEvent->SetActivationTime(gpGlobals->time);
		AddToEventList(m_lastScenarioEvent);
		m_lastScenarioEvent = NULL;
	}
}

/* <213cbb> ../cstrike/dlls/tutor_cs_tutor.cpp:2092 */
void CCSTutor::HandleBombPlanted(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *player = UTIL_GetLocalPlayer();

	if (player == NULL)
	{
		return;
	}

	if (player->IsAlive() && player->m_iTeam == CT)
	{
		CreateAndAddEventToList(BOMB_PLANTED_CT, entity, other);
	}
	else
	{
		CreateAndAddEventToList(BOMB_PLANTED_T, entity, other);
	}
}

/* <213d02> ../cstrike/dlls/tutor_cs_tutor.cpp:2112 */
void CCSTutor::HandleBombDefused(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *defuser = static_cast<CBasePlayer *>(entity);

		if (defuser != NULL && defuser->IsPlayer() && defuser == localPlayer)
		{
			CreateAndAddEventToList(YOU_DEFUSED_BOMB);
		}
		else
		{
			switch (localPlayer->m_iTeam)
			{
			case CT:
				CreateAndAddEventToList(BOMB_DEFUSED_CT);
				break;
			case TERRORIST:
				CreateAndAddEventToList(BOMB_DEFUSED_T);
				break;
			default:
				CreateAndAddEventToList(ROUND_OVER);
				break;
			}
		}
	}
}

/* <213dc6> ../cstrike/dlls/tutor_cs_tutor.cpp:2148 */
void CCSTutor::HandleBombDefusing(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer && !player->m_bHasDefuser)
		{
			CreateAndAddEventToList(DEFUSING_WITHOUT_KIT);
		}
	}
}

/* <213e5b> ../cstrike/dlls/tutor_cs_tutor.cpp:2172 */
void CCSTutor::HandleBombExploded(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		switch (localPlayer->m_iTeam)
		{
		case CT:
			CreateAndAddEventToList(BOMB_EXPLODED_CT);
			break;
		case TERRORIST:
			CreateAndAddEventToList(BOMB_EXPLODED_T);
			break;
		default:
			break;
		}
	}
}

/* <213ebd> ../cstrike/dlls/tutor_cs_tutor.cpp:2191 */
void CCSTutor::HandleRoundStart(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *player = UTIL_GetLocalPlayer();

	m_roundStartTime = gpGlobals->time;
	if (player != NULL)
	{
		if (IsBombMap())
		{
			switch (player->m_iTeam)
			{
			case CT:
				CreateAndAddEventToList(ROUND_START_DE_CT);
				break;
			case TERRORIST:
			{
				if (player->m_bHasC4)
					CreateAndAddEventToList(YOU_ARE_BOMB_CARRIER, entity, other);
				else
					CreateAndAddEventToList(ROUND_START_DE_T);
				break;
			}
			default:
				break;
			}
		}
		else if (IsHostageMap())
		{
			switch (player->m_iTeam)
			{
			case CT:
				CreateAndAddEventToList(ROUND_START_CS_CT);
				break;
			case TERRORIST:
				CreateAndAddEventToList(ROUND_START_CS_T);
				break;
			default:
				break;
			}
		}
	}
}

/* <213fc1> ../cstrike/dlls/tutor_cs_tutor.cpp:2239 */
void CCSTutor::HandleBeingShotAt(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer && localPlayer->IsAlive())
		{
			CreateAndAddEventToList(YOU_HAVE_BEEN_SHOT_AT, entity, other);
		}
	}
}

/* <2158b5> ../cstrike/dlls/tutor_cs_tutor.cpp:2265 */
void CCSTutor::HandleHostageUsed(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *activator = static_cast<CBasePlayer *>(entity);

		if (activator != NULL && activator->IsPlayer())
		{
			bool unusedHostages = !CheckForAllHostagesFollowingSomeone();

			if (activator == localPlayer)
			{
				CreateAndAddEventToList(unusedHostages ? YOU_USED_HOSTAGE_MORE_LEFT : YOU_USED_HOSTAGE_NO_MORE_LEFT);
			}
			else if (!unusedHostages)
			{
				switch (localPlayer->m_iTeam)
				{
				case CT:
					CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_CT);
					break;
				case TERRORIST:
					CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_T);
					break;
				default:
					break;
				}
			}
		}
	}
}

/* <214011> ../cstrike/dlls/tutor_cs_tutor.cpp:2307 */
void CCSTutor::HandleHostageRescued(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *rescuer = static_cast<CBasePlayer *>(entity);

		if (rescuer != NULL && rescuer->IsPlayer())
		{
			switch (localPlayer->m_iTeam)
			{
			case CT:
				CreateAndAddEventToList((localPlayer == rescuer) ? YOU_RESCUED_HOSTAGE : HOSTAGE_RESCUED_CT);
				break;
			case TERRORIST:
				CreateAndAddEventToList(HOSTAGE_RESCUED_T);
				break;
			default:
				break;
			}
		}
	}
}

/* <2140c8> ../cstrike/dlls/tutor_cs_tutor.cpp:2342 */
void CCSTutor::HandleAllHostagesRescued(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		switch (localPlayer->m_iTeam)
		{
		case CT:
			CreateAndAddEventToList(ALL_HOSTAGES_RESCUED_CT);
			break;
		case TERRORIST:
			CreateAndAddEventToList(ALL_HOSTAGES_RESCUED_T);
			break;
		default:
			break;
		}
	}
}

/* <214161> ../cstrike/dlls/tutor_cs_tutor.cpp:2361 */
void CCSTutor::HandleHostageDamaged(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *attacker = static_cast<CBasePlayer *>(other);

		if (entity != NULL && attacker != NULL && attacker->IsPlayer() && localPlayer == attacker)
		{
			CreateAndAddEventToList(YOU_DAMAGED_HOSTAGE);
		}
	}
}

/* <2157fb> ../cstrike/dlls/tutor_cs_tutor.cpp:2389 */
void CCSTutor::HandleHostageKilled(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CheckForAllHostagesDead();

		CBasePlayer *attacker = static_cast<CBasePlayer *>(other);

		if (entity != NULL && attacker != NULL && attacker->IsPlayer())
		{
			bool unusedHostages = CheckForAllHostagesFollowingSomeone();

			if (localPlayer == attacker)
			{
				CreateAndAddEventToList(YOU_KILLED_HOSTAGE);
			}

			if (unusedHostages)
			{
				switch (localPlayer->m_iTeam)
				{
				case CT:
					CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_CT);
					break;
				case TERRORIST:
					CreateAndAddEventToList(ALL_HOSTAGES_FOLLOWING_T);
					break;
				default:
					break;
				}
			}
		}
	}
}

/* <2141f5> ../cstrike/dlls/tutor_cs_tutor.cpp:2433 */
void CCSTutor::HandleRoundDraw(CBaseEntity *entity, CBaseEntity *other)
{
	CHalfLifeMultiplay *mp = g_pGameRules;

	if (mp->m_iTotalRoundsPlayed)
	{
		CreateAndAddEventToList(ROUND_DRAW);
	}

	ResetPlayerDeathInfo();
}

/* <21429a> ../cstrike/dlls/tutor_cs_tutor.cpp:2445 */
void CCSTutor::HandleCTWin(CBaseEntity *entith, CBaseEntity *other)
{
	CreateAndAddEventToList(CT_WIN);
	ResetPlayerDeathInfo();
}

/* <214335> ../cstrike/dlls/tutor_cs_tutor.cpp:2453 */
void CCSTutor::HandleTWin(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(T_WIN);
	ResetPlayerDeathInfo();
}

/* <2143ed> ../cstrike/dlls/tutor_cs_tutor.cpp:2461 */
void CCSTutor::HandleDeathCameraStart(CBaseEntity *entity, CBaseEntity *other)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player != NULL && player->IsPlayer() && player == localPlayer)
		{
			m_messageTypeMask = (TUTORMESSAGETYPE_FRIEND_DEATH | TUTORMESSAGETYPE_ENEMY_DEATH | TUTORMESSAGETYPE_HINT | TUTORMESSAGETYPE_END_GAME);
			CreateAndAddEventToList(DEATH_CAMERA_START);
		}
	}
}

/* <214472> ../cstrike/dlls/tutor_cs_tutor.cpp:2487 */
void CCSTutor::HandleRadioCoverMe(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_COVER_ME, entity, other);
}

/* <2144dd> ../cstrike/dlls/tutor_cs_tutor.cpp:2492 */
void CCSTutor::HandleRadioYouTakeThePoint(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_YOU_TAKE_THE_POINT, entity, other);
}

/* <214548> ../cstrike/dlls/tutor_cs_tutor.cpp:2497 */
void CCSTutor::HandleRadioHoldThisPosition(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_HOLD_THIS_POSITION, entity, other);
}

/* <2145b3> ../cstrike/dlls/tutor_cs_tutor.cpp:2502 */
void CCSTutor::HandleRadioRegroupTeam(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_REGROUP_TEAM, entity, other);
}

/* <21461e> ../cstrike/dlls/tutor_cs_tutor.cpp:2507 */
void CCSTutor::HandleRadioFollowMe(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_FOLLOW_ME, entity, other);
}

/* <214689> ../cstrike/dlls/tutor_cs_tutor.cpp:2512 */
void CCSTutor::HandleRadioTakingFire(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_TAKING_FIRE, entity, other);
}

/* <2146f4> ../cstrike/dlls/tutor_cs_tutor.cpp:2517 */
void CCSTutor::HandleRadioGoGoGo(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_GO_GO_GO, entity, other);
}

/* <21475f> ../cstrike/dlls/tutor_cs_tutor.cpp:2522 */
void CCSTutor::HandleRadioTeamFallBack(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_TEAM_FALL_BACK, entity, other);
}

/* <2147ca> ../cstrike/dlls/tutor_cs_tutor.cpp:2527 */
void CCSTutor::HandleRadioStickTogetherTeam(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_STICK_TOGETHER_TEAM, entity, other);
}

/* <214835> ../cstrike/dlls/tutor_cs_tutor.cpp:2532 */
void CCSTutor::HandleRadioGetInPositionAndWait(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_GET_IN_POSITION_AND_WAIT, entity, other);
}

/* <2148a0> ../cstrike/dlls/tutor_cs_tutor.cpp:2537 */
void CCSTutor::HandleRadioStormTheFront(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_STORM_THE_FRONT, entity, other);
}

/* <21490b> ../cstrike/dlls/tutor_cs_tutor.cpp:2542 */
void CCSTutor::HandleRadioReportInTeam(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_REPORT_IN_TEAM, entity, other);
}

/* <214976> ../cstrike/dlls/tutor_cs_tutor.cpp:2547 */
void CCSTutor::HandleRadioAffirmative(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_AFFIRMATIVE, entity, other);
}

/* <2149e1> ../cstrike/dlls/tutor_cs_tutor.cpp:2552 */
void CCSTutor::HandleRadioEnemySpotted(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_ENEMY_SPOTTED, entity, other);
}

/* <214a4c> ../cstrike/dlls/tutor_cs_tutor.cpp:2557 */
void CCSTutor::HandleRadioNeedBackup(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_NEED_BACKUP, entity, other);
}

/* <214ab7> ../cstrike/dlls/tutor_cs_tutor.cpp:2562 */
void CCSTutor::HandleRadioSectorClear(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_SECTOR_CLEAR, entity, other);
}

/* <214b22> ../cstrike/dlls/tutor_cs_tutor.cpp:2567 */
void CCSTutor::HandleRadioInPosition(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_IN_POSITION, entity, other);
}

/* <214b8d> ../cstrike/dlls/tutor_cs_tutor.cpp:2572 */
void CCSTutor::HandleRadioReportingIn(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_REPORTING_IN, entity, other);
}

/* <214bf8> ../cstrike/dlls/tutor_cs_tutor.cpp:2577 */
void CCSTutor::HandleRadioGetOutOfThere(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_GET_OUT_OF_THERE, entity, other);
}

/* <214c63> ../cstrike/dlls/tutor_cs_tutor.cpp:2582 */
void CCSTutor::HandleRadioNegative(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_NEGATIVE, entity, other);
}

/* <214cce> ../cstrike/dlls/tutor_cs_tutor.cpp:2587 */
void CCSTutor::HandleRadioEnemyDown(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(RADIO_ENEMY_DOWN, entity, other);
}

/* <214d39> ../cstrike/dlls/tutor_cs_tutor.cpp:2592 */
void CCSTutor::HandleNotBuyingAnything(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_TIME_BEGIN, entity, other);
}

/* <214da4> ../cstrike/dlls/tutor_cs_tutor.cpp:2597 */
void CCSTutor::HandleNeedToBuyPrimaryWeapon(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_NEED_PRIMARY, entity, other);
}

/* <214e0f> ../cstrike/dlls/tutor_cs_tutor.cpp:2602 */
void CCSTutor::HandleNeedToBuyPrimaryAmmo(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_NEED_PRIMARY_AMMO, entity, other);
}

/* <214e7a> ../cstrike/dlls/tutor_cs_tutor.cpp:2607 */
void CCSTutor::HandleNeedToBuySecondaryAmmo(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_NEED_SECONDARY_AMMO, entity, other);
}

/* <214ee5> ../cstrike/dlls/tutor_cs_tutor.cpp:2612 */
void CCSTutor::HandleNeedToBuyArmor(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_NEED_ARMOR, entity, other);
}

/* <214f50> ../cstrike/dlls/tutor_cs_tutor.cpp:2617 */
void CCSTutor::HandleNeedToBuyDefuseKit(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_NEED_DEFUSE_KIT, entity, other);
}

/* <214fbb> ../cstrike/dlls/tutor_cs_tutor.cpp:2622 */
void CCSTutor::HandleNeedToBuyGrenade(CBaseEntity *entity, CBaseEntity *other)
{
	CreateAndAddEventToList(BUY_NEED_GRENADE, entity, other);
}

/* <215036> ../cstrike/dlls/tutor_cs_tutor.cpp:2627 */
void CCSTutor::HandleCareerTaskDone(CBaseEntity *entity, CBaseEntity *other)
{
	int numTasksRemaining = 0;

	if (TheCareerTasks != NULL && (numTasksRemaining = TheCareerTasks->GetNumRemainingTasks()) > 0)
		CreateAndAddEventToList((numTasksRemaining == 1) ? CAREER_TASK_DONE_ONE_LEFT : CAREER_TASK_DONE_MORE_LEFT);
	else
		CreateAndAddEventToList(CAREER_TASK_DONE_ALL_DONE);
}

/* <2108c4> ../cstrike/dlls/tutor_cs_tutor.cpp:2650 */
void CCSTutor::__MAKE_VHOOK(HandleShotFired)(Vector source, Vector target)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		float d1, d, angle, FiringLineDistanceToPlayer;

		d1 = (source - localPlayer->pev->origin).Length();

		if (d1 > 32.0f)
		{
			d = (target - source).Length();
			angle = d1 / d;

			FiringLineDistanceToPlayer = sin(acos(angle)) * d1;

			if (FiringLineDistanceToPlayer <= 3000.0f)
			{
				OnEvent(EVENT_BEING_SHOT_AT, localPlayer);
			}
		}
	}
}

/* <21507d> ../cstrike/dlls/tutor_cs_tutor.cpp:2720 */
void CCSTutor::GetNumPlayersAliveOnTeams(int &numT, int &numCT)
{
	numT = 0;
	numCT = 0;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (player == NULL || !player->IsAlive())
		{
			continue;
		}

		switch (player->m_iTeam)
		{
		case CT:
			numCT++;
			break;
		case TERRORIST:
			numT++;
			break;
		}
	}
}

/* <2150d5> ../cstrike/dlls/tutor_cs_tutor.cpp:2749 */
void CCSTutor::CheckForLooseWeaponViewable()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		bool sawFirst = false;
		CBaseEntity *weapon = NULL;
		TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_LOOSE_WEAPON);

		if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
		{
			while ((weapon = UTIL_FindEntityByClassname(weapon, "weaponbox")) != NULL)
			{
				if (IsEntityInViewOfPlayer(weapon, localPlayer))
				{
					if (!sawFirst)
					{
						sawFirst = true;
						CreateAndAddEventToList(YOU_SEE_LOOSE_WEAPON);
					}
				}
			}
		}
	}
}

/* <21514d> ../cstrike/dlls/tutor_cs_tutor.cpp:2787 */
void CCSTutor::CheckForLooseDefuserViewable()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL && localPlayer->m_iTeam == CT)
	{
		bool sawFirst = false;
		CBaseEntity *defuser = NULL;
		TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_LOOSE_DEFUSER);

		if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
		{
			while ((defuser = UTIL_FindEntityByClassname(defuser, "item_thighpack")) != NULL)
			{
				if (IsEntityInViewOfPlayer(defuser, localPlayer))
				{
					if (!sawFirst)
					{
						sawFirst = true;
						CreateAndAddEventToList(YOU_SEE_LOOSE_DEFUSER);
					}
				}
			}
		}
	}
}

/* <2151c1> ../cstrike/dlls/tutor_cs_tutor.cpp:2826 */
void CCSTutor::CheckForBombViewable()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
	{
		return;
	}

	CBaseEntity *bomb = UTIL_FindEntityByClassname(NULL, "grenade");

	if (bomb != NULL && ((CGrenade *)bomb)->m_bIsC4 && IsEntityInViewOfPlayer(bomb, localPlayer))
	{
		switch (localPlayer->m_iTeam)
		{
			case CT:
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_PLANTED_BOMB_CT);

				if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
				{
					CreateAndAddEventToList(YOU_SEE_PLANTED_BOMB_CT);
				}
				break;
			}
			case TERRORIST:
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_PLANTED_BOMB_T);

				if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
				{
					CreateAndAddEventToList(YOU_SEE_PLANTED_BOMB_T);
				}
				break;
			}
		}
	}
	else
	{
		CBasePlayer *bombCarrier = NULL;

		for (int i = 1; i <= gpGlobals->maxClients; ++i)
		{
			CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

			if (player && player->m_bHasC4)
			{
				bombCarrier = player;
				break;
			}
		}

		bomb = UTIL_FindEntityByClassname(NULL, "weapon_c4");

		if (bomb != NULL && IsEntityInViewOfPlayer(bomb, localPlayer))
		{
			if (bombCarrier != NULL)
			{
				if (bombCarrier != localPlayer)
				{
					switch (localPlayer->m_iTeam)
					{
						case CT:
						{
							TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_BOMB_CARRIER_CT);

							if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
							{
								CreateAndAddEventToList(YOU_SEE_BOMB_CARRIER_CT);
							}
							break;
						}
						case TERRORIST:
						{
							TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_BOMB_CARRIER_T);

							if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
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
				switch (localPlayer->m_iTeam)
				{
					case CT:
					{
						TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_LOOSE_BOMB_CT);

						if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
						{
							CreateAndAddEventToList(YOU_SEE_LOOSE_BOMB_CT);
						}
						break;
					}
					case TERRORIST:
					{
						TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_LOOSE_BOMB_T);

						if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
						{
							CreateAndAddEventToList(YOU_SEE_LOOSE_BOMB_T);
						}
						break;
					}
				}
			}
		}
	}
}

/* <215431> ../cstrike/dlls/tutor_cs_tutor.cpp:2959 */
void CCSTutor::CheckForBombsiteViewable()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
	{
		return;
	}

	TutorMessageID mid = CheckForInBombZone();

	if (mid == TUTOR_NUM_MESSAGES)
	{
		switch (localPlayer->m_iTeam)
		{
			case CT:
			{
				mid = YOU_SEE_BOMBSITE_CT;
				break;
			}
			case TERRORIST:
			{
				if (localPlayer->m_bHasC4)
				{
					mid = YOU_SEE_BOMBSITE_T_BOMB;
				}
				else if (TheCSBots() == NULL || !TheCSBots()->IsBombPlanted())
				{
					mid = YOU_SEE_BOMBSITE_T;
				}
				break;
			}
		}

		TutorMessage *definition = GetTutorMessageDefinition(mid);

		if (definition == NULL || definition->m_class != TUTORMESSAGECLASS_EXAMINE)
		{
			bool sawFirst = false;
			CBaseEntity *bombTarget = NULL;

			while ((bombTarget = UTIL_FindEntityByClassname(bombTarget, "func_bomb_target")) != NULL)
			{
				if (IsBombPlantedInBombsite(bombTarget))
				{
					if (!sawFirst)
					{
						sawFirst = true;
						CreateAndAddEventToList(mid);
						break;
					}
				}
			}

			while ((bombTarget = UTIL_FindEntityByClassname(bombTarget, "info_bomb_target")) != NULL)
			{
				if (sawFirst)
					break;

				if (IsBombPlantedInBombsite(bombTarget))
				{
					if (!sawFirst)
					{
						sawFirst = true;
						CreateAndAddEventToList(mid);
						break;
					}
				}
			}
		}
	}
	else
		CreateAndAddEventToList(mid);
}

/* <21534e> ../cstrike/dlls/tutor_cs_tutor.cpp:3026 */
TutorMessageID CCSTutor::CheckForInBombZone()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();
	TutorMessageID mid = TUTOR_NUM_MESSAGES;

	if (localPlayer != NULL && localPlayer->m_iTeam == CT)
	{
		CBaseEntity *bombTarget = NULL;

		while ((bombTarget = UTIL_FindEntityByClassname(bombTarget, "func_bomb_target")) != NULL)
		{
			if (IsBombPlantedInBombsite(bombTarget))
			{
				return YOU_SEE_PLANTED_BOMB_CT;
			}
		}

		while ((bombTarget = UTIL_FindEntityByClassname(bombTarget, "info_bomb_target")) != NULL)
		{
			if (IsBombPlantedInBombsite(bombTarget))
			{
				return YOU_SEE_PLANTED_BOMB_CT;
			}
		}
	}

	return mid;
}

/* <2154b6> ../cstrike/dlls/tutor_cs_tutor.cpp:3078 */
bool CCSTutor::IsBombPlantedInBombsite(CBaseEntity *bombTarget)
{
	CGrenade *bomb = NULL;

	while ((bomb = (CGrenade *)UTIL_FindEntityByClassname(bomb, "grenade")) != NULL)
	{
		if (bomb->m_bIsC4 && IsEntityInBombsite(bomb, bombTarget))
		{
			return true;
		}
	}

	return false;
}

/* <2154f4> ../cstrike/dlls/tutor_cs_tutor.cpp:3102 */
void CCSTutor::CheckForHostageViewable()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
		return;

	CBaseEntity *hostageEntity = NULL;
	bool sawFirst = false;

	while ((hostageEntity = UTIL_FindEntityByClassname(hostageEntity, "hostage_entity")) != NULL)
	{
		bool validHostage = false;
		CHostage *hostage = static_cast<CHostage *>(hostageEntity);

		if (hostage->pev->takedamage == DAMAGE_YES)
		{
			if (!hostage->IsFollowingSomeone())
				validHostage = true;
		}

		if (hostage->IsValid() && validHostage && IsEntityInViewOfPlayer(hostage, localPlayer) && !sawFirst)
		{
			sawFirst = true;

			switch (localPlayer->m_iTeam)
			{
				case CT:
				{
					TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_HOSTAGE_CT);

					if (message != NULL && message->m_class == TUTORMESSAGECLASS_EXAMINE)
					{
						return;
					}

					CreateAndAddEventToList(YOU_SEE_HOSTAGE_CT);
					break;
				}
				case TERRORIST:
				{
					TutorMessage *message = GetTutorMessageDefinition(YOU_SEE_HOSTAGE_T);

					if (message != NULL && message->m_class == TUTORMESSAGECLASS_EXAMINE)
					{
						return;
					}

					CreateAndAddEventToList(YOU_SEE_HOSTAGE_T);
					break;
				}
			}
		}
	}
}

/* <215646> ../cstrike/dlls/tutor_cs_tutor.cpp:3168 */
void CCSTutor::CheckForTimeRunningOut()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();
	CHalfLifeMultiplay *mpRules = g_pGameRules;

	if (localPlayer == NULL || mpRules->IsFreezePeriod() || mpRules->TimeRemaining() > 30.0f)
	{
		return;
	}

	if (IsBombMap())
	{
		switch (localPlayer->m_iTeam)
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
		switch (localPlayer->m_iTeam)
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

/* <2156fd> ../cstrike/dlls/tutor_cs_tutor.cpp:3218 */
void CCSTutor::CheckForAllHostagesDead()
{
	bool foundLiveOne = false;
	CHostage *hostage = NULL;

	while ((hostage = (CHostage *)UTIL_FindEntityByClassname(hostage, "hostage_entity")) != NULL)
	{
		if (hostage->IsAlive())
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

/* <21573c> ../cstrike/dlls/tutor_cs_tutor.cpp:3242 */
bool CCSTutor::CheckForAllHostagesFollowingSomeone()
{
	bool foundUnusedOne = false;
	CHostage *hostage = NULL;

	while ((hostage = (CHostage *)UTIL_FindEntityByClassname(hostage, "hostage_entity")) != NULL)
	{
		if (hostage->pev->takedamage == DAMAGE_YES)
		{
			if (!hostage->IsFollowingSomeone())
			{
				foundUnusedOne = true;
				break;
			}
		}
	}

	return foundUnusedOne ? false : true;
}

/* <210b98> ../cstrike/dlls/tutor_cs_tutor.cpp:3268 */
TutorMessage *CCSTutor::__MAKE_VHOOK(GetTutorMessageDefinition)(int messageID)
{
	if (messageID < 0 || messageID >= TUTOR_NUM_MESSAGES)
	{
		return NULL;
	}

	TutorMessageMapIter iter = m_messageMap.find(TutorIdentifierList[messageID]);

	if (iter != m_messageMap.end())
	{
		return (*iter).second;
	}

	return NULL;
}

/* <215938> ../cstrike/dlls/tutor_cs_tutor.cpp:3285 */
CBaseEntity *CCSTutor::GetEntityForMessageID(int messageID, CBaseEntity *last)
{
	CBaseEntity *ret = NULL;

	switch (messageID)
	{
		case YOU_SEE_FRIEND:
		case YOU_SEE_ENEMY:
			ret = UTIL_FindEntityByClassname(last, "player");
			break;
		case YOU_SEE_FRIEND_CORPSE:
		{
			// TODO: this code is noxref
			// this code fucked my brain, in that pointer Vector * is passed through the CBaseEntity *

#if 1
			CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

			if (localPlayer != NULL)
			{
				if (m_clientCorpseList.empty())
				{
					return NULL;
				}

				ClientCorpseStruct *lastCorpse = NULL;
				ClientCorpseListIter iter;

				if (last != NULL)
				{
					iter = m_clientCorpseList.begin();

					while (iter != m_clientCorpseList.end())
					{
						lastCorpse = (*iter);

						if ((CBaseEntity *)lastCorpse == last)
						{
							break;
						}

						++iter;
					}

					while (iter != m_clientCorpseList.end())
					{
						ClientCorpseStruct *corpse = (*iter);

						if (corpse->m_team == localPlayer->m_iTeam)
						{
							return (CBaseEntity *)&corpse->m_position;
						}

						++iter;
					}

					return NULL;
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
			ret = UTIL_FindEntityByClassname(last, "weapon_c4");
			break;
		case YOU_SEE_PLANTED_BOMB_T:
		case YOU_SEE_PLANTED_BOMB_CT:
			ret = UTIL_FindEntityByClassname(last, "grenade");
			break;
		case YOU_SEE_LOOSE_WEAPON:
			ret = UTIL_FindEntityByClassname(last, "weaponbox");
			break;
		case YOU_SEE_LOOSE_DEFUSER:
			ret = UTIL_FindEntityByClassname(last, "item_thighpack");
			break;
		case YOU_SEE_HOSTAGE_T:
		case YOU_SEE_HOSTAGE_CT:
		case YOU_SEE_HOSTAGE_CT_EXAMINE:
			ret = UTIL_FindEntityByClassname(last, "hostage_entity");
			break;
	}

	return ret;
}

/* <215a44> ../cstrike/dlls/tutor_cs_tutor.cpp:3374 */
void CCSTutor::CheckHintMessages(float time)
{
	if (m_deadAirStartTime <= 0.0f || (time - m_deadAirStartTime <= cv_tutor_hint_interval_time.value))
	{
		return;
	}

	m_lastHintShown++;

	bool confusingHint = false;

	if (IsHostageMap())
	{
		if (m_lastHintShown > HINT_HOSTAGE_START)
		{
			confusingHint = true;
		}
	}

	if (!confusingHint)
	{
		if (IsBombMap() && m_lastHintShown < HINT_END)
		{
			if (m_lastHintShown == HINT_END)
			{
				m_lastHintShown = HINT_1;
			}
		}
	}

	if (m_lastHintShown > HINT_END)
	{
		m_lastHintShown = HINT_1;
	}

	TutorMessage *message = GetTutorMessageDefinition(m_lastHintShown);

	if (message != NULL)
	{
		CreateAndAddEventToList(m_lastHintShown);
	}
}

/* <215b23> ../cstrike/dlls/tutor_cs_tutor.cpp:3456 */
void CCSTutor::CheckInGameHintMessages(float time)
{
	if (m_deadAirStartTime <= 0.0f || (time - m_deadAirStartTime <= cv_tutor_hint_interval_time.value))
	{
		return;
	}

	m_lastInGameHintShown++;

	if (m_lastInGameHintShown <= INGAME_HINT_BEGIN || m_lastInGameHintShown >= INGAME_HINT_END)
	{
		return;
	}

	TutorMessage *message = GetTutorMessageDefinition(m_lastInGameHintShown);

	if (message != NULL)
	{
		CreateAndAddEventToList(m_lastInGameHintShown);
	}
}

/* <215b61> ../cstrike/dlls/tutor_cs_tutor.cpp:3493 */
void CCSTutor::CheckForNeedToReload(bool isPassiveCheck)
{
	CBasePlayer *localPlayer;
	CBasePlayerItem *currentItem;
	CBasePlayerWeapon *currentWeapon;
	ItemInfo itemInfo;

	localPlayer = UTIL_GetLocalPlayer();
	Q_memset(&itemInfo, 0, sizeof(itemInfo));

	if (localPlayer == NULL || !localPlayer->IsPlayer())
	{
		return;
	}

	currentItem = localPlayer->m_pActiveItem;

	if (currentItem == NULL || !currentItem->IsWeapon())
	{
		return;
	}

	currentWeapon = static_cast<CBasePlayerWeapon *>(currentItem);
	currentWeapon->GetItemInfo(&itemInfo);

	if (itemInfo.iSlot && itemInfo.iSlot != 1)
	{
		return;
	}

	if (localPlayer->m_rgAmmo[currentWeapon->m_iPrimaryAmmoType])
	{
		if (isPassiveCheck)
		{
			if (2 * currentWeapon->m_iClip < currentItem->iMaxClip() && !currentWeapon->m_fInReload)
			{
				CreateAndAddEventToList(YOU_SHOULD_RELOAD);
			}
		}
		else
		{
			if (5 * currentWeapon->m_iClip < currentItem->iMaxClip() && !currentWeapon->m_fInReload)
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_SHOULD_RELOAD);

				if (message != NULL)
				{
					message->m_lastCloseTime = 0;
				}

				CreateAndAddEventToList(YOU_SHOULD_RELOAD);
			}
			else
			{
				TutorMessage *message = GetTutorMessageDefinition(YOU_SHOULD_RELOAD);

				if (message != NULL)
				{
					message->m_lastCloseTime = gpGlobals->time;
				}
			}
		}
	}
	else if (!currentWeapon->m_iClip)
	{
		if (!isPassiveCheck)
		{
			TutorMessage *message = GetTutorMessageDefinition(YOU_ARE_OUT_OF_AMMO);

			if (message != NULL)
			{
				message->m_lastCloseTime = 0;
			}
		}

		CreateAndAddEventToList(YOU_ARE_OUT_OF_AMMO);
	}
}

/* <215d16> ../cstrike/dlls/tutor_cs_tutor.cpp:3568 */
void CCSTutor::CheckExamineMessages(float time)
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
		return;

	for (int i = 0; i < TUTOR_NUM_MESSAGES; ++i)
	{
		TutorMessage *message = GetTutorMessageDefinition(i);

		if (message == NULL || message->m_class != TUTORMESSAGECLASS_EXAMINE)
			continue;

		CBaseEntity *entity = NULL;
		bool isPlayerLooking = false;

		while ((entity = GetEntityForMessageID(i, entity)) != NULL)
		{
			if (i == YOU_SEE_FRIEND_CORPSE || i == YOU_SEE_ENEMY_CORPSE)
			{
				if (IsPlayerLookingAtPosition((Vector *)entity, localPlayer))
				{
					isPlayerLooking = true;
					break;
				}
			}
			else if (i == YOU_SEE_HOSTAGE_CT_EXAMINE || i == YOU_SEE_FRIEND || i == YOU_SEE_ENEMY)
			{
				if (IsPlayerLookingAtEntity(entity, localPlayer))
				{
					isPlayerLooking = true;
					break;
				}
			}
			else if (IsPlayerLookingAtPosition(&entity->pev->origin, localPlayer))
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
				CBasePlayer *player = static_cast<CBasePlayer *>(entity);

				if (player->IsPlayer() && player->IsAlive() && player->m_iTeam == localPlayer->m_iTeam)
					validEntity = true;
			}
			else if (i == YOU_SEE_ENEMY)
			{
				CBasePlayer *player = static_cast<CBasePlayer *>(entity);

				if (player->IsPlayer() && player->IsAlive() && player->m_iTeam == localPlayer->m_iTeam)
				{
					if ((player->m_iTeam != CT || localPlayer->m_iTeam == TERRORIST) && (player->m_iTeam != TERRORIST || localPlayer->m_iTeam == CT))
						validEntity = true;
				}
			}
			else if (i == YOU_SEE_HOSTAGE_CT_EXAMINE)
			{
				CHostage *hostage = static_cast<CHostage *>(entity);

				if (entity->pev->takedamage == DAMAGE_YES)
				{
					if (!hostage->IsFollowingSomeone())
						validEntity = true;
				}

				if (!hostage->IsValid() || !validEntity)
					continue;
			}

			if (validEntity)
			{
				CreateAndAddEventToList((TutorMessageID)i, entity);
			}
		}
		else
			message->m_examineStartTime = -1.0f;
	}
}

/* <215eec> ../cstrike/dlls/tutor_cs_tutor.cpp:3696 */
bool CCSTutor::CanLocalPlayerBuyStuff()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		return localPlayer->CanPlayerBuy();
	}

	return false;
}

/* <215f25> ../cstrike/dlls/tutor_cs_tutor.cpp:3714 */
void CCSTutor::CheckBuyZoneMessages()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL || m_currentlyShownMessageID == BUY_TIME_BEGIN)
	{
		return;
	}

	CBasePlayerWeapon *primary = static_cast<CBasePlayerWeapon *>(localPlayer->m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	CBasePlayerWeapon *secondary = static_cast<CBasePlayerWeapon *>(localPlayer->m_rgpPlayerItems[PISTOL_SLOT]);

	if (primary != NULL)
	{
		if (localPlayer->NeedsPrimaryAmmo() && localPlayer->CanAffordPrimaryAmmo())
		{
			TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_PRIMARY_AMMO);
			return;
		}
	}
	else
	{
		if (localPlayer->CanAffordPrimary())
		{
			TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_PRIMARY_WEAPON);
			return;
		}
	}

	if (secondary != NULL && localPlayer->NeedsSecondaryAmmo() && localPlayer->CanAffordSecondaryAmmo())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_SECONDARY_AMMO);
	}
	else if (localPlayer->NeedsArmor() && localPlayer->CanAffordArmor())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_ARMOR);
	}
	else if (localPlayer->NeedsDefuseKit() && localPlayer->CanAffordDefuseKit())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_DEFUSE_KIT);
	}
	else if (localPlayer->NeedsGrenade() && localPlayer->CanAffordGrenade())
	{
		TheTutor->OnEvent(EVENT_TUTOR_NEED_TO_BUY_GRENADE);
	}
	else
		TheTutor->OnEvent(EVENT_TUTOR_NOT_BUYING_ANYTHING);
}

/* <216cdd> ../cstrike/dlls/tutor_cs_tutor.cpp:3767 */
bool CCSTutor::IsHostageMap()
{
	return UTIL_FindEntityByClassname(NULL, "hostage_entity") != NULL;
}

/* <216d01> ../cstrike/dlls/tutor_cs_tutor.cpp:3773 */
bool CCSTutor::IsBombMap()
{
	CHalfLifeMultiplay *mpRules = g_pGameRules;

	return mpRules->m_bMapHasBombTarget;
}

/* <216d35> ../cstrike/dlls/tutor_cs_tutor.cpp:3781 */
void CCSTutor::ResetPlayerDeathInfo()
{
	for (int i = 0; i < ARRAYSIZE(m_playerDeathInfo); ++i)
	{
		m_playerDeathInfo[i].m_hasBeenShown = false;
		m_playerDeathInfo[i].m_event = NULL;
	}
}

/* <216d6d> ../cstrike/dlls/tutor_cs_tutor.cpp:3795 */
void CCSTutor::ConstructRecentDeathsList(TeamName team, char *buf, int buflen, TutorMessageEvent *event)
{
	if (!buf || !buflen)
	{
		return;
	}

	char scratch[32];
	buf[0] = '\0';

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *pPlayer = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (pPlayer == NULL)
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

/* <216dc2> ../cstrike/dlls/tutor_cs_tutor.cpp:3853 */
void CCSTutor::TransferDeathEvents(TutorMessageEvent *oldEvent, TutorMessageEvent *newEvent)
{
	for (int i = 0; i < ARRAYSIZE(m_playerDeathInfo); ++i)
	{
		if (m_playerDeathInfo[i].m_event == oldEvent)
		{
			m_playerDeathInfo[i].m_event = newEvent;
		}
	}
}
