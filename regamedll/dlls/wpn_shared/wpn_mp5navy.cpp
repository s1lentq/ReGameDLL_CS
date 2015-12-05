#include "precompiled.h"

#define MP5N_MAX_SPEED			250

#define MP5N_DAMAGE			26
#define MP5N_RANGE_MODIFER		0.84

#define MP5N_RELOAD_TIME		2.63

enum mp5n_e
{
	MP5N_IDLE1,
	MP5N_RELOAD,
	MP5N_DRAW,
	MP5N_SHOOT1,
	MP5N_SHOOT2,
	MP5N_SHOOT3
};

/* <28bbf6> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_mp5navy, CMP5N);

/* <28b9c0> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:52 */
void CMP5N::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_MP5N;
	SET_MODEL(edict(), "models/w_mp5.mdl");

	m_iDefaultAmmo = MP5NAVY_DEFAULT_GIVE;
	m_flAccuracy = 0;
	m_bDelayFire = false;

	FallInit();
}

/* <28b93f> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:66 */
void CMP5N::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_mp5.mdl");
	PRECACHE_MODEL("models/w_mp5.mdl");

	PRECACHE_SOUND("weapons/mp5-1.wav");
	PRECACHE_SOUND("weapons/mp5-2.wav");
	PRECACHE_SOUND("weapons/mp5_clipout.wav");
	PRECACHE_SOUND("weapons/mp5_clipin.wav");
	PRECACHE_SOUND("weapons/mp5_slideback.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireMP5N = PRECACHE_EVENT(1, "events/mp5n.sc");
}

/* <28b966> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:83 */
int CMP5N::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = MP5N_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 7;
	p->iId = m_iId = WEAPON_MP5N;
	p->iFlags = 0;
	p->iWeight = MP5NAVY_WEIGHT;

	return 1;
}

/* <28b999> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:100 */
BOOL CMP5N::__MAKE_VHOOK(Deploy)(void)
{
	m_flAccuracy = 0;
	m_bDelayFire = false;
	iShellOn = 1;

	return DefaultDeploy("models/v_mp5.mdl", "models/p_mp5.mdl", MP5N_DRAW, "mp5", UseDecrement() != FALSE);
}

/* <28bbbc> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:109 */
void CMP5N::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		MP5NFire(0.2 * m_flAccuracy, 0.075, FALSE);
	}
	else
	{
		MP5NFire(0.04 * m_flAccuracy, 0.075, FALSE);
	}
}

/* <28bcc0> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:117 */
void CMP5N::MP5NFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = ((m_iShotsFired * m_iShotsFired) / 220.1) + 0.45;

	if (m_flAccuracy > 0.75)
		m_flAccuracy = 0.75;

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

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 1, BULLET_PLAYER_9MM,
		MP5N_DAMAGE, MP5N_RANGE_MODIFER, m_pPlayer->pev, false, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireMP5N, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
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
		KickBack(0.9, 0.475, 0.35, 0.0425, 5.0, 3.0, 6);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(0.5, 0.275, 0.2, 0.03, 3.0, 2.0, 10);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.225, 0.15, 0.1, 0.015, 2.0, 1.0, 10);
	}
	else
	{
		KickBack(0.25, 0.175, 0.125, 0.02, 2.25, 1.25, 10);
	}
}

/* <28ba71> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:201 */
void CMP5N::__MAKE_VHOOK(Reload)(void)
{
	if (m_pPlayer->ammo_9mm <= 0)
	{
		return;
	}

	if (DefaultReload(MP5N_MAX_CLIP, MP5N_RELOAD, MP5N_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0;
		m_iShotsFired = 0;
	}
}

/* <28ba36> ../cstrike/dlls/wpn_shared/wpn_mp5navy.cpp:215 */
void CMP5N::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(MP5N_IDLE1, UseDecrement() != FALSE);
}

#ifdef HOOK_GAMEDLL

void CMP5N::Spawn(void)
{
	Spawn_();
}

void CMP5N::Precache(void)
{
	Precache_();
}

int CMP5N::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CMP5N::Deploy(void)
{
	return Deploy_();
}

void CMP5N::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CMP5N::Reload(void)
{
	Reload_();
}

void CMP5N::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
