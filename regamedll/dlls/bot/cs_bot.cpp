#include "precompiled.h"

/* <2e85c8> ../cstrike/dlls/bot/cs_bot.cpp:24 */
NOBODY int GetBotFollowCount(CBasePlayer *leader)
{
//	{
//		int count;                                            //    26
//		{
//			int i;                                        //    28
//			{
//				class CBaseEntity *entity;           //    30
//				class CBasePlayer *player;           //    41
//				class CCSBot *bot;                   //    49
//				FNullEnt(entvars_t *pev);  //    35
//				GetFollowLeader(CCSBot *const this);  //    50
//			}
//		}
//	}
}

/* <2e86df> ../cstrike/dlls/bot/cs_bot.cpp:62 */
NOBODY void CCSBot::__MAKE_VHOOK(Walk)(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //    64
//	Walk(CBot *const this);  //    66
}

/* <2e8732> ../cstrike/dlls/bot/cs_bot.cpp:80 */
NOBODY bool CCSBot::__MAKE_VHOOK(Jump)(bool mustJump)
{
}

/* <2e8e39> ../cstrike/dlls/bot/cs_bot.cpp:97 */
NOBODY int CCSBot::__MAKE_VHOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		class CBaseEntity *attacker;                         //    99
//		GetClassPtr<CBaseEntity>(CBaseEntity *a);  //    99
//		{
//			class CBasePlayer *player;                   //   104
//		}
//		{
//			class CBasePlayer *lastAttacker;             //   113
//			float lastAttackedTimestamp;                  //   114
//			AdjustSafeTime(CCSBot *const this);  //   121
//			IsSurprised(const class CCSBot *const this);  //   124
//			{
//				class CBasePlayer *enemy;            //   126
//				bool panic;                           //   127
//				{
//					float invSkill;               //   148
//					float panicChance;            //   149
//				}
//			}
//		}
//	}
}

/* <2e8769> ../cstrike/dlls/bot/cs_bot.cpp:171 */
NOBODY void CCSBot::__MAKE_VHOOK(Killed)(entvars_t *pevAttacker, int iGib)
{
//	{
//		float const deathDanger;                               //   178
//		float const deathDangerRadius;                         //   179
//	}
}

/* <2e7c11> ../cstrike/dlls/bot/cs_bot.cpp:200 */
NOBODY inline bool IsIntersectingBox(const Vector *start, const Vector *end, const Vector *boxMin, const Vector *boxMax)
{
//	{
//		unsigned char startFlags;                             //   202
//		unsigned char endFlags;                               //   203
//	}
}

/* <2e87d9> ../cstrike/dlls/bot/cs_bot.cpp:253 */
NOBODY void CCSBot::BotTouch(CBaseEntity *other)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   297
//	{
//		Vector center;                                  //   299
//		class Extent extent;                                  //   301
//		bool breakIt;                                         //   307
//		operator+(const Vector *const this,
//				const Vector &v);  //   299
//		{
//			Vector goal;                            //   312
//			Vector(Vector *const this,
//				const Vector &v);  //   312
//			IsIntersectingBox(const Vector *start,
//						const Vector *end,
//						const Vector *boxMin,
//						const Vector *boxMax);  //   314
//		}
//		operator/(const Vector *const this,
//				float fl);  //   299
//	}
//	{
//		class CBasePlayer *player;                           //   269
//		unsigned int otherPri;                                //   272
//		unsigned int myPri;                                   //   275
//		{
//			unsigned int avoidPri;                        //   284
//		}
//	}
}

/* <2e89e3> ../cstrike/dlls/bot/cs_bot.cpp:335 */
NOBODY bool CCSBot::IsBusy(void) const
{
}

/* <2e8a0c> ../cstrike/dlls/bot/cs_bot.cpp:351 */
NOBODY void CCSBot::BotDeathThink(void)
{
}

/* <2e8a34> ../cstrike/dlls/bot/cs_bot.cpp:358 */
NOBODY CBasePlayer *CCSBot::FindNearbyPlayer(void)
{
//	{
//		class CBaseEntity *pEntity;                          //   360
//		Vector vecSrc;                                  //   361
//		float flRadius;                                       //   362
//		Vector(Vector *const this,
//			const Vector &v);  //   361
//	}
}

/* <2e8abd> ../cstrike/dlls/bot/cs_bot.cpp:385 */
void CCSBot::SetEnemy(CBasePlayer *enemy)
{
	if (m_enemy != enemy)
	{
		m_enemy = enemy;
		m_currentEnemyAcquireTimestamp = gpGlobals->time;
	}
}

/* <2e8af6> ../cstrike/dlls/bot/cs_bot.cpp:400 */
NOBODY bool CCSBot::StayOnNavMesh(void)
{
//	{
//		class CNavArea *goalArea;                            //   408
//		{
//			Vector pos;                             //   422
//			Vector to;                              //   426
//			float const stepInDist;                        //   429
//			operator-(const Vector *const this,
//					const Vector &v);  //   426
//			NormalizeInPlace(Vector *const this);  //   427
//			operator*(float fl,
//					const Vector &v);  //   430
//			operator+(const Vector *const this,
//					const Vector &v);  //   430
//		}
//	}
}

/* <2e8c56> ../cstrike/dlls/bot/cs_bot.cpp:450 */
NOBODY void CCSBot::Panic(CBasePlayer *enemy)
{
//	{
//		class Vector2D dir;                                   //   456
//		class Vector2D perp;                                  //   457
//		Vector spot;                                    //   459
//		IsSurprised(const class CCSBot *const this);  //   453
//		{
//			class Vector2D toEnemy;                       //   473
//			float along;                                  //   476
//			float c45;                                    //   477
//			float size;                                   //   478
//			float shift;                                  //   479
//			NormalizeInPlace(Vector2D *const this);  //   474
//			DotProduct(const class Vector2D &a,
//					const class Vector2D &b);  //   476
//			{
//				float side;                           //   495
//				DotProduct(const class Vector2D &a,
//						const class Vector2D &b);  //   495
//			}
//		}
//		{
//			float const offset;                            //   464
//			float side;                                   //   465
//		}
//	}
}

/* <2e9047> ../cstrike/dlls/bot/cs_bot.cpp:527 */
NOBODY bool CCSBot::IsDoingScenario(void)
{
}

/* <2e9070> ../cstrike/dlls/bot/cs_bot.cpp:544 */
NOBODY bool CCSBot::NoticeLooseBomb(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   546
//		class CBaseEntity *bomb;                             //   551
//		GetLooseBomb(CCSBotManager *const this);  //   551
//	}
}

/* <2e90d4> ../cstrike/dlls/bot/cs_bot.cpp:566 */
NOBODY bool CCSBot::CanSeeLooseBomb(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   568
//		class CBaseEntity *bomb;                             //   573
//		GetLooseBomb(CCSBotManager *const this);  //   573
//	}
}

/* <2e9140> ../cstrike/dlls/bot/cs_bot.cpp:588 */
NOBODY bool CCSBot::CanSeePlantedBomb(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   590
//		const Vector *bombPos;                        //   598
//	}
}

/* <2e918e> ../cstrike/dlls/bot/cs_bot.cpp:610 */
NOBODY CBasePlayer *CCSBot::GetAttacker(void)
{
}

/* <2e91b7> ../cstrike/dlls/bot/cs_bot.cpp:622 */
NOBODY void CCSBot::GetOffLadder(void)
{
//	DestroyPath(CCSBot *const this);  //   627
}

/* <2e91f1> ../cstrike/dlls/bot/cs_bot.cpp:637 */
NOBODY float CCSBot::GetHidingSpotCheckTimestamp(HidingSpot *spot)
{
//	{
//		int i;                                                //   639
//	}
}

/* <2e9240> ../cstrike/dlls/bot/cs_bot.cpp:651 */
NOBODY void CCSBot::SetHidingSpotCheckTimestamp(HidingSpot *spot)
{
//	{
//		int leastRecent;                                      //   653
//		float leastRecentTime;                                //   654
//		{
//			int i;                                        //   656
//		}
//	}
}

/* <2e92b8> ../cstrike/dlls/bot/cs_bot.cpp:693 */
NOBODY void CCSBot::UpdateHostageEscortCount(void)
{
//	{
//		float const updateInterval;                            //   695
//		{
//			class CHostage *hostage;                     //   704
//			IsValid(CHostage *const this);  //   709
//			IsFollowing(CHostage *const this,
//					const class CBaseEntity *entity);  //   713
//			edict(CBaseEntity *const this);  //   705
//			FNullEnt(const edict_t *pent);  //   705
//		}
//	}
}

/* <2e940d> ../cstrike/dlls/bot/cs_bot.cpp:722 */
NOBODY bool CCSBot::IsOutnumbered(void)
{
//	GetNearbyFriendCount(const class CCSBot *const this);  //   724
//	GetNearbyEnemyCount(const class CCSBot *const this);  //   724
}

/* <2e94a0> ../cstrike/dlls/bot/cs_bot.cpp:731 */
NOBODY int CCSBot::OutnumberedCount(void)
{
//	IsOutnumbered(const class CCSBot *const this);  //   733
//	GetNearbyEnemyCount(const class CCSBot *const this);  //   734
//	GetNearbyFriendCount(const class CCSBot *const this);  //   734
}

/* <2e95cb> ../cstrike/dlls/bot/cs_bot.cpp:744 */
NOBODY CBasePlayer *CCSBot::GetImportantEnemy(bool checkVisibility)
{
//	{
//		class CCSBotManager *ctrl;                           //   746
//		class CBasePlayer *nearEnemy;                        //   747
//		float nearDist;                                       //   748
//		{
//			int i;                                        //   750
//			{
//				class CBaseEntity *entity;           //   752
//				class CBasePlayer *player;           //   767
//				Vector d;                       //   782
//				float distSq;                         //   783
//				FNullEnt(entvars_t *pev);  //   757
//				operator-(const Vector *const this,
//						const Vector &v);  //   782
//			}
//		}
//	}
}

/* <2e9719> ../cstrike/dlls/bot/cs_bot.cpp:801 */
NOBODY void CCSBot::SetDisposition(DispositionType disposition)
{
//	Invalidate(CountdownTimer *const this);  //   806
}

/* <2e9762> ../cstrike/dlls/bot/cs_bot.cpp:814 */
CCSBot::DispositionType CCSBot::GetDisposition(void) const
{
	if (!m_ignoreEnemiesTimer.IsElapsed())
		return IGNORE_ENEMIES;

	return m_disposition;
}

/* <2e979b> ../cstrike/dlls/bot/cs_bot.cpp:826 */
NOBODY void CCSBot::IgnoreEnemies(float duration)
{
//	Start(CountdownTimer *const this,
//		float duration);  //   828
}

/* <2e97fc> ../cstrike/dlls/bot/cs_bot.cpp:835 */
NOBODY void CCSBot::IncreaseMorale(void)
{
}

/* <2e9824> ../cstrike/dlls/bot/cs_bot.cpp:845 */
void CCSBot::DecreaseMorale(void)
{
	if (m_morale > TERRIBLE)
	{
		m_morale = static_cast<MoraleType>(m_morale - 1);
	}
}

/* <2e984c> ../cstrike/dlls/bot/cs_bot.cpp:857 */
NOBODY bool CCSBot::IsRogue(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   859
//		AllowRogues(const class CCSBotManager *const this);  //   860
//		IsElapsed(const class CountdownTimer *const this);  //   864
//		{
//			float const rogueChance;                       //   869
//			Start(CountdownTimer *const this,
//				float duration);  //   866
//		}
//	}
}

/* <2e98f1> ../cstrike/dlls/bot/cs_bot.cpp:882 */
NOBODY bool CCSBot::IsHurrying(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   887
//		IsElapsed(const class CountdownTimer *const this);  //   884
//	}
}

/* <2e9942> ../cstrike/dlls/bot/cs_bot.cpp:906 */
NOBODY bool CCSBot::IsSafe(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   908
//		GetElapsedRoundTime(const class CCSBotManager *const this);  //   910
//	}
}

/* <2e9987> ../cstrike/dlls/bot/cs_bot.cpp:920 */
NOBODY bool CCSBot::IsWellPastSafe(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   922
//		GetElapsedRoundTime(const class CCSBotManager *const this);  //   924
//	}
}

/* <2e99d8> ../cstrike/dlls/bot/cs_bot.cpp:934 */
NOBODY bool CCSBot::IsEndOfSafeTime(void) const
{
//	IsSafe(const class CCSBot *const this);  //   936
}

/* <2e9a3e> ../cstrike/dlls/bot/cs_bot.cpp:943 */
NOBODY float CCSBot::GetSafeTimeRemaining(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   945
//		GetElapsedRoundTime(const class CCSBotManager *const this);  //   947
//	}
}

/* <2e9a8f> ../cstrike/dlls/bot/cs_bot.cpp:954 */
void CCSBot::AdjustSafeTime(void)
{
	CCSBotManager *ctrl = TheCSBots();

	// if we spotted an enemy sooner than we thought possible, adjust our notion of "safe" time
	if (m_safeTime > ctrl->GetElapsedRoundTime())
	{
		// since right now is not safe, adjust safe time to be a few seconds ago
		m_safeTime = ctrl->GetElapsedRoundTime() - 2.0f;
	}
}

/* <2e9ad0> ../cstrike/dlls/bot/cs_bot.cpp:970 */
NOBODY bool CCSBot::HasNotSeenEnemyForLongTime(void) const
{
//	{
//		float const longTime;                                  //   972
//		GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   973
//	}
}

/* <2e9b26> ../cstrike/dlls/bot/cs_bot.cpp:980 */
NOBODY bool CCSBot::GuardRandomZone(float range)
{
//	{
//		class CCSBotManager *ctrl;                           //   982
//		const class Zone *zone;                             //   984
//		GetRandomZone(const class CCSBotManager *const this);  //   984
//		{
//			class CNavArea *rescueArea;                  //   987
//		}
//	}
}

/* <2e9c1f> ../cstrike/dlls/bot/cs_bot.cpp:1066 */
NOBODY const Vector *FindNearbyRetreatSpot(CCSBot *me, float maxRange)
{
//	{
//		class CNavArea *area;                                //  1068
//		class CollectRetreatSpotsFunctor collector;           //  1073
//		int which;                                            //  1080
//		SearchSurroundingAreas<CollectRetreatSpotsFunctor>(CNavArea *startArea,
//									const Vector *startPos,
//									class CollectRetreatSpotsFunctor &func,
//									float maxRange);  //  1074
//	}
}

/* <2eaa1d> ../cstrike/dlls/bot/cs_bot.cpp:1116 */
NOBODY float CCSBot::GetRangeToFarthestEscortedHostage(void)
{
//	{
//		class FarthestHostage away;                           //  1118
//		ForEachHostage<FarthestHostage>(const class CHostageManager *const this,
//						class FarthestHostage &func);  //  1120
//	}
}

#ifdef HOOK_GAMEDLL

void CCSBot::Walk(void)
{
	Walk_();
}
bool CCSBot::Jump(bool mustJump)
{
	return Jump_(mustJump);
}

int CCSBot::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}
void CCSBot::Killed(entvars_t *pevAttacker, int iGib)
{
	Killed_(pevAttacker, iGib);
}

#endif // HOOK_GAMEDLL
