#pragma once

enum TestPlayerMode
{
	TPM_DISABLE,
	TPM_RECORD,
	TPM_PLAY,
};

class CRegameDLLRuntimeConfig
{
private:
	static const char *getNextToken(char **pBuf);
public:
	CRegameDLLRuntimeConfig();

	bool bIsZero;
	bool disableAllHooks;
	char testRecordingFileName[260];
	char testConfigFileName[260];
	TestPlayerMode testPlayerMode;

	void parseFromConfigFile();
	void parseFromCommandLine(const char *cmdLine);
};

extern CRegameDLLRuntimeConfig g_ReGameDLLRuntimeConfig;
