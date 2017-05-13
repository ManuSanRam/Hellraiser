#pragma once

#include "HRUtility_Prerequisites.h"

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
* @date	    11-09-2016
* @author		Manuel Aldair Santos Ramón (ManuSanRam)
* @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

#if (HR_ACTIVE_PLATFORM == HR_PLATFORM_WINDOWS)  //! If the current platform running the engine is a Microsoft's Windows PC platform...
  //#include "HRUtility_WindowsMath.h"  //! Include the mathematic library's header for a Microsoft's Windows PC platform. 
#elif (HR_ACTIVE_PLATFORM == HR_PLATFORM_OS_X)  //! If the current platform running the engine is an Apple's Mac OS X platform...
  //#include "HRUtility_OSXMath.h"  //! Include the mathematic library's header for a Apple's Mac OS X platform.
#elif (HR_ACTIVE_PLATFORM == HR_PLATFORM_LINUX)  //! If the current platform running the engine is a GNU/Linux's Linux PC platform...
  //#include "HRUtility_LinuxMath.h"  //! Include the mathematic library's header for a GNU/Linux's Linux PC platform.
#elif (HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4)  //! If the current platform running the engine is a Sony's PS4 for developing purposes...
  //#include "HRUtility_PS4Math.h"  //! Include the mathematic library's header for a Sony's Play Station 4 Developing platform.
#endif