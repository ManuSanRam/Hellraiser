#include "HRGraphics_Graphics.h"

/*!************************************************************************************************************************************************************************
* @file		HRGraphics_Buffer.cpp
*
* This file contains definition of the methods declared inside the buffers' classes.
* The methods implemented in the class are:
* - Setting of the channels individually.
* - Obtaining color structures from another 4D vector to get information from.
* - Obtaining color data from another color.
*
* @date        08-11-2016
* @author		Manuel Aldair Santos Ramón (ManuSanRam)
* @copyright	Infernal Coders S.A.
***************************************************************************************************************************************************************************/

namespace HR_SDK
{
	struct GraphicsDevice
	{
		GraphicsDevice() : Device(nullptr) {}
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

	struct GraphicsDeviceContext
	{
		GraphicsDeviceContext() : DevCon(nullptr) {} //! Someting like that?
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

	struct GraphicsSwapChain
	{
		GraphicsSwapChain() : SwapChain(nullptr) {}
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

	bool C_GraphicsAPI::Init
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
	)
	{
		m_Device = new GraphicsDevice;
		m_DC = new GraphicsDeviceContext;
		m_SwapChain = new GraphicsSwapChain;

		HRESULT FuncResult;

		//Describe our Buffer
		DXGI_MODE_DESC BDesc;

		memset(&BDesc, 0, sizeof(DXGI_MODE_DESC));

		BDesc.Width = prm_ScrW;
		BDesc.Height = prm_ScrH;
		BDesc.RefreshRate.Numerator = 60;
		BDesc.RefreshRate.Denominator = 1;
		BDesc.Format = TranslateFormat(prm_Format);
		BDesc.ScanlineOrdering = TranslateScanlineOrder(prm_ScanlineMode);
		BDesc.Scaling = TranslateScaling(prm_ScalingMode);

		//Describe our SwapChain
		DXGI_SWAP_CHAIN_DESC SCDesc;

		memset(&SCDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

		SCDesc.BufferDesc = BDesc;
		SCDesc.SampleDesc.Count = 1;
		SCDesc.SampleDesc.Quality = 0;
		SCDesc.BufferUsage = TranslateDXGIUsage(prm_DXGIUsage);
		SCDesc.BufferCount = 1;
		//! Get the window index
		HWND Window = reinterpret_cast<HWND>(prm_Wnd);
		//! Set the window where graphics will be rendered
		SCDesc.OutputWindow = Window;

		SetFullscreen(prm_Fullscreen);
		if (m_Fullscreen)
		{
			//! Set swapchain to be in fullscreen
			SCDesc.Windowed = FALSE;
		}

		else
		{
			//! Set swapchain to be in a windowed rect
			SCDesc.Windowed = TRUE;
		}
		
		SCDesc.SwapEffect = TranslateSwapEffect(prm_SwapEffect);


		//Create our SwapChain
		FuncResult = D3D11CreateDeviceAndSwapChain
		(
			NULL, 
			TranslateDriver(prm_DriverType), 
			NULL, 
			NULL, 
			NULL, 
			NULL,
			D3D11_SDK_VERSION, 
			&SCDesc, 
			reinterpret_cast<IDXGISwapChain**>(m_SwapChain->GetReference()), 
			reinterpret_cast<ID3D11Device**>(m_Device->GetReference()), 
			NULL, 
			reinterpret_cast<ID3D11DeviceContext**>(m_DC->GetReference())
		);

		if (FAILED(FuncResult))
		{
			return false;
		}

		return true;
	}

	void C_GraphicsAPI::Present()
	{
		reinterpret_cast<IDXGISwapChain*>(m_SwapChain->GetPointer())->Present(0, 0);
	}

	void C_GraphicsAPI::Close()
	{
		reinterpret_cast<IDXGISwapChain*>(m_SwapChain->GetPointer())->Release();
		delete m_SwapChain;
		
		reinterpret_cast<ID3D11DeviceContext*>(m_DC->GetPointer())->Release();
		delete m_DC;

		reinterpret_cast<ID3D11Device*>(m_Device->GetPointer())->Release();
		delete m_Device;
	}

}