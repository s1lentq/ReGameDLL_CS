#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_knife, CKnife, CCSKnife)

void CKnife::Spawn()
{
	Precache();

	m_iId = WEAPON_KNIFE;
	SET_MODEL(edict(), "models/w_knife.mdl");

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_iClip = WEAPON_NOCLIP;

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CKnife::Precache()
{
	PRECACHE_MODEL("models/v_knife.mdl");
	PRECACHE_MODEL("models/shield/v_shield_knife.mdl");
	PRECACHE_MODEL("models/w_knife.mdl");

	PRECACHE_SOUND("weapons/knife_deploy1.wav");
	PRECACHE_SOUND("weapons/knife_hit1.wav");
	PRECACHE_SOUND("weapons/knife_hit2.wav");
	PRECACHE_SOUND("weapons/knife_hit3.wav");
	PRECACHE_SOUND("weapons/knife_hit4.wav");
	PRECACHE_SOUND("weapons/knife_slash1.wav");
	PRECACHE_SOUND("weapons/knife_slash2.wav");
	PRECACHE_SOUND("weapons/knife_stab.wav");
	PRECACHE_SOUND("weapons/knife_hitwall1.wav");

	m_usKnife = PRECACHE_EVENT(1, "events/knife.sc");
}

int CKnife::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = nullptr;
	p->iMaxAmmo1 = -1;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 2;
	p->iPosition = 1;
	p->iId = WEAPON_KNIFE;
	p->iFlags = 0;
	p->iWeight = KNIFE_WEIGHT;

	return 1;
}

BOOL CKnife::Deploy()
{
	EMIT_SOUND(m_pPlayer->edict(), CHAN_ITEM, "weapons/knife_deploy1.wav", 0.3, 2.4);

	m_iSwing = 0;
	m_fMaxSpeed = KNIFE_MAX_SPEED;

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
	{
		return DefaultDeploy("models/shield/v_shield_knife.mdl", "models/shield/p_shield_knife.mdl", KNIFE_SHIELD_DRAW, "shieldknife", UseDecrement() != FALSE);
	}
	else
		return DefaultDeploy("models/v_knife.mdl", "models/p_knife.mdl", KNIFE_DRAW, "knife", UseDecrement() != FALSE);
}

void CKnife::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5f;
}

NOXREF void CKnife::WeaponAnimation(int iAnimation)
{
	int flag;

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usKnife,
		0.0, (float *)&g_vecZero, (float *)&g_vecZero,
		0.0,
		0.0,
		iAnimation, 2, 3, 4);
}

void FindHullIntersection(const Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity)
{
	int i, j, k;
	float distance;
	float *minmaxs[2] = { mins, maxs };
	TraceResult tmpTrace;
	Vector vecHullEnd = tr.vecEndPos;
	Vector vecEnd;

	distance = 1e6f;

	vecHullEnd = vecSrc + ((vecHullEnd - vecSrc) * 2);
	UTIL_TraceLine(vecSrc, vecHullEnd, dont_ignore_monsters, pEntity, &tmpTrace);

	if (tmpTrace.flFraction < 1.0f)
	{
		tr = tmpTrace;
		return;
	}

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 2; k++)
			{
				vecEnd.x = vecHullEnd.x + minmaxs[i][0];
				vecEnd.y = vecHullEnd.y + minmaxs[j][1];
				vecEnd.z = vecHullEnd.z + minmaxs[k][2];

				UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, pEntity, &tmpTrace);

				if (tmpTrace.flFraction < 1.0f)
				{
					real_t thisDistance = (tmpTrace.vecEndPos - vecSrc).Length();

					if (thisDistance < distance)
					{
						tr = tmpTrace;
						distance = thisDistance;
					}
				}
			}
		}
	}
}

void CKnife::PrimaryAttack()
{
	Swing(TRUE);
}

void CKnife::SetPlayerShieldAnim()
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shield");
	}
	else
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldknife");
	}
}

void CKnife::ResetPlayerShieldAnim()
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldknife");
	}
}

bool CKnife::ShieldSecondaryFire(int iUpAnim, int iDownAnim)
{
	if (!m_pPlayer->HasShield())
	{
		return false;
	}

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

		SendWeaponAnim(iDownAnim, UseDecrement() != FALSE);

		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldknife");

		m_fMaxSpeed = KNIFE_MAX_SPEED;
		m_pPlayer->m_bShieldDrawn = false;
	}
	else
	{
		m_iWeaponState |= WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iUpAnim, UseDecrement() != FALSE);

		Q_strcpy(m_pPlayer->m_szAnimExtention, "shielded");

		m_fMaxSpeed = KNIFE_MAX_SPEED_SHIELD;
		m_pPlayer->m_bShieldDrawn = true;
	}

	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) != WPNSTATE_SHIELD_DRAWN);
	m_pPlayer->ResetMaxSpeed();

	m_flNextPrimaryAttack = GetNextAttackDelay(0.4);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.4f;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.6f;

	return true;
}

void CKnife::SecondaryAttack()
{
	if (!ShieldSecondaryFire(KNIFE_SHIELD_UP, KNIFE_SHIELD_DOWN))
	{
		Stab(TRUE);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.35f;
	}
}

void CKnife::Smack()
{
	DecalGunshot(&m_trHit, BULLET_PLAYER_CROWBAR, false, m_pPlayer->pev, false);
}

void CKnife::SwingAgain()
{
	Swing(FALSE);
}

void CKnife::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_pPlayer->m_bShieldDrawn)
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;

	// only idle if the slid isn't back
	SendWeaponAnim(KNIFE_IDLE, UseDecrement() != FALSE);
}

BOOL CKnife::Swing(BOOL fFirst)
{
	BOOL fDidHit = FALSE;
	TraceResult tr;
	Vector vecSrc, vecEnd;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecEnd = vecSrc + gpGlobals->v_forward * 48.0f;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, m_pPlayer->edict(), &tr);

	if (tr.flFraction >= 1.0f)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, m_pPlayer->edict(), &tr);

		if (tr.flFraction < 1.0f)
		{
			// Calculate the point of intersection of the line (or hull) and the object we hit
			// This is and approximation of the "best" intersection
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);

			if (!pHit || pHit->IsBSPModel())
			{
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			}

			// This is the point on the actual surface (the hull could have hit space)
			vecEnd = tr.vecEndPos;
		}
	}

	if (tr.flFraction >= 1.0f)
	{
		if (fFirst)
		{
			if (!m_pPlayer->HasShield())
			{
				switch ((m_iSwing++) % 2)
				{
				case 0: SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE); break;
				case 1: SendWeaponAnim(KNIFE_MIDATTACK2HIT, UseDecrement() != FALSE); break;
				}

				// miss
				m_flNextPrimaryAttack = GetNextAttackDelay(0.35);
				m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5f;
			}
			else
			{
				SendWeaponAnim(KNIFE_SHIELD_ATTACKHIT, UseDecrement() != FALSE);

				m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
				m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.2f;
			}

			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

			// play wiff or swish sound
			if (RANDOM_LONG(0, 1))
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash1.wav", VOL_NORM, ATTN_NORM, 0, 94);
			else
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash2.wav", VOL_NORM, ATTN_NORM, 0, 94);

			// player "shoot" animation
			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		}
	}
	else
	{
		// hit
		fDidHit = TRUE;

		if (!m_pPlayer->HasShield())
		{
			switch ((m_iSwing++) % 2)
			{
			case 0: SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE); break;
			case 1: SendWeaponAnim(KNIFE_MIDATTACK2HIT, UseDecrement() != FALSE); break;
			}

			m_flNextPrimaryAttack = GetNextAttackDelay(0.4);
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5f;
		}
		else
		{
			SendWeaponAnim(KNIFE_SHIELD_ATTACKHIT, UseDecrement() != FALSE);

			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.2f;
		}

		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

		// play thwack, smack, or dong sound
		float flVol = 1.0f;
		int fHitWorld = TRUE;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
		SetPlayerShieldAnim();

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		ClearMultiDamage();

		if (m_flNextPrimaryAttack + 0.4f < UTIL_WeaponTimeBase())
			pEntity->TraceAttack(m_pPlayer->pev, 20, gpGlobals->v_forward, &tr, (DMG_NEVERGIB | DMG_BULLET));
		else
			pEntity->TraceAttack(m_pPlayer->pev, 15, gpGlobals->v_forward, &tr, (DMG_NEVERGIB | DMG_BULLET));

		ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

#ifndef REGAMEDLL_FIXES
		if (pEntity)	// -V595
#endif
		{
			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				// play thwack or smack sound
				switch (RANDOM_LONG(0, 3))
				{
				case 0: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit1.wav", VOL_NORM, ATTN_NORM); break;
				case 1: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit2.wav", VOL_NORM, ATTN_NORM); break;
				case 2: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit3.wav", VOL_NORM, ATTN_NORM); break;
				case 3: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit4.wav", VOL_NORM, ATTN_NORM); break;
				}

				m_pPlayer->m_iWeaponVolume = KNIFE_BODYHIT_VOLUME;

				if (!pEntity->IsAlive())
					return TRUE;
				else
					flVol = 0.1f;

				fHitWorld = FALSE;
			}
		}

		// play texture hit sound
		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line

		if (fHitWorld)
		{
			float fvolbar = TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);
			//fvolbar = 1.0;

			if (RANDOM_LONG(0, 1) > 1)
			{
				fHitWorld = FALSE;
			}
		}

		if (!fHitWorld)
		{
			// delay the decal a bit
			m_trHit = tr;
			SetThink(&CKnife::Smack);

			pev->nextthink = UTIL_WeaponTimeBase() + 0.2f;
			m_pPlayer->m_iWeaponVolume = int(flVol * KNIFE_WALLHIT_VOLUME);

			ResetPlayerShieldAnim();
		}
		else
		{
			// also play knife strike
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, RANDOM_LONG(0, 3) + 98);
		}
	}

	return fDidHit;
}

BOOL CKnife::Stab(BOOL fFirst)
{
	BOOL fDidHit = FALSE;
	TraceResult tr;
	Vector vecSrc, vecEnd;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecEnd = vecSrc + gpGlobals->v_forward * 32.0f;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, m_pPlayer->edict(), &tr);

	if (tr.flFraction >= 1.0f)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, m_pPlayer->edict(), &tr);

		if (tr.flFraction < 1.0f)
		{
			// Calculate the point of intersection of the line (or hull) and the object we hit
			// This is and approximation of the "best" intersection
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);

			if (!pHit || pHit->IsBSPModel())
			{
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			}

			// This is the point on the actual surface (the hull could have hit space)
			vecEnd = tr.vecEndPos;
		}
	}

	if (tr.flFraction >= 1.0f)
	{
		if (fFirst)
		{
			SendWeaponAnim(KNIFE_STABMISS, UseDecrement() != FALSE);
#ifdef REGAMEDLL_FIXES
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;
#endif

			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0f;

			// play wiff or swish sound
			if (RANDOM_LONG(0, 1))
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash1.wav", VOL_NORM, ATTN_NORM, 0, 94);
			else
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash2.wav", VOL_NORM, ATTN_NORM, 0, 94);

			// player "shoot" animation
			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		}
	}
	else
	{
		// hit
		fDidHit = TRUE;

		SendWeaponAnim(KNIFE_STABHIT, UseDecrement() != FALSE);
#ifdef REGAMEDLL_FIXES
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;
#endif

		m_flNextPrimaryAttack = GetNextAttackDelay(1.1);
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.1f;

		// play thwack, smack, or dong sound
		float flVol = 1.0f;
		int fHitWorld = TRUE;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

		float flDamage = 65.0f;

		if (pEntity && pEntity->IsPlayer())
		{
			Vector2D vec2LOS;
			float flDot;
			Vector vMyForward = gpGlobals->v_forward;

			UTIL_MakeVectors(pEntity->pev->angles);

			vec2LOS = vMyForward.Make2D();
			vec2LOS = vec2LOS.Normalize();

			flDot = DotProduct(vec2LOS, gpGlobals->v_forward.Make2D());

			//Triple the damage if we are stabbing them in the back.
			if (flDot > 0.80f)
			{
				flDamage *= 3.0f;
			}
		}

		UTIL_MakeVectors(m_pPlayer->pev->v_angle);
		ClearMultiDamage();

		pEntity->TraceAttack(m_pPlayer->pev, flDamage, gpGlobals->v_forward, &tr, (DMG_NEVERGIB | DMG_BULLET));
		ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

#ifndef REGAMEDLL_FIXES
		if (pEntity)	// -V595
#endif
		{
			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_stab.wav", VOL_NORM, ATTN_NORM);
				m_pPlayer->m_iWeaponVolume = KNIFE_BODYHIT_VOLUME;

				if (!pEntity->IsAlive())
					return TRUE;
				else
					flVol = 0.1f;

				fHitWorld = FALSE;
			}
		}

		// play texture hit sound
		// UNDONE: Calculate the correct point of intersection when we hit with the hull instead of the line

		if (fHitWorld)
		{
			float fvolbar = TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);
			//fvolbar = 1.0;

			if (RANDOM_LONG(0, 1) > 1)
			{
				fHitWorld = FALSE;
			}
		}

		if (!fHitWorld)
		{
			// delay the decal a bit
			m_trHit = tr;
			m_pPlayer->m_iWeaponVolume = int(flVol * KNIFE_WALLHIT_VOLUME);

			SetThink(&CKnife::Smack);
			pev->nextthink = UTIL_WeaponTimeBase() + 0.2f;

			ResetPlayerShieldAnim();
		}
		else
		{
			// also play knife strike
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, RANDOM_LONG(0, 3) + 98);
		}
	}

	return fDidHit;
}
