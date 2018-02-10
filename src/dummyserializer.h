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
 * \file dummyserializer.h
 */

#ifndef SERUT_DUMMYSERIALIZER_H

#define SERUT_DUMMYSERIALIZER_H

#include "serializationinterface.h"

namespace serut
{

/** A dummy serializer which simply counts the number of bytes written but does
 *  not actually write any data. */
class DummySerializer : public SerializationInterface
{
public:
	DummySerializer()								{ m_counter = 0; }
	~DummySerializer()								{ }
	
	/** Returns the number of bytes that currently have been written. */
	size_t getBytesWritten() const							{ return m_counter; }
	
	bool readBytes(void *pBuffer, size_t amount);
	bool writeBytes(const void *pBuffer, size_t amount)				{ m_counter += amount; return true; }
private:
	size_t m_counter;
};

} // end namespace

#endif // SERUT_DUMMYSERIALIZER_H

