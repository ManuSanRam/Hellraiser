#include "HRUtility_Directory.h"

namespace HR_SDK
{
	void C_Directory::Init
	(
		const String prm_Dir
	)
	{
		SIZE_T StrSize = prm_Dir.size();
		m_Path.insert(m_Path.begin(), StrSize + 1, 0);

		m_Path.insert(m_Path.begin(), prm_Dir.c_str(), prm_Dir.c_str() + StrSize);
	}
	
	String C_Directory::GetPath
	(

	)
	{
		return m_Path;
	}
	
	/*!********************************************************************************************************************************************************************
	 * @brief Obtains the name of a file from a given path. Used to open a file or just to get a file name
	 * @param[out} prm_FileStr String that will contain the file 
	 * @return A string containing the file name 
	***********************************************************************************************************************************************************************/
	bool C_Directory::ParseFile
	(
		String prm_FileStr
	)
	{
		//! These will serve to hold the parsed data
		String TempPath(1, 0);
		//! Get position to the last slash, to separate path from file name
		SIZE_T StrIndex = m_Path.find_last_of("/\\");

		//! Get path to the file
		TempPath = m_Path.substr(0, StrIndex);
		//! Get file name and extension
		prm_FileStr = m_Path.substr(StrIndex + 1);

		//! Empty path to hold new data
		m_Path.clear();
		//! Append path
		m_Path.append(TempPath);
		//! Check if file string is empty
		if (prm_FileStr.empty())
		{
			return false;
		}

		else
		{
			//! Append file name
			m_Path.append(prm_FileStr);
		}
		//! Clear temporal path to prevent access violation and stack overflow exceptions
		TempPath.clear();
		//! Append one null character to prevent stack overflow
		m_Path.append(1, '\0');
		return true;
	}
	
	void C_Directory::FullPath
	(

	)
	{
		//! Array where to save the full path for the string
		ANSI_CHAR FullPath[MAX_PATH_INIT];
		//! If the full path is succesfully obtained
		if (_fullpath(FullPath, m_Path.c_str(), _MAX_PATH) != NULL)
		{
			//! Get size of full path buffer
			SIZE_T StrSize = sizeof(FullPath);

			//! Init the path string to safely contain full path - filling it with null characters to prevent access violations
			m_Path.insert(m_Path.begin(), StrSize + 1, 0);

			//! Insert information into path string
			m_Path.insert(m_Path.begin(), FullPath, FullPath + StrSize);
		}
	}

	void C_Directory::Close
	(

	)
	{
		if (!m_Path.empty())
		{
			m_Path.clear();
		}
	}
}