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

#include "tcpserializer.h"
#include <enut/tcpsocket.h>

namespace serut
{

#define TCPSERIALIZER_ERRSTR_COULDNTREAD		"Couldn't read data from TCP stream: "
#define TCPSERIALIZER_ERRSTR_COULDNTWRITE		"Couldn't write data to TCP stream: "
#define TCPSERIALIZER_ERRSTR_INCOMPLETEWRITE		"The amount of bytes written to the TCP stream is less than expected"
#define TCPSERIALIZER_ERRSTR_INCOMPLETEREAD		"The amount of bytes read from the TCP stream is less than expeced"

TCPSerializer::TCPSerializer(nut::TCPSocket *pSocket, bool deleteSocket)
{
	m_pSocket = pSocket;
	m_deleteSocket = deleteSocket;
}

TCPSerializer::~TCPSerializer()
{
	if (m_deleteSocket)
		delete m_pSocket;
}
	
bool TCPSerializer::readBytes(void *pBuffer, size_t amount)
{
	size_t num = amount;

	if (!m_pSocket->read(pBuffer, num))
	{
		setErrorString(std::string(TCPSERIALIZER_ERRSTR_COULDNTREAD) + m_pSocket->getErrorString());
		return false;
	}

	if (num != amount)
	{
		setErrorString(TCPSERIALIZER_ERRSTR_INCOMPLETEREAD);
		return false;
	}
	
	return true;
}

bool TCPSerializer::writeBytes(const void *pBuffer, size_t amount)
{
	size_t num = amount;

	if (!m_pSocket->write(pBuffer, num))
	{
		setErrorString(std::string(TCPSERIALIZER_ERRSTR_COULDNTWRITE) + m_pSocket->getErrorString());
		return false;
	}

	if (num != amount)
	{
		setErrorString(TCPSERIALIZER_ERRSTR_INCOMPLETEWRITE);
		return false;
	}
	
	return true;
}

} // end namespace
