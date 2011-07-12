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

/** \file UDPConnectionServer.h
    \brief This file defines the UDPConnectionServer class, which is an
           interface for a server UDP connection
  */

#ifndef UDPCONNECTIONSERVER_H
#define UDPCONNECTIONSERVER_H

#include "exceptions/IOException.h"
#include "base/Serializable.h"

#include <string>

#include <stdint.h>

/** The class UDPConnectionServer is an interface for a server UDP
    communication.
    \brief Server UDP communication interface
  */
class UDPConnectionServer :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs UDP connection from parameters
  UDPConnectionServer(uint16_t port, double timeout = 2.5);
  /// Destructor
  virtual ~UDPConnectionServer();
 /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the timeout of the connection
  void setTimeout(double timeout);
  /// Returns the timeout of the connection
  double getTimeout() const;
  /// Returns the binded port
  uint16_t getPort() const;
 /** @}
    */

  /** \name Methods
    @{
    */
  /// Open the connection
  void open() throw (IOException);
  /// Close the connection
  void close() throw (IOException);
  /// Test if the connection is open
  bool isOpen() const;
  /// Read buffer from UDP
  ssize_t readBuffer(uint8_t* au8Buffer, ssize_t nbBytes) throw (IOException);
  /// Write buffer to UDP
  void writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes)
    throw (IOException);
 /** @}
    */

protected:
  /** \name Protected constructors
    @{
    */
  /// Copy constructor
  UDPConnectionServer(const UDPConnectionServer& other);
  /// Assignment operator
  UDPConnectionServer& operator = (const UDPConnectionServer& other);
  /** @}
    */

  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// UDP port
  uint16_t mPort;
  /// Timeout of the port
  double mTimeout;
  /// Socket for the port
  ssize_t mSocket;
  /** @}
    */

};

#endif // UDPCONNECTIONSERVER_H
