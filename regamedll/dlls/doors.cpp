#include "precompiled.h"

TYPEDESCRIPTION CBaseDoor::m_SaveData[] =
{
	DEFINE_FIELD(CBaseDoor, m_bHealthValue, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bMoveSnd, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bStopSnd, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bLockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bLockedSentence, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bUnlockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bUnlockedSentence, FIELD_CHARACTER),
};

IMPLEMENT_SAVERESTORE(CBaseDoor, CBaseToggle)

// play door or button locked or unlocked sounds.
// pass in pointer to valid locksound struct.
// if flocked is true, play 'door is locked' sound,
// otherwise play 'door is unlocked' sound
// NOTE: this routine is shared by doors and buttons
void PlayLockSounds(entvars_t *pev, locksound_t *pls, int flocked, int fbutton)
{
	// LOCKED SOUND

	// CONSIDER: consolidate the locksound_t struct (all entries are duplicates for lock/unlock)
	// CONSIDER: and condense this code.
	float flsoundwait;

	if (fbutton)
		flsoundwait = BUTTON_SOUNDWAIT;
	else
		flsoundwait = DOOR_SOUNDWAIT;

	if (flocked)
	{
		int fplaysound = (pls->sLockedSound && gpGlobals->time > pls->flwaitSound);
		int fplaysentence = (pls->sLockedSentence && !pls->bEOFLocked && gpGlobals->time > pls->flwaitSentence);
		float fvol;

		if (fplaysound && fplaysentence)
			fvol = 0.25f;
		else
			fvol = 1.0f;

		// if there is a locked sound, and we've debounced, play sound
		if (fplaysound)
		{
			// play 'door locked' sound
			EMIT_SOUND(ENT(pev), CHAN_ITEM, (char *)STRING(pls->sLockedSound), fvol, ATTN_NORM);
			pls->flwaitSound = gpGlobals->time + flsoundwait;
		}

		// if there is a sentence, we've not played all in list, and we've debounced, play sound
		if (fplaysentence)
		{
			// play next 'door locked' sentence in group
			int iprev = pls->iLockedSentence;

			pls->iLockedSentence = SENTENCEG_PlaySequentialSz(ENT(pev), STRING(pls->sLockedSentence), 0.85, ATTN_NORM, 0, 100, pls->iLockedSentence, FALSE);
			pls->iUnlockedSentence = 0;

			// make sure we don't keep calling last sentence in list
			pls->bEOFLocked = (iprev == pls->iLockedSentence);
			pls->flwaitSentence = gpGlobals->time + DOOR_SENTENCEWAIT;
		}
	}
	else
	{
		// UNLOCKED SOUND

		int fplaysound = (pls->sUnlockedSound && gpGlobals->time > pls->flwaitSound);
		int fplaysentence = (pls->sUnlockedSentence && !pls->bEOFUnlocked && gpGlobals->time > pls->flwaitSentence);
		float fvol;

		// if playing both sentence and sound, lower sound volume so we hear sentence
		if (fplaysound && fplaysentence)
			fvol = 0.25f;
		else
			fvol = 1.0f;

		// play 'door unlocked' sound if set
		if (fplaysound)
		{
			EMIT_SOUND(ENT(pev), CHAN_ITEM, (char *)STRING(pls->sUnlockedSound), fvol, ATTN_NORM);
			pls->flwaitSound = gpGlobals->time + flsoundwait;
		}

		// play next 'door unlocked' sentence in group
		if (fplaysentence)
		{
			int iprev = pls->iUnlockedSentence;

			pls->iUnlockedSentence = SENTENCEG_PlaySequentialSz(ENT(pev), STRING(pls->sUnlockedSentence), 0.85, ATTN_NORM, 0, 100, pls->iUnlockedSentence, FALSE);
			pls->iLockedSentence = 0;

			// make sure we don't keep calling last sentence in list
			pls->bEOFUnlocked = (iprev == pls->iUnlockedSentence);
			pls->flwaitSentence = gpGlobals->time + DOOR_SENTENCEWAIT;
		}
	}
}

// Cache user-entity-field values until spawn is called.
void CBaseDoor::KeyValue(KeyValueData *pkvd)
{
	//skin is used for content type
	if (FStrEq(pkvd->szKeyName, "skin"))
	{
		pev->skin = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "movesnd"))
	{
		m_bMoveSnd = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "stopsnd"))
	{
		m_bStopSnd = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "healthvalue"))
	{
		m_bHealthValue = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "locked_sound"))
	{
		m_bLockedSound = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "locked_sentence"))
	{
		m_bLockedSentence = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "unlocked_sound"))
	{
		m_bUnlockedSound = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "unlocked_sentence"))
	{
		m_bUnlockedSentence = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "WaveHeight"))
	{
		pev->scale = Q_atof(pkvd->szValue) * (1.0 / 8.0);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseToggle::KeyValue(pkvd);
	}
}

// QUAKED func_door (0 .5 .8) ? START_OPEN x DOOR_DONT_LINK TOGGLE
// if two doors touch, they are assumed to be connected and operate as a unit.

// TOGGLE causes the door to wait in both the start and end states for a trigger event.

// START_OPEN causes the door to move to its destination when spawned, and operate in reverse.
// It is used to temporarily or permanently close off an area when triggered (not usefull for
// touch or takedamage doors).

// "angle"	determines the opening direction
// "targetname"	if set, no touch field will be spawned and a remote button or trigger field activates the door.
// "health"	if set, door must be shot open
// "speed"	movement speed (100 default)
// "wait"	wait before returning (3 default, -1 = never return)
// "lip"	lip remaining at end of move (8 default)
// "dmg"	damage to inflict when blocked (2 default)
// "sounds"
// 0)	no sound
// 1)	stone
// 2)	base
// 3)	stone chain
// 4)	screechy metal
LINK_ENTITY_TO_CLASS(func_door, CBaseDoor, CCSDoor)

// func_water - same as a door.
LINK_ENTITY_TO_CLASS(func_water, CBaseDoor, CCSDoor)

void CBaseDoor::Spawn()
{
	Precache();
	SetMovedir(pev);

	// normal door
	if (pev->skin == 0)
	{
		if (pev->spawnflags & SF_DOOR_PASSABLE)
			pev->solid = SOLID_NOT;
		else
			pev->solid = SOLID_BSP;
	}
	else // special contents
	{
		pev->solid = SOLID_NOT;

		// water is silent for now
		pev->spawnflags |= SF_DOOR_ACTUALLY_WATER;
	}

	pev->movetype = MOVETYPE_PUSH;
	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->speed == 0)
		pev->speed = 100;

	m_vecPosition1 = pev->origin;

	// Subtract 2 from size because the engine expands bboxes by 1 in all directions making the size too big
	m_vecPosition2 = m_vecPosition1 + (pev->movedir * (Q_fabs(real_t(pev->movedir.x * (pev->size.x - 2))) + Q_fabs(real_t(pev->movedir.y * (pev->size.y - 2))) + Q_fabs(real_t(pev->movedir.z * (pev->size.z - 2))) - m_flLip));

	assert(("door start/end positions are equal", m_vecPosition1 != m_vecPosition2));

	if (pev->spawnflags & SF_DOOR_START_OPEN)
	{
		// swap pos1 and pos2, put door at pos2
		UTIL_SetOrigin(pev, m_vecPosition2);
		m_vecPosition2 = m_vecPosition1;
		m_vecPosition1 = pev->origin;
	}

	m_toggle_state = TS_AT_BOTTOM;

	// if the door is flagged for USE button activation only, use NULL touch function
	if (pev->spawnflags & SF_DOOR_USE_ONLY)
	{
		SetTouch(nullptr);
	}
	else
	{
		// touchable button
		SetTouch(&CBaseDoor::DoorTouch);
	}

	m_lastBlockedTimestamp = 0;
}

void CBaseDoor::Restart()
{
	SetMovedir(pev);
	m_toggle_state = TS_AT_BOTTOM;
	DoorGoDown();

	if (pev->spawnflags & SF_DOOR_USE_ONLY)
		SetTouch(nullptr);
	else
		SetTouch(&CBaseDoor::DoorTouch);
}

void CBaseDoor::SetToggleState(int state)
{
	if (state == TS_AT_TOP)
		UTIL_SetOrigin(pev, m_vecPosition2);
	else
		UTIL_SetOrigin(pev, m_vecPosition1);
}

#define noiseMoving noise1
#define noiseArrived noise2

void CBaseDoor::Precache()
{
	char *pszSound;

	// set the door's "in-motion" sound
	switch (m_bMoveSnd)
	{
	case 0:
		pev->noiseMoving = ALLOC_STRING("common/null.wav");
		break;
	case 1:
		PRECACHE_SOUND("doors/doormove1.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove1.wav");
		break;
	case 2:
		PRECACHE_SOUND("doors/doormove2.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove2.wav");
		break;
	case 3:
		PRECACHE_SOUND("doors/doormove3.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove3.wav");
		break;
	case 4:
		PRECACHE_SOUND("doors/doormove4.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove4.wav");
		break;
	case 5:
		PRECACHE_SOUND("doors/doormove5.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove5.wav");
		break;
	case 6:
		PRECACHE_SOUND("doors/doormove6.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove6.wav");
		break;
	case 7:
		PRECACHE_SOUND("doors/doormove7.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove7.wav");
		break;
	case 8:
		PRECACHE_SOUND("doors/doormove8.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove8.wav");
		break;
	case 9:
		PRECACHE_SOUND("doors/doormove9.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove9.wav");
		break;
	case 10:
		PRECACHE_SOUND("doors/doormove10.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove10.wav");
		break;
	default:
		pev->noiseMoving = ALLOC_STRING("common/null.wav");
		break;
	}

	// set the door's 'reached destination' stop sound
	switch (m_bStopSnd)
	{
	case 0:
		pev->noiseArrived = ALLOC_STRING("common/null.wav");
		break;
	case 1:
		PRECACHE_SOUND("doors/doorstop1.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop1.wav");
		break;
	case 2:
		PRECACHE_SOUND("doors/doorstop2.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop2.wav");
		break;
	case 3:
		PRECACHE_SOUND("doors/doorstop3.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop3.wav");
		break;
	case 4:
		PRECACHE_SOUND("doors/doorstop4.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop4.wav");
		break;
	case 5:
		PRECACHE_SOUND("doors/doorstop5.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop5.wav");
		break;
	case 6:
		PRECACHE_SOUND("doors/doorstop6.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop6.wav");
		break;
	case 7:
		PRECACHE_SOUND("doors/doorstop7.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop7.wav");
		break;
	case 8:
		PRECACHE_SOUND("doors/doorstop8.wav");
		pev->noiseArrived = ALLOC_STRING("doors/doorstop8.wav");
		break;
	default:
		pev->noiseArrived = ALLOC_STRING("common/null.wav");
		break;
	}

	// get door button sounds, for doors which are directly 'touched' to open
	if (m_bLockedSound)
	{
		pszSound = ButtonSound(int(m_bLockedSound));
		PRECACHE_SOUND(pszSound);
		m_ls.sLockedSound = ALLOC_STRING(pszSound);
	}

	if (m_bUnlockedSound)
	{
		pszSound = ButtonSound(int(m_bUnlockedSound));
		PRECACHE_SOUND(pszSound);
		m_ls.sUnlockedSound = ALLOC_STRING(pszSound);
	}

	// get sentence group names, for doors which are directly 'touched' to open
	switch (m_bLockedSentence)
	{
	case 1: m_ls.sLockedSentence = ALLOC_STRING("NA"); break;	// access denied
	case 2: m_ls.sLockedSentence = ALLOC_STRING("ND"); break;	// security lockout
	case 3: m_ls.sLockedSentence = ALLOC_STRING("NF"); break;	// blast door
	case 4: m_ls.sLockedSentence = ALLOC_STRING("NFIRE"); break;	// fire door
	case 5: m_ls.sLockedSentence = ALLOC_STRING("NCHEM"); break;	// chemical door
	case 6: m_ls.sLockedSentence = ALLOC_STRING("NRAD"); break;	// radiation door
	case 7: m_ls.sLockedSentence = ALLOC_STRING("NCON"); break;	// gen containment
	case 8: m_ls.sLockedSentence = ALLOC_STRING("NH"); break;	// maintenance door
	case 9: m_ls.sLockedSentence = ALLOC_STRING("NG"); break;	// broken door
	default: m_ls.sLockedSentence = 0; break;
	}

	switch (m_bUnlockedSentence)
	{
	case 1: m_ls.sUnlockedSentence = ALLOC_STRING("EA"); break;	// access granted
	case 2: m_ls.sUnlockedSentence = ALLOC_STRING("ED"); break;	// security door
	case 3: m_ls.sUnlockedSentence = ALLOC_STRING("EF"); break;	// blast door
	case 4: m_ls.sUnlockedSentence = ALLOC_STRING("EFIRE"); break;	// fire door
	case 5: m_ls.sUnlockedSentence = ALLOC_STRING("ECHEM"); break;	// chemical door
	case 6: m_ls.sUnlockedSentence = ALLOC_STRING("ERAD"); break;	// radiation door
	case 7: m_ls.sUnlockedSentence = ALLOC_STRING("ECON"); break;	// gen containment
	case 8: m_ls.sUnlockedSentence = ALLOC_STRING("EH"); break;	// maintenance door
	default: m_ls.sUnlockedSentence = 0; break;
	}
}

// Doors not tied to anything (e.g. button, another door) can be touched, to make them activate.
void CBaseDoor::DoorTouch(CBaseEntity *pOther)
{
	entvars_t *pevToucher = pOther->pev;

#ifdef REGAMEDLL_ADD
	if ((pev->spawnflags & SF_DOOR_TOUCH_ONLY_CLIENTS) && !pOther->IsPlayer())
		return;
#endif

	// Ignore touches by dead players
	if (pevToucher->deadflag != DEAD_NO)
		return;

	// If door has master, and it's not ready to trigger,
	// play 'locked' sound
	if (!FStringNull(m_sMaster) && !UTIL_IsMasterTriggered(m_sMaster, pOther))
	{
		PlayLockSounds(pev, &m_ls, TRUE, FALSE);
	}

	// If door is somebody's target, then touching does nothing.
	// You have to activate the owner (e.g. button).
	if (!FStringNull(pev->targetname))
	{
		// play locked sound
		PlayLockSounds(pev, &m_ls, TRUE, FALSE);
		return;
	}

	// remember who activated the door
	m_hActivator = pOther;

	if (DoorActivate())
	{
		// Temporarily disable the touch function, until movement is finished.
		SetTouch(nullptr);
	}
}

// Used by SUB_UseTargets, when a door is the target of a button.
void CBaseDoor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	m_hActivator = pActivator;

	// if not ready to be used, ignore "use" command.
	if (m_toggle_state == TS_AT_BOTTOM || ((pev->spawnflags & SF_DOOR_NO_AUTO_RETURN) && m_toggle_state == TS_AT_TOP))
	{
		DoorActivate();
	}
}

// Causes the door to "do its thing", i.e. start moving, and cascade activation.
int CBaseDoor::DoorActivate()
{
	if (!UTIL_IsMasterTriggered(m_sMaster, m_hActivator))
		return 0;

	// door should close
	if ((pev->spawnflags & SF_DOOR_NO_AUTO_RETURN) && m_toggle_state == TS_AT_TOP)
	{
		DoorGoDown();
	}
	else // door should open
	{
		// give health if player opened the door (medikit)
		if (m_hActivator && m_hActivator->IsPlayer())
		{
			// VARS(m_eoActivator)->health += m_bHealthValue;
			m_hActivator->TakeHealth(m_bHealthValue, DMG_GENERIC);

		}

		// play door unlock sounds
		PlayLockSounds(pev, &m_ls, FALSE, FALSE);
		DoorGoUp();
	}

	return 1;
}

// Starts the door going to its "up" position (simply ToggleData->vecPosition2).
void CBaseDoor::DoorGoUp()
{
	entvars_t *pevActivator;
	bool isReversing = (m_toggle_state == TS_GOING_DOWN);

	// It could be going-down, if blocked.
	assert(m_toggle_state == TS_AT_BOTTOM || m_toggle_state == TS_GOING_DOWN);

	// emit door moving and stop sounds on CHAN_STATIC so that the multicast doesn't
	// filter them out and leave a client stuck with looping door sounds!
	if (!isReversing)
	{
		// water is silent
		if (!(pev->spawnflags & SF_DOOR_ACTUALLY_WATER))
		{
			if (m_toggle_state != TS_GOING_UP && m_toggle_state != TS_GOING_DOWN)
			{
				EMIT_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseMoving), VOL_NORM, ATTN_NORM);
			}

			if (TheBots)
			{
#ifdef REGAMEDLL_FIXES
				if (m_hActivator && m_hActivator->IsPlayer())
#endif
				{
					TheBots->OnEvent(EVENT_DOOR, m_hActivator);
				}
			}
		}
	}

	m_toggle_state = TS_GOING_UP;

	SetMoveDone(&CBaseDoor::DoorHitTop);

	// BUGBUG: Triggered doors don't work with this yet
	if (FClassnameIs(pev, "func_door_rotating"))
	{
		float sign = 1.0f;

		if (m_hActivator)
		{
			pevActivator = m_hActivator->pev;

			// Y axis rotation, move away from the player
			if (!(pev->spawnflags & SF_DOOR_ROTATE_ONEWAY) && pev->movedir.y)
			{
				Vector2D toActivator = pevActivator->origin.Make2D();

				float loX = pev->mins.x + pev->origin.x;
				float loY = pev->mins.y + pev->origin.y;

				float hiX = pev->maxs.x + pev->origin.x;
				float hiY = pev->maxs.y + pev->origin.y;

				float momentArmX = toActivator.x - pev->origin.x;
				float momentArmY = toActivator.y - pev->origin.y;

				if (loX > toActivator.x)
				{
					if (toActivator.y < loY)
					{
#ifdef REGAMEDLL_FIXES
						if (Q_abs(momentArmY) > Q_abs(momentArmX))
#else
						if (Q_abs(int(momentArmY)) > Q_abs(int(momentArmX)))
#endif
							sign = (momentArmY < 0) ? 1 : -1;
						else
							sign = (momentArmX > 0) ? 1 : -1;
					}
					else if (toActivator.y > hiY)
					{
#ifdef REGAMEDLL_FIXES
						if (Q_abs(momentArmY) > Q_abs(momentArmX))
#else
						if (Q_abs(int(momentArmY)) > Q_abs(int(momentArmX)))
#endif
							sign = (momentArmY < 0) ? 1 : -1;
						else
							sign = (momentArmX < 0) ? 1 : -1;
					}
					else
						sign = (momentArmY < 0) ? 1 : -1;
				}
				else
				{
					if (toActivator.x <= hiX)
					{
						if (toActivator.y < loY)
							sign = (momentArmX > 0) ? 1 : -1;
						else if (toActivator.y > hiY)
							sign = (momentArmX < 0) ? 1 : -1;
					}
					else if (toActivator.y < loY)
					{
#ifdef REGAMEDLL_FIXES
						if (Q_abs(momentArmY) > Q_abs(momentArmX))
#else
						if (Q_abs(int(momentArmY)) > Q_abs(int(momentArmX)))
#endif
							sign = (momentArmY > 0) ? 1 : -1;
						else
							sign = (momentArmX > 0) ? 1 : -1;
					}
					else if (toActivator.y > hiY)
					{
#ifdef REGAMEDLL_FIXES
						if (Q_abs(momentArmY) > Q_abs(momentArmX))
#else
						if (Q_abs(int(momentArmY)) > Q_abs(int(momentArmX)))
#endif
							sign = (momentArmY > 0) ? 1 : -1;
						else
							sign = (momentArmX < 0) ? 1 : -1;
					}
					else
						sign = (momentArmY > 0) ? 1 : -1;
				}

				if (isReversing)
				{
					sign = -sign;
				}
			}
		}

		AngularMove(m_vecAngle2 * sign, pev->speed);
	}
	else
	{
		LinearMove(m_vecPosition2, pev->speed);
	}
}

// The door has reached the "up" position.  Either go back down, or wait for another activation.
void CBaseDoor::DoorHitTop()
{
	// water is silent
	if (!(pev->spawnflags & SF_DOOR_ACTUALLY_WATER))
	{
		STOP_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseMoving));
		EMIT_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseArrived), VOL_NORM, ATTN_NORM);
	}

	assert(m_toggle_state == TS_GOING_UP);
	m_toggle_state = TS_AT_TOP;

	// toggle-doors don't come down automatically, they wait for refire.
	if (pev->spawnflags & SF_DOOR_NO_AUTO_RETURN)
	{
		// Re-instate touch method, movement is complete
		if (!(pev->spawnflags & SF_DOOR_USE_ONLY))
		{
			SetTouch(&CBaseDoor::DoorTouch);
		}
	}
	else
	{
		// In flWait seconds, DoorGoDown will fire, unless wait is -1, then door stays open
		pev->nextthink = pev->ltime + m_flWait;
		SetThink(&CBaseDoor::DoorGoDown);

		if (m_flWait == -1)
		{
			pev->nextthink = -1;
		}
	}

	// Fire the close target (if startopen is set, then "top" is closed) - netname is the close target
	if (!FStringNull(pev->netname) && (pev->spawnflags & SF_DOOR_START_OPEN))
	{
		FireTargets(STRING(pev->netname), m_hActivator, this, USE_TOGGLE, 0);
	}

	// this isn't finished
	SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);
}

// Starts the door going to its "down" position (simply ToggleData->vecPosition1).
void CBaseDoor::DoorGoDown()
{
	bool isReversing = (m_toggle_state == TS_GOING_UP);

	if (!isReversing)
	{
		// water is silent
		if (!(pev->spawnflags & SF_DOOR_ACTUALLY_WATER))
		{
			if (m_toggle_state != TS_GOING_UP && m_toggle_state != TS_GOING_DOWN)
			{
				EMIT_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseMoving), VOL_NORM, ATTN_NORM);
			}

			if (TheBots)
			{
#ifdef REGAMEDLL_FIXES
				if (m_hActivator && m_hActivator->IsPlayer())
#endif
				{
					TheBots->OnEvent(EVENT_DOOR, m_hActivator);
				}
			}
		}
	}

#ifdef DOOR_ASSERT
	assert(m_toggle_state == TS_AT_TOP);
#endif

	m_toggle_state = TS_GOING_DOWN;

	SetMoveDone(&CBaseDoor::DoorHitBottom);

	//rotating door
	if (FClassnameIs(pev, "func_door_rotating"))
	{
		AngularMove(m_vecAngle1, pev->speed);
	}
	else
	{
		LinearMove(m_vecPosition1, pev->speed);
	}
}

// The door has reached the "down" position.  Back to quiescence.
void CBaseDoor::DoorHitBottom()
{
	// water is silent
	if (!(pev->spawnflags & SF_DOOR_ACTUALLY_WATER))
	{
		STOP_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseMoving));
		EMIT_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseArrived), VOL_NORM, ATTN_NORM);
	}

	assert(m_toggle_state == TS_GOING_DOWN);
	m_toggle_state = TS_AT_BOTTOM;

	// Re-instate touch method, cycle is complete
	if (pev->spawnflags & SF_DOOR_USE_ONLY)
	{
		// use only door
		SetTouch(nullptr);
	}
	else
	{
		// touchable door
		SetTouch(&CBaseDoor::DoorTouch);
	}

	// this isn't finished
	SUB_UseTargets(m_hActivator, USE_TOGGLE, 0);

	// Fire the close target (if startopen is set, then "top" is closed) - netname is the close target
	if (!FStringNull(pev->netname) && !(pev->spawnflags & SF_DOOR_START_OPEN))
	{
		FireTargets(STRING(pev->netname), m_hActivator, this, USE_TOGGLE, 0);
	}
}

void CBaseDoor::Blocked(CBaseEntity *pOther)
{
	edict_t *pentTarget = nullptr;
	CBaseDoor *pDoor = nullptr;
	const float checkBlockedInterval = 0.25f;

	// Hurt the blocker a little.
	if (pev->dmg != 0.0f)
	{
		pOther->TakeDamage(pev, pev, pev->dmg, DMG_CRUSH);
	}

	if (gpGlobals->time - m_lastBlockedTimestamp < checkBlockedInterval)
	{
		return;
	}

	m_lastBlockedTimestamp = gpGlobals->time;

	// if a door has a negative wait, it would never come back if blocked,
	// so let it just squash the object to death real fast
	if (m_flWait >= 0)
	{
		if (m_toggle_state == TS_GOING_DOWN)
		{
			DoorGoUp();
		}
		else
		{
			DoorGoDown();
		}
	}

	// Block all door pieces with the same targetname here.
	if (!FStringNull(pev->targetname))
	{
		while (true)
		{
			pentTarget = FIND_ENTITY_BY_TARGETNAME(pentTarget, STRING(pev->targetname));

			if (VARS(pentTarget) != pev)
			{
				if (FNullEnt(pentTarget))
					break;

				if (FClassnameIs(pentTarget, "func_door") || FClassnameIs(pentTarget, "func_door_rotating"))
				{
					pDoor = GetClassPtr<CCSDoor>((CBaseDoor *)VARS(pentTarget));

					if (pDoor->m_flWait >= 0)
					{
						if (pDoor->pev->velocity == pev->velocity && pDoor->pev->avelocity == pev->velocity)
						{
							// this is the most hacked, evil, bastardized thing I've ever seen. kjb
							if (FClassnameIs(pentTarget, "func_door"))
							{
								// set origin to realign normal doors
								pDoor->pev->origin = pev->origin;

								// stop!
								pDoor->pev->velocity = g_vecZero;
							}
							else
							{
								// set angles to realign rotating doors
								pDoor->pev->angles = pev->angles;
								pDoor->pev->avelocity = g_vecZero;
							}
						}

						if (!(pev->spawnflags & SF_DOOR_ACTUALLY_WATER))
						{
							STOP_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseMoving));
						}

						if (pDoor->m_toggle_state == TS_GOING_DOWN)
							pDoor->DoorGoUp();
						else
							pDoor->DoorGoDown();
					}
				}
			}
		}
	}
}

// QUAKED FuncRotDoorSpawn (0 .5 .8) ? START_OPEN REVERSE
// DOOR_DONT_LINK TOGGLE X_AXIS Y_AXIS
// if two doors touch, they are assumed to be connected and operate as a unit.

// TOGGLE causes the door to wait in both the start and end states for a trigger event.

// START_OPEN causes the door to move to its destination when spawned,
// and operate in reverse.  It is used to temporarily or permanently
// close off an area when triggered (not usefull for touch or
// takedamage doors).

// You need to have an origin brush as part of this entity.  The
// center of that brush will be
// the point around which it is rotated. It will rotate around the Z
// axis by default.  You can
// check either the X_AXIS or Y_AXIS box to change that.

// "distance" is how many degrees the door will be rotated.
// "speed" determines how fast the door moves; default value is 100.

// REVERSE will cause the door to rotate in the opposite direction.

// "angle"	determines the opening direction
// "targetname"	if set, no touch field will be spawned and a remote button or trigger field activates the door.
// "health"	if set, door must be shot open
// "speed"	movement speed (100 default)
// "wait"	wait before returning (3 default, -1 = never return)
// "dmg"	damage to inflict when blocked (2 default)
// "sounds"
// 0)	no sound
// 1)	stone
// 2)	base
// 3)	stone chain
// 4)	screechy metal
LINK_ENTITY_TO_CLASS(func_door_rotating, CRotDoor, CCSRotDoor)

void CRotDoor::Restart()
{
	CBaseToggle::AxisDir(pev);

	if (pev->spawnflags & SF_DOOR_ROTATE_BACKWARDS)
	{
		pev->movedir = pev->movedir * -1;
	}

	if (pev->speed == 0)
		pev->speed = 100;

	// DOOR_START_OPEN is to allow an entity to be lighted in the closed position
	// but spawn in the open position
	if (pev->spawnflags & SF_DOOR_START_OPEN)
	{
#ifdef REGAMEDLL_FIXES
		pev->angles = m_vecAngle1;
#else
		pev->angles = m_vecAngle2;

		Vector vecSav = m_vecAngle1;
		m_vecAngle2 = m_vecAngle1;
		m_vecAngle1 = vecSav;
#endif

		pev->movedir = pev->movedir * -1;
	}
#ifdef REGAMEDLL_FIXES
	else if (pev->netname.IsNull())
	{
		pev->angles = m_vecAngle1;
	}
#endif

	m_toggle_state = TS_AT_BOTTOM;
	DoorGoDown();
}

void CRotDoor::Spawn()
{
	Precache();

	// set the axis of rotation
	CBaseToggle::AxisDir(pev);

	// check for clockwise rotation
	if (pev->spawnflags & SF_DOOR_ROTATE_BACKWARDS)
	{
		pev->movedir = pev->movedir * -1;
	}

	//m_flWait = 2; who the hell did this? (sjb)
	m_vecAngle1 = pev->angles;
	m_vecAngle2 = pev->angles + pev->movedir * m_flMoveDistance;

	assert(("rotating door start/end positions are equal", m_vecAngle1 != m_vecAngle2));

	if (pev->spawnflags & SF_DOOR_PASSABLE)
		pev->solid = SOLID_NOT;
	else
		pev->solid = SOLID_BSP;

	pev->movetype = MOVETYPE_PUSH;

	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->speed == 0)
		pev->speed = 100;

	// DOOR_START_OPEN is to allow an entity to be lighted in the closed position
	// but spawn in the open position
	if (pev->spawnflags & SF_DOOR_START_OPEN)
	{
		// swap pos1 and pos2, put door at pos2, invert movement direction
		pev->angles = m_vecAngle2;

#ifdef REGAMEDLL_FIXES
		SWAP(m_vecAngle1, m_vecAngle2);
#else
		Vector vecSav = m_vecAngle1;
		m_vecAngle2 = m_vecAngle1;
		m_vecAngle1 = vecSav;
#endif

		pev->movedir = pev->movedir * -1;
	}

	m_toggle_state = TS_AT_BOTTOM;

	if (pev->spawnflags & SF_DOOR_USE_ONLY)
	{
		SetTouch(nullptr);
	}
	else
	{
		// touchable button
		SetTouch(&CRotDoor::DoorTouch);
	}
}

void CRotDoor::SetToggleState(int state)
{
	if (state == TS_AT_TOP)
		pev->angles = m_vecAngle2;
	else
		pev->angles = m_vecAngle1;

	UTIL_SetOrigin(pev, pev->origin);
}

TYPEDESCRIPTION CMomentaryDoor::m_SaveData[] =
{
	DEFINE_FIELD(CMomentaryDoor, m_bMoveSnd, FIELD_CHARACTER),
};

LINK_ENTITY_TO_CLASS(momentary_door, CMomentaryDoor, CCSMomentaryDoor)
IMPLEMENT_SAVERESTORE(CMomentaryDoor, CBaseToggle)

void CMomentaryDoor::Spawn()
{
	SetMovedir(pev);

	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;

	UTIL_SetOrigin(pev, pev->origin);
	SET_MODEL(ENT(pev), STRING(pev->model));

	if (pev->speed == 0)
		pev->speed = 100;

	if (pev->dmg == 0)
		pev->dmg = 2;

	m_vecPosition1 = pev->origin;

	// Subtract 2 from size because the engine expands bboxes by 1 in all directions making the size too big
	m_vecPosition2 = m_vecPosition1 + (pev->movedir * (Q_fabs(real_t(pev->movedir.x * (pev->size.x - 2))) + Q_fabs(real_t(pev->movedir.y * (pev->size.y - 2))) + Q_fabs(real_t(pev->movedir.z * (pev->size.z - 2))) - m_flLip));
	assert(("door start/end positions are equal", m_vecPosition1 != m_vecPosition2));

	if (pev->spawnflags & SF_DOOR_START_OPEN)
	{
		// swap pos1 and pos2, put door at pos2
		UTIL_SetOrigin(pev, m_vecPosition2);

		m_vecPosition2 = m_vecPosition1;
		m_vecPosition1 = pev->origin;
	}

	SetTouch(nullptr);
	Precache();
}

void CMomentaryDoor::Precache()
{
	// set the door's "in-motion" sound
	switch (m_bMoveSnd)
	{
	case 0:
		pev->noiseMoving = ALLOC_STRING("common/null.wav");
		break;
	case 1:
		PRECACHE_SOUND("doors/doormove1.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove1.wav");
		break;
	case 2:
		PRECACHE_SOUND("doors/doormove2.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove2.wav");
		break;
	case 3:
		PRECACHE_SOUND("doors/doormove3.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove3.wav");
		break;
	case 4:
		PRECACHE_SOUND("doors/doormove4.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove4.wav");
		break;
	case 5:
		PRECACHE_SOUND("doors/doormove5.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove5.wav");
		break;
	case 6:
		PRECACHE_SOUND("doors/doormove6.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove6.wav");
		break;
	case 7:
		PRECACHE_SOUND("doors/doormove7.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove7.wav");
		break;
	case 8:
		PRECACHE_SOUND("doors/doormove8.wav");
		pev->noiseMoving = ALLOC_STRING("doors/doormove8.wav");
		break;
	default:
		pev->noiseMoving = ALLOC_STRING("common/null.wav");
		break;
	}
}

void CMomentaryDoor::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "movesnd"))
	{
		m_bMoveSnd = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "stopsnd"))
	{
		//m_bStopSnd = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "healthvalue"))
	{
		//m_bHealthValue = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseToggle::KeyValue(pkvd);
}

void CMomentaryDoor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// Momentary buttons will pass down a float in here
	if (useType != USE_SET)
	{
		return;
	}

	if (value > 1.0f)
		value = 1.0f;

	Vector move = m_vecPosition1 + (value * (m_vecPosition2 - m_vecPosition1));
	Vector delta = move - pev->origin;

	//float speed = delta.Length() * 10;

	// move there in 0.1 sec
	float speed = delta.Length() / 0.1f;

	if (speed == 0)
		return;

	// This entity only thinks when it moves, so if it's thinking, it's in the process of moving
	// play the sound when it starts moving (not yet thinking)
	if (pev->nextthink < pev->ltime || pev->nextthink == 0)
	{
		EMIT_SOUND(ENT(pev), CHAN_STATIC, (char *)STRING(pev->noiseMoving), VOL_NORM, ATTN_NORM);
	}
#if 0
	// If we already moving to designated point, return
	else if (move == m_vecFinalDest)
	{
		return;
	}

	SetMoveDone(&CMomentaryDoor::DoorMoveDone);
#endif

	LinearMove(move, speed);
}
