#pragma once

#include "HRGraphics_Prerequisites.h"

/*!************************************************************************************************************************************************************************
*
* @file		HRGraphics_Prerequisites.h
*
***************************************************************************************************************************************************************************/

namespace HR_SDK
{
	struct GraphicsDevice;
	struct GraphicsRenderTargetView;

	/*!
	*/
	class HR_D3DGRAPHICSAPI_EXPORT C_RenderTarget
	{
	public:
		/*!**********************************************************************************************************************************************************************

			@brief Constructor [default]

		************************************************************************************************************************************************************************/
		C_RenderTarget()
		{
			m_RTV = nullptr;
		}

		/*!

			@brief Destructor

		*/
		~C_RenderTarget()
		{

		}

		/*!
			
			@brief Creates a render target using a texture

		*/
		bool		Create
		(

		);
		
		/*!

			@brief Closes the render target

		*/
		void		Close
		(

		);

		GraphicsRenderTargetView* m_RTV;
	};
}
