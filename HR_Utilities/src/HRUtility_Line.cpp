#include "HRUtility_Line.h"

namespace HR_SDK
{
	void C_Line::Set
	(
		C_Vector3D prm_Start,
		C_Vector3D prm_End
	)
	{
		m_Start = prm_Start;
		m_End = prm_End;
	}
}