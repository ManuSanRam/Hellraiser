#include "HRGraphics_Viewport.h"
#include <d3d11.h>

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
		D3D11_VIEWPORT Viewport;
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

		m_Viewport->Viewport.TopLeftX = m_Top_X;
		m_Viewport->Viewport.TopLeftY = m_Top_Y;
		m_Viewport->Viewport.Width =    m_Width;
		m_Viewport->Viewport.Height =   m_Height;
		m_Viewport->Viewport.MinDepth = m_MinDepth;
		m_Viewport->Viewport.MaxDepth = m_MaxDepth;
	}

	void C_Viewport::Set(GraphicsDeviceContext* prm_DC)
	{
		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->RSSetViewports
		(
			1, 
			&m_Viewport->Viewport
		);
	}
}