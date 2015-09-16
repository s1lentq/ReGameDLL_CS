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

#ifndef CS_BOT_H
#define CS_BOT_H
#ifdef _WIN32
#pragma once
#endif

#include "bot/cs_gamestate.h"
#include "bot/cs_bot_manager.h"
#include "bot/cs_bot_chatter.h"

#define CSBOT_VERSION_MAJOR		1
#define CSBOT_VERSION_MINOR		50

#define FLAG_PROGRESS_DRAW		0x0	// draw status bar progress
#define FLAG_PROGRESS_START		0x1	// init status bar progress
#define FLAG_PROGRESS_HIDE		0x2	// hide status bar progress

#ifdef HOOK_GAMEDLL

#define _navAreaCount (*pnavAreaCount)
#define _currentIndex (*pcurrentIndex)

#endif // HOOK_GAMEDLL

extern int _navAreaCount;
extern int _currentIndex;

class CCSBot;
class BotChatterInterface;

/* <3327a8> ../cstrike/dlls/bot/cs_bot.h:44 */
class BotState
{
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName(void) const = 0;

};/* size: 4, cachelines: 1, members: 1 */

/* <3328b8> ../cstrike/dlls/bot/cs_bot.h:53 */
class IdleState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "Idle";
	}

};/* size: 4, cachelines: 1, members: 1 */

/* <3328d9> ../cstrike/dlls/bot/cs_bot.h:61 */
class HuntState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "Hunt";
	}
	void ClearHuntArea(void)
	{
		m_huntArea = NULL;
	}
private:
	CNavArea *m_huntArea;

};/* size: 8, cachelines: 1, members: 2 */

/* <3328fb> ../cstrike/dlls/bot/cs_bot.h:75 */
class AttackState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "Attack";
	}

	void SetCrouchAndHold(bool crouch)
	{
		m_crouchAndHold = crouch;
	}
	void StopAttacking(CCSBot *me);

protected:
	enum DodgeStateType
	{
		STEADY_ON,
		SLIDE_LEFT,
		SLIDE_RIGHT,
		JUMP,
		NUM_ATTACK_STATES
	} m_dodgeState;

	float m_nextDodgeStateTimestamp;
	CountdownTimer m_repathTimer;
	float m_scopeTimestamp;
	bool m_haveSeenEnemy;
	bool m_isEnemyHidden;
	float m_reacquireTimestamp;
	float m_shieldToggleTimestamp;
	bool m_shieldForceOpen;
	float m_pinnedDownTimestamp;
	bool m_crouchAndHold;
	bool m_didAmbushCheck;
	bool m_dodge;
	bool m_firstDodge;
	bool m_isCoward;
	CountdownTimer m_retreatTimer;

};/* size: 60, cachelines: 1, members: 17 */

/* <332922> ../cstrike/dlls/bot/cs_bot.h:120 */
class InvestigateNoiseState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "InvestigateNoise";
	}
private:
	NOBODY void AttendCurrentNoise(CCSBot *me);
	Vector m_checkNoisePosition;

};/* size: 16, cachelines: 1, members: 2 */

/* <332949> ../cstrike/dlls/bot/cs_bot.h:133 */
class BuyState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "Buy";
	}
private:
	bool m_isInitialDelay;
	int m_prefRetries;
	int m_prefIndex;
	int m_retries;
	bool m_doneBuying;
	bool m_buyDefuseKit;
	bool m_buyGrenade;
	bool m_buyShield;
	bool m_buyPistol;

};/* size: 28, cachelines: 1, members: 10 */

/* <332970> ../cstrike/dlls/bot/cs_bot.h:154 */
class MoveToState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "MoveTo";
	}
	void SetGoalPosition(const Vector &pos)
	{
		m_goalPosition = pos;
	}
	void SetRouteType(RouteType route)
	{
		m_routeType = route;
	}
private:
	Vector m_goalPosition;
	RouteType m_routeType;
	bool m_radioedPlan;
	bool m_askedForCover;

};/* size: 24, cachelines: 1, members: 5 */

/* <332997> ../cstrike/dlls/bot/cs_bot.h:171 */
class FetchBombState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "FetchBomb";
	}

};/* size: 4, cachelines: 1, members: 1 */

/* <3329be> ../cstrike/dlls/bot/cs_bot.h:179 */
class PlantBombState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "PlantBomb";

		// TODO: ??
		//return &statement.m_next[3];
	}

};/* size: 4, cachelines: 1, members: 1 */

/* <3329e5> ../cstrike/dlls/bot/cs_bot.h:188 */
class DefuseBombState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "DefuseBomb";
	}

};/* size: 4, cachelines: 1, members: 1 */

/* <332a0c> ../cstrike/dlls/bot/cs_bot.h:197 */
class HideState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "Hide";
	}
	void SetHidingSpot(const Vector &pos)
	{
		m_hidingSpot = pos;
	}
	const Vector &GetHidingSpot(void) const
	{
		return m_hidingSpot;
	}
	void SetSearchArea(CNavArea *area)
	{
		m_searchFromArea = area;
	}
	void SetSearchRange(float range)
	{
		m_range = range;
	}
	void SetDuration(float time)
	{
		m_duration = time;
	}
	void SetHoldPosition(bool hold)
	{
		m_isHoldingPosition = hold;
	}
	bool IsAtSpot(void) const
	{
		return m_isAtSpot;
	}
private:
	CNavArea *m_searchFromArea;
	float m_range;

	Vector m_hidingSpot;
	bool m_isAtSpot;
	float m_duration;
	bool m_isHoldingPosition;
	float m_holdPositionTime;
	bool m_heardEnemy;

	float m_firstHeardEnemyTime;
	int m_retry;
	Vector m_leaderAnchorPos;

};/* size: 64, cachelines: 1, members: 12 */

/* <332a33> ../cstrike/dlls/bot/cs_bot.h:234 */
class EscapeFromBombState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "EscapeFromBomb";
	}

};/* size: 4, cachelines: 1, members: 1 */

/* <332a5a> ../cstrike/dlls/bot/cs_bot.h:243 */
class FollowState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "Follow";
	}
	void SetLeader(CBaseEntity *leader)
	{
		m_leader = leader;
	}
private:
	NOBODY void ComputeLeaderMotionState(float leaderSpeed);
private:
	EHANDLE m_leader;
	Vector m_lastLeaderPos;
	bool m_isStopped;
	float m_stoppedTimestamp;

	enum LeaderMotionStateType
	{
		INVALID,
		STOPPED,
		WALKING,
		RUNNING
	} m_leaderMotionState;
	IntervalTimer m_leaderMotionStateTime;

	bool m_isSneaking;
	float m_lastSawLeaderTime;
	CountdownTimer m_repathInterval;

	IntervalTimer m_walkTime;
	bool m_isAtWalkSpeed;

	float m_waitTime;
	CountdownTimer m_idleTimer;

};/* size: 76, cachelines: 2, members: 14 */

/* <332a81> ../cstrike/dlls/bot/cs_bot.h:282 */
class UseEntityState: public BotState
{
public:
	NOBODY virtual void OnEnter(CCSBot *me);
	NOBODY virtual void OnUpdate(CCSBot *me);
	NOBODY virtual void OnExit(CCSBot *me);
	virtual const char *GetName(void) const
	{
		return "UseEntity";
	}
	void SetEntity(CBaseEntity *entity)
	{
		m_entity = entity;
	}
private:
	EHANDLE m_entity;

};/* size: 12, cachelines: 1, members: 2 */

/* <32b267> ../cstrike/dlls/bot/cs_bot.h:300 */
class CCSBot: public CBot
{
public:
	CCSBot(void)
	{
	};

public:
	NOBODY virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	NOBODY virtual void Killed(entvars_t *pevAttacker, int iGib);
	NOBODY virtual void RoundRespawn(void);
	NOBODY virtual void Blind(float duration, float holdTime, float fadeTime, int alpha = 255);
	NOBODY virtual void OnTouchingWeapon(CWeaponBox *box);
	NOBODY virtual bool Initialize(const BotProfile *profile);

	NOBODY virtual void SpawnBot(void);
	virtual void Upkeep(void);

	NOBODY virtual void Update(void);
	NOBODY virtual void Walk(void);
	NOBODY virtual bool Jump(bool mustJump = false);

	NOBODY virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL);

	// TODO: change both places?
	NOBODY virtual bool IsVisible(const Vector *pos, bool testFOV = false) const;
	NOBODY virtual bool IsVisible(CBasePlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const;

	virtual bool IsEnemyPartVisible(VisiblePartType part) const;

#ifdef HOOK_GAMEDLL

	bool Initialize_(const BotProfile *profile);
	void SpawnBot_(void);
	void Upkeep_(void);
	void Update_(void);
	void Walk_(void);
	bool Jump_(bool mustJump);
	void Blind_(float duration, float holdTime, float fadeTime, int alpha);
	int TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType);
	void Killed_(entvars_t *pevAttacker, int iGib);
	void OnTouchingWeapon_(CWeaponBox *box);
	void OnEvent_(GameEventType event, CBaseEntity *entity, CBaseEntity *other);
	bool IsVisible_(const Vector *pos, bool testFOV) const;
	bool IsVisible_(CBasePlayer *player, bool testFOV, unsigned char *visParts) const;
	bool IsEnemyPartVisible_(VisiblePartType part) const;
	void RoundRespawn_(void);

#endif // HOOK_GAMEDLL

public:
	void Disconnect(void);
	float GetCombatRange(void) const
	{
		return m_combatRange;
	}
	NOBODY bool IsRogue(void)const;
	void SetRogue(bool rogue)
	{
		m_isRogue = rogue;
	}
	NOBODY bool IsHurrying(void) const;
	void Hurry(float duration)
	{
		m_hurryTimer.Start(duration);
	}
	NOBODY bool IsSafe(void) const;
	NOBODY bool IsWellPastSafe(void) const;
	NOBODY bool IsEndOfSafeTime(void) const;

	NOBODY float GetSafeTimeRemaining(void) const;
	float GetSafeTime(void) const
	{
		return m_safeTime;
	}
	NOBODY bool IsUnhealthy(void);
	NOBODY void Idle(void);

	NOBODY void Hide(CNavArea *searchFromArea = NULL, float duration = -1.0f, float hideRange = 750.0f, bool holdPosition = false);
	NOBODY void Hide(const Vector *hidingSpot = NULL, float duration = -1.0f, bool holdPosition = false);

	NOBODY bool TryToHide(CNavArea *searchFromArea = NULL, float duration = -1.0f, float hideRange = 750.0f, bool holdPosition = false, bool useNearest = false);
	NOBODY bool TryToRetreat(void);

	bool IsHiding(void) const;
	bool IsAtHidingSpot(void) const;
	NOBODY void Hunt(void);
	NOBODY bool IsHunting(void) const;
	NOBODY void Attack(CBasePlayer *victim);
	NOBODY void FireWeaponAtEnemy(void);
	NOBODY void StopAttacking(void);
	bool IsAttacking(void) const;
	NOBODY void MoveTo(const Vector *pos, RouteType route = SAFEST_ROUTE);
	NOBODY bool IsMovingTo(void) const;
	NOBODY void PlantBomb(void);
	NOBODY void FetchBomb(void);
	NOBODY bool NoticeLooseBomb(void) const;
	NOBODY bool CanSeeLooseBomb(void) const;
	bool IsCarryingBomb(void)
	{
		//TODO: unsure
		//return (m_bomber.Get() != NULL);
		return false;
	}
	NOBODY void DefuseBomb(void);
	NOBODY bool IsDefusingBomb(void) const;
	NOBODY bool CanSeePlantedBomb(void) const;
	NOBODY void EscapeFromBomb(void);
	NOBODY bool IsEscapingFromBomb(void) const;
	NOBODY void RescueHostages(void);
	NOBODY void UseEntity(CBaseEntity *entity);
	NOBODY bool IsBuying(void) const;
	NOBODY void Panic(CBasePlayer *enemy);
	NOBODY void Follow(CBasePlayer *player);
	NOBODY void ContinueFollowing(void);
	NOBODY void StopFollowing(void);
	bool IsFollowing(void) const
	{
		return m_isFollowing;
	}
	CBasePlayer *GetFollowLeader(void)
	{
		CBaseEntity *entity = (CBaseEntity *)m_leader;
		return (CBasePlayer *)entity;
	}
	float GetFollowDuration(void) const
	{
		return (gpGlobals->time - m_followTimestamp);
	}
	bool CanAutoFollow(void) const
	{
		return (gpGlobals->time > m_allowAutoFollowTime);
	}
	NOBODY bool IsNotMoving(void);
	void AimAtEnemy(void)
	{
		m_isAimingAtEnemy = true;
	}
	void StopAiming(void)
	{
		m_isAimingAtEnemy = false;
	}
	bool IsAimingAtEnemy(void) const
	{
		return m_isAimingAtEnemy;
	}
	bool IsSurprised(void) const
	{
		return (gpGlobals->time - this->m_surpriseTimestamp >= 5.0f);
	}
	float GetSurpriseDelay(void) const
	{
		return m_surpriseDelay;
	}
	void ClearSurpriseDelay(void)
	{
		m_surpriseDelay = 0.0f;
	}
	float GetStateTimestamp(void) const
	{
		return m_stateTimestamp;
	}
	NOBODY bool IsDoingScenario(void);
	CSGameState *GetGameState(void)
	{
		return &m_gameState;
	}
	const CSGameState *GetGameState(void) const
	{
		return &m_gameState;
	}
	bool IsAtBombsite(void) const
	{
		UNTESTED
		// TODO: return true if we are in a bomb planting zone
		return GetGameState()->IsAtPlantedBombsite();
	}
	NOBODY bool GuardRandomZone(float range = 500.0f);
	NOBODY bool IsBusy(void) const;

	enum TaskType
	{
		SEEK_AND_DESTROY = 0,
		PLANT_BOMB,
		FIND_TICKING_BOMB,
		DEFUSE_BOMB,
		GUARD_TICKING_BOMB,
		GUARD_BOMB_DEFUSER,
		GUARD_LOOSE_BOMB,
		GUARD_BOMB_ZONE,
		ESCAPE_FROM_BOMB,
		HOLD_POSITION,
		FOLLOW,
		VIP_ESCAPE,
		GUARD_VIP_ESCAPE_ZONE,
		COLLECT_HOSTAGES,
		RESCUE_HOSTAGES,
		GUARD_HOSTAGES,
		GUARD_HOSTAGE_RESCUE_ZONE,
		MOVE_TO_LAST_KNOWN_ENEMY_POSITION,
		MOVE_TO_SNIPER_SPOT,
		SNIPING,
	};

	void SetTask(TaskType task, CBaseEntity *entity = NULL)
	{
		m_task = task;
		m_taskEntity = entity;
	}
	TaskType GetTask(void) const
	{
		return m_task;
	}
	CBaseEntity *GetTaskEntity(void)
	{
		return m_taskEntity;
	}

	enum DispositionType
	{
		ENGAGE_AND_INVESTIGATE,
		OPPORTUNITY_FIRE,
		SELF_DEFENSE,
		IGNORE_ENEMIES,
	};

	NOBODY void SetDisposition(DispositionType disposition);
	DispositionType GetDisposition(void) const;
	NOBODY void IgnoreEnemies(float duration);

	enum MoraleType
	{
		TERRIBLE = -3,
		BAD = -2,
		NEGATIVE = -1,
		NEUTRAL = 0,
		POSITIVE = 1,
		GOOD = 2,
		EXCELLENT = 3,
	};
	MoraleType GetMorale(void) const
	{
		return m_morale;
	}
	NOBODY void IncreaseMorale(void);
	void DecreaseMorale(void);
	bool IsNoiseHeard(void) const
	{
		if (m_noiseTimestamp <= 0.0f)
			return false;

		if (gpGlobals->time - m_noiseTimestamp >= GetProfile()->GetReactionTime())
			return true;

		return false;
	}
	NOBODY bool ShouldInvestigateNoise(float *retNoiseDist);
	NOBODY void InvestigateNoise(void);
	NOBODY const Vector *GetNoisePosition(void);
	CNavArea *GetNoiseArea(void) const
	{
		return m_noiseArea;
	}
	void ForgetNoise(void)
	{
		m_noiseTimestamp = 0;
	}
	NOBODY bool CanSeeNoisePosition(void);
	NOBODY float GetNoiseRange(void) const
	{
		return 0.0f;
	}
	NOBODY bool CanHearNearbyEnemyGunfire(float range = -1.0f);
	PriorityType GetNoisePriority(void) const
	{
		return m_noisePriority;
	}
	NOBODY void SendRadioMessage(GameEventType event);
	BotChatterInterface *GetChatter(void)
	{
		return &m_chatter;
	}
	NOBODY bool RespondToHelpRequest(CBasePlayer *them, Place place, float maxRange = -1.0f);
	NOBODY void StartVoiceFeedback(float duration);
	bool IsUsingVoice(void) const
	{
		return (m_voiceFeedbackEndTimestamp != 0.0f);	//return (m_voiceFeedbackEndTimestamp > gpGlobals->time);
	}
	void SetEnemy(CBasePlayer *enemy);
	CBasePlayer *GetEnemy(void)
	{
		return GetClassPtr((CBasePlayer *)m_enemy->pev);
	}
	int GetNearbyEnemyCount(void) const
	{
		return Q_min(GetEnemiesRemaining(), m_nearbyEnemyCount);
	}
	unsigned int GetEnemyPlace(void) const
	{
		return m_enemyPlace;
	}
	NOBODY bool CanSeeBomber(void);
	CBasePlayer *GetBomber(void) const
	{
		return GetClassPtr((CBasePlayer *)m_bomber->pev);
	}
	int GetNearbyFriendCount(void) const
	{
		return Q_min(GetFriendsRemaining(), m_nearbyFriendCount);
	}
	CBasePlayer *GetClosestVisibleFriend(void) const
	{
		return GetClassPtr((CBasePlayer *)m_closestVisibleFriend->pev);
	}
	CBasePlayer *GetClosestVisibleHumanFriend(void) const
	{
		return GetClassPtr((CBasePlayer *)m_closestVisibleHumanFriend->pev);
	}
	NOBODY bool IsOutnumbered(void);
	NOBODY int OutnumberedCount(void);
	NOBODY CBasePlayer *GetImportantEnemy(bool checkVisibility);
	NOBODY void UpdateReactionQueue(void);
	CBasePlayer *GetRecognizedEnemy(void);
	NOBODY bool IsRecognizedEnemyReloading(void);
	NOBODY bool IsRecognizedEnemyProtectedByShield(void);
	NOBODY float GetRangeToNearestRecognizedEnemy(void);
	NOBODY CBasePlayer *GetAttacker(void);
	float GetTimeSinceAttacked(void) const
	{
		return gpGlobals->time - m_attackedTimestamp;
	}
	NOBODY float GetFirstSawEnemyTimestamp(void);
	float GetLastSawEnemyTimestamp(void) const
	{
		return m_lastSawEnemyTimestamp;
	}
	float GetTimeSinceLastSawEnemy(void) const
	{
		return gpGlobals->time - m_lastSawEnemyTimestamp;
	}
	float GetTimeSinceAcquiredCurrentEnemy(void) const
	{
		return (gpGlobals->time - m_currentEnemyAcquireTimestamp);
	}
	NOBODY bool HasNotSeenEnemyForLongTime(void) const;
	const Vector &GetLastKnownEnemyPosition(void) const
	{
		return m_lastEnemyPosition;
	}
	bool IsEnemyVisible(void) const
	{
		return m_isEnemyVisible;
	}
	float GetEnemyDeathTimestamp(void) const
	{
		return m_enemyDeathTimestamp;
	}
	NOBODY bool IsFriendInLineOfFire(void);
	NOBODY bool IsAwareOfEnemyDeath(void) const;
	int GetLastVictimID(void) const
	{
		return m_lastVictimID;
	}
	bool HasPath(void) const
	{
		return m_pathLength != 0;
	}
	void DestroyPath(void)
	{
		m_pathLength = 0;
		m_pathLadder = NULL;
	}
	float GetFeetZ(void) const
	{
		const Vector crouch = VEC_DUCK_HULL_MIN_Z;
		const Vector stand = VEC_HULL_MIN_Z;

		return (IsCrouching()) ? (pev->origin + crouch).z : (pev->origin + stand).z;
	}

	enum PathResult
	{
		PROGRESSING,
		END_OF_PATH,
		PATH_FAILURE,
	};
	NOBODY PathResult UpdatePathMovement(bool allowSpeedChange);
	//bool AStarSearch(CNavArea *startArea); // NOXREF Not implemented
	NOBODY bool ComputePath(CNavArea *goalArea, const Vector *goal, RouteType route);
	NOBODY bool StayOnNavMesh(void);
	CNavArea *GetLastKnownArea(void) const
	{
		return m_lastKnownArea;
	}
	const Vector &GetPathEndpoint(void) const
	{
		return m_path[ m_pathLength - 1 ].pos;
	}
	NOBODY float GetPathDistanceRemaining(void);
	NOBODY void ResetStuckMonitor(void);
	//bool IsAreaVisible(CNavArea *area); // NOXREF Not implemented
	const Vector &GetPathPosition(int numpath) const
	{
		return m_path[ numpath ].pos;
	}
	NOBODY bool GetSimpleGroundHeightWithFloor(const Vector *pos, float *height, Vector *normal);
	NOBODY Place GetPlace(void);
	bool IsUsingLadder(void) const
	{
		return (m_pathLadder != NULL);
	}
	NOBODY void GetOffLadder(void);
	void SetGoalEntity(CBaseEntity *entity)
	{
		m_goalEntity = entity;
	}
	CBaseEntity *GetGoalEntity(void)
	{
		return m_goalEntity;
	}
	NOBODY bool IsNearJump(void);
	NOBODY float GetApproximateFallDamage(float height);
	void ForceRun(float duration)
	{
		Run();
		m_mustRunTimer.Start(duration);
	}
	NOBODY void Wiggle(void);
	NOBODY bool IsFriendInTheWay(Vector *goalPos);
	NOBODY void FeelerReflexAdjustment(Vector *goalPosition);
	void SetLookAngles(float yaw, float pitch)
	{
		m_lookYaw = yaw;
		m_lookPitch = pitch;
	}
	void UpdateLookAngles(void);

	NOBODY void UpdateLookAround(bool updateNow);
	NOBODY void InhibitLookAround(float duration);
	void SetForwardAngle(float angle)
	{
		m_forwardAngle = angle;
	}
	void SetLookAheadAngle(float angle)
	{
		m_lookAheadAngle = angle;
	}
	void SetLookAt(const char *desc, const Vector *pos, PriorityType pri, float duration = -1.0f, bool clearIfClose = false, float angleTolerance = 5.0f);

	void ClearLookAt(void)
	{
		m_lookAtSpotState = NOT_LOOKING_AT_SPOT;
		m_lookAtDesc = NULL;
	}
	bool IsLookingAtSpot(PriorityType pri) const
	{
		if (m_lookAtSpotState != NOT_LOOKING_AT_SPOT && m_lookAtSpotPriority >= pri)
			return true;

		return false;
	}
	bool IsViewMoving(float angleVelThreshold) const
	{
		if (m_lookYawVel < angleVelThreshold && m_lookYawVel > -angleVelThreshold &&
			m_lookPitchVel < angleVelThreshold && m_lookPitchVel > -angleVelThreshold)
		{
			return false;
		}
		return true;
	}
	NOBODY const Vector *GetEyePosition(void) const;
	NOBODY float ComputeWeaponSightRange(void);
	NOBODY void ComputeApproachPoints(void);
	NOBODY void UpdateApproachPoints(void);
	void ClearApproachPoints(void)
	{
		m_approachPointCount = 0;
	}
	NOBODY void DrawApproachPoints(void);
	NOBODY float GetHidingSpotCheckTimestamp(HidingSpot *spot);
	NOBODY void SetHidingSpotCheckTimestamp(HidingSpot *spot);
	NOBODY void EquipBestWeapon(bool mustEquip);
	NOBODY void EquipPistol(void);
	NOBODY void EquipKnife(void);
	NOBODY bool EquipGrenade(bool noSmoke);
	bool IsUsingKnife(void);
	bool IsUsingPistol(void);
	bool IsUsingGrenade(void);
	bool IsUsingSniperRifle(void);
	bool IsUsingAWP(void);
	NOBODY bool IsSniper(void);
	NOBODY bool IsSniping(void);
	bool IsUsingShotgun(void);
	bool IsUsingMachinegun(void);
	void ThrowGrenade(const Vector *target);
	bool IsThrowingGrenade(void) const
	{
		return m_isWaitingToTossGrenade;
	}
	NOBODY bool HasGrenade(void);
	NOBODY bool DoesActiveWeaponHaveSilencer(void);
	NOBODY bool IsUsingHEGrenade(void);
	NOBODY void StartRapidFire(void);
	NOBODY void StopRapidFire(void);
	NOBODY bool IsRapidFiring(void);

	enum ZoomType
	{
		NO_ZOOM = 0,
		LOW_ZOOM,
		HIGH_ZOOM,
	};
	ZoomType GetZoomLevel(void)
	{
		if (m_iFOV > 60.0f)
			return NO_ZOOM;

		if (m_iFOV > 25.0f)
			return LOW_ZOOM;

		return HIGH_ZOOM;
	}
	NOBODY bool AdjustZoom(float range);
	NOBODY bool IsPrimaryWeaponEmpty(void);
	NOBODY bool IsPistolEmpty(void);
	NOBODY int GetHostageEscortCount(void);
	NOBODY void IncreaseHostageEscortCount(void);
	NOBODY float GetRangeToFarthestEscortedHostage(void);
	NOBODY void ResetWaitForHostagePatience(void);
	NOBODY void ResetValues(void);
	NOBODY void BotDeathThink(void);
	NOBODY CBasePlayer *FindNearbyPlayer(void);
	void AdjustSafeTime(void);
	NOBODY void SetState(BotState *state);
	NOBODY void MoveTowardsPosition(const Vector *pos);
	NOBODY void MoveAwayFromPosition(const Vector *pos);
	NOBODY void StrafeAwayFromPosition(const Vector *pos);
	NOBODY void StuckCheck(void);
	NOBODY void BuildTrivialPath(const Vector *goal);
	NOBODY bool ComputePathPositions(void);
	NOBODY void SetupLadderMovement(void);
	NOBODY void SetPathIndex(int newIndex);
	NOBODY void DrawPath(void);
	NOBODY int FindOurPositionOnPath(Vector *close, bool local);
	NOBODY int FindPathPoint(float aheadRange, Vector *point, int *prevIndex);
	NOBODY bool FindClosestPointOnPath(Vector *worldPos, int startIndex, int endIndex, Vector *close);
	NOBODY bool IsStraightLinePathWalkable(Vector *goal);
	NOBODY bool DiscontinuityJump(float ground, bool onlyJumpDown, bool mustJump);
	NOBODY bool UpdateLadderMovement(void);
	NOBODY void ComputeLadderEndpoint(bool isAscending);
	NOBODY void UpdateHostageEscortCount(void);
	NOBODY bool UpdateLookAtNoise(void);
	void UpdateLookAt(void);
	NOBODY void UpdatePeripheralVision(void);
	NOBODY bool BendLineOfSight(Vector *eye, const Vector *point, Vector *bend);
	NOBODY bool FindApproachPointNearestPath(const Vector *pos);
	NOBODY bool FindGrenadeTossPathTarget(const Vector *pos);
	void SetAimOffset(float accuracy);
	void UpdateAimOffset(void);
	NOBODY bool DoEquip(CBasePlayerWeapon *gun);
	NOBODY void ReloadCheck(void);
	NOBODY void SilencerCheck(void);
	NOBODY CBasePlayer *FindMostDangerousThreat(void);
	NOBODY void RespondToRadioCommands(void);
	NOBODY bool IsRadioCommand(GameEventType event);
	void EndVoiceFeedback(bool force = true);
	NOBODY CNavNode *AddNode(const Vector *destPos, const Vector *normal, NavDirType dir, CNavNode *source);
	NOBODY void StartLearnProcess(void);
	NOBODY void UpdateLearnProcess(void);
	NOBODY bool LearnStep(void);
	NOBODY void StartAnalyzeAlphaProcess(void);
	NOBODY void UpdateAnalyzeAlphaProcess(void);
	NOBODY bool AnalyzeAlphaStep(void);
	NOBODY void StartAnalyzeBetaProcess(void);
	NOBODY void UpdateAnalyzeBetaProcess(void);
	NOBODY bool AnalyzeBetaStep(void);
	NOBODY void StartSaveProcess(void);
	NOBODY void UpdateSaveProcess(void);
	void StartNormalProcess(void);
	NOBODY void BotTouch(CBaseEntity *other);
private:
	friend class CCSBotManager;
	friend class AttackState;
	friend class BuyState;

	char m_name[64];
	float m_combatRange;
	mutable bool m_isRogue;
	mutable CountdownTimer m_rogueTimer;
	MoraleType m_morale;
	bool m_diedLastRound;
	float m_safeTime;
	bool m_wasSafe;
	NavRelativeDirType m_blindMoveDir;
	bool m_blindFire;
	float m_surpriseDelay;
	float m_surpriseTimestamp;
	bool m_isFollowing;
	EHANDLE m_leader;
	float m_followTimestamp;
	float m_allowAutoFollowTime;
	CountdownTimer m_hurryTimer;
	IdleState m_idleState;
	HuntState m_huntState;
	AttackState m_attackState;
	InvestigateNoiseState m_investigateNoiseState;
	BuyState m_buyState;
	MoveToState m_moveToState;
	FetchBombState m_fetchBombState;
	PlantBombState m_plantBombState;
	DefuseBombState m_defuseBombState;
	HideState m_hideState;
	EscapeFromBombState m_escapeFromBombState;
	FollowState m_followState;
	UseEntityState m_useEntityState;
	BotState *m_state;
	float m_stateTimestamp;
	bool m_isAttacking;
	TaskType m_task;
	EHANDLE m_taskEntity;
	Vector m_goalPosition;
	EHANDLE m_goalEntity;
	CNavArea *m_currentArea;
	CNavArea *m_lastKnownArea;
	EHANDLE m_avoid;
	float m_avoidTimestamp;
	bool m_isJumpCrouching;
	bool m_isJumpCrouched;
	float m_jumpCrouchTimestamp;

	enum { 	MAX_PATH_LENGTH = 256 };

	struct ConnectInfo
	{
		CNavArea *area;
		NavTraverseType how;
		Vector pos;
		const CNavLadder *ladder;
	} m_path[MAX_PATH_LENGTH];
	/* size: 24, cachelines: 1, members: 4 */

	int m_pathLength;
	int m_pathIndex;
	float m_areaEnteredTimestamp;
	CountdownTimer m_repathTimer;
	mutable CountdownTimer m_avoidFriendTimer;
	mutable bool m_isFriendInTheWay;
	CountdownTimer m_politeTimer;
	bool m_isWaitingBehindFriend;

	enum LadderNavState
	{
		APPROACH_ASCENDING_LADDER,
		APPROACH_DESCENDING_LADDER,
		FACE_ASCENDING_LADDER,
		FACE_DESCENDING_LADDER,
		MOUNT_ASCENDING_LADDER,
		MOUNT_DESCENDING_LADDER,
		ASCEND_LADDER,
		DESCEND_LADDER,
		DISMOUNT_ASCENDING_LADDER,
		DISMOUNT_DESCENDING_LADDER,
		MOVE_TO_DESTINATION,
	}
	m_pathLadderState;
	bool m_pathLadderFaceIn;
	CNavLadder *m_pathLadder;			// 9260
	NavRelativeDirType m_pathLadderDismountDir;
	float m_pathLadderDismountTimestamp;
	float m_pathLadderEnd;
	float m_pathLadderTimestamp;
	class CountdownTimer m_mustRunTimer;
	CSGameState m_gameState;
	byte m_hostageEscortCount;
	float m_hostageEscortCountTimestamp;
	bool m_isWaitingForHostage;
	CountdownTimer m_inhibitWaitingForHostageTimer;
	CountdownTimer m_waitForHostageTimer;
	Vector m_noisePosition;
	float m_noiseTimestamp;
	CNavArea *m_noiseArea;
	float m_noiseCheckTimestamp;
	PriorityType m_noisePriority;
	bool m_isNoiseTravelRangeChecked;
	float m_lookAroundStateTimestamp;
	float m_lookAheadAngle;
	float m_forwardAngle;
	float m_inhibitLookAroundTimestamp;

	enum LookAtSpotState
	{
		NOT_LOOKING_AT_SPOT = 0,
		LOOK_TOWARDS_SPOT,
		LOOK_AT_SPOT,
		NUM_LOOK_AT_SPOT_STATES,
	}
	m_lookAtSpotState;
	Vector m_lookAtSpot;

	PriorityType m_lookAtSpotPriority;
	float m_lookAtSpotDuration;
	float m_lookAtSpotTimestamp;
	float m_lookAtSpotAngleTolerance;
	bool m_lookAtSpotClearIfClose;
	const char *m_lookAtDesc;
	float m_peripheralTimestamp;

	enum { MAX_APPROACH_POINTS = 16 };
	Vector m_approachPoint[MAX_APPROACH_POINTS];
	unsigned char m_approachPointCount;
	Vector m_approachPointViewPosition;

	bool m_isWaitingToTossGrenade;
	CountdownTimer m_tossGrenadeTimer;
	SpotEncounter *m_spotEncounter;
	float m_spotCheckTimestamp;

	enum { MAX_CHECKED_SPOTS = 64 };
	struct HidingSpotCheckInfo
	{
		HidingSpot *spot;
		float timestamp;
	}/* size: 8, cachelines: 1, members: 2 */
	m_checkedHidingSpot[MAX_CHECKED_SPOTS];
	int m_checkedHidingSpotCount;

	float m_lookPitch;			// 10500
	float m_lookPitchVel;
	float m_lookYaw;
	float m_lookYawVel;
	Vector m_eyePos;
	Vector m_aimOffset;
	Vector m_aimOffsetGoal;
	float m_aimOffsetTimestamp;
	float m_aimSpreadTimestamp;
	Vector m_aimSpot;
	DispositionType m_disposition;
	CountdownTimer m_ignoreEnemiesTimer;
	mutable EHANDLE m_enemy;
	bool m_isEnemyVisible;
	unsigned char m_visibleEnemyParts;
	Vector m_lastEnemyPosition;
	float m_lastSawEnemyTimestamp;
	float m_firstSawEnemyTimestamp;
	float m_currentEnemyAcquireTimestamp;
	float m_enemyDeathTimestamp;
	bool m_isLastEnemyDead;
	int m_nearbyEnemyCount;
	unsigned int m_enemyPlace;

	struct WatchInfo
	{
		float timestamp;
		bool isEnemy;
	}/* size: 8, cachelines: 1, members: 2 */
	m_watchInfo[32];

	mutable EHANDLE m_bomber;
	int m_nearbyFriendCount;
	mutable EHANDLE m_closestVisibleFriend;
	mutable EHANDLE m_closestVisibleHumanFriend;
	CBasePlayer *m_attacker;
	float m_attackedTimestamp;
	int m_lastVictimID;
	bool m_isAimingAtEnemy;
	bool m_isRapidFiring;
	IntervalTimer m_equipTimer;
	float m_fireWeaponTimestamp;

	enum { MAX_ENEMY_QUEUE = 20 };
	struct ReactionState
	{
		EHANDLE player;
		bool isReloading;
		bool isProtectedByShield;
	} m_enemyQueue[MAX_ENEMY_QUEUE];
	/* size: 12, cachelines: 1, members: 3 */

	byte m_enemyQueueIndex;
	byte m_enemyQueueCount;
	byte m_enemyQueueAttendIndex;
	bool m_isStuck;
	float m_stuckTimestamp;
	Vector m_stuckSpot;
	NavRelativeDirType m_wiggleDirection;
	float m_wiggleTimestamp;
	float m_stuckJumpTimestamp;

	enum { MAX_VEL_SAMPLES = 5 };

	float m_avgVel[MAX_VEL_SAMPLES];
	int m_avgVelIndex;
	int m_avgVelCount;
	Vector m_lastOrigin;

	GameEventType m_lastRadioCommand;
	float m_lastRadioRecievedTimestamp;
	float m_lastRadioSentTimestamp;
	EHANDLE m_radioSubject;
	Vector m_radioPosition;
	float m_voiceFeedbackStartTimestamp;
	float m_voiceFeedbackEndTimestamp;
	BotChatterInterface m_chatter;
	CNavNode *m_navNodeList;
	CNavNode *m_currentNode;
	NavDirType m_generationDir;
	NavAreaList::iterator m_analyzeIter;		// TODO: //iterator m_analyzeIter;

	enum ProcessType
	{
		PROCESS_NORMAL = 0,
		PROCESS_LEARN,
		PROCESS_ANALYZE_ALPHA,
		PROCESS_ANALYZE_BETA,
		PROCESS_SAVE,
	}
	m_processMode;
	CountdownTimer m_mumbleTimer;
	CountdownTimer m_booTimer;
	CountdownTimer m_relocateTimer;

};/* size: 11424, cachelines: 179, members: 161 */

/* <2e8465> ../cstrike/dlls/bot/cs_bot.cpp:1004 */
class CollectRetreatSpotsFunctor
{
public:
	CollectRetreatSpotsFunctor(CCSBot *me, float range)
	{
		m_me = me;
		m_count = 0;
		m_range = range;
	}

	enum { MAX_SPOTS = 256 };

	bool operator()(CNavArea *area)
	{
		// collect all the hiding spots in this area
		const HidingSpotList *list = area->GetHidingSpotList();

		for (HidingSpotList::const_iterator iter = list->begin(); iter != list->end() && m_count < MAX_SPOTS; ++iter)
		{
			const HidingSpot *spot = *iter;

			// make sure hiding spot is in range
			if (m_range > 0.0f)
				if ((*spot->GetPosition() - m_me->pev->origin).IsLengthGreaterThan(m_range))
					continue;

			// if a Player is using this hiding spot, don't consider it
			if (IsSpotOccupied(m_me, spot->GetPosition()))
			{
				// player is in hiding spot
				/// @todo Check if player is moving or sitting still
				continue;
			}

			// don't select spot if an enemy can see it
			if (UTIL_IsVisibleToTeam(*spot->GetPosition() + Vector(0, 0, HalfHumanHeight), OtherTeam(m_me->m_iTeam )))
				continue;

			// don't select spot if it is closest to an enemy
			CBasePlayer *owner = UTIL_GetClosestPlayer(spot->GetPosition());
			if (owner && m_me->m_iTeam != owner->m_iTeam)
				continue;

			m_spot[ m_count++ ] = spot->GetPosition();
		}

		// if we've filled up, stop searching
		if (m_count == MAX_SPOTS)
			return false;

		return true;
	}
private:

	CCSBot *m_me;
	float m_range;

	const Vector *m_spot[ MAX_SPOTS ];
	int m_count;

};/* size: 1036, cachelines: 17, members: 4 */

/* <2e7f9f> ../cstrike/dlls/bot/cs_bot.cpp:1088 */
class FarthestHostage
{
public:
	FarthestHostage(CCSBot *me)//, float range)
	{
		m_me = me;
		//m_farRange = range;
	}
	bool operator()(CHostage *hostage)
	{
		//TODO: untested

		if (!hostage->IsFollowing(m_me))
			return false;

		return true;
	}
private:
	const CCSBot *m_me;
	float m_farRange;

};/* size: 8, cachelines: 1, members: 2 */

/* <5a0af3> ../cstrike/dlls/bot/cs_bot.h:1114 */
class PathCost
{
public:
	PathCost(CCSBot *bot, RouteType route = SAFEST_ROUTE)
	{
		m_bot = bot;
		m_route = route;
	}
	float operator() (CNavArea *area, CNavArea *fromArea, const CNavLadder *ladder)
	{
		/*#define NAV_MESH_JUMP 0x0002
		float baseDangerFactor = 100.0f;
		float dangerFactor = (1.0f - (0.95f * m_bot->GetProfile()->GetAggression())) * baseDangerFactor;
		if (fromArea == NULL)
		{
			if (m_route == FASTEST_ROUTE)
				return 0.0f;
			return dangerFactor * area->GetDanger(m_bot->m_iTeam);
		}
		else if ((fromArea->GetAttributes() & NAV_MESH_JUMP) && (area->GetAttributes() & NAV_MESH_JUMP))
		{
			return -1.0f;
		}
		else
		{
			float dist;
			if (ladder)
			{
				const float ladderPenalty = 1.0f;
				dist = ladderPenalty * ladder->m_length;

				//if (m_bot->GetHostageEscortCount())
				//	dist *= 100.0f;
			}
			else
			{
				dist = (area->GetCenter() - fromArea->GetCenter()).Length();
			}
			float cost = dist + fromArea->GetCostSoFar();
			if (cv_bot_zombie.value)
				return cost;

			if (!area->IsUnderwater() && area->IsConnected(fromArea, NUM_DIRECTIONS) == false)
			{
				float fallDistance = -fromArea->ComputeHeightChange(area);
				if (ladder && ladder->m_bottom.z < fromArea->GetCenter().z && ladder->m_bottom.z > area->GetCenter().z)
				{
					fallDistance = ladder->m_bottom.z - area->GetCenter().z;
				}
				float fallDamage = m_bot->GetApproximateFallDamage(fallDistance);
				if (fallDamage > 0.0f)
				{
					const float deathFallMargin = 10.0f;
					if (fallDamage + deathFallMargin >= m_bot->pev->health)
						return -1.0f;
					const float painTolerance = 15.0f * m_bot->GetProfile()->GetAggression() + 10.0f;
					if (m_route != FASTEST_ROUTE || fallDamage > painTolerance)
					{
						cost += 100.0f * fallDamage * fallDamage;
					}
				}
			}
			if (area->GetAttributes() & (NAV_MESH_CROUCH | NAV_MESH_WALK))
			{
				float penalty = (m_route == FASTEST_ROUTE) ? 20.0f : 5.0f;
				cost += penalty * dist;
			}
			if (area->GetAttributes() & NAV_MESH_JUMP)
			{
				const float jumpPenalty = 1.0f;
				cost += jumpPenalty * dist;
			}
			if (area->GetAttributes() & NAV_MESH_AVOID)
			{
				const float avoidPenalty = 20.0f;
				cost += avoidPenalty * dist;
			}
			if (m_route == SAFEST_ROUTE)
			{
				cost += dist * dangerFactor * area->GetDanger(m_bot->GetTeamNumber());
			}
			if (!m_bot->IsAttacking())
			{
				float size = (area->GetSizeX() + area->GetSizeY()) / 2.0f;
				if (size >= 1.0f)
				{
					const float costPerFriendPerUnit = 50000.0f;
					cost += costPerFriendPerUnit * (float)area->GetPlayerCount(m_bot->GetTeamNumber()) / size;
				}
			}
			return cost;
		}*/
		return 0.0f;
	}
private:
	CCSBot *m_bot;
	RouteType m_route;

};/* size: 8, cachelines: 1, members: 2 */

/* <568fae> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:95 */
class FollowTargetCollector
{
public:
	FollowTargetCollector(CBasePlayer *player)
	{
		m_player = player;

		Vector playerVel = player->pev->velocity;

		m_forward.x = playerVel.x;
		m_forward.y = playerVel.y;

		float speed = m_forward.NormalizeInPlace();

		Vector playerOrigin = player->pev->origin;

		const float walkSpeed = 100.0f;
		if (speed < walkSpeed)
		{
			m_cutoff.x = playerOrigin.x;
			m_cutoff.y = playerOrigin.y;

			m_forward.x = 0.0f;
			m_forward.y = 0.0f;
		}
		else
		{
			const float k = 1.5f; // 2.0f;
			float trimSpeed = (speed < 200.0f) ? speed : 200.0f;

			m_cutoff.x = playerOrigin.x + k * trimSpeed * m_forward.x;
			m_cutoff.y = playerOrigin.y + k * trimSpeed * m_forward.y;
		}

		m_targetAreaCount = 0;
	}

	enum { MAX_TARGET_AREAS = 128 };

	/* <568dc3> ../cstrike/dlls/bot/states/cs_bot_follow.cpp:124 */
	bool operator()(CNavArea *area)
	{
		if (m_targetAreaCount >= MAX_TARGET_AREAS)
			return false;

		// only use two-way connections
		if (!area->GetParent() || area->IsConnected(area->GetParent(), NUM_DIRECTIONS))
		{
			if (m_forward.IsZero())
			{
				m_targetArea[ m_targetAreaCount++ ] = area;
			}
			else
			{
				// collect areas in the direction of the player's forward motion
				Vector2D to(((*area->GetCenter()).x - m_cutoff.x), (*area->GetCenter()).y - m_cutoff.y);
				to.NormalizeInPlace();

				//if (DotProduct(to, m_forward) > 0.7071f)
				if ((to.x * m_forward.x + to.y * m_forward.y) > 0.7071f)
					m_targetArea[ m_targetAreaCount++ ] = area;
			}
		}

		return (m_targetAreaCount < MAX_TARGET_AREAS);
	}

	CBasePlayer *m_player;
	Vector2D m_forward;
	Vector2D m_cutoff;
	CNavArea *m_targetArea[ MAX_TARGET_AREAS ];
	int m_targetAreaCount;

};/* size: 536, cachelines: 9, members: 5 */

#ifdef HOOK_GAMEDLL

//typedef bool (CCSBot::*IS_VISIBLE_VECTOR)(Vector *, bool);
//typedef bool (CCSBot::*IS_VISIBLE_CBASEPLAYER)(CBasePlayer *, bool, unsigned char *);

typedef void (CCSBot::*HIDE_NAV_AREA)(CNavArea *, float, float, bool);
typedef void (CCSBot::*HIDE_VECTOR)(const Vector *, float, bool);

typedef const CSGameState *(CCSBot::*GETGAMESTATE_CONST)(void) const;
typedef CSGameState *(CCSBot::*GETGAMESTATE_NOTCONST)(void);

#endif // HOOK_GAMEDLL

NOBODY void InstallBotControl(void);
void Bot_ServerCommand(void);
void Bot_RegisterCvars(void);
NOBODY int GetBotFollowCount(CBasePlayer *leader);
NOBODY const Vector *FindNearbyRetreatSpot(CCSBot *me, float maxRange);

NOXREF void drawProgressMeter(float progress, char *title);
NOXREF void startProgressMeter(const char *title);
NOXREF void hideProgressMeter(void);

bool isSniperRifle(CBasePlayerItem *item);
float StayOnLadderLine(CCSBot *me, const CNavLadder *ladder);

// refs

extern void (*pCCSBot__UpdateLookAngles)(void);
extern void (*pCCSBot__Update)(void);

#endif // CS_BOT_H
