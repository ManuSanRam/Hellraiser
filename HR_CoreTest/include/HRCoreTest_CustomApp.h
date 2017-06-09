#pragma once

/*!
*/

#include <HRCore_Application.h>

#include <Windows.h>

#include <HRUtility_Vector3D.h>
#include <HRUtility_Matrix4.h>
#include <HRUtility_Logger.h>

#include <HRGraphics_Graphics.h>

#include <HRGraphics_Texture.h>
#include <HRGraphics_Depth.h>

#include <HRGraphics_Shader.h>
#include "HRCoreTest_TestMesh.h"
#include <HRGraphics_InputLayout.h>

#include <HRGraphics_Viewport.h>
#include <HRGraphics_GCamera.h>

/*!
*/

#define WIN32_LEAN_AND_MEAN
#define WINDOWED_W		1000
#define WINDOWED_H		900

using namespace HR_SDK;

/*!
*/
struct Window;

/*!
*/
class C_CustomApp : public C_Application
{
public:
	/*!
	*/
	C_CustomApp(bool Fullscreen)
	{
		m_Fullscreen = Fullscreen;
		m_Graphics = NULL;
		m_SquareMesh = NULL;
		m_StaticCamera = NULL;

		Init();
	}

	/*!*/
	~C_CustomApp()
	{

	}
	
	/*!
	@brief Runs the app
	*/
	void Run();
	

	/*!
	*/
	virtual void OnInit();
	/*
	*/
	virtual bool OnUpdate();
	/*
	*/
	virtual void OnRender();
	/*
	*/
	virtual void OnDestroy();

	bool m_Fullscreen;

	Window*					m_Window;

	C_Logger*				m_GraphicsLogger;

	C_GraphicsAPI*			m_Graphics;

	C_Texture*				m_BackBuffer;
	C_DepthStencil*			m_Depth;

	C_TestMesh*				m_SquareMesh;
	ID3D11Buffer*			m_VertexBuffer;
	ID3D11Buffer*			m_IndexBuffer;

	C_InputLayout*			m_InputLayout;

	C_VertexShader*			m_VShader;
	C_PixelShader*			m_PShader;

	C_Viewport*				m_Viewport;

	C_ConstantBuffer*		m_WrldBuffer;
	C_ConstantBuffer*		m_ViewBuffer;
	C_ConstantBuffer*		m_ProjBuffer;

	C_GCamera*				m_StaticCamera;

	C_Matrix4 World;
	C_Matrix4 View;
	C_Matrix4 Proj;
};
