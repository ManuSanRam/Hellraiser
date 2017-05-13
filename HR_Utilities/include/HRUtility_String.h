#pragma once

#include <wchar.h>
#include <string.h>

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_String.h
 *
 * This file contains the declaration of methods to operate on ANSI-character strings and UNICODE-character strings.
 * The objects and methods declared for string operations are as follows:
 * - Basic string of wide characters (for Unicode usage).
 *     This object holds a basic string object of Unicode/Wide characters, using any C++ method for basic strings.
 * - Basic string of ANSI characters.
 *     This object holds a basic string object of ANSI characters, using any C++ method or basic strings.
 * - Basic string stream of Wide/Unicode characters.
 *     Performs input/output operations on a basic string of Wide characters.
 * - Basic string stream of ANSI characters.
 *     Performs input/output operations on a basic string of ANSI characters.
 * - Length of a string.
 * - Substring from a string.
 * - Parse a string and transforms it into:
 *     - Floating-point number.
 *     - Unsigned/Signed integer number (8, 16, 32, 64, 128 bits).
 * - Comparing the content of two strings.
 *
 * @date        04-10-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

namespace HR_SDK
{
	/*!
	 * @brief Redefinition of std::basic_string to be used with a different alias
	 * The alias helps to perform string operations in a simplier manner.
	*/
	template<typename Type>
	using BasicString = std::basic_string<Type, std::char_traits<Type>>;

	/*!
	 * @brief Redefinition of std::basic_string to be used with a different alias
	 * The alias helps to perform string operations in a simplier manner.
	*/
	template<typename Type>
	using BasicStringStream = std::basic_stringstream<Type, std::char_traits<Type>>;

	/*!
	 * @brief Redefinition of std::basic_string to be used with a different alias
	 * The alias helps to perform string operations in a simplier manner.
	*/
	typedef BasicString<UNICODE_CHAR> WString;
	
	/*!
	 * @brief Redefinition of std::basic_string to be used with a different alias
	 * The alias helps to perform string operations in a simplier manner.
	*/
	typedef BasicString <ANSI_CHAR> String;

	/*!
	 * @brief Redefinition of std::basic_string to be used with a different alias
	 * The alias helps to perform string operations in a simplier manner.
	*/
	typedef BasicStringStream<UNICODE_CHAR> WStringStream;
	
	/*!
	 * @brief Redefinition of std::basic_string to be used with a different alias
	 * The alias helps to perform string operations in a simplier manner.
	*/
	typedef BasicStringStream<ANSI_CHAR> StringStream;
}

