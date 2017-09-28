#pragma once

/*!******************************************************************************************************************************************************************************
	
	@file		HRUtility_PlatformMath.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	This file contains mathematic functions used inside the engine, contained inside a Platform-independent Math class.
	The mathematic operations are as follows(in order):
	- Absolute value (Integer and Floating-point).
	- Pi (Normal, inverted, half and two-times)
	- Euler constant.
	- Minimum and maximum integer limits.
	- Degree <-> Radian conversions.
	- Infinite limits.
	- Error margins.
	- Thresholds.
	- Truncations (Integer and Floating-point).
	- Roundings (Floor, Round, Ceil).
	- Fractional.
	- Modulo.
	- Power.
	- Exponential.
	- Logarithms (n-base, 2-base, x-base).
	- Square roots - Normal and Inverted (Includes degrees and radians square roots).
	- Check for limits (NaN, infinite and negative number).
	- Trigonometric - Sine[Arc], Cosine[Arc], Tangent[Arc, Arc2] (Degrees and Radians).
	- Linear interpolation.
	- Minimum and maximum number.
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date	    20-09-2016
	@author		Manuel Aldair Santos Ramón (ManuSanRam)
	@copyright	Infernal Coders S.A.

********************************************************************************************************************************************************************************/

#include "HRUtility_Prerequisites.h"

namespace HR_SDK
{
	/*!

		@class C_PlatformMath
		@brief Class that contains the engine's mathematic library

	*/
	MS_ALIGN(16) class HR_UTILITY_EXPORT C_PlatformMath
	{
	public:
		///!*************************************************************************************************************************************************************************

			//! CONSTANTS

			/*
				- Pi number.
				- Euler number(e).
				- Type limits.
				- Degree < -> Radian.
				- Infinite limits.
				- Error margins.
				- Thresholds.
			*/

		///!*************************************************************************************************************************************************************************
		/*!
			@brief Describes the Pi number, obtained as 4 multiplied by the arctangent of 1.0
		*/
		static const float   m_Pi;
		

		/*!
			@brief Describes the inverse factor of Pi, obtained simply as 1.0 divided by Pi.
		*/
		static const float   m_Inv_Pi;
		

		/*!
			@brief Describes the value of Pi divided by 2.0.
		*/
		static const float   m_Half_Pi;
		

		/*!
			@brief Describes the value of Pi multiplied by 2.0.
		*/
		static const float   m_Two_Pi;


		/*!
			@brief Describes the value of the Euler number, the base of natural logarithms.
		*/
		static const float   m_Euler;


		/*!
			@brief Describes the minimum limit of the unsigned 8-bit integer type.
		*/
		static const uint8   m_Min_uint8;
		

		/*!
			@brief Describes the minimum limit of the unsigned 16-bit integer type.
		*/
		static const uint16  m_Min_uint16;
		

		/*!
			@brief Describes the minimum limit of the unsigned 32-bit integer type.
		*/
		static const uint32  m_Min_uint32;
		

		/*!
			@brief Describes the minimum limit of the unsigned 64-bit integer type.
		*/
		static const uint64  m_Min_uint64;
		

		/*!
			@brief Describes the minimum limit of the unsigned 128-bit integer type.
		*/
		static const uint128 m_Min_uint128;
		

		/*!
			@brief Describes the minimum limit of the signed 8-bit integer type.
		*/
		static const int8    m_Min_int8;
		

		/*!
			@brief Describes the minimum limit of the signed 16-bit integer type.
		*/																  
		static const int16   m_Min_int16;								  
		

		/*!																  
			@brief Describes the minimum limit of the signed 32-bit integer type.
		*/																  
		static const int32   m_Min_int32;								  
		

		/*!																  
			@brief Describes the minimum limit of the signed 64-bit integer type.
		*/
		static const int64   m_Min_int64;
		

		/*!
			@brief Describes the minimum limit of the signed 128-bit integer type.
		*/
		static const int128  m_Min_int128;
		

		/*!
			@brief Describes the minimum limit of the float type.
		*/
		static const float   m_Min_float;
		

		/*!
			@brief Describes the maximum limit of the unsigned 8-bit integer type.
		*/
		static const uint8   m_Max_uint8;
		

		/*!
			@brief Describes the maximum limit of the unsigned 16-bit integer type.
		*/
		static const uint16  m_Max_uin16;
		

		/*!
			@brief Describes the maximum limit of the unsigned 32-bit integer type.
		*/
		static const uint32  m_Max_uint32;
		

		/*!
			@brief Describes the maximum limit of the unsigned 64-bit integer type.
		*/
		static const uint64  m_Max_uint64;
		

		/*!
			@brief Describes the maximum limit of the unsigned 128-bit integer type.
		*/
		static const uint128 m_Max_uint128;
		

		/*!
			@brief Describes the maximum limit of the signed 8-bit integer type.
		*/
		static const int8    m_Max_int8;
		

		/*!
			@brief Describes the maximum limit of the signed 16-bit integer type.
		*/
		static const int16   m_Max_int16;
		

		/*!
			@brief Describes the maximum limit of the signed 32-bit integer type.
		*/
		static const int32   m_Max_int32;
		

		/*!
			@brief Describes the maximum limit of the signed 64-bit integer type.
		*/
		static const int64   m_Max_int64;
		

		/*!
			@brief Describes the maximum limit of the signed 128-bit integer type.
		*/
		static const int128  m_Max_int128;
		

		/*!
			@brief Describes the maximum limit of the float type.
		*/
		static const float   m_Max_float;
		

		/*!
			@brief Describes the constant conversion from degrees to radians
		*/
		static const float	 m_DegreeToRadian;


		/*!
			@brief Describes the constant conversion from radians to degrees
		*/
		static const float   m_RadianToDegree;


		/*!
			@brief Highest limit closer to the positive infinite 
		*/
		static const float   m_Pos_Infinite;


		/*!
			@brief Highest limit closer to the negative infinite
		*/
		static const float   m_Neg_Infinite;
			

		static const float   m_LogB2;


		static const float   m_Delta;


		static const float   m_SmallNumber;


		static const float   m_SmallNumber_Float;


		static const float   m_SmallNumber_Kinda;


		static const float   m_BigNumber;


		static const float   m_BigNumber_Kinda;


		static const float   m_Epsilon_Float;


		static const float   m_Epsilon_Double;


		static const float   m_Threshold_PointOnPlane;


		static const float   m_Threshold_PointOnSide;


		static const float   m_Threshold_PointsAreSame;


		static const float   m_Threshold_PointsAreClose;


		static const float   m_Threshold_NormalAreSame;


		static const float   m_Threshold_VectorsAreClose;


		static const float   m_Threshold_SplitPolyWithPlane;


		static const float   m_Threshold_SplitPolyPrecise;


		static const float   m_Threshold_ZeroOnPlane;


		static const float   m_Threshold_NormalsAreParallel;


		static const float   m_Threshold_NormalsAreOrthogonal;


		static const float   m_Threshold_VectorNormalized;


		static const float   m_Threshold_QuaternionNormalized;



		///!**********************************************************************************************************************************************************************
			
			//! METHODS
			/*
				- Truncation.
				- Roundings.
				- Modulo.
				- Power and scientific notation.
				- Checkings.
				- Square root.
				- Trigonometric.
				- Linear interpolation.
				- Minimum and Maximum
			*/

		///!*********************************************************************************************************************************************************************
		///!*********************************************************************************************************************************************************************
			
			//! TRUNCATIONS
		
		///!*********************************************************************************************************************************************************************
		/*!**********************************************************************************************************************************************************************
		
			@brief Truncates a floating number to a given value

			@param _value

			@return 
		
		************************************************************************************************************************************************************************/
		static FORCEINLINE int32 Truncation(float _value) 
		{
			return (int32)_value;
		}


		/*!**************************************************************************************************************************************************************************

			@brief Defines the fractional operation (Fractional part of a floating-point number).

			@param

			@return

		*****************************************************************************************************************************************************************************/
		static FORCEINLINE float TruncationFloat(float _value) 
		{
			return (float)Truncation(_value);
		}


		///!*********************************************************************************************************************************************************************

			//! ROUNDINGS

		///!*********************************************************************************************************************************************************************
		/*!**************************************************************************************************************************************************************************

			@brief Defines the fractional operation (Fractional part of a floating-point number).

			@param

			@return

		*****************************************************************************************************************************************************************************/
		static FORCEINLINE float Floor(float _value) 
		{
			return TruncationFloat(std::floor(_value));
		}


		/*!**************************************************************************************************************************************************************************

			@brief Defines the fractional operation (Fractional part of a floating-point number).

			@param

			@return

		*****************************************************************************************************************************************************************************/
		static FORCEINLINE float Round(float _value) 
		{
			return TruncationFloat(std::round(_value));
		}


		/*!**************************************************************************************************************************************************************************

			@brief Defines the fractional operation (Fractional part of a floating-point number).

			@param

			@return

		*****************************************************************************************************************************************************************************/
		static FORCEINLINE float Ceil(float _value) 
		{
			return TruncationFloat(std::ceil(_value));
		}


		/*!**************************************************************************************************************************************************************************

			@brief Defines the fractional operation (Fractional part of a floating-point number).

			@param

			@return

		*****************************************************************************************************************************************************************************/
		static FORCEINLINE float Fractional(float _value) 
		{
			return (_value - Truncation(_value));
		}


		/*!**************************************************************************************************************************************************************************
			
			@brief Defines the modulo operation (Remainder of a division).
			
		-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param _numer Dividend factor for the modulo operation.
			@param _denom Divisor factor for the modulo operation.
			
		-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return The remaining/residual part of the division
		
		*****************************************************************************************************************************************************************************/
		template<class Real_Number>
		static FORCEINLINE Real_Number Modulo(Real_Number _numer, Real_Number _denom) 
		{
			return (Real_Number)std::fmod(_numer, _denom);
		}


		///!*********************************************************************************************************************************************************************

			//! EXPONENTS

		///!*********************************************************************************************************************************************************************
		/*!
		
		

		*/
		template<class Real_Number>
		static FORCEINLINE Real_Number Power(Real_Number _base, Real_Number _exp) 
		{
			return (_exp <= 0) ? 1 : (Real_Number)std::pow(_base, _exp) ;
		}


		/*!
		


		*/
		template<class Real_Number>
		static FORCEINLINE float Exponential(Real_Number prm_Value) 
		{
			return (float)std::exp(prm_Value);
		}


		/*!
		

		
		*/
		template<class Real_Number>
		static FORCEINLINE Real_Number Factorial(Real_Number prm_Number)
		{
			return(prm_Number == 1 || prm_Number == 0) ? 1 : Factorial(prm_Number - 1) * prm_Number;
		}


		///!*********************************************************************************************************************************************************************

			//! LOGARITHMS

		///!*********************************************************************************************************************************************************************
		/*!
		

		
		*/
		static FORCEINLINE float LogNat(float prm_Value) 
		{
			return (float)std::log(prm_Value);
		}


		/*!
		


		*/
		static FORCEINLINE float LogB2(float prm_Value);
		

		/*!
		

		
		*/
		static FORCEINLINE float LogBX(float prm_Base, float prm_Value) 
		{
			return LogNat(prm_Base) / LogNat(prm_Value);
		}


		///!*********************************************************************************************************************************************************************

			//! SQUARE ROOT

		///!*********************************************************************************************************************************************************************
		/*!
		

		
		*/
		template<class Real_Number>
		static FORCEINLINE float SqRoot(Real_Number prm_Value) 
		{
			return (float)std::sqrt(prm_Value);
		}


		///!*********************************************************************************************************************************************************************

			//! CHECKINGS

		///!*********************************************************************************************************************************************************************
		/*!
		
		
		
		*/
		template<class Real_Number>
		static FORCEINLINE bool IsNan(Real_Number prm_Value) 
		{
			return ((*(uint32*)&prm_Value) & 0x7FFFFFFF) > 0x7F800000
		}


		/*!



		*/
		template<class Real_Number>
		static FORCEINLINE bool IsFinite(Real_Number prm_Value) 
		{
			return ((*(uint32*)&prm_Value) & 0x7F800000) != 0x7F800000;
		}


		/*!
		
		

		*/
		template<class Real_Number>
		static FORCEINLINE bool IsNegative(Real_Number prm_Value) 
		{
			return ((*(uint32*)&prm_Value) >= (uint32)0x80800000);
		}


		///!*********************************************************************************************************************************************************************

			//! TRIGONOMETRY

		///!*********************************************************************************************************************************************************************
		/*!
		*/
		static FORCEINLINE float Sine(float prm_Value) 
		{
			return (float)std::sinf(prm_Value);
		}


		/*!



		*/
		static FORCEINLINE float Cosine(float prm_Value) 
		{
			return (float)std::cosf(prm_Value);
		}


		/*!
		
		
		
		*/
		static FORCEINLINE float Tangent(float prm_Value) 
		{
			return (float)std::tanf(prm_Value);
		}


		/*!
		
		
		
		*/
		static FORCEINLINE float ArcSine(float prm_Value) 
		{
			return (float)std::asinf(prm_Value);
		}


		/*!
		*/
		static FORCEINLINE float ArcCosine(float prm_Value) 
		{
			return (float)std::acosf(prm_Value);
		}


		/*!
		*/
		static FORCEINLINE float ArcTangent(float _value) 
		{
			return (float)std::atanf(_value);
		}


		/*!
		
		

		*/
		static FORCEINLINE float ArcTangent2(float _a, float _b) 
		{
			return (float)std::atan2f(_a, _b);
		}


		///!*********************************************************************************************************************************************************************

			//! INTERPOLATION

		///!*********************************************************************************************************************************************************************
		/*!**********************************************************************************************************************************************************************
		
			@brief Linear interpolation

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param
			@param
			@param

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return
		
		************************************************************************************************************************************************************************/
		template<class Polynomial, class Time>
		static FORCEINLINE Polynomial LinearInterpolation(Polynomial& _a, Polynomial& _b, Time& _time) 
		{
			return (Polynomial)(_a + (_b - _a) * _time);
		}


		///!*********************************************************************************************************************************************************************

			//! MINIMUM AND MAXIMUM

		///!*********************************************************************************************************************************************************************
		/*!**********************************************************************************************************************************************************************
		
			@brief 

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param
			@param

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return
		
		************************************************************************************************************************************************************************/
		template<class Number>
		static FORCEINLINE Number Minimum(Number& prm_A, Number& prm_B) 
		{
		  return (prm_A < prm_B ? prm_A : prm_B);
		}


		/*!**********************************************************************************************************************************************************************

			@brief Get the largest number out of two given ones.
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@param prm_A Reference to the first number given to calculate the largest number
			@param prm_B Reference to the second number given to calculate the largest number
			
		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			@return The largest number between the two given params.
		
		************************************************************************************************************************************************************************/
		template<class Number>
		static FORCEINLINE Number Maximum(Number& _A, Number& _B) 
		{
		  /*! Returns the biggest number between the given params: if true, prm_A is the largest number. Else, prm_B is the largest number */
		  return (_A > _B ? _A : _B);
		}


		///!*********************************************************************************************************************************************************************

			//! INTERSECTIONS

		///!*********************************************************************************************************************************************************************
		/*!**********************************************************************************************************************************************************************
			
			@brief Checks for the intersection between two axis-aligned bounding boxes (AABB).

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@param prm_A AABB to be checked if it intersects with another AABB in any of its vertices.																		   
			@param prm_B AABB to be checked if it intersects with another AABB in any of its vertices.

		-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			
			@return Returns true if any vertex of both prm_A and prm_B are inside the other AABB's area.																	
		
		************************************************************************************************************************************************************************/
		static FORCEINLINE bool Intersection_AABBvAABB(const C_AABB& prm_A, const C_AABB& prm_B);


		/**/
		static FORCEINLINE bool Intersection_PlanevPlane(C_Plane& prm_A, C_Plane& prm_B);


		/**/
		static FORCEINLINE bool Intersection_BoxvBox(const C_Box& prm_A, const C_Box& prm_B);


		/**/
		static FORCEINLINE bool Intersection_SpherevSphere(const C_Sphere& prm_A, const C_Sphere& prm_B);


		/**/
		static FORCEINLINE bool Intersection_AABBvPlane(const C_AABB& prm_A, const C_Plane& prm_B);


		/**/
		static FORCEINLINE bool Intersection_AABBvBox(const C_AABB& prm_A, const C_Box& prm_B);


		/**/
		static FORCEINLINE bool Intersection_AABBvSphere(const C_AABB& prm_A, const C_Sphere& prm_B);


		/**/
		static FORCEINLINE bool Intersection_AABBvRay(const C_AABB& prm_A, const C_Ray& prm_B);


		/**/
		static FORCEINLINE bool Intersection_AABBvLine(const C_AABB, const C_Line& prm_B);


		/**/
		static FORCEINLINE bool Intersection_PlanevBox(const C_Plane& prm_A, const C_Box& prm_B);


		/**/
		static FORCEINLINE bool Intersection_PlanevSphere(const C_Plane& prm_A, const C_Sphere& prm_B, float& SideOfCollision);


		/**/
		static FORCEINLINE bool Intersection_PlanevRay(const C_Plane& prm_A, const C_Ray& prm_B);


		/**/
		static FORCEINLINE bool Intersection_PlanevLine(const C_Plane, const C_Line& prm_B);


		/**/
		static FORCEINLINE bool Intersection_BoxvSphere(const C_Box& prm_A, const C_Sphere& prm_B);


		/**/
		static FORCEINLINE bool Intersection_BoxvRay(const C_Box& prm_A, const C_Ray& prm_B);


		/**/
		static FORCEINLINE bool Intersection_BoxvLine(const C_Box, const C_Line& prm_B);


		/**/
		static FORCEINLINE bool Intersection_SpherevRay(const C_Sphere& prm_A, const C_Ray& prm_B);


		/**/
		static FORCEINLINE bool Intersection_SpherevLine(const C_Sphere, const C_Line& prm_B);

	};
	GCC_ALIGN(16)
}
