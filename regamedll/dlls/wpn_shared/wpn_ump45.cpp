#include "precompiled.h"

#define UMP45_MAX_SPEED			250

#define UMP45_DAMAGE			30
#define UMP45_RANGE_MODIFER		0.82

#define UMP45_RELOAD_TIME		3.5

enum ump45_e
{
	UMP45_IDLE1,
	UMP45_RELOAD,
	UMP45_DRAW,
	UMP45_SHOOT1,
	UMP45_SHOOT2,
	UMP45_SHOOT3
};

/* <2b5b26> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_ump45, CUMP45);

/* <2b58f0> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:52 */
void CUMP45::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_UMP45;
	SET_MODEL(edict(), "models/w_ump45.mdl");

	m_iDefaultAmmo = UMP45_DEFAULT_GIVE;
	m_flAccuracy = 0;
	m_bDelayFire = false;

	FallInit();
}

/* <2b586f> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:66 */
void CUMP45::__MAKE_VHOOK(Precache)(void)
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

/* <2b5896> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:82 */
int CUMP45::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
#ifdef REGAMEDLL_FIXES
	p->pszAmmo1 = "45acp";
#else
	p->pszAmmo1 = "45ACP";
#endif // REGAMEDLL_FIXES
	p->iMaxAmmo1 = MAX_AMMO_45ACP;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = UMP45_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 15;
	p->iId = m_iId = WEAPON_UMP45;
	p->iFlags = 0;
	p->iWeight = UMP45_WEIGHT;

	return 1;
}

/* <2b58c9> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:99 */
BOOL CUMP45::__MAKE_VHOOK(Deploy)(void)
{
	m_flAccuracy = 0;
	m_bDelayFire = false;
	iShellOn = 1;

	return DefaultDeploy("models/v_ump45.mdl", "models/p_ump45.mdl", UMP45_DRAW, "carbine", UseDecrement() != FALSE);
}

/* <2b5aec> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:108 */
void CUMP45::__MAKE_VHOOK(PrimaryAttack)(void)
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

/* <2b5bf0> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:116 */
void CUMP45::UMP45Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired) / 120) + 0.5;

	if (m_flAccuracy > 1)
		m_flAccuracy = 1;

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

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_45ACP,
		UMP45_DAMAGE, UMP45_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireUMP45, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		(int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

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

/* <2b59a1> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:200 */
void CUMP45::__MAKE_VHOOK(Reload)(void)
{
	if (m_pPlayer->ammo_45acp <= 0)
	{
		return;
	}

	if (DefaultReload(UMP45_MAX_CLIP, UMP45_RELOAD, UMP45_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0;
		m_iShotsFired = 0;
	}
}

/* <2b5966> ../cstrike/dlls/wpn_shared/wpn_ump45.cpp:214 */
void CUMP45::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(UMP45_IDLE1, UseDecrement() != FALSE);
}

#ifdef HOOK_GAMEDLL

void CUMP45::Spawn(void)
{
	Spawn_();
}

void CUMP45::Precache(void)
{
	Precache_();
}

int CUMP45::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CUMP45::Deploy(void)
{
	return Deploy_();
}

void CUMP45::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CUMP45::Reload(void)
{
	Reload_();
}

void CUMP45::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
