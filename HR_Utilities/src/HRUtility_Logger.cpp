#include "HRUtility_Logger.h"

namespace HR_SDK
{
	/*!********************************************************************************************************************************************************************
	
	***********************************************************************************************************************************************************************/
	void C_Logger::Init(const String& prm_FileName)
	{
		m_MessageList.clear();

		//! Allocate memory for the file, and create it's memory block
		m_LoggerFile = new C_Filestream(FileAccess::_WRITE);
		
		//! Open the file 
		if (m_LoggerFile->Open(prm_FileName, false))
		{
			//! File opens succesfully...
		}

		else
		{
			//! Else, file is doesn't exist, so create it
			m_LoggerFile->Open(prm_FileName, true);
		}
	}

	void C_Logger::AddEntry(MessageLevel::E prm_Level, const String& prm_Message, const String& File, const String& Function, uint32 Line)
	{
		//! Create a basic entry to write in the loggger
		Shared_Ptr<S_LoggerEntry> Entry = std::make_shared<S_LoggerEntry>();

		String Holder;
		//! Format message according to level
		if (prm_Level == MessageLevel::_MESSAGE)
			Holder = "<tr>\n<td bgcolor = \"#33cc33;\"  style=\"font-family:verdana;text-align:center;\">" + prm_Message + "</td>" + "<td bgcolor = \"#33cc33\" style=\"font-family:verdana;text-align:center;\">" + File + "</td>" + "<td bgcolor = \"#33cc33\" style=\"font-family:verdana;text-align:center;\">" + Function + "</td>" + "<td bgcolor = \"#33cc33\" style=\"font-family:verdana;text-align:center;\">" + std::to_string(Line) + "</td>" + "\n</tr>";
		//! Format message according to level
		if (prm_Level == MessageLevel::_WARNING)
			Holder = "<tr>\n<td bgcolor = \"#ffff00;\" style=\"font-family:verdana;text-align:center;\">" + prm_Message + "</td>" + "<td bgcolor = \"#ffff00\" style=\"font-family:verdana;text-align:center;\">" + File + "</td>" + "<td bgcolor = \"#ffff00\" style=\"font-family:verdana;text-align:center;\">" + Function + "</td>" + "<td bgcolor = \"#ffff00\" style=\"font-family:verdana;text-align:center;\">" + std::to_string(Line) + "</td>" + "\n</tr>";
		//! Format message according to level
		if (prm_Level == MessageLevel::_ERROR)
			Holder = "<tr>\n<td bgcolor = \"#ff9999;\" style=\"font-family:verdana;text-align:center;\">" + prm_Message + "</td>" + "<td bgcolor = \"#ff9999\" style=\"font-family:verdana;text-align:center;\">" + File + "</td>" + "<td bgcolor = \"#ff9999\" style=\"font-family:verdana;text-align:center;\">" + Function + "</td>" + "<td bgcolor = \"#ff9999\" style=\"font-family:verdana;text-align:center;\">" + std::to_string(Line) + "</td>" + "\n</tr>";
		//! Format message according to level
		if (prm_Level == MessageLevel::_FATAL_ERROR)
			Holder = "<tr>\n<td bgcolor = \"#ff0000;\" style=\"font-family:verdana;text-align:center;\">" + prm_Message + "</td>" + "<td bgcolor = \"#ff0000\" style=\"font-family:verdana;text-align:center;\">" + File + "</td>" + "<td bgcolor = \"#ff0000\" style=\"font-family:verdana;text-align:center;\">" + Function + "</td>" + "<td bgcolor = \"#ff0000\" style=\"font-family:verdana;text-align:center;\">" + std::to_string(Line) + "</td>" + "\n</tr>";

		//! Prevent access violation
		String EntryMsg(Holder.size() + 1, 0);
		EntryMsg.insert(EntryMsg.begin(), Holder.c_str(), Holder.c_str() + Holder.size());

		Entry->m_Message = EntryMsg;

		m_MessageList.push_back(Entry);
	}

	void C_Logger::Close(const String& LogTitle)
	{
		char Part1[] = 
		{ "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>" };
		char Part2[] = 
		{ "</title>" };
		char Part3[] = 
		{ "\n\t\t<style>\n\t\ttable{border-collapse: collapse;width: 100 % ;}table, td, th {border: 1px solid #000;text - align: center;}th, td{padding: 12px;}\n</style>\n</head>\n<body><h1 style=\"font-family:verdana;text-align:center;\">\n" };
		char Part4[] = 
		{ "\n</h1>\n<p style=\"font-family:verdana;text-align:center;\"><b>" };
		char Part5[] = 
		{ "</b></p><table align=\"center\">\n" };

		m_LoggerFile->Write(Part1, sizeof(Part1));
		m_LoggerFile->Write((char*)(LogTitle.c_str()), LogTitle.size());
		m_LoggerFile->Write(Part2, sizeof(Part2));
		m_LoggerFile->Write(Part3, sizeof(Part3));
		m_LoggerFile->Write((char*)(LogTitle.c_str()), LogTitle.size());
		m_LoggerFile->Write(Part4, sizeof(Part4));
		String LogDate = C_Time::GetDate(Date::_LITTLE_ENDIAN, Time::_24HRS).c_str();
		m_LoggerFile->Write((char*)LogDate.c_str(), LogDate.size());
		m_LoggerFile->Write(Part5, sizeof(Part5));
		for (uint32 i = 0; i < m_MessageList.size(); ++i)
		{
			String Message = m_MessageList[i]->m_Message;
			m_LoggerFile->Write((char*)Message.c_str(), Message.size());
		}

		char Final[] = { "</table>\n</body>\n</html>" };
		m_LoggerFile->Write(Final, sizeof(Final));

		//! Save the file...
		m_LoggerFile->Close();

		delete m_LoggerFile;
		m_MessageList.clear();
	}
}
