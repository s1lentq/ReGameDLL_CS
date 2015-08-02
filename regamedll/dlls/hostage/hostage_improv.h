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

#include "hostage/hostage_states.h"

class CHostage;
enum HostageChatterType;

class CHostageImprov: public CImprov
{
public:
	CHostageImprov(CBaseEntity *entity);
	virtual ~CHostageImprov(void)
	{
		//~HostageAnimateState();		//    49
		//~HostageFollowState();		//    49
		//~HostageRetreatState();		//    49
		//~HostageEscapeState();		//    49
		//~HostageIdleState();		//    49
		//~CImprov();			//    49
	};

	virtual void OnMoveToSuccess(const Vector &goal)
	{
		//if (m_behavior.IsState(NULL))
		//	IImprovEvent::OnMoveToSuccess(goal);
	}
	virtual void OnMoveToFailure(const Vector &goal, MoveToFailureType reason);
	virtual void OnInjury(float amount)
	{
		//m_behavior.Update();
		//m_lastInjuryTimer.Start();
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
		UNTESTED
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
	//{
	//	UNTESTED
	//	return m_behavior.IsState(&m_followState);
	//}
	void FaceOutwards(void);
	bool IsFriendInTheWay(void);
	void SetKnownGoodPosition(const Vector &pos);
	const Vector &GetKnownGoodPosition(void);
	void ResetToKnownGoodPosition(void);
	void ResetJump(void);
	void ApplyForce(Vector force);
	const Vector GetActualVelocity(void);
	void SetMoveLimit(MoveType limit)
	{
		m_moveLimit = limit;
	};
	MoveType GetMoveLimit(void)
	{
		return m_moveLimit;
	}
	CNavPath *GetPath(void);
	CNavPathFollower *GetPathFollower(void);
	void Idle(void);
	bool IsIdle(void)
	{
		UNTESTED
		return m_behavior.IsState(&m_idleState);
	}
	void Follow(CBasePlayer *leader);
	bool IsFollowing(const CBaseEntity *leader = NULL)
	{
		UNTESTED
		return m_behavior.IsState(&m_followState);
	}
	void Escape(void);
	bool IsEscaping(void);
	void Retreat(void);
	bool IsRetreating(void);
	bool IsAtHome(void);
	bool CanSeeRescueZone(void);
	CBaseEntity *GetFollowLeader(void);
	CBasePlayer *GetClosestVisiblePlayer(int team);
	float GetTimeSinceLastSawPlayer(int team);
	float GetTimeSinceLastInjury(void);
	float GetTimeSinceLastNoise(void);
	bool IsTerroristNearby(void);
	void Frighten(ScareType scare);
	bool IsScared(void);
	ScareType GetScareIntensity(void);
	bool IsIgnoringTerrorists(void);
	float GetAggression(void);
	void Chatter(HostageChatterType sayType, bool mustSpeak);
	void DelayedChatter(float delayTime, HostageChatterType sayType, bool mustSpeak);
	void UpdateDelayedChatter(void);
	bool IsTalking(void);
	void UpdateGrenadeReactions(void);
	void Afraid(void);
	void Wave(void);
	void Agree(void);
	void Disagree(void);
	void CrouchDie(void);
	void Flinch(Activity activity);
	void UpdateIdleActivity(Activity activity, Activity fidget);
	void UpdateStationaryAnimation(void);
	CHostage *GetEntity(void);
	void CheckForNearbyTerrorists(void);
	void UpdatePosition(float);
	void MoveTowards(const Vector &pos, float deltaT);
	bool FaceTowards(const Vector &target, float deltaT);
	float GetSpeed(void);
	void SetMoveAngle(float angle);
	void Wiggle(void);
	void ClearPath(void);
	bool DiscontinuityJump(float ground, bool onlyJumpDown, bool mustJump);
	void UpdateVision(void);
public:
	CountdownTimer m_coughTimer;
	CountdownTimer m_grenadeTimer;
private:
	CHostage *m_hostage;
	CNavArea *m_lastKnownArea;
	Vector m_centroid;
	Vector m_eye;
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
	CountdownTimer m_avoidFriendTimer;
	bool m_isFriendInTheWay;
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
	const CHostageImprov *m_me;
	Vector m_goalPos;
	CHostage *m_blocker;

	/* <46fa9c> ../cstrike/dlls/hostage/hostage_improv.cpp:370 */
	NOBODY inline bool operator()(CHostage *them)
	{
		//
	}

}; /* size: 20, cachelines: 1, members: 3 */

/* <4700b6> ../cstrike/dlls/hostage/hostage_improv.cpp:931 */
class KeepPersonalSpace
{
public:
	/* <46f9d7> ../cstrike/dlls/hostage/hostage_improv.cpp:939 */
	bool operator()(CBaseEntity *entity)
	{
	//	{
	//		float const space;                                     //   953
	//		Vector to;                                      //   955
	//		float range;                                          //   956
	//		{
	//			class CBasePlayer *player;                   //   948
	//		}
	//		{
	//			class CBasePlayer *player;                   //   961
	//			float const cosTolerance;                      //   962
	//			float const spring;                            //   967
	//			float ds;                                     //   969
	//			float const minSpace;                          //   971
	//			float const force;                             //   975
	//			float const damper;                            //   979
	//		}
	//	}
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
	/* <47046f> ../cstrike/dlls/hostage/hostage_improv.cpp:525 */
	bool operator()(CBaseEntity *entity)
	{
//		Vector to;                                      //   530
//		float range;                                          //   531
//		float const closeRange;                                //   533
//		float const aheadTolerance;                            //   537
	}
	/* <46f597> ../cstrike/dlls/hostage/hostage_improv.cpp:546 */
	bool IsBlocked(void)
	{
		return m_isBlocked;
	}
private:
	const CHostageImprov *m_me;
	Vector m_dir;
	bool m_isBlocked;

};/* size: 20, cachelines: 1, members: 3 */

NOBODY inline void DrawAxes(Vector &origin, int red, int green, int blue);

#ifdef HOOK_GAMEDLL

typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY_VECTOR)(const Vector &) const;
typedef bool (CHostageImprov::*IS_FRIEND_IN_THE_WAY_CBASE)(CBaseEntity *, const Vector &) const;

#endif // HOOK_GAMEDLL

#endif // HOSTAGE_IMPROV_H
