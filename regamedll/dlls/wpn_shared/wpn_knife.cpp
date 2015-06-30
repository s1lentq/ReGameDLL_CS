#include "precompiled.h"

/* <270ca6> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:28 */
LINK_ENTITY_TO_CLASS(weapon_knife, CKnife);

/* <270586> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:53 */
NOBODY void CKnife::Spawn(void)
{
}

/* <2704d2> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:66 */
NOBODY void CKnife::Precache(void)
{
}

/* <2704f9> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:85 */
NOBODY int CKnife::GetItemInfo(ItemInfo *p)
{
}

/* <2707c0> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:102 */
NOBODY BOOL CKnife::Deploy(void)
{
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   104
}

/* <27052b> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:119 */
NOBODY void CKnife::Holster(int skiplocal)
{
}

/* <270d70> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:124 */
NOBODY void CKnife::WeaponAnimation(int iAnimation)
{
//	{
//		int flag;                                             //   126
//		edict(CBaseEntity *const this);  //   133
//	}
}

/* <26f852> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:140 */
NOBODY void FindHullIntersection(Vector &vecSrc, TraceResult &tr, float *mins, float *maxs, edict_t *pEntity)
{
//	{
//		int i;                                                //   142
//		int j;                                                //   142
//		int k;                                                //   142
//		float distance;                                       //   143
//		float *minmaxs;                                      //   144
//		TraceResult tmpTrace;                                 //   145
//		Vector vecHullEnd;                              //   146
//		Vector vecEnd;                                  //   147
//		{
//			float thisDistance;                           //   172
//		}
//	}
}

/* <2714ba> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:185 */
NOBODY void CKnife::PrimaryAttack(void)
{
}

/* <270f18> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:190 */
NOBODY void CKnife::SetPlayerShieldAnim(void)
{
}

/* <270f53> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:201 */
NOBODY void CKnife::ResetPlayerShieldAnim(void)
{
}

/* <270f75> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:211 */
NOBODY bool CKnife::ShieldSecondaryFire(int iUpAnim, int iDownAnim)
{
}

/* <270826> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:245 */
NOBODY void CKnife::SecondaryAttack(void)
{
//	ShieldSecondaryFire(CKnife::SecondaryAttack(//				int iUpAnim,
//				int iDownAnim);  //   247
//	SecondaryAttack(CKnife *const this);  //   245
}

/* <27055f> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:254 */
NOBODY void CKnife::Smack(void)
{
}

/* <271493> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:260 */
NOBODY void CKnife::SwingAgain(void)
{
}

/* <2705fc> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:265 */
NOBODY void CKnife::WeaponIdle(void)
{
//	WeaponIdle(CKnife *const this);  //   265
}

/* <270fa7> ../cstrike/dlls/wpn_shared/wpn_knife.cpp:283 */
NOBODY int CKnife::Swing(int fFirst)
{
//	{
//		int fDidHit;                                          //   285
//		TraceResult tr;                                       //   287
//		Vector vecSrc;                                  //   290
//		Vector vecEnd;                                  //   291
//		operator*(const Vector *const this,
//				float fl);  //   291
//		operator+(const Vector *const this,
//				const Vector &v);  //   291
//		{
//			class CBaseEntity *pHit;                     //   302
//			Instance(edict_t *pent);  //   302
//			edict(CBaseEntity *const this);  //   304
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   304
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   304
//		}
//		{
//			float flVol;                                  //   379
//			int fHitWorld;                                //   380
//			class CBaseEntity *pEntity;                  //   385
//			Instance(edict_t *pent);  //   385
//			SetPlayerShieldAnim(CKnife *const this);  //   387
//			Vector(Vector *const this,
//				const Vector &v);  //   396
//			{
//				float fvolbar;                        //   436
//				operator-(const Vector *const this,
//						const Vector &v);  //   436
//				operator*(const Vector *const this,
//						float fl);  //   436
//				operator+(const Vector *const this,
//						const Vector &v);  //   436
//				Vector(Vector *const this,
//					const Vector &v);  //   436
//			}
//			ResetPlayerShieldAnim(CKnife *const this);  //   461
//			Vector(Vector *const this,
//				const Vector &v);  //   401
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //   419
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //   417
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //   415
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //   413
//		}
//	}
}
