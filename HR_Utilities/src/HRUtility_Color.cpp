#include "HRUtility_Color.h"

namespace HR_SDK
{
	/*!*************************************************************************************************************************************
	 * COLOR SECTION
	***************************************************************************************************************************************/
	/*!
	* @brief Assigns the prm_Red as the red channel value.
	* @param prm_Red Value to be assigned to the red channel
	*/
	void C_Color::SetRed(uint8 prm_Red)
	{
		m_Red = prm_Red;
	}

	/*!
	* @brief Assigns the prm_Green as the green channel value.
	* @param prm_Green Value to be assigned to the green channel.
	*/
	void C_Color::SetGreen(uint8 prm_Green)
	{
		m_Green |= (1 << prm_Green);
	}

	/*!
	* @brief Assigns the prm_Blue as the blue channel value.
	* @param prm_Blue Value to be assigned to the blue channel.
	*/
	void C_Color::SetBlue(uint8 prm_Blue)
	{
		m_Blue = prm_Blue;
	}

	/*!
	* @brief Assigns the prm_Alpha as the alpha channel value
	@param prm_Alpha Value to be assigned to the alpha channel.
	*/
	void C_Color::SetAlpha(uint8 prm_Alpha)
	{
		m_Alpha = prm_Alpha;
	}

	/*!
	* - Assigns the prm_Red as the red channel value
	*/
	uint8 C_Color::GetRed()
	{
		return m_Red;
	}

	/*!
	* - Assigns the prm_Green as the green channel value
	*/
	uint8 C_Color::GetGreen()
	{
		return m_Green;
	}

	/*!
	* - Assigns the prm_Blue as the blue channel value
	*/
	uint8 C_Color::GetBlue()
	{
		return m_Blue;
	}

	/*!
	* - Assigns the prm_Alpha as the alpha channel value
	*/
	uint8 C_Color::GetAlpha()
	{
		return m_Alpha;
	}

	/*!*************************************************************************************************************************************
	 * LINEAL COLOR SECTION
	***************************************************************************************************************************************/
	float C_LinearColor::GetRed()
	{
		return m_Red;
	}

	float C_LinearColor::GetGreen()
	{
		return m_Green;
	}

	float C_LinearColor::GetBlue()
	{
		return m_Blue;
	}

	float C_LinearColor::GetAlpha()
	{
		return m_Alpha;
	}

	void C_LinearColor::SetRed(float prm_Red)
	{
		m_Red = prm_Red;
	}

	void C_LinearColor::SetGreen(float prm_Green)
	{
		m_Green = prm_Green;
	}

	void C_LinearColor::SetBlue(float prm_Blue)
	{
		m_Blue = prm_Blue;
	}

	void C_LinearColor::SetAlpha(float prm_Alpha)
	{
		m_Alpha = prm_Alpha;
	}
}