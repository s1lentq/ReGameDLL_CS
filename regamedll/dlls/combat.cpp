#include "precompiled.h"

void PlayerBlind(CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, float fadeTime, float fadeHold, int alpha, Vector &color)
{
	UTIL_ScreenFade(pPlayer, color, fadeTime, fadeHold, alpha, 0);

	if (!fadetoblack.value)
	{
		for (int i = 1; i <= gpGlobals->maxClients; i++)
		{
			CBasePlayer *pObserver = UTIL_PlayerByIndex(i);
			if (pObserver && pObserver->IsObservingPlayer(pPlayer))
			{
				UTIL_ScreenFade(pObserver, color, fadeTime, fadeHold, alpha, 0);
			}
		}
	}

	pPlayer->Blind(fadeTime * 0.33, fadeHold, fadeTime, alpha);

	if (TheBots)
	{
		TheBots->OnEvent(EVENT_PLAYER_BLINDED_BY_FLASHBANG, pPlayer);
	}
}

void RadiusFlash_TraceLine_hook(CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, Vector &vecSrc, Vector &vecSpot, TraceResult *tr)
{
	UTIL_TraceLine(vecSrc, vecSpot, dont_ignore_monsters, ENT(pevInflictor), tr);
}

void RadiusFlash(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int iClassIgnore, int bitsDamageType)
{
	CBaseEntity *pEntity = nullptr;
	TraceResult tr;
	float flAdjustedDamage, falloff;
	Vector vecSpot;
	float flRadius = 1500;

	if (flRadius)
		falloff = flDamage / flRadius;
	else
		falloff = 1;

	int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

	vecSrc.z += 1;

	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, 1500.0)))
	{
		TraceResult tr2;
		Vector vecLOS;
		float flDot;
		float fadeTime;
		float fadeHold;
		int alpha;
		CBasePlayer *pPlayer;
		float currentHoldTime;

		if (!pEntity->IsPlayer())
			continue;

		pPlayer = (CBasePlayer *)pEntity;

		if (pPlayer->pev->takedamage == DAMAGE_NO || pPlayer->pev->deadflag != DEAD_NO)
			continue;

		if (bInWater && pPlayer->pev->waterlevel == 0)
			continue;

		if (!bInWater && pPlayer->pev->waterlevel == 3)
			continue;

#ifdef REGAMEDLL_FIXES
		vecSpot = pPlayer->EyePosition();
#else
		// NOTE: See CBasePlayer::BodyTarget
		vecSpot = pPlayer->BodyTarget(vecSrc);
#endif

		g_ReGameHookchains.m_RadiusFlash_TraceLine.callChain(RadiusFlash_TraceLine_hook, pPlayer, pevInflictor, pevAttacker, vecSrc, vecSpot, &tr);

		if (tr.flFraction != 1.0f && tr.pHit != pPlayer->pev->pContainingEntity)
			continue;

		g_ReGameHookchains.m_RadiusFlash_TraceLine.callChain(RadiusFlash_TraceLine_hook, pPlayer, VARS(tr.pHit), pevAttacker, vecSpot, vecSrc, &tr2);

		if (tr2.flFraction >= 1.0)
		{
			if (tr.fStartSolid)
			{
				tr.vecEndPos = vecSrc;
				tr.flFraction = 0;
			}

			flAdjustedDamage = flDamage - (vecSrc - tr.vecEndPos).Length() * falloff;

			if (flAdjustedDamage < 0)
				flAdjustedDamage = 0;

			UTIL_MakeVectors(pPlayer->pev->v_angle);
			vecLOS = vecSrc - pPlayer->EarPosition();
			flDot = DotProduct(vecLOS, gpGlobals->v_forward);

			if (flDot < 0)
			{
				alpha = 200;
				fadeTime = flAdjustedDamage * 1.75;
				fadeHold = flAdjustedDamage / 3.5;
			}
			else
			{
				alpha = 255;
				fadeTime = flAdjustedDamage * 3;
				fadeHold = flAdjustedDamage / 1.5;
			}

			currentHoldTime = pPlayer->m_blindStartTime + pPlayer->m_blindHoldTime - gpGlobals->time;

			if (currentHoldTime > 0.0 && alpha == 255)
				fadeHold += currentHoldTime;

			if (pPlayer->m_blindStartTime != 0.0f && pPlayer->m_blindFadeTime != 0.0f)
			{
				if ((pPlayer->m_blindStartTime + pPlayer->m_blindFadeTime + pPlayer->m_blindHoldTime) > gpGlobals->time)
				{
					if (pPlayer->m_blindFadeTime > fadeTime)
						fadeTime = pPlayer->m_blindFadeTime;

					if (pPlayer->m_blindAlpha >= alpha)
						alpha = pPlayer->m_blindAlpha;
				}
			}

			Vector color(255, 255, 255);
			g_ReGameHookchains.m_PlayerBlind.callChain(PlayerBlind, pPlayer, pevInflictor, pevAttacker, fadeTime, fadeHold, alpha, color);
		}
	}
}

float GetAmountOfPlayerVisible(Vector vecSrc, CBaseEntity *pEntity)
{
	float retval = 0.0f;
	TraceResult tr;

	const float topOfHead = 25.0f;
	const float standFeet = 34.0f;
	const float crouchFeet = 14.0f;
	const float edgeOffset = 13.0f;

	const float damagePercentageChest = 0.40f;
	const float damagePercentageHead = 0.20f;
	const float damagePercentageFeet = 0.20f;
	const float damagePercentageRightSide = 0.10f;
	const float damagePercentageLeftSide = 0.10f;

	if (!pEntity->IsPlayer())
	{
		// the entity is not a player, so the damage is all or nothing.
		UTIL_TraceLine(vecSrc, pEntity->pev->origin, ignore_monsters, nullptr, &tr);

		if (tr.flFraction == 1.0f)
			retval = 1.0f;

		return retval;
	}

	// check chest
	Vector vecChest = pEntity->pev->origin;
	UTIL_TraceLine(vecSrc, vecChest, ignore_monsters, nullptr, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageChest;

	// check top of head
	Vector vecHead = pEntity->pev->origin + Vector(0, 0, topOfHead);
	UTIL_TraceLine(vecSrc, vecHead, ignore_monsters, nullptr, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageHead;

	// check feet
	Vector vecFeet = pEntity->pev->origin;
	vecFeet.z -= (pEntity->pev->flags & FL_DUCKING) ? crouchFeet : standFeet;

	UTIL_TraceLine(vecSrc, vecFeet, ignore_monsters, nullptr, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageFeet;

	Vector2D dir = (pEntity->pev->origin - vecSrc).Make2D();
	dir.NormalizeInPlace();

	Vector2D perp(-dir.y * edgeOffset, dir.x * edgeOffset);
	Vector vecRightSide = pEntity->pev->origin + Vector(perp.x, perp.y, 0);
	Vector vecLeftSide = pEntity->pev->origin - Vector(perp.x, perp.y, 0);

	// check right "edge"
	UTIL_TraceLine(vecSrc, vecRightSide, ignore_monsters, nullptr, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageRightSide;

	// check left "edge"
	UTIL_TraceLine(vecSrc, vecLeftSide, ignore_monsters, nullptr, &tr);

	if (tr.flFraction == 1.0f)
		retval += damagePercentageLeftSide;

	return retval;
}

void RadiusDamage(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
	CBaseEntity *pEntity = nullptr;
	TraceResult tr;
	float flAdjustedDamage, falloff;
	Vector vecSpot;

	if (flRadius)
		falloff = flDamage / flRadius;
	else
		falloff = 1.0;

	int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

	// in case grenade is lying on the ground
	vecSrc.z += 1;

	if (!pevAttacker)
		pevAttacker = pevInflictor;

	// iterate on all entities in the vicinity.
	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flRadius)))
	{
		if (pEntity->pev->takedamage != DAMAGE_NO)
		{
			// UNDONE: this should check a damage mask, not an ignore
			if (iClassIgnore != CLASS_NONE && pEntity->Classify() == iClassIgnore)
				continue;

			// blast's don't tavel into or out of water
			if (bInWater && pEntity->pev->waterlevel == 0)
				continue;

			if (!bInWater && pEntity->pev->waterlevel == 3)
				continue;

			bool useLOS = false;
			float damageRatio = 1.0f;

			if ((bitsDamageType & DMG_EXPLOSION) && AreRunningCZero())
			{
				useLOS = true;
				damageRatio = GetAmountOfPlayerVisible(vecSrc, pEntity);
			}

			damageRatio = GetAmountOfPlayerVisible(vecSrc, pEntity);

			float length;
#ifdef REGAMEDLL_ADD
			// allow to damage breakable objects
			if (FClassnameIs(pEntity->pev, "func_breakable"))
				length = (vecSrc - pEntity->Center()).Length();
			else
#endif
				length = (vecSrc - pEntity->pev->origin).Length();

			if (useLOS)
			{
				if (!flRadius)
					flRadius = flDamage;

				if (!flDamage)
					flRadius = 0;

				flAdjustedDamage = (flRadius - length) * (flRadius - length) * 1.25 / (flRadius * flRadius) * (damageRatio * flDamage) * 1.5;
			}
			else
			{
				flAdjustedDamage = flDamage - length * falloff;
#ifdef REGAMEDLL_ADD
				// disable grenade damage through walls?
				if (hegrenade_penetration.string[0] == '1' && (bitsDamageType & DMG_EXPLOSION))
				{
					UTIL_TraceLine(vecSrc, pEntity->pev->origin, ignore_monsters, nullptr, &tr);

					if (tr.flFraction != 1.0f)
						flAdjustedDamage = 0.0f;
				}
#endif
			}

#ifdef REGAMEDLL_FIXES
			// not allow inflict to the player damage is less than 1.0f and to entities not less than 0.0f
			if ((pEntity->Classify() == CLASS_PLAYER && flAdjustedDamage < 1.0f) || flAdjustedDamage <= 0.0f)
				continue;
#else
			if (flAdjustedDamage < 0)
				flAdjustedDamage = 0;
#endif
			pEntity->TakeDamage(pevInflictor, pevAttacker, flAdjustedDamage, bitsDamageType);
		}
	}
}

void RadiusDamage2(Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType)
{
	CBaseEntity *pEntity = nullptr;
	TraceResult tr;
	float flAdjustedDamage, falloff;
	Vector vecSpot;

	if (flRadius)
		falloff = flDamage / flRadius;
	else
		falloff = 1.0;

	int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

	// in case grenade is lying on the ground
	vecSrc.z += 1;

	if (!pevAttacker)
		pevAttacker = pevInflictor;

	// iterate on all entities in the vicinity.
	while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flRadius)))
	{
		if (pEntity->pev->takedamage != DAMAGE_NO)
		{
			// UNDONE: this should check a damage mask, not an ignore
			if (iClassIgnore != CLASS_NONE && pEntity->Classify() == iClassIgnore)
				continue;

			// blast's don't tavel into or out of water
			if (bInWater && pEntity->pev->waterlevel == 0)
				continue;

			if (!bInWater && pEntity->pev->waterlevel == 3)
				continue;

			vecSpot = pEntity->BodyTarget(vecSrc);
			UTIL_TraceLine(vecSrc, vecSpot, dont_ignore_monsters, ENT(pevInflictor), &tr);

			if (tr.flFraction == 1.0f || tr.pHit == pEntity->edict())
			{
				if (tr.fStartSolid)
				{
					tr.vecEndPos = vecSrc;
					tr.flFraction = 0;
				}

				flAdjustedDamage = flDamage - (vecSrc - pEntity->pev->origin).Length() * falloff;

				if (flAdjustedDamage < 0)
					flAdjustedDamage = 0;

				else if (flAdjustedDamage > 75)
					flAdjustedDamage = 75;

				if (tr.flFraction == 1.0f)
					pEntity->TakeDamage(pevInflictor, pevAttacker, flAdjustedDamage, bitsDamageType);

				else
				{
					ClearMultiDamage();
					pEntity->TraceAttack(pevInflictor, flAdjustedDamage, (tr.vecEndPos - vecSrc).Normalize(), &tr, bitsDamageType);
					ApplyMultiDamage(pevInflictor, pevAttacker);
				}
			}
		}
	}
}
