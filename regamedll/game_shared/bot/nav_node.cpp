#include "precompiled.h"

/*
* Globals initialization
*/
#ifndef HOOK_GAMEDLL

//NavDirType Opposite[ NUM_DIRECTIONS ] = { SOUTH, WEST, NORTH, EAST };

CNavNode *CNavNode::m_list = NULL;
unsigned int CNavNode::m_listLength = 0;

//Extent NodeMapExtent;

#else // HOOK_GAMEDLL

//NavDirType Opposite[ NUM_DIRECTIONS ];

CNavNode *IMPLEMENT_ARRAY_CLASS(CNavNode, m_list);
unsigned int IMPLEMENT_ARRAY_CLASS(CNavNode, m_listLength);

//Extent NodeMapExtent;

#endif // HOOK_GAMEDLL

/* <4f79dc> ../game_shared/bot/nav_node.cpp:23 */
CNavNode::CNavNode(const Vector *pos, const Vector *normal, class CNavNode *parent)
{
//	{
//		unsigned int nextID;                                  //    28
//		{
//			int i;                                        //    31
//		}
//	}
}

/* <4f7a31> ../game_shared/bot/nav_node.cpp:54 */
void CNavNode::ConnectTo(CNavNode *node, NavDirType dir)
{
}

/* <4f7a75> ../game_shared/bot/nav_node.cpp:64 */
const CNavNode *CNavNode::GetNode(const Vector *pos)
{
//	{
//		float const tolerance;                                 //    66
//		{
//			const class CNavNode *node;                 //    68
//			{
//				float dx;                             //    70
//				float dy;                             //    71
//				float dz;                             //    72
//			}
//		}
//	}
}

/* <4f7af2> ../game_shared/bot/nav_node.cpp:86 */
BOOL CNavNode::IsBiLinked(NavDirType dir) const
{
}

/* <4f7b1c> ../game_shared/bot/nav_node.cpp:100 */
BOOL CNavNode::IsClosedCell(void) const
{
//	IsBiLinked(const class CNavNode *const this,
//			enum NavDirType dir);  //   102
//	IsBiLinked(const class CNavNode *const this,
//			enum NavDirType dir);  //   103
//	IsBiLinked(const class CNavNode *const this,
//			enum NavDirType dir);  //   104
//	IsBiLinked(const class CNavNode *const this,
//			enum NavDirType dir);  //   105
}
