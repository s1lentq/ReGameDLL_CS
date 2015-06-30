#include "precompiled.h"

/* <260ef4> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:48 */
LINK_ENTITY_TO_CLASS(weapon_g3sg1, CG3SG1);

/* <260ca2> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:50 */
NOBODY void CG3SG1::Spawn(void)
{
}

/* <260b97> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:63 */
NOBODY void CG3SG1::Precache(void)
{
}

/* <260bbe> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:79 */
NOBODY int CG3SG1::GetItemInfo(ItemInfo *p)
{
}

/* <260c7b> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:96 */
NOBODY BOOL CG3SG1::Deploy(void)
{
}

/* <260c17> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:102 */
NOBODY void CG3SG1::SecondaryAttack(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   129
}

/* <260eaa> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:133 */
NOBODY void CG3SG1::PrimaryAttack(void)
{
//	Length2D(const Vector *const this);  //   137
//	PrimaryAttack(CG3SG1 *const this);  //   133
}

/* <260dab> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:145 */
NOBODY void CG3SG1::G3SG1Fire(float flSpread,float flCycleTime,BOOL fUseAutoAim)
{
//	{
//		Vector vecAiming;                               //   199
//		Vector vecSrc;                                  //   201
//		int flag;                                             //   206
//		Vector vecDir;                                  //   203
//		operator+(const Vector *const this,
//				const Vector &v);  //   193
//		Vector(Vector *const this,
//			const Vector &v);  //   204
//		Vector(Vector *const this,
//			const Vector &v);  //   204
//	}
}

/* <260d53> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:234 */
NOBODY void CG3SG1::Reload(void)
{
//	{
//		int iResult;                                          //   239
//	}
//	Reload(CG3SG1 *const this);  //   234
}

/* <260d18> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:260 */
NOBODY void CG3SG1::WeaponIdle(void)
{
//	WeaponIdle(CG3SG1 *const this);  //   260
}

/* <260bf1> ../cstrike/dlls/wpn_shared/wpn_g3sg1.cpp:277 */
NOBODY float CG3SG1::GetMaxSpeed(void)
{
}
