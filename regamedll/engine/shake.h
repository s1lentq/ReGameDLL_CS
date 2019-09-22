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

#ifndef SHAKE_H
#define SHAKE_H
#ifdef _WIN32
#pragma once
#endif

// This structure is sent over the net to describe a screen shake event
typedef struct
{
	unsigned short amplitude;		// FIXED 4.12 amount of shake
	unsigned short duration;		// FIXED 4.12 seconds duration
	unsigned short frequency;		// FIXED 8.8 noise frequency (low frequency is a jerk,high frequency is a rumble)

} ScreenShake;

#define FFADE_IN		0x0000		// Just here so we don't pass 0 into the function
#define FFADE_OUT		0x0001		// Fade out (not in)
#define FFADE_MODULATE		0x0002		// Modulate (don't blend)
#define FFADE_STAYOUT		0x0004		// ignores the duration, stays faded out until new ScreenFade message received

// This structure is sent over the net to describe a screen fade event
typedef struct
{
	unsigned short duration;		// FIXED 4.12 seconds duration
	unsigned short holdTime;		// FIXED 4.12 seconds duration until reset (fade & hold)
	short fadeFlags;			// flags
	byte r,g,b,a;				// fade to color ( max alpha )

} ScreenFade;

#endif // SHAKE_H
