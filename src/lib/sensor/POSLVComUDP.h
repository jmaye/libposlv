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

/** \file POSLVComUDP.h
    \brief This file defines the POSLVComUDP class intended for communicating
           with the Applanix POS LV with a UDP connection.
  */

#ifndef POSLVCOMUDP_H
#define POSLVCOMUDP_H

#include <queue>

#include "sensor/POSLVReader.h"

class UDPConnectionServer;

/** The POSLVComUDP class implements the UDP communication with the Applanix
    POS LV device.
    \brief Applanix POS LV UDP communication.
  */
class POSLVComUDP :
  public POSLVReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVComUDP(const POSLVComUDP& other);
  /// Assignment operator
  POSLVComUDP& operator = (const POSLVComUDP& other);
  /** @}
    */

public:
  /** \name Constants
    @{
    */
  /// Max packet size
  static const size_t mMaxPacketSize = 1500;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the connection
  POSLVComUDP(UDPConnectionServer& connection);
  /// Destructor
  virtual ~POSLVComUDP();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Reads a buffer of bytes
  virtual void readBuffer(char* buffer, ssize_t numBytes);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// UDP handle
  UDPConnectionServer& mConnection;
  /// Buffer for fetching UDP packets
  char mPacketsBuffer[mMaxPacketSize];
  /// Buffer for storing UDP bytes and simulates streaming operations
  std::queue<char> mBytesBuffer;
  /** @}
    */

};

#endif // POSLVCOMUDP_H
