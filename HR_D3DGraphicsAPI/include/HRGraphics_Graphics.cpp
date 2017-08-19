/*!******************************************************************************************************************************************************************************

	@file		HRGraphics_Graphics.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of graphics pipeline class, used to load, set and manage graphic pipeline objects.
	The methods implemented in the class are:
	- Initializing DirectX.
	- Setting the graphics environment.
	- Drawing to screen.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		20-07-2017
	@author		Manuel Aldair Santos Ramón (ManuSanRam)
	@copyright	Infernal Coders S.A.

********************************************************************************************************************************************************************************/
#include "HRGraphics_Graphics.h"
#include <d3d11.h>

namespace HR_SDK
{
	/*!
	*/
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



	/*!
	*/
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



	/*!
	*/
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



	/*!**************************************************************************************************************************************************************************

		@brief Initiates the graphics pipeline, setting the GPU device, device context and swap chain.

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _ScrW Width of the screen
		@param _ScrH Height of the screen
		@param _Format Format of the pipeline objects
		@param _ScanlineMode Scanline mode used in the rasterizer
		@param _ScalingMode Scaling mode of the images
		@param _DXGIUsage Usage given to the buffer of the swap chain
		@param _Wnd Index ID of the window
		@param _Fullscreen Flag to determine if the pipeline renders on fullscreen
		@param _SwapEffect Effect of the swap chain to change between render targets
		@param _DriverType Driver used by the GPU

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return True if the pipeline objects were created successfully, false if an error was encountered.

	****************************************************************************************************************************************************************************/
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
		BDesc.Format = (DXGI_FORMAT)prm_Format;
		BDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER(prm_ScanlineMode);
		BDesc.Scaling = DXGI_MODE_SCALING(prm_ScalingMode);

		//Describe our SwapChain
		DXGI_SWAP_CHAIN_DESC SCDesc;

		memset(&SCDesc, 0, sizeof(DXGI_SWAP_CHAIN_DESC));

		SCDesc.BufferDesc = BDesc;
		SCDesc.SampleDesc.Count = 1;
		SCDesc.SampleDesc.Quality = 0;
		SCDesc.BufferUsage = DXGI_USAGE(prm_DXGIUsage);
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

		SCDesc.SwapEffect = DXGI_SWAP_EFFECT(prm_SwapEffect);


		//Create our SwapChain
		FuncResult = D3D11CreateDeviceAndSwapChain
		(
			NULL,
			D3D_DRIVER_TYPE(prm_DriverType),
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


	///**********************************************************************************************************************************************************************

	///																		CREATE PIPELINE OBJECTS

	///*********************************************************************************************************************************************************************/
	///************************************************************************ Output Merger ******************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param
		@param
		@param

		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateDepthStencil
	(
		uint32			_width,
		uint32			_height,
		DXGI_Formats::E	_format,
		D3D_Usages::E	_usage,
		D3D_Binds::E	_bind,
		C_DepthStencil* _depthStencil
	)
	{
		if (_depthStencil)
		{
			//! Create the depth stencil buffer
			if (!_depthStencil->CreateDSBuffer(_width, _height, _format, _usage, _bind, m_Device))
			{
				//! Something went wrong
				return false;
			}

			//! Create the depth stencil state
			if (!_depthStencil->CreateDSState(m_Device, m_DC))
			{
				//! Something went wrong
				return false;
			}

			//! Create the depth stencil view
			if (!_depthStencil->CreateDSView(m_Device))
			{
				//! Something went wrong
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{
			return false;
		}
	}


	/*!**********************************************************************************************************************************************************************

		@brief Create a render target

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _renderTarget

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return True if the render target object was created successfully, false if not

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateRenderTarget
	(
		C_RenderTarget* _renderTarget
	)
	{
		if (_renderTarget)
		{
			if (!_renderTarget->Create(m_Device, m_SwapChain))
			{
				return false;
			}

			return true;
		}

		else
		{
			return false;
		}
	}


	///********************************************************************** Vertex shader stage **************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param

		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateVertexShader
	(
		const String&	_shaderFile,
		const String&	_shaderEntryPoint,
		const String&	_shaderProfile,
		C_VertexShader* _vShader
	)
	{
		if (_vShader)
		{
			if
			(
				!_vShader->Compile
				(
					_shaderFile,
					_shaderEntryPoint,
					_shaderProfile
				)
			)
			{
				return false;
			}

			if
			(
				!_vShader->Create
				(
					m_Device
				)
			)
			{
				return false;
			}


			return true;
		}

		else
		{
			return false;
		}
	}


	///*********************************************************************** Pixel shader stage **************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param

		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreatePixelShader
	(
		const String&	_shaderFile,
		const String&	_shaderEntryPoint,
		const String&	_shaderProfile,
		C_PixelShader*	_pShader
	)
	{
		//! Check if the passed pointer is allocated
		if (_pShader)
		{
			if
				(//! Compile the shader file data to be processed
					!_pShader->Compile
					(
						_shaderFile,
						_shaderEntryPoint,
						_shaderProfile
					)
					)
			{
				//! An error was encountered while compiling the shader data
				return false;
			}

			if
				(//! File data was compiled, create the shader object to process data to GPU
					!_pShader->Create
					(
						m_Device
					)
					)
			{//! Error: Shader couldn't be created...
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{//! Error: Pointer was nullptr.
			return false;
		}
	}


	///**************************************************************************** Geometry *******************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateVertexBuffer
	(
		D3D_Access::E	_access,
		D3D_Usages::E	_usage,
		C_VBuffer*		_vBuff
	)
	{
		//! Check if pointer passed is allocated...
		if (_vBuff)
		{
			//! Check for errors while creating the vertex buffer...
			if 
			(
				!_vBuff->Create
				(
					m_Device,
					D3D_Binds::VERTEX_BUFFER,
					_access,
					_usage
				)
			)
			{
				//! An error was encountered and the vertex buffer couldn't be created...
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{
			//! Pointer passed was not allocated...
			return false;
		}
	}


	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateIndexBuffer
	(
		D3D_Access::E	_access,
		D3D_Usages::E	_usage,
		C_IBuffer32*	_iBuff
	)
	{
		//! Check if pointer passed is allocated...
		if (_iBuff)
		{
			//! Check for errors while creating the vertex buffer...
			if
			(
				!_iBuff->Create
				(
					m_Device,
					D3D_Binds::INDEX_BUFFER,
					_access,
					_usage
				)
			)
			{
				//! An error was encountered and the vertex buffer couldn't be created...
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{
			//! Pointer passed was not allocated...
			return false;
		}
	}


	///************************************************************************ Input Assembler ****************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param

		@param
		@param
		@param

		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	void C_GraphicsAPI::AddInput
	(
		char*			_semantic,
		uint32			_index,
		DXGI_Formats::E _format,
		uint32			_byteOffset,
		C_InputLayout*	_inLayout
	)
	{
		if (_inLayout)
		{
			_inLayout->AddInput
			(
				_semantic,
				_index,
				_format,
				_byteOffset
			);
		}

		else
		{
			return;
		}
	}
	
	
	
	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateInputLayout
	(
		C_VertexShader*	_vShader,
		C_InputLayout*	_inLayout
	)
	{
		if (_inLayout)
		{
			if (_vShader)
			{
				if 
				(
					!_inLayout->CreateInputLayout
					(
						m_Device,
						_vShader->m_Blob
					)
				)
				{
					return false;
				}

				return true;
			}

			else
			{
				return false;
			}
		}

		else
		{
			return false;
		}
	}


	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param
		@param

		@param
		@param

		@param

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateViewport
	(
		uint32			_posX,
		uint32			_posY,
		uint32			_width,
		uint32			_height,
		float			_minDepth,
		float			_maxDepth,
		C_Viewport*		_viewport
	)
	{
		//! Check if viewport pointer is allocated
		if(_viewport)
		{
			//! If allocated, create it using the parameters passed
			_viewport->Create
			(
				_posX,
				_posY,
				_width,
				_height,
				_minDepth,
				_maxDepth
			);

			//! Everything is A-OK!
			return true;
		}

		//! Pointer is not allocated
		else
		{
			//! Error: Pointer passed is not allocated
			return false;
		}
	}


	///************************************************************************ Constant buffer ****************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Create a constant buffer with a certain 

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _access
		@param _usage
		@param _size

		@param _cBuff

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateConstantBuffer
	(
		D3D_Access::E		_access,
		D3D_Usages::E		_usage,
		SIZE_T				_size,
		C_ConstantBuffer*	_cBuff
	)
	{
		//! Check if the constant buffer object was allocated
		if(_cBuff)
		{
			//! Object allocated, execute create function and check if there was any error 
			if 
			(
				!_cBuff->Create
				(
					m_Device,
					D3D_Binds::CONST_BUFFER,
					_access,
					_usage,
					_size
				)
			)
			{//! Fail!
				//!
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{
			//!
			return false;
		}
	}



	/*!**********************************************************************************************************************************************************************

		@brief

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _access
		@param _usage
		@param _size

		@param _cBuff

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::MapConstantBuffer
	(
		void*				_data,
		SIZE_T				_size,
		C_ConstantBuffer*	_cBuff
	)
	{
		//! Check if constant buffer
		if (_cBuff)
		{//! Map content to the constant buffer
			_cBuff->Map(m_DC, _data, _size);
			//! Everything is A-OK!
			return true;
		}

		else
		{//! Error was encountered
			//! End with error
			return false;
		}
	}



	///**************************************************************************** Txture *********************************************************************************/
	/*!**********************************************************************************************************************************************************************



	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateTexture
	(
		const String& _fileName,
		DXGI_Formats::E	_format,
		C_Texture* _texture
	)
	{
		if (_texture)
		{
			if (!_texture->CreateFromFile(_fileName, _format, m_Device, m_DC))
			{
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{//! Null ptr passed
			//! Error encountered
			return false;
		}
	}



	///********************************************************************* Shader Resource View **************************************************************************/
	/*!**********************************************************************************************************************************************************************



	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateShaderResourceView
	(
		DXGI_Formats::E _format,
		C_Texture* _texture, 
		C_ShaderResource* _srv
	)
	{
		if (_srv)
		{
			if (!_srv->Create(_format, _texture, m_Device, m_DC))
			{
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{//! Error: Pointer passed is not allocated
			return false;
		}
	}



	///*************************************************************************** Sampler *********************************************************************************/
	/*!**********************************************************************************************************************************************************************



	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateSampler
	(
		C_Sampler* _sampler
	)
	{
		if (_sampler)
		{
			if (!_sampler->Create(m_Device))
			{//! Error: Creation was unsuccessful
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{//! Pointer passed is not allocated
			return false;
		}
	}



	///************************************************************************** Rasterizer *******************************************************************************/
	/*!**********************************************************************************************************************************************************************



	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::CreateRasterizer
	(
		D3D_FillModes::E _fillMode,
		D3D_CullModes::E _cullMode,
		C_Rasterizer* _raster
	)
	{
		//! Check if pointer is not null
		if (_raster)
		{
			if 
			(//! Execute function and check if result was successful
				!_raster->Create
				(
					_fillMode,
					_cullMode,
					m_Device
				)
			)
			{//! Error was encountered!
				return false;
			}

			//! Everything is A-OK!
			return true;
		}

		else
		{//! Pointer passed was null ptr
			return false;
		}
	}
	///**********************************************************************************************************************************************************************

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	///**********************************************************************************************************************************************************************

	///																		SET PIPELINE OBJECTS

	///*********************************************************************************************************************************************************************/
	///************************************************************************ Output Merger ******************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Set a render target into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _renderTarget Render target to be set into the pipeline

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetRenderTarget
	(
		uint32			_numViews,
		C_DepthStencil* _depthStencil,
		C_RenderTarget* _renderTarget
	)
	{
		if (_renderTarget)
		{
			if (_depthStencil)
			{
				_renderTarget->Set(m_DC, _numViews, _depthStencil);
				return true;
			}

			else
			{
				return false;
			}
		}

		else
		{
			return false;
		}
	}



	/*!**********************************************************************************************************************************************************************

	@brief Clears the render target

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@param _renderTarget Render target to be set into the pipeline
	@param _clearColor Color passed to clear the render target

	************************************************************************************************************************************************************************/
	void C_GraphicsAPI::ClearRenderTarget
	(
		C_RenderTarget* _renderTarget,
		C_LinearColor	_clearColor
	)
	{
		if (_renderTarget)
		{
			_renderTarget->Clear(m_DC, _clearColor);
		}
	}



	void C_GraphicsAPI::ClearDepthStencilView
	(
		C_DepthStencil* _depth
	)
	{
		if (_depth)
		{
			_depth->ClearDSV(m_DC);
		}
	}



	///********************************************************************** Vertex shader stage **************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Sets a vertex shader to the pipeline to be compiled into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _vertexShader Vertex shader object to be set to the pipeline

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetVertexShader
	(
		C_VertexShader* _vertexShader
	)
	{
		if (_vertexShader)
		{
			_vertexShader->Set(m_DC);
			return true;
		}

		else
		{
			return false;
		}
	}



	///*********************************************************************** Pixel shader stage **************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Sets a pixel shader to the pipeline to be compiled into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _pixelShader Pixel shader object to be set to the pipeline

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetPixelShader
	(
		C_PixelShader* _pixelShader
	)
	{
		if (_pixelShader)
		{
			_pixelShader->Set(m_DC);
			return true;
		}

		else
		{
			return false;
		}
	}



	///**************************************************************************** Geometry *******************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Set a vertex data buffer into the GPU to be rendered

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _vBuff Buffer containing the vertex data

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetVertexBuffer
	(
		C_VBuffer* _vBuff
	)
	{
		if (_vBuff)
		{
			_vBuff->SetBuffer(m_DC);
			return true;
		}

		else
		{
			return false;
		}
	}



	/*!**********************************************************************************************************************************************************************

		@brief Set an index buffer into the GPU to be used

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _iBuff Buffer containing the indices of the geometry

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetIndexBuffer
	(
		DXGI_Formats::E _format,
		C_IBuffer32*	_iBuff
	)
	{
		if (_iBuff)
		{
			_iBuff->SetBuffer(m_DC, _format);
			return true;
		}

		else
		{
			return false;
		}
	}



	///************************************************************************ Input Assembler ****************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Set a render target into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _renderTarget Render target to be set into the pipeline

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetInputLayout
	(
		C_InputLayout* _inputLayout
	)
	{
		if (_inputLayout)
		{
			_inputLayout->SetInputLayout(m_DC);
			return true;
		}

		else
		{
			return false;
		}
	}



	/*!**********************************************************************************************************************************************************************

		@brief Set a render target into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _renderTarget Render target to be set into the pipeline

	************************************************************************************************************************************************************************/
	void C_GraphicsAPI::SetTopology
	(
		D3D_Topologies::E _topology
	)
	{
		ID3D11DeviceContext* _dc = reinterpret_cast<ID3D11DeviceContext*>(m_DC->GetPointer());
		_dc->IASetPrimitiveTopology
		(
			D3D11_PRIMITIVE_TOPOLOGY(_topology)
		);
	}



	/*!**********************************************************************************************************************************************************************

		@brief Set a render target into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _renderTarget Render target to be set into the pipeline

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetViewport
	(
		C_Viewport* _viewport
	)
	{
		if (_viewport)
		{
			_viewport->Set(m_DC);
			return true;
		}

		else
		{
			return false;
		}
	}



	///************************************************************************ Constant buffer ****************************************************************************/
	/*!**********************************************************************************************************************************************************************

		@brief Set a render target into the pipeline

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _renderTarget Render target to be set into the pipeline

	************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetConstantBuffer
	(
		uint32				_slot,
		uint32				_numBuffers,
		C_ConstantBuffer*	_cBuff
	)
	{
		if (_cBuff)
		{
			_cBuff->Set(m_DC, _slot, _numBuffers);
			return true;
		}

		else
		{
			return false;
		}
	}



	///********************************************************************* Shader Resource View ******************************************************************************/
	/*!**************************************************************************************************************************************************************************

		@brief
	
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param
		@param
		@param

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	****************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetShaderResourceView
	(
		uint32				_slot, 
		uint32				_numResources,
		C_ShaderResource*	_SRV
	)
	{
		if (_SRV)
		{
			_SRV->Set(m_DC, _slot, _numResources);
			return true;
		}

		else
		{
			return false;
		}
	}



	///*************************************************************************** Sampler *************************************************************************************/
	/*!**************************************************************************************************************************************************************************

		@brief

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return

	****************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetSampler
	(
		uint32		_slot,
		uint32		_numSamplers,
		C_Sampler*	_sampler
	)
	{
		if (_sampler)
		{
			_sampler->Set(m_DC, _slot, _numSamplers);
			return true;
		}

		else
		{
			return false;
		}
	}



	///************************************************************************** Rasterizer *******************************************************************************/
	/*!**************************************************************************************************************************************************************************

		@brief

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param

		@return

	****************************************************************************************************************************************************************************/
	bool C_GraphicsAPI::SetRasterizer
	(
		C_Rasterizer* _raster
	)
	{
		if (_raster)
		{
			_raster->Set(m_DC);
			return true;
		}

		else
		{
			return false;
		}
	}
	///**********************************************************************************************************************************************************************



	/**/
	void C_GraphicsAPI::DrawGeometry
	(
		uint32 _numIndices,
		uint32 _startIndexLoc,
		uint32 _baseVertexLoc
	)
	{
		ID3D11DeviceContext* _devContext = reinterpret_cast<ID3D11DeviceContext*>(m_DC->GetPointer());

		_devContext->DrawIndexed(_numIndices, _startIndexLoc, _baseVertexLoc);
	}



	/*!**********************************************************************************************************************************************************************

		@brief

	************************************************************************************************************************************************************************/
	void C_GraphicsAPI::Render
	(

	)
	{
		IDXGISwapChain* _swapChain = reinterpret_cast<IDXGISwapChain*>(m_SwapChain->GetPointer());
		_swapChain->Present(0, 0);
	}



	/*!**********************************************************************************************************************************************************************

		@brief

	************************************************************************************************************************************************************************/
	void C_GraphicsAPI::Close
	(

	)
	{
		IDXGISwapChain* _swapChain = reinterpret_cast<IDXGISwapChain*>(m_SwapChain->GetPointer());
		_swapChain->Release();
		delete m_SwapChain;

		ID3D11DeviceContext* _dc = reinterpret_cast<ID3D11DeviceContext*>(m_DC->GetPointer());
		_dc ->Release();
		delete m_DC;

		ID3D11Device* _device = reinterpret_cast<ID3D11Device*>(m_Device->GetPointer());
		_device->Release();
		delete m_Device;
	}
}