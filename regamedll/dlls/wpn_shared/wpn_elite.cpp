#include "precompiled.h"

/* <25137f> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:52 */
LINK_ENTITY_TO_CLASS(weapon_elite, CELITE);

/* <251034> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:54 */
void CELITE::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_ELITE;
	SET_MODEL(edict(), "models/w_elite.mdl");

	m_iDefaultAmmo = ELITE_DEFAULT_GIVE;
	m_flAccuracy = 0.88;

	FallInit();
}

/* <250fb3> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:67 */
void CELITE::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_elite.mdl");
	PRECACHE_MODEL("models/w_elite.mdl");

	PRECACHE_SOUND("weapons/elite_fire.wav");
	PRECACHE_SOUND("weapons/elite_reloadstart.wav");
	PRECACHE_SOUND("weapons/elite_leftclipin.wav");
	PRECACHE_SOUND("weapons/elite_clipout.wav");
	PRECACHE_SOUND("weapons/elite_sliderelease.wav");
	PRECACHE_SOUND("weapons/elite_rightclipin.wav");
	PRECACHE_SOUND("weapons/elite_deploy.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");

	m_usFireELITE_LEFT = PRECACHE_EVENT(1, "events/elite_left.sc");
	m_usFireELITE_RIGHT = PRECACHE_EVENT(1, "events/elite_right.sc");
}

/* <250fda> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:86 */
int CELITE::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = ELITE_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 5;
	p->iId = m_iId = WEAPON_ELITE;
	p->iFlags = 0;
	p->iWeight = ELITE_WEIGHT;

	return 1;
}

/* <25100d> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:103 */
BOOL CELITE::__MAKE_VHOOK(Deploy)(void)
{
	m_flAccuracy = 0.88;

	if (!(m_iClip & 1))
	{
		m_iWeaponState |= WPNSTATE_ELITE_LEFT;
	}

	return DefaultDeploy("models/v_elite.mdl", "models/p_elite.mdl", ELITE_DRAW, "dualpistols", UseDecrement() != FALSE);
}

/* <251335> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:114 */
void CELITE::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (!(m_pPlayer->pev->flags & FL_ONGROUND))
	{
		ELITEFire(1.3 * (1 - m_flAccuracy), 0.2, FALSE);
	}
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
	{
		ELITEFire(0.175 * (1 - m_flAccuracy), 0.2, FALSE);
	}
	else if (m_pPlayer->pev->flags & FL_DUCKING)
	{
		ELITEFire(0.08 * (1 - m_flAccuracy), 0.2, FALSE);
	}
	else
	{
		ELITEFire(0.1 * (1 - m_flAccuracy), 0.2, FALSE);
	}
}

/* <251449> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:126 */
void CELITE::ELITEFire(float flSpread, float flCycleTime, BOOL fUseSemi)
{
	float flTimeDiff;
	int flag;
	Vector vecAiming;
	Vector vecSrc;
	Vector vecDir;

#ifdef REGAMEDLL_FIXES
	flCycleTime -= 0.078;
#else
	flCycleTime -= 0.125;
#endif // REGAMEDLL_FIXES

	m_iShotsFired++;

	if (m_iShotsFired > 1)
	{
		return;
	}

	flTimeDiff = gpGlobals->time - m_flLastFire;

	if (m_flLastFire)
	{
		m_flAccuracy -= (0.325 - flTimeDiff) * 0.275;

		if (m_flAccuracy > 0.88)
		{
			m_flAccuracy = 0.88;
		}
		else if (m_flAccuracy < 0.55)
		{
			m_flAccuracy = 0.55;
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

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = GetNextAttackDelay(flCycleTime);
	m_iClip--;

	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;

	vecSrc = m_pPlayer->GetGunPosition();
	vecAiming = gpGlobals->v_forward;

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif // CLIENT_WEAPONS

	if (m_iWeaponState & WPNSTATE_ELITE_LEFT)
	{
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		m_iWeaponState &= ~WPNSTATE_ELITE_LEFT;

		vecDir = m_pPlayer->FireBullets3(vecSrc - gpGlobals->v_right * 5, vecAiming, flSpread,
			8192, BULLET_PLAYER_9MM, 1, ELITE_DAMAGE, ELITE_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

		PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireELITE_LEFT, 0, (float *)&g_vecZero, (float *)&g_vecZero, flTimeDiff, vecDir.x,
			(int)(vecDir.y * 100), m_iClip, FALSE, FALSE);
	}
	else
	{
		m_pPlayer->SetAnimation(PLAYER_ATTACK2);
		m_iWeaponState |= WPNSTATE_ELITE_LEFT;

		vecDir = m_pPlayer->FireBullets3(vecSrc + gpGlobals->v_right * 5, vecAiming, flSpread,
			8192, BULLET_PLAYER_9MM, 1, ELITE_DAMAGE, ELITE_RANGE_MODIFER, m_pPlayer->pev, true, m_pPlayer->random_seed);

		PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireELITE_RIGHT, 0, (float *)&g_vecZero, (float *)&g_vecZero, flTimeDiff, vecDir.x,
			(int)(vecDir.y * 100), m_iClip, FALSE, FALSE);
	}

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
	{
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.0;
	m_pPlayer->pev->punchangle.x -= 2.0;
}

/* <2510f8> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:239 */
void CELITE::__MAKE_VHOOK(Reload)(void)
{
	if (m_pPlayer->ammo_9mm <= 0)
	{
		return;
	}

	if (DefaultReload(ELITE_MAX_CLIP, ELITE_RELOAD, ELITE_RELOAD_TIME))
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.88;
	}
}

/* <24fed7> ../cstrike/dlls/wpn_shared/wpn_elite.cpp:251 */
void CELITE::__MAKE_VHOOK(WeaponIdle)(void)
{
	int iAnim;

	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
		if (m_iClip)
		{
			iAnim = (m_iClip == 1) ? ELITE_IDLE_LEFTEMPTY : ELITE_IDLE;

			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60.0;
			SendWeaponAnim(iAnim, UseDecrement() != FALSE);
		}
	}
}

#ifdef HOOK_GAMEDLL

void CELITE::Spawn(void)
{
	Spawn_();
}

void CELITE::Precache(void)
{
	Precache_();
}

int CELITE::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CELITE::Deploy(void)
{
	return Deploy_();
}

void CELITE::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CELITE::Reload(void)
{
	Reload_();
}

void CELITE::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
