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

LINK_ENTITY_TO_CLASS(item_airbox, CItemAirBox, CCSItemAirBox);

void CItemAirBox::Spawn()
{
	CArmoury::Spawn();

	pev->movetype = MOVETYPE_NOCLIP;

	if (!FStringNull(m_iszSpriteName))
	{
		m_pSprite = CSprite::SpriteCreate(STRING(m_iszSpriteName), pev->origin, FALSE);
		m_pSprite->SetTransparency(m_rendermode, m_rendercolor.x, m_rendercolor.y, m_rendercolor.z, m_renderamt, m_renderfx);
		m_pSprite->SetScale(m_scale);
		m_pSprite->SetAttachment(edict(), pev->body);
		m_pSprite->pev->spawnflags |= SF_SPRITE_STARTON;

		m_pSprite->pev->framerate = m_frameRate;
		m_pSprite->TurnOn();
	}

	if (m_flyup > 0 && m_delay > 0.01)
	{
		SetThink(&CItemAirBox::MoveUp);
		pev->nextthink = gpGlobals->time + 1.0f;
	}
}

void CItemAirBox::Touch(CBaseEntity *pOther)
{
	CArmoury::Touch(pOther);

	// airbox was picked up, so sprite to turn off
	if ((pev->effects & EF_NODRAW) == EF_NODRAW) {
		m_pSprite->TurnOff();
	}
}

void CItemAirBox::Restart()
{
	CArmoury::Restart();
	UTIL_SetOrigin(pev, pev->oldorigin);
}

void CItemAirBox::Precache()
{
	CArmoury::Precache();

	if (!FStringNull(m_iszSpriteName)) {
		PRECACHE_MODEL(STRING(m_iszSpriteName));
	}
}

void CItemAirBox::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "flyup"))
	{
		m_flyup = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "delay"))
	{
		m_delay = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_model"))
	{
		m_iszSpriteName = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_renderfx"))
	{
		m_renderfx = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_rendermode"))
	{
		m_rendermode = Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_renderamt"))
	{
		m_renderamt = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_rendercolor"))
	{
		UTIL_StringToVector(m_rendercolor, pkvd->szValue, ' ');
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_scale"))
	{
		m_scale = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "sprite_framerate"))
	{
		m_frameRate = Q_atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
	{
		CArmoury::KeyValue(pkvd);
	}
}

void CItemAirBox::MoveUp()
{
	pev->velocity.z = m_flyup;
	m_flyup = -m_flyup;
	pev->nextthink = gpGlobals->time + m_delay;
}

void CItemAirBox::OnDestroy()
{
	if (m_pSprite)
	{
		m_pSprite->SetTouch(nullptr);
		m_pSprite->SetThink(&CBaseEntity::SUB_Remove);
		m_pSprite->pev->nextthink = gpGlobals->time + 0.1f;
		m_pSprite = nullptr;
	}
}
