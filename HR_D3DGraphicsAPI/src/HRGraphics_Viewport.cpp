#include "HRGraphics_Viewport.h"

namespace HR_SDK
{
	struct GraphicsDeviceContext
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DC);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DC);
		}
		ID3D11DeviceContext* DC;
	};

	struct GraphicsViewport
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Viewport);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Viewport);
		}
		D3D11_VIEWPORT* Viewport;
	};

	void C_Viewport::Create(uint32 prm_TopX, uint32 prm_TopY, uint32 prm_Width, uint32 prm_Height, float prm_MinDepth, float prm_MaxDepth)
	{
		m_Viewport = new GraphicsViewport();

		//! Save data in local variables
		m_Top_X = prm_TopX;
		m_Top_Y = prm_TopY;
		m_Width = prm_Width;
		m_Height = prm_Height;
		m_MinDepth = prm_MinDepth;
		m_MaxDepth = prm_MaxDepth;

		reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())->TopLeftX = m_Top_X;
		reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())->TopLeftY = m_Top_Y;
		reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())->Width =    m_Width;
		reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())->Height =   m_Height;
		reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())->MinDepth = m_MinDepth;
		reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())->MaxDepth = m_MaxDepth;
	}

	void C_Viewport::Set(GraphicsDeviceContext* prm_DC)
	{
		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->RSSetViewports
		(
			1, 
			reinterpret_cast<D3D11_VIEWPORT*>(m_Viewport->GetPointer())
		);
	}
}