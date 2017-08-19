#pragma once
#include "HRGraphics_Prerequisites.h"

/*!*****************************************************************************************************************************************************************************

	@file		HRGraphics_GCamera.h																																	   

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  																																										   
	This file contains the declaration of the graphics camera object. This object is used to view any objects that are inside its range of vision and that collide with its 																																								   
	frustrum.																																							   
	Its functions are described below:																																	   
	- Look at a certain target, using a rotation.
	- Orbit a target.
	- Render any object that os viewing.																																	      
   				
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		13-02-2017																																				   
	@author		Manuel Santos Ram�n																																		   
	@copyright	Infernal Coders S.A	

********************************************************************************************************************************************************************************/


/*!*****************************************************************************************************************************************************************************

	@section External inclusions
	Here goes any file inclusions for the declared class to work.

********************************************************************************************************************************************************************************/
#include <HRUtility_Matrix4.h>
#include <HRUtility_Vector4D.h>
#include <HRUtility_Vector3D.h>
#include <HRUtility_PlatformMath.h>

namespace HR_SDK
{

/*!*****************************************************************************************************************************************************************************

	@brief Defines the nearest point in Z-coordinate that can be passed to the camera.

********************************************************************************************************************************************************************************/
#define CAMERA_NEAR		0.001f

/*!*****************************************************************************************************************************************************************************

	@brief Defines the farthest point in Z-coordinate that can be passed to the camera.

********************************************************************************************************************************************************************************/
#define CAMERA_FAR		1000.0f

	/*!*************************************************************************************************************************************************************************
	
		@brief Declares a Graphics' Camera object.																														   
		This object is used to render any object that collides in a frustrum.																							   
	
	****************************************************************************************************************************************************************************/
	class HR_D3DGRAPHICSAPI_EXPORT C_GCamera
	{
	public:
		/*!*********************************************************************************************************************************************************************
		
			@date 24-06-2017 13:04
			@brief UPDATE: Implement new functions on the camera.
			Functions added to the class are:
			- LookAt: Moves the target the camera is looking at
			- Move: Moves the camera
			- Pan: Moves the camera and the objective
			- Rotate: Rotates the target with respect to the camera
			- Orbit: Rotates the camera with respect to the target.
			- Pitch: Performs a X-axis proper rotation
			- Yaw: Performs a Y-axis proper rotation
			- Roll: Performs a Z-axis proper rotation
		
		************************************************************************************************************************************************************************/
		C_GCamera()
		{

		}

		/*!**********************************************************************************************************************************************************************
		
			@brief Constructor (Parameter)
		
			@param prm_Position Position of the camera
			@param prm_Target Target the camera is looking at
			@param prm_Up Up vector to define front and right
		
		************************************************************************************************************************************************************************/
		C_GCamera
		(
			C_Vector3D& prm_Position,
			C_Vector3D& prm_Target,
			C_Vector3D& prm_Up
		)
		{
			//! Assign camera�s data (Position, View Target and Up vector)
			SetPosition(prm_Position.m_x, prm_Position.m_y, prm_Position.m_z);
			SetUp(prm_Up.m_x, prm_Up.m_y, prm_Up.m_z);

			SetTargetVector(prm_Target);
		}

		/*!*********************************************************************************************************************************************************************
		 *
		 *	@brief Destructor
		 *
		************************************************************************************************************************************************************************/
		~C_GCamera()
		{

		}

		/*!*********************************************************************************************************************************************************************
		 *
		 *	@brief Sets the camera's position in the world
		 *
		 *	@param prm_Position Position in the world where the camera is located
		 *
		************************************************************************************************************************************************************************/
		void			SetPosition
		(
			float prm_X,
			float prm_Y,
			float prm_Z
		);

		void			SetPositionVector
		(
			const C_Vector3D& prm_Vector
		);

		/*!*********************************************************************************************************************************************************************
		 *
		 *	@brief Sets the target that the camera is looking at
		 *
		 *	@param prm_Target Target's position. This position is the 
		 *
		************************************************************************************************************************************************************************/
		void			SetTarget
		(
			float prm_X,
			float prm_Y,
			float prm_Z
		);
		
		/*!*********************************************************************************************************************************************************************
			
			@brief Sets the target that the camera is looking at
		
			@param prm_Target Target's position. This position is the
		
		************************************************************************************************************************************************************************/
		void			SetTargetVector
		(
			const C_Vector3D& prm_Target
		);

		/*!*********************************************************************************************************************************************************************
		 *
		 *	@brief Sets the Up vector to represent the vector Y-axis
		 *
		 *	@param prm_Up Up vector to represent camera's Y-axis 
		 *
		************************************************************************************************************************************************************************/
		void			SetUp
		(
			float prm_X,
			float prm_Y,
			float prm_Z
		);

		/*!*********************************************************************************************************************************************************************
		 *
		 *	@brief Updates the data of the camera in each frame, 
		 *
		************************************************************************************************************************************************************************/
		void			Update
		(

		);

		/*!*********************************************************************************************************************************************************************
		 
			@brief Calculates the view space matrix, obtaining the orientation which the camera is pointing at.

		----------------------------------------------------------------
		 
		************************************************************************************************************************************************************************/
		void			LookAt
		(
			const C_Vector3D& prm_Target
		);

		/*!*********************************************************************************************************************************************************************
		 *
		 *
		 *
		************************************************************************************************************************************************************************/
		void			Move
		(
			const C_Vector3D& prm_Position
		);

		/*!**********************************************************************************************************************************************************************
		 *
		 *	@brief Moves the camera and the target towards a certain direction
		 *
		 *	@param prm_Direction Direction in which the camera and the target will move.
		 *
		************************************************************************************************************************************************************************/
		void			Pan
		(
			const C_Vector3D& prm_Direction
		);

		/*!*********************************************************************************************************************************************************************
		************************************************************************************************************************************************************************/
		C_Matrix4		Rotate
		(
			const C_Vector3D& prm_Axis
		);

		/*!**********************************************************************************************************************************************************************
		 *
		 *	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		 *	W factor is left as 1																																				*
		 *	@param	Pitch 'X' rotation factor																																	*
		 *
		************************************************************************************************************************************************************************/
		void			Pitch
		(
			float prm_PitchValue
		);

		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		void			Yaw
		(
			float prm_YawValue
		);

		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		void			Roll
		(
			float prm_RollValue
		);

		/*!**********************************************************************************************************************************************************************
		
			@brief	Calculates rotation matrix with given X, Y and Z rotation factors
			W factor is left as 1

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																																			
			@param	Pitch 'X' rotation factor																																	
		
		************************************************************************************************************************************************************************/
		C_Vector3D		m_Position;

		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		C_Vector3D		m_Target;
		
		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		C_Vector3D		m_Up;

		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		C_Vector3D		m_Front;
		
		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		C_Vector3D		m_Right;

		/*!*********************************************************************************************************************************************************************
		*
		*	@brief Updates the data of the camera in each frame,
		*
		************************************************************************************************************************************************************************/
		bool			m_Perform;

		/*!**********************************************************************************************************************************************************************
		*
		*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							*
		*	W factor is left as 1																																				*
		*	@param	Pitch 'X' rotation factor																																	*
		*
		************************************************************************************************************************************************************************/
		C_Matrix4		m_View;
	};
}