/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include "precompiled.h"

LessCtx_t g_LessCtx;
CUtlSymbolTable *CUtlSymbol::s_pSymbolTable = nullptr;

void CUtlSymbol::Initialize()
{
	// Necessary to allow us to create global symbols
	static bool symbolsInitialized = false;
	if (!symbolsInitialized)
	{
		s_pSymbolTable = new CUtlSymbolTable;
		symbolsInitialized = true;
	}
}

CUtlSymbolTable *CUtlSymbol::CurrTable()
{
	Initialize();
	return s_pSymbolTable;
}

CUtlSymbol::CUtlSymbol(const char *pStr)
{
	m_Id = CurrTable()->AddString(pStr);
}

const char *CUtlSymbol::String() const
{
	return CurrTable()->String(m_Id);
}

bool CUtlSymbol::operator==(const char *pStr) const
{
	if (m_Id == UTL_INVAL_SYMBOL)
		return false;

	return Q_strcmp(String(), pStr) == 0;
}

bool CUtlSymbolTable::SymLess(const unsigned int &i1, const unsigned int &i2)
{
	const char *str1 = g_LessCtx.m_pTable->String(i1);
	const char *str2 = g_LessCtx.m_pTable->String(i2);

	return Q_strcmp(str1, str2) < 0;
}

bool CUtlSymbolTable::SymLessi(const unsigned int &i1, const unsigned int &i2)
{
	const char *str1 = g_LessCtx.m_pTable->String(i1);
	const char *str2 = g_LessCtx.m_pTable->String(i2);

	return Q_stricmp(str1, str2) < 0;
}

CUtlSymbolTable::CUtlSymbolTable(int growSize, int initSize, bool caseInsensitive) :
	m_Lookup(growSize, initSize, caseInsensitive ? SymLessi : SymLess),
	m_Strings(256)
{
	;
}

CUtlSymbolTable::~CUtlSymbolTable()
{
	// Release the stringpool string data
	RemoveAll();
}

CUtlSymbol CUtlSymbolTable::Find(const char *pString) const
{
	// Passing this special invalid symbol makes the comparison function
	// use the string passed in the context
	UtlSymId_t idx = m_Lookup.Find(UTL_INVAL_SYMBOL);
	return CUtlSymbol(idx);
}

// Finds and/or creates a symbol based on the string
CUtlSymbol CUtlSymbolTable::AddString(const char *pString)
{
	if (!pString)
		return CUtlSymbol(UTL_INVAL_SYMBOL);

	CUtlSymbol id = Find(pString);

	if (id.IsValid())
		return id;

	int len = Q_strlen(pString) + 1;
	int stridx = m_Strings.AddMultipleToTail(len);

	UtlSymId_t idx = m_Lookup.Insert(stridx);
	return CUtlSymbol(idx);
}

const char *CUtlSymbolTable::String(CUtlSymbol id) const
{
	if (!id.IsValid())
		return "";

	assert(m_Lookup.IsValidIndex((UtlSymId_t)id));
	return &m_Strings[id];
}

void CUtlSymbolTable::RemoveAll()
{
	m_Lookup.RemoveAll();
	m_Strings.RemoveAll();
}
