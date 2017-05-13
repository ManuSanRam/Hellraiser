#pragma once

#include "HRUtility_Prerequisites.h"

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_Vector2D.h
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
 * @date         11-09-2016
 * @author       Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright    Infernal Coders S.A.
*************************************************************************************************************************************************************/


namespace HR_SDK
{
  /*!
   * @class C_Vector2D
   * @brief Declares the 2D vector object, which is a vector in 2D space
  */
  MS_ALIGN(4) class HR_UTILITY_EXPORT C_Vector2D
  {
  public:
	/*!
	 * @brief Defines the class' default constructor
	*/
	C_Vector2D() : m_x(0.0f), m_y(0.0f)
	{

	}

	//! Param
	C_Vector2D(float prm_x, float prm_y) : m_x(prm_x), m_y(prm_y)
	{

	}

	//! Copy
	C_Vector2D(C_Vector2D& prm_Vector)
	{
		m_x = prm_Vector.m_x;
		m_y = prm_Vector.m_y;
	}

	/*!
	 * @brief Defines the class destructor
	*/
	~C_Vector2D() 
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

	/*!********************************************************************************************************************************************************************
	 * @brief Assignment operator between 2D vectors
	***********************************************************************************************************************************************************************/
	C_Vector2D operator = (const C_Vector2D& prm_Vector)
	{
		//! Copy the memory of the parameter into this object
		memcpy(this, &prm_Vector, sizeof(C_Vector2D));
		//! Return the current instance, which is carrying the current data
		return *this;
	}

	/*!********************************************************************************************************************************************************************
	***********************************************************************************************************************************************************************/
	void Set(float X, float Y)
	{
		m_x = X;
		m_y = Y;
	}

	/*!********************************************************************************************************************************************************************
	 * @brief Access operator to the vector's members
	 * @param prm_Index Index in which 
	***********************************************************************************************************************************************************************/
	float& operator [](uint32 prm_Index)
	{
		//! Make sure the index passed as parameter is not negative or surpasses the limit of coordinates (3)
		HR_ASSERTION(prm_Index > 0 && prm_Index < 3);
	  if(prm_Index < 2)
	    return (&m_x)[prm_Index];
	}

	bool operator == (const C_Vector2D& prm_Vector)
	{
		//! If any of the vector's element mismatch with its correspondant element in the parameter, returns false. Else return true.
		return (this->m_x == prm_Vector.m_x && this->m_y == prm_Vector.m_y);
	}
	
	bool operator != (const C_Vector2D& prm_Vector)
	{
		return (this->m_x != prm_Vector.m_x && this->m_y != prm_Vector.m_y);
	}
	
	bool operator < (const C_Vector2D& prm_Vector)
	{
		return (this->m_x < prm_Vector.m_x && this->m_y < prm_Vector.m_y);
	}
	
	bool operator <= (const C_Vector2D& prm_Vector)
	{
		return (this->m_x <= prm_Vector.m_x && this->m_y <= prm_Vector.m_y);
	}

	bool operator > (const C_Vector2D& prm_Vector)
	{
		return (this->m_x > prm_Vector.m_x && this->m_y > prm_Vector.m_y);
	}
	
	bool operator >= (const C_Vector2D& prm_Vector)
	{
		return (this->m_x >= prm_Vector.m_x && this->m_y >= prm_Vector.m_y);
	}

	C_Vector2D operator + (const C_Vector2D& prm_Vector) const
	{
		C_Vector2D result(this->m_x + prm_Vector.m_x, this->m_y + prm_Vector.m_y);
		return result;
	}
	
	C_Vector2D operator += (const C_Vector2D& prm_Vector) const
	{
		return *this + prm_Vector;
	}
	
	C_Vector2D operator - (const C_Vector2D& prm_Vector) const
	{
		C_Vector2D result(this->m_x - prm_Vector.m_x, this->m_y - prm_Vector.m_y);
		return result;
	}
	
	C_Vector2D operator -= (const C_Vector2D& prm_Vector) const
	{
		return *this - prm_Vector;
	}

	C_Vector2D operator * (const float prm_Scalar) const
	{
		C_Vector2D result(this->m_x * prm_Scalar, this->m_y * prm_Scalar);
		return result;
	}
	
	C_Vector2D operator *= (const float prm_Scalar) const
	{
		return *this * prm_Scalar;
	}
	
	C_Vector2D operator / (const float prm_Scalar) const
	{
		C_Vector2D result(this->m_x / prm_Scalar, this->m_y / prm_Scalar);
		return result;
	}
	
	C_Vector2D operator /= (const float prm_Scalar) const
	{
		return *this / prm_Scalar;
	}

	float Length() const;
	float SqrLength() const;
	float Dot(const C_Vector2D& prm_Vector) const;
	float Angle(const C_Vector2D& prm_Vector) const;
	
	void Normalize();

	float Cross(const C_Vector2D& prm_Vector);
  };
}