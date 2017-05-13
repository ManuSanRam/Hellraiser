#pragma once

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"

namespace HR_SDK
{
	class HR_UTILITY_EXPORT C_Line
	{
		C_Line()
		{

		}

		~C_Line()
		{

		}

		void Set(C_Vector3D prm_Start, C_Vector3D prm_End);

		C_Vector3D m_Start;
		C_Vector3D m_End;

	};
}