#include "precompiled.h"

CRegameDLLRuntimeConfig g_ReGameDLLRuntimeConfig;

CRegameDLLRuntimeConfig::CRegameDLLRuntimeConfig()
{
	bIsZero = false;
	disableAllHooks = false;
	testRecordingFileName[0] = 0;
	testConfigFileName[0] = 0;
	testPlayerMode = TPM_DISABLE;
}

void CRegameDLLRuntimeConfig::parseFromConfigFile(void)
{
#ifdef _WIN32

	if (strlen(testConfigFileName) <= 0)
		return;

	std::string str;
	std::string path( bIsZero ? "./czero/server.cfg" : "./cstrike/server.cfg" );
	std::string pattern = "exec tests/";

	std::ifstream intput_file( path );
	std::vector< std::string > out;

	bool bFound = false;
	while (std::getline(intput_file, str))
	{
		if (str.find( pattern ) != -1)
		{
			bFound = true;

			std::ostringstream stringStream;
			stringStream << pattern << testConfigFileName;
			str = stringStream.str();
		}

		out.push_back( str.c_str() );
	}

	if (!bFound)
	{
		std::ostringstream stringStream;
		stringStream << "\n" << pattern << testConfigFileName;

		out.push_back( stringStream.str() );
	}

	intput_file.close();

	std::ofstream output_file( path );
	std::ostream_iterator< std::string > output_iterator(output_file, "\n");
	std::copy(out.begin(), out.end(), output_iterator);

	out.clear();
	output_file.close();

#endif // _WIN32
}

void CRegameDLLRuntimeConfig::parseFromCommandLine(const char *cmdLine)
{
	char localBuf[2048];
	if (strlen(cmdLine) >= sizeof(localBuf))
		regamedll_syserror("%s: too long cmdline", __FUNCTION__);

	strcpy(localBuf, cmdLine);
	char *cpos = localBuf;

	getNextToken(&cpos); //skip executable path

	const char *token = getNextToken(&cpos);
	while (token != NULL)
	{
		if (!strcmp(token, "--regamedll-test-record"))
		{
			const char *fname = getNextToken(&cpos);

			if (fname == NULL)
				regamedll_syserror("%s: usage: --regamedll-test-record <filename>", __FUNCTION__);

			strncpy(testRecordingFileName, fname, sizeof(testRecordingFileName));
			testRecordingFileName[sizeof(testRecordingFileName) - 1] = 0;
			testPlayerMode = TPM_RECORD;
		}
		else if (!strcmp(token, "--regamedll-test-play"))
		{
			const char *fname = getNextToken(&cpos);

			if (fname == NULL)
				regamedll_syserror("%s: usage: --regamedll-test-play <filename>", __FUNCTION__);

			strncpy(testRecordingFileName, fname, sizeof(testRecordingFileName));
			testRecordingFileName[sizeof(testRecordingFileName) - 1] = 0;
			testPlayerMode = TPM_PLAY;
		}
		else if (!strcmp(token, "--regamedll-cfg-init"))
		{
			const char *fname = getNextToken(&cpos);

			if (fname != NULL)
			{
				strncpy(testConfigFileName, fname, sizeof(testConfigFileName));
				testConfigFileName[sizeof(testConfigFileName) - 1] = 0;
			}
		}
		else if (!strcmp(token, "--regamedll-disable-all-hooks"))
		{
			disableAllHooks = true;
		}
		else if (!strcmp(token, "-game"))
		{
			const char *szTokenGame = getNextToken(&cpos);

			if (szTokenGame != NULL && !strcmp(szTokenGame, "czero"))
				bIsZero = true;
		}

		token = getNextToken(&cpos);
	}

	// parse config filename for testdemo
	parseFromConfigFile();
}

const char *CRegameDLLRuntimeConfig::getNextToken(char* *pBuf)
{
	char *rpos = *pBuf;
	if (*rpos == 0)
		return NULL;

	//skip spaces at the beginning
	while (*rpos != 0 && isspace(*rpos))
		rpos++;

	if (*rpos == 0) {
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
				if (rpos != wpos) *wpos = cc;
				rpos++; wpos++;
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
				rpos++; wpos++;
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
