/*!******************************************************************************************************************************************************************************

	@file		HRGraphics_Depth.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the definitions of the class C_DepthStencil. 

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		03-08-2017
	@author		Manuel Santos Ramón [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/

#include "HRGraphics_Depth.h"
#include <d3d11.h>

namespace HR_SDK
{
	/*!



	*/
	struct GraphicsDevice
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Device);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Device);
		}

		/*!
		*/
		ID3D11Device* Device;
	};



	/*!



	*/
	struct GraphicsDeviceContext
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DevCon);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DevCon);
		}

		/*!
		*/
		ID3D11DeviceContext* DevCon;
	};



	/*!



	*/
	struct GraphicsDepthStencilBuffer
	{
		GraphicsDepthStencilBuffer() : Buffer(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Buffer);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Buffer);
		}

		ID3D11Texture2D* Buffer;
	};



	/*!



	*/
	struct GraphicsDepthStencilState
	{
		/*!



		*/
		GraphicsDepthStencilState() : DSS(nullptr) {}


		/*!



		*/
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DSS);
		}


		/*!



		*/
		void** GetReference()
		{
			return reinterpret_cast<void**>(&DSS);
		}


		/*!



		*/
		ID3D11DepthStencilState* DSS;
	};



	/*!



	*/
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



	/*!**************************************************************************************************************************************************************************

		@brief Creates the depth buffer

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _width
		@param _height
		@param _format
		@param _usage
		@param _bind
		@param _device

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return True, if the depth buffer was successfully created. False, if an error was encountered.

	****************************************************************************************************************************************************************************/
	bool C_DepthStencil::CreateDSBuffer
	(
		uint32			_w, 
		uint32			_h,
		DXGI_Formats::E	_format,
		D3D_Usages::E	_usage,
		D3D_Binds::E	_bind,
		GraphicsDevice*	_device
	)
	{
		//! Allocate buffer
		m_DSB = new GraphicsDepthStencilBuffer;

		//! For error checking
		HRESULT FuncResult;

		// Set up the description of the depth buffer.
		D3D11_TEXTURE2D_DESC DSBDesc;
		ZeroMemory(&DSBDesc, sizeof(DSBDesc));

		DSBDesc.Width = _w;
		DSBDesc.Height = _h;
		DSBDesc.MipLevels = 1;
		DSBDesc.ArraySize = 1;
		DSBDesc.Format = (DXGI_FORMAT)_format;
		DSBDesc.SampleDesc.Count = 1;
		DSBDesc.SampleDesc.Quality = 0;
		DSBDesc.Usage = D3D11_USAGE(_usage);
		DSBDesc.BindFlags = D3D11_BIND_FLAG(_bind);
		DSBDesc.CPUAccessFlags = 0;
		DSBDesc.MiscFlags = 0;

		//! Reinterpret pointers for fast management
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_device->GetPointer());
		ID3D11Texture2D** buffer = reinterpret_cast<ID3D11Texture2D**>(m_DSB->GetReference());

		//! Create the texture for the depth buffer using the filled out description.
		FuncResult = device->CreateTexture2D(&DSBDesc, NULL, buffer);

		//! Check if there were errors while creating the buffer
		if (FAILED(FuncResult))
		{
			//! Error was found: couldn't continue
			return false;
		}

		//! Everythng is A-OK!
		return true;
	}



	/*!**************************************************************************************************************************************************************************

		@brief Creates the depth state

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@paramv_device
		@param _devContext

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	****************************************************************************************************************************************************************************/
	bool C_DepthStencil::CreateDSState
	(
		GraphicsDevice*				_device, 
		GraphicsDeviceContext*		_devContext
	)
	{
		//! Allocate the depth-stencil state for its use
		m_DSS = new GraphicsDepthStencilState;

		//! For checking errors
		HRESULT FuncResult;
		
		//! Set up the descriptor to create the depth-stencil state
		D3D11_DEPTH_STENCIL_DESC DSSDesc;
		ZeroMemory(&DSSDesc, sizeof(DSSDesc));
		
		DSSDesc.DepthEnable = true;
		DSSDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DSSDesc.DepthFunc = D3D11_COMPARISON_LESS;
		DSSDesc.StencilEnable = true;
		DSSDesc.StencilReadMask = 0xFF;
		DSSDesc.StencilWriteMask = 0xFF;
		DSSDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		DSSDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		DSSDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		DSSDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		DSSDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		//! Manage pointers by reinterpretation
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_device->GetPointer());
		ID3D11DepthStencilState** dss_ref = reinterpret_cast<ID3D11DepthStencilState**>(m_DSS->GetReference());

		//! Create state and check for any errors
		FuncResult = device->CreateDepthStencilState
		(
			&DSSDesc, 
			dss_ref
		);

		//! If creation failed
		if (FAILED(FuncResult))
		{
			//! Error was encountered. Stop the function and exit
			return false;
		}

		//! Creation was successful, so continue

		//! Manage pointers by reinterpretation
		ID3D11DeviceContext* devCon = reinterpret_cast<ID3D11DeviceContext*>(_devContext->GetPointer());
		ID3D11DepthStencilState* dss_p = reinterpret_cast<ID3D11DepthStencilState*>(m_DSS->GetPointer());

		//! Set the state
		devCon->OMSetDepthStencilState
		(
			dss_p,
			1
		);

		//! Everything is A-OK!
		return true;
	}



	/*!**************************************************************************************************************************************************************************

		@brief Creates the depth view

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _device

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	****************************************************************************************************************************************************************************/
	bool C_DepthStencil::CreateDSView
	(
		GraphicsDevice*				_device
	)
	{
		//! Allocate the pointer for its use
		m_DSV = new GraphicsDepthStencilView;

		//! For error checking
		HRESULT FuncResult;

		//! Set up the descriptor for depth-stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
		ZeroMemory(&DSVDesc, sizeof(DSVDesc));

		DSVDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DSVDesc.Texture2D.MipSlice = 0;

		//! Manage pointers by reinterpretation
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_device->GetPointer());
		ID3D11Resource* dsb_p = reinterpret_cast<ID3D11Resource*>(m_DSB->GetPointer());
		ID3D11DepthStencilView** dsv_r = reinterpret_cast<ID3D11DepthStencilView**>(m_DSV->GetReference());

		//! Create the depth-stencil view
		FuncResult = device->CreateDepthStencilView
		(
			dsb_p,
			&DSVDesc, 
			dsv_r
		);

		//! Check for errors
		if (FAILED(FuncResult))
		{
			//! Error was encountered. Exit the function
			return false;
		}

		//! Everything is A-OK!
		return true;
	}



	/*!**************************************************************************************************************************************************************************

		@brief Clears the depth buffer whenever the depth of the rendered geometry changes

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _DC

	****************************************************************************************************************************************************************************/
	void C_DepthStencil::ClearDSV
	(
		GraphicsDeviceContext* _devContext
	)
	{
		ID3D11DeviceContext* devCont = reinterpret_cast<ID3D11DeviceContext*>(_devContext->GetPointer()); 
		ID3D11DepthStencilView* dsv = reinterpret_cast<ID3D11DepthStencilView*>(m_DSV->GetPointer());

		devCont->ClearDepthStencilView
		(
			dsv,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0
		);
	}



	/*!**************************************************************************************************************************************************************************

		@brief Closes and deallocates all DEPTH objects and from the pipeline

	****************************************************************************************************************************************************************************/
	void C_DepthStencil::Close
	(

	)
	{
		//! Check if DSV is allocated
		if (m_DSV)
		{
			ID3D11DepthStencilView* dsv = reinterpret_cast<ID3D11DepthStencilView*>(m_DSV->GetPointer());

			//! Check if dsv is allocated
			if (dsv)
			{
				//! Release the Direct X 11 depth-stencil view that is allocated
				dsv->Release();
			}

			delete m_DSV;

		}

		//! Point DSV to 0 address 
		m_DSV = NULL;



		//! Check if DSS is allocated
		if (m_DSS)
		{
			ID3D11DepthStencilState* dss = reinterpret_cast<ID3D11DepthStencilState*>(m_DSS->GetPointer());

			if (dss)
			{
				//! Release the Direct X 11 depth-stencil state that is allocated
				dss->Release();
			}

			//! If it is, delete the allocated memory
			delete m_DSS;

		}

		//! Point DSS to 0 address
		m_DSS = NULL;
		


		//! Check if DSB is allocated
		if (m_DSB)
		{
			ID3D11Texture2D* dsb = reinterpret_cast<ID3D11Texture2D*>(m_DSB->GetPointer());

			if (dsb)
			{
				//! Release the Direct X 11 texture buffer where the depth buffer is allocated
				dsb->Release();
			}

			delete m_DSB;

		}

		//! Point DSB to 0 address
		m_DSB = NULL;

	}
}