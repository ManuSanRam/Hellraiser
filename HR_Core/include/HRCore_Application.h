#pragma once
#include "HRCore_Prerequisites.h"

/*!************************************************************************************************************************************************************************
*
*	@file		HRCore_Application.h
*
*	This file contains the declaration of class C_Application.
*	This class is used as an interface to create, control and render applications in any platform.
*	The basic functions of this class are:
*	- Initialize: Starts the application, passing any parameters to correctly start up the application.
*	- Update: Updates the application's window and the logic of the application.
*	- 
*
*	@date			26-09-2016
*	@author			Manuel Aldair Santos Ramón (ManuSanRam)
*	@copyright		Infernal Coders S.A.
*
***************************************************************************************************************************************************************************/
/*!************************************************************************************************************************************************************************
 *
 *	@brief Width dimension of the app when initialized as windowed.
 *
***************************************************************************************************************************************************************************/
#define WINDOWED_W		1080

/*!************************************************************************************************************************************************************************
 *
 *	@brief Height dimension of the app when initialized as windowed.
 *
***************************************************************************************************************************************************************************/
#define WINDOWED_H		720

namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	 *
	 *	@brief Declares an application object
	 *
	***********************************************************************************************************************************************************************/
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

		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief This function performs the correct initialization of the application
		 *	Loads any prerequisite necessary for the correct performance of the application
		 *
		*******************************************************************************************************************************************************************/
		virtual void OnInit() = 0;
		
		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief This function performs the update of the app
		 *	Performs the change of state of the application, performs calculations, manages the application's message loop
		 *
		*******************************************************************************************************************************************************************/
		virtual void OnUpdate() = 0;

		/*!
		*/
		virtual void OnResize() = 0;

		/*!
		 *	@brief This function performs the rendering of the app
		 *	Updates the number of viewports used by the application to show anything to screen.
		*/
		virtual void OnRender() = 0;
		
		/*!
		 *	@brief This function performs the shutdown of the app
		 *	Deallocates and destroys any memory resource used by the application, making sure no memory leaks remain and any resource is deallocated
		*/
		virtual void OnDestroy() = 0;
		
		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Initialize the data for an application to run.
		 *	This function, as well as the class, is maintained as virtual for extensibility purposes.
		 *	User can create amy application type;
		 *
		*******************************************************************************************************************************************************************/
	public:
		/*!
		 * @brief Initialize the application
		*/
		void Init();
		
		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Updates the applications data
		 *
		*******************************************************************************************************************************************************************/
		void Update();

		/*!****************************************************************************************************************************************************************
		 * 
		 *	@brief Resizes
		 *
		*******************************************************************************************************************************************************************/
		void Resize();

		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Draws the application to screen
		 *
		*******************************************************************************************************************************************************************/
		void Render();

		/*!
		 * @brief Releases the application's resources and close
		*/
		void Destroy();
	};

	/*!
	 * @brief Global 
	*/
	static C_Application* g_mainApp = nullptr;
}
