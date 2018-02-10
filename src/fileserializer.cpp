/*
    
  This file is a part of SerUt, a library containing some serialization
  utilities.
  
  Copyright (C) 2008 Jori Liesenborgs

  Contact: jori.liesenborgs@gmail.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  
  USA

*/

#include "fileserializer.h"

namespace serut
{

#define FILESERIALIZER_ERRSTR_ALREADYOPEN			"A file has already been opened"
#define FILESERIALIZER_ERRSTR_NOTOPEN				"No file has been opened yet"
#define	FILESERIALIZER_ERRSTR_CANTOPEN				"Unable to open the specified file"
#define FILESERIALIZER_ERRSTR_INCOMPLETEWRITE			"Couldn't write all the data to the file"
#define FILESERIALIZER_ERRSTR_INCOMPLETEREAD			"Couldn't read the requested amount of data from the file"
#define FILESERIALIZER_ERRSTR_NOREADSUPPORT			"The file was not opened for reading"
#define FILESERIALIZER_ERRSTR_NOWRITESUPPORT			"The file was not opened for writing"
	
FileSerializer::FileSerializer()
{
	m_pFile = 0;
}

FileSerializer::~FileSerializer()
{
	close();
}

bool FileSerializer::open(const std::string &filename, OpenMode m)
{
	if (m_pFile != 0)
	{
		setErrorString(FILESERIALIZER_ERRSTR_ALREADYOPEN);
		return false;
	}
	
	m_mode = m;

	std::string modeString;
	
	if (m == FileSerializer::ReadOnly)
		modeString = std::string("r");
	else if (m == FileSerializer::WriteOnly)
		modeString = std::string("w");
	else
		modeString = std::string("rw");
			
	m_pFile = fopen(filename.c_str(), modeString.c_str());
	if (m_pFile == 0)
	{
		setErrorString(FILESERIALIZER_ERRSTR_CANTOPEN);
		return false;
	}
	return true;
}

bool FileSerializer::close()
{
	if (m_pFile == 0)
	{
		setErrorString(FILESERIALIZER_ERRSTR_NOTOPEN);
		return false;
	}
	
	fclose(m_pFile);
	m_pFile = 0;

	return true;
}

bool FileSerializer::readBytes(void *pBuffer, size_t amount)
{
	if (m_pFile == 0)
	{
		setErrorString(FILESERIALIZER_ERRSTR_NOTOPEN);
		return false;
	}
		
	if (!(m_mode == FileSerializer::ReadOnly || m_mode == FileSerializer::ReadWrite))
	{
		setErrorString(FILESERIALIZER_ERRSTR_NOREADSUPPORT);
		return false;
	}

	if (fread(pBuffer, 1, amount, m_pFile) != amount)
	{
		setErrorString(FILESERIALIZER_ERRSTR_INCOMPLETEREAD);
		return false;
	}

	return true;
}

bool FileSerializer::writeBytes(const void *pBuffer, size_t amount)
{
	if (m_pFile == 0)
	{
		setErrorString(FILESERIALIZER_ERRSTR_NOTOPEN);
		return false;
	}
		
	if (!(m_mode == FileSerializer::WriteOnly || m_mode == FileSerializer::ReadWrite))
	{
		setErrorString(FILESERIALIZER_ERRSTR_NOWRITESUPPORT);
		return false;
	}

	if (fwrite(pBuffer, 1, amount, m_pFile) != amount)
	{
		setErrorString(FILESERIALIZER_ERRSTR_INCOMPLETEWRITE);
		return false;
	}
	
	return true;
}

} // end namespace

