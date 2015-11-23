#include "precompiled.h"

#define SG550_MAX_SPEED			210
#define SG550_MAX_SPEED_ZOOM		150

#define SG550_DAMAGE			70
#define SG550_RANGE_MODIFER		0.98

#define SG550_RELOAD_TIME		3.35

enum sg550_e
{
	SG550_IDLE,
	SG550_SHOOT,
	SG550_SHOOT2,
	SG550_RELOAD,
	SG550_DRAW
};

/* <2a0f39> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:48 */
LINK_ENTITY_TO_CLASS(weapon_sg550, CSG550);

/* <2a0ce8> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:50 */
void CSG550::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_SG550;
	SET_MODEL(edict(), "models/w_sg550.mdl");

	m_iDefaultAmmo = SG550_DEFAULT_GIVE;
	m_flLastFire = 0;

	FallInit();
}

/* <2a0bdd> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:63 */
void CSG550::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_sg550.mdl");
	PRECACHE_MODEL("models/w_sg550.mdl");

	PRECACHE_SOUND("weapons/sg550-1.wav");
	PRECACHE_SOUND("weapons/sg550_boltpull.wav");
	PRECACHE_SOUND("weapons/sg550_clipin.wav");
	PRECACHE_SOUND("weapons/sg550_clipout.wav");
	PRECACHE_SOUND("weapons/zoom.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireSG550 = PRECACHE_EVENT(1, "events/sg550.sc");
}

/* <2a0c04> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:79 */
int CSG550::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = SG550_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 16;
	p->iId = m_iId = WEAPON_SG550;
	p->iFlags = 0;
	p->iWeight = SG550_WEIGHT;

	return 1;
}

/* <2a0cc1> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:96 */
BOOL CSG550::__MAKE_VHOOK(Deploy)(void)
{
	return DefaultDeploy("models/v_sg550.mdl", "models/p_sg550.mdl", SG550_DRAW, "rifle", UseDecrement() != FALSE);
}

/* <2a0c5d> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:101 */
void CSG550::__MAKE_VHOOK(SecondaryAttack)(void)
{
	switch (m_pPlayer->m_iFOV)
	{
	case 90: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; break;
	case 40: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 15; break;
#ifdef REGAMEDLL_FIXES
	default:
#else
	case 15:
#endif // REGAMEDLL_FIXES
		m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; break;
	}

	m_pPlayer->ResetMaxSpeed();

	if (TheBots != NULL)
	{
		TheBots->OnEvent(EVENT_WEAPON_ZOOMED, m_pPlayer);
	}

	EMIT_SOUND(m_pPlayer->edict(), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

/* <2a0eef> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:132 */
void CSG550::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		SG550Fire(0.45 * (1 - m_flAccuracy), 0.25, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		SG550Fire(0.15, 0.25, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		SG550Fire(0.04 * (1 - m_flAccuracy), 0.25, FALSE);
	}
	else
	{
		SG550Fire(0.05 * (1 - m_flAccuracy), 0.25, FALSE);
	}
}

/* <2a1003> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:144 */
void CSG550::SG550Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming, vecSrc, vecDir;
	int flag;

	if (m_pPlayer->pev->fov == DEFAULT_FOV)
	{
		flSpread += 0.025;
	}

	if (m_flLastFire)
	{
		m_flAccuracy = (gpGlobals->time - m_flLastFire) * 0.35 + 0.65;

		if (m_flAccuracy > 0.98)
		{
			m_flAccuracy = 0.98;
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
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

	vecDir = m_pPlayer->FireBullets3(vecSrc, vecAiming, flSpread, 8192, 2, BULLET_PLAYER_556MM, SG550_DAMAGE, SG550_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireSG550, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y,
		(int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.x * 100), 5, FALSE);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.8;

	m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomFloat(m_pPlayer->random_seed + 4, 0.75, 1.25) + m_pPlayer->pev->punchangle.x * 0.25;
	m_pPlayer->pev->punchangle.y += UTIL_SharedRandomFloat(m_pPlayer->random_seed + 5, -0.75, 0.75);
}

/* <2a0d98> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:227 */
void CSG550::__MAKE_VHOOK(Reload)(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
	{
		return;
	}

	if (DefaultReload(SG550_MAX_CLIP, SG550_RELOAD, SG550_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		if (m_pPlayer->pev->fov != DEFAULT_FOV)
		{
			m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 15;
			SecondaryAttack();
		}
	}
}

/* <2a0d5e> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:248 */
void CSG550::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();

	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
	{
		return;
	}

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60.0;
		SendWeaponAnim(SG550_IDLE, UseDecrement() != FALSE);
	}
}

/* <2a0c37> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:265 */
float CSG550::__MAKE_VHOOK(GetMaxSpeed)(void)
{
	return (m_pPlayer->m_iFOV == DEFAULT_FOV) ? SG550_MAX_SPEED : SG550_MAX_SPEED_ZOOM;
}

#ifdef HOOK_GAMEDLL

void CSG550::Spawn(void)
{
	Spawn_();
}

void CSG550::Precache(void)
{
	Precache_();
}

int CSG550::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CSG550::Deploy(void)
{
	return Deploy_();
}

float CSG550::GetMaxSpeed(void)
{
	return GetMaxSpeed_();
}

void CSG550::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CSG550::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CSG550::Reload(void)
{
	Reload_();
}

void CSG550::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
