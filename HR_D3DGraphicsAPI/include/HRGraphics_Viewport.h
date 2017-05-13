#pragma once

#include "HRGraphics_Prerequisites.h"

namespace HR_SDK
{
	struct GraphicsDeviceContext;
	struct GraphicsViewport;

	/*!
	 * @brief Encapsulates the data used to create and manage a D3D11 viewport for graphics initialization.
	*/
	class HR_D3DGRAPHICSAPI_EXPORT C_Viewport
	{
	public:
		/*!
		 * @brief Creates a D3D11 viewport with data 
		 * @param prm_TopX Holds the "X" coordinate of the top of the viewport (Pixel-coordinate space).
		 * @param prm_TopY Holds the "Y" coordinate of the top of the viewport (Pixel-coordinate space).
		 * @param prm_Width Holds the width of the viewport (Pixel-space space).
		 * @param prm_Height Holds the height of the viewport (Pixel-space space).
		*/
		void Create(uint32 prm_TopX, uint32 prm_TopY, uint32 prm_Width, uint32 prm_Height, float prm_MinDepth, float prm_MaxDepth);

		void Set(GraphicsDeviceContext* prm_DC);

		/*!
		*/
		GraphicsViewport* m_Viewport;

		/*!
		*/
		uint32 m_Top_X;
		/*!
		*/
		uint32 m_Top_Y;
		/*!
		*/
		uint32 m_Width;
		/*!
		*/
		uint32 m_Height;

		float m_MinDepth;
		float m_MaxDepth;
	};
}
