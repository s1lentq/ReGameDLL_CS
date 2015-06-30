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

#ifndef UTL_SYMBOL_H
#define UTL_SYMBOL_H
#ifdef _WIN32
#pragma once
#endif

class CUtlSymbolTable;

typedef unsigned short UtlSymId_t;

#define UTL_INVAL_SYMBOL  ((UtlSymId_t)~0)

/* <400608> ../public/utlsymbol.cpp:85 */
struct LessCtx_t
{
	char const *m_pUserString;
	CUtlSymbolTable *m_pTable;
	
	LessCtx_t() : m_pUserString(0), m_pTable(0) {}
};/* size: 8, cachelines: 1, members: 2 */

/* <400e59> ../public/utlsymbol.h:46 */
class CUtlSymbol
{
public:
	// constructor, destructor
	CUtlSymbol() : m_Id(UTL_INVAL_SYMBOL) {}
	CUtlSymbol(UtlSymId_t id) : m_Id(id) {}
	CUtlSymbol(const char* pStr);
	CUtlSymbol(CUtlSymbol const &sym) : m_Id(sym.m_Id) {}
 
	// operator=
	CUtlSymbol &operator=(CUtlSymbol const &src)
	{
		m_Id = src.m_Id;
		return *this;
	}
	// operator==
	bool operator==(CUtlSymbol const &src) const
	{
		return m_Id == src.m_Id;
	}
	bool operator==(const char *pStr) const;
	// Is valid?
	bool IsValid() const
	{
		return m_Id != UTL_INVAL_SYMBOL;
	}
	// Gets at the symbol
	operator UtlSymId_t/* const*/() const	// warning #858
	{
		return m_Id;
	}
	// Gets the string associated with the symbol
	const char *String() const;

protected:
	// Initializes the symbol table
	static void Initialize(void);
	// returns the current symbol table
	static CUtlSymbolTable *CurrTable(void);

	UtlSymId_t m_Id;
	static CUtlSymbolTable *s_pSymbolTable;
};/* size: 2, cachelines: 1, members: 2 */

class CUtlSymbolTable
{
public:
	// constructor, destructor
	CUtlSymbolTable(int growSize = 0,int initSize = 32,bool caseInsensitive = false);
	~CUtlSymbolTable();

	// Finds and/or creates a symbol based on the string
	CUtlSymbol AddString(const char *pString);

	// Finds the symbol for pString
	CUtlSymbol Find(const char *pString) const;

	// Look up the string associated with a particular symbol
	const char *String(CUtlSymbol id) const;

	// Remove all symbols in the table.
	void RemoveAll(void);
public:
	static bool SymLess(const unsigned int &i1, const unsigned int &i2);
	static bool SymLessi(const unsigned int &i1, const unsigned int &i2);
protected:
	CUtlRBTree<unsigned int, unsigned short> m_Lookup;
	CUtlVector<char> m_Strings;
};/* size: 44, cachelines: 1, members: 2 */

#ifdef HOOK_GAMEDLL

#define g_LessCtx (*pg_LessCtx)

#endif // HOOK_GAMEDLL

extern LessCtx_t g_LessCtx;

#endif // UTL_SYMBOL_H
