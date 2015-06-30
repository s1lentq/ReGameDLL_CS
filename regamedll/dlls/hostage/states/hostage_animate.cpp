#include "precompiled.h"

/* <4110a1> ../cstrike/dlls/hostage/states/hostage_animate.cpp:13 */
void HostageAnimateState::Reset(void)
{
}

/* <4110c7> ../cstrike/dlls/hostage/states/hostage_animate.cpp:20 */
void HostageAnimateState::StartSequence(CHostageImprov *improv, const SeqInfo *seqInfo)
{
//	{
//		class CHostage *hostage;                             //    24
//	}
}

/* <41110a> ../cstrike/dlls/hostage/states/hostage_animate.cpp:41 */
void HostageAnimateState::AddSequence(CHostageImprov *improv, const char *seqName, float holdTime, float rate)
{
//	{
//		class CHostage *hostage;                             //    46
//		StartSequence(HostageAnimateState *const this,
//				class CHostageImprov *improv,
//				const class SeqInfo *seqInfo);  //    55
//	}
}

/* <4111be> ../cstrike/dlls/hostage/states/hostage_animate.cpp:62 */
void HostageAnimateState::AddSequence(CHostageImprov *improv, int activity, float holdTime, float rate)
{
//	{
//		class CHostage *hostage;                             //    64
//		void *model;                                         //    66
//		StartSequence(HostageAnimateState *const this,
//				class CHostageImprov *improv,
//				const class SeqInfo *seqInfo);  //    77
//	}
}

/* <41127f> ../cstrike/dlls/hostage/states/hostage_animate.cpp:81 */
bool HostageAnimateState::IsDoneHolding(void)
{
//	IsElapsed(const class CountdownTimer *const this);  //    88
//	Start(CountdownTimer *const this,
//		float duration);  //    96
}

/* <410d45> ../cstrike/dlls/hostage/states/hostage_animate.cpp:103 */
void HostageAnimateState::OnEnter(CHostageImprov *improv)
{
}

/* <410d79> ../cstrike/dlls/hostage/states/hostage_animate.cpp:139 */
void HostageAnimateState::OnExit(CHostageImprov *improv)
{
}

/* <410fb2> ../cstrike/dlls/hostage/states/hostage_animate.cpp:108 */
void HostageAnimateState::OnUpdate(CHostageImprov *improv)
{
//	{
//		class CHostage *hostage;                             //   113
//		IsDoneHolding(HostageAnimateState *const this);  //   118
//	}
//	OnUpdate(HostageAnimateState *const this,
//		class CHostageImprov *improv);  //   108
}

/* <4112d1> ../cstrike/dlls/hostage/states/hostage_animate.cpp:147 */
bool HostageAnimateState::IsPlaying(CHostageImprov *improv, const char *seqName)
{
//	{
//		class CHostage *hostage;                             //   152
//		int id;                                               //   154
//	}
}
