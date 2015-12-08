#include "precompiled.h"

#ifdef _WIN32

void *_malloc_mhook_(size_t n)
{
	void *ptr = malloc(n);
	Regamedll_Debug_logAlloc(n, ptr);
	return ptr;
}

void *_realloc_mhook_(void *memblock, size_t size)
{
	void *ptr = realloc(memblock, size);
	Regamedll_Debug_logRealloc(size, memblock, ptr);
	return ptr;
}

void _free_mhook_(void *p)
{
	Regamedll_Debug_logFree(p);
	free(p);
}

void *_calloc_mhook_(size_t n, size_t s)
{
	void *ptr = calloc(n, s);
	Regamedll_Debug_logAlloc(s * n, ptr);
	return ptr;
}

void *__nh_malloc_mhook_(size_t n)
{
	void *ptr = malloc(n);
	Regamedll_Debug_logAlloc(n, ptr);
	return ptr;
}

char *_strdup_mhook_(const char *s)
{
	char *ptr = _strdup(s);
	Regamedll_Debug_logStrDup(s, ptr);
	return ptr;
}

#endif // _WIN32
