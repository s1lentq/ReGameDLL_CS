#include "precompiled.h"

/* <37c284> ../cstrike/dlls/bot/cs_bot_nav.cpp:16 */
NOBODY void CCSBot::ResetStuckMonitor(void)
{
}

/* <37c2a6> ../cstrike/dlls/bot/cs_bot_nav.cpp:37 */
NOBODY void CCSBot::StuckCheck(void)
{
//	{
//		Vector delta;                                   //    42
//		float const unstuckRange;                              //    44
//		operator-(const Vector *const this,
//				const Vector &v);  //    42
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //    45
//		ResetStuckMonitor(CCSBot *const this);  //    48
//	}
//	{
//		Vector vel;                                     //    57
//		float moveDist;                                       //    64
//		float deltaT;                                         //    66
//		operator-(const Vector *const this,
//				const Vector &v);  //    57
//		Length(const Vector *const this);  //    64
//		{
//			float avgVel;                                 //    81
//			float stuckVel;                               //    88
//			{
//				int t;                                //    82
//			}
//		}
//	}
}

/* <37c05d> ../cstrike/dlls/bot/cs_bot_nav.cpp:114 */
NOBODY bool CCSBot::DiscontinuityJump(float ground, bool onlyJumpDown, bool mustJump)
{
//	{
//		float dz;                                             //   119
//	}
}

/* <37c448> ../cstrike/dlls/bot/cs_bot_nav.cpp:154 */
NOBODY bool CCSBot::GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal)
{
//	GetSimpleGroundHeightWithFloor(CCSBot *const this,
//					const Vector *pos,
//					float *height,
//					Vector *normal);  //   154
}

/* <37c4b8> ../cstrike/dlls/bot/cs_bot_nav.cpp:172 */
NOBODY Place CCSBot::GetPlace(void)
{
}

/* <37c4de> ../cstrike/dlls/bot/cs_bot_nav.cpp:184 */
NOBODY void CCSBot::MoveTowardsPosition(const Vector *pos)
{
//	{
//		float angle;                                          //   249
//		class Vector2D dir;                                   //   251
//		class Vector2D lat;                                   //   252
//		class Vector2D to;                                    //   255
//		float toProj;                                         //   259
//		float latProj;                                        //   260
//		float const c;                                         //   262
//		{
//			float ground;                                 //   200
//			Vector aheadRay;                        //   201
//			bool jumped;                                  //   207
//			NormalizeInPlace(Vector *const this);  //   202
//			{
//				float const farLookAheadRange;         //   210
//				Vector normal;                  //   211
//				Vector stepAhead;               //   212
//				operator*(float fl,
//						const Vector &v);  //   212
//				GetSimpleGroundHeightWithFloor(CCSBot *const this,
//								const Vector *pos,
//								float *height,
//								Vector *normal);  //   215
//				operator+(const Vector *const this,
//						const Vector &v);  //   212
//				DiscontinuityJump(CCSBot *const this,
//							float ground,
//							bool onlyJumpDown,
//							bool mustJump);  //   218
//			}
//			{
//				float const lookAheadRange;            //   225
//				Vector stepAhead;               //   226
//				operator*(float fl,
//						const Vector &v);  //   226
//				operator+(const Vector *const this,
//						const Vector &v);  //   226
//				GetSimpleGroundHeightWithFloor(CCSBot *const this,
//								const Vector *pos,
//								float *height,
//								Vector *normal);  //   228
//				DiscontinuityJump(CCSBot *const this,
//							float ground,
//							bool onlyJumpDown,
//							bool mustJump);  //   230
//			}
//			{
//				float const lookAheadRange;            //   237
//				Vector stepAhead;               //   238
//				operator*(float fl,
//						const Vector &v);  //   238
//				operator+(const Vector *const this,
//						const Vector &v);  //   238
//				GetSimpleGroundHeightWithFloor(CCSBot *const this,
//								const Vector *pos,
//								float *height,
//								Vector *normal);  //   240
//				DiscontinuityJump(CCSBot *const this,
//							float ground,
//							bool onlyJumpDown,
//							bool mustJump);  //   242
//			}
//		}
//		NormalizeInPlace(Vector2D *const this);  //   256
//	}
}

/* <37ca96> ../cstrike/dlls/bot/cs_bot_nav.cpp:282 */
NOBODY void CCSBot::MoveAwayFromPosition(const Vector *pos)
{
//	{
//		float angle;                                          //   285
//		class Vector2D dir;                                   //   287
//		class Vector2D lat;                                   //   288
//		class Vector2D to;                                    //   291
//		float toProj;                                         //   295
//		float latProj;                                        //   296
//		float const c;                                         //   298
//		NormalizeInPlace(Vector2D *const this);  //   292
//	}
}

/* <37cb85> ../cstrike/dlls/bot/cs_bot_nav.cpp:314 */
NOBODY void CCSBot::StrafeAwayFromPosition(const Vector *pos)
{
//	{
//		float angle;                                          //   317
//		class Vector2D dir;                                   //   319
//		class Vector2D lat;                                   //   320
//		class Vector2D to;                                    //   323
//		float latProj;                                        //   326
//		NormalizeInPlace(Vector2D *const this);  //   324
//	}
}

/* <37cc52> ../cstrike/dlls/bot/cs_bot_nav.cpp:338 */
NOBODY void CCSBot::Wiggle(void)
{
//	ResetStuckMonitor(CCSBot *const this);  //   342
}

/* <37cc94> ../cstrike/dlls/bot/cs_bot_nav.cpp:383 */
NOBODY void CCSBot::ComputeApproachPoints(void)
{
//	{
//		Vector eye;                                     //   391
//		Vector ap;                                      //   393
//		float halfWidth;                                      //   394
//		Vector(Vector *const this,
//			const Vector &v);  //   391
//		{
//			int i;                                        //   395
//			{
//				const class ApproachInfo *info;     //   397
//				Vector bendPoint;               //   415
//			}
//			GetApproachInfoCount(const class CNavArea *const this);  //   395
//		}
//	}
}

/* <37cd67> ../cstrike/dlls/bot/cs_bot_nav.cpp:422 */
NOBODY void CCSBot::DrawApproachPoints(void)
{
//	{
//		int i;                                                //   427
//		operator+(const Vector *const this,
//				const Vector &v);  //   428
//		Vector(Vector *const this,
//			const Vector &v);  //   428
//	}
}

/* <37ce12> ../cstrike/dlls/bot/cs_bot_nav.cpp:435 */
NOBODY bool CCSBot::FindApproachPointNearestPath(const Vector *pos)
{
//	{
//		Vector target;                                  //   446
//		Vector close;                                   //   446
//		float targetRangeSq;                                  //   447
//		bool found;                                           //   448
//		int start;                                            //   450
//		int end;                                              //   451
//		float const nearPathSq;                                //   457
//		{
//			int i;                                        //   459
//			{
//				float rangeSq;                        //   464
//				operator-(const Vector *const this,
//						const Vector &v);  //   464
//				LengthSquared(const Vector *const this);  //   464
//			}
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   478
//	}
}
