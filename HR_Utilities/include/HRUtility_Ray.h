#pragma once

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

#include "HRUtility_Prerequisites.h"
#include "HRUtility_Vector3D.h"

namespace HR_SDK
{
  /*!
   * @class C_Ray
   * @brief Declares a three-dimensional ray object, used for raycasting operations
  */
  class HR_UTILITY_EXPORT C_Ray
  {
  public:
	C_Ray() : m_RayStart(0.0f, 0.0f, 0.0f)
	{

	}

	C_Ray(C_Vector3D& prm_Start) : m_RayStart(prm_Start)
	{

	}

	C_Ray(C_Ray& prm_Ray) : m_RayStart(prm_Ray.m_RayStart)
	{

	}

	void Cast();

	bool CollisionRayvAABB();
	bool CollisionRayvPlane();
	bool CollisionRayvBox();
	bool CollisionRayvSphere();

	/*!
	 * @brief Variable that holds the point in space where the ray is being shot from
	*/
    C_Vector3D m_RayStart;

	/*!
	 * @brief
	*/
	C_Vector3D m_Direction;
  };
}