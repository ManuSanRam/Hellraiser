#pragma once
#pragma warning(disable : 4996)

/*!************************************************************************************************************************************************************************
 * @file	    HRUtility_Time.h
 *
 * This file contains the functions to format date and time into strings.
 * The functions are as follows(in order):
 * - Obtain independently day, month and year.
 *   - Format day, month and year as two digit number or full format.
 *   - Format day as day of the month and day of the week or just day of the month.
 * - Obtain time in two different formats.
 *   - 24 hrs (HH:MM:SS)
 *   - 12 hrs (HH:MM:SS am/pm)
 * - Format date using different country formats.
 *   - Big-endian date format (YYYY - MMMM - DD/WWDD).
 *   - Middle-endian date format (DD/WWDD - MMMM - YYYY).
 *   - Little-endian date format (MMMM - DD/WWDD - YYYY).
 *
 * @date        21-10-2016
 * @author	    Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright   Infernal Coders S.A.
***************************************************************************************************************************************************************************/

#include "HRUtility_Prerequisites.h"

namespace HR_SDK
{
	namespace Date
	{
		enum E
		{
			/*!************************************************************************************************************************************************************
			 * @brief Writes date in next format: Day / Month / Year
			***************************************************************************************************************************************************************/
			_LITTLE_ENDIAN,
			/*!************************************************************************************************************************************************************
			 * @brief Writes date in next format: Month / Day / Year
			***************************************************************************************************************************************************************/
			_MIDDLE_ENDIAN,
			/*!************************************************************************************************************************************************************
			 * @brief Writes date in next format: Year / Month / Day
			***************************************************************************************************************************************************************/
			_BIGGER_ENDIAN
		};
	}

	namespace Time
	{
		enum E
		{
			_12HRS = 12,
			_24HRS = 24
		};
	}

	/*!********************************************************************************************************************************************************************
	 * @brief This class is used to get the time in 
	***********************************************************************************************************************************************************************/
	class HR_UTILITY_EXPORT C_Time
	{
	public:
		static String GetDate
		(
			Date::E prm_DateFormat,
			Time::E prm_TimeFormat
		);
	};
}