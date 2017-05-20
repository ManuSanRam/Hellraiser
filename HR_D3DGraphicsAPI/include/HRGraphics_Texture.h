#pragma once

/*!************************************************************************************************************************************************************************
***************************************************************************************************************************************************************************/

#include "HRGraphics_Prerequisites.h"
#include <HRUtility_Datastream.h>
#include <HRUtility_Color.h>

namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	struct GraphicsDevice;
	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	struct GraphicsDeviceContext;
	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	struct GraphicsSwapChain;
	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	struct GraphicsTexture;
	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	struct GraphicsRenderTargetView;
	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	struct GraphicsDepthStencilView;

	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	class HR_D3DGRAPHICSAPI_EXPORT C_Texture
	{
	public:
		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		C_Texture()
		{
			m_Texture = NULL;
			m_RTV = NULL;
		}
		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		~C_Texture()
		{

		}

		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		bool						CreateFromFile
		(
			C_Filestream*		prm_File,
			uint32				prm_Width,
			uint32				prm_Height,
			uint32				prm_MipLevels,
			DXGI_Formats::E		prm_Format,
			D3D_Usages::E		prm_Usage,
			D3D_Binds::E		prm_Bind,
			D3D_Access::E		prm_Access
		);
		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		bool						CreateAsRTV(GraphicsDevice* prm_Device, GraphicsSwapChain* prm_SC);

		void						SetRTV(GraphicsDeviceContext* prm_DC, uint32 prm_NumViews, GraphicsDepthStencilView* prm_DSV);

		void						ClearRTV(GraphicsDeviceContext* prm_DC, C_LinearColor prm_Color);

		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		void						Close();

	public:
		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		GraphicsTexture*				m_Texture;

		/*!****************************************************************************************************************************************************************
		*******************************************************************************************************************************************************************/
		GraphicsRenderTargetView*		m_RTV;
	};
}
