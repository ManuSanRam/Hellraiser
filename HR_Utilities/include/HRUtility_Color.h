#pragma once

#include "HRUtility_Prerequisites.h"

/*!************************************************************************************************************************************************************************
 * @file		HRUtility_Color.h
 *
 * This file contains the Color class declaration, for mathematical operations to get colors and control the data on them.
 * The methods implemented in the class are:
 * - Setting of the channels individually.
 * - Obtaining color structures from another 4D vector to get information from.
 * - Obtaining color data from another color.
 *
 * @date        26-09-2016
 * @author		Manuel Aldair Santos Ramón (ManuSanRam)
 * @copyright	Infernal Coders S.A.
***************************************************************************************************************************************************************************/

#include "HRUtility_PlatformMath.h"
#include "HRUtility_Vector4D.h"

namespace HR_SDK
{
  /*!**********************************************************************************************************************************************************************
   * @brief Defines the structure for colors in RGBA space
   * The color class uses a 4-dimensional vector to control the color data, performing vectorial operations on it 
  *************************************************************************************************************************************************************************/
  class HR_UTILITY_EXPORT C_Color
  {
  public:
	/*!
	 * @brief Constructs an empty color object
	 * Constructs black color with 100 % opacity set.
	*/
	C_Color()
	{
		SetRed(0);
		SetGreen(0);
		SetBlue(0);
		SetAlpha(255);
	}

	/*!
	 * @brief Constructs a color object by floating-point parameters.
	 * By default this constructor returns a black color with 100 % opacity.
	 * @param prm_Red Value passed as data for the color's red channel.
	 * @param prm_Green Value passed as data for the color's green channel.
	 * @param prm_Blue Value passed as data for the color's blue channel.
	 * @param prm_Alpha Value passed as data for the color's alpha channel.
	*/
	C_Color(uint8 prm_Red, uint8 prm_Green, uint8 prm_Blue, uint8 prm_Alpha)
	{
		SetRed(prm_Red);
		SetGreen(prm_Green);
		SetBlue(prm_Blue);
		SetAlpha(prm_Alpha);
	}


	/*!
	@brief Constructor creates an instance of Color using the reference from another 4 dimensional vector
	@param prm_Vector Reference to a 4-dimensional vector, which values will be used to build the color.
	*/
	C_Color(C_Vector4D& prm_Vector)
	{
		SetRed	((uint8)prm_Vector.m_x);
		SetGreen((uint8)prm_Vector.m_y);
		SetBlue	((uint8)prm_Vector.m_z);
		SetAlpha((uint8)prm_Vector.m_w);
	}

	/*!
	@brief Constructor creates an instance of Color using the reference from another 4 dimensional vector
	@param prm_Vector Reference to a 4-dimensional vector, which values will be used to build the color.
	*/
	C_Color(const C_Color& prm_Color)
	{
		m_Red = prm_Color.m_Red;
		m_Green = prm_Color.m_Green;
		m_Blue = prm_Color.m_Blue;
		m_Alpha = prm_Color.m_Alpha;
	}

	C_Color(C_LinearColor& prm_Color)
	{

	}

	/*!
	* @brief Assignment operator between 3D vectors
	*/
	C_Color operator = (const C_Color& prm_Color)
	{
		//! Copy the memory of the parameter into this object
		memcpy(this, &prm_Color, sizeof(C_Color));
		//! Return the current instance, which is carrying the current data
		return *this;
	}

	/*!
	 * @brief Destroys a color object
	*/
	~C_Color()
	{

	}

	/*!
	 * @brief Assigns the prm_Red as the red channel value.
	 * @param prm_Red Value to be assigned to the red channel
	*/
	void SetRed(uint8 prm_Red);

	/*!
	 * @brief Assigns the prm_Green as the green channel value.
	 * @param prm_Green Value to be assigned to the green channel.
	*/
	void SetGreen(uint8 prm_Green);

	/*!
	 * @brief Assigns the prm_Blue as the blue channel value.
	 * @param prm_Blue Value to be assigned to the blue channel.
	*/
	void SetBlue(uint8 prm_Blue);

	/*!
	 * @brief Assigns the prm_Alpha as the alpha channel value
	 @param prm_Alpha Value to be assigned to the alpha channel.
	*/
	void SetAlpha(uint8 prm_Alpha);

	/*!
	 * - Assigns the prm_Red as the red channel value
	*/
	uint8 GetRed();

	/*!
	 * - Assigns the prm_Green as the green channel value
	*/
	uint8 GetGreen();

	/*!
	 * - Assigns the prm_Blue as the blue channel value
	*/
	uint8 GetBlue();

	/*!
	 * - Assigns the prm_Alpha as the alpha channel value
	*/
	uint8 GetAlpha();

  private:
	/*!
	 * @brief Vector who holds the RGBA data of the color.
	 * Channels are controlled in the following way:
	 *   - Red channel is controlled by vector's 'X' coord.
	 *	 - Green channel is controlled by vector's 'Y' coord.
	 *	 - Blue channel is controlled by vector's 'Z' coord.
	 *	 - Alpha channel is controlled by vector's 'W' coord.
	*/
	union
	{
		struct
		{
			uint8 m_Alpha;
			uint8 m_Blue;
			uint8 m_Green;
			uint8 m_Red;
		};
	};
  };

  class HR_UTILITY_EXPORT C_LinearColor
  {
  public:
	  /*!
	  */
	  C_LinearColor()
	  {

	  }

	  /*!
	  */
	  C_LinearColor(float prm_Red, float prm_Green, float prm_Blue, float prm_Alpha)
	  {
		  SetRed(prm_Red);
		  SetGreen(prm_Green);
		  SetBlue(prm_Blue);
		  SetAlpha(prm_Alpha);
	  }

	  /*!
	  */
	  C_LinearColor(const C_LinearColor& prm_LColor)
	  {
		  *this = prm_LColor;
	  }

	  /*!
	  */
	  C_LinearColor(C_Vector4D& prm_Vector)
	  {
		  SetRed(prm_Vector.m_x);
		  SetGreen(prm_Vector.m_y);
		  SetBlue(prm_Vector.m_z);
		  SetAlpha(prm_Vector.m_w);
	  }

	  /*!
	  */
	  C_LinearColor(C_Color& prm_Color)
	  {
		  m_Red   = C_PlatformMath::Power<float>(prm_Color.GetRed(), (1.0f / 2.2f));
		  m_Green = C_PlatformMath::Power<float>(prm_Color.GetGreen(), (1.0f / 2.2f));
		  m_Blue  = C_PlatformMath::Power<float>(prm_Color.GetBlue(), (1.0f / 2.2f));
		  m_Alpha = C_PlatformMath::Power<float>(prm_Color.GetAlpha(), (1.0f / 2.2f));
	  }

	  /*!
	   * @brief Assignment operator between 3D vectors
	  */
	  C_LinearColor& operator = (const C_LinearColor& prm_LColor)
	  {
		  //! Copy the memory of the parameter into this object
		  memcpy(this, &prm_LColor, sizeof(C_LinearColor));
		  //! Return the current instance, which is carrying the current data
		  return *this;
	  }

	  /*!
	  */
	  void Set(float R, float G, float B, float A)
	  {
		  SetRed(R);
		  SetGreen(G);
		  SetBlue(B);
		  SetAlpha(A);
	  }


	  /*!
	  */
	  ~C_LinearColor()
	  {

	  }

	  /*!
	  */
	  float GetRed();
	  /*!
	  */
	  float GetGreen();
	  /*!
	  */
	  float GetBlue();
	  /*!
	  */
	  float GetAlpha();

	  /*!
	  */
	  void SetRed(float prm_Red);
	  /*!
	  */
	  void SetGreen(float prm_Green);
	  /*!
	  */
	  void SetBlue(float prm_Blue);
	  /*!
	  */
	  void SetAlpha(float prm_Alpha);

  private:
	/*!
	*/
	  float m_Red;
	/*!
	*/
	  float m_Green;
	/*!
	*/
	  float m_Blue;
	/*!
	*/
	  float m_Alpha; 
  };
}