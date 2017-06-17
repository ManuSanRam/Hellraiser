#pragma once
#include "HRCore_Prerequisites.h"

/*!***********************************************************************************************************************************************************
* @file		HRGraphics_Buffer.h
*
* This file contains the Color class declaration, for mathematical operations to get colors and control the data on them.
* The methods implemented in the class are:
* - Setting of the channels individually.
* - Obtaining color structures from another 4D vector to get information from.
* - Obtaining color data from another color.
*
* @date        26-09-2016
* @author		Manuel Aldair Santos Ramón (ManuSanRam)
* @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

#define WINDOWED_W		1366
#define WINDOWED_H		768

namespace HR_SDK
{
	/*!
	 * @brief Declares an application object
	*/
	class HR_CORE_EXPORT C_Application
	{
	public:
		/*!
		*/
		struct Window;

		Window* m_Window;

		uint32 m_WinIndex;
		uint32 m_Width;
		uint32 m_Height;
		
		/*!
		*/
		void Run();

		/*!
		 * @brief This function performs the correct initialization of the application
		 * Loads any prerequisite necessary for the correct performance of the app
		*/
		virtual void OnInit() = 0;
		
		/*!
		 * @brief This function performs the update of the app
		 * Performs the change of state of the application, performs calculations, manages the app's message loop
		*/
		virtual void OnUpdate() = 0;

		/*!
		*/
		virtual void OnResize() = 0;

		/*!
		 * @brief This function performs the rendering of the app
		 * Updates the number of viewports used by the app to show anything to screen.
		*/
		virtual void OnRender() = 0;
		
		/*!
		 * @brief This function performs the shutdown of the app
		 * Deallocates and destroys any memory resource used by the app, making sure no memory leaks remain and any resource is deallocated
		*/
		virtual void OnDestroy() = 0;
		
		/*!
		 * @brief Initialiase the data for an application to run.
		 * This function, as well as the class, is maintained as virtual for extensebility purposes.
		 * User can create amy application type;
}
		*/
	public:
		void Init();
		/*!
		 @brief Updates the applications data
		*/
		void Update(bool &prm_Stop);

		void Resize();

		/*!
		*/
		void Render();
		/*!
		*/
		void Destroy();
	};

	static C_Application* g_mainApp = nullptr;
}
