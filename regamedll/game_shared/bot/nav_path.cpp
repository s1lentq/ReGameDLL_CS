#include "precompiled.h"

/* <505025> ../game_shared/bot/nav_path.cpp:24 */
NOBODY bool CNavPath::ComputePathPositions(void)
{
//	{
//		int i;                                                //    34
//		{
//			const class PathSegment *from;              //    36
//			class PathSegment *to;                       //    37
//			{
//				const NavLadderList *list;          //   118
//				const_iterator iter;                  //   119
//				{
//					class CNavLadder *ladder;    //   122
//					AddDirectionVector(Vector *v,
//								enum NavDirType dir,
//								float amount);  //   128
//				}
//				end(const class list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //   120
//				operator++(_List_const_iterator<CNavLadder*> *const this);  //   120
//			}
//			{
//				const NavLadderList *list;          //    91
//				const_iterator iter;                  //    92
//				end(const class list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //    93
//				{
//					class CNavLadder *ladder;    //    95
//					AddDirectionVector(Vector *v,
//								enum NavDirType dir,
//								float amount);  //   104
//				}
//				operator++(_List_const_iterator<CNavLadder*> *const this);  //    93
//			}
//			{
//				float const stepInDist;                //    47
//				AddDirectionVector(Vector *v,
//							enum NavDirType dir,
//							float amount);  //    48
//				{
//					class Vector2D dir;           //    59
//					float const pushDist;          //    63
//					DirectionToVector2D(NavDirType dir,
//								class Vector2D *v);  //    60
//					{
//						int j;                //    71
//					}
//				}
//			}
//		}
//	}
}

/* <50525f> ../game_shared/bot/nav_path.cpp:148 */
NOBODY bool CNavPath::IsAtEnd(const Vector &pos) const
{
//	{
//		float const epsilon;                                   //   153
//		operator-(const Vector *const this,
//				const Vector &v);  //   154
//		IsLengthLessThan(const Vector *const this,
//				float length);  //   154
//	}
}

/* <5052f6> ../game_shared/bot/nav_path.cpp:161 */
NOBODY float CNavPath::GetLength(void) const
{
//	{
//		float length;                                         //   163
//		{
//			int i;                                        //   164
//			operator-(const Vector *const this,
//					const Vector &v);  //   166
//			Length(const Vector *const this);  //   166
//		}
//	}
}

/* <50537f> ../game_shared/bot/nav_path.cpp:177 */
NOBODY bool CNavPath::GetPointAlongPath(float distAlong, Vector *pointOnPath) const
{
//	{
//		float lengthSoFar;                                    //   188
//		float segmentLength;                                  //   189
//		Vector dir;                                     //   190
//		{
//			int i;                                        //   191
//			operator-(const Vector *const this,
//					const Vector &v);  //   193
//			Length(const Vector *const this);  //   194
//			{
//				float delta;                          //   199
//				float t;                              //   200
//				operator*(float fl,
//						const Vector &v);  //   202
//				operator+(const Vector *const this,
//						const Vector &v);  //   202
//			}
//		}
//	}
}

/* <5054da> ../game_shared/bot/nav_path.cpp:218 */
NOBODY int CNavPath::GetSegmentIndexAlongPath(float distAlong) const
{
//	{
//		float lengthSoFar;                                    //   228
//		Vector dir;                                     //   229
//		{
//			int i;                                        //   230
//			operator-(const Vector *const this,
//					const Vector &v);  //   232
//			Length(const Vector *const this);  //   232
//		}
//	}
}

/* <50557e> ../game_shared/bot/nav_path.cpp:250 */
NOBODY bool CNavPath::FindClosestPointOnPath(const Vector *worldPos, int startIndex, int endIndex, Vector *close) const
{
//	{
//		Vector along;                                   //   255
//		Vector toWorldPos;                              //   255
//		Vector pos;                                     //   256
//		const Vector *from;                           //   257
//		const Vector *to;                             //   257
//		float length;                                         //   258
//		float closeLength;                                    //   259
//		float closeDistSq;                                    //   260
//		float distSq;                                         //   261
//		{
//			int i;                                        //   263
//			NormalizeInPlace(Vector *const this);  //   272
//			operator-(const Vector *const this,
//					const Vector &v);  //   275
//			DotProduct(Vector &a,
//					const Vector &b);  //   278
//			operator-(const Vector *const this,
//					const Vector &v);  //   288
//			LengthSquared(const Vector *const this);  //   288
//			operator-(const Vector *const this,
//					const Vector &v);  //   269
//			operator*(float fl,
//					const Vector &v);  //   286
//			operator+(const Vector *const this,
//					const Vector &v);  //   286
//		}
//	}
}

// Build trivial path when start and goal are in the same nav area

/* <5057df> ../game_shared/bot/nav_path.cpp:305 */
bool CNavPath::BuildTrivialPath(const Vector *start, const Vector *goal)
{
	m_segmentCount = 0;

	CNavArea *startArea = TheNavAreaGrid.GetNearestNavArea(start);
	if (startArea == NULL)
		return false;

	CNavArea *goalArea = TheNavAreaGrid.GetNearestNavArea(goal);
	if (goalArea == NULL)
		return false;

	m_segmentCount = 2;

	m_path[0].area = startArea;
	m_path[0].pos.x = start->x;
	m_path[0].pos.y = start->y;
	m_path[0].pos.z = startArea->GetZ(start);
	m_path[0].ladder = NULL;
	m_path[0].how = NUM_TRAVERSE_TYPES;

	m_path[1].area = goalArea;
	m_path[1].pos.x = goal->x;
	m_path[1].pos.y = goal->y;
	m_path[1].pos.z = goalArea->GetZ(goal);
	m_path[1].ladder = NULL;
	m_path[1].how = NUM_TRAVERSE_TYPES;

	return true;
}

/* <505853> ../game_shared/bot/nav_path.cpp:340 */
NOBODY void CNavPath::Draw(void)
{
//	{
//		int i;                                                //   345
//		operator+(const Vector *const this,
//				const Vector &v);  //   347
//		operator+(const Vector *const this,
//				const Vector &v);  //   347
//	}
}

/* <505931> ../game_shared/bot/nav_path.cpp:357 */
NOBODY int CNavPath::FindNextOccludedNode(int anchor)
{
//	{
//		int lastVisible;                                      //   359
//		{
//			int i;                                        //   360
//			{
//				Vector anchorPlusHalf;          //   372
//				Vector iPlusHalf;               //   373
//				Vector anchorPlusFull;          //   380
//				Vector iPlusFull;               //   381
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //   366
//				operator+(const Vector *const this,
//						const Vector &v);  //   372
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //   374
//				operator+(const Vector *const this,
//						const Vector &v);  //   373
//				operator+(const Vector *const this,
//						const Vector &v);  //   380
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //   382
//				operator+(const Vector *const this,
//						const Vector &v);  //   381
//			}
//		}
//	}
}

/* <505c26> ../game_shared/bot/nav_path.cpp:396 */
NOBODY void CNavPath::Optimize(void)
{
}

/* <505c6d> ../game_shared/bot/nav_path.cpp:436 */
NOBODY CNavPathFollower::CNavPathFollower(void)
{
//	CStuckMonitor(CStuckMonitor *const this);  //   436
}

/* <505cce> ../game_shared/bot/nav_path.cpp:447 */
NOBODY void CNavPathFollower::Reset(void)
{
//	Reset(CStuckMonitor *const this);  //   452
}

/* <507c31> ../game_shared/bot/nav_path.cpp:459 */
NOBODY void CNavPathFollower::Update(float deltaT, bool avoidObstacles)
{
//	{
//		const class PathSegment *node;                      //   464
//		float const closeRange;                                //   507
//		float const aheadRange;                                //   523
//		bool isApproachingJumpArea;                           //   529
//		float const giveUpTime;                                //   596
//		operator[](CNavPath *const this,
//				int i);  //   464
//		Invalidate(CNavPath *const this);  //   600
//		{
//			const Vector *approachPos;            //   476
//			const Vector *departPos;              //   477
//			operator[](CNavPath *const this,
//					int i);  //   480
//			operator[](CNavPath *const this,
//					int i);  //   483
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //   508
//		IsLengthLessThan(const Vector *const this,
//				float length);  //   508
//		FindPathPoint(CNavPathFollower *const this,
//				float aheadRange,
//				Vector *point,
//				int *prevIndex);  //   524
//		{
//			float const crouchRange;                       //   547
//			bool didCrouch;                               //   548
//			{
//				int i;                                //   549
//				{
//					const class CNavArea *to;   //   551
//					Vector close;           //   560
//					operator-(const Vector *const this,
//							const Vector &v);  //   563
//					IsLengthGreaterThan(const class Vector2D *const this,
//								float length);  //   563
//					operator[](CNavPath *const this,
//							int i);  //   551
//				}
//			}
//		}
//		GetDuration(const class CStuckMonitor *const this);  //   597
//		GetEndpoint(const class CNavPath *const this);  //   599
//		{
//			float const closeRange;                        //   608
//			class Vector2D to;                            //   609
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   610
//			{
//				const class PathSegment *nextNode;  //   614
//				operator[](CNavPath *const this,
//						int i);  //   614
//				GetEndpoint(const class CNavPath *const this);  //   620
//				Invalidate(CNavPath *const this);  //   621
//				Invalidate(CNavPath *const this);  //   629
//			}
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   587
//		Vector(Vector *const this,
//			const Vector &v);  //   587
//		operator+(const Vector *const this,
//				const Vector &v);  //   588
//		Vector(Vector *const this,
//			const Vector &v);  //   588
//		Invalidate(CNavPath *const this);  //   515
//	}
}

/* <505d18> ../game_shared/bot/nav_path.cpp:662 */
NOBODY int CNavPathFollower::FindOurPositionOnPath(Vector *close, bool local) const
{
//	{
//		Vector along;                                   //   667
//		Vector toFeet;                                  //   667
//		Vector feet;                                    //   668
//		Vector eyes;                                    //   669
//		Vector pos;                                     //   670
//		const Vector *from;                           //   671
//		const Vector *to;                             //   671
//		float length;                                         //   672
//		float closeLength;                                    //   673
//		float closeDistSq;                                    //   674
//		int closeIndex;                                       //   675
//		float distSq;                                         //   676
//		int start;                                            //   678
//		int end;                                              //   678
//		Vector(Vector *const this,
//			const Vector &v);  //   668
//		Vector(Vector *const this,
//			const Vector &v);  //   669
//		{
//			int i;                                        //   696
//			NormalizeInPlace(Vector *const this);  //   705
//			operator-(const Vector *const this,
//					const Vector &v);  //   708
//			DotProduct(Vector &a,
//					const Vector &b);  //   711
//			operator-(const Vector *const this,
//					const Vector &v);  //   721
//			LengthSquared(const Vector *const this);  //   721
//			{
//				Vector probe;                   //   727
//				operator+(const Vector *const this,
//						const Vector &v);  //   727
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //   728
//			}
//			operator[](CNavPath *const this,
//					int i);  //   698
//			operator[](CNavPath *const this,
//					int i);  //   699
//			operator-(const Vector *const this,
//					const Vector &v);  //   702
//			operator*(float fl,
//					const Vector &v);  //   719
//			operator+(const Vector *const this,
//					const Vector &v);  //   719
//		}
//	}
}

/* <506248> ../game_shared/bot/nav_path.cpp:750 */
NOBODY int CNavPathFollower::FindPathPoint(float aheadRange, Vector *point, int *prevIndex)
{
//	{
//		int afterIndex;                                       //   753
//		Vector close;                                   //   756
//		int startIndex;                                       //   757
//		Vector initDir;                                 //   838
//		Vector feet;                                    //   841
//		Vector eyes;                                    //   842
//		float rangeSoFar;                                     //   843
//		bool visible;                                         //   846
//		Vector prevDir;                                 //   848
//		bool isCorner;                                        //   851
//		int i;                                                //   852
//		{
//			int index;                                    //   774
//			float const closeEpsilon;                      //   782
//			operator[](CNavPath *const this,
//					int i);  //   778
//			operator-(const Vector *const this,
//					const Vector &v);  //   783
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   783
//			operator[](CNavPath *const this,
//					int i);  //   793
//		}
//		{
//			Vector pos;                             //   802
//			float const closeEpsilon;                      //   805
//			operator-(const Vector *const this,
//					const Vector &v);  //   806
//			operator[](CNavPath *const this,
//					int i);  //   802
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   806
//		}
//		operator[](CNavPath *const this,
//				int i);  //   818
//		operator[](CNavPath *const this,
//				int i);  //   820
//		operator[](CNavPath *const this,
//				int i);  //   818
//		operator[](CNavPath *const this,
//				int i);  //   831
//		operator[](CNavPath *const this,
//				int i);  //   833
//		operator[](CNavPath *const this,
//				int i);  //   831
//		operator[](CNavPath *const this,
//				int i);  //   838
//		operator[](CNavPath *const this,
//				int i);  //   838
//		operator-(const Vector *const this,
//				const Vector &v);  //   838
//		NormalizeInPlace(Vector *const this);  //   839
//		Vector(Vector *const this,
//			const Vector &v);  //   841
//		{
//			Vector pos;                             //   855
//			Vector to;                              //   856
//			Vector dir;                             //   857
//			Vector probe;                           //   876
//			Vector along;                           //   897
//			operator[](CNavPath *const this,
//					int i);  //   855
//			Vector(Vector *const this,
//				const Vector &v);  //   855
//			operator[](CNavPath *const this,
//					int i);  //   856
//			operator-(const Vector *const this,
//					const Vector &v);  //   856
//			Normalize(const Vector *const this);  //   857
//			DotProduct(Vector &a,
//					const Vector &b);  //   860
//			DotProduct(Vector &a,
//					const Vector &b);  //   867
//			operator+(const Vector *const this,
//					const Vector &v);  //   876
//			IsWalkableTraceLineClear(Vector &from,
//						Vector &to,
//						unsigned int flags);  //   877
//			operator[](CNavPath *const this,
//					int i);  //   886
//			operator[](CNavPath *const this,
//					int i);  //   886
//			operator[](CNavPath *const this,
//					int i);  //   897
//			operator-(const Vector *const this,
//					const Vector &v);  //   897
//			Length2D(const Vector *const this);  //   898
//			operator-(const Vector *const this,
//					const Vector &v);  //   897
//		}
//		Vector(Vector *const this,
//			const Vector &v);  //   842
//		operator[](CNavPath *const this,
//				int i);  //   916
//		{
//			const Vector *afterPoint;             //   921
//			const Vector *beforePoint;            //   922
//			Vector to;                              //   924
//			float length;                                 //   925
//			float t;                                      //   927
//			operator[](CNavPath *const this,
//					int i);  //   921
//			operator[](CNavPath *const this,
//					int i);  //   922
//			operator-(const Vector *const this,
//					const Vector &v);  //   924
//			Length2D(const Vector *const this);  //   925
//			operator*(float fl,
//					const Vector &v);  //   934
//			{
//				float const sightStepSize;             //   939
//				float dt;                             //   940
//				Vector probe;                   //   942
//				operator+(const Vector *const this,
//						const Vector &v);  //   942
//				IsWalkableTraceLineClear(Vector &from,
//							Vector &to,
//							unsigned int flags);  //   943
//				operator+(const Vector *const this,
//						const Vector &v);  //   946
//				operator*(float fl,
//						const Vector &v);  //   946
//			}
//			operator+(const Vector *const this,
//					const Vector &v);  //   934
//		}
//		{
//			float const epsilon;                           //   957
//			class Vector2D toPoint;                       //   958
//			class Vector2D centroid;                      //   959
//			DotProduct(const class Vector2D &a,
//					const class Vector2D &b);  //   964
//			IsLengthLessThan(const class Vector2D *const this,
//					float length);  //   964
//			{
//				int i;                                //   966
//				operator[](CNavPath *const this,
//						int i);  //   969
//				operator[](CNavPath *const this,
//						int i);  //   973
//				operator[](CNavPath *const this,
//						int i);  //   971
//				IsLengthGreaterThan(const class Vector2D *const this,
//							float length);  //   971
//			}
//		}
//	}
}

/* <507004> ../game_shared/bot/nav_path.cpp:1000 */
NOBODY void CNavPathFollower::FeelerReflexAdjustment(Vector *goalPosition, float height)
{
//	{
//		Vector dir;                                     //  1006
//		Vector lat;                                     //  1010
//		float const feelerOffset;                              //  1012
//		float const feelerLengthRun;                           //  1013
//		float const feelerLengthWalk;                          //  1014
//		float const feelerHeight;                              //  1016
//		float feelerLength;                                   //  1018
//		float ground;                                         //  1025
//		Vector normal;                                  //  1026
//		Vector feet;                                    //  1037
//		Vector from;                                    //  1040
//		Vector to;                                      //  1041
//		bool leftClear;                                       //  1043
//		bool rightClear;                                      //  1057
//		float const avoidRange;                                //  1070
//		NormalizeInPlace(Vector *const this);  //  1008
//		CrossProduct(Vector &a,
//				const Vector &b);  //  1031
//		IsWalkableTraceLineClear(Vector &from,
//					Vector &to,
//					unsigned int flags);  //  1043
//		CrossProduct(Vector &a,
//				const Vector &b);  //  1034
//		Vector(Vector *const this,
//			const Vector &v);  //  1037
//		operator*(float fl,
//				const Vector &v);  //  1040
//		operator+(const Vector *const this,
//				const Vector &v);  //  1040
//		operator*(float fl,
//				const Vector &v);  //  1041
//		operator+(const Vector *const this,
//				const Vector &v);  //  1041
//		Vector(Vector *const this,
//			const Vector &v);  //  1049
//		Vector(Vector *const this,
//			const Vector &v);  //  1049
//		operator-(const Vector *const this,
//				const Vector &v);  //  1054
//		IsWalkableTraceLineClear(Vector &from,
//					Vector &to,
//					unsigned int flags);  //  1057
//		operator+(const Vector *const this,
//				const Vector &v);  //  1055
//		Vector(Vector *const this,
//			const Vector &v);  //  1063
//		Vector(Vector *const this,
//			const Vector &v);  //  1063
//		operator*(float fl,
//				const Vector &v);  //  1077
//		operator+(const Vector *const this,
//				const Vector &v);  //  1077
//		operator*(float fl,
//				const Vector &v);  //  1086
//		operator-(const Vector *const this,
//				const Vector &v);  //  1086
//		Vector(Vector *const this,
//			const Vector &v);  //  1065
//		Vector(Vector *const this,
//			const Vector &v);  //  1065
//		Vector(Vector *const this,
//			const Vector &v);  //  1051
//		Vector(Vector *const this,
//			const Vector &v);  //  1051
//	}
}

/* <507a31> ../game_shared/bot/nav_path.cpp:1098 */
NOBODY CStuckMonitor::CStuckMonitor(void)
{
//	IntervalTimer(IntervalTimer *const this);  //  1098
}

/* <507a73> ../game_shared/bot/nav_path.cpp:1108 */
NOBODY void CStuckMonitor::Reset(void)
{
}

/* <507a96> ../game_shared/bot/nav_path.cpp:1119 */
NOBODY void CStuckMonitor::Update(CImprov *improv)
{
//	{
//		float const unstuckRange;                              //  1124
//		operator-(const Vector *const this,
//				const Vector &v);  //  1125
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //  1125
//		Reset(CStuckMonitor *const this);  //  1128
//	}
//	{
//		Vector vel;                                     //  1137
//		float moveDist;                                       //  1148
//		float deltaT;                                         //  1150
//		operator-(const Vector *const this,
//				const Vector &v);  //  1137
//		Length(const Vector *const this);  //  1148
//		{
//			float avgVel;                                 //  1170
//			float stuckVel;                               //  1177
//			{
//				int t;                                //  1171
//			}
//			Start(IntervalTimer *const this);  //  1182
//		}
//	}
}
