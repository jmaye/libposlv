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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file POSLVComTCP.h
    \brief This file defines the POSLVComTCP class intended for communicating
           with the Applanix POS LV with a TCP connection.
  */

#ifndef POSLVCOMTCP_H
#define POSLVCOMTCP_H

#include "sensor/POSLVReader.h"
#include "sensor/POSLVWriter.h"

class TCPConnectionClient;

/** The POSLVComTCP class implements the TCP communication with the Applanix
    POS LV device.
    \brief Applanix POS LV TCP communication.
  */
class POSLVComTCP :
  public POSLVReader,
  public POSLVWriter {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVComTCP(const POSLVComTCP& other);
  /// Assignment operator
  POSLVComTCP& operator = (const POSLVComTCP& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the connection
  POSLVComTCP(TCPConnectionClient& connection);
  /// Destructor
  virtual ~POSLVComTCP();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Writes a buffer of bytes
  virtual void writeBuffer(const char* buffer, ssize_t numBytes);
  /// Reads a buffer of bytes
  virtual void readBuffer(char* buffer, ssize_t numBytes);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// TCP handle
  TCPConnectionClient& mConnection;
  /** @}
    */

};

#endif // POSLVCOMTCP_H
