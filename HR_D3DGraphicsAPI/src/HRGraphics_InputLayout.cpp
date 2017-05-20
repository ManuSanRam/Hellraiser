#include "HRGraphics_InputLayout.h"

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

		ID3D11Device* Device;
	};

	struct GraphicsDeviceContext
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DC);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DC);
		}

		ID3D11DeviceContext* DC;
	};

	struct GraphicsInputLayout
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(InputLayout);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&InputLayout);
		}

		ID3D11InputLayout* InputLayout;
	};

	struct GraphicsBlob
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Blob);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Blob);
		}

		ID3D10Blob* Blob;
	};

	void C_InputLayout::AddInput
	(
		const char* Semantic,
		uint32 Index, 
		DXGI_Formats::E Format,
		uint32 ByteOffset)
	{
		D3D11_INPUT_ELEMENT_DESC InputElemDesc;
		InputElemDesc.SemanticName = Semantic;
		InputElemDesc.SemanticIndex = Index;
		InputElemDesc.Format = TranslateFormat(Format);
		InputElemDesc.InputSlot = 0;
		InputElemDesc.AlignedByteOffset = ByteOffset;
		InputElemDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputElemDesc.InstanceDataStepRate = 0;

		m_Inputs.push_back(InputElemDesc);
	}

	bool C_InputLayout::CreateInputLayout
	(
		GraphicsDevice* prm_Device,
		GraphicsBlob* Shader
	)
	{
		HRESULT ILResult;
		m_InputLayout = new GraphicsInputLayout;

		ILResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateInputLayout
		(
			&m_Inputs[0],
			GetInputCount(),
			reinterpret_cast<ID3D10Blob*>(Shader->GetPointer())->GetBufferPointer(),
			reinterpret_cast<ID3D10Blob*>(Shader->GetPointer())->GetBufferSize(),
			reinterpret_cast<ID3D11InputLayout**>(m_InputLayout->GetReference())
		);

		if (FAILED(ILResult))
		{
			return false;
		}

		return true;
	}

	void C_InputLayout::SetInputLayout
	(
		GraphicsDeviceContext* prm_DC
	)
	{
		reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->IASetInputLayout
		(
			reinterpret_cast<ID3D11InputLayout*>(m_InputLayout->GetPointer())
		);
	}

	void C_InputLayout::Close
	(

	)
	{
		if (m_InputLayout->InputLayout)
		{
			m_InputLayout->InputLayout->Release();
		}

		m_InputLayout->InputLayout = NULL;
	}
}