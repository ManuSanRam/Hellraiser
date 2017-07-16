#pragma once

#include "HRUtility_Prerequisites.h"

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

	@date	    07-02-2017
	@author		Manuel Aldair Santos Ramón (ManuSanRam)
	@copyright	Infernal Coders S.A.

********************************************************************************************************************************************************************************/

#include "HRUtility_Vector3D.h"
#include "HRUtility_Vector4D.h"

namespace HR_SDK
{
	/*!**********************************************************************************************************************************************************************
	* Declares a 4x4 matrix object
	*************************************************************************************************************************************************************************/
	class HR_UTILITY_EXPORT C_Matrix4
	{
	public:
		/*!********************************************************************************************************************************************************************
		
			@brief Default constructor.
		
			@return An empty 4x4 matrix.
		
		***********************************************************************************************************************************************************************/
		C_Matrix4()
		{
			//! Create an empty matrix filled with zeroes.
			ZeroMatrix();
		}

		/*!********************************************************************************************************************************************************************
		
			@brief Constructor (Parameter) #1.
			Creates matrix setting it as IDENTITY or ZERO.
			Identity matrix contains:
		
			 A=	| 1, 0, 0, 0 |
				| 0, 1, 0, 0 |
				| 0, 0, 1, 0 |
				| 0, 0, 0, 1 |
		
			Zero matrix contains:
		
			A=	| 1, 0, 0, 0 |
				| 0, 1, 0, 0 |
				| 0, 0, 1, 0 |
				| 0, 0, 0, 1 |
		
			@param prm_Creator Defines if matrix is created as identity matrix or as a null matrix.
		
			@return A matrix constructed as identity or zero.
		
		***********************************************************************************************************************************************************************/
		C_Matrix4
		(
			bool prm_Creator	//! 
		)
		{
			//! Check which mode to create matrix
			if (prm_Creator)
			{
				//! Create matrix as identity matrix ()
				Identity();
			}

			else
			{
				//! Create matrix as zero matrix (all elements are 0)
				ZeroMatrix();
			}
		}

		/*!********************************************************************************************************************************************************************
		
			@brief Constructor (Parameter) #2.
			Creates matrix setting each element one by one.
		
			@param _00 Element 0,0
			@param _01 Element 0,1
			@param _02 Element 0,2
			@param _03 Element 0,3
			@param _10 Element 1,0
			@param _11 Element 1,1
			@param _12 Element 1,2
			@param _13 Element 1,3
			@param _20 Element 2,0
			@param _21 Element 2,1
			@param _22 Element 2,2
			@param _23 Element 2,3
			@param _30 Element 3,0
			@param _31 Element 3,1
			@param _32 Element 3,2
			@param _33 Element 3,3
		
			@return A matrix containing every element passed as parameter.
			The returned matrix will contain the elements in the following form:
		
			A=	| _00, _01, _02, _03 |
				| _10, _11, _12, _13 |
				| _20, _21, _22, _23 |
				| _30, _31, _32, _33 |
		
		***********************************************************************************************************************************************************************/
		C_Matrix4
		(
			float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33
		)
		{
			//! Set the matrix's elements
			m_Element[0][0] = _00; m_Element[0][1] = _01; m_Element[0][2] = _02; m_Element[0][3] = _03;	//! First row
			m_Element[1][0] = _10; m_Element[1][1] = _11; m_Element[1][2] = _12; m_Element[1][3] = _13;	//! Second row
			m_Element[2][0] = _20; m_Element[2][1] = _21; m_Element[2][2] = _22; m_Element[2][3] = _23;	//! Third row
			m_Element[3][0] = _30; m_Element[3][1] = _31; m_Element[3][2] = _32; m_Element[3][3] = _33;	//! Fourth row
		}

		/*!********************************************************************************************************************************************************************
		
			@brief Constructor (Copy).
			Creates a new matrix object from the data of another matrix object.
		
			@param CopyMatrix. Matrix from where data is copied.
		
			@return A matrix containing the elements from CopyMatrix in the respective positions.
			The returned matrix will contain the elements in the following form:
		
			A=	| CopyMatrix(0,0), CopyMatrix(0,1), CopyMatrix(0,2), CopyMatrix(0,3) |
				| CopyMatrix(1,0), CopyMatrix(1,1), CopyMatrix(1,2), CopyMatrix(1,3) |
				| CopyMatrix(2,0), CopyMatrix(2,1), CopyMatrix(2,2), CopyMatrix(2,3) |
				| CopyMatrix(3,0), CopyMatrix(3,1), CopyMatrix(3,2), CopyMatrix(3,3) |
		
		***********************************************************************************************************************************************************************/
		C_Matrix4(const C_Matrix4& CopyMatrix)
		{
			m_Element[0][0] = CopyMatrix.m_Element[0][0]; m_Element[0][1] = CopyMatrix.m_Element[0][1]; m_Element[0][2] = CopyMatrix.m_Element[0][2]; m_Element[0][3] = CopyMatrix.m_Element[0][3];	//! First row
			m_Element[1][0] = CopyMatrix.m_Element[1][0]; m_Element[1][1] = CopyMatrix.m_Element[1][1]; m_Element[1][2] = CopyMatrix.m_Element[1][2]; m_Element[1][3] = CopyMatrix.m_Element[1][3];	//! Second row
			m_Element[2][0] = CopyMatrix.m_Element[2][0]; m_Element[2][1] = CopyMatrix.m_Element[2][1]; m_Element[2][2] = CopyMatrix.m_Element[2][2]; m_Element[2][3] = CopyMatrix.m_Element[2][3];	//! Third row
			m_Element[3][0] = CopyMatrix.m_Element[3][0]; m_Element[3][1] = CopyMatrix.m_Element[3][1]; m_Element[3][2] = CopyMatrix.m_Element[3][2]; m_Element[3][3] = CopyMatrix.m_Element[3][3];	//! Fourth row
		}

		/*!********************************************************************************************************************************************************************
			@brief Destructor.
		***********************************************************************************************************************************************************************/
		~C_Matrix4()
		{

		}



		/*!********************************************************************************************************************************************************************
			@brief Assignment operator
		***********************************************************************************************************************************************************************/
		C_Matrix4	operator = (const C_Matrix4& Matrix)
		{
			//! Copy the memory of the parameter into this object
			memcpy(this, &Matrix, sizeof(C_Matrix4));
			//! Return the current instance, which is carrying the current data
			return *this;
		}

		/*!********************************************************************************************************************************************************************
		* @brief Equality operator
		* @param Matrix Matrix to compare object with
		***********************************/
		bool		operator == (const C_Matrix4& Matrix)
		{
			//! Iterate through matrix elements
			for (uint32 i = 0; i < 4; ++i)
			{
				for (uint32 j = 0; j < 4; ++j)
				{
					//! Compare if elements at same position are equal
					if (m_Element[i][j] != Matrix.m_Element[i][j])
					{
						//! If said elements are not equal, stop iteration, matrices are not equal
						return false;
					}
				}
			}
			//! If after the end of iteration all elements are equal, matrices are equal
			return true;
		}

		/*!
		* @brief Inequal operator
		* @param Matrix  Matrix to compare object with
		*/
		bool		operator != (const C_Matrix4& Matrix)
		{
			//! Iterate through matrix elements
			for (uint32 i = 0; i < 4; ++i)
			{
				for (uint32 j = 0; j < 4; ++j)
				{
					//! Check if elements at same position are equal
					if (m_Element[i][j] == Matrix.m_Element[i][j])
					{
						//! If said elements are not equal, stop iteration, matrices are not equal
						return false;
					}
				}
			}
			//! If after the end of iteration all elements are equal, matrices are equal
			return true;
		}

		/*!
		* @brief Addition operator
		* @param Matrix Matrix which elements will add with
		*/
		C_Matrix4	operator +  (const C_Matrix4& Matrix)
		{
			return C_Matrix4
			(
				this->m_Element[0][0] + Matrix.m_Element[0][0], this->m_Element[0][1] + Matrix.m_Element[0][1], this->m_Element[0][2] + Matrix.m_Element[0][2], this->m_Element[0][3] + Matrix.m_Element[0][3],
				this->m_Element[1][0] + Matrix.m_Element[1][0], this->m_Element[1][1] + Matrix.m_Element[1][1], this->m_Element[1][2] + Matrix.m_Element[1][2], this->m_Element[1][3] + Matrix.m_Element[1][3],
				this->m_Element[2][0] + Matrix.m_Element[2][0], this->m_Element[2][1] + Matrix.m_Element[2][1], this->m_Element[2][2] + Matrix.m_Element[2][2], this->m_Element[2][3] + Matrix.m_Element[2][3],
				this->m_Element[3][0] + Matrix.m_Element[3][0], this->m_Element[3][1] + Matrix.m_Element[3][1], this->m_Element[3][2] + Matrix.m_Element[3][2], this->m_Element[3][3] + Matrix.m_Element[3][3]
			);
		}

		/*!
		* @brief Add-assign operator
		* @param Matrix Matrix object from which elements will add with
		*/
		C_Matrix4	operator += (const C_Matrix4& Matrix)
		{
			return *this + Matrix;
		}

		/*!
		* @brief Substract operator
		* @param Matrix Matrix object from wich elemtns will substract with
		*/
		C_Matrix4	operator -  (const C_Matrix4& Matrix)
		{
			return C_Matrix4
			(
				this->m_Element[0][0] - Matrix.m_Element[0][0], this->m_Element[0][1] - Matrix.m_Element[0][1], this->m_Element[0][2] - Matrix.m_Element[0][2], this->m_Element[0][3] - Matrix.m_Element[0][3],
				this->m_Element[1][0] - Matrix.m_Element[1][0], this->m_Element[1][1] - Matrix.m_Element[1][1], this->m_Element[1][2] - Matrix.m_Element[1][2], this->m_Element[1][3] - Matrix.m_Element[1][3],
				this->m_Element[2][0] - Matrix.m_Element[2][0], this->m_Element[2][1] - Matrix.m_Element[2][1], this->m_Element[2][2] - Matrix.m_Element[2][2], this->m_Element[2][3] - Matrix.m_Element[2][3],
				this->m_Element[3][0] - Matrix.m_Element[3][0], this->m_Element[3][1] - Matrix.m_Element[3][1], this->m_Element[3][2] - Matrix.m_Element[3][2], this->m_Element[3][3] - Matrix.m_Element[3][3]
			);
		}

		/*!
		* @brief Substract-assign operator
		* @param Matrix Matrix object from which elements will be substracted
		*/
		C_Matrix4	operator -= (const C_Matrix4& Matrix)
		{
			return *this - Matrix;
		}

		/*!
		* @brief Multiplication operator
		* @param prm_Vector Vector from which elements will be operated
		*/
		C_Vector4D	operator * (const C_Vector4D prm_Vector) const
		{
			return C_Vector4D
			(
				prm_Vector.m_x * m_Element[0][0] + prm_Vector.m_y * m_Element[0][1] + prm_Vector.m_z * m_Element[0][2] + prm_Vector.m_w * m_Element[0][3],
				prm_Vector.m_x * m_Element[1][0] + prm_Vector.m_y * m_Element[1][1] + prm_Vector.m_z * m_Element[1][2] + prm_Vector.m_w * m_Element[1][3],
				prm_Vector.m_x * m_Element[2][0] + prm_Vector.m_y * m_Element[2][1] + prm_Vector.m_z * m_Element[2][2] + prm_Vector.m_w * m_Element[2][3],
				prm_Vector.m_x * m_Element[3][0] + prm_Vector.m_y * m_Element[3][1] + prm_Vector.m_z * m_Element[3][2] + prm_Vector.m_w * m_Element[3][3]
			);
		}

		/*!*********************************************************************************************************************************************************************
		* @brief Multiplication operator																																	   *
		* @param prm_Scalar Scalar to multiply matrix																														   *
		* @return Matrix multiplied by scalar																																   *
		***********************************************************************************************************************************************************************/
		C_Matrix4	operator * (float prm_Scalar) const
		{
			return C_Matrix4
			(
				m_Element[0][0] * prm_Scalar, m_Element[0][1] * prm_Scalar, m_Element[0][2] * prm_Scalar, m_Element[0][3] * prm_Scalar,
				m_Element[1][0] * prm_Scalar, m_Element[1][1] * prm_Scalar, m_Element[1][2] * prm_Scalar, m_Element[1][3] * prm_Scalar,
				m_Element[2][0] * prm_Scalar, m_Element[2][1] * prm_Scalar, m_Element[2][2] * prm_Scalar, m_Element[2][3] * prm_Scalar,
				m_Element[3][0] * prm_Scalar, m_Element[3][1] * prm_Scalar, m_Element[3][2] * prm_Scalar, m_Element[3][3] * prm_Scalar
			);
		}

		/*!
		*/
		C_Matrix4	operator *= (float prm_Scalar)
		{
			return *this * prm_Scalar;
		}

		/*!*********************************************************************************************************************************************************************
		* @brief Multiplication operator																																	   *
		* 																																									   *
		* Multipication of two matrices A and B of same dimensions MxN is																									   *
		* 																																									   ******************
		*		|																																											 |	*
		*		| (A00*B00 + A01*B10 + A02 * B20 + A03*B30), (A00*B01 + A01*B11 + A02 * B21 + A03*B31), (A00*B02 + A01*B12 + A02 * B22 + A03*B32), (A00*B03 + A01*B13 + A02 * B23 + A03*B33) |	*
		*		|																																											 |	*
		*		| (A10*B00 + A01*B10 + A12 * B20 + A13*B30), (A10*B01 + A11*B11 + A12 * B21 + A13*B31), (A10*B02 + A11*B12 + A12 * B22 + A13*B32), (A10*B03 + A11*B13 + A12 * B23 + A13*B33) |	*
		*		|																																											 |	*
		*		| (A20*B00 + A01*B10 + A22 * B20 + A23*B30), (A20*B01 + A21*B11 + A22 * B21 + A23*B31), (A20*B02 + A21*B12 + A22 * B22 + A23*B32), (A20*B03 + A21*B13 + A22 * B23 + A23*B33) |	*
		*		|																																											 |	*
		*		| (A30*B00 + A31*B10 + A32 * B20 + A33*B30), (A30*B01 + A31*B11 + A32 * B21 + A33*B31), (A30*B02 + A31*B12 + A32 * B22 + A33*B32), (A30*B03 + A31*B13 + A32 * B23 + A33*B33) |	*
		*		|																																											 |	*
		* 																																									   ******************
		* @param prm_Matrix Matrix to multiply with																														   *
		* @return Product matrix to 																																		   *
		***********************************************************************************************************************************************************************/
		C_Matrix4	operator * (C_Matrix4 prm_Matrix) const
		{
			//! 
			return C_Matrix4
			(
				//! 00 Element
				(m_Element[0][0] * prm_Matrix.m_Element[0][0]) + (m_Element[0][1] * prm_Matrix.m_Element[1][0]) + (m_Element[0][2] * prm_Matrix.m_Element[2][0]) + (m_Element[0][3] * prm_Matrix.m_Element[3][0]),
				//! 01 Element
				(m_Element[0][0] * prm_Matrix.m_Element[0][1]) + (m_Element[0][1] * prm_Matrix.m_Element[1][1]) + (m_Element[0][2] * prm_Matrix.m_Element[2][1]) + (m_Element[0][3] * prm_Matrix.m_Element[3][1]),
				//! 02 Element
				(m_Element[0][0] * prm_Matrix.m_Element[0][2]) + (m_Element[0][1] * prm_Matrix.m_Element[1][2]) + (m_Element[0][2] * prm_Matrix.m_Element[2][2]) + (m_Element[0][3] * prm_Matrix.m_Element[3][2]),
				//! 03 Element
				(m_Element[0][0] * prm_Matrix.m_Element[0][3]) + (m_Element[0][1] * prm_Matrix.m_Element[1][3]) + (m_Element[0][2] * prm_Matrix.m_Element[2][3]) + (m_Element[0][3] * prm_Matrix.m_Element[3][3]),

				//! 10 Element
				(m_Element[1][0] * prm_Matrix.m_Element[0][0]) + (m_Element[1][1] * prm_Matrix.m_Element[1][0]) + (m_Element[1][2] * prm_Matrix.m_Element[2][0]) + (m_Element[1][3] * prm_Matrix.m_Element[3][0]),
				//! 11 Element
				(m_Element[1][0] * prm_Matrix.m_Element[0][1]) + (m_Element[1][1] * prm_Matrix.m_Element[1][1]) + (m_Element[1][2] * prm_Matrix.m_Element[2][1]) + (m_Element[1][3] * prm_Matrix.m_Element[3][1]),
				//! 12 Element
				(m_Element[1][0] * prm_Matrix.m_Element[0][2]) + (m_Element[1][1] * prm_Matrix.m_Element[1][2]) + (m_Element[1][2] * prm_Matrix.m_Element[2][2]) + (m_Element[1][3] * prm_Matrix.m_Element[3][2]),
				//! 13 Element
				(m_Element[1][0] * prm_Matrix.m_Element[0][3]) + (m_Element[1][1] * prm_Matrix.m_Element[1][3]) + (m_Element[1][2] * prm_Matrix.m_Element[2][3]) + (m_Element[1][3] * prm_Matrix.m_Element[3][3]),

				//! 20 Element
				(m_Element[2][0] * prm_Matrix.m_Element[0][0]) + (m_Element[2][1] * prm_Matrix.m_Element[1][0]) + (m_Element[2][2] * prm_Matrix.m_Element[2][0]) + (m_Element[2][3] * prm_Matrix.m_Element[3][0]),
				//! 21 Element
				(m_Element[2][0] * prm_Matrix.m_Element[0][1]) + (m_Element[2][1] * prm_Matrix.m_Element[1][1]) + (m_Element[2][2] * prm_Matrix.m_Element[2][1]) + (m_Element[2][3] * prm_Matrix.m_Element[3][1]),
				//! 22 Element
				(m_Element[2][0] * prm_Matrix.m_Element[0][2]) + (m_Element[2][1] * prm_Matrix.m_Element[1][2]) + (m_Element[2][2] * prm_Matrix.m_Element[2][2]) + (m_Element[2][3] * prm_Matrix.m_Element[3][2]),
				//! 23 Element
				(m_Element[2][0] * prm_Matrix.m_Element[0][3]) + (m_Element[2][1] * prm_Matrix.m_Element[1][3]) + (m_Element[2][2] * prm_Matrix.m_Element[2][3]) + (m_Element[2][3] * prm_Matrix.m_Element[3][3]),

				//! 30 Element
				(m_Element[3][0] * prm_Matrix.m_Element[0][0]) + (m_Element[3][1] * prm_Matrix.m_Element[1][0]) + (m_Element[3][2] * prm_Matrix.m_Element[2][0]) + (m_Element[3][3] * prm_Matrix.m_Element[3][0]),
				//! 31 Element
				(m_Element[3][0] * prm_Matrix.m_Element[0][1]) + (m_Element[3][1] * prm_Matrix.m_Element[1][1]) + (m_Element[3][2] * prm_Matrix.m_Element[2][1]) + (m_Element[3][3] * prm_Matrix.m_Element[3][1]),
				//! 32 Element
				(m_Element[3][0] * prm_Matrix.m_Element[0][2]) + (m_Element[3][1] * prm_Matrix.m_Element[1][2]) + (m_Element[3][2] * prm_Matrix.m_Element[2][2]) + (m_Element[3][3] * prm_Matrix.m_Element[3][2]),
				//! 33 Element
				(m_Element[3][0] * prm_Matrix.m_Element[0][3]) + (m_Element[3][1] * prm_Matrix.m_Element[1][3]) + (m_Element[3][2] * prm_Matrix.m_Element[2][3]) + (m_Element[3][3] * prm_Matrix.m_Element[3][3])
			);
		}

		/*!**********************************************************************************************************************************************************************

			@brief Perform a MATRIX x VECTOR multiplication

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _vector Vector used to multiply

		************************************************************************************************************************************************************************/
		C_Vector4D	operator * (C_Vector4D _vector) const
		{
			//! Perform multiplication and create a new vector with results
			return C_Vector4D
			(
				(m_Element[0][0] * _vector.m_x) + (m_Element[0][1] * _vector.m_y) + (m_Element[0][2] * _vector.m_z) + (m_Element[0][3] * _vector.m_w),
				(m_Element[1][0] * _vector.m_x) + (m_Element[1][1] * _vector.m_y) + (m_Element[1][2] * _vector.m_z) + (m_Element[1][3] * _vector.m_w),
				(m_Element[2][0] * _vector.m_x) + (m_Element[2][1] * _vector.m_y) + (m_Element[2][2] * _vector.m_z) + (m_Element[2][3] * _vector.m_w),
				(m_Element[3][0] * _vector.m_x) + (m_Element[3][1] * _vector.m_y) + (m_Element[3][2] * _vector.m_z) + (m_Element[3][3] * _vector.m_w)
			);
		}

		/*!**********************************************************************************************************************************************************************

			@brief Multiplies this matrix by another matrix
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param prm_Matrix Matrix to multiply this matrix by
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return Product of matrix by matrix

		************************************************************************************************************************************************************************/
		C_Matrix4	operator *= (C_Matrix4 prm_Matrix)
		{
			//! Multiply this matrix object by parameter matrix 
			return *this * prm_Matrix;
		}

		static const C_Matrix4	IDENTITY;
		static const C_Matrix4	ZERO;

		/*!********************************************************************************************************************************************************************
		* @brief Sets all matrix elements to 0																															  *
		**********************************************************************************************************************************************************************/
		void		ZeroMatrix();

		/*!********************************************************************************************************************************************************************
		* @brief Sets matrix as identity (main diagonal elements set to 1, rest set to 0)																					  *
		**********************************************************************************************************************************************************************/
		void		Identity();

		/*!********************************************************************************************************************************************************************
		* @brief Transposes matrix, changing order of the matrix's elements																								  *
		**********************************************************************************************************************************************************************/
		void		Transpose();

		/*!********************************************************************************************************************************************************************
		* @brief Calculates the matrix's determinant																														  *
		* @return The matrix's determinant																																	  *
		**********************************************************************************************************************************************************************/
		float		Determinant();

		/*!********************************************************************************************************************************************************************
		* @brief Returns adjoint matrix																																	  *
		**********************************************************************************************************************************************************************/
		C_Matrix4	Adjoint();

		/*!********************************************************************************************************************************************************************
		* @brief Calculates inverse matrix of this matrix																													  *
		**********************************************************************************************************************************************************************/
		C_Matrix4	Inverse();

		/*!********************************************************************************************************************************************************************
		* @brief Creates a translation matrix, to move an object in the world.																								  *
		* @param prm_TX Translation factor in X axis																														  *
		* @param prm_TY Translation factor in Y axis																														  *
		* @param prm_TZ Translation factor in Z axis																														  *
		* @return A matrix to translate an object in 3D space																												  *
		**********************************************************************************************************************************************************************/
		C_Matrix4&	Translate
		(
			float prm_TX,
			float prm_TY,
			float prm_TZ
		);

		/*!*********************************************************************************************************************************************************************
		* @brief Create rotation matrix along X axis																														   *
		* @param prm_Angle Angle to rotate given in radians																												   *
		* @param prm_Id Boolean to check if matrix will be turned to identity matrix or left with its original info														   *
		***********************************************************************************************************************************************************************/
		C_Matrix4&	RotateX
		(
			float prm_Angle,
			bool prm_Id
		);

		/*!*********************************************************************************************************************************************************************
		* @brief Create rotation matrix along Y axis																														   *
		* @param prm_Angle Angle to rotate given in radians																												   *
		* @param prm_Id Boolean to check if matrix will be turned to identity matrix or left with its original info														   *
		***********************************************************************************************************************************************************************/
		C_Matrix4&	RotateY
		(
			float prm_Angle,
			bool prm_Id
		);

		/*!*********************************************************************************************************************************************************************
		* @brief Create rotation matrix along Z axis																														   *
		* @param prm_Angle Angle to rotate given in radians																												   *
		* @param prm_Id Boolean to check if matrix will be turned to identity matrix or left with its original info														   *
		***********************************************************************************************************************************************************************/
		C_Matrix4&	RotateZ
		(
			float prm_Angle,
			bool prm_Id
		);

		/*!*********************************************************************************************************************************************************************
		*
		*	@brief Calculates a scaling matrix with given X, Y and Z scaling factors																						   *
		*	W factor is left as 1																																			   *
		*
		*	@param prm_SX Scaling factor on X axis																															   *
		*	@param prm_SY Scaling factor on Y axis																															   *
		*	@param prm_SZ Scaling factor on Z axis																															   *
		*
		*	@return A matrix to scale something																																   *
		*
		***********************************************************************************************************************************************************************/
		C_Matrix4&	Scale
		(
			float prm_SX,
			float prm_SY,
			float prm_SZ
		);

		/*!*********************************************************************************************************************************************************************
		*
		* @brief Create look-at matrix																																		   *
		* @param prm_Target Position to look at																															   *
		*
		***********************************************************************************************************************************************************************/
		C_Matrix4		LookAt
		(
			C_Vector3D prm_Position,
			C_Vector3D prm_Target,
			C_Vector3D prm_Up
		);

		/*!
		*/
		C_Matrix4		Projection
		(
			float prm_FOVAngle,
			float prm_Ratio,
			float prm_NearZ,
			float prm_FarZ
		);

		/*!********************************************************************************************************************************************************************
		*
		*	@brief Elements of the matrix.
		*
		***********************************************************************************************************************************************************************/
		float		m_Element[4][4];

  };
}