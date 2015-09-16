#include "precompiled.h"

CSoundEnt *pSoundEnt;

/* <178ca4> ../cstrike/dlls/soundent.cpp:22 */
LINK_ENTITY_TO_CLASS(soundent, CSoundEnt);

// CSound - Clear - zeros all fields for a sound

/* <178d6e> ../cstrike/dlls/soundent.cpp:29 */
void CSound::Clear(void)
{
	m_vecOrigin = g_vecZero;
	m_iType = 0;
	m_iVolume = 0;
	m_flExpireTime = 0;
	m_iNext = SOUNDLIST_EMPTY;
	m_iNextAudible = 0;
}

// Reset - clears the volume, origin, and type for a sound,
// but doesn't expire or unlink it.

/* <178d8f> ../cstrike/dlls/soundent.cpp:43 */
void CSound::Reset(void)
{
	m_vecOrigin = g_vecZero;
	m_iNext = SOUNDLIST_EMPTY;
	m_iType = 0;
	m_iVolume = 0;
}

// FIsSound - returns TRUE if the sound is an Audible sound

/* <178db7> ../cstrike/dlls/soundent.cpp:54 */
NOXREF BOOL CSound::FIsSound(void)
{
	if (m_iType & (bits_SOUND_COMBAT | bits_SOUND_WORLD | bits_SOUND_PLAYER | bits_SOUND_DANGER))
	{
		return TRUE;
	}

	return FALSE;
}

// FIsScent - returns TRUE if the sound is actually a scent

/* <178ddf> ../cstrike/dlls/soundent.cpp:67 */
NOXREF BOOL CSound::FIsScent(void)
{
	if (m_iType & (bits_SOUND_CARCASS | bits_SOUND_MEAT | bits_SOUND_GARBAGE))
	{
		return TRUE;
	}

	return FALSE;
}

/* <17900a> ../cstrike/dlls/soundent.cpp:80 */
void CSoundEnt::__MAKE_VHOOK(Spawn)(void)
{
	pev->solid = SOLID_NOT;
	Initialize();

	pev->nextthink = gpGlobals->time + 1;
}

// Think - at interval, the entire active sound list is checked
// for sounds that have ExpireTimes less than or equal
// to the current world time, and these sounds are deallocated.

/* <178b0c> ../cstrike/dlls/soundent.cpp:93 */
void CSoundEnt::__MAKE_VHOOK(Think)(void)
{
	int iSound;
	int iPreviousSound;

	// how often to check the sound list.
	pev->nextthink = gpGlobals->time + 0.3;

	iPreviousSound = SOUNDLIST_EMPTY;
	iSound = m_iActiveSound;

	while (iSound != SOUNDLIST_EMPTY)
	{
		if (m_SoundPool[ iSound ].m_flExpireTime <= gpGlobals->time && m_SoundPool[ iSound ].m_flExpireTime != SOUND_NEVER_EXPIRE)
		{
			int iNext = m_SoundPool[ iSound ].m_iNext;

			// move this sound back into the free list
			FreeSound(iSound, iPreviousSound);

			iSound = iNext;
		}
		else
		{
			iPreviousSound = iSound;
			iSound = m_SoundPool[ iSound ].m_iNext;
		}
	}

	if (m_fShowReport)
	{
		ALERT(at_aiconsole, "Soundlist: %d / %d  (%d)\n", ISoundsInList(SOUNDLISTTYPE_ACTIVE), ISoundsInList(SOUNDLISTTYPE_FREE), ISoundsInList(SOUNDLISTTYPE_ACTIVE) - m_cLastActiveSounds);
		m_cLastActiveSounds = ISoundsInList(SOUNDLISTTYPE_ACTIVE);
	}
}

// Precache - dummy function

/* <178a76> ../cstrike/dlls/soundent.cpp:132 */
void CSoundEnt::__MAKE_VHOOK(Precache)(void)
{
	;
}

// FreeSound - clears the passed active sound and moves it
// to the top of the free list. TAKE CARE to only call this
// function for sounds in the Active list!!

/* <178e07> ../cstrike/dlls/soundent.cpp:141 */
void CSoundEnt::FreeSound(int iSound, int iPrevious)
{
	if (!pSoundEnt)
	{
		// no sound ent!
		return;
	}

	if (iPrevious != SOUNDLIST_EMPTY)
	{
		// iSound is not the head of the active list, so
		// must fix the index for the Previous sound
		// pSoundEnt->m_SoundPool[ iPrevious ].m_iNext = m_SoundPool[ iSound ].m_iNext;
		pSoundEnt->m_SoundPool[ iPrevious ].m_iNext = pSoundEnt->m_SoundPool[ iSound ].m_iNext;
	}
	else
	{
		// the sound we're freeing IS the head of the active list.
		pSoundEnt->m_iActiveSound = pSoundEnt->m_SoundPool[ iSound ].m_iNext;
	}

	// make iSound the head of the Free list.
	pSoundEnt->m_SoundPool[ iSound ].m_iNext = pSoundEnt->m_iFreeSound;
	pSoundEnt->m_iFreeSound = iSound;
}

// IAllocSound - moves a sound from the Free list to the
// Active list returns the index of the alloc'd sound

/* <178e2d> ../cstrike/dlls/soundent.cpp:171 */
int CSoundEnt::IAllocSound(void)
{
	int iNewSound;

	if (m_iFreeSound == SOUNDLIST_EMPTY)
	{
		// no free sound!
		ALERT(at_console, "Free Sound List is full!\n");
		return SOUNDLIST_EMPTY;
	}

	// there is at least one sound available, so move it to the
	// Active sound list, and return its SoundPool index.

	// copy the index of the next free sound
	iNewSound = m_iFreeSound;

	// move the index down into the free list.
	m_iFreeSound = m_SoundPool[ iNewSound ].m_iNext;

	// point the new sound at the top of the active list.
	m_SoundPool[ iNewSound ].m_iNext = m_iActiveSound;

	// now make the new sound the top of the active list. You're done.
	m_iActiveSound = iNewSound;

	return iNewSound;
}

// InsertSound - Allocates a free sound and fills it with
// sound info.

/* <178e94> ../cstrike/dlls/soundent.cpp:200 */
void CSoundEnt::InsertSound(int iType, const Vector &vecOrigin, int iVolume, float flDuration)
{
	int iThisSound;

	if (!pSoundEnt)
	{
		// no sound ent!
		return;
	}

	iThisSound = pSoundEnt->IAllocSound();

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

// Initialize - clears all sounds and moves them into the
// free sound list.

/* <178f4e> ../cstrike/dlls/soundent.cpp:228 */
void CSoundEnt::Initialize(void)
{
  	int i;
	int iSound;

	m_cLastActiveSounds = 0;
	m_iFreeSound = 0;
	m_iActiveSound = SOUNDLIST_EMPTY;

	// clear all sounds, and link them into the free sound list.
	for (i = 0; i < MAX_WORLD_SOUNDS; i++)
	{
		m_SoundPool[ i ].Clear();
		m_SoundPool[ i ].m_iNext = i + 1;
	}

	// terminate the list here.
	m_SoundPool[ i - 1 ].m_iNext = SOUNDLIST_EMPTY;

	// now reserve enough sounds for each client
	for (i = 0; i < gpGlobals->maxClients; i++)
	{
		iSound = pSoundEnt->IAllocSound();

		if (iSound == SOUNDLIST_EMPTY)
		{
			ALERT(at_console, "Could not AllocSound() for Client Reserve! (DLL)\n");
			return;
		}

		pSoundEnt->m_SoundPool[ iSound ].m_flExpireTime = SOUND_NEVER_EXPIRE;
	}

	if (CVAR_GET_FLOAT("displaysoundlist") == 1)
	{
		m_fShowReport = TRUE;
	}
	else
	{
		m_fShowReport = FALSE;
	}
}

// ISoundsInList - returns the number of sounds in the desired
// sound list.

/* <179031> ../cstrike/dlls/soundent.cpp:274 */
int CSoundEnt::ISoundsInList(int iListType)
{
	int i;
	int iThisSound;

	if (iListType == SOUNDLISTTYPE_FREE)
	{
		iThisSound = m_iFreeSound;
	}
	else if (iListType == SOUNDLISTTYPE_ACTIVE)
	{
		iThisSound = m_iActiveSound;
	}
	else
	{
		ALERT(at_console, "Unknown Sound List Type!\n");
	}

	if (iThisSound == SOUNDLIST_EMPTY)
	{
		return 0;
	}

	i = 0;

	while (iThisSound != SOUNDLIST_EMPTY)
	{
		i++;

		iThisSound = m_SoundPool[ iThisSound ].m_iNext;
	}

	return i;
}

// ActiveList - returns the head of the active sound list

/* <179073> ../cstrike/dlls/soundent.cpp:312 */
NOXREF int CSoundEnt::ActiveList(void)
{
	if (!pSoundEnt)
	{
		return SOUNDLIST_EMPTY;
	}

	return pSoundEnt->m_iActiveSound;
}

// FreeList - returns the head of the free sound list

/* <179083> ../cstrike/dlls/soundent.cpp:325 */
NOXREF int CSoundEnt::FreeList(void)
{
	if (!pSoundEnt)
	{
		return SOUNDLIST_EMPTY;
	}

	return pSoundEnt->m_iFreeSound;
}

// SoundPointerForIndex - returns a pointer to the instance
// of CSound at index's position in the sound pool.

/* <179093> ../cstrike/dlls/soundent.cpp:339 */
CSound *CSoundEnt::SoundPointerForIndex(int iIndex)
{
	if (!pSoundEnt)
	{
		return NULL;
	}

	if (iIndex > (MAX_WORLD_SOUNDS - 1))
	{
		ALERT(at_console, "SoundPointerForIndex() - Index too large!\n");
		return NULL;
	}

	if (iIndex < 0)
	{
		ALERT(at_console, "SoundPointerForIndex() - Index < 0!\n");
		return NULL;
	}

	return &pSoundEnt->m_SoundPool[ iIndex ];
}

// Clients are numbered from 1 to MAXCLIENTS, but the client
// reserved sounds in the soundlist are from 0 to MAXCLIENTS - 1,
// so this function ensures that a client gets the proper index
// to his reserved sound in the soundlist.

/* <1790b8> ../cstrike/dlls/soundent.cpp:367 */
int CSoundEnt::ClientSoundIndex(edict_t *pClient)
{
	int iReturn = ENTINDEX(pClient) - 1;

#if defined(_DEBUG) && !defined(HOOK_GAMEDLL)

	if (iReturn < 0 || iReturn > gpGlobals->maxClients)
	{
		ALERT(at_console, "** ClientSoundIndex returning a bogus value! **\n");
	}

#endif // _DEBUG && !HOOK_GAMEDLL

	return iReturn;
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
