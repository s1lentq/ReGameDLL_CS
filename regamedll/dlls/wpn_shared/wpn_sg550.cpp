#include "precompiled.h"

/* <2a0f39> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:48 */
LINK_ENTITY_TO_CLASS(weapon_sg550, CSG550);

/* <2a0ce8> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:50 */
NOBODY void CSG550::Spawn(void)
{
}

/* <2a0bdd> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:63 */
NOBODY void CSG550::Precache(void)
{
}

/* <2a0c04> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:79 */
NOBODY int CSG550::GetItemInfo(ItemInfo *p)
{
}

/* <2a0cc1> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:96 */
NOBODY BOOL CSG550::Deploy(void)
{
}

/* <2a0c5d> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:101 */
NOBODY void CSG550::SecondaryAttack(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   128
}

/* <2a0eef> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:132 */
NOBODY void CSG550::PrimaryAttack(void)
{
//	Length2D(const Vector *const this);  //   136
//	PrimaryAttack(CSG550 *const this);  //   132
}

/* <2a1003> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:144 */
NOBODY void CSG550::SG550Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
//	{
//		Vector vecAiming;                               //   193
//		Vector vecSrc;                                  //   195
//		Vector vecDir;                                  //   196
//		int flag;                                             //   200
//		operator+(const Vector *const this,
//				const Vector &v);  //   187
//		Vector(Vector *const this,
//			const Vector &v);  //   197
//		Vector(Vector *const this,
//			const Vector &v);  //   197
//	}
}

/* <2a0d98> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:227 */
NOBODY void CSG550::Reload(void)
{
//	{
//		int iResult;                                          //   232
//	}
//	Reload(CSG550 *const this);  //   227
}

/* <2a0d5e> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:248 */
NOBODY void CSG550::WeaponIdle(void)
{
//	WeaponIdle(CSG550 *const this);  //   248
}

/* <2a0c37> ../cstrike/dlls/wpn_shared/wpn_sg550.cpp:265 */
NOBODY float CSG550::GetMaxSpeed(void)
{
}
