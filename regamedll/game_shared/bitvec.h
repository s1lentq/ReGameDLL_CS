/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef BITVEC_H
#define BITVEC_H
#ifdef _WIN32
#pragma once
#endif

class CBitVecAccessor
{
public:
	CBitVecAccessor(uint32 *pDWords, int iBit);

	void operator=(int val);
	operator uint32();

private:
	uint32 *m_pDWords;
	int m_iBit;

};/* size: 8, cachelines: 1, members: 2 */

// CBitVec allows you to store a list of bits and do operations on them like they were
// an atomic type
template<int NUM_BITS>
class CBitVec
{
public:
	CBitVec(void);

	// Set all values to the specified value (0 or 1..)
	void Init(int val = 0);

	// Access the bits like an array.
	CBitVecAccessor	operator[](int i);

	// Operations on other bit vectors.
	CBitVec &operator=(CBitVec<NUM_BITS> const &other);
	bool operator==(CBitVec<NUM_BITS> const &other);
	bool operator!=(CBitVec<NUM_BITS> const &other);

	// Get underlying dword representations of the bits.
	int GetNumDWords()
	{
		return NUM_DWORDS;
	}
	uint32 GetDWord(int i);
	void SetDWord(int i, uint32 val);
	int GetNumBits();

private:

	enum
	{
		NUM_DWORDS = NUM_BITS / 32 + !!(NUM_BITS & 31)
	};

	unsigned int m_DWords[ NUM_DWORDS ];

};/* size: 4, cachelines: 1, members: 1 */

/* <2d39f8> ../game_shared/bitvec.h:73 */
inline CBitVecAccessor::CBitVecAccessor(uint32 *pDWords, int iBit)
{
	m_pDWords = pDWords;
	m_iBit = iBit;
}

/* <2d37d7> ../game_shared/bitvec.h:80 */
inline void CBitVecAccessor::operator=(int val)
{
	if (val)
		m_pDWords[m_iBit >> 5] |= (1 << (m_iBit & 31));
	else
		m_pDWords[m_iBit >> 5] &= ~(uint32)(1 << (m_iBit & 31));
}

/* <2d3a63> ../game_shared/bitvec.h:88 */
inline CBitVecAccessor::operator uint32()
{
	return m_pDWords[m_iBit >> 5] & (1 << (m_iBit & 31));
}

/* <2d3ac9> ../game_shared/bitvec.h:100 */
template<int NUM_BITS>
inline int CBitVec<NUM_BITS>::GetNumBits()
{
	return NUM_BITS;
}

/* <2d39cf> ../game_shared/bitvec.h:107 */
template<int NUM_BITS>
inline CBitVec<NUM_BITS>::CBitVec()
{
	for (int i = 0; i < NUM_DWORDS; i++)
		m_DWords[i] = 0;
}

/* <2d3ae2> ../game_shared/bitvec.h:115 */
template<int NUM_BITS>
inline void CBitVec<NUM_BITS>::Init(int val)
{
	for (int i = 0; i < GetNumBits(); i++)
	{
		(*this)[i] = val;
	}
}

/* <2d3ba8> ../game_shared/bitvec.h:125 */
template<int NUM_BITS>
inline CBitVec<NUM_BITS> &CBitVec<NUM_BITS>::operator=(CBitVec<NUM_BITS> const &other)
{
	Q_memcpy(m_DWords, other.m_DWords, sizeof(m_DWords));
	return *this;
}

/* <2d3a41> ../game_shared/bitvec.h:133 */
template<int NUM_BITS>
inline CBitVecAccessor CBitVec<NUM_BITS>::operator[](int i)
{
	assert(i >= 0 && i < GetNumBits());
	return CBitVecAccessor(m_DWords, i);
}

/* <2d3b11> ../game_shared/bitvec.h:141 */
template<int NUM_BITS>
inline bool CBitVec<NUM_BITS>::operator==(CBitVec<NUM_BITS> const &other)
{
	for (int i = 0; i < NUM_DWORDS; i++)
	{
		if (m_DWords[i] != other.m_DWords[i])
			return false;
	}

	return true;
}

/* <2d3b7f> ../game_shared/bitvec.h:152 */
template<int NUM_BITS>
inline bool CBitVec<NUM_BITS>::operator!=(CBitVec<NUM_BITS> const &other)
{
	return !(*this == other);
}

/* <2d3bd1> ../game_shared/bitvec.h:165 */
template<int NUM_BITS>
inline uint32 CBitVec<NUM_BITS>::GetDWord(int i)
{
	assert(i >= 0 && i < NUM_DWORDS);
	return m_DWords[i];
}

/* <2d3a7d> ../game_shared/bitvec.h:173 */
template<int NUM_BITS>
inline void CBitVec<NUM_BITS>::SetDWord(int i, uint32 val)
{
	assert(i >= 0 && i < NUM_DWORDS);
	m_DWords[i] = val;
}

#endif // BITVEC_H
