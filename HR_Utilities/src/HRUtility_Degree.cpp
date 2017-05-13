#include "HRUtility_Degree.h"

#include "HRUtility_Radian.h"
#include "HRUtility_PlatformMath.h"

namespace HR_SDK
{
	C_Degree::C_Degree(const C_Radian& prm_ValueInRadians)
	{
		m_Value = (prm_ValueInRadians.m_Value * C_PlatformMath::m_RadianToDegree);
	}

	float C_Degree::GetValueInRadians()
	{
		return (m_Value * C_PlatformMath::m_DegreeToRadian);
	}

	float C_Degree::GetValue() const
	{
		return m_Value;
	}

}