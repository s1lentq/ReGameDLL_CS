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

#else // HOOK_GAMEDLL

const char *TutorIdentifierList[150];

#endif // HOOK_GAMEDLL

/* <212575> ../cstrike/dlls/tutor_cs_tutor.cpp:197 */
NOBODY CCSTutor::CCSTutor(void)
{
//	map(map<std::basic_string<char, std::char_traits<char>, std::allocator<char>>, TutorMessage*, std::less<std::basic_string<chconst this);  //   197
//	vector(vector<ClientCorpseStruct*, std::allocator<ClientCorpseStruct*>> *const this);  //   197
//	ApplyPersistentDecay(CCSTutor *const this);  //   216
//	ResetPlayerDeathInfo(CCSTutor *const this);  //   218
}

/* <217e69> ../cstrike/dlls/tutor_cs_tutor.cpp:221 */
NOBODY CCSTutor::~CCSTutor(void)
{
//	DeleteEvent(CCSTutor::~CCSTutor(//			class TutorMessageEvent *event);  //   231
//	DeleteEvent(CCSTutor *const this,
//			class TutorMessageEvent *event);  //   237
//	ClearEventList(CCSTutor *const this);  //   243
//	~vector(vector<ClientCorpseStruct*, std::allocator<ClientCorpseStruct*>> *const this,
//		int const __in_chrg);  //   221
//	~map(map<std::basic_string<char, std::char_traits<char>, std::allocator<char>>, TutorMessage*, std::less<std::basic_string<chconst this,
//		int const __in_chrg);  //   221
}

/* <21066a> ../cstrike/dlls/tutor_cs_tutor.cpp:246 */
NOBODY void ParseMessageParameters(const char *&messageData, TutorMessage *ret)
{
//	{
//		char *token;                                         //   248
//		atof(const char *__nptr);  //   397
//		atoi(const char *__nptr);  //   267
//		atoi(const char *__nptr);  //   274
//		atoi(const char *__nptr);  //   313
//		atoi(const char *__nptr);  //   362
//		atoi(const char *__nptr);  //   369
//		atof(const char *__nptr);  //   390
//	}
}

/* <20ffde> ../cstrike/dlls/tutor_cs_tutor.cpp:405 */
NOXREF TutorMessage *ConstructTutorMessage(const char *&messageData, TutorMessage *defaults)
{
	// TODO: used in ReadTutorMessageFile
	//TutorMessage *ret = new [sizeof(TutorMessage)];
	//memcpy(ret, defaults, sizeof(TutorMessage));
	//ParseMessageParameters(messageData, ret);
	//return ret;
}

/* <21005d> ../cstrike/dlls/tutor_cs_tutor.cpp:431 */
NOBODY void ReadDefaultValues(const char *&messageData, TutorMessage *defaults)
{
}

/* <21164e> ../cstrike/dlls/tutor_cs_tutor.cpp:436 */
NOBODY void CCSTutor::ReadTutorMessageFile(void)
{
//	{
//		int messageFileLen;                                   //   438
//		char *messageFile;                                   //   439
//		char *messageData;                                   //   440
//		class TutorMessage defaultMessage;                    //   451
//		{
//			char *token;                                 //   472
//			{
//				string identifier;                    //   476
//				class TutorMessage *tm;              //   479
//				basic_string(basic_string<char, std::char_traits<char>, std::allocator<char>> *const this);  //   476
//				operator=(basic_string<char, std::char_traits<char>, std::allocator<char>> *const this,
//						const char *__s);  //   477
//				ConstructTutorMessage(char *&const messageData,
//							class TutorMessage *defaults);  //   479
//				operator[](map<std::basic_string<char, std::char_traits<char>, std::allocator<char>>, TutorMessage*, std::less<std::basic_string<chconst this,
//						const key_type &__k);  //   480
//				~basic_string(basic_string<char, std::char_traits<char>, std::allocator<char>> *const this,
//						int const __in_chrg);  //   476
//			}
//			ReadDefaultValues(char *&const messageData,
//						class TutorMessage *defaults);  //   484
//		}
//	}
}

/* <2126f8> ../cstrike/dlls/tutor_cs_tutor.cpp:491 */
NOBODY void CCSTutor::ApplyPersistentDecay(void)
{
//	{
//		enum TutorMessageID mid;                              //   493
//		{
//			class TutorMessage *definition;              //   497
//			{
//				int timesShown;                       //   500
//			}
//		}
//	}
}

/* <21275b> ../cstrike/dlls/tutor_cs_tutor.cpp:511 */
NOBODY bool CCSTutor::HasCurrentWindowBeenActiveLongEnough(float time)
{
}

/* <212787> ../cstrike/dlls/tutor_cs_tutor.cpp:528 */
NOBODY bool CCSTutor::ShouldShowMessageEvent(TutorMessageEvent *event, float time)
{
//	{
//		class TutorMessage *message;                         //   535
//		class TutorMessage *current;                         //   571
//		HasCurrentWindowBeenActiveLongEnough(CCSTutor *const this,
//							float time);  //   566
//	}
}

/* <21362f> ../cstrike/dlls/tutor_cs_tutor.cpp:597 */
NOBODY void CCSTutor::CheckForInterruptingMessageEvent(float time)
{
//	{
//		bool newEvent;                                        //   599
//		class TutorMessageEvent *event;                      //   600
//		class TutorMessage *oldMessage;                      //   602
//		class TutorMessageEvent *oldEvent;                   //   604
//		ProcessShownDeathsForEvent(CCSTutor *const this,
//						class TutorMessageEvent *event);  //   626
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //   627
//	}
}

/* <215ff3> ../cstrike/dlls/tutor_cs_tutor.cpp:642 */
NOBODY void CCSTutor::TutorThink_(float time)
{
//	CheckForWindowClose(CCSTutor *const this,
//				float time);  //   684
//	CheckForContentUpdate(CCSTutor *const this);  //   685
//	CheckInGameHintMessages(CCSTutor *const this,
//				float time);  //   659
//	CanLocalPlayerBuyStuff(CCSTutor *const this);  //   669
//	CanLocalPlayerBuyStuff(CCSTutor *const this);  //   675
//	CanLocalPlayerBuyStuff(CCSTutor *const this);  //   663
}

/* <213556> ../cstrike/dlls/tutor_cs_tutor.cpp:691 */
NOBODY void CCSTutor::CheckForWindowClose(float time)
{
//	{
//		class TutorMessageEvent *event;                      //   700
//		GetTutorMessageUpdateEvent(CCSTutor *const this);  //   700
//	}
}

/* <2134a7> ../cstrike/dlls/tutor_cs_tutor.cpp:715 */
NOBODY void CCSTutor::CheckForContentUpdate(void)
{
//	{
//		class TutorMessage *definition;                      //   722
//		class TutorMessageEvent *event;                      //   733
//		GetTutorMessageUpdateEvent(CCSTutor *const this);  //   733
//	}
}

/* <21281f> ../cstrike/dlls/tutor_cs_tutor.cpp:744 */
NOBODY void CCSTutor::ClearCurrentEvent(bool closeWindow, bool processDeathsForEvent)
{
//	{
//		class TutorMessage *oldMessage;                      //   746
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //   769
//		ProcessShownDeathsForEvent(CCSTutor *const this,
//						class TutorMessageEvent *event);  //   756
//	}
}

// OVERLOADED?
/* <210812> ../cstrike/dlls/tutor_cs_tutor.cpp:744 */
//void CCSTutor::ClearCurrentEvent(bool processDeathsForEvent, bool closeWindow)
//{
//	{
//		class TutorMessage *oldMessage;                      //   746
//		ProcessShownDeathsForEvent(CCSTutor *const this,
//						class TutorMessageEvent *event);  //   756
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //   769
//	}
//}

/* <2128d0> ../cstrike/dlls/tutor_cs_tutor.cpp:775 */
NOBODY void CCSTutor::ProcessShownDeathsForEvent(TutorMessageEvent *event)
{
//	{
//		int i;                                                //   782
//	}
}

/* <212949> ../cstrike/dlls/tutor_cs_tutor.cpp:794 */
NOBODY TutorMessageEvent *CCSTutor::GetTutorMessageUpdateEvent(void)
{
//	{
//		class TutorMessage *definition;                      //   796
//		class TutorMessageEvent *event;                      //   802
//	}
}

/* <212988> ../cstrike/dlls/tutor_cs_tutor.cpp:816 */
NOBODY bool CCSTutor::GetDuplicateMessagesFromEventList(const TutorMessageEvent *&event1, const TutorMessageEvent *&event2)
{
}

/* <212f62> ../cstrike/dlls/tutor_cs_tutor.cpp:836 */
NOBODY void CCSTutor::CheckForInactiveEvents(float time)
{
//	{
//		class TutorMessageEvent *event;                      //   838
//		class TutorMessageEvent *event1;                     //   859
//		class TutorMessageEvent *event2;                     //   860
//		bool foundDup;                                        //   861
//		{
//			class TutorMessageEvent *temp;               //   845
//			DeleteEvent(CCSTutor *const this,
//					class TutorMessageEvent *event);  //   849
//		}
//		TransferDeathEvents(CCSTutor *const this,
//					class TutorMessageEvent *oldEvent,
//					class TutorMessageEvent *newEvent);  //   868
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //   870
//		TransferDeathEvents(CCSTutor *const this,
//					class TutorMessageEvent *oldEvent,
//					class TutorMessageEvent *newEvent);  //   875
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //   877
//	}
}

/* <21314d> ../cstrike/dlls/tutor_cs_tutor.cpp:886 */
NOBODY void CCSTutor::CancelEvent(TutorMessageID mid)
{
//	{
//		class TutorMessageEvent *event;                      //   895
//		{
//			class TutorMessageEvent *temp;               //   900
//			DeleteEvent(CCSTutor *const this,
//					class TutorMessageEvent *event);  //   903
//		}
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //   914
//	}
}

/* <2129db> ../cstrike/dlls/tutor_cs_tutor.cpp:920 */
NOBODY void CCSTutor::LookupHotKey(TutorMessageID mid, int paramNum, wchar_t *buf, int buflen)
{
}

/* <212aa0> ../cstrike/dlls/tutor_cs_tutor.cpp:930 */
NOBODY TutorMessageEvent *CCSTutor::CreateTutorMessageEvent(TutorMessageID mid, CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //   932
//		class TutorMessage *message;                         //   938
//		class TutorMessageEvent *event;                      //   944
//		{
//			int numT;                                     //  1018
//			int numCT;                                    //  1019
//			char numTStr;                                 //  1022
//			char numCTStr;                                //  1025
//			GetNumPlayersAliveOnTeams(CCSTutor *const this,
//							int &numT,
//							int &numCT);  //  1020
//		}
//		{
//			char enemyList;                               //  1057
//		}
//		{
//			char numLeftStr;                              //  1079
//			int numtasks;                                 //  1081
//		}
//		{
//			int numT;                                     //   958
//			int numCT;                                    //   959
//			char numTStr;                                 //   975
//			char numCTStr;                                //   978
//			GetNumPlayersAliveOnTeams(CCSTutor *const this,
//							int &numT,
//							int &numCT);  //   960
//		}
//		{
//			char teammateList;                            //  1006
//		}
//	}
}

/* <212d3b> ../cstrike/dlls/tutor_cs_tutor.cpp:1108 */
NOBODY void CCSTutor::CreateAndAddEventToList(TutorMessageID mid, CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class TutorMessageEvent *event;                      //  1110
//		class TutorMessage *message;                         //  1117
//		AddToEventList(CCSTutor *const this,
//				class TutorMessageEvent *event);  //  1132
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //  1124
//	}
}

/* <212e1a> ../cstrike/dlls/tutor_cs_tutor.cpp:1136 */
NOBODY void CCSTutor::DeleteEventFromEventList(TutorMessageEvent *event)
{
//	{
//		class TutorMessageEvent *temp;                       //  1143
//	}
//	DeleteEventFromEventList(CCSTutor *const this,
//				class TutorMessageEvent *event);  //  1136
}

/* <213215> ../cstrike/dlls/tutor_cs_tutor.cpp:1163 */
NOBODY void CCSTutor::ClearEventList(void)
{
//	{
//		class TutorMessageEvent *temp;                       //  1165
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //  1169
//	}
}

/* <213289> ../cstrike/dlls/tutor_cs_tutor.cpp:1175 */
NOBODY void CCSTutor::DeleteEvent(TutorMessageEvent *event)
{
//	{
//		int i;                                                //  1177
//	}
}

/* <210a17> ../cstrike/dlls/tutor_cs_tutor.cpp:1189 */
NOBODY void CCSTutor::PurgeMessages_(void)
{
//	ClearEventList(CCSTutor *const this);  //  1192
//	DeleteEvent(CCSTutor *const this,
//			class TutorMessageEvent *event);  //  1196
}

/* <212d0e> ../cstrike/dlls/tutor_cs_tutor.cpp:1096 */
NOBODY void CCSTutor::AddToEventList(TutorMessageEvent *event)
{
}

/* <2132ca> ../cstrike/dlls/tutor_cs_tutor.cpp:1203 */
NOBODY void CCSTutor::ComputeDisplayTimesForMessage(void)
{
//	{
//		float now;                                            //  1205
//		class TutorMessage *message;                         //  1207
//		int stringLength;                                     //  1218
//		float minShowTime;                                    //  1219
//	}
}

/* <21333e> ../cstrike/dlls/tutor_cs_tutor.cpp:1241 */
NOBODY bool CCSTutor::ShouldUpdateCurrentMessage(TutorMessageID messageID)
{
//	{
//		class TutorMessage *definition;                      //  1249
//	}
}

/* <213393> ../cstrike/dlls/tutor_cs_tutor.cpp:1259 */
NOBODY void CCSTutor::UpdateCurrentMessage(TutorMessageEvent *event)
{
//	{
//		class TutorMessage *definition;                      //  1274
//		class CBasePlayer *localPlayer;                      //  1280
//		TransferDeathEvents(CCSTutor *const this,
//					class TutorMessageEvent *oldEvent,
//					class TutorMessageEvent *newEvent);  //  1261
//		DeleteEvent(CCSTutor *const this,
//				class TutorMessageEvent *event);  //  1266
//	}
}

/* <21060a> ../cstrike/dlls/tutor_cs_tutor.cpp:1299 */
NOBODY void CCSTutor::ShowTutorMessage_(TutorMessageEvent *event)
{
//	{
//		enum TutorMessageID mid;                              //  1301
//		class TutorMessage *message;                         //  1307
//	}
}

/* <2135cc> ../cstrike/dlls/tutor_cs_tutor.cpp:1324 */
NOBODY void CCSTutor::ConstructMessageAndDisplay(void)
{
//	{
//		class CBasePlayer *pLocalPlayer;                     //  1326
//		enum TutorMessageID mid;                              //  1338
//		class TutorMessage *message;                         //  1343
//	}
}

/* <2161ea> ../cstrike/dlls/tutor_cs_tutor.cpp:1356 */
NOBODY void CCSTutor::CallEventHandler_(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	HandleRadioGetOutOfThere(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1536
//	HandleBombPlanted(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1395
//	HandleRadioReportingIn(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1532
//	HandleRadioInPosition(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1528
//	HandleRadioSectorClear(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1524
//	HandleRadioNeedBackup(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1520
//	HandleRadioEnemySpotted(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1516
//	HandleRadioAffirmative(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1512
//	HandleRadioReportInTeam(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1508
//	HandleRadioStormTheFront(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1504
//	HandleRadioGetInPositionAndWait(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1500
//	HandleRadioStickTogetherTeam(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1496
//	HandleRadioTeamFallBack(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1492
//	HandleRadioGoGoGo(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1488
//	HandleRadioTakingFire(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1484
//	HandleRadioFollowMe(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1480
//	HandleRadioRegroupTeam(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1476
//	HandleRadioHoldThisPosition(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1472
//	HandleRadioYouTakeThePoint(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1468
//	HandleRadioCoverMe(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1464
//	HandleCareerTaskDone(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1585
//	HandleNeedToBuyGrenade(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1581
//	HandleNeedToBuyDefuseKit(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1577
//	HandleNeedToBuyArmor(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1573
//	HandleNeedToBuySecondaryAmmo(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1569
//	HandleNeedToBuyPrimaryAmmo(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1565
//	HandleNeedToBuyPrimaryWeapon(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1561
//	HandleNotBuyingAnything(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1557
//	HandleAutoBuy(CCSTutor *const this,
//			class CBaseEntity *entity,
//			class CBaseEntity *other);  //  1553
//	HandleBuyMenuOpenned(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1549
//	HandleDeathCameraStart(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1459
//	HandleRadioNegative(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1540
//	HandlePlayerSpawned(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1378
//	HandleRoundDraw(CCSTutor *const this,
//			class CBaseEntity *entity,
//			class CBaseEntity *other);  //  1447
//	HandleCTWin(CCSTutor *const this,
//			class CBaseEntity *entith,
//			class CBaseEntity *other);  //  1451
//	HandleTWin(CCSTutor *const this,
//			class CBaseEntity *entity,
//			class CBaseEntity *other);  //  1455
//	HandleAllHostagesRescued(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1435
//	HandlePlayerBlindedByFlashbang(CCSTutor *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //  1411
//	HandleBeingShotAt(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1403
//	HandleWeaponReloaded(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1370
//	HandleWeaponFired(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1362
//	HandleRadioEnemyDown(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1544
//	HandleBombDefusing(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1415
//	HandleBombExploded(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1423
//	HandleHostageDamaged(CCSTutor *const this,
//				class CBaseEntity *entity,
//				class CBaseEntity *other);  //  1439
}

/* <215cc0> ../cstrike/dlls/tutor_cs_tutor.cpp:1594 */
NOBODY void CCSTutor::HandleWeaponFired(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  1597
//		class CBasePlayer *target;                           //  1598
//		class CBasePlayer *localPlayer;                      //  1599
//	}
}

/* <21371d> ../cstrike/dlls/tutor_cs_tutor.cpp:1616 */
NOBODY void CCSTutor::HandleWeaponFiredOnEmpty(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  1618
//		class CBasePlayer *player;                           //  1629
//		{
//			class CBasePlayerWeapon *currentWeapon;      //  1635
//			{
//				class TutorMessage *message;         //  1641
//			}
//		}
//	}
}

/* <213817> ../cstrike/dlls/tutor_cs_tutor.cpp:1654 */
NOBODY void CCSTutor::HandleWeaponReloaded(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  1661
//	}
}

/* <21385d> ../cstrike/dlls/tutor_cs_tutor.cpp:1673 */
NOBODY void CCSTutor::HandlePlayerDied(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *victim;                           //  1675
//		class CBasePlayer *killer;                           //  1676
//		class CBasePlayer *localPlayer;                      //  1678
//		int numT;                                             //  1717
//		int numCT;                                            //  1717
//		GetNumPlayersAliveOnTeams(CCSTutor *const this,
//						int &numT,
//						int &numCT);  //  1718
//	}
}

/* <21394c> ../cstrike/dlls/tutor_cs_tutor.cpp:1945 */
NOBODY void CCSTutor::HandlePlayerTookDamage(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  1947
//		class CBasePlayer *victim;                           //  1953
//		class CBasePlayer *attacker;                         //  1954
//	}
}

/* <213a21> ../cstrike/dlls/tutor_cs_tutor.cpp:1985 */
NOBODY void CCSTutor::HandlePlayerBlindedByFlashbang(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  1992
//		class CBasePlayer *player;                           //  1998
//	}
}

/* <213ab7> ../cstrike/dlls/tutor_cs_tutor.cpp:2008 */
NOBODY void CCSTutor::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  2015
//	}
}

/* <21868e> ../cstrike/dlls/tutor_cs_tutor.cpp:2033 */
NOBODY void CCSTutor::HandleClientCorpseSpawned(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  2040
//		class ClientCorpseStruct *corpse;                    //  2042
//		push_back(vector<ClientCorpseStruct*, std::allocator<ClientCorpseStruct*>> *const this,
//				const value_type &__x);  //  2047
//	}
}

/* <215fbd> ../cstrike/dlls/tutor_cs_tutor.cpp:2050 */
NOBODY void CCSTutor::HandleBuyMenuOpenned(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <213b32> ../cstrike/dlls/tutor_cs_tutor.cpp:2060 */
NOBODY void CCSTutor::HandleAutoBuy(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <213b67> ../cstrike/dlls/tutor_cs_tutor.cpp:2069 */
NOBODY void CCSTutor::HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <213b9c> ../cstrike/dlls/tutor_cs_tutor.cpp:2074 */
NOBODY void CCSTutor::HandlePlayerLeftBuyZone(CBaseEntity *entity, CBaseEntity *other)
{
//	ClearEventList(CCSTutor *const this);  //  2078
//	AddToEventList(CCSTutor *const this,
//			class TutorMessageEvent *event);  //  2083
}

/* <213cbb> ../cstrike/dlls/tutor_cs_tutor.cpp:2092 */
NOBODY void CCSTutor::HandleBombPlanted(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  2094
//	}
}

/* <213d02> ../cstrike/dlls/tutor_cs_tutor.cpp:2112 */
NOBODY void CCSTutor::HandleBombDefused(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2114
//		class CBasePlayer *defuser;                          //  2120
//	}
}

/* <213dc6> ../cstrike/dlls/tutor_cs_tutor.cpp:2148 */
NOBODY void CCSTutor::HandleBombDefusing(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2150
//		class CBasePlayer *player;                           //  2161
//	}
}

/* <213e5b> ../cstrike/dlls/tutor_cs_tutor.cpp:2172 */
NOBODY void CCSTutor::HandleBombExploded(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2174
//	}
}

/* <213ebd> ../cstrike/dlls/tutor_cs_tutor.cpp:2191 */
NOBODY void CCSTutor::HandleRoundStart(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  2194
//		IsBombMap(CCSTutor *const this);  //  2200
//		IsHostageMap(CCSTutor *const this);  //  2222
//	}
}

/* <213fc1> ../cstrike/dlls/tutor_cs_tutor.cpp:2239 */
NOBODY void CCSTutor::HandleBeingShotAt(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *player;                           //  2246
//		class CBasePlayer *localPlayer;                      //  2247
//	}
}

/* <2158b5> ../cstrike/dlls/tutor_cs_tutor.cpp:2265 */
NOBODY void CCSTutor::HandleHostageUsed(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2267
//		bool unusedHostages;                                  //  2278
//		class CBasePlayer *activator;                        //  2280
//	}
}

/* <214011> ../cstrike/dlls/tutor_cs_tutor.cpp:2307 */
NOBODY void CCSTutor::HandleHostageRescued(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2309
//		class CBasePlayer *rescuer;                          //  2320
//	}
}

/* <2140c8> ../cstrike/dlls/tutor_cs_tutor.cpp:2342 */
NOBODY void CCSTutor::HandleAllHostagesRescued(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2344
//	}
}

/* <214161> ../cstrike/dlls/tutor_cs_tutor.cpp:2361 */
NOBODY void CCSTutor::HandleHostageDamaged(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2363
//		class CBasePlayer *attacker;                         //  2380
//	}
}

/* <2157fb> ../cstrike/dlls/tutor_cs_tutor.cpp:2389 */
NOBODY void CCSTutor::HandleHostageKilled(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2391
//		class CBasePlayer *attacker;                         //  2410
//		bool unusedHostages;                                  //  2417
//		CheckForAllHostagesDead(CCSTutor *const this);  //  2397
//	}
}

/* <2141f5> ../cstrike/dlls/tutor_cs_tutor.cpp:2433 */
NOBODY void CCSTutor::HandleRoundDraw(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  2435
//		ResetPlayerDeathInfo(CCSTutor *const this);  //  2441
//	}
}

/* <21429a> ../cstrike/dlls/tutor_cs_tutor.cpp:2445 */
NOBODY void CCSTutor::HandleCTWin(CBaseEntity *entith, CBaseEntity *other)
{
//	ResetPlayerDeathInfo(CCSTutor *const this);  //  2449
}

/* <214335> ../cstrike/dlls/tutor_cs_tutor.cpp:2453 */
NOBODY void CCSTutor::HandleTWin(CBaseEntity *entity, CBaseEntity *other)
{
//	ResetPlayerDeathInfo(CCSTutor *const this);  //  2457
}

/* <2143ed> ../cstrike/dlls/tutor_cs_tutor.cpp:2461 */
NOBODY void CCSTutor::HandleDeathCameraStart(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2463
//		class CBasePlayer *player;                           //  2474
//	}
}

/* <214472> ../cstrike/dlls/tutor_cs_tutor.cpp:2487 */
NOBODY void CCSTutor::HandleRadioCoverMe(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <2144dd> ../cstrike/dlls/tutor_cs_tutor.cpp:2492 */
NOBODY void CCSTutor::HandleRadioYouTakeThePoint(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214548> ../cstrike/dlls/tutor_cs_tutor.cpp:2497 */
NOBODY void CCSTutor::HandleRadioHoldThisPosition(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <2145b3> ../cstrike/dlls/tutor_cs_tutor.cpp:2502 */
NOBODY void CCSTutor::HandleRadioRegroupTeam(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <21461e> ../cstrike/dlls/tutor_cs_tutor.cpp:2507 */
NOBODY void CCSTutor::HandleRadioFollowMe(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214689> ../cstrike/dlls/tutor_cs_tutor.cpp:2512 */
NOBODY void CCSTutor::HandleRadioTakingFire(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <2146f4> ../cstrike/dlls/tutor_cs_tutor.cpp:2517 */
NOBODY void CCSTutor::HandleRadioGoGoGo(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <21475f> ../cstrike/dlls/tutor_cs_tutor.cpp:2522 */
NOBODY void CCSTutor::HandleRadioTeamFallBack(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <2147ca> ../cstrike/dlls/tutor_cs_tutor.cpp:2527 */
NOBODY void CCSTutor::HandleRadioStickTogetherTeam(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214835> ../cstrike/dlls/tutor_cs_tutor.cpp:2532 */
NOBODY void CCSTutor::HandleRadioGetInPositionAndWait(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <2148a0> ../cstrike/dlls/tutor_cs_tutor.cpp:2537 */
NOBODY void CCSTutor::HandleRadioStormTheFront(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <21490b> ../cstrike/dlls/tutor_cs_tutor.cpp:2542 */
NOBODY void CCSTutor::HandleRadioReportInTeam(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214976> ../cstrike/dlls/tutor_cs_tutor.cpp:2547 */
NOBODY void CCSTutor::HandleRadioAffirmative(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <2149e1> ../cstrike/dlls/tutor_cs_tutor.cpp:2552 */
NOBODY void CCSTutor::HandleRadioEnemySpotted(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214a4c> ../cstrike/dlls/tutor_cs_tutor.cpp:2557 */
NOBODY void CCSTutor::HandleRadioNeedBackup(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214ab7> ../cstrike/dlls/tutor_cs_tutor.cpp:2562 */
NOBODY void CCSTutor::HandleRadioSectorClear(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214b22> ../cstrike/dlls/tutor_cs_tutor.cpp:2567 */
NOBODY void CCSTutor::HandleRadioInPosition(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214b8d> ../cstrike/dlls/tutor_cs_tutor.cpp:2572 */
NOBODY void CCSTutor::HandleRadioReportingIn(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214bf8> ../cstrike/dlls/tutor_cs_tutor.cpp:2577 */
NOBODY void CCSTutor::HandleRadioGetOutOfThere(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214c63> ../cstrike/dlls/tutor_cs_tutor.cpp:2582 */
NOBODY void CCSTutor::HandleRadioNegative(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214cce> ../cstrike/dlls/tutor_cs_tutor.cpp:2587 */
NOBODY void CCSTutor::HandleRadioEnemyDown(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214d39> ../cstrike/dlls/tutor_cs_tutor.cpp:2592 */
NOBODY void CCSTutor::HandleNotBuyingAnything(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214da4> ../cstrike/dlls/tutor_cs_tutor.cpp:2597 */
NOBODY void CCSTutor::HandleNeedToBuyPrimaryWeapon(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214e0f> ../cstrike/dlls/tutor_cs_tutor.cpp:2602 */
NOBODY void CCSTutor::HandleNeedToBuyPrimaryAmmo(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214e7a> ../cstrike/dlls/tutor_cs_tutor.cpp:2607 */
NOBODY void CCSTutor::HandleNeedToBuySecondaryAmmo(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214ee5> ../cstrike/dlls/tutor_cs_tutor.cpp:2612 */
NOBODY void CCSTutor::HandleNeedToBuyArmor(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214f50> ../cstrike/dlls/tutor_cs_tutor.cpp:2617 */
NOBODY void CCSTutor::HandleNeedToBuyDefuseKit(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <214fbb> ../cstrike/dlls/tutor_cs_tutor.cpp:2622 */
NOBODY void CCSTutor::HandleNeedToBuyGrenade(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <215036> ../cstrike/dlls/tutor_cs_tutor.cpp:2627 */
NOBODY void CCSTutor::HandleCareerTaskDone(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		int numTasksRemaining;                                //  2629
//	}
}

/* <2108c4> ../cstrike/dlls/tutor_cs_tutor.cpp:2650 */
NOBODY void CCSTutor::HandleShotFired_(Vector source, Vector target)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2652
//		float d1;                                             //  2659
//		float d;                                              //  2666
//		float angle;                                          //  2667
//		float FiringLineDistanceToPlayer;                     //  2668
//		operator-(const Vector *const this,
//				const Vector &v);  //  2659
//		Length(const Vector *const this);  //  2659
//		operator-(const Vector *const this,
//				const Vector &v);  //  2670
//		Length(const Vector *const this);  //  2670
//	}
}

/* <21507d> ../cstrike/dlls/tutor_cs_tutor.cpp:2720 */
NOBODY void CCSTutor::GetNumPlayersAliveOnTeams(int &numT, int &numCT)
{
//	{
//		int i;                                                //  2726
//		{
//			class CBasePlayer *player;                   //  2728
//		}
//	}
}

/* <2150d5> ../cstrike/dlls/tutor_cs_tutor.cpp:2749 */
NOBODY void CCSTutor::CheckForLooseWeaponViewable(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2751
//		class CBaseEntity *weapon;                           //  2757
//		bool sawFirst;                                        //  2758
//		class TutorMessage *message;                         //  2761
//	}
}

/* <21514d> ../cstrike/dlls/tutor_cs_tutor.cpp:2787 */
NOBODY void CCSTutor::CheckForLooseDefuserViewable(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2789
//		class TutorMessage *message;                         //  2797
//		class CBaseEntity *defuser;                          //  2803
//		bool sawFirst;                                        //  2804
//	}
}

/* <2151c1> ../cstrike/dlls/tutor_cs_tutor.cpp:2826 */
NOBODY void CCSTutor::CheckForBombViewable(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2828
//		class CBaseEntity *bomb;                             //  2835
//		class CBasePlayer *bombCarrier;                      //  2870
//		{
//			class TutorMessage *message;                 //  2856
//		}
//		{
//			class TutorMessage *message;                 //  2844
//		}
//		{
//			int i;                                        //  2872
//			{
//				class CBasePlayer *player;           //  2874
//			}
//		}
//		{
//			class TutorMessage *message;                 //  2946
//		}
//		{
//			class TutorMessage *message;                 //  2934
//		}
//		{
//			class TutorMessage *message;                 //  2915
//		}
//		{
//			class TutorMessage *message;                 //  2903
//		}
//	}
}

/* <215431> ../cstrike/dlls/tutor_cs_tutor.cpp:2959 */
NOBODY void CCSTutor::CheckForBombsiteViewable(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  2961
//		enum TutorMessageID mid;                              //  2967
//		class TutorMessage *definition;                      //  2991
//		class CBaseEntity *bombTarget;                       //  2998
//		bool sawFirst;                                        //  3000
//	}
}

/* <21534e> ../cstrike/dlls/tutor_cs_tutor.cpp:3026 */
NOBODY TutorMessageID CCSTutor::CheckForInBombZone(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3028
//		enum TutorMessageID mid;                              //  3034
//		class CBaseEntity *bombTarget;                       //  3044
//		bool sawFirst;                                        //  3046
//		IsBombPlantedInBombsite(CCSTutor *const this,
//					class CBaseEntity *bombTarget);  //  3053
//		IsBombPlantedInBombsite(CCSTutor *const this,
//					class CBaseEntity *bombTarget);  //  3067
//	}
}

/* <2154b6> ../cstrike/dlls/tutor_cs_tutor.cpp:3078 */
NOBODY bool CCSTutor::IsBombPlantedInBombsite(CBaseEntity *bombTarget)
{
//	{
//		class CGrenade *bomb;                                //  3081
//	}
}

/* <2154f4> ../cstrike/dlls/tutor_cs_tutor.cpp:3102 */
NOBODY void CCSTutor::CheckForHostageViewable(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3104
//		class CBaseEntity *hostageEntity;                    //  3110
//		bool sawFirst;                                        //  3111
//		{
//			bool validHostage;                            //  3117
//			class CHostage *hostage;                     //  3118
//			IsFollowingSomeone(CHostage *const this);  //  3119
//			{
//				class TutorMessage *message;         //  3151
//			}
//			{
//				class TutorMessage *message;         //  3139
//			}
//			IsValid(CHostage *const this);  //  3123
//		}
//	}
}

/* <215646> ../cstrike/dlls/tutor_cs_tutor.cpp:3168 */
NOBODY void CCSTutor::CheckForTimeRunningOut(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3170
//		class CHalfLifeMultiplay *mpRules;                   //  3176
//		TimeRemaining(CHalfLifeMultiplay *const this);  //  3185
//		IsHostageMap(CCSTutor *const this);  //  3202
//	}
}

/* <2156fd> ../cstrike/dlls/tutor_cs_tutor.cpp:3218 */
NOBODY void CCSTutor::CheckForAllHostagesDead(void)
{
//	{
//		bool foundLiveOne;                                    //  3220
//		class CBaseEntity *hostage;                          //  3222
//	}
}

/* <21573c> ../cstrike/dlls/tutor_cs_tutor.cpp:3242 */
NOBODY bool CCSTutor::CheckForAllHostagesFollowingSomeone(void)
{
//	{
//		bool foundUnusedOne;                                  //  3244
//		class CHostage *hostage;                             //  3246
//		IsFollowingSomeone(CHostage *const this);  //  3251
//	}
}

/* <210b98> ../cstrike/dlls/tutor_cs_tutor.cpp:3268 */
NOBODY TutorMessage *CCSTutor::GetTutorMessageDefinition_(int messageID)
{
//	{
//		TutorMessageMapIter iter;                             //  3275
//		find(map<std::basic_string<char, std::char_traits<char>, std::allocator<char>>, TutorMessage*, std::less<std::basic_string<chconst this,
//			const key_type &__x);  //  3275
//		~basic_string(basic_string<char, std::char_traits<char>, std::allocator<char>> *const this,
//				int const __in_chrg);  //  3275
//	}
}

/* <215938> ../cstrike/dlls/tutor_cs_tutor.cpp:3285 */
NOBODY CBaseEntity *CCSTutor::GetEntityForMessageID(int messageID, CBaseEntity *last)
{
//	{
//		class CBaseEntity *ret;                              //  3287
//		{
//			class CBasePlayer *localPlayer;              //  3323
//			class ClientCorpseStruct *lastCorpse;        //  3334
//			ClientCorpseListIter iter;                    //  3340
//			{
//				class ClientCorpseStruct *corpse;    //  3343
//				operator++(__normal_iterator<ClientCorpseStruct**, std::vector<ClientCorpseStruct*, std::allocator<ClientCorpseStruct*>> > *const this,
//						int);  //  3353
//				operator++(__normal_iterator<ClientCorpseStruct**, std::vector<ClientCorpseStruct*, std::allocator<ClientCorpseStruct*>> > *const this,
//						int);  //  3346
//			}
//			empty(const class vector<ClientCorpseStruct*, std::allocator<ClientCorpseStruct*>> *const this);  //  3329
//		}
//	}
}

/* <215a44> ../cstrike/dlls/tutor_cs_tutor.cpp:3374 */
NOBODY void CCSTutor::CheckHintMessages(float time)
{
//	{
//		bool confusingHint;                                   //  3397
//		class TutorMessage *message;                         //  3445
//		IsHostageMap(CCSTutor *const this);  //  3400
//		IsBombMap(CCSTutor *const this);  //  3417
//	}
}

/* <215b23> ../cstrike/dlls/tutor_cs_tutor.cpp:3456 */
NOBODY void CCSTutor::CheckInGameHintMessages(float time)
{
//	{
//		class TutorMessage *message;                         //  3482
//	}
}

/* <215b61> ../cstrike/dlls/tutor_cs_tutor.cpp:3493 */
NOBODY void CCSTutor::CheckForNeedToReload(bool isPassiveCheck)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3495
//		class CBasePlayerItem *currentItem;                  //  3502
//		class CBasePlayerWeapon *currentWeapon;              //  3511
//		ItemInfo itemInfo;                                    //  3512
//		iMaxClip(CBasePlayerItem *const this);  //  3541
//		{
//			class TutorMessage *message;                 //  3543
//		}
//		{
//			class TutorMessage *message;                 //  3553
//		}
//		iMaxClip(CBasePlayerItem *const this);  //  3561
//		{
//			class TutorMessage *message;                 //  3526
//		}
//	}
}

/* <215d16> ../cstrike/dlls/tutor_cs_tutor.cpp:3568 */
NOBODY void CCSTutor::CheckExamineMessages(float time)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3570
//		{
//			int i;                                        //  3576
//			{
//				class TutorMessage *message;         //  3578
//				class CBaseEntity *entity;           //  3585
//				bool sawOne;                          //  3588
//				{
//					bool isPlayerLooking;         //  3592
//					{
//						bool validEntity;     //  3617
//						{
//							class CBasePlayer *player;             //  3627
//						}
//						{
//							class CHostage *hostage;           //  3665
//							IsFollowingSomeone(CHostage *const this);  //  3666
//							IsValid(CHostage *const this);  //  3670
//						}
//						{
//							class CBasePlayer *player;             //  3648
//						}
//					}
//				}
//			}
//		}
//	}
}

/* <215eec> ../cstrike/dlls/tutor_cs_tutor.cpp:3696 */
NOBODY bool CCSTutor::CanLocalPlayerBuyStuff(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3698
//	}
}

/* <215f25> ../cstrike/dlls/tutor_cs_tutor.cpp:3714 */
NOBODY void CCSTutor::CheckBuyZoneMessages(void)
{
//	{
//		class CBasePlayer *localPlayer;                      //  3716
//		class CBasePlayerWeapon *primary;                    //  3729
//		class CBasePlayerWeapon *secondary;                  //  3730
//	}
}

/* <216cdd> ../cstrike/dlls/tutor_cs_tutor.cpp:3767 */
NOBODY bool CCSTutor::IsHostageMap(void)
{
}

/* <216d01> ../cstrike/dlls/tutor_cs_tutor.cpp:3773 */
NOBODY bool CCSTutor::IsBombMap(void)
{
//	{
//		class CHalfLifeMultiplay *mpRules;                   //  3775
//	}
}

/* <216d35> ../cstrike/dlls/tutor_cs_tutor.cpp:3781 */
NOBODY void CCSTutor::ResetPlayerDeathInfo(void)
{
//	{
//		int i;                                                //  3785
//	}
}

/* <216d6d> ../cstrike/dlls/tutor_cs_tutor.cpp:3795 */
NOBODY void CCSTutor::ConstructRecentDeathsList(TeamName team, char *buf, int buflen, TutorMessageEvent *event)
{
//	{
//		int i;                                                //  3804
//	}
}

/* <216dc2> ../cstrike/dlls/tutor_cs_tutor.cpp:3853 */
NOBODY void CCSTutor::TransferDeathEvents(TutorMessageEvent *oldEvent, TutorMessageEvent *newEvent)
{
//	{
//		int i;                                                //  3855
//	}
}

#ifdef HOOK_GAMEDLL

void CCSTutor::TutorThink(float time)
{
	TutorThink_(time);
}

void CCSTutor::PurgeMessages(void)
{
	PurgeMessages_();
}

void CCSTutor::CallEventHandler(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	CallEventHandler_(event, entity, other);
}

void CCSTutor::ShowTutorMessage(TutorMessageEvent *event)
{
	ShowTutorMessage_(event);
}

void CCSTutor::HandleShotFired(Vector source, Vector target)
{
	HandleShotFired_(source, target);
}

TutorMessage *CCSTutor::GetTutorMessageDefinition(int messageID)
{
	return GetTutorMessageDefinition_(messageID);
}

#endif // HOOK_GAMEDLL
