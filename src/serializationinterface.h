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
 * \file serializationinterface.h
 */

#ifndef SERUT_SERIALIZATIONINTERFACE_H

#define SERUT_SERIALIZATIONINTERFACE_H

#include <errut/errorbase.h>
#include <sys/types.h>
#include <inttypes.h>
#include <vector>

namespace serut
{

/** Generic serialization interface. 
 *  This class is the core of the package, as it describes the general
 *  serialization interface. Only the SerializationInterface::readBytes
 *  and SerializationInterface::writeBytes member functions need to be
 *  implemented in a derived class, the other member functions use those
 *  two virtual functions to implement their functionality.
 *
 *  Note that currently functions like SerializationInterface::writeDouble
 *  simply serialize the bytes in the same order as they are stored in
 *  memory. This means that byte ordering (endianness) of the host system
 *  is not taken into account and that this package is currently only
 *  useful for communication between systems with the same endianness.
 */
class SerializationInterface : public errut::ErrorBase
{
public:
	SerializationInterface()						{ }
	~SerializationInterface()						{ }
	
	/** Read a specific amount of data from the serializer.
	 *  Read a specific amount of data from the serializer. This must
	 *  be implemented in a derived class.
	 *  \param pBuffer Buffer to store the data in.
	 *  \param amount The number of bytes to read.
	 */
	virtual bool readBytes(void *pBuffer, size_t amount) = 0;

	/** Write a specific amount of data to the serializer.
	 *  Write a specific amount of data to the serializer.
	 *  \param pBuffer Pointer to the data which should be written.
	 *  \param amount The number of bytes that should be written.
	 */
	virtual bool writeBytes(const void *pBuffer, size_t amount) = 0;

	/** Write a double. */
	bool writeDouble(double x)						{ return writeSingle(x); }

	/** Write a float. */
	bool writeFloat(float x)						{ return writeSingle(x); }

	/** Write a 32-bit integer. */
	bool writeInt32(int32_t x)						{ return writeSingle(x); }
	
	/** Write an array of doubles. */
	bool writeDoubles(const double *pX, size_t amount)			{ return writeArray(pX, amount); }

	/** Write an array of floats. */
	bool writeFloats(const float *pX, size_t amount)			{ return writeArray(pX, amount); }

	/** Write an array of 32-bit integers. */
	bool writeInt32s(const int32_t *pX, size_t amount)			{ return writeArray(pX, amount); }

	/** Write the doubles stored in the vector. */
	bool writeDoubles(const std::vector<double> &x)				{ return writeStdVector(x); }

	/** Write the floats stored in the vector. */
	bool writeFloats(const std::vector<float> &x)				{ return writeStdVector(x); }

	/** Write the 32-bit integers which are stored in the vector. */
	bool writeInt32s(const std::vector<int32_t> &x)				{ return writeStdVector(x); }

	/** Write a string. */
	bool writeString(const std::string &x);
	
	/** Read a double. */
	bool readDouble(double *pX)						{ return readSingle(pX); }

	/** Read a float. */
	bool readFloat(float *pX)						{ return readSingle(pX); }

	/** Read a 32-bit integer. */
	bool readInt32(int32_t *pX)						{ return readSingle(pX); }

	/** Read an array of doubles. */
	bool readDoubles(double *pX, size_t amount)				{ return readArray(pX, amount); }

	/** Read an array of floats. */
	bool readFloats(float *pX, size_t amount)				{ return readArray(pX, amount); }

	/** Read an array of 32-bit integers. */
	bool readInt32s(int32_t *pX, size_t amount)				{ return readArray(pX, amount); }

	/** Read a vector of doubles (the current size of the vector specifies the amount). */
	bool readDoubles(std::vector<double> &x)				{ return readStdVector(x); }

	/** Read a vector of floats (the current size of the vector specifies the amount). */
	bool readFloats(std::vector<float> &x)					{ return readStdVector(x); }

	/** Read a vector of 32-bit integers (the current size of the vector specifies the amount). */
	bool readInt32s(std::vector<int32_t> &x)				{ return readStdVector(x); }

	/** Read a string. */
	bool readString(std::string &x);
private:
	template<class T>
	bool writeSingle(T x)
	{
		if (!writeBytes(&x, sizeof(T)))
			return false;
		return true;
	}

	template<class T>
	bool readSingle(T *x)
	{
		if (!readBytes(x, sizeof(T)))
			return false;
		return true;
	}

	template<class T>
	bool writeArray(const T *x, size_t amount)
	{
		if (!writeBytes(x, sizeof(T)*amount))
			return false;
		return true;
	}

	template<class T>
	bool readArray(T *x, size_t amount)
	{
		if (!readBytes(x, sizeof(T)*amount))
			return false;
		return true;
	}

	template<class T>
	bool writeStdVector(const std::vector<T> &v)
	{
		return writeArray(&(v[0]), v.size());
	}

	template<class T>
	bool readStdVector(std::vector<T> &v)
	{
		return readArray(&(v[0]), v.size());
	}
};

} // end namespace

#endif // SERUT_SERIALIZATIONINTERFACE_H

