#include "HRCoreTest_CustomApp.h"

/*!******************************************************************************************************************************************************************************

	@file		HRCore_Application.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of class C_Application.
	This class is used as an interface to create, control and render applications in any platform.
	The basic functions of this class are:
	- Initialize: Starts the application, passing any parameters to correctly start up the application.
	- Update: Updates the application's window and the logic of the application.
	- Render:
	- Close:

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date			26-09-2016
	@author			Manuel Aldair Santos Ramón (ManuSanRam)
	@copyright		Infernal Coders S.A.

********************************************************************************************************************************************************************************/


/*!******************************************************************************************************************************************************************************

	@brief Initialize every object for the app.

********************************************************************************************************************************************************************************/
void C_CustomApp::OnInit()
{
	//! Allocate the log file
	m_AppLogger = new C_Logger();



	//! Open file prepare to receive logging messages
	m_AppLogger->Init("Log Files/CoreTestLog.html");



	//! Report message to log file.
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Application successfully initialized",
		HR_FILE,
		HR_FUNCTION,
		HR_LINE
	);



	/// Graphics pipeline ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate the graphics object
	m_Graphics = new C_GraphicsAPI();

	if(m_Graphics->Init(m_Width,m_Height,DXGI_Formats::RGBA_8_UNORM,DXGI_Scanlines::UNSPECIFIED,DXGI_Scaling::UNSPECIFIED,DXGI_Usage::RENDER_TARGET_OUTPUT,m_WinIndex,m_Fullscreen,DXGI_SwapEffect::DISCARD,D3D_Drivers::HARDWARE))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Successful pipeline initializing",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR, 
			"Error initializing pipeline", 
			HR_FILE, 
			HR_FUNCTION, 
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	/// Back buffer /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate render target object to operate on it
	m_BackBuffer = new C_RenderTarget();

	//! Create the back buffer's render target ----------------------------------------------------------------------------------------------------------------------------------
	if(m_Graphics->CreateRenderTarget(m_BackBuffer))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Back buffer created", 
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error creating the back buffer",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	/// Depth-stencil ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate depth stencil for use
	m_Depth = new C_DepthStencil();

	if(m_Graphics->CreateDepthStencil(m_Width,m_Height,DXGI_Formats::D_24_UNORM_S8_UINT,D3D_Usages::DEFAULT,D3D_Binds::DEPTH_STENCIL,m_Depth))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Depth-stencil created",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error creating the depth-stencil",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set the render target as active -----------------------------------------------------------------------------------------------------------------------------------------
	if(m_Graphics->SetRenderTarget(1,m_Depth,m_BackBuffer))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Back buffer set",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error setting the back buffer",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	

	/// Vertex shader ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate pointer for use
	m_VShader = new C_VertexShader();

	//! Create vertex shader
	if(m_Graphics->CreateVertexShader("Shader Files/BasicVS.hlsl","VSMain","vs_5_0",m_VShader))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Vertex shader created",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error creating the vertex shader",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set vertex shader
	if(m_Graphics->SetVertexShader(m_VShader))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Vertex shader set",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error setting the vertex shader",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Pixel shader ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate pointer for use
	m_PShader = new C_PixelShader();

	//! Create pixel shader
	if(m_Graphics->CreatePixelShader("Shader Files/BasicVS.hlsl","PSMain","ps_5_0",m_PShader))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Pixel shader created",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error creating the pixel shader",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set pixel shader
	if(m_Graphics->SetPixelShader(m_PShader))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Pixel shader set",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error setting the pixel shader",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Geometry ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate mesh for use
	m_SquareMesh = new C_TestMesh();

	//! Create the index buffer from mesh
	if(m_SquareMesh->CreateIndexB(m_Graphics->m_Device))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Test mesh's index buffer loaded",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error loading test mesh's index buffer",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create the index buffer into the pipeline
	if (m_Graphics->CreateIndexBuffer(D3D_Access::NONE, D3D_Usages::DEFAULT, m_SquareMesh->m_SolidIB))
	{
		//! Successful setting of the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as a normal message
			"Vertex buffer created",			//! Message clarify
			HR_FILE,							//! File where it was made
			HR_FUNCTION,						//! 
			HR_LINE
		);
	}

	else
	{
		//! Successful setting of the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as a normal message
			"Vertex buffer created",			//! Message clarify
			HR_FILE,							//! File where it was made
			HR_FUNCTION,						//! 
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set the index buffer
	if(m_Graphics->SetIndexBuffer(DXGI_Formats::R_32_UINT, m_SquareMesh->m_SolidIB))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Index buffer created",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error creating index buffer",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create vertex buffer from mesh
	if (m_SquareMesh->CreateVertexB(m_Graphics->m_Device))
	{
		//! Successful setting of the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as a normal message
			"Vertex buffer created",			//! Message clarify
			HR_FILE,							//! File where it was made
			HR_FUNCTION,						//! 
			HR_LINE
		);
	}

	//! 
	else
	{
		//! Successful setting of the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as a normal message
			"Vertex buffer created",			//! Message clarify
			HR_FILE,							//! File where it was made
			HR_FUNCTION,						//! 
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Create the vertex buffer
	if (m_Graphics->CreateVertexBuffer(D3D_Access::NONE, D3D_Usages::DEFAULT, m_SquareMesh->m_SolidVB))
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,
			"Vertex buffer created",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);
	}

	//! 
	else
	{
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,
			"Error creating vertex buffer",
			HR_FILE,
			HR_FUNCTION,
			HR_LINE
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set the vertices
	if(m_Graphics->SetVertexBuffer(m_SquareMesh->m_SolidVB))
	{
		//! Successful setting of the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as a normal message
			"Vertex buffer created",			//! Message clarify
			HR_FILE,							//! File where it was made
			HR_FUNCTION,						//! 
			HR_LINE
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Input Layout ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_InputLayout = new C_InputLayout();

	m_InputLayout->Init();

	//! Add the inputs of the input layout
	m_InputLayout->AddInput("POSITION",	0,	DXGI_Formats::RGBA_32_FLOAT,		0);
	m_InputLayout->AddInput("TEXCOORD",	0,	DXGI_Formats::RG_32_FLOAT,			16);

	//! Create the input layout
	if (m_Graphics->CreateInputLayout(m_VShader, m_InputLayout))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Input layout created successfully",//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating the input layout",	//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set the input layout
	if (m_Graphics->SetInputLayout(m_InputLayout))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Input layout set successfully",	//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error setting input layout",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Viewport ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Viewport = new C_Viewport();
	
	//! Create viewport
	if (m_Graphics->CreateViewport(0, 0, m_Width, m_Height, 0.0F, 1.0F, m_Viewport))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Viewport created successfully",	//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating viewport",			//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	//! Set viewport
	if (m_Graphics->SetViewport(m_Viewport))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Viewport set successfully",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error setting viewport",			//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Topology ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Graphics->SetTopology(D3D_Topologies::TRIANGLE_LIST);



	/// Camera //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Camera = new C_GCamera();

	m_Camera->SetPosition(0.0f, 0.0f, -40.0f);

	m_Camera->SetUp(0.0f, 1.0f, 0.0f);

	m_Camera->SetTarget(0.0f, 0.0f, 0.0f);



	/// Constant buffer /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! Allocate buffers
	m_WrldBuffer = new C_ConstantBuffer();
	m_ViewBuffer = new C_ConstantBuffer();
	m_ProjBuffer = new C_ConstantBuffer();

	//! Create constant buffers
	if (m_Graphics->CreateConstantBuffer(D3D_Access::NONE, D3D_Usages::DEFAULT, sizeof(C_Matrix4), m_WrldBuffer))	/// WORLD MATRIX BUFFER -------------------------------------
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	if (m_Graphics->CreateConstantBuffer(D3D_Access::NONE, D3D_Usages::DEFAULT, sizeof(C_Matrix4), m_ViewBuffer))	/// VIEW MATRIX BUFFER ----------------------------------------------
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}

	if (m_Graphics->CreateConstantBuffer(D3D_Access::NONE, D3D_Usages::DEFAULT, sizeof(C_Matrix4), m_ProjBuffer))	/// PROJECTION MATRIX BUFFER ----------------------------------------
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating vertex buffer",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Texture -----------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_Texture = new C_Texture();

	//! Load textures
	if (m_Graphics->CreateTexture("Texture Files/GoWLogo.png", DXGI_Formats::RGBA_8_UNORM, m_Texture))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"Texture buffer created successfully",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating texture buffer",	//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Shader resource view ----------------------------------------------------------------------------------------------------------------------------------------------------
	m_ShdResourceView = new C_ShaderResource();

	//! Create shader resource view
	if (m_Graphics->CreateShaderResourceView(DXGI_Formats::RGBA_8_UNORM, m_Texture, m_ShdResourceView))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,				//! Classify as fatal error
			"SRV created successfully",			//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Error creating SRV",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Sampler -----------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_Sampler = new C_Sampler();
	
	//! Create sampler state
	if (m_Graphics->CreateSampler(m_Sampler))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,			//! Classify as fatal error
			"Sampler created successfully",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,			//! Classify as fatal error
			"Sampler created successfully",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}



	/// Rasterizer --------------------------------------------------------------------------------------------------------------------------------------------------------------
	m_Raster = new C_Rasterizer();
	
	//! Create rasterizer
	if (m_Graphics->CreateRasterizer(D3D_FillModes::SOLID, D3D_CullModes::FRONT, m_Raster))
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_MESSAGE,			//! Classify as fatal error
			"Rasterizer created successfully",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);
	}

	else
	{
		//! An error was encountered setting the vertex buffer
		m_AppLogger->AddEntry
		(
			MessageLevel::_FATAL_ERROR,			//! Classify as fatal error
			"Rasterizer created successfully",		//! Message clarify
			HR_FILE,							//! Which file
			HR_FUNCTION,						//! Which function
			HR_LINE								//! Which line
		);

		m_AppLogger->Close("HR_CoreTestLogger");
		exit(1);
	}
}



/*!******************************************************************************************************************************************************************************

	@brief Update the app's data.

********************************************************************************************************************************************************************************/
void C_CustomApp::OnUpdate()
{
	RotationFactor += 0.0005f;
	if (RotationFactor > C_PlatformMath::m_Two_Pi)
	{
		RotationFactor = 0.00f;
	}



	World.Identity();



	//! Get world matrix
	World.Transpose();
}



/*!******************************************************************************************************************************************************************************

	@brief Performs any operation if the app's window is resized.

********************************************************************************************************************************************************************************/
void C_CustomApp::OnResize()
{

}



/*!******************************************************************************************************************************************************************************

	@brief Performs any operation to render something to screen.

********************************************************************************************************************************************************************************/
void C_CustomApp::OnRender()
{
	//! Clear color to clear the back buffer
	C_LinearColor Color;

	//! Dark gray: RGBA [100, 100, 100, 255] * 1 / 2.2 = Linear [0.45, 0.45, 0.45, 1.0]
	Color.SetRed(0.45f);
	Color.SetGreen(0.45f);
	Color.SetBlue(0.45f);
	Color.SetAlpha(1.0f);



	//! Clear back buffer
	m_Graphics->ClearRenderTarget(m_BackBuffer, Color);



	//! Clear depth stencil buffer
	m_Graphics->ClearDepthStencilView(m_Depth);



	//! Map and set world matrix to world constant buffer
	m_Graphics->MapConstantBuffer(&World, sizeof(C_Matrix4), m_WrldBuffer);
	m_Graphics->SetConstantBuffer(0, 1, m_WrldBuffer);



	//! Get view matrix from camera
	m_Camera->m_View.LookAt(m_Camera->m_Position, m_Camera->m_Target, m_Camera->m_Up);
	m_Camera->m_View.Transpose();

	//! Map and set view constant buffer
	m_Graphics->MapConstantBuffer(&m_Camera->m_View, sizeof(C_Matrix4), m_ViewBuffer);
	m_Graphics->SetConstantBuffer(1, 1, m_ViewBuffer);



	//! Calculate the aspect ratio of the projection matrix
	float Ratio = (float)m_Width / (float)m_Height;

	//! Get projection matrix
	Proj.Projection(0.4f * C_PlatformMath::m_Pi, Ratio, CAMERA_NEAR, CAMERA_FAR);
	Proj.Transpose();

	//! Map and set projection constant
	m_Graphics->MapConstantBuffer(&Proj, sizeof(C_Matrix4), m_ProjBuffer);
	m_Graphics->SetConstantBuffer(2, 1, m_ProjBuffer);



	//! Set shader resource view
	m_Graphics->SetShaderResourceView(0, 1, m_ShdResourceView);



	//! Set sampler
	m_Graphics->SetSampler(0, 1, m_Sampler);



	//!
	m_Graphics->SetRasterizer(m_Raster);


	//! Draw loaded data here
	m_Graphics->DrawGeometry(m_SquareMesh->m_SolidIB->GetCount(), 0, 0);



	//! Present graphics to the screen
	m_Graphics->Render();
}



/*!******************************************************************************************************************************************************************************

	@brief Performs any operation to release and deallocate app specific objects.

********************************************************************************************************************************************************************************/
void C_CustomApp::OnDestroy()
{
	//! Close the back buffer render target 
	m_BackBuffer->Close();
	//! Deallocate back buffer
	delete m_BackBuffer;
	//! Point back buffer to null
	m_BackBuffer = nullptr;
	//! Report to the user
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Back buffer deallocated successfully", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//! Deallocate the graphics pipeline
	m_Graphics->Close();
	//! Delete from RAM
	delete m_Graphics;
	//! Nullify the graphics pipeline pointer
	m_Graphics = nullptr;
	//! Report to the user
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Graphics pipeline deallocated successfully",
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//!
	m_SquareMesh->Close();
	delete m_SquareMesh;
	m_SquareMesh = nullptr;
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Geometry deallocated successfully", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE);



	//!
	m_VShader->Close();
	//!
	delete m_VShader;
	//!
	m_VShader = nullptr;
	//!
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Vertex shader deallocated successfully",
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//!
	m_PShader->Close();
	delete m_PShader;
	m_PShader = nullptr;
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Pixel shader cerrado con éxito", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//!
	m_InputLayout->Close();
	delete m_InputLayout;
	m_InputLayout = nullptr;
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Input layout cerrado con éxito", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//! Close the depth
	m_Depth->Close();
	delete m_Depth;
	m_Depth = nullptr;
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Profundidad cerrada con éxito", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//! Close the world matrix
	m_WrldBuffer->Close();
	//!
	delete m_WrldBuffer;
	//!
	m_WrldBuffer = nullptr;
	//!
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Buffer de mundo cerrado con exito", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//! Close the view matrix
	m_ViewBuffer->Close();
	//!
	delete m_ViewBuffer;
	//!
	m_ViewBuffer = nullptr;
	//!
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Buffer de vista cerrado con éxito",
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//! Close the projection matrix
	m_ProjBuffer->Close();
	//!
	delete m_ProjBuffer;
	//!
	m_ProjBuffer = nullptr;
	//!
	m_AppLogger->AddEntry
	(
		MessageLevel::_MESSAGE, 
		"Buffer de proyección cerrado con éxito", 
		HR_FILE, 
		HR_FUNCTION, 
		HR_LINE
	);



	//! Close the app's log file
	m_AppLogger->Close("HR_CoreTestLogger");
	delete m_AppLogger;
	m_AppLogger = nullptr;
}


