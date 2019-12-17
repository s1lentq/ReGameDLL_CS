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

// Returns true if the radio message is an order to do something
// NOTE: "Report in" is not considered a "command" because it doesnt ask the bot to go somewhere, or change its mind
bool CCSBot::IsRadioCommand(GameEventType event) const
{
	if (event == EVENT_RADIO_AFFIRMATIVE
		|| event == EVENT_RADIO_NEGATIVE
		|| event == EVENT_RADIO_ENEMY_SPOTTED
		|| event == EVENT_RADIO_SECTOR_CLEAR
		|| event == EVENT_RADIO_REPORTING_IN
		|| event == EVENT_RADIO_REPORT_IN_TEAM
		|| event == EVENT_RADIO_ENEMY_DOWN)
		return false;

	return true;
}

// Respond to radio commands from HUMAN players
void CCSBot::RespondToRadioCommands()
{
	// bots use the chatter system to respond to each other
	if (m_radioSubject.IsValid() && m_radioSubject->IsPlayer())
	{
		if (m_radioSubject->IsBot())
		{
			m_lastRadioCommand = EVENT_INVALID;
			return;
		}
	}

	if (m_lastRadioCommand == EVENT_INVALID)
		return;

	// a human player has issued a radio command
	GetChatter()->ResetRadioSilenceDuration();

	// if we are doing something important, ignore the radio
	// unless it is a "report in" request - we can do that while we continue to do other things
	// TODO: Create "uninterruptable" flag
	if (m_lastRadioCommand != EVENT_RADIO_REPORT_IN_TEAM)
	{
		if (IsBusy())
		{
			// consume command
			m_lastRadioCommand = EVENT_INVALID;
			return;
		}
	}

	// wait for reaction time before responding
	// delay needs to be long enough for the radio message we're responding to to finish
	float respondTime = 1.0f + 2.0f * GetProfile()->GetReactionTime();
	if (IsRogue())
		respondTime += 2.0f;

	if (gpGlobals->time - m_lastRadioRecievedTimestamp < respondTime)
		return;

	// rogues won't follow commands, unless already following the player
	if (!IsFollowing() && IsRogue())
	{
		if (IsRadioCommand(m_lastRadioCommand))
		{
			GetChatter()->Negative();
		}

		// consume command
		m_lastRadioCommand = EVENT_INVALID;
		return;
	}

	if (!m_radioSubject)
		return;

	// respond to command
	bool canDo = false;
	const float inhibitAutoFollowDuration = 60.0f;
	switch (m_lastRadioCommand)
	{
	case EVENT_RADIO_REPORT_IN_TEAM:
	{
		GetChatter()->ReportingIn();
		break;
	}
	case EVENT_RADIO_FOLLOW_ME:
	case EVENT_RADIO_COVER_ME:
	case EVENT_RADIO_STICK_TOGETHER_TEAM:
	case EVENT_RADIO_REGROUP_TEAM:
	{
		if (!IsFollowing())
		{
			Follow(m_radioSubject);
			m_radioSubject->AllowAutoFollow();
			canDo = true;
		}
		break;
	}
	case EVENT_RADIO_ENEMY_SPOTTED:
	case EVENT_RADIO_NEED_BACKUP:
	case EVENT_RADIO_TAKING_FIRE:
	{
		if (!IsFollowing())
		{
			Follow(m_radioSubject);
			GetChatter()->Say("OnMyWay");
			m_radioSubject->AllowAutoFollow();
			canDo = false;
		}
		break;
	}
	case EVENT_RADIO_TEAM_FALL_BACK:
	{
		if (TryToRetreat())
			canDo = true;
		break;
	}
	case EVENT_RADIO_HOLD_THIS_POSITION:
	{
		// find the leader's area
		SetTask(HOLD_POSITION);
		StopFollowing();
		m_radioSubject->InhibitAutoFollow(inhibitAutoFollowDuration);
		Hide(TheNavAreaGrid.GetNearestNavArea(&m_radioPosition));
		canDo = true;
		break;
	}
	case EVENT_RADIO_GO_GO_GO:
	case EVENT_RADIO_STORM_THE_FRONT:
	{
		StopFollowing();
		Hunt();
		canDo = true;
		m_radioSubject->InhibitAutoFollow(inhibitAutoFollowDuration);
		break;
	}
	case EVENT_RADIO_GET_OUT_OF_THERE:
	{
		if (TheCSBots()->IsBombPlanted())
		{
			EscapeFromBomb();
			m_radioSubject->InhibitAutoFollow(inhibitAutoFollowDuration);
			canDo = true;
		}
		break;
	}
	case EVENT_RADIO_SECTOR_CLEAR:
	{
		// if this is a defusal scenario, and the bomb is planted,
		// and a human player cleared a bombsite, check it off our list too
		if (TheCSBots()->GetScenario() == CCSBotManager::SCENARIO_DEFUSE_BOMB)
		{
			if (m_iTeam == CT && TheCSBots()->IsBombPlanted())
			{
				const CCSBotManager::Zone *zone = TheCSBots()->GetClosestZone(m_radioSubject);
				if (zone)
				{
					GetGameState()->ClearBombsite(zone->m_index);

					// if we are huting for the planted bomb, re-select bombsite
					if (GetTask() == FIND_TICKING_BOMB)
						Idle();

					canDo = true;
				}
			}
		}
		break;
	}
	default:
		// ignore all other radio commands for now
		return;
	}

	if (canDo)
	{
		// affirmative
		GetChatter()->Affirmative();

		// if we agreed to follow a new command, put away our grenade
		if (IsRadioCommand(m_lastRadioCommand) && IsUsingGrenade())
		{
			EquipBestWeapon();
		}
	}

	// consume command
	m_lastRadioCommand = EVENT_INVALID;
}

// Send voice chatter.  Also sends the entindex.
void CCSBot::StartVoiceFeedback(float duration)
{
	m_voiceFeedbackStartTimestamp = gpGlobals->time;
	m_voiceFeedbackEndTimestamp = duration + gpGlobals->time;

	CBasePlayer *pPlayer = nullptr;
	while ((pPlayer = GetNextRadioRecipient(pPlayer)))
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgBotVoice, nullptr, pPlayer->pev);
			WRITE_BYTE(1);				// active is talking
			WRITE_BYTE(entindex());		// client index speaking
		MESSAGE_END();
	}
}

void CCSBot::EndVoiceFeedback(bool force)
{
	if (!force && !m_voiceFeedbackEndTimestamp)
		return;

	m_voiceFeedbackEndTimestamp = 0;

	MESSAGE_BEGIN(MSG_ALL, gmsgBotVoice);
		WRITE_BYTE(0);
		WRITE_BYTE(ENTINDEX(edict()));
	MESSAGE_END();
}

// Decide if we should move to help the player, return true if we will
bool CCSBot::RespondToHelpRequest(CBasePlayer *them, Place place, float maxRange)
{
	if (IsRogue())
		return false;

	// if we're busy, ignore
	if (IsBusy())
		return false;

	// if we are too far away, ignore
	if (maxRange > 0.0f)
	{
		// compute actual travel distance
		PathCost pc(this);
		real_t travelDistance = NavAreaTravelDistance(m_lastKnownArea, TheNavAreaGrid.GetNearestNavArea(&them->pev->origin), pc);
		if (travelDistance < 0.0f)
			return false;

		if (travelDistance > maxRange)
			return false;
	}

	if (place == UNDEFINED_PLACE)
	{
		// if we have no "place" identifier, go directly to them

		// if we are already there, ignore
		float rangeSq = (them->pev->origin - pev->origin).LengthSquared();
		const float close = 750.0f * 750.0f;

		if (rangeSq < close)
			return true;

		MoveTo(&them->pev->origin, FASTEST_ROUTE);
	}
	else
	{
		// if we are already there, ignore
		if (GetPlace() == place)
			return true;

		// go to where help is needed
		const Vector *pos = GetRandomSpotAtPlace(place);
		if (pos)
		{
			MoveTo(pos, FASTEST_ROUTE);
		}
		else
		{
			MoveTo(&them->pev->origin, FASTEST_ROUTE);
		}
	}

	// acknowledge
	GetChatter()->Say("OnMyWay");

	return true;
}

// Send a radio message
void CCSBot::SendRadioMessage(GameEventType event)
{
	// make sure this is a radio event
	if (event <= EVENT_START_RADIO_1 || event >= EVENT_END_RADIO)
	{
		return;
	}

	PrintIfWatched("%3.1f: SendRadioMessage( %s )\n", gpGlobals->time, GameEventName[event]);

	// note the time the message was sent
	TheCSBots()->SetRadioMessageTimestamp(event, m_iTeam);

	m_lastRadioSentTimestamp = gpGlobals->time;

	char slot[2];
	slot[1] = '\0';

	if (event > EVENT_START_RADIO_1 && event < EVENT_START_RADIO_2)
	{
		slot[0] = '0' + event - EVENT_START_RADIO_1;
		ClientCommand("radio1");
		//Radio1(this, event - EVENT_START_RADIO_1);
	}
	else if (event > EVENT_START_RADIO_2 && event < EVENT_START_RADIO_3)
	{
		slot[0] = '0' + event - EVENT_START_RADIO_2;
		ClientCommand("radio2");
		//Radio2(this, event - EVENT_START_RADIO_2);
	}
	else
	{
		slot[0] = '0' + event - EVENT_START_RADIO_3;
		ClientCommand("radio3");
		//Radio3(this, event - EVENT_START_RADIO_3);
	}

	ClientCommand("menuselect", slot);
	ClientCommand("menuselect", "10");
}
