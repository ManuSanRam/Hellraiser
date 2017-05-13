#pragma once

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_PlatformDefines.h
 * 
 * This file contains the macros for the engine's portability in the next systems (In the following order):
 * - Microsoft Software's Windows 10, 8.1, 8 and 7(x86 and x64 architecture).
 * - Apple's Mac OS X (x86 and x64 architecture).
 * - GNU/Linux's Linux OS (x86 and x64 architecture).
 * - Sony's Play Station 3, Play Station 4 and Play Station Vita.
 * - Microsoft Software's XBOX 360 and XBOX ONE.
 * - Nintendo's Gamecube, Wii and Wii U.
 * - Apple's IOs Mobile platform (versions: 10, 9, 8, 7, 6, 5).
 * - Google's Android Mobile platform (versions: Nougat 7.0, Marshmellow 6.0, Lollipop 5.0, KitKat 4.4, Jelly Bean 4.1, Ice Cream Sandwich 4.0).
 * 
 * @date		08-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/


/*!***********************************************************************************************************************************************************
 * SECTION #1: PLATFORMS
 * This section contains the macros for the different platforms the engine can run in:
 * - Microsoft's Windows 10, 8.1, 8 and 7.
 * - Apple's Mac OS X.
 * - GNU/Linux's Linux OS.
 * - Sony's Play Station 3, Play Station 4 and Play Station Vita.
 * - Microsoft's XBOX 360 and XBOX ONE.
 * - Nintendo's Gamecube, Wii and Wii U.
*************************************************************************************************************************************************************/

/*!***********************************************************************************************************************************************************
 * PERSONAL COMPUTERS
*************************************************************************************************************************************************************/
/*!
 * @def	HR_PLATFORM_WINDOWS
 * @brief Defines the Microsoft's Windows platform (10, 8.1, 8 and 7)
*/
#define		HR_PLATFORM_WINDOWS		1
			 
/*!
 * @def	HR_PLATFORM_OS_X
 * @brief Defines the Apple's OS X platform
*/	 
#define		HR_PLATFORM_OS_X		2
			 
/*!
 * @def	HR_PLATFORM_LINUX
 * @brief Defines the GNU/Linux's Linux platform
*/	 
#define		HR_PLATFORM_LINUX		3

/*!***********************************************************************************************************************************************************
 * GAME CONSOLES
*************************************************************************************************************************************************************/
/*!========== SONY ============*/
/*!
 * @def	HR_PLATFORM_PS3
 * @brief Defines the Sony's Play Station 3 platform
*/
#define		HR_PLATFORM_PS3			4
			 
/*!
 * @def	HR_PLATFORM_PS4
 * @brief Defines the Sony's Play Station 4 platform
*/	 
#define		HR_PLATFORM_PS4			5
			 
/*!
 * @def	HR_PLATFORM_PSVITA
 * @brief Defines the Sony's Play Station Vita platform
*/	 
#define		HR_PLATFORM_PSVITA		6

/*!========== MICROSOFT ============*/
/*!
 * @def	HR_PLATFORM_XBOX360
 * @brief Defines the Microsoft's XBOX 360 platform
*/
#define		HR_PLATFORM_XBOX360		7
			 
/*!
 * @def	HR_PLATFORM_XBOXONE
 * @brief Defines the Microsoft's XBOX ONE platform
*/	 
#define		HR_PLATFORM_XBOXONE		8

/*!========== NINTENDO =============*/
/*!
 * @def	HR_PLATFROM_GAMECUBE
 * @brief	Defines the Nintendo´s Gamecube platform
*/
#define		HR_PLATFORM_GAMECUBE	9
			 
/*!
 * @def	HR_PLATFORM_WII
 * @brief Defines the Nintendo's Wii platform
*/	 
#define		HR_PLATFORM_WII			10
			 
/*!
 * @def	HR_PLATFORM_WIIU
 * @brief Defines the Nintendo's Wii U platform
*/	 
#define		HR_PLATFORM_WIIU		11

/*!***********************************************************************************************************************************************************
 * MOBILE DEVICES
*************************************************************************************************************************************************************/
/*!
 * @def HR_PLATFORM_IOS
 * @brief Defines the Apple's IOs platform
*/
#define		HR_PLATFORM_IOS			12

/*!
 * @def HR_PLATFORM_ANDROID
 * @brief Defines the Google's Android platform
*/
#define		HR_PLATFORM_ANDROID		13


/*!***********************************************************************************************************************************************************
 * SECTION #2: COMPILERS.
 * This section contains the macros for the different compilers:
 * - Microsoft Software Visual Compiler.
 * - GCC C++ Compiler.
 * - Intel C++ Compiler.
 * - Borland C++ Compiler.
*************************************************************************************************************************************************************/
/*!
 * @def HR_COMPILER_MSVC
 * @brief Defines the Microsoft Software's Visual Compiler for C++.
*/
#define		HR_COMPILER_MSVC        1
			   
/*!
 * @def HR_COMPILER_GCC
 * @brief Defines the GCC Compiler for C++.
*/	 
#define		HR_COMPILER_GCC         2
			   
/*!
 * @def HR_COMPILER_INTEL
 * @brief Defines the Intel C++ compiler.
*/	 
#define		HR_COMPILER_INTEL       3

/*!
 * @def HR_COMPILER_CLANG
 * @brief Defines the CLang C++ compiler.
*/
#define     HR_COMPILER_CLANG       4

/*!
 * @def HR_COMPILER_BORLAND
 * @brief Defines the Borland C++ compiler.
*/	 
#define		HR_COMPILER_BORLAND     5


/*!***********************************************************************************************************************************************************
 * SECTION #3: ARCHITECTURES.
 * This section contains the macros for the different architectures of the platforms:
 * - x86 architecture.
 * - x64 architecture.
*************************************************************************************************************************************************************/
/*!
 * @def HR_ARCH_x86_32
 * @brief Defines x86 architecture (32-bit operating systems)
*/
#define		HR_ARCH_x86_32			1

/*!
 * @def HR_ARCH_x86_64
 * @brief Defines x64 architecture (64-bit operating systems)
*/
#define		HR_ARCH_x86_64			2

/*!***********************************************************************************************************************************************************
 * SECTION #4: ENDIANESS.
 * This section contains the macros for the endianess of the platform:
 * - Little Endian: (Smallest bit is most significant).
 * - Big Endian: (Largest bit is most significant).
 * - Endian: Endian in which the engine's current platform uses.
 * - Editor Build: Editor mode of the engine's
*************************************************************************************************************************************************************/
/*!
 * @def HR_ENDIAN_LITTLE
 * @brief Defines the "little" endianess (Most significant bit is the smallest)
*/
#define		HR_ENDIAN_LITTLE		1

/*!
 * @def HR_ENDIAN_BIG
 * @brief Defines the "big" endianess (Most significant bit is the largest)
*/
#define		HR_ENDIAN_BIG			2

/*!
 * @def HR_ENDIAN
 * @brief Defines the current endian as little endian
*/
#define		HR_ENDIAN				HR_ENDIAN_LITTLE

/*!
 * @def HR_EDITOR_BUILD
 * @brief Defines the build info. for the engine's Editor Mode
*/
#define		HR_EDITOR_BUILD			1


/*!***********************************************************************************************************************************************************
 * SECTION #5: ACTIVE COMPILER INFORMATION.
 * This section contains the information for the active compiler. The information is as it follows:
 * - Compiler version macro.
 * - Thread type macro.
 * - Forced inline macro.
 * - Restrictions macro.
 * - File name macro.
 * - Line number macro.
 * - Function name macro.
*************************************************************************************************************************************************************/
#if defined ( _MSC_VER )  //! If current compiler is Visual Studio
  /*!
   * @def HR_ACTIVE_COMPILER
   * @brief Defines the active compiler on which the engine's running.
  */
  #define HR_ACTIVE_COMPILER		HR_COMPILER_MSVC  //! Active compiler is defined as Visual Studio.
  /*!
   * @def HR_COMPILER_VERSION
   * @brief Defines the compiler's version.
  */
  #define HR_COMPILER_VERSION		_MSC_VER  //! Microsoft Visual Compiler version is defined.
  /*!
   * @def HR_THREAD_LOCAL
   * @brief Defines the local thread space.
  */
  #define HR_THREAD_LOCAL			__declspec(thread)  //! Local thread Space is defined.
#elif defined ( __GNUC__ )  //! If the current compiler is GCC.
  /*!
   * @def HR_ACTIVE_COMPILER
   * @brief Defines the active compiler on which the engine's running.
  */
  #define HR_ACTIVE_COMPILER		HR_COMPILER_GCC  //!
  /*!
   * @def HR_COMPILER_VERSION
   * @brief Defines the compiler's version.
  */
  #define HR_COMPILER_VERSION		(( ( __GNUC__ ) * 100 ) + ( __GNUC_MINOR__ * 10 ) + __GNUC_BATCHLEVEL__)  //!
  /*!
   * @def HR_COMPILER_VERSION
   * @brief Defines the compiler's version.
  */
  #define HR_THREAD_LOCAL			__thread  //!
#elif defined ( __INTEL_COMPILER )  //! If the current compiler is Intel C++.
  /*!
   * @def HR_ACTIVE_COMPILER
   * @brief Defines the active compiler on which the engine's running.
  */
  #define HR_ACTIVE_COMPILER		HR_COMPILER_INTEL  //!
  /*!
   * @def HR_COMPILER_VERSION
   * @brief Defines the compiler's version.
  */
  #define HR_COMPILER_VERSION		__INTEL_COMPILER  //!
#elif defined ( __clang__ )  //! If the current compiler is CLang C++.
  /*!
   * @def HR_ACTIVE_COMPILER
   * @brief Defines the active compiler on which the engine's running.
  */
  #define HR_ACTIVE_COMPILER		HR_COMPILER_CLANG  //!
  /*!
   * @def HR_COMPILER_VERSION
   * @brief Defines the compiler's version.
  */
  #define HR_COMPILER_VERSION		__clang_major__  //!
  /*!
   * @def HR_COMPILER_VERSION
   * @brief Defines the compiler's version.
  */
  #define HR_THREAD_LOCAL			__thread  //!
#else  //! If the current compiler is unknown or not listed.
  #pragma error (">> No known compiler.")  //! Deliver an error...
#endif

#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC  //!
  #if HR_COMPILER_VERSION >= 1200  //! If the compiler version is 2012 to last version available
    #define FORCEINLINE				__forceinline  //! 
    #ifndef RESTRICT
      #define RESTRICT			__restrict  //!
    #endif
	#define HR_FILE				__FILE__
	#define HR_LINE				__LINE__
    #define HR_FUNCTION			__func__
    #define SAFE_DELETE(x) if(x != nullptr)delete x; x=nullptr;
  #endif

#elif defined (__MINGW32__)  //!
  #if !defined(FORCEINLINE)
    #define FORCEINLINE				__inline  //!
    #ifndef RESTRICT
      #define RESTRICT				
    #endif
  #endif
#else
  #if HR_COMPILER_VERSION >= 1200
    #define FORCEINLINE				__inline	
      #ifndef RESTRICT
        #define RESTRICT			__restrict
      #endif
  #endif
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #6: ACTIVE PLATFORM INFORMATION.
 * This section contains the information for the active platform.
*************************************************************************************************************************************************************/
#if defined ( __WIN32__ ) || defined ( _WIN32 ) //! If the current platform is Windows API
  #define HR_ACTIVE_PLATFORM	HR_PLATFORM_WINDOWS  //! Active platform is
#elif defined ( __APPLE_CC__ )
  #define HR_ACTIVE_PLATFORM	HR_PLATFORM_OS_X
#elif defined ( __ORBIS__ )
  #define HR_ACTIVE_PLATFORM	HR_PLATFORM_PS4
#else
  #define HR_ACTIVE_PLATFORM	HR_PLATFORM_LINUX
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #7: ACTIVE ARCHITECTURE INFORMATION.
 * This section contains the information for the active architecture.
*************************************************************************************************************************************************************/
#if defined ( __x86_64__ ) || defined ( _M_X64 )
  #define HR_ACTIVE_ARCHITECTURE	HR_ARCH_x86_64
#else
  #define HR_ACTIVE_ARCHITECTURE	HR_ARCH_x86_32
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #8: MEMORY ALIGNMENT.
 * This section contains the information for the memory alignment, depending the active compiler.
*************************************************************************************************************************************************************/
#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC
  #define MS_ALIGN(x)				__declspec(align(x))
  #ifndef GCC_PACK
    #define GCC_PACK(x)
  #endif
  #ifndef GCC_ALIGN
    #define GCC_ALIGN(x)
  #endif
#elif (HR_ACTIVE_COMPILER == HR_COMPILER_GCC && HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4)
  #define MS_ALIGN(x)
  #define GCC_PACK(x)
  #define GCC_ALIGN(x) __attribute__ ((__aligned__(x)) )
#else
  #define MS_ALIGN(x)
  #define GCC_PACK(x)		__attribute__ ((packed, __aligned__(x)) )
  #define GCC_ALIGN(x)	__attribute__ ((__aligned__(x)) )
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #9: EXCEPTION THROW OVERRIDING.
 * This section contains the information for the exception and throw overriding.
*************************************************************************************************************************************************************/
#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC
  #define _NOEXCEPT		noexcept
#elif HR_ACTIVE_COMPILER == HR_COMPILER_INTEL
  #define _NOEXCEPT		noexcept
#elif HR_ACTIVE_COMPILER == HR_COMPILER_GCC
  #define _NOEXCEPT		noexcept
#else
  #define _NOEXCEPT
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #10: WINDOWS SPECIFIC INFORMATION.
 * This section contains any specific information for the Microsoft's Windows platform. The information is as follows:
 * - Dynamic Link Library Export macro.
 * - Debugging Mode.
 * - Thread Local.
*************************************************************************************************************************************************************/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_WINDOWS
  #if defined (HR_STATIC_LIBRARY)
    #define HR_UTILITY_EXPORT
  #else
    #if defined (HR_UTILITIES_EXPORTS)
      #define HR_UTILITY_EXPORT __declspec(dllexport)
    #else
      #if defined (__MINGW32__)
        #define HR_UTILITY_EXPORT
      #else
        #define HR_UTILITY_EXPORT __declspec(dllimport)
      #endif
    #endif
  #endif

  #if defined (_DEBUG) || defined (DEBUG)
    #define HR_DEBUG_MODE 1
  #else
    #define HR_DEBUG_MODE 0
  #endif

  #if HR_ACTIVE_COMPILER == HR_COMPILER_INTEL
    #define HR_THREADLOCAL 
  #endif
#endif


/*!***********************************************************************************************************************************************************
 * SECTION #11: OS X / LINUX SPECIFIC INFORMATION.
 * This section contains any specific information for the Apple's OS X and GNU/Linux's Linux platforms. The information is as follows:
 * - Dynamic Link Library Export macro.
 * - Debugging Mode.
 * - Thread Local.
*************************************************************************************************************************************************************/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_OS_X || HR_ACTIVE_PLATFORM == HR_PLATFORM_LINUX
  #if defined (HR_GCC_VISIBILITY)
    #define HR_UTILITY_EXPORT __attribute__ ((visibility("default")))
  #else
    #define HR_UTILITY_EXPORT
  #endif

  #define stricmp strcasecmp

  #if defined (_DEBUG) || defined (DEBUG)
    #define HR_DEBUG_MODE 1
  #else
    #define HR_DEBUG_MODE 0
  #endif

  #if HR_ACTIVE_COMPILER == HR_COMPILER_INTEL
    #define HR_THREADLOCAL __thread
  #endif
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #12: PLAY STATION 3 / PLAY STATION 4 / PLAY STATION VITA SPECIFIC INFORMATION.
 * This section contains any specific information for the Sony's Play Station 3, 4 and Vita platforms. The information is as follows:
 * - Dynamic Link Library Export macro.
 * - Debugging Mode.
 * - Thread Local.
*************************************************************************************************************************************************************/
/*!============ PS4 specifics ===========*/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4
  #if defined (HR_STATIC_LIBRARY)
    #define HR_UTILITY_EXPORT
  #else
    #if defined (HR_UTILITIES_EXPORTS)
      #define HR_UTILITY_EXPORT __declspec(dllexport)
    #else
      #if defined (__MINGW32__)
        #define HR_UTILITY_EXPORT
      #else
        #define HR_UTILITY_EXPORT __declspec(dllimport)
      #endif
    #endif
  #endif

  #if defined (_DEBUG) || defined (DEBUG)
    #define HR_DEBUG_MODE 1
  #else
    #define HR_DEBUG_MODE 0
  #endif
#endif

/*!***********************************************************************************************************************************************************
 * SECTION #13: XBOX 360 / XBOX ONE SPECIFIC INFORMATION.
 * This section contains any specific information for the Microsoft's XBOX 360 and ONE platforms. The information is as follows:
 * - Dynamic Link Library Export macro.
 * - Debugging Mode.
 * - Thread Local.
*************************************************************************************************************************************************************/


/*!***********************************************************************************************************************************************************
 * SECTION #14: GAMECUBE / WII / WII U SPECIFIC INFORMATION.
 * This section contains any specific information for the Nintendos's Gamecube, Wii and Wii U platforms. The information is as follows:
 * - Dynamic Link Library Export macro.
 * - Debugging Mode.
 * - Thread Local.
*************************************************************************************************************************************************************/


/*!***********************************************************************************************************************************************************
* SECTION #14: GAMECUBE / WII / WII U SPECIFIC INFORMATION.
* This section contains any specific information for the Nintendos's Gamecube, Wii and Wii U platforms. The information is as follows:
* - Dynamic Link Library Export macro.
* - Debugging Mode.
* - Thread Local.
*************************************************************************************************************************************************************/
#if HR_DEBUG_MODE
  #define HR_DEBUG_ONLY(x) x
  #define HR_ASSERTION(x) assert(x)
#else
  #define HR_DEBUG_MODE(x)
  #define HR_ASSERTION(x)
#endif
