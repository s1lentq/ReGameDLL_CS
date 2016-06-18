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

#include "bot/cs_gamestate.h"
#include "bot/cs_bot_manager.h"
#include "bot/cs_bot_chatter.h"

#define PRIMARY_WEAPON_BUY_COUNT	13
#define SECONDARY_WEAPON_BUY_COUNT	3

#define FLAG_PROGRESS_DRAW		0x0	// draw status bar progress
#define FLAG_PROGRESS_START		0x1	// init status bar progress
#define FLAG_PROGRESS_HIDE		0x2	// hide status bar progress

#define HI_X				0x01
#define LO_X				0x02
#define HI_Y				0x04
#define LO_Y				0x08
#define HI_Z				0x10
#define LO_Z				0x20

extern int _navAreaCount;
extern int _currentIndex;

extern struct BuyInfo primaryWeaponBuyInfoCT[PRIMARY_WEAPON_BUY_COUNT];
extern struct BuyInfo secondaryWeaponBuyInfoCT[SECONDARY_WEAPON_BUY_COUNT];

extern struct BuyInfo primaryWeaponBuyInfoT[PRIMARY_WEAPON_BUY_COUNT];
extern struct BuyInfo secondaryWeaponBuyInfoT[SECONDARY_WEAPON_BUY_COUNT];

class CCSBot;
class BotChatterInterface;

class BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const = 0;
};

class IdleState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual const char *GetName() const { return "Idle"; }
};

class HuntState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "Hunt"; }
public:
	CNavArea *m_huntArea;
};

class AttackState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "Attack"; }
public:
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
};

class InvestigateNoiseState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "InvestigateNoise"; }
private:
	void AttendCurrentNoise(CCSBot *me);
	Vector m_checkNoisePosition;
};

class BuyState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "Buy"; }
public:
	bool m_isInitialDelay;
	int m_prefRetries;
	int m_prefIndex;
	int m_retries;
	bool m_doneBuying;
	bool m_buyDefuseKit;
	bool m_buyGrenade;
	bool m_buyShield;
	bool m_buyPistol;
};

class MoveToState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "MoveTo"; }

	void SetGoalPosition(const Vector &pos) { m_goalPosition = pos; }
	void SetRouteType(RouteType route) { m_routeType = route; }

private:
	Vector m_goalPosition;
	RouteType m_routeType;
	bool m_radioedPlan;
	bool m_askedForCover;
};

class FetchBombState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual const char *GetName() const { return "FetchBomb"; }
};

class PlantBombState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "PlantBomb"; }
};

class DefuseBombState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "DefuseBomb"; }
};

class HideState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "Hide"; }

public:
	void SetHidingSpot(const Vector &pos) { m_hidingSpot = pos; }
	const Vector &GetHidingSpot() const { return m_hidingSpot; }

	void SetSearchArea(CNavArea *area) { m_searchFromArea = area; }
	void SetSearchRange(float range) { m_range = range; }

	void SetDuration(float time) { m_duration = time; }
	void SetHoldPosition(bool hold) { m_isHoldingPosition = hold; }

	bool IsAtSpot() const { return m_isAtSpot; }

public:
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
};

class EscapeFromBombState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "EscapeFromBomb"; }
};

class FollowState: public BotState
{
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "Follow"; }

	void SetLeader(CBaseEntity *leader) { m_leader = leader; }

public:
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
};

class UseEntityState: public BotState {
public:
	virtual void OnEnter(CCSBot *me) {}
	virtual void OnUpdate(CCSBot *me) {}
	virtual void OnExit(CCSBot *me) {}
	virtual const char *GetName() const { return "UseEntity"; }

	void SetEntity(CBaseEntity *entity) { m_entity = entity; }

private:
	EHANDLE m_entity;
};

// The Counter-strike Bot
class CCSBot: public CBot {
public:
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;		// invoked when injured by something (EXTEND) - returns the amount of damage inflicted
	virtual void Killed(entvars_t *pevAttacker, int iGib) = 0;									// invoked when killed (EXTEND)
	virtual void RoundRespawn() = 0;
	virtual void Blind(float duration, float holdTime, float fadeTime, int alpha = 255) = 0;					// player blinded by a flashbang
	virtual void OnTouchingWeapon(CWeaponBox *box) = 0;										// invoked when in contact with a CWeaponBox

	virtual bool Initialize(const BotProfile *profile) = 0;									// (EXTEND) prepare bot for action
	virtual void SpawnBot() = 0;												// (EXTEND) spawn the bot into the game

	virtual void Upkeep() = 0;													// lightweight maintenance, invoked frequently
	virtual void Update() = 0;													// heavyweight algorithms, invoked less often

	virtual void Walk() = 0;
	virtual bool Jump(bool mustJump = false) = 0;										// returns true if jump was started

	virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL) = 0;			// invoked when event occurs in the game (some events have NULL entity)

	#define CHECK_FOV true
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;							// return true if we can see the point
	virtual bool IsVisible(CBasePlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const = 0;		// return true if we can see any part of the player

	virtual bool IsEnemyPartVisible(VisiblePartType part) const = 0;								// if enemy is visible, return the part we see for our current enemy

public:
	const Vector &GetEyePosition() const
	{
		m_eyePos = pev->origin + pev->view_ofs;
		return m_eyePos;
	}
public:
	friend class CCSBotManager;

	// TODO: Get rid of these
	friend class AttackState;
	friend class BuyState;

	char m_name[64];					// copied from STRING(pev->netname) for debugging

	// behavior properties
	float m_combatRange;					// desired distance between us and them during gunplay
	mutable bool m_isRogue;					// if true, the bot is a "rogue" and listens to no-one
	mutable CountdownTimer m_rogueTimer;

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

	MoraleType m_morale;					// our current morale, based on our win/loss history
	bool m_diedLastRound;					// true if we died last round
	float m_safeTime;					// duration at the beginning of the round where we feel "safe"
	bool m_wasSafe;						// true if we were in the safe time last update
	NavRelativeDirType m_blindMoveDir;			// which way to move when we're blind
	bool m_blindFire;					// if true, fire weapon while blinded

	// TODO: implement through CountdownTimer
	float m_surpriseDelay;					// when we were surprised
	float m_surpriseTimestamp;

	bool m_isFollowing;					// true if we are following someone
	EHANDLE m_leader;					// the ID of who we are following
	float m_followTimestamp;				// when we started following
	float m_allowAutoFollowTime;				// time when we can auto follow

	CountdownTimer m_hurryTimer;				// if valid, bot is in a hurry

	// instances of each possible behavior state, to avoid dynamic memory allocation during runtime
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

	// TODO: Allow multiple simultaneous state machines (look around, etc)
	BotState *m_state;							// current behavior state
	float m_stateTimestamp;							// time state was entered
	bool m_isAttacking;							// if true, special Attack state is overriding the state machine

	// high-level tasks
	enum TaskType
	{
		SEEK_AND_DESTROY,
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

		NUM_TASKS
	};
	TaskType m_task;							// our current task
	EHANDLE m_taskEntity;							// an entity used for our task

	// navigation
	Vector m_goalPosition;
	EHANDLE m_goalEntity;

	CNavArea *m_currentArea;						// the nav area we are standing on
	CNavArea *m_lastKnownArea;						// the last area we were in
	EHANDLE m_avoid;							// higher priority player we need to make way for
	float m_avoidTimestamp;
	bool m_isJumpCrouching;
	bool m_isJumpCrouched;
	float m_jumpCrouchTimestamp;

	// path navigation data
	enum { 	_MAX_PATH_LENGTH = 256 };
	struct ConnectInfo
	{
		CNavArea *area;			// the area along the path
		NavTraverseType how;		// how to enter this area from the previous one
		Vector pos;			// our movement goal position at this point in the path
		const CNavLadder *ladder;	// if "how" refers to a ladder, this is it
	}
	m_path[_MAX_PATH_LENGTH];
	int m_pathLength;
	int m_pathIndex;
	float m_areaEnteredTimestamp;

	CountdownTimer m_repathTimer;												// must have elapsed before bot can pathfind again

	mutable CountdownTimer m_avoidFriendTimer;		// used to throttle how often we check for friends in our path
	mutable bool m_isFriendInTheWay;			// true if a friend is blocking our path
	CountdownTimer m_politeTimer;				// we'll wait for friend to move until this runs out
	bool m_isWaitingBehindFriend;				// true if we are waiting for a friend to move

	enum LadderNavState
	{
		APPROACH_ASCENDING_LADDER,		// prepare to scale a ladder
		APPROACH_DESCENDING_LADDER,		// prepare to go down ladder
		FACE_ASCENDING_LADDER,
		FACE_DESCENDING_LADDER,
		MOUNT_ASCENDING_LADDER,			// move toward ladder until "on" it
		MOUNT_DESCENDING_LADDER,		// move toward ladder until "on" it
		ASCEND_LADDER,				// go up the ladder
		DESCEND_LADDER,				// go down the ladder
		DISMOUNT_ASCENDING_LADDER,		// get off of the ladder
		DISMOUNT_DESCENDING_LADDER,		// get off of the ladder
		MOVE_TO_DESTINATION,			// dismount ladder and move to destination area
	}
	m_pathLadderState;
	bool m_pathLadderFaceIn;			// if true, face towards ladder, otherwise face away
	const CNavLadder *m_pathLadder;			// the ladder we need to use to reach the next area
	NavRelativeDirType m_pathLadderDismountDir;	// which way to dismount
	float m_pathLadderDismountTimestamp;		// time when dismount started
	float m_pathLadderEnd;				// if ascending, z of top, if descending z of bottom
	float m_pathLadderTimestamp;			// time when we started using ladder - for timeout check

	CountdownTimer m_mustRunTimer;			// if nonzero, bot cannot walk

	// game scenario mechanisms
	CSGameState m_gameState;

	// hostages mechanism
	byte m_hostageEscortCount;
	float m_hostageEscortCountTimestamp;
	bool m_isWaitingForHostage;
	CountdownTimer m_inhibitWaitingForHostageTimer;
	CountdownTimer m_waitForHostageTimer;

	// listening mechanism
	Vector m_noisePosition;				// position we last heard non-friendly noise
	float m_noiseTimestamp;				// when we heard it (can get zeroed)
	CNavArea *m_noiseArea;				// the nav area containing the noise
	float m_noiseCheckTimestamp;
	PriorityType m_noisePriority;			// priority of currently heard noise
	bool m_isNoiseTravelRangeChecked;

	// "looking around" mechanism
	float m_lookAroundStateTimestamp;		// time of next state change
	float m_lookAheadAngle;				// our desired forward look angle
	float m_forwardAngle;				// our current forward facing direction
	float m_inhibitLookAroundTimestamp;		// time when we can look around again

	enum LookAtSpotState
	{
		NOT_LOOKING_AT_SPOT,		// not currently looking at a point in space
		LOOK_TOWARDS_SPOT,		// in the process of aiming at m_lookAtSpot
		LOOK_AT_SPOT,			// looking at m_lookAtSpot
		NUM_LOOK_AT_SPOT_STATES
	}
	m_lookAtSpotState;
	Vector m_lookAtSpot;					// the spot we're currently looking at
	PriorityType m_lookAtSpotPriority;
	float m_lookAtSpotDuration;				// how long we need to look at the spot
	float m_lookAtSpotTimestamp;				// when we actually began looking at the spot
	float m_lookAtSpotAngleTolerance;			// how exactly we must look at the spot
	bool m_lookAtSpotClearIfClose;				// if true, the look at spot is cleared if it gets close to us
	const char *m_lookAtDesc;				// for debugging
	float m_peripheralTimestamp;

	enum { MAX_APPROACH_POINTS = 16 };
	Vector m_approachPoint[MAX_APPROACH_POINTS];
	unsigned char m_approachPointCount;
	Vector m_approachPointViewPosition;			// the position used when computing current approachPoint set
	bool m_isWaitingToTossGrenade;				// lining up throw
	CountdownTimer m_tossGrenadeTimer;			// timeout timer for grenade tossing

	SpotEncounter *m_spotEncounter;				// the spots we will encounter as we move thru our current area
	float m_spotCheckTimestamp;				// when to check next encounter spot

	// TODO: Add timestamp for each possible client to hiding spots
	enum { MAX_CHECKED_SPOTS = 64 };
	struct HidingSpotCheckInfo
	{
		HidingSpot *spot;
		float timestamp;
	}
	m_checkedHidingSpot[MAX_CHECKED_SPOTS];
	int m_checkedHidingSpotCount;

	// view angle mechanism
	float m_lookPitch;					// our desired look pitch angle
	float m_lookPitchVel;
	float m_lookYaw;					// our desired look yaw angle
	float m_lookYawVel;

	// aim angle mechanism
	mutable Vector m_eyePos;
	Vector m_aimOffset;					// current error added to victim's position to get actual aim spot
	Vector m_aimOffsetGoal;					// desired aim offset
	float m_aimOffsetTimestamp;				// time of next offset adjustment
	float m_aimSpreadTimestamp;				// time used to determine max spread as it begins to tighten up
	Vector m_aimSpot;					// the spot we are currently aiming to fire at

	// attack state data
	// behavior modifiers
	enum DispositionType
	{
		ENGAGE_AND_INVESTIGATE,		// engage enemies on sight and investigate enemy noises
		OPPORTUNITY_FIRE,		// engage enemies on sight, but only look towards enemy noises, dont investigate
		SELF_DEFENSE,			// only engage if fired on, or very close to enemy
		IGNORE_ENEMIES,			// ignore all enemies - useful for ducking around corners, running away, etc

		NUM_DISPOSITIONS
	};
	DispositionType m_disposition;				// how we will react to enemies
	CountdownTimer m_ignoreEnemiesTimer;			// how long will we ignore enemies
	mutable EHANDLE m_enemy;				// our current enemy
	bool m_isEnemyVisible;					// result of last visibility test on enemy
	unsigned char m_visibleEnemyParts;			// which parts of the visible enemy do we see
	Vector m_lastEnemyPosition;				// last place we saw the enemy
	float m_lastSawEnemyTimestamp;
	float m_firstSawEnemyTimestamp;
	float m_currentEnemyAcquireTimestamp;
	float m_enemyDeathTimestamp;				// if m_enemy is dead, this is when he died
	bool m_isLastEnemyDead;					// true if we killed or saw our last enemy die
	int m_nearbyEnemyCount;					// max number of enemies we've seen recently
	unsigned int m_enemyPlace;				// the location where we saw most of our enemies

	struct WatchInfo
	{
		float timestamp;
		bool isEnemy;
	}
	m_watchInfo[MAX_CLIENTS];
	mutable EHANDLE m_bomber;				// points to bomber if we can see him

	int m_nearbyFriendCount;				// number of nearby teammates
	mutable EHANDLE m_closestVisibleFriend;			// the closest friend we can see
	mutable EHANDLE m_closestVisibleHumanFriend;		// the closest human friend we can see

	CBasePlayer *m_attacker;				// last enemy that hurt us (may not be same as m_enemy)
	float m_attackedTimestamp;				// when we were hurt by the m_attacker

	int m_lastVictimID;					// the entindex of the last victim we killed, or zero
	bool m_isAimingAtEnemy;					// if true, we are trying to aim at our enemy
	bool m_isRapidFiring;					// if true, RunUpkeep() will toggle our primary attack as fast as it can
	IntervalTimer m_equipTimer;				// how long have we had our current weapon equipped
	float m_fireWeaponTimestamp;

	// reaction time system
	enum { MAX_ENEMY_QUEUE = 20 };
	struct ReactionState
	{
		// NOTE: player position & orientation is not currently stored separately
		EHANDLE player;
		bool isReloading;
		bool isProtectedByShield;
	}
	m_enemyQueue[MAX_ENEMY_QUEUE];				// round-robin queue for simulating reaction times

	byte m_enemyQueueIndex;
	byte m_enemyQueueCount;
	byte m_enemyQueueAttendIndex;				// index of the timeframe we are "conscious" of

	// stuck detection
	bool m_isStuck;
	float m_stuckTimestamp;					// time when we got stuck
	Vector m_stuckSpot;					// the location where we became stuck
	NavRelativeDirType m_wiggleDirection;
	float m_wiggleTimestamp;
	float m_stuckJumpTimestamp;				// time for next jump when stuck

	enum { MAX_VEL_SAMPLES = 5 };
	float m_avgVel[MAX_VEL_SAMPLES];
	int m_avgVelIndex;
	int m_avgVelCount;
	Vector m_lastOrigin;

	// chatter mechanism
	GameEventType m_lastRadioCommand;			// last radio command we recieved

	float m_lastRadioRecievedTimestamp;			// time we recieved a radio message
	float m_lastRadioSentTimestamp;				// time when we send a radio message
	EHANDLE m_radioSubject;					// who issued the radio message
	Vector m_radioPosition;					// position referred to in radio message
	float m_voiceFeedbackStartTimestamp;
	float m_voiceFeedbackEndTimestamp;			// new-style "voice" chatter gets voice feedback
	BotChatterInterface m_chatter;

	// learn map mechanism
	const CNavNode *m_navNodeList;
	CNavNode *m_currentNode;
	NavDirType m_generationDir;
	NavAreaList::iterator m_analyzeIter;

	enum ProcessType
	{
		PROCESS_NORMAL,
		PROCESS_LEARN,
		PROCESS_ANALYZE_ALPHA,
		PROCESS_ANALYZE_BETA,
		PROCESS_SAVE,
	}
	m_processMode;
	CountdownTimer m_mumbleTimer;
	CountdownTimer m_booTimer;
	CountdownTimer m_relocateTimer;
};
