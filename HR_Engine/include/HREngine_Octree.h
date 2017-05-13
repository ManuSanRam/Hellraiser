#pragma once

#include "HREngine_Prerequisites.h"
#include "HREngine_Node.h"
#include <HRUtility_AABB.h>

namespace HR_SDK
{
	/*!
	@brief Maximum faces generated of 
	*/
	#define MAX_FACES 3000
	/*!
	 * @brief Performs a space partition of models, divided in 8 nodes
	 * The nodes of the tree have 8 children, obeying the size of the tree.
	*/
	class HR_ENGINE_EXPORT C_Oct
	{
	public:
		//! Generate collection of models
		//! Create a unique list with all their info (faces, vertices, etc)
		/*!
		 * @brief Children of the oct object.
		*/
		C_BSPNode* m_Children[8];
		C_AABB m_BoundingBox;
	};
}
