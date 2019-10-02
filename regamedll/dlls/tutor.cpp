#include "precompiled.h"

cvar_t cv_tutor_message_repeats                            = { "_tutor_message_repeats", "5", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_debug_level                                = { "_tutor_debug_level", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_view_distance                              = { "_tutor_view_distance", "1000", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_viewable_check_interval                    = { "_tutor_bomb_viewable_check_interval", "0.5", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_look_distance                              = { "_tutor_look_distance", "200", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_look_angle                                 = { "_tutor_look_angle", "10", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_examine_time                               = { "_tutor_examine_time", "0.5", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_message_minimum_display_time               = { "_tutor_message_minimum_display_time", "1", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_message_character_display_time_coefficient = { "_tutor_message_character_display_time_coefficient", "0.07", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_tutor_hint_interval_time                         = { "_tutor_hint_interval_time", "10.0", FCVAR_SERVER, 0.0f, nullptr };

bool s_tutorDisabledThisGame = false;
float s_nextCvarCheckTime = 0.0f;

void InstallTutor(bool bCreate)
{
	if (TheTutor)
	{
		delete TheTutor;
		TheTutor = nullptr;
	}

	if (bCreate)
	{
		TheTutor = new CCSTutor;
	}

	s_tutorDisabledThisGame = false;
	s_nextCvarCheckTime = gpGlobals->time;
}

void Tutor_RegisterCVars()
{
#ifdef REGAMEDLL_FIXES
	if (!AreRunningCZero())
		return;
#endif

	CVAR_REGISTER(&cv_tutor_message_repeats);
	CVAR_REGISTER(&cv_tutor_debug_level);
	CVAR_REGISTER(&cv_tutor_view_distance);
	CVAR_REGISTER(&cv_tutor_viewable_check_interval);
	CVAR_REGISTER(&cv_tutor_look_distance);
	CVAR_REGISTER(&cv_tutor_look_angle);
	CVAR_REGISTER(&cv_tutor_examine_time);
	CVAR_REGISTER(&cv_tutor_message_minimum_display_time);
	CVAR_REGISTER(&cv_tutor_message_character_display_time_coefficient);
	CVAR_REGISTER(&cv_tutor_hint_interval_time);
}

void MonitorTutorStatus()
{
	static cvar_t *tutor_enable = nullptr;
	static bool tutor_enableCvarExists = true;

	bool shouldTutorBeOn = false;
	int numHumans = 0;

	if (!tutor_enableCvarExists || s_nextCvarCheckTime > gpGlobals->time)
		return;

	if (tutor_enable || (tutor_enable = CVAR_GET_POINTER("tutor_enable")))
	{
		if (!s_tutorDisabledThisGame && tutor_enable->value > 0.0f)
		{
			shouldTutorBeOn = true;
		}
	}
	else
		tutor_enableCvarExists = false;

	for (int i = 1; i <= gpGlobals->maxClients; i++)
	{
		CBasePlayer *pPlayer = UTIL_PlayerByIndex(i);

		if (pPlayer && !pPlayer->IsBot())
			numHumans++;
	}

	if (shouldTutorBeOn)
	{
		if (numHumans <= 1)
		{
			if (!TheTutor)
			{
				CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
				if (pLocalPlayer)
				{
					ClientPrint(pLocalPlayer->pev, HUD_PRINTCENTER, "#CZero_Tutor_Turned_On");
				}

				TheTutor = new CCSTutor;
			}
		}
		else
		{
			s_tutorDisabledThisGame = true;
		}
	}
	else
	{
		if (TheTutor)
		{
			CBasePlayer *pLocalPlayer = UTIL_GetLocalPlayer();
			if (pLocalPlayer)
			{
				ClientPrint(pLocalPlayer->pev, HUD_PRINTCENTER, "#CZero_Tutor_Turned_Off");
			}

			delete TheTutor;
			TheTutor = nullptr;
		}
	}

	s_nextCvarCheckTime = gpGlobals->time + 1.0f;
}
