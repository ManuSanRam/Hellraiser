#pragma once

#include "HREngine_Prerequisites.h"

#include "HREngine_Mesh.h"
#include "HREngine_Material.h"

namespace HR_SDK
{
	class HR_ENGINE_EXPORT C_Model
	{
	public:
		C_Model()
		{

		}

		~C_Model()
		{

		}

		bool Init(const String& prm_FileName);

		void Render();
		void Close();

		Vector<C_Mesh>		m_Meshes;
		Vector<C_Material>	m_Materials;
	};
}