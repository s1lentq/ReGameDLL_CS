#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_p228, CP228, CCSP228)

void CP228::Spawn()
{
	Precache();

	m_iId = WEAPON_P228;
	SET_MODEL(ENT(pev), "models/w_p228.mdl");

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_iDefaultAmmo = P228_DEFAULT_GIVE;
	m_flAccuracy = 0.9f;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = P228_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CP228::Precache()
{
	PRECACHE_MODEL("models/v_p228.mdl");
	PRECACHE_MODEL("models/w_p228.mdl");
	PRECACHE_MODEL("models/shield/v_shield_p228.mdl");

	PRECACHE_SOUND("weapons/p228-1.wav");
	PRECACHE_SOUND("weapons/p228_clipout.wav");
	PRECACHE_SOUND("weapons/p228_clipin.wav");
	PRECACHE_SOUND("weapons/p228_sliderelease.wav");
	PRECACHE_SOUND("weapons/p228_slidepull.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireP228 = PRECACHE_EVENT(1, "events/p228.sc");
}

int CP228::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "357SIG";
	p->iMaxAmmo1 = MAX_AMMO_357SIG;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = P228_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 3;
	p->iId = m_iId = WEAPON_P228;
	p->iFlags = 0;
	p->iWeight = P228_WEIGHT;

	return 1;
}

BOOL CP228::Deploy()
{
	m_flAccuracy = 0.9f;
	m_fMaxSpeed = P228_MAX_SPEED;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
		return DefaultDeploy("models/shield/v_shield_p228.mdl", "models/shield/p_shield_p228.mdl", P228_SHIELD_DRAW, "shieldgun", UseDecrement() != FALSE);
	else
		return DefaultDeploy("models/v_p228.mdl", "models/p_p228.mdl", P228_DRAW, "onehanded", UseDecrement() != FALSE);
}

void CP228::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		P228Fire(1.5 * (1 - m_flAccuracy), 0.2, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		P228Fire(0.255 * (1 - m_flAccuracy), 0.2, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		P228Fire(0.075 * (1 - m_flAccuracy), 0.2, FALSE);
	}
	else
	{
		P228Fire(0.15 * (1 - m_flAccuracy), 0.2, FALSE);
	}
}

void CP228::SecondaryAttack()
{
	ShieldSecondaryFire(SHIELDGUN_UP, SHIELDGUN_DOWN);
}

void CP228::P228Fire(float flSpread, float flCycleTime, BOOL fUseSemi)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	flCycleTime -= 0.05f;

	if (++m_iShotsFired > 1)
	{
		return;
	}

	if (m_flLastFire != 0.0f)
	{
		m_flAccuracy -= (0.325f - (gpGlobals->time - m_flLastFire)) * 0.3f;

		if (m_flAccuracy > 0.9f)
		{
			m_flAccuracy = 0.9f;
		}
		else if (m_flAccuracy < 0.6f)
		{
			m_flAccuracy = 0.6f;
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
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = P228_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 4096, 1, BULLET_PLAYER_357SIG, flBaseDamage, P228_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireP228, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), m_iClip == 0, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;
	m_pPlayer->pev->punchangle.x -= 2;
	ResetPlayerShieldAnim();
}

void CP228::Reload()
{
	if (m_pPlayer->ammo_357sig <= 0)
		return;

	if (DefaultReload(iMaxClip(), m_pPlayer->HasShield() ? P228_SHIELD_RELOAD : P228_RELOAD, P228_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.9f;
	}
}

void CP228::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	if (m_pPlayer->HasShield())
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;

		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		{
			SendWeaponAnim(P228_SHIELD_IDLE_UP, UseDecrement() != FALSE);
		}
	}
	else if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3.0625f;
		SendWeaponAnim(P228_IDLE, UseDecrement() != FALSE);
	}
}
