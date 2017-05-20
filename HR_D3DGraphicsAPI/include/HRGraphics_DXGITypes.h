#pragma once

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
			RGBA_32_UINT,			/*!  */
			RGBA_32_INT,
			RGB_32_TYPELESS,
			RGB_32_FLOAT,
			RGB_32_UINT,
			RGB_32_INT,
			RGBA_16_TYPELESS,
			RGBA_16_FLOAT,
			RGBA_16_UNORM,
			RGBA_16_UINT,
			RGBA_16_NORM,
			RGBA_16_INT,
			RG_32_TYPELESS,
			RG_32_FLOAT,
			RG_32_UINT,
			RG_32_INT,
			RGBA_8_TYPELESS = 27,
			RGBA_8_UNORM,
			RGBA_8_UNORM_SRGB,
			RGBA_8_UINT,
			RGBA_8_SNORM,
			RGBA_8_SINT,
			R_32_UINT = 42,
			D_24_UNORM_S8_UINT = 45,
		};
	}

	inline DXGI_FORMAT				TranslateFormat
	(
		DXGI_Formats::E prm_Format
	)
	{
		return (DXGI_FORMAT)prm_Format;
	}

	namespace DXGI_CPUAccess
	{
		const uint32 NONE		 = 0	;
		const uint32 DYNAMIC	 = 1	;
		const uint32 READ_WRITE	 = 2	;
		const uint32 SCRATCH	 = 3	;
		const uint32 FIELD       = 15	;
	}

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

	namespace DXGI_Scanline
	{
		enum E
		{
			UNSPECIFIED,
			PROGRESSIVE,
			UPPER_FIELD_FIRST,
			LOWER_FIELD_FIRST
		};
	}

	namespace DXGI_Scaling
	{
		enum E
		{
			UNSPECIFIED,
			CENTERED,
			STRETCHED
		};
	}

	namespace DXGI_SwapEffect
	{
		enum E
		{
			DISCARD,
			SEQUENTIAL
		};
	}
}