#include "precompiled.h"

BOOL pm_shared_initialized = FALSE;

vec3_t rgv3tStuckTable[54];
int rgStuckLast[MAX_CLIENTS][2];

int pm_gcTextures = 0;
char pm_grgszTextureName[MAX_TEXTURES][MAX_TEXTURENAME_LENGHT];
char pm_grgchTextureType[MAX_TEXTURES];

playermove_t *pmove = nullptr;
BOOL g_onladder = FALSE;

#ifdef CLIENT_DLL
	int iJumpSpectator;
	float vJumpOrigin[3];
	float vJumpAngles[3];
#endif

void PM_SwapTextures(int i, int j)
{
	char chTemp;
	char szTemp[MAX_TEXTURENAME_LENGHT];

	Q_strcpy(szTemp, pm_grgszTextureName[i]);
	chTemp = pm_grgchTextureType[i];

	Q_strcpy(pm_grgszTextureName[i], pm_grgszTextureName[j]);
	pm_grgchTextureType[i] = pm_grgchTextureType[j];

	Q_strcpy(pm_grgszTextureName[j], szTemp);
	pm_grgchTextureType[j] = chTemp;
}

NOXREF qboolean PM_IsThereGrassTexture()
{
	for (int i = 0; i < pm_gcTextures; i++)
	{
		if (pm_grgchTextureType[i] == CHAR_TEX_GRASS)
			return TRUE;
	}

	return FALSE;
}

void PM_SortTextures()
{
	// Bubble sort, yuck, but this only occurs at startup and it's only 512 elements...
	int i, j;
	for (i = 0; i < pm_gcTextures; i++)
	{
		for (j = i + 1; j < pm_gcTextures; j++)
		{
			if (Q_stricmp(pm_grgszTextureName[i], pm_grgszTextureName[j]) > 0)
			{
				// Swap
				PM_SwapTextures(i, j);
			}
		}
	}
}

void PM_InitTextureTypes()
{
	char buffer[512];
	int i, j;
	byte *pMemFile;
	int fileSize, filePos = 0;
	static bool bTextureTypeInit = false;

	if (bTextureTypeInit)
		return;

	Q_memset(&(pm_grgszTextureName[0][0]), 0, sizeof(pm_grgszTextureName));
	Q_memset(pm_grgchTextureType, 0, sizeof(pm_grgchTextureType));

	pm_gcTextures = 0;
	Q_memset(buffer, 0, sizeof(buffer));

	pMemFile = pmove->COM_LoadFile("sound/materials.txt", 5, &fileSize);
	if (!pMemFile)
		return;

	// for each line in the file...
	while (pmove->memfgets(pMemFile, fileSize, &filePos, buffer, sizeof(buffer) - 1) && (pm_gcTextures < MAX_TEXTURES))
	{
		// skip whitespace
		i = 0;
		while (buffer[i] && isspace(buffer[i]))
			i++;

		if (!buffer[i])
			continue;

		// skip comment lines
		if (buffer[i] == '/' || !isalpha(buffer[i]))
			continue;

		// get texture type
		pm_grgchTextureType[pm_gcTextures] = toupper(buffer[i++]);

		// skip whitespace
		while (buffer[i] && isspace(buffer[i]))
			i++;

		if (!buffer[i])
			continue;

		// get sentence name
		j = i;
		while (buffer[j] && !isspace(buffer[j]))
			j++;

		if (!buffer[j])
			continue;

		// null-terminate name and save in sentences array
		j = Q_min(j, MAX_TEXTURENAME_LENGHT - 1 + i);
		buffer[j] = '\0';

		Q_strcpy(&(pm_grgszTextureName[pm_gcTextures++][0]), &(buffer[i]));
	}

	// Must use engine to free since we are in a .dll
	pmove->COM_FreeFile(pMemFile);

	PM_SortTextures();
	bTextureTypeInit = true;
}

char EXT_FUNC PM_FindTextureType(char *name)
{
	int left, right, pivot;
	int val;

	assert(pm_shared_initialized);

	left = 0;
	right = pm_gcTextures - 1;

	while (left <= right)
	{
		pivot = (left + right) / 2;

		val = Q_strnicmp(name, pm_grgszTextureName[pivot], MAX_TEXTURENAME_LENGHT - 1);

		if (val == 0)
		{
			return pm_grgchTextureType[pivot];
		}
		else if (val > 0)
		{
			left = pivot + 1;
		}
		else if (val < 0)
		{
			right = pivot - 1;
		}
	}

	return CHAR_TEX_CONCRETE;
}

void PM_PlayStepSound(int step, float fvol)
{
	static int iSkipStep = 0;
	int irand;

	pmove->iStepLeft = !pmove->iStepLeft;

	if (!pmove->runfuncs)
	{
		return;
	}

	irand = pmove->RandomLong(0, 1) + (pmove->iStepLeft * 2);

	// FIXME mp_footsteps needs to be a movevar
	if (pmove->multiplayer && !pmove->movevars->footsteps)
		return;

	// irand - 0,1 for right foot, 2,3 for left foot
	// used to alternate left and right foot
	// FIXME, move to player state
	switch (step)
	{
	default:
	case STEP_CONCRETE:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_step1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_step3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_step2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_step4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_METAL:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_metal4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_DIRT:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_dirt4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_VENT:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_duct4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_GRATE:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_grate4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_TILE:
		if (!pmove->RandomLong(0, 4))
			irand = 4;

		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 4: pmove->PM_PlaySound(CHAN_BODY, "player/pl_tile5.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_SLOSH:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_slosh4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_WADE:
		if (iSkipStep == 0)
		{
			iSkipStep++;
			break;
		}

		if (iSkipStep++ == 3)
		{
			iSkipStep = 0;
		}

		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}

		break;
	case STEP_LADDER:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_ladder4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	case STEP_SNOW:
		switch (irand)
		{
		// right foot
		case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow1.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow3.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		// left foot
		case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow2.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_snow4.wav", fvol, ATTN_NORM, 0, PITCH_NORM); break;
		}
		break;
	}
}

int PM_MapTextureTypeStepType(char chTextureType)
{
	switch (chTextureType)
	{
	default:
	case CHAR_TEX_CONCRETE: return STEP_CONCRETE;
	case CHAR_TEX_METAL:    return STEP_METAL;
	case CHAR_TEX_DIRT:     return STEP_DIRT;
	case CHAR_TEX_VENT:     return STEP_VENT;
	case CHAR_TEX_GRATE:    return STEP_GRATE;
	case CHAR_TEX_TILE:     return STEP_TILE;
	case CHAR_TEX_SLOSH:    return STEP_SLOSH;
	case CHAR_TEX_SNOW:     return STEP_SNOW;
	}
}

void PM_CatagorizeTextureType()
{
	vec3_t start, end;
	const char *pTextureName;

	VectorCopy(pmove->origin, start);
	VectorCopy(pmove->origin, end);

	// Straight down
	end[2] -= 64.0f;

	// Fill in default values, just in case.
	pmove->sztexturename[0] = '\0';
	pmove->chtexturetype = CHAR_TEX_CONCRETE;

	pTextureName = pmove->PM_TraceTexture(pmove->onground, start, end);

	if (!pTextureName)
		return;

	// strip leading '-0' or '+0~' or '{' or '!'
	if (*pTextureName == '-' || *pTextureName == '+')
		pTextureName += 2;

	if (*pTextureName == '{' || *pTextureName == '!' || *pTextureName == '~' || *pTextureName == ' ')
		pTextureName++;

	Q_strcpy(pmove->sztexturename, pTextureName);
	pmove->sztexturename[MAX_TEXTURENAME_LENGHT - 1] = '\0';

	// get texture type
	pmove->chtexturetype = PM_FindTextureType(pmove->sztexturename);
}

LINK_HOOK_VOID_CHAIN2(PM_UpdateStepSound);

void EXT_FUNC __API_HOOK(PM_UpdateStepSound)()
{
	float fvol;
	vec3_t knee;
	vec3_t feet;
	vec3_t center;
	float height;
	float speed;
	int fLadder;
	int step;
	int onground;

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

	// determine if we are on a ladder
	fLadder = (pmove->movetype == MOVETYPE_FLY);

	// determine if we are not in air
	onground = (pmove->onground != -1);

	// If we're on a ladder or on the ground play step sound.
	if (fLadder || onground)
	{
		PM_CatagorizeTextureType();

		VectorCopy(pmove->origin, center);
		VectorCopy(pmove->origin, knee);
		VectorCopy(pmove->origin, feet);

		height = pmove->player_maxs[pmove->usehull][2] - pmove->player_mins[pmove->usehull][2];

		knee[2] = pmove->origin[2] - 0.3 * height;
		feet[2] = pmove->origin[2] - 0.5 * height;

		// find out what we're stepping in or on...
		if (fLadder)
		{
			step = STEP_LADDER;
			fvol = 0.35;
			pmove->flTimeStepSound = 350;
		}
		else if (pmove->PM_PointContents(knee, nullptr) == CONTENTS_WATER)
		{
			step = STEP_WADE;
			fvol = 0.65;
			pmove->flTimeStepSound = 600;
		}
		else if (pmove->PM_PointContents(feet, nullptr) == CONTENTS_WATER)
		{
			step = STEP_SLOSH;
			fvol = 0.5;
			pmove->flTimeStepSound = 300;
		}
		else
		{
			// find texture under player, if different from current texture,
			// get material type
			step = PM_MapTextureTypeStepType(pmove->chtexturetype);

			switch (pmove->chtexturetype)
			{
			default:
			case CHAR_TEX_CONCRETE:
				fvol = 0.5;
				pmove->flTimeStepSound = 300;
				break;
			case CHAR_TEX_METAL:
				fvol = 0.5;
				pmove->flTimeStepSound = 300;
				break;
			case CHAR_TEX_DIRT:
				fvol = 0.55;
				pmove->flTimeStepSound = 300;
				break;
			case CHAR_TEX_VENT:
				fvol = 0.7;
				pmove->flTimeStepSound = 300;
				break;
			case CHAR_TEX_GRATE:
				fvol = 0.5;
				pmove->flTimeStepSound = 300;
				break;
			case CHAR_TEX_TILE:
				fvol = 0.5;
				pmove->flTimeStepSound = 300;
				break;
			case CHAR_TEX_SLOSH:
				fvol = 0.5;
				pmove->flTimeStepSound = 300;
				break;
			}
		}

		if ((pmove->flags & FL_DUCKING) || fLadder)
		{
			// slower step time if ducking
			pmove->flTimeStepSound += 100;

			// play the sound
			// 35% volume if ducking
			if ((pmove->flags & FL_DUCKING) && pmove->flDuckTime < 950.0)
			{
				fvol *= 0.35;
			}
		}

		PM_PlayStepSound(step, fvol);
	}
}

// Add's the trace result to touch list, if contact is not already in list.
qboolean PM_AddToTouched(pmtrace_t tr, vec_t *impactvelocity)
{
	int i;
	for (i = 0; i < pmove->numtouch; i++)
	{
		if (pmove->touchindex[i].ent == tr.ent)
			break;
	}

	// Already in list.
	if (i != pmove->numtouch)
	{
		return FALSE;
	}

	VectorCopy(impactvelocity, tr.deltavelocity);

	if (pmove->numtouch >= MAX_PHYSENTS)
	{
		pmove->Con_DPrintf("Too many entities were touched!\n");
	}

	pmove->touchindex[pmove->numtouch++] = tr;
	return TRUE;
}

void PM_CheckVelocity()
{
	int i;

	// bound velocity
	for (i = 0; i < 3; i++)
	{
		// See if it's bogus.
		if (IS_NAN(pmove->velocity[i]))
		{
			pmove->Con_Printf("PM  Got a NaN velocity %i\n", i);
			pmove->velocity[i] = 0;
		}

		if (IS_NAN(pmove->origin[i]))
		{
			pmove->Con_Printf("PM  Got a NaN origin on %i\n", i);
			pmove->origin[i] = 0;
		}

		// Bound it.
		if (pmove->velocity[i] > pmove->movevars->maxvelocity)
		{
			pmove->Con_DPrintf("PM  Got a velocity too high on %i\n", i);
			pmove->velocity[i] = pmove->movevars->maxvelocity;
		}
		else if (pmove->velocity[i] < -pmove->movevars->maxvelocity)
		{
			pmove->Con_DPrintf("PM  Got a velocity too low on %i\n", i);
			pmove->velocity[i] = -pmove->movevars->maxvelocity;
		}
	}
}

// Slide off of the impacting object
// returns the blocked flags:
// 0x01 == floor
// 0x02 == step / wall
int PM_ClipVelocity(vec_t *in, vec_t *normal, vec_t *out, float overbounce)
{
	float change;
	real_t angle;
	real_t backoff;
	int i, blocked;

	angle = normal[2];

	// Assume unblocked.
	blocked = 0x00;

	// If the plane that is blocking us has a positive z component, then assume it's a floor.
	if (angle > 0)
	{
		blocked |= 0x01;
	}

	// If the plane has no Z, it is vertical (wall/step)
	if (!angle)
	{
		blocked |= 0x02;
	}

	// Determine how far along plane to slide based on incoming direction.
	// Scale by overbounce factor.
	backoff = DotProduct(in, normal) * overbounce;

	for (i = 0; i < 3; i++)
	{
		change = in[i] - normal[i] * backoff;
		out[i] = change;

		// If out velocity is too small, zero it out.
		if (out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON)
		{
			out[i] = 0;
		}
	}

	// Return blocking flags.
	return blocked;
}

void PM_AddCorrectGravity()
{
	real_t ent_gravity;

	if (pmove->waterjumptime)
		return;

	if (pmove->gravity != 0.0f)
		ent_gravity = pmove->gravity;
	else
		ent_gravity = 1.0f;

	// Add gravity so they'll be in the correct position during movement
	// yes, this 0.5 looks wrong, but it's not.
	pmove->velocity[2] -= (ent_gravity * pmove->movevars->gravity * 0.5f * pmove->frametime);
	pmove->velocity[2] += pmove->basevelocity[2] * pmove->frametime;

	pmove->basevelocity[2] = 0;

	PM_CheckVelocity();
}

void PM_FixupGravityVelocity()
{
	real_t ent_gravity;

	if (pmove->waterjumptime)
		return;

	if (pmove->gravity != 0.0)
		ent_gravity = pmove->gravity;
	else
		ent_gravity = 1.0;

	// Get the correct velocity for the end of the dt
	pmove->velocity[2] -= (pmove->movevars->gravity * pmove->frametime * ent_gravity * 0.5);
	PM_CheckVelocity();
}

int PM_FlyMove()
{
	int bumpcount, numbumps;
	vec3_t dir;
	float d;
	int numplanes;
	vec3_t planes[MAX_CLIP_PLANES];
	vec3_t primal_velocity, original_velocity;
	vec3_t new_velocity;
	int i, j;
	pmtrace_t trace;
	vec3_t end;
	float time_left, allFraction;
	int blocked;

	numbumps = 4;	// Bump up to four times
	blocked = 0x00;	// Assume not blocked
	numplanes = 0;	// and not sliding along any planes

	VectorCopy(pmove->velocity, original_velocity);		// Store original velocity
	VectorCopy(pmove->velocity, primal_velocity);

	allFraction = 0;
	time_left = pmove->frametime;				// Total time for this movement operation.

	for (bumpcount = 0; bumpcount < numbumps; bumpcount++)
	{
		if (!pmove->velocity[0] && !pmove->velocity[1] && !pmove->velocity[2])
			break;

		// Assume we can move all the way from the current origin to the
		// end point.
		for (i = 0; i < 3; i++)
		{
			real_t flScale = time_left * pmove->velocity[i];

			end[i] = pmove->origin[i] + flScale;
		}

		// See if we can make it from origin to end point.
		trace = pmove->PM_PlayerTrace(pmove->origin, end, PM_NORMAL, -1);

		allFraction += trace.fraction;

		// If we started in a solid object, or we were in solid space
		// the whole way, zero out our velocity and return that we
		// are blocked by floor and wall.
		if (trace.allsolid)
		{
			// entity is trapped in another solid
			VectorCopy(vec3_origin, pmove->velocity);
			return 4;
		}

		// If we moved some portion of the total distance, then
		// copy the end position into the pmove->origin and
		// zero the plane counter.
		if (trace.fraction > 0.0f)
		{
			// actually covered some distance
			VectorCopy(trace.endpos, pmove->origin);
			VectorCopy(pmove->velocity, original_velocity);

			numplanes = 0;
		}

		// If we covered the entire distance, we are done
		// and can return.
		if (trace.fraction == 1.0f)
		{
			// moved the entire distance
			break;
		}

		// Save entity that blocked us (since fraction was < 1.0)
		// for contact
		// Add it if it's not already in the list
		PM_AddToTouched(trace, pmove->velocity);

		// If the plane we hit has a high z component in the normal, then
		// it's probably a floor
		if (trace.plane.normal[2] > 0.7f)
		{
			// floor
			blocked |= 0x01;
		}

		// If the plane has a zero z component in the normal, then it's a
		// step or wall
		if (!trace.plane.normal[2])
		{
			// step / wall
			blocked |= 0x02;
		}

		// Reduce amount of pmove->frametime left by total time left * fraction
		// that we covered.
		time_left -= time_left * trace.fraction;

		// Did we run out of planes to clip against?
		if (numplanes >= MAX_CLIP_PLANES)
		{
			// this shouldn't really happen
			// Stop our movement if so.
			VectorCopy(vec3_origin, pmove->velocity);
			break;
		}

		// Set up next clipping plane
		VectorCopy(trace.plane.normal, planes[numplanes]);
		numplanes++;

		// modify original_velocity so it parallels all of the clip planes
		// relfect player velocity
		if (numplanes == 1 && pmove->movetype == MOVETYPE_WALK && (pmove->onground == -1 || pmove->friction != 1))
		{
			for (i = 0; i < numplanes; i++)
			{
				if (planes[i][2] > 0.7f)
				{
					// floor or slope
					PM_ClipVelocity(original_velocity, planes[i], new_velocity, 1);
					VectorCopy(new_velocity, original_velocity);
				}
				else
					PM_ClipVelocity(original_velocity, planes[i], new_velocity, 1.0 + pmove->movevars->bounce * (1.0 - pmove->friction));
			}

			VectorCopy(new_velocity, pmove->velocity);
			VectorCopy(new_velocity, original_velocity);
		}
		else
		{
			for (i = 0; i < numplanes; i++)
			{
				PM_ClipVelocity(original_velocity, planes[i], pmove->velocity, 1);

				for (j = 0; j < numplanes; j++)
				{
					if (j != i && DotProduct(pmove->velocity, planes[j]) < 0)
					{
						break;
					}
				}

				if (j == numplanes)
					break;
			}

			if (i == numplanes)
			{
				if (numplanes != 2)
				{
					VectorCopy(vec3_origin, pmove->velocity);
					break;
				}

				CrossProduct(planes[0], planes[1], dir);
				d = DotProduct(dir, pmove->velocity);
				VectorScale(dir, d, pmove->velocity);
			}

			if (DotProduct(pmove->velocity, primal_velocity) <= 0)
			{
				VectorCopy(vec3_origin, pmove->velocity);
				break;
			}
		}
	}

	if (allFraction == 0.0f)
	{
		VectorCopy(vec3_origin, pmove->velocity);
	}

	return blocked;
}

void PM_Accelerate(vec_t *wishdir, real_t wishspeed, float accel)
{
	int i;
	float addspeed;

	real_t currentspeed;
	real_t accelspeed;

	// Dead player's don't accelerate
	if (pmove->dead)
		return;

	// If waterjumping, don't accelerate
	if (pmove->waterjumptime)
		return;

	// See if we are changing direction a bit
	currentspeed = DotProduct(pmove->velocity, wishdir);

	// Reduce wishspeed by the amount of veer.
	addspeed = wishspeed - currentspeed;

	// If not going to add any speed, done.
	if (addspeed <= 0)
		return;

	// Determine amount of accleration.
	accelspeed = accel * pmove->frametime * wishspeed * pmove->friction;

	// Cap at addspeed
	if (accelspeed > addspeed)
		accelspeed = addspeed;

	// Adjust velocity.
	for (i = 0; i < 3; i++)
	{
		pmove->velocity[i] += accelspeed * wishdir[i];
	}
}

// Only used by players. Moves along the ground when player is a MOVETYPE_WALK.
void PM_WalkMove()
{
	int clip;
	int oldonground;
	int i;

	vec3_t wishvel;
	real_t spd;
	float fmove, smove;
	vec3_t wishdir;
	real_t wishspeed;

	//vec3_t start;	// TODO: unused
	vec3_t dest;
	vec3_t original, originalvel;
	vec3_t down, downvel;
	float downdist, updist;

	pmtrace_t trace;

	if (pmove->fuser2 > 0.0)
	{
		real_t flRatio = (100 - pmove->fuser2 * 0.001 * 19) * 0.01;

		pmove->velocity[0] *= flRatio;
		pmove->velocity[1] *= flRatio;
	}

	// Copy movement amounts
	fmove = pmove->cmd.forwardmove;
	smove = pmove->cmd.sidemove;

	// Zero out z components of movement vectors
	pmove->forward[2] = 0;
	pmove->right[2] = 0;

	// Normalize remainder of vectors.
	VectorNormalize(pmove->forward);
	VectorNormalize(pmove->right);

	// Determine x and y parts of velocity
	for (i = 0; i < 2; i++)
	{
		wishvel[i] = pmove->forward[i] * fmove + pmove->right[i] * smove;
	}

	// Zero out z part of velocity
	wishvel[2] = 0;

	// Determine maginitude of speed of move
	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	// Clamp to server defined max speed
	if (wishspeed > pmove->maxspeed)
	{
		VectorScale(wishvel, pmove->maxspeed / wishspeed, wishvel);
		wishspeed = pmove->maxspeed;
	}

	// Set pmove velocity
	pmove->velocity[2] = 0;
	PM_Accelerate(wishdir, wishspeed, pmove->movevars->accelerate);
	pmove->velocity[2] = 0;

	// Add in any base velocity to the current velocity.
	VectorAdd(pmove->velocity, pmove->basevelocity, pmove->velocity);

	spd = Length(pmove->velocity);

	if (spd < 1.0)
	{
		VectorClear(pmove->velocity);
		return;
	}

	// If we are not moving, do nothing
	//if (!pmove->velocity[0] && !pmove->velocity[1] && !pmove->velocity[2])
	//	return;

	oldonground = pmove->onground;

	// first try just moving to the destination
	dest[0] = pmove->origin[0] + pmove->velocity[0] * pmove->frametime;
	dest[1] = pmove->origin[1] + pmove->velocity[1] * pmove->frametime;
	dest[2] = pmove->origin[2];

	// first try moving directly to the next spot
	// VectorCopy(dest, start);

	trace = pmove->PM_PlayerTrace(pmove->origin, dest, PM_NORMAL, -1);

	// If we made it all the way, then copy trace end
	// as new player position.
	if (trace.fraction == 1.0f)
	{
		VectorCopy(trace.endpos, pmove->origin);
		return;
	}

	// Don't walk up stairs if not on ground.
	if (oldonground == -1 && pmove->waterlevel == 0)
	{
		return;
	}

	// If we are jumping out of water, don't do anything more.
	if (pmove->waterjumptime)
		return;

	// Try sliding forward both on ground and up 16 pixels
	// take the move that goes farthest

	// Save out original pos &
	VectorCopy(pmove->origin, original);

	// velocity.
	VectorCopy(pmove->velocity, originalvel);

	// Slide move
	clip = PM_FlyMove();

	// Copy the results out
	VectorCopy(pmove->origin, down);
	VectorCopy(pmove->velocity, downvel);

	// Reset original values.
	VectorCopy(original, pmove->origin);
	VectorCopy(originalvel, pmove->velocity);

	// Start out up one stair height
	VectorCopy(pmove->origin, dest);

	dest[2] += pmove->movevars->stepsize;

	trace = pmove->PM_PlayerTrace(pmove->origin, dest, PM_NORMAL, -1);

	// If we started okay and made it part of the way at least,
	// copy the results to the movement start position and then
	// run another move try.
	if (!trace.startsolid && !trace.allsolid)
	{
		VectorCopy(trace.endpos, pmove->origin);
	}

	// slide move the rest of the way.
	clip = PM_FlyMove();

	// Now try going back down from the end point
	//  press down the stepheight
	VectorCopy(pmove->origin, dest);
	dest[2] -= pmove->movevars->stepsize;

	trace = pmove->PM_PlayerTrace(pmove->origin, dest, PM_NORMAL, -1);

	// If we are not on the ground any more then
	// use the original movement attempt
	if (trace.plane.normal[2] < 0.7f)
		goto usedown;

	// If the trace ended up in empty space, copy the end
	// over to the origin.
	if (!trace.startsolid && !trace.allsolid)
	{
		VectorCopy(trace.endpos, pmove->origin);
	}

	// Copy this origion to up.
	VectorCopy(pmove->origin, pmove->up);

	// decide which one went farther
	downdist = (down[0] - original[0]) * (down[0] - original[0]) + (down[1] - original[1]) * (down[1] - original[1]);
	updist = (pmove->up[0] - original[0]) * (pmove->up[0] - original[0]) + (pmove->up[1] - original[1]) * (pmove->up[1] - original[1]);

	if (downdist > updist)
	{
usedown:
		VectorCopy(down, pmove->origin);
		VectorCopy(downvel, pmove->velocity);
	}
	else
	{
		// copy z value from slide move
		pmove->velocity[2] = downvel[2];
	}
}

// Handles both ground friction and water friction
void PM_Friction()
{
	float *vel;
	float speed;
	real_t newspeed, control, friction, drop;
	vec3_t newvel;

	// If we are in water jump cycle, don't apply friction
	if (pmove->waterjumptime)
		return;

	// Get velocity
	vel = pmove->velocity;

	// Calculate speed
	speed = Q_sqrt(real_t(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]));

	// If too slow, return
	if (speed < 0.1f)
	{
		return;
	}

	drop = 0;

	// apply ground friction
	// On an entity that is the ground
	if (pmove->onground != -1)
	{
		vec3_t start, stop;
		pmtrace_t trace;

		start[0] = stop[0] = pmove->origin[0] + vel[0] / speed * 16;
		start[1] = stop[1] = pmove->origin[1] + vel[1] / speed * 16;
		start[2] = pmove->origin[2] + pmove->player_mins[pmove->usehull][2];
		stop[2] = start[2] - 34;

		trace = pmove->PM_PlayerTrace(start, stop, PM_NORMAL, -1);

		if (trace.fraction == 1.0f)
			friction = pmove->movevars->friction * pmove->movevars->edgefriction;
		else
			friction = pmove->movevars->friction;

		// Grab friction value.
		//friction = pmove->movevars->friction;

		// player friction?
		friction *= pmove->friction;

		// Bleed off some speed, but if we have less than the bleed
		// threshhold, bleed the theshold amount.
		control = (speed < pmove->movevars->stopspeed) ? pmove->movevars->stopspeed : speed;

		// Add the amount to t'he drop amount.
		drop += friction * (control * pmove->frametime);
	}

	// apply water friction
	//if (pmove->waterlevel)
	//{
	//	drop += speed * pmove->movevars->waterfriction * waterlevel * pmove->frametime;
	//}

	// scale the velocity
	newspeed = speed - drop;

	if (newspeed < 0)
	{
		newspeed = 0;
	}

	// Determine proportion of old speed we are using.
	newspeed /= speed;

	// Adjust velocity according to proportion.
	newvel[0] = vel[0] * newspeed;
	newvel[1] = vel[1] * float(newspeed);
	newvel[2] = vel[2] * float(newspeed);

	VectorCopy(newvel, pmove->velocity);
}

void PM_AirAccelerate(vec_t *wishdir, float wishspeed, float accel)
{
	int i;
	float addspeed;
	float wishspd = wishspeed;

	real_t currentspeed;
	real_t accelspeed;

	if (pmove->dead || pmove->waterjumptime)
		return;

	// Cap speed
	if (wishspd > 30)
		wishspd = 30;

	// Determine veer amount
	currentspeed = DotProduct(pmove->velocity, wishdir);

	// See how much to add
	addspeed = wishspd - currentspeed;

	// If not adding any, done.
	if (addspeed <= 0)
		return;

	// Determine acceleration speed after acceleration
	accelspeed = accel * wishspeed * pmove->frametime * pmove->friction;

	// Cap it
	if (accelspeed > addspeed)
		accelspeed = addspeed;

	// Adjust pmove vel.
	for (i = 0; i < 3; i++)
	{
		pmove->velocity[i] += accelspeed * wishdir[i];
	}
}

void PM_WaterMove()
{
	int i;
	vec3_t wishvel;
	vec3_t wishdir;
	vec3_t start, dest;
	vec3_t temp;
	pmtrace_t trace;

	real_t speed, accelspeed, wishspeed;
	float newspeed, addspeed;

	// user intentions
	for (i = 0; i < 3; i++)
	{
		wishvel[i] = (pmove->forward[i] * pmove->cmd.forwardmove) + (pmove->cmd.sidemove * pmove->right[i]);
	}

	// Sinking after no other movement occurs
	if (!pmove->cmd.forwardmove && !pmove->cmd.sidemove && !pmove->cmd.upmove)
	{
		// drift towards bottom
		wishvel[2] -= 60.0f;
	}
	else
	{
		// Go straight up by upmove amount.
		wishvel[2] += pmove->cmd.upmove;
	}

	// Copy it over and determine speed
	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	// Cap speed.
	if (wishspeed > pmove->maxspeed)
	{
		VectorScale(wishvel, pmove->maxspeed / wishspeed, wishvel);
		wishspeed = pmove->maxspeed;
	}

	// Slow us down a bit.
	wishspeed *= 0.8;
	VectorAdd(pmove->velocity, pmove->basevelocity, pmove->velocity);

	// Water friction
	VectorCopy(pmove->velocity, temp);
	speed = VectorNormalize(temp);

	if (speed)
	{
		newspeed = speed - pmove->movevars->friction * pmove->friction * pmove->frametime * speed;

		if (newspeed < 0.0f)
		{
			newspeed = 0.0f;
		}

		VectorScale(pmove->velocity, newspeed / speed, pmove->velocity);
	}
	else
		newspeed = 0;

	// water acceleration
	if (float(wishspeed) < 0.1f)
	{
		return;
	}

	addspeed = float(wishspeed) - newspeed;

	if (addspeed > 0.0f)
	{
		VectorNormalize(wishvel);
		accelspeed = pmove->movevars->accelerate * pmove->friction * pmove->frametime * float(wishspeed);

		if (accelspeed > addspeed)
		{
			accelspeed = addspeed;
		}

		for (i = 0; i < 3; i++)
		{
			pmove->velocity[i] += accelspeed * wishvel[i];
		}
	}

	// Now move
	// assume it is a stair or a slope, so press down from stepheight above
	VectorMA(pmove->origin, pmove->frametime, pmove->velocity, dest);
	VectorCopy(dest, start);

	start[2] += pmove->movevars->stepsize + 1;
	trace = pmove->PM_PlayerTrace(start, dest, PM_NORMAL, -1);

	// FIXME: check steep slope?
	if (!trace.startsolid && !trace.allsolid)
	{
		// walked up the step, so just keep result and exit
		VectorCopy(trace.endpos, pmove->origin);
		return;
	}

	// Try moving straight along out normal path.
	PM_FlyMove();
}

LINK_HOOK_VOID_CHAIN(PM_AirMove, (int playerIndex = 0), pmove->player_index + 1);

void EXT_FUNC __API_HOOK(PM_AirMove)(int playerIndex)
{
	PM_AirMove_internal();
}

void PM_AirMove_internal()
{
	int i;
	vec3_t wishvel;
	float fmove, smove;
	vec3_t wishdir;
	float wishspeed;

	// Copy movement amounts
	fmove = pmove->cmd.forwardmove;
	smove = pmove->cmd.sidemove;

	// Zero out z components of movement vectors
	pmove->forward[2] = 0;
	pmove->right[2] = 0;

	// Renormalize
	VectorNormalize(pmove->forward);
	VectorNormalize(pmove->right);

	// Determine x and y parts of velocity
	for (i = 0; i < 2; i++)
	{
		wishvel[i] = pmove->forward[i] * fmove + pmove->right[i] * smove;
	}

	// Zero out z part of velocity
	wishvel[2] = 0;

	 // Determine maginitude of speed of move
	VectorCopy(wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	// Clamp to server defined max speed
	if (wishspeed > pmove->maxspeed)
	{
		VectorScale(wishvel, pmove->maxspeed/wishspeed, wishvel);
		wishspeed = pmove->maxspeed;
	}

	PM_AirAccelerate(wishdir, wishspeed, pmove->movevars->airaccelerate);

	// Add in any base velocity to the current velocity.
	VectorAdd(pmove->velocity, pmove->basevelocity, pmove->velocity);

	PM_FlyMove();
}

qboolean PM_InWater()
{
	return (pmove->waterlevel > 1) ? TRUE : FALSE;
}

// Sets pmove->waterlevel and pmove->watertype values.
qboolean PM_CheckWater()
{
#ifdef REGAMEDLL_FIXES
	// do not check for dead
	if (pmove->dead || pmove->deadflag != DEAD_NO)
		return FALSE;
#endif

	vec3_t point;
	int cont;
	int truecont;
	float height;
	float heightover2;

	// Pick a spot just above the players feet.
	point[0] = pmove->origin[0] + (pmove->player_mins[pmove->usehull][0] + pmove->player_maxs[pmove->usehull][0]) * 0.5f;
	point[1] = pmove->origin[1] + (pmove->player_mins[pmove->usehull][1] + pmove->player_maxs[pmove->usehull][1]) * 0.5f;
	point[2] = pmove->origin[2] + pmove->player_mins[pmove->usehull][2] + 1;

	// Assume that we are not in water at all.
	pmove->waterlevel = 0;
	pmove->watertype = CONTENTS_EMPTY;

	// Grab point contents.
	cont = pmove->PM_PointContents(point, &truecont);

	// Are we under water? (not solid and not empty?)
	if (cont <= CONTENTS_WATER && cont > CONTENTS_TRANSLUCENT)
	{
		// Set water type
		pmove->watertype = cont;

		// We are at least at level one
		pmove->waterlevel = 1;

		height = (pmove->player_mins[pmove->usehull][2] + pmove->player_maxs[pmove->usehull][2]);
		heightover2 = height * 0.5;

		// Now check a point that is at the player hull midpoint.
		point[2] = pmove->origin[2] + heightover2;
		cont = pmove->PM_PointContents(point, nullptr);

		// If that point is also under water...
		if (cont <= CONTENTS_WATER && cont > CONTENTS_TRANSLUCENT)
		{
			// Set a higher water level.
			pmove->waterlevel = 2;

			// Now check the eye position.  (view_ofs is relative to the origin)
			point[2] = pmove->origin[2] + pmove->view_ofs[2];

			cont = pmove->PM_PointContents(point, nullptr);
			if (cont <= CONTENTS_WATER && cont > CONTENTS_TRANSLUCENT)
			{
				// In over our eyes
				pmove->waterlevel = 3;
			}
		}

		// Adjust velocity based on water current, if any.
		if ((truecont <= CONTENTS_CURRENT_0) && (truecont >= CONTENTS_CURRENT_DOWN))
		{
			// The deeper we are, the stronger the current.
			static vec3_t current_table[] =
			{
				{1, 0, 0}, {0, 1, 0}, {-1, 0, 0},
				{0, -1, 0}, {0, 0, 1}, {0, 0, -1}
			};

			VectorMA(pmove->basevelocity, 50.0 * pmove->waterlevel, current_table[CONTENTS_CURRENT_0 - truecont], pmove->basevelocity);
		}
	}

	return (pmove->waterlevel > 1) ? TRUE : FALSE;
}

void PM_CategorizePosition()
{
	vec3_t point;
	pmtrace_t tr;

	// if the player hull point one unit down is solid, the player
	// is on ground

	// see if standing on something solid

	// Doing this before we move may introduce a potential latency in water detection, but
	// doing it after can get us stuck on the bottom in water if the amount we move up
	// is less than the 1 pixel 'threshold' we're about to snap to.	Also, we'll call
	// this several times per frame, so we really need to avoid sticking to the bottom of
	// water on each call, and the converse case will correct itself if called twice.
	PM_CheckWater();

	point[0] = pmove->origin[0];
	point[1] = pmove->origin[1];
	point[2] = pmove->origin[2] - 2;

	// Shooting up really fast.  Definitely not on ground.
	if (pmove->velocity[2] > 180)
	{
		pmove->onground = -1;
		return;
	}

	// Try and move down.
	tr = pmove->PM_PlayerTrace(pmove->origin, point, PM_NORMAL, -1);

	// If we hit a steep plane, we are not on ground
	if (tr.plane.normal[2] < 0.7f)
	{
		// too steep
		pmove->onground = -1;
	}
	else
	{
		// Otherwise, point to index of ent under us.
		pmove->onground = tr.ent;
	}

	// If we are on something...
	if (pmove->onground != -1)
	{
		// Then we are not in water jump sequence
		pmove->waterjumptime = 0;

		// If we could make the move, drop us down that 1 pixel
		if (pmove->waterlevel < 2 && !tr.startsolid && !tr.allsolid)
		{
			VectorCopy(tr.endpos, pmove->origin);
		}
	}

	// Standing on an entity other than the world
	// So signal that we are touching something.
	if (tr.ent > 0)
	{
		PM_AddToTouched(tr, pmove->velocity);
	}
}

// When a player is stuck, it's costly to try and unstick them
// Grab a test offset for the player based on a passed in index
int PM_GetRandomStuckOffsets(int nIndex, int server, vec_t *offset)
{
	// Last time we did a full
	int idx = rgStuckLast[nIndex][server]++;
	VectorCopy(rgv3tStuckTable[idx % ARRAYSIZE(rgv3tStuckTable)], offset);
	return (idx % ARRAYSIZE(rgv3tStuckTable));
}

void PM_ResetStuckOffsets(int nIndex, int server)
{
	rgStuckLast[nIndex][server] = 0;
}

// If pmove->origin is in a solid position,
// try nudging slightly on all axis to
// allow for the cut precision of the net coordinates
qboolean PM_CheckStuck()
{
	vec3_t base;
	vec3_t offset;
	vec3_t test;
	int hitent;
	int idx;
	real_t fTime;
	int i;
	pmtrace_t traceresult;

	// Last time we did a full
	static float rgStuckCheckTime[MAX_CLIENTS][2];

	// If position is okay, exit
	hitent = pmove->PM_TestPlayerPosition(pmove->origin, &traceresult);
	if (hitent == -1)
	{
		PM_ResetStuckOffsets(pmove->player_index, pmove->server);
		return FALSE;
	}

	VectorCopy(pmove->origin, base);

	// Deal with precision error in network.
	if (!pmove->server)
	{
		// World or BSP model
		if (hitent == 0 || pmove->physents[hitent].model)
		{
			int nReps = 0;
			PM_ResetStuckOffsets(pmove->player_index, pmove->server);
			do
			{
				i = PM_GetRandomStuckOffsets(pmove->player_index, pmove->server, offset);

				VectorAdd(base, offset, test);
				if (pmove->PM_TestPlayerPosition(test, &traceresult) == -1)
				{
					PM_ResetStuckOffsets(pmove->player_index, pmove->server);
					VectorCopy(test, pmove->origin);
					return FALSE;
				}

				nReps++;
			}
			while (nReps < ARRAYSIZE(rgv3tStuckTable));
		}
	}

	// Only an issue on the client.
	if (pmove->server)
		idx = 0;
	else
		idx = 1;

	fTime = pmove->Sys_FloatTime();

	// Too soon?
	if (rgStuckCheckTime[pmove->player_index][idx] >= (fTime - PM_CHECKSTUCK_MINTIME))
	{
		return TRUE;
	}

	rgStuckCheckTime[pmove->player_index][idx] = fTime;

	pmove->PM_StuckTouch(hitent, &traceresult);

	i = PM_GetRandomStuckOffsets(pmove->player_index, pmove->server, offset);

	VectorAdd(base, offset, test);
	if ((hitent = pmove->PM_TestPlayerPosition(test, nullptr)) == -1)
	{
		PM_ResetStuckOffsets(pmove->player_index, pmove->server);

		if (i >= (ARRAYSIZE(rgv3tStuckTable) / 2))
		{
			VectorCopy(test, pmove->origin);
		}

		return FALSE;
	}

	// If player is flailing while stuck in another player (should never happen), then see
	//  if we can't "unstick" them forceably.
	if ((pmove->cmd.buttons & (IN_JUMP | IN_DUCK | IN_ATTACK)) && pmove->physents[hitent].player != 0)
	{
		float x, y, z;
		float xystep = 8.0;
		float zstep = 18.0;
		float xyminmax = xystep;
		float zminmax = 4 * zstep;

		for (z = 0; z <= zminmax; z += zstep)
		{
			for (x = -xyminmax; x <= xyminmax; x += xystep)
			{
				for (y = -xyminmax; y <= xyminmax; y += xystep)
				{
					VectorCopy(base, test);

					test[0] += x;
					test[1] += y;
					test[2] += z;

					if (pmove->PM_TestPlayerPosition(test, nullptr) == -1)
					{
						VectorCopy(test, pmove->origin);
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

void PM_SpectatorMove()
{
	real_t speed, drop, friction;
	real_t control, newspeed;
	float currentspeed, addspeed;
	real_t accelspeed;
	int i;
	vec3_t wishvel;
	float fmove, smove;
	vec3_t wishdir;
	real_t wishspeed;

	// this routine keeps track of the spectators psoition
	// there a two different main move types : track player or moce freely (OBS_ROAMING)
	// doesn't need excate track position, only to generate PVS, so just copy
	// targets position and real view position is calculated on client (saves server CPU)
	if (pmove->iuser1 == OBS_ROAMING)
	{
#ifdef CLIENT_DLL
		if (iJumpSpectator)
		{
			VectorCopy(vJumpOrigin, pmove->origin);
			VectorCopy(vJumpAngles, pmove->angles);
			VectorCopy(vec3_origin, pmove->velocity);
			iJumpSpectator = 0;
			return;
		}
#endif
		// Move around in normal spectator method
		speed = Length (pmove->velocity);

		if (speed >= 1.0)
		{
			drop = 0;

			// extra friction
			friction = pmove->movevars->friction * 1.5;
			control = speed < pmove->movevars->stopspeed ? pmove->movevars->stopspeed : speed;
			drop += friction * (control * pmove->frametime);

			// scale the velocity
			newspeed = speed - drop;

			if (newspeed < 0)
			{
				newspeed = 0;
			}
			newspeed /= speed;

			VectorScale(pmove->velocity, newspeed, pmove->velocity);
		}
		else
		{
			VectorCopy(vec3_origin, pmove->velocity);
		}

		// accelerate
		fmove = pmove->cmd.forwardmove;
		smove = pmove->cmd.sidemove;

		VectorNormalize(pmove->forward);
		VectorNormalize(pmove->right);

		for (i = 0; i < 3; i++)
		{
			wishvel[i] = pmove->forward[i] * fmove + pmove->right[i] * smove;
		}

		wishvel[2] += pmove->cmd.upmove;

		VectorCopy(wishvel, wishdir);
		wishspeed = VectorNormalize(wishdir);

		// clamp to server defined max speed
		if (wishspeed > pmove->movevars->spectatormaxspeed)
		{
			VectorScale(wishvel, pmove->movevars->spectatormaxspeed / wishspeed, wishvel);
			wishspeed = pmove->movevars->spectatormaxspeed;
		}

		currentspeed = DotProduct(pmove->velocity, wishdir);

		addspeed = wishspeed - currentspeed;
		if (addspeed <= 0)
		{
			return;
		}

		accelspeed = pmove->movevars->accelerate * pmove->frametime * wishspeed;
		if (accelspeed > addspeed)
		{
			accelspeed = addspeed;
		}

		for (i = 0; i < 3; i++)
		{
			pmove->velocity[i] += accelspeed * wishdir[i];
		}

		// move
		VectorMA(pmove->origin, pmove->frametime, pmove->velocity, pmove->origin);
	}
	else
	{
		// all other modes just track some kind of target, so spectator PVS = target PVS
		int target;

		// no valid target ?
		if (pmove->iuser2 <= 0)
			return;

		// Find the client this player's targeting
		for (target = 0; target < pmove->numphysent; target++)
		{
			if (pmove->physents[target].info == pmove->iuser2)
				break;
		}

		if (target == pmove->numphysent)
			return;

		// use targets position as own origin for PVS
		VectorCopy(pmove->physents[target].angles, pmove->angles);
		VectorCopy(pmove->physents[target].origin, pmove->origin);

		// no velocity
		VectorCopy(vec3_origin, pmove->velocity);
	}
}

// Use for ease-in, ease-out style interpolation (accel/decel)
// Used by ducking code.
float PM_SplineFraction(float value, float scale)
{
	real_t valueSquared;

	value = scale * value;
	valueSquared = value * value;

	// Nice little ease-in, ease-out spline-like curve
	return 3 * valueSquared - 2 * valueSquared * value;
}

NOXREF float PM_SimpleSpline(float value)
{
	float valueSquared;

	valueSquared = value * value;

	return 3 * valueSquared - 2 * valueSquared * value;
}

void PM_FixPlayerCrouchStuck(int direction)
{
	int hitent;
	int i;
	vec3_t test;

	hitent = pmove->PM_TestPlayerPosition(pmove->origin, nullptr);

	if (hitent == -1)
	{
		return;
	}

	VectorCopy(pmove->origin, test);

	for (i = 0; i < HalfHumanHeight; i++)
	{
		pmove->origin[2] += direction;
		hitent = pmove->PM_TestPlayerPosition(pmove->origin, nullptr);

		if (hitent == -1)
		{
			return;
		}
	}

	// Failed
	VectorCopy(test, pmove->origin);
}

void PM_UnDuck()
{
#ifdef REGAMEDLL_ADD
	if (unduck_method.value)
#endif
	{
#ifdef REGAMEDLL_FIXES
		// if ducking isn't finished yet, so don't unduck
		if (pmove->bInDuck || !(pmove->flags & FL_DUCKING))
		{
			pmove->usehull = 0;
			pmove->flDuckTime = 0;
			pmove->bInDuck = FALSE;
			pmove->view_ofs[2] = PM_VEC_VIEW;
			return;
		}
#endif // #ifdef REGAMEDLL_FIXES
	}

	pmtrace_t trace;
	vec3_t newOrigin;

	VectorCopy(pmove->origin, newOrigin);

	if (pmove->onground != -1)
	{
#ifdef REGAMEDLL_FIXES
		vec3_t offset;
		VectorSubtract(pmove->player_mins[1], pmove->player_mins[0], offset);
		VectorAdd(newOrigin, offset, newOrigin);
#else
		newOrigin[2] += 18.0;
#endif
	}

	trace = pmove->PM_PlayerTrace(newOrigin, newOrigin, PM_NORMAL, -1);
	if (!trace.startsolid)
	{
		pmove->usehull = 0;

		// Oh, no, changing hulls stuck us into something, try unsticking downward first.
		trace = pmove->PM_PlayerTrace(newOrigin, newOrigin, PM_NORMAL, -1);

		if (trace.startsolid)
		{
			// See if we are stuck?  If so, stay ducked with the duck hull until we have a clear spot
			// Con_Printf("unstick got stuck\n");
			pmove->usehull = 1;
			return;
		}

		pmove->flags &= ~FL_DUCKING;
		pmove->bInDuck = FALSE;
		pmove->view_ofs[2] = PM_VEC_VIEW;
		pmove->flDuckTime = 0;

		pmove->flTimeStepSound -= 100;

		if (pmove->flTimeStepSound < 0)
		{
			pmove->flTimeStepSound = 0;
		}

		VectorCopy(newOrigin, pmove->origin);

		// Recatagorize position since ducking can change origin
		PM_CategorizePosition();
	}
}

void PM_Duck()
{
	int buttonsChanged = (pmove->oldbuttons ^ pmove->cmd.buttons);	// These buttons have changed this frame
	int nButtonPressed =  buttonsChanged & pmove->cmd.buttons;		// The changed ones still down are "pressed"

	int duckchange = buttonsChanged & IN_DUCK ? 1 : 0;
	int duckpressed = nButtonPressed & IN_DUCK ? 1 : 0;

	if (pmove->cmd.buttons & IN_DUCK)
	{
		pmove->oldbuttons |= IN_DUCK;
	}
	else
	{
		pmove->oldbuttons &= ~IN_DUCK;
	}

#ifdef REGAMEDLL_ADD
	// Prevent ducking if the iuser3 variable is contain PLAYER_PREVENT_DUCK
	if ((pmove->iuser3 & PLAYER_PREVENT_DUCK) == PLAYER_PREVENT_DUCK)
	{
		// Try to unduck
		if (pmove->flags & FL_DUCKING)
		{
			PM_UnDuck();
		}

		return;
	}
#endif

	if (pmove->dead || (!(pmove->cmd.buttons & IN_DUCK) && !pmove->bInDuck && !(pmove->flags & FL_DUCKING)))
	{
		return;
	}

	pmove->cmd.forwardmove *= PLAYER_DUCKING_MULTIPLIER;
	pmove->cmd.sidemove *= PLAYER_DUCKING_MULTIPLIER;
	pmove->cmd.upmove *= PLAYER_DUCKING_MULTIPLIER;

	if (pmove->cmd.buttons & IN_DUCK)
	{
		if ((nButtonPressed & IN_DUCK) && !(pmove->flags & FL_DUCKING))
		{
			// Use 1 second so super long jump will work
			pmove->flDuckTime = 1000;
			pmove->bInDuck = TRUE;
		}

		if (pmove->bInDuck)
		{
			// Finish ducking immediately if duck time is over or not on ground
			if (((pmove->flDuckTime / 1000.0) <= (1.0 - TIME_TO_DUCK)) || pmove->onground == -1)
			{
				pmove->usehull = 1;
				pmove->view_ofs[2] = PM_VEC_DUCK_VIEW;
				pmove->flags |= FL_DUCKING;
				pmove->bInDuck = FALSE;

				// HACKHACK - Fudge for collision bug - no time to fix this properly
				if (pmove->onground != -1)
				{
#ifdef REGAMEDLL_FIXES
					vec3_t newOrigin;
					VectorSubtract(pmove->player_mins[1], pmove->player_mins[0], newOrigin);
					VectorSubtract(pmove->origin, newOrigin, pmove->origin);
#else
					pmove->origin[2] = pmove->origin[2] - 18.0;
#endif

					// See if we are stuck?
					PM_FixPlayerCrouchStuck(STUCK_MOVEUP);

					// Recatagorize position since ducking can change origin
					PM_CategorizePosition();
				}
			}
			else
			{
				real_t duckFraction = PM_VEC_VIEW;
				real_t time = (1.0 - pmove->flDuckTime / 1000.0);

				// Calc parametric time
				if (time >= 0.0) {
					duckFraction = PM_SplineFraction(time, (1.0 / TIME_TO_DUCK));
				}

#ifdef REGAMEDLL_FIXES
				float fMore = (pmove->player_mins[1][2] - pmove->player_mins[0][2]);
#else
				float fMore = (PM_VEC_DUCK_HULL_MIN - PM_VEC_HULL_MIN);
#endif

				pmove->view_ofs[2] = ((PM_VEC_DUCK_VIEW - fMore) * duckFraction) + (PM_VEC_VIEW * (1 - duckFraction));
			}
		}
	}
	// Try to unduck
	else
	{
		PM_UnDuck();
	}
}

void PM_LadderMove(physent_t *pLadder)
{
	vec3_t ladderCenter;
	trace_t trace;
	bool onFloor;
	vec3_t floor;
	vec3_t modelmins, modelmaxs;

	if (pmove->movetype == MOVETYPE_NOCLIP)
		return;

	pmove->PM_GetModelBounds(pLadder->model, modelmins, modelmaxs);

	VectorAdd(modelmins, modelmaxs, ladderCenter);
	VectorScale(ladderCenter, 0.5, ladderCenter);

	pmove->movetype = MOVETYPE_FLY;

	// On ladder, convert movement to be relative to the ladder
	VectorCopy(pmove->origin, floor);
	floor[2] += pmove->player_mins[pmove->usehull][2] - 1;

	if (pmove->PM_PointContents(floor, nullptr) == CONTENTS_SOLID)
		onFloor = true;
	else
		onFloor = false;

	pmove->gravity = 0;
	pmove->PM_TraceModel(pLadder, pmove->origin, ladderCenter, &trace);

	if (trace.fraction != 1.0f)
	{
		float forward = 0, right = 0;
		vec3_t vpn, v_right;
		float flSpeed = MAX_CLIMB_SPEED;

		// they shouldn't be able to move faster than their maxspeed
		if (flSpeed > pmove->maxspeed)
		{
			flSpeed = pmove->maxspeed;
		}

		AngleVectors(pmove->angles, vpn, v_right, nullptr);

		if (pmove->flags & FL_DUCKING)
		{
			flSpeed *= PLAYER_DUCKING_MULTIPLIER;
		}

		if (pmove->cmd.buttons & IN_BACK)
		{
			forward -= flSpeed;
		}
		if (pmove->cmd.buttons & IN_FORWARD)
		{
			forward += flSpeed;
		}
		if (pmove->cmd.buttons & IN_MOVELEFT)
		{
			right -= flSpeed;
		}
		if (pmove->cmd.buttons & IN_MOVERIGHT)
		{
			right += flSpeed;
		}

		if (pmove->cmd.buttons & IN_JUMP)
		{
			pmove->movetype = MOVETYPE_WALK;
			VectorScale(trace.plane.normal, 270, pmove->velocity);
		}
		else
		{
			if (forward != 0 || right != 0)
			{
				vec3_t velocity, perp, cross, lateral, tmp;
				float normal;

				VectorScale(vpn, forward, velocity);
				VectorMA(velocity, right, v_right, velocity);

				VectorClear(tmp);
				tmp[2] = 1;

				CrossProduct(tmp, trace.plane.normal, perp);
				VectorNormalize(perp);

				// decompose velocity into ladder plane
				normal = DotProduct(velocity, trace.plane.normal);
				// This is the velocity into the face of the ladder
				VectorScale(trace.plane.normal, normal, cross);

				// This is the player's additional velocity
				VectorSubtract(velocity, cross, lateral);

				// This turns the velocity into the face of the ladder into velocity that
				// is roughly vertically perpendicular to the face of the ladder.
				// NOTE: It IS possible to face up and move down or face down and move up
				// because the velocity is a sum of the directional velocity and the converted
				// velocity through the face of the ladder - by design.
				CrossProduct(trace.plane.normal, perp, tmp);
				VectorMA(lateral, -normal, tmp, pmove->velocity);

				// On ground moving away from the ladder
				if (onFloor && normal > 0)
				{
					VectorMA(pmove->velocity, MAX_CLIMB_SPEED, trace.plane.normal, pmove->velocity);
				}
			}
			else
			{
				VectorClear(pmove->velocity);
			}
		}
	}
}

physent_t *PM_Ladder()
{
	int i;
	physent_t *pe;
	hull_t *hull;
	int num;
	vec3_t test;

	for (i = 0; i < pmove->nummoveent; i++)
	{
		pe = &pmove->moveents[i];

		if (pe->model && (modtype_t)pmove->PM_GetModelType(pe->model) == mod_brush && pe->skin == CONTENTS_LADDER)
		{
			hull = (hull_t *)pmove->PM_HullForBsp(pe, test);
			num = hull->firstclipnode;

			// Offset the test point appropriately for this hull.
			VectorSubtract(pmove->origin, test, test);

			// Test the player's hull for intersection with this model
			if (pmove->PM_HullPointContents(hull, num, test) == CONTENTS_EMPTY)
			{
				continue;
			}

			return pe;
		}
	}

	return nullptr;
}

void PM_WaterJump()
{
	if (pmove->waterjumptime > 10000)
	{
		pmove->waterjumptime = 10000;
	}

	if (!pmove->waterjumptime)
	{
		return;
	}

	pmove->waterjumptime -= pmove->cmd.msec;

	if (pmove->waterjumptime < 0 || !pmove->waterlevel)
	{
		pmove->waterjumptime = 0;
		pmove->flags &= ~FL_WATERJUMP;
	}

	pmove->velocity[0] = pmove->movedir[0];
	pmove->velocity[1] = pmove->movedir[1];
}

void PM_AddGravity()
{
	float ent_gravity;

	if (pmove->gravity != 0.0f)
		ent_gravity = pmove->gravity;
	else
		ent_gravity = 1.0f;

	pmove->velocity[2] -= (ent_gravity * pmove->movevars->gravity * pmove->frametime);
	pmove->velocity[2] += pmove->basevelocity[2] * pmove->frametime;

	pmove->basevelocity[2] = 0;
	PM_CheckVelocity();
}

// Does not change the entities velocity at all
pmtrace_t PM_PushEntity(vec_t *push)
{
	pmtrace_t trace;
	vec3_t end;

	VectorAdd(pmove->origin, push, end);

	trace = pmove->PM_PlayerTrace(pmove->origin, end, PM_NORMAL, -1);

	VectorCopy(trace.endpos, pmove->origin);

	// So we can run impact function afterwards.
	if (trace.fraction < 1.0f && !trace.allsolid)
	{
		PM_AddToTouched(trace, pmove->velocity);
	}

	return trace;
}

void PM_Physics_Toss()
{
	pmtrace_t trace;
	vec3_t move;
	float backoff;

	PM_CheckWater();

	if (pmove->velocity[2] > 0)
	{
		pmove->onground = -1;
	}

	// If on ground and not moving, return.
	if (pmove->onground != -1)
	{
		if (VectorCompare(pmove->basevelocity, vec3_origin) && VectorCompare(pmove->velocity, vec3_origin))
		{
			return;
		}
	}

	PM_CheckVelocity();

	// add gravity
	if (pmove->movetype != MOVETYPE_FLY && pmove->movetype != MOVETYPE_BOUNCEMISSILE && pmove->movetype != MOVETYPE_FLYMISSILE)
	{
		PM_AddGravity();
	}

	// move origin
	// Base velocity is not properly accounted for since this entity will move again after the bounce without
	// taking it into account
	VectorAdd(pmove->velocity, pmove->basevelocity, pmove->velocity);

	PM_CheckVelocity();
	VectorScale(pmove->velocity, pmove->frametime, move);
	VectorSubtract(pmove->velocity, pmove->basevelocity, pmove->velocity);

	// Should this clear basevelocity
	trace = PM_PushEntity(move);

	PM_CheckVelocity();

	if (trace.allsolid)
	{
		// entity is trapped in another solid
		pmove->onground = trace.ent;
		VectorCopy(vec3_origin, pmove->velocity);
		return;
	}

	if (trace.fraction == 1.0f)
	{
		PM_CheckWater();
		return;
	}

	if (pmove->movetype == MOVETYPE_BOUNCE)
	{
		backoff = 2.0f - pmove->friction;
	}
	else if (pmove->movetype == MOVETYPE_BOUNCEMISSILE)
	{
		backoff = 2.0f;
	}
	else
		backoff = 1.0f;

	PM_ClipVelocity(pmove->velocity, trace.plane.normal, pmove->velocity, backoff);

	// stop if on ground
	if (trace.plane.normal[2] > 0.7f)
	{
		float vel;
		vec3_t base;

		VectorClear(base);
		if (pmove->velocity[2] < pmove->movevars->gravity * pmove->frametime)
		{
			// we're rolling on the ground, add static friction.
			pmove->onground = trace.ent;
			pmove->velocity[2] = 0;
		}

		vel = DotProduct(pmove->velocity, pmove->velocity);

		if (vel < (30 * 30) || (pmove->movetype != MOVETYPE_BOUNCE && pmove->movetype != MOVETYPE_BOUNCEMISSILE))
		{
			pmove->onground = trace.ent;
			VectorCopy(vec3_origin, pmove->velocity);
		}
		else
		{
			VectorScale(pmove->velocity, (1.0f - trace.fraction) * pmove->frametime * 0.9f, move);
			trace = PM_PushEntity(move);
		}

		VectorSubtract(pmove->velocity, base, pmove->velocity);
	}

	// check for in water
	PM_CheckWater();
}

void PM_NoClip()
{
	int i;
	vec3_t wishvel;
	float fmove, smove;

	// Copy movement amounts
	fmove = pmove->cmd.forwardmove;
	smove = pmove->cmd.sidemove;

	VectorNormalize(pmove->forward);
	VectorNormalize(pmove->right);

	// Determine x and y parts of velocity
	for (i = 0; i < 3; i++)
	{
		wishvel[i] = pmove->forward[i] * fmove + pmove->right[i] * smove;
	}

	wishvel[2] += pmove->cmd.upmove;

	VectorMA(pmove->origin, pmove->frametime, wishvel, pmove->origin);

	// Zero out the velocity so that we don't accumulate a huge downward velocity from
	// gravity, etc.
	VectorClear(pmove->velocity);
}

// Purpose: Corrects bunny jumping (where player initiates a bunny jump before other
// movement logic runs, thus making onground == -1 thus making PM_Friction get skipped and
// running PM_AirMove, which doesn't crop velocity to maxspeed like the ground / other
// movement logic does.
void PM_PreventMegaBunnyJumping()
{
	// Current player speed
	real_t spd;
	// If we have to crop, apply this cropping fraction to velocity
	float fraction;
	// Speed at which bunny jumping is limited
	float maxscaledspeed;

	maxscaledspeed = BUNNYJUMP_MAX_SPEED_FACTOR * pmove->maxspeed;

	// Don't divide by zero
	if (maxscaledspeed <= 0.0f)
		return;

	spd = Length(pmove->velocity);

	if (spd <= maxscaledspeed)
		return;

	// Returns the modifier for the velocity
	fraction = (maxscaledspeed / spd) * 0.8;

	// Crop it down!.
	VectorScale(pmove->velocity, fraction, pmove->velocity);
}

void PM_Jump()
{
	if (pmove->dead)
	{
		// don't jump again until released
		pmove->oldbuttons |= IN_JUMP;
		return;
	}

	// See if we are waterjumping.  If so, decrement count and return.
	if (pmove->waterjumptime != 0.0f)
	{
		pmove->waterjumptime -= pmove->cmd.msec;

		if (pmove->waterjumptime < 0)
		{
			pmove->waterjumptime = 0;
		}

		return;
	}

	// If we are in the water most of the way...
	if (pmove->waterlevel >= 2)
	{
		// swimming, not jumping
		pmove->onground = -1;

		// We move up a certain amount
		if (pmove->watertype == CONTENTS_WATER)
		{
			pmove->velocity[2] = 100;
		}
		else if (pmove->watertype == CONTENTS_SLIME)
		{
			pmove->velocity[2] = 80;
		}
		else // LAVA
			pmove->velocity[2] = 50;

		// play swiming sound
		if (pmove->flSwimTime <= 0)
		{
			// Don't play sound again for 1 second
			pmove->flSwimTime = 1000.0f;

			switch (pmove->RandomLong(0, 3))
			{
			case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
			case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade2.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
			case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade3.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
			case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade4.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
			}
		}

		return;
	}

#ifdef REGAMEDLL_ADD
	// Prevent jumping if the iuser3 variable is contain PLAYER_PREVENT_JUMP
	if ((pmove->iuser3 & PLAYER_PREVENT_JUMP) == PLAYER_PREVENT_JUMP)
	{
		return;
	}
#endif

	// No more effect
	// in air, so no effect
 	if (pmove->onground == -1)
	{
		// Flag that we jumped.
		// don't jump again until released
		pmove->oldbuttons |= IN_JUMP;
		return;
	}

	// don't pogo stick
	if (pmove->oldbuttons & IN_JUMP)
	{
		return;
	}

	if (pmove->bInDuck && (pmove->flags & FL_DUCKING))
	{
		return;
	}

	PM_CatagorizeTextureType();

	// In the air now.
	pmove->onground = -1;

	PM_PreventMegaBunnyJumping();

	real_t fvel = Length(pmove->velocity);
	float fvol = 1.0f;

	if (fvel >= 150.0f)
	{
		PM_PlayStepSound(PM_MapTextureTypeStepType(pmove->chtexturetype), fvol);
	}

#ifdef REGAMEDLL_ADD
	// See if user can super long jump?
	bool cansuperjump = (pmove->PM_Info_ValueForKey(pmove->physinfo, "slj")[0] == '1');

	// Acclerate upward
	// If we are ducking...
	if (pmove->bInDuck || (pmove->flags & FL_DUCKING))
	{
		// Adjust for super long jump module
		// UNDONE: note this should be based on forward angles, not current velocity.
		if (cansuperjump && (pmove->cmd.buttons & IN_DUCK) && pmove->flDuckTime > 0 && Length(pmove->velocity) > 50)
		{
			pmove->punchangle[0] = -5.0f;

			for (int i  = 0; i < 2; i++)
			{
				pmove->velocity[i] = pmove->forward[i] * PLAYER_LONGJUMP_SPEED * 1.6f;
			}

			pmove->velocity[2] = Q_sqrt(2 * 800 * 56.0f);
		}
		else
		{
			pmove->velocity[2] = Q_sqrt(2 * 800 * 45.0f);
		}
	}
	else
#endif
	{
		// NOTE: don't do it in .f (float)
		pmove->velocity[2] = Q_sqrt(2.0 * 800.0f * 45.0f);
	}

	if (pmove->fuser2 > 0.0f)
	{
		// NOTE: don't do it in .f (float)
		real_t flRatio = (100.0 - pmove->fuser2 * 0.001 * 19.0) * 0.01;
		pmove->velocity[2] *= flRatio;
	}

	pmove->fuser2 = 1315.789429;

	// Decay it for simulation
	PM_FixupGravityVelocity();

	// Flag that we jumped.
	// don't jump again until released
	pmove->oldbuttons |= IN_JUMP;
}

void PM_CheckWaterJump()
{
	vec3_t vecStart, vecEnd;
	vec3_t flatforward;
	vec3_t flatvelocity;
	float curspeed;
	pmtrace_t tr;
	int savehull;

	// Already water jumping.
	if (pmove->waterjumptime)
		return;

	// Don't hop out if we just jumped in
	if (pmove->velocity[2] < -180)
	{
		// only hop out if we are moving up
		return;
	}

	// See if we are backing up
	flatvelocity[0] = pmove->velocity[0];
	flatvelocity[1] = pmove->velocity[1];
	flatvelocity[2] = 0;

	// Must be moving
	curspeed = VectorNormalize(flatvelocity);

	// see if near an edge
	flatforward[0] = pmove->forward[0];
	flatforward[1] = pmove->forward[1];
	flatforward[2] = 0;
	VectorNormalize(flatforward);

	// Are we backing into water from steps or something?  If so, don't pop forward
	if (curspeed != 0.0 && (DotProduct(flatvelocity, flatforward) < 0.0))
	{
		return;
	}

	VectorCopy(pmove->origin, vecStart);
	vecStart[2] += WJ_HEIGHT;

	VectorMA(vecStart, 24, flatforward, vecEnd);

	// Trace, this trace should use the point sized collision hull
	savehull = pmove->usehull;
	pmove->usehull = 2;

	tr = pmove->PM_PlayerTrace(vecStart, vecEnd, PM_NORMAL, -1);

	// Facing a near vertical wall?
	if (tr.fraction < 1.0f && Q_fabs(real_t(tr.plane.normal[2])) < 0.1f)
	{
		vecStart[2] += pmove->player_maxs[savehull][2] - WJ_HEIGHT;

		VectorMA(vecStart, 24, flatforward, vecEnd);
		VectorMA(vec3_origin, -50, tr.plane.normal, pmove->movedir);

		tr = pmove->PM_PlayerTrace(vecStart, vecEnd, PM_NORMAL, -1);

		if (tr.fraction == 1.0f)
		{
			pmove->waterjumptime = 2000.0f;
			pmove->velocity[2] = 225.0f;

			pmove->oldbuttons |= IN_JUMP;
			pmove->flags |= FL_WATERJUMP;
		}
	}

	// Reset the collision hull
	pmove->usehull = savehull;
}

void PM_CheckFalling()
{
	if (pmove->onground != -1 && !pmove->dead && pmove->flFallVelocity >= PM_PLAYER_FALL_PUNCH_THRESHHOLD)
	{
		float fvol = 0.5f;

		if (pmove->waterlevel <= 0)
		{
			if (pmove->flFallVelocity > PM_PLAYER_MAX_SAFE_FALL_SPEED)
			{
				fvol = 1.0f;
			}
			else if (pmove->flFallVelocity > PM_PLAYER_MAX_SAFE_FALL_SPEED / 2)
			{
				fvol = 0.85f;
			}
			else if (pmove->flFallVelocity < PM_PLAYER_MIN_BOUNCE_SPEED)
			{
				fvol = 0.0f;
			}
		}

		if (fvol > 0.0f)
		{
			PM_CatagorizeTextureType();

			// play step sound for current texture
			PM_PlayStepSound(PM_MapTextureTypeStepType(pmove->chtexturetype), fvol);

			pmove->flTimeStepSound = 300;

			// Knock the screen around a little bit, temporary effect
			// punch z axis
			pmove->punchangle[2] = pmove->flFallVelocity * 0.013;

			if (pmove->punchangle[0] > 8.0f)
			{
				pmove->punchangle[0] = 8.0f;
			}
		}
	}

	if (pmove->onground != -1)
	{
		pmove->flFallVelocity = 0;
	}
}

void PM_PlayWaterSounds()
{
	// Did we enter or leave water?
	if (pmove->oldwaterlevel != 0)
	{
		if (pmove->waterlevel != 0)
			return;
	}
	else
	{
		if (pmove->waterlevel == 0)
			return;
	}

	switch (pmove->RandomLong(0, 3))
	{
	case 0: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
	case 1: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade2.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
	case 2: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade3.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
	case 3: pmove->PM_PlaySound(CHAN_BODY, "player/pl_wade4.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM); break;
	}
}

float PM_CalcRoll(vec_t *angles, vec_t *velocity, float rollangle, float rollspeed)
{
	float sign;
	real_t side;
	float value;
	vec3_t forward, right, up;

	AngleVectors(angles, forward, right, up);

	side = DotProduct(velocity, right);
	sign = side < 0 ? -1 : 1;
	side = Q_fabs(side);

	value = rollangle;

	if (side < rollspeed)
	{
		side = side * value / rollspeed;
	}
	else
	{
		side = value;
	}

	return side * sign;
}

void PM_DropPunchAngle(vec_t *punchangle)
{
	real_t len;

	len = VectorNormalize(punchangle);
	len -= (10.0 + len * 0.5) * pmove->frametime;
#ifdef PLAY_GAMEDLL
	len = Q_max(len, 0.0);
#else
	len = Q_max(len, 0.0f);
#endif
	VectorScale(punchangle, len, punchangle);
}

void PM_CheckParameters()
{
	float spd;
	real_t maxspeed;
	vec3_t v_angle;

	spd = Q_sqrt(real_t(pmove->cmd.sidemove * pmove->cmd.sidemove + pmove->cmd.forwardmove * pmove->cmd.forwardmove + pmove->cmd.upmove * pmove->cmd.upmove));

	maxspeed = pmove->clientmaxspeed;

	if (maxspeed != 0.0f)
	{
		pmove->maxspeed = Q_min(maxspeed, real_t(pmove->maxspeed));
	}

	if (spd != 0.0f && spd > real_t(pmove->maxspeed))
	{
		real_t fRatio = pmove->maxspeed / spd;

		pmove->cmd.forwardmove *= fRatio;
		pmove->cmd.sidemove *= fRatio;
		pmove->cmd.upmove *= fRatio;
	}

	if ((pmove->flags & (FL_FROZEN | FL_ONTRAIN)) || pmove->dead)
	{
		pmove->cmd.forwardmove = 0;
		pmove->cmd.sidemove = 0;
		pmove->cmd.upmove = 0;
	}

	PM_DropPunchAngle(pmove->punchangle);

	// Take angles from command.
	if (!pmove->dead)
	{
		VectorCopy(pmove->cmd.viewangles, v_angle);
		VectorAdd(v_angle, pmove->punchangle, v_angle);

		// Set up view angles.
		pmove->angles[ROLL] = PM_CalcRoll(v_angle, pmove->velocity, pmove->movevars->rollangle, pmove->movevars->rollspeed) * 4;
		pmove->angles[PITCH] = v_angle[PITCH];
		pmove->angles[YAW] = v_angle[YAW];
	}
	else
	{
		VectorCopy(pmove->oldangles, pmove->angles);
	}

	// Set dead player view_offset
	if (pmove->dead)
	{
#ifdef REGAMEDLL_FIXES
		if (pmove->bInDuck)
		{
			PM_UnDuck();
			pmove->bInDuck = FALSE;
		}
#endif

		pmove->view_ofs[2] = PM_DEAD_VIEWHEIGHT;
	}

	// Adjust client view angles to match values used on server.
	if (pmove->angles[YAW] > 180.0f)
	{
		pmove->angles[YAW] -= 360.0f;
	}
}

void PM_ReduceTimers()
{
	if (pmove->flTimeStepSound > 0)
	{
		pmove->flTimeStepSound -= pmove->cmd.msec;

		if (pmove->flTimeStepSound < 0)
		{
			pmove->flTimeStepSound = 0;
		}
	}

	if (pmove->flDuckTime > 0)
	{
		pmove->flDuckTime -= pmove->cmd.msec;

		if (pmove->flDuckTime < 0)
		{
			pmove->flDuckTime = 0;
		}
	}

	if (pmove->flSwimTime > 0)
	{
		pmove->flSwimTime -= pmove->cmd.msec;

		if (pmove->flSwimTime < 0)
		{
			pmove->flSwimTime = 0;
		}
	}

	if (pmove->fuser2 > 0.0)
	{
		pmove->fuser2 -= pmove->cmd.msec;

		if (pmove->fuser2 < 0.0)
		{
			pmove->fuser2 = 0;
		}
	}
}

qboolean PM_ShouldDoSpectMode()
{
	return (pmove->iuser3 <= 0 || pmove->deadflag == DEAD_DEAD);
}

// Returns with origin, angles, and velocity modified in place.
// Numtouch and touchindex[] will be set if any of the physents
// were contacted during the move.
void PM_PlayerMove(qboolean server)
{
	physent_t *pLadder = nullptr;

	// Are we running server code?
	pmove->server = server;

	// Adjust speeds etc.
	PM_CheckParameters();

	// Assume we don't touch anything
	pmove->numtouch = 0;

	// # of msec to apply movement

	//double v2 = (double)pmove->cmd.msec * 0.001;
	pmove->frametime = pmove->cmd.msec * 0.001;

	PM_ReduceTimers();

	// Convert view angles to vectors
	AngleVectors(pmove->angles, pmove->forward, pmove->right, pmove->up);

	//PM_ShowClipBox();

	// Special handling for spectator and observers. (iuser1 is set if the player's in observer mode)
	if ((pmove->spectator || pmove->iuser1 > 0) && PM_ShouldDoSpectMode())
	{
		PM_SpectatorMove();
		PM_CategorizePosition();
		return;
	}

	// Always try and unstick us unless we are in NOCLIP mode
	if (pmove->movetype != MOVETYPE_NOCLIP && pmove->movetype != MOVETYPE_NONE)
	{
		if (PM_CheckStuck())
		{
			// Can't move, we're stuck
			return;
		}
	}

	// Now that we are "unstuck", see where we are (waterlevel and type, pmove->onground).
	PM_CategorizePosition();

	// Store off the starting water level
	pmove->oldwaterlevel = pmove->waterlevel;

	// If we are not on ground, store off how fast we are moving down
	if (pmove->onground == -1)
	{
		pmove->flFallVelocity = -pmove->velocity[2];
	}

	g_onladder = FALSE;

	// Don't run ladder code if dead or on a train
	if (!pmove->dead && !(pmove->flags & FL_ONTRAIN)
#ifdef REGAMEDLL_ADD
		&& !(pmove->iuser3 & PLAYER_PREVENT_CLIMB)
#endif
		)
	{
		pLadder = PM_Ladder();

		if (pLadder)
		{
			g_onladder = TRUE;
		}
	}

	PM_Duck();
	PM_UpdateStepSound();

	// Don't run ladder code if dead or on a train
	if (!pmove->dead && !(pmove->flags & FL_ONTRAIN))
	{
		if (pLadder)
		{
			PM_LadderMove(pLadder);
		}
		else if (pmove->movetype != MOVETYPE_WALK && pmove->movetype != MOVETYPE_NOCLIP)
		{
			// Clear ladder stuff unless player is noclipping
			// it will be set immediately again next frame if necessary
			pmove->movetype = MOVETYPE_WALK;
		}
	}

	// Handle movement
	switch (pmove->movetype)
	{
	default:
		pmove->Con_DPrintf("Bogus pmove player movetype %i on (%i) 0=cl 1=sv\n", pmove->movetype, pmove->server);
		break;

	case MOVETYPE_NONE:
		break;

	case MOVETYPE_NOCLIP:
		PM_NoClip();
		break;

	case MOVETYPE_TOSS:
	case MOVETYPE_BOUNCE:
		PM_Physics_Toss();
		break;

	case MOVETYPE_FLY:
		PM_CheckWater();

		// Was jump button pressed?
		// If so, set velocity to 270 away from ladder.  This is currently wrong.
		// Also, set MOVE_TYPE to walk, too.
		if (pmove->cmd.buttons & IN_JUMP)
		{
			if (!pLadder)
			{
				PM_Jump();
			}
		}
		else
		{
			pmove->oldbuttons &= ~IN_JUMP;
		}

		// Perform the move accounting for any base velocity.
		VectorAdd(pmove->velocity, pmove->basevelocity, pmove->velocity);
		PM_FlyMove();
		VectorSubtract(pmove->velocity, pmove->basevelocity, pmove->velocity);
		break;

	case MOVETYPE_WALK:
		if (!PM_InWater())
		{
			PM_AddCorrectGravity();
		}

		// If we are leaping out of the water, just update the counters.
		if (pmove->waterjumptime != 0.0f)
		{
			PM_WaterJump();
			PM_FlyMove();

			// Make sure waterlevel is set correctly
			PM_CheckWater();
			return;
		}

		// If we are swimming in the water, see if we are nudging against a place we can jump up out
		//  of, and, if so, start out jump.  Otherwise, if we are not moving up, then reset jump timer to 0
		if (pmove->waterlevel >= 2)
		{
			if (pmove->waterlevel == 2)
			{
				PM_CheckWaterJump();
			}

			// If we are falling again, then we must not trying to jump out of water any more.
			if (pmove->velocity[2] < 0 && pmove->waterjumptime)
			{
				pmove->waterjumptime = 0;
			}

			// Was jump button pressed?
			if (pmove->cmd.buttons & IN_JUMP)
			{
				PM_Jump();
			}
			else
			{
				pmove->oldbuttons &= ~IN_JUMP;
			}

			// Perform regular water movement
			PM_WaterMove();

			VectorSubtract(pmove->velocity, pmove->basevelocity, pmove->velocity);

			// Get a final position
			PM_CategorizePosition();
		}
		// Not underwater
		else
		{
			// Was jump button pressed?
			if (pmove->cmd.buttons & IN_JUMP)
			{
				if (!pLadder)
				{
					PM_Jump();
				}
			}
			else
			{
				pmove->oldbuttons &= ~IN_JUMP;
			}

			// Fricion is handled before we add in any base velocity. That way, if we are on a conveyor,
			// we don't slow when standing still, relative to the conveyor.
			if (pmove->onground != -1)
			{
				pmove->velocity[2] = 0;
				PM_Friction();
			}

			// Make sure velocity is valid.
			PM_CheckVelocity();

			// Are we on ground now
			if (pmove->onground != -1)
			{
				PM_WalkMove();
			}
			else
			{
				// Take into account movement when in air.
				PM_AirMove();
			}

			// Set final flags.
			PM_CategorizePosition();

			// Now pull the base velocity back out.
			// Base velocity is set if you are on a moving object, like
			// a conveyor (or maybe another monster?)
			VectorSubtract(pmove->velocity, pmove->basevelocity, pmove->velocity);

			// Make sure velocity is valid.
			PM_CheckVelocity();

			// Add any remaining gravitational component.
			if (!PM_InWater())
			{
				PM_FixupGravityVelocity();
			}

			// If we are on ground, no downward velocity.
			if (pmove->onground != -1)
			{
				pmove->velocity[2] = 0;
			}

			// See if we landed on the ground with enough force to play a landing sound.
			PM_CheckFalling();
		}

		// Did we enter or leave the water?
		PM_PlayWaterSounds();
		break;
	}
}

void PM_CreateStuckTable()
{
	float x, y, z;

	int idx;
	int i;
	float zi[3];

	Q_memset(rgv3tStuckTable, 0, sizeof(rgv3tStuckTable));

	idx = 0;

	// Little Moves.
	x = 0;
	y = 0;

	// Z moves
	for (z = -0.125; z <= 0.125; z += 0.125)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;

		idx++;
	}

	x = 0;
	z = 0;
	// Y moves
	for (y = -0.125; y <= 0.125; y += 0.125)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;

		idx++;
	}

	y = 0;
	z = 0;
	// X moves
	for (x = -0.125; x <= 0.125; x += 0.125)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;

		idx++;
	}

	// Remaining multi axis nudges.
	for (x = -0.125; x <= 0.125; x += 0.250)
	{
		for (y = -0.125; y <= 0.125; y += 0.250)
		{
			for (z = -0.125; z <= 0.125; z += 0.250)
			{
				rgv3tStuckTable[idx][0] = x;
				rgv3tStuckTable[idx][1] = y;
				rgv3tStuckTable[idx][2] = z;

				idx++;
			}
		}
	}

	// Big Moves.
	x = 0;
	y = 0;

	zi[0] = 0.0f;
	zi[1] = 1.0f;
	zi[2] = 6.0f;

	for (i = 0; i < 3; i++)
	{
		// Z moves
		z = zi[i];

		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;

		idx++;
	}

	x = 0;
	z = 0;

	// Y moves
	for (y = -2.0f; y <= 2.0f; y += 2.0)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;

		idx++;
	}

	y = 0;
	z = 0;

	// X moves
	for (x = -2.0f; x <= 2.0f; x += 2.0f)
	{
		rgv3tStuckTable[idx][0] = x;
		rgv3tStuckTable[idx][1] = y;
		rgv3tStuckTable[idx][2] = z;

		idx++;
	}

	// Remaining multi axis nudges.
	for (i = 0; i < 3; i++)
	{
		z = zi[i];

		for (x = -2.0f; x <= 2.0f; x += 2.0f)
		{
			for (y = -2.0f; y <= 2.0f; y += 2.0)
			{
				rgv3tStuckTable[idx][0] = x;
				rgv3tStuckTable[idx][1] = y;
				rgv3tStuckTable[idx][2] = z;

				idx++;
			}
		}
	}
}

LINK_HOOK_VOID_CHAIN(PM_Move, (struct playermove_s *ppmove, int server), ppmove, server);

// This module implements the shared player physics code between any particular game and
// the engine. The same PM_Move routine is built into the game .dll and the client .dll and is
// invoked by each side as appropriate. There should be no distinction, internally, between server
// and client. This will ensure that prediction behaves appropriately.
void EXT_FUNC __API_HOOK(PM_Move)(struct playermove_s *ppmove, int server)
{
	assert(pm_shared_initialized);

	pmove = ppmove;

	PM_PlayerMove((server != 0) ? TRUE : FALSE);

	if (pmove->onground != -1)
		pmove->flags |= FL_ONGROUND;
	else
		pmove->flags &= ~FL_ONGROUND;

	if (!pmove->multiplayer && pmove->movetype == MOVETYPE_WALK)
	{
		pmove->friction = 1.0f;
	}
}

NOXREF int PM_GetVisEntInfo(int ent)
{
	if (ent >= 0 && ent <= pmove->numvisent)
	{
		return pmove->visents[ent].info;
	}

	return -1;
}

NOXREF int PM_GetPhysEntInfo(int ent)
{
	if (ent >= 0 && ent <= pmove->numphysent)
	{
		return pmove->physents[ent].info;
	}

	return -1;
}

LINK_HOOK_VOID_CHAIN(PM_Init, (struct playermove_s *ppmove), ppmove);

void EXT_FUNC __API_HOOK(PM_Init)(struct playermove_s *ppmove)
{
	assert(!pm_shared_initialized);

	pmove = ppmove;

	PM_CreateStuckTable();
	PM_InitTextureTypes();

	pm_shared_initialized = TRUE;
}
