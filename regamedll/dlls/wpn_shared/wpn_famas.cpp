#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_famas, CFamas, CCSFamas)

void CFamas::Spawn()
{
	Precache();

	m_iId = WEAPON_FAMAS;
	SET_MODEL(edict(), "models/w_famas.mdl");

	m_iDefaultAmmo = FAMAS_DEFAULT_GIVE;
	m_iFamasShotsFired = 0;
	m_flFamasShoot = 0;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = FAMAS_DAMAGE;
	m_flBaseDamageBurst = FAMAS_DAMAGE_BURST;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CFamas::Precache()
{
	PRECACHE_MODEL("models/v_famas.mdl");
	PRECACHE_MODEL("models/w_famas.mdl");

	PRECACHE_SOUND("weapons/famas-1.wav");
	PRECACHE_SOUND("weapons/famas-2.wav");
	PRECACHE_SOUND("weapons/famas_clipout.wav");
	PRECACHE_SOUND("weapons/famas_clipin.wav");
	PRECACHE_SOUND("weapons/famas_boltpull.wav");
	PRECACHE_SOUND("weapons/famas_boltslap.wav");
	PRECACHE_SOUND("weapons/famas_forearm.wav");
	PRECACHE_SOUND("weapons/famas-burst.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireFamas = PRECACHE_EVENT(1, "events/famas.sc");
}

int CFamas::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = FAMAS_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 18;
	p->iId = m_iId = WEAPON_FAMAS;
	p->iFlags = 0;
	p->iWeight = FAMAS_WEIGHT;

	return 1;
}

BOOL CFamas::Deploy()
{
	m_iShotsFired = 0;
	m_iFamasShotsFired = 0;
	m_flFamasShoot = 0;
	m_flAccuracy = 0.2f;

	iShellOn = 1;

	return DefaultDeploy("models/v_famas.mdl", "models/p_famas.mdl", FAMAS_DRAW, "carbine", UseDecrement() != FALSE);
}

void CFamas::SecondaryAttack()
{
	if (m_iWeaponState & WPNSTATE_FAMAS_BURST_MODE)
	{
		ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#Switch_To_FullAuto");
		m_iWeaponState &= ~WPNSTATE_FAMAS_BURST_MODE;
	}
	else
	{
		ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#Switch_To_BurstFire");
		m_iWeaponState |= WPNSTATE_FAMAS_BURST_MODE;
	}

	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3f;
}

void CFamas::PrimaryAttack()
{
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = GetNextAttackDelay(0.15);
		return;
	}

	bool bFireBurst = (m_iWeaponState & WPNSTATE_FAMAS_BURST_MODE) == WPNSTATE_FAMAS_BURST_MODE;

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		FamasFire(0.030 + 0.3 * m_flAccuracy, 0.0825, FALSE, bFireBurst);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
	{
		FamasFire(0.030 + 0.07 * m_flAccuracy, 0.0825, FALSE, bFireBurst);
	}
	else
	{
		FamasFire(0.02 * m_flAccuracy, 0.0825, FALSE, bFireBurst);
	}
}

void CFamas::FamasFire(float flSpread, float flCycleTime, BOOL fUseAutoAim, BOOL bFireBurst)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	if (bFireBurst)
	{
		m_iFamasShotsFired = 0;
		flCycleTime = 0.55f;
	}
	else
	{
		flSpread += 0.01f;
	}

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = (m_iShotsFired * m_iShotsFired * m_iShotsFired / 215) + 0.3f;

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

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = bFireBurst ? m_flBaseDamageBurst : CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = bFireBurst ? FAMAS_DAMAGE_BURST : FAMAS_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 2, BULLET_PLAYER_556MM,
		flBaseDamage, FAMAS_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireFamas, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 10000000), int(m_pPlayer->pev->punchangle.y * 10000000), FALSE, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.1f;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(1.0, 0.45, 0.275, 0.05, 4.0, 2.5, 7);
	}
	else if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(1.25, 0.45, 0.22, 0.18, 5.5, 4.0, 5);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.575, 0.325, 0.2, 0.011, 3.25, 2.0, 8);
	}
	else
	{
		KickBack(0.625, 0.375, 0.25, 0.0125, 3.5, 2.25, 8);
	}

	if (bFireBurst)
	{
		m_iFamasShotsFired++;
		m_fBurstSpread = flSpread;
		m_flFamasShoot = gpGlobals->time + 0.05f;
	}
}

void CFamas::Reload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;

	if (DefaultReload(iMaxClip(), FAMAS_RELOAD, FAMAS_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		if (m_pPlayer->m_iFOV != DEFAULT_FOV)
		{
			SecondaryAttack();
		}

		m_flAccuracy = 0;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}

void CFamas::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;
		SendWeaponAnim(FAMAS_IDLE1, UseDecrement() != FALSE);
	}
}
