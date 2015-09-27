#include "precompiled.h"

#define KNIFE_BODYHIT_VOLUME		128
#define KNIFE_WALLHIT_VOLUME		512
#define KNIFE_MAX_SPEED			250
#define KNIFE_MAX_SPEED_SHIELD		180

enum knife_e
{
	KNIFE_IDLE,
	KNIFE_ATTACK1HIT,
	KNIFE_ATTACK2HIT,
	KNIFE_DRAW,
	KNIFE_STABHIT,
	KNIFE_STABMISS,
	KNIFE_MIDATTACK1HIT,
	KNIFE_MIDATTACK2HIT
};

enum knife_shield_e
{
	KNIFE_SHIELD_IDLE,
	KNIFE_SHIELD_SLASH,
	KNIFE_SHIELD_ATTACKHIT,
	KNIFE_SHIELD_DRAW,
	KNIFE_SHIELD_UPIDLE,
	KNIFE_SHIELD_UP,
	KNIFE_SHIELD_DOWN
};

/* <270ca6> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:28 */
LINK_ENTITY_TO_CLASS(weapon_knife, CKnife);

/* <270586> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:53 */
void CKnife::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_KNIFE;
	SET_MODEL(edict(), "models/w_knife.mdl");

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_iClip = WEAPON_NOCLIP;

	FallInit();	
}

/* <2704d2> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:66 */
void CKnife::__MAKE_VHOOK(Precache)(void)
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

/* <2704f9> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:85 */
int CKnife::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = NULL;
	p->iMaxAmmo1 = -1;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 2;
	p->iPosition = 1;
	p->iId = WEAPON_KNIFE;
	//p->iFlags = 0;
	p->iWeight = KNIFE_WEIGHT;

	return 1;
}

/* <2707c0> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:102 */
BOOL CKnife::__MAKE_VHOOK(Deploy)(void)
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

/* <27052b> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:119 */
void CKnife::__MAKE_VHOOK(Holster)(int skiplocal)
{
	m_pPlayer->m_flNextAttack = WEAPON_TIMEBASED + 0.5;
}

/* <270d70> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:124 */
NOXREF void CKnife::WeaponAnimation(int iAnimation)
{
	int flag;

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL
	(
		flag,
		m_pPlayer->edict(),
		m_usKnife,
		0,
		(float *)&g_vecZero,
		(float*)&g_vecZero,
		0,
		0,
		iAnimation,
		2,		// param noxref
		3,		// param noxref
		4		// param noxref
	);
}

/* <26f852> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:140 */
void FindHullIntersection(Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity)
{
	int i, j, k;
	float distance = 1000000.0;
	float *minmaxs[2] = { mins, maxs };
	TraceResult tmpTrace;
	Vector vecHullEnd, vecEnd;

	vecHullEnd = ((tr.vecEndPos - vecSrc)  * 2) + vecSrc;
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
					float_precision thisDistance = (tmpTrace.vecEndPos - vecSrc).Length();

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

/* <2714ba> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:185 */
void CKnife::__MAKE_VHOOK(PrimaryAttack)(void)
{
	Swing(TRUE);
}

/* <270f18> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:190 */
void CKnife::SetPlayerShieldAnim(void)
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

/* <270f53> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:201 */
void CKnife::ResetPlayerShieldAnim(void)
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldknife");
	}
}

/* <270f75> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:211 */
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

	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) == 0);
	m_pPlayer->ResetMaxSpeed();

	m_flNextPrimaryAttack = GetNextAttackDelay(0.4);
	m_flNextSecondaryAttack = WEAPON_TIMEBASED + 0.4;
	m_flTimeWeaponIdle = WEAPON_TIMEBASED + 0.6;
	
	return true;
}

/* <270826> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:245 */
void CKnife::__MAKE_VHOOK(SecondaryAttack)(void)
{
	if (!ShieldSecondaryFire(KNIFE_SHIELD_UP, KNIFE_SHIELD_DOWN))
	{
		Stab(TRUE);
		pev->nextthink = WEAPON_TIMEBASED + 0.35;
	}
}

/* <27055f> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:254 */
void CKnife::Smack(void)
{
	DecalGunshot(&m_trHit, BULLET_PLAYER_CROWBAR, false, m_pPlayer->pev, false);
}

/* <271493> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:260 */
void CKnife::SwingAgain(void)
{
	Swing(FALSE);
}

/* <2705fc> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:265 */
void CKnife::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > WEAPON_TIMEBASED)
	{
		return;
	}

	if (!m_pPlayer->m_bShieldDrawn)
	{
		m_flTimeWeaponIdle = WEAPON_TIMEBASED + 20.0;
		SendWeaponAnim(KNIFE_IDLE, UseDecrement() != FALSE);
	}
}

/* <270fa7> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:283 */
int CKnife::Swing(int fFirst)
{
	int fDidHit = FALSE;
	TraceResult tr;
	Vector vecSrc, vecEnd;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecEnd = vecSrc + gpGlobals->v_forward * 48;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, m_pPlayer->edict(), &tr);

	if (tr.flFraction >= 1.0f)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, m_pPlayer->edict(), &tr);

		if (tr.flFraction < 1.0f)
		{
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);

			if (!pHit || pHit->IsBSPModel())
			{
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			}

			vecEnd = tr.vecEndPos;
		}
	}

	if (tr.flFraction >= 1.0f)
	{
		if (fFirst)
		{
			if (!m_pPlayer->HasShield())
			{
				switch (m_iSwing++ % 2)
				{
				case 0: SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE); break;
				case 1: SendWeaponAnim(KNIFE_MIDATTACK2HIT, UseDecrement() != FALSE); break;
				}

				m_flNextPrimaryAttack = GetNextAttackDelay(0.35);
				m_flNextSecondaryAttack = WEAPON_TIMEBASED + 0.5;
			}
			else
			{
				SendWeaponAnim(KNIFE_SHIELD_ATTACKHIT, UseDecrement() != FALSE);

				m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
				m_flNextSecondaryAttack = WEAPON_TIMEBASED + 1.2;
			}

			m_flTimeWeaponIdle = WEAPON_TIMEBASED + 2.0;

			if (RANDOM_LONG(0, 1))
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash1.wav", VOL_NORM, ATTN_NORM, 0, 94);
			else
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash2.wav", VOL_NORM, ATTN_NORM, 0, 94);

			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		}
	}
	else
	{
		fDidHit = TRUE;

		if (!m_pPlayer->HasShield())
		{
			switch (m_iSwing++ % 2)
			{
			case 0: SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE); break;
			case 1: SendWeaponAnim(KNIFE_MIDATTACK2HIT, UseDecrement() != FALSE); break;
			}

			m_flNextPrimaryAttack = GetNextAttackDelay(0.4);
			m_flNextSecondaryAttack = WEAPON_TIMEBASED + 0.5;
		}
		else
		{
			SendWeaponAnim(KNIFE_SHIELD_ATTACKHIT, UseDecrement() != FALSE);

			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
			m_flNextSecondaryAttack = WEAPON_TIMEBASED + 1.2;
		}

		m_flTimeWeaponIdle = WEAPON_TIMEBASED + 2.0;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
		SetPlayerShieldAnim();

		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		ClearMultiDamage();

		if (m_flNextPrimaryAttack + 0.4 < WEAPON_TIMEBASED)
			pEntity->TraceAttack(m_pPlayer->pev, 20, gpGlobals->v_forward, &tr, (DMG_NEVERGIB | DMG_BULLET));
		else
			pEntity->TraceAttack(m_pPlayer->pev, 15, gpGlobals->v_forward, &tr, (DMG_NEVERGIB | DMG_BULLET));

		ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

		float flVol = 1;
		int fHitWorld = TRUE;

		if (pEntity != NULL && pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
		{
			switch (RANDOM_LONG(0, 3))
			{
			case 0: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit1.wav", VOL_NORM, ATTN_NORM); break;
			case 1: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit2.wav", VOL_NORM, ATTN_NORM); break;
			case 2: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit3.wav", VOL_NORM, ATTN_NORM); break;
			case 3: EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_hit4.wav", VOL_NORM, ATTN_NORM); break;
			}

			m_pPlayer->m_iWeaponVolume = KNIFE_BODYHIT_VOLUME;

			if (!pEntity->IsAlive())
			{
				return TRUE;
			}

			flVol = 0.1;
			fHitWorld = FALSE;
		}

		if (fHitWorld)
		{
			TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);

			if (RANDOM_LONG(0, 1) > 1)
			{
				fHitWorld = FALSE;
			}
		}

		if (!fHitWorld)
		{
			m_trHit = tr;
			SetThink(&CKnife::Smack);

			pev->nextthink = 0.2;
			m_pPlayer->m_iWeaponVolume = (int)(flVol * KNIFE_WALLHIT_VOLUME);
			
			ResetPlayerShieldAnim();
		}
		else
		{
			float fvolbar = RANDOM_LONG(0, 3) + 98;
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, fvolbar);
		}
	}

	return fDidHit;
}

/* <2714e1> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:468 */
int CKnife::Stab(int fFirst)
{
	int fDidHit = FALSE;
	TraceResult tr;
	Vector vecSrc, vecEnd;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecEnd = vecSrc + gpGlobals->v_forward * 32;

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, m_pPlayer->edict(), &tr);

	if (tr.flFraction >= 1.0f)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, m_pPlayer->edict(), &tr);

		if (tr.flFraction < 1.0f)
		{
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);

			if (!pHit || pHit->IsBSPModel())
			{
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, m_pPlayer->edict());
			}

			vecEnd = tr.vecEndPos;
		}
	}

	if (tr.flFraction >= 1.0f)
	{
		if (fFirst)
		{
			SendWeaponAnim(KNIFE_STABMISS, UseDecrement() != FALSE);

			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
			m_flNextSecondaryAttack = WEAPON_TIMEBASED + 1.0;

			if (RANDOM_LONG(0, 1))
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash1.wav", VOL_NORM, ATTN_NORM, 0, 94);
			else
				EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_slash2.wav", VOL_NORM, ATTN_NORM, 0, 94);

			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		}
	}
	else
	{
		fDidHit = TRUE;

		SendWeaponAnim(KNIFE_STABHIT, UseDecrement() != FALSE);

		m_flNextPrimaryAttack = GetNextAttackDelay(1.1);
		m_flNextSecondaryAttack = WEAPON_TIMEBASED + 1.1;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

		float flDamage = 65.0;

		if (pEntity && pEntity->IsPlayer())
		{
			Vector2D vec2LOS;
			float flDot;
			Vector vMyForward = gpGlobals->v_forward;

			UTIL_MakeVectors(pEntity->pev->angles);

			vec2LOS = vMyForward.Make2D();
			vec2LOS = vec2LOS.Normalize();

			flDot = DotProduct(vec2LOS, gpGlobals->v_forward.Make2D());

			if (flDot > 0.8)
			{
				flDamage *= 3.0;
			}
		}

		UTIL_MakeVectors(m_pPlayer->pev->v_angle);
		ClearMultiDamage();

		pEntity->TraceAttack(m_pPlayer->pev, flDamage, gpGlobals->v_forward, &tr, (DMG_NEVERGIB | DMG_BULLET));
		ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

		float flVol = 1.0f;
		int fHitWorld = TRUE;

		if (pEntity != NULL && pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
		{
			EMIT_SOUND(m_pPlayer->edict(), CHAN_WEAPON, "weapons/knife_stab.wav", VOL_NORM, ATTN_NORM);
			m_pPlayer->m_iWeaponVolume = KNIFE_BODYHIT_VOLUME;

			if (!pEntity->IsAlive())
			{
				return TRUE;
			}

			flVol = 0.1;
			fHitWorld = FALSE;
		}

		if (fHitWorld)
		{
			TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);

			if (RANDOM_LONG(0, 1) > 1)
			{
				fHitWorld = FALSE;
			}
		}

		if (!fHitWorld)
		{
			m_trHit = tr;
			m_pPlayer->m_iWeaponVolume = (int)(flVol * KNIFE_WALLHIT_VOLUME);
			
			SetThink(&CKnife::Smack);
			pev->nextthink = 0.2;

			ResetPlayerShieldAnim();
		}
		else
		{
			float fvolbar = RANDOM_LONG(0, 3) + 98;
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, fvolbar);
		}
	}

	return fDidHit;
}

#ifdef HOOK_GAMEDLL

void CKnife::Spawn(void)
{
	Spawn_();
}

void CKnife::Precache(void)
{
	Precache_();
}

int CKnife::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CKnife::Deploy(void)
{
	return Deploy_();
}

void CKnife::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CKnife::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CKnife::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CKnife::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
