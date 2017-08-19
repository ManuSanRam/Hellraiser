#include "HRUtility_Matrix4.h"
#include "HRUtility_PlatformMath.h"

/*!******************************************************************************************************************************************************************************

	@file		HRUtility_Matrix4.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of 4x4 matrix class and its methods.
	Methods of the matrix are denoted below:

	- Zero matrix:
	- Identity matrix:
	- Transpose:
	- Determinant:
	- Adjoint:
	- Inverse:
	- Rotations on X, Y and Z axis:
	- Roll, Pitch and Yaw rotation:
	- Look At.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		07-02-2017
	@author		Manuel Aldair Santos Ramón [ManuSanRam]
	@copyright	Infernal Coders S.A.

********************************************************************************************************************************************************************************/

namespace HR_SDK
{
	/*!**********************************************************************************************************************************************************************

		@brief Sets all matrix elements to 0

	************************************************************************************************************************************************************************/
	void		C_Matrix4::ZeroMatrix()
	{
		this->m_Element[0][0] = 0.0f;
		this->m_Element[0][1] = 0.0f;
		this->m_Element[0][2] = 0.0f;
		this->m_Element[0][3] = 0.0f;

		this->m_Element[1][0] = 0.0f;
		this->m_Element[1][1] = 0.0f;
		this->m_Element[1][2] = 0.0f;
		this->m_Element[1][3] = 0.0f;

		this->m_Element[2][0] = 0.0f;
		this->m_Element[2][1] = 0.0f;
		this->m_Element[2][2] = 0.0f;
		this->m_Element[2][3] = 0.0f;

		this->m_Element[3][0] = 0.0f;
		this->m_Element[3][1] = 0.0f;
		this->m_Element[3][2] = 0.0f;
		this->m_Element[3][3] = 0.0f;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Sets matrix as identity (main diagonal elements set to 1, rest set to 0)

	************************************************************************************************************************************************************************/
	void		C_Matrix4::Identity()
	{
		//! Transform matrix to zero matrix, emptying its content
		ZeroMatrix();

		//! Set necessary elements to 
		this->m_Element[0][0] = 1.0f;
		this->m_Element[1][1] = 1.0f;
		this->m_Element[2][2] = 1.0f;
		this->m_Element[3][3] = 1.0f;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Transposes matrix, changing order of the matrix's elements

	************************************************************************************************************************************************************************/
	void		C_Matrix4::Transpose()
	{
		C_Matrix4 temp(*this);

		this->m_Element[0][0] = temp.m_Element[0][0];
		this->m_Element[0][1] = temp.m_Element[1][0];
		this->m_Element[0][2] = temp.m_Element[2][0];
		this->m_Element[0][3] = temp.m_Element[3][0];

		this->m_Element[1][0] = temp.m_Element[0][1];
		this->m_Element[1][1] = temp.m_Element[1][1];
		this->m_Element[1][2] = temp.m_Element[2][1];
		this->m_Element[1][3] = temp.m_Element[3][1];

		this->m_Element[2][0] = temp.m_Element[0][2];
		this->m_Element[2][1] = temp.m_Element[1][2];
		this->m_Element[2][2] = temp.m_Element[2][2];
		this->m_Element[2][3] = temp.m_Element[3][2];

		this->m_Element[3][0] = temp.m_Element[0][3];
		this->m_Element[3][1] = temp.m_Element[1][3];
		this->m_Element[3][2] = temp.m_Element[2][3];
		this->m_Element[3][3] = temp.m_Element[3][3];
	}



	/*!**********************************************************************************************************************************************************************

		@brief Calculates the matrix's determinant

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A number representing the determinant of a matrix

	************************************************************************************************************************************************************************/
	float		C_Matrix4::Determinant()
	{
		float _AM, _BM, _CM, _DM, _am, _bm, _cm, _dm;

		//! Positive part
		_AM = 
			(m_Element[0][0] * m_Element[1][1] * m_Element[2][2] * m_Element[3][3]) + 
			(m_Element[0][0] * m_Element[1][2] * m_Element[2][3] * m_Element[3][1]) + 
			(m_Element[0][0] * m_Element[1][3] * m_Element[2][1] * m_Element[3][2]);

		_BM =
			(m_Element[0][1] * m_Element[1][0] * m_Element[2][2] * m_Element[3][3]) +
			(m_Element[0][1] * m_Element[1][2] * m_Element[2][3] * m_Element[3][0]) +
			(m_Element[0][1] * m_Element[1][3] * m_Element[2][0] * m_Element[3][2]);

		_CM =
			(m_Element[0][2] * m_Element[1][0] * m_Element[2][1] * m_Element[3][3]) +
			(m_Element[0][2] * m_Element[1][1] * m_Element[2][3] * m_Element[3][0]) +
			(m_Element[0][2] * m_Element[1][3] * m_Element[2][0] * m_Element[3][1]);

		_DM =
			(m_Element[0][3] * m_Element[1][0] * m_Element[2][1] * m_Element[3][2]) +
			(m_Element[0][3] * m_Element[1][1] * m_Element[2][2] * m_Element[3][0]) +
			(m_Element[0][3] * m_Element[1][2] * m_Element[2][0] * m_Element[3][1]);

		//! Negative part
		_am = 
			(m_Element[0][0] * m_Element[1][1] * m_Element[2][3] * m_Element[3][2]) -
			(m_Element[0][0] * m_Element[1][2] * m_Element[2][1] * m_Element[3][3]) -
			(m_Element[0][0] * m_Element[1][3] * m_Element[2][2] * m_Element[3][1]);

		_bm = 
			(m_Element[0][1] * m_Element[1][0] * m_Element[2][3] * m_Element[3][2]) -
			(m_Element[0][1] * m_Element[1][2] * m_Element[2][0] * m_Element[3][3]) -
			(m_Element[0][1] * m_Element[1][3] * m_Element[2][2] * m_Element[3][0]);

		_cm = 
			(m_Element[0][2] * m_Element[1][0] * m_Element[2][3] * m_Element[3][1]) -
			(m_Element[0][2] * m_Element[1][1] * m_Element[2][0] * m_Element[3][1]) -
			(m_Element[0][2] * m_Element[1][3] * m_Element[2][1] * m_Element[3][0]);

		_dm = 
			(m_Element[0][3] * m_Element[1][0] * m_Element[2][2] * m_Element[3][1]) -
			(m_Element[0][3] * m_Element[1][1] * m_Element[2][0] * m_Element[3][2]) -
			(m_Element[0][3] * m_Element[1][2] * m_Element[2][1] * m_Element[3][0]);

		return _AM + _BM + _CM + _DM - _am - _bm - _cm - _dm;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Calculates the adjoint matrix

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix representing the adjoint matrix of another matrix

	************************************************************************************************************************************************************************/
	C_Matrix4	C_Matrix4::Adjoint()
	{
		float
			_00, _01, _02, _03,
			_10, _11, _12, _13,
			_20, _21, _22, _23,
			_30, _31, _32, _33;

		//! First row
		_00 = (m_Element[1][1] * m_Element[2][2] * m_Element[3][3]) + (m_Element[1][2] * m_Element[2][3] * m_Element[3][1]) + (m_Element[1][3] * m_Element[2][1] * m_Element[3][2])
			- (m_Element[1][1] * m_Element[2][3] * m_Element[3][2]) - (m_Element[1][2] * m_Element[2][1] * m_Element[3][3]) - (m_Element[1][3] * m_Element[2][2] * m_Element[3][1]);

		_01 = (m_Element[1][0] * m_Element[2][2] * m_Element[3][3]) + (m_Element[1][2] * m_Element[2][3] * m_Element[3][0]) + (m_Element[1][3] * m_Element[2][0] * m_Element[3][2])
			- (m_Element[1][0] * m_Element[2][3] * m_Element[3][2]) - (m_Element[1][2] * m_Element[2][0] * m_Element[3][3]) - (m_Element[1][3] * m_Element[2][2] * m_Element[3][0]);

		_02 = (m_Element[1][0] * m_Element[2][1] * m_Element[3][3]) + (m_Element[1][1] * m_Element[2][3] * m_Element[3][0]) + (m_Element[1][3] * m_Element[2][0] * m_Element[3][1])
			- (m_Element[1][0] * m_Element[2][3] * m_Element[3][1]) - (m_Element[1][1] * m_Element[2][0] * m_Element[3][3]) - (m_Element[1][3] * m_Element[2][1] * m_Element[3][0]);

		_03 = (m_Element[1][0] * m_Element[2][1] * m_Element[3][2]) + (m_Element[1][1] * m_Element[2][2] * m_Element[3][0]) + (m_Element[1][2] * m_Element[2][0] * m_Element[3][1])
			- (m_Element[1][0] * m_Element[2][2] * m_Element[3][1]) - (m_Element[1][1] * m_Element[2][0] * m_Element[3][2]) - (m_Element[1][2] * m_Element[2][1] * m_Element[3][0]);
		//! Done!


		//! Second row
		_10 = (m_Element[0][1] * m_Element[2][2] * m_Element[3][3]) + (m_Element[0][2] * m_Element[2][3] * m_Element[3][1]) + (m_Element[0][3] * m_Element[2][1] * m_Element[3][2])
			- (m_Element[0][1] * m_Element[2][3] * m_Element[3][2]) - (m_Element[0][2] * m_Element[2][1] * m_Element[3][3]) - (m_Element[0][3] * m_Element[2][2] * m_Element[3][1]);

		_11 = (m_Element[0][0] * m_Element[2][2] * m_Element[3][3]) + (m_Element[0][2] * m_Element[2][3] * m_Element[3][0]) + (m_Element[0][3] * m_Element[2][0] * m_Element[3][2])
			- (m_Element[0][0] * m_Element[2][3] * m_Element[3][2]) - (m_Element[0][2] * m_Element[2][0] * m_Element[3][3]) - (m_Element[0][3] * m_Element[2][2] * m_Element[3][0]);

		_12 = (m_Element[0][0] * m_Element[2][1] * m_Element[3][3]) + (m_Element[0][1] * m_Element[2][3] * m_Element[3][0]) + (m_Element[0][3] * m_Element[2][0] * m_Element[3][1])
			- (m_Element[0][0] * m_Element[2][3] * m_Element[3][1]) - (m_Element[0][1] * m_Element[2][0] * m_Element[3][3]) - (m_Element[0][3] * m_Element[2][1] * m_Element[3][0]);

		_13 = (m_Element[0][0] * m_Element[2][1] * m_Element[3][2]) + (m_Element[0][1] * m_Element[2][2] * m_Element[3][0]) + (m_Element[0][2] * m_Element[2][0] * m_Element[3][1])
			- (m_Element[0][0] * m_Element[2][2] * m_Element[3][1]) - (m_Element[0][1] * m_Element[2][0] * m_Element[3][2]) - (m_Element[0][2] * m_Element[2][1] * m_Element[3][0]);
		//! Done!


		//! Third row
		_20 = (m_Element[0][1] * m_Element[1][2] * m_Element[3][3]) + (m_Element[0][2] * m_Element[1][3] * m_Element[3][1]) + (m_Element[0][3] * m_Element[1][1] * m_Element[3][2])
			- (m_Element[0][1] * m_Element[1][3] * m_Element[3][2]) - (m_Element[0][2] * m_Element[1][1] * m_Element[3][3]) - (m_Element[0][3] * m_Element[1][2] * m_Element[3][1]);

		_21 = (m_Element[0][0] * m_Element[1][2] * m_Element[3][3]) + (m_Element[0][2] * m_Element[1][3] * m_Element[3][0]) + (m_Element[0][3] * m_Element[1][0] * m_Element[3][2])
			- (m_Element[0][0] * m_Element[1][3] * m_Element[3][2]) - (m_Element[0][2] * m_Element[1][0] * m_Element[3][3]) - (m_Element[0][3] * m_Element[1][2] * m_Element[3][0]);

		_22 = (m_Element[0][0] * m_Element[1][1] * m_Element[3][3]) + (m_Element[0][1] * m_Element[1][3] * m_Element[3][0]) + (m_Element[0][3] * m_Element[1][0] * m_Element[3][1])
			- (m_Element[0][0] * m_Element[1][3] * m_Element[3][1]) - (m_Element[0][1] * m_Element[1][0] * m_Element[3][3]) - (m_Element[0][3] * m_Element[1][1] * m_Element[3][0]);

		_23 = (m_Element[0][0] * m_Element[1][1] * m_Element[3][2]) + (m_Element[0][1] * m_Element[1][2] * m_Element[3][0]) + (m_Element[0][2] * m_Element[1][0] * m_Element[3][1])
			- (m_Element[0][0] * m_Element[1][2] * m_Element[3][1]) - (m_Element[0][1] * m_Element[1][0] * m_Element[3][2]) - (m_Element[0][2] * m_Element[1][1] * m_Element[3][0]);
		//! Done!


		//! Fourth row
		_30 = (m_Element[0][1] * m_Element[1][2] * m_Element[2][3]) + (m_Element[0][2] * m_Element[1][3] * m_Element[2][1]) + (m_Element[0][3] * m_Element[1][1] * m_Element[2][2])
			- (m_Element[0][1] * m_Element[1][3] * m_Element[2][2]) - (m_Element[0][2] * m_Element[1][1] * m_Element[2][3]) - (m_Element[0][3] * m_Element[1][2] * m_Element[2][1]);

		_31 = (m_Element[0][0] * m_Element[1][2] * m_Element[2][3]) + (m_Element[0][2] * m_Element[1][3] * m_Element[2][0]) + (m_Element[0][3] * m_Element[1][0] * m_Element[2][2])
			- (m_Element[0][0] * m_Element[1][3] * m_Element[2][2]) - (m_Element[0][2] * m_Element[1][0] * m_Element[2][3]) - (m_Element[0][3] * m_Element[1][2] * m_Element[2][0]);

		_32 = (m_Element[0][0] * m_Element[1][1] * m_Element[2][3]) + (m_Element[0][1] * m_Element[1][3] * m_Element[2][0]) + (m_Element[0][3] * m_Element[1][0] * m_Element[2][1])
			- (m_Element[0][0] * m_Element[1][3] * m_Element[2][1]) - (m_Element[0][1] * m_Element[1][0] * m_Element[2][3]) - (m_Element[0][3] * m_Element[1][1] * m_Element[2][0]);

		_33 = (m_Element[0][0] * m_Element[1][1] * m_Element[2][2]) + (m_Element[0][1] * m_Element[1][2] * m_Element[2][0]) + (m_Element[0][2] * m_Element[1][0] * m_Element[2][1])
			- (m_Element[0][0] * m_Element[1][2] * m_Element[2][1]) - (m_Element[0][1] * m_Element[1][0] * m_Element[2][2]) - (m_Element[0][2] * m_Element[1][1] * m_Element[2][0]);
		//! Done!

		C_Matrix4 Adjoint
		(
			_00, _01, _02, _03,
			_10, _11, _12, _13,
			_20, _21, _22, _23,
			_30, _31, _32, _33
		);

		Adjoint.Transpose();

		return Adjoint;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Calculates inverse matrix of this matrix

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix, representing the inverse matrix of another matrix

	************************************************************************************************************************************************************************/
	C_Matrix4	C_Matrix4::Inverse()
	{
		return (this->Adjoint() * (1.0f / this->Determinant()));
	}



	/*!**********************************************************************************************************************************************************************

		@brief Create rotation matrix along X axis

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _Angle Angle to rotate given in radians
		@param _Id Boolean to check if matrix will be turned to identity matrix or left with its original info

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix to rotate along the 'X' axis

	************************************************************************************************************************************************************************/
	C_Matrix4&	C_Matrix4::RotateX(float prm_Angle, bool prm_Id)
	{
		if (prm_Id)
		{
			Identity();
		}

		//! Modify elements t rotate along Z axis
		C_Quaternion _result(1.0f, 0.0f, 0.0f, 0.0f), _localRot;

		_localRot.m_w = C_PlatformMath::Cosine(prm_Angle / 2.0f);
		_localRot.m_x = 1.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);
		_localRot.m_y = 0.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);
		_localRot.m_z = 0.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);

		_result = _localRot * _result;

		this->m_Element[0][0] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_y, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_z, 2.0f));
		this->m_Element[0][1] = 2.0f * (_result.m_x * _result.m_y) - 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[0][2] = 2.0f * (_result.m_x * _result.m_z) + 2.0f * (_result.m_w * _result.m_y);
		this->m_Element[0][3] = 0.0f;

		this->m_Element[1][0] = 2.0f * (_result.m_x * _result.m_y) + 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[1][1] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_x, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_z, 2.0f));
		this->m_Element[1][2] = 2.0f * (_result.m_y * _result.m_z) + 2.0f * (_result.m_w * _result.m_x);
		this->m_Element[1][3] = 0.0f;

		this->m_Element[2][0] = 2.0f * (_result.m_x * _result.m_z) - 2.0f * (_result.m_w * _result.m_y);
		this->m_Element[2][1] = 2.0f * (_result.m_x * _result.m_y) - 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[2][2] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_x, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_y, 2.0f));
		this->m_Element[2][3] = 0.0f;

		this->m_Element[3][0] = 0.0f;
		this->m_Element[3][1] = 0.0f;
		this->m_Element[3][2] = 0.0f;
		this->m_Element[3][3] = 1.0f;

		return *this;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Create rotation matrix along Y axis

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _Angle Angle to rotate given in radians
		@param _Id Boolean to check if matrix will be turned to identity matrix or left with its original info

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix to rotate along the 'Y' axis

	************************************************************************************************************************************************************************/
	C_Matrix4&	C_Matrix4::RotateY(float prm_Angle, bool prm_Id)
	{
		if (prm_Id)
		{
			Identity();
		}

		//! Modify elements t rotate along Z axis
		C_Quaternion _result(1.0f, 0.0f, 0.0f, 0.0f), _localRot;

		_localRot.m_w = C_PlatformMath::Cosine(prm_Angle / 2.0f);
		_localRot.m_x = 0.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);
		_localRot.m_y = 1.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);
		_localRot.m_z = 0.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);

		_result = _localRot * _result;

		this->m_Element[0][0] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_y, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_z, 2.0f));
		this->m_Element[0][1] = 2.0f * (_result.m_x * _result.m_y) - 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[0][2] = 2.0f * (_result.m_x * _result.m_z) + 2.0f * (_result.m_w * _result.m_y);
		this->m_Element[0][3] = 0.0f;

		this->m_Element[1][0] = 2.0f * (_result.m_x * _result.m_y) + 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[1][1] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_x, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_z, 2.0f));
		this->m_Element[1][2] = 2.0f * (_result.m_y * _result.m_z) + 2.0f * (_result.m_w * _result.m_x);
		this->m_Element[1][3] = 0.0f;

		this->m_Element[2][0] = 2.0f * (_result.m_x * _result.m_z) - 2.0f * (_result.m_w * _result.m_y);
		this->m_Element[2][1] = 2.0f * (_result.m_x * _result.m_y) - 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[2][2] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_x, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_y, 2.0f));
		this->m_Element[2][3] = 0.0f;

		this->m_Element[3][0] = 0.0f;
		this->m_Element[3][1] = 0.0f;
		this->m_Element[3][2] = 0.0f;
		this->m_Element[3][3] = 1.0f;

		return *this;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Create rotation matrix along Z axis

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _Angle Angle to rotate given in radians
		@param _Id Boolean to check if matrix will be turned to identity matrix or left with its original info

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix to rotate along the 'Z' axis

	************************************************************************************************************************************************************************/
	C_Matrix4&	C_Matrix4::RotateZ(float prm_Angle, bool prm_Id)
	{
		//! If prm_Id is true...
		if (prm_Id)
		{
			//! Turn the matrix into identity matrix
			Identity();
		}

		//! Modify elements t rotate along Z axis
		C_Quaternion _result(1.0f, 0.0f, 0.0f, 0.0f), _localRot;

		_localRot.m_w = C_PlatformMath::Cosine(prm_Angle / 2.0f);
		_localRot.m_x = 0.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);
		_localRot.m_y = 0.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);
		_localRot.m_z = 1.0f * C_PlatformMath::Sine(prm_Angle / 2.0f);

		_result = _localRot * _result;

		this->m_Element[0][0] =  1.0f - (2.0f * C_PlatformMath::Power(_result.m_y, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_z, 2.0f));
		this->m_Element[0][1] = 2.0f * (_result.m_x * _result.m_y) - 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[0][2] = 2.0f * (_result.m_x * _result.m_z) + 2.0f * (_result.m_w * _result.m_y);
		this->m_Element[0][3] = 0.0f;

		this->m_Element[1][0] = 2.0f * (_result.m_x * _result.m_y) + 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[1][1] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_x, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_z, 2.0f));
		this->m_Element[1][2] = 2.0f * (_result.m_y * _result.m_z) + 2.0f * (_result.m_w * _result.m_x);
		this->m_Element[1][3] = 0.0f;

		this->m_Element[2][0] = 2.0f * (_result.m_x * _result.m_z) - 2.0f * (_result.m_w * _result.m_y);
		this->m_Element[2][1] = 2.0f * (_result.m_x * _result.m_y) - 2.0f * (_result.m_w * _result.m_z);
		this->m_Element[2][2] = 1.0f - (2.0f * C_PlatformMath::Power(_result.m_x, 2.0f)) - (2.0f * C_PlatformMath::Power(_result.m_y, 2.0f));
		this->m_Element[2][3] = 0.0f;

		this->m_Element[3][0] = 0.0f;
		this->m_Element[3][1] = 0.0f;
		this->m_Element[3][2] = 0.0f;
		this->m_Element[3][3] = 1.0f;

		return *this;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Calculates a scaling matrix with given X, Y and Z scaling factors.
		W factor is left as 1

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _SX Scaling factor on X axis
		@param _SY Scaling factor on Y axis
		@param _SZ Scaling factor on Z axis

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix to scale something

	************************************************************************************************************************************************************************/
	C_Matrix4&	C_Matrix4::Scale(bool _id, float prm_SX, float prm_SY, float prm_SZ)
	{
		//! If prm_Id is true...
		if (_id)
		{
			Identity();
		}

		//! Modify elements t rotate along Z axis
		m_Element[0][0] *= prm_SX;
		m_Element[1][1] *= prm_SY;
		m_Element[2][2] *= prm_SZ;
		m_Element[3][3] = 1.0f;

		return *this;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Creates a translation matrix, to move an object in the world.

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _TX Translation factor in 'X' axis
		@param _TY Translation factor in 'Y' axis
		@param _TZ Translation factor in 'Z' axis

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix to translate an object in 3D space

	************************************************************************************************************************************************************************/
	C_Matrix4&	C_Matrix4::Translate(bool _id, float prm_TX, float prm_TY, float prm_TZ)
	{
		//! If prm_Id is true...
		if (_id)
		{
			Identity();
		}

		//! Modify elements t rotate along Z axis
			m_Element[3][0] = prm_TX;
			m_Element[3][1] = prm_TY;
			m_Element[3][2] = prm_TZ;
			m_Element[3][3] = 1.0f;

		return *this;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Create look-at matrix

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _position Position from where we're looking at
		@param _target Vector to indicate where is the point we're looking at
		@param _up Vector orthonormal to indicate the "UP" direction

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix containing rotation to look at a given target

	************************************************************************************************************************************************************************/
	C_Matrix4		C_Matrix4::LookAt
	(
		C_Vector3D prm_Position,
		C_Vector3D prm_Target,
		C_Vector3D prm_Up
	)
	{
		C_Vector3D XAxis, YAxis, ZAxis;

		ZAxis = prm_Target - prm_Position;
		XAxis = prm_Up;

		ZAxis.Normalize();
		XAxis.Normalize();

		XAxis = XAxis.Cross(ZAxis);
		XAxis.Normalize();

		YAxis = ZAxis.Cross(XAxis);
		YAxis.Normalize();

		float X, Y, Z;

		X = -XAxis.Dot(prm_Position);
		Y = -YAxis.Dot(prm_Position);
		Z = -ZAxis.Dot(prm_Position);

		*this = C_Matrix4
		(
			XAxis.m_x, YAxis.m_x, ZAxis.m_x, 0.0f,
			XAxis.m_y, YAxis.m_y, ZAxis.m_y, 0.0f,
			XAxis.m_z, YAxis.m_z, ZAxis.m_z, 0.0f,
			X, Y, Z, 1.0f
		);

		return *this;
	}



	/*!**********************************************************************************************************************************************************************

		@brief Calculate a projection matrix

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param _fovAngle
		@param _aspectRatio
		@param _nearZ
		@param _farZ

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@return A matrix used to

	************************************************************************************************************************************************************************/
	C_Matrix4		C_Matrix4::Projection
	(
		float prm_FOVAngle,
		float prm_Ratio,
		float prm_NearZ,
		float prm_FarZ
	)
	{
		float H, W;

		H = 1.0f / (C_PlatformMath::Tangent(prm_FOVAngle * (1.0f / 2.0f)));
		W = H / prm_Ratio;

		float _3rd, _4th;

		_3rd = (prm_FarZ + prm_NearZ) / (prm_NearZ - prm_FarZ);
		_4th = (2.0f * prm_NearZ * prm_FarZ) / (prm_NearZ - prm_FarZ);

		*this = C_Matrix4
		(
			W, 0.0f, 0.0f, 0.0f,
			0.0f, H, 0.0f, 0.0f,
			0.0f, 0.0f, _3rd, -1.0f,
			0.0f, 0.0f, _4th, 0.0f
		);

		return *this;
	}
}