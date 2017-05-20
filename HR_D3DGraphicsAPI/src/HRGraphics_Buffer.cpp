#include "HRGraphics_Buffer.h"

/*!*************************************************************************************************************************************************************************
 * @file		HRGraphics_Buffer.cpp																																	   *
 *																																										   *
 * This file contains definition of the methods declared inside the buffers' classes.																					   *
 * The methods implemented in the class are:																															   *
 * - Setting of the channels individually.																																   *
 * - Obtaining color structures from another 4D vector to get information from.																							   *
 * - Obtaining color data from another color.																															   *
 *																																										   *
 * @date        08-11-2016																																				   *
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)																													   *
 * @copyright	Infernal Coders S.A.																																	   *
***************************************************************************************************************************************************************************/

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
			return reinterpret_cast<void*>(DC);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&DC);
		}

		ID3D11DeviceContext* DC;
	};

	struct GraphicsBuffer
	{
		void* GetPointer()
		{
			return reinterpret_cast<void*>(Buffer);
		}

		void** GetReference()
		{
			return reinterpret_cast<void**>(&Buffer);
		}

		ID3D11Buffer* Buffer;
	};

	/*!*********************************************************************************************************************************************************************
	*																																									   *
	*														BUFFER BASE FUNCTIONS																						   *
	*																																									   *
	***********************************************************************************************************************************************************************/
	template<typename Type>
	C_BufferBase<Type>::~C_BufferBase()
	{
		//! Check if the buffer is pointing to information in memory
		if (m_Buffer)
		{
			//! Release memory from RAM
			reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer())->Release();
		}
		//! Point buffer pointer to null memory
		m_Buffer = NULL;
	}
	/*!*********************************************************************************************************************************************************************
	*																																									   *
	*														VERTEX BUFFER FUNCTIONS																						   *
	*																																									   *
	***********************************************************************************************************************************************************************/
	/*!*********************************************************************************************************************************************************************
	* @brief Adds an array of vertices on the buffer's array																											   *
	* Buffer holds this information, so if necessary, buffer will kill the memory of it's on array																		   *
	* @param prm_VertexArray Array passed to the buffer, to create information																							   *
	***********************************************************************************************************************************************************************/
	template<typename VertexType>
	void C_VertexBuffer<VertexType>::AddVertex(VertexType prm_Vertex)
	{
		m_Vertices.push_back(prm_Vertex);
	}

	/*!*********************************************************************************************************************************************************************
	 * @brief Adds an array of vertices on the buffer's array																											   *
	 * Buffer holds this information, so if necessary, buffer will kill the memory of it's on array																		   *
	 * @param prm_VertexArray Array passed to the buffer, to create information																							   *
	***********************************************************************************************************************************************************************/
	template<typename VertexType>
	void C_VertexBuffer<VertexType>::AddVertices(Vector<VertexType> prm_VertexArray)
	{
		m_Vertices = prm_VertexArray;
	}

	/*!*********************************************************************************************************************************************************************
	* @brief Creates a buffer descriptor to be used to create the vertex buffer into the device																		   	   *
	* @param prm_Usage Usage of the buffer in GPU.																													   	   *
	* @param prm_Count Byte count of data that the buffer holds.																									   	   *
	* @param prm_Bind Binding of the buffer in GPU (Vertex, Index, Constant)																						   	   *
	* @return Returns a buffer descriptor to be used to pass vertex data to GPU																						   	   *
	***********************************************************************************************************************************************************************/
	template<typename VertexType>
	bool C_VertexBuffer<VertexType>::CreateBuffer
	(
		GraphicsDevice* prm_Device,
		uint32 prm_Count,
		D3D_Binds::E prm_Bind,
		D3D_Access::E prm_Access,
		D3D_Usages::E prm_Usage,
		Vector<VertexType> prm_Vector
	)
	{
		//! Holds the result of the device passing the data to the GPU
		HRESULT FuncResult;

		D3D11_BUFFER_DESC Desc;
		D3D11_SUBRESOURCE_DATA SRD;

		//! Create descriptor of buffer
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Usage = TranslateUsage(prm_Usage);
		Desc.ByteWidth = sizeof(VertexType) * prm_Count;
		Desc.BindFlags = TranslateBind(prm_Bind);
		Desc.CPUAccessFlags = TranslateAccess(prm_Access);
		Desc.MiscFlags = 0;

		//! Create subresource data
		ZeroMemory(&SRD, sizeof(SRD));
		SRD.pSysMem = &prm_Vector[0];

		//! Pass the data through the parameter device
		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateBuffer(
			&Desc,
			&SRD,
			reinterpret_cast<ID3D11Buffer**>(m_Buffer->GetReference())
		);
		//! Check if the device correctly passed the data into the GPU
		if (FAILED(FuncResult))
		{
			//! If the device couldn't pass the data correctly
			return false;
		}
		//! If the device was able to pass the data correctly
		return true;
	}

	/*!
	*/
	template<typename VertexType>
	void C_VertexBuffer<VertexType>::SetBuffer
	(
		GraphicsDeviceContext* prm_Device
	)
	{
		HRESULT FuncResult;
		uint32 Stride = sizeof(VertexType);
		uint32 Offset = 0;

		reinterpret_cast<ID3D11DeviceContext*>(prm_Device->GetPointer())->IASetVertexBuffers
		(
			0,
			1,
			reinterpret_cast<ID3D11Buffer**>(m_Buffer->GetReference()),
			&Stride,
			&Offset
		);
	}

	/*!*********************************************************************************************************************************************************************
	*																																									   *
	*														INDEX BUFFER FUNCTIONS																						   *
	*																																									   *
	***********************************************************************************************************************************************************************/
	/*!*********************************************************************************************************************************************************************
	* @brief Adds an index into the buffer's data array.																											   	   *
	* @param prm_Index Index to be inserted to the list.																											   	   *
	***********************************************************************************************************************************************************************/
	template<typename IndexType>
	void C_IndexBuffer<IndexType>::AddIndex(IndexType prm_Index)
	{
		m_Indices.push_back(prm_Index);
	}

	/*!*********************************************************************************************************************************************************************
	* @brief Pass an array of precreated indices to the buffer's data array																							   	   *
	* @param prm_Indices Vector that contains indices to be passed to the GPU																						   	   *
	***********************************************************************************************************************************************************************/
	template<typename IndexType>
	void C_IndexBuffer<IndexType>::AddIndices(Vector<IndexType>& prm_IndexArray)
	{
		m_Indices = prm_IndexArray;
	}

	/*!*********************************************************************************************************************************************************************
	* @brief Creates a buffer descriptor to be used to create the vertex buffer into the device																		   	   *
	* @param prm_Usage Usage of the buffer in GPU.																													   	   *
	* @param prm_Count Byte count of data that the buffer holds.																									   	   *
	* @param prm_Bind Binding of the buffer in GPU (Vertex, Index, Constant)																						   	   *
	* @return Returns a buffer descriptor to be used to pass vertex data to GPU																						   	   *
	***********************************************************************************************************************************************************************/
	template<typename IndexType>
	bool C_IndexBuffer<IndexType>::CreateBuffer
	(
		GraphicsDevice*		prm_Device,
		uint32				prm_Count,
		D3D_Binds::E		prm_Bind,
		D3D_Access::E		prm_Access,
		D3D_Usages::E		prm_Usage,
		Vector<IndexType>	prm_Vector)
	{
		//! Holds the result of the device passing the data to the GPU
		HRESULT FuncResult;

		D3D11_BUFFER_DESC Desc;
		D3D11_SUBRESOURCE_DATA SRD;

		//! Create descriptor of buffer
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Usage = TranslateUsage(prm_Usage);
		Desc.ByteWidth = sizeof(IndexType) * prm_Count;
		Desc.BindFlags = TranslateBind(prm_Bind);
		Desc.CPUAccessFlags = TranslateAccess(prm_Access);
		Desc.MiscFlags = 0;

		//! Create subresource data
		ZeroMemory(&SRD, sizeof(SRD));
		SRD.pSysMem = &prm_Vector[0];

		//! Pass the data through the parameter device
		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateBuffer
		(
			&Desc,
			&SRD,
			reinterpret_cast<ID3D11Buffer**>(m_Buffer->GetReference())
		);
		//! Check if the device correctly passed the data into the GPU
		if (FAILED(FuncResult))
		{
			//! If the device couldn't pass the data correctly
			return false;
		}
		//! If the device was able to pass the data correctly
		return true;
	}

	/*!
	*/
	template<typename IndexType>
	void C_IndexBuffer<IndexType>::SetBuffer
	(
		GraphicsDeviceContext*	prm_Device,
		DXGI_Formats::E			prm_Format
	)
	{
		uint32 Offset = 0;

		reinterpret_cast<ID3D11DeviceContext*>(prm_Device->GetPointer())->IASetIndexBuffer
		(
			reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer()),
			TranslateFormat(prm_Format),
			Offset
		);
	}

	/*!*********************************************************************************************************************************************************************
	*																																									   *
	*														CONSTANT BUFFER FUNCTIONS																					   *
	*																																									   *
	***********************************************************************************************************************************************************************/
	/*!*********************************************************************************************************************************************************************
	* @brief Creates a buffer descriptor to be used to create the vertex buffer into the device																		   	   *
	* @param prm_Usage Usage of the buffer in GPU.																													   	   *
	* @param prm_Count Byte count of data that the buffer holds.																									   	   *
	* @param prm_Bind Binding of the buffer in GPU (Vertex, Index, Constant)																						   	   *
	* @return Returns a buffer descriptor to be used to pass vertex data to GPU																						   	   *
	***********************************************************************************************************************************************************************/
	template<typename ConstantType>
	bool C_ConstantBuffer<ConstantType>::CreateBuffer(GraphicsDevice* prm_Device,
		uint32 prm_Count,
		D3D_Binds::E prm_Bind,
		D3D_Access::E prm_Access,
		D3D_Usages::E prm_Usage,
		Vector<ConstantType> prm_Vector)
	{
		//! Holds the result of the device passing the data to the GPU
		HRESULT FuncResult;

		D3D11_BUFFER_DESC Desc;
		D3D11_SUBRESOURCE_DATA SRD;

		//! Create descriptor of buffer
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Usage = TranslateUsage(prm_Usage);
		Desc.ByteWidth = sizeof(ConstantType) * prm_Count;
		Desc.BindFlags = TranslateBind(prm_Bind);
		Desc.CPUAccessFlags = TranslateUsage(prm_Usage);
		Desc.MiscFlags = 0;

		//! Create subresource data
		ZeroMemory(&SRD, sizeof(SRD));
		SRD.pSysMem = &prm_Vector[0];

		//! Pass the data through the parameter device
		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateBuffer(
			&Desc,
			&SRD,
			reinterpret_cast<ID3D11Buffer**>(m_Buffer->GetReference()));
		//! Check if the device correctly passed the data into the GPU
		if (FAILED(FuncResult))
		{
			//! If the device couldn't pass the data correctly
			return false;
		}
		//! If the device was able to pass the data correctly
		return true;
	}

	template class C_VertexBuffer<S_Vertex>;
	template class C_IndexBuffer<uint16>;
	template class C_IndexBuffer<uint32>;
	template class C_ConstantBuffer<C_ConstantType>;
}