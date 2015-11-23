#include "precompiled.h"

#define AK47_MAX_SPEED			221

#define AK47_DAMAGE			36
#define AK47_RANGE_MODIFER		0.98

#define AK47_RELOAD_TIME		2.45

enum ak47_e
{
	AK47_IDLE1,
	AK47_RELOAD,
	AK47_DRAW,
	AK47_SHOOT1,
	AK47_SHOOT2,
	AK47_SHOOT3
};

/* <23556d> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_ak47, CAK47);

/* <235327> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:52 */
void CAK47::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_AK47;
	SET_MODEL(edict(), "models/w_ak47.mdl");

	m_iDefaultAmmo = AK47_DEFAULT_GIVE;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

/* <235280> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:66 */
void CAK47::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_ak47.mdl");
	PRECACHE_MODEL("models/w_ak47.mdl");

	PRECACHE_SOUND("weapons/ak47-1.wav");
	PRECACHE_SOUND("weapons/ak47-2.wav");
	PRECACHE_SOUND("weapons/ak47_clipout.wav");
	PRECACHE_SOUND("weapons/ak47_clipin.wav");
	PRECACHE_SOUND("weapons/ak47_boltpull.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireAK47 = PRECACHE_EVENT(1, "events/ak47.sc");
}

/* <2352a7> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:82 */
int CAK47::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "762Nato";
	p->iMaxAmmo1 = MAX_AMMO_762NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AK47_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 1;
	p->iId = m_iId = WEAPON_AK47;
	p->iFlags = 0;
	p->iWeight = AK47_WEIGHT;

	return 1;
}

/* <235300> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:99 */
BOOL CAK47::__MAKE_VHOOK(Deploy)(void)
{
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

	return DefaultDeploy("models/v_ak47.mdl", "models/p_ak47.mdl", AK47_DRAW, "ak47", UseDecrement() != FALSE);
}

/* <2352da> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:108 */
void CAK47::__MAKE_VHOOK(SecondaryAttack)(void)
{
	;
}

/* <235523> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:112 */
void CAK47::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		AK47Fire(0.04 + (0.4 * m_flAccuracy), 0.0955, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
	{
		AK47Fire(0.04 + (0.07 * m_flAccuracy), 0.0955, FALSE);
	}
	else
	{
		AK47Fire(0.0275 * m_flAccuracy, 0.0955, FALSE);
	}
}

/* <235637> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:123 */
void CAK47::AK47Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
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

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 2, BULLET_PLAYER_762MM,
		AK47_DAMAGE, AK47_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireAK47, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		(int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.9;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(1.5, 0.45, 0.225, 0.05, 6.5, 2.5, 7);
	}
	else if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(2.0, 1.0, 0.5, 0.35, 9.0, 6.0, 5);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.9, 0.35, 0.15, 0.025, 5.5, 1.5, 9);
	}
	else
	{
		KickBack(1.0, 0.375, 0.175, 0.0375, 5.75, 1.75, 8);
	}
}

/* <2353d8> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:204 */
void CAK47::__MAKE_VHOOK(Reload)(void)
{
#ifdef REGAMEDLL_FIXES
	// to prevent reload if not enough ammo
	if (m_pPlayer->ammo_762nato <= 0)
	{
		return;
	}
#endif // REGAMEDLL_FIXES

	if (DefaultReload(AK47_MAX_CLIP, AK47_RELOAD, AK47_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}

/* <23539d> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:219 */
void CAK47::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
		SendWeaponAnim(AK47_IDLE1, UseDecrement() != FALSE);
	}
}

#ifdef HOOK_GAMEDLL

void CAK47::Spawn(void)
{
	Spawn_();
}

void CAK47::Precache(void)
{
	Precache_();
}

int CAK47::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CAK47::Deploy(void)
{
	return Deploy_();
}

void CAK47::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CAK47::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CAK47::Reload(void)
{
	Reload_();
}

void CAK47::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
