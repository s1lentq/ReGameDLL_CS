#include "precompiled.h"

#define DEFINE_WEAPON(m_wpnid, m_cost, m_slotnum, m_acost)\
	{ m_wpnid, m_cost, 3, m_slotnum, m_acost }

/* <14e3fc> ../cstrike/dlls/player.cpp:5868 */
struct ZombieSpawn
{
	CBaseEntity *entity;
	CountdownTimer useableTimer;
};/* size: 12, cachelines: 1, members: 2 */

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

int giPrecacheGrunt = 0;
int gmsgFlashlight = 0;
int gmsgFlashBattery = 0;
int gmsgResetHUD = 0;
int gmsgInitHUD = 0;
int gmsgViewMode = 0;
int gmsgShowGameTitle = 0;
int gmsgCurWeapon = 0;
int gmsgHealth = 0;
int gmsgDamage = 0;
int gmsgBattery = 0;
int gmsgTrain = 0;
int gmsgLogo = 0;
int gmsgWeaponList = 0;
int gmsgAmmoX = 0;
int gmsgDeathMsg = 0;
int gmsgScoreAttrib = 0;
int gmsgScoreInfo = 0;
int gmsgTeamInfo = 0;
int gmsgTeamScore = 0;
int gmsgGameMode = 0;
int gmsgMOTD = 0;
int gmsgServerName = 0;
int gmsgAmmoPickup = 0;
int gmsgItemPickup = 0;
int gmsgHideWeapon = 0;
int gmsgSayText = 0;
int gmsgTextMsg = 0;
int gmsgSetFOV = 0;
int gmsgShowMenu = 0;
int gmsgSendAudio = 0;
int gmsgRoundTime = 0;
int gmsgMoney = 0;
int gmsgBlinkAcct = 0;
int gmsgArmorType = 0;
int gmsgStatusValue = 0;
int gmsgStatusText = 0;
int gmsgStatusIcon = 0;
int gmsgBarTime = 0;
int gmsgReloadSound = 0;
int gmsgCrosshair = 0;
int gmsgNVGToggle = 0;
int gmsgRadar = 0;
int gmsgSpectator = 0;
int gmsgVGUIMenu = 0;
int gmsgCZCareer = 0;
int gmsgCZCareerHUD = 0;
int gmsgTaskTime = 0;
int gmsgTutorText = 0;
int gmsgTutorLine = 0;
int gmsgShadowIdx = 0;
int gmsgTutorState = 0;
int gmsgTutorClose = 0;
int gmsgAllowSpec = 0;
int gmsgBombDrop = 0;
int gmsgBombPickup = 0;
int gmsgHostagePos = 0;
int gmsgHostageK = 0;
int gmsgGeigerRange = 0;
int gmsgSendCorpse = 0;
int gmsgHLTV = 0;
int gmsgSpecHealth = 0;
int gmsgForceCam = 0;
int gmsgADStop = 0;
int gmsgReceiveW = 0;
int gmsgScenarioIcon = 0;
int gmsgBotVoice = 0;
int gmsgBuyClose = 0;
int gmsgItemStatus = 0;
int gmsgLocation = 0;
int gmsgSpecHealth2 = 0;
int gmsgBarTime2 = 0;
int gmsgBotProgress = 0;
int gmsgBrass = 0;
int gmsgFog = 0;
int gmsgShowTimer = 0;

BOOL gInitHUD = TRUE;
cvar_t *sv_aim = NULL;

TYPEDESCRIPTION CRevertSaved::m_SaveData[] =
{
	DEFINE_FIELD(CRevertSaved, m_messageTime, FIELD_FLOAT),
	DEFINE_FIELD(CRevertSaved, m_loadTime, FIELD_FLOAT),
};

TYPEDESCRIPTION CBasePlayer::m_playerSaveData[] =
{
	DEFINE_FIELD(CBasePlayer, m_flFlashLightTime, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_iFlashBattery, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_afButtonLast, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_afButtonPressed, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_afButtonReleased, FIELD_INTEGER),
	DEFINE_ARRAY(CBasePlayer, m_rgItems, FIELD_INTEGER, MAX_ITEMS),
	DEFINE_FIELD(CBasePlayer, m_afPhysicsFlags, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_flTimeStepSound, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_flTimeWeaponIdle, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_flSwimTime, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_flDuckTime, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_flWallJumpTime, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_flSuitUpdate, FIELD_TIME),
	DEFINE_ARRAY(CBasePlayer, m_rgSuitPlayList, FIELD_INTEGER, CSUITPLAYLIST),
	DEFINE_FIELD(CBasePlayer, m_iSuitPlayNext, FIELD_INTEGER),
	DEFINE_ARRAY(CBasePlayer, m_rgiSuitNoRepeat, FIELD_INTEGER, CSUITNOREPEAT),
	DEFINE_ARRAY(CBasePlayer, m_rgflSuitNoRepeatTime, FIELD_TIME, CSUITNOREPEAT),
	DEFINE_FIELD(CBasePlayer, m_lastDamageAmount, FIELD_INTEGER),
	DEFINE_ARRAY(CBasePlayer, m_rgpPlayerItems, FIELD_CLASSPTR, MAX_ITEM_TYPES),
	DEFINE_FIELD(CBasePlayer, m_pActiveItem, FIELD_CLASSPTR),
	DEFINE_FIELD(CBasePlayer, m_pLastItem, FIELD_CLASSPTR),
	DEFINE_ARRAY(CBasePlayer, m_rgAmmo, FIELD_INTEGER, MAX_AMMO_SLOTS),
	DEFINE_FIELD(CBasePlayer, m_idrowndmg, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_idrownrestored, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_tSneaking, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_iTrain, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_bitsHUDDamage, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_flFallVelocity, FIELD_FLOAT),
	DEFINE_FIELD(CBasePlayer, m_iTargetVolume, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_iWeaponVolume, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_iExtraSoundTypes, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_iWeaponFlash, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_fLongJump, FIELD_BOOLEAN),
	DEFINE_FIELD(CBasePlayer, m_fInitHUD, FIELD_BOOLEAN),
	DEFINE_FIELD(CBasePlayer, m_tbdPrev, FIELD_TIME),
	DEFINE_FIELD(CBasePlayer, m_pTank, FIELD_EHANDLE),
	DEFINE_FIELD(CBasePlayer, m_iHideHUD, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_iFOV, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_flDisplayHistory, FIELD_INTEGER),
	DEFINE_FIELD(CBasePlayer, m_iJoiningState, FIELD_INTEGER),
};

//TODO: check it m_side - for restrict to team? CT changed to TERRORIST, and on the contrary?
WeaponStruct g_weaponStruct[MAX_WEAPONS] =
{
	{ 0, 0, 0, 0, 0 },

	{ WEAPON_P228,		P228_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_SECONDARY,	AMMO_357SIG_PRICE },
	{ WEAPON_SCOUT,		SCOUT_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_762MM_PRICE },
	{ WEAPON_XM1014,	XM1014_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_BUCKSHOT_PRICE },
	{ WEAPON_MAC10,		MAC10_PRICE,		CT,			AUTOBUYCLASS_PRIMARY,	AMMO_45ACP_PRICE },
	{ WEAPON_AUG,		AUG_PRICE,		TERRORIST,		AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
	{ WEAPON_ELITE,		ELITE_PRICE,		CT,			AUTOBUYCLASS_SECONDARY,	AMMO_9MM_PRICE },
	{ WEAPON_FIVESEVEN,	FIVESEVEN_PRICE,	TERRORIST|CT,		AUTOBUYCLASS_SECONDARY,	AMMO_57MM_PRICE },
	{ WEAPON_UMP45,		UMP45_PRICE,		TERRORIST,		AUTOBUYCLASS_PRIMARY,	AMMO_45ACP_PRICE },
	{ WEAPON_SG550,		SG550_PRICE,		TERRORIST,		AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
	{ WEAPON_USP,		USP_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_SECONDARY,	AMMO_45ACP_PRICE },
	{ WEAPON_GLOCK18,	GLOCK18_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_SECONDARY,	AMMO_9MM_PRICE },
	{ WEAPON_MP5N,		MP5NAVY_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_9MM_PRICE },
	{ WEAPON_AWP,		AWP_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_338MAG_PRICE },
	{ WEAPON_M249,		M249_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
	{ WEAPON_M3,		M3_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_BUCKSHOT_PRICE },
	{ WEAPON_M4A1,		M4A1_PRICE,		TERRORIST,		AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
	{ WEAPON_TMP,		TMP_PRICE,		TERRORIST,		AUTOBUYCLASS_PRIMARY,	AMMO_9MM_PRICE },
	{ WEAPON_G3SG1,		G3SG1_PRICE,		CT,			AUTOBUYCLASS_PRIMARY,	AMMO_762MM_PRICE },
	{ WEAPON_DEAGLE,	DEAGLE_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_SECONDARY,	AMMO_50AE_PRICE },
	{ WEAPON_SG552,		SG552_PRICE,		CT,			AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
	{ WEAPON_AK47,		AK47_PRICE,		CT,			AUTOBUYCLASS_PRIMARY,	AMMO_762MM_PRICE },
	{ WEAPON_P90,		P90_PRICE,		TERRORIST|CT,		AUTOBUYCLASS_PRIMARY,	AMMO_57MM_PRICE },
	{ WEAPON_FAMAS,		FAMAS_PRICE,		TERRORIST,		AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
	{ WEAPON_GALIL,		GALIL_PRICE,		CT,			AUTOBUYCLASS_PRIMARY,	AMMO_556MM_PRICE },
				// TODO: this have bug, the cost of galil $2000, but not $2250

	{ WEAPON_SHIELDGUN,	SHIELDGUN_PRICE,	TERRORIST,		AUTOBUYCLASS_PRIMARY,	0 },

	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};

#else //HOOK_GAMEDLL

int giPrecacheGrunt;
int gmsgWeapPickup;
int gmsgHudText;
int gmsgHudTextArgs;
int gmsgShake;
int gmsgFade;
int gmsgFlashlight;
//int gmsgFlashBattery;
//int gmsgResetHUD;
//int gmsgInitHUD;
//int gmsgViewMode;
//int gmsgShowGameTitle;
int gmsgCurWeapon;
//int gmsgHealth;
//int gmsgDamage;
//int gmsgBattery;
//int gmsgTrain;
//int gmsgLogo;
int gmsgWeaponList;
//int gmsgAmmoX;
//int gmsgDeathMsg;
int gmsgScoreAttrib;
int gmsgScoreInfo;
//int gmsgTeamInfo;
//int gmsgTeamScore;
//int gmsgGameMode;
//int gmsgMOTD;
//int gmsgServerName;
int gmsgAmmoPickup;
int gmsgItemPickup;
//int gmsgHideWeapon;
int gmsgSayText;
int gmsgTextMsg;
int gmsgSetFOV;
int gmsgShowMenu;
int gmsgSendAudio;
int gmsgRoundTime;
int gmsgMoney;
int gmsgBlinkAcct;
int gmsgArmorType;
//int gmsgStatusValue;
//int gmsgStatusText;
int gmsgStatusIcon;
int gmsgBarTime;
int gmsgReloadSound;
int gmsgCrosshair;
int gmsgNVGToggle;
//int gmsgRadar;
int gmsgSpectator;
//int gmsgVGUIMenu;
int gmsgCZCareer;
//int gmsgCZCareerHUD;
int gmsgTaskTime;
//int gmsgTutorText;
int gmsgTutorLine;
//int gmsgShadowIdx;
int gmsgTutorState;
int gmsgTutorClose;
//int gmsgAllowSpec;
int gmsgBombDrop;
//int gmsgBombPickup;
//int gmsgHostagePos;
//int gmsgHostageK;
int gmsgGeigerRange;
int gmsgSendCorpse;
//int gmsgHLTV;
//int gmsgSpecHealth;
//int gmsgForceCam;
//int gmsgADStop;
//int gmsgReceiveW;
int gmsgScenarioIcon;
int gmsgBotVoice;
int gmsgBuyClose;
int gmsgItemStatus;
//int gmsgLocation;
int gmsgSpecHealth2;
int gmsgBarTime2;
int gmsgBotProgress;
//int gmsgBrass;
//int gmsgFog;
//int gmsgShowTimer;

BOOL gInitHUD;
cvar_t *sv_aim;

TYPEDESCRIPTION (*CRevertSaved::m_SaveData)[2];
TYPEDESCRIPTION (*CBasePlayer::m_playerSaveData)[40];
WeaponStruct g_weaponStruct[ MAX_WEAPONS ];

#endif //HOOK_GAMEDLL

//int giPrecacheGrunt;
int gEvilImpulse101;
char g_szMapBriefingText[512];

//extern cvar_t fadetoblack;		// move player.h
//extern cvar_t playerid;		// move player.h

//CBaseEntity *g_pSelectedZombieSpawn;

//entvars_t *g_pevLastInflictor;
//extern cvar_t startmoney;		// move player.h
//CBaseEntity *g_pLastSpawn;
//CBaseEntity *g_pLastCTSpawn;
//CBaseEntity *g_pLastTerroristSpawn;
//ZombieSpawn zombieSpawn[256];
//int zombieSpawnCount;
//extern float g_flWeaponCheat;
//float g_flWeaponCheat;		// move player.h

//const char *BotArgs[4];
//bool UseBotArgs;

/* <15353b> ../cstrike/dlls/player.cpp:282 */
NOBODY void LinkUserMessages(void)
{
}

/* <1535a5> ../cstrike/dlls/player.cpp:380 */
void WriteSigonMessages(void)
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
#ifndef HOOK_GAMEDLL
		ItemInfo &II = CBasePlayerItem::ItemInfoArray[i];
#else
		ItemInfo &II = (*CBasePlayerItem::pItemInfoArray)[i];
#endif // HOOK_GAMEDLL

		if (!II.iId)
			continue;

		const char *pszName;
		if (!II.pszName)
			pszName = "Empty";
		else
			pszName = II.pszName;

		MESSAGE_BEGIN(MSG_INIT, gmsgWeaponList);
			WRITE_STRING(pszName);
			WRITE_BYTE(CBasePlayer::GetAmmoIndex(II.pszAmmo1));
			WRITE_BYTE(II.iMaxAmmo1);
			WRITE_BYTE(CBasePlayer::GetAmmoIndex(II.pszAmmo2));
			WRITE_BYTE(II.iMaxAmmo2);
			WRITE_BYTE(II.iSlot);
			WRITE_BYTE(II.iPosition);
			WRITE_BYTE(II.iId);
			WRITE_BYTE(II.iFlags);
		MESSAGE_END();
	}
}

/* <15f281> ../cstrike/dlls/player.cpp:425 */
LINK_ENTITY_TO_CLASS(player, CBasePlayer);

/* <1536a9> ../cstrike/dlls/player.cpp:429 */
void SendItemStatus(CBasePlayer *pPlayer)
{
	int itemStatus = 0;
	if (pPlayer->m_bHasNightVision)
		itemStatus |= ITEM_STATUS_NIGHTVISION;

	if (pPlayer->m_bHasDefuser)
		itemStatus |= ITEM_STATUS_DEFUSER;

	MESSAGE_BEGIN(MSG_ONE, gmsgItemStatus, NULL, pPlayer->pev);
		WRITE_BYTE(itemStatus);
	MESSAGE_END();
}

/* <150ed5> ../cstrike/dlls/player.cpp:438 */
const char *GetCSModelName(int item_id)
{
	const char *modelName = NULL;
	switch (item_id)
	{
		case WEAPON_P228:
			modelName = "models/w_p228.mdl";
			break;
		case WEAPON_SCOUT:
			modelName = "models/w_scout.mdl";
			break;
		case WEAPON_HEGRENADE:
			modelName = "models/w_hegrenade.mdl";
			break;
		case WEAPON_XM1014:
			modelName = "models/w_xm1014.mdl";
			break;
		case WEAPON_C4:
			modelName = "models/w_backpack.mdl";
			break;
		case WEAPON_MAC10:
			modelName = "models/w_mac10.mdl";
			break;
		case WEAPON_AUG:
			modelName = "models/w_aug.mdl";
			break;
		case WEAPON_SMOKEGRENADE:
			modelName = "models/w_smokegrenade.mdl";
			break;
		case WEAPON_ELITE:
			modelName = "models/w_elite.mdl";
			break;
		case WEAPON_FIVESEVEN:
			modelName = "models/w_fiveseven.mdl";
			break;
		case WEAPON_UMP45:
			modelName = "models/w_ump45.mdl";
			break;
		case WEAPON_SG550:
			modelName = "models/w_sg550.mdl";
			break;
		case WEAPON_GALIL:
			modelName = "models/w_galil.mdl";
			break;
		case WEAPON_FAMAS:
			modelName = "models/w_famas.mdl";
			break;
		case WEAPON_USP:
			modelName = "models/w_usp.mdl";
			break;
		case WEAPON_GLOCK18:
			modelName = "models/w_glock18.mdl";
			break;
		case WEAPON_AWP:
			modelName = "models/w_awp.mdl";
			break;
		case WEAPON_MP5N:
			modelName = "models/w_mp5.mdl";
			break;
		case WEAPON_M249:
			modelName = "models/w_m249.mdl";
			break;
		case WEAPON_M3:
			modelName = "models/w_m3.mdl";
			break;
		case WEAPON_M4A1:
			modelName = "models/w_m4a1.mdl";
			break;
		case WEAPON_TMP:
			modelName = "models/w_tmp.mdl";
			break;
		case WEAPON_G3SG1:
			modelName = "models/w_g3sg1.mdl";
			break;
		case WEAPON_FLASHBANG:
			modelName = "models/w_flashbang.mdl";
			break;
		case WEAPON_DEAGLE:
			modelName = "models/w_deagle.mdl";
			break;
		case WEAPON_SG552:
			modelName = "models/w_sg552.mdl";
			break;
		case WEAPON_AK47:
			modelName = "models/w_ak47.mdl";
			break;
		case WEAPON_KNIFE:
			modelName = "models/w_knife.mdl";
			break;
		case WEAPON_P90:
			modelName = "models/w_p90.mdl";
			break;
		case WEAPON_SHIELDGUN:
			modelName = "models/w_shield.mdl";
			break;
		default:
			ALERT(at_console, "CBasePlayer::PackDeadPlayerItems(): Unhandled item- not creating weaponbox\n");
	}
	return modelName;
}

/* <153737> ../cstrike/dlls/player.cpp:572 */
void CBasePlayer::SetPlayerModel(BOOL HasC4)
{
	char *infobuffer = GET_INFO_BUFFER(edict());
	char *model;

	if (m_iTeam == CT)
	{		
		switch (m_iModelName)
		{
			case MODEL_URBAN:
				model = "urban";
				break;
			case MODEL_GSG9:
				model = "gsg9";
				break;
			case MODEL_GIGN:
				model = "gign";
				break;
			case MODEL_SAS:
				model = "sas";
				break;
			case MODEL_VIP:
				model = "vip";
				break;
			case MODEL_SPETSNAZ:
				if (UTIL_IsGame("czero"))
				{
					model = "spetsnaz";
					break;
				}
			default:
			{
				if (IsBot())
				{
					model = (char *)TheBotProfiles->GetCustomSkinModelname(m_iModelName);
					if (!model)
						model = "urban";
				}
				else
					model = "urban";

				break;
			}
		}
	}
	else if (m_iTeam == TERRORIST)
	{
		switch (m_iModelName)
		{
			case MODEL_TERROR:
				model = "terror";
				break;
			case MODEL_LEET:
				model = "leet";
				break;
			case MODEL_ARCTIC:
				model = "arctic";
				break;
			case MODEL_GUERILLA:
				model = "guerilla";
				break;
			case MODEL_MILITIA:
				if (UTIL_IsGame("czero"))
				{
					model = "militia";
					break;
				}
			default:
			{
				if (IsBot())
				{
					model = (char *)TheBotProfiles->GetCustomSkinModelname(m_iModelName);
					if (!model)
						model = "terror";
				}
				else
					model = "terror";

				break;
			}
		}
	}
	else
		model = "urban";

	if (Q_strcmp(GET_KEY_VALUE(infobuffer, "model"), model))
		SET_CLIENT_KEY_VALUE(entindex(), infobuffer, "model", model);
}

/* <15f129> ../cstrike/dlls/player.cpp:659 */
NOXREF CBasePlayer *CBasePlayer::GetNextRadioRecipient(CBasePlayer *pStartPlayer)
{
	CBaseEntity *pEntity = (CBaseEntity *)pStartPlayer;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
	{
		if (FNullEnt(pEntity->edict()))
			break;

		//BOOL bSend = FALSE;
		CBasePlayer *pPlayer = GetClassPtr((CBasePlayer *)pEntity->pev);

		if (pEntity->IsPlayer())
		{
			if (pEntity->pev->flags != FL_DORMANT)
			{
				if (pPlayer && pPlayer->m_iTeam == m_iTeam)
					return pPlayer;
			}
		}
		else if (pPlayer)
		{
			if (pPlayer->pev->iuser1 == OBS_CHASE_LOCKED || pPlayer->pev->iuser1 == OBS_CHASE_FREE || pPlayer->pev->iuser1 == OBS_IN_EYE)
			{
				if (!FNullEnt(m_hObserverTarget))
					continue;

				CBasePlayer *pTarget = (CBasePlayer *)CBaseEntity::Instance(pPlayer->m_hObserverTarget->pev);
				if (pTarget && pTarget->m_iTeam == m_iTeam)
				{
					return pPlayer;
				}
			}
		}
	}
	return NULL;
}

/* <15edd2> ../cstrike/dlls/player.cpp:705 */
void CBasePlayer::Radio(const char *msg_id, const char *msg_verbose, short pitch, bool showIcon)
{
	if (!IsPlayer())
		return;

	if (pev->deadflag != DEAD_NO && !IsBot())
		return;

	CBaseEntity *pEntity = NULL;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
	{
		if (FNullEnt(pEntity->edict()))
			break;
		
		BOOL bSend = FALSE;
		CBasePlayer *pPlayer = GetClassPtr((CBasePlayer *)pEntity->pev);

		// TODO: check out! checking used is here pEntity or pPlayer?
		if (pEntity->IsPlayer())
		{
			if (pEntity->IsDormant())
				continue;

			if (pPlayer && pPlayer->m_iTeam == m_iTeam)
				bSend = TRUE;
		}
		else if (pPlayer)
		{
			if (pPlayer->pev->iuser1 != OBS_CHASE_LOCKED && pPlayer->pev->iuser1 != OBS_CHASE_FREE && pPlayer->pev->iuser1 != OBS_IN_EYE)
				continue;

			if (!FNullEnt(m_hObserverTarget))
				continue;

			CBasePlayer *pTarget = (CBasePlayer *)CBaseEntity::Instance(pPlayer->m_hObserverTarget->pev);

			if (pTarget && pTarget->m_iTeam == pPlayer->m_iTeam)
				bSend = TRUE;
		}

		if (!bSend || pPlayer->m_bIgnoreRadio)
			continue;

		MESSAGE_BEGIN(MSG_ONE, gmsgSendAudio, NULL, pEntity->pev);
			WRITE_BYTE(ENTINDEX(edict()));
			WRITE_STRING(msg_id);
			WRITE_SHORT(pitch);
		MESSAGE_END();

		if (msg_verbose)	
		{
			const char *placeName = NULL;
			Place playerPlace = TheNavAreaGrid.GetPlace( &pev->origin );
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();

			for (BotPhraseList::const_iterator iter = placeList->begin(); iter != placeList->end(); ++iter)
			{
				if ((*iter)->GetID() == playerPlace)
				{
					placeName = (*iter)->GetName();
					break;
				}
			}

			if (placeName != NULL)
				ClientPrint(pEntity->pev, HUD_PRINTRADIO, NumAsString(entindex()), "#Game_radio_location", STRING(pev->netname), placeName, msg_verbose);
			else
				ClientPrint(pEntity->pev, HUD_PRINTRADIO, NumAsString(entindex()), "#Game_radio", STRING(pev->netname), msg_verbose);
		}

		if (showIcon)
		{
			MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, NULL, pEntity->pev);
				WRITE_BYTE(TE_PLAYERATTACHMENT);
				WRITE_BYTE(ENTINDEX(edict()));
				WRITE_COORD(35); // vertical offset
				WRITE_SHORT(g_sModelIndexRadio); // model index
				WRITE_SHORT(15); // life
			MESSAGE_END();
		}
	}
}

/* <1537f3> ../cstrike/dlls/player.cpp:812 */
void CBasePlayer::SmartRadio(void)
{
	;
}

/* <15381b> ../cstrike/dlls/player.cpp:816 */
void CBasePlayer::Pain(int m_LastHitGroup, bool HasArmour)
{
	int temp = RANDOM_LONG(0, 2);

	if (m_LastHitGroup == HITGROUP_HEAD)
	{
		if (m_iKevlar == ARMOR_TYPE_HELMET)
		{
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_helmet-1.wav", VOL_NORM, ATTN_NORM);
			return;
		}

		switch (temp)
		{
		case 0:
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/headshot1.wav", VOL_NORM, ATTN_NORM);
			break;
		case 1:
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/headshot2.wav", VOL_NORM, ATTN_NORM);
			break;
		default:
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/headshot3.wav", VOL_NORM, ATTN_NORM);
			break;
		}
	}
	else
	{
		if (m_LastHitGroup != HITGROUP_LEFTLEG && m_LastHitGroup != HITGROUP_RIGHTLEG)
		{
			if (HasArmour)
			{
				EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_kevlar-1.wav", VOL_NORM, ATTN_NORM);
				return;
			}
		}

		switch (temp)
		{
		case 0:
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_flesh-1.wav", VOL_NORM, ATTN_NORM);
			break;
		case 1:
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_flesh-2.wav", VOL_NORM, ATTN_NORM);
			break;
		default:
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_flesh-3.wav", VOL_NORM, ATTN_NORM);
			break;
		}
	}
}

/* <153b48> ../cstrike/dlls/player.cpp:864 */
Vector VecVelocityForDamage(float flDamage)
{
	Vector vec(RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(200, 300));

	if (flDamage > -50.0f)
		vec = vec * 0.7f;
	else if (flDamage > -200.0f)
		vec = vec * 2.0f;
	else
		vec = vec * 10.0f;

	return vec;
}

/* <14edfb> ../cstrike/dlls/player.cpp:878 */
int TrainSpeed(int iSpeed, int iMax)
{
	int iRet = 0;
	//float fMax = iMax; // unused?
	float fSpeed = iSpeed;

	if (iSpeed < 0)
		iRet = TRAIN_BACK;

	else if (iSpeed == 0)
		iRet = TRAIN_NEUTRAL;

	else if (fSpeed < 0.33)
		iRet = TRAIN_SLOW;

	else if (fSpeed < 0.66)
		iRet = TRAIN_MEDIUM;
	else
		iRet = TRAIN_FAST;

	return iRet;
}

/* <153c8e> ../cstrike/dlls/player.cpp:902 */
NOXREF void CBasePlayer::DeathSound(void)
{
	switch (RANDOM_LONG(1, 4))
	{
		case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/die1.wav", VOL_NORM, ATTN_NORM);
			break;
		case 2: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/die2.wav", VOL_NORM, ATTN_NORM);
			break;
		case 3: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/die3.wav", VOL_NORM, ATTN_NORM);
			break;
		case 4: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/death6.wav", VOL_NORM, ATTN_NORM);
			break;
	}
}

/* <151213> ../cstrike/dlls/player.cpp:937 */
int CBasePlayer::TakeHealth_(float flHealth, int bitsDamageType)
{
	return CBaseMonster::TakeHealth(flHealth, bitsDamageType);
}

/* <150f1c> ../cstrike/dlls/player.cpp:943 */
Vector CBasePlayer::GetGunPosition_(void)
{
	return pev->origin + pev->view_ofs;
}

/* <15412b> ../cstrike/dlls/player.cpp:953 */
bool CBasePlayer::IsHittingShield(Vector &vecDirection, TraceResult *ptr)
{
	if ((m_pActiveItem && m_pActiveItem->m_iId == WEAPON_C4) || !HasShield())
		return false;

	if (ptr->iHitgroup == HITGROUP_SHIELD)
		 return true;

	if (m_bShieldDrawn)
		UTIL_MakeVectors(pev->angles);

	return false;
}

/* <152b58> ../cstrike/dlls/player.cpp:989 */
void CBasePlayer::TraceAttack_(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	bool bShouldBleed = true;
	bool bShouldSpark = false;
	bool bHitShield = IsHittingShield(vecDir, ptr);
	CBasePlayer *pAttacker = (CBasePlayer *)CBasePlayer::Instance(pevAttacker);

	if (CVAR_GET_FLOAT("mp_friendlyfire") == 0 && m_iTeam == pAttacker->m_iTeam)
		bShouldBleed = false;

	if (pev->takedamage == DAMAGE_NO)
		return;

	m_LastHitGroup = ptr->iHitgroup;
	if (bHitShield)
	{
		flDamage = 0;

		if (RANDOM_LONG(0, 1))
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/ric_metal-1.wav", VOL_NORM, ATTN_NORM);
		else
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "weapons/ric_metal-2.wav", VOL_NORM, ATTN_NORM);

		UTIL_Sparks(ptr->vecEndPos);

		pev->punchangle.x = flDamage * RANDOM_FLOAT(-0.15, 0.15);
		pev->punchangle.z = flDamage * RANDOM_FLOAT(-0.15, 0.15);

		if (pev->punchangle.x < 4)
			pev->punchangle.x = -4;

		if (pev->punchangle.z < -5)
			pev->punchangle.z = -5;

		else if (pev->punchangle.z > 5)
			pev->punchangle.z = 5;
	}
	else
	{
		switch (ptr->iHitgroup)
		{
			case HITGROUP_GENERIC:
				break;

			case HITGROUP_HEAD:
			{
				if (m_iKevlar == ARMOR_TYPE_HELMET)
				{
					bShouldBleed = false;
					bShouldSpark = true;
				}

				flDamage *= 4;
				if (bShouldBleed)
				{
					pev->punchangle.x = flDamage * -0.5;

					if (pev->punchangle.x < -12)
						pev->punchangle.x = -12;

					pev->punchangle.z = flDamage * RANDOM_FLOAT(-1, 1);

					if (pev->punchangle.z < -9)
						pev->punchangle.z = -9;

					else if (pev->punchangle.z > 9)
						pev->punchangle.z = 9;
				}
				break;
			}
			case HITGROUP_CHEST:
			{
				flDamage *= 1;

				if (m_iKevlar != ARMOR_TYPE_EMPTY)
					bShouldBleed = false;

				else if (bShouldBleed)
				{
					pev->punchangle.x = flDamage * -0.1;

					if (pev->punchangle.x < -4)
						pev->punchangle.x = -4;
				}
				break;
			}
			case HITGROUP_STOMACH:
			{
				flDamage = flDamage * 1.25;

				if (m_iKevlar != ARMOR_TYPE_EMPTY)
					bShouldBleed = false;

				else if (bShouldBleed)
				{
					pev->punchangle.x = flDamage * -0.1;

					if (pev->punchangle.x < -4)
						pev->punchangle.x = -4;
				}
				break;
			}
			case HITGROUP_LEFTARM:
			case HITGROUP_RIGHTARM:
			{
				if (m_iKevlar != ARMOR_TYPE_EMPTY)
					bShouldBleed = false;

				break;
			}
			case HITGROUP_LEFTLEG:
			case HITGROUP_RIGHTLEG:
			{
				flDamage *= 0.75;
				break;
			}
		}
	}

	if (bShouldBleed)
	{
		BloodSplat(ptr->vecEndPos, vecDir, ptr->iHitgroup, flDamage * 5);
		SpawnBlood(ptr->vecEndPos, BloodColor(), flDamage);
		TraceBleed(flDamage, vecDir, ptr, bitsDamageType);
	}
	else if (ptr->iHitgroup == HITGROUP_HEAD && bShouldSpark == true)
	{
		MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, ptr->vecEndPos);
			WRITE_BYTE(TE_STREAK_SPLASH);
			WRITE_COORD(ptr->vecEndPos.x);
			WRITE_COORD(ptr->vecEndPos.y);
			WRITE_COORD(ptr->vecEndPos.z);
			WRITE_COORD(ptr->vecPlaneNormal.x);
			WRITE_COORD(ptr->vecPlaneNormal.y);
			WRITE_COORD(ptr->vecPlaneNormal.z);
			WRITE_BYTE(5); // color
			WRITE_SHORT(22); // count
			WRITE_SHORT(25); // base speed
			WRITE_SHORT(65); // ramdon velocity
		MESSAGE_END();
	}

	AddMultiDamage(pevAttacker, this, flDamage, bitsDamageType);
}

/* <1541c2> ../cstrike/dlls/player.cpp:1171 */
const char *GetWeaponName(entvars_t *pevInflictor, entvars_t *pKiller)
{
	const char *killer_weapon_name = "world";

	if (pKiller->flags & FL_CLIENT)
	{
#ifndef REGAMEDLL_FIXES
		//int killer_index = ENTINDEX(ENT(pKiller)); unused!
#endif // REGAMEDLL_FIXES

		if (pevInflictor)
		{
			if (pevInflictor == pKiller)
			{
				CBasePlayer *pAttacker = (CBasePlayer *)CBaseEntity::Instance(pKiller);

				if (pAttacker)
				{
					if (pAttacker->m_pActiveItem)
						killer_weapon_name = pAttacker->m_pActiveItem->pszName();
				}
			}
			else
				killer_weapon_name = STRING(pevInflictor->classname);
		}
	}
	else
		killer_weapon_name = STRING(pevInflictor->classname);

	if (!Q_strncmp(killer_weapon_name, "weapon_", 7))
		killer_weapon_name += 7;

	else if (!Q_strncmp(killer_weapon_name, "monster_", 8))
		killer_weapon_name += 8;

	else if (Q_strncmp(killer_weapon_name, "func_", 5))
		killer_weapon_name += 5;

	return killer_weapon_name;
}

/* <14e061> ../cstrike/dlls/player.cpp:1214 */
void LogAttack(CBasePlayer *pAttacker, class CBasePlayer *pVictim, int teamAttack, int healthHit, int armorHit, int newHealth, int newArmor, const char *killer_weapon_name)
{
	int detail = logdetail.value;

	if (!detail)
		return;

	if (!pAttacker || !pVictim)
		return;

	if ((teamAttack && (detail & LOG_TEAMMATEATTACK)) || (!teamAttack && (detail & LOG_ENEMYATTACK)))
		UTIL_LogPrintf("\"%s<%i><%s><%s>\" attacked \"%s<%i><%s><%s>\" with \"%s\" (damage \"%d\") (damage_armor \"%d\") (health \"%d\") (armor \"%d\")\n",
		STRING(pAttacker->pev->netname),
		GETPLAYERUSERID(pAttacker->edict()),
		GETPLAYERAUTHID(pAttacker->edict()),
		GetTeam(pAttacker->m_iTeam),
		STRING(pVictim->pev->netname),
		GETPLAYERUSERID(pVictim->edict()),
		GETPLAYERAUTHID(pVictim->edict()),
		GetTeam(pVictim->m_iTeam),
		killer_weapon_name,
		healthHit,
		armorHit,
		newHealth,
		newArmor
	);
}

/* <15dff9> ../cstrike/dlls/player.cpp:1241 */
NOBODY int CBasePlayer::TakeDamage_(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
//	{
//		int fTookDamage;                                      //  1243
//		float flRatio;                                        //  1244
//		float flBonus;                                        //  1245
//		float flHealthPrev;                                   //  1246
//		int iGunType;                                         //  1247
//		float flShieldRatio;                                  //  1248
//		int teamAttack;                                       //  1251
//		int armorHit;                                         //  1251
//		class CBasePlayer *pAttack;                          //  1252
//		class CBaseEntity *pAttacker;                        //  1452
//		class CBaseEntity *attacker;                         //  1472
//		int i;                                                //  1662
//		{
//			float fTookDamage;                            //  1386
//			{
//				class CGrenade *pGrenade;            //  1290
//				class CBaseEntity *temp;             //  1291
//				GetClassPtr<CBaseEntity>(CBaseEntity *a);  //  1291
//				GetClassPtr<CGrenade>(CGrenade *a);  //  1295
//				edict(CBaseEntity *const this);  //  1299
//				Instance(entvars_t *pev);  //  1312
//			}
//			FNullEnt(const edict_t *pent);  //  1318
//			IsArmored(CBasePlayer *const this,
//					int nHitGroup);  //  1324
//			{
//				float flNew;                          //  1326
//				float flArmor;                        //  1327
//				{
//					int oldValue;                 //  1343
//				}
//			}
//			LogAttack(CBasePlayer *pAttacker,
//					class CBasePlayer *pVictim,
//					int teamAttack,
//					int healthHit,
//					int armorHit,
//					int newHealth,
//					int newArmor,
//					const char *killer_weapon_name);  //  1384
//			{
//				class CHalfLifeMultiplay *mp;        //  1395
//				{
//					int i;                        //  1398
//					{
//						class CBasePlayer *pPlayer;      //  1400
//						{
//							bool killedByHumanPlayer;           //  1403
//						}
//					}
//				}
//			}
//			{
//				int i;                                //  1414
//			}
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  1420
//			edict(CBaseEntity *const this);  //  1423
//			ENTINDEX(edict_t *pEdict);  //  1423
//			ENTINDEX(edict_t *pEdict);  //  1424
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  1429
//			edict(CBaseEntity *const this);  //  1430
//			ENTINDEX(edict_t *pEdict);  //  1430
//			{
//				int i;                                //  1434
//				{
//					class CBasePlayer *pPlayer;  //  1436
//					edict(CBaseEntity *const this);  //  1440
//					MESSAGE_BEGIN(int msg_dest,
//							int msg_type,
//							const float *pOrigin,
//							edict_t *ed);  //  1440
//				}
//			}
//			operator-(const class Vector *const this,
//					const class Vector &v);  //  1320
//			SetAnimation(CBasePlayer *const this,
//					PLAYER_ANIM playerAnim);  //  1372
//		}
//		Instance(entvars_t *pev);  //  1452
//		GetClassPtr<CBaseEntity>(CBaseEntity *a);  //  1472
//		{
//			class CBasePlayer *player;                   //  1475
//			{
//				class CBaseEntity *pBasePlayer;      //  1496
//				class CBasePlayer *basePlayer;       //  1497
//				edict(CBaseEntity *const this);  //  1500
//				FNullEnt(const edict_t *pent);  //  1500
//			}
//			HintMessage(CBasePlayer *const this,
//					const char *pMessage,
//					BOOL bDisplayIfPlayerDead,
//					BOOL bOverride);  //  1484
//			ShouldDoLargeFlinch(CBasePlayer *const this,
//						int nHitGroup,
//						int nGunType);  //  1557
//			SetAnimation(CBasePlayer *const this,
//					PLAYER_ANIM playerAnim);  //  1579
//			Length(const class Vector *const this);  //  1559
//			{
//				class Vector attack_velocity;         //  1561
//				operator-(const class Vector *const this,
//						const class Vector &v);  //  1563
//				Normalize(const class Vector *const this);  //  1564
//				operator+(const class Vector *const this,
//						const class Vector &v);  //  1568
//			}
//			SetAnimation(CBasePlayer *const this,
//					PLAYER_ANIM playerAnim);  //  1570
//		}
//		IsArmored(CBasePlayer *const this,
//				int nHitGroup);  //  1587
//		{
//			float flNew;                                  //  1589
//			float flArmor;                                //  1590
//			{
//				int oldValue;                         //  1604
//			}
//		}
//		LogAttack(CBasePlayer *pAttacker,
//				class CBasePlayer *pVictim,
//				int teamAttack,
//				int healthHit,
//				int armorHit,
//				int newHealth,
//				int newArmor,
//				const char *killer_weapon_name);  //  1630
//		{
//			class CHalfLifeMultiplay *mp;                //  1643
//			{
//				int i;                                //  1646
//				{
//					class CBasePlayer *pPlayer;  //  1648
//					{
//						bool killedByHumanPlayer;   //  1651
//					}
//				}
//			}
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1670
//		edict(CBaseEntity *const this);  //  1673
//		ENTINDEX(edict_t *pEdict);  //  1673
//		ENTINDEX(edict_t *pEdict);  //  1674
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  1679
//		edict(CBaseEntity *const this);  //  1680
//		ENTINDEX(edict_t *pEdict);  //  1680
//		{
//			class CBasePlayer *pPlayer;                  //  1686
//			edict(CBaseEntity *const this);  //  1690
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  1690
//		}
//	}
}

/* <1516a0> ../cstrike/dlls/player.cpp:1706 */
void packPlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem, bool packAmmo)
{
	if (pItem)
	{
		const char *modelName = GetCSModelName(pItem->m_iId);
		if (modelName)
		{
			CWeaponBox *pWeaponBox = (CWeaponBox *)CBaseEntity::Create("weaponbox", pPlayer->pev->origin, pPlayer->pev->angles, ENT(pPlayer->pev));

			pWeaponBox->pev->angles.x = 0;
			pWeaponBox->pev->angles.z = 0;

			pWeaponBox->pev->velocity = pPlayer->pev->velocity * 0.75;

			pWeaponBox->SetThink(&CWeaponBox::Kill);
			pWeaponBox->pev->nextthink = gpGlobals->time + 300;
			pWeaponBox->PackWeapon(pItem);

#ifndef HOOK_GAMEDLL
			if (packAmmo)
				pWeaponBox->PackAmmo(MAKE_STRING(CBasePlayerItem::ItemInfoArray[pItem->m_iId].pszAmmo1), pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()]);
#else // HOOK_GAMEDLL
			if (packAmmo)
				pWeaponBox->PackAmmo(MAKE_STRING((*CBasePlayerItem::pItemInfoArray)[pItem->m_iId].pszAmmo1), pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()]);
#endif // HOOK_GAMEDLL
			SET_MODEL(ENT(pWeaponBox->pev), modelName);
		}
	}
}

/* <15f739> ../cstrike/dlls/player.cpp:1756 */
void CBasePlayer::PackDeadPlayerItems(void)
{
	bool bPackGun = (g_pGameRules->DeadPlayerWeapons(this) != GR_PLR_DROP_GUN_NO);
	bool bPackAmmo = (g_pGameRules->DeadPlayerAmmo(this) != GR_PLR_DROP_AMMO_NO);

	if (bPackGun)
	{
		bool bShieldDropped = false;
		if (HasShield())
		{
			DropShield(TRUE);
			bShieldDropped = true;
		}

		int nBestWeight = 0;
		CBasePlayerItem *pBestItem = NULL;

		//TODO: 1 - 6?
		for (int n = 0; n < MAX_ITEM_TYPES; n++)
		{
			CBasePlayerItem *pPlayerItem = m_rgpPlayerItems[n];

			while (pPlayerItem != NULL)
			{
				ItemInfo info;
				if (pPlayerItem->iItemSlot() < KNIFE_SLOT && !bShieldDropped)
				{
					if (pPlayerItem->GetItemInfo(&info))
					{
						if (info.iWeight > nBestWeight)
						{
							nBestWeight = info.iWeight;
							pBestItem = pPlayerItem;
						}
					}
				}
				else if (pPlayerItem->iItemSlot() == GRENADE_SLOT && UTIL_IsGame("czero"))
					packPlayerItem(this, pPlayerItem, true);

				pPlayerItem = pPlayerItem->m_pNext;
			}
		}
		packPlayerItem(this, pBestItem, bPackAmmo);
	}
	RemoveAllItems(TRUE);
}

/* <15f710> ../cstrike/dlls/player.cpp:1829 */
void CBasePlayer::GiveDefaultItems(void)
{
	RemoveAllItems(FALSE);
	m_bHasPrimary = false;

	switch (m_iTeam)
	{
		case CT:
		{
			GiveNamedItem("weapon_knife");
			GiveNamedItem("weapon_usp");

			GiveAmmo(m_bIsVIP ? 12 : 24, "45acp", MAX_AMMO_45ACP);

			break;
		}
		case TERRORIST:
		{
			GiveNamedItem("weapon_knife");
			GiveNamedItem("weapon_glock18");

			GiveAmmo(40, "9mm", MAX_AMMO_9MM);

			break;
		}
	}
}

/* <15f406> ../cstrike/dlls/player.cpp:1871 */
void CBasePlayer::RemoveAllItems(BOOL removeSuit)
{
	BOOL bKillProgBar = false;
	int i;

	if (m_bHasDefuser)
	{
		m_bHasDefuser = false;
		pev->body = 0;

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("defuser");
		MESSAGE_END();

		SendItemStatus(this);
		bKillProgBar = true;
	}

	if (m_bHasC4)
	{
		m_bHasC4 = false;
		pev->body = 0;

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("c4");
		MESSAGE_END();

		bKillProgBar = true;
	}

	RemoveShield();

	if (bKillProgBar)
		SetProgressBarTime(0);

	if (m_pActiveItem)
	{
		ResetAutoaim();

		m_pActiveItem->Holster();
		m_pActiveItem = NULL;
	}
	m_pLastItem = NULL;

	for (i = 0; i < MAX_ITEM_TYPES; i++)
	{
		m_pActiveItem = m_rgpPlayerItems[i];

		while (m_pActiveItem)
		{
			CBasePlayerItem *pPendingItem = m_pActiveItem->m_pNext;

			m_pActiveItem->Drop();
			m_pActiveItem = pPendingItem;
		}

		m_rgpPlayerItems[i] = NULL;
	}

	m_pActiveItem = NULL;
	m_bHasPrimary = NULL;

	pev->viewmodel = 0;
	pev->weaponmodel = 0;

	if (removeSuit)
		pev->weapons = 0;
	else
		pev->weapons &= ~WEAPON_ALLWEAPONS;

	for (i = 0; i < MAX_AMMO_SLOTS; i++)
		m_rgAmmo[i] = 0;

	UpdateClientData();

	MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, NULL, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(0);
		WRITE_BYTE(0);
	MESSAGE_END();
}

/* <15436c> ../cstrike/dlls/player.cpp:1962 */
void CBasePlayer::SetBombIcon(BOOL bFlash)
{
	if (m_bHasC4)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
			WRITE_BYTE(bFlash ? STATUSICON_FLASH : STATUSICON_SHOW);
			WRITE_STRING("c4");
			WRITE_BYTE(0);
			WRITE_BYTE(160);
			WRITE_BYTE(0);
		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("c4");
		MESSAGE_END();
	}

	SetScoreboardAttributes();
}

void (*CBasePlayer__UpdateClientData)(void);

//TODO: lost? dwarf conflicted by name
/* <0> (null):0 */
NOBODY void __declspec(naked) CBasePlayer::UpdateClientData_(void)
{
	__asm
	{
		jmp CBasePlayer__UpdateClientData
	}
//	{
//		int i;
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		Update(class CUnifiedSignals *const this);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		{
//			class CBaseEntity * pEntity;
//			{
//				class CClientFog * pFog;
//				int r;
//				int g;
//				int b;
//				union  density;
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float  * pOrigin,
//						entvars_t * ent);
//			}
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				edict_t * ed);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		edict(class CBaseEntity *const this);
//		ENTINDEX(edict_t * pEdict);
//		{
//			int iHealth;
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float  * pOrigin,
//					entvars_t * ent);
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		{
//			class Vector damageOrigin;
//			edict_t * other;
//			int visibleDamageBits;
//			Vector(class Vector *const this,
//				const class Vector  &const v);
//			{
//				class CBaseEntity * pEntity;
//				Instance(edict_t * pent);
//			}
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float  * pOrigin,
//					entvars_t * ent);
//		}
//		SendAmmoUpdate(class CBasePlayer *const this);
//		{
//			int weapon_id;
//		}
//		{
//			class CBasePlayerWeapon * w;
//			iFlags(class CBasePlayerItem *const this);
//			AmmoInventory(class CBasePlayer *const this,
//					int iAmmoIndex);
//			HintMessage(class CBasePlayer *const this,
//					const char  * pMessage,
//					BOOL bDisplayIfPlayerDead,
//					BOOL bOverride);
//		}
//		operator-(const class Vector  *const this,
//				const class Vector  &const v);
//		Length(const class Vector  *const this);
//		{
//			class CBaseEntity * pPlayer;
//			entindex(class CBaseEntity *const this);
//			{
//				class CBasePlayer * player;
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float  * pOrigin,
//						entvars_t * ent);
//				entindex(class CBaseEntity *const this);
//			}
//		}
//		FlashlightIsOn(class CBasePlayer *const this);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float  * pOrigin,
//				entvars_t * ent);
//		FlashlightTurnOff(class CBasePlayer *const this);
//	}
}

/* <15f2ab> ../cstrike/dlls/player.cpp:1985 */
void CBasePlayer::SetProgressBarTime(int time)
{
	if (time)
	{
		m_progressStart = gpGlobals->time;
		m_progressEnd = time + gpGlobals->time;
	}
	else
	{
		m_progressStart = 0;
		m_progressEnd = 0;
	}

	MESSAGE_BEGIN(MSG_ONE, gmsgBarTime, NULL, pev);
		WRITE_SHORT(time);
	MESSAGE_END();

	CBaseEntity *pPlayer = NULL;
	int myIndex = entindex();

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		CBasePlayer *player = GetClassPtr((CBasePlayer *)pPlayer->pev);

		if (player->pev->iuser1 == OBS_IN_EYE && player->pev->iuser2 == myIndex)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBarTime, NULL, player->pev);
				WRITE_SHORT(time);
			MESSAGE_END();
		}
	}
}

/* <15dcb4> ../cstrike/dlls/player.cpp:2027 */
void CBasePlayer::SetProgressBarTime2(int time, float timeElapsed)
{
	if (time)
	{
		m_progressStart = gpGlobals->time - timeElapsed;
		m_progressEnd = time + gpGlobals->time - timeElapsed;
	}
	else
	{
		timeElapsed = 0;
		m_progressStart = 0;
		m_progressEnd = 0;
	}

	short iTimeElapsed = (timeElapsed * 100.0 / (m_progressEnd - m_progressStart));

	MESSAGE_BEGIN(MSG_ONE, gmsgBarTime2, NULL, pev);
		WRITE_SHORT(time);
		WRITE_SHORT(iTimeElapsed);
	MESSAGE_END();

	CBaseEntity *pPlayer = NULL;
	int myIndex = entindex();

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		CBasePlayer *player = GetClassPtr((CBasePlayer *)pPlayer->pev);

		if (player->pev->iuser1 == OBS_IN_EYE && player->pev->iuser2 == myIndex)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBarTime, NULL, player->pev);
				WRITE_SHORT(time);
				WRITE_SHORT(iTimeElapsed);
			MESSAGE_END();
		}
	}
}

/* <14e0e9> ../cstrike/dlls/player.cpp:2073 */
void BuyZoneIcon_Set(CBasePlayer *player)
{
	player->m_signals.Signal(SIGNAL_BUY);
}

/* <14e106> ../cstrike/dlls/player.cpp:2086 */
NOBODY void BuyZoneIcon_Clear(CBasePlayer *player)
{
	player->m_signals.Signal(player->m_signals.GetState() & ~SIGNAL_BUY);

	//int signalSave = m_signals.GetSignal();
	//int signalChanged = m_signals.GetState() ^ m_signals.GetSignal();
	//m_signals.Update();
}

/* <14e62c> ../cstrike/dlls/player.cpp:2115 */
NOBODY void BombTargetFlash_Set(CBasePlayer *player)
{
}

/* <14e649> ../cstrike/dlls/player.cpp:2129 */
NOBODY void BombTargetFlash_Clear(CBasePlayer *player)
{
}

/* <158292> ../cstrike/dlls/player.cpp:2136 */
NOBODY void RescueZoneIcon_Set(CBasePlayer *player)
{
}

/* <14e666> ../cstrike/dlls/player.cpp:2156 */
NOBODY void RescueZoneIcon_Clear(CBasePlayer *player)
{
}

/* <1582af> ../cstrike/dlls/player.cpp:2185 */
NOXREF void EscapeZoneIcon_Set(CBasePlayer *player)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, player->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("escape");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	if (player->m_iTeam == CT)
	{
		if (!(player->m_flDisplayHistory & DHF_IN_ESCAPE_ZONE))
		{
			player->m_flDisplayHistory |= DHF_IN_ESCAPE_ZONE;
			player->HintMessage("#Hint_terrorist_escape_zone", TRUE);
		}
	}
}

/* <14e683> ../cstrike/dlls/player.cpp:2203 */
NOXREF void EscapeZoneIcon_Clear(CBasePlayer *player)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, player->pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("escape");
	MESSAGE_END();

	if (player->m_iMenu >= Menu_Buy)
	{
		if (player->m_iMenu <= Menu_BuyItem)
		{
			CLIENT_COMMAND(player->edict(), "slot10\n");
		}
		else if (player->m_iMenu == Menu_ClientBuy)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, NULL, player->pev);
			MESSAGE_END();
		}
	}
}

/* <1582cc> ../cstrike/dlls/player.cpp:2231 */
NOXREF void VIP_SafetyZoneIcon_Set(CBasePlayer *player)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, player->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("vipsafety");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	if(!(player->m_flDisplayHistory & DHF_IN_VIPSAFETY_ZONE))
	{
		if (player->m_iTeam == CT)
		{
			player->m_flDisplayHistory |= DHF_IN_VIPSAFETY_ZONE;
			player->HintMessage("#Hint_ct_vip_zone");
		}
		else if (player->m_iTeam == TERRORIST)
		{
			player->m_flDisplayHistory |= DHF_IN_VIPSAFETY_ZONE;
			player->HintMessage("#Hint_terrorist_vip_zone");
		}
	}
}

/* <14e6a0> ../cstrike/dlls/player.cpp:2255 */
void VIP_SafetyZoneIcon_Clear(CBasePlayer *player)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, player->pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("vipsafety");
	MESSAGE_END();

	if (player->m_iMenu >= Menu_Buy)
	{
		if (player->m_iMenu <= Menu_BuyItem)
		{
			CLIENT_COMMAND(player->edict(), "slot10\n");
		}
		else if (player->m_iMenu == Menu_ClientBuy)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, NULL, player->pev);
			MESSAGE_END();
		}
	}
}

/* <154417> ../cstrike/dlls/player.cpp:2282 */
NOXREF void CBasePlayer::SendFOV(int fov)
{
	pev->fov = (float_precision)fov;
	m_iClientFOV = fov;
	m_iFOV = fov;

	MESSAGE_BEGIN(MSG_ONE, gmsgSetFOV, NULL, pev);
		WRITE_BYTE(fov);
	MESSAGE_END();
}

/* <160a1a> ../cstrike/dlls/player.cpp:2300 */
NOBODY void CBasePlayer::Killed_(entvars_t *pevAttacker, int iGib)
{
//	{
//		class CSound *pSound;                                //  2302
//		Instance(entvars_t *pev);  //  2310
//		{
//			class CBaseEntity *pAttackerEntity;          //  2374
//			class CBasePlayer *pAttacker;                //  2375
//			bool killerHasShield;                         //  2378
//			bool wasBlind;                                //  2380
//			Instance(entvars_t *pev);  //  2374
//			HasShield(CBasePlayer *const this);  //  2378
//			{
//				class CCSBot *pBot;                  //  2383
//				IsBlind(const class CBasePlayer *const this);  //  2384
//			}
//			{
//				int i;                                //  2386
//				{
//					class CBasePlayer *pPlayer;  //  2388
//					{
//						bool killedByHumanPlayer;   //  2391
//					}
//				}
//			}
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  2405
//		{
//			int i;                                        //  2411
//			{
//				class CBasePlayer *pObserver;        //  2413
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						entvars_t *ent);  //  2416
//			}
//		}
//		edict(CBaseEntity *const this);  //  2431
//		SetAnimation(CBasePlayer *const this,
//				PLAYER_ANIM playerAnim);  //  2439
//		{
//			class CSmokeGrenade *pSmoke;                 //  2461
//			Vector(Vector *const this,
//				const Vector &v);  //  2462
//			operator+(const Vector *const this,
//					const Vector &v);  //  2462
//		}
//		Vector(Vector *const this,
//			const Vector &v);  //  2455
//		operator+(const Vector *const this,
//				const Vector &v);  //  2455
//		{
//			class CHEGrenade *pHEGrenade;                //  2448
//			Vector(Vector *const this,
//				const Vector &v);  //  2449
//			operator+(const Vector *const this,
//					const Vector &v);  //  2449
//		}
//		{
//			int gmsgADStop;                               //  2489
//			ENTINDEX(edict_t *pEdict);  //  2486
//			ENTINDEX(edict_t *pEdict);  //  2487
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  2490
//		}
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  2480
//		operator-(const Vector *const this);  //  2535
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  2545
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  2550
//		SendFOV(CBasePlayer *const this,
//			int fov);  //  2556
//		BuyZoneIcon_Clear(CBasePlayer *player);  //  2588
//		HintMessage(CBasePlayer *const this,
//				const char *pMessage,
//				BOOL bDisplayIfPlayerDead,
//				BOOL bOverride);  //  2618
//		HintMessage(CBasePlayer *const this,
//				const char *pMessage,
//				BOOL bDisplayIfPlayerDead,
//				BOOL bOverride);  //  2599
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  2575
//		SendItemStatus(CBasePlayer *pPlayer);  //  2579
//		operator*(const Vector *const this,
//				float fl);  //  2508
//		operator*(const Vector *const this,
//				float fl);  //  2515
//		operator*(const Vector *const this,
//				float fl);  //  2532
//		Length(const Vector *const this);  //  2525
//		Length(const Vector *const this);  //  2525
//		operator/(const Vector *const this,
//				float fl);  //  2525
//		operator*(const Vector *const this,
//				float fl);  //  2525
//		Length(const Vector *const this);  //  2526
//		Length(const Vector *const this);  //  2520
//		Length(const Vector *const this);  //  2520
//		operator/(const Vector *const this,
//				float fl);  //  2520
//		operator*(const Vector *const this,
//				float fl);  //  2520
//		operator/(const Vector *const this,
//				float fl);  //  2520
//		Length(const Vector *const this);  //  2521
//	}
}

/* <154478> ../cstrike/dlls/player.cpp:2625 */
BOOL CBasePlayer::IsBombGuy(void)
{
	if (!g_pGameRules->IsMultiplayer())
		return FALSE;

	return m_bHasC4;
}

/* <1544a1> ../cstrike/dlls/player.cpp:2636 */
void CBasePlayer::SetAnimation(PLAYER_ANIM playerAnim)
{
	int animDesired;
	float speed;
	char szAnim[64];
	int hopSeq;
	int leapSeq;

	if (!pev->modelindex)
		return;

	if ((playerAnim == PLAYER_FLINCH || playerAnim == PLAYER_LARGE_FLINCH) && HasShield())
		return;

	if (playerAnim != PLAYER_FLINCH && playerAnim != PLAYER_LARGE_FLINCH && m_flFlinchTime > gpGlobals->time && pev->health > 0.0f)
		return;

	speed = pev->velocity.Length2D();

	if (pev->flags & FL_FROZEN)
	{
		speed = 0;
		playerAnim = PLAYER_IDLE;
	}

	hopSeq = LookupActivity(ACT_HOP);
	leapSeq = LookupActivity(ACT_LEAP);

	switch (playerAnim)
	{
		case PLAYER_JUMP:
		{
			if (m_Activity == ACT_SWIM || m_Activity == ACT_DIESIMPLE || m_Activity == ACT_HOVER)
				m_IdealActivity = m_Activity;
			else
			{
				m_IdealActivity = ACT_HOP;
				TheBots->OnEvent(EVENT_PLAYER_JUMPED, this);
			}
			break;
		}
		case PLAYER_SUPERJUMP:
		{
			if (m_Activity == ACT_SWIM || m_Activity == ACT_DIESIMPLE || m_Activity == ACT_HOVER)
				m_IdealActivity = m_Activity;
			else
				m_IdealActivity = ACT_LEAP;
			break;
		}
		case PLAYER_DIE:
		{
			m_IdealActivity = ACT_DIESIMPLE;
			DeathSound();
			break;
		}
		case PLAYER_ATTACK1:
		{
			if (m_Activity == ACT_SWIM || m_Activity == ACT_DIESIMPLE || m_Activity == ACT_HOVER)
				m_IdealActivity = m_Activity;
			else
			{
				m_IdealActivity = ACT_RANGE_ATTACK1;
				TheBots->OnEvent(EVENT_WEAPON_FIRED, this);
			}
			break;
		}
		case PLAYER_ATTACK2:
		{
			if (m_Activity == ACT_SWIM || m_Activity == ACT_DIESIMPLE || m_Activity == ACT_HOVER)
				m_IdealActivity = m_Activity;
			else
			{
				m_IdealActivity = ACT_RANGE_ATTACK2;
				TheBots->OnEvent(EVENT_WEAPON_FIRED, this);
			}
			break;
		}
		case PLAYER_RELOAD:
		{
			if (m_Activity == ACT_SWIM || m_Activity == ACT_DIESIMPLE || m_Activity == ACT_HOVER)
				m_IdealActivity = m_Activity;
			else
			{
				m_IdealActivity = ACT_RELOAD;
				TheBots->OnEvent(EVENT_WEAPON_RELOADED, this);
			}
			break;
		}
		case PLAYER_IDLE:
		case PLAYER_WALK:
		{
			if (pev->flags & FL_ONGROUND || (m_Activity != ACT_HOP && m_Activity != ACT_LEAP))
			{
				if (pev->waterlevel <= 1)
					m_IdealActivity = ACT_WALK;

				else if (speed == 0.0f)
					m_IdealActivity = ACT_HOVER;

				else
					m_IdealActivity = ACT_SWIM;
			}
			else
				m_IdealActivity = m_Activity;
			break;
		}
		case PLAYER_HOLDBOMB:
			m_IdealActivity = ACT_HOLDBOMB;
			break;
		case PLAYER_FLINCH:
			m_IdealActivity = ACT_FLINCH;
			break;
		case PLAYER_LARGE_FLINCH:
			m_IdealActivity = ACT_LARGE_FLINCH;
			break;
		default:
			break;
	}
	switch (m_IdealActivity)
	{
		case ACT_HOP:
		case ACT_LEAP:
		{
			if (m_Activity == m_IdealActivity)
				return;

			switch (m_Activity)
			{
				case ACT_RANGE_ATTACK1:
					Q_strcpy(szAnim, "ref_shoot_");
					break;
				case ACT_RANGE_ATTACK2:
					Q_strcpy(szAnim, "ref_shoot2_");
					break;
				case ACT_RELOAD:
					Q_strcpy(szAnim, "ref_reload_");
					break;
				default:
					Q_strcpy(szAnim, "ref_aim_");
					break;
			}

			Q_strcat(szAnim, m_szAnimExtention);
			animDesired = LookupSequence(szAnim);
			if (animDesired == -1)
				animDesired = 0;

			if (pev->sequence != animDesired || !m_fSequenceLoops)
				pev->frame = 0;

			if (!m_fSequenceLoops)
				pev->effects |= EF_NOINTERP;

			if (m_IdealActivity == ACT_LEAP)
				pev->gaitsequence = LookupActivity(ACT_LEAP);
			else
				pev->gaitsequence = LookupActivity(ACT_HOP);

			m_Activity = m_IdealActivity;
			break;
		}
		case ACT_RANGE_ATTACK1:
		{
			m_flLastFired = gpGlobals->time;

			if (pev->flags & FL_DUCKING)
				Q_strcpy(szAnim, "crouch_shoot_");
			else
				Q_strcpy(szAnim, "ref_shoot_");

			Q_strcat(szAnim, m_szAnimExtention);
			animDesired = LookupSequence(szAnim);
			if (animDesired == -1)
				animDesired = 0;

			pev->sequence = animDesired;
			pev->frame = 0;

			ResetSequenceInfo();
			m_Activity = m_IdealActivity;
			break;
		}
		case ACT_RANGE_ATTACK2:
		{
			m_flLastFired = gpGlobals->time;

			if (pev->flags & FL_DUCKING)
				Q_strcpy(szAnim, "crouch_shoot2_");
			else
				Q_strcpy(szAnim, "ref_shoot2_");

			Q_strcat(szAnim, m_szAnimExtention);
			animDesired = LookupSequence(szAnim);
			if (animDesired == -1)
				animDesired = 0;

			pev->sequence = animDesired;
			pev->frame = 0;

			ResetSequenceInfo();
			m_Activity = m_IdealActivity;
			break;
		}
		case ACT_RELOAD:
		{
			if (pev->flags & FL_DUCKING)
				Q_strcpy(szAnim, "crouch_reload_");
			else
				Q_strcpy(szAnim, "ref_reload_");

			Q_strcat(szAnim, m_szAnimExtention);
			animDesired = LookupSequence(szAnim);
			if (animDesired == -1)
				animDesired = 0;

			if (pev->sequence != animDesired || !m_fSequenceLoops)
				pev->frame = 0;

			if (!m_fSequenceLoops)
				pev->effects |= EF_NOINTERP;

			m_Activity = m_IdealActivity;
			break;
		}
		case ACT_HOLDBOMB:
		{
			if (pev->flags & FL_DUCKING)
				Q_strcpy(szAnim, "crouch_aim_");
			else
				Q_strcpy(szAnim, "ref_aim_");

			Q_strcat(szAnim, m_szAnimExtention);
			animDesired = LookupSequence(szAnim);
			if (animDesired == -1)
				animDesired = 0;

			m_Activity = m_IdealActivity;
			break;
		}
		case ACT_WALK:
		{
			if ((m_Activity != ACT_RANGE_ATTACK1 || m_fSequenceFinished)
				&& (m_Activity != ACT_RANGE_ATTACK2 || m_fSequenceFinished)
				&& (m_Activity != ACT_FLINCH || m_fSequenceFinished)
				&& (m_Activity != ACT_LARGE_FLINCH || m_fSequenceFinished)
				&& (m_Activity != ACT_RELOAD || m_fSequenceFinished))
			{
				if (speed <= 135.0f || m_flLastFired + 4.0 >= gpGlobals->time)
				{
					if (pev->flags & FL_DUCKING)
						Q_strcpy(szAnim, "crouch_aim_");
					else
						Q_strcpy(szAnim, "ref_aim_");

					Q_strcat(szAnim, m_szAnimExtention);
					animDesired = LookupSequence(szAnim);
					if (animDesired == -1)
						animDesired = 0;

					m_Activity = ACT_WALK;
				}
				else
				{
					Q_strcpy(szAnim, "run_");
					Q_strcat(szAnim, m_szAnimExtention);
					animDesired = LookupSequence(szAnim);
					if (animDesired == -1)
					{
						if (pev->flags & FL_DUCKING)
							Q_strcpy(szAnim, "crouch_aim_");
						else
							Q_strcpy(szAnim, "ref_aim_");

						Q_strcat(szAnim, m_szAnimExtention);
						animDesired = LookupSequence(szAnim);
						if (animDesired == -1)
							animDesired = 0;

						m_Activity = ACT_RUN;
						pev->gaitsequence = LookupActivity(ACT_RUN);
					}
					else
					{
						m_Activity = ACT_RUN;
						pev->gaitsequence = animDesired;
					}
					if (m_Activity == ACT_RUN)
					{
						//TODO: maybe away used variable 'speed'?
						//if (speed > 150.0f)
						if (pev->velocity.Length2D() > 150.0f)
							TheBots->OnEvent(EVENT_PLAYER_FOOTSTEP, this);
					}
				}
			}
			else
				animDesired = pev->sequence;

			if (speed > 135.0f)
				pev->gaitsequence = LookupActivity(ACT_RUN);
			else
				pev->gaitsequence = LookupActivity(ACT_WALK);
			break;
		}
		case ACT_FLINCH:
		case ACT_LARGE_FLINCH:
		{
			m_Activity = m_IdealActivity;

#ifndef REGAMEDLL_FIXES
			// TODO: why? this condition was checked!
			if ((playerAnim == PLAYER_FLINCH || playerAnim == PLAYER_LARGE_FLINCH) && HasShield())
				return;
#endif // REGAMEDLL_FIXES

			switch (m_LastHitGroup)
			{
				case HITGROUP_GENERIC:
				{
					if (RANDOM_LONG(0, 1))
						animDesired = LookupSequence("head_flinch");
					else
						animDesired = LookupSequence("gut_flinch");
					break;
				}
				case HITGROUP_HEAD:
				case HITGROUP_CHEST:
					animDesired = LookupSequence("head_flinch");
					break;
				case HITGROUP_SHIELD:
					animDesired = 0;
					break;
				default:
					animDesired = LookupSequence("gut_flinch");
					break;
			}

			if (animDesired == -1)
				animDesired = 0;

			break;
		}
		case ACT_DIESIMPLE:
		{
			if (m_Activity == m_IdealActivity)
				return;

			m_Activity = m_IdealActivity;
			m_flDeathThrowTime = 0;
			m_iThrowDirection = THROW_NONE;

			switch (m_LastHitGroup)
			{
				case HITGROUP_GENERIC:
				{
					switch (RANDOM_LONG(0, 8))
					{
						case 0:
							animDesired = LookupActivity(ACT_DIE_HEADSHOT);
							m_iThrowDirection = THROW_BACKWARD;
							break;
						case 1:
							animDesired = LookupActivity(ACT_DIE_GUTSHOT);
							break;
						case 2:
							animDesired = LookupActivity(ACT_DIE_BACKSHOT);
							m_iThrowDirection = THROW_HITVEL;
							break;
						case 3:
							animDesired = LookupActivity(ACT_DIESIMPLE);
							break;
						case 4:
							animDesired = LookupActivity(ACT_DIEBACKWARD);
							m_iThrowDirection = THROW_HITVEL;
							break;
						case 5:
							animDesired = LookupActivity(ACT_DIEFORWARD);
							m_iThrowDirection = THROW_FORWARD;
							break;
						case 6:
							animDesired = LookupActivity(ACT_DIE_CHESTSHOT);
							break;
						case 7:
							animDesired = LookupActivity(ACT_DIE_GUTSHOT);
							break;
						case 8:
							animDesired = LookupActivity(ACT_DIE_HEADSHOT);
							break;
						default:
							break;
					}
					break;
				}
				case HITGROUP_HEAD:
				{
					int random = RANDOM_LONG(0, 8);
					m_bHeadshotKilled = true;

					if (m_bHighDamage)
						++random;

					switch (random)
					{
						case 1:
						case 2:
							m_iThrowDirection = THROW_BACKWARD;
							break;
						case 3:
						case 4:
							m_iThrowDirection = THROW_FORWARD;
							break;
						case 5:
						case 6:
							m_iThrowDirection = THROW_HITVEL;
							break;
						default:
							m_iThrowDirection = THROW_NONE;
							break;
					}

					animDesired = LookupActivity(ACT_DIE_HEADSHOT);
					break;
				}
				case HITGROUP_CHEST:
					animDesired = LookupActivity(ACT_DIE_CHESTSHOT);
					break;
				case HITGROUP_STOMACH:
					animDesired = LookupActivity(ACT_DIE_GUTSHOT);
					break;
				case HITGROUP_LEFTARM:
					animDesired = LookupSequence("left");
					break;
				case HITGROUP_RIGHTARM:
				{
					m_iThrowDirection = RANDOM_LONG(0, 1) ? THROW_HITVEL : THROW_HITVEL_MINUS_AIRVEL;
					animDesired = LookupSequence("right");
					break;
				}
				default:
				{
					animDesired = LookupActivity(ACT_DIESIMPLE);
					break;
				}
			}
			if (pev->flags & FL_DUCKING)
			{
				animDesired = LookupSequence("crouch_die");
				m_iThrowDirection = THROW_BACKWARD;
			}
			else if (m_bKilledByBomb || m_bKilledByGrenade)
			{
				UTIL_MakeVectors(pev->angles);

				if (DotProduct(gpGlobals->v_forward, m_vBlastVector) > 0.0f)
					animDesired = LookupSequence("left");

				else
				{
					if (RANDOM_LONG(0, 1))
						animDesired = LookupSequence("crouch_die");
					else
						animDesired = LookupActivity(ACT_DIE_HEADSHOT);
				}

				if (m_bKilledByBomb)
					m_iThrowDirection = THROW_BOMB;

				else if (m_bKilledByGrenade)
					m_iThrowDirection = THROW_GRENADE;
			}

			if (animDesired == -1)
				animDesired = 0;

			if (pev->sequence != animDesired)
			{
				pev->gaitsequence = 0;
				pev->sequence = animDesired;
				pev->frame = 0.0f;
				ResetSequenceInfo();
			}
			return;
		}
		default:
		{
			if (m_Activity == m_IdealActivity)
				return;

			m_Activity = m_IdealActivity;
			animDesired = LookupActivity(m_IdealActivity);

			if (pev->sequence != animDesired)
			{
				pev->gaitsequence = 0;
				pev->sequence = animDesired;
				pev->frame = 0;

				ResetSequenceInfo();
			}
			return;
		}
	}

	if (pev->gaitsequence != hopSeq && pev->gaitsequence != leapSeq)
	{
		if (pev->flags & FL_DUCKING)
		{
			if (speed != 0.0f)
				pev->gaitsequence = LookupActivity(ACT_CROUCH);
			else
				pev->gaitsequence = LookupActivity(ACT_CROUCHIDLE);
		}
		else
		{
			if (speed > 135.0f)
			{
				if (m_flLastFired + 4.0f < gpGlobals->time)
				{
					if (m_Activity != ACT_FLINCH && m_Activity != ACT_LARGE_FLINCH)
					{
						Q_strcpy(szAnim, "run_");
						Q_strcat(szAnim, m_szAnimExtention);

						animDesired = LookupSequence(szAnim);
						if (animDesired == -1)
						{
							if (pev->flags & FL_DUCKING)
								Q_strcpy(szAnim, "crouch_aim_");
							else
								Q_strcpy(szAnim, "ref_aim_");

							Q_strcat(szAnim, m_szAnimExtention);
							animDesired = LookupSequence(szAnim);
						}
						else
							pev->gaitsequence = animDesired;

						m_Activity = ACT_RUN;
					}
				}
				pev->gaitsequence = LookupActivity(ACT_RUN);
			}
			else
			{
				if (speed > 0.0f)
					pev->gaitsequence = LookupActivity(ACT_WALK);
				else
					pev->gaitsequence = LookupActivity(ACT_IDLE);
			}
		}
	}
	if (pev->sequence != animDesired)
	{
		pev->sequence = animDesired;
		pev->frame = 0;

		ResetSequenceInfo();
	}
}

/* <1544f4> ../cstrike/dlls/player.cpp:3264 */
NOBODY void CBasePlayer::WaterMove(void)
{
//	{
//		int air;                                              //  3266
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  3285
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  3287
//		VARS(EOFFSET eoffset);  //  3322
//		VARS(EOFFSET eoffset);  //  3322
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  3356
//		VARS(EOFFSET eoffset);  //  3363
//		VARS(EOFFSET eoffset);  //  3363
//		VARS(EOFFSET eoffset);  //  3368
//		VARS(EOFFSET eoffset);  //  3368
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  3355
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  3354
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  3353
//	}
}

/* <15493f> ../cstrike/dlls/player.cpp:3380 */
BOOL CBasePlayer::IsOnLadder(void)
{
	return pev->movetype == MOVETYPE_FLY;
}

/* <160720> ../cstrike/dlls/player.cpp:3387 */
NOXREF void CBasePlayer::ThrowWeapon(char *pszItemName)
{
	for (int i = 0; i < MAX_WEAPON_SLOTS; i++)
	{
		CBasePlayerItem *pWeapon = m_rgpPlayerItems[i];

		while (pWeapon != NULL)
		{
			if (!Q_strcmp(pszItemName, STRING(pWeapon->pev->classname)))
			{
				DropPlayerItem(pszItemName);
				return;
			}

			pWeapon = pWeapon->m_pNext;
		}
	}
}

/* <154967> ../cstrike/dlls/player.cpp:3424 */
LINK_ENTITY_TO_CLASS(weapon_shield, CWShield);

/* <151962> ../cstrike/dlls/player.cpp:3426 */
NOBODY void CWShield::Spawn(void)
{
}

/* <152e95> ../cstrike/dlls/player.cpp:3436 */
NOBODY void CWShield::Touch(CBaseEntity *pOther)
{
//	{
//		class CBasePlayer *pPlayer;                          //  3457
//	}
//	Touch(CWShield *const this,
//		class CBaseEntity *pOther);  //  3436
}

/* <154a43> ../cstrike/dlls/player.cpp:3480 */
NOBODY void CBasePlayer::GiveShield(bool bDeploy)
{
}

/* <154a70> ../cstrike/dlls/player.cpp:3504 */
void CBasePlayer::RemoveShield(void)
{
	if (HasShield())
	{
		m_bOwnsShield = false;
		m_bHasPrimary = false;
		m_bShieldDrawn = false;
		pev->gamestate = 1;

		UpdateShieldCrosshair(true);
	}
}

/* <154ad5> ../cstrike/dlls/player.cpp:3521 */
void CBasePlayer::DropShield(bool bDeploy)
{
	if (!HasShield())
		return;

	if (m_pActiveItem && !m_pActiveItem->CanHolster())
		return;

	if (m_pActiveItem)
	{
		CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)m_pActiveItem;

		if (pWeapon->m_iId == WEAPON_HEGRENADE || pWeapon->m_iId == WEAPON_FLASHBANG || pWeapon->m_iId == WEAPON_SMOKEGRENADE)
		{
			if (m_rgAmmo[ pWeapon->m_iPrimaryAmmoType ] <= 0)
				g_pGameRules->GetNextBestWeapon(this, pWeapon);
		}
	}

	if (m_pActiveItem)
	{
		CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)m_pActiveItem;

		if (pWeapon->m_flStartThrow != 0)
			m_pActiveItem->Holster();
	}

	if (IsReloading())
	{
		CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)m_pActiveItem;

		pWeapon->m_fInReload = FALSE;
		m_flNextAttack = 0;
	}

	if (IsProtectedByShield() && m_pActiveItem)
		((CBasePlayerWeapon *)m_pActiveItem)->SecondaryAttack();

	m_bShieldDrawn = false;

	RemoveShield();

	if (m_pActiveItem && bDeploy)
		m_pActiveItem->Deploy();

	UTIL_MakeVectors(pev->angles);

	CWShield *pShield = (CWShield *)CBaseEntity::Create("weapon_shield", pev->origin + gpGlobals->v_forward * 10, pev->angles, edict());

	pShield->pev->angles.x = 0;
	pShield->pev->angles.z = 0;

	pShield->pev->velocity = gpGlobals->v_forward * 400;

	pShield->SetThink(&CBaseEntity::SUB_Remove);
	pShield->pev->nextthink = gpGlobals->time + 300;

	pShield->SetCantBePickedUpByUser(this, 2.0);
}

/* <154b15> ../cstrike/dlls/player.cpp:3588 */
bool CBasePlayer::HasShield(void)
{
	return m_bOwnsShield;
}

/* <1615d2> ../cstrike/dlls/player.cpp:3593 */
NOXREF void CBasePlayer::ThrowPrimary(void)
{
	ThrowWeapon("weapon_m249");
	ThrowWeapon("weapon_g3sg1");
	ThrowWeapon("weapon_sg550");
	ThrowWeapon("weapon_awp");
	ThrowWeapon("weapon_mp5navy");
	ThrowWeapon("weapon_tmp");
	ThrowWeapon("weapon_p90");
	ThrowWeapon("weapon_ump45");
	ThrowWeapon("weapon_m4a1");
	ThrowWeapon("weapon_m3");
	ThrowWeapon("weapon_sg552");
	ThrowWeapon("weapon_scout");
	ThrowWeapon("weapon_galil");
	ThrowWeapon("weapon_famas");

	DropShield(true);
}

/* <154b6d> ../cstrike/dlls/player.cpp:3624 */
void CBasePlayer::AddAccount(int amount, bool bTrackChange)
{
	m_iAccount += amount;

	if (m_iAccount < 0)
		m_iAccount = 0;

	else if (m_iAccount > 16000)
		m_iAccount = 16000;

	MESSAGE_BEGIN(MSG_ONE, gmsgMoney, NULL, pev);
		WRITE_LONG(m_iAccount);
		WRITE_BYTE(bTrackChange);
	MESSAGE_END();
}

/* <154bf8> ../cstrike/dlls/player.cpp:3640 */
void CBasePlayer::ResetMenu(void)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, NULL, pev);
		WRITE_SHORT(0);
		WRITE_CHAR(0);
		WRITE_BYTE(0);
		WRITE_STRING("");
	MESSAGE_END();

#ifdef REGAMEDLL_FIXES
	m_iMenu = Menu_OFF;
#endif // REGAMEDLL_FIXES

}

/* <154c50> ../cstrike/dlls/player.cpp:3651 */
void CBasePlayer::SyncRoundTimer(void)
{
	float tmRemaining;
	CHalfLifeMultiplay *mp = g_pGameRules;

	if (mp->IsMultiplayer())
		tmRemaining = mp->TimeRemaining();
	else
		tmRemaining = 0;

	if (tmRemaining < 0)
		tmRemaining = 0;

	MESSAGE_BEGIN(MSG_ONE, gmsgRoundTime, NULL, pev);
		WRITE_SHORT(tmRemaining);
	MESSAGE_END();

	if (!mp->IsMultiplayer())
		return;

	if (mp->IsFreezePeriod() && TheTutor && !IsObserver())
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgBlinkAcct, NULL, pev);
			WRITE_BYTE( MONEY_BLINK_AMOUNT );
		MESSAGE_END();
	}

	if (mp->IsCareer())
	{
		int remaining;
		bool shouldCountDown = false;
		int fadeOutDelay = 0;

		if (tmRemaining)
			remaining = (int)((float_precision)TheCareerTasks->GetTaskTime() - (gpGlobals->time - mp->m_fRoundCount));

		if (remaining < 0)
			remaining = 0;

		if (mp->IsFreezePeriod())
			remaining = -1;

		if (TheCareerTasks->GetFinishedTaskTime())
			remaining = -TheCareerTasks->GetFinishedTaskTime();

		if (!mp->IsFreezePeriod() && !TheCareerTasks->GetFinishedTaskTime())
			shouldCountDown = true;

		if (!mp->IsFreezePeriod())
		{
			if (TheCareerTasks->GetFinishedTaskTime() || ((float_precision)TheCareerTasks->GetTaskTime() <= TheCareerTasks->GetRoundElapsedTime()))
				fadeOutDelay = 3;
		}

		if (!TheCareerTasks->GetFinishedTaskTime() || TheCareerTasks->GetFinishedTaskRound() == mp->m_iTotalRoundsPlayed)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgTaskTime, NULL, pev);
				WRITE_SHORT(remaining);
				WRITE_BYTE(shouldCountDown);
				WRITE_BYTE(fadeOutDelay);
			MESSAGE_END();
		}
	}
}

/* <154db6> ../cstrike/dlls/player.cpp:3711 */
void CBasePlayer::RemoveLevelText(void)
{
	ResetMenu();
}

void ShowMenu2(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, int fNeedMore, char *pszText)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, NULL, pPlayer->pev);
		WRITE_SHORT(bitsValidSlots);
		WRITE_CHAR(nDisplayTime);
		WRITE_BYTE(fNeedMore);
		WRITE_STRING(pszText);
	MESSAGE_END();
}

/* <154e29> ../cstrike/dlls/player.cpp:3721 */
void WINAPI_HOOK CBasePlayer::MenuPrint(const char *msg)
{
	const char *msg_portion = msg;
	char sbuf[MAX_BUFFER_MENU_BRIEFING + 1];

	while (strlen(msg_portion) >= MAX_BUFFER_MENU_BRIEFING)
	{
		Q_strncpy(sbuf, msg_portion, MAX_BUFFER_MENU_BRIEFING);
		sbuf[ MAX_BUFFER_MENU_BRIEFING ] = '\0';
		msg_portion += MAX_BUFFER_MENU_BRIEFING;

		MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, NULL, pev);
			WRITE_SHORT(0xFFFF);
			WRITE_CHAR(-1);
			WRITE_BYTE(1);	// multipart
			WRITE_STRING(sbuf);
		MESSAGE_END();
	}

	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, NULL, pev);
		WRITE_SHORT(0xFFFF);
		WRITE_CHAR(-1);
		WRITE_BYTE(0);	// multipart
		WRITE_STRING(msg_portion);
	MESSAGE_END();
}

/* <154f3d> ../cstrike/dlls/player.cpp:3753 */
void CBasePlayer::MakeVIP(void)
{
	pev->body = 0;
	m_iModelName = MODEL_VIP;

	SET_CLIENT_KEY_VALUE(entindex(), GET_INFO_BUFFER(edict()), "model", "vip");
	UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Became_VIP\"\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()));

	m_iTeam = CT;
	m_bIsVIP = true;
	m_bNotKilled = false;

	g_pGameRules->m_pVIP = this;
	g_pGameRules->m_iConsecutiveVIP = 1;
}

/* <154fe5> ../cstrike/dlls/player.cpp:3785 */
NOBODY void CBasePlayer::JoiningThink(void)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  3787
//		{
//			class CHalfLifeMultiplay *MPRules;           //  3843
//			RemoveLevelText(CBasePlayer *const this);  //  3815
//			{
//				edict_t *pentSpawnSpot;              //  3861
//				MAKE_STRING_CLASS(const char *str,
//							entvars_t *pev);  //  3857
//				VARS(edict_t *pent);  //  3862
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						edict_t *ed);  //  3866
//				Vector(Vector *const this,
//					const Vector &v);  //  3862
//				Vector(Vector *const this,
//					const Vector &v);  //  3862
//				entindex(CBaseEntity *const this);  //  3867
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						edict_t *ed);  //  3878
//				entindex(CBaseEntity *const this);  //  3879
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						edict_t *ed);  //  3884
//				edict(CBaseEntity *const this);  //  3885
//				ENTINDEX(edict_t *pEdict);  //  3885
//				HintMessage(CBasePlayer *const this,
//						const char *pMessage,
//						BOOL bDisplayIfPlayerDead,
//						BOOL bOverride);  //  3894
//			}
//			ResetMenu(CBasePlayer *const this);  //  3794
//			SendItemStatus(CBasePlayer *pPlayer);  //  3806
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  3798
//			AddAccount(CBasePlayer *const this,
//					int amount,
//					bool bTrackChange);  //  3850
//		}
//		{
//			class CBaseEntity *Target;                   //  3919
//			Vector CamAngles;                       //  3920
//			operator-(const Vector *const this,
//					const Vector &v);  //  3935
//			Normalize(const Vector *const this);  //  3936
//		}
//	}
}

/* <16076f> ../cstrike/dlls/player.cpp:3952 */
NOBODY void CBasePlayer::Disappear(void)
{
//	{
//		class CSound *pSound;                                //  3954
//		edict(CBaseEntity *const this);  //  3964
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  3987
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  3992
//		SendFOV(CBasePlayer *const this,
//			int fov);  //  3998
//		BuyZoneIcon_Clear(CBasePlayer *player);  //  4026
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  4017
//		SendItemStatus(CBasePlayer *pPlayer);  //  4021
//	}
}

/* <15f83d> ../cstrike/dlls/player.cpp:4039 */
NOBODY void CBasePlayer::PlayerDeathThink(void)
{
//	{
//		float flForward;                                      //  4041
//		BOOL fAnyButtonDown;                                  //  4088
//		HasWeapons(CBasePlayer *const this);  //  4056
//		StopAnimation(CBaseMonster *const this);  //  4084
//		Length(const Vector *const this);  //  4049
//		Normalize(const Vector *const this);  //  4053
//		operator*(float fl,
//				const Vector &v);  //  4053
//	}
}

/* <153042> ../cstrike/dlls/player.cpp:4134 */
void CBasePlayer::RoundRespawn_(void)
{
	m_canSwitchObserverModes = true;

	if (m_bJustKilledTeammate && CVAR_GET_FLOAT("mp_tkpunish"))
	{
		m_bJustKilledTeammate = false;
		CLIENT_COMMAND(edict(), "kill\n");
		m_bPunishedForTK = true;
	}
	if (m_iMenu != Menu_ChooseAppearance)
	{
		respawn(pev);

		pev->button = 0;
		pev->nextthink = -1;
	}

	if (m_pActiveItem)
	{
		if (m_pActiveItem->iItemSlot() == GRENADE_SLOT)
			SwitchWeapon(m_pActiveItem);
	}

	m_lastLocation[0] = 0;
}

/* <155577> ../cstrike/dlls/player.cpp:4172 */
NOXREF void CBasePlayer::StartDeathCam(void)
{
	if (pev->view_ofs == g_vecZero)
		return;

	StartObserver(pev->origin, pev->angles);

	if (TheBots)
		TheBots->OnEvent(EVENT_DEATH_CAMERA_START, this);
}

/* <155616> ../cstrike/dlls/player.cpp:4190 */
NOBODY void CBasePlayer::StartObserver(Vector vecPosition, Vector vecViewAngle)
{
//	{
//		int iFirstTime;                                       //  4194
//		class CHalfLifeMultiplay *mp;                        //  4246
//		entindex(CBaseEntity *const this);  //  4199

//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  4262
//		edict(CBaseEntity *const this);  //  4263
//		ENTINDEX(edict_t *pEdict);  //  4263
//		edict(CBaseEntity *const this);  //  4250
//	}
	
	// clear any clientside entities attached to this player
	MESSAGE_BEGIN(MSG_PAS, SVC_TEMPENTITY, pev->origin);
		WRITE_BYTE(TE_KILLPLAYERATTACHMENTS);
		WRITE_BYTE(entindex());
	MESSAGE_END();

	// Holster weapon immediately, to allow it to cleanup
	if (m_pActiveItem)
		m_pActiveItem->Holster();

	if (m_pTank)
	{
		m_pTank->Use(this, this);
		m_pTank = NULL;
	}

	// clear out the suit message cache so we don't keep chattering
	SetSuitUpdate();

	// Tell Ammo Hud that the player is dead
	MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, NULL, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(0xFF);
		WRITE_BYTE(0xFF);
	MESSAGE_END();

	// reset FOV
	SendFOV(0);

	// Setup flags
	m_iHideHUD = (HIDEHUD_WEAPONS | HIDEHUD_HEALTH);
	m_afPhysicsFlags |= PFLAG_OBSERVER;

	pev->effects = EF_NODRAW;
	pev->view_ofs = g_vecZero;

	pev->angles = pev->v_angle = vecViewAngle;

	pev->fixangle = 1;
	pev->solid = SOLID_NOT;

	pev->takedamage = DAMAGE_NO;
	pev->movetype = MOVETYPE_NONE;

	// Move them to the new position
	UTIL_SetOrigin(pev, vecPosition);

	m_afPhysicsFlags &= ~PFLAG_DUCKING;
	pev->flags &= ~FL_DUCKING;
	pev->health = 1;

	m_iObserverC4State = 0;
	m_bObserverHasDefuser = false;

	m_iObserverWeapon = 0;
	m_flNextObserverInput = 0;

	pev->iuser1 = OBS_NONE;

	static int iFirstTime = 1;
	CHalfLifeMultiplay *mp = g_pGameRules;

	if (iFirstTime && mp && mp->IsCareer() && !IsBot())
	{
		Observer_SetMode(OBS_CHASE_LOCKED);//
		CLIENT_COMMAND(edict(), "spec_autodirector_internal 1\n");
		iFirstTime = 0;
	}
	else
		Observer_SetMode(m_iObserverLastMode);//

	ResetMaxSpeed();

	// Tell all clients this player is now a spectator
	MESSAGE_BEGIN(MSG_ALL, gmsgSpectator);
		WRITE_BYTE(entindex());
		WRITE_BYTE(1);
	MESSAGE_END();
}

/* <1526e0> ../cstrike/dlls/player.cpp:4272 */
NOBODY bool CanSeeUseable(void)
{
//	{
//		Vector eye;                                     //  4274
//		FClassnameIs(entvars_t *pev,
//				const char *szClassname);  //  4276
//		{
//			TraceResult result;                           //  4279
//			Vector head;                            //  4280
//			Vector chest;                           //  4281
//			Vector knees;                           //  4282
//			operator+(const Vector *const this,
//					const Vector &v);  //  4280
//			operator+(const Vector *const this,
//					const Vector &v);  //  4281
//			operator+(const Vector *const this,
//					const Vector &v);  //  4282
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //  4274
//	}
}

/* <155815> ../cstrike/dlls/player.cpp:4307 */
NOBODY void CBasePlayer::PlayerUse(void)
{
//	{
//		bool useNewHostages;                                  //  4309
//		class CBaseEntity *pObject;                          //  4359
//		class CBaseEntity *pClosest;                         //  4360
//		Vector vecLOS;                                  //  4361
//		float flMaxDot;                                       //  4362
//		float flDot;                                          //  4363
//		empty(const class list<CNavArea*, std::allocator<CNavArea*> > *const this);  //  4309
//		{
//			class CBaseEntity *pTrain;                   //  4339
//			Instance(edict_t *pent);  //  4339
//			TrainSpeed(int iSpeed,
//					int iMax);  //  4344
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //  4348
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //  4352
//		}
//		{
//			class CBaseEntity *pTrain;                   //  4332
//			Instance(edict_t *pent);  //  4332
//		}
//		{
//			float const useHostageRange;                   //  4373
//			TraceResult result;                           //  4378
//			operator+(const Vector *const this,
//					const Vector &v);  //  4381
//			operator*(float fl,
//					const Vector &v);  //  4381
//			operator+(const Vector *const this,
//					const Vector &v);  //  4381
//			operator+(const Vector *const this,
//					const Vector &v);  //  4381
//			{
//				class CBaseEntity *hit;              //  4385
//				Instance(edict_t *pent);  //  4385
//				FClassnameIs(entvars_t *pev,
//						const char *szClassname);  //  4387
//			}
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  4403
//			operator+(const Vector *const this,
//					const Vector &v);  //  4405
//			operator-(const Vector *const this,
//					const Vector &v);  //  4405
//			NormalizeInPlace(Vector *const this);  //  4406
//			DotProduct(Vector &a,
//					const Vector &b);  //  4408
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //  4433
//		operator-(const Vector *const this,
//				const Vector &v);  //  4433
//		NormalizeInPlace(Vector *const this);  //  4434
//		DotProduct(Vector &a,
//				const Vector &b);  //  4436
//		{
//			int caps;                                     //  4455
//			EMIT_SOUND(edict_t *entity,
//					int channel,
//					const char *sample,
//					float volume,
//					float attenuation);  //  4458
//		}
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  4480
//	}
}

/* <155f41> ../cstrike/dlls/player.cpp:4486 */
NOBODY void CBasePlayer::HostageUsed(void)
{
//	HintMessage(CBasePlayer::HostageUsed(//			const char *pMessage,
//			BOOL bDisplayIfPlayerDead,
//			BOOL bOverride);  //  4493
//	HintMessage(CBasePlayer *const this,
//			const char *pMessage,
//			BOOL bDisplayIfPlayerDead,
//			BOOL bOverride);  //  4497
}

/* <153f69> ../cstrike/dlls/player.cpp:4507 */
NOBODY void CBasePlayer::Jump_(void)
{
//	{
//		Vector vecWallCheckDir;                         //  4509
//		Vector vecAdjustedVelocity;                     //  4510
//		Vector vecSpot;                                 //  4511
//		TraceResult tr;                                       //  4512
//		entvars_t *pevGround;                                //  4549
//	}
//	Jump(CBasePlayer *const this);  //  4507
}

/* <155fe2> ../cstrike/dlls/player.cpp:4565 */
NOBODY void FixPlayerCrouchStuck(edict_t *pPlayer)
{
//	{
//		TraceResult trace;                                    //  4567
//		{
//			int i;                                        //  4570
//		}
//	}
}

/* <153ef5> ../cstrike/dlls/player.cpp:4580 */
NOBODY void CBasePlayer::Duck_(void)
{
	if (pev->button & IN_DUCK)
		SetAnimation(PLAYER_WALK);
}

/* <150f8f> ../cstrike/dlls/player.cpp:4591 */
int CBasePlayer::Classify_(void)
{
	return CLASS_PLAYER;
}

/* <150fb7> ../cstrike/dlls/player.cpp:4597 */
void CBasePlayer::AddPoints_(int score, BOOL bAllowNegativeScore)
{
	if (score < 0 && !bAllowNegativeScore)
	{
		if (pev->frags < 0)
			return;

		if (-score > pev->frags)
			score = -pev->frags;
	}

	pev->frags += score;

	MESSAGE_BEGIN(MSG_BROADCAST, gmsgScoreInfo);
		WRITE_BYTE(ENTINDEX(edict()));
		WRITE_SHORT(pev->frags);
		WRITE_SHORT(m_iDeaths);
		WRITE_SHORT(0);
		WRITE_SHORT(m_iTeam);
	MESSAGE_END();
}

/* <15125b> ../cstrike/dlls/player.cpp:4626 */
NOBODY void CBasePlayer::AddPointsToTeam_(int score, BOOL bAllowNegativeScore)
{
//	{
//		int index;                                            //  4628
//		entindex(CBaseEntity *const this);  //  4628
//		{
//			int i;                                        //  4630
//			{
//				class CBaseEntity *pPlayer;          //  4632
//			}
//		}
//	}
}

/* <156047> ../cstrike/dlls/player.cpp:4645 */
NOBODY bool CBasePlayer::CanPlayerBuy(bool display)
{
//	{
//		bool result;                                          //  4647
//		class CHalfLifeMultiplay *mp;                        //  4666
//		int buyTime;                                          //  4668
//	}
}

/* <15f9ac> ../cstrike/dlls/player.cpp:4717 */
NOBODY void CBasePlayer::PreThink_(void)
{
//	{
//		int buttonsChanged;                                   //  4719
//		class CBaseEntity *pGroundEntity;                    //  4831
//		{
//			class CBaseEntity *pTrain;                   //  4845
//			float vel;                                    //  4846
//			{
//				TraceResult trainTrace;               //  4850
//			}
//		}
//	}
}

/* <156096> ../cstrike/dlls/player.cpp:5146 */
NOBODY void CBasePlayer::CheckTimeBasedDamage(void)
{
//	{
//		int i;                                                //  5148
//		BYTE bDuration;                                       //  5149
//		float gtbdPrev;                                       //  5151
//		{
//			int idif;                                     //  5190
//		}
//	}
}

/* <156112> ../cstrike/dlls/player.cpp:5312 */
NOXREF void CBasePlayer::UpdateGeigerCounter(void)
{
	if (gpGlobals->time < m_flgeigerDelay)
		return;

	m_flgeigerDelay = gpGlobals->time + 0.25;
	BYTE range = (byte)(m_flgeigerRange * 0.25);

	if (range != m_igeigerRangePrev)
	{
		m_igeigerRangePrev = range;

		MESSAGE_BEGIN(MSG_ONE, gmsgGeigerRange, NULL, pev);
			WRITE_BYTE(range);
		MESSAGE_END();
	}

	if (!RANDOM_LONG(0, 3))
		m_flgeigerRange = 1000.0;
}

/* <156189> ../cstrike/dlls/player.cpp:5352 */
NOBODY void CBasePlayer::CheckSuitUpdate(void)
{
//	{
//		int i;                                                //  5354
//		int isentence;                                        //  5355
//		int isearch;                                          //  5356
//		{
//			char sentence;                                //  5390
//		}
//	}
}

/* <156201> ../cstrike/dlls/player.cpp:5414 */
void CBasePlayer::SetSuitUpdate(char *name, int fgroup, int iNoRepeatTime)
{
	;
}

/* <15623f> ../cstrike/dlls/player.cpp:5519 */
NOXREF void CBasePlayer::CheckPowerups(entvars_t *pev)
{
	if (pev->health > 0.0f)
		pev->modelindex = m_modelIndexPlayer;
}

/* <15626b> ../cstrike/dlls/player.cpp:5531 */
void CBasePlayer::SetNewPlayerModel(const char *modelName)
{
	SET_MODEL(edict(), modelName);
	m_modelIndexPlayer = pev->modelindex;
}

/* <1562a4> ../cstrike/dlls/player.cpp:5543 */
NOBODY void CBasePlayer::UpdatePlayerSound(void)
{
//	{
//		int iBodyVolume;                                      //  5545
//		int iVolume;                                          //  5546
//		class CSound *pSound;                                //  5547
//		edict(CBaseEntity *const this);  //  5549
//		Length(const Vector *const this);  //  5564
//	}
}

/* <15a182> ../cstrike/dlls/player.cpp:5667 */
NOBODY void CBasePlayer::PostThink_(void)
{
//	
//pt_end:                                                               //  5767
//	{
//		float flFallDamage;                                   //  5712
//		VARS(EOFFSET eoffset);  //  5723
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  5717
//		VARS(EOFFSET eoffset);  //  5723
//	}
//	SetAnimation(CBasePlayer *const this,
//			PLAYER_ANIM playerAnim);  //  5733
//	{
//		int i;                                                //  5771
//		{
//			class CBasePlayerItem *pPlayerItem;          //  5775
//			{
//				class CBasePlayerWeapon *gun;        //  5779
//			}
//		}
//	}
//	SetAnimation(CBasePlayer *const this,
//			PLAYER_ANIM playerAnim);  //  5752
//	CheckPowerups(CBasePlayer *const this,
//			entvars_t *pev);  //  5761
//	SetAnimation(CBasePlayer *const this,
//			PLAYER_ANIM playerAnim);  //  5757
}

/* <14e39d> ../cstrike/dlls/player.cpp:5837 */
NOXREF BOOL IsSpawnPointValid(CBaseEntity *pPlayer, CBaseEntity *pSpot)
{
	CBaseEntity *ent = NULL;

	if (!pSpot->IsTriggered(pPlayer))
		return FALSE;

	while ((ent = UTIL_FindEntityInSphere(ent, pSpot->pev->origin, 64)) != NULL)
	{
		if (ent->IsPlayer() && ent != pPlayer)
			return FALSE;
	}

	return TRUE;
}

/* <1563a8> ../cstrike/dlls/player.cpp:5879 */
NOBODY void InitZombieSpawns(void)
{
//	{
//		class CBaseEntity *spot;                             //  5884
//		operator!=(const Vector *const this,
//				const Vector &v);  //  5889
//		Invalidate(CountdownTimer *const this);  //  5892
//	}
}

/* <14e440> ../cstrike/dlls/player.cpp:5906 */
CBaseEntity *FindZombieSpawn(CBaseEntity *player, bool forceSpawn)
{
	return NULL;
}

/* <15645f> ../cstrike/dlls/player.cpp:6060 */
edict_t *EntSelectSpawnPoint(CBaseEntity *pPlayer)
{
//	
//CTSpawn:                                                              //  6095
//	
//ReturnSpot:                                                           //  6222
//	{
//		class CBaseEntity *pSpot;                            //  6062
//		edict_t *player;                                     //  6063
//		edict(CBaseEntity *const this);  //  6065
//		FNullEnt(CBaseEntity *ent);  //  6071
//		FNullEnt(CBaseEntity *ent);  //  6085
//		{
//			class CBaseEntity *pFirstSpot;               //  6116
//			FNullEnt(CBaseEntity *ent);  //  6113
//			IsSpawnPointValid(CBaseEntity *pPlayer,
//						class CBaseEntity *pSpot);  //  6123
//			FNullEnt(CBaseEntity *ent);  //  6140
//			{
//				class CBaseEntity *ent;              //  6142
//				edict(CBaseEntity *const this);  //  6146
//				VARS(edict_t *pent);  //  6147
//				INDEXENT(int iEdictNum);  //  6147
//				INDEXENT(int iEdictNum);  //  6147
//				VARS(edict_t *pent);  //  6147
//			}
//			operator==(const Vector *const this,
//					const Vector &v);  //  6125
//		}
//		{
//			class CBaseEntity *pFirstSpot;               //  6168
//			FNullEnt(CBaseEntity *ent);  //  6165
//			IsSpawnPointValid(CBaseEntity *pPlayer,
//						class CBaseEntity *pSpot);  //  6175
//			FNullEnt(CBaseEntity *ent);  //  6192
//			{
//				class CBaseEntity *ent;              //  6194
//				edict(CBaseEntity *const this);  //  6198
//				VARS(edict_t *pent);  //  6199
//				INDEXENT(int iEdictNum);  //  6199
//				INDEXENT(int iEdictNum);  //  6199
//				VARS(edict_t *pent);  //  6199
//			}
//			operator==(const Vector *const this,
//					const Vector &v);  //  6177
//		}
//		FNullEnt(CBaseEntity *ent);  //  6074
//		FNullEnt(CBaseEntity *ent);  //  6218
//		FNullEnt(CBaseEntity *ent);  //  6223
//		INDEXENT(int iEdictNum);  //  6226
//		edict(CBaseEntity *const this);  //  6234
//		FNullEnt(CBaseEntity *ent);  //  6212
//	}
}

/* <15331b> ../cstrike/dlls/player.cpp:6237 */
void SetScoreAttrib(CBasePlayer *dest, CBasePlayer *src)
{
	int state = 0;
	if (src->pev->deadflag != DEAD_NO)
		state |= SCORE_STATUS_DEAD;

	if (src->m_bHasC4)
		state |= SCORE_STATUS_BOMB;

	if (src->m_bIsVIP)
		state |= SCORE_STATUS_VIP;

	if (gmsgScoreAttrib)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgScoreAttrib, NULL, dest->pev);
			WRITE_BYTE(src->entindex());
			WRITE_BYTE(state);
		MESSAGE_END();
	}
}

/* <15fdba> ../cstrike/dlls/player.cpp:6264 */
NOBODY void CBasePlayer::Spawn_(void)
{
//	{
//		int i;                                                //  6394
//		MAKE_STRING_CLASS(const char *str,
//					entvars_t *pev);  //  6275
//		ResetStamina(CBasePlayer *const this);  //  6308
//		edict(CBaseEntity *const this);  //  6314
//		edict(CBaseEntity *const this);  //  6315
//		edict(CBaseEntity *const this);  //  6340
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  6461
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  6461
//		{
//			int i;                                        //  6497
//		}
//		SendItemStatus(CBasePlayer *pPlayer);  //  6502
//		{
//			int i;                                        //  6507
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  6512
//		{
//			class CBasePlayer *pObserver;                //  6520
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  6523
//		}
//		HintMessage(CBasePlayer *const this,
//				const char *pMessage,
//				BOOL bDisplayIfPlayerDead,
//				BOOL bOverride);  //  6547
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  6553
//		entindex(CBaseEntity *const this);  //  6554
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  6568
//		edict(CBaseEntity *const this);  //  6569
//		ENTINDEX(edict_t *pEdict);  //  6569
//		{
//			char *infobuffer;                            //  6580
//			edict(CBaseEntity *const this);  //  6580
//			FStrEq(const char *sz1,
//				const char *sz2);  //  6582
//			entindex(CBaseEntity *const this);  //  6584
//		}
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  6591
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  6463
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  6463
//		RemoveLevelText(CBasePlayer *const this);  //  6439
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  6374
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  6365
//	}
}

/* <153555> ../cstrike/dlls/player.cpp:6620 */
NOBODY void CBasePlayer::Precache_(void)
{
}

/* <151a77> ../cstrike/dlls/player.cpp:6671 */
NOBODY int CBasePlayer::Save_(CSave &save)
{
//	Save(CBasePlayer *const this,
//		class CSave &save);  //  6671
}

/* <153355> ../cstrike/dlls/player.cpp:6685 */
void CBasePlayer::SetScoreboardAttributes(CBasePlayer *destination)
{
	if (destination != NULL)
	{
		SetScoreAttrib(destination, this);
		return;
	}

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *player = (CBasePlayer *)UTIL_PlayerByIndex(i);

		if (player && !FNullEnt(player->edict()))
			SetScoreboardAttributes(player);
	}
}

/* <156e88> ../cstrike/dlls/player.cpp:6712 */
NOBODY void CBasePlayer::RenewItems(void)
{
}

/* <156b9b> ../cstrike/dlls/player.cpp:6718 */
NOBODY int CBasePlayer::Restore_(CRestore &restore)
{
//	{
//		int status;                                           //  6723
//		SAVERESTOREDATA *pSaveData;                          //  6725
//	}
//	Restore(CBasePlayer *const this,
//		class CRestore &restore);  //  6718
}

/* <156eab> ../cstrike/dlls/player.cpp:6771 */
NOBODY void CBasePlayer::Reset(void)
{
//	AddAccount(CBasePlayer::Reset(//			int amount,
//			bool bTrackChange);  //  6776
//	RemoveShield(CBasePlayer *const this);  //  6779
//	AddAccount(CBasePlayer *const this,
//			int amount,
//			bool bTrackChange);  //  6782
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //  6784
//	edict(CBaseEntity *const this);  //  6785
//	ENTINDEX(edict_t *pEdict);  //  6785
}

/* <157066> ../cstrike/dlls/player.cpp:6794 */
NOBODY void CBasePlayer::SelectNextItem(int iItem)
{
//	{
//		class CBasePlayerItem *pItem;                        //  6796
//		{
//			class CBasePlayerItem *pLast;                //  6812
//		}
//		ResetAutoaim(CBasePlayer *const this);  //  6823
//		{
//			class CBasePlayerWeapon *pWeapon;            //  6833
//		}
//		UpdateShieldCrosshair(CBasePlayer *const this,
//					bool draw);  //  6844
//	}
}

/* <15714a> ../cstrike/dlls/player.cpp:6851 */
NOBODY void CBasePlayer::SelectItem(const char *pstr)
{
//	{
//		class CBasePlayerItem *pItem;                        //  6856
//		{
//			int i;                                        //  6858
//			FClassnameIs(entvars_t *pev,
//					const char *szClassname);  //  6866
//		}
//		ResetAutoaim(CBasePlayer *const this);  //  6883
//		{
//			class CBasePlayerWeapon *pWeapon;            //  6896
//			UpdateShieldCrosshair(CBasePlayer *const this,
//						bool draw);  //  6901
//		}
//	}
}

/* <157268> ../cstrike/dlls/player.cpp:6909 */
void CBasePlayer::SelectLastItem(void)
{
	if (m_pActiveItem && !m_pActiveItem->CanHolster())
		return;

	if (!m_pLastItem || m_pLastItem == m_pActiveItem)
	{
		for (int i = 1; i < MAX_ITEMS; i++)
		{
			CBasePlayerItem *pItem = m_rgpPlayerItems[i];
			if(pItem && pItem != m_pActiveItem)
			{
				m_pLastItem = pItem;
				break;
			}
		}
	}

	if(!m_pLastItem || m_pLastItem == m_pActiveItem)
		return;

	ResetAutoaim();

	if (m_pActiveItem)
		m_pActiveItem->Holster();

	if (HasShield())
	{
		CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)m_pActiveItem;

		if (m_pActiveItem)
			pWeapon->m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

		m_bShieldDrawn = false;
	}

	CBasePlayerItem *pTemp = m_pActiveItem;

	m_pActiveItem = m_pLastItem;
	m_pLastItem = pTemp;

	m_pActiveItem->Deploy();
	m_pActiveItem->UpdateItemInfo();

	UpdateShieldCrosshair(true);

	ResetMaxSpeed();
}

/* <15733a> ../cstrike/dlls/player.cpp:6967 */
NOXREF BOOL CBasePlayer::HasWeapons(void)
{
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		if (m_rgpPlayerItems[i])
			return TRUE;
	}
	return FALSE;
}

/* <157372> ../cstrike/dlls/player.cpp:6982 */
NOBODY void CBasePlayer::SelectPrevItem(int iItem)
{
}

/* <15106c> ../cstrike/dlls/player.cpp:6987 */
NOBODY const char *CBasePlayer::TeamID_(void)
{
}

/* <1573aa> ../cstrike/dlls/player.cpp:7010 */
NOBODY void CSprayCan::Spawn(entvars_t *pevOwner)
{
//	operator+(const Vector *const this,
//			const Vector &v);  //  7012
//	EMIT_SOUND(edict_t *entity,
//			int channel,
//			const char *sample,
//			float volume,
//			float attenuation);  //  7018
}

/* <151815> ../cstrike/dlls/player.cpp:7021 */
NOBODY void CSprayCan::Think_(void)
{
//	{
//		TraceResult tr;                                       //  7023
//		int playernum;                                        //  7024
//		int nFrames;                                          //  7025
//		class CBasePlayer *pPlayer;                          //  7026
//		GET_PRIVATE(edict_t *pent);  //  7028
//		GetCustomDecalFrames(CBasePlayer *const this);  //  7031
//		ENTINDEX(edict_t *pEdict);  //  7035
//		operator*(const Vector *const this,
//				float fl);  //  7038
//		operator+(const Vector *const this,
//				const Vector &v);  //  7038
//	}
}

/* <157481> ../cstrike/dlls/player.cpp:7064 */
NOBODY void CBloodSplat::Spawn(entvars_t *pevOwner)
{
//	operator+(const Vector *const this,
//			const Vector &v);  //  7066
}

/* <151758> ../cstrike/dlls/player.cpp:7074 */
NOBODY void CBloodSplat::Spray(void)
{
//	{
//		TraceResult tr;                                       //  7076
//		operator*(const Vector *const this,
//				float fl);  //  7081
//		operator+(const Vector *const this,
//				const Vector &v);  //  7081
//	}
}

/* <1574d3> ../cstrike/dlls/player.cpp:7093 */
void CBasePlayer::GiveNamedItem(const char *pszName)
{
	string_t istr = MAKE_STRING(pszName);
	edict_t *pent = CREATE_NAMED_ENTITY(istr);
	
	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in GiveNamedItem!\n");
		return;
	}

	VARS(pent)->origin = pev->origin;
	pent->v.spawnflags |= SF_NORESPAWN;

	DispatchSpawn(pent);
	DispatchTouch(pent, ENT(pev));
}

/* <157568> ../cstrike/dlls/player.cpp:7114 */
CBaseEntity *FindEntityForward(CBaseEntity *pMe)
{
//	{
//		TraceResult tr;                                       //  7116
//		edict(CBaseEntity *const this);  //  7119
//		operator+(const Vector *const this,
//				const Vector &v);  //  7119
//		operator*(const Vector *const this,
//				float fl);  //  7119
//		operator+(const Vector *const this,
//				const Vector &v);  //  7119
//		operator+(const Vector *const this,
//				const Vector &v);  //  7119
//		FNullEnt(const edict_t *pent);  //  7120
//		{
//			class CBaseEntity *pHit;                     //  7122
//			Instance(edict_t *pent);  //  7122
//		}
//	}
}

/* <15777b> ../cstrike/dlls/player.cpp:7129 */
NOXREF BOOL CBasePlayer::FlashlightIsOn(void)
{
	return pev->effects & EF_DIMLIGHT;
}

/* <15779e> ../cstrike/dlls/player.cpp:7135 */
void CBasePlayer::FlashlightTurnOn(void)
{
	if (!g_pGameRules->FAllowFlashlight())
		return;

	//TODO: check it
	//if (pev->weapons < 0)
	if (pev->weapons & (1 << WEAPON_SUIT))
	{
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/flashlight1.wav", VOL_NORM, ATTN_NORM);

		pev->effects |= EF_DIMLIGHT;

		MESSAGE_BEGIN(MSG_ONE, gmsgFlashlight, NULL, pev);
			WRITE_BYTE(1);
			WRITE_BYTE(m_iFlashBattery);
		MESSAGE_END();

		m_flFlashLightTime = gpGlobals->time + 1.2;
	}
}

/* <157816> ../cstrike/dlls/player.cpp:7157 */
NOBODY void CBasePlayer::FlashlightTurnOff(void)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			entvars_t *ent);  //  7161
}

/* <158ae7> ../cstrike/dlls/player.cpp:7179 */
NOBODY void CBasePlayer::ForceClientDllUpdate(void)
{
}

/* <157f8d> ../cstrike/dlls/player.cpp:7202 */
NOBODY void CBasePlayer::ImpulseCommands_(void)
{
//	{
//		TraceResult tr;                                       //  7204
//		int iImpulse;                                         //  7209
//		{
//			int iOn;                                      //  7215
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  7229
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //  7258
//		operator*(const Vector *const this,
//				float fl);  //  7258
//		operator+(const Vector *const this,
//				const Vector &v);  //  7258
//		operator+(const Vector *const this,
//				const Vector &v);  //  7258
//		{
//			class CSprayCan *pCan;                       //  7263
//			GetClassPtr<CSprayCan>(CSprayCan *a);  //  7263
//		}
//		FlashlightTurnOff(CBasePlayer *const this);  //  7241
//	}
}

/* <15786e> ../cstrike/dlls/player.cpp:7280 */
NOBODY void CBasePlayer::CheatImpulseCommands(int iImpulse)
{
//	{
//		class CBaseEntity *pEntity;                          //  7288
//		TraceResult tr;                                       //  7289
//		{
//			TraceResult tr;                               //  7438
//			Vector dir;                             //  7439
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //  7436
//			{
//				int r;                                //  7440
//				{
//					float bloodRange;             //  7442
//					{
//						int i;                //  7444
//						NormalizeInPlace(Vector *const this);  //  7456
//						operator+(const Vector *const this,
//								const Vector &v);  //  7459
//						operator*(const Vector *const this,
//								float fl);  //  7459
//						operator+(const Vector *const this,
//								const Vector &v);  //  7459
//						operator+(const Vector *const this,
//								const Vector &v);  //  7459
//					}
//				}
//			}
//			AddAccount(CBasePlayer *const this,
//					int amount,
//					bool bTrackChange);  //  7314
//			{
//				TraceResult tr;                       //  7381
//				edict_t *pWorld;                     //  7383
//				Vector start;                   //  7385
//				Vector end;                     //  7386
//				const char *pTextureName;           //  7390
//				operator+(const Vector *const this,
//						const Vector &v);  //  7385
//				operator*(const Vector *const this,
//						float fl);  //  7386
//				operator+(const Vector *const this,
//						const Vector &v);  //  7386
//			}
//			{
//				class CBaseMonster *pMonster;        //  7331
//			}
//			operator+(const Vector *const this,
//					const Vector &v);  //  7418
//			operator*(const Vector *const this,
//					float fl);  //  7418
//			operator+(const Vector *const this,
//					const Vector &v);  //  7418
//			operator+(const Vector *const this,
//					const Vector &v);  //  7418
//			{
//				class CBloodSplat *pBlood;           //  7422
//				GetClassPtr<CBloodSplat>(CBloodSplat *a);  //  7422
//				Spawn(CBloodSplat *const this,
//					entvars_t *pevOwner);  //  7423
//			}
//			Vector(Vector *const this,
//				float X,
//				float Y,
//				float Z);  //  7302
//			operator*(const Vector *const this,
//					float fl);  //  7303
//			operator+(const Vector *const this,
//					const Vector &v);  //  7303
//		}
//	}
}

/* <158256> ../cstrike/dlls/player.cpp:7474 */
NOBODY void OLD_CheckBuyZone(CBasePlayer *player)
{
//	{
//		const char *pszSpawnClass;                          //  7476
//		{
//			class CBaseEntity *pSpot;                    //  7497
//		}
//	}
}

/* <14e5a9> ../cstrike/dlls/player.cpp:7514 */
NOBODY void OLD_CheckBombTarget(CBasePlayer *player)
{
//	{
//		class CBaseEntity *pSpot;                            //  7516
//	}
}

/* <14e5d5> ../cstrike/dlls/player.cpp:7532 */
NOBODY void OLD_CheckRescueZone(CBasePlayer *player)
{
//	{
//		class CBaseEntity *pSpot;                            //  7534
//	}
}

/* <1582e9> ../cstrike/dlls/player.cpp:7553 */
NOBODY void CBasePlayer::HandleSignals(void)
{
//	{
//		int changed;                                          //  7576
//		int state;                                            //  7577
//		{
//			class CHalfLifeMultiplay *mp;                //  7563
//			OLD_CheckRescueZone(CBasePlayer *player);  //  7572
//			OLD_CheckBuyZone(CBasePlayer *player);  //  7566
//			OLD_CheckBombTarget(CBasePlayer *player);  //  7569
//		}
//		Update(CUnifiedSignals *const this);  //  7576
//		BuyZoneIcon_Set(CBasePlayer *player);  //  7582
//		BombTargetFlash_Set(CBasePlayer *player);  //  7590
//		RescueZoneIcon_Set(CBasePlayer *player);  //  7598
//		EscapeZoneIcon_Set(CBasePlayer *player);  //  7606
//		VIP_SafetyZoneIcon_Set(CBasePlayer *player);  //  7614
//		VIP_SafetyZoneIcon_Clear(CBasePlayer *player);  //  7616
//		BuyZoneIcon_Clear(CBasePlayer *player);  //  7584
//		EscapeZoneIcon_Clear(CBasePlayer *player);  //  7608
//		RescueZoneIcon_Clear(CBasePlayer *player);  //  7600
//		BombTargetFlash_Clear(CBasePlayer *player);  //  7592
//	}
}

/* <15325f> ../cstrike/dlls/player.cpp:7625 */
BOOL CBasePlayer::AddPlayerItem_(CBasePlayerItem *pItem)
{
	CBasePlayerItem *pInsert = m_rgpPlayerItems[ pItem->iItemSlot() ];
	while (pInsert != NULL)
	{
		if (FClassnameIs(pInsert->pev, STRING(pItem->pev->classname)))
		{
			if (pItem->AddDuplicate(pInsert))
			{
				g_pGameRules->PlayerGotWeapon(this, pItem);
				pItem->CheckRespawn();
				pItem->UpdateItemInfo();

				if (m_pActiveItem)
					m_pActiveItem->UpdateItemInfo();

				pItem->Kill();
			}
			else if (gEvilImpulse101)
				pItem->Kill();

			return FALSE;
		}

		pInsert = pInsert->m_pNext;
	}
	if (pItem->AddToPlayer(this))
	{
		g_pGameRules->PlayerGotWeapon(this, pItem);

		if (pItem->iItemSlot() == PRIMARY_WEAPON_SLOT)
			m_bHasPrimary = true;

		pItem->CheckRespawn();
		pItem->m_pNext = m_rgpPlayerItems[ pItem->iItemSlot() ];
		m_rgpPlayerItems[ pItem->iItemSlot() ] = pItem;

		if (HasShield())
			pev->gamestate = 0;

		if (g_pGameRules->FShouldSwitchWeapon(this, pItem))
		{
			if (!m_bShieldDrawn)
				SwitchWeapon(pItem);
		}
		return TRUE;
	}
	else if (gEvilImpulse101)
		pItem->Kill();

	return FALSE;
}

/* <1534bd> ../cstrike/dlls/player.cpp:7692 */
BOOL CBasePlayer::RemovePlayerItem_(CBasePlayerItem *pItem)
{
	if (m_pActiveItem == pItem)
	{
		ResetAutoaim();
		pItem->pev->nextthink = 0;

		pItem->SetThink(NULL);
		m_pActiveItem = NULL;

		pev->viewmodel = 0;
		pev->weaponmodel = 0;
	}
	else if (m_pLastItem == pItem)
		m_pLastItem = NULL;

	CBasePlayerItem *pPrev = m_rgpPlayerItems[pItem->iItemSlot()];
	if (pPrev == pItem)
	{
		m_rgpPlayerItems[pItem->iItemSlot()] = pItem->m_pNext;
		return TRUE;
	}

	while (pPrev && pPrev->m_pNext != pItem)
		pPrev = pPrev->m_pNext;

	if (pPrev)
	{
		pPrev->m_pNext = pItem->m_pNext;
		return TRUE;
	}
	return FALSE;
}

/* <15997b> ../cstrike/dlls/player.cpp:7731 */
int CBasePlayer::GiveAmmo_(int iCount, char *szName, int iMax)
{
	if (pev->flags & FL_SPECTATOR || !szName || !g_pGameRules->CanHaveAmmo(this, szName, iMax))
		return -1;

	int i = GetAmmoIndex(szName);
	if (i < 0 || i >= MAX_AMMO_SLOTS)
		return -1;

	int iAdd = min(iCount, iMax - m_rgAmmo[i]);
	if (iAdd < 1)
		return i;

	m_rgAmmo[i] += iAdd;
	if (gmsgAmmoPickup)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgAmmoPickup, NULL, pev);
			WRITE_BYTE(GetAmmoIndex(szName)); 
			WRITE_BYTE(iAdd);
		MESSAGE_END();
	}
	TabulateAmmo();
	return i;
}

/* <158b10> ../cstrike/dlls/player.cpp:7784 */
NOBODY void CBasePlayer::ItemPreFrame(void)
{
}

/* <158b33> ../cstrike/dlls/player.cpp:7805 */
NOBODY void CBasePlayer::ItemPostFrame(void)
{
//	{
//		int fInSelect;                                        //  7807
//	}
}

/* <158b71> ../cstrike/dlls/player.cpp:7834 */
int CBasePlayer::AmmoInventory(int iAmmoIndex)
{
	if (iAmmoIndex == -1)
		return -1;

	return m_rgAmmo[iAmmoIndex];
}

/* <158b9d> ../cstrike/dlls/player.cpp:7844 */
int CBasePlayer::GetAmmoIndex(const char *psz)
{
	if (!psz)
		return -1;

	for (int i = 1; i < MAX_AMMO_SLOTS; i++)
	{
#ifndef HOOK_GAMEDLL
		if (!AmmoInfoArray[i].pszName)
			continue;

		if (!Q_stricmp(psz, CBasePlayerItem::AmmoInfoArray[i].pszName))
#else
		if (!(*CBasePlayerItem::pAmmoInfoArray)[i].pszName)
			continue;

		if (!Q_stricmp(psz, (*CBasePlayerItem::pAmmoInfoArray)[i].pszName))
#endif // HOOK_GAMEDLL
			return i;
	}
	return -1;
}

/* <158bf7> ../cstrike/dlls/player.cpp:7865 */
NOBODY void CBasePlayer::SendAmmoUpdate(void)
{
//	{
//		int i;                                                //  7867
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  7877
//	}
}

/* <158d4b> ../cstrike/dlls/player.cpp:7885 */
NOBODY void CBasePlayer::SendHostagePos(void)
{
//	{
//		class CBaseEntity *pHostage;                         //  7887
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  7894
//	}
}

/* <158c66> ../cstrike/dlls/player.cpp:7908 */
void CBasePlayer::SendHostageIcons(void)
{
	CBaseEntity *pHostage = NULL;
	int numHostages = 0;
	char buf[16];

	if (UTIL_IsGame("czero"))
	{
		while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")) != NULL)
		{
			if (pHostage && pHostage->pev->deadflag == DEAD_NO)
				numHostages++;
		}

		if (numHostages > 4)
			numHostages = 4;

		Q_snprintf(buf, ARRAYSIZE(buf), "hostage%d", numHostages);

		if(numHostages)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgScenarioIcon, NULL, pev);
				WRITE_BYTE(1);
				WRITE_STRING(buf);
				WRITE_BYTE(0);
			MESSAGE_END();
		}
		else
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgScenarioIcon, NULL, pev);
				WRITE_BYTE(0);
			MESSAGE_END();
		}
	}
}

/* <158dc6> ../cstrike/dlls/player.cpp:7949 */
NOBODY void CBasePlayer::SendWeatherInfo(void)
{
//	{
//		class CBaseEntity *pPoint;                           //  7956
//		class CBaseEntity *pPoint2;                          //  7957
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  7964
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  7978
//	}
}

/* <1510bc> ../cstrike/dlls/player.cpp:8330 */
NOBODY BOOL CBasePlayer::FBecomeProne_(void)
{
}

/* <158e8a> ../cstrike/dlls/player.cpp:8341 */
NOBODY void CBasePlayer::BarnacleVictimBitten(entvars_t *pevBarnacle)
{
}

/* <158ec3> ../cstrike/dlls/player.cpp:8350 */
NOBODY void CBasePlayer::BarnacleVictimReleased(void)
{
}

/* <1510e4> ../cstrike/dlls/player.cpp:8360 */
NOBODY int CBasePlayer::Illumination_(void)
{
//	{
//		int iIllum;                                           //  8362
//		Illumination(CBaseEntity *const this);  //  8362
//	}
}

/* <158eeb> ../cstrike/dlls/player.cpp:8371 */
NOBODY void CBasePlayer::EnableControl(BOOL fControl)
{
}

/* <151142> ../cstrike/dlls/player.cpp:8387 */
void CBasePlayer::ResetMaxSpeed_(void)
{
	float speed = 240.0f;

	if (IsObserver())
		speed = 900.0f;

	else if (g_pGameRules->IsMultiplayer() && g_pGameRules->IsFreezePeriod())
		speed = 1.0f;

	else if (m_bIsVIP)
		speed = 227.0f;

	else if (m_pActiveItem)
		speed = m_pActiveItem->GetMaxSpeed();

	pev->maxspeed = speed;
}

/* <158f23> ../cstrike/dlls/player.cpp:8436 */
bool CBasePlayer::HintMessage(const char *pMessage, BOOL bDisplayIfPlayerDead, BOOL bOverride)
{
	if (!bDisplayIfPlayerDead && !IsAlive())
		return false;

	if (bOverride || m_bShowHints)
		return m_hintMessageQueue.AddMessage(pMessage, 6.0, true, NULL);

	return true;
}

/* <1513f7> ../cstrike/dlls/player.cpp:8473 */
Vector CBasePlayer::GetAutoaimVector_(float flDelta)
{
	Vector vecSrc;
	BOOL m_fOldTargeting;
	Vector angles;

	if (g_iSkillLevel == SKILL_HARD)
	{
		UTIL_MakeVectors(pev->v_angle + pev->punchangle);
		return gpGlobals->v_forward;
	}

	vecSrc = GetGunPosition();
	m_fOldTargeting = m_fOnTarget;
	m_vecAutoAim = Vector(0, 0, 0);
	angles = AutoaimDeflection(vecSrc, 8192, flDelta);

	if (g_pGameRules->AllowAutoTargetCrosshair())
	{
		if (m_fOldTargeting != m_fOnTarget)
			m_pActiveItem->UpdateItemInfo();
	}
	else
		m_fOnTarget = FALSE;

	if (angles.x > 180.0f)
		angles.x -= 360.0f;
	if (angles.x < -180.0f)
		angles.x += 360.0f;

	if (angles.y > 180.0f)
		angles.y -= 360.0f;
	if (angles.y < -180.0f)
		angles.y += 360.0f;

	if (angles.x > 25.0f)
		angles.x = 25.0f;
	if (angles.x < -25.0f)
		angles.x = -25.0f;

	if (angles.y > 12.0f)
		angles.y = 12.0f;
	if (angles.y < -12.0f)
		angles.y = -12.0f;

	if (g_iSkillLevel == SKILL_EASY)
		m_vecAutoAim = m_vecAutoAim * 0.67f + angles * 0.33f;
	else
		m_vecAutoAim = angles * 0.9f;

	if (sv_aim && sv_aim->value > 0.0f)
	{
		if (m_vecAutoAim.x != m_lastx || m_vecAutoAim.y != m_lasty)
		{
			SET_CROSSHAIRANGLE(ENT(pev), -m_vecAutoAim.x, m_vecAutoAim.y);

			m_lastx = m_vecAutoAim.x;
			m_lasty = m_vecAutoAim.y;
		}
	}
	UTIL_MakeVectors(pev->v_angle + pev->punchangle + m_vecAutoAim);
	return gpGlobals->v_forward;
}

/* <158f62> ../cstrike/dlls/player.cpp:8553 */
Vector CBasePlayer::AutoaimDeflection(Vector &vecSrc, float flDist, float flDelta)
{
	m_fOnTarget = FALSE;
	return g_vecZero;
}

/* <158fc1> ../cstrike/dlls/player.cpp:8686 */
void CBasePlayer::ResetAutoaim(void)
{
	if (m_vecAutoAim.x != 0.0f || m_vecAutoAim.y != 0.0f)
	{
		m_vecAutoAim = Vector(0, 0, 0);
		SET_CROSSHAIRANGLE(ENT(pev), 0, 0);
	}
	m_fOnTarget = FALSE;
}

// UNDONE: Determine real frame limit, 8 is a placeholder.
// Note: -1 means no custom frames present.

/* <158ff6> ../cstrike/dlls/player.cpp:8704 */
void CBasePlayer::SetCustomDecalFrames(int nFrames)
{
	if (nFrames > 0 && nFrames < 8)
		m_nCustomSprayFrames = nFrames;
	else
		m_nCustomSprayFrames = -1;
}

/* <15902e> ../cstrike/dlls/player.cpp:8720 */
NOBODY int CBasePlayer::GetCustomDecalFrames(void)
{
}

/* <151183> ../cstrike/dlls/player.cpp:8731 */
NOBODY void CBasePlayer::Blind_(float duration, float holdTime, float fadeTime, int alpha)
{
}

/* <159051> ../cstrike/dlls/player.cpp:8741 */
NOBODY void CBasePlayer::InitStatusBar(void)
{
}

/* <159079> ../cstrike/dlls/player.cpp:8749 */
NOBODY void CBasePlayer::UpdateStatusBar(void)
{
//	{
//		int newSBarState;                                     //  8751
//		char sbuf0;                                           //  8752
//		TraceResult tr;                                       //  8758
//		Vector vecSrc;                                  //  8762
//		Vector vecEnd;                                  //  8763
//		BOOL bForceResend;                                    //  8890
//		operator+(const Vector *const this,
//				const Vector &v);  //  8760
//		operator*(const Vector *const this,
//				float fl);  //  8763
//		operator+(const Vector *const this,
//				const Vector &v);  //  8763
//		FNullEnt(const edict_t *pent);  //  8769
//		{
//			class CBaseEntity *pEntity;                  //  8771
//			bool isVisiblePlayer;                         //  8773
//			Instance(edict_t *pent);  //  8771
//			edict(CBaseEntity *const this);  //  8787
//			ENTINDEX(edict_t *pEdict);  //  8787
//			IsObserver(CBasePlayer *const this);  //  8798
//			IsObserver(CBasePlayer *const this);  //  8800
//			HintMessage(CBasePlayer *const this,
//					const char *pMessage,
//					BOOL bDisplayIfPlayerDead,
//					BOOL bOverride);  //  8815
//			HintMessage(CBasePlayer *const this,
//					const char *pMessage,
//					BOOL bDisplayIfPlayerDead,
//					BOOL bOverride);  //  8833
//			IsObserver(CBasePlayer *const this);  //  8840
//			HintMessage(CBasePlayer *const this,
//					const char *pMessage,
//					BOOL bDisplayIfPlayerDead,
//					BOOL bOverride);  //  8865
//			HintMessage(CBasePlayer *const this,
//					const char *pMessage,
//					BOOL bDisplayIfPlayerDead,
//					BOOL bOverride);  //  8861
//		}
//		{
//			int i;                                        //  8906
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  8910
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  8894
//	}
}

/* <1603f0> ../cstrike/dlls/player.cpp:8926 */
void CBasePlayer::DropPlayerItem(const char *pszItemName)
{
	if (!Q_strlen(pszItemName))
	{
		// if this string has no length, the client didn't type a name!
		// assume player wants to drop the active item.
		// make the string null to make future operations in this function easier
		pszItemName = NULL;
	}

	if (m_bIsVIP)
	{
		ClientPrint(pev, HUD_PRINTCENTER, "#Weapon_Cannot_Be_Dropped");
		return;
	}
	else if (!pszItemName && HasShield())
	{
		DropShield(true);
		return;
	}

	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		CBasePlayerItem *pWeapon = m_rgpPlayerItems[i];

		while (pWeapon != NULL)
		{
			if (pszItemName)
			{
				if (!Q_strcmp(pszItemName, STRING(pWeapon->pev->classname)))
					break;
			}
			else
			{
				if (pWeapon == m_pActiveItem)
					break;
			}

			pWeapon = pWeapon->m_pNext;
		}

		if (pWeapon)
		{
			if (!pWeapon->CanDrop())
			{
				ClientPrint(pev, HUD_PRINTCENTER, "#Weapon_Cannot_Be_Dropped");
				continue;
			}

			// take item off hud
			pev->weapons &= ~(1 << pWeapon->m_iId);
			g_pGameRules->GetNextBestWeapon(this, pWeapon);
			UTIL_MakeVectors(pev->angles);

			if (pWeapon->iItemSlot() == PRIMARY_WEAPON_SLOT)
				m_bHasPrimary = false;

			if (!Q_strcmp(STRING(pWeapon->pev->classname), "weapon_c4"))
			{
				m_bHasC4 = false;
				pev->body = 0;
				SetBombIcon(FALSE);
				pWeapon->m_pPlayer->SetProgressBarTime(0);

				if (!g_pGameRules->m_fTeamCount)
				{
					UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Dropped_The_Bomb\"\n",
						STRING(pev->netname),
						GETPLAYERUSERID(edict()),
						GETPLAYERAUTHID(edict()));

					g_pGameRules->m_bBombDropped = TRUE;

					CBaseEntity *pEntity = NULL;

					while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")) != NULL)
					{
						if (FNullEnt(pEntity->edict()))
							break;

						if (!pEntity->IsPlayer())
							continue;

						if (pEntity->pev->flags != FL_DORMANT)
						{
							CBasePlayer *pOther = GetClassPtr((CBasePlayer *)pEntity->pev);

							if (pOther->pev->deadflag == DEAD_NO && pOther->m_iTeam == TERRORIST)
							{
								ClientPrint(pOther->pev, HUD_PRINTCENTER, "#Game_bomb_drop", STRING(pev->netname));

								MESSAGE_BEGIN(MSG_ONE, gmsgBombDrop, NULL, pOther->pev);
									WRITE_COORD(pev->origin.x);
									WRITE_COORD(pev->origin.y);
									WRITE_COORD(pev->origin.z);
									WRITE_BYTE(0);
								MESSAGE_END();
							}
						}
					}
				}
			}

			CWeaponBox *pWeaponBox = (CWeaponBox *)Create("weaponbox", pev->origin + gpGlobals->v_forward * 10, pev->angles, edict());
			pWeaponBox->pev->angles.x = 0;
			pWeaponBox->pev->angles.z = 0;
			pWeaponBox->SetThink(&CWeaponBox::Kill);
			pWeaponBox->pev->nextthink = gpGlobals->time + 300;
			pWeaponBox->PackWeapon(pWeapon);
			pWeaponBox->pev->velocity = gpGlobals->v_forward * 300 + gpGlobals->v_forward * 100;

			if (!Q_strcmp(STRING(pWeapon->pev->classname), "weapon_c4"))
			{
				pWeaponBox->m_bIsBomb = true;
				pWeaponBox->SetThink(&CWeaponBox::BombThink);
				pWeaponBox->pev->nextthink = gpGlobals->time + 1;

				TheCSBots()->SetLooseBomb(pWeaponBox);
				TheCSBots()->OnEvent(EVENT_BOMB_DROPPED, NULL, NULL);
			}

			if (pWeapon->iFlags() & ITEM_FLAG_EXHAUSTIBLE)
			{
				int iAmmoIndex = GetAmmoIndex(pWeapon->pszAmmo1());

				if (iAmmoIndex != -1)
				{
					pWeaponBox->PackAmmo(MAKE_STRING(pWeapon->pszAmmo1()), m_rgAmmo[iAmmoIndex] > 0);
					m_rgAmmo[iAmmoIndex] = 0;
				}
			}

			const char *modelname = GetCSModelName(pWeapon->m_iId);

			if (modelname)
				SET_MODEL(ENT(pWeaponBox->pev), modelname);

			return;
		}
	}
}

/* <1594a2> ../cstrike/dlls/player.cpp:9094 */
BOOL CBasePlayer::HasPlayerItem(CBasePlayerItem *pCheckItem)
{
	CBasePlayerItem *pItem = m_rgpPlayerItems[pCheckItem->iItemSlot()];
	while (pItem)
	{
		if (FClassnameIs(pItem->pev, STRING(pCheckItem->pev->classname)))
			return TRUE;

		pItem = pItem->m_pNext;
	}
	return FALSE;
}

/* <159534> ../cstrike/dlls/player.cpp:9113 */
NOBODY BOOL CBasePlayer::HasNamedPlayerItem(const char *pszItemName)
{
//	{
//		class CBasePlayerItem *pItem;                        //  9115
//		int i;                                                //  9116
//	}
}

/* <1619fd> ../cstrike/dlls/player.cpp:9137 */
NOBODY void CBasePlayer::SwitchTeam(void)
{
//	{
//		int oldTeam;                                          //  9139
//		char *szOldTeam;                                     //  9269
//		char *szNewTeam;                                     //  9270
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  9216
//		entindex(CBaseEntity *const this);  //  9217
//		{
//			int i;                                        //  9253
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					entvars_t *ent);  //  9245
//			SendItemStatus(CBasePlayer *pPlayer);  //  9249
//		}
//		edict(CBaseEntity *const this);  //  9277
//		edict(CBaseEntity *const this);  //  9277
//		{
//			class CCSBot *pBot;                          //  9282
//			{
//				const class BotProfile *pProfile;   //  9285
//				{
//					bool kick;                    //  9288
//				}
//			}
//		}
//		edict(CBaseEntity *const this);  //  9173
//		entindex(CBaseEntity *const this);  //  9173
//		edict(CBaseEntity *const this);  //  9210
//		entindex(CBaseEntity *const this);  //  9210
//		edict(CBaseEntity *const this);  //  9166
//		entindex(CBaseEntity *const this);  //  9166
//		edict(CBaseEntity *const this);  //  9148
//		entindex(CBaseEntity *const this);  //  9148
//		edict(CBaseEntity *const this);  //  9156
//		entindex(CBaseEntity *const this);  //  9156
//		edict(CBaseEntity *const this);  //  9160
//		entindex(CBaseEntity *const this);  //  9160
//		edict(CBaseEntity *const this);  //  9189
//		entindex(CBaseEntity *const this);  //  9189
//		edict(CBaseEntity *const this);  //  9203
//		entindex(CBaseEntity *const this);  //  9203
//		edict(CBaseEntity *const this);  //  9197
//		entindex(CBaseEntity *const this);  //  9197
//		edict(CBaseEntity *const this);  //  9193
//		entindex(CBaseEntity *const this);  //  9193
//	}
}

/* <159594> ../cstrike/dlls/player.cpp:9302 */
void CBasePlayer::UpdateShieldCrosshair(bool draw)
{
	if (draw)
		m_iHideHUD &= ~HIDEHUD_CROSSHAIR;//0xFFFFFFBF;//0xBF;
	else
		m_iHideHUD |= HIDEHUD_CROSSHAIR;//0x40
}

/* <152fbc> ../cstrike/dlls/player.cpp:9313 */
BOOL CBasePlayer::SwitchWeapon(CBasePlayerItem *pWeapon)
{
	if (!pWeapon->CanDeploy())
		return FALSE;

	ResetAutoaim();

	if (m_pActiveItem)
		m_pActiveItem->Holster();

	CBasePlayerItem *pTemp = m_pActiveItem;
	m_pActiveItem = pWeapon;
	m_pLastItem = pTemp;
	pWeapon->Deploy();

	if (pWeapon->m_pPlayer)
		pWeapon->m_pPlayer->ResetMaxSpeed();

	if (HasShield())
		UpdateShieldCrosshair(true);

	return TRUE;
}

/* <1595ed> ../cstrike/dlls/player.cpp:9342 */
void CBasePlayer::TabulateAmmo(void)
{
	ammo_buckshot = AmmoInventory(GetAmmoIndex("buckshot"));
	ammo_9mm = AmmoInventory(GetAmmoIndex("9mm"));
	ammo_556nato = AmmoInventory(GetAmmoIndex("556Nato"));
	ammo_556natobox = AmmoInventory(GetAmmoIndex("556NatoBox"));
	ammo_762nato = AmmoInventory(GetAmmoIndex("762Nato"));
	ammo_45acp = AmmoInventory(GetAmmoIndex("45acp"));
	ammo_50ae = AmmoInventory(GetAmmoIndex("50AE"));
	ammo_338mag = AmmoInventory(GetAmmoIndex("338Magnum"));
	ammo_57mm = AmmoInventory(GetAmmoIndex("57mm"));
	ammo_357sig = AmmoInventory(GetAmmoIndex("357SIG"));
}

/* <1511eb> ../cstrike/dlls/player.cpp:9365 */
NOBODY int CDeadHEV::Classify_(void)
{
}

/* <152451> ../cstrike/dlls/player.cpp:9375 */
NOBODY void CDeadHEV::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  9377
//	KeyValue(CDeadHEV *const this,
//		KeyValueData *pkvd);  //  9375
}

/* <159a88> ../cstrike/dlls/player.cpp:9386 */
LINK_ENTITY_TO_CLASS(monster_hevsuit_dead, CDeadHEV);

/* <1513ce> ../cstrike/dlls/player.cpp:9391 */
NOBODY void CDeadHEV::Spawn_(void)
{
}

/* <159b64> ../cstrike/dlls/player.cpp:9426 */
LINK_ENTITY_TO_CLASS(player_weaponstrip, CStripWeapons);

/* <15f62f> ../cstrike/dlls/player.cpp:9428 */
NOBODY void CStripWeapons::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
//	{
//		class CBasePlayer *pPlayer;                          //  9430
//		Instance(edict_t *pent);  //  9438
//	}
}

/* <159c40> ../cstrike/dlls/player.cpp:9473 */
LINK_ENTITY_TO_CLASS(player_loadsaved, CRevertSaved);

/* <151a24> ../cstrike/dlls/player.cpp:9481 */
IMPLEMENT_SAVERESTORE(CRevertSaved, CPointEntity);

/* <152540> ../cstrike/dlls/player.cpp:9483 */
NOBODY void CRevertSaved::KeyValue_(KeyValueData *pkvd)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //  9485
//	FStrEq(const char *sz1,
//		const char *sz2);  //  9490
//	KeyValue(CRevertSaved *const this,
//		KeyValueData *pkvd);  //  9483
//	atof(const char *__nptr);  //  9487
//	atof(const char *__nptr);  //  9492
}

/* <151365> ../cstrike/dlls/player.cpp:9509 */
NOBODY void CRevertSaved::Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
}

/* <152a96> ../cstrike/dlls/player.cpp:9517 */
NOBODY void CRevertSaved::MessageThink(void)
{
//	{
//		float nextThink;                                      //  9520
//		LoadThink(CRevertSaved *const this);  //  9527
//	}
}

/* <15198b> ../cstrike/dlls/player.cpp:9531 */
NOBODY void CRevertSaved::LoadThink(void)
{
//	LoadThink(CRevertSaved *const this);  //  9531
}

/* <15133c> ../cstrike/dlls/player.cpp:9549 */
NOBODY void CInfoIntermission::Spawn_(void)
{
}

/* <1530e6> ../cstrike/dlls/player.cpp:9560 */
NOBODY void CInfoIntermission::Think_(void)
{
//	{
//		edict_t *pTarget;                                    //  9562
//		FIND_ENTITY_BY_TARGETNAME(edict_t *entStart,
//						const char *pszName);  //  9565
//		FNullEnt(const edict_t *pent);  //  9567
//		operator-(const Vector *const this,
//				const Vector &v);  //  9569
//		Normalize(const Vector *const this);  //  9569
//	}
}

/* <159d1c> ../cstrike/dlls/player.cpp:9574 */
LINK_ENTITY_TO_CLASS(info_intermission, CInfoIntermission);

/* <159df8> ../cstrike/dlls/player.cpp:9586 */
NOBODY void CBasePlayer::StudioEstimateGait(void)
{
//	{
//		float dt;                                             //  9588
//		Vector est_velocity;                            //  9589
//		operator-(const Vector *const this,
//				const Vector &v);  //  9604
//		Length(const Vector *const this);  //  9607
//		{
//			float flYawDiff;                              //  9618
//			float flYaw;                                  //  9619
//		}
//	}
}

/* <159f01> ../cstrike/dlls/player.cpp:9685 */
NOBODY void CBasePlayer::StudioPlayerBlend(int *pBlend, float *pPitch)
{
//	{
//		float range;                                          //  9688
//	}
}

/* <159f81> ../cstrike/dlls/player.cpp:9709 */
NOBODY void CBasePlayer::CalculatePitchBlend(void)
{
//	{
//		int iBlend;                                           //  9711
//		float temp;                                           //  9712
//		StudioPlayerBlend(CBasePlayer *const this,
//					int *pBlend,
//					float *pPitch);  //  9714
//	}
}

/* <15a007> ../cstrike/dlls/player.cpp:9720 */
NOBODY void CBasePlayer::CalculateYawBlend(void)
{
//	{
//		float dt;                                             //  9722
//		float flYaw;                                          //  9723
//		float maxyaw;                                         //  9745
//		float blend_yaw;                                      //  9763
//	}
}

/* <15a07b> ../cstrike/dlls/player.cpp:9776 */
NOBODY void CBasePlayer::StudioProcessGait(void)
{
//	{
//		mstudioseqdesc_t *pseqdesc;                          //  9778
//		float dt;                                             //  9779
//		class model_s *model;                                //  9793
//		studiohdr_t *pstudiohdr;                             //  9797
//		CalculatePitchBlend(CBasePlayer *const this);  //  9791
//	}
}

/* <15a444> ../cstrike/dlls/player.cpp:9821 */
NOBODY void CBasePlayer::ResetStamina(void)
{
}

/* <15a467> ../cstrike/dlls/player.cpp:9829 */
NOBODY float GetPlayerPitch(const edict_t *pEdict)
{
//	{
//		class CBasePlayer *pPlayer;                          //  9831
//		Instance(entvars_t *pev);  //  9836
//	}
}

/* <15a5f9> ../cstrike/dlls/player.cpp:9863 */
NOBODY int GetPlayerGaitsequence(edict_t *pEdict)
{
//	{
//		class CBasePlayer *pPlayer;                          //  9865
//		Instance(entvars_t *pev);  //  9870
//	}
}

/* <15a530> ../cstrike/dlls/player.cpp:9846 */
NOBODY float GetPlayerYaw(const edict_t *pEdict)
{
//	{
//		class CBasePlayer *pPlayer;                          //  9848
//		Instance(entvars_t *pev);  //  9853
//	}
}

/* <15a6c2> ../cstrike/dlls/player.cpp:9880 */
void CBasePlayer::SpawnClientSideCorpse(void)
{
	char *infobuffer = GET_INFO_BUFFER(edict());
	char *pModel = GET_KEY_VALUE(infobuffer, "model");

	MESSAGE_BEGIN(MSG_ALL, gmsgSendCorpse);
		WRITE_STRING(pModel);
		WRITE_LONG(pev->origin.x * 128);
		WRITE_LONG(pev->origin.y * 128);
		WRITE_LONG(pev->origin.z * 128);
		WRITE_COORD(pev->angles.x);
		WRITE_COORD(pev->angles.y);
		WRITE_COORD(pev->angles.z);
		WRITE_LONG((pev->animtime - gpGlobals->time) * 100);
		WRITE_BYTE(pev->sequence);
		WRITE_BYTE(pev->body);
		WRITE_BYTE(m_iTeam);
		WRITE_BYTE(entindex());
	MESSAGE_END();

	m_canSwitchObserverModes = true;

	if (TheTutor)
		TheTutor->OnEvent(EVENT_CLIENT_CORPSE_SPAWNED, this, NULL);
}

/* <15a7a2> ../cstrike/dlls/player.cpp:9909 */
NOBODY BOOL CBasePlayer::IsArmored(int nHitGroup)
{
//	{
//		BOOL fApplyArmor;                                     //  9911
//	}
//	IsArmored(CBasePlayer *const this,
//			int nHitGroup);  //  9909
}

/* <15a847> ../cstrike/dlls/player.cpp:9939 */
NOBODY BOOL CBasePlayer::ShouldDoLargeFlinch(int nHitGroup, int nGunType)
{
}

/* <15a87d> ../cstrike/dlls/player.cpp:9971 */
NOBODY void CBasePlayer::SetPrefsFromUserinfo(char *infobuffer)
{
//	{
//		const char *pszKeyVal;                              //  9973
//		atoi(const char *__nptr);  // 10005
//		atoi(const char *__nptr);  //  9994
//		atoi(const char *__nptr);  //  9983
//	}
}

/* <15a92a> ../cstrike/dlls/player.cpp:10013 */
bool CBasePlayer::IsLookingAtPosition(Vector *pos, float angleTolerance)
{
	Vector to = *pos - EyePosition();
	Vector idealAngle = UTIL_VecToAngles( to );

	idealAngle.x = 360.0 - idealAngle.x;

	float deltaYaw = NormalizeAngle(idealAngle.y - pev->v_angle.y);
	float deltaPitch = NormalizeAngle(idealAngle.x - pev->v_angle.x);

	return (abs(deltaYaw) < angleTolerance
		&& abs(deltaPitch) < angleTolerance);
}

/* <15aa7b> ../cstrike/dlls/player.cpp:10083 */
bool CBasePlayer::CanAffordPrimary(void)
{
	int account = m_iAccount;

	if (m_iTeam == CT)
	{
		WeaponStruct *temp;
		for (int i = 0; i < MAX_WEAPONS; i++)
		{
			temp = &g_weaponStruct[ i ];

			if (temp->m_side & TERRORIST && temp->m_slot == PRIMARY_WEAPON_SLOT && account >= temp->m_price)
				return true;
		}
	}
	else if (m_iTeam == TERRORIST)
	{
		WeaponStruct *temp;
		for (int i = 0; i < MAX_WEAPONS; i++)
		{
			temp = &g_weaponStruct[ i ];

			if (temp->m_side & CT && temp->m_slot == PRIMARY_WEAPON_SLOT && account >= temp->m_price)
				return true;
		}
	}

	return false;
}

/* <15ab2c> ../cstrike/dlls/player.cpp:10139 */
bool CBasePlayer::CanAffordPrimaryAmmo(void)
{
	CBasePlayerWeapon *primary = (CBasePlayerWeapon *)&m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ];

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		WeaponStruct *temp = &g_weaponStruct[ i ];

		if (temp->m_type == primary->m_iId && m_iAccount >= temp->m_ammoPrice)
			return true;
	}

	return false;
}

/* <15aba0> ../cstrike/dlls/player.cpp:10169 */
bool CBasePlayer::CanAffordSecondaryAmmo(void)
{
	CBasePlayerWeapon *secondary = (CBasePlayerWeapon *)&m_rgpPlayerItems[ PISTOL_SLOT ];

	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		WeaponStruct *temp = &g_weaponStruct[ i ];

		if (temp->m_type == secondary->m_iId && m_iAccount >= temp->m_ammoPrice)
			return true;
	}

	return false;
}

/* <15ac14> ../cstrike/dlls/player.cpp:10199 */
bool CBasePlayer::CanAffordArmor(void)
{
	if (m_iKevlar == 1 && pev->armorvalue == 100.0f && m_iAccount >= HELMET_PRICE)
		return true;

	return (m_iAccount >= KEVLAR_PRICE);

	//if (m_iKevlar != 1 || pev->armorvalue != 100.0f || m_iAccount < HELMET_PRICE)
	//	return (m_iAccount >= KEVLAR_PRICE);
	//return true;
}

/* <15ac3c> ../cstrike/dlls/player.cpp:10217 */
bool CBasePlayer::CanAffordDefuseKit(void)
{
	return (m_iAccount >= DEFUSEKIT_PRICE);
}

/* <15ac64> ../cstrike/dlls/player.cpp:10227 */
bool CBasePlayer::CanAffordGrenade(void)
{
	return (m_iAccount >= FLASHBANG_PRICE);
}

/* <15ac8c> ../cstrike/dlls/player.cpp:10247 */
bool CBasePlayer::NeedsPrimaryAmmo(void)
{
	CBasePlayerWeapon *primary = (CBasePlayerWeapon *)&m_rgpPlayerItems[ PRIMARY_WEAPON_SLOT ];

	if (!primary || primary->m_iId == WEAPON_SHIELDGUN)
		return false;

	return (m_rgAmmo[ primary->m_iPrimaryAmmoType ] < primary->iMaxAmmo1());
}

/* <15ace1> ../cstrike/dlls/player.cpp:10268 */
bool CBasePlayer::NeedsSecondaryAmmo(void)
{
	CBasePlayerWeapon *secondary = (CBasePlayerWeapon *)&m_rgpPlayerItems[ PISTOL_SLOT ];

	if (!secondary)
		return false;

	return (m_rgAmmo[ secondary->m_iPrimaryAmmoType ] < secondary->iMaxAmmo1());
}

/* <15ad36> ../cstrike/dlls/player.cpp:10285 */
bool CBasePlayer::NeedsArmor(void)
{
	if (m_iKevlar == ARMOR_TYPE_EMPTY)
		return true;

	return (pev->armorvalue < 50.0f);
}

/* <15ad5e> ../cstrike/dlls/player.cpp:10300 */
bool CBasePlayer::NeedsDefuseKit(void)
{
	CHalfLifeMultiplay *mpRules = g_pGameRules;

	if (m_bHasDefuser || m_iTeam != CT)
		return false;

	return (mpRules->m_bMapHasBombTarget);
}

/* <15ad9a> ../cstrike/dlls/player.cpp:10325 */
bool CBasePlayer::NeedsGrenade(void)
{
	int iAmmoIndex = GetAmmoIndex("HEGrenade");

	if (iAmmoIndex > 0 && m_rgAmmo[ iAmmoIndex ])
		return false;

	iAmmoIndex = GetAmmoIndex("Flashbang");

	if (iAmmoIndex > 0 && m_rgAmmo[ iAmmoIndex ])
		return false;

	iAmmoIndex = GetAmmoIndex("SmokeGrenade");

	if (iAmmoIndex > 0 && m_rgAmmo[ iAmmoIndex ])
		return false;

	return true;
}

/* <15aeab> ../cstrike/dlls/player.cpp:10381 */
NOBODY void CBasePlayer::ClientCommand(const char *cmd, const char *arg1, const char *arg2, const char *arg3)
{
	BotArgs[0] = cmd;
	BotArgs[1] = arg1;
	BotArgs[2] = arg2;
	BotArgs[3] = arg3;

	UseBotArgs = true;
	::ClientCommand(ENT(pev));
	UseBotArgs = false;
}

/* <15aea9> ../cstrike/dlls/player.cpp:10401 */
NOBODY const char *GetBuyStringForWeaponClass(int weaponClass)
{
}

/* <15aee9> ../cstrike/dlls/player.cpp:10454 */
NOBODY void CBasePlayer::ClearAutoBuyData(void)
{
}

/* <15af11> ../cstrike/dlls/player.cpp:10459 */
NOBODY void CBasePlayer::AddAutoBuyData(const char *str)
{
//	{
//		int len;                                              // 10461
//	}
}

/* <15af66> ../cstrike/dlls/player.cpp:10478 */
NOBODY void CBasePlayer::InitRebuyData(const char *str)
{
}

/* <15be4f> ../cstrike/dlls/player.cpp:10500 */
NOBODY void CBasePlayer::AutoBuy(void)
{
//	{
//		const char *c;                                      // 10502
//		bool boughtPrimary;                                   // 10504
//		bool boughtSecondary;                                 // 10505
//		char prioritizedString;                               // 10519
//		PickFlashKillWeaponString(CBasePlayer *const this);  // 10507
//		PickGrenadeKillWeaponString(CBasePlayer *const this);  // 10513
//		PrioritizeAutoBuyString(CBasePlayer *const this,
//					char *autobuyString,
//					const char *priorityString);  // 10524
//		PrioritizeAutoBuyString(CBasePlayer *const this,
//					char *autobuyString,
//					const char *priorityString);  // 10531
//		PickFlashKillWeaponString(CBasePlayer *const this);  // 10542
//	}
}

/* <14ea4e> ../cstrike/dlls/player.cpp:10556 */
NOBODY bool IsPrimaryWeaponClass(int classId)
{
}

/* <15afbe> ../cstrike/dlls/player.cpp:10571 */
NOBODY bool IsPrimaryWeaponId(int id)
{
//	{
//		const char *alias;                                  // 10573
//		int classId;                                          // 10579
//	}
}

/* <14ea6f> ../cstrike/dlls/player.cpp:10583 */
NOBODY bool IsSecondaryWeaponClass(int classId)
{
}

/* <15b059> ../cstrike/dlls/player.cpp:10588 */
NOBODY bool IsSecondaryWeaponId(int id)
{
//	{
//		const char *alias;                                  // 10590
//		int classId;                                          // 10596
//	}
}

/* <15b0f1> ../cstrike/dlls/player.cpp:10600 */
NOBODY const char *GetWeaponAliasFromName(const char *weaponName)
{
}

/* <15b133> ../cstrike/dlls/player.cpp:10607 */
NOBODY bool CurrentWeaponSatisfies(CBasePlayerWeapon *pWeapon, int id, int classId)
{
//	{
//		const char *weaponName;                             // 10612
//	}
}

/* <15b1eb> ../cstrike/dlls/player.cpp:10623 */
NOBODY const char *CBasePlayer::PickPrimaryCareerTaskWeapon(void)
{
//	{
//		intconst BufLen;                                      // 10625
//		char buf;                                             // 10626
//		class CBasePlayerWeapon *primary;                    // 10632
//		class vector<CCareerTask*, std::allocator<CCareerTask*> > taskVector;               // 10634
//		CareerTaskListIt it;                                  // 10635
//		vector(vector<CCareerTask*, std::allocator<CCareerTask*> > *const this);  // 10634
//		{
//			class CCareerTask *pTask;                    // 10638
//			push_back(vector<CCareerTask*, std::allocator<CCareerTask*> > *const this,
//					const value_type  &__x);  // 10656
//			IsPrimaryWeaponId(int id);  // 10644
//			CurrentWeaponSatisfies(CBasePlayerWeapon *pWeapon,
//						int id,
//						int classId);  // 10647
//			IsPrimaryWeaponId(int id);  // 10649
//			GetBuyStringForWeaponClass(int weaponClass);  // 10652
//		}
//		operator++(_List_iterator<CCareerTask*> *const this);  // 10636
//		{
//			int taskNum;                                  // 10664
//			class CCareerTask *temp;                     // 10666
//			operator[](vector<CCareerTask*, std::allocator<CCareerTask*> > *const this,
//					size_type __n);  // 10667
//		}
//		{
//			int i;                                        // 10673
//			{
//				class CCareerTask *pTask;            // 10675
//				IsPrimaryWeaponId(int id);  // 10676
//				GetBuyStringForWeaponClass(int weaponClass);  // 10682
//			}
//			size(const class vector<CCareerTask*, std::allocator<CCareerTask*> > *const this);  // 10673
//		}
//		~vector(vector<CCareerTask*, std::allocator<CCareerTask*> > *const this,
//			intconst __in_chrg);  // 10634
//	}
}

/* <15b5d7> ../cstrike/dlls/player.cpp:10690 */
NOBODY const char *CBasePlayer::PickSecondaryCareerTaskWeapon(void)
{
//	{
//		intconst BufLen;                                      // 10692
//		char buf;                                             // 10693
//		class CBasePlayerWeapon *secondary;                  // 10699
//		class vector<CCareerTask*, std::allocator<CCareerTask*> > taskVector;               // 10701
//		CareerTaskListIt it;                                  // 10702
//		vector(vector<CCareerTask*, std::allocator<CCareerTask*> > *const this);  // 10701
//		{
//			class CCareerTask *pTask;                    // 10705
//			IsSecondaryWeaponId(int id);  // 10711
//			CurrentWeaponSatisfies(CBasePlayerWeapon *pWeapon,
//						int id,
//						int classId);  // 10714
//			push_back(vector<CCareerTask*, std::allocator<CCareerTask*> > *const this,
//					const value_type  &__x);  // 10723
//			IsSecondaryWeaponId(int id);  // 10716
//			GetBuyStringForWeaponClass(int weaponClass);  // 10719
//		}
//		operator++(_List_iterator<CCareerTask*> *const this);  // 10703
//		{
//			int taskNum;                                  // 10731
//			class CCareerTask *temp;                     // 10733
//			operator[](vector<CCareerTask*, std::allocator<CCareerTask*> > *const this,
//					size_type __n);  // 10734
//		}
//		{
//			int i;                                        // 10740
//			{
//				class CCareerTask *pTask;            // 10742
//				IsSecondaryWeaponId(int id);  // 10743
//			}
//			size(const class vector<CCareerTask*, std::allocator<CCareerTask*> > *const this);  // 10740
//		}
//		~vector(vector<CCareerTask*, std::allocator<CCareerTask*> > *const this,
//			intconst __in_chrg);  // 10701
//	}
}

/* <15b9ea> ../cstrike/dlls/player.cpp:10759 */
NOBODY const char *CBasePlayer::PickFlashKillWeaponString(void)
{
//	{
//		bool foundOne;                                        // 10761
//		CareerTaskListIt it;                                  // 10762
//		{
//			class CCareerTask *pTask;                    // 10765
//			operator++(_List_iterator<CCareerTask*> *const this);  // 10776
//		}
//	}
}

/* <15baa1> ../cstrike/dlls/player.cpp:10787 */
NOBODY const char *CBasePlayer::PickGrenadeKillWeaponString(void)
{
//	{
//		bool foundOne;                                        // 10789
//		CareerTaskListIt it;                                  // 10790
//		{
//			class CCareerTask *pTask;                    // 10793
//			operator++(_List_iterator<CCareerTask*> *const this);  // 10804
//		}
//	}
}

/* <15bb0c> ../cstrike/dlls/player.cpp:10816 */
NOBODY void CBasePlayer::PrioritizeAutoBuyString(char *autobuyString, const char *priorityString)
{
//	{
//		char newString;                                       // 10818
//		int newStringPos;                                     // 10819
//		char priorityToken;                                   // 10820
//		const char *priorityChar;                           // 10827
//		char *autobuyPosition;                               // 10872
//	}
}

/* <15bcd5> ../cstrike/dlls/player.cpp:10899 */
NOBODY void CBasePlayer::ParseAutoBuyString(const char *string, bool &boughtPrimary, bool &boughtSecondary)
{
//	{
//		char command;                                         // 10901
//		const char *c;                                      // 10902
//		{
//			int i;                                        // 10912
//			class AutoBuyInfoStruct *commandInfo;        // 10945
//			GetAutoBuyCommandInfo(CBasePlayer *const this,
//						const char *command);  // 10945
//			ShouldExecuteAutoBuyCommand(CBasePlayer *const this,
//							const class AutoBuyInfoStruct *commandInfo,
//							bool boughtPrimary,
//							bool boughtSecondary);  // 10947
//			ClientCommand(CBasePlayer *const this,
//					const char *cmd,
//					const char *arg1,
//					const char *arg2,
//					const char *arg3);  // 10949
//		}
//	}
}

/* <15bb6b> ../cstrike/dlls/player.cpp:10957 */
NOBODY bool CBasePlayer::ShouldExecuteAutoBuyCommand(AutoBuyInfoStruct *commandInfo, bool boughtPrimary, bool boughtSecondary)
{
}

/* <15bbfa> ../cstrike/dlls/player.cpp:10978 */
AutoBuyInfoStruct *CBasePlayer::GetAutoBuyCommandInfo(const char *command)
{
//	{
//		class AutoBuyInfoStruct *ret;                        // 10980
//		int i;                                                // 10982
//		class AutoBuyInfoStruct *temp;                       // 10983
//	}
}

/* <15bc49> ../cstrike/dlls/player.cpp:11000 */
NOBODY void CBasePlayer::PostAutoBuyCommandProcessing(AutoBuyInfoStruct *commandInfo, bool &boughtPrimary, bool &boughtSecondary)
{
//	{
//		class CBasePlayerWeapon *primary;                    // 11002
//		class CBasePlayerWeapon *secondary;                  // 11003
//	}
}

/* <15c0b4> ../cstrike/dlls/player.cpp:11027 */
NOBODY void CBasePlayer::BuildRebuyStruct(void)
{
//	{
//		class CBasePlayerWeapon *primary;                    // 11035
//		class CBasePlayerWeapon *secondary;                  // 11036
//		int iAmmoIndex;                                       // 11072
//		GetAmmoIndex(const char *psz);  // 11075
//		GetAmmoIndex(const char *psz);  // 11087
//		GetAmmoIndex(const char *psz);  // 11099
//	}
}

/* <15c37d> ../cstrike/dlls/player.cpp:11134 */
NOBODY void CBasePlayer::Rebuy(void)
{
//	{
//		char *fileData;                                      // 11138
//		char *token;                                         // 11140
//		RebuyArmor(CBasePlayer *const this);  // 11182
//		RebuyPrimaryWeapon(CBasePlayer *const this);  // 11146
//		RebuyPrimaryAmmo(CBasePlayer *const this);  // 11150
//		RebuySecondaryWeapon(CBasePlayer *const this);  // 11154
//		RebuySecondaryAmmo(CBasePlayer *const this);  // 11158
//		RebuyHEGrenade(CBasePlayer *const this);  // 11162
//		RebuyFlashbang(CBasePlayer *const this);  // 11166
//		RebuySmokeGrenade(CBasePlayer *const this);  // 11170
//		RebuyDefuser(CBasePlayer *const this);  // 11174
//		RebuyNightVision(CBasePlayer *const this);  // 11178
//	}
}

/* <15c96a> ../cstrike/dlls/player.cpp:11200 */
NOBODY void CBasePlayer::RebuyPrimaryWeapon(void)
{
//	{
//		const char *alias;                                  // 11209
//		ClientCommand(CBasePlayer *const this,
//				const char *cmd,
//				const char *arg1,
//				const char *arg2,
//				const char *arg3);  // 11212
//	}
}

/* <15c9e4> ../cstrike/dlls/player.cpp:11217 */
NOBODY void CBasePlayer::RebuyPrimaryAmmo(void)
{
//	{
//		class CBasePlayerWeapon *primary;                    // 11219
//		ClientCommand(CBasePlayer *const this,
//				const char *cmd,
//				const char *arg1,
//				const char *arg2,
//				const char *arg3);  // 11229
//	}
}

/* <15ca68> ../cstrike/dlls/player.cpp:11233 */
NOBODY void CBasePlayer::RebuySecondaryWeapon(void)
{
//	{
//		const char *alias;                                  // 11237
//		ClientCommand(CBasePlayer *const this,
//				const char *cmd,
//				const char *arg1,
//				const char *arg2,
//				const char *arg3);  // 11240
//	}
}

/* <15cae2> ../cstrike/dlls/player.cpp:11245 */
NOBODY void CBasePlayer::RebuySecondaryAmmo(void)
{
//	{
//		class CBasePlayerWeapon *secondary;                  // 11247
//		ClientCommand(CBasePlayer *const this,
//				const char *cmd,
//				const char *arg1,
//				const char *arg2,
//				const char *arg3);  // 11255
//	}
}

/* <15cb66> ../cstrike/dlls/player.cpp:11259 */
NOBODY void CBasePlayer::RebuyHEGrenade(void)
{
//	{
//		int iAmmoIndex;                                       // 11262
//		int numToBuy;                                         // 11269
//		GetAmmoIndex(const char *psz);  // 11262
//		{
//			int i;                                        // 11272
//			ClientCommand(CBasePlayer *const this,
//					const char *cmd,
//					const char *arg1,
//					const char *arg2,
//					const char *arg3);  // 11274
//		}
//	}
}

/* <15cc3f> ../cstrike/dlls/player.cpp:11279 */
NOBODY void CBasePlayer::RebuyFlashbang(void)
{
//	{
//		int iAmmoIndex;                                       // 11282
//		int numToBuy;                                         // 11289
//		GetAmmoIndex(const char *psz);  // 11282
//		{
//			int i;                                        // 11292
//			ClientCommand(CBasePlayer *const this,
//					const char *cmd,
//					const char *arg1,
//					const char *arg2,
//					const char *arg3);  // 11294
//		}
//	}
}

/* <15cd18> ../cstrike/dlls/player.cpp:11299 */
NOBODY void CBasePlayer::RebuySmokeGrenade(void)
{
//	{
//		int iAmmoIndex;                                       // 11302
//		int numToBuy;                                         // 11309
//		GetAmmoIndex(const char *psz);  // 11302
//		{
//			int i;                                        // 11312
//			ClientCommand(CBasePlayer *const this,
//					const char *cmd,
//					const char *arg1,
//					const char *arg2,
//					const char *arg3);  // 11314
//		}
//	}
}

/* <15cdf1> ../cstrike/dlls/player.cpp:11319 */
NOBODY void CBasePlayer::RebuyDefuser(void)
{
//	ClientCommand(CBasePlayer::RebuyDefuser(//			const char *cmd,
//			const char *arg1,
//			const char *arg2,
//			const char *arg3);  // 11327
}

/* <15ce59> ../cstrike/dlls/player.cpp:11330 */
NOBODY void CBasePlayer::RebuyNightVision(void)
{
//	ClientCommand(CBasePlayer::RebuyNightVision(//			const char *cmd,
//			const char *arg1,
//			const char *arg2,
//			const char *arg3);  // 11338
}

/* <15cec1> ../cstrike/dlls/player.cpp:11341 */
NOBODY void CBasePlayer::RebuyArmor(void)
{
//	ClientCommand(CBasePlayer::RebuyArmor(//			const char *cmd,
//			const char *arg1,
//			const char *arg2,
//			const char *arg3);  // 11361
//	ClientCommand(CBasePlayer *const this,
//			const char *cmd,
//			const char *arg1,
//			const char *arg2,
//			const char *arg3);  // 11357
}

/* <15cf7c> ../cstrike/dlls/player.cpp:11366 */
NOBODY bool CBasePlayer::IsObservingPlayer(CBasePlayer *pPlayer)
{
//	edict(CBaseEntity *const this);  // 11368
//	FNullEnt(const edict_t *pent);  // 11368
//	entindex(CBaseEntity *const this);  // 11371
}

/* <15d049> ../cstrike/dlls/player.cpp:11380 */
NOBODY void CBasePlayer::UpdateLocation(bool forceUpdate)
{
//	{
//		const char *placeName;                              // 11390
//		{
//			Place playerPlace;                            // 11393
//			const BotPhraseList *placeList;             // 11394
//			int i;                                        // 11395
//			{
//				const_iterator iter;                  // 11398
//				operator++(_List_const_iterator<BotPhrase*> *const this);  // 11398
//			}
//		}
//		{
//			int i;                                        // 11416
//			{
//				class CBasePlayer *player;           // 11418
//				edict(CBaseEntity *const this);  // 11425
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						edict_t *ed);  // 11425
//				entindex(CBaseEntity *const this);  // 11426
//				edict(CBaseEntity *const this);  // 11434
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						edict_t *ed);  // 11434
//				entindex(CBaseEntity *const this);  // 11435
//			}
//		}
//	}
}

#ifdef HOOK_GAMEDLL

void CBasePlayer::Spawn(void)
{
	Spawn_();
}

void CBasePlayer::Precache(void)
{
	Precache_();
}

int CBasePlayer::Save(CSave &save)
{
	return Save_(save);
}

int CBasePlayer::Restore(CRestore &restore)
{
	return Restore_(restore);
}

int CBasePlayer::Classify(void)
{
	return Classify_();
}

void CBasePlayer::TraceAttack(entvars_t *pevAttacker,float flDamage,Vector vecDir,TraceResult *ptr,int bitsDamageType)
{
	TraceAttack_(pevAttacker,flDamage,vecDir,ptr,bitsDamageType);
}

int CBasePlayer::TakeDamage(entvars_t *pevInflictor,entvars_t *pevAttacker,float flDamage,int bitsDamageType)
{
	return TakeDamage_(pevInflictor,pevAttacker,flDamage,bitsDamageType);
}

int CBasePlayer::TakeHealth(float flHealth,int bitsDamageType)
{
	return TakeHealth_(flHealth,bitsDamageType);
}

void CBasePlayer::Killed(entvars_t *pevAttacker,int iGib)
{
	Killed_(pevAttacker,iGib);
}

void CBasePlayer::AddPoints(int score,BOOL bAllowNegativeScore)
{
	AddPoints_(score,bAllowNegativeScore);
}

void CBasePlayer::AddPointsToTeam(int score,BOOL bAllowNegativeScore)
{
	AddPointsToTeam_(score,bAllowNegativeScore);
}

BOOL CBasePlayer::AddPlayerItem(CBasePlayerItem *pItem)
{
	return AddPlayerItem_(pItem);
}

BOOL CBasePlayer::RemovePlayerItem(CBasePlayerItem *pItem)
{
	return RemovePlayerItem_(pItem);
}

int CBasePlayer::GiveAmmo(int iAmount,char *szName,int iMax)
{
	return GiveAmmo_(iAmount,szName,iMax);
}

void CBasePlayer::StartSneaking(void)
{
	StartSneaking_();
}

void CBasePlayer::StopSneaking(void)
{
	StopSneaking_();
}

BOOL CBasePlayer::IsSneaking(void)
{
	return IsSneaking_();
}

BOOL CBasePlayer::IsAlive(void)
{
	return IsAlive_();
}

BOOL CBasePlayer::IsPlayer(void)
{
	return IsPlayer_();
}

BOOL CBasePlayer::IsNetClient(void)
{
	return IsNetClient_();
}

const char *CBasePlayer::TeamID(void)
{
	return TeamID_();
}

BOOL CBasePlayer::FBecomeProne(void)
{
	return FBecomeProne_();
}

Vector CBasePlayer::BodyTarget(const Vector &posSrc)
{
	return BodyTarget_(posSrc);
}

int CBasePlayer::Illumination(void)
{
	return Illumination_();
}

BOOL CBasePlayer::ShouldFadeOnDeath(void)
{
	return ShouldFadeOnDeath_();
}

void CBasePlayer::ResetMaxSpeed(void)
{
	ResetMaxSpeed_();
}

void CBasePlayer::Jump(void)
{
	Jump_();
}

void CBasePlayer::Duck(void)
{
	Duck_();
}

void CBasePlayer::PreThink(void)
{
	PreThink_();
}

void CBasePlayer::PostThink(void)
{
	PostThink_();
}

Vector CBasePlayer::GetGunPosition(void)
{
	return GetGunPosition_();
}

BOOL CBasePlayer::IsBot(void)
{
	return IsBot_();
}

void CBasePlayer::UpdateClientData(void)
{
	UpdateClientData_();
}

void CBasePlayer::ImpulseCommands(void)
{
	ImpulseCommands_();
}

void CBasePlayer::RoundRespawn(void)
{
	RoundRespawn_();
}

Vector CBasePlayer::GetAutoaimVector(float flDelta)
{
	return GetAutoaimVector_(flDelta);
}

void CBasePlayer::Blind(float flUntilTime,float flHoldTime,float flFadeTime,int iAlpha)
{
	Blind_(flUntilTime,flHoldTime,flFadeTime,iAlpha);
}

void CBasePlayer::OnTouchingWeapon(CWeaponBox *pWeapon)
{
	OnTouchingWeapon_(pWeapon);
}

void CStripWeapons::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CRevertSaved::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CRevertSaved::Save(CSave &save)
{
	return Save_(save);
}

int CRevertSaved::Restore(CRestore &restore)
{
	return Restore_(restore);
}

void CRevertSaved::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	Use_(pActivator, pCaller, useType, value);
}

void CDeadHEV::Spawn(void)
{
	Spawn_();
}

void CDeadHEV::KeyValue(KeyValueData *pkvd)
{
	KeyValue_(pkvd);
}

int CDeadHEV::Classify(void)
{
	return Classify_();
}

void CSprayCan::Think(void)
{
	Think_();
}

void CInfoIntermission::Spawn(void)
{
	Spawn_();
}

void CInfoIntermission::Think(void)
{
	Think_();
}

#endif // HOOK_GAMEDLL
