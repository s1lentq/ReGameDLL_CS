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

#define IMPL(var)\
	var

#define IMPL_CLASS(baseClass,var)\
	baseClass::var

#endif

#define IMPLEMENT_SAVERESTORE(derivedClass, baseClass)\
	int derivedClass::__MAKE_VHOOK(Save)(CSave &save)\
	{\
		if (!baseClass::Save(save))\
			return 0;\
		return save.WriteFields(#derivedClass, this, IMPL(m_SaveData), ARRAYSIZE(IMPL(m_SaveData)));\
	}\
	int derivedClass::__MAKE_VHOOK(Restore)(CRestore &restore)\
	{\
		if (!baseClass::Restore(restore))\
			return 0;\
		return restore.ReadFields(#derivedClass, this, IMPL(m_SaveData), ARRAYSIZE(IMPL(m_SaveData)));\
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

typedef struct
{
	unsigned short size;
	unsigned short token;
	char *pData;

} HEADER;

class CBaseEntity;

class CSaveRestoreBuffer
{
public:
	CSaveRestoreBuffer();
	CSaveRestoreBuffer(SAVERESTOREDATA *pdata);
	~CSaveRestoreBuffer();

	int EntityIndex(entvars_t *pevLookup);
	int EntityIndex(edict_t *pentLookup);
	int EntityIndex(EOFFSET eoLookup);
	int EntityIndex(CBaseEntity *pEntity);
	int EntityFlags(int entityIndex, int flags = 0) { return EntityFlagsSet(entityIndex, flags); }
	int EntityFlagsSet(int entityIndex, int flags);
	edict_t *EntityFromIndex(int entityIndex);
	unsigned short TokenHash(const char *pszToken);

protected:
	SAVERESTOREDATA *m_pdata;
	void BufferRewind(int size);
	unsigned int HashString(const char *pszToken);
};

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
#endif

	int DataEmpty(const char *pdata, int size);
	void BufferField(const char *pname, int size, const char *pdata);
	void BufferString(char *pdata, int len);
	void BufferData(const char *pdata, int size);
	void BufferHeader(const char *pname, int size);
};

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
	int ReadInt();
	short ReadShort();
	int ReadNamedInt(const char *pName);
	char *ReadNamedString(const char *pName);

	int Empty() const { return (m_pdata == NULL || ((m_pdata->pCurrentData - m_pdata->pBaseData) >= m_pdata->bufferSize)); }
	void SetGlobalMode(int global) { m_global = global; }
	void PrecacheMode(BOOL mode) { m_precache = mode; }

private:
	char *BufferPointer();
	void BufferReadBytes(char *pOutput, int size);
	void BufferSkipBytes(int bytes);
	int BufferSkipZString();
	int BufferCheckZString(const char *string);
	void BufferReadHeader(HEADER *pheader);

private:
	int m_global;
	BOOL m_precache;
};

class CGlobalState
{
public:
	CGlobalState();

	void Reset();
	void ClearStates();
	void EntityAdd(string_t globalname, string_t mapName, GLOBALESTATE state);
	void EntitySetState(string_t globalname, GLOBALESTATE state);
	void EntityUpdate(string_t globalname, string_t mapname);
	const globalentity_t *EntityFromTable(string_t globalname);
	GLOBALESTATE EntityGetState(string_t globalname);

	int EntityInTable(string_t globalname) { return (Find(globalname) != NULL) ? TRUE : FALSE; }
	int Save(CSave &save);
	int Restore(CRestore &restore);
	void DumpGlobals();

	static TYPEDESCRIPTION IMPL(m_SaveData)[1];

private:
	globalentity_t *Find(string_t globalname);

	globalentity_t *m_pList;
	int m_listCount;
};

#endif // SAVERESTORE_H
