#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

ItemInfo CBasePlayerItem::ItemInfoArray[32];
AmmoInfo CBasePlayerItem::AmmoInfoArray[32];

TYPEDESCRIPTION CBasePlayerItem::m_SaveData[] =
{
	DEFINE_FIELD(CBasePlayerItem, m_pPlayer, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayerItem, m_pNext, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayerItem, m_iId, FIELD_INTEGER),
};

TYPEDESCRIPTION CBasePlayerWeapon::m_SaveData[] =
{
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextPrimaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flNextSecondaryAttack, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_flTimeWeaponIdle, FIELD_TIME),
	DEFINE_FIELD(CBasePlayerWeapon, m_iPrimaryAmmoType, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerWeapon, m_iSecondaryAmmoType, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerWeapon, m_iClip, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayerWeapon, m_iDefaultAmmo, FIELD_INTEGER),
};

TYPEDESCRIPTION CWeaponBox::m_SaveData[] =
{
	DEFINE_ARRAY(CWeaponBox, m_rgAmmo, FIELD_INTEGER, MAX_AMMO_SLOTS),
	DEFINE_ARRAY(CWeaponBox, m_rgiszAmmo, FIELD_STRING, MAX_AMMO_SLOTS),
	DEFINE_ARRAY(CWeaponBox, m_rgpPlayerItems, FIELD_CLASSPTR, MAX_ITEM_TYPES),
	DEFINE_FIELD(CWeaponBox, m_cAmmoTypes, FIELD_INTEGER),
};

const char *g_pModelNameLaser = "sprites/laserbeam.spr";

#else // HOOK_GAMEDLL

ItemInfo (*CBasePlayerItem::pItemInfoArray)[32];
AmmoInfo (*CBasePlayerItem::pAmmoInfoArray)[32];

TYPEDESCRIPTION (*CBasePlayerItem::pm_SaveData)[3];
TYPEDESCRIPTION (*CBasePlayerWeapon::pm_SaveData)[7];
TYPEDESCRIPTION (*CWeaponBox::pm_SaveData)[4];

const char *g_pModelNameLaser;

#endif // HOOK_GAMEDLL

short g_sModelIndexLaser;
short g_sModelIndexLaserDot;
short g_sModelIndexFireball;
short g_sModelIndexSmoke;
short g_sModelIndexWExplosion;
short g_sModelIndexBubbles;
short g_sModelIndexBloodDrop;
short g_sModelIndexBloodSpray;
short g_sModelIndexSmokePuff;
short g_sModelIndexFireball2;
short g_sModelIndexFireball3;
short g_sModelIndexFireball4;
short g_sModelIndexRadio;

short int g_sModelIndexCTGhost;
short int g_sModelIndexTGhost;
short int g_sModelIndexC4Glow;

int giAmmoIndex;

MULTIDAMAGE gMultiDamage;

/* <1d018e> ../cstrike/dlls/weapons.cpp:82 */
int MaxAmmoCarry(int iszName)
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		ItemInfo *pInfo = &IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, ItemInfoArray)[ i ];

		if (pInfo->pszAmmo1 && !Q_strcmp(STRING(iszName), pInfo->pszAmmo1))
			return pInfo->iMaxAmmo1;

		if (pInfo->pszAmmo2 && !Q_strcmp(STRING(iszName), pInfo->pszAmmo2))
			return pInfo->iMaxAmmo2;
	}

	ALERT(at_console, "MaxAmmoCarry() doesn't recognize '%s'!\n", STRING(iszName));
	return -1;
}

/* <1d2a29> ../cstrike/dlls/weapons.cpp:110 */
void ClearMultiDamage(void)
{
	gMultiDamage.pEntity = NULL;
	gMultiDamage.amount = 0;
	gMultiDamage.type = 0;
}

/* <1d2a41> ../cstrike/dlls/weapons.cpp:124 */
void ApplyMultiDamage(entvars_t *pevInflictor, entvars_t *pevAttacker)
{
	if (gMultiDamage.pEntity)
		gMultiDamage.pEntity->TakeDamage(pevInflictor, pevAttacker, gMultiDamage.amount, gMultiDamage.type);
}

/* <1d2ad3> ../cstrike/dlls/weapons.cpp:140 */
void AddMultiDamage(entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType)
{
	if (pEntity)
	{
		gMultiDamage.type |= bitsDamageType;
		if (pEntity != gMultiDamage.pEntity)
		{
			ApplyMultiDamage(pevInflictor,pevInflictor);
			gMultiDamage.pEntity = pEntity;
			gMultiDamage.amount = flDamage;
		}
		else
			gMultiDamage.amount += flDamage;
	}
}

/* <1d2b6f> ../cstrike/dlls/weapons.cpp:162 */
void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage)
{
	UTIL_BloodDrips(vecSpot, g_vecAttackDir, bloodColor, flDamage);
}

/* <1d2bbb> ../cstrike/dlls/weapons.cpp:168 */
NOXREF int DamageDecal(CBaseEntity *pEntity, int bitsDamageType)
{
	if (pEntity)
		return pEntity->DamageDecal(bitsDamageType);
	return RANDOM_LONG(3, 4);
}

/* <1d2bfa> ../cstrike/dlls/weapons.cpp:176 */
NOXREF void DecalGunshot(TraceResult *pTrace, int iBulletType, bool ClientOnly, entvars_t *pShooter, bool bHitMetal)
{
	;
}

/* <1d07b3> ../cstrike/dlls/weapons.cpp:184 */
NOBODY void EjectBrass(Vector &vecOrigin, Vector &vecLeft, Vector &vecVelocity, float rotation, int model, int soundtype, int entityIndex)
{
//	{
//		class CBaseEntity *ent;                              //   188
//		bool useNewBehavior;                                  //   190
//	}
}

/* <1d2cfd> ../cstrike/dlls/weapons.cpp:220 */
NOBODY void EjectBrass2(Vector &vecOrigin, Vector &vecVelocity, float rotation, int model, int soundtype, entvars_t *pev)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			entvars_t *ent);  //   224
}

/* <1d020f> ../cstrike/dlls/weapons.cpp:242 */
NOXREF void AddAmmoNameToAmmoRegistry(const char *szAmmoname)
{
	for (int i = 0; i < MAX_AMMO_SLOTS; i++)
	{
		if (!IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, AmmoInfoArray)[ i ].pszName)
			continue;

		if (!Q_stricmp(IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, AmmoInfoArray)[ i ].pszName, szAmmoname))
			return;
	}

	giAmmoIndex++;

	if (giAmmoIndex >= MAX_AMMO_SLOTS)
		giAmmoIndex = 0;

	IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, AmmoInfoArray)[ giAmmoIndex ].pszName = szAmmoname;
	IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, AmmoInfoArray)[ giAmmoIndex ].iId = giAmmoIndex;
}

/* <1d2e01> ../cstrike/dlls/weapons.cpp:265 */
void UTIL_PrecacheOtherWeapon(const char *szClassname)
{
	edict_t *pent = CREATE_NAMED_ENTITY(MAKE_STRING(szClassname));

	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in UTIL_PrecacheOtherWeapon\n");
		return;
	}

	CBaseEntity *pEntity = CBaseEntity::Instance(VARS(pent));

	if (pEntity)
	{
		ItemInfo II;
		pEntity->Precache();
		Q_memset(&II, 0, sizeof(II));

		if (((CBasePlayerItem *)pEntity)->GetItemInfo(&II))
		{
			IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, ItemInfoArray)[ II.iId ] = II;

			if (II.pszAmmo1 && *II.pszAmmo1)
				AddAmmoNameToAmmoRegistry(II.pszAmmo1);

			if (II.pszAmmo2 && *II.pszAmmo2)
				AddAmmoNameToAmmoRegistry(II.pszAmmo2);
		}
	}

	REMOVE_ENTITY(pent);
}

/* <1d2fc9> ../cstrike/dlls/weapons.cpp:304 */
NOXREF void UTIL_PrecacheOtherWeapon2(const char *szClassname)
{
	edict_t *pent = CREATE_NAMED_ENTITY(MAKE_STRING(szClassname));

	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in UTIL_PrecacheOtherWeapon\n");
		return;
	}

	CBaseEntity *pEntity = CBaseEntity::Instance(VARS(pent));

	if (pEntity)
	{
		ItemInfo II;
		pEntity->Precache();
		Q_memset(&II, 0, sizeof(II));

		if (((CBasePlayerItem *)pEntity)->GetItemInfo(&II))
		{
			IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, ItemInfoArray)[ II.iId ] = II;

			if (II.pszAmmo1 && *II.pszAmmo1)
				AddAmmoNameToAmmoRegistry(II.pszAmmo1);

			if (II.pszAmmo2 && *II.pszAmmo2)
				AddAmmoNameToAmmoRegistry(II.pszAmmo2);
		}
	}

	REMOVE_ENTITY(pent);
}

/* <1d3191> ../cstrike/dlls/weapons.cpp:345 */
void W_Precache(void)
{
	Q_memset(IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, ItemInfoArray), 0, ARRAYSIZE(IMPLEMENT_ARRAY_CLASS(CBasePlayerItem, ItemInfoArray)));
	giAmmoIndex = 0;

	UTIL_PrecacheOther("item_suit");
	UTIL_PrecacheOther("item_battery");
	UTIL_PrecacheOther("item_antidote");
	UTIL_PrecacheOther("item_security");
	UTIL_PrecacheOther("item_longjump");
	UTIL_PrecacheOther("item_kevlar");
	UTIL_PrecacheOther("item_assaultsuit");
	UTIL_PrecacheOther("item_thighpack");

	UTIL_PrecacheOtherWeapon("weapon_awp");
	UTIL_PrecacheOther("ammo_338magnum");
	UTIL_PrecacheOtherWeapon("weapon_g3sg1");
	UTIL_PrecacheOtherWeapon("weapon_ak47");
	UTIL_PrecacheOtherWeapon("weapon_scout");
	UTIL_PrecacheOther("ammo_762nato");
	UTIL_PrecacheOtherWeapon("weapon_m249");
	UTIL_PrecacheOther("ammo_556natobox");
	UTIL_PrecacheOtherWeapon("weapon_m4a1");
	UTIL_PrecacheOtherWeapon("weapon_sg552");
	UTIL_PrecacheOtherWeapon("weapon_aug");
	UTIL_PrecacheOtherWeapon("weapon_sg550");
	UTIL_PrecacheOther("ammo_556nato");
	UTIL_PrecacheOtherWeapon("weapon_m3");
	UTIL_PrecacheOtherWeapon("weapon_xm1014");
	UTIL_PrecacheOther("ammo_buckshot");
	UTIL_PrecacheOtherWeapon("weapon_usp");
	UTIL_PrecacheOtherWeapon("weapon_mac10");
	UTIL_PrecacheOtherWeapon("weapon_ump45");
	UTIL_PrecacheOther("ammo_45acp");
	UTIL_PrecacheOtherWeapon("weapon_fiveseven");
	UTIL_PrecacheOtherWeapon("weapon_p90");
	UTIL_PrecacheOther("ammo_57mm");
	UTIL_PrecacheOtherWeapon("weapon_deagle");
	UTIL_PrecacheOther("ammo_50ae");
	UTIL_PrecacheOtherWeapon("weapon_p228");
	UTIL_PrecacheOther("ammo_357sig");
	UTIL_PrecacheOtherWeapon("weapon_knife");
	UTIL_PrecacheOtherWeapon("weapon_glock18");
	UTIL_PrecacheOtherWeapon("weapon_mp5navy");
	UTIL_PrecacheOtherWeapon("weapon_tmp");
	UTIL_PrecacheOtherWeapon("weapon_elite");
	UTIL_PrecacheOther("ammo_9mm");
	UTIL_PrecacheOtherWeapon("weapon_flashbang");
	UTIL_PrecacheOtherWeapon("weapon_hegrenade");
	UTIL_PrecacheOtherWeapon("weapon_smokegrenade");
	UTIL_PrecacheOtherWeapon("weapon_c4");
	UTIL_PrecacheOtherWeapon("weapon_galil");
	UTIL_PrecacheOtherWeapon("weapon_famas");

	if (g_pGameRules->IsDeathmatch())
	{
		UTIL_PrecacheOther("weaponbox");
	}

	g_sModelIndexFireball = PRECACHE_MODEL("sprites/zerogxplode.spr");
	g_sModelIndexWExplosion = PRECACHE_MODEL("sprites/WXplo1.spr");
	g_sModelIndexSmoke = PRECACHE_MODEL("sprites/steam1.spr");
	g_sModelIndexBubbles = PRECACHE_MODEL("sprites/bubble.spr");
	g_sModelIndexBloodSpray = PRECACHE_MODEL("sprites/bloodspray.spr");
	g_sModelIndexBloodDrop = PRECACHE_MODEL("sprites/blood.spr");
	g_sModelIndexSmokePuff = PRECACHE_MODEL("sprites/smokepuff.spr");
	g_sModelIndexFireball2 = PRECACHE_MODEL("sprites/eexplo.spr");
	g_sModelIndexFireball3 = PRECACHE_MODEL("sprites/fexplo.spr");
	g_sModelIndexFireball4 = PRECACHE_MODEL("sprites/fexplo1.spr");
	g_sModelIndexRadio = PRECACHE_MODEL("sprites/radio.spr");

	g_sModelIndexCTGhost = PRECACHE_MODEL("sprites/b-tele1.spr");
	g_sModelIndexTGhost = PRECACHE_MODEL("sprites/c-tele1.spr");
	g_sModelIndexC4Glow = PRECACHE_MODEL("sprites/ledglow.spr");

	g_sModelIndexLaser = PRECACHE_MODEL((char *)g_pModelNameLaser);
	g_sModelIndexLaserDot = PRECACHE_MODEL("sprites/laserdot.spr");

	PRECACHE_MODEL("models/grenade.mdl");
	PRECACHE_MODEL("sprites/explode1.spr");
	PRECACHE_SOUND("weapons/debris1.wav");
	PRECACHE_SOUND("weapons/debris2.wav");
	PRECACHE_SOUND("weapons/debris3.wav");
	PRECACHE_SOUND("weapons/grenade_hit1.wav");
	PRECACHE_SOUND("weapons/grenade_hit2.wav");
	PRECACHE_SOUND("weapons/grenade_hit3.wav");
	PRECACHE_SOUND("weapons/bullet_hit1.wav");
	PRECACHE_SOUND("weapons/bullet_hit2.wav");
	PRECACHE_SOUND("items/weapondrop1.wav");
	PRECACHE_SOUND("weapons/generic_reload.wav");
}

/* <1d31ab> ../cstrike/dlls/weapons.cpp:485 */
void CBasePlayerItem::FallInit(void)
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_BBOX;

	UTIL_SetOrigin(pev, pev->origin);
	UTIL_SetSize(pev, Vector(0,0,0), Vector(0,0,0));

	SetTouch(&CBasePlayerItem::DefaultTouch);
	SetThink(&CBasePlayerItem::FallThink);

	pev->nextthink = gpGlobals->time + 0.1;
}

/* <1d20a8> ../cstrike/dlls/weapons.cpp:458 */
IMPLEMENT_SAVERESTORE(CBasePlayerItem, CBaseAnimating);

/* <1d27b2> ../cstrike/dlls/weapons.cpp:472 */
IMPLEMENT_SAVERESTORE(CBasePlayerWeapon, CBasePlayerItem);

/* <1d1730> ../cstrike/dlls/weapons.cpp:475 */
NOBODY void CBasePlayerItem::__MAKE_VHOOK(SetObjectCollisionBox)(void)
{
//	operator+(const Vector ::SetObjectCollisionBox(//			const Vector &v);  //   477
//	operator+(const Vector *const this,
//			const Vector &v);  //   478
}

/* <1d32bc> ../cstrike/dlls/weapons.cpp:506 */
void CBasePlayerItem::FallThink(void)
{
	pev->nextthink = gpGlobals->time + 0.1;
	if (pev->flags & FL_ONGROUND)
	{
		if (!FNullEnt(pev->owner))
		{
			int pitch = RANDOM_LONG(0, 29) + 95;
			EMIT_SOUND_DYN(ENT(pev), CHAN_VOICE, "items/weapondrop1.wav", VOL_NORM, ATTN_NORM, 0, pitch);
		}
		pev->angles.x = 0.0f;
		pev->angles.z = 0.0f;

		Materialize();
	}
}

/* <1d3252> ../cstrike/dlls/weapons.cpp:531 */
void CBasePlayerItem::Materialize(void)
{
	if (pev->effects & EF_NODRAW)
	{
		if (g_pGameRules->IsMultiplayer())
		{
			EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, "items/suitchargeok1.wav", VOL_NORM, ATTN_NORM, 0, 150);
		}

		pev->effects &= ~EF_NODRAW;
		pev->effects |= EF_MUZZLEFLASH;
	}

	pev->solid = SOLID_TRIGGER;
	UTIL_SetOrigin(pev, pev->origin);

	SetTouch(&CBasePlayerItem::DefaultTouch);
	if (g_pGameRules->IsMultiplayer())
	{
		if (!CanDrop())
			SetTouch(NULL);

		SetThink(&CBaseEntity::SUB_Remove);
		pev->nextthink = gpGlobals->time + 1.0f;
	}
	else
		SetThink(NULL);
}

/* <1d327b> ../cstrike/dlls/weapons.cpp:567 */
NOBODY void CBasePlayerItem::AttemptToMaterialize(void)
{
//	{
//		float time;                                           //   569
//	}
}

/* <1d3348> ../cstrike/dlls/weapons.cpp:584 */
void CBasePlayerItem::CheckRespawn(void)
{
	switch (g_pGameRules->WeaponShouldRespawn(this))
	{
		case GR_WEAPON_RESPAWN_YES:
			return;
		case GR_WEAPON_RESPAWN_NO:
			return;
	}
}

/* <1d1e09> ../cstrike/dlls/weapons.cpp:616 */
NOBODY CBaseEntity *CBasePlayerItem::__MAKE_VHOOK(Respawn)(void)
{
//	{
//		class CBaseEntity *pNewWeapon;                       //   620
//	}
	return NULL;
}

/* <1d26f0> ../cstrike/dlls/weapons.cpp:642 */
void CBasePlayerItem::DefaultTouch(CBaseEntity *pOther)
{
	// if it's not a player, ignore
	if (!pOther->IsPlayer())
	{
		return;
	}

	CBasePlayer *pPlayer = reinterpret_cast<CBasePlayer *>(pOther);

	if (pPlayer->m_bIsVIP
		&& m_iId != WEAPON_USP
		&& m_iId != WEAPON_GLOCK18
		&& m_iId != WEAPON_P228
		&& m_iId != WEAPON_DEAGLE
		&& m_iId != WEAPON_KNIFE)
	{
		return;
	}

	// can I have this?
	if (!g_pGameRules->CanHavePlayerItem(pPlayer, this))
	{
		if (gEvilImpulse101)
		{
			UTIL_Remove(this);
		}

		return;
	}

	if (pOther->AddPlayerItem(this))
	{
		AttachToPlayer(pPlayer);
		SetThink(NULL);
		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);
	}

	SUB_UseTargets(pOther, USE_TOGGLE, 0);
}

/* <1d3371> ../cstrike/dlls/weapons.cpp:678 */
void CBasePlayerWeapon::SetPlayerShieldAnim(void)
{
	if (m_pPlayer->HasShield())
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			Q_strcpy(m_pPlayer->m_szAnimExtention, "shield");
		else
			Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgun");
	}
}

/* <1d339a> ../cstrike/dlls/weapons.cpp:689 */
void CBasePlayerWeapon::ResetPlayerShieldAnim(void)
{
	if (m_pPlayer->HasShield())
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgun");
	}
}

/* <1d33c3> ../cstrike/dlls/weapons.cpp:699 */
NOBODY void CBasePlayerWeapon::EjectBrassLate(void)
{
//	{
//		Vector vecShellVelocity;                        //   702
//		int soundType;                                        //   707
//		operator+(const Vector *const this,
//				const Vector &v);  //   701
//		operator*(const Vector *const this,
//				float fl);  //   705
//		operator*(const Vector *const this,
//				float fl);  //   705
//		operator*(const Vector *const this,
//				float fl);  //   705
//		operator+(const Vector *const this,
//				const Vector &v);  //   705
//		operator+(const Vector *const this,
//				const Vector &v);  //   705
//		operator+(const Vector *const this,
//				const Vector &v);  //   705
//		ENTINDEX(edict_t *pEdict);  //   714
//		operator*(const Vector *const this,
//				float fl);  //   714
//		operator*(const Vector *const this,
//				float fl);  //   714
//		operator*(const Vector *const this,
//				float fl);  //   714
//		operator+(const Vector *const this,
//				const Vector &v);  //   714
//		operator+(const Vector *const this,
//				const Vector &v);  //   714
//		operator+(const Vector *const this,
//				const Vector &v);  //   714
//		EjectBrass(Vector &vecOrigin,
//				const Vector &vecLeft,
//				const Vector &vecVelocity,
//				float rotation,
//				int model,
//				int soundtype,
//				int entityIndex);  //   714
//	}
}

/* <1d372a> ../cstrike/dlls/weapons.cpp:717 */
bool CBasePlayerWeapon::ShieldSecondaryFire(int iUpAnim, int iDownAnim)
{
	if (!m_pPlayer->HasShield())
		return false;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iDownAnim, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shieldgun");
		m_fMaxSpeed = 250.0f;
		m_pPlayer->m_bShieldDrawn = false;
	}
	else
	{
		m_iWeaponState |= WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(iUpAnim, UseDecrement() != FALSE);
		Q_strcpy(m_pPlayer->m_szAnimExtention, "shielded");
		m_fMaxSpeed = 180.0f;
		m_pPlayer->m_bShieldDrawn = true;
	}

	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) == 0);
	m_pPlayer->ResetMaxSpeed();

	m_flNextSecondaryAttack = 0.4f;
	m_flNextPrimaryAttack = 0.4f;
	m_flTimeWeaponIdle = 0.6f;

	return true;
}

/* <1d3773> ../cstrike/dlls/weapons.cpp:752 */
NOBODY void CBasePlayerWeapon::KickBack(float up_base, float lateral_base, float up_modifier, float lateral_modifier, float up_max, float lateral_max, int direction_change)
{
//	{
//		float flKickUp;                                       //   754
//		float flKickLateral;                                  //   755
//	}
}

/* <1d242e> ../cstrike/dlls/weapons.cpp:792 */
NOBODY void CBasePlayerWeapon::FireRemaining(int &shotsFired, float &shootTime, BOOL bIsGlock)
{
//	{
//		float nexttime;                                       //   794
//		Vector vecSrc;                                  //   810
//		int flag;                                             //   828
//		Vector vecAiming;                               //   811
//		Vector vecDir;                                  //   814
//		operator+(const Vector *const this,
//				const Vector &v);  //   808
//		Vector(Vector *const this,
//			const Vector &v);  //   818
//		Vector(Vector *const this,
//			const Vector &v);  //   818
//		Vector(Vector *const this,
//			const Vector &v);  //   824
//		Vector(Vector *const this,
//			const Vector &v);  //   824
//	}
}

/* <1d389e> ../cstrike/dlls/weapons.cpp:876 */
NOXREF BOOL CanAttack(float attack_time, float curtime, BOOL isPredicted)
{
	if (isPredicted)
	{
		if (attack_time > 0.0)
			return FALSE;
	}
	else
	{
		if (attack_time > curtime)
			return FALSE;
	}
	return TRUE;
}

/* <1d38f0> ../cstrike/dlls/weapons.cpp:890 */
NOBODY bool CBasePlayerWeapon::HasSecondaryAttack(void)
{
	if (m_pPlayer->HasShield())
		return true;

	if (m_iId != WEAPON_AK47
		&& m_iId != WEAPON_XM1014
		&& m_iId != WEAPON_MAC10
		&& m_iId != WEAPON_ELITE
		&& m_iId != WEAPON_FIVESEVEN
		&& m_iId != WEAPON_MP5N
		&& m_iId != WEAPON_M249
		&& m_iId != WEAPON_M3
		&& m_iId != WEAPON_TMP
		&& m_iId != WEAPON_DEAGLE
		&& m_iId != WEAPON_P228
		&& m_iId != WEAPON_P90
		&& m_iId != WEAPON_C4
		&& m_iId != WEAPON_GALIL)
			return true;
	return false;
}

/* <1d3919> ../cstrike/dlls/weapons.cpp:915 */
NOBODY void CBasePlayerWeapon::__MAKE_VHOOK(ItemPostFrame)(void)
{
//	{
//		int usableButtons;                                    //   918
//		pszAmmo2(CBasePlayerItem *const this);  //   982
//		pszAmmo1(CBasePlayerItem *const this);  //   992
//		iMaxClip(CBasePlayerItem *const this);  //  1006
//		{
//			int j;                                        //   969
//			iMaxClip(CBasePlayerItem *const this);  //   969
//		}
//		FireRemaining(CBasePlayerWeapon *const this,
//				int &shotsFired,
//				float &shootTime,
//				BOOL bIsGlock);  //   923
//		FireRemaining(CBasePlayerWeapon *const this,
//				int &shotsFired,
//				float &shootTime,
//				BOOL bIsGlock);  //   925
//		iFlags(CBasePlayerItem *const this);  //  1051
//		iMaxClip(CBasePlayerItem *const this);  //   992
//	}
}

/* <1d3aac> ../cstrike/dlls/weapons.cpp:1069 */
NOBODY void CBasePlayerItem::DestroyItem(void)
{
}

/* <1d17d4> ../cstrike/dlls/weapons.cpp:1081 */
NOXREF int CBasePlayerItem::__MAKE_VHOOK(AddToPlayer)(CBasePlayer *pPlayer)
{
	m_pPlayer = pPlayer;

	MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev);
		WRITE_BYTE(m_iId);
	MESSAGE_END();

	return 1;
}

/* <1d183d> ../cstrike/dlls/weapons.cpp:1092 */
void CBasePlayerItem::__MAKE_VHOOK(Drop)(void)
{
	SetTouch(NULL);
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.1;
}

/* <1d1866> ../cstrike/dlls/weapons.cpp:1099 */
void CBasePlayerItem::__MAKE_VHOOK(Kill)(void)
{
	SetTouch(NULL);
	SetThink(&CBaseEntity::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.1;
}

/* <1d188f> ../cstrike/dlls/weapons.cpp:1106 */
void CBasePlayerItem::__MAKE_VHOOK(Holster)(int skiplocal)
{
	m_pPlayer->pev->viewmodel = 0;
	m_pPlayer->pev->weaponmodel = 0;
}

/* <1d18c7> ../cstrike/dlls/weapons.cpp:1112 */
void CBasePlayerItem::__MAKE_VHOOK(AttachToPlayer)(CBasePlayer *pPlayer)
{
	pev->movetype = MOVETYPE_FOLLOW;
	pev->solid = SOLID_NOT;
	pev->aiment = pPlayer->edict();
	pev->effects = EF_NODRAW;
	pev->modelindex = 0;
	pev->model = 0;
	pev->owner = pPlayer->edict();
	pev->nextthink = gpGlobals->time + 0.1;

	SetTouch(NULL);
}

/* <1d1e4a> ../cstrike/dlls/weapons.cpp:1126 */
int CBasePlayerWeapon::__MAKE_VHOOK(AddDuplicate)(CBasePlayerItem *pOriginal)
{
	if (m_iDefaultAmmo)
		return ExtractAmmo((CBasePlayerWeapon *)pOriginal);
	else
		return ExtractClipAmmo((CBasePlayerWeapon *)pOriginal);
}

/* <1d237f> ../cstrike/dlls/weapons.cpp:1140 */
int CBasePlayerWeapon::__MAKE_VHOOK(AddToPlayer)(CBasePlayer *pPlayer)
{
	m_pPlayer = pPlayer;
	pPlayer->pev->weapons |= (1 << m_iId);

	if (!m_iPrimaryAmmoType)
	{
		m_iPrimaryAmmoType = pPlayer->GetAmmoIndex(pszAmmo1());
		m_iSecondaryAmmoType = pPlayer->GetAmmoIndex(pszAmmo2());
	}

	if (AddWeapon())
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev);
			WRITE_BYTE(m_iId);
		MESSAGE_END();

		return 1;
	}
	return 0;
}

/* <1d24a3> ../cstrike/dlls/weapons.cpp:1164 */
int CBasePlayerWeapon::__MAKE_VHOOK(UpdateClientData)(CBasePlayer *pPlayer)
{
	BOOL bSend = FALSE;
	int state = 0;

	if (pPlayer->m_pActiveItem == this)
	{
		if (pPlayer->m_fOnTarget)
			state = WEAPON_IS_ONTARGET;
		else
			state = 1;
	}

	if (!pPlayer->m_fWeapon)
		bSend = TRUE;

	if (this == pPlayer->m_pActiveItem || this == pPlayer->m_pClientActiveItem)
	{
		if (pPlayer->m_pActiveItem != pPlayer->m_pClientActiveItem)
			bSend = TRUE;
	}

	if (m_iClip != m_iClientClip || state != m_iClientWeaponState || pPlayer->m_iFOV != pPlayer->m_iClientFOV)
		bSend = TRUE;

	if (bSend)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, NULL, pPlayer->pev);
			WRITE_BYTE(state);
			WRITE_BYTE(m_iId);
			WRITE_BYTE(m_iClip);
		MESSAGE_END();

		m_iClientWeaponState = state;
		m_iClientClip = m_iClip;

		pPlayer->m_fWeapon = TRUE;
	}

	if (m_pNext)
		m_pNext->UpdateClientData(pPlayer);

	return 1;
}

/* <1d22c7> ../cstrike/dlls/weapons.cpp:1218 */
void CBasePlayerWeapon::__MAKE_VHOOK(SendWeaponAnim)(int iAnim, int skiplocal)
{
	m_pPlayer->pev->weaponanim = iAnim;
	if (!skiplocal || !ENGINE_CANSKIP(ENT(m_pPlayer->pev)))
	{
		MESSAGE_BEGIN(MSG_ONE, SVC_WEAPONANIM, NULL, m_pPlayer->pev);
			WRITE_BYTE(iAnim);
			WRITE_BYTE(pev->body);
		MESSAGE_END();
	}
}

/* <1d3ad5> ../cstrike/dlls/weapons.cpp:1231 */
BOOL CBasePlayerWeapon::AddPrimaryAmmo(int iCount, char *szName, int iMaxClip, int iMaxCarry)
{
	int iIdAmmo;
	if (iMaxClip < 1)
	{
		m_iClip = -1;
		iIdAmmo = m_pPlayer->GiveAmmo(iCount, szName, iMaxCarry);
	}
	else if (m_iClip)
		iIdAmmo = m_pPlayer->GiveAmmo(iCount, szName, iMaxCarry);
	else
	{
		int i = _min(m_iClip + iCount, iMaxClip);
		m_iClip = i;

		iIdAmmo = m_pPlayer->GiveAmmo(iCount - i, szName, iMaxCarry);
	}
	if (iIdAmmo > 0)
	{
		m_iPrimaryAmmoType = iIdAmmo;
		if (m_pPlayer->HasPlayerItem(this))
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	}
	return iIdAmmo > 0 ? TRUE : FALSE;
}

/* <1d3cd7> ../cstrike/dlls/weapons.cpp:1267 */
NOXREF BOOL CBasePlayerWeapon::AddSecondaryAmmo(int iCount, char *szName, int iMax)
{
	int iIdAmmo = m_pPlayer->GiveAmmo(iCount, szName, iMax);
	if (iIdAmmo > 0)
	{
		m_iSecondaryAmmoType = iIdAmmo;
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
	}
	return iIdAmmo > 0 ? TRUE : FALSE;
}

/* <1d19ba> ../cstrike/dlls/weapons.cpp:1287 */
NOBODY BOOL CBasePlayerWeapon::__MAKE_VHOOK(IsUseable)(void)
{
//	iMaxAmmo1(CBasePlayerItem *const this);  //  1291
	return FALSE;
}

/* <1d19f4> ../cstrike/dlls/weapons.cpp:1301 */
NOBODY BOOL CBasePlayerWeapon::__MAKE_VHOOK(CanDeploy)(void)
{
	return FALSE;
}

/* <1d3d7a> ../cstrike/dlls/weapons.cpp:1306 */
BOOL CBasePlayerWeapon::DefaultDeploy(char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal)
{
	if (!CanDeploy())
		return FALSE;

	m_pPlayer->TabulateAmmo();
	m_pPlayer->pev->viewmodel = MAKE_STRING(szViewModel);
	m_pPlayer->pev->weaponmodel = MAKE_STRING(szWeaponModel);
	model_name = m_pPlayer->pev->viewmodel;
	Q_strcpy(m_pPlayer->m_szAnimExtention, szAnimExt);
	SendWeaponAnim(iAnim, skiplocal);

	m_pPlayer->m_flNextAttack = 0.75f;
	m_flTimeWeaponIdle = 1.5f;
	m_flLastFireTime = 0.0f;
	m_flDecreaseShotsFired = gpGlobals->time;

	m_pPlayer->m_iFOV = 90;
	m_pPlayer->pev->fov = 90.0f;
	m_pPlayer->m_bResumeZoom = false;
	m_pPlayer->m_iLastZoom = 90;

	return TRUE;
}

/* <1d3df3> ../cstrike/dlls/weapons.cpp:1333 */
void CBasePlayerWeapon::ReloadSound(void)
{
	Vector newVector;
	Vector origin;
	CBaseEntity *pPlayer = NULL;
	float distance;

	m_pPlayer->pev->origin.CopyToArray(origin);

	while ((pPlayer = (CBasePlayer *)UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (pPlayer->IsDormant())
			break;

		if (pPlayer == m_pPlayer)
			continue;

		newVector = origin - pPlayer->pev->origin;
		distance = newVector.Length();

		if (distance <= 512.0f)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgReloadSound, NULL, pPlayer->pev);
				WRITE_BYTE((int)((1.0f - (distance / 512.0f)) * 255.0f));
			if (!Q_memcmp(STRING(pev->classname), "weapon_m3", 10) || !Q_memcmp(STRING(pev->classname), "weapon_xm1014", 14))
				WRITE_BYTE(0);
			else
				WRITE_BYTE(1);
			MESSAGE_END();
		}
	}
}

/* <1d3f0c> ../cstrike/dlls/weapons.cpp:1366 */
int CBasePlayerWeapon::DefaultReload(int iClipSize, int iAnim, float fDelay)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return FALSE;
	
	int j = _min(iClipSize - m_iClip, m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]);
	if (!j)
		return FALSE;

	m_pPlayer->m_flNextAttack = fDelay;

	ReloadSound();
	SendWeaponAnim(iAnim, UseDecrement() != FALSE);

	m_fInReload = TRUE;
	m_flTimeWeaponIdle = fDelay + 0.5f;

	return TRUE;
}

/* <1d2607> ../cstrike/dlls/weapons.cpp:1389 */
BOOL CBasePlayerWeapon::__MAKE_VHOOK(PlayEmptySound)(void)
{
	if (m_iPlayEmptySound)
	{
		if (m_iId == WEAPON_USP || m_iId == WEAPON_GLOCK18 || m_iId == WEAPON_P228 || m_iId == WEAPON_DEAGLE || m_iId == WEAPON_ELITE || m_iId == WEAPON_FIVESEVEN)
			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/dryfire_pistol.wav", 0.8, ATTN_NORM);
		else
			EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/dryfire_rifle.wav", 0.8, ATTN_NORM);
	}
	return FALSE;
}

/* <1d1a1c> ../cstrike/dlls/weapons.cpp:1414 */
void CBasePlayerWeapon::__MAKE_VHOOK(ResetEmptySound)(void)
{
	m_iPlayEmptySound = 1;
}

/* <1d1a44> ../cstrike/dlls/weapons.cpp:1421 */
NOBODY int CBasePlayerWeapon::__MAKE_VHOOK(PrimaryAmmoIndex)(void)
{
	return 0;
}

/* <1d1a6c> ../cstrike/dlls/weapons.cpp:1428 */
NOBODY int CBasePlayerWeapon::__MAKE_VHOOK(SecondaryAmmoIndex)(void)
{
	return 0;
}

/* <1d1a94> ../cstrike/dlls/weapons.cpp:1433 */
void CBasePlayerWeapon::__MAKE_VHOOK(Holster)(int skiplocal)
{
	m_fInReload = 0;
	m_pPlayer->pev->viewmodel = 0;
	m_pPlayer->pev->weaponmodel = 0;
}

/* <1d20fb> ../cstrike/dlls/weapons.cpp:1440 */
void CBasePlayerAmmo::__MAKE_VHOOK(Spawn)(void)
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;
	UTIL_SetSize(pev, Vector(-16, -16, 0), Vector(16, 16, 16));
	UTIL_SetOrigin(pev, pev->origin);

	SetTouch(&CBasePlayerAmmo::DefaultTouch);

	if (g_pGameRules->IsMultiplayer())
	{
		SetThink(&CBaseEntity::SUB_Remove);
		pev->nextthink = gpGlobals->time + 2.0f;
	}
}

/* <1d1d10> ../cstrike/dlls/weapons.cpp:1458 */
CBaseEntity *CBasePlayerAmmo::__MAKE_VHOOK(Respawn)(void)
{
	pev->effects |= EF_NODRAW;
	SetTouch(NULL);

	UTIL_SetOrigin(pev, g_pGameRules->VecAmmoRespawnSpot(this));

	SetThink(&CBasePlayerAmmo::Materialize);
	pev->nextthink = g_pGameRules->FlAmmoRespawnTime(this);

	return this;
}

/* <1d1de0> ../cstrike/dlls/weapons.cpp:1471 */
void CBasePlayerAmmo::Materialize(void)
{
	if (pev->effects & EF_NODRAW)
	{
		if (g_pGameRules->IsMultiplayer())
		{
			EMIT_SOUND_DYN(ENT(pev), CHAN_WEAPON, "items/suitchargeok1.wav", VOL_NORM, ATTN_NORM, 0, 150);
		}

		pev->effects &= ~EF_NODRAW;
		pev->effects |= EF_MUZZLEFLASH;
	}
	SetTouch(&CBasePlayerAmmo::DefaultTouch);
}

/* <1d1e94> ../cstrike/dlls/weapons.cpp:1488 */
void CBasePlayerAmmo::DefaultTouch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	if (AddAmmo(pOther))
	{
		if (g_pGameRules->AmmoShouldRespawn(this) == GR_AMMO_RESPAWN_YES)
		{
			Respawn();
		}
		else
		{
			SetTouch(NULL);
			SetThink(&CBaseEntity::SUB_Remove);
			pev->nextthink = gpGlobals->time + 0.1f;
		}
	}
	else if (gEvilImpulse101)
	{
		SetTouch(NULL);
		SetThink(&CBaseEntity::SUB_Remove);
		pev->nextthink = gpGlobals->time + 0.1f;
	}
}

/* <1d3bc3> ../cstrike/dlls/weapons.cpp:1525 */
int CBasePlayerWeapon::__MAKE_VHOOK(ExtractAmmo)(CBasePlayerWeapon *pWeapon)
{
	int iReturn = 0;
	if (pszAmmo1())
	{
		iReturn = pWeapon->AddPrimaryAmmo(m_iDefaultAmmo, (char *)pszAmmo1(), iMaxClip(), iMaxAmmo1());
		m_iDefaultAmmo = 0;
	}
	if (pszAmmo2())
		iReturn = AddSecondaryAmmo(0, (char *)pszAmmo2(), iMaxAmmo2());

	return iReturn;
}

/* <1d1acc> ../cstrike/dlls/weapons.cpp:1548 */
int CBasePlayerWeapon::__MAKE_VHOOK(ExtractClipAmmo)(CBasePlayerWeapon *pWeapon)
{
	int iAmmo;
	if (m_iClip == WEAPON_NOCLIP)
		iAmmo = 0;
	else
		iAmmo = m_iClip;

	return pWeapon->m_pPlayer->GiveAmmo(iAmmo, (char *)pszAmmo1(), iMaxAmmo1());
}

/* <1d1b2e> ../cstrike/dlls/weapons.cpp:1567 */
NOBODY void CBasePlayerWeapon::__MAKE_VHOOK(RetireWeapon)(void)
{

}

// GetNextAttackDelay - An accurate way of calcualting the next attack time.

/* <1d3f76> ../cstrike/dlls/weapons.cpp:1580 */
float CBasePlayerWeapon::GetNextAttackDelay(float delay)
{
	if (m_flLastFireTime == 0.0f || m_flNextPrimaryAttack == -1.0f)
	{
		// At this point, we are assuming that the client has stopped firing
		// and we are going to reset our book keeping variables.
		m_flPrevPrimaryAttack = delay;
		m_flLastFireTime = gpGlobals->time;
	}

#ifdef REGAMEDLL_BUILD_6153

	// TODO: Build 6xxx
	// at build 6153 beta this removed
	// maybe it was initiated due to the delay of the shot

	// calculate the time between this shot and the previous
	float flTimeBetweenFires = gpGlobals->time - m_flLastFireTime;
	float flCreep = 0.0f;

	if (flTimeBetweenFires > 0.0f)
		flCreep = flTimeBetweenFires - m_flPrevPrimaryAttack;

	float flNextAttack = delay - flCreep + 0.0f;
#else
	float flNextAttack = delay + 0.0f;
#endif // REGAMEDLL_BUILD_6153

	// save the last fire time
	m_flLastFireTime = gpGlobals->time;

	// we need to remember what the m_flNextPrimaryAttack time is set to for each shot, 
	// store it as m_flPrevPrimaryAttack.
	m_flPrevPrimaryAttack = flNextAttack;

	return flNextAttack;
}

/* <1d3fe8> ../cstrike/dlls/weapons.cpp:1614 */
LINK_ENTITY_TO_CLASS(weaponbox, CWeaponBox);

/* <1d2002> ../cstrike/dlls/weapons.cpp:1624 */
IMPLEMENT_SAVERESTORE(CWeaponBox, CBaseEntity);

/* <1d1b57> ../cstrike/dlls/weapons.cpp:1629 */
NOBODY void CWeaponBox::__MAKE_VHOOK(Precache)(void)
{
}

/* <1d2978> ../cstrike/dlls/weapons.cpp:1636 */
NOBODY void CWeaponBox::__MAKE_VHOOK(KeyValue)(KeyValueData *pkvd)
{
//	KeyValue(CWeaponBox *const this,
//		KeyValueData *pkvd);  //  1636
}

/* <1d48ba> ../cstrike/dlls/weapons.cpp:1652 */
void CWeaponBox::BombThink(void)
{
	if (!m_bIsBomb)
		return;

	CBaseEntity *pEntity = NULL;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (!pEntity->IsPlayer() || pEntity->IsDormant())
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr((CBasePlayer *)pEntity->pev);

		if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == TERRORIST)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBombDrop, NULL, pTempPlayer->edict());
				WRITE_COORD(pev->origin.x);
				WRITE_COORD(pev->origin.y);
				WRITE_COORD(pev->origin.z);
				WRITE_BYTE(0);
			MESSAGE_END();
		}
	}

	pev->nextthink = gpGlobals->time + 1;
}

/* <1d1ce7> ../cstrike/dlls/weapons.cpp:1687 */
NOBODY void CWeaponBox::__MAKE_VHOOK(Spawn)(void)
{
}

/* <1d40c4> ../cstrike/dlls/weapons.cpp:1704 */
void CWeaponBox::Kill(void)
{
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		CBasePlayerItem *pWeapon = m_rgpPlayerItems[i];

		while (pWeapon != NULL)
		{
			pWeapon->SetThink(&CBaseEntity::SUB_Remove);
			pWeapon->pev->nextthink = gpGlobals->time + 0.1;
			pWeapon = pWeapon->m_pNext;
		}
	}
	UTIL_Remove(this);
}

/* <1d0640> ../cstrike/dlls/weapons.cpp:1732 */
NOBODY void CWeaponBox::__MAKE_VHOOK(Touch)(CBaseEntity *pOther)
{
//	{
//		class CBasePlayer *pPlayer;                          //  1751
//		int i;                                                //  1769
//		bool bRemove;                                         //  1770
//		bool bEmitSound;                                      //  1771
//		{
//			class CBasePlayerItem *pItem;                //  1779
//			{
//				class CCSBotManager *ctrl;           //  1795
//			}
//			{
//				class CBaseEntity *pEntity;          //  1839
//				class CBasePlayer *pTempPlayer;      //  1840
//				class CCSBotManager *csBots;         //  1864
//			}
//			{
//				class CBasePlayerWeapon *pGrenade;   //  1881
//				int playerGrenades;                   //  1889
//				int maxGrenades;                      //  1890
//				const char *grenadeName;            //  1891
//			}
//		}
//		{
//			int n;                                        //  1951
//		}
//	}
}

/* <1d4148> ../cstrike/dlls/weapons.cpp:1981 */
BOOL CWeaponBox::PackWeapon(CBasePlayerItem *pWeapon)
{
	if (HasWeapon(pWeapon))
		return FALSE;

	if (pWeapon->m_pPlayer)
	{
		if (pWeapon->m_pPlayer->m_pActiveItem == pWeapon)
			pWeapon->Holster();
		
		if (!pWeapon->m_pPlayer->RemovePlayerItem(pWeapon))
			return FALSE;
	}

	int iWeaponSlot = pWeapon->iItemSlot();
	if (m_rgpPlayerItems[iWeaponSlot])
	{
		pWeapon->m_pNext = m_rgpPlayerItems[iWeaponSlot];
		m_rgpPlayerItems[iWeaponSlot] = pWeapon;
	}
	else
	{
		m_rgpPlayerItems[iWeaponSlot] = pWeapon;
		pWeapon->m_pNext = NULL;
	}

	pWeapon->pev->spawnflags |= SF_NORESPAWN;
	pWeapon->pev->movetype = MOVETYPE_NONE;
	pWeapon->pev->solid = SOLID_NOT;
	pWeapon->pev->effects = EF_NODRAW;
	pWeapon->pev->modelindex = 0;
	pWeapon->pev->model = NULL;
	pWeapon->pev->owner = ENT(pev);
	pWeapon->SetThink(NULL);
	pWeapon->SetTouch(NULL);
	pWeapon->m_pPlayer = NULL;

	return TRUE;
}

/* <1d4224> ../cstrike/dlls/weapons.cpp:2036 */
int CWeaponBox::PackAmmo(int iszName, int iCount)
{
	if (!iszName)
	{
		ALERT(at_console, "NULL String in PackAmmo!\n");
		return FALSE;
	}

	int iMaxCarry = MaxAmmoCarry(iszName);
	if (iMaxCarry != -1 && iCount > 0)
	{
		GiveAmmo(iCount, (char *)STRING(iszName), iMaxCarry);
		return TRUE;
	}

	return FALSE;
}

/* <1d426b> ../cstrike/dlls/weapons.cpp:2061 */
int CWeaponBox::GiveAmmo(int iCount, char *szName, int iMax, int *pIndex)
{
	int i = 1;
	for (; i < MAX_AMMO_SLOTS && m_rgiszAmmo[i] != 0; i++)
	{
		if (!Q_stricmp(szName, STRING(m_rgiszAmmo[i])))
		{
			if (pIndex)
				*pIndex = i;

			int iAdd = _min(iCount, iMax - m_rgAmmo[i]);
			if (iCount <= 0 || iAdd > 0)
			{
				m_rgAmmo[i] += iAdd;
				return i;
			}
			return -1;
		}
	}

	if (i < MAX_AMMO_SLOTS)
	{
		if (pIndex)
			*pIndex = i;

		m_rgiszAmmo[i] = MAKE_STRING(szName);
		m_rgAmmo[i] = iCount;

		return i;
	}

	ALERT(at_console, "out of named ammo slots\n");
	return i;
}

/* <1d42d5> ../cstrike/dlls/weapons.cpp:2100 */
BOOL CWeaponBox::HasWeapon(CBasePlayerItem *pCheckItem)
{
	CBasePlayerItem *pItem = m_rgpPlayerItems[pCheckItem->iItemSlot()];
	while (pItem)
	{
		if (FClassnameIs(pItem->pev, STRING(pCheckItem->pev->classname)))
			return TRUE;

		pItem = pItem->m_pNext;
	}
	return FALSE;
}

/* <1d4354> ../cstrike/dlls/weapons.cpp:2119 */
BOOL CWeaponBox::IsEmpty(void)
{
	int i;
	for (i = 0; i < MAX_ITEM_TYPES; i++)
	{
		if (m_rgpPlayerItems[i])
			return FALSE;
	}

	for (i = 0; i < MAX_AMMO_SLOTS; i++)
	{
		if (m_rgiszAmmo[i])
			return FALSE;
	}
	return TRUE;
}

/* <1d1b7f> ../cstrike/dlls/weapons.cpp:2145 */
NOBODY void CWeaponBox::__MAKE_VHOOK(SetObjectCollisionBox)(void)
{
//	operator+(const Vector ::SetObjectCollisionBox(//			const Vector &v);  //  2147
//	operator+(const Vector *const this,
//			const Vector &v);  //  2148
}

/* <1d1d39> ../cstrike/dlls/weapons.cpp:2167 */
NOBODY void CArmoury::Spawn(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //  2172
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //  2172
}

/* <1d1bfb> ../cstrike/dlls/weapons.cpp:2207 */
NOBODY void CArmoury::Restart(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  2209
//		{
//			float flRatio;                                //  2257
//		}
//		{
//			float flRatio;                                //  2239
//		}
//		{
//			float flRatio;                                //  2221
//		}
//	}
}

/* <1d1ee9> ../cstrike/dlls/weapons.cpp:2268 */
NOBODY void CArmoury::Precache(void)
{
//	Precache(CArmoury *const this);  //  2268
}

/* <1d1f2f> ../cstrike/dlls/weapons.cpp:2294 */
NOBODY void CArmoury::ArmouryTouch(CBaseEntity *pOther)
{
//	{
//		class CBasePlayer *p;                                //  2299
//	}
//	ArmouryTouch(CArmoury *const this,
//			class CBaseEntity *pOther);  //  2294
}

/* <1d21bd> ../cstrike/dlls/weapons.cpp:2352 */
NOBODY void CArmoury::KeyValue(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2354
//	FStrEq(const char *sz1,
//		const char *sz2);  //  2359
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //  2364
//	atoi(const char *__nptr);  //  2356
//	KeyValue(CArmoury *const this,
//		KeyValueData *pkvd);  //  2352
}

/* <1d4392> ../cstrike/dlls/weapons.cpp:2368 */
LINK_ENTITY_TO_CLASS(armoury_entity, CArmoury);

#ifdef HOOK_GAMEDLL

void CBasePlayerAmmo::Spawn(void)
{
	Spawn_();
}

CBaseEntity *CBasePlayerAmmo::Respawn(void)
{
	return Respawn_();
}

int CBasePlayerWeapon::Save(CSave &save)
{
	return Save_(save);
}

int CBasePlayerWeapon::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CBasePlayerWeapon::AddToPlayer(CBasePlayer *pPlayer)
{
	return AddToPlayer_(pPlayer);
}

int CBasePlayerWeapon::AddDuplicate(CBasePlayerItem *pItem)
{
	return AddDuplicate_(pItem);
}

BOOL CBasePlayerWeapon::CanDeploy(void)
{
	return CanDeploy_();
}

void CBasePlayerWeapon::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CBasePlayerWeapon::ItemPostFrame(void)
{
	ItemPostFrame_();
}

int CBasePlayerWeapon::PrimaryAmmoIndex(void)
{
	return PrimaryAmmoIndex_();
}

int CBasePlayerWeapon::SecondaryAmmoIndex(void)
{
	return SecondaryAmmoIndex_();
}

int CBasePlayerWeapon::UpdateClientData(CBasePlayer *pPlayer)
{
	return UpdateClientData_(pPlayer);
}

int CBasePlayerWeapon::ExtractAmmo(CBasePlayerWeapon *pWeapon)
{
	return ExtractAmmo_(pWeapon);
}

int CBasePlayerWeapon::ExtractClipAmmo(CBasePlayerWeapon *pWeapon)
{
	return ExtractClipAmmo_(pWeapon);
}

BOOL CBasePlayerWeapon::PlayEmptySound(void)
{
	return PlayEmptySound_();
}

void CBasePlayerWeapon::ResetEmptySound(void)
{
	ResetEmptySound_();
}

void CBasePlayerWeapon::SendWeaponAnim(int iAnim,int skiplocal)
{
	SendWeaponAnim_(iAnim,skiplocal);
}

BOOL CBasePlayerWeapon::IsUseable(void)
{
	return IsUseable_();
}

void CBasePlayerWeapon::RetireWeapon(void)
{
	RetireWeapon_();
}

int CBasePlayerItem::Save(CSave &save)
{
	return Save_(save);
}

int CBasePlayerItem::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBasePlayerItem::SetObjectCollisionBox(void)
{
	SetObjectCollisionBox_();
}

CBaseEntity *CBasePlayerItem::Respawn(void)
{
	return Respawn_();
}

int CBasePlayerItem::AddToPlayer(CBasePlayer *pPlayer)
{
	return AddToPlayer_(pPlayer);
}

void CBasePlayerItem::Holster(int skiplocal)
{
	Holster_(skiplocal);
}

void CBasePlayerItem::Drop(void)
{
	Drop_();
}

void CBasePlayerItem::Kill(void)
{
	Kill_();
}

void CBasePlayerItem::AttachToPlayer(CBasePlayer *pPlayer)
{
	AttachToPlayer_(pPlayer);
}

void CWeaponBox::Spawn(void)
{
	Spawn_();
}

void CWeaponBox::Precache(void)
{
	Precache_();
}

void CWeaponBox::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CWeaponBox::Save(CSave &save)
{
	return Save_(save);
}

int CWeaponBox::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CWeaponBox::SetObjectCollisionBox(void)
{
	SetObjectCollisionBox_();
}

void CWeaponBox::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

#endif // HOOK_GAMEDLL
