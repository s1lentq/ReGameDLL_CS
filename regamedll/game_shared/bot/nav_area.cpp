#include "precompiled.h"

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

// long STL names get truncated in browse info.
#pragma warning(disable : 4786)

#include <list>
#include <vector>
#include <algorithm>

#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif // _WIN32

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

unsigned int CNavArea::m_nextID = 1;
unsigned int CNavArea::m_masterMarker = 1;

unsigned int HidingSpot::m_nextID = 1;
unsigned int HidingSpot::m_masterMarker = 0;

NavLadderList TheNavLadderList;
HidingSpotList TheHidingSpotList;
NavAreaList TheNavAreaList;
CNavAreaGrid TheNavAreaGrid;

CNavArea *CNavArea::m_openList = NULL;
bool CNavArea::m_isReset = false;

FILE_GLOBAL float lastDrawTimestamp = 0.0f;
FILE_GLOBAL NavAreaList goodSizedAreaList;

FILE_GLOBAL CNavArea *markedArea = NULL;
FILE_GLOBAL CNavArea *lastSelectedArea = NULL;
FILE_GLOBAL NavCornerType markedCorner = NUM_CORNERS;

FILE_GLOBAL bool isCreatingNavArea = false;
FILE_GLOBAL bool isAnchored = false;
FILE_GLOBAL Vector anchor;

FILE_GLOBAL bool isPlaceMode = false;
FILE_GLOBAL bool isPlacePainting = false;

FILE_GLOBAL float editTimestamp = 0.0f;

FILE_GLOBAL unsigned int BlockedID[ MAX_BLOCKED_AREAS ];
FILE_GLOBAL int BlockedIDCount = 0;

#else // HOOK_GAMEDLL

unsigned int IMPLEMENT_ARRAY_CLASS(CNavArea, m_nextID);
unsigned int IMPLEMENT_ARRAY_CLASS(CNavArea, m_masterMarker);

unsigned int IMPLEMENT_ARRAY_CLASS(HidingSpot, m_nextID);
unsigned int IMPLEMENT_ARRAY_CLASS(HidingSpot, m_masterMarker);

NavLadderList TheNavLadderList;
HidingSpotList TheHidingSpotList;
NavAreaList TheNavAreaList;
CNavAreaGrid TheNavAreaGrid;
CNavArea *IMPLEMENT_ARRAY_CLASS(CNavArea, m_openList);
bool IMPLEMENT_ARRAY_CLASS(CNavArea, m_isReset);

float lastDrawTimestamp;
NavAreaList goodSizedAreaList;
CNavArea *markedArea;
CNavArea *lastSelectedArea;
NavCornerType markedCorner;
bool isCreatingNavArea;
//bool isAnchored;
//Vector anchor;
//bool isPlaceMode;
bool isPlacePainting;
float editTimestamp;

unsigned int BlockedID[ MAX_BLOCKED_AREAS ];
int BlockedIDCount;

#endif // HOOK_GAMEDLL

/* <4c31b5> ../game_shared/bot/nav_area.cpp:63 */
NOXREF FILE_GLOBAL void buildGoodSizedList(void)
{
	const float minSize = 200.0f;

	NavAreaList::iterator iter;
	for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); iter++)
	{
		CNavArea *area = *iter;

		// skip the small areas
		const Extent *extent = area->GetExtent();
		if (extent->SizeX() < minSize || extent->SizeY() < minSize)
			continue;

		goodSizedAreaList.push_back(area);
	}
}

/* <4c5551> ../game_shared/bot/nav_area.cpp:87 */
void DestroyHidingSpots(void)
{
	// remove all hiding spot references from the nav areas
	for (NavAreaList::iterator areaIter = TheNavAreaList.begin(); areaIter != TheNavAreaList.end(); areaIter++)
	{
		CNavArea *area = *areaIter;
		area->m_hidingSpotList.clear();
	}

	IMPLEMENT_ARRAY_CLASS(HidingSpot, m_nextID) = 0;

	// free all the HidingSpots
	for (HidingSpotList::iterator iter = TheHidingSpotList.begin(); iter != TheHidingSpotList.end(); iter++)
		delete *iter;

	TheHidingSpotList.clear();
}

/* <4c578e> ../game_shared/bot/nav_area.cpp:109 */
NOBODY HidingSpot::HidingSpot(void)
{
//	push_back(list<HidingSpot*, std::allocator<HidingSpot*>>::HidingSpot(//			const value_type &__x);  //   115
}

/* <4c588a> ../game_shared/bot/nav_area.cpp:121 */
NOBODY HidingSpot::HidingSpot(const Vector *pos, unsigned char flags)
{
//	push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//			const value_type &__x);  //   127
}

/* <4c5994> ../game_shared/bot/nav_area.cpp:130 */
NOBODY void HidingSpot::Save(int fd, unsigned int version) const
{
}

/* <4c5bb0> ../game_shared/bot/nav_area.cpp:151 */
HidingSpot *GetHidingSpotByID(unsigned int id)
{
//	{
//		iterator iter;                                        //   153
//		{
//			class HidingSpot *spot;                      //   155
//		}
//		operator++(_List_iterator<HidingSpot*> *const this);  //   153
//	}
}

/* <4c5c30> ../game_shared/bot/nav_area.cpp:169 */
NOBODY void CNavArea::Initialize(void)
{
//	{
//		int i;                                                //   177
//	}
}

/* <4c59dc> ../game_shared/bot/nav_area.cpp:137 */
NOBODY void HidingSpot::Load(SteamFile *file, unsigned int version)
{
//	Read(SteamFile *const this,
//		void *data,
//		int length);  //   139
//	Read(SteamFile *const this,
//		void *data,
//		int length);  //   140
//	Read(SteamFile *const this,
//		void *data,
//		int length);  //   141
}

/* <4c5c82> ../game_shared/bot/nav_area.cpp:198 */
NOBODY CNavArea::CNavArea(void)
{
//	Initialize(CNavArea *const this);  //   200
//	list(list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //   198
//	list(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //   198
//	list(list<NavConnect, std::allocator<NavConnect>> *const this);  //   198
//	list(list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //   198
//	list(list<CNavArea*, std::allocator<CNavArea*>> *const this);  //   198
}

/* <4c5ed7> ../game_shared/bot/nav_area.cpp:207 */
NOBODY CNavArea::CNavArea(const Vector *corner, const Vector *otherCorner)
{
//	list(list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //   207
//	list(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //   207
//	list(list<NavConnect, std::allocator<NavConnect>> *const this);  //   207
//	list(list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //   207
//	list(list<CNavArea*, std::allocator<CNavArea*>> *const this);  //   207
//	Initialize(CNavArea *const this);  //   209
}

/* <4c610d> ../game_shared/bot/nav_area.cpp:248 */
NOBODY CNavArea::CNavArea(const Vector *nwCorner, const Vector *neCorner, const Vector *seCorner, const Vector *swCorner)
{
//	list(list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //   248
//	list(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //   248
//	list(list<NavConnect, std::allocator<NavConnect>> *const this);  //   248
//	list(list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //   248
//	list(list<CNavArea*, std::allocator<CNavArea*>> *const this);  //   248
//	Initialize(CNavArea *const this);  //   250
}

/* <4c63a4> ../game_shared/bot/nav_area.cpp:268 */
NOBODY CNavArea::CNavArea(CNavNode *nwNode, class CNavNode *neNode, class CNavNode *seNode, class CNavNode *swNode)
{
//	list(list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //   268
//	list(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //   268
//	list(list<NavConnect, std::allocator<NavConnect>> *const this);  //   268
//	list(list<CNavLadder*, std::allocator<CNavLadder*>> *const this);  //   268
//	list(list<CNavArea*, std::allocator<CNavArea*>> *const this);  //   268
//	Initialize(CNavArea *const this);  //   270
//	AssignNodes(CNavArea *const this,
//			class CNavArea *area);  //   288
}

/* <4d58d7> ../game_shared/bot/nav_area.cpp:295 */
NOBODY CNavArea::~CNavArea(void)
{
	// if we are resetting the system, don't bother cleaning up - all areas are being destroyed
	if (IMPLEMENT_ARRAY(m_isReset))
	{
		return;
	}

	// tell the other areas we are going away
	//NavAreaList::iterator iter;
	//for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	//{
	//	CNavArea *area = *iter;

	//	if (area == this)
	//		continue;

	//	area->OnDestroyNotify(this);
	//}

	//// unhook from ladders
	//for (int i = 0; i < NUM_LADDER_DIRECTIONS; ++i)
	//{
	//	for (NavLadderList::iterator liter = m_ladder[i].begin(); liter != m_ladder[i].end(); ++liter)
	//	{
	//		CNavLadder *ladder = *liter;

	//		ladder->OnDestroyNotify(this);
	//	}
	//}

	// remove the area from the grid
	//TheNavAreaGrid.RemoveNavArea(this);
}

/* <4c67f0> ../game_shared/bot/nav_area.cpp:333 */
NOBODY void CNavArea::OnDestroyNotify(CNavArea *dead)
{
	NavConnect con;
	con.area = dead;
	for (int d = 0; d < NUM_DIRECTIONS; ++d)
		m_connect[ d ].remove(con);

	m_overlapList.remove(dead);
}

/* <4c6b75> ../game_shared/bot/nav_area.cpp:347 */
NOBODY void CNavArea::ConnectTo(CNavArea *area, NavDirType dir)
{
//	{
//		union NavConnect con;                                 //   354
//		{
//			iterator iter;                                //   350
//			operator++(_List_iterator<NavConnect> *const this);  //   350
//		}
//		push_back(list<NavConnect, std::allocator<NavConnect>> *const this,
//				const value_type &__x);  //   356
//	}
}

/* <4c6cd3> ../game_shared/bot/nav_area.cpp:366 */
NOBODY void CNavArea::Disconnect(CNavArea *area)
{
//	{
//		union NavConnect connect;                             //   368
//		{
//			int dir;                                      //   371
//			remove(list<NavConnect, std::allocator<NavConnect>> *const this,
//				const value_type &__value);  //   372
//		}
//	}
}

/* <4d8fa5> ../game_shared/bot/nav_area.cpp:380 */
NOBODY void CNavArea::FinishMerge(CNavArea *adjArea)
{
//	AssignNodes(CNavArea *const this,
//			class CNavArea *area);  //   394
//	remove(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//		const value_type &__value);  //   400
}

/* <4c6e85> ../game_shared/bot/nav_area.cpp:408 */
NOBODY void CNavArea::MergeAdjacentConnections(CNavArea *adjArea)
{
//	{
//		iterator iter;                                        //   411
//		int dir;                                              //   412
//		{
//			union NavConnect connect;                     //   417
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   420
//		}
//		operator++(_List_iterator<NavConnect> *const this);  //   415
//		{
//			union NavConnect connect;                     //   427
//			remove(list<NavConnect, std::allocator<NavConnect>> *const this,
//				const value_type &__value);  //   430
//		}
//		{
//			iterator areaIter;                            //   439
//			{
//				class CNavArea *area;                //   441
//				{
//					bool connected;               //   449
//					{
//						union NavConnect connect;   //   464
//						remove(list<NavConnect, std::allocator<NavConnect>> *const this,
//							const value_type &__value);  //   470
//						remove(list<NavConnect, std::allocator<NavConnect>> *const this,
//							const value_type &__value);  //   466
//						push_back(list<NavConnect, std::allocator<NavConnect>> *const this,
//								const value_type &__x);  //   474
//					}
//					operator++(_List_iterator<NavConnect> *const this);  //   450
//					{
//						union NavConnect connect;   //   452
//					}
//				}
//			}
//			operator++(_List_iterator<CNavArea*> *const this);  //   439
//		}
//	}
}

/* <4c760a> ../game_shared/bot/nav_area.cpp:486 */
NOBODY void CNavArea::AssignNodes(CNavArea *area)
{
//	{
//		class CNavNode *horizLast;                           //   488
//		{
//			class CNavNode *vertNode;                    //   490
//			{
//				class CNavNode *horizNode;           //   492
//				AssignArea(CNavNode *const this,
//						class CNavArea *area);  //   494
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //   492
//			}
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //   490
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //   497
//		}
//	}
}

/* <4d690e> ../game_shared/bot/nav_area.cpp:507 */
NOBODY bool CNavArea::SplitEdit(bool splitAlongX, float splitEdge, CNavArea **outAlpha, CNavArea **outBeta)
{
//	{
//		class CNavArea *alpha;                               //   509
//		class CNavArea *beta;                                //   510
//		ConnectTo(CNavArea *const this,
//				class CNavArea *area,
//				enum NavDirType dir);  //   580
//		SetAttributes(CNavArea *const this,
//				unsigned char bits);  //   588
//		SetAttributes(CNavArea *const this,
//				unsigned char bits);  //   589
//		SetPlace(CNavArea *const this,
//			Place place);  //   592
//		SetPlace(CNavArea *const this,
//			Place place);  //   593
//		remove(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//			const value_type &__value);  //   603
//		ConnectTo(CNavArea *const this,
//				class CNavArea *area,
//				enum NavDirType dir);  //   543
//		ConnectTo(CNavArea *const this,
//				class CNavArea *area,
//				enum NavDirType dir);  //   544
//	}
}

/* <4c7708> ../game_shared/bot/nav_area.cpp:615 */
NOBODY bool CNavArea::IsConnected(const CNavArea *area, NavDirType dir) const
{
	// we are connected to ourself
	if (area == this)
		return true;

	NavConnectList::const_iterator iter;

	if (dir == NUM_DIRECTIONS)
	{
		// search all directions
		for (int d = 0; d < NUM_DIRECTIONS; ++d)
		{
			for (iter = m_connect[ d ].begin(); iter != m_connect[ d ].end(); ++iter)
			{
				if (area == (*iter).area)
					return true;
			}
		}

		// check ladder connections
		NavLadderList::const_iterator liter;
		for (liter = m_ladder[ LADDER_UP ].begin(); liter != m_ladder[ LADDER_UP ].end(); ++liter)
		{
			CNavLadder *ladder = *liter;

			if (ladder->m_topBehindArea == area || ladder->m_topForwardArea == area || ladder->m_topLeftArea == area || ladder->m_topRightArea == area)
				return true;
		}

		for (liter = m_ladder[ LADDER_DOWN ].begin(); liter != m_ladder[ LADDER_DOWN ].end(); ++liter)
		{
			CNavLadder *ladder = *liter;

			if (ladder->m_bottomArea == area)
				return true;
		}
	}
	else
	{
		// check specific direction
		for (iter = m_connect[ dir ].begin(); iter != m_connect[ dir ].end(); ++iter)
		{
			if (area == (*iter).area)
				return true;
		}
	}

	return false;
}

/* <4c89fd> ../game_shared/bot/nav_area.cpp:674 */
NOBODY float CNavArea::ComputeHeightChange(const CNavArea *area)
{
//	{
//		float ourZ;                                           //   676
//		float areaZ;                                          //   677
//	}
}

/* <4c9e37> ../game_shared/bot/nav_area.cpp:687 */
NOBODY void CNavArea::FinishSplitEdit(CNavArea *newArea, NavDirType ignoreEdge)
{
//	GetZ(const class CNavArea *const this,
//		float x,
//		float y);  //   693
//	GetZ(const class CNavArea *const this,
//		float x,
//		float y);  //   694
//	{
//		int d;                                                //   697
//		{
//			int count;                                    //   702
//			GetAdjacentCount(const class CNavArea *const this,
//					enum NavDirType dir);  //   702
//			{
//				int a;                                //   704
//				{
//					class CNavArea *adj;         //   706
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //   726
//					GetAdjacentArea(const class CNavArea *const this,
//							enum NavDirType dir,
//							int i);  //   706
//					IsOverlappingY(const class CNavArea *const this,
//							const class CNavArea *area);  //   724
//					OppositeDirection(NavDirType dir);  //   729
//					IsConnected(const class CNavArea *const this,
//							const class CNavArea *area,
//							enum NavDirType dir);  //   729
//					OppositeDirection(NavDirType dir);  //   730
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //   730
//					IsOverlappingX(const class CNavArea *const this,
//							const class CNavArea *area);  //   712
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //   714
//					OppositeDirection(NavDirType dir);  //   717
//					IsConnected(const class CNavArea *const this,
//							const class CNavArea *area,
//							enum NavDirType dir);  //   717
//					OppositeDirection(NavDirType dir);  //   718
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //   718
//				}
//			}
//		}
//	}
//	push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//			const value_type &__x);  //   737
}

/* <4c8b85> ../game_shared/bot/nav_area.cpp:745 */
NOBODY bool CNavArea::SpliceEdit(CNavArea *other)
{
//	{
//		class CNavArea *newArea;                             //   747
//		Vector nw;                                      //   748
//		Vector ne;                                      //   748
//		Vector se;                                      //   748
//		Vector sw;                                      //   748
//		{
//			float top;                                    //   753
//			float bottom;                                 //   754
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   774
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   775
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   777
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   778
//		}
//		{
//			float left;                                   //   815
//			float right;                                  //   816
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   840
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   836
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   837
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   839
//		}
//		{
//			float left;                                   //   845
//			float right;                                  //   846
//		}
//		{
//			float top;                                    //   783
//			float bottom;                                 //   784
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   804
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   805
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   807
//			ConnectTo(CNavArea *const this,
//					class CNavArea *area,
//					enum NavDirType dir);  //   808
//		}
//		SetPlace(CNavArea *const this,
//			Place place);  //   886
//		SetPlace(CNavArea *const this,
//			Place place);  //   898
//		push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//				const value_type &__x);  //   901
//		SetPlace(CNavArea *const this,
//			Place place);  //   896
//	}
}

/* <4d72dd> ../game_shared/bot/nav_area.cpp:911 */
NOBODY bool CNavArea::MergeEdit(CNavArea *adj)
{
//	{
//		float const tolerance;                                 //   917
//		bool merge;                                           //   918
//		class Extent origExtent;                              //   930
//		Extent(Extent *const this,
//			const class Extent &const);  //   930
//		GetZ(const class CNavArea *const this,
//			float x,
//			float y);  //   944
//		GetZ(const class CNavArea *const this,
//			float x,
//			float y);  //   949
//		remove(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//			const value_type &__value);  //   957
//		GetZ(const class CNavArea *const this,
//			float x,
//			float y);  //   946
//		GetZ(const class CNavArea *const this,
//			float x,
//			float y);  //   951
//	}
}

/* <4c78a9> ../game_shared/bot/nav_area.cpp:964 */
void ApproachAreaAnalysisPrep(void)
{
	// collect "good-sized" areas for computing approach areas
	buildGoodSizedList();
}

/* <4c7a37> ../game_shared/bot/nav_area.cpp:971 */
void CleanupApproachAreaAnalysisPrep(void)
{
	goodSizedAreaList.clear();
}

/* <4c7b18> ../game_shared/bot/nav_area.cpp:980 */
void DestroyLadders(void)
{
	while (!TheNavLadderList.empty())
	{
		CNavLadder *ladder = TheNavLadderList.front();
		TheNavLadderList.pop_front();
		delete ladder;
	}
}

void (*pDestroyNavigationMap)(void);

/* <4d6733> ../game_shared/bot/nav_area.cpp:994 */
void __declspec(naked) DestroyNavigationMap(void)
{
	__asm
	{
		jmp pDestroyNavigationMap
	}

	//IMPLEMENT_ARRAY_CLASS(CNavArea, m_isReset) = true;

	//// remove each element of the list and delete them
	//while (!TheNavAreaList.empty())
	//{
	//	CNavArea *area = TheNavAreaList.front();
	//	TheNavAreaList.pop_front();
	//	//delete area;//TODO: FIX ME stl m_connect
	//}

	////TheNavAreaList.clear();
	//IMPLEMENT_ARRAY_CLASS(CNavArea, m_isReset) = false;

	//// destroy ladder representations
	//DestroyLadders();

	//// destroy all hiding spots
	//DestroyHidingSpots();

	//// destroy navigation nodes created during map learning
	//CNavNode *node, *next;
	//for (node = IMPLEMENT_ARRAY_CLASS(CNavNode, m_list); node; node = next)
	//{
	//	next = node->m_next;
	//	delete node;
	//}

	//IMPLEMENT_ARRAY_CLASS(CNavNode, m_list) = NULL;

	//// reset the grid
	//TheNavAreaGrid.Reset();
}

/* <4c7e9a> ../game_shared/bot/nav_area.cpp:1046 */
NOBODY void CNavArea::Strip(void)
{
//	clear(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //  1049
}

/* <4c7c70> ../game_shared/bot/nav_area.cpp:1031 */
NOBODY void StripNavigationAreas(void)
{
//	{
//		iterator iter;                                        //  1033
//		{
//			class CNavArea *area;                        //  1036
//			Strip(CNavArea *const this);  //  1038
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //  1034
//	}
}

/* <4d1b9c> ../game_shared/bot/nav_area.cpp:1057 */
NOBODY inline CNavArea *FindFirstAreaInDirection(const Vector *start, NavDirType dir, float range, float beneathLimit, CBaseEntity *traceIgnore, Vector *closePos)
{
//	{
//		class CNavArea *area;                                //  1059
//		Vector pos;                                     //  1061
//		int end;                                              //  1063
//		{
//			int i;                                        //  1065
//			{
//				TraceResult result;                   //  1070
//			}
//		}
//	}
}

/* <4c3de4> ../game_shared/bot/nav_area.cpp:1102 */
NOBODY inline bool testJumpDown(const Vector *fromPos, const Vector *toPos)
{
//	{
//		float dz;                                             //  1104
//		Vector from;                                    //  1120
//		Vector to;                                      //  1121
//		TraceResult result;                                   //  1123
//	}
}

/* <4d1b44> ../game_shared/bot/nav_area.cpp:1138 */
NOBODY inline CNavArea *findJumpDownArea(const Vector *fromPos, NavDirType dir)
{
//	{
//		Vector start;                                   //  1140
//		Vector toPos;                                   //  1143
//		class CNavArea *downArea;                            //  1144
//	}
}

/* <4d1c46> ../game_shared/bot/nav_area.cpp:1157 */
NOBODY void ConnectGeneratedAreas(void)
{
//	{
//		iterator iter;                                        //  1161
//		{
//			class CNavArea *area;                        //  1163
//			class CNavNode *node;                        //  1169
//			{
//				class CNavNode *adj;                 //  1172
//				{
//					class CNavArea *downArea;    //  1180
//					findJumpDownArea(const Vector *fromPos,
//							enum NavDirType dir);  //  1180
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //  1182
//				}
//				ConnectTo(CNavArea *const this,
//						class CNavArea *area,
//						enum NavDirType dir);  //  1176
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1172
//			}
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1170
//			{
//				class CNavNode *adj;                 //  1189
//				ConnectTo(CNavArea *const this,
//						class CNavArea *area,
//						enum NavDirType dir);  //  1193
//				{
//					class CNavArea *downArea;    //  1197
//					findJumpDownArea(const Vector *fromPos,
//							enum NavDirType dir);  //  1197
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //  1199
//				}
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1189
//			}
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1187
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1207
//			{
//				class CNavNode *end;                 //  1210
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1210
//				{
//					class CNavNode *adj;         //  1214
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //  1218
//					{
//						class CNavArea *downArea;    //  1222
//						findJumpDownArea(const Vector *fromPos,
//								enum NavDirType dir);  //  1222
//						ConnectTo(CNavArea *const this,
//								class CNavArea *area,
//								enum NavDirType dir);  //  1224
//					}
//					GetConnectedNode(const class CNavNode *const this,
//							enum NavDirType dir);  //  1214
//				}
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1212
//			}
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1231
//			{
//				class CNavNode *end;                 //  1234
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1234
//				{
//					class CNavNode *adj;         //  1237
//					ConnectTo(CNavArea *const this,
//							class CNavArea *area,
//							enum NavDirType dir);  //  1241
//					{
//						class CNavArea *downArea;    //  1245
//						findJumpDownArea(const Vector *fromPos,
//								enum NavDirType dir);  //  1245
//						ConnectTo(CNavArea *const this,
//								class CNavArea *area,
//								enum NavDirType dir);  //  1247
//					}
//					GetConnectedNode(const class CNavNode *const this,
//							enum NavDirType dir);  //  1237
//				}
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1235
//			}
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //  1161
//	}
}

/* <4d922b> ../game_shared/bot/nav_area.cpp:1259 */
NOBODY void MergeGeneratedAreas(void)
{
//	{
//		bool merged;                                          //  1263
//		{
//			iterator iter;                                //  1269
//			{
//				class CNavArea *area;                //  1271
//				iterator citer;                       //  1274
//				end(list<NavConnect, std::allocator<NavConnect>> *const this);  //  1275
//				operator++(_List_iterator<NavConnect> *const this);  //  1275
//				{
//					class CNavArea *adjArea;     //  1277
//				}
//				end(list<NavConnect, std::allocator<NavConnect>> *const this);  //  1302
//				operator++(_List_iterator<NavConnect> *const this);  //  1302
//				{
//					class CNavArea *adjArea;     //  1304
//				}
//				{
//					class CNavArea *adjArea;     //  1361
//				}
//				end(list<NavConnect, std::allocator<NavConnect>> *const this);  //  1359
//				operator++(_List_iterator<NavConnect> *const this);  //  1359
//				end(list<NavConnect, std::allocator<NavConnect>> *const this);  //  1331
//				operator++(_List_iterator<NavConnect> *const this);  //  1331
//				{
//					class CNavArea *adjArea;     //  1333
//				}
//			}
//			operator++(_List_iterator<CNavArea*> *const this);  //  1269
//		}
//	}
}

/* <4c342b> ../game_shared/bot/nav_area.cpp:1394 */
NOBODY inline bool IsAreaRoughlySquare(const class CNavArea *area)
{
//	{
//		float aspect;                                         //  1396
//		float const maxAspect;                                 //  1398
//		float const minAspect;                                 //  1399
//	}
}

/* <4d70f4> ../game_shared/bot/nav_area.cpp:1410 */
NOBODY void SplitX(CNavArea *area)
{
//	{
//		float split;                                          //  1415
//		float const epsilon;                                   //  1421
//		class CNavArea *alpha;                               //  1429
//		class CNavArea *beta;                                //  1429
//		IsAreaRoughlySquare(const class CNavArea *area);  //  1412
//		SnapToGrid(float *value);  //  1419
//	}
}

/* <4d6fe1> ../game_shared/bot/nav_area.cpp:1442 */
NOBODY void SplitY(CNavArea *area)
{
//	{
//		float split;                                          //  1447
//		float const epsilon;                                   //  1453
//		class CNavArea *alpha;                               //  1461
//		class CNavArea *beta;                                //  1461
//		IsAreaRoughlySquare(const class CNavArea *area);  //  1444
//		SnapToGrid(float *value);  //  1451
//	}
}

/* <4d7207> ../game_shared/bot/nav_area.cpp:1474 */
NOBODY void SquareUpAreas(void)
{
//	{
//		iterator iter;                                        //  1476
//		{
//			class CNavArea *area;                        //  1480
//			operator++(_List_iterator<CNavArea*> *const this);  //  1481
//			IsAreaRoughlySquare(const class CNavArea *area);  //  1483
//		}
//	}
}

/* <4c8066> ../game_shared/bot/nav_area.cpp:1503 */
NOBODY bool TestArea(CNavNode *node, int width, int height)
{
//	{
//		Vector normal;                                  //  1505
//		float d;                                              //  1506
//		float const offPlaneTolerance;                         //  1508
//		class CNavNode *vertNode;                            //  1510
//		class CNavNode *horizNode;                           //  1510
//		{
//			int y;                                        //  1513
//			{
//				int x;                                //  1517
//				{
//					float dist;                   //  1536
//					DotProduct(Vector &a,
//							const Vector &b);  //  1536
//				}
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1529
//			}
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1542
//			{
//				float dist;                           //  1549
//				DotProduct(Vector &a,
//						const Vector &b);  //  1549
//			}
//		}
//		Vector(Vector *const this,
//			const Vector &v);  //  1505
//		DotProduct(Vector &a,
//				const Vector &b);  //  1506
//		{
//			int x;                                        //  1560
//			{
//				float dist;                           //  1567
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1562
//				DotProduct(Vector &a,
//						const Vector &b);  //  1567
//			}
//		}
//	}
}

/* <4c82ea> ../game_shared/bot/nav_area.cpp:1582 */
NOBODY int BuildArea(CNavNode *node, int width, int height)
{
//	{
//		class CNavNode *nwNode;                              //  1586
//		class CNavNode *neNode;                              //  1587
//		class CNavNode *swNode;                              //  1588
//		class CNavNode *seNode;                              //  1589
//		class CNavNode *vertNode;                            //  1591
//		class CNavNode *horizNode;                           //  1592
//		int coveredNodes;                                     //  1594
//		class CNavArea *area;                                //  1629
//		{
//			int y;                                        //  1596
//			{
//				int x;                                //  1600
//				Cover(CNavNode *const this);  //  1602
//				GetConnectedNode(const class CNavNode *const this,
//						enum NavDirType dir);  //  1605
//			}
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1611
//		}
//		{
//			int x;                                        //  1617
//			GetConnectedNode(const class CNavNode *const this,
//					enum NavDirType dir);  //  1619
//		}
//		push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//				const value_type &__x);  //  1630
//		SetAttributes(CNavArea *const this,
//				unsigned char bits);  //  1633
//	}
}

/* <4d3581> ../game_shared/bot/nav_area.cpp:1645 */
NOBODY void BuildLadders(void)
{
//	{
//		TraceResult result;                                   //  1650
//		class CBaseEntity *entity;                           //  1651
//		DestroyLadders(void);  //  1648
//		edict(CBaseEntity *const this);  //  1652
//		FNullEnt(const edict_t *pent);  //  1652
//		{
//			class CNavLadder *ladder;                    //  1654
//			float xSize;                                  //  1666
//			float ySize;                                  //  1667
//			Vector along;                           //  1698
//			float length;                                 //  1699
//			Vector on;                              //  1700
//			Vector out;                             //  1700
//			float const minLadderClearance;                //  1701
//			float const inc;                               //  1704
//			float t;                                      //  1705
//			float const nearLadderRange;                   //  1746
//			Vector center;                          //  1753
//			float topZ;                                   //  1813
//			bool topAdjusted;                             //  1814
//			class CNavArea *topAreaList;                 //  1815
//			{
//				Vector from;                    //  1685
//				Vector to;                      //  1686
//				operator+(const Vector *const this,
//						const Vector &v);  //  1685
//				operator+(const Vector *const this,
//						const Vector &v);  //  1686
//			}
//			{
//				Vector from;                    //  1672
//				Vector to;                      //  1673
//				operator+(const Vector *const this,
//						const Vector &v);  //  1672
//				operator+(const Vector *const this,
//						const Vector &v);  //  1673
//			}
//			CNavLadder(CNavLadder *const this);  //  1654
//			operator-(const Vector *const this,
//					const Vector &v);  //  1698
//			NormalizeInPlace(Vector *const this);  //  1699
//			AddDirectionVector(Vector *v,
//						enum NavDirType dir,
//						float amount);  //  1711
//			operator*(float fl,
//					const Vector &v);  //  1708
//			operator+(const Vector *const this,
//					const Vector &v);  //  1708
//			operator-(const Vector *const this,
//					const Vector &v);  //  1741
//			Length(const Vector *const this);  //  1741
//			DirectionToVector2D(NavDirType dir,
//						class Vector2D *v);  //  1743
//			operator+(const Vector *const this,
//					const Vector &v);  //  1753
//			AddDirectionVector(Vector *v,
//						enum NavDirType dir,
//						float amount);  //  1754
//			AddLadderUp(CNavArea *const this,
//					class CNavLadder *ladder);  //  1764
//			operator+(const Vector *const this,
//					const Vector &v);  //  1772
//			AddDirectionVector(Vector *v,
//						enum NavDirType dir,
//						float amount);  //  1773
//			FindFirstAreaInDirection(const Vector *start,
//						enum NavDirType dir,
//						float range,
//						float beneathLimit,
//						class CBaseEntity *traceIgnore,
//						Vector *closePos);  //  1776
//			FindFirstAreaInDirection(const Vector *start,
//						enum NavDirType dir,
//						float range,
//						float beneathLimit,
//						class CBaseEntity *traceIgnore,
//						Vector *closePos);  //  1781
//			FindFirstAreaInDirection(const Vector *start,
//						enum NavDirType dir,
//						float range,
//						float beneathLimit,
//						class CBaseEntity *traceIgnore,
//						Vector *closePos);  //  1786
//			FindFirstAreaInDirection(const Vector *start,
//						enum NavDirType dir,
//						float range,
//						float beneathLimit,
//						class CBaseEntity *traceIgnore,
//						Vector *closePos);  //  1791
//			AddLadderDown(CNavArea *const this,
//					class CNavLadder *ladder);  //  1801
//			AddLadderDown(CNavArea *const this,
//					class CNavLadder *ladder);  //  1804
//			AddLadderDown(CNavArea *const this,
//					class CNavLadder *ladder);  //  1807
//			AddLadderDown(CNavArea *const this,
//					class CNavLadder *ladder);  //  1810
//			{
//				int a;                                //  1821
//				{
//					class CNavArea *topArea;     //  1823
//					Vector close;           //  1827
//				}
//			}
//			{
//				Vector bottomSpot;              //  1846
//			}
//			push_back(list<CNavLadder*, std::allocator<CNavLadder*>> *const this,
//					const value_type &__x);  //  1853
//			AddDirectionVector(Vector *v,
//						enum NavDirType dir,
//						float amount);  //  1729
//			operator*(float fl,
//					const Vector &v);  //  1726
//			operator-(const Vector *const this,
//					const Vector &v);  //  1726
//		}
//	}
}

/* <4c85c3> ../game_shared/bot/nav_area.cpp:1864 */
NOBODY void MarkJumpAreas(void)
{
//	{
//		iterator iter;                                        //  1866
//		operator++(_List_iterator<CNavArea*> *const this);  //  1866
//		{
//			class CNavArea *area;                        //  1868
//			Vector u;                               //  1869
//			Vector v;                               //  1869
//			Vector normal;                          //  1880
//			CrossProduct(Vector &a,
//					const Vector &b);  //  1880
//			NormalizeInPlace(Vector *const this);  //  1881
//		}
//	}
}

/* <4d943a> ../game_shared/bot/nav_area.cpp:1899 */
NOBODY void GenerateNavigationAreaMesh(void)
{
//	{
//		int tryWidth;                                         //  1902
//		int tryHeight;                                        //  1903
//		int uncoveredNodes;                                   //  1904
//		class Extent extent;                                  //  1935
//		iterator iter;                                        //  1942
//		{
//			class CNavNode *node;                        //  1908
//			GetFirst(void);  //  1908
//			{
//				int covered;                          //  1915
//			}
//		}
//		{
//			class CNavArea *area;                        //  1945
//			const class Extent *areaExtent;             //  1946
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //  1943
//		Initialize(CNavAreaGrid *const this,
//				float minX,
//				float maxX,
//				float minY,
//				float maxY);  //  1959
//		operator++(_List_iterator<CNavArea*> *const this);  //  1961
//	}
}

/* <4c86fa> ../game_shared/bot/nav_area.cpp:1975 */
NOBODY bool CNavArea::IsOverlapping(const Vector *pos) const
{
	if (pos->x >= m_extent.lo.x && pos->x <= m_extent.hi.x &&
		pos->y >= m_extent.lo.y && pos->y <= m_extent.hi.y)
		return true;

	return false;
}

/* <4c8726> ../game_shared/bot/nav_area.cpp:1988 */
NOBODY bool CNavArea::IsOverlapping(const CNavArea *area) const
{
}

/* <4c8761> ../game_shared/bot/nav_area.cpp:2001 */
NOBODY bool CNavArea::IsOverlappingX(const CNavArea *area) const
{
}

/* <4c878d> ../game_shared/bot/nav_area.cpp:2013 */
NOBODY bool CNavArea::IsOverlappingY(const CNavArea *area) const
{
}

/* <4c8a66> ../game_shared/bot/nav_area.cpp:2025 */
NOBODY bool CNavArea::Contains(const Vector *pos) const
{
//	{
//		float ourZ;                                           //  2032
//		IsOverlapping(const class CNavArea *const this,
//				const Vector *pos);  //  2028
//		{
//			const_iterator iter;                          //  2038
//			{
//				const class CNavArea *area;         //  2040
//				float theirZ;                         //  2050
//				IsOverlapping(const class CNavArea *const this,
//						const Vector *pos);  //  2047
//			}
//			end(const class list<CNavArea*, std::allocator<CNavArea*>> *const this);  //  2038
//			operator++(_List_const_iterator<CNavArea*> *const this);  //  2038
//		}
//	}
}

/* <4c87b9> ../game_shared/bot/nav_area.cpp:2071 */
NOBODY bool CNavArea::IsCoplanar(const CNavArea *area) const
{
//	{
//		Vector u;                                       //  2073
//		Vector v;                                       //  2073
//		Vector normal;                                  //  2084
//		Vector otherNormal;                             //  2097
//		float const tolerance;                                 //  2101
//		CrossProduct(Vector &a,
//				const Vector &b);  //  2084
//		NormalizeInPlace(Vector *const this);  //  2085
//		CrossProduct(Vector &a,
//				const Vector &b);  //  2097
//		NormalizeInPlace(Vector *const this);  //  2098
//		DotProduct(Vector &a,
//				const Vector &b);  //  2102
//	}
}

/* <4c8963> ../game_shared/bot/nav_area.cpp:2114 */
//float (__fastcall *pGetZ__Vector)(const CNavArea *pthis, int i ,const Vector *pos);
float (*pGetZ__Vector)(const Vector *pos);

float __declspec(naked) CNavArea::GetZ(const Vector *pos) const
{
	__asm
	{
		jmp pGetZ__Vector
	}
	UNTESTED
		// Crash
/*
	float dx = m_extent.hi.x - m_extent.lo.x;
	float dy = m_extent.hi.y - m_extent.lo.y;

	// guard against division by zero due to degenerate areas
	if (dx == 0.0f || dy == 0.0f)
		return m_neZ;

	float u = (pos->x - m_extent.lo.x) / dx;
	float v = (pos->y - m_extent.lo.y) / dy;

	// clamp Z values to (x,y) volume
	if (u < 0.0f)
		u = 0.0f;
	else if (u > 1.0f)
		u = 1.0f;

	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;

	float northZ = m_extent.lo.z + u * (m_neZ - m_extent.lo.z);
	float southZ = m_swZ + u * (m_extent.hi.z - m_swZ);

	return northZ + v * (southZ - northZ);
*/
}


/* <4caa36> ../game_shared/bot/nav_area.cpp:2143 */
float CNavArea::GetZ(float x, float y) const
{
	Vector pos(x, y, 0.0f);
	return GetZ(&pos);
}

/* <4caab9> ../game_shared/bot/nav_area.cpp:2155 */
void CNavArea::GetClosestPointOnArea(const Vector *pos, Vector *close) const
{
	const Extent *extent = GetExtent();
	if (pos->x < extent->lo.x)
	{
		if (pos->y < extent->lo.y)
			*close = extent->lo;

		else if (pos->y > extent->hi.y)
		{
			close->x = extent->lo.x;
			close->y = extent->hi.y;
		}
		else
		{
			close->x = extent->lo.x;
			close->y = pos->y;
		}
	}
	else if (pos->x > extent->hi.x)
	{
		if (pos->y < extent->lo.y)
		{
			close->x = extent->hi.x;
			close->y = extent->lo.y;
		}
		else if (pos->y > extent->hi.y)
			*close = extent->hi;
		else
		{
			close->x = extent->hi.x;
			close->y = pos->y;
		}
	}
	else if (pos->y < extent->lo.y)
	{
		close->x = pos->x;
		close->y = extent->lo.y;
	}
	else if (pos->y > extent->hi.y)
	{
		close->x = pos->x;
		close->y = extent->hi.y;
	}
	else
		*close = *pos;

	close->z = GetZ(close);
}

/* <4cab19> ../game_shared/bot/nav_area.cpp:2224 */
NOBODY float CNavArea::GetDistanceSquaredToPoint(const Vector *pos) const
{
//	{
//		const class Extent *extent;                         //  2226
//		{
//			Vector d;                               //  2238
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //  2233
//		{
//			Vector d;                               //  2256
//			LengthSquared(const Vector *const this);  //  2260
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //  2265
//		LengthSquared(const Vector *const this);  //  2265
//		{
//			float d;                                      //  2270
//		}
//		{
//			float z;                                      //  2289
//			float d;                                      //  2290
//		}
//		{
//			float d;                                      //  2283
//		}
//		{
//			float d;                                      //  2277
//		}
//	}
}

/* <4cacac> ../game_shared/bot/nav_area.cpp:2298 */
NOBODY CNavArea *CNavArea::GetRandomAdjacentArea(NavDirType dir) const
{
//	{
//		int count;                                            //  2300
//		int which;                                            //  2301
//		int i;                                                //  2303
//		const_iterator iter;                                  //  2304
//		size(const class list<NavConnect, std::allocator<NavConnect>> *const this);  //  2300
//		operator++(_List_const_iterator<NavConnect> *const this);  //  2305
//	}
}

/* <4cadd2> ../game_shared/bot/nav_area.cpp:2322 */
NOBODY void CNavArea::ComputePortal(const CNavArea *to, NavDirType dir, Vector *center, float *halfWidth) const
{
//	{
//		float left;                                           //  2331
//		float right;                                          //  2332
//	}
//	{
//		float top;                                            //  2355
//		float bottom;                                         //  2356
//	}
}

/* <4cb0d7> ../game_shared/bot/nav_area.cpp:2378 */
NOBODY void CNavArea::ComputeClosestPointInPortal(const CNavArea *to, NavDirType dir, const Vector *fromPos, Vector *closePos) const
{
//	{
//		float const margin;                                    //  2380
//		{
//			float left;                                   //  2389
//			float right;                                  //  2390
//			float const leftMargin;                        //  2404
//			float const rightMargin;                       //  2405
//		}
//		{
//			float top;                                    //  2423
//			float bottom;                                 //  2424
//			float const topMargin;                         //  2438
//			float const bottomMargin;                      //  2439
//		}
//	}
}

/* <4cae93> ../game_shared/bot/nav_area.cpp:2455 */
NOBODY bool CNavArea::IsEdge(NavDirType dir) const
{
//	{
//		const_iterator it;                                    //  2457
//		{
//			union NavConnectconst connect;                //  2459
//			OppositeDirection(NavDirType dir);  //  2461
//			IsConnected(const class CNavArea *const this,
//					const class CNavArea *area,
//					enum NavDirType dir);  //  2461
//		}
//		operator++(_List_const_iterator<NavConnect> *const this);  //  2457
//	}
}

/* <4cb1f5> ../game_shared/bot/nav_area.cpp:2473 */
NOBODY NavDirType CNavArea::ComputeDirection(Vector *point) const
{
//	{
//		Vector to;                                      //  2491
//		operator-(const Vector *const this,
//				const Vector &v);  //  2491
//	}
}

/* <4cb26d> ../game_shared/bot/nav_area.cpp:2513 */
NOBODY void CNavArea::Draw(byte red, byte green, byte blue, int duration)
{
//	{
//		Vector nw;                                      //  2515
//		Vector ne;                                      //  2515
//		Vector sw;                                      //  2515
//		Vector se;                                      //  2515
//		float border;                                         //  2531
//		Vector(Vector *const this,
//			const Vector &v);  //  2541
//		Vector(Vector *const this,
//			const Vector &v);  //  2541
//		Vector(Vector *const this,
//			const Vector &v);  //  2542
//		Vector(Vector *const this,
//			const Vector &v);  //  2542
//		Vector(Vector *const this,
//			const Vector &v);  //  2543
//		Vector(Vector *const this,
//			const Vector &v);  //  2543
//		Vector(Vector *const this,
//			const Vector &v);  //  2544
//		Vector(Vector *const this,
//			const Vector &v);  //  2544
//		{
//			float size;                                   //  2557
//			Vector up;                              //  2558
//			Vector down;                            //  2559
//			Vector left;                            //  2562
//			Vector right;                           //  2563
//			Vector(Vector *const this,
//				const Vector &v);  //  2560
//			Vector(Vector *const this,
//				const Vector &v);  //  2560
//			Vector(Vector *const this,
//				const Vector &v);  //  2564
//			Vector(Vector *const this,
//				const Vector &v);  //  2564
//		}
//		{
//			float size;                                   //  2569
//			Vector up;                              //  2570
//			Vector down;                            //  2571
//			Vector left;                            //  2572
//			Vector right;                           //  2573
//			Vector(Vector *const this,
//				const Vector &v);  //  2574
//			Vector(Vector *const this,
//				const Vector &v);  //  2574
//			Vector(Vector *const this,
//				const Vector &v);  //  2575
//			Vector(Vector *const this,
//				const Vector &v);  //  2575
//			Vector(Vector *const this,
//				const Vector &v);  //  2576
//			Vector(Vector *const this,
//				const Vector &v);  //  2576
//			Vector(Vector *const this,
//				const Vector &v);  //  2577
//			Vector(Vector *const this,
//				const Vector &v);  //  2577
//		}
//		Vector(Vector *const this,
//			const Vector &v);  //  2551
//		Vector(Vector *const this,
//			const Vector &v);  //  2551
//		Vector(Vector *const this,
//			const Vector &v);  //  2552
//		Vector(Vector *const this,
//			const Vector &v);  //  2552
//		Vector(Vector *const this,
//			const Vector &v);  //  2547
//		Vector(Vector *const this,
//			const Vector &v);  //  2547
//	}
}

/* <4cb855> ../game_shared/bot/nav_area.cpp:2585 */
NOBODY void CNavArea::DrawMarkedCorner(NavCornerType corner, byte red, byte green, byte blue, int duration)
{
//	{
//		Vector nw;                                      //  2587
//		Vector ne;                                      //  2587
//		Vector sw;                                      //  2587
//		Vector se;                                      //  2587
//		float border;                                         //  2603
//		Vector(Vector *const this,
//			const Vector &v);  //  2625
//		operator+(const Vector *const this,
//				const Vector &v);  //  2625
//		Vector(Vector *const this,
//			const Vector &v);  //  2622
//		operator+(const Vector *const this,
//				const Vector &v);  //  2622
//		Vector(Vector *const this,
//			const Vector &v);  //  2619
//		operator+(const Vector *const this,
//				const Vector &v);  //  2619
//		Vector(Vector *const this,
//			const Vector &v);  //  2616
//		operator+(const Vector *const this,
//				const Vector &v);  //  2616
//	}
}

/* <4cbb32> ../game_shared/bot/nav_area.cpp:2634 */
NOBODY void CNavArea::AddToOpenList(void)
{
//	{
//		class CNavArea *area;                                //  2649
//		class CNavArea *last;                                //  2649
//	}
}

/* <4cbd73> ../game_shared/bot/nav_area.cpp:2685 */
NOBODY void CNavArea::UpdateOnOpenList(void)
{
//	{
//		class CNavArea *other;                               //  2692
//		class CNavArea *before;                              //  2693
//		class CNavArea *after;                               //  2694
//	}
}

/* <4cbdbc> ../game_shared/bot/nav_area.cpp:2713 */
NOBODY void CNavArea::RemoveFromOpenList(void)
{
	if (m_prevOpen)
		m_prevOpen->m_nextOpen = m_nextOpen;
	else
		IMPLEMENT_ARRAY(m_openList) = m_nextOpen;

	if (m_nextOpen)
		m_nextOpen->m_prevOpen = m_prevOpen;

	// zero is an invalid marker
	m_openMarker = 0;
}

/* <4cbddf> ../game_shared/bot/nav_area.cpp:2731 */
NOBODY void CNavArea::ClearSearchLists(void)
{
	CNavArea::MakeNewMarker();
	IMPLEMENT_ARRAY(m_openList) = NULL;
}

/* <4cbe06> ../game_shared/bot/nav_area.cpp:2744 */
NOBODY const Vector *CNavArea::GetCorner(NavCornerType corner) const
{
//	{
//		Vector pos;                                     //  2746
//	}
//	GetCorner(const class CNavArea *const this,
//			enum NavCornerType corner);  //  2744
}

/* <4cbe86> ../game_shared/bot/nav_area.cpp:2776 */
NOBODY bool CNavArea::IsHidingSpotCollision(const Vector *pos) const
{
//	{
//		float const collisionRange;                            //  2778
//		{
//			const_iterator iter;                          //  2780
//			end(const class list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //  2780
//			{
//				const class HidingSpot *spot;       //  2782
//				operator-(const Vector *const this,
//						const Vector &v);  //  2784
//				IsLengthLessThan(const Vector *const this,
//						float length);  //  2784
//			}
//			operator++(_List_const_iterator<HidingSpot*> *const this);  //  2780
//		}
//	}
}

/* <4c3aa2> ../game_shared/bot/nav_area.cpp:2792 */
NOBODY bool IsHidingSpotInCover(const Vector *spot)
{
//	{
//		int coverCount;                                       //  2794
//		TraceResult result;                                   //  2795
//		Vector from;                                    //  2797
//		Vector to;                                      //  2800
//		float const coverRange;                                //  2808
//		float const inc;                                       //  2809
//		int const halfCover;                                   //  2823
//		{
//			float angle;                                  //  2811
//		}
//	}
}

/* <4cc054> ../game_shared/bot/nav_area.cpp:2834 */
NOBODY void CNavArea::ComputeHidingSpots(void)
{
//	{
//		class  extent;                                        //  2840
//		int cornerCount;                                      //  2846
//		float const cornerSize;                                //  2850
//		float offset;                                         //  2928
//		{
//			int d;                                        //  2853
//			{
//				bool isHoriz;                         //  2858
//				{
//					iterator iter;                //  2860
//					{
//						union NavConnect connect;   //  2862
//						IsConnected(const class CNavArea *const this,
//								const class CNavArea *area,
//								enum NavDirType dir);  //  2866
//					}
//					operator++(_List_iterator<NavConnect> *const this);  //  2860
//				}
//			}
//		}
//		{
//			Vector pos;                             //  2932
//			GetCorner(const class CNavArea *const this,
//					enum NavCornerType corner);  //  2932
//			operator+(const Vector *const this,
//					const Vector &v);  //  2932
//			HidingSpot(HidingSpot *const this,
//					const Vector *pos,
//					unsigned char flags);  //  2934
//			push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//					const value_type &__x);  //  2934
//		}
//		{
//			Vector pos;                             //  2939
//			GetCorner(const class CNavArea *const this,
//					enum NavCornerType corner);  //  2939
//			operator+(const Vector *const this,
//					const Vector &v);  //  2939
//			push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//					const value_type &__x);  //  2941
//		}
//		{
//			Vector pos;                             //  2946
//			GetCorner(const class CNavArea *const this,
//					enum NavCornerType corner);  //  2946
//			operator+(const Vector *const this,
//					const Vector &v);  //  2946
//			push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//					const value_type &__x);  //  2948
//		}
//		{
//			Vector pos;                             //  2953
//			GetCorner(const class CNavArea *const this,
//					enum NavCornerType corner);  //  2953
//			operator+(const Vector *const this,
//					const Vector &v);  //  2953
//			IsHidingSpotCollision(const class CNavArea *const this,
//						const Vector *pos);  //  2954
//			HidingSpot(HidingSpot *const this,
//					const Vector *pos,
//					unsigned char flags);  //  2955
//			push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//					const value_type &__x);  //  2955
//		}
//	}
}

/* <4cccaf> ../game_shared/bot/nav_area.cpp:2963 */
NOBODY void ClassifySniperSpot(HidingSpot *spot)
{
//	{
//		Vector eye;                                     //  2965
//		Vector walkable;                                //  2966
//		TraceResult result;                                   //  2967
//		class Extent sniperExtent;                            //  2969
//		float farthestRangeSq;                                //  2970
//		float const minSniperRangeSq;                          //  2971
//		bool found;                                           //  2972
//		operator+(const Vector *const this,
//				const Vector &v);  //  2965
//		{
//			iterator iter;                                //  2974
//			{
//				class CNavArea *area;                //  2976
//				const class Extent *extent;         //  2978
//				{
//					float rangeSq;                //  2995
//					operator-(const Vector *const this,
//							const Vector &v);  //  2995
//					LengthSquared(const Vector *const this);  //  2995
//				}
//			}
//			operator++(_List_iterator<CNavArea*> *const this);  //  2974
//		}
//		{
//			float snipableArea;                           //  3032
//			float const minIdealSniperArea;                //  3034
//			float const longSniperRangeSq;                 //  3035
//			Area(const class Extent *const this);  //  3032
//			SetFlags(HidingSpot *const this,
//				unsigned char flags);  //  3038
//			SetFlags(HidingSpot *const this,
//				unsigned char flags);  //  3040
//		}
//	}
}

/* <4ccf19> ../game_shared/bot/nav_area.cpp:3049 */
NOBODY void CNavArea::ComputeSniperSpots(void)
{
//	{
//		iterator iter;                                        //  3054
//		end(list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //  3054
//		{
//			class HidingSpot *spot;                      //  3056
//		}
//		operator++(_List_iterator<HidingSpot*> *const this);  //  3054
//	}
}

/* <4ccfbd> ../game_shared/bot/nav_area.cpp:3066 */
NOBODY SpotEncounter *CNavArea::GetSpotEncounter(const CNavArea *from, const CNavArea *to)
{
//	{
//		class SpotEncounter *e;                              //  3070
//		{
//			iterator iter;                                //  3072
//			end(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //  3072
//			operator++(_List_iterator<SpotEncounter> *const this);  //  3072
//		}
//	}
}

/* <4cd0a5> ../game_shared/bot/nav_area.cpp:3088 */
NOBODY void CNavArea::AddSpotEncounters(const class CNavArea *from, NavDirType fromDir, const CNavArea *to, NavDirType toDir)
{
//	{
//		class SpotEncounter e;                                //  3090
//		float halfWidth;                                      //  3098
//		float const eyeHeight;                                 //  3102
//		Vector dir;                                     //  3107
//		float length;                                         //  3108
//		float const stepSize;                                  //  3113
//		float const seeSpotRange;                              //  3114
//		TraceResult result;                                   //  3115
//		Vector eye;                                     //  3117
//		Vector delta;                                   //  3117
//		class HidingSpot *spot;                              //  3118
//		class SpotOrder spotOrder;                            //  3119
//		bool done;                                            //  3122
//		SpotEncounter(SpotEncounter *const this);  //  3090
//		operator-(const Vector *const this,
//				const Vector &v);  //  3107
//		NormalizeInPlace(Vector *const this);  //  3108
//		ChangeMasterMarker(void);  //  3111
//		{
//			float along;                                  //  3123
//			{
//				iterator iter;                        //  3136
//				{
//					const Vector *spotPos;//  3147
//					float dot;                    //  3164
//					IsLengthGreaterThan(const Vector *const this,
//								float length);  //  3154
//					Vector(Vector *const this,
//						float X,
//						float Y,
//						float Z);  //  3158
//					NormalizeInPlace(Vector *const this);  //  3163
//					DotProduct(Vector &a,
//							const Vector &b);  //  3164
//					Mark(HidingSpot *const this);  //  3179
//					push_back(list<SpotOrder, std::allocator<SpotOrder>> *const this,
//							const value_type &__x);  //  3174
//				}
//				operator++(_List_iterator<HidingSpot*> *const this);  //  3136
//			}
//			operator*(float fl,
//					const Vector &v);  //  3133
//			operator+(const Vector *const this,
//					const Vector &v);  //  3133
//		}
//		push_back(list<SpotEncounter, std::allocator<SpotEncounter>> *const this,
//				const value_type &__x);  //  3184
//		~SpotEncounter(SpotEncounter *const this,
//				int const __in_chrg);  //  3090
//	}
}

/* <4cd99c> ../game_shared/bot/nav_area.cpp:3192 */
NOBODY void CNavArea::ComputeSpotEncounters(void)
{
//	clear(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //  3194
//	{
//		int fromDir;                                          //  3200
//		{
//			iterator fromIter;                            //  3202
//			{
//				union NavConnect *fromCon;           //  3204
//				{
//					int toDir;                    //  3207
//					{
//						iterator toIter;      //  3209
//						{
//							union NavConnect *toCon;           //  3211
//						}
//						operator++(_List_iterator<NavConnect> *const this);  //  3209
//					}
//				}
//			}
//			operator++(_List_iterator<NavConnect> *const this);  //  3202
//		}
//	}
}

/* <4cdca9> ../game_shared/bot/nav_area.cpp:3228 */
NOBODY void CNavArea::DecayDanger(void)
{
//	{
//		float const decayRate;                                 //  3231
//		{
//			int i;                                        //  3233
//			{
//				float deltaT;                         //  3235
//				float decayAmount;                    //  3236
//			}
//		}
//	}
}

/* <4cdd46> ../game_shared/bot/nav_area.cpp:3251 */
NOBODY void CNavArea::IncreaseDanger(int teamID, float amount)
{
//	DecayDanger(CNavArea *const this);  //  3254
}

/* <4cddc7> ../game_shared/bot/nav_area.cpp:3264 */
NOBODY float CNavArea::GetDanger(int teamID)
{
//	DecayDanger(CNavArea *const this);  //  3266
}

/* <4cde4b> ../game_shared/bot/nav_area.cpp:3274 */
NOBODY void IncreaseDangerNearby(int teamID, float amount, class CNavArea *startArea, const Vector *pos, float maxRadius)
{
//	MakeNewMarker(void);  //  3279
//	ClearSearchLists(void);  //  3280
//	AddToOpenList(CNavArea *const this);  //  3282
//	SetTotalCost(CNavArea *const this,
//			float value);  //  3283
//	IncreaseDanger(CNavArea *const this,
//			int teamID,
//			float amount);  //  3285
//	Mark(CNavArea *const this);  //  3284
//	{
//		class CNavArea *area;                                //  3290
//		PopOpenList(void);  //  3290
//		{
//			int dir;                                      //  3293
//			{
//				int count;                            //  3295
//				GetAdjacentCount(const class CNavArea *const this,
//						enum NavDirType dir);  //  3295
//				{
//					int i;                        //  3296
//					{
//						class CNavArea *adjArea;   //  3298
//						GetAdjacentArea(const class CNavArea *const this,
//								enum NavDirType dir,
//								int i);  //  3298
//						{
//							float cost;   //  3303
//							operator-(const Vector *const this,
//									const Vector &v);  //  3303
//							Length(const Vector *const this);  //  3303
//							AddToOpenList(CNavArea *const this);  //  3306
//							SetTotalCost(CNavArea *const this,
//									float value);  //  3307
//							Mark(CNavArea *const this);  //  3308
//							IncreaseDanger(CNavArea *const this,
//									int teamID,
//									float amount);  //  3309
//						}
//					}
//				}
//			}
//		}
//	}
}

/* <4ce2c4> ../game_shared/bot/nav_area.cpp:3321 */
NOBODY void DrawDanger(void)
{
//	{
//		iterator iter;                                        //  3323
//		{
//			class CNavArea *area;                        //  3325
//			Vector center;                          //  3327
//			Vector top;                             //  3328
//			float danger;                                 //  3331
//			GetDanger(CNavArea *const this,
//					int teamID);  //  3331
//			GetDanger(CNavArea *const this,
//					int teamID);  //  3340
//			Vector(Vector *const this,
//				const Vector &v);  //  3346
//			Vector(Vector *const this,
//				const Vector &v);  //  3346
//			Vector(Vector *const this,
//				const Vector &v);  //  3327
//			Vector(Vector *const this,
//				const Vector &v);  //  3337
//			Vector(Vector *const this,
//				const Vector &v);  //  3337
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //  3323
//	}
}

/* <4ce523> ../game_shared/bot/nav_area.cpp:3356 */
NOBODY bool IsSpotOccupied(CBaseEntity *me, const Vector *pos)
{
//	{
//		float const closeRange;                                //  3358
//		float range;                                          //  3361
//		class CBasePlayer *player;                           //  3362
//		{
//			class CHostage *hostage;                     //  3373
//			GetClosestHostage(CHostageManager *const this,
//						const Vector &pos,
//						float *resultRange);  //  3373
//		}
//	}
}

/* <4c118b> ../game_shared/bot/nav_area.cpp:3385 */
class CollectHidingSpotsFunctor
{
public:
	CollectHidingSpotsFunctor(CBaseEntity *me, const Vector *origin, float range, unsigned char flags, Place place = UNDEFINED_PLACE, bool useCrouchAreas = true)
	{
		m_me = me;
		m_count = 0;
		m_origin = origin;
		m_range = range;
		m_flags = flags;
		m_place = place;
		m_useCrouchAreas = useCrouchAreas;
	}
	enum { MAX_SPOTS = 256 };

	bool operator()(CNavArea *area)
	{
		if (m_place != UNDEFINED_PLACE && area->GetPlace() != m_place)
			return true;

		const HidingSpotList *list = area->GetHidingSpotList();
		for (HidingSpotList::const_iterator iter = list->begin(); iter != list->end() && m_count < MAX_SPOTS; ++iter)
		{
			const HidingSpot *spot = *iter;
			if (m_useCrouchAreas == false)
			{
				CNavArea *area = TheNavAreaGrid.GetNavArea(spot->GetPosition());
				if (area && (area->GetAttributes() & NAV_CROUCH))
					continue;
			}
			if (m_range > 0.0f)
			{
				if ((*spot->GetPosition() - *m_origin).IsLengthGreaterThan(m_range))
					continue;
			}
			if (IsSpotOccupied(m_me, spot->GetPosition()))
			{
				continue;
			}
			if (m_flags & spot->GetFlags())
			{
				m_hidingSpot[m_count++] = spot->GetPosition();
			}
		}
		if (m_count == MAX_SPOTS)
			return false;

		return true;
	}
	void RemoveSpot(int i)
	{
		if (m_count == 0)
			return;

		for (int j = i + 1; j < m_count; ++j)
			m_hidingSpot[j-1] = m_hidingSpot[j];

		--m_count;
	}

	CBaseEntity *m_me;
	const Vector *m_origin;
	float m_range;

	const Vector *m_hidingSpot[MAX_SPOTS];
	int m_count;

	unsigned char m_flags;
	Place m_place;
	bool m_useCrouchAreas;
};

/* <4d1806> ../game_shared/bot/nav_area.cpp:3477 */
NOBODY const Vector *FindNearbyHidingSpot(CBaseEntity *me, const Vector *pos, class CNavArea *startArea, float maxRange, bool isSniper, bool useNearest)
{
//	{
//		class CollectHidingSpotsFunctor collector;            //  3510
//		int which;                                            //  3535
//		{
//			class CollectHidingSpotsFunctor collector;    //  3485
//			CollectHidingSpotsFunctor(CollectHidingSpotsFunctor *const this,
//							class CBaseEntity *me,
//							const Vector *origin,
//							float range,
//							unsigned char flags,
//							Place place,
//							bool useCrouchAreas);  //  3485
//			SearchSurroundingAreas<CollectHidingSpotsFunctor>(CNavArea *startArea,
//										const Vector *startPos,
//										class CollectHidingSpotsFunctor &func,
//										float maxRange);  //  3486
//			{
//				int which;                            //  3490
//			}
//			{
//				class CollectHidingSpotsFunctor collector;    //  3496
//				CollectHidingSpotsFunctor(CollectHidingSpotsFunctor *const this,
//								class CBaseEntity *me,
//								const Vector *origin,
//								float range,
//								unsigned char flags,
//								Place place,
//								bool useCrouchAreas);  //  3496
//				{
//					int which;                    //  3501
//				}
//			}
//		}
//		CollectHidingSpotsFunctor(CollectHidingSpotsFunctor *const this,
//						class CBaseEntity *me,
//						const Vector *origin,
//						float range,
//						unsigned char flags,
//						Place place,
//						bool useCrouchAreas);  //  3510
//		SearchSurroundingAreas<CollectHidingSpotsFunctor>(CNavArea *startArea,
//									const Vector *startPos,
//									class CollectHidingSpotsFunctor &func,
//									float maxRange);  //  3511
//		{
//			const Vector *closest;                //  3519
//			float closeRangeSq;                           //  3520
//			{
//				int i;                                //  3521
//				{
//					float rangeSq;                //  3523
//					operator-(const Vector *const this,
//							const Vector &v);  //  3523
//					LengthSquared(const Vector *const this);  //  3523
//				}
//			}
//		}
//	}
}

/* <4c3feb> ../game_shared/bot/nav_area.cpp:3591 */
NOBODY bool IsCrossingLineOfFire(const Vector &start, const Vector &finish, CBaseEntity *ignore, int ignoreTeam)
{
	for (int p = 1; p <= gpGlobals->maxClients; ++p)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(p));

		if (!IsEntityValid(player))
			continue;

		if (player == ignore)
			continue;

		if (!player->IsAlive())
			continue;

		if (ignoreTeam && player->m_iTeam == ignoreTeam)
			continue;

		UTIL_MakeVectors(player->pev->v_angle + player->pev->punchangle);

		const float longRange = 5000.0f;
		Vector playerTarget = player->pev->origin + longRange * gpGlobals->v_forward;

		Vector result;
		if (IsIntersecting2D(start, finish, player->pev->origin, playerTarget, &result))
		{
			float loZ, hiZ;
			if (start.z < finish.z)
			{
				loZ = start.z;
				hiZ = finish.z;
			}
			else
			{
				loZ = finish.z;
				hiZ = start.z;
			}

			if (result.z >= loZ && result.z <= hiZ + HumanHeight)
				return true;
		}
	}

	return false;
}

/* <4d031a> ../game_shared/bot/nav_area.cpp:3544 */
NOBODY const Vector *FindRandomHidingSpot(CBaseEntity *me, Place place, bool isSniper)
{
//	{
//		class CollectHidingSpotsFunctor collector;            //  3574
//		int which;                                            //  3581
//		{
//			class CollectHidingSpotsFunctor collector;    //  3549
//			CollectHidingSpotsFunctor(CollectHidingSpotsFunctor *const this,
//							class CBaseEntity *me,
//							const Vector *origin,
//							float range,
//							unsigned char flags,
//							Place place,
//							bool useCrouchAreas);  //  3549
//			{
//				class CollectHidingSpotsFunctor collector;    //  3560
//				CollectHidingSpotsFunctor(CollectHidingSpotsFunctor *const this,
//								class CBaseEntity *me,
//								const Vector *origin,
//								float range,
//								unsigned char flags,
//								Place place,
//								bool useCrouchAreas);  //  3560
//				{
//					int which;                    //  3565
//				}
//			}
//			{
//				int which;                            //  3554
//			}
//		}
//		CollectHidingSpotsFunctor(CollectHidingSpotsFunctor *const this,
//						class CBaseEntity *me,
//						const Vector *origin,
//						float range,
//						unsigned char flags,
//						Place place,
//						bool useCrouchAreas);  //  3574
//	}
}

const Vector *FindNearbyRetreatSpot(CBaseEntity *me, const Vector *start, CNavArea *startArea, float maxRange, int avoidTeam, bool useCrouchAreas)
{
	if (startArea == NULL)
		return NULL;

	CollectHidingSpotsFunctor collector(me, start, maxRange, HidingSpot::IN_COVER, UNDEFINED_PLACE, useCrouchAreas);
	SearchSurroundingAreas(startArea, start, collector, maxRange);

	if (collector.m_count == 0)
		return NULL;

	for (int i = 0; i < collector.m_count; ++i)
	{
		if (IsCrossingLineOfFire(*start, *collector.m_hidingSpot[i], me))
		{
			collector.RemoveSpot(i);
			--i;
			continue;
		}
		if (avoidTeam)
		{
			float range;
			if (UTIL_GetClosestPlayer(collector.m_hidingSpot[i], avoidTeam, &range))
			{
				const float dangerRange = 150.0f;
				if (range < dangerRange)
				{
					collector.RemoveSpot(i);
					--i;
					continue;
				}
			}
		}
	}

	if (collector.m_count <= 0)
		return NULL;

	int which = RANDOM_LONG(0, collector.m_count - 1);
	return collector.m_hidingSpot[which];
}

/* <4ce934> ../game_shared/bot/nav_area.cpp:3707 */
NOBODY int CNavArea::GetPlayerCount(int teamID, CBasePlayer *ignore) const
{
//	{
//		int count;                                            //  3709
//		{
//			int i;                                        //  3711
//			{
//				class CBasePlayer *player;           //  3713
//				IsEntityValid(CBaseEntity *entity);  //  3718
//			}
//		}
//	}
}

/* <4cea33> ../game_shared/bot/nav_area.cpp:3749 */
CNavArea *GetMarkedArea(void)
{
	return markedArea;
}

/* <4c2a8c> ../game_shared/bot/nav_area.cpp:3757 */
void EditNavAreasReset(void)
{
	markedArea = NULL;
	lastSelectedArea = NULL;
	isCreatingNavArea = false;
	isPlacePainting = false;

	editTimestamp = 0.0f;
	lastDrawTimestamp = 0.0f;
}

/* <4cea61> ../game_shared/bot/nav_area.cpp:3767 */
NOBODY void DrawHidingSpots(const class CNavArea *area)
{
//	{
//		const HidingSpotList *list;                         //  3769
//		{
//			const_iterator iter;                          //  3770
//			{
//				const class HidingSpot *spot;       //  3772
//				int r;                                //  3774
//				int g;                                //  3774
//				int b;                                //  3774
//				HasGoodCover(const class HidingSpot *const this);  //  3784
//				operator+(const Vector *const this,
//						const Vector &v);  //  3793
//				Vector(Vector *const this,
//					const Vector &v);  //  3793
//				IsIdealSniperSpot(const class HidingSpot *const this);  //  3776
//			}
//			end(const class list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //  3770
//			operator++(_List_const_iterator<HidingSpot*> *const this);  //  3770
//		}
//	}
}

/* <4cebe7> ../game_shared/bot/nav_area.cpp:3802 */
NOBODY void CNavArea::DrawConnectedAreas(void)
{
//	{
//		class CBasePlayer *player;                           //  3804
//		class CCSBotManager *ctrl;                           //  3808
//		float const maxRange;                                  //  3809
//		int dirSet;                                           //  3829
//		int i;                                                //  3830
//		{
//			int swapCount;                                //  3835
//			{
//				int swapI;                            //  3837
//				int nextI;                            //  3838
//				int tmp;                              //  3842
//			}
//		}
//		{
//			enum NavDirType dir;                          //  3850
//			int count;                                    //  3852
//			GetAdjacentCount(const class CNavArea *const this,
//					enum NavDirType dir);  //  3852
//			{
//				int a;                                //  3854
//				{
//					class CNavArea *adj;         //  3856
//					GetAdjacentArea(const class CNavArea *const this,
//							enum NavDirType dir,
//							int i);  //  3856
//					{
//						Vector from;    //  3892
//						Vector to;      //  3892
//						Vector hookPos; //  3893
//						float halfWidth;      //  3894
//						float size;           //  3895
//						Vector drawTo;  //  3921
//						IsDegenerate(const class CNavArea *const this);  //  3869
//						{
//							class IntervalTimer blink;            //  3871
//							bool blinkOn; //  3872
//							GetElapsedTime(const class IntervalTimer *const this);  //  3874
//							Reset(IntervalTimer *const this);  //  3876
//							IntervalTimer(IntervalTimer *const this);  //  3871
//						}
//						operator+(const Vector *const this,
//								const Vector &v);  //  3913
//						operator+(const Vector *const this,
//								const Vector &v);  //  3914
//						OppositeDirection(NavDirType dir);  //  3924
//						IsConnected(const class CNavArea *const this,
//								const class CNavArea *area,
//								enum NavDirType dir);  //  3924
//						Vector(Vector *const this,
//							const Vector &v);  //  3925
//						Vector(Vector *const this,
//							const Vector &v);  //  3925
//						Vector(Vector *const this,
//							const Vector &v);  //  3927
//						Vector(Vector *const this,
//							const Vector &v);  //  3927
//						operator+(const Vector *const this,
//								const Vector &v);  //  3909
//						operator+(const Vector *const this,
//								const Vector &v);  //  3910
//						operator+(const Vector *const this,
//								const Vector &v);  //  3905
//						operator+(const Vector *const this,
//								const Vector &v);  //  3906
//						operator+(const Vector *const this,
//								const Vector &v);  //  3901
//						operator+(const Vector *const this,
//								const Vector &v);  //  3902
//					}
//				}
//			}
//		}
//	}
}

/* <4cf2ee> ../game_shared/bot/nav_area.cpp:3937 */
NOBODY void CNavArea::RaiseCorner(NavCornerType corner, int amount)
{
}

/* <4c3570> ../game_shared/bot/nav_area.cpp:3976 */
class PlaceFloodFillFunctor
{
public:
	PlaceFloodFillFunctor(CNavArea *area)
	{
		m_initialPlace = area->GetPlace();
	}
	bool operator()(CNavArea *area)
	{
		CCSBotManager *ctrl = static_cast<CCSBotManager *>(TheBots);

		if (area->GetPlace() != m_initialPlace)
			return false;

		area->SetPlace(ctrl->GetNavPlace());

		return true;
	}

private:
	unsigned int m_initialPlace;

};/* size: 4, cachelines: 1, members: 1 */

/* <4d76ef> ../game_shared/bot/nav_area.cpp:4002 */
NOBODY void EditNavAreas(NavEditCmdType cmd)
{
//	{
//		class CCSBotManager *ctrl;                           //  4004
//		class CBasePlayer *player;                           //  4006
//		float drawTimestamp;                                  //  4011
//		float const maxDrawRate;                               //  4012
//		bool doDraw;                                          //  4014
//		float const maxRange;                                  //  4026
//		int beamTime;                                         //  4028
//		Vector dir;                                     //  4098
//		Vector from;                                    //  4101
//		Vector to;                                      //  4102
//		TraceResult result;                                   //  4104
//		{
//			iterator iter;                                //  4033
//			{
//				class CNavLadder *ladder;            //  4035
//				float dx;                             //  4037
//				float dy;                             //  4038
//				Vector bottom;                  //  4045
//				Vector top;                     //  4046
//				Vector(Vector *const this,
//					const Vector &v);  //  4043
//				Vector(Vector *const this,
//					const Vector &v);  //  4043
//				AddDirectionVector(Vector *v,
//							enum NavDirType dir,
//							float amount);  //  4048
//				Vector(Vector *const this,
//					const Vector &v);  //  4046
//				Vector(Vector *const this,
//					const Vector &v);  //  4045
//				AddDirectionVector(Vector *v,
//							enum NavDirType dir,
//							float amount);  //  4049
//				Vector(Vector *const this,
//					const Vector &v);  //  4051
//				Vector(Vector *const this,
//					const Vector &v);  //  4051
//				operator+(const Vector *const this,
//						const Vector &v);  //  4054
//				Vector(Vector *const this,
//					const Vector &v);  //  4054
//				Vector(Vector *const this,
//					const Vector &v);  //  4057
//				Vector(Vector *const this,
//					const Vector &v);  //  4057
//				Vector(Vector *const this,
//					const Vector &v);  //  4060
//				Vector(Vector *const this,
//					const Vector &v);  //  4060
//				Vector(Vector *const this,
//					const Vector &v);  //  4063
//				Vector(Vector *const this,
//					const Vector &v);  //  4063
//				Vector(Vector *const this,
//					const Vector &v);  //  4066
//				Vector(Vector *const this,
//					const Vector &v);  //  4066
//			}
//			operator++(_List_iterator<CNavLadder*> *const this);  //  4033
//		}
//		{
//			Vector ap;                              //  4072
//			float halfWidth;                              //  4073
//			{
//				int i;                                //  4074
//				{
//					const class ApproachInfo *info;   //  4076
//					operator+(const Vector *const this,
//							const Vector &v);  //  4090
//					operator+(const Vector *const this,
//							const Vector &v);  //  4090
//					operator+(const Vector *const this,
//							const Vector &v);  //  4091
//					operator+(const Vector *const this,
//							const Vector &v);  //  4091
//					operator+(const Vector *const this,
//							const Vector &v);  //  4092
//					operator+(const Vector *const this,
//							const Vector &v);  //  4092
//					operator+(const Vector *const this,
//							const Vector &v);  //  4093
//					operator+(const Vector *const this,
//							const Vector &v);  //  4093
//				}
//				GetApproachInfoCount(const class CNavArea *const this);  //  4074
//			}
//		}
//		UTIL_MakeVectorsPrivate(Vector &vecAngles,
//					float *p_vForward,
//					float *p_vRight,
//					float *p_vUp);  //  4099
//		operator+(const Vector *const this,
//				const Vector &v);  //  4101
//		operator*(float fl,
//				const Vector &v);  //  4102
//		operator+(const Vector *const this,
//				const Vector &v);  //  4102
//		{
//			Vector cursor;                          //  4110
//			float cursorSize;                             //  4111
//			class CNavArea *area;                        //  4147
//			Vector(Vector *const this,
//				const Vector &v);  //  4110
//			{
//				float z;                              //  4131
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4132
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4132
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4133
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4133
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4134
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4134
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4135
//				Vector(Vector *const this,
//					float X,
//					float Y,
//					float Z);  //  4135
//			}
//			{
//				char buffer;                          //  4156
//				char attrib;                          //  4157
//				char locName;                         //  4158
//				{
//					const char *name;           //  4162
//				}
//				SetPlace(CNavArea *const this,
//					Place place);  //  4195
//			}
//			{
//				const class Extent *extent;         //  4260
//				float yaw;                            //  4262
//				float splitEdge;                      //  4269
//				bool splitAlongX;                     //  4270
//				{
//					int corner;                   //  4506
//				}
//				{
//					class CBasePlayer *pLocalPlayer;   //  4440
//					{
//						Vector origin;  //  4443
//						operator+(const Vector *const this,
//								const Vector &v);  //  4443
//					}
//				}
//				{
//					iterator iter;                //  4397
//					operator++(_List_iterator<CNavArea*> *const this);  //  4397
//					{
//						class CNavArea *area;//  4399
//					}
//				}
//				{
//					int connected;                //  4414
//					int totalUnnamedAreas;        //  4420
//					char buffer;                  //  4430
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4415
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4416
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4417
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4418
//					{
//						iterator iter;        //  4421
//						{
//							class CNavArea *area;        //  4423
//						}
//						operator++(_List_iterator<CNavArea*> *const this);  //  4421
//					}
//				}
//				{
//					enum NavDirType dir;          //  4456
//				}
//				{
//					int connected;                //  4376
//					char buffer;                  //  4382
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4377
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4378
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4379
//					GetAdjacentCount(const class CNavArea *const this,
//							enum NavDirType dir);  //  4380
//				}
//				Vector(Vector *const this,
//					const Vector &v);  //  4302
//				Vector(Vector *const this,
//					const Vector &v);  //  4302
//			}
//			{
//				class PlaceFloodFillFunctor pff;      //  4237
//				SetNavPlace(CCSBotManager *const this,
//						unsigned int place);  //  4233
//				PlaceFloodFillFunctor(PlaceFloodFillFunctor *const this,
//							class CNavArea *area);  //  4237
//				SetPlace(CNavArea *const this,
//					Place place);  //  4226
//			}
//			{
//				class CNavArea *newArea;             //  4567
//				push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//						const value_type &__x);  //  4568
//				{
//					const class Extent *extent; //  4575
//				}
//			}
//			Vector(Vector *const this,
//				const Vector &v);  //  4115
//			operator+(const Vector *const this,
//					const Vector &v);  //  4115
//			operator+(const Vector *const this,
//					const Vector &v);  //  4116
//			operator+(const Vector *const this,
//					const Vector &v);  //  4116
//			operator+(const Vector *const this,
//					const Vector &v);  //  4117
//			operator+(const Vector *const this,
//					const Vector &v);  //  4117
//		}
//	}
}

/* <4c3b30> ../game_shared/bot/nav_area.cpp:4635 */
bool GetGroundHeight(const Vector *pos, float *height, Vector *normal)
{
	Vector to;
	to.x = pos->x;
	to.y = pos->y;
	to.z = pos->z - 9999.9f;

	float offset;
	Vector from;
	TraceResult result;
	edict_t *ignore = NULL;
	//float ground = 0.0f;	// unused?

	const float maxOffset = 100.0f;
	const float inc = 10.0f;

	#define MAX_GROUND_LAYERS 16

	struct GroundLayerInfo
	{
		float ground;
		Vector normal;

	} layer[MAX_GROUND_LAYERS];

	int layerCount = 0;
	for (offset = 1.0f; offset < maxOffset; offset += inc)
	{
		from = *pos + Vector(0, 0, offset);

		UTIL_TraceLine(from, to, ignore_monsters, dont_ignore_glass, ignore, &result);

		if (result.pHit)
		{
			if (FClassnameIs(VARS(result.pHit), "func_door") || FClassnameIs(VARS(result.pHit), "func_door_rotating") || (FClassnameIs(VARS(result.pHit), "func_breakable") && VARS(result.pHit)->takedamage == DAMAGE_YES))
			{
				ignore = result.pHit;
				continue;
			}
		}

		if (!result.fStartSolid)
		{
			if (layerCount == 0 || result.vecEndPos.z > layer[layerCount - 1].ground)
			{
				layer[layerCount].ground = result.vecEndPos.z;
				layer[layerCount].normal = result.vecPlaneNormal;
				++layerCount;

				if (layerCount == MAX_GROUND_LAYERS)
					break;
			}
		}
	}

	if (layerCount == 0)
		return false;

	int i;
	for (i = 0; i < layerCount - 1; ++i)
	{
		if (layer[i + 1].ground - layer[i].ground >= HalfHumanHeight)
			break;
	}

	*height = layer[i].ground;

	if (normal)
	{
		*normal = layer[i].normal;
	}

	return true;
}

/* <4cf4d2> ../game_shared/bot/nav_area.cpp:4724 */
NOBODY bool GetSimpleGroundHeight(const Vector *pos, float *height, Vector *normal)
{
//	{
//		Vector to;                                      //  4726
//		TraceResult result;                                   //  4731
//	}
}

/* <4c0912> ../game_shared/bot/nav_area.cpp:4757 */
class ApproachAreaCost
{
public:
	float operator()(CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		for (int i = 0; i < BlockedIDCount; ++i)
		{
			if (area->GetID() == BlockedID[i])
				return -1.0f;
		}
		if (fromArea == NULL)
			return 0.0f;
		else
		{
			float dist;
			if (ladder)
				dist = ladder->m_length;
			else
				dist = (*area->GetCenter() - *fromArea->GetCenter()).Length();

			float cost = dist + fromArea->GetCostSoFar();
			return cost;
		}
	}
};

/* <4c4182> ../game_shared/bot/nav_area.cpp:4791 */
NOBODY inline bool IsAreaVisible(const Vector *pos, const CNavArea *area)
{
//	{
//		Vector corner;                                  //  4793
//		TraceResult result;                                   //  4794
//		{
//			int c;                                        //  4796
//		}
//	}
}

/* <4cf54c> ../game_shared/bot/nav_area.cpp:4817 */
NOBODY void CNavArea::ComputeApproachAreas(void)
{
//	{
//		Vector eye;                                     //  4825
//		class CNavArea *path;                                //  4836
//		iterator iter;                                        //  4843
//		Vector(Vector *const this,
//			const Vector &v);  //  4825
//		{
//			class CNavArea *farArea;                     //  4846
//			class ApproachAreaCost cost;                  //  4855
//			IsAreaVisible(const Vector *pos,
//					const class CNavArea *area);  //  4851
//			{
//				int count;                            //  4867
//				class CNavArea *area;                //  4868
//				int i;                                //  4876
//				class ApproachAreaCost cost;          //  4928
//				{
//					int block;                    //  4897
//					int a;                        //  4905
//					IsAreaVisible(const Vector *pos,
//							const class CNavArea *area);  //  4884
//				}
//			}
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //  4844
//	}
}

/* <4cf961> ../game_shared/bot/nav_area.cpp:4947 */
NOBODY CNavAreaGrid::CNavAreaGrid(void) : m_cellSize(300.0f)
{
	m_grid = NULL;
	Reset();
}

/* <4c4a70> ../game_shared/bot/nav_area.cpp:4953 */
NOBODY CNavAreaGrid::~CNavAreaGrid(void)
{
//	~list(list<CNavArea*, std::allocator<CNavArea*>>::~CNavAreaGrid(//		int const __in_chrg);  //  4955
}

/* <4cf837> ../game_shared/bot/nav_area.cpp:4962 */
void CNavAreaGrid::Reset(void)
{
	if (m_grid)
	{
		// TODO: FIX ME
		//delete[] m_grid;
	}

	m_grid = NULL;
	m_gridSizeX = 0;
	m_gridSizeY = 0;

	// clear the hash table
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
		m_hashTable[i] = NULL;

	m_areaCount = 0;

	// reset static vars
	EditNavAreasReset();
}

/* <4cf984> ../game_shared/bot/nav_area.cpp:4983 */
NOBODY void CNavAreaGrid::Initialize(float minX, float maxX, float minY, float maxY)
{
//	list(list<CNavArea*, std::allocator<CNavArea*>> *const this);  //  4994
}

/* <4cfa20> ../game_shared/bot/nav_area.cpp:5000 */
NOBODY void CNavAreaGrid::AddNavArea(CNavArea *area)
{
//	{
//		const class Extent *extent;                         //  5003
//		int loX;                                              //  5005
//		int loY;                                              //  5006
//		int hiX;                                              //  5007
//		int hiY;                                              //  5008
//		int key;                                              //  5015
//		WorldToGridX(const class CNavAreaGrid *const this,
//				float wx);  //  5005
//		WorldToGridY(const class CNavAreaGrid *const this,
//				float wy);  //  5006
//		WorldToGridX(const class CNavAreaGrid *const this,
//				float wx);  //  5007
//		WorldToGridY(const class CNavAreaGrid *const this,
//				float wy);  //  5008
//		{
//			int y;                                        //  5010
//			{
//				int x;                                //  5011
//				push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//						const value_type &__x);  //  5012
//			}
//		}
//		ComputeHashKey(const class CNavAreaGrid *const this,
//				unsigned int id);  //  5015
//	}
}

/* <4cfc86> ../game_shared/bot/nav_area.cpp:5039 */
NOBODY void CNavAreaGrid::RemoveNavArea(CNavArea *area)
{
	// add to grid
	const Extent *extent = area->GetExtent();

	int loX = WorldToGridX(extent->lo.x);
	int loY = WorldToGridY(extent->lo.y);
	int hiX = WorldToGridX(extent->hi.x);
	int hiY = WorldToGridY(extent->hi.y);

	for (int y = loY; y <= hiY; ++y)
	{
		for (int x = loX; x <= hiX; ++x)
		{
			m_grid[x + y * m_gridSizeX].remove(area);
		}
	}

	// remove from hash table
	int key = ComputeHashKey(area->GetID());

	if (area->m_prevHash)
	{
		area->m_prevHash->m_nextHash = area->m_nextHash;
	}
	else
	{
		// area was at start of list
		m_hashTable[key] = area->m_nextHash;

		if (m_hashTable[key])
			m_hashTable[key]->m_prevHash = NULL;
	}

	if (area->m_nextHash)
	{
		area->m_nextHash->m_prevHash = area->m_prevHash;
	}

	--m_areaCount;
}

CNavArea *(*pGetNavArea)(const Vector *pos, float beneathLimit);

/* <4cff5e> ../game_shared/bot/nav_area.cpp:5080 */
CNavArea __declspec(naked) *CNavAreaGrid::GetNavArea(const Vector *pos, float beneathLimit) const
{
	__asm
	{
		jmp pGetNavArea
	}

	UNTESTED
	//TODO: Crash NavAreaList::iterator iter = list->begin()
/*
	if (m_grid == NULL)
		return NULL;

	int x = WorldToGridX(pos->x);
	int y = WorldToGridY(pos->y);

	NavAreaList *list = &m_grid[x + y * m_gridSizeX];

	CNavArea *use = NULL;
	float useZ = -100000000.0f;
	Vector testPos = *pos + Vector(0, 0, 5);

	if (list == NULL)
		return NULL;

	for (NavAreaList::iterator iter = list->begin(); iter != list->end(); ++iter)
	{
		CNavArea *area = *iter;

		if (area->IsOverlapping(&testPos))
		{
			float z = area->GetZ(&testPos);
			if (z > testPos.z)
				continue;

			if (z < pos->z - beneathLimit)
				continue;

			if (z > useZ)
			{
				use = area;
				useZ = z;
			}
		}
	}
	return use;
*/
}

CNavArea *(*pGetNearestNavArea)(const Vector *pos, bool anyZ);

/* <4d33b4> ../game_shared/bot/nav_area.cpp:5133 */
NOBODY __declspec(naked) CNavArea *CNavAreaGrid::GetNearestNavArea(const Vector *pos, bool anyZ) const
{
	__asm
	{
		jmp pGetNearestNavArea
	}
	//TODO: UNTESTED
	// Result: Crashed TheNavAreaList.begin()

/*	if (m_grid == NULL)
		return NULL;

	CNavArea *close = NULL;
	float closeDistSq = 100000000.0f;

	close = GetNavArea(pos);
	if (close)
		return close;

	Vector source;
	source.x = pos->x;
	source.y = pos->y;

	if (GetGroundHeight(pos, &source.z) == false)
		return NULL;

	source.z += HalfHumanHeight;

	for (NavAreaList::iterator iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	{
		CNavArea *area = *iter;

		Vector areaPos;
		area->GetClosestPointOnArea(&source, &areaPos);

		float distSq = (areaPos - source).LengthSquared();
		if (distSq < closeDistSq)
		{
			if (!anyZ)
			{
				TraceResult result;
				UTIL_TraceLine(source, areaPos + Vector(0, 0, HalfHumanHeight), ignore_monsters, ignore_glass, NULL, &result);
				if (result.flFraction != 1.0f)
					continue;
			}
			closeDistSq = distSq;
			close = area;
		}
	}
	return close;
*/
}

/* <4d4778> ../game_shared/bot/nav_area.cpp:5191 */
NOBODY CNavArea *CNavAreaGrid::GetNavAreaByID(unsigned int id) const
{
//	{
//		int key;                                              //  5196
//		{
//			class CNavArea *area;                        //  5198
//		}
//		ComputeHashKey(const class CNavAreaGrid *const this,
//				unsigned int id);  //  5196
//	}
}

/* <4d4802> ../game_shared/bot/nav_area.cpp:5209 */
Place CNavAreaGrid::GetPlace(const Vector *pos) const
{
	CNavArea *area = GetNearestNavArea(pos, true);

	if (area)
	{
		return area->GetPlace();
	}

	return UNDEFINED_PLACE;
}
