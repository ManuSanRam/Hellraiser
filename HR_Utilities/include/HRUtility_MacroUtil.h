#pragma once

#if HR_ACTIVE_COMPILER == HR_COMPILER_MSVC
  #define MULTI_LINE_MACRO_BEGIN do{
  #define MULTI_LINE_MACRO_END		\
		_pragma(warning(push))			\
		_pragma(warning(disable:4127))  \
					} while(0)			\
		_pragma(warning(pop))
#else
  #define MULTI_LINE_MACRO_BEGIN do{
  #define MULTI_LINE_MACRO_END } while(0)
#endif


/************************************************************************/
/* Utilidades de parametro                                              */
/************************************************************************/
#ifndef HR_UNREFERENCED_PARAMETER
  #define HR_UNREFERENCED_PARAMETER(P) (void)P
#endif // !UNREFERENCED_PARAMETER
