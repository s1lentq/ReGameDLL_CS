#include "precompiled.h"
#include "entity_state.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//float g_flTimeLimit = 0;
//float g_flResetTime = 0;
//bool g_bClientPrintEnable = true;

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
	"models/player/spetsnaz/spetsnaz.mdl",	// CZ
	"models/player/militia/militia.mdl"	// CZ
};

bool g_skipCareerInitialSpawn;

static entity_field_alias_t entity_field_alias[] =
{
	{ "origin[0]",	0 },
	{ "origin[1]",	0 },
	{ "origin[2]",	0 },
	{ "angles[0]",	0 },
	{ "angles[1]",	0 },
	{ "angles[2]",	0 },
};

static entity_field_alias_t player_field_alias[] =
{
	{ "origin[0]",	0 },
	{ "origin[1]",	0 },
	{ "origin[2]",	0 },
}

static entity_field_alias_t custom_entity_field_alias[] =
{
	{ "origin[0]",	0 },
	{ "origin[1]",	0 },
	{ "origin[2]",	0 },
	{ "angles[0]",	0 },
	{ "angles[1]",	0 },
	{ "angles[2]",	0 },
	{ "skin",	0 },
	{ "sequence",	0 },
	{ "animtime",	0 },
}

#else

//float g_flTimeLimit;
//float g_flResetTime;
//bool g_bClientPrintEnable;

char *sPlayerModelFiles[12];
bool g_skipCareerInitialSpawn;

entity_field_alias_t entity_field_alias[6];
entity_field_alias_t player_field_alias[3];
entity_field_alias_t custom_entity_field_alias[9];

#endif // HOOK_GAMEDLL

PLAYERPVSSTATUS g_PVSStatus[32];
unsigned short m_usResetDecals;
unsigned short g_iShadowSprite;

/* <47b45> ../cstrike/dlls/client.cpp:76 */
NOBODY int CMD_ARGC_(void)
{
//	{
//		int i;                                                //    80
//	}
}

/* <47b84> ../cstrike/dlls/client.cpp:90 */
NOBODY const char *CMD_ARGV_(int i)
{
}

/* <47eac> ../cstrike/dlls/client.cpp:180 */
NOBODY void set_suicide_frame(entvars_t *pev)
{
//	FStrEq(const char *sz1,
//		const char *sz2);  //   182
}

/* <47a58> ../cstrike/dlls/client.cpp:192 */
NOBODY inline void TeamChangeUpdate(CBasePlayer *player, int team_id)
{
//	{
//		int t;                                                //   194
//	}
}

/* <4731f> ../cstrike/dlls/client.cpp:222 */
NOBODY inline void BlinkAccount(CBasePlayer *player, int numBlinks)
{
}

/* <47efd> ../cstrike/dlls/client.cpp:236 */
NOBODY BOOL ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *szRejectReason)
{
}

/* <47f5b> ../cstrike/dlls/client.cpp:255 */
NOBODY void ClientDisconnect(edict_t *pEntity)
{
//	{
//		class CBasePlayer *pPlayer;                          //   257
//		class CSound *pSound;                                //   276
//		Instance(edict_t *pent);  //   257
//	}
}

/* <4c477> ../cstrike/dlls/client.cpp:306 */
void respawn(entvars_t *pev, BOOL fCopyCorpse)
{
	if (gpGlobals->coop || gpGlobals->deathmatch)
	{
		CHalfLifeMultiplay *mp = g_pGameRules;

		if (mp->m_iTotalRoundsPlayed > 0)
			mp->MarkSpawnSkipped();

		CBasePlayer *pPlayer = GetClassPtr((CBasePlayer *)pev);

		if (mp->IsCareer() && mp->ShouldSkipSpawn() && pPlayer->IsAlive())
			g_skipCareerInitialSpawn = true;

		pPlayer->Spawn();
		g_skipCareerInitialSpawn = false;
	}
	else if (pev->deadflag > DEAD_NO)
		SERVER_COMMAND("reload\n");
}

/* <48013> ../cstrike/dlls/client.cpp:347 */
NOBODY void ClientKill(edict_t *pEntity)
{
//	{
//		entvars_t *pev;                                      //   349
//		class CHalfLifeMultiplay *mp;                        //   350
//		class CBasePlayer *pl;                               //   352
//		Instance(entvars_t *pev);  //   352
//		IsObserver(CBasePlayer *const this);  //   354
//	}
}

/* <47a8a> ../cstrike/dlls/client.cpp:379 */
NOBODY void ShowMenu(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, BOOL fNeedMore, char *pszText)
{
}

/* <4735f> ../cstrike/dlls/client.cpp:390 */
NOBODY void ShowVGUIMenu(CBasePlayer *pPlayer, int MenuType, int BitMask, char *szOldMenu)
{
}

/* <4c3c5> ../cstrike/dlls/client.cpp:414 */
NOBODY int CountTeams(void)
{
//	{
//		int iNumCT;                                           //   416
//		int iNumTerrorist;                                    //   416
//		class CBaseEntity *pPlayer;                          //   421
//		class CBasePlayer *player;                           //   422
//		edict(CBaseEntity *const this);  //   425
//		FNullEnt(const edict_t *pent);  //   425
//	}
}

/* <4c2be> ../cstrike/dlls/client.cpp:443 */
NOBODY void ListPlayers(CBasePlayer *current)
{
//	{
//		class CBaseEntity *pPlayer;                          //   445
//		class CBasePlayer *player;                           //   446
//		char message;                                         //   447
//		char cNumber;                                         //   448
//		int iUserID;                                          //   449
//		edict(CBaseEntity *const this);  //   454
//		FNullEnt(const edict_t *pent);  //   454
//		edict(CBaseEntity *const this);  //   460
//	}
}

/* <4c200> ../cstrike/dlls/client.cpp:475 */
NOBODY int CountTeamPlayers(int iTeam)
{
//	{
//		class CBaseEntity *pPlayer;                          //   477
//		int i;                                                //   478
//	}
}

/* <4c4ef> ../cstrike/dlls/client.cpp:494 */
NOBODY void ProcessKickVote(CBasePlayer *pVotingPlayer, CBasePlayer *pKickPlayer)
{
//	{
//		class CBaseEntity *pTempEntity;                      //   500
//		class CBasePlayer *pTempPlayer;                      //   501
//		int iValidVotes;                                      //   502
//		int iVoteID;                                          //   503
//		int iVotesNeeded;                                     //   504
//		float fKickPercent;                                   //   505
//		int iTeamCount;                                       //   507
//		CountTeamPlayers(int iTeam);  //   507
//		edict(CBaseEntity *const this);  //   560
//		FNullEnt(const edict_t *pent);  //   560
//		edict(CBaseEntity *const this);  //   517
//		FNullEnt(const edict_t *pent);  //   517
//	}
}

/* <48298> ../cstrike/dlls/client.cpp:580 */
NOBODY TeamName SelectDefaultTeam(void)
{
//	{
//		enum TeamName team;                                   //   582
//		class CHalfLifeMultiplay *mp;                        //   583
//	}
}

/* <473a3> ../cstrike/dlls/client.cpp:638 */
void CheckStartMoney(void)
{
	int money = (int)startmoney.value;

	if (money > 16000)
		CVAR_SET_FLOAT("mp_startmoney", 16000);
	else if (money < 800)
		CVAR_SET_FLOAT("mp_startmoney", 800);
}

/* <4c084> ../cstrike/dlls/client.cpp:661 */
NOBODY void ClientPutInServer(edict_t *pEntity)
{
//	{
//		class CBasePlayer *pPlayer;                          //   663
//		class CBaseEntity *Target;                           //   664
//		Vector CamAngles;                               //   665
//		class CHalfLifeMultiplay *mp;                        //   666
//		entvars_t *pev;                                      //   668
//		char sName;                                           //   777
//		CheckStartMoney(void);  //   696
//		{
//			char *pApersand;                             //   781
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //   761
//		Normalize(const Vector *const this);  //   762
//	}
}

/* <478f7> ../cstrike/dlls/client.cpp:792 */
NOBODY int Q_strlen_(const char *str)
{
//	{
//		int count;                                            //   794
//	}
}

/* <4bbff> ../cstrike/dlls/client.cpp:814 */
NOBODY void Host_Say(edict_t *pEntity, int teamonly)
{
//	{
//		class CBasePlayer *client;                           //   816
//		int j;                                                //   817
//		char *p;                                             //   818
//		char text;                                            //   819
//		char szTemp;                                          //   820
//		const char *cpSay;                                  //   821
//		const char *cpSayTeam;                              //   822
//		const char *pcmd;                                   //   823
//		bool bSenderDead;                                     //   824
//		entvars_t *pev;                                      //   827
//		class CBasePlayer *player;                           //   828
//		const char *placeName;                              //   913
//		char *pszFormat;                                     //   933
//		char *pszConsoleFormat;                              //   934
//		bool consoleUsesPlaceName;                            //   935
//		CMD_ARGV(int i);  //   823
//		CMD_ARGC(void);  //   846
//		CMD_ARGC(void);  //   853
//		Q_strlen(const char *str);  //   910
//		{
//			Place playerPlace;                            //   916
//			const BotPhraseList *placeList;             //   917
//			int i;                                        //   918
//			{
//				const_iterator iter;                  //   921
//				operator++(_List_const_iterator<BotPhrase*> *const this);  //   921
//			}
//		}
//		{
//			char *pAmpersand;                            //  1026
//		}
//		edict(CBaseEntity *const this);  //  1044
//		FNullEnt(const edict_t *pent);  //  1044
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  1085
//		ENTINDEX(edict_t *pEdict);  //  1086
//		CMD_ARGC(void);  //   865
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  1101
//		ENTINDEX(edict_t *pEdict);  //  1102
//		{
//			char *fullText;                              //  1115
//		}
//		{
//			char *temp;                                  //  1129
//			char *szTeam;                                //  1130
//			char *deadText;                              //  1131
//			edict(CBaseEntity *const this);  //  1156
//			edict(CBaseEntity *const this);  //  1156
//		}
//	}
}

/* <4865e> ../cstrike/dlls/client.cpp:1160 */
NOBODY inline void DropSecondary(CBasePlayer *pPlayer)
{
//	{
//		class CBasePlayerWeapon *pWeapon;                    //  1166
//	}
}

/* <473db> ../cstrike/dlls/client.cpp:1182 */
NOBODY void DropPrimary(CBasePlayer *pPlayer)
{
}

/* <483a2> ../cstrike/dlls/client.cpp:1197 */
NOBODY bool CanBuyThis(CBasePlayer *pPlayer, int iWeapon)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  1199
//	}
}

/* <48696> ../cstrike/dlls/client.cpp:1247 */
NOBODY void BuyPistol(CBasePlayer *pPlayer, int iSlot)
{
//	{
//		int iWeapon;                                          //  1249
//		int iWeaponPrice;                                     //  1250
//		const char *pszWeapon;                              //  1251
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  1320
//		DropSecondary(CBasePlayer *pPlayer);  //  1305
//	}
}

/* <487b0> ../cstrike/dlls/client.cpp:1325 */
NOBODY void BuyShotgun(CBasePlayer *pPlayer, int iSlot)
{
//	{
//		int iWeapon;                                          //  1327
//		int iWeaponPrice;                                     //  1328
//		const char *pszWeapon;                              //  1329
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  1373
//		DropPrimary(CBasePlayer *pPlayer);  //  1359
//	}
}

/* <488b5> ../cstrike/dlls/client.cpp:1378 */
NOBODY void BuySubMachineGun(CBasePlayer *pPlayer, int iSlot)
{
//	{
//		int iWeapon;                                          //  1380
//		int iWeaponPrice;                                     //  1381
//		const char *pszWeapon;                              //  1382
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  1445
//		DropPrimary(CBasePlayer *pPlayer);  //  1431
//	}
}

/* <489bb> ../cstrike/dlls/client.cpp:1450 */
NOBODY void BuyWeaponByWeaponID(CBasePlayer *pPlayer, WeaponIdType weaponID)
{
//	{
//		const class WeaponInfoStruct *info;                 //  1463
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  1493
//		DropPrimary(CBasePlayer *pPlayer);  //  1474
//		DropSecondary(CBasePlayer *pPlayer);  //  1478
//	}
}

/* <48adf> ../cstrike/dlls/client.cpp:1498 */
NOBODY void BuyRifle(CBasePlayer *pPlayer, int iSlot)
{
//	{
//		int iWeapon;                                          //  1500
//		int iWeaponPrice;                                     //  1501
//		bool bIsCT;                                           //  1502
//		const char *pszWeapon;                              //  1503
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  1624
//		DropPrimary(CBasePlayer *pPlayer);  //  1610
//	}
}

/* <48bf5> ../cstrike/dlls/client.cpp:1629 */
NOBODY void BuyMachineGun(CBasePlayer *pPlayer, int iSlot)
{
//	{
//		int iWeapon;                                          //  1631
//		int iWeaponPrice;                                     //  1632
//		const char *pszWeapon;                              //  1633
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  1672
//		DropPrimary(CBasePlayer *pPlayer);  //  1658
//	}
}

/* <473f8> ../cstrike/dlls/client.cpp:1677 */
NOBODY void BuyItem(CBasePlayer *pPlayer, int iSlot)
{
//	{
//		int iItem;                                            //  1679
//		int iItemPrice;                                       //  1680
//		const char *pszItem;                                //  1681
//		{
//			int fullArmor;                                //  1743
//			int helmet;                                   //  1744
//			int price;                                    //  1746
//			int enoughMoney;                              //  1746
//		}
//	}
}

/* <48d40> ../cstrike/dlls/client.cpp:1998 */
NOBODY void HandleMenu_ChooseAppearance(CBasePlayer *player, int slot)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  2000
//		class  appearance;                                    //  2007
//		int numSkins;                                         //  2009
//		edict(CBaseEntity *const this);  //  2183
//		entindex(CBaseEntity *const this);  //  2183
//	}
}

/* <48e4b> ../cstrike/dlls/client.cpp:2214 */
NOBODY BOOL HandleMenu_ChooseTeam(CBasePlayer *player, int slot)
{
//	{
//		class CHalfLifeMultiplay *mp;                        //  2216
//		enum TeamName team;                                   //  2217
//		edict_t *pentSpawnSpot;                              //  2218
//		int oldTeam;                                          //  2525
//		char *szOldTeam;                                     //  2540
//		char *szNewTeam;                                     //  2541
//		edict(CBaseEntity *const this);  //  2235
//		edict(CBaseEntity *const this);  //  2323
//		edict(CBaseEntity *const this);  //  2323
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  2331
//		TeamChangeUpdate(CBasePlayer *player,
//				int team_id);  //  2349
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  2336
//		edict(CBaseEntity *const this);  //  2337
//		ENTINDEX(edict_t *pEdict);  //  2337
//		VARS(edict_t *pent);  //  2352
//		Vector(Vector *const this,
//			const Vector &v);  //  2352
//		VARS(edict_t *pent);  //  2352
//		Vector(Vector *const this,
//			const Vector &v);  //  2352
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				edict_t *ed);  //  2355
//		edict(CBaseEntity *const this);  //  2356
//		ENTINDEX(edict_t *pEdict);  //  2356
//		{
//			bool madeRoom;                                //  2402
//		}
//		edict(CBaseEntity *const this);  //  2378
//		{
//			cvar_t humans_join_team;                      //  2435
//			int humanTeam;                                //  2436
//		}
//		{
//			bool isCZero;                                 //  2494
//		}
//		TeamChangeUpdate(CBasePlayer *player,
//				int team_id);  //  2531
//		edict(CBaseEntity *const this);  //  2548
//		edict(CBaseEntity *const this);  //  2548
//		edict(CBaseEntity *const this);  //  2371
//		Vector(Vector *const this,
//			float X,
//			float Y,
//			float Z);  //  2363
//		CheckStartMoney(void);  //  2466
//	}
}

/* <474a0> ../cstrike/dlls/client.cpp:2553 */
NOBODY void Radio1(CBasePlayer *player, int slot)
{
}

/* <474ca> ../cstrike/dlls/client.cpp:2596 */
NOBODY void Radio2(CBasePlayer *player, int slot)
{
}

/* <474f4> ../cstrike/dlls/client.cpp:2639 */
NOBODY void Radio3(CBasePlayer *player, int slot)
{
}

/* <49402> ../cstrike/dlls/client.cpp:2698 */
NOBODY bool BuyGunAmmo(CBasePlayer &player, CBasePlayerItem &weapon, bool bBlinkMoney)
{
//	{
//		int nAmmo;                                            //  2706
//		int cost;                                             //  2719
//		const char *classname;                              //  2720
//		iMaxAmmo1(CBasePlayerItem *const this);  //  2713
//		BlinkAccount(CBasePlayer *player,
//				int numBlinks);  //  2873
//	}
}

/* <4751e> ../cstrike/dlls/client.cpp:2884 */
NOBODY bool BuyAmmo(CBasePlayer *player, int nSlot, bool bBlinkMoney)
{
//	{
//		class CBasePlayerItem *pItem;                        //  2901
//	}
}

/* <4bb4a> ../cstrike/dlls/client.cpp:2933 */
NOBODY CBaseEntity *EntityFromUserID(int userID)
{
//	{
//		class CBaseEntity *pTempEntity;                      //  2935
//		class CBasePlayer *pTempPlayer;                      //  2936
//		edict(CBaseEntity *const this);  //  2945
//		edict(CBaseEntity *const this);  //  2939
//		FNullEnt(const edict_t *pent);  //  2939
//	}
}

/* <4baa5> ../cstrike/dlls/client.cpp:2958 */
NOBODY int CountPlayersInServer(void)
{
//	{
//		int count;                                            //  2960
//		class CBaseEntity *pTempEntity;                      //  2961
//		class CBasePlayer *pTempPlayer;                      //  2962
//		edict(CBaseEntity *const this);  //  2965
//		FNullEnt(const edict_t *pent);  //  2965
//	}
}

/* <4958c> ../cstrike/dlls/client.cpp:2983 */
NOBODY BOOL HandleBuyAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
//	{
//		BOOL bRetVal;                                         //  2985
//		char *pszFailItem;                                   //  2986
//		enum WeaponIdType weaponID;                           //  2988
//		const char *weaponFailName;                         //  2989
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3014
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3030
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3046
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3051
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3056
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3061
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3066
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3071
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3076
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3081
//		{
//			class CHalfLifeMultiplay *mp;                //  2993
//		}
//		BuyAmmo(CBasePlayer *player,
//			int nSlot,
//			bool bBlinkMoney);  //  3020
//		BuyAmmo(CBasePlayer *player,
//			int nSlot,
//			bool bBlinkMoney);  //  3036
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3054
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3049
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3059
//		BuyAmmo(CBasePlayer *player,
//			int nSlot,
//			bool bBlinkMoney);  //  3022
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3074
//		BuyAmmo(CBasePlayer *player,
//			int nSlot,
//			bool bBlinkMoney);  //  3038
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3064
//		BuyItem(CBasePlayer *pPlayer,
//			int iSlot);  //  3069
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3088
//	}
}

/* <49c3e> ../cstrike/dlls/client.cpp:3113 */
NOBODY BOOL HandleRadioAliasCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
//	{
//		BOOL bRetVal;                                         //  3115
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3118
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3123
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3128
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3133
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3138
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3143
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3149
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3154
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3159
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3164
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3169
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3174
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3180
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3185
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3190
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3195
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3200
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3205
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3210
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3215
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3220
//		Radio3(CBasePlayer *player,
//			int slot);  //  3223
//		Radio1(CBasePlayer *player,
//			int slot);  //  3121
//		Radio1(CBasePlayer *player,
//			int slot);  //  3131
//		Radio2(CBasePlayer *player,
//			int slot);  //  3152
//		Radio1(CBasePlayer *player,
//			int slot);  //  3126
//		Radio1(CBasePlayer *player,
//			int slot);  //  3136
//		Radio1(CBasePlayer *player,
//			int slot);  //  3141
//		Radio1(CBasePlayer *player,
//			int slot);  //  3146
//		Radio3(CBasePlayer *player,
//			int slot);  //  3183
//		Radio2(CBasePlayer *player,
//			int slot);  //  3157
//		Radio2(CBasePlayer *player,
//			int slot);  //  3162
//		Radio2(CBasePlayer *player,
//			int slot);  //  3167
//		Radio2(CBasePlayer *player,
//			int slot);  //  3172
//		Radio2(CBasePlayer *player,
//			int slot);  //  3177
//		Radio3(CBasePlayer *player,
//			int slot);  //  3188
//		Radio3(CBasePlayer *player,
//			int slot);  //  3193
//		Radio3(CBasePlayer *player,
//			int slot);  //  3198
//		Radio3(CBasePlayer *player,
//			int slot);  //  3203
//		Radio3(CBasePlayer *player,
//			int slot);  //  3208
//		Radio3(CBasePlayer *player,
//			int slot);  //  3213
//		Radio3(CBasePlayer *player,
//			int slot);  //  3218
//	}
}

void (*pClientCommand)(edict_t *pEntity);

/* <4c6c1> ../cstrike/dlls/client.cpp:3234 */
NOBODY void __declspec(naked) ClientCommand(edict_t *pEntity)
{
	__asm
	{
		jmp pClientCommand
	}
//	{
//		const char *pcmd;                                   //  3236
//		const char *pstr;                                   //  3237
//		class CHalfLifeMultiplay *mp;                        //  3239
//		entvars_t *pev;                                      //  3245
//		class CBasePlayer *player;                           //  3246
//		CMD_ARGV(int i);  //  3236
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3248
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3256
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3264
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3273
//		{
//			int iVoteID;                                  //  3294
//			int iVoteFail;                                //  3295
//			int iNumArgs;                                 //  3296
//			const char *pszArg1;                        //  3297
//			int iVoteLength;                              //  3298
//			class CBaseEntity *pKickEntity;              //  3332
//			class CBasePlayer *pKickPlayer;              //  3342
//			CMD_ARGC(void);  //  3296
//			CMD_ARGV(int i);  //  3297
//			atoi(const char *__nptr);  //  3309
//			CountTeamPlayers(int iTeam);  //  3326
//		}
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3363
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3371
//		{
//			int iFailed;                                  //  3377
//			int iVote;                                    //  3406
//			CMD_ARGC(void);  //  3400
//			CMD_ARGV(int i);  //  3406
//			atoi(const char *__nptr);  //  3406
//		}
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3448
//		{
//			int iTimeRemaining;                           //  3454
//			int iMinutes;                                 //  3458
//			int iSeconds;                                 //  3458
//			char secs;                                    //  3462
//			char *temp;                                  //  3463
//		}
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3488
//		FStrEq(const char *sz1,
//			const char *sz2);  //  3496
//		IsObserver(CBasePlayer *const this);  //  3930
//		atoi(const char *__nptr);  //  3932
//		IsObserver(CBasePlayer *const this);  //  3937
//		{
//			int slot;                                     //  3966
//			atoi(const char *__nptr);  //  3966
//		}
//		{
//			int i;                                        //  4037
//			{
//				class CBasePlayer *pObserver;        //  4039
//				EMIT_SOUND(edict_t *entity,
//						int channel,
//						const char *sample,
//						float volume,
//						float attenuation);  //  4042
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						entvars_t *ent);  //  4043
//			}
//		}
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  4030
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  4031
//		{
//			int i;                                        //  4059
//			{
//				class CBasePlayer *pObserver;        //  4061
//				EMIT_SOUND(edict_t *entity,
//						int channel,
//						const char *sample,
//						float volume,
//						float attenuation);  //  4064
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						entvars_t *ent);  //  4065
//			}
//		}
//		EMIT_SOUND(edict_t *entity,
//				int channel,
//				const char *sample,
//				float volume,
//				float attenuation);  //  4052
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  4053
//		strstr(const char *__haystack,
//			const char *__needle);  //  4114
//		{
//			bool oldval;                                  //  4234
//		}
//		{
//			bool oldval;                                  //  4246
//		}
//		{
//			char command;                                 //  4270
//		}
//		{
//			bool oldval;                                  //  4221
//		}
//		{
//			bool oldval;                                  //  4210
//			{
//				int arg;                              //  4205
//			}
//		}
//		{
//			int slot;                                     //  3996
//			atoi(const char *__nptr);  //  3996
//		}
//		{
//			float val;                                    //  3925
//			atof(const char *__nptr);  //  3925
//			SetObserverAutoDirector(CBasePlayer *const this,
//						bool val);  //  3926
//		}
//		{
//			int mode;                                     //  3901
//			atoi(const char *__nptr);  //  3901
//			IsObserver(CBasePlayer *const this);  //  3903
//			{
//				int gmsgADStop;                       //  3918
//				MESSAGE_BEGIN(int msg_dest,
//						int msg_type,
//						const float *pOrigin,
//						entvars_t *ent);  //  3919
//			}
//		}
//		{
//			int slot;                                     //  3523
//			atoi(const char *__nptr);  //  3523
//		}
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //  3504
//	}
}

/* <4b959> ../cstrike/dlls/client.cpp:4282 */
NOBODY void ClientUserInfoChanged(edict_t *pEntity, char *infobuffer)
{
//	{
//		class CBasePlayer *pPlayer;                          //  4288
//		const char *szBufferName;                           //  4289
//		int iClientIndex;                                     //  4290
//		entindex(CBaseEntity *const this);  //  4290
//		FStrEq(const char *sz1,
//			const char *sz2);  //  4293
//		{
//			char szName;                                  //  4295
//			{
//				char *pPct;                          //  4300
//			}
//			MESSAGE_BEGIN(int msg_dest,
//					int msg_type,
//					const float *pOrigin,
//					edict_t *ed);  //  4331
//		}
//	}
}

/* <4a378> ../cstrike/dlls/client.cpp:4362 */
NOBODY void ServerDeactivate(void)
{
}

/* <4a392> ../cstrike/dlls/client.cpp:4400 */
NOBODY void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
//	{
//		int i;                                                //  4402
//		class CBaseEntity *pClass;                           //  4403
//	}
}

/* <4a404> ../cstrike/dlls/client.cpp:4459 */
NOBODY void PlayerPreThink(edict_t *pEntity)
{
//	{
//		entvars_t *pev;                                      //  4461
//		class CBasePlayer *pPlayer;                          //  4462
//		GET_PRIVATE(edict_t *pent);  //  4462
//	}
}

/* <4a47c> ../cstrike/dlls/client.cpp:4475 */
NOBODY void PlayerPostThink(edict_t *pEntity)
{
	entvars_t *pev = &pEntity->v;
	CBasePlayer *pPlayer = (CBasePlayer *)GET_PRIVATE(pEntity);

	if (pPlayer)
		pPlayer->PostThink();
}

/* <4a4f4> ../cstrike/dlls/client.cpp:4486 */
void ParmsNewLevel(void)
{
	;
}

/* <4a50d> ../cstrike/dlls/client.cpp:4491 */
NOBODY void ParmsChangeLevel(void)
{
//	{
//		SAVERESTOREDATA *pSaveData;                          //  4494
//	}
}

/* <4a548> ../cstrike/dlls/client.cpp:4504 */
NOBODY void StartFrame(void)
{
	if (g_pGameRules)
		g_pGameRules->Think();

	if (g_fGameOver)
		return;

	CLocalNav::Think();
	static cvar_t *skill = NULL;

	if (!skill)
		skill = CVAR_GET_POINTER("skill");

	gpGlobals->teamplay = 1;

	if (skill)
		g_iSkillLevel = skill->value;
	else
		g_iSkillLevel = 0;

	if (TheTutor)
		TheTutor->StartFrame(gpGlobals->time);

	++g_ulFrameCount;

}

/* <4a581> ../cstrike/dlls/client.cpp:4534 */
void ClientPrecache(void)
{
	int i;
	bool isCZero = UTIL_IsGame("czero");

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
	PRECACHE_SOUND("items/flashlight1.wav");
	PRECACHE_SOUND("items/flashlight1.wav");
	PRECACHE_SOUND("common/bodysplat.wav");
	PRECACHE_SOUND("player/pl_pain2.wav");
	PRECACHE_SOUND("player/pl_pain4.wav");
	PRECACHE_SOUND("player/pl_pain5.wav");
	PRECACHE_SOUND("player/pl_pain6.wav");
	PRECACHE_SOUND("player/pl_pain7.wav");

	int numPlayerModels;
	if (isCZero)
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles);
	else
		numPlayerModels = ARRAYSIZE(sPlayerModelFiles) - 2;

	for (i = 0; i < numPlayerModels; i++)
		PRECACHE_MODEL(sPlayerModelFiles[i]);

	for (i = FirstCustomSkin; i <= LastCustomSkin; i++)
	{
		const char *fname = TheBotProfiles->GetCustomSkinFname( i );

		if (!fname)
			break;

		PRECACHE_MODEL((char *)fname);
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
	Vector vMin = Vector(-38, -24, -41);
	Vector vMax = Vector(38, 24, 41);

	for (i = 0; i < numPlayerModels; i++)
		ENGINE_FORCE_UNMODIFIED(force_model_specifybounds, (float *)&vMin, (float *)&vMax, sPlayerModelFiles[i]);

	for (i = FirstCustomSkin; i <= LastCustomSkin; i++)
	{
		const char *fname = TheBotProfiles->GetCustomSkinFname( i );

		if (!fname)
			break;

		ENGINE_FORCE_UNMODIFIED(force_model_specifybounds_if_avail, (float *)&vMin, (float *)&vMax, fname);
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (isCZero)
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

	if (giPrecacheGrunt)
		UTIL_PrecacheOther("enemy_terrorist");

	g_iShadowSprite = PRECACHE_MODEL("sprites/shadow_circle.spr");

	PRECACHE_MODEL("sprites/wall_puff1.spr");
	PRECACHE_MODEL("sprites/wall_puff2.spr");
	PRECACHE_MODEL("sprites/wall_puff3.spr");
	PRECACHE_MODEL("sprites/wall_puff4.spr");
	PRECACHE_MODEL("sprites/black_smoke1.spr");
	PRECACHE_MODEL("sprites/black_smoke2.spr");
	PRECACHE_MODEL("sprites/black_smoke3.spr");
	PRECACHE_MODEL("sprites/black_smoke4.spr");
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

/* <4a6e5> ../cstrike/dlls/client.cpp:4996 */
const char *GetGameDescription(void)
{
	if (UTIL_IsGame("czero"))
		return "Condition Zero";

	return "Counter-Strike";
}

/* <4a703> ../cstrike/dlls/client.cpp:5022 */
void Sys_Error(const char *error_string)
{
	;
}

/* <4a731> ../cstrike/dlls/client.cpp:5039 */
void PlayerCustomization(edict_t *pEntity, customization_t *pCust)
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

/* <4a7b9> ../cstrike/dlls/client.cpp:5079 */
void SpectatorConnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
		pPlayer->SpectatorConnect();
}

/* <4a83d> ../cstrike/dlls/client.cpp:5095 */
void SpectatorDisconnect(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
		pPlayer->SpectatorDisconnect();
}

/* <4a8b5> ../cstrike/dlls/client.cpp:5111 */
void SpectatorThink(edict_t *pEntity)
{
	CBaseSpectator *pPlayer = (CBaseSpectator *)GET_PRIVATE(pEntity);

	if (pPlayer)
		pPlayer->SpectatorThink();
}

/* <4a92d> ../cstrike/dlls/client.cpp:5160 */
void SetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas)
{
	edict_t *pView = pClient;

	// Find the client's PVS
	if (pViewEntity)
	{
		pView = pViewEntity;
	}

	if (pClient->v.flags & FL_PROXY)
	{
		*pvs = NULL;	// the spectator proxy sees
		*pas = NULL;	// and hears everything
		return;
	}

	CBasePlayer *pPlayer = reinterpret_cast< CBasePlayer * >(CBasePlayer::Instance( pClient ));

	if (pPlayer->pev->iuser2 && pPlayer->m_hObserverTarget)
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

/* <4aa75> ../cstrike/dlls/client.cpp:5226 */
NOXREF void ResetPlayerPVS(edict_t *client, int clientnum)
{
	PLAYERPVSSTATUS *pvs = &g_PVSStatus[clientnum];

	memset(pvs, 0, sizeof(*pvs));
	pvs->headnode = client->headnode;
	pvs->num_leafs = client->num_leafs;
	memcpy(pvs->leafnums, client->leafnums, sizeof(pvs->leafnums));
}

/* <4aae8> ../cstrike/dlls/client.cpp:5240 */
NOXREF bool CheckPlayerPVSLeafChanged(edict_t *client, int clientnum)
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

/* <475e3> ../cstrike/dlls/client.cpp:5263 */
NOXREF void MarkEntityInPVS(int clientnum, int entitynum, float time, bool inpvs)
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

/* <47581> ../cstrike/dlls/client.cpp:5275 */
NOXREF bool CheckEntityRecentlyInPVS(int clientnum, int entitynum, float currenttime)
{
	PLAYERPVSSTATUS *pvs;
	ENTITYPVSSTATUS *es;

	pvs = &g_PVSStatus[clientnum];
	es = &pvs->m_Status[entitynum];

	if (es->m_fTimeEnteredPVS && es->m_fTimeEnteredPVS + 1.0 >= currenttime)
		return true;

	return false;
}

/* <4ac57> ../cstrike/dlls/client.cpp:5312 */
int AddToFullPack(struct entity_state_s *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet)
{
	if ((ent->v.effects & EF_NODRAW) == EF_NODRAW && ent != host)
		return 0;

	if (!ent->v.modelindex || !STRING(ent->v.model))
		return 0;

	if ((ent->v.flags & FL_SPECTATOR) == FL_SPECTATOR && ent != host)
		return 0;

	int i;
	int hostnum = ENTINDEX(host) - 1;

	if (CheckPlayerPVSLeafChanged(host, hostnum))
		ResetPlayerPVS(host, hostnum);

	if (ent != host)
	{
		if (!CheckEntityRecentlyInPVS(hostnum, e, gpGlobals->time))
		{
			if (!ENGINE_CHECK_VISIBILITY(ent, pSet))
			{
				MarkEntityInPVS(hostnum, e, 0, false);
				return 0;
			}

			MarkEntityInPVS(hostnum, e, gpGlobals->time, true);
		}
	}

	if ((ent->v.flags & FL_SKIPLOCALHOST) == FL_SKIPLOCALHOST && (hostflags & 1) && ent->v.owner == host)
		return 0;

	if (host->v.groupinfo)
	{
		UTIL_SetGroupTrace(host->v.groupinfo, GROUP_OP_AND);

		if (ent->v.groupinfo)
		{
			if (g_groupop == GROUP_OP_AND)
			{
				if (!(ent->v.groupinfo & host->v.groupinfo))
					return 0;
			}
			else if (g_groupop == GROUP_OP_NAND)
			{
				if (ent->v.groupinfo & host->v.groupinfo)
					return 0;
			}
		}

		UTIL_UnsetGroupTrace();
	}

	memset(state, 0, sizeof(*state));

	state->number = e;
	state->entityType = ENTITY_NORMAL;

	if (ent->v.flags & FL_CUSTOMENTITY)
		state->entityType = ENTITY_BEAM;

	state->animtime = (int)(1000.0 * ent->v.animtime) / 1000.0;

	memcpy(state->origin, ent->v.origin, sizeof(float) * 3);
	memcpy(state->angles, ent->v.angles, sizeof(float) * 3);
	memcpy(state->mins, ent->v.mins, sizeof(float) * 3);
	memcpy(state->maxs, ent->v.maxs, sizeof(float) * 3);
	memcpy(state->startpos, ent->v.startpos, sizeof(float) * 3);
	memcpy(state->endpos, ent->v.endpos, sizeof(float) * 3);

	state->impacttime = ent->v.impacttime;
	state->starttime = ent->v.starttime;
	state->modelindex = ent->v.modelindex;
	state->frame = ent->v.frame;
	state->skin = ent->v.skin;
	state->effects = ent->v.effects;

	if (!player && ent->v.animtime && !ent->v.velocity.x && !ent->v.velocity.y && !ent->v.velocity.z)
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
	state->renderamt = (int)ent->v.renderamt;
	state->renderfx = ent->v.renderfx;
	state->rendercolor.r = (byte)ent->v.rendercolor.x;
	state->rendercolor.g = (byte)ent->v.rendercolor.y;
	state->rendercolor.b = (byte)ent->v.rendercolor.z;

	state->aiment = 0;

	if (ent->v.aiment)
		state->aiment = ENTINDEX(ent->v.aiment);

	state->owner = 0;
	if (ent->v.owner)
	{
		int owner = ENTINDEX(ent->v.owner);
		
		if (owner >= 1 && owner <= gpGlobals->maxClients)
			state->owner = owner;
	}

	if (player)
	{
		memcpy(state->basevelocity, ent->v.basevelocity, sizeof(float) * 3);

		state->weaponmodel = MODEL_INDEX( STRING(ent->v.weaponmodel) );
		state->gaitsequence = ent->v.gaitsequence;

		state->spectator = (ent->v.flags & FL_SPECTATOR) ? TRUE : FALSE;
		state->friction = ent->v.friction;
		state->gravity = ent->v.gravity;
		state->usehull = (ent->v.flags & FL_DUCKING) ? 1 : 0;
		state->health = (int)ent->v.health;
	}
	else
		state->playerclass = ent->v.playerclass;

	state->iuser4 = ent->v.iuser4;
	return 1;
}

// Creates baselines used for network encoding, especially for player data since players are not spawned until connect time.

/* <4aef3> ../cstrike/dlls/client.cpp:5516 */
void CreateBaseline(int player, int eindex, struct entity_state_s *baseline, struct edict_s *entity, int playermodelindex, Vector player_mins, Vector player_maxs)
{
	baseline->origin = entity->v.origin;
	baseline->angles = entity->v.angles;

	baseline->frame = entity->v.frame;
	baseline->skin = (short)entity->v.skin;

	// render information
	baseline->rendermode = (byte)entity->v.rendermode;
	baseline->renderamt = (byte)entity->v.renderamt;
	baseline->rendercolor.r	= (byte)entity->v.rendercolor.x;
	baseline->rendercolor.g	= (byte)entity->v.rendercolor.y;
	baseline->rendercolor.b	= (byte)entity->v.rendercolor.z;
	baseline->renderfx = (byte)entity->v.renderfx;

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

/* <47d8a> ../cstrike/dlls/client.cpp:5586 */
NOXREF void Entity_FieldInit(struct delta_s *pFields)
{
	entity_field_alias[ FIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ORIGIN0 ].name);
	entity_field_alias[ FIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ORIGIN1 ].name);
	entity_field_alias[ FIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ORIGIN2 ].name);
	entity_field_alias[ FIELD_ANGLES0 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ANGLES0 ].name);
	entity_field_alias[ FIELD_ANGLES1 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ANGLES1 ].name);
	entity_field_alias[ FIELD_ANGLES2 ].field = DELTA_FINDFIELD(pFields, entity_field_alias[ FIELD_ANGLES2 ].name);
}

// Callback for sending entity_state_t info over network.

/* <47da7> ../cstrike/dlls/client.cpp:5604 */
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
	localplayer =  (t->number - 1) == ENGINE_CURRENT_PLAYER();

	if (localplayer)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	if (t->impacttime != 0 && t->starttime != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);

		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ANGLES0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ANGLES1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ANGLES2 ].field);
	}
	if (t->movetype == MOVETYPE_FOLLOW && t->aiment != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	else if (t->aiment != f->aiment)
	{
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
}

/* <47cb4> ../cstrike/dlls/client.cpp:5662 */
NOXREF void Player_FieldInit(struct delta_s *pFields)
{
	player_field_alias[ FIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN0 ].name);
	player_field_alias[ FIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN1 ].name);
	player_field_alias[ FIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, player_field_alias[ FIELD_ORIGIN2 ].name);
}

// Callback for sending entity_state_t for players info over network. 

/* <47cd1> ../cstrike/dlls/client.cpp:5676 */
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
	localplayer =  (t->number - 1) == ENGINE_CURRENT_PLAYER();

	if (localplayer)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	if (t->movetype == MOVETYPE_FOLLOW && t->aiment != 0)
	{
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_UNSETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
	else if (t->aiment != f->aiment)
	{
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN0 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN1 ].field);
		DELTA_SETBYINDEX(pFields, entity_field_alias[ FIELD_ORIGIN2 ].field);
	}
}

/* <4afc4> ../cstrike/dlls/client.cpp:5738 */
void Custom_Entity_FieldInit(delta_s *pFields)
{
	custom_entity_field_alias[ CUSTOMFIELD_ORIGIN0 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN0 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ORIGIN1 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN1 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ORIGIN2 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN2 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANGLES0 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES0 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANGLES1 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES1 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANGLES2 ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES2 ].name);
	custom_entity_field_alias[ CUSTOMFIELD_SKIN ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_SKIN ].name);
	custom_entity_field_alias[ CUSTOMFIELD_SEQUENCE ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_SEQUENCE ].name);
	custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].field = DELTA_FINDFIELD(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].name);
}

// Callback for sending entity_state_t info ( for custom entities ) over network.

/* <4aff3> ../cstrike/dlls/client.cpp:5759 */
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
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN0 ].field);
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN1 ].field);
			DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ORIGIN2 ].field);
		}

		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES0 ].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES1 ].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANGLES2 ].field);
	}

	if (beamType != BEAM_ENTS && beamType != BEAM_ENTPOINT)
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_SKIN ].field);
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_SEQUENCE ].field);
	}

	// animtime is compared by rounding first
	// see if we really shouldn't actually send it

	if ((int)f->animtime == (int)t->animtime)
	{
		DELTA_UNSETBYINDEX(pFields, custom_entity_field_alias[ CUSTOMFIELD_ANIMTIME ].field);
	}
}

/* <4b08a> ../cstrike/dlls/client.cpp:5811 */
void RegisterEncoders(void)
{
	DELTA_ADDENCODER("Entity_Encode", Entity_Encode);
	DELTA_ADDENCODER("Custom_Encode", Custom_Encode);
	DELTA_ADDENCODER("Player_Encode", Player_Encode);
}

/* <4b0a4> ../cstrike/dlls/client.cpp:5818 */
int GetWeaponData(edict_s *player, struct weapon_data_s *info)
{
	entvars_t *pev = &player->v;
	CBasePlayer *pl = reinterpret_cast< CBasePlayer * >(CBasePlayer::Instance( pev ));

	memset(info, 0, sizeof(weapon_data_t) * MAX_WEAPONS);

	if (!pl)
		return 1;

	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		CBasePlayerItem *pPlayerItem = pl->m_rgpPlayerItems[i];

		while (pPlayerItem != NULL)
		{
			CBasePlayerWeapon *gun = reinterpret_cast< CBasePlayerWeapon * >(pPlayerItem->GetWeaponPtr());
			
			if (gun && gun->UseDecrement())
			{
				ItemInfo II;
				memset(&II, 0, sizeof(II));
				gun->GetItemInfo(&II);

				if (II.iId >= 0 && II.iId < MAX_WEAPONS)
				{
					weapon_data_t *item = &info[II.iId];

					item->m_iId = II.iId;
					item->m_iClip = gun->m_iClip;
					item->m_flTimeWeaponIdle = max(gun->m_flTimeWeaponIdle, -0.001);
					item->m_flNextPrimaryAttack = max(gun->m_flNextPrimaryAttack, -0.001);
					item->m_flNextSecondaryAttack = max(gun->m_flNextSecondaryAttack, -0.001);
					item->m_flNextReload = max(gun->m_flNextReload, -0.001);
					item->m_fInReload = gun->m_fInReload;
					item->m_fInSpecialReload = gun->m_fInSpecialReload;
					item->m_fInZoom = gun->m_iShotsFired;
					item->m_fAimedDamage = gun->m_flLastFire;
					item->m_iWeaponState = gun->m_iWeaponState;
					item->fuser2 = gun->m_flStartThrow;
					item->fuser3 = gun->m_flReleaseThrow;
					item->iuser1 = gun->m_iSwing;
				}
			}

			pPlayerItem = pPlayerItem->m_pNext;
		}
	}

	return 1;
}

/* <4b1fd> ../cstrike/dlls/client.cpp:5889 */
void UpdateClientData(const struct edict_s *ent, int sendweapons, struct clientdata_s *cd)
{
	if (!ent || !ent->pvPrivateData)
		return;

	entvars_t *pevOrg = NULL;
	entvars_t *pev = (entvars_t *)&ent->v;
	CBasePlayer *pl = reinterpret_cast< CBasePlayer * >(CBasePlayer::Instance( pev ));

	if (pl->pev->iuser1 == OBS_IN_EYE && pl->m_hObserverTarget)
	{
		pevOrg = pev;
		pev = pl->m_hObserverTarget->pev;
		pl = reinterpret_cast< CBasePlayer * >(CBasePlayer::Instance( pev ));
	}

	cd->flags = pev->flags;
	cd->health = pev->health;
	cd->viewmodel = MODEL_INDEX( STRING(pev->viewmodel) );
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
	cd->waterjumptime = (int)pev->teleport_time;

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

	if (sendweapons && pl != NULL)
	{
		cd->ammo_shells = pl->ammo_buckshot;
		cd->ammo_nails = pl->ammo_9mm;
		cd->ammo_cells = pl->ammo_556nato;
		cd->ammo_rockets = pl->ammo_556natobox;
		cd->vuser2.x = pl->ammo_762nato;
		cd->vuser2.y = pl->ammo_45acp;
		cd->vuser2.z = pl->ammo_50ae;
		cd->vuser3.x = pl->ammo_338mag;
		cd->vuser3.y = pl->ammo_57mm;
		cd->vuser3.z = pl->ammo_357sig;
		cd->m_flNextAttack = pl->m_flNextAttack;

		int iUser3 = 0;
		if (pl->m_bCanShoot && !pl->m_bIsDefusing)
			iUser3 |= DATA_IUSER3_CANSHOOT;

		if (g_pGameRules->IsFreezePeriod())
			iUser3 |= DATA_IUSER3_FREEZETIMEOVER;
		else
			iUser3 &= ~DATA_IUSER3_FREEZETIMEOVER;

		if (pl->m_signals.GetState() & SIGNAL_BOMB)
			iUser3 |= DATA_IUSER3_INBOMBZONE;
		else
			iUser3 &= ~DATA_IUSER3_INBOMBZONE;

		if (pl->HasShield())
			iUser3 |= DATA_IUSER3_HOLDINGSHIELD;
		else
			iUser3 &= ~DATA_IUSER3_HOLDINGSHIELD;

		if (!pl->pev->iuser1 && !pevOrg)
			cd->iuser3 = iUser3;

		if (pl->m_pActiveItem != NULL)
		{
			ItemInfo II;
			memset(&II, 0, sizeof(II));

			CBasePlayerWeapon *gun = reinterpret_cast< CBasePlayerWeapon * >(pl->m_pActiveItem->GetWeaponPtr());

			if (gun != NULL && gun->UseDecrement() && gun->GetItemInfo(&II))
			{
				cd->m_iId = II.iId;

				if ((unsigned int)gun->m_iPrimaryAmmoType < MAX_AMMO_TYPES)
				{
					cd->vuser4.x = gun->m_iPrimaryAmmoType;
					cd->vuser4.y = pl->m_rgAmmo[ gun->m_iPrimaryAmmoType ];
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

/* <4b3ee> ../cstrike/dlls/client.cpp:6050 */
void CmdStart(const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed)
{
	entvars_t *pev = (entvars_t *)&player->v;
	CBasePlayer *pl = reinterpret_cast< CBasePlayer * >(CBasePlayer::Instance( pev ));

	if (!pl)
		return;

	if (pl->pev->groupinfo)
		UTIL_SetGroupTrace(pl->pev->groupinfo, GROUP_OP_AND);

	pl->random_seed = random_seed;
}

/* <4b4eb> ../cstrike/dlls/client.cpp:6074 */
void CmdEnd(const edict_t *player)
{
	entvars_t *pev = (entvars_t *)&player->v;
	CBasePlayer *pl = reinterpret_cast< CBasePlayer * >(CBasePlayer::Instance( pev ));

	if (!pl)
		return;

	if (pl->pev->groupinfo)
		UTIL_UnsetGroupTrace();

	if (pev->flags & FL_DUCKING)
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
}

/* <4b644> ../cstrike/dlls/client.cpp:6101 */
int ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
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

/* <4b6c2> ../cstrike/dlls/client.cpp:6122 */
int GetHullBounds(int hullnumber, float *mins, float *maxs)
{
	return hullnumber < 3;
}

// Create pseudo-baselines for items that aren't placed in the map at spawn time, but which are likely
// to be created during play ( e.g., grenades, ammo packs, projectiles, corpses, etc. )

/* <4b733> ../cstrike/dlls/client.cpp:6156 */
void CreateInstancedBaselines(void)
{
	int iret = 0;
	entity_state_t state;

	memset(&state, 0, sizeof( state ));

	// Create any additional baselines here for things like grendates, etc.
	// iret = ENGINE_INSTANCE_BASELINE( pc->pev->classname, &state );

	// Destroy objects.
	// UTIL_Remove( pc );
}

/* <4b77c> ../cstrike/dlls/client.cpp:6179 */
int InconsistentFile(const edict_t *player, const char *filename, char *disconnect_message)
{
	// Server doesn't care?
	if (CVAR_GET_FLOAT( "mp_consistency" ) != 1)
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

/* <4b7cf> ../cstrike/dlls/client.cpp:6204 */
int AllowLagCompensation(void)
{
	return 1;
}
