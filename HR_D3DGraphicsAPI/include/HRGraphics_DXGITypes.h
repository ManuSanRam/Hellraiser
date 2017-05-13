#pragma once

namespace HR_SDK
{
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