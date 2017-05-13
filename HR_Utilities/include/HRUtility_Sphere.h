#pragma once

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"

namespace HR_SDK
{
	class HR_UTILITY_EXPORT C_Sphere
	{
	public:
		C_Sphere()
		{

		}

		C_Sphere(C_Vector3D prm_Vector, float prm_Radius): m_Center(prm_Vector), m_Radius(prm_Radius)
		{

		}

		~C_Sphere()
		{

		}

		void Set
		(
			C_Vector3D	prm_Center,
			float		prm_Radius
		);

		float CalculateCircumference();
		float CalculateVolume();

		bool CollisionSpherevSphere();
		bool CollisionSpherevAABB();
		bool CollisionSpherevPlane();
		bool CollisionSpherevBox();
		bool CollisionSpherevRay();

		C_Vector3D		m_Center;
		float			m_Radius;
	};
}