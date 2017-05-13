#include "HRUtility_Vector4D.h"
#include "HRUtility_PlatformMath.h"



namespace HR_SDK
{
	float      C_Vector4D::Length() const
	{
		return C_PlatformMath::SqRoot(C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f) + C_PlatformMath::Power<float>(m_z, 2.0f) + C_PlatformMath::Power<float>(m_w, 2.0f));
	}

	float      C_Vector4D::SqrLength() const
	{
		return (C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f) + C_PlatformMath::Power<float>(m_z, 2.0f) + C_PlatformMath::Power<float>(m_w, 2.0f));
	}

	float      C_Vector4D::Dot(const C_Vector4D& prm_Vector) const
	{
		return ((m_x * prm_Vector.m_x) + (m_y * prm_Vector.m_y) + (m_z * prm_Vector.m_z) + (m_w * prm_Vector.m_w));
	}
	
	float      C_Vector4D::Angle(const C_Vector4D& prm_Vector) const
	{
		return C_PlatformMath::ArcCosine((Dot(prm_Vector) * (1.0f / (Length() * prm_Vector.Length()))));
	}
			  
	void       C_Vector4D::Normalize()
	{
		*this *= 1.0f / Length();
	}
}