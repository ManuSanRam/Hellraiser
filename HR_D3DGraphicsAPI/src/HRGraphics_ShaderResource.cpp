/*!******************************************************************************************************************************************************************************

	@file	HRGraphics_ShaderResource.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the definition of the function specified in the class C_ShaderResource.
	It also contains the definition of the forward-declared structures used to encapsulate certain API specific objects.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		19-07-2017
	@author		Manuel Santos Ram'on [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/
#include "HRGraphics_ShaderResource.h"
#include <d3d11.h>

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
		void** GetReference() { return reinterpret_cast<void**>(&Device); }

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
		void** GetReference() { return reinterpret_cast<void**>(&DevCon); }

		/*!
		*/
		ID3D11DeviceContext* DevCon;
	};
	
	
	
	/*!
	*/
	struct GraphicsTexture
	{
		GraphicsTexture() : Texture(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Texture);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Texture);
		}

		ID3D11Texture2D* Texture;
	};
	


	/*!
	*/
	struct GraphicsShaderResource
	{
		/*!
		*/
		GraphicsShaderResource()
		{
			ShaderResourceView = nullptr;
		}

		/*!
		*/
		void* GetPointer() 
		{ 
			return reinterpret_cast<void*>(ShaderResourceView); 
		}

		/*!
		*/
		void** GetReference() 
		{ 
			return reinterpret_cast<void**>(&ShaderResourceView); 
		}

		/*!
		*/
		ID3D11ShaderResourceView* ShaderResourceView;
	};



	/*!**************************************************************************************************************************************************************************

		@brief Creates a shader resource object using the data from a texture buffer.
	
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _Format DXGI format used to give the format in the GPU
		@param _Texture Texture buffer containing the data of the image that will be sampled
		@param _Device Device object used to create the shader resource object
		@param _DC Device context object used to set the mip maps of the shader resource object

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return True if the shader resource object was created successfully, false if an error was encountered.

	****************************************************************************************************************************************************************************/
	bool C_ShaderResource::Create
	(
		DXGI_Formats::E			_Format,
		C_Texture*				_Texture,
		GraphicsDevice*			_Device,
		GraphicsDeviceContext*	_DC
	)
	{
		// Create shader resource view object to receive the image data to the shader 
		m_ShaderResource = new GraphicsShaderResource();



		ID3D11ShaderResourceView** srv = reinterpret_cast<ID3D11ShaderResourceView**>(m_ShaderResource->GetReference());
		// Pointer to device for fast use
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_Device->GetPointer());
		// Pointer to device context for fast use
		ID3D11DeviceContext* dc = reinterpret_cast<ID3D11DeviceContext*>(_DC->GetPointer());
		// Pointer to texture buffer for fast use
		ID3D11Texture2D* texture = reinterpret_cast<ID3D11Texture2D*>(_Texture->m_Texture->GetPointer());



		// Descriptor fot the Shader resource
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;

		// Set the shader resource descriptor
		ZeroMemory(&SRVDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		SRVDesc.Format = (DXGI_FORMAT)_Format;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MostDetailedMip = 0;
		SRVDesc.Texture2D.MipLevels = -1;

		// Create the shader resource view for the texture.
		HRESULT Result = device->CreateShaderResourceView(texture, &SRVDesc, srv);
		if (FAILED(Result))
		{
			return false;
		}

		// Generate mip maps for this texture.
		dc->GenerateMips(*srv);

		return true;
	}



	/*!**************************************************************************************************************************************************************************

		@brief Releases and deallocates the object's data

	****************************************************************************************************************************************************************************/
	void C_ShaderResource::Close
	(

	)
	{
		//! Verify pointers to perform safe DirectX resource release
		if (m_ShaderResource != NULL)
		{
			ID3D11ShaderResourceView* tempSRV = reinterpret_cast<ID3D11ShaderResourceView*>(m_ShaderResource->GetPointer());
			if (tempSRV)
			{
				tempSRV->Release();
			}
			delete tempSRV;
		}
	}



	/*!**************************************************************************************************************************************************************************

		@brief Sets the shader resource to the pipeline

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _DC Device context pointer.
		@param _slot slot in the shader to be passed to the pixel shader
		@param _numSRVs Number of SRVs to be set to the pipeline

	****************************************************************************************************************************************************************************/
	void C_ShaderResource::Set
	(
		GraphicsDeviceContext* _DC,
		uint32 _slot,
		uint32 _numSRVs
	)
	{
		ID3D11ShaderResourceView** tempSRV = reinterpret_cast<ID3D11ShaderResourceView**>(m_ShaderResource->GetReference());
		// Pointer to device context for fast use
		ID3D11DeviceContext* tempDC = reinterpret_cast<ID3D11DeviceContext*>(_DC->GetPointer());

		tempDC->PSSetShaderResources(_slot, _numSRVs, tempSRV);
	}
}