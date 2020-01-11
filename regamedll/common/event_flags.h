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

#ifndef EVENT_FLAGSH
#define EVENT_FLAGSH
#ifdef _WIN32
#pragma once
#endif

// Skip local host for event send.
#define FEV_NOTHOST		(1<<0)

// Send the event reliably.  You must specify the origin and angles and use
// PLAYBACK_EVENT_FULL for this to work correctly on the server for anything
// that depends on the event origin/angles.  I.e., the origin/angles are not
// taken from the invoking edict for reliable events.
#define FEV_RELIABLE		(1<<1)

// Don't restrict to PAS/PVS, send this event to _everybody_ on the server ( useful for stopping CHAN_STATIC
//  sounds started by client event when client is not in PVS anymore ( hwguy in TFC e.g. ).
#define FEV_GLOBAL		(1<<2)

// If this client already has one of these events in its queue, just update the event instead of sending it as a duplicate
//
#define FEV_UPDATE		(1<<3)

// Only send to entity specified as the invoker
#define FEV_HOSTONLY		(1<<4)

// Only send if the event was created on the server.
#define FEV_SERVER		(1<<5)

// Only issue event client side ( from shared code )
#define FEV_CLIENT		(1<<6)

#endif // EVENT_FLAGSH
