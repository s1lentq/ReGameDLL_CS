#ifndef PLATFORM_GAMEDLL_H
#define PLATFORM_GAMEDLL_H
#ifdef _WIN32
#pragma once
#endif

#define _logf regamedll_log

extern void regamedll_log(const char *fmt, ...);
extern void NORETURN regamedll_syserror(const char *error, ...);

#endif // PLATFORM_GAMEDLL_H
