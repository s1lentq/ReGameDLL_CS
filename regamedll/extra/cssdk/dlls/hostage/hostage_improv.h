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

#include "hostage/hostage.h"
#include "hostage/hostage_states.h"

class CHostage;
enum HostageChatterType;

// A Counter-Strike Hostage improved
class CHostageImprov: public CImprov {
public:
	// invoked when an improv reaches its MoveTo goal
	virtual void OnMoveToSuccess(const Vector &goal) = 0;

	// invoked when an improv fails to reach a MoveTo goal
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason) = 0;
	virtual void OnInjury(float amount) = 0;
	virtual bool IsAlive() const = 0;
	virtual void MoveTo(const Vector &goal) = 0;
	virtual void LookAt(const Vector &target) = 0;
	virtual void ClearLookAt() = 0;
	virtual void FaceTo(const Vector &goal) = 0;
	virtual void ClearFaceTo() = 0;
	virtual bool IsAtMoveGoal(float error = 20.0f) const = 0;
	virtual bool HasLookAt() const = 0;
	virtual bool HasFaceTo() const = 0;
	virtual bool IsAtFaceGoal() const = 0;
	virtual bool IsFriendInTheWay(const Vector &goalPos) const = 0;
	virtual bool IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const = 0;
	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void StrafeLeft() = 0;
	virtual void StrafeRight() = 0;

	#define HOSTAGE_MUST_JUMP true
	virtual bool Jump() = 0;

	virtual void Crouch() = 0;
	virtual void StandUp() = 0;
	virtual void TrackPath(const Vector &pathGoal, float deltaT) = 0;												// move along path by following "pathGoal"
	virtual void StartLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos) = 0;
	virtual bool TraverseLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT) = 0;
	virtual bool GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal = NULL) = 0;
	virtual void Run() = 0;
	virtual void Walk() = 0;
	virtual void Stop() = 0;
	virtual float GetMoveAngle() const = 0;
	virtual float GetFaceAngle() const = 0;
	virtual const Vector &GetFeet() const = 0;
	virtual const Vector &GetCentroid() const = 0;
	virtual const Vector &GetEyes() const = 0;
	virtual bool IsRunning() const = 0;
	virtual bool IsWalking() const = 0;
	virtual bool IsStopped() const = 0;
	virtual bool IsCrouching() const = 0;
	virtual bool IsJumping() const = 0;
	virtual bool IsUsingLadder() const = 0;
	virtual bool IsOnGround() const = 0;
	virtual bool IsMoving() const = 0;
	virtual bool CanRun() const = 0;
	virtual bool CanCrouch() const = 0;
	virtual bool CanJump() const = 0;
	virtual bool IsVisible(const Vector &pos, bool testFOV = false) const = 0;						// return true if hostage can see position
	virtual bool IsPlayerLookingAtMe(CBasePlayer *other, float cosTolerance = 0.95f) const = 0;
	virtual CBasePlayer *IsAnyPlayerLookingAtMe(int team = 0, float cosTolerance = 0.95f) const = 0;
	virtual CBasePlayer *GetClosestPlayerByTravelDistance(int team = 0, float *range = NULL) const = 0;
	virtual CNavArea *GetLastKnownArea() const = 0;
	virtual void OnUpdate(float deltaT) = 0;
	virtual void OnUpkeep(float deltaT) = 0;
	virtual void OnReset() = 0;
	virtual void OnGameEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL) = 0;
	virtual void OnTouch(CBaseEntity *other) = 0;									// in contact with "other"
public:
	enum MoveType { Stopped, Walking, Running };
	enum ScareType { NERVOUS, SCARED, TERRIFIED };

	const Vector &GetKnownGoodPosition() const { return m_knownGoodPos; }
	void ApplyForce(Vector force) { m_vel.x += force.x; m_vel.y += force.y; }							// apply a force to the hostage
	const Vector GetActualVelocity() const { return m_actualVel; }
	void SetMoveLimit(MoveType limit) { m_moveLimit = limit; }
	MoveType GetMoveLimit() const { return m_moveLimit; }
	CNavPath *GetPath() { return &m_path; }

	// hostage states
	// stand idle
	void Idle() { m_behavior.SetState(&m_idleState); }
	bool IsIdle() const { return m_behavior.IsState(&m_idleState); }

	// begin following "leader"
	void Follow(CBasePlayer *leader) { m_followState.SetLeader(leader); m_behavior.SetState(&m_followState); }
	bool IsFollowing(const CBaseEntity *leader = NULL) const { return m_behavior.IsState(&m_followState); }

	// Escape
	void Escape() { m_behavior.SetState(&m_escapeState); }
	bool IsEscaping() const { return m_behavior.IsState(&m_escapeState); }

	// Retreat
	void Retreat() { m_behavior.SetState(&m_retreatState); }
	bool IsRetreating() const { return m_behavior.IsState(&m_retreatState); }

	CBaseEntity *GetFollowLeader() const { return m_followState.GetLeader(); }
	ScareType GetScareIntensity() const { return m_scareIntensity; }
	bool IsIgnoringTerrorists() const { return m_ignoreTerroristTimer.IsElapsed(); }
	float GetAggression() const { return m_aggression; }
	bool IsTalking() const { return m_talkingTimer.IsElapsed(); }
	CHostage *GetEntity() const { return m_hostage; }
	void SetMoveAngle(float angle) { m_moveAngle = angle; }
public:
	CountdownTimer m_coughTimer;
	CountdownTimer m_grenadeTimer;
private:
	CHostage *m_hostage;
	CNavArea *m_lastKnownArea;	// last area we were in
	mutable Vector m_centroid;
	mutable Vector m_eye;
	HostageStateMachine m_behavior;
	HostageIdleState m_idleState;
	HostageEscapeState m_escapeState;
	HostageRetreatState m_retreatState;
	HostageFollowState m_followState;
	HostageAnimateState m_animateState;
	bool m_didFidget;
	float m_aggression;
	IntervalTimer m_lastSawCT;
	IntervalTimer m_lastSawT;
	CountdownTimer m_checkNearbyTerroristTimer;
	bool m_isTerroristNearby;
	CountdownTimer m_nearbyTerroristTimer;
	CountdownTimer m_scaredTimer;
	ScareType m_scareIntensity;
	CountdownTimer m_ignoreTerroristTimer;
	CountdownTimer m_blinkTimer;
	char m_blinkCounter;
	IntervalTimer m_lastInjuryTimer;
	IntervalTimer m_lastNoiseTimer;
	mutable CountdownTimer m_avoidFriendTimer;
	mutable bool m_isFriendInTheWay;
	CountdownTimer m_chatterTimer;
	bool m_isDelayedChatterPending;
	CountdownTimer m_delayedChatterTimer;
	HostageChatterType m_delayedChatterType;
	bool m_delayedChatterMustSpeak;
	CountdownTimer m_talkingTimer;
	unsigned int m_moveFlags;
	Vector2D m_vel;
	Vector m_actualVel;
	Vector m_moveGoal;
	Vector m_knownGoodPos;
	bool m_hasKnownGoodPos;
	Vector m_priorKnownGoodPos;
	bool m_hasPriorKnownGoodPos;
	CountdownTimer m_priorKnownGoodPosTimer;
	IntervalTimer m_collisionTimer;
	Vector m_viewGoal;
	bool m_isLookingAt;
	Vector m_faceGoal;
	bool m_isFacingTo;
	CNavPath m_path;			// current path to follow
	CNavPathFollower m_follower;
	Vector m_lastPosition;
	MoveType m_moveType;
	MoveType m_moveLimit;
	bool m_isCrouching;			// true if hostage is crouching
	CountdownTimer m_minCrouchTimer;
	float m_moveAngle;
	NavRelativeDirType m_wiggleDirection;

	CountdownTimer m_wiggleTimer;		// for wiggling
	CountdownTimer m_wiggleJumpTimer;
	CountdownTimer m_inhibitObstacleAvoidance;
	CountdownTimer m_jumpTimer;		// if zero, we can jump

	bool m_hasJumped;
	bool m_hasJumpedIntoAir;
	Vector m_jumpTarget;
	CountdownTimer m_clearPathTimer;
	bool m_traversingLadder;
	EHANDLE m_visiblePlayer[MAX_CLIENTS];
	int m_visiblePlayerCount;
	CountdownTimer m_visionTimer;
};

class CheckWayFunctor {
public:
	CheckWayFunctor(const CHostageImprov *me, const Vector &goalPos)
	{
		m_me = me;
		m_goalPos = goalPos;
		m_blocker = NULL;
	}
	bool operator()(CHostage *them)
	{
		if (((CBaseMonster *)them)->IsAlive() && m_me->IsFriendInTheWay((CBaseEntity *)them, m_goalPos))
		{
			m_blocker = them;
			return false;
		}

		return true;
	}

	const CHostageImprov *m_me;
	Vector m_goalPos;
	CHostage *m_blocker;
};

// Functor used with NavAreaBuildPath() for building Hostage paths.
// Once we hook up crouching and ladders, this can be removed and ShortestPathCost() can be used instead.
class HostagePathCost {
public:
	float operator()(CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		if (fromArea == NULL)
		{
			// first area in path, no cost
			return 0.0f;
		}
		else
		{
			// compute distance travelled along path so far
			float dist;

			if (ladder != NULL)
			{
				const float ladderCost = 10.0f;
				return ladder->m_length * ladderCost + fromArea->GetCostSoFar();
			}
			else
			{
				dist = (*area->GetCenter() - *fromArea->GetCenter()).Length();
			}

			float cost = dist + fromArea->GetCostSoFar();

			// if this is a "crouch" area, add penalty
			if (area->GetAttributes() & NAV_CROUCH)
			{
				const float crouchPenalty = 10.0f;
				cost += crouchPenalty * dist;
			}

			// if this is a "jump" area, add penalty
			if (area->GetAttributes() & NAV_JUMP)
			{
				const float jumpPenalty = 10.0f;
				cost += jumpPenalty * dist;
			}

			return cost;
		}
	}
};

class KeepPersonalSpace {
public:
	KeepPersonalSpace(CHostageImprov *improv)
	{
		m_improv = improv;
		m_velDir = improv->GetActualVelocity();
		m_speed = m_velDir.NormalizeInPlace();
	}
	bool operator()(CBaseEntity *entity)
	{
		const float space = 1.0f;
		Vector to;
		float range;
		
		if (entity == reinterpret_cast<CBaseEntity *>(m_improv->GetEntity()))
			return true;

		if (entity->IsPlayer() && !entity->IsAlive())
			return true;

		to = entity->pev->origin - m_improv->GetCentroid();
		range = to.NormalizeInPlace();

		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		const float spring = 50.0f;
		const float damper = 1.0f;

		if (range >= spring)
			return true;

		const float cosTolerance = 0.8f;
		if (entity->IsPlayer() && player->m_iTeam == CT && !m_improv->IsFollowing() && m_improv->IsPlayerLookingAtMe(player, cosTolerance))
			return true;

		const float minSpace = (spring - range);
		float ds = -minSpace;

		m_improv->ApplyForce(to * ds);

		const float force = 0.1f;
		m_improv->ApplyForce(m_speed * -force * m_velDir);

		return true;
	}

private:
	CHostageImprov *m_improv;
	Vector m_velDir;
	float m_speed;
};
