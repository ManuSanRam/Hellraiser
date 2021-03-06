#pragma once

#include "HRUtility_Prerequisites.h"

/*!******************************************************************************************************************************************************************************
	
	@file		HRUtility_Quaternion.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	This file contains the declaration of the class Quaternion.
	This object is used to create gimbal-lock free rotation matrices.
	The functions implemented inside this class are described below:
	- Normalization of a quaternion. (Unit quaternion)
	- Magnitude/Length of a vector.
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		18-02-2017
	@author		Manuel Santos Ram�n (ManuSanRam)
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/



namespace HR_SDK
{
	/*!**************************************************************************************************************************************************************************

		@class C_Quaternion

		@brief Quaternion object, used to perform rotations in 3D space

	****************************************************************************************************************************************************************************/
	class HR_UTILITY_EXPORT C_Quaternion
	{
	public:
		/*!**********************************************************************************************************************************************************************

			@brief Constructor [Default]

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A quaternion object with all elements except the 'W' element equal to zero.

		************************************************************************************************************************************************************************/
		C_Quaternion() : m_w(1.0f), m_x(0.0f), m_y(0.0f), m_z(0.0f)
		{

		}

		/*!**********************************************************************************************************************************************************************

			@brief Constructor [Parameter]

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _w 'W' axis element
			@param _x 'X' axis element
			@param _y 'Y' axis element
			@param _z 'Z' element

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A quaternion object, containing the values passed on each respective element

		*************************************************************************************************************************************************************************/
		C_Quaternion(float _w, float _x, float _y, float _z) : m_w(_w), m_x(_x), m_y(_y), m_z(_z)
		{

		}

		/*!**********************************************************************************************************************************************************************

			@brief Constructor [Copy]

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param prm_Copy Quaternion from which to copy data

		************************************************************************************************************************************************************************/
		C_Quaternion
		(
			const C_Quaternion& _Copy
		)
		{
			this->m_w = _Copy.m_w;
			this->m_x = _Copy.m_x;
			this->m_y = _Copy.m_y;
			this->m_z = _Copy.m_z;
		}

		/*!*********************************************************************************************************************************************************************

			@brief Destructor

		***********************************************************************************************************************************************************************/
		~C_Quaternion
		(

		)
		{

		}

		/*!**********************************************************************************************************************************************************************
			
			@brief Assignment operator
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _quaternion Quaternion to copy data to quaternion

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A quaternion with its data assigned the values of _quaternion

		************************************************************************************************************************************************************************/
		C_Quaternion operator = 
		(
			const C_Quaternion& _quaternion
		)
		{
			//! Copy the memory of the parameter into this object
			memcpy(this, &_quaternion, sizeof(C_Quaternion));
			//! Return the current instance, which is carrying the current data
			return *this;
		}

		/*!**********************************************************************************************************************************************************************

			@brief Multiplies a quaternion by another quaternion

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param[in] _Quat Quaternion reference used to perform the operation

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A quaternion, product of the multiplication between two quaternions

		************************************************************************************************************************************************************************/
		C_Quaternion operator * 
		(
			const C_Quaternion& _Quat
		)
		{
			return C_Quaternion
			(
				this->m_w * _Quat.m_w - this->m_x * _Quat.m_x - this->m_y * _Quat.m_y - this->m_z * _Quat.m_z,	//! 'W' element
				this->m_w * _Quat.m_w + this->m_w * _Quat.m_w + this->m_w * _Quat.m_w - this->m_w * _Quat.m_w,	//! 'X' element
				this->m_w * _Quat.m_w - this->m_w * _Quat.m_w + this->m_w * _Quat.m_w + this->m_w * _Quat.m_w,	//! 'Y' element
				this->m_w * _Quat.m_w + this->m_w * _Quat.m_w + this->m_w * _Quat.m_w + this->m_w * _Quat.m_w	//! 'Z' element
			);
		}

		/*!**********************************************************************************************************************************************************************
			
			@brief Multiplication of two quaternions and save result in one of them

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param _quaternion Quaternion to multiply by

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@return The multiplication of two quaternions

		************************************************************************************************************************************************************************/
		C_Quaternion& operator *= 
		(
			const C_Quaternion& _quaternion
		)
		{
			return (*this * _quaternion);
		}

		/*!**********************************************************************************************************************************************************************
			
			@brief Multiply a quaternion 
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param prm_Scalar Scalar that will multiply each of the quaternions elements
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@return Returns a quaternion with each of its elements multiplied by the scalar

		************************************************************************************************************************************************************************/
		C_Quaternion operator * 
		(
			float _scalar
		)
		{
			return C_Quaternion
			(
				this->m_w / _scalar,
				this->m_x / _scalar,
				this->m_y / _scalar,
				this->m_z / _scalar
			);
		}

		/*!**********************************************************************************************************************************************************************
			
			@brief Multiply and equal the result of a quaternion and a scalar

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param prm_Scalar Scalar that will multiply each of the quaternions elements

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@return Returns a quaternion with each of its elements multiplied by the scalar

		************************************************************************************************************************************************************************/
		C_Quaternion& operator *= 
		(
			float _scalar
		)
		{
			return (*this * _scalar);
		}

		/*!*********************************************************************************************************************************************************************

			@brief Calculate the magnitude of the quaternion																													   

		***********************************************************************************************************************************************************************/
		float Magnitude();

		/*!*********************************************************************************************************************************************************************
			
			@brief Normalize a quaternion

		***********************************************************************************************************************************************************************/
		void Normalize();


		/*!**********************************************************************************************************************************************************************

			@brief Element 'W' of the quaternion

		************************************************************************************************************************************************************************/
		float m_w;

		/*!**********************************************************************************************************************************************************************

			@brief Element 'X' of the quaternion

		************************************************************************************************************************************************************************/
		float m_x;

		/*!**********************************************************************************************************************************************************************

			@brief Element 'Y' of the quaternion

		************************************************************************************************************************************************************************/
		float m_y;

		/*!**********************************************************************************************************************************************************************

			@brief Element 'Z' of the quaternion

		************************************************************************************************************************************************************************/
		float m_z;
	};
}