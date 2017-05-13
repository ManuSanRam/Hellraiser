#include "HRGraphics_Texture.h"

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
		C_Filestream*		prm_File, 
		uint32				prm_Width, 
		uint32				prm_Height, 
		uint32				prm_MipLevels, 
		D3D_Formats::E		prm_Format,
		D3D_Usages::E		prm_Usage,
		D3D_Binds::E		prm_Bind,
		D3D_Access::E		prm_Access

	)
	{
		D3D11_TEXTURE2D_DESC desc;

		desc.Width = prm_Width;
		desc.Height = prm_Height;
		desc.MipLevels = desc.ArraySize = prm_MipLevels;
		desc.Format = TranslateFormat(prm_Format);
		desc.SampleDesc.Count = 1;
		desc.Usage = TranslateUsage(prm_Usage);
		desc.BindFlags = TranslateBind(prm_Bind);
		desc.CPUAccessFlags = TranslateAccess(prm_Access);
		desc.MiscFlags = 0;

		return true;
	}

	bool C_Texture::CreateAsRTV
	(
		GraphicsDevice* prm_Device, 
		GraphicsSwapChain* prm_SC
	)
	{
		m_Texture = new GraphicsTexture();
		HRESULT FuncResult = reinterpret_cast<IDXGISwapChain*>(prm_SC->GetPointer())->GetBuffer(0, __uuidof(ID3D11Texture2D), m_Texture->GetReference());

		if (FAILED(FuncResult))
		{
			return false;
		}

		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateRenderTargetView
		(
			reinterpret_cast<ID3D11Resource*>(m_Texture->GetPointer()), 
			NULL, 
			reinterpret_cast<ID3D11RenderTargetView**>(m_RTV->GetReference())
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
		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->OMSetRenderTargets
		(
			prm_NumViews,
			reinterpret_cast<ID3D11RenderTargetView**>(m_RTV->GetReference()),
			reinterpret_cast<ID3D11DepthStencilView*>(prm_DSV->GetPointer())
		);
	}

	void C_Texture::ClearRTV(GraphicsDeviceContext* prm_DC, C_LinearColor prm_Color)
	{
		float Color[] = { prm_Color.GetRed(), prm_Color.GetGreen(), prm_Color.GetBlue(), prm_Color.GetAlpha() };
		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->ClearRenderTargetView
		(
			reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer()),
			Color
		);
	}

	void C_Texture::Close()
	{
		if (reinterpret_cast<ID3D11Texture2D*>(m_Texture->GetPointer()))
		{
			reinterpret_cast<ID3D11Texture2D*>(m_Texture->GetPointer())->Release();
		}

		if (reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer()))
		{
			reinterpret_cast<ID3D11RenderTargetView*>(m_RTV->GetPointer())->Release();
		}
	}
}