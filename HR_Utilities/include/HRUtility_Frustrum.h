#pragma once

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Plane.h"

namespace HR_SDK
{
	class HR_UTILITY_EXPORT C_Frustrum
	{
	public:
		C_Plane m_FrustrumPlanes[6];
	};
}