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

#ifndef HLTV_H
#define HLTV_H
#ifdef _WIN32
#pragma once
#endif

#define TYPE_CLIENT			0	// client is a normal HL client (default)
#define TYPE_PROXY			1	// client is another proxy
#define TYPE_COMMENTATOR		3	// client is a commentator
#define TYPE_DEMO			4	// client is a demo file

// sub commands of svc_hltv:
#define HLTV_ACTIVE			0	// tells client that he's an spectator and will get director commands
#define HLTV_STATUS			1	// send status infos about proxy
#define HLTV_LISTEN			2	// tell client to listen to a multicast stream

// director command types:
#define DRC_CMD_NONE			0	// NULL director command
#define DRC_CMD_START			1	// start director mode
#define DRC_CMD_EVENT			2	// informs about director command
#define DRC_CMD_MODE			3	// switches camera modes
#define DRC_CMD_CAMERA			4	// set fixed camera
#define DRC_CMD_TIMESCALE		5	// sets time scale
#define DRC_CMD_MESSAGE			6	// send HUD centerprint
#define DRC_CMD_SOUND			7	// plays a particular sound
#define DRC_CMD_STATUS			8	// HLTV broadcast status
#define DRC_CMD_BANNER			9	// set GUI banner
#define DRC_CMD_STUFFTEXT		10	// like the normal svc_stufftext but as director command
#define DRC_CMD_CHASE			11	// chase a certain player
#define DRC_CMD_INEYE			12	// view player through own eyes
#define DRC_CMD_MAP			13	// show overview map
#define DRC_CMD_CAMPATH			14	// define camera waypoint
#define DRC_CMD_WAYPOINTS		15	// start moving camera, inetranl message

#define DRC_CMD_LAST			15

// DRC_CMD_EVENT event flags
#define DRC_FLAG_PRIO_MASK		0x0F	// priorities between 0 and 15 (15 most important)
#define DRC_FLAG_SIDE			(1<<4)	//
#define DRC_FLAG_DRAMATIC		(1<<5)	// is a dramatic scene
#define DRC_FLAG_SLOWMOTION		(1<<6)	// would look good in SloMo
#define DRC_FLAG_FACEPLAYER		(1<<7)	// player is doning something (reload/defuse bomb etc)
#define DRC_FLAG_INTRO			(1<<8)	// is a introduction scene
#define DRC_FLAG_FINAL			(1<<9)	// is a final scene
#define DRC_FLAG_NO_RANDOM		(1<<10)	// don't randomize event data

// DRC_CMD_WAYPOINT flags
#define DRC_FLAG_STARTPATH		1	// end with speed 0.0
#define DRC_FLAG_SLOWSTART		2	// start with speed 0.0
#define DRC_FLAG_SLOWEND		4	// end with speed 0.0

#endif // HLTV_H
