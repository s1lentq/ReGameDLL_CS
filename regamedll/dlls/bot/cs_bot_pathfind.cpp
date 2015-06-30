#include "precompiled.h"

/* <38db02> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:30 */
NOBODY bool CCSBot::ComputePathPositions(void)
{
//	{
//		int i;                                                //    40
//		{
//			const class ConnectInfo *from;              //    42
//			class ConnectInfo *to;                       //    43
//			{
//				const NavLadderList *list;          //   124
//				const_iterator iter;                  //   125
//				end(const class list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //   126
//				{
//					class CNavLadder *ladder;    //   128
//					AddDirectionVector(Vector *v,
//								enum NavDirType dir,
//								float amount);  //   134
//				}
//				operator++(_List_const_iterator<CNavLadder*> *const this);  //   126
//			}
//			{
//				const NavLadderList *list;          //    97
//				const_iterator iter;                  //    98
//				{
//					class CNavLadder *ladder;    //   101
//					AddDirectionVector(Vector *v,
//								enum NavDirType dir,
//								float amount);  //   110
//				}
//				end(const class list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //    99
//				operator++(_List_const_iterator<CNavLadder*> *const this);  //    99
//			}
//			{
//				float const stepInDist;                //    53
//				AddDirectionVector(Vector *v,
//							enum NavDirType dir,
//							float amount);  //    54
//				{
//					class Vector2D dir;           //    65
//					float const pushDist;          //    69
//					DirectionToVector2D(NavDirType dir,
//								class Vector2D *v);  //    66
//					{
//						int j;                //    77
//					}
//				}
//			}
//		}
//	}
}

/* <38d424> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:155 */
NOBODY void CCSBot::SetupLadderMovement(void)
{
//	{
//		const class ConnectInfo *to;                        //   160
//		{
//			TraceResult result;                           //   186
//			Vector from;                            //   187
//			Vector to;                              //   188
//			AddDirectionVector(Vector *v,
//						enum NavDirType dir,
//						float amount);  //   184
//			Vector(Vector *const this,
//				const Vector &v);  //   187
//			Vector(Vector *const this,
//				const Vector &v);  //   188
//			DirectionToAngle(NavDirType dir);  //   196
//			OppositeDirection(NavDirType dir);  //   203
//			DirectionToAngle(NavDirType dir);  //   203
//			AddDirectionVector(Vector *v,
//						enum NavDirType dir,
//						float amount);  //   205
//		}
//		AddDirectionVector(Vector *v,
//					enum NavDirType dir,
//					float amount);  //   177
//		OppositeDirection(NavDirType dir);  //   178
//		DirectionToAngle(NavDirType dir);  //   178
//	}
}

/* <38dd85> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:213 */
NOBODY void CCSBot::ComputeLadderEndpoint(bool isAscending)
{
//	{
//		TraceResult result;                                   //   215
//		{
//			Vector from;                            //   221
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   221
//		}
//		{
//			Vector from;                            //   233
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   233
//		}
//	}
}

/* <38de76> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:248 */
NOBODY bool CCSBot::UpdateLadderMovement(void)
{
//	{
//		bool giveUp;                                          //   253
//		float const ladderTimeoutDuration;                     //   256
//		float const tolerance;                                 //   315
//		float const closeToGoal;                               //   316
//		{
//			float const farAway;                           //   299
//			operator-(const class Vector2D *const this,
//					const class Vector2D &v);  //   300
//			IsLengthGreaterThan(const class Vector2D *const this,
//						float length);  //   300
//			DestroyPath(CCSBot *const this);  //   304
//		}
//		AddDirectionVector(Vector *v,
//					enum NavDirType dir,
//					float amount);  //   543
//		GetFeetZ(const class CCSBot *const this);  //   510
//		GetFeetZ(const class CCSBot *const this);  //   475
//		{
//			Vector to;                              //   446
//			Vector idealAngle;                      //   447
//			operator-(const Vector *const this,
//					const Vector &v);  //   446
//			AnglesAreEqual(float a,
//					float b,
//					float tolerance);  //   449
//		}
//		{
//			Vector to;                              //   429
//			Vector idealAngle;                      //   430
//			operator-(const Vector *const this,
//					const Vector &v);  //   429
//			AnglesAreEqual(float a,
//					float b,
//					float tolerance);  //   432
//		}
//		GetFeetZ(const class CCSBot *const this);  //   368
//		{
//			bool approached;                              //   380
//			class Vector2D d;                             //   382
//			{
//				class Vector2D perp;                  //   386
//				Length(const class Vector2D *const this);  //   388
//			}
//			{
//				float const walkRange;                 //   395
//				IsLengthLessThan(const class Vector2D *const this,
//						float length);  //   396
//			}
//		}
//		{
//			bool approached;                              //   322
//			class Vector2D d;                             //   324
//			float const walkRange;                         //   335
//			{
//				class Vector2D perp;                  //   328
//				Length(const class Vector2D *const this);  //   330
//			}
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   336
//		}
//		AddDirectionVector(Vector *v,
//					enum NavDirType dir,
//					float amount);  //   481
//		DestroyPath(CCSBot *const this);  //   528
//		GetFeetZ(const class CCSBot *const this);  //   538
//		SetPathIndex(CCSBot *const this,
//				int newIndex);  //   592
//	}
}

/* <38e44d> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:609 */
NOBODY bool CCSBot::FindClosestPointOnPath(Vector *worldPos, int startIndex, int endIndex, Vector *close)
{
//	{
//		Vector along;                                   //   614
//		Vector toWorldPos;                              //   614
//		Vector pos;                                     //   615
//		const Vector *from;                           //   616
//		const Vector *to;                             //   616
//		float length;                                         //   617
//		float closeLength;                                    //   618
//		float closeDistSq;                                    //   619
//		float distSq;                                         //   620
//		{
//			int i;                                        //   622
//			NormalizeInPlace(Vector *const this);  //   631
//			operator-(const Vector *const this,
//					const Vector &v);  //   634
//			DotProduct(Vector &a,
//					const Vector &b);  //   637
//			operator-(const Vector *const this,
//					const Vector &v);  //   647
//			LengthSquared(const Vector *const this);  //   647
//			operator-(const Vector *const this,
//					const Vector &v);  //   628
//			operator*(float fl,
//					const Vector &v);  //   645
//			operator+(const Vector *const this,
//					const Vector &v);  //   645
//		}
//	}
}

/* <38e6d0> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:665 */
NOBODY int CCSBot::FindOurPositionOnPath(Vector *close, bool local)
{
//	{
//		Vector along;                                   //   670
//		Vector toFeet;                                  //   670
//		Vector feet;                                    //   671
//		Vector eyes;                                    //   672
//		Vector pos;                                     //   673
//		const Vector *from;                           //   674
//		const Vector *to;                             //   674
//		float length;                                         //   675
//		float closeLength;                                    //   676
//		float closeDistSq;                                    //   677
//		int closeIndex;                                       //   678
//		float distSq;                                         //   679
//		int start;                                            //   681
//		int end;                                              //   681
//		{
//			int i;                                        //   699
//			operator-(const Vector *const this,
//					const Vector &v);  //   724
//			LengthSquared(const Vector *const this);  //   724
//			{
//				Vector probe;                   //   730
//				operator+(const Vector *const this,
//						const Vector &v);  //   730
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //   731
//			}
//			operator-(const Vector *const this,
//					const Vector &v);  //   705
//			NormalizeInPlace(Vector *const this);  //   708
//			operator-(const Vector *const this,
//					const Vector &v);  //   711
//			DotProduct(Vector &a,
//					const Vector &b);  //   714
//			operator*(float fl,
//					const Vector &v);  //   722
//			operator+(const Vector *const this,
//					const Vector &v);  //   722
//		}
//		GetFeetZ(const class CCSBot *const this);  //   671
//		operator+(const Vector *const this,
//				const Vector &v);  //   672
//	}
}

/* <38c911> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:752 */
NOBODY bool CCSBot::IsStraightLinePathWalkable(Vector *goal)
{
//	{
//		float const inc;                                       //   757
//		Vector feet;                                    //   759
//		Vector dir;                                     //   760
//		float length;                                         //   761
//		float lastGround;                                     //   763
//		float along;                                          //   769
//		Vector pos;                                     //   770
//		float ground;                                         //   771
//		bool done;                                            //   772
//	}
}

/* <38ec40> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:810 */
NOBODY int CCSBot::FindPathPoint(float aheadRange, Vector *point, int *prevIndex)
{
//	{
//		int afterIndex;                                       //   813
//		Vector close;                                   //   816
//		int startIndex;                                       //   817
//		Vector initDir;                                 //   898
//		Vector feet;                                    //   901
//		Vector eyes;                                    //   902
//		float rangeSoFar;                                     //   903
//		bool visible;                                         //   906
//		Vector prevDir;                                 //   908
//		bool isCorner;                                        //   911
//		int i;                                                //   912
//		{
//			int index;                                    //   834
//			float const closeEpsilon;                      //   842
//			operator-(const Vector *const this,
//					const Vector &v);  //   843
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   843
//		}
//		{
//			Vector pos;                             //   862
//			float const closeEpsilon;                      //   865
//			operator-(const Vector *const this,
//					const Vector &v);  //   866
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   866
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //   898
//		NormalizeInPlace(Vector *const this);  //   899
//		GetFeetZ(const class CCSBot *const this);  //   901
//		{
//			Vector pos;                             //   915
//			Vector to;                              //   916
//			Vector dir;                             //   917
//			Vector probe;                           //   936
//			Vector along;                           //   957
//			Vector(Vector *const this,
//				const Vector &v);  //   915
//			operator-(const Vector *const this,
//					const Vector &v);  //   916
//			Normalize(const Vector *const this);  //   917
//			DotProduct(Vector &a,
//					const Vector &b);  //   920
//			DotProduct(Vector &a,
//					const Vector &b);  //   927
//			operator+(const Vector *const this,
//					const Vector &v);  //   936
//			IsWalkableTraceLineClear(Vector &from,
//						Vector &to,
//						unsigned int flags);  //   937
//			operator-(const Vector *const this,
//					const Vector &v);  //   957
//			Length2D(const Vector *const this);  //   958
//			operator-(const Vector *const this,
//					const Vector &v);  //   957
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   902
//		{
//			const Vector *afterPoint;             //   981
//			const Vector *beforePoint;            //   982
//			Vector to;                              //   984
//			float length;                                 //   985
//			float t;                                      //   987
//			operator-(const Vector *const this,
//					const Vector &v);  //   984
//			Length2D(const Vector *const this);  //   985
//			operator*(float fl,
//					const Vector &v);  //   994
//			{
//				float const sightStepSize;             //   999
//				float dt;                             //  1000
//				Vector probe;                   //  1002
//				operator+(const Vector *const this,
//						const Vector &v);  //  1002
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //  1003
//				operator+(const Vector *const this,
//						const Vector &v);  //  1006
//				operator*(float fl,
//						const Vector &v);  //  1006
//			}
//			operator+(const Vector *const this,
//					const Vector &v);  //   994
//		}
//		{
//			float const epsilon;                           //  1017
//			class Vector2D toPoint;                       //  1018
//			DotProduct(const class Vector2D &a,
//					const class Vector2D &b);  //  1021
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1021
//			{
//				int i;                                //  1023
//				IsLengthGreaterThan(const class Vector2D *const this,
//							float length);  //  1028
//			}
//		}
//	}
}

/* <38f761> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1052 */
NOBODY void CCSBot::SetPathIndex(int newIndex)
{
//	SetupLadderMovement(CCSBot *const this);  //  1059
//	SetPathIndex(CCSBot *const this,
//			int newIndex);  //  1052
}

/* <38cafc> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1077 */
bool CCSBot::IsNearJump(void)
{
//	{
//		int i;                                                //  1082
//		{
//			float dz;                                     //  1086
//		}
//	}
}

/* <38f844> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1100 */
NOBODY float CCSBot::GetApproximateFallDamage(float height)
{
//	{
//		float const slope;                                     //  1103
//		float const intercept;                                 //  1104
//		float damage;                                         //  1106
//	}
}

/* <38f89b> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1118 */
NOBODY bool CCSBot::IsFriendInTheWay(Vector *goalPos)
{
//	{
//		float const avoidFriendInterval;                       //  1126
//		Vector moveDir;                                 //  1130
//		float length;                                         //  1133
//		IsElapsed(const class CountdownTimer *const this);  //  1121
//		{
//			int i;                                        //  1138
//			{
//				class CBasePlayer *player;           //  1140
//				Vector toFriend;                //  1158
//				float const personalSpace;             //  1161
//				float friendDistAlong;                //  1166
//				Vector pos;                     //  1173
//				float const friendRadius;              //  1180
//				FNullEnt(entvars_t *pev);  //  1145
//				operator-(const Vector *const this,
//						const Vector &v);  //  1158
//				IsLengthGreaterThan(const Vector *const this,
//							float length);  //  1162
//				DotProduct(Vector &a,
//						const Vector &b);  //  1166
//				operator*(float fl,
//						const Vector &v);  //  1177
//				operator+(const Vector *const this,
//						const Vector &v);  //  1177
//				operator-(const Vector *const this,
//						const Vector &v);  //  1181
//				IsLengthLessThan(const Vector *const this,
//						float length);  //  1181
//			}
//		}
//		Start(CountdownTimer *const this,
//			float duration);  //  1127
//		operator-(const Vector *const this,
//				const Vector &v);  //  1130
//		NormalizeInPlace(Vector *const this);  //  1133
//	}
}

/* <38fbd5> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1197 */
NOBODY void CCSBot::FeelerReflexAdjustment(Vector *goalPosition)
{
//	{
//		Vector dir;                                     //  1203
//		Vector lat;                                     //  1204
//		float const feelerOffset;                              //  1206
//		float const feelerLengthRun;                           //  1207
//		float const feelerLengthWalk;                          //  1208
//		float const feelerHeight;                              //  1209
//		float feelerLength;                                   //  1211
//		float ground;                                         //  1218
//		Vector normal;                                  //  1219
//		Vector feet;                                    //  1230
//		Vector from;                                    //  1231
//		Vector to;                                      //  1232
//		float testZ;                                          //  1233
//		bool leftClear;                                       //  1235
//		bool rightClear;                                      //  1260
//		float const avoidRange;                                //  1279
//		GetEyePosition(const class CCSBot *const this);  //  1220
//		GetFeetZ(const class CCSBot *const this);  //  1230
//		CrossProduct(Vector &a,
//				const Vector &b);  //  1224
//		CrossProduct(Vector &a,
//				const Vector &b);  //  1227
//		IsWalkableTraceLineClear(Vector &from,
//					Vector &to,
//					unsigned int flags);  //  1235
//		operator*(float fl,
//				const Vector &v);  //  1231
//		operator+(const Vector *const this,
//				const Vector &v);  //  1231
//		operator*(float fl,
//				const Vector &v);  //  1232
//		operator+(const Vector *const this,
//				const Vector &v);  //  1232
//		Vector(Vector *const this,
//			const Vector &v);  //  1252
//		Vector(Vector *const this,
//			const Vector &v);  //  1252
//		operator-(const Vector *const this,
//				const Vector &v);  //  1257
//		IsWalkableTraceLineClear(Vector &from,
//					Vector &to,
//					unsigned int flags);  //  1260
//		operator+(const Vector *const this,
//				const Vector &v);  //  1258
//		Vector(Vector *const this,
//			const Vector &v);  //  1274
//		Vector(Vector *const this,
//			const Vector &v);  //  1274
//		operator*(float fl,
//				const Vector &v);  //  1286
//		operator+(const Vector *const this,
//				const Vector &v);  //  1286
//		operator*(float fl,
//				const Vector &v);  //  1292
//		operator-(const Vector *const this,
//				const Vector &v);  //  1292
//		Vector(Vector *const this,
//			const Vector &v);  //  1254
//		Vector(Vector *const this,
//			const Vector &v);  //  1254
//		Vector(Vector *const this,
//			const Vector &v);  //  1276
//		Vector(Vector *const this,
//			const Vector &v);  //  1276
//	}
}

/* <3912bf> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1300 */
NOBODY CCSBot::PathResult CCSBot::UpdatePathMovement(bool allowSpeedChange)
{
//	{
//		bool nearEndOfPath;                                   //  1329
//		int prevIndex;                                        //  1373
//		float const aheadRange;                                //  1374
//		int newIndex;                                         //  1375
//		float const nearCornerRange;                           //  1378
//		Vector toGoal;                                  //  1448
//		Vector adjustedGoal;                            //  1510
//		bool didFall;                                         //  1583
//		float const giveUpDuration;                            //  1608
//		{
//			Vector toEnd;                           //  1332
//			Vector d;                               //  1337
//			float const walkRange;                         //  1339
//			GetFeetZ(const class CCSBot *const this);  //  1335
//			IsLengthLessThan(const Vector *const this,
//					float length);  //  1342
//			{
//				float const nearEndRange;              //  1349
//				float const closeEpsilon;              //  1353
//				IsLengthLessThan(const Vector *const this,
//						float length);  //  1350
//				DestroyPath(CCSBot *const this);  //  1357
//			}
//		}
//		FindPathPoint(CCSBot *const this,
//				float aheadRange,
//				Vector *point,
//				int *prevIndex);  //  1375
//		operator-(const Vector *const this,
//				const Vector &v);  //  1379
//		IsLengthLessThan(const Vector *const this,
//				float length);  //  1379
//		ClearLookAt(CCSBot *const this);  //  1381
//		SetPathIndex(CCSBot *const this,
//				int newIndex);  //  1388
//		{
//			float const crouchRange;                       //  1409
//			bool didCrouch;                               //  1410
//			{
//				int i;                                //  1411
//				{
//					const class CNavArea *to;   //  1413
//					Vector close;           //  1419
//					operator-(const Vector *const this,
//							const Vector &v);  //  1422
//					IsLengthGreaterThan(const class Vector2D *const this,
//								float length);  //  1422
//				}
//			}
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //  1443
//		{
//			float const lookAheadRange;                    //  1458
//			operator-(const Vector *const this,
//					const Vector &v);  //  1455
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1461
//			{
//				float along;                          //  1463
//				int i;                                //  1464
//				Length2D(const Vector *const this);  //  1463
//				{
//					Vector delta;           //  1467
//					float segmentLength;          //  1468
//					operator-(const Vector *const this,
//							const Vector &v);  //  1467
//					Length2D(const Vector *const this);  //  1468
//					{
//						float t;              //  1473
//						Vector target;  //  1474
//						operator-(const Vector *const this,
//								const Vector &v);  //  1483
//						operator*(float fl,
//								const Vector &v);  //  1481
//						operator+(const Vector *const this,
//								const Vector &v);  //  1481
//					}
//					operator-(const Vector *const this,
//							const Vector &v);  //  1490
//				}
//				GetPathEndpoint(const class CCSBot *const this);  //  1498
//			}
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //  1503
//		Vector(Vector *const this,
//			const Vector &v);  //  1510
//		{
//			const Vector *pos;                    //  1528
//			operator+(const Vector *const this,
//					const Vector &v);  //  1529
//			Vector(Vector *const this,
//				const Vector &v);  //  1529
//			operator+(const Vector *const this,
//					const Vector &v);  //  1531
//			Vector(Vector *const this,
//				const Vector &v);  //  1531
//			operator+(const Vector *const this,
//					const Vector &v);  //  1532
//			Vector(Vector *const this,
//				const Vector &v);  //  1532
//		}
//		{
//			float const politeDuration;                    //  1542
//			Start(CountdownTimer *const this,
//				float duration);  //  1543
//		}
//		IsElapsed(const class CountdownTimer *const this);  //  1545
//		DestroyPath(CCSBot *const this);  //  1552
//		GetFeetZ(const class CCSBot *const this);  //  1584
//		{
//			float const closeRange;                        //  1586
//			class Vector2D to;                            //  1587
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //  1588
//			GetFeetZ(const class CCSBot *const this);  //  1594
//		}
//		DestroyPath(CCSBot *const this);  //  1622
//		IsNearJump(const class CCSBot *const this);  //  1518
//	}
}

/* <3906a6> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1634 */
NOBODY void CCSBot::BuildTrivialPath(const Vector *goal)
{
}

/* <3907cd> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1664 */
NOBODY bool CCSBot::ComputePath(CNavArea *goalArea, const Vector *goal, RouteType route)
{
//	{
//		class CNavArea *startArea;                           //  1679
//		Vector pathEndPosition;                         //  1687
//		class CNavArea *closestArea;                         //  1705
//		class PathCost pathCost;                              //  1706
//		bool pathToGoalExists;                                //  1707
//		class CNavArea *effectiveGoalArea;                   //  1709
//		int count;                                            //  1716
//		class CNavArea *area;                                //  1717
//		IsElapsed(const class CountdownTimer *const this);  //  1669
//		Start(CountdownTimer *const this,
//			float duration);  //  1673
//		DestroyPath(CCSBot *const this);  //  1675
//		Vector(Vector *const this,
//			const Vector &v);  //  1687
//		NavAreaBuildPath<PathCost>(CNavArea *startArea,
//						class CNavArea *goalArea,
//						const Vector *goalPos,
//						class PathCost &costFunc,
//						class CNavArea ** closestArea);  //  1707
//		SetupLadderMovement(CCSBot *const this);  //  1786
//		DestroyPath(CCSBot *const this);  //  1747
//	}
}

/* <390ef6> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1798 */
NOBODY float CCSBot::GetPathDistanceRemaining(void)
{
//	{
//		int idx;                                              //  1803
//		float dist;                                           //  1805
//		const Vector *prevCenter;                     //  1806
//		{
//			int i;                                        //  1808
//			operator-(const Vector *const this,
//					const Vector &v);  //  1810
//			Length(const Vector *const this);  //  1810
//		}
//	}
}

/* <390fb1> ../cstrike/dlls/bot/cs_bot_pathfind.cpp:1821 */
NOBODY void CCSBot::DrawPath(void)
{
//	{
//		Vector close;                                   //  1830
//		{
//			int i;                                        //  1826
//			operator+(const Vector *const this,
//					const Vector &v);  //  1828
//			operator+(const Vector *const this,
//					const Vector &v);  //  1828
//		}
//		Vector(Vector *const this,
//			const Vector &v);  //  1835
//		operator+(const Vector *const this,
//				const Vector &v);  //  1835
//		operator+(const Vector *const this,
//				const Vector &v);  //  1836
//		operator+(const Vector *const this,
//				const Vector &v);  //  1836
//		operator+(const Vector *const this,
//				const Vector &v);  //  1837
//		operator+(const Vector *const this,
//				const Vector &v);  //  1837
//	}
}
