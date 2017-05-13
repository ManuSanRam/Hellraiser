#include "HRUtility_Time.h"

namespace HR_SDK
{
	String C_Time::GetDate
	(
		Date::E prm_DateFormat,
		Time::E prm_TimeFormat
	)
	{
		//! Temporal variables to use.
		time_t Time;
		struct tm* TimeInfo;
		char Date[200];
		String DateStr;

		//! Capture the time in format of time_t type
		time(&Time);

		//! Get the local time
		TimeInfo = localtime(&Time);
		
		//!
		if (prm_DateFormat == Date::_MIDDLE_ENDIAN)
		{
			if (prm_TimeFormat == Time::_24HRS)
			{
				strftime(Date, 200, "%A, %B %d, %Y - %H : %M", TimeInfo);
			}

			else if (prm_TimeFormat == Time::_12HRS)
			{
				strftime(Date, 200, "%A, %B %d, %Y - %I : %M %p", TimeInfo);
			}
		}

		//!
		else if (prm_DateFormat == Date::_LITTLE_ENDIAN)
		{
			if (prm_TimeFormat == Time::_24HRS)
			{
				strftime(Date, 200, "%A, %d %B, %Y - %H : %M", TimeInfo);
			}

			else if (prm_TimeFormat == Time::_12HRS)
			{
				strftime(Date, 200, "%A, %d %B, %Y - %I : %M %p", TimeInfo);
			}
		}

		//!
		else if (prm_DateFormat == Date::_BIGGER_ENDIAN)
		{
			if (prm_TimeFormat == Time::_24HRS)
			{
				strftime(Date, 200, "%A, %Y, %B %d - %H : %M", TimeInfo);
			}

			else if (prm_TimeFormat == Time::_12HRS)
			{
				strftime(Date, 200, "%A, %Y, %B %d - %I : %M %p", TimeInfo);
			}
		}

		DateStr.insert(DateStr.begin(), Date, Date + sizeof(Date));
		return DateStr;
	}
};