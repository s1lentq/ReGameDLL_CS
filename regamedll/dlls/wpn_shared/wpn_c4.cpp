#include "precompiled.h"

/* <246a03> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:48 */
LINK_ENTITY_TO_CLASS(weapon_c4, CC4);

/* <2469b9> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:50 */
NOBODY void CC4::Spawn(void)
{
//	Spawn(CC4 *const this);  //    50
}

/* <246418> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:80 */
NOBODY void CC4::Precache(void)
{
}

/* <24643f> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:88 */
NOBODY int CC4::GetItemInfo(ItemInfo *p)
{
}

/* <2466d5> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:105 */
NOBODY BOOL CC4::Deploy(void)
{
}

/* <2466fc> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:123 */
NOBODY void CC4::Holster(int skiplocal)
{
//	Holster(CC4 *const this,
//		int skiplocal);  //   123
}

/* <2464e8> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:152 */
NOBODY void CC4::PrimaryAttack(void)
{
//	{
//		BOOL PlaceBomb;                                       //   154
//		class CGrenade *pBomb;                               //   155
//		int onGround;                                         //   161
//		int inBombZone;                                       //   164
//		{
//			class CBaseEntity *pEntity;                  //   288
//			class CBasePlayer *pTempPlayer;              //   289
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   277
//			Vector(Vector *const this,
//				const Vector &v);  //   277
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //   280
//			edict(CBaseEntity *const this);  //   283
//			ENTINDEX(edict_t *pEdict);  //   283
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //   293
//			edict(CBaseEntity *const this);  //   315
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //   319
//			edict(CBaseEntity *const this);  //   315
//		}
//	}
}

/* <2464c1> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:358 */
NOBODY void CC4::WeaponIdle(void)
{
}

/* <24674f> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:419 */
NOBODY void CC4::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CBasePlayer *pPlayer;                          //   423
//		edict_t *m_pentOldCurBombTarget;                     //   426
//		class CGrenade *pC4;                                 //   435
//	}
//	Use(CC4 *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   419
}

/* <2468b7> ../cstrike/dlls/wpn_shared/wpn_c4.cpp:399 */
NOBODY void CC4::KeyValue(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   401
//	FStrEq(const char *sz1,
//		const char *sz2);  //   406
//	KeyValue(CC4 *const this,
//		KeyValueData *pkvd);  //   399
//	atof(const char *__nptr);  //   403
}
