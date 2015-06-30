#include "precompiled.h"

/* <3a397f> ../cstrike/dlls/bot/cs_bot_radio.cpp:220 */
NOBODY void CCSBot::StartVoiceFeedback(float duration)
{
//	{
//		class CBasePlayer *pPlayer;                          //   227
//		MESSAGE_BEGIN(int msg_dest,
//				int msg_type,
//				const float *pOrigin,
//				entvars_t *ent);  //   230
//		edict(CBaseEntity *const this);  //   232
//		ENTINDEX(edict_t *pEdict);  //   232
//	}
}

/* <3a3a32> ../cstrike/dlls/bot/cs_bot_radio.cpp:241 */
NOBODY void CCSBot::EndVoiceFeedback(bool force)
{
//	MESSAGE_BEGIN(int msg_dest,
//			int msg_type,
//			const float *pOrigin,
//			edict_t *ed);  //   249
//	edict(CBaseEntity *const this);  //   251
//	ENTINDEX(edict_t *pEdict);  //   251
}

/* <3a3bcd> ../cstrike/dlls/bot/cs_bot_radio.cpp:259 */
NOBODY bool CCSBot::RespondToHelpRequest(CBasePlayer *them, Place place, float maxRange)
{
//	{
//		class PathCost pc;                                    //   272
//		float travelDistance;                                 //   273
//		NavAreaTravelDistance<PathCost>(CNavArea *startArea,
//						class CNavArea *endArea,
//						class PathCost &costFunc);  //   273
//	}
//	{
//		float rangeSq;                                        //   287
//		float const close;                                     //   288
//		operator-(const Vector *const this,
//				const Vector &v);  //   287
//		LengthSquared(const Vector *const this);  //   287
//	}
//	{
//		const Vector *pos;                            //   301
//	}
//	Say(BotChatterInterface *const this,
//		const char *phraseName,
//		float lifetime,
//		float delay);  //   309
}

/* <3a4316> ../cstrike/dlls/bot/cs_bot_radio.cpp:319 */
NOBODY void CCSBot::SendRadioMessage(GameEventType event)
{
//	{
//		class CCSBotManager *ctrl;                           //   328
//		char slot;                                            //   333
//	}
}
