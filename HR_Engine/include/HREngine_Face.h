#pragma once

#include "HREngine_Prerequisites.h"

namespace HR_SDK
{
	class HR_ENGINE_EXPORT C_Face
	{
	public:
		C_Face()
		{

		}

		~C_Face()
		{

		}

		S_Vertex m_FaceVertices[3];
		C_Vector3D m_FaceNormal;
		//! Material ID
	};
}