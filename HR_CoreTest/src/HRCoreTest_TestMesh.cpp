#include "HRCoreTest_TestMesh.h"

struct HR_SDK::GraphicsDevice
{
	void* GetPointer()
	{
		return reinterpret_cast<void*>(Device);
	}

	void** GetReference()
	{
		return reinterpret_cast<void**>(&Device);
	}

	ID3D11Device* Device;
};

struct HR_SDK::GraphicsDeviceContext
{
	void* GetPointer()
	{
		return reinterpret_cast<void*>(DevCon);
	}

	void** GetReference()
	{
		return reinterpret_cast<void**>(&DevCon);
	}

	ID3D11DeviceContext* DevCon;
};

struct HR_SDK::GraphicsSwapChain
{
	void* GetPointer()
	{
		return reinterpret_cast<void*>(SwapChain);
	}

	void** GetReference()
	{
		return reinterpret_cast<void**>(&SwapChain);
	}

	IDXGISwapChain* SwapChain;
};

struct HR_SDK::GraphicsVertexBuffer
{
	void* GetPointer()
	{
		return reinterpret_cast<void*>(VB);
	}

	void** GetReference()
	{
		return reinterpret_cast<void**>(&VB);
	}

	ID3D11Buffer* VB;
};

struct HR_SDK::GraphicsIndexBuffer
{
	void* GetPointer()
	{
		return reinterpret_cast<void*>(IB);
	}

	void** GetReference()
	{
		return reinterpret_cast<void**>(&IB);
	}

	ID3D11Buffer* IB;
};

bool C_TestMesh::CreateVertexB(GraphicsDevice* prm_Device)
{
	S_Vertex Vertices[4];

	Vertices[0].m_Position.Set		(-0.5f, -0.5f, 0.5f);
	Vertices[0].m_Color.Set			(1.0f, 0.0f, 0.0f, 1.0f);
	Vertices[0].m_TextCoords.Set	(0.0f, 0.0f);
	Vertices[0].m_Normal.Set		(0.0f , 0.0f, 1.0f);

	Vertices[1].m_Position.Set		(-0.5f, 0.5f, 0.5f);
	Vertices[1].m_Color.Set			(0.0f, 1.0f, 0.0f, 1.0f);
	Vertices[1].m_TextCoords.Set	(0.0f, 0.0f);
	Vertices[1].m_Normal.Set		(0.0f, 0.0f, 1.0f);

	Vertices[2].m_Position.Set		(0.5f, 0.5f, 0.5f);
	Vertices[2].m_Color.Set			(0.0f, 0.0f, 1.0f, 1.0f);
	Vertices[2].m_TextCoords.Set	(0.0f, 0.0f);
	Vertices[2].m_Normal.Set		(0.0f, 0.0f, 1.0f);

	Vertices[3].m_Position.Set		(0.5f, -0.5f, 0.5f);
	Vertices[3].m_Color.Set			(0.0f, 1.0f, 0.0f, 1.0f);
	Vertices[3].m_TextCoords.Set	(0.0f, 0.0f);
	Vertices[3].m_Normal.Set		(0.0f, 0.0f, 1.0f);

	for (auto vert : Vertices)
	{
		m_VB.AddVertex(vert);
	}

	if (!m_VB.m_Vertices.size())
	{
		return false;
	}

	m_VB.CreateBuffer(prm_Device, m_VB.GetCount(), D3D_Binds::VERTEX_BUFFER, D3D_Access::WRITE, D3D_Usages::DYNAMIC, m_VB.m_Vertices);
	return true;

}

bool C_TestMesh::CreateIndexB(GraphicsDevice* prm_Device)
{
	uint32 Indices[6];
	//! First triangle
	Indices[0] = 0;
	Indices[1] = 1;
	Indices[2] = 2;
	//! Second triangle
	Indices[3] = 0;
	Indices[4] = 2;
	Indices[5] = 3;

	for (auto indc : Indices)
	{
		m_IB.AddIndex(indc);
	}

	if (!m_IB.m_Indices.size())
	{
		return false;
	}

	m_IB.CreateBuffer(prm_Device, m_IB.GetCount(), D3D_Binds::INDEX_BUFFER, D3D_Access::WRITE, D3D_Usages::DEFAULT, m_IB.m_Indices);

	return true;
}

void C_TestMesh::SetIB
(
	GraphicsDeviceContext*	prm_DC
)
{
	m_IB.SetBuffer(prm_DC, DXGI_Formats::R_32_UINT);
}

void C_TestMesh::SetVB
(
	GraphicsDeviceContext*	prm_DC
)
{
	uint32 Stride = sizeof(S_Vertex);
	uint32 Offset = 0;

	m_VB.SetBuffer(prm_DC);
}

void C_TestMesh::SetTopology
(
	GraphicsDeviceContext*	prm_DC,
	D3D_Topologies::E prm_Topology
)
{
	reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->IASetPrimitiveTopology
	(
		TranslateTopology(prm_Topology)
	);
}

void C_TestMesh::Draw
(
	GraphicsDeviceContext*	prm_DC,
	uint32					prm_Indices
)
{
	reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->DrawIndexed
	(
		prm_Indices, 0, 0
	);
}