#include "precompiled.h"

/* <281342> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:60 */
LINK_ENTITY_TO_CLASS(weapon_m4a1, CM4A1);

/* <281059> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:62 */
NOBODY void CM4A1::Spawn(void)
{
}

/* <280fb2> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:77 */
NOBODY void CM4A1::Precache(void)
{
}

/* <280fd9> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:97 */
NOBODY int CM4A1::GetItemInfo(ItemInfo *p)
{
}

/* <281169> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:114 */
NOBODY BOOL CM4A1::Deploy(void)
{
//	Deploy(CM4A1 *const this);  //   114
}

/* <281032> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:127 */
NOBODY void CM4A1::SecondaryAttack(void)
{
}

/* <2812fd> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:149 */
NOBODY void CM4A1::PrimaryAttack(void)
{
//	Length2D(const Vector *const this);  //   155
//	Length2D(const Vector *const this);  //   164
}

/* <28140c> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:173 */
NOBODY void CM4A1::M4A1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
//	{
//		Vector vecAiming;                               //   210
//		Vector vecSrc;                                  //   212
//		Vector vecDir;                                  //   213
//		int flag;                                             //   223
//		operator+(const Vector *const this,
//				const Vector &v);  //   204
//		Vector(Vector *const this,
//			const Vector &v);  //   220
//		Vector(Vector *const this,
//			const Vector &v);  //   220
//		Length2D(const Vector *const this);  //   246
//		Vector(Vector *const this,
//			const Vector &v);  //   216
//		Vector(Vector *const this,
//			const Vector &v);  //   216
//	}
}

/* <28110b> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:257 */
NOBODY void CM4A1::Reload(void)
{
//	{
//		int iResult;                                          //   262
//	}
//	Reload(CM4A1 *const this);  //   257
}

/* <2810cf> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:279 */
NOBODY void CM4A1::WeaponIdle(void)
{
//	WeaponIdle(CM4A1 *const this);  //   279
}

/* <28100c> ../cstrike/dlls/wpn_shared/wpn_m4a1.cpp:296 */
float CM4A1::GetMaxSpeed(void)
{
	return 230.0f;
}
