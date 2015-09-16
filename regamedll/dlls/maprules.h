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

#ifndef MAPRULES_H
#define MAPRULES_H
#ifdef _WIN32
#pragma once
#endif

#define MAX_EQUIP 32
#define SF_SCORE_NEGATIVE 0x0001
#define SF_SCORE_TEAM 0x0002

#define SF_ENVTEXT_ALLPLAYERS 0x0001

#define SF_TEAMMASTER_FIREONCE 0x0001
#define SF_TEAMMASTER_ANYTEAM 0x0002

#define SF_TEAMSET_FIREONCE 0x0001
#define SF_TEAMSET_CLEARTEAM 0x0002

#define SF_PKILL_FIREONCE 0x0001

#define SF_GAMECOUNT_FIREONCE 0x0001
#define SF_GAMECOUNT_RESET 0x0002

#define SF_GAMECOUNTSET_FIREONCE 0x0001

#define SF_PLAYEREQUIP_USEONLY 0x0001

#define SF_PTEAM_FIREONCE 0x0001
#define SF_PTEAM_KILL 0x0002
#define SF_PTEAM_GIB 0x0004

/* <edff5> ../cstrike/dlls/maprules.cpp:34 */
class CRuleEntity: public CBaseEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

	void SetMaster(int iszMaster)
	{
		m_iszMaster = iszMaster;
	}
protected:
	BOOL CanFireForActivator(CBaseEntity *pActivator);

private:
	string_t m_iszMaster;

};/* size: 156, cachelines: 3, members: 3 */

// CRulePointEntity -- base class for all rule "point" entities (not brushes)

/* <ee010> ../cstrike/dlls/maprules.cpp:95 */
class CRulePointEntity: public CRuleEntity
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 156, cachelines: 3, members: 1 */

// CRuleBrushEntity -- base class for all rule "brush" entities (not brushes)
// Default behavior is to set up like a trigger, invisible, but keep the model for volume testing

/* <ee209> ../cstrike/dlls/maprules.cpp:112 */
class CRuleBrushEntity: public CRuleEntity
{
public:
	virtual void Spawn(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);

#endif // HOOK_GAMEDLL

};/* size: 156, cachelines: 3, members: 1 */

// CGameScore / game_score	-- award points to player / team
//	Points +/- total
//	Flag: Allow negative scores			SF_SCORE_NEGATIVE
//	Flag: Award points to team in teamplay		SF_SCORE_TEAM

/* <ee086> ../cstrike/dlls/maprules.cpp:135 */
class CGameScore: public CRulePointEntity
{
public:
	virtual void Spawn(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline int Points(void)
	{
		return (int)(pev->frags);
	}
	inline BOOL AllowNegativeScore(void)
	{
		return pev->spawnflags & SF_SCORE_NEGATIVE;
	}
	inline BOOL AwardToTeam(void)
	{
		return pev->spawnflags & SF_SCORE_TEAM;
	}
	inline void SetPoints(int points)
	{
		pev->frags = points;
	}

};/* size: 156, cachelines: 3, members: 1 */

// CGameEnd / game_end	-- Ends the game in MP

/* <ee0d3> ../cstrike/dlls/maprules.cpp:195 */
class CGameEnd: public CRulePointEntity
{
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 156, cachelines: 3, members: 1 */

// CGameText / game_text	-- NON-Localized HUD Message (use env_message to display a titles.txt message)
//	Flag: All players	SF_ENVTEXT_ALLPLAYERS

/* <ee120> ../cstrike/dlls/maprules.cpp:223 */
class CGameText: public CRulePointEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL MessageToAll(void)
	{
		return (pev->spawnflags & SF_ENVTEXT_ALLPLAYERS) == SF_ENVTEXT_ALLPLAYERS;
	}
	inline void MessageSet(const char *pMessage)
	{
		pev->message = ALLOC_STRING(pMessage);
	}
	inline const char *MessageGet(void)
	{
		return STRING(pev->message);
	}

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

private:
	hudtextparms_t m_textParms;

};/* size: 196, cachelines: 4, members: 3 */

// CGameTeamMaster / game_team_master -- "Masters" like multisource, but based on the team of the activator
// Only allows mastered entity to fire if the team matches my team

// team index (pulled from server team list "mp_teamlist"
// Flag: Remove on Fire
// Flag: Any team until set?		-- Any team can use this until the team is set (otherwise no teams can use it)

/* <ee16d> ../cstrike/dlls/maprules.cpp:352 */
class CGameTeamMaster: public CRulePointEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	virtual BOOL IsTriggered(CBaseEntity *pActivator);
	virtual const char *TeamID(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int ObjectCaps_(void)
	{
		return (CRulePointEntity::ObjectCaps() | FCAP_MASTER);
	}
	BOOL IsTriggered_(CBaseEntity *pActivator);
	const char *TeamID_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL RemoveOnFire(void)
	{
		return (pev->spawnflags & SF_TEAMMASTER_FIREONCE) == SF_TEAMMASTER_FIREONCE;
	}
	inline BOOL AnyTeam(void)
	{
		return (pev->spawnflags & SF_TEAMMASTER_ANYTEAM) == SF_TEAMMASTER_ANYTEAM;
	}

private:
	BOOL TeamMatch(CBaseEntity *pActivator);

public:
	int m_teamIndex;
	USE_TYPE triggerType;

};/* size: 164, cachelines: 3, members: 3 */

// CGameTeamSet / game_team_set	-- Changes the team of the entity it targets to the activator's team
// Flag: Fire once
// Flag: Clear team		-- Sets the team to "NONE" instead of activator

/* <ee1bb> ../cstrike/dlls/maprules.cpp:464 */
class CGameTeamSet: public CRulePointEntity
{
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL RemoveOnFire(void)
	{
		return (pev->spawnflags & SF_TEAMSET_FIREONCE) == SF_TEAMSET_FIREONCE;
	}
	inline BOOL ShouldClearTeam(void)
	{
		return (pev->spawnflags & SF_TEAMSET_CLEARTEAM) == SF_TEAMSET_CLEARTEAM;
	}

};/* size: 156, cachelines: 3, members: 1 */

// CGamePlayerZone / game_player_zone -- players in the zone fire my target when I'm fired
// Needs master?

/* <ee229> ../cstrike/dlls/maprules.cpp:502 */
class CGamePlayerZone: public CRuleBrushEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[4];

private:
	string_t m_iszInTarget;
	string_t m_iszOutTarget;
	string_t m_iszInCount;
	string_t m_iszOutCount;

};/* size: 172, cachelines: 3, members: 6 */

// CGamePlayerHurt / game_player_hurt	-- Damages the player who fires it
// Flag: Fire once

/* <ee277> ../cstrike/dlls/maprules.cpp:619 */
class CGamePlayerHurt: public CRulePointEntity
{
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL RemoveOnFire(void)
	{
		return (pev->spawnflags & SF_PKILL_FIREONCE) == SF_PKILL_FIREONCE;
	}

};/* size: 156, cachelines: 3, members: 1 */

// CGameCounter / game_counter	-- Counts events and fires target
// Flag: Fire once
// Flag: Reset on Fire

/* <ee2c5> ../cstrike/dlls/maprules.cpp:662 */
class CGameCounter: public CRulePointEntity
{
public:
	virtual void Spawn(void);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL RemoveOnFire(void)
	{
		return (pev->spawnflags & SF_GAMECOUNT_FIREONCE) == SF_GAMECOUNT_FIREONCE;
	}
	inline BOOL ResetOnFire(void)
	{
		return (pev->spawnflags & SF_GAMECOUNT_RESET) == SF_GAMECOUNT_RESET;
	}
	inline void CountUp(void)
	{
		pev->frags++;
	}
	inline void CountDown(void)
	{
		pev->frags--;
	}
	inline void ResetCount(void)
	{
		pev->frags = pev->dmg;
	}
	inline int CountValue(void)
	{
		return (int)(pev->frags);
	}
	inline int LimitValue(void)
	{
		return (int)(pev->health);
	}
	inline BOOL HitLimit(void)
	{
		return CountValue() == LimitValue();
	}

private:
	inline void SetCountValue(int value)
	{
		pev->frags = value;
	}
	inline void SetInitialValue(int value)
	{
		pev->dmg = value;
	}

};/* size: 156, cachelines: 3, members: 1 */

// CGameCounterSet / game_counter_set	-- Sets the counter's value
// Flag: Fire once

/* <ee313> ../cstrike/dlls/maprules.cpp:738 */
class CGameCounterSet: public CRulePointEntity
{
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL RemoveOnFire(void)
	{
		return (pev->spawnflags & SF_GAMECOUNTSET_FIREONCE) == SF_GAMECOUNTSET_FIREONCE;
	}

};/* size: 156, cachelines: 3, members: 1 */

// CGamePlayerEquip / game_playerequip	-- Sets the default player equipment
// Flag: USE Only

/* <ee361> ../cstrike/dlls/maprules.cpp:771 */
class CGamePlayerEquip: public CRulePointEntity
{
public:
	virtual void KeyValue(KeyValueData *pkvd);
	virtual void Touch(CBaseEntity *pOther);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void KeyValue_(KeyValueData *pkvd);
	void Touch_(CBaseEntity *pOther);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	inline BOOL UseOnly(void)
	{
		return (pev->spawnflags & SF_PLAYEREQUIP_USEONLY) == SF_PLAYEREQUIP_USEONLY;
	}

private:
	void EquipPlayer(CBaseEntity *pPlayer);

public:
	string_t m_weaponNames[ MAX_EQUIP ];
	int m_weaponCount[ MAX_EQUIP ];

};/* size: 412, cachelines: 7, members: 3 */

// CGamePlayerTeam / game_player_team	-- Changes the team of the player who fired it
// Flag: Fire once
// Flag: Kill Player
// Flag: Gib Player

/* <ee3af> ../cstrike/dlls/maprules.cpp:867 */
class CGamePlayerTeam: public CRulePointEntity
{
public:
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

private:
	inline BOOL RemoveOnFire(void)
	{
		return (pev->spawnflags & SF_PTEAM_FIREONCE) == SF_PTEAM_FIREONCE;
	}
	inline BOOL ShouldKillPlayer(void)
	{
		return (pev->spawnflags & SF_PTEAM_KILL) == SF_PTEAM_KILL;
	}
	inline BOOL ShouldGibPlayer(void)
	{
		return (pev->spawnflags & SF_PTEAM_GIB) == SF_PTEAM_GIB;
	}
	const char *TargetTeamName(const char *pszTargetName);

};/* size: 156, cachelines: 3, members: 1 */

// linked objects
C_DLLEXPORT void game_score(entvars_t *pev);
C_DLLEXPORT void game_end(entvars_t *pev);
C_DLLEXPORT void game_text(entvars_t *pev);
C_DLLEXPORT void game_team_master(entvars_t *pev);
C_DLLEXPORT void game_team_set(entvars_t *pev);
C_DLLEXPORT void game_zone_player(entvars_t *pev);
C_DLLEXPORT void game_player_hurt(entvars_t *pev);
C_DLLEXPORT void game_counter(entvars_t *pev);
C_DLLEXPORT void game_counter_set(entvars_t *pev);
C_DLLEXPORT void game_player_equip(entvars_t *pev);
C_DLLEXPORT void game_player_team(entvars_t *pev);

#endif // MAPRULES_H
