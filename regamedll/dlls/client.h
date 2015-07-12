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

#ifndef CLIENT_H
#define CLIENT_H
#ifdef _WIN32
#pragma once
#endif

#define FIELD_ORIGIN0			0
#define FIELD_ORIGIN1			1
#define FIELD_ORIGIN2			2

#define FIELD_ANGLES0			3
#define FIELD_ANGLES1			4
#define FIELD_ANGLES2			5

#define CUSTOMFIELD_ORIGIN0		0
#define CUSTOMFIELD_ORIGIN1		1
#define CUSTOMFIELD_ORIGIN2		2

#define CUSTOMFIELD_ANGLES0		3
#define CUSTOMFIELD_ANGLES1		4
#define CUSTOMFIELD_ANGLES2		5

#define CUSTOMFIELD_SKIN		6
#define CUSTOMFIELD_SEQUENCE		7
#define CUSTOMFIELD_ANIMTIME		8

typedef struct
{
	float m_fTimeEnteredPVS;
} ENTITYPVSSTATUS;
/* size: 4, cachelines: 1, members: 1 */

typedef struct
{
	ENTITYPVSSTATUS m_Status[1380];
	int headnode;
	int num_leafs;
	short int leafnums[MAX_ENT_LEAFS];
} PLAYERPVSSTATUS;
/* size: 5624, cachelines: 88, members: 4 */

typedef struct
{
	char name[32];
	int field;
} entity_field_alias_t;
/* size: 36, cachelines: 1, members: 2 */

#ifdef HOOK_GAMEDLL

//#define g_flTimeLimit (*pg_flTimeLimit)
//#define g_flResetTime (*pg_flResetTime)
//#define g_bClientPrintEnable (*pg_bClientPrintEnable)

#define g_PVSStatus (*pg_PVSStatus)
#define m_usResetDecals (*pm_usResetDecals)
#define g_iShadowSprite (*pg_iShadowSprite)
#define sPlayerModelFiles (*psPlayerModelFiles)
#define g_skipCareerInitialSpawn (*pg_skipCareerInitialSpawn)
#define entity_field_alias (*pentity_field_alias)
#define player_field_alias (*pplayer_field_alias)
#define custom_entity_field_alias (*pcustom_entity_field_alias)

#endif // HOOK_GAMEDLL

extern PLAYERPVSSTATUS g_PVSStatus[32];

#ifdef HOOK_GAMEDLL

extern float g_flTimeLimit;
extern float g_flResetTime;
extern bool g_bClientPrintEnable;
extern bool g_skipCareerInitialSpawn;

extern char *sPlayerModelFiles[12];
extern bool g_skipCareerInitialSpawn;
extern entity_field_alias_t entity_field_alias[6];
extern entity_field_alias_t player_field_alias[3];
extern entity_field_alias_t custom_entity_field_alias[9];

#endif // HOOK_GAMEDLL

extern unsigned short m_usResetDecals;
extern unsigned short g_iShadowSprite;

NOBODY int CMD_ARGC_(void);
NOBODY const char *CMD_ARGV_(int i);
NOBODY void set_suicide_frame(entvars_t *pev);
NOBODY BOOL ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason);
NOBODY void ClientDisconnect(edict_t *pEntity);
void respawn(entvars_t *pev, BOOL fCopyCorpse = FALSE);
NOBODY void ClientKill(edict_t *pEntity);
NOBODY void ShowMenu(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText);
NOBODY void ShowVGUIMenu(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu);
NOBODY int CountTeams(void);
NOBODY void ListPlayers(CBasePlayer *current);
NOBODY int CountTeamPlayers(int iTeam);
NOBODY void ProcessKickVote(CBasePlayer *pVotingPlayer, CBasePlayer *pKickPlayer);
NOBODY TeamName SelectDefaultTeam(void);
void CheckStartMoney(void);
NOBODY void ClientPutInServer(edict_t *pEntity);
NOBODY int Q_strlen_(const char *str);
NOBODY void Host_Say(edict_t *pEntity, int teamonly);
NOBODY void DropPrimary(CBasePlayer *pPlayer);
NOBODY bool CanBuyThis(CBasePlayer *pPlayer, int iWeapon);
NOBODY void BuyPistol(CBasePlayer *pPlayer, int iSlot);
NOBODY void BuyShotgun(CBasePlayer *pPlayer, int iSlot);
NOBODY void BuySubMachineGun(CBasePlayer *pPlayer, int iSlot);
NOBODY void BuyWeaponByWeaponID(CBasePlayer *pPlayer, WeaponIdType weaponID);
NOBODY void BuyRifle(CBasePlayer *pPlayer, int iSlot);
NOBODY void BuyMachineGun(CBasePlayer *pPlayer, int iSlot);
NOBODY void BuyItem(CBasePlayer *pPlayer, int iSlot);
NOBODY void HandleMenu_ChooseAppearance(CBasePlayer *player, int slot);
NOBODY BOOL HandleMenu_ChooseTeam(CBasePlayer *player, int slot);
NOBODY void Radio1(CBasePlayer *player, int slot);
NOBODY void Radio2(CBasePlayer *player, int slot);
NOBODY void Radio3(CBasePlayer *player, int slot);
NOBODY bool BuyGunAmmo(CBasePlayer &player, CBasePlayerItem &weapon, bool bBlinkMoney);
NOBODY bool BuyAmmo(CBasePlayer *player, int nSlot, bool bBlinkMoney);
NOBODY CBaseEntity *EntityFromUserID(int userID);
NOBODY int CountPlayersInServer(void);
NOBODY BOOL HandleBuyAliasCommands(CBasePlayer *pPlayer, const char *pszCommand);
NOBODY BOOL HandleRadioAliasCommands(CBasePlayer *pPlayer, const char *pszCommand);
NOBODY void ClientCommand(edict_t *pEntity);
NOBODY void ClientUserInfoChanged(edict_t *pEntity, char *infobuffer);
NOBODY void ServerDeactivate(void);
NOBODY void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
NOBODY void PlayerPreThink(edict_t *pEntity);
NOBODY void PlayerPostThink(edict_t *pEntity);
void ParmsNewLevel(void);
NOBODY void ParmsChangeLevel(void);
NOBODY void StartFrame(void);
void ClientPrecache(void);
const char *GetGameDescription(void);
void Sys_Error(const char *error_string);
void PlayerCustomization(edict_t *pEntity, customization_t *pCust);
void SpectatorConnect(edict_t *pEntity);
void SpectatorDisconnect(edict_t *pEntity);
void SpectatorThink(edict_t *pEntity);
void SetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas);
NOXREF void ResetPlayerPVS(edict_t *client, int clientnum);
NOXREF bool CheckPlayerPVSLeafChanged(edict_t *client, int clientnum);
NOXREF void MarkEntityInPVS(int clientnum, int entitynum, float time, bool inpvs);
NOXREF bool CheckEntityRecentlyInPVS(int clientnum, int entitynum, float currenttime);
int AddToFullPack(struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet);
void CreateBaseline(int player, int eindex, struct entity_state_s *baseline, struct edict_s *entity, int playermodelindex, Vector player_mins, Vector player_maxs);
NOXREF void Entity_FieldInit(struct delta_s *pFields);
void Entity_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to);
NOXREF void Player_FieldInit(struct delta_s *pFields);
void Player_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to);
void Custom_Entity_FieldInit(delta_s *pFields);
void Custom_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to);
void RegisterEncoders(void);
int GetWeaponData(edict_s *player, struct weapon_data_s *info);
void UpdateClientData(const edict_s *ent, int sendweapons, clientdata_s *cd);
void CmdStart(const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed);
void CmdEnd(const edict_t *player);
int ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size);
int GetHullBounds(int hullnumber, float *mins, float *maxs);
void CreateInstancedBaselines(void);
int InconsistentFile(const edict_t *player, const char *filename, char *disconnect_message);
int AllowLagCompensation(void);

// refs
extern void (*pClientCommand)(edict_t *pEntity);

#endif // CLIENT_H
