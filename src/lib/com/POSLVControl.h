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

/** \file POSLVControl.h
    \brief This file defines the POSLVControl class which is an interface for
           controlling the Applanix POS LV device
  */

#ifndef POSLVCONTROL_H
#define POSLVCONTROL_H

#include "base/TCPConnectionClient.h"
#include "exceptions/IOException.h"
#include "types/Message.h"

/** The POSLVControl class is an interface for controlling the Applanix POS LV
    device.
    \brief Applanix POS LV control
  */
class POSLVControl :
  public TCPConnectionClient {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVControl(const POSLVControl& other);
  /// Assignment operator
  POSLVControl& operator = (const POSLVControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVControl(const std::string& serverIP, uint16_t port = 5601,
    double timeout = 2.5);
  /// Destructor
  ~POSLVControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Sends a message to the Applanix
  const Message* sendMessage(const Message& message) throw (IOException);
  /** @}
    */

  /** \name Operators
    @{
    */
  /// Reads 8-bit signed integer
  POSLVControl& operator >> (int8_t& value);
  /// Reads 8-bit unsigned integer
  POSLVControl& operator >> (uint8_t& value);
  /// Reads 16-bit signed integer
  POSLVControl& operator >> (int16_t& value);
  /// Reads 16-bit unsigned integer
  POSLVControl& operator >> (uint16_t& value);
  /// Reads 32-bit signed integer
  POSLVControl& operator >> (int32_t& value);
  /// Reads 32-bit unsigned integer
  POSLVControl& operator >> (uint32_t& value);
  /// Reads 64-bit signed integer
  POSLVControl& operator >> (int64_t& value);
  /// Reads 64-bit unsigned integer
  POSLVControl& operator >> (uint64_t& value);
  /// Reads 32-bit floating point
  POSLVControl& operator >> (float& value);
  /// Reads 64-bit floating point
  POSLVControl& operator >> (double& value);
  /// Writes 8-bit signed integer
  POSLVControl& operator << (int8_t value);
  /// Writes 8-bit unsigned integer
  POSLVControl& operator << (uint8_t value);
  /// Writes 16-bit signed integer
  POSLVControl& operator << (int16_t value);
  /// Writes 16-bit unsigned integer
  POSLVControl& operator << (uint16_t value);
  /// Writes 32-bit signed integer
  POSLVControl& operator << (int32_t value);
  /// Writes 32-bit unsigned integer
  POSLVControl& operator << (uint32_t value);
  /// Writes 64-bit signed integer
  POSLVControl& operator << (int64_t value);
  /// Writes 64-bit unsigned integer
  POSLVControl& operator << (uint64_t value);
  /// Writes 32-bit floating point
  POSLVControl& operator << (float value);
  /// Writes 64-bit floating point
  POSLVControl& operator << (double value);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
   /// Reads a Message from the network
  const Message* readMessage() throw (IOException);
  /// Reads the start of a message
  void readStartMessage();
  /// Reads the end of a message
  std::string readEndMessage();
  /** @}
    */

};

#endif // POSLVCONTROL_H
