#include "HRGraphics_Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "externals/stb_image.h"

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

	struct GraphicsShaderResourceView
	{
		GraphicsShaderResourceView() : SRV(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(SRV);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&SRV);
		}

		ID3D11ShaderResourceView* SRV;
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

	bool C_Texture::CreateFromFile
	(
		const String&			prm_FileName,
		GraphicsDevice*			prm_Device,
		GraphicsDeviceContext*	prm_DC
	)
	{
		HRESULT TextResult;
		int32 Width = 0, Height = 0, CompNum = 0;

		//! Load data from image
		unsigned char* ImageData = stbi_load(prm_FileName.c_str(), &Width, &Height, &CompNum, STBI_rgb_alpha);
		ID3D11Device* TmpDevice = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer());
		ID3D11Texture2D* TmpTexture = reinterpret_cast<ID3D11Texture2D*>(m_Texture->GetReference());
		ID3D11ShaderResourceView* TmpSRV = reinterpret_cast<ID3D11ShaderResourceView*>(m_SRV->GetReference());

		D3D11_TEXTURE2D_DESC T2DDesc;
		T2DDesc.Width = Width;
		T2DDesc.Height = Height;
		T2DDesc.MipLevels = 1; 
		T2DDesc.ArraySize = 0;
		T2DDesc.Format = TranslateFormat(DXGI_Formats::RGBA_8_UNORM);
		T2DDesc.SampleDesc.Count = 1;
		T2DDesc.Usage = TranslateUsage(D3D_Usages::DEFAULT);
		T2DDesc.BindFlags = TranslateBind(D3D_Binds::SHADER_RESOURCE);
		T2DDesc.CPUAccessFlags = TranslateAccess(D3D_Access::NONE);
		T2DDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

		//! Create texture object
		TextResult = TmpDevice->CreateTexture2D(&T2DDesc, NULL, &TmpTexture);
		if (FAILED(TextResult))
		{
			return false;
		}

		//! Save copy of Device Context
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer());

		//! Update image data into texture object
		TmpDC->UpdateSubresource(TmpTexture, 0, NULL, ImageData, (Width * 4) * sizeof(unsigned char), 0);

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;

		SRVDesc.Format = T2DDesc.Format;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MostDetailedMip = 0;
		SRVDesc.Texture2D.MipLevels = -1;

		// Create the shader resource view for the texture.
		TextResult = TmpDevice->CreateShaderResourceView(TmpTexture, &SRVDesc, &TmpSRV);
		if (FAILED(TextResult))
		{
			return false;
		}

		// Generate mipmaps for this texture.
		TmpDC->GenerateMips(TmpSRV);

		TmpTexture->Release();
		stbi_image_free(ImageData);
		return true;
	}

	bool C_Texture::CreateAsRTV
	(
		GraphicsDevice* prm_Device, 
		GraphicsSwapChain* prm_SC
	)
	{
		//! TO-DO: Change this stuff to single reinterpretations - Thursday May 18th, 2017
		m_Texture = new GraphicsTexture();

		IDXGISwapChain* TmpSC = reinterpret_cast<IDXGISwapChain*>(prm_SC->GetPointer());

		HRESULT FuncResult = TmpSC->GetBuffer(0, __uuidof(ID3D11Texture2D), m_Texture->GetReference());

		if (FAILED(FuncResult))
		{
			return false;
		}

		m_RTV = new GraphicsRenderTargetView();
		ID3D11Device* TmpDev = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer());
		ID3D11Resource* TmpRes = reinterpret_cast<ID3D11Resource*>(m_Texture->GetPointer());
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

		reinterpret_cast<ID3D11Texture2D*>(m_Texture->GetPointer())->Release();
		return true;
	}

	void C_Texture::SetRTV(GraphicsDeviceContext* prm_DC, uint32 prm_NumViews, GraphicsDepthStencilView* prm_DSV)
	{
		//! Simplify function, reducing castings to one and using them temporal pointers (They after exiting scope) - Thursday May 18th, 2017
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer());
		ID3D11RenderTargetView** TmpRTV = reinterpret_cast<ID3D11RenderTargetView**>(m_RTV->GetReference());
		ID3D11DepthStencilView* TmpDSV = reinterpret_cast<ID3D11DepthStencilView*>(prm_DSV->GetPointer());

		//! Set the render target to the device context
		TmpDC->OMSetRenderTargets
		(
			prm_NumViews,
			TmpRTV,
			TmpDSV
		);
	}

	void C_Texture::ClearRTV(GraphicsDeviceContext* prm_DC, C_LinearColor prm_Color)
	{
		float Color[] = { prm_Color.GetRed(), prm_Color.GetGreen(), prm_Color.GetBlue(), prm_Color.GetAlpha() };

		//! Reduce castings to one. Temporal pointer die after leaving function scope
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer());
		ID3D11RenderTargetView* TmpRTV = reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer());

		//! Clear RTV - Thursday May 18th, 2017
		TmpDC->ClearRenderTargetView
		(
			TmpRTV,
			Color
		);
	}

	void C_Texture::Close()
	{
		//! Reduce the castings to single one. Temporal pointers die after leaving function scope
		ID3D11Texture2D* TmpText = reinterpret_cast<ID3D11Texture2D*>(m_Texture->GetPointer());
		ID3D11RenderTargetView* TmpRTV = reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer());

		//! Verify pointers to perform safe DirectX resource release
		if (TmpText != NULL)
		{
			TmpText->Release();
		}

		//! Make sure that pointer doesn't carry trash
		TmpText = NULL;

		//! If not, jut make sure pointer carries no garbage - Thursday May 18th, 2017
		if (TmpRTV != NULL)
		{
			TmpRTV->Release();
		}
		//! Make sure that pointer doesn't carry trash - Friday May 19th, 2017
		TmpRTV = NULL;
	}
}