#pragma once

#include "HRGraphics_Prerequisites.h"
#include <HRUtility_Matrix4.h>

namespace HR_SDK
{
	class HR_D3DGRAPHICSAPI_EXPORT C_ConstantType
	{
	public:
		C_ConstantType()
		{

		}

		C_ConstantType(const C_ConstantType& prm_CT)
		{
			this->m_View = prm_CT.m_View;
			this->m_World = prm_CT.m_World;
			this->m_Projection = prm_CT.m_Projection;
		}

		~C_ConstantType()
		{

		}

		C_Matrix4 GetWorldMatrix()
		{
			return m_World;
		}

		C_Matrix4 GetViewMatrix()
		{
			return m_View;
		}

		C_Matrix4 GetProjectionMatrix()
		{
			return m_Projection;
		}

		C_Matrix4 m_World;
		C_Matrix4 m_View;
		C_Matrix4 m_Projection;
	};
}
