#pragma once

#include "HRUtility_Prerequisites.h"
#include <windows.h>

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_WinTimer.h
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
	 * @class C_Timer
	 * @brief Declares a timer, used to keep track of time using a moment in time from which start to count
	*/
	MS_ALIGN(16) class HR_UTILITY_EXPORT C_Timer
	{
	public:
		/*!
		 * @brief Default constructor
		*/
		C_Timer()
		{
			ResetTimer();  //! Safely assure that timer is not holding garbage at the moment of construction
		}

		/*!
		 * @brief Resets the timer
		*/
		void ResetTimer();

		/*!
		 * @brief Obtain a high resolution time scaled in milliseconds
		*/
		unsigned long TimeInMilliseconds();

		/*!
		 * @brief Obtain a high resolution time scaled in microseconds
		*/
		unsigned long TimeInMicroseconds();

		/*!*/
		unsigned long TimeInMillisecondsCPU();

		/*!*/
		unsigned long TimeInMicrosecondsCPU();

		/*!
		 * @brief This function keeps track of the time elapsed since the timer started running
		*/
		unsigned long StartInMS();

		struct Data;
		Data* m;
  };
  GCC_ALIGN(16)
}