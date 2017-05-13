#include "HRUtility_Prerequisites.h"

namespace HR_SDK
{
	/*!*/
	HR_THREAD_LOCAL uint64 C_MemoryCounter::m_Allocations = 0;

	/*!*/
	HR_THREAD_LOCAL uint64 C_MemoryCounter::m_Frees = 0;
}