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

#ifndef CUSTOMENTITY_H
#define CUSTOMENTITY_H
#ifdef _WIN32
#pragma once
#endif

// Custom Entities
// Start/End Entity is encoded as 12 bits of entity index, and 4 bits of attachment (4:12)
#define BEAMENT_ENTITY(x)		((x) & 0xFFF)
#define BEAMENT_ATTACHMENT(x)		(((x)>>12) & 0xF)

// Beam types, encoded as a byte
enum
{
	BEAM_POINTS = 0,
	BEAM_ENTPOINT,
	BEAM_ENTS,
	BEAM_HOSE,
};

#define BEAM_FSINE		0x10
#define BEAM_FSOLID		0x20
#define BEAM_FSHADEIN		0x40
#define BEAM_FSHADEOUT		0x80

#endif // CUSTOMENTITY_H
