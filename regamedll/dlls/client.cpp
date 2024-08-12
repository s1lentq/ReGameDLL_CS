#include "precompiled.h"

int gmsgWeapPickup = 0;
int gmsgHudText = 0;
int gmsgHudTextPro = 0;
int gmsgHudTextArgs = 0;
int gmsgShake = 0;
int gmsgFade = 0;
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
int gmsgAccount = 0;
int gmsgHealthInfo = 0;
bool g_bClientPrintEnable = true;

char *sPlayerModelFiles[] =
{
	"models/player.mdl",
	"models/player/leet/leet.mdl",
	"models/player/gign/gign.mdl",
	"models/player/vip/vip.mdl",
	"models/player/gsg9/gsg9.mdl",
	"models/player/guerilla/guerilla.mdl",
	"models/player/arctic/arctic.mdl",
	"models/player/sas/sas.mdl",
	"models/player/terror/terror.mdl",
	"models/player/urban/urban.mdl",
	"models/player/spetsnaz/spetsnaz.mdl", // CZ
	"models/player/militia/militia.mdl"    // CZ
};

bool g_skipCareerInitialSpawn = false;

static entity_field_alias_t entity_field_alias[] =
{
	{ "origin[0]", 0 },
	{ "origin[1]", 0 },
	{ "origin[2]", 0 },
	{ "angles[0]", 0 },
	{ "angles[1]", 0 },
	{ "angles[2]", 0 },
};

static entity_field_alias_t player_field_alias[] =
{
	{ "origin[0]", 0 },
	{ "origin[1]", 0 },
	{ "origin[2]", 0 },
};

static entity_field_alias_t custom_entity_field_alias[] =
{
	{ "origin[0]", 0 },
	{ "origin[1]", 0 },
	{ "origin[2]", 0 },
	{ "angles[0]", 0 },
	{ "angles[1]", 0 },
	{ "angles[2]", 0 },
	{ "skin",      0 },
	{ "sequence",  0 },
	{ "animtime",  0 },
};

bool g_bServerActive = false;
bool g_bItemCreatedByBuying = false;
PLAYERPVSSTATUS g_PVSStatus[MAX_CLIENTS];
unsigned short m_usResetDecals;
unsigned short g_iShadowSprite;

void LinkUserMessages()
{
	if (gmsgCurWeapon)
		return;

	gmsgCurWeapon     = REG_USER_MSG("CurWeapon", 3);
	gmsgGeigerRange   = REG_USER_MSG("Geiger", 1);
	gmsgFlashlight    = REG_USER_MSG("Flashlight", 2);
	gmsgFlashBattery  = REG_USER_MSG("FlashBat", 1);
	gmsgHealth        = REG_USER_MSG("Health", 1);
	gmsgDamage        = REG_USER_MSG("Damage", 12);
	gmsgBattery       = REG_USER_MSG("Battery", 2);
	gmsgTrain         = REG_USER_MSG("Train", 1);
	gmsgHudTextPro    = REG_USER_MSG("HudTextPro", -1);
	gmsgHudText       = REG_USER_MSG("HudText", -1);
	gmsgSayText       = REG_USER_MSG("SayText", -1);
	gmsgTextMsg       = REG_USER_MSG("TextMsg", -1);
	gmsgWeaponList    = REG_USER_MSG("WeaponList", -1);
	gmsgResetHUD      = REG_USER_MSG("ResetHUD", 0);
	gmsgInitHUD       = REG_USER_MSG("InitHUD", 0);
	gmsgViewMode      = REG_USER_MSG("ViewMode", 0);
	gmsgShowGameTitle = REG_USER_MSG("GameTitle", 1);
	gmsgDeathMsg      = REG_USER_MSG("DeathMsg", -1);
	gmsgScoreAttrib   = REG_USER_MSG("ScoreAttrib", 2);
	gmsgScoreInfo     = REG_USER_MSG("ScoreInfo", 9);
	gmsgTeamInfo      = REG_USER_MSG("TeamInfo", -1);
	gmsgTeamScore     = REG_USER_MSG("TeamScore", -1);
	gmsgGameMode      = REG_USER_MSG("GameMode", 1);
	gmsgMOTD          = REG_USER_MSG("MOTD", -1);
	gmsgServerName    = REG_USER_MSG("ServerName", -1);
	gmsgAmmoPickup    = REG_USER_MSG("AmmoPickup", 2);
	gmsgWeapPickup    = REG_USER_MSG("WeapPickup", 1);
	gmsgItemPickup    = REG_USER_MSG("ItemPickup", -1);
	gmsgHideWeapon    = REG_USER_MSG("HideWeapon", 1);
	gmsgSetFOV        = REG_USER_MSG("SetFOV", 1);
	gmsgShowMenu      = REG_USER_MSG("ShowMenu", -1);
	gmsgShake         = REG_USER_MSG("ScreenShake", 6);
	gmsgFade          = REG_USER_MSG("ScreenFade", 10);
	gmsgAmmoX         = REG_USER_MSG("AmmoX", 2);
	gmsgSendAudio     = REG_USER_MSG("SendAudio", -1);
	gmsgRoundTime     = REG_USER_MSG("RoundTime", 2);
	gmsgMoney         = REG_USER_MSG("Money", 5);
	gmsgArmorType     = REG_USER_MSG("ArmorType", 1);
	gmsgBlinkAcct     = REG_USER_MSG("BlinkAcct", 1);
	gmsgStatusValue   = REG_USER_MSG("StatusValue", -1);
	gmsgStatusText    = REG_USER_MSG("StatusText", -1);
	gmsgStatusIcon    = REG_USER_MSG("StatusIcon", -1);
	gmsgBarTime       = REG_USER_MSG("BarTime", 2);
	gmsgReloadSound   = REG_USER_MSG("ReloadSound", 2);
	gmsgCrosshair     = REG_USER_MSG("Crosshair", 1);
	gmsgNVGToggle     = REG_USER_MSG("NVGToggle", 1);
	gmsgRadar         = REG_USER_MSG("Radar", 7);
	gmsgSpectator     = REG_USER_MSG("Spectator", 2);
	gmsgVGUIMenu      = REG_USER_MSG("VGUIMenu", -1);
	gmsgTutorText     = REG_USER_MSG("TutorText", -1);
	gmsgTutorLine     = REG_USER_MSG("TutorLine", -1);
	gmsgTutorState    = REG_USER_MSG("TutorState", -1);
	gmsgTutorClose    = REG_USER_MSG("TutorClose", -1);
	gmsgAllowSpec     = REG_USER_MSG("AllowSpec", 1);
	gmsgBombDrop      = REG_USER_MSG("BombDrop", 7);
	gmsgBombPickup    = REG_USER_MSG("BombPickup", 0);
	gmsgSendCorpse    = REG_USER_MSG("ClCorpse", -1);
	gmsgHostagePos    = REG_USER_MSG("HostagePos", 8);
	gmsgHostageK      = REG_USER_MSG("HostageK", 1);
	gmsgHLTV          = REG_USER_MSG("HLTV", 2);
	gmsgSpecHealth    = REG_USER_MSG("SpecHealth", 1);
	gmsgForceCam      = REG_USER_MSG("ForceCam", 3);
	gmsgADStop        = REG_USER_MSG("ADStop", 0);
	gmsgReceiveW      = REG_USER_MSG("ReceiveW", 1);
	gmsgCZCareer      = REG_USER_MSG("CZCareer", -1);
	gmsgCZCareerHUD   = REG_USER_MSG("CZCareerHUD", -1);
	gmsgShadowIdx     = REG_USER_MSG("ShadowIdx", 4);
	gmsgTaskTime      = REG_USER_MSG("TaskTime", 4);
	gmsgScenarioIcon  = REG_USER_MSG("Scenario", -1);
	gmsgBotVoice      = REG_USER_MSG("BotVoice", 2);
	gmsgBuyClose      = REG_USER_MSG("BuyClose", 0);
	gmsgSpecHealth2   = REG_USER_MSG("SpecHealth2", 2);
	gmsgBarTime2      = REG_USER_MSG("BarTime2", 4);
	gmsgItemStatus    = REG_USER_MSG("ItemStatus", 1);
	gmsgLocation      = REG_USER_MSG("Location", -1);
	gmsgBotProgress   = REG_USER_MSG("BotProgress", -1);
	gmsgBrass         = REG_USER_MSG("Brass", -1);
	gmsgFog           = REG_USER_MSG("Fog", 7);
	gmsgShowTimer     = REG_USER_MSG("ShowTimer", 0);
	gmsgHudTextArgs   = REG_USER_MSG("HudTextArgs", -1);

#ifdef BUILD_LATEST
	gmsgAccount       = REG_USER_MSG("Account", 5);
	gmsgHealthInfo    = REG_USER_MSG("HealthInfo", 5);
#endif
}

void WriteSigonMessages()
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		ItemInfo &info = CBasePlayerItem::m_ItemInfoArray[i];
		if (!info.iId)
			continue;

		const char *pszName;
		if (!info.pszName)
			pszName = "Empty";
		else
			pszName = info.pszName;

		int iFlags = info.iFlags;

#ifdef PLAY_GAMEDLL
		// TODO: fix test demo
		iFlags &= ~ITEM_FLAG_CUSTOM;
#endif

		MESSAGE_BEGIN(MSG_INIT, gmsgWeaponList);
			WRITE_STRING(pszName);
			WRITE_BYTE(CBasePlayer::GetAmmoIndex(info.pszAmmo1));
			WRITE_BYTE(info.iMaxAmmo1);
			WRITE_BYTE(CBasePlayer::GetAmmoIndex(info.pszAmmo2));
			WRITE_BYTE(info.iMaxAmmo2);
			WRITE_BYTE(info.iSlot);
			WRITE_BYTE(info.iPosition);
			WRITE_BYTE(info.iId);
			WRITE_BYTE(iFlags);
		MESSAGE_END();
	}
}

int CMD_ARGC_()
{
	if (!UseBotArgs)
		return CMD_ARGC();

	int i = 0;
	while (BotArgs[i])
		i++;

	return i;
}

const char *CMD_ARGV_(int i)
{
	if (!UseBotArgs)
		return CMD_ARGV(i);

	if (i < 4)
		return BotArgs[i];

	return nullptr;
}

NOXREF void set_suicide_frame(entvars_t *pev)
{
	if (!FStrEq(STRING(pev->model), "models/player.mdl"))
		return;

	pev->solid = SOLID_NOT;
	pev->movetype = MOVETYPE_TOSS;
	pev->deadflag = DEAD_DEAD;
	pev->nextthink = -1;
}

void BlinkAccount(CBasePlayer *pPlayer, int numBlinks)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgBlinkAcct, nullptr, pPlayer->pev);
		WRITE_BYTE(numBlinks);
	MESSAGE_END();
}

BOOL EXT_FUNC ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
	return g_pGameRules->ClientConnected(pEntity, pszName, pszAddress, szRejectReason);
}

void EXT_FUNC ClientDisconnect(edict_t *pEntity)
{
	CBasePlayer *pPlayer = CBasePlayer::Instance(pEntity);

	if (!g_pGameRules->IsGameOver())
	{
		UTIL_ClientPrintAll(HUD_PRINTNOTIFY, "#Game_disconnected", STRING(pEntity->v.netname));
#ifndef REGAMEDLL_FIXES
		CSound *pSound = CSoundEnt::SoundPointerForIndex(CSoundEnt::ClientSoundIndex(pEntity));

		if (pSound)
			pSound->Reset();
#endif
		pEntity->v.takedamage = DAMAGE_NO;
		pEntity->v.solid = SOLID_NOT;
		pEntity->v.flags = FL_DORMANT;

		if (pPlayer)
		{
			pPlayer->Disconnect();
		}

		UTIL_SetOrigin(&pEntity->v, pEntity->v.origin);
		g_pGameRules->ClientDisconnected(pEntity);
	}

#ifndef REGAMEDLL_FIXES
	if (TheBots && pPlayer && pPlayer->IsBot())
#else
	// These checks are already inside into this CCSBotManager::ClientDisconnect
	if (TheBots)
#endif
	{
		TheBots->ClientDisconnect(pPlayer);
	}
}

void respawn(entvars_t *pev, BOOL fCopyCorpse)
{
	if (gpGlobals->coop || gpGlobals->deathmatch)
	{
		if (CSGameRules()->m_iTotalRoundsPlayed > 0)
			CSGameRules()->MarkSpawnSkipped();

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);
		if (CSGameRules()->IsCareer() && CSGameRules()->ShouldSkipSpawn() && pPlayer->IsAlive())
			g_skipCareerInitialSpawn = true;

		pPlayer->Spawn();
		g_skipCareerInitialSpawn = false;
	}
	else if (pev->deadflag > DEAD_NO)
	{
		SERVER_COMMAND("reload\n");
	}
}

// Suicide...
void EXT_FUNC ClientKill(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	// prevent suiciding too often
	if (pPlayer->m_fNextSuicideTime > gpGlobals->time)
		return;

	// don't let them suicide for 1 second after suiciding
	pPlayer->m_fNextSuicideTime = gpGlobals->time + 1.0f;
	pPlayer->Kill();
}

LINK_HOOK_VOID_CHAIN(ShowMenu, (CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText), pPlayer, bitsValidSlots, nDisplayTime, fNeedMore, pszText)

void EXT_FUNC __API_HOOK(ShowMenu)(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, nullptr, pPlayer->pev);
		WRITE_SHORT(bitsValidSlots);
		WRITE_CHAR(nDisplayTime);
		WRITE_BYTE(fNeedMore);
		WRITE_STRING(pszText);
	MESSAGE_END();
}

LINK_HOOK_VOID_CHAIN(ShowVGUIMenu, (CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu), pPlayer, MenuType, BitMask, szOldMenu);

void EXT_FUNC __API_HOOK(ShowVGUIMenu)(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu)
{
#ifdef REGAMEDLL_ADD
	if (CSGameRules()->ShouldSkipShowMenu()) {
		CSGameRules()->MarkShowMenuSkipped();
		pPlayer->ResetMenu();
		return;
	}

	if (pPlayer->CSPlayer()->m_bForceShowMenu) {
		ShowMenu(pPlayer, BitMask, -1, 0, szOldMenu);
		return;
	}

#endif

	if (pPlayer->m_bVGUIMenus || MenuType > VGUI_Menu_Buy_Item)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgVGUIMenu, nullptr, pPlayer->pev);
			WRITE_BYTE(MenuType);
			WRITE_SHORT(BitMask);
			WRITE_CHAR(-1);
			WRITE_BYTE(0);
			WRITE_STRING(" ");
		MESSAGE_END();
	}
	else
		ShowMenu(pPlayer, BitMask, -1, 0, szOldMenu);
}

NOXREF int CountTeams()
{
	int iNumCT = 0, iNumTerrorist = 0;

	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (pEntity->IsDormant())
			continue;

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (pPlayer->m_iTeam == UNASSIGNED)
			continue;

		if (pPlayer->IsDormant())
			continue;

		if (pPlayer->m_iTeam == SPECTATOR)
			continue;

		if (pPlayer->m_iTeam == CT)
			iNumCT++;

		else if (pPlayer->m_iTeam == TERRORIST)
			iNumTerrorist++;
	}

	return iNumCT - iNumTerrorist;
}

void ListPlayers(CBasePlayer *current)
{
	char message[120] = "", cNumber[12];

	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (pEntity->IsDormant())
			continue;

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);
		int iUserID = GETPLAYERUSERID(ENT(pPlayer->pev));

		Q_sprintf(cNumber, "%d", iUserID);
		Q_strcpy(message, "\n");
		Q_strcat(message, cNumber);
		Q_strcat(message, " : ");
		Q_strcat(message, STRING(pPlayer->pev->netname));

		ClientPrint(current->pev, HUD_PRINTCONSOLE, message);
	}

	ClientPrint(current->pev, HUD_PRINTCONSOLE, "\n");
}

int CountTeamPlayers(int iTeam)
{
	int nCount = 0;
	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (pEntity->IsDormant())
			continue;

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);
		if (pPlayer->m_iTeam == iTeam)
		{
			nCount++;
		}
	}

	return nCount;
}

void ProcessKickVote(CBasePlayer *pVotingPlayer, CBasePlayer *pKickPlayer)
{
	CBaseEntity *pTempEntity;
	CBasePlayer *pTempPlayer;
	int iValidVotes;
	int iVoteID;
	int iVotesNeeded;
	float fKickPercent;

	if (!pVotingPlayer || !pKickPlayer)
		return;

	int iTeamCount = CountTeamPlayers(pVotingPlayer->m_iTeam);

	if (iTeamCount < 3)
		return;

	iValidVotes = 0;
	pTempEntity = nullptr;
	iVoteID = pVotingPlayer->m_iCurrentKickVote;

	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		if (pTempEntity->IsDormant())
			continue;

		pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

		if (!pTempPlayer || pTempPlayer->m_iTeam == UNASSIGNED)
			continue;

		if (pTempPlayer->m_iTeam == pVotingPlayer->m_iTeam && pTempPlayer->m_iCurrentKickVote == iVoteID)
			iValidVotes++;
	}

	if (kick_percent.value < 0)
		CVAR_SET_STRING("mp_kickpercent", "0.0");

	else if (kick_percent.value > 1)
		CVAR_SET_STRING("mp_kickpercent", "1.0");

	iVotesNeeded = iValidVotes;
	fKickPercent = (iTeamCount * kick_percent.value + 0.5);

	if (iVotesNeeded >= int(fKickPercent))
	{
#ifdef REGAMEDLL_FIXES
		SERVER_COMMAND(UTIL_VarArgs("kick #%d \"You have been voted off.\"\n", iVoteID));
		SERVER_EXECUTE();
#endif

		UTIL_ClientPrintAll(HUD_PRINTCENTER, "#Game_kicked", STRING(pKickPlayer->pev->netname));

#ifndef REGAMEDLL_FIXES
		SERVER_COMMAND(UTIL_VarArgs("kick #%d\n", iVoteID));
#endif
		pTempEntity = nullptr;

		while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
		{
			if (FNullEnt(pTempEntity->edict()))
				break;

			if (pTempEntity->IsDormant())
				continue;

			pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

			if (!pTempPlayer || pTempPlayer->m_iTeam == UNASSIGNED)
				continue;

			if (pTempPlayer->m_iTeam == pVotingPlayer->m_iTeam && pTempPlayer->m_iCurrentKickVote == iVoteID)
				pTempPlayer->m_iCurrentKickVote = 0;
		}
	}
}

void CheckStartMoney()
{
	int money = int(startmoney.value);

#ifndef REGAMEDLL_ADD
	if (money > 16000)
		CVAR_SET_FLOAT("mp_startmoney", 16000);
	else if (money < 800)
		CVAR_SET_FLOAT("mp_startmoney", 800);
#else
	int max_money = int(maxmoney.value);
	if (max_money > MAX_MONEY_THRESHOLD)
	{
		max_money = MAX_MONEY_THRESHOLD;
		CVAR_SET_FLOAT("mp_maxmoney", MAX_MONEY_THRESHOLD);
	}

	if (money > max_money)
		CVAR_SET_FLOAT("mp_startmoney", max_money);
	else if (money < 0)
		CVAR_SET_FLOAT("mp_startmoney", 0);
#endif

}

void EXT_FUNC ClientPutInServer(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);

	pPlayer->SetCustomDecalFrames(-1);
	pPlayer->SetPrefsFromUserinfo(GET_INFO_BUFFER(pEntity));

	if (!g_pGameRules->IsMultiplayer())
	{
		pPlayer->Spawn();
		return;
	}

#ifdef REGAMEDLL_FIXES
	pPlayer->m_bHasDefuser = false;
#endif
	pPlayer->m_bNotKilled = true;
	pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
	pPlayer->m_iTeamKills = 0;
	pPlayer->m_bJustConnected = true;
	pPlayer->Spawn();
	pPlayer->m_bTeamChanged = false;
	pPlayer->m_iNumSpawns = 0;

	CheckStartMoney();

#ifdef REGAMEDLL_ADD
	pPlayer->AddAccount(startmoney.value, RT_PLAYER_JOIN);
#else
	pPlayer->m_iAccount = int(startmoney.value);
#endif

	pPlayer->m_fGameHUDInitialized = FALSE;
	pPlayer->m_flDisplayHistory &= ~DHF_ROUND_STARTED;
	pPlayer->pev->flags |= FL_SPECTATOR;
	pPlayer->pev->solid = SOLID_NOT;
	pPlayer->pev->movetype = MOVETYPE_NOCLIP;
	pPlayer->pev->effects = (EF_NODRAW | EF_NOINTERP);
	pPlayer->pev->takedamage = DAMAGE_NO;
	pPlayer->pev->deadflag = DEAD_DEAD;
	pPlayer->pev->velocity = g_vecZero;
	pPlayer->pev->punchangle = g_vecZero;
	pPlayer->m_iJoiningState = READINGLTEXT;
	pPlayer->m_iTeam = UNASSIGNED;
	pPlayer->pev->fixangle = 1;
	pPlayer->m_iModelName = MODEL_URBAN;
	pPlayer->m_bContextHelp = true;
	pPlayer->m_bHasNightVision = false;
	pPlayer->m_iHostagesKilled = 0;
	pPlayer->m_iMapVote = 0;
	pPlayer->m_iCurrentKickVote = 0;
	pPlayer->m_fDeadTime = 0;
	pPlayer->has_disconnected = false;
	pPlayer->m_iMenu = Menu_OFF;
	pPlayer->ClearAutoBuyData();
	pPlayer->m_rebuyString = nullptr;

	SET_CLIENT_MAXSPEED(ENT(pPlayer->pev), 1);
	SET_MODEL(ENT(pPlayer->pev), "models/player.mdl");

	pPlayer->SetThink(nullptr);

	CBaseEntity *pTarget = nullptr;
	pPlayer->m_pIntroCamera = UTIL_FindEntityByClassname(nullptr, "trigger_camera");

#ifndef REGAMEDLL_FIXES
	if (g_pGameRules && g_pGameRules->IsMultiplayer())
	{
		CSGameRules()->m_bMapHasCameras = (pPlayer->m_pIntroCamera != nullptr);
	}
#endif

	if (pPlayer->m_pIntroCamera)
	{
		// find the target (by default info_target) for the camera view direction.
		pTarget = UTIL_FindEntityByTargetname(nullptr, STRING(pPlayer->m_pIntroCamera->pev->target));
	}

	if (pPlayer->m_pIntroCamera && pTarget)
	{
		Vector CamAngles = UTIL_VecToAngles((pTarget->pev->origin - pPlayer->m_pIntroCamera->pev->origin).Normalize());
		CamAngles.x = -CamAngles.x;

		UTIL_SetOrigin(pPlayer->pev, pPlayer->m_pIntroCamera->pev->origin);

		pPlayer->pev->angles = CamAngles;
		pPlayer->pev->v_angle = pPlayer->pev->angles;

		pPlayer->m_fIntroCamTime =
#ifdef REGAMEDLL_FIXES
			(CSGameRules()->m_bMapHasCameras <= 1) ? 0.0 : // no need to refresh cameras if map has only one
#endif
			gpGlobals->time + 6;

		pPlayer->pev->view_ofs = g_vecZero;
	}
#ifndef REGAMEDLL_FIXES
	else
	{
		pPlayer->m_iTeam = CT;

		if (g_pGameRules)
		{
			g_pGameRules->GetPlayerSpawnSpot(pPlayer);
		}

		pPlayer->m_iTeam = UNASSIGNED;
		pPlayer->pev->v_angle = g_vecZero;
		pPlayer->pev->angles = gpGlobals->v_forward;
	}
#endif

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, (CBaseEntity *)pPlayer);
	}

	pPlayer->m_iJoiningState = SHOWLTEXT;

	static char sName[128];
	Q_strcpy(sName, STRING(pPlayer->pev->netname));

	for (char *pApersand = sName; pApersand && *pApersand != '\0'; pApersand++)
	{
		if (*pApersand == '%')
			*pApersand = ' ';
	}

#ifdef REGAMEDLL_API
	pPlayer->CSPlayer()->OnConnect();
#endif

	UTIL_ClientPrintAll(HUD_PRINTNOTIFY, "#Game_connected", (sName[0] != '\0') ? sName : "<unconnected>");
}

void Host_Say(edict_t *pEntity, BOOL teamonly)
{
	int j;
	char *p;
	char text[128];
	char szTemp[256];
	const char *cpSay = "say";
	const char *cpSayTeam = "say_team";
	const char *pcmd = CMD_ARGV_(0);
	bool bSenderDead = false;

	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);

	if (pPlayer->m_flLastTalk != 0.0f && gpGlobals->time - pPlayer->m_flLastTalk < 0.66f)
		return;

	pPlayer->m_flLastTalk = gpGlobals->time;

	if (pPlayer->pev->deadflag != DEAD_NO)
		bSenderDead = true;

	// We can get a raw string now, without the "say " prepended
	if (CMD_ARGC_() == 0)
		return;

	if (!Q_stricmp(pcmd, cpSay) || !Q_stricmp(pcmd, cpSayTeam))
	{
		if (CMD_ARGC_() >= 2)
		{
			Q_strlcpy(szTemp, CMD_ARGS());
			p = szTemp;
		}
		else
		{
			// say with a blank message, nothing to do
			return;
		}
	}
	else // Raw text, need to prepend argv[0]
	{
		if (CMD_ARGC_() >= 2)
		{
			Q_sprintf(szTemp, "%s %s", pcmd, CMD_ARGS());
		}
		else
		{
			// Just a one word command, use the first word...sigh
			Q_sprintf(szTemp, "%s", pcmd);
		}

		p = szTemp;
	}

#ifdef REGAMEDLL_FIXES
	Q_StripPrecedingAndTrailingWhitespace(p);
#endif

	// remove quotes (leading & trailing) if present
	if (*p == '"')
	{
		p++;
		p[Q_strlen(p) - 1] = '\0';
	}

	// Check if buffer contains an invalid unicode sequence
	// This can happen after truncation up to 127 chars into SV_ParseStringCommand
	if (!Q_UnicodeValidate(p))
	{
		// Try fix invalid sequence in UTF-8
		Q_UnicodeRepair(p);
	}

	// make sure the text has content
	if (!p[0])
	{
		// no character found, so say nothing
		return;
	}

	Q_StripUnprintableAndSpace(p);

	if (Q_strlen(p) <= 0)
		return;

	const char *placeName = nullptr;
	const char *pszFormat = nullptr;
	char *pszConsoleFormat = nullptr;
	bool consoleUsesPlaceName = false;

	// team only
	if (teamonly)
	{
		if ((
#ifdef REGAMEDLL_ADD
			location_area_info.value >= 2 ||
#endif
			AreRunningCZero()) && (pPlayer->m_iTeam == CT || pPlayer->m_iTeam == TERRORIST))
		{
			// search the place name where is located the player
			Place playerPlace = TheNavAreaGrid.GetPlace(&pPlayer->pev->origin);
			const BotPhraseList *placeList = TheBotPhrases->GetPlaceList();

			for (auto phrase : *placeList)
			{
				if (phrase->GetID() == playerPlace)
				{
					placeName = phrase->GetName();
					break;
				}
			}

			if (!placeName)
				placeName = TheNavAreaGrid.IDToName(playerPlace);
		}

		bool bUseLocFallback = false;
#ifdef REGAMEDLL_ADD
		if (chat_loc_fallback.value)
			bUseLocFallback = true;
#endif

		if (pPlayer->m_iTeam == CT)
		{
			if (bSenderDead)
			{
				pszFormat = "#Cstrike_Chat_CT_Dead";
				pszConsoleFormat = "*DEAD*(Counter-Terrorist) %s : %s";
			}
			else if (placeName)
			{
				pszFormat = bUseLocFallback ? "\x1(Counter-Terrorist) \x3%s1\x1 @ \x4%s3\x1 :  %s2" : "#Cstrike_Chat_CT_Loc";
				pszConsoleFormat = "*(Counter-Terrorist) %s @ %s : %s";
				consoleUsesPlaceName = true;
			}
			else
			{
				pszFormat = "#Cstrike_Chat_CT";
				pszConsoleFormat = "(Counter-Terrorist) %s : %s";
			}
		}
		else if (pPlayer->m_iTeam == TERRORIST)
		{
			if (bSenderDead)
			{
				pszFormat = "#Cstrike_Chat_T_Dead";
				pszConsoleFormat = "*DEAD*(Terrorist) %s : %s";
			}
			else if (placeName)
			{
				pszFormat = bUseLocFallback ? "\x1(Terrorist) \x3%s1\x1 @ \x4%s3\x1 :  %s2" : "#Cstrike_Chat_T_Loc";
				pszConsoleFormat = "(Terrorist) %s @ %s : %s";
				consoleUsesPlaceName = true;
			}
			else
			{
				pszFormat = "#Cstrike_Chat_T";
				pszConsoleFormat = "(Terrorist) %s : %s";
			}
		}
		else
		{
			pszFormat = "#Cstrike_Chat_Spec";
			pszConsoleFormat = "(Spectator) %s : %s";
		}
	}
	// everyone
	else
	{
		if (bSenderDead)
		{
			if (pPlayer->m_iTeam == SPECTATOR)
			{
				pszFormat = "#Cstrike_Chat_AllSpec";
				pszConsoleFormat = "*SPEC* %s : %s";
			}
			else
			{
				pszFormat = "#Cstrike_Chat_AllDead";
				pszConsoleFormat = "*DEAD* %s : %s";
			}
		}
		else
		{
			pszFormat = "#Cstrike_Chat_All";
			pszConsoleFormat = "%s : %s";
		}
	}

	text[0] = '\0';

	// -3 for /n and null terminator
	j = sizeof(text) - 3 - Q_strlen(text) - Q_strlen(pszFormat);

	if (placeName)
	{
		j -= Q_strlen(placeName) + 1;
	}

	if ((signed int)Q_strlen(p) > j)
		p[j] = 0;

	for (char *pAmpersand = p; pAmpersand && *pAmpersand != '\0'; pAmpersand++)
	{
		if (pAmpersand[0] == '%')
		{
			if (pAmpersand[1] != 'l' && pAmpersand[1] != ' ' && pAmpersand[1] != '\0')
			{
				pAmpersand[0] = ' ';
			}
		}
	}

	Q_strcat(text, p);
	Q_strcat(text, "\n");

	// loop through all players
	// Start with the first player.
	// This may return the world in single player if the client types something between levels or during spawn
	// so check it, or it will infinite loop

	CBasePlayer *pReceiver = nullptr;
	while ((pReceiver = UTIL_FindEntityByClassname(pReceiver, "player")))
	{
		if (FNullEnt(pReceiver->edict()))
			break;

		if (!pReceiver->pev)
			continue;

		if (pReceiver->edict() == pEntity)
			continue;

		if (pReceiver->IsDormant())
			continue;

		// Not a client ? (should never be true)
		if (!pReceiver->IsNetClient())
			continue;

		// can the receiver hear the sender? or has he muted him?
		if (gpGlobals->deathmatch != 0.0f && CSGameRules()->m_VoiceGameMgr.PlayerHasBlockedPlayer(pReceiver, pPlayer))
			continue;

		if (teamonly && pReceiver->m_iTeam != pPlayer->m_iTeam)
			continue;

		if (
#ifdef REGAMEDLL_ADD
			!(bool)allchat.value &&
#endif
			((pReceiver->pev->deadflag != DEAD_NO && !bSenderDead) || (pReceiver->pev->deadflag == DEAD_NO && bSenderDead)))
		{
			if (!(pPlayer->pev->flags & FL_PROXY))
				continue;
		}

		if ((pReceiver->m_iIgnoreGlobalChat == IGNOREMSG_ENEMY && pReceiver->m_iTeam == pPlayer->m_iTeam)
			|| pReceiver->m_iIgnoreGlobalChat == IGNOREMSG_NONE)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgSayText, nullptr, pReceiver->pev);
				WRITE_BYTE(ENTINDEX(pEntity));
				WRITE_STRING(pszFormat);
				WRITE_STRING("");
				WRITE_STRING(text);

				if (placeName)
				{
					WRITE_STRING(placeName);
				}

			MESSAGE_END();
		}
	}

	// print to the sending client
	MESSAGE_BEGIN(MSG_ONE, gmsgSayText, nullptr, &pEntity->v);
		WRITE_BYTE(ENTINDEX(pEntity));
		WRITE_STRING(pszFormat);
		WRITE_STRING("");
		WRITE_STRING(text);

		if (placeName)
		{
			WRITE_STRING(placeName);
		}

	MESSAGE_END();

#ifdef REGAMEDLL_FIXES
	// don't to type for listenserver
	if (IS_DEDICATED_SERVER())
#endif
	{
		// echo to server console
		if (pszConsoleFormat)
		{
			if (placeName && consoleUsesPlaceName)
				SERVER_PRINT(UTIL_VarArgs(pszConsoleFormat, STRING(pPlayer->pev->netname), placeName, text));
			else
				SERVER_PRINT(UTIL_VarArgs(pszConsoleFormat, STRING(pPlayer->pev->netname), text));
		}
		else
		{
			SERVER_PRINT(text);
		}
	}

	if (logmessages.value)
	{
		const char *temp = teamonly ? "say_team" : "say";
		const char *deadText = (pPlayer->m_iTeam != SPECTATOR && bSenderDead) ? " (dead)" : "";

		char *szTeam = GetTeam(pPlayer->m_iTeam);

		UTIL_LogPrintf("\"%s<%i><%s><%s>\" %s \"%s\"%s\n", STRING(pPlayer->pev->netname), GETPLAYERUSERID(pPlayer->edict()), GETPLAYERAUTHID(pPlayer->edict()),
			szTeam, temp, p, deadText);
	}
}

bool CanBuyThis(CBasePlayer *pPlayer, int iWeapon)
{
	if (pPlayer->HasShield() && iWeapon == WEAPON_ELITE)
		return false;

	if (pPlayer->HasShield() && iWeapon == WEAPON_SHIELDGUN)
		return false;

	if (pPlayer->m_rgpPlayerItems[PISTOL_SLOT] && pPlayer->m_rgpPlayerItems[PISTOL_SLOT]->m_iId == WEAPON_ELITE && iWeapon == WEAPON_SHIELDGUN)
		return false;

	if (pPlayer->m_rgpPlayerItems[PRIMARY_WEAPON_SLOT] && pPlayer->m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]->m_iId == iWeapon)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cstrike_Already_Own_Weapon");
		}

		return false;
	}

	if (pPlayer->m_rgpPlayerItems[PISTOL_SLOT] && pPlayer->m_rgpPlayerItems[PISTOL_SLOT]->m_iId == iWeapon)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cstrike_Already_Own_Weapon");
		}

		return false;
	}

	if (!CanBuyWeaponByMaptype(pPlayer->m_iTeam, (WeaponIdType)iWeapon, CSGameRules()->m_bMapHasVIPSafetyZone == TRUE))
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Buy_This");
		}

		return false;
	}

	return true;
}

void BuyPistol(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 5)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	switch (iSlot)
	{
	case 1:
		buyWeapon = WEAPON_GLOCK18;
		break;
	case 2:
		buyWeapon = WEAPON_USP;
		break;
	case 3:
		buyWeapon = WEAPON_P228;
		break;
	case 4:
		buyWeapon = WEAPON_DEAGLE;
		break;
	case 5:
		buyWeapon = (pPlayer->m_iTeam == CT) ? WEAPON_FIVESEVEN : WEAPON_ELITE;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuyShotgun(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 2)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	switch (iSlot)
	{
	case 1:
		buyWeapon = WEAPON_M3;
		break;
	case 2:
		buyWeapon = WEAPON_XM1014;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuySubMachineGun(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 4)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	switch (iSlot)
	{
	case 1:
		buyWeapon = (pPlayer->m_iTeam == CT) ? WEAPON_TMP : WEAPON_MAC10;
		break;
	case 2:
		buyWeapon = WEAPON_MP5N;
		break;
	case 3:
		buyWeapon = WEAPON_UMP45;
		break;
	case 4:
		buyWeapon = WEAPON_P90;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuyRifle(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot < 1 || iSlot > 6)
		return;

	WeaponIdType buyWeapon = WEAPON_NONE;
	bool bIsCT = (pPlayer->m_iTeam == CT) ? true : false;

	switch (iSlot)
	{
	case 2:
		buyWeapon = bIsCT ? WEAPON_SCOUT : WEAPON_AK47;
		break;
	case 3:
		buyWeapon = bIsCT ? WEAPON_M4A1 : WEAPON_SCOUT;
		break;
	case 4:
		buyWeapon = bIsCT ? WEAPON_AUG : WEAPON_SG552;
		break;
	case 5:
		buyWeapon = bIsCT ? WEAPON_SG550 : WEAPON_AWP;
		break;
	case 6:
		buyWeapon = bIsCT ? WEAPON_AWP : WEAPON_G3SG1;
		break;
	default:
		buyWeapon = bIsCT ? WEAPON_FAMAS : WEAPON_GALIL;
		break;
	}

	BuyWeaponByWeaponID(pPlayer, buyWeapon);
}

void BuyMachineGun(CBasePlayer *pPlayer, int iSlot)
{
	if (iSlot != 1)
		return;

	BuyWeaponByWeaponID(pPlayer, WEAPON_M249);
}

LINK_HOOK_VOID_CHAIN(BuyItem, (CBasePlayer *pPlayer, int iSlot), pPlayer, iSlot)

void EXT_FUNC __API_HOOK(BuyItem)(CBasePlayer *pPlayer, int iSlot)
{
	int iItemPrice = 0;
	const char *pszItem = nullptr;

	if (!pPlayer->CanPlayerBuy(true))
		return;

	if (pPlayer->m_iTeam == CT)
	{
		if (iSlot < 1 || iSlot > 8)
			return;
	}
	else
	{
		if (iSlot < 1 || iSlot > 6)
			return;
	}

	bool bFullArmor = (pPlayer->pev->armorvalue >= 100);
	bool bHasHelmet = (pPlayer->m_iKevlar == ARMOR_VESTHELM);
	bool bEnoughMoney = false;

	switch (iSlot)
	{
		case MENU_SLOT_ITEM_VEST:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_KEVLAR, ITEM_TYPE_BUYING))
				return;
#endif
			if (bFullArmor)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar");
				}

				return;
			}

			if (pPlayer->m_iAccount >= KEVLAR_PRICE)
			{
				if (bHasHelmet && g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Helmet_Bought_Kevlar");
				}

				bEnoughMoney = true;
				pszItem = "item_kevlar";
				iItemPrice = KEVLAR_PRICE;
			}
			break;
		}
		case MENU_SLOT_ITEM_VESTHELM:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_ASSAULT, ITEM_TYPE_BUYING))
				return;
#endif
			if (bFullArmor)
			{
				if (bHasHelmet)
				{
					if (g_bClientPrintEnable)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar_Helmet");
					}

					return;
				}

				if (pPlayer->m_iAccount >= HELMET_PRICE)
				{
					if (g_bClientPrintEnable)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Kevlar_Bought_Helmet");
					}

					bEnoughMoney = true;
					pszItem = "item_assaultsuit";
					iItemPrice = HELMET_PRICE;
				}
				break;
			}
			else
			{
				if (bHasHelmet)
				{
					if (pPlayer->m_iAccount >= KEVLAR_PRICE)
					{
						if (g_bClientPrintEnable)
						{
							ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_Helmet_Bought_Kevlar");
						}

						bEnoughMoney = true;
						pszItem = "item_assaultsuit";
						iItemPrice = KEVLAR_PRICE;
					}
				}
				else
				{
					if (pPlayer->m_iAccount >= ASSAULTSUIT_PRICE)
					{
						bEnoughMoney = true;
						pszItem = "item_assaultsuit";
						iItemPrice = ASSAULTSUIT_PRICE;
					}
				}
			}
			break;
		}
		case MENU_SLOT_ITEM_FLASHGREN:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_FLASHBANG, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->AmmoInventory(AMMO_FLASHBANG) >= MaxAmmoCarry(WEAPON_FLASHBANG))
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= FLASHBANG_PRICE)
			{
				bEnoughMoney = true;
				pszItem = "weapon_flashbang";
				iItemPrice = FLASHBANG_PRICE;

			}
			break;
		}
		case MENU_SLOT_ITEM_HEGREN:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_HEGRENADE, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->AmmoInventory(AMMO_HEGRENADE) >= MaxAmmoCarry(WEAPON_HEGRENADE))
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= HEGRENADE_PRICE)
			{
				bEnoughMoney = true;
				pszItem = "weapon_hegrenade";
				iItemPrice = HEGRENADE_PRICE;
			}
			break;
		}
		case MENU_SLOT_ITEM_SMOKEGREN:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_SMOKEGRENADE, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->AmmoInventory(AMMO_SMOKEGRENADE) >= MaxAmmoCarry(WEAPON_SMOKEGRENADE))
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Carry_Anymore");
				}

				return;
			}

			if (pPlayer->m_iAccount >= SMOKEGRENADE_PRICE)
			{
				bEnoughMoney = true;
				pszItem = "weapon_smokegrenade";
				iItemPrice = SMOKEGRENADE_PRICE;
			}
			break;
		}
		case MENU_SLOT_ITEM_NVG:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_NVG, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->m_bHasNightVision)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_One");
				}

				return;
			}

			if (pPlayer->m_iAccount >= NVG_PRICE)
			{
				if (!(pPlayer->m_flDisplayHistory & DHF_NIGHTVISION))
				{
					pPlayer->HintMessage("#Hint_use_nightvision");
					pPlayer->m_flDisplayHistory |= DHF_NIGHTVISION;
				}

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/equip_nvg.wav", VOL_NORM, ATTN_NORM);

				bEnoughMoney = true;
				pPlayer->m_bHasNightVision = true;
				pPlayer->AddAccount(-NVG_PRICE, RT_PLAYER_BOUGHT_SOMETHING);
				pPlayer->SendItemStatus();
			}
			break;
		}
		case MENU_SLOT_ITEM_DEFUSEKIT:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_DEFUSEKIT, ITEM_TYPE_BUYING))
				return;
#endif
			if (pPlayer->m_iTeam != CT || !CSGameRules()->m_bMapHasBombTarget)
				return;

			if (pPlayer->m_bHasDefuser)
			{
				if (g_bClientPrintEnable)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Already_Have_One");
				}

				return;
			}

			if (pPlayer->m_iAccount >= DEFUSEKIT_PRICE)
			{
				bEnoughMoney = true;
				pPlayer->GiveDefuser();
				pPlayer->AddAccount(-DEFUSEKIT_PRICE, RT_PLAYER_BOUGHT_SOMETHING);

#ifdef REGAMEDLL_FIXES
				EMIT_SOUND(ENT(pPlayer->pev), CHAN_VOICE, "items/kevlar.wav", VOL_NORM, ATTN_NORM);
#else
				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/kevlar.wav", VOL_NORM, ATTN_NORM);
#endif
			}
			break;
		}
		case MENU_SLOT_ITEM_SHIELD:
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_SHIELDGUN, ITEM_TYPE_BUYING))
				return;
#endif

			if (!CanBuyThis(pPlayer, WEAPON_SHIELDGUN))
				return;

			if (pPlayer->m_iAccount >= SHIELDGUN_PRICE)
			{
				bEnoughMoney = true;
				pPlayer->DropPrimary();
				pPlayer->GiveShield();
				pPlayer->AddAccount(-SHIELDGUN_PRICE, RT_PLAYER_BOUGHT_SOMETHING);

				EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);
			}
			break;
		}
	}

	if (!bEnoughMoney)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer);
		}

		return;
	}

	if (pszItem)
	{
		g_bItemCreatedByBuying = true;
		pPlayer->GiveNamedItem(pszItem);
		g_bItemCreatedByBuying = false;

		pPlayer->AddAccount(-iItemPrice, RT_PLAYER_BOUGHT_SOMETHING);
	}

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}
}

LINK_HOOK_CHAIN(CBaseEntity *, BuyWeaponByWeaponID, (CBasePlayer *pPlayer, WeaponIdType weaponID), pPlayer, weaponID)

CBaseEntity *EXT_FUNC __API_HOOK(BuyWeaponByWeaponID)(CBasePlayer *pPlayer, WeaponIdType weaponID)
{
	if (!pPlayer->CanPlayerBuy(true))
		return nullptr;

#ifdef REGAMEDLL_ADD
	if (pPlayer->HasRestrictItem((ItemID)weaponID, ITEM_TYPE_BUYING))
		return nullptr;
#endif

	if (!CanBuyThis(pPlayer, weaponID))
		return nullptr;

	WeaponInfoStruct *info = GetWeaponInfo(weaponID);
	if (!info || !info->entityName)
		return nullptr;

	if (pPlayer->m_iAccount < info->cost)
	{
		if (g_bClientPrintEnable)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer);
		}

		return nullptr;
	}

	if (IsPrimaryWeapon(weaponID))
	{
		pPlayer->DropPrimary();
	}
	else
	{
		pPlayer->DropSecondary();
	}

	auto pEntity = pPlayer->GiveNamedItem(info->entityName);
	pPlayer->AddAccount(-info->cost, RT_PLAYER_BOUGHT_SOMETHING);

#ifdef REGAMEDLL_ADD
	if (refill_bpammo_weapons.value > 1)
	{
		CBasePlayerItem *pItem = static_cast<CBasePlayerItem *>(pEntity);

		if (pItem) {
			pPlayer->GiveAmmo(pItem->iMaxAmmo1(), pItem->pszAmmo1(), pItem->iMaxAmmo1());
		}
	}
#endif

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
	}

	return pEntity;
}

LINK_HOOK_VOID_CHAIN(HandleMenu_ChooseAppearance, (CBasePlayer *pPlayer, int slot), pPlayer, slot)

void EXT_FUNC __API_HOOK(HandleMenu_ChooseAppearance)(CBasePlayer *pPlayer, int slot)
{
	int numSkins = AreRunningCZero() ? CZ_NUM_SKIN : CS_NUM_SKIN;

	struct
	{
		ModelName model_id;
		char *model_name;
		int model_name_index;

	} appearance;

	Q_memset(&appearance, 0, sizeof(appearance));

	if (pPlayer->m_iTeam == TERRORIST)
	{
		if ((slot > numSkins || slot < 1) && (!TheBotProfiles->GetCustomSkin(slot) || !pPlayer->IsBot()))
		{
			slot = RANDOM_LONG(1, numSkins);
		}

		switch (slot)
		{
		case 1:
			appearance.model_id = MODEL_TERROR;
			appearance.model_name = "terror";
			break;
		case 2:
			appearance.model_id = MODEL_LEET;
			appearance.model_name = "leet";
			break;
		case 3:
			appearance.model_id = MODEL_ARCTIC;
			appearance.model_name = "arctic";
			break;
		case 4:
			appearance.model_id = MODEL_GUERILLA;
			appearance.model_name = "guerilla";
			break;
		case 5:
			if (AreRunningCZero())
			{
				appearance.model_id = MODEL_MILITIA;
				appearance.model_name = "militia";
				break;
			}
		default:
			if (TheBotProfiles->GetCustomSkinModelname(slot) && pPlayer->IsBot())
			{
				appearance.model_name = (char *)TheBotProfiles->GetCustomSkinModelname(slot);
			}
			else
			{
				appearance.model_id = MODEL_TERROR;
				appearance.model_name = "terror";
			}
			break;
		}

		// default T model models/player/terror/terror.mdl
		appearance.model_name_index = 8;

	}
	else if (pPlayer->m_iTeam == CT)
	{
		if ((slot > numSkins || slot < 1) && (!TheBotProfiles->GetCustomSkin(slot) || !pPlayer->IsBot()))
		{
			slot = RANDOM_LONG(1, numSkins);
		}

		switch (slot)
		{
		case 1:
			appearance.model_id = MODEL_URBAN;
			appearance.model_name = "urban";
			break;
		case 2:
			appearance.model_id = MODEL_GSG9;
			appearance.model_name = "gsg9";
			break;
		case 3:
			appearance.model_id = MODEL_SAS;
			appearance.model_name = "sas";
			break;
		case 4:
			appearance.model_id = MODEL_GIGN;
			appearance.model_name = "gign";
			break;
		case 5:
			if (AreRunningCZero())
			{
				appearance.model_id = MODEL_SPETSNAZ;
				appearance.model_name = "spetsnaz";
				break;
			}
		default:
			if (TheBotProfiles->GetCustomSkinModelname(slot) && pPlayer->IsBot())
			{
				appearance.model_name = (char *)TheBotProfiles->GetCustomSkinModelname(slot);
			}
			else
			{
				appearance.model_id = MODEL_URBAN;
				appearance.model_name = "urban";
			}
			break;
		}

		// default CT model models/player/urban/urban.mdl
		appearance.model_name_index = 9;
	}

#ifdef REGAMEDLL_FIXES
	pPlayer->ResetMenu();
#else
	pPlayer->m_iMenu = Menu_OFF;
#endif

	// Reset the player's state
	switch (pPlayer->m_iJoiningState)
	{
	case JOINED:
		CSGameRules()->CheckWinConditions();
		break;

	case PICKINGTEAM:
	{
		pPlayer->m_iJoiningState = GETINTOGAME;

		if (CSGameRules()->IsCareer())
		{
			if (!pPlayer->IsBot())
			{
				CSGameRules()->CheckWinConditions();
			}
		}
		break;
	}
	}

	pPlayer->pev->body = 0;
	pPlayer->m_iModelName = appearance.model_id;

	pPlayer->SetClientUserInfoModel(GET_INFO_BUFFER(pPlayer->edict()), appearance.model_name);
	pPlayer->SetNewPlayerModel(sPlayerModelFiles[appearance.model_name_index]);

	if (CSGameRules()->m_bMapHasVIPSafetyZone)
	{
		if (!CSGameRules()->m_pVIP && pPlayer->m_iTeam == CT)
		{
			pPlayer->MakeVIP();
		}
	}
}

LINK_HOOK_CHAIN(BOOL, HandleMenu_ChooseTeam, (CBasePlayer *pPlayer, int slot), pPlayer, slot)

// returns true if the selection has been handled and the player's menu
// can be closed...false if the menu should be displayed again
BOOL EXT_FUNC __API_HOOK(HandleMenu_ChooseTeam)(CBasePlayer *pPlayer, int slot)
{
	// If this player is a VIP, don't allow him to switch teams/appearances unless the following conditions are met :
	// a) There is another TEAM_CT player who is in the queue to be a VIP
	// b) This player is dead

	if (pPlayer->m_bIsVIP)
	{
		if (pPlayer->pev->deadflag == DEAD_NO)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Switch_From_VIP");
			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");

			return TRUE;
		}
		else if (CSGameRules()->IsVIPQueueEmpty())
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Switch_From_VIP");
			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");

			return TRUE;
		}
	}

	TeamName team = UNASSIGNED;

	switch (slot)
	{
	case MENU_SLOT_TEAM_TERRORIST:
		team = TERRORIST;
		break;
	case MENU_SLOT_TEAM_CT:
		team = CT;
		break;
	case MENU_SLOT_TEAM_VIP:
	{
		if (CSGameRules()->m_bMapHasVIPSafetyZone && pPlayer->m_iTeam == CT)
		{
			CSGameRules()->AddToVIPQueue(pPlayer);
			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");
			return TRUE;
		}
		else
		{
			return FALSE;
		}
		break;
	}
	case MENU_SLOT_TEAM_RANDOM:
	{
		// Attempt to auto-select a team
		team = CSGameRules()->SelectDefaultTeam();
		if (team == UNASSIGNED)
		{
			if (cv_bot_auto_vacate.value > 0.0f && !pPlayer->IsBot())
			{
				team = (RANDOM_LONG(0, 1) == 0) ? TERRORIST : CT;

				bool atLeastOneLeft = UTIL_KickBotFromTeam(team);

				if (!atLeastOneLeft)
				{
					// no bots on that team, try the other
					team = (team == CT) ? TERRORIST : CT;

					atLeastOneLeft = UTIL_KickBotFromTeam(team);

					if (!atLeastOneLeft)
					{
						// couldn't kick any bots, fail
						team = UNASSIGNED;
					}
				}

				if (atLeastOneLeft)
				{
					CONSOLE_ECHO("These bots has left the game to make room for human players.\n");
				}
			}
		}

		break;
	}
	case MENU_SLOT_TEAM_SPECT:
	{
		// Prevent this is the cvar is set
		// spectator proxy
		if (!allow_spectators.value && !(pPlayer->pev->flags & FL_PROXY))
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Be_Spectator");
			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");

			return FALSE;
		}

		// are we already a spectator?
		if (pPlayer->m_iTeam == SPECTATOR)
		{
			return TRUE;
		}

		// Only spectate if we are in the freeze period or dead.
		// This is done here just in case.
		if (g_pGameRules->IsFreezePeriod() || pPlayer->pev->deadflag != DEAD_NO)
		{
			if (pPlayer->m_iTeam != UNASSIGNED && pPlayer->pev->deadflag == DEAD_NO)
			{
				if (pPlayer->Kill())
				{
					// add 1 to frags to balance out the 1 subtracted for killing yourself
					pPlayer->pev->frags++;
				}
			}

			pPlayer->RemoveAllItems(TRUE);

#ifndef REGAMEDLL_FIXES
			// NOTE: It is already does reset inside RemoveAllItems
			pPlayer->m_bHasC4 = false;
#endif

#ifdef REGAMEDLL_FIXES
			if (pPlayer->m_iTeam != SPECTATOR)
#endif
			{
				// notify other clients of player joined to team spectator
				UTIL_LogPrintf("\"%s<%i><%s><%s>\" joined team \"SPECTATOR\"\n", STRING(pPlayer->pev->netname),
					GETPLAYERUSERID(pPlayer->edict()), GETPLAYERAUTHID(pPlayer->edict()), GetTeam(pPlayer->m_iTeam));
			}

			pPlayer->m_iTeam = SPECTATOR;
			pPlayer->m_iJoiningState = JOINED;

			// Reset money
#ifdef REGAMEDLL_ADD
			pPlayer->AddAccount(0, RT_PLAYER_SPEC_JOIN, false);
#else
			pPlayer->m_iAccount = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgMoney, nullptr, pPlayer->pev);
				WRITE_LONG(pPlayer->m_iAccount);
				WRITE_BYTE(0);
			MESSAGE_END();
#endif

#ifndef REGAMEDLL_FIXES
			MESSAGE_BEGIN(MSG_BROADCAST, gmsgScoreInfo);
#else
			MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
#endif
				WRITE_BYTE(ENTINDEX(pPlayer->edict()));
				WRITE_SHORT(int(pPlayer->pev->frags));
				WRITE_SHORT(pPlayer->m_iDeaths);
				WRITE_SHORT(0);
				WRITE_SHORT(0);
			MESSAGE_END();

			pPlayer->m_pIntroCamera = nullptr;
			pPlayer->m_bTeamChanged = true;

			if (TheBots)
			{
				TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, pPlayer);
			}

			pPlayer->TeamChangeUpdate();

			edict_t *pentSpawnSpot = g_pGameRules->GetPlayerSpawnSpot(pPlayer);
			pPlayer->StartObserver(pentSpawnSpot->v.origin, pentSpawnSpot->v.angles);

#ifndef REGAMEDLL_FIXES
			// TODO: it was already sent in StartObserver
			MESSAGE_BEGIN(MSG_ALL, gmsgSpectator);
				WRITE_BYTE(ENTINDEX(pPlayer->edict()));
				WRITE_BYTE(1);
			MESSAGE_END();
#endif
			// do we have fadetoblack on? (need to fade their screen back in)
			if (fadetoblack.value == FADETOBLACK_STAY)
			{
				UTIL_ScreenFade(pPlayer, Vector(0, 0, 0), 0.001, 0, 0, FFADE_IN);
			}

			return TRUE;
		}
		else
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Be_Spectator");
			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");

			return FALSE;
		}

		break;
	}
	default:
		return FALSE;
	}

	// If the code gets this far, the team is not TEAM_UNASSIGNED
	// Player is switching to a new team (It is possible to switch to the
	// same team just to choose a new appearance)
	if (CSGameRules()->TeamFull(team))
	{
		// The specified team is full
		// attempt to kick a bot to make room for this player
		bool madeRoom = false;
		if (cv_bot_auto_vacate.value > 0 && !pPlayer->IsBot())
		{
			if (UTIL_KickBotFromTeam(team))
			{
				CONSOLE_ECHO("These bots has left the game to make room for human players.\n");
				madeRoom = true;
			}
		}

		if (!madeRoom)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Terrorists_Full" : "#CTs_Full");
			return FALSE;
		}
	}

	// players are allowed to change to their own team so they can just change their model
	if (CSGameRules()->TeamStacked(team, pPlayer->m_iTeam))
	{
		// The specified team is full
		ClientPrint(pPlayer->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Too_Many_Terrorists" : "#Too_Many_CTs");
		return FALSE;
	}

	if (team != SPECTATOR && !pPlayer->IsBot()
#ifdef REGAMEDLL_ADD
		&& !(pPlayer->pev->flags & FL_FAKECLIENT) && auto_join_team.value != 1.0f
#endif
	)
	{
		int humanTeam = UNASSIGNED;
		if (!Q_stricmp(humans_join_team.string, "CT"))
		{
			humanTeam = CT;
		}
		else if (!Q_stricmp(humans_join_team.string, "T"))
		{
			humanTeam = TERRORIST;
		}

		if (humanTeam != UNASSIGNED && team != humanTeam)
		{
			// TODO: These localization strings are not defined on the client CS 1.6, only for CZero
#ifdef REGAMEDLL_FIXES
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "Humans can only be CT!" : "Humans can only be terrorists!");
#else
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, (team == TERRORIST) ? "#Humans_Join_Team_CT" : "#Humans_Join_Team_T");
#endif
			return FALSE;
		}
	}

	// If we already died and changed teams once, deny
	if (pPlayer->m_bTeamChanged)
	{
		if (pPlayer->pev->deadflag != DEAD_NO)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Only_1_Team_Change");
			return FALSE;
		}
	}

	if (pPlayer->m_iTeam == SPECTATOR && team != SPECTATOR)
	{
		// If they're switching into spectator, setup spectator properties..
		pPlayer->m_bNotKilled = true;
		pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
		pPlayer->m_iTeamKills = 0;

		CheckStartMoney();

		// all players start with "mp_startmoney" bucks
#ifdef REGAMEDLL_ADD
		pPlayer->AddAccount(startmoney.value, RT_PLAYER_SPEC_JOIN, false);
#else
		pPlayer->m_iAccount = int(startmoney.value);
#endif

		pPlayer->pev->solid = SOLID_NOT;
		pPlayer->pev->movetype = MOVETYPE_NOCLIP;
		pPlayer->pev->effects = (EF_NODRAW | EF_NOINTERP);
		pPlayer->pev->takedamage = DAMAGE_NO;
		pPlayer->pev->deadflag = DEAD_DEAD;
		pPlayer->pev->punchangle = g_vecZero;

		pPlayer->m_bHasNightVision = false;
		pPlayer->m_iHostagesKilled = 0;
		pPlayer->m_fDeadTime = 0;
		pPlayer->has_disconnected = false;

#ifdef REGAMEDLL_ADD
		pPlayer->m_iJoiningState = PICKINGTEAM;
#else
		pPlayer->pev->velocity = g_vecZero;
		pPlayer->m_iJoiningState = GETINTOGAME;
#endif
		pPlayer->SendItemStatus();

#ifndef REGAMEDLL_ADD
		SET_CLIENT_MAXSPEED(ENT(pPlayer->pev), 1);
#endif

		SET_MODEL(ENT(pPlayer->pev), "models/player.mdl");
	}

#ifdef REGAMEDLL_ADD
	if (!CSGameRules()->ShouldSkipShowMenu())
#endif
	{
		if (!CSGameRules()->IsCareer())
		{
			switch (team)
			{
			case CT:
				if (AreRunningCZero())
					ShowVGUIMenu(pPlayer, VGUI_Menu_Class_CT, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6), "#CT_Select");
				else
					ShowVGUIMenu(pPlayer, VGUI_Menu_Class_CT, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5), "#CT_Select");
				break;

			case TERRORIST:
				if (AreRunningCZero())
					ShowVGUIMenu(pPlayer, VGUI_Menu_Class_T, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6), "#Terrorist_Select");
				else
					ShowVGUIMenu(pPlayer, VGUI_Menu_Class_T, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5), "#Terrorist_Select");
				break;
			}
		}

		pPlayer->m_iMenu = Menu_ChooseAppearance;

		// Show the appropriate Choose Appearance menu
		// This must come before pPlayer->Kill() for CheckWinConditions() to function properly
		if (pPlayer->pev->deadflag == DEAD_NO)
		{
			pPlayer->Kill();
		}
	}

	TeamName oldTeam;
	char *szOldTeam, *szNewTeam;

	// Switch their actual team...
	pPlayer->m_bTeamChanged = true;
	oldTeam = pPlayer->m_iTeam;
	pPlayer->m_iTeam = team;

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, pPlayer);
	}

	pPlayer->TeamChangeUpdate();

	szOldTeam = GetTeam(oldTeam);
	szNewTeam = GetTeam(team);

	// Notify others that this player has joined a new team
	UTIL_ClientPrintAll(HUD_PRINTNOTIFY, (team == TERRORIST) ? "#Game_join_terrorist" : "#Game_join_ct",
		(STRING(pPlayer->pev->netname) && STRING(pPlayer->pev->netname)[0] != 0) ? STRING(pPlayer->pev->netname) : "<unconnected>");

	UTIL_LogPrintf("\"%s<%i><%s><%s>\" joined team \"%s\"\n", STRING(pPlayer->pev->netname), GETPLAYERUSERID(pPlayer->edict()), GETPLAYERAUTHID(pPlayer->edict()), szOldTeam, szNewTeam);
	return TRUE;
}

void Radio1(CBasePlayer *pPlayer, int slot)
{
	if (pPlayer->m_flRadioTime >= gpGlobals->time)
		return;

	if (pPlayer->m_iRadioMessages <= 0)
		return;

	pPlayer->m_iRadioMessages--;
	pPlayer->m_flRadioTime = gpGlobals->time + CGameRules::GetRadioTimeout();

	switch (slot)
	{
	case 1:
		pPlayer->Radio("%!MRAD_COVERME", "#Cover_me");
		break;
	case 2:
		pPlayer->Radio("%!MRAD_TAKEPOINT", "#You_take_the_point");
		break;
	case 3:
		pPlayer->Radio("%!MRAD_POSITION", "#Hold_this_position");
		break;
	case 4:
		pPlayer->Radio("%!MRAD_REGROUP", "#Regroup_team");
		break;
	case 5:
		pPlayer->Radio("%!MRAD_FOLLOWME", "#Follow_me");
		break;
	case 6:
		pPlayer->Radio("%!MRAD_HITASSIST", "#Taking_fire");
		break;
	}

	if (TheBots)
	{
		TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_1 + slot), pPlayer);
	}
}

void Radio2(CBasePlayer *pPlayer, int slot)
{
	if (pPlayer->m_flRadioTime >= gpGlobals->time)
		return;

	if (pPlayer->m_iRadioMessages <= 0)
		return;

	pPlayer->m_iRadioMessages--;
	pPlayer->m_flRadioTime = gpGlobals->time + CGameRules::GetRadioTimeout();

	switch (slot)
	{
	case 1:
		pPlayer->Radio("%!MRAD_GO", "#Go_go_go");
		break;
	case 2:
		pPlayer->Radio("%!MRAD_FALLBACK", "#Team_fall_back");
		break;
	case 3:
		pPlayer->Radio("%!MRAD_STICKTOG", "#Stick_together_team");
		break;
	case 4:
		pPlayer->Radio("%!MRAD_GETINPOS", "#Get_in_position_and_wait");
		break;
	case 5:
		pPlayer->Radio("%!MRAD_STORMFRONT", "#Storm_the_front");
		break;
	case 6:
		pPlayer->Radio("%!MRAD_REPORTIN", "#Report_in_team");
		break;
	}

	if (TheBots)
	{
		TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_2 + slot), pPlayer);
	}
}

void Radio3(CBasePlayer *pPlayer, int slot)
{
	if (pPlayer->m_flRadioTime >= gpGlobals->time)
		return;

	if (pPlayer->m_iRadioMessages <= 0)
		return;

	pPlayer->m_iRadioMessages--;
	pPlayer->m_flRadioTime = gpGlobals->time + CGameRules::GetRadioTimeout();

	switch (slot)
	{
	case 1:
		if (RANDOM_LONG(0, 1))
			pPlayer->Radio("%!MRAD_AFFIRM", "#Affirmative");
		else
			pPlayer->Radio("%!MRAD_ROGER", "#Roger_that");

		break;
	case 2:
		pPlayer->Radio("%!MRAD_ENEMYSPOT", "#Enemy_spotted");
		break;
	case 3:
		pPlayer->Radio("%!MRAD_BACKUP", "#Need_backup");
		break;
	case 4:
		pPlayer->Radio("%!MRAD_CLEAR", "#Sector_clear");
		break;
	case 5:
		pPlayer->Radio("%!MRAD_INPOS", "#In_position");
		break;
	case 6:
		pPlayer->Radio("%!MRAD_REPRTINGIN", "#Reporting_in");
		break;
	case 7:
		pPlayer->Radio("%!MRAD_BLOW", "#Get_out_of_there");
		break;
	case 8:
		pPlayer->Radio("%!MRAD_NEGATIVE", "#Negative");
		break;
	case 9:
		pPlayer->Radio("%!MRAD_ENEMYDOWN", "#Enemy_down");
		break;
	}

	if (TheBots)
	{
		TheBots->OnEvent((GameEventType)(EVENT_START_RADIO_3 + slot), pPlayer);
	}
}

LINK_HOOK_CHAIN(bool, BuyGunAmmo, (CBasePlayer *pPlayer, CBasePlayerItem *weapon, bool bBlinkMoney), pPlayer, weapon, bBlinkMoney)

bool EXT_FUNC __API_HOOK(BuyGunAmmo)(CBasePlayer *pPlayer, CBasePlayerItem *weapon, bool bBlinkMoney)
{
	if (!pPlayer->CanPlayerBuy(true))
		return false;

	// Ensure that the weapon uses ammo
	int nAmmo = weapon->PrimaryAmmoIndex();
	if (nAmmo == -1)
		return false;

	// Can only buy if the player does not already have full ammo
	if (pPlayer->m_rgAmmo[nAmmo] >= weapon->iMaxAmmo1())
		return false;

	WeaponInfoStruct *info = GetWeaponInfo(weapon->m_iId);
	if (!info)
	{
		ALERT(at_console, "Tried to buy ammo for an unrecognized gun\n");
		return false;
	}

	// Purchase the ammo if the player has enough money
	if (pPlayer->m_iAccount >= info->clipCost)
	{
#ifdef REGAMEDLL_FIXES
		if (pPlayer->GiveAmmo(info->buyClipSize, weapon->pszAmmo1(), weapon->iMaxAmmo1()) == -1)
			return false;

		EMIT_SOUND(ENT(weapon->pev), CHAN_ITEM, "items/9mmclip1.wav", VOL_NORM, ATTN_NORM);
#else
		if (!pPlayer->GiveNamedItemEx(info->ammoName1)) {
			return false;
		}
#endif

		pPlayer->AddAccount(-info->clipCost, RT_PLAYER_BOUGHT_SOMETHING);
		return true;
	}

	if (bBlinkMoney)
	{
		if (g_bClientPrintEnable)
		{
			// Not enough money.. let the player know
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer);
		}
	}

	return false;
}

bool BuyAmmo(CBasePlayer *pPlayer, int nSlot, bool bBlinkMoney)
{
	if (!pPlayer->CanPlayerBuy(true))
		return false;

	if (nSlot < PRIMARY_WEAPON_SLOT || nSlot > PISTOL_SLOT)
		return false;

	// Buy one ammo clip for all weapons in the given slot
	//
	// nSlot == 1 : Primary weapons
	// nSlot == 2 : Secondary weapons

	CBasePlayerItem *pItem = pPlayer->m_rgpPlayerItems[nSlot];

	if (pPlayer->HasShield())
	{
		if (pPlayer->m_rgpPlayerItems[PISTOL_SLOT])
			pItem = pPlayer->m_rgpPlayerItems[PISTOL_SLOT];
	}

	if (pItem)
	{
		while (BuyGunAmmo(pPlayer, pItem, bBlinkMoney))
		{
			pItem = pItem->m_pNext;

			if (!pItem)
			{
				return true;
			}
		}
	}

	return false;
}

CBaseEntity *EntityFromUserID(int userID)
{
	CBaseEntity *pTempEntity = nullptr;
	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		if (pTempEntity->IsDormant())
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

		if (pTempPlayer->m_iTeam != UNASSIGNED && userID == GETPLAYERUSERID(pTempEntity->edict()))
		{
			return pTempPlayer;
		}
	}

	return nullptr;
}

NOXREF int CountPlayersInServer()
{
	int count = 0;
	CBaseEntity *pTempEntity = nullptr;
	while ((pTempEntity = UTIL_FindEntityByClassname(pTempEntity, "player")))
	{
		if (FNullEnt(pTempEntity->edict()))
			break;

		if (pTempEntity->IsDormant())
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pTempEntity->pev);

		if (pTempPlayer->m_iTeam != UNASSIGNED)
		{
			count++;
		}
	}

	return count;
}

// Handles the special "buy" alias commands we're creating to accommodate the buy
// scripts players use (now that we've rearranged the buy menus and broken the scripts)
// ** Returns TRUE if we've handled the command **
BOOL HandleBuyAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	// Let them buy it if it's got a weapon data string.
	BOOL bRetVal = FALSE;
	const char *pszFailItem = nullptr;

	WeaponIdType weaponID = WEAPON_NONE;
	const char *weaponFailName = BuyAliasToWeaponID(pszCommand, weaponID);

	// Ok, we have weapon info ID.
	if (weaponID != WEAPON_NONE)
	{
		// assasination maps have a specific set of weapons that can be used in them.
		if (CanBuyWeaponByMaptype(pPlayer->m_iTeam, weaponID, CSGameRules()->m_bMapHasVIPSafetyZone == TRUE))
		{
			bRetVal = TRUE;
			BuyWeaponByWeaponID(pPlayer, weaponID);
		}
		else if (weaponFailName)
		{
			bRetVal = TRUE;
			if (g_bClientPrintEnable)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Alias_Not_Avail", weaponFailName);
			}
		}
		else
		{
			bRetVal = TRUE;
			if (g_bClientPrintEnable)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Cannot_Buy_This");
			}
		}
	}
	else
	{
		// primary ammo
		if (FStrEq(pszCommand, "primammo"))
		{
			bRetVal = TRUE;

			// Buy as much primary ammo as possible
			// Blink money only if player doesn't have enough for the
			// first clip
			if (BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, true))
			{
				while (BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, false))
					;

				if (TheTutor)
				{
					TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
				}
			}
		}
		// secondary ammo
		else if (FStrEq(pszCommand, "secammo"))
		{
			bRetVal = TRUE;

			// Buy as much secondary ammo as possible
			// Blink money only if player doesn't have enough for the
			// first clip
			if (BuyAmmo(pPlayer, PISTOL_SLOT, true))
			{
				while (BuyAmmo(pPlayer, PISTOL_SLOT, false))
					;

				if (TheTutor)
				{
					TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
				}
			}
		}
		// equipment
		else if (FStrEq(pszCommand, "vest"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_VEST);
		}
		else if (FStrEq(pszCommand, "vesthelm"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_VESTHELM);
		}
		else if (FStrEq(pszCommand, "flash"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_FLASHGREN);
		}
		else if (FStrEq(pszCommand, "hegren"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_HEGREN);
		}
		else if (FStrEq(pszCommand, "sgren"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_SMOKEGREN);
		}
		else if (FStrEq(pszCommand, "nvgs"))
		{
			bRetVal = TRUE;
			BuyItem(pPlayer, MENU_SLOT_ITEM_NVG);
		}
		else if (FStrEq(pszCommand, "defuser"))
		{
			bRetVal = TRUE;
			if (pPlayer->m_iTeam == CT)
			{
				BuyItem(pPlayer, MENU_SLOT_ITEM_DEFUSEKIT);
			}
			else
			{
				// fail gracefully
				pszFailItem = "#Bomb_Defusal_Kit";
			}
		}
		else if (FStrEq(pszCommand, "shield"))
		{
			bRetVal = TRUE;
			if (pPlayer->m_iTeam == CT)
			{
				BuyItem(pPlayer, MENU_SLOT_ITEM_SHIELD);
			}
			else
			{
				// fail gracefully
				pszFailItem = "#TactShield_Desc";
			}
		}
	}

	if (g_bClientPrintEnable && pszFailItem)
	{
		ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Alias_Not_Avail", pszFailItem);
	}

	pPlayer->BuildRebuyStruct();
	return bRetVal;
}

struct RadioStruct
{
	int slot;
	void (*func)(CBasePlayer *, int);
	const char *alias;

} radioInfo[] = {
	{ 1, Radio1, "coverme" },
	{ 2, Radio1, "takepoint" },
	{ 3, Radio1, "holdpos" },
	{ 4, Radio1, "regroup" },
	{ 5, Radio1, "followme" },
	{ 6, Radio1, "takingfire" },

	{ 1, Radio2, "go" },
	{ 2, Radio2, "fallback" },
	{ 3, Radio2, "sticktog" },
	{ 4, Radio2, "getinpos" },
	{ 5, Radio2, "stormfront" },
	{ 6, Radio2, "report" },

	{ 1, Radio3, "roger" },
	{ 2, Radio3, "enemyspot" },
	{ 3, Radio3, "needbackup" },
	{ 4, Radio3, "sectorclear" },
	{ 5, Radio3, "inposition" },
	{ 6, Radio3, "reportingin" },
	{ 7, Radio3, "getout" },
	{ 8, Radio3, "negative" },
	{ 9, Radio3, "enemydown" },
};

BOOL HandleRadioAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	for (auto& radio : radioInfo)
	{
		if (FStrEq(pszCommand, radio.alias))
		{
			radio.func(pPlayer, radio.slot);
			return TRUE;
		}
	}

	return FALSE;
}

void EXT_FUNC InternalCommand(edict_t *pEntity, const char *pcmd, const char *parg1)
{
	const char *pstr = nullptr;
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pev);

	if (FStrEq(pcmd, "say"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_SAY])
		{
			pPlayer->m_flLastCommandTime[CMD_SAY] = gpGlobals->time + 0.3f;
			Host_Say(pEntity, FALSE);
		}
	}
	else if (FStrEq(pcmd, "say_team"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_SAYTEAM])
		{
			pPlayer->m_flLastCommandTime[CMD_SAYTEAM] = gpGlobals->time + 0.3f;
			Host_Say(pEntity, TRUE);
		}
	}
	else if (FStrEq(pcmd, "fullupdate"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_FULLUPDATE])
		{
			pPlayer->m_flLastCommandTime[CMD_FULLUPDATE] = gpGlobals->time + 0.6f;
			pPlayer->ForceClientDllUpdate();
		}
	}
	else if (FStrEq(pcmd, "vote"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_VOTE])
		{
			pPlayer->m_flLastCommandTime[CMD_VOTE] = gpGlobals->time + 0.3f;

			if (gpGlobals->time < pPlayer->m_flNextVoteTime)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Wait_3_Seconds");
				return;
			}

#ifdef REGAMEDLL_ADD
			static const int flagKick = UTIL_ReadFlags("k");
			if ((flagKick & UTIL_ReadFlags(vote_flags.string)) == 0)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}
#endif

			pPlayer->m_flNextVoteTime = gpGlobals->time + 3;

			if (pPlayer->m_iTeam != UNASSIGNED)
			{
				int iVoteID;
				bool bVoteFail = false;
				int iNumArgs = CMD_ARGC_();
				int iVoteLength = Q_strlen(parg1);
				if (iNumArgs != 2 || iVoteLength <= 0 || iVoteLength > 6)
				{
					bVoteFail = true;
				}

				iVoteID = Q_atoi(parg1);
				if (iVoteID <= 0)
				{
					bVoteFail = true;
				}

				if (bVoteFail)
				{
					ListPlayers(pPlayer);
					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_vote_usage");
					return;
				}

				if (CountTeamPlayers(pPlayer->m_iTeam) < 3)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Cannot_Vote_With_Less_Than_Three");
					return;
				}

				CBaseEntity *pKickEntity = EntityFromUserID(iVoteID);
				if (pKickEntity)
				{
					CBasePlayer *pKickPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pKickEntity->pev);

					if (pKickPlayer->m_iTeam != pPlayer->m_iTeam)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_vote_players_on_your_team");
						return;
					}

					if (pKickPlayer == pPlayer)
					{
						ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_vote_not_yourself");
						return;
					}

					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_vote_cast", UTIL_dtos1(iVoteID));
					pPlayer->m_iCurrentKickVote = iVoteID;
					ProcessKickVote(pPlayer, pKickPlayer);
				}
				else
				{
					ListPlayers(pPlayer);
					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_vote_player_not_found", UTIL_dtos1(iVoteID));
				}
			}
		}
	}
	else if (FStrEq(pcmd, "listmaps"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_LISTMAPS])
		{
			pPlayer->m_flLastCommandTime[CMD_LISTMAPS] = gpGlobals->time + 0.3f;
			CSGameRules()->DisplayMaps(pPlayer, 0);
		}
	}
	else if (FStrEq(pcmd, "votemap"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_VOTEMAP])
		{
			pPlayer->m_flLastCommandTime[CMD_VOTEMAP] = gpGlobals->time + 0.3f;

			if (gpGlobals->time < pPlayer->m_flNextVoteTime)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Wait_3_Seconds");
				return;
			}

#ifdef REGAMEDLL_ADD
			static const int flagMap = UTIL_ReadFlags("m");
			if ((flagMap & UTIL_ReadFlags(vote_flags.string)) == 0)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}
#endif

			pPlayer->m_flNextVoteTime = gpGlobals->time + 3;

			if (pPlayer->m_iTeam != UNASSIGNED)
			{
				if (gpGlobals->time < CGameRules::GetVotemapMinElapsedTime())
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Cannot_Vote_Map");
					return;
				}

				bool bFailed = false;
				int iNumArgs = CMD_ARGC_();
				int iVoteLength = Q_strlen(parg1);
				if (iNumArgs != 2 || iVoteLength > 5)
				{
					bFailed = true;
				}

				int iVoteID = Q_atoi(parg1);
				if (iVoteID < 1 || iVoteID > MAX_VOTE_MAPS)
				{
					bFailed = true;
				}

				if (iVoteID > GetMapCount())
				{
					bFailed = true;
				}

				if (bFailed)
				{
					CSGameRules()->DisplayMaps(pPlayer, 0);
					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_votemap_usage");
					return;
				}

				if (CountTeamPlayers(pPlayer->m_iTeam) < 2)
				{
					ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Cannot_Vote_Need_More_People");
					return;
				}

				if (pPlayer->m_iMapVote)
				{
					if (--CSGameRules()->m_iMapVotes[pPlayer->m_iMapVote] < 0)
					{
						CSGameRules()->m_iMapVotes[pPlayer->m_iMapVote] = 0;
					}
				}

				ClientPrint(pPlayer->pev, HUD_PRINTCONSOLE, "#Game_voted_for_map", UTIL_dtos1(iVoteID));
				pPlayer->m_iMapVote = iVoteID;
				CSGameRules()->ProcessMapVote(pPlayer, iVoteID);
			}
		}
	}
	else if (FStrEq(pcmd, "timeleft"))
	{
		if (gpGlobals->time > pPlayer->m_iTimeCheckAllowed)
		{
			pPlayer->m_iTimeCheckAllowed = int(gpGlobals->time + 1.0f);

			if (!timelimit.value)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTTALK, "#Game_no_timelimit");
				return;
			}

			int timeRemaining = (int)CSGameRules()->GetTimeLeft();
			if (timeRemaining < 0)
				timeRemaining = 0;

			int iMinutes = timeRemaining / 60;
			int iSeconds = timeRemaining % 60;

			char secs[5];
			char *temp = UTIL_dtos2(iSeconds);

			if (iSeconds >= 10)
			{
				secs[0] = temp[0];
				secs[1] = temp[1];
				secs[2] = '\0';
			}
			else
			{
				secs[0] = '0';
				secs[1] = temp[0];
				secs[2] = '\0';
			}

			ClientPrint(pPlayer->pev, HUD_PRINTTALK, "#Game_timelimit", UTIL_dtos1(iMinutes), secs);
		}
	}
	else if (FStrEq(pcmd, "listplayers"))
	{
		if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_LISTPLAYERS])
		{
			pPlayer->m_flLastCommandTime[CMD_LISTPLAYERS] = gpGlobals->time + 0.3f;
			ListPlayers(pPlayer);
		}
	}
	else if (FStrEq(pcmd, "client_buy_open"))
	{
		if (pPlayer->m_iMenu == Menu_OFF)
		{
			pPlayer->m_iMenu = Menu_ClientBuy;
		}

		if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
		{
			if (TheTutor)
			{
				TheTutor->OnEvent(EVENT_TUTOR_BUY_MENU_OPENNED);
			}
		}
		else
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, nullptr, pPlayer->pev);
			MESSAGE_END();
		}
	}
	else if (FStrEq(pcmd, "client_buy_close"))
	{
		if (pPlayer->m_iMenu == Menu_ClientBuy)
		{
			pPlayer->m_iMenu = Menu_OFF;
		}
	}
	else if (FStrEq(pcmd, "menuselect"))
	{
		int slot = Q_atoi(parg1);
		if (pPlayer->m_iJoiningState == JOINED || (pPlayer->m_iMenu != Menu_ChooseAppearance && pPlayer->m_iMenu != Menu_ChooseTeam))
		{
			if (slot == 10)
			{
				pPlayer->m_iMenu = Menu_OFF;
			}
		}

#ifdef REGAMEDLL_ADD
		auto canOpenOldMenu = [pPlayer]()-> bool
		{
			if (!pPlayer->m_bVGUIMenus || pPlayer->CSPlayer()->m_bForceShowMenu) {
				pPlayer->CSPlayer()->m_bForceShowMenu = false;
				return true;
			}

			return false;
		};
#else
		auto canOpenOldMenu = [pPlayer]()-> bool {
			return pPlayer->m_bVGUIMenus == false;
		};
#endif

		switch (pPlayer->m_iMenu)
		{
			case Menu_OFF:
				break;

			case Menu_ChooseTeam:
			{
				if (canOpenOldMenu() && !HandleMenu_ChooseTeam(pPlayer, slot))
				{
					pPlayer->m_iMenu = Menu_ChooseTeam;
					if (pPlayer->m_iJoiningState == JOINED)
						ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
					else
						ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5), "#Team_Select");
				}
				break;
			}
			case Menu_IGChooseTeam:
			{
				if (canOpenOldMenu()) {
					HandleMenu_ChooseTeam(pPlayer, slot);
				}
				break;
			}
			case Menu_ChooseAppearance:
			{
				if (canOpenOldMenu()) {
					HandleMenu_ChooseAppearance(pPlayer, slot);
				}
				break;
			}
			case Menu_Buy:
			{
				if (canOpenOldMenu())
				{
					switch (slot)
					{
						case VGUI_MenuSlot_Buy_Pistol:
						{
							pPlayer->m_iMenu = Menu_BuyPistol;
							if (pPlayer->m_iTeam == CT)
								ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Pistol, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#CT_BuyPistol");
							else
								ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Pistol, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#T_BuyPistol");
							break;
						}
						case VGUI_MenuSlot_Buy_ShotGun:
						{
							pPlayer->m_iMenu = Menu_BuyShotgun;
							if (CSGameRules()->m_bMapHasVIPSafetyZone && pPlayer->m_iTeam == TERRORIST)
								ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_ShotGun, MENU_KEY_0, "#AS_BuyShotgun");
							else
								ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_ShotGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_0), "#BuyShotgun");
							break;
						}
						case VGUI_MenuSlot_Buy_SubMachineGun:
						{
							pPlayer->m_iMenu = Menu_BuySubMachineGun;
							if (CSGameRules()->m_bMapHasVIPSafetyZone)
							{
								if (pPlayer->m_iTeam == CT)
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_0), "#AS_CT_BuySubMachineGun");
								else
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_3 | MENU_KEY_0), "#AS_T_BuySubMachineGun");
							}
							else
							{
								if (pPlayer->m_iTeam == CT)
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_0), "#CT_BuySubMachineGun");
								else
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_SubMachineGun, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_0), "#T_BuySubMachineGun");
							}
							break;
						}
						case VGUI_MenuSlot_Buy_Rifle:
						{
							pPlayer->m_iMenu = Menu_BuyRifle;
							if (CSGameRules()->m_bMapHasVIPSafetyZone)
							{
								if (pPlayer->m_iTeam == CT)
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_0), "#AS_CT_BuyRifle");
								else
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#AS_T_BuyRifle");
							}
							else
							{
								if (pPlayer->m_iTeam == CT)
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#CT_BuyRifle");
								else
									ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Rifle, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#T_BuyRifle");
							}
							break;
						}
						case VGUI_MenuSlot_Buy_MachineGun:
						{
							pPlayer->m_iMenu = Menu_BuyMachineGun;
							if (CSGameRules()->m_bMapHasVIPSafetyZone && pPlayer->m_iTeam == TERRORIST)
								ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_MachineGun, MENU_KEY_0, "#AS_T_BuyMachineGun");
							else
								ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_MachineGun, (MENU_KEY_1 | MENU_KEY_0), "#BuyMachineGun");
							break;
						}
						case VGUI_MenuSlot_Buy_PrimAmmo:
						{
							if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
							{
								if (BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, true))
								{
									while (BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, false))
										;

									if (TheTutor)
									{
										TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
									}
								}

								pPlayer->BuildRebuyStruct();
							}
							break;
						}
						case VGUI_MenuSlot_Buy_SecAmmo:
						{
							if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
							{
								if (BuyAmmo(pPlayer, PISTOL_SLOT, true))
								{
									while (BuyAmmo(pPlayer, PISTOL_SLOT, false))
										;

									if (TheTutor)
									{
										TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
									}
								}

								pPlayer->BuildRebuyStruct();
							}
							break;
						}
						case VGUI_MenuSlot_Buy_Item:
						{
							if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
							{
								pPlayer->m_iMenu = Menu_BuyItem;
								if (CSGameRules()->m_bMapHasBombTarget)
								{
									if (pPlayer->m_iTeam == CT)
										ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_0), "#DCT_BuyItem");
									else
										ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#DT_BuyItem");
								}
								else
								{
									if (pPlayer->m_iTeam == CT)
										ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_8 | MENU_KEY_0), "#CT_BuyItem");
									else
										ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#T_BuyItem");
								}
							}
							break;
						}
					}
				}
				break;
			}
			case Menu_BuyPistol:
			{
				if (canOpenOldMenu())
				{
					BuyPistol(pPlayer, slot);
#ifdef REGAMEDLL_FIXES
					pPlayer->BuildRebuyStruct();
#endif
				}
				break;
			}
			case Menu_BuyShotgun:
			{
				if (canOpenOldMenu())
				{
					BuyShotgun(pPlayer, slot);
#ifdef REGAMEDLL_FIXES
					pPlayer->BuildRebuyStruct();
#endif
				}
				break;
			}
			case Menu_BuySubMachineGun:
			{
				if (canOpenOldMenu())
				{
					BuySubMachineGun(pPlayer, slot);
#ifdef REGAMEDLL_FIXES
					pPlayer->BuildRebuyStruct();
#endif
				}
				break;
			}
			case Menu_BuyRifle:
			{
				if (canOpenOldMenu())
				{
					BuyRifle(pPlayer, slot);
#ifdef REGAMEDLL_FIXES
					pPlayer->BuildRebuyStruct();
#endif
				}
				break;
			}
			case Menu_BuyMachineGun:
			{
				if (canOpenOldMenu())
				{
					BuyMachineGun(pPlayer, slot);
#ifdef REGAMEDLL_FIXES
					pPlayer->BuildRebuyStruct();
#endif
				}
				break;
			}
			case Menu_BuyItem:
			{
				if (canOpenOldMenu())
				{
					BuyItem(pPlayer, slot);
#ifdef REGAMEDLL_FIXES
					pPlayer->BuildRebuyStruct();
#endif
				}
				break;
			}
			case Menu_Radio1:
			{
				Radio1(pPlayer, slot);
				break;
			}
			case Menu_Radio2:
			{
				Radio2(pPlayer, slot);
				break;
			}
			case Menu_Radio3:
			{
				Radio3(pPlayer, slot);
				break;
			}
			default:
				ALERT(at_console, "ClientCommand(): Invalid menu selected\n");
				break;
		}
	}
	else if (FStrEq(pcmd, "chooseteam"))
	{
		if (pPlayer->m_iMenu == Menu_ChooseAppearance)
			return;

		if (pPlayer->m_bTeamChanged)
		{
			if (pPlayer->pev->deadflag != DEAD_NO)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Only_1_Team_Change");
				return;
			}
		}

		if (!CSGameRules()->IsCareer())
		{
			pPlayer->m_iMenu = Menu_ChooseTeam;
			if (CSGameRules()->m_bMapHasVIPSafetyZone && pPlayer->m_iJoiningState == JOINED && pPlayer->m_iTeam == CT)
			{
				if (CSGameRules()->IsFreezePeriod() || pPlayer->pev->deadflag != DEAD_NO)
					ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#IG_VIP_Team_Select_Spect");
				else
					ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_5 | MENU_KEY_0), "#IG_VIP_Team_Select");
			}
			else
			{
				if (CSGameRules()->IsFreezePeriod() || pPlayer->pev->deadflag != DEAD_NO)
					ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#IG_Team_Select_Spect");
				else
					ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
			}
		}
	}
	else if (FStrEq(pcmd, "showbriefing"))
	{
		if (pPlayer->m_iMenu == Menu_OFF)
		{
			if (g_szMapBriefingText[0] != '\0')
			{
				if (pPlayer->m_iTeam != UNASSIGNED && !(pPlayer->m_afPhysicsFlags & PFLAG_OBSERVER))
				{
					pPlayer->MenuPrint(g_szMapBriefingText);
					pPlayer->m_bMissionBriefing = true;
				}
			}
		}
	}
	else if (FStrEq(pcmd, "ignoremsg"))
	{
		if (pPlayer->m_iIgnoreGlobalChat == IGNOREMSG_NONE)
		{
			pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_ENEMY;
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Ignore_Broadcast_Messages");
		}
		else if (pPlayer->m_iIgnoreGlobalChat == IGNOREMSG_ENEMY)
		{
			pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_TEAM;
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Ignore_Broadcast_Team_Messages");
		}
		else if (pPlayer->m_iIgnoreGlobalChat == IGNOREMSG_TEAM)
		{
			pPlayer->m_iIgnoreGlobalChat = IGNOREMSG_NONE;
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Accept_All_Messages");
		}
	}
	else if (FStrEq(pcmd, "ignorerad"))
	{
		pPlayer->m_bIgnoreRadio = !pPlayer->m_bIgnoreRadio;
		ClientPrint(pPlayer->pev, HUD_PRINTCENTER, pPlayer->m_bIgnoreRadio ? "#Ignore_Radio" : "#Accept_Radio");
	}
	else if (FStrEq(pcmd, "become_vip"))
	{
		if (pPlayer->m_iJoiningState != JOINED || pPlayer->m_iTeam != CT
#ifdef REGAMEDLL_FIXES
			|| !CSGameRules()->m_bMapHasVIPSafetyZone
#endif
			)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Command_Not_Available");
			return;
		}

		CSGameRules()->AddToVIPQueue(pPlayer);
	}
	else if (FStrEq(pcmd, "spectate") && (pPlayer->pev->flags & FL_PROXY)) // always allow proxies to become a spectator
	{
		// clients wants to become a spectator
		HandleMenu_ChooseTeam(pPlayer, MENU_SLOT_TEAM_SPECT);
	}
	else if (FStrEq(pcmd, "specmode"))
	{
		// new spectator mode
		int mode = Q_atoi(parg1);
		if (pPlayer->GetObserverMode() != OBS_NONE && pPlayer->CanSwitchObserverModes())
			pPlayer->Observer_SetMode(mode);
		else
			pPlayer->m_iObserverLastMode = mode;

		if (mode == OBS_CHASE_FREE)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgADStop, nullptr, pPlayer->pev);
			MESSAGE_END();
		}
	}
	else if (FStrEq(pcmd, "spec_set_ad"))
	{
		float val = Q_atof(parg1);
		pPlayer->SetObserverAutoDirector(val > 0.0f);
	}
	else if (FStrEq(pcmd, "follownext"))
	{
		// follow next player
		int arg = Q_atoi(parg1);
		if (pPlayer->GetObserverMode() != OBS_NONE && pPlayer->CanSwitchObserverModes())
		{
			pPlayer->Observer_FindNextPlayer(arg != 0);
		}
	}
	else if (FStrEq(pcmd, "follow"))
	{
		if (pPlayer->GetObserverMode() != OBS_NONE && pPlayer->CanSwitchObserverModes())
		{
			pPlayer->Observer_FindNextPlayer(false, parg1);
		}
	}
#ifdef REGAMEDLL_FIXES
	else if (FStrEq(pcmd, "cl_setautobuy"))
	{
		if (pPlayer->pev->deadflag != DEAD_NO && pPlayer->m_autoBuyString[0] != '\0')
			return;

		pPlayer->ClearAutoBuyData();

		for (int i = 1; i < CMD_ARGC_(); i++)
		{
			pPlayer->AddAutoBuyData(CMD_ARGV_(i));
		}

		if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
		{
			bool oldval = g_bClientPrintEnable;
			g_bClientPrintEnable = false;
			pPlayer->AutoBuy();
			g_bClientPrintEnable = oldval;
		}
	}
	else if (FStrEq(pcmd, "cl_setrebuy"))
	{
		if (pPlayer->pev->deadflag != DEAD_NO && pPlayer->m_rebuyString)
			return;

		if (CMD_ARGC_() == 2)
		{
			pPlayer->InitRebuyData(parg1);

			if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
			{
				bool oldval = g_bClientPrintEnable;
				g_bClientPrintEnable = false;
				pPlayer->Rebuy();
				g_bClientPrintEnable = oldval;
			}
		}
	}
#endif
	else
	{
		if (g_pGameRules->ClientCommand_DeadOrAlive(GetClassPtr<CCSPlayer>((CBasePlayer *)pev), pcmd))
			return;

		if (TheBots)
		{
			if (TheBots->ClientCommand(GetClassPtr<CCSPlayer>((CBasePlayer *)pev), pcmd))
				return;
		}

		if (FStrEq(pcmd, "mp_debug"))
		{
			UTIL_SetDprintfFlags(parg1);
		}
		else if (FStrEq(pcmd, "jointeam"))
		{
			if (pPlayer->m_iMenu == Menu_ChooseAppearance)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}

			int slot = Q_atoi(parg1);
			if (HandleMenu_ChooseTeam(pPlayer, slot))
			{
				if (slot == MENU_SLOT_TEAM_VIP || slot == MENU_SLOT_TEAM_SPECT || pPlayer->m_bIsVIP)
				{
#ifdef REGAMEDLL_FIXES
					pPlayer->ResetMenu();
#else
					pPlayer->m_iMenu = Menu_OFF;
#endif
				}
				else
					pPlayer->m_iMenu = Menu_ChooseAppearance;
			}
			else
			{
				pPlayer->m_iMenu = Menu_ChooseTeam;
				if (pPlayer->m_iJoiningState == JOINED)
					ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5 | MENU_KEY_0), "#IG_Team_Select");
				else
					ShowVGUIMenu(pPlayer, VGUI_Menu_Team, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_5), "#Team_Select");
			}
		}
		else if (FStrEq(pcmd, "joinclass"))
		{
			int slot = Q_atoi(parg1);
			if (pPlayer->m_iMenu != Menu_ChooseAppearance)
			{
				ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Command_Not_Available");
				return;
			}

			HandleMenu_ChooseAppearance(pPlayer, slot);
		}
		else if (pPlayer->pev->deadflag == DEAD_NO)
		{
			if (FStrEq(pcmd, "nightvision"))
			{
				if (gpGlobals->time >= pPlayer->m_flLastCommandTime[CMD_NIGHTVISION])
				{
					pPlayer->m_flLastCommandTime[CMD_NIGHTVISION] = gpGlobals->time + 0.3f;

					if (!pPlayer->m_bHasNightVision)
						return;

					if (pPlayer->m_bNightVisionOn)
					{
						EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/nvg_off.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

						MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pPlayer->pev);
							WRITE_BYTE(0); // disable nightvision
						MESSAGE_END();

						pPlayer->m_bNightVisionOn = false;

						for (int i = 1; i <= gpGlobals->maxClients; i++)
						{
							CBasePlayer *pObserver = UTIL_PlayerByIndex(i);

							if (!UTIL_IsValidPlayer(pObserver))
								continue;

							if (pObserver->IsObservingPlayer(pPlayer))
							{
								EMIT_SOUND(ENT(pObserver->pev), CHAN_ITEM, "items/nvg_off.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

								MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pObserver->pev);
									WRITE_BYTE(0); // disable nightvision
								MESSAGE_END();

								pObserver->m_bNightVisionOn = false;
							}
						}
					}
					else
					{
						EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/nvg_on.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

						MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pPlayer->pev);
							WRITE_BYTE(1); // enable nightvision
						MESSAGE_END();

						pPlayer->m_bNightVisionOn = true;

						for (int i = 1; i <= gpGlobals->maxClients; i++)
						{
							CBasePlayer *pObserver = UTIL_PlayerByIndex(i);

							if (!UTIL_IsValidPlayer(pObserver))
								continue;

							if (pObserver->IsObservingPlayer(pPlayer))
							{
								EMIT_SOUND(ENT(pObserver->pev), CHAN_ITEM, "items/nvg_on.wav", RANDOM_FLOAT(0.92, 1), ATTN_NORM);

								MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pObserver->pev);
									WRITE_BYTE(1);  // enable nightvision
								MESSAGE_END();

								pObserver->m_bNightVisionOn = true;
							}
						}
					}
				}
			}
			else if (FStrEq(pcmd, "radio1"))
			{
				ShowMenu(pPlayer, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), -1, FALSE, "#RadioA");
				pPlayer->m_iMenu = Menu_Radio1;
			}
			else if (FStrEq(pcmd, "radio2"))
			{
				ShowMenu(pPlayer, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), -1, FALSE, "#RadioB");
				pPlayer->m_iMenu = Menu_Radio2;
				return;
			}
			else if (FStrEq(pcmd, "radio3"))
			{
				ShowMenu(pPlayer, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_9 | MENU_KEY_0), -1, FALSE, "#RadioC");
				pPlayer->m_iMenu = Menu_Radio3;
			}
			else if (FStrEq(pcmd, "drop"))
			{
				// player is dropping an item.
				if (pPlayer->HasShield())
				{
					if (pPlayer->m_pActiveItem && pPlayer->m_pActiveItem->m_iId == WEAPON_C4)
					{
						pPlayer->DropPlayerItem("weapon_c4");
					}
					else
						pPlayer->DropShield();
				}
				else
					pPlayer->DropPlayerItem(parg1);
			}
			else if (FStrEq(pcmd, "fov"))
			{
#if 0
				if (CVAR_GET_FLOAT("sv_cheats") != 0.0f && CMD_ARGC() > 1)
					GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->m_iFOV = Q_atoi(CMD_ARGV(1));
				else
					CLIENT_PRINTF(pEntity, print_console, UTIL_VarArgs("\"fov\" is \"%d\"\n", int(GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->m_iFOV)));
#endif
			}
			else if (FStrEq(pcmd, "use"))
			{
				GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->SelectItem(parg1);
			}
			else if (((pstr = Q_strstr(pcmd, "weapon_"))) && (pstr == pcmd))
			{
				GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->SelectItem(pcmd);
			}
			else if (FStrEq(pcmd, "lastinv"))
			{
				GetClassPtr<CCSPlayer>((CBasePlayer *)pev)->SelectLastItem();
			}
			else if (FStrEq(pcmd, "buyammo1"))
			{
				if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
				{
					BuyAmmo(pPlayer, PRIMARY_WEAPON_SLOT, true);
					pPlayer->BuildRebuyStruct();

					if (TheTutor)
					{
						TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
					}
				}
			}
			else if (FStrEq(pcmd, "buyammo2"))
			{
				if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
				{
					BuyAmmo(pPlayer, PISTOL_SLOT, true);
					pPlayer->BuildRebuyStruct();

					if (TheTutor)
					{
						TheTutor->OnEvent(EVENT_PLAYER_BOUGHT_SOMETHING, pPlayer);
					}
				}
			}
			else if (FStrEq(pcmd, "buyequip"))
			{
				if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
				{
					if (CSGameRules()->m_bMapHasBombTarget)
					{
						if (pPlayer->m_iTeam == CT)
							ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_0), "#DCT_BuyItem");
						else
							ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#DT_BuyItem");
					}
					else
					{
						if (pPlayer->m_iTeam == CT)
							ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_8 | MENU_KEY_0), "#CT_BuyItem");
						else
							ShowVGUIMenu(pPlayer, VGUI_Menu_Buy_Item, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_0), "#T_BuyItem");
					}

					pPlayer->m_iMenu = Menu_BuyItem;
				}
			}
			else if (FStrEq(pcmd, "buy"))
			{
				if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
				{
					ShowVGUIMenu(pPlayer, VGUI_Menu_Buy, (MENU_KEY_1 | MENU_KEY_2 | MENU_KEY_3 | MENU_KEY_4 | MENU_KEY_5 | MENU_KEY_6 | MENU_KEY_7 | MENU_KEY_8 | MENU_KEY_0), "#Buy");
					pPlayer->m_iMenu = Menu_Buy;

					if (TheBots)
					{
						TheBots->OnEvent(EVENT_TUTOR_BUY_MENU_OPENNED);
					}
				}
			}
#ifndef REGAMEDLL_FIXES
			// Moved to above
			else if (FStrEq(pcmd, "cl_setautobuy"))
			{
				pPlayer->ClearAutoBuyData();

				for (int i = 1; i < CMD_ARGC_(); i++)
				{
					pPlayer->AddAutoBuyData(CMD_ARGV_(i));
				}

				bool oldval = g_bClientPrintEnable;
				g_bClientPrintEnable = false;
				pPlayer->AutoBuy();
				g_bClientPrintEnable = oldval;
			}
			else if (FStrEq(pcmd, "cl_setrebuy"))
			{
				if (CMD_ARGC_() == 2)
				{
					pPlayer->InitRebuyData(parg1);

					bool oldval = g_bClientPrintEnable;
					g_bClientPrintEnable = false;
					pPlayer->Rebuy();
					g_bClientPrintEnable = oldval;
				}
			}
#endif
			else if (FStrEq(pcmd, "cl_autobuy"))
			{
				if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
				{
					bool oldval = g_bClientPrintEnable;
					g_bClientPrintEnable = false;
					pPlayer->AutoBuy();
					g_bClientPrintEnable = oldval;
				}
			}
			else if (FStrEq(pcmd, "cl_rebuy"))
			{
				if (pPlayer->m_signals.GetState() & SIGNAL_BUY)
				{
					bool oldval = g_bClientPrintEnable;
					g_bClientPrintEnable = false;
					pPlayer->Rebuy();
					g_bClientPrintEnable = oldval;
				}
			}
			else if (FStrEq(pcmd, "smartradio"))
			{
				pPlayer->SmartRadio();
			}
#ifdef REGAMEDLL_ADD
			else if (FStrEq(pcmd, "give"))
			{
				if (CVAR_GET_FLOAT("sv_cheats") != 0.0f && CMD_ARGC() > 1 && FStrnEq(parg1, "weapon_", sizeof("weapon_") - 1))
				{
					const auto pInfo = GetWeaponInfo(parg1);
					if (pInfo)
					{
						if (pInfo->id != WEAPON_GLOCK && pInfo->id != WEAPON_C4 /* && pInfo->id != WEAPON_KNIFE */)
						{
							pPlayer->GiveNamedItemEx(pInfo->entityName);
							pPlayer->GiveAmmo(pInfo->maxRounds, pInfo->ammoName2);
						}
					}
				}
			}
#endif
			else
			{
				if (HandleBuyAliasCommands(pPlayer, pcmd))
					return;

				if (HandleRadioAliasCommands(pPlayer, pcmd))
					return;

				if (!g_pGameRules->ClientCommand(GetClassPtr<CCSPlayer>((CBasePlayer *)pev), pcmd))
				{
					// tell the user they entered an unknown command
					char command[128];

					// check the length of the command (prevents crash)
					// max total length is 192 ...and we're adding a string below ("Unknown command: %s\n")
					Q_strncpy(command, pcmd, sizeof(command) - 1);
					command[sizeof(command) - 1] = '\0';
#ifdef REGAMEDLL_FIXES
					// Add extra '\n' to make command string safe
					// This extra '\n' is removed by the client, so it is ok
					command[sizeof(command) - 2] = '\0';
					command[Q_strlen(command)] = '\n';
#endif

					// tell the user they entered an unknown command
					ClientPrint(&pEntity->v, HUD_PRINTCONSOLE, "#Game_unknown_command", command);
				}
			}
		}
	}
}

// Use CMD_ARGV, CMD_ARGV, and CMD_ARGC to get pointers the character string command.
void EXT_FUNC ClientCommand_(edict_t *pEntity)
{
	// Is the client spawned yet?
	if (!pEntity->pvPrivateData)
		return;

	static char command[128] = "";
	Q_strncpy(command, CMD_ARGV_(0), sizeof command - 1);
	command[sizeof command - 1] = '\0';

	g_ReGameHookchains.m_InternalCommand.callChain(InternalCommand, pEntity, command, CMD_ARGV_(1));
}

// called after the player changes userinfo - gives dll a chance to modify it before it gets sent into the rest of the engine.
void EXT_FUNC ClientUserInfoChanged(edict_t *pEntity, char *infobuffer)
{
	// Is the client spawned yet?
	if (!pEntity->pvPrivateData)
		return;

	CBasePlayer *pPlayer = CBasePlayer::Instance(pEntity);
	char *szBufferName = GET_KEY_VALUE(infobuffer, "name");

	// msg everyone if someone changes their name, and it isn't the first time (changing no name to current name)
	if (pEntity->v.netname && STRING(pEntity->v.netname)[0] != '\0' && !FStrEq(STRING(pEntity->v.netname), szBufferName))
	{
		char szName[32];
		Q_snprintf(szName, sizeof(szName), "%s", szBufferName);

		// First parse the name and remove any %'s
		for (char *pPct = szName; pPct && *pPct != '\0'; pPct++)
		{
			// Replace it with a space
			if (*pPct == '%' || *pPct == '&')
				*pPct = ' ';
		}

		if (szName[0] == '#')
			szName[0] = '*';

		// Can set it a new name?
		if (!pPlayer->SetClientUserInfoName(infobuffer, szName))
		{
			// so to back old name into buffer
			SET_CLIENT_KEY_VALUE(pPlayer->entindex(), infobuffer, "name", STRING(pPlayer->pev->netname));
		}
	}

	// was already checking on pvPrivateData
#ifndef REGAMEDLL_FIXES
	g_pGameRules->ClientUserInfoChanged(GetClassPtr<CCSPlayer>((CBasePlayer *)&pEntity->v), infobuffer);
#else
	g_pGameRules->ClientUserInfoChanged(pPlayer, infobuffer);
#endif
}

void EXT_FUNC ServerDeactivate()
{
	// It's possible that the engine will call this function more times than is necessary
	// Therefore, only run it one time for each call to ServerActivate
	if (!g_bServerActive)
		return;

	g_bServerActive = false;

	// Peform any shutdown operations here...
	g_pGameRules->ServerDeactivate();
	CLocalNav::Reset();

	if (TheBots)
	{
		TheBots->ServerDeactivate();
	}

	if (g_pHostages)
	{
		g_pHostages->ServerDeactivate();
	}

	WeaponInfoReset();
}

void EXT_FUNC ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	int i;
	CBaseEntity *pClass;

	// Every call to ServerActivate should be matched by a call to ServerDeactivate
	g_bServerActive = true;
	EmptyEntityHashTable();

	// Clients have not been initialized yet
	for (i = 0; i < edictCount; i++)
	{
		edict_t *pEdict = &pEdictList[i];

		if (pEdict->free)
			continue;

		// Clients aren't necessarily initialized until ClientPutInServer()
		if (i < clientMax || !pEdict->pvPrivateData)
			continue;

		pClass = CBaseEntity::Instance(pEdict);

		// Activate this entity if it's got a class & isn't dormant
		if (pClass && !pClass->IsDormant())
		{
			AddEntityHashValue(&pEdict->v, STRING(pEdict->v.classname), CLASSNAME);
			pClass->Activate();
		}
		else
		{
			ALERT(at_console, "Can't instance %s\n", STRING(pEdict->v.classname));
		}
	}

	// Link user messages here to make sure first client can get them...
	LinkUserMessages();
	WriteSigonMessages();

	if (g_pGameRules)
	{
		g_pGameRules->CheckMapConditions();
	}

	if (TheBots)
	{
		TheBots->ServerActivate();
	}

	if (g_pHostages)
	{
		g_pHostages->ServerActivate();
	}

#ifdef REGAMEDLL_ADD
	CSGameRules()->ServerActivate();

	if (location_area_info.value)
		LoadNavigationMap();
#endif
}

void EXT_FUNC PlayerPreThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->PreThink();
	}
}

void EXT_FUNC PlayerPostThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->PostThink();
	}
}

void EXT_FUNC ParmsNewLevel()
{
	;
}

void EXT_FUNC ParmsChangeLevel()
{
	// retrieve the pointer to the save data
	SAVERESTOREDATA *pSaveData = (SAVERESTOREDATA *)gpGlobals->pSaveData;

	if (pSaveData)
	{
		pSaveData->connectionCount = BuildChangeList(pSaveData->levelList, MAX_LEVEL_CONNECTIONS);
	}
}

void EXT_FUNC StartFrame()
{
	if (g_pGameRules)
	{
		g_pGameRules->Think();
		if (g_pGameRules->IsGameOver())
			return;
	}

	CLocalNav::Think();

	gpGlobals->teamplay = 1.0f;
	g_iSkillLevel = g_pskill ? (int)g_pskill->value : 0;

	if (TheBots) {
		TheBots->StartFrame();
	}

	if (TheTutor) {
		TheTutor->StartFrame(gpGlobals->time);
	}

	EndFrame();
}

void EndFrame()
{
	CTriggerSetOriginManager::getInstance()->Update();
}

void ClientPrecache()
{
	int i;

	PRECACHE_SOUND("weapons/dryfire_pistol.wav");
	PRECACHE_SOUND("weapons/dryfire_rifle.wav");
	PRECACHE_SOUND("player/pl_shot1.wav");
	PRECACHE_SOUND("player/pl_die1.wav");
	PRECACHE_SOUND("player/headshot1.wav");
	PRECACHE_SOUND("player/headshot2.wav");
	PRECACHE_SOUND("player/headshot3.wav");
	PRECACHE_SOUND("player/bhit_flesh-1.wav");
	PRECACHE_SOUND("player/bhit_flesh-2.wav");
	PRECACHE_SOUND("player/bhit_flesh-3.wav");
	PRECACHE_SOUND("player/bhit_kevlar-1.wav");
	PRECACHE_SOUND("player/bhit_helmet-1.wav");
	PRECACHE_SOUND("player/die1.wav");
	PRECACHE_SOUND("player/die2.wav");
	PRECACHE_SOUND("player/die3.wav");
	PRECACHE_SOUND("player/death6.wav");
	PRECACHE_SOUND("radio/locknload.wav");
	PRECACHE_SOUND("radio/letsgo.wav");
	PRECACHE_SOUND("radio/moveout.wav");
	PRECACHE_SOUND("radio/com_go.wav");
	PRECACHE_SOUND("radio/rescued.wav");
	PRECACHE_SOUND("radio/rounddraw.wav");
	PRECACHE_SOUND("items/kevlar.wav");
	PRECACHE_SOUND("items/ammopickup2.wav");
	PRECACHE_SOUND("items/nvg_on.wav");
	PRECACHE_SOUND("items/nvg_off.wav");
	PRECACHE_SOUND("items/equip_nvg.wav");
	PRECACHE_SOUND("weapons/c4_beep1.wav");
	PRECACHE_SOUND("weapons/c4_beep2.wav");
	PRECACHE_SOUND("weapons/c4_beep3.wav");
	PRECACHE_SOUND("weapons/c4_beep4.wav");
	PRECACHE_SOUND("weapons/c4_beep5.wav");
	PRECACHE_SOUND("weapons/c4_explode1.wav");
	PRECACHE_SOUND("weapons/c4_plant.wav");
	PRECACHE_SOUND("weapons/c4_disarm.wav");
	PRECACHE_SOUND("weapons/c4_disarmed.wav");
	PRECACHE_SOUND("weapons/explode3.wav");
	PRECACHE_SOUND("weapons/explode4.wav");
	PRECACHE_SOUND("weapons/explode5.wav");
	PRECACHE_SOUND("player/sprayer.wav");
	PRECACHE_SOUND("player/pl_fallpain2.wav");
	PRECACHE_SOUND("player/pl_fallpain3.wav");
	PRECACHE_SOUND("player/pl_snow1.wav");
	PRECACHE_SOUND("player/pl_snow2.wav");
	PRECACHE_SOUND("player/pl_snow3.wav");
	PRECACHE_SOUND("player/pl_snow4.wav");
	PRECACHE_SOUND("player/pl_snow5.wav");
	PRECACHE_SOUND("player/pl_snow6.wav");
	PRECACHE_SOUND("player/pl_step1.wav");
	PRECACHE_SOUND("player/pl_step2.wav");
	PRECACHE_SOUND("player/pl_step3.wav");
	PRECACHE_SOUND("player/pl_step4.wav");
	PRECACHE_SOUND("common/npc_step1.wav");
	PRECACHE_SOUND("common/npc_step2.wav");
	PRECACHE_SOUND("common/npc_step3.wav");
	PRECACHE_SOUND("common/npc_step4.wav");
	PRECACHE_SOUND("player/pl_metal1.wav");
	PRECACHE_SOUND("player/pl_metal2.wav");
	PRECACHE_SOUND("player/pl_metal3.wav");
	PRECACHE_SOUND("player/pl_metal4.wav");
	PRECACHE_SOUND("player/pl_dirt1.wav");
	PRECACHE_SOUND("player/pl_dirt2.wav");
	PRECACHE_SOUND("player/pl_dirt3.wav");
	PRECACHE_SOUND("player/pl_dirt4.wav");
	PRECACHE_SOUND("player/pl_duct1.wav");
	PRECACHE_SOUND("player/pl_duct2.wav");
	PRECACHE_SOUND("player/pl_duct3.wav");
	PRECACHE_SOUND("player/pl_duct4.wav");
	PRECACHE_SOUND("player/pl_grate1.wav");
	PRECACHE_SOUND("player/pl_grate2.wav");
	PRECACHE_SOUND("player/pl_grate3.wav");
	PRECACHE_SOUND("player/pl_grate4.wav");
	PRECACHE_SOUND("player/pl_slosh1.wav");
	PRECACHE_SOUND("player/pl_slosh2.wav");
	PRECACHE_SOUND("player/pl_slosh3.wav");
	PRECACHE_SOUND("player/pl_slosh4.wav");
	PRECACHE_SOUND("player/pl_tile1.wav");
	PRECACHE_SOUND("player/pl_tile2.wav");
	PRECACHE_SOUND("player/pl_tile3.wav");
	PRECACHE_SOUND("player/pl_tile4.wav");
	PRECACHE_SOUND("player/pl_tile5.wav");
	PRECACHE_SOUND("player/pl_swim1.wav");
	PRECACHE_SOUND("player/pl_swim2.wav");
	PRECACHE_SOUND("player/pl_swim3.wav");
	PRECACHE_SOUND("player/pl_swim4.wav");
	PRECACHE_SOUND("player/pl_ladder1.wav");
	PRECACHE_SOUND("player/pl_ladder2.wav");
	PRECACHE_SOUND("player/pl_ladder3.wav");
	PRECACHE_SOUND("player/pl_ladder4.wav");
	PRECACHE_SOUND("player/pl_wade1.wav");
	PRECACHE_SOUND("player/pl_wade2.wav");
	PRECACHE_SOUND("player/pl_wade3.wav");
	PRECACHE_SOUND("player/pl_wade4.wav");
	PRECACHE_SOUND("debris/wood1.wav");
	PRECACHE_SOUND("debris/wood2.wav");
	PRECACHE_SOUND("debris/wood3.wav");
	PRECACHE_SOUND("plats/train_use1.wav");
	PRECACHE_SOUND("plats/vehicle_ignition.wav");
	PRECACHE_SOUND("buttons/spark5.wav");
	PRECACHE_SOUND("buttons/spark6.wav");
	PRECACHE_SOUND("debris/glass1.wav");
	PRECACHE_SOUND("debris/glass2.wav");
	PRECACHE_SOUND("debris/glass3.wav");
	PRECACHE_SOUND(SOUND_FLASHLIGHT_ON);
	PRECACHE_SOUND(SOUND_FLASHLIGHT_OFF);
	PRECACHE_SOUND("common/bodysplat.wav");
	PRECACHE_SOUND("player/pl_pain2.wav");
	PRECACHE_SOUND("player/pl_pain4.wav");
	PRECACHE_SOUND("player/pl_pain5.wav");
	PRECACHE_SOUND("player/pl_pain6.wav");
	PRECACHE_SOUND("player/pl_pain7.wav");

	int numPlayerModels;
	if (AreRunningCZero())
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles);
	else
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles) - 2;

	for (i = 0; i < numPlayerModels; i++)
		PRECACHE_MODEL(sPlayerModelFiles[i]);

	if (AreRunningCZero())
	{
		for (i = FirstCustomSkin; i <= LastCustomSkin; i++)
		{
			const char *fname = TheBotProfiles->GetCustomSkinFname(i);

			if (!fname)
				break;

			PRECACHE_MODEL(fname);
		}
	}

	PRECACHE_MODEL("models/p_ak47.mdl");
	PRECACHE_MODEL("models/p_aug.mdl");
	PRECACHE_MODEL("models/p_awp.mdl");
	PRECACHE_MODEL("models/p_c4.mdl");
	PRECACHE_MODEL("models/w_c4.mdl");
	PRECACHE_MODEL("models/p_deagle.mdl");
	PRECACHE_MODEL("models/shield/p_shield_deagle.mdl");
	PRECACHE_MODEL("models/p_flashbang.mdl");
	PRECACHE_MODEL("models/shield/p_shield_flashbang.mdl");
	PRECACHE_MODEL("models/p_hegrenade.mdl");
	PRECACHE_MODEL("models/shield/p_shield_hegrenade.mdl");
	PRECACHE_MODEL("models/p_glock18.mdl");
	PRECACHE_MODEL("models/shield/p_shield_glock18.mdl");
	PRECACHE_MODEL("models/p_p228.mdl");
	PRECACHE_MODEL("models/shield/p_shield_p228.mdl");
	PRECACHE_MODEL("models/p_smokegrenade.mdl");
	PRECACHE_MODEL("models/shield/p_shield_smokegrenade.mdl");
	PRECACHE_MODEL("models/p_usp.mdl");
	PRECACHE_MODEL("models/shield/p_shield_usp.mdl");
	PRECACHE_MODEL("models/p_fiveseven.mdl");
	PRECACHE_MODEL("models/shield/p_shield_fiveseven.mdl");
	PRECACHE_MODEL("models/p_knife.mdl");
	PRECACHE_MODEL("models/shield/p_shield_knife.mdl");
	PRECACHE_MODEL("models/w_flashbang.mdl");
	PRECACHE_MODEL("models/w_hegrenade.mdl");
	PRECACHE_MODEL("models/p_sg550.mdl");
	PRECACHE_MODEL("models/p_g3sg1.mdl");
	PRECACHE_MODEL("models/p_m249.mdl");
	PRECACHE_MODEL("models/p_m3.mdl");
	PRECACHE_MODEL("models/p_m4a1.mdl");
	PRECACHE_MODEL("models/p_mac10.mdl");
	PRECACHE_MODEL("models/p_mp5.mdl");
	PRECACHE_MODEL("models/p_ump45.mdl");
	PRECACHE_MODEL("models/p_p90.mdl");
	PRECACHE_MODEL("models/p_scout.mdl");
	PRECACHE_MODEL("models/p_sg552.mdl");
	PRECACHE_MODEL("models/w_smokegrenade.mdl");
	PRECACHE_MODEL("models/p_tmp.mdl");
	PRECACHE_MODEL("models/p_elite.mdl");
	PRECACHE_MODEL("models/p_xm1014.mdl");
	PRECACHE_MODEL("models/p_galil.mdl");
	PRECACHE_MODEL("models/p_famas.mdl");
	PRECACHE_MODEL("models/p_shield.mdl");
	PRECACHE_MODEL("models/w_shield.mdl");

	Vector temp = g_vecZero;
	Vector vMin(-38, -24, -41);
	Vector vMax(38, 24, 41);

	for (i = 0; i < numPlayerModels; i++)
		ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, sPlayerModelFiles[i]);

	if (AreRunningCZero())
	{
		for (i = FirstCustomSkin; i <= LastCustomSkin; i++)
		{
			const char *fname = TheBotProfiles->GetCustomSkinFname(i);
			if (!fname)
				break;

			ENGINE_FORCE_UNMODIFIED(force_model_specifybounds_if_avail, (float *)&vMin, (float *)&vMax, fname);
		}
	}

	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke1.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke2.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke3.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/black_smoke4.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/fast_wallpuff1.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/smokepuff.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/gas_puff_01.spr");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc.tga");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc_nw.tga");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc_ne.tga");
	ENGINE_FORCE_UNMODIFIED(force_exactfile, (float *)&temp, (float *)&temp, "sprites/scope_arc_sw.tga");

	if (AreRunningCZero())
	{
		vMin = Vector(-13, -6, -22);
		vMax = Vector(13, 6, 22);
	}
	else
	{
		vMin = Vector(-12, -6, -22);
		vMax = Vector(12, 6, 22);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_deagle.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_p228.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_elite.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_usp.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_fiveseven.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_glock18.mdl");

	if (AreRunningCZero())
	{
		vMin = Vector(-26, -19, -21);
		vMax = Vector(26, 23, 21);
	}
	else
	{
		vMin = Vector(-25, -19, -21);
		vMax = Vector(25, 23, 21);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_xm1014.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_m3.mdl");

	if (AreRunningCZero())
	{
		vMin = Vector(-23, -9, -20);
		vMax = Vector(23, 17, 20);
	}
	else
	{
		vMin = Vector(-23, -8, -20);
		vMax = Vector(23, 8, 20);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_mac10.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_mp5.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_ump45.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_tmp.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_p90.mdl");

	if (AreRunningCZero())
	{
		vMin = Vector(-38, -33, -22);
		vMax = Vector(38, 15, 35);
	}
	else
	{
		vMin = Vector(-31, -8, -21);
		vMax = Vector(31, 12, 31);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_ak47.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_aug.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_awp.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_g3sg1.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_sg550.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_m4a1.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_scout.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_sg552.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_famas.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_galil.mdl");

	if (AreRunningCZero())
	{
		vMin = Vector(-30, -10, -20);
		vMax = Vector(30, 11, 20);
	}
	else
	{
		vMin = Vector(-24, -10, -20);
		vMax = Vector(25, 10, 20);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_m249.mdl");

	vMin = Vector(-7, -7, -15);
	vMax = Vector(7, 7, 15);

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_c4.mdl");

	vMin = Vector(-4, -8, -3);
	vMax = Vector(3, 7, 3);

	if (AreRunningCZero())
	{
		vMin = Vector(-17, -8, -3);
		vMax = Vector(17, 7, 3);
	}
	else
	{
		vMin = Vector(-4, -8, -3);
		vMax = Vector(3, 7, 3);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_c4.mdl");

	if (AreRunningCZero())
	{
		vMin = Vector(-7, -3, -18);
		vMax = Vector(7, 2, 18);
	}
	else
	{
		vMin = Vector(-7, -2, -18);
		vMax = Vector(7, 2, 18);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_flashbang.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_hegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_smokegrenade.mdl");

	if (AreRunningCZero())
		vMin = Vector(-5, -5, -7);
	else
		vMin = Vector(-5, -5, -5);

	vMax = Vector(5, 5, 14);

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_flashbang.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_hegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/w_smokegrenade.mdl");

	vMin = Vector(-7, -11, -18);
	vMax = Vector(7, 6, 18);

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/p_knife.mdl");

	if (AreRunningCZero())
	{
		vMin = Vector(-21, -25, -54);
		vMax = Vector(21, 23, 24);
	}
	else
	{
		vMin = Vector(-16, -8, -54);
		vMax = Vector(16, 6, 24);
	}

	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_deagle.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_fiveseven.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_flashbang.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_glock18.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_hegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_knife.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_p228.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_smokegrenade.mdl");
	ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, "models/shield/p_shield_usp.mdl");

	PRECACHE_SOUND("common/wpn_hudoff.wav");
	PRECACHE_SOUND("common/wpn_hudon.wav");
	PRECACHE_SOUND("common/wpn_moveselect.wav");
	PRECACHE_SOUND("common/wpn_select.wav");
	PRECACHE_SOUND("common/wpn_denyselect.wav");
	PRECACHE_SOUND("player/geiger6.wav");
	PRECACHE_SOUND("player/geiger5.wav");
	PRECACHE_SOUND("player/geiger4.wav");
	PRECACHE_SOUND("player/geiger3.wav");
	PRECACHE_SOUND("player/geiger2.wav");
	PRECACHE_SOUND("player/geiger1.wav");

	g_iShadowSprite = PRECACHE_MODEL("sprites/shadow_circle.spr");

	PRECACHE_MODEL("sprites/wall_puff1.spr");
	PRECACHE_MODEL("sprites/wall_puff2.spr");
	PRECACHE_MODEL("sprites/wall_puff3.spr");
	PRECACHE_MODEL("sprites/wall_puff4.spr");
	PRECACHE_MODEL("sprites/black_smoke1.spr");
	PRECACHE_MODEL("sprites/black_smoke2.spr");
	PRECACHE_MODEL("sprites/black_smoke3.spr");
	PRECACHE_MODEL("sprites/black_smoke4.spr");

#ifdef REGAMEDLL_FIXES
	PRECACHE_MODEL("sprites/gas_puff_01.spr");
#endif

	PRECACHE_MODEL("sprites/fast_wallpuff1.spr");
	PRECACHE_MODEL("sprites/pistol_smoke1.spr");
	PRECACHE_MODEL("sprites/pistol_smoke2.spr");
	PRECACHE_MODEL("sprites/rifle_smoke1.spr");
	PRECACHE_MODEL("sprites/rifle_smoke2.spr");
	PRECACHE_MODEL("sprites/rifle_smoke3.spr");
	PRECACHE_GENERIC("sprites/scope_arc.tga");
	PRECACHE_GENERIC("sprites/scope_arc_nw.tga");
	PRECACHE_GENERIC("sprites/scope_arc_ne.tga");
	PRECACHE_GENERIC("sprites/scope_arc_sw.tga");

	m_usResetDecals = g_engfuncs.pfnPrecacheEvent(1, "events/decal_reset.sc");
}

const char *EXT_FUNC GetGameDescription()
{
#ifdef REGAMEDLL_ADD
	if (CSGameRules()) {
		return CSGameRules()->GetGameDescription();
	}
#else
	if (AreRunningCZero()) {
		return "Condition Zero";
	}
#endif
	return "Counter-Strike";
}

void EXT_FUNC SysEngine_Error(const char *error_string)
{
	;
}

void EXT_FUNC PlayerCustomization(edict_t *pEntity, customization_t *pCust)
{
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (!pPlayer)
	{
		ALERT(at_console, "PlayerCustomization:  Couldn't get player!\n");
		return;
	}

	if (!pCust)
	{
		ALERT(at_console, "PlayerCustomization:  NULL customization!\n");
		return;
	}

	switch (pCust->resource.type)
	{
	case t_decal:
		pPlayer->SetCustomDecalFrames(pCust->nUserData2);
		break;
	case t_sound:
	case t_skin:
	case t_model:
		break;
	default:
		ALERT(at_console, "PlayerCustomization:  Unknown customization type!\n");
		break;
	}
}

void EXT_FUNC SpectatorConnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorConnect();
	}
}

void EXT_FUNC SpectatorDisconnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorDisconnect();
	}
}

void EXT_FUNC SpectatorThink(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
	{
		pPlayer->SpectatorThink();
	}
}

void EXT_FUNC SetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas)
{
	edict_t *pView = pClient;

	// Find the client's PVS
	if (pViewEntity)
	{
		pView = pViewEntity;
	}

	if (pClient->v.flags & FL_PROXY)
	{
		*pvs = nullptr;	// the spectator proxy sees
		*pas = nullptr;	// and hears everything
		return;
	}

	CBasePlayer *pPlayer = CBasePlayer::Instance(pClient);
	if (pPlayer && pPlayer->pev->iuser2 && pPlayer->m_hObserverTarget)
	{
		if (pPlayer->m_afPhysicsFlags & PFLAG_OBSERVER)
		{
			pView = pPlayer->m_hObserverTarget->edict();
			UTIL_SetOrigin(pPlayer->pev, pPlayer->m_hObserverTarget->pev->origin);
		}
	}

	Vector org = pView->v.origin + pView->v.view_ofs;

	if (pView->v.flags & FL_DUCKING)
	{
		org = org + (VEC_HULL_MIN - VEC_DUCK_HULL_MIN);
	}

	*pvs = ENGINE_SET_PVS((float *)&org);
	*pas = ENGINE_SET_PAS((float *)&org);
}

void ResetPlayerPVS(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];

	Q_memset(pvs, 0, sizeof(*pvs));
	pvs->headnode = client->headnode;
	pvs->num_leafs = client->num_leafs;
	Q_memcpy(pvs->leafnums, client->leafnums, sizeof(pvs->leafnums));
}

bool CheckPlayerPVSLeafChanged(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];
	if (pvs->headnode != client->headnode || pvs->num_leafs != client->num_leafs)
		return true;

	for (int i = 0; i < pvs->num_leafs; i++)
	{
		if (client->leafnums[i] != pvs->leafnums[i])
			return true;
	}

	return false;
}

void MarkEntityInPVS(int clientnum, int entitynum, float time, bool inpvs)
{
	PLAYERPVSSTATUS *pvs;
	ENTITYPVSSTATUS *es;

	pvs = &g_PVSStatus[clientnum];
	es = &pvs->m_Status[entitynum];

	if (inpvs)
		es->m_fTimeEnteredPVS = time;
	else
		es->m_fTimeEnteredPVS = 0;
}

bool CheckEntityRecentlyInPVS(int clientnum, int entitynum, float currenttime)
{
	PLAYERPVSSTATUS *pvs;
	ENTITYPVSSTATUS *es;

	pvs = &g_PVSStatus[clientnum];
	es = &pvs->m_Status[entitynum];

	if (es->m_fTimeEnteredPVS && es->m_fTimeEnteredPVS + 1.0f >= currenttime)
	{
		return true;
	}

	return false;
}

BOOL EXT_FUNC AddToFullPack(struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, BOOL player, unsigned char *pSet)
{
	if (ent != host)
	{
		if ((ent->v.effects & EF_NODRAW) == EF_NODRAW)
			return FALSE;

#ifdef REGAMEDLL_ADD
		if (ent->v.owner == host)
		{
			// the owner can't see this entity
			if ((ent->v.effects & EF_OWNER_NO_VISIBILITY) == EF_OWNER_NO_VISIBILITY)
				return FALSE;
		}
		// no one can't see this entity except the owner
		else if ((ent->v.effects & EF_OWNER_VISIBILITY) == EF_OWNER_VISIBILITY)
			return FALSE;
#endif
	}

	if (!ent->v.modelindex || !STRING(ent->v.model))
		return FALSE;

	if ((ent->v.flags & FL_SPECTATOR) == FL_SPECTATOR && ent != host)
		return FALSE;

	int i;
	int hostnum = ENTINDEX(host) - 1;
	if (CheckPlayerPVSLeafChanged(host, hostnum))
		ResetPlayerPVS(host, hostnum);

#ifdef REGAMEDLL_ADD
	if ((ent->v.effects & EF_FORCEVISIBILITY) != EF_FORCEVISIBILITY)
#endif
	{
		if (ent != host)
		{
			if (!CheckEntityRecentlyInPVS(hostnum, e, gpGlobals->time))
			{
				if (!ENGINE_CHECK_VISIBILITY(ent, pSet))
				{
					MarkEntityInPVS(hostnum, e, 0, false);
					return FALSE;
				}

				MarkEntityInPVS(hostnum, e, gpGlobals->time, true);
			}
		}
	}

	if ((ent->v.flags & FL_SKIPLOCALHOST) == FL_SKIPLOCALHOST && (hostflags & 1) && ent->v.owner == host)
		return FALSE;

	if (host->v.groupinfo)
	{
		UTIL_SetGroupTrace(host->v.groupinfo, GROUP_OP_AND);

		if (ent->v.groupinfo)
		{
			if (g_groupop == GROUP_OP_AND)
			{
				if (!(ent->v.groupinfo & host->v.groupinfo))
					return FALSE;
			}
			else if (g_groupop == GROUP_OP_NAND)
			{
				if (ent->v.groupinfo & host->v.groupinfo)
					return FALSE;
			}
		}

		UTIL_UnsetGroupTrace();
	}

	Q_memset(state, 0, sizeof(entity_state_t));

	state->number = e;
	state->entityType = ENTITY_NORMAL;

	if (ent->v.flags & FL_CUSTOMENTITY)
		state->entityType = ENTITY_BEAM;

	state->animtime = int(1000.0 * ent->v.animtime) / 1000.0;

	Q_memcpy(state->origin, ent->v.origin, sizeof(float) * 3);
	Q_memcpy(state->angles, ent->v.angles, sizeof(float) * 3);
	Q_memcpy(state->mins, ent->v.mins, sizeof(float) * 3);
	Q_memcpy(state->maxs, ent->v.maxs, sizeof(float) * 3);
	Q_memcpy(state->startpos, ent->v.startpos, sizeof(float) * 3);
	Q_memcpy(state->endpos, ent->v.endpos, sizeof(float) * 3);

	state->impacttime = ent->v.impacttime;
	state->starttime = ent->v.starttime;
	state->modelindex = ent->v.modelindex;
	state->frame = ent->v.frame;
	state->skin = ent->v.skin;
	state->effects = ent->v.effects;

#ifdef REGAMEDLL_ADD
	// don't send unhandled custom bits to client
	state->effects &= ~EF_CUSTOM_BITS;

	if  (ent->v.skin == CONTENTS_LADDER &&
		(host->v.iuser3 & PLAYER_PREVENT_CLIMB) == PLAYER_PREVENT_CLIMB) {
		state->skin = CONTENTS_EMPTY;
	}
#endif

	// add studio interpolation if non-player entity is moving (why?)
	if (!player &&
#ifdef REGAMEDLL_ADD
		// adds slerp (studio interpolation) if not set
		!(ent->v.effects & EF_NOSLERP) &&
#endif
		ent->v.animtime && !ent->v.velocity.x && !ent->v.velocity.y && !ent->v.velocity.z)
		state->eflags |= EFLAG_SLERP;

	state->scale = ent->v.scale;
	state->solid = ent->v.solid;
	state->colormap = ent->v.colormap;
	state->movetype = ent->v.movetype;
	state->sequence = ent->v.sequence;
	state->framerate = ent->v.framerate;
	state->body = ent->v.body;

	for (i = 0; i < 4; i++)
		state->controller[i] = ent->v.controller[i];

	for (i = 0; i < 2; i++)
		state->blending[i] = ent->v.blending[i];

	state->rendermode = ent->v.rendermode;
	state->renderamt = int(ent->v.renderamt);
	state->renderfx = ent->v.renderfx;
	state->rendercolor.r = byte(ent->v.rendercolor.x);
	state->rendercolor.g = byte(ent->v.rendercolor.y);
	state->rendercolor.b = byte(ent->v.rendercolor.z);

	state->aiment = 0;

	// following something
	if (ent->v.aiment)
	{
#ifdef REGAMEDLL_ADD
		// if set, it will still follow the player with a bit of "delay", still looks fine (experimental)
		if (ent->v.effects & EF_FOLLOWKEEPRENDER)
		{
			// will keep the current render entity values if it's set
			state->movetype = MOVETYPE_NONE;
		}
		else
#endif
		{
			state->aiment = ENTINDEX(ent->v.aiment);
		}
	}

	state->owner = 0;
	if (ent->v.owner)
	{
		int owner = ENTINDEX(ent->v.owner);
		if (owner >= 1 && owner <= gpGlobals->maxClients)
			state->owner = owner;
	}

	if (player)
	{
		Q_memcpy(state->basevelocity, ent->v.basevelocity, sizeof(float) * 3);

		state->weaponmodel = MODEL_INDEX(STRING(ent->v.weaponmodel));
		state->gaitsequence = ent->v.gaitsequence;

		state->spectator = (ent->v.flags & FL_SPECTATOR) ? TRUE : FALSE;
		state->friction = ent->v.friction;
		state->gravity = ent->v.gravity;
		state->usehull = (ent->v.flags & FL_DUCKING) ? 1 : 0;
		state->health = int(ent->v.health);
	}
	else
		state->playerclass = ent->v.playerclass;

	state->iuser4 = ent->v.iuser4;
	return TRUE;
}

// Creates baselines used for network encoding, especially for player data since players are not spawned until connect time.
void EXT_FUNC CreateBaseline(int player, int eindex, struct entity_state_s *baseline, edict_t *entity, int playermodelindex, Vector player_mins, Vector player_maxs)
{
	baseline->origin = entity->v.origin;
	baseline->angles = entity->v.angles;

	baseline->frame = entity->v.frame;
	baseline->skin = (short)entity->v.skin;

	// render information
	baseline->rendermode = byte(entity->v.rendermode);
	baseline->renderamt = byte(entity->v.renderamt);
	baseline->rendercolor.r	= byte(entity->v.rendercolor.x);
	baseline->rendercolor.g	= byte(entity->v.rendercolor.y);
	baseline->rendercolor.b	= byte(entity->v.rendercolor.z);
	baseline->renderfx = byte(entity->v.renderfx);

	if (player)
	{
		baseline->mins = player_mins;
		baseline->maxs = player_maxs;

		baseline->colormap = eindex;
		baseline->modelindex = playermodelindex;
		baseline->friction = 1.0;
		baseline->movetype = MOVETYPE_WALK;

		baseline->solid = SOLID_SLIDEBOX;
		baseline->scale = entity->v.scale;
		baseline->framerate = 1.0;
		baseline->gravity = 1.0;
	}
	else
	{
		baseline->mins = entity->v.mins;
		baseline->maxs = entity->v.maxs;

		baseline->colormap = 0;
		baseline->modelindex = entity->v.modelindex;
		baseline->movetype = entity->v.movetype;

		baseline->scale = entity->v.scale;
		baseline->solid = entity->v.solid;
		baseline->framerate = entity->v.framerate;
		baseline->gravity = entity->v.gravity;
	}
}

void Entity_FieldInit(struct delta_s *pFields)
{
	entity_field_alias[FIELD_ORIGIN0].field = DELTA_FINDFIELD(pFields, entity_field_alias[FIELD_ORIGIN0].name);
	entity_field_alias[FIELD_ORIGIN1].field = DELTA_FINDFIELD(pFields, entity_field_alias[FIELD_ORIGIN1].name);
	entity_field_alias[FIELD_ORIGIN2].field = DELTA_FINDFIELD(pFields, entity_field_alias[FIELD_ORIGIN2].name);
	entity_field_alias[FIELD_ANGLES0].field = DELTA_FINDFIELD(pFields, entity_field_alias[FIELD_ANGLES0].name);
	entity_field_alias[FIELD_ANGLES1].field = DELTA_FINDFIELD(pFields, entity_field_alias[FIELD_ANGLES1].name);
	entity_field_alias[FIELD_ANGLES2].field = DELTA_FINDFIELD(pFields, entity_field_alias[FIELD_ANGLES2].name);
}

// Callback for sending entity_state_t info over network.
void Entity_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to)
{
	entity_state_t *f, *t;
	int localplayer = 0;
	static int initialized = 0;

	if (!initialized)
	{
		Entity_FieldInit(pFields);
		initialized = 1;
	}

	f = (entity_state_t *)from;
	t = (entity_state_t *)to;

	// Never send origin to local player, it's sent with more resolution in clientdata_t structure
	localplayer = (t->number - 1) == ENGINE_CURRENT_PLAYER();

	if (localplayer)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);
	}
	if (t->impacttime != 0 && t->starttime != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);

		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ANGLES0].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ANGLES1].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ANGLES2].field);
	}
	if (t->movetype == MOVETYPE_FOLLOW && t->aiment != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);
	}
	else if (t->aiment != f->aiment)
	{
		DELTA_SETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);
	}
}

void Player_FieldInit(struct delta_s *pFields)
{
	player_field_alias[FIELD_ORIGIN0].field = DELTA_FINDFIELD(pFields, player_field_alias[FIELD_ORIGIN0].name);
	player_field_alias[FIELD_ORIGIN1].field = DELTA_FINDFIELD(pFields, player_field_alias[FIELD_ORIGIN1].name);
	player_field_alias[FIELD_ORIGIN2].field = DELTA_FINDFIELD(pFields, player_field_alias[FIELD_ORIGIN2].name);
}

// Callback for sending entity_state_t for players info over network.
void Player_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to)
{
	entity_state_t *f, *t;
	int localplayer = 0;

	static int initialized = 0;
	if (!initialized)
	{
		Player_FieldInit(pFields);
		initialized = 1;
	}

	f = (entity_state_t *)from;
	t = (entity_state_t *)to;

	// Never send origin to local player, it's sent with more resolution in clientdata_t structure
	localplayer = (t->number - 1) == ENGINE_CURRENT_PLAYER();

	if (localplayer)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);
	}
	if (t->movetype == MOVETYPE_FOLLOW && t->aiment != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);
	}
	else if (t->aiment != f->aiment)
	{
		DELTA_SETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN0].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN1].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[FIELD_ORIGIN2].field);
	}
}

void Custom_Entity_FieldInit(delta_s *pFields)
{
	custom_entity_field_alias[CUSTOMFIELD_ORIGIN0].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ORIGIN0].name);
	custom_entity_field_alias[CUSTOMFIELD_ORIGIN1].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ORIGIN1].name);
	custom_entity_field_alias[CUSTOMFIELD_ORIGIN2].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ORIGIN2].name);
	custom_entity_field_alias[CUSTOMFIELD_ANGLES0].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ANGLES0].name);
	custom_entity_field_alias[CUSTOMFIELD_ANGLES1].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ANGLES1].name);
	custom_entity_field_alias[CUSTOMFIELD_ANGLES2].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ANGLES2].name);
	custom_entity_field_alias[CUSTOMFIELD_SKIN].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_SKIN].name);
	custom_entity_field_alias[CUSTOMFIELD_SEQUENCE].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_SEQUENCE].name);
	custom_entity_field_alias[CUSTOMFIELD_ANIMTIME].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[CUSTOMFIELD_ANIMTIME].name);
}

// Callback for sending entity_state_t info ( for custom entities ) over network.
void Custom_Encode(struct delta_s *pFields, const unsigned char *from, const unsigned char *to)
{
	entity_state_t *f, *t;
	int beamType;
	static int initialized = 0;

	if (!initialized)
	{
		Custom_Entity_FieldInit(pFields);
		initialized = 1;
	}

	f = (entity_state_t *)from;
	t = (entity_state_t *)to;

	beamType = t->rendermode & 0x0F;

	if (beamType != BEAM_POINTS)
	{
		if (beamType != BEAM_ENTPOINT)
		{
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ORIGIN0].field);
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ORIGIN1].field);
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ORIGIN2].field);
		}

		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ANGLES0].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ANGLES1].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ANGLES2].field);
	}

	if (beamType != BEAM_ENTS && beamType != BEAM_ENTPOINT)
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_SKIN].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_SEQUENCE].field);
	}

	// animtime is compared by rounding first
	// see if we really shouldn't actually send it
	if (int(f->animtime) == int(t->animtime))
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[CUSTOMFIELD_ANIMTIME].field);
	}
}

// Allows game .dll to override network encoding of certain types of entities and tweak values, etc.
void EXT_FUNC RegisterEncoders()
{
	DELTA_ADDENCODER("Entity_Encode", Entity_Encode);
	DELTA_ADDENCODER("Custom_Encode", Custom_Encode);
	DELTA_ADDENCODER("Player_Encode", Player_Encode);
}

int EXT_FUNC GetWeaponData(edict_t *pEdict, struct weapon_data_s *info)
{
#ifdef CLIENT_WEAPONS
	entvars_t *pev = &pEdict->v;
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	Q_memset(info, 0, sizeof(weapon_data_t) * MAX_WEAPONS);

	if (!pPlayer)
		return 1;

	// go through all of the weapons and make a list of the ones to pack
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		auto pPlayerItem = pPlayer->m_rgpPlayerItems[i];
		while (pPlayerItem)
		{
			// there's a weapon here. Should I pack it?
			auto weapon = (CBasePlayerWeapon *)pPlayerItem->GetWeaponPtr();
			if (weapon && weapon->UseDecrement())
			{
				// Get The ID
				ItemInfo II;
				Q_memset(&II, 0, sizeof(II));

#ifdef REGAMEDLL_API
				pPlayerItem->CSPlayerItem()->GetItemInfo(&II);
#else
				weapon->GetItemInfo(&II);
#endif

				if (II.iId >= 0 && II.iId < MAX_WEAPONS)
				{
					auto item = &info[II.iId];

					item->m_iId = II.iId;
					item->m_iClip = weapon->m_iClip;
					item->m_flTimeWeaponIdle = Q_max(weapon->m_flTimeWeaponIdle, -0.001f);
					item->m_flNextPrimaryAttack = Q_max(weapon->m_flNextPrimaryAttack, -0.001f);
					item->m_flNextSecondaryAttack = Q_max(weapon->m_flNextSecondaryAttack, -0.001f);
					item->m_flNextReload = Q_max(weapon->m_flNextReload, -0.001f);
					item->m_fInReload = weapon->m_fInReload;
					item->m_fInSpecialReload = weapon->m_fInSpecialReload;
					item->m_fInZoom = weapon->m_iShotsFired;
					item->m_fAimedDamage = weapon->m_flLastFire;
					item->m_iWeaponState = weapon->m_iWeaponState;
					item->fuser2 = weapon->m_flStartThrow;
					item->fuser3 = weapon->m_flReleaseThrow;
					item->iuser1 = weapon->m_iSwing;

#ifdef REGAMEDLL_FIXES
					if (pPlayerItem == pPlayer->m_pActiveItem && !weapon->m_fInReload && weapon->m_iClip == II.iMaxClip)
					{
						const WeaponInfoStruct *wpnInfo = GetDefaultWeaponInfo(II.iId);

						if (wpnInfo && wpnInfo->gunClipSize != II.iMaxClip)
							item->m_iClip = wpnInfo->gunClipSize;
					}
#endif
				}
			}

			pPlayerItem = pPlayerItem->m_pNext;
		}
	}
#else
	Q_memset(info, 0, sizeof(weapon_data_t) * MAX_WEAPONS);
#endif

	return 1;
}

// Data sent to current client only engine sets cd to 0 before calling.
void EXT_FUNC UpdateClientData(const edict_t *ent, int sendweapons, struct clientdata_s *cd)
{
	if (!ent || !ent->pvPrivateData)
		return;

	entvars_t *pevOrg = nullptr;
	entvars_t *pev = const_cast<entvars_t *>(&ent->v);
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	// if user is spectating different player in First person, override some vars
	if (pPlayer && pPlayer->pev->iuser1 == OBS_IN_EYE && pPlayer->m_hObserverTarget)
	{
		pevOrg = pev;
		pev = pPlayer->m_hObserverTarget->pev;
		pPlayer = CBasePlayer::Instance(pev);
	}

	cd->flags = pev->flags;
#ifdef REGAMEDLL_FIXES
	cd->health = max(pev->health, 0.0f);
#else
	cd->health = pev->health;
#endif

	cd->viewmodel = MODEL_INDEX(STRING(pev->viewmodel));
	cd->waterlevel = pev->waterlevel;
	cd->watertype = pev->watertype;
	cd->weapons = pev->weapons;
	cd->origin = pev->origin;
	cd->velocity = pev->velocity;
	cd->view_ofs = pev->view_ofs;
	cd->punchangle = pev->punchangle;
	cd->bInDuck = pev->bInDuck;
	cd->flTimeStepSound = pev->flTimeStepSound;
	cd->flDuckTime = pev->flDuckTime;
	cd->flSwimTime = pev->flSwimTime;
	cd->waterjumptime = int(pev->teleport_time);

	Q_strcpy(cd->physinfo, ENGINE_GETPHYSINFO(ent));

	cd->maxspeed = pev->maxspeed;
	cd->fov = pev->fov;
	cd->weaponanim = pev->weaponanim;
	cd->pushmsec = pev->pushmsec;

	if (pevOrg)
	{
		cd->iuser1 = pevOrg->iuser1;
		cd->iuser2 = pevOrg->iuser2;
		cd->iuser3 = pevOrg->iuser3;
	}
	else
	{
		cd->iuser1 = pev->iuser1;
		cd->iuser2 = pev->iuser2;
		cd->iuser3 = pev->iuser3;
	}

	cd->fuser1 = pev->fuser1;
	cd->fuser3 = pev->fuser3;
	cd->fuser2 = pev->fuser2;

	if (sendweapons && pPlayer)
	{
		cd->ammo_shells = pPlayer->ammo_buckshot;
		cd->ammo_nails = pPlayer->ammo_9mm;
		cd->ammo_cells = pPlayer->ammo_556nato;
		cd->ammo_rockets = pPlayer->ammo_556natobox;
		cd->vuser2.x = pPlayer->ammo_762nato;
		cd->vuser2.y = pPlayer->ammo_45acp;
		cd->vuser2.z = pPlayer->ammo_50ae;
		cd->vuser3.x = pPlayer->ammo_338mag;
		cd->vuser3.y = pPlayer->ammo_57mm;
		cd->vuser3.z = pPlayer->ammo_357sig;
		cd->m_flNextAttack = pPlayer->m_flNextAttack;

		int iUser3 = 0;

		if (
#ifdef REGAMEDLL_API
			pPlayer->CSPlayer()->m_bCanShootOverride ||
#endif
			(pPlayer->m_bCanShoot && !pPlayer->m_bIsDefusing))
			iUser3 |= PLAYER_CAN_SHOOT;

		if (g_pGameRules->IsFreezePeriod())
			iUser3 |= PLAYER_FREEZE_TIME_OVER;

		if (pPlayer->m_signals.GetState() & SIGNAL_BOMB)
			iUser3 |= PLAYER_IN_BOMB_ZONE;

		if (pPlayer->HasShield())
			iUser3 |= PLAYER_HOLDING_SHIELD;

		if (pPlayer->pev->iuser1 == OBS_NONE && !pevOrg)
		{
#ifdef REGAMEDLL_ADD
			// useful for mods
			iUser3 |= pev->iuser3;
#endif
			cd->iuser3 = iUser3;
		}

		if (pPlayer->m_pActiveItem)
		{
			ItemInfo II;
			Q_memset(&II, 0, sizeof(II));

			CBasePlayerWeapon *weapon = (CBasePlayerWeapon *)pPlayer->m_pActiveItem->GetWeaponPtr();
			if (weapon && weapon->UseDecrement() &&
#ifdef REGAMEDLL_API
				weapon->CSPlayerItem()->GetItemInfo(&II)
#else
				weapon->GetItemInfo(&II)
#endif
				)
			{
				cd->m_iId = II.iId;

				if ((unsigned int)weapon->m_iPrimaryAmmoType < MAX_AMMO_SLOTS)
				{
					cd->vuser4.x = weapon->m_iPrimaryAmmoType;
					cd->vuser4.y = pPlayer->m_rgAmmo[weapon->m_iPrimaryAmmoType];
				}
				else
				{
					cd->vuser4.x = -1.0;
					cd->vuser4.y = 0;
				}
			}
		}
	}
}

void EXT_FUNC CmdStart(const edict_t *pEdict, const struct usercmd_s *cmd, unsigned int random_seed)
{
	entvars_t *pev = const_cast<entvars_t *>(&pEdict->v);
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer)
		return;

	if (pPlayer->pev->groupinfo)
		UTIL_SetGroupTrace(pPlayer->pev->groupinfo, GROUP_OP_AND);

	pPlayer->random_seed = random_seed;
}

void EXT_FUNC CmdEnd(const edict_t *pEdict)
{
	entvars_t *pev = const_cast<entvars_t *>(&pEdict->v);
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer)
		return;

	if (pPlayer->pev->groupinfo)
		UTIL_UnsetGroupTrace();

	if (pev->flags & FL_DUCKING)
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
}

int EXT_FUNC ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
{
	// Parse stuff from args
	int max_buffer_size = *response_buffer_size;

	// Zero it out since we aren't going to respond.
	// If we wanted to response, we'd write data into response_buffer
	*response_buffer_size = 0;

	// Since we don't listen for anything here, just respond that it's a bogus message
	// If we didn't reject the message, we'd return 1 for success instead.
	return 0;
}

BOOL EXT_FUNC GetHullBounds(int hullnumber, float *mins, float *maxs)
{
#ifdef REGAMEDLL_ADD
	if (hullbounds_sets.value == 0.0f)
	{
		return (hullnumber < 3) ? TRUE : FALSE;
	}
#endif

#ifdef REGAMEDLL_FIXES
	switch (hullnumber)
	{
	case 0: // Normal player
		Q_memcpy(mins, (float*)VEC_HULL_MIN, sizeof(vec3_t));
		Q_memcpy(maxs, (float*)VEC_HULL_MAX, sizeof(vec3_t));
		return TRUE;
	case 1: // Crouched player
		Q_memcpy(mins, (float*)VEC_DUCK_HULL_MIN, sizeof(vec3_t));
		Q_memcpy(maxs, (float*)VEC_DUCK_HULL_MAX, sizeof(vec3_t));
		return TRUE;
	case 2: // Point based hull
		Q_memcpy(mins, (float*)Vector(0, 0, 0), sizeof(vec3_t));
		Q_memcpy(maxs, (float*)Vector(0, 0, 0), sizeof(vec3_t));
		return TRUE;
	default:
		return FALSE;
	}
#else // REGAMEDLL_FIXES
	switch (hullnumber)
	{
	case 0: // Normal player
		mins = VEC_HULL_MIN;
		maxs = VEC_HULL_MAX;
		return TRUE;
	case 1: // Crouched player
		mins = VEC_DUCK_HULL_MIN;
		maxs = VEC_DUCK_HULL_MAX;
		return TRUE;
	case 2: // Point based hull
		mins = Vector(0, 0, 0);
		maxs = Vector(0, 0, 0);
		return TRUE;
	default:
		return FALSE;
	}
#endif // REGAMEDLL_FIXES
}

// Create pseudo-baselines for items that aren't placed in the map at spawn time, but which are likely
// to be created during play ( e.g., grenades, ammo packs, projectiles, corpses, etc. )
void EXT_FUNC CreateInstancedBaselines()
{
#ifndef REGAMEDLL_FIXES
	int iret = 0;
	entity_state_t state;

	Q_memset(&state, 0, sizeof(state));

	// Create any additional baselines here for things like grendates, etc.
	// iret = ENGINE_INSTANCE_BASELINE(pc->pev->classname, &state);

	// Destroy objects.
	// UTIL_Remove(pc);
#endif
}

int EXT_FUNC InconsistentFile(const edict_t *pEdict, const char *filename, char *disconnect_message)
{
	// Server doesn't care?
	if (!CVAR_GET_FLOAT("mp_consistency"))
		return 0;

	// Default behavior is to kick the player
	Q_sprintf(disconnect_message, "Server is enforcing file consistency for %s\n", filename);

	// Kick now with specified disconnect message.
	return 1;
}

// The game .dll should return 1 if lag compensation should be allowed ( could also just set
// the sv_unlag cvar.
// Most games right now should return 0, until client-side weapon prediction code is written
// and tested for them ( note you can predict weapons, but not do lag compensation, too,
// if you want.
int EXT_FUNC AllowLagCompensation()
{
	return 1;
}
