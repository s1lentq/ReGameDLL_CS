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

// custom enum
enum ChooseTeamMenuSlot
{
	MENU_SLOT_TEAM_UNDEFINED = -1,

	MENU_SLOT_TEAM_TERRORIST = 1,
	MENU_SLOT_TEAM_CT,
	MENU_SLOT_TEAM_VIP,

	MENU_SLOT_TEAM_RANDOM = 5,
	MENU_SLOT_TEAM_SPECT
};

// custom enum
enum BuyItemMenuSlot
{
	MENU_SLOT_ITEM_VEST = 1,
	MENU_SLOT_ITEM_VESTHELM,
	MENU_SLOT_ITEM_FLASHGREN,
	MENU_SLOT_ITEM_HEGREN,
	MENU_SLOT_ITEM_SMOKEGREN,
	MENU_SLOT_ITEM_NVG,
	MENU_SLOT_ITEM_DEFUSEKIT,
	MENU_SLOT_ITEM_SHIELD,
};

#define CS_NUM_SKIN				4
#define CZ_NUM_SKIN				5

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
#define CUSTOMFIELD_SEQUENCE	7
#define CUSTOMFIELD_ANIMTIME	8

typedef struct
{
	float m_fTimeEnteredPVS;

} ENTITYPVSSTATUS;

const int MAX_ENTITIES = 1380;
struct PLAYERPVSSTATUS
{
	ENTITYPVSSTATUS m_Status[MAX_ENTITIES];
	int headnode;
	int num_leafs;
	short int leafnums[MAX_ENT_LEAFS];
};

struct entity_field_alias_t
{
	char name[32];
	int field;
};

C_DLLEXPORT int CountTeams();
C_DLLEXPORT int CountTeamPlayers(int iTeam);

extern bool g_bServerActive;
extern bool g_skipCareerInitialSpawn;

extern unsigned short m_usResetDecals;
extern unsigned short g_iShadowSprite;

#ifdef REGAMEDLL_API
void HandleMenu_ChooseAppearance_OrigFunc(CBasePlayer *pPlayer, int slot);
BOOL HandleMenu_ChooseTeam_OrigFunc(CBasePlayer *pPlayer, int slot);
bool BuyGunAmmo_OrigFunc(CBasePlayer *pPlayer, CBasePlayerItem *weapon, bool bBlinkMoney);
CBaseEntity *BuyWeaponByWeaponID_OrigFunc(CBasePlayer *pPlayer, WeaponIdType weaponID);
void ShowMenu_OrigFunc(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText);
void ShowVGUIMenu_OrigFunc(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu);
#endif

void LinkUserMessages();
void WriteSigonMessages();

int CMD_ARGC_();
const char *CMD_ARGV_(int i);
void set_suicide_frame(entvars_t *pev);
void BlinkAccount(CBasePlayer *pPlayer, int numBlinks = 2);
BOOL ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason);
void ClientDisconnect(edict_t *pEntity);
void respawn(entvars_t *pev, BOOL fCopyCorpse = FALSE);
void ClientKill(edict_t *pEntity);
void ShowMenu(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText);
void ShowVGUIMenu(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu);
void ListPlayers(CBasePlayer *current);
void ProcessKickVote(CBasePlayer *pVotingPlayer, CBasePlayer *pKickPlayer);
void CheckStartMoney();
void ClientPutInServer(edict_t *pEntity);
void Host_Say(edict_t *pEntity, BOOL teamonly);
void DropSecondary(CBasePlayer *pPlayer);
void DropPrimary(CBasePlayer *pPlayer);
bool CanBuyThis(CBasePlayer *pPlayer, int iWeapon);
void BuyPistol(CBasePlayer *pPlayer, int iSlot);
void BuyShotgun(CBasePlayer *pPlayer, int iSlot);
void BuySubMachineGun(CBasePlayer *pPlayer, int iSlot);
CBaseEntity *BuyWeaponByWeaponID(CBasePlayer *pPlayer, WeaponIdType weaponID);
void BuyRifle(CBasePlayer *pPlayer, int iSlot);
void BuyMachineGun(CBasePlayer *pPlayer, int iSlot);
void BuyItem(CBasePlayer *pPlayer, int iSlot);
void HandleMenu_ChooseAppearance(CBasePlayer *pPlayer, int slot);
BOOL HandleMenu_ChooseTeam(CBasePlayer *pPlayer, int slot);
void Radio1(CBasePlayer *pPlayer, int slot);
void Radio2(CBasePlayer *pPlayer, int slot);
void Radio3(CBasePlayer *pPlayer, int slot);
bool BuyGunAmmo(CBasePlayer *pPlayer, CBasePlayerItem *weapon, bool bBlinkMoney);
bool BuyAmmo(CBasePlayer *pPlayer, int nSlot, bool bBlinkMoney);
CBaseEntity *EntityFromUserID(int userID);
int CountPlayersInServer();
BOOL HandleBuyAliasCommands(CBasePlayer *pPlayer, const char *pszCommand);
BOOL HandleRadioAliasCommands(CBasePlayer *pPlayer, const char *pszCommand);
void ClientCommand_(edict_t *pEntity);
void ClientUserInfoChanged(edict_t *pEntity, char *infobuffer);
void ServerDeactivate();
void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
void PlayerPreThink(edict_t *pEntity);
void PlayerPostThink(edict_t *pEntity);
void ParmsNewLevel();
void ParmsChangeLevel();
void StartFrame();
void EndFrame();
void ClientPrecache();
const char *GetGameDescription();
void SysEngine_Error(const char *error_string);
void PlayerCustomization(edict_t *pEntity, customization_t *pCust);
void SpectatorConnect(edict_t *pEntity);
void SpectatorDisconnect(edict_t *pEntity);
void SpectatorThink(edict_t *pEntity);
void SetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas);
void ResetPlayerPVS(edict_t *client, int clientnum);
bool CheckPlayerPVSLeafChanged(edict_t *client, int clientnum);
void MarkEntityInPVS(int clientnum, int entitynum, float time, bool inpvs);
bool CheckEntityRecentlyInPVS(int clientnum, int entitynum, float currenttime);
BOOL AddToFullPack(struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, BOOL player, unsigned char *pSet);
void CreateBaseline(int player, int eindex, struct entity_state_s *baseline, edict_t *entity, int playermodelindex, Vector player_mins, Vector player_maxs);
void Entity_FieldInit(struct delta_s *pFields);
void Entity_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to);
void Player_FieldInit(struct delta_s *pFields);
void Player_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to);
void Custom_Entity_FieldInit(delta_s *pFields);
void Custom_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to);
void RegisterEncoders();
int GetWeaponData(edict_t *pEdict, struct weapon_data_s *info);
void UpdateClientData(const edict_t *ent, int sendweapons, struct clientdata_s *cd);
void CmdStart(const edict_t *pEdict, const struct usercmd_s *cmd, unsigned int random_seed);
void CmdEnd(const edict_t *pEdict);
int ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size);
BOOL GetHullBounds(int hullnumber, float *mins, float *maxs);
void CreateInstancedBaselines();
int InconsistentFile(const edict_t *pEdict, const char *filename, char *disconnect_message);
int AllowLagCompensation();

inline const char *GetTeamName(int team)
{
	switch (team)
	{
	case CT:        return "CT";
	case TERRORIST: return "TERRORIST";
	case SPECTATOR: return "SPECTATOR";
	default:        return "UNASSIGNED";
	}
}

extern int gmsgWeapPickup;
extern int gmsgHudText;
extern int gmsgHudTextPro;
extern int gmsgHudTextArgs;
extern int gmsgShake;
extern int gmsgFade;
extern int gmsgFlashlight;
extern int gmsgFlashBattery;
extern int gmsgResetHUD;
extern int gmsgInitHUD;
extern int gmsgViewMode;
extern int gmsgShowGameTitle;
extern int gmsgCurWeapon;
extern int gmsgHealth;
extern int gmsgDamage;
extern int gmsgBattery;
extern int gmsgTrain;
extern int gmsgLogo;
extern int gmsgWeaponList;
extern int gmsgAmmoX;
extern int gmsgDeathMsg;
extern int gmsgScoreAttrib;
extern int gmsgScoreInfo;
extern int gmsgTeamInfo;
extern int gmsgTeamScore;
extern int gmsgGameMode;
extern int gmsgMOTD;
extern int gmsgServerName;
extern int gmsgAmmoPickup;
extern int gmsgItemPickup;
extern int gmsgHideWeapon;
extern int gmsgSayText;
extern int gmsgTextMsg;
extern int gmsgSetFOV;
extern int gmsgShowMenu;
extern int gmsgSendAudio;
extern int gmsgRoundTime;
extern int gmsgMoney;
extern int gmsgBlinkAcct;
extern int gmsgArmorType;
extern int gmsgStatusValue;
extern int gmsgStatusText;
extern int gmsgStatusIcon;
extern int gmsgBarTime;
extern int gmsgReloadSound;
extern int gmsgCrosshair;
extern int gmsgNVGToggle;
extern int gmsgRadar;
extern int gmsgSpectator;
extern int gmsgVGUIMenu;
extern int gmsgCZCareer;
extern int gmsgCZCareerHUD;
extern int gmsgTaskTime;
extern int gmsgTutorText;
extern int gmsgTutorLine;
extern int gmsgShadowIdx;
extern int gmsgTutorState;
extern int gmsgTutorClose;
extern int gmsgAllowSpec;
extern int gmsgBombDrop;
extern int gmsgBombPickup;
extern int gmsgHostagePos;
extern int gmsgHostageK;
extern int gmsgGeigerRange;
extern int gmsgSendCorpse;
extern int gmsgHLTV;
extern int gmsgSpecHealth;
extern int gmsgForceCam;
extern int gmsgADStop;
extern int gmsgReceiveW;
extern int gmsgScenarioIcon;
extern int gmsgBotVoice;
extern int gmsgBuyClose;
extern int gmsgItemStatus;
extern int gmsgLocation;
extern int gmsgSpecHealth2;
extern int gmsgBarTime2;
extern int gmsgBotProgress;
extern int gmsgBrass;
extern int gmsgFog;
extern int gmsgShowTimer;
extern int gmsgAccount;
extern int gmsgHealthInfo;
