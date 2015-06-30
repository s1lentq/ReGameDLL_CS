#include "precompiled.h"
#include "game_shared/simple_checksum.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

BotProfileManager *TheBotProfiles = NULL;

#else // HOOK_GAMEDLL

BotProfileManager *TheBotProfiles;

#endif // HOOK_GAMEDLL

/* <4a693f> ../game_shared/bot/bot_profile.cpp:52 */
NOBODY const char *GetDecoratedSkinName(const char *name, const char *filename)
{
//	{
//		int const BufLen;                                      //    57
//		char buf;                                             //    59
//	}
}

/* <4a7a99> ../game_shared/bot/bot_profile.cpp:65 */
NOBODY const char *BotProfile::GetWeaponPreferenceAsString(int i) const
{
}

/* <4a7acd> ../game_shared/bot/bot_profile.cpp:78 */
NOBODY bool BotProfile::HasPrimaryPreference(void) const
{
//	{
//		int i;                                                //    80
//		{
//			int weaponClass;                              //    82
//		}
//	}
}

/* <4a7b22> ../game_shared/bot/bot_profile.cpp:99 */
NOBODY bool BotProfile::HasPistolPreference(void) const
{
//	{
//		int i;                                                //   101
//	}
}

/* <4a7b5e> ../game_shared/bot/bot_profile.cpp:112 */
NOBODY bool BotProfile::IsValidForTeam(BotProfileTeamType team) const
{
}

/* <4a7bb2> ../game_shared/bot/bot_profile.cpp:122 */
NOBODY BotProfileManager::BotProfileManager(void)
{
//	list(list<BotProfile*, std::allocator<BotProfile*>> *const this);  //   122
//	vector(vector<char*, std::allocator<char*>> *const this);  //   122
//	{
//		int i;                                                //   125
//	}
}

/* <4a8acb> ../game_shared/bot/bot_profile.cpp:137 */
NOBODY void BotProfileManager::Init(const char *filename, unsigned int *checksum)
{
//	{
//		int dataLength;                                       //   139
//		char *dataPointer;                                   //   140
//		const char *dataFile;                               //   141
//		BotProfileList templateList;                          //   159
//		class BotProfile defaultProfile;                      //   161
//		ComputeSimpleChecksum(const unsigned char *dataPointer,
//					int dataLength);  //   155
//		BotProfile(BotProfile *const this);  //   161
//		list(list<BotProfile*, std::allocator<BotProfile*>> *const this);  //   159
//		{
//			char *token;                                 //   172
//			bool isDefault;                               //   174
//			bool isTemplate;                              //   175
//			bool isCustomSkin;                            //   176
//			class BotProfile *profile;                   //   270
//			bool isFirstWeaponPref;                       //   348
//			{
//				int const BufLen;                      //   180
//				char skinName;                        //   181
//				const char *decoratedName;          //   236
//				bool skinExists;                      //   237
//				GetDecoratedSkinName(const char *name,
//							const char *filename);  //   236
//				GetCustomSkinIndex(BotProfileManager *const this,
//							const char *name,
//							const char *filename);  //   237
//				CloneString(const char *str);  //   241
//				CloneString(const char *str);  //   244
//			}
//			{
//				const class BotProfile *inherit;    //   287
//				{
//					char *c;                     //   292
//					strchr(char *__s,
//						int __c);  //   292
//					{
//						iterator iter;        //   297
//						operator++(_List_iterator<BotProfile*> *const this);  //   297
//					}
//					Inherit(BotProfile *const this,
//						const class BotProfile *parent,
//						const class BotProfile *baseline);  //   314
//				}
//			}
//			{
//				char attributeName;                   //   366
//				{
//					char *c;                     //   474
//					strchr(char *__s,
//						int __c);  //   474
//					{
//						int i;                //   478
//					}
//				}
//				atof(const char *__nptr);  //   464
//				atof(const char *__nptr);  //   453
//				atoi(const char *__nptr);  //   424
//				atoi(const char *__nptr);  //   420
//				atof(const char *__nptr);  //   416
//				atoi(const char *__nptr);  //   407
//				GetCustomSkinIndex(BotProfileManager *const this,
//							const char *name,
//							const char *filename);  //   411
//				atof(const char *__nptr);  //   403
//				atof(const char *__nptr);  //   399
//			}
//			BotProfile(BotProfile *const this);  //   278
//			CloneString(const char *str);  //   334
//			push_back(list<BotProfile*, std::allocator<BotProfile*>> *const this,
//					const value_type &__x);  //   514
//			push_back(list<BotProfile*, std::allocator<BotProfile*>> *const this,
//					const value_type &__x);  //   519
//		}
//		~list(list<BotProfile*, std::allocator<BotProfile*>> *const this,
//			int const __in_chrg);  //   159
//		{
//			iterator iter;                                //   527
//			operator++(_List_iterator<BotProfile*> *const this);  //   527
//		}
//		~list(list<BotProfile*, std::allocator<BotProfile*>> *const this,
//			int const __in_chrg);  //   159
//	}
}

/* <4a7dfd> ../game_shared/bot/bot_profile.cpp:532 */
NOBODY BotProfileManager::~BotProfileManager(void)
{
//	{
//		iterator it;                                          //   536
//		begin(vector<char*, std::allocator<char*>> *const this);  //   537
//		end(vector<char*, std::allocator<char*>> *const this);  //   537
//		operator++(__normal_iterator<char**, std::vector<char*, std::allocator<char*>> > *const this);  //   537
//		clear(vector<char*, std::allocator<char*>> *const this);  //   541
//	}
//	~vector(vector<char*, std::allocator<char*>> *const this,
//		int const __in_chrg);  //   532
//	~list(list<BotProfile*, std::allocator<BotProfile*>> *const this,
//		int const __in_chrg);  //   532
}

/* <4a7c76> ../game_shared/bot/bot_profile.cpp:548 */
NOBODY void BotProfileManager::Reset(void)
{
//	clear(list<BotProfile*, std::allocator<BotProfile*>> *const this);  //   553
//	{
//		iterator iter;                                        //   550
//		operator++(_List_iterator<BotProfile*> *const this);  //   550
//	}
//	{
//		int i;                                                //   555
//	}
}

/* <4a7fdf> ../game_shared/bot/bot_profile.cpp:579 */
NOBODY const char *BotProfileManager::GetCustomSkin(int index)
{
}

/* <4a8019> ../game_shared/bot/bot_profile.cpp:593 */
const char *BotProfileManager::GetCustomSkinFname(int index)
{
	if (index < FirstCustomSkin || index > LastCustomSkin)
	{
		return NULL;
	}

	return m_skinModelnames[ index - FirstCustomSkin ];
}

/* <4a8053> ../game_shared/bot/bot_profile.cpp:607 */
const char *BotProfileManager::GetCustomSkinModelname(int index)
{
	if (index < FirstCustomSkin || index > LastCustomSkin)
	{
		return NULL;
	}
	return m_skins[ index - FirstCustomSkin ];
}

/* <4a80db> ../game_shared/bot/bot_profile.cpp:621 */
NOBODY int BotProfileManager::GetCustomSkinIndex(const char *name, const char *filename)
{
//	{
//		const char *skinName;                               //   623
//		GetDecoratedSkinName(const char *name,
//					const char *filename);  //   626
//		{
//			int i;                                        //   629
//		}
//	}
}

/* <4a8916> ../game_shared/bot/bot_profile.cpp:647 */
NOBODY int BotProfileManager::FindVoiceBankIndex(const char *filename)
{
//	{
//		int index;                                            //   649
//		const_iterator it;                                    //   651
//		begin(vector<char*, std::allocator<char*>> *const this);  //   652
//		end(vector<char*, std::allocator<char*>> *const this);  //   652
//		operator++(__normal_iterator<char* const*, std::vector<char*, std::allocator<char*>> > *const this);  //   652
//		CloneString(const char *str);  //   660
//		push_back(vector<char*, std::allocator<char*>> *const this,
//				const value_type &__x);  //   660
//	}
}

/* <4a8177> ../game_shared/bot/bot_profile.cpp:669 */
NOBODY const BotProfile *BotProfileManager::GetRandomProfile(BotDifficultyType difficulty, BotProfileTeamType team) const
{
//	{
//		const_iterator iter;                                  //   674
//		int validCount;                                       //   677
//		int which;                                            //   690
//		operator++(_List_const_iterator<BotProfile*> *const this);  //   678
//		{
//			const class BotProfile *profile;            //   680
//			IsDifficulty(const class BotProfile *const this,
//					enum BotDifficultyType diff);  //   682
//			IsValidForTeam(const class BotProfile *const this,
//					enum BotProfileTeamType team);  //   682
//		}
//		operator++(_List_const_iterator<BotProfile*> *const this);  //   691
//		{
//			const class BotProfile *profile;            //   693
//			IsDifficulty(const class BotProfile *const this,
//					enum BotDifficultyType diff);  //   695
//			IsValidForTeam(const class BotProfile *const this,
//					enum BotProfileTeamType team);  //   695
//		}
//	}
}
