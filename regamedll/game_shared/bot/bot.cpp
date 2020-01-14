#include "precompiled.h"

// Nasty Hack.  See client.cpp/ClientCommand()
const char *BotArgs[4] = {};
bool UseBotArgs = false;

CBot::CBot()
{
	// the profile will be attached after this instance is constructed
	m_profile = nullptr;

	// assign this bot a unique ID
	static unsigned int nextID = 1;

	// wraparound (highly unlikely)
	if (nextID == 0)
		++nextID;

	m_id = nextID++;
	m_postureStackIndex = 0;
}

// Prepare bot for action
bool CBot::Initialize(const BotProfile *profile)
{
	m_profile = profile;
	return true;
}

void CBot::Spawn()
{
	// Let CBasePlayer set some things up
	CBasePlayer::Spawn();

	// Make sure everyone knows we are a bot
	pev->flags |= (FL_CLIENT | FL_FAKECLIENT);

	// Bots use their own thinking mechanism
	SetThink(nullptr);
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

Vector CBot::GetAutoaimVector(float flDelta)
{
	UTIL_MakeVectors(pev->v_angle + pev->punchangle);
	return gpGlobals->v_forward;
}

void CBot::BotThink()
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

void CBot::MoveForward()
{
	m_forwardSpeed = GetMoveSpeed();
	m_buttonFlags |= IN_FORWARD;

	// make mutually exclusive
	m_buttonFlags &= ~IN_BACK;
}

void CBot::MoveBackward()
{
	m_forwardSpeed = -GetMoveSpeed();
	m_buttonFlags |= IN_BACK;

	// make mutually exclusive
	m_buttonFlags &= ~IN_FORWARD;
}

void CBot::StrafeLeft()
{
	m_strafeSpeed = -GetMoveSpeed();
	m_buttonFlags |= IN_MOVELEFT;

	// make mutually exclusive
	m_buttonFlags &= ~IN_MOVERIGHT;
}

void CBot::StrafeRight()
{
	m_strafeSpeed = GetMoveSpeed();
	m_buttonFlags |= IN_MOVERIGHT;

	// make mutually exclusive
	m_buttonFlags &= ~IN_MOVELEFT;
}

bool CBot::Jump(bool mustJump)
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
void CBot::ClearMovement()
{
	ResetCommand();
}

// Returns true if we are in the midst of a jump
bool CBot::IsJumping()
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

void CBot::Crouch()
{
	m_isCrouching = true;
}

void CBot::StandUp()
{
	m_isCrouching = false;
}

void CBot::UseEnvironment()
{
	m_buttonFlags |= IN_USE;
}

void CBot::PrimaryAttack()
{
	m_buttonFlags |= IN_ATTACK;
}

void CBot::ClearPrimaryAttack()
{
	m_buttonFlags &= ~IN_ATTACK;
}

void CBot::TogglePrimaryAttack()
{
	m_buttonFlags ^= IN_ATTACK;
}

void CBot::SecondaryAttack()
{
	m_buttonFlags |= IN_ATTACK2;
}

void CBot::Reload()
{
	m_buttonFlags |= IN_RELOAD;
}

// Returns ratio of ammo left to max ammo (1 = full clip, 0 = empty)
float CBot::GetActiveWeaponAmmoRatio() const
{
	CBasePlayerWeapon *pCurrentWeapon = GetActiveWeapon();
	if (!pCurrentWeapon)
		return 0.0f;

	// Weapons with no ammo are always full
	if (pCurrentWeapon->m_iClip < 0)
		return 1.0f;

	return float(pCurrentWeapon->m_iClip) / float(pCurrentWeapon->iMaxClip());
}

// Return true if active weapon has an empty clip
bool CBot::IsActiveWeaponClipEmpty() const
{
	CBasePlayerWeapon *pCurrentWeapon = GetActiveWeapon();
	if (pCurrentWeapon && pCurrentWeapon->m_iClip == 0)
		return true;

	return false;
}

// Return true if active weapon has no ammo at all
bool CBot::IsActiveWeaponOutOfAmmo() const
{
	CBasePlayerWeapon *pCurrentWeapon = GetActiveWeapon();
	if (!pCurrentWeapon)
		return true;

	if (pCurrentWeapon->m_iClip < 0)
		return false;

	if (pCurrentWeapon->m_iClip == 0 && m_rgAmmo[pCurrentWeapon->m_iPrimaryAmmoType] <= 0)
		return true;

	return false;
}

// Return true if looking thru weapon's scope
bool CBot::IsUsingScope() const
{
	// if our field of view is less than 90, we're looking thru a scope (maybe only true for CS...)
	if (m_iFOV < 90.0f)
		return true;

	return false;
}

void CBot::ExecuteCommand()
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

#ifdef REGAMEDLL_FIXES
	// don't move if frozen state present
	if (pev->flags & FL_FROZEN)
	{
		adjustedMSec = 0;
		ResetCommand();
	}
#endif

	// Run the command
	PLAYER_RUN_MOVE(edict(), pev->v_angle, m_forwardSpeed, m_strafeSpeed, m_verticalSpeed, m_buttonFlags, 0, adjustedMSec);
}

void CBot::ResetCommand()
{
	m_forwardSpeed = 0.0f;
	m_strafeSpeed = 0.0f;
	m_verticalSpeed = 0.0f;
	m_buttonFlags = 0;
}

byte CBot::ThrottledMsec() const
{
	int iNewMsec;

	// Estimate Msec to use for this command based on time passed from the previous command
	iNewMsec = int((gpGlobals->time - m_flPreviousCommandTime) * 1000);

	// Doh, bots are going to be slower than they should if this happens.
	// Upgrade that CPU or use less bots!
	if (iNewMsec > 255)
		iNewMsec = 255;

	return byte(iNewMsec);
}

#ifndef REGAMEDLL_FIXES
// Do a "client command" - useful for invoking menu choices, etc.
void CBot::ClientCommand(const char *cmd, const char *arg1, const char *arg2, const char *arg3)
{
	BotArgs[0] = cmd;
	BotArgs[1] = arg1;
	BotArgs[2] = arg2;
	BotArgs[3] = arg3;

	UseBotArgs = true;
	::ClientCommand_(ENT(pev));
	UseBotArgs = false;
}
#endif

// Returns TRUE if given entity is our enemy
bool CBot::IsEnemy(CBaseEntity *pEntity) const
{
	// only Players (real and AI) can be enemies
	if (!pEntity->IsPlayer())
		return false;

	// corpses are no threat
	if (!pEntity->IsAlive())
		return false;

	CBasePlayer *pPlayer = static_cast<CBasePlayer *>(pEntity);

	// if they are on our team, they are our friends
	if (BotRelationship(pPlayer) == BOT_TEAMMATE)
		return false;

	// yep, we hate 'em
	return true;
}

// Return number of enemies left alive
int CBot::GetEnemiesRemaining() const
{
	int count = 0;
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (!pPlayer)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (FStrEq(STRING(pPlayer->pev->netname), ""))
			continue;

		if (!IsEnemy(pPlayer))
			continue;

		if (!pPlayer->IsAlive())
			continue;

		count++;
	}

	return count;
}

// Return number of friends left alive
int CBot::GetFriendsRemaining() const
{
	int count = 0;
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBaseEntity *pPlayer = UTIL_PlayerByIndex(i);
		if (!pPlayer)
			continue;

		if (FNullEnt(pPlayer->pev))
			continue;

		if (FStrEq(STRING(pPlayer->pev->netname), ""))
			continue;

		if (IsEnemy(pPlayer))
			continue;

		if (!pPlayer->IsAlive())
			continue;

		if (pPlayer == static_cast<CBaseEntity *>(const_cast<CBot *>(this)))
			continue;

		count++;
	}

	return count;
}

bool CBot::IsLocalPlayerWatchingMe() const
{
	// avoid crash during spawn
	if (!pev)
		return false;

	int myIndex = const_cast<CBot *>(this)->entindex();

	CBasePlayer *pPlayer = UTIL_GetLocalPlayer();
	if (!pPlayer)
		return false;

	if (((pPlayer->pev->flags & FL_SPECTATOR) || pPlayer->m_iTeam == SPECTATOR) && pPlayer->pev->iuser2 == myIndex)
	{
		switch (pPlayer->pev->iuser1)
		{
		case OBS_CHASE_LOCKED:
		case OBS_CHASE_FREE:
		case OBS_IN_EYE:
			return true;
		}
	}

	return false;
}

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
		const char *name = pev ? STRING(pev->netname) : "(NULL pev)";
		Q_sprintf(buffer, "%s: ", name ? name : "(NULL netname)");

		SERVER_PRINT(buffer);

		va_start(varg, format);
		vsprintf(buffer, format, varg);
		va_end(varg);

		SERVER_PRINT(buffer);
	}
}

ActiveGrenade::ActiveGrenade(int weaponID, CGrenade *grenadeEntity)
{
	m_id = weaponID;
	m_entity = grenadeEntity;
	m_detonationPosition = grenadeEntity->pev->origin;
	m_dieTimestamp = 0;
}

void ActiveGrenade::OnEntityGone()
{
	if (m_id == WEAPON_SMOKEGRENADE)
	{
		// smoke lingers after grenade is gone
		const float smokeLingerTime = 4.0f;
		m_dieTimestamp = gpGlobals->time + smokeLingerTime;
	}

	m_entity = nullptr;
}

bool ActiveGrenade::IsValid() const
{
	if (!m_entity)
	{
		if (gpGlobals->time > m_dieTimestamp)
			return false;
	}

	return true;
}

const Vector *ActiveGrenade::GetPosition() const
{
	return &m_entity->pev->origin;
}
