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

#define SCRIPT_EVENT_DEAD           1000 // character is now dead
#define SCRIPT_EVENT_NOINTERRUPT    1001 // does not allow interrupt
#define SCRIPT_EVENT_CANINTERRUPT   1002 // will allow interrupt
#define SCRIPT_EVENT_FIREEVENT      1003 // event now fires
#define SCRIPT_EVENT_SOUND          1004 // Play named wave file (on CHAN_BODY)
#define SCRIPT_EVENT_SENTENCE       1005 // Play named sentence
#define SCRIPT_EVENT_INAIR          1006 // Leave the character in air at the end of the sequence (don't find the floor)
#define SCRIPT_EVENT_ENDANIMATION   1007 // Set the animation by name after the sequence completes
#define SCRIPT_EVENT_SOUND_VOICE    1008 // Play named wave file (on CHAN_VOICE)
#define SCRIPT_EVENT_SENTENCE_RND1  1009 // Play sentence group 25% of the time
#define SCRIPT_EVENT_NOT_DEAD       1010 // Bring back to life (for life/death sequences)
