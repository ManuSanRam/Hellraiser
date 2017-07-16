#pragma once

/*!******************************************************************************************************************************************************************************

	@file	HRGraphics_ShaderResource.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



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
		/*!
		*/
		C_ShaderResource
		(

		)
		{
			m_ShaderResource = nullptr;
		}

		/*!
		*/
		~C_ShaderResource
		(

		)
		{

		}

		/*!
		*/
		bool Create
		(
			DXGI_Formats::E			_Format,
			C_Texture*				_Texture,
			GraphicsDevice*			_Device,
			GraphicsDeviceContext*	_DC
		);

		/*!
		*/
		void Close
		(

		);

		/*!
		*/
		void Set
		(
			GraphicsDeviceContext* _DC,
			uint32 _slot,
			uint32 _numSRVs
		);

		/*!
		*/
		GraphicsShaderResource* m_ShaderResource;
	};
}
