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

#ifndef EXPLODE_H
#define EXPLODE_H
#ifdef _WIN32
#pragma once
#endif

#define	SF_ENVEXPLOSION_NODAMAGE	(1<<0)	// when set, ENV_EXPLOSION will not actually inflict damage
#define	SF_ENVEXPLOSION_REPEATABLE	(1<<1)	// can this entity be refired?
#define SF_ENVEXPLOSION_NOFIREBALL	(1<<2)	// don't draw the fireball
#define SF_ENVEXPLOSION_NOSMOKE		(1<<3)	// don't draw the smoke
#define SF_ENVEXPLOSION_NODECAL		(1<<4)	// don't make a scorch mark
#define SF_ENVEXPLOSION_NOSPARKS	(1<<5)	// don't make a scorch mark

/* <7e4a8> ../cstrike/dlls/explode.cpp:29 */
class CShower: public CBaseEntity
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual int ObjectCaps(void)
	{
		return ObjectCaps_();
	}
	NOBODY virtual void Think(void);
	NOBODY virtual void Touch(CBaseEntity *pOther);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	int ObjectCaps_(void)
	{
		return FCAP_DONT_SAVE;
	}
	void Think_(void);
	void Touch_(CBaseEntity *pOther);

#endif // HOOK_GAMEDLL

};/* size: 152, cachelines: 3, members: 1 */

/* <7e66b> ../cstrike/dlls/explode.cpp:84 */
class CEnvExplosion: public CBaseMonster
{
public:
	NOBODY virtual void Spawn(void);
	NOBODY virtual void KeyValue(KeyValueData *pkvd);
	NOBODY virtual int Save(CSave &save);
	NOBODY virtual int Restore(CRestore &restore);
	NOBODY virtual void Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#ifdef HOOK_GAMEDLL

	void Spawn_(void);
	void KeyValue_(KeyValueData *pkvd);
	int Save_(CSave &save);
	int Restore_(CRestore &restore);
	void Use_(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value);

#endif // HOOK_GAMEDLL

public:
	NOBODY void EXPORT Smoke(void);

public:
	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[2];

public:
	int m_iMagnitude;
	int m_spriteScale;

};/* size: 412, cachelines: 7, members: 4 */

NOBODY void ExplosionCreate(Vector &center, Vector &angles, edict_t *pOwner, int magnitude, BOOL doDamage);

#endif // EXPLODE_H
