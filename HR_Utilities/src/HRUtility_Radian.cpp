#include "HRUtility_Radian.h"

#include "HRUtility_Degree.h"
#include "HRUtility_PlatformMath.h"

namespace HR_SDK
{
	C_Radian::C_Radian(const C_Degree& prm_ValueInDegrees)
	{
		m_Value = (prm_ValueInDegrees.m_Value * C_PlatformMath::m_DegreeToRadian);
	}

	float C_Radian::GetValueInDegrees()
	{
		return (m_Value * C_PlatformMath::m_RadianToDegree);
	}

	float C_Radian::GetValue() const
	{
		return m_Value;
	}
}