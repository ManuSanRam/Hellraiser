#pragma once

/*!******************************************************************************************************************************************************************************

	@file	HRGraphics_ShaderResource.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of a shader resource object, used to pass data like textures into the shader file to be sampled.
	The functions of this class are as described below:
	- Create a shader resource object, using data loaded into a texture buffer.
	- Set a shader resource object into the pipeline.
	- Release and deallocate the shader resource object, effectively deleting the memory block where it's contained.

	The class only takes parameters from the pipeline to be created and set, performing the task internally but being created by the pipeline.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		19-07-2017
	@author		Manuel Santos Ramón [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/

#include "HRGraphics_Prerequisites.h"
#include "HRGraphics_Texture.h"

namespace HR_SDK
{
	struct GraphicsDevice;
	struct GraphicsDeviceContext;
	struct GraphicsTexture;
	struct GraphicsShaderResource;

	class HR_D3DGRAPHICSAPI_EXPORT C_ShaderResource
	{
	public:
		/*!**********************************************************************************************************************************************************************

			@brief Constructor [Default]

		************************************************************************************************************************************************************************/
		C_ShaderResource
		(

		)
		{
			m_ShaderResource = NULL;
		}

		/*!**********************************************************************************************************************************************************************

			@brief Destructor

		************************************************************************************************************************************************************************/
		~C_ShaderResource
		(

		)
		{

		}

		/*!**********************************************************************************************************************************************************************

			@brief Creates a shader resource object using the data from a texture buffer.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _Format DXGI format used to give the format in the GPU
			@param _Texture Texture buffer containing the data of the image that will be sampled
			@param _Device Device object used to create the shader resource object
			@param _DC Device context object used to set the mip maps of the shader resource object

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return True if the shader resource object was created successfully, false if an error was encountered.

		************************************************************************************************************************************************************************/
		bool Create
		(
			DXGI_Formats::E			_Format,
			C_Texture*				_Texture,
			GraphicsDevice*			_Device,
			GraphicsDeviceContext*	_DC
		);

		/*!**********************************************************************************************************************************************************************

			@brief Releases and deallocates the object's data

		************************************************************************************************************************************************************************/
		void Close
		(

		);

		/*!**********************************************************************************************************************************************************************

			@brief Sets the shader resource to the pipeline

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _DC Device context pointer.
			@param _slot slot in the shader to be passed to the pixel shader
			@param _numSRVs Number of SRVs to be set to the pipeline

		************************************************************************************************************************************************************************/
		void Set
		(
			GraphicsDeviceContext*	_DC,
			uint32					_slot,
			uint32					_numSRVs
		);

		/*!**********************************************************************************************************************************************************************

			@brief Pointer to shader resource view.

		************************************************************************************************************************************************************************/
		GraphicsShaderResource*		m_ShaderResource;
	};
}
