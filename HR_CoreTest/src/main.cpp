#include "HRCoreTest_CustomApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	C_CustomApp* App = new C_CustomApp(false);

	App->Run();

	delete App;

	App = NULL;

	return 0;
}