#include "HRUtility_Quaternion.h"

/*!******************************************************************************************************************************************************************************
	
	@file		HRUtility_Quaternion.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the definition of the class C_Quaternion

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		29-07-2017
	@author		Manuel Santos Ram�n [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/

#include "HRUtility_PlatformMath.h"

namespace HR_SDK
{
	/*!
	*/
	float C_Quaternion::Magnitude()
	{
		return C_PlatformMath::
			SqRoot<float>
			(
				C_PlatformMath::Power<float>(m_w, 2.0f) + 
				C_PlatformMath::Power<float>(m_x, 2.0f) + 
				C_PlatformMath::Power<float>(m_y, 2.0f) + 
				C_PlatformMath::Power<float>(m_z, 2.0f)
			);
	}

	void C_Quaternion::Normalize()
	{
		float Magnitude = this->Magnitude();
		*this *= 1.0f / Magnitude;
	}
}