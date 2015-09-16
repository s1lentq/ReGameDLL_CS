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

#ifndef IMPROV_H
#define IMPROV_H
#ifdef _WIN32
#pragma once
#endif

class CBaseEntity;
class CNavLadder;

/* <46f4d9> ../game_shared/bot/improv.h:17 */
class IImprovEvent
{
public:
	virtual void OnMoveToSuccess(const Vector &goal) {};

	enum MoveToFailureType
	{
		FAIL_INVALID_PATH = 0,
		FAIL_STUCK,
		FAIL_FELL_OFF,
	};

	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) {};
	virtual void OnInjury(float amount) {};

};/* size: 4, cachelines: 1, members: 1 */

class CImprov: public IImprovEvent
{
public:
	virtual ~CImprov(void) {};

	virtual bool IsAlive(void) const = 0;

	virtual void MoveTo(const Vector &goal) = 0;
	virtual void LookAt(const Vector &target) = 0;
	virtual void ClearLookAt(void) = 0;
	virtual void FaceTo(const Vector &goal) = 0;
	virtual void ClearFaceTo(void) = 0;

	virtual bool IsAtMoveGoal(float error = 20.0f) const = 0;
	virtual bool HasLookAt(void) const = 0;
	virtual bool HasFaceTo(void) const = 0;
	virtual bool IsAtFaceGoal(void) const = 0;
	virtual bool IsFriendInTheWay(const Vector &goalPos) const = 0;
	virtual bool IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const = 0;

	virtual void MoveForward(void) = 0;
	virtual void MoveBackward(void) = 0;
	virtual void StrafeLeft(void) = 0;
	virtual void StrafeRight(void) = 0;
	virtual bool Jump(void) = 0;
	virtual void Crouch(void) = 0;
	virtual void StandUp(void) = 0;

	virtual void TrackPath(const Vector &pathGoal, float deltaT) = 0;
	virtual void StartLadder(const CNavLadder *ladder, enum NavTraverseType how, const Vector *approachPos, const Vector *departPos) = 0;

	virtual bool TraverseLadder(const CNavLadder *ladder, enum NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT) = 0;
	virtual bool GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal = NULL) = 0;

	virtual void Run(void) = 0;
	virtual void Walk(void) = 0;
	virtual void Stop(void) = 0;

	virtual float GetMoveAngle(void) const = 0;
	virtual float GetFaceAngle(void) const = 0;

	virtual const Vector &GetFeet(void) const = 0;
	virtual const Vector &GetCentroid(void) const = 0;
	virtual const Vector &GetEyes(void) const = 0;

	virtual bool IsRunning(void) const = 0;
	virtual bool IsWalking(void) const = 0;
	virtual bool IsStopped(void) const = 0;

	virtual bool IsCrouching(void) const = 0;
	virtual bool IsJumping(void) const = 0;
	virtual bool IsUsingLadder(void) const = 0;
	virtual bool IsOnGround(void) const = 0;
	virtual bool IsMoving(void) const = 0;

	virtual bool CanRun(void) const = 0;
	virtual bool CanCrouch(void) const = 0;
	virtual bool CanJump(void) const = 0;
	virtual bool IsVisible(const Vector &pos, bool testFOV = false) const = 0;
	virtual bool IsPlayerLookingAtMe(CBasePlayer *other, float cosTolerance = 0.95f) const = 0;

	virtual CBasePlayer *IsAnyPlayerLookingAtMe(int team = 0, float cosTolerance = 0.95f) const = 0;
	virtual CBasePlayer *GetClosestPlayerByTravelDistance(int team = 0, float *range = NULL) const = 0;
	virtual CNavArea *GetLastKnownArea(void) const = 0;

	virtual void OnUpdate(float deltaT) = 0;
	virtual void OnUpkeep(float deltaT) = 0;
	virtual void OnReset(void) = 0;
	virtual void OnGameEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other) = 0;
	virtual void OnTouch(CBaseEntity *other) = 0;

};/* size: 4, cachelines: 1, members: 1 */

#ifdef HOOK_GAMEDLL

typedef bool (CImprov::*IS_FRIEND_INT_THEWAY_VECTOR)(const Vector &goalPos) const;
typedef bool (CImprov::*IS_FRIEND_INT_THEWAY_CBASEENTITY)(CBaseEntity *myFriend, const Vector &goalPos) const;

#endif // HOOK_GAMEDLL

#endif // IMPROV_H
