#include "precompiled.h"

edict_t *g_pBodyQueueHead;
CGlobalState gGlobalState;

DLL_DECALLIST gDecals[] =
{
	DEFINE_DECAL("{shot1"),		// DECAL_GUNSHOT1
	DEFINE_DECAL("{shot2"),		// DECAL_GUNSHOT2
	DEFINE_DECAL("{shot3"),		// DECAL_GUNSHOT3
	DEFINE_DECAL("{shot4"),		// DECAL_GUNSHOT4
	DEFINE_DECAL("{shot5"),		// DECAL_GUNSHOT5
	DEFINE_DECAL("{lambda01"),	// DECAL_LAMBDA1
	DEFINE_DECAL("{lambda02"),	// DECAL_LAMBDA2
	DEFINE_DECAL("{lambda03"),	// DECAL_LAMBDA3
	DEFINE_DECAL("{lambda04"),	// DECAL_LAMBDA4
	DEFINE_DECAL("{lambda05"),	// DECAL_LAMBDA5
	DEFINE_DECAL("{lambda06"),	// DECAL_LAMBDA6
	DEFINE_DECAL("{scorch1"),	// DECAL_SCORCH1
	DEFINE_DECAL("{scorch2"),	// DECAL_SCORCH2
	DEFINE_DECAL("{blood1"),	// DECAL_BLOOD1
	DEFINE_DECAL("{blood2"),	// DECAL_BLOOD2
	DEFINE_DECAL("{blood3"),	// DECAL_BLOOD3
	DEFINE_DECAL("{blood4"),	// DECAL_BLOOD4
	DEFINE_DECAL("{blood5"),	// DECAL_BLOOD5
	DEFINE_DECAL("{blood6"),	// DECAL_BLOOD6
	DEFINE_DECAL("{yblood1"),	// DECAL_YBLOOD1
	DEFINE_DECAL("{yblood2"),	// DECAL_YBLOOD2
	DEFINE_DECAL("{yblood3"),	// DECAL_YBLOOD3
	DEFINE_DECAL("{yblood4"),	// DECAL_YBLOOD4
	DEFINE_DECAL("{yblood5"),	// DECAL_YBLOOD5
	DEFINE_DECAL("{yblood6"),	// DECAL_YBLOOD6
	DEFINE_DECAL("{break1"),	// DECAL_GLASSBREAK1
	DEFINE_DECAL("{break2"),	// DECAL_GLASSBREAK2
	DEFINE_DECAL("{break3"),	// DECAL_GLASSBREAK3
	DEFINE_DECAL("{bigshot1"),	// DECAL_BIGSHOT1
	DEFINE_DECAL("{bigshot2"),	// DECAL_BIGSHOT2
	DEFINE_DECAL("{bigshot3"),	// DECAL_BIGSHOT3
	DEFINE_DECAL("{bigshot4"),	// DECAL_BIGSHOT4
	DEFINE_DECAL("{bigshot5"),	// DECAL_BIGSHOT5
	DEFINE_DECAL("{spit1"),		// DECAL_SPIT1
	DEFINE_DECAL("{spit2"),		// DECAL_SPIT2
	DEFINE_DECAL("{bproof1"),	// DECAL_BPROOF1
	DEFINE_DECAL("{gargstomp"),	// DECAL_GARGSTOMP1,	// Gargantua stomp crack
	DEFINE_DECAL("{smscorch1"),	// DECAL_SMALLSCORCH1,	// Small scorch mark
	DEFINE_DECAL("{smscorch2"),	// DECAL_SMALLSCORCH2,	// Small scorch mark
	DEFINE_DECAL("{smscorch3"),	// DECAL_SMALLSCORCH3,	// Small scorch mark
	DEFINE_DECAL("{mommablob"),	// DECAL_MOMMABIRTH		// BM Birth spray
	DEFINE_DECAL("{mommablob"),	// DECAL_MOMMASPLAT		// BM Mortar spray?? need decal*/
};

char g_szMapBriefingText[512];

#define SF_DECAL_NOTINDEATHMATCH BIT(11)

class CDecal: public CBaseEntity
{
public:
	virtual void Spawn();
	virtual void KeyValue(KeyValueData *pkvd);

public:
	void EXPORT StaticDecal();
	void EXPORT TriggerDecal(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
};

LINK_ENTITY_TO_CLASS(infodecal, CDecal, CCSDecal)

void CDecal::Spawn()
{
	if (pev->skin < 0 || (gpGlobals->deathmatch != 0.0f && (pev->spawnflags & SF_DECAL_NOTINDEATHMATCH)))
	{
		REMOVE_ENTITY(ENT(pev));
		return;
	}

	if (FStringNull(pev->targetname))
	{
		SetThink(&CDecal::StaticDecal);

		// if there's no targetname, the decal will spray itself on as soon as the world is done spawning.
		pev->nextthink = gpGlobals->time;
	}
	else
	{
		// if there IS a targetname, the decal sprays itself on when it is triggered.
		SetThink(&CBaseEntity::SUB_DoNothing);
		SetUse(&CDecal::TriggerDecal);
	}
}

void CDecal::TriggerDecal(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	// this is set up as a USE function for infodecals that have targetnames, so that the
	// decal doesn't get applied until it is fired. (usually by a scripted sequence)
	TraceResult trace;
	int entityIndex;

	UTIL_TraceLine(pev->origin - Vector(5, 5, 5), pev->origin + Vector(5, 5, 5), ignore_monsters, ENT(pev), &trace);

	MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
		WRITE_BYTE(TE_BSPDECAL);
		WRITE_COORD(pev->origin.x);
		WRITE_COORD(pev->origin.y);
		WRITE_COORD(pev->origin.z);
		WRITE_SHORT(int(pev->skin));
		entityIndex = (short)ENTINDEX(trace.pHit);
		WRITE_SHORT(entityIndex);
		if (entityIndex)
		{
			WRITE_SHORT(int(VARS(trace.pHit)->modelindex));
		}
	MESSAGE_END();

	SetThink(&CDecal::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CDecal::StaticDecal()
{
	TraceResult trace;
	int entityIndex, modelIndex;

	UTIL_TraceLine(pev->origin - Vector(5, 5, 5), pev->origin + Vector(5, 5, 5), ignore_monsters, ENT(pev), &trace);

	entityIndex = (short)ENTINDEX(trace.pHit);

	if (entityIndex)
		modelIndex = VARS(trace.pHit)->modelindex;
	else
		modelIndex = 0;

	STATIC_DECAL(pev->origin, pev->skin, entityIndex, modelIndex);
	SUB_Remove();
}

void CDecal::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "texture"))
	{
		pev->skin = DECAL_INDEX(pkvd->szValue);

		// Found
		if (pev->skin >= 0)
			return;

		ALERT(at_console, "Can't find decal %s\n", pkvd->szValue);
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}

// Body queue class here.... It's really just CBaseEntity
class CCorpse: public CBaseEntity
{
public:
	virtual int ObjectCaps() { return FCAP_DONT_SAVE; }
};

LINK_ENTITY_TO_CLASS(bodyque, CCorpse, CCSCorpse)

static void InitBodyQue()
{
	g_pBodyQueueHead = nullptr;
}

// make a body que entry for the given ent so the ent can be respawned elsewhere
// GLOBALS ASSUMED SET:  g_eoBodyQueueHeadstion
void CopyToBodyQue(entvars_t *pev)
{
#if 0
	if (pev->effects & EF_NODRAW)
		return;

	entvars_t *pevHead = VARS(g_pBodyQueueHead);

	pevHead->angles = pev->angles;
	pevHead->model = pev->model;
	pevHead->modelindex = pev->modelindex;
	pevHead->frame = pev->frame;
	pevHead->colormap = pev->colormap;
	pevHead->movetype = MOVETYPE_TOSS;
	pevHead->velocity = pev->velocity;
	pevHead->flags = 0;
	pevHead->deadflag = pev->deadflag;
	pevHead->renderfx = kRenderFxDeadPlayer;
	pevHead->renderamt = ENTINDEX(ENT(pev));

	pevHead->effects = pev->effects | EF_NOINTERP;

	pevHead->sequence = pev->sequence;
	pevHead->animtime = pev->animtime;

	UTIL_SetOrigin(pevHead, pev->origin);
	UTIL_SetSize(pevHead, pev->mins, pev->maxs);

	g_pBodyQueueHead = pevHead->owner;
#endif
}

void ClearBodyQue()
{
	;
}

LINK_ENTITY_TO_CLASS(worldspawn, CWorld, CCSWorld)

void CWorld::Spawn()
{
#ifdef REGAMEDLL_FIXES
	static char szMapBriefingFile[64] = "";

	EmptyEntityHashTable();
	Precache();

	g_szMapBriefingText[0] = '\0';
	Q_sprintf(szMapBriefingFile, "maps/%s.txt", STRING(gpGlobals->mapname));

	int flength = 0;
	char *pFile = (char *)LOAD_FILE_FOR_ME(szMapBriefingFile, &flength);

	if (pFile && flength)
	{
		Q_strncpy(g_szMapBriefingText, pFile, ARRAYSIZE(g_szMapBriefingText) - 2);
		g_szMapBriefingText[ARRAYSIZE(g_szMapBriefingText) - 2] = '\0';

		PRECACHE_GENERIC(szMapBriefingFile);
	}
	else
	{
		pFile = (char *)LOAD_FILE_FOR_ME("maps/default.txt", &flength);
		if (pFile && flength)
		{
			Q_strncpy(g_szMapBriefingText, pFile, ARRAYSIZE(g_szMapBriefingText) - 2);
			g_szMapBriefingText[ARRAYSIZE(g_szMapBriefingText) - 2] = '\0';

			PRECACHE_GENERIC("maps/default.txt");
		}
	}

	if (pFile)
	{
		FREE_FILE(pFile);
	}

#else
	EmptyEntityHashTable();
	Precache();

	g_szMapBriefingText[0] = '\0';

	int flength = 0;
	char *pFile = (char *)LOAD_FILE_FOR_ME(UTIL_VarArgs("maps/%s.txt", STRING(gpGlobals->mapname)), &flength);

	if (pFile && flength)
	{
		Q_strncpy(g_szMapBriefingText, pFile, ARRAYSIZE(g_szMapBriefingText) - 2);
		PRECACHE_GENERIC(UTIL_VarArgs("maps/%s.txt", STRING(gpGlobals->mapname)));
		FREE_FILE(pFile);
	}
	else
	{
		pFile = (char *)LOAD_FILE_FOR_ME(UTIL_VarArgs("maps/default.txt"), &flength);

		if (pFile && flength)
		{
			Q_strncpy(g_szMapBriefingText, pFile, ARRAYSIZE(g_szMapBriefingText) - 2);
			PRECACHE_GENERIC(UTIL_VarArgs("maps/default.txt"));
			FREE_FILE(pFile);
		}
	}
#endif
}

void CWorld::Precache()
{
	g_pLastSpawn = nullptr;
	g_pLastCTSpawn = nullptr;
	g_pLastTerroristSpawn = nullptr;

	CVAR_SET_STRING("sv_gravity", "800");
	CVAR_SET_STRING("sv_maxspeed", "900");
	CVAR_SET_STRING("sv_stepsize", "18");

	// clear DSP
	CVAR_SET_STRING("room_type", "0");

	// Set up game rules
	if (g_pGameRules)
	{
		delete g_pGameRules;
	}

	g_pGameRules = InstallGameRules();

	// NOTE: What is the essence of soundent in CS 1.6? I think this is for NPC monsters - s1lent
#ifndef REGAMEDLL_FIXES
	// UNDONE why is there so much Spawn code in the Precache function? I'll just keep it here

	// LATER - do we want a sound ent in deathmatch? (sjb)
	//pSoundEnt = CBaseEntity::Create("soundent", g_vecZero, g_vecZero, edict());
	pSoundEnt = GetClassPtr<CCSSoundEnt>((CSoundEnt *)nullptr);

	if (pSoundEnt == nullptr)
	{
		ALERT(at_console, "**COULD NOT CREATE SOUNDENT**\n");
	}
	else
	{
		pSoundEnt->Spawn();
	}
#endif
	InitBodyQue();

	// init sentence group playback stuff from sentences.txt.
	// ok to call this multiple times, calls after first are ignored.
	SENTENCEG_Init();

	// init texture type array from materials.txt
	TEXTURETYPE_Init();

	// the area based ambient sounds MUST be the first precache_sounds
	// player precaches
	// get weapon precaches

	WeaponsPrecache();
	ClientPrecache();
	BotPrecache();

	// sounds used from C physics code
	// clears sound channels
	PRECACHE_SOUND("common/null.wav");

	// temporary sound for respawning weapons.
	PRECACHE_SOUND("items/suitchargeok1.wav");

	// player picks up a gun.
	PRECACHE_SOUND("items/gunpickup2.wav");

	// dead bodies hitting the ground (animation events)
	PRECACHE_SOUND("common/bodydrop3.wav");
	PRECACHE_SOUND("common/bodydrop4.wav");

	g_Language = int(CVAR_GET_FLOAT("sv_language"));
	if (g_Language == LANGUAGE_GERMAN)
	{
		PRECACHE_MODEL("models/germangibs.mdl");
	}
	else
	{
		PRECACHE_MODEL("models/hgibs.mdl");
		PRECACHE_MODEL("models/agibs.mdl");
	}

	PRECACHE_SOUND("weapons/ric1.wav");
	PRECACHE_SOUND("weapons/ric2.wav");
	PRECACHE_SOUND("weapons/ric3.wav");
	PRECACHE_SOUND("weapons/ric4.wav");
	PRECACHE_SOUND("weapons/ric5.wav");

	PRECACHE_SOUND("weapons/ric_metal-1.wav");
	PRECACHE_SOUND("weapons/ric_metal-2.wav");
	PRECACHE_SOUND("weapons/ric_conc-1.wav");
	PRECACHE_SOUND("weapons/ric_conc-2.wav");

	// Setup light animation tables. 'a' is total darkness, 'z' is maxbright.

	// 0 normal
	LIGHT_STYLE(0, "m");

	// 1 FLICKER (first variety)
	LIGHT_STYLE(1, "mmnmmommommnonmmonqnmmo");

	// 2 SLOW STRONG PULSE
	LIGHT_STYLE(2, "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba");

	// 3 CANDLE (first variety)
	LIGHT_STYLE(3, "mmmmmaaaaammmmmaaaaaabcdefgabcdefg");

	// 4 FAST STROBE
	LIGHT_STYLE(4, "mamamamamama");

	// 5 GENTLE PULSE 1
	LIGHT_STYLE(5, "jklmnopqrstuvwxyzyxwvutsrqponmlkj");

	// 6 FLICKER (second variety)
	LIGHT_STYLE(6, "nmonqnmomnmomomno");

	// 7 CANDLE (second variety)
	LIGHT_STYLE(7, "mmmaaaabcdefgmmmmaaaammmaamm");

	// 8 CANDLE (third variety)
	LIGHT_STYLE(8, "mmmaaammmaaammmabcdefaaaammmmabcdefmmmaaaa");

	// 9 SLOW STROBE (fourth variety)
	LIGHT_STYLE(9, "aaaaaaaazzzzzzzz");

	// 10 FLUORESCENT FLICKER
	LIGHT_STYLE(10, "mmamammmmammamamaaamammma");

	// 11 SLOW PULSE NOT FADE TO BLACK
	LIGHT_STYLE(11, "abcdefghijklmnopqrrqponmlkjihgfedcba");

	// 12 UNDERWATER LIGHT MUTATION
	// this light only distorts the lightmap - no contribution
	// is made to the brightness of affected surfaces
	LIGHT_STYLE(12, "mmnnmmnnnmmnn");

	// styles 32-62 are assigned by the light program for switchable lights
	// 63 testing
	LIGHT_STYLE(63, "a");

	for (int i = 0; i < ARRAYSIZE(gDecals); i++)
		gDecals[i].index = DECAL_INDEX(gDecals[i].name);

	if (pev->speed > 0)
		CVAR_SET_FLOAT("sv_zmax", pev->speed);
	else
		CVAR_SET_FLOAT("sv_zmax", 4096);

	if (pev->netname)
	{
		ALERT(at_aiconsole, "Chapter title: %s\n", STRING(pev->netname));

		CBaseEntity *pEntity = CBaseEntity::Create("env_message", g_vecZero, g_vecZero, nullptr);
		if (pEntity)
		{
			pEntity->SetThink(&CBaseEntity::SUB_CallUseToggle);
			pEntity->pev->message = pev->netname;
			pev->netname = 0;
			pEntity->pev->nextthink = gpGlobals->time + 0.3f;
			pEntity->pev->spawnflags = SF_MESSAGE_ONCE;
		}
	}

#ifdef REGAMEDLL_FIXES
	if (!IS_DEDICATED_SERVER())
#endif
	{
		// NOTE: cvar v_dark refers for the client side
		if (pev->spawnflags & SF_WORLD_DARK)
			CVAR_SET_FLOAT("v_dark", 1);
		else
			CVAR_SET_FLOAT("v_dark", 0);
	}

	if (pev->spawnflags & SF_WORLD_TITLE)
	{
		// display the game title if this key is set
		gDisplayTitle = TRUE;
	}
	else
		gDisplayTitle = FALSE;
}

void CWorld::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "skyname"))
	{
		CVAR_SET_STRING("sv_skyname", pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sounds"))
	{
		gpGlobals->cdAudioTrack = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "WaveHeight"))
	{
		pev->scale = Q_atof(pkvd->szValue) * 0.125f;
		CVAR_SET_FLOAT("sv_wateramp", pev->scale);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "MaxRange"))
	{
		pev->speed = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "chaptertitle"))
	{
		pev->netname = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "startdark"))
	{
		int flag = Q_atoi(pkvd->szValue);
		if (flag)
		{
			pev->spawnflags |= SF_WORLD_DARK;
		}
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "newunit"))
	{
		if (Q_atoi(pkvd->szValue))
			CVAR_SET_FLOAT("sv_newunit", 1.0f);

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "gametitle"))
	{
		if (Q_atoi(pkvd->szValue))
			pev->spawnflags |= SF_WORLD_TITLE;

		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "mapteams"))
	{
		pev->team = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "defaultteam"))
	{
		if (Q_atoi(pkvd->szValue))
			pev->spawnflags |= SF_WORLD_FORCETEAM;

		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseEntity::KeyValue(pkvd);
	}
}
