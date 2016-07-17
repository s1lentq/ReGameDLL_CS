#pragma once

#define _logf regamedll_log
#define printf2 _printf2
#define chatf _print_chat

extern void _printf2(const char *fmt, ...);
extern void _print_chat(class CBasePlayer *pPlayer, const char *fmt, ...);
extern void _print_console(struct entvars_s *pev, const char *fmt, ...);
