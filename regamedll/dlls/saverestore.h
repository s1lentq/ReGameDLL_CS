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

#ifndef SAVERESTORE_H
#define SAVERESTORE_H
#ifdef _WIN32
#pragma once
#endif

#define MAX_ENTITY_ARRAY	64

#ifndef HOOK_GAMEDLL

#define IMPLEMENT_ARRAY(var)\
	var

#define IMPLEMENT_ARRAY_CLASS(baseClass,var)\
	baseClass::var

#else // HOOK_GAMEDLL

#define IMPLEMENT_ARRAY(var)\
	(*p##var)

#define IMPLEMENT_ARRAY_CLASS(baseClass,var)\
	(*baseClass::p##var)

#endif // HOOK_GAMEDLL

#define IMPLEMENT_SAVERESTORE(derivedClass, baseClass)\
	int derivedClass::Save_(CSave &save)\
	{\
		if (!baseClass::Save(save))\
			return 0;\
		return save.WriteFields(#derivedClass, this, IMPLEMENT_ARRAY(m_SaveData), ARRAYSIZE(IMPLEMENT_ARRAY(m_SaveData)));\
	}\
	int derivedClass::Restore_(CRestore &restore)\
	{\
		if (!baseClass::Restore(restore))\
			return 0;\
		return restore.ReadFields(#derivedClass, this, IMPLEMENT_ARRAY(m_SaveData), ARRAYSIZE(IMPLEMENT_ARRAY(m_SaveData)));\
	}

typedef enum
{
	GLOBAL_OFF,
	GLOBAL_ON,
	GLOBAL_DEAD

} GLOBALESTATE;

typedef struct globalentity_s
{
	char name[64];
	char levelName[32];
	GLOBALESTATE state;
	struct globalentity_s *pNext;

} globalentity_t;
/* size: 104, cachelines: 2, members: 4 */

typedef struct
{
	unsigned short size;
	unsigned short token;
	char *pData;

} HEADER;
/* size: 8, cachelines: 1, members: 3 */

class CBaseEntity;

/* <39a4f3> ../cstrike/dlls/saverestore.h:33 */
class CSaveRestoreBuffer
{
public:
	CSaveRestoreBuffer(void);
	CSaveRestoreBuffer(SAVERESTOREDATA *pdata);
	~CSaveRestoreBuffer(void);

	int EntityIndex(entvars_t *pevLookup);
	int EntityIndex(edict_t *pentLookup);
	int EntityIndex(EOFFSET eoLookup);
	int EntityIndex(CBaseEntity *pEntity);
	int EntityFlags(int entityIndex, int flags = 0)
	{
		return EntityFlagsSet(entityIndex, flags);
	}
	int EntityFlagsSet(int entityIndex, int flags);
	edict_t *EntityFromIndex(int entityIndex);
	unsigned short TokenHash(const char *pszToken);

protected:

	SAVERESTOREDATA *m_pdata;
	void BufferRewind(int size);
	unsigned int HashString(const char *pszToken);

};/* size: 4, cachelines: 1, members: 1 */

/* <19e94e> ../cstrike/dlls/saverestore.h:50 */
class CSave: public CSaveRestoreBuffer
{
public:
	CSave(SAVERESTOREDATA *pdata) : CSaveRestoreBuffer(pdata) {};

	void WriteShort(const char *pname, const short *value, int count);
	void WriteInt(const char *pname, const int *value, int count);
	void WriteFloat(const char *pname, const float *value, int count);
	void WriteTime(const char *pname, const float *value, int count);
	void WriteData(const char *pname, int size, const char *pdata);
	void WriteString(const char *pname, const char *pstring);
	void WriteString(const char *pname, const int *stringId, int count);
	void WriteVector(const char *pname, const Vector &value);
	void WriteVector(const char *pname, const float *value, int count);
	void WritePositionVector(const char *pname, const Vector &value);
	void WritePositionVector(const char *pname, const float *value, int count);
	void WriteFunction(const char *pname, void **data, int count);
	int WriteEntVars(const char *pname, entvars_t *pev);
	int WriteFields(const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
private:

#ifdef HOOK_GAMEDLL
public:
#endif // HOOK_GAMEDLL

	int DataEmpty(const char *pdata, int size);
	void BufferField(const char *pname, int size, const char *pdata);
	void BufferString(char *pdata, int len);
	void BufferData(const char *pdata, int size);
	void BufferHeader(const char *pname, int size);

};/* size: 4, cachelines: 1, members: 1 */

/* <1d9f06> ../cstrike/dlls/saverestore.h:82 */
class CRestore: public CSaveRestoreBuffer
{
public:
	CRestore(SAVERESTOREDATA *pdata) : CSaveRestoreBuffer(pdata)
	{
		m_global = 0;
		m_precache = TRUE;
	}
	int ReadEntVars(const char *pname, entvars_t *pev);
	int ReadFields(const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
	int ReadField(void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount, int startField, int size, char *pName, void *pData);
	int ReadInt(void);
	short ReadShort(void);
	int ReadNamedInt(const char *pName);
	char *ReadNamedString(const char *pName);
	inline int Empty(void)
	{
		return (m_pdata == NULL || ((m_pdata->pCurrentData - m_pdata->pBaseData) >= m_pdata->bufferSize));
	}
	inline void SetGlobalMode(int global)
	{
		m_global = global;
	}
	inline void PrecacheMode(BOOL mode)
	{
		m_precache = mode;
	}

#ifdef HOOK_GAMEDLL
public:
#else
private:
#endif // HOOK_GAMEDLL

	char *BufferPointer(void);
	void BufferReadBytes(char *pOutput, int size);
	void BufferSkipBytes(int bytes);
	int BufferSkipZString(void);
	int BufferCheckZString(const char *string);
	void BufferReadHeader(HEADER *pheader);

private:
	int m_global;
	BOOL m_precache;

};/* size: 12, cachelines: 1, members: 3 */

/* <245f6> ../cstrike/dlls/saverestore.h:153 */
class CGlobalState
{
public:
	CGlobalState(void);

	void Reset(void);
	void ClearStates(void);
	void EntityAdd(string_t globalname, string_t mapName, GLOBALESTATE state);
	void EntitySetState(string_t globalname, GLOBALESTATE state);
	void EntityUpdate(string_t globalname, string_t mapname);
	const globalentity_t *EntityFromTable(string_t globalname);
	GLOBALESTATE EntityGetState(string_t globalname);
	int EntityInTable(string_t globalname)
	{
		if (Find(globalname) != NULL)
			return 1;
		return 0;
	}
	int Save(CSave &save);
	int Restore(CRestore &restore);
	void DumpGlobals(void);

	static TYPEDESCRIPTION IMPLEMENT_ARRAY(m_SaveData)[1];

#ifdef HOOK_GAMEDLL
public:
#else
private:
#endif // HOOK_GAMEDLL
	globalentity_t *Find(string_t globalname);

private:
	globalentity_t *m_pList;
	int m_listCount;

};/* size: 8, cachelines: 1, members: 3 */

#endif // SAVERESTORE_H
