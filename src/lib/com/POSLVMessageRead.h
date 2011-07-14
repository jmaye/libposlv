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

/** \file POSLVMessageRead.h
    \brief This file defines the POSLVMessageRead class which is an interface
           for all messages reading from the Applanix device.
  */

#ifndef POSLVMESSAGEREAD_H
#define POSLVMESSAGEREAD_H

#include "types/Message.h"
#include "exceptions/IOException.h"

/** The POSLVMessageRead class is an interface for all messages reading from the
    Applanix device.
    \brief Applanix POS LV reading interface for messages
  */
class POSLVMessageRead {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVMessageRead();
  /// Copy constructor
  POSLVMessageRead(const POSLVMessageRead& other);
  /// Assignment operator
  POSLVMessageRead& operator = (const POSLVMessageRead& other);
  /// Destructor
  virtual ~POSLVMessageRead();
  /** @}
    */

  /** \name Operators
    @{
    */
  /// Reads 8-bit signed integer
  POSLVMessageRead& operator >> (int8_t& value);
  /// Reads 8-bit unsigned integer
  POSLVMessageRead& operator >> (uint8_t& value);
  /// Reads 16-bit signed integer
  POSLVMessageRead& operator >> (int16_t& value);
  /// Reads 16-bit unsigned integer
  POSLVMessageRead& operator >> (uint16_t& value);
  /// Reads 32-bit signed integer
  POSLVMessageRead& operator >> (int32_t& value);
  /// Reads 32-bit unsigned integer
  POSLVMessageRead& operator >> (uint32_t& value);
  /// Reads 64-bit signed integer
  POSLVMessageRead& operator >> (int64_t& value);
  /// Reads 64-bit unsigned integer
  POSLVMessageRead& operator >> (uint64_t& value);
  /// Reads 32-bit floating point
  POSLVMessageRead& operator >> (float& value);
  /// Reads 64-bit floating point
  POSLVMessageRead& operator >> (double& value);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Reads a message from the network
  const Message* readMessage() throw (IOException);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Reads a buffer of byte
  virtual void readBuffer(uint8_t* au8Buffer, ssize_t nbBytes) = 0;
  /// Reads the start of a group
  void readStartMessage();
  /// Reads the end of a group
  std::string readEndMessage();
  /** @}
    */

};

#endif // POSLVMESSAGEREAD
