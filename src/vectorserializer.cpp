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

#include "vectorserializer.h"
#include <string.h>

using namespace std;

namespace serut
{

VectorSerializer::VectorSerializer()
{
	m_readPos = 0;
}

VectorSerializer::VectorSerializer(const vector<uint8_t> &initialBuffer)
{
	m_readPos = 0;
	m_bytes = initialBuffer;
}

VectorSerializer::~VectorSerializer()
{
}

bool VectorSerializer::readBytes(void *pBuffer, size_t amount)
{
	int s = (int)m_bytes.size();
	int left = s - m_readPos;
	if ((int)amount > left)
	{
		setErrorString("Can't read the requested amount");
		return false;
	}

	memcpy(pBuffer, &(m_bytes[m_readPos]), amount);
	m_readPos += (int)amount;

	return true;
}

bool VectorSerializer::writeBytes(const void *pBuffer, size_t amount)
{
	int s = (int)m_bytes.size();
	m_bytes.resize(s + (int)amount);

	memcpy(&(m_bytes[s]), pBuffer, amount);
	
	return true;
}

} // end namespace
