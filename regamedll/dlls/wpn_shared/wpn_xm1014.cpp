#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_xm1014, CXM1014, CCSXM1014);

void CXM1014::__MAKE_VHOOK(Spawn)()
{
	Precache();

	m_iId = WEAPON_XM1014;
	SET_MODEL(edict(), "models/w_xm1014.mdl");

	m_iDefaultAmmo = XM1014_DEFAULT_GIVE;

	// get ready to fall
	FallInit();
}

void CXM1014::__MAKE_VHOOK(Precache)()
{
	PRECACHE_MODEL("models/v_xm1014.mdl");
	PRECACHE_MODEL("models/w_xm1014.mdl");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/shotgunshell.mdl");

	PRECACHE_SOUND("weapons/xm1014-1.wav");
	PRECACHE_SOUND("weapons/reload1.wav");
	PRECACHE_SOUND("weapons/reload3.wav");

	m_usFireXM1014 = PRECACHE_EVENT(1, "events/xm1014.sc");
}

int CXM1014::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "buckshot";
	p->iMaxAmmo1 = MAX_AMMO_BUCKSHOT;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = XM1014_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 12;
	p->iId = m_iId = WEAPON_XM1014;
	p->iFlags = 0;
	p->iWeight = XM1014_WEIGHT;

	return 1;
}

BOOL CXM1014::__MAKE_VHOOK(Deploy)()
{
	return DefaultDeploy("models/v_xm1014.mdl", "models/p_xm1014.mdl", XM1014_DRAW, "m249", UseDecrement() != FALSE);
}

void CXM1014::__MAKE_VHOOK(PrimaryAttack)()
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	// don't fire underwater
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = GetNextAttackDelay(0.15);
		return;
	}

	if (m_iClip <= 0)
	{
		Reload();
			
		if (!m_iClip)
		{
			PlayEmptySound();
		}

		if (TheBots != NULL)
		{
			TheBots->OnEvent(EVENT_WEAPON_FIRED_ON_EMPTY, m_pPlayer);
		}

		m_flNextPrimaryAttack = GetNextAttackDelay(1);
		return;
	}

	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
	m_iClip--;

	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	// player "shoot" animation
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

	m_pPlayer->FireBullets(6, vecSrc, vecAiming, XM1014_CONE_VECTOR, 3048, BULLET_PLAYER_BUCKSHOT, 0);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireXM1014, 0, (float *)&g_vecZero, (float *)&g_vecZero, m_vVecAiming.x, m_vVecAiming.y, 7,
		int(m_vVecAiming.x * 100), m_iClip == 0, FALSE);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		// HEV suit - indicate out of ammo condition
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	if (m_iClip != 0)
		m_flPumpTime = UTIL_WeaponTimeBase() + 0.125f;

	m_flNextPrimaryAttack = GetNextAttackDelay(0.25);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.25f;

	if (m_iClip != 0)
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.25f;
	else
		m_flTimeWeaponIdle = 0.75f;

	m_fInSpecialReload = 0;

	if (m_pPlayer->pev->flags & FL_ONGROUND)
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 3, 5);
	else
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 7, 10);
}

void CXM1014::__MAKE_VHOOK(Reload)()
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 || m_iClip == XM1014_MAX_CLIP)
		return;

	// don't reload until recoil is done
	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
		return;

	// check to see if we're ready to reload
	if (m_fInSpecialReload == 0)
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		SendWeaponAnim(XM1014_START_RELOAD, UseDecrement() != FALSE);

		m_fInSpecialReload = 1;
		m_flNextSecondaryAttack = m_flTimeWeaponIdle = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.55f;
		m_flNextPrimaryAttack = GetNextAttackDelay(0.55);
	}
	else if (m_fInSpecialReload == 1)
	{
		if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
			return;

		// was waiting for gun to move to side
		m_fInSpecialReload = 2;

		if (RANDOM_LONG(0, 1))
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, "weapons/reload1.wav", VOL_NORM, ATTN_NORM, 0, 85 + RANDOM_LONG(0, 31));
		else
			EMIT_SOUND_DYN(m_pPlayer->edict(), CHAN_ITEM, "weapons/reload3.wav", VOL_NORM, ATTN_NORM, 0, 85 + RANDOM_LONG(0, 31));

		SendWeaponAnim(XM1014_RELOAD, UseDecrement());

		m_flTimeWeaponIdle = m_flNextReload = UTIL_WeaponTimeBase() + 0.3f;
	}
	else
	{
		++m_iClip;

#ifdef REGAMEDLL_ADD
		if (refill_bpammo_weapons.value < 2.0f)
#endif
		{
			--m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType];
			--m_pPlayer->ammo_buckshot;
		}

		m_fInSpecialReload = 1;
	}
}

void CXM1014::__MAKE_VHOOK(WeaponIdle)()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES);

	if (m_flPumpTime && m_flPumpTime < UTIL_WeaponTimeBase())
	{
		m_flPumpTime = 0;
	}

	if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
	{
		if (m_iClip == 0 && m_fInSpecialReload == 0 && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			Reload();
		}
		else if (m_fInSpecialReload != 0)
		{
			if (m_iClip != XM1014_MAX_CLIP && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
			{
				Reload();
			}
			else
			{
				// reload debounce has timed out
				SendWeaponAnim(XM1014_PUMP, UseDecrement() != FALSE);

				m_fInSpecialReload = 0;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5f;
			}
		}
		else
		{
			SendWeaponAnim(XM1014_IDLE, UseDecrement() != FALSE);
		}
	}
}
