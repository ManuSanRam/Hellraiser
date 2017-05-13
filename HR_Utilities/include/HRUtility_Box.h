#pragma once

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"

namespace HR_SDK
{
	class HR_UTILITY_EXPORT C_Box
	{
	public:
		C_Box()
		{

		}

		~C_Box()
		{

		}

		void SetMin
		(
			C_Vector3D prm_Min
		);

		void SetMax
		(
			C_Vector3D prm_Max
		);

		bool CollisionBoxvBox
		(
			const C_Box& prm_Box
		);
		bool CollisionBoxvPlane
		(
			const C_Plane& prm_Plane
		);
		bool CollisionBoxvSphere
		(
			const C_Sphere& prm_Sphere
		);
		bool CollisionBoxvLine
		(
			const C_Line& prm_Line
		);
		bool CollisionBoxvRay
		(
			const C_Ray& prm_Ray
		);

		C_Vector3D m_Min;
		C_Vector3D m_Max;
	};
}
