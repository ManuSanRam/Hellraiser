#pragma once

#include "HREngine_Prerequisites.h"

#include <types.h>
#include <Importer.hpp>
#include <mesh.h>

#include <HRGraphics_Buffer.h>

using namespace Assimp;

namespace HR_SDK
{
	class HR_ENGINE_EXPORT C_Mesh
	{
	public:
		C_Mesh()
		{

		}

		~C_Mesh()
		{

		}

		bool Load(const String& prm_FileName, const aiScene& prm_ModelScene);

		bool Init();
		void Render();

		void Close();

		C_VBuffer*			m_VertexBuffer;
		C_IBuffer32*		m_IndexBuffer;
	};
}
