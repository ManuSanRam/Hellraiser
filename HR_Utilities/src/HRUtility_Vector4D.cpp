#include "HRUtility_Vector4D.h"
#include "HRUtility_PlatformMath.h"

/*!
*/

namespace HR_SDK
{
	/*!
	*/
	void C_Vector4D::Set
	(
		float prm_X,
		float prm_Y,
		float prm_Z,
		float prm_W
	)
	{
		m_x = prm_X;
		m_y = prm_Y;
		m_z = prm_Z;
		m_w = prm_W;
	}

	/*!
	*/
	float      C_Vector4D::Length
	(

	) const
	{
		return C_PlatformMath::SqRoot(C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f) + C_PlatformMath::Power<float>(m_z, 2.0f) + C_PlatformMath::Power<float>(m_w, 2.0f));
	}

	/*!
	*/
	float      C_Vector4D::SqrLength
	(

	) const
	{
		return (C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f) + C_PlatformMath::Power<float>(m_z, 2.0f) + C_PlatformMath::Power<float>(m_w, 2.0f));
	}

	/*!
	*/
	float      C_Vector4D::Dot
	(
		const C_Vector4D& prm_Vector
	) const
	{
		return ((m_x * prm_Vector.m_x) + (m_y * prm_Vector.m_y) + (m_z * prm_Vector.m_z) + (m_w * prm_Vector.m_w));
	}
	
	/*!
	*/
	float      C_Vector4D::Angle
	(
		const C_Vector4D& prm_Vector
	) const
	{
		return C_PlatformMath::ArcCosine((Dot(prm_Vector) * (1.0f / (Length() * prm_Vector.Length()))));
	}
	
	/*!
	*/
	C_Vector4D C_Vector4D::Cross
	(
		const C_Vector4D& prm_Vector
	) const
	{
		return C_Vector4D
		(
			(m_y * prm_Vector.m_z) - (m_z * prm_Vector.m_y),
			(m_z * prm_Vector.m_x) - (m_x * prm_Vector.m_z),
			(m_x * prm_Vector.m_y) - (m_y * prm_Vector.m_x),
			0.0f
		);
	}

	/*!
	*/
	C_Vector4D  C_Vector4D::UnitCross
	(
		const C_Vector4D& prm_Vector
	) const
	{
		C_Vector4D UC = this->Cross(prm_Vector);
		UC.Normalize();
		return UC;
	}

	/*!
	*/
	void       C_Vector4D::Normalize
	(

	)
	{
		*this *= 1.0f / Length();
	}
}