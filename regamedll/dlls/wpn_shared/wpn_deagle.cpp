#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_deagle, CDEAGLE, CCSDEAGLE)

void CDEAGLE::Spawn()
{
	Precache();

	m_iId = WEAPON_DEAGLE;
	SET_MODEL(edict(), "models/w_deagle.mdl");

	m_iDefaultAmmo = DEAGLE_DEFAULT_GIVE;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_fMaxSpeed = DEAGLE_MAX_SPEED;
	m_flAccuracy = 0.9f;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = DEAGLE_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CDEAGLE::Precache()
{
	PRECACHE_MODEL("models/v_deagle.mdl");
	PRECACHE_MODEL("models/shield/v_shield_deagle.mdl");
	PRECACHE_MODEL("models/w_deagle.mdl");

	PRECACHE_SOUND("weapons/deagle-1.wav");
	PRECACHE_SOUND("weapons/deagle-2.wav");
	PRECACHE_SOUND("weapons/de_clipout.wav");
	PRECACHE_SOUND("weapons/de_clipin.wav");
	PRECACHE_SOUND("weapons/de_deploy.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireDeagle = PRECACHE_EVENT(1, "events/deagle.sc");
}

int CDEAGLE::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "50AE";
	p->iMaxAmmo1 = MAX_AMMO_50AE;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = DEAGLE_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 1;
	p->iId = m_iId = WEAPON_DEAGLE;
	p->iFlags = 0;
	p->iWeight = DEAGLE_WEIGHT;

	return 1;
}

BOOL CDEAGLE::Deploy()
{
	m_flAccuracy = 0.9f;
	m_fMaxSpeed = DEAGLE_MAX_SPEED;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
		return DefaultDeploy("models/shield/v_shield_deagle.mdl", "models/shield/p_shield_deagle.mdl", DEAGLE_DRAW, "shieldgun", UseDecrement() != FALSE);
	else
		return DefaultDeploy("models/v_deagle.mdl", "models/p_deagle.mdl", DEAGLE_DRAW, "onehanded", UseDecrement() != FALSE);
}

void CDEAGLE::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		DEAGLEFire(1.5 * (1 - m_flAccuracy), 0.3, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		DEAGLEFire(0.25 * (1 - m_flAccuracy), 0.3, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		DEAGLEFire(0.115 * (1 - m_flAccuracy), 0.3, FALSE);
	}
	else
	{
		DEAGLEFire(0.13 * (1 - m_flAccuracy), 0.3, FALSE);
	}
}

void CDEAGLE::SecondaryAttack()
{
	ShieldSecondaryFire(DEAGLE_SHIELD_UP, DEAGLE_SHIELD_DOWN);
}

void CDEAGLE::DEAGLEFire(float flSpread, float flCycleTime, BOOL fUseSemi)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	flCycleTime -= 0.075f;

	if (++m_iShotsFired > 1)
	{
		return;
	}

	if (m_flLastFire != 0.0)
	{
		m_flAccuracy -= (0.4f - (gpGlobals->time - m_flLastFire)) * 0.35f;

		if (m_flAccuracy > 0.9f)
		{
			m_flAccuracy = 0.9f;
		}
		else if (m_flAccuracy < 0.55f)
		{
			m_flAccuracy = 0.55f;
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
	SetPlayerShieldAnim();

	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = DEAGLE_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 4096, 2, BULLET_PLAYER_50AE, flBaseDamage, DEAGLE_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireDeagle, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), m_iClip == 0, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.8f;
#ifdef REGAMEDLL_ADD
	KickBack(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0);
#else
	m_pPlayer->pev->punchangle.x -= 2;
#endif
	ResetPlayerShieldAnim();
}

void CDEAGLE::Reload()
{
	if (m_pPlayer->ammo_50ae <= 0)
		return;

	if (DefaultReload(iMaxClip(), DEAGLE_RELOAD, DEAGLE_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.9f;
	}
}

void CDEAGLE::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
#ifdef REGAMEDLL_FIXES
		if (m_pPlayer->HasShield())
#endif
		{
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;

			if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			{
				SendWeaponAnim(DEAGLE_SHIELD_IDLE_UP, UseDecrement() != FALSE);
			}
		}
#ifdef REGAMEDLL_FIXES
		else if (m_iClip)
		{
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3.0625f;
			SendWeaponAnim(DEAGLE_IDLE1, UseDecrement() != FALSE);
		}
#endif
	}
}
