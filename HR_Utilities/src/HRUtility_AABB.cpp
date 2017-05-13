#include "HRUtility_AABB.h"

#include "HRUtility_PlatformMath.h"

#include "HRUtility_Plane.h"
#include "HRUtility_Box.h"
#include "HRUtility_Sphere.h"
#include "HRUtility_Ray.h"

namespace HR_SDK
{
	void C_AABB::SetMin
	(
		C_Vector3D prm_Min
	)
	{
		m_Min = prm_Min;
	}

	void C_AABB::SetMax
	(
		C_Vector3D prm_Max
	)
	{
		m_Max = prm_Max;
	}

	bool C_AABB::CollisionAABBvAABB
	(
		const C_AABB& prm_AABB
	)
	{
		return C_PlatformMath::Intersection_AABBvAABB(*this, prm_AABB);
	}

	bool C_AABB::CollisionAABBvPlane
	(
		const C_Plane& prm_Plane
	)
	{
		return C_PlatformMath::Intersection_AABBvPlane(*this, prm_Plane);
	}

	bool C_AABB::CollisionAABBvBox
	(
		const C_Box& prm_Box
	)
	{
		return C_PlatformMath::Intersection_AABBvBox(*this, prm_Box);
	}

	bool C_AABB::CollisionAABBvSphere
	(
		const C_Sphere& prm_Sphere
	)
	{
		return C_PlatformMath::Intersection_AABBvSphere(*this, prm_Sphere);
	}

	bool C_AABB::CollisionAABBvRay
	(
		const C_Ray& prm_Ray
	)
	{
		return C_PlatformMath::Intersection_AABBvRay(*this, prm_Ray);
	}

	bool C_AABB::CollisionAABBvLine
	(
		const C_Line& prm_Line
	)
	{
		return C_PlatformMath::Intersection_AABBvLine(*this, prm_Line);
	}

}
