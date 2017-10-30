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

#pragma once

class CItemAirBox: public CArmoury {
public:
	void Spawn();
	void Precache();
	void Restart();
	void OnDestroy();
	void Touch(CBaseEntity *pOther);
	void KeyValue(KeyValueData *pkvd);
	int ObjectCaps() { return (CArmoury::ObjectCaps() | FCAP_MUST_RESET); }

protected:
	void EXPORT MoveUp();

private:
	EntityHandle<CSprite> m_hSprite;

	float m_flyup;
	float m_delay;

	Vector m_rendercolor;
	int m_renderfx;
	int m_rendermode;
	float m_renderamt;
	float m_scale;
	float m_frameRate;

	string_t m_iszSpriteName;
};
