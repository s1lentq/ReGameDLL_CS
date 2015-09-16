#include "precompiled.h"

/* <31d087> ../cstrike/dlls/bot/cs_bot_event.cpp:22 */
void CCSBot::__MAKE_VHOOK(OnEvent)(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
//	{
//		class CCSBotManager *ctrl;                           //    63
//		class CBasePlayer *player;                           //    65
//		float range;                                          //   363
//		enum PriorityType priority;                           //   364
//		bool isHostile;                                       //   365
//		const Vector *newNoisePosition;               //   419
//		float newNoiseDist;                                   //   420
//		{
//			class CBasePlayer *killer;                   //    81
//			{
//				float const knifeAmbushChance;         //    91
//				Hurry(CCSBot *const this,
//					float duration);  //    88
//			}
//		}
//		Say(BotChatterInterface *const this,
//			const char *phraseName,
//			float lifetime,
//			float delay);  //   221
//		{
//			float const bombBeepHearRangeSq;               //   242
//			operator-(const Vector *const this,
//					const Vector &v);  //   243
//			LengthSquared(const Vector *const this);  //   243
//			{
//				const class Zone *zone;             //   248
//			}
//		}
//		{
//			float const bombPickupHearRangeSq;             //   229
//			operator-(const Vector *const this,
//					const Vector &v);  //   230
//			LengthSquared(const Vector *const this);  //   230
//		}
//		{
//			class CBasePlayer *victim;                   //   111
//			class CBasePlayer *killer;                   //   113
//			GetNearbyEnemyCount(const class CCSBot *const this);  //   175
//			{
//				float delay;                          //   185
//			}
//			GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   155
//			SetTask(CCSBot *const this,
//				enum TaskType task,
//				class CBaseEntity *entity);  //   164
//			GetEnemy(CCSBot *const this);  //   164
//			Say(BotChatterInterface *const this,
//				const char *phraseName,
//				float lifetime,
//				float delay);  //   118
//			entindex(CBaseEntity *const this);  //   124
//		}
//		GetEnemy(CCSBot *const this);  //   292
//		ForceRun(CCSBot *const this,
//			float duration);  //   294
//		{
//			float const hearCallRange;                     //   329
//			Vector vecCenter;                       //   334
//			operator-(const Vector *const this,
//					const Vector &v);  //   330
//			IsLengthGreaterThan(const Vector *const this,
//						float length);  //   330
//			{
//				enum RouteType route;                 //   343
//				SetTask(CCSBot *const this,
//					enum TaskType task,
//					class CBaseEntity *entity);  //   338
//				SetGoalEntity(CCSBot *const this,
//						class CBaseEntity *entity);  //   340
//			}
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //   376
//		IsLengthGreaterThan(const Vector *const this,
//					float length);  //   376
//		{
//			float const headOffChance;                     //   390
//			SetTask(CCSBot *const this,
//				enum TaskType task,
//				class CBaseEntity *entity);  //   396
//		}
//		operator-(const Vector *const this,
//				const Vector &v);  //   420
//		Length(const Vector *const this);  //   420
//		{
//			float const veryCloseRange;                    //   434
//			class CNavArea *noiseArea;                   //   461
//			float const maxErrorRadius;                    //   481
//			float const maxHearingRange;                   //   482
//			float errorRadius;                            //   483
//			{
//				float const shortTermMemoryTime;       //   445
//				{
//					float oldNoiseDist;           //   452
//					operator-(const Vector *const this,
//							const Vector &v);  //   452
//					Length(const Vector *const this);  //   452
//				}
//			}
//		}
//	}
}

#ifdef HOOK_GAMEDLL

void CCSBot::OnEvent(GameEventType event, CBaseEntity *entity, CBaseEntity *other)
{
	OnEvent_(event, entity, other);
}

#endif // HOOK_GAMEDLL
