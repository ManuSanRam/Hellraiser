#include "HRUtility_Box.h"
#include "HRUtility_PlatformMath.h"

namespace HR_SDK
{
	void C_Box::SetMin
	(
		C_Vector3D prm_Min
	)
	{
		
	}

	void C_Box::SetMax
	(
		C_Vector3D prm_Min
	)
	{

	}

	bool C_Box::CollisionBoxvBox
	(
		const C_Box& prm_Box
	)
	{
		return C_PlatformMath::Intersection_BoxvBox(*this, prm_Box);
	}

	bool C_Box::CollisionBoxvPlane
	(
		const C_Plane& prm_Plane
	)
	{
		return C_PlatformMath::Intersection_PlanevBox(prm_Plane, *this);
	}
	
	bool C_Box::CollisionBoxvSphere
	(
		const C_Sphere& prm_Sphere
	)
	{
		return C_PlatformMath::Intersection_BoxvSphere(*this, prm_Sphere);
	}
	
	bool C_Box::CollisionBoxvLine
	(
		const C_Line& prm_Line
	)
	{
		return C_PlatformMath::Intersection_BoxvLine(*this, prm_Line);
	}

	bool C_Box::CollisionBoxvRay
	(
		const C_Ray& prm_Ray
	)
	{
		return C_PlatformMath::Intersection_BoxvRay(*this, prm_Ray);
	}

}