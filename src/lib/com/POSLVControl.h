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
#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"
#include "types/Acknowledge.h"

/** The POSLVControl class is an interface for controlling the Applanix POS LV
    device.
    \brief Applanix POS LV control
  */
class POSLVControl :
  public TCPConnectionClient,
  public POSLVMessageRead,
  public POSLVMessageWrite {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVControl(const std::string& serverIP, uint16_t port = 5601,
    double timeout = 2.5);
  /// Destructor
  virtual ~POSLVControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Send a control message to the POSLV
  const Acknowledge& sendControl(const Message& message) throw (IOException);
  /** @}
    */

protected:
  /** \name Protected constructors
    @{
    */
  /// Copy constructor
  POSLVControl(const POSLVControl& other);
  /// Assignment operator
  POSLVControl& operator = (const POSLVControl& other);
  /** @}
    */

  /** \name Protected methods
    @{
    */
  /// Reads a buffer of bytes
  virtual void readBuffer(uint8_t* au8Buffer, ssize_t nbBytes);
  /// Writes a buffer of bytes
  virtual void writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes);
  /** @}
    */

};

#endif // POSLVCONTROL_H
