#pragma once



#include "HREngine_Prerequisites.h"
#include "HREngine_Emitter.h"
#include "HREngine_Force.h"



/*!******************************************************************************************************************************************************************************

	@file		HREngine_ParticleSystem.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	This file contains the declaration of C_ParticleSystem class.
	This class defines a particle system object, used to render instances of images to simulate objects on the world

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	@date		27-09-2017
	@author		Manuel Aldair Santos Ram�n [ManuSanRam]
	@copyright	Infernal Coders S.A

********************************************************************************************************************************************************************************/



namespace HR_SDK
{
	/*!**************************************************************************************************************************************************************************

		@brief Particle system object to create SVFX

	****************************************************************************************************************************************************************************/
	class HR_ENGINE_EXPORT C_ParticleSystem
	{
	public:
		/*!**********************************************************************************************************************************************************************

			@brief Constructor [Default]

		************************************************************************************************************************************************************************/
		C_ParticleSystem()
		{

		}


		/*!**********************************************************************************************************************************************************************
		
			@brief Destructor
		
		************************************************************************************************************************************************************************/
		~C_ParticleSystem()
		{

		}


		/*!**********************************************************************************************************************************************************************
		
			@brief
		
		************************************************************************************************************************************************************************/
		bool			Init();
		
		/*!**********************************************************************************************************************************************************************
		
			@brief
		
		************************************************************************************************************************************************************************/
		void			Play();
		
		/*!**********************************************************************************************************************************************************************
		
			@brief
		
		************************************************************************************************************************************************************************/
		void			Pause();
		
		/*!**********************************************************************************************************************************************************************
		
			@brief
		
		************************************************************************************************************************************************************************/
		void			Stop();



		/*!**********************************************************************************************************************************************************************

			@brief Number of emitters contained in the particle system

		************************************************************************************************************************************************************************/
		Vector<C_Emitter> m_Emitters;

		/*!**********************************************************************************************************************************************************************

			@brief Number of forces affecting the particles

		************************************************************************************************************************************************************************/
		Vector<C_Force> m_Forces;
	};
}