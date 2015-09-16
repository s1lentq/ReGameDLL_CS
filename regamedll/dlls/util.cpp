#include "precompiled.h"

#if 1

void *addr_orig;
char patchByte[5];
char patchByteOriginal[5];

//static DWORD oldProtection;
///VirtualProtect(addr_orig,5,PAGE_EXECUTE_READWRITE,&oldProtection);
//memcpy(addr_orig,patchByteOriginal,5);
//pWeaponUSP(a);
//int seedad = pUTIL_SharedRandomLong(seed,low,high);
//memcpy(addr_orig,patchByte,5);

#endif

unsigned int glSeed;
CUtlVector< hash_item_t > stringsHashTable;

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

unsigned int seed_table[256] =
{
	28985U, 27138U, 26457U, 9451U, 17764U, 10909U, 28790U, 8716U, 6361U, 4853U, 17798U, 21977U, 19643U, 20662U, 10834U, 20103,
	27067U, 28634U, 18623U, 25849U, 8576U, 26234U, 23887U, 18228U, 32587U, 4836U, 3306U, 1811U, 3035U, 24559U, 18399U, 315,
	26766U, 907U, 24102U, 12370U, 9674U, 2972U, 10472U, 16492U, 22683U, 11529U, 27968U, 30406U, 13213U, 2319U, 23620U, 16823,
	10013U, 23772U, 21567U, 1251U, 19579U, 20313U, 18241U, 30130U, 8402U, 20807U, 27354U, 7169U, 21211U, 17293U, 5410U, 19223,
	10255U, 22480U, 27388U, 9946U, 15628U, 24389U, 17308U, 2370U, 9530U, 31683U, 25927U, 23567U, 11694U, 26397U, 32602U, 15031,
	18255U, 17582U, 1422U, 28835U, 23607U, 12597U, 20602U, 10138U, 5212U, 1252U, 10074U, 23166U, 19823U, 31667U, 5902U, 24630,
	18948U, 14330U, 14950U, 8939U, 23540U, 21311U, 22428U, 22391U, 3583U, 29004U, 30498U, 18714U, 4278U, 2437U, 22430U, 3439,
	28313U, 23161U, 25396U, 13471U, 19324U, 15287U, 2563U, 18901U, 13103U, 16867U, 9714U, 14322U, 15197U, 26889U, 19372U, 26241,
	31925U, 14640U, 11497U, 8941U, 10056U, 6451U, 28656U, 10737U, 13874U, 17356U, 8281U, 25937U, 1661U, 4850U, 7448U, 12744,
	21826U, 5477U, 10167U, 16705U, 26897U, 8839U, 30947U, 27978U, 27283U, 24685U, 32298U, 3525U, 12398U, 28726U, 9475U, 10208,
	617U, 13467U, 22287U, 2376U, 6097U, 26312U, 2974U, 9114U, 21787U, 28010U, 4725U, 15387U, 3274U, 10762U, 31695U, 17320,
	18324U, 12441U, 16801U, 27376U, 22464U, 7500U, 5666U, 18144U, 15314U, 31914U, 31627U, 6495U, 5226U, 31203U, 2331U, 4668,
	12650U, 18275U, 351U, 7268U, 31319U, 30119U, 7600U, 2905U, 13826U, 11343U, 13053U, 15583U, 30055U, 31093U, 5067U, 761,
	9685U, 11070U, 21369U, 27155U, 3663U, 26542U, 20169U, 12161U, 15411U, 30401U, 7580U, 31784U, 8985U, 29367U, 20989U, 14203,
	29694U, 21167U, 10337U, 1706U, 28578U, 887U, 3373U, 19477U, 14382U, 675U, 7033U, 15111U, 26138U, 12252U, 30996U, 21409,
	25678U, 18555U, 13256U, 23316U, 22407U, 16727U, 991U, 9236U, 5373U, 29402U, 6117U, 15241U, 27715U, 19291U, 19888U, 19847U
};

TYPEDESCRIPTION gEntvarsDescription[86] =
{
	DEFINE_ENTITY_FIELD(classname, FIELD_STRING),
	DEFINE_ENTITY_GLOBAL_FIELD(globalname, FIELD_STRING),
	DEFINE_ENTITY_FIELD(origin, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_FIELD(oldorigin, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_FIELD(velocity, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(basevelocity, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(movedir, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(angles, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(avelocity, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(punchangle, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(v_angle, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(fixangle, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(idealpitch, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(pitch_speed, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(ideal_yaw, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(yaw_speed, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(modelindex, FIELD_INTEGER),
	DEFINE_ENTITY_GLOBAL_FIELD(model, FIELD_MODELNAME),
	DEFINE_ENTITY_FIELD(viewmodel, FIELD_MODELNAME),
	DEFINE_ENTITY_FIELD(weaponmodel, FIELD_MODELNAME),
	DEFINE_ENTITY_FIELD(absmin, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_FIELD(absmax, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_GLOBAL_FIELD(mins, FIELD_VECTOR),
	DEFINE_ENTITY_GLOBAL_FIELD(maxs, FIELD_VECTOR),
	DEFINE_ENTITY_GLOBAL_FIELD(size, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(ltime, FIELD_TIME),
	DEFINE_ENTITY_FIELD(nextthink, FIELD_TIME),
	DEFINE_ENTITY_FIELD(solid, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(movetype, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(skin, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(body, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(effects, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(gravity, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(friction, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(light_level, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(frame, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(scale, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(sequence, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(animtime, FIELD_TIME),
	DEFINE_ENTITY_FIELD(framerate, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(controller, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(blending, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(rendermode, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(renderamt, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(rendercolor, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(renderfx, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(health, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(frags, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(weapons, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(takedamage, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(deadflag, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(view_ofs, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(button, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(impulse, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(chain, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(dmg_inflictor, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(enemy, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(aiment, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(owner, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(groundentity, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(spawnflags, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(flags, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(colormap, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(team, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(max_health, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(teleport_time, FIELD_TIME),
	DEFINE_ENTITY_FIELD(armortype, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(armorvalue, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(waterlevel, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(watertype, FIELD_INTEGER),
	DEFINE_ENTITY_GLOBAL_FIELD(target, FIELD_STRING),
	DEFINE_ENTITY_GLOBAL_FIELD(targetname, FIELD_STRING),
	DEFINE_ENTITY_FIELD(netname, FIELD_STRING),
	DEFINE_ENTITY_FIELD(message, FIELD_STRING),
	DEFINE_ENTITY_FIELD(dmg_take, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(dmg_save, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(dmg, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(dmgtime, FIELD_TIME),
	DEFINE_ENTITY_FIELD(noise, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(noise1, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(noise2, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(noise3, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(speed, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(air_finished, FIELD_TIME),
	DEFINE_ENTITY_FIELD(pain_finished, FIELD_TIME),
	DEFINE_ENTITY_FIELD(radsuit_finished, FIELD_TIME),
};

int g_groupmask = 0;
int g_groupop = 0;

const int gSizes[18] = { 4, 4, 4, 4, 4, 4, 4, 12, 12, 4, 4, 4, 4, 2, 1, 4, 4, 4 };

#else //HOOK_GAMEDLL

unsigned int seed_table[256];
TYPEDESCRIPTION gEntvarsDescription[86];

int g_groupop;
int g_groupmask;

const int gSizes[18];

#endif //HOOK_GAMEDLL

/* <1ac4be> ../cstrike/dlls/util.cpp:59 */
unsigned int U_Random(void)
{
	glSeed *= 69069;
	glSeed += seed_table[glSeed & 0xFF] + 1;
	return (glSeed & 0xFFFFFFF);
}

/* <1ab992> ../cstrike/dlls/util.cpp:67 */
void U_Srand(unsigned int seed)
{
	glSeed = seed_table[seed & 0xFF];
}

/* <1ac4f8> ../cstrike/dlls/util.cpp:78 */
int UTIL_SharedRandomLong(unsigned int seed, int low, int high)
{
	unsigned int range = high - low + 1;
	U_Srand((unsigned int)(high + low + seed));
	if (range != 1)
	{
		int rnum = U_Random();
		int offset = rnum % range;
		return (low + offset);
	}

	return low;
}

/* <1ac5b5> ../cstrike/dlls/util.cpp:108 */
float UTIL_SharedRandomFloat(unsigned int seed, float low, float high)
{
	unsigned int range = high - low;
	U_Srand((unsigned int)seed + *(unsigned int *)&low + *(unsigned int *)&high);

	U_Random();
	U_Random();

	if (range)
	{
		int tensixrand = U_Random() & 0xFFFFu;
		float offset = (float)tensixrand / 0x10000u;
		return (low + offset * range);
	}

	return low;
}

/* <1ac6a9> ../cstrike/dlls/util.cpp:136 */
NOXREF void UTIL_ParametricRocket(entvars_t *pev, Vector p_vecOrigin, Vector vecAngles, edict_t *owner)
{
	TraceResult tr;
	Vector vecTravel;
	float travelTime;

	pev->startpos = p_vecOrigin;
	UTIL_MakeVectors(vecAngles);
	UTIL_TraceLine(pev->startpos, gpGlobals->v_forward * 8192.0f + pev->startpos, ignore_monsters, owner, &tr);
	pev->endpos = tr.vecEndPos;

	vecTravel = pev->endpos - pev->startpos;
	if (pev->velocity.Length() > 0.0f)
		travelTime = vecTravel.Length() / pev->velocity.Length();
	else
		travelTime = 0.0f;

	pev->starttime = gpGlobals->time;
	pev->impacttime = travelTime + gpGlobals->time;
}

/* <1ac888> ../cstrike/dlls/util.cpp:160 */
void UTIL_SetGroupTrace(int groupmask, int op)
{
	g_groupmask = groupmask;
	g_groupop = op;

	ENGINE_SETGROUPMASK(groupmask, op);
}

/* <1ac8bf> ../cstrike/dlls/util.cpp:168 */
void UTIL_UnsetGroupTrace(void)
{
	g_groupmask = 0;
	g_groupop = 0;

	ENGINE_SETGROUPMASK(0,0);
}

/* <1ac90c> ../cstrike/dlls/util.cpp:177 */
NOXREF UTIL_GroupTrace::UTIL_GroupTrace(int groupmask, int op)
{
	m_oldgroupmask = g_groupmask;
	m_oldgroupop = g_groupop;

	g_groupmask = groupmask;
	g_groupop = op;

	ENGINE_SETGROUPMASK(groupmask, op);
}

/* <1ac963> ../cstrike/dlls/util.cpp:188 */
NOXREF UTIL_GroupTrace::~UTIL_GroupTrace(void)
{
	g_groupmask = m_oldgroupmask;
	g_groupop = m_oldgroupop;

	ENGINE_SETGROUPMASK(g_groupmask, g_groupop);
}

/* <1ac985> ../cstrike/dlls/util.cpp:345 */
NOXREF BOOL UTIL_GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	return g_pGameRules->GetNextBestWeapon(pPlayer,pCurrentWeapon);
}

/* <1ab9ab> ../cstrike/dlls/util.cpp:352 */
NOXREF float UTIL_AngleMod(float a)
{
	if (a < 0.0f)
		a = a + 360.0f * ((int)(a / 360.0f) + 1);
	else if (a >= 360.0f)
		a = a - 360.0f * ((int)(a / 360.0f));
	return a;
}

/* <1aca1d> ../cstrike/dlls/util.cpp:366 */
NOXREF float UTIL_AngleDiff(float destAngle, float srcAngle)
{
	float delta = destAngle - srcAngle;
	if (destAngle > srcAngle)
	{
		if (delta >= 180.0f)
			delta -= 360.0f;
	}
	else
	{
		if (delta <= -180.0f)
			delta += 360.0f;
	}
	return delta;
}

/* <1aca77> ../cstrike/dlls/util.cpp:384 */
Vector UTIL_VecToAngles(const Vector &vec)
{
	float rgflVecOut[3];
	VEC_TO_ANGLES(vec, rgflVecOut);
	return Vector(rgflVecOut);
}

/* <1acaf6> ../cstrike/dlls/util.cpp:392 */
NOXREF void UTIL_MoveToOrigin(edict_t *pent, const Vector &vecGoal, float flDist, int iMoveType)
{
	float rgfl[3];
	vecGoal.CopyToArray(rgfl);
	MOVE_TO_ORIGIN(pent, rgfl, flDist, iMoveType);
}

/* <1acb92> ../cstrike/dlls/util.cpp:401 */
int UTIL_EntitiesInBox(CBaseEntity **pList, int listMax, const Vector &mins, const Vector &maxs, int flagMask)
{
	edict_t *pEdict = INDEXENT(1);
	CBaseEntity *pEntity;
	int count = 0;

	if (!pEdict)
		return 0;

	for (int i = 1; i < gpGlobals->maxEntities; i++, pEdict++)
	{
		if (pEdict->free)
			continue;

		if (flagMask && !(pEdict->v.flags & flagMask))
			continue;

		if (mins.x > pEdict->v.absmax.x
			|| mins.y > pEdict->v.absmax.y
			|| mins.z > pEdict->v.absmax.z
			|| maxs.x < pEdict->v.absmin.x
			|| maxs.y < pEdict->v.absmin.y
			|| maxs.z < pEdict->v.absmin.z)
			continue;

		pEntity = CBaseEntity::Instance(pEdict);
		if (!pEntity)
			continue;

		pList[count++] = pEntity;

		if (count >= listMax)
			break;
	}

	return count;
}

/* <1acca2> ../cstrike/dlls/util.cpp:443 */
NOXREF int UTIL_MonstersInSphere(CBaseEntity ** pList, int listMax, const Vector &center, float radius)
{
	edict_t *pEdict;
	CBaseEntity *pEntity;
	int count = 0;
	float distance;
	float delta;

	float radiusSquared = radius * radius;
	pEdict = INDEXENT(1);

	if (!pEdict)
		return count;

	for (int i = 1; i < gpGlobals->maxEntities; i++, pEdict++)
	{
		if (pEdict->free)
			continue;

		if (!(pEdict->v.flags & (FL_CLIENT|FL_MONSTER)))
			continue;

		delta = center.x - pEdict->v.origin.x;
		delta *= delta;

		if (delta > radiusSquared)
			continue;

		distance = delta;

		delta = center.y - pEdict->v.origin.y;
		delta *= delta;

		distance += delta;
		if (distance > radiusSquared)
			continue;

		delta = center.z - (pEdict->v.absmin.z + pEdict->v.absmax.z) * 0.5;
		delta *= delta;

		distance += delta;
		if (distance > radiusSquared)
			continue;

		pEntity = CBaseEntity::Instance(pEdict);
		if (!pEntity)
			continue;

		pList[count] = pEntity;
		count++;

		if (count >= listMax)
			return count;
	}

	return count;
}

/* <1acdcc> ../cstrike/dlls/util.cpp:505 */
CBaseEntity *UTIL_FindEntityInSphere(CBaseEntity *pStartEntity, const Vector &vecCenter, float flRadius)
{
	edict_t	*pentEntity;
	if (pStartEntity)
		pentEntity = pStartEntity->edict();
	else
		pentEntity = NULL;

	pentEntity = FIND_ENTITY_IN_SPHERE(pentEntity, vecCenter, flRadius);
	if (!FNullEnt(pentEntity))
	{
		return CBaseEntity::Instance(pentEntity);
	}

	return NULL;
}

/* <1acec6> ../cstrike/dlls/util.cpp:535 */
CBaseEntity *UTIL_FindEntityByString_Old(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue)
{
	edict_t	*pentEntity;
	if (pStartEntity)
		pentEntity = pStartEntity->edict();
	else
		pentEntity = NULL;

	pentEntity = FIND_ENTITY_BY_STRING(pentEntity, szKeyword, szValue);
	if (!FNullEnt(pentEntity))
	{
		return CBaseEntity::Instance(pentEntity);
	}

	return NULL;
}

/* <1acfbb> ../cstrike/dlls/util.cpp:552 */
CBaseEntity *UTIL_FindEntityByString(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue)
{
	edict_t	*pentEntity;
	int startEntityIndex;

	if (pStartEntity)
		pentEntity = pStartEntity->edict();
	else
		pentEntity = NULL;

	startEntityIndex = ENTINDEX(pentEntity);

	//it best each entity list
	if (*szKeyword == 'c')
	{
		int hash;
		hash_item_t *item;
		int count;

		hash = CaseInsensitiveHash(szValue, stringsHashTable.Count());
		count = stringsHashTable.Count();
		item = &stringsHashTable[ hash ];

		if (!item->pev)
		{
			item->lastHash = NULL;
			return NULL;
		}

		while (item->pev != NULL)
		{
			if (!Q_strcmp(STRING(item->pev->classname), szValue))
				break;

			hash = (hash + 1) % count;
			item = &stringsHashTable[ hash ];
		}

		if (!item->pev)
		{
			item->lastHash = NULL;
			return NULL;
		}

		if (pStartEntity != NULL)
		{
			if (item->lastHash && item->lastHash->pevIndex <= startEntityIndex)
				item = item->lastHash;

			if (item->pevIndex <= startEntityIndex)
			{
				while (item->pevIndex <= startEntityIndex)
				{
					if (!item->next)
						break;

					item = item->next;
				}

				if (item->pevIndex == startEntityIndex)
				{
					stringsHashTable[ hash ].lastHash = NULL;
					return NULL;
				}
			}
		}

		stringsHashTable[ hash ].lastHash = item;
		pentEntity = ENT(item->pev);
	}
	else
		pentEntity = FIND_ENTITY_BY_STRING(pentEntity, szKeyword, szValue);

	if (!FNullEnt(pentEntity))
	{
		return CBaseEntity::Instance(pentEntity);
	}

	return NULL;
}

/* <1ad192> ../cstrike/dlls/util.cpp:673 */
CBaseEntity *UTIL_FindEntityByClassname(CBaseEntity *pStartEntity, const char *szName)
{
	return UTIL_FindEntityByString(pStartEntity, "classname", szName);
}

/* <1ac408> ../cstrike/dlls/util.cpp:678 */
CBaseEntity *UTIL_FindEntityByTargetname(CBaseEntity *pStartEntity, const char *szName)
{
	return UTIL_FindEntityByString(pStartEntity, "targetname", szName);
}

/* <1ad209> ../cstrike/dlls/util.cpp:684 */
CBaseEntity *UTIL_FindEntityGeneric(const char *szWhatever, const Vector &vecSrc, float flRadius)
{
	CBaseEntity *pSearch = NULL;
	CBaseEntity *pEntity = UTIL_FindEntityByTargetname(NULL, szWhatever);
	if (pEntity)
		return pEntity;

	float flMaxDist2 = flRadius * flRadius;
	while ((pSearch = UTIL_FindEntityByClassname(pSearch, szWhatever)) != NULL)
	{
		float flDist2 = (pSearch->pev->origin - vecSrc).Length();
		flDist2 = flDist2 * flDist2;
		if (flMaxDist2 > flDist2)
		{
			pEntity = pSearch;
			flMaxDist2 = flDist2;
		}
	}
	return pEntity;
}

/* <1ad347> ../cstrike/dlls/util.cpp:711 */
CBaseEntity *UTIL_PlayerByIndex(int playerIndex)
{
	CBaseEntity *pPlayer = NULL;
	if (playerIndex > 0 && playerIndex <= gpGlobals->maxClients)
	{
		edict_t *pPlayerEdict = INDEXENT(playerIndex);
		if (pPlayerEdict && !pPlayerEdict->free)
			pPlayer = CBaseEntity::Instance(pPlayerEdict);
	}
	return pPlayer;
}

/* <1abab0> ../cstrike/dlls/util.cpp:728 */
void UTIL_MakeVectors(const Vector &vecAngles)
{
	MAKE_VECTORS(vecAngles);
}

/* <1ad442> ../cstrike/dlls/util.cpp:734 */
void UTIL_MakeAimVectors(const Vector &vecAngles)
{
	float rgflVec[3];
	vecAngles.CopyToArray(rgflVec);
	rgflVec[0] = -rgflVec[0];
	MAKE_VECTORS(rgflVec);
}

/* <1ad4b2> ../cstrike/dlls/util.cpp:745 */
void UTIL_MakeInvVectors(const Vector &vec, globalvars_t *pgv)
{
	MAKE_VECTORS(vec);

	pgv->v_right = pgv->v_right * -1;

	SWAP(pgv->v_forward.y, pgv->v_right.x);
	SWAP(pgv->v_forward.z, pgv->v_up.x);
	SWAP(pgv->v_right.z, pgv->v_up.y);
}

/* <1ad53b> ../cstrike/dlls/util.cpp:758 */
void UTIL_EmitAmbientSound(edict_t *entity, const Vector &vecOrigin, const char *samp, float vol, float attenuation, int fFlags, int pitch)
{
	float rgfl[3];
	vecOrigin.CopyToArray(rgfl);

	if (samp && *samp == '!')
	{
		char name[32];
		if (SENTENCEG_Lookup(samp, name) >= 0)
			EMIT_AMBIENT_SOUND(entity, rgfl, name, vol, attenuation, fFlags, pitch);
	}
	else
		EMIT_AMBIENT_SOUND(entity, rgfl, samp, vol, attenuation, fFlags, pitch);
}

/* <1abaf7> ../cstrike/dlls/util.cpp:773 */
unsigned short FixedUnsigned16(float value, float scale)
{
	int output = value * scale;
	if (output < 0)
		output = 0;

	if (output > USHRT_MAX)
		output = USHRT_MAX;

	return (unsigned short)output;
}

/* <1abb9f> ../cstrike/dlls/util.cpp:786 */
short FixedSigned16(float value, float scale)
{
	int output = value * scale;
	if (output > SHRT_MAX)
		output = SHRT_MAX;

	if (output < SHRT_MIN)
		output = SHRT_MIN;

	return (short)output;
}

/* <1ac13b> ../cstrike/dlls/util.cpp:806 */
void UTIL_ScreenShake(const Vector &center, float amplitude, float frequency, float duration, float radius)
{
	int i;
	float localAmplitude;
	ScreenShake shake;

	shake.duration = FixedUnsigned16(duration, 1<<12);
	shake.frequency = FixedUnsigned16(frequency, 1<<8);

	for (i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (!pPlayer || !(pPlayer->pev->flags & FL_ONGROUND))
			continue;

		localAmplitude = 0;
		if (radius > 0)
		{
			Vector delta = center - pPlayer->pev->origin;
			float distance = delta.Length();

			if (distance < radius)
				localAmplitude = amplitude;
		}
		else
			localAmplitude = amplitude;

		if (localAmplitude)
		{
			shake.amplitude = FixedUnsigned16(localAmplitude, 1<<12);

			MESSAGE_BEGIN(MSG_ONE, gmsgShake, NULL, pPlayer->edict());
				WRITE_SHORT(shake.amplitude);
				WRITE_SHORT(shake.duration);
				WRITE_SHORT(shake.frequency);
			MESSAGE_END();
		}
	}
}

/* <1ad88a> ../cstrike/dlls/util.cpp:852 */
NOXREF void UTIL_ScreenShakeAll(const Vector &center, float amplitude, float frequency, float duration)
{
	UTIL_ScreenShake(center, amplitude, frequency, duration, 0);
}

/* <1ac3a1> ../cstrike/dlls/util.cpp:858 */
void UTIL_ScreenFadeBuild(ScreenFade &fade, const Vector &color, float fadeTime, float fadeHold, int alpha, int flags)
{
	fade.duration = FixedUnsigned16(fadeTime, 1<<12);
	fade.holdTime = FixedUnsigned16(fadeHold, 1<<12);
	fade.r = (int)color.x;
	fade.g = (int)color.y;
	fade.b = (int)color.z;
	fade.a = alpha;
	fade.fadeFlags = flags;
}

/* <1abb68> ../cstrike/dlls/util.cpp:870 */
void UTIL_ScreenFadeWrite(const ScreenFade &fade, CBaseEntity *pEntity)
{
	if (!pEntity || !pEntity->IsNetClient())
		return;

	MESSAGE_BEGIN(MSG_ONE, gmsgFade, NULL, pEntity->edict());
		WRITE_SHORT(fade.duration);
		WRITE_SHORT(fade.holdTime);
		WRITE_SHORT(fade.fadeFlags);
		WRITE_BYTE(fade.r);
		WRITE_BYTE(fade.g);
		WRITE_BYTE(fade.b);
		WRITE_BYTE(fade.a);
	MESSAGE_END();
}

/* <1adc11> ../cstrike/dlls/util.cpp:889 */
void UTIL_ScreenFadeAll(const Vector &color, float fadeTime, float fadeHold, int alpha, int flags)
{
	int i;
	ScreenFade fade;
	UTIL_ScreenFadeBuild(fade, color, fadeTime, fadeHold, alpha, flags);
	for (i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		UTIL_ScreenFadeWrite(fade, pPlayer);
	}
}

/* <1ade39> ../cstrike/dlls/util.cpp:906 */
void UTIL_ScreenFade(CBaseEntity *pEntity, const Vector &color, float fadeTime, float fadeHold, int alpha, int flags)
{
	ScreenFade fade;
	UTIL_ScreenFadeBuild(fade, color, fadeTime, fadeHold, alpha, flags);
	UTIL_ScreenFadeWrite(fade, pEntity);
}

/* <1adfa3> ../cstrike/dlls/util.cpp:915 */
void UTIL_HudMessage(CBaseEntity *pEntity, const hudtextparms_t &textparms, const char *pMessage)
{
	if (!pEntity || !pEntity->IsNetClient())
		return;

	MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, NULL, pEntity->edict());
	WRITE_BYTE(TE_TEXTMESSAGE);
	WRITE_BYTE(textparms.channel & 0xFF);
	WRITE_SHORT(FixedSigned16(textparms.x,1<<13));
	WRITE_SHORT(FixedSigned16(textparms.y,1<<13));
	WRITE_BYTE(textparms.effect);
	WRITE_BYTE(textparms.r1);
	WRITE_BYTE(textparms.g1);
	WRITE_BYTE(textparms.b1);
	WRITE_BYTE(textparms.a1);
	WRITE_BYTE(textparms.r2);
	WRITE_BYTE(textparms.g2);
	WRITE_BYTE(textparms.b2);
	WRITE_BYTE(textparms.a2);
	WRITE_SHORT(FixedUnsigned16(textparms.fadeinTime,1<<8));
	WRITE_SHORT(FixedUnsigned16(textparms.fadeoutTime,1<<8));
	WRITE_SHORT(FixedUnsigned16(textparms.holdTime,1<<8));

	if (textparms.effect == 2)
		WRITE_SHORT(FixedUnsigned16(textparms.fxTime,1<<8));

	if (!pMessage)
		WRITE_STRING(" ");	//TODO: oh yeah
	else
	{
		if (Q_strlen(pMessage) >= 512)
		{
			char tmp[512];
			Q_strncpy(tmp, pMessage, 511);
			tmp[511] = 0;
			WRITE_STRING(tmp);
		}
		else
			WRITE_STRING(pMessage);
	}
	MESSAGE_END();
}

/* <1ae1bf> ../cstrike/dlls/util.cpp:963 */
void UTIL_HudMessageAll(const hudtextparms_t &textparms, const char *pMessage)
{
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (pPlayer)
			UTIL_HudMessage(pPlayer, textparms, pMessage);
	}
}

/* <1ae2ce> ../cstrike/dlls/util.cpp:977 */
void UTIL_ClientPrintAll(int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgTextMsg);
		WRITE_BYTE(msg_dest);
		WRITE_STRING(msg_name);
	if (param1)
		WRITE_STRING(param1);
	if (param2)
		WRITE_STRING(param2);
	if (param3)
		WRITE_STRING(param3);
	if (param4)
		WRITE_STRING(param4);
	MESSAGE_END();
}

/* <1ae370> ../cstrike/dlls/util.cpp:995 */
void ClientPrint(entvars_t *client, int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgTextMsg, NULL, client);
		WRITE_BYTE(msg_dest);
		WRITE_STRING(msg_name);
	if (param1)
		WRITE_STRING(param1);
	if (param2)
		WRITE_STRING(param2);
	if (param3)
		WRITE_STRING(param3);
	if (param4)
		WRITE_STRING(param4);
	MESSAGE_END();
}

/* <1ae423> ../cstrike/dlls/util.cpp:1013 */
NOXREF void UTIL_SayText(const char *pText, CBaseEntity *pEntity)
{
	if (pEntity->IsNetClient())
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgSayText, NULL, pEntity->edict());
			WRITE_BYTE(pEntity->entindex());
			WRITE_STRING(pText);
		MESSAGE_END();
	}
}

/* <1ae4e4> ../cstrike/dlls/util.cpp:1024 */
void UTIL_SayTextAll(const char *pText, CBaseEntity *pEntity)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgSayText);
		WRITE_BYTE(pEntity->entindex());
		WRITE_STRING(pText);
	MESSAGE_END();
}

/* <1ae592> ../cstrike/dlls/util.cpp:1033 */
char *UTIL_dtos1(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

/* <1ae5df> ../cstrike/dlls/util.cpp:1040 */
char *UTIL_dtos2(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

/* <1ae62c> ../cstrike/dlls/util.cpp:1047 */
NOXREF char *UTIL_dtos3(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

/* <1ae679> ../cstrike/dlls/util.cpp:1054 */
NOXREF char *UTIL_dtos4(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

/* <1ae6c6> ../cstrike/dlls/util.cpp:1061 */
void UTIL_ShowMessageArgs(const char *pString, CBaseEntity *pPlayer, CUtlVector<char *> *args, bool isHint)
{
	if (pPlayer && pPlayer->IsNetClient())
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgHudTextArgs, NULL, pPlayer->pev);
			WRITE_STRING(pString);
			WRITE_BYTE(isHint);
			WRITE_BYTE(args->Count());

		for (int i = 0; i < args->Count(); i++)
			WRITE_STRING(args->Element(i));

		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgHudText, NULL, pPlayer->pev);
			WRITE_STRING(pString);
			WRITE_BYTE(isHint);
		MESSAGE_END();
	}
}

/* <1abc11> ../cstrike/dlls/util.cpp:1083 */
void UTIL_ShowMessage(const char *pString, CBaseEntity *pEntity, bool isHint)
{
	if (!pEntity || !pEntity->IsNetClient())
		return;

	MESSAGE_BEGIN(MSG_ONE, gmsgHudText, NULL, pEntity->edict());
		WRITE_STRING(pString);
		WRITE_BYTE((int)isHint);
	MESSAGE_END();
}

/* <1ae8ac> ../cstrike/dlls/util.cpp:1095 */
void UTIL_ShowMessageAll(const char *pString, bool isHint)
{
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (pPlayer)
			UTIL_ShowMessage(pString, pPlayer, isHint);
	}
}

/* <1abc44> ../cstrike/dlls/util.cpp:1116 */
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters), pentIgnore, ptr);
}

// OVERLOAD
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters) | (ignoreGlass ? 0x100 : 0), pentIgnore, ptr);
}

/* <1aeb0a> ../cstrike/dlls/util.cpp:1122 */
void UTIL_TraceHull(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, int hullNumber, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_HULL(vecStart, vecEnd, (igmon == ignore_monsters), hullNumber, pentIgnore, ptr);
}

/* <1aeb8d> ../cstrike/dlls/util.cpp:1127 */
void UTIL_TraceModel(const Vector &vecStart, const Vector &vecEnd, int hullNumber, edict_t *pentModel, TraceResult *ptr)
{
	TRACE_MODEL(vecStart, vecEnd, hullNumber, pentModel, ptr);
}

/* <1aec01> ../cstrike/dlls/util.cpp:1132 */
NOXREF TraceResult UTIL_GetGlobalTrace(void)
{
	TraceResult tr;

	tr.flFraction = gpGlobals->trace_fraction;
	tr.fInWater = (int)gpGlobals->trace_inwater;
	tr.fAllSolid = (int)gpGlobals->trace_allsolid;
	tr.fStartSolid = (int)gpGlobals->trace_startsolid;
	tr.fInOpen = (int)gpGlobals->trace_inopen;
	tr.vecEndPos = gpGlobals->trace_endpos;
	tr.flPlaneDist = gpGlobals->trace_plane_dist;
	tr.vecPlaneNormal = gpGlobals->trace_plane_normal;
	tr.iHitgroup = gpGlobals->trace_hitgroup;
	tr.pHit = gpGlobals->trace_ent;

	return tr;
}

/* <1aec38> ../cstrike/dlls/util.cpp:1150 */
void UTIL_SetSize(entvars_t *pev, const Vector &vecMin, const Vector &vecMax)
{
	SET_SIZE(ENT(pev), vecMin, vecMax);
}

/* <1aec8e> ../cstrike/dlls/util.cpp:1156 */
float UTIL_VecToYaw(const Vector &vec)
{
	return VEC_TO_YAW(vec);
}

/* <1aecc4> ../cstrike/dlls/util.cpp:1162 */
void UTIL_SetOrigin(entvars_t *pev, const Vector &vecOrigin)
{
	edict_t *ent = ENT(pev);
	if (ent)
		SET_ORIGIN(ent, vecOrigin);
}

/* <1aed1f> ../cstrike/dlls/util.cpp:1169 */
NOXREF void UTIL_ParticleEffect(const Vector &vecOrigin, const Vector &vecDirection, ULONG ulColor, ULONG ulCount)
{
	PARTICLE_EFFECT(vecOrigin, vecDirection, (float)ulColor, (float)ulCount);
}

/* <1aed84> ../cstrike/dlls/util.cpp:1175 */
float UTIL_Approach(float target, float value, float speed)
{
	float delta = target - value;
	if (delta > speed)
		value += speed;
	else if (delta < -speed)
		value -= speed;
	else
		value = target;
	return value;
}

/* <1aedeb> ../cstrike/dlls/util.cpp:1190 */
float_precision UTIL_ApproachAngle(float target, float value, float speed)
{
	target = UTIL_AngleMod(target);
	value = UTIL_AngleMod(target);

	float delta = target - value;
	if (speed < 0.0f)
		speed = -speed;

	if (delta < -180.0f)
		delta += 360.0f;
	else if (delta > 180.0f)
		delta -= 360.0f;

	if (delta > speed)
		value += speed;
	else if (delta < -speed)
		value -= speed;
	else
		value = target;
	return value;
}

/* <1aeec5> ../cstrike/dlls/util.cpp:1217 */
float_precision UTIL_AngleDistance(float next, float cur)
{
	float_precision delta;

	delta = next - cur;

	if (delta < -180.0f)
		delta += 360.0f;

	else if (delta > 180.0f)
		delta -= 360.0f;

	return delta;
}

/* <1aef1c> ../cstrike/dlls/util.cpp:1230 */
float UTIL_SplineFraction(float value, float scale)
{
	float valueSquared = value * scale;
	return 3.0f * (valueSquared * valueSquared) - (valueSquared * valueSquared * valueSquared + valueSquared * valueSquared * valueSquared);
}

/* <1aef78> ../cstrike/dlls/util.cpp:1240 */
char *UTIL_VarArgs(char *format, ...)
{
	va_list argptr;
	static char string[1024];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	return string;
}

/* <1aefea> ../cstrike/dlls/util.cpp:1252 */
NOXREF Vector UTIL_GetAimVector(edict_t *pent, float flSpeed)
{
	Vector tmp;
	GET_AIM_VECTOR(pent, flSpeed, tmp);
	return tmp;
}

/* <1af041> ../cstrike/dlls/util.cpp:1259 */
int UTIL_IsMasterTriggered(string_t sMaster, CBaseEntity *pActivator)
{
	if (sMaster)
	{
		edict_t *pentTarget = FIND_ENTITY_BY_TARGETNAME(NULL, STRING(sMaster));
		if (!FNullEnt(pentTarget))
		{
			CBaseEntity *pMaster = CBaseEntity::Instance(pentTarget);
			if (pMaster && (pMaster->ObjectCaps() & FCAP_MASTER))
				return pMaster->IsTriggered(pActivator);
		}
		ALERT(at_console, "Master was null or not a master!\n");
	}

	return 1;
}

/* <1af149> ../cstrike/dlls/util.cpp:1279 */
BOOL UTIL_ShouldShowBlood(int color)
{
	if (color != DONT_BLEED)
	{
		if (color == BLOOD_COLOR_RED)
		{
			if (CVAR_GET_FLOAT("violence_hblood") != 0.0f)
				return TRUE;
		}
		else
		{
			if (CVAR_GET_FLOAT("violence_ablood") != 0.0f)
				return TRUE;
		}
	}
	return FALSE;
}

/* <1abd3e> ../cstrike/dlls/util.cpp:1297 */
int UTIL_PointContents(const Vector &vec)
{
	return POINT_CONTENTS(vec);
}

/* <1af1a3> ../cstrike/dlls/util.cpp:1302 */
void UTIL_BloodStream(const Vector &origin, const Vector &direction, int color, int amount)
{
	if (!UTIL_ShouldShowBlood(color))
		return;

	if (g_Language == LANGUAGE_GERMAN && color == BLOOD_COLOR_RED)
		color = 0;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, origin);
		WRITE_BYTE(TE_BLOODSTREAM);
		WRITE_COORD(origin.x);
		WRITE_COORD(origin.y);
		WRITE_COORD(origin.z);
		WRITE_COORD(direction.x);
		WRITE_COORD(direction.y);
		WRITE_COORD(direction.z);
		WRITE_BYTE(color);
		WRITE_BYTE(Q_min(amount, 255));
	MESSAGE_END();
}

/* <1af25d> ../cstrike/dlls/util.cpp:1324 */
void UTIL_BloodDrips(const Vector &origin, const Vector &direction, int color, int amount)
{
	if (!UTIL_ShouldShowBlood(color))
		return;

	if (color == DONT_BLEED || amount == 0)
		return;

	if (g_Language == LANGUAGE_GERMAN && color == BLOOD_COLOR_RED)
		color = 0;

	if (g_pGameRules->IsMultiplayer())
		amount *= 2;

	if (amount > 255)
		amount = 255;

	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, origin);
		WRITE_BYTE(TE_BLOODSPRITE);
		WRITE_COORD(origin.x);
		WRITE_COORD(origin.y);
		WRITE_COORD(origin.z);
		WRITE_SHORT(g_sModelIndexBloodSpray);
		WRITE_SHORT(g_sModelIndexBloodDrop);
		WRITE_BYTE(color);
		WRITE_BYTE(Q_min(Q_max(3, amount / 10), 16));
	MESSAGE_END();
}

/* <1af310> ../cstrike/dlls/util.cpp:1356 */
Vector UTIL_RandomBloodVector(void)
{
	Vector direction;
	direction.x = RANDOM_FLOAT(-1, 1);
	direction.y = RANDOM_FLOAT(-1, 1);
	direction.z = RANDOM_FLOAT(0, 1);
	return direction;
}

/* <1af471> ../cstrike/dlls/util.cpp:1368 */
void UTIL_BloodDecalTrace(TraceResult *pTrace, int bloodColor)
{
	if (UTIL_ShouldShowBlood(bloodColor))
	{
		if (bloodColor == BLOOD_COLOR_RED)
			UTIL_DecalTrace(pTrace, DECAL_BLOOD1 + RANDOM_LONG(0, 5));
		else
			UTIL_DecalTrace(pTrace, DECAL_YBLOOD1 + RANDOM_LONG(0, 5));
	}
}

/* <1af349> ../cstrike/dlls/util.cpp:1380 */
void UTIL_DecalTrace(TraceResult *pTrace, int decalNumber)
{
	short entityIndex;
	int index;
	int message;

	if (decalNumber < 0)
		return;

	index = gDecals[decalNumber].index;
	if (index < 0 || pTrace->flFraction == 1.0f)
		return;

	if (pTrace->pHit)
	{
		CBaseEntity *pEntity = CBaseEntity::Instance(pTrace->pHit);
		if (pEntity && !pEntity->IsBSPModel())
			return;

		entityIndex = ENTINDEX(pTrace->pHit);
	}
	else
		entityIndex = 0;

	message = TE_DECAL;
	if (entityIndex)
	{
		if (index > 255)
		{
			message = TE_DECALHIGH;
			index -= 256;
		}
	}
	else
	{
		message = TE_WORLDDECAL;
		if (index > 255)
		{
			message = TE_WORLDDECALHIGH;
			index -= 256;
		}
	}
	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(message);
		WRITE_COORD(pTrace->vecEndPos.x);
		WRITE_COORD(pTrace->vecEndPos.y);
		WRITE_COORD(pTrace->vecEndPos.z);
		WRITE_BYTE(index);
	if (entityIndex)
		WRITE_SHORT(entityIndex);
	MESSAGE_END();
}

/* <1af4c8> ../cstrike/dlls/util.cpp:1447 */
void UTIL_PlayerDecalTrace(TraceResult *pTrace, int playernum, int decalNumber, BOOL bIsCustom)
{
	int index;
	if (!bIsCustom)
	{
		if (decalNumber < 0)
			return;

		index = gDecals[decalNumber].index;
		if (index < 0)
			return;
	}
	else
		index = decalNumber;

	if (pTrace->flFraction != 1.0f)
	{
		MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
			WRITE_BYTE(TE_PLAYERDECAL);
			WRITE_BYTE(playernum);
			WRITE_COORD(pTrace->vecEndPos.x);
			WRITE_COORD(pTrace->vecEndPos.y);
			WRITE_COORD(pTrace->vecEndPos.z);
			WRITE_SHORT((int)ENTINDEX(pTrace->pHit));
			WRITE_BYTE(index);
		MESSAGE_END();
	}
}

/* <1af583> ../cstrike/dlls/util.cpp:1477 */
void UTIL_GunshotDecalTrace(TraceResult *pTrace, int decalNumber, bool ClientOnly, entvars_t *pShooter)
{
	if (decalNumber < 0)
		return;

	int index = gDecals[decalNumber].index;
	if (index < 0 || pTrace->flFraction == 1.0f)
		return;

	if (ClientOnly)
		MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, pTrace->vecEndPos, pShooter);
	else
		MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pTrace->vecEndPos);

	WRITE_BYTE(TE_GUNSHOTDECAL);
		WRITE_COORD(pTrace->vecEndPos.x);
		WRITE_COORD(pTrace->vecEndPos.y);
		WRITE_COORD(pTrace->vecEndPos.z);
		WRITE_SHORT((int)ENTINDEX(pTrace->pHit));
		WRITE_BYTE(index);
	MESSAGE_END();
}

/* <1af67d> ../cstrike/dlls/util.cpp:1515 */
void UTIL_Sparks(const Vector &position)
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, position);
		WRITE_BYTE(TE_SPARKS);
		WRITE_COORD(position.x);
		WRITE_COORD(position.y);
		WRITE_COORD(position.z);
	MESSAGE_END();
}

/* <1af6dc> ../cstrike/dlls/util.cpp:1526 */
void UTIL_Ricochet(const Vector &position, float scale)
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, position);
		WRITE_BYTE(TE_ARMOR_RICOCHET);
		WRITE_COORD(position.x);
		WRITE_COORD(position.y);
		WRITE_COORD(position.z);
		WRITE_BYTE((int)(scale * 10.0f));
	MESSAGE_END();
}

/* <1af74a> ../cstrike/dlls/util.cpp:1538 */
BOOL UTIL_TeamsMatch(const char *pTeamName1, const char *pTeamName2)
{
	if (!g_pGameRules->IsTeamplay())
		return TRUE;

	if (*pTeamName1 != '\0' && *pTeamName2 != '\0')
	{
		if (!Q_stricmp(pTeamName1, pTeamName2))
			return TRUE;
	}
	return FALSE;
}

/* <1af78a> ../cstrike/dlls/util.cpp:1555 */
void UTIL_StringToVector(float *pVector, const char *pString)
{
	char *pstr;
	char *pfront;
	char tempString[128];
	int j;

	Q_strcpy(tempString, pString);

#ifdef GAMEDLL_FIXES
	tempString[127] = 0;
#endif // GAMEDLL_FIXES

	pstr = tempString;
	pfront = tempString;

	for (j = 0; j < 3; j++)
	{
		pVector[j] = Q_atof(pfront);

		while (*pstr && *pstr != ' ')
			pstr++;

		if (!*pstr)
			break;

		pstr++;
		pfront = pstr;
	}

	for (j++; j < 3; j++)
		pVector[j] = 0;
}

/* <1af85f> ../cstrike/dlls/util.cpp:1586 */
void UTIL_StringToIntArray(int *pVector, int count, const char *pString)
{
	char *pstr;
	char *pfront;
	char tempString[128];
	int j;

	Q_strcpy(tempString, pString);

	pstr = tempString;
	pfront = tempString;

	for (j = 0; j < count; j++)
	{
		pVector[j] = Q_atoi(pfront);

		while (*pstr && *pstr != ' ')
			pstr++;

		if (!*pstr)
			break;

		pstr++;
		pfront = pstr;
	}

	for (j++; j < count; j++)
		pVector[j] = 0;
}

/* <1af90d> ../cstrike/dlls/util.cpp:1612 */
Vector UTIL_ClampVectorToBox(const Vector &input, const Vector &clampSize)
{
	Vector sourceVector = input;
	if (sourceVector.x > clampSize.x)
		sourceVector.x -= clampSize.x;
	else if (sourceVector.x < -clampSize.x)
		sourceVector.x += clampSize.x;
	else
		sourceVector.x = 0;
	if (sourceVector.y > clampSize.y)
		sourceVector.y -= clampSize.y;
	else if (sourceVector.y < -clampSize.y)
		sourceVector.y += clampSize.y;
	else
		sourceVector.y = 0;
	if (sourceVector.z > clampSize.z)
		sourceVector.z -= clampSize.z;
	else if (sourceVector.z < -clampSize.z)
		sourceVector.z += clampSize.z;
	else
		sourceVector.z = 0;
	return sourceVector.Normalize();
}

/* <1afa45> ../cstrike/dlls/util.cpp:1641 */
float UTIL_WaterLevel(const Vector &position, float minz, float maxz)
{
	Vector midUp;
	float diff;

	midUp = position;
	midUp.z = minz;

	if (UTIL_PointContents(midUp) != CONTENTS_WATER)
		return minz;

	midUp.z = maxz;
	if (UTIL_PointContents(midUp) == CONTENTS_WATER)
		return maxz;

	diff = maxz - minz;
	while (diff > 1)
	{
		midUp.z = minz + diff / 2;
		if (UTIL_PointContents(midUp) == CONTENTS_WATER)
			minz = midUp.z;
		else
			maxz = midUp.z;

		diff = maxz - minz;
	}
	return midUp.z;
}

/* <1afb44> ../cstrike/dlls/util.cpp:1674 */
void UTIL_Bubbles(Vector mins, Vector maxs, int count)
{
	Vector mid = (mins + maxs) * 0.5f;
	float flHeight = UTIL_WaterLevel(mid, mid.z, mid.z + 1024.0f) - mins.z;

	MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, mid);
		WRITE_BYTE(TE_BUBBLES);
		WRITE_COORD(mins.x);
		WRITE_COORD(mins.y);
		WRITE_COORD(mins.z);
		WRITE_COORD(maxs.x);
		WRITE_COORD(maxs.y);
		WRITE_COORD(maxs.z);
		WRITE_COORD(flHeight);
		WRITE_SHORT(g_sModelIndexBubbles);
		WRITE_BYTE(count);
		WRITE_COORD(8);
	MESSAGE_END();
}

/* <1afc62> ../cstrike/dlls/util.cpp:1696 */
void UTIL_BubbleTrail(Vector from, Vector to, int count)
{
	float flHeight = UTIL_WaterLevel(from, from.z, from.z + 256.0f) - from.z;
	if (flHeight < 8.0f)
	{
		flHeight = UTIL_WaterLevel(to, to.z, to.z + 256.0f) - to.z;

		if (flHeight < 8.0f)
			return;

		flHeight = flHeight + to.z - from.z;
	}

	if (count > 255)
		count = 255;

	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_BUBBLETRAIL);
		WRITE_COORD(from.x);
		WRITE_COORD(from.y);
		WRITE_COORD(from.z);
		WRITE_COORD(to.x);
		WRITE_COORD(to.y);
		WRITE_COORD(to.z);
		WRITE_COORD(flHeight);
		WRITE_SHORT(g_sModelIndexBubbles);
		WRITE_BYTE(count);
		WRITE_COORD(8);
	MESSAGE_END();
}

/* <1afcfe> ../cstrike/dlls/util.cpp:1731 */
void UTIL_Remove(CBaseEntity *pEntity)
{
	if (pEntity)
	{
		pEntity->UpdateOnRemove();
		pEntity->pev->flags |= FL_KILLME;
		pEntity->pev->targetname = 0;
	}
}

/* <1afd2c> ../cstrike/dlls/util.cpp:1745 */
NOXREF BOOL UTIL_IsValidEntity(edict_t *pent)
{
	if (!pent || pent->free || (pent->v.flags & FL_KILLME))
		return FALSE;

	return TRUE;
}

/* <1afd5c> ../cstrike/dlls/util.cpp:1753 */
void UTIL_PrecacheOther(const char *szClassname)
{
	edict_t *pent = CREATE_NAMED_ENTITY(MAKE_STRING(szClassname));
	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in UTIL_PrecacheOther\n");
		return;
	}

	CBaseEntity *pEntity = CBaseEntity::Instance(VARS(pent));
	if (pEntity)
	{
		pEntity->Precache();
	}

	REMOVE_ENTITY(pent);
}

/* <1afe5f> ../cstrike/dlls/util.cpp:1774 */
void UTIL_LogPrintf(char *fmt, ...)
{
	va_list argptr;
	static char string[1024];

	va_start(argptr, fmt);
	vsprintf(string, fmt, argptr);
	va_end(argptr);

	ALERT(at_logged, "%s", string);
}

/* <1afebd> ../cstrike/dlls/util.cpp:1791 */
NOXREF float UTIL_DotPoints(const Vector &vecSrc, const Vector &vecCheck, const Vector &vecDir)
{
	Vector2D vec2LOS = (vecCheck - vecSrc).Make2D();
	vec2LOS = vec2LOS.Normalize();
	return DotProduct(vec2LOS, (vecDir.Make2D()));
}

/* <1affcc> ../cstrike/dlls/util.cpp:1805 */
void UTIL_StripToken(const char *pKey, char *pDest)
{
	int i = 0;
	while (pKey[i] && pKey[i] != '#')
	{
		pDest[i] = pKey[i];
		i++;
	}
	pDest[i] = 0;
}

/* <1b003a> ../cstrike/dlls/util.cpp:1847 */
CSaveRestoreBuffer::CSaveRestoreBuffer(void)
{
	m_pdata = NULL;
}

/* <1b0084> ../cstrike/dlls/util.cpp:1853 */
CSaveRestoreBuffer::CSaveRestoreBuffer(SAVERESTOREDATA *pdata)
{
	m_pdata = pdata;
}

/* <1b00d4> ../cstrike/dlls/util.cpp:1859 */
CSaveRestoreBuffer::~CSaveRestoreBuffer(void)
{
	;
}

/* <1b0186> ../cstrike/dlls/util.cpp:1863 */
int CSaveRestoreBuffer::EntityIndex(CBaseEntity *pEntity)
{
	if (!pEntity)
		return -1;

	return EntityIndex(pEntity->pev);
}

/* <1b0214> ../cstrike/dlls/util.cpp:1871 */
int CSaveRestoreBuffer::EntityIndex(entvars_t *pevLookup)
{
	if (!pevLookup)
		return -1;

	return EntityIndex(ENT(pevLookup));
}

/* <1b02a7> ../cstrike/dlls/util.cpp:1878 */
int CSaveRestoreBuffer::EntityIndex(EOFFSET eoLookup)
{
	return EntityIndex(ENT(eoLookup));
}

/* <1b032f> ../cstrike/dlls/util.cpp:1884 */
int CSaveRestoreBuffer::EntityIndex(edict_t *pentLookup)
{
	if (!m_pdata || !pentLookup)
		return -1;

	for (int i = 0; i < m_pdata->tableCount; i++)
	{
		ENTITYTABLE *pTable = &m_pdata->pTable[i];
		if (pTable->pent == pentLookup)
			return i;
	}
	return -1;
}

/* <1b03b7> ../cstrike/dlls/util.cpp:1902 */
edict_t *CSaveRestoreBuffer::EntityFromIndex(int entityIndex)
{
	if (!m_pdata || entityIndex < 0)
		return NULL;

	for (int i = 0; i < m_pdata->tableCount; i++)
	{
		ENTITYTABLE *pTable = &m_pdata->pTable[i];
		if (pTable->id == entityIndex)
			return pTable->pent;
	}
	return NULL;
}

/* <1b03fb> ../cstrike/dlls/util.cpp:1920 */
int CSaveRestoreBuffer::EntityFlagsSet(int entityIndex, int flags)
{
	if (!m_pdata || entityIndex < 0)
		return 0;

	if (!m_pdata || entityIndex < 0 || entityIndex > m_pdata->tableCount)
		return 0;

	m_pdata->pTable[ entityIndex ].flags |= flags;
	return m_pdata->pTable[ entityIndex ].flags;
}

/* <1b0445> ../cstrike/dlls/util.cpp:1933 */
void CSaveRestoreBuffer::BufferRewind(int size)
{
	if (!m_pdata)
		return;

	if (m_pdata->size < size)
		size = m_pdata->size;

	m_pdata->pCurrentData -= size;
	m_pdata->size -= size;
}

#ifndef _WIN32
/* <1abdfb> ../cstrike/dlls/util.cpp:1950 */
extern "C"
{
	inline unsigned _rotr(unsigned val, int shift)
	{
		register unsigned lobit;
		register unsigned num = val;

		shift &= 0x1f;

		while (shift--)
		{
			lobit = num & 1;
			num >>= 1;
			if (lobit)
				num |= 0x80000000;
		}
		return num;
	}
}
#endif

/* <1b04b5> ../cstrike/dlls/util.cpp:1971 */
unsigned int CSaveRestoreBuffer::HashString(const char *pszToken)
{
	unsigned int hash = 0;
	while (*pszToken)
		hash = _rotr(hash, 4) ^ *pszToken++;

	return hash;
}

/* <1b0531> ../cstrike/dlls/util.cpp:1981 */
unsigned short CSaveRestoreBuffer::TokenHash(const char *pszToken)
{
	unsigned short hash = (unsigned short)(HashString(pszToken) % (unsigned)m_pdata->tokenCount);
	for (int i = 0; i < m_pdata->tokenCount; i++)
	{
		int index = hash + i;
		if (index >= m_pdata->tokenCount)
			index -= m_pdata->tokenCount;

		if (!m_pdata->pTokens[index] || !Q_strcmp(pszToken, m_pdata->pTokens[index]))
		{
			m_pdata->pTokens[index] = (char *)pszToken;
			return index;
		}
	}
	ALERT(at_error, "CSaveRestoreBuffer :: TokenHash() is COMPLETELY FULL!");
	return 0;
}

/* <1b06a5> ../cstrike/dlls/util.cpp:2020 */
NOXREF void CSave::WriteData(const char *pname, int size, const char *pdata)
{
	BufferField(pname, size, pdata);
}

/* <1b0860> ../cstrike/dlls/util.cpp:2026 */
NOXREF void CSave::WriteShort(const char *pname, const short *data, int count)
{
	BufferField(pname, sizeof(short) * count, (const char *)data);
}

/* <1b0a7b> ../cstrike/dlls/util.cpp:2032 */
NOXREF void CSave::WriteInt(const char *pname, const int *data, int count)
{
	BufferField(pname, sizeof(int) * count, (const char *)data);
}

/* <1b0c77> ../cstrike/dlls/util.cpp:2038 */
NOXREF void CSave::WriteFloat(const char *pname, const float *data, int count)
{
	BufferField(pname, sizeof(float) * count, (const char *)data);
}

/* <1b0ea5> ../cstrike/dlls/util.cpp:2044 */
NOXREF void CSave::WriteTime(const char *pname, const float *data, int count)
{
	int i;
	BufferHeader(pname, sizeof(float) * count);

	for (i = 0; i < count; i++)
	{
		float tmp = data[0];

		if (m_pdata)
			tmp -= m_pdata->time;

		BufferData((const char *)&tmp, sizeof(float));
		data++;
	}
}

/* <1b1053> ../cstrike/dlls/util.cpp:2065 */
NOXREF void CSave::WriteString(const char *pname, const char *pdata)
{
	BufferField(pname, Q_strlen(pdata) + 1, pdata);
}

/* <1b121f> ../cstrike/dlls/util.cpp:2076 */
NOXREF void CSave::WriteString(const char *pname, const int *stringId, int count)
{
	int i;
	int size = 0;

	for (i = 0; i < count; i++)
		size += Q_strlen(STRING(stringId[i])) + 1;

	BufferHeader(pname, size);
	for (i = 0; i < count; i++)
	{
		const char *pString = STRING(stringId[i]);
		BufferData(pString, Q_strlen(pString) + 1);
	}
}

/* <1b1480> ../cstrike/dlls/util.cpp:2099 */
NOXREF void CSave::WriteVector(const char *pname, const Vector &value)
{
	WriteVector(pname, &value.x, 1);
}

/* <1b1630> ../cstrike/dlls/util.cpp:2105 */
NOXREF void CSave::WriteVector(const char *pname, const float *value, int count)
{
	BufferHeader(pname, sizeof(float) * 3 * count);
	BufferData((const char *)value, sizeof(float) * 3 * count);
}

/* <1b17b9> ../cstrike/dlls/util.cpp:2113 */
NOXREF void CSave::WritePositionVector(const char *pname, const Vector &value)
{
	if (m_pdata && m_pdata->fUseLandmark)
	{
		Vector tmp = value - m_pdata->vecLandmarkOffset;
		WriteVector(pname, tmp);
	}
	WriteVector(pname, value);
}

/* <1b1bde> ../cstrike/dlls/util.cpp:2126 */
NOXREF void CSave::WritePositionVector(const char *pname, const float *value, int count)
{
	BufferHeader(pname, sizeof(float) * 3 * count);
	for (int i = 0; i < count; i++)
	{
		Vector tmp(value[0], value[1], value[2]);

		if (m_pdata && m_pdata->fUseLandmark)
			tmp = tmp - m_pdata->vecLandmarkOffset;

		BufferData((const char *)&tmp.x, sizeof(float) * 3);
		value += 3;
	}
}

/* <1b2ca4> ../cstrike/dlls/util.cpp:2145 */
NOXREF void CSave::WriteFunction(const char *pname, void **data, int count)
{
	const char *functionName = NAME_FOR_FUNCTION((uint32)*data);

	if (functionName)
		BufferField(pname, Q_strlen(functionName) + 1, functionName);
	else
		ALERT(at_error, "Invalid function pointer in entity!");
}

/* <1b2e7a> ../cstrike/dlls/util.cpp:2157 */
void EntvarsKeyvalue(entvars_t *pev, KeyValueData *pkvd)
{
	for (int i = 0; i < ARRAYSIZE(gEntvarsDescription); i++)
	{
		TYPEDESCRIPTION *pField = &gEntvarsDescription[i];

		if (!Q_stricmp(pField->fieldName, pkvd->szKeyName))
		{
			switch (pField->fieldType)
			{
			case FIELD_STRING:
			case FIELD_MODELNAME:
			case FIELD_SOUNDNAME:
				*(string_t *)((char *)pev + pField->fieldOffset) = ALLOC_STRING(pkvd->szValue);
				break;
			case FIELD_FLOAT:
			case FIELD_TIME:
				*(float *)((char *)pev + pField->fieldOffset) = Q_atof(pkvd->szValue);
				break;
			case FIELD_INTEGER:
				*(string_t *)((char *)pev + pField->fieldOffset) = Q_atoi(pkvd->szValue);
				break;
			case FIELD_VECTOR:
			case FIELD_POSITION_VECTOR:
				UTIL_StringToVector((float *)((char *)pev + pField->fieldOffset), pkvd->szValue);
				break;

			default:
			case FIELD_EVARS:
			case FIELD_CLASSPTR:
			case FIELD_EDICT:
			case FIELD_ENTITY:
			case FIELD_POINTER:
				ALERT(at_error, "Bad field in entity!!\n");
				break;
			}
			pkvd->fHandled = TRUE;
			break;
		}
	}
}

/* <1b2f7f> ../cstrike/dlls/util.cpp:2207 */
int CSave::WriteEntVars(const char *pname, entvars_t *pev)
{
	return WriteFields(pname, pev, gEntvarsDescription, ARRAYSIZE(gEntvarsDescription));
}

/* <1b2fc9> ../cstrike/dlls/util.cpp:2214 */
int CSave::WriteFields(const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	int i;
	int emptyCount = 0;

	for (i = 0; i < fieldCount; i++)
	{
		void *pOutputData = ((char *)pBaseData + pFields[i].fieldOffset);
		if (DataEmpty((const char *)pOutputData, pFields[i].fieldSize * gSizes[pFields[i].fieldType]))
			emptyCount++;
	}

	int entityArray[ MAX_ENTITY_ARRAY ];
	int actualCount = fieldCount - emptyCount;

	WriteInt(pname, &actualCount, 1);
	for (i = 0; i < fieldCount; i++)
	{
		TYPEDESCRIPTION *pTest = &pFields[i];
		void *pOutputData = ((char *)pBaseData + pTest->fieldOffset);

		if (DataEmpty((const char *)pOutputData, pTest->fieldSize * gSizes[pTest->fieldType]))
			continue;

		switch (pTest->fieldType)
		{
			case FIELD_FLOAT:
				WriteFloat(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
				break;

			case FIELD_TIME:
				WriteTime(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
				break;

			case FIELD_MODELNAME:
			case FIELD_SOUNDNAME:
			case FIELD_STRING:
				WriteString(pTest->fieldName, (int *)pOutputData, pTest->fieldSize);
				break;

			case FIELD_CLASSPTR:
			case FIELD_EVARS:
			case FIELD_EDICT:
			case FIELD_ENTITY:
			case FIELD_EHANDLE:
			{
				if (pTest->fieldSize > MAX_ENTITY_ARRAY)
					ALERT(at_error, "Can't save more than %d entities in an array!!!\n", MAX_ENTITY_ARRAY);

				for (int j = 0; j < pTest->fieldSize; j++)
				{
					switch (pTest->fieldType)
					{
						case FIELD_EVARS:
							entityArray[j] = EntityIndex(((entvars_t **)pOutputData)[j]);
							break;
						case FIELD_CLASSPTR:
							entityArray[j] = EntityIndex(((CBaseEntity **)pOutputData)[j]);
							break;
						case FIELD_EDICT:
							entityArray[j] = EntityIndex(((edict_t **)pOutputData)[j]);
							break;
						case FIELD_ENTITY:
							entityArray[j] = EntityIndex(((EOFFSET *)pOutputData)[j]);
							break;
						case FIELD_EHANDLE:
							entityArray[j] = EntityIndex((CBaseEntity *)(((EHANDLE *)pOutputData)[j]));
							break;
						default:
							break;
					}
				}
				WriteInt(pTest->fieldName, entityArray, pTest->fieldSize);
				break;
			}
			case FIELD_POSITION_VECTOR:
				WritePositionVector(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
				break;
			case FIELD_VECTOR:
				WriteVector(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
				break;
			case FIELD_BOOLEAN:
			case FIELD_INTEGER:
				WriteInt(pTest->fieldName, (int *)pOutputData, pTest->fieldSize);
				break;
			case FIELD_SHORT:
				WriteData(pTest->fieldName, 2 * pTest->fieldSize, ((char *)pOutputData));
				break;
			case FIELD_CHARACTER:
				WriteData(pTest->fieldName, pTest->fieldSize, ((char *)pOutputData));
				break;
			case FIELD_POINTER:
				WriteInt(pTest->fieldName, (int *)(char *)pOutputData, pTest->fieldSize);
				break;
			case FIELD_FUNCTION:
				WriteFunction(pTest->fieldName, &pOutputData, pTest->fieldSize);
				break;

			default: ALERT(at_error, "Bad field type\n");
		}
	}
	return 1;
}

/* <1b3e49> ../cstrike/dlls/util.cpp:2324 */
NOXREF void CSave::BufferString(char *pdata, int len)
{
	char c = 0;
	BufferData(pdata, len);
	BufferData(&c, 1);
}

/* <1b3f5d> ../cstrike/dlls/util.cpp:2333 */
NOXREF int CSave::DataEmpty(const char *pdata, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (pdata[i])
			return 0;
	}
	return 1;
}

/* <1b3f9f> ../cstrike/dlls/util.cpp:2344 */
void CSave::BufferField(const char *pname, int size, const char *pdata)
{
	BufferHeader(pname, size);
	BufferData(pdata, size);
}

/* <1b4128> ../cstrike/dlls/util.cpp:2351 */
void CSave::BufferHeader(const char *pname, int size)
{
	short hashvalue = TokenHash(pname);
	if (size > (1 << (sizeof(short) * 8)))
		ALERT(at_error, "CSave :: BufferHeader() size parameter exceeds 'short'!");

	BufferData((const char *)&size, sizeof(short));
	BufferData((const char *)&hashvalue, sizeof(short));
}

/* <1b421f> ../cstrike/dlls/util.cpp:2361 */
void CSave::BufferData(const char *pdata, int size)
{
	if (!m_pdata)
		return;

	if (m_pdata->size + size > m_pdata->bufferSize)
	{
		ALERT(at_error, "Save/Restore overflow!");
		m_pdata->size = m_pdata->bufferSize;
		return;
	}

	Q_memcpy(m_pdata->pCurrentData, pdata, size);
	m_pdata->pCurrentData += size;
	m_pdata->size += size;
}

/* <1b427f> ../cstrike/dlls/util.cpp:2386 */
int CRestore::ReadField(void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount, int startField, int size, char *pName, void *pData)
{
	float time = 0.0f;
	Vector position = Vector(0, 0, 0);

	if (m_pdata)
	{
		time = m_pdata->time;
		if (m_pdata->fUseLandmark)
			position = m_pdata->vecLandmarkOffset;
	}
	for (int i = 0; i < fieldCount; i++)
	{
		int fieldNumber = (i + startField) % fieldCount;
		TYPEDESCRIPTION *pTest = &pFields[fieldNumber];

		if (!Q_stricmp(pTest->fieldName, pName))
		{
			if (!m_global || !(pTest->flags & FTYPEDESC_GLOBAL))
			{
				for (int j = 0; j < pTest->fieldSize; j++)
				{
					void *pOutputData = ((char *)pBaseData + pTest->fieldOffset + (j * gSizes[pTest->fieldType]));
					void *pInputData = (char *)pData + j * gSizes[pTest->fieldType];

					switch (pTest->fieldType)
					{
						case FIELD_TIME:
						{
							float timeData = *(float *)pInputData;
							timeData += time;
							*((float *)pOutputData) = timeData;
							break;
						}
						case FIELD_FLOAT: *((float *)pOutputData) = *(float *)pInputData; break;
						case FIELD_MODELNAME:
						case FIELD_SOUNDNAME:
						case FIELD_STRING:
						{
							char *pString = (char *)pData;
							for (int stringCount = 0; stringCount < j; stringCount++)
							{
								while (*pString)
									pString++;

								pString++;
							}

							pInputData = pString;
							if (!Q_strlen((char *)pInputData))
								*((int *)pOutputData) = 0;
							else
							{
								int string = ALLOC_STRING((char *)pInputData);
								*((int *)pOutputData) = string;

								if (!FStringNull(string) && m_precache)
								{
									if (pTest->fieldType == FIELD_MODELNAME)
										PRECACHE_MODEL((char *)STRING(string));
									else if (pTest->fieldType == FIELD_SOUNDNAME)
										PRECACHE_SOUND((char *)STRING(string));
								}
							}
							break;
						}
						case FIELD_EVARS:
						{
							int entityIndex = *(int *)pInputData;
							edict_t *pent = EntityFromIndex(entityIndex);

							if (pent)
								*((entvars_t **)pOutputData) = VARS(pent);
							else
								*((entvars_t **)pOutputData) = NULL;

							break;
						}
						case FIELD_CLASSPTR:
						{
							int entityIndex = *(int *)pInputData;
							edict_t *pent = EntityFromIndex(entityIndex);

							if (pent)
								*((CBaseEntity **)pOutputData) = CBaseEntity::Instance(pent);
							else
								*((CBaseEntity **)pOutputData) = NULL;

							break;
						}
						case FIELD_EDICT:
						{
							int entityIndex = *(int *)pInputData;
							edict_t *pent = EntityFromIndex(entityIndex);
							*((edict_t **)pOutputData) = pent;
							break;
						}
						case FIELD_EHANDLE:
						{
							pOutputData = (char *)pOutputData + j * (sizeof(EHANDLE) - gSizes[pTest->fieldType]);
							int entityIndex = *(int *)pInputData;
							edict_t *pent = EntityFromIndex(entityIndex);

							if (pent)
								*((EHANDLE *)pOutputData) = CBaseEntity::Instance(pent);
							else
								*((EHANDLE *)pOutputData) = NULL;

							break;
						}
						case FIELD_ENTITY:
						{
							int entityIndex = *(int *)pInputData;
							edict_t *pent = EntityFromIndex(entityIndex);

							if (pent)
								*((EOFFSET *)pOutputData) = OFFSET(pent);
							else
								*((EOFFSET *)pOutputData) = 0;

							break;
						}
						case FIELD_VECTOR:
						{
							((float *)pOutputData)[0] = ((float *)pInputData)[0];
							((float *)pOutputData)[1] = ((float *)pInputData)[1];
							((float *)pOutputData)[2] = ((float *)pInputData)[2];
							break;
						}
						case FIELD_POSITION_VECTOR:
						{
							((float *)pOutputData)[0] = ((float *)pInputData)[0] + position.x;
							((float *)pOutputData)[1] = ((float *)pInputData)[1] + position.y;
							((float *)pOutputData)[2] = ((float *)pInputData)[2] + position.z;
							break;
						}
						case FIELD_BOOLEAN:
						case FIELD_INTEGER:
							*((int *)pOutputData) = *(int *)pInputData;
							break;
						case FIELD_SHORT:
							*((short *)pOutputData) = *(short *)pInputData;
							break;
						case FIELD_CHARACTER:
							*((char *)pOutputData) = *(char *)pInputData;
							break;
						case FIELD_POINTER:
							*((int *)pOutputData) = *(int *)pInputData;
							break;
						case FIELD_FUNCTION:
						{
							if (!Q_strlen((char *)pInputData))
								*((int *)pOutputData) = 0;
							else
								*((int *)pOutputData) = FUNCTION_FROM_NAME((char *)pInputData);

							break;
						}
						default:
							ALERT(at_error, "Bad field type\n");
							break;
					}
				}
			}
			return fieldNumber;
		}
	}
	return -1;
}

/* <1b4a80> ../cstrike/dlls/util.cpp:2547 */
int CRestore::ReadEntVars(const char *pname, entvars_t *pev)
{
	return ReadFields(pname, pev, gEntvarsDescription, ARRAYSIZE(gEntvarsDescription));
}

/* <1b4884> ../cstrike/dlls/util.cpp:2553 */
int CRestore::ReadFields(const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	unsigned short i = ReadShort();
	unsigned short token = ReadShort();

	if (token != TokenHash(pname))
	{
		BufferRewind(2 * sizeof(short));
		return 0;
	}

	int fileCount = ReadInt();
	int lastField = 0;

	for (i = 0; i < fieldCount; i++)
	{
		if (!m_global || !(pFields[i].flags & FTYPEDESC_GLOBAL))
			Q_memset(((char *)pBaseData + pFields[i].fieldOffset), 0, pFields[i].fieldSize * gSizes[pFields[i].fieldType]);
	}
	for (i = 0; i < fileCount; i++)
	{
		HEADER header;
		BufferReadHeader(&header);

		lastField = ReadField(pBaseData, pFields, fieldCount, lastField, header.size, m_pdata->pTokens[header.token], header.pData);
		lastField++;
	}
	return 1;
}

/* <1b46b1> ../cstrike/dlls/util.cpp:2595 */
NOXREF void CRestore::BufferReadHeader(HEADER *pheader)
{
	pheader->size = ReadShort();
	pheader->token = ReadShort();
	pheader->pData = BufferPointer();

	BufferSkipBytes(pheader->size);
}

/* <1b4654> ../cstrike/dlls/util.cpp:2605 */
NOXREF short CRestore::ReadShort(void)
{
	short tmp = 0;
	BufferReadBytes((char *)&tmp, sizeof(short));
	return tmp;
}

/* <1b45f5> ../cstrike/dlls/util.cpp:2614 */
NOXREF int CRestore::ReadInt(void)
{
	int tmp = 0;
	BufferReadBytes((char *)&tmp, sizeof(int));
	return tmp;
}

/* <1b4f84> ../cstrike/dlls/util.cpp:2623 */
NOXREF int CRestore::ReadNamedInt(const char *pName)
{
	HEADER header;
	BufferReadHeader(&header);
	return ((int *)header.pData)[0];
}

/* <1b4776> ../cstrike/dlls/util.cpp:2631 */
NOXREF char *CRestore::ReadNamedString(const char *pName)
{
	HEADER header;
	BufferReadHeader(&header);
	return (char *)header.pData;
}

/* <1b453a> ../cstrike/dlls/util.cpp:2644 */
NOXREF char *CRestore::BufferPointer(void)
{
	if (!m_pdata)
		return NULL;

	return m_pdata->pCurrentData;
}

/* <1b455c> ../cstrike/dlls/util.cpp:2652 */
void CRestore::BufferReadBytes(char *pOutput, int size)
{
	if (!m_pdata || Empty())
		return;

	if ((m_pdata->size + size) > m_pdata->bufferSize)
	{
		ALERT(at_error, "Restore overflow!");
		m_pdata->size = m_pdata->bufferSize;
		return;
	}

	if (pOutput)
		Q_memcpy(pOutput, m_pdata->pCurrentData, size);

	m_pdata->pCurrentData += size;
	m_pdata->size += size;
}

/* <1b5092> ../cstrike/dlls/util.cpp:2673 */
NOXREF void CRestore::BufferSkipBytes(int bytes)
{
	BufferReadBytes(NULL, bytes);
}

/* <1b50bc> ../cstrike/dlls/util.cpp:2678 */
NOXREF int CRestore::BufferSkipZString(void)
{
	if (!m_pdata)
		return 0;

	int maxLen = m_pdata->bufferSize - m_pdata->size;
	int len = 0;
	char *pszSearch = m_pdata->pCurrentData;

	while (*pszSearch++ && len < maxLen)
		len++;

	len++;
	BufferSkipBytes(len);
	return len;
}

/* <1b5144> ../cstrike/dlls/util.cpp:2700 */
NOXREF int CRestore::BufferCheckZString(const char *string)
{
	if (!m_pdata)
		return 0;

	int maxLen = m_pdata->bufferSize - m_pdata->size;
	int len = Q_strlen(string);

	if (len <= maxLen)
	{
		if (!strncmp(string, m_pdata->pCurrentData, len))
			return 1;
	}
	return 0;
}

/* <1b51a7> ../cstrike/dlls/util.cpp:2715 */
char UTIL_TextureHit(TraceResult *ptr, Vector vecSrc, Vector vecEnd)
{
	char chTextureType;
	float rgfl1[3];
	float rgfl2[3];
	const char *pTextureName;
	char szbuffer[64];
	CBaseEntity *pEntity = CBaseEntity::Instance(ptr->pHit);

	if (pEntity && pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
		return CHAR_TEX_FLESH;

	vecSrc.CopyToArray(rgfl1);
	vecEnd.CopyToArray(rgfl2);

	if (pEntity)
		pTextureName = TRACE_TEXTURE(ENT(pEntity->pev), rgfl1, rgfl2);
	else
		pTextureName = TRACE_TEXTURE(ENT(0), rgfl1, rgfl2);

	if (pTextureName)
	{
		if (*pTextureName == '-' || *pTextureName == '+')
			pTextureName += 2;

		if (*pTextureName == '{' || *pTextureName == '!' || *pTextureName == '~' || *pTextureName == ' ')
			pTextureName++;

		Q_strcpy(szbuffer, pTextureName);
		szbuffer[16] = 0;
		chTextureType = TEXTURETYPE_Find(szbuffer);
	}
	else
		chTextureType = 0;
	return chTextureType;
}

/* <1b5330> ../cstrike/dlls/util.cpp:2767 */
NOXREF int GetPlayerTeam(int index)
{
	CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex(index);
	if (pPlayer != NULL)
	{
		return pPlayer->m_iTeam;
	}

	return 0;
}

/* <1b5412> ../cstrike/dlls/util.cpp:2775 */
bool UTIL_IsGame(const char *gameName)
{
	if (gameName != NULL)
	{
		static char gameDir[256];
		GET_GAME_DIR(gameDir);
		return (Q_stricmp(gameDir, gameName) == 0);
	}

	return false;
}

/* <1b5470> ../cstrike/dlls/util.cpp:2802 */
float_precision UTIL_GetPlayerGaitYaw(int playerIndex)
{
	CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex(playerIndex);
	if (pPlayer != NULL)
	{
		return pPlayer->m_flGaityaw;
	}

	return 0;
}
