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
	for (int i = 0; i < _numBlobs; ++i)
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
	for (int j = 0; j < nElements - 1; ++j)
	{
		newBlob[0] = (char *)newBlob + _blockSize;
		newBlob = (void **)newBlob[0];
	}

	newBlob[0] = NULL;

	_numElements += nElements;
	++_numBlobs;

#ifdef _WIN32
	if (_numBlobs >= MAX_BLOBS - 1)
		DebugBreak();
#endif // _WIN32

}

void *CMemoryPool::Alloc(unsigned int amount)
{
	void *returnBlock;
	if (amount > (unsigned int)_blockSize)
		return NULL;

	++_blocksAllocated;
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
