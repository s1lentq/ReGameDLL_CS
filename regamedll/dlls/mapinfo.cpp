#include "precompiled.h"

CMapInfo *g_pMapInfo = nullptr;

void CMapInfo::OnCreate()
{
	m_flBombRadius = 500.0f;
	m_iBuyingStatus = BUYING_EVERYONE;

#ifdef REGAMEDLL_ADD
	if (g_pMapInfo)
	{
		// Should only be one of these.
		ALERT(at_warning, "Warning: Multiple info_map_parameters entities in map!\n");
	}
	else
#endif
	{
		g_pMapInfo = this;
	}
}

void CMapInfo::OnDestroy()
{
	g_pMapInfo = nullptr;
}

void CMapInfo::CheckMapInfo()
{
	bool bCTCantBuy, bTCantBuy;
	switch (m_iBuyingStatus)
	{
	case BUYING_EVERYONE:
		bCTCantBuy = false;
		bTCantBuy = false;

		ALERT(at_console, "EVERYONE CAN BUY!\n");
		break;
	case BUYING_ONLY_CTS:
		bCTCantBuy = false;
		bTCantBuy = true;

		ALERT(at_console, "Only CT's can buy!!\n");
		break;
	case BUYING_ONLY_TERRORISTS:
		bCTCantBuy = true;
		bTCantBuy = false;

		ALERT(at_console, "Only T's can buy!!\n");
		break;
	case BUYING_NO_ONE:
		bCTCantBuy = true;
		bTCantBuy = true;

		ALERT(at_console, "No one can buy!!\n");
		break;
	default:
		bCTCantBuy = false;
		bTCantBuy = false;
		break;
	}

	CSGameRules()->m_flBombRadius = m_flBombRadius;
	CSGameRules()->m_bCTCantBuy = bCTCantBuy;
	CSGameRules()->m_bTCantBuy = bTCantBuy;
}

void CMapInfo::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "buying"))
	{
		m_iBuyingStatus = (InfoMapBuyParam)Q_atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "bombradius"))
	{
		m_flBombRadius = (float)Q_atoi(pkvd->szValue);

		if (m_flBombRadius > MAX_BOMB_RADIUS)
			m_flBombRadius = MAX_BOMB_RADIUS;

		pkvd->fHandled = TRUE;
	}
}

void CMapInfo::Spawn()
{
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_NOT;
	pev->effects |= EF_NODRAW;
}

LINK_ENTITY_TO_CLASS(info_map_parameters, CMapInfo, CCSMapInfo)
