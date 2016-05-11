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
#pragma once

#define SF_BEAM_STARTON			0x0001
#define SF_BEAM_TOGGLE			0x0002
#define SF_BEAM_RANDOM			0x0004
#define SF_BEAM_RING			0x0008
#define SF_BEAM_SPARKSTART		0x0010
#define SF_BEAM_SPARKEND		0x0020
#define SF_BEAM_DECALS			0x0040
#define SF_BEAM_SHADEIN			0x0080
#define SF_BEAM_SHADEOUT		0x0100
#define SF_BEAM_TEMPORARY		0x8000

#define SF_GIBSHOOTER_REPEATABLE	1
#define SF_FUNNEL_REVERSE		1

#define SF_BUBBLES_STARTOFF		0x0001

#define SF_BLOOD_RANDOM			0x0001
#define SF_BLOOD_STREAM			0x0002
#define SF_BLOOD_PLAYER			0x0004
#define SF_BLOOD_DECAL			0x0008

#define SF_SHAKE_EVERYONE		0x0001
#define SF_SHAKE_DISRUPT		0x0002
#define SF_SHAKE_INAIR			0x0004

#define SF_FADE_IN			0x0001
#define SF_FADE_MODULATE		0x0002
#define SF_FADE_ONLYONE			0x0004

#define SF_SPRITE_STARTON		0x0001
#define SF_SPRITE_ONCE			0x0002
#define SF_SPRITE_TEMPORARY		0x8000

#define SF_MESSAGE_ONCE			0x0001	// Fade in, not out
#define SF_MESSAGE_ALL			0x0002	// Send to all clients

class CSprite: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Restart() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;

public:
	void SetAttachment(edict_t *pEntity, int attachment)
	{
		if (pEntity != NULL)
		{
			pev->skin = ENTINDEX(pEntity);
			pev->body = attachment;
			pev->aiment = pEntity;
			pev->movetype = MOVETYPE_FOLLOW;
		}
	}

	float Frames() const { return m_maxFrame; }
	void SetTransparency(int rendermode, int r, int g, int b, int a, int fx)
	{
		pev->rendermode = rendermode;
		pev->rendercolor.x = r;
		pev->rendercolor.y = g;
		pev->rendercolor.z = b;
		pev->renderamt = a;
		pev->renderfx = fx;
	}

	void SetTexture(int spriteIndex) { pev->modelindex = spriteIndex; }
	void SetScale(float scale) { pev->scale = scale; }
	void SetColor(int r, int g, int b) { pev->rendercolor.x = r; pev->rendercolor.y = g; pev->rendercolor.z = b; }
	void SetBrightness(int brightness) { pev->renderamt = brightness; }
	void AnimateAndDie(float framerate)
	{
		SetThink(&CSprite::AnimateUntilDead);
		pev->framerate = framerate;
		pev->dmgtime = gpGlobals->time + (m_maxFrame / framerate);
		pev->nextthink = gpGlobals->time;
	}
private:
	float m_lastTime;
	float m_maxFrame;
};

class CBeam: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual int ObjectCaps() = 0;
	virtual Vector Center() = 0;
public:
	void SetType(int type) { pev->rendermode = (pev->rendermode & 0xF0) | (type & 0x0F); }
	void SetFlags(int flags) { pev->rendermode = (pev->rendermode & 0x0F) | (flags & 0xF0); }
	void SetStartPos(const Vector &pos) { pev->origin = pos; }
	void SetEndPos(const Vector &pos) { pev->angles = pos; }

	void SetStartEntity(int entityIndex);
	void SetEndEntity(int entityIndex);

	void SetStartAttachment(int attachment) { pev->sequence = (pev->sequence & 0x0FFF) | ((attachment & 0xF) << 12); }
	void SetEndAttachment(int attachment) { pev->skin = (pev->skin & 0x0FFF) | ((attachment & 0xF) << 12); }
	void SetTexture(int spriteIndex) { pev->modelindex = spriteIndex; }
	void SetWidth(int width) { pev->scale = width; }
	void SetNoise(int amplitude) { pev->body = amplitude; }
	void SetColor(int r, int g, int b) { pev->rendercolor.x = r; pev->rendercolor.y = g; pev->rendercolor.z = b; }
	void SetBrightness(int brightness) { pev->renderamt = brightness; }
	void SetFrame(float frame) { pev->frame = frame; }
	void SetScrollRate(int speed) { pev->animtime = speed; }
	int GetType() const { return pev->rendermode & 0x0F; }
	int GetFlags() const { return pev->rendermode & 0xF0; }
	int GetStartEntity() const { return pev->sequence & 0xFFF; }
	int GetEndEntity() const { return pev->skin & 0xFFF; }

	const Vector &GetStartPos();
	const Vector &GetEndPos();

	int GetTexture() const { return pev->modelindex; }
	int GetWidth() const { return pev->scale; }
	int GetNoise() const { return pev->body; }
	int GetBrightness() const { return pev->renderamt; }
	int GetFrame() const { return pev->frame; }
	int GetScrollRate() const { return pev->animtime; }

	void LiveForTime(float time)
	{
		SetThink(&CBeam::SUB_Remove);
		pev->nextthink = gpGlobals->time + time;
	}
	void BeamDamageInstant(TraceResult *ptr, float damage)
	{
		pev->dmg = damage;
		pev->dmgtime = gpGlobals->time - 1;
		BeamDamage(ptr);
	}
};

class CLaser: public CBeam {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	CSprite *m_pSprite;
	int m_iszSpriteName;
	Vector m_firePosition;
};

class CBubbling: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual int ObjectCaps() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_density;
	int m_frequency;
	int m_bubbleModel;
	int m_state;
};

class CLightning: public CBeam {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Activate() = 0;
public:
	inline BOOL ServerSide() const
	{
		if (!m_life && !(pev->spawnflags & SF_BEAM_RING))
			return TRUE;

		return FALSE;
	}
public:
	int m_active;
	int m_iszStartEntity;
	int m_iszEndEntity;
	float m_life;
	int m_boltWidth;
	int m_noiseAmplitude;
	int m_brightness;
	int m_speed;
	float m_restrike;
	int m_spriteTexture;
	int m_iszSpriteName;
	int m_frameStart;
	float m_radius;
};

class CGlow: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Think() = 0;
public:
	float m_lastTime;
	float m_maxFrame;
};

class CBombGlow: public CSprite {
public:
	virtual void Spawn() = 0;
	virtual void Think() = 0;
public:
	float m_lastTime;
	float m_tmBeepPeriod;
	bool m_bSetModel;
};

class CGibShooter: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual int Save(CSave &save) = 0;
	virtual int Restore(CRestore &restore) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
	virtual CGib *CreateGib() = 0;
public:
	int m_iGibs;
	int m_iGibCapacity;
	int m_iGibMaterial;
	int m_iGibModelIndex;

	float m_flGibVelocity;
	float m_flVariance;
	float m_flGibLife;
};

class CEnvShooter: public CGibShooter {
public:
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual CGib *CreateGib() = 0;
};

#define MAX_BEAM 24

class CTestEffect: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_iLoop;
	int m_iBeam;

	CBeam *m_pBeam[MAX_BEAM];

	float m_flBeamTime[MAX_BEAM];
	float m_flStartTime;
};

class CBlood: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;

public:
	int Color() const { return pev->impulse; }
	float BloodAmount() const { return pev->dmg; }

	void SetColor(int color) { pev->impulse = color; }
	void SetBloodAmount(float amount) { pev->dmg = amount; }
};

class CShake: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	float Amplitude() const { return pev->scale; }
	float Frequency() const { return pev->dmg_save; }
	float Duration() const { return pev->dmg_take; }
	float Radius() const { return pev->dmg; }

	void SetAmplitude(float amplitude) { pev->scale = amplitude; }
	void SetFrequency(float frequency) { pev->dmg_save = frequency; }
	void SetDuration(float duration) { pev->dmg_take = duration; }
	void SetRadius(float radius) { pev->dmg = radius; }
};

class CFade: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	float Duration() const { return pev->dmg_take; }
	float HoldTime() const { return pev->dmg_save; }

	void SetDuration(float duration) { pev->dmg_take = duration; }
	void SetHoldTime(float hold) { pev->dmg_save = hold; }
};

class CMessage: public CPointEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void KeyValue(KeyValueData *pkvd) = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class CEnvFunnel: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
public:
	int m_iSprite;
};

class CEnvBeverage: public CBaseDelay {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value) = 0;
};

class CItemSoda: public CBaseEntity {
public:
	virtual void Spawn() = 0;
	virtual void Precache() = 0;
};

// Inlines
inline void CBeam::SetStartEntity(int entityIndex)
{
	pev->sequence = (entityIndex & 0x0FFF) | ((pev->sequence & 0xF000) << 12);
	pev->owner = INDEXENT(entityIndex);
}

inline void CBeam::SetEndEntity(int entityIndex)
{
	pev->skin = (entityIndex & 0x0FFF) | ((pev->skin & 0xF000) << 12);
	pev->aiment = INDEXENT(entityIndex);
}

inline const Vector &CBeam::GetStartPos()
{
	if (GetType() == BEAM_ENTS)
	{
		edict_t *pent = INDEXENT(GetStartEntity());
		return pent->v.origin;
	}

	return pev->origin;
}

inline const Vector &CBeam::GetEndPos()
{
	int type = GetType();
	if (type == BEAM_POINTS || type == BEAM_HOSE)
	{
		return pev->angles;
	}

	edict_t *pent = INDEXENT(GetEndEntity());
	if (pent != NULL)
	{
		return pent->v.origin;
	}

	return pev->angles;
}
