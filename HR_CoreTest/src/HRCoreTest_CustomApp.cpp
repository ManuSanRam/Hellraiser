#include "HRCoreTest_CustomApp.h"

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

void C_CustomApp::OnInit()
{
	//! Allocate the log file
	m_GraphicsLogger = new C_Logger();
	//! Open file prepare to receive logging messages
	m_GraphicsLogger->Init("Log Files/CoreTestLog.html");
	//! Report message to log file.
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Application successfully initialized", HR_FILE, HR_FUNCTION, HR_LINE);

	/*!********************************************************************************************************************************************************************
	 *
	 *	INITIALIZE THE PIPELINE
	 *
	***********************************************************************************************************************************************************************/
	//! Allocate the graphics API
	m_Graphics = new C_GraphicsAPI();
	//! Create the COM objects for the pipeline
	if (m_Graphics->Init(m_Width, m_Height, DXGI_Formats::RGBA_8_UNORM, DXGI_Scanlines::UNSPECIFIED, DXGI_Scaling::UNSPECIFIED, DXGI_Usage::RENDER_TARGET_OUTPUT, m_WinIndex, m_Fullscreen, DXGI_SwapEffect::DISCARD, D3D_Drivers::HARDWARE))
	{
		//! COM objects created successfully: report message to log file.
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Graphics pipeline successfully initialized", HR_FILE, HR_FUNCTION, HR_LINE);
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
	if (m_Depth->CreateDSBuffer(m_Width, m_Height, DXGI_Formats::D_24_UNORM_S8_UINT, D3D_Usages::DEFAULT, D3D_Binds::DEPTH_STENCIL, m_Graphics->m_Device))
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

	C_Texture* Texture = new C_Texture();
	if (Texture->CreateFromFile("Texture Files/GowLogo.png", m_Graphics->m_Device, m_Graphics->m_DC))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Textura creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		delete Texture;
		m_GraphicsLogger->AddEntry(MessageLevel::_FATAL_ERROR, "No se pudo crear la textura", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	Texture->Close();
	delete Texture;

	
	/*!********************************************************************************************************************************************************************
	 *
	 *	INITIALIZE GEOMETRY TO BE RENDERED
	 *
	***********************************************************************************************************************************************************************/
	//! Allocate vertex shader
	m_VShader = new C_VertexShader();
	//! Allocate pixel shader
	m_PShader = new C_PixelShader();

	//! Comile th vertex shader using specified file
	if (m_VShader->Compile("Shader Files/BasicVS.hlsl", "VSMain", "vs_5_0"))
	{
		//! Shader compilation succedeed: report to log file.
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Shader de vertices compilado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
		//! Continue the program
	}

	else
	{
		//! Shader compilation failed: report to log file.
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "No se pudo compilar shader de vertices", HR_FILE, HR_FUNCTION, HR_LINE);
		//! Write information to file, close file
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		//! Stop the program reporting an error
		exit(1);
	}

	if (m_PShader->Compile("Shader Files/BasicVS.hlsl", "PSMain", "ps_5_0"))
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
	m_Viewport->Create(0, 0, m_Width, m_Height, 0.0f, 1.0f);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Viewport creado", HR_FILE, HR_FUNCTION, HR_LINE);
	m_Viewport->Set(m_Graphics->m_DC);
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Viewport configurado", HR_FILE, HR_FUNCTION, HR_LINE);

	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Graficos cargados con exito... Listo para dibujar", HR_FILE, HR_FUNCTION, HR_LINE);
	
	//! Create world space constant buffer
	m_WrldBuffer = new C_ConstantBuffer();
	if (m_WrldBuffer->Create(m_Graphics->m_Device, D3D_Binds::CONST_BUFFER, D3D_Access::NONE, D3D_Usages::DEFAULT, sizeof(C_Matrix4)))
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
	if(m_ViewBuffer->Create(m_Graphics->m_Device, D3D_Binds::CONST_BUFFER, D3D_Access::NONE, D3D_Usages::DEFAULT, sizeof(C_Matrix4)))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Constant buffer de vista creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de vista", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create projection space constant buffer
	m_ProjBuffer = new C_ConstantBuffer();
	if(m_ProjBuffer->Create(m_Graphics->m_Device, D3D_Binds::CONST_BUFFER, D3D_Access::NONE, D3D_Usages::DEFAULT, sizeof(C_Matrix4)))
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Constant buffer de proyeccion creado con exito", HR_FILE, HR_FUNCTION, HR_LINE);
	}

	else
	{
		m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);
		m_GraphicsLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create the camera
	m_StaticCamera = new C_GCamera();
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	/*!
	 * Set the camera's data 
	*/
	//! Position
	m_StaticCamera->SetPosition
	(
		C_Vector3D(0.0f, 0.0f, -60.0f)
	);
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Target
	m_StaticCamera->SetTarget
	(
		C_Vector3D(0.0f, 0.0f, 0.0f)
	);
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Up vector
	m_StaticCamera->SetUp
	(
		C_Vector3D(0.0f, 1.0f, 0.0f)
	);
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);
}

void C_CustomApp::OnUpdate()
{
	RotationFactor += 0.0005f;
	if (RotationFactor > C_PlatformMath::m_Two_Pi)
	{
		RotationFactor = 0.00f;
	}

	C_Matrix4 Rotation, RotX, RotY, RotZ, Scalation, Translation;

	World.Identity();

	Scalation.Scale(15.0f, 15.0f, 15.0f);

	RotX.RotateX(RotationFactor, true);
	RotY.RotateY(RotationFactor, true);
	RotZ.RotateZ(RotationFactor, true);
	
	Rotation = RotX * RotY;

	Translation.Translate(0.0f, 0.0f, 0.0f);

	World = Scalation * Rotation * Translation;
	World.Transpose();
}

void C_CustomApp::OnResize()
{

}

void C_CustomApp::OnRender()
{
	/*!
		Color on the screen...
	*/
	C_LinearColor Color;

	Color.SetRed(0.0f);
	Color.SetGreen(0.2f);
	Color.SetBlue(0.46f);
	Color.SetAlpha(1.0f);

	m_BackBuffer->ClearRTV(m_Graphics->m_DC, Color);

	m_Depth->ClearDSV(m_Graphics->m_DC);

	//! Set world matrix

	m_WrldBuffer->Map(m_Graphics->m_DC, &World, sizeof(C_Matrix4));
	m_WrldBuffer->Set(m_Graphics->m_DC, 0, 1);

	//! Get view and projection matrices from camera
	m_StaticCamera->LookAt();
	View = m_StaticCamera->m_View;
	View.Transpose();

	m_ViewBuffer->Map(m_Graphics->m_DC, &View, sizeof(C_Matrix4));
	m_ViewBuffer->Set(m_Graphics->m_DC, 1, 1);

	float Ratio = (float)m_Width / (float)m_Height;

	//! Get matrices
	m_StaticCamera->Projection(0.4f * C_PlatformMath::m_Pi, Ratio, CAMERA_NEAR, CAMERA_FAR);
	Proj = m_StaticCamera->m_Projection;
	Proj.Transpose();

	m_ProjBuffer->Map(m_Graphics->m_DC, &Proj, sizeof(C_Matrix4));
	m_ProjBuffer->Set(m_Graphics->m_DC, 2, 1);

	//! Render your shit here...
	m_SquareMesh->Draw(m_Graphics->m_DC);

	m_Graphics->Present();
}

void C_CustomApp::OnDestroy()
{
	//! Close the back buffer render target 
	m_BackBuffer->Close();
	//! Deallocate back buffer
	delete m_BackBuffer;
	//! Point back buffer to null
	m_BackBuffer = NULL;
	//! Report 
	m_GraphicsLogger->AddEntry(MessageLevel::_MESSAGE, "Back buffer cerrado con exito", HR_FILE, HR_FUNCTION, HR_LINE);

	//!
	m_Graphics->Close();
	delete m_Graphics;
	m_Graphics = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//!
	delete m_SquareMesh;
	m_SquareMesh = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//!
	m_VShader->Close();
	delete m_VShader;
	m_VShader = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//!
	m_PShader->Close();
	delete m_PShader;
	m_PShader = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//!
	m_InputLayout->Close();
	delete m_InputLayout;
	m_InputLayout = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Close the depth
	m_Depth->Close();
	delete m_Depth;
	m_Depth = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Close the world matrix
	delete m_WrldBuffer;
	m_WrldBuffer = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Close the view matrix
	delete m_ViewBuffer;
	m_ViewBuffer = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	//! Close the projection matrix
	delete m_ProjBuffer;
	m_ProjBuffer = NULL;
	m_GraphicsLogger->AddEntry(MessageLevel::_ERROR, "Error al crear constant buffer de proyeccion", HR_FILE, HR_FUNCTION, HR_LINE);

	m_GraphicsLogger->Close("HR_CoreTestLogger");
	delete m_GraphicsLogger;
}


