

/*!******************************************************************************************************************************************************************************

	@file		HRGraphics_RenderTarget.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the definition of the methods from the @class C_RenderTarget.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		21-07-2017
	@author		Manuel Santos Ramón [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/

#include "HRGraphics_RenderTarget.h"

#include <d3d11.h>

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
		GraphicsDeviceContext() : DevCon(nullptr) {}
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

	struct GraphicsRenderTargetView
	{
		GraphicsRenderTargetView() : RTV(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(RTV);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&RTV);
		}

		ID3D11RenderTargetView* RTV;
	};

	struct GraphicsDepthStencilView
	{
		GraphicsDepthStencilView() : DSV(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DSV);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DSV);
		}

		ID3D11DepthStencilView* DSV;
	};

	/*!**********************************************************************************************************************************************************************

		@brief Creates a render target

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _device GPU device
		@param _swapChain Swap chain where render target is targeted

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return True if render target is created successfully, false if an error was encountered

	************************************************************************************************************************************************************************/
	bool	C_RenderTarget::	Create
	(
		GraphicsDevice* _device,
		GraphicsSwapChain* _swapChain
	)
	{
		ID3D11Texture2D* _texture;
		IDXGISwapChain* TmpSC = reinterpret_cast<IDXGISwapChain*>(_swapChain->GetPointer());
		HRESULT FuncResult = TmpSC->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_texture);

		if (FAILED(FuncResult))
		{
			return false;
		}

		m_RTV = new GraphicsRenderTargetView();
		ID3D11Device* TmpDev = reinterpret_cast<ID3D11Device*>(_device->GetPointer());
		ID3D11Resource* TmpRes = reinterpret_cast<ID3D11Resource*>(_texture);
		ID3D11RenderTargetView** TmpRTV = reinterpret_cast<ID3D11RenderTargetView**>(m_RTV->GetReference());

		FuncResult = TmpDev->CreateRenderTargetView
		(
			TmpRes,
			NULL,
			TmpRTV
		);

		if (FAILED(FuncResult))
		{
			return false;
		}

		TmpRes->Release();
		return true;
	}



	/*!**********************************************************************************************************************************************************************

	@brief Creates a render target

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@param _device GPU device
	@param _swapChain Swap chain where render target is targeted

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@return True if render target is created successfully, false if an error was encountered

	************************************************************************************************************************************************************************/
	bool	C_RenderTarget::CreateRendereable
	(
		GraphicsDevice* _device,
		GraphicsSwapChain* _swapChain
	)
	{
		return true;
	}


	/*!**********************************************************************************************************************************************************************

		@brief Sets a render target to the GPU

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _devContext GPU device
		@param[in] _numViews Swap chain where render target is targeted
		@param[in] _depthStencil Depth stencil object

	************************************************************************************************************************************************************************/
	void	C_RenderTarget::Set
	(
		GraphicsDeviceContext* _devContext,
		uint32 _numViews,
		C_DepthStencil* _depthStencil
	)
	{
		//! Simplify function, reducing castings to one and using them temporal pointers (They after exiting scope) - Thursday May 18th, 2017
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(_devContext->GetPointer());
		ID3D11RenderTargetView** TmpRTV = reinterpret_cast<ID3D11RenderTargetView**>(m_RTV->GetReference());
		ID3D11DepthStencilView* TmpDSV = reinterpret_cast<ID3D11DepthStencilView*>(_depthStencil->m_DSV->GetPointer());

		//! Set the render target to the device context
		TmpDC->OMSetRenderTargets
		(
			_numViews,
			TmpRTV,
			TmpDSV
		);
	}

	/*!**********************************************************************************************************************************************************************

		@brief Clears a render target to draw new data

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _devContext Device context used to set the render target at
		@param[in] _color Clear color passed to the render target

	************************************************************************************************************************************************************************/
	void	C_RenderTarget::Clear
	(
		GraphicsDeviceContext* _devContext,
		C_LinearColor& _color
	)
	{
		float Color[] = { _color.GetRed(), _color.GetGreen(), _color.GetBlue(), _color.GetAlpha() };

		//! Reduce castings to one. Temporal pointer die after leaving function scope
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(_devContext->GetPointer());
		ID3D11RenderTargetView* TmpRTV = reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer());

		//! Clear RTV - Thursday May 18th, 2017
		TmpDC->ClearRenderTargetView
		(
			TmpRTV,
			Color
		);
	}

	
	void	C_RenderTarget::Close
	(

	)
	{
		//! If not, jut make sure pointer carries no garbage - Thursday May 18th, 2017
		if (m_RTV != NULL)
		{
			ID3D11RenderTargetView* TmpRTV = reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer());
			if (TmpRTV) { TmpRTV->Release(); }

			delete TmpRTV;
		}
	}
}