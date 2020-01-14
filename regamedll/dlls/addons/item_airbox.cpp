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
*/

#include "precompiled.h"

LINK_ENTITY_TO_CLASS(item_airbox, CItemAirBox, CCSItemAirBox);

void CItemAirBox::Spawn()
{
	CArmoury::Spawn();

	pev->movetype = MOVETYPE_NOCLIP;

	if (!m_iszSpriteName.IsNull())
	{
		m_hSprite.Remove();

		m_hSprite = CSprite::SpriteCreate(m_iszSpriteName, pev->origin, FALSE);
		m_hSprite->SetTransparency(m_rendermode, m_rendercolor.x, m_rendercolor.y, m_rendercolor.z, m_renderamt, m_renderfx);
		m_hSprite->SetScale(m_scale);
		m_hSprite->SetAttachment(edict(), pev->body);
		m_hSprite->pev->spawnflags |= SF_SPRITE_STARTON;

		m_hSprite->pev->framerate = m_frameRate;
		m_hSprite->TurnOn();
	}

	if (m_flyup > 0 && m_delay > 0.01f)
	{
		SetThink(&CItemAirBox::MoveUp);
		pev->nextthink = gpGlobals->time + 1.0f;
	}
}

void CItemAirBox::OnDestroy()
{
	m_hSprite.Remove();
}

void CItemAirBox::Touch(CBaseEntity *pOther)
{
	CArmoury::Touch(pOther);

	// airbox was picked up, so sprite to turn off
	if ((pev->effects & EF_NODRAW) == EF_NODRAW) 
	{
		m_hSprite->TurnOff();

		pev->nextthink = 0;
		SetThink(nullptr);
	}
}

void CItemAirBox::Restart()
{
	CArmoury::Restart();
	UTIL_SetOrigin(pev, pev->oldorigin);

	if (m_flyup > 0 && m_delay > 0.01f)
	{
		SetThink(&CItemAirBox::MoveUp);
		pev->nextthink = gpGlobals->time + 0.1f;
	}
}

void CItemAirBox::Precache()
{
	CArmoury::Precache();

	if (!m_iszSpriteName.IsNull()) {
		PRECACHE_MODEL(m_iszSpriteName);
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
