#include "HRUtility_Plane.h"

/*!*************************************************************************************************************************************************************************
 * @file		HRUtility_Plane.cpp																																		   *
 * @brief		Contains function definitions from class C_Plane.																										   *
 * @date		19-03-2017																																				   *
 * @author		Manuel Santos Ramón (ManuSanRam)																														   *
 * @copyright	Infernal Coders S.A																																		   *
***************************************************************************************************************************************************************************/

#include "HRUtility_Box.h"
#include "HRUtility_Sphere.h"
#include "HRUtility_Ray.h"

namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	 * @brief Calculates the plane with three given points where the plane passes through
	 * @param prm_PointA
	 * @param prm_PointB
	 * @param prm_PointC
	***********************************************************************************************************************************************************************/
	void C_Plane::Calculate
	(
		const C_Vector3D& prm_PointA,
		const C_Vector3D& prm_PointB,
		const C_Vector3D& prm_PointC
	)
	{
		C_Vector3D DirU, DirV;

		DirU.Set(prm_PointB.m_x - prm_PointA.m_x, prm_PointB.m_y - prm_PointA.m_y, prm_PointB.m_z - prm_PointA.m_z);
		DirV.Set(prm_PointC.m_x - prm_PointA.m_x, prm_PointC.m_y - prm_PointA.m_y, prm_PointC.m_z - prm_PointA.m_z);

		m_Normal = DirU.Cross(DirV);
		m_Normal.Normalize();
		//! D
		m_D = -(m_Normal.Dot(prm_PointA));
	}

	/*!********************************************************************************************************************************************************************
	 * @brief Checks the location of a certain point towards the plane.
	 * @param prm_Point Point to be located.
	 * @return Returns 1 if the point is in front of the plane, returns 2 if the point is behind the plane, else returns 0 if the 
	***********************************************************************************************************************************************************************/
	uint32 C_Plane::CheckPoint
	(
		const C_Vector3D& prm_Point
	)
	{
		//! Get point's location
		float Comparison = m_Normal.Dot(prm_Point) - m_D;

		//! Check point's location towards plane
		if (Comparison > 0.0f)
		{
			//! Point is in front of plane
			return 1;
		}

		else if (Comparison < 0.0f)
		{
			//! Point is behind plane
			return 2;
		}

		else
		{
			//! Point is on plane
			return 0;
		}
	}

	/*!
	*/
	bool C_Plane::CollisionPlanevPlane
	(
		const C_Plane& prm_Plane
	)
	{
		return false;
	}

	/*!
	*/
	bool C_Plane::CollisionPlanevSphere
	(
		const C_Sphere& prm_Shere
	)
	{
		return false;
	}

	/*!
	*/
	bool C_Plane::CollisionPlanevLine
	(
		const C_Line& prm_Line
	)
	{
		return false;
	}

	/*!
	*/
	bool C_Plane::CollisionPlanevRay
	(
		const C_Ray& prm_Ray
	)
	{
		return false;
	}

	/*!
	*/
	bool C_Plane::CollisionPlanevBox
	(
		const C_Box& prm_Box
	)
	{
		return false;
	}

}