#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//static PlaceDirectory placeDirectory;

#else // HOOK_GAMEDLL

//PlaceDirectory placeDirectory;

#endif // HOOK_GAMEDLL

/* <4edbfc> ../game_shared/bot/nav_file.cpp:60 */
NOBODY void PlaceDirectory::Reset(void)
{
	//m_directory.clear();
}

/* <4edbaf> ../game_shared/bot/nav_file.cpp:66 */
NOBODY bool PlaceDirectory::IsKnown(Place place) const
{
	//std::vector<Place>::const_iterator it = std::find(m_directory.begin(), m_directory.end(), place);
	//return (it != m_directory.end());
}

/* <4ec844> ../game_shared/bot/nav_file.cpp:74 */
NOBODY PlaceDirectory::EntryType PlaceDirectory::GetEntry(Place place) const
{
	//if (place == UNDEFINED_PLACE)
	//	return 0;

	//std::vector<Place>::const_iterator it = std::find(m_directory.begin(), m_directory.end(), place);

	//if (it == m_directory.end())
	//{
	//	assert(false && "PlaceDirectory::GetEntry failure");
	//	return 0;
	//}
	//return 1 + (it - m_directory.begin());
}

/* <4ee200> ../game_shared/bot/nav_file.cpp:91 */
NOBODY void PlaceDirectory::AddPlace(Place place)
{
	//if (place == UNDEFINED_PLACE)
	//	return;

	//assert(place < 1000);

	//if (IsKnown(place))
	//	return;

	//m_directory.push_back(place);
}

/* <4edf61> ../game_shared/bot/nav_file.cpp:105 */
NOBODY Place PlaceDirectory::EntryToPlace(EntryType entry) const
{
	//if (entry == 0)
	//	return UNDEFINED_PLACE;

	//unsigned int i = entry - 1;

	//if (i > m_directory.size())
	//{
	//	assert(false && "PlaceDirectory::EntryToPlace: Invalid entry");
	//	return UNDEFINED_PLACE;
	//}

	//return m_directory[ i ];
}

/* <4edc2e> ../game_shared/bot/nav_file.cpp:122 */
NOBODY void PlaceDirectory::Save(int fd)
{
	// store number of entries in directory
	//EntryType count = m_directory.size();
	//Q_write(fd, &count, sizeof(EntryType));

	// store entries		
	//std::vector<Place>::iterator it;
	//for (it = m_directory.begin(); it != m_directory.end(); ++it)
	//{
	//	const char *placeName = TheBotPhrases->IDToName(*it);

		// store string length followed by string itself
	//	unsigned short len = strlen(placeName)+1;
	//	Q_write(fd, &len, sizeof(unsigned short));
	//	Q_write(fd, placeName, len);
	//}
}

/* <4edfaa> ../game_shared/bot/nav_file.cpp:142 */
NOBODY void PlaceDirectory::Load(SteamFile *file)
{
	// read number of entries
	//EntryType count;
	//file->Read(&count, sizeof(EntryType));

	//m_directory.reserve(count);

	// read each entry
	//char placeName[256];
	//unsigned short len;
	//for (int i = 0; i<count; i++)
	//{
	//	file->Read(&len, sizeof(unsigned short));
	//	file->Read(placeName, len);

	//	AddPlace(TheBotPhrases->NameToID(placeName));
	//}
}

/* <4ee54b> ../game_shared/bot/nav_file.cpp:173 */
NOBODY char *GetBspFilename(const char *navFilename)
{
//	{
//		char bspFilename;                                     //   175
//		int len;                                              //   179
//	}
}

/* <4ee5c1> ../game_shared/bot/nav_file.cpp:191 */
NOBODY void CNavArea::Save(FILE *fp) const
{
//	{
//		int base;                                             //   198
//	}
}

/* <4f09b8> ../game_shared/bot/nav_file.cpp:212 */
NOBODY void CNavArea::Save(int fd, unsigned int version)
{
//	{
//		unsigned char count;                                  //   246
//		unsigned int saveCount;                               //   259
//		unsigned char type;                                   //   281
//		unsigned int zero;                                    //   282
//		EntryType entry;                                      //   370
//		{
//			int d;                                        //   229
//			{
//				unsigned int count;                   //   232
//				const_iterator iter;                  //   235
//				size(const class list<NavConnect, std::allocator<NavConnect>> *const this);  //   232
//				{
//					union NavConnect connect;     //   238
//				}
//				operator++(_List_const_iterator<NavConnect> *const this);  //   236
//			}
//		}
//		size(const class list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //   247
//		size(const class list<HidingSpot*, std::allocator<HidingSpot*>> *const this);  //   254
//		{
//			iterator iter;                                //   260
//			operator++(_List_iterator<HidingSpot*> *const this);  //   260
//			{
//				class HidingSpot *spot;              //   262
//			}
//		}
//		{
//			int a;                                        //   283
//		}
//		{
//			unsigned int count;                           //   310
//			class SpotEncounter *e;                      //   316
//			size(const class list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //   310
//			{
//				iterator iter;                        //   317
//				{
//					unsigned char dir;            //   326
//					unsigned char spotCount;      //   338
//					size(const class list<SpotOrder, std::allocator<SpotOrder>> *const this);  //   339
//					size(const class list<SpotOrder, std::allocator<SpotOrder>> *const this);  //   346
//					{
//						iterator oiter;       //   351
//						operator++(_List_iterator<SpotOrder> *const this);  //   351
//						{
//							class SpotOrder *order;          //   353
//							unsigned int id;  //   356
//							unsigned char t;  //   359
//						}
//					}
//				}
//				operator++(_List_iterator<SpotEncounter> *const this);  //   317
//			}
//		}
//		GetEntry(const class PlaceDirectory *const this,
//			Place place);  //   370
//	}
}

/* <4ee669> ../game_shared/bot/nav_file.cpp:379 */
NOBODY void CNavArea::Load(SteamFile *file, unsigned int version)
{
//	{
//		unsigned char hidingSpotCount;                        //   424
//		unsigned char type;                                   //   461
//		unsigned int count;                                   //   479
//		EntryType entry;                                      //   550
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   382
//		{
//			unsigned int e;                               //   485
//			{
//				class SpotEncounter encounter;        //   487
//				unsigned char spotCount;              //   496
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   493
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   489
//				SpotEncounter(SpotEncounter *const this);  //   487
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   490
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   492
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   497
//				{
//					int s;                        //   499
//					{
//						Vector pos;     //   501
//						Read(SteamFile *const this,
//							void *data,
//							int length);  //   502
//						Read(SteamFile *const this,
//							void *data,
//							int length);  //   503
//					}
//				}
//				~SpotEncounter(SpotEncounter *const this,
//						int const __in_chrg);  //   487
//			}
//		}
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   389
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   392
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   399
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   400
//		{
//			int d;                                        //   404
//			{
//				unsigned int count;                   //   407
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   408
//				{
//					unsigned int i;               //   410
//					{
//						union NavConnect connect;   //   412
//						Read(SteamFile *const this,
//							void *data,
//							int length);  //   413
//						push_back(list<NavConnect, std::allocator<NavConnect>> *const this,
//								const value_type &__x);  //   415
//					}
//				}
//			}
//		}
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   425
//		{
//			int h;                                        //   444
//			{
//				class HidingSpot *spot;              //   447
//				push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//						const value_type &__x);  //   451
//			}
//		}
//		{
//			Vector pos;                             //   430
//			{
//				int h;                                //   431
//				{
//					class HidingSpot *spot;      //   436
//					Read(SteamFile *const this,
//						void *data,
//						int length);  //   433
//					push_back(list<HidingSpot*, std::allocator<HidingSpot*>> *const this,
//							const value_type &__x);  //   438
//				}
//			}
//		}
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   458
//		{
//			int a;                                        //   462
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   464
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   466
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   467
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   470
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   471
//		}
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   480
//		{
//			unsigned int e;                               //   509
//			{
//				class SpotEncounter encounter;        //   511
//				unsigned char dir;                    //   515
//				unsigned char spotCount;              //   525
//				class SpotOrder order;                //   528
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   513
//				SpotEncounter(SpotEncounter *const this);  //   511
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   516
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   519
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   521
//				Read(SteamFile *const this,
//					void *data,
//					int length);  //   526
//				{
//					int s;                        //   529
//					{
//						unsigned char t;      //   533
//						Read(SteamFile *const this,
//							void *data,
//							int length);  //   531
//						Read(SteamFile *const this,
//							void *data,
//							int length);  //   534
//						push_back(list<SpotOrder, std::allocator<SpotOrder>> *const this,
//								const value_type &__x);  //   538
//					}
//				}
//				push_back(list<SpotEncounter, std::allocator<SpotEncounter>> *const this,
//						const value_type &__x);  //   541
//				~SpotEncounter(SpotEncounter *const this,
//						int const __in_chrg);  //   511
//			}
//		}
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   551
//		EntryToPlace(const class PlaceDirectory *const this,
//				EntryType entry);  //   554
//		SetPlace(CNavArea *const this,
//			Place place);  //   554
//	}
}

/* <4f029e> ../game_shared/bot/nav_file.cpp:562 */
NOBODY NavErrorType CNavArea::PostLoad(void)
{
//	{
//		enum NavErrorType error;                              //   564
//		class SpotEncounter *e;                              //   610
//		{
//			int d;                                        //   567
//			{
//				iterator iter;                        //   569
//				{
//					union NavConnect *connect;   //   572
//					unsigned int id;              //   574
//				}
//				operator++(_List_iterator<NavConnect> *const this);  //   570
//			}
//		}
//		{
//			int a;                                        //   585
//		}
//		{
//			iterator iter;                                //   611
//			end(list<SpotEncounter, std::allocator<SpotEncounter>> *const this);  //   611
//			{
//				float halfWidth;                      //   632
//				float const eyeHeight;                 //   636
//			}
//			{
//				iterator oiter;                       //   642
//				end(list<SpotOrder, std::allocator<SpotOrder>> *const this);  //   642
//				{
//					class SpotOrder *order;      //   644
//				}
//				operator++(_List_iterator<SpotOrder> *const this);  //   642
//			}
//			operator++(_List_iterator<SpotEncounter> *const this);  //   611
//		}
//		{
//			iterator oiter;                               //   657
//			{
//				class CNavArea *area;                //   659
//				push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//						const value_type &__x);  //   665
//			}
//			operator++(_List_iterator<CNavArea*> *const this);  //   657
//		}
//	}
}


/* <4edbe0> ../game_shared/bot/nav_file.cpp:680 */
NOBODY void COM_FixSlashes(char *pname)
{
}

/* <4f3e47> ../game_shared/bot/nav_file.cpp:702 */
NOBODY bool SaveNavigationMap(const char *filename)
{
//	{
//		int fd;                                               //   716
//		unsigned int magic;                                   //   723
//		unsigned int version;                                 //   733
//		char *bspFilename;                                   //   739
//		unsigned int bspSize;                                 //   743
//		iterator it;                                          //   754
//		unsigned int count;                                   //   775
//		COM_FixSlashes(char *pname);  //   710
//		GetBspFilename(const char *navFilename);  //   739
//		Reset(PlaceDirectory *const this);  //   752
//		{
//			class CNavArea *area;                        //   757
//			Place place;                                  //   759
//			AddPlace(PlaceDirectory *const this,
//				Place place);  //   763
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //   755
//		Save(PlaceDirectory *const this,
//			int fd);  //   767
//		size(const class list<CNavArea*, std::allocator<CNavArea*>> *const this);  //   775
//		{
//			class CNavArea *area;                        //   781
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //   779
//	}
}

/* <4f169d> ../game_shared/bot/nav_file.cpp:811 */
NOBODY void LoadLocationFile(const char *filename)
{
//	{
//		char locFilename;                                     //   813
//		char *dot;                                           //   816
//		strchr(char *__s,
//			int __c);  //   816
//		{
//			int locDataLength;                            //   821
//			char *locDataFile;                           //   822
//			char *locData;                               //   823
//			{
//				int dirSize;                          //   831
//				atoi(const char *__nptr);  //   831
//				{
//					class vector<unsigned int, std::allocator<unsigned int>> directory;                                      //   835
//					unsigned int areaID;          //   846
//					unsigned int locDirIndex;     //   846
//					vector(vector<unsigned int, std::allocator<unsigned int>> *const this);  //   835
//					reserve(vector<unsigned int, std::allocator<unsigned int>> *const this,
//						size_type __n);  //   837
//					{
//						int i;                //   839
//						push_back(vector<unsigned int, std::allocator<unsigned int>> *const this,
//								const value_type &__x);  //   842
//					}
//					{
//						class CNavArea *area;//   858
//						unsigned int place;   //   859
//						atoi(const char *__nptr);  //   853
//						atoi(const char *__nptr);  //   856
//						SetPlace(CNavArea *const this,
//							Place place);  //   862
//					}
//					~vector(vector<unsigned int, std::allocator<unsigned int>> *const this,
//						int const __in_chrg);  //   835
//				}
//			}
//		}
//	}
}

/* <4f05c5> ../game_shared/bot/nav_file.cpp:876 */
NOBODY void SanityCheckNavigationMap(const char *mapName)
{
//	{
//		int const BufLen;                                      //   885
//		char bspFilename;                                     //   886
//		char navFilename;                                     //   887
//		class SteamFile navFile;                              //   891
//		bool result;                                          //   900
//		unsigned int magic;                                   //   901
//		unsigned int version;                                 //   910
//		SteamFile(SteamFile *const this,
//				const char *filename);  //   891
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   902
//		~SteamFile(SteamFile *const this,
//				int const __in_chrg);  //   891
//		~SteamFile(SteamFile *const this,
//				int const __in_chrg);  //   891
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   911
//		{
//			unsigned int saveBspSize;                     //   921
//			unsigned int bspSize;                         //   931
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   922
//		}
//	}
}

void (*pLoadNavigationMap)(void);

/* <4f19c7> ../game_shared/bot/nav_file.cpp:947 */
NOBODY NavErrorType __declspec(naked) LoadNavigationMap(void)
{
	__asm
	{
		jmp pLoadNavigationMap
	}
//	{
//		char filename;                                        //   955
//		class SteamFile navFile;                              //   965
//		bool result;                                          //   971
//		unsigned int magic;                                   //   972
//		unsigned int version;                                 //   981
//		unsigned int count;                                   //  1020
//		class Extent extent;                                  //  1023
//		iterator iter;                                        //  1056
//		Reset(PlaceDirectory *const this);  //   961
//		SteamFile(SteamFile *const this,
//				const char *filename);  //   965
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   973
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //   982
//		{
//			unsigned int saveBspSize;                     //   992
//			char *bspFilename;                           //   996
//			unsigned int bspSize;                         //  1000
//			Read(SteamFile *const this,
//				void *data,
//				int length);  //   993
//			{
//				char *msg;                           //  1005
//			}
//		}
//		Read(SteamFile *const this,
//			void *data,
//			int length);  //  1021
//		{
//			unsigned int i;                               //  1030
//			{
//				class CNavArea *area;                //  1032
//				const class Extent *areaExtent;     //  1036
//				Load(CNavArea *const this,
//					class SteamFile *file,
//					unsigned int version);  //  1033
//				push_back(list<CNavArea*, std::allocator<CNavArea*>> *const this,
//						const value_type &__x);  //  1034
//			}
//		}
//		~SteamFile(SteamFile *const this,
//				int const __in_chrg);  //   965
//		operator++(_List_iterator<CNavArea*> *const this);  //  1057
//		{
//			class CNavArea *area;                        //  1064
//		}
//		operator++(_List_iterator<CNavArea*> *const this);  //  1062
//		Load(PlaceDirectory *const this,
//			class SteamFile *file);  //  1016
//	}
}
