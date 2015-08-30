#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBubbling::m_SaveData[] =
{
	DEFINE_FIELD(CBubbling, m_density, FIELD_INTEGER),
	DEFINE_FIELD(CBubbling, m_frequency, FIELD_INTEGER),
	DEFINE_FIELD(CBubbling, m_state, FIELD_INTEGER),
};

TYPEDESCRIPTION CLightning::m_SaveData[] =
{
	DEFINE_FIELD(CLightning, m_active, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_iszStartEntity, FIELD_STRING),
	DEFINE_FIELD(CLightning, m_iszEndEntity, FIELD_STRING),
	DEFINE_FIELD(CLightning, m_life, FIELD_FLOAT),
	DEFINE_FIELD(CLightning, m_boltWidth, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_noiseAmplitude, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_brightness, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_speed, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_restrike, FIELD_FLOAT),
	DEFINE_FIELD(CLightning, m_spriteTexture, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_iszSpriteName, FIELD_STRING),
	DEFINE_FIELD(CLightning, m_frameStart, FIELD_INTEGER),
	DEFINE_FIELD(CLightning, m_radius, FIELD_FLOAT),
};

TYPEDESCRIPTION CLaser::m_SaveData[] =
{
	DEFINE_FIELD(CLaser, m_pSprite, FIELD_CLASSPTR),
	DEFINE_FIELD(CLaser, m_iszSpriteName, FIELD_STRING),
	DEFINE_FIELD(CLaser, m_firePosition, FIELD_POSITION_VECTOR),
};

TYPEDESCRIPTION CGlow::m_SaveData[] =
{
	DEFINE_FIELD(CGlow, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CGlow, m_maxFrame, FIELD_FLOAT),
};

TYPEDESCRIPTION CSprite::m_SaveData[] =
{
	DEFINE_FIELD(CSprite, m_lastTime, FIELD_TIME),
	DEFINE_FIELD(CSprite, m_maxFrame, FIELD_FLOAT),
};

TYPEDESCRIPTION CGibShooter::m_SaveData[] =
{
	DEFINE_FIELD(CGibShooter, m_iGibs, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_iGibCapacity, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_iGibMaterial, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_iGibModelIndex, FIELD_INTEGER),
	DEFINE_FIELD(CGibShooter, m_flGibVelocity, FIELD_FLOAT),
	DEFINE_FIELD(CGibShooter, m_flVariance, FIELD_FLOAT),
	DEFINE_FIELD(CGibShooter, m_flGibLife, FIELD_FLOAT),
};

#else

TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CBubbling, m_SaveData)[3];
TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CLightning, m_SaveData)[13];
TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CLaser, m_SaveData)[3];
TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CGlow, m_SaveData)[2];
TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CSprite, m_SaveData)[2];
TYPEDESCRIPTION IMPLEMENT_ARRAY_CLASS(CGibShooter, m_SaveData)[7];

#endif // HOOK_GAMEDLL

/* <76042> ../cstrike/dlls/effects.cpp:33 */
LINK_ENTITY_TO_CLASS(info_target, CPointEntity);

/* <7610e> ../cstrike/dlls/effects.cpp:57 */
LINK_ENTITY_TO_CLASS(env_bubbles, CBubbling);

/* <741e0> ../cstrike/dlls/effects.cpp:68 */
IMPLEMENT_SAVERESTORE(CBubbling, CBaseEntity);

/* <7344d> ../cstrike/dlls/effects.cpp:73 */
void CBubbling::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	SET_MODEL(ENT(pev), STRING(pev->model));	// Set size

	// Remove model & collisions
	pev->solid = SOLID_NOT;

	// The engine won't draw this model if this is set to 0 and blending is on
	pev->renderamt = 0;
	pev->rendermode = kRenderTransTexture;

	int speed = (pev->speed > 0) ? pev->speed : -pev->speed;

	// HACKHACK!!! - Speed in rendercolor
	pev->rendercolor.x = (speed >> 8);
	pev->rendercolor.y = (speed & 255);
	pev->rendercolor.z = (pev->speed < 0) ? 1 : 0;

	if (!(pev->spawnflags & SF_BUBBLES_STARTOFF))
	{
		SetThink(&CBubbling::FizzThink);

		pev->nextthink = gpGlobals->time + 2.0;
		m_state = 1;
	}
	else
		m_state = 0;
}

/* <73489> ../cstrike/dlls/effects.cpp:99 */
void CBubbling::__MAKE_VHOOK(Precache)(void)
{
	// Precache bubble sprite
	m_bubbleModel = PRECACHE_MODEL("sprites/bubble.spr");
}

/* <742a4> ../cstrike/dlls/effects.cpp:105 */
void CBubbling::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (ShouldToggle(useType, m_state))
		m_state = !m_state;

	if (m_state)
	{
		SetThink(&CBubbling::FizzThink);
		pev->nextthink = gpGlobals->time + 0.1;
	}
	else
	{
		SetThink(NULL);
		pev->nextthink = 0;
	}
}

/* <74aae> ../cstrike/dlls/effects.cpp:123 */
void CBubbling::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "density"))
	{
		m_density = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "frequency"))
	{
		m_frequency = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "current"))
	{
		pev->speed = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

/* <73d03> ../cstrike/dlls/effects.cpp:145 */
void CBubbling::FizzThink(void)
{
	MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, VecBModelOrigin(pev));
		WRITE_BYTE(TE_FIZZ);
		WRITE_SHORT(ENTINDEX(edict()));
		WRITE_SHORT(m_bubbleModel);
		WRITE_BYTE(m_density);
	MESSAGE_END();

	if (m_frequency > 19)
		pev->nextthink = gpGlobals->time + 0.5;
	else
		pev->nextthink = gpGlobals->time + 2.5 - (0.1 * m_frequency);
}

/* <7620c> ../cstrike/dlls/effects.cpp:166 */
LINK_ENTITY_TO_CLASS(beam, CBeam);

/* <734b0> ../cstrike/dlls/effects.cpp:168 */
void CBeam::__MAKE_VHOOK(Spawn)(void)
{
	// Remove model & collisions
	pev->solid = SOLID_NOT;
	Precache();
}

/* <734d6> ../cstrike/dlls/effects.cpp:174 */
void CBeam::__MAKE_VHOOK(Precache)(void)
{
	if (pev->owner)
	{
		SetStartEntity(ENTINDEX(pev->owner));
	}
	if (pev->aiment)
	{
		SetEndEntity(ENTINDEX(pev->aiment));
	}
}

/* <762d8> ../cstrike/dlls/effects.cpp:182 */
void CBeam::SetStartEntity(int entityIndex)
{
	pev->sequence = (entityIndex & 0x0FFF) | ((pev->sequence & 0xF000) << 12); 
	pev->owner = INDEXENT(entityIndex);
}

/* <76303> ../cstrike/dlls/effects.cpp:188 */
void CBeam::SetEndEntity(int entityIndex)
{
	pev->skin = (entityIndex & 0x0FFF) | ((pev->skin & 0xF000) << 12); 
	pev->aiment = INDEXENT(entityIndex);
}

/* <7632e> ../cstrike/dlls/effects.cpp:196 */
const Vector &CBeam::GetStartPos(void)
{
	if (GetType() == BEAM_ENTS)
	{
		edict_t *pent = INDEXENT(GetStartEntity());
		return pent->v.origin;
	}

	return pev->origin;
}

/* <7639a> ../cstrike/dlls/effects.cpp:207 */
const Vector &CBeam::GetEndPos(void)
{
	int type = GetType();
	if (type == BEAM_POINTS || type == BEAM_HOSE)
	{
		return pev->angles;
	}

	edict_t *pent = INDEXENT(GetEndEntity());
	if (pent)
	{
		return pent->v.origin;
	}

	return pev->angles;
}

/* <76540> ../cstrike/dlls/effects.cpp:222 */
CBeam *CBeam::BeamCreate(const char *pSpriteName, int width)
{
	// Create a new entity with CBeam private data
	CBeam *pBeam = GetClassPtr((CBeam *)NULL);

	if (pBeam->pev->classname)
		RemoveEntityHashValue(pBeam->pev, STRING(pBeam->pev->classname), CLASSNAME);

	MAKE_STRING_CLASS("beam", pBeam->pev);
	AddEntityHashValue(pBeam->pev, STRING(pBeam->pev->classname), CLASSNAME);

	pBeam->BeamInit(pSpriteName, width);

	return pBeam;
}

/* <76422> ../cstrike/dlls/effects.cpp:234 */
void CBeam::BeamInit(const char *pSpriteName, int width)
{
	pev->flags |= FL_CUSTOMENTITY;

	SetColor(255, 255, 255);
	SetBrightness(255);
	SetNoise(0);
	SetFrame(0);
	SetScrollRate(0);
	pev->model = MAKE_STRING(pSpriteName);
	SetTexture(PRECACHE_MODEL((char *)pSpriteName));
	SetWidth(width);

	pev->skin = 0;
	pev->sequence = 0;
	pev->rendermode = 0;
}

/* <76a56> ../cstrike/dlls/effects.cpp:251 */
void CBeam::PointsInit(const Vector &start, const Vector &end)
{
	SetType(BEAM_POINTS);
	SetStartPos(start);
	SetEndPos(end);
	SetStartAttachment(0);
	SetEndAttachment(0);
	RelinkBeam();
}

/* <7695b> ../cstrike/dlls/effects.cpp:262 */
void CBeam::HoseInit(const Vector &start, const Vector &direction)
{
	SetType(BEAM_HOSE);
	SetStartPos(start);
	SetEndPos(direction);
	SetStartAttachment(0);
	SetEndAttachment(0);
	RelinkBeam();
}

/* <76887> ../cstrike/dlls/effects.cpp:273 */
void CBeam::PointEntInit(const Vector &start, int endIndex)
{
	SetType(BEAM_ENTPOINT);
	SetStartPos(start);
	SetEndEntity(endIndex);
	SetStartAttachment(0);
	SetEndAttachment(0);
	RelinkBeam();
}

/* <767ab> ../cstrike/dlls/effects.cpp:283 */
void CBeam::EntsInit(int startIndex, int endIndex)
{
	SetType(BEAM_ENTS);
	SetStartEntity(startIndex);
	SetEndEntity(endIndex);
	SetStartAttachment(0);
	SetEndAttachment(0);
	RelinkBeam();
}

/* <7663a> ../cstrike/dlls/effects.cpp:294 */
void CBeam::RelinkBeam(void)
{
	const Vector &startPos = GetStartPos();
	const Vector &endPos = GetEndPos();

	pev->mins.x = _min(startPos.x, endPos.x);
	pev->mins.y = _min(startPos.y, endPos.y);
	pev->mins.z = _min(startPos.z, endPos.z);

	pev->maxs.x = _max(startPos.x, endPos.x);
	pev->maxs.y = _max(startPos.y, endPos.y);
	pev->maxs.z = _max(startPos.z, endPos.z);

	pev->mins = pev->mins - pev->origin;
	pev->maxs = pev->maxs - pev->origin;

	UTIL_SetSize(pev, pev->mins, pev->maxs);
	UTIL_SetOrigin(pev, pev->origin);
}

/* <77305> ../cstrike/dlls/effects.cpp:311 */
void CBeam::TriggerTouch(CBaseEntity *pOther)
{
	if (pOther->pev->flags & (FL_CLIENT | FL_MONSTER))
	{
		if (pev->owner)
		{
			CBaseEntity *pOwner = CBaseEntity::Instance(pev->owner);
			pOwner->Use(pOther, this, USE_TOGGLE, 0);
		}
		ALERT(at_console, "Firing targets!!!\n");
	}
}

/* <773e2> ../cstrike/dlls/effects.cpp:325 */
CBaseEntity *CBeam::RandomTargetname(const char *szName)
{
	int total = 0;

	CBaseEntity *pEntity = NULL;
	CBaseEntity *pNewEntity = NULL;

	while ((pNewEntity = UTIL_FindEntityByTargetname(pNewEntity, szName)) != NULL)
	{
		total++;

		if (RANDOM_LONG(0, total - 1) < 1)
			pEntity = pNewEntity;
	}

	return pEntity;
}

/* <77431> ../cstrike/dlls/effects.cpp:341 */
void CBeam::DoSparks(const Vector &start, const Vector &end)
{
	if (pev->spawnflags & (SF_BEAM_SPARKSTART | SF_BEAM_SPARKEND))
	{
		if (pev->spawnflags & SF_BEAM_SPARKSTART)
		{
			UTIL_Sparks(start);
		}
		if (pev->spawnflags & SF_BEAM_SPARKEND)
		{
			UTIL_Sparks(end);
		}
	}
}

/* <774c2> ../cstrike/dlls/effects.cpp:402 */
LINK_ENTITY_TO_CLASS(env_lightning, CLightning);

/* <77592> ../cstrike/dlls/effects.cpp:403 */
LINK_ENTITY_TO_CLASS(env_beam, CLightning);

/* <74192> ../cstrike/dlls/effects.cpp:441 */
IMPLEMENT_SAVERESTORE(CLightning, CBeam);

/* <744b2> ../cstrike/dlls/effects.cpp:444 */
void CLightning::__MAKE_VHOOK(Spawn)(void)
{
	if (FStringNull(m_iszSpriteName))
	{
		SetThink(&CLightning::SUB_Remove);
		return;
	}

	// Remove model & collisions
	pev->solid = SOLID_NOT;
	Precache();

	pev->dmgtime = gpGlobals->time;

	if (ServerSide())
	{
		SetThink(NULL);
		if (pev->dmg > 0)
		{
			SetThink(&CLightning::DamageThink);
			pev->nextthink = gpGlobals->time + 0.1f;
		}
		if (pev->targetname)
		{
			if (!(pev->spawnflags & SF_BEAM_STARTON))
			{
				pev->effects = EF_NODRAW;
				m_active = 0;
				pev->nextthink = 0;
			}
			else
				m_active = 1;

			SetUse(&CLightning::ToggleUse);
		}
	}
	else
	{
		m_active = 0;
		if (!FStringNull(pev->targetname))
		{
			SetUse(&CLightning::StrikeUse);
		}
		if (FStringNull(pev->targetname) || (pev->spawnflags & SF_BEAM_STARTON))
		{
			SetThink(&CLightning::StrikeThink);
			pev->nextthink = gpGlobals->time + 1.0f;
		}
	}
}

/* <7357f> ../cstrike/dlls/effects.cpp:493 */
void CLightning::__MAKE_VHOOK(Precache)(void)
{
	m_spriteTexture = PRECACHE_MODEL((char *)STRING(m_iszSpriteName));
	CBeam::Precache();
}

/* <786a1> ../cstrike/dlls/effects.cpp:500 */
void CLightning::__MAKE_VHOOK(Activate)(void)
{
	if (ServerSide())
		BeamUpdateVars();
}

/* <7536c> ../cstrike/dlls/effects.cpp:507 */
void CLightning::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "LightningStart"))
	{
		m_iszStartEntity = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "LightningEnd"))
	{
		m_iszEndEntity = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "life"))
	{
		m_life = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "BoltWidth"))
	{
		m_boltWidth = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "NoiseAmplitude"))
	{
		m_noiseAmplitude = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "TextureScroll"))
	{
		m_speed = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "StrikeTime"))
	{
		m_restrike = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "texture"))
	{
		m_iszSpriteName = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "framestart"))
	{
		m_frameStart = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "Radius"))
	{
		m_radius = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "damage"))
	{
		pev->dmg = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBeam::KeyValue(pkvd);
}

/* <75ad3> ../cstrike/dlls/effects.cpp:569 */
void CLightning::ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!ShouldToggle(useType, m_active))
		return;

	if (m_active)
	{
		m_active = 0;
		pev->effects |= EF_NODRAW;
		pev->nextthink = 0;
	}
	else
	{
		m_active = 1;
		pev->effects &= ~EF_NODRAW;
		DoSparks(GetStartPos(), GetEndPos());

		if (pev->dmg > 0)
		{
			pev->nextthink = gpGlobals->time;
			pev->dmgtime = gpGlobals->time;
		}
	}
}

/* <7422d> ../cstrike/dlls/effects.cpp:593 */
void CLightning::StrikeUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!ShouldToggle(useType, m_active))
		return;

	if (m_active)
	{
		m_active = 0;
		SetThink(NULL);
	}
	else
	{
		SetThink(&CLightning::StrikeThink);
		pev->nextthink = gpGlobals->time + 0.1f;
	}

	if (!(pev->spawnflags & SF_BEAM_TOGGLE))
		SetUse(NULL);
}

/* <71e66> ../cstrike/dlls/effects.cpp:614 */
int IsPointEntity(CBaseEntity *pEnt)
{
	if (!pEnt->pev->modelindex)
		return 1;

	if (FClassnameIs(pEnt->pev, "info_target") || FClassnameIs(pEnt->pev, "info_landmark") || FClassnameIs(pEnt->pev, "path_corner"))
	{
		return 1;
	}
	return 0;
}

/* <77f64> ../cstrike/dlls/effects.cpp:625 */
void CLightning::StrikeThink(void)
{
	if (m_life != 0.0f)
	{
		if (pev->spawnflags & SF_BEAM_RANDOM)
			pev->nextthink = gpGlobals->time + m_life + RANDOM_FLOAT(0, m_restrike);
		else
			pev->nextthink = gpGlobals->time + m_life + m_restrike;
	}
	m_active = 1;

	if (FStringNull(m_iszEndEntity))
	{
		if (FStringNull(m_iszStartEntity))
		{
			RandomArea();
		}
		else
		{
			CBaseEntity *pStart = RandomTargetname(STRING(m_iszStartEntity));
			if (pStart != NULL)
				RandomPoint(pStart->pev->origin);
			else
				ALERT(at_console, "env_beam: unknown entity \"%s\"\n", STRING(m_iszStartEntity));
		}
		return;
	}

	CBaseEntity *pStart = RandomTargetname(STRING(m_iszStartEntity));
	CBaseEntity *pEnd = RandomTargetname(STRING(m_iszEndEntity));

	if (pStart != NULL && pEnd != NULL)
	{
		if (IsPointEntity(pStart) || IsPointEntity(pEnd))
		{
			if (pev->spawnflags & SF_BEAM_RING)
			{
				// don't work
				return;
			}
		}

		MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);

		if (IsPointEntity(pStart) || IsPointEntity(pEnd))
		{
			// One point entity must be in pEnd
			if (!IsPointEntity(pEnd))
			{
				CBaseEntity *pTemp;
				pTemp = pStart;
				pStart = pEnd;
				pEnd = pTemp;
			}

			// One sided
			if (!IsPointEntity(pStart))
			{
				WRITE_BYTE(TE_BEAMENTPOINT);
				WRITE_SHORT(pStart->entindex());
				WRITE_COORD(pEnd->pev->origin.x);
				WRITE_COORD(pEnd->pev->origin.y);
				WRITE_COORD(pEnd->pev->origin.z);
			}
			else
			{
				WRITE_BYTE(TE_BEAMPOINTS);
				WRITE_COORD(pStart->pev->origin.x);
				WRITE_COORD(pStart->pev->origin.y);
				WRITE_COORD(pStart->pev->origin.z);
				WRITE_COORD(pEnd->pev->origin.x);
				WRITE_COORD(pEnd->pev->origin.y);
				WRITE_COORD(pEnd->pev->origin.z);
			}


		}
		else
		{
			if (pev->spawnflags & SF_BEAM_RING)
				WRITE_BYTE(TE_BEAMRING);
			else
				WRITE_BYTE(TE_BEAMENTS);
			WRITE_SHORT(pStart->entindex());
			WRITE_SHORT(pEnd->entindex());
		}

		WRITE_SHORT(m_spriteTexture);
		WRITE_BYTE(m_frameStart);	// framestart
		WRITE_BYTE((int)pev->framerate);	// framerate
		WRITE_BYTE((int)(m_life*10.0));	// life
		WRITE_BYTE(m_boltWidth);	// width
		WRITE_BYTE(m_noiseAmplitude);	// noise
		WRITE_BYTE((int)pev->rendercolor.x);	// r, g, b
		WRITE_BYTE((int)pev->rendercolor.y);	// r, g, b
		WRITE_BYTE((int)pev->rendercolor.z);	// r, g, b
		WRITE_BYTE(pev->renderamt);	// brightness
		WRITE_BYTE(m_speed);		// speed
		MESSAGE_END();

		DoSparks(pStart->pev->origin, pEnd->pev->origin);

		if (pev->dmg > 0)
		{
			TraceResult tr;
			UTIL_TraceLine(pStart->pev->origin, pEnd->pev->origin, dont_ignore_monsters, NULL, &tr);
			BeamDamageInstant(&tr, pev->dmg);
		}
	}
}

/* <77680> ../cstrike/dlls/effects.cpp:731 */
void CBeam::BeamDamage(TraceResult *ptr)
{
	RelinkBeam();

	if (ptr->flFraction != 1.0f && ptr->pHit != NULL)
	{
		CBaseEntity *pHit = CBaseEntity::Instance(ptr->pHit);

		if (pHit != NULL)
		{
			ClearMultiDamage();
			pHit->TraceAttack(pev, pev->dmg * (gpGlobals->time - pev->dmgtime), (ptr->vecEndPos - pev->origin).Normalize(), ptr, DMG_ENERGYBEAM);
			ApplyMultiDamage(pev, pev);

			if (pev->spawnflags & SF_BEAM_DECALS)
			{
				if (pHit->IsBSPModel())
				{
					UTIL_DecalTrace(ptr, DECAL_BIGSHOT1 + RANDOM_LONG(0, 4));
				}
			}
		}
	}

	pev->dmgtime = gpGlobals->time;
}

/* <777dd> ../cstrike/dlls/effects.cpp:753 */
void CLightning::DamageThink(void)
{
	pev->nextthink = gpGlobals->time + 0.1;

	TraceResult tr;
	UTIL_TraceLine(GetStartPos(), GetEndPos(), dont_ignore_monsters, NULL, &tr);
	BeamDamage(&tr);
}

/* <77a90> ../cstrike/dlls/effects.cpp:763 */
void CLightning::Zap(const Vector &vecSrc, const Vector &vecDest)
{
	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_BEAMPOINTS);
		WRITE_COORD(vecSrc.x);
		WRITE_COORD(vecSrc.y);
		WRITE_COORD(vecSrc.z);
		WRITE_COORD(vecDest.x);
		WRITE_COORD(vecDest.y);
		WRITE_COORD(vecDest.z);
		WRITE_SHORT(m_spriteTexture);
		WRITE_BYTE(m_frameStart);		// framestart
		WRITE_BYTE((int)pev->framerate);	// framerate
		WRITE_BYTE((int)(m_life * 10.0));	// life
		WRITE_BYTE(m_boltWidth);		// width
		WRITE_BYTE(m_noiseAmplitude);		// noise
		WRITE_BYTE((int)pev->rendercolor.x);	// r, g, b
		WRITE_BYTE((int)pev->rendercolor.y);	// r, g, b
		WRITE_BYTE((int)pev->rendercolor.z);	// r, g, b
		WRITE_BYTE((int)pev->renderamt);	// brightness
		WRITE_BYTE(m_speed);		// speed
	MESSAGE_END();

	DoSparks(vecSrc, vecDest);
}

/* <77b45> ../cstrike/dlls/effects.cpp:789 */
void CLightning::RandomArea(void)
{
	for (int iLoops = 0; iLoops < 10; iLoops++)
	{
		Vector vecSrc = pev->origin;
		Vector vecDir1 = Vector(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1));
		vecDir1 = vecDir1.Normalize();

		TraceResult tr1;
		UTIL_TraceLine(vecSrc, vecSrc + vecDir1 * m_radius, ignore_monsters, ENT(pev), &tr1);

		if (tr1.flFraction == 1.0f)
			continue;

		Vector vecDir2;
		do
		{
			vecDir2 = Vector(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1));
		}
		while (DotProduct(vecDir1, vecDir2) > 0);

		vecDir2 = vecDir2.Normalize();

		TraceResult tr2;
		UTIL_TraceLine(vecSrc, vecSrc + vecDir2 * m_radius, ignore_monsters, ENT(pev), &tr2);

		if (tr2.flFraction == 1.0f)
			continue;

		if ((tr1.vecEndPos - tr2.vecEndPos).Length() < m_radius * 0.1f)
			continue;

		UTIL_TraceLine(tr1.vecEndPos, tr2.vecEndPos, ignore_monsters, ENT(pev), &tr2);

		if (tr2.flFraction != 1.0f)
			continue;

		Zap(tr1.vecEndPos, tr2.vecEndPos);
		break;
	}
}

/* <77de8> ../cstrike/dlls/effects.cpp:831 */
void CLightning::RandomPoint(Vector &vecSrc)
{
	int iLoops = 0;

	for (iLoops = 0; iLoops < 10; iLoops++)
	{
		Vector vecDir1 = Vector(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1));
		vecDir1 = vecDir1.Normalize();

		TraceResult tr1;
		UTIL_TraceLine(vecSrc, vecSrc + vecDir1 * m_radius, ignore_monsters, ENT(pev), &tr1);

		if ((tr1.vecEndPos - vecSrc).Length() < m_radius * 0.1f)
			continue;

		if (tr1.flFraction == 1.0f)
			continue;

		Zap(vecSrc, tr1.vecEndPos);
		break;
	}
}

/* <78313> ../cstrike/dlls/effects.cpp:855 */
void CLightning::BeamUpdateVars(void)
{
	int beamType;
	int pointStart, pointEnd;

	edict_t *pStart = FIND_ENTITY_BY_TARGETNAME(NULL, STRING(m_iszStartEntity));
	edict_t *pEnd = FIND_ENTITY_BY_TARGETNAME(NULL, STRING(m_iszEndEntity));

	pointStart = IsPointEntity(CBaseEntity::Instance(pStart));
	pointEnd = IsPointEntity(CBaseEntity::Instance(pEnd));

	pev->skin = 0;
	pev->sequence = 0;
	pev->rendermode = 0;
	pev->flags |= FL_CUSTOMENTITY;
	pev->model = m_iszSpriteName;
	SetTexture(m_spriteTexture);

	beamType = BEAM_ENTS;
	if (pointStart || pointEnd)
	{
		// One point entity must be in pStart
		if (!pointStart)
		{
			edict_t *pTemp;
			// Swap start & end
			pTemp = pStart;
			pStart = pEnd;
			pEnd = pTemp;

			int swap = pointStart;
			pointStart = pointEnd;
			pointEnd = swap;
		}
		if (!pointEnd)
			beamType = BEAM_ENTPOINT;
		else
			beamType = BEAM_POINTS;
	}

	SetType(beamType);
	if (beamType == BEAM_POINTS || beamType == BEAM_ENTPOINT || beamType == BEAM_HOSE)
	{
		SetStartPos(pStart->v.origin);

		if (beamType == BEAM_POINTS || beamType == BEAM_HOSE)
			SetEndPos(pEnd->v.origin);
		else
			SetEndEntity(ENTINDEX(pEnd));
	}
	else
	{
		SetStartEntity(ENTINDEX(pStart));
		SetEndEntity(ENTINDEX(pEnd));
	}

	RelinkBeam();

	SetWidth(m_boltWidth);
	SetNoise(m_noiseAmplitude);
	SetFrame(m_frameStart);
	SetScrollRate(m_speed);

	if (pev->spawnflags & SF_BEAM_SHADEIN)
	{
		SetFlags(BEAM_FSHADEIN);
	}
	else if (pev->spawnflags & SF_BEAM_SHADEOUT)
	{
		SetFlags(BEAM_FSHADEOUT);
	}
}

/* <786d8> ../cstrike/dlls/effects.cpp:920 */
LINK_ENTITY_TO_CLASS(env_laser, CLaser);

/* <74144> ../cstrike/dlls/effects.cpp:929 */
IMPLEMENT_SAVERESTORE(CLaser, CBeam);

/* <76b3f> ../cstrike/dlls/effects.cpp:931 */
void CLaser::__MAKE_VHOOK(Spawn)(void)
{
	if (FStringNull(pev->model))
	{
		SetThink(&CLaser::SUB_Remove);
		return;
	}

	// Remove model & collisions
	pev->solid = SOLID_NOT;
	Precache();

	SetThink(&CLaser::StrikeThink);
	pev->flags |= FL_CUSTOMENTITY;

	PointsInit(pev->origin, pev->origin);

	if (!m_pSprite && m_iszSpriteName)
		m_pSprite = CSprite::SpriteCreate(STRING(m_iszSpriteName), pev->origin, TRUE);
	else
		m_pSprite = NULL;

	if (m_pSprite)
		m_pSprite->SetTransparency(kRenderGlow, pev->rendercolor.x, pev->rendercolor.y, pev->rendercolor.z, pev->renderamt, pev->renderfx);

	if (pev->targetname && !(pev->spawnflags & SF_BEAM_STARTON))
		TurnOff();
	else
		TurnOn();
}

/* <73d82> ../cstrike/dlls/effects.cpp:960 */
void CLaser::__MAKE_VHOOK(Precache)(void)
{
	pev->modelindex = PRECACHE_MODEL((char *)STRING(pev->model));

	if (m_iszSpriteName)
	{
		PRECACHE_MODEL((char *)STRING(m_iszSpriteName));
	}
}

/* <74ff2> ../cstrike/dlls/effects.cpp:968 */
void CLaser::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "LaserTarget"))
	{
		pev->message = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "width"))
	{
		SetWidth(Q_atoi(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "NoiseAmplitude"))
	{
		SetNoise(Q_atoi(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "TextureScroll"))
	{
		SetScrollRate(Q_atoi(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "texture"))
	{
		pev->model = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "EndSprite"))
	{
		m_iszSpriteName = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "framestart"))
	{
		pev->frame = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "damage"))
	{
		pev->dmg = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBeam::KeyValue(pkvd);
}

/* <787a8> ../cstrike/dlls/effects.cpp:1015 */
int CLaser::IsOn(void)
{
	if (pev->effects & EF_NODRAW)
		return 0;

	return 1;
}

/* <787c9> ../cstrike/dlls/effects.cpp:1023 */
void CLaser::TurnOff(void)
{
	pev->effects |= EF_NODRAW;
	pev->nextthink = 0;

	if (m_pSprite)
		m_pSprite->TurnOff();
}

/* <78804> ../cstrike/dlls/effects.cpp:1032 */
void CLaser::TurnOn(void)
{
	pev->effects &= ~EF_NODRAW;

	if (m_pSprite)
		m_pSprite->TurnOn();

	pev->dmgtime = gpGlobals->time;
	pev->nextthink = gpGlobals->time;
}

/* <75f0a> ../cstrike/dlls/effects.cpp:1042 */
void CLaser::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	int active = IsOn();

	if (!ShouldToggle(useType, active))
		return;

	if (active)
		TurnOff();
	else
		TurnOn();
}

/* <78841> ../cstrike/dlls/effects.cpp:1059 */
void CLaser::FireAtPoint(TraceResult &tr)
{
	SetEndPos(tr.vecEndPos);

	if (m_pSprite)
		UTIL_SetOrigin(m_pSprite->pev, tr.vecEndPos);

	BeamDamage(&tr);
	DoSparks(GetStartPos(), tr.vecEndPos);
}

/* <778f6> ../cstrike/dlls/effects.cpp:1069 */
void CLaser::StrikeThink(void)
{
	CBaseEntity *pEnd = RandomTargetname(STRING(pev->message));

	if (pEnd)
		m_firePosition = pEnd->pev->origin;

	TraceResult tr;
	UTIL_TraceLine(pev->origin, m_firePosition, dont_ignore_monsters, NULL, &tr);
	FireAtPoint(tr);
	pev->nextthink = gpGlobals->time + 0.1f;
}

/* <7894f> ../cstrike/dlls/effects.cpp:1099 */
LINK_ENTITY_TO_CLASS(env_glow, CGlow);

/* <740f6> ../cstrike/dlls/effects.cpp:1107 */
IMPLEMENT_SAVERESTORE(CGlow, CPointEntity);

/* <735a6> ../cstrike/dlls/effects.cpp:1109 */
void CGlow::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;

	PRECACHE_MODEL((char *)STRING(pev->model));
	SET_MODEL(ENT(pev), STRING(pev->model));

	m_maxFrame = (float)MODEL_FRAMES(pev->modelindex) - 1;

	if (m_maxFrame > 1.0f && pev->framerate != 0.0f)
	{
		pev->nextthink	= gpGlobals->time + 0.1f;
	}

	m_lastTime = gpGlobals->time;
}

/* <74606> ../cstrike/dlls/effects.cpp:1127 */
void CGlow::__MAKE_VHOOK(Think)(void)
{
	Animate(pev->framerate * (gpGlobals->time - m_lastTime));

	pev->nextthink = gpGlobals->time + 0.1f;
	m_lastTime = gpGlobals->time;
}

/* <78a1f> ../cstrike/dlls/effects.cpp:1136 */
void CGlow::Animate(float frames)
{
	if (m_maxFrame > 0)
		pev->frame = fmod((float_precision)(pev->frame + frames), (float_precision)m_maxFrame);
}

/* <78a4a> ../cstrike/dlls/effects.cpp:1157 */
LINK_ENTITY_TO_CLASS(env_bombglow, CBombGlow);

/* <735cd> ../cstrike/dlls/effects.cpp:1161 */
void CBombGlow::__MAKE_VHOOK(Spawn)(void)
{
#ifdef REGAMEDLL_FIXES
	PRECACHE_MODEL("sprites/flare1.spr");
#endif // REGAMEDLLFIXES

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;
	pev->nextthink = gpGlobals->time + 0.05;
	pev->rendermode = kRenderGlow;
	pev->rendercolor.x = 255;
	pev->rendercolor.y = 15;
	pev->rendercolor.z = 15;
	pev->renderamt = 100;
	pev->renderfx = kRenderFxNone;

	m_tmBeepPeriod = 2;
	m_lastTime = gpGlobals->time;
	m_bSetModel = false;
}

/* <73a40> ../cstrike/dlls/effects.cpp:1184 */
void CBombGlow::__MAKE_VHOOK(Think)(void)
{
	if (!m_bSetModel)
	{
		m_bSetModel = true;

		PRECACHE_MODEL("sprites/flare1.spr");
		SET_MODEL(ENT(pev), "sprites/flare1.spr");
	}

	pev->effects |= EF_NODRAW;

	if (gpGlobals->time > m_lastTime + m_tmBeepPeriod)
	{
		m_tmBeepPeriod *= 0.95f;
		m_lastTime = gpGlobals->time;

		if (m_tmBeepPeriod < 0.1f)
			m_tmBeepPeriod = 0.1f;

		pev->effects = 0;
		EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/c4_beep1.wav", VOL_NORM, 1.0);
	}

	pev->nextthink = gpGlobals->time + 0.05f;
}

/* <78b1a> ../cstrike/dlls/effects.cpp:1226 */
LINK_ENTITY_TO_CLASS(env_sprite, CSprite);

/* <740a8> ../cstrike/dlls/effects.cpp:1234 */
IMPLEMENT_SAVERESTORE(CSprite, CPointEntity);

/* <75dc8> ../cstrike/dlls/effects.cpp:1236 */
void CSprite::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;

	Precache();
	SET_MODEL(ENT(pev), STRING(pev->model));
	m_maxFrame = (float)MODEL_FRAMES(pev->modelindex) - 1;

	if (pev->targetname && !(pev->spawnflags & SF_SPRITE_STARTON))
		TurnOff();
	else
		TurnOn();

	// Worldcraft only sets y rotation, copy to Z
	if (pev->angles.y != 0.0f && pev->angles.z == 0.0f)
	{
		pev->angles.z = pev->angles.y;
		pev->angles.y = 0;
	}
}

/* <75d55> ../cstrike/dlls/effects.cpp:1260 */
void CSprite::__MAKE_VHOOK(Restart)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;

	if (pev->targetname && !(pev->spawnflags & SF_SPRITE_STARTON))
		TurnOff();
	else
		TurnOn();
}

/* <74436> ../cstrike/dlls/effects.cpp:1273 */
void CSprite::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL((char *)STRING(pev->model));

	if (pev->aiment)
	{
		SetAttachment(pev->aiment, pev->body);
	}
	else
	{
		pev->skin = 0;
		pev->body = 0;
	}
}

/* <78bea> ../cstrike/dlls/effects.cpp:1289 */
void CSprite::SpriteInit(const char *pSpriteName, const Vector &origin)
{
	pev->model = MAKE_STRING(pSpriteName);
	pev->origin = origin;
	Spawn();
}

/* <78c1d> ../cstrike/dlls/effects.cpp:1296 */
CSprite *CSprite::SpriteCreate(const char *pSpriteName, const Vector &origin, BOOL animate)
{
	CSprite *pSprite = GetClassPtr((CSprite *)NULL);
	pSprite->SpriteInit(pSpriteName, origin);

	if (pSprite->pev->classname)
		RemoveEntityHashValue(pSprite->pev, STRING(pSprite->pev->classname), CLASSNAME);

	MAKE_STRING_CLASS("env_sprite", pSprite->pev);
	AddEntityHashValue(pSprite->pev, STRING(pSprite->pev->classname), CLASSNAME);

	pSprite->pev->solid = SOLID_NOT;
	pSprite->pev->movetype = MOVETYPE_NOCLIP;

	if (animate)
	{
		pSprite->TurnOn();
	}

	return pSprite;
}

/* <75679> ../cstrike/dlls/effects.cpp:1310 */
void CSprite::AnimateThink(void)
{
	Animate(pev->framerate * (gpGlobals->time - m_lastTime));
	pev->nextthink = gpGlobals->time + 0.1;
	m_lastTime = gpGlobals->time;
}

/* <78d6b> ../cstrike/dlls/effects.cpp:1318 */
void CSprite::AnimateUntilDead(void)
{
	if (gpGlobals->time > pev->dmgtime)
	{
		UTIL_Remove(this);
	}
	else
	{
		AnimateThink();
		pev->nextthink = gpGlobals->time;
	}
}

/* <78de9> ../cstrike/dlls/effects.cpp:1329 */
NOXREF void CSprite::Expand(float scaleSpeed, float fadeSpeed)
{
	pev->speed = scaleSpeed;
	pev->health = fadeSpeed;
	SetThink(&CSprite::ExpandThink);

	pev->nextthink = gpGlobals->time;
	m_lastTime = gpGlobals->time;
}

/* <73e2e> ../cstrike/dlls/effects.cpp:1340 */
void CSprite::ExpandThink(void)
{
	float frametime = gpGlobals->time - m_lastTime;

	pev->scale += pev->speed * frametime;
	pev->renderamt -= pev->health * frametime;

	if (pev->renderamt <= 0)
	{
		pev->renderamt = 0;
		UTIL_Remove(this);
	}
	else
	{
		pev->nextthink = gpGlobals->time + 0.1f;
		m_lastTime = gpGlobals->time;
	}
}

/* <78e2e> ../cstrike/dlls/effects.cpp:1358 */
void CSprite::Animate(float frames)
{
	pev->frame += frames;

	if (pev->frame > m_maxFrame)
	{
		if (pev->spawnflags & SF_SPRITE_ONCE)
			TurnOff();

		else if (m_maxFrame > 0)
			pev->frame = fmod((float_precision)pev->frame, (float_precision)m_maxFrame);
	}
}

/* <78e73> ../cstrike/dlls/effects.cpp:1376 */
void CSprite::TurnOff(void)
{
	pev->effects = EF_NODRAW;
	pev->nextthink = 0;
}

/* <78e94> ../cstrike/dlls/effects.cpp:1383 */
void CSprite::TurnOn(void)
{
	pev->effects = 0;

	if ((pev->framerate && m_maxFrame > 1) || (pev->spawnflags & SF_SPRITE_ONCE))
	{
		SetThink(&CSprite::AnimateThink);
		pev->nextthink = gpGlobals->time;
		m_lastTime = gpGlobals->time;
	}

	pev->frame = 0;
}

/* <75e27> ../cstrike/dlls/effects.cpp:1396 */
void CSprite::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	int on = pev->effects != EF_NODRAW;

	if (ShouldToggle(useType, on))
	{
		if (on)
			TurnOff();
		else
			TurnOn();
	}
}

/* <7405a> ../cstrike/dlls/effects.cpp:1448 */
IMPLEMENT_SAVERESTORE(CGibShooter, CBaseDelay);

/* <78eb7> ../cstrike/dlls/effects.cpp:1449 */
LINK_ENTITY_TO_CLASS(gibshooter, CGibShooter);

/* <73dbb> ../cstrike/dlls/effects.cpp:1452 */
void CGibShooter::__MAKE_VHOOK(Precache)(void)
{
	if (g_Language == LANGUAGE_GERMAN)
	{
		m_iGibModelIndex = PRECACHE_MODEL("models/germanygibs.mdl");
	}
	else
	{
		m_iGibModelIndex = PRECACHE_MODEL("models/hgibs.mdl");
	}
}

/* <74886> ../cstrike/dlls/effects.cpp:1465 */
void CGibShooter::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "m_iGibs"))
	{
		m_iGibs = m_iGibCapacity = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_flVelocity"))
	{
		m_flGibVelocity = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_flVariance"))
	{
		m_flVariance = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "m_flGibLife"))
	{
		m_flGibLife = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseDelay::KeyValue(pkvd);
}

/* <735f4> ../cstrike/dlls/effects.cpp:1493 */
void CGibShooter::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SetThink(&CGibShooter::ShootThink);
	pev->nextthink = gpGlobals->time;
}

/* <73cb5> ../cstrike/dlls/effects.cpp:1499 */
void CGibShooter::__MAKE_VHOOK(Spawn)(void)
{
	Precache();

	pev->solid = SOLID_NOT;
	pev->effects = EF_NODRAW;

	if (m_flDelay == 0.0f)
	{
		m_flDelay = 0.1f;
	}

	if (m_flGibLife == 0.0f)
	{
		m_flGibLife = 25;
	}

	SetMovedir(pev);
	pev->body = MODEL_FRAMES(m_iGibModelIndex);
}

/* <744ff> ../cstrike/dlls/effects.cpp:1521 */
CGib *CGibShooter::__MAKE_VHOOK(CreateGib)(void)
{
	if (CVAR_GET_FLOAT("violence_hgibs") == 0)
		return NULL;

	CGib *pGib = GetClassPtr((CGib *)NULL);

	pGib->Spawn("models/hgibs.mdl");
	pGib->m_bloodColor = BLOOD_COLOR_RED;

	if (pev->body <= 1)
	{
		ALERT(at_aiconsole, "GibShooter Body is <= 1!\n");
	}

	// avoid throwing random amounts of the 0th gib. (skull).
	pGib->pev->body = RANDOM_LONG(1, pev->body - 1);

	return pGib;
}

/* <75751> ../cstrike/dlls/effects.cpp:1541 */
void CGibShooter::ShootThink(void)
{
	pev->nextthink = m_flDelay + gpGlobals->time;

	Vector vecShootDir;
	vecShootDir = pev->movedir;
	
	float rnd_right = RANDOM_FLOAT(-1, 1);
	float rnd_forward = RANDOM_FLOAT(-1, 1);
	float rnd_up = RANDOM_FLOAT(-1, 1);

	// right
	vecShootDir[0] = (vecShootDir[0] + (rnd_right * gpGlobals->v_right[0]) * m_flVariance);
	vecShootDir[1] = (vecShootDir[1] + (rnd_right * gpGlobals->v_right[1]) * m_flVariance);
	vecShootDir[2] = (vecShootDir[2] + (rnd_right * gpGlobals->v_right[2]) * m_flVariance);

	// forward
	vecShootDir[0] = (vecShootDir[0] + (rnd_forward * gpGlobals->v_forward[0]) * m_flVariance);
	vecShootDir[1] = (vecShootDir[1] + (rnd_forward * gpGlobals->v_forward[1]) * m_flVariance);
	vecShootDir[2] = (vecShootDir[2] + (rnd_forward * gpGlobals->v_forward[2]) * m_flVariance);

	// up
	vecShootDir[0] = (vecShootDir[0] + (rnd_up * gpGlobals->v_up[0]) * m_flVariance);
	vecShootDir[1] = (vecShootDir[1] + (rnd_up * gpGlobals->v_up[1]) * m_flVariance);
	vecShootDir[2] = (vecShootDir[2] + (rnd_up * gpGlobals->v_up[2]) * m_flVariance);

	vecShootDir = vecShootDir.Normalize();
	CGib *pGib = CreateGib();

	if (pGib)
	{
		pGib->pev->origin = pev->origin;
		pGib->pev->velocity = vecShootDir * m_flGibVelocity;

		pGib->pev->avelocity.x = RANDOM_FLOAT(100, 200);
		pGib->pev->avelocity.y = RANDOM_FLOAT(100, 300);

		float thinkTime = pGib->pev->nextthink - gpGlobals->time;

		pGib->m_lifeTime = (m_flGibLife * RANDOM_FLOAT(0.95, 1.05));	// +/- 5%
		if (pGib->m_lifeTime < thinkTime)
		{
			pGib->pev->nextthink = gpGlobals->time + pGib->m_lifeTime;
			pGib->m_lifeTime = 0;
		}

	}

	if (--m_iGibs <= 0)
	{
		if (pev->spawnflags & SF_GIBSHOOTER_REPEATABLE)
		{
			m_iGibs = m_iGibCapacity;
			SetThink(NULL);
			pev->nextthink = gpGlobals->time;
		}
		else
		{
			SetThink(&CGibShooter::SUB_Remove);
			pev->nextthink = gpGlobals->time;
		}
	}
}

/* <78f87> ../cstrike/dlls/effects.cpp:1600 */
LINK_ENTITY_TO_CLASS(env_shooter, CEnvShooter);

/* <749e7> ../cstrike/dlls/effects.cpp:1602 */
NOBODY void CEnvShooter::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "shootmodel"))
	{
		pev->model = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "shootsounds"))
	{
		int iNoise = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;

		switch(iNoise)
		{
		case 0:
			m_iGibMaterial = matGlass;
			break;
		case 1:
			m_iGibMaterial = matWood;
			break;
		case 2:
			m_iGibMaterial = matMetal;
			break;
		case 3:
			m_iGibMaterial = matFlesh;
			break;
		case 4:
			m_iGibMaterial = matRocks;
			break;

		default:
		case -1:
			m_iGibMaterial = matNone;
			break;
		}
	}
	else
		CGibShooter::KeyValue(pkvd);
}

/* <73cdc> ../cstrike/dlls/effects.cpp:1644 */
void CEnvShooter::__MAKE_VHOOK(Precache)(void)
{
	m_iGibModelIndex = PRECACHE_MODEL((char *)STRING(pev->model));
	CBreakable::MaterialSoundPrecache((Materials)m_iGibMaterial);
}

/* <7464b> ../cstrike/dlls/effects.cpp:1651 */
CGib *CEnvShooter::__MAKE_VHOOK(CreateGib)(void)
{
	CGib *pGib = GetClassPtr((CGib *)NULL);

	pGib->Spawn(STRING(pev->model));

	int bodyPart = 0;

	if (pev->body > 1)
		bodyPart = RANDOM_LONG(0, pev->body - 1);

	pGib->pev->body = bodyPart;
	pGib->m_bloodColor = DONT_BLEED;
	pGib->m_material = m_iGibMaterial;

	pGib->pev->rendermode = pev->rendermode;
	pGib->pev->renderamt = pev->renderamt;
	pGib->pev->rendercolor = pev->rendercolor;
	pGib->pev->renderfx = pev->renderfx;
	pGib->pev->scale = pev->scale;
	pGib->pev->skin = pev->skin;

	return pGib;
}

/* <79057> ../cstrike/dlls/effects.cpp:1696 */
LINK_ENTITY_TO_CLASS(test_effect, CTestEffect);

/* <73656> ../cstrike/dlls/effects.cpp:1698 */
void CTestEffect::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
}

/* <7367c> ../cstrike/dlls/effects.cpp:1703 */
void CTestEffect::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("sprites/lgtning.spr");
}

/* <76e39> ../cstrike/dlls/effects.cpp:1708 */
void CTestEffect::TestThink(void)
{
	int i;
	float t = (gpGlobals->time - m_flStartTime);

	if (m_iBeam < 24)
	{
		CBeam *pbeam = CBeam::BeamCreate("sprites/lgtning.spr", 100);

		TraceResult tr;
		Vector vecSrc = pev->origin;
		Vector vecDir = Vector(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1),RANDOM_FLOAT(-1, 1));
		vecDir = vecDir.Normalize();

		UTIL_TraceLine(vecSrc, vecSrc + vecDir * 128, ignore_monsters, ENT(pev), &tr);

		pbeam->PointsInit(vecSrc, tr.vecEndPos);
		pbeam->SetColor(255, 180, 100);
		pbeam->SetWidth(100);
		pbeam->SetScrollRate(12);

		m_flBeamTime[m_iBeam] = gpGlobals->time;
		m_pBeam[m_iBeam] = pbeam;
		m_iBeam++;

	}

	if (t < 3.0)
	{
		for (i = 0; i < m_iBeam; i++)
		{
			t = (gpGlobals->time - m_flBeamTime[i]) / (3 + m_flStartTime - m_flBeamTime[i]);
			m_pBeam[i]->SetBrightness(255 * t);
		}
		pev->nextthink = gpGlobals->time + 0.1f;
	}
	else
	{
		for (i = 0; i < m_iBeam; i++)
		{
			UTIL_Remove(m_pBeam[i]);
		}

		m_flStartTime = gpGlobals->time;
		m_iBeam = 0;
		SetThink(NULL);
	}
}

/* <736a2> ../cstrike/dlls/effects.cpp:1759 */
void CTestEffect::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	SetThink(&CTestEffect::TestThink);

	pev->nextthink = gpGlobals->time + 0.1f;
	m_flStartTime = gpGlobals->time;
}

/* <79127> ../cstrike/dlls/effects.cpp:1788 */
LINK_ENTITY_TO_CLASS(env_blood, CBlood);

/* <73c8f> ../cstrike/dlls/effects.cpp:1797 */
void CBlood::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;

	SetMovedir(pev);
}

/* <74c34> ../cstrike/dlls/effects.cpp:1807 */
void CBlood::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "color"))
	{
		int color = Q_atoi(pkvd->szValue);
		switch (color)
		{
		case 1:
			SetColor(BLOOD_COLOR_YELLOW);
			break;
		default:
			SetColor(BLOOD_COLOR_RED);
			break;
		}

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "amount"))
	{
		SetBloodAmount(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <791f7> ../cstrike/dlls/effects.cpp:1834 */
Vector CBlood::Direction(void)
{
	if (pev->spawnflags & SF_BLOOD_RANDOM)
		return UTIL_RandomBloodVector();

	return pev->movedir;
}

/* <79256> ../cstrike/dlls/effects.cpp:1843 */
Vector CBlood::BloodPosition(CBaseEntity *pActivator)
{
	if (pev->spawnflags & SF_BLOOD_PLAYER)
	{
		edict_t *pPlayer;

		if (pActivator && pActivator->IsPlayer())
			pPlayer = pActivator->edict();
		else
			pPlayer = INDEXENT(1);

		if (pPlayer)
		{
			return (pPlayer->v.origin + pPlayer->v.view_ofs) + Vector(RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-10, 10));
		}
	}

	return pev->origin;
}

/* <79351> ../cstrike/dlls/effects.cpp:1863 */
void CBlood::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (pev->spawnflags & SF_BLOOD_STREAM)
		UTIL_BloodStream(BloodPosition(pActivator), Direction(), (Color() == BLOOD_COLOR_RED) ? 70 : Color(), (int)BloodAmount());
	else
		UTIL_BloodDrips(BloodPosition(pActivator), Direction(), Color(), (int)BloodAmount());

	if (pev->spawnflags & SF_BLOOD_DECAL)
	{
		Vector forward = Direction();
		Vector start = BloodPosition(pActivator);

		TraceResult tr;
		UTIL_TraceLine(start, start + forward * BloodAmount() * 2, ignore_monsters, NULL, &tr);

		if (tr.flFraction != 1.0f)
		{
			UTIL_BloodDecalTrace(&tr, Color());
		}
	}
}

/* <79594> ../cstrike/dlls/effects.cpp:1905 */
LINK_ENTITY_TO_CLASS(env_shake, CShake);

/* <73705> ../cstrike/dlls/effects.cpp:1919 */
void CShake::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;

	if (pev->spawnflags & SF_SHAKE_EVERYONE)
		pev->dmg = 0;
}

/* <74d76> ../cstrike/dlls/effects.cpp:1931 */
void CShake::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "amplitude"))
	{
		SetAmplitude(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "frequency"))
	{
		SetFrequency(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "duration"))
	{
		SetDuration(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "radius"))
	{
		SetRadius(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <73c2d> ../cstrike/dlls/effects.cpp:1958 */
void CShake::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	UTIL_ScreenShake(pev->origin, Amplitude(), Frequency(), Duration(), Radius());
}

/* <79664> ../cstrike/dlls/effects.cpp:1979 */
LINK_ENTITY_TO_CLASS(env_fade, CFade);

/* <7372b> ../cstrike/dlls/effects.cpp:1987 */
void CFade::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = 0;
	pev->frame = 0;
}

/* <74efa> ../cstrike/dlls/effects.cpp:1996 */
void CFade::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "duration"))
	{
		SetDuration(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "holdtime"))
	{
		SetHoldTime(Q_atof(pkvd->szValue));
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <73bb4> ../cstrike/dlls/effects.cpp:2013 */
void CFade::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	int fadeFlags = 0;

	if (!(pev->spawnflags & SF_FADE_IN))
		fadeFlags |= FFADE_OUT;

	if (pev->spawnflags & SF_FADE_MODULATE)
		fadeFlags |= FFADE_MODULATE;

	if (pev->spawnflags & SF_FADE_ONLYONE)
	{
		if (pActivator->IsNetClient())
		{
			UTIL_ScreenFade(pActivator, pev->rendercolor, Duration(), HoldTime(), (int)pev->renderamt, fadeFlags);
		}
	}
	else
		UTIL_ScreenFadeAll(pev->rendercolor, Duration(), HoldTime(), (int)pev->renderamt, fadeFlags);

	SUB_UseTargets(this, USE_TOGGLE, 0);
}

/* <79734> ../cstrike/dlls/effects.cpp:2048 */
LINK_ENTITY_TO_CLASS(env_message, CMessage);

/* <73751> ../cstrike/dlls/effects.cpp:2051 */
void CMessage::__MAKE_VHOOK(Spawn)(void)
{
	Precache();

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;

	switch (pev->impulse)
	{
	case 1: // Medium radius
		pev->speed = ATTN_STATIC;
		break;

	case 2:	// Large radius
		pev->speed = ATTN_NORM;
		break;

	case 3:	//EVERYWHERE
		pev->speed = ATTN_NONE;
		break;

	default:
	case 0: // Small radius
		pev->speed = ATTN_IDLE;
		break;
	}
	pev->impulse = 0;

	// No volume, use normal
	if (pev->scale <= 0.0f)
		pev->scale = 1.0;
}

/* <73df7> ../cstrike/dlls/effects.cpp:2085 */
void CMessage::__MAKE_VHOOK(Precache)(void)
{
	if (pev->noise)
	{
		PRECACHE_SOUND((char *)STRING(pev->noise));
	}
}

/* <74765> ../cstrike/dlls/effects.cpp:2091 */
void CMessage::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "messagesound"))
	{
		pev->noise = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "messagevolume"))
	{
		pev->scale = Q_atof(pkvd->szValue) * 0.1;
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "messageattenuation"))
	{
		pev->impulse = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CPointEntity::KeyValue(pkvd);
}

/* <73aa5> ../cstrike/dlls/effects.cpp:2113 */
void CMessage::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	CBaseEntity *pPlayer = NULL;

	if (pev->spawnflags & SF_MESSAGE_ALL)
		UTIL_ShowMessageAll(STRING(pev->message));
	else
	{
		if (pActivator && pActivator->IsPlayer())
			pPlayer = pActivator;
		else
		{
			pPlayer = CBaseEntity::Instance(INDEXENT(1));
		}

		if (pPlayer)
			UTIL_ShowMessage(STRING(pev->message), pPlayer);
	}
	if (pev->noise)
	{
		EMIT_SOUND(edict(), CHAN_BODY, STRING(pev->noise), pev->scale, pev->speed);
	}
	if (pev->spawnflags & SF_MESSAGE_ONCE)
		UTIL_Remove(this);

	SUB_UseTargets(this, USE_TOGGLE, 0);
}

/* <79804> ../cstrike/dlls/effects.cpp:2160 */
LINK_ENTITY_TO_CLASS(env_funnel, CEnvFunnel);

/* <73778> ../cstrike/dlls/effects.cpp:2155 */
void CEnvFunnel::__MAKE_VHOOK(Precache)(void)
{
	m_iSprite = PRECACHE_MODEL("sprites/flare6.spr");
}

/* <7379f> ../cstrike/dlls/effects.cpp:2162 */
void CEnvFunnel::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_LARGEFUNNEL);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z);
		WRITE_SHORT(m_iSprite);

		// funnel flows in reverse?
		if (pev->spawnflags & SF_FUNNEL_REVERSE)
		{
			WRITE_SHORT(1);
		}
		else
		{
			WRITE_SHORT(0);
		}


	MESSAGE_END();

	SetThink(&CEnvFunnel::SUB_Remove);
	pev->nextthink = gpGlobals->time;
}

/* <7382b> ../cstrike/dlls/effects.cpp:2187 */
void CEnvFunnel::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	pev->solid = SOLID_NOT;
	pev->effects = EF_NODRAW;
}

/* <73852> ../cstrike/dlls/effects.cpp:2207 */
void CEnvBeverage::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/can.mdl");
	PRECACHE_SOUND("weapons/g_bounce3.wav");
}

/* <798d4> ../cstrike/dlls/effects.cpp:2213 */
LINK_ENTITY_TO_CLASS(env_beverage, CEnvBeverage);

/* <7439c> ../cstrike/dlls/effects.cpp:2215 */
void CEnvBeverage::__MAKE_VHOOK(Use)(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (pev->frags != 0.0f || pev->health <= 0.0f)
	{
		// no more cans while one is waiting in the dispenser, or if I'm out of cans.
		return;
	}

	CBaseEntity *pCan = CBaseEntity::Create("item_sodacan", pev->origin, pev->angles, edict());

	if (pev->skin == 6)
	{
		// random
		pCan->pev->skin = RANDOM_LONG(0, 5);
	}
	else
		pCan->pev->skin = pev->skin;

	pev->frags = 1;
	pev->health--;
}

/* <73879> ../cstrike/dlls/effects.cpp:2242 */
void CEnvBeverage::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	pev->solid = SOLID_NOT;
	pev->effects = EF_NODRAW;
	pev->frags = 0;

	if (pev->health == 0.0f)
	{
		pev->health = 10;
	}
}

/* <738a0> ../cstrike/dlls/effects.cpp:2267 */
void CItemSoda::__MAKE_VHOOK(Precache)(void)
{
	;
}

/* <799a4> ../cstrike/dlls/effects.cpp:2271 */
LINK_ENTITY_TO_CLASS(item_sodacan, CItemSoda);

/* <738c6> ../cstrike/dlls/effects.cpp:2273 */
void CItemSoda::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_TOSS;

	SET_MODEL(ENT(pev), "models/can.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	SetThink(&CItemSoda::CanThink);
	pev->nextthink = gpGlobals->time + 0.5f;
}

/* <73961> ../cstrike/dlls/effects.cpp:2286 */
void CItemSoda::CanThink(void)
{
	EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/g_bounce3.wav", VOL_NORM, ATTN_NORM);

	pev->solid = SOLID_TRIGGER;
	UTIL_SetSize(pev, Vector(-8, -8, 0), Vector(8, 8, 8));

	SetThink(NULL);
	SetTouch(&CItemSoda::CanTouch);
}

/* <7431d> ../cstrike/dlls/effects.cpp:2296 */
void CItemSoda::CanTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
	{
		return;
	}

	// spoit sound here
	pOther->TakeHealth(1, DMG_GENERIC);// a bit of health.

	if (!FNullEnt(pev->owner))
	{
		// tell the machine the can was taken
		pev->owner->v.frags = 0;
	}

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_NONE;
	pev->effects = EF_NODRAW;

	SetTouch(NULL);
	SetThink(&CItemSoda::SUB_Remove);
	pev->nextthink = gpGlobals->time;
}

#ifdef HOOK_GAMEDLL

void CBombGlow::Spawn(void)
{
	Spawn_();
}

void CBombGlow::Think(void)
{
	Think_();
}

void CSprite::Spawn(void)
{
	Spawn_();
}

void CSprite::Precache(void)
{
	Precache_();
}

void CSprite::Restart(void)
{
	Restart_();
}

int CSprite::Save(CSave &save)
{
	return Save_(save);
}

int CSprite::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CSprite::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBeam::Spawn(void)
{
	Spawn_();
}

void CBeam::Precache(void)
{
	Precache_();
}

void CLaser::Spawn(void)
{
	Spawn_();
}

void CLaser::Precache(void)
{
	Precache_();
}

void CLaser::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CLaser::Save(CSave &save)
{
	return Save_(save);
}

int CLaser::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CLaser::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBubbling::Spawn(void)
{
	Spawn_();
}

void CBubbling::Precache(void)
{
	Precache_();
}

void CBubbling::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBubbling::Save(CSave &save)
{
	return Save_(save);
}

int CBubbling::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBubbling::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CLightning::Spawn(void)
{
	Spawn_();
}

void CLightning::Precache(void)
{
	Precache_();
}

void CLightning::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CLightning::Save(CSave &save)
{
	return Save_(save);
}

int CLightning::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CLightning::Activate(void)
{
	Activate_();
}

void CGlow::Spawn(void)
{
	Spawn_();
}

int CGlow::Save(CSave &save)
{
	return Save_(save);
}

int CGlow::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGlow::Think(void)
{
	Think_();
}

void CGibShooter::Spawn(void)
{
	Spawn_();
}

void CGibShooter::Precache(void)
{
	Precache_();
}

void CGibShooter::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CGibShooter::Save(CSave &save)
{
	return Save_(save);
}

int CGibShooter::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CGibShooter::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

CGib *CGibShooter::CreateGib(void)
{
	return CreateGib_();
}

void CEnvShooter::Precache(void)
{
	Precache_();
}

void CEnvShooter::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

CGib *CEnvShooter::CreateGib(void)
{
	return CreateGib_();
}

void CTestEffect::Spawn(void)
{
	Spawn_();
}

void CTestEffect::Precache(void)
{
	Precache_();
}

void CTestEffect::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBlood::Spawn(void)
{
	Spawn_();
}

void CBlood::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CBlood::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CShake::Spawn(void)
{
	Spawn_();
}

void CShake::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CShake::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFade::Spawn(void)
{
	Spawn_();
}

void CFade::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CFade::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CMessage::Spawn(void)
{
	Spawn_();
}

void CMessage::Precache(void)
{
	Precache_();
}

void CMessage::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

void CMessage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CEnvFunnel::Spawn(void)
{
	Spawn_();
}

void CEnvFunnel::Precache(void)
{
	Precache_();
}

void CEnvFunnel::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CEnvBeverage::Spawn(void)
{
	Spawn_();
}

void CEnvBeverage::Precache(void)
{
	Precache_();
}

void CEnvBeverage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CItemSoda::Spawn(void)
{
	Spawn_();
}

void CItemSoda::Precache(void)
{
	Precache_();
}

#endif // HOOK_GAMEDLL
