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

#ifndef EFFECTS_H
#define EFFECTS_H
#ifdef _WIN32
#pragma once
#endif

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

/* <7249d> ../cstrike/dlls/effects.h:33 */
class CSprite: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Restart(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Restart_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		int flags = 0;
		if (pev->spawnflags & SF_SPRITE_TEMPORARY)
			flags = FCAP_DONT_SAVE;

		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION)|flags;
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT AnimateThink(void);
	NOBODY void EXPORT ExpandThink(void);

	NOBODY void Animate(float frames);
	NOBODY void Expand(float scaleSpeed, float fadeSpeed);
	NOBODY void SpriteInit(const char *pSpriteName, const Vector &origin);

	void SetAttachment(edict_t *pEntity, int attachment)
	{
		if (pEntity)
		{
			pev->skin = ENTINDEX(pEntity);
			pev->body = attachment;
			pev->aiment = pEntity;
			pev->movetype = MOVETYPE_FOLLOW;
		}
	}
	NOBODY void TurnOff(void);
	NOBODY void TurnOn(void);
	float Frames(void)
	{
		return m_maxFrame;
	}
	void SetTransparency(int rendermode, int r, int g, int b, int a, int fx)
	{
		pev->rendermode = rendermode;
		pev->rendercolor.x = r;
		pev->rendercolor.y = g;
		pev->rendercolor.z = b;
		pev->renderamt = a;
		pev->renderfx = fx;
	}
	void SetTexture(int spriteIndex)
	{
		pev->modelindex = spriteIndex;
	}
	void SetScale(float scale)
	{
		pev->scale = scale;
	}
	void SetColor(int r, int g, int b)
	{
		pev->rendercolor.x = r;
		pev->rendercolor.y = g;
		pev->rendercolor.z = b;
	}
	void SetBrightness(int brightness)
	{
		pev->renderamt = brightness;
	}
	void AnimateAndDie(float framerate)
	{
		SetThink(&CSprite::AnimateUntilDead);
		pev->framerate = framerate;
		pev->dmgtime = gpGlobals->time + (m_maxFrame / framerate);
		pev->nextthink = gpGlobals->time;
	}

	NOBODY void EXPORT AnimateUntilDead(void);
	NOBODY static CSprite *SpriteCreate(const char *pSpriteName, const Vector &origin, BOOL animate);

	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

private:

	float m_lastTime;
	float m_maxFrame;

};/* size: 160, cachelines: 3, members: 4 */

/* <723cb> ../cstrike/dlls/effects.h:105 */
class CBeam: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual Vector Center(void)
	{
		return Center_();
	}

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	int ObjectCaps_(void)
	{
		int flags = 0;
		if (pev->spawnflags & SF_BEAM_TEMPORARY)
			flags = FCAP_DONT_SAVE;

		return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION)|flags;
	}
	Vector Center_(void)
	{
		return (GetStartPos() + GetEndPos()) * 0.5;
	}

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT TriggerTouch(CBaseEntity *pOther);

	void SetType(int type)
	{
		pev->rendermode = (pev->rendermode & 0xF0)|(type & 0x0F);
	}
	void SetFlags(int flags)
	{
		pev->rendermode = (pev->rendermode & 0x0F)|(flags&0xF0);
	}
	void SetStartPos(const Vector &pos)
	{
		pev->origin = pos;
	}
	void SetEndPos(const Vector &pos)
	{
		pev->angles = pos;
	}
	NOBODY void SetStartEntity(int entityIndex);
	NOBODY void SetEndEntity(int entityIndex);
	void SetStartAttachment(int attachment)
	{
		pev->sequence = (pev->sequence & 0x0FFF) | ((attachment & 0xF) << 12);
	}
	void SetEndAttachment(int attachment)
	{
		pev->skin = (pev->skin & 0x0FFF) | ((attachment & 0xF) << 12);
	}
	void SetTexture(int spriteIndex)
	{
		pev->modelindex = spriteIndex;
	}
	void SetWidth(int width)
	{
		pev->scale = width;
	}
	void SetNoise(int amplitude)
	{
		pev->body = amplitude;
	}
	void SetColor(int r, int g, int b)
	{
		pev->rendercolor.x = r;
		pev->rendercolor.y = g;
		pev->rendercolor.z = b;
	}
	void SetBrightness(int brightness)
	{
		pev->renderamt = brightness;
	}
	void SetFrame(float frame)
	{
		pev->frame = frame;
	}
	void SetScrollRate(int speed)
	{
		pev->animtime = speed;
	}
	int GetType(void)
	{
		return pev->rendermode & 0x0F;
	}
	int GetFlags(void)
	{
		return pev->rendermode & 0xF0;
	}
	int GetStartEntity(void)
	{
		return pev->sequence & 0xFFF;
	}
	int GetEndEntity(void)
	{
		return pev->skin & 0xFFF;
	}

	NOBODY const Vector &GetStartPos(void);
	NOBODY const Vector &GetEndPos(void);

	int GetTexture(void)
	{
		return pev->modelindex;
	}
	int GetWidth(void)
	{
		return pev->scale;
	}
	int GetNoise(void)
	{
		return pev->body;
	}
	int GetBrightness(void)
	{
		return pev->renderamt;
	}
	int GetFrame(void)
	{
		return pev->frame;
	}
	int GetScrollRate(void)
	{
		return pev->animtime;
	}

	NOBODY void RelinkBeam(void);
	NOBODY void DoSparks(const Vector &start, const Vector &end);
	NOBODY CBaseEntity *RandomTargetname(const char *szName);
	NOBODY void BeamDamage(TraceResult *ptr);
	NOBODY void BeamInit(const char *pSpriteName, int width);
	NOBODY void PointsInit(const Vector &start, const Vector &end);
	NOBODY void PointEntInit(const Vector &start, int endIndex);
	NOBODY void EntsInit(int startIndex, int endIndex);
	NOBODY void HoseInit(const Vector &start, const Vector &direction);

	NOBODY static CBeam *BeamCreate(const char *pSpriteName, int width);

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

};/* size: 152, cachelines: 3, members: 1 */

/* <72402> ../cstrike/dlls/effects.h:188 */
class CLaser: public CBeam
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void TurnOn(void);
	NOBODY void TurnOff(void);
	NOBODY int IsOn(void);

	NOBODY void FireAtPoint(TraceResult &point);
	NOBODY void EXPORT StrikeThink(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[3];

public:
	CSprite *m_pSprite;
	int m_iszSpriteName;
	Vector m_firePosition;

};/* size: 172, cachelines: 3, members: 5 */

/* <7237e> ../cstrike/dlls/effects.cpp:36 */
class CBubbling: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	int ObjectCaps_(void)
	{
		return CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION;
	}
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	void EXPORT FizzThink(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[3];

public:
	int m_density;
	int m_frequency;
	int m_bubbleModel;
	int m_state;

}; /* size: 168, cachelines: 3, members: 6 */

/* <723e6> ../cstrike/dlls/effects.cpp:357 */
class CLightning: public CBeam
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Activate(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Activate_(void);

#endif // HOOK_GAMEDLL

public:
	void EXPORT StrikeThink(void);
	void EXPORT DamageThink(void);
	void RandomArea(void);
	void RandomPoint(Vector &vecSrc);
	void Zap(const Vector &vecSrc, const Vector &vecDest);
	void EXPORT StrikeUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	void EXPORT ToggleUse(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

	/* <71e17> ../cstrike/dlls/effects.cpp:373 */
	inline BOOL ServerSide(void)
	{
		if (!m_life && !(pev->spawnflags & SF_BEAM_RING))
			return TRUE;

		return FALSE;
	}
	void BeamUpdateVars(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[13];

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

}; /* size: 204, cachelines: 4, members: 15 */

/* <7244f> ../cstrike/dlls/effects.cpp:1085 */
class CGlow: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Think(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Think_(void);

#endif // HOOK_GAMEDLL

	NOBODY void Animate(float frames);
public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

public:
	float m_lastTime;
	float m_maxFrame;

};/* size: 160, cachelines: 3, members: 4 */

/* <724b8> ../cstrike/dlls/effects.cpp:1146 */
class CBombGlow: public CSprite
{
public:
	virtual void Spawn(void);
	virtual void Think(void);

public:
	float m_lastTime;
	float m_tmBeepPeriod;
	bool m_bSetModel;

};/* size: 172, cachelines: 3, members: 4 */

/* <72581> ../cstrike/dlls/effects.cpp:1413 */
class CGibShooter: public CBaseDelay
{
public:
	virtual void Spawn(void);
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	virtual int Save(CSave &save);
	virtual int Restore(CRestore &restore);
	virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	virtual CGib *CreateGib(void);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
	CGib *CreateGib_(void);

#endif // HOOK_GAMEDLL

public:
	void EXPORT ShootThink(void);
public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[7];

public:
	int m_iGibs;
	int m_iGibCapacity;
	int m_iGibMaterial;
	int m_iGibModelIndex;

	float m_flGibVelocity;
	float m_flVariance;
	float m_flGibLife;

};/* size: 188, cachelines: 3, members: 9 */

/* <725ef> ../cstrike/dlls/effects.cpp:1592 */
class CEnvShooter: public CGibShooter
{
public:
	virtual void Precache(void);
	virtual void KeyValue(KeyValueData *pkvd);
	CGib *CreateGib(void);

#ifdef HOOK_GAMEDLL

	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	CGib *CreateGib_(void);

#endif // HOOK_GAMEDLL

};/* size: 188, cachelines: 3, members: 1 */

#define MAX_BEAM 24

/* <7263d> ../cstrike/dlls/effects.cpp:1679 */
class CTestEffect: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
#endif // HOOK_GAMEDLL

public:
	void EXPORT TestThink(void);

public:
	int m_iLoop;
	int m_iBeam;

	CBeam *m_pBeam[ MAX_BEAM ];
	
	float m_flBeamTime[ MAX_BEAM ];
	float m_flStartTime;

};/* size: 364, cachelines: 6, members: 6 */

/* <72690> ../cstrike/dlls/effects.cpp:1769 */
class CBlood: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
#endif // HOOK_GAMEDLL

public:
	/* <7205b> ../cstrike/dlls/effects.cpp:1776 */
	inline int Color(void)
	{
		return pev->impulse;
	}
	/* <72079> ../cstrike/dlls/effects.cpp:1777 */
	inline float BloodAmount(void)
	{
		return pev->dmg;
	}
	/* <72092> ../cstrike/dlls/effects.cpp:1779 */
	inline void SetColor(int color)
	{
		pev->impulse = color;
	}
	/* <720b7> ../cstrike/dlls/effects.cpp:1780 */
	inline void SetBloodAmount(float amount)
	{
		pev->dmg = amount;
	}

public:
	Vector Direction(void);
	Vector BloodPosition(CBaseEntity *pActivator);

};/* size: 152, cachelines: 3, members: 1 */

/* <726de> ../cstrike/dlls/effects.cpp:1886 */
class CShake: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	/* <7210f> ../cstrike/dlls/effects.cpp:1893 */
	inline float Amplitude(void)
	{
		return pev->scale;
	}
	/* <7212d> ../cstrike/dlls/effects.cpp:1894 */
	inline float Frequency(void)
	{
		return pev->dmg_save;
	}
	/* <72146> ../cstrike/dlls/effects.cpp:1895 */
	inline float Duration(void)
	{
		return pev->dmg_take;
	}
	/* <7215f> ../cstrike/dlls/effects.cpp:1896 */
	inline float Radius(void)
	{
		return pev->dmg;
	}
	/* <72178> ../cstrike/dlls/effects.cpp:1898 */
	inline void SetAmplitude(float amplitude)
	{
		pev->scale = amplitude;
	}
	/* <7219d> ../cstrike/dlls/effects.cpp:1899 */
	inline void SetFrequency(float frequency)
	{
		pev->dmg_save = frequency;
	}
	/* <721c2> ../cstrike/dlls/effects.cpp:1900 */
	inline void SetDuration(float duration)
	{
		pev->dmg_take = duration;
	}
	/* <721e7> ../cstrike/dlls/effects.cpp:1901 */
	inline void SetRadius(float radius)
	{
		pev->dmg = radius;
	}

};/* size: 152, cachelines: 3, members: 1 */

/* <7272c> ../cstrike/dlls/effects.cpp:1964 */
class CFade: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
#endif // HOOK_GAMEDLL

public:
	/* <72231> ../cstrike/dlls/effects.cpp:1971 */
	inline float Duration(void)
	{
		return pev->dmg_take;
	}
	/* <7224f> ../cstrike/dlls/effects.cpp:1972 */
	inline float HoldTime(void)
	{
		return pev->dmg_save;
	}
	/* <72268> ../cstrike/dlls/effects.cpp:1974 */
	inline void SetDuration(float duration)
	{
		pev->dmg_take = duration;
	}
	/* <7228d> ../cstrike/dlls/effects.cpp:1975 */
	inline void SetHoldTime(float hold)
	{
		pev->dmg_save = hold;
	}

};/* size: 152, cachelines: 3, members: 1 */

/* <7277a> ../cstrike/dlls/effects.cpp:2038 */
class CMessage: public CPointEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
	void KeyValue_(KeyValueData *pkvd);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);
#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <727c8> ../cstrike/dlls/effects.cpp:2145 */
class CEnvFunnel: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	int m_iSprite;

};/* size: 164, cachelines: 3, members: 2 */

/* <7281b> ../cstrike/dlls/effects.cpp:2199 */
class CEnvBeverage: public CBaseDelay
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void Precache_(void);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

};/* size: 160, cachelines: 3, members: 1 */

/* <72869> ../cstrike/dlls/effects.cpp:2258 */
class CItemSoda: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void Precache(void);

#ifdef HOOK_GAMEDLL
	void Spawn_(void);
	void Precache_(void);
#endif // HOOK_GAMEDLL

public:
	void EXPORT CanThink(void);
	void EXPORT CanTouch(CBaseEntity *pOther);

};/* size: 152, cachelines: 3, members: 1 */

NOBODY int IsPointEntity(CBaseEntity *pEnt);

#endif // EFFECTS_H
