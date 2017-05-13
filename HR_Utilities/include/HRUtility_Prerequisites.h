#pragma once

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_Prerequisites.h
 *
 * This file contains the inclusion of every prerequisite needed in the engine for its correct execution.
 * The prerequisites included are as following:
 * - Platform-specific data types.
 * - Standard C and C++ header files.
 * - Engine's classes forward declaration.
 *
 * @date		10-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

#include "HRUtility_PlatformDefines.h" //! Basic defines for multi-platform
#include "HRUtility_PlatformTypes.h"  //! Custom types used by the engine.
#include "HRUtility_MacroUtil.h"  //! Macros for multiline defines and unreferenced parameters.
#include "HRUtility_MemoryAllocators.h"  //! Memory allocation operations

#include "HRUtility_STDHeaders.h"  //! Second inclusion: Standard headers, for use of C++ standard functions and data-structures.
#include "HRUtility_FwdDecl.h"  //! Third inclusion: Forward Declarations, for external use of classes and cyclic inclusion error prevention.

#include "HRUtility_String.h"  //! Custom definition of strings
//#include "HRUtility_StringUtil.h" //! For use of general string types, so no more inclusions are needed. 