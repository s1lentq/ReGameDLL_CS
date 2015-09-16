#include "precompiled.h"

// STL uses exceptions, but we are not compiling with them - ignore warning
#pragma warning(disable : 4530)

// long STL names get truncated in browse info.
#pragma warning(disable : 4786)

#undef min
#undef max

#include <list>
#include <vector>
#include <algorithm>

#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>

#ifndef _WIN32

#include <unistd.h>

#endif // _WIN32

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

static PlaceDirectory placeDirectory;

#else // HOOK_GAMEDLL

PlaceDirectory placeDirectory;

#endif // HOOK_GAMEDLL

/* <4edbfc> ../game_shared/bot/nav_file.cpp:60 */
void PlaceDirectory::Reset(void)
{
	m_directory.clear();
}

/* <4edbaf> ../game_shared/bot/nav_file.cpp:66 */
bool PlaceDirectory::IsKnown(Place place) const
{
	std::vector<Place>::const_iterator it = std::find(m_directory.begin(), m_directory.end(), place);
	return (it != m_directory.end());
}

/* <4ec844> ../game_shared/bot/nav_file.cpp:74 */
PlaceDirectory::EntryType PlaceDirectory::GetEntry(Place place) const
{
	if (place == UNDEFINED_PLACE)
		return 0;

	std::vector<Place>::const_iterator it = std::find(m_directory.begin(), m_directory.end(), place);

	if (it == m_directory.end())
	{
		assert(false && "PlaceDirectory::GetEntry failure");
		return 0;
	}

	return 1 + (it - m_directory.begin());
}

/* <4ee200> ../game_shared/bot/nav_file.cpp:91 */
void PlaceDirectory::AddPlace(Place place)
{
	if (place == UNDEFINED_PLACE)
		return;

	assert(place < 1000);

	if (IsKnown(place))
		return;

	m_directory.push_back(place);
}

/* <4edf61> ../game_shared/bot/nav_file.cpp:105 */
Place PlaceDirectory::EntryToPlace(EntryType entry) const
{
	if (entry == 0)
		return UNDEFINED_PLACE;

	unsigned int i = entry - 1;

	if (i > m_directory.size())
	{
		assert(false && "PlaceDirectory::EntryToPlace: Invalid entry");
		return UNDEFINED_PLACE;
	}

	return m_directory[ i ];
}

/* <4edc2e> ../game_shared/bot/nav_file.cpp:122 */
void PlaceDirectory::Save(int fd)
{
	// store number of entries in directory
	EntryType count = m_directory.size();
	Q_write(fd, &count, sizeof(EntryType));

	// store entries
	std::vector<Place>::iterator it;
	for (it = m_directory.begin(); it != m_directory.end(); ++it)
	{
		const char *placeName = TheBotPhrases->IDToName(*it);

		// store string length followed by string itself
		unsigned short len = Q_strlen(placeName) + 1;
		Q_write(fd, &len, sizeof(unsigned short));
		Q_write(fd, placeName, len);
	}
}

/* <4edfaa> ../game_shared/bot/nav_file.cpp:142 */
void PlaceDirectory::Load(SteamFile *file)
{
	// read number of entries
	EntryType count;
	file->Read(&count, sizeof(EntryType));

	m_directory.reserve(count);

	// read each entry
	char placeName[256];
	unsigned short len;
	for (int i = 0; i < count; i++)
	{
		file->Read(&len, sizeof(unsigned short));
		file->Read(placeName, len);

		AddPlace(TheBotPhrases->NameToID(placeName));
	}
}

/* <4ee54b> ../game_shared/bot/nav_file.cpp:173 */
char *GetBspFilename(const char *navFilename)
{
	static char bspFilename[256];

	Q_sprintf(bspFilename, "maps\\%s.bsp", STRING(gpGlobals->mapname));

	int len = Q_strlen(bspFilename);
	if (len < 3)
		return NULL;

	bspFilename[len - 3] = 'b';
	bspFilename[len - 2] = 's';
	bspFilename[len - 1] = 'p';

	return bspFilename;
}

/* <4ee5c1> ../game_shared/bot/nav_file.cpp:191 */
void CNavArea::Save(FILE *fp) const
{
	fprintf(fp, "v  %f %f %f\n", m_extent.lo.x, m_extent.lo.y, m_extent.lo.z);
	fprintf(fp, "v  %f %f %f\n", m_extent.hi.x, m_extent.lo.y, m_neZ);
	fprintf(fp, "v  %f %f %f\n", m_extent.hi.x, m_extent.hi.y, m_extent.hi.z);
	fprintf(fp, "v  %f %f %f\n", m_extent.lo.x, m_extent.hi.y, m_swZ);

	static int base = 1;
	fprintf(fp, "\n\ng %04dArea%s%s%s%s\n",
		m_id,
		(GetAttributes() & NAV_CROUCH) ? "CROUCH" : "",
		(GetAttributes() & NAV_JUMP) ? "JUMP" : "",
		(GetAttributes() & NAV_PRECISE) ? "PRECISE" : "",
		(GetAttributes() & NAV_NO_JUMP) ? "NO_JUMP" : ""
	);

	fprintf(fp, "f %d %d %d %d\n\n", base, base + 1, base + 2, base + 3);
	base += 4;
}

/* <4f09b8> ../game_shared/bot/nav_file.cpp:212 */
NOBODY void CNavArea::Save(int fd, unsigned int version)
{
	// save ID
	Q_write(fd, &m_id, sizeof(unsigned int));

	// save attribute flags
	Q_write(fd, &m_attributeFlags, sizeof(unsigned char));

	// save extent of area
	Q_write(fd, &m_extent, 6 * sizeof(float));

	// save heights of implicit corners
	Q_write(fd, &m_neZ, sizeof(float));
	Q_write(fd, &m_swZ, sizeof(float));

	// save connections to adjacent areas
	// in the enum order NORTH, EAST, SOUTH, WEST
	for (int d = 0; d < NUM_DIRECTIONS; d++)
	{
		// save number of connections for this direction
		unsigned int count = m_connect[d].size();
		Q_write(fd, &count, sizeof(unsigned int));

		NavConnectList::const_iterator iter;
		for (iter = m_connect[d].begin(); iter != m_connect[d].end(); ++iter)
		{
			NavConnect connect = *iter;
			Q_write(fd, &connect.area->m_id, sizeof(unsigned int));
		}
	}

	//
	// Store hiding spots for this area
	//
	unsigned char count;
	if (m_hidingSpotList.size() > 255)
	{
		count = 255;
		CONSOLE_ECHO("Warning: NavArea #%d: Truncated hiding spot list to 255\n", m_id);
	}
	else
	{
		count = m_hidingSpotList.size();
	}

	Q_write(fd, &count, sizeof(unsigned char));

	// store HidingSpot objects
	unsigned int saveCount = 0;
	for (HidingSpotList::iterator iter = m_hidingSpotList.begin(); iter != m_hidingSpotList.end(); ++iter)
	{
		HidingSpot *spot = *iter;

		spot->Save(fd, version);

		// overflow check
		if (++saveCount == count)
			break;
	}

	//
	// Save the approach areas for this area
	//

	// save number of approach areas
	Q_write(fd, &m_approachCount, sizeof(unsigned char));
	if (cv_bot_debug.value > 0.0f)
		CONSOLE_ECHO("  m_approachCount = %d\n", m_approachCount);

	// save approach area info
	unsigned char type;
	unsigned int zero = 0;
	for (int a = 0; a < m_approachCount; ++a)
	{
		if (m_approach[a].here.area)
			Q_write(fd, &m_approach[a].here.area->m_id, sizeof(unsigned int));
		else
			Q_write(fd, &zero, sizeof(unsigned int));

		if (m_approach[a].prev.area)
			Q_write(fd, &m_approach[a].prev.area->m_id, sizeof(unsigned int));
		else
			Q_write(fd, &zero, sizeof(unsigned int));

		type = (unsigned char)m_approach[a].prevToHereHow;
		Q_write(fd, &type, sizeof(unsigned char));

		if (m_approach[a].next.area)
			Q_write(fd, &m_approach[a].next.area->m_id, sizeof(unsigned int));
		else
			Q_write(fd, &zero, sizeof(unsigned int));

		type = (unsigned char)m_approach[a].hereToNextHow;
		Q_write(fd, &type, sizeof(unsigned char));
	}

	//
	// Save encounter spots for this area
	//
	{
		// save number of encounter paths for this area
		unsigned int count = m_spotEncounterList.size();
		Q_write(fd, &count, sizeof(unsigned int));

		if (cv_bot_debug.value > 0.0f)
			CONSOLE_ECHO("  m_spotEncounterList.size() = %d\n", count);

		SpotEncounter *e;
		for (SpotEncounterList::iterator iter = m_spotEncounterList.begin(); iter != m_spotEncounterList.end(); ++iter)
		{
			e = &(*iter);

			if (e->from.area)
				Q_write(fd, &e->from.area->m_id, sizeof(unsigned int));
			else
				Q_write(fd, &zero, sizeof(unsigned int));

			unsigned char dir = e->fromDir;
			Q_write(fd, &dir, sizeof(unsigned char));

			if (e->to.area)
				Q_write(fd, &e->to.area->m_id, sizeof(unsigned int));
			else
				Q_write(fd, &zero, sizeof(unsigned int));

			dir = e->toDir;
			Q_write(fd, &dir, sizeof(unsigned char));

			// write list of spots along this path
			unsigned char spotCount;
			if (e->spotList.size() > 255)
			{
				spotCount = 255;
				CONSOLE_ECHO("Warning: NavArea #%d: Truncated encounter spot list to 255\n", m_id);
			}
			else
			{
				spotCount = e->spotList.size();
			}
			Q_write(fd, &spotCount, sizeof(unsigned char));

			saveCount = 0;
			for (SpotOrderList::iterator oiter = e->spotList.begin(); oiter != e->spotList.end(); ++oiter)
			{
				SpotOrder *order = &(*oiter);

				// order->spot may be NULL if we've loaded a nav mesh that has been edited but not re-analyzed
				unsigned int id = (order->spot) ? order->spot->GetID() : 0;
				Q_write(fd, &id, sizeof(unsigned int));

				unsigned char t = 255 * order->t;
				Q_write(fd, &t, sizeof(unsigned char));

				// overflow check
				if (++saveCount == spotCount)
					break;
			}
		}
	}

	// store place dictionary entry
	PlaceDirectory::EntryType entry = placeDirectory.GetEntry(GetPlace());
	Q_write(fd, &entry, sizeof(entry));
}

/* <4ee669> ../game_shared/bot/nav_file.cpp:379 */
NOBODY void CNavArea::Load(SteamFile *file, unsigned int version)
{
	// load ID
	file->Read(&m_id, sizeof(unsigned int));

	// update nextID to avoid collisions
	if (m_id >= IMPLEMENT_ARRAY(m_nextID))
		IMPLEMENT_ARRAY(m_nextID) = m_id + 1;

	// load attribute flags
	file->Read(&m_attributeFlags, sizeof(unsigned char));

	// load extent of area
	file->Read(&m_extent, 6 * sizeof(float));

	m_center.x = (m_extent.lo.x + m_extent.hi.x) / 2.0f;
	m_center.y = (m_extent.lo.y + m_extent.hi.y) / 2.0f;
	m_center.z = (m_extent.lo.z + m_extent.hi.z) / 2.0f;

	// load heights of implicit corners
	file->Read(&m_neZ, sizeof(float));
	file->Read(&m_swZ, sizeof(float));

	// load connections (IDs) to adjacent areas
	// in the enum order NORTH, EAST, SOUTH, WEST
	for (int d = 0; d < NUM_DIRECTIONS; d++)
	{
		// load number of connections for this direction
		unsigned int count;
		file->Read(&count, sizeof(unsigned int));

		for (unsigned int i = 0; i<count; ++i)
		{
			NavConnect connect;
			file->Read(&connect.id, sizeof(unsigned int));

			m_connect[d].push_back(connect);
		}
	}

	//
	// Load hiding spots
	//

	// load number of hiding spots
	unsigned char hidingSpotCount;
	file->Read(&hidingSpotCount, sizeof(unsigned char));

	if (version == 1)
	{
		// load simple vector array
		Vector pos;
		for (int h = 0; h < hidingSpotCount; ++h)
		{
			file->Read(&pos, 3 * sizeof(float));

			// create new hiding spot and put on master list
			HidingSpot *spot = new HidingSpot(&pos, HidingSpot::IN_COVER);

			m_hidingSpotList.push_back(spot);
		}
	}
	else
	{
		// load HidingSpot objects for this area
		for (int h=0; h<hidingSpotCount; ++h)
		{
			// create new hiding spot and put on master list
			HidingSpot *spot = new HidingSpot;

			spot->Load(file, version);

			m_hidingSpotList.push_back(spot);
		}
	}

	//
	// Load number of approach areas
	//
	file->Read(&m_approachCount, sizeof(unsigned char));

	// load approach area info (IDs)
	unsigned char type;
	for (int a = 0; a < m_approachCount; ++a)
	{
		file->Read(&m_approach[a].here.id, sizeof(unsigned int));

		file->Read(&m_approach[a].prev.id, sizeof(unsigned int));
		file->Read(&type, sizeof(unsigned char) );
		m_approach[a].prevToHereHow = (NavTraverseType)type;

		file->Read(&m_approach[a].next.id, sizeof(unsigned int));
		file->Read(&type, sizeof(unsigned char));
		m_approach[a].hereToNextHow = (NavTraverseType)type;
	}

	//
	// Load encounter paths for this area
	//
	unsigned int count;
	file->Read(&count, sizeof(unsigned int));

	if (version < 3)
	{
		// old data, read and discard
		for (unsigned int e = 0; e < count; ++e)
		{
			SpotEncounter encounter;

			file->Read(&encounter.from.id, sizeof(unsigned int));
			file->Read(&encounter.to.id, sizeof(unsigned int));

			file->Read(&encounter.path.from.x, 3 * sizeof(float));
			file->Read(&encounter.path.to.x, 3 * sizeof(float));

			// read list of spots along this path
			unsigned char spotCount;
			file->Read(&spotCount, sizeof(unsigned char));

			for (int s = 0; s < spotCount; ++s)
			{
				Vector pos;
				file->Read(&pos, 3 * sizeof(float));
				file->Read(&pos, sizeof(float));
			}
		}
		return;
	}

	for (unsigned int e = 0; e<count; ++e)
	{
		SpotEncounter encounter;

		file->Read(&encounter.from.id, sizeof(unsigned int));

		unsigned char dir;
		file->Read(&dir, sizeof(unsigned char));
		encounter.fromDir = static_cast<NavDirType>(dir);

		file->Read(&encounter.to.id, sizeof(unsigned int));

		file->Read(&dir, sizeof(unsigned char));
		encounter.toDir = static_cast<NavDirType>(dir);

		// read list of spots along this path
		unsigned char spotCount;
		file->Read(&spotCount, sizeof(unsigned char));

		SpotOrder order;
		for (int s = 0; s < spotCount; ++s)
		{
			file->Read(&order.id, sizeof(unsigned int));

			unsigned char t;
			file->Read(&t, sizeof(unsigned char));

			order.t = (float)t / 255.0f;

			encounter.spotList.push_back(order);
		}

		m_spotEncounterList.push_back(encounter);
	}

	if (version < 5)
		return;

	//
	// Load Place data
	//
	PlaceDirectory::EntryType entry;
	file->Read(&entry, sizeof(entry));

	// convert entry to actual Place
	SetPlace(placeDirectory.EntryToPlace(entry));
}

/* <4f029e> ../game_shared/bot/nav_file.cpp:562 */
NOBODY NavErrorType CNavArea::PostLoad(void)
{
	NavErrorType error = NAV_OK;

	// connect areas together
	for (int d = 0; d < NUM_DIRECTIONS; d++)
	{
		NavConnectList::iterator iter;
		for (iter = m_connect[d].begin(); iter != m_connect[d].end(); ++iter)
		{
			NavConnect *connect = &(*iter);

			unsigned int id = connect->id;
			connect->area = TheNavAreaGrid.GetNavAreaByID(id);
			if (id && connect->area == NULL)
			{
				CONSOLE_ECHO("ERROR: Corrupt navigation data. Cannot connect Navigation Areas.\n");
				error = NAV_CORRUPT_DATA;
			}
		}
	}

	// resolve approach area IDs
	for (int a = 0; a < m_approachCount; ++a)
	{
		m_approach[a].here.area = TheNavAreaGrid.GetNavAreaByID(m_approach[a].here.id);
		if (m_approach[a].here.id && m_approach[a].here.area == NULL)
		{
			CONSOLE_ECHO("ERROR: Corrupt navigation data. Missing Approach Area (here).\n");
			error = NAV_CORRUPT_DATA;
		}

		m_approach[a].prev.area = TheNavAreaGrid.GetNavAreaByID(m_approach[a].prev.id);
		if (m_approach[a].prev.id && m_approach[a].prev.area == NULL)
		{
			CONSOLE_ECHO("ERROR: Corrupt navigation data. Missing Approach Area (prev).\n");
			error = NAV_CORRUPT_DATA;
		}

		m_approach[a].next.area = TheNavAreaGrid.GetNavAreaByID(m_approach[a].next.id);
		if (m_approach[a].next.id && m_approach[a].next.area == NULL)
		{
			CONSOLE_ECHO("ERROR: Corrupt navigation data. Missing Approach Area (next).\n");
			error = NAV_CORRUPT_DATA;
		}
	}

	// resolve spot encounter IDs
	SpotEncounter *e;
	for (SpotEncounterList::iterator iter = m_spotEncounterList.begin(); iter != m_spotEncounterList.end(); ++iter)
	{
		e = &(*iter);

		e->from.area = TheNavAreaGrid.GetNavAreaByID(e->from.id);
		if (e->from.area == NULL)
		{
			CONSOLE_ECHO("ERROR: Corrupt navigation data. Missing \"from\" Navigation Area for Encounter Spot.\n");
			error = NAV_CORRUPT_DATA;
		}

		e->to.area = TheNavAreaGrid.GetNavAreaByID(e->to.id);
		if (e->to.area == NULL)
		{
			CONSOLE_ECHO("ERROR: Corrupt navigation data. Missing \"to\" Navigation Area for Encounter Spot.\n");
			error = NAV_CORRUPT_DATA;
		}

		if (e->from.area && e->to.area)
		{
			// compute path
			float halfWidth;
			ComputePortal(e->to.area, e->toDir, &e->path.to, &halfWidth);
			ComputePortal(e->from.area, e->fromDir, &e->path.from, &halfWidth);

			const float eyeHeight = HalfHumanHeight;
			e->path.from.z = e->from.area->GetZ(&e->path.from) + eyeHeight;
			e->path.to.z = e->to.area->GetZ(&e->path.to) + eyeHeight;
		}

		// resolve HidingSpot IDs
		for (SpotOrderList::iterator oiter = e->spotList.begin(); oiter != e->spotList.end(); ++oiter)
		{
			SpotOrder *order = &(*oiter);

			order->spot = GetHidingSpotByID(order->id);
			if (order->spot == NULL)
			{
				CONSOLE_ECHO("ERROR: Corrupt navigation data. Missing Hiding Spot\n");
				error = NAV_CORRUPT_DATA;
			}
		}
	}

	// build overlap list
	/// @todo Optimize this
	for (NavAreaList::iterator oiter = TheNavAreaList.begin(); oiter != TheNavAreaList.end(); ++oiter)
	{
		CNavArea *area = *oiter;

		if (area == this)
			continue;

		if (IsOverlapping(area))
			m_overlapList.push_back(area);
	}

	return error;
}


/* <4edbe0> ../game_shared/bot/nav_file.cpp:680 */
void COM_FixSlashes(char *pname)
{
#ifdef _WIN32
	while (*pname)
	{
		if (*pname == '/')
			*pname = '\\';
		pname++;
	}
#else
	while (*pname)
	{
		if (*pname == '\\')
			*pname = '/';
		pname++;
	}
#endif // _WIN32
}

/* <4f3e47> ../game_shared/bot/nav_file.cpp:702 */
NOBODY bool SaveNavigationMap(const char *filename)
{
	if (filename == NULL)
		return false;

	//
	// Store the NAV file
	//
	COM_FixSlashes(const_cast<char *>(filename));

#ifdef WIN32
	int fd = _open(filename, _O_BINARY | _O_CREAT | _O_WRONLY, _S_IREAD | _S_IWRITE);
#else
	int fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP);
#endif // WIN32

	if (fd < 0)
		return false;

	// store "magic number" to help identify this kind of file
	unsigned int magic = NAV_MAGIC_NUMBER;
	Q_write(fd, &magic, sizeof(unsigned int));

	// store version number of file
	// 1 = hiding spots as plain vector array
	// 2 = hiding spots as HidingSpot objects
	// 3 = Encounter spots use HidingSpot ID's instead of storing vector again
	// 4 = Includes size of source bsp file to verify nav data correlation
	// ---- Beta Release at V4 -----
	// 5 = Added Place info
	unsigned int version = 5;
	Q_write(fd, &version, sizeof(unsigned int));

	// get size of source bsp file and store it in the nav file
	// so we can test if the bsp changed since the nav file was made
	char *bspFilename = GetBspFilename(filename);
	if (bspFilename == NULL)
		return false;

	unsigned int bspSize = (unsigned int)GET_FILE_SIZE(bspFilename);
	CONSOLE_ECHO("Size of bsp file '%s' is %u bytes.\n", bspFilename, bspSize);

	Q_write(fd, &bspSize, sizeof(unsigned int));

	//
	// Build a directory of the Places in this map
	//
	placeDirectory.Reset();

	NavAreaList::iterator it;
	for (it = TheNavAreaList.begin(); it != TheNavAreaList.end(); ++it)
	{
		CNavArea *area = *it;
		Place place = area->GetPlace();

		if (place)
		{
			placeDirectory.AddPlace(place);
		}
	}

	placeDirectory.Save(fd);

	//
	// Store navigation areas
	//

	// store number of areas
	unsigned int count = TheNavAreaList.size();
	Q_write(fd, &count, sizeof(unsigned int));

	// store each area
	for (it = TheNavAreaList.begin(); it != TheNavAreaList.end(); ++it)
	{
		CNavArea *area = *it;
		area->Save(fd, version);
	}

	Q_close(fd);

#ifdef _WIN32
	// output a simple Wavefront file to visualize the generated areas in 3DSMax
	FILE *fp = fopen("c:\\tmp\\nav.obj", "w");
	if (fp)
	{
		for (NavAreaList::iterator iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
		{
			(*iter)->Save(fp);
		}

		fclose(fp);
	}
#endif // _WIN32

	return true;
}

/* <4f169d> ../game_shared/bot/nav_file.cpp:811 */
NOBODY void LoadLocationFile(const char *filename)
{
	char locFilename[256];
	Q_strcpy(locFilename, filename);

	char *dot = Q_strchr(locFilename, '.');
	if (dot)
	{
		Q_strcpy(dot, ".loc");

		int locDataLength;
		char *locDataFile = (char *)LOAD_FILE_FOR_ME(const_cast<char *>(locFilename), &locDataLength);
		char *locData = locDataFile;

		if (locData)
		{
			CONSOLE_ECHO("Loading legacy 'location file' '%s'\n", locFilename);

			// read directory
			locData = MP_COM_Parse(locData);
			int dirSize = Q_atoi(MP_COM_GetToken());

			if (dirSize)
			{
				std::vector<unsigned int> directory;
				directory.reserve(dirSize);

				for (int i = 0; i < dirSize; ++i)
				{
					locData = MP_COM_Parse(locData);
					directory.push_back(TheBotPhrases->NameToID(MP_COM_GetToken()));
				}

				// read places for each nav area
				unsigned int areaID, locDirIndex;
				while (true)
				{
					locData = MP_COM_Parse(locData);
					if (locData == NULL)
						break;

					areaID = Q_atoi(MP_COM_GetToken());

					locData = MP_COM_Parse(locData);
					locDirIndex = Q_atoi(MP_COM_GetToken());

					CNavArea *area = TheNavAreaGrid.GetNavAreaByID(areaID);
					unsigned int place = (locDirIndex > 0) ? directory[locDirIndex - 1] : UNDEFINED_PLACE;

					if (area)
						area->SetPlace(place);
				}
			}

			FREE_FILE(locDataFile);
		}
	}
}

/* <4f05c5> ../game_shared/bot/nav_file.cpp:876 */
NOBODY void SanityCheckNavigationMap(const char *mapName)
{
	if (!mapName)
	{
		CONSOLE_ECHO("ERROR: navigation file not specified.\n");
		return;
	}

	// nav filename is derived from map filename
	const int BufLen = 4096;
	char bspFilename[BufLen];
	char navFilename[BufLen];

	Q_snprintf(bspFilename, BufLen, "maps\\%s.bsp", mapName);
	Q_snprintf(navFilename, BufLen, "maps\\%s.nav", mapName);

	SteamFile navFile(navFilename);

	if (!navFile.IsValid())
	{
		CONSOLE_ECHO("ERROR: navigation file %s does not exist.\n", navFilename);
		return;
	}

	// check magic number
	bool result;
	unsigned int magic;
	result = navFile.Read(&magic, sizeof(unsigned int));
	if (!result || magic != NAV_MAGIC_NUMBER)
	{
		CONSOLE_ECHO("ERROR: Invalid navigation file '%s'.\n", navFilename);
		return;
	}

	// read file version number
	unsigned int version;
	result = navFile.Read(&version, sizeof(unsigned int));
	if (!result || version > 5)
	{
		CONSOLE_ECHO("ERROR: Unknown version in navigation file %s.\n", navFilename);
		return;
	}

	if (version >= 4)
	{
		// get size of source bsp file and verify that the bsp hasn't changed
		unsigned int saveBspSize;
		navFile.Read(&saveBspSize, sizeof(unsigned int));

		// verify size
		if (bspFilename == NULL)
		{
			CONSOLE_ECHO("ERROR: No map corresponds to navigation file %s.\n", navFilename);
			return;
		}

		unsigned int bspSize = (unsigned int)GET_FILE_SIZE(bspFilename);

		if (bspSize != saveBspSize)
		{
			// this nav file is out of date for this bsp file
			CONSOLE_ECHO("ERROR: Out-of-date navigation data in navigation file %s.\n", navFilename);
			return;
		}
	}
	CONSOLE_ECHO("navigation file %s passes the sanity check.\n", navFilename);
}

void (*pLoadNavigationMap)(void);

/* <4f19c7> ../game_shared/bot/nav_file.cpp:947 */
NOBODY NavErrorType __declspec(naked) LoadNavigationMap(void)
{
	__asm
	{
		jmp pLoadNavigationMap
	}

	//// since the navigation map is destroyed on map change,
	//// if it exists it has already been loaded for this map
	//if (!TheNavAreaList.empty())
	//	return NAV_OK;

	//// nav filename is derived from map filename
	//char filename[256];
	//Q_sprintf(filename, "maps\\%s.nav", STRING(gpGlobals->mapname));

	//// free previous navigation map data
	//DestroyNavigationMap();
	//placeDirectory.Reset();

	//IMPLEMENT_ARRAY_CLASS(CNavArea, m_nextID) = 1;

	//SteamFile navFile(filename);

	//if (!navFile.IsValid())
	//	return NAV_CANT_ACCESS_FILE;

	//// check magic number
	//bool result;
	//unsigned int magic;
	//result = navFile.Read(&magic, sizeof(unsigned int));
	//if (!result || magic != NAV_MAGIC_NUMBER)
	//{
	//	CONSOLE_ECHO("ERROR: Invalid navigation file '%s'.\n", filename);
	//	return NAV_INVALID_FILE;
	//}

	//// read file version number
	//unsigned int version;
	//result = navFile.Read(&version, sizeof(unsigned int));
	//if (!result || version > 5)
	//{
	//	CONSOLE_ECHO("ERROR: Unknown navigation file version.\n");
	//	return NAV_BAD_FILE_VERSION;
	//}

	//if (version >= 4)
	//{
	//	// get size of source bsp file and verify that the bsp hasn't changed
	//	unsigned int saveBspSize;
	//	navFile.Read(&saveBspSize, sizeof(unsigned int));

	//	// verify size
	//	char *bspFilename = GetBspFilename(filename);
	//	if (bspFilename == NULL)
	//		return NAV_INVALID_FILE;

	//	unsigned int bspSize = (unsigned int)GET_FILE_SIZE(bspFilename);

	//	if (bspSize != saveBspSize)
	//	{
	//		// this nav file is out of date for this bsp file
	//		char *msg = "*** WARNING ***\nThe AI navigation data is from a different version of this map.\nThe CPU players will likely not perform well.\n";
	//		HintMessageToAllPlayers(msg);
	//		CONSOLE_ECHO("\n-----------------\n");
	//		CONSOLE_ECHO(msg);
	//		CONSOLE_ECHO("-----------------\n\n");
	//	}
	//}

	//// load Place directory
	//if (version >= 5)
	//{
	//	placeDirectory.Load(&navFile);
	//}

	//// get number of areas
	//unsigned int count;
	//result = navFile.Read(&count, sizeof(unsigned int));

	//Extent extent;
	//extent.lo.x = 9999999999.9f;
	//extent.lo.y = 9999999999.9f;
	//extent.hi.x = -9999999999.9f;
	//extent.hi.y = -9999999999.9f;

	//// load the areas and compute total extent
	//for (unsigned int i = 0; i < count; i++)
	//{
	//	CNavArea *area = new CNavArea;
	//	area->Load(&navFile, version);
	//	TheNavAreaList.push_back(area);

	//	const Extent *areaExtent = area->GetExtent();

	//	// check validity of nav area
	//	if (areaExtent->lo.x >= areaExtent->hi.x || areaExtent->lo.y >= areaExtent->hi.y)
	//		CONSOLE_ECHO("WARNING: Degenerate Navigation Area #%d at ( %g, %g, %g )\n",
	//			area->GetID(), area->m_center.x, area->m_center.y, area->m_center.z);

	//	if (areaExtent->lo.x < extent.lo.x)
	//		extent.lo.x = areaExtent->lo.x;

	//	if (areaExtent->lo.y < extent.lo.y)
	//		extent.lo.y = areaExtent->lo.y;

	//	if (areaExtent->hi.x > extent.hi.x)
	//		extent.hi.x = areaExtent->hi.x;

	//	if (areaExtent->hi.y > extent.hi.y)
	//		extent.hi.y = areaExtent->hi.y;
	//}

	//// add the areas to the grid
	//TheNavAreaGrid.Initialize(extent.lo.x, extent.hi.x, extent.lo.y, extent.hi.y);

	//NavAreaList::iterator iter;
	//for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	//	TheNavAreaGrid.AddNavArea(*iter);

	//// allow areas to connect to each other, etc
	//for (iter = TheNavAreaList.begin(); iter != TheNavAreaList.end(); ++iter)
	//{
	//	CNavArea *area = *iter;
	//	area->PostLoad();
	//}

	//// load legacy location file (Places)
	//if (version < 5)
	//{
	//	LoadLocationFile(filename);
	//}

	////
	//// Set up all the ladders
	////
	//BuildLadders();

	//return NAV_OK;
}
