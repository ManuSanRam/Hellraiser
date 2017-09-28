#include <HRUtility_Logger.h>


#include <HRUtility_PlatformMath.h>


#include <HRUtility_Vector2D.h>
#include <HRUtility_Vector2Di.h>
#include <HRUtility_Vector3D.h>
#include <HRUtility_Vector4D.h>


#include <HRUtility_Matrix3.h>
#include <HRUtility_Matrix4.h>


#include <HRUtility_Quaternion.h>


#include <HRUtility_Radian.h>
#include <HRUtility_Degree.h>


#include <HRUtility_Datastream.h>



/*!******************************************************************************************************************************************************************************

	@file		HR_UnitTest_main.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	This file contains the entrance point for the Utilities' unit Test program.
	It will serve to test the following functions:
	- Mathematic library.
		- Arithmetics.
		- Power.
	    - Vector math.
	    - Matrix math.
	    - Quaternion math.
	- File Management.
	    - Directory.
	    - File.
	- Logger.
	- Thread management.
	- Debug.
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date        03-10-2016
	@author		Manuel Aldair Santos Ramón (ManuSanRam)
	@copyright	Infernal Coders S.A.

********************************************************************************************************************************************************************************/


//! We use the whole SDK for further testing of the Utilities library.
using namespace HR_SDK;

/*!******************************************************************************************************************************************************************************

	@brief Defines the Utilities' Unit Test's entrance point
	@return The result of the execution of the program. 0 is a successful compilation and execution, Non-zero marks an unsuccessful run.

********************************************************************************************************************************************************************************/
int main()
{
	//! Create the logger to present results to user
	HR_SDK::C_Logger UtilitiesLog;

	//! Init logger
	UtilitiesLog.Init("../externals/Log Files/UtilitiesLog.html"); //! File to write to
	UtilitiesLog.AddEntry //! Add a new log entry
	(
		MessageLevel::_MESSAGE,			//! Write as message in log stack
		"LOGGER FILE - Initiated...",	//! Message
		HR_FILE,						//! File 
		HR_FUNCTION,					//! Function
		HR_LINE							//! Line
	);



	/*!**************************************************************************************************************************************************************************

		>> TEST #1: TRUNCATION FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Truncation(3.5286f) == 3)
	{//! Function returned expected result
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack
			"FUNCTION: Truncation - Correct",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! Function failed to return expected result
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,				//! Write as message in log stack
			"FUNCTION: Truncation - INCORRECT",	//! Message
			HR_FILE,							//! File 
			HR_FUNCTION,						//! Function
			HR_LINE								//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #2: FLOAT-POINT TRUNCATION FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::TruncationFloat(3.5f) == 3.0f)
	{//! Function returned expected result
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack
			"FUNCTION: Float truncation - Correct",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! Function failed to return expected result
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,				//! Write as message in log stack
			"FUNCTION: Float truncation - INCORRECT",	//! Message
			HR_FILE,							//! File 
			HR_FUNCTION,						//! Function
			HR_LINE								//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #3: FLOORING FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Floor(3.5f) == 3.0f)
	{//! Function returned expected result
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack
			"FUNCTION: Flooring - Correct",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! Function failed to return expected result
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,				//! Write as message in log stack
			"FUNCTION: Flooring - INCORRECT",	//! Message
			HR_FILE,							//! File 
			HR_FUNCTION,						//! Function
			HR_LINE								//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #4: ROUNDING FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Round(3.2f) == 3.0f)
	{//!
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack
			"FUNCTION: Round - CORRECT", 	//! Message
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Round - INCORRECT", 	//! Message
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #5: CEILING FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Ceil(3.2f) == 4.0f)	//! Check for a expected result.
	{//! 
		//! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Ceiling - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Ceiling - INCORRECT",//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}


	/*!**************************************************************************************************************************************************************************

		>> TEST #6: FRACTIONAL FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Fractional(3.2345f) == 0.2345f)	//! Check for a expected result.
	{//! 
		//! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Fractional - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Fractional - INCORRECT",//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #7: MODULO FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Modulo(16, 3) == 1)	//! Check for a expected result.
	{//! 
	 //! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Modulo - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Modulo - INCORRECT",//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #8: POWER FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Power(2, 4) == 16)	//! Check for a expected result.
	{//! 
	 //! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Power - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Power - INCORRECT",	//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #9: EXPONENTIAL FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Exponential(1) < 0 )	//! Check for a expected result.
	{//! 
	 //! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Exponential - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Exponential - INCORRECT",	//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #10: FACTORIAL FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Factorial(4) == 24)	//! Check for a expected result.
	{//! 
	 //! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Factorial - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Factorial - INCORRECT",	//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		>> TEST #11: RADIAN -> DEGREE CONVERSION FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Factorial(4) == 24)	//! Check for a expected result.
	{//! 
	 //! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Factorial - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Factorial - INCORRECT",	//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

	>> TEST #12: DEGREE -> RADIAN CONVERSION FUNCTION

	****************************************************************************************************************************************************************************/
	if (C_PlatformMath::Factorial(4) == 24)	//! Check for a expected result.
	{//! 
	 //! Write to log file 
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,			//! Write as message in log stack 
			"FUNCTION: Factorial - CORRECT",	//! Message
			HR_FILE,						//! File 
			HR_FUNCTION,					//! Function
			HR_LINE							//! Line
		);
	}

	else
	{//! 
	 //! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,			//! Write as message in log stack
			"FUNCTION: Factorial - INCORRECT",	//! Message 
			HR_FILE, 						//! File 
			HR_FUNCTION, 					//! Function
			HR_LINE							//! Line
		);
	}



	/*!**************************************************************************************************************************************************************************

		TEST #: FILE READING FUNCTION

	****************************************************************************************************************************************************************************/
	//! Create a read only filestream object
	C_Filestream InputTest(FileAccess::_READ);
	//! Open the file to read
	InputTest.Open("../binary/Other Files/HR_ReadTest.txt", false);
	//! Buffer that will contain the info read from the file
	Vector<char> Buffer;
	//! Get the size of the file
	SIZE_T FileSize = InputTest.GetSize();
	Buffer.resize(100);
	
	//! Read file and insert read data into the buffer
	InputTest.Read(&Buffer[0], 100);

	//! String used to present read data to the user
	String strBuffer;
	
	//! Save the read data to the string
	strBuffer.insert(strBuffer.end(), Buffer.begin(), Buffer.end());
	


	if (strBuffer.c_str() != NULL)	//! Check if file was successfully read - Data would be captured here if true
	{//! Function returned expected result
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_MESSAGE,				//! Write as message in log stack
			"FUNCTION: File reading - CORRECT",	//! Message
			HR_FILE,							//! File 
			HR_FUNCTION,						//! Function
			HR_LINE								//! Line
		);

		//! Present read buffer to the screen
		std::cout << strBuffer;
	}
	
	else
	{//! Function failed to return expected result!
		//! Write to log file
		UtilitiesLog.AddEntry
		(
			MessageLevel::_ERROR,					//! Write as message in log stack	
			"FUNCTION: File reading - INCORRECT",	//! Message
			HR_FILE,								//! File 
			HR_FUNCTION,							//! Function
			HR_LINE									//! Line
		);
	}
	
	//! Expect keyboard input
	std::cin.get();

	//! Close the file and write to it.
	InputTest.Close();
	UtilitiesLog.Close("HRUtilitiesTest");
	
	return 0;
}