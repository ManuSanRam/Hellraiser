#include "HRCore_Application.h"

/*!***********************************************************************************************************************************************************
* @file		HRCore_Application.cpp
*
* This file contains the definition of the functions of the C_Application class
* The function implementations are as follows:
*   - Initialize any resource used by any custom application.
*   - Updates any message used by said application.
*   - Renders the application's rect to screen.
*   - Deallocates and frees any memory used by the application.
*
* @date         26-09-2016
* @author		Manuel Aldair Santos Ramón (ManuSanRam)
* @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

namespace HR_SDK
{
	/*!
	 * @brief Initializes the application
	 * Loads any resource needed for the correct start of the app
	*/
	void C_Application::Init()
	{
		OnInit();
	}

	/*!
	 * @brief Updates the application
	 * Performs calculations, manages message dispatcher and controls the app's main loop
	*/
	bool C_Application::Update()
	{
		return OnUpdate();
	}

	/*!
	 * @brief Renders the application to screen
	 * Renders the app's main rect and all the information used by it into the screen
	*/
	void C_Application::Render()
	{
		OnRender();
	}

	/*!
	 * @brief Destroys any memory used by the application
	*/
	void C_Application::Destroy()
	{
		OnDestroy();
	}
}