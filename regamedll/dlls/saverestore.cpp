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

TYPEDESCRIPTION g_EntvarsDescription[] =
{
	DEFINE_ENTITY_FIELD(classname, FIELD_STRING),
	DEFINE_ENTITY_GLOBAL_FIELD(globalname, FIELD_STRING),
	DEFINE_ENTITY_FIELD(origin, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_FIELD(oldorigin, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_FIELD(velocity, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(basevelocity, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(movedir, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(angles, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(avelocity, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(punchangle, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(v_angle, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(fixangle, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(idealpitch, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(pitch_speed, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(ideal_yaw, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(yaw_speed, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(modelindex, FIELD_INTEGER),
	DEFINE_ENTITY_GLOBAL_FIELD(model, FIELD_MODELNAME),
	DEFINE_ENTITY_FIELD(viewmodel, FIELD_MODELNAME),
	DEFINE_ENTITY_FIELD(weaponmodel, FIELD_MODELNAME),
	DEFINE_ENTITY_FIELD(absmin, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_FIELD(absmax, FIELD_POSITION_VECTOR),
	DEFINE_ENTITY_GLOBAL_FIELD(mins, FIELD_VECTOR),
	DEFINE_ENTITY_GLOBAL_FIELD(maxs, FIELD_VECTOR),
	DEFINE_ENTITY_GLOBAL_FIELD(size, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(ltime, FIELD_TIME),
	DEFINE_ENTITY_FIELD(nextthink, FIELD_TIME),
	DEFINE_ENTITY_FIELD(solid, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(movetype, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(skin, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(body, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(effects, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(gravity, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(friction, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(light_level, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(frame, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(scale, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(sequence, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(animtime, FIELD_TIME),
	DEFINE_ENTITY_FIELD(framerate, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(controller, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(blending, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(rendermode, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(renderamt, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(rendercolor, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(renderfx, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(health, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(frags, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(weapons, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(takedamage, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(deadflag, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(view_ofs, FIELD_VECTOR),
	DEFINE_ENTITY_FIELD(button, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(impulse, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(chain, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(dmg_inflictor, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(enemy, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(aiment, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(owner, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(groundentity, FIELD_EDICT),
	DEFINE_ENTITY_FIELD(spawnflags, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(flags, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(colormap, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(team, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(max_health, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(teleport_time, FIELD_TIME),
	DEFINE_ENTITY_FIELD(armortype, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(armorvalue, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(waterlevel, FIELD_INTEGER),
	DEFINE_ENTITY_FIELD(watertype, FIELD_INTEGER),
	DEFINE_ENTITY_GLOBAL_FIELD(target, FIELD_STRING),
	DEFINE_ENTITY_GLOBAL_FIELD(targetname, FIELD_STRING),
	DEFINE_ENTITY_FIELD(netname, FIELD_STRING),
	DEFINE_ENTITY_FIELD(message, FIELD_STRING),
	DEFINE_ENTITY_FIELD(dmg_take, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(dmg_save, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(dmg, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(dmgtime, FIELD_TIME),
	DEFINE_ENTITY_FIELD(noise, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(noise1, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(noise2, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(noise3, FIELD_SOUNDNAME),
	DEFINE_ENTITY_FIELD(speed, FIELD_FLOAT),
	DEFINE_ENTITY_FIELD(air_finished, FIELD_TIME),
	DEFINE_ENTITY_FIELD(pain_finished, FIELD_TIME),
	DEFINE_ENTITY_FIELD(radsuit_finished, FIELD_TIME),
};

void EntvarsKeyvalue(entvars_t *pev, KeyValueData *pkvd)
{
	for (int i = 0; i < ARRAYSIZE(g_EntvarsDescription); i++)
	{
		TYPEDESCRIPTION *pField = &g_EntvarsDescription[i];

		if (!Q_stricmp(pField->fieldName, pkvd->szKeyName))
		{
			switch (pField->fieldType)
			{
			case FIELD_STRING:
			case FIELD_MODELNAME:
			case FIELD_SOUNDNAME:
				*(string_t *)((char *)pev + pField->fieldOffset) = ALLOC_STRING(pkvd->szValue);
				break;
			case FIELD_FLOAT:
			case FIELD_TIME:
				*(float *)((char *)pev + pField->fieldOffset) = Q_atof(pkvd->szValue);
				break;
			case FIELD_INTEGER:
				*(string_t *)((char *)pev + pField->fieldOffset) = Q_atoi(pkvd->szValue);
				break;
			case FIELD_VECTOR:
			case FIELD_POSITION_VECTOR:
				UTIL_StringToVector((float *)((char *)pev + pField->fieldOffset), pkvd->szValue);
				break;

			default:
			case FIELD_EVARS:
			case FIELD_CLASSPTR:
			case FIELD_EDICT:
			case FIELD_ENTITY:
			case FIELD_POINTER:
				ALERT(at_error, "Bad field in entity!!\n");
				break;
			}
			pkvd->fHandled = TRUE;
			break;
		}
	}
}

const int CSaveRestoreBuffer::m_Sizes[] =
{
	sizeof(float),     // FIELD_FLOAT
	sizeof(int),       // FIELD_STRING
	sizeof(int),       // FIELD_ENTITY
	sizeof(int),       // FIELD_CLASSPTR
	sizeof(int),       // FIELD_EHANDLE
	sizeof(int),       // FIELD_entvars_t
	sizeof(int),       // FIELD_EDICT
	sizeof(float) * 3, // FIELD_VECTOR
	sizeof(float) * 3, // FIELD_POSITION_VECTOR
	sizeof(int *),     // FIELD_POINTER
	sizeof(int),       // FIELD_INTEGER
	sizeof(int *),     // FIELD_FUNCTION
	sizeof(int),       // FIELD_BOOLEAN
	sizeof(short),     // FIELD_SHORT
	sizeof(char),      // FIELD_CHARACTER
	sizeof(float),     // FIELD_TIME
	sizeof(int),       // FIELD_MODELNAME
	sizeof(int),       // FIELD_SOUNDNAME
};

CSaveRestoreBuffer::CSaveRestoreBuffer()
{
	m_pData = nullptr;
}

CSaveRestoreBuffer::CSaveRestoreBuffer(SAVERESTOREDATA *pdata)
{
	m_pData = pdata;
}

CSaveRestoreBuffer::~CSaveRestoreBuffer()
{
	;
}

int CSaveRestoreBuffer::EntityIndex(CBaseEntity *pEntity)
{
	if (!pEntity)
		return -1;

	return EntityIndex(pEntity->pev);
}

int CSaveRestoreBuffer::EntityIndex(entvars_t *pevLookup)
{
	if (!pevLookup)
		return -1;

	return EntityIndex(ENT(pevLookup));
}

int CSaveRestoreBuffer::EntityIndex(EOFFSET eoLookup)
{
	return EntityIndex(ENT(eoLookup));
}

int CSaveRestoreBuffer::EntityIndex(edict_t *pentLookup)
{
	if (!m_pData || !pentLookup)
		return -1;

	for (int i = 0; i < m_pData->tableCount; i++)
	{
		ENTITYTABLE *pTable = &m_pData->pTable[i];
		if (pTable->pent == pentLookup)
			return i;
	}

	return -1;
}

edict_t *CSaveRestoreBuffer::EntityFromIndex(int entityIndex)
{
	if (!m_pData || entityIndex < 0)
		return nullptr;

	for (int i = 0; i < m_pData->tableCount; i++)
	{
		ENTITYTABLE *pTable = &m_pData->pTable[i];
		if (pTable->id == entityIndex)
			return pTable->pent;
	}

	return nullptr;
}

int CSaveRestoreBuffer::EntityFlagsSet(int entityIndex, int flags)
{
	if (!m_pData || entityIndex < 0)
		return 0;

	if (!m_pData || entityIndex < 0 || entityIndex > m_pData->tableCount)
		return 0;

	m_pData->pTable[entityIndex].flags |= flags;
	return m_pData->pTable[entityIndex].flags;
}

int CSaveRestoreBuffer::EntityFlags(int entityIndex, int flags)
{
	return EntityFlagsSet(entityIndex, flags);
}

void CSaveRestoreBuffer::BufferRewind(int size)
{
	if (!m_pData)
		return;

	if (m_pData->size < size)
		size = m_pData->size;

	m_pData->pCurrentData -= size;
	m_pData->size -= size;
}

#ifndef _WIN32
extern "C"
{
	inline unsigned _rotr(unsigned val, int shift)
	{
		register unsigned lobit;
		register unsigned num = val;

		shift &= 0x1f;

		while (shift--)
		{
			lobit = num & 1;
			num >>= 1;
			if (lobit)
				num |= 0x80000000;
		}

		return num;
	}
}
#endif // _WIN32

unsigned int CSaveRestoreBuffer::HashString(const char *pszToken)
{
	unsigned int hash = 0;
	while (*pszToken)
		hash = _rotr(hash, 4) ^ *pszToken++;

	return hash;
}

unsigned short CSaveRestoreBuffer::TokenHash(const char *pszToken)
{
	unsigned short hash = (unsigned short)(HashString(pszToken) % (unsigned)m_pData->tokenCount);
	for (int i = 0; i < m_pData->tokenCount; i++)
	{
		int index = hash + i;
		if (index >= m_pData->tokenCount)
			index -= m_pData->tokenCount;

		if (!m_pData->pTokens[index] || !Q_strcmp(pszToken, m_pData->pTokens[index]))
		{
			m_pData->pTokens[index] = (char *)pszToken;
			return index;
		}
	}

	ALERT(at_error, "CSaveRestoreBuffer :: TokenHash() is COMPLETELY FULL!");
	return 0;
}


void CSave::WriteData(const char *pname, int size, const char *pdata)
{
	BufferField(pname, size, pdata);
}

NOXREF void CSave::WriteShort(const char *pname, const short *data, int count)
{
	BufferField(pname, sizeof(short) * count, (const char *)data);
}

void CSave::WriteInt(const char *pname, const int *data, int count)
{
	BufferField(pname, sizeof(int) * count, (const char *)data);
}

void CSave::WriteFloat(const char *pname, const float *data, int count)
{
	BufferField(pname, sizeof(float) * count, (const char *)data);
}

void CSave::WriteTime(const char *pname, const float *data, int count)
{
	BufferHeader(pname, sizeof(float) * count);

	for (int i = 0; i < count; i++)
	{
		float tmp = data[0];
		if (m_pData) {
			tmp -= m_pData->time;
		}

		BufferData((const char *)&tmp, sizeof(float));
		data++;
	}
}

NOXREF void CSave::WriteString(const char *pname, const char *pdata)
{
	BufferField(pname, Q_strlen(pdata) + 1, pdata);
}

void CSave::WriteString(const char *pname, const int *stringId, int count)
{
	int i;
	int size = 0;

	for (i = 0; i < count; i++) {
		size += Q_strlen(STRING(stringId[i])) + 1;
	}

	BufferHeader(pname, size);
	for (i = 0; i < count; i++)
	{
		const char *pString = STRING(stringId[i]);
		BufferData(pString, Q_strlen(pString) + 1);
	}
}

void CSave::WriteVector(const char *pname, const Vector &value)
{
	WriteVector(pname, &value.x, 1);
}

void CSave::WriteVector(const char *pname, const float *value, int count)
{
	BufferHeader(pname, sizeof(float) * 3 * count);
	BufferData((const char *)value, sizeof(float) * 3 * count);
}

NOXREF void CSave::WritePositionVector(const char *pname, const Vector &value)
{
	if (m_pData && m_pData->fUseLandmark)
	{
		Vector tmp = value - m_pData->vecLandmarkOffset;
		WriteVector(pname, tmp);
	}
	WriteVector(pname, value);
}

void CSave::WritePositionVector(const char *pname, const float *value, int count)
{
	BufferHeader(pname, sizeof(float) * 3 * count);
	for (int i = 0; i < count; i++)
	{
		Vector tmp(value[0], value[1], value[2]);
		if (m_pData && m_pData->fUseLandmark) {
			tmp -= m_pData->vecLandmarkOffset;
		}

		BufferData((const char *)&tmp.x, sizeof(float) * 3);
		value += 3;
	}
}

void CSave::WriteFunction(const char *pname, void **data, int count)
{
	const char *functionName = NAME_FOR_FUNCTION((uint32)*data);

	if (functionName)
		BufferField(pname, Q_strlen(functionName) + 1, functionName);
	else
		ALERT(at_error, "Invalid function pointer in entity!");
}

int CSave::WriteEntVars(const char *pname, entvars_t *pev)
{
	return WriteFields(pname, pev, g_EntvarsDescription, ARRAYSIZE(g_EntvarsDescription));
}

int CSave::WriteFields(const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	int i;
	int emptyCount = 0;

	for (i = 0; i < fieldCount; i++)
	{
		void *pOutputData = ((char *)pBaseData + pFields[i].fieldOffset);
		if (DataEmpty((const char *)pOutputData, pFields[i].fieldSize * m_Sizes[pFields[i].fieldType]))
			emptyCount++;
	}

	int entityArray[MAX_ENTITY_ARRAY];
	int actualCount = fieldCount - emptyCount;

	WriteInt(pname, &actualCount, 1);
	for (i = 0; i < fieldCount; i++)
	{
		TYPEDESCRIPTION *pTest = &pFields[i];
		void *pOutputData = ((char *)pBaseData + pTest->fieldOffset);

		if (DataEmpty((const char *)pOutputData, pTest->fieldSize * m_Sizes[pTest->fieldType]))
			continue;

		switch (pTest->fieldType)
		{
		case FIELD_FLOAT:
			WriteFloat(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
			break;

		case FIELD_TIME:
			WriteTime(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
			break;

		case FIELD_MODELNAME:
		case FIELD_SOUNDNAME:
		case FIELD_STRING:
			WriteString(pTest->fieldName, (int *)pOutputData, pTest->fieldSize);
			break;

		case FIELD_CLASSPTR:
		case FIELD_EVARS:
		case FIELD_EDICT:
		case FIELD_ENTITY:
		case FIELD_EHANDLE:
		{
			if (pTest->fieldSize > MAX_ENTITY_ARRAY)
				ALERT(at_error, "Can't save more than %d entities in an array!!!\n", MAX_ENTITY_ARRAY);

			for (int j = 0; j < pTest->fieldSize; j++)
			{
				switch (pTest->fieldType)
				{
				case FIELD_EVARS:
					entityArray[j] = EntityIndex(((entvars_t **)pOutputData)[j]);
					break;
				case FIELD_CLASSPTR:
					entityArray[j] = EntityIndex(((CBaseEntity **)pOutputData)[j]);
					break;
				case FIELD_EDICT:
					entityArray[j] = EntityIndex(((edict_t **)pOutputData)[j]);
					break;
				case FIELD_ENTITY:
					entityArray[j] = EntityIndex(((EOFFSET *)pOutputData)[j]);
					break;
				case FIELD_EHANDLE:
					entityArray[j] = EntityIndex((CBaseEntity *)(((EHANDLE *)pOutputData)[j]));
					break;
				default:
					break;
				}
			}
			WriteInt(pTest->fieldName, entityArray, pTest->fieldSize);
			break;
		}
		case FIELD_POSITION_VECTOR:
			WritePositionVector(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
			break;
		case FIELD_VECTOR:
			WriteVector(pTest->fieldName, (float *)pOutputData, pTest->fieldSize);
			break;
		case FIELD_BOOLEAN:
		case FIELD_INTEGER:
			WriteInt(pTest->fieldName, (int *)pOutputData, pTest->fieldSize);
			break;
		case FIELD_SHORT:
			WriteData(pTest->fieldName, 2 * pTest->fieldSize, ((char *)pOutputData));
			break;
		case FIELD_CHARACTER:
			WriteData(pTest->fieldName, pTest->fieldSize, ((char *)pOutputData));
			break;
		case FIELD_POINTER:
			WriteInt(pTest->fieldName, (int *)(char *)pOutputData, pTest->fieldSize);
			break;
		case FIELD_FUNCTION:
			WriteFunction(pTest->fieldName, &pOutputData, pTest->fieldSize);
			break;
		default:
			ALERT(at_error, "Bad field type\n");
			break;
		}
	}

	return 1;
}

NOXREF void CSave::BufferString(char *pdata, int len)
{
	char c = 0;
	BufferData(pdata, len);
	BufferData(&c, 1);
}

int CSave::DataEmpty(const char *pdata, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (pdata[i])
			return 0;
	}

	return 1;
}

void CSave::BufferField(const char *pname, int size, const char *pdata)
{
	BufferHeader(pname, size);
	BufferData(pdata, size);
}

void CSave::BufferHeader(const char *pname, int size)
{
	short hashvalue = TokenHash(pname);
	if (size > (1 << (sizeof(short) * 8)))
		ALERT(at_error, "CSave :: BufferHeader() size parameter exceeds 'short'!");

	BufferData((const char *)&size, sizeof(short));
	BufferData((const char *)&hashvalue, sizeof(short));
}

void CSave::BufferData(const char *pdata, int size)
{
	if (!m_pData)
		return;

	if (m_pData->size + size > m_pData->bufferSize)
	{
		ALERT(at_error, "Save/Restore overflow!");
		m_pData->size = m_pData->bufferSize;
		return;
	}

	Q_memcpy(m_pData->pCurrentData, pdata, size);
	m_pData->pCurrentData += size;
	m_pData->size += size;
}

int CRestore::ReadField(void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount, int startField, int size, char *pName, void *pData)
{
	float time = 0.0f;
	Vector position(0, 0, 0);

	if (m_pData)
	{
		time = m_pData->time;
		if (m_pData->fUseLandmark) {
			position = m_pData->vecLandmarkOffset;
		}
	}
	for (int i = 0; i < fieldCount; i++)
	{
		int fieldNumber = (i + startField) % fieldCount;
		TYPEDESCRIPTION *pTest = &pFields[fieldNumber];

		if (!Q_stricmp(pTest->fieldName, pName))
		{
			if (!m_global || !(pTest->flags & FTYPEDESC_GLOBAL))
			{
				for (int j = 0; j < pTest->fieldSize; j++)
				{
					void *pOutputData = ((char *)pBaseData + pTest->fieldOffset + (j * m_Sizes[pTest->fieldType]));
					void *pInputData = (char *)pData + j * m_Sizes[pTest->fieldType];

					switch (pTest->fieldType)
					{
					case FIELD_TIME:
					{
						float timeData = *(float *)pInputData;
						timeData += time;
						*((float *)pOutputData) = timeData;
						break;
					}
					case FIELD_FLOAT: *((float *)pOutputData) = *(float *)pInputData; break;
					case FIELD_MODELNAME:
					case FIELD_SOUNDNAME:
					case FIELD_STRING:
					{
						char *pString = (char *)pData;
						for (int stringCount = 0; stringCount < j; stringCount++)
						{
							while (*pString)
								pString++;

							pString++;
						}

						pInputData = pString;
						if (!Q_strlen((char *)pInputData))
							*((int *)pOutputData) = 0;
						else
						{
							int string = ALLOC_STRING((char *)pInputData);
							*((int *)pOutputData) = string;

							if (!FStringNull(string) && m_precache)
							{
								if (pTest->fieldType == FIELD_MODELNAME)
									PRECACHE_MODEL((char *)STRING(string));
								else if (pTest->fieldType == FIELD_SOUNDNAME)
									PRECACHE_SOUND((char *)STRING(string));
							}
						}
						break;
					}
					case FIELD_EVARS:
					{
						int entityIndex = *(int *)pInputData;
						edict_t *pent = EntityFromIndex(entityIndex);

						if (pent)
							*((entvars_t **)pOutputData) = VARS(pent);
						else
							*((entvars_t **)pOutputData) = nullptr;

						break;
					}
					case FIELD_CLASSPTR:
					{
						int entityIndex = *(int *)pInputData;
						edict_t *pent = EntityFromIndex(entityIndex);

						if (pent)
							*((CBaseEntity **)pOutputData) = CBaseEntity::Instance(pent);
						else
							*((CBaseEntity **)pOutputData) = nullptr;

						break;
					}
					case FIELD_EDICT:
					{
						int entityIndex = *(int *)pInputData;
						edict_t *pent = EntityFromIndex(entityIndex);
						*((edict_t **)pOutputData) = pent;
						break;
					}
					case FIELD_EHANDLE:
					{
						pOutputData = (char *)pOutputData + j * (sizeof(EHANDLE) - m_Sizes[pTest->fieldType]);
						int entityIndex = *(int *)pInputData;
						edict_t *pent = EntityFromIndex(entityIndex);

						if (pent)
							*((EHANDLE *)pOutputData) = CBaseEntity::Instance(pent);
						else
							*((EHANDLE *)pOutputData) = nullptr;

						break;
					}
					case FIELD_ENTITY:
					{
						int entityIndex = *(int *)pInputData;
						edict_t *pent = EntityFromIndex(entityIndex);

						if (pent)
							*((EOFFSET *)pOutputData) = OFFSET(pent);
						else
							*((EOFFSET *)pOutputData) = 0;

						break;
					}
					case FIELD_VECTOR:
					{
						((float *)pOutputData)[0] = ((float *)pInputData)[0];
						((float *)pOutputData)[1] = ((float *)pInputData)[1];
						((float *)pOutputData)[2] = ((float *)pInputData)[2];
						break;
					}
					case FIELD_POSITION_VECTOR:
					{
						((float *)pOutputData)[0] = ((float *)pInputData)[0] + position.x;
						((float *)pOutputData)[1] = ((float *)pInputData)[1] + position.y;
						((float *)pOutputData)[2] = ((float *)pInputData)[2] + position.z;
						break;
					}
					case FIELD_BOOLEAN:
					case FIELD_INTEGER:
						*((int *)pOutputData) = *(int *)pInputData;
						break;
					case FIELD_SHORT:
						*((short *)pOutputData) = *(short *)pInputData;
						break;
					case FIELD_CHARACTER:
						*((char *)pOutputData) = *(char *)pInputData;
						break;
					case FIELD_POINTER:
						*((int *)pOutputData) = *(int *)pInputData;
						break;
					case FIELD_FUNCTION:
					{
						if (!Q_strlen((char *)pInputData))
							*((int *)pOutputData) = 0;
						else
							*((int *)pOutputData) = FUNCTION_FROM_NAME((char *)pInputData);

						break;
					}
					default:
						ALERT(at_error, "Bad field type\n");
						break;
					}
				}
			}
			return fieldNumber;
		}
	}
	return -1;
}

int CRestore::ReadEntVars(const char *pname, entvars_t *pev)
{
	return ReadFields(pname, pev, g_EntvarsDescription, ARRAYSIZE(g_EntvarsDescription));
}

int CRestore::ReadFields(const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount)
{
	unsigned short i = ReadShort();
	unsigned short token = ReadShort();

	if (token != TokenHash(pname))
	{
		BufferRewind(2 * sizeof(short));
		return 0;
	}

	int fileCount = ReadInt();
	int lastField = 0;

	for (i = 0; i < fieldCount; i++)
	{
		if (!m_global || !(pFields[i].flags & FTYPEDESC_GLOBAL))
			Q_memset(((char *)pBaseData + pFields[i].fieldOffset), 0, pFields[i].fieldSize * m_Sizes[pFields[i].fieldType]);
	}

	for (i = 0; i < fileCount; i++)
	{
		HEADER header;
		BufferReadHeader(&header);

		lastField = ReadField(pBaseData, pFields, fieldCount, lastField, header.size, m_pData->pTokens[header.token], header.pData);
		lastField++;
	}

	return 1;
}

void CRestore::BufferReadHeader(HEADER *pheader)
{
	pheader->size = ReadShort();
	pheader->token = ReadShort();
	pheader->pData = BufferPointer();

	BufferSkipBytes(pheader->size);
}

short CRestore::ReadShort()
{
	short tmp = 0;
	BufferReadBytes((char *)&tmp, sizeof(short));
	return tmp;
}

int CRestore::ReadInt()
{
	int tmp = 0;
	BufferReadBytes((char *)&tmp, sizeof(int));
	return tmp;
}

NOXREF int CRestore::ReadNamedInt(const char *pName)
{
	HEADER header;
	BufferReadHeader(&header);
	return ((int *)header.pData)[0];
}

NOXREF char *CRestore::ReadNamedString(const char *pName)
{
	HEADER header;
	BufferReadHeader(&header);
	return (char *)header.pData;
}

char *CRestore::BufferPointer()
{
	if (!m_pData)
		return nullptr;

	return m_pData->pCurrentData;
}

void CRestore::BufferReadBytes(char *pOutput, int size)
{
	if (!m_pData || Empty())
		return;

	if ((m_pData->size + size) > m_pData->bufferSize)
	{
		ALERT(at_error, "Restore overflow!");
		m_pData->size = m_pData->bufferSize;
		return;
	}

	if (pOutput)
		Q_memcpy(pOutput, m_pData->pCurrentData, size);

	m_pData->pCurrentData += size;
	m_pData->size += size;
}

void CRestore::BufferSkipBytes(int bytes)
{
	BufferReadBytes(nullptr, bytes);
}

NOXREF int CRestore::BufferSkipZString()
{
	if (!m_pData)
		return 0;

	int maxLen = m_pData->bufferSize - m_pData->size;
	int len = 0;
	char *pszSearch = m_pData->pCurrentData;

	while (*pszSearch++ && len < maxLen)
		len++;

	len++;
	BufferSkipBytes(len);
	return len;
}

NOXREF int CRestore::BufferCheckZString(const char *string)
{
	if (!m_pData)
		return 0;

	int maxLen = m_pData->bufferSize - m_pData->size;
	int len = Q_strlen(string);

	if (len <= maxLen)
	{
		if (!Q_strncmp(string, m_pData->pCurrentData, len))
			return 1;
	}

	return 0;
}

CGlobalState::CGlobalState()
{
	Reset();
}

void CGlobalState::Reset()
{
	m_pList = nullptr;
	m_listCount = 0;
}

globalentity_t *CGlobalState::Find(string_t globalname)
{
	if (!globalname)
		return nullptr;

	globalentity_t *pTest = m_pList;
	const char *pEntityName = STRING(globalname);

	while (pTest)
	{
		if (!Q_strcmp(pEntityName, pTest->name))
			break;

		pTest = pTest->pNext;
	}

	return pTest;
}

// This is available all the time now on impulse 104, remove later
void CGlobalState::DumpGlobals()
{
	static char *estates[] = { "Off", "On", "Dead" };
	globalentity_t *pTest;

	ALERT(at_console, "-- Globals --\n");
	pTest = m_pList;

	while (pTest)
	{
		ALERT(at_console, "%s: %s (%s)\n", pTest->name, pTest->levelName, estates[pTest->state]);
		pTest = pTest->pNext;
	}
}

void CGlobalState::EntityAdd(string_t globalname, string_t mapName, GLOBALESTATE state)
{
	assert(!Find(globalname));

	globalentity_t *pNewEntity = (globalentity_t *)calloc(sizeof(globalentity_t), 1);
	assert(pNewEntity != nullptr);

	pNewEntity->pNext = m_pList;
	m_pList = pNewEntity;
	Q_strcpy(pNewEntity->name, STRING(globalname));
	Q_strcpy(pNewEntity->levelName, STRING(mapName));
	pNewEntity->state = state;

	m_listCount++;
}

void CGlobalState::EntitySetState(string_t globalname, GLOBALESTATE state)
{
	globalentity_t *pEnt = Find(globalname);
	if (pEnt)
	{
		pEnt->state = state;
	}
}

const globalentity_t *CGlobalState::EntityFromTable(string_t globalname)
{
	globalentity_t *pEnt = Find(globalname);

	return pEnt;
}

GLOBALESTATE CGlobalState::EntityGetState(string_t globalname)
{
	globalentity_t *pEnt = Find(globalname);
	if (pEnt)
	{
		return pEnt->state;
	}

	return GLOBAL_OFF;
}

TYPEDESCRIPTION CGlobalState::m_SaveData[] =
{
	DEFINE_FIELD(CGlobalState, m_listCount, FIELD_INTEGER)
};

TYPEDESCRIPTION CGlobalState::m_GlobalEntitySaveData[] =
{
	DEFINE_ARRAY(globalentity_t, name, FIELD_CHARACTER, 64),
	DEFINE_ARRAY(globalentity_t, levelName, FIELD_CHARACTER, MAX_MAPNAME_LENGHT),
	DEFINE_FIELD(globalentity_t, state, FIELD_INTEGER)
};

int CGlobalState::Save(CSave &save)
{
	int i;
	globalentity_t *pEntity;

	if (!save.WriteFields("GLOBAL", this, m_SaveData, ARRAYSIZE(m_SaveData)))
	{
		return 0;
	}

	pEntity = m_pList;
	for (i = 0; i < m_listCount && pEntity; i++)
	{
		if (!save.WriteFields("GENT", pEntity, m_GlobalEntitySaveData, ARRAYSIZE(m_GlobalEntitySaveData)))
		{
			return 0;
		}

		pEntity = pEntity->pNext;
	}

	return 1;
}

int CGlobalState::Restore(CRestore &restore)
{
	int i, listCount;
	globalentity_t tmpEntity;

	ClearStates();

	if (!restore.ReadFields("GLOBAL", this, m_SaveData, ARRAYSIZE(m_SaveData)))
	{
		return 0;
	}

	// Get new list count
	listCount = m_listCount;

	// Clear loaded data
	m_listCount = 0;

	for (i = 0; i < listCount; i++)
	{
		if (!restore.ReadFields("GENT", &tmpEntity, m_GlobalEntitySaveData, ARRAYSIZE(m_GlobalEntitySaveData)))
		{
			return 0;
		}

		EntityAdd(MAKE_STRING(tmpEntity.name), MAKE_STRING(tmpEntity.levelName), tmpEntity.state);
	}

	return 1;
}

void CGlobalState::EntityUpdate(string_t globalname, string_t mapname)
{
	globalentity_t *pEnt = Find(globalname);
	if (pEnt)
	{
		Q_strcpy(pEnt->levelName, STRING(mapname));
	}
}

void CGlobalState::ClearStates()
{
	globalentity_t *pFree = m_pList;
	while (pFree)
	{
		globalentity_t *pNext = pFree->pNext;

		free(pFree);
		pFree = pNext;
	}

	Reset();
}

void EXT_FUNC SaveGlobalState(SAVERESTOREDATA *pSaveData)
{
	CSave saveHelper(pSaveData);
	gGlobalState.Save(saveHelper);
}

void EXT_FUNC RestoreGlobalState(SAVERESTOREDATA *pSaveData)
{
	CRestore restoreHelper(pSaveData);
	gGlobalState.Restore(restoreHelper);
}

void EXT_FUNC ResetGlobalState()
{
	gGlobalState.ClearStates();

	// Init the HUD on a new game / load game
	gInitHUD = TRUE;
}
