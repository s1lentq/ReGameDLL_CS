#include "precompiled.h"

CSoundEnt *pSoundEnt;

/* <178ca4> ../cstrike/dlls/soundent.cpp:22 */
LINK_ENTITY_TO_CLASS(soundent, CSoundEnt);

/* <178d6e> ../cstrike/dlls/soundent.cpp:29 */
NOBODY void CSound::Clear(void)
{
}

/* <178d8f> ../cstrike/dlls/soundent.cpp:43 */
NOBODY void CSound::Reset(void)
{
}

/* <178db7> ../cstrike/dlls/soundent.cpp:54 */
NOBODY BOOL CSound::FIsSound(void)
{
}

/* <178ddf> ../cstrike/dlls/soundent.cpp:67 */
NOBODY BOOL CSound::FIsScent(void)
{
}

/* <17900a> ../cstrike/dlls/soundent.cpp:80 */
NOBODY void CSoundEnt::Spawn_(void)
{
}

/* <178b0c> ../cstrike/dlls/soundent.cpp:93 */
NOBODY void CSoundEnt::Think_(void)
{
//	{
//		int iSound;                                           //    95
//		int iPreviousSound;                                   //    96
//		{
//			int iNext;                                    //   107
//			FreeSound(int iSound,
//					int iPrevious);  //   110
//		}
//	}
//	Think(CSoundEnt *const this);  //    93
}

/* <178a76> ../cstrike/dlls/soundent.cpp:132 */
NOBODY void CSoundEnt::Precache_(void)
{
}

/* <178e07> ../cstrike/dlls/soundent.cpp:141 */
NOBODY void CSoundEnt::FreeSound(int iSound, int iPrevious)
{
}

/* <178e2d> ../cstrike/dlls/soundent.cpp:171 */
int CSoundEnt::IAllocSound(void)
{
	if (m_iFreeSound == SOUNDLIST_EMPTY)
	{
		ALERT(at_console, "Free Sound List is full!\n");
		return SOUNDLIST_EMPTY;
	}

	int iNewSound = m_iFreeSound;

	m_iFreeSound = m_SoundPool[ iNewSound ].m_iNext;
	m_SoundPool[ iNewSound ].m_iNext = m_iActiveSound;
	m_iActiveSound = iNewSound;

	return iNewSound;
}

/* <178e94> ../cstrike/dlls/soundent.cpp:200 */
void CSoundEnt::InsertSound(int iType, const Vector &vecOrigin, int iVolume, float flDuration)
{
	if (!pSoundEnt)
		return;

	int iThisSound = pSoundEnt->IAllocSound();

	if (iThisSound == SOUNDLIST_EMPTY)
	{
		ALERT(at_console, "Could not AllocSound() for InsertSound() (DLL)\n");
		return;
	}

	pSoundEnt->m_SoundPool[ iThisSound ].m_vecOrigin = vecOrigin;
	pSoundEnt->m_SoundPool[ iThisSound ].m_iType = iType;
	pSoundEnt->m_SoundPool[ iThisSound ].m_iVolume = iVolume;
	pSoundEnt->m_SoundPool[ iThisSound ].m_flExpireTime = gpGlobals->time + flDuration;
}

/* <178f4e> ../cstrike/dlls/soundent.cpp:228 */
NOBODY void CSoundEnt::Initialize(void)
{
//	{
//		int i;                                                //   230
//		int iSound;                                           //   231
//		Clear(CSound *const this);  //   239
//		IAllocSound(CSoundEnt *const this);  //   249
//	}
}

/* <179031> ../cstrike/dlls/soundent.cpp:274 */
NOBODY int CSoundEnt::ISoundsInList(int iListType)
{
//	{
//		int i;                                                //   276
//		int iThisSound;                                       //   277
//	}
}

/* <179073> ../cstrike/dlls/soundent.cpp:312 */
NOBODY int CSoundEnt::ActiveList(void)
{
}

/* <179083> ../cstrike/dlls/soundent.cpp:325 */
NOBODY int CSoundEnt::FreeList(void)
{
}

/* <179093> ../cstrike/dlls/soundent.cpp:339 */
NOBODY CSound *CSoundEnt::SoundPointerForIndex(int iIndex)
{
}

/* <1790b8> ../cstrike/dlls/soundent.cpp:367 */
NOBODY int CSoundEnt::ClientSoundIndex(edict_t *pClient)
{
//	{
//		int iReturn;                                          //   369
//		ENTINDEX(edict_t *pEdict);  //   369
//	}
}

#ifdef HOOK_GAMEDLL

void CSoundEnt::Spawn(void)
{
	Spawn_();
}

void CSoundEnt::Precache(void)
{
	Precache_();
}

void CSoundEnt::Think(void)
{
	Think_();
}

#endif // HOOK_GAMEDLL
