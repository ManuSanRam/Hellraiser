#pragma once

#include "HREngine_Prerequisites.h"

#include <types.h>
#include <Importer.hpp>
#include <mesh.h>

#include <HRGraphics_Buffer.h>
#include <HRGraphics_Shader.h>
#include <HRGraphics_InputLayout.h>

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

		bool CreateMeshFromFile();

		bool SetMesh();

		bool

		Importer*			m_ModelImporter;

		C_VBuffer*			m_VertexBuffer;
		C_IBuffer32*		m_IndexBuffer;

		C_VertexShader*		m_VShader;
		C_PixelShader*		m_PShader;

		C_InputLayout*		m_InputLayout;
	};
}
