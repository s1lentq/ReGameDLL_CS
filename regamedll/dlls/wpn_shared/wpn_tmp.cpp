#include "precompiled.h"

#define TMP_MAX_SPEED			250

#define TMP_DAMAGE			20
#define TMP_RANGE_MODIFER		0.85

#define TMP_RELOAD_TIME			2.12

enum tmp_e
{
	TMP_IDLE1,
	TMP_RELOAD,
	TMP_DRAW,
	TMP_SHOOT1,
	TMP_SHOOT2,
	TMP_SHOOT3
};

/* <2b06f0> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_tmp, CTMP);

/* <2b04ba> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:52 */
void CTMP::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_TMP;
	SET_MODEL(edict(), "models/w_tmp.mdl");

	m_iDefaultAmmo = TMP_DEFAULT_GIVE;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	m_bDelayFire = false;

	FallInit();
}

/* <2b0439> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:67 */
void CTMP::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_tmp.mdl");
	PRECACHE_MODEL("models/w_tmp.mdl");

	PRECACHE_SOUND("weapons/tmp-1.wav");
	PRECACHE_SOUND("weapons/tmp-2.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireTMP = PRECACHE_EVENT(1, "events/tmp.sc");
}

/* <2b0460> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:81 */
int CTMP::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = TMP_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 11;
	p->iId = m_iId = WEAPON_TMP;
	p->iFlags = 0;
	p->iWeight = TMP_WEIGHT;

	return 1;
}

/* <2b0493> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:98 */
BOOL CTMP::__MAKE_VHOOK(Deploy)(void)
{
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	m_bDelayFire = false;
	iShellOn = 1;

	return DefaultDeploy("models/v_tmp.mdl", "models/p_tmp.mdl", TMP_DRAW, "onehanded", UseDecrement() != FALSE);
}

/* <2b06b6> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:108 */
void CTMP::__MAKE_VHOOK(PrimaryAttack)(void)
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

/* <2b07ba> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:116 */
void CTMP::TMPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.55;

	if (m_flAccuracy > 1.4)
		m_flAccuracy = 1.4;

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
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_9MM,
		TMP_DAMAGE, TMP_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireTMP, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		(int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), 5, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

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

/* <2b056b> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:197 */
void CTMP::__MAKE_VHOOK(Reload)(void)
{
#ifdef REGAMEDLL_FIXES
	// to prevent reload if not enough ammo
	if (m_pPlayer->ammo_9mm <= 0)
	{
		return;
	}
#endif // REGAMEDLL_FIXES

	if (DefaultReload(TMP_MAX_CLIP, TMP_RELOAD, TMP_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
	}
}

/* <2b0530> ../cstrike/dlls/wpn_shared/wpn_tmp.cpp:211 */
void CTMP::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(TMP_IDLE1, UseDecrement() != FALSE);
}

#ifdef HOOK_GAMEDLL

void CTMP::Spawn(void)
{
	Spawn_();
}

void CTMP::Precache(void)
{
	Precache_();
}

int CTMP::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CTMP::Deploy(void)
{
	return Deploy_();
}

void CTMP::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CTMP::Reload(void)
{
	Reload_();
}

void CTMP::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
