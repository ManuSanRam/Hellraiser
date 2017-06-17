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

#include "HRCoreTest_CustomApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	//!
	g_mainApp = new C_CustomApp(false);

	//!
	g_mainApp->Run();

	//!
	delete g_mainApp;
	
	//!
	g_mainApp = nullptr;

	return 0;
}
