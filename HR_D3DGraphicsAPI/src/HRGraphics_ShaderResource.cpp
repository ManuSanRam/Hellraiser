#include "HRGraphics_ShaderResource.h"

/*!

	@file	HRGraphics_ShaderResource.cpp

*/

namespace HR_SDK
{
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
	
	struct GraphicsShaderResource
	{
		/*!
		*/
		GraphicsShaderResource() : ShaderResourceView(nullptr) {}

		/*!
		*/
		void* GetPointer() { return reinterpret_cast<void*>(ShaderResourceView); }

		/*!
		*/
		void** GetReference() { return reinterpret_cast<void**>(ShaderResourceView); }

		/*!
		*/
		ID3D11ShaderResourceView* ShaderResourceView;
	};

	/*!
	*/
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
		ID3D11ShaderResourceView** tempSRV = reinterpret_cast<ID3D11ShaderResourceView**>(m_ShaderResource->GetReference());
		// Pointer to device for fast use
		ID3D11Device* tempDevice = reinterpret_cast<ID3D11Device*>(_Device->GetPointer());
		// Pointer to device context for fast use
		ID3D11DeviceContext* tempDC = reinterpret_cast<ID3D11DeviceContext*>(_DC->GetPointer());
		// Pointer to texture buffer for fast use
		ID3D11Texture2D* tempText = reinterpret_cast<ID3D11Texture2D*>(_Texture->m_Texture->GetPointer());

		// Descriptor fot the Shader resource
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;

		// Set the shader resource descriptor
		ZeroMemory(&SRVDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		SRVDesc.Format = TranslateFormat(_Format);
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MostDetailedMip = 0;
		SRVDesc.Texture2D.MipLevels = -1;

		// Create the shader resource view for the texture.
		HRESULT Result = tempDevice->CreateShaderResourceView(tempText, &SRVDesc, tempSRV);
		if (FAILED(Result))
		{
			return false;
		}

		// Generate mipmaps for this texture.
		tempDC->GenerateMips(*tempSRV);

		return true;
	}

	/*!
	*/
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