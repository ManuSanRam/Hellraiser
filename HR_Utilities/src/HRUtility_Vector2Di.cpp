#include "HRUtility_Vector2Di.h"
#include "HRUtility_PlatformMath.h"

/*!
*/

namespace HR_SDK
{
	/*!
	*/
	float       C_Vector2Di::Length() const
	{
		return C_PlatformMath::SqRoot(C_PlatformMath::Power<float>((float)m_x, 2.0f) + C_PlatformMath::Power<float>((float)m_y, 2.0f));
	}

	/*!
	*/
	float       C_Vector2Di::SqrLength() const
	{
		return (C_PlatformMath::Power<float>((float)m_x, 2.0f) + C_PlatformMath::Power<float>((float)m_y, 2.0f));
	}

	/*!
	*/
	int32       C_Vector2Di::Dot(const C_Vector2Di& prm_Vector) const
	{
		return
		(
			m_x * prm_Vector.m_x, + m_y * prm_Vector.m_y
		);
	}
	
	/*!
	*/
	float       C_Vector2Di::Angle(const C_Vector2Di& prm_Vector) const
	{
		return C_PlatformMath::ArcCosine((Dot(prm_Vector) * (1.0f / (Length() * prm_Vector.Length()))));
	}
	
	/*!
	*/
	void        C_Vector2Di::Normalize()
	{
		*this *= 1.0f / Length();
	}
	
	/*!
	*/
	float       C_Vector2Di::Cross(const C_Vector2Di& prm_Vector)
	{
		return float((m_y * prm_Vector.m_x) - (m_x * prm_Vector.m_y));
	}
}