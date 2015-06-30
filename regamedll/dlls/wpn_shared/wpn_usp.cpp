#include "precompiled.h"

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
void CUSP::Spawn_(void)
{
	Precache();
	m_iId = WEAPON_USP;
	SET_MODEL(ENT(pev),"models/w_usp.mdl");
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_iDefaultAmmo = 12;//TODO: Default clip USP_MAX_CLIP
	m_flAccuracy = 0.92f;
	FallInit();
}

void CUSP::Precache_(void)
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
int CUSP::GetItemInfo_(ItemInfo *p)
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
	p->iWeight = 5;

	return 1;
}

/* <2bad2e> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:124 */
BOOL CUSP::Deploy_(void)
{
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
	m_flAccuracy = 0.92f;
	m_fMaxSpeed = 250.0f;
	m_pPlayer->m_bShieldDrawn = false;

	if (m_pPlayer->HasShield())
	{
		m_iWeaponState &= ~WPNSTATE_USP_SILENCED;
		return DefaultDeploy("models/shield/v_shield_usp.mdl", "models/shield/p_shield_usp.mdl", USP_SHIELD_DRAW, "shieldgun", UseDecrement() != FALSE);
	}
	else if (m_iWeaponState & WPNSTATE_USP_SILENCED)
		return DefaultDeploy("models/v_usp.mdl", "models/p_usp.mdl", USP_DRAW, "onehanded", UseDecrement() != FALSE);
	return DefaultDeploy("models/v_usp.mdl", "models/p_usp.mdl", USP_UNSIL_DRAW, "onehanded", UseDecrement() != FALSE);
}

/* <2bae77> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:147 */
NOBODY void CUSP::SecondaryAttack_(void)
{
//	SecondaryAttack(CUSP *const this);  //   147
}

/* <2bb000> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:173 */
NOBODY void CUSP::PrimaryAttack_(void)
{
//	Length2D(const Vector *const this);  //   179
//	Length2D(const Vector *const this);  //   190
}

/* <2bb10f> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:200 */
UNTESTED void CUSP::USPFire(float flSpread, float flCycleTime, BOOL fUseSemi)
{
	int flag;
	//int iDamage;;//unused
	//Vector vecAiming;//unused
	//Vector vecSrc;;//unused
	Vector vecDir;

	flCycleTime -= 0.075f;
	
	m_iShotsFired++;
	if (m_iShotsFired > 1)
		return;
	
	if (m_flLastFire != 0.0f)
	{
		m_flAccuracy -= (0.3f - (gpGlobals->time - m_flLastFire)) * 0.275f;
		if (m_flAccuracy > 0.92f)
			m_flAccuracy = 0.92f;
		else if (m_flAccuracy < 0.6f)
			m_flAccuracy = 0.6f;
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
			TheBots->OnEvent(EVENT_WEAPON_FIRED_ON_EMPTY, m_pPlayer, NULL);
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

	UTIL_MakeVectors(m_pPlayer->pev->punchangle + m_pPlayer->pev->v_angle);

	if (!(m_iWeaponState & WPNSTATE_USP_SILENCED))
		m_pPlayer->pev->effects |= EF_MUZZLEFLASH;

	vecDir = FireBullets3(m_pPlayer->GetGunPosition(), gpGlobals->v_forward, flSpread, 4096, 1, BULLET_PLAYER_45ACP, (m_iWeaponState & WPNSTATE_USP_SILENCED) ? 30 : 34, 0.79f, m_pPlayer->pev, true, m_pPlayer->random_seed);

#ifdef CLIENT_WEAPONS
	flag = FEV_NOTHOST;
#else
	flag = 0;
#endif
	PLAYBACK_EVENT_FULL(flag, m_pPlayer->edict(), m_usFireUSP, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100.0f), 0, m_iClip == 0, (int)(m_iWeaponState & WPNSTATE_USP_SILENCED));

	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", 0, 0);

	m_flTimeWeaponIdle = 2.0f;
	m_pPlayer->pev->punchangle.x -= 2.0f;
	ResetPlayerShieldAnim();
}

/* <2bae19> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:297 */
void CUSP::Reload_(void)
{
	if (m_pPlayer->ammo_45acp <= 0)
		return;

	int iResult;
	if (m_pPlayer->HasShield())
		iResult = DefaultReload(USP_MAX_CLIP, USP_SHIELD_RELOAD, 2.7);
	else if (m_iWeaponState & WPNSTATE_USP_SILENCED)
		iResult = DefaultReload(USP_MAX_CLIP, USP_RELOAD, 2.7);
	else
		iResult = DefaultReload(USP_MAX_CLIP, USP_UNSIL_RELOAD, 2.7);

	if (iResult)
	{
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
		m_flAccuracy = 0.92f;
	}
}

/* <2b9c2a> ../cstrike/dlls/wpn_shared/wpn_usp.cpp:318 */
void CUSP::WeaponIdle_(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(0.173648);

	if (m_flTimeWeaponIdle > 0.0f)
		return;

	if (m_pPlayer->HasShield())
	{
		m_flTimeWeaponIdle = 20.0f;
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			SendWeaponAnim(USP_DRAW, UseDecrement() != FALSE);
	}
	else if (m_iClip)
	{
		//int iAnim = USP_UNSIL_IDLE * (~m_iWeaponState & WPNSTATE_USP_SILENCED);
		int iAnim = (~m_iWeaponState & WPNSTATE_USP_SILENCED) ? USP_UNSIL_IDLE: USP_IDLE;// : USP_UNSIL_IDLE;
		m_flTimeWeaponIdle = 60.0f;
		SendWeaponAnim(iAnim, UseDecrement() != FALSE);
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
