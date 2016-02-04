#include "precompiled.h"

CBaseTutor *TheTutor = NULL;

/* <1f545d> ../cstrike/dlls/tutor_base_tutor.cpp:22 */
TutorMessageEvent::TutorMessageEvent(int mid, int duplicateID, float time, float lifetime, int priority)
{
	m_messageID = mid;
	m_duplicateID = duplicateID;
	m_activationTime = time;
	m_lifetime = lifetime;
	m_priority = priority;

	m_paramList = NULL;
	m_numParameters = 0;
	m_next = NULL;
}

/* <1f4d07> ../cstrike/dlls/tutor_base_tutor.cpp:34 */
TutorMessageEvent::~TutorMessageEvent()
{
	;
}

/* <1f54a6> ../cstrike/dlls/tutor_base_tutor.cpp:38 */
bool TutorMessageEvent::IsActive(float time)
{
	return (m_lifetime + m_activationTime >= time);
}

/* <1f54da> ../cstrike/dlls/tutor_base_tutor.cpp:48 */
int TutorMessageEvent::GetPriority()
{
	return m_priority;
}

/* <1f5500> ../cstrike/dlls/tutor_base_tutor.cpp:53 */
float TutorMessageEvent::GetTimeActive(float time)
{
	return (time - m_activationTime);
}

/* <1f5534> ../cstrike/dlls/tutor_base_tutor.cpp:58 */
void TutorMessageEvent::SetActivationTime(float time)
{
	m_activationTime = time;
}

/* <1f5568> ../cstrike/dlls/tutor_base_tutor.cpp:63 */
int TutorMessageEvent::GetID()
{
	return m_messageID;
}

/* <1f5589> ../cstrike/dlls/tutor_base_tutor.cpp:68 */
int TutorMessageEvent::GetDuplicateID()
{
	return m_duplicateID;
}

/* <1f55af> ../cstrike/dlls/tutor_base_tutor.cpp:73 */
void TutorMessageEvent::SetNext(TutorMessageEvent *next)
{
	m_next = next;
}

/* <1f55e3> ../cstrike/dlls/tutor_base_tutor.cpp:78 */
TutorMessageEvent *TutorMessageEvent::GetNext()
{
	return m_next;
}

/* <1f5604> ../cstrike/dlls/tutor_base_tutor.cpp:83 */
void TutorMessageEvent::AddParameter(char *str)
{
	if (str == NULL)
	{
		return;
	}

	TutorMessageEventParam *param = new TutorMessageEventParam;

	param->m_next = NULL;
	param->m_data = new char[Q_strlen(str) + 1];

	if (param->m_data != NULL)
	{
		Q_strcpy(param->m_data, str);
		param->m_data[Q_strlen(str)] = '\0';
		++m_numParameters;

		if (m_paramList != NULL)
		{
			TutorMessageEventParam *temp = m_paramList;

			while (temp->m_next)
				temp = temp->m_next;

			temp->m_next = param;
		}
		else
			m_paramList = param;
	}
}

/* <1f565d> ../cstrike/dlls/tutor_base_tutor.cpp:117 */
char *TutorMessageEvent::GetNextParameter(char *buf, int buflen)
{
	TutorMessageEventParam *param = m_paramList;

	if (param == NULL)
	{
		return NULL;
	}

	m_numParameters--;
	m_paramList = param->m_next;

	Q_strncpy(buf, param->m_data, buflen);

#ifdef REGAMEDLL_FIXES
	buf[buflen] = '\0';
#endif // REGAMEDLL_FIXES

	delete param;
	return buf;
}

/* <1f569e> ../cstrike/dlls/tutor_base_tutor.cpp:136 */
int TutorMessageEvent::GetNumParameters()
{
	return m_numParameters;
}

/* <1f56d8> ../cstrike/dlls/tutor_base_tutor.cpp:144 */
CBaseTutor::CBaseTutor()
{
	m_eventList = NULL;
	m_deadAirStartTime = 0;
	m_roundStartTime = 0;
}

/* <1f4d28> ../cstrike/dlls/tutor_base_tutor.cpp:152 */
CBaseTutor::~CBaseTutor()
{
	TutorMessageEvent *event = m_eventList;

	while (event != NULL)
	{
		TutorMessageEvent *temp = event;
		event = event->GetNext();

		delete temp;
	}
}

/* <1f5766> ../cstrike/dlls/tutor_base_tutor.cpp:163 */
void CBaseTutor::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	CallEventHandler(event, entity, other);
	CheckForStateTransition(event, entity, other);
}

/* <1f5842> ../cstrike/dlls/tutor_base_tutor.cpp:172 */
void CBaseTutor::ShotFired(Vector source, Vector target)
{
	HandleShotFired(source, target);
}

/* <1f58ca> ../cstrike/dlls/tutor_base_tutor.cpp:178 */
void CBaseTutor::CheckForStateTransition(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	if (m_stateSystem->UpdateState(event, entity, other))
	{
		DisplayNewStateDescriptionToPlayer();
	}
}

/* <1f58f5> ../cstrike/dlls/tutor_base_tutor.cpp:189 */
void CBaseTutor::StartFrame(float time)
{
	TutorThink(time);
}

/* <1f5993> ../cstrike/dlls/tutor_base_tutor.cpp:192 */
void CBaseTutor::DisplayMessageToPlayer(CBasePlayer *player, int id, const char *szMessage, TutorMessageEvent *event)
{
	TutorMessage *definition;
	int numArgs;
	char param[512];

	numArgs = event->GetNumParameters();
	definition = GetTutorMessageDefinition(event->GetID());

	MESSAGE_BEGIN(MSG_ONE, gmsgTutorText, NULL, player->pev);
		WRITE_STRING(szMessage);
		WRITE_BYTE(numArgs);

		for (int arg = 0; arg < numArgs; ++arg)
		{
			char *str = event->GetNextParameter(param, sizeof(param));

			if (str != NULL)
				WRITE_STRING(str);
			else
				WRITE_STRING("");
		}

		WRITE_SHORT(id);
		WRITE_SHORT(player->IsAlive() == FALSE);

		if (definition != NULL)
			WRITE_SHORT(definition->m_type);
		else
			WRITE_SHORT(TUTORMESSAGETYPE_DEFAULT);
	MESSAGE_END();

	m_deadAirStartTime = -1.0f;

	if (definition != NULL)
	{
		if (gpGlobals->time - m_roundStartTime > 1.0f)
		{
			switch (definition->m_type)
			{
			case TUTORMESSAGETYPE_FRIEND_DEATH:
				EMIT_SOUND_DYN(ENT(player->pev), CHAN_ITEM, "events/friend_died.wav", VOL_NORM, ATTN_NORM, 0, 120);
				break;
			case TUTORMESSAGETYPE_ENEMY_DEATH:
				EMIT_SOUND_DYN(ENT(player->pev), CHAN_ITEM, "events/enemy_died.wav", VOL_NORM, ATTN_NORM, 0, 85);
				break;
			default:
				EMIT_SOUND_DYN(ENT(player->pev), CHAN_ITEM, "events/tutor_msg.wav", VOL_NORM, ATTN_NORM, 0, 100);
				break;
			}
		}

		if (definition->m_decay)
		{
			REGISTER_TUTOR_MESSAGE_SHOWN(id);
		}
	}
}

/* <1f5ad1> ../cstrike/dlls/tutor_base_tutor.cpp:264 */
NOXREF void CBaseTutor::DrawLineToEntity(CBasePlayer *player, int entindex, int id)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgTutorLine, NULL, player->pev);
		WRITE_SHORT(entindex);
		WRITE_SHORT(id);
	MESSAGE_END();
}

/* <1f5b4f> ../cstrike/dlls/tutor_base_tutor.cpp:275 */
void CBaseTutor::DisplayNewStateDescriptionToPlayer()
{
	CBasePlayer *localPlayer = UTIL_GetLocalPlayer();

	if (localPlayer == NULL)
	{
		return;
	}

	char *desc = m_stateSystem->GetCurrentStateString();

	if (!desc)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgTutorState, NULL, localPlayer->pev);
			WRITE_STRING(NULL);
		MESSAGE_END();
	}
}

/* <1f5bb4> ../cstrike/dlls/tutor_base_tutor.cpp:293 */
void CBaseTutor::CloseCurrentWindow()
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
void CBaseTutor::CalculatePathForObjective(CBaseEntity *player)
{
	;
}

/* <1f52e6> ../cstrike/dlls/tutor_base_tutor.cpp:312 */
bool CBaseTutor::__MAKE_VHOOK(IsEntityInViewOfPlayer)(CBaseEntity *entity, CBasePlayer *player)
{
	if (entity == NULL || player == NULL)
	{
		return false;
	}

	if (cv_tutor_view_distance.value < (entity->pev->origin - player->pev->origin).Length())
	{
		return false;
	}

	if (player->FInViewCone(entity))
	{
		TraceResult result;
		Vector eye = player->pev->view_ofs + player->pev->origin;

		UTIL_TraceLine(eye, entity->pev->origin, ignore_monsters, ignore_glass, player->pev->pContainingEntity, &result);

		if (result.flFraction == 1.0f)
		{
			return true;
		}
	}

	return false;
}

/* <1f508a> ../cstrike/dlls/tutor_base_tutor.cpp:343 */
bool CBaseTutor::__MAKE_VHOOK(IsPlayerLookingAtPosition)(Vector *origin, CBasePlayer *player)
{
	if (origin == NULL || player == NULL)
	{
		return false;
	}

	if (cv_tutor_look_distance.value < (*origin - player->pev->origin).Length())
	{
		return false;
	}

	if (player->IsLookingAtPosition(origin, cv_tutor_look_angle.value))
	{
		TraceResult result;
		Vector eye = player->pev->origin + player->pev->view_ofs;

		UTIL_TraceLine(eye, *origin, ignore_monsters, ignore_glass, ENT(player->pev), &result);

		if (result.flFraction == 1.0f)
			return true;
	}

	return false;
}

/* <1f4e92> ../cstrike/dlls/tutor_base_tutor.cpp:373 */
bool CBaseTutor::__MAKE_VHOOK(IsPlayerLookingAtEntity)(CBaseEntity *entity, CBasePlayer *player)
{
	if (entity == NULL || player == NULL)
	{
		return false;
	}

	UTIL_MakeVectors(player->pev->v_angle);

	Vector srcVec = player->pev->view_ofs + player->pev->origin;
	Vector destVec = gpGlobals->v_forward * cv_tutor_look_distance.value + srcVec;

	TraceResult result;
	UTIL_TraceLine(srcVec, destVec, dont_ignore_monsters, ignore_glass, ENT(player->pev), &result);

	if (result.pHit != NULL)
	{
		if (!FNullEnt(result.pHit) && CBaseEntity::Instance(result.pHit) == entity)
		{
			return true;
		}
	}

	return false;
}

/* <1f51b0> ../cstrike/dlls/tutor_base_tutor.cpp:402 */
bool CBaseTutor::__MAKE_VHOOK(IsBombsiteInViewOfPlayer)(CBaseEntity *entity, CBasePlayer *player)
{
	if (entity == NULL || player == NULL)
	{
		return false;
	}

	Vector bombSiteCenter = (entity->pev->absmax + entity->pev->absmin) * 0.5;

	if (cv_tutor_view_distance.value < (bombSiteCenter - player->pev->origin).Length())
	{
		return false;
	}

	if (player->FInViewCone(entity))
	{
		TraceResult result;
		Vector eye = player->pev->origin + player->pev->view_ofs;

		UTIL_TraceLine(eye, bombSiteCenter, ignore_monsters, ignore_glass, ENT(player->pev), &result);

		if (result.flFraction == 1.0f)
		{
			return true;
		}
	}

	return false;
}

/* <1f4e37> ../cstrike/dlls/tutor_base_tutor.cpp:436 */
bool CBaseTutor::__MAKE_VHOOK(IsEntityInBombsite)(CBaseEntity *bombsite, CBaseEntity *entity)
{
	if (bombsite == NULL || entity == NULL)
	{
		return false;
	}

	if (entity->pev->origin.x <= bombsite->pev->absmax.x
		&& entity->pev->origin.y <= bombsite->pev->absmax.y
		&& entity->pev->origin.z <= bombsite->pev->absmax.z
		&& entity->pev->origin.x >= bombsite->pev->absmin.x
		&& entity->pev->origin.y >= bombsite->pev->absmin.y
		&& entity->pev->origin.z >= bombsite->pev->absmin.z)
	{
		return true;
	}

	return false;
}

/* <1f5c5b> ../cstrike/dlls/tutor_base_tutor.cpp:457 */
bool CBaseTutor::DoMessagesHaveSameID(int id1, int id2)
{
	if (id1 == id2)
	{
		return true;
	}

	TutorMessage *message1 = GetTutorMessageDefinition(id1);
	TutorMessage *message2 = GetTutorMessageDefinition(id2);

	if (message1 == NULL || message2 == NULL)
	{
		return false;
	}

	if (message1->m_duplicateID && message2->m_duplicateID)
	{
		return true;
	}

	return false;
}
