#include "HRGraphics_Rasterizer.h"

/*!

	@file	HRGraphics_ShaderResource.cpp

*/

namespace HR_SDK
{
	/*!
	*/
	struct GraphicsDevice
	{
		/*!
		*/
		GraphicsDevice() : Device(nullptr) {}

		/*!
		*/
		void* GetPointer() { return reinterpret_cast<void*>(Device); }

		/*!
		*/
		void** GetReference() { return reinterpret_cast<void**>(Device); }

		/*!
		*/
		ID3D11Device* Device;
	};

	/*!
	*/
	struct GraphicsDeviceContext
	{
		/*!
		*/
		GraphicsDeviceContext() : DevCon(nullptr) {}

		/*!
		*/
		void* GetPointer() { return reinterpret_cast<void*>(DevCon); }

		/*!
		*/
		void** GetReference() { return reinterpret_cast<void**>(DevCon); }

		/*!
		*/
		ID3D11DeviceContext* DevCon;
	};

	/*!
	*/
	struct GraphicsRasterizerState
	{
		/*!
		*/
		GraphicsRasterizerState() : RasterizerState(nullptr) {}

		/*!
		*/
		void* GetPointer() { return reinterpret_cast<void*>(RasterizerState); }

		/*!
		*/
		void** GetReference() { return reinterpret_cast<void**>(RasterizerState); }

		/*!
		*/
		ID3D11RasterizerState* RasterizerState;
	};

	/*!
	*/
	bool C_Rasterizer::Create
	(
		D3D_FillModes::E _FillMode,
		D3D_CullModes::E _CullMode,
		GraphicsDevice* _Device
	)
	{
		m_Rasterizer = new GraphicsRasterizerState();

		//! Descriptor of the rasterizer to be created in the device
		D3D11_RASTERIZER_DESC RasterDesc;

		//! Clean the object for use
		ZeroMemory(&RasterDesc, sizeof(D3D11_RASTERIZER_DESC));
		
		//! Set parameters
		RasterDesc.FillMode = TranslateFillMode(_FillMode);
		RasterDesc.CullMode = TranslateCullMode(_CullMode);

		//! Access pointer that will point to that information
		ID3D11RasterizerState** rasterizer = reinterpret_cast<ID3D11RasterizerState**>(m_Rasterizer->GetReference());
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_Device->GetPointer());

		//! Create the rasterizer
		HRESULT RasterResult = device->CreateRasterizerState(&RasterDesc, rasterizer);

		//! Check for errors on creation of rasterizer
		if (FAILED(RasterResult))
		{
			//! There was an error during the rasterizer creation
			return false;
		}

		//! Everything's A-OK!
		return true;

	}

	/*!
	*/
	void C_Rasterizer::Close
	(

	)
	{

	}

	/*!
	*/
	void C_Rasterizer::Set
	(
		GraphicsDeviceContext* _DC
	)
	{

	}
}