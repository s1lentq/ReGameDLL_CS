#include "precompiled.h"

/* <4205b1> ../cstrike/dlls/hostage/states/hostage_escape.cpp:12 */
void HostageEscapeToCoverState::OnEnter(CHostageImprov *improv)
{
//	{
//		class CNavPath path;                                  //    18
//		class HostagePathCost pathCost;                       //    19
//		Invalidate(CNavPath *const this);  //    14
//		CNavPath(CNavPath *const this);  //    18
//		Compute<HostagePathCost>(CNavPath *const this,
//					const Vector *start,
//					const Vector *goal,
//					class HostagePathCost &costFunc);  //    20
//		{
//			float const moveRange;                         //    23
//			int idx;                                      //    24
//			{
//				Vector pathPos;                 //    32
//				float const hidingRange;               //    34
//				const Vector *spot;           //    35
//				operator[](CNavPath *const this,
//						int i);  //    32
//				Vector(Vector *const this,
//					const Vector &v);  //    32
//			}
//		}
//	}
}

/* <41fd51> ../cstrike/dlls/hostage/states/hostage_escape.cpp:52 */
void HostageEscapeToCoverState::OnUpdate(CHostageImprov *improv)
{
//	Idle(CHostageImprov *const this);  //    57
//	OnUpdate(HostageEscapeToCoverState *const this,
//		class CHostageImprov *improv);  //    52
}

/* <41f65f> ../cstrike/dlls/hostage/states/hostage_escape.cpp:95 */
void HostageEscapeToCoverState::OnExit(CHostageImprov *improv)
{
}

/* <41faaf> ../cstrike/dlls/hostage/states/hostage_escape.cpp:100 */
void HostageEscapeToCoverState::OnMoveToFailure(const Vector &goal, MoveToFailureType reason)
{
//	{
//		class HostageEscapeState *escape;                    //   103
//		LookAround(HostageEscapeState *const this);  //   104
//	}
}

/* <41fa2f> ../cstrike/dlls/hostage/states/hostage_escape.cpp:110 */
void HostageEscapeLookAroundState::OnEnter(CHostageImprov *improv)
{
//	Start(CountdownTimer *const this,
//		float duration);  //   112
}

/* <41fc67> ../cstrike/dlls/hostage/states/hostage_escape.cpp:119 */
void HostageEscapeLookAroundState::OnUpdate(CHostageImprov *improv)
{
//	IsElapsed(const class CountdownTimer *const this);  //   123
//	OnUpdate(HostageEscapeLookAroundState *const this,
//		class CHostageImprov *improv);  //   119
}

/* <41f693> ../cstrike/dlls/hostage/states/hostage_escape.cpp:133 */
void HostageEscapeLookAroundState::OnExit(CHostageImprov *improv)
{
}

/* <41fb6b> ../cstrike/dlls/hostage/states/hostage_escape.cpp:145 */
void HostageEscapeState::OnEnter(CHostageImprov *improv)
{
//	{
//		class CCSBotManager *ctrl;                           //   148
//		const class Zone *zone;                             //   149
//		GetRandomZone(const class CCSBotManager *const this);  //   149
//		SetRescueGoal(HostageEscapeToCoverState *const this,
//				const Vector &rescueGoal);  //   153
//		SetState(SimpleStateMachine<CHostageImprov*, HostageState> *const this,
//			class HostageState *newState);  //   156
//		Reset(SimpleStateMachine<CHostageImprov*, HostageState> *const this,
//			class CHostageImprov *userData);  //   155
//	}
}

/* <41fe8e> ../cstrike/dlls/hostage/states/hostage_escape.cpp:167 */
void HostageEscapeState::OnUpdate(CHostageImprov *improv)
{
//	{
//		class CBasePlayer *player;                           //   192
//		{
//			float const farRange;                          //   198
//		}
//	}
//	OnUpdate(HostageEscapeState *const this,
//		class CHostageImprov *improv);  //   167
}

/* <41f6c7> ../cstrike/dlls/hostage/states/hostage_escape.cpp:230 */
void HostageEscapeState::OnExit(CHostageImprov *improv)
{
}
