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

#ifndef BOT_H
#define BOT_H
#ifdef _WIN32
#pragma once
#endif

#ifdef HOOK_GAMEDLL

#define g_flBotCommandInterval (*pg_flBotCommandInterval)
#define g_flBotFullThinkInterval (*pg_flBotFullThinkInterval)

#define BotArgs (*pBotArgs)
#define UseBotArgs (*pUseBotArgs)

#endif // HOOK_GAMEDLL

extern float g_flBotCommandInterval;
extern float g_flBotFullThinkInterval;

extern const char *BotArgs[4];
extern bool UseBotArgs;

class BotProfile;

/* <36c175> ../game_shared/bot/bot.h:36 */
template <class T>
T *CreateBot(const BotProfile *profile)
{
	edict_t *pentBot;
	if (UTIL_ClientsInGame() >= gpGlobals->maxClients)
	{
		CONSOLE_ECHO( "Unable to create bot: Server is full (%d/%d clients).\n", UTIL_ClientsInGame(), gpGlobals->maxClients);
		return NULL;
	}

	char netname[64];
	UTIL_ConstructBotNetName(netname, sizeof(netname), profile);
	pentBot = CREATE_FAKE_CLIENT(netname);

	if (FNullEnt(pentBot))
	{
		CONSOLE_ECHO("Unable to create bot: pfnCreateFakeClient() returned null.\n");
		return NULL;
	}
	else
	{
		T *pBot = NULL;
		FREE_PRIVATE(pentBot);
		pBot = GetClassPtr((T *)VARS(pentBot));
		pBot->Initialize(profile);

		return pBot;
	}
}

// The base bot class from which bots for specific games are derived
class CBot: public CBasePlayer 
{
public:
	// constructor initializes all values to zero
	CBot(void);

	NOBODY virtual void Spawn(void);

	// invoked when injured by something
	virtual int TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
	{
		return CBasePlayer::TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType);
	}
	// invoked when killed
	virtual void Killed(entvars_t *pevAttacker, int iGib)
	{
		CBasePlayer::Killed(pevAttacker, iGib);
	}
	NOBODY virtual void Think(void) { };
	virtual BOOL IsBot(void)
	{
		return true;
	}
	NOBODY virtual Vector GetAutoaimVector(float flDelta);
	// invoked when in contact with a CWeaponBox
	NOBODY virtual void OnTouchingWeapon(CWeaponBox *box) {}
	NOBODY virtual bool Initialize(const BotProfile *profile);

	virtual void SpawnBot(void) = 0;

	// lightweight maintenance, invoked frequently
	virtual void Upkeep(void) = 0;

	// heavyweight algorithms, invoked less often
	virtual void Update(void) = 0;

	NOBODY virtual void Run(void);
	NOBODY virtual void Walk(void);
	NOBODY virtual void Crouch(void);
	NOBODY virtual void StandUp(void);
	NOBODY virtual void MoveForward(void);
	NOBODY virtual void MoveBackward(void);
	NOBODY virtual void StrafeLeft(void);
	NOBODY virtual void StrafeRight(void);

	// returns true if jump was started
	NOBODY virtual bool Jump(bool mustJump = false);

	// zero any MoveForward(), Jump(), etc
	NOBODY virtual void ClearMovement(void);

	// Weapon interface
	NOBODY virtual void UseEnvironment(void);
	NOBODY virtual void PrimaryAttack(void);
	NOBODY virtual void ClearPrimaryAttack(void);
	virtual void TogglePrimaryAttack(void);
	NOBODY virtual void SecondaryAttack(void);
	NOBODY virtual void Reload(void);

	// invoked when event occurs in the game (some events have NULL entities)
	virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL) { };

	// return true if we can see the point
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;

	// return true if we can see any part of the player
	virtual bool IsVisible(CBasePlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const = 0;

	enum VisiblePartType
	{
		NONE = 0x00,
		CHEST = 0x01,
		HEAD = 0x02,
		LEFT_SIDE = 0x04,	// the left side of the object from our point of view (not their left side)
		RIGHT_SIDE = 0x08,	// the right side of the object from our point of view (not their right side)
		FEET = 0x10
	};

	// if enemy is visible, return the part we see
	virtual bool IsEnemyPartVisible(VisiblePartType part) const = 0;

	// return true if player is facing towards us
	NOBODY virtual bool IsPlayerFacingMe(CBasePlayer *other) const;
	
	// returns true if other player is pointing right at us
	NOBODY virtual bool IsPlayerLookingAtMe(CBasePlayer *other) const;
	virtual void ExecuteCommand(void);
	NOBODY virtual void SetModel(const char *modelName);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	Vector GetAutoaimVector_(float flDelta);
	bool Initialize_(const BotProfile *profile);
	void Crouch_(void);
	void StandUp_(void);
	void MoveForward_(void);
	void MoveBackward_(void);
	void StrafeLeft_(void);
	void StrafeRight_(void);
	bool Jump_(bool mustJump = false);
	void ClearMovement_(void);
	void UseEnvironment_(void);
	void PrimaryAttack_(void);
	void ClearPrimaryAttack_(void);
	void TogglePrimaryAttack_(void);
	void SecondaryAttack_(void);
	void Reload_(void);
	void ExecuteCommand_(void);

#endif // HOOK_GAMEDLL

public:
	unsigned int GetID(void) const
	{
		return m_id;
	}
	bool IsRunning(void) const
	{
		return m_isRunning;
	}
	bool IsCrouching(void) const
	{
		return m_isCrouching;
	}

	// push the current posture context onto the top of the stack
	void PushPostureContext(void);

	// restore the posture context to the next context on the stack
	void PopPostureContext(void);
	NOBODY bool IsJumping(void);

	// return time last jump began
	float GetJumpTimestamp(void) const
	{
		return m_jumpTimestamp;
	}
	// returns ratio of ammo left to max ammo (1 = full clip, 0 = empty)
	NOBODY float GetActiveWeaponAmmoRatio(void) const;

	// return true if active weapon has any empty clip
	NOBODY bool IsActiveWeaponClipEmpty(void) const;

	// return true if active weapon has no ammo at all
	NOBODY bool IsActiveWeaponOutOfAmmo(void) const;

	// is the weapon in the middle of a reload
	bool IsActiveWeaponReloading(void) const;

	// return true if active weapon's bullet spray has become large and inaccurate
	bool IsActiveWeaponRecoilHigh(void) const;

	// return the weapon the bot is currently using
	CBasePlayerWeapon *GetActiveWeapon(void) const;

	// return true if looking thru weapon's scope
	bool IsUsingScope(void) const;

	// returns TRUE if given entity is our enemy
	NOBODY bool IsEnemy(CBaseEntity *ent) const;

	// return number of enemies left alive
	NOBODY int GetEnemiesRemaining(void) const;

	// return number of friends left alive
	NOBODY int GetFriendsRemaining(void) const;

	// return true if local player is observing this bot
	bool IsLocalPlayerWatchingMe(void) const;

	// output message to console
	NOXREF void Print(char *format,...) const;

	// output message to console if we are being watched by the local player
	void PrintIfWatched(char *format,...) const;

	void BotThink(void);
	bool IsNetClient(void) const
	{
		return false;
	}
	int Save(CSave &save) const;
	int Restore(CRestore &restor) const;

	// return our personality profile
	const BotProfile *GetProfile(void) const
	{
		return m_profile;
	}
#ifndef HOOK_GAMEDLL
protected:
#endif // HOOK_GAMEDLL
	// Do a "client command" - useful for invoking menu choices, etc.
	void ClientCommand(const char *cmd, const char *arg1 = NULL, const char *arg2 = NULL, const char *arg3 = NULL);

	// the "personality" profile of this bot
	const BotProfile *m_profile;
private:

	NOXREF void ResetCommand(void);
	NOXREF byte ThrottledMsec(void) const;

	// returns current movement speed (for walk/run)
	float GetMoveSpeed(void);

	// unique bot ID
	unsigned int m_id;

	// Think mechanism variables
	float m_flNextBotThink;
	float m_flNextFullBotThink;

	// Command interface variables
	float m_flPreviousCommandTime;

	// run/walk mode
	bool m_isRunning;

	// true if crouching (ducking)
	bool m_isCrouching;
	float m_forwardSpeed;
	float m_strafeSpeed;
	float m_verticalSpeed;

	// bitfield of movement buttons
	unsigned short m_buttonFlags;

	// time when we last began a jump
	float m_jumpTimestamp;

	// the PostureContext represents the current settings of walking and crouching
	struct PostureContext
	{
		bool isRunning;
		bool isCrouching;
	};

	enum { MAX_POSTURE_STACK = 8 };
	PostureContext m_postureStack[MAX_POSTURE_STACK];

	// index of top of stack
	int m_postureStackIndex;

};/* size: 2564, cachelines: 41, members: 15 */

/* <48f61d> ../game_shared/bot/bot.h:253 */
inline void CBot::SetModel(const char *modelName)
{
	SET_CLIENT_KEY_VALUE(entindex(), GET_INFO_BUFFER(edict()), "model", (char *)modelName);
}

/* <48e98a> ../game_shared/bot/bot.h:259 */
inline float CBot::GetMoveSpeed(void)
{
	if (m_isRunning || m_isCrouching)
		return pev->maxspeed;

	return 0.4f * pev->maxspeed;
}

/* <48f6a3> ../game_shared/bot/bot.h:269 */
inline void CBot::Run(void)
{
	m_isRunning = true;
}

/* <48f6c9> ../game_shared/bot/bot.h:275 */
inline void CBot::Walk(void)
{
	m_isRunning = false;
}

/* <5d3ed6> ../game_shared/bot/bot.h:281 */
inline CBasePlayerWeapon *CBot::GetActiveWeapon(void) const
{
	return static_cast<CBasePlayerWeapon *>(m_pActiveItem);
}

/* <5c4d70> ../game_shared/bot/bot.h:287 */
inline bool CBot::IsActiveWeaponReloading(void) const
{
	CBasePlayerWeapon *gun = GetActiveWeapon();
	if (gun == NULL)
		return false;

	return (gun->m_fInReload || gun->m_fInSpecialReload) != 0;
}

/* <3c5c5c> ../game_shared/bot/bot.h:297 */
inline bool CBot::IsActiveWeaponRecoilHigh(void) const
{
	CBasePlayerWeapon *gun = GetActiveWeapon();
	if (gun != NULL)
	{
		const float highRecoil = 0.4f;
		return (gun->m_flAccuracy > highRecoil) != 0;
	}
	return false;
}

/* <5194b2> ../game_shared/bot/bot.h:308 */
inline void CBot::PushPostureContext(void)
{
	if (m_postureStackIndex == MAX_POSTURE_STACK)
	{
		if (pev)
			PrintIfWatched("PushPostureContext() overflow error!\n");
		return;
	}
	m_postureStack[m_postureStackIndex].isRunning = m_isRunning;
	m_postureStack[m_postureStackIndex].isCrouching = m_isCrouching;
	++m_postureStackIndex;
}

/* <519534> ../game_shared/bot/bot.h:323 */
inline void CBot::PopPostureContext(void)
{
	if (m_postureStackIndex == 0)
	{
		if (pev)
			PrintIfWatched("PopPostureContext() underflow error!\n");

		m_isRunning = true;
		m_isCrouching = false;
		return;
	}

	--m_postureStackIndex;
	m_isRunning = m_postureStack[m_postureStackIndex].isRunning;
	m_isCrouching = m_postureStack[m_postureStackIndex].isCrouching;
}

/* <48fae3> ../game_shared/bot/bot.h:340 */
inline bool CBot::IsPlayerFacingMe(CBasePlayer *other) const
{
	Vector toOther = other->pev->origin - pev->origin;
	UTIL_MakeVectors(other->pev->v_angle + other->pev->punchangle);
	Vector otherDir = gpGlobals->v_forward;

	if (otherDir.x * toOther.x + otherDir.y * toOther.y < 0.0f)
		return true;
	return false;
}

/* <48fbfc> ../game_shared/bot/bot.h:355 */
inline bool CBot::IsPlayerLookingAtMe(CBasePlayer *other) const
{
	Vector toOther = other->pev->origin - pev->origin;
	toOther.NormalizeInPlace();

	UTIL_MakeVectors(other->pev->v_angle + other->pev->punchangle);
	Vector otherDir = gpGlobals->v_forward;

	const float lookAtCos = 0.9f;
	if (otherDir.x * toOther.x + otherDir.y * toOther.y < -lookAtCos)
	{
		Vector vec(other->EyePosition());
		if (IsVisible(&vec))
			return true;
	}
	return false;
}

#ifdef HOOK_GAMEDLL

typedef bool (CBot::*IS_VISIBLE_VECTOR)(const Vector *, bool) const;
typedef bool (CBot::*IS_VISIBLE_CBASE_PLAYER)(CBasePlayer *, bool, unsigned char *) const;

#endif // HOOK_GAMEDLL

#endif // BOT_H
