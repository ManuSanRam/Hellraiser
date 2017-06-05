#pragma once
#include "HRGraphics_Prerequisites.h"

/*!*************************************************************************************************************************************************************************
 * @file		HRGraphics_GCamera.h																																	   *
 * 																																										   *
 * This file contains the declaration of the graphics camera object. This object is used to view any objects that are inside its range of vision and that collide with its *																																								   
 * frustrum.																																							   *
 * Its functions are described below:																																	   *
 * - Look at a certain target, using a rotation.																														   *
 * - Render any object that os viewing.																																	   *   
 * - 																																									   *
 * @date		13-02-2017																																				   *
 * @author		Manuel Santos Ramón																																		   *
 * @copyright	Infernal Coders S.A																																		   *
***************************************************************************************************************************************************************************/


/*!*************************************************************************************************************************************************************************
 * @section External inclusions																																			   *
 * Here goes any file inclusions for the declared class to work																											   *
***************************************************************************************************************************************************************************/
#include <HRUtility_Matrix4.h>
#include <HRUtility_Vector4D.h>
#include <HRUtility_Vector3D.h>
#include <HRUtility_PlatformMath.h>

namespace HR_SDK
{
#define CAMERA_NEAR		0.001f
#define CAMERA_FAR		1000.0f
	/*!*********************************************************************************************************************************************************************
	 * @brief Declares a Graphics' Camera object.																														   *
	 * This object is used to render any object that collides in a frustrum.																							   *
	***********************************************************************************************************************************************************************/
	class HR_D3DGRAPHICSAPI_EXPORT C_GCamera
	{
	public:
		/*!****************************************************************************************************************************************************************
		 * @brief Constructor
		*******************************************************************************************************************************************************************/
		C_GCamera()
		{

		}

		/*!****************************************************************************************************************************************************************
		 * @brief Destructor
		*******************************************************************************************************************************************************************/
		~C_GCamera()
		{

		}

		/*!****************************************************************************************************************************************************************
		 * Update: May 23th, 2017 17:55 pm
		 *
		 * Modifying the camera functionality, for setting view and projection matrices for the constant buffers
		 * This functions are exclusive for the graphics camera. It can rotate and translate.
		*******************************************************************************************************************************************************************/
		/*!****************************************************************************************************************************************************************
		 * @brief Sets the camera's position in the world
		 * @param prm_Position Position of the camera in world space
		*******************************************************************************************************************************************************************/
		void SetPosition
		(
			const C_Vector3D prm_Position
		);

		/*!
		*/
		void SetTarget
		(
			const C_Vector3D prm_Target
		);

		/*!
		 * @brief Sets the camera's up vector
		*/
		void SetUp
		(
			const C_Vector3D prm_Up
		);

		/*!
		 * @brief Calculates the view space matrix, obtaining the orientation which the camera is pointing at.
		*/
		void LookAt
		(

		);

		/*!
		 * @brief Creates the projection space matrix of the camera. This shall be replaced with the frustrum
		 * @param prm_FOVAngle Angle in radians 
		*/
		void Projection
		(
			float prm_FOVAngle,
			float prm_Ratio,
			float prm_NearZ,
			float prm_FarZ
		);

		//! This object needs to be defined
		//! C_Frustrum m_FOV;

		C_Vector3D m_Position;
		C_Vector3D m_Target;
		C_Vector3D m_Up;

		C_Matrix4  m_View;
		C_Matrix4  m_Projection;
	};
}