#pragma once

#include "HRUtility_Prerequisites.h"

namespace HR_SDK
{
  /*!
   * @class C_Degree
   * @brief Declares the structure for trigonometric operations performed on degrees
  */
  class HR_UTILITY_EXPORT C_Degree
  {
  public:
	explicit C_Degree(float prm_Value) : m_Value(prm_Value)
	{

	}

	C_Degree(const C_Radian& prm_ValueInRadians);

	inline float GetValueInRadians();
	inline float GetValue() const;

	float m_Value;
  };
}