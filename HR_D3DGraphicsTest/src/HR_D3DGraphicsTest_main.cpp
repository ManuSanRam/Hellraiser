#include <windows.h>
#include <tchar.h> 
#include <HRUtility_Prerequisites.h>
#include <HRGraphics_Prerequisites.h>

#include <HRGraphics_Graphics.h>

/*!***********************************************************************************************************************************************************
* @file		HRGraphics_Buffer.cpp
*
* This file contains definition of the methods declared inside the buffers' classes.
* The methods implemented in the class are:
* - Setting of the channels individually.
* - Obtaining color structures from another 4D vector to get information from.
* - Obtaining color data from another color.
*
* @date        08-11-2016
* @author		Manuel Aldair Santos Ramón (ManuSanRam)
* @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

using namespace HR_SDK;

#include <windows.h>

const char g_szClassName[] = "DirectX 3D Graphics Unit Test";

#define SCREEN_W  1400
#define SCREEN_H  850

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class----------------------------
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Hellraiser Engine - DirectX 3D Graphics Unit Test.",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_W, SCREEN_H,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Create Graphics
	//C_GraphicsAPI Graphics;
	//// Set Graphics
	//Graphics.InitGraphicsAPI(2, hwnd, SCREEN_W, SCREEN_H, false, FORMAT::RGBA_FLOAT_32, 1);
	//// Create Back buffer RTV from texture
	//C_Texture BackBufferText;
	//
	//Graphics.CreateRTV(&BackBufferText);
	//
	//// Set Viewport
	//Graphics.SetViewport(0, 0, SCREEN_W, SCREEN_H);
	//
	//// Set Input layout
	//	// Create input layout
	//Graphics.SetInputLayout();
	//
	//// Set primitive
	//Vector<S_Vertex> Primitive;
	//S_Vertex V1(C_Vector3D(0.25f, 0.75f, 0.0f), C_LinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	//S_Vertex V2(C_Vector3D(0.5f, 0.25f, 0.0f), C_LinearColor(0.0f, 1.0f, 0.0f, 1.0f));
	//S_Vertex V3(C_Vector3D(0.75f, 0.75f, 0.0f), C_LinearColor(0.0f, 0.0f, 1.0f, 1.0f));
	//
	//Primitive.push_back(V1);
	//Primitive.push_back(V2);
	//Primitive.push_back(V3);
	//
	//Vector<uint32> Indices;
	//Indices.push_back(0);
	//Indices.push_back(1);
	//Indices.push_back(2);
	//
	//Graphics.MapVertices(Primitive, D3D11_USAGE_DYNAMIC, D3D11_BIND_VERTEX_BUFFER);
	//Graphics.MapIndices(Indices, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER);
	

	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	//Graphics.Render();

	//Graphics.CloseGraphicsAPI();

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}