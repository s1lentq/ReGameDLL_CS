#include "precompiled.h"

/* <354545> ../cstrike/dlls/bot/cs_bot_listen.cpp:17 */
NOBODY bool CCSBot::ShouldInvestigateNoise(float *retNoiseDist)
{
//	IsNoiseHeard(const class CCSBot *const this);  //    32
//	{
//		float const noiseCheckInterval;                        //    36
//		Vector toNoise;                                 //    44
//		float noiseDist;                                      //    45
//		float const maxNoiseDist;                              //    46
//		float const oneStoreyHeight;                           //    49
//		float chance;                                         //    72
//		operator-(const Vector *const this,
//				const Vector &v);  //    44
//		Length(const Vector *const this);  //    45
//		{
//			class PathCost pc;                            //    53
//			float travelDistToNoise;                      //    54
//			float const tooFar;                            //    58
//			NavAreaTravelDistance<PathCost>(CNavArea *startArea,
//							class CNavArea *endArea,
//							class PathCost &costFunc);  //    54
//		}
//		{
//			float friendFactor;                           //    78
//		}
//	}
}

/* <354c8d> ../cstrike/dlls/bot/cs_bot_listen.cpp:104 */
NOBODY bool CCSBot::CanHearNearbyEnemyGunfire(float range)
{
//	{
//		float gunfireDistSq;                                  //   125
//		float enemyDistSq;                                    //   126
//		float const muchCloserSq;                              //   127
//		operator-(const Vector *const this,
//				const Vector &v);  //   126
//		operator-(const Vector *const this,
//				const Vector &v);  //   125
//		LengthSquared(const Vector *const this);  //   125
//		LengthSquared(const Vector *const this);  //   126
//	}
//	CanSeeNoisePosition(const class CCSBot *const this);  //   119
//	operator-(const Vector *const this,
//			const Vector &v);  //   115
//	IsLengthGreaterThan(const Vector *const this,
//				float length);  //   115
}

/* <354e7b> ../cstrike/dlls/bot/cs_bot_listen.cpp:141 */
NOBODY bool CCSBot::CanSeeNoisePosition(void)
{
//	{
//		TraceResult result;                                   //   143
//		operator+(const Vector *const this,
//				const Vector &v);  //   144
//		GetEyePosition(const class CCSBot *const this);  //   144
//	}
}

/* <354f48> ../cstrike/dlls/bot/cs_bot_listen.cpp:160 */
NOBODY bool CCSBot::UpdateLookAtNoise(void)
{
//	{
//		bool nearbyThreat;                                    //   176
//		float const recentThreatTime;                          //   177
//		float const closeThreatRange;                          //   178
//		Vector spot;                                    //   190
//		enum PriorityType pri;                                //   231
//		IsNoiseHeard(const class CCSBot *const this);  //   163
//		operator-(const Vector *const this,
//				const Vector &v);  //   181
//		IsLengthLessThan(const Vector *const this,
//				float length);  //   181
//		CanSeeNoisePosition(const class CCSBot *const this);  //   193
//		{
//			int nearIdx;                                  //   200
//			float nearRangeSq;                            //   201
//			{
//				int i;                                //   202
//				{
//					float distanceSq;             //   206
//					operator-(const Vector *const this,
//							const Vector &v);  //   206
//					LengthSquared(const Vector *const this);  //   206
//				}
//			}
//		}
//	}
}
