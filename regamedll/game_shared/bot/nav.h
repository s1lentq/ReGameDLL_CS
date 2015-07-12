/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef NAV_H
#define NAV_H
#ifdef _WIN32
#pragma once
#endif

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

// to help identify nav files
#define NAV_MAGIC_NUMBER 0xFEEDFACE

// A place is a named group of navigation areas
typedef unsigned int Place;

// ie: "no place"
#define UNDEFINED_PLACE		0
#define ANY_PLACE		0xFFFF

#define WALK_THRU_DOORS		0x01
#define WALK_THRU_BREAKABLES	0x02

//class CNavArea;
//class CNavNode;

enum NavErrorType
{
	NAV_OK,
	NAV_CANT_ACCESS_FILE,
	NAV_INVALID_FILE,
	NAV_BAD_FILE_VERSION,
	NAV_CORRUPT_DATA,
};

enum NavAttributeType
{
	NAV_CROUCH = 0x01,	// must crouch to use this node/area
	NAV_JUMP = 0x02,	// must jump to traverse this area
	NAV_PRECISE = 0x04,	// do not adjust for obstacles, just move along area
	NAV_NO_JUMP = 0x08,	// inhibit discontinuity jumping
};

enum NavDirType
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST,

	NUM_DIRECTIONS
};

// Defines possible ways to move from one area to another
enum NavTraverseType
{
	// NOTE: First 4 directions MUST match NavDirType
	GO_NORTH = 0,
	GO_EAST,
	GO_SOUTH,
	GO_WEST,
	GO_LADDER_UP,
	GO_LADDER_DOWN,
	GO_JUMP,

	NUM_TRAVERSE_TYPES
};

enum NavCornerType
{
	NORTH_WEST = 0,
	NORTH_EAST,
	SOUTH_EAST,
	SOUTH_WEST,

	NUM_CORNERS
};

enum NavRelativeDirType
{
	FORWARD = 0,
	RIGHT,
	BACKWARD,
	LEFT,
	UP,
	DOWN,

	NUM_RELATIVE_DIRECTIONS
};

const float GenerationStepSize = 25.0f;		// (30) was 20, but bots can't fit always fit
const float StepHeight = 18.0f;			// if delta Z is greater than this, we have to jump to get up
const float JumpHeight = 41.8f;			// if delta Z is less than this, we can jump up on it
const float JumpCrouchHeight = 58.0f;		// (48) if delta Z is less than or equal to this, we can jumpcrouch up on it

// Strictly speaking, you CAN get up a slope of 1.643 (about 59 degrees), but you move very, very slowly
// This slope will represent the slope you can navigate without much slowdown
// rise/run - if greater than this, we can't move up it (de_survivor canyon ramps)
const float MaxSlope = 1.4f;

// instead of MaxSlope, we are using the following max Z component of a unit normal
const float MaxUnitZSlope = 0.7f;

const float BotRadius = 10.0f;		// circular extent that contains bot
const float DeathDrop = 200.0f;		// (300) distance at which we will die if we fall - should be about 600, and pay attention to fall damage during pathfind

const float HalfHumanWidth = 16.0f;
const float HalfHumanHeight = 36.0f;
const float HumanHeight = 72.0f;

/* <4f7910> ../game_shared/bot/nav.h:104 */
struct Extent
{
	Vector lo;
	Vector hi;

	UNTESTED float SizeX(void) const
	{
		return hi.x - lo.x;
	}
	UNTESTED float SizeY(void) const
	{
		return hi.y - lo.y;
	}
	UNTESTED float SizeZ(void) const
	{
		return hi.z - lo.z;
	}
	UNTESTED float Area(void) const
	{
		return SizeX() * SizeY();
	}
	// return true if 'pos' is inside of this extent
	UNTESTED bool Contains(const Vector *pos) const
	{
		return (pos->x >= lo.x && pos->x <= hi.x &&
			pos->y >= lo.y && pos->y <= hi.y &&
			pos->z >= lo.z && pos->z <= hi.z);
	}

};/* size: 24, cachelines: 1, members: 2 */

struct Ray
{
	Vector from;
	Vector to;

};/* size: 24, cachelines: 1, members: 2 */

/* <34358b> ../game_shared/bot/nav.h:134 */
inline NavDirType OppositeDirection(NavDirType dir)
{
	switch (dir)
	{
		case NORTH:
			return SOUTH;
		case EAST:
			return WEST;
		case SOUTH:
			return NORTH;
		case WEST:
			return EAST;
	}

	return NORTH;
}

/* <4c3042> ../game_shared/bot/nav.h:148 */
inline NavDirType DirectionLeft(NavDirType dir)
{
	switch (dir)
	{
		case NORTH:
			return WEST;
		case SOUTH:
			return EAST;
		case EAST:
			return NORTH;
		case WEST:
			return SOUTH;
	}

	return NORTH;
}

/* <4c3061> ../game_shared/bot/nav.h:162 */
inline NavDirType DirectionRight(NavDirType dir)
{
	switch(dir)
	{
		case NORTH:
			return EAST;
		case SOUTH:
			return WEST;
		case EAST:
			return SOUTH;
		case WEST:
			return NORTH;
	}

	return NORTH;
}

/* <3433a4> ../game_shared/bot/nav.h:176 */
inline void AddDirectionVector(Vector *v, NavDirType dir, float amount)
{
	switch(dir)
	{
		case NORTH:
			v->y -= amount;
			return;
		case EAST: 
			v->x += amount;
			return;
		case SOUTH:
			v->y += amount;
			return;
		case WEST: 
			v->x -= amount;
			return;
	}
}

/* <38c828> ../game_shared/bot/nav.h:188 */
inline float DirectionToAngle(NavDirType dir)
{
	switch(dir)
	{
		case NORTH:
			return 270.0f;
		case EAST:
			return 0.0f;
		case SOUTH:
			return 90.0f;
		case WEST:
			return 180.0f;
	}

	return 0.0f;
}

/* <3d8335> ../game_shared/bot/nav.h:202 */
inline NavDirType AngleToDirection(float angle)
{
	while (angle < 0.0f)
		angle += 360.0f;

	while (angle > 360.0f)
		angle -= 360.0f;

	if (angle < 45 || angle > 315)
		return EAST;

	if (angle >= 45 && angle < 135)
		return SOUTH;

	if (angle >= 135 && angle < 225)
		return WEST;

	return NORTH;
}

/* <38ccf5> ../game_shared/bot/nav.h:223 */
inline void DirectionToVector2D(NavDirType dir, Vector2D *v)
{
	switch (dir)
	{
		case NORTH:
			v->x =  0.0f;
			v->y = -1.0f;
			break;
		case SOUTH:
			v->x =  0.0f;
			v->y =  1.0f;
			break;
		case EAST:
			v->x =  1.0f;
			v->y =  0.0f;
			break;
		case WEST:
			v->x = -1.0f;
			v->y =  0.0f;
			break;
	}
}

/* <3433d1> ../game_shared/bot/nav.h:235 */
inline void SnapToGrid(Vector *pos)
{
	int cx = pos->x / GenerationStepSize;
	int cy = pos->y / GenerationStepSize;
	pos->x = cx * GenerationStepSize;
	pos->y = cy * GenerationStepSize;
}

/* <3433d1> ../game_shared/bot/nav.h:235 */
inline void SnapToGrid(float *value)
{
	int c = *value / GenerationStepSize;
	*value = c * GenerationStepSize;
}

/* <14ea2f> ../game_shared/bot/nav.h:251 */
inline float_precision NormalizeAngle(float_precision angle)
{
	while (angle < -180.0f)
		angle += 360.0f;
	
	while (angle > 180.0f)
		angle -= 360.0f;

	return angle;
}

/* <4ad17f> ../game_shared/bot/nav.h:263 */
inline float NormalizeAnglePositive(float angle)
{
	while (angle < 0.0f)
		angle += 360.0f;
	
	while (angle >= 360.0f)
		angle -= 360.0f;

	return angle;
}

/* <38c40b> ../game_shared/bot/nav.h:275 */
inline float AngleDifference(float a, float b)
{
	float angleDiff = a - b;

	while (angleDiff > 180.0f)
		angleDiff -= 360.0f;

	while (angleDiff < -180.0f)
		angleDiff += 360.0f;

	return angleDiff;
}

/* <38cac9> ../game_shared/bot/nav.h:288 */
inline bool AnglesAreEqual(float a, float b, float tolerance = 5.0f)
{
	if (abs( AngleDifference( a, b ) ) < tolerance)
		return true;

	return false;
}

/* <3d8457> ../game_shared/bot/nav.h:297 */
inline bool VectorsAreEqual(const Vector *a, const Vector *b, float tolerance = 0.1f)
{
	if (abs(a->x - b->x) < tolerance &&
			abs(a->y - b->y) < tolerance &&
			abs(a->z - b->z) < tolerance)
		return true;

	return false;
}

/* <3436f6> ../game_shared/bot/nav.h:313 */
inline bool IsEntityWalkable(entvars_t *entity, unsigned int flags)
{
	// if we hit a door, assume its walkable because it will open when we touch it
	if (FClassnameIs(entity, "func_door") || FClassnameIs(entity, "func_door_rotating"))
		return (flags & WALK_THRU_DOORS) ? true : false;

	// if we hit a breakable object, assume its walkable because we will shoot it when we touch it
	if (FClassnameIs(entity, "func_breakable") && entity->takedamage == DAMAGE_YES)
		return (flags & WALK_THRU_BREAKABLES) ? true : false;

	return false;
}

// Check LOS, ignoring any entities that we can walk through
/* <38d33d> ../game_shared/bot/nav.h:330 */
inline bool IsWalkableTraceLineClear(Vector &from, Vector &to, unsigned int flags = 0)
{
	TraceResult result;
	edict_t *ignore = NULL;
	Vector useFrom = from;

	while (true)
	{
		UTIL_TraceLine(useFrom, to, ignore_monsters, ignore, &result);

		if (result.flFraction != 1.0f && IsEntityWalkable( VARS( result.pHit ), flags ))
		{
			ignore = result.pHit;

			Vector dir = to - from;
			dir.NormalizeInPlace();
			useFrom = result.vecEndPos + 5.0f * dir;
		}
		else
			break;
	}

	if (result.flFraction == 1.0f)
		return true;

	return false;
}

#endif // NAV_H
