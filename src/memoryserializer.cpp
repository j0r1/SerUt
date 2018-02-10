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

#include "memoryserializer.h"
#include <string.h>

namespace serut
{

#define MEMORYSERIALIZER_ERRSTR_CANTREADBEYONDBOUNDS		"Trying to read beyond buffer size"
#define MEMORYSERIALIZER_ERRSTR_CANTWRITEBEYONDBOUNDS		"Trying to write beyond buffer size"
	
MemorySerializer::MemorySerializer(const void *pReadBuffer, size_t readSize, void *pWriteBuffer, size_t writeSize)
{
	m_pReadBuffer = (const uint8_t *)pReadBuffer; 
	m_pWriteBuffer = (uint8_t *)pWriteBuffer; 
	m_readSize = readSize; 
	m_writeSize = writeSize; 
	m_readPosition = 0; 
	m_writePosition = 0;
}

MemorySerializer::~MemorySerializer()
{
}

bool MemorySerializer::readBytes(void *pBuffer, size_t amount)
{
	if (amount + m_readPosition > m_readSize)
	{
		setErrorString(MEMORYSERIALIZER_ERRSTR_CANTREADBEYONDBOUNDS);
		return false;
	}

	memcpy(pBuffer, m_pReadBuffer + m_readPosition, amount);
	m_readPosition += amount;
	
	return true;
}

bool MemorySerializer::writeBytes(const void *pBuffer, size_t amount)
{
	if (amount + m_writePosition > m_writeSize)
	{
		setErrorString(MEMORYSERIALIZER_ERRSTR_CANTWRITEBEYONDBOUNDS);
		return false;
	}

	memcpy(m_pWriteBuffer + m_writePosition, pBuffer, amount);
	m_writePosition += amount;
	
	return true;
}

} // end namespace
