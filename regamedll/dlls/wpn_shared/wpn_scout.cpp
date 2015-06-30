#include "precompiled.h"

/* <29ba7b> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:48 */
LINK_ENTITY_TO_CLASS(weapon_scout, CSCOUT);

/* <29b7ee> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:50 */
NOBODY void CSCOUT::Spawn(void)
{
}

/* <29b70a> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:62 */
NOBODY void CSCOUT::Precache(void)
{
}

/* <29b731> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:79 */
NOBODY int CSCOUT::GetItemInfo(ItemInfo *p)
{
}

/* <29b8f7> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:96 */
NOBODY BOOL CSCOUT::Deploy(void)
{
//	Deploy(CSCOUT *const this);  //    96
}

/* <29b78a> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:109 */
NOBODY void CSCOUT::SecondaryAttack(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   136
}

/* <29ba31> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:140 */
NOBODY void CSCOUT::PrimaryAttack(void)
{
//	Length2D(const Vector *const this);  //   144
//	PrimaryAttack(CSCOUT *const this);  //   140
}

/* <29bb45> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:154 */
NOBODY void CSCOUT::SCOUTFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
//	{
//		Vector vecAiming;                               //   197
//		Vector vecSrc;                                  //   200
//		Vector vecDir;                                  //   202
//		int flag;                                             //   206
//		operator+(const Vector *const this,
//				const Vector &v);  //   188
//		Vector(Vector *const this,
//			const Vector &v);  //   203
//		Vector(Vector *const this,
//			const Vector &v);  //   203
//	}
}

/* <29b89e> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:232 */
NOBODY void CSCOUT::Reload(void)
{
//	{
//		int iResult;                                          //   234
//	}
//	Reload(CSCOUT *const this);  //   232
}

/* <29b864> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:250 */
NOBODY void CSCOUT::WeaponIdle(void)
{
//	WeaponIdle(CSCOUT *const this);  //   250
}

/* <29b764> ../cstrike/dlls/wpn_shared/wpn_scout.cpp:267 */
NOBODY float CSCOUT::GetMaxSpeed(void)
{
}
