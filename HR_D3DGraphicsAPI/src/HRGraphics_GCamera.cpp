#include "HRGraphics_GCamera.h"

/*!
*/

namespace HR_SDK
{
	/*!**************************************************************************************************************************************************************************
	
		@brief Updates the data of the camera in each frame,
	
	****************************************************************************************************************************************************************************/
	void C_GCamera::SetPosition
	(
		float prm_X,
		float prm_Y,
		float prm_Z
	)
	{
		m_Position.Set(prm_X, prm_Y, prm_Z);
	}

	/*!**************************************************************************************************************************************************************************
	****************************************************************************************************************************************************************************/
	void C_GCamera::SetPositionVector
	(
		const C_Vector3D& prm_Position
	)
	{
		m_Position = prm_Position;
	}

	/*!**************************************************************************************************************************************************************************
	****************************************************************************************************************************************************************************/
	void C_GCamera::SetTarget
	(
		float prm_X,
		float prm_Y,
		float prm_Z
	)
	{
		m_Target.Set(prm_X, prm_Y, prm_Z);
	}

	/*!**************************************************************************************************************************************************************************
	
		@brief Updates the data of the camera in each frame,
	
	****************************************************************************************************************************************************************************/
	void C_GCamera::SetTargetVector
	(
		const C_Vector3D& prm_Target
	)
	{
		//! Reset the target
		m_Target = prm_Target;

		//! Recalculate the front, right and Up vectors, to censerve them orthonormal
		//! Front
		m_Front = m_Target - m_Position;
		m_Front.Normalize();

		//! Right
		m_Right = m_Front.Cross(m_Up);
		m_Right.Normalize();

		//! Up
		m_Up = m_Front.Cross(m_Right);
		m_Up.Normalize();
	}

	/*!**************************************************************************************************************************************************************************
	****************************************************************************************************************************************************************************/
	void C_GCamera::SetUp
	(
		float prm_X,
		float prm_Y,
		float prm_Z
	)
	{
		m_Up.Set(prm_X, prm_Y, prm_Z);
	}

	/*!**************************************************************************************************************************************************************************
	
		@brief Updates the data of the camera in each frame.
		This updating occurs if the @var m_Perform
	
	****************************************************************************************************************************************************************************/
	void C_GCamera::		Update
	(

	)
	{
		//! Check if any changes were made
		if (m_Perform)
		{
			//! Recalculate view matrix
			m_View.LookAt(m_Position, m_Target, m_Up);
		}
	}

	/*!**************************************************************************************************************************************************************************
	
		@brief Calculates the view space matrix, obtaining the orientation which the camera is pointing at.
	
	****************************************************************************************************************************************************************************/
	void			C_GCamera::LookAt
	(
		const C_Vector3D& prm_Target
	) 
	{
		//! Reset camera's target
		SetTargetVector(prm_Target);
		//! Reset the updating switch
		m_Perform = true;
	}

	/*!**************************************************************************************************************************************************************************
	
	
	
	****************************************************************************************************************************************************************************/
	void			C_GCamera::Move
	(
		const C_Vector3D& prm_Position
	)
	{

	}

	/*!**************************************************************************************************************************************************************************
	
		@brief Moves the camera and the target towards a certain direction
	
		@param prm_Direction Direction in which the camera and the target will move.
	
	****************************************************************************************************************************************************************************/
	void			C_GCamera::Pan
	(
		const C_Vector3D& prm_Direction
	)
	{

	}

	/*!**************************************************************************************************************************************************************************
	****************************************************************************************************************************************************************************/
	C_Matrix4		C_GCamera::Rotate
	(
		const C_Vector3D& prm_Axis
	)
	{
		C_Matrix4 rotation;

		return rotation;
		//m_Position *= rotation;
	}

	/*!**************************************************************************************************************************************************************************
	
		@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							
		W factor is left as 1																																				
		@param	Pitch 'X' rotation factor																																	
	
	****************************************************************************************************************************************************************************/
	void			C_GCamera::Pitch
	(
		float prm_PitchValue
	)
	{
		C_Matrix4 rotation;
		rotation.RotateY(prm_PitchValue, true);

		//m_Up *= rotation;
	}

	/*!**************************************************************************************************************************************************************************
	
		@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							
		W factor is left as 1																																				
		@param	Pitch 'X' rotation factor																																	
	
	****************************************************************************************************************************************************************************/
	void			C_GCamera::Yaw
	(
		float prm_YawValue
	)
	{
		C_Matrix4 rotation;

		rotation.RotateX(prm_YawValue, true);

		//m_Right *= rotation;
	}

	/*!**************************************************************************************************************************************************************************
	*
	*	@brief	Calculates rotation matrix with given X, Y and Z rotation factors																							
	*	W factor is left as 1																																				
	*	@param	Pitch 'X' rotation factor																																	
	*
	****************************************************************************************************************************************************************************/
	void			C_GCamera::Roll
	(
		float prm_RollValue
	)
	{
		C_Matrix4 rotation;

		rotation.RotateZ(prm_RollValue, true);

		//m_Front *= rotation;
	}

}