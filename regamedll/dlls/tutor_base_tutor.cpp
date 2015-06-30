#include "precompiled.h"

CBaseTutor *TheTutor;

/* <1f545d> ../cstrike/dlls/tutor_base_tutor.cpp:22 */
NOBODY TutorMessageEvent::TutorMessageEvent(int mid, int duplicateID, float time, float lifetime, int priority)
{
}

/* <1f4d07> ../cstrike/dlls/tutor_base_tutor.cpp:34 */
//NOBODY void TutorMessageEvent::~TutorMessageEvent(void)
//{
//}

/* <1f54a6> ../cstrike/dlls/tutor_base_tutor.cpp:38 */
NOBODY bool TutorMessageEvent::IsActive(float time)
{
}

/* <1f54da> ../cstrike/dlls/tutor_base_tutor.cpp:48 */
NOBODY int TutorMessageEvent::GetPriority(void)
{
}

/* <1f5500> ../cstrike/dlls/tutor_base_tutor.cpp:53 */
NOBODY float TutorMessageEvent::GetTimeActive(float time)
{
}

/* <1f5534> ../cstrike/dlls/tutor_base_tutor.cpp:58 */
NOBODY void TutorMessageEvent::SetActivationTime(float time)
{
}

/* <1f5568> ../cstrike/dlls/tutor_base_tutor.cpp:63 */
NOBODY int TutorMessageEvent::GetID(void)
{
}

/* <1f5589> ../cstrike/dlls/tutor_base_tutor.cpp:68 */
NOBODY int TutorMessageEvent::GetDuplicateID(void)
{
}

/* <1f55af> ../cstrike/dlls/tutor_base_tutor.cpp:73 */
NOBODY void TutorMessageEvent::SetNext(TutorMessageEvent *next)
{
}

/* <1f55e3> ../cstrike/dlls/tutor_base_tutor.cpp:78 */
NOBODY TutorMessageEvent *TutorMessageEvent::GetNext(void)
{
}

/* <1f5604> ../cstrike/dlls/tutor_base_tutor.cpp:83 */
NOBODY void TutorMessageEvent::AddParameter(char *str)
{
//	{
//		class TutorMessageEventParam *param;                 //    88
//		class TutorMessageEventParam *temp;                  //   101
//	}
}

/* <1f565d> ../cstrike/dlls/tutor_base_tutor.cpp:117 */
NOBODY char *TutorMessageEvent::GetNextParameter(char *buf, int buflen)
{
//	{
//		class TutorMessageEventParam *param;                 //   119
//	}
}

/* <1f569e> ../cstrike/dlls/tutor_base_tutor.cpp:136 */
NOBODY int TutorMessageEvent::GetNumParameters(void)
{
}

/* <1f56d8> ../cstrike/dlls/tutor_base_tutor.cpp:144 */
NOBODY CBaseTutor::CBaseTutor(void)
{
	m_eventList = NULL;
	m_deadAirStartTime = 0;
	m_roundStartTime = 0;
}

/* <1f4d28> ../cstrike/dlls/tutor_base_tutor.cpp:152 */
NOBODY CBaseTutor::~CBaseTutor(void)
{
//	{
//		class TutorMessageEvent *event;				//   154
//		{
//			class TutorMessageEvent *temp;			//   157
//			GetNext(TutorMessageEvent *const this);		//   158
//		}
//	}
}

/* <1f5766> ../cstrike/dlls/tutor_base_tutor.cpp:163 */
void CBaseTutor::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	CallEventHandler(event, entity, other);
	CheckForStateTransition(event, entity, other);
}

/* <1f5842> ../cstrike/dlls/tutor_base_tutor.cpp:172 */
NOBODY void CBaseTutor::ShotFired(Vector source, Vector target)
{
//	Vector(Vector *const this,
//		const Vector &v);  //   175
//	Vector(Vector *const this,
//		const Vector &v);  //   175
}

/* <1f58ca> ../cstrike/dlls/tutor_base_tutor.cpp:178 */
NOXREF void CBaseTutor::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (m_stateSystem->UpdateState(event, entity, other))
		DisplayNewStateDescriptionToPlayer();
}

/* <1f58f5> ../cstrike/dlls/tutor_base_tutor.cpp:189 */
NOBODY void CBaseTutor::StartFrame(float time)
{
	TutorThink(time);
}

/* <1f5993> ../cstrike/dlls/tutor_base_tutor.cpp:192 */
NOBODY void CBaseTutor::DisplayMessageToPlayer(CBasePlayer *player, int id, const char *szMessage, TutorMessageEvent *event)
{
//	{
//		class TutorMessage *definition;                      //   196
//		unsigned char numArgs;                                //   202
//		char param;                                           //   207
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //   198
//		{
//			int arg;                                      //   210
//			{
//				char *str;                           //   212
//				GetNextParameter(TutorMessageEvent *const this,
//						char *buf,
//						int buflen);  //   212
//			}
//		}
//	}
}

/* <1f5ad1> ../cstrike/dlls/tutor_base_tutor.cpp:264 */
NOBODY void CBaseTutor::DrawLineToEntity(CBasePlayer *player, int entindex, int id)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgTutorLine, NULL, player->pev);
		WRITE_SHORT(entindex);
		WRITE_SHORT(id);
	MESSAGE_END();
}

/* <1f5b4f> ../cstrike/dlls/tutor_base_tutor.cpp:275 */
NOXREF void CBaseTutor::DisplayNewStateDescriptionToPlayer(void)
{
	char *desc;
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
		return;

	desc = m_stateSystem->GetCurrentStateString();

	if (!desc)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgTutorState, NULL, localPlayer->pev);
			WRITE_STRING(NULL);
		MESSAGE_END();
	}
}

/* <1f5bb4> ../cstrike/dlls/tutor_base_tutor.cpp:293 */
void CBaseTutor::CloseCurrentWindow(void)
{
	CBasePlayer *localPlayer = (CBasePlayer *)UTIL_GetLocalPlayer();

	if (localPlayer != NULL)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgTutorClose, NULL, localPlayer->pev);
		MESSAGE_END();

		m_deadAirStartTime = gpGlobals->time;
	}
}

/* <1f5c26> ../cstrike/dlls/tutor_base_tutor.cpp:307 */
NOBODY void CBaseTutor::CalculatePathForObjective(CBaseEntity *player)
{
}

/* <1f52e6> ../cstrike/dlls/tutor_base_tutor.cpp:312 */
NOBODY bool CBaseTutor::IsEntityInViewOfPlayer(CBaseEntity *entity, CBasePlayer *player)
{
//	{
//		Vector eye;                                     //   332
//		TraceResult result;                                   //   334
//		operator-(const Vector *const this,
//				const Vector &v);  //   320
//		Length(const Vector *const this);  //   320
//	}
//	IsEntityInViewOfPlayer(CBaseTutor *const this,
//				class CBaseEntity *entity,
//				class CBasePlayer *player);  //   312
}

/* <1f508a> ../cstrike/dlls/tutor_base_tutor.cpp:343 */
NOBODY bool CBaseTutor::IsPlayerLookingAtPosition(Vector *origin, CBasePlayer *player)
{
//	{
//		Vector eye;                                     //   363
//		TraceResult result;                                   //   364
//		operator-(const Vector *const this,
//				const Vector &v);  //   351
//		Length(const Vector *const this);  //   351
//	}
//	IsPlayerLookingAtPosition(CBaseTutor *const this,
//					Vector *origin,
//					class CBasePlayer *player);  //   343
}

/* <1f4e92> ../cstrike/dlls/tutor_base_tutor.cpp:373 */
NOBODY bool CBaseTutor::IsPlayerLookingAtEntity(CBaseEntity *entity, CBasePlayer *player)
{
//	{
//		Vector srcVec;                                  //   380
//		Vector destVec;                                 //   386
//		TraceResult result;                                   //   389
//	}
//	IsPlayerLookingAtEntity(CBaseTutor *const this,
//				class CBaseEntity *entity,
//				class CBasePlayer *player);  //   373
}

/* <1f51b0> ../cstrike/dlls/tutor_base_tutor.cpp:402 */
NOBODY bool CBaseTutor::IsBombsiteInViewOfPlayer(CBaseEntity *entity, CBasePlayer *player)
{
//	{
//		Vector bombSiteCenter;                          //   410
//		Vector eye;                                     //   426
//		TraceResult result;                                   //   428
//	}
//	IsBombsiteInViewOfPlayer(CBaseTutor *const this,
//				class CBaseEntity *entity,
//				class CBasePlayer *player);  //   402
}

/* <1f4e37> ../cstrike/dlls/tutor_base_tutor.cpp:436 */
NOBODY bool CBaseTutor::IsEntityInBombsite(CBaseEntity *bombsite, CBaseEntity *entity)
{
//	IsEntityInBombsite(CBaseTutor *const this,
//				class CBaseEntity *bombsite,
//				class CBaseEntity *entity);  //   436
}

/* <1f5c5b> ../cstrike/dlls/tutor_base_tutor.cpp:457 */
NOBODY bool CBaseTutor::DoMessagesHaveSameID(int id1, int id2)
{
//	{
//		class TutorMessage *message1;                        //   464
//		class TutorMessage *message2;                        //   465
//	}
}
