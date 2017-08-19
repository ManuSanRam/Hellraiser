/*!*************************************************************************************************************************************************************************
 * @file		HRGraphics_Shader.cpp																																	   *
 *																																										   *
 * This file contains definition of the methods declared inside the shaders' classes.																					   *
 * The methods implemented in the class are:																															   *
 * - Compiling data into a blob.																																		   *
 * - Creating the shader																																				   *
 * - Setting the shader to a context																																	   *
 *																																										   *
 * @date        16-03-2017																																				   *
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)																													   *
 * @copyright	Infernal Coders S.A.																																	   *
***************************************************************************************************************************************************************************/
#include "HRGraphics_Shader.h"
#include <d3d11.h>
#include <D3DX11async.h>

namespace HR_SDK
{
	struct GraphicsDevice
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Device);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Device);
		}

		ID3D11Device* Device;
	};

	struct GraphicsDeviceContext
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(DevCon);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DevCon);
		}

		ID3D11DeviceContext* DevCon;
	};

	struct GraphicsBlob
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Blob);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Blob);
		}

		ID3D10Blob* Blob;
	};

	struct GraphicsVertexShader
	{
		GraphicsVertexShader() : VertexShader(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(VertexShader);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&VertexShader);
		}

		ID3D11VertexShader* VertexShader;
	};

	struct GraphicsPixelShader
	{
		GraphicsPixelShader() : PixelShader(nullptr) {}
		void* GetPointer()
		{
			return reinterpret_cast<void*>(PixelShader);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&PixelShader);
		}

		ID3D11PixelShader* PixelShader;
	};

	///**************************************************************************************************************************************************************************
	 																																									   
	/// 																		VERTEX SHADER CLASS																		   
	 																																									   
	///*************************************************************************************************************************************************************************/
	/*!**************************************************************************************************************************************************************************
		
		@brief Compiles a shader, specifying the entrance point and profile to compile the information from an effects file.												   
		
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		@param prm_FileName File path to effects file.																													   
		@param prm_EntrancePoint Entrance point to function inside effects file.																							   
		@param prm_Profile Shader profile.																																   

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		@return True, if data was successfully compiled to blob. False, if there was an error in compilation.															   
	
	****************************************************************************************************************************************************************************/
	bool C_VertexShader::Compile(const String& prm_FileName, const String& prm_EntrancePoint, const String& prm_Profile)
	{
		//! Verify the result of the shader compilation
		HRESULT ShaderResult;
		//! This blob saves the error, should it occur, of the shader compilation
		ID3D10Blob* ErrorBlob;



		//! Both blob objects are allocated.
		m_Blob =		new GraphicsBlob;
		
		//! Compile the shader, register the result of the function in HRESULT for debugging
		ShaderResult = D3DX11CompileFromFile
		(
			prm_FileName.c_str(),		//! Shader file path 
			NULL,
			NULL,
			prm_EntrancePoint.c_str(),	//! Shader function entrance - Vertex shader
			prm_Profile.c_str(),		//! Shader profile
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			NULL,
			reinterpret_cast<ID3D10Blob**>(m_Blob->GetReference()),	//! Blob to compile shader
			&ErrorBlob,	//! Blob to get errors
			NULL
		);

		//! Check if shader compilation fails
		if (FAILED(ShaderResult))
		{
			//! Capture the error buffer size
			SIZE_T ErrorSize = ErrorBlob->GetBufferSize();
			//! Init string to capture error message, allocating correct buffer size and starting content of the string in null pointer
			String ErrorDesc(ErrorSize + 1, 0);
			//! Save content of error buffer in char pointer - casting buffer content to correct type
			char* ErrorMsg = (char*)ErrorBlob->GetBufferPointer();
			//! Get error message from blob
			ErrorDesc.insert(ErrorDesc.begin(), ErrorMsg, ErrorMsg + ErrorSize);
			//! Release reinterpreted error blob, since info has been saved already
			ErrorBlob->Release();
			
			//! Just if the blob is currently pointing to memory that will be unused
			if (m_Blob->Blob)
			{
				//! Release shader blob resource
				reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer())->Release();
			}
			
			//! Delete shader blob
			delete m_Blob;
			
			//! ERROR: Shader compilation failed - error is saved in a string 
			return false;
		}
		//! Successful shader compilation!
		return true;
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Creates the shader from the data compiled to the blob.																									   *
	 * @param prm_Device Device that creates the shader.																												   *
	 * @return True, if the shader was successfully created. False, if there was any error during the creation of the shader.											   *
	***********************************************************************************************************************************************************************/
	bool C_VertexShader::Create(GraphicsDevice* prm_Device)
	{
		HRESULT Creation;

		m_VShader = new GraphicsVertexShader();

		ID3D10Blob* TmpBlob = reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer());
		ID3D11VertexShader** TmpShader /*= nullptr; */= reinterpret_cast<ID3D11VertexShader**>(m_VShader->GetReference());

		Creation = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateVertexShader
		(
			TmpBlob->GetBufferPointer(),
			TmpBlob->GetBufferSize(),
			NULL,
			TmpShader
		);

		if (FAILED(Creation))
		{
			return false;
		}

		return true;

	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Sets the shader into the device context.																													   *
	 * @param prm_DC Device context where the shader will be set.																										   *
	***********************************************************************************************************************************************************************/
	void C_VertexShader::Set(GraphicsDeviceContext* prm_DC)
	{
		if (m_VShader)
		{
			reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->VSSetShader
			(
				reinterpret_cast<ID3D11VertexShader*>(m_VShader->GetPointer()),
				NULL,
				0
			);
		}
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Releases any DirectX shader resources.																													   *
	***********************************************************************************************************************************************************************/
	void C_VertexShader::Close()
	{
		if (m_VShader)
		{
			reinterpret_cast<ID3D11VertexShader*>(m_VShader->GetPointer())->Release();
		}
		delete m_VShader;

		if (m_Blob)
		{
			reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer())->Release();
		}
		delete m_Blob;
	}

	/*!*********************************************************************************************************************************************************************
	 *																																									   *
	 *																          PIXEL SHADER CLASS																		   *
	 *																																									   *
	***********************************************************************************************************************************************************************/
	/*!*********************************************************************************************************************************************************************
	 * @brief Compiles a shader, specifying the entrance point and profile to compile the information from an effects file.												   *
	 * @param prm_FileName File path to effects file.																													   *
	 * @param prm_EntrancePoint Entrance point to function inside effects file.																							   *
	 * @param prm_Profile Shader profile.																																   *
	 * @return True, if data was successfully compiled to blob. False, if there was an error in compilation.															   *
	***********************************************************************************************************************************************************************/
	bool C_PixelShader::Compile(const String& FileName, const String& Entrance, const String& Profile)
	{
		//! Verify the result of the shader compilation
		HRESULT ShaderResult;
		//! This blob saves the error, should it occur, of the shader compilation
		ID3D10Blob* ErrorBlob;

		//! Both blob objects are allocated.
		m_Blob = new GraphicsBlob;

		//! Compile the shader, register the result of the function in HRESULT for debugging
		ShaderResult = D3DX11CompileFromFile
		(
			FileName.c_str(),	//! Shader file path 
			NULL,
			NULL,
			Entrance.c_str(),	//! Shader function entrance - Vertex shader
			Profile.c_str(),	//! Shader profile
			D3D10_SHADER_ENABLE_STRICTNESS,
			0,
			NULL,
			reinterpret_cast<ID3D10Blob**>(m_Blob->GetReference()),	//! Blob to compile shader
			&ErrorBlob,	//! Blob to get errors
			NULL
		);

		//! Check if shader compilation fails
		if (FAILED(ShaderResult))
		{
			//! Capture the error buffer size
			SIZE_T ErrorSize = ErrorBlob->GetBufferSize();
			//! Init string to capture error message, allocating correct buffer size and starting content of the string in null pointer
			String ErrorDesc(ErrorSize + 1, 0);

			//! Save content of error buffer in char pointer - casting buffer content to correct type
			char* ErrorMsg = (char*)ErrorBlob->GetBufferPointer();

			//! Get error message from blob
			ErrorDesc.insert(ErrorDesc.begin(), ErrorMsg, ErrorMsg + ErrorSize);

			//! Release reinterpreted error blob, since info has been saved already
			ErrorBlob->Release();

			//! Just if the blob is currently pointing to memory that will be unused
			if (m_Blob->Blob)
			{
				//! Release shader blob resource
				reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer())->Release();
			}
			//! Delete shader blob
			delete m_Blob;
			//! ERROR: Shader compilation failed - error is saved in a string 
			return false;
		}
		//! Successful shader compilation!
		return true;
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Creates the shader from the data compiled to the blob.																									   *
	 * @param prm_Device Device that creates the shader.																												   *
	 * @return True, if the shader was successfully created. False, if there was any error during the creation of the shader.											   *
	***********************************************************************************************************************************************************************/
	bool C_PixelShader::Create
	(
		GraphicsDevice* prm_Device
	)
	{
		HRESULT Creation;

		m_PShader = new GraphicsPixelShader();

		Creation = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreatePixelShader
		(
			reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer())->GetBufferPointer(),
			reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer())->GetBufferSize(),
			NULL,
			reinterpret_cast<ID3D11PixelShader**>(m_PShader->GetReference())
		);

		if (FAILED(Creation))
		{
			return false;
		}

		return true;
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Sets the shader into the device context.																													   *
	 * @param prm_DC Device context where the shader will be set.																										   *
	***********************************************************************************************************************************************************************/
	void C_PixelShader::Set
	(
		GraphicsDeviceContext* prm_DC
	)
	{
		if (m_PShader)
		{
			reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer())->PSSetShader
			(
				reinterpret_cast<ID3D11PixelShader*>(m_PShader->GetPointer()),
				NULL,
				0
			);
		}
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Releases any DirectX shader resources.																													   *
	***********************************************************************************************************************************************************************/
	void C_PixelShader::Close()
	{
		if (m_PShader)
		{
			reinterpret_cast<ID3D11PixelShader*>(m_PShader->GetPointer())->Release();
		}
		delete m_PShader;

		if (m_Blob)
		{
			reinterpret_cast<ID3D10Blob*>(m_Blob->GetPointer())->Release();
		}
		delete m_Blob;
	}
}