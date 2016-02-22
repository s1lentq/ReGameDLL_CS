#include "precompiled.h"

CRegameDLLRuntimeConfig g_ReGameDLLRuntimeConfig;

CRegameDLLRuntimeConfig::CRegameDLLRuntimeConfig()
{
	bIsZero = false;
}

void CRegameDLLRuntimeConfig::parseFromCommandLine(const char *cmdLine)
{
	char localBuf[2048];
	if (strlen(cmdLine) >= sizeof(localBuf))
		regamedll_syserror("%s: too long cmdline", __FUNCTION__);

	strcpy(localBuf, cmdLine);
	char *cpos = localBuf;

	getNextToken(&cpos); // skip executable path

	const char *token = getNextToken(&cpos);
	while (token != NULL)
	{
		if (!strcmp(token, "-game"))
		{
			const char *gameMod = getNextToken(&cpos);

			if (gameMod != NULL && !strcmp(gameMod, "czero"))
				bIsZero = true;
		}

		token = getNextToken(&cpos);
	}
}

const char *CRegameDLLRuntimeConfig::getNextToken(char* *pBuf)
{
	char *rpos = *pBuf;
	if (*rpos == 0)
		return NULL;

	// skip spaces at the beginning
	while (*rpos != 0 && isspace(*rpos))
		rpos++;

	if (*rpos == 0)
	{
		*pBuf = rpos;
		return NULL;
	}

	const char *res = rpos;
	char *wpos = rpos;
	char inQuote = 0;
	while (*rpos != 0)
	{
		char cc = *rpos;
		if (inQuote)
		{
			if (inQuote == cc)
			{
				inQuote = 0;
				rpos++;
			}
			else
			{
				if (rpos != wpos)
					*wpos = cc;
				rpos++;
				wpos++;
			}
		}
		else
		{
			if (isspace(cc))
			{
				break;
			}
			else if (cc == '\'' || cc == '"')
			{
				inQuote = cc;
				rpos++;
			}
			else
			{
				if (rpos != wpos)
					*wpos = cc;
				rpos++;
				wpos++;
			}
		}
	}
	if (*rpos != 0)
	{
		rpos++;
	}

	*pBuf = rpos;
	*wpos = 0;
	return res;
}
