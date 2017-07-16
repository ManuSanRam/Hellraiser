#include "HRGraphics_Depth.h"

namespace HR_SDK
{
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
		GraphicsDepthStencilState() : DSS(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DSS);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DSS);
		}

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

	/*!
	*/
	bool C_DepthStencil::CreateDSBuffer
	(
		uint32			prm_W, 
		uint32			prm_H,
		DXGI_Formats::E	prm_Format,
		D3D_Usages::E	prm_Usage,
		D3D_Binds::E	prm_Bind,
		GraphicsDevice*	prm_Device
	)
	{
		m_DSB = new GraphicsDepthStencilBuffer;

		HRESULT FuncResult;
		D3D11_TEXTURE2D_DESC DSBDesc;

		// Set up the description of the depth buffer.
		DSBDesc.Width = prm_W;
		DSBDesc.Height = prm_H;
		DSBDesc.MipLevels = 1;
		DSBDesc.ArraySize = 1;
		DSBDesc.Format = TranslateFormat(prm_Format);
		DSBDesc.SampleDesc.Count = 1;
		DSBDesc.SampleDesc.Quality = 0;
		DSBDesc.Usage = TranslateUsage(prm_Usage);
		DSBDesc.BindFlags = TranslateBind(prm_Bind);
		DSBDesc.CPUAccessFlags = 0;
		DSBDesc.MiscFlags = 0;

		// Create the texture for the depth buffer using the filled out description.
		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateTexture2D(&DSBDesc, NULL, reinterpret_cast<ID3D11Texture2D**>(m_DSB->GetReference()));
		if (FAILED(FuncResult))
		{
			return false;
		}
		return true;
	}

	/*!
	*/
	bool C_DepthStencil::CreateDSState
	(
		GraphicsDevice*				prm_Device, 
		GraphicsDeviceContext*		prm_DC
	)
	{
		m_DSS = new GraphicsDepthStencilState;

		HRESULT FuncResult;
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

		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateDepthStencilState
		(
			&DSSDesc, 
			reinterpret_cast<ID3D11DepthStencilState**>(m_DSS->GetReference())
		);
		if (FAILED(FuncResult))
		{
			return false;
		}

		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->OMSetDepthStencilState(
			reinterpret_cast<ID3D11DepthStencilState*>(m_DSS->GetPointer()), 1);
		if (m_DSS == NULL)
		{
			return false;
		}

		return true;
	}

	/*!
	*/
	bool C_DepthStencil::CreateDSView
	(
		GraphicsDevice*				prm_Device, 
		GraphicsDeviceContext*		prm_DC,
		DXGI_Formats::E				prm_Format
	)
	{
		m_DSV = new GraphicsDepthStencilView;

		HRESULT FuncResult;
		D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
		ZeroMemory(&DSVDesc, sizeof(DSVDesc));

		DSVDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DSVDesc.Texture2D.MipSlice = 0;

		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateDepthStencilView
		(
			reinterpret_cast<ID3D11Resource*>(m_DSB->GetPointer()), 
			&DSVDesc, 
			reinterpret_cast<ID3D11DepthStencilView**>(m_DSV->GetReference())
		);

		if (FAILED(FuncResult))
		{
			return false;
		}

		return true;
	}

	/*!
	*/
	void C_DepthStencil::ClearDSV
	(
		GraphicsDeviceContext* prm_DC
	)
	{
		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->ClearDepthStencilView
		(
			reinterpret_cast<ID3D11DepthStencilView*>(m_DSV->GetPointer()),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0
		);
	}

	/*!
	*/
	void C_DepthStencil::Close()
	{
		//! Check if Depth Stencil View exists
		if (m_DSV)
		{
			//! Check if 
			if (m_DSV->DSV)
			{
				reinterpret_cast<ID3D11DepthStencilView*>(m_DSV->GetPointer())->Release();
			}
		}

		else
		{
			m_DSV = NULL;
		}

		if (m_DSS)
		{
			if (m_DSS->DSS)
			{
				reinterpret_cast<ID3D11DepthStencilState*>(m_DSS->GetPointer())->Release();
			}
		}

		else
		{
			m_DSS = NULL;
		}

		if (m_DSB)
		{
			if (m_DSB->Buffer)
			{
				reinterpret_cast<ID3D11Texture2D*>(m_DSB->GetPointer())->Release();
			}
		}

		else
		{
			m_DSB = NULL;
		}

	}
}