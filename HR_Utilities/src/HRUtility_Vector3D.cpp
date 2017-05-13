#include "HRUtility_Vector3D.h"
#include "HRUtility_PlatformMath.h"

/*!*************************************************************************************************************************************************************************
 * @brief		HRUtility_Vector3D.cpp																																	   *
 * 																																										   *
 * This file contains the definitions of the functions in the class C_Vector3D, declared in the file HRUtility_Vector3D.h												   *
 * 																																										   *
 * @date		19-02-2017																																				   *
 * @author		Manuel Santos Ramón (ManuSanRam)																														   *
 * @copyright	Infernal Coders S.A																																		   *
***************************************************************************************************************************************************************************/

namespace HR_SDK
{
	/*!*********************************************************************************************************************************************************************
	 * @brief Obtains the length of the vector.																															   *
	 * @retun Length of the vector																																		   *
	***********************************************************************************************************************************************************************/
	float      C_Vector3D::Length() const
	{
		return C_PlatformMath::SqRoot(C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f) + C_PlatformMath::Power<float>(m_z, 2.0f));
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Obtains the squared length of the vector.																													   *
	 * @return The length of the vector squared.																														   *
	***********************************************************************************************************************************************************************/
	float      C_Vector3D::SqrLength() const
	{
		return (C_PlatformMath::Power<float>(m_x, 2.0f) + C_PlatformMath::Power<float>(m_y, 2.0f) + C_PlatformMath::Power<float>(m_z, 2.0f));
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Calculates the scalar/dot product between to vectors																										   *
	 * @param prm_Vector Vector used for the method.																													   *
	 * @return Returns the proyection of one vector over the other																										   *
	***********************************************************************************************************************************************************************/
	float      C_Vector3D::Dot(const C_Vector3D& prm_Vector) const
	{
		return ((m_x * prm_Vector.m_x) + (m_y * prm_Vector.m_y) + (m_z * prm_Vector.m_z));
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Obtains the angle in which the vector is pointig towards																									   *
	 * @return The angle of the vector expressed in degrees.																											   *
	***********************************************************************************************************************************************************************/
	float      C_Vector3D::Angle(const C_Vector3D& prm_Vector) const
	{
		return C_PlatformMath::ArcCosine((Dot(prm_Vector) * (1.0f / (Length() * prm_Vector.Length()))));
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Equal operator checks if the elements of both vectors are the same.																						   *
	***********************************************************************************************************************************************************************/
	void       C_Vector3D::Normalize()
	{
		*this *= 1.0f / Length();
	}

	/*!
	* @brief Equal operator checks if the elements of both vectors are the same.
	*/
	C_Vector3D C_Vector3D::Cross(const C_Vector3D& prm_Vector)
	{
		return C_Vector3D
		(
			1.0f * ((m_y * prm_Vector.m_z) - (m_z * prm_Vector.m_y)),  //! Get X
			-1.0f * ((m_z * prm_Vector.m_x) - (m_x * prm_Vector.m_z)),  //! Get Y
			1.0f * ((m_x * prm_Vector.m_y) - (m_y * prm_Vector.m_x))   //! Get Z
		);
	}

	/*!
	* @brief Equal operator checks if the elements of both vectors are the same.
	*/
	C_Vector3D C_Vector3D::UnitCross(const C_Vector3D& prm_Vector)
	{
		C_Vector3D result = Cross(prm_Vector);
		return result / result.Length();
	}

	/*!
	*/
	void C_Vector3D::NullVector()
	{
		this->m_x = 0.0f;
		this->m_y = 0.0f;
		this->m_z = 0.0f;
	}

	/*!
	*/
	void C_Vector3D::UnitVector()
	{
		this->m_x = 1.0f;
		this->m_y = 1.0f;
		this->m_z = 1.0f;
	}
}