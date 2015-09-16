#include "precompiled.h"

#define P90_MAX_SPEED		245
#define P90_RELOAD_TIME		3.4

enum p90_e
{
	P90_IDLE1,
	P90_RELOAD,
	P90_DRAW,
	P90_SHOOT1,
	P90_SHOOT2,
	P90_SHOOT3
};

/* <29657d> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:49 */
LINK_ENTITY_TO_CLASS(weapon_p90, CP90);

/* <296337> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:51 */
void CP90::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_P90;
	SET_MODEL(edict(), "models/w_p90.mdl");

	m_iDefaultAmmo = P90_DEFAULT_GIVE;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	m_bDelayFire = false;

	FallInit();
}

/* <2962b6> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:66 */
void CP90::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_p90.mdl");
	PRECACHE_MODEL("models/w_p90.mdl");

	PRECACHE_SOUND("weapons/p90-1.wav");
	PRECACHE_SOUND("weapons/p90_clipout.wav");
	PRECACHE_SOUND("weapons/p90_clipin.wav");
	PRECACHE_SOUND("weapons/p90_boltpull.wav");
	PRECACHE_SOUND("weapons/p90_cliprelease.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireP90 = PRECACHE_EVENT(1, "events/p90.sc");
}

/* <2962dd> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:83 */
int CP90::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "57mm";
	p->iMaxAmmo1 = MAX_AMMO_57MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = P90_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 8;

	m_iId = WEAPON_P90;
	p->iId = WEAPON_P90;

	p->iFlags = 0;
	p->iWeight = P90_WEIGHT;

	return 1;
}

/* <296310> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:100 */
BOOL CP90::__MAKE_VHOOK(Deploy)(void)
{
	m_iShotsFired = 0;
	m_bDelayFire = false;
	m_flAccuracy = 0.2;

	iShellOn = 1;

	return DefaultDeploy("models/v_p90.mdl", "models/p_p90.mdl", P90_DRAW, "carbine", UseDecrement() != FALSE);
}

/* <296533> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:110 */
void CP90::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		P90Fire(0.3 * m_flAccuracy, 0.066, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 170)
	{
		P90Fire(0.115 * m_flAccuracy, 0.066, FALSE);
	}
	else
	{
		P90Fire(0.045 * m_flAccuracy, 0.066, FALSE);
	}
}

/* <296647> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:120 */
void CP90::P90Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	Vector vecAiming;
	Vector vecSrc;
	Vector vecDir;
	int flag;

	m_bDelayFire = true;
	m_iShotsFired++;

	m_flAccuracy = (m_iShotsFired * m_iShotsFired / 175) + 0.45;

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

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecDir = gpGlobals->v_forward;

	vecAiming = m_pPlayer->FireBullets3
	(
		vecSrc,
		vecDir,
		flSpread,
		8192,
		1,
		BULLET_PLAYER_57MM,
		21,
		0.885,
		m_pPlayer->pev,
		false,
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
		m_pPlayer->edict(),
		m_usFireP90,
		0,
		(float *)&g_vecZero,
		(float *)&g_vecZero,
		vecAiming.x,
		vecAiming.y,
		(int)(m_pPlayer->pev->punchangle.x * 100),
		(int)(m_pPlayer->pev->punchangle.y * 100),
		5,
		FALSE
	);

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = WEAPON_TIMEBASED + 2.0;

	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		KickBack(0.9, 0.45, 0.35, 0.04, 5.25, 3.5, 4);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		KickBack(0.45, 0.3, 0.2, 0.0275, 4.0, 2.25, 7);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		KickBack(0.275, 0.2, 0.125, 0.02, 3.0, 1.0, 9);
	}
	else
	{
		KickBack(0.3, 0.225, 0.125, 0.02, 3.25, 1.25, 8);
	}
}

/* <2963e8> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:202 */
void CP90::__MAKE_VHOOK(Reload)(void)
{
	if (m_pPlayer->ammo_57mm <= 0)
	{
		return;
	}

	if (DefaultReload(P90_MAX_CLIP, P90_RELOAD, P90_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);

		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
	}
}

/* <2963ad> ../cstrike/dlls/wpn_shared/wpn_p90.cpp:216 */
void CP90::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > WEAPON_TIMEBASED)
	{
		return;
	}

	m_flTimeWeaponIdle = WEAPON_TIMEBASED + 20.0;
	SendWeaponAnim(P90_IDLE1, UseDecrement() != FALSE);
}

/* <29626a> ../cstrike/dlls/weapons.h:1052 */
float CP90::__MAKE_VHOOK(GetMaxSpeed)(void)
{
	return P90_MAX_SPEED;
}

#ifdef HOOK_GAMEDLL

void CP90::Spawn(void)
{
	Spawn_();
}

void CP90::Precache(void)
{
	Precache_();
}

int CP90::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CP90::Deploy(void)
{
	return Deploy_();
}

void CP90::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CP90::Reload(void)
{
	Reload_();
}

void CP90::WeaponIdle(void)
{
	WeaponIdle_();
}

float CP90::GetMaxSpeed(void)
{
	return GetMaxSpeed_();
}

#endif // HOOK_GAMEDLL
