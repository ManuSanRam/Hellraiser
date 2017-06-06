#include "HRCoreTest_CustomApp.h"

struct Window
{
	uint32 m_Window;
	LPCSTR m_AppName;
	BOOL   m_Fullscreen;

	uint32 m_Width;
	uint32 m_Height;

	/*!
	@brief Starts up the Win32 window and message loop
	*/
	void StartWin();
	/*!
	@brief Closes Win32 systems and the app data
	*/
	void StopWin();
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
};

/*!***********************************************************************************************************
* @file		HRCoreTest_CustomApp.cpp
* 
*************************************************************************************************************/
void C_CustomApp::Run()
{
	//! While the main loop is still running
	while (this->Update())
	{
		//! Render stuff to the screen
		this->Render();
	}
}

void Window::StartWin()
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get an external pointer to this object.	
	//ApplicationHandle = this;

	// Give the application a name.
	m_AppName = "HELLRAISER GAME ENGINE - Core Project Unit Test";

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
	wc.lpszClassName = m_AppName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	m_Width = GetSystemMetrics(SM_CXSCREEN);
	m_Height = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (m_Fullscreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_Width;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_Height;
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
		m_Width = WINDOWED_W;
		m_Height = WINDOWED_H;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_Width) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_Height) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	HWND wind = CreateWindowEx(WS_EX_APPWINDOW, m_AppName, m_AppName,
		WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, m_Width, m_Height, NULL, NULL, NULL, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(wind, SW_SHOW);
	SetForegroundWindow(wind);
	SetFocus(wind);

	m_Window = reinterpret_cast<uint32>(wind);

	// Hide the mouse cursor.
	ShowCursor(true);

	return;
}

void Window::StopWin()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (m_Fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(reinterpret_cast<HWND>(m_Window));
	m_Window = NULL;

	// Remove the application instance.
	UnregisterClass(m_AppName, GetModuleHandle(0));

	// Release the pointer to this class.
	//ApplicationHandle = NULL;

	return;
}

void C_CustomApp::OnInit()
{
	m_Window = new Window();
	m_Window->StartWin();

	m_GraphicsLogger = new C_Logger();
	m_GraphicsLogger->Init("../externals/Log Files/CoreTestLog.html");
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Aplicación iniciada con exito", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Set Pipeline
	//! Start-up Direct 3D
	m_Graphics = new C_GraphicsAPI();
	if (m_Graphics->Init(m_Window->m_Width, m_Window->m_Height, DXGI_Formats::RGBA_8_UNORM, DXGI_Scanlines::UNSPECIFIED, DXGI_Scaling::UNSPECIFIED, DXGI_Usage::RENDER_TARGET_OUTPUT, m_Window->m_Window, m_Fullscreen, DXGI_SwapEffect::DISCARD, D3D_Drivers::HARDWARE))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Pipeline grafico cargado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_FATAL_ERROR, "Pipeline grafico no se pudo cargar", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		//this->OnDestroy();
		exit(1);
	}

	//! Create Back buffer (Render Target View)
	m_BackBuffer = new C_Texture();
	if (m_BackBuffer->CreateAsRTV(m_Graphics->m_Device, m_Graphics->m_SwapChain))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Back buffer creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_FATAL_ERROR, "Back buffer no se pudo crear", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create Depth stencil
	m_Depth = new C_DepthStencil();
	if (m_Depth->CreateDSBuffer(m_Window->m_Width, m_Window->m_Height, DXGI_Formats::D_24_UNORM_S8_UINT, D3D_Usages::DEFAULT, D3D_Binds::DEPTH_STENCIL, m_Graphics->m_Device))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Buffer de profundidad creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_FATAL_ERROR, "Buffer de profundidad no se pudo crear", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	if (m_Depth->CreateDSView(m_Graphics->m_Device, m_Graphics->m_DC, DXGI_Formats::D_24_UNORM_S8_UINT))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Depth Stencil View creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_FATAL_ERROR, "No se pudo crear Depth Stencil View", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	m_BackBuffer->SetRTV(m_Graphics->m_DC, 1, m_Depth->m_DSV);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Render Target View configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	
	//! Init geometry to be drawn...
	//! Compile the shaders...
	m_VShader = new C_VertexShader();
	m_PShader = new C_PixelShader();
	if (m_VShader->Compile("../externals/Shader Files/BasicVS.hlsl", "VSMain", "vs_5_0"))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Shader de vertices compilado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo compilar shader de vertices", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	if (m_PShader->Compile("../externals/Shader Files/BasicVS.hlsl", "PSMain", "ps_5_0"))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Shader de pixeles compilado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo compilar el shader de pixeles", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	if (m_VShader->Create(m_Graphics->m_Device))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Shader de vertices creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo crear shader de vertices", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	if (m_PShader->Create(m_Graphics->m_Device))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Shader de pixeles creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo crear shader de pixeles", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	m_VShader->Set(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Vertex Shader configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	m_PShader->Set(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Pixel Shader configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Set vertex information
	m_SquareMesh = new C_TestMesh();

	if (m_SquareMesh->CreateIndexB(m_Graphics->m_Device))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Buffer de indices creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se puede crear buffer de indices", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	m_SquareMesh->SetIB(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Buffer de indices configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	if (m_SquareMesh->CreateVertexB(m_Graphics->m_Device))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Buffer de vertices creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo crear buffer", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	m_SquareMesh->SetVB(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Buffer de vertices configurado", HR_FILE, HR_FUNCTION, HR_LINE);
	
	//!Create input layout
	m_InputLayout = new C_InputLayout();
	m_InputLayout->AddInput("POSITION", 0, DXGI_Formats::RGB_32_FLOAT, 0);
	m_InputLayout->AddInput("COLOR", 0, DXGI_Formats::RGBA_32_FLOAT, D3D11_APPEND_ALIGNED_ELEMENT);
	if (m_InputLayout->CreateInputLayout(m_Graphics->m_Device, m_VShader->m_Blob))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Input layout creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo crear el input layout", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	m_InputLayout->SetInputLayout(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Input layout configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	m_SquareMesh->SetTopology(m_Graphics->m_DC, D3D_Topologies::TRIANGLE_LIST);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Topologia de primitiva configurada", HR_FILE, HR_FUNCTION, HR_LINE);

	m_Viewport = new C_Viewport();
	m_Viewport->Create(0, 0, m_Window->m_Width, m_Window->m_Height, 0.0f, 1.0f);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Viewport creado", HR_FILE, HR_FUNCTION, HR_LINE);
	m_Viewport->Set(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Viewport configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Graficos cargados con exito... Listo para dibujar", HR_FILE, HR_FUNCTION, HR_LINE);
	
	//! Create world space constant buffer
	m_WrldBuffer = new C_ConstantBuffer();
	if (m_WrldBuffer->Create(m_Graphics->m_Device, 1, D3D_Binds::CONST_BUFFER, D3D_Access::WRITE, D3D_Usages::DYNAMIC, sizeof(C_Matrix4)))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Constant buffer de mundo creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de mundo", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create view space constant buffer
	m_ViewBuffer = new C_ConstantBuffer();
	if(m_ViewBuffer->Create(m_Graphics->m_Device, 1, D3D_Binds::CONST_BUFFER, D3D_Access::WRITE, D3D_Usages::DYNAMIC, sizeof(C_Matrix4)))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Constant buffer de mundo creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de mundo", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create projection space constant buffer
	m_ProjBuffer = new C_ConstantBuffer();
	if(m_ProjBuffer->Create(m_Graphics->m_Device, 1, D3D_Binds::CONST_BUFFER, D3D_Access::WRITE, D3D_Usages::DYNAMIC, sizeof(C_Matrix4)))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Constant buffer de mundo creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de mundo", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create the camera
	m_StaticCamera = new C_GCamera();

	/*!
	 * Set the camera's data 
	*/
	//! Position
	m_StaticCamera->SetPosition
	(
		C_Vector3D(0.0f, 0.0f, 0.1f)
	);
	//! Target
	m_StaticCamera->SetTarget
	(
		C_Vector3D(1.0f, 0.0f, 0.0f)
	);
	//! Up vector
	m_StaticCamera->SetUp
	(
		C_Vector3D(0.0f, 1.0f, 0.0f)
	);
}

bool C_CustomApp::OnUpdate()
{
	MSG msg;

	// Handle the windows messages.
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	/*!
		If user kills window, closes window
	*/
	if (msg.message == WM_QUIT)
	{
		//! Stop updating the window and get the fuck out
		return false;
	}

	//! Return true = Keep updating main loop
	return true;
}

void C_CustomApp::OnRender()
{
	/*!
		Color on the screen...
	*/
	C_LinearColor Color;

	Color.SetRed(0.0f);
	Color.SetGreen(0.0f);
	Color.SetBlue(0.0f);
	Color.SetAlpha(1.0f);

	m_BackBuffer->ClearRTV(m_Graphics->m_DC, Color);

	m_Depth->ClearDSV(m_Graphics->m_DC);

	//! Set world matrix
	C_Matrix4 World;
	World.Identity();

	//! Pass world matrix to constant buffer
	m_WrldBuffer->Map(m_Graphics->m_DC, &World, sizeof(C_Matrix4));
	m_WrldBuffer->Set(m_Graphics->m_DC, 0, 1);

	//! Get view and projection matrices from camera
	m_StaticCamera->LookAt();
	C_Matrix4 View = m_StaticCamera->m_View;
	View.Transpose();

	//! Get matrices
	m_StaticCamera->Projection(0.4 * C_PlatformMath::m_Pi, (float)m_Window->m_Width/m_Window->m_Height, 1.0f, 1000.0f);
	C_Matrix4 Proj = m_StaticCamera->m_Projection;
	Proj.Transpose();

	//! Pass data to respective constant buffers
	m_ViewBuffer->Map(m_Graphics->m_DC, &View, sizeof(C_Matrix4));
	m_ViewBuffer->Set(m_Graphics->m_DC, 1, 1);

	//! Pass view and projection matrices to the constant buffer
	m_ProjBuffer->Map(m_Graphics->m_DC, &Proj, sizeof(C_Matrix4));
	m_ProjBuffer->Set(m_Graphics->m_DC, 2, 1);

	//! Render your shit here...
	m_SquareMesh->Draw(m_Graphics->m_DC);

	m_Graphics->Present();
}

void C_CustomApp::OnDestroy()
{
	/*!
	Shutdown Graphics API
	*/
	m_Graphics->Close();
	delete m_Graphics;
	m_Graphics = NULL;

	m_BackBuffer->Close();
	delete m_BackBuffer;
	m_BackBuffer = NULL;

	delete m_SquareMesh;
	m_SquareMesh = NULL;

	m_VShader->Close();
	delete m_VShader;
	m_VShader = NULL;

	m_PShader->Close();
	delete m_PShader;
	m_PShader = NULL;

	m_InputLayout->Close();
	delete m_InputLayout;
	m_InputLayout = NULL;

	m_Depth->Close();
	delete m_Depth;
	m_Depth = NULL;

	/*delete m_WrldBuffer;
	m_WrldBuffer = NULL;

	delete m_ViewBuffer;
	m_ViewBuffer = NULL;

	delete m_ProjBuffer;
	m_ProjBuffer = NULL;
	*/
	/*!
		Kill the application´s window
	*/
	m_Window->StopWin();
	delete m_Window;

	m_GraphicsLogger->Close("HR_CoreTestLogger");
	delete m_GraphicsLogger;
}

LRESULT CALLBACK Window::wndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
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
