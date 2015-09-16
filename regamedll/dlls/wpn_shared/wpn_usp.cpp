#include "precompiled.h"

#define USP_MAX_SPEED		250
#define USP_RELOAD_TIME		2.7

enum usp_e
{
	USP_IDLE,
	USP_SHOOT1,
	USP_SHOOT2,
	USP_SHOOT3,
	USP_SHOOT_EMPTY,
	USP_RELOAD,
	USP_DRAW,
	USP_ATTACH_SILENCER,
	USP_UNSIL_IDLE,
	USP_UNSIL_SHOOT1,
	USP_UNSIL_SHOOT2,
	USP_UNSIL_SHOOT3,
	USP_UNSIL_SHOOT_EMPTY,
	USP_UNSIL_RELOAD,
	USP_UNSIL_DRAW,
	USP_DETACH_SILENCER
};

enum usp_shield_e
{
	USP_SHIELD_IDLE,
	USP_SHIELD_SHOOT1,
	USP_SHIELD_SHOOT2,
	USP_SHIELD_SHOOT_EMPTY,
	USP_SHIELD_RELOAD,
	USP_SHIELD_DRAW,
	USP_SHIELD_UP_IDLE,
	USP_SHIELD_UP,
	USP_SHIELD_DOWN
};

/* <2bb045> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:68 */
LINK_ENTITY_TO_CLASS(weapon_usp, CUSP);

/* <2bad55> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:70 */
void CUSP::__MAKE_VHOOK(Spawn)(void)
{
	Precache();

	m_iId = WEAPON_USP;
	SET_MODEL(ENT(pev), "models/w_usp.mdl");

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_iDefaultAmmo = USP_DEFAULT_GIVE;
	m_flAccuracy = 0.92f;

	FallInit();
}

void CUSP::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_usp.mdl");
	PRECACHE_MODEL("models/w_usp.mdl");
	PRECACHE_MODEL("models/shield/v_shield_usp.mdl");

	PRECACHE_SOUND("weapons/usp1.wav");
	PRECACHE_SOUND("weapons/usp2.wav");
	PRECACHE_SOUND("weapons/usp_unsil-1.wav");
	PRECACHE_SOUND("weapons/usp_clipout.wav");
	PRECACHE_SOUND("weapons/usp_clipin.wav");
	PRECACHE_SOUND("weapons/usp_silencer_on.wav");
	PRECACHE_SOUND("weapons/usp_silencer_off.wav");
	PRECACHE_SOUND("weapons/usp_sliderelease.wav");
	PRECACHE_SOUND("weapons/usp_slideback.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireUSP = PRECACHE_EVENT(1, "events/usp.sc");
}

/* <2bacfb> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:107 */
int CUSP::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszAmmo1 = "45ACP";
	p->iMaxAmmo1 = MAX_AMMO_45ACP;
	p->pszName = STRING(pev->classname);
	p->pszAmmo2 = 0;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = USP_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 4;
	p->iFlags = 0;

	m_iId = WEAPON_USP;
	p->iId = WEAPON_USP;

	p->iWeight = USP_WEIGHT;

	return 1;
}

/* <2bad2e> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:124 */
BOOL CUSP::__MAKE_VHOOK(Deploy)(void)
{
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_flAccuracy = 0.92f;
	m_fMaxSpeed = USP_MAX_SPEED;
	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
	{
		m_iWeaponState &= ~WPNSTATE_USP_SILENCED;
		return DefaultDeploy("models/shield/v_shield_usp.mdl", "models/shield/p_shield_usp.mdl", USP_SHIELD_DRAW, "shieldgun", UseDecrement());
	}
	else if (m_iWeaponState & WPNSTATE_USP_SILENCED)
	{
		return DefaultDeploy("models/v_usp.mdl", "models/p_usp.mdl", USP_DRAW, "onehanded", UseDecrement());
	}

	return DefaultDeploy("models/v_usp.mdl", "models/p_usp.mdl", USP_UNSIL_DRAW, "onehanded", UseDecrement());
}

/* <2bae77> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:147 */
void CUSP::__MAKE_VHOOK(SecondaryAttack)(void)
{
	if (ShieldSecondaryFire(USP_SHIELD_UP, USP_SHIELD_DOWN))
	{
		return;
	}

	if (m_iWeaponState & WPNSTATE_USP_SILENCED)
	{
		m_iWeaponState &= ~WPNSTATE_USP_SILENCED;

		SendWeaponAnim(USP_DETACH_SILENCER, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "onehanded");
	}
	else
	{
		m_iWeaponState |= WPNSTATE_USP_SILENCED;

		SendWeaponAnim(USP_ATTACH_SILENCER, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "onehanded");
	}
	
	m_flNextSecondaryAttack = WEAPON_TIMEBASED + 3.0;
	m_flTimeWeaponIdle = WEAPON_TIMEBASED + 3.0;

	m_flNextPrimaryAttack = GetNextAttackDelay(3.0);
}

/* <2bb000> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:173 */
void CUSP::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (m_iWeaponState & WPNSTATE_USP_SILENCED)
	{
		if (!(m_pPlayer->pev->flags & FL_ONGROUND))
		{
			USPFire(1.3 * (1 - m_flAccuracy), 0.225, FALSE);
		}
		else if (m_pPlayer->pev->velocity.Length2D() > 0)
		{
			USPFire(0.25 * (1 - m_flAccuracy), 0.225, FALSE);
		}
		else if (m_pPlayer->pev->flags & FL_DUCKING)
		{
			USPFire(0.125 * (1 - m_flAccuracy), 0.225, FALSE);
		}
		else
		{
			USPFire(0.15 * (1 - m_flAccuracy), 0.225, FALSE);
		}
	}
	else
	{
		if (!(m_pPlayer->pev->flags & FL_ONGROUND))
		{
			USPFire(1.2 * (1 - m_flAccuracy), 0.225, FALSE);
		}
		else if (m_pPlayer->pev->velocity.Length2D() > 0)
		{
			USPFire(0.225 * (1 - m_flAccuracy), 0.225, FALSE);
		}
		else if (m_pPlayer->pev->flags & FL_DUCKING)
		{
			USPFire(0.08 * (1 - m_flAccuracy), 0.225, FALSE);
		}
		else
		{
			USPFire(0.1 * (1 - m_flAccuracy), 0.225, FALSE);
		}
	}
}

/* <2bb10f> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:200 */
void CUSP::USPFire(float flSpread, float flCycleTime, BOOL fUseSemi)
{
	int flag;
	int iDamage;
	Vector vecAiming;
	Vector vecSrc;
	Vector vecDir;

	flCycleTime -= 0.075;

	if (++m_iShotsFired > 1)
	{
		return;
	}

	if (m_flLastFire != 0.0)
	{
		m_flAccuracy -= (0.3 - (gpGlobals->time - m_flLastFire)) * 0.275;

		if (m_flAccuracy > 0.92)
		{
			m_flAccuracy = 0.92;
		}
		else if (m_flAccuracy < 0.6)
		{
			m_flAccuracy = 0.6;
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

	m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack;

	m_iClip--;
	SetPlayerShieldAnim();

	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
	m_pPlayer->m_iWeaponVolume = 2048;
	m_pPlayer->m_iWeaponFlash = 128;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	if (!(m_iWeaponState & WPNSTATE_USP_SILENCED))
	{
		m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	}

	vecSrc = m_pPlayer->GetGunPosition();
	vecDir = gpGlobals->v_forward;

	iDamage = (m_iWeaponState & WPNSTATE_USP_SILENCED) ? 30 : 34;
	
	vecAiming = m_pPlayer->FireBullets3
	(
		vecSrc,
		vecDir,
		flSpread,
		4096.0,
		1,
		BULLET_PLAYER_45ACP,
		iDamage,
		0.79,
		m_pPlayer->pev,
		true,
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
		m_usFireUSP,
		0,
		(float *)&g_vecZero,
		(float *)&g_vecZero,
		vecAiming.x,
		vecAiming.y,
		(int)(m_pPlayer->pev->punchangle.x * 100),
		0,
		m_iClip == 0,
		(m_iWeaponState & WPNSTATE_USP_SILENCED)
	);

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, FALSE);
	}
	
	m_flTimeWeaponIdle = WEAPON_TIMEBASED + 2;
	m_pPlayer->pev->punchangle.x -= 2;
	ResetPlayerShieldAnim();
}

/* <2bae19> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:297 */
void CUSP::__MAKE_VHOOK(Reload)(void)
{
	if (m_pPlayer->ammo_45acp <= 0)
	{
		return;
	}

	int iResult;
	if (m_pPlayer->HasShield())
	{
		iResult = DefaultReload(USP_MAX_CLIP, USP_SHIELD_RELOAD, USP_RELOAD_TIME);
	}
	else if (m_iWeaponState & WPNSTATE_USP_SILENCED)
	{
		iResult = DefaultReload(USP_MAX_CLIP, USP_RELOAD, USP_RELOAD_TIME);
	}
	else
		iResult = DefaultReload(USP_MAX_CLIP, USP_UNSIL_RELOAD, USP_RELOAD_TIME);

	if (iResult)
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.92f;
	}
}

/* <2b9c2a> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:318 */
void CUSP::__MAKE_VHOOK(WeaponIdle)(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);
	
	if (m_flTimeWeaponIdle > 0)
	{
		return;
	}

	if (m_pPlayer->HasShield())
	{
		m_flTimeWeaponIdle = WEAPON_TIMEBASED + 20.0;

		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		{
			SendWeaponAnim(USP_DRAW, UseDecrement());
		}
	}
	else if (m_iClip)
	{
		int iAnim = (~m_iWeaponState & WPNSTATE_USP_SILENCED) ? USP_UNSIL_IDLE: USP_IDLE;

		m_flTimeWeaponIdle = WEAPON_TIMEBASED + 60.0;
		SendWeaponAnim(iAnim, UseDecrement());
	}
}

#ifdef HOOK_GAMEDLL

void CUSP::Spawn(void)
{
	Spawn_();
}

void CUSP::Precache(void)
{
	Precache_();
}

int CUSP::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CUSP::Deploy(void)
{
	return Deploy_();
}

void CUSP::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CUSP::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CUSP::Reload(void)
{
	Reload_();
}

void CUSP::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
