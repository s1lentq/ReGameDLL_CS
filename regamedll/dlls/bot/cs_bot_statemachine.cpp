#include "precompiled.h"

/* <3b3a2a> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:16 */
NOBODY void CCSBot::SetState(BotState *state)
{
//	StopAttacking(CCSBot *const this);  //    22
}

/* <3b3ab4> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:34 */
NOBODY void CCSBot::Idle(void)
{
//	SetTask(CCSBot::Idle(//		enum TaskType task,
//		class CBaseEntity *entity);  //    36
}

/* <3b3afa> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:41 */
NOBODY void CCSBot::EscapeFromBomb(void)
{
//	SetTask(CCSBot::EscapeFromBomb(//		enum TaskType task,
//		class CBaseEntity *entity);  //    43
}

/* <3b3b4b> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:48 */
NOBODY void CCSBot::Follow(CBasePlayer *player)
{
//	SetTask(CCSBot *const this,
//		enum TaskType task,
//		class CBaseEntity *entity);  //    60
//	SetLeader(FollowState *const this,
//			class CBasePlayer *player);  //    61
}

/* <3b3bd1> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:69 */
NOBODY void CCSBot::ContinueFollowing(void)
{
//	{
//		class CBasePlayer *leader;                           //    73
//		SetTask(CCSBot *const this,
//			enum TaskType task,
//			class CBaseEntity *entity);  //    71
//		SetLeader(FollowState *const this,
//				class CBasePlayer *player);  //    74
//	}
}

/* <3b3c57> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:83 */
NOBODY void CCSBot::StopFollowing(void)
{
}

/* <3b3c7e> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:94 */
NOBODY void CCSBot::RescueHostages(void)
{
//	SetTask(CCSBot::RescueHostages(//		enum TaskType task,
//		class CBaseEntity *entity);  //    96
}

/* <3b3cc9> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:103 */
NOBODY void CCSBot::UseEntity(CBaseEntity *entity)
{
//	SetEntity(UseEntityState *const this,
//			class CBaseEntity *entity);  //   105
}

/* <3b3d23> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:116 */
NOBODY void CCSBot::Hide(CNavArea *searchFromArea, float duration, float hideRange, bool holdPosition)
{
//	{
//		class CNavArea *source;                              //   120
//		Vector sourcePos;                               //   121
//		const Vector *pos;                            //   146
//		DestroyPath(CCSBot *const this);  //   118
//		SetDuration(HideState *const this,
//				float time);  //   142
//		SetSearchArea(HideState *const this,
//				class CNavArea *area);  //   140
//		SetSearchRange(HideState *const this,
//				float range);  //   141
//		SetHoldPosition(HideState *const this,
//				bool hold);  //   143
//		SetHidingSpot(HideState *const this,
//				const Vector *pos);  //   154
//		Idle(CCSBot *const this);  //   160
//	}
}

/* <3b3e98> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:171 */
NOBODY void CCSBot::Hide(const Vector *hidingSpot, float duration, bool holdPosition)
{
//	{
//		class CNavArea *hideArea;                            //   173
//		DestroyPath(CCSBot *const this);  //   181
//		SetHoldPosition(HideState *const this,
//				bool hold);  //   186
//		SetSearchArea(HideState *const this,
//				class CNavArea *area);  //   183
//		SetSearchRange(HideState *const this,
//				float range);  //   184
//		SetDuration(HideState *const this,
//				float time);  //   185
//		SetHidingSpot(HideState *const this,
//				const Vector *pos);  //   187
//		Idle(CCSBot *const this);  //   193
//	}
}

/* <3b3fc1> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:205 */
NOBODY bool CCSBot::TryToHide(CNavArea *searchFromArea, float duration, float hideRange, bool holdPosition, bool useNearest)
{
//	{
//		class CNavArea *source;                              //   207
//		Vector sourcePos;                               //   208
//		const Vector *pos;                            //   232
//		SetDuration(HideState *const this,
//				float time);  //   228
//		SetSearchArea(HideState *const this,
//				class CNavArea *area);  //   226
//		SetSearchRange(HideState *const this,
//				float range);  //   227
//		SetHoldPosition(HideState *const this,
//				bool hold);  //   229
//		SetHidingSpot(HideState *const this,
//				const Vector *pos);  //   239
//	}
}

/* <3b40ed> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:256 */
NOBODY bool CCSBot::TryToRetreat(void)
{
//	{
//		const Vector *spot;                           //   258
//		{
//			float holdTime;                               //   265
//			Hide(CCSBot *const this,
//				const Vector *hidingSpot,
//				float duration,
//				bool holdPosition);  //   268
//		}
//	}
}

/* <3b426a> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:280 */
NOBODY void CCSBot::Hunt(void)
{
}

/* <3b4291> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:290 */
NOBODY void CCSBot::Attack(CBasePlayer *victim)
{
	if (victim == NULL)
		return;

	// zombies never attack
	if (cv_bot_zombie.value)
		return;

	// cannot attack if we are reloading
	if (IsActiveWeaponReloading())
		return;

	// change enemy
	SetEnemy( victim );

	// Do not "re-enter" the attack state if we are already attacking
	if (IsAttacking())
		return;

	if (IsAtHidingSpot())
		m_attackState.SetCrouchAndHold( (RANDOM_FLOAT(0, 100) < 60.0f) != 0 );
	else
		m_attackState.SetCrouchAndHold( 0 );

	PrintIfWatched("ATTACK BEGIN (reaction time = %g (+ update time), surprise time = %g, attack delay = %g)\n");
	m_isAttacking = true;
	m_attackState.OnEnter( this );// TODO: Reverse me

	// cheat a bit and give the bot the initial location of its victim
	m_lastEnemyPosition = victim->pev->origin;
	m_lastSawEnemyTimestamp = gpGlobals->time;
	m_aimSpreadTimestamp = gpGlobals->time;

	// compute the angle difference between where are looking, and where we need to look
	Vector toEnemy = victim->pev->origin - pev->origin;
	Vector idealAngle;

	idealAngle = UTIL_VecToAngles( toEnemy );

	float deltaYaw = (float)abs(m_lookYaw - idealAngle.y);

	while (deltaYaw > 180.0f)
		deltaYaw -= 360.0f;

	if (deltaYaw < 0.0f)
		deltaYaw = -deltaYaw;

	// immediately aim at enemy - accuracy penalty depending on how far we must turn to aim
	// accuracy is halved if we have to turn 180 degrees
	float turn = deltaYaw / 180.0f;
	float accuracy = GetProfile()->GetSkill() / (1.0f + turn);

	SetAimOffset( accuracy );

	// define time when aim offset will automatically be updated
	// longer time the more we had to turn (surprise)
	m_aimOffsetTimestamp = gpGlobals->time + RANDOM_FLOAT( 0.25f + turn, 1.5f );
}

/* <3b4416> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:366 */
NOBODY void CCSBot::StopAttacking(void)
{
//	Idle(CCSBot *const this);  //   374
}

/* <3b447d> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:378 */
bool CCSBot::IsAttacking(void) const
{
	return m_isAttacking;
}

/* <3b449f> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:387 */
NOBODY bool CCSBot::IsEscapingFromBomb(void) const
{
}

/* <3b44c6> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:399 */
NOBODY bool CCSBot::IsDefusingBomb(void) const
{
}

/* <3b44ed> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:411 */
bool CCSBot::IsHiding(void) const
{
	return (m_state == static_cast<const BotState *>( &m_hideState ));
}

/* <3b450f> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:423 */
bool CCSBot::IsAtHidingSpot(void) const
{
	if (!IsHiding())
		return false;

	return m_hideState.IsAtSpot();
}

/* <3b454a> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:435 */
NOBODY bool CCSBot::IsHunting(void) const
{
}

/* <3b4571> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:447 */
NOBODY bool CCSBot::IsMovingTo(void) const
{
}

/* <3b4598> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:460 */
NOBODY bool CCSBot::IsBuying(void) const
{
}

/* <3b45bf> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:472 */
NOBODY void CCSBot::MoveTo(const Vector *pos, RouteType route)
{
//	SetGoalPosition(MoveToState *const this,
//			const Vector *pos);  //   474
//	SetRouteType(MoveToState *const this,
//			enum RouteType route);  //   475
}

/* <3b463c> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:480 */
NOBODY void CCSBot::PlantBomb(void)
{
}

/* <3b4663> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:489 */
NOBODY void CCSBot::FetchBomb(void)
{
}

/* <3b468a> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:495 */
NOBODY void CCSBot::DefuseBomb(void)
{
}

/* <3b46b1> ../cstrike/dlls/bot/cs_bot_statemachine.cpp:504 */
NOBODY void CCSBot::InvestigateNoise(void)
{
}
