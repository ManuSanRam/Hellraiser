#pragma once

/*!*************************************************************************************************************************************************************************
 * @file		HRUtility_PlatformTypes.h																																   *
 * 																																										   *
 * This file contains custom types depending of the active platform and compiler the engine's running.																	   *
 * The custom types are the following:																																	   *
 * - Un-signed and signed 8-bit integers.																																   *
 * - Un-signed and signed 16-bit integers.																																   *
 * - Un-signed and signed 32-bit integers.																																   *
 * - Un-signed and signed 64-bit integers.																																   *
 * - Un-signed and signed 128-bit integers.																																   *
 * - Wide characters.																																					   *
 * - ANSI-type characters.																																				   *
 * - UNICODE-type characters.																																			   *
 * - Size_t type.																																						   *
 * 																																										   *
 * @date		10-09-2016																																				   *
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)																													   *
 * @copyright	Infernal Coders S.A.																																	   *
***************************************************************************************************************************************************************************/

#if HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4
  #include <scebase.h>
#endif

/*!*************************************************************************************************************************************************************************
 * @namespace HR_SDK																																					   *
 * @brief Defines the namespace that contains every basic type and operation used inside the engine																		   *
***************************************************************************************************************************************************************************/
namespace HR_SDK
{
/*!***********************************************************************************************************************************************************
 * SECTION #1: INTEGER TYPES.
 * This section contains the declaration of every integer type:
 * - Dynamic Link Library Export macro.
 * - Debugging Mode.
 * - Thread Local.
*************************************************************************************************************************************************************/
  /*!*********************************************************************************************************************************************************
  * Unsigned integer types
  ***********************************************************************************************************************************************************/
  /*!
   * @brief Unsigned 8-bit size integer
  */
  typedef unsigned char    uint8;
  /*!
   * @brief Unsigned 16-bit size integer
  */
  typedef unsigned short   uint16;
  /*! 
   * @brief Unsigned 32-bit size integer
  */
  typedef unsigned int     uint32;
#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC
  /*!
   * @brief Unsigned 64-bit size integer
  */
  typedef unsigned __int64 uint64;
#else
  /*!
    @brief Unsigned 64-bit size integer
  */
  typedef unsigned long    uint64;
#endif
  /*!*********************************************************************************************************************************************************
   * Signed integer types
  ***********************************************************************************************************************************************************/
  typedef signed char      int8;
  typedef signed short     int16;
  typedef signed int       int32;
#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC
  typedef signed __int64   int64;
#else
  typedef signed long      int64;
#endif

  /*!*********************************************************************************************************************************************************
   * @brief 128-bit size integer type
  ***********************************************************************************************************************************************************/
  MS_ALIGN(16) class HR_UTILITY_EXPORT QWord
  {
  public:
	/*!
	 * @brief Lower part of the 128-bit integer (Numeric value)
	*/
    uint64 a_Lower;
	/*!
	 * @brief Upper part of the 128-bit integer (Sign)
	*/
	int64  a_Upper;

	/*!
	 * @brief Operator overloaded for casting
	*/
	operator int64 () const
	{
	  return a_Lower;
	}

	/*!
	  @brief
	*/
	QWord()
	{
	  
	}

	/*!
	  @brief Default constructor 
	*/
	QWord(bool prm_from) : a_Lower(prm_from), a_Upper(0)
	{
	  
	}

	/*!*/
	QWord(uint8 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(int8 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(uint16 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(int16 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(uint32 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(int32 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(uint64 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(int64 prm_from) : a_Lower(prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(float prm_from) : a_Lower((uint64)prm_from), a_Upper(0)
	{

	}

	/*!*/
	QWord(double prm_from) : a_Lower((uint64)prm_from), a_Upper(0)
	{

	}

  };
  GCC_ALIGN(16)

  typedef QWord            int128;
  typedef QWord            uint128;

  /*!
   * Character types, depending of the character set standards
  */
#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC || HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4
  typedef wchar_t          WIDE_CHAR;
#else
  typedef unsigned short   WIDE_CHAR;
#endif
  typedef char             ANSI_CHAR;
  typedef WIDE_CHAR        UNICODE_CHAR;

  /*!
   * Memory type
  */
  typedef char				Byte;

  /*!
   * Size types, depending of the PC's architecture
  */
#if ((HR_ACTIVE_ARCHITECTURE == HR_ARCH_x86_64) && (HR_ACTIVE_COMPILER == HR_COMPILER_MSVC))
  /*!
   * @brief Size type for 64-bit architecture
  */
  typedef unsigned __int64 SIZE_T;
#else
  /*!
   * @brief Size type for 64-bit architecture
  */
  typedef unsigned long    SIZE_T;
#endif
}