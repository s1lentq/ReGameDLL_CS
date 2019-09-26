#include "precompiled.h"

CBaseTutor *TheTutor = nullptr;

TutorMessageEvent::TutorMessageEvent(int mid, int duplicateID, float time, float lifetime, int priority)
{
	m_messageID = mid;
	m_duplicateID = duplicateID;
	m_activationTime = time;
	m_lifetime = lifetime;
	m_priority = priority;

	m_paramList = nullptr;
	m_numParameters = 0;
	m_next = nullptr;
}

TutorMessageEvent::~TutorMessageEvent()
{
	;
}

bool TutorMessageEvent::IsActive(float time)
{
	return (m_lifetime + m_activationTime >= time);
}

int TutorMessageEvent::GetPriority()
{
	return m_priority;
}

float TutorMessageEvent::GetTimeActive(float time)
{
	return (time - m_activationTime);
}

void TutorMessageEvent::SetActivationTime(float time)
{
	m_activationTime = time;
}

int TutorMessageEvent::GetID()
{
	return m_messageID;
}

int TutorMessageEvent::GetDuplicateID()
{
	return m_duplicateID;
}

void TutorMessageEvent::SetNext(TutorMessageEvent *next)
{
	m_next = next;
}

TutorMessageEvent *TutorMessageEvent::GetNext()
{
	return m_next;
}

void TutorMessageEvent::AddParameter(char *str)
{
	if (str == nullptr)
		return;

	TutorMessageEventParam *param = new TutorMessageEventParam;

	param->m_next = nullptr;
	param->m_data = new char[Q_strlen(str) + 1];

	if (param->m_data)
	{
		Q_strcpy(param->m_data, str);
		param->m_data[Q_strlen(str)] = '\0';
		m_numParameters++;

		if (m_paramList)
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

char *TutorMessageEvent::GetNextParameter(char *buf, int buflen)
{
	TutorMessageEventParam *param = m_paramList;
	if (!param)
	{
		return nullptr;
	}

	m_numParameters--;
	m_paramList = param->m_next;

	Q_strncpy(buf, param->m_data, buflen);

#ifdef REGAMEDLL_FIXES
	buf[buflen] = '\0';
#endif

	delete param;
	return buf;
}

int TutorMessageEvent::GetNumParameters()
{
	return m_numParameters;
}

CBaseTutor::CBaseTutor()
{
	m_eventList = nullptr;
	m_deadAirStartTime = 0;
	m_roundStartTime = 0;
}

CBaseTutor::~CBaseTutor()
{
	TutorMessageEvent *event = m_eventList;
	while (event)
	{
		TutorMessageEvent *temp = event;
		event = event->GetNext();

		delete temp;
	}
}

void CBaseTutor::OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	CallEventHandler(event, pEntity, pOther);
	CheckForStateTransition(event, pEntity, pOther);
}

void CBaseTutor::ShotFired(Vector source, Vector target)
{
	HandleShotFired(source, target);
}

void CBaseTutor::CheckForStateTransition(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	if (m_stateSystem->UpdateState(event, pEntity, pOther))
	{
		DisplayNewStateDescriptionToPlayer();
	}
}

void CBaseTutor::StartFrame(float time)
{
	TutorThink(time);
}

void CBaseTutor::DisplayMessageToPlayer(CBasePlayer *pPlayer, int id, const char *szMessage, TutorMessageEvent *event)
{
	TutorMessage *definition;
	int numArgs;
	char param[512];

	numArgs = event->GetNumParameters();
	definition = GetTutorMessageDefinition(event->GetID());

	MESSAGE_BEGIN(MSG_ONE, gmsgTutorText, nullptr, pPlayer->pev);
		WRITE_STRING(szMessage);
		WRITE_BYTE(numArgs);

		for (int arg = 0; arg < numArgs; arg++)
		{
			char *str = event->GetNextParameter(param, sizeof(param));
			if (str)
				WRITE_STRING(str);
			else
				WRITE_STRING("");
		}

		WRITE_SHORT(id);
		WRITE_SHORT(pPlayer->IsAlive() == FALSE);

		if (definition)
			WRITE_SHORT(definition->m_type);
		else
			WRITE_SHORT(TUTORMESSAGETYPE_DEFAULT);
	MESSAGE_END();

	m_deadAirStartTime = -1.0f;

	if (definition)
	{
		if (gpGlobals->time - m_roundStartTime > 1.0f)
		{
			switch (definition->m_type)
			{
			case TUTORMESSAGETYPE_FRIEND_DEATH:
				EMIT_SOUND_DYN(ENT(pPlayer->pev), CHAN_ITEM, "events/friend_died.wav", VOL_NORM, ATTN_NORM, 0, 120);
				break;
			case TUTORMESSAGETYPE_ENEMY_DEATH:
				EMIT_SOUND_DYN(ENT(pPlayer->pev), CHAN_ITEM, "events/enemy_died.wav", VOL_NORM, ATTN_NORM, 0, 85);
				break;
			default:
				EMIT_SOUND_DYN(ENT(pPlayer->pev), CHAN_ITEM, "events/tutor_msg.wav", VOL_NORM, ATTN_NORM, 0, 100);
				break;
			}
		}

		if (definition->m_decay)
		{
			REGISTER_TUTOR_MESSAGE_SHOWN(id);
		}
	}
}

NOXREF void CBaseTutor::DrawLineToEntity(CBasePlayer *pPlayer, int entindex, int id)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgTutorLine, nullptr, pPlayer->pev);
		WRITE_SHORT(entindex);
		WRITE_SHORT(id);
	MESSAGE_END();
}

void CBaseTutor::DisplayNewStateDescriptionToPlayer()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (!pLocalPlayer)
	{
		return;
	}

	auto desc = m_stateSystem->GetCurrentStateString();
	if (!desc)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgTutorState, nullptr, pLocalPlayer->pev);
			WRITE_STRING(nullptr);
		MESSAGE_END();
	}
}

void CBaseTutor::CloseCurrentWindow()
{
	CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
	if (pLocalPlayer)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgTutorClose, nullptr, pLocalPlayer->pev);
		MESSAGE_END();

		m_deadAirStartTime = gpGlobals->time;
	}
}

void CBaseTutor::CalculatePathForObjective(CBaseEntity *pPlayer)
{
	;
}

bool CBaseTutor::IsEntityInViewOfPlayer(CBaseEntity *pEntity, CBasePlayer *pPlayer)
{
	if (!pEntity || !pPlayer)
		return false;

	if (cv_tutor_view_distance.value < (pEntity->pev->origin - pPlayer->pev->origin).Length())
		return false;

	if (pPlayer->FInViewCone(pEntity))
	{
		TraceResult result;
		Vector eye = pPlayer->pev->view_ofs + pPlayer->pev->origin;

		UTIL_TraceLine(eye, pEntity->pev->origin, ignore_monsters, ignore_glass, pPlayer->pev->pContainingEntity, &result);

		if (result.flFraction == 1.0f)
		{
			return true;
		}
	}

	return false;
}

bool CBaseTutor::IsPlayerLookingAtPosition(Vector *origin, CBasePlayer *pPlayer)
{
	if (!origin || !pPlayer)
		return false;

	if (cv_tutor_look_distance.value < (*origin - pPlayer->pev->origin).Length())
		return false;

	if (pPlayer->IsLookingAtPosition(origin, cv_tutor_look_angle.value))
	{
		TraceResult result;
		Vector eye = pPlayer->pev->origin + pPlayer->pev->view_ofs;

		UTIL_TraceLine(eye, *origin, ignore_monsters, ignore_glass, ENT(pPlayer->pev), &result);

		if (result.flFraction == 1.0f)
			return true;
	}

	return false;
}

bool CBaseTutor::IsPlayerLookingAtEntity(CBaseEntity *pEntity, CBasePlayer *pPlayer)
{
	if (!pEntity || !pPlayer)
		return false;

	UTIL_MakeVectors(pPlayer->pev->v_angle);

	Vector srcVec = pPlayer->pev->view_ofs + pPlayer->pev->origin;
	Vector destVec = gpGlobals->v_forward * cv_tutor_look_distance.value + srcVec;

	TraceResult result;
	UTIL_TraceLine(srcVec, destVec, dont_ignore_monsters, ignore_glass, ENT(pPlayer->pev), &result);

	if (result.pHit)
	{
		if (!FNullEnt(result.pHit) && CBaseEntity::Instance(result.pHit) == pEntity)
		{
			return true;
		}
	}

	return false;
}

bool CBaseTutor::IsBombsiteInViewOfPlayer(CBaseEntity *pEntity, CBasePlayer *pPlayer)
{
	if (!pEntity || !pPlayer)
		return false;

	Vector bombSiteCenter = pEntity->Center();
	if (cv_tutor_view_distance.value < (bombSiteCenter - pPlayer->pev->origin).Length())
		return false;

	if (pPlayer->FInViewCone(pEntity))
	{
		TraceResult result;
		Vector eye = pPlayer->pev->origin + pPlayer->pev->view_ofs;

		UTIL_TraceLine(eye, bombSiteCenter, ignore_monsters, ignore_glass, ENT(pPlayer->pev), &result);

		if (result.flFraction == 1.0f)
		{
			return true;
		}
	}

	return false;
}

bool CBaseTutor::IsEntityInBombsite(CBaseEntity *bombsite, CBaseEntity *pEntity)
{
	if (!bombsite || !pEntity)
		return false;

	return bombsite->Intersects(pEntity);
}

bool CBaseTutor::DoMessagesHaveSameID(int id1, int id2)
{
	if (id1 == id2)
		return true;

	TutorMessage *message1 = GetTutorMessageDefinition(id1);
	TutorMessage *message2 = GetTutorMessageDefinition(id2);

	if (!message1 || !message2)
		return false;

	if (message1->m_duplicateID && message2->m_duplicateID)
		return true;

	return false;
}
