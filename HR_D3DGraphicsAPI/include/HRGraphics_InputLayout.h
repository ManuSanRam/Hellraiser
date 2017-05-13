#pragma once

/*!*************************************************************************************************************************************************************************
* @file			HRGraphics_Buffer.cpp																																	   *
*																																										   *
* This file contains definition of the methods declared inside the buffers' classes.																					   *
* The methods implemented in the class are:																																   *
* - Setting of the channels individually.																																   *
* - Obtaining color structures from another 4D vector to get information from.																							   *
* - Obtaining color data from another color.																															   *
*																																										   *
* @date         08-11-2016																																				   *
* @author		Manuel Aldair Santos Ramón (ManuSanRam)																													   *
* @copyright	Infernal Coders S.A.																																	   *
***************************************************************************************************************************************************************************/

#include "HRGraphics_Prerequisites.h"

namespace HR_SDK
{
	/*!*********************************************************************************************************************************************************************
	 * @brief This struct holds the device object, used to encapsulate 3rd party data from DirectX.																	   	   *
	***********************************************************************************************************************************************************************/
	struct GraphicsDevice;
	/*!*********************************************************************************************************************************************************************
	 * @brief This struct holds the device context object, used to encapsulate 3rd party data from DirectX.																   *
	***********************************************************************************************************************************************************************/
	struct GraphicsDeviceContext;
	/*!*********************************************************************************************************************************************************************
	 * @brief This struct holds the input layout object, used to encapsulate 3rd party data from DirectX.																   *
	***********************************************************************************************************************************************************************/
	struct GraphicsInputLayout;
	/*!*********************************************************************************************************************************************************************
	 * @brief This struct holds the blob object, used to encapsulate 3rd party data from DirectX.																		   *
	***********************************************************************************************************************************************************************/
	struct GraphicsBlob;

	/*!*********************************************************************************************************************************************************************
	 * @brief This class creates, sets and controls the data of the input layout stage of the renring pipeline.															   *
	 * Here, the data passed is used to describe the objects used to render graphics to screen using shader files.														   *
	***********************************************************************************************************************************************************************/
	class HR_D3DGRAPHICSAPI_EXPORT C_InputLayout
	{
	public:
		/*!*****************************************************************************************************************************************************************
		 * @brief Constructor (default)																																	   *
		*******************************************************************************************************************************************************************/
		C_InputLayout()
		{
			m_Inputs.clear();
		}

		/*!*****************************************************************************************************************************************************************
		 * @brief Destructor 																																			   *
		*******************************************************************************************************************************************************************/
		~C_InputLayout()
		{
			m_Inputs.clear();
		}

		/*!*****************************************************************************************************************************************************************
		 * @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		 * @param Semantic Semantic of the element to link to element in shader file.																					   *
		 * @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		 * @param Format Format of the element, describing its size in bits.																							   *
		 * @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		void AddInput
		(
			const char* Semantic, 
			uint32 Index, 
			D3D_Formats::E Format, 
			uint32 ByteOffset
		);

		/*!*****************************************************************************************************************************************************************
		* @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		* @param Semantic Semantic of the element to link to element in shader file.																					   *
		* @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		* @param Format Format of the element, describing its size in bits.																							       *
		* @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		bool CreateInputLayout
		(
			GraphicsDevice* prm_Device,
			GraphicsBlob* Shader
		);

		/*!*****************************************************************************************************************************************************************
		* @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		* @param Semantic Semantic of the element to link to element in shader file.																					   *
		* @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		* @param Format Format of the element, describing its size in bits.																								   *
		* @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		void SetInputLayout
		(
			GraphicsDeviceContext* prm_DC
		);

		/*!*****************************************************************************************************************************************************************
		* @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		* @param Semantic Semantic of the element to link to element in shader file.																					   *
		* @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		* @param Format Format of the element, describing its size in bits.																							       *
		* @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		void Close();

		/*!*****************************************************************************************************************************************************************
		* @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		* @param Semantic Semantic of the element to link to element in shader file.																					   *
		* @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		* @param Format Format of the element, describing its size in bits.																							       *
		* @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		uint32 GetInputCount()
		{
			return m_Inputs.size();
		}

		/*!*****************************************************************************************************************************************************************
		* @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		* @param Semantic Semantic of the element to link to element in shader file.																					   *
		* @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		* @param Format Format of the element, describing its size in bits.																							       *
		* @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		Vector<D3D11_INPUT_ELEMENT_DESC> m_Inputs;
	public:
		/*!*****************************************************************************************************************************************************************
		* @brief Creates an element descriptor to be inserted into the input layout list and passed to shader															   *
		* @param Semantic Semantic of the element to link to element in shader file.																					   *
		* @param Index Index of the element in the layout, used to describe if the element will use another part of the shader's code.									   *
		* @param Format Format of the element, describing its size in bits.																							       *
		* @param ByteOffset Offset of the element to be read by the input layout.																						   *
		*******************************************************************************************************************************************************************/
		GraphicsInputLayout* m_InputLayout;
	};
}