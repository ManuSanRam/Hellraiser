#pragma once

/*!************************************************************************************************************************************************************************
 * @file
 *
 *
 *
 *
 *
 * @date
 * @author
 * @copyright
***************************************************************************************************************************************************************************/

namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	* @brief Abstraction of DXGI formats
	***********************************************************************************************************************************************************************/
	namespace DXGI_Formats
	{
		/*!
		*/
		enum E
		{
			UNKNOWN,				/*! Unknown DXGI format. */
			RGBA_32_TYPELESS,		/*! 32-bit RGBA of non-specific type format. */
			RGBA_32_FLOAT,			/*! 32-bit RGBA of float type format. */
			RGBA_32_UINT,			/*! 32-bit RGBA of unsigned integer type format */
			RGBA_32_INT,			/*! 32-bit RGBA of signed integer type format */
			RGB_32_TYPELESS,		/*! 32-bit RGBA of non-specific type format. */
			RGB_32_FLOAT,			/*! 32-bit RGBA of float type format. */
			RGB_32_UINT,			/*! 32-bit RGBA of unsigned integer type format */
			RGB_32_INT,				/*! 32-bit RGBA of signed integer type format */
			RGBA_16_TYPELESS,		/*! 32-bit RGBA of non-specific type format. */
			RGBA_16_FLOAT,			/*! 32-bit RGBA of float type format. */
			RGBA_16_UNORM,			/*! 32-bit RGBA of unsigned integer type format */
			RGBA_16_UINT,			/*! 32-bit RGBA of signed integer type format */
			RGBA_16_NORM,			/*! 32-bit RGBA of non-specific type format. */
			RGBA_16_INT,			/*! 32-bit RGBA of float type format. */
			RG_32_TYPELESS,			/*! 32-bit RGBA of unsigned integer type format */
			RG_32_FLOAT,			/*! 32-bit RGBA of signed integer type format */
			RG_32_UINT,				/*! 32-bit RGBA of non-specific type format. */
			RG_32_INT,				/*! 32-bit RGBA of float type format. */
			RGBA_8_TYPELESS = 27,	/*! 32-bit RGBA of unsigned integer type format */
			RGBA_8_UNORM,			/*! 32-bit RGBA of signed integer type format */
			RGBA_8_UNORM_SRGB,		/*! 32-bit RGBA of non-specific type format. */
			RGBA_8_UINT,			/*! 32-bit RGBA of float type format. */
			RGBA_8_SNORM,			/*! 32-bit RGBA of unsigned integer type format */
			RGBA_8_SINT,			/*! 32-bit RGBA of signed integer type format */
			R_32_UINT = 42,			/*! 32-bit RGBA of non-specific type format. */
			D_24_UNORM_S8_UINT = 45,/*! 32-bit RGBA of float type format. */
		};							
	}								

	/*!
	*/
	namespace DXGI_CPUAccess
	{
		const uint32 NONE		 = 0	;
		const uint32 DYNAMIC	 = 1	;
		const uint32 READ_WRITE	 = 2	;
		const uint32 SCRATCH	 = 3	;
		const uint32 FIELD       = 15	;
	}

	/*!
	*/
	namespace DXGI_Usage
	{
		const uint64 SHADER_INPUT			= (1L << (0 + 4));
		const uint64 RENDER_TARGET_OUTPUT	= (1L << (1 + 4));
		const uint64 BACK_BUFFER			= (1L << (2 + 4));
		const uint64 SHARED					= (1L << (3 + 4));
		const uint64 READ_ONLY				= (1L << (4 + 4));
		const uint64 DISCARD_ON_PRESENT		= (1L << (5 + 4));
		const uint64 UNORDERED_ACCESS		= (1L << (6 + 4));
	}

	/*!
	*/
	namespace DXGI_Scanlines
	{
		enum E
		{
			UNSPECIFIED,
			PROGRESSIVE,
			UPPER_FIELD_FIRST,
			LOWER_FIELD_FIRST
		};
	}

	/*!
	*/
	namespace DXGI_Scaling
	{
		/*!
		*/
		enum E
		{
			UNSPECIFIED,
			CENTERED,
			STRETCHED
		};
	}

	/*!
	*/
	namespace DXGI_SwapEffect
	{
		/*!
		*/
		enum E
		{
			DISCARD,
			SEQUENTIAL
		};
	}
}