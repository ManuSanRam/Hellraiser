#pragma once

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

using namespace HR_SDK;

#define ROTATION_FACTOR 0.01f

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
	}

	/*!
	*/
	~C_CustomApp()
	{
		
	}

	/*!
	*/
	virtual void OnInit();
	
	/*!
	*/
	virtual void OnUpdate();

	/*!*/
	virtual void OnResize();

	/*!
	*/
	virtual void OnRender();
	
	/*!
	*/
	virtual void OnDestroy();

	bool m_Fullscreen;

	/*!
	*/
	C_Logger*				m_GraphicsLogger;

	/*!
	*/
	C_GraphicsAPI*			m_Graphics;

	/*!
	*/
	C_Texture*				m_BackBuffer;
	
	/*!
	*/
	C_DepthStencil*			m_Depth;

	/*!
	*/
	C_TestMesh*				m_SquareMesh;
	/*!
	*/
	ID3D11Buffer*			m_VertexBuffer;
	/*!
	*/
	ID3D11Buffer*			m_IndexBuffer;

	/*!
	*/
	C_InputLayout*			m_InputLayout;

	/*!
	*/
	C_VertexShader*			m_VShader;
	/*!
	*/
	C_PixelShader*			m_PShader;

	/*!
	*/
	C_Viewport*				m_Viewport;

	/*!
	*/
	C_ConstantBuffer*		m_WrldBuffer;
	/*!
	*/
	C_ConstantBuffer*		m_ViewBuffer;
	/*!
	*/
	C_ConstantBuffer*		m_ProjBuffer;

	/*!
	*/
	C_GCamera*				m_StaticCamera;

	/*!
	*/
	C_Matrix4 World;
	/*!
	*/
	C_Matrix4 View;
	/*!
	*/
	C_Matrix4 Proj;
};

static float RotationFactor = ROTATION_FACTOR;
