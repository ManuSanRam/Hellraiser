/*!************************************************************************************************************************************************************************
*
*	@file		HRCore_Application.h
*
*	This file contains the declaration of class C_Application.
*	This class is used as an interface to create, control and render applications in any platform.
*	The basic functions of this class are:
*	- Initialize: Starts the application, passing any parameters to correctly start up the application.
*	- Update: Updates the application's window and the logic of the application.
*	-
*
*	@date			26-09-2016
*	@author			Manuel Aldair Santos Ramón (ManuSanRam)
*	@copyright		Infernal Coders S.A.
*
***************************************************************************************************************************************************************************/
#include "HRGraphics_Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "externals/stb_image.h"
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
	
	bool C_Texture::CreateFromFile
	(
		const String&			_FileName,
		DXGI_Formats::E			_Format,
		GraphicsDevice*			_Device,
		GraphicsDeviceContext*	_DC
	)
	{
		HRESULT TextResult;
		int32 Width = 0, Height = 0, CompNum = 0;

		//! Allocate the texture buffer
		m_Texture = new GraphicsTexture();

		//! Load image data to byte array
		unsigned char* ImageData = stbi_load(_FileName.c_str(), &Width, &Height, &CompNum, STBI_rgb_alpha);

		//! Manage pointers by reinterpretation
		ID3D11Device* TmpDevice = reinterpret_cast<ID3D11Device*>(_Device->GetPointer());
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(_DC->GetPointer());
		ID3D11Texture2D** TmpTexture = reinterpret_cast<ID3D11Texture2D**>(m_Texture->GetReference());

		//! Create texture descriptor
		D3D11_TEXTURE2D_DESC T2DDesc;
		ZeroMemory(&T2DDesc, sizeof(D3D11_TEXTURE2D_DESC));

		T2DDesc.Width = Width;
		T2DDesc.Height = Height;
		T2DDesc.MipLevels = 1; 
		T2DDesc.ArraySize = 1;
		T2DDesc.Format = (DXGI_FORMAT)_Format;
		T2DDesc.SampleDesc.Count = 1;
		T2DDesc.SampleDesc.Quality = 0;
		T2DDesc.Usage = D3D11_USAGE_DEFAULT;
		T2DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		T2DDesc.CPUAccessFlags = 0;
		T2DDesc.MiscFlags = 0;

		//! Create texture buffer object
		TextResult = TmpDevice->CreateTexture2D(&T2DDesc, NULL, TmpTexture);
		if (FAILED(TextResult))
		{
			//! Error was encountered, exit with failure
			return false;
		}

		//! Update image data into texture object
		TmpDC->UpdateSubresource
		(
			*TmpTexture, 
			0, 
			NULL, 
			ImageData, 
			(Width * 4) * sizeof(unsigned char), 
			0
		);

		//! Free the original image data. Don't need it here, since it's saved on texture buffer pointer
		stbi_image_free(ImageData);
		return true;
	}

	void C_Texture::Close()
	{
		//! Verify pointers to perform safe DirectX resource release
		if (m_Texture != NULL)
		{
			ID3D11Texture2D* TmpText = reinterpret_cast<ID3D11Texture2D*>(m_Texture->GetPointer());
			if (TmpText) 
			{ 
				TmpText->Release(); 
			}
			
			delete m_Texture;
		}

		//! Point to address 0 to prevent trash carriage
		m_Texture = NULL;
	}
}