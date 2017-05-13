#include "HRUtility_Matrix4.h"
#include "HRUtility_PlatformMath.h"

namespace HR_SDK
{
	/*!
	*/
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

	/*!
	*/
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

	/*!
	*/
	void		C_Matrix4::Transpose()
	{
		C_Matrix4 temp(*this);

		this ->m_Element[0][0] = temp.m_Element[0][0]; 
		this ->m_Element[0][1] = temp.m_Element[1][0]; 
		this ->m_Element[0][2] = temp.m_Element[2][0]; 
		this ->m_Element[0][3] = temp.m_Element[3][0];

		this ->m_Element[1][0] = temp.m_Element[0][1]; 
		this ->m_Element[1][1] = temp.m_Element[1][1]; 
		this ->m_Element[1][2] = temp.m_Element[2][1]; 
		this ->m_Element[1][3] = temp.m_Element[3][1];
		
		this ->m_Element[2][0] = temp.m_Element[0][2]; 
		this ->m_Element[2][1] = temp.m_Element[1][2]; 
		this ->m_Element[2][2] = temp.m_Element[2][2]; 
		this ->m_Element[2][3] = temp.m_Element[3][2];
		
		this ->m_Element[3][0] = temp.m_Element[0][3]; 
		this ->m_Element[3][1] = temp.m_Element[1][3]; 
		this ->m_Element[3][2] = temp.m_Element[2][3]; 
		this ->m_Element[3][3] = temp.m_Element[3][3];
	}

	/*!
	*/
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

	/*!
	* @brief Calculates inverted matrix
	*/
	C_Matrix4	C_Matrix4::Inverse()
	{
		return (this->Adjoint() * (1.0f / this->Determinant()));
	}

	/*!
		@brief Rotates matrix along X axis
	*/
	C_Matrix4&	C_Matrix4::RotateX(float prm_Angle, bool prm_Id)
	{
		if (prm_Id)
		{
			Identity();
		}

		m_Element[1][1] = C_PlatformMath::Cosine(prm_Angle);
		m_Element[1][2] = -C_PlatformMath::Sine(prm_Angle);

		m_Element[2][1] = C_PlatformMath::Sine(prm_Angle);
		m_Element[2][2] = C_PlatformMath::Cosine(prm_Angle);

		return *this;
	}

	/*!
	*/
	C_Matrix4&	C_Matrix4::RotateY(float prm_Angle, bool prm_Id)
	{
		if (prm_Id)
		{
			Identity();
		}

		m_Element[0][0] = C_PlatformMath::Cosine(prm_Angle);
		m_Element[0][2] = C_PlatformMath::Sine(prm_Angle);

		m_Element[2][0] = -C_PlatformMath::Sine(prm_Angle);
		m_Element[2][2] = C_PlatformMath::Cosine(prm_Angle);

		return *this;
	}

	/*!
	*/
	C_Matrix4&	C_Matrix4::RotateZ(float prm_Angle, bool prm_Id)
	{
		//! If prm_Id is true...
		if (prm_Id)
		{
			//! Turn the matrix into identity matrix
			Identity();
		}

		//! Modify elements t rotate along Z axis
		m_Element[0][0] = C_PlatformMath::Cosine(prm_Angle);
		m_Element[0][1] = -C_PlatformMath::Sine(prm_Angle);

		m_Element[1][0] = C_PlatformMath::Sine(prm_Angle);
		m_Element[1][1] = C_PlatformMath::Cosine(prm_Angle);

		return *this;
	}

	/*!
	*/
	C_Matrix4&	C_Matrix4::RotRollPitchYaw(float prm_Pitch, float prm_Yaw, float prm_Roll)
	{
		C_Matrix4 Roll(1), Pitch(1), Yaw(1);

		*this *= Roll.RotateX(prm_Roll, true);
		*this *= Pitch.RotateY(prm_Pitch, true);
		*this *= Yaw.RotateZ(prm_Yaw, true);

		return *this;
	}

	/*!
	*/
	void		C_Matrix4::LookAt(C_Vector3D prm_Target)
	{

	}
}