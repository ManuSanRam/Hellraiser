#include "HRUtility_Sphere.h"
#include "HRUtility_PlatformMath.h"

namespace HR_SDK
{
	void C_Sphere::Set
	(
		C_Vector3D		prm_Vector,
		float			prm_Radius
	)
	{
		m_Center = prm_Vector;
		m_Radius = prm_Radius;
	}

	float C_Sphere::CalculateCircumference()
	{
		return 2.0f * (C_PlatformMath::m_Pi * m_Radius);
	}

	float C_Sphere::CalculateVolume()
	{
		return (4.0f / 3.0f) * (C_PlatformMath::m_Pi * C_PlatformMath::Power(m_Radius, 3.0f));
	}


}