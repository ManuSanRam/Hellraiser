#pragma once
#include "HRGraphics_Prerequisites.h"

/*!*************************************************************************************************************************************************************************
 * @file		HRGraphics_Vertex.h																																		   *
 * @brief		Declares vertex class. A vertex is a point in 3D space that is part of a model (2D or 3D).																   *
 *																																										   *
 * A vertex contains information such as:																																   *
 * - Position. Position of the vertex in space.																															   *
 * - Color. RGBA color of the vertex.																																	   *
 * - Normal. 																																							   *
 * - Texture Coordinates. U, V coordinates of the vertex, that contains information of the 																				   *
 * 																																										   *
 * @date		07-02-2017																																				   *
 * @author		Manuel Aldair Santos Ram�n (ManuSanRam)																													   *
 * @copyright	Infernal Coders S.A																																		   *
***************************************************************************************************************************************************************************/

/*!*************************************************************************************************************************************************************************
 * @section External inclusions																																			   *
***************************************************************************************************************************************************************************/
#include <HRUtility_Vector2D.h>
#include <HRUtility_Vector3D.h>
#include <HRUtility_Color.h>

namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	 * @brief
	***********************************************************************************************************************************************************************/
	struct HR_D3DGRAPHICSAPI_EXPORT S_Vertex
	{
	public:
		S_Vertex
		(
			float _x,
			float _y,
			float _z,

			float _u,
			float _v
		)
		{
			m_Position.m_x = _x;
			m_Position.m_y = _y;
			m_Position.m_z = _z;

			m_TexCoords.m_x = _u;
			m_TexCoords.m_y = _v;
		}

		S_Vertex(const S_Vertex &prm_Copy)
		{
			*this = prm_Copy;
		}
		/*!*****************************************************************************************************************************************************************
		 * @brief Position of the vertex in 3D space																													   *
		*******************************************************************************************************************************************************************/
		C_Vector3D		m_Position;
		
		/*!*****************************************************************************************************************************************************************
		 * @brief Color of the vertex.																																	   *
		*******************************************************************************************************************************************************************/
		C_Vector2D		m_TexCoords;
	};
}
