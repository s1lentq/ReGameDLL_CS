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

class CBaseEntity;
class CNavLadder;

// Improv-specific events
class IImprovEvent {
public:
	virtual void OnMoveToSuccess(const Vector &goal) {};					// invoked when an improv reaches its MoveTo goal

	enum MoveToFailureType
	{
		FAIL_INVALID_PATH = 0,
		FAIL_STUCK,
		FAIL_FELL_OFF,
	};

	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) {}		// invoked when an improv fails to reach a MoveTo goal
	virtual void OnInjury(float amount) {}							// invoked when the improv is injured
};

// The Improv interface definition
// An "Improv" is an improvisational actor that simulates the
// behavor of a human in an unscripted, "make it up as you go" manner.
class CImprov: public IImprovEvent {
public:
	virtual ~CImprov() {}
	virtual bool IsAlive() const = 0;									// return true if this improv is alive

	virtual void MoveTo(const Vector &goal) = 0;								// move improv towards far-away goal (pathfind)
	virtual void LookAt(const Vector &target) = 0;								// define desired view target
	virtual void ClearLookAt() = 0;										// remove view goal
	virtual void FaceTo(const Vector &goal) = 0;								// orient body towards goal
	virtual void ClearFaceTo() = 0;										// remove body orientation goal

	virtual bool IsAtMoveGoal(float error = 20.0f) const = 0;						// return true if improv is standing on its movement goal
	virtual bool HasLookAt() const = 0;									// return true if improv has a look at goal
	virtual bool HasFaceTo() const = 0;									// return true if improv has a face to goal
	virtual bool IsAtFaceGoal() const = 0;									// return true if improv is facing towards its face goal
	virtual bool IsFriendInTheWay(const Vector &goalPos) const = 0;						// return true if a friend is blocking our line to the given goal position
	virtual bool IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const = 0;			// return true if the given friend is blocking our line to the given goal position

	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void StrafeLeft() = 0;
	virtual void StrafeRight() = 0;
	virtual bool Jump() = 0;
	virtual void Crouch() = 0;
	virtual void StandUp() = 0;																// "un-crouch"

	virtual void TrackPath(const Vector &pathGoal, float deltaT) = 0;											// move along path by following "pathGoal"
	virtual void StartLadder(const CNavLadder *ladder, enum NavTraverseType how, const Vector *approachPos, const Vector *departPos) = 0;			// invoked when a ladder is encountered while following a path

	virtual bool TraverseLadder(const CNavLadder *ladder, enum NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT) = 0;	// traverse given ladder
	virtual bool GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal = NULL) = 0;						// find "simple" ground height, treating current nav area as part of the floor

	virtual void Run() = 0;
	virtual void Walk() = 0;
	virtual void Stop() = 0;

	virtual float GetMoveAngle() const = 0;					// return direction of movement
	virtual float GetFaceAngle() const = 0;					// return direction of view

	virtual const Vector &GetFeet() const = 0;				// return position of "feet" - point below centroid of improv at feet level
	virtual const Vector &GetCentroid() const = 0;
	virtual const Vector &GetEyes() const = 0;

	virtual bool IsRunning() const = 0;
	virtual bool IsWalking() const = 0;
	virtual bool IsStopped() const = 0;

	virtual bool IsCrouching() const = 0;
	virtual bool IsJumping() const = 0;
	virtual bool IsUsingLadder() const = 0;
	virtual bool IsOnGround() const = 0;
	virtual bool IsMoving() const = 0;					// if true, improv is walking, crawling, running somewhere

	virtual bool CanRun() const = 0;
	virtual bool CanCrouch() const = 0;
	virtual bool CanJump() const = 0;
	virtual bool IsVisible(const Vector &pos, bool testFOV = false) const = 0;				// return true if improv can see position
	virtual bool IsPlayerLookingAtMe(CBasePlayer *other, float cosTolerance = 0.95f) const = 0;		// return true if 'other' is looking right at me
	virtual CBasePlayer *IsAnyPlayerLookingAtMe(int team = 0, float cosTolerance = 0.95f) const = 0;	// return player on given team that is looking right at me (team == 0 means any team), NULL otherwise

	virtual CBasePlayer *GetClosestPlayerByTravelDistance(int team = 0, float *range = NULL) const = 0;	// return actual travel distance to closest player on given team (team == 0 means any team)
	virtual CNavArea *GetLastKnownArea() const = 0;

	virtual void OnUpdate(float deltaT) = 0;								// a less frequent, full update 'tick'
	virtual void OnUpkeep(float deltaT) = 0;								// a frequent, lightweight update 'tick'
	virtual void OnReset() = 0;										// reset improv to initial state
	virtual void OnGameEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other) = 0;		// invoked when an event occurs in the game
	virtual void OnTouch(CBaseEntity *other) = 0;								// "other" has touched us
};
