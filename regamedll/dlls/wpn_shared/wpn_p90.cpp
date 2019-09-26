#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_p90, CP90, CCSP90)

void CP90::Spawn()
{
	Precache();

	m_iId = WEAPON_P90;
	SET_MODEL(edict(), "models/w_p90.mdl");

	m_iDefaultAmmo = P90_DEFAULT_GIVE;
	m_flAccuracy = 0.2f;
	m_iShotsFired = 0;
	m_bDelayFire = false;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = P90_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CP90::Precache()
{
	PRECACHE_MODEL("models/v_p90.mdl");
	PRECACHE_MODEL("models/w_p90.mdl");

	PRECACHE_SOUND("weapons/p90-1.wav");
	PRECACHE_SOUND("weapons/p90_clipout.wav");
	PRECACHE_SOUND("weapons/p90_clipin.wav");
	PRECACHE_SOUND("weapons/p90_boltpull.wav");
	PRECACHE_SOUND("weapons/p90_cliprelease.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireP90 = PRECACHE_EVENT(1, "events/p90.sc");
}

int CP90::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "57mm";
	p->iMaxAmmo1 = MAX_AMMO_57MM;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = P90_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 8;
	p->iId = m_iId = WEAPON_P90;
	p->iFlags = 0;
	p->iWeight = P90_WEIGHT;

	return 1;
}

BOOL CP90::Deploy()
{
	m_iShotsFired = 0;
	m_bDelayFire = false;
	m_flAccuracy = 0.2f;

	iShellOn = 1;

	return DefaultDeploy("models/v_p90.mdl", "models/p_p90.mdl", P90_DRAW, "carbine", UseDecrement() != FALSE);
}

void CP90::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		P90Fire(0.3 * m_flAccuracy, 0.066, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 170)
	{
		P90Fire(0.115 * m_flAccuracy, 0.066, FALSE);
	}
	else
	{
		P90Fire(0.045 * m_flAccuracy, 0.066, FALSE);
	}
}

void CP90::P90Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = (m_iShotsFired * m_iShotsFired / 175) + 0.45f;

	if (m_flAccuracy > 1)
		m_flAccuracy = 1;

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = GetNextAttackDelay(0.2);
		}

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_WEAPON_FIRED_ON_EMPTY, m_pPlayer);
		}

		return;
	}

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = P90_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_57MM, flBaseDamage, P90_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireP90, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), 5, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(0.9, 0.45, 0.35, 0.04, 5.25, 3.5, 4);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(0.45, 0.3, 0.2, 0.0275, 4.0, 2.25, 7);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.275, 0.2, 0.125, 0.02, 3.0, 1.0, 9);
	}
	else
	{
		KickBack(0.3, 0.225, 0.125, 0.02, 3.25, 1.25, 8);
	}
}

void CP90::Reload()
{
	if (m_pPlayer->ammo_57mm <= 0)
		return;

	if (DefaultReload(iMaxClip(), P90_RELOAD, P90_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.2f;
		m_iShotsFired = 0;
	}
}

void CP90::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;
	SendWeaponAnim(P90_IDLE1, UseDecrement() != FALSE);
}

float CP90::GetMaxSpeed()
{
	return P90_MAX_SPEED;
}
