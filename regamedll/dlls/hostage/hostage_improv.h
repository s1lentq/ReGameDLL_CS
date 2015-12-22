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

#ifndef HOSTAGE_IMPROV_H
#define HOSTAGE_IMPROV_H
#ifdef _WIN32
#pragma once
#endif

#include "hostage/hostage.h"
#include "hostage/hostage_states.h"

class CHostage;
enum HostageChatterType;

class CHostageImprov: public CImprov
{
public:
	CHostageImprov(CBaseEntity *entity);
	~CHostageImprov(void) {};

	virtual void OnMoveToSuccess(const Vector &goal)
	{
		m_behavior.OnMoveToSuccess(goal);
	}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason);
	virtual void OnInjury(float amount)
	{
		m_behavior.OnInjury(amount);

		m_lastInjuryTimer.Start();
		Frighten(TERRIFIED);
	}
	virtual bool IsAlive(void) const;
	virtual void MoveTo(const Vector &goal);
	virtual void LookAt(const Vector &target);
	virtual void ClearLookAt(void);
	virtual void FaceTo(const Vector &goal);
	virtual void ClearFaceTo(void);
	virtual bool IsAtMoveGoal(float error = 20.0f) const;
	virtual bool HasLookAt(void) const
	{
		return m_isLookingAt;
	}
	virtual bool HasFaceTo(void) const
	{
		return m_isFacingTo;
	}
	virtual bool IsAtFaceGoal(void) const;
	virtual bool IsFriendInTheWay(const Vector &goalPos) const;
	virtual bool IsFriendInTheWay(CBaseEntity *myFriend, const Vector &goalPos) const;
	virtual void MoveForward(void)
	{
		m_moveFlags |= IN_FORWARD;
	}
	virtual void MoveBackward(void)
	{
		m_moveFlags |= IN_BACK;
	}
	virtual void StrafeLeft(void)
	{
		m_moveFlags |= IN_MOVELEFT;
	}
	virtual void StrafeRight(void)
	{
		m_moveFlags |= IN_MOVERIGHT;
	}

	#define HOSTAGE_MUST_JUMP true
	virtual bool Jump(void);

	virtual void Crouch(void);
	virtual void StandUp(void);
	virtual void TrackPath(const Vector &pathGoal, float deltaT);
	virtual void StartLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos);
	virtual bool TraverseLadder(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT);
	virtual bool GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal = NULL);
	virtual void Run(void);
	virtual void Walk(void);
	virtual void Stop(void);
	virtual float GetMoveAngle(void) const
	{
		return m_moveAngle;
	}
	virtual float GetFaceAngle(void) const
	{
		return m_moveAngle;
	}
	virtual const Vector &GetFeet(void) const;
	virtual const Vector &GetCentroid(void) const;
	virtual const Vector &GetEyes(void) const;
	virtual bool IsRunning(void) const
	{
		return (m_moveType == Running);
	}
	virtual bool IsWalking(void) const
	{
		return (m_moveType == Walking);
	}
	virtual bool IsStopped(void) const
	{
		return (m_moveType == Stopped);
	}
	virtual bool IsCrouching(void) const
	{
		return m_isCrouching;
	}
	virtual bool IsJumping(void) const
	{
		return (m_jumpTimer.IsElapsed() == false);
	}
	virtual bool IsUsingLadder(void) const
	{
		return false;
	}
	virtual bool IsOnGround(void) const;
	virtual bool IsMoving(void) const;
	virtual bool CanRun(void) const
	{
		return true;
	}
	virtual bool CanCrouch(void) const
	{
		return true;
	}
	virtual bool CanJump(void) const
	{
		return true;
	}
	virtual bool IsVisible(const Vector &pos, bool testFOV = false) const;
	virtual bool IsPlayerLookingAtMe(CBasePlayer *other, float cosTolerance = 0.95f) const;
	virtual CBasePlayer *IsAnyPlayerLookingAtMe(int team = 0, float cosTolerance = 0.95f) const;
	virtual CBasePlayer *GetClosestPlayerByTravelDistance(int team = 0, float *range = NULL) const;
	virtual CNavArea *GetLastKnownArea(void) const
	{
		return m_lastKnownArea;
	}
	virtual void OnUpdate(float deltaT);
	virtual void OnUpkeep(float deltaT);
	virtual void OnReset(void);
	virtual void OnGameEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL);
	virtual void OnTouch(CBaseEntity *other);

#ifdef HOOK_GAMEDLL

	void OnMoveToSuccess_(const Vector &goal)
	{
		//if (m_behavior.IsState(NULL))
		//	IImprovEvent::OnMoveToSuccess(goal);
	}
	void OnMoveToFailure_(const Vector &goal, MoveToFailureType reason);
	void OnInjury_(float amount)
	{
		//m_behavior.Update();
		//m_lastInjuryTimer.Start();
	}
	bool IsAlive_(void) const;
	void MoveTo_(const Vector &goal);
	void LookAt_(const Vector &target);
	void ClearLookAt_(void);
	void FaceTo_(const Vector &goal);
	void ClearFaceTo_(void);
	bool IsAtMoveGoal_(float error = 20.0f) const;
	bool IsAtFaceGoal_(void) const;
	bool IsFriendInTheWay_(const Vector &goalPos) const;
	bool IsFriendInTheWay_(CBaseEntity *myFriend, const Vector &goalPos) const;
	bool Jump_(void);
	void Crouch_(void);
	void StandUp_(void);
	void TrackPath_(const Vector &pathGoal, float deltaT);
	void StartLadder_(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos);
	bool TraverseLadder_(const CNavLadder *ladder, NavTraverseType how, const Vector *approachPos, const Vector *departPos, float deltaT);
	bool GetSimpleGroundHeightWithFloor_(const Vector *pos, float *height, Vector *normal = NULL);
	void Run_(void);
	void Walk_(void);
	void Stop_(void);
	const Vector &GetFeet_(void) const;
	const Vector &GetCentroid_(void) const;
	const Vector &GetEyes_(void) const;
	bool IsOnGround_(void) const;
	bool IsMoving_(void) const;
	bool IsVisible_(const Vector &pos, bool testFOV = false) const;
	bool IsPlayerLookingAtMe_(CBasePlayer *other, float cosTolerance = 0.95f) const;
	CBasePlayer *IsAnyPlayerLookingAtMe_(int team = 0, float cosTolerance = 0.95f) const;
	CBasePlayer *GetClosestPlayerByTravelDistance_(int team = 0, float *range = NULL) const;
	void OnUpdate_(float deltaT);
	void OnUpkeep_(float deltaT);
	void OnReset_(void);
	void OnGameEvent_(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL);
	void OnTouch_(CBaseEntity *other);

#endif // HOOK_GAMEDLL

public:
	enum MoveType
	{
		Stopped = 0,
		Walking,
		Running,
	};

	enum ScareType
	{
		NERVOUS = 0,
		SCARED,
		TERRIFIED,
	};

	void FaceOutwards(void);
	bool IsFriendInTheWay(void) const;
	void SetKnownGoodPosition(const Vector &pos);
	const Vector &GetKnownGoodPosition(void) const
	{
		return m_knownGoodPos;
	}
	void ResetToKnownGoodPosition(void);
	void ResetJump(void)
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
	void ApplyForce(Vector force);
#ifdef PLAY_GAMEDLL
	void ApplyForce2(float_precision x, float_precision y)
	{
		m_vel.x += x;
		m_vel.y += y;
	}
#endif // PLAY_GAMEDLL
	const Vector GetActualVelocity(void) const
	{
		return m_actualVel;
	}
	void SetMoveLimit(MoveType limit)
	{
		m_moveLimit = limit;
	}
	MoveType GetMoveLimit(void) const
	{
		return m_moveLimit;
	}
	CNavPath *GetPath(void)
	{
		return &m_path;
	}
	CNavPathFollower *GetPathFollower(void);
	void Idle(void)
	{
		m_behavior.SetState(&m_idleState);
	}
	bool IsIdle(void) const
	{
		return m_behavior.IsState(&m_idleState);
	}
	void Follow(CBasePlayer *leader)
	{
		m_followState.SetLeader(leader);
		m_behavior.SetState(&m_followState);
	}
	bool IsFollowing(const CBaseEntity *leader = NULL) const
	{
		return m_behavior.IsState(&m_followState);
	}
	void Escape(void)
	{
		m_behavior.SetState(&m_escapeState);
	}
	bool IsEscaping(void) const
	{
		return m_behavior.IsState(&m_escapeState);
	}
	void Retreat(void)
	{
		m_behavior.SetState(&m_retreatState);
	}
	bool IsRetreating(void) const
	{
		return m_behavior.IsState(&m_retreatState);
	}
	bool IsAtHome(void) const;
	bool CanSeeRescueZone(void) const;
	CBaseEntity *GetFollowLeader(void) const
	{
		return m_followState.GetLeader();
	}
	CBasePlayer *GetClosestVisiblePlayer(int team);
	float GetTimeSinceLastSawPlayer(int team);
	float GetTimeSinceLastInjury(void);
	float GetTimeSinceLastNoise(void);
	bool IsTerroristNearby(void);
	void Frighten(ScareType scare);
	bool IsScared(void) const;
	ScareType GetScareIntensity(void) const
	{
		return m_scareIntensity;
	}
	bool IsIgnoringTerrorists(void) const
	{
		m_ignoreTerroristTimer.IsElapsed();
	}
	float GetAggression(void) const
	{
		return m_aggression;
	}
	void Chatter(HostageChatterType sayType, bool mustSpeak = true);
	void DelayedChatter(float delayTime, HostageChatterType sayType, bool mustSpeak = false);
	NOXREF void UpdateDelayedChatter(void);
	bool IsTalking(void) const
	{
		return m_talkingTimer.IsElapsed();
	}
	void UpdateGrenadeReactions(void);
	void Afraid(void);
	void Wave(void);
	void Agree(void);
	void Disagree(void);
	void CrouchDie(void);
	void Flinch(Activity activity);
	void UpdateIdleActivity(Activity activity, Activity fidget);
	void UpdateStationaryAnimation(void);
	CHostage *GetEntity(void) const
	{
		return m_hostage;
	}
	void CheckForNearbyTerrorists(void);
	void UpdatePosition(float);
	void MoveTowards(const Vector &pos, float deltaT);
	bool FaceTowards(const Vector &target, float deltaT);
	float GetSpeed(void);
	void SetMoveAngle(float angle)
	{
		m_moveAngle = angle;
	}
	void Wiggle(void);
	void ClearPath(void);

	#define HOSTAGE_ONLY_JUMP_DOWN true
	bool DiscontinuityJump(float ground, bool onlyJumpDown = false, bool mustJump = false);
	void UpdateVision(void);

public:
	CountdownTimer m_coughTimer;
	CountdownTimer m_grenadeTimer;

private:
	CHostage *m_hostage;
	CNavArea *m_lastKnownArea;
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
	CNavPath m_path;
	CNavPathFollower m_follower;
	Vector m_lastPosition;
	MoveType m_moveType;
	MoveType m_moveLimit;
	bool m_isCrouching;
	CountdownTimer m_minCrouchTimer;
	float m_moveAngle;
	NavRelativeDirType m_wiggleDirection;
	CountdownTimer m_wiggleTimer;
	CountdownTimer m_wiggleJumpTimer;
	CountdownTimer m_inhibitObstacleAvoidance;
	CountdownTimer m_jumpTimer;
	bool m_hasJumped;
	bool m_hasJumpedIntoAir;
	Vector m_jumpTarget;
	CountdownTimer m_clearPathTimer;
	bool m_traversingLadder;
	EHANDLE m_visiblePlayer[32];
	int m_visiblePlayerCount;
	CountdownTimer m_visionTimer;

};/* size: 7308, cachelines: 115, members: 70 */

/* <46fac7> ../cstrike/dlls/hostage/hostage_improv.cpp:363 */
class CheckWayFunctor
{
public:
	CheckWayFunctor(const CHostageImprov *me, const Vector &goalPos)
	{
		m_me = me;
		m_goalPos = goalPos;
		m_blocker = NULL;
	}
	/* <46fa9c> ../cstrike/dlls/hostage/hostage_improv.cpp:370 */
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

}; /* size: 20, cachelines: 1, members: 3 */

/* <46f426> ../cstrike/dlls/hostage/hostage_improv.h:400 */
class HostagePathCost
{
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

			dist = (*area->GetCenter() - *fromArea->GetCenter()).Length();
			float cost = fromArea->GetCostSoFar() + dist;

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

/* <4700b6> ../cstrike/dlls/hostage/hostage_improv.cpp:931 */
class KeepPersonalSpace
{
public:
	/* <4700b6> ../cstrike/dlls/hostage/hostage_improv.cpp:931 */
	KeepPersonalSpace(CHostageImprov *improv)
	{
		m_improv = improv;
		m_velDir = improv->GetActualVelocity();
		m_speed = m_velDir.NormalizeInPlace();
	}
	/* <46f9d7> ../cstrike/dlls/hostage/hostage_improv.cpp:939 */
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

#ifdef PLAY_GAMEDLL
		// TODO: fix test demo
		range = to.NormalizeInPlace<float>();
#else
		range = to.NormalizeInPlace();
#endif // PLAY_GAMEDLL
		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		const float spring = 50.0f;
		const float damper = 1.0f;

		if (range >= spring)
			return true;

		const float cosTolerance = 0.8f;
		if (entity->IsPlayer() && player->m_iTeam == CT && !m_improv->IsFollowing() && m_improv->IsPlayerLookingAtMe(player, cosTolerance))
			return true;

		const float minSpace = (spring - range);
		float_precision ds = -minSpace;

#ifndef PLAY_GAMEDLL
		m_improv->ApplyForce(to * ds);
#else
		// TODO: fix test demo
		m_improv->ApplyForce2(to.x * ds, to.y * ds);
#endif // PLAY_GAMEDLL

		const float force = 0.1f;
		m_improv->ApplyForce(m_speed * -force * m_velDir);

		return true;
	}

private:
	CHostageImprov *m_improv;
	Vector m_velDir;
	float m_speed;

}; /* size: 20, cachelines: 1, members: 3 */

/* <46fbb8> ../cstrike/dlls/hostage/hostage_improv.cpp:518 */
class CheckAhead
{
public:
	/* <46fbb8> ../cstrike/dlls/hostage/hostage_improv.cpp:518 */
	CheckAhead(const CHostageImprov *me)
	{
		m_me = me;

		m_isBlocked = false;

		m_dir.x = BotCOS(me->GetMoveAngle());
		m_dir.y = BotSIN(me->GetMoveAngle());
		m_dir.z = 0;
	}
	/* <47046f> ../cstrike/dlls/hostage/hostage_improv.cpp:525 */
	bool operator()(CBaseEntity *entity)
	{
		Vector to;
		float_precision range;
		const float closeRange = 60.0f;
		const float aheadTolerance = 0.95f;

		if (entity != reinterpret_cast<CBaseEntity *>(m_me->GetEntity()))
		{
			to = (entity->Center() - m_me->GetCentroid());
			range = to.NormalizeInPlace();

			if (range <= closeRange && DotProduct(to, m_dir) >= aheadTolerance)
				m_isBlocked = true;
		}

		return true;
	}
	/* <46f597> ../cstrike/dlls/hostage/hostage_improv.cpp:546 */
	bool IsBlocked(void) const
	{
		return m_isBlocked;
	}

private:
	const CHostageImprov *m_me;
	Vector m_dir;
	bool m_isBlocked;

};/* size: 20, cachelines: 1, members: 3 */

#ifdef HOOK_GAMEDLL

bool NavAreaBuildPath__HostagePathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, class HostagePathCost &costFunc, CNavArea **closestArea = NULL);
bool NavAreaBuildPath__ShortestPathCost__wrapper(CNavArea *startArea, CNavArea *goalArea, const Vector *goalPos, class ShortestPathCost &costFunc, CNavArea **closestArea = NULL);

typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY_VECTOR)(const Vector &) const;
typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY_CBASE)(CBaseEntity *, const Vector &) const;
typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY)(void) const;

#endif // HOOK_GAMEDLL

#endif // HOSTAGE_IMPROV_H
