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

TEST(StructOffsets, ReversingChecks, 5000)
{
	CHECK_CLASS_SIZE(CBasePlayer, 0x9B0, 0x9C4);
	CHECK_CLASS_SIZE(CHostageImprov, 0x1C8Cu, 0x1C8Cu);
	CHECK_CLASS_SIZE(BotPhraseManager, 0x21Cu, 0x214u);

	//CHECK_CLASS_SIZE(CBotManager, 12u, 12);
	//CHECK_CLASS_SIZE(CCSBotManager, 740, 0x2E0u);//0x2E4u | 0x2E0u

	//CHECK_CLASS_SIZE(HostageStateMachine, 0x10, 0x10);
	//CHECK_CLASS_SIZE(HostageFollowState, 0x4C, 0x4C);
	//CHECK_CLASS_SIZE(CCSBot, 0x2CA0, 0x2CA0);

	printf("sizeof CBot: 0x%2X (%d)\n", REPEAT_SIZEOF(CBot));
	printf("sizeof CCSBot: 0x%2X (%d)\n", REPEAT_SIZEOF(CCSBot));

	printf("sizeof CBotManager: 0x%2X (%d)\n", REPEAT_SIZEOF(CBotManager));
	printf("sizeof CCSBotManager: 0x%2X (%d)\n", REPEAT_SIZEOF(CCSBotManager));
	printf("sizeof BotPhraseManager: 0x%2X (%d)\n", REPEAT_SIZEOF(BotPhraseManager));

	printf("sizeof CBasePlayer: 0x%2X (%d)\n", REPEAT_SIZEOF(CBasePlayer));
	printf("sizeof ActiveGrenade: 0x%2X (%d)\n", REPEAT_SIZEOF(ActiveGrenade));
	printf("sizeof CHostageImprov: 0x%2X (%d)\n", REPEAT_SIZEOF(CHostageImprov));
	printf("sizeof HostageStateMachine: 0x%2X (%d)\n", REPEAT_SIZEOF(HostageStateMachine));
	printf("sizeof HostageFollowState: 0x%2X (%d)\n", REPEAT_SIZEOF(HostageFollowState));

	printf("offsetof CBaseEntity::pev: 0x%2X (%d)\n", REPEAT_OFFSETOF(CBaseEntity, pev));
	printf("offsetof CBaseEntity::has_disconnected: 0x%2X (%d)\n", REPEAT_OFFSETOF(CBaseEntity, has_disconnected));

}

#pragma warning( pop )
