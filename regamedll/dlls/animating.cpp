#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

TYPEDESCRIPTION CBaseAnimating::m_SaveData[] =
{
	DEFINE_FIELD(CBaseMonster, m_flFrameRate, FIELD_FLOAT),
	DEFINE_FIELD(CBaseMonster, m_flGroundSpeed, FIELD_FLOAT),
	DEFINE_FIELD(CBaseMonster, m_flLastEventCheck, FIELD_TIME),
	DEFINE_FIELD(CBaseMonster, m_fSequenceFinished, FIELD_BOOLEAN),
	DEFINE_FIELD(CBaseMonster, m_fSequenceLoops, FIELD_BOOLEAN),
};

#else

TYPEDESCRIPTION (*CBaseAnimating::m_SaveData)[5];

#endif // HOOK_GAMEDLL

/* <10583> ../cstrike/dlls/animating.cpp:38 */
IMPLEMENT_SAVERESTORE(CBaseAnimating, CBaseDelay);
//NOBODY int CBaseAnimating::Save(CSave &save)
//{
//}

/* <10537> ../cstrike/dlls/animating.cpp:38 */
//NOBODY int CBaseAnimating::Restore(CRestore &restore)
//{
//}

/* <105cf> ../cstrike/dlls/animating.cpp:45 */
NOBODY float CBaseAnimating::StudioFrameAdvance(float flInterval)
{
}

/* <10605> ../cstrike/dlls/animating.cpp:77 */
int CBaseAnimating::LookupActivity(int activity)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::LookupActivity(pmodel, pev, activity);
}

/* <10653> ../cstrike/dlls/animating.cpp:91 */
NOBODY int CBaseAnimating::LookupActivityHeaviest(int activity)
{
//	{ 
//		void *pmodel;                                        //    93
//	} 
}

/* <107b1> ../cstrike/dlls/animating.cpp:136 */
NOBODY void CBaseAnimating::DispatchAnimEvents(float flInterval)
{
//	{
//		MonsterEvent_t event;                                 //   138
//		void *pmodel;                                        //   140
//		float flStart;                                        //   152
//		float flEnd;                                          //   153
//		int index;                                            //   160
//	}
}

/* <106a1> ../cstrike/dlls/animating.cpp:100 */
int CBaseAnimating::LookupSequence(const char *label)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::LookupSequence(pmodel, label);
}

/* <10711> ../cstrike/dlls/animating.cpp:110 */
void CBaseAnimating::ResetSequenceInfo(void)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));

	GetSequenceInfo(pmodel, pev, &m_flFrameRate, &m_flGroundSpeed);
	m_fSequenceLoops = ((GetSequenceFlags() & STUDIO_LOOPING) != 0);
	pev->animtime = gpGlobals->time;
	pev->framerate = 1.0f;

	m_fSequenceFinished = FALSE;
	m_flLastEventCheck = gpGlobals->time;
}

/* <1077c> ../cstrike/dlls/animating.cpp:126 */
BOOL CBaseAnimating::GetSequenceFlags(void)
{
	void *pmodel = GET_MODEL_PTR(ENT(pev));
	return ::GetSequenceFlags(pmodel, pev);
}

/* <10837> ../cstrike/dlls/animating.cpp:171 */
NOBODY float CBaseAnimating::SetBoneController(int iController, float flValue)
{
//	{ 
//		void *pmodel;                                        //   173
//	} 
}

/* <10893> ../cstrike/dlls/animating.cpp:180 */
NOBODY void CBaseAnimating::InitBoneControllers(void)
{
//	{ 
//		void *pmodel;                                        //   182
//	} 
}

/* <108d3> ../cstrike/dlls/animating.cpp:192 */
NOBODY float CBaseAnimating::SetBlending(int iBlender, float flValue)
{
//	{ 
//		void *pmodel;                                        //   194
//	} 
}

/* <1092f> ../cstrike/dlls/animating.cpp:201 */
NOBODY void CBaseAnimating::GetBonePosition(int iBone, class Vector &origin, class Vector &angles)
{
}

/* <10984> ../cstrike/dlls/animating.cpp:208 */
NOBODY void CBaseAnimating::GetAttachment(int iAttachment, class Vector &origin, class Vector &angles)
{
}

/* <109d4> ../cstrike/dlls/animating.cpp:215 */
NOBODY int CBaseAnimating::FindTransition(int iEndingSequence, int iGoalSequence, int *piDir)
{
//	{
//		void *pmodel;                                        //   217
//		{
//			int iDir;                                     //   221
//			int sequence;                                 //   222
//		}
//	}
}

/* <10a5d> ../cstrike/dlls/animating.cpp:234 */
NOXREF void CBaseAnimating::GetAutomovement(Vector &origin, class Vector &angles, float flInterval)
{
}

/* <10aad> ../cstrike/dlls/animating.cpp:239 */
NOBODY void CBaseAnimating::SetBodygroup(int iGroup, int iValue)
{
}

/* <10af0> ../cstrike/dlls/animating.cpp:244 */
NOBODY int CBaseAnimating::GetBodygroup(int iGroup)
{
}

/* <10b5f> ../cstrike/dlls/animating.cpp:250 */
NOBODY int CBaseAnimating::ExtractBbox(int sequence, float *mins, float *maxs)
{
}

/* <10b99> ../cstrike/dlls/animating.cpp:258 */
NOBODY void CBaseAnimating::SetSequenceBox(void)
{
//	{
//		class Vector mins;                                    //   260
//		class Vector maxs;                                    //   260
//		ExtractBbox(CBaseAnimating *const this,
//				int sequence,
//				float *mins,
//				float *maxs);  //   263
//		{
//			float yaw;                                    //   267
//			class Vector xvector;                         //   269
//			class Vector yvector;                         //   269
//			class Vector bounds;                          //   274
//			class Vector rmin;                            //   279
//			class Vector rmax;                            //   280
//			class Vector base;                            //   281
//			class Vector transformed;                     //   281
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   280
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //   279
//			{
//				int i;                                //   283
//				{
//					int j;                        //   286
//					{
//						int k;                //   289
//						{
//							int l;        //   298
//						}
//					}
//				}
//			}
//		}
//	}
}

#ifdef HOOK_GAMEDLL

int CBaseAnimating::Save(CSave &save)
{
	return Save_(save);
}

int CBaseAnimating::Restore(CRestore &restore)
{
	return Restore_(restore);
}

//void CBaseAnimating::HandleAnimEvent(MonsterEvent_t *pEvent)
//{
//	HandleAnimEvent_(pEvent);
//}

#endif // HOOK_GAMEDLL
