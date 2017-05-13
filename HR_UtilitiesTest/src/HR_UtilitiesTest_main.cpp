#include <HRUtility_PlatformMath.h>
#include <HRUtility_Vector3D.h>
#include <HRUtility_Logger.h>

/*!***********************************************************************************************************************************************************
 * @file		HR_UnitTest_main.cpp
 *
 * This file contains the entrance point for the Utilities' Unit Test program.
 * It will serve to test the following functions:
 * - Mathematic library.
 *     - Vector math.
 *     - Matrix math.
 *     - Quaternion math.
 *     - Geometric math.
 * - Memory allocation.
 *     - Stack allocator.
 *     - Heap allocator.
 *     - Frame allocator.
 * - File Management.
 *     - Directory.
 *     - File.
 * - Exception.
 * - Logger.
 * - Thread management.
 * - Debug.
 *
 * @date        03-10-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/


//! We use the whole SDK for further testing of the Utilities library.
using namespace HR_SDK;

/*!
 * @brief Defines the Utilities' Unit Test's entrance point
 * @return The result of the execution of the program. 0 is a succesful compilation and execution, Non-zero marks an unsuccesful run.
*/
int main()
{
  HR_SDK::C_Logger UtilitiesLog;  
  
  UtilitiesLog.Init("../externals/Log Files/UtilitiesLog.html");
  UtilitiesLog.AddEntry(MessageLevel::_MESSAGE, "Inicio de proyecto correcto.", HR_FILE, HR_FUNCTION, HR_LINE);

  if (C_PlatformMath::Floor(3.5f) == 3.0f)
  {
	  UtilitiesLog.AddEntry(MessageLevel::_MESSAGE, "Función correcta.", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  else
  {
	  UtilitiesLog.AddEntry(MessageLevel::_ERROR, "Función no entrego el valor deseado", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  if (C_PlatformMath::Round(3.2f) == 3.0f)
  {
	  UtilitiesLog.AddEntry(MessageLevel::_MESSAGE, "Función correcta.", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  else
  {
	  UtilitiesLog.AddEntry(MessageLevel::_ERROR, "Función no entrego el valor deseado", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  if (C_PlatformMath::Ceil(3.2f) == 4.0f)
  {
	  UtilitiesLog.AddEntry(MessageLevel::_MESSAGE, "Función correcta.", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  else
  {
	  UtilitiesLog.AddEntry(MessageLevel::_ERROR, "Función no entrego el valor deseado", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  C_Filestream InputTest(FileAccess::_READ);
  InputTest.Open("../binary/Other Files/HR_ReadTest.txt", false);
 
  Vector<char> Buffer;

  SIZE_T FileSize = InputTest.GetSize();
  Buffer.resize(100);

  InputTest.Read(&Buffer[0], 100);
  
  String strBuffer;
  strBuffer.insert(strBuffer.end(), Buffer.begin(), Buffer.end());

  std::cout << strBuffer;
  std::cin.get();

  if (strBuffer.c_str() != NULL)
  {
	  UtilitiesLog.AddEntry(MessageLevel::_MESSAGE, "Lectura de archivos correcta.", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  else
  {
	  UtilitiesLog.AddEntry(MessageLevel::_ERROR, "Lectura de archivos incorrecta", HR_FILE, HR_FUNCTION, HR_LINE);
  }

  InputTest.Close();
  UtilitiesLog.Close("HRUtilitiesTest");

  return 0;
}