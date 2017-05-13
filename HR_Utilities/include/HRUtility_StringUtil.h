#pragma once

#include "HRUtility_Prerequisites.h"

namespace HR_SDK
{
	/*!
	* @brief Defines methods to perform operations on strings.
	*/
	class HR_UTILITY_EXPORT C_StringUtility
	{
	public:
		/*!
		* @brief Obtains a substring from a string
		* @param prm_Str String from which you obtain the substring
		* @param prm_Offset Offset from the start of the string
		* @param prm_Count Count of characters to extract
		*/
		template<typename StringType>
		static BasicString<StringType> SubStr(BasicString<StringType>& prm_Str, SIZE_T prm_Offset = 0, SIZE_T prm_Count = BasicString<StringType>::npos)
		{
			BasicStringStream<StringType> SS;
			SS << prm_Str;

			return (SS.str()).substr(prm_Offset, prm_Count);
		}

		/*!
		* @brief Converts a string to a floating-point number
		*/
		template<typename StringType>
		static float StringToFloat(const String& prm_S, float prm_Value)
		{
			StringStream SS(prm_S);
			float ReturnNum = prm_Value;

			SS >> ReturnNum;

			return ReturnNum;
		}

		/*!
		*/
		template<typename StringType>
		static BasicString<StringType> FloatToString(const String& prm_S, float prmNumber)
		{
			StringStream SS(prm_S);

			SS << prmNumber;

			return SS.str();
		}

		/*!
		*/
		template<typename StringType>
		static uint32 StringToUInt(const String& prm_SS, uint32 prm_Number)
		{
			StringStream StringSHolder(prm_SS);
			int64 NumHolder = prm_Number;

			StringSHolder >> prm_Number;

			if (NumHolder < 0)
			{
				return 0; //Only for Windows
			}

			return (uint32)NumHolder;
		}

		/*!
		*/
		template<typename StringType>
		static int32 StringToInt(const StringStream& prm_SS, int32 prm_Number)
		{
			StringStream StringSHolder(prm_SS.str());
			int32 NumHolder = prm_Number;

			StringSHolder >> prm_Number;

			return NumHolder;
		}

		/*!
		*/
		template<typename StringType>
		static BasicString<StringType> IntToString(int32 prm_Number)
		{
			BasicStringStream<StringType> StringSHolder;

			StringSHolder << prm_Number;

			return StringSHolder.str().;
		}
		/*!
		*/
		template<typename StringType>
		static BasicString<StringType> UIntToString(uint32 prm_Number)
		{
			BasicStringStream<StringType> StringSHolder;

			StringSHolder << prm_Number;

			return StringSHolder.str().;
		}

		/*!
		*/
		template<typename StringType>
		static int32 Compare(const BasicString<StringType>& prm_A, const BasicString<StringType>& prm_B, bool CaseSens)
		{
			//! Checks if the comparison will be sensitive about Upper and Lower case
			if (CaseSens)
			{
				//! Invoke the standard string function compare
				return (int32)prm_A.compare(prm_B);
			}

			//! If not, either convert to uppercase or lowercase both strings, and then compare them
			int Size = (int32)std::min(prm_A.size(), prm_B.size());
			for (int32 i = 0; i < Size; i++)
			{
				if (toupper(prm_A[i]) < toupper(prm_B[i]))
					return -1;
				if (toupper(prm_A[i]) > toupper(prm_B[i]))
					return 1;
			}

			return (prm_A.size() < prm_B.size() ? -1 : prm_A.size() == prm_B.size() ? 0 : 1);
		}

		/*!
		*/
		template<typename StringType>
		static Vector<BasicString<StringType>> Split(const BasicString<StringType>& prm_A, const BasicString<StringType>& prm_Delim)
		{
			BasicStringStream<StringType> BSS(prm_A);
			Vector<BasicString<StringType>> TokenVector;
			SIZE_T Pos = 0;

			while ((pos = BSS.str().find(prm_Delim)) != BasicString<StringType>::npos)
			{
				BasicString<StringType> Token = SubStr(BSS.str(), 0, Pos);
				TokenVector.push_back(Token);
			}
			return TokenVector;
		}

		/*!
		*/
		template<typename StringType>
		static BasicString<StringType> Trim(const BasicString<StringType>& prm_A, const BasicString<StringType>& prm_Delim)
		{
			BasicStringStream<StringType> BSS(prm_A);

			std::remove(BSS.str().begin(), BSS.str().end(), prm_Delim);

			return BSS.str();
		}
	};
}