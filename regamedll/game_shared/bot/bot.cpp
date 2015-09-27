#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

// 30 times per second, just like human clients
float g_flBotCommandInterval = 1.0 / 30.0;

// full AI only 10 times per second
float g_flBotFullThinkInterval = 1.0 / 10.0;

const char *BotArgs[4] = { NULL };
bool UseBotArgs = false;

#else // HOOK_GAMEDLL

float g_flBotCommandInterval;
float g_flBotFullThinkInterval;

const char *BotArgs[4];
bool UseBotArgs;

#endif // HOOK_GAMEDLL

/* <48fed0> ../game_shared/bot/bot.cpp:28 */
NOBODY CBot::CBot(void)
{
//	CBasePlayer(CBasePlayer *const this);  //    28
//	{
//		unsigned int nextID;                                  //    34
//	}
}

/* <48f6ef> ../game_shared/bot/bot.cpp:50 */
bool CBot::__MAKE_VHOOK(Initialize)(const BotProfile *profile)
{
	m_profile = profile;
	return true;
}

/* <48fbbd> ../game_shared/bot/bot.cpp:57 */
NOBODY void CBot::__MAKE_VHOOK(Spawn)(void)
{
//	ResetCommand(CBot *const this);  //    80
}

/* <48fa37> ../game_shared/bot/bot.cpp:88 */
NOBODY Vector CBot::__MAKE_VHOOK(GetAutoaimVector)(float flDelta)
{
//	operator+(const Vector *const this,
//			const Vector &v);  //    90
//	Vector(Vector *const this,
//		const Vector &v);  //    92
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
NOBODY void CBot::__MAKE_VHOOK(MoveForward)(void)
{
//	GetMoveSpeed(CBot *const this);  //   121
}

/* <48f761> ../game_shared/bot/bot.cpp:130 */
NOBODY void CBot::__MAKE_VHOOK(MoveBackward)(void)
{
//	GetMoveSpeed(CBot *const this);  //   132
}

/* <48f79f> ../game_shared/bot/bot.cpp:140 */
NOBODY void CBot::__MAKE_VHOOK(StrafeLeft)(void)
{
//	GetMoveSpeed(CBot *const this);  //   142
}

/* <48f7dd> ../game_shared/bot/bot.cpp:150 */
NOBODY void CBot::__MAKE_VHOOK(StrafeRight)(void)
{
//	GetMoveSpeed(CBot *const this);  //   152
}

/* <48fe00> ../game_shared/bot/bot.cpp:160 */
NOBODY bool CBot::__MAKE_VHOOK(Jump)(bool mustJump)
{
//	{
//		float const sanityInterval;                            //   173
//		IsJumping(CBot *const this);  //   162
//		{
//			float const minJumpInterval;                   //   167
//		}
//	}
//	Jump(CBot *const this,
//		bool mustJump);  //   160
}

/* <48f81b> ../game_shared/bot/bot.cpp:187 */
NOBODY void CBot::__MAKE_VHOOK(ClearMovement)(void)
{
//	ResetCommand(CBot *const this);  //   189
}

/* <48ffe7> ../game_shared/bot/bot.cpp:196 */
NOBODY bool CBot::IsJumping(void)
{
}

/* <48f859> ../game_shared/bot/bot.cpp:214 */
NOBODY void CBot::__MAKE_VHOOK(Crouch)(void)
{
}

/* <48f87f> ../game_shared/bot/bot.cpp:220 */
NOBODY void CBot::__MAKE_VHOOK(StandUp)(void)
{
}

/* <48f8a5> ../game_shared/bot/bot.cpp:227 */
NOBODY void CBot::__MAKE_VHOOK(UseEnvironment)(void)
{
}

/* <48f8cb> ../game_shared/bot/bot.cpp:234 */
NOBODY void CBot::__MAKE_VHOOK(PrimaryAttack)(void)
{
}

/* <48f8f1> ../game_shared/bot/bot.cpp:240 */
NOBODY void CBot::__MAKE_VHOOK(ClearPrimaryAttack)(void)
{
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
NOBODY void CBot::__MAKE_VHOOK(SecondaryAttack)(void)
{
}

/* <48f963> ../game_shared/bot/bot.cpp:266 */
NOBODY void CBot::__MAKE_VHOOK(Reload)(void)
{
}

/* <490008> ../game_shared/bot/bot.cpp:275 */
NOBODY float CBot::GetActiveWeaponAmmoRatio(void) const
{
//	{
//		class CBasePlayerWeapon *gun;                        //   277
//		iMaxClip(CBasePlayerItem *const this);  //   286
//	}
}

/* <490058> ../game_shared/bot/bot.cpp:293 */
NOBODY bool CBot::IsActiveWeaponClipEmpty(void) const
{
//	{
//		class CBasePlayerWeapon *gun;                        //   295
//	}
}

/* <490096> ../game_shared/bot/bot.cpp:307 */
NOBODY bool CBot::IsActiveWeaponOutOfAmmo(void) const
{
//	{
//		class CBasePlayerWeapon *gun;                        //   309
//	}
}

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
NOXREF void CBot::ResetCommand(void)
{
	m_forwardSpeed = 0.0f;
	m_strafeSpeed = 0.0f;
	m_verticalSpeed = 0.0f;
	m_buttonFlags = 0;
}

/* <49011b> ../game_shared/bot/bot.cpp:372 */
NOXREF byte CBot::ThrottledMsec(void) const
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

/* <4901ac> ../game_shared/bot/bot.cpp:410 */
NOBODY bool CBot::IsEnemy(CBaseEntity *ent) const
{
//	{
//		class CBasePlayer *player;                           //   420
//	}
//	IsEnemy(const class CBot *const this,
//		class CBaseEntity *ent);  //   410
}

/* <49021a> ../game_shared/bot/bot.cpp:434 */
NOBODY int CBot::GetEnemiesRemaining(void) const
{
//	{
//		int count;                                            //   436
//		{
//			int i;                                        //   438
//			{
//				class CBaseEntity *player;           //   440
//				FNullEnt(entvars_t *pev);  //   445
//				IsEnemy(const class CBot *const this,
//					class CBaseEntity *ent);  //   451
//			}
//		}
//	}
}

/* <490338> ../game_shared/bot/bot.cpp:467 */
NOBODY int CBot::GetFriendsRemaining(void) const
{
//	{
//		int count;                                            //   469
//		{
//			int i;                                        //   471
//			{
//				class CBaseEntity *player;           //   473
//				FNullEnt(entvars_t *pev);  //   478
//				IsEnemy(const class CBot *const this,
//					class CBaseEntity *ent);  //   484
//			}
//		}
//	}
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
NOXREF const Vector *ActiveGrenade::GetPosition(void) const
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
