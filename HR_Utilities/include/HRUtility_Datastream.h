#pragma once

/*!************************************************************************************************************************************************************************
 * @file		HRUtility_Datastream.h
 *
 * This file contains the declaration of buffer operations. The operations can be made under three types of buffers.
 *   - Datas tream buffer.
 *   - Memory stream buffer.
 *   - File stream buffer.
 * The operations are as follows(in order):
 * - Open the stream with given access (Write or Read).
 * - Seek through a stream, either to read or write on said position.
 * - Tell the current position in the stream.
 * - Reads a given number of bytes from the stream and saves it a destination.
 * - Writes a given number of bytes to the stream, read from a source buffer.
 * - Checks if the buffer has reached it's end.
 *
 * @date        26-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
***************************************************************************************************************************************************************************/

#include "HRUtility_Directory.h"

namespace HR_SDK
{
  /*!
   * @brief
  */
	namespace FileAccess
	{
		enum E
		{
			/*!********************************************************************************************************************************************************************
			* @brief Stream access for writing operations
			***********************************************************************************************************************************************************************/
			_WRITE = 0x01,

			/*!********************************************************************************************************************************************************************
			* @brief Stream access for reading operations
			***********************************************************************************************************************************************************************/
			_READ = 0x02,
		};
	}

  /*!
   * @brief Controls information for input output operations of any kind
   * This class is used as an interface for the other datastream classes. Since this 
  */
  class HR_UTILITY_EXPORT C_Datastream
  {
  public:
	  C_Datastream()
	  {

	  }

	  /*!
	  */
	  C_Datastream(int32 Access)
	  {
		//!
		m_Access = Access;
	  }

	  virtual ~C_Datastream()
	  {

	  }

  public:
	  /*!
	   * @brief Defines an enumerator used for specific permissions to operate inside a datastream
	  */
	  int32 m_Access;
  public:
	  virtual SIZE_T     Seek(SIZE_T Offset, SIZE_T ) = 0;

	  /*!
	  */
	  virtual SIZE_T     Tell() = 0;
	  
	  /*!
	  */
	  virtual SIZE_T     Read(Byte* DestBuf, SIZE_T ByteCount) = 0;
	  
	  /*!
	  */
	  virtual SIZE_T     Write(Byte* SrcBuf, SIZE_T ByteCount) = 0;
	  
	  /*!
	  */
	  virtual bool       EndOfBuffer() = 0;

	  /*!
	  */
	  virtual bool      IsReadable()
	  {
		  //!
		  return (m_Access & FileAccess::_READ);
	  }

	  /*!
	  */
	  virtual bool      IsWritable()
	  {
		  //!
		  return (m_Access & FileAccess::_WRITE);
	  }
  };
}

namespace HR_SDK
{
  /*!
   * @brief Supports data that is stored or read in memory
  */
  class HR_UTILITY_EXPORT C_Memorystream : public C_Datastream
  {
  public:
	  /*!*/
	  C_Memorystream(int32 Access)
	  {
		  m_Access = Access;
		m_Buffer = NULL;
		//!
	    m_Pos = 0;
	    //!
		m_End = m_Buffer;
	    //!
		m_Size = 0;
	  }

	  /*!*/
	  virtual ~C_Memorystream()
	  {
		  delete m_Buffer;
	  }

	  /*!*/
	  virtual SIZE_T     Seek(SIZE_T Offset, SIZE_T ByteCount) override;
	  
	  /*!*/
	  virtual SIZE_T     Tell() override;
	  
	  /*!
	  * @brief Reads from an input stream
	  * @param prm_DestinationBuf Location where read information is saved
	  * @param prm_ByteCount Number of bytes that will be read from the buffer
	  */
	  virtual SIZE_T     Read(Byte* DestBuf, SIZE_T ByteCount) override;
	  
	  /*!*/
	  virtual SIZE_T     Write(Byte* SrcBuf, SIZE_T ByteCount) override;
	  
	  /*!*/
	  virtual bool       EndOfBuffer();
  private:
	  SIZE_T GetSize() 
	  {
		  return m_Size;
	  }

  protected:
	  /*!
	  * @brief Points to the start to the
	  */
	  Byte* m_Buffer;

	  /*!
	  * @brief Holds the pointer to the current element of the stream
	  * Stream's start and end do not change, yet a pointer
	  */
	  SIZE_T m_Pos;

	  /*!
	  */
	  Byte* m_End;

	  /*!
	  * @brief Holds the size of the stream
	  * This member variable serves to tell us the exact size of the stream (From start to end).
	  */
	  SIZE_T m_Size;
  };
}

namespace HR_SDK
{
  /*!
   * @brief Supports data that is written or read in a file
  */
  class HR_UTILITY_EXPORT C_Filestream : public C_Datastream
  {
  public:
	  /*!
	  */
	  C_Filestream(int32 Access)
	  {
		  //!
		  m_Access = Access;
	      //!
		  m_Size = 0;
	  }

	  C_Filestream(const C_Filestream& File)
	  {
		  m_Access = File.m_Access;
		  m_Size = File.m_Size;
	  }

	  /*!
	  */
	  virtual ~C_Filestream()
	  {

	  }

	  /*!
	  */
	  SIZE_T GetSize();

	  /*!
	  */
	  C_Directory GetDir()
	  {
		  //! 
		  return m_Dir;
	  }

	  /*!
	  * @brief Opens a file for use.
	  * @param FileName File to be open for use.
	  */
	  bool              Open(const String& FileName, bool Create);
	  
	  /*!
	  */
	  void              Close();

	  /*!
	  */
	  virtual SIZE_T    Seek(SIZE_T Offset, SIZE_T) override;
	  
	  /*!
	  */
	  virtual SIZE_T    Tell() override;
	  
	  /*!
	   * @brief Reads from an input stream
	   * @param prm_DestinationBuf Location where read information is saved
	   * @param prm_ByteCount Number of bytes that will be read from the buffer
	  */
	  virtual SIZE_T    Read(Byte* DestBuf, SIZE_T Count) override;
	  
	  /*!
	  */
	  virtual SIZE_T    Write(Byte* SrcBuf, SIZE_T Count) override;

	  /*!
	  */
	  virtual bool      EndOfBuffer() override;

	  
  private:
	  /*!
	   * @brief Write or read from or into this file stream
	   * Holds info, either to extract characters from or 
	  */
	  std::fstream      m_Stream;

	  /*!
	  */
	  C_Directory       m_Dir;
					    
	  /*!			    
	  */			    
	  SIZE_T            m_Size;
  };
}
