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

#ifndef UTLMEMORY_H
#define UTLMEMORY_H

#ifdef _WIN32
#pragma once
#endif

#include "osconfig.h"
#include "tier0/dbg.h"
#include <string.h>

#pragma warning (disable:4100)
#pragma warning (disable:4514)

/*template <class T> 
inline void Construct(T *pMemory)
{
	::new(pMemory) T;
}

template <class T> 
inline void CopyConstruct(T *pMemory,T const& src)
{
	::new(pMemory) T(src);
}

template <class T> 
inline void Destruct(T *pMemory)
{
	pMemory->~T();

#ifdef _DEBUG
	memset(pMemory,0xDD,sizeof(T));
#endif
}*/
//-----------------------------------------------------------------------------
// The CUtlMemory class:
// A growable memory class which doubles in size by default.
//-----------------------------------------------------------------------------
template< class T >
class CUtlMemory
{
public:
	// constructor, destructor
	CUtlMemory(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemory(T* pMemory, int numElements);
	~CUtlMemory();

	// element access
	T& operator[](int i);
	T const& operator[](int i) const;
	T& Element(int i);
	T const& Element(int i) const;

	// Can we use this index?
	bool IsIdxValid(int i) const;

	// Gets the base address (can change when adding elements!)
	T* Base();
	T const* Base() const;

	// Attaches the buffer to external memory....
	void SetExternalBuffer(T* pMemory, int numElements);

	// Size
	int NumAllocated() const;
	int Count() const;

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

	// is the memory externally allocated?
	bool IsExternallyAllocated() const;

	// Set the size by which the memory grows
	void SetGrowSize(int size);

private:
	enum
	{
		EXTERNAL_BUFFER_MARKER = -1,
	};

	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};


//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
template< class T >
CUtlMemory<T>::CUtlMemory(int nGrowSize, int nInitAllocationCount) : m_pMemory(0),
m_nAllocationCount(nInitAllocationCount), m_nGrowSize(nGrowSize)
{
	Assert((nGrowSize >= 0) && (nGrowSize != EXTERNAL_BUFFER_MARKER));
	if (m_nAllocationCount)
	{
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}

template< class T >
CUtlMemory<T>::CUtlMemory(T* pMemory, int numElements) : m_pMemory(pMemory),
m_nAllocationCount(numElements)
{
	// Special marker indicating externally supplied memory
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template< class T >
CUtlMemory<T>::~CUtlMemory()
{
	Purge();
}


//-----------------------------------------------------------------------------
// Attaches the buffer to external memory....
//-----------------------------------------------------------------------------
template< class T >
void CUtlMemory<T>::SetExternalBuffer(T* pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	m_pMemory = pMemory;
	m_nAllocationCount = numElements;

	// Indicate that we don't own the memory
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}


//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< class T >
inline T& CUtlMemory<T>::operator[](int i)
{
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T >
inline T const& CUtlMemory<T>::operator[](int i) const
{
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T >
inline T& CUtlMemory<T>::Element(int i)
{
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T >
inline T const& CUtlMemory<T>::Element(int i) const
{
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}


//-----------------------------------------------------------------------------
// is the memory externally allocated?
//-----------------------------------------------------------------------------
template< class T >
bool CUtlMemory<T>::IsExternallyAllocated() const
{
	return m_nGrowSize == EXTERNAL_BUFFER_MARKER;
}


template< class T >
void CUtlMemory<T>::SetGrowSize(int nSize)
{
	Assert((nSize >= 0) && (nSize != EXTERNAL_BUFFER_MARKER));
	m_nGrowSize = nSize;
}


//-----------------------------------------------------------------------------
// Gets the base address (can change when adding elements!)
//-----------------------------------------------------------------------------
template< class T >
inline T* CUtlMemory<T>::Base()
{
	return m_pMemory;
}

template< class T >
inline T const* CUtlMemory<T>::Base() const
{
	return m_pMemory;
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
template< class T >
inline int CUtlMemory<T>::NumAllocated() const
{
	return m_nAllocationCount;
}

template< class T >
inline int CUtlMemory<T>::Count() const
{
	return m_nAllocationCount;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< class T >
inline bool CUtlMemory<T>::IsIdxValid(int i) const
{
	return (i >= 0) && (i < m_nAllocationCount);
}


//-----------------------------------------------------------------------------
// Grows the memory
//-----------------------------------------------------------------------------
template< class T >
void CUtlMemory<T>::Grow(int num)
{
	Assert(num > 0);

	if (IsExternallyAllocated())
	{
		// Can't grow a buffer whose memory was externally allocated 
		Assert(0);
		return;
	}

	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in m_nGrowSize)
	int nAllocationRequested = m_nAllocationCount + num;
	while (m_nAllocationCount < nAllocationRequested)
	{
		if (m_nAllocationCount != 0)
		{
			if (m_nGrowSize)
			{
				m_nAllocationCount += m_nGrowSize;
			}
			else
			{
				m_nAllocationCount += m_nAllocationCount;
			}
		}
		else
		{
			// Compute an allocation which is at least as big as a cache line...
			m_nAllocationCount = (31 + sizeof(T)) / sizeof(T);
			Assert(m_nAllocationCount != 0);
		}
	}

	if (m_pMemory)
	{
		m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
	}
	else
	{
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}


//-----------------------------------------------------------------------------
// Makes sure we've got at least this much memory
//-----------------------------------------------------------------------------
template< class T >
inline void CUtlMemory<T>::EnsureCapacity(int num)
{
	if (m_nAllocationCount >= num)
		return;

	if (IsExternallyAllocated())
	{
		// Can't grow a buffer whose memory was externally allocated 
		Assert(0);
		return;
	}

	m_nAllocationCount = num;
	if (m_pMemory)
	{
		m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
	}
	else
	{
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T >
void CUtlMemory<T>::Purge()
{
	if (!IsExternallyAllocated())
	{
		if (m_pMemory)
		{
			free((void*)m_pMemory);
			m_pMemory = 0;
		}
		m_nAllocationCount = 0;
	}
}

#endif // UTLMEMORY_H
