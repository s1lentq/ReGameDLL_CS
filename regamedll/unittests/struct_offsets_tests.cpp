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

#ifdef HOOK_GAMEDLL
	// assert
	CHECK_CLASS_SIZE(CNavArea, 0x238u, 0x214u);

	CHECK_CLASS_SIZE(CBasePlayer, 0x9B0, 0x9C4);
	CHECK_CLASS_SIZE(CHostageImprov, 0x1C8Cu, 0x1C8Cu);
	CHECK_CLASS_SIZE(CHostage, 0x7B0, 0x7C4);

	CHECK_CLASS_SIZE(CBaseGrenCatch, 0x98, 0xA8);
	CHECK_CLASS_SIZE(CFuncWeaponCheck, 0x11C, 0x12C);

	CHECK_CLASS_SIZE(BotPhraseManager, 0x21Cu, 0x214u);
	CHECK_CLASS_SIZE(BotPhrase, 0x50, 0x44);

	//CHECK_CLASS_SIZE(CHalfLifeMultiplay, 0x2D0u, 0x2C4u);
	CHECK_CLASS_SIZE(CHalfLifeTraining, 0x2E8u, 0x2D8u);
	CHECK_CLASS_SIZE(CGib, 0x98, 0xA8);
	CHECK_CLASS_SIZE(CSprayCan, 0x88, 0x98);
	CHECK_CLASS_SIZE(CBaseEntity, 0x88, 0x98);
	CHECK_CLASS_SIZE(CGrenade, 0x1E0, 0x1F4);
	//CHECK_CLASS_SIZE(CountdownTimer, 0xC, 0x8);
	CHECK_CLASS_SIZE(CCareerTaskManager, 0x28, 0x24);
	CHECK_CLASS_SIZE(CCareerTask, 0x2C, 0x2C);
	CHECK_CLASS_SIZE(CPreventDefuseTask, 0x30, 0x30);
	CHECK_CLASS_SIZE(CSoundEnt, 0x898, 0x8A8);
	//CHECK_CLASS_SIZE(CCSTutor, 0x160u, 0x164u);		// UNDONE: don't need a check this

	//CHECK_CLASS_SIZE(CBotManager, 12u, 12);
	CHECK_CLASS_SIZE(CCSBot, 11404, 11424);
	//CHECK_CLASS_SIZE(CCSBotManager, 740, 0x2E0u);//0x2E4u | 0x2E0u

	CHECK_CLASS_SIZE(BotStatement, 0x70u, 0x70u);
	//CHECK_CLASS_SIZE(HostageStateMachine, 0x10, 0x10);
	//CHECK_CLASS_SIZE(HostageFollowState, 0x4C, 0x4C);
	//CHECK_CLASS_SIZE(CCSBot, 0x2CA0, 0x2CA0);
#endif // HOOK_GAMEDLL
}

#pragma warning( pop )
