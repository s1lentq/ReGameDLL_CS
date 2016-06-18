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

class BotProfile;

// The base bot class from which bots for specific games are derived
class CBot: public CBasePlayer {
public:
	virtual void Spawn() = 0;

	// invoked when injured by something
	virtual BOOL TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType) = 0;

	// invoked when killed
	virtual void Killed(entvars_t *pevAttacker, int iGib) = 0;
	virtual BOOL IsNetClient() = 0;
	virtual void Think() = 0;
	virtual BOOL IsBot() = 0;
	virtual Vector GetAutoaimVector(float flDelta) = 0;

	// invoked when in contact with a CWeaponBox
	virtual void OnTouchingWeapon(CWeaponBox *box) = 0;
	virtual bool Initialize(const BotProfile *profile) = 0;
	virtual void SpawnBot() = 0;

	// lightweight maintenance, invoked frequently
	virtual void Upkeep() = 0;

	// heavyweight algorithms, invoked less often
	virtual void Update() = 0;

	virtual void Run() = 0;
	virtual void Walk() = 0;
	virtual void Crouch() = 0;
	virtual void StandUp() = 0;
	virtual void MoveForward() = 0;
	virtual void MoveBackward() = 0;
	virtual void StrafeLeft() = 0;
	virtual void StrafeRight() = 0;

	// returns true if jump was started
	#define MUST_JUMP true
	virtual bool Jump(bool mustJump = false) = 0;

	// zero any MoveForward(), Jump(), etc
	virtual void ClearMovement() = 0;

	// Weapon interface
	virtual void UseEnvironment() = 0;
	virtual void PrimaryAttack() = 0;
	virtual void ClearPrimaryAttack() = 0;
	virtual void TogglePrimaryAttack() = 0;
	virtual void SecondaryAttack() = 0;
	virtual void Reload() = 0;

	// invoked when event occurs in the game (some events have NULL entities)
	virtual void OnEvent(GameEventType event, CBaseEntity *entity = NULL, CBaseEntity *other = NULL) = 0;

	// return true if we can see the point
	virtual bool IsVisible(const Vector *pos, bool testFOV = false) const = 0;

	// return true if we can see any part of the player
	virtual bool IsVisible(CBasePlayer *player, bool testFOV = false, unsigned char *visParts = NULL) const = 0;

	enum VisiblePartType:uint8
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
	virtual bool IsPlayerFacingMe(CBasePlayer *other) const = 0;

	// returns true if other player is pointing right at us
	virtual bool IsPlayerLookingAtMe(CBasePlayer *other) const = 0;
	virtual void ExecuteCommand() = 0;
	virtual void SetModel(const char *modelName) = 0;

public:
	unsigned int GetID() const { return m_id; }
	bool IsRunning() const { return m_isRunning; }
	bool IsCrouching() const { return m_isCrouching; }

	// return time last jump began
	float GetJumpTimestamp() const { return m_jumpTimestamp; }

	// return our personality profile
	const BotProfile *GetProfile() const { return m_profile; }

public:
	// the "personality" profile of this bot
	const BotProfile *m_profile;

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
