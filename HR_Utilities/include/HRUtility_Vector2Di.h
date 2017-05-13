#pragma once

#include "HRUtility_Prerequisites.h"

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_Vector2Di.h
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
   * @brief Declares the 2D integer vector structure, which describes a point in 2D space
  */
  MS_ALIGN(4) class HR_UTILITY_EXPORT C_Vector2Di
  {
  public:
    /*!
    * @brief Defines the class' default constructor
    */
    C_Vector2Di() : m_x(0), m_y(0)
    {
    
    }
    
    //! Param
    C_Vector2Di(int32 prm_x, int32 prm_y) : m_x(prm_x), m_y(prm_y)
    {
    
    }
    
    //! Copy
    C_Vector2Di(C_Vector2Di& prm_Vector)
    {
      m_x = prm_Vector.m_x;
      m_y = prm_Vector.m_y;
    }

    /*!
    * @brief Defines the class destructor
    */
    ~C_Vector2Di()
    {
    
    }
    
    /*!
    * @brief Declares the vector's 'x' coordinate.
    */
    int32 m_x;

    /*!
    * @brief Declares the vector's 'y' coordinate.
    */
    int32 m_y;
    
	/*!
	* @brief Assignment operator between 2D vectors
	*/
	C_Vector2Di operator = (const C_Vector2Di& prm_Vector)
	{
		//! Copy the memory of the parameter into this object
		memcpy(this, &prm_Vector, sizeof(C_Vector2Di));
		//! Return the current instance, which is carrying the current data
		return *this;
	}

    /*!
     * @brief Access operator to the vector's members
     * @param prm_Index Index in which
    */
    int32& operator [](uint32 prm_Index)
    {
	  //! Make sure the index passed as parameter is not negative or surpasses the limit of coordinates (3)
	  HR_ASSERTION(prm_Index > 0 && prm_Index < 2);
      //if (prm_Index < 2)
       return (&m_x)[prm_Index];
    }
    
	bool operator == (const C_Vector2Di& prm_Vector)
	{
		//! If any of the vector's element mismatch with its correspondant element in the parameter, returns false. Else return true.
		return (this->m_x == prm_Vector.m_x && this->m_y == prm_Vector.m_y);
	}

	bool operator != (const C_Vector2Di& prm_Vector)
	{
		return (this->m_x != prm_Vector.m_x && this->m_y != prm_Vector.m_y);
	}
    
	bool operator < (const C_Vector2Di& prm_Vector)
	{
		return (this->m_x < prm_Vector.m_x && this->m_y < prm_Vector.m_y);
	}
    
	bool operator <= (const C_Vector2Di& prm_Vector)
	{
		return (this->m_x <= prm_Vector.m_x && this->m_y <= prm_Vector.m_y);
	}
    
	bool operator > (const C_Vector2Di& prm_Vector)
	{
		return (this->m_x > prm_Vector.m_x && this->m_y > prm_Vector.m_y);
	}
    
	bool operator >= (const C_Vector2Di& prm_Vector)
	{
		return (this->m_x >= prm_Vector.m_x && this->m_y >= prm_Vector.m_y);
	}
    
	C_Vector2Di operator + (const C_Vector2Di& prm_Vector) const
	{
		C_Vector2Di result(this->m_x + prm_Vector.m_x, this->m_y + prm_Vector.m_y);
		return result;
	}
    
	C_Vector2Di operator += (const C_Vector2Di& prm_Vector) const
	{
		return *this + prm_Vector;
	}
    
	C_Vector2Di operator - (const C_Vector2Di& prm_Vector) const
	{
		C_Vector2Di result(this->m_x - prm_Vector.m_x, this->m_y - prm_Vector.m_y);
		return result;
	}
    
	C_Vector2Di operator -= (const C_Vector2Di& prm_Vector) const
	{
		return *this - prm_Vector;
	}
    
	C_Vector2Di operator * (const float prm_Scalar) const
	{
		C_Vector2Di result(int32(this->m_x * prm_Scalar), int32(this->m_y * prm_Scalar));
		return result;
	}
    
	C_Vector2Di operator *= (const float prm_Scalar) const
	{
		return *this * prm_Scalar;
	}
    
	C_Vector2Di operator / (const float prm_Scalar) const
	{
		C_Vector2Di result(int32(this->m_x / prm_Scalar), int32(this->m_y / prm_Scalar));
		return result;
	}
    
	C_Vector2Di operator /= (const float prm_Scalar) const
	{
		return *this / prm_Scalar;
	}
    
    float Length() const;
    float SqrLength() const;
    int32 Dot(const C_Vector2Di& prm_Vector) const;
    float Angle(const C_Vector2Di& prm_Vector) const;
    
    void Normalize();

    float Cross(const C_Vector2Di& prm_Vector);
  };
  GCC_ALIGN(16)
}