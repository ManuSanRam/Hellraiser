#include "HRCore_Application.h"
#include <Windows.h>

/*!******************************************************************************************************************************************************************************

	@file		HRCore_Application.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the definition of the functions of class C_Application.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date			26-09-2016
	@author			Manuel Aldair Santos Ramón (ManuSanRam)
	@copyright		Infernal Coders S.A.

********************************************************************************************************************************************************************************/



/*!******************************************************************************************************************************************************************************

	@brief Defines optimizations for the Win32 library

********************************************************************************************************************************************************************************/
#define WIN32_LEAN_AND_MEAN



/*!******************************************************************************************************************************************************************************
	
	@brief Message pump for the application's window.
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	@param hwnd Window that receives input for the pump to process
	@param umsg Message to be processed by the pump
	@param wparam wParameter object to process any parameter needed by any function
	@param lparam lParameter object to process any parameter needed by any function
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	@return Event to control the window.

********************************************************************************************************************************************************************************/
static LRESULT CALLBACK wndProc
(
	HWND hwnd, 
	UINT umsg, 
	WPARAM wparam, 
	LPARAM lparam
);



namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	 *
	 *	@brief Structure to control the window where the application will be controlled, viewed and processed.
	 *
	***********************************************************************************************************************************************************************/
	struct C_Application::Window
	{
		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Name of the App
		 *
		*******************************************************************************************************************************************************************/
		String m_AppName;
		
		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Flag to determine if the app will be in fullscreen or windowed.
		 *
		*******************************************************************************************************************************************************************/
		BOOL   m_Fullscreen;

		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Starts up the Win32 window and message loop
		 *
		 *	@param prm_Width Width of the window
		 *	@param prm_Height Height of the window
		 *	@param prm_WindowIndex Index to the window that will be controlled
		 *
		*******************************************************************************************************************************************************************/
		void StartWin
		(
			uint32 &prm_Width, 
			uint32 &prm_Height, 
			uint32 &prm_WindowIndex
		);
		/*!****************************************************************************************************************************************************************
		 *
		 *	@brief Closes Win32 systems and the app data
		 *
		 *	@param WindowIndex Index to the window that will be controlled
		 *
		*******************************************************************************************************************************************************************/
		void StopWin
		(
			uint32 &prm_WindowIndex
		);
	};

	/*!********************************************************************************************************************************************************************
	*
	*	@brief Starts up the Win32 window and message loop
	*
	*	@param prm_Width Width of the window
	*	@param prm_Height Height of the window
	*	@param prm_WindowIndex Index to the window that will be controlled
	*
	***********************************************************************************************************************************************************************/
	void C_Application::Window::StartWin
	(
		uint32 &prm_Width, 
		uint32 &prm_Height, 
		uint32 &prm_WindowIndex
	)
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		//! Window position on screen space
		int32 posX, posY;
		//! Window dimensions on screen space
		uint32 Width, Height;

		// Give the application a name.
		m_AppName = "Hellraiser Engine - Core Unit Test";

		// Setup the windows class with default settings.
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		//wc.hInstance = m_Instance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_AppName.c_str();
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);

		// Determine the resolution of the clients desktop screen.
		Width = GetSystemMetrics(SM_CXSCREEN);
		Height = GetSystemMetrics(SM_CYSCREEN);

		// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
		if (m_Fullscreen)
		{
			// If full screen set the screen to maximum size of the users desktop and 32bit.
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)Width;
			dmScreenSettings.dmPelsHeight = (unsigned long)Height;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Change the display settings to full screen.
			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			// Set the position of the window to the top left corner.
			posX = posY = 0;
		}
		else
		{
			// If windowed then set it to given resolution.
			Width = WINDOWED_W;
			Height = WINDOWED_H;

			// Place the window in the middle of the screen.
			posX = (GetSystemMetrics(SM_CXSCREEN) - Width) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - Height) / 2;
		}

		// Create the window with the screen settings and get the handle to it.
		HWND wind = CreateWindowEx
		(
			WS_EX_APPWINDOW, 
			m_AppName.c_str(),
			m_AppName.c_str(),
			WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, 
			posY, 
			Width, 
			Height, 
			NULL, 
			NULL, 
			NULL, 
			NULL
		);

		SetWindowLong(wind, GWL_STYLE, 0);

		// Bring the window up on the screen and set it as main focus.
		ShowWindow(wind, SW_SHOW);
		SetForegroundWindow(wind);
		SetFocus(wind);

		prm_Width = Width;
		prm_Height = Height;

		prm_WindowIndex = reinterpret_cast<uint32>(wind);

		// Hide the mouse cursor.
		ShowCursor(true);

		return;
	}

	/*!********************************************************************************************************************************************************************
	*
	*	@brief Closes Win32 systems and the app data
	*
	*	@param WindowIndex Index to the window that will be controlled
	*
	***********************************************************************************************************************************************************************/
	void C_Application::Window::StopWin
	(
		uint32 &prm_WindowIndex
	)
	{
		// Show the mouse cursor.
		ShowCursor(true);

		// Fix the display settings if leaving full screen mode.
		if (m_Fullscreen)
		{
			ChangeDisplaySettings(NULL, 0);
		}

		// Remove the window.
		DestroyWindow(reinterpret_cast<HWND>(prm_WindowIndex));
		prm_WindowIndex = NULL;

		// Remove the application instance.
		UnregisterClass(m_AppName.c_str(), GetModuleHandle(0));

		return;
	}


	/*!
	*/
	void C_Application::Run
	(

	)
	{
		MSG msg;
		memset(&msg, 0, sizeof(MSG));
		msg.message = WM_NULL;

		this->Init();

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//! Update app
			this->Update();

			//! Render app
			this->Render();
		}

		//! Deallocate app
		this->Destroy();
	}

	/*!
	 * @brief Initializes the application
	 * Loads any resource needed for the correct start of the app
	*/
	void C_Application::Init
	(

	)
	{
		m_Window = new Window();

		m_WinIndex = 0;
		m_Width = 0;
		m_Height = 0;

		m_AppLogger = nullptr;

		m_Window->StartWin(m_Width, m_Height, m_WinIndex);

		OnInit();
	}

	/*!
	 * @brief Updates the application
	 * Performs calculations, manages message dispatcher and controls the app's main loop
	*/
	void C_Application::Update()
	{
		OnUpdate();
	}

	void C_Application::Resize()
	{
		OnResize();
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

		//! Kill the application´s window
		m_Window->StopWin(m_WinIndex);

		delete m_Window;
	}
}

LRESULT CALLBACK wndProc
(
	HWND hwnd, 
	UINT umsg, 
	WPARAM wparam, 
	LPARAM lparam
)
{
	switch (umsg)
	{
		case WM_SIZE:
		{
			//! Reset the swap chain and back buffer.
			//! Resize the viewport according to wparam .
		}
		break;

		case WM_KEYDOWN:
		{
			if (wparam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);;
			return 0;
		}
		break;

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;

		// All other messages pass to the message handler in the system class.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
	return 0;
}