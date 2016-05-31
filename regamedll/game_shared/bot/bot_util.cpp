#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

short s_iBeamSprite = 0;
float cosTable[ COS_TABLE_SIZE ];

#endif

bool UTIL_IsNameTaken(const char *name, bool ignoreHumans)
{
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBaseEntity *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (player->IsPlayer() && ((CBasePlayer *)player)->IsBot())
		{
			// bots can have prefixes so we need to check the name
			// against the profile name instead.
			CBot *bot = static_cast<CBot *>(player);
			if (FStrEq(name, bot->GetProfile()->GetName()))
			{
				return true;
			}
		}
		else
		{
			if (!ignoreHumans)
			{
				if (FStrEq(name, STRING(player->pev->netname)))
					return true;
			}
		}
	}

	return false;
}

int UTIL_ClientsInGame()
{
	int iCount = 0;
	for (int iIndex = 1; iIndex <= gpGlobals->maxClients; ++iIndex)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(iIndex);

		if (pPlayer == NULL)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (FStrEq(STRING(pPlayer->pev->netname), ""))
			continue;

		++iCount;
	}

	return iCount;
}

int UTIL_ActivePlayersInGame()
{
	int iCount = 0;
	for (int iIndex = 1; iIndex <= gpGlobals->maxClients; ++iIndex)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(iIndex);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		// ignore spectators
		if (player->m_iTeam != TERRORIST && player->m_iTeam != CT)
			continue;

		if (player->m_iJoiningState != JOINED)
			continue;

		++iCount;
	}

	return iCount;
}

int UTIL_HumansInGame(bool ignoreSpectators)
{
	int iCount = 0;

	for (int iIndex = 1; iIndex <= gpGlobals->maxClients; ++iIndex)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(iIndex);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (player->IsBot())
			continue;

		if (ignoreSpectators && player->m_iTeam != TERRORIST && player->m_iTeam != CT)
			continue;

		if (ignoreSpectators && player->m_iJoiningState != JOINED)
			continue;

		++iCount;
	}

	return iCount;
}

int UTIL_HumansOnTeam(int teamID, bool isAlive)
{
	int iCount = 0;
	for (int iIndex = 1; iIndex <= gpGlobals->maxClients; ++iIndex)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(iIndex);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (player->IsBot())
			continue;

		if (player->m_iTeam != teamID)
			continue;

		if (isAlive && !player->IsAlive())
			continue;

		++iCount;
	}

	return iCount;
}

int UTIL_BotsInGame()
{
	int iCount = 0;

	for (int iIndex = 1; iIndex <= gpGlobals->maxClients; ++iIndex)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(iIndex);

		if (pPlayer == NULL)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (FStrEq(STRING(pPlayer->pev->netname), ""))
			continue;

		if (!pPlayer->IsBot())
			continue;

		++iCount;
	}

	return iCount;
}

bool UTIL_KickBotFromTeam(TeamName kickTeam)
{
	int i;

	// try to kick a dead bot first
	for (i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		const char *name = STRING(player->pev->netname);
		if (FStrEq(name, ""))
			continue;

		if (!player->IsBot())
			continue;

		if (!player->IsAlive() && player->m_iTeam == kickTeam)
		{
			// its a bot on the right team - kick it
			SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", STRING(player->pev->netname)));
			return true;
		}
	}

	// no dead bots, kick any bot on the given team
	for (i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		const char *name = STRING(player->pev->netname);
		if (FStrEq(name, ""))
			continue;

		if (!player->IsBot())
			continue;

		if (player->m_iTeam == kickTeam)
		{
			// its a bot on the right team - kick it
			SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", STRING(player->pev->netname)));
			return true;
		}
	}

	return false;
}

bool UTIL_IsTeamAllBots(int team)
{
	int botCount = 0;
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (player->m_iTeam != team)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (!(player->pev->flags & FL_FAKECLIENT))
			return false;

		++botCount;
	}

	return botCount ? true : false;
}

// Return the closest active player to the given position.
// If 'distance' is non-NULL, the distance to the closest player is returned in it.
extern CBasePlayer *UTIL_GetClosestPlayer(const Vector *pos, float *distance)
{
	CBasePlayer *closePlayer = NULL;
	float closeDistSq = 1.0e12f;	// 999999999999.9f

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (!IsEntityValid(player))
			continue;

		if (!player->IsAlive())
			continue;

		float distSq = (player->pev->origin - *pos).LengthSquared();
		if (distSq < closeDistSq)
		{
			closeDistSq = distSq;
			closePlayer = player;
		}
	}

	if (distance)
		*distance = Q_sqrt(closeDistSq);

	return closePlayer;
}

// Return the closest active player on the given team to the given position.
// If 'distance' is non-NULL, the distance to the closest player is returned in it.
extern CBasePlayer *UTIL_GetClosestPlayer(const Vector *pos, int team, float *distance)
{
	CBasePlayer *closePlayer = NULL;
	float closeDistSq = 1.0e12f;	// 999999999999.9f

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (!IsEntityValid(player))
			continue;

		if (!player->IsAlive())
			continue;

		if (player->m_iTeam != team)
			continue;

		float distSq = (player->pev->origin - *pos).LengthSquared();
		if (distSq < closeDistSq)
		{
			closeDistSq = distSq;
			closePlayer = player;
		}
	}

	if (distance)
		*distance = Q_sqrt(closeDistSq);

	return closePlayer;
}

const char *UTIL_GetBotPrefix()
{
	return cv_bot_prefix.string;
}

void UTIL_ConstructBotNetName(char *name, int nameLength, const BotProfile *profile)
{
	if (profile == NULL)
	{
		name[0] = '\0';
		return;
	}

	// if there is no bot prefix just use the profile name.
	if ((UTIL_GetBotPrefix() == NULL) || (Q_strlen(UTIL_GetBotPrefix()) == 0))
	{
		Q_strncpy(name, profile->GetName(), nameLength);
		return;
	}

	Q_snprintf(name, nameLength, "%s %s", UTIL_GetBotPrefix(), profile->GetName());
}

bool UTIL_IsVisibleToTeam(const Vector &spot, int team, float maxRange)
{
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (!player->IsAlive())
			continue;

		if (player->m_iTeam != team)
			continue;

		if (maxRange > 0.0f && (spot - player->Center()).IsLengthGreaterThan(maxRange))
			continue;

		TraceResult result;
		UTIL_TraceLine(player->EyePosition(), spot, ignore_monsters, ignore_glass, ENT(player->pev), &result);

		if (result.flFraction == 1.0f)
			return true;
	}

	return false;
}

CBasePlayer *UTIL_GetLocalPlayer()
{
	if (!IS_DEDICATED_SERVER())
		return UTIL_PlayerByIndex(1);

	return NULL;
}

NOXREF Vector UTIL_ComputeOrigin(entvars_t *pevVars)
{
	if (pevVars->origin.x == 0.0f && pevVars->origin.y == 0.0f && pevVars->origin.z == 0.0f)
		return (pevVars->absmax + pevVars->absmin) * 0.5f;
	else
		return pevVars->origin;
}

NOXREF Vector UTIL_ComputeOrigin(CBaseEntity *pEntity)
{
	return UTIL_ComputeOrigin(pEntity->pev);
}

NOXREF Vector UTIL_ComputeOrigin(edict_t *pentEdict)
{
	return UTIL_ComputeOrigin(VARS(pentEdict));
}

NOXREF void UTIL_DrawBeamFromEnt(int iIndex, Vector vecEnd, int iLifetime, byte bRed, byte bGreen, byte bBlue)
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecEnd);
		WRITE_BYTE(TE_BEAMENTPOINT);
		WRITE_SHORT(iIndex);
		WRITE_COORD(vecEnd.x);
		WRITE_COORD(vecEnd.y);
		WRITE_COORD(vecEnd.z);
		WRITE_SHORT(s_iBeamSprite);
		WRITE_BYTE(0);
		WRITE_BYTE(0);
		WRITE_BYTE(iLifetime);
		WRITE_BYTE(10);
		WRITE_BYTE(0);
		WRITE_BYTE(bRed);
		WRITE_BYTE(bGreen);
		WRITE_BYTE(bBlue);
		WRITE_BYTE(255);
		WRITE_BYTE(0);
	MESSAGE_END();
}

void UTIL_DrawBeamPoints(Vector vecStart, Vector vecEnd, int iLifetime, byte bRed, byte bGreen, byte bBlue)
{
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, vecStart);
		WRITE_BYTE(TE_BEAMPOINTS);
		WRITE_COORD(vecStart.x);
		WRITE_COORD(vecStart.y);
		WRITE_COORD(vecStart.z);
		WRITE_COORD(vecEnd.x);
		WRITE_COORD(vecEnd.y);
		WRITE_COORD(vecEnd.z);
		WRITE_SHORT(s_iBeamSprite);
		WRITE_BYTE(0);
		WRITE_BYTE(0);
		WRITE_BYTE(iLifetime);
		WRITE_BYTE(10);
		WRITE_BYTE(0);
		WRITE_BYTE(bRed);
		WRITE_BYTE(bGreen);
		WRITE_BYTE(bBlue);
		WRITE_BYTE(255);
		WRITE_BYTE(0);
	MESSAGE_END();
}

void CONSOLE_ECHO(const char *pszMsg, ...)
{
	va_list argptr;
	static char szStr[1024];

	va_start(argptr, pszMsg);
	vsprintf(szStr, pszMsg, argptr);
	va_end(argptr);

	SERVER_PRINT(szStr);
}

void CONSOLE_ECHO_LOGGED(const char *pszMsg, ...)
{
	va_list argptr;
	static char szStr[1024];

	va_start(argptr, pszMsg);
	vsprintf(szStr, pszMsg, argptr);
	va_end(argptr);

	SERVER_PRINT(szStr);
	UTIL_LogPrintf(szStr);
}

void BotPrecache()
{
	s_iBeamSprite = PRECACHE_MODEL("sprites/smoke.spr");

	PRECACHE_SOUND("buttons/bell1.wav");
	PRECACHE_SOUND("buttons/blip1.wav");
	PRECACHE_SOUND("buttons/blip2.wav");
	PRECACHE_SOUND("buttons/button11.wav");
	PRECACHE_SOUND("buttons/latchunlocked2.wav");
	PRECACHE_SOUND("buttons/lightswitch2.wav");
	PRECACHE_SOUND("ambience/quail1.wav");

	PRECACHE_SOUND("events/tutor_msg.wav");
	PRECACHE_SOUND("events/enemy_died.wav");
	PRECACHE_SOUND("events/friend_died.wav");
	PRECACHE_SOUND("events/task_complete.wav");
}

void InitBotTrig()
{
	for (int i = 0; i < COS_TABLE_SIZE; ++i)
	{
		float_precision angle = 2.0f * M_PI * float(i) / float(COS_TABLE_SIZE - 1);
		cosTable[i] = Q_cos(angle);
	}
}

float BotCOS(float angle)
{
	angle = NormalizeAnglePositive(angle);
	int i = angle * ((COS_TABLE_SIZE - 1) / 360.0f);
	return cosTable[ i ];
}

float BotSIN(float angle)
{
	angle = NormalizeAnglePositive(angle - 90);
	int i = angle * ((COS_TABLE_SIZE - 1) / 360.0f);
	return cosTable[ i ];
}

// Determine if this event is audible, and if so, return its audible range and priority
bool IsGameEventAudible(GameEventType event, CBaseEntity *entity, CBaseEntity *other, float *range, PriorityType *priority, bool *isHostile)
{
	CBasePlayer *player = static_cast<CBasePlayer *>(entity);

	if (entity == NULL || !player->IsPlayer())
		player = NULL;

	const float ShortRange = 1000.0f;
	const float NormalRange = 2000.0f;

	switch (event)
	{
	// TODO: Check weapon type (knives are pretty quiet)
	// TODO: Use actual volume, account for silencers, etc.
	case EVENT_WEAPON_FIRED:
	{
		if (player->m_pActiveItem == NULL)
			return false;

		switch (player->m_pActiveItem->m_iId)
		{
		// silent "firing"
		case WEAPON_HEGRENADE:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_FLASHBANG:
		case WEAPON_SHIELDGUN:
		case WEAPON_C4:
			return false;
		// quiet
		case WEAPON_KNIFE:
		case WEAPON_TMP:
			*range = ShortRange;
			break;
		// M4A1 - check for silencer
		case WEAPON_M4A1:
		{
			CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(player->m_pActiveItem);
			if (pWeapon->m_iWeaponState & WPNSTATE_M4A1_SILENCED)
				*range = ShortRange;
			else
				*range = NormalRange;
			break;
		}
		// USP - check for silencer
		case WEAPON_USP:
		{
			CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(player->m_pActiveItem);
			if (pWeapon->m_iWeaponState & WPNSTATE_USP_SILENCED)
				*range = ShortRange;
			else
				*range = NormalRange;
			break;
		}
		// loud
		case WEAPON_AWP:
			*range = 99999.0f;
			break;
		// normal
		default:
			*range = NormalRange;
			break;
		}

		*priority = PRIORITY_HIGH;
		*isHostile = true;
		return true;
	}
	case EVENT_HE_GRENADE_EXPLODED:
		*range = 99999.0f;
		*priority = PRIORITY_HIGH;
		*isHostile = true;
		return true;

	case EVENT_FLASHBANG_GRENADE_EXPLODED:
		*range = 1000.0f;
		*priority = PRIORITY_LOW;
		*isHostile = true;
		return true;

	case EVENT_SMOKE_GRENADE_EXPLODED:
		*range = 1000.0f;
		*priority = PRIORITY_LOW;
		*isHostile = true;
		return true;

	case EVENT_GRENADE_BOUNCED:
		*range = 500.0f;
		*priority = PRIORITY_LOW;
		*isHostile = true;
		return true;

	case EVENT_BREAK_GLASS:
	case EVENT_BREAK_WOOD:
	case EVENT_BREAK_METAL:
	case EVENT_BREAK_FLESH:
	case EVENT_BREAK_CONCRETE:
		*range = 1100.0f;
		*priority = PRIORITY_MEDIUM;
		*isHostile = true;
		return true;

	case EVENT_DOOR:
		*range = 1100.0f;
		*priority = PRIORITY_MEDIUM;
		*isHostile = false;
		return true;

	case EVENT_WEAPON_FIRED_ON_EMPTY:
	case EVENT_PLAYER_FOOTSTEP:
	case EVENT_WEAPON_RELOADED:
	case EVENT_WEAPON_ZOOMED:
	case EVENT_PLAYER_LANDED_FROM_HEIGHT:
		*range = 1100.0f;
		*priority = PRIORITY_LOW;
		*isHostile = false;
		return true;

	case EVENT_HOSTAGE_USED:
	case EVENT_HOSTAGE_CALLED_FOR_HELP:
		*range = 1200.0f;
		*priority = PRIORITY_MEDIUM;
		*isHostile = false;
		return true;
	}

	return false;
}

void HintMessageToAllPlayers(const char *message)
{
	hudtextparms_t textParms;

	textParms.x = -1.0f;
	textParms.y = -1.0f;
	textParms.effect = 0;

	textParms.r1 = 100;
	textParms.g1 = 255;
	textParms.b1 = 100;

	textParms.r2 = 255;
	textParms.g2 = 255;
	textParms.b2 = 255;

	textParms.fadeinTime = 1.0f;
	textParms.fadeoutTime = 5.0f;
	textParms.holdTime = 5.0f;
	textParms.fxTime = 0.0f;

	textParms.channel = 0;

	UTIL_HudMessageAll(textParms, message);
}
