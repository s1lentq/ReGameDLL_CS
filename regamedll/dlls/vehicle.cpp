#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CFuncVehicle::m_SaveData[] =
{
	DEFINE_FIELD(CFuncVehicle, m_ppath, FIELD_CLASSPTR),
	DEFINE_FIELD(CFuncVehicle, m_length, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_height, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_speed, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_dir, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_startSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_controlMins, FIELD_VECTOR),
	DEFINE_FIELD(CFuncVehicle, m_controlMaxs, FIELD_VECTOR),
	DEFINE_FIELD(CFuncVehicle, m_sounds, FIELD_INTEGER),
	DEFINE_FIELD(CFuncVehicle, m_flVolume, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_flBank, FIELD_FLOAT),
	DEFINE_FIELD(CFuncVehicle, m_oldSpeed, FIELD_FLOAT),
};

#else

TYPEDESCRIPTION (*CFuncVehicle::pm_SaveData)[12];

#endif // HOOK_GAMEDLL

/* <1bc835> ../cstrike/dlls/vehicle.cpp:20 */
NOBODY void FixupAngles2(Vector &v)
{
}

/* <1bb2f1> ../cstrike/dlls/vehicle.cpp:54 */
IMPLEMENT_SAVERESTORE(CFuncVehicle, CBaseEntity);

/* <1bbf8f> ../cstrike/dlls/vehicle.cpp:55 */
LINK_ENTITY_TO_CLASS(func_vehicle, CFuncVehicle);

/* <1bb408> ../cstrike/dlls/vehicle.cpp:57 */
NOBODY void CFuncVehicle::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //    59
//	FStrEq(const char *sz1,
//		const char *sz2);  //    64
//	FStrEq(const char *sz1,
//		const char *sz2);  //    69
//	FStrEq(const char *sz1,
//		const char *sz2);  //    74
//	FStrEq(const char *sz1,
//		const char *sz2);  //    79
//	FStrEq(const char *sz1,
//		const char *sz2);  //    84
//	FStrEq(const char *sz1,
//		const char *sz2);  //    90
//	FStrEq(const char *sz1,
//		const char *sz2);  //    95
//	KeyValue(CBaseEntity *const this,
//		KeyValueData *pkvd);  //   105
//	atof(const char *__nptr);  //    61
//	atof(const char *__nptr);  //    66
//	atof(const char *__nptr);  //    76
//	atoi(const char *__nptr);  //    97
//	atof(const char *__nptr);  //    71
//	atoi(const char *__nptr);  //    81
//	atoi(const char *__nptr);  //    86
//	atof(const char *__nptr);  //    92
}

/* <1bc059> ../cstrike/dlls/vehicle.cpp:109 */
NOBODY void CFuncVehicle::NextThink(float thinkTime, BOOL alwaysThink)
{
}

/* <1bb9d0> ../cstrike/dlls/vehicle.cpp:120 */
NOBODY void CFuncVehicle::Blocked_(CBaseEntity *pOther)
{
//	{
//		entvars_t *pevOther;                                 //   122
//		Vector vFrontLeft;                              //   150
//		Vector vFrontRight;                             //   150
//		Vector vBackLeft;                               //   150
//		Vector vBackRight;                              //   150
//		Vector forward;                                 //   151
//		Vector right;                                   //   152
//		Vector vOrigin;                                 //   159
//		float minx;                                           //   161
//		float miny;                                           //   161
//		float minz;                                           //   161
//		float maxx;                                           //   162
//		float maxy;                                           //   162
//		float maxz;                                           //   162
//		VARS(edict_t *pent);  //   125
//		operator-(const Vector *const this,
//				const Vector &v);  //   139
//		Normalize(const Vector *const this);  //   139
//		operator*(const Vector *const this,
//				float fl);  //   139
//		operator*(const Vector *const this,
//				float fl);  //   143
//		{
//			float deltaSpeed;                             //   130
//		}
//		operator*(const Vector *const this,
//				float fl);  //   151
//		operator*(const Vector *const this,
//				float fl);  //   151
//		operator*(const Vector *const this,
//				float fl);  //   152
//		operator*(const Vector *const this,
//				float fl);  //   152
//		operator+(const Vector *const this,
//				const Vector &v);  //   154
//		operator-(const Vector *const this,
//				const Vector &v);  //   154
//		operator-(const Vector *const this,
//				const Vector &v);  //   157
//		operator+(const Vector *const this,
//				const Vector &v);  //   157
//		Vector(Vector *const this,
//			const Vector &v);  //   159
//	}
}

/* <1bcf96> ../cstrike/dlls/vehicle.cpp:179 */
NOBODY void CFuncVehicle::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	StopSound(CFuncVehicle *const this);  //   197
//	{
//		float delta;                                          //   210
//		float flSpeedRatio;                                   //   211
//		StopSound(CFuncVehicle *const this);  //   207
//	}
}

/* <1bc0bd> ../cstrike/dlls/vehicle.cpp:303 */
NOBODY void CFuncVehicle::StopSound(void)
{
//	{
//		short unsigned int us_encode;                         //   308
//		short unsigned int us_sound;                          //   309
//	}
}

/* <1bb33d> ../cstrike/dlls/vehicle.cpp:324 */
NOBODY void CFuncVehicle::UpdateSound(void)
{
//	{
//		float flpitch;                                        //   326
//		{
//			short unsigned int us_encode;                 //   355
//			short unsigned int us_sound;                  //   356
//			short unsigned int us_pitch;                  //   357
//			short unsigned int us_volume;                 //   358
//		}
//	}
}

/* <1bc12b> ../cstrike/dlls/vehicle.cpp:368 */
NOBODY void CFuncVehicle::CheckTurning(void)
{
//	{
//		float maxspeed;                                       //   370
//		TraceResult tr;                                       //   371
//		bool bTurnIntoWall;                                   //   373
//		operator*(const Vector *const this,
//				float fl);  //   398
//		operator+(const Vector *const this,
//				const Vector &v);  //   398
//		operator*(const Vector *const this,
//				float fl);  //   387
//		operator+(const Vector *const this,
//				const Vector &v);  //   387
//		operator*(const Vector *const this,
//				float fl);  //   379
//		operator-(const Vector *const this,
//				const Vector &v);  //   379
//		operator*(const Vector *const this,
//				float fl);  //   406
//		operator-(const Vector *const this,
//				const Vector &v);  //   406
//	}
}

/* <1bc358> ../cstrike/dlls/vehicle.cpp:466 */
NOBODY void CFuncVehicle::CollisionDetection(void)
{
//	{
//		TraceResult tr;                                       //   468
//		bool bHitSomething;                                   //   469
//		operator*(const Vector *const this,
//				float fl);  //   533
//		operator-(const Vector *const this,
//				const Vector &v);  //   533
//		operator*(const Vector *const this,
//				float fl);  //   551
//		operator-(const Vector *const this,
//				const Vector &v);  //   551
//		operator*(const Vector *const this,
//				float fl);  //   569
//		operator-(const Vector *const this,
//				const Vector &v);  //   569
//		DotProduct(Vector &a,
//				const Vector &b);  //   573
//		operator*(const Vector *const this,
//				float fl);  //   573
//		{
//			class CBaseEntity *pHit;                     //   490
//			DotProduct(Vector &a,
//					const Vector &b);  //   479
//			operator*(const Vector *const this,
//					float fl);  //   479
//			Instance(edict_t *pent);  //   490
//		}
//		operator*(const Vector *const this,
//				float fl);  //   496
//		operator+(const Vector *const this,
//				const Vector &v);  //   496
//		operator*(const Vector *const this,
//				float fl);  //   514
//		operator+(const Vector *const this,
//				const Vector &v);  //   514
//		DotProduct(Vector &a,
//				const Vector &b);  //   517
//		operator*(const Vector *const this,
//				float fl);  //   517
//		operator*(const Vector *const this,
//				float fl);  //   475
//		operator+(const Vector *const this,
//				const Vector &v);  //   475
//	}
}

/* <1bc7aa> ../cstrike/dlls/vehicle.cpp:588 */
NOBODY void CFuncVehicle::TerrainFollowing(void)
{
//	{
//		TraceResult tr;                                       //   590
//		operator+(const Vector *const this,
//				const Vector &v);  //   593
//	}
}

/* <1bc856> ../cstrike/dlls/vehicle.cpp:609 */
NOBODY void CFuncVehicle::Next(void)
{
//	{
//		Vector vGravityVector;                          //   611
//		Vector forward;                                 //   615
//		Vector right;                                   //   616
//		Vector up;                                      //   617
//		float time;                                           //   633
//		Vector(Vector *const this,
//			const Vector &v);  //   611
//		operator*(const Vector *const this,
//				float fl);  //   615
//		operator*(const Vector *const this,
//				float fl);  //   615
//		operator*(const Vector *const this,
//				float fl);  //   616
//		operator*(const Vector *const this,
//				float fl);  //   616
//		operator*(const Vector *const this,
//				float fl);  //   617
//		operator+(const Vector *const this,
//				const Vector &v);  //   619
//		operator-(const Vector *const this,
//				const Vector &v);  //   619
//		operator+(const Vector *const this,
//				const Vector &v);  //   619
//		operator+(const Vector *const this,
//				const Vector &v);  //   620
//		operator+(const Vector *const this,
//				const Vector &v);  //   620
//		operator+(const Vector *const this,
//				const Vector &v);  //   620
//		operator+(const Vector *const this,
//				const Vector &v);  //   621
//		operator+(const Vector *const this,
//				const Vector &v);  //   621
//		operator-(const Vector *const this,
//				const Vector &v);  //   622
//		operator-(const Vector *const this,
//				const Vector &v);  //   622
//		operator+(const Vector *const this,
//				const Vector &v);  //   622
//		operator-(const Vector *const this,
//				const Vector &v);  //   623
//		operator+(const Vector *const this,
//				const Vector &v);  //   623
//		operator+(const Vector *const this,
//				const Vector &v);  //   623
//		operator-(const Vector *const this,
//				const Vector &v);  //   624
//		operator+(const Vector *const this,
//				const Vector &v);  //   624
//		{
//			Vector temp;                            //   737
//			operator!=(const Vector *const this,
//					const Vector &v);  //   678
//			NextThink(CFuncVehicle *const this,
//					float thinkTime,
//					BOOL alwaysThink);  //   755
//			{
//				Vector vTargetAngle;            //   683
//				Vector vAngle;                  //   683
//				float vx;                             //   684
//				float vy;                             //   684
//				CrossProduct(Vector &a,
//						const Vector &b);  //   680
//				CrossProduct(Vector &a,
//						const Vector &b);  //   681
//				FixupAngles2(Vector &v);  //   693
//				FixupAngles2(Vector &v);  //   694
//			}
//			operator!=(const Vector *const this,
//					const Vector &v);  //   746
//			Normalize(const Vector *const this);  //   748
//			operator*(float fl,
//					const Vector &v);  //   748
//			operator*(const Vector *const this,
//					float fl);  //   721
//			{
//				float flAirTime;                      //   725
//			}
//			operator*(const Vector *const this,
//					float fl);  //   734
//			operator+(const Vector *const this,
//					const Vector &v);  //   752
//			UpdateSound(CFuncVehicle *const this);  //   742
//		}
//	}
}

/* <1bd087> ../cstrike/dlls/vehicle.cpp:764 */
NOBODY void CFuncVehicle::DeadEnd(void)
{
//	{
//		class CPathTrack *pTrack;                            //   767
//		class CPathTrack *pNext;                             //   767
//	}
}

/* <1bd0d4> ../cstrike/dlls/vehicle.cpp:810 */
NOBODY void CFuncVehicle::SetControls(entvars_t *pevControls)
{
//	{
//		Vector offset;                                  //   812
//		operator-(const Vector *const this,
//				const Vector &v);  //   812
//		operator+(const Vector *const this,
//				const Vector &v);  //   814
//		operator+(const Vector *const this,
//				const Vector &v);  //   815
//	}
}

/* <1bb1b2> ../cstrike/dlls/vehicle.cpp:819 */
BOOL CFuncVehicle::OnControls_(entvars_t *pevTest)
{
	Vector offset = pevTest->origin - pev->origin;

	if (pev->spawnflags & SF_TRACKTRAIN_NOCONTROL)
		return FALSE;

	UTIL_MakeVectors(pev->angles);

	Vector local;
	local.x = DotProduct(offset, gpGlobals->v_forward);
	local.y = -DotProduct(offset, gpGlobals->v_right);
	local.z = DotProduct(offset, gpGlobals->v_up);

	return (local.x >= m_controlMins.x && local.y >= m_controlMins.y && local.z >= m_controlMins.z
		&& local.x <= m_controlMaxs.x && local.y <= m_controlMaxs.y && local.z <= m_controlMaxs.z);
}

/* <1bb676> ../cstrike/dlls/vehicle.cpp:841 */
NOBODY void CFuncVehicle::Find(void)
{
//	{
//		entvars_t *pevTarget;                                //   847
//		Vector nextPos;                                 //   855
//		Vector look;                                    //   858
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //   843
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   848
//		Vector(Vector *const this,
//			const Vector &v);  //   855
//		Vector(Vector *const this,
//			const Vector &v);  //   858
//		operator-(const Vector *const this,
//				const Vector &v);  //   863
//		NextThink(CFuncVehicle *const this,
//				float thinkTime,
//				BOOL alwaysThink);  //   870
//		UpdateSound(CFuncVehicle *const this);  //   874
//	}
}

/* <1bb840> ../cstrike/dlls/vehicle.cpp:878 */
NOBODY void CFuncVehicle::NearestPath(void)
{
//	{
//		class CBaseEntity *pTrack;                           //   880
//		class CBaseEntity *pNearest;                         //   881
//		float dist;                                           //   882
//		float closest;                                        //   882
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //   889
//		operator-(const Vector *const this,
//				const Vector &v);  //   891
//		Length(const Vector *const this);  //   891
//		operator-(const Vector *const this,
//				const Vector &v);  //   912
//		Length(const Vector *const this);  //   912
//		operator-(const Vector *const this,
//				const Vector &v);  //   912
//		Length(const Vector *const this);  //   912
//		NextThink(CFuncVehicle *const this,
//				float thinkTime,
//				BOOL alwaysThink);  //   920
//	}
}

/* <1bb00a> ../cstrike/dlls/vehicle.cpp:926 */
NOBODY void CFuncVehicle::OverrideReset_(void)
{
//	NextThink(class CFuncVehicle *const this, float thinkTime, BOOL alwaysThink);  //   928
}

/* <1bd198> ../cstrike/dlls/vehicle.cpp:933 */
NOBODY CFuncVehicle *CFuncVehicle::Instance(edict_t *pent)
{
//	FClassnameIs(edict_t *pent,
//			const char *szClassname);  //   935
//	GET_PRIVATE(edict_t *pent);  //   936
}

/* <1bb055> ../cstrike/dlls/vehicle.cpp:951 */
int CFuncVehicle::Classify_(void)
{
	return CLASS_VEHICLE;
}

/* <1bb0ef> ../cstrike/dlls/vehicle.cpp:956 */
NOBODY void CFuncVehicle::Spawn_(void)
{
//	NextThink(CFuncVehicle::Spawn(//			float thinkTime,
//			BOOL alwaysThink);  //   999
}

/* <1bb13e> ../cstrike/dlls/vehicle.cpp:1005 */
NOBODY void CFuncVehicle::Restart_(void)
{
//	STOP_SOUND(edict_t *entity,
//			int channel,
//			const char *sample);  //  1024
//	NextThink(CFuncVehicle *const this,
//			float thinkTime,
//			BOOL alwaysThink);  //  1027
}

/* <1bb07b> ../cstrike/dlls/vehicle.cpp:1032 */
void CFuncVehicle::Precache_(void)
{
	if (m_flVolume == 0.0f)
		m_flVolume = 1.0f;

	switch (m_sounds)
	{
		case 1:
			PRECACHE_SOUND("plats/vehicle1.wav");
			pev->noise = MAKE_STRING("plats/vehicle1.wav");
			break;
		case 2:
			PRECACHE_SOUND("plats/vehicle2.wav");
			pev->noise = MAKE_STRING("plats/vehicle2.wav");
			break;
		case 3:
			PRECACHE_SOUND("plats/vehicle3.wav");
			pev->noise = MAKE_STRING("plats/vehicle3.wav");
			break;
		case 4:
			PRECACHE_SOUND("plats/vehicle4.wav");
			pev->noise = MAKE_STRING("plats/vehicle4.wav");
			break;
		case 5:
			PRECACHE_SOUND("plats/vehicle6.wav");
			pev->noise = MAKE_STRING("plats/vehicle6.wav");
			break;
		case 6:
			PRECACHE_SOUND("plats/vehicle7.wav");
			pev->noise = MAKE_STRING("plats/vehicle7.wav");
			break;
	}

	PRECACHE_SOUND("plats/vehicle_brake1.wav");
	PRECACHE_SOUND("plats/vehicle_start1.wav");

	m_usAdjustPitch = PRECACHE_EVENT(1, "events/vehicle.sc");
}

/* <1bd23c> ../cstrike/dlls/vehicle.cpp:1064 */
LINK_ENTITY_TO_CLASS(func_vehiclecontrols, CFuncVehicleControls);

/* <1bbd36> ../cstrike/dlls/vehicle.cpp:1067 */
NOBODY void CFuncVehicleControls::Find(void)
{
//	{
//		edict_t *pTarget;                                    //  1069
//		class CFuncVehicle *pvehicle;                        //  1082
//		Instance(edict_t *pent);  //  1082
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  1073
//		FNullEnt(const edict_t *pent);  //  1074
//		FNullEnt(const edict_t *pent);  //  1076
//		SetControls(CFuncVehicle *const this,
//				entvars_t *pevControls);  //  1083
//		FClassnameIs(edict_t *pent,
//				const char *szClassname);  //  1074
//	}
}

/* <1bb0c8> ../cstrike/dlls/vehicle.cpp:1088 */
NOBODY void CFuncVehicleControls::Spawn_(void)
{
}

#ifdef HOOK_GAMEDLL

void CFuncVehicle::Spawn(void)
{
	Spawn_();
}

void CFuncVehicle::Precache(void)
{
	Precache_();
}

void CFuncVehicle::Restart(void)
{
	Restart_();
}

void CFuncVehicle::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CFuncVehicle::Save(CSave &save)
{
	return Save_(save);
}

int CFuncVehicle::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CFuncVehicle::Classify(void)
{
	return Classify_();
}

void CFuncVehicle::OverrideReset(void)
{
	OverrideReset_();
}

BOOL CFuncVehicle::OnControls(entvars_t *pev)
{
	return OnControls_(pev);
}

void CFuncVehicle::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CFuncVehicle::Blocked(CBaseEntity *pOther)
{
	Blocked_(pOther);
}

#endif // HOOK_GAMEDLL
