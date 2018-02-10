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

#include "serializationinterface.h"

namespace serut
{

#define SERIALIZATIONINTERFACE_MAXSTRINGLENGTH				65535

#define SERIALIZATIONINTERFACE_ERRSTR_STRINGTOOLONG			"Specified string is longer than 65535"

bool SerializationInterface::writeString(const std::string &x)
{
	if (x.length() >= SERIALIZATIONINTERFACE_MAXSTRINGLENGTH)
	{
		setErrorString(SERIALIZATIONINTERFACE_ERRSTR_STRINGTOOLONG);
		return false;
	}
	
	uint16_t length = (uint16_t)x.length();
	
	if (!writeSingle(length))
		return false;
	if (!writeBytes(x.c_str(), x.length()))
		return false;
	return true;
}

bool SerializationInterface::readString(std::string &x)
{
	int16_t length;
	
	if (!readSingle(&length))
		return false;

	// TODO: this can probably be done a bit more efficiently
	
	size_t length2 = (size_t)length;
	
	std::vector<char> buffer(length2 + 1);
	
	if (!readBytes(&(buffer[0]), length2))
		return false;

	buffer[length2] = 0;
	x = std::string((const char *)&(buffer[0]));
	
	return true;
}

} // end namespace

