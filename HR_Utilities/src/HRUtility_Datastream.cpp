#include "HRUtility_Datastream.h"

namespace HR_SDK
{
	/*!******************************************************************************
	 * MEMORY STREAM
	********************************************************************************/
	/*!
	 * @brief Open a filestream using a directory with a certain access
	 * @param Seeker Number of bytes to deface the position
	 * @return Defaced position of the stream.
	*/
	SIZE_T    C_Memorystream::Seek(SIZE_T Offset, SIZE_T Seeker)
	{
		//! Deface the current position of the stream
		m_Pos = (*m_Buffer + Offset) + Seeker;
		//! Return the new current position inside the stream
		return m_Pos;
	}

	/*!
	 * @brief Tell the position inside the buffer
	 * @return The number of bytes from the start of the file to the current position.
	*/
	SIZE_T    C_Memorystream::Tell()
	{
		//! 
		return m_Pos - *m_Buffer;
	}

	/*!
	 * @brief Read from the local buffer and save information to another buffer
	 * @param DestBuf Destination to save the data
	 * @param ByteCount Count of bytes to 
	 * @return Amount of bytes successfully read from the local buffer, either the amount passed as parameter or a truncated amount
	*/
	SIZE_T    C_Memorystream::Read(Byte* DestBuf, SIZE_T ByteCount)
	{
		//! Locally save the count of bytes to read from the local buffer
		SIZE_T BytesRead = ByteCount;
		//! Check if the count doesn't exceed the data inside the buffer
		if (BytesRead > (m_Pos - *m_Buffer))
			//! Truncate the byte count so it only reads the permitted amount 
			BytesRead = (m_Pos - *m_Buffer);
		//! Copy the data in memory to the destination buffer
		memcpy(DestBuf, m_Buffer, BytesRead);
		//! Return the number of bytes that were succesfully read
		return BytesRead;
	}

	/*!
	 * @brief Write into the local buffer, taking  nth amount of data from a source buffer
	 * @param SrcBuf Buffer from which the data is taken and written to the local buffer
	 * @param ByteCount Amount of bytes to be written from the source into the local buffer
	 * @return Amount of bytes successfully written into the buffer, either the passed amount or a truncated amount. 
	*/
	SIZE_T    C_Memorystream::Write(Byte* SrcBuf, SIZE_T ByteCount)
	{
		//! Locally save the amount of bytes to write
		SIZE_T BytesWrite = ByteCount;
		//! Check if there's vacant space to write the data
		if (m_Pos + ByteCount > *m_End)
			//! If not, truncate the amount of bytes to write into the buffer
			BytesWrite = *m_End - m_Pos;
		//! Copy the memory block into the local buffer
		memcpy(m_Buffer, SrcBuf, BytesWrite);
		//! Return the amount of succesfully written bytes
		return BytesWrite;
	}

	/*!
	 * @brief Checks if the end of the buffer has been reached or not.
	 * @return False if the amount of info is equal or might overflow the buffer, true if there's still space inside the local buffer.
	*/
	bool      C_Memorystream::EndOfBuffer()
	{
		//! Check if the amount of allocated space is overflowing the buffer or a the end
		return ((m_Pos - *m_Buffer) < *m_End);
	}

	/*!******************************************************************************
	 * FILE STREAM
	********************************************************************************/
	SIZE_T C_Filestream::GetSize()
	{
		return m_Size;
	}

	/*!
	 * @brief Open a filestream using a directory with a certain access
	 * @param FileName
	 * @param
	*/
	bool      C_Filestream::Open(const String& FileName, bool Create)
	{
	  //! Check if input/output is permitted
		m_Dir.Init(FileName);
		m_Dir.FullPath();

		if (!Create)
		{
			if (IsReadable() && IsWritable())
				m_Stream.open(m_Dir.GetPath().c_str(), std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
			else if (IsReadable())
				m_Stream.open(m_Dir.GetPath().c_str(), std::ios::in | std::ios::ate | std::ios::binary);
			else if (IsWritable())
				m_Stream.open(m_Dir.GetPath().c_str(), std::ios::out | std::ios::ate | std::ios::binary);
			
		}
			

		else
		{
			//! Create file
			if (IsReadable() && IsWritable())
				m_Stream.open(m_Dir.GetPath().c_str(), std::ios::in | std::ios::out | std::ios::ate | std::ios::binary | std::ios::trunc);
			else if (IsReadable())
				m_Stream.open(m_Dir.GetPath().c_str(), std::ios::in | std::ios::ate | std::ios::binary | std::ios::trunc);
			else if (IsWritable())
				m_Stream.open(m_Dir.GetPath().c_str(), std::ios::out | std::ios::ate | std::ios::binary | std::ios::trunc);
		}

		if (m_Stream.is_open())
		{
			m_Size = Tell();
			//! Position back to the beggining of the file
			Seek(0, std::ios::beg);
			return true;
		}

		else
		{
			//! File opening failure
			return false;
		}
	}

	/*!
	 * @brief Open a filestream using a directory with a certain access
	 * @param FileName
	 * @param
	*/
	SIZE_T    C_Filestream::Seek(SIZE_T Offset, SIZE_T Seeker)
	{
	  //!
	  if (IsReadable())
		m_Stream.seekg(Offset, Seeker);
	  if(IsWritable())
	    m_Stream.seekp(Offset, Seeker);
	  //!
	  return Seeker;
	}

	/*!
	 * @brief Open a filestream using a directory with a certain access
	 * @param FileName
	 * @param
	*/
	SIZE_T    C_Filestream::Tell()
	{
	  //!
		SIZE_T Pos = 0;
	  if (IsReadable())
		//!
		Pos = (SIZE_T)m_Stream.tellg();
	  //!
	  if (IsWritable())
		//!
		Pos = (SIZE_T)m_Stream.tellp();
	  return Pos;
	}

	/*!
	 * @brief Open a filestream using a directory with a certain access
	 * @param FileName
	 * @param
	*/
	SIZE_T    C_Filestream::Read(Byte* prm_DestinationBuf, SIZE_T prm_ByteCount)
	{
		//!
		SIZE_T BytesRead = prm_ByteCount;
		//!
		if (!IsReadable())
		{
			//!
			return 0;
		}

		//!
		if (m_Stream.is_open())
		{
			//! Read 'n' characters from stream into buffer
			m_Stream.read(prm_DestinationBuf, BytesRead);
			//!
			return BytesRead;
		}
		//!
		return 0;
	}

	/*!
	 * @brief Writes information to the stream and into te file
	 * @param SrcBuf Buffer from which to take the information to write into the file
	 * @param Count Amount of bytes to be written into the file
	 * @return The amount of bytes correctly written into the file, otherwise return 0 if file couldn't be opened or stream has no write permissions
	*/
	SIZE_T    C_Filestream::Write(Byte* SrcBuf, SIZE_T Count)
	{
		//! Locally save the byte count to write inside the file
		SIZE_T BytesWrite = Count;

		//! Check if the stream is able to write on the stream
		if (!IsWritable())
		{
			//! No writing permissions, means no bytes written
			return 0;
		}
		//! Check if the file was correctly opened
		if (m_Stream.is_open())
		{
			//! Write information to the file
			m_Stream.write(SrcBuf, BytesWrite);
			//! Return the amount of bytes wrote to the file
			return BytesWrite;
		}
		//! If the file was not opened
		//! Return 0 bytes, since nothing was written to the file
		return 0;
	}

	/*!
	 * @brief Check if the user has reached the end of the local buffer
	 * @return false if the position of the buffer reaches or is greater than the end, true if there's still space.
	*/
	bool      C_Filestream::EndOfBuffer()
	{
		//! Check if the data-written space of the buffer is lesser than the end.
		return (m_Stream.eof());
	}

	void      C_Filestream::Close()
	{
		if (m_Stream.is_open())
			m_Stream.close();
	}
}
