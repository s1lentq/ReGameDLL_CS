#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFrictionModifier::m_SaveData[] =
{
	DEFINE_FIELD(CFrictionModifier, m_frictionFraction, FIELD_FLOAT),
};

TYPEDESCRIPTION CAutoTrigger::m_SaveData[] =
{
	DEFINE_FIELD(CAutoTrigger, m_globalstate, FIELD_STRING),
	DEFINE_FIELD(CAutoTrigger, triggerType, FIELD_INTEGER),
};

TYPEDESCRIPTION CTriggerRelay::m_SaveData[1] =
{
	DEFINE_FIELD(CTriggerRelay, triggerType, FIELD_INTEGER),
};

TYPEDESCRIPTION CMultiManager::m_SaveData[] =
{
	DEFINE_FIELD(CMultiManager, m_cTargets, FIELD_INTEGER),
	DEFINE_FIELD(CMultiManager, m_index, FIELD_INTEGER),
	DEFINE_FIELD(CMultiManager, m_startTime, FIELD_TIME),
	DEFINE_ARRAY(CMultiManager, m_iTargetName, FIELD_STRING, MAX_MULTI_TARGETS),
	DEFINE_ARRAY(CMultiManager, m_flTargetDelay, FIELD_FLOAT, MAX_MULTI_TARGETS),
};

TYPEDESCRIPTION CChangeLevel::m_SaveData[] =
{
	DEFINE_ARRAY(CChangeLevel, m_szMapName, FIELD_CHARACTER, 32),
	DEFINE_ARRAY(CChangeLevel, m_szLandmarkName, FIELD_CHARACTER, 32),
	DEFINE_FIELD(CChangeLevel, m_changeTarget, FIELD_STRING),
	DEFINE_FIELD(CChangeLevel, m_changeTargetDelay, FIELD_FLOAT),
};
TYPEDESCRIPTION CTriggerChangeTarget::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerChangeTarget, m_iszNewTarget, FIELD_STRING),
};

TYPEDESCRIPTION CTriggerCamera::m_SaveData[] =
{
	DEFINE_FIELD(CTriggerCamera, m_hPlayer, FIELD_EHANDLE),
	DEFINE_FIELD(CTriggerCamera, m_hTarget, FIELD_EHANDLE),
	DEFINE_FIELD(CTriggerCamera, m_pentPath, FIELD_CLASSPTR),
	DEFINE_FIELD(CTriggerCamera, m_sPath, FIELD_STRING),
	DEFINE_FIELD(CTriggerCamera, m_flWait, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_flReturnTime, FIELD_TIME),
	DEFINE_FIELD(CTriggerCamera, m_flStopTime, FIELD_TIME),
	DEFINE_FIELD(CTriggerCamera, m_moveDistance, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_targetSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_initialSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_acceleration, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_deceleration, FIELD_FLOAT),
	DEFINE_FIELD(CTriggerCamera, m_state, FIELD_INTEGER),
};

#else

TYPEDESCRIPTION (*CFrictionModifier::pm_SaveData)[1];
TYPEDESCRIPTION (*CAutoTrigger::pm_SaveData)[2];
TYPEDESCRIPTION (*CTriggerRelay::pm_SaveData)[1];
TYPEDESCRIPTION (*CMultiManager::pm_SaveData)[5];
TYPEDESCRIPTION (*CChangeLevel::pm_SaveData)[4];
TYPEDESCRIPTION (*CTriggerChangeTarget::pm_SaveData)[1];
TYPEDESCRIPTION (*CTriggerCamera::pm_SaveData)[13];

#endif // HOOK_GAMEDLL

/* <1a257e> ../cstrike/dlls/triggers.cpp:60 */
LINK_ENTITY_TO_CLASS(func_friction, CFrictionModifier);

/* <1a0ad7> ../cstrike/dlls/triggers.cpp:68 */
IMPLEMENT_SAVERESTORE(CFrictionModifier, CBaseEntity);

/* <19fa7d> ../cstrike/dlls/triggers.cpp:72 */
NOBODY void CFrictionModifier::__MAKE_VHOOK(Spawn)(void)
{
}

/* <19faa6> ../cstrike/dlls/triggers.cpp:82 */
NOBODY void CFrictionModifier::ChangeFriction(CBaseEntity *pOther)
{
}

/* <1a1c39> ../cstrike/dlls/triggers.cpp:91 */
NOBODY void CFrictionModifier::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
}

/* <1a2657> ../cstrike/dlls/triggers.cpp:126 */
LINK_ENTITY_TO_CLASS(trigger_auto, CAutoTrigger);

/* <1a0a85> ../cstrike/dlls/triggers.cpp:134 */
IMPLEMENT_SAVERESTORE(CAutoTrigger, CBaseDelay);

/* <1a1b64> ../cstrike/dlls/triggers.cpp:136 */
NOBODY void CAutoTrigger::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   138
//	FStrEq(const char *sz1,
//		const char *sz2);  //   143
//	{
//		int type;                                             //   145
//		atoi(const char *__nptr);  //   145
//	} 
//	KeyValue(class CAutoTrigger *const this,
//		KeyValueData *pkvd);  //   136
}

/* <19fb05> ../cstrike/dlls/triggers.cpp:165 */
NOBODY void CAutoTrigger::__MAKE_VHOOK(Spawn)(void)
{
}

/* <19fb2d> ../cstrike/dlls/triggers.cpp:171 */
NOBODY void CAutoTrigger::__MAKE_VHOOK(Precache)(void)
{
}

/* <19d48c> ../cstrike/dlls/triggers.cpp:177 */
NOBODY void CAutoTrigger::__MAKE_VHOOK(Think)(void)
{
}

/* <1a2730> ../cstrike/dlls/triggers.cpp:207 */
LINK_ENTITY_TO_CLASS(trigger_relay, CTriggerRelay);

/* <1a0a33> ../cstrike/dlls/triggers.cpp:214 */
IMPLEMENT_SAVERESTORE(CTriggerRelay, CBaseDelay);

/* <1a1abc> ../cstrike/dlls/triggers.cpp:216 */
NOBODY void CTriggerRelay::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   218
//	KeyValue(class CTriggerRelay *const this,
//		KeyValueData *pkvd);  //   216
}

/* <19fb7e> ../cstrike/dlls/triggers.cpp:240 */
NOBODY void CTriggerRelay::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a01d7> ../cstrike/dlls/triggers.cpp:247 */
NOBODY void CTriggerRelay::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <1a283f> ../cstrike/dlls/triggers.cpp:304 */
LINK_ENTITY_TO_CLASS(multi_manager, CMultiManager);

/* <1a09e0> ../cstrike/dlls/triggers.cpp:316 */
IMPLEMENT_SAVERESTORE(CMultiManager, CBaseToggle);

/* <1a19ed> ../cstrike/dlls/triggers.cpp:318 */
NOBODY void CMultiManager::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   325
//	{ 
//		char tmp;                                             //   335
//		atof(const char *__nptr);  //   339
//	} 
//	KeyValue(class CMultiManager *const this,
//		KeyValueData *pkvd);  //   318
}

/* <19fbce> ../cstrike/dlls/triggers.cpp:347 */
NOBODY void CMultiManager::__MAKE_VHOOK(Spawn)(void)
{
//	{
//		int swapped;                                          //   355
//		{
//			int i;                                        //   360
//			{ 
//				int name;                             //   365
//				float delay;                          //   366
//			} 
//		} 
//	} 
}

/* <1a03e5> ../cstrike/dlls/triggers.cpp:377 */
NOBODY void CMultiManager::__MAKE_VHOOK(Restart)(void)
{
//	{
//		int i;                                                //   379
//		edict_t *pentTarget;                                 //   380
//		const char *name;                                   //   381
//		{
//			class CBaseEntity *pTarget;                  //   399
//			FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//							const char *pszName);  //   395
//			FNullEnt(const edict_t *pent);  //   396
//			Instance(edict_t *pent);  //   399
//		} 
//		IsClone(class CMultiManager *const this);  //   410
//	} 
}

/* <1a1402> ../cstrike/dlls/triggers.cpp:420 */
NOBODY BOOL CMultiManager::__MAKE_VHOOK(HasTarget)(string_t targetname)
{
//	{
//		int i;                                                //   422
//		FStrEq(const char *sz1,
//			const char *sz2);  //   423
//	} 
}

/* <1a0393> ../cstrike/dlls/triggers.cpp:432 */
NOBODY void CMultiManager::ManagerThink(void)
{
//	{
//		float time;                                           //   434
//		IsClone(class CMultiManager *const this);  //   446
//	} 
}

/* <1a291b> ../cstrike/dlls/triggers.cpp:457 */
NOBODY CMultiManager *CMultiManager::Clone(void)
{
	CMultiManager *pMulti = GetClassPtr((CMultiManager *)NULL);
	edict_t *pEdict = pMulti->pev->pContainingEntity;

	Q_memcpy(pMulti->pev, pev, sizeof(*pev));
	pMulti->pev->pContainingEntity = pEdict;
	pMulti->pev->spawnflags |= SF_MULTIMAN_CLONE;
	pMulti->m_cTargets = m_cTargets;
	Q_memcpy(pMulti->m_iTargetName, m_iTargetName, sizeof(m_iTargetName));
	Q_memcpy(pMulti->m_flTargetDelay, m_flTargetDelay, sizeof(m_flTargetDelay));
	return pMulti;
}

/* <1a2a24> ../cstrike/dlls/triggers.cpp:475 */
NOBODY void CMultiManager::ManagerUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	ShouldClone(class CMultiManager *const this);  //   479
//	{ 
//		class CMultiManager *pClone;                         //   481
//	} 
}

/* <1a2ada> ../cstrike/dlls/triggers.cpp:532 */
LINK_ENTITY_TO_CLASS(env_render, CRenderFxManager);

/* <19fc52> ../cstrike/dlls/triggers.cpp:535 */
NOBODY void CRenderFxManager::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a0c95> ../cstrike/dlls/triggers.cpp:540 */
NOBODY void CRenderFxManager::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(class CRenderFxManager *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   540
}

/* <1a2bb6> ../cstrike/dlls/triggers.cpp:583 */
LINK_ENTITY_TO_CLASS(trigger, CBaseTrigger);

/* <1a2c92> ../cstrike/dlls/triggers.cpp:590 */
NOBODY void CBaseTrigger::InitTrigger(void)
{
//	operator!=(const class Vector *const this,
//			const class Vector  &const v);  //   594
}

/* <1a17cf> ../cstrike/dlls/triggers.cpp:608 */
NOBODY void CBaseTrigger::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   610
//	FStrEq(const char *sz1,
//		const char *sz2);  //   615
//	KeyValue(class CBaseTrigger *const this,
//		KeyValueData *pkvd);  //   608
//	atof(const char *__nptr);  //   612
//	atof(const char *__nptr);  //   617
}

/* <1a3060> ../cstrike/dlls/triggers.cpp:636 */
LINK_ENTITY_TO_CLASS(trigger_hurt, CTriggerHurt);

/* <1a313c> ../cstrike/dlls/triggers.cpp:649 */
LINK_ENTITY_TO_CLASS(trigger_monsterjump, CTriggerMonsterJump);

/* <1a2fdc> ../cstrike/dlls/triggers.cpp:652 */
NOBODY void CTriggerMonsterJump::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(class CTriggerMonsterJump *const this);  //   652
}

/* <1a00e4> ../cstrike/dlls/triggers.cpp:671 */
NOBODY void CTriggerMonsterJump::__MAKE_VHOOK(Think)(void)
{
}

/* <19fca2> ../cstrike/dlls/triggers.cpp:678 */
NOBODY void CTriggerMonsterJump::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevOther;                                 //   680
//		operator*(const class Vector *const this,
//				float fl);  //   695
//	} 
}

/* <1a3218> ../cstrike/dlls/triggers.cpp:715 */
LINK_ENTITY_TO_CLASS(trigger_cdaudio, CTriggerCDAudio);

/* <1a2382> ../cstrike/dlls/triggers.cpp:721 */
NOBODY void CTriggerCDAudio::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
//	PlayTrack(class CTriggerCDAudio *const this);  //   728
}

/* <1a2fb4> ../cstrike/dlls/triggers.cpp:731 */
NOBODY void CTriggerCDAudio::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a2288> ../cstrike/dlls/triggers.cpp:736 */
NOBODY void CTriggerCDAudio::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	PlayTrack(class CTriggerCDAudio *const this);  //   738
}

/* <19e08b> ../cstrike/dlls/triggers.cpp:741 */
NOBODY void PlayCDTrack(int iTrack)
{
//	{
//		edict_t *pClient;                                    //   743
//		{
//			char string;                                  //   764
//		}
//	}
}

/* <1a3372> ../cstrike/dlls/triggers.cpp:773 */
NOBODY void CTriggerCDAudio::PlayTrack(void)
{
//	PlayCDTrack(int iTrack);  //   775
}

/* <1a340c> ../cstrike/dlls/triggers.cpp:794 */
LINK_ENTITY_TO_CLASS(target_cdaudio, CTargetCDAudio);

/* <1a170f> ../cstrike/dlls/triggers.cpp:796 */
NOBODY void CTargetCDAudio::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   798
//	KeyValue(class CBaseEntity *const this,
//		KeyValueData *pkvd);  //   804
//	KeyValue(class CTargetCDAudio *const this,
//		KeyValueData *pkvd);  //   796
}

/* <1a066a> ../cstrike/dlls/triggers.cpp:807 */
NOBODY void CTargetCDAudio::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(class CTargetCDAudio *const this);  //   807
}

/* <1a2175> ../cstrike/dlls/triggers.cpp:816 */
NOBODY void CTargetCDAudio::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Play(class CTargetCDAudio *const this);  //   818
}

/* <1a2465> ../cstrike/dlls/triggers.cpp:822 */
NOBODY void CTargetCDAudio::__MAKE_VHOOK(Think)(void)
{
//	{
//		edict_t *pClient;                                    //   824
//		operator-(const class Vector *const this,
//				const class Vector  &const v);  //   835
//		Length(const class Vector *const this);  //   835
//		Play(class CTargetCDAudio *const this);  //   836
//	} 
}

/* <1a34e8> ../cstrike/dlls/triggers.cpp:840 */
NOBODY void CTargetCDAudio::Play(void)
{
//	PlayCDTrack(int iTrack);  //   842
}

/* <1a2f8b> ../cstrike/dlls/triggers.cpp:853 */
NOBODY void CTriggerHurt::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a5df2> ../cstrike/dlls/triggers.cpp:883 */
NOBODY void CTriggerHurt::RadiationThink(void)
{

}

/* <1a007c> ../cstrike/dlls/triggers.cpp:942 */
NOBODY void CBaseTrigger::ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <1a0d93> ../cstrike/dlls/triggers.cpp:959 */
NOBODY void CBaseTrigger::HurtTouch(CBaseEntity *pOther)
{
//	{
//		float fldmg;                                          //   961
//	} 
//	HurtTouch(class CBaseTrigger *const this,
//			class CBaseEntity *pOther);  //   959
}

/* <1a3582> ../cstrike/dlls/triggers.cpp:1086 */
LINK_ENTITY_TO_CLASS(trigger_multiple, CTriggerMultiple);

/* <1a2f67> ../cstrike/dlls/triggers.cpp:1089 */
NOBODY void CTriggerMultiple::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a365e> ../cstrike/dlls/triggers.cpp:1135 */
LINK_ENTITY_TO_CLASS(trigger_once, CTriggerOnce);

/* <1a301c> ../cstrike/dlls/triggers.cpp:1136 */
NOBODY void CTriggerOnce::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(class CTriggerMultiple *const this);  //  1140
}

/* <1a20a4> ../cstrike/dlls/triggers.cpp:1145 */
NOBODY void CBaseTrigger::MultiTouch(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevToucher;                               //  1147
//		ActivateMultiTrigger(class CBaseTrigger *const this,
//					class CBaseEntity *pActivator);  //  1157
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  1154
//	} 
}

/* <1a373a> ../cstrike/dlls/triggers.cpp:1167 */
NOBODY void CBaseTrigger::ActivateMultiTrigger(CBaseEntity *pActivator)
{
}

/* <19fd1a> ../cstrike/dlls/triggers.cpp:1214 */
NOBODY void CBaseTrigger::MultiWaitOver(void)
{
}

/* <1a1f98> ../cstrike/dlls/triggers.cpp:1231 */
NOBODY void CBaseTrigger::CounterUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		BOOL fTellActivator;                                  //  1239
//	} 
//	CounterUse(class CBaseTrigger *const this,
//			class CBaseEntity *pActivator,
//			class CBaseEntity *pCaller,
//			USE_TYPE useType,
//			float value);  //  1231
}

/* <1a3767> ../cstrike/dlls/triggers.cpp:1278 */
LINK_ENTITY_TO_CLASS(trigger_counter, CTriggerCounter);

/* <19fd42> ../cstrike/dlls/triggers.cpp:1280 */
NOBODY void CTriggerCounter::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a3843> ../cstrike/dlls/triggers.cpp:1299 */
LINK_ENTITY_TO_CLASS(trigger_transition, CTriggerVolume);

/* <19fd6a> ../cstrike/dlls/triggers.cpp:1302 */
NOBODY void CTriggerVolume::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a3955> ../cstrike/dlls/triggers.cpp:1321 */
LINK_ENTITY_TO_CLASS(fireanddie, CFireAndDie);

/* <1a0618> ../cstrike/dlls/triggers.cpp:1323 */
NOBODY void CFireAndDie::__MAKE_VHOOK(Spawn)(void)
{
//	MAKE_STRING_CLASS(const char *str,
//				entvars_t *pev);  //  1325
}

/* <19fdbb> ../cstrike/dlls/triggers.cpp:1330 */
NOBODY void CFireAndDie::__MAKE_VHOOK(Precache)(void)
{
}

/* <1a01ae> ../cstrike/dlls/triggers.cpp:1337 */
NOBODY void CFireAndDie::__MAKE_VHOOK(Think)(void)
{
}

/* <1a3a67> ../cstrike/dlls/triggers.cpp:1371 */
LINK_ENTITY_TO_CLASS(trigger_changelevel, CChangeLevel);

/* <1a098d> ../cstrike/dlls/triggers.cpp:1382 */
IMPLEMENT_SAVERESTORE(CChangeLevel, CBaseTrigger);

/* <1a1d4a> ../cstrike/dlls/triggers.cpp:1388 */
NOBODY void CChangeLevel::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1390
//	KeyValue(class CChangeLevel *const this,
//		KeyValueData *pkvd);  //  1388
}

/* <1a2f25> ../cstrike/dlls/triggers.cpp:1423 */
NOBODY void CChangeLevel::__MAKE_VHOOK(Spawn)(void)
{
}

/* <19fde3> ../cstrike/dlls/triggers.cpp:1441 */
NOBODY void CChangeLevel::ExecuteChangeLevel(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  1443
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  1448
}

/* <1a3b43> ../cstrike/dlls/triggers.cpp:1456 */
edict_t *CChangeLevel::FindLandmark(const char *pLandmarkName)
{
	edict_t	*pentLandmark = FIND_ENTITY_BY_STRING(NULL, "targetname", pLandmarkName);
	while (!FNullEnt(pentLandmark))
	{
		// Found the landmark
		if (FClassnameIs(pentLandmark, "info_landmark"))
			return pentLandmark;
		else
			pentLandmark = FIND_ENTITY_BY_STRING(pentLandmark, "targetname", pLandmarkName);
	}

	ALERT(at_error, "Can't find landmark %s\n", pLandmarkName);
	return NULL;
}

/* <1a3e4f> ../cstrike/dlls/triggers.cpp:1479 */
NOBODY void CChangeLevel::UseChangeLevel(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	ChangeLevelNow(class CChangeLevel *const this,
//			class CBaseEntity *pActivator);  //  1481
}

/* <1a3fb2> ../cstrike/dlls/triggers.cpp:1484 */
NOBODY void CChangeLevel::ChangeLevelNow(CBaseEntity *pActivator)
{
//	{
//		edict_t *pentLandmark;                               //  1486
//		LEVELLIST levels;                                     //  1487
//		class CBaseEntity *pPlayer;                          //  1502
//		Instance(edict_t *pent);  //  1502
//		InTransitionVolume(class CBaseEntity *pEntity,
//					char *pVolumeName);  //  1503
//		{
//			class CFireAndDie *pFireAndDie;              //  1512
//			GetClassPtr<CFireAndDie>(class CFireAndDie *a);  //  1512
//			edict(class CBaseEntity *const this);  //  1520
//		} 
//		FNullEnt(const edict_t *pent);  //  1532
//	} 
}

/* <1a3ef5> ../cstrike/dlls/triggers.cpp:1545 */
NOBODY void CChangeLevel::TouchChangeLevel(CBaseEntity *pOther)
{
//	FClassnameIs(entvars_t *pev,
//			const char *szClassname);  //  1547
//	ChangeLevelNow(class CChangeLevel *const this,
//			class CBaseEntity *pActivator);  //  1550
}

// Add a transition to the list, but ignore duplicates 
// (a designer may have placed multiple trigger_changelevels with the same landmark)

/* <1a3ff8> ../cstrike/dlls/triggers.cpp:1556 */
int CChangeLevel::AddTransitionToList(LEVELLIST *pLevelList, int listCount, const char *pMapName, const char *pLandmarkName, edict_t *pentLandmark)
{
	int i;

	if (!pLevelList || !pMapName || !pLandmarkName || !pentLandmark)
	{
		return 0;
	}

	for (i = 0; i < listCount; i++)
	{
		if (pLevelList[i].pentLandmark == pentLandmark && Q_strcmp(pLevelList[i].mapName, pMapName) == 0)
		{
			return 0;
		}
	}

	Q_strcpy(pLevelList[ listCount ].mapName, pMapName);
	Q_strcpy(pLevelList[ listCount ].landmarkName, pLandmarkName);

	pLevelList[ listCount ].pentLandmark = pentLandmark;
	pLevelList[ listCount ].vecLandmarkOrigin = VARS(pentLandmark)->origin;

	return 1;
}

/* <1a44ba> ../cstrike/dlls/triggers.cpp:1576 */
NOBODY int BuildChangeList(LEVELLIST *pLevelList, int maxList)
{
	CChangeLevel::ChangeList(pLevelList, maxList);
}

/* <1a4075> ../cstrike/dlls/triggers.cpp:1582 */
int CChangeLevel::InTransitionVolume(CBaseEntity *pEntity, char *pVolumeName)
{
	edict_t	*pentVolume;

	if (pEntity->ObjectCaps() & FCAP_FORCE_TRANSITION)
	{
		return 1;
	}

	// If you're following another entity, follow it through the transition (weapons follow the player)
	if (pEntity->pev->movetype == MOVETYPE_FOLLOW)
	{
		if (pEntity->pev->aiment != NULL)
		{
			pEntity = CBaseEntity::Instance(pEntity->pev->aiment);
		}
	}

	// Unless we find a trigger_transition, everything is in the volume
	int inVolume = 1;

	pentVolume = FIND_ENTITY_BY_TARGETNAME(NULL, pVolumeName);
	while (!FNullEnt(pentVolume))
	{
		CBaseEntity *pVolume = CBaseEntity::Instance(pentVolume);

		if (pVolume && FClassnameIs(pVolume->pev, "trigger_transition"))
		{
			// It touches one, it's in the volume
			if (pVolume->Intersects(pEntity))
				return 1;
			else
			{
				// Found a trigger_transition, but I don't intersect it -- if I don't find another, don't go!
				inVolume = 0;
			}
		}

		pentVolume = FIND_ENTITY_BY_TARGETNAME(pentVolume, pVolumeName);
	}

	return inVolume;
}

// This has grown into a complicated beast
// Can we make this more elegant?
// This builds the list of all transitions on this level and which entities are in their PVS's and can / should
// be moved across.

/* <1a40b1> ../cstrike/dlls/triggers.cpp:1625 */
int CChangeLevel::ChangeList(LEVELLIST *pLevelList, int maxList)
{
	edict_t	*pentChangelevel, *pentLandmark;
	int i, count = 0;

	// Find all of the possible level changes on this BSP
	pentChangelevel = FIND_ENTITY_BY_STRING(NULL, "classname", "trigger_changelevel");

	if (FNullEnt(pentChangelevel))
		return 0;

	while (!FNullEnt(pentChangelevel))
	{
		CChangeLevel *pTrigger = GetClassPtr((CChangeLevel *)VARS(pentChangelevel));

		if (pTrigger != NULL)
		{
			// Find the corresponding landmark
			pentLandmark = FindLandmark(pTrigger->m_szLandmarkName);
			if (pentLandmark)
			{
				// Build a list of unique transitions
				if (AddTransitionToList( pLevelList, count, pTrigger->m_szMapName, pTrigger->m_szLandmarkName, pentLandmark))
				{
					count++;

					// FULL!!
					if (count >= maxList)
						break;
				}
			}
		}

		pentChangelevel = FIND_ENTITY_BY_STRING(pentChangelevel, "classname", "trigger_changelevel");
	}

	if (gpGlobals->pSaveData && ((SAVERESTOREDATA *)gpGlobals->pSaveData)->pTable)
	{
		CSave saveHelper((SAVERESTOREDATA *)gpGlobals->pSaveData);

		for (i = 0; i < count; i++)
		{
			int j, entityCount = 0;
			CBaseEntity *pEntList[ MAX_ENTITY ];
			int entityFlags[ MAX_ENTITY ];

			// Follow the linked list of entities in the PVS of the transition landmark
			edict_t *pent = FIND_ENTITY_IN_PVS(pLevelList[i].pentLandmark);

			// Build a list of valid entities in this linked list (we're going to use pent->v.chain again)
			while (!FNullEnt(pent))
			{
				CBaseEntity *pEntity = CBaseEntity::Instance(pent);
				if (pEntity)
				{
					int caps = pEntity->ObjectCaps();

					if (!(caps & FCAP_DONT_SAVE))
					{
						int flags = 0;

						// If this entity can be moved or is global, mark it
						if (caps & FCAP_ACROSS_TRANSITION)
							flags |= FENTTABLE_MOVEABLE;

						if (pEntity->pev->globalname && !pEntity->IsDormant())
							flags |= FENTTABLE_GLOBAL;

						if (flags)
						{
							pEntList[ entityCount ] = pEntity;
							entityFlags[ entityCount ] = flags;
							entityCount++;

							if (entityCount > MAX_ENTITY)
							{
								ALERT( at_error, "Too many entities across a transition!" );
							}
						}
					}
				}
				pent = pent->v.chain;
			}

			for (j = 0; j < entityCount; j++)
			{
				// Check to make sure the entity isn't screened out by a trigger_transition
				if (entityFlags[j] && InTransitionVolume(pEntList[j], pLevelList[i].landmarkName))
				{
					// Mark entity table with 1<<i
					int index = saveHelper.EntityIndex(pEntList[j]);
					// Flag it with the level number
					saveHelper.EntityFlagsSet(index, entityFlags[j] | (1 << i));
				}
			}
		}
	}

	return count;
}

/* <1a44fc> ../cstrike/dlls/triggers.cpp:1722 */
NOBODY void NextLevel(void)
{
//	{
//		edict_t *pent;                                       //  1724
//		class CChangeLevel *pChange;                         //  1725
//		FIND_ENTITY_BY_CLASSNAME(edict_t *entStart,
//					const char *pszName);  //  1728
//		FNullEnt(const edict_t *pent);  //  1731
//		GetClassPtr<CChangeLevel>(class CChangeLevel *a);  //  1738
//		VARS(edict_t *pent);  //  1738
//		GetClassPtr<CChangeLevel>(class CChangeLevel *a);  //  1734
//	}
}

/* <1a4709> ../cstrike/dlls/triggers.cpp:1760 */
LINK_ENTITY_TO_CLASS(func_ladder, CLadder);

/* <1a1937> ../cstrike/dlls/triggers.cpp:1763 */
NOBODY void CLadder::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
}

/* <19fe6c> ../cstrike/dlls/triggers.cpp:1772 */
NOBODY void CLadder::__MAKE_VHOOK(Precache)(void)
{
}

/* <19fe95> ../cstrike/dlls/triggers.cpp:1786 */
NOBODY void CLadder::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a47e5> ../cstrike/dlls/triggers.cpp:1804 */
LINK_ENTITY_TO_CLASS(trigger_push, CTriggerPush);

/* <1a18ff> ../cstrike/dlls/triggers.cpp:1807 */
NOBODY void CTriggerPush::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
}

/* <1a2eda> ../cstrike/dlls/triggers.cpp:1817 */
NOBODY void CTriggerPush::__MAKE_VHOOK(Spawn)(void)
{
//	operator==(const class Vector *const this,
//			const class Vector  &const v);  //  1819
}

/* <1a023c> ../cstrike/dlls/triggers.cpp:1835 */
NOBODY void CTriggerPush::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevToucher;                               //  1837
//		operator*(float fl,
//				const class Vector  &const v);  //  1854
//		operator+(const class Vector *const this,
//				const class Vector  &const v);  //  1854
//		{ 
//			class Vector vecPush;                         //  1861
//			operator*(float fl,
//					const class Vector  &const v);  //  1861
//			operator+(const class Vector *const this,
//					const class Vector  &const v);  //  1863
//		}
//	}
}

/* <1a051f> ../cstrike/dlls/triggers.cpp:1878 */
NOBODY void CBaseTrigger::TeleportTouch(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevToucher;                               //  1880
//		edict_t *pentTarget;                                 //  1881
//		class Vector tmp;                                     //  1910
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1906
//		FNullEnt(const edict_t *pent);  //  1907
//		Vector(class Vector *const this,
//			const class Vector  &const v);  //  1910
//	} 
}

/* <1a48c1> ../cstrike/dlls/triggers.cpp:1940 */
LINK_ENTITY_TO_CLASS(trigger_teleport, CTriggerTeleport);

/* <1a2eb1> ../cstrike/dlls/triggers.cpp:1942 */
NOBODY void CTriggerTeleport::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a499d> ../cstrike/dlls/triggers.cpp:1950 */
LINK_ENTITY_TO_CLASS(info_teleport_destination, CPointEntity);

/* <1a4a79> ../cstrike/dlls/triggers.cpp:1970 */
LINK_ENTITY_TO_CLASS(func_buyzone, CBuyZone);

/* <1a2e71> ../cstrike/dlls/triggers.cpp:1973 */
NOBODY void CBuyZone::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(class CBuyZone *const this);  //  1973
}

/* <1a116b> ../cstrike/dlls/triggers.cpp:1986 */
NOBODY void CBuyZone::BuyTouch(CBaseEntity *pOther)
{
//	{ 
//		class CBasePlayer *p;                                //  1991
//	} 
//	BuyTouch(class CBuyZone *const this,
//		class CBaseEntity *pOther);  //  1986
}

/* <1a4b55> ../cstrike/dlls/triggers.cpp:2016 */
LINK_ENTITY_TO_CLASS(func_bomb_target, CBombTarget);

/* <1a2e48> ../cstrike/dlls/triggers.cpp:2019 */
NOBODY void CBombTarget::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a10c1> ../cstrike/dlls/triggers.cpp:2027 */
NOBODY void CBombTarget::BombTargetTouch(CBaseEntity *pOther)
{
//	{ 
//		class CBasePlayer *p;                                //  2031
//	} 
//	BombTargetTouch(class CBombTarget *const this,
//			class CBaseEntity *pOther);  //  2027
}

/* <1a0014> ../cstrike/dlls/triggers.cpp:2042 */
NOBODY void CBombTarget::BombTargetUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <1a4c31> ../cstrike/dlls/triggers.cpp:2064 */
LINK_ENTITY_TO_CLASS(func_hostage_rescue, CHostageRescue);

/* <1a2e1f> ../cstrike/dlls/triggers.cpp:2067 */
NOBODY void CHostageRescue::__MAKE_VHOOK(Spawn)(void)
{
}

/* <19ffbf> ../cstrike/dlls/triggers.cpp:2074 */
NOBODY void CHostageRescue::HostageRescueTouch(CBaseEntity *pOther)
{
//	Signal(class CUnifiedSignals *const this,
//		int flSignal);  //  2078
}

/* <1a4d0d> ../cstrike/dlls/triggers.cpp:2105 */
LINK_ENTITY_TO_CLASS(func_escapezone, CEscapeZone);

/* <1a2df6> ../cstrike/dlls/triggers.cpp:2108 */
NOBODY void CEscapeZone::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a0f88> ../cstrike/dlls/triggers.cpp:2115 */
NOBODY void CEscapeZone::EscapeTouch(CBaseEntity *pOther)
{
//	{
//		class CBasePlayer *p;                                //  2120
//		Signal(class CUnifiedSignals *const this,
//			int flSignal);  //  2147
//	} 
//	EscapeTouch(class CEscapeZone *const this,
//			class CBaseEntity *pOther);  //  2115
}

/* <1a4de9> ../cstrike/dlls/triggers.cpp:2163 */
LINK_ENTITY_TO_CLASS(func_vip_safetyzone, CVIP_SafetyZone);

/* <1a2dcd> ../cstrike/dlls/triggers.cpp:2166 */
NOBODY void CVIP_SafetyZone::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a0ec7> ../cstrike/dlls/triggers.cpp:2173 */
NOBODY void CVIP_SafetyZone::VIP_SafetyTouch(CBaseEntity *pOther)
{
//	{ 
//		class CBasePlayer *p;                                //  2178
//		Signal(class CUnifiedSignals *const this,
//			int flSignal);  //  2180
//	} 
//	VIP_SafetyTouch(class CVIP_SafetyZone *const this,
//			class CBaseEntity *pOther);  //  2173
}

/* <1a4ec5> ../cstrike/dlls/triggers.cpp:2204 */
LINK_ENTITY_TO_CLASS(trigger_autosave, CTriggerSave);

/* <1a2d8e> ../cstrike/dlls/triggers.cpp:2206 */
NOBODY void CTriggerSave::__MAKE_VHOOK(Spawn)(void)
{
	//Spawn(class CTriggerSave *const this);  //  2206
}

/* <1a0c01> ../cstrike/dlls/triggers.cpp:2218 */
NOBODY void CTriggerSave::SaveTouch(CBaseEntity *pOther)
{
//	SaveTouch(class CTriggerSave *const this,
//			class CBaseEntity *pOther);  //  2218
}

/* <1a4fa1> ../cstrike/dlls/triggers.cpp:2242 */
LINK_ENTITY_TO_CLASS(trigger_endsection, CTriggerEndSection);

/* <1a0b7f> ../cstrike/dlls/triggers.cpp:2245 */
NOBODY void CTriggerEndSection::EndSectionUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	EndSectionUse(class CTriggerEndSection *const this,
//			class CBaseEntity *pActivator,
//			class CBaseEntity *pCaller,
//			USE_TYPE useType,
//			float value);  //  2245
}

/* <1a2d4f> ../cstrike/dlls/triggers.cpp:2260 */
NOBODY void CTriggerEndSection::__MAKE_VHOOK(Spawn)(void)
{
//	Spawn(class CTriggerEndSection *const this);  //  2260
}

/* <1a0b29> ../cstrike/dlls/triggers.cpp:2276 */
NOBODY void CTriggerEndSection::EndSectionTouch(CBaseEntity *pOther)
{
//	EndSectionTouch(class CTriggerEndSection *const this,
//			class CBaseEntity *pOther);  //  2276
}

/* <1a196f> ../cstrike/dlls/triggers.cpp:2291 */
NOBODY void CTriggerEndSection::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2293
//	KeyValue(class CTriggerEndSection *const this,
//		KeyValueData *pkvd);  //  2291
}

/* <1a507d> ../cstrike/dlls/triggers.cpp:2311 */
LINK_ENTITY_TO_CLASS(trigger_gravity, CTriggerGravity);

/* <1a2d26> ../cstrike/dlls/triggers.cpp:2313 */
NOBODY void CTriggerGravity::__MAKE_VHOOK(Spawn)(void)
{
}

/* <19febe> ../cstrike/dlls/triggers.cpp:2319 */
NOBODY void CTriggerGravity::GravityTouch(CBaseEntity *pOther)
{
}

/* <1a5159> ../cstrike/dlls/triggers.cpp:2351 */
LINK_ENTITY_TO_CLASS(trigger_changetarget, CTriggerChangeTarget);

/* <1a093a> ../cstrike/dlls/triggers.cpp:2358 */
IMPLEMENT_SAVERESTORE(CTriggerChangeTarget, CBaseDelay);

/* <1a1691> ../cstrike/dlls/triggers.cpp:2360 */
NOBODY void CTriggerChangeTarget::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2362
//	KeyValue(class CTriggerChangeTarget *const this,
//		KeyValueData *pkvd);  //  2360
}

/* <19ff1f> ../cstrike/dlls/triggers.cpp:2371 */
NOBODY void CTriggerChangeTarget::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a010d> ../cstrike/dlls/triggers.cpp:2376 */
NOBODY void CTriggerChangeTarget::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{ 
//		class CBaseEntity *pTarget;                          //  2378
//		{ 
//			class CBaseMonster *pMonster;                //  2383
//		} 
//	} 
}

/* <1a5235> ../cstrike/dlls/triggers.cpp:2425 */
LINK_ENTITY_TO_CLASS(trigger_camera, CTriggerCamera);

/* <1a08e7> ../cstrike/dlls/triggers.cpp:2445 */
IMPLEMENT_SAVERESTORE(CTriggerCamera, CBaseDelay);

/* <19ff6f> ../cstrike/dlls/triggers.cpp:2447 */
NOBODY void CTriggerCamera::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a1537> ../cstrike/dlls/triggers.cpp:2462 */
NOBODY void CTriggerCamera::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2464
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2469
//	KeyValue(CTriggerCamera *const this,
//		KeyValueData *pkvd);  //  2462
//	atof(const char *__nptr);  //  2466
}

/* <1a55e4> ../cstrike/dlls/triggers.cpp:2490 */
NOBODY void CTriggerCamera::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CTriggerCamera *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  2490
}

/* <1a5494> ../cstrike/dlls/triggers.cpp:2587 */
NOBODY void CTriggerCamera::FollowTarget(void)
{
//	{ 
//		class Vector vecGoal;                                 //  2606
//		float dx;                                             //  2615
//		float dy;                                             //  2616
//	} 
//	FollowTarget(CTriggerCamera *const this);  //  2587
}

/* <1a5311> ../cstrike/dlls/triggers.cpp:2644 */
NOBODY void CTriggerCamera::Move(void)
{
//	{
//		float fraction;                                       //  2688
//		{
//			class Vector delta;                           //  2676
//			operator-(const class Vector *const this,
//					const class Vector  &const v);  //  2676
//			Length(const class Vector *const this);  //  2677
//			Normalize(const class Vector *const this);  //  2678
//		} 
//		operator*(const class Vector *const this,
//				float fl);  //  2689
//		operator*(const class Vector *const this,
//				float fl);  //  2689
//		operator*(const class Vector *const this,
//				float fl);  //  2689
//		operator+(const class Vector *const this,
//				const class Vector  &const v);  //  2689
//	} 
}

/* <1a5815> ../cstrike/dlls/triggers.cpp:2699 */
LINK_ENTITY_TO_CLASS(env_snow, CWeather);

/* <1a58f1> ../cstrike/dlls/triggers.cpp:2700 */
LINK_ENTITY_TO_CLASS(func_snow, CWeather);

/* <1a59cd> ../cstrike/dlls/triggers.cpp:2701 */
LINK_ENTITY_TO_CLASS(env_rain, CWeather);

/* <1a5aa9> ../cstrike/dlls/triggers.cpp:2702 */
LINK_ENTITY_TO_CLASS(func_rain, CWeather);

/* <1a1477> ../cstrike/dlls/triggers.cpp:2716 */
NOBODY void CClientFog::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2718
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //  2730
//	KeyValue(CClientFog *const this,
//		KeyValueData *pkvd);  //  2716
}

/* <19ff97> ../cstrike/dlls/triggers.cpp:2735 */
NOBODY void CClientFog::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1a5ba9> ../cstrike/dlls/triggers.cpp:2744 */
LINK_ENTITY_TO_CLASS(env_fog, CClientFog);

#ifdef HOOK_GAMEDLL

void CFrictionModifier::Spawn(void)
{
	Spawn_();
}

void CFrictionModifier::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFrictionModifier::Save(CSave &save)
{
	return Save_(save);
}

int CFrictionModifier::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CAutoTrigger::Spawn(void)
{
	Spawn_();
}

void CAutoTrigger::Precache(void)
{
	Precache_();
}

void CAutoTrigger::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CAutoTrigger::Save(CSave &save)
{
	return Save_(save);
}

int CAutoTrigger::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CAutoTrigger::Think(void)
{
	Think_();
}

void CTriggerRelay::Spawn(void)
{
	Spawn_();
}

void CTriggerRelay::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CTriggerRelay::Save(CSave &save)
{
	return Save_(save);
}

int CTriggerRelay::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CTriggerRelay::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CMultiManager::Spawn(void)
{
	Spawn_();
}

void CMultiManager::Restart(void)
{
	Restart_();
}

void CMultiManager::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CMultiManager::Save(CSave &save)
{
	return Save_(save);
}

int CMultiManager::Restore(CRestore &restore)
{
	return Restore_(restore);
}

BOOL CMultiManager::HasTarget(string_t targetname)
{
	return HasTarget_(targetname);
}

void CRenderFxManager::Spawn(void)
{
	Spawn_();
}

void CRenderFxManager::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBaseTrigger::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerHurt::Spawn(void)
{
	Spawn_();
}

void CTriggerMonsterJump::Spawn(void)
{
	Spawn_();
}

void CTriggerMonsterJump::Think(void)
{
	Think_();
}

void CTriggerMonsterJump::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CTriggerCDAudio::Spawn(void)
{
	Spawn_();
}

void CTriggerCDAudio::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CTriggerCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CTargetCDAudio::Spawn(void)
{
	Spawn_();
}

void CTargetCDAudio::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTargetCDAudio::Think(void)
{
	Think_();
}

void CTargetCDAudio::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CTriggerMultiple::Spawn(void)
{
	Spawn_();
}

void CTriggerOnce::Spawn(void)
{
	Spawn_();
}

void CTriggerCounter::Spawn(void)
{
	Spawn_();
}

void CTriggerVolume::Spawn(void)
{
	Spawn_();
}

void CFireAndDie::Spawn(void)
{
	Spawn_();
}

void CFireAndDie::Precache(void)
{
	Precache_();
}

void CFireAndDie::Think(void)
{
	Think_();
}

void CChangeLevel::Spawn(void)
{
	Spawn_();
}

void CChangeLevel::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CChangeLevel::Save(CSave &save)
{
	return Save_(save);
}

int CChangeLevel::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CLadder::Spawn(void)
{
	Spawn_();
}

void CLadder::Precache(void)
{
	Precache_();
}

void CLadder::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerPush::Spawn(void)
{
	Spawn_();
}

void CTriggerPush::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerPush::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CTriggerTeleport::Spawn(void)
{
	Spawn_();
}

void CBuyZone::Spawn(void)
{
	Spawn_();
}

void CBombTarget::Spawn(void)
{
	Spawn_();
}

void CHostageRescue::Spawn(void)
{
	Spawn_();
}

void CEscapeZone::Spawn(void)
{
	Spawn_();
}

void CVIP_SafetyZone::Spawn(void)
{
	Spawn_();
}

void CTriggerSave::Spawn(void)
{
	Spawn_();
}

void CTriggerEndSection::Spawn(void)
{
	Spawn_();
}

void CTriggerEndSection::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CTriggerGravity::Spawn(void)
{
	Spawn_();
}

void CTriggerChangeTarget::Spawn(void)
{
	Spawn_();
}
void CTriggerChangeTarget::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CTriggerChangeTarget::Save(CSave &save)
{
	return Save_(save);
}

int CTriggerChangeTarget::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CTriggerChangeTarget::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CTriggerCamera::Spawn(void)
{
	Spawn_();
}
void CTriggerCamera::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CTriggerCamera::Save(CSave &save)
{
	return Save_(save);
}

int CTriggerCamera::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CTriggerCamera::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CClientFog::Spawn(void)
{
	Spawn_();
}
void CClientFog::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

#endif // HOOK_GAMEDLL
