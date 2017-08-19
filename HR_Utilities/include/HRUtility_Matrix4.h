#pragma once

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"
#include "HRUtility_Vector4D.h"
#include "HRUtility_Quaternion.h"

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
	/*!**************************************************************************************************************************************************************************

		@class C_Matrix4

		@brief 4x4 matrix object, used to describe:
		- Transitions in 3D space.
		- Rotations in 3D space.
		- Scaling in 3D space.
	
	****************************************************************************************************************************************************************************/
	class HR_UTILITY_EXPORT C_Matrix4
	{
	public:
		/*!**********************************************************************************************************************************************************************
		
			@brief Constructor [Default]

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
			@return An empty 4x4 matrix.
		
		************************************************************************************************************************************************************************/
		C_Matrix4()
		{
			//! Create an empty matrix filled with zeros.
			ZeroMatrix();
		}


		/*!**********************************************************************************************************************************************************************
		
			@brief Constructor (Parameter) #1.
			Creates matrix setting it as IDENTITY or ZERO.
			Identity matrix contains:
			
					| 1, 0, 0, 0 |
					|			 |
					| 0, 1, 0, 0 |
				A =	|			 |
					| 0, 0, 1, 0 |
					|			 |
					| 0, 0, 0, 1 |
		
			Zero matrix contains:
		
					| 0, 0, 0, 0 |
					|			 |
					| 0, 0, 0, 0 |
				A =	|			 |
					| 0, 0, 0, 0 |
					|			 |
					| 0, 0, 0, 0 |

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
			@param prm_Creator Defines if matrix is created as identity matrix or as a null matrix.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
			@return A matrix constructed as identity or zero.
		
		************************************************************************************************************************************************************************/
		C_Matrix4
		(
			bool _Creator	//! 
		)
		{
			//! Check which mode to create matrix
			if (_Creator)
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


		/*!**********************************************************************************************************************************************************************
		
			@brief Constructor (Parameter) #2.
			Creates matrix setting each element one by one.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _00 Element (0,0) of the matrix
			@param _01 Element (0,1) of the matrix
			@param _02 Element (0,2) of the matrix
			@param _03 Element (0,3) of the matrix
			@param _10 Element (1,0) of the matrix
			@param _11 Element (1,1) of the matrix
			@param _12 Element (1,2) of the matrix
			@param _13 Element (1,3) of the matrix
			@param _20 Element (2,0) of the matrix
			@param _21 Element (2,1) of the matrix
			@param _22 Element (2,2) of the matrix
			@param _23 Element (2,3) of the matrix
			@param _30 Element (3,0) of the matrix
			@param _31 Element (3,1) of the matrix
			@param _32 Element (3,2) of the matrix
			@param _33 Element (3,3) of the matrix
		
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix containing every element passed as parameter.
			The returned matrix will contain the elements in the following form:
		
			A=	| _00, _01, _02, _03 |
				| _10, _11, _12, _13 |
				| _20, _21, _22, _23 |
				| _30, _31, _32, _33 |
		
		************************************************************************************************************************************************************************/
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


		/*!**********************************************************************************************************************************************************************
		
			@brief Constructor [Copy].

			Creates a new matrix object from the data of another matrix object.
			The returned matrix will contain the elements in the following form:

					| CopyMatrix(0,0), CopyMatrix(0,1), CopyMatrix(0,2), CopyMatrix(0,3) |
					|																	 |
					| CopyMatrix(1,0), CopyMatrix(1,1), CopyMatrix(1,2), CopyMatrix(1,3) |
				A =	|																	 |
					| CopyMatrix(2,0), CopyMatrix(2,1), CopyMatrix(2,2), CopyMatrix(2,3) |
					|																	 |
					| CopyMatrix(3,0), CopyMatrix(3,1), CopyMatrix(3,2), CopyMatrix(3,3) |
		
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param CopyMatrix. Matrix from where data is copied.
		
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix containing the elements from CopyMatrix in the respective positions.
		
		************************************************************************************************************************************************************************/
		C_Matrix4(const C_Matrix4& _CopyMatrix)
		{
			//! Assign each copied element in its respective position in the new matrix 
			m_Element[0][0] = _CopyMatrix.m_Element[0][0]; m_Element[0][1] = _CopyMatrix.m_Element[0][1]; m_Element[0][2] = _CopyMatrix.m_Element[0][2]; m_Element[0][3] = _CopyMatrix.m_Element[0][3];	//! First row
			m_Element[1][0] = _CopyMatrix.m_Element[1][0]; m_Element[1][1] = _CopyMatrix.m_Element[1][1]; m_Element[1][2] = _CopyMatrix.m_Element[1][2]; m_Element[1][3] = _CopyMatrix.m_Element[1][3];	//! Second row
			m_Element[2][0] = _CopyMatrix.m_Element[2][0]; m_Element[2][1] = _CopyMatrix.m_Element[2][1]; m_Element[2][2] = _CopyMatrix.m_Element[2][2]; m_Element[2][3] = _CopyMatrix.m_Element[2][3];	//! Third row
			m_Element[3][0] = _CopyMatrix.m_Element[3][0]; m_Element[3][1] = _CopyMatrix.m_Element[3][1]; m_Element[3][2] = _CopyMatrix.m_Element[3][2]; m_Element[3][3] = _CopyMatrix.m_Element[3][3];	//! Fourth row
		}


		/*!**********************************************************************************************************************************************************************

			@brief Destructor

		************************************************************************************************************************************************************************/
		~C_Matrix4()
		{

		}


		/*!**********************************************************************************************************************************************************************

			@brief Assigns the values from another matrix into another matrix

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _matrix Matrix that holds the data that will be assigned to this matrix.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A new matrix containing the elements passed from the matrix parameter
		
		************************************************************************************************************************************************************************/
		C_Matrix4	operator = (const C_Matrix4& _matrix)
		{
			//! Copy the memory of the parameter into this object
			memcpy(this, &_matrix, sizeof(C_Matrix4));

			//! Return the current instance, which is carrying the current data
			return *this;
		}


		/*!**********************************************************************************************************************************************************************

			@brief Compare if two matrices are equal (All elements are equal)

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _matrix Matrix to compare object with

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return True if matrices are equal, false if not
		
		************************************************************************************************************************************************************************/
		bool		operator == (const C_Matrix4& _matrix)
		{
			//! Iterate through matrix elements
			for (uint32 i = 0; i < 4; ++i)
			{
				for (uint32 j = 0; j < 4; ++j)
				{
					//! Compare if elements at same position are equal
					if (m_Element[i][j] != _matrix.m_Element[i][j])
					{
						//! If said elements are not equal, stop iteration, matrices are not equal
						return false;
					}
				}
			}
			//! If after the end of iteration all elements are equal, matrices are equal
			return true;
		}


		/*!**********************************************************************************************************************************************************************
		
			@brief Non-equal operator

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param _matrix  Matrix to compare with current matrix

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return True if matrices are non-equal, false if matrices are equal
		
		************************************************************************************************************************************************************************/
		bool		operator != 
		(
			const C_Matrix4& _matrix
		)
		{
			return !this->operator==(_matrix);
		}


		/*!**********************************************************************************************************************************************************************

			@brief Addition operator

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param Matrix Matrix which elements will add with

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix result of the addition of two other matrices

		************************************************************************************************************************************************************************/
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


		/*!**********************************************************************************************************************************************************************

			@brief Add-assign operator

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param Matrix Matrix object from which elements will add with

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return The matrix with its data containing the result of the addition of the two matrices

		************************************************************************************************************************************************************************/
		C_Matrix4	operator += (const C_Matrix4& Matrix)
		{
			return *this + Matrix;
		}


		/*!**********************************************************************************************************************************************************************

			@brief Substraction operator

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param Matrix Matrix object from which elements will substract with

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix, result of the substraction of thw two given matrices

		************************************************************************************************************************************************************************/
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


		/*!**********************************************************************************************************************************************************************

			@brief Substract-assign operator

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param Matrix Matrix object from which elements will be substracted

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return 

		************************************************************************************************************************************************************************/
		C_Matrix4	operator -= (const C_Matrix4& Matrix)
		{
			return *this - Matrix;
		}


		/*!**********************************************************************************************************************************************************************

			@brief Multiplication operator for scalars

			Multiplication of two matrices A and B of same dimensions MxN is:

			| (A00 * Scalar), (A01 * Scalar), (A02 * Scalar), (A03 * Scalar) |
			|																 |
			| (A10 * Scalar), (A11 * Scalar), (A12 * Scalar), (A13 * Scalar) |
		A =	|																 |
			| (A20 * Scalar), (A21 * Scalar), (A22 * Scalar), (A23 * Scalar) |
			|																 |
			| (A30 * Scalar), (A31 * Scalar), (A32 * Scalar), (A33 * Scalar) |

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _scalar Scalar number that multiplies 

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return Product matrix result of a matrix multiplied by a scalar

		************************************************************************************************************************************************************************/
		C_Matrix4	operator * (float _scalar) const
		{
			return C_Matrix4
			(
				m_Element[0][0] * _scalar, m_Element[0][1] * _scalar, m_Element[0][2] * _scalar, m_Element[0][3] * _scalar,
				m_Element[1][0] * _scalar, m_Element[1][1] * _scalar, m_Element[1][2] * _scalar, m_Element[1][3] * _scalar,
				m_Element[2][0] * _scalar, m_Element[2][1] * _scalar, m_Element[2][2] * _scalar, m_Element[2][3] * _scalar,
				m_Element[3][0] * _scalar, m_Element[3][1] * _scalar, m_Element[3][2] * _scalar, m_Element[3][3] * _scalar
			);
		}

		
		/*!**********************************************************************************************************************************************************************

			@brief Multiplication equal operator fro scalars

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _scalar Scalar to multiply matrix

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return Matrix multiplied by scalar

		************************************************************************************************************************************************************************/
		C_Matrix4	operator *= (float _scalar)
		{
			return *this * _scalar;
		}


		/*!**********************************************************************************************************************************************************************

			@brief Multiplication operator																															   
		 																																									  
			Multiplication of two matrices A and B of same dimensions MxN is:																									   
																																													 
				| (A00*B00 + A01*B10 + A02*B20 + A03*B30), (A00*B01 + A01*B11 + A02*B21 + A03*B31), (A00*B02 + A01*B12 + A02*B22 + A03*B32), (A00*B03 + A01*B13 + A02*B23 + A03*B33) |
				|																																									 |
				| (A10*B00 + A01*B10 + A12*B20 + A13*B30), (A10*B01 + A11*B11 + A12*B21 + A13*B31), (A10*B02 + A11*B12 + A12*B22 + A13*B32), (A10*B03 + A11*B13 + A12*B23 + A13*B33) |
			A =	|																																									 |
				| (A20*B00 + A01*B10 + A22*B20 + A23*B30), (A20*B01 + A21*B11 + A22*B21 + A23*B31), (A20*B02 + A21*B12 + A22*B22 + A23*B32), (A20*B03 + A21*B13 + A22*B23 + A23*B33) |
				|																																									 |
				| (A30*B00 + A31*B10 + A32*B20 + A33*B30), (A30*B01 + A31*B11 + A32*B21 + A33*B31), (A30*B02 + A31*B12 + A32*B22 + A33*B32), (A30*B03 + A31*B13 + A32*B23 + A33*B33) |

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _matrix Matrix to multiply with																														   
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return Product between two matrices																																   
		
		************************************************************************************************************************************************************************/
		C_Matrix4	operator * (C_Matrix4 _matrix) const
		{
			//! Perform the operations
			float
				_00 = (m_Element[0][0] * _matrix.m_Element[0][0]) + (m_Element[0][1] * _matrix.m_Element[1][0]) + (m_Element[0][2] * _matrix.m_Element[2][0]) + (m_Element[0][3] * _matrix.m_Element[3][0]),
				_01 = (m_Element[0][0] * _matrix.m_Element[0][1]) + (m_Element[0][1] * _matrix.m_Element[1][1]) + (m_Element[0][2] * _matrix.m_Element[2][1]) + (m_Element[0][3] * _matrix.m_Element[3][1]),
				_02 = (m_Element[0][0] * _matrix.m_Element[0][2]) + (m_Element[0][1] * _matrix.m_Element[1][2]) + (m_Element[0][2] * _matrix.m_Element[2][2]) + (m_Element[0][3] * _matrix.m_Element[3][2]),
				_03 = (m_Element[0][0] * _matrix.m_Element[0][3]) + (m_Element[0][1] * _matrix.m_Element[1][3]) + (m_Element[0][2] * _matrix.m_Element[2][3]) + (m_Element[0][3] * _matrix.m_Element[3][3]),

				_10 = (m_Element[1][0] * _matrix.m_Element[0][0]) + (m_Element[1][1] * _matrix.m_Element[1][0]) + (m_Element[1][2] * _matrix.m_Element[2][0]) + (m_Element[1][3] * _matrix.m_Element[3][0]),
				_11 = (m_Element[1][0] * _matrix.m_Element[0][1]) + (m_Element[1][1] * _matrix.m_Element[1][1]) + (m_Element[1][2] * _matrix.m_Element[2][1]) + (m_Element[1][3] * _matrix.m_Element[3][1]),
				_12 = (m_Element[1][0] * _matrix.m_Element[0][2]) + (m_Element[1][1] * _matrix.m_Element[1][2]) + (m_Element[1][2] * _matrix.m_Element[2][2]) + (m_Element[1][3] * _matrix.m_Element[3][2]),
				_13 = (m_Element[1][0] * _matrix.m_Element[0][3]) + (m_Element[1][1] * _matrix.m_Element[1][3]) + (m_Element[1][2] * _matrix.m_Element[2][3]) + (m_Element[1][3] * _matrix.m_Element[3][3]),

				_20 = (m_Element[2][0] * _matrix.m_Element[0][0]) + (m_Element[2][1] * _matrix.m_Element[1][0]) + (m_Element[2][2] * _matrix.m_Element[2][0]) + (m_Element[2][3] * _matrix.m_Element[3][0]),
				_21 = (m_Element[2][0] * _matrix.m_Element[0][1]) + (m_Element[2][1] * _matrix.m_Element[1][1]) + (m_Element[2][2] * _matrix.m_Element[2][1]) + (m_Element[2][3] * _matrix.m_Element[3][1]),
				_22 = (m_Element[2][0] * _matrix.m_Element[0][2]) + (m_Element[2][1] * _matrix.m_Element[1][2]) + (m_Element[2][2] * _matrix.m_Element[2][2]) + (m_Element[2][3] * _matrix.m_Element[3][2]),
				_23 = (m_Element[2][0] * _matrix.m_Element[0][3]) + (m_Element[2][1] * _matrix.m_Element[1][3]) + (m_Element[2][2] * _matrix.m_Element[2][3]) + (m_Element[2][3] * _matrix.m_Element[3][3]),

				_30 = (m_Element[3][0] * _matrix.m_Element[0][0]) + (m_Element[3][1] * _matrix.m_Element[1][0]) + (m_Element[3][2] * _matrix.m_Element[2][0]) + (m_Element[3][3] * _matrix.m_Element[3][0]),
				_31 = (m_Element[3][0] * _matrix.m_Element[0][1]) + (m_Element[3][1] * _matrix.m_Element[1][1]) + (m_Element[3][2] * _matrix.m_Element[2][1]) + (m_Element[3][3] * _matrix.m_Element[3][1]),
				_32 = (m_Element[3][0] * _matrix.m_Element[0][2]) + (m_Element[3][1] * _matrix.m_Element[1][2]) + (m_Element[3][2] * _matrix.m_Element[2][2]) + (m_Element[3][3] * _matrix.m_Element[3][2]),
				_33 = (m_Element[3][0] * _matrix.m_Element[0][3]) + (m_Element[3][1] * _matrix.m_Element[1][3]) + (m_Element[3][2] * _matrix.m_Element[2][3]) + (m_Element[3][3] * _matrix.m_Element[3][3])
			;

			//! Construct new matrix with the above results
			return C_Matrix4
			(
				_00, _01, _02, _03,
				_10, _11, _12, _13,
				_20, _21, _22, _23,
				_30, _31, _32, _33
			);
		}


		/*!**********************************************************************************************************************************************************************

			@brief Multiplies two matrices, saving the result in one of them

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _matrix Matrix to multiply this matrix by

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return Product of matrix by matrix

		************************************************************************************************************************************************************************/
		C_Matrix4	operator *= (C_Matrix4 _matrix)
		{
			//! Multiply this matrix object by parameter matrix 
			return *this * _matrix;
		}


		/*!**********************************************************************************************************************************************************************

			@brief Perform a MATRIX x VECTOR multiplication

			The multiplication is performed as follows:

				| (0,0), (0,1), (0,2), (0,3) |							  | A(0,0) x V[x] + A(0,1) x V[y] + A(0,2) x V[z] + A(0,3) x V[w] |
				|							 |							  |																  |
				| (0,0), (0,1), (0,2), (0,3) |							  | A(1,0) x V[x] + A(1,1) x V[y] + A(1,2) x V[z] + A(1,3) x V[w] |
			A =	|							 |   x   V = | X, Y, Z, W | = |																  |
				| (0,0), (0,1), (0,2), (0,3) |							  | A(2,0) x V[x] + A(2,1) x V[y] + A(2,2) x V[z] + A(2,3) x V[w] |
				|							 |							  |																  |
				| (0,0), (0,1), (0,2), (0,3) |							  | A(3,0) x V[x] + A(3,1) x V[y] + A(3,2) x V[z] + A(3,3) x V[w] |

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _vector 4D vector used to perform the multiplication

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A vector, result of the multiplication of a vector and a matrix

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
			
			@brief Sets all matrix elements to 0

		************************************************************************************************************************************************************************/
		void		ZeroMatrix();


		/*!**********************************************************************************************************************************************************************
			
			@brief Sets matrix as identity (main diagonal elements set to 1, rest set to 0)		

		************************************************************************************************************************************************************************/
		void		Identity();


		/*!**********************************************************************************************************************************************************************

			@brief Transposes matrix, changing order of the matrix's elements																								  

		************************************************************************************************************************************************************************/
		void		Transpose();


		/*!**********************************************************************************************************************************************************************

			@brief Calculates the matrix's determinant

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A number representing the determinant of a matrix																																	  

		************************************************************************************************************************************************************************/
		float		Determinant();


		/*!**********************************************************************************************************************************************************************

			@brief Calculates the adjoint matrix

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix representing the adjoint matrix of another matrix

		************************************************************************************************************************************************************************/
		C_Matrix4	Adjoint();


		/*!**********************************************************************************************************************************************************************

			@brief Calculates inverse matrix of this matrix

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix, representing the inverse matrix of another matrix

		************************************************************************************************************************************************************************/
		C_Matrix4	Inverse();


		/*!**********************************************************************************************************************************************************************

			@brief Creates a translation matrix, to move an object in the world.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _TX Translation factor in 'X' axis
			@param _TY Translation factor in 'Y' axis
			@param _TZ Translation factor in 'Z' axis

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix to translate an object in 3D space

		************************************************************************************************************************************************************************/
		C_Matrix4&	Translate
		(
			bool _id,
			float _TX,
			float _TY,
			float _TZ
		);


		/*!**********************************************************************************************************************************************************************

			@brief Create rotation matrix along X axis

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _Angle Angle to rotate given in radians
			@param _Id Boolean to check if matrix will be turned to identity matrix or left with its original info

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix to rotate along the 'X' axis

		************************************************************************************************************************************************************************/
		C_Matrix4&	RotateX
		(
			float _Angle,
			bool _Id
		);


		/*!**********************************************************************************************************************************************************************

			@brief Create rotation matrix along Y axis

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _Angle Angle to rotate given in radians
			@param _Id Boolean to check if matrix will be turned to identity matrix or left with its original info

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix to rotate along the 'Y' axis

		************************************************************************************************************************************************************************/
		C_Matrix4&	RotateY
		(
			float _Angle,
			bool _Id
		);


		/*!**********************************************************************************************************************************************************************

			@brief Create rotation matrix along Z axis

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _Angle Angle to rotate given in radians																												   
			@param _Id Boolean to check if matrix will be turned to identity matrix or left with its original info

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix to rotate along the 'Z' axis

		************************************************************************************************************************************************************************/
		C_Matrix4&	RotateZ
		(
			float _Angle,
			bool _Id
		);


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
		C_Matrix4&	Scale
		(
			bool _id,
			float _SX,
			float _SY,
			float _SZ
		);


		/*!**********************************************************************************************************************************************************************
		
			@brief Create look-at matrix

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param _position Position from where we're looking at
			@param _target Vector to indicate where is the point we're looking at
			@param _up Vector orthonormal to indicate the "UP" direction

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return A matrix containing rotation to look at a given target
		
		************************************************************************************************************************************************************************/
		C_Matrix4		LookAt
		(
			C_Vector3D _position,
			C_Vector3D _target,
			C_Vector3D _up
		);


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
		C_Matrix4		Projection
		(
			float _fovAngle,
			float _aspectRatio,
			float _nearZ,
			float _farZ
		);


		/*!********************************************************************************************************************************************************************
		
			@brief Elements of the matrix.
		
		***********************************************************************************************************************************************************************/
		float		m_Element[4][4];


  };
}