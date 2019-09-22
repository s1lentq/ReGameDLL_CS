/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include "precompiled.h"

CMemoryPool::CMemoryPool(int blockSize, int numElements)
{
	_blocksPerBlob = numElements;
	_blockSize = blockSize;
	_numBlobs = 0;
	_numElements = 0;

	AddNewBlob();

	_peakAlloc = 0;
	_blocksAllocated = 0;
}

CMemoryPool::~CMemoryPool()
{
	for (int i = 0; i < _numBlobs; i++)
		free(_memBlob[i]);
}

void CMemoryPool::AddNewBlob()
{
	int sizeMultiplier = pow(2.0, _numBlobs);
	int nElements = _blocksPerBlob * sizeMultiplier;
	int blobSize = _blockSize * nElements;

	_memBlob[_numBlobs] = malloc(blobSize);

#ifdef _WIN32
	if (!_memBlob[_numBlobs])
		DebugBreak();
#endif // _WIN32

	_headOfFreeList = _memBlob[_numBlobs];

#ifdef _WIN32
	if (!_headOfFreeList)
		DebugBreak();
#endif // _WIN32

	void **newBlob = (void **)_headOfFreeList;
	for (int j = 0; j < nElements - 1; j++)
	{
		newBlob[0] = (char *)newBlob + _blockSize;
		newBlob = (void **)newBlob[0];
	}

	newBlob[0] = nullptr;

	_numElements += nElements;
	_numBlobs++;

#ifdef _WIN32
	if (_numBlobs >= MAX_BLOBS - 1)
		DebugBreak();
#endif // _WIN32

}

void *CMemoryPool::Alloc(unsigned int amount)
{
	void *returnBlock;
	if (amount > (unsigned int)_blockSize)
		return nullptr;

	_blocksAllocated++;
	_peakAlloc = Q_max(_peakAlloc, _blocksAllocated);

	if (_blocksAllocated >= _numElements)
		AddNewBlob();

#ifdef _WIN32
	if (!_headOfFreeList)
		DebugBreak();
#endif // _WIN32

	returnBlock = _headOfFreeList;
	_headOfFreeList = *((void **)_headOfFreeList);
	return returnBlock;
}

void CMemoryPool::Free(void *memblock)
{
	if (!memblock)
		return;

#ifdef _DEBUG
	Q_memset(memblock, 0xDD, _blockSize);
#endif // _DEBUG

	--_blocksAllocated;
	*((void **)memblock) = _headOfFreeList;
	_headOfFreeList = memblock;
}
