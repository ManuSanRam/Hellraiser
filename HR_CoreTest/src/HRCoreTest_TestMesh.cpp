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
	S_Vertex V1
	(
		-0.75f, -0.75f, 0.5f, 
		1.0f, 1.0f, 0.0f, 1.0f
	);
	
	S_Vertex V2
	(
		-0.375f, 0.0f, 0.5f, 
		1.0f, 1.0f, 0.0f, 1.0f
	);
	
	S_Vertex V3
	(
		0.0f, -0.75f, 0.5f, 
		0.7f, 0.7f, 0.0f, 1.0f
	);
	

	S_Vertex V4
	(
		0.0f, 0.75f, 0.5f, 
		1.0f, 1.0f, 0.0f, 1.0f
	);

	S_Vertex V5
	(
		0.375f, 0.0f, 0.5f,
		0.7f, 0.7f, 0.0f, 1.0f
	);

	S_Vertex V6
	(
		0.75f, -0.75f, 0.5f,
		0.3f, 0.3f, 0.0f, 1.0f
	);

	m_VB.AddVertex(V1);
	m_VB.AddVertex(V2);
	m_VB.AddVertex(V3);
	m_VB.AddVertex(V4);
	m_VB.AddVertex(V5);
	m_VB.AddVertex(V6);

	if (!m_VB.m_Vertices.size())
	{
		return false;
	}

	if (m_VB.Create(prm_Device, D3D_Binds::VERTEX_BUFFER, D3D_Access::NONE, D3D_Usages::DEFAULT))
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool C_TestMesh::CreateIndexB(GraphicsDevice* prm_Device)
{
	uint32 Indices[9];
	//! First triangle
	Indices[0] = 0;
	Indices[1] = 1;
	Indices[2] = 2;
	//! Second triangle
	Indices[3] = 1;
	Indices[4] = 3;
	Indices[5] = 4;
	//! Third triangle
	Indices[6] = 2;
	Indices[7] = 4;
	Indices[8] = 5;

	for (auto indc : Indices)
	{
		m_IB.AddIndex(indc);
	}

	if (!m_IB.m_Indices.size())
	{
		return false;
	}

	if (m_IB.Create(prm_Device, m_IB.GetCount(), D3D_Binds::INDEX_BUFFER, D3D_Access::NONE, D3D_Usages::DEFAULT))
	{
		return true;
	}

	else
	{
		return false;
	}
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
	GraphicsDeviceContext*	prm_DC
)
{
	reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->DrawIndexed
	(
		m_IB.GetCount(), 0, 0
	);
}