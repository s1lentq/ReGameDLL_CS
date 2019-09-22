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

#ifndef IN_BUTTONS_H
#define IN_BUTTONS_H
#ifdef _WIN32
#pragma once
#endif

#define IN_ATTACK	(1<<0)
#define IN_JUMP		(1<<1)
#define IN_DUCK		(1<<2)
#define IN_FORWARD	(1<<3)
#define IN_BACK		(1<<4)
#define IN_USE		(1<<5)
#define IN_CANCEL	(1<<6)
#define IN_LEFT		(1<<7)
#define IN_RIGHT	(1<<8)
#define IN_MOVELEFT	(1<<9)
#define IN_MOVERIGHT	(1<<10)
#define IN_ATTACK2	(1<<11)
#define IN_RUN		(1<<12)
#define IN_RELOAD	(1<<13)
#define IN_ALT1		(1<<14)
#define IN_SCORE	(1<<15)	// Used by client.dll for when scoreboard is held down

#define IN_ACTIVE	(IN_ATTACK | IN_ATTACK2 | IN_JUMP | IN_DUCK | IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT)

#endif // IN_BUTTONS_H
