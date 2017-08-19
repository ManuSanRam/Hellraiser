#include "HRCoreTest_TestMesh.h"



/*!******************************************************************************************************************************************************************************

	@file		HRCoreTest_TestMesh.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of the test mesh object, used to test the graphics pipeline and the rendering.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		11-08-2017
	@author		Manuel Santos Ramón [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/



bool C_TestMesh::CreateVertexB
(
	GraphicsDevice* prm_Device
)
{
	S_Vertex V1
	(
		-1.0f, -1.0f, -1.0f,
		0.0f, 0.0f
	);

	S_Vertex V2
	(
		-1.0f, 1.0f, -1.0f,
		0.0f, 1.0f
	);

	S_Vertex V3
	(
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f
	);

	S_Vertex V4
	(
		1.0f, -1.0f, -1.0f,
		1.0f, 0.0f
	);



	S_Vertex V5
	(
		-1.0f, -1.0f, 1.0f,
		1.0f, 0.0f
	);

	S_Vertex V6
	(
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f
	);

	S_Vertex V7
	(
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f
	);

	S_Vertex V8
	(
		1.0f, -1.0f, 1.0f,
		0.0f, 0.0f
	);



	m_SolidVB = new C_VBuffer();



	m_SolidVB->AddVertex(V1);
	m_SolidVB->AddVertex(V2);
	m_SolidVB->AddVertex(V3);
	m_SolidVB->AddVertex(V4);
	m_SolidVB->AddVertex(V5);
	m_SolidVB->AddVertex(V6);
	m_SolidVB->AddVertex(V7);
	m_SolidVB->AddVertex(V8);



	if (!m_SolidVB->m_Vertices.size())
	{
		return false;
	}



	return true;



}




bool C_TestMesh::CreateIndexB
(
	GraphicsDevice* prm_Device
)
{
	uint32 Indices[]{
		//! Front
		0, 1, 2,
		0, 2, 3,

		//! Back
		4, 6, 5,
		4, 7, 6,

		//! Left
		4, 5, 1,
		4, 1, 0,

		//! Right
		3, 2, 6,
		3, 6, 7,

		//! Top
		1, 5, 6,
		1, 6, 2,

		//! Bottom
		4, 0, 3,
		4, 3, 7

	};



	m_SolidIB = new C_IBuffer32();



	for (auto indc : Indices)
	{
		m_SolidIB->AddIndex(indc);
	}



	if (!m_SolidIB->m_Indices.size())
	{
		return false;
	}

	return true;
}



void C_TestMesh::Close
(

)
{
	if (m_SolidVB)
	{
		m_SolidVB->Close();
		delete m_SolidVB;
	}

	m_SolidVB = nullptr;

	if (m_SolidIB)
	{
		m_SolidIB->Close();
		delete m_SolidIB;
	}

	m_SolidIB = nullptr;
}