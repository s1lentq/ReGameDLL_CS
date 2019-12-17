#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_c4, CC4, CCSC4)

void CC4::Spawn()
{
	SET_MODEL(edict(), "models/w_backpack.mdl");

	pev->frame = 0;
	pev->body = 3;
	pev->sequence = 0;
	pev->framerate = 0;

	m_iId = WEAPON_C4;
	m_iDefaultAmmo = C4_DEFAULT_GIVE;
	m_bStartedArming = false;
	m_fArmedTime = 0;

	if (!FStringNull(pev->targetname))
	{
		pev->effects |= EF_NODRAW;
		DROP_TO_FLOOR(edict());
		return;
	}

	// Get ready to fall down
	FallInit();
	SetThink(&CBasePlayerItem::FallThink);
	pev->nextthink = UTIL_WeaponTimeBase() + 0.1f;

	// extend
	CBasePlayerWeapon::Spawn();
}

void CC4::Precache()
{
	PRECACHE_MODEL("models/v_c4.mdl");
	PRECACHE_MODEL("models/w_backpack.mdl");

	PRECACHE_SOUND("weapons/c4_click.wav");
}

int CC4::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "C4";
	p->iMaxAmmo1 = MAX_AMMO_C4;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 4;
	p->iPosition = 3;
	p->iId = m_iId = WEAPON_C4;
	p->iWeight = C4_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return 1;
}

BOOL CC4::Deploy()
{
	pev->body = 0;

	m_bStartedArming = false;
	m_fArmedTime = 0;

	if (m_pPlayer->HasShield())
	{
		m_bHasShield = true;
		m_pPlayer->pev->gamestate = HITGROUP_SHIELD_DISABLED;
	}

	return DefaultDeploy("models/v_c4.mdl", "models/p_c4.mdl", C4_DRAW, "c4", UseDecrement() != FALSE);
}

void CC4::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5f;

#ifdef REGAMEDLL_FIXES
	if(m_bStartedArming)
	{
		m_pPlayer->SetProgressBarTime(0);
	}
#endif

	m_bStartedArming = false;	// stop arming sequence

	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
#ifndef REGAMEDLL_FIXES
		// Moved to DestroyItem()
		m_pPlayer->pev->weapons &= ~(1 << WEAPON_C4);
#endif

		DestroyItem();
	}

	if (m_bHasShield)
	{
		m_pPlayer->pev->gamestate = HITGROUP_SHIELD_ENABLED;
		m_bHasShield = false;
	}
}

void CC4::PrimaryAttack()
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return;

	int inBombZone = (m_pPlayer->m_signals.GetState() & SIGNAL_BOMB) == SIGNAL_BOMB;
	int onGround = (m_pPlayer->pev->flags & FL_ONGROUND) == FL_ONGROUND;

#ifdef REGAMEDLL_FIXES
	if (!onGround)
	{
		TraceResult tr;
		UTIL_TraceLine(m_pPlayer->pev->origin, m_pPlayer->pev->origin + Vector(0, 0, -8192), ignore_monsters, m_pPlayer->edict(), &tr);
		onGround = (tr.flFraction != 1.0 && m_pPlayer->pev->velocity.z == 0.0f);
	}
#endif

	bool bPlaceBomb = (onGround && inBombZone);

	if (!m_bStartedArming)
	{
		if (!inBombZone)
		{
			ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Plant_At_Bomb_Spot");
			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
			return;
		}

		if (!onGround)
		{
			ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Plant_Must_Be_On_Ground");
			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
			return;
		}

		m_bStartedArming = true;
		m_bBombPlacedAnimation = false;
		m_fArmedTime = gpGlobals->time + C4_ARMING_ON_TIME;

		// player "arming bomb" animation
		SendWeaponAnim(C4_ARM, UseDecrement() != FALSE);

		// freeze the player in place while planting
#ifdef REGAMEDLL_FIXES
		m_pPlayer->ResetMaxSpeed();
#else
		SET_CLIENT_MAXSPEED(m_pPlayer->edict(), 1.0);
#endif

		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		m_pPlayer->SetProgressBarTime(C4_ARMING_ON_TIME);
	}
	else
	{
		if (bPlaceBomb)
		{
			CBaseEntity *pEntity = nullptr;
			CBasePlayer *pTempPlayer = nullptr;

			if (m_fArmedTime <= gpGlobals->time)
			{
				m_bStartedArming = false;
				m_fArmedTime = 0;

				Broadcast("BOMBPL");
				m_pPlayer->m_bHasC4 = false;

				if (pev->speed != 0 && CSGameRules())
				{
					CSGameRules()->m_iC4Timer = int(pev->speed);
				}

#ifdef REGAMEDLL_FIXES
				Vector vBombAngles = Vector(0, m_pPlayer->pev->angles[1] - 90.0, 0);
#else
				Vector vBombAngles = Vector(0, 0, 0);
#endif
				CGrenade *pBomb = CGrenade::ShootSatchelCharge(m_pPlayer->pev, m_pPlayer->pev->origin, vBombAngles);

				MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
					WRITE_BYTE(9);
					WRITE_BYTE(DRC_CMD_EVENT);
					WRITE_SHORT(m_pPlayer->entindex());
					WRITE_SHORT(0);
					WRITE_LONG(DRC_FLAG_FACEPLAYER | 11);
				MESSAGE_END();

				MESSAGE_BEGIN(MSG_ALL, gmsgBombDrop);
					WRITE_COORD(pBomb->pev->origin.x);
					WRITE_COORD(pBomb->pev->origin.y);
					WRITE_COORD(pBomb->pev->origin.z);
					WRITE_BYTE(BOMB_FLAG_PLANTED);
				MESSAGE_END();

				UTIL_ClientPrintAll(HUD_PRINTCENTER, "#Bomb_Planted");
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_BOMB_PLANTED, m_pPlayer, pBomb);
				}

				if (TheCareerTasks && CSGameRules()->IsCareer() && !m_pPlayer->IsBot())
				{
					TheCareerTasks->HandleEvent(EVENT_BOMB_PLANTED, m_pPlayer);
				}

				UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Planted_The_Bomb\"\n",
					STRING(m_pPlayer->pev->netname),
					GETPLAYERUSERID(m_pPlayer->edict()),
					GETPLAYERAUTHID(m_pPlayer->edict()));

				g_pGameRules->m_bBombDropped = FALSE;

				// Play the plant sound.
				EMIT_SOUND(edict(), CHAN_WEAPON, "weapons/c4_plant.wav", VOL_NORM, ATTN_NORM);

				// hide the backpack in Terrorist's models.
				m_pPlayer->pev->body = 0;

				// release the player from being frozen
				m_pPlayer->ResetMaxSpeed();

				// No more c4!
				m_pPlayer->SetBombIcon(FALSE);

				if (--m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
				{
					RetireWeapon();
					return;
				}
			}
			else
			{
				if (m_fArmedTime - 0.75f <= gpGlobals->time && !m_bBombPlacedAnimation)
				{
					// call the c4 Placement animation
					m_bBombPlacedAnimation = true;
					SendWeaponAnim(C4_DROP, UseDecrement() != FALSE);

					// player "place" animation
					m_pPlayer->SetAnimation(PLAYER_HOLDBOMB);
				}
			}
		}
		else
		{
			if (inBombZone)
				ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Plant_Must_Be_On_Ground");
			else
				ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Arming_Cancelled");

			m_bStartedArming = false;
			m_flNextPrimaryAttack = GetNextAttackDelay(1.5);

			// release the player from being frozen, we've somehow left the bomb zone
			m_pPlayer->ResetMaxSpeed();
			m_pPlayer->SetProgressBarTime(0);
			m_pPlayer->SetAnimation(PLAYER_HOLDBOMB);

			// this means the placement animation is canceled
			if (m_bBombPlacedAnimation)
				SendWeaponAnim(C4_DRAW, UseDecrement() != FALSE);
			else
				SendWeaponAnim(C4_IDLE1, UseDecrement() != FALSE);

			return;
		}
	}

	m_flNextPrimaryAttack = GetNextAttackDelay(0.3);
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
}

void CC4::WeaponIdle()
{
	if (m_bStartedArming)
	{
		// if the player releases the attack button cancel the arming sequence
		m_bStartedArming = false;

		// release the player from being frozen
		m_pPlayer->ResetMaxSpeed();

		m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
		m_pPlayer->SetProgressBarTime(0);

		// this means the placement animation is canceled
		if (m_bBombPlacedAnimation)
			SendWeaponAnim(C4_DRAW, UseDecrement() != FALSE);
		else
			SendWeaponAnim(C4_IDLE1, UseDecrement() != FALSE);
	}

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
		if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		{
			RetireWeapon();
			return;
		}

		SendWeaponAnim(C4_DRAW, UseDecrement() != FALSE);
		SendWeaponAnim(C4_IDLE1, UseDecrement() != FALSE);
	}
}

void CC4::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "detonatedelay"))
	{
		pev->speed = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "detonatetarget"))
	{
		pev->noise1 = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "defusetarget"))
	{
		pev->target = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

void CC4::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
#ifndef REGAMEDLL_FIXES
	if (m_pPlayer)
		return;

	CBasePlayer *pPlayer = UTIL_PlayerByIndex(1);
	if (pPlayer)
	{
		edict_t *m_pentOldCurBombTarget = pPlayer->m_pentCurBombTarget;
		pPlayer->m_pentCurBombTarget = nullptr;

		if (pev->speed != 0 && CSGameRules())
		{
			CSGameRules()->m_iC4Timer = int(pev->speed);
		}

		EMIT_SOUND(edict(), CHAN_WEAPON, "weapons/c4_plant.wav", VOL_NORM, ATTN_NORM);

		CGrenade::ShootSatchelCharge(pPlayer->pev, pev->origin, Vector(0, 0, 0));

		CGrenade *pBomb = nullptr;
		while ((pBomb = UTIL_FindEntityByClassname(pBomb, "grenade")))
		{
			if (pBomb->m_bIsC4 && pBomb->m_flNextFreq == gpGlobals->time)
			{
				pBomb->pev->target = pev->target;
				pBomb->pev->noise1 = pev->noise1;
				break;
			}
		}

		pPlayer->m_pentCurBombTarget = m_pentOldCurBombTarget;
		SUB_Remove();
	}
#endif
}

float CC4::GetMaxSpeed()
{
#ifdef REGAMEDLL_FIXES
	if (m_bStartedArming)
		return 1.0f;
#endif

	return C4_MAX_SPEED;
}
