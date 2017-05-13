#pragma once

#include <HRCore_Application.h>

#include <Windows.h>

#include <HRUtility_Vector3D.h>
#include <HRUtility_Logger.h>

#include <HRGraphics_Graphics.h>

#include <HRGraphics_Texture.h>
#include <HRGraphics_Depth.h>

#include <HRGraphics_Shader.h>
#include "HRCoreTest_TestMesh.h"
#include <HRGraphics_InputLayout.h>

#include <HRGraphics_Viewport.h>



#define WIN32_LEAN_AND_MEAN
#define WINDOWED_W		1000
#define WINDOWED_H		800

using namespace HR_SDK;

struct Window;

class C_CustomApp : public C_Application
{
public:
	C_CustomApp()
	{
		m_Width = 0;
		m_Height = 0;
		m_Fullscreen = false;
		m_Graphics = NULL;
		m_SquareMesh = NULL;

		Init();
	}

	C_CustomApp(bool Fullscreen)
	{
		m_Width = 0;
		m_Height = 0;
		m_Fullscreen = Fullscreen;
		m_Graphics = NULL;
		m_SquareMesh = NULL;

		Init();
	}

	~C_CustomApp()
	{
		Destroy();
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

	uint32 m_Width;
	uint32 m_Height;

	Window*					m_Window;

	C_Logger*				m_GraphicsLogger;

	C_GraphicsAPI*			m_Graphics;

	C_Texture*				m_BackBuffer;
	C_DepthStencil*			m_Depth;

	C_TestMesh*				m_SquareMesh;

	C_InputLayout*			m_InputLayout;

	C_VertexShader*			m_VShader;
	C_PixelShader*			m_PShader;

	C_Viewport*				m_Viewport;
};

static float Red =		0.0f;
static float Green =	0.0f;
static float Blue =		0.0f;
static float Alpha =	1.0f;
