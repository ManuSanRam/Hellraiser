/*!
*/

#include "HRCoreTest_CustomApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	g_mainApp = new C_CustomApp(false);

	g_mainApp->Run();

	delete g_mainApp;
	g_mainApp = nullptr;

	return 0;
}
