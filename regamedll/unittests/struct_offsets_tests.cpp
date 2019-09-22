#include "precompiled.h"
#include "cppunitlite/TestHarness.h"

#pragma warning(push)
#ifndef _WIN32
#pragma warning(disable : 1875)		// warning #1875: offsetof applied to non-POD (Plain Old Data) types is nonstandard
#endif // _WIN32

#define CHECK_CLASS_SIZE CHECK_STRUCT_SIZE

#define CHECK_STRUCT_SIZE(s,win_size,lin_size) {\
	int needOff = __isWindows ? win_size : lin_size; \
	UINT32_EQUALS("Bad size "#s"::", needOff, sizeof(s)); \
}

#define CHECK_STRUCT_OFFSET(s,f,win_off,lin_off) {\
	int needOff = __isWindows ? win_off : lin_off; \
	int realOff = offsetof(s, f); \
	UINT32_EQUALS("Bad offset "#s"::"#f, needOff, realOff); \
	}

#define REPEAT_SIZEOF(st)\
		sizeof(st), sizeof(st)

#define REPEAT_OFFSETOF(st,memb)\
		offsetof(st,memb), offsetof(st,memb)

#define REPEAT_SIZEOF_PRINT(st)\
	printf("sizeof %s: 0x%2X (%d)\n", #st, sizeof(st), sizeof(st))

#define REPEAT_OFFSETOF_PRINT(st,memb)\
	printf("sizeof %s::%s: 0x%2X (%d)\n", #st, #memb, offsetof(st,memb), offsetof(st,memb))

TEST(StructOffsets, ReversingChecks, 5000)
{
	// sizeof class
	REPEAT_SIZEOF_PRINT(CNavArea);
	REPEAT_SIZEOF_PRINT(CBot);
	REPEAT_SIZEOF_PRINT(CCSBot);
	REPEAT_SIZEOF_PRINT(CBotManager);
	REPEAT_SIZEOF_PRINT(CCSBotManager);
	REPEAT_SIZEOF_PRINT(BotPhraseManager);
	REPEAT_SIZEOF_PRINT(BotPhrase);
	REPEAT_SIZEOF_PRINT(CBasePlayer);
	REPEAT_SIZEOF_PRINT(ActiveGrenade);
	REPEAT_SIZEOF_PRINT(CSoundEnt);
	REPEAT_SIZEOF_PRINT(CCSTutor);

	REPEAT_SIZEOF_PRINT(CHostageImprov);
	REPEAT_SIZEOF_PRINT(CHostage);

	REPEAT_SIZEOF_PRINT(CBaseGrenCatch);
	REPEAT_SIZEOF_PRINT(CFuncWeaponCheck);

	REPEAT_SIZEOF_PRINT(HostageStateMachine);
	REPEAT_SIZEOF_PRINT(HostageFollowState);
	REPEAT_SIZEOF_PRINT(CHalfLifeMultiplay);
	REPEAT_SIZEOF_PRINT(CHalfLifeTraining);
	REPEAT_SIZEOF_PRINT(CGib);
	REPEAT_SIZEOF_PRINT(CSprayCan);
	REPEAT_SIZEOF_PRINT(CountdownTimer);
	REPEAT_SIZEOF_PRINT(CCareerTaskManager);
	REPEAT_SIZEOF_PRINT(CCareerTask);
	REPEAT_SIZEOF_PRINT(CPreventDefuseTask);

	REPEAT_SIZEOF_PRINT(BotStatement);

	// offset the members
	REPEAT_OFFSETOF_PRINT(CBaseEntity, pev);
	REPEAT_OFFSETOF_PRINT(CBaseEntity, has_disconnected);
	//REPEAT_OFFSETOF_PRINT(CPreventDefuseTask, m_bombPlantedThisRound);
	//REPEAT_OFFSETOF_PRINT(CPreventDefuseTask, m_defuseStartedThisRound);
}

#pragma warning( pop )
