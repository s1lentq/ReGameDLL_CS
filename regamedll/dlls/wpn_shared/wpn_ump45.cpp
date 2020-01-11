#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_ump45, CUMP45, CCSUMP45)

void CUMP45::Spawn()
{
	Precache();

	m_iId = WEAPON_UMP45;
	SET_MODEL(edict(), "models/w_ump45.mdl");

	m_iDefaultAmmo = UMP45_DEFAULT_GIVE;
	m_flAccuracy = 0.0f;
	m_bDelayFire = false;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = UMP45_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CUMP45::Precache()
{
	PRECACHE_MODEL("models/v_ump45.mdl");
	PRECACHE_MODEL("models/w_ump45.mdl");

	PRECACHE_SOUND("weapons/ump45-1.wav");
	PRECACHE_SOUND("weapons/ump45_clipout.wav");
	PRECACHE_SOUND("weapons/ump45_clipin.wav");
	PRECACHE_SOUND("weapons/ump45_boltslap.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireUMP45 = PRECACHE_EVENT(1, "events/ump45.sc");
}

int CUMP45::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
#ifdef REGAMEDLL_FIXES
	p->pszAmmo1 = "45acp";
#else
	p->pszAmmo1 = "45ACP";
#endif
	p->iMaxAmmo1 = MAX_AMMO_45ACP;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = UMP45_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 15;
	p->iId = m_iId = WEAPON_UMP45;
	p->iFlags = 0;
	p->iWeight = UMP45_WEIGHT;

	return 1;
}

BOOL CUMP45::Deploy()
{
	m_flAccuracy = 0.0f;
	m_bDelayFire = false;
	iShellOn = 1;

	return DefaultDeploy("models/v_ump45.mdl", "models/p_ump45.mdl", UMP45_DRAW, "carbine", UseDecrement() != FALSE);
}

void CUMP45::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		UMP45Fire(0.24 * m_flAccuracy, 0.1, FALSE);
	}
	else
	{
		UMP45Fire(0.04 * m_flAccuracy, 0.1, FALSE);
	}
}

void CUMP45::UMP45Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired) / 210) + 0.5f;

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

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = UMP45_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_45ACP,
		flBaseDamage, UMP45_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireUMP45, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(0.125, 0.65, 0.55, 0.0475, 5.5, 4.0, 10);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(0.55, 0.3, 0.225, 0.03, 3.5, 2.5, 10);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.25, 0.175, 0.125, 0.02, 2.25, 1.25, 10);
	}
	else
	{
		KickBack(0.275, 0.2, 0.15, 0.0225, 2.5, 1.5, 10);
	}
}

void CUMP45::Reload()
{
	if (m_pPlayer->ammo_45acp <= 0)
		return;

	if (DefaultReload(iMaxClip(), UMP45_RELOAD, UMP45_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.0f;
		m_iShotsFired = 0;
	}
}

void CUMP45::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;
	SendWeaponAnim(UMP45_IDLE1, UseDecrement() != FALSE);
}
