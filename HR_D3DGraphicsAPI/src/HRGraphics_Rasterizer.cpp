/*!******************************************************************************************************************************************************************************

	@file		HRGraphics_Rasterizer.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of the Rasterizer object, used to present graphics as:
	- Wireframe, rendering only the edges that connect the vertices.
	- Solid, rendering the model as it would normally look.
	- Solid - wireframe, rendering the model in solid and wireframe

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		29-07-2017
	@author		Manuel Santos Ramón [ManuSanRam]
	copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/


#include "HRGraphics_Rasterizer.h"
#include <d3d11.h>


namespace HR_SDK
{
	/*!**************************************************************************************************************************************************************************

		@brief Direct 3D interface for a rasterizer state object.

	****************************************************************************************************************************************************************************/
	struct GraphicsDevice
	{
		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		GraphicsDevice() : Device(nullptr) {}


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		void* GetPointer() { return reinterpret_cast<void*>(Device); }


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		void** GetReference() { return reinterpret_cast<void**>(&Device); }


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		ID3D11Device* Device;
	};


	/*!**************************************************************************************************************************************************************************

		@brief Direct 3D interface for a rasterizer state object.

	****************************************************************************************************************************************************************************/
	struct GraphicsDeviceContext
	{
		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		GraphicsDeviceContext() : DevCon(nullptr) {}


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		void* GetPointer() { return reinterpret_cast<void*>(DevCon); }


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		void** GetReference() { return reinterpret_cast<void**>(&DevCon); }


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		ID3D11DeviceContext* DevCon;
	};


	/*!**************************************************************************************************************************************************************************

		@brief Direct 3D interface for a rasterizer state object.

	****************************************************************************************************************************************************************************/
	struct GraphicsRasterizerState
	{
		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		GraphicsRasterizerState() : RasterizerState(nullptr) {}


		/*!**********************************************************************************************************************************************************************

			@brief Get the pointer to rasterizer state

		************************************************************************************************************************************************************************/
		void* GetPointer() { return reinterpret_cast<void*>(RasterizerState); }


		/*!**********************************************************************************************************************************************************************

			@brief Get the reference to the address pointed by Rasterizer state

		************************************************************************************************************************************************************************/
		void** GetReference() { return reinterpret_cast<void**>(&RasterizerState); }


		/*!**********************************************************************************************************************************************************************

			@brief Direct 3D interface for a rasterizer state object.

		************************************************************************************************************************************************************************/
		ID3D11RasterizerState* RasterizerState;
	};


	/*!**************************************************************************************************************************************************************************

		@brief Creates a rasterizer state object

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _fillMode Mode to render the geometry.
		The fill modes are:
		- SOLID: Renders geometry as planes in between the vertices.
		- WIREFRAME: Renders geometry as connections between the vertices, simply rendering as a net.

		@param _cullMode Mode to specify the faces that will be drawn on screen
		The culling modes are:
		- NONE: All triangles are drawn.
		- FRONT: Triangles facing front are not rendering.
		- BACK: Triangles facing back are not rendering.

		@param _device Device passing the rasterizer to GPU

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return True if rasterizer was successfully created, false if any errors occurred.

	****************************************************************************************************************************************************************************/
	bool C_Rasterizer::Create
	(
		D3D_FillModes::E _fillMode,
		D3D_CullModes::E _cullMode,
		GraphicsDevice* _device
	)
	{
		//! Allocate rasterizer to pass to pipeline
		m_Rasterizer = new GraphicsRasterizerState();

		//! Descriptor of the rasterizer to be created in the device
		D3D11_RASTERIZER_DESC RasterDesc;

		//! Clean the object for use
		ZeroMemory(&RasterDesc, sizeof(D3D11_RASTERIZER_DESC));
		
		//! Set parameters
		RasterDesc.FillMode = D3D11_FILL_MODE(_fillMode);
		RasterDesc.CullMode = D3D11_CULL_MODE(_cullMode);

		//! Access pointer that will point to that information
		ID3D11RasterizerState** rasterizer = reinterpret_cast<ID3D11RasterizerState**>(m_Rasterizer->GetReference());
		ID3D11Device* device = reinterpret_cast<ID3D11Device*>(_device->GetPointer());

		//! Create the rasterizer
		HRESULT RasterResult = device->CreateRasterizerState(&RasterDesc, rasterizer);

		//! Check for errors on creation of rasterizer
		if (FAILED(RasterResult))
		{
			//! There was an error during the rasterizer creation
			return false;
		}

		//! Everything is A-OK!
		return true;

	}



	/*!**************************************************************************************************************************************************************************

	@brief Closes and deallocates

	****************************************************************************************************************************************************************************/
	void C_Rasterizer::Close
	(

	)
	{
		if (m_Rasterizer)
		{
			//! Release the Direct3D object 
			ID3D11RasterizerState* rasterizer = reinterpret_cast<ID3D11RasterizerState*>(m_Rasterizer->GetPointer());
			rasterizer->Release();

			//! Deallocate pointer
			delete m_Rasterizer;
		}

		//! Prevent pointer from carrying trash
		m_Rasterizer = NULL;
	}



	/*!**************************************************************************************************************************************************************************

	@brief Sets a rasterizer state into the device context

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@param _DC Device context pointing to the GPU, used to set the rasterizer to the pipeline.

	****************************************************************************************************************************************************************************/
	void C_Rasterizer::Set
	(
		GraphicsDeviceContext* _DC
	)
	{
		ID3D11DeviceContext* devContext;
		
		//! check if the DC passed is valid (Not NULL).
		if (_DC != NULL)
		{
			devContext = reinterpret_cast<ID3D11DeviceContext*>(_DC->GetPointer());
		}
		
		else
		{
			//! Exit the function if an error
			return;
		}

		ID3D11RasterizerState* rasterizer = reinterpret_cast<ID3D11RasterizerState*>(m_Rasterizer->GetPointer());

		//! Sets the rasterizer in the device context passed as parameterdevContext->
		devContext->RSSetState(rasterizer);
	}



}