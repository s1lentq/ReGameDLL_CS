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

#include "precompiled.h"

BOOL gInitHUD = TRUE;

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
	DEFINE_ARRAY(CBasePlayer, m_rgSuitPlayList, FIELD_INTEGER, MAX_SUIT_PLAYLIST),
	DEFINE_FIELD(CBasePlayer, m_iSuitPlayNext, FIELD_INTEGER),
	DEFINE_ARRAY(CBasePlayer, m_rgiSuitNoRepeat, FIELD_INTEGER, MAX_SUIT_NOREPEAT),
	DEFINE_ARRAY(CBasePlayer, m_rgflSuitNoRepeatTime, FIELD_TIME, MAX_SUIT_NOREPEAT),
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

const char *CDeadHEV::m_szPoses[] =
{
	"deadback",
	"deadsitting",
	"deadstomach",
	"deadtable"
};

LINK_ENTITY_TO_CLASS(player, CBasePlayer, CCSPlayer)

#ifdef REGAMEDLL_API
void CBasePlayer::OnCreate()
{
	;
}

void CBasePlayer::OnDestroy()
{
	if (m_rebuyString)
	{
		delete[] m_rebuyString;
		m_rebuyString = nullptr;
	}
	m_hintMessageQueue.Reset();
}
#endif

void CBasePlayer::SendItemStatus()
{
	int itemStatus = 0;
	if (m_bHasNightVision)
		itemStatus |= ITEM_STATUS_NIGHTVISION;

	if (m_bHasDefuser)
		itemStatus |= ITEM_STATUS_DEFUSER;

	MESSAGE_BEGIN(MSG_ONE, gmsgItemStatus, nullptr, pev);
		WRITE_BYTE(itemStatus);
	MESSAGE_END();
}

const char *GetCSModelName(int item_id)
{
	const char *modelName = nullptr;
	switch (item_id)
	{
	case WEAPON_P228:         modelName = "models/w_p228.mdl"; break;
	case WEAPON_SCOUT:        modelName = "models/w_scout.mdl"; break;
	case WEAPON_HEGRENADE:    modelName = "models/w_hegrenade.mdl"; break;
	case WEAPON_XM1014:       modelName = "models/w_xm1014.mdl"; break;
	case WEAPON_C4:           modelName = "models/w_backpack.mdl"; break;
	case WEAPON_MAC10:        modelName = "models/w_mac10.mdl"; break;
	case WEAPON_AUG:          modelName = "models/w_aug.mdl"; break;
	case WEAPON_SMOKEGRENADE: modelName = "models/w_smokegrenade.mdl"; break;
	case WEAPON_ELITE:        modelName = "models/w_elite.mdl"; break;
	case WEAPON_FIVESEVEN:    modelName = "models/w_fiveseven.mdl"; break;
	case WEAPON_UMP45:        modelName = "models/w_ump45.mdl"; break;
	case WEAPON_SG550:        modelName = "models/w_sg550.mdl"; break;
	case WEAPON_GALIL:        modelName = "models/w_galil.mdl"; break;
	case WEAPON_FAMAS:        modelName = "models/w_famas.mdl"; break;
	case WEAPON_USP:          modelName = "models/w_usp.mdl"; break;
	case WEAPON_GLOCK18:      modelName = "models/w_glock18.mdl"; break;
	case WEAPON_AWP:          modelName = "models/w_awp.mdl"; break;
	case WEAPON_MP5N:         modelName = "models/w_mp5.mdl"; break;
	case WEAPON_M249:         modelName = "models/w_m249.mdl"; break;
	case WEAPON_M3:           modelName = "models/w_m3.mdl"; break;
	case WEAPON_M4A1:         modelName = "models/w_m4a1.mdl"; break;
	case WEAPON_TMP:          modelName = "models/w_tmp.mdl"; break;
	case WEAPON_G3SG1:        modelName = "models/w_g3sg1.mdl"; break;
	case WEAPON_FLASHBANG:    modelName = "models/w_flashbang.mdl"; break;
	case WEAPON_DEAGLE:       modelName = "models/w_deagle.mdl"; break;
	case WEAPON_SG552:        modelName = "models/w_sg552.mdl"; break;
	case WEAPON_AK47:         modelName = "models/w_ak47.mdl"; break;
	case WEAPON_KNIFE:        modelName = "models/w_knife.mdl"; break;
	case WEAPON_P90:          modelName = "models/w_p90.mdl"; break;
	case WEAPON_SHIELDGUN:    modelName = "models/w_shield.mdl"; break;
	default:
		ALERT(at_console, "CBasePlayer::PackDeadPlayerItems(): Unhandled item- not creating weaponbox\n");
	}

	return modelName;
}

LINK_HOOK_CLASS_CHAIN(bool, CBasePlayer, SetClientUserInfoName, (char *infobuffer, char *szNewName), infobuffer, szNewName)

bool EXT_FUNC CBasePlayer::__API_HOOK(SetClientUserInfoName)(char *infobuffer, char *szNewName)
{
	int nClientIndex = entindex();

#ifdef REGAMEDLL_FIXES
	if (IsProxy())
	{
		SET_CLIENT_KEY_VALUE(nClientIndex, infobuffer, "name", szNewName);
		return true;
	}
#endif

	if (pev->deadflag != DEAD_NO)
	{
		m_bHasChangedName = true;
		Q_snprintf(m_szNewName, sizeof(m_szNewName), "%s", szNewName);
		ClientPrint(pev, HUD_PRINTTALK, "#Name_change_at_respawn");
		return false;
	}

	// Set the name
	SET_CLIENT_KEY_VALUE(nClientIndex, infobuffer, "name", szNewName);

	MESSAGE_BEGIN(MSG_BROADCAST, gmsgSayText);
		WRITE_BYTE(nClientIndex);
		WRITE_STRING("#Cstrike_Name_Change");
		WRITE_STRING(STRING(pev->netname));
		WRITE_STRING(szNewName);
	MESSAGE_END();

	UTIL_LogPrintf("\"%s<%i><%s><%s>\" changed name to \"%s\"\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()), GetTeam(m_iTeam), szNewName);
	return true;
}

void EXT_FUNC CBasePlayer::SetClientUserInfoModel_api(char *infobuffer, char *szNewModel)
{
	SET_CLIENT_KEY_VALUE(entindex(), infobuffer, "model", szNewModel);
}

void CBasePlayer::SetClientUserInfoModel(char *infobuffer, char *szNewModel)
{
	if (szNewModel == nullptr)
		return;

	if (Q_strcmp(GET_KEY_VALUE(infobuffer, "model"), szNewModel) != 0)
	{
		g_ReGameHookchains.m_CBasePlayer_SetClientUserInfoModel.callChain(&CBasePlayer::SetClientUserInfoModel_api, this, infobuffer, szNewModel);
	}
}

void CBasePlayer::SetPlayerModel(BOOL HasC4)
{
	char *infobuffer = GET_INFO_BUFFER(edict());
	char *model;

#ifdef REGAMEDLL_ADD
	auto modelEx = CSPlayer()->m_szModel;
	if (modelEx[0] != '\0') {
		model = modelEx;
	} else
#endif
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
			if (AreRunningCZero())
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
			if (AreRunningCZero())
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

	SetClientUserInfoModel(infobuffer, model);
}

CBasePlayer *CBasePlayer::GetNextRadioRecipient(CBasePlayer *pStartPlayer)
{
	CBaseEntity *pEntity = static_cast<CBaseEntity *>(pStartPlayer);
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		bool bSend = false;
		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (pEntity->IsPlayer())
		{
			if (pEntity->IsDormant())
				continue;

			if (pPlayer && pPlayer->m_iTeam == m_iTeam)
				bSend = true;
		}
		else if (pPlayer)
		{
			int iSpecMode = GetObserverMode();
			if (iSpecMode != OBS_CHASE_LOCKED && iSpecMode != OBS_CHASE_FREE && iSpecMode != OBS_IN_EYE)
				continue;

			if (!FNullEnt(m_hObserverTarget))
				continue;

			CBasePlayer *pTarget = CBasePlayer::Instance(pPlayer->m_hObserverTarget->pev);
			if (!pTarget || pTarget->IsDormant())
				continue;

			if (pTarget->m_iTeam == m_iTeam)
			{
				bSend = true;
			}
		}

		if (bSend)
		{
			return pPlayer;
		}
	}

	return nullptr;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, Radio, (const char *msg_id, const char *msg_verbose, short pitch, bool showIcon), msg_id, msg_verbose, pitch, showIcon)

void EXT_FUNC CBasePlayer::__API_HOOK(Radio)(const char *msg_id, const char *msg_verbose, short pitch, bool showIcon)
{
	// Spectators don't say radio messages.
	if (!IsPlayer())
		return;

	// Neither do dead guys.
	if (pev->deadflag != DEAD_NO && !IsBot())
		return;

	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (pEntity->IsDormant())
			continue;

		bool bSend = false;
		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (!pPlayer)
			continue;

		// ignorerad command
		if (pPlayer->m_bIgnoreRadio)
			continue;

		// are we a regular player? (not spectator)
		if (pPlayer->IsPlayer())
		{
			if (pPlayer->IsDormant())
				continue;

			// is this player on our team? (even dead players hear our radio calls)
			if (g_pGameRules->PlayerRelationship(this, pPlayer) == GR_TEAMMATE)
				bSend = true;
		}
		// this means we're a spectator
		else
		{
			// do this when spectator mode is in
			int iSpecMode = pPlayer->GetObserverMode();
			if (iSpecMode != OBS_CHASE_LOCKED && iSpecMode != OBS_CHASE_FREE && iSpecMode != OBS_IN_EYE)
				continue;

			if (FNullEnt(pPlayer->m_hObserverTarget))
				continue;

			CBasePlayer *pTarget = CBasePlayer::Instance(pPlayer->m_hObserverTarget->pev);
			if (!pTarget || pTarget->IsDormant())
				continue;

			if (g_pGameRules->PlayerRelationship(this, pTarget) == GR_TEAMMATE)
			{
				bSend = true;
			}
		}

		if (bSend)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgSendAudio, nullptr, pEntity->pev);
				WRITE_BYTE(ENTINDEX(edict()));
				WRITE_STRING(msg_id);
				WRITE_SHORT(pitch);
			MESSAGE_END();

			// radio message icon
			if (msg_verbose && msg_verbose[0] != 0)
			{
				// search the place name where is located the player
				const char *placeName = nullptr;
				if ((
#ifdef REGAMEDLL_ADD
					location_area_info.value >= 2 ||
#endif
					AreRunningCZero()) && TheBotPhrases)
				{
					Place playerPlace = TheNavAreaGrid.GetPlace(&pev->origin);
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

				if (placeName && placeName[0])
				{
					bool bUseLocFallback = false;
#ifdef REGAMEDLL_ADD
					if (chat_loc_fallback.value)
						bUseLocFallback = true;
#endif

					ClientPrint(pEntity->pev, HUD_PRINTRADIO, NumAsString(entindex()), bUseLocFallback ? "\x3%s1\x1 @ \x4%s2\x1 (RADIO): %s3" : "#Game_radio_location", STRING(pev->netname), placeName, msg_verbose);
				}
				else
				{
					ClientPrint(pEntity->pev, HUD_PRINTRADIO, NumAsString(entindex()), "#Game_radio", STRING(pev->netname), msg_verbose);
				}
			}

			// icon over the head for teammates
#ifdef REGAMEDLL_ADD
			if (showIcon && show_radioicon.value)
#else
			if (showIcon)
#endif
			{
					// put an icon over this guys head to show that he used the radio
					MESSAGE_BEGIN(MSG_ONE, SVC_TEMPENTITY, nullptr, pEntity->pev);
						WRITE_BYTE(TE_PLAYERATTACHMENT);
						WRITE_BYTE(ENTINDEX(edict()));		// byte	(entity index of player)
						WRITE_COORD(35);					// coord (vertical offset) ( attachment origin.z = player origin.z + vertical offset)
						WRITE_SHORT(g_sModelIndexRadio);	// short (model index) of tempent
						WRITE_SHORT(15);					// short (life * 10 ) e.g. 40 = 4 seconds
					MESSAGE_END();
			}
		}
	}
}

void CBasePlayer::SmartRadio()
{
	;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, Pain, (int iLastHitGroup, bool bHasArmour), iLastHitGroup, bHasArmour)

void EXT_FUNC CBasePlayer::__API_HOOK(Pain)(int iLastHitGroup, bool bHasArmour)
{
	int temp = RANDOM_LONG(0, 2);

	if (iLastHitGroup == HITGROUP_HEAD)
	{
		if (m_iKevlar == ARMOR_VESTHELM)
		{
			EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_helmet-1.wav", VOL_NORM, ATTN_NORM);
			return;
		}

		switch (temp)
		{
		case 0:  EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/headshot1.wav", VOL_NORM, ATTN_NORM); break;
		case 1:  EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/headshot2.wav", VOL_NORM, ATTN_NORM); break;
		default: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/headshot3.wav", VOL_NORM, ATTN_NORM); break;
		}
	}
	else
	{
		if (iLastHitGroup != HITGROUP_LEFTLEG && iLastHitGroup != HITGROUP_RIGHTLEG)
		{
			if (bHasArmour)
			{
				EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_kevlar-1.wav", VOL_NORM, ATTN_NORM);
				return;
			}
		}

		switch (temp)
		{
		case 0:  EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_flesh-1.wav", VOL_NORM, ATTN_NORM); break;
		case 1:  EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_flesh-2.wav", VOL_NORM, ATTN_NORM); break;
		default: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/bhit_flesh-3.wav", VOL_NORM, ATTN_NORM); break;
		}
	}
}

NOXREF Vector VecVelocityForDamage(float flDamage)
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

int TrainSpeed(int iSpeed, int iMax)
{
	float fMax;
	float fSpeed;
	int iRet = 0;

	fMax = float(iMax);
	fSpeed = iSpeed / fMax;

	if (iSpeed < 0)
		iRet = TRAIN_BACK;
	else if (iSpeed == 0)
		iRet = TRAIN_NEUTRAL;
	else if (fSpeed < 0.33f)
		iRet = TRAIN_SLOW;
	else if (fSpeed < 0.66f)
		iRet = TRAIN_MEDIUM;
	else
		iRet = TRAIN_FAST;

	return iRet;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, DeathSound)

void EXT_FUNC CBasePlayer::__API_HOOK(DeathSound)()
{
	// temporarily using pain sounds for death sounds
	switch (RANDOM_LONG(1, 4))
	{
	case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/die1.wav", VOL_NORM, ATTN_NORM); break;
	case 2: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/die2.wav", VOL_NORM, ATTN_NORM); break;
	case 3: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/die3.wav", VOL_NORM, ATTN_NORM); break;
	case 4: EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/death6.wav", VOL_NORM, ATTN_NORM); break;
	}
}

LINK_HOOK_CLASS_CHAIN(BOOL, CBasePlayer, TakeHealth, (float flHealth, int bitsDamageType), flHealth, bitsDamageType)

// override takehealth
// bitsDamageType indicates type of damage healed.
BOOL EXT_FUNC CBasePlayer::__API_HOOK(TakeHealth)(float flHealth, int bitsDamageType)
{
	return CBaseMonster::TakeHealth(flHealth, bitsDamageType);
}

Vector CBasePlayer::GetGunPosition()
{
	return pev->origin + pev->view_ofs;
}

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

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, TraceAttack, (entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType), pevAttacker, flDamage, vecDir, ptr, bitsDamageType)

void EXT_FUNC CBasePlayer::__API_HOOK(TraceAttack)(entvars_t *pevAttacker, float flDamage, VectorRef vecDir, TraceResult *ptr, int bitsDamageType)
{
	bool bShouldBleed = true;
	bool bShouldSpark = false;
	bool bHitShield = IsHittingShield(vecDir, ptr);

	CBasePlayer *pAttacker = CBasePlayer::Instance(pevAttacker);

#ifdef REGAMEDLL_ADD
	if (pAttacker && pAttacker->IsPlayer())
	{
		// don't take damage if victim has protection
		if (CSPlayer()->GetProtectionState() == CCSPlayer::ProtectionSt_Active)
			return;

		if (!CSGameRules()->FPlayerCanTakeDamage(this, pAttacker))
			bShouldBleed = false;
	}

#else
	if (pAttacker && pAttacker->IsPlayer() && m_iTeam == pAttacker->m_iTeam && !friendlyfire.value)
		bShouldBleed = false;
#endif

	if (pev->takedamage == DAMAGE_NO)
		return;

	m_LastHitGroup = ptr->iHitgroup;

	if (bHitShield)
	{
		flDamage = 0;
		bShouldBleed = false;

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
			if (m_iKevlar == ARMOR_VESTHELM)
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

			if (m_iKevlar != ARMOR_NONE)
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
			flDamage *= 1.25;

			if (m_iKevlar != ARMOR_NONE)
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
			if (m_iKevlar != ARMOR_NONE)
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
		SpawnBlood(ptr->vecEndPos, BloodColor(), flDamage);			// a little surface blood.
		TraceBleed(flDamage, vecDir, ptr, bitsDamageType);
	}
	// they hit a helmet
	else if (ptr->iHitgroup == HITGROUP_HEAD && bShouldSpark)
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

const char *CBasePlayer::GetKillerWeaponName(entvars_t *pevInflictor, entvars_t *pevKiller) const
{
	// by default, the player is killed by the world
	const char *killer_weapon_name = "world";

	// Is the killer a client?
	if (pevKiller->flags & FL_CLIENT)
	{
		if (pevInflictor)
		{
			if (pevInflictor == pevKiller)
			{
#ifdef REGAMEDLL_FIXES
				// Ignore the inflictor's weapon if victim killed self
				if (pevKiller != pev)
#endif
				{
					// If the inflictor is the killer, then it must be their current weapon doing the damage
					CBasePlayer *pAttacker = CBasePlayer::Instance(pevKiller);
					if (pAttacker && pAttacker->IsPlayer())
					{
						if (pAttacker->m_pActiveItem)
							killer_weapon_name = pAttacker->m_pActiveItem->pszName();
					}
				}
			}
			else
			{
				// it's just that easy
				killer_weapon_name = STRING(pevInflictor->classname);
			}
		}
	}
	else
#ifdef REGAMEDLL_FIXES
		if (pevInflictor)
#endif
	{
		killer_weapon_name = STRING(pevInflictor->classname);
	}

	// strip the monster_* or weapon_* from the inflictor's classname
	const char cut_weapon[]  = "weapon_";
	const char cut_monster[] = "monster_";
	const char cut_func[]    = "func_";

	// replace the code names with the 'real' names
	if (!Q_strncmp(killer_weapon_name, cut_weapon, sizeof(cut_weapon) - 1))
		killer_weapon_name += sizeof(cut_weapon) - 1;

	else if (!Q_strncmp(killer_weapon_name, cut_monster, sizeof(cut_monster) - 1))
		killer_weapon_name += sizeof(cut_monster) - 1;

	else if (!Q_strncmp(killer_weapon_name, cut_func, sizeof(cut_func) - 1))
		killer_weapon_name += sizeof(cut_func) - 1;

	return killer_weapon_name;
}

void LogAttack(CBasePlayer *pAttacker, CBasePlayer *pVictim, int teamAttack, int healthHit, int armorHit, int newHealth, int newArmor, const char *killer_weapon_name)
{
	int detail = logdetail.value;

	if (!detail)
		return;

	if (!pAttacker || !pVictim)
		return;

	if ((teamAttack && (detail & LOG_TEAMMATEATTACK)) || (!teamAttack && (detail & LOG_ENEMYATTACK)))
	{
		UTIL_LogPrintf("\"%s<%i><%s><%s>\" attacked \"%s<%i><%s><%s>\" with \"%s\" (damage \"%d\") (damage_armor \"%d\") (health \"%d\") (armor \"%d\")\n",
			STRING(pAttacker->pev->netname), GETPLAYERUSERID(pAttacker->edict()), GETPLAYERAUTHID(pAttacker->edict()), GetTeam(pAttacker->m_iTeam),
			STRING(pVictim->pev->netname), GETPLAYERUSERID(pVictim->edict()), GETPLAYERAUTHID(pVictim->edict()),
			GetTeam(pVictim->m_iTeam), killer_weapon_name, healthHit, armorHit, newHealth, newArmor);
	}
}

LINK_HOOK_CLASS_CHAIN(BOOL, CBasePlayer, TakeDamage, (entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType), pevInflictor, pevAttacker, flDamage, bitsDamageType)

// Take some damage.
// RETURN: TRUE took damage, FALSE otherwise
// NOTE: each call to TakeDamage with bitsDamageType set to a time-based damage
// type will cause the damage time countdown to be reset.  Thus the ongoing effects of poison, radiation
// etc are implemented with subsequent calls to TakeDamage using DMG_GENERIC.
BOOL EXT_FUNC CBasePlayer::__API_HOOK(TakeDamage)(entvars_t *pevInflictor, entvars_t *pevAttacker, FloatRef flDamage, int bitsDamageType)
{
	BOOL bTookDamage;
	float flRatio = ARMOR_RATIO;
	float flBonus = ARMOR_BONUS;
	int iGunType = 0;
	float flShieldRatio = 0;
	BOOL bTeamAttack = FALSE;
	int armorHit = 0;
	CBasePlayer *pAttack = nullptr;

#ifdef REGAMEDLL_ADD
	{
		CBaseEntity *pAttacker = GET_PRIVATE<CBaseEntity>(ENT(pevAttacker));

		// don't take damage if victim has protection
		if (((pAttacker && pAttacker->IsPlayer()) || (bitsDamageType & DMG_FALL)) && CSPlayer()->GetProtectionState() == CCSPlayer::ProtectionSt_Active)
			return FALSE;
	}
#endif

	if (bitsDamageType & (DMG_EXPLOSION | DMG_BLAST | DMG_FALL))
		m_LastHitGroup = HITGROUP_GENERIC;

	else if (m_LastHitGroup == HITGROUP_SHIELD && (bitsDamageType & DMG_BULLET))
		return FALSE;

	if (HasShield())
		flShieldRatio = 0.2;

	if (m_bIsVIP)
		flRatio *= 0.5;

	if (bitsDamageType & (DMG_EXPLOSION | DMG_BLAST))
	{
		if (!IsAlive())
			return FALSE;

		if (bitsDamageType & DMG_EXPLOSION)
		{
			CBaseEntity *temp = GetClassPtr<CCSEntity>((CBaseEntity *)pevInflictor);
			if (FClassnameIs(temp->pev, "grenade"))
			{
				CGrenade *pGrenade = GetClassPtr<CCSGrenade>((CGrenade *)pevInflictor);

				pAttack = CBasePlayer::Instance(pevAttacker);

				if (
#ifdef REGAMEDLL_ADD
					!CSGameRules()->IsFreeForAll() &&
#endif
					pGrenade->m_iTeam == m_iTeam)
				{
					if (friendlyfire.value)
					{
						bTeamAttack = TRUE;
#ifdef REGAMEDLL_ADD
						flDamage *= clamp(((pAttack == this) ?
							ff_damage_reduction_grenade_self.value :
							ff_damage_reduction_grenade.value), 0.0f, 1.0f);
#endif
					}
					else if (pAttack == this)
					{
#ifdef REGAMEDLL_ADD
						flDamage *= clamp(ff_damage_reduction_grenade_self.value, 0.0f, 1.0f);
#endif
					}
					else
					{
						// if cvar friendlyfire is disabled
						// and if the victim is teammate then ignore this damage
						return FALSE;
					}
				}
			}
		}

		if (!FNullEnt(ENT(pevInflictor)))
			m_vBlastVector = pev->origin - pevInflictor->origin;

		if (pev->armorvalue != 0.0f && IsArmored(m_LastHitGroup))
		{
			real_t flNew = flRatio * flDamage;
			real_t flArmor = (flDamage - flNew) * flBonus;

			// Does this use more armor than we have?
			if (flArmor > pev->armorvalue)
			{
				flNew = flDamage - pev->armorvalue;
				armorHit = flArmor;
				pev->armorvalue = 0;
			}
			else
			{
				int oldValue = pev->armorvalue;

				if (flArmor < 0.0)
					flArmor = 1.0;

				pev->armorvalue -= flArmor;
				armorHit = oldValue - pev->armorvalue;
			}

			flDamage = flNew;

			if (pev->armorvalue <= 0.0)
				m_iKevlar = ARMOR_NONE;

			Pain(m_LastHitGroup, true);
		}
		else
		{
			Pain(m_LastHitGroup, false);
		}

		m_lastDamageAmount = flDamage;

		if (pev->health > flDamage)
		{
			SetAnimation(PLAYER_FLINCH);
			Pain(m_LastHitGroup, false);
		}
		else
		{
			if (bitsDamageType & DMG_BLAST)
				m_bKilledByBomb = true;

			else if (bitsDamageType & DMG_EXPLOSION)
				m_bKilledByGrenade = true;
		}

		LogAttack(pAttack, this, bTeamAttack, int(flDamage), armorHit, pev->health - flDamage, pev->armorvalue, GetKillerWeaponName(pevInflictor, pevAttacker));
		bTookDamage = CBaseMonster::TakeDamage(pevInflictor, pevAttacker, int(flDamage), bitsDamageType);

		if (bTookDamage)
		{
			if (TheBots)
			{
				TheBots->OnEvent(EVENT_PLAYER_TOOK_DAMAGE, this, pAttack);
			}

			if (TheCareerTasks)
			{
				CBasePlayer *pPlayerAttacker = CBasePlayer::Instance(pevAttacker);
				if (pPlayerAttacker && !pPlayerAttacker->IsBot() && pPlayerAttacker->m_iTeam != m_iTeam)
				{
					TheCareerTasks->HandleEnemyInjury(GetKillerWeaponName(pevInflictor, pevAttacker), pPlayerAttacker->HasShield(), pPlayerAttacker);
				}
			}

#ifdef REGAMEDLL_API
			CSPlayer()->RecordDamage(pAttack, flDamage);
#endif
		}

		{
			// reset damage time countdown for each type of time based damage player just sustained
			for (int i = 0; i < ITBD_END; i++)
			{
				if (bitsDamageType & (DMG_PARALYZE << i))
					m_rgbTimeBasedDamage[i] = 0;
			}
		}

		// tell director about it
		MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
			WRITE_BYTE(9);								// command length in bytes
			WRITE_BYTE(DRC_CMD_EVENT);					// take damage event
			WRITE_SHORT(ENTINDEX(edict()));				// index number of primary entity
			WRITE_SHORT(ENTINDEX(ENT(pevInflictor)));	// index number of secondary entity
			WRITE_LONG(5);								// eventflags (priority and flags)
		MESSAGE_END();

		MESSAGE_BEGIN(MSG_SPEC, gmsgHLTV);
			WRITE_BYTE(ENTINDEX(edict()));
			WRITE_BYTE(int(Q_max(pev->health, 0.0f)) | DRC_FLAG_FACEPLAYER);
		MESSAGE_END();

		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

			if (!UTIL_IsValidPlayer(pPlayer))
				continue;

			if (pPlayer->m_hObserverTarget != this)
				continue;

			MESSAGE_BEGIN(MSG_ONE, gmsgSpecHealth, nullptr, pPlayer->edict());
				WRITE_BYTE(int(Q_max(pev->health, 0.0f)));
			MESSAGE_END();
		}

		return bTookDamage;
	}

	CBaseEntity *pAttacker = CBaseEntity::Instance(pevAttacker);

	if (!g_pGameRules->FPlayerCanTakeDamage(this, pAttacker) && !FClassnameIs(pevInflictor, "grenade"))
	{
		// Refuse the damage
		return FALSE;
	}

	if ((bitsDamageType & DMG_BLAST) && g_pGameRules->IsMultiplayer())
	{
		// blasts damage armor more.
		flBonus *= 2;
	}

	// Already dead
	if (!IsAlive())
		return FALSE;

	pAttacker = GetClassPtr<CCSEntity>((CBaseEntity *)pevAttacker);

	if (pAttacker->IsPlayer() && !(pAttacker == this && (bitsDamageType & DMG_FALL)))
	{
		pAttack = GetClassPtr<CCSPlayer>((CBasePlayer *)pevAttacker);

		// warn about team attacks
		if (g_pGameRules->PlayerRelationship(this, pAttack) == GR_TEAMMATE)
		{
			if (pAttack != this)
			{
#ifndef REGAMEDLL_FIXES
				if (!(m_flDisplayHistory & DHF_FRIEND_INJURED))
				{
					m_flDisplayHistory |= DHF_FRIEND_INJURED;
					pAttack->HintMessage("#Hint_try_not_to_injure_teammates");
				}
#else
				if (!(pAttack->m_flDisplayHistory & DHF_FRIEND_INJURED))
				{
					pAttack->m_flDisplayHistory |= DHF_FRIEND_INJURED;
					pAttack->HintMessage("#Hint_try_not_to_injure_teammates");
				}
#endif

				bTeamAttack = TRUE;
				if (gpGlobals->time > pAttack->m_flLastAttackedTeammate + 0.6f)
				{
					CBaseEntity *pEntity = nullptr;
					while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
					{
						if (FNullEnt(pEntity->edict()))
							break;

						if (pEntity->IsDormant())
							continue;

						CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

						if (pPlayer->m_iTeam == m_iTeam)
						{
							ClientPrint(pPlayer->pev, HUD_PRINTTALK, "#Game_teammate_attack", STRING(pAttack->pev->netname));
						}
					}

					pAttack->m_flLastAttackedTeammate = gpGlobals->time;
				}

#ifdef REGAMEDLL_ADD
				// bullets hurt teammates less
				flDamage *= clamp(((bitsDamageType & DMG_BULLET) ?
					ff_damage_reduction_bullets.value :
					ff_damage_reduction_other.value), 0.0f, 1.0f);
#endif // #ifdef REGAMEDLL_ADD
			}

#ifndef REGAMEDLL_ADD
			flDamage *= 0.35;
#endif
		}

		if (pAttack->m_pActiveItem)
		{
			iGunType = pAttack->m_pActiveItem->m_iId;
			flRatio += flShieldRatio;

			switch (iGunType)
			{
			case WEAPON_AUG:
			case WEAPON_M4A1:		flRatio *= 1.4;  break;
			case WEAPON_AWP:		flRatio *= 1.95; break;
			case WEAPON_G3SG1:		flRatio *= 1.65; break;
			case WEAPON_SG550:		flRatio *= 1.45; break;
			case WEAPON_M249:		flRatio *= 1.5;  break;
			case WEAPON_ELITE:		flRatio *= 1.05; break;
			case WEAPON_DEAGLE:		flRatio *= 1.5;  break;
			case WEAPON_GLOCK18:	flRatio *= 1.05; break;
			case WEAPON_FIVESEVEN:
			case WEAPON_P90:
				flRatio *= 1.5;
				break;
			case WEAPON_MAC10:
				flRatio *= 0.95;
				break;
			case WEAPON_P228:
				flRatio *= 1.25;
				break;
			case WEAPON_SCOUT:
			case WEAPON_KNIFE:
				flRatio *= 1.7;
				break;
			case WEAPON_FAMAS:
			case WEAPON_SG552:
				flRatio *= 1.4;
				break;
			case WEAPON_GALIL:
			case WEAPON_AK47:
				flRatio *= 1.55;
				break;
			}
		}

		if (!ShouldDoLargeFlinch(m_LastHitGroup, iGunType))
		{
			m_flVelocityModifier = 0.5f;

			if (m_LastHitGroup == HITGROUP_HEAD)
				m_bHighDamage = (flDamage > 60);
			else
				m_bHighDamage = (flDamage > 20);

			SetAnimation(PLAYER_FLINCH);
		}
		else
		{
			if (pev->velocity.Length() < 300)
			{
				Vector attack_velocity = (pev->origin - pAttack->pev->origin).Normalize() * 170;
				pev->velocity = pev->velocity + attack_velocity;

				m_flVelocityModifier = 0.65f;
			}

			SetAnimation(PLAYER_LARGE_FLINCH);
		}
	}

	// Armor
	// armor doesn't protect against fall or drown damage!
	if (pev->armorvalue != 0.0f && !(bitsDamageType & (DMG_DROWN | DMG_FALL)) && IsArmored(m_LastHitGroup))
	{
		real_t flNew = flRatio * flDamage;
		real_t flArmor = (flDamage - flNew) * flBonus;

		// Does this use more armor than we have?
		if (flArmor > pev->armorvalue)
		{
			armorHit = flArmor;
			flArmor = pev->armorvalue;
			flArmor *= (1 / flBonus);
			flNew = flDamage - flArmor;
			pev->armorvalue = 0;
		}
		else
		{
			int oldValue = pev->armorvalue;

			if (flArmor < 0.0)
				flArmor = 1.0;

			pev->armorvalue -= flArmor;
			armorHit = oldValue - pev->armorvalue;
		}

		flDamage = flNew;

		if (pev->armorvalue <= 0.0f)
			m_iKevlar = ARMOR_NONE;

		Pain(m_LastHitGroup, true);
	}
	else
	{
		Pain(m_LastHitGroup, false);
	}

	// keep track of amount of damage last sustained
	m_lastDamageAmount = flDamage;

	LogAttack(pAttack, this, bTeamAttack, flDamage, armorHit, pev->health - flDamage, pev->armorvalue, GetKillerWeaponName(pevInflictor, pevAttacker));

	// this cast to INT is critical!!! If a player ends up with 0.5 health, the engine will get that
	// as an int (zero) and think the player is dead! (this will incite a clientside screentilt, etc)
	bTookDamage = CBaseMonster::TakeDamage(pevInflictor, pevAttacker, int(flDamage), bitsDamageType);

	if (bTookDamage)
	{
		if (TheBots)
		{
			TheBots->OnEvent(EVENT_PLAYER_TOOK_DAMAGE, this, pAttack);
		}

		if (TheCareerTasks)
		{
			CBasePlayer *pPlayerAttacker = CBasePlayer::Instance(pevAttacker);
			if (pPlayerAttacker && !pPlayerAttacker->IsBot() && pPlayerAttacker->m_iTeam != m_iTeam)
			{
				TheCareerTasks->HandleEnemyInjury(GetKillerWeaponName(pevInflictor, pevAttacker), pPlayerAttacker->HasShield(), pPlayerAttacker);
			}
		}

#ifdef REGAMEDLL_API
		CSPlayer()->RecordDamage(pAttack, flDamage);
#endif
	}

	{
		// reset damage time countdown for each type of time based damage player just sustained
		for (int i = 0; i < ITBD_END; i++)
		{
			if (bitsDamageType & (DMG_PARALYZE << i))
				m_rgbTimeBasedDamage[i] = 0;
		}
	}

	// tell director about it
	MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
		WRITE_BYTE(9);								// command length in bytes
		WRITE_BYTE(DRC_CMD_EVENT);					// take damage event
		WRITE_SHORT(ENTINDEX(edict()));				// index number of primary entity
		WRITE_SHORT(ENTINDEX(ENT(pevInflictor)));	// index number of secondary entity
		WRITE_LONG(5);								// eventflags (priority and flags)
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_SPEC, gmsgHLTV);
		WRITE_BYTE(ENTINDEX(edict()));
		WRITE_BYTE(int(Q_max(pev->health, 0.0f)) | DRC_FLAG_FACEPLAYER);
	MESSAGE_END();

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pPlayer))
			continue;

		if (pPlayer->m_hObserverTarget == this)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgSpecHealth, nullptr, pPlayer->edict());
				WRITE_BYTE(int(Q_max(pev->health, 0.0f)));
			MESSAGE_END();
		}
	}

#ifdef REGAMEDLL_FIXES
	if ((bitsDamageType & DMG_DROWN) && pev->waterlevel == 0) {
		bitsDamageType &= ~DMG_DROWN;
	}
#endif

	// Save this so we can report it to the client
	m_bitsHUDDamage = -1;

	// make sure the damage bits get resent
	m_bitsDamageType |= bitsDamageType;

	return bTookDamage;
}

LINK_HOOK_CHAIN(CWeaponBox *, CreateWeaponBox, (CBasePlayerItem *pItem, CBasePlayer *pPlayerOwner, const char *modelName, Vector &origin, Vector &angles, Vector &velocity, float lifeTime, bool packAmmo), pItem, pPlayerOwner, modelName, origin, angles, velocity, lifeTime, packAmmo)

CWeaponBox *EXT_FUNC __API_HOOK(CreateWeaponBox)(CBasePlayerItem *pItem, CBasePlayer *pPlayerOwner, const char *modelName, Vector &origin, Vector &angles, Vector &velocity, float lifeTime, bool packAmmo)
{
	// create a box to pack the stuff into.
	CWeaponBox *pWeaponBox = (CWeaponBox *)CBaseEntity::Create("weaponbox", origin, angles, pPlayerOwner ? ENT(pPlayerOwner->pev) : nullptr);

	if (pWeaponBox)
	{
		// don't let weaponbox tilt.
		pWeaponBox->pev->angles.x = 0;
		pWeaponBox->pev->angles.z = 0;
		pWeaponBox->pev->velocity = velocity;
		pWeaponBox->SetThink(&CWeaponBox::Kill);
		pWeaponBox->pev->nextthink = gpGlobals->time + lifeTime;
		pWeaponBox->PackWeapon(pItem); // now pack all of the items in the lists

		// player is the ammo source
		if (pPlayerOwner)
		{
			// by removing ammo ONLY on exhaustible weapons (slot 4 and 5)
			// you are allowing to duplicate ammo whenever:
			// (1) you have 2 weapons sharing the same ammo type (e.g. mp5navy and glock)
			// (2) you are dropping a weapon alive and pickup another (with same ammo type) without ammo
			// and, logically, you throw your ammo with your gun with packing enabled
			bool exhaustibleAmmo = (pItem->iFlags() & ITEM_FLAG_EXHAUSTIBLE) == ITEM_FLAG_EXHAUSTIBLE;

			// pack the primary ammo
			if (exhaustibleAmmo || packAmmo)
			{
#ifndef REGAMEDLL_ADD
				pWeaponBox->PackAmmo(MAKE_STRING(pItem->pszAmmo1()), pPlayerOwner->m_rgAmmo[pItem->PrimaryAmmoIndex()]);
#else
				pWeaponBox->GiveAmmo(pPlayerOwner->m_rgAmmo[pItem->PrimaryAmmoIndex()], (char *)pItem->pszAmmo1(), pItem->iMaxAmmo1());
#endif

#ifndef REGAMEDLL_FIXES
				if (exhaustibleAmmo)
#endif
				{
					pPlayerOwner->m_rgAmmo[pItem->PrimaryAmmoIndex()] = 0;
				}
			}

			// (3rd party support) now that reapi can register custom ammo
#ifdef REGAMEDLL_ADD
			// use this flag if you don't want the player harvesting this kind of ammo from dropped weapons
			bool exhaustSecondaryAmmo = (pItem->iFlags() & ITEM_FLAG_EXHAUST_SECONDARYAMMO) == ITEM_FLAG_EXHAUST_SECONDARYAMMO;
			int iSecondaryAmmoIndex = pItem->SecondaryAmmoIndex();

			// pack secondary ammo now (must be valid too)
			if ((exhaustibleAmmo || exhaustSecondaryAmmo || packAmmo) && iSecondaryAmmoIndex != -1)
			{
				pWeaponBox->GiveAmmo(pPlayerOwner->m_rgAmmo[iSecondaryAmmoIndex], (char *)pItem->pszAmmo2(), pItem->iMaxAmmo2());

#ifndef REGAMEDLL_FIXES
				if (exhaustibleAmmo)
#endif
				{
					pPlayerOwner->m_rgAmmo[iSecondaryAmmoIndex] = 0;
				}
			}
#endif
		}

		pWeaponBox->SetModel(modelName);
	}

	return pWeaponBox;
}

CWeaponBox *PackPlayerItem(CBasePlayer *pPlayer, CBasePlayerItem *pItem, bool packAmmo)
{
	if (!pItem)
		return nullptr;

	const char *modelName = GetCSModelName(pItem->m_iId);
	if (modelName)
	{
		Vector vecOrigin   = pPlayer->pev->origin;
		Vector vecAngles   = pPlayer->pev->angles;
		Vector vecVelocity = pPlayer->pev->velocity * 0.75f;

		// create a box to pack the stuff into
		return CreateWeaponBox(pItem, pPlayer,
			modelName,
			vecOrigin,
			vecAngles,
			vecVelocity,
			CGameRules::GetItemKillDelay(), packAmmo
		);
	}

	return nullptr;
}

#ifdef REGAMEDLL_ADD
void PackPlayerNade(CBasePlayer *pPlayer, CBasePlayerItem *pItem, bool packAmmo)
{
	if (!pItem)
		return;

	if (pItem->m_flStartThrow != 0.0f || pPlayer->m_rgAmmo[pItem->PrimaryAmmoIndex()] <= 0) {
		return;
	}

	const char *modelName = GetCSModelName(pItem->m_iId);
	if (modelName)
	{
		float flOffset = 0.0f;
		switch (pItem->m_iId)
		{
		case WEAPON_HEGRENADE:
			flOffset = 14.0f;
			break;
		case WEAPON_FLASHBANG:
			flOffset = 0.0f;
			break;
		case WEAPON_SMOKEGRENADE:
			flOffset = -14.0f;
			break;
		}

		Vector vecAngles = pPlayer->pev->angles;
		Vector dir(Q_cos(vecAngles.y) * flOffset, Q_sin(vecAngles.y) * flOffset, 0.0f);

		vecAngles.x = 0.0f;
		vecAngles.y += 45.0f;

		Vector vecOrigin   = pPlayer->pev->origin + dir;
		Vector vecVelocity = pPlayer->pev->velocity * 0.75f;

		// create a box to pack the stuff into.
		CreateWeaponBox(pItem, pPlayer,
			modelName,
			vecOrigin,
			vecAngles,
			vecVelocity,
			CGameRules::GetItemKillDelay(),
			packAmmo);
	}
}
#endif

// PackDeadPlayerItems - call this when a player dies to
// pack up the appropriate weapons and ammo items, and to
// destroy anything that shouldn't be packed.
void CBasePlayer::PackDeadPlayerItems()
{
	// get the game rules
	int iPackGun = g_pGameRules->DeadPlayerWeapons(this);
	bool bPackAmmo = (g_pGameRules->DeadPlayerAmmo(this) != GR_PLR_DROP_AMMO_NO);

	if (iPackGun != GR_PLR_DROP_GUN_NO)
	{
		bool bSkipPrimSec = false;
		if (HasShield())
		{
			DropShield();
#ifdef REGAMEDLL_ADD
			if(iPackGun != GR_PLR_DROP_GUN_ALL)
#endif
			{
				bSkipPrimSec = true;
			}
		}

		int nBestWeight = 0;
		CBasePlayerItem *pBestItem = nullptr;

#ifdef REGAMEDLL_ADD
		int iGunsPacked = 0;

		if (iPackGun == GR_PLR_DROP_GUN_ACTIVE)
		{
			// check if we've just already dropped our active gun
			if (!bSkipPrimSec && m_pActiveItem && m_pActiveItem->CanDrop() && m_pActiveItem->iItemSlot() < KNIFE_SLOT)
			{
				pBestItem = m_pActiveItem;

				// if active item is undroppable, then nothing is dropped
			}

			// are we allowing nade drop?
			if ((int)nadedrops.value >= 1)
			{
				// goto item loop but skip guns
				iPackGun = GR_PLR_DROP_GUN_ALL;
				bSkipPrimSec = true;
			}
		}

		if (iPackGun == GR_PLR_DROP_GUN_ALL || iPackGun == GR_PLR_DROP_GUN_BEST)
#endif
		{
			for (int n = 0; n < MAX_ITEM_TYPES; n++)
			{
				// there's a weapon here. Should I pack it?
				CBasePlayerItem *pPlayerItem = m_rgpPlayerItems[n];

				while (pPlayerItem)
				{
					ItemInfo info;
					if (pPlayerItem->iItemSlot() < KNIFE_SLOT && !bSkipPrimSec)
					{
#ifdef REGAMEDLL_API
						if (pPlayerItem->CSPlayerItem()->GetItemInfo(&info)
#else
						if (pPlayerItem->GetItemInfo(&info)
#endif
#ifdef REGAMEDLL_FIXES
							&& pPlayerItem->CanDrop() // needs to be droppable
#endif
							)
						{
#ifdef REGAMEDLL_ADD
							if (iPackGun == GR_PLR_DROP_GUN_ALL)
							{
								CBasePlayerItem *pNext = pPlayerItem->m_pNext;

								CWeaponBox *pWeaponBox = PackPlayerItem(this, pPlayerItem, bPackAmmo);
								if (pWeaponBox)
								{
									// just push a few units in forward to separate them
									pWeaponBox->pev->velocity = pWeaponBox->pev->velocity * (1.0 + (iGunsPacked * 0.2));
									iGunsPacked++;
								}

								pPlayerItem = pNext;
								continue;
							}
#endif
							if (info.iWeight > nBestWeight)
							{
								nBestWeight = info.iWeight;
								pBestItem = pPlayerItem;
							}
						}
					}
					// drop a grenade after death
					else if (pPlayerItem->iItemSlot() == GRENADE_SLOT)
					{
						if (AreRunningCZero())
						{

#ifdef REGAMEDLL_FIXES
							if (pPlayerItem->m_flStartThrow == 0.0f && m_rgAmmo[pPlayerItem->PrimaryAmmoIndex()] > 0)
#endif
							{
								PackPlayerItem(this, pPlayerItem, true);
							}
						}
#ifdef REGAMEDLL_ADD
						else
						{
							switch ((int)nadedrops.value)
							{
							case 1:
								PackPlayerNade(this, pPlayerItem, true);
								break;
							case 2:
							{
								CBasePlayerItem *pNext = pPlayerItem->m_pNext;
								PackPlayerNade(this, pPlayerItem, true);
								pPlayerItem = pNext;
								continue;
							}
							}
						}
#endif
					}

					pPlayerItem = pPlayerItem->m_pNext;
				}
			}
		}

		PackPlayerItem(this, pBestItem, bPackAmmo);
	}

	RemoveAllItems(TRUE);
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, GiveDefaultItems)

void EXT_FUNC CBasePlayer::__API_HOOK(GiveDefaultItems)()
{
	RemoveAllItems(FALSE);

// NOTE: It is already does reset inside RemoveAllItems
#ifndef REGAMEDLL_FIXES
	m_bHasPrimary = false;
#endif

#ifdef REGAMEDLL_ADD
	auto GiveWeapon = [&](int ammo, const char *pszWeaponName) {
		auto pItem = static_cast<CBasePlayerItem *>(GiveNamedItemEx(pszWeaponName));
		if (pItem) {
			GiveAmmo(refill_bpammo_weapons.value != 0.0f ? pItem->iMaxAmmo1() : ammo, pItem->pszAmmo1(), pItem->iMaxAmmo1());
		}
	};

	bool bGiveKnife = false;
	if (m_iTeam == CT)
		bGiveKnife = ct_give_player_knife.value != 0;
	else if (m_iTeam == TERRORIST)
		bGiveKnife = t_give_player_knife.value != 0;

	if (bGiveKnife && !HasRestrictItem(ITEM_KNIFE, ITEM_TYPE_EQUIPPED)) {
		GiveNamedItemEx("weapon_knife");
	}

	const int iAmountOfBPAmmo = m_bIsVIP ? 1 : 2; // Give regular the player backpack ammo twice more than to VIP the player

	// Give default secondary equipment
	{
		char *secondaryString = NULL;
		if (m_iTeam == CT)
			secondaryString = ct_default_weapons_secondary.string;
		else if (m_iTeam == TERRORIST)
			secondaryString = t_default_weapons_secondary.string;

		if (secondaryString && secondaryString[0] != '\0')
		{
			secondaryString = SharedParse(secondaryString);

			while (secondaryString)
			{
				WeaponInfoStruct *weaponInfo;
				WeaponIdType weaponId = AliasToWeaponID(SharedGetToken());
				if (weaponId != WEAPON_NONE)
					weaponInfo = GetWeaponInfo(weaponId);
				else
					weaponInfo = GetWeaponInfo(SharedGetToken());

				if (weaponInfo) {
					const auto iItemID = GetItemIdByWeaponId(weaponInfo->id);
					if (iItemID != ITEM_NONE && !HasRestrictItem(iItemID, ITEM_TYPE_EQUIPPED) && IsSecondaryWeapon(iItemID)) {
						GiveWeapon(weaponInfo->gunClipSize * iAmountOfBPAmmo, weaponInfo->entityName);
					}
				}

				secondaryString = SharedParse(secondaryString);
			}
		}
	}

	// Give default primary equipment
	{
		char *primaryString = NULL;

		if (m_iTeam == CT)
			primaryString = ct_default_weapons_primary.string;
		else if (m_iTeam == TERRORIST)
			primaryString = t_default_weapons_primary.string;

		if (primaryString && primaryString[0] != '\0')
		{
			primaryString = SharedParse(primaryString);

			while (primaryString)
			{
				WeaponInfoStruct *weaponInfo;
				WeaponIdType weaponId = AliasToWeaponID(SharedGetToken());
				if (weaponId != WEAPON_NONE)
					weaponInfo = GetWeaponInfo(weaponId);
				else
					weaponInfo = GetWeaponInfo(SharedGetToken());

				if (weaponInfo) {
					const auto iItemID = GetItemIdByWeaponId(weaponInfo->id);
					if (iItemID != ITEM_NONE && !HasRestrictItem(iItemID, ITEM_TYPE_EQUIPPED) && IsPrimaryWeapon(iItemID)) {
						GiveWeapon(weaponInfo->gunClipSize * iAmountOfBPAmmo, weaponInfo->entityName);
					}
				}

				primaryString = SharedParse(primaryString);
			}
		}
	}

	// Give the player grenades if he needs them
	char *grenadeString = NULL;
	if (m_iTeam == CT)
		grenadeString = ct_default_grenades.string;
	else if (m_iTeam == TERRORIST)
		grenadeString = t_default_grenades.string;

	if (grenadeString && grenadeString[0] != '\0')
	{
		grenadeString = SharedParse(grenadeString);

		while (grenadeString)
		{
			WeaponInfoStruct *weaponInfo;
			WeaponIdType weaponId = AliasToWeaponID(SharedGetToken());
			if (weaponId != WEAPON_NONE)
				weaponInfo = GetWeaponInfo(weaponId);
			else
				weaponInfo = GetWeaponInfo(SharedGetToken());

			if (weaponInfo) {
				const auto iItemID = GetItemIdByWeaponId(weaponInfo->id);
				if (iItemID != ITEM_NONE && !HasRestrictItem(iItemID, ITEM_TYPE_EQUIPPED) && IsGrenadeWeapon(iItemID)) {
					GiveNamedItemEx(weaponInfo->entityName);
				}
			}

			grenadeString = SharedParse(grenadeString);
		}
	}

#else
	switch (m_iTeam)
	{
	case CT:
		GiveNamedItem("weapon_knife");
		GiveNamedItem("weapon_usp");
		GiveAmmo(m_bIsVIP ? 12 : 24, "45acp");
		break;
	case TERRORIST:
		GiveNamedItem("weapon_knife");
		GiveNamedItem("weapon_glock18");
		GiveAmmo(40, "9mm");
		break;
	}
#endif
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, RemoveAllItems, (BOOL removeSuit), removeSuit)

void EXT_FUNC CBasePlayer::__API_HOOK(RemoveAllItems)(BOOL removeSuit)
{
	int i;

#ifdef REGAMEDLL_FIXES
	if (m_pTank)
	{
		m_pTank->Use(this, this, USE_OFF, 0);
		m_pTank = nullptr;
	}
#endif

	if (m_bHasDefuser)
	{
		RemoveDefuser();
	}

	if (m_bHasC4)
	{
		m_bHasC4 = false;
		pev->body = 0;
		SetBombIcon(FALSE);
		SetProgressBarTime(0);
	}

	RemoveShield();

	if (m_pActiveItem)
	{
		ResetAutoaim();

		m_pActiveItem->Holster();
		m_pActiveItem = nullptr;
	}

	m_pLastItem = nullptr;

	for (i = 0; i < MAX_ITEM_TYPES; i++)
	{
		m_pActiveItem = m_rgpPlayerItems[i];

		while (m_pActiveItem)
		{
			CBasePlayerItem *pPendingItem = m_pActiveItem->m_pNext;

			m_pActiveItem->Drop();
			m_pActiveItem = pPendingItem;
		}

		m_rgpPlayerItems[i] = nullptr;
	}

	m_pActiveItem = nullptr;
	m_bHasPrimary = false;

	pev->viewmodel = 0;
	pev->weaponmodel = 0;

#ifdef REGAMEDLL_FIXES
	// if (m_iFOV != DEFAULT_FOV)
	{
		pev->fov = m_iFOV = m_iLastZoom = DEFAULT_FOV;
		m_bResumeZoom = false;
	}
#endif

	if (removeSuit)
		pev->weapons = 0;
	else
		pev->weapons &= ~WEAPON_ALLWEAPONS;

	for (i = 0; i < MAX_AMMO_SLOTS; i++)
		m_rgAmmo[i] = 0;

	UpdateClientData();

#ifdef REGAMEDLL_FIXES
	m_iHideHUD |= HIDEHUD_WEAPONS;

	m_bHasNightVision = false;
	SendItemStatus();

	ResetMaxSpeed();
#endif

	// send Selected Weapon Message to our client
	MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, nullptr, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(0);
		WRITE_BYTE(0);
	MESSAGE_END();
}

void CBasePlayer::SetBombIcon(BOOL bFlash)
{
	if (m_bHasC4)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
			WRITE_BYTE(bFlash ? STATUSICON_FLASH : STATUSICON_SHOW);
			WRITE_STRING("c4");
			WRITE_BYTE(0);
			WRITE_BYTE(160);
			WRITE_BYTE(0);
		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("c4");
		MESSAGE_END();
	}

	SetScoreboardAttributes();
}

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

	MESSAGE_BEGIN(MSG_ONE, gmsgBarTime, nullptr, pev);
		WRITE_SHORT(time);
	MESSAGE_END();

	int playerIndex = entindex();
	CBaseEntity *pEntity = nullptr;

	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (pEntity->IsDormant())
			continue;

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (pPlayer->GetObserverMode() == OBS_IN_EYE && pPlayer->pev->iuser2 == playerIndex)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBarTime, nullptr, pPlayer->pev);
				WRITE_SHORT(time);
			MESSAGE_END();
		}
	}
}

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

	MESSAGE_BEGIN(MSG_ONE, gmsgBarTime2, nullptr, pev);
		WRITE_SHORT(time);
		WRITE_SHORT(iTimeElapsed);
	MESSAGE_END();

	int playerIndex = entindex();
	CBaseEntity *pEntity = nullptr;

	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (pEntity->IsDormant())
			continue;

		CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (pPlayer->GetObserverMode() == OBS_IN_EYE && pPlayer->pev->iuser2 == playerIndex)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBarTime2, nullptr, pPlayer->pev);
				WRITE_SHORT(time);
				WRITE_SHORT(iTimeElapsed);
			MESSAGE_END();
		}
	}
}

void BuyZoneIcon_Set(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("buyzone");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();
}

void BuyZoneIcon_Clear(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("buyzone");
	MESSAGE_END();

	if (pPlayer->m_iMenu >= Menu_Buy)
	{
		if (pPlayer->m_iMenu <= Menu_BuyItem)
		{

#ifdef REGAMEDLL_FIXES
			// NOTE: is client-side bug
			if (pPlayer->m_bVGUIMenus)
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, nullptr, pPlayer->pev);
				MESSAGE_END();
			}
#endif

			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");
		}
		else if (pPlayer->m_iMenu == Menu_ClientBuy)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, nullptr, pPlayer->pev);
			MESSAGE_END();
		}
	}
}

void BombTargetFlash_Set(CBasePlayer *pPlayer)
{
	if (pPlayer->m_bHasC4 && !(pPlayer->m_flDisplayHistory & DHF_IN_TARGET_ZONE))
	{
		pPlayer->m_flDisplayHistory |= DHF_IN_TARGET_ZONE;
		pPlayer->HintMessage("#Hint_you_are_in_targetzone");
	}

	pPlayer->SetBombIcon(TRUE);
}

void BombTargetFlash_Clear(CBasePlayer *pPlayer)
{
	pPlayer->SetBombIcon(FALSE);
}

void RescueZoneIcon_Set(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("rescue");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	if (pPlayer->m_iTeam == CT && !(pPlayer->m_flDisplayHistory & DHF_IN_RESCUE_ZONE))
	{
		pPlayer->m_flDisplayHistory |= DHF_IN_RESCUE_ZONE;
		pPlayer->HintMessage("#Hint_hostage_rescue_zone");
	}
}

void RescueZoneIcon_Clear(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("rescue");
	MESSAGE_END();

	if (pPlayer->m_iMenu >= Menu_Buy)
	{
		if (pPlayer->m_iMenu <= Menu_BuyItem)
		{
			CLIENT_COMMAND(ENT(pPlayer->pev), "slot10\n");
		}
		else if (pPlayer->m_iMenu == Menu_ClientBuy)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, nullptr, pPlayer->pev);
			MESSAGE_END();
		}
	}
}

void EscapeZoneIcon_Set(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("escape");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	if (pPlayer->m_iTeam == CT)
	{
		if (!(pPlayer->m_flDisplayHistory & DHF_IN_ESCAPE_ZONE))
		{
			pPlayer->m_flDisplayHistory |= DHF_IN_ESCAPE_ZONE;
			pPlayer->HintMessage("#Hint_terrorist_escape_zone");
		}
	}
}

void EscapeZoneIcon_Clear(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("escape");
	MESSAGE_END();

	if (pPlayer->m_iMenu >= Menu_Buy)
	{
		if (pPlayer->m_iMenu <= Menu_BuyItem)
		{
			CLIENT_COMMAND(pPlayer->edict(), "slot10\n");
		}
		else if (pPlayer->m_iMenu == Menu_ClientBuy)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, nullptr, pPlayer->pev);
			MESSAGE_END();
		}
	}
}

void VIP_SafetyZoneIcon_Set(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("vipsafety");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	if (!(pPlayer->m_flDisplayHistory & DHF_IN_VIPSAFETY_ZONE))
	{
		if (pPlayer->m_iTeam == CT)
		{
			pPlayer->m_flDisplayHistory |= DHF_IN_VIPSAFETY_ZONE;
			pPlayer->HintMessage("#Hint_ct_vip_zone", TRUE);
		}
		else if (pPlayer->m_iTeam == TERRORIST)
		{
			pPlayer->m_flDisplayHistory |= DHF_IN_VIPSAFETY_ZONE;
			pPlayer->HintMessage("#Hint_terrorist_vip_zone", TRUE);
		}
	}
}

void VIP_SafetyZoneIcon_Clear(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pPlayer->pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("vipsafety");
	MESSAGE_END();

	if (pPlayer->m_iMenu >= Menu_Buy)
	{
		if (pPlayer->m_iMenu <= Menu_BuyItem)
		{
			CLIENT_COMMAND(pPlayer->edict(), "slot10\n");
		}
		else if (pPlayer->m_iMenu == Menu_ClientBuy)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgBuyClose, nullptr, pPlayer->pev);
			MESSAGE_END();
		}
	}
}

void CBasePlayer::SendFOV(int fov)
{
	pev->fov = real_t(fov);
	m_iClientFOV = fov;
	m_iFOV = fov;

	MESSAGE_BEGIN(MSG_ONE, gmsgSetFOV, nullptr, pev);
		WRITE_BYTE(fov);
	MESSAGE_END();
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, Killed, (entvars_t *pevAttacker, int iGib), pevAttacker, iGib)

void EXT_FUNC CBasePlayer::__API_HOOK(Killed)(entvars_t *pevAttacker, int iGib)
{
	m_canSwitchObserverModes = false;

	if (m_LastHitGroup == HITGROUP_HEAD)
		m_bHeadshotKilled = true;

	CBaseEntity *pAttackerEntity = CBaseEntity::Instance(pevAttacker);

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_DIED, this, pAttackerEntity);
	}

	if (CSGameRules()->IsCareer())
	{
		bool killerHasShield = false;
		bool wasBlind = false;

		if (TheCareerTasks)
		{
			if (!IsBot())
			{
				TheCareerTasks->HandleEvent(EVENT_DIE, nullptr, this);
			}

			TheCareerTasks->HandleDeath(m_iTeam, this);

#ifdef REGAMEDLL_FIXES
			if (!m_bKilledByBomb)
			{
				CBasePlayer *pAttacker = CBasePlayer::Instance(pevAttacker);

				if(pAttacker /*safety*/ && !pAttacker->IsBot() && pAttacker->m_iTeam != m_iTeam)
				{
					if (pAttacker->HasShield())
						killerHasShield = true;

					if (IsBot() && IsBlind()) // dystopm: shouldn't be !IsBot() ?
						wasBlind = true;

					TheCareerTasks->HandleEnemyKill(wasBlind, GetKillerWeaponName(GetLastInflictor(), pevAttacker), m_bHeadshotKilled, killerHasShield, pAttacker, this); // last 2 param swapped to match function definition
				}
			}
#endif
		}

#ifndef REGAMEDLL_FIXES
		if (!m_bKilledByBomb)
		{
			CBasePlayer *pAttacker = CBasePlayer::Instance(pevAttacker);

			if (pAttacker->HasShield())
				killerHasShield = true;

			if (IsBot() && IsBlind())
			{
				wasBlind = true;
			}

			for (int i = 1; i <= gpGlobals->maxClients; i++)
			{
				CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

				if (!UTIL_IsValidPlayer(pPlayer))
					continue;

				bool killedByHumanPlayer = (!pPlayer->IsBot() && pPlayer->pev == pevAttacker && pPlayer->m_iTeam != m_iTeam);
				if (killedByHumanPlayer)
				{
					if (TheCareerTasks)
					{
						TheCareerTasks->HandleEnemyKill(wasBlind, GetKillerWeaponName(GetLastInflictor(), pevAttacker), m_bHeadshotKilled, killerHasShield, this, pPlayer);
					}
				}
			}
		}
#endif
	}

	if (!m_bKilledByBomb)
	{
		g_pGameRules->PlayerKilled(this, pevAttacker, GetLastInflictor());
	}

	MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pev);
		WRITE_BYTE(0);
	MESSAGE_END();

	m_bNightVisionOn = false;

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pObserver = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pObserver))
			continue;

		if (pObserver->IsObservingPlayer(this))
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pObserver->pev);
				WRITE_BYTE(0);
			MESSAGE_END();

			pObserver->m_bNightVisionOn = false;
		}

#ifdef REGAMEDLL_FIXES
		if (pObserver->m_hObserverTarget == this)
			pObserver->m_flNextFollowTime = 0.0f;
#endif
	}

	if (m_pTank)
	{
		m_pTank->Use(this, this, USE_OFF, 0);
		m_pTank = nullptr;
	}

#ifndef REGAMEDLL_FIXES
	CSound *pSound = CSoundEnt::SoundPointerForIndex(CSoundEnt::ClientSoundIndex(edict()));

	if (pSound)
	{
		pSound->Reset();
	}
#endif
	SetAnimation(PLAYER_DIE);

	if (m_pActiveItem && m_pActiveItem->m_pPlayer)
	{
		switch (m_pActiveItem->m_iId)
		{
		case WEAPON_HEGRENADE:
		{
			CHEGrenade *pHEGrenade = static_cast<CHEGrenade *>(m_pActiveItem);
			if ((pev->button & IN_ATTACK) && m_rgAmmo[pHEGrenade->m_iPrimaryAmmoType])
			{
				ThrowGrenade(pHEGrenade, (pev->origin + pev->view_ofs), pev->angles, 1.5, pHEGrenade->m_usCreateExplosion);

#ifdef REGAMEDLL_FIXES
				m_rgAmmo[m_pActiveItem->PrimaryAmmoIndex()]--;
				pHEGrenade->m_flStartThrow = 0;
#endif
			}
			break;
		}
		case WEAPON_FLASHBANG:
		{
			CFlashbang *pFlashbang = static_cast<CFlashbang *>(m_pActiveItem);
			if ((pev->button & IN_ATTACK) && m_rgAmmo[pFlashbang->m_iPrimaryAmmoType])
			{
				ThrowGrenade(pFlashbang, (pev->origin + pev->view_ofs), pev->angles, 1.5);

#ifdef REGAMEDLL_FIXES
				m_rgAmmo[m_pActiveItem->PrimaryAmmoIndex()]--;
				pFlashbang->m_flStartThrow = 0;
#endif
			}
			break;
		}
		case WEAPON_SMOKEGRENADE:
		{
			CSmokeGrenade *pSmoke = static_cast<CSmokeGrenade *>(m_pActiveItem);
			if ((pev->button & IN_ATTACK) && m_rgAmmo[pSmoke->m_iPrimaryAmmoType])
			{
				ThrowGrenade(pSmoke, (pev->origin + pev->view_ofs), pev->angles, 1.5, pSmoke->m_usCreateSmoke);

#ifdef REGAMEDLL_FIXES
				m_rgAmmo[m_pActiveItem->PrimaryAmmoIndex()]--;
				pSmoke->m_flStartThrow = 0;
#endif
			}
			break;
		}
		default:
			break;
		}
	}

	pev->modelindex = m_modelIndexPlayer;
	pev->deadflag = DEAD_DYING;
	pev->movetype = MOVETYPE_TOSS;
	pev->takedamage = DAMAGE_NO;

	pev->gamestate = HITGROUP_SHIELD_DISABLED;
	m_bShieldDrawn = false;

	pev->flags &= ~FL_ONGROUND;

#ifdef REGAMEDLL_FIXES
	// FlashlightTurnOff()
	pev->effects &= ~EF_DIMLIGHT;
#endif

#ifndef REGAMEDLL_ADD
	if (fadetoblack.value == 0.0)
	{
		pev->iuser1 = OBS_CHASE_FREE;
		pev->iuser2 = ENTINDEX(edict());
		pev->iuser3 = ENTINDEX(ENT(pevAttacker));

		m_hObserverTarget = UTIL_PlayerByIndexSafe(pev->iuser3);

		MESSAGE_BEGIN(MSG_ONE, gmsgADStop, nullptr, pev);
		MESSAGE_END();
	}
	else
	{
		UTIL_ScreenFade(this, Vector(0, 0, 0), 3, 3, 255, (FFADE_OUT | FFADE_STAYOUT));
	}
#else

	float flDyingDuration = GetSequenceDuration() + CGameRules::GetDyingTime();
	switch ((int)fadetoblack.value)
	{
	default:
	{
		pev->iuser1 = OBS_CHASE_FREE;
		pev->iuser2 = ENTINDEX(edict());
		pev->iuser3 = ENTINDEX(ENT(pevAttacker));

		m_hObserverTarget = UTIL_PlayerByIndexSafe(pev->iuser3);

		MESSAGE_BEGIN(MSG_ONE, gmsgADStop, nullptr, pev);
		MESSAGE_END();

		break;
	}
	case FADETOBLACK_STAY:
	{
		UTIL_ScreenFade(this, Vector(0, 0, 0), 0.8f, flDyingDuration, 255, (FFADE_OUT | FFADE_STAYOUT));
		break;
	}
	case FADETOBLACK_AT_DYING:
	{
		pev->iuser1 = OBS_CHASE_FREE;
		pev->iuser2 = ENTINDEX(edict());
		pev->iuser3 = ENTINDEX(ENT(pevAttacker));

		m_hObserverTarget = UTIL_PlayerByIndexSafe(pev->iuser3);

		MESSAGE_BEGIN(MSG_ONE, gmsgADStop, nullptr, pev);
		MESSAGE_END();

		UTIL_ScreenFade(this, Vector(0, 0, 0), 0.8f, flDyingDuration, 255, (FFADE_OUT));

		break;
	}
	}
#endif // REGAMEDLL_ADD

	SetScoreboardAttributes();

	if (m_iThrowDirection)
	{
		switch (m_iThrowDirection)
		{
		case THROW_FORWARD:
		{
			UTIL_MakeVectors(pev->angles);
			pev->velocity = gpGlobals->v_forward * RANDOM_FLOAT(100, 200);
			pev->velocity.z = RANDOM_FLOAT(50, 100);
			break;
		}
		case THROW_BACKWARD:
		{
			UTIL_MakeVectors(pev->angles);
			pev->velocity = gpGlobals->v_forward * RANDOM_FLOAT(-100, -200);
			pev->velocity.z = RANDOM_FLOAT(50, 100);
			break;
		}
		case THROW_HITVEL:
		{
			if (FClassnameIs(pevAttacker, "player"))
			{
				UTIL_MakeVectors(pevAttacker->angles);

				pev->velocity = gpGlobals->v_forward * RANDOM_FLOAT(200, 300);
				pev->velocity.z = RANDOM_FLOAT(200, 300);
			}
			break;
		}
		case THROW_BOMB:
		{
			// TODO: fix test demo
			pev->velocity = m_vBlastVector * (1.0f / m_vBlastVector.Length()) * float(2300.0f - m_vBlastVector.Length()) * 0.25f;
			pev->velocity.z = (2300.0f - m_vBlastVector.Length()) / 2.75f;
			break;
		}
		case THROW_GRENADE:
		{
			pev->velocity = m_vBlastVector * (1 / m_vBlastVector.Length()) * (500 - m_vBlastVector.Length());
			pev->velocity.z = (350 - m_vBlastVector.Length()) * 1.5;
			break;
		}
		case THROW_HITVEL_MINUS_AIRVEL:
		{
			if (FClassnameIs(pevAttacker, "player"))
			{
				UTIL_MakeVectors(pevAttacker->angles);
				pev->velocity = gpGlobals->v_forward * RANDOM_FLOAT(200, 300);
			}
			break;
		}
		default:
			break;
		}

		pev->angles.y = UTIL_VecToAngles(-pev->velocity).y;
		pev->v_angle.y = pev->angles.y;

		m_iThrowDirection = THROW_NONE;
	}

	SetSuitUpdate(nullptr, SUIT_SENTENCE, SUIT_REPEAT_OK);

	m_iClientHealth = 0;
	MESSAGE_BEGIN(MSG_ONE, gmsgHealth, nullptr, pev);
		WRITE_BYTE(m_iClientHealth);
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, nullptr, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(0xFF);
		WRITE_BYTE(0xFF);
	MESSAGE_END();

	SendFOV(0);

	CSGameRules()->CheckWinConditions();
	m_bNotKilled = false;

	if (m_bHasC4)
	{
		DropPlayerItem("weapon_c4");

#ifndef REGAMEDLL_FIXES
		// NOTE: It is already does reset inside DropPlayerItem
		SetProgressBarTime(0);
#endif
	}
	else if (m_bHasDefuser)
	{
		RemoveDefuser();
#ifdef REGAMEDLL_FIXES
		SpawnDefuser(pev->origin, ENT(pev));
#else
		GiveNamedItem("item_thighpack");
#endif
	}

#ifndef REGAMEDLL_FIXES
	// NOTE: moved to RemoveDefuser
	m_bIsDefusing = false;
#endif

	BuyZoneIcon_Clear(this);

#ifdef REGAMEDLL_ADD
	CSPlayer()->OnKilled();
#endif

	SetThink(&CBasePlayer::PlayerDeathThink);
	pev->nextthink = gpGlobals->time + 0.1f;
	pev->solid = SOLID_NOT;

	if (m_bPunishedForTK)
	{
		m_bPunishedForTK = false;
		HintMessage("#Hint_cannot_play_because_tk", TRUE, TRUE);
	}

	if (ShouldGibPlayer(iGib))
	{

#ifndef REGAMEDLL_FIXES
		pev->solid = SOLID_NOT;
#endif
		GibMonster();
		pev->effects |= EF_NODRAW;

#ifndef REGAMEDLL_FIXES
		CSGameRules()->CheckWinConditions();
#endif
		return;
	}

	DeathSound();

	pev->angles.x = 0;
	pev->angles.z = 0;

	if (!(m_flDisplayHistory & DHF_SPEC_DUCK))
	{
		HintMessage("#Spec_Duck", TRUE, TRUE);
		m_flDisplayHistory |= DHF_SPEC_DUCK;
	}
}

BOOL CBasePlayer::IsBombGuy()
{
	if (!g_pGameRules->IsMultiplayer())
		return FALSE;

	return m_bHasC4;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, SetAnimation, (PLAYER_ANIM playerAnim), playerAnim)

void EXT_FUNC CBasePlayer::__API_HOOK(SetAnimation)(PLAYER_ANIM playerAnim)
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
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_PLAYER_JUMPED, this);
				}
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
#ifndef REGAMEDLL_FIXES
			DeathSound();
#endif
			break;
		}
		case PLAYER_ATTACK1:
		{
			if (m_Activity == ACT_SWIM || m_Activity == ACT_DIESIMPLE || m_Activity == ACT_HOVER)
				m_IdealActivity = m_Activity;
			else
			{
				m_IdealActivity = ACT_RANGE_ATTACK1;
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_WEAPON_FIRED, this);
				}
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
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_WEAPON_FIRED, this);
				}
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
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_WEAPON_RELOADED, this);
				}
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
			case ACT_RANGE_ATTACK1:	Q_strcpy(szAnim, "ref_shoot_"); break;
			case ACT_RANGE_ATTACK2:	Q_strcpy(szAnim, "ref_shoot2_"); break;
			case ACT_RELOAD:	Q_strcpy(szAnim, "ref_reload_"); break;
			default:		Q_strcpy(szAnim, "ref_aim_"); break;
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
						// TODO: maybe away used variable 'speed'?
						//if (speed > 150.0f)
						if (pev->velocity.Length2D() > 150.0f)
						{
							if (TheBots)
							{
								TheBots->OnEvent(EVENT_PLAYER_FOOTSTEP, this);
							}
						}
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
#endif

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
						animDesired = LookupActivity(ACT_DIESIMPLE);
						break;
					}
					break;
				}
				case HITGROUP_HEAD:
				{
					int random = RANDOM_LONG(0, 8);
					m_bHeadshotKilled = true;

					if (m_bHighDamage)
						random++;

					switch (random)
					{
					case 1:
					case 2:
						m_iThrowDirection = THROW_BACKWARD;
						break;
					case 3:
					case 4:
#ifndef REGAMEDLL_FIXES
						m_iThrowDirection = THROW_FORWARD;
						break;
#endif
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
					animDesired = LookupActivity(ACT_DIESIMPLE);
					break;
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

void CBasePlayer::WaterMove()
{
	int air;

	if (pev->movetype == MOVETYPE_NOCLIP || pev->movetype == MOVETYPE_NONE)
		return;

#ifdef REGAMEDLL_FIXES
	if (!IsAlive())
		return;
#else
	if (pev->health < 0.0f)
		return;
#endif

	// waterlevel 0 - not in water
	// waterlevel 1 - feet in water
	// waterlevel 2 - waist in water
	// waterlevel 3 - head in water
	if (pev->waterlevel != 3)
	{
		// not underwater

		// play 'up for air' sound
#ifdef REGAMEDLL_FIXES
		if (pev->flags & FL_INWATER)
#endif
		{
			if (pev->air_finished < gpGlobals->time)
				EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/pl_wade1.wav", VOL_NORM, ATTN_NORM);

			else if (pev->air_finished < gpGlobals->time + 9)
				EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/pl_wade2.wav", VOL_NORM, ATTN_NORM);
		}

		pev->air_finished = gpGlobals->time + AIRTIME;
		pev->dmg = 2;

		// if we took drowning damage, give it back slowly
		if (m_idrowndmg > m_idrownrestored)
		{
			// set drowning damage bit.  hack - dmg_drownrecover actually
			// makes the time based damage code 'give back' health over time.
			// make sure counter is cleared so we start count correctly.

			// NOTE: this actually causes the count to continue restarting
			// until all drowning damage is healed.
			m_rgbTimeBasedDamage[ITBD_DROWN_RECOVER] = 0;
			m_bitsDamageType |= DMG_DROWNRECOVER;
			m_bitsDamageType &= ~DMG_DROWN;
		}
	}
	else
	{
		// fully under water
		// stop restoring damage while underwater
		m_rgbTimeBasedDamage[ITBD_DROWN_RECOVER] = 0;
		m_bitsDamageType &= ~DMG_DROWNRECOVER;

		// drown!
		if (gpGlobals->time > pev->air_finished)
		{
			if (gpGlobals->time > pev->pain_finished)
			{
				// take drowning damage
				pev->dmg += 1;

				if (pev->dmg > 5)
					pev->dmg = 5;

				TakeDamage(VARS(eoNullEntity), VARS(eoNullEntity), pev->dmg, DMG_DROWN);

#ifdef REGAMEDLL_FIXES
				// NOTE: If we died after the damage of above and was followed respawn,
				// so we should get out of code.
				if (!(m_bitsDamageType & DMG_DROWN))
					return;
#endif

				pev->pain_finished = gpGlobals->time + 1;

				// track drowning damage, give it back when
				// player finally takes a breath
				m_idrowndmg += pev->dmg;
			}
		}
		else
			m_bitsDamageType &= ~(DMG_DROWNRECOVER | DMG_DROWN);
	}

	if (!pev->waterlevel)
	{
		if (pev->flags & FL_INWATER)
			pev->flags &= ~FL_INWATER;

		return;
	}

	// make bubbles
	air = int(pev->air_finished - gpGlobals->time);

	if (!RANDOM_LONG(0, 0x1f) && RANDOM_LONG(0, AIRTIME - 1) >= air)
	{
		switch (RANDOM_LONG(0, 3))
		{
		case 0: EMIT_SOUND(ENT(pev), CHAN_BODY, "player/pl_swim1.wav", 0.8, ATTN_NORM); break;
		case 1: EMIT_SOUND(ENT(pev), CHAN_BODY, "player/pl_swim2.wav", 0.8, ATTN_NORM); break;
		case 2: EMIT_SOUND(ENT(pev), CHAN_BODY, "player/pl_swim3.wav", 0.8, ATTN_NORM); break;
		case 3: EMIT_SOUND(ENT(pev), CHAN_BODY, "player/pl_swim4.wav", 0.8, ATTN_NORM); break;
		}
	}

	if (pev->watertype == CONTENT_LAVA)		// do damage
	{
		if (pev->dmgtime < gpGlobals->time)
			TakeDamage(VARS(eoNullEntity), VARS(eoNullEntity), pev->waterlevel * 10, DMG_BURN);
	}
	else if (pev->watertype == CONTENT_SLIME)	// do damage
	{
		pev->dmgtime = gpGlobals->time + 1;
		TakeDamage(VARS(eoNullEntity), VARS(eoNullEntity), pev->waterlevel * 4, DMG_ACID);
	}
	if (!(pev->flags & FL_INWATER))
	{
		pev->flags |= FL_INWATER;
		pev->dmgtime = 0;
	}
}

BOOL CBasePlayer::IsOnLadder()
{
	return pev->movetype == MOVETYPE_FLY;
}

NOXREF void CBasePlayer::ThrowWeapon(char *pszItemName)
{
	for (int i = 0; i < MAX_WEAPON_SLOTS; i++)
	{
		CBasePlayerItem *pWeapon = m_rgpPlayerItems[i];

		while (pWeapon)
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

LINK_ENTITY_TO_CLASS(weapon_shield, CWShield, CCSShield)

void CWShield::Spawn()
{
	pev->movetype = MOVETYPE_TOSS;
	pev->solid = SOLID_TRIGGER;

	UTIL_SetSize(pev, g_vecZero, g_vecZero);
	SET_MODEL(ENT(pev), "models/w_shield.mdl");
}

void CWShield::Touch(CBaseEntity *pOther)
{
	if (!pOther->IsPlayer())
		return;

	CBasePlayer *pPlayer = (CBasePlayer *)pOther;

	if (pPlayer->pev->deadflag != DEAD_NO)
		return;

	if (m_hEntToIgnoreTouchesFrom && m_hEntToIgnoreTouchesFrom == pPlayer)
	{
		if (m_flTimeToIgnoreTouches > gpGlobals->time)
			return;

		m_hEntToIgnoreTouchesFrom = nullptr;
	}

	if (!pPlayer->m_bHasPrimary)
	{
		if (pPlayer->m_rgpPlayerItems[PISTOL_SLOT] && pPlayer->m_rgpPlayerItems[PISTOL_SLOT]->m_iId == WEAPON_ELITE)
			return;

		if (pPlayer->m_pActiveItem)
		{
			if (!pPlayer->m_pActiveItem->CanHolster())
				return;
		}

		if (!pPlayer->m_bIsVIP)
		{
#ifdef REGAMEDLL_ADD
			if (pPlayer->HasRestrictItem(ITEM_SHIELDGUN, ITEM_TYPE_TOUCHED))
				return;
#endif
			pPlayer->GiveShield();

			EMIT_SOUND(edict(), CHAN_ITEM, "items/gunpickup2.wav", VOL_NORM, ATTN_NORM);
			UTIL_Remove(this);

			pev->nextthink = gpGlobals->time + 0.1;
		}
	}
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, GiveShield, (bool bDeploy), bDeploy)

void EXT_FUNC CBasePlayer::__API_HOOK(GiveShield)(bool bDeploy)
{
	m_bOwnsShield = true;
	m_bHasPrimary = true;

#ifdef REGAMEDLL_FIXES
	pev->gamestate = HITGROUP_SHIELD_ENABLED;
#endif

	if (m_pActiveItem)
	{
		CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(m_pActiveItem);

		if (bDeploy)
		{
			if (m_rgAmmo[pWeapon->m_iPrimaryAmmoType] > 0)
				pWeapon->Holster();

			if (!pWeapon->Deploy())
				pWeapon->RetireWeapon();
		}
	}

#ifndef REGAMEDLL_FIXES
	// NOTE: Moved above, because CC4::Deploy can reset hitbox of shield
	pev->gamestate = HITGROUP_SHIELD_ENABLED;
#endif
}

void CBasePlayer::RemoveShield()
{
	if (HasShield())
	{
		m_bOwnsShield = false;
		m_bHasPrimary = false;
		m_bShieldDrawn = false;
		pev->gamestate = HITGROUP_SHIELD_DISABLED;

		UpdateShieldCrosshair(true);
	}
}

LINK_HOOK_CLASS_CHAIN(CBaseEntity *, CBasePlayer, DropShield, (bool bDeploy), bDeploy)

CBaseEntity *EXT_FUNC CBasePlayer::__API_HOOK(DropShield)(bool bDeploy)
{
	if (!HasShield())
		return nullptr;

	if (m_pActiveItem && !m_pActiveItem->CanHolster())
		return nullptr;

	CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(m_pActiveItem);

	if (pWeapon)
	{
		if (pWeapon->m_iId == WEAPON_HEGRENADE || pWeapon->m_iId == WEAPON_FLASHBANG || pWeapon->m_iId == WEAPON_SMOKEGRENADE)
		{
			if (m_rgAmmo[pWeapon->m_iPrimaryAmmoType] <= 0)
				g_pGameRules->GetNextBestWeapon(this, pWeapon);
		}
	}

	if (m_pActiveItem)
	{
		if (m_pActiveItem->m_flStartThrow != 0.0f)
			m_pActiveItem->Holster();
	}

	if (IsReloading())
	{
		pWeapon->m_fInReload = FALSE;
		m_flNextAttack = 0;
	}

	if (m_pActiveItem && IsProtectedByShield())
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
	pShield->pev->nextthink = gpGlobals->time + CGameRules::GetItemKillDelay();
	pShield->SetCantBePickedUpByUser(this, 2.0);

	return pShield;
}

bool CBasePlayer::HasShield()
{
	return m_bOwnsShield;
}

NOXREF void CBasePlayer::ThrowPrimary()
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

	DropShield();
}

LINK_HOOK_CLASS_CHAIN(CGrenade *, CBasePlayer, ThrowGrenade, (CBasePlayerWeapon *pWeapon, Vector vecSrc, Vector vecThrow, float time, unsigned short usEvent), pWeapon, vecSrc, vecThrow, time, usEvent)

CGrenade *CBasePlayer::__API_HOOK(ThrowGrenade)(CBasePlayerWeapon *pWeapon, VectorRef vecSrc, VectorRef vecThrow, float time, unsigned short usEvent)
{
	switch (pWeapon->m_iId)
	{
	case WEAPON_HEGRENADE:    return CGrenade::ShootTimed2(pev, vecSrc, vecThrow, time, m_iTeam, usEvent);
	case WEAPON_FLASHBANG:    return CGrenade::ShootTimed(pev, vecSrc, vecThrow, time);
	case WEAPON_SMOKEGRENADE: return CGrenade::ShootSmokeGrenade(pev, vecSrc, vecThrow, time, usEvent);
	}

	return nullptr;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, AddAccount, (int amount, RewardType type, bool bTrackChange), amount, type, bTrackChange)

#ifdef REGAMEDLL_ADD
void EXT_FUNC CBasePlayer::__API_HOOK(AddAccount)(int amount, RewardType type, bool bTrackChange)
{
	bool bSendMoney = true;
	switch (type)
	{
	case RT_INTO_GAME:
	case RT_PLAYER_JOIN:
		bSendMoney = false;
	case RT_PLAYER_RESET:
	case RT_PLAYER_SPEC_JOIN:
		m_iAccount = 0;
		break;
	}

	m_iAccount += amount;

	if (bSendMoney)
	{
		m_iAccount = clamp<int>(m_iAccount, 0, maxmoney.value);

		// Send money update to HUD
		MESSAGE_BEGIN(MSG_ONE, gmsgMoney, nullptr, pev);
			WRITE_LONG(m_iAccount);
			WRITE_BYTE(bTrackChange);
		MESSAGE_END();
	}
}
#else
void EXT_FUNC CBasePlayer::__API_HOOK(AddAccount)(int amount, RewardType type, bool bTrackChange)
{
	m_iAccount += amount;

	if (m_iAccount > 16000)
		m_iAccount = 16000;

	else if (m_iAccount < 0)
		m_iAccount = 0;

	// Send money update to HUD
	MESSAGE_BEGIN(MSG_ONE, gmsgMoney, nullptr, pev);
		WRITE_LONG(m_iAccount);
		WRITE_BYTE(bTrackChange);
	MESSAGE_END();
}
#endif

void CBasePlayer::ResetMenu()
{
#ifdef REGAMEDLL_FIXES
	m_iMenu = Menu_OFF;
#endif

	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, nullptr, pev);
		WRITE_SHORT(0);
		WRITE_CHAR(0);
		WRITE_BYTE(0);
		WRITE_STRING("");
	MESSAGE_END();
}

void CBasePlayer::SyncRoundTimer()
{
	float tmRemaining = 0;
	BOOL bFreezePeriod = g_pGameRules->IsFreezePeriod();

	if (g_pGameRules->IsMultiplayer())
	{
		tmRemaining = CSGameRules()->GetRoundRemainingTimeReal();

#ifdef REGAMEDLL_FIXES
		// hide timer HUD because it is useless.
		if (tmRemaining <= 0.0f && CSGameRules()->m_iRoundTime <= 0) {
			m_iHideHUD |= HIDEHUD_TIMER;
			return;
		}

		if (m_iHideHUD & HIDEHUD_TIMER)
		{
			m_iHideHUD &= ~HIDEHUD_TIMER;
			MESSAGE_BEGIN(MSG_ONE, gmsgShowTimer, nullptr, pev);
			MESSAGE_END();
		}
#endif
	}

	if (tmRemaining < 0)
		tmRemaining = 0;

	MESSAGE_BEGIN(MSG_ONE, gmsgRoundTime, nullptr, pev);
		WRITE_SHORT(int(tmRemaining));
	MESSAGE_END();

	if (!g_pGameRules->IsMultiplayer())
		return;

	if (bFreezePeriod && TheTutor && GetObserverMode() == OBS_NONE)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgBlinkAcct, nullptr, pev);
			WRITE_BYTE(MONEY_BLINK_AMOUNT);
		MESSAGE_END();
	}

	if (TheCareerTasks && CSGameRules()->IsCareer())
	{
		int remaining = 0;
		bool shouldCountDown = false;
		int fadeOutDelay = 0;

		if (tmRemaining != 0.0f)
		{
			remaining = TheCareerTasks->GetTaskTime() - (gpGlobals->time - CSGameRules()->m_fRoundStartTime);
		}

		if (remaining < 0)
			remaining = 0;

		if (bFreezePeriod)
			remaining = -1;

		if (TheCareerTasks->GetFinishedTaskTime())
			remaining = -TheCareerTasks->GetFinishedTaskTime();

		if (!bFreezePeriod && !TheCareerTasks->GetFinishedTaskTime())
		{
			shouldCountDown = true;
		}
		if (!bFreezePeriod)
		{
			if (TheCareerTasks->GetFinishedTaskTime() || (TheCareerTasks->GetTaskTime() <= TheCareerTasks->GetRoundElapsedTime()))
			{
				fadeOutDelay = 3;
			}
		}

		if (!TheCareerTasks->GetFinishedTaskTime() || TheCareerTasks->GetFinishedTaskRound() == CSGameRules()->m_iTotalRoundsPlayed)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgTaskTime, nullptr, pev);
				WRITE_SHORT(remaining);			// remaining of time, -1 the timer is disappears
				WRITE_BYTE(shouldCountDown);	// timer counts down
				WRITE_BYTE(fadeOutDelay); 		// fade in time, hide HUD timer after the expiration time
			MESSAGE_END();
		}
	}
}

void CBasePlayer::RemoveLevelText()
{
	ResetMenu();
}

void ShowMenu2(CBasePlayer *pPlayer, int bitsValidSlots, int nDisplayTime, int fNeedMore, char *pszText)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, nullptr, pPlayer->pev);
		WRITE_SHORT(bitsValidSlots);
		WRITE_CHAR(nDisplayTime);
		WRITE_BYTE(fNeedMore);
		WRITE_STRING(pszText);
	MESSAGE_END();
}

void CBasePlayer::MenuPrint(const char *msg)
{
	const char *msg_portion = msg;
	char sbuf[MAX_BUFFER_MENU_BRIEFING + 1];

	while (Q_strlen(msg_portion) >= MAX_BUFFER_MENU_BRIEFING)
	{
		Q_strncpy(sbuf, msg_portion, MAX_BUFFER_MENU_BRIEFING);
		sbuf[MAX_BUFFER_MENU_BRIEFING] = '\0';
		msg_portion += MAX_BUFFER_MENU_BRIEFING;

		MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, nullptr, pev);
			WRITE_SHORT(0xFFFF);
			WRITE_CHAR(-1);
			WRITE_BYTE(1);	// multipart
			WRITE_STRING(sbuf);
		MESSAGE_END();
	}

	MESSAGE_BEGIN(MSG_ONE, gmsgShowMenu, nullptr, pev);
		WRITE_SHORT(0xFFFF);
		WRITE_CHAR(-1);
		WRITE_BYTE(0);	// multipart
		WRITE_STRING(msg_portion);
	MESSAGE_END();
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, MakeVIP)

void EXT_FUNC CBasePlayer::__API_HOOK(MakeVIP)()
{
	pev->body = 0;
	m_iModelName = MODEL_VIP;

	SetClientUserInfoModel(GET_INFO_BUFFER(edict()), "vip");
	UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Became_VIP\"\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()));

	m_iTeam = CT;
	m_bIsVIP = true;
	m_bNotKilled = false;

	CSGameRules()->m_pVIP = this;
	CSGameRules()->m_iConsecutiveVIP = 1;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, JoiningThink)

void EXT_FUNC CBasePlayer::__API_HOOK(JoiningThink)()
{
	switch (m_iJoiningState)
	{
		case JOINED:
		{
			return;
		}
		case SHOWLTEXT:
		{
			ResetMenu();
			m_iJoiningState = SHOWTEAMSELECT;

#ifndef REGAMEDLL_FIXES
			// NOTE: client already clears StatusIcon on join
			MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
				WRITE_BYTE(STATUSICON_HIDE);
				WRITE_STRING("defuser");
			MESSAGE_END();

			m_bHasDefuser = false; // set in ClientPutInServer
#endif
			m_fLastMovement = gpGlobals->time;
			m_bMissionBriefing = false;

			SendItemStatus();  // NOTE: must be on UpdateClientData

			break;
		}
		case READINGLTEXT:
		{
			if (m_afButtonPressed & (IN_ATTACK | IN_ATTACK2 | IN_JUMP))
			{
				m_afButtonPressed &= ~(IN_ATTACK | IN_ATTACK2 | IN_JUMP);

				RemoveLevelText();
				m_iJoiningState = SHOWTEAMSELECT;
			}
			break;
		}
		case GETINTOGAME:
		{
			if (GetIntoGame()) {
				return;
			}

			break;
		}
	}

	if (m_pIntroCamera && gpGlobals->time >= m_fIntroCamTime
#ifdef REGAMEDLL_FIXES
		&& m_fIntroCamTime > 0.0 // update only if cameras are available
#endif
		)
	{
		// find the next another camera
		m_pIntroCamera = UTIL_FindEntityByClassname(m_pIntroCamera, "trigger_camera");

		// could not find, go back to the start
		if (!m_pIntroCamera)
		{
			m_pIntroCamera = UTIL_FindEntityByClassname(nullptr, "trigger_camera");
		}

		CBaseEntity *Target = UTIL_FindEntityByTargetname(nullptr, STRING(m_pIntroCamera->pev->target));
		if (Target)
		{
			Vector vecAngles = UTIL_VecToAngles((Target->pev->origin - m_pIntroCamera->pev->origin).Normalize());

			vecAngles.x = -vecAngles.x;
			UTIL_SetOrigin(pev, m_pIntroCamera->pev->origin);

			pev->angles = vecAngles;
			pev->v_angle = pev->angles;

			pev->velocity = g_vecZero;
			pev->punchangle = g_vecZero;

			pev->fixangle = 1;
			pev->view_ofs = g_vecZero;
			m_fIntroCamTime = gpGlobals->time + 6;
		}
		else
			m_pIntroCamera = nullptr;
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, Disappear)

void EXT_FUNC CBasePlayer::__API_HOOK(Disappear)()
{
	if (m_pTank)
	{
		m_pTank->Use(this, this, USE_OFF, 0);
		m_pTank = nullptr;
	}

#ifndef REGAMEDLL_FIXES
	CSound *pSound = CSoundEnt::SoundPointerForIndex(CSoundEnt::ClientSoundIndex(edict()));

	if (pSound)
	{
		pSound->Reset();
	}
#endif

	m_fSequenceFinished = TRUE;
	pev->modelindex = m_modelIndexPlayer;
	pev->view_ofs = Vector(0, 0, -8);
	pev->deadflag = DEAD_DYING;
	pev->solid = SOLID_NOT;
	pev->flags &= ~FL_ONGROUND;

#ifdef REGAMEDLL_FIXES
	// FlashlightTurnOff()
	pev->effects &= ~EF_DIMLIGHT;
#endif

	SetSuitUpdate(nullptr, SUIT_SENTENCE, SUIT_REPEAT_OK);

	m_iClientHealth = 0;
	MESSAGE_BEGIN(MSG_ONE, gmsgHealth, nullptr, pev);
		WRITE_BYTE(m_iClientHealth);
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, nullptr, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(0xFF);
		WRITE_BYTE(0xFF);
	MESSAGE_END();

	SendFOV(0);

	CSGameRules()->CheckWinConditions();
	m_bNotKilled = false;

	if (m_bHasC4)
	{
		DropPlayerItem("weapon_c4");

#ifndef REGAMEDLL_FIXES
		// NOTE: It is already does reset inside DropPlayerItem
		SetProgressBarTime(0);
#endif
	}
	else if (m_bHasDefuser)
	{
		RemoveDefuser();
#ifdef REGAMEDLL_FIXES
		SpawnDefuser(pev->origin, ENT(pev));
#else
		GiveNamedItem("item_thighpack");
#endif
	}

	BuyZoneIcon_Clear(this);

	SetThink(&CBasePlayer::PlayerDeathThink);
	pev->nextthink = gpGlobals->time + 0.1f;

	pev->angles.x = 0;
	pev->angles.z = 0;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, PlayerDeathThink)

void EXT_FUNC CBasePlayer::__API_HOOK(PlayerDeathThink)()
{
	if (m_iJoiningState != JOINED)
		return;

	// If the anim is done playing, go to the next state (waiting for a keypress to
	// either respawn the guy or put him into observer mode).
	if (pev->flags & FL_ONGROUND)
	{
		float flForward = pev->velocity.Length() - 20;
		if (flForward <= 0)
			pev->velocity = g_vecZero;
		else
			pev->velocity = flForward * pev->velocity.Normalize();
	}

	if (HasWeapons())
	{
		// we drop the guns here because weapons that have an area effect and can kill their user
		// will sometimes crash coming back from CBasePlayer::Killed() if they kill their owner because the
		// player class sometimes is freed. It's safer to manipulate the weapons once we know
		// we aren't calling into any of their code anymore through the player pointer.
		PackDeadPlayerItems();
	}

#ifdef REGAMEDLL_FIXES
	// Clear inclination came from client view
	pev->angles.x = 0;
#endif

	if (pev->modelindex && !m_fSequenceFinished && pev->deadflag == DEAD_DYING)
	{
		StudioFrameAdvance();
		return;
	}

	// once we're done animating our death and we're on the ground, we want to set movetype to None so our dead body won't do collisions and stuff anymore
	// this prevents a bug where the dead body would go to a player's head if he walked over it while the dead player was clicking their button to respawn
	if (pev->movetype != MOVETYPE_NONE && (pev->flags & FL_ONGROUND))
		pev->movetype = MOVETYPE_NONE;

	if (pev->deadflag == DEAD_DYING)
	{
		// Used for a timer.
		m_fDeadTime = gpGlobals->time;
		pev->deadflag = DEAD_DEAD;
	}

	StopAnimation();
	pev->effects |= EF_NOINTERP;

	BOOL fAnyButtonDown = (pev->button & ~IN_SCORE);

#ifdef REGAMEDLL_FIXES
	// do not make a corpse if the player goes to respawn.
	if (pev->deadflag != DEAD_RESPAWNABLE)
#endif
	{
		// if the player has been dead for one second longer than allowed by forcerespawn,
		// forcerespawn isn't on. Send the player off to an intermission camera until they choose to respawn.
		if (g_pGameRules->IsMultiplayer() && HasTimePassedSinceDeath(CGameRules::GetDyingTime()) && !(m_afPhysicsFlags & PFLAG_OBSERVER))
		{
			// Send message to everybody to spawn a corpse.
			SpawnClientSideCorpse();

			// go to dead camera.
			StartDeathCam();
		}
	}

	// wait for all buttons released
	if (pev->deadflag == DEAD_DEAD && m_iTeam != UNASSIGNED && m_iTeam != SPECTATOR)
	{
		if (fAnyButtonDown)
			return;

		if (g_pGameRules->FPlayerCanRespawn(this))
		{
#ifdef REGAMEDLL_ADD
			if (forcerespawn.value <= 0 || (m_iTeam != CT && m_iTeam != TERRORIST))
#endif
			{
				pev->deadflag = DEAD_RESPAWNABLE;

				if (CSGameRules()->IsMultiplayer())
					CSGameRules()->CheckWinConditions();
			}
		}

		pev->nextthink = gpGlobals->time + 0.1f;
		return;
	}

#ifdef REGAMEDLL_ADD
	if (forcerespawn.value <= 0)
#endif
	{
		if (pev->deadflag == DEAD_RESPAWNABLE)
		{
#ifdef REGAMEDLL_FIXES
			if (GetObserverMode() != OBS_NONE && (m_iTeam == UNASSIGNED || m_iTeam == SPECTATOR))
				return;

			// Player cannot respawn while in the Choose Appearance menu
			if (m_iMenu == Menu_ChooseAppearance || m_iJoiningState == SHOWTEAMSELECT)
				return;
#endif

			// don't copy a corpse if we're in deathcam.
			respawn(pev, FALSE);
			pev->button = 0;
			pev->nextthink = -1;
		}
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, RoundRespawn)

void EXT_FUNC CBasePlayer::__API_HOOK(RoundRespawn)()
{
	m_canSwitchObserverModes = true;

	// teamkill punishment..
	if (m_bJustKilledTeammate && tkpunish.value)
	{
		m_bPunishedForTK = true;
		m_bJustKilledTeammate = false;

#ifndef REGAMEDLL_FIXES
		// TODO: wtf?
		CLIENT_COMMAND(edict(), "kill\n");
#endif
	}

	if (m_iMenu != Menu_ChooseAppearance)
	{
		respawn(pev);

		pev->button = 0;
		pev->nextthink = -1;
	}

	if (m_pActiveItem && m_pActiveItem->iItemSlot() == GRENADE_SLOT)
		SwitchWeapon(m_pActiveItem);

	m_lastLocation[0] = '\0';

#ifdef REGAMEDLL_FIXES
	if (m_bPunishedForTK && pev->health > 0)
		Kill();
#endif

}


LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, StartDeathCam)

// StartDeathCam - find an intermission spot and send the
// player off into observer mode
void EXT_FUNC CBasePlayer::__API_HOOK(StartDeathCam)()
{
#ifdef REGAMEDLL_FIXES
	m_canSwitchObserverModes = true;
#endif

	if (pev->view_ofs == g_vecZero)
	{
		// don't accept subsequent attempts to StartDeathCam()
		return;
	}

	StartObserver(pev->origin, pev->angles);

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_DEATH_CAMERA_START, this);
	}
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, StartObserver, (Vector &vecPosition, Vector &vecViewAngle), vecPosition, vecViewAngle)

void EXT_FUNC CBasePlayer::__API_HOOK(StartObserver)(Vector &vecPosition, Vector &vecViewAngle)
{
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
		m_pTank->Use(this, this, USE_OFF, 0);
		m_pTank = nullptr;
	}

	// clear out the suit message cache so we don't keep chattering
	SetSuitUpdate(nullptr, SUIT_SENTENCE, SUIT_REPEAT_OK);

	// Tell Ammo Hud that the player is dead
	MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, nullptr, pev);
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

	// set position and viewangle
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

	// Find a player to watch
	m_flNextObserverInput = 0;

	pev->iuser1 = OBS_NONE;

	static int iFirstTime = 1;
	if (iFirstTime != 0 && CSGameRules() && CSGameRules()->IsCareer() && !IsBot())
	{
		Observer_SetMode(OBS_CHASE_LOCKED);
		CLIENT_COMMAND(edict(), "spec_autodirector_internal 1\n");
		iFirstTime = 0;
	}
	else
		Observer_SetMode(m_iObserverLastMode);

	ResetMaxSpeed();

	// Tell all clients this player is now a spectator
	MESSAGE_BEGIN(MSG_ALL, gmsgSpectator);
		WRITE_BYTE(entindex());
		WRITE_BYTE(1);
	MESSAGE_END();
}

bool CanSeeUseable(CBasePlayer *me, CBaseEntity *pEntity)
{
	TraceResult result;
	Vector eye = me->pev->origin + me->pev->view_ofs;

	if (FClassnameIs(pEntity->pev, "hostage_entity"))
	{
		Vector chest = pEntity->pev->origin + Vector(0, 0, HalfHumanHeight);
		Vector head  = pEntity->pev->origin + Vector(0, 0, HumanHeight * 0.9);
		Vector knees = pEntity->pev->origin + Vector(0, 0, StepHeight);

		UTIL_TraceLine(eye, chest, ignore_monsters, ignore_glass, me->edict(), &result);
		if (result.flFraction < 1.0f)
		{
			UTIL_TraceLine(eye, head, ignore_monsters, ignore_glass, pEntity->edict(), &result);
			if (result.flFraction < 1.0f)
			{
				UTIL_TraceLine(eye, knees, ignore_monsters, ignore_glass, pEntity->edict(), &result);
				if (result.flFraction < 1.0f)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void CBasePlayer::PlayerUse()
{
	// Was use pressed or released?
	if (!((pev->button | m_afButtonPressed | m_afButtonReleased) & IN_USE))
		return;

	// Hit Use on a train?
	if (m_afButtonPressed & IN_USE)
	{
		if (m_pTank)
		{
			// Stop controlling the tank
			// TODO: Send HUD Update
			m_pTank->Use(this, this, USE_OFF, 0);
			m_pTank = nullptr;
			return;
		}

		if (m_afPhysicsFlags & PFLAG_ONTRAIN)
		{
			m_iTrain = (TRAIN_NEW | TRAIN_OFF);
			m_afPhysicsFlags &= ~PFLAG_ONTRAIN;

			CBaseEntity *pTrain = Instance(pev->groundentity);
			if (pTrain && pTrain->Classify() == CLASS_VEHICLE)
			{
#ifdef REGAMEDLL_ADD
				if (legacy_vehicle_block.value == 0)
					return;
#endif
				((CFuncVehicle *)pTrain)->m_pDriver = nullptr;
			}
			return;
		}
		else
		{
			// Start controlling the train!
			CBaseEntity *pTrain = Instance(pev->groundentity);

			if (pTrain && !(pev->button & IN_JUMP) && (pev->flags & FL_ONGROUND) && (pTrain->ObjectCaps() & FCAP_DIRECTIONAL_USE) && pTrain->OnControls(pev))
			{
				m_afPhysicsFlags |= PFLAG_ONTRAIN;

				m_iTrain = TrainSpeed(pTrain->pev->speed, pTrain->pev->impulse);
				m_iTrain |= TRAIN_NEW;

				if (pTrain->Classify() == CLASS_VEHICLE)
				{
					EMIT_SOUND(ENT(pev), CHAN_ITEM, "plats/vehicle_ignition.wav", 0.8, ATTN_NORM);
					((CFuncVehicle *)pTrain)->m_pDriver = this;
				}
				else
					EMIT_SOUND(ENT(pev), CHAN_ITEM, "plats/train_use1.wav", 0.8, ATTN_NORM);

				return;
			}
		}
	}

	bool useNewHostages = !TheNavAreaList.empty() && AreImprovAllowed();
	CBaseEntity *pObject = nullptr;
	CBaseEntity *pClosest = nullptr;
	Vector vecLOS;
	float flMaxDot = VIEW_FIELD_NARROW;
	float flDot;

	// so we know which way we are facing
	UTIL_MakeVectors(pev->v_angle);

	if (useNewHostages)
	{
		TraceResult result;
		const float useHostageRange = 1000.0f;

		Vector vecStart = pev->origin + pev->view_ofs;
		Vector vecEnd = vecStart + gpGlobals->v_forward * useHostageRange;

		UTIL_TraceLine(vecStart, vecEnd, dont_ignore_monsters, edict(), &result);

		if (result.flFraction < 1.0f)
		{
			CBaseEntity *hit = Instance(result.pHit);
			if (hit && FClassnameIs(hit->pev, "hostage_entity") && CanSeeUseable(this, hit))
				pClosest = hit;
		}

		if (!pClosest)
		{
			while ((pObject = UTIL_FindEntityInSphere(pObject, pev->origin, useHostageRange)))
			{
				if (!FClassnameIs(pObject->pev, "hostage_entity"))
					continue;

				vecLOS = VecBModelOrigin(pObject->pev) - vecStart;
				vecLOS.NormalizeInPlace();

				flDot = DotProduct(vecLOS, gpGlobals->v_forward);

				if (flDot > flMaxDot && CanSeeUseable(this, pObject))
				{
					pClosest = pObject;
					flMaxDot = flDot;
				}
			}
		}
	}

	int caps;
	int iClosestCaps = 0;

	if (!pClosest)
	{
		while ((pObject = UTIL_FindEntityInSphere(pObject, pev->origin, MAX_PLAYER_USE_RADIUS)))
		{
			caps = pObject->ObjectCaps();
			if (caps & (FCAP_IMPULSE_USE | FCAP_CONTINUOUS_USE | FCAP_ONOFF_USE))
			{
				// TODO: PERFORMANCE- should this check be done on a per case basis AFTER we've determined that
				// this object is actually usable? This dot is being done for every object within PLAYER_SEARCH_RADIUS
				// when player hits the use key. How many objects can be in that area, anyway? (sjb)
				vecLOS = (VecBModelOrigin(pObject->pev) - (pev->origin + pev->view_ofs));
				vecLOS.NormalizeInPlace();

				flDot = DotProduct(vecLOS, gpGlobals->v_forward);

				// only if the item is in front of the user
				if (flDot > flMaxDot)
				{
					flMaxDot = flDot;
					pClosest = pObject;
#ifdef REGAMEDLL_FIXES
					iClosestCaps = caps;
#endif
				}
			}
		}
	}
#ifdef REGAMEDLL_FIXES
	else // catch new hostages caps
	{
		iClosestCaps = pClosest->ObjectCaps();
	}

	caps = iClosestCaps;
#endif
	pObject = pClosest;

	// Found an object
	if (pObject)
	{
		if (!useNewHostages || CanSeeUseable(this, pObject))
		{
			// TODO: traceline here to prevent +USEing buttons through walls
#ifndef REGAMEDLL_FIXES
			int caps = pObject->ObjectCaps();
#endif
			if (m_afButtonPressed & IN_USE)
				EMIT_SOUND(ENT(pev), CHAN_ITEM, "common/wpn_select.wav", 0.4, ATTN_NORM);

			if (((pev->button & IN_USE) && (caps & FCAP_CONTINUOUS_USE))
				|| ((m_afButtonPressed & IN_USE) && (caps & (FCAP_IMPULSE_USE | FCAP_ONOFF_USE))))
			{
				if (caps & FCAP_CONTINUOUS_USE)
					m_afPhysicsFlags |= PFLAG_USING;

				pObject->Use(this, this, USE_SET, 1);
			}
			// UNDONE: Send different USE codes for ON/OFF.  Cache last ONOFF_USE object to send 'off' if you turn away
			// BUGBUG This is an "off" use
			else if ((m_afButtonReleased & IN_USE) 
#ifdef REGAMEDLL_FIXES
				&& (caps & FCAP_ONOFF_USE))
#else 
				&& (pObject->ObjectCaps() & FCAP_ONOFF_USE))
#endif
			{
				pObject->Use(this, this, USE_SET, 0);
			}
		}
	}
	else if (m_afButtonPressed & IN_USE)
	{
		UseEmpty();
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, UseEmpty)

void EXT_FUNC CBasePlayer::__API_HOOK(UseEmpty)()
{
	EMIT_SOUND(ENT(pev), CHAN_ITEM, "common/wpn_denyselect.wav", 0.4, ATTN_NORM);
}

void CBasePlayer::HostageUsed()
{
	if (m_flDisplayHistory & DHF_HOSTAGE_USED)
		return;

	if (m_iTeam == TERRORIST)
		HintMessage("#Hint_use_hostage_to_stop_him");

	else if (m_iTeam == CT)
		HintMessage("#Hint_lead_hostage_to_rescue_point");

	m_flDisplayHistory |= DHF_HOSTAGE_USED;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, Jump)

void EXT_FUNC CBasePlayer::__API_HOOK(Jump)()
{
	if (pev->flags & FL_WATERJUMP)
		return;

	if (pev->waterlevel >= 2)
	{
		return;
	}

	// jump velocity is sqrt( height * gravity * 2)
	// If this isn't the first frame pressing the jump button, break out.
	if (!(m_afButtonPressed & IN_JUMP))
	{
		// don't pogo stick
		return;
	}

	if (!(pev->flags & FL_ONGROUND) || !pev->groundentity)
		return;

	// many features in this function use v_forward, so makevectors now.
	UTIL_MakeVectors(pev->angles);
	SetAnimation(PLAYER_JUMP);

	if ((pev->flags & FL_DUCKING) || (m_afPhysicsFlags & PFLAG_DUCKING))
	{
		if (m_fLongJump && (pev->button & IN_DUCK) && (gpGlobals->time - m_flDuckTime < 1.0f) && pev->velocity.Length() > 50)
		{
			SetAnimation(PLAYER_SUPERJUMP);
		}
	}

	// If you're standing on a conveyor, add it's velocity to yours (for momentum)
	entvars_t *pevGround = VARS(pev->groundentity);
	if (pevGround)
	{
		if (pevGround->flags & FL_CONVEYOR)
		{
			pev->velocity = pev->velocity + pev->basevelocity;
		}

		if (FClassnameIs(pevGround, "func_tracktrain")
			|| FClassnameIs(pevGround, "func_train")
			|| FClassnameIs(pevGround, "func_vehicle"))
		{
			pev->velocity = pevGround->velocity + pev->velocity;
		}
	}
}

// This is a glorious hack to find free space when you've crouched into some solid space
// Our crouching collisions do not work correctly for some reason and this is easier
// than fixing the problem :(
NOXREF void FixPlayerCrouchStuck(edict_t *pPlayer)
{
	TraceResult trace;

	// Move up as many as 18 pixels if the player is stuck.
	for (int i = 0; i < 18; i++)
	{
		UTIL_TraceHull(pPlayer->v.origin, pPlayer->v.origin, dont_ignore_monsters, head_hull, pPlayer, &trace);

		if (trace.fStartSolid)
			pPlayer->v.origin.z++;
		else
			break;
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, Duck)

void EXT_FUNC CBasePlayer::__API_HOOK(Duck)()
{
	if (pev->button & IN_DUCK)
		SetAnimation(PLAYER_WALK);
}

LINK_HOOK_CLASS_CHAIN2(int, CBasePlayer, ObjectCaps)

int EXT_FUNC CBasePlayer::__API_HOOK(ObjectCaps)()
{
	return (CBaseMonster::ObjectCaps() & ~FCAP_ACROSS_TRANSITION);
}

LINK_HOOK_CLASS_CHAIN2(int, CBasePlayer, Classify)

// ID's player as such.
int EXT_FUNC CBasePlayer::__API_HOOK(Classify)()
{
	return CLASS_PLAYER;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, AddPoints, (int score, BOOL bAllowNegativeScore), score, bAllowNegativeScore)

void EXT_FUNC CBasePlayer::__API_HOOK(AddPoints)(int score, BOOL bAllowNegativeScore)
{
	// Positive score always adds
	if (score < 0 && !bAllowNegativeScore)
	{
		// Can't go more negative
		if (pev->frags < 0)
			return;

		if (-score > pev->frags)
		{
			// Sum will be 0
			score = -pev->frags;
		}
	}

	pev->frags += score;

#ifdef REGAMEDLL_FIXES
	MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
#else
	MESSAGE_BEGIN(MSG_BROADCAST, gmsgScoreInfo);
#endif
		WRITE_BYTE(ENTINDEX(edict()));
		WRITE_SHORT(int(pev->frags));
		WRITE_SHORT(m_iDeaths);
		WRITE_SHORT(0);
		WRITE_SHORT(m_iTeam);
	MESSAGE_END();
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, AddPointsToTeam, (int score, BOOL bAllowNegativeScore), score, bAllowNegativeScore)

void EXT_FUNC CBasePlayer::__API_HOOK(AddPointsToTeam)(int score, BOOL bAllowNegativeScore)
{
	int index = entindex();
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pPlayer))
			continue;

		if (i != index)
		{
			if (g_pGameRules->PlayerRelationship(this, pPlayer) == GR_TEAMMATE)
			{
				pPlayer->AddPoints(score, bAllowNegativeScore);
			}
		}
	}
}

bool CBasePlayer::CanPlayerBuy(bool display)
{
	if (!g_pGameRules->IsMultiplayer())
	{
		return CHalfLifeTraining::PlayerCanBuy(this);
	}

	// is the player alive?
	if (pev->deadflag != DEAD_NO)
	{
		return false;
	}

	// is the player in a buy zone?
	if (!(m_signals.GetState() & SIGNAL_BUY))
	{
		return false;
	}

#ifdef REGAMEDLL_ADD
	if (buytime.value != -1.0f)
#endif
	{
		int buyTime = int(buytime.value * 60.0f);
		if (buyTime < MIN_BUY_TIME)
		{
			buyTime = MIN_BUY_TIME;
			CVAR_SET_FLOAT("mp_buytime", (MIN_BUY_TIME / 60.0f));
		}

		if (gpGlobals->time - CSGameRules()->m_fRoundStartTime > buyTime)
		{
			if (display)
			{
				ClientPrint(pev, HUD_PRINTCENTER, "#Cant_buy", UTIL_dtos1(buyTime));
			}

			return false;
		}
	}

	if (m_bIsVIP)
	{
		if (display)
		{
			ClientPrint(pev, HUD_PRINTCENTER, "#VIP_cant_buy");
		}

		return false;
	}

	if (CSGameRules()->m_bCTCantBuy && m_iTeam == CT)
	{
		if (display)
		{
			ClientPrint(pev, HUD_PRINTCENTER, "#CT_cant_buy");
		}

		return false;
	}

	if (CSGameRules()->m_bTCantBuy && m_iTeam == TERRORIST)
	{
		if (display)
		{
			ClientPrint(pev, HUD_PRINTCENTER, "#Terrorist_cant_buy");
		}

		return false;
	}

	return true;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, PreThink)

void EXT_FUNC CBasePlayer::__API_HOOK(PreThink)()
{
	// These buttons have changed this frame
	int buttonsChanged = (m_afButtonLast ^ pev->button);

	// this means the player has pressed or released a key
	if (buttonsChanged)
	{
		m_fLastMovement = gpGlobals->time;
	}

	// Debounced button codes for pressed/released
	// UNDONE: Do we need auto-repeat?
	m_afButtonPressed  = (buttonsChanged & pev->button);		// The changed ones still down are "pressed"
	m_afButtonReleased = (buttonsChanged & (~pev->button));		// The ones not down are "released"

	// Hint messages should be updated even if the game is over
	m_hintMessageQueue.Update(this);
	g_pGameRules->PlayerThink(this);

	if (g_pGameRules->IsGameOver())
	{
		// intermission or finale
		return;
	}

	if (m_iJoiningState != JOINED)
		JoiningThink();

	// Mission Briefing text, remove it when the player hits an important button
	if (m_bMissionBriefing)
	{
		if (m_afButtonPressed & (IN_ATTACK | IN_ATTACK2))
		{
			m_afButtonPressed &= ~(IN_ATTACK | IN_ATTACK2);
			RemoveLevelText();
			m_bMissionBriefing = false;
		}
	}

	// is this still used?
	UTIL_MakeVectors(pev->v_angle);

	ItemPreFrame();
	WaterMove();

	if (pev->flags & FL_ONGROUND)
	{
		// Slow down the player based on the velocity modifier
		if (m_flVelocityModifier < 1.0f)
		{
			real_t modvel = m_flVelocityModifier + 0.01;

			m_flVelocityModifier = modvel;
			pev->velocity = pev->velocity * modvel;
		}

		if (m_flVelocityModifier > 1.0f)
			m_flVelocityModifier = 1;
	}

	if (
#ifdef REGAMEDLL_FIXES
		IsAlive() &&
#endif
		(m_flIdleCheckTime <= (double)gpGlobals->time || m_flIdleCheckTime == 0.0f))
	{
		// check every 5 seconds
		m_flIdleCheckTime = gpGlobals->time + 5.0;

#ifdef REGAMEDLL_ADD
		if (CSPlayer()->CheckActivityInGame())
		{
			m_fLastMovement = gpGlobals->time;
		}
#endif

		real_t flLastMove = gpGlobals->time - m_fLastMovement;

		//check if this player has been inactive for 2 rounds straight
		if (!IsBot() && flLastMove > CSGameRules()->m_fMaxIdlePeriod)
		{
			DropIdlePlayer("Player idle");

			m_fLastMovement = gpGlobals->time;
		}
#ifdef REGAMEDLL_ADD
		if (afk_bomb_drop_time.value > 0.0 && IsBombGuy())
		{
			if (flLastMove > afk_bomb_drop_time.value && !CSGameRules()->IsFreezePeriod())
			{
				DropPlayerItem("weapon_c4");
			}
		}
#endif
	}

	if (g_pGameRules && g_pGameRules->FAllowFlashlight())
		m_iHideHUD &= ~HIDEHUD_FLASHLIGHT;
	else
		m_iHideHUD |= HIDEHUD_FLASHLIGHT;

	// JOHN: checks if new client data (for HUD and view control) needs to be sent to the client
	UpdateClientData();

	CheckTimeBasedDamage();
	CheckSuitUpdate();

	// So the correct flags get sent to client asap.
	if (m_afPhysicsFlags & PFLAG_ONTRAIN)
		pev->flags |= FL_ONTRAIN;
	else
		pev->flags &= ~FL_ONTRAIN;

#ifdef REGAMEDLL_ADD
	PlayerRespawnThink();
#endif

	// Observer Button Handling
	if (GetObserverMode() != OBS_NONE && (m_afPhysicsFlags & PFLAG_OBSERVER))
	{
		Observer_Think();
		return;
	}

	if (pev->deadflag >= DEAD_DYING && pev->deadflag != DEAD_RESPAWNABLE)
	{
		PlayerDeathThink();
		return;
	}

	// new code to determine if a player is on a train or not
	CBaseEntity *pGroundEntity = Instance(pev->groundentity);
	if (pGroundEntity && pGroundEntity->Classify() == CLASS_VEHICLE)
	{
		pev->iuser4 = 1;
	}
	else
	{
		pev->iuser4 = 0;
	}

	// Train speed control
	if (m_afPhysicsFlags & PFLAG_ONTRAIN)
	{
		CBaseEntity *pTrain = Instance(pev->groundentity);
		float vel;

		if (!pTrain)
		{
			TraceResult trainTrace;
			// Maybe this is on the other side of a level transition
			UTIL_TraceLine(pev->origin, pev->origin + Vector(0, 0, -38), ignore_monsters, ENT(pev), &trainTrace);

			// HACKHACK - Just look for the func_tracktrain classname
			if (trainTrace.flFraction != 1.0f && trainTrace.pHit)
				pTrain = Instance(trainTrace.pHit);

			if (!pTrain || !(pTrain->ObjectCaps() & FCAP_DIRECTIONAL_USE) || !pTrain->OnControls(pev))
			{
				m_afPhysicsFlags &= ~PFLAG_ONTRAIN;
				m_iTrain = (TRAIN_NEW | TRAIN_OFF);

#ifdef REGAMEDLL_FIXES
				if (pTrain && pTrain->Classify() == CLASS_VEHICLE) // ensure func_vehicle's m_pDriver assignation
#endif
				{
#ifdef REGAMEDLL_ADD
					if (legacy_vehicle_block.value == 0)
						return;
#endif
					((CFuncVehicle *)pTrain)->m_pDriver = nullptr;
				}
				return;
			}
		}
		else if (!(pev->flags & FL_ONGROUND) || (pTrain->pev->spawnflags & SF_TRACKTRAIN_NOCONTROL))
		{
			// Turn off the train if you jump, strafe, or the train controls go dead
			m_afPhysicsFlags &= ~PFLAG_ONTRAIN;
			m_iTrain = (TRAIN_NEW | TRAIN_OFF);

#ifdef REGAMEDLL_FIXES
			if (pTrain->Classify() == CLASS_VEHICLE) // ensure func_vehicle's m_pDriver assignation
#endif
			{
#ifdef REGAMEDLL_ADD
				if (legacy_vehicle_block.value == 0)
					return;
#endif
				((CFuncVehicle *)pTrain)->m_pDriver = nullptr;
			}
			return;
		}

		pev->velocity = g_vecZero;
		vel = 0;

		if (pTrain->Classify() == CLASS_VEHICLE)
		{
			if (pev->button & IN_FORWARD)
			{
				vel = 1;
				pTrain->Use(this, this, USE_SET, vel);
			}

			if (pev->button & IN_BACK)
			{
				vel = -1;
				pTrain->Use(this, this, USE_SET, vel);
			}

			if (pev->button & IN_MOVELEFT)
			{
				vel = 20;
				pTrain->Use(this, this, USE_SET, vel);
			}
			if (pev->button & IN_MOVERIGHT)
			{
				vel = 30;
				pTrain->Use(this, this, USE_SET, vel);
			}
		}
		else
		{
			if (m_afButtonPressed & IN_FORWARD)
			{
				vel = 1;
				pTrain->Use(this, this, USE_SET, vel);
			}
			else if (m_afButtonPressed & IN_BACK)
			{
				vel = -1;
				pTrain->Use(this, this, USE_SET, vel);
			}
		}

		if (vel)
		{
			m_iTrain = TrainSpeed(pTrain->pev->speed, pTrain->pev->impulse);
			m_iTrain |= (TRAIN_ACTIVE | TRAIN_NEW);
		}
	}
	else if (m_iTrain & TRAIN_ACTIVE)
	{
		// turn off train
		m_iTrain = TRAIN_NEW;
	}

	if (pev->button & IN_JUMP)
	{
		// If on a ladder, jump off the ladder
		// else Jump
		Jump();
	}

	// If trying to duck, already ducked, or in the process of ducking
	if ((pev->button & IN_DUCK) || (pev->flags & FL_DUCKING) || (m_afPhysicsFlags & PFLAG_DUCKING))
	{
		Duck();
	}

	if (!(pev->flags & FL_ONGROUND))
	{
		m_flFallVelocity = -pev->velocity.z;
	}

	// TODO: (HACKHACK) Can't be hit by traceline when not animating?
	//StudioFrameAdvance();

	// Clear out ladder pointer
	m_hEnemy = nullptr;

	if (m_afPhysicsFlags & PFLAG_ONBARNACLE)
	{
		pev->velocity = g_vecZero;
	}

	if (!(m_flDisplayHistory & DHF_ROUND_STARTED) && CanPlayerBuy(false))
	{
		HintMessage("#Hint_press_buy_to_purchase", FALSE);
		m_flDisplayHistory |= DHF_ROUND_STARTED;
	}

	UpdateLocation();

#ifdef REGAMEDLL_ADD
	auto protectStateCurrent = CSPlayer()->GetProtectionState();
	if (protectStateCurrent  == CCSPlayer::ProtectionSt_Expired ||
		(protectStateCurrent == CCSPlayer::ProtectionSt_Active &&
		((respawn_immunity_force_unset.value == 1 && (m_afButtonPressed & IN_ACTIVE)) || (respawn_immunity_force_unset.value == 2 && (m_afButtonPressed & (IN_ATTACK | IN_ATTACK2))))))
	{
		RemoveSpawnProtection();
	}
#endif
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, CheckTimeBasedDamage)

// If player is taking time based damage, continue doing damage to player -
// this simulates the effect of being poisoned, gassed, dosed with radiation etc -
// anything that continues to do damage even after the initial contact stops.
// Update all time based damage counters, and shut off any that are done.

// The m_bitsDamageType bit MUST be set if any damage is to be taken.
// This routine will detect the initial on value of the m_bitsDamageType
// and init the appropriate counter.  Only processes damage every second.
void EXT_FUNC CBasePlayer::__API_HOOK(CheckTimeBasedDamage)()
{
	int i;
	byte bDuration = 0;

	if (!(m_bitsDamageType & DMG_TIMEBASED))
		return;

	// only check for time based damage approx. every 2 seconds
#ifdef REGAMEDLL_FIXES
	if (Q_abs(gpGlobals->time - m_tbdPrev) < 2.0f)
#else
	if (Q_abs(int64(gpGlobals->time - m_tbdPrev)) < 2.0f)
#endif
		return;

	m_tbdPrev = gpGlobals->time;

	for (i = 0; i < ITBD_END; i++)
	{
		// make sure bit is set for damage type
		if (m_bitsDamageType & (DMG_PARALYZE << i))
		{
			switch (i)
			{
			case ITBD_PARALYZE:
				// UNDONE - flag movement as half-speed
				bDuration = PARALYZE_DURATION;
				break;
			case ITBD_NERVE_GAS:
				bDuration = NERVEGAS_DURATION;
				break;
			case ITBD_POISON:
			{
				TakeDamage(pev, pev, POISON_DAMAGE, DMG_GENERIC);
				bDuration = POISON_DURATION;
				break;
			}
			case ITBD_DROWN_RECOVER:
			{
				// NOTE: this hack is actually used to RESTORE health
				// after the player has been drowning and finally takes a breath
				if (m_idrowndmg > m_idrownrestored)
				{
					int idif = Q_min(m_idrowndmg - m_idrownrestored, 10);

					TakeHealth(idif, DMG_GENERIC);
					m_idrownrestored += idif;
				}
				// get up to 5*10 = 50 points back
				bDuration = 4;
				break;
			}
			case ITBD_RADIATION:
				bDuration = RADIATION_DURATION;
				break;
			case ITBD_ACID:
				bDuration = ACID_DURATION;
				break;
			case ITBD_SLOW_BURN:
				bDuration = SLOWBURN_DURATION;
				break;
			case ITBD_SLOW_FREEZE:
				bDuration = SLOWFREEZE_DURATION;
				break;
			default:
				bDuration = 0;
				break;
			}

			if (m_rgbTimeBasedDamage[i])
			{
				// use up an antitoxin on poison or nervegas after a few seconds of damage
				if ((i == ITBD_NERVE_GAS && m_rgbTimeBasedDamage[i] < NERVEGAS_DURATION) || (i == ITBD_POISON && m_rgbTimeBasedDamage[i] < POISON_DURATION))
				{
					if (m_rgItems[ITEM_ID_ANTIDOTE])
					{
						m_rgbTimeBasedDamage[i] = 0;
						m_rgItems[ITEM_ID_ANTIDOTE]--;
						SetSuitUpdate("!HEV_HEAL4", SUIT_SENTENCE, SUIT_REPEAT_OK);
					}
				}

				// decrement damage duration, detect when done.
				if (!m_rgbTimeBasedDamage[i] || --m_rgbTimeBasedDamage[i] == 0)
				{
					m_rgbTimeBasedDamage[i] = 0;
					// if we're done, clear damage bits
					m_bitsDamageType &= ~(DMG_PARALYZE << i);
				}
			}
			else
				// first time taking this damage type - init damage duration
				m_rgbTimeBasedDamage[i] = bDuration;
		}
	}
}

void CBasePlayer::UpdateGeigerCounter()
{
	byte range;

	// delay per update ie: don't flood net with these msgs
	if (gpGlobals->time < m_flgeigerDelay)
		return;

	m_flgeigerDelay = gpGlobals->time + 0.25;

	// send range to radition source to client
	range = byte(m_flgeigerRange / 4.0);//* 0.25);		// TODO: ACHECK!

	if (range != m_igeigerRangePrev)
	{
		m_igeigerRangePrev = range;

		MESSAGE_BEGIN(MSG_ONE, gmsgGeigerRange, nullptr, pev);
			WRITE_BYTE(range);
		MESSAGE_END();
	}

	// reset counter and semaphore
	if (!RANDOM_LONG(0, 3))
	{
		m_flgeigerRange = 1000.0;
	}
}

void CBasePlayer::CheckSuitUpdate()
{
	int i;
	int isentence = 0;
	int isearch = m_iSuitPlayNext;

	// Ignore suit updates if no suit
	if (!(pev->weapons & (1 << WEAPON_SUIT)))
		return;

	// if in range of radiation source, ping geiger counter
	UpdateGeigerCounter();

	if (g_pGameRules->IsMultiplayer())
	{
		// don't bother updating HEV voice in multiplayer.
		return;
	}

	if (gpGlobals->time >= m_flSuitUpdate && m_flSuitUpdate > 0)
	{
		// play a sentence off of the end of the queue
		for (i = 0; i < MAX_SUIT_NOREPEAT; i++)
		{
			if ((isentence = m_rgSuitPlayList[isearch]))
				break;

			if (++isearch == MAX_SUIT_NOREPEAT)
				isearch = 0;
		}

		if (isentence)
		{
			m_rgSuitPlayList[isearch] = 0;

			if (isentence > 0)
			{
				// play sentence number
				char sentence[MAX_SENTENCE_NAME + 1];
				Q_strcpy(sentence, "!");
				Q_strcat(sentence, gszallsentencenames[isentence]);
				EMIT_SOUND_SUIT(ENT(pev), sentence);
			}
			else
			{
				// play sentence group
				EMIT_GROUPID_SUIT(ENT(pev), -isentence);
			}

			m_flSuitUpdate = gpGlobals->time + SUIT_UPDATE_TIME;
		}
		else
			// queue is empty, don't check
			m_flSuitUpdate = 0;
	}
}

// add sentence to suit playlist queue. if group is true, then
// name is a sentence group (HEV_AA), otherwise name is a specific
// sentence name ie: !HEV_AA0.  If iNoRepeat is specified in
// seconds, then we won't repeat playback of this word or sentence
// for at least that number of seconds.
void CBasePlayer::SetSuitUpdate(char *name, bool group, int iNoRepeatTime)
{
	;
}

void CBasePlayer::CheckPowerups()
{
	if (pev->health <= 0.0f)
		return;

	// don't use eyes
	pev->modelindex = m_modelIndexPlayer;
}

void CBasePlayer::SetNewPlayerModel(const char *modelName)
{
	SET_MODEL(edict(), modelName);
	m_modelIndexPlayer = pev->modelindex;

#ifdef REGAMEDLL_FIXES
	ResetSequenceInfo();
#endif
}

// UpdatePlayerSound - updates the position of the player's
// reserved sound slot in the sound list.
void CBasePlayer::UpdatePlayerSound()
{
	int iBodyVolume;
	int iVolume;

	CSound *pSound = CSoundEnt::SoundPointerForIndex(CSoundEnt::ClientSoundIndex(edict()));

	if (!pSound)
	{
		ALERT(at_console, "Client lost reserved sound!\n");
		return;
	}

	pSound->m_iType = bits_SOUND_NONE;

	// now calculate the best target volume for the sound. If the player's weapon
	// is louder than his body/movement, use the weapon volume, else, use the body volume.
	// now figure out how loud the player's movement is.

	if (pev->flags & FL_ONGROUND)
	{
		iBodyVolume = pev->velocity.Length();

		// clamp the noise that can be made by the body, in case a push trigger,
		// weapon recoil, or anything shoves the player abnormally fast.
		// NOTE: 512 units is a pretty large radius for a sound made by the player's body.
		// then again, I think some materials are pretty loud.
		if (iBodyVolume > 512)
		{
			iBodyVolume = 512;
		}
	}
	else
	{
		iBodyVolume = 0;
	}

	if (pev->button & IN_JUMP)
	{
		// Jumping is a little louder.
		iBodyVolume += 100;
	}

	// convert player move speed and actions into sound audible by monsters.
	if (m_iWeaponVolume > iBodyVolume)
	{
		m_iTargetVolume = m_iWeaponVolume;

		// OR in the bits for COMBAT sound if the weapon is being louder than the player.
		pSound->m_iType |= bits_SOUND_COMBAT;
	}
	else
	{
		m_iTargetVolume = iBodyVolume;
	}

	// decay weapon volume over time so bits_SOUND_COMBAT stays set for a while
	m_iWeaponVolume -= 250 * gpGlobals->frametime;

	// if target volume is greater than the player sound's current volume, we paste the new volume in
	// immediately. If target is less than the current volume, current volume is not set immediately to the
	// lower volume, rather works itself towards target volume over time. This gives monsters a much better chance
	// to hear a sound, especially if they don't listen every frame.
	iVolume = pSound->m_iVolume;

	if (m_iTargetVolume > iVolume)
	{
		iVolume = m_iTargetVolume;
	}
	else if (iVolume > m_iTargetVolume)
	{
		iVolume -= 250 * gpGlobals->frametime;

		if (iVolume < m_iTargetVolume)
			iVolume = 0;
	}

	if (m_fNoPlayerSound)
	{
		// debugging flag, lets players move around and shoot without monsters hearing.
		iVolume = 0;
	}

	if (gpGlobals->time > m_flStopExtraSoundTime)
	{
		// since the extra sound that a weapon emits only lasts for one client frame, we keep that sound around for a server frame or two
		// after actual emission to make sure it gets heard.
		m_iExtraSoundTypes = 0;
	}

	if (pSound)
	{
		pSound->m_vecOrigin = pev->origin;
		pSound->m_iVolume = iVolume;
		pSound->m_iType |= (bits_SOUND_PLAYER | m_iExtraSoundTypes);
	}

	// keep track of virtual muzzle flash
	m_iWeaponFlash -= 256 * gpGlobals->frametime;

	if (m_iWeaponFlash < 0)
		m_iWeaponFlash = 0;

	UTIL_MakeVectors(pev->angles);
	gpGlobals->v_forward.z = 0;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, PostThink)

void EXT_FUNC CBasePlayer::__API_HOOK(PostThink)()
{
	// intermission or finale
	if (g_pGameRules->IsGameOver())
		goto pt_end;

	if (!IsAlive())
		goto pt_end;

	// Handle Tank controlling
	if (m_pTank)
	{
		// if they've moved too far from the gun,  or selected a weapon, unuse the gun
		if (m_pTank->OnControls(pev) && !pev->weaponmodel)
		{
			// try fire the gun
			m_pTank->Use(this, this, USE_SET, 2);
		}
		else
		{
			// they've moved off the platform
			m_pTank->Use(this, this, USE_OFF, 0);
			m_pTank = nullptr;
		}
	}

	// do weapon stuff
	ItemPostFrame();

	// check to see if player landed hard enough to make a sound
	// falling farther than half of the maximum safe distance, but not as far a max safe distance will
	// play a bootscrape sound, and no damage will be inflicted. Fallling a distance shorter than half
	// of maximum safe distance will make no sound. Falling farther than max safe distance will play a
	// fallpain sound, and damage will be inflicted based on how far the player fell
	if ((pev->flags & FL_ONGROUND) && pev->health > 0.0f && m_flFallVelocity >= PLAYER_FALL_PUNCH_THRESHHOLD)
	{
		if (pev->watertype != CONTENT_WATER)
		{
			// after this point, we start doing damage
			if (m_flFallVelocity > MAX_PLAYER_SAFE_FALL_SPEED)
			{
				float flFallDamage = g_pGameRules->FlPlayerFallDamage(this);

				// splat
				if (flFallDamage > pev->health)
				{
					// NOTE: play on item channel because we play footstep landing on body channel
					EMIT_SOUND(ENT(pev), CHAN_ITEM, "common/bodysplat.wav", VOL_NORM, ATTN_NORM);
				}

#ifdef REGAMEDLL_FIXES
				if (flFallDamage >= 1.0f)
#else
				if (flFallDamage > 0)
#endif
				{
					m_LastHitGroup = HITGROUP_GENERIC;

					// FIXED: The player falling to the ground,
					// the damage caused by the fall is initiated by himself (and not by the world)
					entvars_t *pevAttacker =
#ifdef REGAMEDLL_FIXES
					pev;
#else
					VARS(eoNullEntity);
#endif
					TakeDamage(pevAttacker, pevAttacker, flFallDamage, DMG_FALL);

					pev->punchangle.x = 0;
					if (TheBots)
					{
						TheBots->OnEvent(EVENT_PLAYER_LANDED_FROM_HEIGHT, this);
					}
				}
			}
		}

		if (IsAlive())
		{
			SetAnimation(PLAYER_WALK);
		}
	}

	if (pev->flags & FL_ONGROUND)
	{
#ifndef REGAMEDLL_FIXES
		if (m_flFallVelocity > 64.0f && !g_pGameRules->IsMultiplayer())
		{
			CSoundEnt::InsertSound(bits_SOUND_PLAYER, pev->origin, m_flFallVelocity, 0.2);
		}
#endif
		m_flFallVelocity = 0;
	}

	// select the proper animation for the player character
	if (IsAlive())
	{
		if (pev->velocity.x || pev->velocity.y)
		{
			if (((pev->velocity.x || pev->velocity.y) && (pev->flags & FL_ONGROUND)) || pev->waterlevel > 1)
				SetAnimation(PLAYER_WALK);
		}
		else if (pev->gaitsequence != ACT_FLY)
			SetAnimation(PLAYER_IDLE);
	}

	StudioFrameAdvance();
	CheckPowerups();

#ifdef REGAMEDLL_ADD
	if (m_flTimeStepSound) {
		pev->flTimeStepSound = int(m_flTimeStepSound);
	}
#endif

	// NOTE: this is useless for CS 1.6 - s1lent
#ifndef REGAMEDLL_FIXES
	UpdatePlayerSound();
#endif

pt_end:
#ifdef CLIENT_WEAPONS
	// Decay timers on weapons
	// go through all of the weapons and make a list of the ones to pack
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		if (m_rgpPlayerItems[i])
		{
			CBasePlayerItem *pPlayerItem = m_rgpPlayerItems[i];

			while (pPlayerItem)
			{
				CBasePlayerWeapon *gun = (CBasePlayerWeapon *)pPlayerItem->GetWeaponPtr();

				if (gun && gun->UseDecrement())
				{
					gun->m_flNextPrimaryAttack = Q_max(gun->m_flNextPrimaryAttack - gpGlobals->frametime, -1.0f);
					gun->m_flNextSecondaryAttack = Q_max(gun->m_flNextSecondaryAttack - gpGlobals->frametime, -0.001f);

					if (gun->m_flTimeWeaponIdle != 1000.0f)
					{
						gun->m_flTimeWeaponIdle = Q_max(gun->m_flTimeWeaponIdle - gpGlobals->frametime, -0.001f);
					}
				}

				pPlayerItem = pPlayerItem->m_pNext;
			}
		}
	}

	m_flNextAttack -= gpGlobals->frametime;

	if (m_flNextAttack < -0.001)
		m_flNextAttack = -0.001;
#endif // CLIENT_WEAPONS

	// Track button info so we can detect 'pressed' and 'released' buttons next frame
	m_afButtonLast = pev->button;
	m_iGaitsequence = pev->gaitsequence;

	StudioProcessGait();
}

// checks if the spot is clear of players
BOOL IsSpawnPointValid(CBaseEntity *pPlayer, CBaseEntity *pSpot)
{
	if (!pSpot->IsTriggered(pPlayer))
		return FALSE;

#ifdef REGAMEDLL_ADD
	if (!kill_filled_spawn.value)
		return TRUE;
#endif

	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityInSphere(pEntity, pSpot->pev->origin, MAX_PLAYER_USE_RADIUS)))
	{
		// if ent is a client, don't spawn on 'em
		if (pEntity->IsPlayer() && pEntity != pPlayer)
			return FALSE;
	}

	return TRUE;
}

bool CBasePlayer::SelectSpawnSpot(const char *pEntClassName, CBaseEntity *&pSpot)
{
	edict_t *pPlayer = edict();

	// Find the next spawn spot.
	pSpot = UTIL_FindEntityByClassname(pSpot, pEntClassName);

	// skip over the null point
	if (FNullEnt(pSpot))
	{
		pSpot = UTIL_FindEntityByClassname(pSpot, pEntClassName);
	}

	CBaseEntity *pFirstSpot = pSpot;

	do
	{
		if (pSpot)
		{
			// check if pSpot is valid
			if (IsSpawnPointValid(this, pSpot))
			{
				if (pSpot->pev->origin == Vector(0, 0, 0))
				{
					pSpot = UTIL_FindEntityByClassname(pSpot, pEntClassName);
					continue;
				}

				// if so, go to pSpot
				return true;
			}
		}

		// increment pSpot
		pSpot = UTIL_FindEntityByClassname(pSpot, pEntClassName);
	}
	// loop if we're not back to the start
	while (pSpot != pFirstSpot);

	// we haven't found a place to spawn yet,  so kill any guy at the first spawn point and spawn there
	if (!FNullEnt(pSpot))
	{
#ifdef REGAMEDLL_ADD
		if (kill_filled_spawn.value != 0.0)
#endif
		{
			CBaseEntity *pEntity = nullptr;
			while ((pEntity = UTIL_FindEntityInSphere(pEntity, pSpot->pev->origin, MAX_PLAYER_USE_RADIUS)))
			{
				// if ent is a client, kill em (unless they are ourselves)
				if (pEntity->IsPlayer() && pEntity->edict() != pPlayer)
				{
					pEntity->TakeDamage(VARS(eoNullEntity), VARS(eoNullEntity), 200, DMG_GENERIC);
				}
			}
		}

		// if so, go to pSpot
		return true;
	}

	return false;
}

CBaseEntity *g_pLastSpawn;
CBaseEntity *g_pLastCTSpawn;
CBaseEntity *g_pLastTerroristSpawn;

LINK_HOOK_CLASS_CHAIN2(edict_t *, CBasePlayer, EntSelectSpawnPoint)

edict_t *EXT_FUNC CBasePlayer::__API_HOOK(EntSelectSpawnPoint)()
{
	CBaseEntity *pSpot;

	// choose a info_player_deathmatch point
	if (g_pGameRules->IsCoOp())
	{
		pSpot = UTIL_FindEntityByClassname(g_pLastSpawn, "info_player_coop");

		if (!FNullEnt(pSpot))
			goto ReturnSpot;

		pSpot = UTIL_FindEntityByClassname(g_pLastSpawn, "info_player_start");

		if (!FNullEnt(pSpot))
			goto ReturnSpot;
	}
	// VIP spawn point
	else if (g_pGameRules->IsDeathmatch() && m_bIsVIP)
	{
		pSpot = UTIL_FindEntityByClassname(nullptr, "info_vip_start");

		// skip over the null point
		if (!FNullEnt(pSpot))
		{
			goto ReturnSpot;
		}

		goto CTSpawn;
	}
	// the counter-terrorist spawns at "info_player_start"
	else if (g_pGameRules->IsDeathmatch() && m_iTeam == CT)
	{
CTSpawn:
		pSpot = g_pLastCTSpawn;

		if (SelectSpawnSpot("info_player_start", pSpot))
		{
			goto ReturnSpot;
		}
	}
	// The terrorist spawn points
	else if (g_pGameRules->IsDeathmatch() && m_iTeam == TERRORIST)
	{
		pSpot = g_pLastTerroristSpawn;

		if (SelectSpawnSpot("info_player_deathmatch", pSpot))
		{
			goto ReturnSpot;
		}
	}

	// If startspot is set, (re)spawn there.
	if (FStringNull(gpGlobals->startspot) || !Q_strlen(STRING(gpGlobals->startspot)))
	{
		pSpot = UTIL_FindEntityByClassname(nullptr, "info_player_deathmatch");

		if (!FNullEnt(pSpot))
			goto ReturnSpot;
	}
	else
	{
		pSpot = UTIL_FindEntityByTargetname(nullptr, STRING(gpGlobals->startspot));

		if (!FNullEnt(pSpot))
			goto ReturnSpot;
	}

ReturnSpot:
	if (FNullEnt(pSpot))
	{
		ALERT(at_error, "PutClientInServer: no info_player_start on level\n");
		return INDEXENT(0);
	}

	if (m_iTeam == TERRORIST)
		g_pLastTerroristSpawn = pSpot;
	else
		g_pLastCTSpawn = pSpot;

	return pSpot->edict();
}

void CBasePlayer::SetScoreAttrib(CBasePlayer *dest)
{
	int state = SCORE_STATUS_NONE;
	if (pev->deadflag != DEAD_NO)
		state |= SCORE_STATUS_DEAD;

	if (m_bHasC4)
		state |= SCORE_STATUS_BOMB;

	if (m_bIsVIP)
		state |= SCORE_STATUS_VIP;

#ifdef BUILD_LATEST

#ifdef REGAMEDLL_FIXES
	if (scoreboard_showdefkit.value)
#endif
	{
		if (m_bHasDefuser)
			state |= SCORE_STATUS_DEFKIT;
	}

#endif

#ifdef REGAMEDLL_FIXES
	// TODO: Remove these fixes when they are implemented on the client side
	if (state & (SCORE_STATUS_BOMB | SCORE_STATUS_DEFKIT) && GetForceCamera(dest) != CAMERA_MODE_SPEC_ANYONE)
	{
		if (CSGameRules()->PlayerRelationship(this, dest) != GR_TEAMMATE)
			state &= ~(SCORE_STATUS_BOMB | SCORE_STATUS_DEFKIT);
	}
#endif

	if (gmsgScoreAttrib)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgScoreAttrib, nullptr, dest->pev);
			WRITE_BYTE(entindex());
			WRITE_BYTE(state);
		MESSAGE_END();
	}
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, Spawn)

void EXT_FUNC CBasePlayer::__API_HOOK(Spawn)()
{
	int i;

#ifdef REGAMEDLL_FIXES
	// Do not allow to do spawn, if player chooses a team or appearance.
	if (m_bJustConnected && m_iJoiningState == PICKINGTEAM) {
		return;
	}
#endif

	m_iGaitsequence = 0;

	m_flGaitframe = 0;
	m_flGaityaw = 0;
	m_flGaitMovement = 0;
	m_prevgaitorigin = Vector(0, 0, 0);
	m_progressStart = 0;
	m_progressEnd = 0;

	MAKE_STRING_CLASS("player", pev);

	pev->health = 100;

	if (!m_bNotKilled)
	{
		pev->armorvalue = 0;
		m_iKevlar = ARMOR_NONE;
	}

	pev->maxspeed = 1000;
	pev->takedamage = DAMAGE_AIM;
	pev->solid = SOLID_SLIDEBOX;
	pev->movetype = MOVETYPE_WALK;
	pev->max_health = pev->health;

	pev->flags &= FL_PROXY;
	pev->flags |= FL_CLIENT;
	pev->air_finished = gpGlobals->time + AIRTIME;
	pev->dmg = 2;
	pev->effects = 0;
	pev->deadflag = DEAD_NO;
	pev->dmg_take = 0;
	pev->dmg_save = 0;

#ifdef REGAMEDLL_FIXES
	pev->watertype = CONTENTS_EMPTY;
	pev->waterlevel = 0;
	pev->basevelocity = g_vecZero;	// pushed by trigger_push
#endif

	m_bitsHUDDamage = -1;
	m_bitsDamageType = 0;
	m_afPhysicsFlags = 0;
	m_fLongJump = FALSE;
	m_iClientFOV = 0;
	m_pentCurBombTarget = nullptr;

	if (m_bOwnsShield)
		pev->gamestate = HITGROUP_SHIELD_ENABLED;
	else
		pev->gamestate = HITGROUP_SHIELD_DISABLED;

	ResetStamina();
	pev->friction = 1;
	pev->gravity = 1;

	SET_PHYSICS_KEY_VALUE(edict(), "slj", "0");
	SET_PHYSICS_KEY_VALUE(edict(), "hl", "1");
	m_hintMessageQueue.Reset();

	m_flVelocityModifier = 1;
	m_iLastZoom = DEFAULT_FOV;
	m_flLastTalk = 0;
	m_flIdleCheckTime = 0;
	m_flRadioTime = 0;
#ifdef REGAMEDLL_ADD
	m_iRadioMessages = int(radio_maxinround.value);
#else
	m_iRadioMessages = 60;
#endif
	m_bHasC4 = false;
	m_bKilledByBomb = false;
	m_bKilledByGrenade = false;
	m_flDisplayHistory &= ~DHM_ROUND_CLEAR;
	m_tmHandleSignals = 0;
	m_fCamSwitch = 0;
	m_iChaseTarget = 1;
	m_bEscaped = false;
	m_tmNextRadarUpdate = gpGlobals->time;

#ifdef BUILD_LATEST
	m_tmNextAccountHealthUpdate = gpGlobals->time;
#endif

	m_vLastOrigin = Vector(0, 0, 0);
	m_iCurrentKickVote = 0;
	m_flNextVoteTime = 0;
	m_bJustKilledTeammate = false;

	SET_VIEW(ENT(pev), ENT(pev));

	m_hObserverTarget = nullptr;
	pev->iuser1 =
		pev->iuser2 =
		pev->iuser3 = 0;

	m_flLastFired = -15;
	m_bHeadshotKilled = false;
	m_bReceivesNoMoneyNextRound = false;
	m_bShieldDrawn = false;

	m_blindUntilTime = 0;
	m_blindStartTime = 0;
	m_blindHoldTime = 0;
	m_blindFadeTime = 0;
	m_blindAlpha = 0;

	m_canSwitchObserverModes = true;
	m_lastLocation[0] = '\0';

	m_bitsDamageType &= ~(DMG_DROWN | DMG_DROWNRECOVER);
	m_rgbTimeBasedDamage[ITBD_DROWN_RECOVER] = 0;
	m_idrowndmg = 0;
	m_idrownrestored = 0;

#ifdef REGAMEDLL_ADD
	CSPlayer()->OnSpawn();
#endif

	if (m_iObserverC4State)
	{
		m_iObserverC4State = 0;

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("c4");
		MESSAGE_END();
	}

	if (m_bObserverHasDefuser)
	{
		m_bObserverHasDefuser = false;

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("defuser");
		MESSAGE_END();
	}

	MESSAGE_BEGIN(MSG_ONE, SVC_ROOMTYPE, nullptr, pev);
		WRITE_SHORT(int(CVAR_GET_FLOAT("room_type")));
	MESSAGE_END();

	if (g_pGameRules->IsFreezePeriod())
		m_bCanShoot = false;
	else
		m_bCanShoot = true;

	m_iNumSpawns++;
	InitStatusBar();

	for (i = 0; i < MAX_RECENT_PATH; i++)
		m_vRecentPath[i] = Vector(0, 0, 0);

	if (m_pActiveItem && !pev->viewmodel)
	{
		switch (m_pActiveItem->m_iId)
		{
		case WEAPON_AWP:
			pev->viewmodel = MAKE_STRING("models/v_awp.mdl");
			break;
		case WEAPON_G3SG1:
			pev->viewmodel = MAKE_STRING("models/v_g3sg1.mdl");
			break;
		case WEAPON_SCOUT:
			pev->viewmodel = MAKE_STRING("models/v_scout.mdl");
			break;
		case WEAPON_SG550:
			pev->viewmodel = MAKE_STRING("models/v_sg550.mdl");
			break;
		}
	}

	m_iFOV = DEFAULT_FOV;
	m_flNextDecalTime = 0;
	m_flTimeStepSound = 0;
	m_iStepLeft = 0;
	m_flFieldOfView = 0.5;
	m_bloodColor = BLOOD_COLOR_RED;
	m_flNextAttack = 0;
	m_flgeigerDelay = gpGlobals->time + 2;

	StartSneaking();

	m_iFlashBattery = 99;
	m_flFlashLightTime = 1;

#ifdef REGAMEDLL_ADD
	ReloadWeapons();
#endif

	pev->body = m_bHasDefuser ? 1 : 0;

	if (m_bMissionBriefing)
	{
		RemoveLevelText();
		m_bMissionBriefing = false;
	}

	m_flFallVelocity = 0;

	if (!g_skipCareerInitialSpawn)
	{
		g_pGameRules->GetPlayerSpawnSpot(this);
	}

	if (!pev->modelindex)
	{
		// get rid of the dependency on m_modelIndexPlayer.
		SET_MODEL(ENT(pev), "models/player.mdl");
		m_modelIndexPlayer = pev->modelindex;
	}

	pev->sequence = LookupActivity(ACT_IDLE);

	if (pev->flags & FL_DUCKING)
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
	else
		UTIL_SetSize(pev, VEC_HULL_MIN, VEC_HULL_MAX);

	// Override what CBasePlayer set for the view offset.
	pev->view_ofs = VEC_VIEW;
	Precache();

	m_HackedGunPos = Vector(0, 32, 0);

	if (m_iPlayerSound == SOUNDLIST_EMPTY)
	{
		ALERT(at_console, "Couldn't alloc player sound slot!\n");
	}

	m_iHideHUD &= ~(HIDEHUD_WEAPONS | HIDEHUD_HEALTH | HIDEHUD_TIMER | HIDEHUD_MONEY | HIDEHUD_CROSSHAIR);
	m_fNoPlayerSound = FALSE;
	m_pLastItem = nullptr;
	m_fWeapon = FALSE;
	m_pClientActiveItem = nullptr;
	m_iClientBattery = -1;
	m_fInitHUD = TRUE;

#ifdef REGAMEDLL_FIXES
	m_iClientHideHUD = -1;
#endif

	if (!m_bNotKilled)
	{
#ifndef REGAMEDLL_FIXES
		m_iClientHideHUD = -1;
#endif

		for (i = 0; i < MAX_AMMO_SLOTS; i++)
			m_rgAmmo[i] = 0;

		m_bHasPrimary = false;
		m_bHasNightVision = false;

#ifdef REGAMEDLL_FIXES
		m_iHideHUD |= HIDEHUD_WEAPONS;
#endif

		SendItemStatus();
	}
	else
	{
		for (i = 0; i < MAX_AMMO_SLOTS; i++)
			m_rgAmmoLast[i] = -1;
	}

	MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pev);
		WRITE_BYTE(0);
	MESSAGE_END();

	m_bNightVisionOn = false;

	for (i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pObserver = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pObserver))
			continue;

		if (pObserver->IsObservingPlayer(this))
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, nullptr, pObserver->pev);
				WRITE_BYTE(0);
			MESSAGE_END();

			pObserver->m_bNightVisionOn = false;
		}
	}

	m_lastx = m_lasty = 0;

	g_pGameRules->PlayerSpawn(this);

	m_bNotKilled = true;
	m_bIsDefusing = false;

	// Get rid of the progress bar...
	SetProgressBarTime(0);
	ResetMaxSpeed();

	UTIL_SetOrigin(pev, pev->origin);

	if (m_bIsVIP)
	{
		m_iKevlar = ARMOR_VESTHELM;
		pev->armorvalue = 200;
		HintMessage("#Hint_you_are_the_vip", TRUE, TRUE);
	}

	SetScoreboardAttributes();

	MESSAGE_BEGIN(MSG_ALL, gmsgTeamInfo);
		WRITE_BYTE(entindex());
		WRITE_STRING(GetTeamName(m_iTeam));
	MESSAGE_END();

	UpdateLocation(true);

	MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
		WRITE_BYTE(ENTINDEX(edict()));
		WRITE_SHORT(int(pev->frags));
		WRITE_SHORT(m_iDeaths);
		WRITE_SHORT(0);
		WRITE_SHORT(m_iTeam);
	MESSAGE_END();

	if (m_bHasChangedName)
	{
		char *infobuffer = GET_INFO_BUFFER(edict());

		if (!FStrEq(m_szNewName, GET_KEY_VALUE(infobuffer, "name")))
		{
			SET_CLIENT_KEY_VALUE(entindex(), infobuffer, "name", m_szNewName);
		}

		m_bHasChangedName = false;
		m_szNewName[0] = '\0';
	}

	UTIL_ScreenFade(this, Vector(0, 0, 0), 0.001);
	SyncRoundTimer();

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_SPAWNED, this);
	}

	m_allowAutoFollowTime = false;

	for (i = 0; i < COMMANDS_TO_TRACK; i++)
		m_flLastCommandTime[i] = -1;

#ifdef REGAMEDLL_FIXES
	// everything that comes after this, this spawn of the player a the game.
	if (m_bJustConnected)
		return;

	FireTargets("game_playerspawn", this, this, USE_TOGGLE, 0);
#endif
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, Precache)

void EXT_FUNC CBasePlayer::__API_HOOK(Precache)()
{
	// SOUNDS / MODELS ARE PRECACHED in ClientPrecache() (game specific)
	// because they need to precache before any clients have connected

	// init geiger counter vars during spawn and each time
	// we cross a level transition

	m_flgeigerRange = 1000;
	m_igeigerRangePrev = 1000;
	m_bitsDamageType = 0;
	m_bitsHUDDamage = -1;
	m_iClientBattery = -1;
	m_iTrain = TRAIN_NEW;

	// Make sure any necessary user messages have been registered
	LinkUserMessages();

	// won't update for 1/2 a second
	m_iUpdateTime = 5;

	if (gInitHUD)
		m_fInitHUD = TRUE;
}

int CBasePlayer::Save(CSave &save)
{
	if (!CBaseMonster::Save(save))
		return 0;

	return save.WriteFields("PLAYER", this, m_playerSaveData, ARRAYSIZE(m_playerSaveData));
}

void CBasePlayer::SetScoreboardAttributes(CBasePlayer *destination)
{
	if (destination)
	{
		SetScoreAttrib(destination);
		return;
	}

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pPlayer))
			continue;

		SetScoreboardAttributes(pPlayer);
	}
}

// Marks everything as new so the player will resend this to the hud.
NOXREF void CBasePlayer::RenewItems()
{
	;
}

int CBasePlayer::Restore(CRestore &restore)
{
	if (!CBaseMonster::Restore(restore))
		return 0;

	int status = restore.ReadFields("PLAYER", this, m_playerSaveData, ARRAYSIZE(m_playerSaveData));
	SAVERESTOREDATA *pSaveData = (SAVERESTOREDATA *)gpGlobals->pSaveData;

	// landmark isn't present.
	if (!pSaveData->fUseLandmark)
	{
		ALERT(at_console, "No Landmark:%s\n", pSaveData->szLandmarkName);

		// default to normal spawn
		edict_t *pentSpawnSpot = EntSelectSpawnPoint();

		pev->origin = pentSpawnSpot->v.origin + Vector(0, 0, 1);
		pev->angles = pentSpawnSpot->v.angles;
	}

	// Clear out roll
	pev->v_angle.z = 0;
	pev->angles = pev->v_angle;

	// turn this way immediately
	pev->fixangle = 1;

	// Copied from spawn() for now
	m_bloodColor = BLOOD_COLOR_RED;
	m_modelIndexPlayer = pev->modelindex;

	if (pev->flags & FL_DUCKING)
		UTIL_SetSize(pev, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX);
	else
		UTIL_SetSize(pev, VEC_HULL_MIN, VEC_HULL_MAX);

#ifdef BUILD_LATEST_FIXES
	TabulateAmmo();
#endif

	m_flDisplayHistory &= ~DHM_CONNECT_CLEAR;
	SetScoreboardAttributes();

	return status;
}

void CBasePlayer::Reset()
{
	pev->frags = 0;
	m_iDeaths = 0;

#ifndef REGAMEDLL_ADD
	m_iAccount = 0;
#endif

#ifndef REGAMEDLL_FIXES
	MESSAGE_BEGIN(MSG_ONE, gmsgMoney, nullptr, pev);
		WRITE_LONG(m_iAccount);
		WRITE_BYTE(0);
	MESSAGE_END();
#endif

	m_bNotKilled = false;

#ifdef REGAMEDLL_FIXES
	// RemoveShield() included
	RemoveAllItems(TRUE);
#else
	RemoveShield();
#endif

	CheckStartMoney();
	AddAccount(startmoney.value, RT_PLAYER_RESET);

	MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
		WRITE_BYTE(ENTINDEX(edict()));
		WRITE_SHORT(0);
		WRITE_SHORT(0);
		WRITE_SHORT(0);
		WRITE_SHORT(m_iTeam);
	MESSAGE_END();

#ifdef REGAMEDLL_ADD
	if (CSPlayer()->GetProtectionState() == CCSPlayer::ProtectionSt_Active) {
		RemoveSpawnProtection();
	}

	CSPlayer()->ResetAllStats();
#endif
}

NOXREF void CBasePlayer::SelectNextItem(int iItem)
{
	CBasePlayerItem *pItem = m_rgpPlayerItems[iItem];

	if (!pItem)
	{
		return;
	}

#ifdef REGAMEDLL_FIXES
	if (m_pActiveItem && !m_pActiveItem->CanHolster())
		return;
#endif

	if (pItem == m_pActiveItem)
	{
		pItem = m_pActiveItem->m_pNext;

		if (!pItem)
		{
			return;
		}

		CBasePlayerItem *pLast = pItem;

		while (pLast->m_pNext)
			pLast = pLast->m_pNext;

		pLast->m_pNext = m_pActiveItem;
		m_pActiveItem->m_pNext = nullptr;
		m_rgpPlayerItems[iItem] = pItem;
	}

	ResetAutoaim();

	if (m_pActiveItem)
	{
		m_pActiveItem->Holster();
	}

	if (HasShield())
	{
		CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)m_pActiveItem;
		pWeapon->m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
		m_bShieldDrawn = false;
	}

	m_pLastItem = m_pActiveItem;
	m_pActiveItem = pItem;

	UpdateShieldCrosshair(true);

	m_pActiveItem->Deploy();
	m_pActiveItem->UpdateItemInfo();

	ResetMaxSpeed();
}

void CBasePlayer::SelectItem(const char *pstr)
{
	if (!pstr)
	{
		return;
	}

#ifdef REGAMEDLL_FIXES
	if (m_pActiveItem && !m_pActiveItem->CanHolster())
		return;
#endif

	auto pItem = GetItemByName(pstr);
	if (!pItem || pItem == m_pActiveItem)
		return;

#ifdef REGAMEDLL_FIXES
	if (!pItem->CanDeploy())
		return;
#endif

	ResetAutoaim();

	// FIX, this needs to queue them up and delay
	if (m_pActiveItem)
	{
		m_pActiveItem->Holster();
	}

	m_pLastItem = m_pActiveItem;
	m_pActiveItem = pItem;

	CBasePlayerWeapon *pWeapon = (CBasePlayerWeapon *)m_pActiveItem;
	pWeapon->m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	m_bShieldDrawn = false;
	UpdateShieldCrosshair(true);

	m_pActiveItem->Deploy();
	m_pActiveItem->UpdateItemInfo();

	ResetMaxSpeed();
}

void CBasePlayer::SelectLastItem()
{
	if (m_pActiveItem && !m_pActiveItem->CanHolster())
		return;

	if (!m_pLastItem || m_pLastItem == m_pActiveItem)
	{
		for (int i = PRIMARY_WEAPON_SLOT; i <= KNIFE_SLOT; i++)
		{
			CBasePlayerItem *pItem = m_rgpPlayerItems[i];
			if (pItem && pItem != m_pActiveItem)
			{
				m_pLastItem = pItem;
				break;
			}
		}
	}

	if (!m_pLastItem || m_pLastItem == m_pActiveItem)
		return;

#ifdef REGAMEDLL_FIXES
	if (!m_pLastItem->CanDeploy())
		return;
#endif

	ResetAutoaim();

	if (m_pActiveItem)
	{
		m_pActiveItem->Holster();
	}

	if (HasShield())
	{
		CBasePlayerWeapon *pWeapon = static_cast<CBasePlayerWeapon *>(m_pActiveItem);
		if (pWeapon)
			pWeapon->m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

		m_bShieldDrawn = false;
	}

	SWAP(m_pActiveItem, m_pLastItem);

	m_pActiveItem->Deploy();
	m_pActiveItem->UpdateItemInfo();

	UpdateShieldCrosshair(true);

	ResetMaxSpeed();
}

// HasWeapons - do I have any weapons at all?
bool CBasePlayer::HasWeapons()
{
	for (auto item : m_rgpPlayerItems)
	{
		if (item)
			return true;
	}

	return false;
}

NOXREF void CBasePlayer::SelectPrevItem(int iItem)
{
	;
}

const char *CBasePlayer::TeamID()
{
	// Not fully connected yet
	if (!pev)
		return "";

	// return their team name
	return m_szTeamName;
}

void CSprayCan::Spawn(entvars_t *pevOwner)
{
#ifdef REGAMEDLL_FIXES
	pev->origin = pevOwner->origin + pevOwner->view_ofs;
#else
	pev->origin = pevOwner->origin + Vector(0, 0, 32);
#endif

	pev->angles = pevOwner->v_angle;
	pev->owner = ENT(pevOwner);
	pev->frame = 0;

	pev->nextthink = gpGlobals->time + 0.1f;
	EMIT_SOUND(ENT(pev), CHAN_VOICE, "player/sprayer.wav", VOL_NORM, ATTN_NORM);
}

void CSprayCan::Think()
{
	CBasePlayer *pPlayer = GET_PRIVATE<CBasePlayer>(pev->owner);

	int nFrames = -1;
	if (pPlayer)
	{
		nFrames = pPlayer->GetCustomDecalFrames();
	}

	TraceResult tr;
	int playernum = ENTINDEX(pev->owner);

	UTIL_MakeVectors(pev->angles);
	UTIL_TraceLine(pev->origin, pev->origin + gpGlobals->v_forward * 128, ignore_monsters, pev->owner, &tr);

	// No customization present.
	if (nFrames == -1)
	{
		UTIL_DecalTrace(&tr, DECAL_LAMBDA6);
		UTIL_Remove(this);
	}
	else
	{
		UTIL_PlayerDecalTrace(&tr, playernum, pev->frame, TRUE);

		// Just painted last custom frame.
		if (pev->frame++ >= (nFrames - 1))
			UTIL_Remove(this);
	}

	pev->nextthink = gpGlobals->time + 0.1f;
}

void CBloodSplat::Spawn(entvars_t *pevOwner)
{
	pev->origin = pevOwner->origin + Vector(0, 0, 32);
	pev->angles = pevOwner->v_angle;
	pev->owner = ENT(pevOwner);

	SetThink(&CBloodSplat::Spray);
	pev->nextthink = gpGlobals->time + 0.1f;
}

void CBloodSplat::Spray()
{
	TraceResult tr;
	if (g_Language != LANGUAGE_GERMAN)
	{
		UTIL_MakeVectors(pev->angles);
		UTIL_TraceLine(pev->origin, pev->origin + gpGlobals->v_forward * 128, ignore_monsters, pev->owner, &tr);
		UTIL_BloodDecalTrace(&tr, BLOOD_COLOR_RED);
	}

	SetThink(&CBloodSplat::SUB_Remove);
	pev->nextthink = gpGlobals->time + 0.1f;
}

LINK_HOOK_CLASS_CHAIN(CBaseEntity *, CBasePlayer, GiveNamedItem, (const char *pszName), pszName)

CBaseEntity *EXT_FUNC CBasePlayer::__API_HOOK(GiveNamedItem)(const char *pszName)
{
	string_t istr = MAKE_STRING(pszName);
	edict_t *pent = CREATE_NAMED_ENTITY(istr);

	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in GiveNamedItem!\n");
		return nullptr;
	}

	pent->v.origin = pev->origin;
	pent->v.spawnflags |= SF_NORESPAWN;

	DispatchSpawn(pent);
	DispatchTouch(pent, ENT(pev));

	return GET_PRIVATE<CBaseEntity>(pent);
}

// external function for 3rd-party
CBaseEntity *CBasePlayer::GiveNamedItemEx(const char *pszName)
{
	string_t istr = ALLOC_STRING(pszName);
	edict_t *pent = CREATE_NAMED_ENTITY(istr);

	if (FNullEnt(pent))
	{
		ALERT(at_console, "NULL Ent in GiveNamedItemEx classname `%s`!\n", pszName);
		return nullptr;
	}

	pent->v.origin = pev->origin;
	pent->v.spawnflags |= SF_NORESPAWN;

	DispatchSpawn(pent);
	DispatchTouch(pent, ENT(pev));

	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pent);

#ifdef REGAMEDLL_FIXES
	// not allow the item to fall to the ground.
	if (FNullEnt(pent->v.owner) || pent->v.owner != edict())
	{
		pent->v.flags |= FL_KILLME;
		UTIL_Remove(pEntity);
		return nullptr;
	}
#endif

	return pEntity;
}

// Creates a copy of the specified entity (pEntitySource) and gives it to the player
// The cloned entity inherits base properties (entvars) of the original entity
// Returns Pointer to the cloned entity, or NULL if the entity cannot be created
CBaseEntity *CBasePlayer::GiveCopyItem(CBaseEntity *pEntitySource)
{
	edict_t *pEdict = CREATE_NAMED_ENTITY(pEntitySource->pev->classname);
	if (FNullEnt(pEdict))
	{
		ALERT(at_console, "NULL Ent in GiveCloneItem classname `%s`!\n", STRING(pEntitySource->pev->classname));
		return nullptr;
	}

	// copy entity properties
	Q_memcpy(&pEdict->v, pEntitySource->pev, sizeof(pEdict->v));

	pEdict->v.pContainingEntity = pEdict;
	pEdict->v.origin = pev->origin;
	pEdict->v.spawnflags |= SF_NORESPAWN;
	pEdict->v.owner = NULL; // will re-link owner after touching
	pEdict->v.chain = ENT(pEntitySource->pev); // refer to source copy entity

	DispatchSpawn(pEdict);
	DispatchTouch(pEdict, ENT(pev));
	pEdict->v.chain = NULL;

	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pEdict);

	// not allow the item to fall to the ground.
	if (FNullEnt(pEdict->v.owner) || pEdict->v.owner != edict())
	{
		pEdict->v.flags |= FL_KILLME;
		UTIL_Remove(pEntity);
		return nullptr;
	}

	return pEntity;
}

CBaseEntity *FindEntityForward(CBaseEntity *pEntity)
{
	TraceResult tr;
	Vector vecStart(pEntity->pev->origin + pEntity->pev->view_ofs);

	UTIL_MakeVectors(pEntity->pev->v_angle);
	UTIL_TraceLine(vecStart, vecStart + gpGlobals->v_forward * 8192, dont_ignore_monsters, pEntity->edict(), &tr);

	if (tr.flFraction != 1.0f && !FNullEnt(tr.pHit))
	{
		CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);
		return pHit;
	}

	return nullptr;
}

BOOL CBasePlayer::FlashlightIsOn()
{
	return pev->effects & EF_DIMLIGHT;
}

void CBasePlayer::FlashlightTurnOn()
{
	if (!g_pGameRules->FAllowFlashlight())
		return;

	if (pev->weapons & (1 << WEAPON_SUIT))
	{
		EMIT_SOUND(ENT(pev), CHAN_ITEM, SOUND_FLASHLIGHT_ON, VOL_NORM, ATTN_NORM);

		pev->effects |= EF_DIMLIGHT;

		MESSAGE_BEGIN(MSG_ONE, gmsgFlashlight, nullptr, pev);
			WRITE_BYTE(1);
			WRITE_BYTE(m_iFlashBattery);
		MESSAGE_END();

		m_flFlashLightTime = gpGlobals->time + FLASH_DRAIN_TIME;
	}
}

void CBasePlayer::FlashlightTurnOff()
{
	EMIT_SOUND(ENT(pev), CHAN_ITEM, SOUND_FLASHLIGHT_OFF, VOL_NORM, ATTN_NORM);

	pev->effects &= ~EF_DIMLIGHT;
	MESSAGE_BEGIN(MSG_ONE, gmsgFlashlight, nullptr, pev);
		WRITE_BYTE(0);
		WRITE_BYTE(m_iFlashBattery);
	MESSAGE_END();

	m_flFlashLightTime = gpGlobals->time + FLASH_CHARGE_TIME;
}

// When recording a demo, we need to have the server tell us the entire client state so that the client side .dll can behave correctly.
// Reset stuff so that the state is transmitted.
void CBasePlayer::ForceClientDllUpdate()
{
#ifdef REGAMEDLL_FIXES
	// fix for https://github.com/ValveSoftware/halflife/issues/1567
	m_iClientHideHUD = -1;
	m_flNextSBarUpdateTime = -1;
	InitStatusBar();
#ifdef BUILD_LATEST
	m_tmNextAccountHealthUpdate = -1;
#endif
#endif

	m_iClientHealth = -1;
	m_iClientBattery = -1;

	m_fWeapon = FALSE;		// Force weapon send
	m_fInitHUD = TRUE;		// Force HUD gmsgResetHUD message
	m_iTrain |= TRAIN_NEW;	// Force new train message.

	// Now force all the necessary messages to be sent.
	UpdateClientData();
	HandleSignals();

#ifdef REGAMEDLL_FIXES
	// Update HUD backpack ammo
	for (int i = 0; i < MAX_AMMO_SLOTS; i++)
		m_rgAmmoLast[i] = -1;

	// Force update server name
	MESSAGE_BEGIN(MSG_ONE, gmsgServerName, nullptr, pev);
		WRITE_STRING(CVAR_GET_STRING("hostname"));
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, SVC_ROOMTYPE, nullptr, pev);
		WRITE_SHORT(int(CVAR_GET_FLOAT("room_type")));
	MESSAGE_END();

	SendItemStatus();

	// Loop through all active players and update their info to the client who started recording the demo
	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pPlayer))
			continue;

		if (pev->deadflag == DEAD_NO)
		{
			// NOTE: Don't use here PlayerRelationShip,
			// because we have to send a radar message about the players in the team anyway,
			// even if they are not teammates
			bool sameTeam = pPlayer->m_iTeam == m_iTeam;
			if (sameTeam)
			{
				const Vector &vecOrigin = CSGameRules()->IsFreeForAll() ?
					g_vecZero : pPlayer->pev->origin;

				MESSAGE_BEGIN(MSG_ONE, gmsgRadar, nullptr, pev);
					WRITE_BYTE(pPlayer->entindex());
					WRITE_COORD(vecOrigin.x);
					WRITE_COORD(vecOrigin.y);
					WRITE_COORD(vecOrigin.z);
				MESSAGE_END();
			}

			// Update last location of players
			if (sameTeam || pPlayer->m_iTeam == SPECTATOR)
			{
				if (pPlayer->m_lastLocation[0])
				{
					MESSAGE_BEGIN(MSG_ONE, gmsgLocation, nullptr, pev);
						WRITE_BYTE(pPlayer->entindex());
						WRITE_STRING(pPlayer->m_lastLocation);
					MESSAGE_END();
				}
			}
		}

		// Update team info
		MESSAGE_BEGIN(MSG_ONE, gmsgTeamInfo, nullptr, pev);
			WRITE_BYTE(pPlayer->entindex());
			WRITE_STRING(GetTeamName(pPlayer->m_iTeam));
		MESSAGE_END();

		// Update score info Frags, Deaths, etc
		MESSAGE_BEGIN(MSG_ONE, gmsgScoreInfo, nullptr, pev);
			WRITE_BYTE(pPlayer->entindex());
			WRITE_SHORT(int(pPlayer->pev->frags));
			WRITE_SHORT(pPlayer->m_iDeaths);
			WRITE_SHORT(0);
			WRITE_SHORT(pPlayer->m_iTeam);
		MESSAGE_END();

		// Update player attributes DEAD, BOMB, VIP etc
		pPlayer->SetScoreAttrib(this);
	}
#endif
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, ImpulseCommands)

void EXT_FUNC CBasePlayer::__API_HOOK(ImpulseCommands)()
{
	TraceResult tr;

	// Handle use events
	PlayerUse();

	int iImpulse = pev->impulse;

	switch (iImpulse)
	{
		case 99:
		{
			int iOn;

			if (!gmsgLogo)
			{
				iOn = 1;
				gmsgLogo = REG_USER_MSG("Logo", 1);
			}
			else
				iOn = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgLogo, nullptr, pev);
				WRITE_BYTE(iOn);
			MESSAGE_END();

			if (!iOn)
				gmsgLogo = 0;

			break;
		}
		case 100:
		{
			// temporary flashlight for level designers
			if (FlashlightIsOn())
				FlashlightTurnOff();
			else
				FlashlightTurnOn();

			break;
		}
		case 201:
		{
			// paint decal
			if (gpGlobals->time < m_flNextDecalTime)
			{
				// too early!
				break;
			}

			UTIL_MakeVectors(pev->v_angle);
			UTIL_TraceLine(pev->origin + pev->view_ofs, pev->origin + pev->view_ofs + gpGlobals->v_forward * 128, ignore_monsters, edict(), &tr);

			if (tr.flFraction != 1.0f)
			{
				// line hit something, so paint a decal
				m_flNextDecalTime = gpGlobals->time + CVAR_GET_FLOAT("decalfrequency");
				CSprayCan *pCan = GetClassPtr<CCSSprayCan>((CSprayCan *)nullptr);
				pCan->Spawn(pev);
			}
			break;
		}
		default:
			// check all of the cheat impulse commands now
			CheatImpulseCommands(iImpulse);
	}

	pev->impulse = 0;
}

void CBasePlayer::CheatImpulseCommands(int iImpulse)
{
	if (!CVAR_GET_FLOAT("sv_cheats"))
		return;

	CBaseEntity *pEntity;
	TraceResult tr;

	switch (iImpulse)
	{
		case 101:
#ifdef REGAMEDLL_ADD
			AddAccount(int(maxmoney.value));
			ALERT(at_console, "Crediting %s with $%i\n", STRING(pev->netname), int(maxmoney.value));
#else
			AddAccount(16000);
			ALERT(at_console, "Crediting %s with $16000\n", STRING(pev->netname));
#endif
			break;
		case 102:
			CGib::SpawnRandomGibs(pev, 1, 1);
			break;
#ifndef REGAMEDLL_FIXES
		case 103:
		{
			// What the hell are you doing?
			pEntity = FindEntityForward(this);

			if (pEntity)
			{
				CBaseMonster *pMonster = pEntity->MyMonsterPointer();

				if (pMonster)
					pMonster->ReportAIState();
			}
			break;
		}
#endif
		case 104:
			// Dump all of the global state varaibles (and global entity names)
			gGlobalState.DumpGlobals();
			break;
#ifndef REGAMEDLL_FIXES
		case 105:
		{
			// player makes no sound for monsters to hear.
			if (m_fNoPlayerSound)
			{
				ALERT(at_console, "Player is audible\n");
				m_fNoPlayerSound = FALSE;
			}
			else
			{
				ALERT(at_console, "Player is silent\n");
				m_fNoPlayerSound = TRUE;
			}
			break;
		}
#endif
		case 106:
		{
			// Give me the classname and targetname of this entity.
			pEntity = FindEntityForward(this);

			if (pEntity)
			{
				ALERT(at_console, "Classname: %s", STRING(pEntity->pev->classname));

				if (!FStringNull(pEntity->pev->targetname))
					ALERT(at_console, " - Targetname: %s\n", STRING(pEntity->pev->targetname));
				else
					ALERT(at_console, " - TargetName: No Targetname\n");

				ALERT(at_console, "Model: %s\n", STRING(pEntity->pev->model));

				if (pEntity->pev->globalname)
					ALERT(at_console, "Globalname: %s\n", STRING(pEntity->pev->globalname));
			}
			break;
		}
		case 107:
		{
			TraceResult tr;
			edict_t *pWorld = INDEXENT(0);

			Vector start = pev->origin + pev->view_ofs;
			Vector end = start + gpGlobals->v_forward * 1024;
			UTIL_TraceLine(start, end, ignore_monsters, edict(), &tr);

			if (tr.pHit)
				pWorld = tr.pHit;

			const char *pszTextureName = TRACE_TEXTURE(pWorld, start, end);

			if (pszTextureName)
				ALERT(at_console, "Texture: %s\n", pszTextureName);

			break;
		}
#ifdef REGAMEDLL_ADD
		// noclip with air acceleration
		case 200:
		{
			if (pev->movetype == MOVETYPE_WALK)
			{
				pev->movetype = MOVETYPE_NOCLIP;
				pev->fuser3 = MAX_PLAYER_RUN_MODIFIER_SPEED; // air acceleration increases xN times
				ALERT(at_console, "noclip ON\n");
			}
			else
			{
				pev->movetype = MOVETYPE_WALK;
				pev->fuser3 = 0;
				ALERT(at_console, "noclip OFF\n");
			}

			break;
		}
#endif
		case 202:
		{
			// Random blood splatter
			UTIL_MakeVectors(pev->v_angle);
			UTIL_TraceLine(pev->origin + pev->view_ofs, pev->origin + pev->view_ofs + gpGlobals->v_forward * 128, ignore_monsters, edict(), &tr);

			if (tr.flFraction != 1.0f)
			{
				// line hit something, so paint a decal
				CBloodSplat *pBlood = GetClassPtr<CCSBloodSplat>((CBloodSplat *)nullptr);
				pBlood->Spawn(pev);
			}
			break;
		}
		case 203:
		{
			// remove creature.
			pEntity = FindEntityForward(this);

			if (pEntity && pEntity->pev->takedamage != DAMAGE_NO)
			{
				pEntity->SetThink(&CBaseEntity::SUB_Remove);
			}
			break;
		}
		case 204:
		{
			TraceResult tr;
			Vector dir(0, 0, 1);

			UTIL_BloodDrips(pev->origin, BLOOD_COLOR_RED, 2000);

			for (int r = 1; r < 4; r++)
			{
				float bloodRange = r * 50.0f;
				for (int i = 0; i < 50; i++)
				{
					dir.x = RANDOM_FLOAT(-1, 1);
					dir.y = RANDOM_FLOAT(-1, 1);
					dir.z = RANDOM_FLOAT(-1, 1);

					if (dir.x || dir.y || dir.z)
						dir.NormalizeInPlace();
					else
						dir.z = -1.0f;

					UTIL_TraceLine(EyePosition(), EyePosition() + dir * bloodRange, ignore_monsters, pev->pContainingEntity, &tr);

					if (tr.flFraction < 1.0f)
						UTIL_BloodDecalTrace(&tr, BLOOD_COLOR_RED);
				}
			}
			break;
		}
#ifdef REGAMEDLL_ADD
		case 255:
		{
			// Give weapons
			for (int wpnid = WEAPON_NONE + 1; wpnid < MAX_WEAPONS; wpnid++)
			{
				// unwanted candidates
				if (wpnid == WEAPON_GLOCK
					|| wpnid == WEAPON_C4
					|| wpnid == WEAPON_KNIFE)
					continue;

				// If by some case the weapon got invalid
				const auto pInfo = GetWeaponInfo(wpnid);
				if (pInfo) {
					GiveNamedItemEx(pInfo->entityName);
					GiveAmmo(pInfo->maxRounds, pInfo->ammoName2);
				}
			}

#ifdef REGAMEDLL_API
			CSPlayer()->m_iWeaponInfiniteAmmo = WPNMODE_INFINITE_BPAMMO;
			CSPlayer()->m_iWeaponInfiniteIds  = WEAPON_ALLWEAPONS;
#endif

			GiveNamedItemEx("item_longjump");
			GiveNamedItemEx("item_thighpack");
			GiveNamedItemEx("item_kevlar");
			break;
		}
#endif
	}
}

void OLD_CheckBuyZone(CBasePlayer *pPlayer)
{
	const char *pszSpawnClass = nullptr;

#ifdef REGAMEDLL_FIXES
	if (!CSGameRules()->CanPlayerBuy(pPlayer))
	{
		return;
	}
#endif

	if (pPlayer->m_iTeam == TERRORIST)
	{
		pszSpawnClass = "info_player_deathmatch";
	}
	else if (pPlayer->m_iTeam == CT)
	{
		pszSpawnClass = "info_player_start";
	}

	if (pszSpawnClass)
	{
		CBaseEntity *pSpot = nullptr;
		while ((pSpot = UTIL_FindEntityByClassname(pSpot, pszSpawnClass)))
		{
			if ((pSpot->pev->origin - pPlayer->pev->origin).Length() < 200.0f)
			{
				pPlayer->m_signals.Signal(SIGNAL_BUY);
#ifdef REGAMEDLL_FIXES
				break;
#endif
			}
		}
	}
}

void OLD_CheckBombTarget(CBasePlayer *pPlayer)
{
	CBaseEntity *pSpot = nullptr;
	while ((pSpot = UTIL_FindEntityByClassname(pSpot, "info_bomb_target")))
	{
		if ((pSpot->pev->origin - pPlayer->pev->origin).Length() <= 256.0f)
		{
			pPlayer->m_signals.Signal(SIGNAL_BOMB);
#ifdef REGAMEDLL_FIXES
			break;
#endif
		}
	}
}

void OLD_CheckRescueZone(CBasePlayer *pPlayer)
{
	CBaseEntity *pSpot = nullptr;
	while ((pSpot = UTIL_FindEntityByClassname(pSpot, "info_hostage_rescue")))
	{
		if ((pSpot->pev->origin - pPlayer->pev->origin).Length() <= MAX_HOSTAGES_RESCUE_RADIUS)
		{
			pPlayer->m_signals.Signal(SIGNAL_RESCUE);
#ifdef REGAMEDLL_FIXES
			break;
#endif
		}
	}
}

void CBasePlayer::HandleSignals()
{
	if (CSGameRules()->IsMultiplayer())
	{

#ifdef REGAMEDLL_ADD
		if (buytime.value != 0.0f)
#endif
		{
#ifdef REGAMEDLL_ADD
			if (buy_anywhere.value)
			{
				if (pev->deadflag == DEAD_NO && (m_iTeam == TERRORIST || m_iTeam == CT)
					&& !(m_signals.GetSignal() & SIGNAL_BUY)
					// Restricted by map rules
					&& CSGameRules()->CanPlayerBuy(this)
					)
				{
					// 0 = default. 1 = both teams. 2 = Terrorists. 3 = Counter-Terrorists.
					if (buy_anywhere.value == 1
						|| (buy_anywhere.value == 2 && m_iTeam == TERRORIST)
						|| (buy_anywhere.value == 3 && m_iTeam == CT)
						)
					{
						m_signals.Signal(SIGNAL_BUY);
					}
				}
			}
#endif
			{
				if (!CSGameRules()->m_bMapHasBuyZone)
					OLD_CheckBuyZone(this);
			}
		}

#ifdef REGAMEDLL_ADD
		if (m_bHasC4 && (plant_c4_anywhere.value || CSPlayer()->m_bPlantC4Anywhere))
		{
			if (IsAlive() && (m_iTeam == TERRORIST || m_iTeam == CT)
				&& !(m_signals.GetSignal() & SIGNAL_BOMB))
			{
				m_signals.Signal(SIGNAL_BOMB);
			}
		}
#endif

		if (!CSGameRules()->m_bMapHasBombZone)
			OLD_CheckBombTarget(this);

		if (!CSGameRules()->m_bMapHasRescueZone)
			OLD_CheckRescueZone(this);
	}

	int state = m_signals.GetSignal();
	int changed = m_signals.GetState() ^ state;

	m_signals.Update();

	if (changed & SIGNAL_BUY)
	{
		if (state & SIGNAL_BUY)
			BuyZoneIcon_Set(this);
		else
			BuyZoneIcon_Clear(this);
	}
	if (changed & SIGNAL_BOMB)
	{
		if (state & SIGNAL_BOMB)
			BombTargetFlash_Set(this);
		else
			BombTargetFlash_Clear(this);
	}
	if (changed & SIGNAL_RESCUE)
	{
		if (state & SIGNAL_RESCUE)
			RescueZoneIcon_Set(this);
		else
			RescueZoneIcon_Clear(this);
	}
	if (changed & SIGNAL_ESCAPE)
	{
		if (state & SIGNAL_ESCAPE)
			EscapeZoneIcon_Set(this);
		else
			EscapeZoneIcon_Clear(this);
	}
	if (changed & SIGNAL_VIPSAFETY)
	{
		if (state & SIGNAL_VIPSAFETY)
			VIP_SafetyZoneIcon_Set(this);
		else
			VIP_SafetyZoneIcon_Clear(this);
	}
}

LINK_HOOK_CLASS_CHAIN(BOOL, CBasePlayer, AddPlayerItem, (CBasePlayerItem *pItem), pItem)

// Add a weapon to the player (Item == Weapon == Selectable Object)
BOOL EXT_FUNC CBasePlayer::__API_HOOK(AddPlayerItem)(CBasePlayerItem *pItem)
{
	CBasePlayerItem *pInsert = m_rgpPlayerItems[pItem->iItemSlot()];
	while (pInsert)
	{
		if (FClassnameIs(pInsert->pev, STRING(pItem->pev->classname)))
		{
			if (pItem->AddDuplicate(pInsert))
			{
				g_pGameRules->PlayerGotWeapon(this, pItem);
				pItem->CheckRespawn();

				// ugly hack to update clip w/o an update clip message
				pItem->UpdateItemInfo();

				if (m_pActiveItem)
					m_pActiveItem->UpdateItemInfo();

				pItem->Kill();
			}

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
		pItem->m_pNext = m_rgpPlayerItems[pItem->iItemSlot()];
		m_rgpPlayerItems[pItem->iItemSlot()] = pItem;

		if (HasShield())
			pev->gamestate = HITGROUP_SHIELD_ENABLED;

		// should we switch to this item?
		if (g_pGameRules->FShouldSwitchWeapon(this, pItem))
		{
			if (!m_bShieldDrawn)
			{
				SwitchWeapon(pItem);
			}
		}
#ifdef REGAMEDLL_FIXES
		m_iHideHUD &= ~HIDEHUD_WEAPONS;
#endif

		return TRUE;
	}

	return FALSE;
}

LINK_HOOK_CLASS_CHAIN(BOOL, CBasePlayer, RemovePlayerItem, (CBasePlayerItem *pItem), pItem)

BOOL EXT_FUNC CBasePlayer::__API_HOOK(RemovePlayerItem)(CBasePlayerItem *pItem)
{
	if (m_pActiveItem == pItem)
	{
		ResetAutoaim();

#ifdef REGAMEDLL_FIXES
		// if (m_iFOV != DEFAULT_FOV)
		{
			pev->fov = m_iFOV = m_iLastZoom = DEFAULT_FOV;
			m_bResumeZoom = false;

			ResetMaxSpeed();
		}
#endif

		pItem->pev->nextthink = 0;

		pItem->SetThink(nullptr);
		m_pActiveItem = nullptr;

		pev->viewmodel = 0;
		pev->weaponmodel = 0;
	}
#ifndef REGAMEDLL_FIXES
	else
#endif
	if (m_pLastItem == pItem)
		m_pLastItem = nullptr;

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

LINK_HOOK_CLASS_CHAIN(int, CBasePlayer, GiveAmmo, (int iCount, const char *szName, int iMax), iCount, szName, iMax)

// Returns the unique ID for the ammo, or -1 if error
int EXT_FUNC CBasePlayer::__API_HOOK(GiveAmmo)(int iCount, const char *szName, int iMax)
{
	if (pev->flags & FL_SPECTATOR)
		return -1;

	if (!szName)
	{
		// no ammo.
		return -1;
	}

	if (iMax == -1)
		iMax = MaxAmmoCarry(szName);

	if (!g_pGameRules->CanHaveAmmo(this, szName, iMax))
	{
		// game rules say I can't have any more of this ammo type.
		return -1;
	}

	int i = GetAmmoIndex(szName);
	if (i < 0 || i >= MAX_AMMO_SLOTS)
		return -1;

	int iAdd = Q_min(iCount, iMax - m_rgAmmo[i]);
	if (iAdd < 1)
		return i;

	m_rgAmmo[i] += iAdd;

	// make sure the ammo messages have been linked first
	if (gmsgAmmoPickup)
	{
		// Send the message that ammo has been picked up
		MESSAGE_BEGIN(MSG_ONE, gmsgAmmoPickup, nullptr, pev);
			WRITE_BYTE(i); // ammo ID
			WRITE_BYTE(iAdd); // amount
		MESSAGE_END();
	}

	TabulateAmmo();
	return i;
}

// Called every frame by the player PreThink
void CBasePlayer::ItemPreFrame()
{
#ifdef CLIENT_WEAPONS
	if (m_flNextAttack > 0)
		return;
#else
	if (gpGlobals->time < m_flNextAttack)
		return;
#endif

	if (!m_pActiveItem)
		return;

	m_pActiveItem->ItemPreFrame();
}

// Called every frame by the player PostThink
void CBasePlayer::ItemPostFrame()
{
	static int fInSelect = FALSE;

	// check if the player is using a tank
	if (m_pTank)
		return;

	if (m_pActiveItem)
	{
		if (HasShield() && IsReloading())
		{
			if (pev->button & IN_ATTACK2)
				m_flNextAttack = 0;
		}
	}

#ifdef CLIENT_WEAPONS
	if (m_flNextAttack > 0)
#else
	if (gpGlobals->time < m_flNextAttack)
#endif
		return;

	ImpulseCommands();

	if (m_pActiveItem)
		m_pActiveItem->ItemPostFrame();
}

int CBasePlayer::AmmoInventory(int iAmmoIndex)
{
	if (iAmmoIndex == -1)
		return -1;

	return m_rgAmmo[iAmmoIndex];
}

int CBasePlayer::GetAmmoIndex(const char *psz)
{
	if (!psz)
		return -1;

	for (int i = 1; i < MAX_AMMO_SLOTS; i++)
	{
		if (!CBasePlayerItem::m_AmmoInfoArray[i].pszName)
			continue;

		if (!Q_stricmp(CBasePlayerItem::m_AmmoInfoArray[i].pszName, psz))
			return i;
	}

	return -1;
}

void CBasePlayer::SendAmmoUpdate()
{
	for (int i = 0; i < MAX_AMMO_SLOTS; i++)
	{
		if (m_rgAmmo[i] != m_rgAmmoLast[i])
		{
			m_rgAmmoLast[i] = m_rgAmmo[i];

			// send "Ammo" update message
			MESSAGE_BEGIN(MSG_ONE, gmsgAmmoX, nullptr, pev);
				WRITE_BYTE(i);
				WRITE_BYTE(clamp(m_rgAmmo[i], 0, 255)); // clamp the value to one byte
			MESSAGE_END();
		}
	}
}

void CBasePlayer::SendHostagePos()
{
	CHostage *pHostage = nullptr;

	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgHostagePos, nullptr, pev);
			WRITE_BYTE(1);
			WRITE_BYTE(pHostage->m_iHostageIndex);
			WRITE_COORD(pHostage->pev->origin.x);
			WRITE_COORD(pHostage->pev->origin.y);
			WRITE_COORD(pHostage->pev->origin.z);
		MESSAGE_END();
	}

	SendHostageIcons();
}

void CBasePlayer::SendHostageIcons()
{
	if (!AreRunningCZero()
#ifdef REGAMEDLL_ADD
		&& !show_scenarioicon.value
#endif
		)
	{
		return;
	}

	int hostagesCount = 0;
	CHostage *pHostage = nullptr;

	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		if (pHostage->IsAlive())
			hostagesCount++;
	}

	if (hostagesCount > MAX_HOSTAGE_ICON)
		hostagesCount = MAX_HOSTAGE_ICON;

	char buf[18];
	Q_snprintf(buf, ARRAYSIZE(buf), "hostage%d", hostagesCount);

	if (hostagesCount)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgScenarioIcon, nullptr, pev);
			WRITE_BYTE(1);		// active
			WRITE_STRING(buf);	// sprite
			WRITE_BYTE(0);
		MESSAGE_END();
	}
	else
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgScenarioIcon, nullptr, pev);
			WRITE_BYTE(0);		// active
		MESSAGE_END();
	}
}

void CBasePlayer::SendWeatherInfo()
{
	auto SendReceiveW = [&](BYTE byte)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgReceiveW, nullptr, pev);
				WRITE_BYTE(byte);
		MESSAGE_END();
	};

	/* Rain */
	if (UTIL_FindEntityByClassname(nullptr, "env_rain"))
		return SendReceiveW(1);

	if (UTIL_FindEntityByClassname(nullptr, "func_rain"))
		return SendReceiveW(1);

	/* Snow */
	if (UTIL_FindEntityByClassname(nullptr, "env_snow"))
		return SendReceiveW(2);

	if (UTIL_FindEntityByClassname(nullptr, "func_snow"))
		return SendReceiveW(2);
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, UpdateClientData)

// resends any changed player HUD info to the client.
// Called every frame by PlayerPreThink
// Also called at start of demo recording and playback by
// ForceClientDllUpdate to ensure the demo gets messages
// reflecting all of the HUD state info.
void EXT_FUNC CBasePlayer::__API_HOOK(UpdateClientData)()
{
	if (m_fInitHUD)
	{
		m_fInitHUD = FALSE;
		gInitHUD = FALSE;
#ifdef REGAMEDLL_FIXES
		m_signals.Reset();
#else
		m_signals.Update();
#endif

		MESSAGE_BEGIN(MSG_ONE, gmsgResetHUD, nullptr, pev);
		MESSAGE_END();

		if (!m_fGameHUDInitialized)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgInitHUD, nullptr, pev);
			MESSAGE_END();

			CBaseEntity *pEntity = UTIL_FindEntityByClassname(nullptr, "env_fog");
			if (pEntity)
			{
				CClientFog *pFog = static_cast<CClientFog *>(pEntity);

				int r = clamp(int(pFog->pev->rendercolor[0]), 0, 255);
				int g = clamp(int(pFog->pev->rendercolor[1]), 0, 255);
				int b = clamp(int(pFog->pev->rendercolor[2]), 0, 255);

				union
				{
					float f;
					char b[4];

				} density;

				density.f = pFog->m_fDensity;

				MESSAGE_BEGIN(MSG_ONE, gmsgFog, nullptr, pev);
					WRITE_BYTE(r);
					WRITE_BYTE(g);
					WRITE_BYTE(b);
					WRITE_BYTE(density.b[0]);
					WRITE_BYTE(density.b[1]);
					WRITE_BYTE(density.b[2]);
					WRITE_BYTE(density.b[3]);
				MESSAGE_END();
			}

			g_pGameRules->InitHUD(this);
			m_fGameHUDInitialized = TRUE;

			if (g_pGameRules->IsMultiplayer())
			{
				FireTargets("game_playerjoin", this, this, USE_TOGGLE, 0);
			}

			m_iObserverLastMode = OBS_ROAMING;
			m_iObserverC4State = 0;
			m_bObserverHasDefuser = false;
			SetObserverAutoDirector(false);
		}

#ifndef REGAMEDLL_FIXES
		FireTargets("game_playerspawn", this, this, USE_TOGGLE, 0);
#endif
		MESSAGE_BEGIN(MSG_ONE, gmsgMoney, nullptr, pev);
			WRITE_LONG(m_iAccount);
			WRITE_BYTE(0);
		MESSAGE_END();

		if (m_bHasDefuser)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
				WRITE_BYTE(STATUSICON_SHOW);
				WRITE_STRING("defuser");
				WRITE_BYTE(0);
				WRITE_BYTE(160);
				WRITE_BYTE(0);
			MESSAGE_END();
		}

		SetBombIcon(FALSE);
		SyncRoundTimer();
		SendHostagePos();
		SendWeatherInfo();

		if (g_pGameRules->IsMultiplayer())
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgTeamScore, nullptr, pev);
				WRITE_STRING(GetTeam(CT));
				WRITE_SHORT(CSGameRules()->m_iNumCTWins);
			MESSAGE_END();

			MESSAGE_BEGIN(MSG_ONE, gmsgTeamScore, nullptr, pev);
				WRITE_STRING(GetTeam(TERRORIST));
				WRITE_SHORT(CSGameRules()->m_iNumTerroristWins);
			MESSAGE_END();
		}

#ifdef REGAMEDLL_FIXES
		// send "flashlight" update message
		if (FlashlightIsOn())
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgFlashlight, nullptr, pev);
				WRITE_BYTE(1);
				WRITE_BYTE(m_iFlashBattery);
			MESSAGE_END();
		}
#endif
	}

	if (m_iHideHUD != m_iClientHideHUD)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgHideWeapon, nullptr, pev);
			WRITE_BYTE(m_iHideHUD);
		MESSAGE_END();

#ifdef REGAMEDLL_FIXES
		if (m_iHideHUD && !(m_iHideHUD & HIDEHUD_OBSERVER_CROSSHAIR))
		{
			if (m_iClientHideHUD < 0)
				m_iClientHideHUD = 0;

			int hudChanged = m_iClientHideHUD ^ m_iHideHUD;
			if (hudChanged & (HIDEHUD_FLASHLIGHT | HIDEHUD_HEALTH | HIDEHUD_TIMER | HIDEHUD_MONEY | HIDEHUD_CROSSHAIR))
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgCrosshair, nullptr, pev);
					WRITE_BYTE(0);
				MESSAGE_END();
			}
		}
#endif

		m_iClientHideHUD = m_iHideHUD;
	}

	if (m_iFOV != m_iClientFOV)
	{
		// cache FOV change at end of function, so weapon updates can see that FOV has changed
		pev->fov = m_iFOV;

		MESSAGE_BEGIN(MSG_ONE, gmsgSetFOV, nullptr, pev);
			WRITE_BYTE(m_iFOV);
		MESSAGE_END();

		MESSAGE_BEGIN(MSG_SPEC, gmsgHLTV);
			WRITE_BYTE(ENTINDEX(edict()));
			WRITE_BYTE(m_iFOV);
		MESSAGE_END();
	}

	// HACKHACK -- send the message to display the game title
	if (gDisplayTitle)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgShowGameTitle, nullptr, pev);
			WRITE_BYTE(0);
		MESSAGE_END();

		gDisplayTitle = FALSE;
	}

	if (int(pev->health) != m_iClientHealth)
	{
		int iHealth = clamp(int(pev->health), 0, 255);

		if (pev->health > 0.0f && pev->health <= 1.0f)
			iHealth = 1;

		// send "health" update message
		MESSAGE_BEGIN(MSG_ONE, gmsgHealth, nullptr, pev);
			WRITE_BYTE(iHealth);
		MESSAGE_END();

		m_iClientHealth = int(pev->health);
	}

	if (int(pev->armorvalue) != m_iClientBattery)
	{
		m_iClientBattery = int(pev->armorvalue);

		// send "armor" update message
		MESSAGE_BEGIN(MSG_ONE, gmsgBattery, nullptr, pev);
			WRITE_SHORT(int(pev->armorvalue));
		MESSAGE_END();
	}

	if (pev->dmg_take != 0.0f || pev->dmg_save != 0.0f || m_bitsHUDDamage != m_bitsDamageType)
	{
		// Comes from inside me if not set
		Vector damageOrigin = pev->origin;

		// send "damage" message
		// causes screen to flash, and pain compass to show direction of damage
		edict_t *other = pev->dmg_inflictor;

		if (other)
		{
			CBaseEntity *pEntity = CBaseEntity::Instance(other);

			if (pEntity)
			{
				if (pEntity == this && (m_bitsDamageType & DMG_FALL))
					damageOrigin = Vector(0, 0, 0); // do not show direction of damage caused by fall
				else
					damageOrigin = pEntity->Center();
			}
		}

		// only send down damage type that have hud art
		int visibleDamageBits = m_bitsDamageType & DMG_SHOWNHUD;

		MESSAGE_BEGIN(MSG_ONE, gmsgDamage, nullptr, pev);
			WRITE_BYTE(int(pev->dmg_save));
			WRITE_BYTE(int(pev->dmg_take));
			WRITE_LONG(visibleDamageBits);
			WRITE_COORD(damageOrigin.x);
			WRITE_COORD(damageOrigin.y);
			WRITE_COORD(damageOrigin.z);
		MESSAGE_END();

		pev->dmg_take = 0;
		pev->dmg_save = 0;
		m_bitsHUDDamage = m_bitsDamageType;

		// Clear off non-time-based damage indicators
		m_bitsDamageType &= DMG_TIMEBASED;
	}

	// Update Flashlight
	if (m_flFlashLightTime && m_flFlashLightTime <= gpGlobals->time)
	{
		if (FlashlightIsOn())
		{
			if (m_iFlashBattery)
			{
				m_flFlashLightTime = gpGlobals->time + FLASH_DRAIN_TIME;

				if (--m_iFlashBattery <= 0)
				{
					FlashlightTurnOff();
				}
			}
		}
		else
		{
			if (m_iFlashBattery < 100)
			{
				m_flFlashLightTime = gpGlobals->time + FLASH_CHARGE_TIME;
				m_iFlashBattery++;
			}
			else
				m_flFlashLightTime = 0;
		}

		MESSAGE_BEGIN(MSG_ONE, gmsgFlashBattery, nullptr, pev);
			WRITE_BYTE(m_iFlashBattery);
		MESSAGE_END();
	}

	if (m_iTrain & TRAIN_NEW)
	{
		// send "train hud" update message
		MESSAGE_BEGIN(MSG_ONE, gmsgTrain, nullptr, pev);
			WRITE_BYTE(m_iTrain & 0xF);
		MESSAGE_END();

		m_iTrain &= ~TRAIN_NEW;
	}

	SendAmmoUpdate();

	// Update all the items
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		if (m_rgpPlayerItems[i])
		{
			// each item updates it's successors
			m_rgpPlayerItems[i]->UpdateClientData(this);
		}
	}

	// Cache and client weapon change
	m_pClientActiveItem = m_pActiveItem;
	m_iClientFOV = m_iFOV;

	// Update Status Bar
	if (m_flNextSBarUpdateTime < gpGlobals->time)
	{
		UpdateStatusBar();
		m_flNextSBarUpdateTime = gpGlobals->time + 0.2f;
	}

	if (!(m_flDisplayHistory & DHF_AMMO_EXHAUSTED))
	{
		if (m_pActiveItem && m_pActiveItem->IsWeapon())
		{
			CBasePlayerWeapon *weapon = static_cast<CBasePlayerWeapon *>(m_pActiveItem);

			if (!(weapon->iFlags() & ITEM_FLAG_EXHAUSTIBLE))
			{
				if (AmmoInventory(weapon->m_iPrimaryAmmoType) < 1 && weapon->m_iClip == 0)
				{
					m_flDisplayHistory |= DHF_AMMO_EXHAUSTED;
					HintMessage("#Hint_out_of_ammo");
				}
			}
		}
	}

	if (gpGlobals->time > m_tmHandleSignals)
	{
		m_tmHandleSignals = gpGlobals->time + 0.5f;
		HandleSignals();
	}

	if (pev->deadflag == DEAD_NO && gpGlobals->time > m_tmNextRadarUpdate)
	{
		Vector vecOrigin = pev->origin;
		m_tmNextRadarUpdate = gpGlobals->time + 1.0f;

#ifdef REGAMEDLL_ADD
		if (CSGameRules()->IsFreeForAll())
			vecOrigin = g_vecZero;
#endif

		const float flToleranceDist = 64.0f;
		if ((pev->origin - m_vLastOrigin).Length() >= flToleranceDist)
		{
			for (int i = 1; i <= gpGlobals->maxClients; i++)
			{
				CBaseEntity *pEntity = UTIL_PlayerByIndex(i);

				if (!UTIL_IsValidPlayer(pEntity))
					continue;

				if (i == entindex())
					continue;

				CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

				if (pPlayer->pev->deadflag != DEAD_NO)
					continue;

				if (pPlayer->m_iTeam == m_iTeam)
				{
					MESSAGE_BEGIN(MSG_ONE, gmsgRadar, nullptr, pPlayer->pev);
						WRITE_BYTE(entindex());
						WRITE_COORD(vecOrigin.x);
						WRITE_COORD(vecOrigin.y);
						WRITE_COORD(vecOrigin.z);
					MESSAGE_END();
				}
			}
		}

		m_vLastOrigin = pev->origin;
	}

#ifdef BUILD_LATEST

	if (
#ifdef REGAMEDLL_FIXES
		(scoreboard_showmoney.value != -1.0f || scoreboard_showhealth.value != -1.0f) &&
#endif
		(m_iTeam == CT || m_iTeam == TERRORIST) &&
		(m_iLastAccount != m_iAccount || m_iLastClientHealth != m_iClientHealth || m_tmNextAccountHealthUpdate < gpGlobals->time))
	{
		m_tmNextAccountHealthUpdate = gpGlobals->time + 5.0f;

		for (int playerIndex = 1; playerIndex <= gpGlobals->maxClients; playerIndex++)
		{
			CBaseEntity *pEntity = UTIL_PlayerByIndex(playerIndex);

			if (!UTIL_IsValidPlayer(pEntity))
				continue;

			CBasePlayer *pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

#ifdef REGAMEDLL_FIXES
			if (scoreboard_showhealth.value != -1.0f)
#endif
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgHealthInfo, nullptr, pPlayer->edict());
					WRITE_BYTE(entindex());
					WRITE_LONG(ShouldToShowHealthInfo(pPlayer) ? m_iClientHealth : -1 /* means that 'HP' field will be hidden */);
				MESSAGE_END();
			}

#ifdef REGAMEDLL_FIXES
			if (scoreboard_showmoney.value != -1.0f)
#endif
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgAccount, nullptr, pPlayer->edict());
					WRITE_BYTE(entindex());
					WRITE_LONG(ShouldToShowAccount(pPlayer) ? m_iAccount : -1 /* means that this 'Money' will be hidden */);
				MESSAGE_END();
			}
		}

		m_iLastAccount = m_iAccount;
		m_iLastClientHealth = m_iClientHealth;
	}
#endif // #ifdef BUILD_LATEST
}

bool CBasePlayer::ShouldToShowAccount(CBasePlayer *pReceiver) const
{
#ifdef BUILD_LATEST
	int iShowAccount = static_cast<int>(scoreboard_showmoney.value);

#ifdef REGAMEDLL_FIXES
	if (iShowAccount == 0)
		return false; // don't send any update for this field to any clients
#endif

	// show only Terrorist or CT 'Money' field to all clients
	if (m_iTeam == iShowAccount)
		return true;

	switch (iShowAccount)
	{
	// show field to teammates
	case 3: return !CSGameRules()->IsFreeForAll() && pReceiver->m_iTeam == m_iTeam;

	// show field to all clients
	case 4: return true;

	// show field to teammates and spectators
	case 5: return ((!CSGameRules()->IsFreeForAll() && pReceiver->m_iTeam == m_iTeam) || pReceiver->m_iTeam == SPECTATOR);
	default:
		break;
	}
#endif // #ifdef BUILD_LATEST

	return false;
}

bool CBasePlayer::ShouldToShowHealthInfo(CBasePlayer *pReceiver) const
{
#ifdef BUILD_LATEST
	int iShowHealth = static_cast<int>(scoreboard_showhealth.value);

#ifdef REGAMEDLL_FIXES
	if (iShowHealth == 0)
		return false; // don't send any update for this field to any clients
#endif

	// show only Terrorist or CT 'HP' fields to all clients
	if (m_iTeam == iShowHealth)
		return true;

	switch (iShowHealth)
	{
	// show field to teammates
	case 3: return !CSGameRules()->IsFreeForAll() && pReceiver->m_iTeam == m_iTeam;

	// show field to all clients
	case 4: return true;

	// show field to teammates and spectators
	case 5: return ((!CSGameRules()->IsFreeForAll() && pReceiver->m_iTeam == m_iTeam) || pReceiver->m_iTeam == SPECTATOR);
	default:
		break;
	}
#endif // #ifdef BUILD_LATEST

	return false;
}

BOOL CBasePlayer::FBecomeProne()
{
	m_afPhysicsFlags |= PFLAG_ONBARNACLE;
	return TRUE;
}

NOXREF void CBasePlayer::BarnacleVictimBitten(entvars_t *pevBarnacle)
{
	TakeDamage(pevBarnacle, pevBarnacle, pev->armorvalue + pev->health, DMG_SLASH | DMG_ALWAYSGIB);
}

NOXREF void CBasePlayer::BarnacleVictimReleased()
{
	m_afPhysicsFlags &= ~PFLAG_ONBARNACLE;
}

// return player light level plus virtual muzzle flash
int CBasePlayer::Illumination()
{
	int iIllum = CBaseEntity::Illumination();

	iIllum += m_iWeaponFlash;

	if (iIllum > 255)
		return 255;

	return iIllum;
}

void CBasePlayer::EnableControl(BOOL fControl)
{
	if (!fControl)
		pev->flags |= FL_FROZEN;
	else
		pev->flags &= ~FL_FROZEN;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, ResetMaxSpeed)

void EXT_FUNC CBasePlayer::__API_HOOK(ResetMaxSpeed)()
{
	float speed;

	if (GetObserverMode() != OBS_NONE)
	{
		// Player gets speed bonus in observer mode
		speed = 900;
	}
	else if (g_pGameRules->IsMultiplayer() && g_pGameRules->IsFreezePeriod())
	{
		// Player should not move during the freeze period
		speed = 1;
	}
	// VIP is slow due to the armour he's wearing
	else if (m_bIsVIP)
	{
		speed = 227;
	}
	else if (m_pActiveItem)
	{
		// Get player speed from selected weapon
		speed = m_pActiveItem->GetMaxSpeed();
	}
	else
	{
		// No active item, set the player's speed to default
		speed = 240;
	}

	pev->maxspeed = speed;
}

LINK_HOOK_CLASS_CHAIN(bool, CBasePlayer, HintMessageEx, (const char *pMessage, float duration, bool bDisplayIfPlayerDead, bool bOverride), pMessage, duration, bDisplayIfPlayerDead, bOverride)

bool EXT_FUNC CBasePlayer::__API_HOOK(HintMessageEx)(const char *pMessage, float duration, bool bDisplayIfPlayerDead, bool bOverride)
{
	if (!bDisplayIfPlayerDead && !IsAlive())
		return false;

	if (bOverride || m_bShowHints)
		return m_hintMessageQueue.AddMessage(pMessage, duration, true, nullptr);

	return true;
}

bool EXT_FUNC CBasePlayer::HintMessage(const char *pMessage, BOOL bDisplayIfPlayerDead, BOOL bOverride)
{
	return HintMessageEx(pMessage, 6.0f, bDisplayIfPlayerDead == TRUE, bOverride == TRUE);
}

Vector CBasePlayer::GetAutoaimVector(float flDelta)
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

	if (g_psv_aim && g_psv_aim->value > 0.0f)
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

Vector CBasePlayer::AutoaimDeflection(Vector &vecSrc, float flDist, float flDelta)
{
	m_fOnTarget = FALSE;
	return g_vecZero;
}

void CBasePlayer::ResetAutoaim()
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
void CBasePlayer::SetCustomDecalFrames(int nFrames)
{
	if (nFrames > 0 && nFrames < 8)
		m_nCustomSprayFrames = nFrames;
	else
		m_nCustomSprayFrames = -1;
}

// Returns the # of custom frames this player's custom clan logo contains.
int CBasePlayer::GetCustomDecalFrames()
{
	return m_nCustomSprayFrames;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, Blind, (float duration, float holdTime, float fadeTime, int alpha), duration, holdTime, fadeTime, alpha)

void EXT_FUNC CBasePlayer::__API_HOOK(Blind)(float duration, float holdTime, float fadeTime, int alpha)
{
	m_blindUntilTime = gpGlobals->time + duration;
	m_blindStartTime = gpGlobals->time;

	m_blindHoldTime = holdTime;
	m_blindFadeTime = fadeTime;
	m_blindAlpha = alpha;
}

void CBasePlayer::InitStatusBar()
{
	m_flStatusBarDisappearDelay = 0.0f;
	m_SbarString0[0] = '\0';
}

void CBasePlayer::UpdateStatusBar()
{
	int newSBarState[SBAR_END];
	char sbuf0[MAX_SBAR_STRING];

	Q_memset(newSBarState, 0, sizeof(newSBarState));
	Q_strcpy(sbuf0, m_SbarString0);

	// Find an ID Target
	TraceResult tr;
	UTIL_MakeVectors(pev->v_angle + pev->punchangle);

	Vector vecSrc = EyePosition();
	Vector vecEnd = vecSrc + (gpGlobals->v_forward * ((pev->flags & FL_SPECTATOR) != 0 ? MAX_SPEC_ID_RANGE : MAX_ID_RANGE));

	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, edict(), &tr);

	if (tr.flFraction != 1.0f)
	{
		if (!FNullEnt(tr.pHit))
		{
			CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
			bool isVisiblePlayer = ((TheBots == nullptr || !TheBots->IsLineBlockedBySmoke(&pev->origin, &pEntity->pev->origin)) && pEntity->Classify() == CLASS_PLAYER);

			if (gpGlobals->time >= m_blindUntilTime && isVisiblePlayer)
			{
				CBasePlayer *pTarget = (CBasePlayer *)pEntity;

				bool sameTeam = g_pGameRules->PlayerRelationship(this, pTarget) == GR_TEAMMATE;

				newSBarState[SBAR_ID_TARGETNAME] = ENTINDEX(pTarget->edict());
				newSBarState[SBAR_ID_TARGETTYPE] = sameTeam ? SBAR_TARGETTYPE_TEAMMATE : SBAR_TARGETTYPE_ENEMY;

				if (sameTeam || GetObserverMode() != OBS_NONE)
				{
					if (playerid.value != PLAYERID_MODE_OFF || GetObserverMode() != OBS_NONE)
						Q_strcpy(sbuf0, "1 %c1: %p2\n2  %h: %i3%%");
					else
						Q_strcpy(sbuf0, " ");

					newSBarState[SBAR_ID_TARGETHEALTH] = int((pEntity->pev->health / pEntity->pev->max_health) * 100);

					if (!(m_flDisplayHistory & DHF_FRIEND_SEEN) && !(pev->flags & FL_SPECTATOR))
					{
						m_flDisplayHistory |= DHF_FRIEND_SEEN;
						HintMessage("#Hint_spotted_a_friend");
					}
				}
				else if (GetObserverMode() == OBS_NONE)
				{
					if (playerid.value != PLAYERID_MODE_TEAMONLY && playerid.value != PLAYERID_MODE_OFF)
						Q_strcpy(sbuf0, "1 %c1: %p2");
					else
						Q_strcpy(sbuf0, " ");

					if (!(m_flDisplayHistory & DHF_ENEMY_SEEN))
					{
						m_flDisplayHistory |= DHF_ENEMY_SEEN;
						HintMessage("#Hint_spotted_an_enemy");
					}
				}

				m_flStatusBarDisappearDelay = gpGlobals->time + 2.0f;
			}
			else if (pEntity->Classify() == CLASS_HUMAN_PASSIVE)
			{
				if (playerid.value != PLAYERID_MODE_OFF || GetObserverMode() != OBS_NONE)
					Q_strcpy(sbuf0, "1 %c1  %h: %i3%%");
				else
					Q_strcpy(sbuf0, " ");

				newSBarState[SBAR_ID_TARGETTYPE] = SBAR_TARGETTYPE_HOSTAGE;
				newSBarState[SBAR_ID_TARGETHEALTH] = int((pEntity->pev->health / pEntity->pev->max_health) * 100);

				if (!(m_flDisplayHistory & DHF_HOSTAGE_SEEN_FAR) && tr.flFraction > 0.1f)
				{
					m_flDisplayHistory |= DHF_HOSTAGE_SEEN_FAR;

					if (m_iTeam == TERRORIST)
						HintMessage("#Hint_prevent_hostage_rescue", TRUE);

					else if (m_iTeam == CT)
						HintMessage("#Hint_rescue_the_hostages", TRUE);
				}
				else if (m_iTeam == CT && !(m_flDisplayHistory & DHF_HOSTAGE_SEEN_NEAR) && tr.flFraction <= 0.1f)
				{
					m_flDisplayHistory |= (DHF_HOSTAGE_SEEN_NEAR | DHF_HOSTAGE_SEEN_FAR);
					HintMessage("#Hint_press_use_so_hostage_will_follow");
				}

				m_flStatusBarDisappearDelay = gpGlobals->time + 2.0f;
			}
		}
	}
	else if (m_flStatusBarDisappearDelay > gpGlobals->time)
	{
		// hold the values for a short amount of time after viewing the object
		newSBarState[SBAR_ID_TARGETTYPE] = m_izSBarState[SBAR_ID_TARGETTYPE];
		newSBarState[SBAR_ID_TARGETNAME] = m_izSBarState[SBAR_ID_TARGETNAME];
		newSBarState[SBAR_ID_TARGETHEALTH] = m_izSBarState[SBAR_ID_TARGETHEALTH];
	}

	bool bForceResend = false;

	if (Q_strcmp(sbuf0, m_SbarString0) != 0)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgStatusText, nullptr, pev);
			WRITE_BYTE(0);
			WRITE_STRING(sbuf0);
		MESSAGE_END();

		Q_strcpy(m_SbarString0, sbuf0);

		// make sure everything's resent
		bForceResend = true;
	}

	// Check values and send if they don't match
	for (int i = 1; i < SBAR_END; i++)
	{
		if (newSBarState[i] != m_izSBarState[i] || bForceResend)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgStatusValue, nullptr, pev);
				WRITE_BYTE(i);
				WRITE_SHORT(newSBarState[i]);
			MESSAGE_END();

			m_izSBarState[i] = newSBarState[i];
		}
	}
}

LINK_HOOK_CLASS_CHAIN(CBaseEntity *, CBasePlayer, DropPlayerItem, (const char *pszItemName), pszItemName)

// DropPlayerItem - drop the named item, or if no name, the active item.
CBaseEntity *EXT_FUNC CBasePlayer::__API_HOOK(DropPlayerItem)(const char *pszItemName)
{
	if (!Q_strlen(pszItemName))
	{
		// if this string has no length, the client didn't type a name!
		// assume player wants to drop the active item.
		// make the string null to make future operations in this function easier
		pszItemName = nullptr;
	}

	if (m_bIsVIP)
	{
		ClientPrint(pev, HUD_PRINTCENTER, "#Weapon_Cannot_Be_Dropped");
		return nullptr;
	}
	else if (!pszItemName && HasShield())
	{
		DropShield();
		return nullptr;
	}

#ifndef REGAMEDLL_FIXES
	CBasePlayerItem *pWeapon = nullptr;
	for (int i = 0; i < MAX_ITEM_TYPES; i++)
	{
		pWeapon = m_rgpPlayerItems[i];
		while (pWeapon)
		{
			if (pszItemName)
			{
				if (FClassnameIs(pWeapon->pev, pszItemName))
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
			break;
	}
#else
	auto pWeapon = pszItemName ? GetItemByName(pszItemName) : m_pActiveItem;
#endif
	if (pWeapon)
	{
		if (!pWeapon->CanDrop())
		{
			ClientPrint(pev, HUD_PRINTCENTER, "#Weapon_Cannot_Be_Dropped");
			return nullptr;
		}

		// take item off hud
		pev->weapons &= ~(1 << pWeapon->m_iId);

#ifdef REGAMEDLL_FIXES
		// No more weapon
		if ((pev->weapons & ~(1 << WEAPON_SUIT)) == 0) {
			m_iHideHUD |= HIDEHUD_WEAPONS;
		}
#endif

		g_pGameRules->GetNextBestWeapon(this, pWeapon);
		UTIL_MakeVectors(pev->angles);

#ifndef REGAMEDLL_FIXES
		if (pWeapon->iItemSlot() == PRIMARY_WEAPON_SLOT)
			m_bHasPrimary = false; // I may have more than just 1 primary weapon :)
#endif

		if (FClassnameIs(pWeapon->pev, "weapon_c4"))
		{
			m_bHasC4 = false;
			pev->body = 0;
			SetBombIcon(FALSE);
			pWeapon->m_pPlayer->SetProgressBarTime(0);

			if (!CSGameRules()->m_flRestartRoundTime)
			{
				UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Dropped_The_Bomb\"\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()));
				g_pGameRules->m_bBombDropped = TRUE;

				CBaseEntity *pEntity = nullptr;
				while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
				{
					if (FNullEnt(pEntity->edict()))
						break;

					if (!pEntity->IsPlayer() || pEntity->IsDormant())
						continue;

					CBasePlayer *pOther = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

					if (pOther->pev->deadflag == DEAD_NO && pOther->m_iTeam == TERRORIST)
					{
						ClientPrint(pOther->pev, HUD_PRINTCENTER, "#Game_bomb_drop", STRING(pev->netname));

						MESSAGE_BEGIN(MSG_ONE, gmsgBombDrop, nullptr, pOther->pev);
							WRITE_COORD(pev->origin.x);
							WRITE_COORD(pev->origin.y);
							WRITE_COORD(pev->origin.z);
							WRITE_BYTE(BOMB_FLAG_DROPPED);
						MESSAGE_END();
					}
				}
			}
		}

		const char *modelname = GetCSModelName(pWeapon->m_iId);

		Vector vecOrigin   = pev->origin + gpGlobals->v_forward * 10;
		Vector vecAngles   = pev->angles;
		Vector vecVelocity = gpGlobals->v_forward * 300 + gpGlobals->v_forward * 100;

		bool bPackAmmo = false;

#ifdef REGAMEDLL_ADD
		if (ammodrop.value >= 2.0f)
			bPackAmmo = true;
#endif

		CWeaponBox *pWeaponBox = CreateWeaponBox(pWeapon, this,
			modelname,
			vecOrigin,
			vecAngles,
			vecVelocity,
			CGameRules::GetItemKillDelay(),
			bPackAmmo
			);

		if (!pWeaponBox)
		{
			return nullptr;
		}

#ifdef REGAMEDLL_FIXES
		if (!m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]) {
			m_bHasPrimary = false; // ensure value assignation on successful weapon removal
		}
#endif

		if (FClassnameIs(pWeapon->pev, "weapon_c4"))
		{
			pWeaponBox->m_bIsBomb = true;
			pWeaponBox->SetThink(&CWeaponBox::BombThink);
			pWeaponBox->pev->nextthink = gpGlobals->time + 1.0f;

			if (TheCSBots())
			{
				// tell the bots about the dropped bomb
				TheCSBots()->SetLooseBomb(pWeaponBox);
				TheCSBots()->OnEvent(EVENT_BOMB_DROPPED);
			}
		}

		return pWeaponBox;
	}

	return nullptr;
}

// Does the player already have this item?
bool CBasePlayer::HasPlayerItem(CBasePlayerItem *pCheckItem)
{
	auto item = m_rgpPlayerItems[pCheckItem->iItemSlot()];
	while (item)
	{
		if (FClassnameIs(item->pev, STRING(pCheckItem->pev->classname)))
			return true;

		item = item->m_pNext;
	}

	return false;
}

// Does the player already have this item?
bool CBasePlayer::HasNamedPlayerItem(const char *pszItemName)
{
	for (auto item : m_rgpPlayerItems)
	{
		while (item)
		{
			if (FClassnameIs(item->pev, pszItemName))
				return true;

			item = item->m_pNext;
		}
	}

	return false;
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, SwitchTeam)

void CBasePlayer::__API_HOOK(SwitchTeam)()
{
	int oldTeam;
	char *szOldTeam;
	char *szNewTeam;
	const char *szName;
	char *szNewModel = nullptr;

	oldTeam = m_iTeam;

	if (m_iTeam == CT)
	{
		m_iTeam = TERRORIST;

		switch (m_iModelName)
		{
		case MODEL_URBAN:
			m_iModelName = MODEL_LEET;
			szNewModel = "leet";
			break;
		case MODEL_GIGN:
			m_iModelName = MODEL_GUERILLA;
			szNewModel = "guerilla";
			break;
		case MODEL_SAS:
			m_iModelName = MODEL_ARCTIC;
			szNewModel = "arctic";
			break;
		case MODEL_SPETSNAZ:
			if (AreRunningCZero())
			{
				m_iModelName = MODEL_MILITIA;
				szNewModel = "militia";
				break;
			}
		default:
			if (m_iModelName == MODEL_GSG9 || !IsBot() || !TheBotProfiles->GetCustomSkinModelname(m_iModelName))
			{
				m_iModelName = MODEL_TERROR;
				szNewModel = "terror";
			}
			break;
		}
	}
	else if (m_iTeam == TERRORIST)
	{
		m_iTeam = CT;

		switch (m_iModelName)
		{
		case MODEL_TERROR:
			m_iModelName = MODEL_GSG9;
			szNewModel = "gsg9";
			break;

		case MODEL_ARCTIC:
			m_iModelName = MODEL_SAS;
			szNewModel = "sas";
			break;

		case MODEL_GUERILLA:
			m_iModelName = MODEL_GIGN;
			szNewModel = "gign";
			break;

		case MODEL_MILITIA:
			if (AreRunningCZero())
			{
				m_iModelName = MODEL_SPETSNAZ;
				szNewModel = "spetsnaz";
				break;
			}
		default:
			if (m_iModelName == MODEL_LEET || !IsBot() || !TheBotProfiles->GetCustomSkinModelname(m_iModelName))
			{
				m_iModelName = MODEL_URBAN;
				szNewModel = "urban";
			}
			break;
		}
	}

	SetClientUserInfoModel(GET_INFO_BUFFER(edict()), szNewModel);

	MESSAGE_BEGIN(MSG_ALL, gmsgTeamInfo);
		WRITE_BYTE(entindex());
		WRITE_STRING(GetTeamName(m_iTeam));
	MESSAGE_END();

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_CHANGED_TEAM, this);
	}

	UpdateLocation(true);

	if (m_iTeam)
	{
		SetScoreboardAttributes();
	}

	if (pev->netname)
	{
		szName = STRING(pev->netname);

		if (!szName[0])
			szName = "<unconnected>";
	}
	else
		szName = "<unconnected>";

	UTIL_ClientPrintAll(HUD_PRINTNOTIFY, (m_iTeam == TERRORIST) ? "#Game_join_terrorist_auto" : "#Game_join_ct_auto", szName);

	if (m_bHasDefuser)
	{
		RemoveDefuser();

#ifndef REGAMEDLL_FIXES
		// NOTE: unreachable code - Vaqtincha
		for (int i = 0; i < MAX_ITEM_TYPES; i++)
		{
			m_pActiveItem = m_rgpPlayerItems[i];

			if (m_pActiveItem && FClassnameIs(m_pActiveItem->pev, "item_thighpack"))
			{
				m_pActiveItem->Drop();
				m_rgpPlayerItems[i] = nullptr;
			}
		}
#endif

	}

	szOldTeam = GetTeam(oldTeam);
	szNewTeam = GetTeam(m_iTeam);

	UTIL_LogPrintf("\"%s<%i><%s><%s>\" joined team \"%s\" (auto)\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()), szOldTeam, szNewTeam);

	CCSBot *pBot = static_cast<CCSBot *>(this);

	if (pBot->IsBot())
	{
		const BotProfile *pProfile = pBot->GetProfile();

		if (pProfile)
		{
			bool bKick = false;

			if (m_iTeam == CT && !pProfile->IsValidForTeam(BOT_TEAM_CT))
				bKick = true;

			else if (m_iTeam == TERRORIST && !pProfile->IsValidForTeam(BOT_TEAM_T))
				bKick = true;

			if (bKick)
			{
				SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", STRING(pev->netname)));
			}
		}
	}

#ifdef REGAMEDLL_FIXES
	// Initialize the player counts now that a player has switched teams
	int NumDeadCT, NumDeadTerrorist, NumAliveTerrorist, NumAliveCT;
	CSGameRules()->InitializePlayerCounts(NumAliveTerrorist, NumAliveCT, NumDeadTerrorist, NumDeadCT);
#endif
}

void CBasePlayer::UpdateShieldCrosshair(bool draw)
{
	if (draw)
		m_iHideHUD &= ~HIDEHUD_CROSSHAIR;
	else
		m_iHideHUD |= HIDEHUD_CROSSHAIR;
}

BOOL CBasePlayer::SwitchWeapon(CBasePlayerItem *pWeapon)
{
	if (!pWeapon->CanDeploy())
	{
		return FALSE;
	}

	ResetAutoaim();

	if (m_pActiveItem)
	{
		m_pActiveItem->Holster();
	}

	CBasePlayerItem *pTemp = m_pActiveItem;
	m_pActiveItem = pWeapon;
	m_pLastItem = pTemp;

	pWeapon->Deploy();

	if (pWeapon->m_pPlayer)
	{
		pWeapon->m_pPlayer->ResetMaxSpeed();
	}

	if (HasShield())
	{
		UpdateShieldCrosshair(true);
	}

	return TRUE;
}

void CBasePlayer::TabulateAmmo()
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

LINK_ENTITY_TO_CLASS(monster_hevsuit_dead, CDeadHEV, CCSDeadHEV)

void CDeadHEV::Spawn()
{
	PRECACHE_MODEL("models/player.mdl");
	SET_MODEL(ENT(pev), "models/player.mdl");

	pev->effects = 0;
	pev->yaw_speed = 8.0f;

	pev->sequence = 0;
	pev->body = 1;

	m_bloodColor = BLOOD_COLOR_RED;
	pev->sequence = LookupSequence(m_szPoses[m_iPose]);

	if (pev->sequence == -1)
	{
		ALERT(at_console, "Dead hevsuit with bad pose\n");
		pev->sequence = 0;
		pev->effects = EF_BRIGHTFIELD;
	}

	// Corpses have less health
	pev->health = 8;
	MonsterInitDead();
}

void CDeadHEV::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "pose"))
	{
		m_iPose = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CBaseMonster::KeyValue(pkvd);
	}
}

LINK_ENTITY_TO_CLASS(player_weaponstrip, CStripWeapons, CCSStripWeapons)

void CStripWeapons::KeyValue(KeyValueData *pkvd)
{
#ifdef REGAMEDLL_ADD
	if (FStrEq(pkvd->szKeyName, "primary") && Q_atoi(pkvd->szValue) > 0)
	{
		m_bitsIgnoreSlots |= (1 << PRIMARY_WEAPON_SLOT);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "secondary") && Q_atoi(pkvd->szValue) > 0)
	{
		m_bitsIgnoreSlots |= (1 << PISTOL_SLOT);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "knife") && Q_atoi(pkvd->szValue) > 0)
	{
		m_bitsIgnoreSlots |= (1 << KNIFE_SLOT);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "grenade") && Q_atoi(pkvd->szValue) > 0)
	{
		m_bitsIgnoreSlots |= (1 << GRENADE_SLOT);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "bomb") && Q_atoi(pkvd->szValue) > 0)
	{
		m_bitsIgnoreSlots |= (1 << C4_SLOT);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "items") && Q_atoi(pkvd->szValue) > 0)
	{
		m_bitsIgnoreSlots |= (1 << ALL_OTHER_ITEMS);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "special"))
	{
		m_iszSpecialItem = ALLOC_STRING(pkvd->szValue);
	}
	else
#endif
	{
		CPointEntity::KeyValue(pkvd);
	}
}

void CStripWeapons::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	CBasePlayer *pPlayer = nullptr;
	if (pActivator && pActivator->IsPlayer())
	{
		pPlayer = (CBasePlayer *)pActivator;
	}
	else if (!g_pGameRules->IsDeathmatch())
	{
		pPlayer = (CBasePlayer *)Instance(INDEXENT(1));
	}

	if (pPlayer)
	{
#ifdef REGAMEDLL_ADD
		if (m_bitsIgnoreSlots != 0 || m_iszSpecialItem)
		{
			if (m_iszSpecialItem)
			{
				const char *weaponName = STRING(m_iszSpecialItem);
				WeaponSlotInfo *slotInfo = GetWeaponSlot(weaponName);

				if (slotInfo != nullptr && slotInfo->slot == GRENADE_SLOT)
					pPlayer->CSPlayer()->RemovePlayerItemEx(weaponName, true);
				else
					pPlayer->CSPlayer()->RemovePlayerItem(weaponName);
			}

			for (int slot = PRIMARY_WEAPON_SLOT; slot <= ALL_OTHER_ITEMS; slot++)
			{
				if (m_bitsIgnoreSlots & (1 << slot))
					continue;

				if (slot == ALL_OTHER_ITEMS)
				{
					pPlayer->CSPlayer()->RemovePlayerItem("item_longjump");
					pPlayer->CSPlayer()->RemovePlayerItem("item_assaultsuit");
					pPlayer->CSPlayer()->RemovePlayerItem("item_kevlar");
					pPlayer->CSPlayer()->RemovePlayerItem("item_thighpack");
					pPlayer->CSPlayer()->RemovePlayerItem("weapon_shield");
				}
				else
				{
					pPlayer->ForEachItem(slot, [pPlayer](CBasePlayerItem *pItem)
					{
						if (pItem->iItemSlot() == GRENADE_SLOT)
							pPlayer->CSPlayer()->RemovePlayerItemEx(STRING(pItem->pev->classname), true);
						else
							pPlayer->CSPlayer()->RemovePlayerItem(STRING(pItem->pev->classname));

						return false;
					});
				}
			}
		}
		else
#endif
		{
			pPlayer->RemoveAllItems(FALSE);
		}
	}
}

void CBasePlayer::StudioEstimateGait()
{
	real_t dt;
	Vector est_velocity;

	dt = gpGlobals->frametime;

	if (dt < 0)
		dt = 0;

	else if (dt > 1.0)
		dt = 1;

	if (dt == 0)
	{
		m_flGaitMovement = 0;
		return;
	}

	est_velocity = pev->origin - m_prevgaitorigin;
	m_prevgaitorigin = pev->origin;

	m_flGaitMovement = est_velocity.Length();

	if (dt <= 0 || m_flGaitMovement / dt < 5)
	{
		m_flGaitMovement = 0;

		est_velocity.x = 0;
		est_velocity.y = 0;
	}

	if (!est_velocity.x && !est_velocity.y)
	{
		real_t flYawDiff = pev->angles.y - m_flGaityaw;
		real_t flYaw = Q_fmod(flYawDiff, 360);

		flYawDiff = flYawDiff - int64(flYawDiff / 360) * 360;

		if (flYawDiff > 180)
			flYawDiff -= 360;

		if (flYawDiff < -180)
			flYawDiff += 360;

		if (flYaw < -180)
			flYaw += 360;

		else if (flYaw > 180)
			flYaw -= 360;

		if (flYaw > -5 && flYaw < 5)
			m_flYawModifier = 0.05f;

		if (flYaw < -90 || flYaw > 90)
			m_flYawModifier = 3.5f;

		if (dt < 0.25f)
			flYawDiff *= dt * m_flYawModifier;
		else
			flYawDiff *= dt;

#ifdef REGAMEDLL_FIXES
		if (real_t(Q_abs(flYawDiff)) < 0.1f)
#else
		if (real_t(Q_abs(int64(flYawDiff))) < 0.1f)
#endif
			flYawDiff = 0;

		m_flGaityaw += flYawDiff;
		m_flGaityaw -= int64(m_flGaityaw / 360) * 360;
		m_flGaitMovement = 0;
	}
	else
	{
		m_flGaityaw = (Q_atan2(real_t(est_velocity.y), real_t(est_velocity.x)) * 180 / M_PI);

		if (m_flGaityaw > 180)
			m_flGaityaw = 180;

		if (m_flGaityaw < -180)
			m_flGaityaw = -180;
	}
}

void CBasePlayer::StudioPlayerBlend(int *pBlend, float *pPitch)
{
	// calc up/down pointing
	float range = float(int64(*pPitch * 3.0f));

	*pBlend = range;

	if (range <= -45.0f)
	{
		*pBlend = 255;
		*pPitch = 0;
	}
	else if (range >= 45.0f)
	{
		*pBlend = 0;
		*pPitch = 0;
	}
	else
	{
		*pBlend = int64((45.0f - range) * (255.0f / 90.0f));
		*pPitch = 0;
	}
}

void CBasePlayer::CalculatePitchBlend()
{
	int iBlend;
	float temp = pev->angles.x;

	StudioPlayerBlend(&iBlend, &temp);

	pev->blending[1] = iBlend;
	m_flPitch = iBlend;
}

void CBasePlayer::CalculateYawBlend()
{
	float dt;
	float maxyaw = 255.0f;

	real_t flYaw;		// view direction relative to movement
	real_t blend_yaw;

	dt = gpGlobals->frametime;

	if (dt < 0.0f)
		dt = 0;

	else if (dt > 1.0f)
		dt = 1;

	StudioEstimateGait();

	// calc side to side turning
	flYaw = Q_fmod(real_t(pev->angles.y - m_flGaityaw), 360);

	if (flYaw < -180)
		flYaw += 360;

	else if (flYaw > 180)
		flYaw -= 360;

	if (m_flGaitMovement != 0.0)
	{
		if (flYaw > 120)
		{
			m_flGaityaw -= 180;
			m_flGaitMovement = -m_flGaitMovement;
			flYaw -= 180;
		}
		else if (flYaw < -120)
		{
			m_flGaityaw += 180;
			m_flGaitMovement = -m_flGaitMovement;
			flYaw += 180;
		}
	}

	flYaw = (flYaw / 90) * 128 + 127;

	if (flYaw > 255)
		flYaw = 255;

	else if (flYaw < 0)
		flYaw = 0;

	blend_yaw = maxyaw - flYaw;

	pev->blending[0] = int64(blend_yaw);
	m_flYaw = blend_yaw;
}

void CBasePlayer::StudioProcessGait()
{
	mstudioseqdesc_t *pseqdesc;
	real_t dt = gpGlobals->frametime;

	if (dt < 0.0)
		dt = 0;

	else if (dt > 1.0)
		dt = 1;

	CalculateYawBlend();
	CalculatePitchBlend();

	studiohdr_t *pstudiohdr = (studiohdr_t *)GET_MODEL_PTR(edict());

	if (!pstudiohdr)
		return;

	pseqdesc = (mstudioseqdesc_t *)((byte *)pstudiohdr + pstudiohdr->seqindex) + pev->gaitsequence;

	// calc gait frame
	if (pseqdesc->linearmovement.x > 0.0f)
		m_flGaitframe += (m_flGaitMovement / pseqdesc->linearmovement.x) * pseqdesc->numframes;
	else
		m_flGaitframe += pev->framerate * pseqdesc->fps * dt;

	// do modulo
	m_flGaitframe -= int(m_flGaitframe / pseqdesc->numframes) * pseqdesc->numframes;

	if (m_flGaitframe < 0)
		m_flGaitframe += pseqdesc->numframes;
}

void CBasePlayer::ResetStamina()
{
	pev->fuser1 = 0;
	pev->fuser3 = 0;
	pev->fuser2 = 0;
}

real_t GetPlayerPitch(const edict_t *pEdict)
{
	if (!pEdict)
		return 0.0f;

	entvars_t *pev = VARS(const_cast<edict_t *>(pEdict));
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer || !pPlayer->IsPlayer())
		return 0.0f;

	return pPlayer->m_flPitch;
}

real_t GetPlayerYaw(const edict_t *pEdict)
{
	if (!pEdict)
		return 0.0f;

	entvars_t *pev = VARS(const_cast<edict_t *>(pEdict));
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer || !pPlayer->IsPlayer())
		return 0.0f;

	return pPlayer->m_flYaw;
}

int GetPlayerGaitsequence(const edict_t *pEdict)
{
	if (!pEdict)
		return 1;

	entvars_t *pev = VARS(const_cast<edict_t *>(pEdict));
	CBasePlayer *pPlayer = CBasePlayer::Instance(pev);

	if (!pPlayer || !pPlayer->IsPlayer())
		return 1;

	return pPlayer->m_iGaitsequence;
}

float CBasePlayer::GetDyingAnimationDuration() const
{
	float animDuration = -1.0f;

	if (CGameRules::GetDyingTime() < DEATH_ANIMATION_TIME) // a short time, timeDiff estimates to be small
	{
		float flSequenceDuration = GetSequenceDuration();
		if (flSequenceDuration > 0)
			animDuration = flSequenceDuration;
	}

	if (animDuration <= 0)
		animDuration = CGameRules::GetDyingTime(); // in case of failure

	return animDuration;
}

void CBasePlayer::SpawnClientSideCorpse()
{
#ifdef REGAMEDLL_FIXES
	// not allow to spawn, if the player was torn to gib
	if (pev->effects & EF_NODRAW)
		return;

	// deadflag == DEAD_RESPAWNABLE already checked before
#endif

#ifdef REGAMEDLL_ADD
	if (forcerespawn.value > 0.0f)
		return;
#endif

	char *infobuffer = GET_INFO_BUFFER(edict());
	char *pModel = GET_KEY_VALUE(infobuffer, "model");
	float timeDiff = pev->animtime - gpGlobals->time;

#ifdef REGAMEDLL_ADD
	if (CGameRules::GetDyingTime() < DEATH_ANIMATION_TIME) // a short time, timeDiff estimates to be small
	{
		float animDuration = GetDyingAnimationDuration();

		// client receives a negative value
		animDuration *= -1.0;

		if (animDuration < timeDiff) // reasonable way to fix client side unfinished sequence bug
		{
			// by some reason, if client receives a value less
			// than "(negative current sequence time) * 100"
			// animation will play visually awkward
			// at this function call time, player death animation
			// has already finished so we can safely fake it
			timeDiff = animDuration;
		}
	}
#endif

	MESSAGE_BEGIN(MSG_ALL, gmsgSendCorpse);
		WRITE_STRING(pModel);
		WRITE_LONG(pev->origin.x * 128);
		WRITE_LONG(pev->origin.y * 128);
		WRITE_LONG(pev->origin.z * 128);
		WRITE_COORD(pev->angles.x);
		WRITE_COORD(pev->angles.y);
		WRITE_COORD(pev->angles.z);
		WRITE_LONG(timeDiff * 100);
		WRITE_BYTE(pev->sequence);
		WRITE_BYTE(pev->body);
		WRITE_BYTE(m_iTeam);
		WRITE_BYTE(entindex());
	MESSAGE_END();

#ifndef REGAMEDLL_FIXES
	// already defined in StartDeathCam
	m_canSwitchObserverModes = true;
#endif

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_CLIENT_CORPSE_SPAWNED, this);
	}
}

BOOL CBasePlayer::IsArmored(int nHitGroup)
{
	BOOL fApplyArmor = FALSE;

	if (m_iKevlar == ARMOR_NONE)
		return FALSE;

	switch (nHitGroup)
	{
	case HITGROUP_HEAD:
	{
		fApplyArmor = (m_iKevlar == ARMOR_VESTHELM);
		break;
	}
	case HITGROUP_GENERIC:
	case HITGROUP_CHEST:
	case HITGROUP_STOMACH:
	case HITGROUP_LEFTARM:
	case HITGROUP_RIGHTARM:
		fApplyArmor = TRUE;
		break;
	}

	return fApplyArmor;
}

BOOL CBasePlayer::ShouldDoLargeFlinch(int nHitGroup, int nGunType)
{
	if (pev->flags & FL_DUCKING)
		return FALSE;

	if (nHitGroup != HITGROUP_LEFTLEG && nHitGroup != HITGROUP_RIGHTLEG)
	{
		switch (nGunType)
		{
		case WEAPON_SCOUT:
		case WEAPON_AUG:
		case WEAPON_SG550:
		case WEAPON_GALIL:
		case WEAPON_FAMAS:
		case WEAPON_AWP:
		case WEAPON_M3:
		case WEAPON_M4A1:
		case WEAPON_G3SG1:
		case WEAPON_DEAGLE:
		case WEAPON_SG552:
		case WEAPON_AK47:
			return TRUE;
		}
	}

	return FALSE;
}

void CBasePlayer::SetPrefsFromUserinfo(char *infobuffer)
{
	const char *pszKeyVal;

	pszKeyVal = GET_KEY_VALUE(infobuffer, "_cl_autowepswitch");

	if (Q_strcmp(pszKeyVal, "") != 0)
		m_iAutoWepSwitch = Q_atoi(pszKeyVal);
	else
		m_iAutoWepSwitch = 1;

	pszKeyVal = GET_KEY_VALUE(infobuffer, "_vgui_menus");

	if (Q_strcmp(pszKeyVal, "") != 0)
		m_bVGUIMenus = Q_atoi(pszKeyVal) != 0;
	else
		m_bVGUIMenus = true;

	pszKeyVal = GET_KEY_VALUE(infobuffer, "_ah");

	if (Q_strcmp(pszKeyVal, "") != 0)
		m_bShowHints = Q_atoi(pszKeyVal) != 0;
	else
		m_bShowHints = true;
}

bool CBasePlayer::IsLookingAtPosition(Vector *pos, float angleTolerance)
{
	Vector to = *pos - EyePosition();
	Vector idealAngle = UTIL_VecToAngles(to);

	idealAngle.x = 360.0 - idealAngle.x;

	float deltaYaw = NormalizeAngle(idealAngle.y - pev->v_angle.y);
	float deltaPitch = NormalizeAngle(idealAngle.x - pev->v_angle.x);

	return (Q_abs(deltaYaw) < angleTolerance
		&& Q_abs(deltaPitch) < angleTolerance);
}

bool CBasePlayer::CanAffordPrimary()
{
	auto team = (m_iTeam == CT) ? TERRORIST : (m_iTeam == TERRORIST) ? CT : UNASSIGNED;
	if (team == UNASSIGNED)
		return false;

	for (auto& weapon : g_weaponStruct)
	{
		if ((weapon.m_side & team) && weapon.m_slot == PRIMARY_WEAPON_SLOT && m_iAccount >= weapon.m_price)
			return true;
	}

	return false;
}

bool CBasePlayer::CanAffordPrimaryAmmo()
{
	CBasePlayerWeapon *pPrimary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	for (auto& weapon : g_weaponStruct) {
		if (weapon.m_type == pPrimary->m_iId && m_iAccount >= weapon.m_ammoPrice)
			return true;
	}

	return false;
}

bool CBasePlayer::CanAffordSecondaryAmmo()
{
	CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PISTOL_SLOT]);
	for (auto& weapon : g_weaponStruct) {
		if (weapon.m_type == pSecondary->m_iId && m_iAccount >= weapon.m_ammoPrice)
			return true;
	}

	return false;
}

bool CBasePlayer::CanAffordArmor()
{
	if (m_iKevlar == ARMOR_KEVLAR && pev->armorvalue == 100.0f && m_iAccount >= HELMET_PRICE)
		return true;

	return (m_iAccount >= KEVLAR_PRICE);
}

bool CBasePlayer::CanAffordDefuseKit()
{
	return (m_iAccount >= DEFUSEKIT_PRICE);
}

bool CBasePlayer::CanAffordGrenade()
{
	return (m_iAccount >= FLASHBANG_PRICE);
}

bool CBasePlayer::NeedsPrimaryAmmo()
{
	CBasePlayerWeapon *pPrimary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	if (!pPrimary || pPrimary->m_iId == WEAPON_SHIELDGUN) {
		return false;
	}

	return (m_rgAmmo[pPrimary->m_iPrimaryAmmoType] < pPrimary->iMaxAmmo1());
}

bool CBasePlayer::NeedsSecondaryAmmo()
{
	CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PISTOL_SLOT]);
	if (!pSecondary) {
		return false;
	}

	return (m_rgAmmo[pSecondary->m_iPrimaryAmmoType] < pSecondary->iMaxAmmo1());
}

bool CBasePlayer::NeedsArmor()
{
	if (m_iKevlar == ARMOR_NONE)
		return true;

	return (pev->armorvalue < 50.0f);
}

bool CBasePlayer::NeedsDefuseKit()
{
	if (m_bHasDefuser || m_iTeam != CT)
		return false;

	return (CSGameRules()->m_bMapHasBombTarget);
}

bool CBasePlayer::NeedsGrenade()
{
	int iAmmoIndex = GetAmmoIndex("HEGrenade");

	if (iAmmoIndex > 0 && m_rgAmmo[iAmmoIndex])
		return false;

	iAmmoIndex = GetAmmoIndex("Flashbang");

	if (iAmmoIndex > 0 && m_rgAmmo[iAmmoIndex])
		return false;

	iAmmoIndex = GetAmmoIndex("SmokeGrenade");

	if (iAmmoIndex > 0 && m_rgAmmo[iAmmoIndex])
		return false;

	return true;
}

void CBasePlayer::ClientCommand(const char *cmd, const char *arg1, const char *arg2, const char *arg3)
{
	BotArgs[0] = cmd;
	BotArgs[1] = arg1;
	BotArgs[2] = arg2;
	BotArgs[3] = arg3;

	UseBotArgs = true;
	::ClientCommand_(ENT(pev));
	UseBotArgs = false;
}

const char *GetBuyStringForWeaponClass(int weaponClass)
{
	switch (weaponClass)
	{
	case WEAPONCLASS_PISTOL:
		return "deagle elites fn57 usp glock p228 shield";
	case WEAPONCLASS_SNIPERRIFLE:
		return "awp sg550 g3sg1 scout";
	case WEAPONCLASS_GRENADE:
		return "hegren";
	case WEAPONCLASS_SHOTGUN:
		return "xm1014 m3";
	case WEAPONCLASS_SUBMACHINEGUN:
		return "p90 ump45 mp5 tmp mac10";
	case WEAPONCLASS_MACHINEGUN:
		return "m249";
	case WEAPONCLASS_RIFLE:
		return "sg552 aug ak47 m4a1 galil famas";
	}

	return nullptr;
}

void CBasePlayer::ClearAutoBuyData()
{
	m_autoBuyString[0] = '\0';
}

void CBasePlayer::AddAutoBuyData(const char *str)
{
	int len = Q_strlen(m_autoBuyString);

	if (len < sizeof(m_autoBuyString) - 1)
	{
		if (len > 0)
		{
			Q_strncat(m_autoBuyString, " ", len);
		}

#ifndef REGAMEDLL_FIXES
		Q_strncat(m_autoBuyString, str, sizeof(m_autoBuyString) - Q_strlen(m_autoBuyString));
#else
		Q_strncat(m_autoBuyString, str, sizeof(m_autoBuyString) - Q_strlen(m_autoBuyString) - 1);
#endif
	}
}

void CBasePlayer::InitRebuyData(const char *str)
{
	if (!str || Q_strlen(str) > MAX_REBUY_LENGTH)
	{
		return;
	}

	if (m_rebuyString)
	{
		delete[] m_rebuyString;
		m_rebuyString = nullptr;
	}

	m_rebuyString = new char[Q_strlen(str) + 1];
	Q_strcpy(m_rebuyString, str);
	m_rebuyString[Q_strlen(str)] = '\0';
}

void CBasePlayer::AutoBuy()
{
	const char *c = nullptr;
	bool boughtPrimary = false;
	bool boughtSecondary = false;
	char prioritizedString[MAX_AUTOBUY_LENGTH];

	c = PickFlashKillWeaponString();

	if (c)
	{
		ParseAutoBuyString(c, boughtPrimary, boughtSecondary);
	}

	c = PickGrenadeKillWeaponString();

	if (c)
	{
		ParseAutoBuyString(c, boughtPrimary, boughtSecondary);
	}

	c = PickPrimaryCareerTaskWeapon();

	if (c)
	{
		Q_strcpy(prioritizedString, c);

		PrioritizeAutoBuyString(prioritizedString, m_autoBuyString);
		ParseAutoBuyString(prioritizedString, boughtPrimary, boughtSecondary);
	}

	c = PickSecondaryCareerTaskWeapon();

	if (c)
	{
		Q_strcpy(prioritizedString, c);

		PrioritizeAutoBuyString(prioritizedString, m_autoBuyString);
		ParseAutoBuyString(prioritizedString, boughtPrimary, boughtSecondary);
	}

	ParseAutoBuyString(m_autoBuyString, boughtPrimary, boughtSecondary);

	c = PickFlashKillWeaponString();

	if (c)
	{
		ParseAutoBuyString(c, boughtPrimary, boughtSecondary);
	}

	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_LEFT_BUY_ZONE);
	}
}

bool IsPrimaryWeaponClass(int classId)
{
	return (classId >= WEAPONCLASS_SUBMACHINEGUN && classId <= WEAPONCLASS_SNIPERRIFLE);
}

bool IsPrimaryWeaponId(int id)
{
	int classId = WEAPONCLASS_NONE;
	const char *alias = WeaponIDToAlias(id);

	if (alias)
	{
		classId = AliasToWeaponClass(alias);
	}

	return IsPrimaryWeaponClass(classId);
}

bool IsSecondaryWeaponClass(int classId)
{
	return (classId == WEAPONCLASS_PISTOL);
}

bool IsSecondaryWeaponId(int id)
{
	int classId = WEAPONCLASS_NONE;
	const char *alias = WeaponIDToAlias(id);

	if (alias)
	{
		classId = AliasToWeaponClass(alias);
	}

	return IsSecondaryWeaponClass(classId);
}

const char *GetWeaponAliasFromName(const char *weaponName)
{
	const char cut_weapon[] = "weapon_";
	if (!Q_strncmp(weaponName, cut_weapon, sizeof(cut_weapon) - 1))
	{
		weaponName += sizeof(cut_weapon) - 1;
	}

	return weaponName;
}

bool CurrentWeaponSatisfies(CBasePlayerWeapon *pWeapon, int id, int classId)
{
	if (!pWeapon)
		return false;

	const char *weaponName = GetWeaponAliasFromName(pWeapon->pszName());

	if (id && AliasToWeaponID(weaponName) == id)
		return true;

	if (classId && AliasToWeaponClass(weaponName) == classId)
		return true;

	return false;
}

const char *CBasePlayer::PickPrimaryCareerTaskWeapon()
{
	const int BufLen = 256;
	static char buf[BufLen];
	CBasePlayerWeapon *pPrimary;
	std::vector<CCareerTask *> taskVector;

	if (!TheCareerTasks)
	{
		return nullptr;
	}

	buf[0] = '\0';
	pPrimary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);

	for (auto pTask : *TheCareerTasks->GetTasks())
	{
		if (pTask->IsComplete() || pTask->GetWeaponId() == WEAPON_HEGRENADE)
			continue;

		if (!IsPrimaryWeaponId(pTask->GetWeaponId()))
		{
			if (!IsPrimaryWeaponClass(pTask->GetWeaponClassId()))
			{
				continue;
			}
		}

		if (pPrimary)
		{
			if (CurrentWeaponSatisfies(pPrimary, pTask->GetWeaponId(), pTask->GetWeaponClassId()))
			{
				if (IsPrimaryWeaponId(pTask->GetWeaponId()))
				{
					return WeaponIDToAlias(pTask->GetWeaponId());
				}
				else
				{
					return GetBuyStringForWeaponClass(pTask->GetWeaponClassId());
				}
			}
		}

		taskVector.push_back(pTask);
	}

	int taskNum = taskVector.size();
	if (taskNum > 1)
	{
		// randomize names weapons of list
		int rand = RANDOM_LONG(0, taskNum - 1);
		SWAP(taskVector[0], taskVector[rand]);
	}

	if (!taskNum)
	{
		return nullptr;
	}

	for (int i = 0; i < taskNum; i++)
	{
		CCareerTask *pTask = taskVector[i];

		if (IsPrimaryWeaponId(pTask->GetWeaponId()))
			Q_strncat(buf, WeaponIDToAlias(pTask->GetWeaponId()), sizeof(buf) - Q_strlen(buf) - 1);
		else
			Q_strncat(buf, GetBuyStringForWeaponClass(pTask->GetWeaponClassId()), sizeof(buf) - Q_strlen(buf) - 1);

		Q_strncat(buf, " ", sizeof(buf) - Q_strlen(buf) - 1);
	}

	return buf;
}

const char *CBasePlayer::PickSecondaryCareerTaskWeapon()
{
	const int BufLen = 256;
	static char buf[BufLen];
	CBasePlayerWeapon *pSecondary;
	std::vector<CCareerTask *> taskVector;

	if (!TheCareerTasks)
	{
		return nullptr;
	}

	pSecondary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PISTOL_SLOT]);

	for (auto pTask : *TheCareerTasks->GetTasks())
	{
		if (pTask->IsComplete() || pTask->GetWeaponId() == WEAPON_HEGRENADE)
			continue;

		if (!IsSecondaryWeaponId(pTask->GetWeaponId()))
		{
			if (!IsSecondaryWeaponClass(pTask->GetWeaponClassId()))
			{
				continue;
			}
		}

		if (pSecondary)
		{
			if (CurrentWeaponSatisfies(pSecondary, pTask->GetWeaponId(), pTask->GetWeaponClassId()))
			{
				if (IsSecondaryWeaponId(pTask->GetWeaponId()))
				{
					return WeaponIDToAlias(pTask->GetWeaponId());
				}
				else
				{
					return GetBuyStringForWeaponClass(pTask->GetWeaponClassId());
				}
			}
		}

		taskVector.push_back(pTask);
	}

	int taskNum = taskVector.size();
	if (taskNum > 1)
	{
		// randomize names weapons of list
		int rand = RANDOM_LONG(0, taskNum - 1);
		SWAP(taskVector[0], taskVector[rand]);
	}

	if (!taskNum)
	{
		return nullptr;
	}

	buf[0] = '\0';

	for (int i = 0; i < taskNum; i++)
	{
		CCareerTask *pTask = taskVector[i];

		if (IsSecondaryWeaponId(pTask->GetWeaponId()))
			Q_strncat(buf, WeaponIDToAlias(pTask->GetWeaponId()), sizeof(buf) - Q_strlen(buf) - 1);
		else
			Q_strncat(buf, GetBuyStringForWeaponClass(pTask->GetWeaponClassId()), sizeof(buf) - Q_strlen(buf) - 1);

		Q_strncat(buf, " ", sizeof(buf) - Q_strlen(buf) - 1);
	}

	return buf;
}

const char *CBasePlayer::PickFlashKillWeaponString()
{
	if (!TheCareerTasks)
		return nullptr;

	bool foundOne = false;
	for (auto pTask : *TheCareerTasks->GetTasks())
	{
		if (!pTask->IsComplete() && !Q_strcmp(pTask->GetTaskName(), "killblind"))
		{
			foundOne = true;
			break;
		}
	}

	if (foundOne)
		return "flash flash";

	return nullptr;
}

const char *CBasePlayer::PickGrenadeKillWeaponString()
{
	if (!TheCareerTasks)
		return nullptr;

	bool foundOne = false;
	for (auto pTask : *TheCareerTasks->GetTasks())
	{
		if (!pTask->IsComplete() && pTask->GetWeaponId() == WEAPON_HEGRENADE)
		{
			foundOne = true;
			break;
		}
	}

	if (foundOne)
		return "hegren";

	return nullptr;
}

// PostAutoBuyCommandProcessing - reorders the tokens in autobuyString based on the order of tokens in the priorityString.
void CBasePlayer::PrioritizeAutoBuyString(char *autobuyString, const char *priorityString)
{
	char newString[MAX_AUTOBUY_LENGTH];
	int newStringPos = 0;
	char priorityToken[32];

	if (!priorityString || !autobuyString)
		return;

	const char *priorityChar = priorityString;
	while (*priorityChar != '\0')
	{
		int i = 0;

		// get the next token from the priority string.
		while (*priorityChar != '\0' && *priorityChar != ' ')
		{
			priorityToken[i++] = *priorityChar;
			priorityChar++;
		}

		priorityToken[i] = '\0';

		// skip spaces
		while (*priorityChar == ' ')
			priorityChar++;

		if (Q_strlen(priorityToken) == 0)
		{
			continue;
		}

		// see if the priority token is in the autobuy string.
		// if  it is, copy that token to the new string and blank out
		// that token in the autobuy string.
		char *autoBuyPosition = Q_strstr(autobuyString, priorityToken);
		if (autoBuyPosition)
		{
			while (*autoBuyPosition != '\0' && *autoBuyPosition != ' ')
			{
				newString[newStringPos] = *autoBuyPosition;
				*autoBuyPosition = ' ';

				newStringPos++;
				autoBuyPosition++;
			}

			newString[newStringPos++] = ' ';
		}
	}

	// now just copy anything left in the autobuyString to the new string in the order it's in already.
	char *autobuyPosition = autobuyString;
	while (*autobuyPosition != '\0')
	{
		// skip spaces
		while (*autobuyPosition == ' ')
			autobuyPosition++;

		// copy the token over to the new string.
		while (*autobuyPosition != '\0' && *autobuyPosition != ' ')
		{
			newString[newStringPos++] = *autobuyPosition;
			autobuyPosition++;
		}

		// add a space at the end.
		newString[newStringPos++] = ' ';
	}

	// terminate the string.  Trailing spaces shouldn't matter.
	newString[newStringPos] = '\0';

	Q_sprintf(autobuyString, "%s", newString);
}

void CBasePlayer::ParseAutoBuyString(const char *string, bool &boughtPrimary, bool &boughtSecondary)
{
	char command[32];
	const char *c = string;

	if (!string || !string[0])
		return;

	// loop through the string of commands, trying each one in turn.
	while (*c)
	{
		int i = 0;

		// copy the next word into the command buffer.
		while (*c && (*c != ' ') && i < sizeof(command) - 1)
		{
			command[i++] = *c++;
		}

		if (*c == ' ')
		{
			// skip the space.
			c++;
		}

		// terminate the string.
		command[i] = '\0';

		// clear out any spaces.
		i = 0;
		while (command[i] != '\0')
		{
			if (command[i] == ' ')
			{
				command[i] = '\0';
				break;
			}

			i++;
		}

		// make sure we actually have a command.
		if (Q_strlen(command) == 0)
		{
			continue;
		}

		AutoBuyInfoStruct *commandInfo = GetAutoBuyCommandInfo(command);
		if (ShouldExecuteAutoBuyCommand(commandInfo, boughtPrimary, boughtSecondary))
		{
			ClientCommand(commandInfo->m_command);

			// check to see if we actually bought a primary or secondary weapon this time.
			PostAutoBuyCommandProcessing(commandInfo, boughtPrimary, boughtSecondary);
		}
	}
}

bool CBasePlayer::ShouldExecuteAutoBuyCommand(AutoBuyInfoStruct *commandInfo, bool boughtPrimary, bool boughtSecondary)
{
	if (!commandInfo)
	{
		return false;
	}

	if (boughtPrimary && (commandInfo->m_class & AUTOBUYCLASS_PRIMARY) != 0 && (commandInfo->m_class & AUTOBUYCLASS_AMMO) == 0)
	{
		// this is a primary weapon and we already have one.
		return false;
	}

	if (boughtSecondary && (commandInfo->m_class & AUTOBUYCLASS_SECONDARY) != 0 && (commandInfo->m_class & AUTOBUYCLASS_AMMO) == 0)
	{
		// this is a secondary weapon and we already have one.
		return false;
	}

	return true;
}

AutoBuyInfoStruct *CBasePlayer::GetAutoBuyCommandInfo(const char *command)
{
	// loop through all the commands till we find the one that matches.
	for (auto& buyInfo : g_autoBuyInfo)
	{
		if (buyInfo.m_class == AUTOBUYCLASS_NONE)
			continue;

		if (FStrEq(buyInfo.m_command, command))
			return &buyInfo;
	}

	return nullptr;
}

void CBasePlayer::PostAutoBuyCommandProcessing(AutoBuyInfoStruct *commandInfo, bool &boughtPrimary, bool &boughtSecondary)
{
	if (!commandInfo)
	{
		return;
	}

	CBasePlayerWeapon *pPrimary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PISTOL_SLOT]);

	if (pPrimary && FClassnameIs(pPrimary->pev, commandInfo->m_classname))
	{
		// I just bought the gun I was trying to buy.
		boughtPrimary = true;
	}
	else if (!pPrimary && ((commandInfo->m_class & AUTOBUYCLASS_SHIELD) == AUTOBUYCLASS_SHIELD) && HasShield())
	{
		// the shield is a primary weapon even though it isn't a "real" weapon.
		boughtPrimary = true;
	}
	else if (pSecondary && FClassnameIs(pSecondary->pev, commandInfo->m_classname))
	{
		// I just bought the pistol I was trying to buy.
		boughtSecondary = true;
	}
}

void CBasePlayer::BuildRebuyStruct()
{
	if (m_bIsInRebuy)
	{
		// if we are in the middle of a rebuy, we don't want to update the buy struct.
		return;
	}

	CBasePlayerWeapon *pPrimary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PISTOL_SLOT]);

	// do the primary weapon/ammo stuff.
	if (!pPrimary)
	{
		// count a shieldgun as a primary.
		if (HasShield())
		{
			m_rebuyStruct.m_primaryWeapon = WEAPON_SHIELDGUN;
			m_rebuyStruct.m_primaryAmmo = 0;			// shields don't have ammo.
		}
		else
		{
			m_rebuyStruct.m_primaryWeapon = 0;	// if we don't have a shield and we don't have a primary weapon, we got nuthin.
			m_rebuyStruct.m_primaryAmmo = 0;	// can't have ammo if we don't have a gun right?
		}
	}
	else
	{
		m_rebuyStruct.m_primaryWeapon = pPrimary->m_iId;
		m_rebuyStruct.m_primaryAmmo = m_rgAmmo[pPrimary->m_iPrimaryAmmoType];
	}

	// do the secondary weapon/ammo stuff.
	if (!pSecondary)
	{
		m_rebuyStruct.m_secondaryWeapon = 0;
		m_rebuyStruct.m_secondaryAmmo = 0;	// can't have ammo if we don't have a gun right?
	}
	else
	{
		m_rebuyStruct.m_secondaryWeapon = pSecondary->m_iId;
		m_rebuyStruct.m_secondaryAmmo = m_rgAmmo[pSecondary->m_iPrimaryAmmoType];
	}

	// HE Grenade
	int iAmmoIndex = GetAmmoIndex("HEGrenade");

	if (iAmmoIndex != -1)
		m_rebuyStruct.m_heGrenade = m_rgAmmo[iAmmoIndex];
	else
		m_rebuyStruct.m_heGrenade = 0;

	// flashbang
	iAmmoIndex = GetAmmoIndex("Flashbang");

	if (iAmmoIndex != -1)
		m_rebuyStruct.m_flashbang = m_rgAmmo[iAmmoIndex];
	else
		m_rebuyStruct.m_flashbang = 0;

	// smokegrenade
	iAmmoIndex = GetAmmoIndex("SmokeGrenade");

	if (iAmmoIndex != -1)
		m_rebuyStruct.m_smokeGrenade = m_rgAmmo[iAmmoIndex];
	else
		m_rebuyStruct.m_smokeGrenade = 0;

	m_rebuyStruct.m_defuser = m_bHasDefuser;			// defuser
	m_rebuyStruct.m_nightVision = m_bHasNightVision;	// night vision
	m_rebuyStruct.m_armor = m_iKevlar;					// check for armor.
}

void CBasePlayer::Rebuy()
{
	char *fileData = m_rebuyString;
	char *token;

	m_bIsInRebuy = true;

	while (true)
	{
		fileData = SharedParse(fileData);
		token = SharedGetToken();

		if (!fileData)
			break;

		if (!Q_stricmp(token, "primaryWeapon"))
			RebuyPrimaryWeapon();
		else if (!Q_stricmp(token, "primaryAmmo"))
			RebuyPrimaryAmmo();
		else if (!Q_stricmp(token, "secondaryWeapon"))
			RebuySecondaryWeapon();
		else if (!Q_stricmp(token, "secondaryAmmo"))
			RebuySecondaryAmmo();
		else if (!Q_stricmp(token, "hegrenade"))
			RebuyHEGrenade();
		else if (!Q_stricmp(token, "flashbang"))
			RebuyFlashbang();
		else if (!Q_stricmp(token, "smokegrenade"))
			RebuySmokeGrenade();
		else if (!Q_stricmp(token, "defuser"))
			RebuyDefuser();
		else if (!Q_stricmp(token, "nightvision"))
			RebuyNightVision();
		else if (!Q_stricmp(token, "armor"))
			RebuyArmor();
	}

	m_bIsInRebuy = false;

	// after we're done buying, the user is done with their equipment purchasing experience.
	// so we are effectively out of the buy zone.
	if (TheTutor)
	{
		TheTutor->OnEvent(EVENT_PLAYER_LEFT_BUY_ZONE);
	}
}

void CBasePlayer::RebuyPrimaryWeapon()
{
	if (!m_rgpPlayerItems[PRIMARY_WEAPON_SLOT])
	{
		if (m_rebuyStruct.m_primaryWeapon)
		{
			const char *alias = WeaponIDToAlias(m_rebuyStruct.m_primaryWeapon);
			if (alias)
				ClientCommand(alias);
		}
	}
}

void CBasePlayer::RebuyPrimaryAmmo()
{
	CBasePlayerWeapon *pPrimary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PRIMARY_WEAPON_SLOT]);
	if (pPrimary)
	{
		// if we had more ammo before than we have now, buy more.
		if (m_rebuyStruct.m_primaryAmmo > m_rgAmmo[pPrimary->m_iPrimaryAmmoType]) {
			ClientCommand("primammo");
		}
	}
}

void CBasePlayer::RebuySecondaryWeapon()
{
	if (m_rebuyStruct.m_secondaryWeapon)
	{
		const char *alias = WeaponIDToAlias(m_rebuyStruct.m_secondaryWeapon);
		if (alias) {
			ClientCommand(alias);
		}
	}
}

void CBasePlayer::RebuySecondaryAmmo()
{
	CBasePlayerWeapon *pSecondary = static_cast<CBasePlayerWeapon *>(m_rgpPlayerItems[PISTOL_SLOT]);
	if (pSecondary)
	{
		if (m_rebuyStruct.m_secondaryAmmo > m_rgAmmo[pSecondary->m_iPrimaryAmmoType]) {
			ClientCommand("secammo");
		}
	}
}

void CBasePlayer::RebuyHEGrenade()
{
	int iAmmoIndex = GetAmmoIndex("HEGrenade");
	if (iAmmoIndex == -1)
		return;

	int numToBuy = m_rebuyStruct.m_heGrenade - m_rgAmmo[iAmmoIndex];
	for (int i = 0; i < numToBuy; i++)
		ClientCommand("hegren");
}

void CBasePlayer::RebuyFlashbang()
{
	int iAmmoIndex = GetAmmoIndex("Flashbang");
	if (iAmmoIndex == -1)
		return;

	int numToBuy = m_rebuyStruct.m_flashbang - m_rgAmmo[iAmmoIndex];
	for (int i = 0; i < numToBuy; i++)
		ClientCommand("flash");
}

void CBasePlayer::RebuySmokeGrenade()
{
	int iAmmoIndex = GetAmmoIndex("SmokeGrenade");
	if (iAmmoIndex == -1)
		return;

	int numToBuy = m_rebuyStruct.m_smokeGrenade - m_rgAmmo[iAmmoIndex];
	for (int i = 0; i < numToBuy; i++)
		ClientCommand("sgren");
}

void CBasePlayer::RebuyDefuser()
{
	// If we don't have a defuser, and we want one, buy it!
	if (m_rebuyStruct.m_defuser && !m_bHasDefuser)
	{
		ClientCommand("defuser");
	}
}

void CBasePlayer::RebuyNightVision()
{
	// If we don't have night vision and we want one, buy it!
	if (m_rebuyStruct.m_nightVision && !m_bHasNightVision)
	{
		ClientCommand("nvgs");
	}
}

void CBasePlayer::RebuyArmor()
{
	if (m_rebuyStruct.m_armor)
	{
		if (m_rebuyStruct.m_armor > m_iKevlar)
		{
			if (m_rebuyStruct.m_armor == ARMOR_KEVLAR)
				ClientCommand("vest");
			else
				ClientCommand("vesthelm");
		}
	}
}

bool CBasePlayer::IsObservingPlayer(CBasePlayer *pPlayer)
{
	if (!pPlayer || pev->flags == FL_DORMANT)
		return false;

	if (FNullEnt(pPlayer))
		return false;

	return (GetObserverMode() == OBS_IN_EYE && pev->iuser2 == pPlayer->entindex()) != 0;
}

void CBasePlayer::UpdateLocation(bool forceUpdate)
{
	if (!forceUpdate && m_flLastUpdateTime >= gpGlobals->time + 2.0f)
		return;

	const char *placeName = nullptr;

	if (pev->deadflag == DEAD_NO && (
#ifdef REGAMEDLL_ADD
		(location_area_info.value == 1 || location_area_info.value == 3) ||
#endif
		AreBotsAllowed()))
	{
		// search the place name where is located the player
		Place playerPlace = TheNavAreaGrid.GetPlace(&pev->origin);
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

	if (!placeName || !placeName[0] || (m_lastLocation[0] && !Q_strcmp(placeName, &m_lastLocation[1])))
	{
		return;
	}

	m_flLastUpdateTime = gpGlobals->time;
	Q_snprintf(m_lastLocation, sizeof(m_lastLocation), "#%s", placeName);

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (!UTIL_IsValidPlayer(pPlayer))
			continue;

		if (pPlayer->m_iTeam == m_iTeam || pPlayer->m_iTeam == SPECTATOR)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgLocation, nullptr, pPlayer->edict());
				WRITE_BYTE(entindex());
				WRITE_STRING(m_lastLocation);
			MESSAGE_END();
		}
		else if (forceUpdate)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgLocation, nullptr, pPlayer->edict());
				WRITE_BYTE(entindex());
				WRITE_STRING("");
			MESSAGE_END();
		}
	}
}

void CBasePlayer::ReloadWeapons(CBasePlayerItem *pWeapon, bool bForceReload, bool bForceRefill)
{
#ifdef REGAMEDLL_ADD
	bool bCanAutoReload = (bForceReload || auto_reload_weapons.value != 0.0f);
	bool bCanRefillBPAmmo = (bForceRefill || refill_bpammo_weapons.value != 0.0f);

	if (!bCanAutoReload && !bCanRefillBPAmmo)
		return;

	// if we died in the previous round
	// so that we have nothing to reload
	if (!m_bNotKilled)
		return;

	// to ignore first spawn on ClientPutinServer
	if (m_bJustConnected)
		return;

	for (int i = PRIMARY_WEAPON_SLOT; i <= PISTOL_SLOT; i++)
	{
		auto item = m_rgpPlayerItems[i];
		while (item)
		{
			if (pWeapon == nullptr || pWeapon == item)
			{
				if (bCanRefillBPAmmo) {
					m_rgAmmo[item->PrimaryAmmoIndex()] = item->iMaxAmmo1();
				}
				if (bCanAutoReload) {
					((CBasePlayerWeapon *)item)->InstantReload(bCanRefillBPAmmo);
				}
			}

			if (pWeapon == item)
				break;

			item = item->m_pNext;
		}

		if (pWeapon && pWeapon == item)
			break;
	}
#endif
}

void CBasePlayer::TeamChangeUpdate()
{
	MESSAGE_BEGIN(MSG_ALL, gmsgTeamInfo);
		WRITE_BYTE(entindex());
		WRITE_STRING(GetTeamName(m_iTeam));
	MESSAGE_END();

	if (m_iTeam != UNASSIGNED)
	{
		SetScoreboardAttributes();
	}
}

LINK_HOOK_CLASS_CHAIN(bool, CBasePlayer, HasRestrictItem, (ItemID item, ItemRestType type), item, type)

bool EXT_FUNC CBasePlayer::__API_HOOK(HasRestrictItem)(ItemID item, ItemRestType type) {
	return false;
}

void CBasePlayer::DropSecondary()
{
	if (HasShield())
	{
		if (IsProtectedByShield() && m_pActiveItem) {
			((CBasePlayerWeapon *)m_pActiveItem)->SecondaryAttack();
		}

		m_bShieldDrawn = false;
	}

#ifdef REGAMEDLL_ADD
	ForEachItem(PISTOL_SLOT, [this](CBasePlayerItem *item) {
		DropPlayerItem(STRING(item->pev->classname));
		return false;
	});
#else
	auto item = m_rgpPlayerItems[PISTOL_SLOT];
	if (item)
	{
		DropPlayerItem(STRING(item->pev->classname));
	}
#endif

}

void CBasePlayer::DropPrimary()
{
	if (HasShield()) {
		DropShield();
		return;
	}

#ifdef REGAMEDLL_ADD
	ForEachItem(PRIMARY_WEAPON_SLOT, [this](CBasePlayerItem *item) {
		DropPlayerItem(STRING(item->pev->classname));
		return false;
	});
#else
	auto item = m_rgpPlayerItems[PRIMARY_WEAPON_SLOT];
	if (item)
	{
		DropPlayerItem(STRING(item->pev->classname));
	}
#endif

}

CBasePlayerItem *CBasePlayer::GetItemByName(const char *itemName) {
	return ForEachItem([itemName](CBasePlayerItem *item) {
		return FClassnameIs(item->pev, itemName);
	});
}

CBasePlayerItem *CBasePlayer::GetItemById(WeaponIdType weaponID) {
	return ForEachItem([weaponID](CBasePlayerItem *item) {
		return item->m_iId == weaponID;
	});
}

void CBasePlayer::RemoveBomb()
{
	auto pBomb = GetItemByName("weapon_c4");
	if (!pBomb)
		return;

	m_bHasC4 = false;
	pev->body = 0;
	SetBombIcon(FALSE);
	SetProgressBarTime(0);

	if (m_pActiveItem == pBomb) {
		((CBasePlayerWeapon *)pBomb)->RetireWeapon();
	}

	if (RemovePlayerItem(pBomb)) {
		pev->weapons &= ~(1 << pBomb->m_iId);

#ifdef REGAMEDLL_FIXES
		// No more weapon
		if ((pev->weapons & ~(1 << WEAPON_SUIT)) == 0) {
			m_iHideHUD |= HIDEHUD_WEAPONS;
		}
#endif

		pBomb->Kill();
	}
}

void CBasePlayer::GiveDefuser()
{
	m_bHasDefuser = true;
	pev->body = 1;

	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
		WRITE_BYTE(STATUSICON_SHOW);
		WRITE_STRING("defuser");
		WRITE_BYTE(0);
		WRITE_BYTE(160);
		WRITE_BYTE(0);
	MESSAGE_END();

	SendItemStatus();

#if defined(REGAMEDLL_FIXES) || defined(BUILD_LATEST)
	SetScoreboardAttributes();
#endif
}

void CBasePlayer::RemoveDefuser()
{
	m_bHasDefuser = false;
	pev->body = 0;

	MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
		WRITE_BYTE(STATUSICON_HIDE);
		WRITE_STRING("defuser");
	MESSAGE_END();

	SendItemStatus();

#ifdef REGAMEDLL_FIXES
	if (m_bIsDefusing)
	{
		SetProgressBarTime(0);
		m_bIsDefusing = false;
	}
#else
	SetProgressBarTime(0);
#endif
}

CItemThighPack *SpawnDefuser(const Vector &vecOrigin, edict_t *pentOwner)
{
	CItemThighPack *pDefuser = (CItemThighPack *)CBaseEntity::Create("item_thighpack", vecOrigin, g_vecZero, pentOwner);

	if (pDefuser)
	{
		pDefuser->SetThink(&CBaseEntity::SUB_Remove);
		pDefuser->pev->nextthink = gpGlobals->time + CGameRules::GetItemKillDelay();
		pDefuser->pev->spawnflags |= SF_NORESPAWN;
	}

	return pDefuser;
}

void CBasePlayer::Disconnect()
{
	SetThink(nullptr);
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, OnSpawnEquip, (bool addDefault, bool equipGame), addDefault, equipGame)

void EXT_FUNC CBasePlayer::__API_HOOK(OnSpawnEquip)(bool addDefault, bool equipGame)
{
	if (equipGame)
	{
		CGamePlayerEquip *pWeaponEntity = nullptr;
		while ((pWeaponEntity = UTIL_FindEntityByClassname(pWeaponEntity, "game_player_equip")))
		{

#ifdef REGAMEDLL_FIXES
			if (pWeaponEntity->CanEquipOverTouch(this))
#endif
			{
				pWeaponEntity->Touch(this);

				addDefault = false;
			}
		}
	}

	if (m_bNotKilled)
		addDefault = false;

	if (addDefault || m_bIsVIP)
	{
		GiveDefaultItems();
	}

#ifdef REGAMEDLL_ADD
	if (!m_bIsVIP)
	{
		switch (static_cast<ArmorType>((int)free_armor.value))
		{
		case ARMOR_KEVLAR: GiveNamedItemEx("item_kevlar"); break;
		case ARMOR_VESTHELM: GiveNamedItemEx("item_assaultsuit"); break;
		}
	}

	if (NeedsDefuseKit() && (int)defuser_allocation.value == DEFUSERALLOCATION_ALL)
		GiveNamedItemEx("item_thighpack");
#endif
}

void CBasePlayer::HideTimer()
{
	// HACK HACK, we need to hide only the timer.
	MESSAGE_BEGIN(MSG_ONE, gmsgBombDrop, nullptr, pev);
		WRITE_COORD(0);
		WRITE_COORD(0);
		WRITE_COORD(0);
		WRITE_BYTE(BOMB_FLAG_PLANTED);
	MESSAGE_END();

	MESSAGE_BEGIN(MSG_ONE, gmsgBombPickup, nullptr, pev);
	MESSAGE_END();
}

LINK_HOOK_CLASS_CHAIN2(bool, CBasePlayer, MakeBomber)

bool EXT_FUNC CBasePlayer::__API_HOOK(MakeBomber)()
{
	if (!GiveNamedItemEx("weapon_c4"))
	{
		// something happened?
		// C4 failed to attach to the player
		return false;
	}

	m_bHasC4 = true;
	pev->body = 1;
	SetBombIcon();

	m_flDisplayHistory |= DHF_BOMB_RETRIEVED;
	HintMessage("#Hint_you_have_the_bomb", FALSE, TRUE);

	// Log this information
	UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Spawned_With_The_Bomb\"\n", STRING(pev->netname), GETPLAYERUSERID(edict()), GETPLAYERAUTHID(edict()));
	g_pGameRules->m_bBombDropped = FALSE;

	return true;
}

LINK_HOOK_CLASS_CHAIN2(bool, CBasePlayer, GetIntoGame)

bool EXT_FUNC CBasePlayer::__API_HOOK(GetIntoGame)()
{
	m_bNotKilled = false;
	m_iIgnoreGlobalChat = IGNOREMSG_NONE;

	m_iTeamKills = 0;
	m_iFOV = DEFAULT_FOV;

	Q_memset(&m_rebuyStruct, 0, sizeof(m_rebuyStruct));

	m_bIsInRebuy = false;
	m_bJustConnected = false;
	m_fLastMovement = gpGlobals->time;

	ResetMaxSpeed();
	m_iJoiningState = JOINED;

	if (CSGameRules()->m_bMapHasEscapeZone && m_iTeam == CT)
	{
#ifndef REGAMEDLL_ADD
		m_iAccount = 0;
#endif
		CheckStartMoney();
		AddAccount(startmoney.value, RT_INTO_GAME);
	}

	if (g_pGameRules->FPlayerCanRespawn(this))
	{
		Spawn();
		CSGameRules()->CheckWinConditions();

		if (!CSGameRules()->m_flRestartRoundTime && CSGameRules()->m_bMapHasBombTarget && !CSGameRules()->IsThereABomber() && !CSGameRules()->IsThereABomb()
#ifdef REGAMEDLL_ADD
			&& give_player_c4.value
#endif
			)
		{
			CSGameRules()->GiveC4();
		}
		if (m_iTeam == TERRORIST)
		{
			CSGameRules()->m_iNumEscapers++;
		}
	}
	else
	{
		pev->deadflag = DEAD_RESPAWNABLE;

		MAKE_STRING_CLASS("player", pev);

		pev->flags &= (FL_PROXY | FL_FAKECLIENT);
		pev->flags |= (FL_SPECTATOR | FL_CLIENT);

		edict_t *pentSpawnSpot = g_pGameRules->GetPlayerSpawnSpot(this);
		StartObserver(pev->origin, pentSpawnSpot->v.angles);

		CSGameRules()->CheckWinConditions();

		MESSAGE_BEGIN(MSG_ALL, gmsgTeamInfo);
			WRITE_BYTE(entindex());
			WRITE_STRING(GetTeamName(m_iTeam));
		MESSAGE_END();

		MESSAGE_BEGIN(MSG_ALL, gmsgLocation);
			WRITE_BYTE(entindex());
			WRITE_STRING("");
		MESSAGE_END();

		MESSAGE_BEGIN(MSG_ALL, gmsgScoreInfo);
			WRITE_BYTE(ENTINDEX(edict()));
			WRITE_SHORT(int(pev->frags));
			WRITE_SHORT(m_iDeaths);
			WRITE_SHORT(0);
			WRITE_SHORT(m_iTeam);
		MESSAGE_END();

		if (!(m_flDisplayHistory & DHF_SPEC_DUCK))
		{
			HintMessage("#Spec_Duck", TRUE, TRUE);
			m_flDisplayHistory |= DHF_SPEC_DUCK;
		}
	}

	return true;
}

void CBasePlayer::PlayerRespawnThink()
{
#ifdef REGAMEDLL_ADD
	if (GetObserverMode() != OBS_NONE && (m_iTeam == UNASSIGNED || m_iTeam == SPECTATOR))
		return;

	// Player cannot respawn while in the Choose Appearance menu
	if (m_iMenu == Menu_ChooseAppearance || m_iJoiningState == SHOWTEAMSELECT)
		return;

	if (pev->deadflag < DEAD_DYING)
		return;

	if (CSPlayer()->m_flRespawnPending > 0)
	{
		if (CSPlayer()->m_flRespawnPending <= gpGlobals->time)
		{
			// Pending respawn caused by game doesn't respawn with disabled CVar
			if (CSPlayer()->m_bGameForcingRespawn && !forcerespawn.value)
			{
				CSPlayer()->m_flRespawnPending = 0.0f;
				CSPlayer()->m_bGameForcingRespawn = false;
				return;
			}

			Spawn();
			pev->button = 0;
			pev->nextthink = -1;
			return;
		}
	}
	else if (pev->deadflag == DEAD_DEAD && forcerespawn.value > 0)
	{
		CSPlayer()->m_bGameForcingRespawn = true;
		CSPlayer()->m_flRespawnPending = gpGlobals->time + forcerespawn.value;
	}

#endif
}

LINK_HOOK_CLASS_CHAIN(bool, CBasePlayer, CanSwitchTeam, (TeamName teamToSwap), teamToSwap)

bool CBasePlayer::__API_HOOK(CanSwitchTeam)(TeamName teamToSwap)
{
	if (m_iTeam != teamToSwap)
		return false;

	// we won't VIP player to switch team
	if (CSGameRules()->m_pVIP == this)
	{
		return false;
	}

	return true;
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, SetSpawnProtection, (float flProtectionTime), flProtectionTime)

void EXT_FUNC CBasePlayer::__API_HOOK(SetSpawnProtection)(float flProtectionTime)
{
#ifdef REGAMEDLL_ADD
	if (respawn_immunity_effects.value > 0)
	{
		CSPlayer()->m_bSpawnProtectionEffects = true;
		pev->rendermode = kRenderTransAdd;
		pev->renderamt  = 100.0f;

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
			WRITE_BYTE(STATUSICON_FLASH);
			WRITE_STRING("suithelmet_full");
			WRITE_BYTE(0);
			WRITE_BYTE(160);
			WRITE_BYTE(0);
		MESSAGE_END();
	}

	CSPlayer()->m_flSpawnProtectionEndTime = gpGlobals->time + flProtectionTime;
#endif
}

LINK_HOOK_CLASS_VOID_CHAIN2(CBasePlayer, RemoveSpawnProtection)

void CBasePlayer::__API_HOOK(RemoveSpawnProtection)()
{
#ifdef REGAMEDLL_ADD
	if (CSPlayer()->m_bSpawnProtectionEffects)
	{
		if (pev->rendermode == kRenderTransAdd && pev->renderamt == 100.0f)
		{
			pev->renderamt = 255.0f;
			pev->rendermode = kRenderNormal;
		}

		MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, nullptr, pev);
			WRITE_BYTE(STATUSICON_HIDE);
			WRITE_STRING("suithelmet_full");
		MESSAGE_END();

		CSPlayer()->m_bSpawnProtectionEffects = false;
	}

	CSPlayer()->m_flSpawnProtectionEndTime = 0.0f;
#endif
}

LINK_HOOK_CLASS_VOID_CHAIN(CBasePlayer, DropIdlePlayer, (const char *reason), reason)

void EXT_FUNC CBasePlayer::__API_HOOK(DropIdlePlayer)(const char *reason)
{
	if (!autokick.value)
		return;

	edict_t *pEntity = edict();

	int iUserID = GETPLAYERUSERID(pEntity);

	// Log the kick
	UTIL_LogPrintf("\"%s<%i><%s><%s>\" triggered \"Game_idle_kick\" (auto)\n", STRING(pev->netname), iUserID , GETPLAYERAUTHID(pEntity), GetTeam(m_iTeam));
	UTIL_ClientPrintAll(HUD_PRINTCONSOLE, "#Game_idle_kick", STRING(pev->netname));

#ifdef REGAMEDLL_FIXES
	if (iUserID != -1)
	{
		SERVER_COMMAND(UTIL_VarArgs("kick #%d \"%s\"\n", iUserID, reason));
	}
#else
	SERVER_COMMAND(UTIL_VarArgs("kick \"%s\"\n", STRING(pev->netname)));
#endif // #ifdef REGAMEDLL_FIXES
}

bool CBasePlayer::Kill()
{
	if (GetObserverMode() != OBS_NONE)
		return false;

	if (m_iJoiningState != JOINED)
		return false;

	m_LastHitGroup = HITGROUP_GENERIC;

	// have the player kill himself
	pev->health = 0.0f;

#ifdef REGAMEDLL_API
	CSPlayer()->ResetAllStats(); // reset damage stats on killed himself or team change
#endif

	Killed(pev, GIB_NEVER);

	if (CSGameRules()->m_pVIP == this)
		CSGameRules()->m_iConsecutiveVIP = 10;

	return true;
}

const usercmd_t *CBasePlayer::GetLastUserCommand() const
{
#ifdef REGAMEDLL_API
	return CSPlayer()->GetLastUserCommand();
#else
	return nullptr;
#endif
}
