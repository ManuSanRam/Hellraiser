#pragma once

#include "HRUtility_Prerequisites.h"

namespace HR_SDK
{
  /*!
   * @class C_Radian
   * @brief Declares the structure for trigonometric operations performed on radians
  */
  class HR_UTILITY_EXPORT C_Radian
  {
  public:
	  explicit C_Radian(float prm_Value): m_Value(prm_Value)
	  {

	  }

	  C_Radian(const C_Degree& prm_ValueInDegrees);

	  inline float GetValueInDegrees();
	  inline float GetValue() const;

	  float m_Value;
  };
}