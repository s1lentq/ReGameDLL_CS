#include "precompiled.h"

// range for snipers to select a hiding spot
const float sniperHideRange = 2000.0f;

// The Idle state.
// We never stay in the Idle state - it is a "home base" for the state machine that
// does various checks to determine what we should do next.

/* <5a12ee> ../cstrike/dlls/bot/states/cs_bot_idle.cpp:26 */
void IdleState::__MAKE_VHOOK(OnEnter)(CCSBot *me)
{
	me->DestroyPath();
	me->SetEnemy(NULL);

	// lurking death
	if (me->IsUsingKnife() && me->IsWellPastSafe() && !me->IsHurrying())
		me->Walk();

	// Since Idle assigns tasks, we assume that coming back to Idle means our task is complete
	me->SetTask(CCSBot::SEEK_AND_DESTROY);
	me->SetDisposition(CCSBot::ENGAGE_AND_INVESTIGATE);
}

/* <5a0c66> ../cstrike/dlls/bot/states/cs_bot_idle.cpp:46 */
void IdleState::__MAKE_VHOOK(OnUpdate)(CCSBot *me)
{
	// all other states assume GetLastKnownArea() is valid, ensure that it is
	if (me->GetLastKnownArea() == NULL && me->StayOnNavMesh() == false)
		return;

	// zombies never leave the Idle state
	if (cv_bot_zombie.value > 0.0f)
	{
		me->ResetStuckMonitor();
		return;
	}

	// if we are in the early "safe" time, grab a knife or grenade
	if (me->IsSafe())
	{
		// if we have a grenade, use it
		if (!me->EquipGrenade())
		{
			// high-skill bots run with the knife
			if (me->GetProfile()->GetSkill() > 0.33f)
			{
				me->EquipKnife();
			}
		}
	}

	CCSBotManager *ctrl = TheCSBots();

	// if round is over, hunt
	if (me->GetGameState()->IsRoundOver())
	{
		// if we are escorting hostages, try to get to the rescue zone
		if (me->GetHostageEscortCount())
		{
			const CCSBotManager::Zone *zone = ctrl->GetClosestZone(me->GetLastKnownArea(), PathCost(me, FASTEST_ROUTE));
			me->SetTask(CCSBot::RESCUE_HOSTAGES);
			me->Run();
			me->SetDisposition(CCSBot::SELF_DEFENSE);
			me->MoveTo(ctrl->GetRandomPositionInZone(zone), FASTEST_ROUTE);
			me->PrintIfWatched("Trying to rescue hostages at the end of the round\n");
			return;
		}

		me->Hunt();
		return;
	}

	const float defenseSniperCampChance = 75.0f;
	const float offenseSniperCampChance = 10.0f;

	// if we were following someone, continue following them
	if (me->IsFollowing())
	{
		me->ContinueFollowing();
		return;
	}

	// Scenario logic
	switch (ctrl->GetScenario())
	{
		case CCSBotManager::SCENARIO_DEFUSE_BOMB:
		{
			static int inumpo = 0;
			inumpo++;

			// if this is a bomb game and we have the bomb, go plant it
			if (me->m_iTeam == TERRORIST)
			{
				if (me->GetGameState()->IsBombPlanted())
				{
					if (me->GetGameState()->GetPlantedBombsite() != CSGameState::UNKNOWN)
					{
						// T's always know where the bomb is - go defend it
						const CCSBotManager::Zone *zone = ctrl->GetZone(me->GetGameState()->GetPlantedBombsite());
						me->SetTask(CCSBot::GUARD_TICKING_BOMB);

						Place place = TheNavAreaGrid.GetPlace(&zone->m_center);
						if (place != UNDEFINED_PLACE)
						{
							// pick a random hiding spot in this place
							const Vector *spot = FindRandomHidingSpot(me, place, me->IsSniper());
							if (spot != NULL)
							{
								me->Hide(spot);
								return;
							}
						}

						// hide nearby
						me->Hide(TheNavAreaGrid.GetNearestNavArea(&zone->m_center));
						return;
					}
					else
					{
						// ask our teammates where the bomb is
						me->GetChatter()->RequestBombLocation();

						// we dont know where the bomb is - we must search the bombsites
						int zoneIndex = me->GetGameState()->GetNextBombsiteToSearch();

						// move to bombsite - if we reach it, we'll update its cleared status, causing us to select another
						const Vector *pos = ctrl->GetRandomPositionInZone(ctrl->GetZone(zoneIndex));
						if (pos != NULL)
						{
							me->SetTask(CCSBot::FIND_TICKING_BOMB);
							me->MoveTo(pos);
							return;
						}
					}
				}
				else if (me->IsCarryingBomb())
				{
					// if we're at a bomb site, plant the bomb
					if (me->IsAtBombsite())
					{
						// plant it
						me->SetTask(CCSBot::PLANT_BOMB);
						me->PlantBomb();

						// radio to the team
						me->GetChatter()->PlantingTheBomb(me->GetPlace());

						return;
					}
					else if (ctrl->IsTimeToPlantBomb())
					{
						// move to the closest bomb site
						const CCSBotManager::Zone *zone = ctrl->GetClosestZone(me->GetLastKnownArea(), PathCost(me));
						if (zone != NULL)
						{
							// pick a random spot within the bomb zone
							const Vector *pos = ctrl->GetRandomPositionInZone(zone);
							if (pos != NULL)
							{
								// move to bombsite
								me->SetTask(CCSBot::PLANT_BOMB);
								me->Run();
								me->MoveTo(pos);

								return;
							}
						}
					}
				}
				else
				{
					// small chance of sniper camping on offense, if we aren't carrying the bomb
					if (me->GetFriendsRemaining() && me->IsSniper() && RANDOM_FLOAT(0, 100.0f) < offenseSniperCampChance)
					{
						me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
						me->Hide(me->GetLastKnownArea(), RANDOM_FLOAT(10.0f, 30.0f), sniperHideRange);
						me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
						me->PrintIfWatched("Sniping!\n");
						return;
					}

					// if the bomb is loose (on the ground), go get it
					if (me->NoticeLooseBomb())
					{
						me->FetchBomb();
						return;
					}

					// if bomb has been planted, and we hear it, move to a hiding spot near the bomb and guard it
					if (!me->IsRogue() && me->GetGameState()->IsBombPlanted() && me->GetGameState()->GetBombPosition() != NULL)
					{
						const Vector *bombPos = me->GetGameState()->GetBombPosition();
						if (bombPos != NULL)
						{
							me->SetTask(CCSBot::GUARD_TICKING_BOMB);
							me->Hide(TheNavAreaGrid.GetNavArea(bombPos));
							return;
						}
					}
				}
			}
			// CT
			else
			{
				if (me->GetGameState()->IsBombPlanted())
				{
					// if the bomb has been planted, attempt to defuse it
					const Vector *bombPos = me->GetGameState()->GetBombPosition();
					if (bombPos != NULL)
					{
						// if someone is defusing the bomb, guard them
						if (ctrl->GetBombDefuser())
						{
							if (!me->IsRogue())
							{
								me->SetTask(CCSBot::GUARD_BOMB_DEFUSER);
								me->Hide(TheNavAreaGrid.GetNavArea(bombPos));
								return;
							}
						}
						else if (me->IsDoingScenario())
						{
							// move to the bomb and defuse it
							me->SetTask(CCSBot::DEFUSE_BOMB);
							me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
							me->MoveTo(bombPos);
							return;
						}
						else
						{
							// we're not allowed to defuse, guard the bomb zone
							me->SetTask(CCSBot::GUARD_BOMB_ZONE);
							me->Hide(TheNavAreaGrid.GetNavArea(bombPos));
							me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
							return;
						}
					}
					else if (me->GetGameState()->GetPlantedBombsite() != CSGameState::UNKNOWN)
					{
						// we know which bombsite, but not exactly where the bomb is, go there
						const CCSBotManager::Zone *zone = ctrl->GetZone(me->GetGameState()->GetPlantedBombsite());
						if (zone != NULL)
						{
							if (me->IsDoingScenario())
							{
								me->SetTask(CCSBot::DEFUSE_BOMB);
								me->MoveTo(&zone->m_center);
								me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
								return;
							}
							else
							{
								// we're not allowed to defuse, guard the bomb zone
								me->SetTask(CCSBot::GUARD_BOMB_ZONE);
								me->Hide(TheNavAreaGrid.GetNavArea(&zone->m_center));
								me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
								return;
							}
						}
					}
					else
					{
						// we dont know where the bomb is - we must search the bombsites
						// find closest un-cleared bombsite
						const CCSBotManager::Zone *zone = NULL;
						float travelDistance = 9999999.9f;

						for (int z = 0; z < ctrl->GetZoneCount(); ++z)
						{
							if (ctrl->GetZone(z)->m_areaCount == 0)
								continue;

							// don't check bombsites that have been cleared
							if (me->GetGameState()->IsBombsiteClear(z))
								continue;

							// just use the first overlapping nav area as a reasonable approximation
							ShortestPathCost pathCost = ShortestPathCost();
							float_precision dist = NavAreaTravelDistance(me->GetLastKnownArea(), TheNavAreaGrid.GetNearestNavArea(&ctrl->GetZone(z)->m_center), pathCost);

							if (/*dist >= 0.0f && */dist < travelDistance)
							{
								zone = ctrl->GetZone(z);
								travelDistance = dist;
							}
						}

						if (zone != NULL)
						{
							const float farAwayRange = 2000.0f;
							if (travelDistance > farAwayRange)
							{
								zone = NULL;
							}
						}

						// if closest bombsite is "far away", pick one at random
						if (zone == NULL)
						{
							int zoneIndex = me->GetGameState()->GetNextBombsiteToSearch();
							zone = ctrl->GetZone(zoneIndex);
						}

						// move to bombsite - if we reach it, we'll update its cleared status, causing us to select another
						if (zone != NULL)
						{
							const Vector *pos = ctrl->GetRandomPositionInZone(zone);
							if (pos != NULL)
							{
								me->SetTask(CCSBot::FIND_TICKING_BOMB);
								me->MoveTo(pos);
								return;
							}
						}
					}

					assert((0, "A CT bot doesn't know what to do while the bomb is planted!\n"));
				}

				// if we have a sniper rifle, we like to camp, whether rogue or not
				if (me->IsSniper())
				{
					if (RANDOM_FLOAT(0, 100) <= defenseSniperCampChance)
					{
						CNavArea *snipingArea = NULL;

						// if the bomb is loose, snipe near it
						if (me->GetGameState()->IsLooseBombLocationKnown())
						{
							snipingArea = TheNavAreaGrid.GetNearestNavArea(me->GetGameState()->GetBombPosition());
							me->PrintIfWatched("Sniping near loose bomb\n");
						}
						else
						{
							// snipe bomb zone(s)
							const CCSBotManager::Zone *zone = ctrl->GetRandomZone();
							if (zone != NULL)
							{
								snipingArea = ctrl->GetRandomAreaInZone(zone);
								me->PrintIfWatched("Sniping near bombsite\n");
							}
						}

						if (snipingArea != NULL)
						{
							me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
							me->Hide(snipingArea, -1.0f, sniperHideRange);
							me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
							return;
						}
					}
				}

				// rogues just hunt, unless they want to snipe
				// if the whole team has decided to rush, hunt
				// if we know the bomb is dropped, hunt for enemies and the loose bomb
				if (me->IsRogue() || ctrl->IsDefenseRushing() || me->GetGameState()->IsLooseBombLocationKnown())
				{
					me->Hunt();
					return;
				}

				// the lower our morale gets, the more we want to camp the bomb zone(s)
				// only decide to camp at the start of the round, or if we haven't seen anything for a long time
				if (me->IsSafe() || me->HasNotSeenEnemyForLongTime())
				{
					float guardBombsiteChance = -34.0f * me->GetMorale();

					if (RANDOM_FLOAT(0.0f, 100.0f) < guardBombsiteChance)
					{
						float guardRange = 500.0f + 100.0f * (me->GetMorale() + 3);

						// guard bomb zone(s)
						const CCSBotManager::Zone *zone = ctrl->GetRandomZone();
						if (zone != NULL)
						{
							CNavArea *area = ctrl->GetRandomAreaInZone(zone);
							if (area != NULL)
							{
								me->PrintIfWatched("I'm guarding a bombsite\n");
								me->GetChatter()->AnnouncePlan("GoingToDefendBombsite", area->GetPlace());
								me->SetTask(CCSBot::GUARD_BOMB_ZONE);
								me->Hide(area, -1.0, guardRange);
								me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
								return;
							}
						}
					}
				}
			}
			break;
		}
		case CCSBotManager::SCENARIO_ESCORT_VIP:
		{
			if (me->m_iTeam == TERRORIST)
			{
				// if we have a sniper rifle, we like to camp, whether rogue or not
				if (me->IsSniper())
				{
					if (RANDOM_FLOAT(0, 100) <= defenseSniperCampChance)
					{
						// snipe escape zone(s)
						const CCSBotManager::Zone *zone = ctrl->GetRandomZone();
						if (zone != NULL)
						{
							CNavArea *area = ctrl->GetRandomAreaInZone(zone);
							if (area != NULL)
							{
								me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
								me->Hide(area, -1.0, sniperHideRange);
								me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
								me->PrintIfWatched("Sniping near escape zone\n");
								return;
							}
						}
					}
				}

				// rogues just hunt, unless they want to snipe
				// if the whole team has decided to rush, hunt
				if (me->IsRogue() || ctrl->IsDefenseRushing())
					break;

				// the lower our morale gets, the more we want to camp the escape zone(s)
				float guardEscapeZoneChance = -34.0f * me->GetMorale();

				if (RANDOM_FLOAT(0.0f, 100.0f) < guardEscapeZoneChance)
				{
					// guard escape zone(s)
					const CCSBotManager::Zone *zone = ctrl->GetRandomZone();
					if (zone != NULL)
					{
						CNavArea *area = ctrl->GetRandomAreaInZone(zone);
						if (area != NULL)
						{
							// guard the escape zone - stay closer if our morale is low
							me->SetTask(CCSBot::GUARD_VIP_ESCAPE_ZONE);
							me->PrintIfWatched("I'm guarding an escape zone\n");

							float escapeGuardRange = 750.0f + 250.0f * (me->GetMorale() + 3);
							me->Hide(area, -1.0, escapeGuardRange);
							me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
							return;
						}
					}
				}
			}
			// CT
			else
			{
				if (me->m_bIsVIP)
				{
					// if early in round, pick a random zone, otherwise pick closest zone
					const float earlyTime = 20.0f;
					const CCSBotManager::Zone *zone = NULL;

					if (ctrl->GetElapsedRoundTime() < earlyTime)
					{
						// pick random zone
						zone = ctrl->GetRandomZone();
					}
					else
					{
						// pick closest zone
						zone = ctrl->GetClosestZone(me->GetLastKnownArea(), PathCost(me));
					}

					if (zone != NULL)
					{
						// pick a random spot within the escape zone
						const Vector *pos = ctrl->GetRandomPositionInZone(zone);
						if (pos != NULL)
						{
							// move to escape zone
							me->SetTask(CCSBot::VIP_ESCAPE);
							me->Run();
							me->MoveTo(pos);

							// tell team to follow
							const float repeatTime = 30.0f;
							if (me->GetFriendsRemaining() && ctrl->GetRadioMessageInterval(EVENT_RADIO_FOLLOW_ME, me->m_iTeam) > repeatTime)
								me->SendRadioMessage(EVENT_RADIO_FOLLOW_ME);
							return;
						}
					}
				}
				else
				{
					// small chance of sniper camping on offense, if we aren't VIP
					if (me->GetFriendsRemaining() && me->IsSniper() && RANDOM_FLOAT(0, 100.0f) < offenseSniperCampChance)
					{
						me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
						me->Hide(me->GetLastKnownArea(), RANDOM_FLOAT(10.0f, 30.0f), sniperHideRange);
						me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
						me->PrintIfWatched("Sniping!\n");
						return;
					}
				}
			}
			break;
		}
		case CCSBotManager::SCENARIO_RESCUE_HOSTAGES:
		{
			if (me->m_iTeam == TERRORIST)
			{
				bool campHostages;

				// if we are in early game, camp the hostages
				if (me->IsSafe())
				{
					campHostages = true;
				}
				else if (me->GetGameState()->HaveSomeHostagesBeenTaken() || me->GetGameState()->AreAllHostagesBeingRescued())
				{
					campHostages = false;
				}
				else
				{
					// later in the game, camp either hostages or escape zone
					const float campZoneChance = 100.0f * (ctrl->GetElapsedRoundTime() - me->GetSafeTime()) / 120.0f;
					campHostages = (RANDOM_FLOAT(0, 100) > campZoneChance) ? true : false;
				}

				// if we have a sniper rifle, we like to camp, whether rogue or not
				if (me->IsSniper())
				{
					if (RANDOM_FLOAT(0, 100) <= defenseSniperCampChance)
					{
						const Vector *hostagePos = me->GetGameState()->GetRandomFreeHostagePosition();
						if (hostagePos != NULL && campHostages)
						{
							me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
							me->PrintIfWatched("Sniping near hostages\n");
							me->Hide(TheNavAreaGrid.GetNearestNavArea(hostagePos), -1.0, sniperHideRange);
							me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
							return;
						}
						else
						{
							// camp the escape zone(s)
							if (me->GuardRandomZone(sniperHideRange))
							{
								me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
								me->PrintIfWatched("Sniping near a rescue zone\n");
								me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
								return;
							}
						}
					}
				}

				// if safe time is up, and we stumble across a hostage, guard it
				if (!me->IsSafe() && !me->IsRogue())
				{
					CBaseEntity *hostage = me->GetGameState()->GetNearestVisibleFreeHostage();
					if (hostage != NULL)
					{
						// we see a free hostage, guard it
						CNavArea *area = TheNavAreaGrid.GetNearestNavArea(&hostage->pev->origin);
						if (area != NULL)
						{
							me->SetTask(CCSBot::GUARD_HOSTAGES);
							me->Hide(area);
							me->PrintIfWatched("I'm guarding hostages I found\n");
							// don't chatter here - he'll tell us when he's in his hiding spot
							return;
						}
					}
				}

				// decide if we want to hunt, or guard
				const float huntChance = 70.0f + 25.0f * me->GetMorale();

				// rogues just hunt, unless they want to snipe
				// if the whole team has decided to rush, hunt
				if (me->GetFriendsRemaining())
				{
					if (me->IsRogue() || ctrl->IsDefenseRushing() || RANDOM_FLOAT(0, 100) < huntChance)
					{
						me->Hunt();
						return;
					}
				}

				// decide whether to camp the hostages or the escape zones
				const Vector *hostagePos = me->GetGameState()->GetRandomFreeHostagePosition();
				if (hostagePos != NULL && campHostages)
				{
					CNavArea *area = TheNavAreaGrid.GetNearestNavArea(hostagePos);
					if (area != NULL)
					{
						// guard the hostages - stay closer to hostages if our morale is low
						me->SetTask(CCSBot::GUARD_HOSTAGES);
						me->PrintIfWatched("I'm guarding hostages\n");

						float hostageGuardRange = 750.0f + 250.0f * (me->GetMorale() + 3);
						me->Hide(area, -1.0, hostageGuardRange);
						me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);

						if (RANDOM_FLOAT(0, 100) < 50)
							me->GetChatter()->GuardingHostages(area->GetPlace(), IS_PLAN);

						return;
					}
				}

				// guard rescue zone(s)
				if (me->GuardRandomZone())
				{
					me->SetTask(CCSBot::GUARD_HOSTAGE_RESCUE_ZONE);
					me->PrintIfWatched("I'm guarding a rescue zone\n");
					me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
					me->GetChatter()->GuardingHostageEscapeZone(IS_PLAN);
					return;
				}
			}
			// CT
			else
			{
				// only decide to do something else if we aren't already rescuing hostages
				if (!me->GetHostageEscortCount())
				{
					// small chance of sniper camping on offense
					if (me->GetFriendsRemaining() && me->IsSniper() && RANDOM_FLOAT(0, 100.0f) < offenseSniperCampChance)
					{
						me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
						me->Hide(me->GetLastKnownArea(), RANDOM_FLOAT(10.0f, 30.0f), sniperHideRange);
						me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
						me->PrintIfWatched("Sniping!\n");
						return;
					}

					if (me->GetFriendsRemaining() && !me->GetHostageEscortCount())
					{
						// rogues just hunt, unless all friends are dead
						// if we have friends left, we might go hunting instead of hostage rescuing
						const float huntChance = 33.3f;
						if (me->IsRogue() || RANDOM_FLOAT(0.0f, 100.0f) < huntChance)
						{
							me->Hunt();
							return;
						}
					}
				}

				// look for free hostages - CT's have radar so they know where hostages are at all times
				CHostage *hostage = me->GetGameState()->GetNearestFreeHostage();

				// if we are not allowed to do the scenario, guard the hostages to clear the area for the human(s)
				if (!me->IsDoingScenario())
				{
					if (hostage != NULL)
					{
						CNavArea *area = TheNavAreaGrid.GetNearestNavArea(&hostage->pev->origin);
						if (area != NULL)
						{
							me->SetTask(CCSBot::GUARD_HOSTAGES);
							me->Hide(area);
							me->PrintIfWatched("I'm securing the hostages for a human to rescue\n");
							return;
						}
					}

					me->Hunt();
					return;
				}

				bool fetchHostages = false;
				bool rescueHostages = false;
				const CCSBotManager::Zone *zone = NULL;
				me->SetGoalEntity(NULL);

				// if we are escorting hostages, determine where to take them
				if (me->GetHostageEscortCount())
					zone = ctrl->GetClosestZone(me->GetLastKnownArea(), PathCost(me, FASTEST_ROUTE));

				// if we are escorting hostages and there are more hostages to rescue,
				// determine whether it's faster to rescue the ones we have, or go get the remaining ones
				if (hostage != NULL)
				{
					if (zone != NULL)
					{
						PathCost pathCost(me, FASTEST_ROUTE);
						float toZone = NavAreaTravelDistance(me->GetLastKnownArea(), zone->m_area[0], pathCost);
						float toHostage = NavAreaTravelDistance(me->GetLastKnownArea(), TheNavAreaGrid.GetNearestNavArea(&hostage->pev->origin), pathCost);

						if (toHostage < 0.0f)
						{
							rescueHostages = true;
						}
						else
						{
							if (toZone < toHostage)
								rescueHostages = true;
							else
								fetchHostages = true;
						}
					}
					else
					{
						fetchHostages = true;
					}
				}
				else if (zone != NULL)
				{
					rescueHostages = true;
				}

				if (fetchHostages)
				{
					// go get hostages
					me->SetTask(CCSBot::COLLECT_HOSTAGES);
					me->Run();
					me->SetGoalEntity(hostage);
					me->ResetWaitForHostagePatience();

					// if we already have some hostages, move to the others by the quickest route
					RouteType route = (me->GetHostageEscortCount()) ? FASTEST_ROUTE : SAFEST_ROUTE;
					me->MoveTo(&hostage->pev->origin, route);
					me->PrintIfWatched("I'm collecting hostages\n");
					return;
				}

				if (rescueHostages)
				{
					me->SetTask(CCSBot::RESCUE_HOSTAGES);
					me->Run();
					me->SetDisposition(CCSBot::SELF_DEFENSE);
					me->MoveTo(ctrl->GetRandomPositionInZone(zone), FASTEST_ROUTE);
					me->PrintIfWatched("I'm rescuing hostages\n");
					me->GetChatter()->EscortingHostages();
					return;
				}
			}
			break;
		}
		// deathmatch
		default:
		{
			// sniping check
			if (me->GetFriendsRemaining() && me->IsSniper() && RANDOM_FLOAT(0, 100.0f) < offenseSniperCampChance)
			{
				me->SetTask(CCSBot::MOVE_TO_SNIPER_SPOT);
				me->Hide(me->GetLastKnownArea(), RANDOM_FLOAT(10.0f, 30.0f), sniperHideRange);
				me->SetDisposition(CCSBot::OPPORTUNITY_FIRE);
				me->PrintIfWatched("Sniping!\n");
				return;
			}
			break;
		}
	}

	// if we have nothing special to do, go hunting for enemies
	me->Hunt();
}
