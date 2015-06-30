#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

cvar_t cv_tutor_message_repeats = { "_tutor_message_repeats", "5", FCVAR_SERVER };
cvar_t cv_tutor_debug_level = { "_tutor_debug_level", "0", FCVAR_SERVER };
cvar_t cv_tutor_view_distance = { "_tutor_view_distance", "1000", FCVAR_SERVER };
cvar_t cv_tutor_viewable_check_interval = { "_tutor_bomb_viewable_check_interval", "0.5", FCVAR_SERVER };
cvar_t cv_tutor_look_distance = { "_tutor_look_distance", "200", FCVAR_SERVER };
cvar_t cv_tutor_look_angle = { "_tutor_look_angle", "10", FCVAR_SERVER };
cvar_t cv_tutor_examine_time = { "_tutor_examine_time", "0.5", FCVAR_SERVER };
cvar_t cv_tutor_message_minimum_display_time = { "_tutor_message_minimum_display_time", "1", FCVAR_SERVER };
cvar_t cv_tutor_message_character_display_time_coefficient = { "_tutor_message_character_display_time_coefficient", "0.07", FCVAR_SERVER };
cvar_t cv_tutor_hint_interval_time = { "_tutor_hint_interval_time", "10.0", FCVAR_SERVER };

#else

cvar_t cv_tutor_message_repeats;
cvar_t cv_tutor_debug_level;
cvar_t cv_tutor_view_distance;
cvar_t cv_tutor_viewable_check_interval;
cvar_t cv_tutor_look_distance;
cvar_t cv_tutor_look_angle;
cvar_t cv_tutor_examine_time;
cvar_t cv_tutor_message_minimum_display_time;
cvar_t cv_tutor_message_character_display_time_coefficient;
cvar_t cv_tutor_hint_interval_time;

#endif // HOOK_GAMEDLL

bool s_tutorDisabledThisGame;
float s_nextCvarCheckTime;

/* <1dfdbc> ../cstrike/dlls/tutor.cpp:32 */
NOBODY void InstallTutor(bool start)
{
	// TODO: check out!
	//if (TheTutor)
	//{
	//	(*((void (__cdecl **)(_DWORD))TheTutor->_vptr.CBaseTutor + 1))(TheTutor);
	//	TheTutor = 0;
	//}

	if (TheTutor)
	{
		delete TheTutor;


		//TheTutor->~CBaseTutor();
		//TheTutor = NULL;
	}

	if (start)
		TheTutor = new CCSTutor;

	s_tutorDisabledThisGame = false;
	s_nextCvarCheckTime = gpGlobals->time;
}

/* <1dfde7> ../cstrike/dlls/tutor.cpp:51 */
void Tutor_RegisterCVars(void)
{
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

/* <1dfdff> ../cstrike/dlls/tutor.cpp:66 */
NOBODY void MonitorTutorStatus(void)
{
//	{
//		cvar_t *tutor_enable;                                //    68
//		bool tutor_enableCvarExists;                          //    69
//		bool shouldTutorBeOn;                                 //    82
//		int numHumans;                                        //    96
//		{
//			int i;                                        //    97
//			{
//				class CBasePlayer *pPlayer;          //    99
//			}
//		}
//		{
//			class CBasePlayer *localPlayer;              //   125
//		}
//		{
//			class CBasePlayer *localPlayer;              //   113
//		}
//	}
}
