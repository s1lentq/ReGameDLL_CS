#pragma once

class CRegameDLLRuntimeConfig
{
private:
	bool bIsZero;
	const char *getNextToken(char **pBuf);

public:
	CRegameDLLRuntimeConfig();

	bool IsCzero() const { return bIsZero; }
	void parseFromCommandLine(const char *cmdLine);
};

extern CRegameDLLRuntimeConfig g_ReGameDLLRuntimeConfig;
