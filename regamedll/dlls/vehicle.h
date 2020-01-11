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

#define VEHICLE_SPEED0_ACCELERATION  0.005000000000000000
#define VEHICLE_SPEED1_ACCELERATION  0.002142857142857143
#define VEHICLE_SPEED2_ACCELERATION  0.003333333333333334
#define VEHICLE_SPEED3_ACCELERATION  0.004166666666666667
#define VEHICLE_SPEED4_ACCELERATION  0.004000000000000000
#define VEHICLE_SPEED5_ACCELERATION  0.003800000000000000
#define VEHICLE_SPEED6_ACCELERATION  0.004500000000000000
#define VEHICLE_SPEED7_ACCELERATION  0.004250000000000000
#define VEHICLE_SPEED8_ACCELERATION  0.002666666666666667
#define VEHICLE_SPEED9_ACCELERATION  0.002285714285714286
#define VEHICLE_SPEED10_ACCELERATION 0.001875000000000000
#define VEHICLE_SPEED11_ACCELERATION 0.001444444444444444
#define VEHICLE_SPEED12_ACCELERATION 0.001200000000000000
#define VEHICLE_SPEED13_ACCELERATION 0.000916666666666666

#define VEHICLE_STARTPITCH 60
#define VEHICLE_MAXPITCH   200
#define VEHICLE_MAXSPEED   1500

class CFuncVehicleControls: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual int ObjectCaps() { return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION; }

public:
	void EXPORT Find();
};
