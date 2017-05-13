#include "HRUtility_Matrix3.h"

namespace HR_SDK
{
	C_Matrix3     C_Matrix3::Adjoint() const
	{
		C_Matrix3 CofMatrix
		(
			(1.0f * (m_Element[1][1] * m_Element[2][2]) - (m_Element[2][1] * m_Element[1][2])), (-1.0f * (m_Element[1][0] * m_Element[2][2]) - (m_Element[2][0] * m_Element[1][2])), (1.0f * (m_Element[1][0] * m_Element[2][1]) - (m_Element[2][0] * m_Element[1][1])),
			(-1.0f * (m_Element[0][1] * m_Element[2][2]) - (m_Element[2][1] * m_Element[0][2])), (1.0f * (m_Element[0][0] * m_Element[2][2]) - (m_Element[2][0] * m_Element[0][2])), (-1.0f * (m_Element[0][0] * m_Element[2][1]) - (m_Element[2][0] * m_Element[0][1])),
			(1.0f * (m_Element[0][1] * m_Element[1][2]) - (m_Element[1][1] * m_Element[0][2])), (-1.0f * (m_Element[0][0] * m_Element[1][2]) - (m_Element[1][0] * m_Element[0][2])), (1.0f * (m_Element[0][0] * m_Element[1][1]) - (m_Element[1][0] * m_Element[0][1]))
		);

		return CofMatrix.Transpose();
	}

	float     C_Matrix3::Determinant() const
	{
		return
		(
			(m_Element[0][0] * m_Element[1][1] * m_Element[2][2]) +
			(m_Element[0][1] * m_Element[1][2] * m_Element[2][0]) +
			(m_Element[0][2] * m_Element[1][0] * m_Element[2][1]) -
			(m_Element[2][0] * m_Element[1][1] * m_Element[0][2]) -
			(m_Element[2][1] * m_Element[1][2] * m_Element[0][0]) -
			(m_Element[2][2] * m_Element[1][0] * m_Element[0][1])
		);
	}

	C_Matrix3 C_Matrix3::Transpose() const
	{
		C_Matrix3 temp(*this);

		return C_Matrix3
		(
			temp.m_Element[0][0], temp.m_Element[1][0], temp.m_Element[2][0],
			temp.m_Element[0][1], temp.m_Element[1][1], temp.m_Element[2][1],
			temp.m_Element[0][2], temp.m_Element[1][2], temp.m_Element[2][2]
		);
	}
	
	C_Matrix3 C_Matrix3::Inverse() const
	{
		return (this->Adjoint() * (1.0f / this->Determinant()));
	}
}