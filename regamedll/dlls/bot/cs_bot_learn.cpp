#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

const float updateTimesliceDuration = 0.0f;

#else

const float updateTimesliceDuration = 0.0;//TODO: what value?? check it.

#endif // HOOK_GAMEDLL

int _navAreaCount;
int _currentIndex;

/* <343cbe> ../cstrike/dlls/bot/cs_bot_learn.cpp:95 */
NOBODY inline class CNavNode *LadderEndSearch(CBaseEntity *entity, const Vector *pos, NavDirType mountDir)
{
//	{
//		Vector center;                                  //    97
//		{
//			int d;                                        //   103
//			{
//				Vector tryPos;                  //   105
//				Vector tryNormal;               //   118
//				float const fudge;                     //   123
//				TraceResult result;                   //   124
//			}
//		}
//	}
}

/* <343a56> ../cstrike/dlls/bot/cs_bot_learn.cpp:30 */
NOBODY CNavNode *CCSBot::AddNode(const Vector *destPos, const Vector *normal, NavDirType dir, CNavNode *source)
{
//	{
//		class CNavNode *node;                                //    34
//		bool useNew;                                          //    37
//		float const zTolerance;                                //    48
//		TraceResult result;                                   //    63
//		Vector floor;                                   //    64
//		Vector ceiling;                                 //    64
//		bool crouch;                                          //    65
//		MarkAsVisited(CNavNode *const this,
//				enum NavDirType dir);  //    52
//		{
//			float y;                                      //    66
//			{
//				float x;                              //    68
//			}
//		}
//		SetAttributes(CNavNode *const this,
//				unsigned char bits);  //    89
//	}
}

/* <343b40> ../cstrike/dlls/bot/cs_bot_learn.cpp:150 */
NOXREF void drawProgressMeter(float progress, char *title)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
		WRITE_BYTE(FLAG_PROGRESS_DRAW);
		WRITE_BYTE((int)progress);
		WRITE_STRING(title);
	MESSAGE_END();
}

/* <3435ce> ../cstrike/dlls/bot/cs_bot_learn.cpp:159 */
NOXREF void startProgressMeter(const char *title)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
		WRITE_BYTE(FLAG_PROGRESS_START);
		WRITE_STRING(title);
	MESSAGE_END();
}

/* <3435a8> ../cstrike/dlls/bot/cs_bot_learn.cpp:167 */
NOXREF void hideProgressMeter(void)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgBotProgress);
		WRITE_BYTE(FLAG_PROGRESS_HIDE);
	MESSAGE_END();
}

/* <343b63> ../cstrike/dlls/bot/cs_bot_learn.cpp:182 */
NOBODY void CCSBot::StartLearnProcess(void)
{
//	{
//		Vector pos;                                     //   192
//		Vector normal;                                  //   195
//		startProgressMeter(const char *title);  //   184
//		drawProgressMeter(float progress,
//					char *title);  //   185
//		Vector(Vector *const this,
//			const Vector &v);  //   192
//		SnapToGrid(Vector *pos);  //   193
//		StartNormalProcess(CCSBot *const this);  //   199
//	}

	Vector pos;
	Vector normal;

	startProgressMeter("#CZero_LearningMap");
	drawProgressMeter(0, "#CZero_LearningMap");


}

/* <343d37> ../cstrike/dlls/bot/cs_bot_learn.cpp:217 */
NOBODY bool CCSBot::LearnStep(void)
{
//	{
//		int dir;                                              //   249
//		{
//			float feetOffset;                             //   256
//			Vector pos;                             //   259
//			int cx;                                       //   262
//			int cy;                                       //   263
//			TraceResult result;                           //   283
//			Vector from;                            //   284
//			Vector to;                              //   284
//			Vector toNormal;                        //   289
//			Vector fromOrigin;                      //   298
//			Vector toOrigin;                        //   299
//			bool walkable;                                //   303
//			IsEntityWalkable(entvars_t *entity,
//					unsigned int flags);  //   362
//			{
//				float toGround;                       //   309
//				float fromGround;                     //   310
//				float epsilon;                        //   312
//				{
//					Vector delta;           //   322
//					float const inc;               //   323
//					float along;                  //   324
//					bool done;                    //   325
//					float ground;                 //   326
//					Vector normal;          //   327
//					operator-(const Vector *const this,
//							const Vector &v);  //   322
//					{
//						Vector p;       //   333
//						operator*(const Vector *const this,
//								float fl);  //   343
//						operator+(const Vector *const this,
//								const Vector &v);  //   343
//					}
//				}
//			}
//			VARS(edict_t *pent);  //   362
//			GetFeetZ(const class CCSBot *const this);  //   256
//			Vector(Vector *const this,
//				const Vector &v);  //   259
//			MarkAsVisited(CNavNode *const this,
//					enum NavDirType dir);  //   280
//			operator+(const Vector *const this,
//					const Vector &v);  //   294
//			operator+(const Vector *const this,
//					const Vector &v);  //   298
//			operator+(const Vector *const this,
//					const Vector &v);  //   299
//			{
//				class CNavNode *newNode;             //   376
//				AddNode(CCSBot *const this,
//					const Vector *destPos,
//					const Vector *normal,
//					enum NavDirType dir,
//					class CNavNode *source);  //   376
//			}
//		}
//		HasVisited(CNavNode *const this,
//				enum NavDirType dir);  //   251
//	}
//	{
//		iterator iter;                                        //   225
//		{
//			class CNavLadder *ladder;                    //   227
//			LadderEndSearch(CBaseEntity *entity,
//					const Vector *pos,
//					enum NavDirType mountDir);  //   230
//			LadderEndSearch(CBaseEntity *entity,
//					const Vector *pos,
//					enum NavDirType mountDir);  //   234
//		}
//		operator++(_List_iterator<CNavLadder*> *const this);  //   225
//	}
}

/* <34489e> ../cstrike/dlls/bot/cs_bot_learn.cpp:392 */
NOBODY void CCSBot::UpdateLearnProcess(void)
{
//	{
//		float startTime;                                      //   394
//	}
}

/* <344750> ../cstrike/dlls/bot/cs_bot_learn.cpp:409 */
void CCSBot::StartAnalyzeAlphaProcess(void)
{
	m_processMode = PROCESS_ANALYZE_ALPHA;
	m_analyzeIter = TheNavAreaList.begin();

	_navAreaCount = TheNavAreaList.size();
	_currentIndex = 0;

	ApproachAreaAnalysisPrep();
	DestroyHidingSpots();

	startProgressMeter("#CZero_AnalyzingHidingSpots");
	drawProgressMeter(0, "#CZero_AnalyzingHidingSpots");
}

/* <34396c> ../cstrike/dlls/bot/cs_bot_learn.cpp:427 */
NOBODY inline bool CCSBot::AnalyzeAlphaStep(void)
{
//	{
//		class CNavArea *area;                                //   432
//	}
}

/* <3448de> ../cstrike/dlls/bot/cs_bot_learn.cpp:443 */
NOBODY void CCSBot::UpdateAnalyzeAlphaProcess(void)
{
//	{
//		float startTime;                                      //   445
//		float progress;                                       //   462
//		AnalyzeAlphaStep(CCSBot *const this);  //   451
//		drawProgressMeter(float progress,
//					char *title);  //   454
//		StartAnalyzeBetaProcess(CCSBot *const this);  //   456
//		drawProgressMeter(float progress,
//					char *title);  //   463
//	}
}

/* <344aed> ../cstrike/dlls/bot/cs_bot_learn.cpp:467 */
NOBODY void CCSBot::StartAnalyzeBetaProcess(void)
{
//	size(const class list<CNavArea*, std::allocator<CNavArea*>> *const this);  //   471
}

/* <3437c8> ../cstrike/dlls/bot/cs_bot_learn.cpp:479 */
NOBODY inline bool CCSBot::AnalyzeBetaStep(void)
{
//	{
//		class CNavArea *area;                                //   484
//	}
}

/* <344b8d> ../cstrike/dlls/bot/cs_bot_learn.cpp:495 */
NOBODY void CCSBot::UpdateAnalyzeBetaProcess(void)
{
//	{
//		float startTime;                                      //   497
//		float progress;                                       //   512
//		AnalyzeBetaStep(CCSBot *const this);  //   503
//		drawProgressMeter(float progress,
//					char *title);  //   506
//		StartSaveProcess(CCSBot *const this);  //   507
//		drawProgressMeter(float progress,
//					char *title);  //   513
//	}
}

/* <344d1f> ../cstrike/dlls/bot/cs_bot_learn.cpp:517 */
NOBODY void CCSBot::StartSaveProcess(void)
{
}

/* <344d41> ../cstrike/dlls/bot/cs_bot_learn.cpp:527 */
NOBODY void CCSBot::UpdateSaveProcess(void)
{
//	{
//		char filename;                                        //   530
//		char msg;                                             //   538
//		char cmd;                                             //   548
//		hideProgressMeter(void);  //   542
//		StartNormalProcess(CCSBot *const this);  //   545
//	}
}

/* <344e24> ../cstrike/dlls/bot/cs_bot_learn.cpp:554 */
void CCSBot::StartNormalProcess(void)
{
	m_processMode = PROCESS_NORMAL;
}
