#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_awp, CAWP, CCSAWP)

void CAWP::Spawn()
{
	Precache();

	m_iId = WEAPON_AWP;
	SET_MODEL(ENT(pev), "models/w_awp.mdl");

	m_iDefaultAmmo = AWP_DEFAULT_GIVE;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = AWP_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CAWP::Precache()
{
	PRECACHE_MODEL("models/v_awp.mdl");
	PRECACHE_MODEL("models/w_awp.mdl");

	PRECACHE_SOUND("weapons/awp1.wav");
	PRECACHE_SOUND("weapons/boltpull1.wav");
	PRECACHE_SOUND("weapons/boltup.wav");
	PRECACHE_SOUND("weapons/boltdown.wav");
	PRECACHE_SOUND("weapons/zoom.wav");
	PRECACHE_SOUND("weapons/awp_deploy.wav");
	PRECACHE_SOUND("weapons/awp_clipin.wav");
	PRECACHE_SOUND("weapons/awp_clipout.wav");

	m_iShell = PRECACHE_MODEL("models/rshell_big.mdl");
	m_iShellId = m_iShell;
	m_usFireAWP = PRECACHE_EVENT(1, "events/awp.sc");
}

int CAWP::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "338Magnum";
	p->iMaxAmmo1 = MAX_AMMO_338MAGNUM;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AWP_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 2;
	p->iId = m_iId = WEAPON_AWP;
	p->iFlags = 0;
	p->iWeight = AWP_WEIGHT;

	return 1;
}

BOOL CAWP::Deploy()
{
	if (DefaultDeploy("models/v_awp.mdl", "models/p_awp.mdl", AWP_DRAW, "rifle", UseDecrement() != FALSE))
	{
		m_pPlayer->m_flNextAttack = GetNextAttackDelay(1.45);
		m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0f;

		return TRUE;
	}

	return FALSE;
}

void CAWP::SecondaryAttack()
{
	switch (m_pPlayer->m_iFOV)
	{
	case 90: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; break;
	case 40: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 10; break;
	default: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; break;
	}

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_WEAPON_ZOOMED, m_pPlayer);
	}

	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(m_pPlayer->edict(), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);

	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CAWP::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		AWPFire(0.85, 1.45, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
	{
		AWPFire(0.25, 1.45, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 10)
	{
		AWPFire(0.1, 1.45, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		AWPFire(0.0, 1.45, FALSE);
	}
	else
	{
		AWPFire(0.001, 1.45, FALSE);
	}
}

void CAWP::AWPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	if (m_pPlayer->pev->fov != DEFAULT_FOV)
	{
		m_pPlayer->m_bResumeZoom = true;
		m_pPlayer->m_iLastZoom = m_pPlayer->m_iFOV;

		// reset a fov
		m_pPlayer->m_iFOV = DEFAULT_FOV;
		m_pPlayer->pev->fov = DEFAULT_FOV;
	}
	// If we are not zoomed in, the bullet diverts more.
	else
	{
		flSpread += 0.08f;
	}

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

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.55f;
	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = AWP_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 3, BULLET_PLAYER_338MAG, flBaseDamage, AWP_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireAWP, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.x * 100), FALSE, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;
	m_pPlayer->pev->punchangle.x -= 2.0f;
}

void CAWP::Reload()
{
	if (m_pPlayer->ammo_338mag <= 0)
		return;

	if (DefaultReload(iMaxClip(), AWP_RELOAD, AWP_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		if (m_pPlayer->pev->fov != DEFAULT_FOV)
		{
			m_pPlayer->m_iFOV = 10;
			m_pPlayer->pev->fov = 10;

			SecondaryAttack();
		}
	}
}

void CAWP::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase() && m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60.0f;
		SendWeaponAnim(AWP_IDLE, UseDecrement() != FALSE);
	}
}

float CAWP::GetMaxSpeed()
{
	if (m_pPlayer->m_iFOV == DEFAULT_FOV)
		return AWP_MAX_SPEED;

	// Slower speed when zoomed in.
	return AWP_MAX_SPEED_ZOOM;
}
