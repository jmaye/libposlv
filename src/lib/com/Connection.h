/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file Connection.h
    \brief This file defines the Connection class, which implements the phyiscal
           connection to the device
  */


#ifndef CONNECTION_H
#define CONNECTION_H

#include "exceptions/IOException.h"
#include "types/Group.h"

#include <string>

#include <stdint.h>

/** The class Connection represents a phyiscal connection to the device.
    \brief Connection
  */
class Connection {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Connection(const Connection& other);
  /// Assignment operator
  Connection& operator = (const Connection& other);
  /** @}
    */

  /** \name Private methods
    @{
    */
  /// Reads a byte from the device
  uint8_t readByte() const throw (IOException);
  /// Reads the start of a group
  std::string readStartGroup() const throw (IOException);
  /// Read the end of a group
  std::string readEndGroup() const throw (IOException);
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Host name
  std::string mstrHost;
  /// Server port
  uint16_t mPort;
  /// Timeout for the port
  double mTimeout;
  /// Socket for the port
  ssize_t mSocket;
  /** @}
    */

public:
  Connection(const std::string &strHost, uint32_t u32Port,
    double f64Timeout = 2.5);
  ~Connection();

  const std::string& getHost() const;

  uint32_t getPort() const;

  double getTimeout() const;

  void setTimeout(double f64Time);

  void open() throw(IOException);

  void close() throw(IOException);

  bool isOpen() const;

  const Group* readGroup() throw(IOException);

  void sendControl() throw(IOException);

  Connection& operator >> (int8_t &i8Value) throw(IOException);
  Connection& operator >> (uint8_t &u8Value) throw(IOException);
  Connection& operator >> (int16_t &i16Value) throw(IOException);
  Connection& operator >> (uint16_t &u16Value) throw(IOException);
  Connection& operator >> (int32_t &i32Value) throw(IOException);
  Connection& operator >> (uint32_t &u32Value) throw(IOException);
  Connection& operator >> (int64_t &i64Value) throw(IOException);
  Connection& operator >> (uint64_t &u64Value) throw(IOException);
  Connection& operator >> (std::string &strValue) throw(IOException);
  Connection& operator >> (float &f32Value) throw(IOException);
  Connection& operator >> (double &f64Value) throw(IOException);

protected:

};

#endif // CONNECTION_H
