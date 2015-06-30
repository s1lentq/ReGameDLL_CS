#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CAirtank::m_SaveData[] =
{
	DEFINE_FIELD(CAirtank, m_state, FIELD_INTEGER)
};

#else

TYPEDESCRIPTION (*CAirtank::m_SaveData)[1];

#endif // HOOK_GAMEDLL

/* <4fc9> ../cstrike/dlls/airtank.cpp:29 */
int CAirtank::BloodColor_(void)
{
	return DONT_BLEED;
}

/* <5329> ../cstrike/dlls/airtank.cpp:41 */
LINK_ENTITY_TO_CLASS(item_airtank, CAirtank);

/* <5211> ../cstrike/dlls/airtank.cpp:47 */
IMPLEMENT_SAVERESTORE(CAirtank, CGrenade);

/* <50dd> ../cstrike/dlls/airtank.cpp:50 */
void CAirtank::Spawn_(void)
{
//	Vector(Vector::Spawn(//		float X,
//		float Y,
//		float Z);  //    58
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //    58
}

/* <4fef> ../cstrike/dlls/airtank.cpp:71 */
void CAirtank::Precache_(void)
{
}

/* <503d> ../cstrike/dlls/airtank.cpp:78 */
void CAirtank::Killed_(entvars_t *pevAttacker, int iGib)
{
//	Vector(Vector *const this,
//		float X,
//		float Y,
//		float Z);  //    84
//	Vector(Vector *const this,
//		const Vector &v);  //    84
}

/* <5016> ../cstrike/dlls/airtank.cpp:88 */
void CAirtank::TankThink(void)
{
}

/* <525d> ../cstrike/dlls/airtank.cpp:96 */
void CAirtank::TankTouch(CBaseEntity *pOther)
{
//	TankTouch(CAirtank *const this,
//			class CBaseEntity *pOther);  //    96
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //   104
}

#ifdef HOOK_GAMEDLL

void CAirtank::Spawn(void)
{
	Spawn_();
}

void CAirtank::Precache(void)
{
	Precache_();
}

int CAirtank::Save(CSave &save)
{
	return Save_(save);
}

int CAirtank::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CAirtank::Killed(entvars_t *pevAttacker, int iGib)
{
	Killed_(pevAttacker, iGib);
}

int CAirtank::BloodColor(void)
{
	return BloodColor_();
}

#endif // HOOK_GAMEDLL
