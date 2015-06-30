#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

BOOL g_fDrawLines = FALSE;

#else

BOOL g_fDrawLines;

#endif // HOOK_GAMEDLL

/* <c08f4> ../cstrike/dlls/h_ai.cpp:47 */
NOBODY BOOL FBoxVisible(entvars_t *pevLooker, entvars_t *pevTarget, Vector &vecTargetOrigin, float flSize)
{
//	{
//		TraceResult tr;                                       //    54
//		Vector vecLookerOrigin;                         //    55
//		operator+(const Vector *const this,
//				const Vector &v);  //    55
//		{
//			int i;                                        //    56
//			{
//				Vector vecTarget;               //    58
//				Vector(Vector *const this,
//					const Vector &v);  //    58
//			}
//		}
//	}
}

/* <c0a19> ../cstrike/dlls/h_ai.cpp:78 */
NOBODY Vector VecCheckToss(entvars_t *pev, Vector &vecSpot1, Vector vecSpot2, float flGravityAdj)
{
//	{
//		TraceResult tr;                                       //    80
//		Vector vecMidPoint;                             //    81
//		Vector vecApex;                                 //    82
//		Vector vecScale;                                //    83
//		Vector vecGrenadeVel;                           //    84
//		Vector vecTemp;                                 //    85
//		float flGravity;                                      //    86
//		float distance1;                                      //   119
//		float distance2;                                      //   120
//		float time1;                                          //   123
//		float time2;                                          //   124
//		Vector(Vector *const this,
//			const Vector &v);  //   153
//		operator*(const Vector *const this,
//				float fl);  //    97
//		operator+(const Vector *const this,
//				const Vector &v);  //    97
//		operator*(const Vector *const this,
//				float fl);  //    98
//		operator+(const Vector *const this,
//				const Vector &v);  //    98
//		operator-(const Vector *const this,
//				const Vector &v);  //   106
//		operator+(const Vector *const this,
//				const Vector &v);  //   106
//		operator*(const Vector *const this,
//				float fl);  //   106
//		operator+(const Vector *const this,
//				const Vector &v);  //   107
//		operator-(const Vector *const this,
//				const Vector &v);  //   133
//		operator/(const Vector *const this,
//				float fl);  //   133
//		operator*(const Vector *const this,
//				float fl);  //   138
//		operator+(const Vector *const this,
//				const Vector &v);  //   138
//		Vector(Vector *const this,
//			const Vector &v);  //   156
//	}
}

/* <c0d21> ../cstrike/dlls/h_ai.cpp:164 */
NOBODY Vector VecCheckThrow(entvars_t *pev, Vector &vecSpot1, Vector vecSpot2, float flSpeed, float flGravityAdj)
{
//	{
//		float flGravity;                                      //   166
//		Vector vecGrenadeVel;                           //   168
//		float time;                                           //   171
//		Vector vecApex;                                 //   177
//		TraceResult tr;                                       //   180
//		operator-(const Vector *const this,
//				const Vector &v);  //   168
//		Length(const Vector *const this);  //   171
//		operator-(const Vector *const this,
//				const Vector &v);  //   177
//		operator*(const Vector *const this,
//				float fl);  //   177
//		operator+(const Vector *const this,
//				const Vector &v);  //   177
//		Vector(Vector *const this,
//			const Vector &v);  //   192
//		operator*(const Vector *const this,
//				float fl);  //   172
//		Vector(Vector *const this,
//			const Vector &v);  //   195
//	}
}
