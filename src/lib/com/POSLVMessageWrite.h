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

/** \file POSLVMessageWrite.h
    \brief This file defines the POSLVMessageWrite class which is an interface
           for all messages writing to the Applanix device.
  */

#ifndef POSLVMESSAGEWRITE_H
#define POSLVMESSAGEWRITE_H

#include "types/Message.h"
#include "exceptions/IOException.h"

/** The POSLVMessageWrite class is an interface for all messages writing to the
    Applanix device.
    \brief Applanix POS LV writing interface for messages
  */
class POSLVMessageWrite {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVMessageWrite();
  /// Copy constructor
  POSLVMessageWrite(const POSLVMessageWrite& other);
  /// Assignment operator
  POSLVMessageWrite& operator = (const POSLVMessageWrite& other);
  /// Destructor
  virtual ~POSLVMessageWrite();
  /** @}
    */

  /** \name Operators
    @{
    */
  /// Writes 8-bit signed integer
  POSLVMessageWrite& operator << (int8_t value);
  /// Writes 8-bit unsigned integer
  POSLVMessageWrite& operator << (uint8_t value);
  /// Writes 16-bit signed integer
  POSLVMessageWrite& operator << (int16_t value);
  /// Writes 16-bit unsigned integer
  POSLVMessageWrite& operator << (uint16_t value);
  /// Writes 32-bit signed integer
  POSLVMessageWrite& operator << (int32_t value);
  /// Writes 32-bit unsigned integer
  POSLVMessageWrite& operator << (uint32_t value);
  /// Writes 64-bit signed integer
  POSLVMessageWrite& operator << (int64_t value);
  /// Writes 64-bit unsigned integer
  POSLVMessageWrite& operator << (uint64_t value);
  /// Writes 32-bit floating point
  POSLVMessageWrite& operator << (float value);
  /// Writes 64-bit floating point
  POSLVMessageWrite& operator << (double value);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Sends a message to the Applanix
  void sendMessage(const Message& message) throw (IOException);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Writes a buffer of byte
  virtual void writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes) = 0;
  /** @}
    */

};

#endif // POSLVMESSAGEWRITE
