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
#include <xnamath.h>
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
	  /*!
	  */
	  C_GCamera()
	  {
		  m_View.Identity();
		  m_Position.UnitVector();
	  }
	  
	  /*!
	  */
	  C_GCamera(C_Vector3D prm_Position, float prm_FOV, float prm_Aspect, float prm_Near, float prm_Far)
	  {
		  SetPerspective(prm_FOV, prm_Aspect, prm_Near, prm_Far);
		  SetPosition(prm_Position);
		  SetForward(C_Vector3D(0.0f, 0.0f, 1.0f));
		  SetUp(C_Vector3D(0.0f, 1.0f, 0.0f));
	  }

	  /*!
	  */
	  ~C_GCamera()
	  {
	  
	  }
	  
	  /*!
	  */
	  void SetCamPosition(C_Vector3D prm_Pos)
	  {
	  	m_Position = prm_Pos;
	  }

	  /*!
	  */
	  void SetCamForward(C_Vector3D prm_Fwd)
	  {
		  m_Forward = prm_Fwd;
	  }

	  /*!
	  */
	  void SetUp(C_Vector3D prm_Up)
	  {
		  m_Up = prm_Up;
	  }

	  void SetPerspective(float prm_FOV, float prm_Aspect, float prm_Near, float prm_Far)
	  {
		float radFOV = (prm_FOV * C_PlatformMath::m_Pi * (1 / 180.0f));

		radFOV = C_PlatformMath::Tangent(radFOV) / 2.0f;

		m_View.m_Element[0][0] = 1.0f / (prm_Aspect * radFOV);
		m_View.m_Element[1][1] = 1.0f / (radFOV);
		m_View.m_Element[2][2] = (prm_Far + prm_Near) / (prm_Far - prm_Near);
		m_View.m_Element[2][3] = 1.0f;
		m_View.m_Element[3][2] = (2.0f * prm_Far * prm_Near) / (prm_Far - prm_Near);
		
		m_View.Transpose();
	  }
	  
	  /*!
	  */
	  C_Matrix4 GetView()
	  {
	  	return m_View * LookAt(m_Position, m_Position + m_Forward, m_Up);
	  }

	  /*!
	  */
	  C_Matrix4 LookAt(C_Vector3D prm_Eye, C_Vector3D prm_Forward, C_Vector3D prm_Up)
	  {
		  C_Vector3D Z(1.0f, 1.0f, 1.0f), X(1.0f, 1.0f, 1.0f), Y(1.0f, 1.0f, 1.0f);

		  Z = prm_Eye - prm_Forward;
		  Z.Normalize();

		  Y = prm_Up;

		  X = Y.Cross(Z);
		  Y = Z.Cross(X);

		  X.Normalize();
		  Y.Normalize();

		  // Finally create the view matrix from the three updated vectors.
		  C_Matrix4 LookAtMatrix
		  (
			  X.m_x, Y.m_x, Z.m_x, 0.0f,
			  X.m_y, Y.m_y, Z.m_y, 0.0f,
			  X.m_z, Y.m_z, Z.m_z, 0.0f,
			  X.Dot(prm_Eye), Y.Dot(prm_Eye), Z.Dot(prm_Eye), 1.0f
		  );

		  return m_View * LookAtMatrix;
	  }
	  
	  private:
	  /*!
	  */
	  C_Vector3D m_Position;

	  /*!
	  */
	  C_Vector3D m_Forward;

	  /*!
	  */
	  C_Vector3D m_Up;
	  
	  /*!
	  */
	  C_Matrix4 m_View;
	};
}