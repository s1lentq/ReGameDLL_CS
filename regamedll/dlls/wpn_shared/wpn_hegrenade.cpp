#include "precompiled.h"

#define HEGRENADE_MAX_SPEED		250
#define HEGRENADE_MAX_SPEED_SHIELD	180

enum hegrenade_e
{
	HEGRENADE_IDLE,
	HEGRENADE_PULLPIN,
	HEGRENADE_THROW,
	HEGRENADE_DRAW
};

/* <26b3cd> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:38 */
LINK_ENTITY_TO_CLASS(weapon_hegrenade, CHEGrenade);

/* <26b07c> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:40 */
void CHEGrenade::__MAKE_VHOOK(Spawn)(void)
{
	Precache();
	m_iId = WEAPON_HEGRENADE;
	SET_MODEL(edict(), "models/w_hegrenade.mdl");

	pev->dmg = 4;
	
	m_iDefaultAmmo = HEGRENADE_DEFAULT_GIVE;
	m_flStartThrow = 0;
	m_flReleaseThrow = -1;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	// get ready to fall down.
	FallInit();
}

/* <26afc7> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:59 */
void CHEGrenade::__MAKE_VHOOK(Precache)(void)
{
	PRECACHE_MODEL("models/v_hegrenade.mdl");
	PRECACHE_MODEL("models/shield/v_shield_hegrenade.mdl");

	PRECACHE_SOUND("weapons/hegrenade-1.wav");
	PRECACHE_SOUND("weapons/hegrenade-2.wav");
	PRECACHE_SOUND("weapons/he_bounce-1.wav");
	PRECACHE_SOUND("weapons/pinpull.wav");

	m_usCreateExplosion = PRECACHE_EVENT(1, "events/createexplo.sc");
}

/* <26afee> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:74 */
int CHEGrenade::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "HEGrenade";
	p->iMaxAmmo1 = MAX_AMMO_HEGRENADE;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 3;
	p->iPosition = 1;
	p->iId = m_iId = WEAPON_HEGRENADE;
	p->iWeight = HEGRENADE_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return 1;
}

/* <26b12c> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:92 */
BOOL CHEGrenade::__MAKE_VHOOK(Deploy)(void)
{
	m_flReleaseThrow = -1;
	m_fMaxSpeed = HEGRENADE_MAX_SPEED;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
		return DefaultDeploy("models/shield/v_shield_hegrenade.mdl", "models/shield/p_shield_hegrenade.mdl", HEGRENADE_DRAW, "shieldgren", UseDecrement() != FALSE);
	else
		return DefaultDeploy("models/v_hegrenade.mdl", "models/p_hegrenade.mdl", HEGRENADE_DRAW, "grenade", UseDecrement() != FALSE);
}

/* <26b047> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:107 */
void CHEGrenade::__MAKE_VHOOK(Holster)(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;

	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		m_pPlayer->pev->weapons &= ~(1 << WEAPON_HEGRENADE);
		DestroyItem();
	}

	m_flStartThrow = 0;
	m_flReleaseThrow = -1;
}

/* <26b0f2> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:123 */
void CHEGrenade::__MAKE_VHOOK(PrimaryAttack)(void)
{
	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		return;
	}

	if (!m_flStartThrow && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0)
	{
		m_flReleaseThrow = 0;
		m_flStartThrow = gpGlobals->time;

		SendWeaponAnim(HEGRENADE_PULLPIN, UseDecrement() != FALSE);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
	}
}

/* <26b497> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:138 */
bool CHEGrenade::ShieldSecondaryFire(int iUpAnim, int iDownAnim)
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

		m_fMaxSpeed = HEGRENADE_MAX_SPEED;
		m_pPlayer->m_bShieldDrawn = false;
	}
	else
	{
		m_iWeaponState |= WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iUpAnim, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shielded");

		m_fMaxSpeed = HEGRENADE_MAX_SPEED_SHIELD;
		m_pPlayer->m_bShieldDrawn = true;
	}

	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) != WPNSTATE_SHIELD_DRAWN);
	m_pPlayer->ResetMaxSpeed();

	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.4;
	m_flNextPrimaryAttack = GetNextAttackDelay(0.4);
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.6;

	return true;
}

/* <26b167> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:176 */
void CHEGrenade::__MAKE_VHOOK(SecondaryAttack)(void)
{
	ShieldSecondaryFire(SHIELDGUN_DRAW, SHIELDGUN_DRAWN_IDLE);
}

/* <26b4c9> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:181 */
void CHEGrenade::SetPlayerShieldAnim(void)
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shield");
	else
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
}

/* <26b4eb> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:192 */
void CHEGrenade::ResetPlayerShieldAnim(void)
{
	if (!m_pPlayer->HasShield())
		return;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
	}
}

/* <26a24e> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:202 */
void CHEGrenade::__MAKE_VHOOK(WeaponIdle)(void)
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

		float flVel = (90.0 - angThrow.x) * 6.0;

		if (flVel > 750.0f)
			flVel = 750.0f;

		UTIL_MakeVectors(angThrow);

		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16;
		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;

		CGrenade::ShootTimed2(m_pPlayer->pev, vecSrc, vecThrow, 1.5, m_pPlayer->m_iTeam, m_usCreateExplosion);

		SendWeaponAnim(HEGRENADE_THROW, UseDecrement() != FALSE);
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

		if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			SendWeaponAnim(HEGRENADE_DRAW, UseDecrement() != FALSE);
		}
		else
		{
			RetireWeapon();
			return;
		}

		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
		m_flReleaseThrow = -1;
	}
	else if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		if (m_pPlayer->HasShield())
		{
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;

			if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			{
				SendWeaponAnim(SHIELDREN_IDLE, UseDecrement() != FALSE);
			}
		}
		else
		{
			SendWeaponAnim(HEGRENADE_IDLE, UseDecrement() != FALSE);

			// how long till we do this again.
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
		}
	}
}

/* <26b021> ../cstrike/dlls/wpn_shared/wpn_hegrenade.cpp:303 */
BOOL CHEGrenade::__MAKE_VHOOK(CanDeploy)(void)
{
	return m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] != 0;
}

#ifdef HOOK_GAMEDLL

void CHEGrenade::Spawn(void)
{
	Spawn_();
}

void CHEGrenade::Precache(void)
{
	Precache_();
}

int CHEGrenade::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CHEGrenade::CanDeploy(void)
{
	return CanDeploy_();
}

BOOL CHEGrenade::Deploy(void)
{
	return Deploy_();
}

void CHEGrenade::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CHEGrenade::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CHEGrenade::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CHEGrenade::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
