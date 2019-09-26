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

#ifndef PMTRACE_H
#define PMTRACE_H
#ifdef _WIN32
#pragma once
#endif

typedef struct
{
	vec3_t normal;
	float dist;

} pmplane_t;

typedef struct pmtrace_s
{
	qboolean allsolid;			// if true, plane is not valid
	qboolean startsolid;			// if true, the initial point was in a solid area
	qboolean inopen, inwater;		// End point is in empty space or in water
	float fraction;				// time completed, 1.0 = didn't hit anything
	vec3_t endpos;				// final position
	pmplane_t plane;			// surface normal at impact
	int ent;				// entity at impact
	vec3_t deltavelocity;			// Change in player's velocity caused by impact.  
						// Only run on server.
	int hitgroup;

} pmtrace_t;

#endif // PMTRACE_H
