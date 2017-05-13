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
 * @date        26-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

namespace HR_SDK
{
  /*!
  @class C_Vector3D
  @brief Declares the 3D vector structure for a point in 3D space
  */
  class HR_UTILITY_EXPORT C_Vector4D
  {
  public:
    /*!
     * @brief Defines the class' default constructor
    */
    C_Vector4D() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f)
    {
    
    }
    
    /*!
	 * @brief Defines the class' parameter constructor
	*/
    C_Vector4D(float prm_x, float prm_y, float prm_z, float prm_w) : m_x(prm_x), m_y(prm_y), m_z(prm_z), m_w(prm_w)
    {
    
    }
    
    /*!
	 * @brief Defines the class' copy constructor
	*/
    C_Vector4D(const C_Vector4D& prm_Vector)
    {
	  this->m_x = prm_Vector.m_x;
	  this->m_y = prm_Vector.m_y;
	  this->m_z = prm_Vector.m_z;
	  this->m_w = prm_Vector.m_w;
    }
    
    /*!
     * @brief Defines the class destructor
    */
    ~C_Vector4D()
    {
    
    }
    
    /*!
     * @brief Declares the vector's 'x' coordinate.
    */
    float m_x;
    
    /*!
     * @brief Declares the vector's 'y' coordinate.
    */
    float m_y;
    
	/*!
	 * @brief Declares the vector's 'z' coordinate
	*/
    float m_z;
    
	/*!
	 * @brief Declares the vector's 'w' coordinate
	*/
    float m_w;
    
	/*!
	 * @brief Assignment operator between 2D vectors
	*/
	C_Vector4D operator = (const C_Vector4D& prm_Vector)
	{
	  memcpy(this, &prm_Vector, sizeof(C_Vector4D));
	  return *this;
	}

    /*!
    @brief Access operator to the vector's members
    @param prm_Index Index in which
    */
    float&     operator [](uint32 prm_Index)
    {
		HR_ASSERTION(prm_Index < 4);
        return (&m_x)[prm_Index];
    }
    
    bool       operator == (const C_Vector4D& prm_Vector)
	{
		return (this->m_x == prm_Vector.m_x && this->m_y == prm_Vector.m_y && this->m_z == prm_Vector.m_z && this->m_w == prm_Vector.m_w);
	}

    bool       operator != (const C_Vector4D& prm_Vector)
	{
		return (this->m_x != prm_Vector.m_x && this->m_y != prm_Vector.m_y && this->m_z != prm_Vector.m_z && this->m_w != prm_Vector.m_w);
	}

    bool       operator < (const C_Vector4D& prm_Vector)
	{
		return (this->m_x < prm_Vector.m_x && this->m_y < prm_Vector.m_y && this->m_z < prm_Vector.m_z && this->m_w < prm_Vector.m_w);
	}

    bool       operator <= (const C_Vector4D& prm_Vector)
	{
		return (this->m_x <= prm_Vector.m_x && this->m_y <= prm_Vector.m_y && this->m_z <= prm_Vector.m_z && this->m_w <= prm_Vector.m_w);
	}

    bool       operator > (const C_Vector4D& prm_Vector)
	{
		return (this->m_x > prm_Vector.m_x && this->m_y > prm_Vector.m_y && this->m_z > prm_Vector.m_z && this->m_w > prm_Vector.m_w);
	}

    bool       operator >= (const C_Vector4D& prm_Vector)
	{
		return (this->m_x >= prm_Vector.m_x && this->m_y >= prm_Vector.m_y && this->m_z >= prm_Vector.m_z && this->m_w >= prm_Vector.m_w);
	}
    
    C_Vector4D operator + (const C_Vector4D& prm_Vector) const
	{
		C_Vector4D result(this->m_x + prm_Vector.m_x, this->m_y + prm_Vector.m_y, this->m_z + prm_Vector.m_z, this->m_w + prm_Vector.m_w);
		return result;
	}

    C_Vector4D operator += (const C_Vector4D& prm_Vector) const
	{
		return *this + prm_Vector;
	}

    C_Vector4D operator - (const C_Vector4D& prm_Vector) const
	{
		C_Vector4D result(this->m_x - prm_Vector.m_x, this->m_y - prm_Vector.m_y, this->m_z - prm_Vector.m_z, this->m_w - prm_Vector.m_w);
		return result;
	}

    C_Vector4D operator -= (const C_Vector4D& prm_Vector) const
	{
		return *this - prm_Vector;
	}
    
    C_Vector4D operator * (const float prm_Scalar) const
	{
		C_Vector4D result(this->m_x * prm_Scalar, this->m_y * prm_Scalar, this->m_z * prm_Scalar, this->m_w * prm_Scalar);
		return result;
	}

    C_Vector4D operator *= (const float prm_Scalar) const
	{
		return *this * prm_Scalar;
	}

    C_Vector4D operator / (const float prm_Scalar) const
	{
		C_Vector4D result(this->m_x / prm_Scalar, this->m_y / prm_Scalar, this->m_z / prm_Scalar, this->m_w / prm_Scalar);
		return result;
	}

    C_Vector4D operator /= (const float prm_Scalar) const
	{
		return *this / prm_Scalar;
	}
    
    float      Length() const;
    float      SqrLength() const;
    float      Dot(const C_Vector4D& prm_Vector) const;
    float      Angle(const C_Vector4D& prm_Vector) const;

	C_Vector4D Cross(const C_Vector4D& prm_Vector) const;
	C_Vector4D Cross3(const C_Vector4D& prm_Vector) const;
    
    void       Normalize();
  };
}