#include "precompiled.h"

/* <2662bb> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:68 */
LINK_ENTITY_TO_CLASS(weapon_glock18, CGLOCK18);

/* <26611a> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:70 */
void CGLOCK18::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_GLOCK18;
	SET_MODEL(edict(), "models/w_glock18.mdl");

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_iDefaultAmmo = GLOCK18_DEFAULT_GIVE;
	m_bBurstFire = false;

	m_iGlock18ShotsFired = 0;
	m_flGlock18Shoot = 0;
	m_flAccuracy = 0.9;

	FallInit();
}

/* <2660c0> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:88 */
void CGLOCK18::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_glock18.mdl");
	PRECACHE_MODEL("models/w_glock18.mdl");
	PRECACHE_MODEL("models/shield/v_shield_glock18.mdl");

	PRECACHE_SOUND("weapons/glock18-1.wav");
	PRECACHE_SOUND("weapons/glock18-2.wav");
	PRECACHE_SOUND("weapons/clipout1.wav");
	PRECACHE_SOUND("weapons/clipin1.wav");
	PRECACHE_SOUND("weapons/sliderelease1.wav");
	PRECACHE_SOUND("weapons/slideback1.wav");
	PRECACHE_SOUND("weapons/357_cock1.wav");
	PRECACHE_SOUND("weapons/de_clipin.wav");
	PRECACHE_SOUND("weapons/de_clipout.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireGlock18 = PRECACHE_EVENT(1, "events/glock18.sc");
}

/* <2660e7> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:112 */
int CGLOCK18::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = GLOCK18_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 2;
	p->iId = m_iId = WEAPON_GLOCK18;
	p->iFlags = 0;
	p->iWeight = GLOCK18_WEIGHT;

	return 1;
}

/* <266281> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:129 */
BOOL CGLOCK18::__MAKE_VHOOK(Deploy)(void)
{
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	m_bBurstFire = false;
	m_iGlock18ShotsFired = 0;
	m_flGlock18Shoot = 0;
	m_flAccuracy = 0.9;
	m_fMaxSpeed = GLOCK18_MAX_SPEED;

	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
	{
		m_iWeaponState &= ~WPNSTATE_GLOCK18_BURST_MODE;
		return DefaultDeploy("models/shield/v_shield_glock18.mdl", "models/shield/p_shield_glock18.mdl", GLOCK18_SHIELD_DRAW, "shieldgun", UseDecrement() != FALSE);
	}
	else if (RANDOM_LONG(0, 1))
	{
		return DefaultDeploy("models/v_glock18.mdl", "models/p_glock18.mdl", GLOCK18_DRAW, "onehanded", UseDecrement() != FALSE);
	}

	return DefaultDeploy("models/v_glock18.mdl", "models/p_glock18.mdl", GLOCK18_DRAW2, "onehanded", UseDecrement() != FALSE);
}

/* <266246> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:156 */
void CGLOCK18::__MAKE_VHOOK(SecondaryAttack)(void)
{
	if (ShieldSecondaryFire(GLOCK18_SHIELD_UP, GLOCK18_SHIELD_DOWN))
	{
		return;
	}

	if (m_iWeaponState & WPNSTATE_GLOCK18_BURST_MODE)
	{
		ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#Switch_To_SemiAuto");
		m_iWeaponState &= ~WPNSTATE_GLOCK18_BURST_MODE;
	}
	else
	{
		ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#Switch_To_BurstFire");
		m_iWeaponState |= WPNSTATE_GLOCK18_BURST_MODE;
	}
	
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

/* <2664c3> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:175 */
void CGLOCK18::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (m_iWeaponState & WPNSTATE_GLOCK18_BURST_MODE)
	{
		if (!(m_pPlayer->pev->flags & FL_ONGROUND))
		{
			GLOCK18Fire(1.2 * (1 - m_flAccuracy), 0.5, TRUE);
		}
		else if (m_pPlayer->pev->velocity.Length2D() > 0)
		{
			GLOCK18Fire(0.185 * (1 - m_flAccuracy), 0.5, TRUE);
		}
		else if (m_pPlayer->pev->flags & FL_DUCKING)
		{
			GLOCK18Fire(0.095 * (1 - m_flAccuracy), 0.5, TRUE);
		}
		else
		{
			GLOCK18Fire(0.3 * (1 - m_flAccuracy), 0.5, TRUE);
		}
	}
	else
	{
		if (!(m_pPlayer->pev->flags & FL_ONGROUND))
		{
			GLOCK18Fire(1.0 * (1 - m_flAccuracy), 0.2, FALSE);
		}
		else if (m_pPlayer->pev->velocity.Length2D() > 0)
		{
			GLOCK18Fire(0.165 * (1 - m_flAccuracy), 0.2, FALSE);
		}
		else if (m_pPlayer->pev->flags & FL_DUCKING)
		{
			GLOCK18Fire(0.075 * (1 - m_flAccuracy), 0.2, FALSE);
		}
		else
		{
			GLOCK18Fire(0.1 * (1 - m_flAccuracy), 0.2, FALSE);
		}
	}
}

/* <266385> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:201 */
void CGLOCK18::GLOCK18Fire(float flSpread, float flCycleTime, BOOL bFireBurst)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	if (bFireBurst)
	{
		m_iGlock18ShotsFired = 0;
	}
	else
	{
		m_iShotsFired++;

		if (m_iShotsFired > 1)
		{
			return;
		}

		flCycleTime -= 0.05;
	}

	if (m_flLastFire)
	{
		// Mark the time of this shot and determine the accuracy modifier based on the last shot fired...
		m_flAccuracy -= (0.325 - (gpGlobals->time - m_flLastFire)) * 0.275;

		if (m_flAccuracy > 0.9)
		{
			m_flAccuracy = 0.9;
		}
		else if (m_flAccuracy < 0.6)
		{
			m_flAccuracy = 0.6;
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

		if (TheBots != NULL)
		{
			TheBots->OnEvent(EVENT_WEAPON_FIRED_ON_EMPTY, m_pPlayer);
		}

		return;
	}

	m_iClip--;

	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;

	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	// non-silenced
	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_9MM, GLOCK18_DAMAGE, GLOCK18_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireGlock18, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		(int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), m_iClip == 0, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, FALSE);
	}
	
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.5;

	if (bFireBurst)
	{
		// Fire off the next two rounds
		m_iGlock18ShotsFired++;
		m_flGlock18Shoot = gpGlobals->time + 0.1;
	}

	ResetPlayerShieldAnim();
}

/* <2661e8> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:307 */
void CGLOCK18::__MAKE_VHOOK(Reload)(void)
{
	int iResult;

	if (m_pPlayer->ammo_9mm <= 0)
	{
		return;
	}

	if (m_pPlayer->HasShield())
		iResult = GLOCK18_SHIELD_RELOAD;
	else if (RANDOM_LONG(0, 1))
		iResult = GLOCK18_RELOAD;
	else
		iResult = GLOCK18_RELOAD2;

	if (DefaultReload(GLOCK18_MAX_CLIP, iResult, GLOCK18_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.9;
	}
}

/* <266190> ../cstrike/dlls/wpn_shared/wpn_glock18.cpp:329 */
void CGLOCK18::__MAKE_VHOOK(WeaponIdle)(void)
{
	int iAnim;
	float flRand;

	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	if (m_pPlayer->HasShield())
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0;

		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		{
			SendWeaponAnim(GLOCK18_SHIELD_IDLE, UseDecrement() != FALSE);
		}
	}
	// only idle if the slid isn't back
	else if (m_iClip)
	{
		flRand = RANDOM_FLOAT(0, 1);

		if (flRand <= 0.3)
		{
			iAnim = GLOCK18_IDLE3;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3.0625;
		}
		else if (flRand <= 0.6)
		{
			iAnim = GLOCK18_IDLE1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3.75;
		}
		else
		{
			iAnim = GLOCK18_IDLE2;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.5;
		}

		SendWeaponAnim(iAnim, UseDecrement() != FALSE);
	}
}

#ifdef HOOK_GAMEDLL

void CGLOCK18::Spawn(void)
{
	Spawn_();
}

void CGLOCK18::Precache(void)
{
	Precache_();
}

int CGLOCK18::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CGLOCK18::Deploy(void)
{
	return Deploy_();
}

void CGLOCK18::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CGLOCK18::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CGLOCK18::Reload(void)
{
	Reload_();
}

void CGLOCK18::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
