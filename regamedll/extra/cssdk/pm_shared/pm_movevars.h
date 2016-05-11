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
#pragma once

typedef struct movevars_s
{
	float gravity;			// Gravity for map
	float stopspeed;		// Deceleration when not moving
	float maxspeed;			// Max allowed speed
	float spectatormaxspeed;
	float accelerate;		// Acceleration factor
	float airaccelerate;		// Same for when in open air
	float wateraccelerate;		// Same for when in water
	float friction;
	float edgefriction;		// Extra friction near dropofs
	float waterfriction;		// Less in water
	float entgravity;		// 1.0
	float bounce;			// Wall bounce value. 1.0
	float stepsize;			// sv_stepsize;
	float maxvelocity;		// maximum server velocity.
	float zmax;			// Max z-buffer range (for GL)
	float waveHeight;		// Water wave height (for GL)
	qboolean footsteps;		// Play footstep sounds
	char skyName[32];		// Name of the sky map
	float rollangle;
	float rollspeed;
	float skycolor_r;		// Sky color
	float skycolor_g;
	float skycolor_b;
	float skyvec_x;			// Sky vector
	float skyvec_y;
	float skyvec_z;

} movevars_t;
