#include "precompiled.h"

#define FLASHBANG_MAX_SPEED		250
#define FLASHBANG_MAX_SPEED_SHIELD	180

enum flashbang_e
{
	FLASHBANG_IDLE,
	FLASHBANG_PULLPIN,
	FLASHBANG_THROW,
	FLASHBANG_DRAW
};

/* <25ba9b> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:37 */
LINK_ENTITY_TO_CLASS(weapon_flashbang, CFlashbang);

/* <25b72f> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:39 */
void CFlashbang::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_FLASHBANG;
	SET_MODEL(edict(), "models/w_flashbang.mdl");

	pev->dmg = 4;

	m_iDefaultAmmo = FLASHBANG_DEFAULT_GIVE;
	m_flStartThrow = 0;
	m_flReleaseThrow = -1.0;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	// get ready to fall down.
	FallInit();
}

/* <25b67a> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:58 */
void CFlashbang::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_flashbang.mdl");
	PRECACHE_MODEL("models/shield/v_shield_flashbang.mdl");

	PRECACHE_SOUND("weapons/flashbang-1.wav");
	PRECACHE_SOUND("weapons/flashbang-2.wav");
	PRECACHE_SOUND("weapons/pinpull.wav");
}

/* <25b6a1> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:69 */
int CFlashbang::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "Flashbang";
	p->iMaxAmmo1 = MAX_AMMO_FLASHBANG;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 3;
	p->iPosition = 2;
	p->iId = m_iId = WEAPON_FLASHBANG;
	p->iWeight = FLASHBANG_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return 1;
}

/* <25b7df> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:87 */
BOOL CFlashbang::__MAKE_VHOOK(Deploy)(void)
{
	m_flReleaseThrow = -1.0;
	m_fMaxSpeed = FLASHBANG_MAX_SPEED;

	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
		return DefaultDeploy("models/shield/v_shield_flashbang.mdl", "models/shield/p_shield_flashbang.mdl", FLASHBANG_DRAW, "shieldgren", UseDecrement() != FALSE);
	else
		return DefaultDeploy("models/v_flashbang.mdl", "models/p_flashbang.mdl", FLASHBANG_DRAW, "grenade", UseDecrement() != FALSE);
}

/* <25b6fa> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:102 */
void CFlashbang::__MAKE_VHOOK(Holster)(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;

	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		m_pPlayer->pev->weapons &= ~(1 << WEAPON_FLASHBANG);
		DestroyItem();
	}

	m_flStartThrow = 0;
	m_flReleaseThrow = -1.0;
}

/* <25b7a5> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:118 */
void CFlashbang::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		return;
	}

	if (!m_flStartThrow && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0)
	{
		m_flReleaseThrow = 0;
		m_flStartThrow = gpGlobals->time;

		SendWeaponAnim(FLASHBANG_PULLPIN, UseDecrement() != FALSE);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
	}
}

/* <25bb65> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:133 */
bool CFlashbang::ShieldSecondaryFire(int iUpAnim, int iDownAnim)
{
	if (!m_pPlayer->HasShield() || m_flStartThrow > 0)
	{
		return false;
	}

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iDownAnim, UseDecrement() != FALSE);

		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");

		m_fMaxSpeed = FLASHBANG_MAX_SPEED;
		m_pPlayer->m_bShieldDrawn = false;
	}
	else
	{
		m_iWeaponState |= WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iUpAnim, UseDecrement() != FALSE);

		Q_strcpy(m_pPlayer->m_szAnimExtention, "shielded");

		m_fMaxSpeed = FLASHBANG_MAX_SPEED_SHIELD;
		m_pPlayer->m_bShieldDrawn = true;
	}

	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) != WPNSTATE_SHIELD_DRAWN);
	m_pPlayer->ResetMaxSpeed();

	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.4;
	m_flNextPrimaryAttack = GetNextAttackDelay(0.4);
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.6;

	return true;
}

/* <25b81a> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:171 */
void CFlashbang::__MAKE_VHOOK(SecondaryAttack)(void)
{
	ShieldSecondaryFire(SHIELDGUN_DRAW, SHIELDGUN_DRAWN_IDLE);
}

/* <25bb97> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:176 */
void CFlashbang::SetPlayerShieldAnim(void)
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shield");
	else
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
}

/* <25bbb9> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:187 */
void CFlashbang::ResetPlayerShieldAnim(void)
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
	}
}

/* <25a8bd> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:198 */
void CFlashbang::__MAKE_VHOOK(WeaponIdle)(void)
{
	if (m_flReleaseThrow == 0 && m_flStartThrow != 0.0f)
		m_flReleaseThrow = gpGlobals->time;

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_flStartThrow)
	{
		m_pPlayer->Radio("%!MRAD_FIREINHOLE", "#Fire_in_the_hole");

		Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;

		if (angThrow.x < 0)
			angThrow.x = -10 + angThrow.x * ((90 - 10) / 90.0);
		else
			angThrow.x = -10 + angThrow.x * ((90 + 10) / 90.0);

		float_precision flVel = (90.0 - angThrow.x) * 6.0;

		if (flVel > 750.0f)
			flVel = 750.0f;

		UTIL_MakeVectors(angThrow);

		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16;
		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;

		CGrenade::ShootTimed(m_pPlayer->pev, vecSrc, vecThrow, 1.5);

		SendWeaponAnim(FLASHBANG_THROW, UseDecrement() != FALSE);
		SetPlayerShieldAnim();

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

		m_flStartThrow = 0;
		m_flNextPrimaryAttack = GetNextAttackDelay(0.5);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.75;

		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;

		if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			// just threw last grenade
			// set attack times in the future, and weapon idle in the future so we can see the whole throw
			// animation, weapon idle will automatically retire the weapon for us.
			// ensure that the animation can finish playing
			m_flTimeWeaponIdle = m_flNextSecondaryAttack = m_flNextPrimaryAttack = GetNextAttackDelay(0.5);
		}

		ResetPlayerShieldAnim();
	}
	else if (m_flReleaseThrow > 0)
	{
		// we've finished the throw, restart.
		m_flStartThrow = 0;
		RetireWeapon();
	}
	else if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		int iAnim;
		float flRand = RANDOM_FLOAT(0, 1);

		if (m_pPlayer->HasShield())
		{
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0;

			if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			{
				SendWeaponAnim(SHIELDREN_IDLE, UseDecrement() != FALSE);
			}
		}
		else
		{
			if (flRand <= 0.75)
			{
				iAnim = FLASHBANG_IDLE;

				// how long till we do this again.
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
			}
			else
			{
			#ifdef REGAMEDLL_FIXES
				iAnim = FLASHBANG_IDLE;
			#else
				// TODO: This is a bug?
				iAnim = *(int *)&flRand;
			#endif // REGAMEDLL_FIXES
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 75.0 / 30.0;
			}

			SendWeaponAnim(iAnim, UseDecrement() != FALSE);
		}
	}
}

/* <25b6d4> ../cstrike/dlls/wpn_shared/wpn_flashbang.cpp:315 */
BOOL CFlashbang::__MAKE_VHOOK(CanDeploy)(void)
{
	return m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] != 0;
}

#ifdef HOOK_GAMEDLL

void CFlashbang::Spawn(void)
{
	Spawn_();
}

void CFlashbang::Precache(void)
{
	Precache_();
}

int CFlashbang::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CFlashbang::CanDeploy(void)
{
	return CanDeploy_();
}

BOOL CFlashbang::Deploy(void)
{
	return Deploy_();
}

void CFlashbang::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CFlashbang::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CFlashbang::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CFlashbang::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
