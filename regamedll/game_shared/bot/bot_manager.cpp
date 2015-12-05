#include "precompiled.h"

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

//#define DEFINE_EVENT_NAMES

/*#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"
#include "soundent.h"
#include "gamerules.h"
#include "player.h"
#include "client.h"
#include "game_shared/perf_counter.h"

#include "bot.h"
#include "bot_manager.h"
#include "nav_area.h"
#include "bot_util.h"
#include "hostage.h"

#include "tutor.h"*/

//#define CHECK_PERFORMANCE

const float smokeRadius = 115.0f;		///< for smoke grenades

/* <49f6d7> ../game_shared/bot/bot_manager.cpp:58 */
NOBODY GameEventType NameToGameEvent(const char *name)
{
	/*for (int i=0; GameEventName[i]; ++i)
		if (!Q_stricmp(GameEventName[i], name))
			return static_cast<GameEventType>(i);*/

	return EVENT_INVALID;
}

/* <49f733> ../game_shared/bot/bot_manager.cpp:69 */
NOBODY CBotManager::CBotManager()
{
	//InitBotTrig();
}

/* <49f586> ../game_shared/bot/bot_manager.cpp:78 */
void CBotManager::__MAKE_VHOOK(RestartRound)(void)
{
	DestroyAllGrenades();
}

void CBotManager::__MAKE_VHOOK(StartFrame)(void)
{
	// debug smoke grenade visualization
	if (cv_bot_debug.value == 5)
	{
		UNTESTED

		Vector edge, lastEdge;

		ActiveGrenadeList::iterator iter = m_activeGrenadeList.begin();
		while (iter != m_activeGrenadeList.end())
		{
			ActiveGrenade *ag = *iter;

			// lazy validation
			if (!ag->IsValid())
			{
				delete ag;
				iter = m_activeGrenadeList.erase(iter);
				continue;
			}
			else
				++iter;

			const Vector *pos = ag->GetDetonationPosition();

			UTIL_DrawBeamPoints(*pos, *pos + Vector(0, 0, 50), 1, 255, 100, 0);

			lastEdge = Vector(smokeRadius + pos->x, pos->y, pos->z);
			float angle;
			for (angle = 0.0f; angle <= 180.0f; angle += 22.5f)
			{
				edge.x = smokeRadius * BotCOS(angle) + pos->x;
				edge.y = pos->y;
				edge.z = smokeRadius * BotSIN(angle) + pos->z;

				UTIL_DrawBeamPoints(edge, lastEdge, 1, 255, 50, 0);

				lastEdge = edge;
			}

			lastEdge = Vector(pos->x, smokeRadius + pos->y, pos->z);
			for (angle = 0.0f; angle <= 180.0f; angle += 22.5f)
			{
				edge.x = pos->x;
				edge.y = smokeRadius * BotCOS(angle) + pos->y;
				edge.z = smokeRadius * BotSIN(angle) + pos->z;

				UTIL_DrawBeamPoints(edge, lastEdge, 1, 255, 50, 0);

				lastEdge = edge;
			}
		}
	}

	// Process each active bot
	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBasePlayer *pPlayer = reinterpret_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (!pPlayer)
			continue;

		if (pPlayer->IsBot() && IsEntityValid(pPlayer))
		{
			CBot *pBot = static_cast<CBot *>(pPlayer);

			pBot->BotThink();
		}
	}
}

/* <49f7a6> ../game_shared/bot/bot_manager.cpp:205 */
const char *CBotManager::GetNavMapFilename(void) const
{
	static char filename[256];
	Q_sprintf(filename, "maps\\%s.nav", STRING(gpGlobals->mapname));
	return filename;
}

/* <49f17b> ../game_shared/bot/bot_manager.cpp:219 */
void CBotManager::__MAKE_VHOOK(OnEvent)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	// propogate event to all bots
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *player = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(i));

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (!player->IsBot())
			continue;

		// do not send self-generated event
		if (entity == player)
			continue;

		CBot *bot = static_cast<CBot *>(player);
		bot->OnEvent(event, entity, other);
	}

	if (TheTutor != NULL)
	{
		TheTutor->OnEvent(event, entity, other);
	}

	if (g_pHostages != NULL)
	{
		g_pHostages->OnEvent(event, entity, other);
	}
}

/* <49f7ff> ../game_shared/bot/bot_manager.cpp:257 */
void CBotManager::AddGrenade(int type, CGrenade *grenade)
{
	ActiveGrenade *ag = new ActiveGrenade(type, grenade);

	m_activeGrenadeList.push_back(ag);
}

/* <49f95a> ../game_shared/bot/bot_manager.cpp:267 */
void CBotManager::RemoveGrenade(CGrenade *grenade)
{
	for (ActiveGrenadeList::iterator iter = m_activeGrenadeList.begin(); iter != m_activeGrenadeList.end(); ++iter)
	{
		ActiveGrenade *ag = *iter;

		if (ag->IsEntity(grenade))
		{
			ag->OnEntityGone();
			return;
		}
	}
}

/* <49f9fc> ../game_shared/bot/bot_manager.cpp:285 */
NOXREF void CBotManager::ValidateActiveGrenades(void)
{
	ActiveGrenadeList::iterator iter = m_activeGrenadeList.begin();
	while (iter != m_activeGrenadeList.end())
	{
		ActiveGrenade *ag = *iter;

		if (!ag->IsValid())
		{
			delete ag;
			iter = m_activeGrenadeList.erase(iter);
		}
		else
			++iter;
	}
}

/* <49faf3> ../game_shared/bot/bot_manager.cpp:305 */
NOXREF void CBotManager::DestroyAllGrenades(void)
{
	for (ActiveGrenadeList::iterator iter = m_activeGrenadeList.begin(); iter != m_activeGrenadeList.end(); iter++)
		delete *iter;

	m_activeGrenadeList.clear();
}

/* <49fc24> ../game_shared/bot/bot_manager.cpp:317 */
bool CBotManager::IsInsideSmokeCloud(const Vector *pos)
{
	ActiveGrenadeList::iterator iter = m_activeGrenadeList.begin();
	while (iter != m_activeGrenadeList.end())
	{
		ActiveGrenade *ag = *iter;
		if (!ag->IsValid())
		{
			delete ag;
			iter = m_activeGrenadeList.erase(iter);
			continue;
		}
		else
			++iter;

		if (ag->GetID() == WEAPON_SMOKEGRENADE)
		{
			const Vector *smokeOrigin = ag->GetDetonationPosition();

			if ((*smokeOrigin - *pos).IsLengthLessThan(smokeRadius))
				return true;
		}
	}
	return false;
}

/* <49fd8b> ../game_shared/bot/bot_manager.cpp:355 */
bool CBotManager::IsLineBlockedBySmoke(const Vector *from, const Vector *to)
{
	const float smokeRadiusSq = smokeRadius * smokeRadius;

	// distance along line of sight covered by smoke
	float totalSmokedLength = 0.0f;

	// compute unit vector and length of line of sight segment
	Vector sightDir = *to - *from;
	float sightLength = sightDir.NormalizeInPlace();

	ActiveGrenadeList::iterator iter = m_activeGrenadeList.begin();
	while (iter != m_activeGrenadeList.end())
	{
		ActiveGrenade *ag = *iter;

		if (!ag->IsValid())
		{
			delete ag;
			iter = m_activeGrenadeList.erase(iter);
			continue;
		}
		else
			++iter;

		if (ag->GetID() == WEAPON_SMOKEGRENADE)
		{
			const Vector *smokeOrigin = ag->GetDetonationPosition();

			Vector toGrenade = *smokeOrigin - *from;

			float alongDist = DotProduct(toGrenade, sightDir);

			// compute closest point to grenade along line of sight ray
			Vector close;

			// constrain closest point to line segment
			if (alongDist < 0.0f)
				close = *from;

			else if (alongDist >= sightLength)
				close = *to;
			else
				close = *from + sightDir * alongDist;

			// if closest point is within smoke radius, the line overlaps the smoke cloud
			Vector toClose = close - *smokeOrigin;
			float lengthSq = toClose.LengthSquared();

			if (lengthSq < smokeRadiusSq)
			{
				// some portion of the ray intersects the cloud
				float fromSq = toGrenade.LengthSquared();
				float toSq = (*smokeOrigin - *to).LengthSquared();

				if (fromSq < smokeRadiusSq)
				{
					if (toSq < smokeRadiusSq)
					{
						// both 'from' and 'to' lie within the cloud
						// entire length is smoked
						totalSmokedLength += (*to - *from).Length();
					}
					else
					{
						// 'from' is inside the cloud, 'to' is outside
						// compute half of total smoked length as if ray crosses entire cloud chord
						float halfSmokedLength = sqrt(smokeRadiusSq - lengthSq);

						if (alongDist > 0.0f)
						{
							// ray goes thru 'close'
							totalSmokedLength += halfSmokedLength + (close - *from).Length();
						}
						else
						{
							// ray starts after 'close'
							totalSmokedLength += halfSmokedLength - (close - *from).Length();
						}
					}
				}
				else if (toSq < smokeRadiusSq)
				{
					// 'from' is outside the cloud, 'to' is inside
					// compute half of total smoked length as if ray crosses entire cloud chord
					float halfSmokedLength = sqrt(smokeRadiusSq - lengthSq);

					Vector v = *to - *smokeOrigin;
					if (DotProduct(v, sightDir) > 0.0f)
					{
						// ray goes thru 'close'
						totalSmokedLength += halfSmokedLength + (close - *to).Length();
					}
					else
					{
						// ray ends before 'close'
						totalSmokedLength += halfSmokedLength - (close - *to).Length();
					}
				}
				else
				{
					// 'from' and 'to' lie outside of the cloud - the line of sight completely crosses it
					// determine the length of the chord that crosses the cloud

					float smokedLength = 2.0f * sqrt(smokeRadiusSq - lengthSq);
					totalSmokedLength += smokedLength;
				}
			}
		}
	}

	const float maxSmokedLength = 0.7f * smokeRadius;
	return (totalSmokedLength > maxSmokedLength);
}


#ifdef HOOK_GAMEDLL

void CBotManager::RestartRound(void)
{
	RestartRound_();
}

void CBotManager::StartFrame(void)
{
	StartFrame_();
}

void CBotManager::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	return OnEvent_(event, entity, other);
}

#endif // HOOK_GAMEDLL