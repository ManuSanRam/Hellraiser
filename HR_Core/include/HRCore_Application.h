#pragma once

/*!******************************************************************************************************************************************************************************

	@file		HRCore_Application.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of class C_Application.
	This class is used as an interface to create, control and render applications in any platform.

	The basic functions of this class are:
	- Initialize: Starts the application, passes parameters to the app's objects.
	- Update: Updates the app's data.
	- Render: Renders the app's data to the screen.
	- Close: Releases the app's data to the screen.

	The main function is the function Run:
	- Run: This function executes the application, initializing the data, updating it and rendering it's data to screen, and dallocating and destroying data once
		   execution is finished.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date			26-09-2016
	@author			Manuel Aldair Santos Ram�n (ManuSanRam)
	@copyright		Infernal Coders S.A.

********************************************************************************************************************************************************************************/



#include "HRCore_Prerequisites.h"
#include <HRUtility_Logger.h>



/*!******************************************************************************************************************************************************************************

	@def WINDOWED_W
	@brief Width of the app when initialized as windowed.

********************************************************************************************************************************************************************************/
#define WINDOWED_W		1080



/*!******************************************************************************************************************************************************************************

	@def WINDOWED_H
	@brief Height of the app when initialized as windowed.

********************************************************************************************************************************************************************************/
#define WINDOWED_H		720



namespace HR_SDK
{
	/*!**************************************************************************************************************************************************************************
	
		@brief Declares an application object
	
	****************************************************************************************************************************************************************************/
	class HR_CORE_EXPORT C_Application
	{
	public:
		/*!**********************************************************************************************************************************************************************

			@brief 

		************************************************************************************************************************************************************************/
		struct			Window;



		/*!**********************************************************************************************************************************************************************

			@brief

		************************************************************************************************************************************************************************/
		Window*			m_Window;



		/*!**********************************************************************************************************************************************************************

			@brief

		************************************************************************************************************************************************************************/
		uint32			m_WinIndex;
		


		/*!**********************************************************************************************************************************************************************

			@brief

		************************************************************************************************************************************************************************/
		uint32			m_Width;
		


		/*!**********************************************************************************************************************************************************************

			@brief

		************************************************************************************************************************************************************************/
		uint32			m_Height;



		/*!**********************************************************************************************************************************************************************

			@brief

		************************************************************************************************************************************************************************/
		C_Logger*		m_AppLogger;



		/*!**********************************************************************************************************************************************************************

			@brief

		************************************************************************************************************************************************************************/
		void Run();



		/*!**********************************************************************************************************************************************************************
		
			@brief This function performs the correct initialization of the application
			Loads any prerequisite necessary for the correct performance of the application
		
		************************************************************************************************************************************************************************/
		virtual void OnInit() = 0;
		


		/*!**********************************************************************************************************************************************************************
		
			@brief This function performs the update of the app
			Performs the change of state of the application, performs calculations, manages the application's message loop
		
		************************************************************************************************************************************************************************/
		virtual void OnUpdate() = 0;



		/*!**********************************************************************************************************************************************************************

			@brief This function performs the update of the app
			Performs the change of state of the application, performs calculations, manages the application's message loop

		************************************************************************************************************************************************************************/
		virtual void OnResize() = 0;



		/*!**********************************************************************************************************************************************************************

			@brief This function performs the rendering of the app
			Updates the number of viewports used by the application to show anything to screen.
		
		************************************************************************************************************************************************************************/
		virtual void OnRender() = 0;
		


		/*!**********************************************************************************************************************************************************************

			@brief This function performs the shutdown of the app
			Deallocates and destroys any memory resource used by the application, making sure no memory leaks remain and any resource is deallocated
		
		************************************************************************************************************************************************************************/
		virtual void OnDestroy() = 0;
		


		/*!**********************************************************************************************************************************************************************
		
			@brief Initialize the data for an application to run.
			This function, as well as the class, is maintained as virtual for extensibility purposes.
			User can create amy application type;
		
		************************************************************************************************************************************************************************/
	public:



		/*!**********************************************************************************************************************************************************************
			
			@brief Initialize the application
		
		************************************************************************************************************************************************************************/
		void Init();
		


		/*!**********************************************************************************************************************************************************************
		
			@brief Updates the applications data
		
		************************************************************************************************************************************************************************/
		void Update();



		/*!**********************************************************************************************************************************************************************
		
			@brief Resizes the rendering area of the data
		
		************************************************************************************************************************************************************************/
		void Resize();



		/*!**********************************************************************************************************************************************************************
		
			@brief Draws the application to screen
		
		************************************************************************************************************************************************************************/
		void Render();



		/*!**********************************************************************************************************************************************************************

			@brief Releases the application's resources and closes
		
		************************************************************************************************************************************************************************/
		void Destroy();
	};



	/*!**************************************************************************************************************************************************************************

		@brief Global pointer used to access certain data
	
	****************************************************************************************************************************************************************************/
	static C_Application* g_mainApp = nullptr;
}
