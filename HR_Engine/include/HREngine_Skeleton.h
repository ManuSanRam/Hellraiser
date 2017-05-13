#pragma once

#include "HREngine_Prerequisites.h"
#include "HREngine_Joint.h"

namespace HR_SDK
{
	class HR_ENGINE_EXPORT C_Skeleton
	{
	public:
		C_Skeleton()
		{

		}

		~C_Skeleton()
		{

		}

		Vector<C_Joint> m_SkeletonJoints;
	};
}