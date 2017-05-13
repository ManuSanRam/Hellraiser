#pragma once

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"

/*!***********************************************************************************************************************************************************
* @file		HRUtility_Math.h
*
* This file contains mathematic functions used inside the engine, contained inside a Platform-specific Math class.
* The mathematic operations are as follows(in order):
* - Absolute value (Integer and Floating-point).
* - Pi (Normal, inverted, half and two-times)
* - Euler constant.
* - Minimum and maximum integer limits.
* - Degree <-> Radian conversions.
* - Infinite limits.
* - Error margins.
* - Thresholds.
* - Truncations (Integer and Floating-point).
* - Roundings (Floor, Round, Ceil).
* - Fractional.
* - Modulo.
* - Power.
* - Exponential.
* - Logarithms (n-base, 2-base, x-base).
* - Square roots - Normal and Inverted (Includes degrees and radians square roots).
* - Check for limits (NaN, infinite and negative number).
* - Trigonometrics - Sine[Arc], Cosine[Arc], Tangent[Arc, Arc2] (Degrees and Radians).
* - Linear interpolation.
* - Minimum and maximum number.
*
* @date        26-09-2016
* @author		Manuel Aldair Santos Ramón (ManuSanRam)
* @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

namespace HR_SDK
{
  /*!
   * @brief Declares a 3D plane
  */
  class HR_UTILITY_EXPORT C_Plane : public C_Vector3D
  {
  public:
	C_Plane()
	{

	}

	~C_Plane()
	{

	}

	/*!*********************************************************************************************************************************************************************
	 * Using system 																																					   *
	 * X - X0 = U1 + V1																																					   *
	 * Y - Y0 = U2 + V2																																					   *
	 * Z - Z0 = U3 + V3																																					   *
	***********************************************************************************************************************************************************************/
	void Calculate
	(
		const C_Vector3D& prm_PointA,
		const C_Vector3D& prm_PointB,
		const C_Vector3D& prm_PointC
	);

	uint32 CheckPoint
	(
		const C_Vector3D& prm_Point
	);

	/*!*********************************************************************************************************************************************************************
	 * Collisions																																						   *
	***********************************************************************************************************************************************************************/
	/*!
	 * @brief Checks if there was a collision between two planes
	*/
	bool CollisionPlanevPlane
	(
		const C_Plane& prm_Plane
	);
	/*!
	 * @brief Checks if there was a collision between a plane and a sphere
	*/
	bool CollisionPlanevSphere
	(
		const C_Sphere& prm_Sphere
	);
	/*!
	 * @brief Checks if there was a collision between a plane and a line
	*/
	bool CollisionPlanevLine
	(
		const C_Line& prm_Line
	);
	/*!
	*/
	bool CollisionPlanevRay
	(
		const C_Ray& prm_Ray
	);
	/*!
	*/
	bool CollisionPlanevBox
	(
		const C_Box& prm_Box
	);

	/*!
	*/
	float m_D;

	/*!
	*/
	C_Vector3D m_Normal;

  };
}
