#include "precompiled.h"

#define AWP_MAX_SPEED		210
#define AWP_MAX_SPEED_ZOOM	150
#define AWP_RELOAD_TIME		2.5

enum awp_e
{
	AWP_IDLE,
	AWP_SHOOT,
	AWP_SHOOT2,
	AWP_SHOOT3,
	AWP_RELOAD,
	AWP_DRAW,
};

/* <23fdac> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_awp, CAWP);

/* <23fb10> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:52 */
void CAWP::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_AWP;
	SET_MODEL(ENT(pev), "models/w_awp.mdl");

	m_iDefaultAmmo = AWP_DEFAULT_GIVE;
	FallInit();
}

/* <23fa2c> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:64 */
void CAWP::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_awp.mdl");
	PRECACHE_MODEL("models/w_awp.mdl");

	PRECACHE_SOUND("weapons/awp1.wav");
	PRECACHE_SOUND("weapons/boltpull1.wav");
	PRECACHE_SOUND("weapons/boltup.wav");
	PRECACHE_SOUND("weapons/boltdown.wav");
	PRECACHE_SOUND("weapons/zoom.wav");
	PRECACHE_SOUND("weapons/awp_deploy.wav");
	PRECACHE_SOUND("weapons/awp_clipin.wav");
	PRECACHE_SOUND("weapons/awp_clipout.wav");

	m_iShell = PRECACHE_MODEL("models/rshell_big.mdl");
	m_iShellId = m_iShell;
	m_usFireAWP = PRECACHE_EVENT(1, "events/awp.sc");
}

/* <23fa53> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:83 */
int CAWP::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "338Magnum";
	p->iMaxAmmo1 = MAX_AMMO_338MAGNUM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AWP_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 2;
	p->iId = m_iId = WEAPON_AWP;
	p->iFlags = 0;
	p->iWeight = AWP_WEIGHT;

	return 1;
}

/* <23fc19> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:100 */
BOOL CAWP::__MAKE_VHOOK(Deploy)(void)
{
	if (DefaultDeploy("models/v_awp.mdl", "models/p_awp.mdl", AWP_DRAW, "rifle", UseDecrement() != FALSE))
	{
		m_pPlayer->m_flNextAttack = GetNextAttackDelay(1.45);
		m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack;

		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.0;

		return TRUE;
	}

	return FALSE;
}

/* <23faac> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:113 */
void CAWP::__MAKE_VHOOK(SecondaryAttack)(void)
{
	switch (m_pPlayer->m_iFOV)
	{
	case 90: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; break;
	case 40: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 10; break;
	default: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; break;
	}

	if (TheBots != NULL)
	{
		TheBots->OnEvent(EVENT_WEAPON_ZOOMED, m_pPlayer);
	}

	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(m_pPlayer->edict(), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);

	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

/* <23fd53> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:143 */
void CAWP::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		AWPFire(0.85, 1.45, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 140)
	{
		AWPFire(0.25, 1.45, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 10)
	{
		AWPFire(0.1, 1.45, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		AWPFire(0.0, 1.45, FALSE);
	}
	else
	{
		AWPFire(0.001, 1.45, FALSE);
	}
}

/* <23fe76> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:157 */
void CAWP::AWPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	if (m_pPlayer->pev->fov != DEFAULT_FOV)
	{
		m_pPlayer->m_bResumeZoom = true;
		m_pPlayer->m_iLastZoom = m_pPlayer->m_iFOV;

		// reset a fov
		m_pPlayer->m_iFOV = DEFAULT_FOV;
		m_pPlayer->pev->fov = DEFAULT_FOV;
	}
	else
	{
		flSpread += 0.08;
	}

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = GetNextAttackDelay(0.2);
		}

		if (TheBots != NULL)
		{
			TheBots->OnEvent(EVENT_WEAPON_FIRED_ON_EMPTY, m_pPlayer, 0);
		}

		return;
	}

	m_iClip--;

	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.55;
	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecDir = gpGlobals->v_forward;

	vecAiming = m_pPlayer->FireBullets3
	(
		vecSrc,
		vecDir,
		flSpread,
		8192.0,
		3,
		BULLET_PLAYER_338MAG,
		115,
		0.99,
		m_pPlayer->pev,
		true,			// TODO: why awp is have bPistol set true?
		m_pPlayer->random_seed
	);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL
	(
		flag,
		ENT(m_pPlayer->pev),
		m_usFireAWP,
		0,
		(float *)&g_vecZero,
		(float *)&g_vecZero,
		vecAiming.x,
		vecAiming.y,
		(int)(m_pPlayer->pev->punchangle.x * 100),
		(int)(m_pPlayer->pev->punchangle.x * 100),
		FALSE,
		FALSE
	);

	m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack;

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
	m_pPlayer->pev->punchangle.x -= 2;
}

/* <23fbc1> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:239 */
void CAWP::__MAKE_VHOOK(Reload)(void)
{
	int iResult;

	if (m_pPlayer->ammo_338mag <= 0)
	{
		return;
	}

	iResult = DefaultReload(AWP_MAX_CLIP, AWP_RELOAD, AWP_RELOAD_TIME);

	if (iResult)
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		if (m_pPlayer->pev->fov != DEFAULT_FOV)
		{
			m_pPlayer->m_iFOV = 10;
			m_pPlayer->pev->fov = 10;

			SecondaryAttack();
		}
	}
}

/* <23fb86> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:265 */
void CAWP::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase() && m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;
		SendWeaponAnim(AWP_IDLE, UseDecrement() != FALSE);
	}
}

/* <23fa86> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:283 */
float CAWP::__MAKE_VHOOK(GetMaxSpeed)(void)
{
	return m_pPlayer->m_iFOV == DEFAULT_FOV ? AWP_MAX_SPEED : AWP_MAX_SPEED_ZOOM;
}

#ifdef HOOK_GAMEDLL

void CAWP::Spawn(void)
{
	Spawn_();
}

void CAWP::Precache(void)
{
	Precache_();
}

int CAWP::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CAWP::Deploy(void)
{
	return Deploy_();
}

float CAWP::GetMaxSpeed(void)
{
	return GetMaxSpeed_();
}

void CAWP::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CAWP::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CAWP::Reload(void)
{
	Reload_();
}

void CAWP::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
