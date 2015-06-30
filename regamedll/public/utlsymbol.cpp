#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

static LessCtx_t g_LessCtx;
CUtlSymbolTable *CUtlSymbol::s_pSymbolTable = 0;

#else

LessCtx_t g_LessCtx;
CUtlSymbolTable *CUtlSymbol::s_pSymbolTable;

#endif // HOOK_GAMEDLL

/* <401141> ../public/utlsymbol.cpp:31 */
void CUtlSymbol::Initialize(void)
{
	static bool symbolsInitialized = false;
	if (!symbolsInitialized)
	{
		s_pSymbolTable = new CUtlSymbolTable;
		symbolsInitialized = true;
	}
}

/* <40125f> ../public/utlsymbol.cpp:42 */
NOBODY CUtlSymbolTable *CUtlSymbol::CurrTable(void)
{
//	Initialize(void);  //    44
	return NULL;
}

/* <403946> ../public/utlsymbol.cpp:53 */
NOBODY CUtlSymbol::CUtlSymbol(const char *pStr)
{
//	CurrTable(void);  //    55
}

/* <4013a8> ../public/utlsymbol.cpp:58 */
NOBODY const char *CUtlSymbol::String(void) const
{
//	CurrTable(void);  //    60
//	String(const class CUtlSymbolTable *const this,
//		class CUtlSymbol id);  //    60
	return NULL;
}

/* <40154b> ../public/utlsymbol.cpp:67 */
NOBODY bool CUtlSymbol::operator==(const char *pStr) const
{
//	String(const class CUtlSymbol *const this);  //    71
	return false;
}

/* <40104d> ../public/utlsymbol.cpp:91 */
NOBODY bool CUtlSymbolTable::SymLess(const unsigned int &i1, const unsigned int &i2)
{
//	{
//		const char *str1;                                   //    93
//		const char *str2;                                   //    95
//		operator[](CUtlVector<char> *const this,
//				int i);  //    94
//		operator[](CUtlVector<char> *const this,
//				int i);  //    96
//	}
	return false;
}

/* <400f73> ../public/utlsymbol.cpp:102 */
NOBODY bool CUtlSymbolTable::SymLessi(const unsigned int &i1, const unsigned int &i2)
{
//	{
//		const char *str1;                                   //   104
//		const char *str2;                                   //   106
//		operator[](CUtlVector<char> *const this,
//				int i);  //   105
//		operator[](CUtlVector<char> *const this,
//				int i);  //   107
//	}
	return false;
}

/* <4016f4> ../public/utlsymbol.cpp:120 */
NOBODY CUtlSymbolTable::CUtlSymbolTable(int growSize, int initSize, bool caseInsensitive)
{
//	CUtlRBTree(CUtlRBTree<unsigned int, unsigned short> *const this,
//			int growSize,
//			int initSize,
//			LessFunc_t lessfunc);  //   121
//	CUtlVector(CUtlVector<char> *const this,
//			int growSize,
//			int initSize);  //   121
}

/* <401823> ../public/utlsymbol.cpp:125 */
NOBODY CUtlSymbolTable::~CUtlSymbolTable(void)
{
//	~CUtlVector(CUtlVector<char>::~CUtlSymbolTable(//			int const __in_chrg);  //   125
//	~CUtlRBTree(CUtlRBTree<unsigned int, unsigned short> *const this,
//			int const __in_chrg);  //   125
}

/* <4019b0> ../public/utlsymbol.cpp:130 */
NOBODY CUtlSymbol CUtlSymbolTable::Find(const char *pString) const
{
//	{
//		UtlSymId_t idx;                                       //   141
//		Find(const class CUtlRBTree<unsigned int, unsigned short> *const this,
//			const unsigned int &search);  //   141
//		CUtlSymbol(CUtlSymbol *const this,
//				UtlSymId_t id);  //   142
//		CUtlSymbol(CUtlSymbol *const this);  //   133
//	}
}

/* <40358d> ../public/utlsymbol.cpp:150 */
NOBODY CUtlSymbol CUtlSymbolTable::AddString(const char *pString)
{
//	{
//		class CUtlSymbol id;                                  //   155
//		int len;                                              //   161
//		int stridx;                                           //   162
//		UtlSymId_t idx;                                       //   164
//		IsValid(const class CUtlSymbol *const this);  //   157
//		CUtlSymbol(CUtlSymbol *const this,
//				UtlSymId_t id);  //   165
//		AddMultipleToTail(CUtlVector<char> *const this,
//					int num);  //   162
//		Insert(CUtlRBTree<unsigned int, unsigned short> *const this,
//			const unsigned int &insert);  //   164
//		CUtlSymbol(CUtlSymbol *const this,
//				UtlSymId_t id);  //   153
//	}
}

/* <401b8f> ../public/utlsymbol.cpp:173 */
NOBODY const char *CUtlSymbolTable::String(CUtlSymbol id) const
{
//	IsValid(const class CUtlSymbol *const this);  //   175
//	operator[](const class CUtlVector<char> *const this,
//			int i);  //   179
	return NULL;
}

/* <401c10> ../public/utlsymbol.cpp:187 */
NOBODY void CUtlSymbolTable::RemoveAll(void)
{
//	RemoveAll(CUtlRBTree<unsigned int, unsigned short> *const this);  //   189
//	RemoveAll(CUtlVector<char> *const this);  //   190
}
