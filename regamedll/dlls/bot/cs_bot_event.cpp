/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#include "precompiled.h"

void CCSBot::OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	GetGameState()->OnEvent(event, pEntity, pOther);
	GetChatter()->OnEvent(event, pEntity, pOther);

	// Morale adjustments happen even for dead players
	switch (event)
	{
	case EVENT_TERRORISTS_WIN:
		if (m_iTeam == CT)
		{
			DecreaseMorale();
		}
		else
		{
			IncreaseMorale();
		}
		break;
	case EVENT_CTS_WIN:
		if (m_iTeam == CT)
		{
			IncreaseMorale();
		}
		else
		{
			DecreaseMorale();
		}
		break;
	}

	if (!IsAlive())
		return;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);

	// If we just saw a nearby friend die, and we haven't yet acquired an enemy
	// automatically acquire our dead friend's killer
	if (!IsAttacking() && (GetDisposition() == ENGAGE_AND_INVESTIGATE || GetDisposition() == OPPORTUNITY_FIRE))
	{
		if (event == EVENT_PLAYER_DIED)
		{
			if (BotRelationship(pPlayer) == BOT_TEAMMATE)
			{
				CBasePlayer *pKiller = static_cast<CBasePlayer *>(pOther);

				// check that attacker is an enemy (for friendly fire, etc)
				if (pKiller && pKiller->IsPlayer())
				{
					// check if we saw our friend die - dont check FOV - assume we're aware of our surroundings in combat
					// snipers stay put
					if (!IsSniper() && IsVisible(&pPlayer->pev->origin))
					{
						// people are dying - we should hurry
						Hurry(RANDOM_FLOAT(10.0f, 15.0f));

						// if we're hiding with only our knife, be a little more cautious
						const float knifeAmbushChance = 50.0f;
						if (!IsHiding() || !IsUsingKnife() || RANDOM_FLOAT(0, 100) < knifeAmbushChance)
						{
							PrintIfWatched("Attacking our friend's killer!\n");
							Attack(pKiller);
							return;
						}
					}
				}
			}
		}
	}

	switch (event)
	{
	case EVENT_PLAYER_DIED:
	{
		CBasePlayer *pVictim = pPlayer;
		CBasePlayer *pKiller = (pOther && pOther->IsPlayer()) ? static_cast<CBasePlayer *>(pOther) : nullptr;

		// if the human player died in the single player game, tell the team
		if (CSGameRules()->IsCareer() && !pVictim->IsBot() && BotRelationship(pVictim) == BOT_TEAMMATE)
		{
			GetChatter()->Say("CommanderDown", 20.0f);
		}

		// keep track of the last player we killed
		if (pKiller == this)
		{
			m_lastVictimID = pVictim->entindex();
		}

		// react to teammate death
		if (BotRelationship(pVictim) == BOT_TEAMMATE)
		{
			// chastise friendly fire from humans
			if (pKiller && !pKiller->IsBot() && BotRelationship(pKiller) == BOT_TEAMMATE && pKiller != this)
			{
				GetChatter()->KilledFriend();
			}

			if (IsHunting())
			{
				PrintIfWatched("Rethinking hunt due to teammate death\n");
				Idle();
				return;
			}

			if (IsAttacking())
			{
				if (GetTimeSinceLastSawEnemy() > 0.4f)
				{
					PrintIfWatched("Rethinking my attack due to teammate death\n");

					// allow us to sneak past windows, doors, etc
					IgnoreEnemies(1.0f);

					// move to last known position of enemy - this could cause us to flank if
					// the danger has changed due to our teammate's recent death
					SetTask(MOVE_TO_LAST_KNOWN_ENEMY_POSITION, GetEnemy());
					MoveTo(&GetLastKnownEnemyPosition());
					return;
				}
			}
		}
		// an enemy was killed
		else
		{
			if (pKiller && BotRelationship(pKiller) == BOT_TEAMMATE)
			{
				// only chatter about enemy kills if we see them occur, and they were the last one we see
				if (GetNearbyEnemyCount() <= 1)
				{
					// report if number of enemies left is few and we killed the last one we saw locally
					GetChatter()->EnemiesRemaining();

					if (IsVisible(&pVictim->pev->origin, CHECK_FOV))
					{
						// congratulate teammates on their kills
						if (pKiller != this)
						{
							float delay = RANDOM_FLOAT(2.0f, 3.0f);
							if (pKiller->IsBot())
							{
								if (RANDOM_FLOAT(0.0f, 100.0f) < 40.0f)
									GetChatter()->Say("NiceShot", 3.0f, delay);
							}
							else
							{
								// humans get the honorific
								if (CSGameRules()->IsCareer())
									GetChatter()->Say("NiceShotCommander", 3.0f, delay);
								else
									GetChatter()->Say("NiceShotSir", 3.0f, delay);
							}
						}
					}
				}
			}
		}
		return;
	}
	case EVENT_TERRORISTS_WIN:
		if (m_iTeam == TERRORIST)
			GetChatter()->CelebrateWin();
		return;
	case EVENT_CTS_WIN:
		if (m_iTeam == CT)
			GetChatter()->CelebrateWin();
		return;
	case EVENT_BOMB_DEFUSED:
		if (m_iTeam == CT && TheCSBots()->GetBombTimeLeft() < 2.0)
			GetChatter()->Say("BarelyDefused");
		return;
	case EVENT_BOMB_PICKED_UP:
	{
		if (m_iTeam == CT && pPlayer)
		{
			// check if we're close enough to hear it
			const float bombPickupHearRangeSq = 1000.0f * 1000.0f;
			if ((pev->origin - pPlayer->pev->origin).LengthSquared() < bombPickupHearRangeSq)
			{
				GetChatter()->TheyPickedUpTheBomb();
			}
		}
		return;
	}
	case EVENT_BOMB_BEEP:
	{
		// if we don't know where the bomb is, but heard it beep, we've discovered it
		if (GetGameState()->IsPlantedBombLocationKnown() == false)
		{
			// check if we're close enough to hear it
			const float bombBeepHearRangeSq = 1000.0f * 1000.0f;
			if ((pev->origin - pEntity->pev->origin).LengthSquared() < bombBeepHearRangeSq)
			{
				// radio the news to our team
				if (m_iTeam == CT && GetGameState()->GetPlantedBombsite() == CSGameState::UNKNOWN)
				{
					const CCSBotManager::Zone *zone = TheCSBots()->GetZone(&pEntity->pev->origin);
					if (zone)
					{
						GetChatter()->FoundPlantedBomb(zone->m_index);
					}
				}

				// remember where the bomb is
				GetGameState()->UpdatePlantedBomb(&pEntity->pev->origin);
			}
		}
		return;
	}
	case EVENT_BOMB_PLANTED:
	{
		// if we're a CT, forget what we're doing and go after the bomb
		if (m_iTeam == CT)
		{
			Idle();
		}

		// if we are following someone, stop following
		if (IsFollowing())
		{
			StopFollowing();
			Idle();
		}

		OnEvent(EVENT_BOMB_BEEP, pOther);
		return;
	}
	case EVENT_BOMB_DEFUSE_ABORTED:
		PrintIfWatched("BOMB DEFUSE ABORTED\n");
		return;
	case EVENT_WEAPON_FIRED:
	case EVENT_WEAPON_FIRED_ON_EMPTY:
	case EVENT_WEAPON_RELOADED:
	{
		if (m_enemy == pEntity && IsUsingKnife())
			ForceRun(5.0f);
		break;
	}
	default:
		break;
	}

	// Process radio events from our team
	if (pPlayer && BotRelationship(pPlayer) == BOT_TEAMMATE && event > EVENT_START_RADIO_1 && event < EVENT_END_RADIO)
	{
		// TODO: Distinguish between radio commands and responses
		if (event != EVENT_RADIO_AFFIRMATIVE && event != EVENT_RADIO_NEGATIVE && event != EVENT_RADIO_REPORTING_IN)
		{
			m_lastRadioCommand = event;
			m_lastRadioRecievedTimestamp = gpGlobals->time;
			m_radioSubject = pPlayer;
			m_radioPosition = pPlayer->pev->origin;
		}
	}

	// player_follows needs a player
	if (!pPlayer)
		return;

	if (!IsRogue() && event == EVENT_HOSTAGE_CALLED_FOR_HELP && m_iTeam == CT && IsHunting())
	{
		if ((pEntity->pev->origin - pev->origin).IsLengthGreaterThan(1000.0f))
			return;

		Vector vecHostageOrigin = pEntity->Center();
		if (IsVisible(&vecHostageOrigin))
		{
			m_task = COLLECT_HOSTAGES;
			m_taskEntity = nullptr;

			Run();
			m_goalEntity = pEntity;

			MoveTo(&pEntity->pev->origin, m_hostageEscortCount == 0 ? SAFEST_ROUTE : FASTEST_ROUTE);
			PrintIfWatched("I'm fetching a hostage that called out to me\n");

			return;
		}
	}

	// don't pay attention to noise that friends make
	if (!IsEnemy(pPlayer))
		return;

	float range;
	PriorityType priority;
	bool isHostile;

	if (IsGameEventAudible(event, pEntity, pOther, &range, &priority, &isHostile) == false)
		return;

	if (event == EVENT_HOSTAGE_USED)
	{
		if (m_iTeam == CT)
			return;

		if ((pEntity->pev->origin - pev->origin).IsLengthGreaterThan(range))
			return;

		GetChatter()->HostagesBeingTaken();

		if (!GetGameState()->GetNearestVisibleFreeHostage() && m_task != GUARD_HOSTAGE_RESCUE_ZONE && GuardRandomZone())
		{
			m_task = GUARD_HOSTAGE_RESCUE_ZONE;
			m_taskEntity = nullptr;

			SetDisposition(OPPORTUNITY_FIRE);
			PrintIfWatched("Trying to beat them to an escape zone!\n");
		}
	}

	// check if noise is close enough for us to hear
	const Vector *newNoisePosition = &pPlayer->pev->origin;
	float newNoiseDist = (pev->origin - *newNoisePosition).Length();
	if (newNoiseDist < range)
	{
		// we heard the sound
		if ((IsLocalPlayerWatchingMe() && cv_bot_debug.value == 3.0f) || cv_bot_debug.value == 4.0f)
		{
			PrintIfWatched("Heard noise (%s from %s, pri %s, time %3.1f)\n",
				(event == EVENT_WEAPON_FIRED) ? "Weapon fire " : "",
				STRING(pPlayer->pev->netname),
				(priority == PRIORITY_HIGH) ? "HIGH" : ((priority == PRIORITY_MEDIUM) ? "MEDIUM" : "LOW"),
				gpGlobals->time);
		}

		if (event == EVENT_PLAYER_FOOTSTEP && IsUsingSniperRifle() && newNoiseDist < 300.0)
			EquipPistol();

		// should we pay attention to it
		// if noise timestamp is zero, there is no prior noise
		if (m_noiseTimestamp > 0.0f)
		{
			// only overwrite recent sound if we are louder (closer), or more important - if old noise was long ago, its faded
			const float shortTermMemoryTime = 3.0f;
			if (gpGlobals->time - m_noiseTimestamp < shortTermMemoryTime)
			{
				// prior noise is more important - ignore new one
				if (priority < m_noisePriority)
					return;

				float oldNoiseDist = (pev->origin - m_noisePosition).Length();
				if (newNoiseDist >= oldNoiseDist)
					return;
			}
		}

		// find the area in which the noise occured
		// TODO: Better handle when noise occurs off the nav mesh
		// TODO: Make sure noise area is not through a wall or ceiling from source of noise
		// TODO: Change GetNavTravelTime to better deal with NULL destination areas
		CNavArea *noiseArea = TheNavAreaGrid.GetNavArea(newNoisePosition);
		if (!noiseArea)
			noiseArea = TheNavAreaGrid.GetNearestNavArea(newNoisePosition);

		if (!noiseArea)
		{
			PrintIfWatched("  *** Noise occurred off the nav mesh - ignoring!\n");
			return;
		}

		m_noiseArea = noiseArea;

		// remember noise priority
		m_noisePriority = priority;

		// randomize noise position in the area a bit - hearing isn't very accurate
		// the closer the noise is, the more accurate our placement
		// TODO: Make sure not to pick a position on the opposite side of ourselves.
		const float maxErrorRadius = 400.0f;
		const float maxHearingRange = 2000.0f;
		float errorRadius = maxErrorRadius * newNoiseDist / maxHearingRange;

		m_noisePosition.x = newNoisePosition->x + RANDOM_FLOAT(-errorRadius, errorRadius);
		m_noisePosition.y = newNoisePosition->y + RANDOM_FLOAT(-errorRadius, errorRadius);

		// make sure noise position remains in the same area
		m_noiseArea->GetClosestPointOnArea(&m_noisePosition, &m_noisePosition);

		m_isNoiseTravelRangeChecked = false;

		// note when we heard the noise
		m_noiseTimestamp = gpGlobals->time;
	}
}
