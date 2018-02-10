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
 * \file memoryserializer.h
 */

#ifndef SERUT_MEMORYSERIALIZER_H

#define SERUT_MEMORYSERIALIZER_H

#include "serializationinterface.h"

namespace serut
{

/** A serializer for reading from and writing to memory. */
class MemorySerializer : public SerializationInterface
{
public:
	/** Construct an instance.
	 *  Construct an instance.
	 *  \param pReadBuffer Buffer from which data may be read.
	 *  \param readSize The amount of bytes which may be read.
	 *  \param pWriteBuffer Buffer to which data may be written.
	 *  \param writeSize The amount of bytes which may be written.
	 */
	MemorySerializer(const void *pReadBuffer, size_t readSize,
			 void *pWriteBuffer, size_t writeSize);

	~MemorySerializer();
	
	/** Returns the amount of bytes that have currently been read. */
	size_t getBytesRead() const							{ return m_readPosition; }

	/** Returns the amount of bytes that have currently been written. */
	size_t getBytesWritten() const							{ return m_writePosition; }
	
	bool readBytes(void *pBuffer, size_t amount);
	bool writeBytes(const void *pBuffer, size_t amount);
private:
	const uint8_t *m_pReadBuffer;
	uint8_t *m_pWriteBuffer;
	size_t m_readPosition;
	size_t m_writePosition;
	size_t m_readSize;
	size_t m_writeSize;
};

} // end namespace

#endif // SERUT_MEMORYSERIALIZER_H

