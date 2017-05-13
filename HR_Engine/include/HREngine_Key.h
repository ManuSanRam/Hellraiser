#pragma once

#include "HREngine_Prerequisites.h"
#include <HRUtility_Vector3D.h>
#include <HRUtility_Matrix4.h>

namespace HR_SDK
{
	class HR_ENGINE_EXPORT C_Key
	{
	public:
		C_Key()
		{

		}

		~C_Key()
		{

		}

		C_Vector3D		m_Position;
		C_Matrix4		m_Rotation;
		C_Matrix4		m_Scale;
		float			m_Time;
	};
}
