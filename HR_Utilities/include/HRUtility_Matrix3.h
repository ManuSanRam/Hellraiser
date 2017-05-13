#pragma once

#include "HRUtility_Prerequisites.h"

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_Math.h
 *
 * This file contains mathematic functions used inside the engine, contained inside a Platform-specific Math class.
 * The mathematic operations are as follows(in order):
 * - Absolute value (Integer and Floating-point).
 * - Pi (Normal, inverted, half and two-times)
 * - Euler constant.
 * - Minimum and maximum integer limits.
 * - Degree <-> Radian conversions.
 * - Infinite limits.
 * - Error margins.
 * - Thresholds.
 * - Truncations (Integer and Floating-point).
 * - Roundings (Floor, Round, Ceil).
 * - Fractional.
 * - Modulo.
 * - Power.
 * - Exponential.
 * - Logarithms (n-base, 2-base, x-base).
 * - Square roots - Normal and Inverted (Includes degrees and radians square roots).
 * - Check for limits (NaN, infinite and negative number).
 * - Trigonometrics - Sine[Arc], Cosine[Arc], Tangent[Arc, Arc2] (Degrees and Radians).
 * - Linear interpolation.
 * - Minimum and maximum number.
 *
 * @date	    11-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

#include "HRUtility_Vector3D.h"

namespace HR_SDK
{
  /*!
  */
  MS_ALIGN(16) class HR_UTILITY_EXPORT C_Matrix3
  {
  public:
    
	C_Matrix3()
	{
	  m_Element[0][0] = 0.0f; m_Element[0][1] = 0.0f; m_Element[0][2] = 0.0f;
	  m_Element[1][0] = 0.0f; m_Element[1][1] = 0.0f; m_Element[1][2] = 0.0f;
	  m_Element[2][0] = 0.0f; m_Element[2][1] = 0.0f; m_Element[2][2] = 0.0f;
	}

	C_Matrix3
	(
	  float _00, float _01, float _02,
	  float _10, float _11, float _12,
	  float _20, float _21, float _22
	)
	{
	  m_Element[0][0] = _00; m_Element[0][1] = _01; m_Element[0][2] = _00;
	  m_Element[1][0] = _10; m_Element[1][1] = _11; m_Element[1][2] = _12;
	  m_Element[2][0] = _20; m_Element[2][1] = _21; m_Element[2][2] = _22;
	}

	C_Matrix3(const C_Matrix3& prm_CopyMatrix)
	{
	  m_Element[0][0] = prm_CopyMatrix.m_Element[0][0]; m_Element[0][1] = prm_CopyMatrix.m_Element[0][1]; m_Element[0][2] = prm_CopyMatrix.m_Element[0][2];
	  m_Element[1][0] = prm_CopyMatrix.m_Element[1][0]; m_Element[1][1] = prm_CopyMatrix.m_Element[1][1]; m_Element[1][2] = prm_CopyMatrix.m_Element[1][2];
	  m_Element[2][0] = prm_CopyMatrix.m_Element[2][0]; m_Element[2][1] = prm_CopyMatrix.m_Element[2][1]; m_Element[2][2] = prm_CopyMatrix.m_Element[2][2];
	}

	~C_Matrix3()
	{

	}

    float m_Element[3][3];

	C_Matrix3 operator =  (const C_Matrix3& Matrix)
	{
		//! Copy the memory of the parameter into this object
		memcpy(this, &Matrix, sizeof(C_Matrix3));
		//! Return the current instance, which is carrying the current data
		return *this;
	}

	bool operator == (const C_Matrix3& Matrix)
	{
		for (uint32 i = 0; i < 3; ++i)
		{
			for (uint32 j = 0; j < 3; ++j)
			{
				if (m_Element[i][j] != Matrix.m_Element[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}

	bool operator != (const C_Matrix3& Matrix)
	{
		for (uint32 i = 0; i < 3; ++i)
		{
			for (uint32 j = 0; j < 3; ++j)
			{
				if (m_Element[i][j] != Matrix.m_Element[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}
	
	C_Matrix3 operator +  (const C_Matrix3& Matrix)
	{
		return C_Matrix3
		(
			this->m_Element[0][0] + Matrix.m_Element[0][0], this->m_Element[0][1] + Matrix.m_Element[0][1], this->m_Element[0][2] + Matrix.m_Element[0][2],
			this->m_Element[1][0] + Matrix.m_Element[1][0], this->m_Element[1][1] + Matrix.m_Element[1][1], this->m_Element[1][2] + Matrix.m_Element[1][2],
			this->m_Element[2][0] + Matrix.m_Element[2][0], this->m_Element[2][1] + Matrix.m_Element[2][1], this->m_Element[2][2] + Matrix.m_Element[2][2]
		);
	}
	
	C_Matrix3 operator += (const C_Matrix3& Matrix)
	{
		return *this + Matrix;
	}
	
	C_Matrix3 operator -  (const C_Matrix3& Matrix)
	{
		return C_Matrix3
		(
			this->m_Element[0][0] - Matrix.m_Element[0][0], this->m_Element[0][1] - Matrix.m_Element[0][1], this->m_Element[0][2] - Matrix.m_Element[0][2],
			this->m_Element[1][0] - Matrix.m_Element[1][0], this->m_Element[1][1] - Matrix.m_Element[1][1], this->m_Element[1][2] - Matrix.m_Element[1][2],
			this->m_Element[2][0] - Matrix.m_Element[2][0], this->m_Element[2][1] - Matrix.m_Element[2][1], this->m_Element[2][2] - Matrix.m_Element[2][2]
		);
	}
	
	C_Matrix3 operator -= (const C_Matrix3& Matrix)
	{
		return *this - Matrix;
	}

	C_Matrix3 operator * (const float& Scalar)
	{
		return C_Matrix3
		(
			this->m_Element[0][0] * Scalar, this->m_Element[0][1] * Scalar, this->m_Element[0][2] * Scalar,
			this->m_Element[1][0] * Scalar, this->m_Element[1][1] * Scalar, this->m_Element[1][2] * Scalar,
			this->m_Element[2][0] * Scalar, this->m_Element[2][1] * Scalar, this->m_Element[2][2] * Scalar
		);
	}

	C_Matrix3 operator *= (const float& Scalar)
	{
		return *this * Scalar;
	}

	static const C_Matrix3	IDENTITY;
	static const C_Matrix3	ZERO;

	C_Matrix3		Adjoint() const;
	float			Determinant() const;

	C_Matrix3		Translation(float prm_TX, float prm_TY, float prm_TZ);

	C_Matrix3		RotationX(float prm_Angle);
	C_Matrix3		RotationY(float prm_Angle);
	C_Matrix3		RotationZ(float prm_Angle);

	C_Matrix3		Scale(float prm_SX, float SY, float SZ);

	void			Identity();
	void			LookAt(C_Vector3D& );

	C_Matrix3		Transpose() const;
	C_Matrix3		Inverse() const;
  
  };
  GCC_ALIGN(16)
}