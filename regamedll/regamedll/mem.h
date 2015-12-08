#ifndef MEM_H
#define MEM_H
#ifdef _WIN32
#pragma once
#endif

#ifdef _WIN32

void *_malloc_mhook_(size_t n);
void *_realloc_mhook_(void *memblock, size_t size);
void _free_mhook_(void *p);
void *_calloc_mhook_(size_t n, size_t s);
void *__nh_malloc_mhook_(size_t n);
char *_strdup_mhook_(const char *s);

#endif // _WIN32

#endif // MEM_H