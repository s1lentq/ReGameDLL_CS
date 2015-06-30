#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CRecharge::m_SaveData[] =
{
	DEFINE_FIELD(CRecharge, m_flNextCharge, FIELD_TIME),
	DEFINE_FIELD(CRecharge, m_iReactivate, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_iJuice, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_iOn, FIELD_INTEGER),
	DEFINE_FIELD(CRecharge, m_flSoundTime, FIELD_TIME),
};

#else

TYPEDESCRIPTION (*CRecharge::m_SaveData)[5];

#endif // HOOK_GAMEDLL

/* <c61e2> ../cstrike/dlls/h_battery.cpp:61 */
IMPLEMENT_SAVERESTORE(CRecharge, CBaseEntity);

/* <c65cc> ../cstrike/dlls/h_battery.cpp:63 */
LINK_ENTITY_TO_CLASS(func_recharge, CRecharge);

/* <c648b> ../cstrike/dlls/h_battery.cpp:66 */
void CRecharge::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    68
//	FStrEq(const char *sz1,
//		const char *sz2);  //    69
//	FStrEq(const char *sz1,
//		const char *sz2);  //    70
//	FStrEq(const char *sz1,
//		const char *sz2);  //    71
//	FStrEq(const char *sz1,
//		const char *sz2);  //    72
//	FStrEq(const char *sz1,
//		const char *sz2);  //    76
//	atoi(const char *__nptr);  //    78
}

/* <c616f> ../cstrike/dlls/h_battery.cpp:85 */
void CRecharge::Spawn_(void)
{
}

/* <c6122> ../cstrike/dlls/h_battery.cpp:99 */
void CRecharge::Precache_(void)
{
}

/* <c630e> ../cstrike/dlls/h_battery.cpp:107 */
void CRecharge::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	FClassnameIs(entvars_t *pev,
//			const char *szClassname);  //   110
//	Use(CRecharge *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   107
}

/* <c6149> ../cstrike/dlls/h_battery.cpp:178 */
void CRecharge::Recharge(void)
{
}

/* <c622e> ../cstrike/dlls/h_battery.cpp:185 */
void CRecharge::Off(void)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //   189
//	Off(CRecharge *const this);  //   185
}

#ifdef HOOK_GAMEDLL

void CRecharge::Spawn(void)
{
	Spawn_();
}

void CRecharge::Precache(void)
{
	Precache_();
}

void CRecharge::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CRecharge::Save(CSave &save)
{
	return Save_(save);
}

int CRecharge::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRecharge::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
