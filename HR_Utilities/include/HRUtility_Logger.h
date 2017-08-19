#pragma once

#include "HRUtility_Prerequisites.h"

/*!******************************************************************************************************************************************************************************
	
	@file		HRUtility_Logger.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	This file contains the logger subsystem used by the engine to send message to the user of when a certain event has ocurred.
	The file contains two classes:
	- Logger entry.
		Creates a message to the user. Warns of any runtime events.
	
	- Logger.
		Manages messages and presents them in a format to the user.

	- System logger module.
		Module to create global instances of logger object

	- Logger global instance.
		Global instance of the engine's main logger

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	@date       03-10-2016
	@author		Manuel Aldair Santos Ram�n (ManuSanRam)
	@copyright	Infernal Coders S.A.

********************************************************************************************************************************************************************************/

#include "HRUtility_StringUtil.h"
#include "HRUtility_Time.h"
#include "HRUtility_Datastream.h"

namespace HR_SDK
{
  /*!**********************************************************************************************************************************************************************
   * @brief Level of significance for a message.
   * Four lvels for a message.
   *	- MESSAGE: Normal message to the user.
   *	- WARNING: Warning message of a secondary error event. Doesn't stop the program. 
   *	- ERROR: Warning message of a primary error event. Might stop the program depending of the event.
   *	- FATAL ERROR: Warning message of a vital error event. Stops the program.
  *************************************************************************************************************************************************************************/
  namespace MessageLevel
  {
  	enum E
  	{
  	  /*!******************************************************************************************************************************************************************
  	   * @brief Defines a simple message. Warns the user of any operation executed in the engine.
	   * Not an error, simply displays a message whenever an event is made
  	  *********************************************************************************************************************************************************************/
  	  _MESSAGE,
  	  /*!******************************************************************************************************************************************************************
  	   * @brief Defines a warning message. Warns the user of secondary errors.
  	   * Errors of this kind do not stop the program, only warns user that a secondary system hasn't loaded correctly.
  	  *********************************************************************************************************************************************************************/
  	  _WARNING,
  	  /*!******************************************************************************************************************************************************************
  	   * @brief Defines a simple message. Warns the user of any operation executed in the engine.
	   * Errors of this kind tend to cause unexpected behaviour on the application.
  	  *********************************************************************************************************************************************************************/
  	  _ERROR,
  	  /*!******************************************************************************************************************************************************************
  	   * @brief Defines a simple message. Warns the user of any operation executed in the engine.
	   * Errors of this kind make the program halt instantly, since the program cannot run.
  	  ********************************************************************************************************************************************************************/
  	  _FATAL_ERROR
  	};
  }
  /*!**********************************************************************************************************************************************************************
   * @class S_LoggerEntry
   * @brief Declares the Log entry object, a data stream that holds the message data.
   * Contains the following data:
   * - Message level.
   * - Message string.
  *************************************************************************************************************************************************************************/
  struct HR_UTILITY_EXPORT S_LoggerEntry
  {
	/*!********************************************************************************************************************************************************************
	 * @brief Message displayed by the entry
	***********************************************************************************************************************************************************************/
	String				m_Message;
  };

  /*!**********************************************************************************************************************************************************************
   * @class C_Logger
   * @brief Creates a report of events on certain platform.
  *************************************************************************************************************************************************************************/
  class HR_UTILITY_EXPORT C_Logger
  {
  public:
	/*!********************************************************************************************************************************************************************
	 * @brief Constructor
	***********************************************************************************************************************************************************************/
	C_Logger()
	{
		
	}
	/*!********************************************************************************************************************************************************************
	 * @brief Destructor
	***********************************************************************************************************************************************************************/
	virtual ~C_Logger()
	{
		
	}

	/*!********************************************************************************************************************************************************************
	
	@brief Initializes the logger
	
	***********************************************************************************************************************************************************************/
	void				Init(const String& _FileName);
	/*!********************************************************************************************************************************************************************
	
	@brief Adds a new entry to the 
	
	***********************************************************************************************************************************************************************/
	void				AddEntry(MessageLevel::E _level, const String& _message, const String& _file, const String& _function, uint32 _line);
	/*!********************************************************************************************************************************************************************
	
	@brief Close the logger.
	
	***********************************************************************************************************************************************************************/
	void				Close(const String& _loggerTitle);

	/*!********************************************************************************************************************************************************************
	
	@brief Saves the entries to be printed 
	
	***********************************************************************************************************************************************************************/
	Vector<Shared_Ptr<S_LoggerEntry>>		m_MessageList;
	/*!********************************************************************************************************************************************************************
	
	@brief File to write the entries
	
	***********************************************************************************************************************************************************************/
	C_Filestream*							m_LoggerFile;
  };
}
