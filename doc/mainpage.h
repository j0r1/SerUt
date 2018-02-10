/**\mainpage SerUt
 *
 * \author Jori Liesenborgs
 *
 * \section intro Introduction
 *
 * 	SerUt is a package containing some serialization utilities. 
 *
 * \section copyright Copyright license
 *
 * 	The license which applies to this library is the LGPL. You can find the
 * 	full version in the file \c LICENSE.LGPL which is included in the library
 * 	archive. The short version is the following:
 *
 *	\code
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  
 * USA.
 *	\endcode
 * 	
 * \section using Using the library
 *
 * 	The package containts an abstract class serut::SerializationInterface
 * 	of which only the serut::SerializationInterface::readBytes and 
 * 	serut::SerializationInterface::writeBytes need to be implemented. For the
 * 	available implementations, just take a look at the available classes.
 *
 * 	\warning Currently, the byte ordering of the CPU is not taken into
 * 	         account. This means that the SerUt will not work between
 * 	         machines with different byte ordering. 
 *
 * \section contact Contact
 *
 * 	If you have any questions, remarks or requests, you can contact me at
 * 	\c jori(\c dot)\c liesenborgs(\c at)\c gmail(\c dot)\c com
 *
 */
 
