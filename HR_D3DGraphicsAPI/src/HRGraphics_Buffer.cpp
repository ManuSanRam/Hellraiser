#include "HRGraphics_Buffer.h"

/*!******************************************************************************************************************************************************************************
	
	@file		HRGraphics_Buffer.cpp

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																																										   
	This file contains definition of the methods declared inside the buffers' classes.																					   
	The methods implemented in the class are:																															   
	- Setting of the channels individually.																																   
	- Obtaining color structures from another 4D vector to get information from.																						 
	- Obtaining color data from another color.																															   
					
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date        08-11-2016																																				   
	@author		Manuel Aldair Santos Ram�n (ManuSanRam)																													   
	@copyright	Infernal Coders S.A.	

********************************************************************************************************************************************************************************/


#include <d3d11.h>


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
		GraphicsBuffer() : Buffer(nullptr) {}
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



	/*!**************************************************************************************************************************************************************************
																																										   
															BUFFER BASE FUNCTIONS																						   
																																										   
	****************************************************************************************************************************************************************************/
	C_BufferBase::~C_BufferBase()
	{
		delete m_Buffer;
		m_Buffer = NULL;
	}



	/*!**************************************************************************************************************************************************************************
																																									   
															VERTEX BUFFER FUNCTIONS																						   
																																										   
	****************************************************************************************************************************************************************************/
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
	bool C_VertexBuffer<VertexType>::Create
	(
		GraphicsDevice* prm_Device,
		D3D_Binds::E prm_Bind,
		D3D_Access::E prm_Access,
		D3D_Usages::E prm_Usage
	)
	{
		m_Buffer = new GraphicsBuffer();

		//! Holds the result of the device passing the data to the GPU
		HRESULT FuncResult;

		D3D11_BUFFER_DESC Desc;
		D3D11_SUBRESOURCE_DATA SRD;

		//! Create descriptor of buffer
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Usage = D3D11_USAGE(prm_Usage);
		Desc.ByteWidth = sizeof(VertexType) * m_Vertices.size();
		Desc.BindFlags = D3D11_BIND_FLAG(prm_Bind);
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG(prm_Access);
		Desc.MiscFlags = 0;

		//! Create subresource data
		ZeroMemory(&SRD, sizeof(SRD));
		SRD.pSysMem = &m_Vertices[0];
		
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



	template<typename VertexType>
	void C_VertexBuffer<VertexType>::Close()
	{
		ID3D11Buffer* TmpBuffer = reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer());

		if (TmpBuffer)
		{
			TmpBuffer->Release();
		}
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
	bool C_IndexBuffer<IndexType>::Create
	(
		GraphicsDevice*		prm_Device,
		D3D_Binds::E		prm_Bind,
		D3D_Access::E		prm_Access,
		D3D_Usages::E		prm_Usage
	)
	{
		m_Buffer = new GraphicsBuffer();
		//! Holds the result of the device passing the data to the GPU
		HRESULT FuncResult;

		D3D11_BUFFER_DESC Desc;
		D3D11_SUBRESOURCE_DATA SRD;

		//! Create descriptor of buffer
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Usage = D3D11_USAGE(prm_Usage);
		Desc.ByteWidth = sizeof(IndexType) * m_Indices.size();
		Desc.BindFlags = D3D11_BIND_FLAG(prm_Bind);
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG(prm_Access);
		Desc.MiscFlags = 0;
		//! Create subresource data
		ZeroMemory(&SRD, sizeof(SRD));
		SRD.pSysMem = &m_Indices[0];
		
		//! Pass the data through the parameter device
		ID3D11Buffer** TmpBuff = reinterpret_cast<ID3D11Buffer**>(m_Buffer->GetReference());
		FuncResult = reinterpret_cast<ID3D11Device*>(prm_Device->GetPointer())->CreateBuffer
		(
			&Desc,
			&SRD,
			TmpBuff
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
		DXGI_Formats::E			prm_IF
	)
	{
		uint32 Offset = 0;

		reinterpret_cast<ID3D11DeviceContext*>(prm_Device->GetPointer())->IASetIndexBuffer
		(
			reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer()),
			DXGI_FORMAT(prm_IF),
			Offset
		);
	}



	/*!
	*/
	template<typename IndexType>
	void C_IndexBuffer<IndexType>::Close()
	{
		ID3D11Buffer* TmpBuffer = reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer());

		if (TmpBuffer)
		{
			TmpBuffer->Release();
		}
	}

	/*!*********************************************************************************************************************************************************************
	*																																									   *
	*														CONSTANT BUFFER FUNCTIONS																					   *
	*																																									   *
	***********************************************************************************************************************************************************************/
	/*!*********************************************************************************************************************************************************************
		
		@brief Creates a buffer descriptor to be used to create the vertex buffer into the device

		@param prm_Usage Usage of the buffer in GPU.																													   
		@param prm_Count Byte count of data that the buffer holds.																									   	   
		@param prm_Bind Binding of the buffer in GPU (Vertex, Index, Constant)	

		@return Returns a buffer descriptor to be used to pass vertex data to GPU

	***********************************************************************************************************************************************************************/
	bool C_ConstantBuffer::Create
	(
		GraphicsDevice* _device,
		D3D_Binds::E	_bind,
		D3D_Access::E	_access,
		D3D_Usages::E	_usage,
		SIZE_T			_size
	)
	{
		//! Holds the result of the device passing the data to the shader file
		HRESULT FuncResult;

		D3D11_BUFFER_DESC Desc;

		//! Create descriptor of buffer
		ZeroMemory(&Desc, sizeof(Desc));

		Desc.Usage = D3D11_USAGE(_usage);
		Desc.ByteWidth = _size;
		Desc.BindFlags = D3D11_BIND_FLAG(_bind);
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG(_access);
		Desc.MiscFlags = 0;

		m_Buffer = new GraphicsBuffer();

		//! Pass the data through the parameter device
		FuncResult = reinterpret_cast<ID3D11Device*>(_device->GetPointer())->CreateBuffer(
			&Desc,
			NULL,
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



	/*!
	 * @brief 
	*/
	void C_ConstantBuffer::Map
	(
		GraphicsDeviceContext*	_dc,
		void*					_data,
		SIZE_T					_dataSize
	)
	{
		//! Point to the adress using a reinterpreted pointer
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(_dc->GetPointer());
		//! Point to the adress using a reinterpreted pointer
		ID3D11Buffer* TmpCBuff = reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer());

		//!
		TmpDC->UpdateSubresource(TmpCBuff, 0, NULL, _data, _dataSize, 0);
	}



	/*!
	*/
	void C_ConstantBuffer::Set
	(
		GraphicsDeviceContext*	prm_DC,
		uint32					prm_Slot,
		uint32					prm_NumBuffers
	)
	{
		//! Set to the pipeline
		ID3D11DeviceContext* TmpDC = reinterpret_cast<ID3D11DeviceContext*>(prm_DC->GetPointer());
		ID3D11Buffer** TmpCBuff = reinterpret_cast<ID3D11Buffer**>(m_Buffer->GetReference());

		TmpDC->VSSetConstantBuffers(prm_Slot, prm_NumBuffers, TmpCBuff);
	}



	/*!
	*/
	void C_ConstantBuffer::Close() 
	{
		ID3D11Buffer* TmpBuffer = reinterpret_cast<ID3D11Buffer*>(m_Buffer->GetPointer());

		if (TmpBuffer)
		{
			TmpBuffer->Release();
		}
	}

	template class C_VertexBuffer<S_Vertex>;
	template class C_IndexBuffer<uint16>;
	template class C_IndexBuffer<uint32>;
}