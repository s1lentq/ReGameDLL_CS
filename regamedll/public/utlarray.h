/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#pragma once

// A growable array class that maintains a free list and keeps elements
// in the same location
#include "tier0/platform.h"
#include "tier0/dbg.h"

#define FOR_EACH_ARRAY(vecName, iteratorName)\
	for (int iteratorName = 0; (vecName).IsUtlArray && iteratorName < (vecName).Count(); iteratorName++)

#define FOR_EACH_ARRAY_BACK(vecName, iteratorName)\
	for (int iteratorName = (vecName).Count() - 1; (vecName).IsUtlArray && iteratorName >= 0; iteratorName--)

template <class T, size_t MAX_SIZE>
class CUtlArray
{
public:
	typedef T ElemType_t;
	enum { IsUtlArray = true }; // Used to match this at compiletime

	CUtlArray();
	CUtlArray(T *pMemory, size_t count);
	~CUtlArray();

	CUtlArray<T, MAX_SIZE> &operator=(const CUtlArray<T, MAX_SIZE> &other);
	CUtlArray(CUtlArray const &vec);

	// element access
	T &operator[](int i);
	const T &operator[](int i) const;
	T &Element(int i);
	const T &Element(int i) const;
	T &Random();
	const T &Random() const;

	T *Base();
	const T *Base() const;

	// Returns the number of elements in the array, NumAllocated() is included for consistency with UtlVector
	int Count() const;
	int NumAllocated() const;

	// Is element index valid?
	bool IsValidIndex(int i) const;
	static int InvalidIndex();

	void CopyArray(const T *pArray, size_t count);

	void Clear();
	void RemoveAll();
	void Swap(CUtlArray< T, MAX_SIZE> &vec);

	// Finds an element (element needs operator== defined)
	int Find(const T &src) const;
	void FillWithValue(const T &src);

	bool HasElement(const T &src) const;

protected:
	T m_Memory[MAX_SIZE];
};

// Constructor
template <typename T, size_t MAX_SIZE>
inline CUtlArray<T, MAX_SIZE>::CUtlArray()
{
}

template <typename T, size_t MAX_SIZE>
inline CUtlArray<T, MAX_SIZE>::CUtlArray(T *pMemory, size_t count)
{
	CopyArray(pMemory, count);
}

// Destructor
template <typename T, size_t MAX_SIZE>
inline CUtlArray<T, MAX_SIZE>::~CUtlArray()
{
}

template <typename T, size_t MAX_SIZE>
inline CUtlArray<T, MAX_SIZE> &CUtlArray<T, MAX_SIZE>::operator=(const CUtlArray<T, MAX_SIZE> &other)
{
	if (this != &other)
	{
		for (size_t n = 0; n < MAX_SIZE; n++)
			m_Memory[n] = other.m_Memory[n];
	}

	return *this;
}

template <typename T, size_t MAX_SIZE>
inline CUtlArray<T, MAX_SIZE>::CUtlArray(CUtlArray const &vec)
{
	for (size_t n = 0; n < MAX_SIZE; n++)
		m_Memory[n] = vec.m_Memory[n];
}

template <typename T, size_t MAX_SIZE>
inline T *CUtlArray<T, MAX_SIZE>::Base()
{
	return &m_Memory[0];
}

template <typename T, size_t MAX_SIZE>
inline const T *CUtlArray<T, MAX_SIZE>::Base() const
{
	return &m_Memory[0];
}

// Element access
template <typename T, size_t MAX_SIZE>
inline T &CUtlArray<T, MAX_SIZE>::operator[](int i)
{
	Assert(IsValidIndex(i));
	return m_Memory[i];
}

template <typename T, size_t MAX_SIZE>
inline const T &CUtlArray<T, MAX_SIZE>::operator[](int i) const
{
	Assert(IsValidIndex(i));
	return m_Memory[i];
}

template <typename T, size_t MAX_SIZE>
inline T &CUtlArray<T, MAX_SIZE>::Element(int i)
{
	Assert(IsValidIndex(i));
	return m_Memory[i];
}

template <typename T, size_t MAX_SIZE>
inline const T &CUtlArray<T, MAX_SIZE>::Element(int i) const
{
	Assert(IsValidIndex(i));
	return m_Memory[i];
}

// Count
template <typename T, size_t MAX_SIZE>
inline int CUtlArray<T, MAX_SIZE>::Count() const
{
	return (int)MAX_SIZE;
}

template <typename T, size_t MAX_SIZE>
inline int CUtlArray<T, MAX_SIZE>::NumAllocated() const
{
	return (int)MAX_SIZE;
}

// Is element index valid?
template <typename T, size_t MAX_SIZE>
inline bool CUtlArray<T, MAX_SIZE>::IsValidIndex(int i) const
{
	return (i >= 0) && (i < MAX_SIZE);
}

// Returns in invalid index
template <typename T, size_t MAX_SIZE>
inline int CUtlArray<T, MAX_SIZE>::InvalidIndex()
{
	return -1;
}

template <typename T, size_t MAX_SIZE>
void CUtlArray<T, MAX_SIZE>::CopyArray(const T *pArray, size_t count)
{
	Assert(count < MAX_SIZE);

	for (size_t n = 0; n < count; n++)
		m_Memory[n] = pArray[n];
}

template <typename T, size_t MAX_SIZE>
void CUtlArray<T, MAX_SIZE>::Clear()
{
	Q_memset(m_Memory, 0, MAX_SIZE * sizeof(T));
}

template <typename T, size_t MAX_SIZE>
void CUtlArray<T, MAX_SIZE>::RemoveAll()
{
	Clear();
}

template <typename T, size_t MAX_SIZE>
void CUtlArray<T, MAX_SIZE>::Swap(CUtlArray< T, MAX_SIZE> &vec)
{
	for (size_t n = 0; n < MAX_SIZE; n++)
		SWAP(m_Memory[n], vec.m_Memory[n]);
}

// Finds an element (element needs operator== defined)
template <typename T, size_t MAX_SIZE>
int CUtlArray<T, MAX_SIZE>::Find(const T &src) const
{
	for (int i = 0; i < Count(); i++)
	{
		if (Element(i) == src)
			return i;
	}

	return -1;
}

template <typename T, size_t MAX_SIZE>
void CUtlArray<T, MAX_SIZE>::FillWithValue(const T &src)
{
	for (int i = 0; i < Count(); i++)
		Element(i) = src;
}

template <typename T, size_t MAX_SIZE>
bool CUtlArray<T, MAX_SIZE>::HasElement(const T &src) const
{
	return (Find(src) >= 0);
}
