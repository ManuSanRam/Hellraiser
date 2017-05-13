#pragma once

/*!***********************************************************************************************************************************************************
 * @file		HRUtility_STDHeaders.h
 * 
 * This file contains every header file from the standard C++ library.
 * The headers in this file are as following (In the following order):
 * - C Standard Library (cstdlib)
 * - C Standard Input/Output Library (cstdio)
 * - C++ Standard Input/Output Library (stdio.h)
 * - Input/Output Stream Library (iostream)
 * - C Assertions and C++ Assertions Library (cassert, assert.h)
 * - File Input/Output Stream Library (fstream)
 * - C Math Library (cmath)
 * - C++ Math Library (math.h)
 * - Type Limits Library (limits)
 * - C++ Algorithm Library (algorithm)
 * - C++ Exceptions Library (exception)
 * - C++ Dynamic Memory Library (new)
 * - C++ Memory Allocation Library (memory)
 * - C Time Library (ctime)
 * - C++ Time Library (time.h)
 * - C++ Deque container (deque)
 * - C++ Vector container (vector)
 * - C++ List container (list)
 * - C++ Stack container (stack)
 * - C++ Queue container (queue)
 * - C++ Set, Multiset, Un-ordered set containers (set, unordered_set)
 * - C++ Map, Multimap, Un-ordered map containers (map, unordered_map)
 * 
 * @date		11-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
*************************************************************************************************************************************************************/

#ifdef __BORDLANDC__
  #define __STD_ALGORITHM
#endif

/*!***********************************************************************************************************************************************************
 * C Language header files
*************************************************************************************************************************************************************/
#include <cstdlib>  //! C-type standard library
#include <cstdio>  //! C-type standard input and output header
#include <cassert>  //! C-type assertions
#include <ctime>  //! C-type time header
#include <cstdarg>  //! C-type standard argument header
#include <cmath>  //! C-type standard mathematic header

/*!***********************************************************************************************************************************************************
 * Memory management
*************************************************************************************************************************************************************/
#include <memory>  //! General utilities for dynamic memory management
#include <cstring>	 
#include <time.h>

/*!***********************************************************************************************************************************************************
 * Standard Template Libraries Containers
*************************************************************************************************************************************************************/
#include <deque>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

/*!***********************************************************************************************************************************************************
  For GCC ver 4.3
*************************************************************************************************************************************************************/
#if (HR_ACTIVE_COMPILER == HR_COMPILER_GCC)
  #if HR_COMPILER_VERSION >= 430
    #include <trl/unordered_map>
    #include <trl/unordered_set>
  #elif (HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4)
    #include <unordered_map>
    #include <unordered_set>
  #else
    #include <ext/hash_map>
    #include <ext/hash_set>
  #endif
#else
  #if (HR_ACTIVE_COMPILER == HR_COMPILER_MSVC) && HR_COMPILER_VERSION >= 1600
    #include <unordered_map>
    #include <unordered_set>
  #else
    #include <hash_set>
    #include <hash_map>
  #endif
#endif

/*!***********************************************************************************************************************************************************
 * STL algorithms and functions
*************************************************************************************************************************************************************/
#include <algorithm>
#include <functional>
#include <limits>

/*!***********************************************************************************************************************************************************
 * C++ Streaming
*************************************************************************************************************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef __BORLANDC__
  namespace HR_SDK
  {
    using namespace std;
  }
#endif

/*!***********************************************************************************************************************************************************
 * C Types and Statistics
*************************************************************************************************************************************************************/
extern "C"
{
  #include <sys/types.h>
  #include <sys/stat.h>
}

/*!***********************************************************************************************************************************************************
 * Windows specifics
*************************************************************************************************************************************************************/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_WINDOWS  //! If the current platform is a Windows PC
  #undef min  //! We unde
  #undef max
  #if !defined ( NOMINMAX ) && defined ( _MSC_VER )
    #define NOMINMAX
  #endif
  #if defined ( __MINGW32__ )
    #include <unistd.h>
  #endif
#endif

/*!***********************************************************************************************************************************************************
 * Linux specifics
*************************************************************************************************************************************************************/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_LINUX
  extern "C"
  {
    #include <unistd.h>
    #include <dlfcn.h>
  }
#endif

/*!***********************************************************************************************************************************************************
 * Apple specifics
*************************************************************************************************************************************************************/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_OS_X
  extern "C"
  {
    #include <unistd.h>
    #include <sys/param.h>
    #include <CoreFoundation/CoreFoundation.h>
  }
#endif

/*!***********************************************************************************************************************************************************
 * Play Station 4 specifics
*************************************************************************************************************************************************************/
#if HR_ACTIVE_PLATFORM == HR_PLATFORM_PS4
  extern "C"
  {
    #include <unistd.h>
    #include <sys/param.h>
  }
#endif

namespace HR_SDK
{
  template
	  <typename Type, 
	  typename Allocator = std::allocator<Type>>
  using Deque = std::deque<Type, Allocator>;

  template
	  <typename Type, 
	  typename Allocator = std::allocator<Type>>
  using Vector = std::vector<Type, Allocator>;

  template
	  <typename Type, 
	  typename Allocator = std::allocator<Type>>
  using List = std::list<Type, Allocator>;

  template
	  <typename Type, 
	  typename Allocator = std::allocator<Type>>
  using Stack = std::stack<Type, std::deque<Type, Allocator>>;

  template
	  <typename Type, 
	  typename Allocator = std::allocator<Type>>
  using Queue = std::queue<Type, std::deque<Type, Allocator>>;

  template 
	  <typename Type, 
	  typename Comp = std::less<Type>, 
	  typename Allocator = std::allocator<Type>>
  using Set = std::set<Type, Comp, Allocator>;

  template 
	  <typename Key, 
	  typename Value, 
	  typename Comp = std::less<Key>, 
	  typename Allocator = std::allocator<std::pair<const Key, Value>>>
  using Map = std::map<Key, Value, Comp, Allocator>;

  template 
	  <typename Key, 
	  typename Value, 
	  typename Comp = std::less<Key>, 
	  typename Allocator = std::allocator<std::pair<const Key, Value>>>
  using MultiMap = std::multimap<Key, Value, Comp, Allocator>;

  template 
	  <typename Type, 
	  typename Hash = std::hash<Type>, 
	  typename Comp = std::equal_to<Type>, 
	  typename Allocator = std::allocator<Type>>
  using Unordered_Set = std::unordered_set<Type, Hash, Comp, Allocator>;

  template 
	  <typename Key, 
	  typename Value, 
	  typename Hash = std::hash<Key>, 
	  typename Comp = std::equal_to<Type>, 
	  typename Allocator = std::allocator<std::pair<const Key, Value>>>
  using Unordered_Map = std::unordered_map<Key, Value, Hash, Comp, Allocator>;

  template 
	  <typename Key, 
	  typename Value, 
	  typename Hash = std::hash<Key>, 
	  typename Comp = std::equal_to<Type>, 
	  typename Allocator = std::allocator<std::pair<const Key, Value>>>
  using Unordered_MultiMap = std::unordered_multimap<Key, Value, Hash, Comp, Allocator>;

  /*!*********************************************************************************************************************************************************
   * Smart Pointers
  ***********************************************************************************************************************************************************/
  //! Shared pointer
  template<typename Type>
  using Shared_Ptr = std::shared_ptr<Type>;

  //! unique pointer
  template<typename Type, typename Allocator = C_GenAllocator>
  using Unique_Ptr = std::unique_ptr<Type, decltype(&hr_delete<Type, Allocator>)>;

  //! Shared pointer allocation with specific allocator
  template<class Type, class AllocatorCategory, class... Args>
  Shared_Ptr<Type> hr_shared_ptr_new(Args&&... prm_args)
  {
    return std::allocate_shared<Type>(std::allocator<Type, AllocatorCategory>(), std::forward<Args>(prm_args)...);
  }

  //! Shared pointer allocation with generic allocator
  template
	  <class Type, 
	  class... Args>
  Shared_Ptr<Type> hr_shared_ptr_new(Args&&... prm_args)
  {
    return std::allocate_shared<Type>(C_StdAlloc<Type, C_GenAllocator>(), std::forward<Args>(prm_args)...);
  }

  //! Shared pointer allocation of n'th data size
  template
	  <class Type, 
	  class MainAlloc = C_GenAllocator, 
	  class PtrDataAlloc = C_GenAllocator>
  Shared_Ptr<Type> hr_shared_ptr(Type* prm_Data)
  {
    return std::shared_ptr<Type>(prm_Data, &hr_delete<Type, MainAlloc>, C_StdAlloc<Type, PtrDataAlloc>());
  }

  //!
  template
	  <class Type, 
	  class Allocator = C_GenAllocator>
  Unique_Ptr<Type, Allocator> hr_unique_ptr(Type* prm_Data)
  {
	  return std::unique_ptr<Type, decltype(&hr_delete<Type, Allocator>)>(prm_Data, hr_delete<Type, Allocator>);
  }

  //!
  template
	  <class Type, 
	  class Allocator, class... Args>
  Unique_Ptr<Type> hr_unique_ptr_new(Args&&... prm_args)
  {
	  Type* RawPtr = hr_new<Type, Allocator>(std::forward<Args>(prm_args)...);
	  return hr_unique_ptr<Type, Allocator>(RawPtr);
  }

  //!
  template
	  <class Type, 
	  class... Args>
  Unique_Ptr<Type> hr_unique_ptr_new(Args&&... prm_args)
  {
	  Type* RawPtr = hr_new<Type, C_GenAllocator>(std::forward<Args>(prm_args)...);
	  return hr_unique_ptr<Type, Allocator>(RawPtr);
  }
}
