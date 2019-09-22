#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_mac10, CMAC10, CCSMAC10)

void CMAC10::Spawn()
{
	Precache();

	m_iId = WEAPON_MAC10;
	SET_MODEL(edict(), "models/w_mac10.mdl");

	m_iDefaultAmmo = MAC10_DEFAULT_GIVE;
	m_flAccuracy = 0.15f;
	m_bDelayFire = false;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = MAC10_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CMAC10::Precache()
{
	PRECACHE_MODEL("models/v_mac10.mdl");
	PRECACHE_MODEL("models/w_mac10.mdl");

	PRECACHE_SOUND("weapons/mac10-1.wav");
	PRECACHE_SOUND("weapons/mac10_clipout.wav");
	PRECACHE_SOUND("weapons/mac10_clipin.wav");
	PRECACHE_SOUND("weapons/mac10_boltpull.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireMAC10 = PRECACHE_EVENT(1, "events/mac10.sc");
}

int CMAC10::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "45acp";
	p->iMaxAmmo1 = MAX_AMMO_45ACP;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = MAC10_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 13;
	p->iId = m_iId = WEAPON_MAC10;
	p->iFlags = 0;
	p->iWeight = MAC10_WEIGHT;

	return 1;
}

BOOL CMAC10::Deploy()
{
	m_flAccuracy = 0.15f;
	iShellOn = 1;
	m_bDelayFire = false;

	return DefaultDeploy("models/v_mac10.mdl", "models/p_mac10.mdl", MAC10_DRAW, "onehanded", UseDecrement() != FALSE);
}

void CMAC10::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		MAC10Fire(0.375 * m_flAccuracy, 0.07, FALSE);
	}
	else
	{
		MAC10Fire(0.03 * m_flAccuracy, 0.07, FALSE);
	}
}

void CMAC10::MAC10Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.6f;

	if (m_flAccuracy > 1.65f)
		m_flAccuracy = 1.65f;

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
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = MAC10_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_45ACP,
		flBaseDamage, MAC10_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireMAC10, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(1.3, 0.55, 0.4, 0.05, 4.75, 3.75, 5);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(0.9, 0.45, 0.25, 0.035, 3.5, 2.75, 7);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.75, 0.4, 0.175, 0.03, 2.75, 2.5, 10);
	}
	else
	{
		KickBack(0.775, 0.425, 0.2, 0.03, 3.0, 2.75, 9);
	}
}

void CMAC10::Reload()
{
	if (m_pPlayer->ammo_45acp <= 0)
		return;

	if (DefaultReload(iMaxClip(), MAC10_RELOAD, MAC10_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0;
		m_iShotsFired = 0;
	}
}

void CMAC10::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;
	SendWeaponAnim(MAC10_IDLE1, UseDecrement() != FALSE);
}
