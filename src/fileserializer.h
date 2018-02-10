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

/**
 * \file fileserializer.h
 */

#ifndef SERUT_FILESERIALIZER_H

#define SERUT_FILESERIALIZER_H

#include "serializationinterface.h"
#include <stdio.h>
#include <string>

namespace serut
{

/** A serializer for writing to and reading from files. */
class FileSerializer : public SerializationInterface
{
public:
	/** Specifies the mode in which a file can be opened. */
	enum OpenMode 
	{ 
		/** Read-only mode. */
		ReadOnly,
		/** Write-only mode. */
		WriteOnly,
		/** Both reading and writing. */
		ReadWrite
	};
	
	FileSerializer();
	~FileSerializer();
	
	/** Open a file. 
	 *  Open a file.
	 *  \param filename The name of the file to open
	 *  \param m The mode in which the file should be opened.
	 */
	bool open(const std::string &filename, OpenMode m);

	/** Close a previously opened file. */
	bool close();
	
	bool readBytes(void *pBuffer, size_t amount);
	bool writeBytes(const void *pBuffer, size_t amount);
private:
	FILE *m_pFile;
	OpenMode m_mode;
};

} // end namespace

#endif // SERUT_FILESERIALIZER_H

