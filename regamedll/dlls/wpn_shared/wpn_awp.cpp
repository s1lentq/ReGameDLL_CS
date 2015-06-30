#include "precompiled.h"

/* <23fdac> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:50 */
LINK_ENTITY_TO_CLASS(weapon_awp, CAWP);

/* <23fb10> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:52 */
NOBODY void CAWP::Spawn(void)
{
}

/* <23fa2c> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:64 */
NOBODY void CAWP::Precache(void)
{
}

/* <23fa53> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:83 */
NOBODY int CAWP::GetItemInfo(ItemInfo *p)
{
}

/* <23fc19> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:100 */
NOBODY BOOL CAWP::Deploy(void)
{
//	Deploy(CAWP *const this);  //   100
}

/* <23faac> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:113 */
NOBODY void CAWP::SecondaryAttack(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   139
}

/* <23fd53> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:143 */
NOBODY void CAWP::PrimaryAttack(void)
{
//	Length2D(const Vector *const this);  //   147
//	PrimaryAttack(CAWP *const this);  //   143
}

/* <23fe76> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:157 */
NOBODY void CAWP::AWPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
//	{
//		Vector vecAiming;                               //   205
//		Vector vecSrc;                                  //   207
//		Vector vecDir;                                  //   209
//		int flag;                                             //   212
//		operator+(const Vector *const this,
//				const Vector &v);  //   194
//		Vector(Vector *const this,
//			const Vector &v);  //   210
//		Vector(Vector *const this,
//			const Vector &v);  //   210
//	}
}

/* <23fbc1> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:239 */
NOBODY void CAWP::Reload(void)
{
//	{
//		int iResult;                                          //   244
//	}
//	Reload(CAWP *const this);  //   239
}

/* <23fb86> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:265 */
NOBODY void CAWP::WeaponIdle(void)
{
//	WeaponIdle(CAWP *const this);  //   265
}

/* <23fa86> ../cstrike/dlls/wpn_shared/wpn_awp.cpp:283 */
NOBODY float CAWP::GetMaxSpeed(void)
{
}
