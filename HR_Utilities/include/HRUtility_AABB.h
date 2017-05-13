#pragma once

/*!************************************************************************************************************************************************************************
 * @file			HRUtility_AABB.h
 *
 * 
 *
 * @date			20-03-2017
 * @author			Manuel Santos Ramón (ManuSanRam)
 * @copyright		Infernal Coders S.A
***************************************************************************************************************************************************************************/

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"

namespace HR_SDK
{
  /*!***********************************************************************************************************************************************************************
   * @brief Defines an Axis-aligned bounding box (AABB) object, a box that always remains aligned to all axis															   *
  *************************************************************************************************************************************************************************/
  class HR_UTILITY_EXPORT C_AABB
  {
  public:
	/*!
	*/
	C_Vector3D m_Min;

	/*!
	*/
	C_Vector3D m_Max;

	/*!
	*/
	void SetMin
	(
		C_Vector3D prm_Min
	);

	/*!
	*/
	void SetMax
	(
		C_Vector3D prm_Max
	);

	/*!
	*/
	bool CollisionAABBvLine
	(
		const C_Line& prm_Line
	);

	/*!
	*/
	bool CollisionAABBvAABB
	(
		const C_AABB& prm_Box
	);
	
	/*!
	*/
	bool CollisionAABBvPlane
	(
		const C_Plane& prm_Plane
	);

	/*!
	*/
	bool CollisionAABBvBox
	(
		const C_Box& prm_Plane
	);

	/*!
	*/
	bool CollisionAABBvSphere
	(
		const C_Sphere& prm_Sphere
	);
	
	/*!
	*/
	bool CollisionAABBvRay
	(
		const C_Ray& prm_Ray
	);
  };
}
