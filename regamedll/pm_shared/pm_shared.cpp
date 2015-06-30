#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//static int pm_shared_initialized = 0;

//static vec_t rgv3tStuckTable[54][3];
//static int rgStuckLast[32][2];

//static int pm_gcTextures = 0;	// TODO: var names without pm_*
//static char pm_grgszTextureName[1024][17];
//static char pm_grgchTextureType[1024];

//playermove_t *pmove = NULL;
//int g_onladder = 0;

#else // HOOK_GAMEDLL

int pm_shared_initialized;

vec3_t rgv3tStuckTable[54];
//int rgStuckLast[32][2];

int pm_gcTextures;
char pm_grgszTextureName[ CTEXTURESMAX ][ CBTEXTURENAMEMAX ];
char pm_grgchTextureType[ CTEXTURESMAX ];

playermove_t *pmove;
//int g_onladder;

#endif // HOOK_GAMEDLL

/* <2cc613> ../cstrike/pm_shared/pm_shared.c:165 */
NOXREF void PM_SwapTextures(int i, int j)
{
	char chTemp;
	char szTemp[CBTEXTURENAMEMAX];

	Q_strcpy(szTemp, pm_grgszTextureName[i]);
	chTemp = pm_grgchTextureType[i];

	Q_strcpy(pm_grgszTextureName[i], pm_grgszTextureName[j]);
	pm_grgchTextureType[i] = pm_grgchTextureType[j];

	Q_strcpy(pm_grgszTextureName[j], szTemp);
	pm_grgchTextureType[j] = chTemp;
}

/* <2cc691> ../cstrike/pm_shared/pm_shared.c:180 */
NOXREF int PM_IsThereGrassTexture(void)
{
	int i;

	for (i = 0 ; i < pm_gcTextures; i++)
	{
		if (pm_grgchTextureType[i] == CHAR_TEX_GRASS)
			return 1;
	}
	return 0;
}

/* <2cc6bb> ../cstrike/pm_shared/pm_shared.c:193 */
NOXREF void PM_SortTextures(void)
{
	int i, j;

	for (i = 0 ; i < pm_gcTextures; i++)
	{
		for (j = i + 1; j < pm_gcTextures; j++)
		{
			if (Q_stricmp(pm_grgszTextureName[i], pm_grgszTextureName[j]) > 0)
				PM_SwapTextures(i, j);
		}
	}
}

/* <2cc720> ../cstrike/pm_shared/pm_shared.c:213 */
void PM_InitTextureTypes(void)
{
	char buffer[512];
	int i, j;
	byte *pMemFile;
	int fileSize, filePos;
	static qboolean bTextureTypeInit = false;

	if (bTextureTypeInit)
		return;

	Q_memset(&(pm_grgszTextureName[0][0]), 0, sizeof(pm_grgszTextureName));
	Q_memset(pm_grgchTextureType, 0, sizeof(pm_grgchTextureType));

	pm_gcTextures = 0;
	Q_memset(buffer, 0, sizeof(buffer));

	fileSize = pmove->COM_FileSize("sound/materials.txt");
	pMemFile = pmove->COM_LoadFile("sound/materials.txt", 5, NULL);

	if (!pMemFile)
		return;

	filePos = 0;

	while (pmove->memfgets(pMemFile, fileSize, &filePos, buffer, 511) != NULL && (pm_gcTextures < CTEXTURESMAX))
	{
		i = 0;

		while (buffer[i] && isspace(buffer[i]))
			i++;

		if (!buffer[i])
			continue;

		if (buffer[i] == '/' || !isalpha(buffer[i]))
			continue;

		pm_grgchTextureType[pm_gcTextures] = toupper(buffer[i++]);

		while (buffer[i] && isspace(buffer[i]))
			i++;

		if (!buffer[i])
			continue;

		j = i;

		while (buffer[j] && !isspace(buffer[j]))
			j++;

		if (!buffer[j])
			continue;

		j = min (j, CBTEXTURENAMEMAX - 1 + i);
		buffer[j] = 0;
		Q_strcpy(&(pm_grgszTextureName[pm_gcTextures++][0]), &(buffer[i]));
	}

	pmove->COM_FreeFile(pMemFile);

	PM_SortTextures();

	bTextureTypeInit = true;
}

/* <2cc7c5> ../cstrike/pm_shared/pm_shared.c:283 */
char PM_FindTextureType(char *name)
{
	int left = 0;
	int right = pm_gcTextures - 1;
	int pivot;
	int val;

	assert( pm_shared_initialized );

	while (left <= right)
	{
		pivot = (left + right) / 2;

		val = Q_strnicmp(name, pm_grgszTextureName[pivot], CBTEXTURENAMEMAX - 1);

		if (val == 0)
			return pm_grgchTextureType[pivot];

		else if (val > 0)
			left = pivot + 1;

		else if (val < 0)
			right = pivot - 1;
	}

	return CHAR_TEX_CONCRETE;
}

/* <2cc416> ../cstrike/pm_shared/pm_shared.c:315 */
void PM_PlayStepSound(int step, float fvol)
{
	static int iSkipStep = 0;
	int irand;
	//vec3_t hvel;//unused?

	pmove->iStepLeft = pmove->iStepLeft == 0;

	if (!pmove->runfuncs)
		return;

	irand = pmove->RandomLong(0, 1) + (pmove->iStepLeft * 2);

	if (pmove->multiplayer && !pmove->movevars->footsteps)
		return;

	switch (step)
	{
		default:
		case STEP_CONCRETE:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_step1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_step3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_step2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_step4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_METAL:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_DIRT:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_VENT:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_GRATE:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_TILE:
		{
			if (!pmove->RandomLong(0, 4))
				irand = 4;

			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 4:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile5.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_SLOSH:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_WADE:
		{
			if (iSkipStep)
			{
				if (iSkipStep++ == 3)
					iSkipStep = 0;

				switch (irand)
				{
					case 0:
						pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
						break;
					case 1:
						pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
						break;
					case 2:
						pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
						break;
					case 3:
						pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
						break;
				}
			}
			else
				iSkipStep++;

			break;
		}
		case STEP_LADDER:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
		case STEP_SNOW:
		{
			switch (irand)
			{
				case 0:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow1.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 1:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow3.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 2:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow2.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
				case 3:
					pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow4.wav", fvol, ATTN_NORM, 0, PITCH_NORM);
					break;
			}
			break;
		}
	}
}

/* <2cc462> ../cstrike/pm_shared/pm_shared.c:489 */
NOXREF int PM_MapTextureTypeStepType(char chTextureType)
{
	switch (chTextureType)
	{
		default:
		case CHAR_TEX_CONCRETE:
			return STEP_CONCRETE;
		case CHAR_TEX_METAL:
			return STEP_METAL;
		case CHAR_TEX_DIRT:
			return STEP_DIRT;
		case CHAR_TEX_VENT:
			return STEP_VENT;
		case CHAR_TEX_GRATE:
			return STEP_GRATE;
		case CHAR_TEX_TILE:
			return STEP_TILE;
		case CHAR_TEX_SLOSH:
			return STEP_SLOSH;
		case CHAR_TEX_SNOW:
			return STEP_SNOW;
	}
}

/* <2cc8af> ../cstrike/pm_shared/pm_shared.c:512 */
void PM_CatagorizeTextureType(void)
{
	vec3_t start, end;
	const char *pTextureName;

	VectorCopy(pmove->origin, start);
	VectorCopy(pmove->origin, end);

	end[2] -= 64.0f;

	pmove->sztexturename[0] = '\0';
	pmove->chtexturetype = CHAR_TEX_CONCRETE;

	pTextureName = pmove->PM_TraceTexture(pmove->onground, start, end);

	if (!pTextureName)
		return;

	if (*pTextureName == '-' || *pTextureName == '+')
		pTextureName += 2;

	if (*pTextureName == '{' || *pTextureName == '!' || *pTextureName == '~' || *pTextureName == ' ')
		pTextureName++;

	Q_strcpy(pmove->sztexturename, pTextureName);
	pmove->sztexturename[CBTEXTURENAMEMAX - 1] = 0;

	pmove->chtexturetype = PM_FindTextureType(pmove->sztexturename);
}

/* <2cc93c> ../cstrike/pm_shared/pm_shared.c:546 */
void PM_UpdateStepSound(void)
{
	float fvol;
	vec3_t knee;
	vec3_t feet;
	vec3_t center;
	float height;
	float speed;
	int fLadder;
	int step;

	if (pmove->flTimeStepSound > 0)
		return;

	if (pmove->flags & FL_FROZEN)
		return;

	speed = Length(pmove->velocity);

	if (speed <= 150.0)
	{
		pmove->flTimeStepSound = 400;
		return;
	}

	fLadder = (pmove->movetype == MOVETYPE_FLY);

	if (fLadder || pmove->onground != -1)
	{
		PM_CatagorizeTextureType();

		VectorCopy(pmove->origin, center);
		VectorCopy(pmove->origin, knee);
		VectorCopy(pmove->origin, feet);

		height = pmove->_player_maxs[pmove->usehull][2] - pmove->_player_mins[pmove->usehull][2];

		knee[2] = pmove->origin[2] - 0.3 * height;
		feet[2] = pmove->origin[2] - 0.5 * height;

		if (fLadder)
		{
			step = STEP_LADDER;
			fvol = 0.35;
			pmove->flTimeStepSound = 350;
		}
		else if (pmove->PM_PointContents(knee, NULL) == CONTENTS_WATER)
		{
			step = STEP_WADE;
			fvol = 0.65;
			pmove->flTimeStepSound = 600;
		}
		else if (pmove->PM_PointContents(feet, NULL) == CONTENTS_WATER)
		{
			step = STEP_SLOSH;
			fvol = 0.5;
			pmove->flTimeStepSound = 300;
		}
		else
		{
			step = PM_MapTextureTypeStepType(pmove->chtexturetype);
			switch (pmove->chtexturetype)
			{
				case CHAR_TEX_DIRT:
				{
					fvol = 0.55;
					break;
				}
				case CHAR_TEX_VENT:
				{
					fvol = 0.7;
					break;
				}
				default:
				{
					fvol = 0.5;
					break;
				}
			}
			pmove->flTimeStepSound = 300;
		}
		if (pmove->flags & FL_DUCKING || fLadder)
		{
			pmove->flTimeStepSound += 100;

			if (pmove->flags & FL_DUCKING && pmove->flDuckTime < 950.0)
				fvol *= 0.35;
		}
		PM_PlayStepSound(step, fvol);
	}
}

/* <2cca3d> ../cstrike/pm_shared/pm_shared.c:679 */
NOBODY qboolean PM_AddToTouched(pmtrace_t tr, vec3_t impactvelocity)
{
//	int i;                                                        //   681
}

/* <2cca88> ../cstrike/pm_shared/pm_shared.c:707 */
NOBODY void PM_CheckVelocity(void)
{
//	int i;                                                        //   709
}

/* <2ccbe9> ../cstrike/pm_shared/pm_shared.c:752 */
NOBODY int PM_ClipVelocity(vec3_t in, vec3_t normal, vec3_t out, float overbounce)
{
//	float backoff;                                                //   754
//	float change;                                                 //   755
//	float angle;                                                  //   756
//	int i;                                                        //   757
//	int blocked;                                                  //   757
}

/* <2ccc93> ../cstrike/pm_shared/pm_shared.c:784 */
NOBODY void PM_AddCorrectGravity(void)
{
//	float ent_gravity;                                            //   786
}

/* <2cc482> ../cstrike/pm_shared/pm_shared.c:806 */
NOBODY void PM_FixupGravityVelocity(void)
{
//	float ent_gravity;                                            //   808
}

/* <2ccd08> ../cstrike/pm_shared/pm_shared.c:831 */
NOBODY int PM_FlyMove(void)
{
//	int bumpcount;                                                //   833
//	int numbumps;                                                 //   833
//	vec3_t dir;                                                   //   834
//	float d;                                                      //   835
//	int numplanes;                                                //   836
//	vec_t planes;                                                 //   837
//	vec3_t primal_velocity;                                       //   838
//	vec3_t original_velocity;                                     //   838
//	vec3_t new_velocity;                                          //   839
//	int i;                                                        //   840
//	int j;                                                        //   840
//	pmtrace_t trace;                                              //   841
//	vec3_t end;                                                   //   842
//	float time_left;                                              //   843
//	float allFraction;                                            //   843
//	int blocked;                                                  //   844
}

/* <2cce2e> ../cstrike/pm_shared/pm_shared.c:1027 */
NOBODY void PM_Accelerate(vec3_t wishdir, float wishspeed, float accel)
{
//	int i;                                                        //  1029
//	float addspeed;                                               //  1030
//	float accelspeed;                                             //  1030
//	float currentspeed;                                           //  1030
}

/* <2cceaf> ../cstrike/pm_shared/pm_shared.c:1071 */
NOBODY void PM_WalkMove(void)
{
//	int clip;                                                     //  1073
//	int oldonground;                                              //  1074
//	int i;                                                        //  1075
//	vec3_t wishvel;                                               //  1077
//	float spd;                                                    //  1078
//	float fmove;                                                  //  1079
//	float smove;                                                  //  1079
//	vec3_t wishdir;                                               //  1080
//	float wishspeed;                                              //  1081
//	vec3_t dest;                                                  //  1083
//	vec3_t start;                                                 //  1083
//	vec3_t original;                                              //  1084
//	vec3_t originalvel;                                           //  1084
//	vec3_t down;                                                  //  1085
//	vec3_t downvel;                                               //  1085
//	float downdist;                                               //  1086
//	float updist;                                                 //  1086
//	pmtrace_t trace;                                              //  1088
//	
//usedown:                                                              //  1234
//	{
//		float flRatio;                                        //  1092
//	}
}

/* <2ccffb> ../cstrike/pm_shared/pm_shared.c:1249 */
NOBODY void PM_Friction(void)
{
//	float *vel;                                                  //  1251
//	float speed;                                                  //  1252
//	float newspeed;                                               //  1252
//	float control;                                                //  1252
//	float friction;                                               //  1253
//	float drop;                                                   //  1254
//	vec3_t newvel;                                                //  1255
//	{
//		vec3_t start;                                         //  1278
//		vec3_t stop;                                          //  1278
//		pmtrace_t trace;                                      //  1279
//	}
}

/* <2cd0ba> ../cstrike/pm_shared/pm_shared.c:1326 */
NOBODY void PM_AirAccelerate(vec3_t wishdir, float wishspeed, float accel)
{
//	int i;                                                        //  1328
//	float addspeed;                                               //  1329
//	float accelspeed;                                             //  1329
//	float currentspeed;                                           //  1329
//	float wishspd;                                                //  1329
}

/* <2cd14b> ../cstrike/pm_shared/pm_shared.c:1368 */
NOBODY void PM_WaterMove(void)
{
//	int i;                                                        //  1370
//	vec3_t wishvel;                                               //  1371
//	float wishspeed;                                              //  1372
//	vec3_t wishdir;                                               //  1373
//	vec3_t start;                                                 //  1374
//	vec3_t dest;                                                  //  1374
//	vec3_t temp;                                                  //  1375
//	pmtrace_t trace;                                              //  1376
//	float speed;                                                  //  1378
//	float newspeed;                                               //  1378
//	float addspeed;                                               //  1378
//	float accelspeed;                                             //  1378
}

/* <2cd220> ../cstrike/pm_shared/pm_shared.c:1464 */
NOBODY void PM_AirMove(void)
{
//	int i;                                                        //  1466
//	vec3_t wishvel;                                               //  1467
//	float fmove;                                                  //  1468
//	float smove;                                                  //  1468
//	vec3_t wishdir;                                               //  1469
//	float wishspeed;                                              //  1470
}

/* <2cc586> ../cstrike/pm_shared/pm_shared.c:1510 */
NOBODY qboolean PM_InWater(void)
{
}

/* <2cd2a7> ../cstrike/pm_shared/pm_shared.c:1522 */
NOBODY qboolean PM_CheckWater(void)
{
//	vec3_t point;                                                 //  1524
//	int cont;                                                     //  1525
//	int truecont;                                                 //  1526
//	float height;                                                 //  1527
//	float heightover2;                                            //  1528
//	{
//		vec_t current_table;                                  //  1575
//	}
}

/* <2cd33a> ../cstrike/pm_shared/pm_shared.c:1593 */
NOBODY void PM_CatagorizePosition(void)
{
//	vec3_t point;                                                 //  1595
//	pmtrace_t tr;                                                 //  1596
}

/* <2cc4c5> ../cstrike/pm_shared/pm_shared.c:1654 */
NOBODY int PM_GetRandomStuckOffsets(int nIndex, int server, vec3_t offset)
{
//	int idx;                                                      //  1657
}

/* <2cc49d> ../cstrike/pm_shared/pm_shared.c:1665 */
NOBODY void PM_ResetStuckOffsets(int nIndex, int server)
{
}

/* <2cd3cf> ../cstrike/pm_shared/pm_shared.c:1681 */
NOBODY int PM_CheckStuck(void)
{
//	vec3_t base;                                                  //  1683
//	vec3_t offset;                                                //  1684
//	vec3_t test;                                                  //  1685
//	int hitent;                                                   //  1686
//	int idx;                                                      //  1687
//	float fTime;                                                  //  1688
//	int i;                                                        //  1689
//	pmtrace_t traceresult;                                        //  1690
//	float rgStuckCheckTime;                                       //  1692
//	{
//		int nReps;                                            //  1713
//		PM_ResetStuckOffsets(int nIndex,
//					int server);  //  1714
//		PM_GetRandomStuckOffsets(int nIndex,
//					int server,
//					vec3_t offset);  //  1717
//		PM_ResetStuckOffsets(int nIndex,
//					int server);  //  1722
//	}
//	{
//		float x;                                              //  1769
//		float y;                                              //  1769
//		float z;                                              //  1769
//		float xystep;                                         //  1770
//		float zstep;                                          //  1771
//		float xyminmax;                                       //  1772
//		float zminmax;                                        //  1773
//	}
//	PM_GetRandomStuckOffsets(int nIndex,
//				int server,
//				vec3_t offset);  //  1750
//	PM_ResetStuckOffsets(int nIndex,
//				int server);  //  1757
//	PM_ResetStuckOffsets(int nIndex,
//				int server);  //  1698
}

/* <2cd61f> ../cstrike/pm_shared/pm_shared.c:1807 */
NOBODY void PM_SpectatorMove(void)
{
//	float speed;                                                  //  1809
//	float drop;                                                   //  1809
//	float friction;                                               //  1809
//	float control;                                                //  1809
//	float newspeed;                                               //  1809
//	float currentspeed;                                           //  1811
//	float addspeed;                                               //  1811
//	float accelspeed;                                             //  1811
//	int i;                                                        //  1812
//	vec3_t wishvel;                                               //  1813
//	float fmove;                                                  //  1814
//	float smove;                                                  //  1814
//	vec3_t wishdir;                                               //  1815
//	float wishspeed;                                              //  1816
//	{
//		int target;                                           //  1905
//	}
}

/* <2cc509> ../cstrike/pm_shared/pm_shared.c:1941 */
NOBODY float PM_SplineFraction(float value, float scale)
{
//	float valueSquared;                                           //  1943
}

/* <2cd757> ../cstrike/pm_shared/pm_shared.c:1952 */
NOBODY float PM_SimpleSpline(float value)
{
//	float valueSquared;                                           //  1954
}

/* <2cc595> ../cstrike/pm_shared/pm_shared.c:1959 */
NOBODY void PM_FixPlayerCrouchStuck(int direction)
{
//	int hitent;                                                   //  1961
//	int i;                                                        //  1962
//	vec3_t test;                                                  //  1963
}

/* <2cd7cd> ../cstrike/pm_shared/pm_shared.c:1983 */
NOBODY void PM_Duck(void)
{
//	float duckFraction;                                           //  1986
//	int buttonsChanged;                                           //  1988
//	int nButtonPressed;                                           //  1989
//	int duckchange;                                               //  1991
//	int duckpressed;                                              //  1992
//	{
//		float fMore;                                          //  2063
//		float time;                                           //  2064
//	}
//	{
//		pmtrace_t trace;                                      //  2074
//		vec3_t newOrigin;                                     //  2075
//	}
//	PM_FixPlayerCrouchStuck(int direction);  //  2055
}

/* <2cd8c2> ../cstrike/pm_shared/pm_shared.c:2332 */
NOBODY void PM_LadderMove(physent_t *pLadder)
{
//	vec3_t ladderCenter;                                          //  2334
//	trace_t trace;                                                //  2335
//	qboolean onFloor;                                             //  2336
//	vec3_t floor;                                                 //  2337
//	vec3_t modelmins;                                             //  2338
//	vec3_t modelmaxs;                                             //  2338
//	{
//		float forward;                                        //  2364
//		float right;                                          //  2364
//		vec3_t vpn;                                           //  2365
//		vec3_t v_right;                                       //  2365
//		float flSpeed;                                        //  2366
//		{
//			vec3_t velocity;                              //  2407
//			vec3_t perp;                                  //  2407
//			vec3_t cross;                                 //  2407
//			vec3_t lateral;                               //  2407
//			vec3_t tmp;                                   //  2407
//			float normal;                                 //  2408
//		}
//	}
}

/* <2cda06> ../cstrike/pm_shared/pm_shared.c:2457 */
NOBODY physent_t *PM_Ladder(void)
{
//	int i;                                                        //  2459
//	physent_t *pe;                                               //  2460
//	hull_t *hull;                                                //  2461
//	int num;                                                      //  2462
//	vec3_t test;                                                  //  2463
}

/* <2cda77> ../cstrike/pm_shared/pm_shared.c:2491 */
NOBODY void PM_WaterJump(void)
{
}

/* <2cda8d> ../cstrike/pm_shared/pm_shared.c:2519 */
NOBODY void PM_AddGravity(void)
{
//	float ent_gravity;                                            //  2521
}

/* <2cdac6> ../cstrike/pm_shared/pm_shared.c:2541 */
NOBODY pmtrace_t PM_PushEntity(vec3_t push)
{
//	pmtrace_t trace;                                              //  2543
//	vec3_t end;                                                   //  2544
}

/* <2cdb13> ../cstrike/pm_shared/pm_shared.c:2569 */
NOBODY void PM_Physics_Toss(void)
{
//	pmtrace_t trace;                                              //  2571
//	vec3_t move;                                                  //  2572
//	float backoff;                                                //  2573
//	PM_AddGravity(void);  //  2594
//	{
//		float vel;                                            //  2636
//		vec3_t base;                                          //  2637
//	}
}

/* <2cdba2> ../cstrike/pm_shared/pm_shared.c:2674 */
NOBODY void PM_NoClip(void)
{
//	int i;                                                        //  2676
//	vec3_t wishvel;                                               //  2677
//	float fmove;                                                  //  2678
//	float smove;                                                  //  2678
}

/* <2ccab0> ../cstrike/pm_shared/pm_shared.c:2711 */
NOBODY void PM_PreventMegaBunnyJumping(void)
{
//	float spd;                                                    //  2714
//	float fraction;                                               //  2716
//	float maxscaledspeed;                                         //  2718
}

/* <2cc541> ../cstrike/pm_shared/pm_shared.c:2741 */
NOBODY void PM_Jump(void)
{
//	float fvol;                                                   //  2743
//	float fvel;                                                   //  2744
//	{
//		float flRatio;                                        //  2847
//	}
}

/* <2cdc4b> ../cstrike/pm_shared/pm_shared.c:2869 */
NOBODY void PM_CheckWaterJump(void)
{
//	vec3_t vecStart;                                              //  2871
//	vec3_t vecEnd;                                                //  2871
//	vec3_t flatforward;                                           //  2872
//	vec3_t flatvelocity;                                          //  2873
//	float curspeed;                                               //  2874
//	pmtrace_t tr;                                                 //  2875
//	int savehull;                                                 //  2876
}

/* <2cdcd3> ../cstrike/pm_shared/pm_shared.c:2933 */
NOBODY void PM_CheckFalling(void)
{
//	{
//		float fvol;                                           //  2939
//		PM_MapTextureTypeStepType(char chTextureType);  //  2963
//		PM_PlayStepSound(int step,
//				float fvol);  //  2963
//	}
}

/* <2cdd60> ../cstrike/pm_shared/pm_shared.c:2988 */
NOBODY void PM_PlayWaterSounds(void)
{
}

/* <2cdd76> ../cstrike/pm_shared/pm_shared.c:3018 */
NOXREF float PM_CalcRoll(vec_t *angles, vec_t *velocity, float rollangle, float rollspeed)
{
	long double sign;
	long double side;
	long double value;

	vec3_t forward;
	vec3_t right;
	vec3_t up;

	AngleVectors(angles, forward, right, up);

	side = velocity[0] * right[0] + velocity[1] * right[1] + velocity[2] * right[2];

	sign = side < 0 ? -1 : 1;

	side = fabs(side);

	value = rollangle;

	if (side < rollspeed)
		side = side * value / rollspeed;
	else
		side = value;

	return side * sign;
}

/* <2cde69> ../cstrike/pm_shared/pm_shared.c:3053 */
NOXREF void PM_DropPunchAngle(vec_t *punchangle)
{
	long double len = VectorNormalize(punchangle);

	len -= (len * 0.5f + 10.0f) * pmove->frametime;
	len = max(len, 0.0f);

	VectorScale(punchangle, len, punchangle);
}

/* <2cdeb8> ../cstrike/pm_shared/pm_shared.c:3069 */
void PM_CheckParamters(void)
{
	long double spd;
	float maxspeed;
	vec3_t v_angle;

	spd = sqrt((long double)(pmove->cmd.sidemove * pmove->cmd.sidemove + pmove->cmd.forwardmove * pmove->cmd.forwardmove + pmove->cmd.upmove * pmove->cmd.upmove));

	maxspeed = pmove->clientmaxspeed;

	if (maxspeed)
	{
		if (maxspeed <= pmove->clientmaxspeed)
			maxspeed = pmove->maxspeed;

		pmove->maxspeed = maxspeed;
	}

	if (spd)
	{
		if (spd > pmove->maxspeed)
		{
			long double fRatio = pmove->maxspeed / spd;

			pmove->cmd.forwardmove *= fRatio;
			pmove->cmd.sidemove *= fRatio;
			pmove->cmd.upmove *= fRatio;
		}
	}

	if ((pmove->flags & (FL_FROZEN | FL_ONTRAIN)) || pmove->dead)
	{
		pmove->cmd.forwardmove = 0.0f;
		pmove->cmd.sidemove = 0.0f;
		pmove->cmd.upmove = 0.0f;
	}

	PM_DropPunchAngle(pmove->punchangle);

	if (pmove->dead)
	{
		pmove->angles[0] = pmove->oldangles[0];
		pmove->angles[1] = pmove->oldangles[1];
		pmove->angles[2] = pmove->oldangles[2];
	}
	else
	{
		v_angle[0] = pmove->cmd.viewangles[0] + pmove->punchangle[0];
		v_angle[1] = pmove->cmd.viewangles[1] + pmove->punchangle[1];
		v_angle[2] = pmove->cmd.viewangles[2] + pmove->punchangle[2];

		pmove->angles[2] = PM_CalcRoll(v_angle, pmove->velocity, pmove->movevars->rollangle, pmove->movevars->rollspeed) * 4.0f;
		pmove->angles[0] = v_angle[0];
		pmove->angles[1] = v_angle[1];
	}

	if (pmove->dead)
		pmove->view_ofs[2] = -8.000000f;

	if (pmove->angles[1] > 180.0f)
		pmove->angles[1] = pmove->angles[1] - 360.0f;
}

/* <2cdfc3> ../cstrike/pm_shared/pm_shared.c:3136 */
void PM_ReduceTimers(void)
{
	if (pmove->flTimeStepSound > 0)
	{
		pmove->flTimeStepSound -= pmove->cmd.msec;
		if (pmove->flTimeStepSound < 0)
			pmove->flTimeStepSound = 0;
	}

	if (pmove->flDuckTime > 0)
	{
		pmove->flDuckTime -= pmove->cmd.msec;
		if (pmove->flDuckTime < 0)
			pmove->flDuckTime = 0;
	}

	if (pmove->flSwimTime > 0)
	{
		pmove->flSwimTime -= pmove->cmd.msec;
		if (pmove->flSwimTime < 0)
			pmove->flSwimTime = 0;
	}

	if (pmove->fuser2 > 0.0)
	{
		pmove->fuser2 -= pmove->cmd.msec;
		if (pmove->fuser2 < 0.0)
			pmove->fuser2 = 0;
	}
}

/* <2cc577> ../cstrike/pm_shared/pm_shared.c:3203 */
NOXREF qboolean PM_ShouldDoSpectMode(void)
{
	return (pmove->iuser3 <= 0 || pmove->deadflag == DEAD_DEAD);
}

/* <2cdfe9> ../cstrike/pm_shared/pm_shared.c:3225 */
NOBODY void PM_PlayerMove(qboolean server)
{
//	physent_t *pLadder;                                          //  3227
//	PM_ShouldDoSpectMode(void);  //  3251
//	PM_InWater(void);  //  3457
//	PM_Jump(void);  //  3392
//	PM_AddCorrectGravity(void);  //  3360
//	PM_Jump(void);  //  3343
//	PM_FixupGravityVelocity(void);  //  3459
}

/* <2ce101> ../cstrike/pm_shared/pm_shared.c:3479 */
void PM_CreateStuckTable(void)
{
	float x, y, z;
	int idx;
	int i;
	float zi[3];

	Q_memset(rgv3tStuckTable, 0, sizeof(rgv3tStuckTable));

	idx = 0;
	x = y = 0;

	for (z = -0.125; z <= 0.125; z += 0.125, idx++)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;
	}

	x = z = 0;

	for (y = -0.125; y <= 0.125; y += 0.125, idx++)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;
	}

	y = z = 0;

	for (x = -0.125; x <= 0.125; x += 0.125, idx++)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;
	}

	for (x = -0.125; x <= 0.125; x += 0.250)
	{
		for (y = -0.125; y <= 0.125; y += 0.250)
		{
			for (z = -0.125; z <= 0.125; z += 0.250, idx++)
			{
				rgv3tStuckTable[idx][0] = x;
				rgv3tStuckTable[idx][1] = y;
				rgv3tStuckTable[idx][2] = z;
			}
		}
	}

	x = y = 0;
	zi[0] = 0;
	zi[1] = 1;
	zi[2] = 6;

	for (i = 0; i < 3; i++, idx++)
	{
		z = zi[i];
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;
	}

	x = z = 0.0;

	for (y = -2.0; y <= 2.0; y += 2.0, idx++)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;
	}

	y = z = 0;

	for (x = -2.0; x <= 2.0; x += 2.0, idx++)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;
	}

	for (i = 0; i < 3; i++)
	{
		z = zi[i];

		for (y = -2.0; y <= 2.0; y += 2.0)
		{
			for (z = -2.0; z <= 2.0; z += 2.0, idx++)
			{
				rgv3tStuckTable[idx][0] = x;
				rgv3tStuckTable[idx][1] = y;
				rgv3tStuckTable[idx][2] = z;
			}
		}
	}
}

/* <2ce182> ../cstrike/pm_shared/pm_shared.c:3596 */
void PM_Move(struct playermove_s *ppmove, int server)
{
	assert( pm_shared_initialized );

	pmove = ppmove;

	PM_PlayerMove((server != 0) ? TRUE : FALSE);// TODO: Reverse me
	
	if (pmove->onground != -1)
		pmove->flags |= FL_ONGROUND;
	else
		pmove->flags &= ~FL_ONGROUND;

	if (!pmove->multiplayer && pmove->movetype == MOVETYPE_WALK)
		pmove->friction = 1.0f;
}

/* <2ce1c1> ../cstrike/pm_shared/pm_shared.c:3620 */
NOXREF int PM_GetVisEntInfo(int ent)
{
	if (ent >= 0 && ent <= pmove->numvisent)
		return pmove->visents[ent].info;

	return -1;
}

/* <2ce1ee> ../cstrike/pm_shared/pm_shared.c:3629 */
NOXREF int PM_GetPhysEntInfo(int ent)
{
	if (ent >= 0 && ent <= pmove->numphysent)
		return pmove->physents[ent].info;

	return -1;
}

/* <2ce21b> ../cstrike/pm_shared/pm_shared.c:3638 */
void PM_Init(struct playermove_s *ppmove)
{
	assert( !pm_shared_initialized );

	pmove = ppmove;

	PM_CreateStuckTable();
	PM_InitTextureTypes();

	pm_shared_initialized = 1;
}
