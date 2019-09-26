#include "precompiled.h"

unsigned int glSeed;
CUtlVector<hash_item_t> stringsHashTable;

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

int g_groupmask = 0;
int g_groupop = 0;

float UTIL_WeaponTimeBase()
{
#ifdef CLIENT_WEAPONS
	return 0.0;
#else
	return gpGlobals->time;
#endif
}

unsigned int U_Random()
{
	glSeed *= 69069;
	glSeed += seed_table[glSeed & 0xFF] + 1;
	return (glSeed & 0xFFFFFFF);
}

void U_Srand(unsigned int seed)
{
	glSeed = seed_table[seed & 0xFF];
}

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

float UTIL_SharedRandomFloat(unsigned int seed, float low, float high)
{
	unsigned int range = high - low;
	U_Srand((unsigned int)seed + *(unsigned int *)&low + *(unsigned int *)&high);

	U_Random();
	U_Random();

	if (range)
	{
		int tensixrand = U_Random() & 0xFFFFu;
		float offset = float(tensixrand) / 0x10000u;
		return (low + offset * range);
	}

	return low;
}

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

void UTIL_SetGroupTrace(int groupmask, int op)
{
	g_groupmask = groupmask;
	g_groupop = op;

	ENGINE_SETGROUPMASK(groupmask, op);
}

void UTIL_UnsetGroupTrace()
{
	g_groupmask = 0;
	g_groupop = 0;

	ENGINE_SETGROUPMASK(0, 0);
}

NOXREF UTIL_GroupTrace::UTIL_GroupTrace(int groupmask, int op)
{
	m_oldgroupmask = g_groupmask;
	m_oldgroupop = g_groupop;

	g_groupmask = groupmask;
	g_groupop = op;

	ENGINE_SETGROUPMASK(groupmask, op);
}

NOXREF UTIL_GroupTrace::~UTIL_GroupTrace()
{
	g_groupmask = m_oldgroupmask;
	g_groupop = m_oldgroupop;

	ENGINE_SETGROUPMASK(g_groupmask, g_groupop);
}

NOXREF BOOL UTIL_GetNextBestWeapon(CBasePlayer *pPlayer, CBasePlayerItem *pCurrentWeapon)
{
	return g_pGameRules->GetNextBestWeapon(pPlayer,pCurrentWeapon);
}

float UTIL_AngleMod(float a)
{
	if (a < 0.0f)
		a = a + 360.0f * (int(a / 360.0f) + 1);
	else if (a >= 360.0f)
		a = a - 360.0f * int(a / 360.0f);
	return a;
}

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

Vector UTIL_VecToAngles(const Vector &vec)
{
	float rgflVecOut[3];
	VEC_TO_ANGLES(vec, rgflVecOut);
	return Vector(rgflVecOut);
}

NOXREF void UTIL_MoveToOrigin(edict_t *pent, const Vector &vecGoal, float flDist, int iMoveType)
{
	float rgfl[3];
	vecGoal.CopyToArray(rgfl);
	MOVE_TO_ORIGIN(pent, rgfl, flDist, iMoveType);
}

int UTIL_EntitiesInBox(CBaseEntity **pList, int listMax, const Vector &mins, const Vector &maxs, int flagMask)
{
	edict_t *pEdict = INDEXENT(1);
	int count = 0;

	if (!pEdict)
		return 0;

	for (int i = 1; i < gpGlobals->maxEntities; i++, pEdict++)
	{
		if (pEdict->free)
			continue;

		if (flagMask && !(pEdict->v.flags & flagMask))
			continue;

		CBaseEntity *pEntity = CBaseEntity::Instance(pEdict);
		if (!pEntity)
			continue;

		if (!pEntity->Intersects(mins, maxs))
			continue;

		pList[count++] = pEntity;

		if (count >= listMax)
			break;
	}

	return count;
}

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

		if (!(pEdict->v.flags & (FL_CLIENT | FL_MONSTER)))
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

		pList[count++] = pEntity;

		if (count >= listMax)
			return count;
	}

	return count;
}

CBaseEntity *UTIL_FindEntityInSphere(CBaseEntity *pStartEntity, const Vector &vecCenter, float flRadius)
{
	edict_t	*pentEntity;
	if (pStartEntity)
		pentEntity = pStartEntity->edict();
	else
		pentEntity = nullptr;

	pentEntity = FIND_ENTITY_IN_SPHERE(pentEntity, vecCenter, flRadius);
	if (!FNullEnt(pentEntity))
	{
		return CBaseEntity::Instance(pentEntity);
	}

	return nullptr;
}

CBaseEntity *UTIL_FindEntityByString_Old(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue)
{
	edict_t	*pentEntity;
	if (pStartEntity)
		pentEntity = pStartEntity->edict();
	else
		pentEntity = nullptr;

	pentEntity = FIND_ENTITY_BY_STRING(pentEntity, szKeyword, szValue);
	if (!FNullEnt(pentEntity))
	{
		return CBaseEntity::Instance(pentEntity);
	}

	return nullptr;
}

CBaseEntity *EXT_FUNC UTIL_FindEntityByString(CBaseEntity *pStartEntity, const char *szKeyword, const char *szValue)
{
	edict_t	*pentEntity;
	int startEntityIndex;

	if (pStartEntity)
		pentEntity = pStartEntity->edict();
	else
		pentEntity = nullptr;

	startEntityIndex = ENTINDEX(pentEntity);

	// it best each entity list
	if (*szKeyword == 'c')
	{
		int hash;
		hash_item_t *item;
		int count;

		hash = CaseInsensitiveHash(szValue, stringsHashTable.Count());
		count = stringsHashTable.Count();
		item = &stringsHashTable[hash];

		if (!item->pev)
		{
			item->lastHash = nullptr;
			return nullptr;
		}

		while (item->pev)
		{
			if (!Q_strcmp(STRING(item->pev->classname), szValue))
				break;

			hash = (hash + 1) % count;
			item = &stringsHashTable[hash];
		}

		if (!item->pev)
		{
			item->lastHash = nullptr;
			return nullptr;
		}

		if (pStartEntity)
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
					stringsHashTable[hash].lastHash = nullptr;
					return nullptr;
				}
			}
		}

		stringsHashTable[hash].lastHash = item;
		pentEntity = ENT(item->pev);
	}
	else
		pentEntity = FIND_ENTITY_BY_STRING(pentEntity, szKeyword, szValue);

	if (!FNullEnt(pentEntity))
	{
		return CBaseEntity::Instance(pentEntity);
	}

	return nullptr;
}

CBaseEntity *UTIL_FindEntityByClassname(CBaseEntity *pStartEntity, const char *szName)
{
	return UTIL_FindEntityByString(pStartEntity, "classname", szName);
}

CBaseEntity *UTIL_FindEntityByTargetname(CBaseEntity *pStartEntity, const char *szName)
{
	return UTIL_FindEntityByString(pStartEntity, "targetname", szName);
}

CBaseEntity *UTIL_FindEntityGeneric(const char *szWhatever, const Vector &vecSrc, float flRadius)
{
	CBaseEntity *pSearch = nullptr;
	CBaseEntity *pEntity = UTIL_FindEntityByTargetname(nullptr, szWhatever);
	if (pEntity)
		return pEntity;

	float flMaxDist2 = flRadius * flRadius;
	while ((pSearch = UTIL_FindEntityByClassname(pSearch, szWhatever)))
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

#ifndef REGAMEDLL_FIXES
CBasePlayer *EXT_FUNC UTIL_PlayerByIndex(int playerIndex)
{
	CBasePlayer *pPlayer = nullptr;
	if (playerIndex > 0 && playerIndex <= gpGlobals->maxClients)
	{
		edict_t *pPlayerEdict = INDEXENT(playerIndex);
		if (pPlayerEdict && !pPlayerEdict->free)
			pPlayer = CBasePlayer::Instance(pPlayerEdict);
	}

	return pPlayer;
}
#endif

void UTIL_MakeVectors(const Vector &vecAngles)
{
	MAKE_VECTORS(vecAngles);
}

void UTIL_MakeAimVectors(const Vector &vecAngles)
{
	float rgflVec[3];
	vecAngles.CopyToArray(rgflVec);
	rgflVec[0] = -rgflVec[0];
	MAKE_VECTORS(rgflVec);
}

void UTIL_MakeInvVectors(const Vector &vec, globalvars_t *pgv)
{
	MAKE_VECTORS(vec);

	pgv->v_right = pgv->v_right * -1;

	SWAP(pgv->v_forward.y, pgv->v_right.x);
	SWAP(pgv->v_forward.z, pgv->v_up.x);
	SWAP(pgv->v_right.z, pgv->v_up.y);
}

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

unsigned short FixedUnsigned16(float value, float scale)
{
	int output = value * scale;
	if (output < 0)
		output = 0;

	if (output > USHRT_MAX)
		output = USHRT_MAX;

	return (unsigned short)output;
}

short FixedSigned16(float value, float scale)
{
	int output = value * scale;
	if (output > SHRT_MAX)
		output = SHRT_MAX;

	if (output < SHRT_MIN)
		output = SHRT_MIN;

	return (short)output;
}

void UTIL_ScreenShake(const Vector &center, float amplitude, float frequency, float duration, float radius)
{
	int i;
	float localAmplitude;
	ScreenShake shake;

	shake.duration = FixedUnsigned16(duration, (1<<12));
	shake.frequency = FixedUnsigned16(frequency, (1<<8));

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

			MESSAGE_BEGIN(MSG_ONE, gmsgShake, nullptr, pPlayer->edict());
				WRITE_SHORT(shake.amplitude);
				WRITE_SHORT(shake.duration);
				WRITE_SHORT(shake.frequency);
			MESSAGE_END();
		}
	}
}

NOXREF void UTIL_ScreenShakeAll(const Vector &center, float amplitude, float frequency, float duration)
{
	UTIL_ScreenShake(center, amplitude, frequency, duration, 0);
}

void UTIL_ScreenFadeBuild(ScreenFade &fade, const Vector &color, float fadeTime, float fadeHold, int alpha, int flags)
{
	fade.duration = FixedUnsigned16(fadeTime, 1<<12);
	fade.holdTime = FixedUnsigned16(fadeHold, 1<<12);
	fade.r = int(color.x);
	fade.g = int(color.y);
	fade.b = int(color.z);
	fade.a = alpha;
	fade.fadeFlags = flags;
}

void UTIL_ScreenFadeWrite(const ScreenFade &fade, CBaseEntity *pEntity)
{
	if (!pEntity || !pEntity->IsNetClient())
		return;

	MESSAGE_BEGIN(MSG_ONE, gmsgFade, nullptr, pEntity->edict());
		WRITE_SHORT(fade.duration);
		WRITE_SHORT(fade.holdTime);
		WRITE_SHORT(fade.fadeFlags);
		WRITE_BYTE(fade.r);
		WRITE_BYTE(fade.g);
		WRITE_BYTE(fade.b);
		WRITE_BYTE(fade.a);
	MESSAGE_END();
}

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

void UTIL_ScreenFade(CBaseEntity *pEntity, const Vector &color, float fadeTime, float fadeHold, int alpha, int flags)
{
	ScreenFade fade;
	UTIL_ScreenFadeBuild(fade, color, fadeTime, fadeHold, alpha, flags);
	UTIL_ScreenFadeWrite(fade, pEntity);
}

void UTIL_HudMessage(CBaseEntity *pEntity, const hudtextparms_t &textparms, const char *pMessage)
{
	if (!pEntity || !pEntity->IsNetClient())
		return;

	MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, nullptr, pEntity->edict());
		WRITE_BYTE(TE_TEXTMESSAGE);
		WRITE_BYTE(textparms.channel & 0xFF);
		WRITE_SHORT(FixedSigned16(textparms.x, (1<<13)));
		WRITE_SHORT(FixedSigned16(textparms.y, (1<<13)));
		WRITE_BYTE(textparms.effect);
		WRITE_BYTE(textparms.r1);
		WRITE_BYTE(textparms.g1);
		WRITE_BYTE(textparms.b1);
		WRITE_BYTE(textparms.a1);
		WRITE_BYTE(textparms.r2);
		WRITE_BYTE(textparms.g2);
		WRITE_BYTE(textparms.b2);
		WRITE_BYTE(textparms.a2);
		WRITE_SHORT(FixedUnsigned16(textparms.fadeinTime, (1<<8)));
		WRITE_SHORT(FixedUnsigned16(textparms.fadeoutTime, (1<<8)));
		WRITE_SHORT(FixedUnsigned16(textparms.holdTime, (1<<8)));

		if (textparms.effect == 2)
			WRITE_SHORT(FixedUnsigned16(textparms.fxTime, (1<<8)));

		if (!pMessage)
			WRITE_STRING(" ");
		else
		{
			if (Q_strlen(pMessage) >= 512)
			{
				char tmp[512];
				Q_strlcpy(tmp, pMessage);
				WRITE_STRING(tmp);
			}
			else
			{
				WRITE_STRING(pMessage);
			}
		}
	MESSAGE_END();
}

void UTIL_HudMessageAll(const hudtextparms_t &textparms, const char *pMessage)
{
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (pPlayer)
		{
			UTIL_HudMessage(pPlayer, textparms, pMessage);
		}
	}
}

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

void ClientPrint(entvars_t *client, int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgTextMsg, nullptr, client);
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

void UTIL_Log(const char *fmt, ...)
{
	va_list ap;
	static char string[1024];

	va_start(ap, fmt);
	Q_vsnprintf(string, sizeof(string), fmt, ap);
	va_end(ap);

	if (Q_strlen(string) < sizeof(string) - 2)
		Q_strcat(string, "\n");
	else
		string[Q_strlen(string) - 1] = '\n';

	FILE *fp = fopen("regamedll.log", "at");
	if (fp)
	{
		fprintf(fp, "%s", string);
		fclose(fp);
	}
}

void UTIL_ServerPrint(const char *fmt, ...)
{
#ifdef PLAY_GAMEDLL
	// Check is null, test the demo started before than searches pointer to refs
	if (&g_engfuncs == nullptr || g_engfuncs.pfnServerPrint == nullptr)
		return;
#endif

	static char string[1024];
	va_list ap;
	va_start(ap, fmt);
	Q_vsnprintf(string, sizeof(string), fmt, ap);
	va_end(ap);

	if (Q_strlen(string) < sizeof(string) - 2)
		Q_strcat(string, "\n");
	else
		string[Q_strlen(string) - 1] = '\n';

	SERVER_PRINT(string);
}

void UTIL_PrintConsole(edict_t *pEdict, const char *fmt, ...)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pEdict);
	if (!pEntity || !pEntity->IsNetClient())
		return;

	static char string[1024];

	va_list ap;
	va_start(ap, fmt);
	Q_vsnprintf(string, sizeof(string), fmt, ap);
	va_end(ap);

	if (Q_strlen(string) < sizeof(string) - 2)
		Q_strcat(string, "\n");
	else
		string[Q_strlen(string) - 1] = '\n';

	ClientPrint(pEntity->pev, HUD_PRINTCONSOLE, string);
}

void UTIL_SayText(edict_t *pEdict, const char *fmt, ...)
{
	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pEdict);
	if (!pEntity || !pEntity->IsNetClient())
		return;

	static char string[1024];

	va_list ap;
	va_start(ap, fmt);
	Q_vsnprintf(string, sizeof(string), fmt, ap);
	va_end(ap);

	if (Q_strlen(string) < sizeof(string) - 2)
		Q_strcat(string, "\n");
	else
		string[Q_strlen(string) - 1] = '\n';

	MESSAGE_BEGIN(MSG_ONE, gmsgSayText, nullptr, pEntity->edict());
		WRITE_BYTE(pEntity->entindex());
		WRITE_STRING(string);
	MESSAGE_END();
}

void UTIL_SayTextAll(const char *pText, CBaseEntity *pEntity)
{
	MESSAGE_BEGIN(MSG_ALL, gmsgSayText);
		WRITE_BYTE(pEntity->entindex());
		WRITE_STRING(pText);
	MESSAGE_END();
}

char *UTIL_dtos1(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

char *UTIL_dtos2(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

NOXREF char *UTIL_dtos3(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

NOXREF char *UTIL_dtos4(int d)
{
	static char buf[8];
	Q_sprintf(buf, "%d", d);
	return buf;
}

void UTIL_ShowMessageArgs(const char *pString, CBaseEntity *pPlayer, CUtlVector<char *> *args, bool isHint)
{
	if (!pPlayer)
		return;

	if (!pPlayer->IsNetClient())
		return;

	if (args)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgHudTextArgs, nullptr, pPlayer->pev);
			WRITE_STRING(pString);
			WRITE_BYTE(isHint);
			WRITE_BYTE(args->Count());

		for (int i = 0; i < args->Count(); i++)
			WRITE_STRING((*args)[i]);

		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgHudTextPro, nullptr, pPlayer->pev);
			WRITE_STRING(pString);
			WRITE_BYTE(isHint);
		MESSAGE_END();
	}
}

void UTIL_ShowMessage(const char *pString, CBaseEntity *pEntity, bool isHint)
{
	if (!pEntity || !pEntity->IsNetClient())
		return;

	MESSAGE_BEGIN(MSG_ONE, gmsgHudTextPro, nullptr, pEntity->edict());
		WRITE_STRING(pString);
		WRITE_BYTE(int(isHint));
	MESSAGE_END();
}

void UTIL_ShowMessageAll(const char *pString, bool isHint)
{
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (pPlayer)
			UTIL_ShowMessage(pString, pPlayer, isHint);
	}
}

void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters), pentIgnore, ptr);
}

// OVERLOAD
void UTIL_TraceLine(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, IGNORE_GLASS ignoreGlass, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_LINE(vecStart, vecEnd, (igmon == ignore_monsters) | (ignoreGlass ? 0x100 : 0), pentIgnore, ptr);
}

void UTIL_TraceHull(const Vector &vecStart, const Vector &vecEnd, IGNORE_MONSTERS igmon, int hullNumber, edict_t *pentIgnore, TraceResult *ptr)
{
	TRACE_HULL(vecStart, vecEnd, (igmon == ignore_monsters), hullNumber, pentIgnore, ptr);
}

void UTIL_TraceModel(const Vector &vecStart, const Vector &vecEnd, int hullNumber, edict_t *pentModel, TraceResult *ptr)
{
	TRACE_MODEL(vecStart, vecEnd, hullNumber, pentModel, ptr);
}

NOXREF TraceResult UTIL_GetGlobalTrace()
{
	TraceResult tr;

	tr.flFraction = gpGlobals->trace_fraction;
	tr.fInWater = int(gpGlobals->trace_inwater);
	tr.fAllSolid = int(gpGlobals->trace_allsolid);
	tr.fStartSolid = int(gpGlobals->trace_startsolid);
	tr.fInOpen = int(gpGlobals->trace_inopen);
	tr.vecEndPos = gpGlobals->trace_endpos;
	tr.flPlaneDist = gpGlobals->trace_plane_dist;
	tr.vecPlaneNormal = gpGlobals->trace_plane_normal;
	tr.iHitgroup = gpGlobals->trace_hitgroup;
	tr.pHit = gpGlobals->trace_ent;

	return tr;
}

void UTIL_SetSize(entvars_t *pev, const Vector &vecMin, const Vector &vecMax)
{
	SET_SIZE(ENT(pev), vecMin, vecMax);
}

float UTIL_VecToYaw(const Vector &vec)
{
	return VEC_TO_YAW(vec);
}

void UTIL_SetOrigin(entvars_t *pev, const Vector &vecOrigin)
{
	edict_t *pEdict = ENT(pev);
	if (pEdict)
	{
		SET_ORIGIN(pEdict, vecOrigin);
	}
}

NOXREF void UTIL_ParticleEffect(const Vector &vecOrigin, const Vector &vecDirection, ULONG ulColor, ULONG ulCount)
{
	PARTICLE_EFFECT(vecOrigin, vecDirection, float(ulColor), float(ulCount));
}

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

real_t UTIL_ApproachAngle(float target, float value, float speed)
{
	target = UTIL_AngleMod(target);

#ifdef REGAMEDLL_FIXES
	value = UTIL_AngleMod(value);
#else
	value = UTIL_AngleMod(target);
#endif

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

real_t UTIL_AngleDistance(float next, float cur)
{
	real_t delta;

	delta = next - cur;

	if (delta < -180.0f)
		delta += 360.0f;

	else if (delta > 180.0f)
		delta -= 360.0f;

	return delta;
}

float UTIL_SplineFraction(float value, float scale)
{
	float valueSquared = value * scale;
	return 3.0f * (valueSquared * valueSquared) - (valueSquared * valueSquared * valueSquared + valueSquared * valueSquared * valueSquared);
}

char *UTIL_VarArgs(char *format, ...)
{
	va_list argptr;
	static char string[1024];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	return string;
}

NOXREF Vector UTIL_GetAimVector(edict_t *pent, float flSpeed)
{
	Vector tmp;
	GET_AIM_VECTOR(pent, flSpeed, tmp);
	return tmp;
}

bool UTIL_IsMasterTriggered(string_t sMaster, CBaseEntity *pActivator)
{
	if (sMaster)
	{
		edict_t *pentTarget = FIND_ENTITY_BY_TARGETNAME(nullptr, STRING(sMaster));
		if (!FNullEnt(pentTarget))
		{
			CBaseEntity *pMaster = CBaseEntity::Instance(pentTarget);
			if (pMaster && (pMaster->ObjectCaps() & FCAP_MASTER))
				return pMaster->IsTriggered(pActivator) != FALSE;
		}

		ALERT(at_console, "Master was null or not a master!\n");
	}

	return true;
}

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

int UTIL_PointContents(const Vector &vec)
{
	return POINT_CONTENTS(vec);
}

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
		WRITE_BYTE(clamp(amount / 10, 3, 16));
	MESSAGE_END();
}

Vector UTIL_RandomBloodVector()
{
	Vector direction;
	direction.x = RANDOM_FLOAT(-1, 1);
	direction.y = RANDOM_FLOAT(-1, 1);
	direction.z = RANDOM_FLOAT(0, 1);
	return direction;
}

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
			WRITE_SHORT(int(ENTINDEX(pTrace->pHit)));
			WRITE_BYTE(index);
		MESSAGE_END();
	}
}

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
		WRITE_SHORT(int(ENTINDEX(pTrace->pHit)));
		WRITE_BYTE(index);
	MESSAGE_END();
}

void UTIL_Sparks(const Vector &position)
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, position);
		WRITE_BYTE(TE_SPARKS);
		WRITE_COORD(position.x);
		WRITE_COORD(position.y);
		WRITE_COORD(position.z);
	MESSAGE_END();
}

void UTIL_Ricochet(const Vector &position, float scale)
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, position);
		WRITE_BYTE(TE_ARMOR_RICOCHET);
		WRITE_COORD(position.x);
		WRITE_COORD(position.y);
		WRITE_COORD(position.z);
		WRITE_BYTE(int(scale * 10.0f));
	MESSAGE_END();
}

bool UTIL_TeamsMatch(const char *pTeamName1, const char *pTeamName2)
{
	if (!g_pGameRules->IsTeamplay())
		return true;

	if (*pTeamName1 != '\0' && *pTeamName2 != '\0')
	{
		if (!Q_stricmp(pTeamName1, pTeamName2))
			return true;
	}

	return false;
}

void UTIL_StringToVector(float *pVector, const char *pString)
{
	char *pstr;
	char *pfront;
	char tempString[128];
	int j;

	Q_strlcpy(tempString, pString);

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

void UTIL_StringToVector(Vector &vecIn, const char *pString, char cSeparator)
{
	return UTIL_StringToVectorND(vecIn, 3, pString, cSeparator);
}

void UTIL_StringToVectorND(Vector &vecIn, int nCount, const char *pString, char cSeparator)
{
	int i;
	char *pstr;
	char *pfront;
	char tempString[128];

	Q_strlcpy(tempString, pString);

	pstr = tempString;
	pfront = tempString;

	for (i = 0; i < nCount; i++)
	{
		vecIn[i] = Q_atof(pfront);

		while (*pstr && *pstr != cSeparator)
			pstr++;

		if (!*pstr)
			break;

		pstr++;
		pfront = pstr;
	}

	if (++i < nCount)
	{
		Q_memset(&vecIn[i], 0, sizeof(float) * (nCount - i));
	}
}

void UTIL_StringToIntArray(int *pVector, int count, const char *pString)
{
	char *pstr;
	char *pfront;
	char tempString[128];
	int j;

	Q_strlcpy(tempString, pString);

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

void UTIL_Remove(CBaseEntity *pEntity)
{
	if (!pEntity)
		return;

#ifdef REGAMEDLL_FIXES
	if (pEntity->pev == VARS(eoNullEntity) || pEntity->IsPlayer() || (pEntity->pev->flags & FL_KILLME) == FL_KILLME)
		return;
#endif

	pEntity->UpdateOnRemove();

	pEntity->pev->solid = SOLID_NOT;
	pEntity->pev->flags |= FL_KILLME;
	pEntity->pev->targetname = 0;
}

NOXREF BOOL UTIL_IsValidEntity(edict_t *pent)
{
	if (!pent || pent->free || (pent->v.flags & FL_KILLME))
		return FALSE;

	return TRUE;
}

void UTIL_PrecacheOther(const char *szClassname)
{
	edict_t *pent = CREATE_NAMED_ENTITY(MAKE_STRING(szClassname));
	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in UTIL_PrecacheOther classname `%s`\n", szClassname);
		return;
	}

	CBaseEntity *pEntity = CBaseEntity::Instance(VARS(pent));
	if (pEntity)
	{
		pEntity->Precache();
	}

	REMOVE_ENTITY(pent);
}

void UTIL_RestartOther(const char *szClassname)
{
	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, szClassname)))
	{
		pEntity->Restart();
	}
}

void UTIL_ResetEntities()
{
	edict_t *pEdict = INDEXENT(1);
	for (int i = 1; i < gpGlobals->maxEntities; i++, pEdict++)
	{
		if (pEdict->free)
			continue;

		CBaseEntity *pEntity = CBaseEntity::Instance(pEdict);
		if (!pEntity)
			continue;

		// only non-player entities
		if (pEntity->IsPlayer())
			continue;

		int caps = pEntity->ObjectCaps();
		if ((caps & FCAP_MUST_RELEASE) == FCAP_MUST_RELEASE)
			UTIL_Remove(pEntity);

		else if ((caps & FCAP_MUST_RESET) == FCAP_MUST_RESET)
			pEntity->Restart();
	}
}

void UTIL_RemoveOther(const char *szClassname, int nRemoveCount)
{
	int num = 0;
	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, szClassname)))
	{
#ifndef REGAMEDLL_FIXES
		if (nRemoveCount > 0 && num++ >= nRemoveCount)
			break;
#endif

		UTIL_Remove(pEntity);
	}
}

void UTIL_LogPrintf(const char *fmt, ...)
{
	va_list argptr;
	static char string[1024];

	va_start(argptr, fmt);
	vsprintf(string, fmt, argptr);
	va_end(argptr);

	ALERT(at_logged, "%s", string);
}

NOXREF float UTIL_DotPoints(const Vector &vecSrc, const Vector &vecCheck, const Vector &vecDir)
{
	Vector2D vec2LOS = (vecCheck - vecSrc).Make2D();
	vec2LOS = vec2LOS.Normalize();
	return DotProduct(vec2LOS, (vecDir.Make2D()));
}

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
		szbuffer[16] = '\0';
		chTextureType = TEXTURETYPE_Find(szbuffer);
	}
	else
		chTextureType = '\0';

	return chTextureType;
}

NOXREF int GetPlayerTeam(int index)
{
	CBasePlayer *pPlayer = UTIL_PlayerByIndexSafe(index);
	if (pPlayer)
	{
		return pPlayer->m_iTeam;
	}

	return 0;
}

bool UTIL_IsGame(const char *pszGameName)
{
#ifndef CSTRIKE
	if (pszGameName)
	{
		char szGameDir[256];
		GET_GAME_DIR(szGameDir);
		return (Q_stricmp(szGameDir, pszGameName) == 0);
	}
#endif

	return false;
}

real_t UTIL_GetPlayerGaitYaw(int playerIndex)
{
	CBasePlayer *pPlayer = UTIL_PlayerByIndex(playerIndex);
	if (pPlayer)
	{
		return pPlayer->m_flGaityaw;
	}

	return 0;
}

int UTIL_ReadFlags(const char *c)
{
	int flags = 0;

	while (*c)
	{
		if (*c >= 'a' && *c <= 'z')
		{
			flags |= (1 << (*c - 'a'));
		}

		c++;
	}

	return flags;
}

// Determine whether bots can be used or not
bool UTIL_AreBotsAllowed()
{
#ifdef REGAMEDLL_ADD
	if (g_engfuncs.pfnEngCheckParm == nullptr)
		return false;
#endif

	if (AreRunningCZero())
	{
#ifdef REGAMEDLL_ADD
		// If they pass in -nobots, don't allow bots.  This is for people who host servers, to
		// allow them to disallow bots to enforce CPU limits.
		int nobots = ENG_CHECK_PARM("-nobots", nullptr);
		if (nobots)
		{
			return false;
		}
#endif

		return true;
	}

#ifdef REGAMEDLL_ADD
	// let enables zBot by default from listen server?
	if (!IS_DEDICATED_SERVER())
	{
		return true;
	}

	// allow the using of bots for CS 1.6
	int bots = ENG_CHECK_PARM("-bots", nullptr);
	if (bots)
	{
		return true;
	}
#endif

	return false;
}

bool UTIL_IsBeta()
{
#ifdef BUILD_LATEST
	if (g_engfuncs.pfnEngCheckParm == nullptr)
		return false;

	// always beta from listen server
	if (!IS_DEDICATED_SERVER())
	{
		return true;
	}

	int beta = ENG_CHECK_PARM("-beta", nullptr);
	if (beta)
	{
		return true;
	}
#endif // #ifdef BUILD_LATEST

	return false;
}

bool UTIL_AreHostagesImprov()
{
	if (AreRunningCZero())
	{
		return true;
	}

#ifdef REGAMEDLL_ADD
	// someday in CS 1.6
	int improv = ENG_CHECK_PARM("-host-improv", nullptr);
	if (improv)
	{
		return true;
	}
#endif

	return false;
}

int UTIL_GetNumPlayers()
{
	int nNumPlayers = 0;
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);
		if (pPlayer)
		{
			nNumPlayers++;
		}
	}

	return nNumPlayers;
}

bool UTIL_IsSpawnPointOccupied(CBaseEntity *pSpot)
{
	if (!pSpot)
		return false;

	const int maxList = 8;
	CBaseEntity *pList[maxList];

	Vector mins(pSpot->pev->origin + VEC_SPOT_HULL_MIN - 8.0);
	Vector maxs(pSpot->pev->origin + VEC_SPOT_HULL_MAX + 8.0);

	int nCount = UTIL_EntitiesInBox(pList, maxList, mins, maxs, FL_MONSTER | FL_CLIENT);
	for (int i = 0; i < nCount; i++)
	{
		if (pList[i]->pev->solid != SOLID_NOT)
			return false;
	}

	return false;
}

void MAKE_STRING_CLASS(const char *str, entvars_t *pev)
{
	if (!FStringNull(pev->classname))
	{
		RemoveEntityHashValue(pev, STRING(pev->classname), CLASSNAME);
	}

	pev->classname = MAKE_STRING(str);
	AddEntityHashValue(pev, STRING(pev->classname), CLASSNAME);
}

void NORETURN Sys_Error(const char *error, ...)
{
	va_list argptr;
	static char text[1024];

	va_start(argptr, error);
	vsnprintf(text, sizeof(text), error, argptr);
	va_end(argptr);

	FILE *fl = fopen("regamedll_error.txt", "w");
	if (fl)
	{
		fprintf(fl, "%s\n", text);
		fclose(fl);
	}

	CONSOLE_ECHO("FATAL ERROR (shutting down): %s\n", text);

	//TerminateProcess(GetCurrentProcess(), 1);
	int *null = 0;
	*null = 0;
	exit(-1);
}

int UTIL_CountPlayersInBrushVolume(bool bOnlyAlive, CBaseEntity *pBrushEntity, int &playersInCount, int &playersOutCount, CPlayerInVolumeAdapter *pAdapter)
{
	playersInCount = 0;
	playersOutCount = 0;

	if (pBrushEntity)
	{
		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

			if (!pPlayer || !pPlayer->IsInWorld())
				continue;

			if (bOnlyAlive && !pPlayer->IsAlive())
				continue;

			TraceResult trace;
			int hullNumber = (pPlayer->pev->flags & FL_DUCKING) ? head_hull : human_hull;
			UTIL_TraceModel(pPlayer->pev->origin, pPlayer->pev->origin, hullNumber, pBrushEntity->edict(), &trace);

			bool fInVolume = trace.fStartSolid > 0.0f;
			if (fInVolume)
			{
				playersInCount++;
			}
			else
			{
				playersOutCount++;
			}

			if (pAdapter) {
				pAdapter->PlayerDetected(fInVolume, pPlayer);
			}
		}
	}
	else
	{
		playersOutCount = UTIL_GetNumPlayers();
	}

	return playersInCount + playersOutCount;
}
