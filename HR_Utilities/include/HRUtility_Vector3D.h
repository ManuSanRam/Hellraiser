#pragma once

#include "HRUtility_Prerequisites.h"

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_Vector3D.h
 *
 * This file contains mathematic functions for vectorial operations in 3D space.
 * The vectorial operations are as follows(in order):
 * - Length (Squared and normal).
 * - Normalization of vector.
 * - Dot product.
 * - Cross product.
 * - Unit cross product.
 * - Perpendicular vector.
 * - Unitary perpendicular vector.
 * - Direction of vector (Angle).
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
  class HR_UTILITY_EXPORT C_Vector3D
  {
  public:

    /*!
    * @brief Defines the class' default constructor
    */
    C_Vector3D() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
    {
  
    }
  
    //! Param
    C_Vector3D(float prm_x, float prm_y, float prm_z) : m_x(prm_x), m_y(prm_y), m_z(prm_z)
    {
  
    }
  
    //! Copy
    C_Vector3D(C_Vector3D& prm_Vector)
    {
  	  m_x = prm_Vector.m_x;
  	  m_y = prm_Vector.m_y;
  	  m_z = prm_Vector.m_z;
    }
  
    /*!
     * @brief Defines the class destructor
    */
    ~C_Vector3D()
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
	 * @brief Declares the vector's 'z' coordinate.
	*/
    float m_z;

	/*!
	 * @brief Access operator to the vector's members.
	 * @param prm_Index Index to the element's vector.
	 * @return The reference to one of the vector's coordinates (x, y, z).
	*/
	float&      operator [](uint32 prm_Index)
	{
		//! Make sure the index passed as parameter is not negative or surpasses the limit of coordinates (3)
		HR_ASSERTION(prm_Index > 0 && prm_Index < 3);
		//! Return the reference to the vector's element (either x, y or z)
		return (&m_x)[prm_Index];
	}

	/*!
	 * @brief Assignment operator between 3D vectors
	*/
	C_Vector3D operator = (const C_Vector3D& prm_Vector)
	{
		//! Copy the memory of the parameter into this object
		memcpy(this, &prm_Vector, sizeof(C_Vector3D));
		//! Return the current instance, which is carrying the current data
		return *this;
	}

	void Set(float X, float Y, float Z)
	{
		m_x = X;
		m_y = Y;
		m_z = Z;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    bool       operator == (const C_Vector3D& prm_Vector)
	{
		//! If any of the vector's element mismatch with its correspondant element in the parameter, returns false. Else return true.
		return (this->m_x == prm_Vector.m_x && this->m_y == prm_Vector.m_y && this->m_z == prm_Vector.m_z);
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    bool       operator != (const C_Vector3D& prm_Vector)
	{
		return (this->m_x != prm_Vector.m_x && this->m_y != prm_Vector.m_y && this->m_z != prm_Vector.m_z);
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    bool       operator < (const C_Vector3D& prm_Vector)
	{
		return (this->m_x < prm_Vector.m_x && this->m_y < prm_Vector.m_y && this->m_z < prm_Vector.m_z);
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    bool       operator <= (const C_Vector3D& prm_Vector)
	{
		return (this->m_x <= prm_Vector.m_x && this->m_y <= prm_Vector.m_y && this->m_z <= prm_Vector.m_z);
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    bool       operator > (const C_Vector3D& prm_Vector)
	{
		return (this->m_x > prm_Vector.m_x && this->m_y > prm_Vector.m_y && this->m_z > prm_Vector.m_z);
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    bool       operator >= (const C_Vector3D& prm_Vector)
	{
		return (this->m_x >= prm_Vector.m_x && this->m_y >= prm_Vector.m_y && this->m_z >= prm_Vector.m_z);
	}
  
	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator + (const C_Vector3D& prm_Vector) const
	{
		C_Vector3D result(this->m_x + prm_Vector.m_x, this->m_y + prm_Vector.m_y, this->m_z + prm_Vector.m_z);
		return result;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator += (const C_Vector3D& prm_Vector) const
	{
		return *this + prm_Vector;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator - (const C_Vector3D& prm_Vector) const
	{
		C_Vector3D result(this->m_x - prm_Vector.m_x, this->m_y - prm_Vector.m_y, this->m_z - prm_Vector.m_z);
		return result;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator -= (const C_Vector3D& prm_Vector) const
	{
		return *this - prm_Vector;
	}
  
	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator * (const float prm_Scalar) const
	{
		C_Vector3D result(this->m_x * prm_Scalar, this->m_y * prm_Scalar, this->m_z * prm_Scalar);
		return result;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator *= (const float prm_Scalar) const
	{
		return *this * prm_Scalar;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
    C_Vector3D operator / (const float prm_Scalar) const
	{
		C_Vector3D result(this->m_x / prm_Scalar, this->m_y / prm_Scalar, this->m_z / prm_Scalar);
		return result;
	}

	/*!
	 * @brief Equal operator checks if the elements of both vectors are the same.
	*/
	C_Vector3D operator /= (const float prm_Scalar) const
	{
		return *this / prm_Scalar;
	}
  
	/*!
	* @brief Obtains the length of the vector.
	* @retun Length of the vector
	*/
    float      Length() const;
    
	/*!
	* @brief Obtains the squared length of the vector.
	* @return The length of the vector squared.
	*/
	float      SqrLength() const;
    
	/*!
	 * @brief Calculates the scalar/dot product between to vectors
	 * @param prm_Vector Vector used for the method.
	 * @return Returns the proyection of one vector over the other
	*/
	float      Dot(const C_Vector3D& prm_Vector) const;
    
	/*!
	* @brief Obtains the angle in which the vector is pointig towards
	* @return The angle of the vector expressed in degrees.
	*/
	float      Angle(const C_Vector3D& prm_Vector) const;
  
	/*!
	* @brief Equal operator checks if the elements of both vectors are the same.
	*/
	void       Normalize();

	/*!
	* @brief Equal operator checks if the elements of both vectors are the same.
	*/
	C_Vector3D Cross(const C_Vector3D& prm_Vector);
    
	/*!
	* @brief Equal operator checks if the elements of both vectors are the same.
	*/
	C_Vector3D UnitCross(const C_Vector3D& prm_Vector);

	/*!
	*/
	void NullVector();

	/*!
	*/
	void UnitVector();
  };
}