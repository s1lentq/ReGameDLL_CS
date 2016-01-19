#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

// 30 times per second, just like human clients
float g_flBotCommandInterval = 1.0 / 30.0;

// full AI only 10 times per second
float g_flBotFullThinkInterval = 1.0 / 10.0;

// Nasty Hack.  See client.cpp/ClientCommand()
const char *BotArgs[4] = { NULL };
bool UseBotArgs = false;

#else // HOOK_GAMEDLL

float g_flBotCommandInterval;
float g_flBotFullThinkInterval;

const char *BotArgs[4];
bool UseBotArgs;

#endif // HOOK_GAMEDLL

/* <48fed0> ../game_shared/bot/bot.cpp:28 */
CBot::CBot(void)
{
	// the profile will be attached after this instance is constructed
	m_profile = NULL;

	// assign this bot a unique ID
	static unsigned int nextID = 1;

	// wraparound (highly unlikely)
	if (nextID == 0)
		++nextID;

	m_id = nextID++;
	m_postureStackIndex = 0;
}

// Prepare bot for action

/* <48f6ef> ../game_shared/bot/bot.cpp:50 */
bool CBot::__MAKE_VHOOK(Initialize)(const BotProfile *profile)
{
	m_profile = profile;
	return true;
}

/* <48fbbd> ../game_shared/bot/bot.cpp:57 */
void CBot::__MAKE_VHOOK(Spawn)(void)
{
	// Let CBasePlayer set some things up
	CBasePlayer::Spawn();

	// Make sure everyone knows we are a bot
	pev->flags |= (FL_CLIENT | FL_FAKECLIENT);

	// Bots use their own thinking mechanism
	SetThink(NULL);
	pev->nextthink = -1;

	m_flNextBotThink = gpGlobals->time + g_flBotCommandInterval;
	m_flNextFullBotThink = gpGlobals->time + g_flBotFullThinkInterval;
	m_flPreviousCommandTime = gpGlobals->time;

	m_isRunning = true;
	m_isCrouching = false;
	m_postureStackIndex = 0;

	m_jumpTimestamp = 0.0f;

	// Command interface variable initialization
	ResetCommand();

	// Allow derived classes to setup at spawn time
	SpawnBot();
}

/* <48fa37> ../game_shared/bot/bot.cpp:88 */
Vector CBot::__MAKE_VHOOK(GetAutoaimVector)(float flDelta)
{
	UTIL_MakeVectors(pev->v_angle + pev->punchangle);
	return gpGlobals->v_forward;
}

/* <48ffa8> ../game_shared/bot/bot.cpp:97 */
void CBot::BotThink(void)
{
	if (gpGlobals->time >= m_flNextBotThink)
	{
		m_flNextBotThink = gpGlobals->time + g_flBotCommandInterval;

		Upkeep();

		if (gpGlobals->time >= m_flNextFullBotThink)
		{
			m_flNextFullBotThink = gpGlobals->time + g_flBotFullThinkInterval;

			ResetCommand();
			Update();
		}
		ExecuteCommand();
	}
}

/* <48f723> ../game_shared/bot/bot.cpp:119 */
void CBot::__MAKE_VHOOK(MoveForward)(void)
{
	m_forwardSpeed = GetMoveSpeed();
	m_buttonFlags |= IN_FORWARD;

	// make mutually exclusive
	m_buttonFlags &= ~IN_BACK;
}

/* <48f761> ../game_shared/bot/bot.cpp:130 */
void CBot::__MAKE_VHOOK(MoveBackward)(void)
{
	m_forwardSpeed = -GetMoveSpeed();
	m_buttonFlags |= IN_BACK;

	// make mutually exclusive
	m_buttonFlags &= ~IN_FORWARD;
}

/* <48f79f> ../game_shared/bot/bot.cpp:140 */
void CBot::__MAKE_VHOOK(StrafeLeft)(void)
{
	m_strafeSpeed = -GetMoveSpeed();
	m_buttonFlags |= IN_MOVELEFT;

	// make mutually exclusive
	m_buttonFlags &= ~IN_MOVERIGHT;
}

/* <48f7dd> ../game_shared/bot/bot.cpp:150 */
void CBot::__MAKE_VHOOK(StrafeRight)(void)
{
	m_strafeSpeed = GetMoveSpeed();
	m_buttonFlags |= IN_MOVERIGHT;

	// make mutually exclusive
	m_buttonFlags &= ~IN_MOVELEFT;
}

/* <48fe00> ../game_shared/bot/bot.cpp:160 */
bool CBot::__MAKE_VHOOK(Jump)(bool mustJump)
{
	if (IsJumping() || IsCrouching())
		return false;

	if (!mustJump)
	{
		const float minJumpInterval = 0.9f; // 1.5f;
		if (gpGlobals->time - m_jumpTimestamp < minJumpInterval)
			return false;
	}

	// still need sanity check for jumping frequency
	const float sanityInterval = 0.3f;
	if (gpGlobals->time - m_jumpTimestamp < sanityInterval)
		return false;

	// jump
	m_buttonFlags |= IN_JUMP;
	m_jumpTimestamp = gpGlobals->time;
	return true;
}

// Zero any MoveForward(), Jump(), etc

/* <48f81b> ../game_shared/bot/bot.cpp:187 */
void CBot::__MAKE_VHOOK(ClearMovement)(void)
{
	ResetCommand();
}

// Returns true if we are in the midst of a jump

/* <48ffe7> ../game_shared/bot/bot.cpp:196 */
bool CBot::IsJumping(void)
{
	// if long time after last jump, we can't be jumping
	if (gpGlobals->time - m_jumpTimestamp > 3.0f)
		return false;

	// if we just jumped, we're still jumping
	if (gpGlobals->time - m_jumpTimestamp < 1.0f)
		return true;

	// a little after our jump, we're jumping until we hit the ground
	if (pev->flags & FL_ONGROUND)
		return false;

	return true;
}

/* <48f859> ../game_shared/bot/bot.cpp:214 */
void CBot::__MAKE_VHOOK(Crouch)(void)
{
	m_isCrouching = true;
}

/* <48f87f> ../game_shared/bot/bot.cpp:220 */
void CBot::__MAKE_VHOOK(StandUp)(void)
{
	m_isCrouching = false;
}

/* <48f8a5> ../game_shared/bot/bot.cpp:227 */
void CBot::__MAKE_VHOOK(UseEnvironment)(void)
{
	m_buttonFlags |= IN_USE;
}

/* <48f8cb> ../game_shared/bot/bot.cpp:234 */
void CBot::__MAKE_VHOOK(PrimaryAttack)(void)
{
	m_buttonFlags |= IN_ATTACK;
}

/* <48f8f1> ../game_shared/bot/bot.cpp:240 */
void CBot::__MAKE_VHOOK(ClearPrimaryAttack)(void)
{
	m_buttonFlags &= ~IN_ATTACK;
}

/* <48f917> ../game_shared/bot/bot.cpp:246 */
void CBot::__MAKE_VHOOK(TogglePrimaryAttack)(void)
{
	if (m_buttonFlags & IN_ATTACK)
		m_buttonFlags &= ~IN_ATTACK;
	else
		m_buttonFlags |= IN_ATTACK;
}

/* <48f93d> ../game_shared/bot/bot.cpp:260 */
void CBot::__MAKE_VHOOK(SecondaryAttack)(void)
{
	m_buttonFlags |= IN_ATTACK2;
}

/* <48f963> ../game_shared/bot/bot.cpp:266 */
void CBot::__MAKE_VHOOK(Reload)(void)
{
	m_buttonFlags |= IN_RELOAD;
}

// Returns ratio of ammo left to max ammo (1 = full clip, 0 = empty)

/* <490008> ../game_shared/bot/bot.cpp:275 */
float CBot::GetActiveWeaponAmmoRatio(void) const
{
	CBasePlayerWeapon *weapon = GetActiveWeapon();

	if (!weapon)
		return 0.0f;

	// weapons with no ammo are always full
	if (weapon->m_iClip < 0)
		return 1.0f;

	return (float)weapon->m_iClip / (float)weapon->iMaxClip();
}

// Return true if active weapon has an empty clip

/* <490058> ../game_shared/bot/bot.cpp:293 */
bool CBot::IsActiveWeaponClipEmpty(void) const
{
	CBasePlayerWeapon *weapon = GetActiveWeapon();

	if (weapon != NULL && weapon->m_iClip == 0)
		return true;

	return false;
}

// Return true if active weapon has no ammo at all

/* <490096> ../game_shared/bot/bot.cpp:307 */
bool CBot::IsActiveWeaponOutOfAmmo(void) const
{
	CBasePlayerWeapon *gun = GetActiveWeapon();

	if (gun == NULL)
		return true;

	if (gun->m_iClip < 0)
		return false;

	if (gun->m_iClip == 0 && m_rgAmmo[ gun->m_iPrimaryAmmoType ] <= 0)
		return true;

	return false;
}

// Return true if looking thru weapon's scope

/* <4900d4> ../game_shared/bot/bot.cpp:327 */
bool CBot::IsUsingScope(void) const
{
	// if our field of view is less than 90, we're looking thru a scope (maybe only true for CS...)
	if (m_iFOV < 90.0f)
		return true;

	return false;
}

/* <48f989> ../game_shared/bot/bot.cpp:338 */
void CBot::__MAKE_VHOOK(ExecuteCommand)(void)
{
	byte adjustedMSec;

	// Adjust msec to command time interval
	adjustedMSec = ThrottledMsec();

	// player model is "munged"
	pev->angles = pev->v_angle;
	pev->angles.x /= -3.0f;

	// save the command time
	m_flPreviousCommandTime = gpGlobals->time;

	if (IsCrouching())
	{
		m_buttonFlags |= IN_DUCK;
	}

	// Run the command
	PLAYER_RUN_MOVE(edict(), pev->v_angle, m_forwardSpeed, m_strafeSpeed, m_verticalSpeed, m_buttonFlags, 0, adjustedMSec);
}

/* <4900fa> ../game_shared/bot/bot.cpp:362 */
void CBot::ResetCommand(void)
{
	m_forwardSpeed = 0.0f;
	m_strafeSpeed = 0.0f;
	m_verticalSpeed = 0.0f;
	m_buttonFlags = 0;
}

/* <49011b> ../game_shared/bot/bot.cpp:372 */
byte CBot::ThrottledMsec(void) const
{
	int iNewMsec;

	// Estimate Msec to use for this command based on time passed from the previous command
	iNewMsec = (int)((gpGlobals->time - m_flPreviousCommandTime) * 1000);

	// Doh, bots are going to be slower than they should if this happens.
	// Upgrade that CPU or use less bots!
	if (iNewMsec > 255)
		iNewMsec = 255;

	return (byte)iNewMsec;
}

// Do a "client command" - useful for invoking menu choices, etc.

/* <49016e> ../game_shared/bot/bot.cpp:389 */
void CBot::ClientCommand(const char *cmd, const char *arg1, const char *arg2, const char *arg3)
{
	BotArgs[0] = cmd;
	BotArgs[1] = arg1;
	BotArgs[2] = arg2;
	BotArgs[3] = arg3;

	UseBotArgs = true;
	::ClientCommand(ENT(pev));
	UseBotArgs = false;
}

// Returns TRUE if given entity is our enemy

/* <4901ac> ../game_shared/bot/bot.cpp:410 */
bool CBot::IsEnemy(CBaseEntity *ent) const
{
	// only Players (real and AI) can be enemies
	if (!ent->IsPlayer())
		return false;

	// corpses are no threat
	if (!ent->IsAlive())
		return false;

	CBasePlayer *player = static_cast<CBasePlayer *>(ent);

	// if they are on our team, they are our friends
	if (player->m_iTeam == m_iTeam)
		return false;

	// yep, we hate 'em
	return true;
}

// Return number of enemies left alive

/* <49021a> ../game_shared/bot/bot.cpp:434 */
int CBot::GetEnemiesRemaining(void) const
{
	int count = 0;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBaseEntity *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (!IsEnemy(player))
			continue;

		if (!player->IsAlive())
			continue;

		count++;
	}

	return count;
}

// Return number of friends left alive

/* <490338> ../game_shared/bot/bot.cpp:467 */
int CBot::GetFriendsRemaining(void) const
{
	int count = 0;

	for (int i = 1; i <= gpGlobals->maxClients; ++i)
	{
		CBaseEntity *player = UTIL_PlayerByIndex(i);

		if (player == NULL)
			continue;

		if (FNullEnt(player->pev))
			continue;

		if (FStrEq(STRING(player->pev->netname), ""))
			continue;

		if (IsEnemy(player))
			continue;

		if (!player->IsAlive())
			continue;

		if (player == static_cast<CBaseEntity *>(const_cast<CBot *>(this)))
			continue;

		count++;
	}

	return count;
}

/* <490489> ../game_shared/bot/bot.cpp:503 */
bool CBot::IsLocalPlayerWatchingMe(void) const
{
	// avoid crash during spawn
	if (pev == NULL)
		return false;

	int myIndex = const_cast<CBot *>(this)->entindex();

	CBasePlayer *player = UTIL_GetLocalPlayer();
	if (player == NULL)
		return false;

	if ((player->pev->flags & FL_SPECTATOR || player->m_iTeam == SPECTATOR) && player->pev->iuser2 == myIndex)
	{
		switch (player->pev->iuser1)
		{
			case OBS_CHASE_LOCKED:
			case OBS_CHASE_FREE:
			case OBS_IN_EYE:
				return true;
		}
	}

	return false;
}

/* <4904f2> ../game_shared/bot/bot.cpp:536 */
NOXREF void CBot::Print(char *format, ...) const
{
	va_list varg;
	char buffer[1024];

	// prefix the message with the bot's name
	Q_sprintf(buffer, "%s: ", STRING(pev->netname));
	SERVER_PRINT(buffer);

	va_start(varg, format);
	vsprintf(buffer, format, varg);
	va_end(varg);

	SERVER_PRINT(buffer);
}

/* <490561> ../game_shared/bot/bot.cpp:557 */
void CBot::PrintIfWatched(char *format, ...) const
{
	if (!cv_bot_debug.value)
		return;

	if ((IsLocalPlayerWatchingMe() && (cv_bot_debug.value == 1 || cv_bot_debug.value == 3))
		|| (cv_bot_debug.value == 2 || cv_bot_debug.value == 4))
	{
		va_list varg;
		char buffer[1024];

		// prefix the message with the bot's name (this can be NULL if bot was just added)
		const char *name;
		if (pev == NULL)
			name = "(NULL pev)";
		else
			name = STRING(pev->netname);

		Q_sprintf(buffer, "%s: ", (name != NULL) ? name : "(NULL netname)");

		SERVER_PRINT(buffer);

		va_start(varg, format);
		vsprintf(buffer, format, varg);
		va_end(varg);

		SERVER_PRINT(buffer);
	}
}

/* <49066c> ../game_shared/bot/bot.cpp:588 */
ActiveGrenade::ActiveGrenade(int weaponID, CGrenade *grenadeEntity)
{
	m_id = weaponID;
	m_entity = grenadeEntity;
	m_detonationPosition = grenadeEntity->pev->origin;
	m_dieTimestamp = 0;
}

/* <49069d> ../game_shared/bot/bot.cpp:597 */
void ActiveGrenade::OnEntityGone(void)
{
	if (m_id == WEAPON_SMOKEGRENADE)
	{
		// smoke lingers after grenade is gone
		const float smokeLingerTime = 4.0f;
		m_dieTimestamp = gpGlobals->time + smokeLingerTime;
	}

	m_entity = NULL;
}

/* <4906e1> ../game_shared/bot/bot.cpp:610 */
bool ActiveGrenade::IsValid(void) const
{
	if (!m_entity)
	{
		if (gpGlobals->time > m_dieTimestamp)
			return false;
	}
	return true;
}

/* <490710> ../game_shared/bot/bot.cpp:622 */
const Vector *ActiveGrenade::GetPosition(void) const
{
	return &m_entity->pev->origin;
}

#ifdef HOOK_GAMEDLL

void CBot::Spawn(void)
{
	Spawn_();
}

Vector CBot::GetAutoaimVector(float flDelta)
{
	return GetAutoaimVector_(flDelta);
}

bool CBot::Initialize(const BotProfile *profile)
{
	return Initialize_(profile);
}

void CBot::Crouch(void)
{
	Crouch_();
}

void CBot::StandUp(void)
{
	StandUp_();
}

void CBot::MoveForward(void)
{
	MoveForward_();
}

void CBot::MoveBackward(void)
{
	MoveBackward_();
}

void CBot::StrafeLeft(void)
{
	StrafeLeft_();
}

void CBot::StrafeRight(void)
{
	StrafeRight_();
}

bool CBot::Jump(bool mustJump)
{
	return Jump_(mustJump);
}

void CBot::ClearMovement(void)
{
	ClearMovement_();
}

void CBot::UseEnvironment(void)
{
	UseEnvironment_();
}

void CBot::PrimaryAttack(void)
{
	PrimaryAttack_();
}

void CBot::ClearPrimaryAttack(void)
{
	ClearPrimaryAttack_();
}

void CBot::TogglePrimaryAttack(void)
{
	TogglePrimaryAttack_();
}

void CBot::SecondaryAttack(void)
{
	SecondaryAttack_();
}

void CBot::Reload(void)
{
	Reload_();
}

void CBot::ExecuteCommand(void)
{
	ExecuteCommand_();
}

#endif // HOOK_GAMEDLL
