/*
    
  This file is a part of SerUt, a library containing some serialization
  utilities.
  
  Copyright (C) 2008-2018 Jori Liesenborgs

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
 * \file vectorserializer.h
 */

#ifndef SERUT_VECTORSERIALIZER_H

#define SERUT_VECTORSERIALIZER_H

#include "serutconfig.h"
#include "serializationinterface.h"
#include <stdint.h>

namespace serut
{

/** A serializer which uses an STL vector, which can grow in size. */
class SERUT_IMPORTEXPORT VectorSerializer : public SerializationInterface
{
public:
	/** Construct an instance with no predefined data - what you read is only what you've written. */
	VectorSerializer();
	/** Construct an instance which will copy the specified initial data - new writes will append, reads will
	 *  start from this initial data. */
	VectorSerializer(const std::vector<uint8_t> &initialBuffer);
	~VectorSerializer();

	bool readBytes(void *pBuffer, size_t amount);
	bool writeBytes(const void *pBuffer, size_t amount);

	/** Returns the vector instance that's being used for reading and writing. */
	const std::vector<uint8_t> &getBuffer() const { return m_bytes; }

	/** Returns a pointer to the first element of the internal buffer (do not use if no data is available!). */
	const unsigned char *getBufferPointer() { return static_cast<const unsigned char *>(&m_bytes[0]); }

	/** Returns the current size of the internal buffer. */
	int getBufferSize() const { return m_bytes.size(); }
private:
	int m_readPos;
	std::vector<uint8_t> m_bytes;
};

} // end namespace

#endif // SERUT_VECTORSERIALIZER_H
