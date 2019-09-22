#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_sg552, CSG552, CCSSG552)

void CSG552::Spawn()
{
	Precache();

	m_iId = WEAPON_SG552;
	SET_MODEL(edict(), "models/w_sg552.mdl");

	m_iDefaultAmmo = SG552_DEFAULT_GIVE;
	m_flAccuracy = 0.2f;
	m_iShotsFired = 0;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = SG552_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CSG552::Precache()
{
	PRECACHE_MODEL("models/v_sg552.mdl");
	PRECACHE_MODEL("models/w_sg552.mdl");

	PRECACHE_SOUND("weapons/sg552-1.wav");
	PRECACHE_SOUND("weapons/sg552-2.wav");
	PRECACHE_SOUND("weapons/sg552_clipout.wav");
	PRECACHE_SOUND("weapons/sg552_clipin.wav");
	PRECACHE_SOUND("weapons/sg552_boltpull.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireSG552 = PRECACHE_EVENT(1, "events/sg552.sc");
}

int CSG552::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = SG552_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 10;
	p->iId = m_iId = WEAPON_SG552;
	p->iFlags = 0;
	p->iWeight = SG552_WEIGHT;

	return 1;
}

BOOL CSG552::Deploy()
{
	m_flAccuracy = 0.2f;
	m_iShotsFired = 0;
	iShellOn = 1;

	return DefaultDeploy("models/v_sg552.mdl", "models/p_sg552.mdl", SG552_DRAW, "mp5", UseDecrement() != FALSE);
}

void CSG552::SecondaryAttack()
{
	if (m_pPlayer->m_iFOV == DEFAULT_FOV)
		m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 55;
	else
		m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 90;

	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3f;
}

void CSG552::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		SG552Fire(0.035 + (0.45 * m_flAccuracy), 0.0825, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
	{
		SG552Fire(0.035 + (0.075 * m_flAccuracy), 0.0825, FALSE);
	}
	else if (m_pPlayer->pev->fov == DEFAULT_FOV)
	{
		SG552Fire(0.02 * m_flAccuracy, 0.0825, FALSE);
	}
	else
	{
		SG552Fire(0.02 * m_flAccuracy, 0.135, FALSE);
	}
}

void CSG552::SG552Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220) + 0.3f;

	if (m_flAccuracy > 1.0f)
		m_flAccuracy = 1.0f;

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

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = SG552_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 2, BULLET_PLAYER_556MM,
		flBaseDamage, SG552_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireSG552, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), 5, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(1.0, 0.45, 0.28, 0.04, 4.25, 2.5, 7);
	}
	else if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(1.25, 0.45, 0.22, 0.18, 6.0, 4.0, 5);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.6, 0.35, 0.2, 0.0125, 3.7, 2.0, 10);
	}
	else
	{
		KickBack(0.625, 0.375, 0.25, 0.0125, 4.0, 2.25, 9);
	}
}

void CSG552::Reload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;

	if (DefaultReload(iMaxClip(), SG552_RELOAD, SG552_RELOAD_TIME))
	{
		if (m_pPlayer->m_iFOV != DEFAULT_FOV)
		{
			SecondaryAttack();
		}

		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.2f;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}

void CSG552::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;
	SendWeaponAnim(SG552_IDLE1, UseDecrement() != FALSE);
}

float CSG552::GetMaxSpeed()
{
	if (m_pPlayer->m_iFOV == DEFAULT_FOV)
		return SG552_MAX_SPEED;

	return SG552_MAX_SPEED_ZOOM;
}
