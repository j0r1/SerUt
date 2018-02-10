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
 * \file tcpserializer.h
 */

#ifndef SERUT_TCPSERIALIZER_H

#define SERUT_TCPSERIALIZER_H

#include "serializationinterface.h"
#include <time.h>

namespace nut
{
	class TCPSocket;
}

namespace serut
{

/** Serializer which can be used to read from and write to a TCP connection. */
class TCPSerializer : public SerializationInterface
{
public:
	/** Construct an instance.
	 *  Construct an instance.
	 *  \param pSocket The socket which should be used for communication.
	 *  \param deleteSocket Flag indicating if the socket should be deleted when
	 *                      this instance is destroyed.
	 */
	TCPSerializer(nut::TCPSocket *pSocket, bool deleteSocket);

	~TCPSerializer();

	/** Returns the socket which is being used for communication. */
	nut::TCPSocket *getSocket()							{ return m_pSocket; }

	bool readBytes(void *pBuffer, size_t amount);
	bool writeBytes(const void *pBuffer, size_t amount);
private:
	nut::TCPSocket *m_pSocket;
	bool m_deleteSocket;
};
	
} // end namespace

#endif // SERUT_TCPSERIALIZER_H
