#include "HRUtility_Timer.h"
#include <Windows.h>

namespace HR_SDK
{
	struct C_Timer::Data
	{
		LARGE_INTEGER m_Frequency;
		LARGE_INTEGER m_Start;
		time_t m_ZeroClock;
	};

	void C_Timer::ResetTimer()
	{
		//! Get the frequency of performance
		QueryPerformanceFrequency(&m->m_Frequency);
		//! Get the count of performance
		QueryPerformanceCounter(&m->m_Start);

		//! Zero clock takes the current processor time
		m->m_ZeroClock = clock();
	}

	unsigned long C_Timer::StartInMS()
	{
		unsigned long newTicks = 
			(unsigned long) //! Prevent type conversion warnings
			(1000 * m->m_Start.QuadPart //! Scale count of time stamp by 1000 for milliseconds
				/ m->m_Frequency.QuadPart); //! Divide by ticks frequency to obtain milliseconds
		return newTicks; //! Return calculation of time
	}

	unsigned long C_Timer::TimeInMilliseconds()
	{
		LARGE_INTEGER CurrentTime; //! Variable that will hold the current captured time stamp
		QueryPerformanceCounter(&CurrentTime); //! Get the time stamp

		LONGLONG NewTime = CurrentTime.QuadPart - m->m_Start.QuadPart; //! New time holds the value of the time elapsed since the start time

		unsigned long NewTicks = 
			(unsigned long) //! We convert to unsigned long, to prevent type conversion-warnings
			(1000 * NewTime //! We scale the new time by 1000 (milliseconds)
				/ m->m_Frequency.QuadPart); //! The division gives us milliseconds

		return NewTicks; //! Return the calculated time value in milliseconds
	}

	unsigned long C_Timer::TimeInMicroseconds()
	{
		LARGE_INTEGER CurrentTime; //! Variable that will hold the current captured time stamp
		QueryPerformanceCounter(&CurrentTime); //! Get the time stamp

		LONGLONG NewTime = CurrentTime.QuadPart - m->m_Start.QuadPart; //! New time holds the value of the time elapsed since the start time

		unsigned long NewTicks =
			(unsigned long) //! We convert to unsigned long, to prevent type conversion-warnings
			(1000000 * NewTime //! We scale the new time by 1000 (milliseconds)
				/ m->m_Frequency.QuadPart); //! The division gives us milliseconds

		return NewTicks; //! Return the calculated time value in milliseconds
	}
}