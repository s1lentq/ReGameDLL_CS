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

#define MAX_EQUIP			32
#define SF_SCORE_NEGATIVE		0x0001
#define SF_SCORE_TEAM			0x0002

#define SF_ENVTEXT_ALLPLAYERS		0x0001

#define SF_TEAMMASTER_FIREONCE		0x0001
#define SF_TEAMMASTER_ANYTEAM		0x0002

#define SF_TEAMSET_FIREONCE		0x0001
#define SF_TEAMSET_CLEARTEAM		0x0002

#define SF_PKILL_FIREONCE		0x0001

#define SF_GAMECOUNT_FIREONCE		0x0001
#define SF_GAMECOUNT_RESET		0x0002

#define SF_GAMECOUNTSET_FIREONCE	0x0001

#define SF_PLAYEREQUIP_USEONLY		0x0001

#define SF_PTEAM_FIREONCE		0x0001
#define SF_PTEAM_KILL			0x0002
#define SF_PTEAM_GIB			0x0004

class CRuleEntity: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
public:
	void SetMaster(int iszMaster) { m_iszMaster = iszMaster; }

private:
	string_t m_iszMaster;
};

// CRulePointEntity -- base class for all rule "point" entities (not brushes)
class CRulePointEntity: public CRuleEntity {
public:
	virtual void Spawn() = 0;
};

// CRuleBrushEntity -- base class for all rule "brush" entities (not brushes)
// Default behavior is to set up like a trigger, invisible, but keep the model for volume testing
class CRuleBrushEntity: public CRuleEntity {
public:
	virtual void Spawn() = 0;
};

// CGameScore / game_score	-- award points to player / team
//	Points +/- total
//	Flag: Allow negative scores			SF_SCORE_NEGATIVE
//	Flag: Award points to team in teamplay		SF_SCORE_TEAM
class CGameScore: public CRulePointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int Points() const { return int(pev->frags); }
	BOOL AllowNegativeScore() { return pev->spawnflags & SF_SCORE_NEGATIVE; }
	BOOL AwardToTeam() const { return pev->spawnflags & SF_SCORE_TEAM; }
	void SetPoints(int points) { pev->frags = points; }
};

// CGameEnd / game_end	-- Ends the game in MP
class CGameEnd: public CRulePointEntity {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

// CGameText / game_text	-- NON-Localized HUD Message (use env_message to display a titles.txt message)
//	Flag: All players	SF_ENVTEXT_ALLPLAYERS
class CGameText: public CRulePointEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;

public:
	BOOL MessageToAll() const { return (pev->spawnflags & SF_ENVTEXT_ALLPLAYERS) == SF_ENVTEXT_ALLPLAYERS; }
	void MessageSet(const char *pMessage) { pev->message = ALLOC_STRING(pMessage); }
	const char *MessageGet() const { return STRING(pev->message); }

private:
	hudtextparms_t m_textParms;
};

// CGameTeamMaster / game_team_master -- "Masters" like multisource, but based on the team of the activator
// Only allows mastered entity to fire if the team matches my team
//
// team index (pulled from server team list "mp_teamlist"
// Flag: Remove on Fire
// Flag: Any team until set?		-- Any team can use this until the team is set (otherwise no teams can use it)
class CGameTeamMaster: public CRulePointEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int ObjectCaps() = 0;
	virtual BOOL IsTriggered(CBaseEntity *pActivator) = 0;
	virtual const char *TeamID() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	BOOL RemoveOnFire() const { return (pev->spawnflags & SF_TEAMMASTER_FIREONCE) == SF_TEAMMASTER_FIREONCE; }
	BOOL AnyTeam() const { return (pev->spawnflags & SF_TEAMMASTER_ANYTEAM) == SF_TEAMMASTER_ANYTEAM; }

public:
	int m_teamIndex;
	USE_TYPE triggerType;
};

// CGameTeamSet / game_team_set	-- Changes the team of the entity it targets to the activator's team
// Flag: Fire once
// Flag: Clear team		-- Sets the team to "NONE" instead of activator
class CGameTeamSet: public CRulePointEntity {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	BOOL RemoveOnFire() const { return (pev->spawnflags & SF_TEAMSET_FIREONCE) == SF_TEAMSET_FIREONCE; }
	BOOL ShouldClearTeam() const { return (pev->spawnflags & SF_TEAMSET_CLEARTEAM) == SF_TEAMSET_CLEARTEAM; }
};

// CGamePlayerZone / game_player_zone -- players in the zone fire my target when I'm fired
// Needs master?
class CGamePlayerZone: public CRuleBrushEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
private:
	string_t m_iszInTarget;
	string_t m_iszOutTarget;
	string_t m_iszInCount;
	string_t m_iszOutCount;
};

// CGamePlayerHurt / game_player_hurt	-- Damages the player who fires it
// Flag: Fire once
class CGamePlayerHurt: public CRulePointEntity {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	BOOL RemoveOnFire() const { return (pev->spawnflags & SF_PKILL_FIREONCE) == SF_PKILL_FIREONCE; }
};

// CGameCounter / game_counter	-- Counts events and fires target
// Flag: Fire once
// Flag: Reset on Fire
class CGameCounter: public CRulePointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	BOOL RemoveOnFire() const { return (pev->spawnflags & SF_GAMECOUNT_FIREONCE) == SF_GAMECOUNT_FIREONCE; }
	BOOL ResetOnFire() const { return (pev->spawnflags & SF_GAMECOUNT_RESET) == SF_GAMECOUNT_RESET; }

	void CountUp() { pev->frags++; }
	void CountDown() { pev->frags--; }
	void ResetCount() { pev->frags = pev->dmg; }

	int CountValue() const { return int(pev->frags); }
	int LimitValue() const { return int(pev->health); }
	BOOL HitLimit() const { return CountValue() == LimitValue(); }

private:
	void SetCountValue(int value) { pev->frags = value; }
	void SetInitialValue(int value) { pev->dmg = value; }
};

// CGameCounterSet / game_counter_set	-- Sets the counter's value
// Flag: Fire once
class CGameCounterSet: public CRulePointEntity {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	BOOL RemoveOnFire() const { return (pev->spawnflags & SF_GAMECOUNTSET_FIREONCE) == SF_GAMECOUNTSET_FIREONCE; }
};

// CGamePlayerEquip / game_playerequip	-- Sets the default player equipment
// Flag: USE Only
class CGamePlayerEquip: public CRulePointEntity {
public:
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Touch(CBaseEntity *pOther) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	BOOL UseOnly() const { return (pev->spawnflags & SF_PLAYEREQUIP_USEONLY) == SF_PLAYEREQUIP_USEONLY; }
public:
	string_t m_weaponNames[ MAX_EQUIP ];
	int m_weaponCount[ MAX_EQUIP ];
};

// CGamePlayerTeam / game_player_team -- Changes the team of the player who fired it
// Flag: Fire once
// Flag: Kill Player
// Flag: Gib Player
class CGamePlayerTeam: public CRulePointEntity {
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
private:
	BOOL RemoveOnFire() const { return (pev->spawnflags & SF_PTEAM_FIREONCE) == SF_PTEAM_FIREONCE; }
	BOOL ShouldKillPlayer() const { return (pev->spawnflags & SF_PTEAM_KILL) == SF_PTEAM_KILL; }
	BOOL ShouldGibPlayer() const { return (pev->spawnflags & SF_PTEAM_GIB) == SF_PTEAM_GIB; }
};
