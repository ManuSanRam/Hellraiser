#pragma once

#include "HRGraphics_Prerequisites.h"

namespace HR_SDK
{
	struct GraphicsDevice;
	struct GraphicsDeviceContext;
	struct GraphicsRenderTargetView;
	struct GraphicsDepthStencilBuffer;
	struct GraphicsDepthStencilState;
	struct GraphicsDepthStencilView;

	class HR_D3DGRAPHICSAPI_EXPORT C_DepthStencil
	{
	public:
		C_DepthStencil()
		{
			m_DSB = NULL;
			m_DSS = NULL;
			m_DSV = NULL;
		}

		~C_DepthStencil()
		{
			if (m_DSV)
			{
				delete m_DSV;
			}
			m_DSV = NULL;

			if (m_DSS)
			{
				delete m_DSS;
			}
			m_DSS = NULL;

			if (m_DSB)
			{
				delete m_DSB;
			}
			m_DSB = NULL;
		}

		bool CreateDSBuffer
		(
			uint32			prm_W,
			uint32			prm_H,
			D3D_Formats::E	prm_Format,
			D3D_Usages::E	prm_Usage,
			D3D_Binds::E	prm_Bind,
			GraphicsDevice*	prm_Device
		);
		bool CreateDSState
		(
			GraphicsDevice* prm_Device, GraphicsDeviceContext* prm_DC
		);

		bool CreateDSView
		(
			GraphicsDevice* prm_Device, GraphicsDeviceContext* prm_DC, D3D_Formats::E prm_Format
		);
		
		void ClearDSV
		(
			GraphicsDeviceContext* prm_DC
		);

		void Close
		(

		);

		GraphicsDepthStencilBuffer*			m_DSB;
		GraphicsDepthStencilState*			m_DSS;
		GraphicsDepthStencilView*			m_DSV;
	};
}