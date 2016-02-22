#include "precompiled.h"

void regamedll_log(const char *fmt, ...)
{
	va_list argptr;
	static char data[8192];

	va_start(argptr, fmt);
	Q_vsnprintf(data, sizeof(data), fmt, argptr);
	data[sizeof(data) - 1] = 0;

	strcat(data,"\n");

#ifdef _WIN32

	int fd = _open("regamedll.log", _O_WRONLY | _O_APPEND | _O_CREAT, _S_IREAD | _S_IWRITE);
	int len = Q_strlen(data);
	_write(fd, data, len);
	_close(fd);

#else

	FILE *fd = fopen("regamedll.log", "at");
	fprintf(fd, "%s", data);
	fclose(fd);

#endif // _WIN32
}

void __declspec(noreturn) regamedll_syserror(const char *fmt, ...)
{
	va_list argptr;
	static char string[8192];

	va_start(argptr, fmt);
	vsnprintf(string, sizeof(string), fmt, argptr);
	va_end(argptr);

	printf("%s\n", string);

	FILE *fl = fopen("regamedll_error.txt", "w");
	fprintf(fl, "%s\n", string);
	fclose(fl);

	//TerminateProcess(GetCurrentProcess(), 1);
	*((int *)NULL) = 0;
	while (true);
}
