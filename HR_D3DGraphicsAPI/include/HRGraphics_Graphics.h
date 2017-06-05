#pragma once

#include "HRGraphics_Prerequisites.h"

/*!*************************************************************************************************************************************************************************
* @file		HRGraphics_Graphics.h																																		   *
*																																										   *
* This file contains the Graphics class, used to load, set and manage graphics data.																					   *
* The methods implemented in the class are:																																   *
* - Initialising DirectX.																																				   *
* - Setting the graphics environment.																																	   *
* - Drawing to screen.																																					   *
*																																										   *
* @date         07-12-2016																																				   *
* @author		Manuel Aldair Santos Ramón (ManuSanRam)																													   *
* @copyright	Infernal Coders S.A.																																	   *
***************************************************************************************************************************************************************************/

namespace HR_SDK
{
	struct GraphicsDevice;
	struct GraphicsDeviceContext;
	struct GraphicsSwapChain;

	/*!*********************************************************************************************************************************************************************
	 * @brief Declares the Graphics API object used to control graphics using methods and types of DirectX 11															   *
	 * Every method, variable and type are encapsulated so only Graphics API is the one managing any graphical operation internally										   *
	***********************************************************************************************************************************************************************/
	class HR_D3DGRAPHICSAPI_EXPORT C_GraphicsAPI
	{
	public:
	  /*!*******************************************************************************************************************************************************************
	   * @brief Constructor (default)																																	   *
	  *********************************************************************************************************************************************************************/
	  C_GraphicsAPI()
	  {
		  m_Fullscreen = false;
		  m_VSync = true;

		  m_SwapChain = NULL;
		  m_Device = NULL;
		  m_DC = NULL;
	  }

	  /*!*******************************************************************************************************************************************************************
	   * @brief Destructor																																				   *
	  *********************************************************************************************************************************************************************/
	  ~C_GraphicsAPI() 
	  {

	  }

	  /*!
	  */
	  void SetFullscreen(bool prm_FScr)
	  {
		  m_Fullscreen = prm_FScr;
	  }
	  /*!
	  */
	  void SetVSync(bool prm_VSync)
	  {
		  m_VSync = prm_VSync;
	  }

	  /*!
	   * @brief Initiates the DirectX graphics pipeline. Sets the device, the swap chain and the device context.
	   * @param
	   * @return
	  */
	  bool Init
	  (
		  uint32 prm_ScrW, 
		  uint32 prm_ScrH, 
		  DXGI_Formats::E prm_Format,
		  DXGI_Scanlines::E prm_ScanlineMode,
		  DXGI_Scaling::E prm_ScalingMode,
		  const uint64 prm_DXGIUsage,
		  uint32 prm_Wnd,
		  bool prm_Fullscreen,
		  DXGI_SwapEffect::E prm_SwapEffect,
		  D3D_Drivers::E prm_DriverType
	  );

	  /*!
	  */
	  void Present();
	  /*!
	  */
	  void Close();

	  /*!
	  */
	  bool m_Fullscreen;
	  /*!
	  */
	  bool m_VSync;
	  /*!
	  */
	  GraphicsDevice*			m_Device;
	  /*!
	  */
	  GraphicsDeviceContext*	m_DC;
	  /*!
	  */
	  GraphicsSwapChain*		m_SwapChain;
	};
}