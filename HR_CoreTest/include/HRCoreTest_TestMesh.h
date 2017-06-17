#pragma once

#include <HRGraphics_Buffer.h>

using namespace HR_SDK;

namespace HR_SDK
{
	struct GraphicsDevice;
	struct GraphicsDeviceContext;
	struct GraphicsSwapChain;

	struct GraphicsVertexBuffer;
	struct GraphicsIndexBuffer;
}

/*!
 * @brief Declares a test mesh to test the graphics API
*/
class C_TestMesh
{
public:
	/*!
	 * @brief Constructor (default)
	*/
	C_TestMesh()
	{
		
	}
	/*!
	 * @brief Destructor
	*/
	~C_TestMesh()
	{

	}

	/*!
	 * @brief Feeds the mesh's geometry buffer with data for rendering
	*/
	bool CreateVertexB(GraphicsDevice* prm_Device);
	
	/*!
	 * @brief Feeds the mesh's index buffer with data for control
	*/
	bool CreateIndexB(GraphicsDevice* prm_Device);

	/*!
	*/
	void SetIB
	(
		GraphicsDeviceContext*	prm_DC
	);

	/*!
	*/
	void SetVB
	(
		GraphicsDeviceContext*	prm_DC
	);

	/*!
	*/
	void SetTopology
	(
		GraphicsDeviceContext*	prm_DC,
		D3D_Topologies::E prm_Topology
	);

	/*!
	*/
	void SetFillMode
	(

	);

	/*!
	 * @brief Draws the test mesh to screen
	*/
	void Draw
	(
		GraphicsDeviceContext*	prm_DC
	);

	/*!
	 * @brief Buffer to control geometry data.
	*/
	C_VBuffer		m_SolidVB;
	
	/*!
	 * @brief 
	*/
	C_IBuffer32		m_SolidIB;
};
