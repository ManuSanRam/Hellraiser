#pragma once

/*!*************************************************************************************************************************************************************************
 * @file		HRGraphics_Buffer.cpp																																	   *
 *																																										   *
 * This file contains definition of the shader classes (Vertex and Pixel shaders).																						   *
 * The methods implemented in the classes are:																															   *
 * - Compiling data into a blob to create a shader.																														   *
 * - Creating the shader using the blob's data.																															   *
 * - Setting the shader to a device context.																															   *
 *																																										   *
 * @date        16-03-2017																																				   *
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)																													   *
 * @copyright	Infernal Coders S.A.																																	   *
***************************************************************************************************************************************************************************/



#include "HRGraphics_Prerequisites.h"



#include <HRUtility_Datastream.h>

namespace HR_SDK
{
	struct GraphicsDevice;
	struct GraphicsDeviceContext;
	struct GraphicsBlob;
	struct GraphicsVertexShader;
	struct GraphicsPixelShader;

	

	#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

	
	
	class HR_D3DGRAPHICSAPI_EXPORT C_ShaderBase
	{
	public:
		/*!*****************************************************************************************************************************************************************
		 * @brief Compiles a shader, specifiyng the entrace point and profile to compile the information from an effects file. This one is a virtual function.			   *					   
		 * @param prm_FileName File path to effects file.																												   *
		 * @param prm_EntrancePoint Entrance point to function inside effects file.																						   *
		 * @param prm_Profile Shader profile.																															   *
		 * @return True, if data was successfully compiled to blob. False, if there was an error in compilation.														   *
		*******************************************************************************************************************************************************************/
		virtual bool Compile(const String& FileName, const String& Entrance, const String& Profile) = 0;
		/*!*****************************************************************************************************************************************************************
		 * @brief Creates the shader from the data compiled to the blob. This one is a virtual function																	   *				   
		 * @param prm_Device Device that creates the shader.																											   *
		 * @return True, if the shader was successfully created. False, if there was any error during the creation of the shader.										   *
		*******************************************************************************************************************************************************************/
		virtual bool Create(GraphicsDevice* prm_Device) = 0;
		/*!*****************************************************************************************************************************************************************
		 * @brief Sets the shader into the device context. This one is a virtual function																				   *						   
		 * @param prm_DC Device context where the shader will be set.																									   *
		*******************************************************************************************************************************************************************/
		virtual void Set(GraphicsDeviceContext* prm_DC) = 0;
		/*!*****************************************************************************************************************************************************************
		 * @brief Releases any Direct X shader resources- This one is a virtual function																				   *
		*******************************************************************************************************************************************************************/
		virtual void Close() = 0;

	public:
		/*!*****************************************************************************************************************************************************************
		 * @brief Container to hold the shader data to GPU																												   *
		*******************************************************************************************************************************************************************/
		GraphicsBlob* m_Blob;
	};

	/*!*********************************************************************************************************************************************************************
	 * @brief Defines a vertex shader object, used to load vertex data to GPU 																							   *
	***********************************************************************************************************************************************************************/
	class HR_D3DGRAPHICSAPI_EXPORT C_VertexShader : public C_ShaderBase
	{
	public:
		/*!*****************************************************************************************************************************************************************
		 * @brief Constructor (Default)																																	   *
		*******************************************************************************************************************************************************************/
		C_VertexShader()
		{

		}

		/*!*****************************************************************************************************************************************************************
		 * @brief Destructor																																			   *
		*******************************************************************************************************************************************************************/
		~C_VertexShader()
		{

		}

		/*!*****************************************************************************************************************************************************************
		 * @brief Compiles a shader, specifiyng the entrace point and profile to compile the information from an effects file.											   *
		 * @param prm_FileName File path to effects file.																												   *
		 * @param prm_EntrancePoint Entrance point to function inside effects file.																						   *
		 * @param prm_Profile Shader profile.																															   *
		 * @return True, if data was successfully compiled to blob. False, if there was an error in compilation.														   *
		*******************************************************************************************************************************************************************/
		bool Compile(const String& FileName, const String& Entrance, const String& Profile);
		/*!*****************************************************************************************************************************************************************
		 * @brief Creates the shader from the data compiled to the blob.																								   *
		 * @param prm_Device Device that creates the shader.																											   *
		 * @return True, if the shader was successfully created. False, if there was any error during the creation of the shader.										   *
		*******************************************************************************************************************************************************************/
		bool Create(GraphicsDevice* prm_Device);
		/*!*****************************************************************************************************************************************************************
		 * @brief Sets the shader into the device context.																												   *
		 * @param prm_DC Device context where the shader will be set.																									   *
		*******************************************************************************************************************************************************************/
		void Set(GraphicsDeviceContext* prm_DC);
		/*!*****************************************************************************************************************************************************************
		 * @brief Releases any DirectX shader resources.																												   *
		*******************************************************************************************************************************************************************/
		void Close();
	public:
		/*!*****************************************************************************************************************************************************************
		 * @brief Vertex shader pointer that contains effects data for vertices																							   *
		*******************************************************************************************************************************************************************/
		GraphicsVertexShader* m_VShader;
	};

	/*!

		@class C_PixelShader

		@brief Pixel shader object class

	*/
	class HR_D3DGRAPHICSAPI_EXPORT C_PixelShader : public C_ShaderBase
	{
	public:
		/*!

			@brief Constructor [Default]

		*/
		C_PixelShader()
		{
			
		}

		/*!

			@brief Destructor

		*/
		~C_PixelShader()
		{

		}

		/*!**********************************************************************************************************************************************************************

			@brief Compiles a shader, specifying the entrance point and profile to compile the information from an effects file.	

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param prm_FileName File path to effects file.																												 
			@param prm_EntrancePoint Entrance point to function inside effects file.																			
			@param prm_Profile Shader profile.																	

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return True, if data was successfully compiled to blob. False, if there was an error in compilation.												

		************************************************************************************************************************************************************************/
		bool Compile(const String& FileName, const String& Entrance, const String& Profile);
		/*!*****************************************************************************************************************************************************************
		 * @brief Creates the shader from the data compiled to the blob.																								   *
		 * @param prm_Device Device that creates the shader.																											   *
		 * @return True, if the shader was successfully created. False, if there was any error during the creation of the shader.										   *
		*******************************************************************************************************************************************************************/
		bool Create(GraphicsDevice* prm_Device);
		/*!*****************************************************************************************************************************************************************
		 * @brief Sets the shader into the device context.																												   *
		 * @param prm_DC Device context where the shader will be set.																									   *
		*******************************************************************************************************************************************************************/
		void Set(GraphicsDeviceContext* prm_DC);
		/*!*****************************************************************************************************************************************************************
		* @brief Releases any DirectX shader resources.																													   *
		*******************************************************************************************************************************************************************/
		void Close();
	public:
		/*!*****************************************************************************************************************************************************************
		 * @brief Pixel shader pointer containing data loaded to a blob																									   *
		*******************************************************************************************************************************************************************/
		GraphicsPixelShader* m_PShader;
	};
}