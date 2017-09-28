#include "HRGraphics_Sampler.h"
#include <d3d11.h>



/*!******************************************************************************************************************************************************************************

	@file	HRGraphics_ShaderResource.cpp

	@date
	@author
	@copyright

********************************************************************************************************************************************************************************/



namespace HR_SDK
{
	/*!**************************************************************************************************************************************************************************

		@brief Abstracted data structure to operate on Direct X 11 devices

	****************************************************************************************************************************************************************************/
	struct GraphicsDevice
	{
		/*!**********************************************************************************************************************************************************************

			@brief Constructor [Default]

		************************************************************************************************************************************************************************/
		GraphicsDevice() : Device(nullptr) {}



		/*!**********************************************************************************************************************************************************************

			@brief Get the pointer to the device

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return Data pointer to the device

		************************************************************************************************************************************************************************/
		void* GetPointer() { return reinterpret_cast<void*>(Device); }



		/*!**********************************************************************************************************************************************************************

			@brief Get the reference to the device.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return 

		************************************************************************************************************************************************************************/
		void** GetReference() { return reinterpret_cast<void**>(&Device); }



		/*!

			@brief Device pointer

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
	struct GraphicsSamplerState
	{
		/*!
		*/
		GraphicsSamplerState() : SamplerState(nullptr) {}

		/*!
		*/
		void* GetPointer() { return reinterpret_cast<void*>(SamplerState); }

		/*!
		*/
		void** GetReference() { return reinterpret_cast<void**>(&SamplerState); }

		/*!
		*/
		ID3D11SamplerState* SamplerState;
	};



	/*!
	*/
	bool C_Sampler::Create
	(
		GraphicsDevice* _Device
	)
	{
		//! Allocate the sampler object for use
		m_Sampler = new GraphicsSamplerState();

		//! Create sampler descriptor
		D3D11_SAMPLER_DESC SamplerDesc;
		ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));

		//! Set descriptor's info
		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		SamplerDesc.MinLOD = 0;
		SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		//! Reinterpret data for use of pointers
		ID3D11SamplerState** sampler = reinterpret_cast<ID3D11SamplerState**>(m_Sampler->GetReference());
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_Device->GetPointer());

		//! Create the sampler
		HRESULT SamplerResult = device->CreateSamplerState(&SamplerDesc, sampler);

		//! Check for errors in the creation of the sampler
		if (FAILED(SamplerResult))
		{
			//! Error encountered
			return false;
		}

		//! Everything's A-OK
		return true;

	}

	/*!
	*/
	void C_Sampler::Close
	(

	)
	{
		if (m_Sampler != nullptr)
		{
			ID3D11SamplerState* temp = reinterpret_cast<ID3D11SamplerState*>(m_Sampler->GetPointer());
			if (temp != nullptr)
			{
				temp->Release();
			}

			delete m_Sampler;
			m_Sampler = NULL;
		}
	}

	/*!
	*/
	void C_Sampler::Set
	(
		GraphicsDeviceContext* _DC,
		uint32	_slot,
		uint32	_numSamplers
	)
	{
		ID3D11DeviceContext* temp = reinterpret_cast<ID3D11DeviceContext*>(_DC->GetPointer());
		ID3D11SamplerState** tempSS = reinterpret_cast<ID3D11SamplerState**>(m_Sampler->GetReference());

		temp->PSSetSamplers(_slot, _numSamplers, tempSS);
	}
}