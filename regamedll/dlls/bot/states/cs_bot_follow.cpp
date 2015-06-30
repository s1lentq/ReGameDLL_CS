#include "precompiled.h"

/* <56918b> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:16 */
NOBODY void FollowState::OnEnter(CCSBot *me)
{
//	DestroyPath(CCSBot *const this);  //    20
//	Invalidate(CountdownTimer *const this);  //    33
//	Invalidate(IntervalTimer *const this);  //    37
//	Start(CountdownTimer *const this,
//		float duration);  //    41
}

/* <569268> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:48 */
NOBODY void FollowState::ComputeLeaderMotionState(float leaderSpeed)
{
//	{
//		float const runWalkThreshold;                          //    51
//		float const walkStopThreshold;                         //    52
//		enum LeaderMotionStateType prevState;                 //    53
//		{
//			float const minWalkTime;                       //    68
//			GetElapsedTime(const class IntervalTimer *const this);  //    69
//			Start(IntervalTimer *const this);  //    64
//		}
//		Start(IntervalTimer *const this);  //    83
//	}
}

/* <568fae> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:95 */
class FollowTargetCollector
{
public:
	FollowTargetCollector(CBasePlayer *player)
	{
		m_player = player;

		Vector playerVel = player->pev->velocity;

		m_forward.x = playerVel.x;
		m_forward.y = playerVel.y;

		float speed = m_forward.NormalizeInPlace();

		Vector playerOrigin = player->pev->origin;

		const float walkSpeed = 100.0f;
		if (speed < walkSpeed)
		{
			m_cutoff.x = playerOrigin.x;
			m_cutoff.y = playerOrigin.y;

			m_forward.x = 0.0f;
			m_forward.y = 0.0f;
		}
		else
		{
			const float k = 1.5f; // 2.0f;
			float trimSpeed = min(speed, 200.0f);

			m_cutoff.x = playerOrigin.x + k * trimSpeed * m_forward.x;
			m_cutoff.y = playerOrigin.y + k * trimSpeed * m_forward.y;
		}

		m_targetAreaCount = 0;
	}

	enum { MAX_TARGET_AREAS = 128 };

	/* <568dc3> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:124 */
	bool operator()(CNavArea *area)
	{
		if (m_targetAreaCount >= MAX_TARGET_AREAS)
			return false;
		
		// only use two-way connections
		if (!area->GetParent() || area->IsConnected(area->GetParent(), NUM_DIRECTIONS))
		{
			if (m_forward.IsZero())
			{
				m_targetArea[ m_targetAreaCount++ ] = area;
			}
			else
			{
				// collect areas in the direction of the player's forward motion
				Vector2D to(((*area->GetCenter()).x - m_cutoff.x), (*area->GetCenter()).y - m_cutoff.y);
				to.NormalizeInPlace();

				//if (DotProduct( to, m_forward ) > 0.7071f)
				if ((to.x * m_forward.x + to.y * m_forward.y) > 0.7071f)
					m_targetArea[ m_targetAreaCount++ ] = area;
			}
		}

		return (m_targetAreaCount < MAX_TARGET_AREAS);
	}

	CBasePlayer *m_player;
	Vector2D m_forward;
	Vector2D m_cutoff;
	CNavArea *m_targetArea[ MAX_TARGET_AREAS ];
	int m_targetAreaCount;

};/* size: 536, cachelines: 9, members: 5 */


/* <569368> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:164 */
NOBODY void FollowState::OnUpdate(CCSBot *me)
{
//	{
//		float leaderSpeed;                                    //   194
//		bool isLeaderVisible;                                 //   200
//		float const farAwayRange;                              //   213
//		float const longTime;                                  //   231
//		bool repath;                                          //   241
//		float const nearLeaderRange;                           //   244
//		SetTask(CCSBot *const this,
//			enum TaskType task,
//			class CBaseEntity *entity);  //   177
//		IsNotMoving(const class CCSBot *const this);  //   190
//		Length(const class Vector2D *const this);  //   194
//		operator-(const Vector *const this,
//				const Vector &v);  //   214
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //   214
//		GetElapsedTime(const class IntervalTimer *const this);  //   245
//		operator-(const Vector *const this,
//				const Vector &v);  //   251
//		IsLengthLessThan(const Vector *const this,
//				float length);  //   251
//		{
//			float const hideRange;                         //   253
//		}
//		IsElapsed(const class CountdownTimer *const this);  //   263
//		DestroyPath(CCSBot *const this);  //   280
//		IsElapsed(const class CountdownTimer *const this);  //   284
//		{
//			float const runSpeed;                          //   291
//			float const collectRange;                      //   293
//			class FollowTargetCollector collector;        //   294
//			FollowTargetCollector(FollowTargetCollector *const this,
//						class CBasePlayer *player);  //   294
//			SearchSurroundingAreas<FollowTargetCollector>(CNavArea *startArea,
//									const Vector *startPos,
//									class FollowTargetCollector &func,
//									float maxRange);  //   295
//			{
//				int i;                                //   299
//			}
//			{
//				class CNavArea *target;              //   306
//				Vector targetPos;               //   307
//				IsElapsed(const class CountdownTimer *const this);  //   310
//				{
//					class CNavArea *area;        //   321
//					float closeRangeSq;           //   322
//					Vector close;           //   323
//					{
//						int a;                //   325
//						{
//							float rangeSq;//   331
//							operator-(const Vector *const this,
//									const Vector &v);  //   331
//							LengthSquared(const Vector *const this);  //   331
//						}
//					}
//				}
//				Start(CountdownTimer *const this,
//					float duration);  //   345
//				Reset(CountdownTimer *const this);  //   347
//			}
//		}
//		Start(CountdownTimer *const this,
//			float duration);  //   191
//	}
}

/* <569231> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:353 */
NOBODY void FollowState::OnExit(CCSBot *me)
{
}
