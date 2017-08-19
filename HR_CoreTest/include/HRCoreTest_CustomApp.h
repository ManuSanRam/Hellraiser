#pragma once

/*!******************************************************************************************************************************************************************************

	@file		HRCoreTest_CustomApp.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of class C_Application.
	This class is used as an interface to create, control and render applications in any platform.

	The basic functions of this class are:
	- Initialize: Starts the application, passes parameters to the app's objects.
	- Update: Updates the app's data.
	- Render: Renders the app's data to the screen.
	- Close: Releases the app's data to the screen.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date			26-09-2016
	@author			Manuel Santos Ram�n [ManuSanRam]
	@copyright		Infernal Coders S.A.

********************************************************************************************************************************************************************************/



#include <HRCore_Application.h>

#include <Windows.h>

#include <HRUtility_Vector3D.h>
#include <HRUtility_Matrix4.h>
#include <HRUtility_Logger.h>

#include <HRGraphics_Graphics.h>

#include "HRCoreTest_TestMesh.h"
#include <HRGraphics_GCamera.h>



using namespace HR_SDK;



/*!******************************************************************************************************************************************************************************

	@def ROTATION_FACTOR
	@brief Factor used to rotate a model along any given axis

********************************************************************************************************************************************************************************/
#define ROTATION_FACTOR 0.01f



/*!******************************************************************************************************************************************************************************

	@class C_CustomApp
	@brief App that can be customized to perform specific actions.

********************************************************************************************************************************************************************************/
class C_CustomApp : public C_Application
{
public:
	/*!**************************************************************************************************************************************************************************

		@brief Constructor [Default]

	****************************************************************************************************************************************************************************/
	C_CustomApp(bool Fullscreen)
	{
		//! User decides to start app in fullscreen or windowed mode
		m_Fullscreen = Fullscreen;

		//! Start everything pointing to address 0
		m_Graphics = NULL;

		m_BackBuffer = NULL;
		m_Depth = NULL;

		m_VShader = NULL;
		m_PShader = NULL;
		
		m_SquareMesh = NULL;

		m_InputLayout = NULL;
		m_Viewport = NULL;

		m_Camera = NULL;
	}



	/*!**************************************************************************************************************************************************************************

		@brief Destructor

	****************************************************************************************************************************************************************************/
	~C_CustomApp()
	{
		
	}



	/*!**************************************************************************************************************************************************************************

		@brief Initialize every object for the app.

	****************************************************************************************************************************************************************************/
	virtual void				OnInit();
	


	/*!**************************************************************************************************************************************************************************

		@brief Update the app's data.

	****************************************************************************************************************************************************************************/
	virtual void				OnUpdate();



	/*!**************************************************************************************************************************************************************************

		@brief Performs any operation if the app's window is resized.

	****************************************************************************************************************************************************************************/
	virtual void				OnResize();



	/*!**************************************************************************************************************************************************************************

		@brief Performs any operation to render something to screen.

	****************************************************************************************************************************************************************************/
	virtual void				OnRender();
	


	/*!**************************************************************************************************************************************************************************

		@brief Performs any operation to release and deallocate app specific objects.

	****************************************************************************************************************************************************************************/
	virtual void				OnDestroy();



	/*!**************************************************************************************************************************************************************************
	
		@brief Check if the application is drawn in fullscreen or windowed.
		True if the application is rendered in fulscreen, false if the application is rendered in windowed mode.

	****************************************************************************************************************************************************************************/
	bool m_Fullscreen;



	/*!**************************************************************************************************************************************************************************

		@brief Graphics pipeline object.
		This object sets every resource necessary for rendering.

	****************************************************************************************************************************************************************************/
	C_GraphicsAPI*				m_Graphics;



	/*!**************************************************************************************************************************************************************************

		@brief Texture buffer to render the final image.

	****************************************************************************************************************************************************************************/
	C_RenderTarget*				m_BackBuffer;
	


	/*!**************************************************************************************************************************************************************************

		@brief Depth-stencil object to set the order of rendering.

	****************************************************************************************************************************************************************************/
	C_DepthStencil*				m_Depth;



	/*!**************************************************************************************************************************************************************************

		@brief File containing the processing of the vertices into an effects file

	****************************************************************************************************************************************************************************/
	C_VertexShader*				m_VShader;



	/*!**************************************************************************************************************************************************************************

		@brief File containing the processing of the pixels into an effects file

	****************************************************************************************************************************************************************************/
	C_PixelShader*				m_PShader;



	/*!**************************************************************************************************************************************************************************

		@brief Geometry to be rendered, containing the vertices and the indices of the geometry

	****************************************************************************************************************************************************************************/
	C_TestMesh*					m_SquareMesh;



	/*!**************************************************************************************************************************************************************************

		@brief Input layout containing the semantics for the shader

	****************************************************************************************************************************************************************************/
	C_InputLayout*				m_InputLayout;



	/*!**************************************************************************************************************************************************************************

		@brief Viewport area to render the processed data on the screen

	****************************************************************************************************************************************************************************/
	C_Viewport*					m_Viewport;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_ConstantBuffer*			m_WrldBuffer;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_ConstantBuffer*			m_ViewBuffer;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_ConstantBuffer*			m_ProjBuffer;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_Texture*					m_Texture;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_ShaderResource*			m_ShdResourceView;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_Sampler*					m_Sampler;



	/*!**************************************************************************************************************************************************************************

		@brief Constant buffer containing the world transformation matrix

	****************************************************************************************************************************************************************************/
	C_Rasterizer*				m_Raster;



	/*!**************************************************************************************************************************************************************************

		@brief Camera object to 

	****************************************************************************************************************************************************************************/
	C_GCamera*					m_Camera;



	/*!**************************************************************************************************************************************************************************

		@brief World matrix to operate vertices and pixels on world space

	****************************************************************************************************************************************************************************/
	C_Matrix4					World;



	/*!**************************************************************************************************************************************************************************

		@brief Projection matrix to operate vertices and pixels on scren 

	****************************************************************************************************************************************************************************/
	C_Matrix4					Proj;
};

static float RotationFactor = ROTATION_FACTOR;
