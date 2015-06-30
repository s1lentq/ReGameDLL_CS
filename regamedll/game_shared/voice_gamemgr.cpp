#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//cvar_t voice_serverdebug = { "voice_serverdebug", "0" };
//cvar_t sv_alltalk = { "sv_alltalk", "0", FCVAR_SERVER };

#else

//cvar_t voice_serverdebug;
//cvar_t sv_alltalk;

#endif // HOOK_GAMEDLL

//CPlayerBitVec g_PlayerModEnable;
//CBitVec<32> g_BanMasks[32];
//CBitVec<32> g_SentGameRulesMasks[32];
//CBitVec<32> g_SentBanMasks[32];
//CPlayerBitVec g_bWantModEnable;

/* <2d3c38> ../game_shared/voice_gamemgr.cpp:68 */
NOBODY void VoiceServerDebug(const char *pFmt, ...)
{
//	{
//		char msg;                                             //    70
//		va_list marker;                                       //    71
//	}
}

/* <2d3cd1> ../game_shared/voice_gamemgr.cpp:89 */
CVoiceGameMgr::CVoiceGameMgr(void)
{
}

/* <2d3c98> ../game_shared/voice_gamemgr.cpp:96 */
CVoiceGameMgr::~CVoiceGameMgr(void)
{
//	~CVoiceGameMgr(CVoiceGameMgr::~CVoiceGameMgr();  //    98
}

/* <2d3d0b> ../game_shared/voice_gamemgr.cpp:101 */
NOBODY bool CVoiceGameMgr::Init(IVoiceGameMgrHelper *pHelper, int maxClients)
{
}

/* <2d3d4e> ../game_shared/voice_gamemgr.cpp:123 */
NOBODY void CVoiceGameMgr::SetHelper(IVoiceGameMgrHelper *pHelper)
{
}

/* <2d4486> ../game_shared/voice_gamemgr.cpp:129 */
NOBODY void CVoiceGameMgr::Update(double frametime)
{
}

/* <2d3d82> ../game_shared/voice_gamemgr.cpp:140 */
NOBODY void CVoiceGameMgr::ClientConnected(edict_t *pEdict)
{
//	{
//		int index;                                            //   142
//		ENTINDEX(edict_t *pEdict);  //   142
//		operator=(CBitVecAccessor *const this,
//				int val);  //   145
//		Init(CBitVec<32> *const this,
//			int val);  //   146
//		Init(CBitVec<32> *const this,
//			int val);  //   147
//	}
}

/* <2d3ec5> ../game_shared/voice_gamemgr.cpp:152 */
NOBODY bool CVoiceGameMgr::PlayerHasBlockedPlayer(CBasePlayer *pReceiver, CBasePlayer *pSender)
{
//	{
//		int iReceiverIndex;                                   //   154
//		int iSenderIndex;                                     //   154
//		entindex(CBaseEntity *const this);  //   159
//		entindex(CBaseEntity *const this);  //   160
//		operator uint32(CBitVecAccessor *const this);  //   165
//	}
}

NOBODY bool CVoiceGameMgr::ClientCommand(CBasePlayer *pPlayer, const char *cmd)
{
}

/* <2d416b> ../game_shared/voice_gamemgr.cpp:215 */
NOBODY void CVoiceGameMgr::UpdateMasks(void)
{
//	{
//		bool bAllTalk;                                        //   219
//		{
//			int iClient;                                  //   221
//			{
//				class CBaseEntity *pEnt;             //   223
//				class CBasePlayer *pPlayer;          //   234
//				CPlayerBitVec gameRulesMask;          //   236
//				operator uint32(CBitVecAccessor *const this);  //   228
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						entvars_t *ent);  //   230
//				CBitVec(CBitVec<32> *const this);  //   236
//				{
//					int iOtherClient;             //   240
//					{
//						class CBaseEntity *pEnt;   //   242
//						operator=(CBitVecAccessor *const this,
//								int val);  //   245
//					}
//				}
//				operator!=(CBitVec<32> *const this,
//						const class CBitVec<32> &other);  //   251
//				operator!=(CBitVec<32> *const this,
//						const class CBitVec<32> &other);  //   252
//				{
//					int dw;                       //   258
//					operator=(CBitVec<32> *const this,
//							const class CBitVec<32> &other);  //   254
//					operator=(CBitVec<32> *const this,
//							const class CBitVec<32> &other);  //   255
//					MESSAGE_BEGIN(int msg_dest,
//							int msg_type,
//							const float *pOrigin,
//							entvars_t *ent);  //   257
//				}
//				{
//					int iOtherClient;             //   268
//					{
//						bool bCanHear;        //   270
//						operator uint32(CBitVecAccessor *const this);  //   270
//						operator uint32(CBitVecAccessor *const this);  //   270
//					}
//				}
//			}
//		}
//	}
}
