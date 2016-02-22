#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

LessCtx_t g_LessCtx;

#endif

CUtlSymbolTable *CUtlSymbol::s_pSymbolTable = 0;

void CUtlSymbol::Initialize()
{
	// necessary to allow us to create global symbols
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
