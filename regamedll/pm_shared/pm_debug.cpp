#include "precompiled.h"

static int PM_boxpnt[6][4] =
{
	{ 0, 4, 6, 2 }, // +X
	{ 0, 1, 5, 4 }, // +Y
	{ 0, 2, 3, 1 }, // +Z
	{ 7, 5, 1, 3 }, // -X
	{ 7, 3, 2, 6 }, // -Y
	{ 7, 6, 4, 5 }, // -Z
};

/* <2d0110> ../cstrike/pm_shared/pm_debug.c:43 */
NOBODY void PM_ShowClipBox(void)
{
}

/* <2d0012> ../cstrike/pm_shared/pm_debug.c:82 */
NOBODY void PM_ParticleLine(vec3_t start, vec3_t end, int pcolor, float life, float vert)
{
//	float linestep;                                               //    84
//	float curdist;                                                //    85
//	float len;                                                    //    86
//	vec3_t curpos;                                                //    87
//	vec3_t diff;                                                  //    88
//	int i;                                                        //    89
}

/* <2d0197> ../cstrike/pm_shared/pm_debug.c:114 */
NOBODY void PM_DrawRectangle(vec3_t tl, vec3_t bl, vec3_t tr, vec3_t br, int pcolor, float life)
{
}

/* <2cff57> ../cstrike/pm_shared/pm_debug.c:128 */
NOBODY void PM_DrawPhysEntBBox(int num, int pcolor, float life)
{
//	physent_t *pe;                                               //   130
//	vec3_t org;                                                   //   131
//	int j;                                                        //   132
//	vec3_t tmp;                                                   //   133
//	vec_t p;                                                      //   134
//	float gap;                                                    //   135
//	vec3_t modelmins;                                             //   136
//	vec3_t modelmaxs;                                             //   136
//	{
//		vec3_t forward;                                       //   161
//		vec3_t right;                                         //   161
//		vec3_t up;                                            //   161
//	}
}

/* <2d030c> ../cstrike/pm_shared/pm_debug.c:218 */
NOBODY void PM_DrawBBox(vec3_t mins, vec3_t maxs, vec3_t origin, int pcolor, float life)
{
//	int j;                                                        //   220
//	vec3_t tmp;                                                   //   222
//	vec_t p;                                                      //   223
//	float gap;                                                    //   224
//	PM_DrawRectangle(vec3_t tl,
//			vec3_t bl,
//			vec3_t tr,
//			vec3_t br,
//			int pcolor,
//			float life);  //   238
}

/* <2d03e9> ../cstrike/pm_shared/pm_debug.c:260 */
NOBODY void PM_ViewEntity(void)
{
//	vec3_t forward;                                               //   262
//	vec3_t right;                                                 //   262
//	vec3_t up;                                                    //   262
//	float raydist;                                                //   263
//	vec3_t origin;                                                //   264
//	vec3_t end;                                                   //   265
//	int i;                                                        //   266
//	pmtrace_t trace;                                              //   267
//	int pcolor;                                                   //   268
//	float fup;                                                    //   269
//	PM_DrawPhysEntBBox(int num,
//				int pcolor,
//				float life);  //   294
}
