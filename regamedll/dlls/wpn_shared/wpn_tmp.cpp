#include "precompiled.h"

LINK_ENTITY_TO_CLASS(weapon_tmp, CTMP, CCSTMP)

void CTMP::Spawn()
{
	Precache();

	m_iId = WEAPON_TMP;
	SET_MODEL(edict(), "models/w_tmp.mdl");

	m_iDefaultAmmo = TMP_DEFAULT_GIVE;
	m_flAccuracy = 0.2f;
	m_iShotsFired = 0;
	m_bDelayFire = false;

#ifdef REGAMEDLL_API
	CSPlayerWeapon()->m_flBaseDamage = TMP_DAMAGE;
#endif

	// Get ready to fall down
	FallInit();

	// extend
	CBasePlayerWeapon::Spawn();
}

void CTMP::Precache()
{
	PRECACHE_MODEL("models/v_tmp.mdl");
	PRECACHE_MODEL("models/w_tmp.mdl");

	PRECACHE_SOUND("weapons/tmp-1.wav");
	PRECACHE_SOUND("weapons/tmp-2.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireTMP = PRECACHE_EVENT(1, "events/tmp.sc");
}

int CTMP::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = nullptr;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = TMP_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 11;
	p->iId = m_iId = WEAPON_TMP;
	p->iFlags = 0;
	p->iWeight = TMP_WEIGHT;

	return 1;
}

BOOL CTMP::Deploy()
{
	m_flAccuracy = 0.2f;
	m_iShotsFired = 0;
	m_bDelayFire = false;
	iShellOn = 1;

	return DefaultDeploy("models/v_tmp.mdl", "models/p_tmp.mdl", TMP_DRAW, "onehanded", UseDecrement() != FALSE);
}

void CTMP::PrimaryAttack()
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		TMPFire(0.25 * m_flAccuracy, 0.07, FALSE);
	}
	else
	{
		TMPFire(0.03 * m_flAccuracy, 0.07, FALSE);
	}
}

void CTMP::TMPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.55f;

	if (m_flAccuracy > 1.4f)
		m_flAccuracy = 1.4f;

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
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef REGAMEDLL_API
	float flBaseDamage = CSPlayerWeapon()->m_flBaseDamage;
#else
	float flBaseDamage = TMP_DAMAGE;
#endif
	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_9MM,
		flBaseDamage, TMP_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireTMP, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		int(m_pPlayer->pev->punchangle.x * 100), int(m_pPlayer->pev->punchangle.y * 100), 5, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", SUIT_SENTENCE, SUIT_REPEAT_OK);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0f;

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(1.1, 0.5, 0.35, 0.045, 4.5, 3.5, 6);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(0.8, 0.4, 0.2, 0.03, 3.0, 2.5, 7);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.7, 0.35, 0.125, 0.025, 2.5, 2.0, 10);
	}
	else
	{
		KickBack(0.725, 0.375, 0.15, 0.025, 2.75, 2.25, 9);
	}
}

void CTMP::Reload()
{
#ifdef REGAMEDLL_FIXES
	// to prevent reload if not enough ammo
	if (m_pPlayer->ammo_9mm <= 0)
		return;
#endif

	if (DefaultReload(iMaxClip(), TMP_RELOAD, TMP_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.2f;
		m_iShotsFired = 0;
	}
}

void CTMP::WeaponIdle()
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0f;
	SendWeaponAnim(TMP_IDLE1, UseDecrement() != FALSE);
}
