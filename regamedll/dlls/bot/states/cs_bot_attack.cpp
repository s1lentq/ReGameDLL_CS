#include "precompiled.h"

/* <519735> ../cstrike/dlls/bot/states/cs_bot_attack.cpp:16 */
NOBODY void AttackState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
//	{
//		class CBasePlayer *enemy;                            //    18
//		float skill;                                          //   105
//		float dodgeChance;                                    //   108
//		GetEnemy(CCSBot *const this);  //    18
//		PushPostureContext(CBot *const this);  //    21
//		DestroyPath(CCSBot *const this);  //    23
//		Invalidate(CountdownTimer *const this);  //    34
//		{
//			float const crouchFarRange;                    //    63
//			float crouchChance;                           //    64
//			operator-(const Vector *const this,
//					const Vector &v);  //    69
//			IsLengthGreaterThan(const Vector *const this,
//						float length);  //    69
//			{
//				TraceResult result;                   //    77
//				Vector origin;                  //    79
//				Vector(Vector *const this,
//					const Vector &v);  //    79
//			}
//		}
//	}
}

/* <51a140> ../cstrike/dlls/bot/states/cs_bot_attack.cpp:135 */
NOBODY void AttackState::StopAttacking(CCSBot *me)
{
	if (me->m_task == CCSBot::SNIPING)
	{
		// stay in our hiding spot
		me->Hide(me->GetLastKnownArea(), -1.0f, 50.0f);
	}
	else
	{
		me->StopAttacking();
	}
}

/* <51997e> ../cstrike/dlls/bot/states/cs_bot_attack.cpp:152 */
NOBODY void AttackState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
//	{
//		class CBasePlayerWeapon *weapon;                     //   161
//		class CBasePlayer *enemy;                            //   173
//		float notSeenEnemyTime;                               //   368
//		float chaseTime;                                      //   444
//		float const hurtRecentlyTime;                          //   474
//		StopRapidFire(CCSBot *const this);  //   158
//		GetEnemy(CCSBot *const this);  //   173
//		IsElapsed(const class CountdownTimer *const this);  //   189
//		{
//			bool isPinnedDown;                            //   198
//			Start(CountdownTimer *const this,
//				float duration);  //   210
//		}
//		{
//			bool repath;                                  //   252
//			ForceRun(CCSBot *const this,
//				float duration);  //   240
//			Hurry(CCSBot *const this,
//				float duration);  //   241
//			{
//				float const repathRange;               //   255
//				operator-(const Vector *const this,
//						const Vector &v);  //   256
//				IsLengthGreaterThan(const Vector *const this,
//							float length);  //   256
//			}
//			IsElapsed(const class CountdownTimer *const this);  //   264
//			DestroyPath(CCSBot *const this);  //   272
//			Start(CountdownTimer *const this,
//				float duration);  //   267
//		}
//		IsReloading(CBasePlayer *const this);  //   286
//		IsProtectedByShield(CBasePlayer *const this);  //   289
//		{
//			float const sniperMinRange;                    //   320
//			operator-(const Vector *const this,
//					const Vector &v);  //   321
//			IsLengthLessThan(const Vector *const this,
//					float length);  //   321
//		}
//		{
//			float const shotgunMaxRange;                   //   327
//			operator-(const Vector *const this,
//					const Vector &v);  //   328
//			IsLengthGreaterThan(const Vector *const this,
//						float length);  //   328
//		}
//		{
//			Vector toAimSpot3D;                     //   342
//			float targetRange;                            //   343
//			float const waitScopeTime;                     //   349
//			operator-(const Vector *const this,
//					const Vector &v);  //   342
//			Length(const Vector *const this);  //   343
//			GetZoomLevel(const class CCSBot *const this);  //   346
//		}
//		IsProtectedByShield(CBasePlayer *const this);  //   295
//		IsProtectedByShield(CBasePlayer *const this);  //   302
//		IsAwareOfEnemyDeath(const class CCSBot *const this);  //   358
//		{
//			float hideChance;                             //   397
//			{
//				float ambushTime;                     //   401
//				const Vector *spot;           //   405
//			}
//		}
//		StopAttacking(AttackState *const this,
//				class CCSBot *me);  //   424
//		StopAttacking(AttackState *const this,
//				class CCSBot *me);  //   377
//		GetNoisePosition(const class CCSBot *const this);  //   378
//		SetTask(CCSBot *const this,
//			enum TaskType task,
//			class CBaseEntity *entity);  //   465
//		entindex(CBaseEntity *const this);  //   361
//		{
//			Vector toEnemy;                         //   508
//			float range;                                  //   509
//			float const hysterisRange;                     //   511
//			float minRange;                               //   513
//			float maxRange;                               //   514
//			float const dodgeRange;                        //   526
//			operator-(const Vector *const this,
//					const Vector &v);  //   508
//			Length2D(const Vector *const this);  //   509
//			{
//				int next;                             //   534
//				{
//					float const jumpChance;        //   540
//					IsNotMoving(const class CCSBot *const this);  //   541
//				}
//			}
//		}
//		GetTimeSinceAttacked(const class CCSBot *const this);  //   476
//		GetEnemy(CCSBot *const this);  //   478
//		StopAttacking(AttackState *const this,
//				class CCSBot *me);  //   459
//		GetNearbyEnemyCount(const class CCSBot *const this);  //   361
//		entindex(CBaseEntity *const this);  //   362
//	}
}

/* <5198d4> ../cstrike/dlls/bot/states/cs_bot_attack.cpp:578 */
NOBODY void AttackState::__MAKE_VHOOK(OnExit)(CCSBot *me)
{
//	ForgetNoise(CCSBot *const this);  //   585
//	PopPostureContext(CBot *const this);  //   589
//	IsProtectedByShield(CBasePlayer *const this);  //   592
//	StopRapidFire(CCSBot *const this);  //   597
//	ClearSurpriseDelay(CCSBot *const this);  //   598
}

#ifdef HOOK_GAMEDLL

void AttackState::OnEnter(CCSBot *me)
{
	OnEnter_(me);
}

void AttackState::OnUpdate(CCSBot *me)
{
	OnUpdate_(me);
}

void AttackState::OnExit(CCSBot *me)
{
	OnExit_(me);
}

#endif // HOOK_GAMEDLL