#include "precompiled.h"

/* <5c4e91> ../cstrike/dlls/bot/states/cs_bot_move_to.cpp:21 */
NOBODY void MoveToState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
//	{
//		enum RouteType route;                                 //    30
//	}
}

/* <5c4edf> ../cstrike/dlls/bot/states/cs_bot_move_to.cpp:55 */
NOBODY void MoveToState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
//	{
//		class CCSBotManager *ctrl;                           //    76
//		{
//			class CBasePlayer *victim;                   //    61
//			GetTaskEntity(CCSBot *const this);  //    61
//		}
//		{
//			float const nearPlantSite;                     //   161
//			{
//				float const radioTime;                 //   173
//			}
//		}
//		Say(BotChatterInterface *const this,
//			const char *phraseName,
//			float lifetime,
//			float delay);  //   140
//		{
//			class CHostage *hostage;                     //   197
//			float const repathToleranceSq;                 //   205
//			float error;                                  //   206
//			GetGoalEntity(CCSBot *const this);  //   197
//			IsValid(CHostage *const this);  //   198
//			IsFollowingSomeone(CHostage *const this);  //   198
//			operator-(const Vector *const this,
//					const Vector &v);  //   206
//			LengthSquared(const Vector *const this);  //   206
//			{
//				Vector pos;                     //   216
//				Vector to;                      //   217
//				float const watchHostageRange;         //   220
//				operator+(const Vector *const this,
//						const Vector &v);  //   216
//				operator-(const Vector *const this,
//						const Vector &v);  //   217
//				IsLengthLessThan(const Vector *const this,
//						float length);  //   221
//				{
//					enum NavRelativeDirType dir;  //   226
//					float const useRange;          //   236
//					GetGoalEntity(CCSBot *const this);  //   239
//				}
//			}
//		}
//		{
//			int z;                                        //   100
//			Contains(const class Extent *const this,
//				const Vector *pos);  //   106
//		}
//		{
//			const Vector *bombPos;                //   284
//			IsActiveWeaponReloading(const class CBot *const this);  //   278
//			{
//				Vector toBomb;                  //   287
//				float const defuseRange;               //   291
//				GetFeetZ(const class CCSBot *const this);  //   290
//				IsLengthLessThan(const Vector *const this,
//						float length);  //   292
//			}
//		}
//		{
//			class CBasePlayer *victim;                   //   303
//			GetTaskEntity(CCSBot *const this);  //   303
//			Say(BotChatterInterface *const this,
//				const char *phraseName,
//				float lifetime,
//				float delay);  //   307
//		}
//	}
}

/* <5c4e54> ../cstrike/dlls/bot/states/cs_bot_move_to.cpp:320 */
NOBODY void MoveToState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
}

#ifdef HOOK_GAMEDLL

void MoveToState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void MoveToState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

void MoveToState::OnExit(CCSBot *me)
{
	OnExit_(me);
}

#endif // HOOK_GAMEDLL
