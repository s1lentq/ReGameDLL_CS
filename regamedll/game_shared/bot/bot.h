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

#include "gamerules.h"

// 30 times per second, just like human clients
constexpr float g_flBotCommandInterval = 1.0 / 30.0;

// full AI only 10 times per second
constexpr float g_flBotFullThinkInterval = 1.0 / 10.0;

class BotProfile;

template <class T, class TWrap>
T *CreateBot(const BotProfile *profile)
{
	edict_t *pentBot;
	if (UTIL_ClientsInGame() >= gpGlobals->maxClients)
	{
		CONSOLE_ECHO("Unable to create bot: Server is full (%d/%d clients).\n", UTIL_ClientsInGame(), gpGlobals->maxClients);
		return nullptr;
	}

	char netname[64];
	UTIL_ConstructBotNetName(netname, sizeof(netname), profile);
	pentBot = CREATE_FAKE_CLIENT(netname);

	if (FNullEnt(pentBot))
	{
		CONSOLE_ECHO("Unable to create bot: pfnCreateFakeClient() returned null.\n");
		return nullptr;
	}
	else
	{
		T *pBot = nullptr;
		FREE_PRIVATE(pentBot);
		pBot = GetClassPtr<TWrap>((T *)VARS(pentBot));
		pBot->Initialize(profile);

		return pBot;
	}
}

// The base bot class from which bots for specific games are derived
class CBot: public CBasePlayer
{
public:
	// constructor initializes all values to zero
	CBot();

	virtual void Spawn();

	// invoked when injured by something
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
	{
		return CBasePlayer::TakeDamage(pevInflictor, pevAttacker, flDamage, bitsDamageType);
	}
	// invoked when killed
	virtual void Killed(entvars_t *pevAttacker, int iGib)
	{
		CBasePlayer::Killed(pevAttacker, iGib);
	}

	virtual void Think() {};
	virtual BOOL IsBot() { return TRUE; }
	virtual Vector GetAutoaimVector(float flDelta);

	// invoked when in contact with a CWeaponBox
	virtual void OnTouchingWeapon(CWeaponBox *box) {}

	// prepare bot for action
	virtual bool Initialize(const BotProfile *profile);

	virtual void SpawnBot() = 0;

	// lightweight maintenance, invoked frequently
	virtual void Upkeep() = 0;

	// heavyweight algorithms, invoked less often
	virtual void Update() = 0;

	virtual void Run();
	virtual void Walk();
	virtual void Crouch();
	virtual void StandUp();
	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void StrafeLeft();
	virtual void StrafeRight();

	// returns true if jump was started
	#define MUST_JUMP true
	virtual bool Jump(bool mustJump = false);

	// zero any MoveForward(), Jump(), etc
	virtual void ClearMovement();

	// Weapon interface
	virtual void UseEnvironment();
	virtual void PrimaryAttack();
	virtual void ClearPrimaryAttack();
	virtual void TogglePrimaryAttack();
	virtual void SecondaryAttack();
	virtual void Reload();

	// invoked when event occurs in the game (some events have NULL entities)
	virtual void OnEvent(GameEventType event, CBaseEntity *pEntity = nullptr, CBaseEntity *pOther = nullptr) {};

	// return true if we can see the point
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;

	// return true if we can see any part of the player
	virtual bool IsVisible(CBasePlayer *pPlayer, bool testFOV = false, unsigned char *visParts = nullptr) const = 0;

	enum VisiblePartType : uint8
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
	virtual bool IsPlayerFacingMe(CBasePlayer *pOther) const;

	// returns true if other player is pointing right at us
	virtual bool IsPlayerLookingAtMe(CBasePlayer *pOther) const;
	virtual void ExecuteCommand();
	virtual void SetModel(const char *modelName);

public:
	// return bot's unique ID
	unsigned int GetID() const { return m_id; }
	bool IsRunning() const { return m_isRunning; }
	bool IsCrouching() const { return m_isCrouching; }

	// push the current posture context onto the top of the stack
	void PushPostureContext();

	// restore the posture context to the next context on the stack
	void PopPostureContext();
	bool IsJumping();

	// return time last jump began
	float GetJumpTimestamp() const { return m_jumpTimestamp; }
	// returns ratio of ammo left to max ammo (1 = full clip, 0 = empty)
	float GetActiveWeaponAmmoRatio() const;

	// return true if active weapon has any empty clip
	bool IsActiveWeaponClipEmpty() const;

	// return true if active weapon has no ammo at all
	bool IsActiveWeaponOutOfAmmo() const;

	// is the weapon in the middle of a reload
	bool IsActiveWeaponReloading() const;

	// return true if active weapon's bullet spray has become large and inaccurate
	bool IsActiveWeaponRecoilHigh() const;

	// return the weapon the bot is currently using
	CBasePlayerWeapon *GetActiveWeapon() const;

	// return true if looking thru weapon's scope
	bool IsUsingScope() const;

	// returns TRUE if given entity is our enemy
	bool IsEnemy(CBaseEntity *pEntity) const;

	// return number of enemies left alive
	int GetEnemiesRemaining() const;

	// return number of friends left alive
	int GetFriendsRemaining() const;

	// return true if local player is observing this bot
	bool IsLocalPlayerWatchingMe() const;

	// output message to console
	void Print(char *format,...) const;

	// output message to console if we are being watched by the local player
	void PrintIfWatched(char *format,...) const;

	void BotThink();

#ifdef REGAMEDLL_FIXES
	BOOL IsNetClient() { return FALSE; }
#else
	// The ambiguous function because there is a virtual function in inherited classes.
	bool IsNetClient() const { return false; }

	int Save(CSave &save) const;
	int Restore(CRestore &restore) const;
#endif
	// return our personality profile
	const BotProfile *GetProfile() const { return m_profile; }

	enum BotRelationshipTeam: uint8
	{
		BOT_TEAMMATE = 0,
		BOT_ENEMY
	};
	BotRelationshipTeam BotRelationship(CBasePlayer *pTarget) const;

protected:
#ifndef REGAMEDLL_FIXES
	// Do a "client command" - useful for invoking menu choices, etc.
	void ClientCommand(const char *cmd, const char *arg1 = nullptr, const char *arg2 = nullptr, const char *arg3 = nullptr);
#endif

	// the "personality" profile of this bot
	const BotProfile *m_profile;

private:
	void ResetCommand();
	byte ThrottledMsec() const;

	// returns current movement speed (for walk/run)
	float GetMoveSpeed();

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
};

inline void CBot::SetModel(const char *modelName)
{
	SET_CLIENT_KEY_VALUE(entindex(), GET_INFO_BUFFER(edict()), "model", (char *)modelName);
}

inline float CBot::GetMoveSpeed()
{
	if (m_isRunning || m_isCrouching)
		return pev->maxspeed;

	return 0.4f * pev->maxspeed;
}

inline void CBot::Run()
{
	m_isRunning = true;
}

inline void CBot::Walk()
{
	m_isRunning = false;
}

inline CBasePlayerWeapon *CBot::GetActiveWeapon() const
{
	return static_cast<CBasePlayerWeapon *>(m_pActiveItem);
}

inline bool CBot::IsActiveWeaponReloading() const
{
	CBasePlayerWeapon *pCurrentWeapon = GetActiveWeapon();
	if (!pCurrentWeapon)
		return false;

	return (pCurrentWeapon->m_fInReload || pCurrentWeapon->m_fInSpecialReload) != 0;
}

inline bool CBot::IsActiveWeaponRecoilHigh() const
{
	CBasePlayerWeapon *pCurrentWeapon = GetActiveWeapon();
	if (pCurrentWeapon)
	{
		const float highRecoil = 0.4f;
		return (pCurrentWeapon->m_flAccuracy > highRecoil) != 0;
	}

	return false;
}

inline void CBot::PushPostureContext()
{
	if (m_postureStackIndex == MAX_POSTURE_STACK)
	{
		if (pev)
		{
			PrintIfWatched("PushPostureContext() overflow error!\n");
		}

		return;
	}

	m_postureStack[m_postureStackIndex].isRunning = m_isRunning;
	m_postureStack[m_postureStackIndex].isCrouching = m_isCrouching;
	m_postureStackIndex++;
}

inline void CBot::PopPostureContext()
{
	if (m_postureStackIndex == 0)
	{
		if (pev)
		{
			PrintIfWatched("PopPostureContext() underflow error!\n");
		}

		m_isRunning = true;
		m_isCrouching = false;
		return;
	}

	m_postureStackIndex--;
	m_isRunning = m_postureStack[m_postureStackIndex].isRunning;
	m_isCrouching = m_postureStack[m_postureStackIndex].isCrouching;
}

inline bool CBot::IsPlayerFacingMe(CBasePlayer *pOther) const
{
	Vector toOther = pOther->pev->origin - pev->origin;
	UTIL_MakeVectors(pOther->pev->v_angle + pOther->pev->punchangle);
	Vector otherDir = gpGlobals->v_forward;

	if (otherDir.x * toOther.x + otherDir.y * toOther.y < 0.0f)
		return true;

	return false;
}

inline bool CBot::IsPlayerLookingAtMe(CBasePlayer *pOther) const
{
	Vector toOther = pOther->pev->origin - pev->origin;
	toOther.NormalizeInPlace();

	UTIL_MakeVectors(pOther->pev->v_angle + pOther->pev->punchangle);
	Vector otherDir = gpGlobals->v_forward;

	const float lookAtCos = 0.9f;
	if (otherDir.x * toOther.x + otherDir.y * toOther.y < -lookAtCos)
	{
		Vector vec(pOther->EyePosition());
		if (IsVisible(&vec))
			return true;
	}

	return false;
}

inline CBot::BotRelationshipTeam CBot::BotRelationship(CBasePlayer *pTarget) const
{
#ifdef REGAMEDLL_ADD
	if (CSGameRules()->IsFreeForAll())
		return BOT_ENEMY;
#endif

	return pTarget->m_iTeam == m_iTeam ? BOT_TEAMMATE : BOT_ENEMY;
}

extern const char *BotArgs[4];
extern bool UseBotArgs;

extern bool AreBotsAllowed();
