#include "precompiled.h"

/* <58e6e0> ../cstrike/dlls/bot/states/cs_bot_hunt.cpp:18 */
NOBODY void HuntState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
//	SetTask(CCSBot *const this,
//		enum TaskType task,
//		class CBaseEntity *entity);  //    29
//	DestroyPath(CCSBot *const this);  //    31
}

/* <58e452> ../cstrike/dlls/bot/states/cs_bot_hunt.cpp:38 */
NOBODY void HuntState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
//	{
//		class CCSBotManager *ctrl;                           //    40
//		float const huntingTooLongTime;                        //    44
//		{
//			class CHostage *hostage;                     //   129
//			{
//				class CNavArea *area;                //   132
//				SetTask(CCSBot *const this,
//					enum TaskType task,
//					class CBaseEntity *entity);  //   136
//			}
//		}
//		SetTask(CCSBot *const this,
//			enum TaskType task,
//			class CBaseEntity *entity);  //   118
//		{
//			float const safeTime;                          //    62
//		}
//		SetTask(CCSBot *const this,
//			enum TaskType task,
//			class CBaseEntity *entity);  //    82
//		SetTask(CCSBot *const this,
//			enum TaskType task,
//			class CBaseEntity *entity);  //    92
//		{
//			float oldest;                                 //   163
//			int areaCount;                                //   165
//			float const minSize;                           //   166
//			iterator iter;                                //   167
//			int which;                                    //   189
//			{
//				class CNavArea *area;                //   170
//				const class Extent *extent;         //   175
//				float age;                            //   180
//				GetClearedTimestamp(CNavArea *const this,
//							int teamID);  //   180
//			}
//			operator++(_List_iterator<CNavArea*> *const this);  //   168
//			operator++(_List_iterator<CNavArea*> *const this);  //   192
//		}
//		SetRogue(CCSBot *const this,
//			bool rogue);  //    49
//	}
}

/* <58e418> ../cstrike/dlls/bot/states/cs_bot_hunt.cpp:211 */
NOBODY void HuntState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
}

#ifdef HOOK_GAMEDLL

void HuntState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void HuntState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

void HuntState::OnExit(CCSBot *me)
{
	OnExit_(me);
}

#endif // HOOK_GAMEDLL