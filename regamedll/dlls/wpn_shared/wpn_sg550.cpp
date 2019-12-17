#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_sg550, CSG550, CCSSG550)

void CSG550::Spawn()
{
	Precache();

	m_iId = WEAPON_SG550;
	SET_MODEL(edict(), "models/w_sg550.mdl");

	m_iDefaultAmmo = SG550_DEFAULT_GIVE;
	m_flLastFire = 0;

#ifdef REGAMEDLL_FIXES
	m_flAccuracy = 0.2f;
#endif

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = SG550_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CSG550::Precache()
{
	PRECACHE_MODEL("models/v_sg550.mdl");
	PRECACHE_MODEL("models/w_sg550.mdl");

	PRECACHE_SOUND("weapons/sg550-1.wav");
	PRECACHE_SOUND("weapons/sg550_boltpull.wav");
	PRECACHE_SOUND("weapons/sg550_clipin.wav");
	PRECACHE_SOUND("weapons/sg550_clipout.wav");
	PRECACHE_SOUND("weapons/zoom.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireSG550 = PRECACHE_EVENT(1, "events/sg550.sc");
}

int CSG550::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = SG550_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 16;
	p->iId = m_iId = WEAPON_SG550;
	p->iFlags = 0;
	p->iWeight = SG550_WEIGHT;

	return 1;
}

BOOL CSG550::Deploy()
{
#ifdef REGAMEDLL_FIXES
	m_flAccuracy = 0.2f;
#endif

	return DefaultDeploy("models/v_sg550.mdl", "models/p_sg550.mdl", SG550_DRAW, "rifle", UseDecrement() != FALSE);
}

void CSG550::SecondaryAttack()
{
	switch (m_pPlayer->m_iFOV)
	{
	case 90: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; break;
	case 40: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 15; break;
#ifdef REGAMEDLL_FIXES
	default:
#else
	case 15:
#endif
		m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; break;
	}

	m_pPlayer->ResetMaxSpeed();

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_WEAPON_ZOOMED, m_pPlayer);
	}

	EMIT_SOUND(m_pPlayer->edict(), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CSG550::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		SG550Fire(0.45 * (1 - m_flAccuracy), 0.25, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		SG550Fire(0.15, 0.25, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		SG550Fire(0.04 * (1 - m_flAccuracy), 0.25, FALSE);
	}
	else
	{
		SG550Fire(0.05 * (1 - m_flAccuracy), 0.25, FALSE);
	}
}

void CSG550::SG550Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	if (m_pPlayer->pev->fov == DEFAULT_FOV)
	{
		flSpread += 0.025f;
	}

	if (m_flLastFire)
	{
		m_flAccuracy = (gpGlobals->time - m_flLastFire) * 0.35f + 0.65f;

		if (m_flAccuracy > 0.98f)
		{
			m_flAccuracy = 0.98f;
		}
	}

	m_flLastFire = gpGlobals->time;

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

	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = SG550_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 2, BULLET_PLAYER_556MM, flBaseDamage, SG550_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireSG550, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.x * 100), 5, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.8f;

	m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomFloat(m_pPlayer->random_seed + 4, 0.75, 1.25) + m_pPlayer->pev->punchangle.x * 0.25;
	m_pPlayer->pev->punchangle.y += UTIL_SharedRandomFloat(m_pPlayer->random_seed + 5, -0.75, 0.75);
}

void CSG550::Reload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;

	if (DefaultReload(iMaxClip(), SG550_RELOAD, SG550_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		if (m_pPlayer->pev->fov != DEFAULT_FOV)
		{
			m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 15;
			SecondaryAttack();
		}
	}
}

void CSG550::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60.0f;
		SendWeaponAnim(SG550_IDLE, UseDecrement() != FALSE);
	}
}

float CSG550::GetMaxSpeed()
{
	return (m_pPlayer->m_iFOV == DEFAULT_FOV) ? SG550_MAX_SPEED : SG550_MAX_SPEED_ZOOM;
}
