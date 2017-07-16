#include "HRUtility_Vector2D.h"
#include "HRUtility_PlatformMath.h"

/*!
*/

namespace HR_SDK
{
	/*!
	*/
	void C_Vector2D::Set(float prm_X, float prm_Y)
	{
		//! Set values of X and Y elements of the vector...
		m_x = prm_X;
		m_y = prm_Y;
	}

	/*!
	*/
	float      C_Vector2D::Length() const
	{
		return C_PlatformMath::SqRoot(C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f));
	}
	
	/*!
	*/
	float      C_Vector2D::SqrLength() const
	{
		return (C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f));
	}
	
	/*!
	*/
	float      C_Vector2D::Dot(const C_Vector2D& prm_Vector) const
	{
		return
		(
			m_x * prm_Vector.m_x, +m_y * prm_Vector.m_y
		);
	}
	
	/*!
	*/
	float      C_Vector2D::Angle(const C_Vector2D& prm_Vector) const
	{
		return C_PlatformMath::ArcCosine((Dot(prm_Vector) * (1.0f / (Length() * prm_Vector.Length()))));
	}

	/*!
	*/
	void       C_Vector2D::Normalize()
	{
		*this *= 1.0f / Length();
	}
	
	/*!
	*/
	C_Vector2D      C_Vector2D::Cross(const C_Vector2D& prm_Vector)
	{
		return C_Vector2D((m_y * prm_Vector.m_x), (m_x * prm_Vector.m_y));
	}
}