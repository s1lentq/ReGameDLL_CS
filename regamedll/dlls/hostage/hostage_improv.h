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
class CHostageImprov: public CImprov
{
public:
	CHostageImprov(CBaseEntity *pEntity = nullptr);
	~CHostageImprov() {};

	// invoked when an improv reaches its MoveTo goal
	virtual void OnMoveToSuccess(const Vector &goal) { m_behavior.OnMoveToSuccess(goal); }

	// invoked when an improv fails to reach a MoveTo goal
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason);
	virtual void OnInjury(float amount)
	{
		m_behavior.OnInjury(amount);
		m_lastInjuryTimer.Start();
		Frighten(TERRIFIED);
	}
	virtual bool IsAlive() const;
	virtual void MoveTo(const Vector &goal);
	virtual void LookAt(const Vector &target);
	virtual void ClearLookAt();
	virtual void FaceTo(const Vector &goal);
	virtual void ClearFaceTo();
	virtual bool IsAtMoveGoal(float error = 20.0f) const;
	virtual bool HasLookAt() const { return m_isLookingAt; }
	virtual bool HasFaceTo() const { return m_isFacingTo; }
	virtual bool IsAtFaceGoal() const;
	virtual bool IsFriendInTheWay(const Vector &goalPos) const;
	virtual bool IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const;
	virtual void MoveForward() { m_moveFlags |= IN_FORWARD; }
	virtual void MoveBackward() { m_moveFlags |= IN_BACK; }
	virtual void StrafeLeft() { m_moveFlags |= IN_MOVELEFT; }
	virtual void StrafeRight() { m_moveFlags |= IN_MOVERIGHT; }

	#define HOSTAGE_MUST_JUMP true
	virtual bool Jump();

	virtual void Crouch();
	virtual void StandUp();
	virtual void TrackPath(const Vector &pathGoal, float deltaT);												// move along path by following "pathGoal"
	virtual void StartLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos);
	virtual bool TraverseLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT);
	virtual bool GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal = nullptr);
	virtual void Run();
	virtual void Walk();
	virtual void Stop();
	virtual float GetMoveAngle() const { return m_moveAngle; }
	virtual float GetFaceAngle() const { return m_moveAngle; }
	virtual const Vector &GetFeet() const;
	virtual const Vector &GetCentroid() const;
	virtual const Vector &GetEyes() const;
	virtual bool IsRunning() const { return (m_moveType == Running); }
	virtual bool IsWalking() const { return (m_moveType == Walking); }
	virtual bool IsStopped() const { return (m_moveType == Stopped); }
	virtual bool IsCrouching() const { return m_isCrouching; }
	virtual bool IsJumping() const { return (m_jumpTimer.IsElapsed() == false); }
	virtual bool IsUsingLadder() const { return false; }
	virtual bool IsOnGround() const;
	virtual bool IsMoving() const;
	virtual bool CanRun() const { return true; }
	virtual bool CanCrouch() const { return true; }
	virtual bool CanJump() const { return true; }
	virtual bool IsVisible(const Vector &pos, bool testFOV = false) const;						// return true if hostage can see position
	virtual bool IsPlayerLookingAtMe(CBasePlayer *pOther, float cosTolerance = 0.95f) const;
	virtual CBasePlayer *IsAnyPlayerLookingAtMe(int team = 0, float cosTolerance = 0.95f) const;
	virtual CBasePlayer *GetClosestPlayerByTravelDistance(int team = 0, float *range = nullptr) const;
	virtual CNavArea *GetLastKnownArea() const { return m_lastKnownArea; }
	virtual void OnUpdate(float deltaT);
	virtual void OnUpkeep(float deltaT);
	virtual void OnReset();
	virtual void OnGameEvent(GameEventType event, CBaseEntity *pEntity = nullptr, CBaseEntity *pOther = nullptr);
	virtual void OnTouch(CBaseEntity *pOther);									// in contact with "other"

#ifdef PLAY_GAMEDLL
	void ApplyForce2(real_t x, real_t y);
#endif

public:
	enum MoveType { Stopped, Walking, Running };
	enum ScareType { NERVOUS, SCARED, TERRIFIED };

	void FaceOutwards();
	bool IsFriendInTheWay() const;
	void SetKnownGoodPosition(const Vector &pos);
	const Vector &GetKnownGoodPosition() const { return m_knownGoodPos; }
	void ResetToKnownGoodPosition();
	void ResetJump();
	void ApplyForce(Vector force);					// apply a force to the hostage
	const Vector GetActualVelocity() const { return m_actualVel; }
	void SetMoveLimit(MoveType limit) { m_moveLimit = limit; }
	MoveType GetMoveLimit() const { return m_moveLimit; }
	CNavPath *GetPath() { return &m_path; }
	CNavPathFollower *GetPathFollower();

	// hostage states
	// stand idle
	void Idle() { m_behavior.SetState(&m_idleState); }
	bool IsIdle() const { return m_behavior.IsState(&m_idleState); }

	// begin following "leader"
	void Follow(CBasePlayer *leader) { m_followState.SetLeader(leader); m_behavior.SetState(&m_followState); }
	bool IsFollowing(const CBaseEntity *pLeader = nullptr) const
	{
		if (!m_behavior.IsState(&m_followState))
			return false;

		if (pLeader && pLeader != m_followState.GetLeader())
			return false;

		return true;
	}

	// Escape
	void Escape() { m_behavior.SetState(&m_escapeState); }
	bool IsEscaping() const { return m_behavior.IsState(&m_escapeState); }

	// Retreat
	void Retreat() { m_behavior.SetState(&m_retreatState); }
	bool IsRetreating() const { return m_behavior.IsState(&m_retreatState); }

	bool IsAtHome() const;
	bool CanSeeRescueZone() const;
	CBasePlayer *GetFollowLeader() const { return m_followState.GetLeader(); }
	CBasePlayer *GetClosestVisiblePlayer(int team);
	float GetTimeSinceLastSawPlayer(int team);
	float GetTimeSinceLastInjury();
	float GetTimeSinceLastNoise();
	bool IsTerroristNearby();
	void Frighten(ScareType scare);
	bool IsScared() const;
	ScareType GetScareIntensity() const { return m_scareIntensity; }
	bool IsIgnoringTerrorists() const { return m_ignoreTerroristTimer.IsElapsed(); }
	float GetAggression() const { return m_aggression; }
	void Chatter(HostageChatterType sayType, bool mustSpeak = true);
	void DelayedChatter(float delayTime, HostageChatterType sayType, bool mustSpeak = false);
	void UpdateDelayedChatter();
	bool IsTalking() const { return m_talkingTimer.IsElapsed(); }
	void UpdateGrenadeReactions();
	void Afraid();
	void Wave();
	void Agree();
	void Disagree();
	void CrouchDie();
	void Flinch(Activity activity);
	void UpdateIdleActivity(Activity activity, Activity fidget);
	void UpdateStationaryAnimation();
	CHostage *GetEntity() const { return m_hostage; }
	void CheckForNearbyTerrorists();
	void UpdatePosition(float deltaT);
	void MoveTowards(const Vector &pos, float deltaT);
	bool FaceTowards(const Vector &target, float deltaT);	// rotate body to face towards "target"
	float GetSpeed();
	void SetMoveAngle(float angle) { m_moveAngle = angle; }
	void Wiggle();											// attempt to wiggle-out of begin stuck
	void ClearPath();

	#define HOSTAGE_ONLY_JUMP_DOWN true
	bool DiscontinuityJump(float ground, bool onlyJumpDown = false, bool mustJump = false);
	void UpdateVision();

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
	CNavPath m_path;					// current path to follow
	CNavPathFollower m_follower;
	Vector m_lastPosition;
	MoveType m_moveType;
	MoveType m_moveLimit;
	bool m_isCrouching;					// true if hostage is crouching
	CountdownTimer m_minCrouchTimer;
	float m_moveAngle;
	NavRelativeDirType m_wiggleDirection;

	CountdownTimer m_wiggleTimer;		// for wiggling
	CountdownTimer m_wiggleJumpTimer;
	CountdownTimer m_inhibitObstacleAvoidance;
	CountdownTimer m_jumpTimer;			// if zero, we can jump

	bool m_hasJumped;
	bool m_hasJumpedIntoAir;
	Vector m_jumpTarget;
	CountdownTimer m_clearPathTimer;
	bool m_traversingLadder;
	EntityHandle<CBasePlayer> m_visiblePlayer[MAX_CLIENTS];
	int m_visiblePlayerCount;
	CountdownTimer m_visionTimer;
};

class CheckWayFunctor
{
public:
	CheckWayFunctor(const CHostageImprov *me, const Vector &goalPos)
	{
		m_me = me;
		m_goalPos = goalPos;
		m_blocker = nullptr;
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
class HostagePathCost
{
public:
	float operator()(CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		if (fromArea == nullptr)
		{
			// first area in path, no cost
			return 0.0f;
		}
		else
		{
			// compute distance travelled along path so far
			float dist;

			if (ladder)
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

class KeepPersonalSpace
{
public:
	KeepPersonalSpace(CHostageImprov *improv)
	{
		m_improv = improv;
		m_velDir = improv->GetActualVelocity();
		m_speed = m_velDir.NormalizeInPlace();
	}
	bool operator()(CBaseEntity *pEntity)
	{
		const float space = 1.0f;
		Vector to;
		float range;

		if (pEntity == reinterpret_cast<CBaseEntity *>(m_improv->GetEntity()))
			return true;

		if (pEntity->IsPlayer() && !pEntity->IsAlive())
			return true;

		to = pEntity->pev->origin - m_improv->GetCentroid();

#ifdef PLAY_GAMEDLL
		// TODO: fix test demo
		range = to.NormalizeInPlace<float>();
#else
		range = to.NormalizeInPlace();
#endif

		CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);

		const float spring = 50.0f;
		const float damper = 1.0f;

		if (range >= spring)
			return true;

		const float cosTolerance = 0.8f;
		if (pEntity->IsPlayer() && pPlayer->m_iTeam == CT && !m_improv->IsFollowing() && m_improv->IsPlayerLookingAtMe(pPlayer, cosTolerance))
			return true;

		const float minSpace = (spring - range);
		real_t ds = -minSpace;

#ifndef PLAY_GAMEDLL
		m_improv->ApplyForce(to * ds);
#else
		// TODO: fix test demo
		m_improv->ApplyForce2(to.x * ds, to.y * ds);
#endif

		const float force = 0.1f;
		m_improv->ApplyForce(m_speed * -force * m_velDir);

		return true;
	}

private:
	CHostageImprov *m_improv;
	Vector m_velDir;
	float m_speed;
};

class CheckAhead
{
public:
	CheckAhead(const CHostageImprov *me)
	{
		m_me = me;
		m_dir = Vector(BotCOS(me->GetMoveAngle()), BotSIN(me->GetMoveAngle()), 0.0f);
		m_isBlocked = false;
	}
	bool operator()(CBaseEntity *pEntity)
	{
		Vector to;
		real_t range;
		const float closeRange = 60.0f;
		const float aheadTolerance = 0.95f;

		if (pEntity != reinterpret_cast<CBaseEntity *>(m_me->GetEntity()))
		{
			to = (pEntity->Center() - m_me->GetCentroid());
			range = to.NormalizeInPlace();

			if (range <= closeRange && DotProduct(to, m_dir) >= aheadTolerance)
				m_isBlocked = true;
		}

		return true;
	}
	bool IsBlocked() const { return m_isBlocked; }

private:
	const CHostageImprov *m_me;
	Vector m_dir;
	bool m_isBlocked;
};

#ifdef PLAY_GAMEDLL
inline void CHostageImprov::ApplyForce2(real_t x, real_t y)
{
	m_vel.x += x;
	m_vel.y += y;
}
#endif

inline void CHostageImprov::ResetJump()
{
	if (m_hasJumpedIntoAir)
	{
		if (IsOnGround())
		{
			m_jumpTimer.Invalidate();
		}
	}
	else if (!IsOnGround())
	{
		m_hasJumpedIntoAir = true;
	}
}
