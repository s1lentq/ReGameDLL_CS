#include "precompiled.h"

/* <23556d> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_ak47, CAK47);

/* <235327> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:52 */
NOBODY void CAK47::__MAKE_VHOOK(Spawn)(void)
{
}

/* <235280> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:66 */
NOBODY void CAK47::__MAKE_VHOOK(Precache)(void)
{
}

/* <2352a7> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:82 */
NOBODY int CAK47::__MAKE_VHOOK(GetItemInfo)(ItemInfo *p)
{
}

/* <235300> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:99 */
NOBODY BOOL CAK47::__MAKE_VHOOK(Deploy)(void)
{
}

/* <2352da> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:108 */
NOBODY void CAK47::__MAKE_VHOOK(SecondaryAttack)(void)
{
}

/* <235523> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:112 */
NOBODY void CAK47::__MAKE_VHOOK(PrimaryAttack)(void)
{
//	Length2D(const Vector *const this);  //   116
//	PrimaryAttack(CAK47 *const this);  //   112
}

/* <235637> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:123 */
NOBODY void CAK47::AK47Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
//	{
//		Vector vecAiming;                               //   158
//		Vector vecSrc;                                  //   160
//		Vector vecDir;                                  //   162
//		int flag;                                             //   165
//		operator+(const Vector *const this,
//				const Vector &v);  //   157
//		Vector(Vector *const this,
//			const Vector &v);  //   163
//		Vector(Vector *const this,
//			const Vector &v);  //   163
//		Length2D(const Vector *const this);  //   193
//	}
}

/* <2353d8> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:204 */
NOBODY void CAK47::__MAKE_VHOOK(Reload)(void)
{
//	Reload(CAK47 *const this);  //   204
}

/* <23539d> ../cstrike/dlls/wpn_shared/wpn_ak47.cpp:219 */
NOBODY void CAK47::__MAKE_VHOOK(WeaponIdle)(void)
{
//	WeaponIdle(CAK47 *const this);  //   219
}

#ifdef HOOK_GAMEDLL

void CAK47::Spawn(void)
{
	Spawn_();
}

void CAK47::Precache(void)
{
	Precache_();
}

int CAK47::GetItemInfo(ItemInfo *p)
{
	return GetItemInfo_(p);
}

BOOL CAK47::Deploy(void)
{
	return Deploy_();
}

void CAK47::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CAK47::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CAK47::Reload(void)
{
	Reload_();
}

void CAK47::WeaponIdle(void)
{
	WeaponIdle_();
}

#endif // HOOK_GAMEDLL
