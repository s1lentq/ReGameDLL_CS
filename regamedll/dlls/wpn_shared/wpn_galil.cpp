#include "precompiled.h"

/* <2c5a1c> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_galil, CGalil);

/* <2c57b0> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:52 */
void CGalil::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_GALIL;
	SET_MODEL(edict(), "models/w_galil.mdl");

	m_iDefaultAmmo = GALIL_DEFAULT_GIVE;

	FallInit();
}

/* <2c5709> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:65 */
void CGalil::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_galil.mdl");
	PRECACHE_MODEL("models/w_galil.mdl");

	PRECACHE_SOUND("weapons/galil-1.wav");
	PRECACHE_SOUND("weapons/galil-2.wav");
	PRECACHE_SOUND("weapons/galil_clipout.wav");
	PRECACHE_SOUND("weapons/galil_clipin.wav");
	PRECACHE_SOUND("weapons/galil_boltpull.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireGalil = PRECACHE_EVENT(1, "events/galil.sc");
}

/* <2c5730> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:81 */
int CGalil::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = GALIL_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = m_iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = GALIL_WEIGHT;

	return 1;
}

/* <2c5789> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:98 */
BOOL CGalil::__MAKE_VHOOK(Deploy)(void)
{
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

	return DefaultDeploy("models/v_galil.mdl", "models/p_galil.mdl", GALIL_DRAW, "ak47", UseDecrement() != FALSE);
}

/* <2c5763> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:107 */
void CGalil::__MAKE_VHOOK(SecondaryAttack)(void)
{
	;
}

/* <2c59d2> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:111 */
void CGalil::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = GetNextAttackDelay(0.15);
		return;
	}

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		GalilFire(0.04 + (0.3 * m_flAccuracy), 0.0875, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
	{
		GalilFire(0.04 + (0.07 * m_flAccuracy), 0.0875, FALSE);
	}
	else
	{
		GalilFire(0.0375 * m_flAccuracy, 0.0875, FALSE);
	}
}

/* <2c5ae6> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:129 */
void CGalil::GalilFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.35;

	if (m_flAccuracy > 1.25)
		m_flAccuracy = 1.25;

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = GetNextAttackDelay(0.2);
		}

		if (TheBots != NULL)
		{
			TheBots->OnEvent(EVENT_WEAPON_FIRED_ON_EMPTY, m_pPlayer);
		}

		return;
	}

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 2, BULLET_PLAYER_556MM,
		GALIL_DAMAGE, GALIL_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireGalil, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		(int)(m_pPlayer->pev->punchangle.x * 10000000), (int)(m_pPlayer->pev->punchangle.y * 10000000), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.28;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(1.0, 0.45, 0.28, 0.045, 3.75, 3.0, 7);
	}
	else if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(1.2, 0.5, 0.23, 0.15, 5.5, 3.5, 6);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.6, 0.3, 0.2, 0.0125, 3.25, 2.0, 7);
	}
	else
	{
		KickBack(0.65, 0.35, 0.25, 0.015, 3.5, 2.25, 7);
	}
}

/* <2c5861> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:210 */
void CGalil::__MAKE_VHOOK(Reload)(void)
{
#ifdef REGAMEDLL_FIXES
	// to prevent reload if not enough ammo
	if (m_pPlayer->ammo_556nato <= 0)
	{
		return;
	}
#endif // REGAMEDLL_FIXES

	if (DefaultReload(GALIL_MAX_CLIP, GALIL_RELOAD, GALIL_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}

/* <2c5826> ../cstrike/dlls/wpn_shared/wpn_galil.cpp:232 */
void CGalil::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
		SendWeaponAnim(GALIL_IDLE1, UseDecrement() != FALSE);
	}
}

#ifdef HOOK_GAMEDLL

void CGalil::Spawn(void)
{
	Spawn_();
}

void CGalil::Precache(void)
{
	Precache_();
}

int CGalil::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CGalil::Deploy(void)
{
	return Deploy_();
}

void CGalil::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CGalil::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CGalil::Reload(void)
{
	Reload_();
}

void CGalil::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
