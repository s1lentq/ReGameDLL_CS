#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBaseDoor::m_SaveData[] =
{
	DEFINE_FIELD(CBaseDoor, m_bHealthValue, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bMoveSnd, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bStopSnd, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bLockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bLockedSentence, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bUnlockedSound, FIELD_CHARACTER),
	DEFINE_FIELD(CBaseDoor, m_bUnlockedSentence, FIELD_CHARACTER),
};

TYPEDESCRIPTION CMomentaryDoor::m_SaveData[] =
{
	DEFINE_FIELD(CMomentaryDoor, m_bMoveSnd, FIELD_CHARACTER),
};

#else

TYPEDESCRIPTION (*CBaseDoor::m_SaveData)[7];
TYPEDESCRIPTION (*CMomentaryDoor::m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <693c0> ../cstrike/dlls/doors.cpp:98 */
IMPLEMENT_SAVERESTORE(CBaseDoor, CBaseToggle);

/* <68561> ../cstrike/dlls/doors.cpp:112 */
NOBODY void PlayLockSounds(entvars_t *pev, locksound_t *pls, int flocked, int fbutton)
{
//	{
//		float flsoundwait;                                    //   118
//		{
//			int fplaysound;                               //   127
//			int fplaysentence;                            //   128
//			float fvol;                                   //   129
//			{
//				int iprev;                            //   148
//			}
//		}
//		{
//			int fplaysound;                               //   164
//			int fplaysentence;                            //   165
//			float fvol;                                   //   166
//			{
//				int iprev;                            //   184
//			}
//		}
//	}
}

/* <69a4f> ../cstrike/dlls/doors.cpp:201 */
NOBODY void CBaseDoor::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   204
//	FStrEq(const char *sz1,
//		const char *sz2);  //   209
//	KeyValue(CBaseDoor *const this,
//		KeyValueData *pkvd);  //   201
//	atof(const char *__nptr);  //   206
//	atof(const char *__nptr);  //   211
}

/* <69f8b> ../cstrike/dlls/doors.cpp:278 */
LINK_ENTITY_TO_CLASS(func_door, CBaseDoor);

/* <6a058> ../cstrike/dlls/doors.cpp:282 */
LINK_ENTITY_TO_CLASS(func_water, CBaseDoor);

/* <690bc> ../cstrike/dlls/doors.cpp:285 */
NOBODY void CBaseDoor::Spawn_(void)
{
//	fabs(double __x);  //   312
//	fabs(double __x);  //   312
//	fabs(double __x);  //   312
//	operator*(const Vector *const this,
//			float fl);  //   312
//	operator+(const Vector *const this,
//			const Vector &v);  //   312
}

/* <69949> ../cstrike/dlls/doors.cpp:334 */
NOBODY void CBaseDoor::Restart_(void)
{
}

/* <69289> ../cstrike/dlls/doors.cpp:350 */
NOBODY void CBaseDoor::SetToggleState_(int state)
{
//	SetToggleState(CBaseDoor *const this,
//			int state);  //   350
}

#define noiseMoving noise1
#define noiseArrived noise2

/* <6924c> ../cstrike/dlls/doors.cpp:359 */
NOBODY void CBaseDoor::Precache_(void)
{
//	{
//		char *pszSound;                                      //   361
//	}
}

/* <6a3b8> ../cstrike/dlls/doors.cpp:508 */
NOBODY void CBaseDoor::DoorTouch(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevToucher;                               //   510
//	}
//	DoorTouch(CBaseDoor *const this,
//			class CBaseEntity *pOther);  //   508
}

/* <6a33b> ../cstrike/dlls/doors.cpp:543 */
NOBODY void CBaseDoor::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	DoorActivate(CBaseDoor *const this);  //   548
}

/* <6a319> ../cstrike/dlls/doors.cpp:554 */
NOBODY int CBaseDoor::DoorActivate(void)
{
}

/* <6a125> ../cstrike/dlls/doors.cpp:588 */
NOBODY void CBaseDoor::DoorGoUp(void)
{
//	{
//		entvars_t *pevActivator;                             //   590
//		bool isReversing;                                     //   596
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   604
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   613
//		{
//			float sign;                                   //   615
//			{
//				class Vector2D toActivator;           //   626
//				float loX;                            //   628
//				float loY;                            //   629
//				float hiX;                            //   630
//				float hiY;                            //   631
//				float momentArmX;                     //   633
//				float momentArmY;                     //   634
//			}
//			operator*(const Vector *const this,
//					float fl);  //   712
//		}
//		Vector(Vector *const this,
//			const Vector &v);  //   715
//	}
}

/* <6940c> ../cstrike/dlls/doors.cpp:721 */
NOBODY void CBaseDoor::DoorHitTop(void)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   725
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   726
}

/* <697ad> ../cstrike/dlls/doors.cpp:762 */
NOBODY void CBaseDoor::DoorGoDown(void)
{
//	{
//		bool isReversing;                                     //   765
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   770
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   782
//		Vector(Vector *const this,
//			const Vector &v);  //   785
//		Vector(Vector *const this,
//			const Vector &v);  //   783
//	}
}

/* <694a5> ../cstrike/dlls/doors.cpp:791 */
NOBODY void CBaseDoor::DoorHitBottom(void)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   795
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   796
}

/* <6a465> ../cstrike/dlls/doors.cpp:817 */
NOBODY void CBaseDoor::Blocked_(CBaseEntity *pOther)
{
//	{
//		edict_t *pentTarget;                                 //   819
//		class CBaseDoor *pDoor;                              //   820
//		float const checkBlockedInterval;                      //   827
//	}
//	Blocked(CBaseDoor *const this,
//		class CBaseEntity *pOther);  //   817
}

/* <6a767> ../cstrike/dlls/doors.cpp:943 */
LINK_ENTITY_TO_CLASS(func_door_rotating, CRotDoor);

/* <698be> ../cstrike/dlls/doors.cpp:946 */
NOBODY void CRotDoor::Restart_(void)
{
//	operator*(const Vector ::Restart(//			float fl);  //   953
//	{
//		Vector vecSav;                                  //   967
//		operator*(const Vector *const this,
//				float fl);  //   970
//	}
}

/* <69177> ../cstrike/dlls/doors.cpp:978 */
NOBODY void CRotDoor::Spawn_(void)
{
//	operator*(const class Vector  *const this,
//			float fl);  //   986
//	operator*(const Vector *const this,
//			float fl);  //   990
//	operator+(const Vector *const this,
//			const Vector &v);  //   990
//	{
//		Vector vecSav;                                  //  1011
//		operator*(const Vector *const this,
//				float fl);  //  1014
//	}
}

/* <68fcc> ../cstrike/dlls/doors.cpp:1028 */
NOBODY void CRotDoor::SetToggleState_(int state)
{
}

/* <6a834> ../cstrike/dlls/doors.cpp:1056 */
LINK_ENTITY_TO_CLASS(momentary_door, CMomentaryDoor);

/* <69373> ../cstrike/dlls/doors.cpp:1063 */
IMPLEMENT_SAVERESTORE(CMomentaryDoor, CBaseToggle);

/* <69001> ../cstrike/dlls/doors.cpp:1065 */
NOBODY void CMomentaryDoor::Spawn_(void)
{
//	fabs(double __x);  //  1082
//	fabs(double __x);  //  1082
//	fabs(double __x);  //  1082
//	operator*(const Vector *const this,
//			float fl);  //  1082
//	operator+(const Vector *const this,
//			const Vector &v);  //  1082
}

/* <68fa5> ../cstrike/dlls/doors.cpp:1096 */
NOBODY void CMomentaryDoor::Precache_(void)
{
}

/* <69970> ../cstrike/dlls/doors.cpp:1143 */
NOBODY void CMomentaryDoor::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1146
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1151
//	FStrEq(const char *sz1,
//		const char *sz2);  //  1156
//	KeyValue(CMomentaryDoor *const this,
//		KeyValueData *pkvd);  //  1143
}

/* <6953e> ../cstrike/dlls/doors.cpp:1165 */
NOBODY void CMomentaryDoor::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		Vector move;                                    //  1172
//		Vector delta;                                   //  1174
//		float speed;                                          //  1175
//	}
//	Use(CMomentaryDoor *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //  1165
}

#ifdef HOOK_GAMEDLL

void CBaseDoor::Spawn(void)
{
	Spawn_();
}

void CBaseDoor::Precache(void)
{
	Precache_();
}

void CBaseDoor::Restart(void)
{
	Restart_();
}
	
void CBaseDoor::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBaseDoor::Save(CSave &save)
{
	return Save_(save);
}

int CBaseDoor::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBaseDoor::SetToggleState(int state)
{
	SetToggleState_(state);
}

void CBaseDoor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CBaseDoor::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

void CRotDoor::Spawn(void)
{
	Spawn_();
}

void CRotDoor::Restart(void)
{
	Restart_();
}

void CRotDoor::SetToggleState(int state)
{
	SetToggleState_(state);
}

void CMomentaryDoor::Spawn(void)
{
	Spawn_();
}

void CMomentaryDoor::Precache(void)
{
	Precache_();
}

void CMomentaryDoor::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CMomentaryDoor::Save(CSave &save)
{
	return Save_(save);
}

int CMomentaryDoor::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CMomentaryDoor::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
