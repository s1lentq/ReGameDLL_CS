//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#include "precompiled.h"
#include "resource.h"

class CDialogInitInfo
{
public:
	const char *m_pFilename;
	int m_iLine;
	const char *m_pExpression;
};

class CAssertDisable
{
public:
	char m_Filename[MAX_OSPATH];

	// If these are not -1, then this CAssertDisable only disables asserts on lines between
	// these values (inclusive).
	int m_LineMin;
	int m_LineMax;

	// Decremented each time we hit this assert and ignore it, until it's 0.
	// Then the CAssertDisable is removed.
	// If this is -1, then we always ignore this assert.
	int m_nIgnoreTimes;

	CAssertDisable *m_pNext;
};

static CDialogInitInfo g_Info{};
static bool g_bAssertsEnabled = true;
static CAssertDisable *g_pAssertDisables = nullptr;

// Set to true if they want to break in the debugger
static bool g_bBreak = false;

// Internal functions
static HINSTANCE g_hTier0Instance = nullptr;
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,		// handle to the DLL module
	DWORD fdwReason,		// reason for calling function
	LPVOID lpvReserved		// reserved
)
{
	g_hTier0Instance = hinstDLL;
	return true;
}

static bool IsDebugBreakEnabled()
{
	static bool bResult = (Q_strstr(Plat_GetCommandLine(), "-debugbreak") != nullptr);
	return bResult;
}

static bool AreAssertsDisabled()
{
	static bool bResult = (Q_strstr(Plat_GetCommandLine(), "-noassert") != nullptr);
	return bResult;
}

static bool AreAssertsEnabledInFileLine(const char *pFilename, int iLine)
{
	CAssertDisable **pPrev = &g_pAssertDisables;
	CAssertDisable *pNext = nullptr;

	for (CAssertDisable *pCur = g_pAssertDisables; pCur; pCur = pNext)
	{
		pNext = pCur->m_pNext;

		if (Q_stricmp(pFilename, pCur->m_Filename) == 0)
		{
			// Are asserts disabled in the whole file?
			bool bAssertsEnabled = true;
			if (pCur->m_LineMin == -1 && pCur->m_LineMax == -1)
				bAssertsEnabled = false;

			// Are asserts disabled on the specified line?
			if (iLine >= pCur->m_LineMin && iLine <= pCur->m_LineMax)
				bAssertsEnabled = false;

			if (!bAssertsEnabled)
			{
				// If this assert is only disabled for the next N times, then countdown..
				if (pCur->m_nIgnoreTimes > 0)
				{
					pCur->m_nIgnoreTimes--;

					if (pCur->m_nIgnoreTimes == 0)
					{
						// Remove this one from the list.
						*pPrev = pNext;
						delete pCur;
						continue;
					}
				}

				return false;
			}
		}

		pPrev = &pCur->m_pNext;
	}

	return true;
}

CAssertDisable *CreateNewAssertDisable(const char *pFilename)
{
	CAssertDisable *pDisable = new CAssertDisable;
	pDisable->m_pNext = g_pAssertDisables;
	g_pAssertDisables = pDisable;

	pDisable->m_LineMin = pDisable->m_LineMax = -1;
	pDisable->m_nIgnoreTimes = -1;

	Q_strlcpy(pDisable->m_Filename, g_Info.m_pFilename);

	return pDisable;
}

void IgnoreAssertsInCurrentFile()
{
	CreateNewAssertDisable(g_Info.m_pFilename);
}

CAssertDisable *IgnoreAssertsNearby(int nRange)
{
	CAssertDisable *pDisable = CreateNewAssertDisable(g_Info.m_pFilename);
	pDisable->m_LineMin = g_Info.m_iLine - nRange;
	pDisable->m_LineMax = g_Info.m_iLine - nRange;
	return pDisable;
}

static int g_iLastLineRange = 5;
static int g_nLastIgnoreNumTimes = 1;

int CALLBACK AssertDialogProc(
	HWND hDlg,		// handle to dialog box
	UINT uMsg,		// message
	WPARAM wParam,	// first message parameter
	LPARAM lParam	// second message parameter
)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hDlg, IDC_ASSERT_MSG_CTRL, g_Info.m_pExpression);
		SetDlgItemText(hDlg, IDC_FILENAME_CONTROL, g_Info.m_pFilename);

		SetDlgItemInt(hDlg, IDC_LINE_CONTROL, g_Info.m_iLine, false);
		SetDlgItemInt(hDlg, IDC_IGNORE_NUMLINES, g_iLastLineRange, false);
		SetDlgItemInt(hDlg, IDC_IGNORE_NUMTIMES, g_nLastIgnoreNumTimes, false);

		// Center the dialog.
		RECT rcDlg, rcDesktop;
		GetWindowRect(hDlg, &rcDlg);
		GetWindowRect(GetDesktopWindow(), &rcDesktop);
		SetWindowPos(hDlg, HWND_TOP,
			((rcDesktop.right  - rcDesktop.left) - (rcDlg.right  - rcDlg.left)) / 2,
			((rcDesktop.bottom - rcDesktop.top)  - (rcDlg.bottom - rcDlg.top))  / 2,
			0, 0,
			SWP_NOSIZE
		);

		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		// Ignore this assert N times
		case IDC_IGNORE_THIS:
		{
			BOOL bTranslated = false;
			UINT value = GetDlgItemInt(hDlg, IDC_IGNORE_NUMTIMES, &bTranslated, false);
			if (bTranslated && value > 1)
			{
				CAssertDisable *pDisable = IgnoreAssertsNearby(0);
				pDisable->m_nIgnoreTimes = value - 1;
				g_nLastIgnoreNumTimes = value;
			}

			EndDialog(hDlg, 0);
			return TRUE;
		}
		case IDC_IGNORE_NEARBY:
		{
			BOOL bTranslated = false;
			UINT value = GetDlgItemInt(hDlg, IDC_IGNORE_NUMLINES, &bTranslated, false);
			if (!bTranslated || value < 1)
				return TRUE;

			IgnoreAssertsNearby(value);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		case IDC_IGNORE_FILE:
			IgnoreAssertsInCurrentFile();
			EndDialog(hDlg, 0);
			return TRUE;
		// Always ignore this assert
		case IDC_IGNORE_ALWAYS:
			IgnoreAssertsNearby(0);
			EndDialog(hDlg, 0);
			return TRUE;
		case IDC_IGNORE_ALL:
			g_bAssertsEnabled = false;
			EndDialog(hDlg, 0);
			return TRUE;
		case IDC_BREAK:
			g_bBreak = true;
			EndDialog(hDlg, 0);
			return TRUE;
		}
		case WM_KEYDOWN:
		{
			// Escape?
			if (wParam == 2)
			{
				// Ignore this assert
				EndDialog(hDlg, 0);
				return TRUE;
			}

			break;
		}

		return TRUE;
	}
	}

	return FALSE;
}

static HWND g_hBestParentWindow = nullptr;

static BOOL CALLBACK ParentWindowEnumProc(
	HWND hWnd,		// handle to parent window
	LPARAM lParam	// application-defined value
)
{
	if (IsWindowVisible(hWnd))
	{
		DWORD procID;
		GetWindowThreadProcessId(hWnd, &procID);
		if (procID == (DWORD)lParam)
		{
			g_hBestParentWindow = hWnd;
			return FALSE; // don't iterate any more.
		}
	}

	return TRUE;
}

static HWND FindLikelyParentWindow()
{
	// Enumerate top-level windows and take the first visible one with our processID.
	g_hBestParentWindow = nullptr;
	EnumWindows(ParentWindowEnumProc, GetCurrentProcessId());
	return g_hBestParentWindow;
}

bool DoNewAssertDialog(const char *pFilename, int line, const char *pExpression)
{
	if (AreAssertsDisabled())
		return false;

	// If they have the old mode enabled (always break immediately), then just break right into
	// the debugger like we used to do.
	if (IsDebugBreakEnabled())
		return true;

	// Have ALL Asserts been disabled?
	if (!g_bAssertsEnabled)
		return false;

	// Has this specific Assert been disabled?
	if (!AreAssertsEnabledInFileLine(pFilename, line))
		return false;

	// Now create the dialog.
	g_Info.m_pFilename = pFilename;
	g_Info.m_iLine = line;
	g_Info.m_pExpression = pExpression;

	g_bBreak = false;

	HWND hParentWindow = FindLikelyParentWindow();
	DialogBox(g_hTier0Instance, MAKEINTRESOURCE(IDD_ASSERT_DIALOG), hParentWindow, AssertDialogProc);

	return g_bBreak;
}
