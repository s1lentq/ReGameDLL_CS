#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

// Just add more items to the bottom of this array and they will automagically be supported
// This is done instead of just a classname in the FGD so we can control which entities can
// be spawned, and still remain fairly flexible
const char *CBreakable::pSpawnObjects[] =
{
	NULL,
	"item_battery",
	"item_healthkit",
	"weapon_9mmhandgun",
	"ammo_9mmclip",
	"weapon_9mmAR",
	"ammo_9mmAR",
	"ammo_ARgrenades",
	"weapon_shotgun",
	"ammo_buckshot",
	"weapon_crossbow",
	"ammo_crossbow",
	"weapon_357",
	"ammo_357",
	"weapon_rpg",
	"ammo_rpgclip",
	"ammo_gaussclip",
	"weapon_handgrenade",
	"weapon_tripmine",
	"weapon_satchel",
	"weapon_snark",
	"weapon_hornetgun",
	"weapon_usp",
	"weapon_glock18",
	"weapon_awp",
	"weapon_mp5n",
	"weapon_m249",
	"weapon_m3",
	"weapon_m4a1",
	"weapon_tmp",
	"weapon_g3sg1",
	"weapon_flashbang"
};

const char *CBreakable::pSoundsWood[] =
{
	"debris/wood1.wav",
	"debris/wood2.wav",
	"debris/wood3.wav",
};

const char *CBreakable::pSoundsFlesh[] =
{
	"debris/flesh1.wav",
	"debris/flesh2.wav",
	"debris/flesh3.wav",
	"debris/flesh5.wav",
	"debris/flesh6.wav",
	"debris/flesh7.wav",
};

const char *CBreakable::pSoundsMetal[] =
{
	"debris/metal1.wav",
	"debris/metal2.wav",
	"debris/metal3.wav",
};

const char *CBreakable::pSoundsConcrete[] =
{
	"debris/concrete1.wav",
	"debris/concrete2.wav",
	"debris/concrete3.wav",
};

const char *CBreakable::pSoundsGlass[] =
{
	"debris/glass1.wav",
	"debris/glass2.wav",
	"debris/glass3.wav",
};

char *CPushable::m_soundNames[] =
{
	"debris/pushbox1.wav",
	"debris/pushbox2.wav",
	"debris/pushbox3.wav"
};

TYPEDESCRIPTION CBreakable::m_SaveData[] =
{
	DEFINE_FIELD(CBreakable, m_Material, FIELD_INTEGER),
	DEFINE_FIELD(CBreakable, m_Explosion, FIELD_INTEGER),
	DEFINE_FIELD(CBreakable, m_angle, FIELD_FLOAT),
	DEFINE_FIELD(CBreakable, m_iszGibModel, FIELD_STRING),
	DEFINE_FIELD(CBreakable, m_iszSpawnObject, FIELD_STRING),
};

TYPEDESCRIPTION CPushable::m_SaveData[] =
{
	DEFINE_FIELD(CPushable, m_maxSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CPushable, m_soundTime, FIELD_TIME),
};

#else // HOOK_GAMEDLL

const char *(*CBreakable::ppSpawnObjects)[32];

const char *(*CBreakable::ppSoundsWood)[3];
const char *(*CBreakable::ppSoundsFlesh)[6];
const char *(*CBreakable::ppSoundsMetal)[3];
const char *(*CBreakable::ppSoundsConcrete)[3];
const char *(*CBreakable::ppSoundsGlass)[3];

char *(*CPushable::pm_soundNames)[3];

TYPEDESCRIPTION (*CBreakable::pm_SaveData)[5];
TYPEDESCRIPTION (*CPushable::pm_SaveData)[2];

#endif // HOOK_GAMEDLL

/* <85bf3> ../cstrike/dlls/func_break.cpp:76 */
NOBODY void CBreakable::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    90
//	FStrEq(const char *sz1,
//		const char *sz2);  //   103
//	FStrEq(const char *sz1,
//		const char *sz2);  //   107
//	FStrEq(const char *sz1,
//		const char *sz2);  //   112
//	FStrEq(const char *sz1,
//		const char *sz2);  //   117
//	FStrEq(const char *sz1,
//		const char *sz2);  //   124
//	FStrEq(const char *sz1,
//		const char *sz2);  //   129
//	{
//		int object;                                           //   119
//		atoi(const char *__nptr);  //   119
//	}
//	atoi(const char *__nptr);  //   126
//	ExplosionSetMagnitude(CBreakable *const this,
//				int magnitude);  //   126
//	{
//		int i;                                                //    92
//		atoi(const char *__nptr);  //    92
//	}
}

/* <86426> ../cstrike/dlls/func_break.cpp:139 */
LINK_ENTITY_TO_CLASS(func_breakable, CBreakable);

/* <85b30> ../cstrike/dlls/func_break.cpp:155 */
IMPLEMENT_SAVERESTORE(CBreakable, CBaseEntity);

/* <85663> ../cstrike/dlls/func_break.cpp:157 */
NOBODY void CBreakable::Spawn_(void)
{
}

/* <8568a> ../cstrike/dlls/func_break.cpp:191 */
NOBODY void CBreakable::Restart_(void)
{
}

/* <864f1> ../cstrike/dlls/func_break.cpp:260 */
const char **CBreakable::MaterialSoundList(Materials precacheMaterial, int &soundCount)
{
	const char **pSoundList = NULL;

	switch (precacheMaterial)
	{
		case matWood:
		{
			pSoundList = pSoundsWood;
			soundCount = ARRAYSIZE(pSoundsWood);
			const int dad = ARRAYSIZE(pSoundsConcrete);
			break;
		}
		case matFlesh:
		{
			pSoundList = pSoundsFlesh;
			soundCount = ARRAYSIZE(pSoundsFlesh);
			break;
		}
		case matComputer:
		case matUnbreakableGlass:
		case matGlass:
		{
			pSoundList = pSoundsGlass;
			soundCount = ARRAYSIZE(pSoundsGlass);
			break;
		}
		case matMetal:
		{
			pSoundList = pSoundsMetal;
			soundCount = ARRAYSIZE(pSoundsMetal);
			break;
		}
		case matCinderBlock:
		case matRocks:
		{
			pSoundList = pSoundsConcrete;
			soundCount = ARRAYSIZE(pSoundsConcrete);
			break;
		}
		case matCeilingTile:
		case matNone:
		default:
			soundCount = 0;
			break;
	}
	return pSoundList;
}

/* <86526> ../cstrike/dlls/func_break.cpp:303 */
NOBODY void CBreakable::MaterialSoundPrecache(Materials precacheMaterial)
{
//	{
//		const char ** pSoundList;                           //   305
//		int i;                                                //   306
//		int soundCount;                                       //   306
//		MaterialSoundList(Materials precacheMaterial,
//					int &soundCount);  //   308
//	}
}

/* <86598> ../cstrike/dlls/func_break.cpp:316 */
void CBreakable::MaterialSoundRandom(edict_t *pEdict, Materials soundMaterial, float volume)
{
	int soundCount = 0;
	const char **pSoundList = MaterialSoundList(soundMaterial, soundCount);

	if (soundCount)
		EMIT_SOUND(pEdict, CHAN_BODY, pSoundList[ RANDOM_LONG(0, soundCount - 1) ], volume, 1.0);
}

/* <8634b> ../cstrike/dlls/func_break.cpp:328 */
NOBODY void CBreakable::Precache_(void)
{
//	{
//		const char *pGibName;                               //   330
//		MaterialSoundPrecache(Materials precacheMaterial);  //   386
//	}
}

/* <86676> ../cstrike/dlls/func_break.cpp:401 */
NOBODY void CBreakable::DamageSound(void)
{
//	{
//		int pitch;                                            //   403
//		float fvol;                                           //   404
//		char *rgpsz;                                         //   405
//		int i;                                                //   406
//		int material;                                         //   407
//	}
}

/* <8691c> ../cstrike/dlls/func_break.cpp:475 */
NOBODY void CBreakable::BreakTouch(CBaseEntity *pOther)
{
//	{
//		float flDamage;                                       //   477
//		entvars_t *pevToucher;                               //   478
//		Length(const Vector *const this);  //   500
//	}
}

/* <85f2d> ../cstrike/dlls/func_break.cpp:538 */
NOBODY void CBreakable::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CBreakable *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   538
}

/* <85964> ../cstrike/dlls/func_break.cpp:554 */
NOBODY void CBreakable::TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
//	{
//		float flVolume;                                       //   565
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   568
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //   569
//	}
//	Vector(Vector *const this,
//		const Vector &v);  //   580
}

/* <86719> ../cstrike/dlls/func_break.cpp:588 */
NOBODY int CBreakable::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		Vector vecTemp;                                 //   590
//		operator*(const Vector *const this,
//				float fl);  //   606
//		operator+(const Vector *const this,
//				const Vector &v);  //   606
//		operator-(const Vector *const this,
//				const Vector &v);  //   606
//		Normalize(const Vector *const this);  //   621
//		operator*(const Vector *const this,
//				float fl);  //   596
//		operator+(const Vector *const this,
//				const Vector &v);  //   596
//		operator-(const Vector *const this,
//				const Vector &v);  //   596
//	}
}

/* <856fe> ../cstrike/dlls/func_break.cpp:653 */
NOBODY void CBreakable::Die(void)
{
//	{
//		Vector vecSpot;                                 //   655
//		Vector vecVelocity;                             //   656
//		class CBaseEntity *pEntity;                          //   657
//		char cFlag;                                           //   658
//		int pitch;                                            //   659
//		float fvol;                                           //   660
//		float size;                                           //   790
//		Vector mins;                                    //   798
//		Vector maxs;                                    //   799
//		class CBaseEntity *pList;                            //   804
//		int count;                                            //   805
//		operator+(const Vector *const this,
//				const Vector &v);  //   755
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //   756
//		operator*(const Vector *const this,
//				float fl);  //   755
//		operator+(const Vector *const this,
//				const Vector &v);  //   755
//		Vector(Vector *const this,
//			const Vector &v);  //   798
//		Vector(Vector *const this,
//			const Vector &v);  //   799
//		{
//			int i;                                        //   808
//		}
//		Explodable(CBreakable *const this);  //   825
//		edict(CBaseEntity *const this);  //   827
//		operator*(const Vector *const this,
//				float fl);  //   747
//		edict(CBaseEntity *const this);  //   822
//	}
}

/* <86992> ../cstrike/dlls/func_break.cpp:833 */
NOBODY BOOL CBreakable::IsBreakable(void)
{
}

/* <85a99> ../cstrike/dlls/func_break.cpp:839 */
NOBODY int CBreakable::DamageDecal_(int bitsDamageType)
{
//	DamageDecal(CBreakable *const this,
//			int bitsDamageType);  //   839
}

/* <869b4> ../cstrike/dlls/func_break.cpp:888 */
LINK_ENTITY_TO_CLASS(func_pushable, CPushable);

/* <85e0b> ../cstrike/dlls/func_break.cpp:886 */
IMPLEMENT_SAVERESTORE(CPushable, CBreakable);

/* <856d7> ../cstrike/dlls/func_break.cpp:893 */
NOBODY void CPushable::Spawn_(void)
{
}

/* <863eb> ../cstrike/dlls/func_break.cpp:920 */
NOBODY void CPushable::Precache_(void)
{
//	{
//		int i;                                                //   922
//	}
}

/* <85fa3> ../cstrike/dlls/func_break.cpp:930 */
NOBODY void CPushable::KeyValue_(KeyValueData *pkvd)
{
//	{
//		int bbox;                                             //   934
//	}
//	FStrEq(const char *sz1,
//		const char *sz2);  //   932
//	FStrEq(const char *sz1,
//		const char *sz2);  //   958
//	KeyValue(CBreakable *const this,
//		KeyValueData *pkvd);  //   964
//	atof(const char *__nptr);  //   960
//	KeyValue(CPushable *const this,
//		KeyValueData *pkvd);  //   930
}

/* <86c0d> ../cstrike/dlls/func_break.cpp:969 */
NOBODY void CPushable::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	Use(CPushable *const this,
//		class CBaseEntity *pActivator,
//		class CBaseEntity *pCaller,
//		USE_TYPE useType,
//		float value);  //   969
//	operator!=(const Vector *const this,
//			const Vector &v);  //   978
}

/* <86b99> ../cstrike/dlls/func_break.cpp:983 */
NOBODY void CPushable::Touch_(CBaseEntity *pOther)
{
//	FClassnameIs(entvars_t *pev,
//			const char *szClassname);  //   985
}

/* <86a82> ../cstrike/dlls/func_break.cpp:992 */
NOBODY void CPushable::Move(CBaseEntity *pOther, int push)
{
//	{
//		entvars_t *pevToucher;                               //   994
//		int playerTouch;                                      //   995
//		float factor;                                         //  1015
//		float length;                                         //  1035
//		VARS(edict_t *pent);  //   998
//		STOP_SOUND(edict_t *entity,
//				int channel,
//				const char *sample);  //  1056
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  1051
//	}
}

/* <868b0> ../cstrike/dlls/func_break.cpp:1061 */
NOBODY int CPushable::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	TakeDamage(CPushable *const this,
//			entvars_t *pevInflictor,
//			entvars_t *pevAttacker,
//			float flDamage,
//			int bitsDamageType);  //  1061
}

#ifdef HOOK_GAMEDLL

void CBreakable::Spawn(void)
{
	Spawn_();
}

void CBreakable::Precache(void)
{
	Precache_();
}

void CBreakable::Restart(void)
{
	Restart_();
}

void CBreakable::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CBreakable::Save(CSave &save)
{
	return Save_(save);
}

int CBreakable::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CBreakable::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	TraceAttack_(pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}

int CBreakable::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

int CBreakable::DamageDecal(int bitsDamageType)
{
	return DamageDecal_(bitsDamageType);
}

void CBreakable::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CPushable::Spawn(void)
{
	Spawn_();
}

void CPushable::Precache(void)
{
	Precache_();
}

void CPushable::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CPushable::Save(CSave &save)
{
	return Save_(save);
}

int CPushable::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CPushable::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
	return TakeDamage_(pevInflictor, pevAttacker, flDamage, bitsDamageType);
}

void CPushable::Touch(CBaseEntity *pOther)
{
	Touch_(pOther);
}

void CPushable::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

#endif // HOOK_GAMEDLL
