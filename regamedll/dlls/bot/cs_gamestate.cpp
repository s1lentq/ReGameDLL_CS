#include "precompiled.h"

/* <3fca3c> ../cstrike/dlls/bot/cs_gamestate.cpp:13 */
NOBODY CSGameState::CSGameState(void)
{

}

/* <3fcd6b> ../cstrike/dlls/bot/cs_gamestate.cpp:27 */
NOBODY CSGameState::CSGameState(CCSBot *owner)
{
//	IntervalTimer(IntervalTimer *const this);  //    27
//	{
//		int i;                                                //    41
//	}
//	IntervalTimer(IntervalTimer *const this);  //    27
//	CountdownTimer(CountdownTimer *const this);  //    27
}

/* <3fd4f4> ../cstrike/dlls/bot/cs_gamestate.cpp:55 */
NOBODY void CSGameState::Reset(void)
{
//	{
//		class CCSBotManager *ctrl;                           //    66
//		int i;                                                //    69
//		Invalidate(IntervalTimer *const this);  //    61
//		Invalidate(IntervalTimer *const this);  //    62
//		{
//			int swap;                                     //    81
//			int rnd;                                      //    82
//		}
//	}
}

/* <3fce67> ../cstrike/dlls/bot/cs_gamestate.cpp:97 */
NOBODY void CSGameState::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	SetBombState(CSGameState *const this,
//			enum BombState state);  //   104
//	UpdatePlantedBomb(CSGameState *const this,
//				const Vector *pos);  //   109
//	SetBombState(CSGameState *const this,
//			enum BombState state);  //   117
//	SetBombState(CSGameState *const this,
//			enum BombState state);  //   124
}

/* <3fcf9c> ../cstrike/dlls/bot/cs_gamestate.cpp:144 */
NOBODY bool CSGameState::IsRoundOver(void) const
{
}

/* <3fcfc6> ../cstrike/dlls/bot/cs_gamestate.cpp:150 */
NOBODY void CSGameState::SetBombState(BombState state)
{
}

/* <3fcff2> ../cstrike/dlls/bot/cs_gamestate.cpp:160 */
NOBODY void CSGameState::UpdateLooseBomb(const Vector *pos)
{
//	SetBombState(CSGameState *const this,
//			enum BombState state);  //   166
//	Reset(IntervalTimer *const this);  //   163
}

/* <3fd06e> ../cstrike/dlls/bot/cs_gamestate.cpp:170 */
NOBODY float CSGameState::TimeSinceLastSawLooseBomb(void) const
{
//	GetElapsedTime(const class IntervalTimer *const this);  //   172
}

/* <3fd0f4> ../cstrike/dlls/bot/cs_gamestate.cpp:176 */
NOBODY bool CSGameState::IsLooseBombLocationKnown(void) const
{
//	HasStarted(const class IntervalTimer *const this);  //   181
}

/* <3fd135> ../cstrike/dlls/bot/cs_gamestate.cpp:185 */
NOBODY void CSGameState::UpdateBomber(const Vector *pos)
{
//	Reset(IntervalTimer *const this);  //   188
//	SetBombState(CSGameState *const this,
//			enum BombState state);  //   191
}

/* <3fd1b1> ../cstrike/dlls/bot/cs_gamestate.cpp:195 */
NOBODY float CSGameState::TimeSinceLastSawBomber(void) const
{
//	GetElapsedTime(const class IntervalTimer *const this);  //   197
}

/* <3fd237> ../cstrike/dlls/bot/cs_gamestate.cpp:201 */
NOBODY bool CSGameState::IsPlantedBombLocationKnown(void) const
{
}

/* <3fd25a> ../cstrike/dlls/bot/cs_gamestate.cpp:213 */
NOBODY int CSGameState::GetPlantedBombsite(void) const
{
}

/* <3fd284> ../cstrike/dlls/bot/cs_gamestate.cpp:225 */
NOBODY bool CSGameState::IsAtPlantedBombsite(void) const
{
//	{
//		class CCSBotManager *ctrl;                           //   230
//		const class Zone *zone;                             //   231
//	}
}

/* <3fd2d2> ../cstrike/dlls/bot/cs_gamestate.cpp:246 */
NOBODY int CSGameState::GetNextBombsiteToSearch(void)
{
//	{
//		int i;                                                //   251
//		{
//			int z;                                        //   256
//		}
//	}
}

/* <3fd32c> ../cstrike/dlls/bot/cs_gamestate.cpp:277 */
NOBODY const Vector *CSGameState::GetBombPosition(void) const
{
//	HasStarted(const class IntervalTimer *const this);  //   283
}

/* <3fd373> ../cstrike/dlls/bot/cs_gamestate.cpp:313 */
NOBODY void CSGameState::UpdatePlantedBomb(const Vector *pos)
{
//	{
//		class CCSBotManager *ctrl;                           //   315
//		const class Zone *zone;                             //   316
//		SetBombState(CSGameState *const this,
//				enum BombState state);  //   330
//	}
}

/* <3fd3dd> ../cstrike/dlls/bot/cs_gamestate.cpp:337 */
NOBODY void CSGameState::MarkBombsiteAsPlanted(int zoneIndex)
{
//	SetBombState(CSGameState *const this,
//			enum BombState state);  //   340
}

/* <3fd43a> ../cstrike/dlls/bot/cs_gamestate.cpp:347 */
NOBODY void CSGameState::ClearBombsite(int zoneIndex)
{
}

/* <3fd475> ../cstrike/dlls/bot/cs_gamestate.cpp:354 */
NOBODY bool CSGameState::IsBombsiteClear(int zoneIndex) const
{
}

/* <3fd4b0> ../cstrike/dlls/bot/cs_gamestate.cpp:367 */
NOBODY void CSGameState::InitializeHostageInfo(void)
{
//	{
//		class CBaseEntity *hostage;                          //   373
//	}
}

/* <3fd5ab> ../cstrike/dlls/bot/cs_gamestate.cpp:398 */
NOBODY CHostage *CSGameState::GetNearestFreeHostage(Vector *knowPos)
{
//	{
//		class CNavArea *startArea;                           //   403
//		class CHostage *close;                               //   407
//		const Vector *closePos;                       //   408
//		float closeDistance;                                  //   409
//		{
//			int i;                                        //   411
//			{
//				const Vector *hostagePos;     //   413
//				class CNavArea *hostageArea;         //   435
//				{
//					class ShortestPathCost pc;    //   438
//					float travelDistance;         //   439
//					NavAreaTravelDistance<ShortestPathCost>(CNavArea *startArea,
//										class CNavArea *endArea,
//										class ShortestPathCost &costFunc);  //   439
//				}
//				IsValid(CHostage *const this);  //   418
//				IsFollowingSomeone(CHostage *const this);  //   421
//			}
//		}
//	}
}

/* <3fdbd3> ../cstrike/dlls/bot/cs_gamestate.cpp:461 */
NOBODY const Vector *CSGameState::GetRandomFreeHostagePosition(void)
{
//	{
//		const Vector *freePos;                        //   466
//		int freeCount;                                        //   467
//		{
//			int i;                                        //   469
//			{
//				const class HostageInfo *info;      //   471
//				IsFollowingSomeone(CHostage *const this);  //   480
//			}
//		}
//	}
}

/* <3fdcd2> ../cstrike/dlls/bot/cs_gamestate.cpp:509 */
NOBODY unsigned char CSGameState::ValidateHostagePositions(void)
{
//	{
//		float const validateInterval;                          //   515
//		TraceResult result;                                   //   520
//		unsigned char status;                                 //   521
//		int i;                                                //   523
//		int startValidCount;                                  //   524
//		int endValidCount;                                    //   605
//		IsElapsed(const class CountdownTimer *const this);  //   512
//		Start(CountdownTimer *const this,
//			float duration);  //   516
//		{
//			class HostageInfo *info;                     //   531
//			{
//				float const tolerance;                 //   594
//				IsValid(CHostage *const this);  //   576
//				IsFollowingSomeone(CHostage *const this);  //   586
//				operator-(const Vector *const this,
//						const Vector &v);  //   595
//				IsLengthGreaterThan(const Vector *const this,
//							float length);  //   595
//			}
//			IsFollowingSomeone(CHostage *const this);  //   541
//		}
//	}
}

/* <3fdef7> ../cstrike/dlls/bot/cs_gamestate.cpp:626 */
NOBODY CHostage *CSGameState::GetNearestVisibleFreeHostage(void)
{
//	{
//		class CHostage *close;                               //   628
//		float closeRangeSq;                                   //   629
//		float rangeSq;                                        //   630
//		Vector pos;                                     //   632
//		{
//			int i;                                        //   634
//			{
//				const class HostageInfo *info;      //   636
//				IsFollowingSomeone(CHostage *const this);  //   643
//				operator+(const Vector *const this,
//						const Vector &v);  //   647
//				operator-(const Vector *const this,
//						const Vector &v);  //   648
//				LengthSquared(const Vector *const this);  //   648
//			}
//		}
//	}
}

/* <3fe064> ../cstrike/dlls/bot/cs_gamestate.cpp:668 */
NOBODY bool CSGameState::AreAllHostagesBeingRescued(void)
{
//	{
//		bool isAllDead;                                       //   674
//		{
//			int i;                                        //   676
//			{
//				const class HostageInfo *info;      //   678
//				IsValid(CHostage *const this);  //   683
//				IsFollowingSomeone(CHostage *const this);  //   685
//			}
//		}
//	}
}

/* <3fe148> ../cstrike/dlls/bot/cs_gamestate.cpp:712 */
NOBODY bool CSGameState::AreAllHostagesGone(void)
{
//	{
//		int i;                                                //   718
//		{
//			const class HostageInfo *info;              //   720
//		}
//	}
}

/* <3fe1a2> ../cstrike/dlls/bot/cs_gamestate.cpp:742 */
NOBODY void CSGameState::AllHostagesGone(void)
{
//	{
//		int i;                                                //   744
//	}
}
