#include "precompiled.h"

enum TutorStateType
{
	TUTORSTATE_UNDEFINED = 0,
	TUTORSTATE_LOOKING_FOR_HOSTAGE,
	TUTORSTATE_ESCORTING_HOSTAGE,
	TUTORSTATE_LOOKING_FOR_LOST_HOSTAGE,
	TUTORSTATE_FOLLOWING_HOSTAGE_ESCORT,
	TUTORSTATE_MOVING_TO_BOMBSITE,
	TUTORSTATE_LOOKING_FOR_BOMB_CARRIER,
	TUTORSTATE_GUARDING_LOOSE_BOMB,
	TUTORSTATE_DEFUSING_BOMB,
	TUTORSTATE_GUARDING_HOSTAGE,
	TUTORSTATE_MOVING_TO_INTERCEPT_ENEMY,
	TUTORSTATE_LOOKING_FOR_HOSTAGE_ESCORT,
	TUTORSTATE_ATTACKING_HOSTAGE_ESCORT,
	TUTORSTATE_ESCORTING_BOMB_CARRIER,
	TUTORSTATE_MOVING_TO_BOMB_SITE,
	TUTORSTATE_PLANTING_BOMB,
	TUTORSTATE_GUARDING_BOMB,
	TUTORSTATE_LOOKING_FOR_LOOSE_BOMB,
	TUTORSTATE_RUNNING_AWAY_FROM_TICKING_BOMB,
	TUTORSTATE_BUYTIME,
	TUTORSTATE_WAITING_FOR_START,
};

/* <22bf8e> ../cstrike/dlls/tutor_cs_states.cpp:53 */
NOBODY CCSTutorStateSystem::CCSTutorStateSystem(void)
{
//	CCSTutorUndefinedState(CCSTutorUndefinedState *const this);  //    55
}

/* <22bd56> ../cstrike/dlls/tutor_cs_states.cpp:58 */
NOBODY CCSTutorStateSystem::~CCSTutorStateSystem(void)
{
}

/* <22bccf> ../cstrike/dlls/tutor_cs_states.cpp:68 */
NOBODY bool CCSTutorStateSystem::UpdateState(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		enum TutorStateType nextStateType;                    //    70
//		CCSTutorUndefinedState(CCSTutorUndefinedState *const this);  //    76
//	}
}

/* <22b96f> ../cstrike/dlls/tutor_cs_states.cpp:108 */
NOBODY char *CCSTutorStateSystem::GetCurrentStateString(void)
{
}

/* <22bbfe> ../cstrike/dlls/tutor_cs_states.cpp:118 */
NOBODY CBaseTutorState *CCSTutorStateSystem::ConstructNewState(int stateType)
{
//	{
//		class CBaseTutorState *ret;                          //   120
//		CCSTutorWaitingForStartState(CCSTutorWaitingForStartState *const this);  //   128
//		CCSTutorBuyMenuState(CCSTutorBuyMenuState *const this);  //   132
//	}
//	ConstructNewState(CCSTutorStateSystem *const this,
//				int stateType);  //   118
}

/* <22bfcb> ../cstrike/dlls/tutor_cs_states.cpp:141 */
NOBODY CCSTutorUndefinedState::CCSTutorUndefinedState(void)
{
}

/* <22bb33> ../cstrike/dlls/tutor_cs_states.cpp:146 */
NOBODY CCSTutorUndefinedState::~CCSTutorUndefinedState(void)
{
//	~CCSTutorUndefinedState(CCSTutorUndefinedState::~CCSTutorUndefinedState();  //   148
}

/* <22bdd8> ../cstrike/dlls/tutor_cs_states.cpp:150 */
NOBODY int CCSTutorUndefinedState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		int ret;                                              //   152
//		HandlePlayerSpawned(CCSTutorUndefinedState *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //   156
//	}
}

/* <22bfed> ../cstrike/dlls/tutor_cs_states.cpp:163 */
NOBODY int CCSTutorUndefinedState::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //   171
//		class CBasePlayer *player;                           //   178
//	}
}

/* <22b995> ../cstrike/dlls/tutor_cs_states.cpp:190 */
NOBODY char *CCSTutorUndefinedState::GetStateString(void)
{
}

/* <22c03e> ../cstrike/dlls/tutor_cs_states.cpp:198 */
NOBODY CCSTutorWaitingForStartState::CCSTutorWaitingForStartState(void)
{
}

/* <22bab6> ../cstrike/dlls/tutor_cs_states.cpp:203 */
NOBODY CCSTutorWaitingForStartState::~CCSTutorWaitingForStartState(void)
{
}

/* <22beca> ../cstrike/dlls/tutor_cs_states.cpp:207 */
NOBODY int CCSTutorWaitingForStartState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		int ret;                                              //   209
//		HandlePlayerSpawned(CCSTutorWaitingForStartState *const this,
//					class CBaseEntity *entity,
//					class CBaseEntity *other);  //   214
//	}
}

/* <22b9bb> ../cstrike/dlls/tutor_cs_states.cpp:224 */
NOBODY char *CCSTutorWaitingForStartState::GetStateString(void)
{
}

/* <22c060> ../cstrike/dlls/tutor_cs_states.cpp:230 */
NOBODY int CCSTutorWaitingForStartState::HandlePlayerSpawned(CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CBasePlayer *localPlayer;                      //   238
//		class CBasePlayer *player;                           //   245
//	}
}

/* <22c0b1> ../cstrike/dlls/tutor_cs_states.cpp:257 */
NOBODY int CCSTutorWaitingForStartState::HandleBuyTimeStart(CBaseEntity *entity, CBaseEntity *other)
{
}

/* <22c0e2> ../cstrike/dlls/tutor_cs_states.cpp:266 */
NOBODY CCSTutorBuyMenuState::CCSTutorBuyMenuState(void)
{
}

/* <22ba5a> ../cstrike/dlls/tutor_cs_states.cpp:271 */
NOBODY CCSTutorBuyMenuState::~CCSTutorBuyMenuState(void)
{
}

/* <22b9e1> ../cstrike/dlls/tutor_cs_states.cpp:275 */
NOBODY int CCSTutorBuyMenuState::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
}

/* <22ba34> ../cstrike/dlls/tutor_cs_states.cpp:288 */
NOBODY char *CCSTutorBuyMenuState::GetStateString(void)
{
}

/* <22c104> ../cstrike/dlls/tutor_cs_states.cpp:293 */
NOBODY int CCSTutorBuyMenuState::HandleRoundStart(CBaseEntity *entity, CBaseEntity *other)
{
}
