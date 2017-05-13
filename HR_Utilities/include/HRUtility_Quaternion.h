#pragma once

#include "HRUtility_Prerequisites.h"

/*!************************************************************************************************************************************************************************
@file		HRUtility_Quaternion.h

This file contains the declaration of the class Quaternion.
This object is used to create gimbal-lock free rotation matrices.
The functions implemented inside this class are described below:
- Normalization of a quaternion. (Unit quaternion)
- Magnitude/Length of a vector.
- 

@date		18-02-2017
@author		Manuel Santos Ramón (ManuSanRam)
@copyright	Infernal Coders S.A
***************************************************************************************************************************************************************************/

namespace HR_SDK
{
  /*!***********************************************************************************************************************************************************************
   * @brief Declares the quaternion object, used for 3D rotations																										   *
  *************************************************************************************************************************************************************************/
  class HR_UTILITY_EXPORT C_Quaternion
  {
  public:
	/*!*********************************************************************************************************************************************************************
	 * @brief Constructor (Default)																																		   *
	 * This constructor initiates all elements excepet the 'W' element to zero.																							   *
	***********************************************************************************************************************************************************************/
	C_Quaternion() : m_w(1.0f), m_x(0.0f), m_y(0.0f), m_z(0.0f)
	{
	
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Constructor (Parameter)																																	   *
	 * @param prm_x 'X' axis element																																	   *
	 * @param prm_y 'Y' axis element																																	   *
	 * @param prm_z 'Z' axis element																																	   *
	 * @param prm_w 'W' elementt																																		   *
	***********************************************************************************************************************************************************************/
	C_Quaternion(float prm_w, float prm_x, float prm_y, float prm_z) : m_w(prm_w), m_x(prm_x), m_y(prm_y), m_z(prm_z)
	{

	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Constructor (Copy)																																		   *
	 * @param prm_Copy Quaternion from which to copy data																												   *
	***********************************************************************************************************************************************************************/
	C_Quaternion(const C_Quaternion& prm_Copy)
	{
		this->m_w = prm_Copy.m_w;
		this->m_x = prm_Copy.m_x;
		this->m_y = prm_Copy.m_y;
		this->m_z = prm_Copy.m_z;
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Destructor																																				   *
	***********************************************************************************************************************************************************************/
	~C_Quaternion()
	{
	
	}

	/*!********************************************************************************************************************************************************************
	 * @brief Assignment operator
	 * @param rm Quat
	***********************************************************************************************************************************************************************/
	C_Quaternion operator = (const C_Quaternion& prm_Quat)
	{
		//! Copy the memory of the parameter into this object
		memcpy(this, &prm_Quat, sizeof(C_Quaternion));
		//! Return the current instance, which is carrying the current data
		return *this;
	}

	/*!
	*/
	C_Quaternion operator * (const C_Quaternion& prm_Quat)
	{
		return C_Quaternion
		(
			this->m_w * prm_Quat.m_w - this->m_w * prm_Quat.m_w - this->m_w * prm_Quat.m_w - this->m_w * prm_Quat.m_w,
			this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w - this->m_w * prm_Quat.m_w,
			this->m_w * prm_Quat.m_w - this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w,
			this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w + this->m_w * prm_Quat.m_w
		);
	}

	/*!********************************************************************************************************************************************************************
	* @brief
	* @param
	* @return 
	***********************************************************************************************************************************************************************/
	C_Quaternion& operator *= (const C_Quaternion& prm_Quat)
	{
		return (*this * prm_Quat);
	}

	/*!********************************************************************************************************************************************************************
	* @brief Multiply operator
	* @param prm_Scalar Scalar that will multiply each of the quaternions elements
	* @return Returns a quaternion with each of its elements multiplied by the scalar
	***********************************************************************************************************************************************************************/
	C_Quaternion operator * (float prm_Scalar)
	{
		return C_Quaternion
		(
			this->m_w / prm_Scalar,
			this->m_x / prm_Scalar, 
			this->m_y / prm_Scalar, 
			this->m_z / prm_Scalar
		);
	}

	/*!********************************************************************************************************************************************************************
	* @brief Multiply operator
	* @param prm_Scalar Scalar that will multiply each of the quaternions elements
	* @return Returns a quaternion with each of its elements multiplied by the scalar
	************************************************************************************************************************************************************************/
	C_Quaternion& operator *= (float prm_Scalar)
	{
		return (*this * prm_Scalar);
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Calculate the magnitude of the quaternion																													   *
	***********************************************************************************************************************************************************************/
	float Magnitude();

	/*!*********************************************************************************************************************************************************************
	 * @brief Normalize a quaternion																																	   *
	***********************************************************************************************************************************************************************/
	void Normalize();

  private:
	/*!
	 * @brief Element 'X' of the quaternion
	*/
    float m_w;
    /*!
	 * @brief Element 'Y' of the quaternion
	*/
	float m_x;
    /*!
	 * @brief Element 'Z' of the quaternion
	*/
	float m_y;
    /*!
	 * @brief Element 'W' of the quaternion
	*/
	float m_z;
  };
}